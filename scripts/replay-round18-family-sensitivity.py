"""Retain a second observed family calibration as sensitivity, never an error bound."""
from pathlib import Path
import argparse
import hashlib
import json
from round10_payability import load_flat_rows, load_official_scorer, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--analysis', type=Path, required=True)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--family', default='591')
    ap.add_argument('--output', type=Path, required=True)
    args = ap.parse_args()
    assert not args.output.exists()
    analysis = json.loads(args.analysis.read_bytes())
    comp, context, rows = load_flat_rows(args.capture)
    assert context['snapshot_id'] == analysis['snapshot']['snapshot_id']
    sc = load_official_scorer()
    validate_policy_for_replay(comp['policy'], rows, sc)
    formal = next(r['metrics'] for r in rows if r['id'] == args.family)
    front = [sc.Point(r['id'], r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct'])
             for r in rows if (r.get('score') or {}).get('on_frontier')]
    bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
    output = []
    for run in analysis['runs']:
        folder = ROOT / 'evidence/round18' / run['run_id'] / run['batch'] / 'gate'
        state = json.loads((folder / 'state.json').read_bytes())
        entries = {e['name']: e for e in state['spec']['entries']}
        anchors = [n for n in entries if n in ('public' + args.family, 'public' + args.family + '-shadow')]
        if not anchors:
            continue
        metrics = {(m['candidate'], m['round']): m for m in state['metrics']}
        for name in anchors:
            for block in range(1, state['spec']['screen_blocks'] + 1):
                raw = folder / f'round{block}-{name}.jsonl'
                key = str(raw.relative_to(ROOT))
                assert hashlib.sha256(raw.read_bytes()).hexdigest() == analysis['raw_input_audit'][key]['sha256']
        for candidate in analysis['candidates']:
            obs = [o for o in candidate['observations'] if o['run_id'] == run['run_id'] and o['calibration'] == 'primary']
            for ob in obs:
                for name in anchors:
                    m = metrics[name, ob['block']]
                    x = formal['balanced_time_ratio'] * ob['public_time'] / m['time']
                    y = formal['mean_file_compression_pct'] * ob['public_size_pct'] / m['size_pct']
                    p = sc.Point('__alternative__', x, y)
                    f = sc.pareto_front(front + [p])
                    weights = sc.local_global_improvement_space_log_weights(f, bounds)
                    score = 100 * comp['policy']['pareto_share'] * weights.get(p.name, 0)
                    if not (0 < x <= bounds.time_s and 0 < y <= bounds.ratio_pct):
                        score = 0
                    output.append({'candidate': candidate['candidate'], 'run_id': run['run_id'], 'block': ob['block'],
                                   'alternative_anchor': name, 'alternative_family': args.family,
                                   'projected_time': x, 'projected_size_pct': y,
                                   'alternative_conditional_pool_pct': score,
                                   'declared_primary_family_pool_pct': ob['single_pool_share_pct'],
                                   'frontier_ids': [p.name for p in f]})
    result = {'status': 'INFERRED_OBSERVED_REFERENCE_FAMILY_SENSITIVITY_NOT_PRIVATE_BOUND', 'snapshot': context,
              'analysis_sha256': hashlib.sha256(args.analysis.read_bytes()).hexdigest(), 'rows': output,
              'limits': ['Every reference and candidate is paired within the same original timing block.',
                         'The declared586 parent calibration remains separate. Whole591 transfer is a competing assumption, not a conservative bound or probability.',
                         'This does not establish private-corpus performance, admission, registration, or payable rewards.']}
    args.output.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps([{k: v for k, v in r.items() if k != 'frontier_ids'} for r in output], indent=2))


if __name__ == '__main__':
    main()
