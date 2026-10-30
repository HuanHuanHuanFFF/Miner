from pathlib import Path
import datetime, hashlib, importlib.util, json, sys

sys.dont_write_bytecode = True
root = Path.cwd()
round_dir = root / 'competitions/torchlean/candidates/r28-3h-20261030T171558Z'
folder = round_dir / 'development/ci-bridge/batch4'
plan_path = folder / 'plan-draft.json'
prefix_path = folder / 'prefix-and-whole-draft.json'
plan = json.loads(plan_path.read_bytes())
prefix = json.loads(prefix_path.read_bytes())
base = (round_dir / 'competition-state/source-private/official-53.lean').read_bytes()
sha_bytes = lambda b: hashlib.sha256(b).hexdigest()

def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

point_script = folder / 'build_pointwise128_frozen.py'
zero_script = folder / 'build_zero_mobile_v2.py'
point = load(point_script, 'ci4_pointwise_readonly_audit')
zero = load(zero_script, 'ci4_zero_readonly_audit')
candidate_by_name = {item['name']: item for item in plan['candidates']}
point_plan = candidate_by_name['public53-pointwise128-nat-native-only']
whole_plan = candidate_by_name['public53-zero-proof-v2']

def transform_result(module, raw, submission, variant):
    result = module.transform(raw, submission, variant)
    if isinstance(result, tuple):
        result = result[0]
    return {'sha256': sha_bytes(result), 'bytes': len(result)}

point_result = transform_result(point, base, 53, point_plan['variant'])
whole_result = transform_result(zero, base, 53, whole_plan['variant'])
helper_results = []
for helper in plan['helpers']:
    result = transform_result(zero, base, helper['fetch']['submission'], helper['variant'])
    helper_results.append({
        'name': helper['name'], 'planned_sha256': helper['sha256'],
        'recomputed_sha256': result['sha256'], 'planned_bytes': helper['bytes'],
        'recomputed_bytes': result['bytes'], 'hash_matches': result['sha256'] == helper['sha256'],
        'size_matches': result['bytes'] == helper['bytes'], 'seconds': helper['seconds'],
        'within_120': helper['seconds'] <= 120, 'roots': helper['helper_roots'],
    })

runner_path = round_dir / 'development/ci-bridge/runner.py'
runner = runner_path.read_text(encoding='utf-8')
probe_path = round_dir / 'development/ci-bridge/code-diagnostics.py'
latest_request_path = round_dir / 'requests/185000-zero-native-cost-decouple.md'
latest_request = latest_request_path.read_text(encoding='utf-8')
native_only_zero_present = any(
    item.get('full_gate') is False and item.get('declares_correct') is False
    and 'zero' in item.get('name', '').lower()
    for item in plan['candidates']
)
conditional_whole_in_plan = any(
    item.get('name') == 'public53-zero-proof-v2' and item.get('full_gate') is True
    and item.get('declares_correct') is True for item in plan['candidates']
)
checks = {
    'official53_base_hash_matches': sha_bytes(base) == plan['reference']['sha256'],
    'pointwise_transform_rebuild_matches_plan': point_result['sha256'] == point_plan['sha256'] and point_result['bytes'] == point_plan['bytes'] and point_result['bytes'] <= 256000,
    'whole_v2_transform_rebuild_matches_plan': whole_result['sha256'] == whole_plan['sha256'] and whole_result['bytes'] == whole_plan['bytes'] and whole_result['bytes'] <= 256000,
    'all_helper_transforms_rebuild': all(h['hash_matches'] and h['size_matches'] and h['within_120'] for h in helper_results),
    'plan_and_prefix_helper_lists_match': {h['name'] for h in plan['helpers']} == {h['name'] for h in prefix['helpers']} == set(whole_plan['requires_helpers']),
    'whole_v2_has_full_gate_boundary': whole_plan['full_gate'] is True and whole_plan['declares_correct'] is True,
    'pointwise_has_nativeonly_boundary': point_plan['full_gate'] is False and point_plan['declares_correct'] is False,
    'pointwise_recipe_hash_matches': sha_bytes(point_script.read_bytes()) == point_plan['patch_script_sha256'],
    'zero_recipe_hash_matches': sha_bytes(zero_script.read_bytes()) == whole_plan['patch_script_sha256'] and all(h['patch_script_sha256'] == sha_bytes(zero_script.read_bytes()) for h in plan['helpers']),
    'probe_hash_matches_plan': sha_bytes(probe_path.read_bytes()) == plan['code_probe_sha256'],
    'helpers_run_before_full_candidates': runner.find("for entry in plan.get('helpers',[]):") < runner.find("for entry in plan['candidates']:") and runner.find('def materialize(entry):') < runner.find("for entry in plan.get('helpers',[]):"),
    'helper_cap_hard_clamped_at_120': "min(120,entry.get('seconds',120)," in runner,
    'helper_exceptions_become_failed_diagnostics': "except Exception as error:" in runner[runner.find("for entry in plan.get('helpers',[]):"):runner.find("if plan.get('mode')=='helpers-only':")],
    'failed_required_helper_skips_candidate': 'SKIPPED_AFTER_BOUNDED_HELPER_FAILED' in runner,
    'latest_zero_native_candidate_not_yet_present': not native_only_zero_present,
    'latest_request_fullgate_separation_not_yet_reflected': conditional_whole_in_plan,
    'latest_request_was_read': 'runtime-identical' in latest_request or 'runtimeidentical' in latest_request,
    'plan_still_unsubmitted': prefix['state'] == 'NOT_DISPATCHED_FROZEN_PREFIXES_AND_CONDITIONAL_WHOLE',
}

