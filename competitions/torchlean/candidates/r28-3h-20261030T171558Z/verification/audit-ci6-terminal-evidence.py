from pathlib import Path
import datetime,hashlib,json

root=Path.cwd();round_dir=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z';run_dir=round_dir/'evidence/41119180001'
rec=json.loads((run_dir/'execution-reconciliation.json').read_bytes())
manifest_path=run_dir/'original-artifact-hashes.json';manifest_bytes=manifest_path.read_bytes();manifest=json.loads(manifest_bytes)
artifact_dir=run_dir/manifest['directory'];sha=lambda b:hashlib.sha256(b).hexdigest()
missing=[];unexpected=[];bad=[]
expected=set(manifest['files'])
actual={p.relative_to(artifact_dir).as_posix() for p in artifact_dir.rglob('*') if p.is_file()}
missing=sorted(expected-actual);unexpected=sorted(actual-expected)
for rel,entry in manifest['files'].items():
 p=(artifact_dir/rel).resolve()
 if not p.is_relative_to(artifact_dir.resolve()):
  bad.append({'path':rel,'reason':'path escaped artifact directory'});continue
 if not p.is_file():
  continue
 b=p.read_bytes()
 if len(b)!=entry['bytes'] or sha(b)!=entry['sha256']:
  bad.append({'path':rel,'bytes_match':len(b)==entry['bytes'],'hash_match':sha(b)==entry['sha256']})
summary_path=artifact_dir/'summary.json';summary_bytes=summary_path.read_bytes();summary=json.loads(summary_bytes)
ci_path=run_dir/'ci-run.json';ci_bytes=ci_path.read_bytes();ci=json.loads(ci_bytes)
job_path=run_dir/'job.log';ci_log_path=run_dir/'ci.log';job=job_path.read_bytes();ci_log=ci_log_path.read_bytes();log=ci_log.decode('utf-8',errors='replace')
dispatch=json.loads((round_dir/'evidence/dispatch-20261030T195529Z/dispatch.json').read_bytes())
checks={
 'run_and_source_binding':int(ci['databaseId'])==int(rec['run'])==int(dispatch['run']['databaseId'])==41119180001 and ci['headSha']==rec['source_commit']==dispatch['source_commit']=='c68fb4c752cff8d937ef5960dcced2a0a64e3108',
 'runner_finished_and_group_complete':summary['complete'] is True and 'error' not in summary and summary['finished_at_utc']==rec['observed_runner_finished_at_utc'] and int(summary['run_id'])==41119180001 and summary['source_commit']==rec['source_commit'],
 'all_original_artifact_paths_match_manifest':not missing and not unexpected and not bad and len(expected)==133,
 'manifest_receipt_hash_matches':sha(manifest_bytes)==rec['artifact_manifest_sha256'] and manifest['artifact']['id']==rec['artifact_id']==13009300414,
 'summary_receipt_hash_matches':sha(summary_bytes)==rec['summary_sha256'],
 'job_log_bytes_match_and_final_cleanup_markers':sha(ci_log)==sha(job)==rec['job_log_sha256'] and ci_log==job and f"Artifact torchlean-{rec['run']}-receipts.zip successfully finalized" in log and 'Post job cleanup.' in log and 'Cleaning up orphan processes' in log,
 'terminal_time_order_consistent':rec['observed_runner_finished_at_utc'] < rec['observed_artifact_finalized_at_utc'] < rec['observed_post_cleanup_at_utc'] < rec['observed_orphan_cleanup_at_utc'],
 'platform_original_status_preserved_stale':ci['status']=='in_progress' and ci.get('conclusion','')==rec['observed_platform_conclusion']=='',
}
out={'round':'R28','scope':'INDEPENDENT_CI6_RUNNER_TERMINAL_EVIDENCE_REVIEW','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'runner_execution_terminal_verified':all(checks.values()),'run':41119180001,'source_commit':rec['source_commit'],'observed_platform_status':ci['status'],'observed_platform_conclusion':ci.get('conclusion',''),'observed_runner_finished_at_utc':summary['finished_at_utc'],'artifact_id':manifest['artifact']['id'],'artifact_manifest_sha256':sha(manifest_bytes),'summary_sha256':sha(summary_bytes),'job_log_sha256':sha(job),'job_log_matches_ci_log':job==ci_log,'artifact_file_count':len(expected),'missing_files':missing,'unexpected_files':unexpected,'file_hash_mismatches':bad,'checks':checks,'scope_note':'This review establishes runner terminality and complete artifact/log integrity only. It does not expose/interpret candidate scores, seed values, input records, or proof-binding output; those remain withheld until root completes the isolated full-group audit.'}
(round_dir/'verification/ci6-execution-terminal-review.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'runner_execution_terminal_verified':out['runner_execution_terminal_verified'],'failed_checks':[k for k,v in checks.items() if not v],'artifact_file_count':len(expected),'missing':len(missing),'unexpected':len(unexpected),'hash_mismatches':len(bad),'platform_status':ci['status'],'platform_conclusion':ci.get('conclusion',''),'summary_complete':summary['complete']},indent=2))
