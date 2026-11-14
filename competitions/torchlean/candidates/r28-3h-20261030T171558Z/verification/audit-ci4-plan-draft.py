from pathlib import Path
import hashlib,importlib.util,json,datetime,sys
sys.dont_write_bytecode=True
root=Path.cwd();round=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z';folder=round/'development/ci-bridge/batch4';draft=json.loads((folder/'plan-draft.json').read_bytes());prefix=json.loads((folder/'prefix-and-whole-draft.json').read_bytes());base=(round/'competition-state/source-private/official-53.lean').read_bytes();basehash=hashlib.sha256(base).hexdigest()
def load(path,name):
 s=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
def output_hash(module,raw,variant):
 result=module.transform(raw,53,variant)
 if isinstance(result,tuple): result=result[0]
 return {'sha256':hashlib.sha256(result).hexdigest(),'bytes':len(result)}
point=load(folder/'build_pointwise128_frozen.py','ci4_pointwise_review');zero=load(folder/'build_zero_mobile_v2.py','ci4_zero_review')
point_plan=next(x for x in draft['candidates'] if x['name']=='public53-pointwise128-nat-native-only')
whole=draft['whole_candidate']
point_result=output_hash(point,base,point_plan['variant']);whole_result=output_hash(zero,base,whole['variant'])
helper_results=[]
for h in draft['helpers']:
 built=zero.transform(base,h['fetch']['submission'],h['variant']);
 if isinstance(built,tuple):built=built[0]
 helper_results.append({'name':h['name'],'planned_sha256':h['sha256'],'recomputed_sha256':hashlib.sha256(built).hexdigest(),'planned_bytes':h['bytes'],'recomputed_bytes':len(built),'hash_matches':hashlib.sha256(built).hexdigest()==h['sha256'],'size_matches':len(built)==h['bytes'],'seconds':h['seconds'],'within_120':h['seconds']<=120,'roots':h['helper_roots']})
# Pointwise uses the frozen source recipe's own transform contract; whole proof-v2 and helper transforms use one pinned #53 body.
runner=(round/'development/ci-bridge/runner.py').read_text(encoding='utf-8');client=(round/'development/ci-bridge/client.py').read_text(encoding='utf-8')
probe=load(round/'development/ci-bridge/code-diagnostics.py','ci4_probe_review')
plan_source=hashlib.sha256((round/'ci-plan.json').read_bytes()).hexdigest()
checks={
 'base53_hash_matches_recipe':basehash=='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb',
 'pointwise_candidate_rebuild_matches':point_result['sha256']==point_plan['sha256'] and point_result['bytes']==point_plan['bytes'] and point_result['bytes']<=256000,
 'zero_v2_candidate_rebuild_matches':whole_result['sha256']==whole['sha256'] and whole_result['bytes']==whole['bytes'] and whole_result['bytes']<=256000,
 'all_prefix_hashes_rebuild':all(x['hash_matches'] and x['size_matches'] and x['within_120'] for x in helper_results),
 'zero_v2_requires_exact_prefixes':set(whole['requires_helpers'])=={x['name'] for x in draft['helpers']} and whole['full_gate'] is True and whole['declares_correct'] is True,
 'pointwise_nativeonly_boundary':point_plan['full_gate'] is False and point_plan['declares_correct'] is False,
 'helper_runner_materializes_before_helper_loop':'def materialize(entry):' in runner and runner.find('def materialize(entry):')<runner.find('for entry in plan.get(\'helpers\',[]):'),
 'required_helpers_checked_before_candidate_build':'required=entry.get(\'requires_helpers\',[])' in runner and runner.find('required=entry.get(\'requires_helpers\',[])')<runner.find('binary,info=build(entry)'),
 'conditional_skip_marker_present':'SKIPPED_AFTER_BOUNDED_HELPER_FAILED' in runner,
 'helper_cap_plan_says_120':all(x['seconds']==120 for x in draft['helpers']),
 'helper_runtime_hard_cap_120':"min(120,entry.get('seconds',120)" in runner,
 'helper_logs_not_uploaded_verbatim':'-helper.log' not in runner,
 'probe_code_diagnostics_still_hash_pinned':hashlib.sha256((round/'development/ci-bridge/code-diagnostics.py').read_bytes()).hexdigest()==draft['code_probe_sha256'],
 'ci4_plan_is_draft_not_dispatched':prefix['state']=='NOT_DISPATCHED_FROZEN_PREFIXES_AND_CONDITIONAL_WHOLE',
}
out={'round':'R28','scope':'READ_ONLY_CI4_HELPER_CONTROL_AND_SOURCE_HASH_REVIEW','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'current_ci_plan_sha256':plan_source,'helper_plan_state':prefix['state'],'base53_sha256':basehash,'pointwise_candidate':{'name':point_plan['name'],'planned':point_plan['sha256'],'recomputed':point_result['sha256'],'bytes':point_result['bytes'],'full_gate':point_plan['full_gate'],'declares_correct':point_plan['declares_correct']},'whole_candidate':{'name':whole['name'],'planned':whole['sha256'],'recomputed':whole_result['sha256'],'bytes':whole_result['bytes'],'full_gate':whole['full_gate'],'declares_correct':whole['declares_correct'],'requires_helpers':whole['requires_helpers']},'helpers':helper_results,'checks':checks,'checks_passed':all(checks.values()),'issues':['The runner currently computes helper cap as min(entry.seconds,remaining) rather than hard-clamping at 120; this exact draft sets each helper seconds=120, but the code does not enforce the ceiling for future plans.','The runner writes complete Lean helper stdout/stderr to OUT/<name>-helper.log, and the workflow uploads all of OUT. Verify after CI4 collection that these logs contain no third-party prefix source text; sanitizing raw helper logs before upload is safer.','A thrown helper timeout/process exception can leave the helper loop before it records an explicit per-helper skip; nonzero exit codes do produce helper diagnostics and the conditional skip marker. Catch exceptions per helper if the requirement is an explicit marker for all timeout cases.'],'correctness_boundary':'The prefix probes do not establish the full candidate theorem. Pointwise is NativeOnly; zero-v2 fullgate remains gated on both exact helper exits 0 and then must pass the original all12 gate. No proof inherited.'}
(round/'verification/audit-ci4-plan-draft.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps({'checks_passed':out['checks_passed'],'base53':basehash,'pointwise':out['pointwise_candidate'],'whole':out['whole_candidate'],'helpers':helper_results,'failed_checks':[k for k,v in checks.items() if not v]},indent=2))
