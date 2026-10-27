"""R15 bounded, source-derived opportunity screen; no Lean or timing claims.

Generator reused read-only from R14's translation of Conjectures.io MIT source,
official commit 4b7e83841cc0c32c6529f533923c73d33b5ecf97.
"""
from pathlib import Path
from collections import defaultdict
from datetime import datetime, timezone
import hashlib, json, runpy, time

HERE = Path(__file__).resolve().parent
ROOT = next(p for p in HERE.parents if (p / 'AGENTS.md').exists())
OLD = ROOT / 'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z'
GEN = runpy.run_path(str(OLD / 'astra-public-input-domain.py'))
started = time.perf_counter()
MAX_READS = 180000
reads = 0
def elem(c, i, role=0, row=31):
    global reads
    reads += 1
    if reads > MAX_READS or time.perf_counter() - started > 4.4:
        raise RuntimeError('Bound exceeded; partial result not accepted')
    return GEN['element'](c, i, role, row)

def snan(w):
    return (w & 0x7fc00000) == 0x7f800000 and (w & 0x003fffff) != 0
def nan(w):
    return (w & 0x7fffffff) > 0x7f800000

out = {'status':'SOURCE_MODEL_ONLY', 'created_at_utc':datetime.now(timezone.utc).isoformat(),
       'limits':{'max_reads':MAX_READS,'internal_seconds':4.4,'external_process_timeout_ms':5000},
       'limitations':['Counts are not costs or speedups. Cell time is an upper bound on removable time.',
                       'R14 exposed draws only; Python generator not independently run against current Lean.',
                       'Sum sampled rows have bounded prefix/tail searches, UNKNOWN when exhausted.'],
       'runs':[]}
for run in (40129155932, 40152158687, 40155753018):
    base = ROOT / f'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/{run}'
    planfile = next(base.glob('download-*/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'))
    base = planfile.parent
    verdict = json.loads((base/'f01-d12-scalar-combined-verdict.json').read_bytes())
    work = json.loads((base/'public-cell-work.json').read_bytes())
    costs = {k:v['submission_ns']*work[k] for k,v in verdict['classes'].items()}
    total_ns = sum(costs.values())
    cases = json.loads(planfile.read_bytes())['cases']
    grouped = defaultdict(lambda:defaultdict(int)); scalar=[]; sums=[]
    for c in cases:
        if not c['timed']: continue
        cell = ':'.join(c['name'].split(':')[:2])
        if c['kernel'] == 'mul':
            row = {'name':c['name'],'work':c['work'],'samples':256}
            counts = defaultdict(int)
            for j in range(256):
                lo,hi = j*c['work']//256,(j+1)*c['work']//256
                i = lo + GEN['word'](c['seed'],j,63) % (hi-lo)
                a=elem(c,i); b=GEN['partner'](c,i,a)
                ea,eb=(a>>23)&255,(b>>23)&255
                for cutoff in (84,86,100,102):
                    counts[f'cutoff{cutoff}'] += ea+eb<=cutoff
                counts['low128'] += ea+eb<128
                counts['zero_low128'] += ea+eb<128 and ((a&0x7fffffff)==0 or (b&0x7fffffff)==0)
                counts['normal_low102'] += 0<ea<255 and 0<eb<255 and ea+eb<=102
            row.update(counts); scalar.append(row)
            for key,val in counts.items(): grouped[cell][key]+=val
            grouped[cell]['samples']+=256
        elif c['kernel']=='sum' and (c['specRate']>0 or c['mag']==2):
            for j in range(min(4,c['batch'])):
                b=j*c['batch']//min(4,c['batch']); n=c['length']; first=None; last=None
                for i in range(min(n,1024)):
                    if nan(elem(c,b*n+i,row=n)):
                        first=i; break
                if first is not None:
                    for i in range(n-1,max(first,n-1-1024),-1):
                        if snan(elem(c,b*n+i,row=n)):
                            last=i; break
                sums.append({'name':c['name'],'length':n,'batch':c['batch'],'row':b,
                             'first_raw_nan':first,'last_snan':last,
                             'known_saved_suffix_reads':last-first if last is not None else None})
    groups={k:{**v,'cell_share_whole':costs[k]/total_ns,'cell_ns':costs[k],
                   'hit_fractions':{key:val/v['samples'] for key,val in v.items() if key!='samples'}}
            for k,v in grouped.items()}
    out['runs'].append({'run':run,'plan_sha256':hashlib.sha256(planfile.read_bytes()).hexdigest(),
                        'plan':str(planfile.relative_to(ROOT)), 'scalar_groups':groups,
                        'scalar_cases':scalar,'sum_rows':sums,
                        'sum_cell_shares':{k:v/total_ns for k,v in costs.items() if k.startswith('sum:')}})
out['reads']=reads;out['elapsed_seconds']=time.perf_counter()-started
out['script_sha256']=hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
(HERE/'domain-screen.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'reads':reads,'elapsed_seconds':out['elapsed_seconds'],
 'runs':[{'run':r['run'],'groups':r['scalar_groups'],'sum_cell_shares':r['sum_cell_shares']} for r in out['runs']]}))
