from pathlib import Path
from datetime import datetime, timezone
import ast, importlib.util, json, hashlib, time
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
tree=ast.parse((D/'check_far_only_add.py').read_bytes());ns={}
exec(compile(ast.Module(body=[x for x in tree.body if isinstance(x,ast.FunctionDef) and x.name=='selected'],type_ignores=[]),'fixed-guard','exec'),ns)
assert hashlib.sha256((D/'Runtime-far-only-add.lean.inc').read_bytes()).hexdigest()=='d03e7c8e02e6b2b86fc1ca8ba476379248a06f2da8eee2b430d63a9152d7cc19'
keys=['hit','normal_low','subnormal_low','zero_low','same_sign_hit','opposite_sign_hit'];runs=[];start=time.monotonic()
for run in [40168687803,40169957447,40171180249]:
    base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());pre='diagnostics/f01-d7-public-suite/public-suite/'
    plan,ph=M.load_checked(base,idx,pre+'public-drawn-plan.json');v,vh=M.load_checked(base,idx,pre+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,pre+'public-cell-work.json')
    costs={k:x['submission_ns']*work[k] for k,x in v['classes'].items()};total=sum(costs.values());groups={}
    for c in plan['cases']:
        if c['kernel']!='add' or not c['timed']:continue
        cell=':'.join(c['name'].split(':')[:2]);g=groups.setdefault(cell,{'samples':0,**{k:0 for k in keys}})
        for j in range(256):
            lo,hi=j*c['work']//256,(j+1)*c['work']//256;i=lo+M.E['word'](c['seed'],j,63)%(hi-lo)
            u=M.E['element'](c,i,0,31);vv=M.partner(c,i,u);hit=ns['selected'](u,vv) is not None
            low=min(u&0x7fffffff,vv&0x7fffffff);same=(u^vv)<0x80000000;g['samples']+=1
            values=[hit,hit and low>=0x800000,hit and 0<low<0x800000,hit and low==0,hit and same,hit and not same]
            for k,h in zip(keys,values):g[k]+=h
    for cell,g in groups.items():
        g['whole_cell_share']=costs[cell]/total
        g['equal_cost_proxy']={k:g['whole_cell_share']*g[k]/g['samples'] for k in keys}
        assert g['hit']==g['normal_low']+g['subnormal_low']+g['zero_low']==g['same_sign_hit']+g['opposite_sign_hit']
    runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'groups':groups,
                 'proxy_NOT_upper_bound_or_speed':{k:sum(g['equal_cost_proxy'][k] for g in groups.values()) for k in keys}})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'runs':runs,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
     'runtime_sha256':'d03e7c8e02e6b2b86fc1ca8ba476379248a06f2da8eee2b430d63a9152d7cc19','elapsed_seconds':time.monotonic()-start,
     'scope':'Same256 deterministic strata per timed ADD case on three old exposed R15 plans. Uniform-per-cell source hit proxy only, not time bound/speed/probability. No source/threshold change, no new correctness sample.'}
(D/'far-only-exposure.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps([{'run':r['run'],**r['proxy_NOT_upper_bound_or_speed']} for r in runs]))
