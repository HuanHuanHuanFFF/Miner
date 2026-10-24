"""R13 exactDF per-case whole anchors and independent generated-C stage diagnosis.

run(g,kernel,out,public_plan,seed) is statement-only. No scored gate may call it.
Original official C/flags/input generation are retained as separate evidence;
only disposable upper-layer C is instrumented and relinked for diagnosis.
"""
from pathlib import Path
import hashlib,importlib.util,json,re,shlex,shutil,subprocess,time,traceback

HEAD='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
SOURCE='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
SEED=1224016
INNER=3
PROFILE_PROCESSES=2
MAX_SECONDS=300
PREFIX='profile-r13-'
CATEGORIES=('whole_bmm','whole_sum','amap','bpack','cross_prepare','compute','output','repair','dispatch_scan')
ROOTS={'lp_competition_Submission_bmm':'whole_bmm','lp_competition_Submission_sum':'whole_sum'}


def require(ok,message):
    if not ok:raise RuntimeError(message)


def sha(raw):return hashlib.sha256(raw).hexdigest()


def file_sha(path):
    h=hashlib.sha256()
    with Path(path).open('rb')as stream:
        for chunk in iter(lambda:stream.read(1024*1024),b''):h.update(chunk)
    return h.hexdigest()


def mask_c(text):
    return re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*',
                  lambda m:''.join('\n'if c=='\n'else' 'for c in m.group()),text,flags=re.S)


def functions(text):
    masked=mask_c(text);rows=[]
    pattern=re.compile(r'^LEAN_EXPORT\s+(lean_object\*|uint32_t|float|size_t|uint8_t)\s+([A-Za-z_][A-Za-z0-9_]*)\([^;\n]*\)\s*\{',re.M)
    for match in pattern.finditer(masked):
        depth=1;i=match.end()
        while depth and i<len(masked):
            depth+=(masked[i]=='{')-(masked[i]=='}');i+=1
        require(depth==0,'unbalanced generated C function '+match.group(2))
        rows.append({'symbol':match.group(2),'return_type':match.group(1),'start':match.start(),
                     'head_end':match.end(),'end':i,'body':text[match.start():i]})
    return rows


def category(name):
    if '___boxed'in name:return None
    if name in ROOTS:return ROOTS[name]
    if ('_all' in name or '_any' in name)and '___at___00Submission_bmm_'in name:return 'dispatch_scan'
    if re.search(r'Submission_(?:R7NaNReplay_(?:replayLoop|replayEarly|replayStep)|R7SumRepair_suffixLoop)(?:___|$)',name):return 'repair'
    if 'Array_mapMUnsafe_map' in name and '___at___00Submission_'in name:return 'amap'
    if re.search(r'Submission_Packed10_packB(?:___|$)',name)or '___at___00Submission_Packed10_packB_'in name:return 'bpack'
    if re.search(r'Submission_R11CrossRows_(?:packGeneral|packShared|pack)(?:___|$)',name):return 'cross_prepare'
    if re.search(r'Submission_(?:NativeFinal_dotLoop|Packed10Index_loop|Packed10_dot|R11CrossRows_(?:wordLoop|natLoop|dot8)|R7SinglePassSum_(?:loop|natLoop))(?:___|$)',name):return 'compute'
    if re.search(r'Submission_(?:RowStream_(?:emit|group|row|output|core)|RowOutput_row|DirectContinuous_(?:core|output|row)|R11CrossRows_(?:core|words|finish8)|Packed10_finish|UnderflowZero_zeros)(?:___|$)',name):return 'output'
    if 'Fin_foldl_loop'in name and re.search(r'___at___00Submission_(?:RowStream_|DirectContinuous_|R11CrossRows_)',name):return 'output'
    return None


