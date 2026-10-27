"""Light interface/parser checks only. Does not run the drafted Linux entry or Lean."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,importlib.util,json

H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
def module(name,path):
    s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
for name in ('route-profile-driver.py','route-profile-entry.py','audit_design_inputs.py'):
    ast.parse((H/name).read_text())
d=module('r19_route_draft_static',H/'route-profile-driver.py')
old_path=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-current.py'
assert sha(old_path)=='8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e'
old=module('r19_route_old_parser',old_path)
run=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40099316795'
ix=json.loads((run/'original-artifact-hashes.json').read_text());folder=run/ix['directory']
result_path=folder/'diagnostics/f01-d13-cost-profile/cost-profile/measurement/profile-whole-multi-result.json'
result=json.loads(result_path.read_text());first=result['seeds'][0];seed=first['seed']
base=result_path.parent
log=base/f'profile-whole-multi-seed-{seed}-process-0.log'
assert sha(log)==ix['files'][log.relative_to(folder).as_posix()]['sha256']
assert old.bench_rows(log.read_text(),first['plan'])==first['processes'][0]['rows']
request=json.loads((H/'request.json').read_text());plans=[json.loads((H/r['path']).read_text())for r in request['plans']]
assert request['allowed_seen_seeds']==[1927003,1927005]
assert all(sha(H/r['path'])==r['sha256']for r in request['plans'])
plan=plans[0]
# Synthetic labels/time amounts test data plumbing only, never actual route measurements.
lines=['ROUTE19 '+c['name']+' '+d.shape_route(c,False)+' false false'for c in plan['cases']if c['kernel']=='bmm']
labels=d.parse_labels('\n'.join(lines),plan)
rows={c['name']:dict(best_ns=(i+1 if c['timed']else 0),checksum=i,timed=c['timed'])for i,c in enumerate(plan['cases'])}
summary=d.summarise(plan,[rows,rows],labels)
assert summary['mean_of_case_timers']['whole_ns']==sum(r['best_ns']for r in rows.values())
assert sum(r['ns']for r in summary['mean_of_case_timers']['routes'].values())==summary['mean_of_case_timers']['BMM_ns']
rejects=0
for bad in ('\n'.join(lines[:-1]),'\n'.join(lines+[lines[0]]),'\n'.join([lines[0].replace('false false','true true')]+lines[1:])):
    try:d.parse_labels(bad,plan)
    except RuntimeError:rejects+=1
assert rejects==3
lean=(H/'RouteLabels.lean').read_text()
assert 'import Submission\nimport BenchSuite' in lean and 'Submission.UnderflowZero.small'in lean
assert 'Bench.Suite.element c i.val 0 c.n'in lean and 'Bench.Suite.element c i.val 1 c.p'in lean
assert not any(x in lean for x in ('monoNanos','Submission.bmm','unsafe','extern','axiom'))
driver=(H/'route-profile-driver.py').read_text()
assert 'benchmark_suite.make_plan'not in driver and '1927003,1927005'in driver
assert 'old.verify_same_seed(*processes)'in driver and "remaining(90),build='read'"in driver
assert 'BenchSuite_C'in driver and 'identity()==before'in driver
data=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='STATIC_DRAFT_AND_EXISTING_PARSER_CHECKS_PASS',
          original_raw_log_fixture_rows=156,synthetic_label_cases=len(labels),negative_label_cases=rejects,
          timing_unit_check='Raw case ns conserved; no work multiplication',
          files=[dict(path=p.name,sha256=sha(p),bytes=p.stat().st_size)for p in sorted(H.iterdir())if p.is_file()and p.name not in ('draft-validation.json',)],
          runtime=dict(Lean='NOT_RUN',Linux_diagnostic='NOT_RUN',new_route_times='UNKNOWN',destruction_C_audit='PENDING_FIRST_RUN'))
(H/'draft-validation.json').write_text(json.dumps(data,indent=2)+'\n')
print(json.dumps({k:data[k]for k in ('state','original_raw_log_fixture_rows','synthetic_label_cases','negative_label_cases','timing_unit_check')},indent=2))
