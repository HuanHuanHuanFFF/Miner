"""Apply the frozen R14 four-block confirmation conditions to original receipts."""
from pathlib import Path
from datetime import datetime
import argparse,hashlib,json,statistics,subprocess
from round10_payability import load_flat_rows
ROOT=Path(__file__).resolve().parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('receipt',type=Path);ap.add_argument('--capture',type=Path,required=True);ap.add_argument('--output',type=Path,required=True);ap.add_argument('--parent',default='public514');ap.add_argument('--shadow',default='public514-shadow');a=ap.parse_args()
    folder=a.receipt;state=json.loads((folder/'state.json').read_bytes());ci=json.loads((folder/'ci-run.json').read_bytes())
    assert ci['status']=='completed' and ci['conclusion']=='success' and ci['headSha']==state['git_sha']
    spec=state['spec'];assert spec['screen_blocks']==4 and spec['refine_blocks']==0
    original=json.loads(subprocess.check_output(['git','show',state['git_sha']+':evidence/round14/'+state['batch']+'.json']))
    assert original==spec
    policy_file=ROOT/'evidence/round14/confirmation-policy.json';policy_bytes=policy_file.read_bytes()
    assert subprocess.check_output(['git','show',state['git_sha']+':evidence/round14/confirmation-policy.json'])==policy_bytes
    entries={e['name']:e for e in spec['entries']};parent=a.parent;shadow=a.shadow
    assert entries[parent]['hashes']==entries[shadow]['hashes']
    assert entries[parent]['control'] and entries[shadow]['control']
    if spec.get('confirmation_gate_policy'):
        assert spec['confirmation_gate_policy']['parent']==parent and spec['confirmation_gate_policy']['shadow']==shadow
    competition,context,rows=load_flat_rows(a.capture);anchor=next(r for r in rows if r['id']==entries[parent]['formal_id']);formal=anchor['metrics']
    frontier=[r for r in rows if(r.get('score')or{}).get('on_frontier')]
    metrics={};ids={}
    for e in entries.values():
        for f,h in e['hashes'].items():assert sha(ROOT/e['path']/f)==h
        for block in range(1,5):
            n=e['name'];raw=[json.loads(s)for s in(folder/f'round{block}-{n}.jsonl').read_text().splitlines()]
            assert raw[0]['methods'][n]['source_sha256']==e['hashes']['parse.rs']
            files=[r for r in raw if r['kind']=='file'];assert len(files)==28 and sum(r['raw_bytes']for r in files)==15930000
            x=[];y=[]
            for f in files:
                assert ids.setdefault(f['file'],f['sha256'])==f['sha256']
                ts={}
                for method in(n,'incumbent'):
                    m=f['methods'][method];reps=[v for v in m['reps']if v['phase']=='measured']
                    assert len(reps)==11 and m['deterministic']and not m['errors']
                    ts[method]=statistics.median(v['total_s']for v in reps)
                x.append(ts[n]/ts['incumbent']);y.append(100*f['methods'][n]['output_bytes']/f['raw_bytes'])
            metrics[n,block]=(statistics.mean(x),statistics.mean(y))
    results=[]
    for e in entries.values():
        if e['control']:continue
        assert e['anchor']==parent
        n=e['name'];rp=[metrics[n,b][0]/metrics[parent,b][0]for b in range(1,5)];rs=[metrics[n,b][0]/metrics[shadow,b][0]for b in range(1,5)]
        x=formal['balanced_time_ratio']*statistics.mean(rp);y=formal['mean_file_compression_pct']*metrics[n,1][1]/metrics[parent,1][1]
        dominators=[r['id']for r in frontier if r['metrics']['balanced_time_ratio']<=x and r['metrics']['mean_file_compression_pct']<=y]
        checks={'fresh_mean_improves_parent':statistics.mean(rp)<1,'fresh_mean_improves_shadow':statistics.mean(rs)<1,
            'at_least_three_blocks_improve_parent':sum(v<1 for v in rp)>=3,'at_least_three_blocks_improve_shadow':sum(v<1 for v in rs)>=3,
            'current_declared_family_projection_on_frontier':not dominators and x<=competition['policy']['max_balanced_time_ratio']and y<=competition['policy']['max_mean_file_compression_pct']}
        results.append({'candidate':n,'files':e['hashes'],'decision':'PUBLIC_CONFIRMATION_PASSED'if all(checks.values())else'NO_PROMOTION_CONFIRMATION_FAILED',
            'checks':checks,'vs_parent_blocks_percent':[100*(v-1)for v in rp],'vs_shadow_blocks_percent':[100*(v-1)for v in rs],
            'vs_parent_mean_percent':100*(statistics.mean(rp)-1),'vs_shadow_mean_percent':100*(statistics.mean(rs)-1),
            'family_point':{'x':x,'y':y,'dominators':dominators},'prior_gate_reference':spec.get('reuse_public_gate')})
    result={'run_id':state['run_id'],'batch':state['batch'],'commit':state['git_sha'],'policy_sha256':hashlib.sha256(policy_bytes).hexdigest(),'snapshot':context,'formal_anchor_id':entries[parent]['formal_id'],'anchor_admission':anchor.get('admission'),'results':results,
        'scope':'Frozen fresh four-block decision only, no discovery pooling or trimming. All prior contradictory evidence retained separately. Conditional public family geometry and exact public gate do not certify private admission, entitlement or reward.'}
    a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result,indent=2))
if __name__=='__main__':main()
