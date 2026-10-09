"""Rebuild frozen confirmation metrics from original repetitions before deciding."""
from pathlib import Path
import argparse,hashlib,json,statistics,subprocess
from round3 import load_scorer
from round10_payability import load_flat_rows,validate_policy_for_replay
from round15_gate import share_confirmation_gates

ROOT=Path(__file__).resolve().parents[1]
def read(p):return json.loads(p.read_bytes())
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('receipt',type=Path);ap.add_argument('--output',type=Path,required=True);args=ap.parse_args()
    folder=args.receipt;state=read(folder/'state.json');ci=read(folder/'ci-run.json');inv=read(folder/'raw-artifact-files.json')['files']
    assert ci['status']=='completed' and ci['headSha']==state['git_sha'] and str(ci['databaseId'])==state['run_id']
    assert sha(folder/'state.json')==inv['state.json']['sha256']
    spec=state['spec'];assert spec['screen_blocks']==4 and spec['refine_blocks']==0
    def frozen(path):return subprocess.check_output(['git','show',state['git_sha']+':'+path],cwd=ROOT)
    assert json.loads(frozen('evidence/round16/'+state['batch']+'.json'))==spec
    assert frozen(spec['snapshot_pages'])==(ROOT/spec['snapshot_pages']).read_bytes()
    policy=ROOT/'evidence/round16/confirmation-policy.json';assert frozen('evidence/round16/confirmation-policy.json')==policy.read_bytes()
    assert spec['confirmation_share_gate_policy']['minimum_pool_fraction']==read(policy)['target_pool_fraction']
    entries={e['name']:e for e in spec['entries']};metric={(m['candidate'],m['round']):m for m in state['metrics']};identity={}
    for name,e in entries.items():
        assert all(sha(ROOT/e['path']/f)==h for f,h in e['hashes'].items())
        for b in range(1,5):
            path=folder/f'round{b}-{name}.jsonl';assert sha(path)==inv[path.name]['sha256']
            raw=[json.loads(line)for line in path.read_text().splitlines()];meta=raw[0];files=[x for x in raw if x['kind']=='file']
            assert meta['methods'][name]['source_sha256']==e['hashes']['parse.rs'] and meta['measured_rounds']==11
            assert len(files)==28 and sum(f['raw_bytes']for f in files)==15930000
            ratios=[];sizes=[]
            for f in files:
                assert identity.setdefault(f['file'],f['sha256'])==f['sha256'];t=[]
                for n in(name,'incumbent'):
                    v=f['methods'][n];assert v['deterministic'] and not v['errors'];reps=[x['total_s']for x in v['reps']if x['phase']=='measured'];assert len(reps)==11 and min(reps)>0;t.append(statistics.median(reps))
                ratios.append(t[0]/t[1]);sizes.append(100*f['methods'][name]['output_bytes']/f['raw_bytes'])
            x,y=statistics.mean(ratios),statistics.mean(sizes)
            assert abs(x-metric[name,b]['time'])<1e-12 and abs(y-metric[name,b]['size_pct'])<1e-12
            metric[name,b].update(time=x,size_pct=y)
    capture=(ROOT/spec['snapshot_pages']).parent;comp,context,rows=load_flat_rows(capture)
    scorer=load_scorer(ROOT/'sources/conjectures-optimisation-deflate/validator/scoring/pareto.py');validation=validate_policy_for_replay(comp['policy'],rows,scorer)
    permitted,decisions=share_confirmation_gates(state,spec['gate_candidates'],read(ROOT/spec['snapshot_pages']),scorer)
    def differences(a,b,path='decision'):
        if isinstance(a,dict):
            assert a.keys()==b.keys()
            return [v for k in a for v in differences(a[k],b[k],path+'.'+k)]
        if isinstance(a,list):
            assert len(a)==len(b)
            return [v for i in range(len(a)) for v in differences(a[i],b[i],path+'.'+str(i))]
        return [] if a==b else [(path,a,b)]
    delta=differences(decisions,state['gate_share_confirmation_decisions'])
    # Windows/Linux libm can differ in the final log-weight normalization by an ulp.
    # Every discrete check, permitted candidate and block count must still be exact.
    assert all(isinstance(a,float) and isinstance(b,float) and abs(a-b)<1e-14 for _,a,b in delta), delta
    assert set(state['gates'])<=set(permitted)
    result={'status':'FROZEN_CONFIRMATION_REPLAYED_FROM_RAW_REPS','run_id':state['run_id'],'candidate_files':{n:entries[n]['hashes']for n in spec['gate_candidates']},'policy_sha256':sha(policy),'snapshot':context,'official_weight_replay':validation,'max_fraction_rounding_difference':max((abs(a-b)for _,a,b in delta),default=0),'decisions':decisions,'gates':state['gates'],'scope':'Freshfourblocks only; discovery excluded. Exactsource/spec/policy/snapshotandrawbyteidentities checked. Gateallocation isnotadmission or actualreward.'}
    args.output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'run_id':state['run_id'],'permitted':permitted,'decisions':decisions},indent=2))

if __name__=='__main__':main()
