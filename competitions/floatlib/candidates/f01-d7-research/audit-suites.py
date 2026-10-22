"""Read exact nested current-official public-suite verdicts, never legacy aliases."""
from pathlib import Path
import datetime, hashlib, json, subprocess

ROOT=Path.cwd();OWN=Path(__file__).resolve().parent
RUNS=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs'
rows=[];comparisons=[]
for rid in sorted(int(p.parent.name) for p in RUNS.glob('[0-9]*/ci-run.json') if int(p.parent.name)>=39832394805):
    rp=RUNS/str(rid);ip=rp/'original-artifact-hashes.json'
    if not ip.exists():continue
    index=json.loads(ip.read_bytes());artifact=rp/index['directory'];stage=artifact/'diagnostics/f01-d7-public-suite/public-suite'
    if not (stage/'summary.json').exists():continue
    for filename,info in index['files'].items():
        payload=(artifact/filename).read_bytes();assert len(payload)==info['bytes'] and hashlib.sha256(payload).hexdigest()==info['sha256'],filename
    summary=json.loads((stage/'summary.json').read_bytes());assert summary['official_commit']=='4b7e83841cc0c32c6529f533923c73d33b5ecf97'
    if 'adapter_sha256' in summary:
        original=subprocess.check_output(['git','show',summary['source_commit']+':competitions/floatlib/candidates/f01-d7-research/public-suite.py'])
        assert hashlib.sha256(original).hexdigest()==summary['adapter_sha256']
        assert hashlib.sha256((stage/'requested-plan.json').read_bytes()).hexdigest()==summary['requested_plan_sha256']
    suite=(stage/'public-v2.json').read_bytes();assert hashlib.sha256(suite).hexdigest()==summary['suite_sha256']
    assert (stage/'official-source-clean.log').read_bytes()==b''
    work=json.loads((stage/'public-cell-work.json').read_bytes());assert all(w>0 for w in work.values())
    for entry in summary['results']:
        vp=stage/entry['verdict'];v=json.loads(vp.read_bytes());k=stage/'inputs'/entry['candidate']/'Kernel.lean';digest=hashlib.sha256(k.read_bytes()).hexdigest();assert digest==entry['kernel_sha256']
        row={'run':rid,'candidate':entry['candidate'],'kernel_sha256':digest,'official_commit':summary['official_commit'],'suite_sha256':summary['suite_sha256'],'seed':summary['seed'],'full_gate':entry['full_gate'],'statement_pass':entry.get('statement_pass',False),'stage':v['stage'],'reason':v.get('reason',''),'verdict':vp.relative_to(ROOT).as_posix(),'verdict_sha256':hashlib.sha256(vp.read_bytes()).hexdigest()}
        if entry['full_gate']:
            assert v['passed'] and v['mode']=='gate' and v['stage']=='score' and len(v['rounds'])==25
            assert v['verifier_fingerprint']==v['verifier_fingerprint_end'] and v['suite']['sha256']==summary['suite_sha256']
            times={op:sum(c['submission_ns']*work[n] for n,c in v['classes'].items() if n.startswith(op+':')) for op in ['add','mul','sum','bmm']}
            ref={op:sum(c['incumbent_ns']*work[n] for n,c in v['classes'].items() if n.startswith(op+':')) for op in times}
            ratio=sum(times.values())/sum(ref.values());assert abs(ratio-v['ratio'])<1e-10
            row.update(ratio=ratio,operation_total_ns=times,operation_reference_total_ns=ref,time_share_percent={op:t/sum(times.values())*100 for op,t in times.items()},classes=v['classes'],cell_work=work,verifier_fingerprint=v['verifier_fingerprint'])
        rows.append(row)
    batch=[r for r in rows if r['run']==rid and r['full_gate']];parent=next((r for r in batch if r['candidate']=='f01-d5-stream-pack'),None)
    if parent:
        for r in batch:
            if r is parent:continue
            comparisons.append({'run':rid,'seed':r['seed'],'candidate':r['candidate'],'kernel_sha256':r['kernel_sha256'],'parent_sha256':parent['kernel_sha256'],'whole_entry_raw_candidate_over_parent':sum(r['operation_total_ns'].values())/sum(parent['operation_total_ns'].values()),'whole_entry_headline_ratio_normalized_candidate_over_parent':r['ratio']/parent['ratio'],'operations_raw_candidate_over_parent':{op:r['operation_total_ns'][op]/parent['operation_total_ns'][op] for op in parent['operation_total_ns']},'operations_reference_normalized_candidate_over_parent':{op:(r['operation_total_ns'][op]/r['operation_reference_total_ns'][op])/(parent['operation_total_ns'][op]/parent['operation_reference_total_ns'][op]) for op in parent['operation_total_ns']},'scope':'Same runner and public plan; discovery sample, not independent confirmation or private champion comparison.'})
out={'as_of_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'protocol':'Original official4b7e838 public-v2;152scored cases,26cells,25rounds','records':rows,'comparisons':comparisons,'baseline_environment_validation':'Exact parent8eb current original public-v2 complete gate control in every comparison batch; shipped reference measured by each unchanged gate','champion_direct_ratio':'UNKNOWN_PRIVATE_SUITE_AND_SOURCE_UNAVAILABLE','champion_replacement':'UNACHIEVED'}
(OWN/'public-suite-results.json').write_bytes((json.dumps(out,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps({'records':[{k:r.get(k) for k in ['run','candidate','full_gate','statement_pass','stage','reason','ratio','time_share_percent']} for r in rows],'comparisons':comparisons},ensure_ascii=False,indent=2))
