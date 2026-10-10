"""Verify immutable artifact bytes and summarize actual collected R23 costs."""
from pathlib import Path
import argparse,datetime as dt,hashlib,json
ROOT=Path(__file__).resolve().parents[1]
def read(p):return json.loads(p.read_bytes())
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--output',type=Path,required=True);a=ap.parse_args();e=ROOT/'evidence/round23';raw={};run_meta={};standard=[];gates=[];native=[];pending=[]
 for p in e.glob('[0-9]*/**/raw-artifact-files.json'):
  inv=read(p);folder=p.parent
  for name,v in inv['files'].items():
   f=folder/name;b=f.read_bytes();assert len(b)==v['bytes'] and hashlib.sha256(b).hexdigest()==v['sha256'],f
   raw[f.relative_to(ROOT).as_posix()]=v
  ci=read(folder/'ci-run.json');run_meta[str(ci['databaseId'])]=ci
  if (folder/'state.json').exists():
   st=read(folder/'state.json');assert st['git_sha']==ci['headSha'] and st['run_id']==str(ci['databaseId'])
   assert all((folder/f"round{m['round']}-{m['candidate']}.jsonl").exists()for m in st['metrics'])
   standard.append({'run_id':st['run_id'],'batch':st['batch'],'role':st['spec'].get('r18_role','discovery'),'ci_conclusion':ci['conclusion'],'paired_processes':len(st['metrics']),'expected_paired_processes':len(st['spec']['entries'])*st['spec']['screen_blocks'],'state_phase':st['phase'],'failures':st['failures']})
  for g in folder.glob('**/gate-receipt.json'):
   r=read(g);assert r['git_sha']==ci['headSha'] and r['run_id']==str(ci['databaseId']);gates.append({'run_id':r['run_id'],'candidate':r['spec']['candidate'],'files':r['spec']['files'],'status':r['status'],'checks':r['checks']})
  for n in folder.glob('**/encoder.json'):
   r=read(n);assert r['git_sha']==ci['headSha'] and r['run_id']==str(ci['databaseId']);native.append({'run_id':r['run_id'],'rows':len(r['rows']),'status':r['status']})
 for p in e.glob('*-failure-ci.json'):
  r=read(p);ident=r.get('databaseId')or r.get('run_id');assert ident is not None, 'Failure metadata must identify its actual run';run_meta[str(ident)]=r
 dispatches=[read(p)for p in sorted(e.glob('dispatch-*.json'))]
 for d in dispatches:
  ident=str(d['run']['databaseId'])
  if ident not in run_meta:pending.append(ident)
 seconds=0
 for ident,m in run_meta.items():
  for j in m.get('jobs',[]):
   if j.get('name')!='round23' or not j.get('startedAt')or not j.get('completedAt'):continue
   seconds+=(dt.datetime.fromisoformat(j['completedAt'].replace('Z','+00:00'))-dt.datetime.fromisoformat(j['startedAt'].replace('Z','+00:00'))).total_seconds()
 hashes={}
 for p in (ROOT/'candidates').glob('r23-*/manifest.json'):
  d=read(p);actual={f:hashlib.sha256((p.parent/f).read_bytes()).hexdigest()for f in ['parse.rs','Parse.lean']};assert d['hashes']==actual
  hashes[p.parent.name]=actual
 result={'status':'VERIFIED_COLLECTED_RAW_BYTES','checked_at_utc':dt.datetime.now(dt.timezone.utc).isoformat(),'dispatched_runs':len(dispatches),'run_conclusions':{k:m.get('conclusion')for k,m in run_meta.items()},'uncollected_run_ids':pending,'raw_file_count':len(raw),'raw_bytes':sum(v['bytes']for v in raw.values()),'raw_files':raw,'original_protocol_batches':standard,'original_paired_processes':sum(r['paired_processes']for r in standard),'native_encoder_batches':native,'native_encoded_rows_including_controls':sum(r['rows']for r in native),'full_gates':gates,'runner_seconds':seconds,'runner_minutes':seconds/60,'candidate_pairs':hashes,'distinct_candidate_rust_count':len({v['parse.rs']for v in hashes.values()}),'limits':['Runner sums are concurrent elapsed job seconds, not money or wall-budget usage.','Cancelled CI is not success; complete raw timing batches remain separately auditable.','No formal submission or private-corpus performance claim.']}
 a.output.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({k:result[k]for k in ['dispatched_runs','uncollected_run_ids','raw_file_count','raw_bytes','original_paired_processes','distinct_candidate_rust_count','runner_minutes']}))
if __name__=='__main__':main()
