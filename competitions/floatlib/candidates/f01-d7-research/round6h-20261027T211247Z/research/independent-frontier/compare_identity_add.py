"""Separate raw-identity proposal; finite models and old draw opportunity only."""
import importlib.util,json,hashlib,time,random
from pathlib import Path
from datetime import datetime,timezone
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('sameexp',D/'same_exponent_add.py');M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)

def guard(u,v):return ((u^v)&0x7fffffff)==0 and (u&0x7fffffff)<0x7f800000
def core(u,v):
    if u!=v:return 0
    m=u&0x7fffffff;s=u&0x80000000
    if m<0x800000:return s|(m<<1)
    if m>=0x7f000000:return s|0x7f800000
    return u+0x800000

def main():
    st=time.monotonic();rng=random.Random(2202);n=0;trace=hashlib.sha256()
    words=[0,0x80000000,1,0x80000001,0x7fffff,0xffffff,0x7f7fffff,0xff7fffff]
    words += [(e<<23)|f|s for e in range(255) for f in [0,1,2,3,0x3fffff,0x400000,0x7ffffe,0x7fffff] for s in [0,0x80000000]]
    words += [(rng.randrange(255)<<23)|rng.getrandbits(23)|(rng.getrandbits(1)<<31) for _ in range(30000)]
    for u in words:
        for v in [u,u^0x80000000]:
            assert guard(u,v);q=core(u,v);assert q==M.oracle(u,v),(hex(u),hex(v),hex(q),hex(M.oracle(u,v)))
            trace.update(q.to_bytes(4,'little'));n+=1
    runs=[]
    for run in [40168687803,40169957447,40171180249]:
        base=M.R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}';idx=json.loads((base/'original-artifact-hashes.json').read_bytes());prefix='diagnostics/f01-d7-public-suite/public-suite/'
        plan,ph=M.load_checked(base,idx,prefix+'public-drawn-plan.json');verdict,vh=M.load_checked(base,idx,prefix+'f01-r15-dev-packed-b2-1-verdict.json');work,wh=M.load_checked(base,idx,prefix+'public-cell-work.json')
        costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};total=sum(costs.values());groups={}
        for c in plan['cases']:
            if c['kernel']!='add' or not c['timed']:continue
            cell=':'.join(c['name'].split(':')[:2]);g=groups.setdefault(cell,{'samples':0,'identity':0,'cancel_nonzero':0,'doubling_nonzero':0,'zeros':0,'sameexp':0,'union':0})
            for j in range(256):
                lo,hi=j*c['work']//256,(j+1)*c['work']//256;i=lo+M.E['word'](c['seed'],j,63)%(hi-lo)
                u=M.E['element'](c,i,0,31);v=M.partner(c,i,u);h=guard(u,v);he=M.guard(u,v)
                g['samples']+=1;g['identity']+=h;g['sameexp']+=he;g['union']+=h or he
                g['cancel_nonzero']+=h and u!=v and (u&0x7fffffff)!=0
                g['doubling_nonzero']+=h and u==v and (u&0x7fffffff)!=0
                g['zeros']+=h and (u&0x7fffffff)==0
        for cell,g in groups.items():
            g['cell_share_whole']=costs[cell]/total
            for key in ['identity','sameexp','union','cancel_nonzero','doubling_nonzero','zeros']:
                g[key+'_equal_cost_proxy']=g[key]/g['samples']*g['cell_share_whole']
        runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'groups':groups,'proxy_NOT_speed_or_upper_bound':{k:sum(g[k+'_equal_cost_proxy'] for g in groups.values()) for k in ['identity','sameexp','union','cancel_nonzero','doubling_nonzero','zeros']}})
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'model':{'cases':n,'differences':0,'trace_sha256':trace.hexdigest()},'runs':runs,'elapsed_seconds':time.monotonic()-st,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'scope':'Finite exact oracle and exposed 3 R15 plan source model only; no Lean/native timing/holdout. Proxy assumes equal per-pair cost within cell and is not a ceiling or speedup.'}
    (D/'identity-add-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8');print(json.dumps({'model':out['model'],'runs':[{'run':r['run'],**r['proxy_NOT_speed_or_upper_bound']} for r in runs],'elapsed_seconds':out['elapsed_seconds']}))
if __name__=='__main__':main()
