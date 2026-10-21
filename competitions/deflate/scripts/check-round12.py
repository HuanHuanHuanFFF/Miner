"""Read-only final byte/version audit, separate from performance and Lean claims."""
from pathlib import Path
from datetime import datetime
import argparse,hashlib,json,subprocess

ROOT=Path(__file__).resolve().parents[1]

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--output',type=Path,required=True);ap.add_argument('--final',action='store_true');args=ap.parse_args()
    records=sorted((ROOT/'evidence/round12').glob('dispatch-*.json'))
    assert 1<=len(records)<=5
    runs=[];blobs={};distinct=set();all_files=0
    for p in records:
        dispatch=json.loads(p.read_bytes());rid=str(dispatch['run']['databaseId']);legacy=dispatch.get('actual_experiment_round')=='11'
        folder=ROOT/'evidence'/('round11'if legacy else'round12')/rid/dispatch['batch']/'gate'
        if not (folder/'state.json').exists():
            assert not args.final,'Final receipt missing for'+rid
            runs.append({'run_id':rid,'status':'PENDING_FINAL_RECEIPT'});continue
        state=json.loads((folder/'state.json').read_bytes());ci=json.loads((folder/'ci-run.json').read_bytes());raw=json.loads((folder/'raw-artifact-files.json').read_bytes())
        assert str(ci['databaseId'])==rid==state['run_id']
        assert ci['headSha']==dispatch['git_sha']==state['git_sha']
        assert ci['event']=='workflow_dispatch'and ci['headBranch']=='codex/round12-frontier'
        assert ci['status']=='completed'and ci['conclusion']=='success'
        assert state['batch']==dispatch['batch']
        assert raw['artifact_name']==f'r{11 if legacy else 12}-{rid}-{dispatch["batch"]}-gate'
        assert dispatch['job_timeout_minutes']<=35 and dispatch['repository_visibility_verified']=='public'and dispatch['allow_private']is False
        if dispatch.get('additional_run_approved'):
            assert dispatch['batch']=='probe-e'and dispatch['job_timeout_minutes']<=20
        for name,meta in raw['files'].items():
            file=(folder/name).resolve();assert file.is_relative_to(folder.resolve())
            assert file.stat().st_size==meta['bytes']and sha(file)==meta['sha256'],(rid,name)
            all_files+=1
        spec_in_git='evidence/'+('round11'if legacy else'round12')+'/'+dispatch['batch']+'.json'
        spec=json.loads(subprocess.check_output(['git','show',dispatch['git_sha']+':'+spec_in_git],cwd=ROOT))
        assert spec==state['spec']
        for e in spec['entries']:
            for f,digest in e['hashes'].items():
                key=(dispatch['git_sha'],e['path']+'/'+f)
                if key not in blobs:blobs[key]=hashlib.sha256(subprocess.check_output(['git','show',key[0]+':'+key[1]],cwd=ROOT)).hexdigest()
                assert blobs[key]==digest==sha(ROOT/e['path']/f),(rid,e['name'],f)
            if not legacy and not e['control']:distinct.add(e['hashes']['parse.rs'])
        eq=None;decode=None
        if (folder/'equivalence-research.json').exists():eq=json.loads((folder/'equivalence-research.json').read_bytes())
        if (folder/'r12-decode/decode.json').exists():
            decode=json.loads((folder/'r12-decode/decode.json').read_bytes())
            assert decode['run_id']==rid and decode['git_sha']==state['git_sha']
            assert all(r['cases']==444 and r['decode_or_panic_failures']==0 for r in decode['cases'])
        if not legacy and eq and eq.get('cases'):
            assert eq['returncode']==0 and all(r['cases']==444 and r['different_or_failed']==0 for r in eq['cases'])
        durations=[]
        for job in ci['jobs']:
            if job['conclusion']=='success':
                duration=(datetime.fromisoformat(job['completedAt'].replace('Z','+00:00'))-datetime.fromisoformat(job['startedAt'].replace('Z','+00:00'))).total_seconds()
                assert 0<=duration<=35*60+15
                durations.append(duration)
        gates=[]
        for name,v in state['gates'].items():
            e=next(e for e in spec['entries']if e['name']==name)
            assert v==json.loads((folder/(name+'-gate.json')).read_bytes())
            assert all(sha(folder/('input-'+name)/f)==h for f,h in e['hashes'].items())
            gates.append({'candidate':name,'accepted':bool(v.get('accepted')),'files':e['hashes']})
        if state.get('gate_confirmation_decisions'):
            from round4 import confirmation_gates
            selected,decisions=confirmation_gates(state,spec['gate_candidates'])
            assert decisions==state['gate_confirmation_decisions']
            assert set(state['gates'])==set(selected)
        runs.append({'run_id':rid,'classification':'UNINTENDED_R11_REPLAY'if legacy else'R12_RESEARCH',
            'source_commit':state['git_sha'],'status':ci['status'],'conclusion':ci['conclusion'],'paired_processes':len(state['metrics']),
            'successful_job_seconds':sum(durations),'raw_files_verified':len(raw['files']),'full_gates':gates})
    captures=[]
    for folder in sorted((ROOT/'evidence/round12').glob('official-*')):
        if not(folder/'receipt.json').exists():continue
        meta=json.loads((folder/'receipt.json').read_bytes())
        for record in meta['raw_response_files']:
            file=folder/record['file'];assert sha(file)==record['sha256']and file.stat().st_size==record['bytes']
        for name,record in meta['derived_files'].items():assert sha(folder/name)==record['sha256']and(folder/name).stat().st_size==record['bytes']
        captures.append({'snapshot_id':meta['snapshot_id'],'folder':folder.relative_to(ROOT).as_posix(),'freshness':meta['competition_context']['freshness'],'pagination':meta['pagination']})
    result={'status':'VERIFIED_FINAL_BYTES_AND_VERSION_BINDINGS'if args.final else'VERIFIED_AVAILABLE_BYTES_WITH_PENDING_RUNS',
        'scope':'Hash, frozen Git object, CI/run/artifact and allocation consistency. Performance must be recomputed separately; no new universal correctness, private admission, registration, chain or payment claim.',
        'runs':runs,'new_rust_sources':len(distinct),'raw_artifact_files_verified':all_files,'git_source_blobs_verified':len(blobs),'official_captures':captures,
        'new_paired_processes':sum(r.get('paired_processes',0)for r in runs if r.get('classification')=='R12_RESEARCH'),
        'unintended_replay_paired_processes':sum(r.get('paired_processes',0)for r in runs if r.get('classification')=='UNINTENDED_R11_REPLAY'),
        'successful_job_seconds':sum(r.get('successful_job_seconds',0)for r in runs)}
    args.output.write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'status':result['status'],'runs':len(runs),'new_rust_sources':len(distinct),'raw_files_verified':all_files,'new_paired_processes':result['new_paired_processes']}))

if __name__=='__main__':main()
