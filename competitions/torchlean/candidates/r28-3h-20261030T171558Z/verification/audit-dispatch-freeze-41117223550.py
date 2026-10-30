from pathlib import Path
import datetime,hashlib,json,subprocess

root=Path.cwd();round_dir=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
run_id=41117223550;dispatch_dir=round_dir/'evidence/dispatch-20261030T194055Z'
dispatch=json.loads((dispatch_dir/'dispatch.json').read_bytes());request=json.loads((dispatch_dir/'request.json').read_bytes())
plan_path=round_dir/'ci-plan.json';plan=json.loads(plan_path.read_bytes())
ci_request=json.loads((round_dir/'CI-REQUEST.json').read_bytes());status=json.loads((round_dir/'development-status.json').read_bytes())
sha=lambda b:hashlib.sha256(b).hexdigest();commit=dispatch['source_commit'];rows=[]
for rel,expected in dispatch['frozen_files'].items():
 blob=subprocess.check_output(['git','show',f'{commit}:{rel}'],cwd=root)
 current=(root/Path(*rel.split('/'))).read_bytes()
 rows.append({'path':rel,'expected_sha256':expected,'commit_blob_sha256':sha(blob),'workspace_sha256':sha(current),'blob_matches':sha(blob)==expected,'workspace_matches':sha(current)==expected})
hashes=[x['sha256'] for x in plan['candidates']]
checks={
 'run_id_commit_and_status_binding':dispatch['run']['databaseId']==run_id and dispatch['run']['headSha']==commit and dispatch['run']['status'] in {'queued','in_progress'},
 'request_payload_matches_receipt':request==dispatch['request'],
 'root_plan_hash_matches_request_and_commit':sha(plan_path.read_bytes())==ci_request['plan_sha256']==dispatch['frozen_files'][str(plan_path.relative_to(root)).replace('\\','/')],
 'candidate_hash_matches_request':hashes==ci_request['candidate_hashes']==[freeze['candidate_sha256'] for freeze in [json.loads((round_dir/'development/ci-bridge/batch5/freeze.json').read_bytes())]],
 'source_recipe_hash_matches_plan':sha((round_dir/'development/ci-bridge/batch5/build_pointwise128_typed.py').read_bytes())==plan['candidates'][0]['patch_script_sha256'],
 'nativeonly_no_fullgate':len(plan['candidates'])==1 and plan['candidates'][0]['full_gate'] is False and plan['candidates'][0]['declares_correct'] is False and plan['helpers']==[],
 'public_repo_and_private_disabled':dispatch['repository_public'] is True and request['inputs']['allow_private']=='false',
 'manual_dispatch_sentinel':request['inputs']['competition']=='floatlib' and request['inputs']['candidates']=='__torchlean_r28__',
 'all_commit_blobs_match_receipt':all(x['blob_matches'] for x in rows),
 'all_workspace_files_match_receipt':all(x['workspace_matches'] for x in rows),
}
reconciled=ci_request['state']=='RUN_IDENTIFIED' and ci_request.get('run')==run_id and any(x.get('run')==run_id for x in status.get('active_CI',[]))
out={'round':'R28','scope':'READ_ONLY_CI5_DISPATCH_FREEZE_AUDIT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'run':run_id,'source_commit':commit,'head_at_audit':subprocess.check_output(['git','rev-parse','HEAD'],cwd=root,text=True).strip(),'root_plan_sha256':sha(plan_path.read_bytes()),'candidate_hashes':hashes,'checks':checks,'checks_passed':all(checks.values()),'root_reconciliation':{'state_consistent_with_dispatch':reconciled,'ci_request_state':ci_request['state'],'ci_request_run':ci_request.get('run'),'root_status_state':status['state'],'root_status_active_runs':[x['run'] for x in status.get('active_CI',[])],'dispatch_state':dispatch['state'],'dispatch_run_status':dispatch['run']['status'],'note':'Dispatch receipt identifies run 41117223550 in progress; root CI-REQUEST/status are still READY/no active run as of this read.'},'frozen_files':rows,'seeds':plan['seeds'],'dispatch_window':{'not_after':plan['dispatch_not_after_utc'],'start_cutoff':plan['start_cutoff_utc'],'driver_seconds':plan['driver_seconds']}}
(round_dir/'verification/audit-dispatch-freeze-41117223550.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':out['checks_passed'],'failed_checks':[k for k,v in checks.items() if not v],'reconciliation':out['root_reconciliation'],'frozen_files':len(rows),'plan':out['root_plan_sha256'],'candidate':hashes},indent=2))
