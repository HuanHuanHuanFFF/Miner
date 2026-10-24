"""Bounded sampled eligibility on an already exposed actual public plan."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,random,time
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4];R=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7'
def functions(p,names,constants=()):
    tree=ast.parse(p.read_bytes());nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in names or isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id in constants for t in n.targets)]
    env={};exec(compile(ast.Module(body=nodes,type_ignores=[]),str(p),'exec'),env);return env
generator=R/'public-nonfinite-opportunity.py';assert hashlib.sha256(generator.read_bytes()).hexdigest()=='28eb38c9388f595960ea039e18b5783984cb2a0b0cdb182011449a0cd146e7a1'
g=functions(generator,{'word','ctz','element'},{'M32','M64'})
support=functions(ROOT/'competitions/floatlib/candidates/f01-d7-research/scalar-opportunity.py',{'partner'},{'M32'})
base=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357';index=json.loads((base/'original-artifact-hashes.json').read_bytes());stage=base/index['directory'];plan_path=stage/'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json';plan=json.loads(plan_path.read_bytes())
rng=random.Random(202610242118);start=time.perf_counter();rows=[];n_total=0
for c in plan['cases']:
    if c['kernel'] not in ('add','mul') or not c['timed']:continue
    length=c['work'];n=min(256,length)
    positions=list(range(length)) if length<=n else [0,length-1]+rng.sample(range(1,length-1),n-2)
    counts={'sample':n,'opposite_finite_exact_cancel':0,'same_exp_opposite_normal':0,'short_gap_int32_add':0,'normal_mul_exponent_shift':0}
    fixed_b=g['element'](c,0,1,31)
    for i in positions:
        a=g['element'](c,i,0,31);b=support['partner'](c,i,a,g['element'],g['word'],fixed_b);ex=(a>>23)&255;ey=(b>>23)&255
        counts['opposite_finite_exact_cancel']+=((a^b)==0x80000000 and ex<255)
        counts['same_exp_opposite_normal']+=(ex==ey and 24<=ex<=254 and bool((a^b)&0x80000000))
        counts['short_gap_int32_add']+=(min(ex,ey)>=24 and max(ex,ey)<=253 and abs(ex-ey)<=6)
        counts['normal_mul_exponent_shift']+=(1<=ex<=254 and 1<=ey<=254 and 128<=ex+ey<=380)
        n_total+=1
        if n_total%512==0:assert time.perf_counter()-start<5,'Local sampler exceeded5second cap'
    rows.append({'case':c['name'],'kernel':c['kernel'],'relation':c['relation'],'work':c['work'],'length':length,'counts':counts})
assert n_total>=5000, 'Scalar iterations must use c.work, not tensor c.length'
groups={}
for op in ('add','mul'):
    selected=[r for r in rows if r['kernel']==op];weight=sum(r['work'] for r in selected)
    groups[op]={k:sum(r['work']*r['counts'][k]/r['counts']['sample'] for r in selected)/weight for k in selected[0]['counts'] if k!='sample'}
result={'state':'SAMPLED_PUBLIC_ELIGIBILITY_ONLY','at_utc':datetime.now(timezone.utc).isoformat(),'run':40124283357,'seed':plan.get('seed',1425001),'plan_sha256':hashlib.sha256(plan_path.read_bytes()).hexdigest(),'generator_sha256':hashlib.sha256(generator.read_bytes()).hexdigest(),'samples':n_total,'wall_seconds':time.perf_counter()-start,'work_weighted_sample_hit_fractions':groups,'cases':rows,'scope':'At most256 selected positions per already exposed timed scalar case, using old checksum-anchored source transcription. Current input counts are samples, not exhaustive/new checksums, measured stage costs or speedup. No holdout generated/read, no Lean, no benchmark or CI.'}
(OUT/'development-scalar-coverage-sample.json').write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps({k:v for k,v in result.items() if k!='cases'}))
