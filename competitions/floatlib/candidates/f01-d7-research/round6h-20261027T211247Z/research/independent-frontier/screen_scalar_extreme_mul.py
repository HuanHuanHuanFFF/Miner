"""Fixed scalar field-domain screen; no new runtime or floating oracle expansion."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util,json,hashlib,time
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
def partner(c,i,u):
    assert c['kernel']=='mul'
    w=M.E['word'](c['seed'],i,31)
    if c['relation']==5 and w%100<c['relParam']:return (w&0x80000000)|0x3f800000
    return M.partner(c,i,u)
keys=['zero_rawS102','inf_finiteS382','union','normal_zero','subnormal_or_zero_input_zero'];start=time.monotonic();runs=[]
for run in [40168687803,40169957447,40171180249]:
    base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());pre='diagnostics/f01-d7-public-suite/public-suite/'
    plan,ph=M.load_checked(base,idx,pre+'public-drawn-plan.json');v,vh=M.load_checked(base,idx,pre+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,pre+'public-cell-work.json')
    costs={k:x['submission_ns']*work[k] for k,x in v['classes'].items()};total=sum(costs.values());groups={}
    for c in plan['cases']:
        if c['kernel']!='mul' or not c['timed']:continue
        cell=':'.join(c['name'].split(':')[:2]);g=groups.setdefault(cell,{'samples':0,**{k:0 for k in keys}})
        for j in range(256):
            lo,hi=j*c['work']//256,(j+1)*c['work']//256;i=lo+M.E['word'](c['seed'],j,63)%(hi-lo)
            u=M.E['element'](c,i,0,31);vv=partner(c,i,u);eu,ev=(u>>23)&255,(vv>>23)&255;s=eu+ev
            z=s<=102;ov=s>=382 and eu<255 and ev<255
            g['samples']+=1
            for k,h in zip(keys,[z,ov,z or ov,z and eu>0 and ev>0,z and (eu==0 or ev==0)]):g[k]+=h
    for cell,g in groups.items():
        g['whole_cell_share']=costs[cell]/total;g['equal_cost_proxy']={k:g['whole_cell_share']*g[k]/g['samples'] for k in keys}
        assert g['union']==g['zero_rawS102']+g['inf_finiteS382']
        assert g['zero_rawS102']==g['normal_zero']+g['subnormal_or_zero_input_zero']
    runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'groups':groups,
                 'proxy_NOT_upper_bound_or_speed':{k:sum(g['equal_cost_proxy'][k] for g in groups.values()) for k in keys}})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'runs':runs,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
     'elapsed_seconds':time.monotonic()-start,'scope':'Scalar MUL only, same256 deterministic strata per timed case on three already seen R15 plans. Relation5 correctly produces signed1.0 for MUL, not ADD signedzero. These weighted source-domain proxies are not timing bounds, speed, probability or BMM underflow exposure.',
     'runtime':'NONE','thresholds':'Mathematically selected S<=102 and finite S>=382, no sweep; S103/381 left to exact old operation.'}
(D/'scalar-extreme-mul-exposure.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps([{'run':r['run'],**r['proxy_NOT_upper_bound_or_speed']} for r in runs]))
