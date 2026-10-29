"""Read-only old-input opportunity screen, not speed evidence or a timing bound."""
from pathlib import Path
import importlib.util, hashlib, json, time
from datetime import datetime, timezone

D = Path(__file__).resolve().parent
R = next(p for p in D.parents if (p/'AGENTS.md').exists())
OLD = R/'competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/research/independent-frontier'
spec = importlib.util.spec_from_file_location('old_generator', OLD/'same_exponent_add.py')
M = importlib.util.module_from_spec(spec); spec.loader.exec_module(M)
KEYS = ['e0_pair', 'e01_pair', 'one_e0', 'decode_miss', 'nan_pair', 'normal_pair', 'cast64_window', 'active_low_mul', 'low_mul', 'finite_pair']

def main():
    started = time.monotonic(); runs=[]
    for run in [40168687803,40169957447,40171180249]:
        base=R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
        idx=json.loads((base/'original-artifact-hashes.json').read_bytes()); prefix='diagnostics/f01-d7-public-suite/public-suite/'
        plan,ph=M.load_checked(base,idx,prefix+'public-drawn-plan.json')
        verdict,vh=M.load_checked(base,idx,prefix+'f01-r15-dev-packed-b2-1-verdict.json')
        work,wh=M.load_checked(base,idx,prefix+'public-cell-work.json')
        costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()}; total=sum(costs.values()); groups={}
        for c in plan['cases']:
            if c['kernel']!='add' or not c['timed']: continue
            cell=':'.join(c['name'].split(':')[:2]); g=groups.setdefault(cell,{'samples':0,**{k:0 for k in KEYS}})
            for j in range(256):
                lo,hi=j*c['work']//256,(j+1)*c['work']//256
                i=lo+M.E['word'](c['seed'],j,63)%(hi-lo)
                u=M.E['element'](c,i,0,31); v=M.partner(c,i,u)
                eu,ev=(u>>23)&255,(v>>23)&255; au,av=u&0x7fffffff,v&0x7fffffff
                finite=eu<255 and ev<255; scale=max(eu-1,0)+max(ev-1,0)
                hits=[eu==ev==0,eu<=1 and ev<=1,eu==0 or ev==0,
                      not((au==0 or 24<=eu<=254) and (av==0 or 24<=ev<=254)),
                      (eu==255 and u&0x7fffff!=0) or (ev==255 and v&0x7fffff!=0),
                      1<=eu<=254 and 1<=ev<=254,
                      24<=min(eu,ev) and max(eu,ev)<=254 and abs(eu-ev)<=39,
                      finite and 101<=scale<=123,finite and eu+ev<128,finite]
                g['samples']+=1
                for k,h in zip(KEYS,hits): g[k]+=int(h)
        for cell,g in groups.items():
            g['whole_cell_share']=costs[cell]/total
            g['equal_cost_proxy']={k:g['whole_cell_share']*g[k]/g['samples'] for k in KEYS}
        runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,
                     'groups':groups,'whole_op_shares':{op:sum(v for k,v in costs.items() if k.startswith(op+':'))/total for op in ['add','mul','sum','bmm']},
                     'proxy_NOT_upper_bound_or_speed':{k:sum(g['equal_cost_proxy'][k] for g in groups.values()) for k in KEYS}})
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'OLD_EXPOSED_INPUT_DOMAIN_SCREEN_ONLY',
         'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'generator_helper_sha256':hashlib.sha256((OLD/'same_exponent_add.py').read_bytes()).hexdigest(),
         'scope':'256 deterministic strata per timed ADD case from three already exposed R15 draws. Fractions times class costs assume equal cost and are not removable-time bounds. active_low_mul labels exponent relations of ADD inputs only, not MUL workloads.',
         'elapsed_seconds':time.monotonic()-started,'runs':runs}
    (D/'domain-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
    print(json.dumps([{'run':r['run'],'op':r['whole_op_shares'],'proxy':r['proxy_NOT_upper_bound_or_speed']} for r in runs]))
if __name__=='__main__': main()
