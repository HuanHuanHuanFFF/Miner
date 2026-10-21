"""Inverse scoring survey at observed candidate qualities, for resource planning only."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,json,hashlib
from round3 import load_scorer
from round10_payability import load_flat_rows,validate_policy_for_replay
ROOT=Path(__file__).resolve().parents[1]
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--capture',type=Path,required=True);ap.add_argument('--output',type=Path,required=True);a=ap.parse_args();assert not a.output.exists()
    folder=ROOT/'evidence/round24/38102994768/screen-bc/gate';state=json.loads((folder/'state.json').read_bytes());audit=json.loads((ROOT/'evidence/round24/analysis-bc.json').read_bytes())['raw_input_audit'];es={e['name']:e for e in state['spec']['entries']};by={(m['candidate'],m['round']):m for m in state['metrics']};comp,ctx,rows=load_flat_rows(a.capture);sc=load_scorer(ROOT/'evidence/round24/official-rules-start/validator--scoring--pareto.py');policy=validate_policy_for_replay(comp['policy'],rows,sc);formal={str(r['id']):r for r in rows};b=sc.Boundaries(comp['policy']['max_balanced_time_ratio'],comp['policy']['max_mean_file_compression_pct']);front=[sc.Point(str(r['id']),r['metrics']['balanced_time_ratio'],r['metrics']['mean_file_compression_pct'])for r in rows if(r.get('score')or{}).get('on_frontier')]
    audit={k.replace('\\','/'):v for k,v in audit.items()}
    def share(x,y):
        if any(p.time_s<=x and p.ratio_pct<=y for p in front):return 0.0
        nf=sc.pareto_front(front+[sc.Point('__target__',x,y)]);return 100*comp['policy']['pareto_share']*sc.local_global_improvement_space_log_weights(nf,b).get('__target__',0)
    results=[]
    for name in ['fast-stack','r24-609-fast-adaptive']:
        observations=[]
        for block in [1,2]:
            p=folder/f'round{block}-{name}.jsonl';assert hashlib.sha256(p.read_bytes()).hexdigest()==audit[p.relative_to(ROOT).as_posix()]['sha256']
            m=by[name,block]
            for anchor,fid in [('public609','609'),('public609-shadow','609'),('public607','607')]:
                ref=by[anchor,block];fm=formal[fid]['metrics'];observations.append({'block':block,'anchor':anchor,'time':fm['balanced_time_ratio']*m['time']/ref['time'],'size_pct':fm['mean_file_compression_pct']*m['size_pct']/ref['size_pct']})
        grid=[]
        for i in range(400,1001):
            factor=i/1000;vs=[share(o['time']*factor,o['size_pct'])for o in observations];grid.append({'time_factor':factor,'min_across_observed_anchor_views_pct':min(vs),'max_across_views_pct':max(vs)})
        targets={}
        for target in [10,15]:
            good=[r for r in grid if r['min_across_observed_anchor_views_pct']>=target]
            if good:
                r=max(good,key=lambda x:x['time_factor']);targets[str(target)]={'largest_sampled_time_factor':r['time_factor'],'time_axis_reduction_pct':100*(1-r['time_factor']),'minimum_modeled_share_pct':r['min_across_observed_anchor_views_pct'],'transformed_time_range':[min(o['time']*r['time_factor']for o in observations),max(o['time']*r['time_factor']for o in observations)]}
            else:targets[str(target)]=None
        results.append({'candidate_or_control':name,'source_files':es[name]['hashes'],'actual_bc_observations':observations,'target_survey':targets,'grid':grid})
    result={'status':'INFERRED_INVERSE_SCORING_GEOMETRY_NOT_PERFORMANCE','snapshot':ctx,'calculated_utc':datetime.now(timezone.utc).isoformat(),'policy_validation':policy,'results':results,'limits':'Synthetic uniform time-axis scaling at each actuallyobserved quality/anchor view, onlyto judge requiredalgorithmicmargin. Notobservedtiming, a plannedimplementation, noise stress, errorbound orprobability. Primaryandsecondaryviews reuse2blocks, not6independentmeasurements. Gridstep0.001isnottheexactcontinuousboundary.'};a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'snapshot':ctx,'targets':[{k:r[k]for k in ['candidate_or_control','target_survey']}for r in results]},indent=2))
if __name__=='__main__':main()
