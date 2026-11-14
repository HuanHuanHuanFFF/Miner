"""Bounded, statement-only all-pairs dot-bank research driver; no commands on import."""
from pathlib import Path
import hashlib, importlib.util, json, re, shlex, shutil, statistics, time

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').is_file())
SUPPORT=HERE.parent/'development-scalar/f64-cost/driver.py'
SUPPORT_SHA='053f20a9efc4967fe9068f254140654314c4b6b54296e63e790b29504d856e89'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
encode=lambda x:(json.dumps(x,ensure_ascii=False,indent=2)+'\n').encode()
def require(condition,message):
    if not condition: raise RuntimeError(message)

def support():
    require(sha(SUPPORT)==SUPPORT_SHA,'Pinned diagnostic support changed')
    s=importlib.util.spec_from_file_location('r24_dot_pinned_support',SUPPORT)
    m=importlib.util.module_from_spec(s);s.loader.exec_module(m)
    return m

def prepare(g,kernel,out,manifest):
    old=support();out=Path(out);out.mkdir(parents=True,exist_ok=True)
    require(g._SANDBOX and not any(n=='score' for n,_ in g.STAGES),'Statement diagnostic only')
    require(sha(kernel)==sha(g.WORK)==manifest['candidate_sha256'],'Exact source differs')
    require(old.sha(g.HERE/'gate.py')=='1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194','Original gate differs')
    require(g.foreign(g.LAYER/'upper')==[],'Statement layer already has foreign artifacts')
    config=(g.LIB/'lakefile.lean').read_bytes();text=config.decode()
    target=re.search(r'^lean_exe benchFull where\s*\n((?:[ \t]+[^\n]*\n|\n)*)',text,re.M)
    require(target is not None,'Original target missing')
    fields=[s.strip() for s in target[1].splitlines() if s.strip() and not s.lstrip().startswith('--')]
    require(set(fields)=={'srcDir := "bench"','root := `MainFull'} and len(fields)==2,'Target-specific settings need review')
    require('R24DotBarrier' not in text and 'r24DotCost' not in text,'Owned target collision')
    extra=(b'\n\nlean_lib R24DotBarrier where\n  srcDir := "work"\n'
           b'\nlean_exe r24DotCost where\n  srcDir := "work"\n  root := `R24DotCostMain\n')
    own={g.WORK.parent/'R24DotCostMain.lean':(HERE/'R24DotCostMain.lean').read_bytes(),
         g.WORK.parent/'R24DotBarrier.lean':(HERE/'R24DotBarrier.lean').read_bytes(),
         g.WORK.parent/'R24DotFixtures.json':(HERE/'fixtures.json').read_bytes(),
         g.WORK.parent/'R24DotCostLake.lean':config+extra}
    result={'official_before':old.official_sources(g),'original_build_before':old.original_build(g),
        'owned_files':{},'build_argv':[g.LAKE,'-f','work/R24DotCostLake.lean','build','r24DotCost'],
        'logical_binary':str(g.BUILD/'bin/r24DotCost'),'fixture_path':str(g.WORK.parent/'R24DotFixtures.json'),
        'source_sha256':sha(kernel),'scope':'Separate diagnostic target/config/barrier only. Original gate/contracts/bench/pins/lakefile untouched.'}
    for p,b in own.items():
        require(not p.exists(),'Owned file already exists: '+str(p))
        with p.open('xb') as f:f.write(b)
        result['owned_files'][str(p)]=hashlib.sha256(b).hexdigest()
    (out/'prepare.json').write_bytes(encode(result))
    return result

def cleanup(prepared):
    for name,digest in prepared['owned_files'].items():
        p=Path(name);require(sha(p)==digest,'Changed owned source preserved: '+name);p.unlink()

def normalize(args):
    return [re.sub(r'(?<=/)(MainFull|R24DotCostMain)(?=\.)','<MAIN>',
        re.sub(r'(?<=/)(benchFull|r24DotCost)(?=\.|$)','<BIN>',x)) for x in args]

