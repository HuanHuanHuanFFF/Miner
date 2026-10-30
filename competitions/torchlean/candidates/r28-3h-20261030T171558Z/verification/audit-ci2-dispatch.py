from pathlib import Path
import hashlib,json,subprocess,datetime
ROOT=Path.cwd(); ROUND=ROOT/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'; E=ROUND/'evidence/dispatch-20261030T180113Z'
d=json.loads((E/'dispatch.json').read_bytes()); req=json.loads((E/'request.json').read_bytes()); plan=json.loads((ROUND/'ci-plan.json').read_bytes()); ci=json.loads((ROUND/'CI-REQUEST.json').read_bytes()); status=json.loads((ROUND/'development-status.json').read_bytes()); live=json.loads((ROUND/'competition-state/live-refresh.json').read_bytes()); boards=json.loads((ROUND/'competition-state/boards.raw').read_bytes())
board=plan['board']; champion_raw=ROUND/'competition-state'/f'champions-{board}.raw'; champions=json.loads(champion_raw.read_bytes()); current=[x for x in champions['champions'] if x.get('current') is True]; board_row=[x for x in boards['boards'] if x['id']==board]
plan_rel=(ROUND/'ci-plan.json').relative_to(ROOT).as_posix(); plan_hash=hashlib.sha256((ROUND/'ci-plan.json').read_bytes()).hexdigest()
rows=[]
for rel,expected in d['frozen_files'].items():
    blob=subprocess.check_output(['git','show',f"{d['source_commit']}:{rel}"],cwd=ROOT); current_bytes=(ROOT/rel).read_bytes()
    rows.append({'path':rel,'expected_sha256':expected,'commit_blob_sha256':hashlib.sha256(blob).hexdigest(),'workspace_sha256':hashlib.sha256(current_bytes).hexdigest(),'commit_blob_matches':hashlib.sha256(blob).hexdigest()==expected,'workspace_matches':hashlib.sha256(current_bytes).hexdigest()==expected})
source_receipt=next((x for x in live['receipts'] if x.get('submission')==plan['reference']['fetch']['submission'] and x['url'].endswith('/source')),None)
base_source=ROOT/source_receipt['path'] if source_receipt else None
base_hash=hashlib.sha256(base_source.read_bytes()).hexdigest() if base_source and base_source.is_file() else None
freeze=json.loads((ROUND/'development/ci-bridge/batch2/freeze.json').read_bytes())
probe=ROOT/plan['code_probe']; recipe=ROOT/plan['candidates'][0]['patch_script']
checks={
 'run_commit_matches_head_and_dispatch':d['source_commit']==d['run']['headSha']==subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip(),
 'request_plan_hash_matches':ci['plan_sha256']==plan_hash==d['frozen_files'][plan_rel],
 'request_candidate_hash_matches':ci['candidate_sha256']==plan['candidates'][0]['sha256']==freeze['candidate_sha256'],
 'request_run_matches':ci['run']==d['run']['databaseId']==status['active_CI'][0]['run'],
 'manual_public_false_route':d['repository_public'] is True and req['inputs']=={'competition':'floatlib','candidates':'__torchlean_r28__','seed':str(plan['dispatch_seed']),'allow_private':'false'},
 'candidate_recipe_hash_matches_freeze':hashlib.sha256(recipe.read_bytes()).hexdigest()==plan['candidates'][0]['patch_script_sha256']==freeze['frozen_recipe_sha256'],
 'reference_source_hash_matches_saved_receipt':base_hash==plan['reference']['sha256']==source_receipt['sha256'],
 'code_probe_hash_matches_plan':hashlib.sha256(probe.read_bytes()).hexdigest()==plan['code_probe_sha256'],
 'fresh_current_champion_bound':len(current)==1 and current[0]['submission']==plan['champion']['submission'] and current[0]['source_sha256']==plan['champion']['source_sha256'] and current[0]['ratio']==plan['champion']['current_champion_over_calibration'] and champions['publication_hash']==plan['champion']['publication_hash'] and hashlib.sha256(champion_raw.read_bytes()).hexdigest()==plan['champion']['champion_response_sha256'] and hashlib.sha256((ROUND/'competition-state/boards.raw').read_bytes()).hexdigest()==plan['champion']['boards_response_sha256'] and board_row[0]['current_promotion_id']==current[0]['promotion_id'],
 'prior_run_terminal_review_linked':json.loads((ROUND/'evidence/41099255272/execution-reconciliation.json').read_bytes())['independent_review']['sha256']==hashlib.sha256((ROUND/'evidence/41099255272/independent-terminal-review.json').read_bytes()).hexdigest(),
 'all_frozen_blobs_match':all(x['commit_blob_matches'] for x in rows),'all_frozen_workspace_files_match':all(x['workspace_matches'] for x in rows),
 'mobile_full_gate_planned':plan['candidates'][0].get('full_gate') is True,
 'plan_is_quick_exploration':plan['measurement_mode']=='quick' and len(plan['seeds'])==2,
 'not_yet_complete':d['run']['status']=='queued' and d['state']=='RUN_IDENTIFIED'
}
out={'round':'R28','scope':'READ_ONLY_CI2_DISPATCH_AND_PLAN_FREEZE_AUDIT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'run':d['run']['databaseId'],'source_commit':d['source_commit'],'plan_sha256':plan_hash,'candidate_sha256':plan['candidates'][0]['sha256'],'board':board,'checks':checks,'frozen_files':rows,'reference_source':{'submission':plan['reference']['fetch']['submission'],'receipt_sha256':source_receipt['sha256'] if source_receipt else None,'saved_sha256':base_hash,'matches':base_hash==plan['reference']['sha256']},'champion':{'submission':plan['champion']['submission'],'current_source_available':current[0]['source_available'] if current else None,'response_sha256':plan['champion']['champion_response_sha256'],'publication_hash':plan['champion']['publication_hash'],'comparison':plan['champion']['comparison']},'code_probe_sha256':hashlib.sha256(probe.read_bytes()).hexdigest(),'recipe_sha256':hashlib.sha256(recipe.read_bytes()).hexdigest(),'candidate_proof_outcome':'UNKNOWN_UNTIL_RUN; exact full original gate planned; no proof inherited','checks_passed':all(checks.values())}
(ROUND/'verification/audit-ci2-dispatch.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
