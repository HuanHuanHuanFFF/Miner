"""Local synthetic structure/rejection tests; never Linux/kernel evidence."""
from pathlib import Path
import copy,hashlib,importlib.util,json,time,uuid

HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('r13_profile_analysis',HERE/'profile-analyze.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)


def run():
    started=time.monotonic()
    # Reuse only the already published public plan, not any future measurements.
    r=m.REPO/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40080782614'
    ix=m.load(r/'original-artifact-hashes.json');root=r/ix['directory']
    p=next(root.rglob('public-drawn-plan.json'));plan=m.load(p)
    require=m.require;require(m.canonical(plan)==m.PLAN,'public fixture plan hash drift')
    d={'complete':True,'diagnostic_only':True,'full_gate':False,'kernel_sha256':m.SOURCE,'official_commit':m.HEAD,'seed':m.SEED,
        'module_sha256':m.MODULE,'inner':3,'profile_processes':2,'cases':[]}
    for c in plan['cases']:
        rootcat='whole_bmm'if c['kernel']=='bmm'else 'whole_sum'if c['kernel']=='sum'else None
        sweeps=4 if c['timed']else 1;calls=sweeps*(c['batch']if c['kernel']=='sum'else 1)if rootcat else 0
        stages={cat:{'inclusive_ns':0,'exclusive_ns':0,'calls':0}for cat in m.CATEGORIES}
        if rootcat:
            stages[rootcat]={'inclusive_ns':1000,'exclusive_ns':600,'calls':calls}
            stages['compute']={'inclusive_ns':400,'exclusive_ns':400,'calls':calls}
        row={'timed':c['timed'],'best_ns':100 if c['timed']else 0,'checksum':123}
        d['cases'].append({'case':c,'original_whole_row':row,'checksum_matches_original':True,
            'profile_measurements':[{'process':i,'benchmark_row':copy.deepcopy(row),
                'stages_all_checksum_and_timed_sweeps':copy.deepcopy(stages),'expected_pure_kernel_calls':calls}for i in range(2)]})
    require(m.validate_shape(d,plan),'synthetic valid structure rejected')
    rejected=[]
    def bad(name,mutate):
        changed=copy.deepcopy(d);mutate(changed)
        try:m.validate_shape(changed,plan)
        except ValueError:rejected.append(name)
        else:raise AssertionError(name+' accepted')
    bad('incomplete',lambda x:x.update(complete=False))
    bad('wrong exact source',lambda x:x.update(kernel_sha256='0'*64))
    bad('wrong seed',lambda x:x.update(seed=1224017))
    bad('missing case',lambda x:x['cases'].pop())
    bad('duplicate/reordered case',lambda x:x['cases'].__setitem__(1,x['cases'][0]))
    bad('wrong checksum',lambda x:x['cases'][0]['profile_measurements'][0]['benchmark_row'].update(checksum=124))
    bmm=next(i for i,r in enumerate(d['cases'])if r['case']['kernel']=='bmm')
    bad('wrong pure root call count',lambda x:x['cases'][bmm]['profile_measurements'][0]['stages_all_checksum_and_timed_sweeps']['whole_bmm'].update(calls=0))
    bad('missing stage',lambda x:x['cases'][0]['profile_measurements'][0]['stages_all_checksum_and_timed_sweeps'].pop('repair'))
    bad('nested exclusive double count',lambda x:x['cases'][bmm]['profile_measurements'][0]['stages_all_checksum_and_timed_sweeps']['compute'].update(exclusive_ns=399))
    bad('infinite/untyped time',lambda x:x['cases'][0]['original_whole_row'].update(best_ns=float('inf')))
    require(m.word(0,0,0)==0 and m.word(1,0,0)==0x100b05e5,'known SplitMix finalizer vectors')
    require(m.word((1<<64)+1,0,0)==m.word(1,0,0),'UInt64 seed wrap differs')
    c=next(c for c in plan['cases']if c['kernel']=='bmm').copy()
    c.update(mag=0,center=127,spread=0,positive=100,mantBits=0,codebook=0,scaleBlock=0,
        zeroPct=0,subPct=0,specRate=0,batch=2,m=4,n=8,p=10)
    require(m.element(c,0,0,8)==0x3f800000,'ordinary identity word')
    routes=[]
    for expected,shape,extra in [('UnderflowZero',{}, {'center':1}),('Cross',{'p':2},{}),
        ('DirectContinuous',{'n':4},{}),('DirectSmall',{'p':1},{}),('RowStream',{}, {})]:
        v={**c,**shape,**extra};found=m.classify(v)['route'];require(found==expected,'route '+expected);routes.append(found)
    # Hash-index reader is independently fail-closed on byte and path changes.
    base=HERE/('profile-analyze-fixture-'+uuid.uuid4().hex)
    require(base.resolve().parent==HERE.resolve(),'fixture escaped owned directory')
    base.mkdir()
    if True:  # Preserve the tiny fixture so its input and corruption remain reviewable.
        (base/'raw').mkdir();f=base/'raw/a.json';f.write_bytes(b'{}\n')
        ip=base/'index.json';ip.write_text(json.dumps({'directory':'raw','files':{'a.json':{'sha256':m.sha(f.read_bytes()),'bytes':3}}}),encoding='utf-8',newline='\n')
        original=m.Originals(ip);require(original.read(f)==b'{}\n','hash-index positive')
        f.write_bytes(b'[]\n')
        try:original.read(f)
        except ValueError:rejected.append('changed raw artifact bytes')
        else:raise AssertionError('changed raw artifact accepted')
        try:original.read(base/'outside.json')
        except ValueError:rejected.append('path outside raw artifact root')
        else:raise AssertionError('outside path accepted')
    # Entire real-plan route model is lightweight and does not execute Lean/float operations.
    model=[m.classify(c)for c in plan['cases']]
    counts=dict(__import__('collections').Counter(r['route']for r in model))
    result={'state':'PASS','exit_code':0,'elapsed_seconds':time.monotonic()-started,
        'scope':'Synthetic schema and literal source-model tests; no actual R13 profile result or Linux execution.',
        'synthetic_cases':156,'rejected':rejected,'route_fixtures':routes,'source_model_real_plan_route_counts':counts,
        'official_drawn_plan_sha256':m.PLAN,'fixture_plan_file':str(p),'fixture_plan_file_sha256':m.sha(p.read_bytes()),
        'source_sha256':{n:m.sha((HERE/n).read_bytes())for n in ['profile-analyze.py','profile-analyze-test.py']},
        'actual_r13_profile':'NOT_RUN_PENDING_RAW_ARTIFACTS'}
    out=HERE/'profile-analyze-tests.json';out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8',newline='\n')
    print(json.dumps(result))


if __name__=='__main__':run()
