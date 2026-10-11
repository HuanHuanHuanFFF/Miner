"""Add conservative strict-first geometry to already audited per-block projections."""
from pathlib import Path
from datetime import datetime, timezone
import argparse, hashlib, json, statistics as st
from round3 import load_scorer
from round10_payability import load_flat_rows, validate_policy_for_replay

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('analysis', type=Path)
    ap.add_argument('--capture', type=Path, required=True)
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    analysis = json.loads(a.analysis.read_bytes())
    comp,ctx,rows = load_flat_rows(a.capture)
    assert analysis['snapshot'] == ctx
    source = ROOT/'evidence/round25/official-rules-start/validator--scoring--pareto.py'
    sc = load_scorer(source)
    check = validate_policy_for_replay(comp['policy'],rows,sc)
    bounds = sc.Boundaries(comp['policy']['max_balanced_time_ratio'],comp['policy']['max_mean_file_compression_pct'])
    front = [sc.Point(str(r['id']),r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])
             for r in rows if (r.get('score') or {}).get('on_frontier')]
    top = max(rows,key=lambda r:float((r.get('score') or {}).get('payable_weight') or 0))
    def evaluate(o):
        n='__r25_candidate__';x=o['projected_time'];y=o['projected_size_pct']
        eligible=0<x<=bounds.time_s and 0<y<=bounds.ratio_pct and not any(p.time_s<=x and p.ratio_pct<=y for p in front)
        f=sc.pareto_front(front+([sc.Point(n,x,y)] if eligible else []))
        w=sc.local_global_improvement_space_log_weights(f,bounds)
        value=100*comp['policy']['pareto_share']*w.get(n,0)
        assert abs(value-o['single_pool_share_pct'])<1e-9
        rivals=sorted([(p.name,100*comp['policy']['pareto_share']*w.get(p.name,0)) for p in f if p.name!=n],key=lambda x:x[1],reverse=True)
        leading_rival=rivals[0] if rivals else (None,0.0)
        return {k:o[k] for k in ['run_id','block','role','entry_role','entry_name','calibration','projected_time','projected_size_pct']} | {
            'share_pct':value,'strict_geometric_first':value>0 and value>leading_rival[1],
            'geometric_rank':1+sum(s>value for _,s in rivals) if value>0 else None,
            'first_rival_id':leading_rival[0],'first_rival_geometric_share_pct':leading_rival[1],
            'current_payable_top_id':str(top['id']),'current_top_after_geometric_share_pct':100*comp['policy']['pareto_share']*w.get(str(top['id']),0)}
    candidates=[]
    for g in analysis['candidates']:
        obs=[evaluate(o) for o in g['observations']]
        summaries=[]
        for role in sorted({o['role'] for o in obs}):
            for cal in sorted({o['calibration'] for o in obs}):
                selected=[o for o in obs if o['role']==role and o['calibration']==cal and o['entry_role']=='candidate']
                if not selected:continue
                v=[o['share_pct'] for o in selected]
                summaries.append({'role':role,'calibration':cal,'n':len(v),'runner_count':len({o['run_id'] for o in selected}),
                    'minimum_pct':min(v),'median_pct':st.median(v),'maximum_pct':max(v),
                    'zeros':sum(x==0 for x in v),'strict_geometric_first_count':sum(o['strict_geometric_first'] for o in selected),
                    'at_least_10_count':sum(x>=10 for x in v),'at_least_15_count':sum(x>=15 for x in v)})
        candidates.append({'candidate':g['candidate'],'rust_sha256':g['rust_sha256'],'summary':summaries,'observations':obs})
    out={'status':'INFERRED_PER_BLOCK_STRICT_FIRST_REPLAY_ON_AUDITED_PUBLIC_DATA','snapshot':ctx,
         'computed_utc':datetime.now(timezone.utc).isoformat(),'policy_validation':check,
         'analysis_sha256':hashlib.sha256(a.analysis.read_bytes()).hexdigest(),'scorer_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
         'candidates':candidates,'limits':['All existing geometric allocations, including unpaid ones, count as rivals; first must be strictly greater, not tied.',
         'Candidate shares assume admission and a distinct eligible hotkey; neither private results nor formal payout are established.',
         'Discovery, independent confirmation and incidental controls stay separate. Observed counts are not success probabilities.']}
    a.output.write_bytes((json.dumps(out,indent=2)+'\n').encode())
    print(json.dumps({'snapshot':ctx,'candidates':[{'candidate':g['candidate'],'summary':g['summary']} for g in candidates]},indent=2))


if __name__=='__main__':main()
