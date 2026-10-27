"""Residual raw-zero opportunity after cutoff84, bounded source model only."""
from pathlib import Path
from datetime import datetime,timezone
from collections import defaultdict
import hashlib,json,runpy,time
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
OLD=ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z'
G=runpy.run_path(str(OLD/'astra-public-input-domain.py'))
start=time.perf_counter();count=0;results=[]
for run,baseline in ((39904491256,'f01-d7-direct-nonnan'),(40129155932,'f01-d12-scalar-combined'),
                     (40152158687,'f01-d12-scalar-combined'),(40155753018,'f01-d12-scalar-combined')):
    root=ROOT/f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
    path=next(root.glob('download-*/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'))
    cases=json.loads(path.read_bytes())['cases']
    verdictfile=path.parent/(baseline+'-verdict.json')
    verdict=json.loads(verdictfile.read_bytes());work=json.loads((path.parent/'public-cell-work.json').read_bytes())
    costs={k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()}
    groups=defaultdict(lambda:defaultdict(int));rows=[]
    for c in cases:
        if not c['timed'] or c['kernel']!='mul':continue
        stat=defaultdict(int);hist=defaultdict(int)
        for j in range(256):
            assert count<44000 and time.perf_counter()-start<4.4
            lo,hi=j*c['work']//256,(j+1)*c['work']//256
            i=lo+G['word'](c['seed'],j,63)%(hi-lo)
            a=G['element'](c,i,0,31);b=G['partner'](c,i,a)
            ex,ey=(a>>23)&255,(b>>23)&255;s=ex+ey
            za=(a&0x7fffffff)==0;zb=(b&0x7fffffff)==0
            stat['low128']+=s<128;stat['cutoff84']+=s<=84
            stat['zero_low128']+=(za or zb) and s<128
            stat['zero_low128_already_cutoff84']+=(za or zb) and s<=84
            residual=(za or zb) and 84<s<128
            stat['zero_residual85_127']+=residual
            stat['nonzero_residual85_127']+=not(za or zb) and 84<s<128
            if residual:hist[str(s)]+=1
            stat['samples']+=1;count+=1
        cell=':'.join(c['name'].split(':')[:2])
        for k,v in stat.items():groups[cell][k]+=v
        rows.append({'name':c['name'],'work':c['work'],**stat,'residual_exponent_histogram':dict(hist)})
    bygroup={k:{**v,'cell_share_whole':costs[k]/sum(costs.values()),
                'fractions':{a:b/v['samples'] for a,b in v.items() if a!='samples'}} for k,v in groups.items()}
    sample_total=sum(v['samples'] for v in groups.values())
    results.append({'run':run,'baseline':baseline,'plan_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
                    'verdict_sha256':hashlib.sha256(verdictfile.read_bytes()).hexdigest(),
                    'total_mul_samples':sample_total,'residual_samples':sum(v['zero_residual85_127'] for v in groups.values()),
                    'groups':bygroup,'cases':rows})
out={'state':'SOURCE_MODEL_ONLY','created_at_utc':datetime.now(timezone.utc).isoformat(),'pairs':count,
     'external_timeout_ms':5000,'internal_limit_seconds':4.4,'elapsed_seconds':time.perf_counter()-start,
     'scope':'Exact old low branch and any signed-zero input, excluding exsum<=84 already covered. Counts are not cost.',
     'cost_limit':'Complete cell scored cost is an upper bound only; actual residual-path time UNKNOWN.',
     'runs':results}
(HERE/'lowzero-residual-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'pairs':count,'elapsed_seconds':out['elapsed_seconds'],
 'runs':[{'run':x['run'],'residual_samples':x['residual_samples'],'groups':x['groups']} for x in results]}))
