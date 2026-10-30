from pathlib import Path
import hashlib, importlib.util, json, re, sys
sys.dont_write_bytecode=True
ROOT=Path.cwd(); ROUND=ROOT/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'; RUN=41099255272
E=ROUND/'evidence'/str(RUN); dispatch=json.loads((ROUND/'evidence/dispatch-20261030T172922Z/dispatch.json').read_bytes())
api_run=json.loads((E/'ci-run.json').read_bytes()); observed=(E/'ci-run-observed-inprogress.json').read_bytes()
attempt=json.loads((E/f'actions-runs-{RUN}-attempts-1.json').read_bytes())
check=json.loads((E/'check-suites-111411837243.json').read_bytes())
fresh_status=json.loads((E.parent/'ci1-fresh-status-174756.json').read_bytes())
rec=json.loads((E/'execution-reconciliation.json').read_bytes())
outer_manifest=json.loads((E/'original-artifact-hashes.json').read_bytes()); folder=E/outer_manifest['directory']
cli_art=json.loads((E/'artifacts.json').read_bytes())['artifacts'][0]
api_art=json.loads((E/f'actions-runs-{RUN}-artifacts.json').read_bytes())['artifacts'][0]
summary_raw=(folder/'summary.json').read_bytes(); summary=json.loads(summary_raw); plan_raw=(folder/'plan.json').read_bytes(); plan=json.loads(plan_raw)
log_raw=(E/'ci.log').read_bytes(); log=log_raw.decode('utf-8')
spec=importlib.util.spec_from_file_location('fixed_r28_audit',ROUND/'development/ci-bridge/audit-native.py')
fixed=importlib.util.module_from_spec(spec);spec.loader.exec_module(fixed)
outer=fixed.base.audit_tree(folder,outer_manifest['files'])
inner_manifest=json.loads((folder/'file-hashes.json').read_bytes())
inner=fixed.base.audit_tree(folder,inner_manifest,excluded=('file-hashes.json',))
reference_flags=fixed.flags(folder/'calibration')

# Reconcile file/hash and workflow identity without rewriting stale platform responses.
plan_rel=ROUND.relative_to(ROOT).as_posix()+'/ci-plan.json'
plan_hash=hashlib.sha256(plan_raw).hexdigest()
ci_snapshots={
 'run':api_run.get('status')=='in_progress' and api_run.get('conclusion') in ('',None),
 'run_snapshot_equals_observed_inprogress_bytes':hashlib.sha256((E/'ci-run.json').read_bytes()).hexdigest()==hashlib.sha256(observed).hexdigest(),
 'attempt':attempt.get('status')=='in_progress' and attempt.get('id')==RUN and attempt.get('head_sha')==dispatch['source_commit'],
 'check_suite':check.get('status')=='in_progress' and check.get('id')==fresh_status.get('check_suite_id') and check.get('head_sha')==dispatch['source_commit'],
 'fresh_run_status_snapshot_stale':fresh_status.get('id')==RUN and fresh_status.get('status')=='in_progress' and fresh_status.get('head_sha')==dispatch['source_commit'],
 'stale_api_updated_before_runner_finish':bool(api_run.get('updatedAt') and api_run['updatedAt'] < rec['observed_runner_finished_at_utc']),
 'root_status_still_lists_active_run':any(x['run']==RUN for x in json.loads((ROUND/'development-status.json').read_bytes())['active_CI']),
}
artifact_meta={
 'cli_api_id_match':cli_art['id']==api_art['id']==outer_manifest['artifact']['id']==rec['artifact_id'],
 'artifact_name_match':cli_art['name']==api_art['name']==f'torchlean-{RUN}-receipts',
 'workflow_run_match':outer_manifest['artifact']['workflow_run']['id']==RUN,
 'source_commit_match':outer_manifest['artifact']['workflow_run']['head_sha']==dispatch['source_commit']==api_run['headSha']==summary['source_commit']==rec['source_commit'],
 'plan_hash_matches_dispatch':plan_hash==dispatch['frozen_files'][plan_rel],
 'plan_hash_matches_reconciliation':plan_hash==hashlib.sha256((ROUND/'ci-plan.json').read_bytes()).hexdigest(),
}
# Correct candidate/plan/run bindings (keep separate from patch-recipe hash).
candidate_sha=plan['candidates'][0]['sha256']
artifact_meta['candidate_hash_matches_frozen_plan_and_gate']=candidate_sha==summary['full_gates'][0]['source_sha256']==json.loads((ROUND/'CI-REQUEST.json').read_bytes())['candidate_sha256']
artifact_meta['frozen_candidate_recipe_and_patch_present'] = plan['candidates'][0]['patch_script_sha256']==dispatch['frozen_files'][plan['candidates'][0]['patch_script']]
artifact_meta['official_commit_matches'] = summary['official_commit']==plan['official_commit']=='9d4640e4d92b7f29611643e54601d5a114dc70b1'
artifact_meta['benchmark_identity_matches_expected'] = summary['benchmark_identity']=='6684da73f5dd5d1d4fdf5ab12b296e39202f6ef143b6b412a312689aa6f9b06b'
artifact_meta['proof_identity_matches_expected'] = summary['proof_identity']=='3a69968c7210ab18b325047e518ddfa942e642e21268a241e8693b075377bee6'

