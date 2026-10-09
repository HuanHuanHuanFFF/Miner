"""Account for collected R18 runner time without inventing billing or token costs."""
from pathlib import Path
from datetime import datetime,timezone
from collections import Counter
import argparse,hashlib,json

ROOT=Path(__file__).resolve().parents[1]
E=ROOT/'evidence/round18'

def dt(s):return datetime.fromisoformat(s.replace('Z','+00:00'))
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--output',type=Path,required=True);args=ap.parse_args();out=args.output.resolve();assert out.is_relative_to(E.resolve())and not out.exists()
    budget=json.loads((E/'budget.json').read_bytes());now=datetime.now(timezone.utc);dispatch={};runs={};audit={}
    for p in E.glob('dispatch-*.json'):
        j=json.loads(p.read_bytes());rid=str(j['run']['databaseId']);assert rid not in dispatch;dispatch[rid]=j;audit[str(p.relative_to(ROOT))]=sha(p)
    for p in E.glob('*/**/ci-run.json'):
        j=json.loads(p.read_bytes());rid=str(j['databaseId'])
        if rid not in dispatch:continue
        assert j['headSha']==dispatch[rid]['git_sha']and j['headBranch']=='codex/round18-frontier'and j['status']=='completed'
        audit[str(p.relative_to(ROOT))]=sha(p)
        if rid in runs:
            assert runs[rid]['conclusion']==j['conclusion']and runs[rid]['headSha']==j['headSha']
        else:runs[rid]=j
    details=[];job_ids=set();durations=[];queues=[]
    for rid,run in sorted(runs.items(),key=lambda kv:kv[1]['createdAt']):
        active=[]
        for job in run['jobs']:
            if job['conclusion']=='skipped':continue
            assert job['databaseId']not in job_ids and job['status']=='completed';job_ids.add(job['databaseId']);seconds=(dt(job['completedAt'])-dt(job['startedAt'])).total_seconds();assert seconds>=0;durations.append(seconds)
            active.append({'job_id':job['databaseId'],'job_name':job['name'],'started_at':job['startedAt'],'completed_at':job['completedAt'],'conclusion':job['conclusion'],'runner_wall_seconds':seconds})
        queue=max(0,(min(dt(j['started_at'])for j in active)-dt(run['createdAt'])).total_seconds())if active else 0;queues.append(queue)
        details.append({'run_id':rid,'batch':dispatch[rid]['batch'],'mode':dispatch[rid]['mode'],'git_sha':run['headSha'],'conclusion':run['conclusion'],'queue_to_first_runner_seconds':queue,'runner_wall_seconds':sum(j['runner_wall_seconds']for j in active),'jobs':active})
    usage=json.loads((E/'usage-observations.json').read_bytes());paired={}
    for p in E.glob('*/**/state.json'):
        j=json.loads(p.read_bytes());rid=j.get('run_id')
        if rid in runs:
            keys={(m['candidate'],m['round'])for m in j.get('metrics',[])};paired.setdefault(rid,set()).update(keys)
    result={'status':'VERIFIED_COLLECTED_CI_ACCOUNTING_SNAPSHOT','recorded_at_utc':now.isoformat(),'fixed_start_utc':budget['start_utc'],'fixed_deadline_utc':budget['deadline_utc'],'wall_clock_elapsed_seconds':(now-dt(budget['start_utc'])).total_seconds(),'wall_clock_remaining_seconds':max(0,(dt(budget['deadline_utc'])-now).total_seconds()),'dispatched_run_count':len(dispatch),'collected_completed_run_count':len(runs),'not_yet_collected_run_ids':sorted(set(dispatch)-set(runs)),'collected_modes':dict(Counter(x['mode']for x in details)),'collected_conclusions':dict(Counter(x['conclusion']for x in details)),'completed_runner_job_count':len(job_ids),'completed_runner_wall_seconds':sum(durations),'queue_seconds_to_first_runner_sum':sum(queues),'original_screen_confirmation_paired_processes':sum(len(v)for v in paired.values()),'latest_shared_account_observation':usage[-1]if usage else None,'successful_resets':budget['reset']['successes'],'formal_uploads_in_this_research':0,'new_registrations_or_wallet_signatures':0,'cloud_money_cost':'UNKNOWN; billing was not queried','model_tokens_or_money_attributable_to_this_task':'UNKNOWN; account percentage is shared usage, not task cost','runs':details,'input_sha256':audit,'scope':'Completed job start/end intervals sum concurrent runner wall time, not elapsed research time or billed minutes. Missing local receipts do not establish that a run is still running. Diagnostic and gate measurements are separate from original screening/confirmation paired-process count. Immutable CI/dispatch inputs are cited by hash.'}
    out.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({k:v for k,v in result.items()if k not in('runs','input_sha256')}))

if __name__=='__main__':main()
