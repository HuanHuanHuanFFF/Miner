"""Conservative source-header guarantee for allfast A; no input generation or new runtime."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,json,hashlib
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
runs=[]
for run in [40168687803,40169957447,40171180249]:
    base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());pre='diagnostics/f01-d7-public-suite/public-suite/'
    plan,ph=M.load_checked(base,idx,pre+'public-drawn-plan.json');v,vh=M.load_checked(base,idx,pre+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,pre+'public-cell-work.json')
    cost={k:x['submission_ns']*work[k] for k,x in v['classes'].items()};total=sum(cost.values())
    under=json.loads((D/f'underflow-summary-{run}.json').read_bytes());old43={r['name']:r['whole_certificates']['old43'] for r in under['cases']};rows=[]
    for c in plan['cases']:
        if not c['timed'] or c['kernel']!='bmm':continue
        b,m,n,p=(c[k] for k in ['batch','m','n','p'])
        eligible=n>1 and m>=4 and p>=2 and not old43[c['name']]
        lower=c['center']-c['spread']-(c['scaleShift'] if c['scaleBlock'] else 0)
        guarantee=(c['mag']!=2 and c['specRate']==0 and c['subPct']==0 and lower>=24
                   and (c['zeroPct']==0 or c['zeroKind'] in [0,1,2]))
        if not eligible:continue
        groups=b*(m//4);G=(p+1)//2;cell=':'.join(c['name'].split(':')[:2])
        rows.append({'name':c['name'],'shape':[b,m,n,p],'all_A_fastOK_guaranteed_from_header':guarantee,
                     'ordinary_exp_lower_bound':lower,'full4_groups':groups,'column_groups':G,
                     'scan_reads_if_all_pass':4*n*groups,'existing_A_decode_checks_in_full_groups':4*n*groups*G,
                     'full_group_loop_iterations':n*groups*G,
                     'whole_uniform_case_and_row_proxy_if_guaranteed':
                        cost[cell]/total*c['work']/work[cell]*(4*(m//4)/m) if guarantee else 0})
    runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,
                 'guaranteed_cases':[r['name'] for r in rows if r['all_A_fastOK_guaranteed_from_header']],
                 'uniform_proxy_NOT_time_bound_or_speed':sum(r['whole_uniform_case_and_row_proxy_if_guaranteed'] for r in rows),
                 'cases':rows})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
     'runs':runs,'scope':'Conservative generator-header implication only on three prefreeze old plans; false means UNKNOWN, not rejection. Runtime would still scan raw data. No shape/threshold/source tuning. Uniform case/row proxies are not timing bounds or attainable gains.',
     'new_runtime':'NONE','new_CI':False}
(D/'warm-a-header-screen.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps([{'run':r['run'],'guaranteed_cases':r['guaranteed_cases'],'uniform_proxy':r['uniform_proxy_NOT_time_bound_or_speed']} for r in runs]))