PRELUDE=r'''
/* R13 diagnostic-only POSIX ABI, copied from the established profile helper. */
struct timespec;
struct pr13_timespec { long sec; long nsec; };
extern int clock_gettime(int, struct timespec *);
extern int printf(const char *, ...);
static unsigned long long pr13_inc[9],pr13_exc[9],pr13_calls[9];
static unsigned long long pr13_start[128],pr13_child[128];
static int pr13_cat[128],pr13_active[128],pr13_depth;
static unsigned long long pr13_now(void) {
  struct pr13_timespec t;
  if(clock_gettime(1,(struct timespec *)&t)) __builtin_trap();
  return (unsigned long long)t.sec*1000000000ULL+(unsigned long long)t.nsec;
}
static void pr13_begin(int c) {
  if(pr13_depth>=128) __builtin_trap();
  pr13_active[pr13_depth]=(c<2)||(pr13_depth&&pr13_active[pr13_depth-1]);
  pr13_cat[pr13_depth]=c;pr13_child[pr13_depth]=0;
  pr13_start[pr13_depth]=pr13_now();pr13_depth++;
}
static void pr13_end(int c) {
  unsigned long long end=pr13_now(),elapsed;
  if(pr13_depth<=0) __builtin_trap();
  pr13_depth--;if(pr13_cat[pr13_depth]!=c) __builtin_trap();
  elapsed=end-pr13_start[pr13_depth];
  if(elapsed<pr13_child[pr13_depth]) __builtin_trap();
  if(pr13_active[pr13_depth]) {
    pr13_inc[c]+=elapsed;pr13_exc[c]+=elapsed-pr13_child[pr13_depth];pr13_calls[c]++;
  }
  if(pr13_depth) pr13_child[pr13_depth-1]+=elapsed;
}
__attribute__((destructor)) static void pr13_dump(void) {
  int c;
  for(c=0;c<9;c++)printf("FL13 cat=%d inclusive_ns=%llu exclusive_ns=%llu calls=%llu\n",c,pr13_inc[c],pr13_exc[c],pr13_calls[c]);
  printf("FL13_END depth=%d\n",pr13_depth);
}
'''


def instrument(raw):
    text=raw.decode('utf-8');require('pr13_'not in text,'already instrumented C')
    inventory=[];skipped=[];patches=[]
    for row in functions(text):
        cat=category(row['symbol'])
        if cat is None:continue
        body=row['body'];clean=mask_c(body)
        # Real recursive C calls would make an inclusive per-entry probe a
        # per-iteration operation. Tail-recursive goto _start is safe because
        # begin is placed BEFORE that label.
        rest=clean[clean.index('{')+1:]
        if re.search(r'\b'+re.escape(row['symbol'])+r'\s*\(',rest):
            skipped.append({'symbol':row['symbol'],'category':cat,'reason':'recursive C call; not instrumented'});continue
        cid=CATEGORIES.index(cat);first=body.index('{')+1
        changed=body[:first]+f'\npr13_begin({cid});\n'+body[first:]
        returns=list(re.finditer(r'\breturn\s+([^;\n]+);',mask_c(changed)))
        require(returns and len(returns)==len(re.findall(r'\breturn\b',mask_c(changed))), 'return format drift '+row['symbol'])
        for number,match in reversed(list(enumerate(returns))):
            expression=changed[match.start(1):match.end(1)]
            replacement='{ '+row['return_type']+f' pr13_value_{number} = '+expression+f'; pr13_end({cid}); return pr13_value_{number}; }}'
            changed=changed[:match.start()]+replacement+changed[match.end():]
        # Instrumentation must remain balanced through all nested returns.
        require(mask_c(changed).count('{')==mask_c(changed).count('}'),'instrumentation brace drift')
        patches.append((row['start'],row['end'],changed))
        inventory.append({'symbol':row['symbol'],'category':cat,'return_sites':len(returns),
            'original_sha256':sha(body.encode()),'instrumented_sha256':sha(changed.encode())})
    require(set(ROOTS)<=set(r['symbol']for r in inventory),'actual bmm/sum roots absent')
    require(any(r['category']=='compute'for r in inventory),'no actual compute boundary')
    for start,end,changed in reversed(patches):text=text[:start]+changed+text[end:]
    return (PRELUDE+text).encode(),{'instrumented_functions':inventory,'skipped':skipped,
        'category_function_counts':{c:sum(r['category']==c for r in inventory)for c in CATEGORIES},
        'timers_at_function_entry_before_tail_label':True,'all_selected_return_sites_instrumented':True,
        'exclusive_nested_accounting':True}


def parse_stages(log):
    rows={};end=[]
    pattern=re.compile(r'FL13 cat=(\d+) inclusive_ns=(\d+) exclusive_ns=(\d+) calls=(\d+)')
    for line in log.splitlines():
        if line.startswith('FL13 cat='):
            m=pattern.fullmatch(line);require(m is not None,'malformed stage row')
            c,inc,exc,calls=map(int,m.groups());require(0<=c<len(CATEGORIES)and c not in rows,'duplicate/unknown category')
            require(exc<=inc,'exclusive exceeds inclusive');rows[c]={'inclusive_ns':inc,'exclusive_ns':exc,'calls':calls}
        elif line.startswith('FL13_END '):end.append(line)
    require(set(rows)==set(range(len(CATEGORIES)))and end==['FL13_END depth=0'],'incomplete stage data/stack imbalance')
    return {CATEGORIES[c]:v for c,v in rows.items()}


