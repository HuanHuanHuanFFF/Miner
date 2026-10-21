"""Report every measured R16 source against the requested original abs15 parent."""
from pathlib import Path
import argparse,hashlib,json,statistics

ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round16'
PARENT='r13-514-abs15'

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def read(p):return json.loads(p.read_bytes())

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--analysis',type=Path,required=True);ap.add_argument('--output',type=Path,required=True);args=ap.parse_args()
    analysis=read(args.analysis);groups={};models={c['source_sha256']:c for c in analysis['candidates']}
    for run in analysis['runs']:
        folder=E/run['run_id']/run['batch']/'gate';state=read(folder/'state.json');inv=read(folder/'raw-artifact-files.json')['files'];assert sha(folder/'state.json')==inv['state.json']['sha256']
        assert state['run_id']==run['run_id'] and state['git_sha']==run['commit']
        by={(x['candidate'],x['round']):x for x in state['metrics']};entries={x['name']:x for x in state['spec']['entries']}
        for n,entry in entries.items():
            digest=entry['hashes']['parse.rs']
            if digest not in models:continue
            blocks=sorted(b for name,b in by if name==n)
            if not blocks:continue
            assert all((PARENT,b)in by for b in blocks)
            for name in(n,PARENT):
                for b in blocks:
                    path=folder/f'round{b}-{name}.jsonl';assert sha(path)==inv[path.name]['sha256'];raw=[json.loads(x)for x in path.read_text().splitlines()];files=[x for x in raw if x['kind']=='file']
                    assert len(files)==28 and sum(x['raw_bytes']for x in files)==15930000 and raw[0]['measured_rounds']==11
                    ratios=[]
                    for f in files:
                        t=[]
                        for k in(name,'incumbent'):
                            reps=[x['total_s']for x in f['methods'][k]['reps']if x['phase']=='measured'];assert len(reps)==11 and min(reps)>0;t.append(statistics.median(reps))
                        ratios.append(t[0]/t[1])
                    assert abs(statistics.mean(ratios)-by[name,b]['time'])<1e-12
            ratios=[by[n,b]['time']/by[PARENT,b]['time']for b in blocks]
            model=models[digest];g=groups.setdefault(digest,{'candidate':model['candidate'],'source_sha256':digest,'observations':[]})
            g['observations'].append({'run_id':run['run_id'],'batch':run['batch'],'role':'control'if entry.get('control')else'candidate','block_relative_to_abs15':ratios,'public_size_change_pp_vs_abs15':by[n,blocks[0]]['size_pct']-by[PARENT,blocks[0]]['size_pct']})
    rows=[]
    for digest,g in groups.items():
        model=models[digest];obs=g['observations'];y=obs[0]['public_size_change_pp_vs_abs15'];assert all(abs(v['public_size_change_pp_vs_abs15']-y)<1e-12 for v in obs)
        g.update(runners=len(obs),blocks=sum(len(v['block_relative_to_abs15'])for v in obs),time_change_pct_vs_abs15=100*(statistics.mean(statistics.mean(v['block_relative_to_abs15'])for v in obs)-1),size_change_pp_vs_abs15=y,conditional_pool_percent=model['same_family']['candidate']['geometric_share_pct_of_competition_pareto_pool'],stress_pool_percent=model['stress']['candidate']['geometric_share_pct_of_competition_pareto_pool'],exact_public_gate_accepted=model['full_gate_accepted'])
        rows.append(g)
    result={'status':'RAW_RECOMPUTED_COMMON_PARENT_SUMMARY','snapshot':analysis['snapshot'],'source_analysis':str(args.analysis),'source_analysis_sha256':sha(args.analysis),'rows':rows,'paired_processes':analysis['paired_processes'],'scope':'Timeagainstrequestedoriginalabs15 uses actualpairednormalizedtotalaxes with equalrunneraggregation, retaininglatercontrolroles. Conditionalgeometry separatelyusesofficial514transfer. No privateguarantee or newformalresult.'}
    args.output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps([{k:v[k]for k in('candidate','runners','blocks','time_change_pct_vs_abs15','size_change_pp_vs_abs15','conditional_pool_percent')}for v in rows],indent=2))

if __name__=='__main__':main()
