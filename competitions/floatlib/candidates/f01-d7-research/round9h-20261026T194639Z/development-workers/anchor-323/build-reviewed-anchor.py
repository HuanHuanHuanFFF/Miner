"""Construct/replay reviewed323 without changing any global model or source costs."""
import argparse
from copy import deepcopy
from contextlib import redirect_stdout
from datetime import datetime, timezone
import hashlib
import importlib.util
import io
import json
import math
from pathlib import Path
import statistics
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'competitions/floatlib/scripts/estimate_champion_time.py').is_file())
D7 = ROOT / 'competitions/floatlib/candidates/f01-d7-research'
OLD_ANCHOR = D7 / 'round8h-20261024T190259Z/freeze-anchor.json'
OLD_B2 = D7 / 'round11h-20261025T173831Z/development-previous-champion-model.json'
CURRENT = D7 / 'champion-time-estimate.json'
FROZEN_MODEL = HERE / 'retained-b2-model-ab3b.json'
FROZEN_PAIRS = HERE / 'retained-b2-pair-records.json'
SNAPSHOT = D7 / 'official-20261026T195059Z'
ESTIMATOR = ROOT / 'competitions/floatlib/scripts/estimate_champion_time.py'
OUT = HERE / 'reviewed323-anchor.json'
CURRENT_SHA = 'ab3be355546023e1e8c88a98830018cf3a72f5b238de6b86dd7c0603b296bfda'
OLD_B2_SHA = '9222bdf6edec6efe75c009203405357155045f75028727a2e1fc237b9a343e53'
ANCHOR_SHA = '4a833683649369da031ebdbc8b3c2d37a8bee9d50b6fb5aaf734982faef064d7'
OPS = ('add', 'mul', 'sum', 'bmm')
read = lambda p: json.loads(Path(p).read_bytes())
sha = lambda p: hashlib.sha256(Path(p).read_bytes()).hexdigest()
rel = lambda p: Path(p).resolve().relative_to(ROOT).as_posix()
encode = lambda v: (json.dumps(v, ensure_ascii=False, indent=2, allow_nan=False) + '\n').encode('utf-8')


def require(ok, text):
    if not ok:
        raise ValueError(text)


