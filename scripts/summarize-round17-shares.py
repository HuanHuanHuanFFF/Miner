"""Observed DNA block shares and mean-coordinate projections, kept distinct."""
from pathlib import Path
import argparse,json,statistics
from round10_payability import load_flat_rows,load_official_scorer,validate_policy_for_replay
ROOT=Path(__file__).resolve().parents[1]
N='r14-514-dna-nofold'
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--capture',type=Path,required=True);ap.add_argument('--output',type=Path,required=True);a=ap.parse_args()
    comp,ctx,rows=load_flat_rows(a.capture);sc=load_official_scorer();validate_policy_for_replay(comp['policy'],rows,sc)
    fm=next(x['metrics']for x in rows if x['id']=='514');front=[sc.Point(x['id'],x['metrics']['balanced_time_ratio'],x['metrics']['mean_file_compression_pct'])for x in rows if(x.get('score')or{}).get('on_frontier')]
    def score(x,y):return 100*sc.local_global_improvement_space_log_weights(sc.pareto_front(front+[sc.Point('__dna__',x,y)])).get('__dna__',0)
    runs=[]
    for rnd,rid,batch in [('round14','37901182218','dna-j'),('round17','37949768851','retest-a'),('round17','37949875804','retest-b')]:
        folder=ROOT/'evidence'/rnd/rid/batch/'gate';s=json.loads((folder/'state.json').read_bytes());ci=json.loads((folder/'ci-run.json').read_bytes());assert ci['status']=='completed'and ci['headSha']==s['git_sha'];m={(v['candidate'],v['round']):v for v in s['metrics']}
        assert next(v for v in s['spec']['entries']if v['name']==N)['hashes']['parse.rs']=='805c03a521b44b665aef3113cb4d6f823924032fec164524163aa0c756002542'
        obs=[]
        for b in range(1,s['spec']['screen_blocks']+1):
            y=fm['mean_file_compression_pct']*m[N,b]['size_pct']/m['public514',b]['size_pct'];v={'block':b,'size_pct':y,'calibrations':{}}
            for anchor in('public514','public514-shadow'):
                x=fm['balanced_time_ratio']*m[N,b]['time']/m[anchor,b]['time'];v['calibrations'][anchor]={'time':x,'pool_pct':score(x,y)}
            obs.append(v)
        runs.append({'run_id':rid,'batch':batch,'new':rnd=='round17','observations':obs})
    summaries={}
    for scope,selected in [('new_only',[v for v in runs if v['new']]),('all_three_runs',runs)]:
        summaries[scope]={}
        for anchor in('public514','public514-shadow'):
            values=[v['calibrations'][anchor]['pool_pct']for run in selected for v in run['observations']]
            xs=[statistics.mean(v['calibrations'][anchor]['time']for v in run['observations'])for run in selected];y=selected[0]['observations'][0]['size_pct']
            summaries[scope][anchor]={'blocks':len(values),'observed_min_pct':min(values),'observed_max_pct':max(values),'observed_median_pct':statistics.median(values),'observed_mean_share_pct':statistics.mean(values),'blocks_ge1pct':sum(v>=1 for v in values),'blocks_ge10pct':sum(v>=10 for v in values),'mean_coordinate_pool_pct':score(statistics.mean(xs),y)}
    result={'snapshot':ctx,'runs':runs,'summaries':summaries,'scope':'Raw reps and source identities are verified in performance-final analysis. Perblock shares are conditional projections, not payouts. Mean-coordinate score differs from mean block share because geometry is nonlinear; neither is a calibrated expected income. No artificial stress adjustment.'}
    a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(summaries,indent=2))
if __name__=='__main__':main()
