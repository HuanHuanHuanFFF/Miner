from pathlib import Path
import datetime,hashlib,importlib.util,json,re,sys

sys.dont_write_bytecode=True
root=Path.cwd();round_dir=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
batch=round_dir/'development/ci-bridge/batch5';recipe=batch/'build_pointwise128_typed.py'
plan_path=round_dir/'ci-plan.json';plan=json.loads(plan_path.read_bytes())
ci_request=json.loads((round_dir/'CI-REQUEST.json').read_bytes());status=json.loads((round_dir/'development-status.json').read_bytes())
freeze=json.loads((batch/'freeze.json').read_bytes())
producer=round_dir/'research/mobile-mechanism/pointwise128-typed-receipt.json';producer_receipt=json.loads(producer.read_bytes())
base=(round_dir/'competition-state/source-private/official-53.lean').read_bytes()
sha=lambda b:hashlib.sha256(b).hexdigest()
spec=importlib.util.spec_from_file_location('r28_ci5_typed_readonly',recipe);mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
candidate=mod.transform(base,53,plan['candidates'][0]['variant'])
entry=plan['candidates'][0]
snapshot=round_dir/'competition-state/refresh-20261030T181518Z'
receipt=json.loads((snapshot/'receipt.json').read_bytes());champ_raw=(snapshot/'champions-mobilenet.raw').read_bytes();boards_raw=(snapshot/'boards.raw').read_bytes()
receipt_by={Path(x['path']).name:x for x in receipt['receipts'] if 'path' in x}
candidate_names=re.findall(r'(?m)^(?:@\[[^\n]*?\]\s+)?(?:lemma|theorem|def|abbrev|structure|instance)\s+([A-Za-z][A-Za-z0-9_]*)',candidate.decode('utf-8'))
forbidden=re.findall(rb'\b(sorry|admit|axiom|unsafe|native_decide|implemented_by|extern)\b',candidate)
old_plan_hash='a8a3d3b93ae306524dc76912ff7be9391898513d65ebbb0a76612071343a8aab'
old_ci4_seeds={1862165997,2581435054}
prior_seeds=set(old_ci4_seeds)
for r in (round_dir/'evidence').iterdir():
    if not r.is_dir(): continue
    for p in r.glob('download-*/plan.json'):
        try: prior_seeds.update(json.loads(p.read_bytes()).get('seeds',[]))
        except Exception: pass
checks={
 'official53_source_hash_matches_reference':sha(base)==plan['reference']['sha256']=='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb',
 'typed_recipe_rebuild_matches_plan':sha(candidate)==entry['sha256']==ci_request['candidate_hashes'][0]==freeze['candidate_sha256']==producer_receipt['candidate_sha256'] and len(candidate)==entry['bytes']==freeze['bytes']==producer_receipt['candidate_bytes'] and len(candidate)<=256000,
 'recipe_hash_matches_plan_freeze_and_producer':sha(recipe.read_bytes())==entry['patch_script_sha256']==producer_receipt['recipe_sha256'] and sha(producer.read_bytes())==freeze['producer_receipt_sha256'],
 'source_is_explicitly_nativeonly':entry['full_gate'] is False and entry['declares_correct'] is False and 'correct' not in candidate_names,
 'no_forbidden_constructs_in_candidate_source':not forbidden,
 'single_candidate_no_helpers_no_full_gate':len(plan['candidates'])==1 and plan['helpers']==[] and not any(x.get('full_gate',False) for x in plan['candidates']),
 'only_mobile_pointwise_candidate_is_in_plan':entry['name']=='public53-pointwise128-typed-native-only' and plan['board']=='mobilenet' and plan['measurement_mode']=='quick',
 'two_new_measurement_seeds':len(plan['seeds'])==2 and len(set(plan['seeds']))==2 and not (set(plan['seeds'])&prior_seeds),
 'producer_receipt_matches_old_failed_candidate_and_new_source':producer_receipt['old_sha256']=='5ecfdd8cd0073e37185d4f88126db886372429b10efb429f84210710557afe5d' and producer_receipt['candidate_sha256']==entry['sha256'] and producer_receipt['proof_state'].startswith('UNPROVED_NATIVE_RESEARCH_ONLY'),
 'mobile_champion_response_hash_and_publication_match_snapshot':sha(champ_raw)==plan['champion']['champion_response_sha256']==receipt_by['champions-mobilenet.raw']['sha256'] and sha(boards_raw)==plan['champion']['boards_response_sha256']==receipt_by['boards.raw']['sha256'] and receipt['state']=='LIVE_ALL_SIX' and plan['champion']['publication_hash']=='0c6957aa9fdec2541618776c29514f7e80afcb5adf27973c84c5d8f3a6b0a8f5',
 'root_request_plan_status_consistent':sha(plan_path.read_bytes())==ci_request['plan_sha256']==old_plan_hash and ci_request['state']=='READY' and ci_request['batch']==5 and status['state']=='CI5_FINISH_POINTWISE_REPAIR_READY' and status['active_CI']==[],
 'no_fullgate_or_correctness_claim':entry.get('full_gate') is False and entry.get('declares_correct') is False,
}
out={'round':'R28','scope':'READ_ONLY_CI5_TYPED_POINTWISE_PRE-DISPATCH_SOURCE_AND_PLAN_AUDIT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'plan_sha256':sha(plan_path.read_bytes()),'candidate_sha256':sha(candidate),'candidate_bytes':len(candidate),'recipe_sha256':sha(recipe.read_bytes()),'producer_receipt_sha256':sha(producer.read_bytes()),'producer_receipt_declared_sha256':freeze['producer_receipt_sha256'],'official53_sha256':sha(base),'seeds':plan['seeds'],'prior_seed_count':len(prior_seeds),'champion_snapshot':{'at_utc':plan['champion']['at_utc'],'publication':plan['champion']['publication_hash'],'response_sha256':sha(champ_raw),'boards_sha256':sha(boards_raw),'current_ratio':plan['champion']['current_champion_over_calibration']},'dispatch_window':{'not_after':plan['dispatch_not_after_utc'],'start_cutoff':plan['start_cutoff_utc'],'driver_seconds':plan['driver_seconds']},'checks':checks,'checks_passed':all(checks.values()),'freshness_boundary':'Champion response is exactly bound to the 18:15 snapshot; no newer refresh was present in the workspace during this audit. Re-fetch before dispatch/score adoption. Candidate costs remain diagnostic and unproved.', 'correctness_boundary':'The typed candidate has no correct declaration and is NativeOnly. No proof/full gate or accepted native build is asserted; the new run must report build failure or measurement under this exact source hash.'}
(round_dir/'verification/audit-ci5-preflight.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':out['checks_passed'],'failed_checks':[k for k,v in checks.items() if not v],'plan_sha256':out['plan_sha256'],'candidate_sha256':out['candidate_sha256'],'bytes':out['candidate_bytes'],'recipe_sha256':out['recipe_sha256'],'seeds':out['seeds'],'current_champion_snapshot':out['champion_snapshot']},indent=2))
