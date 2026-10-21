"""Apply the predeclared proof-spending rule to one complete frozen confirmation."""
from pathlib import Path
from datetime import datetime,timezone
import copy,hashlib,json,subprocess
from round4 import confirmation_gates

ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round13'
def read(p):return json.loads(p.read_bytes())
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    policy_path=E/'confirm-aa-decision-policy.json';policy=read(policy_path);rid=policy['confirmation_run_id']
    dispatch=read(E/f'dispatch-{rid}.json');folder=E/rid/dispatch['batch']/'gate'
    ci=read(folder/'ci-run.json');state=read(folder/'state.json');inv=read(folder/'raw-artifact-files.json')
    assert ci['status']=='completed' and ci['conclusion']=='success' and str(ci['databaseId'])==rid
    assert ci['headSha']==state['git_sha']==dispatch['git_sha'] and state['run_id']==rid
    assert state['spec']==read(E/(dispatch['batch']+'.json')) and not state['failures']
    assert inv['artifact_name']==f'r13-{rid}-{dispatch["batch"]}-gate'
    for f,v in inv['files'].items():
        p=(folder/f).resolve();assert p.is_relative_to(folder.resolve()) and p.stat().st_size==v['bytes'] and sha(p)==v['sha256']
    assert subprocess.check_output(['git','show',state['git_sha']+':scripts/round4.py'])==(ROOT/'scripts/round4.py').read_bytes()
    freeze_time=subprocess.check_output(['git','log','--follow','--format=%aI','--','evidence/round13/confirm-aa-decision-policy.json'],text=True).splitlines()[-1]
    artifact=read(folder/'artifact-receipt.json')
    assert datetime.fromisoformat(freeze_time)<datetime.fromisoformat(artifact['created_at'].replace('Z','+00:00'))
    entries={e['name']:e for e in state['spec']['entries']};name=policy['candidate'];entry=entries[name]
    assert entry['hashes']['parse.rs']==policy['rust_sha256'] and state['spec']['screen_blocks']==policy['expected_blocks']==4
    for e in entries.values():
        for f,h in e['hashes'].items():assert sha(ROOT/e['path']/f)==h
    decode=read(folder/'r12-decode/decode.json');case=next(c for c in decode['cases'] if c['candidate']==name)
    assert decode['run_id']==rid and decode['git_sha']==state['git_sha'] and decode['source_hashes'][name]==entry['hashes']
    assert case['cases']==540 and case['decode_or_panic_failures']==0
    proof=policy['proof_pair_if_permitted']
    for f in ('parse.rs','Parse.lean'):assert sha(ROOT/'candidates'/proof['candidate']/f)==proof[f]
    decision_state=copy.deepcopy(state)
    decision_state['spec']['confirmation_gate_policy']={k:policy[k] for k in ('parent','shadow','min_improved_blocks')}
    selected,decisions=confirmation_gates(decision_state,[name]);assert len(decisions)==1
    by={(m['candidate'],m['round']):m for m in state['metrics']}
    direct=entry['comparison_baseline']
    result={'status':'PROOF_ALLOCATION_PERMITTED' if selected else 'STOP_COMPOSITION_NO_FULL_GATE',
        'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'run_id':rid,'git_sha':state['git_sha'],
        'policy_sha256':sha(policy_path),'policy_first_commit_time':freeze_time,'final_artifact_created_at':artifact['created_at'],
        'policy_frozen_before_result_artifact':True,'decision':decisions[0],
        'relative_to_direct_baseline':[by[name,b]['time']/by[direct,b]['time'] for b in range(1,5)],
        'proof_pair':proof,'proof_gate_status':'NOT_RUN; allocation is separate from verification',
        'scope':'Only the fresh confirmation controls spending; discovery excluded. Original artifact unmodified. Conditional geometry is not formal admission, ranking or reward.'}
    (E/'confirm-aa-decision.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(result,indent=2))

if __name__=='__main__':main()