def flags(g,out,old):
    result={}
    for name,a,b in [('compile',g.BUILD/'ir/MainFull.c.o.export.trace',g.BUILD/'ir/R24DotCostMain.c.o.export.trace'),
                     ('link',g.BUILD/'bin/benchFull.trace',g.BUILD/'bin/r24DotCost.trace'),
                     ('response',g.BUILD/'bin/benchFull.rsp',g.BUILD/'bin/r24DotCost.rsp')]:
        pair=[]
        for role,p in [('original',a),('new',b)]:
            p=old.visible(g,p);raw=p.read_bytes();(out/(role+'-'+name+'.raw')).write_bytes(raw)
            pair.append(shlex.split(raw.decode()) if name=='response' else old.trace_command(p))
        removed=[]
        if name=='response':
            fresh=[]
            for arg in pair[1]:
                p=Path(arg)
                owned=(p.name in ('libR24DotBarrier.a','R24DotBarrier.c.o.export','R24DotBarrier.c.o.noexport'))
                if owned:
                    require(p.is_absolute() and p.is_relative_to(g.BUILD),'Barrier object escapes build')
                    q=old.visible(g,p);removed.append({'path':str(p),'sha256':sha(q),'bytes':q.stat().st_size})
                else:fresh.append(arg)
            require(removed,'Independent compiled barrier not linked')
            pair[1]=fresh
        require(not any('-flto' in x for row in pair for x in row),'Cross-module LTO would defeat barrier')
        equal=normalize(pair[0])==normalize(pair[1])
        result[name]={'original_args':pair[0],'new_args':pair[1],'only_owned_barrier_removed':removed,'equal_after_only_root_mapping':equal}
    (out/'flags-and-link.json').write_bytes(encode(result))
    require(all(x['equal_after_only_root_mapping'] for x in result.values()),'Compiler/link delta not explained by owned target/barrier')
    return result

def capture(g,out,old,budget,deadline):
    tool=old.load_module(old.CAPTURE,'r24_dot_capture');files=[];objects=[]
    for stem in ['R24DotCostMain','R24DotBarrier','Submission']:
        p=old.visible(g,g.BUILD/'ir'/(stem+'.c'));require(p.is_file(),'Missing selected C: '+stem)
        target=out/(stem+'.c');target.write_bytes(p.read_bytes());files.append({'name':target.name,'sha256':sha(target),'bytes':target.stat().st_size})
        candidates=[p for p in (g.LAYER/'upper/ir').glob(stem+'*.o.*') if p.is_file() and p.read_bytes().startswith(b'\x7fELF')]
        require(candidates,'Missing native object for '+stem)
        obj=next((p for p in candidates if p.name==stem+'.c.o.export'),candidates[0]);objects.append(obj)
        for suffix,cmd,limit in [('nm',['nm','-S','--defined-only',str(obj)],2*1024*1024),
                                 ('asm',['objdump','-dr','--no-show-raw-insn','-Mintel',str(obj)],8*1024*1024)]:
            dest=out/(stem+'-'+suffix+'.txt')
            record=tool._bounded_tool(cmd,dest,budget.cap('capture-'+stem+'-'+suffix,6,24,deadline),limit)
            require(record.get('ok'),'Bounded native capture incomplete')
            files.append({'name':dest.name,'sha256':sha(dest),'bytes':dest.stat().st_size})
    return files,objects

