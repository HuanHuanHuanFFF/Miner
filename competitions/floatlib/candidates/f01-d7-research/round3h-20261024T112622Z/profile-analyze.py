"""Read-only exactDF R13 profile validation and diagnostic cost distributions.

No stage measurement is converted to an official score or removable-cost claim.
"""
from pathlib import Path
import argparse,collections,hashlib,importlib.util,json,re,statistics

HERE=Path(__file__).resolve().parent
REPO=next(p for p in HERE.parents if (p/'competitions/floatlib').is_dir())
SOURCE='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
HEAD='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
MODULE='0b973c9c309b4e86d8e0576a32873ab097a41a1db3b45c1600f3892ac538a334'
PLAN='dbeebe1f0e1252c24275f22349ad1d8bf11899be6a88150ba2364a9950f66140'
BENCH='2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f'
SEED=1224016
CATEGORIES=('whole_bmm','whole_sum','amap','bpack','cross_prepare','compute','output','repair','dispatch_scan')
PREFIX='profile-r13-'
MASK64=(1<<64)-1


def require(ok,message):
    if not ok:raise ValueError(message)


def sha(raw):return hashlib.sha256(raw).hexdigest()
def canonical(value):return sha(json.dumps(value,sort_keys=True,separators=(',',':')).encode())
def load(path):return json.loads(Path(path).read_bytes())
def integer(v):return type(v)is int and v>=0


def word(seed,index,stream):
    z=(seed+index*0x9e3779b97f4a7c15+stream*0xd1b54a32d192ed03)&MASK64
    z=((z^(z>>30))*0xbf58476d1ce4e5b9)&MASK64
    z=((z^(z>>27))*0x94d049bb133111eb)&MASK64
    return (z^(z>>31))&0xffffffff


