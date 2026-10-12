"""Inverse geometry at actual observed fast-candidate views; hypothetical planning only."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,json
from round3 import load_scorer
from round10_payability import load_flat_rows,validate_policy_for_replay

ROOT=Path(__file__).resolve().parents[1]


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('analysis',type=Path);ap.add_argument('--capture',type=Path,required=True);ap.add_argument('--output',type=Path,required=True)
    a=ap.parse_args();assert not a.output.exists();data=json.loads(a.analysis.read_bytes())
    comp,ctx,rows=load_flat_rows(a.capture);assert data['snapshot']==ctx
    sc=load_scorer(ROOT/'evidence/round25/official-rules-start/validator--scoring--pareto.py')
    check=validate_policy_for_replay(comp['policy'],rows,sc)
    b=sc.Boundaries(comp['policy']['max_balanced_time_ratio'],comp['policy']['max_mean_file_compression_pct'])
    front=[sc.Point(str(r['id']),r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct']) for r in rows if(r.get('score')or{}).get('on_frontier')]
    def score(x,y):
        if any(p.time_s<=x and p.ratio_pct<=y for p in front):return 0.0,False
        f=sc.pareto_front(front+[sc.Point('__new__',x,y)]);w=sc.local_global_improvement_space_log_weights(f,b);v=w.get('__new__',0)
        return 100*comp['policy']['pareto_share']*v,v>0 and all(v>s for n,s in w.items() if n!='__new__')
    results=[]
    for g in data['candidates']:
        obs=[o for o in g['observations'] if o['entry_role']=='candidate']
        # Same block in multiple reference views is not additional independent data.
        ts=[]
        for i in range(1501):
            factor=.925+i*.00005;vs=[score(o['projected_time']*factor,o['projected_size_pct']) for o in obs]
            ts.append({'time_factor':factor,'minimum_share_pct':min(v[0] for v in vs),'all_views_strict_first':all(v[1] for v in vs)})
        qs=[]
        for i in range(1501):
            delta=i*.001;vs=[score(o['projected_time'],o['projected_size_pct']-delta) for o in obs]
            qs.append({'quality_pp_reduction':delta,'minimum_share_pct':min(v[0] for v in vs),'all_views_strict_first':all(v[1] for v in vs)})
        targets={}
        for target in ['first',10,15]:
            def good(v):return v['all_views_strict_first'] if target=='first' else v['minimum_share_pct']>=target
            t=[v for v in ts if good(v)];q=[v for v in qs if good(v)]
            targets[str(target)]={'least_time_axis_reduction_pct_on_grid':100*(1-max(v['time_factor'] for v in t)) if t else None,
                'least_quality_axis_pp_reduction_on_grid':min(v['quality_pp_reduction'] for v in q) if q else None}
        results.append({'candidate':g['candidate'],'actual_block_count':len({(o['run_id'],o['block']) for o in obs}),
            'runner_count':len({o['run_id'] for o in obs}),'actual_reference_views':len(obs),'targets':targets,'time_grid':ts,'quality_grid':qs})
    out={'status':'INFERRED_INVERSE_GEOMETRY_NOT_OBSERVED_GAIN','computed_utc':datetime.now(timezone.utc).isoformat(),
        'snapshot':ctx,'policy_validation':check,'results':results,'limits':['Uniform shifts are planning scenarios, not measured improvements, noise bounds, attainable algorithms or probabilities.',
        'All main observations and their declared reference views must pass; this does not predict a newrunner or heldout corpus.',
        'Two independent one-axis grids; requirements cannot be added or treated as continuous thresholds.']}
    a.output.write_bytes((json.dumps(out,indent=2)+'\n').encode());print(json.dumps({'snapshot':ctx,'results':[{'candidate':x['candidate'],'targets':x['targets']} for x in results]},indent=2))


if __name__=='__main__':main()