# Runner process, returned failure, artifact finalization, and post-job cleanup markers.
lines=log.splitlines()
runner_exit=next((x for x in lines if 'Process completed with exit code 1.' in x),None)
runner_summary=next((x for x in lines if '"complete": false' in x),None)
artifact_final=next((x for x in lines if f'Artifact torchlean-{RUN}-receipts.zip successfully finalized' in x),None)
post_cleanup=next((x for x in lines if 'Post job cleanup.' in x),None)
orphan_cleanup=next((x for x in lines if 'Cleaning up orphan processes' in x),None)
terminal_evidence={
 'runner_process_exit1_logged':runner_exit is not None,
 'runner_summary_complete_false_logged':runner_summary is not None,
 'artifact_finalized_logged':artifact_final is not None,
 'post_job_cleanup_logged':post_cleanup is not None,
 'orphan_process_cleanup_logged':orphan_cleanup is not None,
 'runner_finished_at_matches_summary':summary['finished_at_utc']==rec['observed_runner_finished_at_utc'],
 'job_log_hash_matches_reconciliation':hashlib.sha256(log_raw).hexdigest()==rec['job_log_sha256'],
 'summary_hash_matches_reconciliation':hashlib.sha256(summary_raw).hexdigest()==rec['summary_sha256'],
 'artifact_manifest_hash_matches_reconciliation':hashlib.sha256((E/'original-artifact-hashes.json').read_bytes()).hexdigest()==rec['artifact_manifest_sha256'],
 'artifact_digest_matches_upload_log_and_api':(outer_manifest['artifact']['digest']=='sha256:'+re.search(r'SHA256 digest of uploaded artifact zip is ([0-9a-f]{64})',log).group(1)==api_art['digest']),
 'runner_terminal_state_is_failure_stale_platform':rec['state']=='RUNNER_EXECUTION_FINISHED_FAILURE_PLATFORM_METADATA_STALE' and rec['platform_status']=='in_progress' and rec['platform_conclusion']=='',
 'runner_finished_before_artifact_finalized':rec['observed_runner_finished_at_utc'] < rec['observed_artifact_finalized_at_utc'],
}

# Exact proof boundary: the candidate gate rejected this hash at statement; no candidate timing row exists.
gate=summary['full_gates'][0]; verdict=gate['verdict']; gate_log=(folder/'public11-mapidx-add-v1/full-gate-raw-statement.log').read_text(encoding='utf-8',errors='replace')
results=summary['results']; candidate_measurements=[p.relative_to(folder).as_posix() for p in folder.rglob('*') if p.is_file() and 'public11-mapidx-add-v1' in p.name and 'measurement.json' in p.name]
proof={
 'candidate_sha256':candidate_sha,
 'gate_source_matches_candidate':gate['source_sha256']==candidate_sha,
 'original_full_gate_was_run':bool(plan['candidates'][0].get('full_gate')),
 'full_gate_exit_code':gate['exit_code'],'stage':verdict['stage'],'passed':verdict['passed'],'reason':verdict['reason'],
 'statement_log_contains_no_goals':('No goals to be solved' in gate_log and 'Submission.lean:2103:1' in gate_log),
 'verifier_fingerprint_stable':verdict['verifier_fingerprint']==verdict['verifier_fingerprint_end'],
 'gate_not_exhausted':verdict['exhausted'] is False,
 'candidate_build_or_measurement_result_present':any(x.get('name')=='public11-mapidx-add-v1' for x in results),
 'candidate_measurement_files':candidate_measurements,
 'classification':'EXACT_CANDIDATE_PROOF_FAILED_AT_STATEMENT; correctness unproved; no performance multiplier (UNKNOWN, not zero)',
}

