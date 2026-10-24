"""Synthetic coarse-reader tests plus explicit rejection of actual fine data."""
from pathlib import Path
import copy,hashlib,importlib.util,json,time
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r13_coarse_reader',HERE/'profile-coarse-analyze.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)


def run():
    started=time.monotonic()
    rawroot=m.REPO/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40092014611'
    ix=m.load(rawroot/'original-artifact-hashes.json');root=rawroot/ix['directory']
    fine=next(root.rglob('profile-r13-result.json'));plan=m.load(fine.with_name('profile-r13-full-public-plan.json'))
    d={'complete':True,'diagnostic_only':True,'full_gate':False,'kernel_sha256':m.SOURCE,'official_commit':m.HEAD,'seed':m.SEED,
        'module_sha256':m.MODULE,'inner':3,'profile_processes':2,'cases':[]}
    routecat={'Cross':'cross_scope','RowStream':'rowstream_scope','DirectContinuous':'direct_continuous',
        'DirectSmall':'direct_small','UnderflowZero':'underflow_fill'}
    for c in plan['cases']:
        route=m.classify(c)['route'];rootcat='whole_bmm'if c['kernel']=='bmm'else 'whole_sum'if c['kernel']=='sum'else None
        sweeps=4 if c['timed']else 1;calls=sweeps*(c['batch']if c['kernel']=='sum'else 1)if rootcat else 0
        stages={cat:{'inclusive_ns':0,'exclusive_ns':0,'calls':0}for cat in m.CATEGORIES}
        if rootcat:stages[rootcat]={'inclusive_ns':1000,'exclusive_ns':1000,'calls':calls}
        if c['kernel']=='bmm':
            stages[rootcat]['exclusive_ns']=600;cat=routecat[route]
            stages[cat]={'inclusive_ns':400,'exclusive_ns':400,'calls':calls}
            if route=='Cross':
                stages[cat]['exclusive_ns']=200;stages['cross_words']={'inclusive_ns':200,'exclusive_ns':200,'calls':calls}
            elif route=='RowStream':
                stages[cat]['exclusive_ns']=200
                for inner in ('rowstream_amap','rowstream_bpack'):stages[inner]={'inclusive_ns':100,'exclusive_ns':100,'calls':calls}
        anchor={'timed':c['timed'],'best_ns':100 if c['timed']else 0,'checksum':123}
        d['cases'].append({'case':c,'original_whole_row':anchor,'checksum_matches_original':True,
            'profile_measurements':[{'process':i,'benchmark_row':{**anchor,'best_ns':110+10*i if c['timed']else 0},
                'stages_all_checksum_and_timed_sweeps':copy.deepcopy(stages),'expected_pure_kernel_calls':calls}for i in range(2)]})
    assert m.validate_shape(d,plan)
    summary=m.summarize(d);assert len(summary['cases'])==156
    assert summary['groups']['route:RowStream']['timed']['profile_vs_original_context_and_instrumentation_ratio']=={'sum_ratio':1.15,'case_median':1.15,'case_min':1.15,'case_max':1.15}
    cross=next(c for c in summary['cases']if c['route']['route']=='Cross')
    assert cross['coarse_intervals']['cross_words_prepare_compute_repair']==200
    assert cross['coarse_intervals']['cross_core_exclusive_output_and_cleanup']==200
    rejected=[]
    def reject(name,fn):
        try:fn()
        except ValueError:rejected.append(name)
        else:raise AssertionError(name+' accepted')
    def bad(name,mutate):
        x=copy.deepcopy(d);mutate(x);reject(name,lambda:m.validate_shape(x,plan))
    bad('incomplete',lambda x:x.update(complete=False))
    bad('wrong exact source',lambda x:x.update(kernel_sha256='0'*64))
    bad('wrong seed',lambda x:x.update(seed=1324004))
    bad('missing case',lambda x:x['cases'].pop())
    bad('duplicate/reordered case',lambda x:x['cases'].__setitem__(1,x['cases'][0]))
    bad('wrong checksum',lambda x:x['cases'][0]['profile_measurements'][0]['benchmark_row'].update(checksum=124))
    bmm=next(i for i,r in enumerate(d['cases'])if r['case']['kernel']=='bmm')
    bad('wrong pure root call count',lambda x:x['cases'][bmm]['profile_measurements'][0]['stages_all_checksum_and_timed_sweeps']['whole_bmm'].update(calls=0))
    bad('missing stage',lambda x:x['cases'][0]['profile_measurements'][0]['stages_all_checksum_and_timed_sweeps'].pop('cross_words'))
    bad('exclusive double count',lambda x:x['cases'][bmm]['profile_measurements'][0]['stages_all_checksum_and_timed_sweeps']['whole_bmm'].update(exclusive_ns=1001))
    bad('per-packet/element probe',lambda x:x['cases'][bmm]['profile_measurements'][0]['stages_all_checksum_and_timed_sweeps'][routecat[m.classify(x['cases'][bmm]['case'])['route']]].update(calls=5))
    reject('actual fine producer identity',lambda:m.validate_shape(m.load(fine),plan))
    reject('actual fine artifact filename',lambda:m.analyze(fine,rawroot/'original-artifact-hashes.json',Path('unused'),Path('unused')))
    stages=d['cases'][bmm]['profile_measurements'][0]['stages_all_checksum_and_timed_sweeps']
    log='\n'.join(f"FC13 cat={j} inclusive_ns={stages[c]['inclusive_ns']} exclusive_ns={stages[c]['exclusive_ns']} calls={stages[c]['calls']}"for j,c in enumerate(m.CATEGORIES))+'\nFC13_END depth=0\n'
    assert m.parse_stages(log)==stages
    reject('fine marker protocol',lambda:m.parse_stages(log.replace('FC13','FL13')))
    reject('unbalanced timer stack',lambda:m.parse_stages(log.replace('depth=0','depth=1')))
    reject('unknown stage index',lambda:m.parse_stages(log.replace('cat=9 ','cat=10 ')))
    result={'state':'PASS','exit_code':0,'elapsed_seconds':time.monotonic()-started,'synthetic_cases':156,
        'rejected':rejected,'coarse_ratio_fixture':1.15,'cross_words_and_exclusive_fixture_ns':200,
        'actual_fine_result_sha256':hashlib.sha256(fine.read_bytes()).hexdigest(),
        'source_sha256':{n:hashlib.sha256((HERE/n).read_bytes()).hexdigest()for n in ['profile-coarse-analyze.py','profile-coarse-analyze-build.py','profile-coarse-analyze-test.py']},
        'actual_coarse_data':'NOT_RUN_PENDING_RUN40094358287_ARTIFACTS'}
    (HERE/'profile-coarse-analyze-tests.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(result))


if __name__=='__main__':run()
