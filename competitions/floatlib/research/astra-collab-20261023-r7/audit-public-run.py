from pathlib import Path
from datetime import datetime,timezone
import argparse,hashlib,json,math
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[3]
ap=argparse.ArgumentParser();ap.add_argument('--artifact',required=True);ap.add_argument('--parent',default='f01-d5-stream-pack');ap.add_argument('--candidates',nargs='+',required=True);ap.add_argument('--output',required=True);args=ap.parse_args()
A=ROOT/args.artifact
paths=list(A.glob('diagnostics/*/public-suite/summary.json'));assert len(paths)==1
D=paths[0].parent;summary=json.loads(paths[0].read_text())
weights=json.loads((D/'public-cell-work.json').read_text())
assert hashlib.sha256((D/'public-v2.json').read_bytes()).hexdigest()==summary['suite_sha256']
env=json.loads((A/'provenance.json').read_text())
def one(name):
    row=next(r for r in summary['results'] if r['candidate']==name)
    p=D/row['verdict'];v=json.loads(p.read_text())
    assert hashlib.sha256(p.read_bytes()).hexdigest()==row['verdict_sha256']
    stored=D/'inputs'/name/'Kernel.lean'
    if stored.exists():assert hashlib.sha256(stored.read_bytes()).hexdigest()==row['kernel_sha256']
    local=ROOT/'competitions/floatlib/candidates'/name/'Kernel.lean'
    if local.exists():assert hashlib.sha256(local.read_bytes()).hexdigest()==row['kernel_sha256']
    result={'candidate':name,'sha256':row['kernel_sha256'],'passed':v['passed'],'stage':v['stage'],'reason':v['reason'],'verdict':str(p.relative_to(ROOT)),'verdict_sha256':row['verdict_sha256']}
    if v['passed']:
        assert row['full_gate'] and row['exit_code']==0 and v['mode']=='gate' and v['stage']=='score'
        assert len(v['rounds'])==25 and set(v['classes'])==set(weights)
        assert v['suite']['sha256']==summary['suite_sha256']
        assert v['verifier_fingerprint']==v['verifier_fingerprint_end']
        log=(D/(name+'-gate.log')).read_text()
        for item in ['Submission replays cleanly','VerifyFull replays cleanly',"['Classical.choice', 'Quot.sound', 'propext']"]:assert item in log
        cells={k:{'sub':x['submission_ns']*weights[k],'ref':x['incumbent_ns']*weights[k],'spread_sub':x['spread_sub'],'spread_ref':x['spread_inc']} for k,x in v['classes'].items()}
        sub=sum(c['sub'] for c in cells.values());ref=sum(c['ref'] for c in cells.values())
        assert math.isclose(sub/ref,v['ratio'],rel_tol=1e-12)
        assert math.isclose(sub,row['scored_submission_total_ns'],rel_tol=1e-12)
        shares={op:sum(c['sub'] for k,c in cells.items() if k.startswith(op+':'))/sub for op in ['add','mul','sum','bmm']}
        result.update(full_gate='PASS_ACTUAL_CURRENT_PUBLIC_SUITE',cells=cells,shares=shares,sub_total_ns=sub,ref_total_ns=ref,headline=v['ratio'],gate_log_sha256=hashlib.sha256((D/(name+'-gate.log')).read_bytes()).hexdigest(),fingerprint=v['verifier_fingerprint'])
    return result
parent=one(args.parent);assert parent['passed']
results=[]
for name in args.candidates:
    r=one(name)
    if r['passed']:
        comp={}
        for op in ['add','mul','sum','bmm','whole']:
            def total(q,key):return sum(x[key] for k,x in q['cells'].items() if op=='whole' or k.startswith(op+':'))
            comp[op]={'raw_new_over_parent':total(r,'sub')/total(parent,'sub'),'reference_normalized_new_over_parent':(total(r,'sub')/total(r,'ref'))/(total(parent,'sub')/total(parent,'ref')),'reference_drift':total(r,'ref')/total(parent,'ref')}
        r['comparison']=comp
    results.append(r)
out={'audited_at_utc':datetime.now(timezone.utc).isoformat(),'seed':summary['seed'],'official_commit':summary['official_commit'],'source_commit':summary['source_commit'],'suite_sha256':summary['suite_sha256'],'plan_sha256':summary['requested_plan_sha256'],'cell_work_sha256':hashlib.sha256((D/'public-cell-work.json').read_bytes()).hexdigest(),'cpu':next((x.strip() for x in env.get('lscpu','').splitlines() if 'Model name:' in x),'UNKNOWN'),'parent':parent,'results':results,'scope':'Exact real nested full gates, saved source, original replays/three axioms/fingerprint/25rounds; weighted current-public-plan observations. No private-suite/current-champion claim or independent-confirmation claim unless separately established.'}
target=HERE/args.output;assert target.resolve().is_relative_to(HERE.resolve());target.write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({'seed':out['seed'],'cpu':out['cpu'],'results':[{'candidate':r['candidate'],'passed':r['passed'],'reason':r['reason'],'comparison':r.get('comparison')} for r in results]},indent=2))
