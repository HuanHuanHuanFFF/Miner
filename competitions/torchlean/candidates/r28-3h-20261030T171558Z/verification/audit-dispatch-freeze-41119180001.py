from pathlib import Path
import datetime,hashlib,json,subprocess

root=Path.cwd();round_dir=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z';run_id=41119180001
dispatch_dir=round_dir/'evidence/dispatch-20261030T195529Z'
dispatch=json.loads((dispatch_dir/'dispatch.json').read_bytes());payload=json.loads((dispatch_dir/'request.json').read_bytes())
plan_path=round_dir/'ci-plan.json';plan=json.loads(plan_path.read_bytes())
ci_request=json.loads((round_dir/'CI-REQUEST.json').read_bytes());status=json.loads((round_dir/'development-status.json').read_bytes())
sha=lambda b:hashlib.sha256(b).hexdigest();commit=dispatch['source_commit'];rows=[]
for rel,expected in dispatch['frozen_files'].items():
 blob=subprocess.check_output(['git','show',f'{commit}:{rel}'],cwd=root);current=(root/Path(*rel.split('/'))).read_bytes()
 rows.append({'path':rel,'expected_sha256':expected,'commit_blob_sha256':sha(blob),'workspace_sha256':sha(current),'blob_matches':sha(blob)==expected,'workspace_matches':sha(current)==expected})
norm_path=round_dir/'development/ci-bridge/batch6/build_norm26_36.py';zero_path=round_dir/'development/ci-bridge/batch6/build_mixer36_input_zero_cost.py'
checks={
 'run_and_commit_binding':dispatch['run']['databaseId']==run_id and dispatch['run']['headSha']==commit,
 'dispatch_payload_matches_receipt':payload==dispatch['request'],
 'plan_hash_matches_request_and_frozen_commit':sha(plan_path.read_bytes())==ci_request['plan_sha256']==dispatch['frozen_files'][str(plan_path.relative_to(root)).replace('\\','/')],
 'candidate_hashes_match_request':[x['sha256'] for x in plan['candidates']]==ci_request['candidate_hashes'],
 'recipe_hashes_match_plan':sha(norm_path.read_bytes())==plan['candidates'][0]['patch_script_sha256'] and sha(zero_path.read_bytes())==plan['candidates'][1]['patch_script_sha256'],
 'confirmation_isolation_bound':ci_request['confirmation_isolation']==plan['confirmation_isolation']=='OnlyDroot/verificationmayinspectseed/input/resultbeforewholebatchcomplete; researchusesprefreeze materials',
 'candidate_gate_boundaries_preserved':plan['candidates'][0]['full_gate'] is False and plan['candidates'][0]['declares_correct'] is True and plan['candidates'][1]['full_gate'] is False and plan['candidates'][1]['declares_correct'] is False,
 'public_repo_private_false':dispatch['repository_public'] is True and payload['inputs']['allow_private']=='false',
 'manual_dispatch_sentinel':payload['inputs']['competition']=='floatlib' and payload['inputs']['candidates']=='__torchlean_r28__',
 'all_commit_blobs_match_receipt':all(x['blob_matches'] for x in rows),
 'all_workspace_files_match_receipt':all(x['workspace_matches'] for x in rows),
 'root_status_request_run_match':ci_request['state']=='RUN_IDENTIFIED' and ci_request.get('run')==run_id and any(x.get('run')==run_id and x.get('source_commit')==commit for x in status.get('active_CI',[])),
}
out={'round':'R28','scope':'READ_ONLY_CI6_DISPATCH_FREEZE_AUDIT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'run':run_id,'source_commit':commit,'root_plan_sha256':sha(plan_path.read_bytes()),'candidate_hashes':[x['sha256'] for x in plan['candidates']],'checks':checks,'checks_passed':all(checks.values()),'frozen_files':rows,'restricted_seed_group':{'count':len(plan['seeds']),'two_distinct':len(set(plan['seeds']))==2,'visible_to_roles':'Droot/verification only until full batch completion; no seed values in this dispatch audit'},'root_status_state':status['state'],'dispatch_status':dispatch['run']['status']}
(round_dir/'verification/audit-dispatch-freeze-41119180001.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':out['checks_passed'],'failed_checks':[k for k,v in checks.items() if not v],'run':run_id,'source_commit':commit,'plan_sha256':out['root_plan_sha256'],'candidate_hashes':out['candidate_hashes'],'frozen_file_count':len(rows),'root_status_state':status['state']},indent=2))
