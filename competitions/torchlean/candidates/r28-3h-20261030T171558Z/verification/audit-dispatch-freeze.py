from pathlib import Path
import hashlib,json,subprocess,datetime
root=Path.cwd(); round=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'; ev=round/'evidence/dispatch-20261030T172922Z'
d=json.loads((ev/'dispatch.json').read_bytes()); req=json.loads((ev/'request.json').read_bytes()); plan=json.loads((round/'ci-plan.json').read_bytes()); ci=json.loads((round/'CI-REQUEST.json').read_bytes()); status=json.loads((round/'development-status.json').read_bytes())
head=subprocess.check_output(['git','rev-parse','HEAD'],cwd=root,text=True).strip(); rows=[]
for rel,expected in d['frozen_files'].items():
    blob=subprocess.check_output(['git','show',f"{d['source_commit']}:{rel}"],cwd=root)
    current=(root/rel).read_bytes()
    blob_hash=hashlib.sha256(blob).hexdigest(); current_hash=hashlib.sha256(current).hexdigest()
    rows.append({'path':rel,'expected_sha256':expected,'run_commit_blob_sha256':blob_hash,'workspace_sha256':current_hash,'blob_matches':blob_hash==expected,'workspace_matches':current_hash==expected})
checks={
 'head_matches_run':head==d['source_commit']==d['run']['headSha'],
 'plan_hash_matches_request':hashlib.sha256((round/'ci-plan.json').read_bytes()).hexdigest()==d['frozen_files'][str((round/'ci-plan.json').relative_to(root)).replace('\\','/')]==ci['plan_sha256'],
 'candidate_hash_matches_request':plan['candidates'][0]['sha256']==ci['candidate_sha256'],
 'run_id_matches_status':d['run']['databaseId']==status['active_CI'][0]['run'],
 'public_repo':d['repository_public'] is True,
 'allow_private_false':req['inputs']['allow_private']=='false',
 'correct_manual_sentinel':req['inputs']['competition']=='floatlib' and req['inputs']['candidates']=='__torchlean_r28__',
 'dispatch_result_identified':d['state']=='RUN_IDENTIFIED' and d['run']['status']=='in_progress' and ci['state']=='RUN_IDENTIFIED',
 'all_frozen_blobs_match':all(x['blob_matches'] for x in rows),
 'all_workspace_files_match':all(x['workspace_matches'] for x in rows),
}
out={'round':'R28','scope':'READ_ONLY_DISPATCH_RECEIPT_AND_FROZEN_BLOB_AUDIT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'run':d['run']['databaseId'],'source_commit':d['source_commit'],'plan_sha256':ci['plan_sha256'],'candidate_sha256':ci['candidate_sha256'],'checks':checks,'frozen_files':rows,'checks_passed':all(checks.values())}
(round/'verification/audit-dispatch-freeze.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8');print(json.dumps(out,indent=2))
