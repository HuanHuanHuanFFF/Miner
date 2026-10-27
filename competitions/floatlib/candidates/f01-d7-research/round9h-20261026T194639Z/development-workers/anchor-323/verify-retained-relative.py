"""Read-only historical authentication plus explicitly synthetic metamorphic checks."""
from contextlib import redirect_stdout
from copy import deepcopy
from datetime import datetime, timezone
import hashlib
import importlib.util
import io
import json
import math
from pathlib import Path
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
D7 = ROOT / 'competitions/floatlib/candidates/f01-d7-research'
sha = lambda p: hashlib.sha256(Path(p).read_bytes()).hexdigest()
read = lambda p: json.loads(Path(p).read_bytes())
encode = lambda x: (json.dumps(x, ensure_ascii=False, indent=2) + '\n').encode()


def require(ok, text):
    if not ok:
        raise ValueError(text)


def module(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def main():
    old_files = [p for p in HERE.iterdir() if p.is_file() and not p.name.startswith(('retained-relative-', 'verify-retained-relative', 'derived-b2-cells'))]
    globals_ = [D7 / 'champion-time-estimate.json', D7 / 'multiplier-comparison.json', D7 / 'current-official-snapshot.json', ROOT / 'competitions/floatlib/coordination/development-status.json']
    protected = {str(p): sha(p) for p in old_files + globals_}
    relative_path = HERE / 'retained-relative-draft.py'
    relative = module(relative_path, 'r19_retained_relative_check')
    est_path = ROOT / 'competitions/floatlib/scripts/estimate_champion_time.py'
    require(sha(est_path) == '60476400919dff41f190c1779948f8eeca300753eb920c71ae659438f5bc3eb5', 'Original estimator source changed')
    est = module(est_path, 'r19_retained_relative_original_authenticator')
    retained_path = HERE / 'retained-b2-model-ab3b.json'
    control_path = D7 / 'round8h-20261024T190259Z/freeze-anchor.json'
    reviewed_path = HERE / 'reviewed323-anchor.json'
    retained, control, reviewed = read(retained_path), read(control_path), read(reviewed_path)
    require(sha(retained_path) == 'ab3be355546023e1e8c88a98830018cf3a72f5b238de6b86dd7c0603b296bfda', 'Wrong ab3b raw bytes')
    est.validate_anchor(control); est.validate_anchor(reviewed)
    derived = relative.derive_retained_cells(retained, control)
    records_path = D7 / 'public-suite-results.json'
    records = read(records_path)['records']
    runs = [40168687803, 40169957447, 40171180249]
    roles = dict(zip(runs, ('D', 'A', 'B')))
    candidate_sha = 'df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172'
    pairs, candidate_control_pairs, raw_inputs = [], [], {}
    for run in runs:
        by_source = {}
        for source in (candidate_sha, relative.B2, relative.CONTROL41):
            matches = [r for r in records if r['run'] == run and r['kernel_sha256'] == source and r.get('full_gate')]
            require(len(matches) == 1, 'Historical source gate absent/ambiguous')
            row = est.checked_record(matches[0], ROOT)
            plan = read(ROOT / row['runner_execution'] / 'requested-plan.json')
            require(not plan.get('profile_parent') and not plan.get('profile_current') and not any(c.get('capture_codegen') for c in plan['candidates']), 'Historical requested observer present')
            row.update(observer_free=True, cohort_role=roles[run])
            by_source[source] = row
            for item in row['raw_evidence']:
                raw_inputs[item['path']] = item['sha256']
        pairs.append((by_source[candidate_sha], by_source[relative.B2]))
        candidate_control_pairs.append((by_source[candidate_sha], by_source[relative.CONTROL41]))
    def estimate(source=candidate_sha, supplied=pairs):
        return relative.estimate_relative_to_retained(retained, control, source, retained['champion_digest'], retained['champion_suite'], supplied)
    pure_inputs_before = relative.canonical([retained, control, pairs])
    model = estimate()
    old_model = est.estimate_from_anchor(reviewed, candidate_sha, retained['champion_digest'], retained['champion_suite'], candidate_control_pairs)
    # Every denominator/workload stays exactly ab3b; no raw new-run absolute cost.
    for actual, frozen in zip(model['samples'], retained['samples']):
        require(actual['champion_projected_total_ns'] == frozen['champion_projected_total_ns'] and actual['cell_work'] == frozen['cell_work'], 'Frozen denominator/work changed')
    identity = estimate(relative.B2, ())
    require(identity == retained and encode(identity) == retained_path.read_bytes(), 'Same-source byte identity failed')
    late = deepcopy(pairs * 4)
    for c, b in late:
        c['classes']['add:dense']['submission_ns'] *= 1000000
    require(estimate(relative.B2, late) == retained, 'Later controls refitted same-source B2')
    scaled = deepcopy(pairs)
    for i, (c, b) in enumerate(scaled):
        for row, exponent in ((c, 3+i), (b, 10+i)):
            for v in row['classes'].values():
                v['submission_ns'] *= 2 ** exponent
                v['incumbent_ns'] *= 2 ** exponent
    scaled_model = estimate(supplied=scaled)
    require(scaled_model == model, 'Per-row absolute scale leaked into projection')
    # Synthetic transformations are algebra tests, never acceptable raw evidence.
    synthetic_checks = []
    for factor in (0.5, 1.0, 2.0):
        transformed = []
        for _, b in pairs:
            c = deepcopy(b); c['kernel_sha256'] = 'c' * 64; c['candidate'] = 'SYNTHETIC_RELATIVE_FACTOR'
            for value in c['classes'].values():
                value['submission_ns'] *= factor
            transformed.append((c, deepcopy(b)))
        result = estimate('c' * 64, transformed)
        require(all(value == factor for value in result['cell_relative_delta_to_retained_median'].values()), 'Synthetic factor wrong')
        for s, old in zip(result['samples'], retained['samples']):
            require(s['candidate_total_ns'] == {op: value * factor for op, value in old['candidate_total_ns'].items()}, 'Synthetic direction/scale wrong')
        require(result['whole']['ratio_median'] == retained['whole']['ratio_median'] * factor, 'Synthetic whole direction wrong')
        synthetic_checks.append({'factor': factor, 'whole_median': result['whole']['ratio_median'], 'exact_expected': True})
    # Order is immaterial; source/reference/run/work/observer/cohort changes fail.
    reordered = estimate(supplied=list(reversed(pairs)))
    require(reordered['operations'] == model['operations'] and reordered['samples'] == model['samples'], 'Pair order changed numeric estimate')
    reject = []
    for field, value in [('run', 0), ('seed', 0), ('drawn_plan_sha256', '0'*64), ('observer_free', False), ('kernel_sha256', '0'*64), ('suite_sha256', '0'*64), ('rounds', 24), ('full_gate', False), ('candidate', 'changed-name')]:
        bad = deepcopy(pairs); bad[0][0][field] = value
        try:
            estimate(supplied=bad)
        except relative.RelativeRejected as exc:
            reject.append({'field': field, 'reason': str(exc)})
        else:
            raise ValueError('Changed pair accepted: '+field)
    try:
        estimate(supplied=pairs[:2])
    except relative.RelativeRejected:
        reject.append({'field': 'cohort_size', 'reason': 'Two pairs rejected'})
    else:
        raise ValueError('Missing third pair accepted')
    bad_work = deepcopy(pairs); bad_work[0][0]['cell_work']['add:dense'] += 1
    try:
        estimate(supplied=bad_work)
    except relative.RelativeRejected:
        reject.append({'field': 'cell_work', 'reason': 'Different paired workload rejected'})
    else:
        raise ValueError('Unmatched paired work accepted')
    forged = deepcopy(pairs[0][0]); forged['classes']['add:dense']['submission_ns'] *= 2
    try:
        est.checked_record(forged, ROOT)
    except est.EstimateRejected:
        reject.append({'field': 'raw_classes_tamper', 'reason': 'Original checked_record rejects changed classes before pure calculation'})
    else:
        raise ValueError('Original raw authenticator accepted tampered classes')
    changed_retained = deepcopy(retained)
    changed_retained['cell_relative_delta_median']['add:dense'] *= 2
    try:
        relative.estimate_relative_to_retained(changed_retained, control, relative.B2, retained['champion_digest'], retained['champion_suite'])
    except relative.RelativeRejected:
        reject.append({'field': 'frozen_retained_delta', 'reason': 'Changed frozen B2 model rejected even for same source'})
    else:
        raise ValueError('Frozen retained model refit accepted')
    try:
        relative.estimate_relative_to_retained(retained, control, relative.B2, '0'*64, retained['champion_suite'])
    except relative.RelativeRejected:
        reject.append({'field': 'champion_digest', 'reason': 'Changed champion cannot silently update frozen denominator'})
    else:
        raise ValueError('Changed champion accepted')
    require(relative.canonical([retained, control, pairs]) == pure_inputs_before, 'Pure function mutated input data')
    # Exact real algebra x=C/41=(C/B2)*(B2/41); medians do not distribute.
    cells = sorted(model['cell_relative_delta_to_retained_median'])
    comparison = {}
    for cell in cells:
        x = [est.normalized_pair_delta(c, a, reviewed, candidate_sha)[cell] for c, a in candidate_control_pairs]
        y = [relative.normalized_relative_pair(c, b, candidate_sha, control)[cell] for c, b in pairs]
        z = [est.normalized_pair_delta(b, a, reviewed, relative.B2)[cell] for (_, b), (_, a) in zip(pairs, candidate_control_pairs)]
        require(all(math.isclose(xi, yi * zi, rel_tol=1e-14) for xi, yi, zi in zip(x, y, z)), 'Per-run ratio composition failed')
        old_delta = old_model['cell_relative_delta_median'][cell]
        new_delta = retained['cell_relative_delta_median'][cell] * model['cell_relative_delta_to_retained_median'][cell]
        comparison[cell] = {'old_direct_median_C_over41': old_delta, 'retained_relative_derived_C_over41': new_delta, 'relative_over_old': new_delta / old_delta}
    numeric_difference = {op: {'old_direct': old_model['operations'][op]['ratio_median'], 'new_retained_relative': model['operations'][op]['ratio_median']} for op in relative.OPS}
    numeric_difference['whole'] = {'old_direct': old_model['whole']['ratio_median'], 'new_retained_relative': model['whole']['ratio_median']}
    require(protected == {path: sha(path) for path in protected}, 'Old/global file bytes changed during review')
    receipt = {'status': 'PASS', 'verified_at_utc': datetime.now(timezone.utc).isoformat(), 'pure_function_sha256': sha(relative_path),
        'historical_candidate': pairs[0][0]['candidate'], 'historical_source_sha256': candidate_sha,
        'runs': runs, 'raw_input_count': len(raw_inputs), 'raw_inputs': [{'path': p, 'sha256': h} for p, h in sorted(raw_inputs.items())],
        'same_source_exact_ab3b_dict_and_serialized_bytes': True, 'later_controls_do_not_refit_B2': True,
        'pure_input_objects_unchanged': True,
        'champion323_denominators_and_work_unchanged': True, 'independent_per_row_absolute_scaling_invariant': True,
        'pair_permutation_invariant': True, 'synthetic_direction_checks': synthetic_checks, 'identity_rejections': reject,
        'historical_old_vs_new': numeric_difference, 'cell_method_comparison': comparison,
        'old_and_global_bytes_unchanged': protected,
        'scope': 'Historical three shared executions, not new unseen D/A/B for the historical candidate. Observer-free checks cover requested-plan flags; live selection must still use the existing complete no-observer/adoption guard. All transformed data is synthetic and cannot pass raw-byte reauthentication.'}
    (HERE / 'derived-b2-cells.json').write_bytes(encode(derived))
    (HERE / 'retained-relative-historical-model.json').write_bytes(encode(model))
    (HERE / 'retained-relative-verification.json').write_bytes(encode(receipt))
    print(json.dumps({'status': receipt['status'], 'historical_source_sha256': candidate_sha, 'raw_input_count': len(raw_inputs), 'historical_old_vs_new': numeric_difference, 'same_source_exact_ab3b': True, 'absolute_scaling_invariant': True, 'negative_checks': len(reject)}, ensure_ascii=False))


if __name__ == '__main__':
    main()