def verify_case(case,control,row,stages):
    require(row['checksum']==control['checksum'],'profile checksum differs from untouched whole '+case['name'])
    sweeps=INNER+1 if case['timed']else 1
    expected_bmm=sweeps if case['kernel']=='bmm'else 0
    expected_sum=sweeps*case['batch']if case['kernel']=='sum'else 0
    require(stages['whole_bmm']['calls']==expected_bmm and stages['whole_sum']['calls']==expected_sum,
            'whole-call coverage mismatch '+case['name'])
    return expected_bmm+expected_sum


def run(g,kernel,out,public_plan,seed):
    kernel,out=Path(kernel),Path(out);out.mkdir(parents=True,exist_ok=True)
    require(not(out/(PREFIX+'result.json')).exists(),'use fresh diagnostic output')
    started=time.monotonic();deadline=started+MAX_SECONDS;executions=[]
    def save(name,data):
        require(not data.startswith(b'\x7fELF'),'ELF artifact export prohibited')
        with(out/(PREFIX+name)).open('xb')as stream:stream.write(data)
    def save_json(name,value):save(name,(json.dumps(value,ensure_ascii=False,indent=2)+'\n').encode())
    try:
        require(getattr(g,'_SANDBOX',False),'original sandbox upper layer required')
        require(not any(name=='score'for name,_ in g.STAGES),'refusing scored gate')
        require(seed==SEED and g._PAIRS==500000,'only exposed1224016 /500000 plan supported')
        require(Path(g.benchmark_suite.__file__).resolve()==(g.HERE/'benchmark_suite.py').resolve(),'wrong official generator module')
        require(sha(kernel.read_bytes())==SOURCE==sha(g.WORK.read_bytes()),'exactDF source/work mismatch')
        require(subprocess.check_output(['git','rev-parse','HEAD'],cwd=g.HERE,text=True).strip()==HEAD,'official version drift')
        expected=g.benchmark_suite.make_plan(g.benchmark_suite.load(g.HERE/'suites/public-v2.json'),seed,500000)
        require(expected==public_plan,'plan is not exact official public generator/seed')
        require(len({c['name']for c in public_plan['cases']})==len(public_plan['cases']),'duplicate case name')
        old_path=Path(__file__).resolve().parent.parent/'profile-current.py'
        spec=importlib.util.spec_from_file_location('r13_existing_profile_helpers',old_path)
        old=importlib.util.module_from_spec(spec);spec.loader.exec_module(old)
        upper=g.LAYER/'upper';cpath=upper/'ir/Submission.c'
        require(cpath.is_file(),'original candidate C missing')
        original=cpath.read_bytes();changed,coverage=instrument(original)
        commands=[]
        for trace in sorted(upper.rglob('*.trace')):
            try:commands.extend(r['message'][3:]for r in json.loads(trace.read_bytes()).get('log',[])if r.get('message','').startswith('.> '))
            except (OSError,ValueError):continue
        commands=list(dict.fromkeys(commands));parsed=[shlex.split(c)for c in commands]
        bench=g.BUILD/'bin/benchFull';logical_c=g.BUILD/'ir/Submission.c'
        compiles=[a for a in parsed if Path(a[0]).name=='clang'and '-c'in a and str(logical_c)in a]
        links=[a for a in parsed if Path(a[0]).name=='clang'and '-c'not in a and '-o'in a and a[a.index('-o')+1]==str(bench)]
        require(len(compiles)==len(links)==1,'missing/ambiguous original compile/link trace')
        compile_argv,link_argv=compiles[0],links[0];obj=Path(compile_argv[compile_argv.index('-o')+1])
        def visible(logical):
            try:top=upper/Path(logical).relative_to(g.BUILD)
            except ValueError:top=Path(logical)
            return top if top.is_file()else Path(logical)
        def identity(logical):
            p=visible(logical);require(p.is_file(),'compiled object/binary inaccessible')
            return {'logical':str(logical),'bytes':p.stat().st_size,'sha256':file_sha(p),'binary_exported':False}
        before={'object':identity(obj),'binary':identity(bench)}
        save('original-Submission.c',original);save('instrumented-Submission.c',changed);save('Kernel.lean',kernel.read_bytes())
        save_json('full-public-plan.json',public_plan);save_json('build-commands.json',commands)
        for i,arg in enumerate(a for a in link_argv if a.startswith('@')):save(f'link-response-{i}.rsp',visible(Path(arg[1:])).read_bytes())
        immutable={str(p.relative_to(g.HERE)):file_sha(p)for p in [g.HERE/'gate.py',g.HERE/'benchmark_suite.py',g.HERE/'suites/public-v2.json',*sorted((g.LIB/'contract').rglob('*.lean'))]}
        cpu=getattr(g,'_BENCH_CPU','');argv=(['taskset','-c',str(cpu)]if cpu and shutil.which('taskset')else[])+[str(bench)]
        def command(args,name,build,plan,cap=30):
            require(time.monotonic()<deadline,'300second diagnostic budget exhausted')
            compact=json.dumps(plan,separators=(',',':'))
            env={'BENCH_PLAN':compact,'BENCH_SEED':str(seed),'BENCH_PAIRS':'500000','BENCH_INNER':str(INNER),'LEAN_ABORT_ON_PANIC':'1'}
            t=time.monotonic();code,log=g.run(args,max(.1,min(cap,deadline-t)),build=build,env_extra=env,
                memory_mb=g._BUILD_MEMORY_MB if build=='write'else g._BENCH_MEMORY_MB)
            save(name+'.log',log.encode());executions.append({'name':name,'exit_code':code,'seconds':time.monotonic()-t,
                'plan_sha256':sha(compact.encode()),'log_sha256':sha(log.encode()),'argv':args})
            save_json('executions.json.part-'+str(len(executions)),executions)
            require(code==0,name+' failed; complete returned log retained');return log
        # Untouched original full public call/checksum/time anchor before any
        # generated-C mutation. This is NOT another full correctness gate.
        control_log=command(argv,'original-whole-full-plan','read',public_plan,120)
        control=old.bench_rows(control_log,public_plan)
        require('FL13 'not in control_log,'control already instrumented')
        save_json('original-whole-full-plan.json',control)
        cpath.write_bytes(changed)
        command(compile_argv,'compile-instrumented','write',public_plan,60)
        command(link_argv,'link-instrumented','write',public_plan,60)
        after={'object':identity(obj),'binary':identity(bench)}
        require(before['object']['sha256']!=after['object']['sha256']and before['binary']['sha256']!=after['binary']['sha256'],'rebuild did not change exact objects')
        cases=[]
        for index,case in enumerate(public_plan['cases']):
            single={**public_plan,'cases':[case]};measurements=[]
            for process in range(PROFILE_PROCESSES):
                log=command(argv,f'case-{index:03d}-profile-{process}','read',single)
                row=old.bench_rows(log,single)[case['name']]
                stages=parse_stages(log)
                expected_calls=verify_case(case,control[case['name']],row,stages)
                measurements.append({'process':process,'benchmark_row':row,'stages_all_checksum_and_timed_sweeps':stages,
                    'expected_pure_kernel_calls':expected_calls,
                    'stage_status':{c:('OBSERVED'if stages[c]['calls']else'NOT_EXECUTED_OR_BOUNDARY_NOT_SEPARATE')for c in CATEGORIES}})
            cases.append({'case':case,'original_whole_row':control[case['name']],'profile_measurements':measurements,
                'checksum_matches_original':True,'scalar_stage_scope':'WHOLE_BENCHMARK_ONLY'if case['kernel']in ('add','mul')else None})
            save_json('cases-progress.json.part-'+str(index),cases[-1])
        require(all(file_sha(g.HERE/name)==value for name,value in immutable.items()),'official source changed')
        require(sha(g.WORK.read_bytes())==SOURCE,'Kernel work source changed')
        result={'diagnostic_only':True,'full_gate':False,'complete':True,'kernel_sha256':SOURCE,'official_commit':HEAD,'seed':seed,
            'inner':INNER,'profile_processes':PROFILE_PROCESSES,'cases':cases,'coverage':coverage,'executions':executions,
            'build_identities':{'before':before,'instrumented':after},'official_source_hashes_unchanged':immutable,
            'module_sha256':file_sha(Path(__file__)),'reused_profile_helper_sha256':file_sha(old_path),
            'stage_scope':'Inclusive/exclusive generated-C function intervals across warmup+all3 sweeps; nested exclusive totals avoid double counting. Pure kernel interval excludes official caller checksum/refcount work, which remains included in each whole benchmark row.',
            'limits':'Per-function clocks, different per-case process/cache context, instrumentation/compiler layout and startup make stage/whole deltas diagnostic only; never project these microtimes to official gain.',
            'unknown_boundaries':'Inline dispatch scans, fused compute/output and first-NaN repair not isolated by observed C function boundaries remain root exclusive/residual. Zero stage time is not proof that a phase has zero cost.',
            'artifacts':'No ELF/object exported; generated source/patch-equivalent originals, commands, link responses, hashes, logs and checksum rows only.'}
        save_json('result.json',result);return result
    except Exception as exc:
        save_json('error.json',{'diagnostic_only':True,'complete':False,'error':str(exc),'traceback':traceback.format_exc(),'executions':executions})
        raise
