"""Freeze an R11 request; original public gate and R10 receipts stay unchanged."""
import argparse
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[5]
OUT = Path(__file__).resolve().parent
D7 = OUT.parent
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--seed', type=int, required=True)
parser.add_argument('--candidates', nargs='+', required=True)
parser.add_argument('--statement-only', nargs='*', default=[])
parser.add_argument('--capture-codegen', nargs='*', default=[])
parser.add_argument('--role', choices=['DISCOVERY','ADDITIONAL_INPUT_DIAGNOSTIC','STATEMENT_DIAGNOSTIC','FROZEN_INDEPENDENT_CONFIRMATION'], default='DISCOVERY')
parser.add_argument('--prior-run', type=int)
parser.add_argument('--cohort', type=Path)
parser.add_argument('--cohort-sha256')
parser.add_argument('--cohort-role', choices=['A','B'])
args = parser.parse_args()
assert len(set(args.candidates)) == len(args.candidates)
assert set(args.statement_only) | set(args.capture_codegen) <= set(args.candidates)
assert not set(args.statement_only) & set(args.capture_codegen)
assert not args.capture_codegen or args.role == 'DISCOVERY'
assert not args.statement_only or args.role == 'STATEMENT_DIAGNOSTIC'
assert args.role != 'FROZEN_INDEPENDENT_CONFIRMATION' or (args.prior_run and not args.capture_codegen and not args.statement_only)
spec = importlib.util.spec_from_file_location('unchanged_adoption_guard', D7/'adoption-guard.py')
guard = importlib.util.module_from_spec(spec); spec.loader.exec_module(guard)
digest = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
read = lambda p: json.loads(p.read_text(encoding='utf-8'))
save = lambda p,x: p.write_text(json.dumps(x,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
state_path=ROOT/'competitions/floatlib/coordination/development-status.json'
state=read(state_path)
assert state['research_round']['id']=='R11-20261023T193125Z', 'Wrong active round; refuse all writes'
if args.role != 'STATEMENT_DIAGNOSTIC':
    assert 'f01-r8-combined-result-guard' in args.candidates, 'A scored comparison needs retained41'
used = []
for p in (ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs').glob('dispatch-*/dispatch.json'):
    entry = read(p)
    if entry.get('state') in ('RUN_IDENTIFIED','DISPATCH_SENT_NO_AUTOMATIC_RETRY'):
        used.append(int(entry['inputs']['seed']))
assert args.seed not in used, 'Seed already dispatched'
rows=[]; files={}
for name in args.candidates:
    assert re.fullmatch(r'f01-[a-z0-9-]+', name)
    folder=ROOT/'competitions/floatlib/candidates'/name
    kernel=folder/'Kernel.lean'; manifest=folder/'manifest.json'
    meta=read(manifest)
    assert digest(kernel)==meta['candidate_sha256'] and kernel.stat().st_size==meta['candidate_bytes']<=256000
    row={'candidate':name,'sha256':digest(kernel),'capture_codegen':name in args.capture_codegen}
    if name in args.statement_only: row['validation_mode']='statement-only'
    rows.append(row)
    for p in [kernel,manifest]:files[p.relative_to(ROOT).as_posix()]={'sha256':digest(p),'bytes':p.stat().st_size}
if args.role != 'STATEMENT_DIAGNOSTIC':
    assert next(r['sha256'] for r in rows if r['candidate']=='f01-r8-combined-result-guard')=='41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
if args.role=='FROZEN_INDEPENDENT_CONFIRMATION':
    assert args.cohort and args.cohort_sha256 and args.cohort_role, 'Explicit frozen cohort and role required'
    verify_spec=importlib.util.spec_from_file_location('r11_request_cohort',OUT/'verify-three-groups.py')
    verifier=importlib.util.module_from_spec(verify_spec);verify_spec.loader.exec_module(verifier)
    cohort=read(args.cohort)
    verifier.verify_freeze(cohort,args.cohort_sha256,args.cohort,guard)
    assert args.prior_run==cohort['groups']['D']['run'], 'Wrong frozen discovery'
    assert args.seed==cohort['groups'][args.cohort_role]['seed'], 'Wrong frozen confirmation seed'
    assert args.candidates==cohort['candidate_orders'][args.cohort_role], 'Wrong frozen measurement order'
    packet=guard.load_run(ROOT,D7,args.prior_run,tuple(args.candidates))
    assert packet['run_conclusion']=='success' and packet['job_conclusion']=='success'
    assert not packet['codegen_present'], 'Use a clean discovery before frozen confirmation'
    assert packet['plan'].get('selection_policy')==guard.SELECTION_POLICY
    assert all(packet['kernel_hashes'][r['candidate']]==r['sha256'] for r in rows), 'Prior exact sources differ'
plan={'seed':args.seed,'official_commit':guard.OFFICIAL,'suite':'suites/public-v2.json','dispatch_state':'READY',
      'publication_state':'AUTHORIZED_R11_PUBLIC_DEVELOPMENT_VALIDATION','candidates':rows,
      'comparison_baseline':'f01-r8-combined-result-guard','profile_parent':False,'profile_current':False,
      'authorization_receipt':(OUT/'round-plan.json').relative_to(ROOT).as_posix(),
      'selection_policy':guard.SELECTION_POLICY,'sample_role':args.role,
      'purpose':'R11 complete-cost architecture experiment; exact source and original public-v2 gates. No official champion or formal admission claim.'}
if args.role=='FROZEN_INDEPENDENT_CONFIRMATION':
    plan['confirmation_candidates']=[{'candidate':r['candidate'],'sha256':r['sha256'],'prior_discovery_run':args.prior_run} for r in rows if r['candidate']!='f01-r8-combined-result-guard']
    plan['cohort']={'path':args.cohort.relative_to(ROOT).as_posix() if args.cohort.is_absolute() else args.cohort.as_posix(),'sha256':args.cohort_sha256,'role':args.cohort_role}
for p in [D7/'public-suite.py',D7/'adoption-guard.py',ROOT/'competitions/floatlib/pins.json',ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci.py']:
    files[p.relative_to(ROOT).as_posix()]={'sha256':digest(p),'bytes':p.stat().st_size}
for p in [OUT/'round-plan.json',Path(__file__).resolve()]:
    files[p.relative_to(ROOT).as_posix()]={'sha256':digest(p),'bytes':p.stat().st_size}
if args.capture_codegen:
    p=D7/'capture-codegen.py'
    files[p.relative_to(ROOT).as_posix()]={'sha256':digest(p),'bytes':p.stat().st_size}
destination=OUT/f'plan-{args.seed}.json'
assert not destination.exists(), 'A frozen request already exists for this seed'
live=ROOT/'competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json'
previous=digest(live)
save(destination,plan);live.write_bytes(destination.read_bytes())
save(OUT/f'freeze-{args.seed}.json',{'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'request_sha256':digest(destination),'previous_live_plan_sha256':previous,'files':files,'unused_seed_checked_against_dispatches':len(used),'role':args.role})
state['research_round'].setdefault('prepared_requests',[]).append({'seed':args.seed,'role':args.role,'plan':destination.relative_to(ROOT).as_posix(),'sha256':digest(destination),'candidates':rows})
state['updated_at_utc']=datetime.now(timezone.utc).isoformat();save(state_path,state)
print(json.dumps({'seed':args.seed,'role':args.role,'candidates':args.candidates,'request_sha256':digest(destination)},ensure_ascii=False))
