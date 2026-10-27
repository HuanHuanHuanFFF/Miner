from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[3]
D=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39793280952/download-ee29d23604144525bb4a144a8603ba38'
summary=json.loads((D/'summary.json').read_text());prov=json.loads((D/'provenance.json').read_text())
parent=json.loads((D/'f01-d5-stream-pack-verdict.json').read_text())
rows=[]
for name in ['f01-r6-normal-mul-proof1','f01-r6-active-bias-proof1','f01-r6-web-absorption26-proof1']:
    p=D/(name+'-verdict.json');v=json.loads(p.read_text());s=next(x for x in summary['results'] if x['candidate']==name)
    b=(ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean').read_bytes()
    assert hashlib.sha256(b).hexdigest()==s['kernel_sha256']
    row={'candidate':name,'sha256':s['kernel_sha256'],'stage':v['stage'],'passed':v['passed'],'reason':v['reason'],'verdict':str(p.relative_to(ROOT)),'verdict_sha256':hashlib.sha256(p.read_bytes()).hexdigest()}
    if v['passed']:
        assert s['full_gate'] and len(v['rounds'])==25 and len(v['classes'])==12
        log=(D/(name+'-gate.log')).read_text()
        assert 'Submission replays cleanly' in log and 'VerifyFull replays cleanly' in log
        assert "['Classical.choice', 'Quot.sound', 'propext']" in log
        comps={}
        for prefix in ['mul:','']:
            sums=[]
            for vv in [parent,v]:
                cs=[x for k,x in vv['classes'].items() if k.startswith(prefix)]
                sn=sum(x['submission_ns'] for x in cs);rn=sum(x['incumbent_ns'] for x in cs);sums.append((sn,rn,sn/rn))
            a,b=sums;comps[prefix or 'whole']={'parent_sub':a[0],'candidate_sub':b[0],'raw_new_over_parent':b[0]/a[0],'reference_normalized_new_over_parent':b[2]/a[2],'reference_drift':b[1]/a[1]}
        row.update(full_gate='PASS_LEGACY12_25',comparisons=comps,classes=v['classes'],parent_classes=parent['classes'],decision='PARK_PERFORMANCE_REGRESSION')
    else:
        err=D/'diagnostics'/name/'full-build-output.txt'
        row.update(build_output=str(err.relative_to(ROOT)),build_output_sha256=hashlib.sha256(err.read_bytes()).hexdigest(),reported_error_lines=[x for x in err.read_text().splitlines() if x.startswith('error:')],full_gate='FAIL_STATEMENT_NO_PERFORMANCE')
    rows.append(row)
out={'audited_at_utc':datetime.now(timezone.utc).isoformat(),'run':39793280952,'seed':707,'source_commit':summary['source_commit'],'official_commit':summary['official_commit'],'cpu':next(x.strip() for x in prov['lscpu'].splitlines() if 'Model name:' in x),'results':rows,'scope':'Actual exact-source legacy gate evidence. No cross-suite champion inference.'}
(HERE/'full-and-failed-results-707.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'run':out['run'],'cpu':out['cpu'],'results':[{'candidate':r['candidate'],'passed':r['passed'],'comparisons':r.get('comparisons'),'error_count':len(r.get('reported_error_lines',[]))} for r in rows]},indent=2))