# Reference-only profile integrity and route-ceiling screen; not candidate timing.
profile=json.loads((folder/'cost-profile/profile.json').read_bytes()); profile_rows=[]; raw_profile_valid=True
for row in profile['rows']:
    fn=folder/'cost-profile'/(row['cell'].replace(':','_')+'.raw'); raw=fn.read_text(encoding='utf-8',errors='replace')
    metrics={}
    good=[]
    for line in raw.splitlines():
        f=line.split()
        if f and f[0]=='R27_PROFILE': metrics[f[1]]={'calls':int(f[2]),'inclusive_ns':int(f[3]),'exclusive_ns':int(f[4])}
        elif len(f)==4 and f[1]=='true': good.append(f[0])
        elif len(f)==2 and f[1]=='start': continue
        else: raw_profile_valid=False
    expected=row['instrumented_kernel_entry_times']
    metric_match=(metrics==expected)
    check_count=(len(good)==row['checksum_pairs']==6)
    raw_profile_valid=raw_profile_valid and metric_match and check_count
    profile_rows.append({'cell':row['cell'],'checksums_in_json':row['checksum_pairs'],'checksums_in_raw':len(good),'metrics_match_raw':metric_match,'add_relu_share':row['share_within_profiled_entries']['add_relu'],'add_relu_calls':expected['add_relu']['calls'],'add_relu_exclusive_ns':expected['add_relu']['exclusive_ns']})
required_reduction=1.0-0.97*plan['champion']['current_champion_over_calibration']
max_add_relu_share=max(x['add_relu_share'] for x in profile_rows)
profile_result={
 'state':summary['cost_profile']['state'],'rows':len(profile_rows),'checksum_pairs_in_json':sum(x['checksums_in_json'] for x in profile_rows),
 'raw_cell_outputs_match_json':raw_profile_valid,'source_sha256_matches_public_reference':profile['source_sha256']==plan['reference']['sha256'],
 'control_binary_matches_reference':profile['control_binary_sha256']==results[0]['binary_sha256'],
 'profile_scope':profile['scope'],'profile_rows':profile_rows,'required_whole_model_reduction_to_0_97':required_reduction,
 'max_add_relu_share_of_profiled_entries':max_add_relu_share,
 'profile_negative_screen':'ALL_SIX_CELLS_BELOW_REQUIRED_REDUCTION; reference-only single-run instrumented ceiling screen; not standard timing or candidate result',
}

