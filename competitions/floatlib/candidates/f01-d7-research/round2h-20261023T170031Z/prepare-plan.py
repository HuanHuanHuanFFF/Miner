from pathlib import Path
import argparse, datetime, hashlib, importlib.util, json, random, statistics

ap=argparse.ArgumentParser()
ap.add_argument('--candidate',required=True)
ap.add_argument('--sha256',required=True)
ap.add_argument('--seed',type=int,required=True)
prior=ap.add_mutually_exclusive_group()
prior.add_argument('--confirmation-run',type=int)
prior.add_argument('--extra-input-of',type=int,help='Another input group even after a negative performance screen; never an adoption confirmation')
a=ap.parse_args()
root=Path(__file__).resolve().parents[5]
d7=root/'competitions/floatlib/candidates/f01-d7-research'
out=Path(__file__).resolve().parent
read=lambda p:json.loads(p.read_bytes())
save=lambda p,x:p.write_text(json.dumps(x,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
digest=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
sp=root/'competitions/floatlib/coordination/development-status.json';state=read(sp)
baseline=Path(state['kernel']).parent.name
assert baseline=='f01-r8-combined-result-guard' and state['kernel_sha256']=='41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
candidate_path=root/'competitions/floatlib/candidates'/a.candidate/'Kernel.lean'
assert digest(candidate_path)==a.sha256 and candidate_path.stat().st_size<=256000
spec=importlib.util.spec_from_file_location('g',d7/'adoption-guard.py');g=importlib.util.module_from_spec(spec);spec.loader.exec_module(g)
used=[]
for p in (root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs').glob('dispatch-*/dispatch.json'):
    x=read(p)
    if x.get('state') in ('RUN_IDENTIFIED','DISPATCH_SENT_NO_AUTOMATIC_RETRY'):used.append(int(x['inputs']['seed']))
assert a.seed not in used
entries=[{'candidate':baseline,'sha256':state['kernel_sha256'],'capture_codegen':False},{'candidate':a.candidate,'sha256':a.sha256,'capture_codegen':False}]
plan={'seed':a.seed,'official_commit':g.OFFICIAL,'suite':'suites/public-v2.json','dispatch_state':'READY','publication_state':'AUTHORIZED_CONTINUED_RESEARCH','candidates':entries,'comparison_baseline':baseline,'profile_parent':False,'profile_current':False,'authorization_receipt':(out/'round-plan.json').relative_to(root).as_posix(),'selection_policy':g.SELECTION_POLICY,'sample_role':'DISCOVERY','purpose':'Exact BMM-only candidate versus retained41, full unchanged gates on same runner; no inherited performance.'}
prior_run=a.confirmation_run or a.extra_input_of
if prior_run:
    packet=g.load_run(root,d7,prior_run,(a.candidate,baseline))
    assert packet['kernel_hashes'][a.candidate]==a.sha256 and packet['plan']['selection_policy']==g.SELECTION_POLICY
    g.require(packet['run_conclusion']=='success' and packet['job_conclusion']=='success','Prior run/job must have completed successfully')
    g.require(packet['kernel_hashes'][baseline]==state['kernel_sha256'],'Prior baseline hash changed')
    g.require(not packet['codegen_present'] and not packet['plan'].get('profile_parent') and not packet['plan'].get('profile_current') and not any(r.get('capture_codegen') for r in packet['plan']['candidates']),'Prior sample had observers')
    for name in (a.candidate,baseline):
        v=packet['verdicts'][name]
        g.require(v['passed'] is True and v['mode']=='gate' and v['stage']=='score' and len(v['rounds'])==25,'Prior sample not a complete gate')
        g.require(v['seed']==packet['seed']==packet['plan']['seed'],'Prior seed mismatch')
    relative=packet['verdicts'][a.candidate]['ratio']/packet['verdicts'][baseline]['ratio']
    ratios=[[sub/inc for inc,sub in packet['verdicts'][n]['rounds']] for n in (a.candidate,baseline)]
    rng=random.Random(90423);gains=[]
    for _ in range(2000):
        medians=[statistics.median(values[rng.randrange(25)] for _ in range(25)) for values in ratios]
        gains.append(1-medians[0]/medians[1])
    gains.sort();k=.05*1999;lo=int(k);p05=gains[lo]+(gains[lo+1]-gains[lo])*(k-lo)
    screen={'run':prior_run,'candidate':a.candidate,'sha256':a.sha256,'relative_normalized_ratio':relative,'gain_p05':p05,'policy':g.SELECTION_POLICY,'evidence':packet['evidence'],'role':'Discovery screen only; not independent confirmation or formal admission'}
    save(out/f'discovery-{packet["seed"]}-screen.json',screen)
    if a.confirmation_run:
        assert relative<=.97 and p05>0,'No pre-frozen local selection signal; do not dispatch confirmation'
        plan.update(candidates=list(reversed(entries)),sample_role='FROZEN_INDEPENDENT_CONFIRMATION',confirmation_candidates=[{'candidate':a.candidate,'sha256':a.sha256,'prior_discovery_run':a.confirmation_run}],purpose='Frozen exact BMM source and retained41, unused seed/new hosted runner, reverse candidate order. All observers disabled.')
    else:
        plan.update(candidates=list(reversed(entries)),sample_role='ADDITIONAL_INPUT_DIAGNOSTIC',additional_input_candidates=[{'candidate':a.candidate,'sha256':a.sha256,'prior_discovery_run':prior_run}],purpose='User-requested additional distinct input group for the exact source, retaining negative discovery. This role cannot satisfy independent adoption confirmation; thresholds unchanged.')
live=root/'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json';old=live.read_bytes()
role='confirmation' if a.confirmation_run else ('extra-input' if a.extra_input_of else 'discovery')
save(live,plan);(out/f'{role}-{a.seed}-plan.json').write_bytes(live.read_bytes())
save(out/f'{role}-{a.seed}-freeze.json',{'recorded_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'before_live_request_sha256':hashlib.sha256(old).hexdigest(),'new_request_sha256':digest(live),'unused_seed_checked_against_dispatches':len(used),'files':{str(p.relative_to(root)).replace('\\','/'):{'sha256':digest(p),'bytes':p.stat().st_size} for p in [candidate_path,candidate_path.with_name('manifest.json'),root/state['kernel'],d7/'public-suite.py',d7/'adoption-guard.py',root/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci.py',root/'competitions/floatlib/pins.json']},'role':plan['sample_role']})
state['research_round'].update(state=f'PREPARED_{role.upper()}{a.seed}',candidate=a.candidate,candidate_sha256=a.sha256,plan=(out/f'{role}-{a.seed}-plan.json').relative_to(root).as_posix())
save(sp,state)
print(json.dumps({'role':role,'seed':a.seed,'candidate':a.candidate,'sha256':a.sha256,'plan_sha256':digest(live)}))
