"""Bind exposed plans / original timer interfaces; never execute Lean or a benchmark."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re,time

HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'competitions/floatlib/pins.json').is_file())
C=ROOT/'competitions/floatlib/candidates';start=time.monotonic();sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
SOURCE='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
kernel=C/'f01-r15-dev-packed-b2-1/Kernel.lean';assert sha(kernel)==SOURCE
generator=C/'f01-d6-research/public-delta/benchmark_suite.py'
suite_source=C/'f01-d7-research/round8h-20261024T190259Z/astra-official-source/lean/bench/BenchSuite.lean'
assert sha(generator)=='7198464dfc08f4bb2a3a5e31ce5a105964d1d73ad6b11ee49e682a30c04daf69'
assert sha(suite_source)=='2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f'
sources=[kernel,generator,suite_source]
R13=C/'f01-d7-research/round3h-20261024T112622Z'
for name in ('profile-suite.py','profile-entry.py','profile-coarse-entry.py','profile-whole-multi-entry.py',
             'profile-whole-multi-current.py','profile-coarse-analysis-40094358287-summary.md'):
    sources.append(R13/name)
parser=R13/'profile-whole-multi-current.py'
assert sha(parser)=='8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e'
plans=[];receipts=[]
for run,seed in ((40398675395,1927003),(40407333869,1927005)):
    r=C/f'f01-mul-log2-proof1/ci-runs/{run}'
    ixp=r/'original-artifact-hashes.json';ix=json.loads(ixp.read_text());down=r/ix['directory']
    for name,info in ix['files'].items():
        p=down/name;assert p.resolve().is_relative_to(down.resolve())
        assert p.stat().st_size==info['bytes'] and sha(p)==info['sha256'],name
    assert set(ix['files'])=={p.relative_to(down).as_posix()for p in down.rglob('*')if p.is_file()}
    suite=down/'diagnostics/f01-d7-public-suite/public-suite'
    prov=json.loads((suite/'provenance.json').read_text())
    assert prov['seed']==seed and prov['rounds']==25 and prov['pairs']==500000
    assert prov['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
    assert prov['official_generator_sha256']==sha(generator)
    p=suite/'public-drawn-plan.json';plan=json.loads(p.read_text())
    assert len(plan['cases'])==len({c['name']for c in plan['cases']})==156
    v=json.loads((suite/'f01-r15-dev-packed-b2-1-verdict.json').read_text())
    assert v['passed']and v['stage']=='score'and v['seed']==seed and len(v['rounds'])==25
    assert len(v['classes'])==26 and all(isinstance(row,list)and len(row)==2 for row in v['rounds'])
    assert sha(suite/'inputs/f01-r15-dev-packed-b2-1/Kernel.lean')==SOURCE
    rows=[]
    for name in ix['files']:
        if name.endswith('.log'):
            for line in (down/name).read_text(errors='replace').splitlines():
                if re.fullmatch(r'\S+ (?:true|false) \d+ \d+',line):rows.append(dict(path=name,line=line))
    assert not rows,'raw case rows unexpectedly available: use them before building another diagnostic'
    target=HERE/f'seen-{seed}-plan.json';target.write_bytes(p.read_bytes())
    bmm=[c for c in plan['cases']if c['kernel']=='bmm']
    plans.append(dict(seed=seed,path=target.name,sha256=sha(target),original_path=p.relative_to(ROOT).as_posix(),
                      original_run=run,case_count=156,BMM_cases=len(bmm),timed_BMM_cases=sum(c['timed']for c in bmm),
                      metadata_input_elements=sum(c['batch']*(c['m']*c['n']+c['n']*c['p'])for c in bmm)))
    receipts.append(dict(run=run,seed=seed,index_sha256=sha(ixp),original_files_verified=len(ix['files']),
                         provenance_sha256=sha(suite/'provenance.json'),B2_verdict_sha256=sha(suite/'f01-r15-dev-packed-b2-1-verdict.json'),
                         verdict_case_rows=False,classes=26,rounds_shape='25x[inc_total_ns,sub_total_ns]',raw_timer_rows_found=0))
oldr=C/'f01-mul-log2-proof1/ci-runs/40099316795';oldix=json.loads((oldr/'original-artifact-hashes.json').read_text())
oldp=oldr/oldix['directory']/'diagnostics/f01-d13-cost-profile/cost-profile/measurement/profile-whole-multi-result.json'
oldrel=oldp.relative_to(oldr/oldix['directory']).as_posix();assert sha(oldp)==oldix['files'][oldrel]['sha256']
old=json.loads(oldp.read_text());assert old['complete']and old['full_gate']is False
assert old['kernel_sha256']=='df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
assert len(old['executions'])==6 and old['build_identities']['before']==old['build_identities']['after']
request=dict(schema_version=1,diagnostic_only=True,kernel_sha256=SOURCE,
             official_commit='4b7e83841cc0c32c6529f533923c73d33b5ecf97',
             suite_sha256='a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a',
             generator_sha256=sha(generator),BenchSuite_lean_sha256=sha(suite_source),
             allowed_seen_seeds=[1927003,1927005],plans=plans,inner=3,processes_per_plan=2,
             maximum_module_seconds=240,scope='Original unchanged benchFull raw whole-case timers; separate pre-timer metadata process; no score or stage instrumentation')
(HERE/'request.json').write_text(json.dumps(request,indent=2)+'\n',encoding='utf-8')
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='ORIGINAL_CASE_TIMER_INTERFACE_CONFIRMED_NEW_ROUTE_TIMES_UNKNOWN',
            sources=[dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(p),bytes=p.stat().st_size)for p in sources],
            seen_plan_receipts=receipts,request_sha256=sha(HERE/'request.json'),
            old_whole_interface=dict(run=40099316795,result_sha256=sha(oldp),elapsed_seconds=old['elapsed_seconds'],
                                     processes=6,source_sha256=old['kernel_sha256'],immutable_build=True),
            boundaries=dict(printed_ns='Whole timed pass, fastest of3 after checksum/warmup; not process wall time or ns/work',
                            input_generation='Outside original timer',candidate_preparation='Inside public bmm call',
                            output_traversal='Inside timed pass',candidate_result_destruction='Requires saved actual BenchSuite C/lifetime check; scalar sink does not retain vector',
                            observer='Original benchmark timer only; metadata route labeling occurs in another process',
                            score='NOT_RUN_NOT_RECONSTRUCTIBLE_FROM_DIAGNOSTIC_2_PROCESSES'),
            old_limit='Fine/coarse probe disturbance and df5c route/source differences prohibit transferring old stage/route shares to622d',
            new_runtime='NOT_RUN',elapsed_seconds=time.monotonic()-start)
assert time.monotonic()-start<5
(HERE/'input-audit.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(dict(state=record['state'],plans=plans,old_whole_seconds=old['elapsed_seconds'],seconds=record['elapsed_seconds']),indent=2))
