"""Bounded far-add exposure and guard-equivalence model. Not Lean or timing."""
from pathlib import Path
from datetime import datetime,timezone
from collections import defaultdict
import hashlib,json,runpy,time
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z'
G=runpy.run_path(str(OLD/'astra-public-input-domain.py'))
start=time.perf_counter();count=0;wordmask=(1<<32)-1
def near(ex,ey):return ((ex-ey+25)&wordmask)<=50
guards=0
for ex in range(256):
    for ey in range(256):
        assert near(ex,ey)==(abs(ex-ey)<=25)
        guards+=1
results=[]
for run in (40129155932,40152158687,40155753018):
    root=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
    path=next(root.glob('download-*/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'))
    cases=json.loads(path.read_bytes())['cases']
    verdict=json.loads((path.parent/'f01-d12-scalar-combined-verdict.json').read_bytes())
    work=json.loads((path.parent/'public-cell-work.json').read_bytes())
    costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()}
    groups=defaultdict(lambda:defaultdict(int));rows=[]
    for c in cases:
        if not c['timed'] or c['kernel']!='add':continue
        stats=defaultdict(int)
        for j in range(256):
            assert count<33000 and time.perf_counter()-start<4.4
            lo,hi=j*c['work']//256,(j+1)*c['work']//256
            i=lo+G['word'](c['seed'],j,63)%(hi-lo)
            a=G['element'](c,i,0,31);b=G['partner'](c,i,a)
            ex,ey=(a>>23)&255,(b>>23)&255
            stats['normal_gap26']+=0<min(ex,ey) and max(ex,ey)<255 and abs(ex-ey)>=26
            stats['finite_gap27']+=max(ex,ey)<255 and abs(ex-ey)>=27
            stats['zero_finite']+=((a&0x7fffffff)==0 and ey<255) or ((b&0x7fffffff)==0 and ex<255)
            stats['new_guard_near']+=near(ex,ey)
            stats['low_decoder_reject']+=(1<=min(ex,ey)<=23)
            stats['samples']+=1;count+=1
        cell=':'.join(c['name'].split(':')[:2])
        for k,v in stats.items():groups[cell][k]+=v
        rows.append({'name':c['name'],'work':c['work'],'relation':c['relation'],'relParam':c['relParam'],**stats})
    bygroup={k:{**v,'cell_share_whole':costs[k]/sum(costs.values()),
                'fractions':{a:b/v['samples'] for a,b in v.items() if a!='samples'}} for k,v in groups.items()}
    results.append({'run':run,'plan_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'groups':bygroup,'cases':rows})
out={'state':'SOURCE_MODEL_ONLY','created_at_utc':datetime.now(timezone.utc).isoformat(),
     'pairs':count,'exhaustive_exponent_guard_pairs':guards,'external_timeout_ms':5000,
     'internal_limit_seconds':4.4,'elapsed_seconds':time.perf_counter()-start,
     'new_runtime_guard_expression':'((ex - ey + 25) mod 2^32) <= 50 iff abs(ex-ey)<=25 for 8-bit fields',
     'limitations':['Finite guard table is not Lean proof.','Scalar hit fractions are not timing fractions.','All input plans already exposed.'],
     'runs':results}
(HERE/'far-add-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'pairs':count,'guard_pairs':guards,'elapsed_seconds':out['elapsed_seconds'],
 'runs':[{'run':x['run'],'groups':x['groups']} for x in results]}))
