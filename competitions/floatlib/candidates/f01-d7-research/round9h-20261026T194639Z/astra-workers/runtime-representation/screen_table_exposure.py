"""Exposure only, on completed R15 discovery; never timing or unseen confirmation."""
from pathlib import Path
from collections import defaultdict
import importlib.util,hashlib,json,time,datetime
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
model=ROOT/'competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-public-input-domain.py'
spec=importlib.util.spec_from_file_location('r14_public_model',model)
g=importlib.util.module_from_spec(spec);spec.loader.exec_module(g)
plan=ROOT/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40168687803/download-13caf4644cf1467e8717d9474d417b8a/diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
start=time.perf_counter();trace=hashlib.sha256();rows=[]
grouped=defaultdict(lambda:{'sampled_pairs':0,'native_pairs':0,'table_reads':0,'two_table_pairs':0,'zero_table_pairs':0})
def fast(u):
    a=u&0x7fffffff
    return a==0 or 0x0c000000<=a<0x7f800000
for c in json.loads(plan.read_text())['cases']:
    if c['kernel'] not in ('add','mul') or not c['timed']:continue
    total=min(256,c['work']);counts={'sampled_pairs':total,'native_pairs':0,'table_reads':0,'two_table_pairs':0,'zero_table_pairs':0}
    for j in range(total):
        if time.perf_counter()-start>3:raise RuntimeError('3 second cooperative bound exceeded')
        lo,hi=j*c['work']//total,(j+1)*c['work']//total
        i=lo+g.word(c['seed'],j,63)%(hi-lo)
        a=g.element(c,i,0,31);b=g.partner(c,i,a)
        native=c['kernel']=='add' or ((a>>23)&255)+((b>>23)&255)>=128
        reads=int(fast(a))+int(fast(b)) if native else 0
        counts['native_pairs']+=int(native);counts['table_reads']+=reads
        counts['two_table_pairs']+=int(native and reads==2)
        counts['zero_table_pairs']+=int(native and reads==0)
        for v in (i,a,b):trace.update(v.to_bytes(4,'little'))
    name=':'.join(c['name'].split(':')[:2])
    for k,v in counts.items():grouped[name][k]+=v
    rows.append({'case':c['name'],'work':c['work'],**counts})
result={'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'state':'SOURCE_MODEL_EXPOSURE_ONLY','run':40168687803,'plan_sha256':sha(plan),
 'generator_translation':str(model),'generator_translation_sha256':sha(model),'original_generator_sha256':sha(g.GEN),
 'plan':str(plan),'cases':len(rows),'trace_sha256':trace.hexdigest(),
 'elapsed_seconds':time.perf_counter()-start,'group_counts':dict(grouped),'case_counts':rows,
 'limitations':'Previously completed R15 discovery only. Python official-source translation is not independently cross-checked with Lean draws. Counts are unweighted samples, not phase time, benefit, confidence or adoption. Native LowScale routing and table-hit guards are modeled exactly at source level; tensor repair calls are not sampled.',
 'decision':'The constant-table change reaches ordinary ADD and native-MUL, but must pay a validity flag on native pairs without any table hits. Full original workload decides net value; no grid or new input selection is justified.'}
(HERE/'table-exposure.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'cases':len(rows),'elapsed_seconds':result['elapsed_seconds'],'groups':result['group_counts']}))
