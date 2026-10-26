"""Pure R19 draft: frozen ab3b B2 projection times new same-runner C/B2 deltas.

This estimates development costs; it never selects/adopts a candidate, reads files,
changes the official gate, or recalibrates the retained B2 model. Callers must first
authenticate rows against original gate/source/plan bytes and the cohort freeze.
"""
from copy import deepcopy
import hashlib
import json
import math
import statistics

OPS = ('add', 'mul', 'sum', 'bmm')
B2 = '622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
CONTROL41 = '41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
RETAINED_CANONICAL_SHA256 = '7b74b04df19964a2b809e7a1c3623fa92dd50bfb2f1e104ea27570d683e82bb5'
CONTROL_PAYLOAD = 'cc65cf4e32e8d4edb62c4d43585886cb10904a6e681618a1710c06a2b0fdfdfe'


class RelativeRejected(ValueError):
    pass


def require(value, message):
    if not value:
        raise RelativeRejected(message)


def canonical(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=False, allow_nan=False).encode()).hexdigest()


def positive(value):
    return type(value) in (int, float) and math.isfinite(value) and value > 0


def digest(value):
    return isinstance(value, str) and len(value) == 64 and all(c in '0123456789abcdef' for c in value)


def aggregate(values):
    return {'ratio_median': statistics.median(values), 'ratio_range': [min(values), max(values)]}


def derive_retained_cells(retained, control):
    """Export derived B2 per-work costs and authoritative frozen contributions."""
    require(canonical(retained) == RETAINED_CANONICAL_SHA256, 'Retained ab3b model changed; explicit review required')
    require(control.get('payload_sha256') == CONTROL_PAYLOAD == canonical({k: v for k, v in control.items() if k != 'payload_sha256'}), 'Old control41 anchor changed')
    require(control['candidate_kernel_sha256'] == CONTROL41 and retained['kernel_sha256'] == B2, 'Wrong frozen sources')
    require(len(control['frozen_records']) == len(retained['samples']) == 6, 'Wrong frozen workload count')
    delta = retained['cell_relative_delta_median']
    cells = sorted(delta)
    require(all(positive(delta[c]) for c in cells), 'Invalid frozen B2 delta')
    samples = []
    for row, sample in zip(control['frozen_records'], retained['samples']):
        require(row['run'] == sample['run'] and row['seed'] == sample['seed'], 'Frozen sample identity differs')
        require(row['cell_work'] == sample['cell_work'] and set(row['classes']) == set(cells), 'Frozen workload/cells differ')
        unit = {c: row['classes'][c]['submission_ns'] * delta[c] for c in cells}
        # Keep the exact multiplication order that produced ab3b. Using unit*work
        # instead is mathematically equivalent but can alter the last float bit.
        contribution = {c: row['classes'][c]['submission_ns'] * sample['cell_work'][c] * delta[c] for c in cells}
        totals = {op: sum(contribution[c] for c in cells if c.startswith(op + ':')) for op in OPS}
        require(totals == sample['candidate_total_ns'], 'Frozen B2 projection no longer reconstructs exactly')
        samples.append({'run': row['run'], 'seed': row['seed'], 'cell_work': deepcopy(sample['cell_work']),
                        'derived_ns_per_work': unit, 'derived_frozen_contribution_ns': contribution})
    return {'kind': 'DERIVED_FROZEN_B2_CELL_PROJECTION_NOT_RAW_MEASUREMENT',
        'retained_model_canonical_sha256': RETAINED_CANONICAL_SHA256,
        'control_anchor_payload_sha256': CONTROL_PAYLOAD,
        'frozen_b2_over_control41_cell_delta': deepcopy(delta), 'samples': samples,
        'scope': 'Derived from old measured control41 costs and frozen B2/41 deltas; not measured B2 absolute ns. Original cross-suite/hardware assumptions remain.'}


def normalized_relative_pair(candidate, baseline, candidate_sha256, control):
    """Rows must already be authenticated by original checked_record/cohort code."""
    require(candidate.get('kernel_sha256') == candidate_sha256 and baseline.get('kernel_sha256') == B2, 'Wrong candidate or retained baseline source')
    expected = control['frozen_records'][0]
    for row in (candidate, baseline):
        require(row.get('full_gate') is True and row.get('rounds') == 25, 'Original full25 gate required')
        require(row.get('observer_free') is True, 'Observer-free evidence authentication required')
        require(row.get('cohort_role') in ('D', 'A', 'B'), 'Frozen D/A/B role required')
        require(digest(row.get('verdict_sha256')) and row.get('raw_evidence'), 'Raw verdict/evidence binding absent')
        for item in row['raw_evidence']:
            require(item.get('path') and digest(item.get('sha256')), 'Malformed raw evidence binding')
        require(row.get('suite_sha256') == control['public_suite_sha256'], 'Public suite changed')
        for field in ('official_commit', 'incumbent_sha256', 'reference_champion_sha256', 'verifier_fingerprint'):
            require(row.get(field) == expected[field], 'Changed frozen gate/reference: ' + field)
    for field in ('run', 'seed', 'suite_sha256', 'official_commit', 'runner_execution', 'drawn_plan_sha256', 'provenance_sha256', 'incumbent_sha256', 'reference_champion_sha256', 'verifier_fingerprint', 'cell_work', 'cohort_role'):
        require(candidate.get(field) is not None and candidate[field] == baseline.get(field), 'Unmatched pair: ' + field)
    cells = sorted(control['frozen_records'][0]['classes'])
    require(set(candidate['classes']) == set(baseline['classes']) == set(candidate['cell_work']) == set(cells), 'Incomplete pair cells')
    result = {}
    for c in cells:
        x, y = candidate['classes'][c], baseline['classes'][c]
        require(all(positive(v) for v in (x['submission_ns'], x['incumbent_ns'], y['submission_ns'], y['incumbent_ns'], candidate['cell_work'][c])), 'Invalid cost/work')
        result[c] = (x['submission_ns'] / x['incumbent_ns']) / (y['submission_ns'] / y['incumbent_ns'])
        require(positive(result[c]), 'Non-finite relative delta')
    return result


