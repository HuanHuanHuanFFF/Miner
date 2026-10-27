"""Build ADD analogue of executed MUL package; no Lean, Git, CI or network."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,ast
H=Path(__file__).resolve().parent;R19=H.parent
R=next(p for p in H.parents if(p/'competitions/floatlib/pins.json').is_file());C=R/'competitions/floatlib/candidates'
T=R19/'development-runtime-cost';SOURCE='77377f8b373988545c557aa6f5cd5edfd82ec772bb643a404a15e26e02d627af'
OLD='74899988939a056a40675aefe8c63f2f9db1c7b4728f3d496bf140ede6ad85dc'
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
def save(p,x):p.write_bytes((json.dumps(x,indent=2,ensure_ascii=False)+'\n').encode())
def write(p,raw):p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(raw)
def component(p):return dict(path=p.relative_to(R).as_posix(),sha256=sha(p),bytes=p.stat().st_size)
def verify(run):
 root=C/'f01-mul-log2-proof1/ci-runs'/str(run);idx=root/'original-artifact-hashes.json';x=json.loads(idx.read_text());d=root/x['directory']
 for name,row in x['files'].items():
  p=d/name;assert sha(p)==row['sha256']and p.stat().st_size==row['bytes'],name
 assert {p.relative_to(d).as_posix()for p in d.rglob('*')if p.is_file()}==set(x['files'])
 return d,dict(run=run,index=component(idx),files=len(x['files']),bytes=sum(r['bytes']for r in x['files'].values()))
def main():
 protected=[p for p in T.rglob('*')if p.is_file()]+[R19/'development-runtime-cost-audit.py',C/'f01-r19-dev-runtime-cost1/manifest.json',C/'f01-r19-dev-runtime-cost1/Kernel.lean']
 before={p:sha(p)for p in protected}
 ci12,receipt12=verify(40430974047);ci13,receipt13=verify(40432634558)
 source=C/'f01-r19-dev-grs-add-runtime2/Kernel.lean';raw=source.read_bytes()
 assert sha(source)==SOURCE and len(raw)==228707
 original_input=ci12/'diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r19-dev-grs-add-runtime2/Kernel.lean'
 assert original_input.read_bytes()==raw
 base=C/'f01-r15-dev-packed-b2-1/Kernel.lean';assert raw.startswith(base.read_bytes())
 oldmanifest=json.loads((C/'f01-r19-dev-runtime-cost1/manifest.json').read_text())
 for row in oldmanifest['components']:
  p=R/row['path'];assert sha(p)==row['sha256']and p.stat().st_size==row['bytes']
 # Template was actually run successfully in CI13. Keep its immutable raw identity.
 template_input=ci13/'diagnostics/f01-d7-public-suite/public-suite/inputs/f01-r19-dev-runtime-cost1/Kernel.lean'
 assert sha(template_input)==OLD
 runtime_stage=ci13/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-runtime-cost1/runtime-cost/stage-receipt.json'
 stage=json.loads(runtime_stage.read_text());assert stage['status']=='DIAGNOSTIC_DATA_COMPLETE_REVIEW_PENDING'
 runtime_dir=runtime_stage.parent
 template_flags=runtime_dir/'flags-and-link.json';flags=json.loads(template_flags.read_text())
 assert set(flags)=={'compile','link','link_response'} and all(v['equal_after_only_root_target_path_mapping']for v in flags.values())
 assert (runtime_dir/'caller.lean').read_bytes()==(T/'R19RuntimeCostMain.lean').read_bytes()
 prepare=json.loads((runtime_dir/'prepare.json').read_text())
 assert prepare['build_argv'][1:]==['-f','work/R19RuntimeCostLake.lean','build','r19RuntimeCost']
 for name in('plan-1927003.json','plan-1927005.json','exposed-plans.json','legacy-whole-parser.py','bounded-capture-source.py'):
  write(H/name,(T/name).read_bytes())
 maintext=(T/'R19RuntimeCostMain.lean').read_text().replace('MUL','ADD').replace('r19CostGuardedMul','r19CostGuardedAdd').replace('Submission.R19DirectBias.guardedMul Submission.mul','Submission.R19GRS32Add.guardedAdd Submission.add')
 maintext=maintext.replace('Bench.Suite.run Submission.add r19CostGuardedAdd Submission.sum Submission.bmm','Bench.Suite.run r19CostGuardedAdd Submission.mul Submission.sum Submission.bmm')
 assert 'guardedMul'not in maintext and 'R19DirectBias'not in maintext and 'diagnosticEntry'not in maintext
 write(H/'R19AddCostMain.lean',maintext.encode())
 driver=(T/'driver.py').read_text()
 for a,b in((OLD,SOURCE),('R19RuntimeCost','R19AddCost'),('r19RuntimeCost','r19AddCost'),('compiled748999','compiled77377f8b'),
             ('guardedMul Submission.mul','guardedAdd Submission.add'),('R19DirectBias_diagnosticEntry','R19GRS32Add_diagnosticEntry'),
             ('ADD/SUM/BMM remain old B2 callbacks','MUL/SUM/BMM remain old B2 callbacks')):driver=driver.replace(a,b)
 driver=driver.replace("r19_reused_R13_rows","r19_add_reused_R13_rows").replace("r19_reused_bounded_capture","r19_add_reused_bounded_capture")
 aliasline="    require(b'diagnosticEntry' not in template and b'@[inline]' in template and b'guardedAdd Submission.add' in template, 'Wrong guarded alias')"
 assert aliasline in driver
 driver=driver.replace(aliasline,"""    require(b'diagnosticEntry' not in template and b'@[inline] def r19CostGuardedAdd' in template
            and template.count(b'Submission.R19GRS32Add.guardedAdd Submission.add x y') == 1
            and template.count(b'Bench.Suite.run Submission.add Submission.mul Submission.sum Submission.bmm') == 1
            and template.count(b'Bench.Suite.run r19CostGuardedAdd Submission.mul Submission.sum Submission.bmm') == 1
            and template.count(b'Bench.Suite.run ') == 2 and b'guardedMul' not in template, 'Wrong ADD function alias or callback composition')""")
 driver=driver.replace("'source_sha256':SOURCE, 'runs':[]","'source_sha256':SOURCE, 'changed_operation':'ADD', 'runs':[]")
 assert all(s not in driver for s in('748999','R19DirectBias','R19RuntimeCost','r19RuntimeCost'))
 assert driver.count('guardedMul')==1 and "b'guardedMul' not in template"in driver
 write(H/'driver.py',driver.encode());ast.parse(driver)
 hook=(R19/'development-runtime-cost-audit.py').read_text()
 for a,b in((OLD,SOURCE),('development-runtime-cost','development-add-cost'),('r19_runtime_cost_driver','r19_add_cost_driver'),
             ("'runtime-cost'","'add-cost'"),('runtime-cost-diagnostic','add-cost-diagnostic'),('runtime-cost diagnostic failed','add-cost diagnostic failed'),
             ('HISTORICAL40420540388','HISTORICAL40430974047'),('new_public_MUL_correctness','new_public_ADD_correctness')):hook=hook.replace(a,b)
 hook=hook.replace("    assert manifest['runtime_cost']['reuse_historical_replay_only'] is True","    assert manifest['runtime_cost']['reuse_historical_replay_only'] is True\n    assert manifest['runtime_cost']['changed_operation'] == 'ADD'")
 hook=hook.replace("    driver = here/'development-add-cost/driver.py'","""    binding_path = here/'development-add-cost/historical-bindings.json'
    binding = json.loads(binding_path.read_bytes())
    assert manifest['historical_statement_evidence']['run'] == binding['run'] == 40430974047
    assert sha(binding_path) == manifest['historical_statement_evidence']['binding_sha256']
    assert binding['source_sha256'] == SOURCE
    driver = here/'development-add-cost/driver.py'""")
 assert OLD not in hook and '40420540388'not in hook
 hookpath=R19/'development-add-cost-audit.py';write(hookpath,hook.encode());ast.parse(hook)
 history=H/'historical40430974047';history.mkdir(exist_ok=True)
 original=ci12/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r19-dev-grs-add-runtime2'
 paths=[original/n for n in('helper-audit.json','helper-axioms.raw','helper-audit-source.lean','diagnostic-only-verdict.json','index.json','replay.log')]
 paths += [R19/'development-proof-f01-r19-dev-grs-add-runtime2-40430974047.json',R/'competitions/floatlib/candidates/f01-d7-research/official-policy/gate-4b7e838.raw']
 copies=[]
 for p in paths:
  target=history/p.name;write(target,p.read_bytes());copies.append(dict(original_path=p.relative_to(R).as_posix(),copy_path=target.relative_to(R).as_posix(),sha256=sha(p),bytes=p.stat().st_size))
 audit=json.loads((history/'helper-audit.json').read_text());assert audit['accepted']and audit['kernel_replay']and audit['expected_count']==len(audit['names'])==7 and audit['kernel_sha256']==SOURCE
 save(H/'historical-bindings.json',dict(run=40430974047,source_sha256=SOURCE,original_input=component(original_input),original_artifact_index=receipt12['index'],scope='CI12 original statement/Submission+VerifyFull replay/7explicit roots only; no theorem equating guardedAdd with public ADD',copies=copies))
 files=[H/n for n in('R19AddCostMain.lean','driver.py','plan-1927003.json','plan-1927005.json','exposed-plans.json','legacy-whole-parser.py','bounded-capture-source.py','historical-bindings.json')]+sorted(history.iterdir())
 assert len(files)==16
 candidate=C/'f01-r19-dev-add-cost1';candidate.mkdir(exist_ok=True);write(candidate/'Kernel.lean',raw)
 manifest=dict(oldmanifest);manifest.update(candidate=candidate.name,candidate_sha256=SOURCE,candidate_bytes=len(raw),
   created_at_utc=datetime.now(timezone.utc).isoformat(),parent=source.parent.name,parent_sha256=SOURCE,
   proof_status='HISTORICAL_CI12_77377_STATEMENT_REPLAY_7ROOTS_BOUND_PUBLIC_ADD_REMAINS_B2_GUARDED_EQUIVALENCE_UNKNOWN',
   mechanism='Exact77377 carrier; post-original-statement owned Lake target; same binary inline guardedAdd(B2 fallback) versus B2, only ADD callback replaced',
   components=[component(p)for p in files],helper_audit_module=hookpath.name,helper_audit_module_sha256=sha(hookpath),
   historical_statement_evidence=dict(run=40430974047,binding_path=(H/'historical-bindings.json').relative_to(R).as_posix(),binding_sha256=sha(H/'historical-bindings.json'),not_rerun=True),
   runtime_cost=dict(oldmanifest['runtime_cost'],changed_operation='ADD'),
   scope='NOT_RUN independent ADD diagnostic composition only; no original25-round score/gate/adoption or proof of new public ADD. MUL/SUM/BMM original B2 callbacks.')
 assert manifest['diagnostic_timeout_seconds']==600 and manifest['runtime_cost']['overall_budget_seconds_from_stage_registration']==580
 save(candidate/'manifest.json',manifest)
 assert all(sha(p)==v for p,v in before.items()),'Template or old candidate changed'
 save(H/'package-receipt.json',dict(status='ADD_PACKAGED_REMOTE_NOT_RUN',source_sha256=SOURCE,source_bytes=len(raw),source_prefix_exact622d=True,
   audit_sha256=sha(hookpath),driver_sha256=sha(H/'driver.py'),caller_sha256=sha(H/'R19AddCostMain.lean'),manifest_sha256=sha(candidate/'manifest.json'),
   component_count=len(files),historical=receipt12,executed_template=receipt13,template_stage_sha256=sha(runtime_stage),
   template_caller_sha256=sha(runtime_dir/'caller.lean'),template_flags_sha256=sha(template_flags),template_prepare_sha256=sha(runtime_dir/'prepare.json'),
   old_template_all_files_unchanged={p.relative_to(R).as_posix():v for p,v in before.items()},
   Lean='NOT_RUN',actual_benchmark='NOT_RUN',actual_C_ASM='NOT_RUN'))
 print(json.dumps({k:v for k,v in json.loads((H/'package-receipt.json').read_text()).items()if k not in('old_template_all_files_unchanged','historical','executed_template')},indent=2))
if __name__=='__main__':main()
