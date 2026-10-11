"""Survey parser-only headroom from actual paired fast-family repetitions, keeping encode work fixed."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, json, statistics as st
from round3 import load_scorer
from round10_payability import load_flat_rows, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round24'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', required=True, type=Path)
    ap.add_argument('--output', required=True, type=Path)
    a = ap.parse_args()
    assert not a.output.exists()
    comp, ctx, formal_rows = load_flat_rows(a.capture)
    formal = {str(r['id']): r for r in formal_rows}
    sc = load_scorer(E / 'official-rules-start/validator--scoring--pareto.py')
    check = validate_policy_for_replay(comp['policy'], formal_rows, sc)
    bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
    front = [sc.Point(str(r['id']), r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in formal_rows if (r.get('score') or {}).get('on_frontier')]
    folder = E / '38080627701/screen-a/gate'
    state = json.loads((folder / 'state.json').read_bytes())
    inv = json.loads((folder / 'raw-artifact-files.json').read_bytes())['files']
    by = {(r['candidate'], r['round']): r for r in state['metrics']}
    native = json.loads((E / 'feedback-ab-native.json').read_bytes())
    candidates, audits = [], []

    def score(name, x, y):
        if any(p.time_s <= x and p.ratio_pct <= y for p in front):
            return 0.0
        nf = sc.pareto_front(front + [sc.Point(name, x, y)])
        return 100 * comp['policy']['pareto_share'] * sc.local_global_improvement_space_log_weights(nf, bounds).get(name, 0)

    def intervals(grid, threshold):
        result, active = [], []
        for r in grid:
            if r['minimum_share_pct'] >= threshold:
                active.append(r)
            elif active:
                result.append(active)
                active = []
        if active:
            result.append(active)
        return [{'parser_time_scale_start': g[0]['parser_time_scale'], 'parser_time_scale_end': g[-1]['parser_time_scale'], 'smallest_sampled_parser_reduction_pct': 100 * (1 - g[-1]['parser_time_scale']), 'minimum_over_grid_and_observed_views_pct': min(r['minimum_share_pct'] for r in g), 'grid_points': len(g)} for g in result]

    for name in ['r24-595-gain', 'r24-595-chain3-gain']:
        data = []
        for block in [1, 2]:
            path = folder / f'round{block}-{name}.jsonl'
            assert hashlib.sha256(path.read_bytes()).hexdigest() == inv[path.name]['sha256']
            rows = [json.loads(x) for x in path.read_text().splitlines()]
            files = [r for r in rows if r['kind'] == 'file']
            assert len(files) == 28
            reps = []
            for f in files:
                own = [r for r in f['methods'][name]['reps'] if r['phase'] == 'measured']
                inc = [r['total_s'] for r in f['methods']['incumbent']['reps'] if r['phase'] == 'measured']
                assert len(own) == len(inc) == 11 and all(abs(r['total_s'] - r['time_s'] - r['encode_s']) < 1e-9 for r in own)
                reps.append((own, st.median(inc)))
            audits.append({'file': path.relative_to(ROOT).as_posix(), 'sha256': inv[path.name]['sha256']})
            data.append((block, reps))
        grid = []
        for i in range(1001):
            factor = i / 1000
            points = []
            for block, reps in data:
                px = st.mean(st.median(r['encode_s'] + factor * r['time_s'] for r in own) / inc for own, inc in reps)
                if factor == 1:
                    assert abs(px - by[name, block]['time']) < 1e-12
                for anchor in ['public595', 'public595-shadow']:
                    ref = by[anchor, block]
                    x = px * formal['595']['metrics']['balanced_time_ratio'] / ref['time']
                    y = by[name, block]['size_pct'] * formal['595']['metrics']['mean_file_compression_pct'] / ref['size_pct']
                    points.append({'block': block, 'anchor': anchor, 'time_axis': x, 'size_axis_pct': y, 'share_pct': score(name, x, y)})
            vals = [p['share_pct'] for p in points]
            grid.append({'parser_time_scale': factor, 'minimum_share_pct': min(vals), 'maximum_share_pct': max(vals), 'time_axis_minimum': min(p['time_axis'] for p in points), 'time_axis_maximum': max(p['time_axis'] for p in points)})
        candidates.append({'candidate': name, 'actual_main_blocks': 2, 'runner_count': 1, 'reference_views': 2, 'targets': {str(t): intervals(grid, t) for t in [10, 15]}, 'parser_free_hypothesis': grid[0], 'actual_unmodified_timing_replay': grid[-1], 'grid': grid})
    out = {'status': 'INFERRED_PARSER_ONLY_RESOURCE_ENVELOPE_FROM_ACTUAL_REPS', 'computed_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': ctx, 'policy_check': check, 'raw_audits': audits, 'candidates': candidates, 'existing_actual_same_source_reference_gaps': json.loads((E / 'analysis-a.json').read_bytes())['same_source_controls'], 'limits': ['Only parser scale1uses actualcandidate total-time measurements. Every otherpoint is hypothetical encode+scaledparse perrep, with actualpairedincumbent fixed, followed by originalmedian/mean aggregation.', 'This is a maximum-work-elimination planning envelope under unchanged tokens/encoding, not an implemented candidate, private prediction guarantee, new observation, stress scenario or probability.', 'Independent data remain2blocks on1runner, not4samples; actualreferencecopy discrepancies are retained separately.', 'Nonmonotonic scoring intervals are all retained on declaredparser scalegrid0..1step0.001. This doesnotprove continuous extrema orachievability.']}
    a.output.write_bytes((json.dumps(out, indent=2) + '\n').encode())
    print(json.dumps({'snapshot': ctx, 'candidates': [{k: r[k] for k in ['candidate', 'targets', 'parser_free_hypothesis', 'actual_unmodified_timing_replay']} for r in candidates]}, indent=2))


if __name__ == '__main__':
    main()
