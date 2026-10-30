from pathlib import Path
import datetime, hashlib, importlib.util, json, re, sys

sys.dont_write_bytecode = True
root = Path.cwd()
round_dir = root / 'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
batch = round_dir / 'development/ci-bridge/batch4'
plan_path = batch / 'plan-draft.json'
freeze_path = batch / 'cost-source-freeze.json'
root_plan_path = round_dir / 'ci-plan.json'
root_request_path = round_dir / 'CI-REQUEST.json'
root_status_path = round_dir / 'development-status.json'
plan = json.loads(plan_path.read_bytes())
freeze = json.loads(freeze_path.read_bytes())
root_plan = json.loads(root_plan_path.read_bytes())
root_request = json.loads(root_request_path.read_bytes())
root_status = json.loads(root_status_path.read_bytes())
base = (round_dir / 'competition-state/source-private/official-53.lean').read_bytes()
sha = lambda data: hashlib.sha256(data).hexdigest()

def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

point_path = batch / 'build_pointwise128_frozen.py'
zero_v2_path = batch / 'build_zero_mobile_v2.py'
zero_native_path = batch / 'build_zero_runtime_native.py'
point = load(point_path, 'ci4_final_point_readonly')
zero_v2 = load(zero_v2_path, 'ci4_final_v2_readonly')
zero_native = load(zero_native_path, 'ci4_final_native_readonly')
by_name = {x['name']: x for x in plan['candidates']}
zero_plan = by_name['public53-zero-runtime-native-only']
point_plan = by_name['public53-pointwise128-nat-native-only']
candidate_zero = zero_native.transform(base, 53, zero_plan['variant'])
candidate_point = point.transform(base, 53, point_plan['variant'])
proof_v2 = zero_v2.transform(base, 53, 'zero-both-proof-v2')
if isinstance(proof_v2, tuple):
    proof_v2 = proof_v2[0]
zero_baseline = zero_native.make_zero(base, 53, 'zero-both')

def command_blocks(data):
    text = data.decode('utf-8')
    rx = re.compile(r'(?m)^(?:@\[[^\n]*?\]\s+)?(?:private\s+)?(lemma|theorem|def|abbrev|structure|instance|set_option|local|open|namespace|end)\b')
    matches = list(rx.finditer(text))
    out = []
    for i, m in enumerate(matches):
        end = matches[i+1].start() if i+1 < len(matches) else len(text)
        name_match = re.match(r'\s+([A-Za-z][A-Za-z0-9_]*)', text[m.end():])
        name = name_match.group(1) if name_match and m.group(1) in {'lemma','theorem','def','abbrev','structure','instance'} else None
        out.append({'kind': m.group(1), 'name': name, 'text': text[m.start():end]})
    return out

candidate_blocks = command_blocks(candidate_zero)
proof_blocks = command_blocks(proof_v2)
baseline_blocks = command_blocks(zero_baseline)
runtime_kinds = {'def','abbrev','structure','instance'}
proof_kinds = {'lemma','theorem'}
candidate_runtime = [(b['kind'],b['name'],sha(b['text'].encode())) for b in candidate_blocks if b['kind'] in runtime_kinds]
proof_runtime = [(b['kind'],b['name'],sha(b['text'].encode())) for b in proof_blocks if b['kind'] in runtime_kinds]
candidate_proofs = {b['name']: sha(b['text'].encode()) for b in candidate_blocks if b['kind'] in proof_kinds}
baseline_proofs = {b['name']: sha(b['text'].encode()) for b in baseline_blocks if b['kind'] in proof_kinds}
removed_proofs = sorted(set(baseline_proofs) - set(candidate_proofs))
retained_proof_changes = sorted(n for n in set(candidate_proofs) & set(baseline_proofs) if candidate_proofs[n] != baseline_proofs[n])
all_decl_names = {b['name'] for b in candidate_blocks if b['name']}
removed_set=set(removed_proofs)
closure_refs={b['name']:sorted(set(re.findall(r'(?<![A-Za-z0-9_])(?:Submission\.)?([A-Za-z][A-Za-z0-9_]*)',b['text'])) & removed_set) for b in candidate_blocks if b['name'] and b['kind'] in (runtime_kinds|proof_kinds)}
closure_refs={name:refs for name,refs in closure_refs.items() if refs}

helper_results=[]
for h in plan['helpers']:
    produced, root_name = zero_v2.prefix(base, h['variant'])
    helper_results.append({'name':h['name'],'sha256':sha(produced),'planned_sha256':h['sha256'],'bytes':len(produced),'planned_bytes':h['bytes'],'root':'Submission.'+root_name,'planned_roots':h['helper_roots'],'seconds':h['seconds'],'matches':sha(produced)==h['sha256'] and len(produced)==h['bytes'] and root_name in [x.split('.')[-1] for x in h['helper_roots']]})

