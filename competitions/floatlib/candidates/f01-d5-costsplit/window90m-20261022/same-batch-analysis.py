"""Describe controlled within-batch comparisons; preserve all original measurements."""
from pathlib import Path
import datetime,hashlib,json,os
OWN=Path(__file__).resolve().parent;ROOT=Path.cwd()
summary=json.loads((OWN/'summary.json').read_bytes());rows=[]
for job in summary['jobs']:
    if not job['collected']:continue
    group=[r for r in summary['records'] if r['run']==job['run'] and r['full_gate'] and r['candidate']!='baseline']
    parent=next((r for r in group if r['candidate']=='f01-d4-final-lowmul'),None)
    if parent is None:
        parent=next((r for r in group if r['candidate']=='f01-d5-stream-pack'),None)
    if parent is None:
        parent=next((r for r in group if r['candidate']=='f01-d4-packed10'),None)
    if parent is None:
        parent=next((r for r in group if r['candidate']=='f01-d4-add-sum-word'),None)
    if parent is None:continue
    p=json.loads((ROOT/parent['verdict_path']).read_bytes())
    for row in group:
        if row is parent:continue
        v=json.loads((ROOT/row['verdict_path']).read_bytes())
        ops={}
        for op in ['add','mul','sum','bmm']:
            pc={k:c for k,c in p['classes'].items() if k.startswith(op+':')}
            vc={k:c for k,c in v['classes'].items() if k.startswith(op+':')}
            ps=sum(c['submission_ns'] for c in pc.values());vs=sum(c['submission_ns'] for c in vc.values())
            pi=sum(c['incumbent_ns'] for c in pc.values());vi=sum(c['incumbent_ns'] for c in vc.values())
            ops[op]=dict(raw_candidate_over_parent=vs/ps,reference_normalized_candidate_over_parent=(vs/vi)/(ps/pi),reference_drift=vi/pi,parent_ns=ps,candidate_ns=vs)
        rows.append(dict(run=job['run'],cpu=job['cpu'],seed=row['seed'],parent=parent['candidate'],parent_kernel_sha256=parent['kernel_sha256'],candidate=row['candidate'],candidate_kernel_sha256=row['kernel_sha256'],operations=ops,parent_verdict_sha256=hashlib.sha256((ROOT/parent['verdict_path']).read_bytes()).hexdigest(),candidate_verdict_sha256=hashlib.sha256((ROOT/row['verdict_path']).read_bytes()).hexdigest()))
result=dict(updated_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),comparisons=rows,scope='Each exact full source is paired against the unchanged shipped reference. Rows are sequential candidates on one runner, not a separately interleaved direct-parent promotion gate. Confirmation uses new runners after freezing.')
p=OWN/'same-batch-comparisons.json';t=p.with_name(p.name+'.update-tmp');t.write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode());os.replace(t,p)
print(json.dumps([dict(run=r['run'],candidate=r['candidate'],ratios={k:round(v['reference_normalized_candidate_over_parent'],5) for k,v in r['operations'].items()}) for r in rows]))
