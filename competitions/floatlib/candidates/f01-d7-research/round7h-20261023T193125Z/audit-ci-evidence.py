"""Read-only final inventory: every original artifact byte and candidate HEAD."""
from datetime import datetime,timezone
import hashlib,json,subprocess
from pathlib import Path

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[4]
CI=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
read=lambda p:json.loads(p.read_bytes())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()

def inside(base,relative):
 path=(base/relative).resolve();path.relative_to(base.resolve());return path

def main():
 state=read(ROOT/'competitions/floatlib/coordination/development-status.json')['research_round']
 assert state['id']=='R11-20261023T193125Z' and not state['active_ci']
 assert len(state['started_ci'])==len(state['completed_ci'])
 rows=[];events=[];members=0;unknown_times=[]
 for row in state['started_ci']:
  assert row['collected'] and row['run'] in state['completed_ci']
  base=CI/str(row['run']);ci=read(base/'ci-run.json');idx=read(base/'original-artifact-hashes.json')
  assert ci['databaseId']==row['run'] and ci['status']=='completed' and ci['event']=='workflow_dispatch'
  assert ci['headSha']==row['source_commit']==idx['artifact']['workflow_run']['head_sha']
  assert idx['artifact']['workflow_run']['id']==row['run']
  assert idx['artifact'] in read(base/'artifacts.json')['artifacts']
  artifact=inside(base,idx['directory'])
  for name,info in idx['files'].items():
   path=inside(artifact,name);assert path.stat().st_size==info['bytes'] and sha(path)==info['sha256'],str(path)
   members+=1
  dispatch=read(ROOT/row['dispatch_receipt'])
  assert dispatch['inputs'].get('allow_private','false')=='false'
  jobs=[j for j in ci['jobs'] if j['name']=='floatlib'];assert len(jobs)==1
  job=jobs[0];assert job['status']=='completed'
  if job.get('startedAt') and job.get('completedAt'):
   events.extend([(job['startedAt'],1,row['run']),(job['completedAt'],-1,row['run'])])
  else:unknown_times.append(row['run'])
  nested=artifact/'diagnostics/f01-d7-public-suite/public-suite'
  checked=[]
  if (nested/'summary.json').exists():
   summary=read(nested/'summary.json')
   assert summary['source_commit']==ci['headSha']
   assert summary['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
   assert summary['adapter_sha256']=='86084d93c52022f4f4a5cfb7969e2b4a035b9a4a4f1f8c6c7e74bd412eafca24'
   assert summary['suite_sha256']=='a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a'
   assert (nested/'official-source-clean.log').read_bytes()==b''
   plan=read(nested/'requested-plan.json')
   original_plan=subprocess.check_output(['git','cat-file','blob',ci['headSha']+':competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json'],cwd=ROOT)
   assert original_plan==(nested/'requested-plan.json').read_bytes()
   for result in summary['results']:
    name=result['candidate'];source=nested/'inputs'/name/'Kernel.lean'
    original=subprocess.check_output(['git','cat-file','blob',ci['headSha']+':competitions/floatlib/candidates/'+name+'/Kernel.lean'],cwd=ROOT)
    assert original==source.read_bytes() and sha(source)==result['kernel_sha256']
    checked.append({'candidate':name,'sha256':result['kernel_sha256'],'stage':result['stage'],
                    'full_gate':result['full_gate'],'statement_pass':result.get('statement_pass',False)})
  else:
   assert row['state']=='OUTER_ADAPTER_FAILURE_COLLECTED'
  rows.append({'run':row['run'],'seed':row['seed'],'source_commit':ci['headSha'],'conclusion':ci['conclusion'],
               'original_members':len(idx['files']),'artifact_index_sha256':sha(base/'original-artifact-hashes.json'),
               'ci_run_sha256':sha(base/'ci-run.json'),'candidate_inputs_from_actual_HEAD':checked,
               'unexecuted_candidates':row.get('unexecuted_candidates',[])})
 active=peak=0
 for stamp,delta,run in sorted(events):active+=delta;peak=max(peak,active);assert active>=0
 assert active==0 and peak<=2
 result={'recorded_at_utc':datetime.now(timezone.utc).isoformat(),'scope':'All original collected members and actual immutable CI HEAD inputs. Statement acceptance is not full-gate or new-entry acceptance.',
         'started':len(rows),'collected':len(rows),'active':0,'original_members_verified':members,
         'known_job_timing_count':len(rows)-len(unknown_times),'unknown_job_timings':unknown_times,
         'peak_concurrent_known_validation_jobs':peak,'private_runner_used':False,'rows':rows}
 destination=HERE/'all-ci-evidence-audit.json'
 with destination.open('x',encoding='utf-8',newline='\n') as out:out.write(json.dumps(result,ensure_ascii=False,indent=2)+'\n')
 print(json.dumps({k:result[k] for k in ('started','collected','active','original_members_verified','peak_concurrent_known_validation_jobs','unknown_job_timings')}))

if __name__=='__main__':main()
