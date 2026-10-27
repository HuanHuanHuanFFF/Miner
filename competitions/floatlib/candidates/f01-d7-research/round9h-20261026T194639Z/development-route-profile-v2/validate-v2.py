"""Static/package checks and finite all-small equivalence; no Lean/CI."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,importlib.util,json

H=Path(__file__).resolve().parent;R19=H.parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
candidate=R/'competitions/floatlib/candidates/f01-r19-dev-route-profile2';manifest=json.loads((candidate/'manifest.json').read_text())
hook=R19/'development-route-audit-v2.py'
assert sha(candidate/'Kernel.lean')==manifest['candidate_sha256']=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert sha(hook)==manifest['helper_audit_module_sha256']
for row in manifest['components']:
    p=(R/row['path']).resolve();assert p.is_relative_to(H.resolve())and sha(p)==row['sha256']and p.stat().st_size==row['bytes']
    assert b'\r\n'not in p.read_bytes()
for path in(hook,H/'driver.py',H/'pack-v2.py'):ast.parse(path.read_text())
spec=importlib.util.spec_from_file_location('r19_route_v2_validation',hook);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
class FakeGate:pass
stages=m.stages(FakeGate(),candidate/'Kernel.lean',H/'not-executed-output',manifest)
assert [n for n,_ in stages]==['route-collection']
receipt=json.loads((H/'package-receipt.json').read_text())
drift=[dict(path=name,packaging_sha256=value,current_sha256=sha(R/name))
       for name,value in receipt['v1_all_files_unchanged'].items() if sha(R/name)!=value]
req=json.loads((H/'request.json').read_text());old=json.loads((R19/'development-route-profile/request.json').read_text())
for key in('maximum_module_seconds','inner','processes_per_plan','allowed_seen_seeds','plans','timeout_context'):
    assert req[key]==old[key]
assert req['maximum_module_seconds']==60
source=(H/'RouteLabels.lean').read_text()
assert 'if hk : k < count then'in source and 'else false'in source and 'else true'in source
assert 'allSmallFrom c count role row (k + 1)'in source and 'termination_by count - k'in source
assert 'Bench.Suite.element c k role row'in source and 'Submission.UnderflowZero.small'in source
assert 'Vector.ofFn'not in source and 'Array.ofFn'not in source
old_lean=(R19/'development-route-profile/RouteLabels.lean').read_text()
assert source[source.index('  let route :='):]==old_lean[old_lean.index('  let route :='):]
assert 'allSmallFrom c (c.batch * c.m * c.n) 0 c.n 0'in source
assert 'allSmallFrom c (c.batch * c.n * c.p) 1 c.p 0'in source
checked=0
def lazy(bits):
    for b in bits:
        if not b:return False
    return True
for n in range(13):
    for mask in range(1<<n):
        bits=[bool(mask&(1<<i))for i in range(n)]
        assert all(bits)==lazy(bits);checked+=1
driver=(H/'driver.py').read_text()
assert driver.index('require(code==0,f"metadata seed=')<driver.index('labels=parse_labels(log,plan)')
assert "'BENCH_PAIRS':'500000','BENCH_INNER':'3'"in driver
assert 'request[\'maximum_module_seconds\']==60'in driver and 'remaining(90)'in driver
result=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='V2_STATIC_PACKAGE_AND_LAZY_ALL_EQUIVALENCE_PASS_RUNTIME_NOT_RUN',
            kernel_sha256=sha(candidate/'Kernel.lean'),manifest_sha256=sha(candidate/'manifest.json'),hook_sha256=sha(hook),
            components=8,stages=[n for n,_ in stages],finite_boolean_arrays=checked,
            v1_unchanged_at_packaging=True,v1_drift_since_packaging=drift,inputs_and_timer_flags_unchanged=True,resource_caps_unchanged=True,
            strict_exit0_before_label_parse=True,
            limits='Finite predicate test is algorithmic plumbing only; actual Lean metadata and same60s CI completion NOT_RUN')
(H/'validation-receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
print(json.dumps(result,indent=2))