# Reuse the fixed R28 auditor's raw-tree and reference-flag checks; no scorer is run because there are no candidate measurements.
source_receipt=json.loads((folder/'source-fetch-11.json').read_bytes())
fixed_checks={
 'outer':outer,'inner':inner,'reference_flag_check':fixed.flags(folder/'calibration'),
 'source_fetch':{'status':source_receipt.get('status'),'bytes':source_receipt.get('bytes'),'sha256':source_receipt.get('sha256'),'matches_plan':source_receipt.get('sha256')==plan['reference']['sha256'] and source_receipt.get('status')==200},
 'api_status':{'run':api_run['status'],'conclusion':api_run.get('conclusion'),'run_id':api_run['databaseId'],'head_sha':api_run['headSha'],'run_response_sha256':hashlib.sha256((E/'ci-run.json').read_bytes()).hexdigest(),'observed_inprogress_sha256':hashlib.sha256(observed).hexdigest(),'run_responses_byte_identical':(E/'ci-run.json').read_bytes()==observed,'attempt_status':attempt['status'],'attempt_updated_at':attempt['updated_at'],'fresh_run_status':fresh_status.get('status'),'fresh_run_updated_at':fresh_status.get('updated_at'),'fresh_check_suite_id':fresh_status.get('check_suite_id'),'check_suite_status':check['status'],'check_suite_updated_at':check['updated_at']},
 'artifact':{'id':outer_manifest['artifact']['id'],'name':outer_manifest['artifact']['name'],'size_bytes':outer_manifest['artifact']['size_in_bytes'],'digest':outer_manifest['artifact']['digest'],'created_at':outer_manifest['artifact']['created_at'],'run_id':outer_manifest['artifact']['workflow_run']['id'],'outer_entries':len(outer_manifest['files']),'inner_entries':len(inner_manifest),'outer_status':outer['status'],'inner_status':inner['status']},
 'terminal_evidence':terminal_evidence,'proof':proof,'reference_profile':profile_result,
 'reconciliation_sha256':hashlib.sha256((E/'execution-reconciliation.json').read_bytes()).hexdigest(),
}
checks={
 'dispatch_source_run_commit':dispatch['source_commit']==api_run['headSha']==rec['source_commit']==str(summary['source_commit']),
 'plan_and_candidate_binding':artifact_meta['plan_hash_matches_dispatch'] and artifact_meta['candidate_hash_matches_frozen_plan_and_gate'],
 'outer_manifest':outer['status']=='PASS','inner_manifest':inner['status']=='PASS',
 'run_api_preserved_stale':ci_snapshots['run'] and ci_snapshots['run_snapshot_equals_observed_inprogress_bytes'] and ci_snapshots['attempt'] and ci_snapshots['check_suite'],
 'actual_runner_terminal':all(terminal_evidence[k] for k in ['runner_process_exit1_logged','runner_summary_complete_false_logged','artifact_finalized_logged','post_job_cleanup_logged','orphan_process_cleanup_logged','runner_finished_at_matches_summary','job_log_hash_matches_reconciliation','summary_hash_matches_reconciliation','artifact_manifest_hash_matches_reconciliation','artifact_digest_matches_upload_log_and_api','runner_terminal_state_is_failure_stale_platform']),
 'exact_candidate_failed_gate':proof['gate_source_matches_candidate'] and proof['full_gate_exit_code']==1 and proof['stage']=='statement' and not proof['passed'] and proof['statement_log_contains_no_goals'] and not proof['candidate_build_or_measurement_result_present'] and not proof['candidate_measurement_files'],
 'reference_profile_complete':profile_result['state']=='COMPLETE_INSTRUMENTED_COST_DISCRIMINATOR' and profile_result['rows']==6 and profile_result['checksum_pairs_in_json']==36 and profile_result['raw_cell_outputs_match_json'],
 'reference_source_matches':source_receipt.get('sha256')==plan['reference']['sha256'],
 'stale_platform_state_not_rewritten':api_run['status']=='in_progress' and rec['platform_status']=='in_progress' and ci_snapshots['run_snapshot_equals_observed_inprogress_bytes'],
}
review={
 'round':'R28','run':RUN,'source_commit':dispatch['source_commit'],'scope':'INDEPENDENT_RUNNER_TERMINAL_AND_ARTIFACT_AUDIT; exact candidate gate failed; no score',
 'captured_at_utc':__import__('datetime').datetime.now(__import__('datetime').timezone.utc).isoformat(),
 'runner_execution_terminal_verified':all(checks[k] for k in ['actual_runner_terminal','outer_manifest','inner_manifest','dispatch_source_run_commit']),
 'platform_status_stale':api_run['status']=='in_progress' and rec['platform_status']=='in_progress',
 'api_responses_preserved':ci_snapshots['run_snapshot_equals_observed_inprogress_bytes'],
 'slot_release_eligible':all(checks[k] for k in ['actual_runner_terminal','outer_manifest','inner_manifest','dispatch_source_run_commit']),
 'do_not_cancel_or_retry_old_run':True,'do_not_rewrite_platform_status':True,
 'candidate_sha256':candidate_sha,'candidate_proof':proof,'candidate_measurement':'NONE; performance multiplier UNKNOWN, not zero',
 'reference_profile':profile_result,'artifact_and_execution':fixed_checks,'checks':checks,'checks_passed':all(checks.values()),
 'next':'Root may release one compute slot based on verified runner exit/artifact finalization/cleanup while retaining platform status as STALE_IN_PROGRESS; any next candidate needs a new source hash/full all12 gate and its own independent standard confirmation.'
}
out=ROUND/'verification/ci1-execution-terminal-review.json';out.write_text(json.dumps(review,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':review['checks_passed'],'runner_execution_terminal_verified':review['runner_execution_terminal_verified'],'platform_status_stale':review['platform_status_stale'],'slot_release_eligible':review['slot_release_eligible'],'outer':outer['status'],'outer_files':outer['files'],'inner':inner['status'],'inner_files':inner['files'],'candidate_proof':proof,'profile':{'rows':profile_result['rows'],'checksum_pairs':profile_result['checksum_pairs_in_json'],'max_add_relu_share':max_add_relu_share,'required_reduction':required_reduction,'raw_rows_match':raw_profile_valid}},indent=2))