runner_path = round_dir / 'development/ci-bridge/runner.py'
runner = runner_path.read_text(encoding='utf-8')
probe_path = round_dir / 'development/ci-bridge/code-diagnostics.py'
latest_request_path = round_dir / 'requests/185600-ci4-cost-only-final-draft.md'
latest_request = latest_request_path.read_text(encoding='utf-8')
champion_snapshot = round_dir / 'competition-state/refresh-20261030T181518Z'
champion_receipt = json.loads((champion_snapshot / 'receipt.json').read_bytes())
champion_raw = (champion_snapshot / 'champions-mobilenet.raw').read_bytes()
boards_raw = (champion_snapshot / 'boards.raw').read_bytes()
champion_response = json.loads(champion_raw)
boards_response = json.loads(boards_raw)
current_row = next(x for x in champion_response['champions'] if x['current'] is True)
mobile_board = next(x for x in boards_response['boards'] if x['id'] == 'mobilenet')
receipt_by_path = {Path(x['path']).name:x for x in champion_receipt['receipts'] if 'path' in x}
checks={
    'official53_base_matches_pin': sha(base)==plan['reference']['sha256']=='3dbe2f708299e6ee13e512a0f639eae681497ffaf01132330d92071581f7a9cb',
    'zero_candidate_rebuild_matches_plan_and_freeze': sha(candidate_zero)==zero_plan['sha256']==freeze['zero_sha256'] and len(candidate_zero)==zero_plan['bytes']<=256000,
    'pointwise_rebuild_matches_plan': sha(candidate_point)==point_plan['sha256'] and len(candidate_point)==point_plan['bytes']<=256000,
    'runtime_blocks_byte_identical_to_zero_v2': candidate_runtime==proof_runtime and len(candidate_runtime)==freeze['zero_runtime_ordered_blocks']==158,
    'proof_pruning_exactly_12_without_rewriting_retained_proofs': len(removed_proofs)==freeze['removed_proof_count']==12 and not retained_proof_changes and all(n in removed_proofs for n in ['qCtx8','qCtx14','correct']),
    'retained_runtime_and_proofs_have_no_removed_symbol_references': not closure_refs,
    'no_correct_declaration_or_forbidden_constructs': 'correct' not in all_decl_names and not re.search(rb'\b(sorry|admit|axiom|unsafe|native_decide|implemented_by|extern)\b',candidate_zero),
    'both_candidates_nativeonly': all(x.get('full_gate') is False and x.get('declares_correct') is False for x in plan['candidates']),
    'only_two_cost_candidates_and_no_whole_proof_gate': len(plan['candidates'])==2 and not any(x.get('full_gate') for x in plan['candidates']) and 'public53-zero-proof-v2' not in by_name,
    'owned_recipe_sha_matches_and_has_no_nonstdlib_dependencies': sha(zero_native_path.read_bytes())==zero_plan['patch_script_sha256'] and 'socket' not in zero_native_path.read_text(encoding='utf-8') and 'urllib' not in zero_native_path.read_text(encoding='utf-8'),
    'pointwise_recipe_sha_matches': sha(point_path.read_bytes())==point_plan['patch_script_sha256'],
    'helpers_rebuild_hash_size_root_and_120s': len(helper_results)==2 and all(x['matches'] and x['seconds']<=120 for x in helper_results),
    'helper_caps_exceptions_and_skip_boundary_resolved': "min(120,entry.get('seconds',120)," in runner and "SKIPPED_AFTER_BOUNDED_HELPER_FAILED" in runner and 'except Exception as error:' in runner[runner.find("for entry in plan.get('helpers',[]):"):runner.find("if plan.get('mode')=='helpers-only':")],
    'probe_hash_matches_plan': sha(probe_path.read_bytes())==plan['code_probe_sha256'],
    'champion_and_boards_response_hashes_match_plan_receipts': sha(champion_raw)==plan['champion']['champion_response_sha256']==receipt_by_path['champions-mobilenet.raw']['sha256'] and sha(boards_raw)==plan['champion']['boards_response_sha256']==receipt_by_path['boards.raw']['sha256'] and champion_receipt['state']=='LIVE_ALL_SIX',
    'plan_current_mobile_identity_ratio_and_publication_bind': current_row['submission']==plan['champion']['submission']==57 and current_row['source_sha256']==plan['champion']['source_sha256'] and current_row['ratio']==plan['champion']['current_champion_over_calibration'] and champion_response['publication_hash']==boards_response['publication_hash']==plan['champion']['publication_hash'] and mobile_board['current_promotion_id']==current_row['promotion_id'],
    'final_request_reflects_two_cost_sources_and_held_whole_proof': '474eff80' in latest_request and '5ecfdd8c' in latest_request and '不执行whole600 gate' in latest_request and '85eb仅保留' in latest_request,
    'freeze_state_excludes_full_gate': freeze['state']=='TWO_COST_SOURCES_ONLY_NO_FULL_GATE_SELECTED' and freeze['zero_no_correct'] is True and freeze['zero_runtime_ordered_blocks_identical'] is True,
    'root_ci_request_matches_exact_root_plan': root_request['state']=='READY' and root_request['batch']==4 and sha(root_plan_path.read_bytes())==root_request['plan_sha256'] and [x['sha256'] for x in root_plan['candidates']]==root_request['candidate_hashes'] and [x['name'] for x in root_plan['helpers']]==root_request['helpers'],
    'root_dispatch_plan_is_two_nativeonly_cost_entries': len(root_plan['candidates'])==2 and all(x.get('full_gate') is False and x.get('declares_correct') is False for x in root_plan['candidates']) and not any(x.get('full_gate') for x in root_plan['candidates']),
    'root_status_has_no_active_run_before_ci4': root_status['state']=='CI3_COLLECTED_TWO_FULL_GATES_MIXER_GAIN_CI4_READY' and root_status['active_CI']==[] and root_request.get('active_CI',[])==[],
}

