from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,math
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[3]
RUN=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39794432216/download-cb6051c5206745749e7caaaf3b04f68b'
D=RUN/'diagnostics/f01-d6-public-suite/public-suite'
summary=json.loads((D/'summary.json').read_text());weights=json.loads((D/'public-cell-work.json').read_text())
assert hashlib.sha256((D/'public-v2.json').read_bytes()).hexdigest()==summary['suite_sha256']
records=[]
for name in ['f01-d5-stream-pack','f01-r6-normal-add-proof1']:
    p=D/(name+'-verdict.json');v=json.loads(p.read_text());s=next(x for x in summary['results'] if x['candidate']==name)
    assert v['passed'] and v['stage']=='score' and v['mode']=='gate' and s['full_gate']
    assert len(v['rounds'])==25 and len(v['classes'])==26
    assert s['kernel_sha256']==hashlib.sha256((ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean').read_bytes()).hexdigest()
    log=(D/(name+'-gate.log')).read_text()
    for x in ['Submission replays cleanly','VerifyFull replays cleanly',"['Classical.choice', 'Quot.sound', 'propext']"]:assert x in log
    cells={k:{'sub':x['submission_ns']*weights[k],'ref':x['incumbent_ns']*weights[k]} for k,x in v['classes'].items()}
    total=sum(x['sub'] for x in cells.values());ref=sum(x['ref'] for x in cells.values())
    assert math.isclose(total/ref,v['ratio'],rel_tol=1e-12)
    assert math.isclose(total,s['scored_submission_total_ns'],rel_tol=1e-12)
    shares={op:sum(x['sub'] for k,x in cells.items() if k.startswith(op+':'))/total for op in ['add','mul','sum','bmm']}
    records.append({'candidate':name,'sha256':s['kernel_sha256'],'full_gate':'PASS_PUBLIC_V2_26CELLS_25ROUNDS','headline':v['ratio'],'total_sub_ns':total,'total_ref_ns':ref,'shares':shares,'cells':cells,'verdict':str(p.relative_to(ROOT)),'verdict_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'gate_log_sha256':hashlib.sha256((D/(name+'-gate.log')).read_bytes()).hexdigest()})
a,b=records
comparison={}
for op in ['add','mul','sum','bmm','whole']:
    def ss(r,key):return sum(x[key] for k,x in r['cells'].items() if op=='whole' or k.startswith(op+':'))
    comparison[op]={'raw_new_over_parent':ss(b,'sub')/ss(a,'sub'),'reference_normalized_new_over_parent':(ss(b,'sub')/ss(b,'ref'))/(ss(a,'sub')/ss(a,'ref')),'reference_drift':ss(b,'ref')/ss(a,'ref')}
out={'audited_at_utc':datetime.now(timezone.utc).isoformat(),'run':39794432216,'seed':719,'official_commit':summary['official_commit'],'suite_sha256':summary['suite_sha256'],'plan_sha256':summary['requested_plan_sha256'],'cell_work_sha256':hashlib.sha256((D/'public-cell-work.json').read_bytes()).hexdigest(),'parent_and_candidate':records,'comparison':comparison,'decision':'Single shared public plan; approximately0.3% whole normalized difference is not a material confirmed gain. No independent new-suite confirmation or private paid-suite/current-champion result. Shares are observed for this current candidate/public plan only.','frozen_D_combination':'c18748c6 statementFAIL from active-bias bridge; no timing recorded'}
(HERE/'public-suite-719.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:v for k,v in out.items() if k not in ['parent_and_candidate']}|{'shares':{r['candidate']:r['shares'] for r in records}},indent=2))
