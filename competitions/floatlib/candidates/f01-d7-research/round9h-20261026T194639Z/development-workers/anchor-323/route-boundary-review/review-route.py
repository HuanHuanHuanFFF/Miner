"""Independent raw-ns/label arithmetic and retained-C boundary review; no Lean."""
from collections import Counter
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40425497337'
DOWNLOAD=RUN/'download-7864aa0826ad4b229a60800f85179f67'
DIAG=DOWNLOAD/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-route-profile1'
DATA=DIAG/'route-profile'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
read=lambda p:json.loads(Path(p).read_bytes())
encode=lambda x:(json.dumps(x,ensure_ascii=False,indent=2)+'\n').encode()


def require(ok,message):
    if not ok:raise ValueError(message)


def function(text,name):
    pattern=r'^(?:LEAN_EXPORT|static) [^;\n]*?\b'+re.escape(name)+r'\([^;\n]*\)\s*\{'
    m=re.search(pattern,text,re.M);require(m is not None,'Missing C function '+name)
    i=text.find('{',m.start());depth=0
    while i<len(text):
        if text[i] in ('"',"'"):
            quote=text[i];i+=1
            while i<len(text) and text[i]!=quote:i+=2 if text[i]=='\\' else 1
        elif text[i]=='{':depth+=1
        elif text[i]=='}':
            depth-=1
            if depth==0:return dict(start_line=text[:m.start()].count('\n')+1,end_line=text[:i+1].count('\n')+1,text=text[m.start():i+1])
        i+=1
    raise ValueError('Unclosed C function')


def raw_rows(path,plan):
    expected={c['name']:c for c in plan['cases']};rows={}
    for line in path.read_text('utf-8').splitlines():
        m=re.fullmatch(r'(\S+) (true|false) ([0-9]+) ([0-9]+)',line)
        if not m:continue
        name,timed,ns,checksum=m.groups();require(name in expected and name not in rows,'Unexpected/duplicate row')
        flag=timed=='true';require(flag==expected[name]['timed'],'Timed flag differs')
        require(int(ns)>0 if flag else int(ns)==0,'Invalid ns')
        rows[name]={'timed':flag,'best_ns':int(ns),'checksum':int(checksum)}
    require(set(rows)==set(expected) and len(rows)==156,'Raw156-case coverage differs')
    require('ROUTE19 ' not in path.read_text('utf-8'),'Metadata observer in timing binary')
    return rows


