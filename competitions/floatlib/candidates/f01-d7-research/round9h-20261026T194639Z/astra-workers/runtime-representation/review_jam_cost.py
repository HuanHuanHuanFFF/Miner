"""Read-only independent source-cost review of the current Jam17 mechanism."""
from pathlib import Path
import hashlib,json,re,datetime
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
JAM=HERE.parent/'exact-arithmetic'
header=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/upstream/lean-lean.h'
sha=lambda b:hashlib.sha256(b).hexdigest()
h=header.read_bytes();assert sha(h)=='982c731a1fbacc7688006f44f9f7af9d9e3e0247d310a728827f49e7f1466c13'
t=h.decode();sources=[]
for p in [header,JAM/'Jam17.lean.inc',JAM/'Probe-jam17-v1.lean',JAM/'Kernel-jam17-public-v1.draft.lean']:
    b=p.read_bytes();sources.append({'path':str(p),'bytes':len(b),'sha256':sha(b)})
primitives=[]
for name in ['lean_uint32_to_float32','lean_float32_to_uint32','lean_uint64_to_float32','lean_float32_to_uint64','lean_float32_to_int32']:
    m=re.search(r'^static inline [^\n]+\b'+name+r'\([^\n]*\)\s*\{',t,re.M);assert m,name
    i=m.end();depth=1
    while depth:
        if t[i]=='{':depth+=1
        elif t[i]=='}':depth-=1
        i+=1
    b=t[m.start():i]
    primitives.append({'name':name,'line':t.count('\n',0,m.start())+1,'body':b,'sha256':sha(b.encode())})
result={'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'state':'INDEPENDENT_FIXED_SOURCE_COST_REVIEW_ONLY','sources':sources,'primitives':primitives,
 'verified_source_facts':['jamWord adds a low17-nonzero flag after shift17 and narrows to UInt32','normalCore exposes both 24-bit masks before the UInt64 product','UInt32 reverse contains 0/2^32 saturation and no external isnan call','signed32 reverse contains external lean_float32_isnan; switching sign type is not assumed cheaper'],
 'unknown':['Exact accepted diagnostic/public caller lowering','Clamp removal','P/J/R spills and function boundaries','Net path cost versus B2','Whole discovery performance'],
 'next_decision':'After the single already-planned compilation, inspect actual accepted-path C/ASM. Do not start a signed variant or explicit-mask variant without a concrete surviving-code symptom.',
 'resource':{'ci_runs':0,'local_compiler_runs':0,'tokens':'UNKNOWN','cached_input_tokens':'UNKNOWN'}}
(HERE/'jam17-cost-review.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'sources':len(sources),'fixed_primitives':len(primitives),'jam_runtime_sha':sources[1]['sha256']}))
