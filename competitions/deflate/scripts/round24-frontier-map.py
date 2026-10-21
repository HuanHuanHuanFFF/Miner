"""Actual official snapshot replay and bounded synthetic target-region survey."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, json, math
from round3 import load_scorer
from round10_payability import load_flat_rows, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    source = ROOT / 'evidence/round24/official-rules-start/validator--scoring--pareto.py'
    sc = load_scorer(source)
    comp, ctx, rows = load_flat_rows(a.capture)
    validation = validate_policy_for_replay(comp['policy'], rows, sc)
    b = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
    front = sorted([sc.Point(str(r['id']), r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct'])
        for r in rows if (r.get('score') or {}).get('on_frontier')], key=lambda p:p.time_s)
    top = sorted(rows, key=lambda r:float((r.get('score') or {}).get('payable_weight') or 0), reverse=True)[:12]
    anchor = next(r for r in rows if str(r['id']) == '595')['metrics']
    # Include the region near the fastest frontier at fine resolution and a
    # broad logarithmic view so the study is not confined to that algorithm family.
    xs = sorted(set([anchor['balanced_time_ratio'] * (1 + (-6 + i*.01)/100) for i in range(1001)]
                    + [0.3 * (9.99/0.3)**(i/1200) for i in range(1201)]))
    ys = [33.8, 33.9, 34.0, 34.05, 34.08, 34.09, 34.1, 34.2, 34.5, 35.0, 35.5,
          36.0, 36.2, 36.3, 36.4, 36.45, 36.5, 36.51, 36.52, 36.53, 36.54, 36.55, 36.6]
    survey = []
    for y in ys:
        records = []
        for x in xs:
            if any(p.time_s <= x and p.ratio_pct <= y for p in front):
                share = 0.0
            else:
                nf = sc.pareto_front(front + [sc.Point('__new__', x, y)])
                share = 100*comp['policy']['pareto_share']*sc.local_global_improvement_space_log_weights(nf, b).get('__new__', 0)
            records.append({'time_ratio': x, 'share_pct': share})
        intervals = {}
        for target in [10, 15]:
            segments, active = [], []
            for r in records:
                if r['share_pct'] >= target: active.append(r)
                elif active: segments.append(active); active = []
            if active: segments.append(active)
            intervals[str(target)] = [{'start_time': s[0]['time_ratio'], 'end_time': s[-1]['time_ratio'],
                'width_relative_pct': 100*(s[-1]['time_ratio']/s[0]['time_ratio']-1),
                'sampled_min_share_pct': min(r['share_pct'] for r in s),
                'sampled_max_share_pct': max(r['share_pct'] for r in s)} for s in segments]
        survey.append({'size_pct': y, 'target_intervals': intervals, 'grid': records})
    result = {'status': 'INFERRED_GEOMETRY_ONLY_NOT_CANDIDATE_PERFORMANCE', 'snapshot': ctx,
        'computed_utc': datetime.now(timezone.utc).isoformat(), 'policy_validation': validation,
        'scorer_sha256': hashlib.sha256(source.read_bytes()).hexdigest(), 'formal_anchor595': anchor,
        'top': [{'id':r['id'], 'metrics':r['metrics'], 'payable_share_pct':100*r['score']['payable_weight']} for r in top],
        'frontier': [{'id':p.name, 'time_ratio':p.time_s, 'size_pct':p.ratio_pct} for p in front],
        'survey': survey,
        'limits': 'Sampled synthetic coordinates map the required improvements, not observed performance, confidence bounds, or a probability. Two candidates must also be reinserted jointly. Private quality/time transfer and future admission remain UNKNOWN.'}
    assert not a.output.exists()
    a.output.write_bytes((json.dumps(result, indent=2)+'\n').encode())
    print(json.dumps({'snapshot':ctx, 'policy_validation':validation, 'top':result['top'][:4],
        'fast_frontier':result['frontier'][:14], 'targets':[{'size_pct':v['size_pct'],'intervals':v['target_intervals']} for v in survey]}, indent=2))
if __name__ == '__main__': main()