old_secondary_path=batch/'prefix-and-whole-draft.json'
old_secondary=json.loads(old_secondary_path.read_bytes())
out={
    'round':'R28','scope':'READ_ONLY_CI4_FINAL_COST_ONLY_DRAFT_SOURCE_AND_GATE_REVIEW',
    'captured_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'plan_draft_sha256':sha(plan_path.read_bytes()),'freeze_receipt_sha256':sha(freeze_path.read_bytes()),
    'root_plan_sha256':sha(root_plan_path.read_bytes()),'root_ci_request_sha256':sha(root_request_path.read_bytes()),
    'native_recipe_sha256':sha(zero_native_path.read_bytes()),'pointwise_recipe_sha256':sha(point_path.read_bytes()),
    'runner_sha256':sha(runner_path.read_bytes()),'latest_request_sha256':sha(latest_request_path.read_bytes()),
    'official53_sha256':sha(base),'zero_native':{'sha256':sha(candidate_zero),'bytes':len(candidate_zero),'runtime_blocks':len(candidate_runtime),'removed_proofs':removed_proofs,'retained_proof_changes':retained_proof_changes,'retained_declaration_references_to_removed_proofs':closure_refs,'full_gate':zero_plan['full_gate'],'declares_correct':zero_plan['declares_correct']},
    'pointwise':{'sha256':sha(candidate_point),'bytes':len(candidate_point),'full_gate':point_plan['full_gate'],'declares_correct':point_plan['declares_correct']},
    'helpers':helper_results,'checks':checks,'checks_passed':all(checks.values()),
    'stale_secondary_draft':{'path':'development/ci-bridge/batch4/prefix-and-whole-draft.json','state':old_secondary.get('state'),'still_contains_held_fullgate_candidate':old_secondary.get('whole_candidate',{}).get('name')=='public53-zero-proof-v2','note':'This supporting JSON was not refreshed; plan-draft.json and cost-source-freeze.json are the current final draft. Ensure it is not used as the frozen dispatch plan.'},
    'dispatch_preflight':{'state':root_request['state'],'batch':root_request['batch'],'root_plan_sha256':sha(root_plan_path.read_bytes()),'candidate_hashes':root_request['candidate_hashes'],'helpers':root_request['helpers'],'dispatch_not_after_utc':root_plan['dispatch_not_after_utc'],'start_cutoff_utc':root_plan['start_cutoff_utc'],'root_status_state':root_status['state'],'active_CI':root_status['active_CI']},
    'correctness_boundary':'Both cost candidates are NativeOnly and explicitly declare_correct=false. Prefix elaboration is diagnostic only. No whole proof gate is selected or inherited; a positive cost signal requires a separate repaired proof candidate, original all12 gate, and fresh independent confirmation.',
    'freshness_boundary':'Current #57 identity, ratio, publication and exact response hashes match the verified 18:15 snapshot. No later refresh directory exists as of this audit. Refresh and rebind official champion data immediately before any later dispatch/score adoption; cost-only exploration results remain separate from current-board promotion claims.',
}
(round_dir/'verification/audit-ci4-final-draft.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'checks_passed':out['checks_passed'],'failed_checks':[k for k,v in checks.items() if not v],'zero':out['zero_native'],'pointwise':out['pointwise'],'helpers':helper_results,'stale_secondary_draft':out['stale_secondary_draft']},indent=2))
