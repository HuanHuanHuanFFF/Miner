"""Show preservation checks reject internally consistent absolute-ns/source refits."""
from copy import deepcopy
from datetime import datetime, timezone
import importlib.util
import json
from pathlib import Path
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('r19_review_policy_checks', HERE / 'build-reviewed-anchor.py')
b = importlib.util.module_from_spec(spec)
spec.loader.exec_module(b)
est, old, anchor, current, pairs = b.construct()


def close_consistency(model, rows, classes):
    for row, sample in zip(rows, model['samples']):
        projected = {op: sum(classes[c]['submission_ns'] * sample['cell_work'][c] for c in sorted(classes) if c.startswith(op + ':')) for op in b.OPS}
        sample.update(champion_projected_total_ns=projected,
            operation_ratios={op: sample['candidate_total_ns'][op] / projected[op] for op in b.OPS},
            whole_ratio=sum(sample['candidate_total_ns'].values()) / sum(projected.values()))
    model['operations'] = {op: b.aggregate([s['operation_ratios'][op] for s in model['samples']]) for op in b.OPS}
    model['whole'] = b.aggregate([s['whole_ratio'] for s in model['samples']])
    return est.build_frozen_anchor(model, rows, anchor['provenance'], classes)


absolute = deepcopy(anchor['champion_classes'])
raw_classes = b.report(b.SNAPSHOT / 'champion-report.raw')['classes']
for cell in absolute:
    absolute[cell]['submission_ns'] = raw_classes[cell]['submission_ns']
absolute_anchor = close_consistency(deepcopy(anchor['original_model']), anchor['frozen_records'], absolute)
rows, model = deepcopy(anchor['frozen_records']), deepcopy(anchor['original_model'])
rows[0]['classes']['add:dense']['submission_ns'] += 1.0
model['samples'][0]['candidate_total_ns']['add'] += model['samples'][0]['cell_work']['add:dense']
refit_anchor = close_consistency(model, rows, anchor['champion_classes'])
rejections = []
for name, modified in [('absolute323_ns_substitution', absolute_anchor), ('control41_source_cost_refit', refit_anchor)]:
    # Original validator guarantees internal consistency; provenance policy is extra.
    est.validate_anchor(modified)
    try:
        b.verify(est, old, modified, current, pairs)
    except ValueError as exc:
        rejections.append({'case': name, 'internally_valid_original_schema': True,
                           'review_preservation_rejected': True, 'reason': str(exc)})
    else:
        raise ValueError('Prohibited recalibration escaped preservation checks: ' + name)
receipt = {'status': 'PASS', 'verified_at_utc': datetime.now(timezone.utc).isoformat(),
    'cases': rejections, 'scope': 'Synthetic in-memory negative checks only; original/derived data bytes unchanged.'}
(HERE / 'preservation-rejections.json').write_bytes(b.encode(receipt))
print(json.dumps(receipt, ensure_ascii=False))