out = {
    'round': 'R28', 'scope': 'READ_ONLY_CURRENT_CI4_DRAFT_SOURCE_AND_CONTROL_REVIEW',
    'captured_at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'draft_plan_sha256': sha_bytes(plan_path.read_bytes()),
    'prefix_draft_sha256': sha_bytes(prefix_path.read_bytes()),
    'runner_sha256': sha_bytes(runner_path.read_bytes()),
    'latest_request_sha256': sha_bytes(latest_request_path.read_bytes()),
    'official53_sha256': sha_bytes(base), 'dispatch_state': prefix['state'],
    'pointwise': {'sha256': point_result['sha256'], 'bytes': point_result['bytes'], 'full_gate': point_plan['full_gate'], 'declares_correct': point_plan['declares_correct']},
    'zero_whole_v2': {'sha256': whole_result['sha256'], 'bytes': whole_result['bytes'], 'full_gate': whole_plan['full_gate'], 'declares_correct': whole_plan['declares_correct'], 'requires_helpers': whole_plan['requires_helpers']},
    'helpers': helper_results, 'checks': checks, 'checks_passed': all(checks.values()),
    'latest_request_alignment': {
        'zero_runtime_identical_nativeonly_candidate_present': native_only_zero_present,
        'whole_zero_v2_gate_removed_from_ci4': not conditional_whole_in_plan,
        'action': 'Do not treat current CI4 draft as final/dispatched candidate set. Latest request asks for an added runtime-identical Zero NativeOnly candidate and defers whole proof gate to a later batch; current plan still has only pointwise NativeOnly plus conditional whole-v2 full gate. Reaudit exact new candidate before dispatch.'
    },
    'runner_review': {
        'hard_120s_cap': "min(120,entry.get('seconds',120)," in runner,
        'per_helper_exception_recorded': checks['helper_exceptions_become_failed_diagnostics'],
        'conditional_skip_marker': 'SKIPPED_AFTER_BOUNDED_HELPER_FAILED' in runner,
        'helper_log_path': 'OUT/<helper-name>-helper.log',
        'retention_boundary': 'The user explicitly authorized original raw diagnostic evidence to be preserved. After collection, inspect uploaded helper logs for full prefix-source leakage; retain bytes/hash and failure evidence. Do not discard logs based on hypothetical leakage.'
    },
    'correctness_boundary': 'Helper elaboration only checks bounded prefixes. The pointwise entry is NativeOnly. Whole zero-v2 is a proof-bearing candidate and must pass original all12 if scheduled later; no helper or prior proof transfers.',
}
(round_dir / 'verification/audit-ci4-current-draft.json').write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
print(json.dumps({'checks_passed': out['checks_passed'], 'failed_checks': [k for k,v in checks.items() if not v], 'plan_sha256': out['draft_plan_sha256'], 'pointwise': out['pointwise'], 'zero_whole_v2': out['zero_whole_v2'], 'latest_request_alignment': out['latest_request_alignment'], 'helpers': helper_results}, indent=2))
