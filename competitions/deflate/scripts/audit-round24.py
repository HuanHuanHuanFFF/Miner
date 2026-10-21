"""Audit immutable evidence, exact source pairs and actual collected runner costs."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def read(p):return json.loads(p.read_bytes())
def digest(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--output',required=True,type=Path);a=ap.parse_args();assert not a.output.exists();raw={};metas={};standards=[];gates=[];native=[];official=[]
    for p in E.glob('[0-9]*/**/raw-artifact-files.json'):
        inv=read(p);folder=p.parent;ci=read(folder/'ci-run.json');ident=str(ci['databaseId']);assert ci['headBranch']=='codex/round24-stable-dual';metas[ident]=ci
        for name,v in inv['files'].items():
            f=(folder/name).resolve();assert f.is_relative_to(folder.resolve()) and f.stat().st_size==v['bytes'] and digest(f)==v['sha256'],f;raw[f.relative_to(ROOT).as_posix()]=v
        if (folder/'state.json').exists():
            s=read(folder/'state.json');assert s['git_sha']==ci['headSha'] and s['run_id']==ident;assert all((folder/f"round{m['round']}-{m['candidate']}.jsonl").is_file()for m in s['metrics']);standards.append({'run_id':ident,'batch':s['batch'],'role':s['spec'].get('r18_role','discovery'),'paired_processes':len(s['metrics']),'expected_processes':len(s['spec']['entries'])*s['spec']['screen_blocks'],'phase':s['phase'],'failures':s['failures'],'ci_conclusion':ci['conclusion']})
        for f in folder.glob('**/gate-receipt.json'):
            d=read(f);assert d['git_sha']==ci['headSha'] and d['run_id']==ident;gates.append({'run_id':ident,'candidate':d['spec']['candidate'],'files':d['spec']['files'],'status':d['status'],'checks':d.get('checks'),'receipt':f.relative_to(ROOT).as_posix()})
        for f in folder.glob('**/encoder.json'):
            d=read(f);assert d['git_sha']==ci['headSha'] and d['run_id']==ident;native.append({'run_id':ident,'status':d['status'],'rows':len(d['rows'])})
    for p in E.glob('[0-9]*/execution-log/ci-run.json'):
        d=read(p);ident=str(d['databaseId']);assert d['status']=='completed';rec=read(p.parent/'receipt.json');assert digest(p.parent/'ci.log')==rec['raw_cli_log_sha256'];metas[ident]=d
    dispatches=[read(p)for p in E.glob('dispatch-*.json')];pending=[];jobs=[]
    for d in dispatches:
        assert d['inputs']['allow_private']=='false' and d['repository_visibility_verified']=='public' and d['fixed_deadline_utc']==read(E/'budget.json')['deadline_utc'];ident=str(d['run']['databaseId'])
        if ident not in metas or metas[ident]['status']!='completed':pending.append({'run_id':ident,'batch':d['batch'],'reason':'Not yet collected as a completed run'})
    for ident,d in metas.items():
        for j in d.get('jobs',[]):
            if j['name']!='round24' or j.get('conclusion')=='skipped':continue
            if not j.get('startedAt')or not j.get('completedAt'):continue
            sec=(datetime.fromisoformat(j['completedAt'].replace('Z','+00:00'))-datetime.fromisoformat(j['startedAt'].replace('Z','+00:00'))).total_seconds();assert sec>=0
            jobs.append({'run_id':ident,'started_at':j['startedAt'],'completed_at':j['completedAt'],'conclusion':j['conclusion'],'runner_seconds':sec})
    pairs={}
    for p in (ROOT/'candidates').glob('r24-*/manifest.json'):
        m=read(p);hs={f:digest(p.parent/f)for f in ['parse.rs','Parse.lean']};assert hs==m['hashes'];pairs[p.parent.name]=hs
        if (p.parent/'VERIFICATION.json').exists():
            c=read(p.parent/'VERIFICATION.json');assert c['files']==hs;g=read(ROOT/c['receipt']);assert g['status']=='EXACT_ORIGINAL_PUBLIC_GATE_ACCEPTED' and all(g['checks'].values()) and g['spec']['files']==hs
    for p in E.glob('official*/receipt.json'):
        d=read(p)
        for v in d.get('raw_response_files',[]):
            f=p.parent/v['file'];assert f.stat().st_size==v['bytes'] and digest(f)==v['sha256']
        if d.get('raw_response_files'):official.append({'receipt':p.relative_to(ROOT).as_posix(),'snapshot_id':d.get('snapshot_id'),'raw_responses':len(d['raw_response_files'])})
    seconds=sum(j['runner_seconds']for j in jobs);out={'status':'VERIFIED_COLLECTED_EVIDENCE_AUDIT','checked_at_utc':datetime.now(timezone.utc).isoformat(),'fixed_budget':read(E/'budget.json'),'dispatch_count':len(dispatches),'uncollected_or_unfinished':pending,'run_conclusions':{k:d.get('conclusion')for k,d in metas.items()},'runner_jobs':jobs,'runner_seconds':seconds,'runner_minutes':seconds/60,'raw_file_count':len(raw),'raw_bytes':sum(x['bytes']for x in raw.values()),'raw_files':raw,'original_protocol_batches':standards,'original_paired_processes':sum(d['paired_processes']for d in standards),'native_batches':native,'complete_gate_receipts':gates,'candidate_pairs':pairs,'distinct_r24_rust_count':len({v['parse.rs']for v in pairs.values()}),'official_api_captures':official,'limits':['Collected-job seconds add concurrentrunner durations; they are not wallbudget duration, billing or money.','Publicstandard runner andaccountusage do not establish attributable monetary cost. Monetary cost UNKNOWN.','Pending andfailed experiments are retained; diagnostics are not counted as originalprotocol candidate scores.','No formal competition upload, registration, signature or spending was authorized or performed.']};a.output.write_bytes((json.dumps(out,indent=2)+'\n').encode());print(json.dumps({k:out[k]for k in ['dispatch_count','uncollected_or_unfinished','runner_minutes','raw_file_count','raw_bytes','original_paired_processes','distinct_r24_rust_count']},indent=2))
if __name__=='__main__':main()
