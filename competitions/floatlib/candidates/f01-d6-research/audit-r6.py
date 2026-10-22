"""Derive R6 evidence from exact dispatches and downloaded original payloads."""
from pathlib import Path
import argparse, datetime, hashlib, json, subprocess

ROOT=Path.cwd(); OWN=Path(__file__).resolve().parent
RUNS=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
ap=argparse.ArgumentParser(); ap.add_argument('--git',action='store_true'); args=ap.parse_args()
def load(p): return json.loads(p.read_bytes())
def sha(b): return hashlib.sha256(b).hexdigest()
def save(p,v): p.write_bytes((json.dumps(v,ensure_ascii=False,indent=2)+'\n').encode())
window=load(OWN/'window.json'); jobs=[]; records=[]; verified=0; comparisons=[]
for dp in sorted(RUNS.glob('dispatch-*/dispatch.json')):
    d=load(dp)
    if not (d.get('checked_at_utc','')>=window['start_utc'] and d.get('inputs',{}).get('seed','').isdigit() and 701<=int(d['inputs']['seed'])<=799 and d.get('run')): continue
    rid=d['run']['databaseId']; rp=RUNS/str(rid)
    j={'run':rid,'seed':int(d['inputs']['seed']),'candidates':d['inputs']['candidates'].split(','),'source_commit':d['source_commit'],'dispatch':dp.relative_to(ROOT).as_posix(),'status':d['run']['status'],'collected':False}
    if (rp/'ci-run.json').exists():
        meta=load(rp/'ci-run.json'); assert meta['headSha']==d['source_commit'];j.update(status=meta['status'],conclusion=meta['conclusion'])
    if not (rp/'original-artifact-hashes.json').exists():jobs.append(j);continue
    index=load(rp/'original-artifact-hashes.json'); artifact=rp/index['directory']; assert index['artifact']['name']==f'floatlib-{rid}-receipts'
    for name,expected in index['files'].items():
        p=artifact/name;b=p.read_bytes();assert len(b)==expected['bytes'] and sha(b)==expected['sha256'],p
        if args.git:
            raw=subprocess.check_output(['git','show','HEAD:'+p.relative_to(ROOT).as_posix()]); assert raw==b,p
        verified+=1
    summary=load(artifact/'summary.json');assert summary['run_id']==str(rid) and summary['source_commit']==d['source_commit']
    provenance=load(artifact/'provenance.json');j.update(collected=True,artifact=artifact.relative_to(ROOT).as_posix(),provenance=provenance)
    for row in summary['results']:
        vpath=artifact/row['verdict'];v=load(vpath);name=row['candidate'];src=artifact/'inputs'/name/'Kernel.lean';digest=sha(src.read_bytes());assert digest==row['kernel_sha256']
        if name!='baseline':
            assert digest==sha((ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean').read_bytes())
        full=bool(row['full_gate']);assert not full or (v['passed'] and v['mode']=='gate' and v['stage']=='score' and len(v['classes'])==12 and len(v['rounds'])==25 and v['verifier_fingerprint']==v['verifier_fingerprint_end'])
        r={'run':rid,'seed':j['seed'],'candidate':name,'kernel_sha256':digest,'passed':v['passed'],'stage':v['stage'],'full_gate':full,'validation_mode':row['validation_mode'],'verdict_path':vpath.relative_to(ROOT).as_posix(),'verdict_sha256':sha(vpath.read_bytes()),'reason':v.get('reason','')}
        if full:
            ns={k:sum(c['submission_ns'] for n,c in v['classes'].items() if n.startswith(k+':')) for k in ['add','mul','sum','bmm']}
            ref={k:sum(c['incumbent_ns'] for n,c in v['classes'].items() if n.startswith(k+':')) for k in ns}
            ratio=sum(ns.values())/sum(ref.values());assert abs(ratio-v['ratio'])<1e-10
            r.update(operations_ns=ns,operations_reference_ns=ref,ratio=ratio,classes=v['classes'],paired_gain_p05=row.get('paired_gain_p05'))
        records.append(r)
    jobs.append(j)
for j in jobs:
    xs=[r for r in records if r['run']==j['run'] and r['full_gate']];parent=next((r for r in xs if r['candidate']=='f01-d5-stream-pack'),None)
    if not parent:continue
    for r in xs:
        if r['candidate'] in ('baseline','f01-d5-stream-pack'):continue
        operations={}
        for op in ['add','mul','sum','bmm']:
            pc={n:c for n,c in parent['classes'].items() if n.startswith(op+':')}
            raw=r['operations_ns'][op]/parent['operations_ns'][op]
            norm=sum(c['submission_ns']*r['classes'][n]['ratio']/c['ratio'] for n,c in pc.items())/sum(c['submission_ns'] for c in pc.values())
            operations[op]={'raw_candidate_over_parent':raw,'reference_normalized_candidate_over_parent':norm}
        norm=sum(c['submission_ns']*r['classes'][n]['ratio']/c['ratio'] for n,c in parent['classes'].items())/sum(parent['operations_ns'].values())
        comparisons.append({'run':j['run'],'seed':j['seed'],'candidate':r['candidate'],'kernel_sha256':r['kernel_sha256'],'parent_sha256':parent['kernel_sha256'],'operations':operations,'whole_entry_raw_candidate_over_parent':sum(r['operations_ns'].values())/sum(parent['operations_ns'].values()),'whole_entry_reference_normalized_candidate_over_parent':norm,'scope':'Controlled same runner; discovery or confirmation designation is recorded separately. Reference normalization does not create a direct paired candidate/champion result.'})
result={'window_id':'R6_NINETY_MINUTES_20261022','start_utc':window['start_utc'],'deadline_utc':window['deadline_utc'],'audited_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'jobs':jobs,'records':records,'comparisons':comparisons,'verified_original_payload_files':verified,'git_payloads_checked':args.git,'goal_status':'UNACHIEVED'}
save(OWN/'summary.json',result)
window['runs']=[{k:j[k] for k in ['run','seed','candidates','source_commit','status','collected']} for j in jobs];save(OWN/'window.json',window)
statep=ROOT/'competitions/floatlib/coordination/development-status.json';state=load(statep);state['updated_at_utc']=result['audited_at_utc'];state['active_jobs']=[j['run'] for j in jobs if j['status']!='completed'];state['collaboration']['active_ci']=window['runs'];state['collaboration']['evidence_summary']=(OWN/'summary.json').relative_to(ROOT).as_posix();save(statep,state)
print(json.dumps({'jobs':[{k:j.get(k) for k in ['run','status','conclusion','collected']} for j in jobs],'full_passes':[(r['candidate'],r['run']) for r in records if r['full_gate']],'comparisons':comparisons,'verified_payloads':verified},ensure_ascii=False,indent=2))