def module(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def node_text(raw, path):
    """Read one JSON node's original lexical bytes, without normalizing whitespace."""
    text = raw.decode('utf-8')
    decoder = json.JSONDecoder()
    start = 0
    for part in path:
        while text[start].isspace():
            start += 1
        if isinstance(part, int):
            require(text[start] == '[', 'Expected array')
            start += 1
            for i in range(part + 1):
                while text[start].isspace():
                    start += 1
                if i == part:
                    break
                _, start = decoder.raw_decode(text, start)
                while text[start].isspace():
                    start += 1
                require(text[start] == ',', 'Array node absent')
                start += 1
        else:
            require(text[start] == '{', 'Expected object')
            start += 1
            while True:
                while text[start].isspace():
                    start += 1
                key, start = decoder.raw_decode(text, start)
                while text[start].isspace():
                    start += 1
                require(text[start] == ':', 'Expected colon')
                start += 1
                while text[start].isspace():
                    start += 1
                if key == part:
                    break
                _, start = decoder.raw_decode(text, start)
                while text[start].isspace():
                    start += 1
                require(text[start] == ',', 'Object node absent')
                start += 1
    _, end = decoder.raw_decode(text, start)
    return text[start:end].encode('utf-8')


def aggregate(values):
    return {'ratio_median': statistics.median(values), 'ratio_range': [min(values), max(values)]}


def report(path):
    value = read(path)['report']
    return json.loads(value) if isinstance(value, str) else value


def archive_review_inputs():
    """Freeze the input model and selected index rows locally, never pin mutable paths."""
    require(sha(CURRENT) == CURRENT_SHA, 'Wrong current model for archival')
    current = read(CURRENT)
    public_path = D7 / 'public-suite-results.json'
    runs = [p['run'] for p in current['paired_updates']]
    records = [r for r in read(public_path)['records'] if r['run'] in runs and
               r['kernel_sha256'] in (current['kernel_sha256'], read(OLD_ANCHOR)['candidate_kernel_sha256'])]
    frozen_pairs = {'scope': 'Derived index selection, not new measurement. Raw gates are separately hashed.',
        'source_index_at_review': {'path': rel(public_path), 'sha256': sha(public_path), 'bytes': public_path.stat().st_size},
        'records': records}
    for path, raw in ((FROZEN_MODEL, CURRENT.read_bytes()), (FROZEN_PAIRS, encode(frozen_pairs))):
        if path.exists():
            require(path.read_bytes() == raw, 'Existing review archive differs: ' + path.name)
        else:
            with path.open('xb') as stream:
                stream.write(raw)


def construct():
    est = module(ESTIMATOR, 'r19_original_estimator_review')
    require(sha(OLD_ANCHOR) == ANCHOR_SHA, 'Wrong309 anchor bytes')
    require(sha(OLD_B2) == OLD_B2_SHA, 'Wrong frozen309 B2 bytes')
    require(sha(CURRENT) == CURRENT_SHA, 'Current ab3b model changed; do not rebase implicitly')
    require(sha(FROZEN_MODEL) == CURRENT_SHA, 'Archived ab3b bytes differ')
    old, old_b2, current = read(OLD_ANCHOR), read(OLD_B2), read(CURRENT)
    est.validate_anchor(old)
    receipt = read(SNAPSHOT / 'receipts.json')
    require(receipt['status'] == 'VERIFIED_SNAPSHOT' and receipt['compatible_frozen_protocol'], 'Unverified snapshot')
    input_paths = {OLD_ANCHOR, OLD_B2, FROZEN_MODEL, FROZEN_PAIRS, ESTIMATOR, Path(__file__).resolve(), SNAPSHOT / 'receipts.json'}
    for item in receipt['responses'].values():
        path = SNAPSHOT / item['file']
        require(sha(path) == item['sha256'] and path.stat().st_size == item['bytes'], 'Snapshot bytes changed: ' + item['file'])
        input_paths.add(path)
    detail, official = read(SNAPSHOT / 'champion-detail.raw'), report(SNAPSHOT / 'champion-report.raw')
    champions = read(SNAPSHOT / 'champions.raw')
    require(detail['id'] == receipt['champion'] == int(official['submission']) == next(c['submission'] for c in champions if c['current']) == 323, 'Champion323 not current in snapshot')
    require(read(SNAPSHOT / 'leaderboard.raw')['leader'] == 323, 'Leaderboard mismatch')
    require(detail['state'] == 'accepted' and detail['verification_current'] and detail['classes'] == official['classes'], 'Champion detail/report mismatch')
    require(official['passed'] and official['reference_complete'] and not official['incumbent_failed'] and not official['exhausted'], 'Incomplete official gate')
    require(official['mode'] == 'gate' and official['slot'] == 'full' and official['stage'] == 'score' and len(official['rounds']) == 25, 'Wrong official gate boundary')
    original = old['original_model']
    old_report_path, old_receipt_path = ROOT / original['champion_report'], ROOT / original['official_receipts']
    require(sha(old_report_path) == original['champion_report_sha256'] and sha(old_receipt_path) == original['official_receipts_sha256'], 'Old official evidence changed')
    old_report = report(old_report_path)
    old_receipt = read(old_receipt_path)
    require(original['champion_submission'] == int(old_report['submission']) == old_receipt['champion'] == 309, 'Old champion309 identity differs')
    require(old_receipt['status'] == 'VERIFIED_SNAPSHOT' and old_receipt['compatible_frozen_protocol'], 'Old snapshot unverified')
    for item in old_receipt['responses'].values():
        path = old_receipt_path.parent / item['file']
        require(sha(path) == item['sha256'] and path.stat().st_size == item['bytes'], 'Old snapshot raw evidence changed')
        input_paths.add(path)
    old_detail = read(old_receipt_path.parent / 'champion-detail.raw')
    require(old_detail['id'] == 309 and old_detail['digest'] == old['champion_digest'], 'Old309 digest differs')
    require(old_report['passed'] and old_report['reference_complete'] and not old_report['incumbent_failed'] and not old_report['exhausted'] and len(old_report['rounds']) == 25, 'Incomplete309 gate')
    require(old_report['classes'] == old['champion_classes'], 'Old champion costs not original309')
    require(official['suite'] == old_report['suite'] == old['champion_suite'], 'Successor suite changed')
    require(official['champion_sha256'] == detail['champion_sha256'] == old['champion_digest'], '323/309 digest chain broken')
    require(detail['digest'] == current['champion_digest'], 'Current323 digest differs')
    require(official['verifier_fingerprint'] == official['verifier_fingerprint_end'] == old_report['verifier_fingerprint'] == old_report['verifier_fingerprint_end'] == detail['verifier_fingerprint'], 'Verifier chain broken')
    require(detail['incumbent_sha256'] == official['incumbent_sha256'], 'Official incumbent digest differs')
    previous_anchor = ROOT / old['provenance']['previous_anchor']
    require(sha(previous_anchor) == old['provenance']['previous_anchor_sha256'], 'Previous285 anchor changed')
    input_paths.update((old_report_path, old_receipt_path, previous_anchor))
    cells = sorted(old['champion_classes'])
    require(set(cells) == set(official['classes']), 'Successor cells differ')
    ratios = {}
    for cell in cells:
        row = official['classes'][cell]
        require(est.positive(row['submission_ns']) and est.positive(row['incumbent_ns']), 'Bad official cell')
        ratios[cell] = row['submission_ns'] / row['incumbent_ns']
        require(math.isclose(ratios[cell], row['ratio'], rel_tol=1e-12), 'Official paired ratio differs')
    require(ratios == current['champion_successor_chain']['cell_successor_over_previous_time'], 'Current323 ratios differ')
    classes = deepcopy(old['champion_classes'])
    for cell in cells:
        classes[cell]['submission_ns'] *= ratios[cell]
    model = deepcopy(original)
    for sample in model['samples']:
        projected = {op: sum(classes[cell]['submission_ns'] * sample['cell_work'][cell] for cell in cells if cell.startswith(op + ':')) for op in OPS}
        sample.update(champion_projected_total_ns=projected, operation_ratios={op: sample['candidate_total_ns'][op] / projected[op] for op in OPS}, whole_ratio=sum(sample['candidate_total_ns'].values()) / sum(projected.values()))
    model.update(as_of_utc=receipt['queried_at_utc'], champion_submission=323, champion_digest=detail['digest'],
                 champion_report=rel(SNAPSHOT / 'champion-report.raw'), champion_report_sha256=sha(SNAPSHOT / 'champion-report.raw'),
                 official_receipts=rel(SNAPSHOT / 'receipts.json'), official_receipts_sha256=sha(SNAPSHOT / 'receipts.json'),
                 estimator_sha256=sha(Path(__file__)),
                 method='REVIEWED_FROZEN_ANCHOR_CHAMPION_SUCCESSOR',
                 formula='Original309 champion cell submission_ns multiplied only by official same-suite323/309 paired cell ratio; original control41 costs/work retained.',
                 scope='INFERRED. Frozen cross-suite/cross-hardware assumptions remain unresolved. No new same-machine measurement; direct champion comparison and admission UNKNOWN.',
                 operations={op: aggregate([s['operation_ratios'][op] for s in model['samples']]) for op in OPS},
                 whole=aggregate([s['whole_ratio'] for s in model['samples']]))
    for row in old['frozen_records']:
        for item in row.get('raw_evidence', []):
            path = ROOT / item['path']
            require(sha(path) == item['sha256'], 'Frozen historical raw bytes changed')
            input_paths.add(path)
    # Reproduce the explicit three-pair adoption delta. Later controls are not a refit.
    frozen_pair_index = read(FROZEN_PAIRS)
    records = frozen_pair_index['records']
    frozen_runs = [p['run'] for p in current['paired_updates']]
    require(frozen_runs == [40168687803, 40169957447, 40171180249], 'Frozen B2 cohort changed')
    require(current['cell_relative_delta_median'] == old_b2['cell_relative_delta_median'], 'B2 delta was refitted')
    frozen_rows = [r for r in records if r['run'] in frozen_runs]
    pairs = est.select_pairs(frozen_rows, frozen_runs, current['kernel_sha256'], old)
    for candidate, baseline in pairs:
        for item in candidate['raw_evidence'] + baseline['raw_evidence']:
            input_paths.add(ROOT / item['path'])
    provenance = {'kind': 'REVIEWED_309_TO_323_SAME_SUITE_PAIRED_CELL_RATIO_ONLY',
        'reviewed_at_utc': receipt['queried_at_utc'],
        'previous_anchor': rel(OLD_ANCHOR), 'previous_anchor_sha256': ANCHOR_SHA,
        'previous_anchor_provenance_unchanged': deepcopy(old['provenance']),
        'frozen_b2_model_sha256': CURRENT_SHA, 'frozen_previous309_b2_model_sha256': OLD_B2_SHA,
        'frozen_b2_model': rel(FROZEN_MODEL), 'frozen_b2_pair_records': rel(FROZEN_PAIRS),
        'source_index_at_review': frozen_pair_index['source_index_at_review'],
        'frozen_b2_pair_runs': frozen_runs,
        'champion_successor_chain': deepcopy(current['champion_successor_chain']),
        'raw_current_official_snapshot': rel(SNAPSHOT / 'receipts.json'),
        'raw_current_official_snapshot_sha256': sha(SNAPSHOT / 'receipts.json'),
        'raw_source_status': receipt['responses']['champion-source']['status'],
        'rule': 'Only champion_classes[*].submission_ns changes numerically; keep all control41 frozen_records, candidate totals and workload values/lexical bytes. No B2 refit.',
        'legacy_champion_class_metadata': 'incumbent_ns, ratio, spread_inc, spread_sub are preserved309 calibration metadata, not measured323 cell metadata. Only submission_ns is a derived323 projection.',
        'derived_data': ['champion_classes[*].submission_ns', 'original_model.samples[*].champion_projected_total_ns', 'original_model.samples[*].operation_ratios', 'original_model.samples[*].whole_ratio', 'original_model.operations', 'original_model.whole', 'payload_sha256'],
        'scope': 'INFERRED development projection only; original cross-suite/cross-hardware assumptions retained. Direct same-suite candidate/champion comparison and official admission UNKNOWN. No new gate or benchmark executed.',
        'frozen_files': [{'path': rel(path), 'sha256': sha(path), 'bytes': path.stat().st_size} for path in sorted(input_paths, key=rel)]}
    anchor = est.build_frozen_anchor(model, old['frozen_records'], provenance, classes)
    est.validate_anchor(anchor)
    return est, old, anchor, current, pairs


def verify(est, old, anchor, current, pairs):
    est.validate_anchor(anchor)
    old_raw, new_raw = OLD_ANCHOR.read_bytes(), encode(anchor)
    paths = [('frozen_records',)] + [('original_model', 'samples', i, key) for i in range(len(old['original_model']['samples'])) for key in ('candidate_total_ns', 'cell_work')]
    lexical = []
    for path in paths:
        a, b = node_text(old_raw, path), node_text(new_raw, path)
        require(a == b, 'Protected lexical bytes changed: ' + str(path))
        lexical.append({'json_path': list(path), 'bytes': len(a), 'sha256': hashlib.sha256(a).hexdigest()})
    require(anchor['frozen_records'] == old['frozen_records'], 'Frozen records changed')
    for cell, row in old['champion_classes'].items():
        require({k: v for k, v in row.items() if k != 'submission_ns'} == {k: v for k, v in anchor['champion_classes'][cell].items() if k != 'submission_ns'}, 'Extra class metadata changed')
    rebuilt = est.estimate_from_anchor(anchor, current['kernel_sha256'], current['champion_digest'], current['champion_suite'], pairs)
    for field in ('operations', 'whole', 'samples', 'cell_relative_delta_median', 'paired_updates'):
        require(rebuilt[field] == current[field], 'ab3b exact field mismatch: ' + field)
    # Independent arithmetic path: use old costs/current frozen delta/raw323 ratio.
    ratio = anchor['provenance']['champion_successor_chain']['cell_successor_over_previous_time']
    delta = current['cell_relative_delta_median']
    for row, sample in zip(old['frozen_records'], current['samples']):
        for op in OPS:
            keys = sorted(k for k in row['classes'] if k.startswith(op + ':'))
            c = sum(row['classes'][k]['submission_ns'] * sample['cell_work'][k] * delta[k] for k in keys)
            h = sum(old['champion_classes'][k]['submission_ns'] * ratio[k] * sample['cell_work'][k] for k in keys)
            require(c == sample['candidate_total_ns'][op] and h == sample['champion_projected_total_ns'][op], 'Independent sample arithmetic mismatch')
    # Verify fail-closed behavior for changed payload and old champion identity.
    rejected = []
    bad = deepcopy(anchor); bad['frozen_records'][0]['cell_work']['add:dense'] += 1
    for name, call in [('mutated_payload', lambda: est.validate_anchor(bad)), ('old_champion_identity', lambda: est.estimate_from_anchor(anchor, current['kernel_sha256'], old['champion_digest'], old['champion_suite'], pairs))]:
        try:
            call()
        except est.EstimateRejected:
            rejected.append(name)
        else:
            raise ValueError('Expected rejection absent: ' + name)
    return rebuilt, {'status': 'PASS', 'verified_at_utc': datetime.now(timezone.utc).isoformat(),
        'original_estimator_sha256': sha(ESTIMATOR), 'old_anchor_sha256': ANCHOR_SHA,
        'new_anchor_sha256': hashlib.sha256(new_raw).hexdigest(), 'new_anchor_payload_sha256': anchor['payload_sha256'],
        'target_model_sha256': CURRENT_SHA, 'exact_ab3b_fields': ['operations', 'whole', 'samples', 'cell_relative_delta_median', 'paired_updates'],
        'sample_count': len(rebuilt['samples']), 'frozen_source_pair_count': len(pairs),
        'operations': rebuilt['operations'], 'whole': rebuilt['whole'], 'protected_lexical_nodes': lexical,
        'negative_rejections': rejected, 'raw_input_count': len(anchor['provenance']['frozen_files']),
        'scope': anchor['provenance']['scope']}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--verify-only', action='store_true')
    parser.add_argument('--probe-original-main', action='store_true', help='Read-only10-pair drift probe; never save global outputs')
    args = parser.parse_args()
    if not args.verify_only:
        archive_review_inputs()
    est, old, anchor, current, pairs = construct()
    rebuilt, receipt = verify(est, old, anchor, current, pairs)
    if args.verify_only:
        require(OUT.read_bytes() == encode(anchor), 'Saved anchor differs from deterministic reconstruction')
    else:
        OUT.write_bytes(encode(anchor))
        (HERE / 'b2-reconstructed.json').write_bytes(encode(rebuilt))
    if args.probe_original_main:
        tracked = [CURRENT, D7 / 'multiplier-comparison.json', ROOT / 'competitions/floatlib/coordination/development-status.json', D7 / 'current-official-snapshot.json']
        before = {rel(p): sha(p) for p in tracked}
        est.DEFAULT_ANCHOR = OUT
        captured = io.StringIO()
        with redirect_stdout(captured):
            probe = est.main(['--dry-run'])
        require(before == {rel(p): sha(p) for p in tracked}, 'Dry-run mutated global bytes')
        receipt['original_main_dry_run'] = {'default_anchor_override_accepted': True, 'global_bytes_unchanged': before,
            'pair_count': len(probe['paired_updates']), 'matches_frozen_ab3b': probe['operations'] == current['operations'] and probe['whole'] == current['whole'] and probe['samples'] == current['samples'],
            'operations': probe['operations'], 'whole': probe['whole'], 'stdout': captured.getvalue(),
            'decision': 'DEFAULT_ANCHOR override is API-compatible; original main with10 pairs would refit B2, so draft wrapper must stay read-only until mainD explicitly resolves retained-source identity.'}
    (HERE / 'validation-receipt.json').write_bytes(encode(receipt))
    print(json.dumps({k: receipt[k] for k in ('status', 'new_anchor_sha256', 'new_anchor_payload_sha256', 'sample_count', 'frozen_source_pair_count', 'operations', 'whole')}, ensure_ascii=False))


if __name__ == '__main__':
    main()
