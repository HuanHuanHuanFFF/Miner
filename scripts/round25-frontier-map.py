"""Plan fast-end search using current official scorer; no synthetic performance claims."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, json
from round3 import load_scorer
from round10_payability import load_flat_rows, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    source = ROOT/'evidence/round25/official-rules-start/validator--scoring--pareto.py'
    sc = load_scorer(source)
    comp, ctx, rows = load_flat_rows(a.capture)
    check = validate_policy_for_replay(comp['policy'], rows, sc)
    assert comp['policy']['improvement_share'] == 0
    by = {str(r['id']): r for r in rows}
    bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'], comp['policy']['max_mean_file_compression_pct'])
    front = [sc.Point(str(r['id']), r['metrics']['balanced_time_ratio'], r['metrics']['mean_file_compression_pct'])
             for r in rows if (r.get('score') or {}).get('on_frontier')]
    top = max(rows, key=lambda r: float((r.get('score') or {}).get('payable_weight') or 0))
    # A conservative geometric rank counts all existing frontier allocations,
    # including unpaid ones. Registration/payment changes are not predicted.
    def score(x, y):
        if any(p.time_s <= x and p.ratio_pct <= y for p in front):
            return {'time_ratio': x, 'share_pct': 0.0, 'geometric_rank': None}
        f = sc.pareto_front(front + [sc.Point('__new__', x, y)])
        w = sc.local_global_improvement_space_log_weights(f, bounds)
        value = w.get('__new__', 0)
        return {'time_ratio': x, 'share_pct': 100*comp['policy']['pareto_share']*value,
                'geometric_rank': 1+sum(v > value for k,v in w.items() if k != '__new__'),
                'current_top_after_pct': 100*comp['policy']['pareto_share']*w.get(str(top['id']),0)}
    xs = [0.38+i*0.00005 for i in range(2401)]
    ys = [35.5,35.8,36.0,36.1,36.15,36.2,36.25,36.3,36.35,36.4,36.45,36.48,36.5,36.52,36.54,36.6]
    survey = []
    for y in ys:
        grid = [score(x,y) for x in xs]
        intervals = {}
        for target in ['top1',10,15]:
            groups, active = [], []
            for row in grid:
                good = row['geometric_rank'] == 1 if target == 'top1' else row['share_pct'] >= target
                if good: active.append(row)
                elif active: groups.append(active); active = []
            if active: groups.append(active)
            intervals[str(target)] = [{'min_time':g[0]['time_ratio'],'max_time':g[-1]['time_ratio'],
                'relative_width_pct':100*(g[-1]['time_ratio']/g[0]['time_ratio']-1),
                'min_share_pct':min(r['share_pct'] for r in g),'max_share_pct':max(r['share_pct'] for r in g)} for g in groups]
        survey.append({'quality_pct':y,'intervals':intervals,'grid':grid})
    out = {'status':'INFERRED_SCORING_GEOMETRY_NOT_IMPLEMENTED_PERFORMANCE','snapshot':ctx,
           'computed_utc':datetime.now(timezone.utc).isoformat(),'policy_validation':check,
           'scorer_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
           'current_payable_top':{'id':top['id'],'metrics':top['metrics'],'share_pct':100*top['score']['payable_weight']},
           'anchor595':by['595']['metrics'],'frontier':[{ 'id':p.name,'time':p.time_s,'quality':p.ratio_pct} for p in sorted(front,key=lambda p:p.time_s)],
           'survey':survey,'limits':['Synthetic grid for investment decisions, not observed timing, stress, error bound or probability.',
           'Rank compares recomputed geometric allocations including unpaid points; a new candidate assumes separate eligible ownership and admission.',
           'No continuous-boundary claim. Actual candidate decisions use empirical blocks and same-source references.']}
    a.output.write_bytes((json.dumps(out,indent=2)+'\n').encode())
    print(json.dumps({'snapshot':ctx,'top':out['current_payable_top'],'policy_validation':check,
                      'targets':[{ 'quality':s['quality_pct'],'intervals':s['intervals']} for s in survey]},indent=2))


if __name__ == '__main__': main()
