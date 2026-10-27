"""Minimal recovery package; preserves executedv1 and fixed resources. No Git/Lean/CI."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,difflib

H=Path(__file__).resolve().parent;R19=H.parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
V1=R19/'development-route-profile';REC=R19/'development-workers/structural-cost/route-profile/recovery'
C=R/'competitions/floatlib/candidates';SOURCE='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
run=C/'f01-mul-log2-proof1/ci-runs/40425497337';ix=json.loads((run/'original-artifact-hashes.json').read_text())
data=run/ix['directory']/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-route-profile1/route-profile'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
protected=[p for p in V1.rglob('*')if p.is_file()]+[R19/'development-route-audit.py',C/'f01-r19-dev-route-profile1/manifest.json',C/'f01-r19-dev-route-profile1/Kernel.lean']
before={p.relative_to(R).as_posix():sha(p)for p in protected}
for name in('legacy-whole-parser.py','parser-provenance.json','request-original-240.json'):(H/name).write_bytes((V1/name).read_bytes())
for name in('seen-1927003-plan.json','seen-1927005-plan.json'):(H/name).write_bytes((data/name).read_bytes())
old_lean=(data/'RouteLabels.lean').read_text();old_driver=(data/'driver-source.py').read_text()
start=old_lean.index('def routeLabel ');end=old_lean.index('  let route :=',start)
replacement='''def allSmallFrom (c : Bench.Suite.Case) (count role row k : Nat) : Bool :=
  if hk : k < count then
    if Submission.UnderflowZero.small
        (Bench.Suite.float (Bench.Suite.element c k role row)) then
      allSmallFrom c count role row (k + 1)
    else false
  else true
termination_by count - k
decreasing_by omega

def routeLabel (c : Bench.Suite.Case) : String × Bool × Bool :=
  let aSmall := allSmallFrom c (c.batch * c.m * c.n) 0 c.n 0
  let bSmall := allSmallFrom c (c.batch * c.n * c.p) 1 c.p 0
'''
lean=old_lean[:start]+replacement+old_lean[end:]
assert 'Vector.ofFn'not in lean and 'Array.ofFn'not in lean
(H/'RouteLabels.lean').write_bytes(lean.encode())
old_error="require(code==0,'metadata failed');labels="
new_error='require(code==0,f"metadata seed={rec[\'seed\']} failed exit={code}; elapsed={time.monotonic()-started:.3f}s");labels='
assert old_driver.count(old_error)==1
driver=old_driver.replace(old_error,new_error)
(H/'driver.py').write_bytes(driver.encode())
req=json.loads((data/'request.json').read_text())
assert req['maximum_module_seconds']==60 and req['inner']==3 and req['processes_per_plan']==2
req['recovery']=dict(parent_run=40425497337,cause='Second metadata exit124 at remaining60s deadline',
                     metadata_change='Exact same count/role/row, generator and predicate; lazy first-false scan without operand arrays',
                     old_metadata_sha256=sha(data/'RouteLabels.lean'),new_metadata_sha256=sha(H/'RouteLabels.lean'),
                     resources_raised=False,exit0_still_required=True)
(H/'request.json').write_bytes((json.dumps(req,indent=2)+'\n').encode())
hook_old=(R19/'development-route-audit.py').read_text()
hook=hook_old.replace("parent/'development-route-profile'","parent/'development-route-profile-v2'")
hook=hook.replace("=='development-route-audit.py'","=='development-route-audit-v2.py'")
hook=hook.replace("'r19_bound_route_driver'","'r19_bound_route_driver_v2'")
assert "parent/'development-route-profile-v2'"in hook and "=='development-route-audit-v2.py'"in hook
hook_path=R19/'development-route-audit-v2.py';hook_path.write_bytes(hook.encode())
names=('driver.py','RouteLabels.lean','legacy-whole-parser.py','parser-provenance.json','seen-1927003-plan.json','seen-1927005-plan.json','request.json','request-original-240.json')
components=[dict(path=(H/n).relative_to(R).as_posix(),bytes=(H/n).stat().st_size,sha256=sha(H/n))for n in names]
target=C/'f01-r19-dev-route-profile2';target.mkdir(exist_ok=True)
kernel=(data/'Kernel.lean').read_bytes();assert hashlib.sha256(kernel).hexdigest()==SOURCE
(target/'Kernel.lean').write_bytes(kernel)
manifest=dict(candidate=target.name,candidate_file='Kernel.lean',candidate_sha256=SOURCE,candidate_bytes=len(kernel),
              parent='f01-r19-dev-route-profile1',parent_sha256=SOURCE,validation_mode='statement-only',diagnostic_only=True,
              created_at_utc=datetime.now(timezone.utc).isoformat(),helper_audit_module='development-route-audit-v2.py',
              helper_audit_module_sha256=sha(hook_path),helper_audit_source_sha256=SOURCE,
              route_profile_request_sha256=sha(H/'request.json'),route_profile_maximum_seconds=60,components=components,
              proof_status='UNCHANGED_622D_PRIOR_GATES_NOT_REPLAYED_HERE',performance='RECOVERY_DIAGNOSTIC_NOT_RUN',
              full_gate='NOT_RUN_DIAGNOSTIC_ONLY',destruction_scope='PENDING_ACTUAL_BENCHSUITE_C_REVIEW',
              mechanism='Only metadata removes eager A/B construction, keeps exact all-small semantics and strict exit0; original timer binary/plans/flags/budgets unchanged')
(target/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
assert before=={p.relative_to(R).as_posix():sha(p)for p in protected}
(REC/'RouteLabels-v1-v2.diff.txt').write_bytes(''.join(difflib.unified_diff(old_lean.splitlines(keepends=True),lean.splitlines(keepends=True),fromfile='executed-v1',tofile='v2')).encode())
(REC/'driver-v1-v2.diff.txt').write_bytes(''.join(difflib.unified_diff(old_driver.splitlines(keepends=True),driver.splitlines(keepends=True),fromfile='executed-v1',tofile='v2')).encode())
ci=(C/'f01-word-tensors/ci-diagnostics.py').read_text()
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='V2_MINIMAL_LAZY_METADATA_PACKAGED_RUNTIME_NOT_RUN',
            cause_receipt_sha256=sha(REC/'cause.json'),v1_all_files_unchanged=before,
            candidate_sha256=SOURCE,manifest_sha256=sha(target/'manifest.json'),hook_sha256=sha(hook_path),
            components=components,timer_driver_only_change='Error message now includes seed/exit/elapsed; strict nonzero rejection retained',
            constraints=dict(collection_cap=60,inner=120,nested_statement=180,BENCH_INNER=3,BENCH_PAIRS=500000,plans=[1927003,1927005]),
            integration=dict(v2_hook_name_currently_allowlisted="'development-route-audit-v2.py'"in ci,
                             parent_action='Register v2 hook name in ci-diagnostics allowlist if absent; child did not edit global files'),
            runtime=dict(Lean='NOT_RUN',CI='NOT_RUN',resource_increase=False))
(H/'package-receipt.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps({k:record[k]for k in('state','manifest_sha256','hook_sha256','integration')},indent=2))