def element(c,i,role,row):
    """Literal unsigned-word translation of official Bench.Suite.element.

    This models input routing only. It performs no float kernel arithmetic.
    """
    def draw(j,k):return word(c['seed'],j,role*16+k)
    if c['mag']==2:return draw(i,0)
    place=c['specPlace']
    special=(c['specRate']>0 and (
        (i+c['seed']+7*role)%c['specPeriod']==0 if place==1 else
        draw(i//c['specBurst'],8)%100000<c['specRate'] if place==2 else
        (i%row in (0,max(0,row-1)) and draw(i,9)%100000<c['specRate']) if place==3 else
        draw(i,9)%100000<c['specRate']))
    if special:
        kinds=[k for k in range(5)if (c['specMask']>>k)&1]
        kind=kinds[draw(i,5)%len(kinds)]if kinds else 1
        sign=draw(i,6)&0x80000000;low=draw(i,7)&0x7fffff
        return sign|{0:0x7f800000,1:0x7f800000|(low|1),2:0x7f7fffff,3:low|1,4:0}[kind]
    if c['zeroPct']>0 and draw(i//c['zeroCluster'],11)%100<c['zeroPct']:
        w=draw(i,10)
        return {0:0,1:0x80000000,2:w&0x80000000,3:(w&0x807fffff)|((1+w%30)<<23)}[c['zeroKind']]
    if c['subPct']>0 and draw(i//c['subBlock'],12)%100<c['subPct']:
        return (draw(i,13)&0x807fffff)|1
    j=draw(i,14)%c['codebook']if c['codebook']else i
    w=draw(j,1)
    trailing=(w&-w).bit_length()-1 if w else 32
    e=c['center']-min(trailing,c['spread'])if c['mag']==1 else c['center']-c['spread']+w%(2*c['spread']+1)
    shift=draw(i//c['scaleBlock'],2)%(2*c['scaleShift']+1)-c['scaleShift']if c['scaleBlock']else 0
    keep=0x7fffff if c['mantBits']>=23 else 0x7fffff^((1<<(23-c['mantBits']))-1)
    sign=0 if draw(j,4)%100<c['positive']else 0x80000000
    return sign|(max(1,min(254,e+shift))<<23)|(draw(j,3)&keep)


def classify(c):
    if c['kernel']!='bmm':return {'route':c['kernel'],'evidence':'official case kernel'}
    b,m,n,p=(c[k]for k in ('batch','m','n','p'))
    scanned=[0,0];first_reject=[]
    for role,length,row in ((0,b*m*n,n),(1,b*n*p,p)):
        for i in range(length):
            raw=element(c,i,role,row);scanned[role]+=1
            if raw&0x7fffffff>=0x16000000:
                first_reject=[role,i,raw];break
        if first_reject:break
    if not first_reject:route='UnderflowZero'
    elif p==2 and 4<=b*m and 0<n<(1<<64) and max(b*m*n,b*n*p,b*m*p)<(1<<64):route='Cross'
    elif n<=4 and 2<p:route='DirectContinuous'
    elif n<=4 or p<=2:route='DirectSmall'
    elif b*m*p==0 or n==0:route='ReferenceEmpty'
    else:route='RowStream'
    return {'route':route,'evidence':'SOURCE_MODEL: literal official element words + frozen DF routing, not machine branch trace',
        'underflow_scan_words':scanned,'first_underflow_reject_role_index_raw':first_reject or None}


def validate_shape(d,plan):
    require(d.get('complete')is True and d.get('diagnostic_only')is True and d.get('full_gate')is False,'incomplete or non-diagnostic result')
    require(d.get('kernel_sha256')==SOURCE and d.get('official_commit')==HEAD and d.get('seed')==SEED,'source/official/seed mismatch')
    require(d.get('module_sha256')==MODULE,'unfrozen profile producer')
    require(d.get('inner')==3 and d.get('profile_processes')==2,'profile repetition mismatch')
    require(len(plan.get('cases',[]))==156 and canonical(plan)==PLAN,'not exact official1224016 /156case plan')
    require(len(d.get('cases',[]))==156,'result case count differs')
    names=[c['name']for c in plan['cases']]
    require(len(set(names))==156,'duplicate plan case')
    require([r.get('case')for r in d['cases']]==plan['cases'],'result/order/case parameters differ from original plan')
    for item in d['cases']:
        c=item['case'];anchor=item['original_whole_row'];timed=c['timed']
        require(type(timed)is bool and anchor.get('timed')is timed,'anchor timed flag mismatch')
        require(integer(anchor.get('checksum'))and integer(anchor.get('best_ns')),'invalid anchor row')
        require((anchor['best_ns']>0)if timed else anchor['best_ns']==0,'invalid whole time')
        require(item.get('checksum_matches_original')is True,'checksum assertion absent')
        measures=item.get('profile_measurements',[])
        require(len(measures)==2 and [r.get('process')for r in measures]==[0,1],'profile process coverage')
        sweeps=4 if timed else 1
        calls=sweeps if c['kernel']=='bmm'else sweeps*c['batch']if c['kernel']=='sum'else 0
        for r in measures:
            row=r['benchmark_row'];stages=r['stages_all_checksum_and_timed_sweeps']
            require(row.get('timed')is timed and row.get('checksum')==anchor['checksum'],'profile checksum/timed differs')
            require(integer(row.get('best_ns'))and ((row['best_ns']>0)if timed else row['best_ns']==0),'invalid profile whole time')
            require(set(stages)==set(CATEGORIES),'stage coverage differs')
            for v in stages.values():
                require(set(v)=={'inclusive_ns','exclusive_ns','calls'}and all(integer(x)for x in v.values()),'invalid stage row')
                require(v['exclusive_ns']<=v['inclusive_ns'],'exclusive exceeds inclusive')
                require(v['calls']>0 or v['inclusive_ns']==v['exclusive_ns']==0,'zero calls with positive stage time')
            bmm=calls if c['kernel']=='bmm'else 0;total=calls if c['kernel']=='sum'else 0
            require(stages['whole_bmm']['calls']==bmm and stages['whole_sum']['calls']==total and r.get('expected_pure_kernel_calls')==calls,'pure root coverage differs')
            root_ns=stages['whole_bmm']['inclusive_ns']+stages['whole_sum']['inclusive_ns']
            require(sum(v['exclusive_ns']for v in stages.values())==root_ns,'exclusive partition does not equal measured pure roots')
    return True


class Originals:
    def __init__(self,index_path):
        self.path=Path(index_path).resolve();self.index=load(self.path)
        self.root=(self.path.parent/self.index['directory']).resolve()
        require(self.root.is_relative_to(self.path.parent),'unsafe artifact directory')
        self.files=self.index['files'];self.checked={}
    def read(self,path):
        p=Path(path).resolve();require(p.is_relative_to(self.root),'evidence outside original artifact root')
        key=p.relative_to(self.root).as_posix();require(key in self.files,'original index omits '+key)
        raw=p.read_bytes();entry=self.files[key]
        require(sha(raw)==entry['sha256']and len(raw)==entry['bytes'],'original artifact hash/size mismatch '+key)
        require(not raw.startswith(b'\x7fELF'),'unexpected binary export')
        self.checked[key]={'sha256':sha(raw),'bytes':len(raw)};return raw


def parse_bench(log):
    rows={}
    for line in log.splitlines():
        v=line.split()
        if len(v)!=4 or v[1]not in ('true','false'):continue
        require(v[0]not in rows and v[2].isdigit()and v[3].isdigit(),'duplicate/malformed benchmark log row')
        rows[v[0]]={'timed':v[1]=='true','best_ns':int(v[2]),'checksum':int(v[3])}
    return rows


def parse_stages(log):
    rows={};ends=[]
    for line in log.splitlines():
        if line.startswith('FL13 cat='):
            m=re.fullmatch(r'FL13 cat=(\d+) inclusive_ns=(\d+) exclusive_ns=(\d+) calls=(\d+)',line)
            require(m is not None,'malformed stage log');c,inc,exc,calls=map(int,m.groups())
            require(0<=c<9 and c not in rows,'duplicate stage log category')
            rows[c]={'inclusive_ns':inc,'exclusive_ns':exc,'calls':calls}
        elif line.startswith('FL13_END '):ends.append(line)
    require(set(rows)==set(range(9))and ends==['FL13_END depth=0'],'missing/unbalanced stage log')
    return {CATEGORIES[c]:v for c,v in rows.items()}


def summarize(d):
    cases=[];groups=collections.defaultdict(list)
    for item in d['cases']:
        c=item['case'];route=classify(c)
        exc={cat:statistics.mean(r['stages_all_checksum_and_timed_sweeps'][cat]['exclusive_ns']for r in item['profile_measurements'])for cat in CATEGORIES}
        pure=sum(exc.values())
        row={'name':c['name'],'kernel':c['kernel'],'official_cell':':'.join(c['name'].split(':')[:2]),'timed':c['timed'],
            'route':route,'work':c['work'],'original_whole_row':item['original_whole_row'],
            'profile_whole_rows':[r['benchmark_row']for r in item['profile_measurements']],
            'exclusive_ns_mean_per_profile_process':exc,'measured_pure_root_ns_mean_per_process':pure,
            'exclusive_fraction_of_instrumented_pure_root':{k:v/pure if pure else None for k,v in exc.items()},
            'inseparable_cost':'UNKNOWN: root exclusive includes inline scans/dispatch/fused work and timer overhead; categories may include allocation, fill, conversion and layout costs.'}
        cases.append(row)
        groups['route:'+route['route']].append(row);groups['cell:'+row['official_cell']].append(row)
        groups['kernel:'+c['kernel']].append(row)
    summary={}
    for key,allrows in sorted(groups.items()):
        summary[key]={}
        for label,rows in [('timed',[r for r in allrows if r['timed']]),('untimed',[r for r in allrows if not r['timed']])]:
            exc={cat:sum(r['exclusive_ns_mean_per_profile_process'][cat]for r in rows)for cat in CATEGORIES};pure=sum(exc.values())
            summary[key][label]={'cases':len(rows),'original_whole_best_ns_sum':sum(r['original_whole_row']['best_ns']for r in rows),
                'exclusive_ns_sum_of_per_case_process_means':exc,
                'exclusive_fraction_of_instrumented_pure_roots':{k:v/pure if pure else None for k,v in exc.items()}}
    return {'diagnostic_only':True,'formal_score_prediction':None,'case_count':len(cases),'cases':cases,'groups':summary,
        'interpretation':{'whole':'Original fastest sweep includes caller checksum and cleanup; instrumented stages aggregate warmup + all three timed sweeps in separate processes.',
            'fractions':'Nested-exclusive fractions refer only to instrumented pure-root durations of this workload, never official-score shares.',
            'amap':'Only actual RowStream_output Array.map helper; includes mapping/allocation overhead, not pure conversion alone.',
            'bpack':'Packed10_packB includes allocation/fill/padding/conversion; its entire duration is NOT removable by candidate708.',
            'route':'SOURCE_MODEL from exact generator words + frozen DF control flow; no per-branch machine trace was recorded.',
            'unknown':'Inseparable scans, fused stages, uninstrumented helpers and timer/layout effects are UNKNOWN. No stage ns predicts official speedup or champion multiplier.'}}


def analyze(result_path,index_path,kernel_path,bench_source):
    original=Originals(index_path);result_path=Path(result_path).resolve();folder=result_path.parent
    d=json.loads(original.read(result_path));plan=json.loads(original.read(folder/(PREFIX+'full-public-plan.json')))
    validate_shape(d,plan)
    require(sha(Path(kernel_path).read_bytes())==SOURCE and original.read(folder/(PREFIX+'Kernel.lean'))==Path(kernel_path).read_bytes(),'DF kernel bytes differ')
    require(sha(Path(bench_source).read_bytes())==BENCH,'official BenchSuite generator source differs')
    require(sha((HERE/'profile-current.py').read_bytes())==MODULE,'local frozen helper changed')
    spec=importlib.util.spec_from_file_location('r13_frozen_format_helpers',HERE/'profile-current.py')
    helper=importlib.util.module_from_spec(spec);spec.loader.exec_module(helper)
    c=original.read(folder/(PREFIX+'original-Submission.c'));changed=original.read(folder/(PREFIX+'instrumented-Submission.c'))
    reproduced,coverage=helper.instrument(c)
    require(changed==reproduced and coverage==d['coverage'],'instrumentation source/inventory differs')
    amap=[r['symbol']for r in coverage['instrumented_functions']if r['category']=='amap']
    pattern=r'lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowStream_output_spec__[0-9]+(?:___redArg)?'
    require(amap and all(re.fullmatch(pattern,n)for n in amap),'amap contains non-RowStream mapping')
    anchor_log=original.read(folder/(PREFIX+'original-whole-full-plan.log')).decode()
    anchors=parse_bench(anchor_log)
    require('FL13 'not in anchor_log,'original anchor was instrumented')
    expected={r['case']['name']:r['original_whole_row']for r in d['cases']}
    require(anchors==expected==json.loads(original.read(folder/(PREFIX+'original-whole-full-plan.json'))),'original whole log/json/result differ')
    executions=d['executions'];require(len(executions)==3+156*2 and len({e['name']for e in executions})==len(executions),'execution coverage differs')
    for e in executions:
        raw=original.read(folder/(PREFIX+e['name']+'.log'))
        require(e['exit_code']==0 and sha(raw)==e['log_sha256'],'execution not successful/raw log differs')
    for i,item in enumerate(d['cases']):
        for r in item['profile_measurements']:
            log=original.read(folder/(PREFIX+f"case-{i:03d}-profile-{r['process']}.log")).decode()
            require(parse_bench(log)=={item['case']['name']:r['benchmark_row']}and parse_stages(log)==r['stages_all_checksum_and_timed_sweeps'],'raw profile log/result differs')
    # Verify all exported diagnostic source/commands/progress artifacts, not just summaries.
    for p in sorted(folder.glob(PREFIX+'*')):
        if p.is_file():original.read(p)
    out=summarize(d)
    out['validated']={'complete':True,'exactDF':SOURCE,'official_commit':HEAD,'seed':SEED,'cases':156,'checksums_and_pure_root_calls':True,
        'exclusive_partition':True,'official_plan_canonical_sha256':PLAN,'raw_logs_reconciled':True,'artifact_files':original.checked,
        'hash_index':{'path':str(original.path),'sha256':sha(original.path.read_bytes())},
        'local_sources':{str(p):sha(p.read_bytes())for p in [Path(__file__),Path(kernel_path),Path(bench_source),HERE/'profile-current.py']},
        'actual_amap_symbols':amap,'source_branch_model_only':True}
    return out


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--result',required=True,type=Path);ap.add_argument('--index',required=True,type=Path)
    ap.add_argument('--out',required=True,type=Path)
    ap.add_argument('--kernel',type=Path,default=REPO/'competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean')
    ap.add_argument('--bench-source',type=Path,default=REPO/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/BenchSuite.lean')
    a=ap.parse_args();require(not a.out.exists(),'refusing overwrite of analysis receipt')
    result=analyze(a.result,a.index,a.kernel,a.bench_source)
    a.out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps({'state':'VALIDATED_DIAGNOSTIC','cases':result['case_count'],'out':str(a.out),'sha256':sha(a.out.read_bytes())}))


if __name__=='__main__':main()
