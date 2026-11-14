from pathlib import Path
import datetime,hashlib,importlib.util,json,re,sys

sys.dont_write_bytecode=True
root=Path.cwd();round_dir=root/'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
batch=round_dir/'development/ci-bridge/batch6';plan_path=round_dir/'ci-plan.json'
plan=json.loads(plan_path.read_bytes());request=json.loads((round_dir/'CI-REQUEST.json').read_bytes());status=json.loads((round_dir/'development-status.json').read_bytes())
freeze=json.loads((batch/'freeze.json').read_bytes());base=(round_dir/'competition-state/source-private/official-36.lean').read_bytes()
sha=lambda b:hashlib.sha256(b).hexdigest()

def load(path,name):
 spec=importlib.util.spec_from_file_location(name,path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

norm_path=batch/'build_norm26_36.py';zero_path=batch/'build_mixer36_input_zero_cost.py'
norm=load(norm_path,'ci6_norm_builder_readonly');zero=load(zero_path,'ci6_zero_builder_readonly')
norm_entry=next(x for x in plan['candidates'] if x['name']=='norm26-standard-confirmation')
zero_entry=next(x for x in plan['candidates'] if x['name']=='norm26-input-zero-native-experiment')
norm_candidate=norm.transform(base,36,norm_entry['variant'])
zero_candidate=zero.transform(base,36,zero_entry['variant'])

refresh=round_dir/'competition-state/refresh-20261030T195212Z';receipt=json.loads((refresh/'receipt.json').read_bytes())
receipt_items={Path(x['path']).name:x for x in receipt['receipts'] if 'path' in x}
raw_files={p.name:p.read_bytes() for p in refresh.glob('*.raw')}
champ_raw=raw_files['champions-mixer.raw'];boards_raw=raw_files['boards.raw']
champ=json.loads(champ_raw);boards=json.loads(boards_raw)
current=next(x for x in champ['champions'] if x['current'] is True);mixer_board=next(x for x in boards['boards'] if x['id']=='mixer')

prior_root=round_dir/'evidence/41107618451/download-61071bff514a4286bc113fab65196ffd'
prior_summary_path=prior_root/'summary.json';prior_gate_path=prior_root/'public36-norm26/full-gate-verdict.json'
prior_summary=json.loads(prior_summary_path.read_bytes());prior_gate=json.loads(prior_gate_path.read_bytes())
prior_audit=json.loads((round_dir/'verification/audit-native-run-41107618451.json').read_bytes())
prior_gate_audit=next(x for x in prior_audit['full_gates'] if x['name']=='public36-norm26')
norm_receipt=round_dir/'development/native/mixer36-input-zero-cost-receipt.json'
norm_receipt_json=json.loads(norm_receipt.read_bytes())
local_zero=round_dir/'development/native/source-private/mixer36-input-zero-cost-Kernel.lean'
native_zero_path=round_dir/'development/native/build_mixer36_input_zero_cost.py'
freeze_by_name={x['name']:x for x in freeze['sources']}

prior_seeds=set()
for r in (round_dir/'evidence').iterdir():
 if not r.is_dir():continue
 for p in r.glob('download-*/plan.json'):
  try:prior_seeds.update(json.loads(p.read_bytes()).get('seeds',[]))
  except Exception:pass

def has_decl(data,name):
 return re.search(rb'(?m)^(?:@\[[^\n]*?\]\s+)?(?:lemma|theorem|def|abbrev|structure|instance)\s+'+re.escape(name.encode())+rb'\b',data) is not None

checks={
 'official36_source_hash_matches_reference':sha(base)==plan['reference']['sha256']=='595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b',
 'norm26_rebuild_exact_and_bounded':sha(norm_candidate)==norm_entry['sha256'] and len(norm_candidate)==norm_entry['bytes']<=256000,
 'inputzero_rebuild_exact_and_bounded':sha(zero_candidate)==zero_entry['sha256']==norm_receipt_json['candidate_sha256'] and len(zero_candidate)==zero_entry['bytes']==norm_receipt_json['candidate_bytes']<=256000,
 'inputzero_packaged_kernel_equals_recipe_output':local_zero.is_file() and sha(local_zero.read_bytes())==sha(zero_candidate)==zero_entry['sha256'],
 'candidate_recipe_hashes_match_plan':sha(norm_path.read_bytes())==norm_entry['patch_script_sha256']=='fe05b956373f898af7e09ca43924583af81c56a357e98f0b4e674f3c9de84c48' and sha(zero_path.read_bytes())==zero_entry['patch_script_sha256'],
 'inputzero_recipe_packaging_change_only':sha(native_zero_path.read_bytes())==norm_receipt_json['recipe_sha256'] and native_zero_path.read_text(encoding='utf-8').replace('path=ROUND/"research/cross-source/build_norm26_36.py";assert sha(path.read_bytes())==NORM_RECIPE','path=HERE/"build_norm26_36.py";assert sha(path.read_bytes())==NORM_RECIPE')==zero_path.read_text(encoding='utf-8'),
 'freeze_sources_match_root_plan':all(freeze_by_name[x['name']]['sha256']==x['sha256'] and freeze_by_name[x['name']]['bytes']==x['bytes'] and freeze_by_name[x['name']]['sample_role']==x['sample_role'] for x in plan['candidates']),
 'norm26_full_gate_prior_same_exact_source_passed':norm_entry['full_gate'] is False and norm_entry['declares_correct'] is True and sha(norm_candidate)==norm_entry['sha256']==prior_gate_audit['source_sha256'] and prior_gate['passed'] is True and prior_gate['stage']=='axioms',
 'prior_norm26_gate_receipts_match_plan_and_pass':sha(prior_summary_path.read_bytes())==norm_entry['exact_prior_original_gate']['summary_sha256'] and sha(prior_gate_path.read_bytes())==norm_entry['exact_prior_original_gate']['verdict_sha256'] and prior_gate_audit['source_sha256']==norm_entry['sha256'] and prior_gate_audit['exit_code']==0 and prior_gate['passed'] is True and prior_gate['stage']=='axioms' and prior_gate['verifier_fingerprint']==prior_gate['verifier_fingerprint_end']==norm_entry['exact_prior_original_gate']['verifier_fingerprint'],
 'inputzero_nativeonly_no_correct':zero_entry['full_gate'] is False and zero_entry['declares_correct'] is False and not has_decl(zero_candidate,'correct'),
 'zero_no_correct_scope_and_freeze':zero_entry['sample_role']=='EXPERIMENT_ONLY_NO_CORRECT_NOT_ADOPTABLE' and freeze['sources'][1]['sample_role']=='EXPERIMENT_ONLY_NO_CORRECT_NOT_ADOPTABLE',
 'new_seed_pair_unique_and_previously_unseen':len(plan['seeds'])==2 and len(set(plan['seeds']))==2 and not(set(plan['seeds'])&prior_seeds),
 'standard_confirmation_group_isolation_bound':request['confirmation_isolation']==plan['confirmation_isolation']=='OnlyDroot/verificationmayinspectseed/input/resultbeforewholebatchcomplete; researchusesprefreeze materials' and status['confirmation_isolation']==plan['confirmation_isolation'],
 'fresh_current_mixer_response_hashes_match_plan_and_receipt':sha(champ_raw)==plan['champion']['champion_response_sha256']==receipt_items['champions-mixer.raw']['sha256'] and sha(boards_raw)==plan['champion']['boards_response_sha256']==receipt_items['boards.raw']['sha256'] and receipt['state']=='LIVE_ALL_SIX_BEFORE_STANDARD_FREEZE' and receipt_items['champions-mixer.raw']['status']==200 and receipt_items['boards.raw']['status']==200,
 'current_mixer_identity_ratio_publication_match':current['submission']==plan['champion']['submission']==56 and current['source_sha256']==plan['champion']['source_sha256'] and current['ratio']==plan['champion']['current_champion_over_calibration'] and champ['publication_hash']==boards['publication_hash']==plan['champion']['publication_hash'] and mixer_board['current_promotion_id']==current['promotion_id'],
 'root_request_plan_candidate_and_status_bind':sha(plan_path.read_bytes())==request['plan_sha256']=='68c6633d07b021d4de3399cd1be3a5555101250292b3faf62b929d2e5559884d' and [x['sha256'] for x in plan['candidates']]==request['candidate_hashes'] and request['state']=='READY' and request['batch']==6 and status['state']=='FINAL_STANDARD_CONFIRMATION_READY_RESEARCH_CONTINUES_TO_CUTOFF' and status['active_CI']==[],
 'standard_timing_spec_exact':plan['measurement_mode']=='standard' and plan['driver_seconds']==1800,
 'confirmation_group_pair_count_freeze':freeze['expected_pairs_each']==792 and freeze['timing']=='Originalstandard11rounds/3inner/50ms',
 'current_deadline_is_preserved':plan['stop_new_research_utc']=='2026-10-30T20:15:58Z' and plan['start_cutoff_utc']=='2026-10-30T20:15:00+00:00',
}
out={'round':'R28','scope':'READ_ONLY_CI6_STANDARD_CONFIRMATION_PREFLIGHT','captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'plan_sha256':sha(plan_path.read_bytes()),'freeze_sha256':sha((batch/'freeze.json').read_bytes()),'candidates':[{'name':norm_entry['name'],'sha256':sha(norm_candidate),'bytes':len(norm_candidate),'full_gate_in_new_run':norm_entry['full_gate'],'declares_correct':norm_entry['declares_correct'],'prior_exact_gate':{'summary_sha256':sha(prior_summary_path.read_bytes()),'verdict_sha256':sha(prior_gate_path.read_bytes()),'stage':prior_gate['stage'],'passed':prior_gate['passed'],'verifier_fingerprint':prior_gate['verifier_fingerprint']}},{'name':zero_entry['name'],'sha256':sha(zero_candidate),'bytes':len(zero_candidate),'full_gate':zero_entry['full_gate'],'declares_correct':zero_entry['declares_correct'],'role':zero_entry['sample_role']}],'restricted_seed_group':{'seeds':plan['seeds'],'prior_seed_count':len(prior_seeds),'unique_and_unseen':checks['new_seed_pair_unique_and_previously_unseen'],'visibility':'Only Droot/verification may inspect before full group completion; do not copy values to general handoff.'},'champion_snapshot':{'at_utc':plan['champion']['at_utc'],'publication':plan['champion']['publication_hash'],'champion':current['submission'],'ratio':current['ratio'],'response_sha256':sha(champ_raw),'boards_sha256':sha(boards_raw)},'dispatch_window':{'not_after':plan['dispatch_not_after_utc'],'start_cutoff':plan['start_cutoff_utc'],'driver_seconds':plan['driver_seconds'],'shared_deadline':plan['stop_new_research_utc']},'checks':checks,'checks_passed':all(checks.values()),'correctness_boundary':'Norm26 is the exact source previously accepted by the original all12 gate; CI6 omits duplicate full gate and uses a fresh standard performance confirmation. Input-zero is separate NativeOnly experiment with no correct, not adoptable regardless of cost result. No proofs are inherited by the input-zero experiment.'}
(round_dir/'verification/audit-ci6-preflight.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':out['checks_passed'],'failed_checks':[k for k,v in checks.items() if not v],'plan_sha256':out['plan_sha256'],'candidates':out['candidates'],'snapshot':out['champion_snapshot'],'restricted_seed_group':{'count':len(plan['seeds']),'unique_and_unseen':checks['new_seed_pair_unique_and_previously_unseen']},'dispatch_window':out['dispatch_window']},indent=2))