def build_and_measure(g,prepared,out,manifest,absolute_deadline):
    old=support();budget=old.Budget(absolute_deadline);out=Path(out)
    record={'complete':False,'diagnostic_only':True,'new_runtime_correctness':'UNPROVED_FINITE_ORACLE_ONLY',
        'formal_adoption':False,'source_sha256':manifest['candidate_sha256'],'runs':[],
        'scope':'Synthetic generic primitive cost only. Own optimized word64/128 reference, not former2 or current champion. Whole bank prepares each operand row once per call and allocates/drops all outputs inside; repeated resident raw inputs. Includes external raw bank barrier/all-output observer. Not old FloatLib BMM or new target implementation.'}
    def save():
        record['remaining_seconds']=absolute_deadline-time.monotonic();record['budget_events']=budget.events
        (out/'result.json').write_bytes(encode(record))
    save()
    try:
        start=time.monotonic();code,log=g.own(prepared['build_argv'],budget.cap('build',180,64),build='write')
        (out/'build.log').write_bytes(log.encode());record.update(build_exit_code=code,build_seconds=time.monotonic()-start);save()
        require(code==0,'New diagnostic target did not build')
        require(old.original_build(g)==prepared['original_build_before'],'Original objects changed')
        foreign=g.foreign(g.LAYER/'upper');record['foreign']=foreign
        require(all(Path(n).name.split('.')[0] in ('R24DotBarrier','R24DotCostMain','r24DotCost','libR24DotBarrier') for n in foreign),'Unexpected foreign dependency rebuild')
        rebuilt=re.findall(r'(?:Built|Building)\s+([^\s(]+)',log);record['build_targets']=rebuilt
        require(all(n.split(':')[0] in ('R24DotBarrier','R24DotCostMain','r24DotCost') for n in rebuilt),'Non-owned dependency rebuild')
        record['flags']=flags(g,out,old);save()
        files,objects=capture(g,out,old,budget,min(time.monotonic()+40,absolute_deadline-24))
        record['native_capture']=files
        audit=load_local(HERE/'audit-callers.py','r24_dot_actual_callers')
        record['actual_caller_audit']=audit.review(out)
        require(record['actual_caller_audit']['pass'],'Selected C/ASM caller and loop audit failed before timing')
        binary=old.visible(g,Path(prepared['logical_binary']));record['binary_sha256']=sha(binary)
        identities={str(p):sha(p) for p in objects+[binary]}
        if Path('/proc/cpuinfo').is_file():
            raw=Path('/proc/cpuinfo').read_bytes();(out/'cpuinfo.raw').write_bytes(raw);record['cpuinfo_sha256']=hashlib.sha256(raw).hexdigest()
        cpu=getattr(g,'_BENCH_CPU','');argv=(['taskset','-c',str(cpu)] if cpu else [])+[prepared['logical_binary']]
        base_env={'BENCH_DOT_FIXTURE':prepared['fixture_path'],'BENCH_DOT_MACS':'131072','LEAN_ABORT_ON_PANIC':'1'}
        cap=budget.cap('native-oracle',90,32);code,log=g.own(argv,cap,build='read',env_extra={**base_env,'BENCH_DOT_MODE':'verify'},memory_mb=g._BENCH_MEMORY_MB)
        (out/'native-oracle.log').write_bytes(log.encode());record['native_oracle_exit_code']=code;save();require(code==0,'Native oracle rejected source; no timing')
        parser=load_local(HERE/'parse-results.py','r24_dot_parser')
        fixtures=json.loads((HERE/'fixtures.json').read_bytes())
        record['native_oracle']=parser.verify(log,fixtures);save()
        measure_end=min(time.monotonic()+300,absolute_deadline-32)
        for group in ['24282601','24282603']:
            for boundary in ['full']:
                for index,variant in enumerate(['exact','eager','eager','exact','exact','lazy','lazy','exact']):
                    env={**base_env,'BENCH_DOT_MODE':'measure','BENCH_DOT_GROUP':group,'BENCH_DOT_BOUNDARY':boundary,'BENCH_DOT_VARIANT':variant}
                    cap=budget.cap('measure-'+group+'-'+boundary+'-'+str(index),45,32,measure_end)
                    start=time.monotonic();code,log=g.own(argv,cap,build='read',env_extra=env,memory_mb=g._BENCH_MEMORY_MB)
                    label=group+'-'+boundary+'-'+str(index)+'-'+variant;(out/(label+'.log')).write_bytes(log.encode())
                    item={'group':group,'boundary':boundary,'order':index,'variant':variant,'exit_code':code,'wall_seconds':time.monotonic()-start,
                          'log_sha256':hashlib.sha256(log.encode()).hexdigest(),'env':env,'argv':argv}
                    record['runs'].append(item);save();require(code==0,'Process failed, raw evidence retained')
                    rows=parser.rows(log,fixtures,group)
                    require(all(x['variant']==variant and x['boundary']==boundary for x in rows.values()),'Printed runner mode differs from selected process')
                    (out/(label+'-rows.json')).write_bytes(encode(rows));item['rows']=rows;save()
        record['paired']=parser.paired(record['runs'])
        require(all(sha(p)==h for p,h in identities.items()),'Measured native artifacts changed')
        require(all(sha(p)==h for p,h in prepared['owned_files'].items()),'Owned inputs changed')
        require(old.original_build(g)==prepared['original_build_before'] and old.official_sources(g)==prepared['official_before'],'Original source/build changed')
        record['originals_unchanged']=True
        record['complete']=True
    except Exception as error:
        record.update(complete=False,error_type=type(error).__name__,error=str(error));raise
    finally:save()

def load_local(path,name):
    spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
