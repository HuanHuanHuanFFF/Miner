"""Audit final R16 receipt identities, original bytes and exact accepted pairs."""
from pathlib import Path
from datetime import datetime
import argparse,hashlib,json,subprocess

ROOT=Path(__file__).resolve().parents[1]
EVIDENCE=ROOT/'evidence/round16'

def read(path):return json.loads(path.read_bytes())
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--final',action='store_true');args=ap.parse_args()
    budget=read(EVIDENCE/'budget.json');start=datetime.fromisoformat(budget['start_utc']);deadline=datetime.fromisoformat(budget['deadline_utc'])
    assert int((deadline-start).total_seconds())==7200
    frozen=read(EVIDENCE/'frozen-candidates.json')
    assert len(frozen['candidates'])==12
    for entry in frozen['candidates']:
        assert all(sha(ROOT/'candidates'/entry['candidate']/name)==value for name,value in entry['files'].items()), 'Frozen exact candidate changed'
    runs=[];pending=[];accepted=[];metrics=0
    for path in sorted(EVIDENCE.glob('dispatch-*.json')):
        d=read(path);rid=str(d['run']['databaseId']);batch=d['batch'];assert path.name==f'dispatch-{rid}.json'and d['round']==16
        assert d['inputs']['experiment_round']=='16'and d['inputs']['specification']==batch
        assert d['allow_private']is False and d['inputs']['allow_private']=='false'and d['repository_visibility_verified']=='public'
        created=datetime.fromisoformat(d['run']['createdAt'].replace('Z','+00:00'));assert start<=created<deadline and 10<=d['job_timeout_minutes']<=90
        git_sha=d['git_sha'];assert d['run']['headSha']==git_sha
        spec=read(EVIDENCE/f'{batch}.json');frozen=json.loads(subprocess.check_output(['git','show',git_sha+f':evidence/round16/{batch}.json']))
        assert spec==frozen
        for e in spec['entries']:
            for f,h in e['hashes'].items():assert sha(ROOT/e['path']/f)==h,(batch,e['name'],f)
        phase='diagnostics'if spec.get('native_only')else'gate';folder=EVIDENCE/rid/batch/phase
        no_artifact=folder.with_name('diagnostics-no-artifact')
        if not (folder/'ci-run.json').exists() and (no_artifact/'collection-status.json').exists():
            ci=read(no_artifact/'ci-run.json');receipt=read(no_artifact/'collection-status.json')
            assert ci['status']=='completed'and ci['conclusion']!='success'and str(ci['databaseId'])==rid and ci['headSha']==git_sha
            assert receipt['run_id']==rid and receipt['git_sha']==git_sha and (no_artifact/'ci.log').is_file()
            runs.append({'run_id':rid,'batch':batch,'phase':'FAILED_WITHOUT_UPLOADED_ARTIFACT','ci_conclusion':ci['conclusion'],'paired_processes':0,'original_files':0,'scope':'OriginalGitHublog preserved; no artifact digest invented'})
            continue
        if not (folder/'ci-run.json').exists():pending.append({'run_id':rid,'batch':batch,'reason':'Final receipt not collected'});continue
        ci=read(folder/'ci-run.json');assert str(ci['databaseId'])==rid and ci['headSha']==git_sha
        if ci['status']!='completed':pending.append({'run_id':rid,'batch':batch,'reason':'Collected CI status not terminal'});continue
        inv=read(folder/'raw-artifact-files.json');assert inv['artifact_name']==f'r16-{rid}-{batch}-{phase}'
        for name,v in inv['files'].items():
            p=(folder/name).resolve();assert p.is_relative_to(folder.resolve())and p.stat().st_size==v['bytes']and sha(p)==v['sha256']
        count=0
        if phase=='gate' and (folder/'collection-status.json').exists():
            failed=read(folder/'collection-status.json')
            assert ci['conclusion']!='success'and failed['run_id']==rid and failed['git_sha']==git_sha
            reports=[read(p)for p in folder.rglob('*.json')if p.name not in('ci-run.json','artifact-receipt.json','raw-artifact-files.json','collection-status.json')]
            bound=[r for r in reports if isinstance(r,dict)and'run_id'in r and'git_sha'in r]
            assert bound and all(str(r['run_id'])==rid and r['git_sha']==git_sha for r in bound)
        elif phase=='gate':
            state=read(folder/'state.json');assert state['run_id']==rid and state['git_sha']==git_sha and state['spec']==spec
            count=len(state['metrics']);assert not state['failures'];metrics+=count
            for n,v in state['gates'].items():
                if not v.get('accepted'):continue
                e=next(e for e in spec['entries']if e['name']==n);assert v==read(folder/(n+'-gate.json'))
                assert all(sha(folder/('input-'+n)/f)==h for f,h in e['hashes'].items())
                log=(folder/(n+'-gate.log')).read_text();assert 'LZ77.Obligation slot.parse' in log and 'verification accepted' in log
                assert 'Classical.choice' in log and 'Quot.sound' in log and 'propext' in log
                accepted.append({'candidate':n,'run_id':rid,'files':e['hashes'],'verdict':'EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED'})
        else:
            reports=[read(p)for p in folder.rglob('*.json')if p.name not in('ci-run.json','artifact-receipt.json','raw-artifact-files.json')]
            bound=[r for r in reports if isinstance(r,dict)and'run_id'in r and'git_sha'in r];assert bound
            assert all(str(r['run_id'])==rid and r['git_sha']==git_sha for r in bound)
        runs.append({'run_id':rid,'batch':batch,'phase':phase,'ci_conclusion':ci['conclusion'],'paired_processes':count,'original_files':len(inv['files'])})
    if args.final:assert not pending,'Final audit requires every launched CI terminal and collected'
    result={'status':'PASS_FINAL_IDENTITIES_AND_BYTES'if not pending else'PASS_COLLECTED_PENDING_REMAINS','runs':runs,'pending':pending,'paired_processes':metrics,'accepted_pairs':accepted,
        'scope':'Identity/byte/pinned-spec audit only. Paired axes are independently recomputed by analyze-round16.py. CI failure preserved; accepted public pair is not formal admission/ranking/reward. Native rows are never counted as paired timing.'}
    (EVIDENCE/'audit.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'status':result['status'],'runs':len(runs),'pending':pending,'paired_processes':metrics,'accepted_pairs':accepted},indent=2))

if __name__=='__main__':main()
