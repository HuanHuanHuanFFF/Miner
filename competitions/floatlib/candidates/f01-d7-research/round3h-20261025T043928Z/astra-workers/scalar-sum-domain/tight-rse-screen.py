"""Bounded exact product/scale exposure for literal 124/125/126 roundSelect."""
from pathlib import Path
from datetime import datetime,timezone
from collections import defaultdict
import ast,hashlib,json,random,runpy,time
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z'
G=runpy.run_path(str(OLD/'astra-public-input-domain.py'))
start=time.perf_counter();count=0;results=[]
for run in (40129155932,40152158687,40155753018):
    root=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
    path=next(root.glob('download-*/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'))
    cases=json.loads(path.read_bytes())['cases']
    vf=path.parent/'f01-d12-scalar-combined-verdict.json';wf=path.parent/'public-cell-work.json'
    v=json.loads(vf.read_bytes());w=json.loads(wf.read_bytes())
    cost={k:r['submission_ns']*w[k] for k,r in v['classes'].items()}
    groups=defaultdict(lambda:defaultdict(int));rows=[]
    for c in cases:
        if not c['timed'] or c['kernel']!='mul':continue
        stats=defaultdict(int)
        for j in range(512):
            assert count<65000 and time.perf_counter()-start<4.4
            lo,hi=j*c['work']//512,(j+1)*c['work']//512
            i=lo+G['word'](c['seed'],j,63)%(hi-lo)
            a=G['element'](c,i,0,31);b=G['partner'](c,i,a)
            ea,eb=(a>>23)&255,(b>>23)&255
            ma=(a&0x7fffff)|(0x800000 if ea else 0)
            mb=(b&0x7fffff)|(0x800000 if eb else 0)
            p=ma*mb;s=max(0,ea-1)+max(0,eb-1)
            stats['samples']+=1;count+=1
            if ea+eb>=128:continue
            stats['old_low128']+=1
            if p==0:
                stats['zero_product']+=1;continue
            if s<=123:stats['old_roundLow_nonzero']+=1
            if s in (124,125,126):
                stats[f'scale{s}_nonzero']+=1
                hit=p<(1<<(172-s))
                stats[f'scale{s}_tight_hit']+=hit
                stats['tight_hits']+=hit
        cell=':'.join(c['name'].split(':')[:2])
        for k,n in stats.items():groups[cell][k]+=n
        rows.append({'name':c['name'],'work':c['work'],'center':c['center'],'spread':c['spread'],
                     'subPct':c['subPct'],'zeroPct':c['zeroPct'],**stats})
    results.append({'run':run,'plan_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
      'verdict_sha256':hashlib.sha256(vf.read_bytes()).hexdigest(),
      'groups':{k:{**r,'cell_share_whole':cost[k]/sum(cost.values())} for k,r in groups.items()},'cases':rows})

oracle=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
raw=oracle.read_bytes();assert hashlib.sha256(raw).hexdigest()=='3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
tree=ast.parse(raw);env={}
exec(compile(ast.Module(body=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name=='rounded'],type_ignores=[]),str(oracle),'exec'),env)
def low(p,s,sign):
    if p==0:return sign<<31
    q,r=divmod(p,1<<(149-s));half=1<<(148-s)
    q+=int(r>half or (r==half and q&1))
    if q==0:return sign<<31
    if q==0x800000:return (sign<<31)|0x800000
    return (sign<<31)|(q&0x7fffff)
checks=0;trace=hashlib.sha256();outside=[];rng=random.Random(15250124)
for s in (124,125,126):
    width=172-s;shift=149-s
    values={0,1,(1<<width)-1,(1<<width)-2,1<<(shift-1),(1<<(shift-1))+1,
            (1<<shift)+(1<<(shift-1)),(2<<shift)+(1<<(shift-1))}
    values.update(rng.randrange(1<<width) for _ in range(512))
    for p in sorted(values):
        for sign in (0,1):
            assert time.perf_counter()-start<4.4
            old=env['rounded'](-p if sign else p,s-298,bool(sign))
            got=low(p,s,sign);assert old==got,(s,p,sign,old,got)
            trace.update(p.to_bytes(8,'little')+bytes([s,sign])+got.to_bytes(4,'little'));checks+=1
    p=(1<<width)+(1<<shift)
    old=env['rounded'](p,s-298);got=low(p,s,0);assert old!=got
    outside.append({'scale':s,'product':hex(p),'bound_rejects':True,'original':hex(old),'unguarded_roundLow':hex(got)})
out={'state':'FINITE_SOURCE_MODEL_ONLY','created_at_utc':datetime.now(timezone.utc).isoformat(),
     'pairs':count,'rounding_checks':checks,'external_timeout_ms':5000,'internal_limit_seconds':4.4,
     'elapsed_seconds':time.perf_counter()-start,'rounding_trace_sha256':trace.hexdigest(),
     'outside_domain_counterexamples':outside,'runs':results,
     'limitations':['No timing, Lean, or adoption claim.','Product zero excluded from target hits; old zero already skips log2/RNE.',
                    'Scalar exposure only; BMM raw replay also calls Submission.mul but its executed exposure is UNKNOWN.']}
(HERE/'tight-rse-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'pairs':count,'rounding_checks':checks,'elapsed_seconds':out['elapsed_seconds'],'outside':outside,
                 'runs':[{'run':r['run'],'groups':r['groups']} for r in results]}))
