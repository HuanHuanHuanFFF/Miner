"""Bounded target-space replay; coordinates are opportunities, never forecasts."""
from pathlib import Path
import hashlib, json, math
from round10_payability import load_official_scorer

ROOT = Path(__file__).resolve().parents[1]
E = ROOT / 'evidence/round18'

def main():
    source = E / 'official-start-live/pareto-pages.json'
    pages = json.loads(source.read_bytes())
    rows = {r['id']: r for p in pages for r in p['items']}
    sc = load_official_scorer()
    front = [sc.Point(r['id'], r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct']) for r in rows.values() if (r.get('score') or {}).get('on_frontier')]
    weights = sc.local_global_improvement_space_log_weights(sc.pareto_front(front))
    error = max(abs(weights.get(p.name, 0) - rows[p.name]['score']['pareto_weight']) for p in front)
    assert error < 1e-10
    def score(x, y):
        if not 0 < x <= 10 or not 0 < y <= 40:
            return 0.0
        f = sc.pareto_front(front + [sc.Point('__candidate__', x, y)])
        return 100 * sc.local_global_improvement_space_log_weights(f).get('__candidate__', 0)
    targets = []
    for ident in ('582', '514', '542', '553', '561', '573', '550', '361'):
        if ident not in rows or not rows[ident].get('metrics'):
            continue
        m = rows[ident]['metrics']; x0 = m['balanced_time_ratio']; y0 = m['mean_file_compression_pct']
        offsets = [0, -.001, -.005, -.01, -.02, -.05, -.1, -.2, -.5, -1]
        if x0 > 1:
            offsets += [.0005, .001, .002, .005, .01]
        curves = []
        for dy in offsets:
            y = y0 + dy
            # Include both sides of every frontier-time discontinuity, plus a log grid.
            xs = {x0 * math.exp(math.log(.4) + i / 240 * math.log(1.4 / .4)) for i in range(241)}
            for p in front:
                if .4 * x0 <= p.time_s <= 1.4 * x0:
                    xs.update((p.time_s * (1 - 1e-10), p.time_s * (1 + 1e-10)))
            vals = [(x, score(x, y)) for x in sorted(xs)]
            result = {'size_delta_pp': dy, 'size_pct': y, 'at_original_time_share_pct': score(x0, y), 'best_sample': max(vals, key=lambda v:v[1]), 'sample_count':len(vals)}
            for target in (5, 15):
                passing = [(x,s) for x,s in vals if s >= target]
                closest = min(passing, key=lambda v:abs(math.log(v[0]/x0))) if passing else None
                result[f'closest_sample_at_least_{target}_pct'] = None if closest is None else {'time':closest[0], 'time_change_pct':100*(closest[0]/x0-1), 'share_pct':closest[1]}
            curves.append(result)
        targets.append({'reference_id':ident, 'reference_time':x0, 'reference_size_pct':y0, 'curves':curves})
    result = {'snapshot':pages[0]['context'], 'snapshot_file_sha256':hashlib.sha256(source.read_bytes()).hexdigest(), 'official_weight_replay_max_error':error, 'targets':targets,
              'scope':'INFERRED opportunity map on bounded finite coordinates. Keep speed and size tradeoffs. Discontinuity-side samples can be arbitrarily narrow and are not robust target regions. No synthetic timing, no confidence/probability claim. Candidate admission, registration, and simultaneous geometry require separate checks.'}
    (E/'target-map.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    for row in targets:
        print('REFERENCE', row['reference_id'], row['reference_time'], row['reference_size_pct'])
        for curve in row['curves']:
            if curve['size_delta_pp'] in (0,-.02,-.1,-.5,.001,.005):
                print(curve['size_delta_pp'], 'same-time',round(curve['at_original_time_share_pct'],3), '5%',curve['closest_sample_at_least_5_pct'],'15%',curve['closest_sample_at_least_15_pct'])

if __name__ == '__main__':
    main()
