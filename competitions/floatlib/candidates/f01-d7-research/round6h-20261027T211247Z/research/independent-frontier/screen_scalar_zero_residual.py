from pathlib import Path
from datetime import datetime,timezone
import ast,importlib.util,json,hashlib
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('gen',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
tree=ast.parse((D/'screen_scalar_extreme_mul.py').read_bytes());env={'M':M}
exec(compile(ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name=='partner'],type_ignores=[]),'mul-partner','exec'),env)
keys=['finite_raw_zero','residual_S103_127','residual_S128plus','union_with_extremes'];runs=[]
for run in [40168687803,40169957447,40171180249]:
    base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());pre='diagnostics/f01-d7-public-suite/public-suite/'
    plan,ph=M.load_checked(base,idx,pre+'public-drawn-plan.json');v,vh=M.load_checked(base,idx,pre+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,pre+'public-cell-work.json')
    costs={k:x['submission_ns']*work[k] for k,x in v['classes'].items()};total=sum(costs.values());groups={}
    for c in plan['cases']:
        if c['kernel']!='mul' or not c['timed']:continue
        cell=':'.join(c['name'].split(':')[:2]);g=groups.setdefault(cell,{'samples':0,**{k:0 for k in keys}})
        for j in range(256):
            lo,hi=j*c['work']//256,(j+1)*c['work']//256;i=lo+M.E['word'](c['seed'],j,63)%(hi-lo)
            u=M.E['element'](c,i,0,31);vv=env['partner'](c,i,u);eu,ev=(u>>23)&255,(vv>>23)&255;s=eu+ev
            zero=eu<255 and ev<255 and (u&0x7fffffff==0 or vv&0x7fffffff==0)
            vals=[zero,zero and 103<=s<128,zero and s>=128,zero or s<=102 or (s>=382 and eu<255 and ev<255)]
            g['samples']+=1
            for k,h in zip(keys,vals):g[k]+=h
    for cell,g in groups.items():g['equal_cost_proxy']={k:costs[cell]/total*g[k]/g['samples'] for k in keys}
    runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'groups':groups,
                 'proxy_NOT_upper_bound_or_speed':{k:sum(g['equal_cost_proxy'][k] for g in groups.values()) for k in keys}})
out={'at_utc':datetime.now(timezone.utc).isoformat(),'runs':runs,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
     'scope':'Same fixed old scalar MUL strata only. Separates prior e139 low-branch zero domain from high-zero residual. No new guard/runtime/correctness samples or speed bound.'}
(D/'scalar-zero-residual-exposure.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps([{'run':r['run'],**r['proxy_NOT_upper_bound_or_speed']} for r in runs]))