def main():
    index=read(RUN/'original-artifact-hashes.json');require(len(index['files'])==138,'Wrong original artifact count')
    inputs=[]
    def bind(path):
        path=Path(path);item=index['files'][path.relative_to(DOWNLOAD).as_posix()]
        require(sha(path)==item['sha256'] and path.stat().st_size==item['bytes'],'Original bytes changed '+str(path))
        inputs.append({'path':path.relative_to(ROOT).as_posix(),'bytes':path.stat().st_size,'sha256':sha(path)})
    for name in ['request.json','config.json','build-identity-before.json','driver-source.py','Kernel.lean','RouteLabels.lean',
                 'BenchSuite_C.c','MainFull_C.c','Submission_C.c','seen-1927003-plan.json','labels-1927003.log','labels-1927003.json',
                 'whole-1927003-0.log','whole-1927003-1.log','rows-1927003-0.json','rows-1927003-1.json','result-1927003.json','partial-progress.json','error.json']:
        bind(DATA/name)
    bind(DIAG/'route-audit.json');bind(DIAG/'native-assembly-index.json')
    plan=read(DATA/'seen-1927003-plan.json');saved=read(DATA/'result-1927003.json');require(sha(DATA/'seen-1927003-plan.json')==saved['plan_sha256'],'Plan binding differs')
    rows=[raw_rows(DATA/f'whole-1927003-{i}.log',plan) for i in range(2)]
    require(rows==saved['complete_case_rows'] and all(rows[0][n]['checksum']==rows[1][n]['checksum'] for n in rows[0]),'Raw rows/checksums differ')
    require(all(rows[i]==read(DATA/f'rows-1927003-{i}.json') for i in range(2)),'Cached row serialization differs')
    bmm={c['name']:c for c in plan['cases'] if c['kernel']=='bmm'};labels={}
    for line in (DATA/'labels-1927003.log').read_text().splitlines():
        m=re.fullmatch(r'ROUTE19 (\S+) (\S+) (true|false) (true|false)',line)
        if not m:continue
        name,route,a,b=m.groups();require(name in bmm and name not in labels,'Bad metadata label')
        labels[name]={'route':route,'aSmall':a=='true','bSmall':b=='true'}
    require(set(labels)==set(bmm) and len(labels)==35,'BMM metadata coverage differs')
    require(labels==read(DATA/'labels-1927003.json')==saved['labels'],'Raw metadata differs')
    timed=[c for c in plan['cases'] if c['timed']];require(len(timed)==152,'Wrong timed coverage')
    sums=[]
    for r in rows:
        operations={op:sum(r[c['name']]['best_ns'] for c in timed if c['kernel']==op) for op in ('add','mul','sum','bmm')}
        whole=sum(r[c['name']]['best_ns'] for c in timed);require(sum(operations.values())==whole,'Operation conservation failed')
        routes={tag:sum(r[c['name']]['best_ns'] for c in timed if c['kernel']=='bmm' and labels[c['name']]['route']==tag) for tag in sorted({v['route'] for v in labels.values()})}
        require(sum(routes.values())==operations['bmm'],'Route conservation failed')
        sums.append({'whole_ns':whole,'operations_ns':operations,'routes_ns':routes,
                     'routes':{k:{'ns':v,'BMM_share':v/operations['bmm'],'whole_share':v/whole} for k,v in routes.items()}})
    # Use integer twice-mean accounting for exact conservation, not mean percentages.
    whole2=sum(s['whole_ns'] for s in sums);bmm2=sum(s['operations_ns']['bmm'] for s in sums)
    mean_routes={k:{'mean_ns':sum(s['routes_ns'][k] for s in sums)/2,
        'BMM_share':sum(s['routes_ns'][k] for s in sums)/bmm2,
        'whole_share':sum(s['routes_ns'][k] for s in sums)/whole2} for k in sums[0]['routes_ns']}
    require(sum(2*x['mean_ns'] for x in mean_routes.values())==bmm2,'Mean route conservation failed')
    for k,v in mean_routes.items():
        old=saved['timing']['mean_of_case_timers']['routes'][k]
        require(v['mean_ns']==old['ns'] and v['BMM_share']==old['BMM_share'] and v['whole_share']==old['whole_share'],'Independent arithmetic differs '+k)
    dc=[]
    for c in timed:
        if c['kernel']=='bmm' and labels[c['name']]['route']=='DirectContinuous':
            ns=[r[c['name']]['best_ns'] for r in rows]
            dc.append({'name':c['name'],'shape':{k:c[k] for k in ('batch','m','n','p','work')},
                'output_elements':c['batch']*c['m']*c['p'],'process_ns':ns,'mean_ns':sum(ns)/2,
                'whole_share':sum(ns)/whole2,'BMM_share':sum(ns)/bmm2,'process1_over_process0':ns[1]/ns[0]})
    dc.sort(key=lambda x:-x['mean_ns'])
    ctext=(DATA/'BenchSuite_C.c').read_text('utf-8')
    names=['lp_competition_Bench_Suite_runBmm___lam__2','lp_competition_Bench_Suite_runBmm___lam__2___boxed',
        'lp_competition_Bench_Suite_runBmm','lp_competition_Bench_Suite_measure',
        'lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg']
    funcs={n:function(ctext,n) for n in names};passbody=funcs[names[0]]['text'];timer=funcs[names[-1]]['text']
    require(passbody.index('lean_apply_6(')<passbody.index('Array_forIn_')<passbody.index('lean_dec_ref(v___x_2501_)')<passbody.index('return v___x_2504_'),'Output reference lifetime differs')
    clocks=[m.start() for m in re.finditer('lean_io_mono_nanos_now\\(',timer)];require(len(clocks)==2,'Timer clocks differ')
    require(clocks[0]<timer.index('lean_apply_2(v_pass_')<timer.index('lean_dec_ref_known(v___x_2211_')<clocks[1],'Pass/IO-result cleanup not bracketed by clock')
    construct=funcs['lp_competition_Bench_Suite_runBmm']['text'];require(construct.index('l_Array_ofFn')<construct.index('Bench_Suite_measure('),'Input generation boundary differs')
    measure=funcs['lp_competition_Bench_Suite_measure']['text']
    require(measure.index('lean_apply_2(v_pass_')<measure.index('Bench_Suite_measure_spec__0___redArg('),'Warmup not before timed loop')
    identity=read(DATA/'build-identity-before.json')
    for key in ('BenchSuite_C','MainFull_C','Submission_C'):require(sha(DATA/(key+'.c'))==identity[key]['sha256'],'C differs from original build identity')
    require(sha(DATA/'Kernel.lean')=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58','Wrong B2 source')
    cmain=(DATA/'MainFull_C.c').read_text();require('m_fun = (void*)lp_competition_Submission_bmm' in cmain and 'lp_competition_Bench_Suite_run(' in cmain,'Original BMM caller differs')
    progress=read(DATA/'partial-progress.json')['current'];require(progress['seed']==1927005 and progress['exit_code']==124,'Second seen metadata failure differs')
    bodymeta={n:{'start_line':v['start_line'],'end_line':v['end_line']} for n,v in funcs.items()}
    result={'status':'VERIFIED_FIRST_SEEN_PLAN_RAW_NS_AND_GENERATED_C_BOUNDARY','verified_at_utc':datetime.now(timezone.utc).isoformat(),
        'run':40425497337,'source_commit':index['artifact']['workflow_run']['head_sha'],'seed':1927003,
        'plan_sha256':sha(DATA/'seen-1927003-plan.json'),'case_count':156,'timed_case_count':152,'timed_BMM_cases':34,
        'route_timed_case_counts':dict(Counter(labels[c['name']]['route'] for c in timed if c['kernel']=='bmm')),
        'raw_processes':sums,'mean':{'whole_ns':whole2/2,'BMM_ns':bmm2/2,'BMM_whole_share':bmm2/whole2,'routes':mean_routes},
        'process1_over_process0':{'whole':sums[1]['whole_ns']/sums[0]['whole_ns'],'BMM':sums[1]['operations_ns']['bmm']/sums[0]['operations_ns']['bmm'],
            'routes':{k:sums[1]['routes_ns'][k]/sums[0]['routes_ns'][k] for k in sums[0]['routes_ns']}},
        'conservation_exact':True,'shares_are_ratio_of_mean_case_ns_not_mean_of_percentages':True,'DC_cases_by_mean_ns':dc,
        'generated_C':{'functions':bodymeta,'output_local_ref_drop_before_pass_return':True,'stop_clock_after_pass_and_IO_wrapper_drop':True,
            'input_generation_before_measure':True,'scope':'C/source ownership boundary verified; actual final free conditional on reference ownership; exact native schedule/cycles not verified.'},
        'timer_scope':'Original best-of3 whole-case pass: full kernel route/guards/preparation/allocation + checksum output traversal + local output ref drop + pass/IO return overhead. Input generation, untimed warmup, final retained input-closure destruction and printing outside the measured pass.',
        'native_limit':'BenchSuite object/binary hashes are original metadata attestation; raw object/LLVM IR/BenchSuite ASM not retained here. No independent native cleanup or cycle-cost claim.',
        'build_identity_before':identity,'post_first_plan_identity':'Inferred from successful original driver assertions after both processes; no independent raw object rehash possible',
        'second_seen_plan_status':'METADATA_TIMEOUT_124_NO_COMPLETE_ROUTE_TIMINGS','cross_seed_stability':'UNKNOWN','score_or_adoption':False,
        'budget_inference':{'DC_assigned_whole_cost_share_this_plan':mean_routes['DirectContinuous']['whole_share'],
            'all_BMM_assigned_whole_share_this_plan':bmm2/whole2,
            'conditional_fraction_of_all_BMM_cost_to_remove_for_10percent_whole':0.10/(bmm2/whole2),
            'scope':'Conditional accounting ceiling only if other cases unchanged; includes irreducible benchmark overhead. Not a universal speed limit or gain prediction.',
            'next_route':'Prefer shared BMM output/construction/lifetime or batch/row costs over DC-only threshold tuning; keep long-inner counter-cases. No threshold grid proposed.'},
        'reviewed_original_files_rehashed':len(inputs),'inputs':inputs}
    (HERE/'review.json').write_bytes(encode(result))
    (HERE/'boundary-C-excerpts.txt').write_text('\n\n'.join(f'// BenchSuite_C.c:{v["start_line"]}\n{v["text"]}' for v in funcs.values())+'\n',encoding='utf-8')
    print(json.dumps({'status':result['status'],'mean_whole_ns':whole2/2,'mean_BMM_ns':bmm2/2,'BMM_whole_share':bmm2/whole2,
        'routes':mean_routes,'process_drift':result['process1_over_process0']['whole'],'conservation':True,'DC_cases':len(dc)}))


if __name__=='__main__':main()
