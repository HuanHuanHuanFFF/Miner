"""Freeze a separate diagnostic request without altering the scored gate plan."""
from datetime import datetime, timezone
from pathlib import Path
import hashlib, importlib.util, json, os, uuid

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
SEED=1324001
PROFILE=ROOT/'competitions/floatlib/candidates/f01-d13-cost-profile'
STATE=ROOT/'competitions/floatlib/coordination/development-status.json'
def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def save(path,obj):path.write_bytes((json.dumps(obj,ensure_ascii=False,indent=2)+'\n').encode())
def main():
    state_raw=STATE.read_bytes();state=json.loads(state_raw)
    assert state['research_round']['id']=='R13-20261024T112622Z'
    for path in (ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs').glob('dispatch-*/dispatch.json'):
        receipt=json.loads(path.read_bytes())
        assert int(receipt['inputs']['seed'])!=SEED,'Diagnostic seed already prepared/dispatched'
    request=json.loads((PROFILE/'profile-request.json').read_bytes())
    assert request['dispatch_seed']==SEED and request['profile_seed']==1224016
    assert request['diagnostic_only'] is True and request['full_gate'] is False
    paths=[HERE/n for n in ['profile-entry.py','profile-current.py','profile-suite.py','prepare-profile.py','round-plan.json','execution-binding.py','sync-ci-state.py']]
    paths += [PROFILE/n for n in ['Kernel.lean','manifest.json','profile-request.json']]
    source=ROOT/'competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean'
    paths += [HERE.parent/'profile-current.py', source]
    spec=importlib.util.spec_from_file_location('r13_profile_execution',HERE/'execution-binding.py')
    binding=importlib.util.module_from_spec(spec);spec.loader.exec_module(binding)
    paths += [ROOT/n for n in binding.EXECUTION_FILES]
    files={p.relative_to(ROOT).as_posix():{'sha256':digest(p),'bytes':p.stat().st_size} for p in paths}
    assert digest(source)==request['source_sha256']
    plan={'seed':SEED,'kind':'PROFILE_DIAGNOSTIC','dispatch_candidates':'f01-d13-cost-profile',
          'sample_role':'ADDITIONAL_INPUT_DIAGNOSTIC','diagnostic_only':True,'full_gate':False,
          'profile_request_sha256':digest(PROFILE/'profile-request.json'),
          'candidates':[{'candidate':'f01-d12-scalar-combined','sha256':request['source_sha256']}],
          'purpose':'Exact-source exposed-input cost diagnosis. Never a scored group or admission evidence.'}
    dest=HERE/f'plan-{SEED}.json';assert not dest.exists(),'Frozen diagnostic request already exists'
    save(dest,plan)
    save(HERE/f'freeze-{SEED}.json',{'recorded_at_utc':datetime.now(timezone.utc).isoformat(),
        'request_sha256':digest(dest),'files':files,'role':plan['sample_role']})
    state['research_round'].setdefault('prepared_requests',[]).append({'seed':SEED,'role':plan['sample_role'],
        'kind':plan['kind'],'plan':dest.relative_to(ROOT).as_posix(),'sha256':digest(dest),'candidates':plan['candidates']})
    state['updated_at_utc']=datetime.now(timezone.utc).isoformat()
    assert STATE.read_bytes()==state_raw,'Concurrent state change'
    temp=STATE.with_name(STATE.name+'.profile-'+uuid.uuid4().hex+'.tmp')
    save(temp,state);os.replace(temp,STATE)
    print(json.dumps({'seed':SEED,'files':len(files),'request_sha256':digest(dest),'diagnostic_only':True}))
if __name__=='__main__':main()
