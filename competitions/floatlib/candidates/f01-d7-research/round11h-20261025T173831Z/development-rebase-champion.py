"""Reviewed 309 -> 323 same-suite official cell-ratio chain; no source refit."""
from copy import deepcopy
from datetime import datetime, timezone
from pathlib import Path
import argparse
import hashlib
import json
import math
import statistics

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
D7 = HERE.parent
OPS = ('add', 'mul', 'sum', 'bmm')
OLD_SHA = '9222bdf6edec6efe75c009203405357155045f75028727a2e1fc237b9a343e53'
read = lambda p: json.loads(p.read_bytes())
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
encoded = lambda x: (json.dumps(x, ensure_ascii=False, indent=2) + '\n').encode()
positive = lambda n: type(n) in (int, float) and math.isfinite(n) and n > 0


def construct(snapshot):
    receipt = read(snapshot / 'receipts.json')
    assert receipt['status'] == 'VERIFIED_SNAPSHOT' and receipt['compatible_frozen_protocol']
    for item in receipt['responses'].values():
        p = snapshot / item['file']
        assert sha(p) == item['sha256'] and p.stat().st_size == item['bytes']
    detail = read(snapshot / 'champion-detail.raw')
    report = read(snapshot / 'champion-report.raw')['report']
    report = json.loads(report) if isinstance(report, str) else report
    champion = next(c for c in read(snapshot / 'champions.raw') if c['current'])
    assert detail['id'] == champion['submission'] == receipt['champion'] == int(report['submission']) == 323
    assert read(snapshot / 'leaderboard.raw')['leader'] == 323
    assert detail['state'] == 'accepted' and detail['verification_current']
    assert report['passed'] and report['reference_complete'] and not report['exhausted'] and not report['incumbent_failed']
    assert report['mode'] == 'gate' and report['slot'] == 'full' and report['stage'] == 'score' and len(report['rounds']) == 25
    assert detail['classes'] == report['classes']
    current_model_path = D7 / 'champion-time-estimate.json'
    model_path = current_model_path if sha(current_model_path) == OLD_SHA else HERE / 'development-previous-champion-model.json'
    assert sha(model_path) == OLD_SHA, 'This transition only accepts the original frozen309 B2 model'
    old = read(model_path)
    assert old['champion_submission'] == 309 and report['champion_sha256'] == old['champion_digest']
    assert detail['champion_sha256'] == report['champion_sha256']
    assert detail['incumbent_sha256'] == report['incumbent_sha256']
    assert detail['verifier_fingerprint'] == report['verifier_fingerprint']
    assert report['suite'] == old['champion_suite']
    old_report_path = ROOT / old['champion_report']
    assert sha(old_report_path) == old['champion_report_sha256']
    old_report = read(old_report_path)['report']
    old_report = json.loads(old_report) if isinstance(old_report, str) else old_report
    assert report['verifier_fingerprint'] == report['verifier_fingerprint_end'] == old_report['verifier_fingerprint'] == old_report['verifier_fingerprint_end']
    anchor_path = ROOT / old['anchor']
    assert sha(anchor_path) == old['anchor_sha256']
    anchor = read(anchor_path)
    assert anchor['champion_classes'] == old_report['classes']
    cells = set(old_report['classes'])
    assert set(report['classes']) == cells
    delta = {}
    for cell in cells:
        row = report['classes'][cell]
        assert positive(row['submission_ns']) and positive(row['incumbent_ns'])
        delta[cell] = row['submission_ns'] / row['incumbent_ns']
        assert math.isclose(delta[cell], row['ratio'], rel_tol=1e-12)
    new = deepcopy(old)
    for previous, sample in zip(old['samples'], new['samples']):
        assert set(sample['cell_work']) == cells
        for op in OPS:
            old_projection = sum(old_report['classes'][c]['submission_ns'] * sample['cell_work'][c] for c in cells if c.startswith(op + ':'))
            assert math.isclose(old_projection, previous['champion_projected_total_ns'][op], rel_tol=1e-12)
        projected = {op: sum(old_report['classes'][c]['submission_ns'] * delta[c] * sample['cell_work'][c] for c in sorted(cells) if c.startswith(op + ':')) for op in OPS}
        sample['champion_projected_total_ns'] = projected
        sample['operation_ratios'] = {op: sample['candidate_total_ns'][op] / projected[op] for op in OPS}
        sample['whole_ratio'] = sum(sample['candidate_total_ns'].values()) / sum(projected.values())
        assert sample['candidate_total_ns'] == previous['candidate_total_ns']
        assert sample['cell_work'] == previous['cell_work']
    def aggregate(values):
        return {'ratio_median': statistics.median(values), 'ratio_range': [min(values), max(values)]}
    at = datetime.now(timezone.utc).isoformat()
    new.update(as_of_utc=at, champion_submission=323, champion_digest=detail['digest'],
        champion_report=(snapshot / 'champion-report.raw').relative_to(ROOT).as_posix(),
        champion_report_sha256=sha(snapshot / 'champion-report.raw'),
        current_champion_report=(snapshot / 'champion-report.raw').relative_to(ROOT).as_posix(),
        current_champion_report_sha256=sha(snapshot / 'champion-report.raw'),
        official_receipts=(snapshot / 'receipts.json').relative_to(ROOT).as_posix(),
        official_receipts_sha256=sha(snapshot / 'receipts.json'),
        estimator_sha256=sha(Path(__file__)), current_public_results_sha256=sha(D7 / 'public-suite-results.json'),
        method='FROZEN_SOURCE_WITH_VERIFIED_SUCCESSOR_CELL_RATIOS',
        update_kind='OFFICIAL_SAME_SUITE_CHAMPION_SUCCESSOR',
        operations={op: aggregate([s['operation_ratios'][op] for s in new['samples']]) for op in OPS},
        whole=aggregate([s['whole_ratio'] for s in new['samples']]),
        formula='Keep all frozen B2 candidate totals, source deltas and workloads; multiply each original309 anchor-cell cost by the same-suite official323/309 submission_ns/incumbent_ns ratio, re-sum each frozen workload and take original workload medians.',
        previous_champion_model='competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/development-previous-champion-model.json',
        previous_champion_model_sha256=OLD_SHA,
        champion_successor_chain={'from_submission': 309, 'from_digest': old['champion_digest'],
            'to_submission': 323, 'to_digest': detail['digest'], 'suite': report['suite'],
            'verifier_fingerprint': report['verifier_fingerprint'],
            'official_report_reference_digest': report['champion_sha256'],
            'cell_successor_over_previous_time': dict(sorted(delta.items())),
            'scope': 'Official same-suite paired successor ratio; original cross-suite development calibration uncertainty retained.'})
    return old, new, receipt, detail, champion


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--snapshot', required=True)
    ap.add_argument('--apply', action='store_true')
    args = ap.parse_args()
    snapshot = D7 / args.snapshot
    assert snapshot.resolve().parent == D7.resolve() and snapshot.name.startswith('official-')
    old, new, receipt, detail, champion = construct(snapshot)
    if args.apply:
        model_path = D7 / 'champion-time-estimate.json'
        assert sha(model_path) == OLD_SHA, 'Apply exactly once; later runs reproduce from the archived original'
        view_path = D7 / 'multiplier-comparison.json'
        state_path = ROOT / 'competitions/floatlib/coordination/development-status.json'
        pointer_path = D7 / 'current-official-snapshot.json'
        originals = {p: p.read_bytes() for p in (model_path, view_path, state_path, pointer_path)}
        archive = HERE / 'development-previous-champion-model.json'
        if archive.exists():
            assert archive.read_bytes() == originals[model_path]
        else:
            with archive.open('xb') as stream:
                stream.write(originals[model_path])
        view, state, pointer = read(view_path), read(state_path), read(pointer_path)
        assert view['kernel_sha256'] == state['kernel_sha256'] == new['kernel_sha256']
        competition = read(snapshot / 'competition.raw')
        summary = {k: new[k] for k in ('status', 'method', 'candidate', 'kernel_sha256', 'champion_submission', 'champion_digest', 'operations', 'whole')}
        summary.update(evidence=model_path.relative_to(ROOT).as_posix(), evidence_sha256=hashlib.sha256(encoded(new)).hexdigest())
        view['champion'].update(submission=323, digest=detail['digest'], snapshot=competition['current_snapshot_id'],
            receipts=(snapshot / 'receipts.json').relative_to(ROOT).as_posix(), checked_at_utc=receipt['queried_at_utc'],
            official_cumulative_speedup_vs_shipped=champion['speedup_vs_shipped'], official_speedup_basis=champion['speedup_basis'],
            candidate_over_champion_time='UNKNOWN', candidate_over_champion_time_by_operation={op: 'UNKNOWN' for op in OPS})
        view['champion_time_estimate'] = summary
        assert not view.get('dashboard_research_candidate'), 'Research model also needs an explicit transition'
        view['dashboard_policy'].update(estimator=Path(__file__).relative_to(ROOT).as_posix(), updated_at_utc=new['as_of_utc'])
        view['as_of_utc'] = new['as_of_utc']
        pointer.update(queried_at_utc=receipt['queried_at_utc'], directory=snapshot.name, champion=323,
            official_commit=receipt['official_commit'], policy_snapshot=competition['current_snapshot_id'])
        state['current_multiplier_view'].update(official_champion=323, snapshot=competition['current_snapshot_id'], champion_time_estimate=summary,
            dashboard_policy=view['dashboard_policy'], champion_official_historical_speedup_vs_shipped=champion['speedup_vs_shipped'], champion_official_speedup_basis=champion['speedup_basis'])
        state['current_champion_comparison'].update(submission=323, source_digest=detail['digest'], policy_snapshot=competition['current_snapshot_id'],
            queried_at_utc=receipt['queried_at_utc'], direct_paired_ratio='UNKNOWN', method=new['method'], evidence=summary['evidence'])
        state['updated_at_utc'] = new['as_of_utc']
        try:
            for p, value in ((model_path, new), (view_path, view), (pointer_path, pointer), (state_path, state)):
                assert p.read_bytes() == originals[p]
                p.write_bytes(encoded(value))
            record = {'at_utc': new['as_of_utc'], 'snapshot': snapshot.name, 'old_model_sha256': OLD_SHA,
                'new_model_sha256': sha(model_path), 'retained_source_sha256_unchanged': new['kernel_sha256'],
                'candidate_totals_and_workloads_unchanged': True,
                'reason': 'Official champion changed309->323; no repeated-control refit or candidate adoption',
                'operations': new['operations'], 'whole': new['whole']}
            (HERE / 'development-champion-transition.json').write_bytes(encoded(record))
        except BaseException:
            for p, raw in originals.items():
                p.write_bytes(raw)
            raise
    current_verified = False
    if not args.apply and sha(D7 / 'champion-time-estimate.json') != OLD_SHA:
        current = read(D7 / 'champion-time-estimate.json')
        assert current['champion_digest'] == new['champion_digest'] and current['champion_successor_chain'] == new['champion_successor_chain']
        assert current['operations'] == new['operations'] and current['whole'] == new['whole'] and current['samples'] == new['samples']
        current_verified = True
    print(json.dumps({'applied': args.apply, 'current_projection_reproduced': current_verified, 'champion': 323, 'operations': new['operations'], 'whole': new['whole'], 'candidate_totals_unchanged': True}))


if __name__ == '__main__':
    main()