def estimate_relative_to_retained(retained, control, candidate_sha256, champion_digest, champion_suite, pairs=()):
    """Exactly3 authenticated C/B2 pairs for a new source; B2 is strict identity.

    Estimation does not replace full original gate, fixed D/A/B discovery/holdouts,
    ratio<=.97, positive paired bootstrap p05, no observers, or fresh official checks.
    """
    derived = derive_retained_cells(retained, control)
    require(champion_digest == retained['champion_digest'] and champion_suite == retained['champion_suite'], 'Champion changed; reviewed transition required')
    require(digest(candidate_sha256), 'Invalid candidate source digest')
    if candidate_sha256 == B2:
        # Deliberately ignore later controls: identity returns the exact frozen
        # model, including all metadata; no timestamp or noisy update is added.
        return deepcopy(retained)
    require(len(pairs) == 3, 'New source needs exactly the frozen D/A/B full-gate pairs')
    require(len({c.get('candidate') for c, _ in pairs}) == 1 and all(b.get('candidate') == retained['candidate'] for _, b in pairs), 'Candidate/baseline names differ within cohort')
    require({c.get('cohort_role') for c, _ in pairs} == {'D', 'A', 'B'}, 'Missing/duplicate cohort role')
    for field in ('run', 'seed', 'runner_execution'):
        require(len({c.get(field) for c, _ in pairs}) == 3 and all(c.get(field) is not None for c, _ in pairs), 'Duplicate/missing independent execution: ' + field)
    deltas = [normalized_relative_pair(c, b, candidate_sha256, control) for c, b in pairs]
    cells = sorted(deltas[0])
    median = {c: statistics.median(d[c] for d in deltas) for c in cells}
    samples = []
    for frozen, old_sample in zip(derived['samples'], retained['samples']):
        totals = {op: sum(frozen['derived_frozen_contribution_ns'][c] * median[c] for c in cells if c.startswith(op + ':')) for op in OPS}
        require(all(positive(value) for value in totals.values()), 'Non-finite projected cost')
        projected = old_sample['champion_projected_total_ns']
        sample = deepcopy(old_sample)
        sample.update(candidate_total_ns=totals, operation_ratios={op: totals[op] / projected[op] for op in OPS},
                      whole_ratio=sum(totals.values()) / sum(projected.values()),
                      source_role='DERIVED_FROZEN_RETAINED_B2_RELATIVE_PROJECTION')
        samples.append(sample)
    model = deepcopy(retained)
    model.pop('cell_relative_delta_median', None)  # Old name denotes direct C/41.
    model.pop('as_of_utc', None)  # Caller must attach this new estimate's time.
    model.pop('estimator_sha256', None)  # Caller must bind this core plus adapter.
    model.update(method='FROZEN_RETAINED_B2_RELATIVE_PAIRED_DELTAS', update_kind='RETAINED_RELATIVE_SOURCE_DELTA',
        candidate=pairs[0][0]['candidate'], kernel_sha256=candidate_sha256, samples=samples,
        relative_to_retained_kernel_sha256=B2, retained_model_canonical_sha256=RETAINED_CANONICAL_SHA256,
        retained_model_as_of_utc=retained.get('as_of_utc'),
        frozen_b2_cell_relative_delta_to_control41=deepcopy(retained['cell_relative_delta_median']),
        cell_relative_delta_to_retained_median=median,
        operations={op: aggregate([s['operation_ratios'][op] for s in samples]) for op in OPS},
        whole=aggregate([s['whole_ratio'] for s in samples]),
        paired_updates=[{'run': c['run'], 'seed': c['seed'], 'runner_execution': c['runner_execution'], 'cohort_role': c['cohort_role'],
            'candidate_verdict': c['verdict'], 'candidate_verdict_sha256': c['verdict_sha256'],
            'baseline_verdict': b['verdict'], 'baseline_verdict_sha256': b['verdict_sha256'],
            'cell_relative_delta_to_retained': d, 'raw_evidence': deepcopy(c['raw_evidence'] + b['raw_evidence'])} for (c, b), d in zip(pairs, deltas)],
        formula='Freeze all ab3b B2 contributions and champion323 denominators. Multiply each frozen per-cell contribution by median over exactly3 same-runner (C/inc_C)/(B2/inc_B2), re-sum six original workloads.',
        scope='INFERRED retained-relative development projection. Derived B2 costs are not new raw B2 measurements. Absolute new-run ns never calibrates old costs. Direct champion comparison/admission UNKNOWN.',
        selection_scope='Estimator only; unchanged original full gate, frozen D/A/B, .97 ratio, positive p05 and no-observer policy remain external mandatory obligations.')
    return model
