from pathlib import Path
import datetime, hashlib, json, subprocess

root=Path.cwd()
round_dir=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
run_id=41113231015
dispatch_dir=round_dir/'evidence/dispatch-20261030T191144Z'
dispatch=json.loads((dispatch_dir/'dispatch.json').read_bytes())
request=json.loads((dispatch_dir/'request.json').read_bytes())
plan_path=round_dir/'ci-plan.json'
plan=json.loads(plan_path.read_bytes())
ci_request=json.loads((round_dir/'CI-REQUEST.json').read_bytes())
status=json.loads((round_dir/'development-status.json').read_bytes())
sha=lambda b:hashlib.sha256(b).hexdigest()
commit=dispatch['source_commit']
head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=root,text=True).strip()
rows=[]
for rel,expected in dispatch['frozen_files'].items():
    blob=subprocess.check_output(['git','show',f'{commit}:{rel}'],cwd=root)
    current=(root/Path(*rel.split('/'))).read_bytes()
    bh,ch=sha(blob),sha(current)
    rows.append({'path':rel,'expected_sha256':expected,'commit_blob_sha256':bh,'workspace_sha256':ch,'blob_matches':bh==expected,'workspace_matches':ch==expected})
candidate_hashes=[x['sha256'] for x in plan['candidates']]
helper_names=[x['name'] for x in plan['helpers']]
checks={
  'run_and_head_binding': dispatch['run']['databaseId']==run_id and dispatch['run']['headSha']==commit,
  'request_payload_matches_receipt': request==dispatch['request'],
  'exact_plan_sha_bound_to_request_and_dispatch': sha(plan_path.read_bytes())==ci_request['plan_sha256']==dispatch['frozen_files'][str(plan_path.relative_to(root)).replace('\\','/')],
  'candidate_hashes_bound': candidate_hashes==ci_request['candidate_hashes'] and all(not x.get('full_gate',False) and not x.get('declares_correct',True) for x in plan['candidates']),
  'helper_names_bound': helper_names==ci_request['helpers'] and all(x['seconds']<=120 for x in plan['helpers']),
  'two_cost_sources_no_full_gate': len(plan['candidates'])==2 and not any(x.get('full_gate',False) for x in plan['candidates']) and 'public53-zero-proof-v2' not in {x['name'] for x in plan['candidates']},
  'public_repo_and_private_disabled': dispatch['repository_public'] is True and request['inputs']['allow_private']=='false',
  'manual_dispatch_sentinel': request['inputs']['competition']=='floatlib' and request['inputs']['candidates']=='__torchlean_r28__',
  'all_frozen_commit_blobs_match': all(x['blob_matches'] for x in rows),
  'all_frozen_workspace_files_match': all(x['workspace_matches'] for x in rows),
}
reconciled=(ci_request['state']=='RUN_IDENTIFIED' and ci_request.get('run')==run_id and any(x.get('run')==run_id for x in status.get('active_CI',[])))
out={
  'round':'R28','scope':'READ_ONLY_CI4_DISPATCH_FREEZE_AUDIT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
  'run':run_id,'source_commit':commit,'head_at_audit':head,'root_plan_sha256':sha(plan_path.read_bytes()),'root_request_plan_sha256':ci_request['plan_sha256'],
  'checks':checks,'checks_passed':all(checks.values()),
  'root_reconciliation':{'state_consistent_with_dispatch':reconciled,'ci_request_state':ci_request['state'],'ci_request_run':ci_request.get('run'),'root_status_state':status['state'],'root_status_active_runs':[x['run'] for x in status.get('active_CI',[])],'dispatch_receipt_state':dispatch['state'],'dispatch_run_status_at_receipt':dispatch['run']['status'],'note':'Dispatch receipt identifies run 41113231015, but root CI-REQUEST/status are still at READY/no active run as of this read; root should reconcile before terminal result review.'},
  'frozen_files':rows,
  'candidate_hashes':candidate_hashes,'helpers':helper_names,
  'dispatch_deadlines_utc':{'not_after':plan['dispatch_not_after_utc'],'start_cutoff':plan['start_cutoff_utc']},
}
(round_dir/'verification/audit-dispatch-freeze-41113231015.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':out['checks_passed'],'failed_checks':[k for k,v in checks.items() if not v],'reconciliation':out['root_reconciliation'],'frozen_file_count':len(rows),'plan_sha256':out['root_plan_sha256'],'candidate_hashes':candidate_hashes,'helpers':helper_names},indent=2))
