"""Project already-audited parent controls through all available same-block anchors."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import importlib
import json
import statistics as st
from round10_payability import load_flat_rows

expanded = importlib.import_module('audit-round24-score-algebra').expanded


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ('capture', 'parent', 'anchors', 'output'):
        ap.add_argument('--' + name, type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    parent, anchors = [json.loads(p.read_bytes()) for p in (a.parent, a.anchors)]
    comp, ctx, rows = load_flat_rows(a.capture)
    assert parent['snapshot'] == anchors['snapshot'] == ctx
    assert comp['policy']['pareto_share'] == 1 and comp['policy']['improvement_share'] == 0
    formal = {str(r['id']): r for r in rows}
    front = [(str(r['id']), r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct'])
             for r in rows if (r.get('score') or {}).get('on_frontier')]
    before = expanded(front)
    assert max(abs(before[n]['share_pct'] - 100 * formal[n]['score']['pareto_weight']) for n, _, _ in front) < 1e-10
    source = next(c for c in parent['candidates'] if c['candidate'] == 'r22-595-chain-halfhead')
    name = source['candidate']
    observations = []
    for anchor in anchors['anchor_measurements']:
        available = [o for o in source['observations'] if o['run_id'] == anchor['run_id'] and
                     o['block'] == anchor['block'] and o['calibration'] == 'primary']
        assert len(available) == 1 and available[0]['entry_role'] == 'control'
        o = available[0]
        fm = formal[anchor['formal_id']]['metrics']
        x = o['public_time'] * fm['balanced_time_ratio'] / anchor['public_time']
        y = o['public_size_pct'] * fm['mean_file_compression_pct'] / anchor['public_size_pct']
        dominated = any(t <= x and q <= y for _, t, q in front)
        assert x <= comp['policy']['max_balanced_time_ratio'] and y <= comp['policy']['max_mean_file_compression_pct']
        scores = expanded(front + ([] if dominated else [(name, x, y)]))
        value = scores.get(name, {}).get('share_pct', 0)
        if anchor['anchor'] in ('public595', 'public595-shadow'):
            calibration = 'primary' if anchor['anchor'] == 'public595' else 'shadow'
            previous = next(v for v in source['observations'] if v['run_id'] == o['run_id'] and
                            v['block'] == o['block'] and v['calibration'] == calibration)
            assert abs(previous['projected_time'] - x) < 1e-12
            assert abs(previous['single_pool_share_pct'] - value) < 1e-10
        observations.append({'run_id': o['run_id'], 'block': o['block'],
                             'entry_role': 'incidental_parent_control', 'anchor': anchor['anchor'],
                             'projected_time': x, 'projected_size_pct': y, 'share_pct': value,
                             'strict_first': value > 0 and all(value > v['share_pct']
                                                             for n, v in scores.items() if n != name)})
    summaries = []
    for anchor in sorted({r['anchor'] for r in observations}):
        rs = [r for r in observations if r['anchor'] == anchor]
        vs = [r['share_pct'] for r in rs]
        summaries.append({'anchor': anchor, 'observations': len(rs),
                          'run_count': len({r['run_id'] for r in rs}),
                          'minimum_pct': min(vs), 'median_pct': st.median(vs),
                          'maximum_pct': max(vs), 'zeros': sum(v == 0 for v in vs),
                          'strict_first_count': sum(r['strict_first'] for r in rs)})
    out = {'status': 'INFERRED_PARENT_CONTROLS_RELATED_ANCHOR_SENSITIVITY',
           'calculated_utc': datetime.now(timezone.utc).isoformat(), 'snapshot': ctx,
           'candidate': name, 'rust_sha256': source['rust_sha256'],
           'summary': summaries, 'observations': observations,
           'input_sha256': {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in (a.parent, a.anchors)},
           'limits': ['Related-anchor views of the same recorded controls, not new measurements or candidate confirmation.',
                      'No selection of a calibration by reward. Different available anchor cohorts are not equally sized independent samples.',
                      'Actual reference transfer errors and same-source differences remain diagnostic; neither is a private guarantee.']}
    a.output.write_text(json.dumps(out, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'snapshot': ctx['snapshot_id'], 'summary': summaries}, indent=2))


if __name__ == '__main__':
    main()
