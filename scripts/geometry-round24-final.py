"""Replay frozen observed neighborhoods and survey target coordinates; no new timing samples."""
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter
import argparse, csv, hashlib, json, statistics as st
from round3 import load_scorer
from round10_payability import load_flat_rows, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'


def dist(v):
    return {'n': len(v), 'minimum': min(v), 'median': st.median(v), 'maximum': max(v)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--confirmation', type=Path, required=True)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    summary = json.loads((a.confirmation / 'summary.json').read_bytes())
    comp, ctx, rows = load_flat_rows(a.capture)
    assert summary['snapshot'] == ctx
    sc = load_scorer(E / 'official-rules-start/validator--scoring--pareto.py')
    check = validate_policy_for_replay(comp['policy'], rows, sc)
    bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
    front = sc.pareto_front([sc.Point(str(r['id']), r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in rows if (r.get('score') or {}).get('on_frontier')])
    old = sc.local_global_improvement_space_log_weights(front, bounds)
    top = max(old, key=old.get)

    def replay(points):
        valid = [sc.Point(n, x, y) for n, x, y in points if 0 < x <= bounds.time_s and 0 < y <= bounds.ratio_pct and not any(p.time_s <= x and p.ratio_pct <= y for p in front)]
        nf = sc.pareto_front(front + valid)
        w = sc.local_global_improvement_space_log_weights(nf, bounds)
        return nf, {k: 100 * comp['policy']['pareto_share'] * v for k, v in w.items()}

    with (a.confirmation / 'main-blocks.csv').open(encoding='utf-8-sig', newline='') as f:
        observed = list(csv.DictReader(f))
    details = []
    for r in observed:
        n, x, y = r['candidate'], float(r['projected_time']), float(r['projected_size_pct'])
        nf, w = replay([(n, x, y)])
        assert abs(w.get(n, 0) - float(r['single_pool_share_pct'])) < 1e-10
        ids = [p.name for p in nf]
        i = ids.index(n) if n in ids else None
        zero_time = min((p.time_s for p in front if p.ratio_pct <= y), default=None)
        zero_quality = min((p.ratio_pct for p in front if p.time_s <= x), default=None)
        details.append({**{k: r[k] for k in ['label', 'candidate', 'run_id', 'block', 'anchor']}, 'time': x, 'size_pct': y, 'share_pct': w.get(n, 0), 'predecessor': ids[i-1] if i is not None and i > 0 else None, 'successor': ids[i+1] if i is not None and i+1 < len(ids) else None, 'removed_formal_frontier_ids': [p.name for p in front if p.name not in ids], 'zero_at_time_axis': zero_time, 'time_axis_headroom_to_zero_pct': None if zero_time is None else 100 * (zero_time / x - 1), 'zero_at_size_axis_pct': zero_quality, 'size_axis_headroom_to_zero_pp': None if zero_quality is None else zero_quality - y, 'top_submission_id': top, 'top_before_pct': 100 * old[top], 'top_after_pct': w.get(top, 0), 'top_change_pp': w.get(top, 0) - 100 * old[top]})
    neighborhood_summaries = []
    surveys = []
    for name in sorted({r['candidate'] for r in details}):
        rs = [r for r in details if r['candidate'] == name]
        assert len(rs) == 27
        for anchor in sorted({r['anchor'] for r in rs}):
            ar = [r for r in rs if r['anchor'] == anchor]
            neighborhood_summaries.append({'candidate': name, 'anchor': anchor, 'main_blocks': len(ar), 'neighbors': [{'predecessor': k[0], 'successor': k[1], 'count': count} for k, count in Counter((r['predecessor'], r['successor']) for r in ar).items()], 'time_headroom_to_zero_pct': dist([r['time_axis_headroom_to_zero_pct'] for r in ar if r['time_axis_headroom_to_zero_pct'] is not None]), 'size_headroom_to_zero_pp': dist([r['size_axis_headroom_to_zero_pp'] for r in ar if r['size_axis_headroom_to_zero_pp'] is not None]), 'top_share_change_pp': dist([r['top_change_pp'] for r in ar])})
        time_grid, quality_grid = [], []
        # Scan the full declared grids because switches can make share non-monotonic.
        for i in range(400, 1001):
            factor = i / 1000
            values = [replay([(name, r['time'] * factor, r['size_pct'])])[1].get(name, 0) for r in rs]
            time_grid.append({'time_factor': factor, 'minimum_share_pct': min(values), 'maximum_share_pct': max(values)})
        # Quality offsets are an inverse geometry survey, not achievable bytes or empirical noise.
        for i in range(0, 1001):
            delta = i / 10000
            values = [replay([(name, r['time'], r['size_pct'] - delta)])[1].get(name, 0) for r in rs]
            quality_grid.append({'size_reduction_pp': delta, 'minimum_share_pct': min(values), 'maximum_share_pct': max(values)})
        targets = {}
        for target in [10, 15]:
            tg = [r for r in time_grid if r['minimum_share_pct'] >= target]
            qg = [r for r in quality_grid if r['minimum_share_pct'] >= target]
            targets[str(target)] = {'smallest_sampled_time_reduction': max(tg, key=lambda r: r['time_factor']) if tg else None, 'smallest_sampled_size_reduction': min(qg, key=lambda r: r['size_reduction_pp']) if qg else None}
        surveys.append({'candidate': name, 'main_blocks': 9, 'anchor_views': 3, 'targets': targets, 'time_grid': time_grid, 'quality_grid': quality_grid})
    out = {'status': 'VERIFIED_OBSERVED_GEOMETRY_AND_INFERRED_TARGET_SURVEY', 'computed_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': ctx, 'policy_check': check, 'raw_confirmation_summary_sha256': hashlib.sha256((a.confirmation / 'summary.json').read_bytes()).hexdigest(), 'observed_points': details, 'neighborhood_summaries': neighborhood_summaries, 'inverse_target_surveys': surveys, 'limits': ['Observed rows reuse the9actual main blocks and3conditional anchor views per candidate, not27independent measurements.', 'Boundary headroom is exact captured-frontier geometry at each conditional point, not a prediction of future noise or private transfer error.', 'Uniform axis transformations are hypothetical resource-planning inputs only; not implemented optimizations, observed benchmark samples, success probability or an exact continuous minimum.', 'Quality grid step0.0001percentagepoint andtime factorstep0.001 canmiss narrower intervals; absence means none in the declared grid, not impossibility.', 'No admission, same-hotkey eligibility or actual payable reward is established.']}
    a.output.write_bytes((json.dumps(out, indent=2) + '\n').encode())
    print(json.dumps({'neighborhoods': neighborhood_summaries, 'targets': [{'candidate': r['candidate'], 'targets': r['targets']} for r in surveys]}, indent=2))


if __name__ == '__main__':
    main()
