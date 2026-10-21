"""Capture public GitHub job identities for the three frozen confirmation runs."""
from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,importlib,json
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--label',required=True);a=ap.parse_args();assert a.label in ['start','final'];out=E/('confirmation-runners-'+a.label);out.mkdir(exist_ok=False);h=importlib.import_module('collect-round2');env=h.gh_env();repo='HuanHuanHuanFFF/Miner';runs=['38106900587','38106909000','38106920250'];records=[];selected=[]
    for run in runs:
        began=datetime.now(timezone.utc).isoformat();raw=h.run(['api',f'repos/{repo}/actions/runs/{run}/jobs?per_page=100'],env).encode();ended=datetime.now(timezone.utc).isoformat();p=out/(run+'.response.json');p.write_bytes(raw);data=json.loads(raw);jobs=[j for j in data['jobs']if j['name']=='round24'];assert len(jobs)==1;j=jobs[0];dispatch=json.loads((E/f'dispatch-{run}.json').read_bytes());assert j['head_sha']==dispatch['git_sha'] and j['run_id']==int(run)
        assert j['runner_id']and j['runner_name']and 'self-hosted'not in j.get('labels',[])
        if a.label=='final':assert j['status']=='completed'
        selected.append({'run_id':run,'job_id':j['id'],'head_sha':j['head_sha'],'status':j['status'],'conclusion':j.get('conclusion'),'started_at':j['started_at'],'completed_at':j.get('completed_at'),'runner_id':j['runner_id'],'runner_name':j['runner_name'],'runner_group_name':j.get('runner_group_name'),'labels':j.get('labels'),'html_url':j['html_url']})
        records.append({'file':p.name,'sha256':hashlib.sha256(raw).hexdigest(),'bytes':len(raw),'request_started_utc':began,'request_finished_utc':ended,'source':'GitHubCLI API response body capture'})
    unique=len({j['runner_id']for j in selected});assert unique==3
    if a.label=='final':
        initial=json.loads((E/'confirmation-runners-start/receipt.json').read_bytes());assert {(j['run_id'],j['runner_id'],j['job_id'])for j in initial['jobs']}=={(j['run_id'],j['runner_id'],j['job_id'])for j in selected}
    result={'status':'VERIFIED_THREE_DISTINCT_GITHUB_RUNNER_IDENTITIES','label':a.label,'repository':repo,'captured_utc':datetime.now(timezone.utc).isoformat(),'distinct_runner_ids':unique,'jobs':selected,'raw_responses':records,'scope':'DistinctGitHubrunner/job identities forfrozenSHA confirmations. This doesnotprove distinctphysicalhosts or remove hostnoise; CPU/toolchain/perfiletimes remainin eachoriginalbenchmarkreceipt.'};(out/'receipt.json').write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps({'status':result['status'],'jobs':selected},indent=2))
if __name__=='__main__':main()
