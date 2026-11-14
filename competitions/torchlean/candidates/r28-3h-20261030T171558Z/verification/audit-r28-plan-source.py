from pathlib import Path
import hashlib, importlib.util, json

root=Path.cwd()
round=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
state=round/'competition-state'
plan=json.loads((round/'ci-plan.json').read_bytes())
live=json.loads((state/'live-refresh.json').read_bytes())
boards=json.loads((state/'boards.raw').read_bytes())
champ=json.loads((state/'champions-resnet.raw').read_bytes())
entry=plan['candidates'][0]
patch_path=root/entry['patch_script']
spec=importlib.util.spec_from_file_location('r28_patch_review',patch_path)
patch=importlib.util.module_from_spec(spec);spec.loader.exec_module(patch)
source_path=state/'source-private/official-11.lean'
raw=source_path.read_bytes();built=patch.transform(raw,11,entry['variant'])
source_hash=hashlib.sha256(raw).hexdigest();candidate_hash=hashlib.sha256(built).hexdigest()
current=[x for x in champ['champions'] if x.get('current') is True]
board=[x for x in boards['boards'] if x['id']=='resnet']
profile_path=root/plan['profile_adapter']
ci_request=json.loads((round/'research/CI-REQUEST.json').read_bytes())
root_status=json.loads((round/'development-status.json').read_bytes())
root_ci_request=json.loads((round/'CI-REQUEST.json').read_bytes())
research_ci_request=json.loads((round/'research/CI-REQUEST.json').read_bytes())
receipt=next(x for x in live['receipts'] if x['url'].endswith('/champions?board=resnet'))
plan_hash=hashlib.sha256((round/'ci-plan.json').read_bytes()).hexdigest()
profile_text=profile_path.read_text(encoding='utf-8')
runner_text=(round/'development/ci-bridge/runner.py').read_text(encoding='utf-8')
result={
 'scope':'READ_ONLY_R28_PREDISPATCH_PLAN_AND_SOURCE_BINDING',
 'captured_at_utc':__import__('datetime').datetime.now(__import__('datetime').timezone.utc).isoformat(),
 'plan_sha256':hashlib.sha256((round/'ci-plan.json').read_bytes()).hexdigest(),
 'candidate_source':{'reference_submission':11,'reference_sha256':source_hash,'reference_receipt_matches':source_hash==plan['reference']['sha256']==entry['fetch']['sha256'],'candidate_sha256_recomputed':candidate_hash,'candidate_sha256_planned':entry['sha256'],'candidate_hash_matches':candidate_hash==entry['sha256'],'candidate_bytes_recomputed':len(built),'candidate_bytes_planned':entry['bytes'],'within_256000':len(built)<=256000,'patch_sha256_recomputed':hashlib.sha256(patch_path.read_bytes()).hexdigest(),'patch_sha256_planned':entry['patch_script_sha256']},
 'champion_binding':{'publication_hash':boards['publication_hash'],'champion_response_sha256':hashlib.sha256((state/'champions-resnet.raw').read_bytes()).hexdigest(),'receipt_sha256':receipt['sha256'],'receipt_status':receipt['status'],'current_count':len(current),'current_submission':current[0]['submission'] if current else None,'current_source_sha256':current[0]['source_sha256'] if current else None,'current_source_available':current[0]['source_available'] if current else None,'board_promotion_id':board[0]['current_promotion_id'] if board else None,'current_promotion_id':current[0]['promotion_id'] if current else None,'plan_submission_matches':bool(current and plan['champion']['submission']==current[0]['submission']),'plan_source_sha256_matches':bool(current and plan['champion']['source_sha256']==current[0]['source_sha256']),'plan_edge_ratio_matches':bool(current and plan['champion']['current_champion_over_calibration']==current[0]['ratio']),'plan_timestamp_matches_receipt':plan['champion']['at_utc']==live['at_utc'],'plan_publication_hash_matches':plan['champion'].get('publication_hash')==boards['publication_hash'],'plan_response_sha256_matches':plan['champion'].get('champion_response_sha256')==hashlib.sha256((state/'champions-resnet.raw').read_bytes()).hexdigest(),'plan_boards_sha256_matches':plan['champion'].get('boards_response_sha256')==hashlib.sha256((state/'boards.raw').read_bytes()).hexdigest()},
 'runner_contract':{'full_gate':entry.get('full_gate'),'declares_correct':entry.get('declares_correct'),'measurement_mode':plan['measurement_mode'],'seed_count':len(plan['seeds']),'standard_confirmation_group_in_plan':any(x in plan for x in ('confirmation','confirmation_seeds','confirm_seeds')),'current_champion_measurement_direct':False,'profile_enabled':plan.get('profile_control',False),'profile_runs_on_reference_before_candidate_gate':True,'profile_budget_seconds':plan.get('profile_budget_seconds'),'profile_global_cap_240_present':'time.monotonic()+240' in profile_text,'profile_per_run_cap_20_present':'min(20,max(1,global_end-time.monotonic()-15))' in profile_text,'profile_failure_is_nonfatal':'except Exception as error' in runner_text and "record['cost_profile']={'state':'INCOMPLETE_DIAGNOSTIC_ONLY'" in runner_text,'profile_sha256_recomputed':hashlib.sha256(profile_path.read_bytes()).hexdigest(),'profile_sha256_planned':plan['profile_adapter_sha256'],'profile_hash_matches':hashlib.sha256(profile_path.read_bytes()).hexdigest()==plan['profile_adapter_sha256']},
 'dispatch_control':{'root_ci_request_state':root_ci_request['state'],'root_ci_request_plan_sha256':root_ci_request.get('plan_sha256'),'root_request_plan_hash_matches':root_ci_request.get('plan_sha256')==plan_hash,'root_request_candidate_hash_matches':root_ci_request.get('candidate_sha256')==candidate_hash,'research_ci_request_state':research_ci_request['state'],'root_round_state':root_status['state'],'root_active_ci_count':len(root_status.get('active_CI',[])),'client_checks_root_ci_request_state':b'CI-REQUEST.json' in (round/'development/ci-bridge/client.py').read_bytes(),'client_requires_exact_remote_commit':b"'/commits/'+branch" in (round/'development/ci-bridge/client.py').read_bytes(),'client_preflight_limits_active_branch_runs':b"assert not any(x['status']!='completed' for x in prior)" in (round/'development/ci-bridge/client.py').read_bytes()},
 'known_predispatch_gaps':['This is a quick exploration with two seeds in one runner; it is not a standard confirmation or fresh independent new-runner group.','The profile is now capped at 240 seconds with per-call limits of 20 seconds and its errors are recorded as diagnostic failures; it still runs before the candidate gate.','The dispatch helper does not itself validate the root CI-REQUEST state/hash, although the current root request is READY and binds this exact plan hash.','The 17:40 dispatch deadline and 17:50 runner start cutoff leave ten minutes for a queued runner to start.'],
 'checks_passed':candidate_hash==entry['sha256'] and len(current)==1 and plan['champion']['submission']==current[0]['submission'] and plan['champion']['source_sha256']==current[0]['source_sha256'] and plan['champion']['current_champion_over_calibration']==current[0]['ratio'] and hashlib.sha256(profile_path.read_bytes()).hexdigest()==plan['profile_adapter_sha256'] and plan['champion'].get('publication_hash')==boards['publication_hash'] and plan['champion'].get('champion_response_sha256')==hashlib.sha256((state/'champions-resnet.raw').read_bytes()).hexdigest() and root_ci_request.get('plan_sha256')==plan_hash and root_ci_request.get('candidate_sha256')==candidate_hash
}
out=round/'verification/audit-r28-plan-source.json'
out.write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps(result,indent=2))
