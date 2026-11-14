"""Exact same-sign/same-exponent ADD model and bounded exposed-domain screen.

Independent oracle uses integer multiples of 2^-149 and general binary32 RNE.
The runtime formula has no float operation, general alignment or leading search.
"""
import ast, hashlib, json, random, time
from pathlib import Path
from datetime import datetime, timezone

D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
G=R/'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
tree=ast.parse(G.read_bytes()); E={}
nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in {'word','ctz','element'} or isinstance(n,ast.Assign) and any(isinstance(z,ast.Name) and z.id in {'M32','M64'} for z in n.targets)]
exec(compile(ast.Module(body=nodes,type_ignores=[]),str(G),'exec'),E)

def decode(u):
    e=(u>>23)&255; f=u&0x7fffff
    assert e<255
    m=f if e==0 else (0x800000|f)<<(e-1)
    return -m if u>>31 else m

def encode(q,negative_zero=False):
    if q==0:return 0x80000000 if negative_zero else 0
    sign=0x80000000 if q<0 else 0; n=abs(q)
    if n<1<<24:return sign|n
    shift=n.bit_length()-24
    lo=n&((1<<shift)-1); m=n>>shift; half=1<<(shift-1)
    m+=lo>half or (lo==half and m&1)
    if m==1<<24:m>>=1;shift+=1
    e=shift+1
    return sign|0x7f800000 if e>=255 else sign|(e<<23)|(m-0x800000)

def oracle(u,v):
    return encode(decode(u)+decode(v),u==v==0x80000000)

def guard(u,v):return (u^v)<0x800000 and (u&0x7f800000)!=0x7f800000

def core(u,v):
    t=(u&0x7fffff)+(v&0x7fffff); e=u&0x7f800000; s=u&0x80000000
    if e==0:return s|t
    if e==0x7f000000:return s|0x7f800000
    r=(t+((t>>1)&1))>>1
    return s|(e+0x800000+r)

def partner(c,i,a):
    w=E['word'](c['seed'],i,31); r=c['relation']
    if r==1:return a
    if r==2:return a^0x80000000
    if r in (3,7):
        mask=(1<<min(23,c['relParam']))-1; b=(a&(~mask&0xffffffff))|(w&mask)
        return b^0x80000000 if r==3 else b
    if r==4:return E['element'](c,0,1,31)
    if r==5 and w%100<c['relParam']:return w&0x80000000
    if r==6:
        ea=(a>>23)&255
        if ea not in (0,255):return (w&0x807fffff)|(max(1,min(254,ea-c['relParam']))<<23)
    return E['element'](c,i,1,31)

def load_checked(base,idx,name):
    p=base/idx['directory']/name;b=p.read_bytes();h=hashlib.sha256(b).hexdigest()
    assert h==idx['files'][name]['sha256'],name
    return json.loads(b),h

def main():
    start=time.monotonic(); trace=hashlib.sha256(); count=0
    fs=[0,1,2,3,4,5,6,7,0x3fffff,0x400000,0x7ffffb,0x7ffffc,0x7ffffd,0x7ffffe,0x7fffff]
    for e in range(255):
        for s in [0,0x80000000]:
            for a in fs:
                for b in fs:
                    u=s|(e<<23)|a;v=s|(e<<23)|b
                    assert guard(u,v)
                    out=core(u,v);assert out==oracle(u,v),(hex(u),hex(v),hex(out),hex(oracle(u,v)))
                    trace.update(out.to_bytes(4,'little'));count+=1
    rng=random.Random(2201)
    for _ in range(30000):
        e=rng.randrange(255);s=rng.getrandbits(1)<<31
        u=s|(e<<23)|rng.getrandbits(23);v=s|(e<<23)|rng.getrandbits(23)
        out=core(u,v);assert out==oracle(u,v);trace.update(out.to_bytes(4,'little'));count+=1
    model={'cases':count,'differences':0,'trace_sha256':trace.hexdigest(),'scope':'Finite integer oracle only; not Lean or exhaustive proof'}
    runs=[]
    for run in [40168687803,40169957447,40171180249]:
        base=R/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
        idx=json.loads((base/'original-artifact-hashes.json').read_bytes());prefix='diagnostics/f01-d7-public-suite/public-suite/'
        plan,ph=load_checked(base,idx,prefix+'public-drawn-plan.json')
        verdict,vh=load_checked(base,idx,prefix+'f01-r15-dev-packed-b2-1-verdict.json')
        work,wh=load_checked(base,idx,prefix+'public-cell-work.json')
        costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()};total=sum(costs.values())
        groups={};rows=[]
        for c in plan['cases']:
            if c['kernel']!='add' or not c['timed']:continue
            n=min(256,c['work']);hits=0;sub=0;over=0
            for j in range(n):
                lo,hi=j*c['work']//n,(j+1)*c['work']//n
                i=lo+E['word'](c['seed'],j,63)%(hi-lo)
                u=E['element'](c,i,0,31);v=partner(c,i,u)
                if guard(u,v):
                    hits+=1;sub+=((u>>23)&255)==0;over+=((u>>23)&255)==254
            cell=':'.join(c['name'].split(':')[:2]);g=groups.setdefault(cell,{'samples':0,'hits':0,'subnormal_or_zero_hits':0,'overflow_hits':0})
            for k,v in [('samples',n),('hits',hits),('subnormal_or_zero_hits',sub),('overflow_hits',over)]:g[k]+=v
            rows.append({'name':c['name'],'samples':n,'hits':hits,'relation':c['relation'],'relParam':c['relParam']})
        for k,g in groups.items():
            g['cell_share_whole']=costs[k]/total;g['hit_fraction']=g['hits']/g['samples'];g['equal_cost_proxy']=g['cell_share_whole']*g['hit_fraction']
        runs.append({'run':run,'plan_sha256':ph,'verdict_sha256':vh,'work_sha256':wh,'add_whole_ceiling':sum(v for k,v in costs.items() if k.startswith('add:'))/total,'equal_cost_proxy_NOT_upper_bound':sum(g['equal_cost_proxy'] for g in groups.values()),'groups':groups,'cases':rows})
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'model':model,'runs':runs,'elapsed_seconds':time.monotonic()-start,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'generator_translation_sha256':hashlib.sha256(G.read_bytes()).hexdigest(),'limits':'Exposed R15 public draws only; 256 stratified scalar pairs/case. Equal-cost weighting is a proxy, NOT a timing upper bound, real saving, future prevalence or success probability. No Lean or native timing.'}
    (D/'same-exponent-add.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
    print(json.dumps({'model':model,'runs':[{'run':r['run'],'proxy':r['equal_cost_proxy_NOT_upper_bound'],'add_share':r['add_whole_ceiling']} for r in runs],'elapsed_seconds':out['elapsed_seconds']}))

if __name__=='__main__':main()
