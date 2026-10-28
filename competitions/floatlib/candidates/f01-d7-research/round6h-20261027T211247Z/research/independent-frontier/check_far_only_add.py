"""Fixed boundary oracle for frozen far-only guard, not an all-input proof."""
from pathlib import Path
from datetime import datetime, timezone
import importlib.util, hashlib, json
D=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('oracle',D/'same_exponent_add.py')
M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)

def selected(u,v):
    a=u&0x7fffffff;b=v&0x7fffffff
    hi,ha,la=(v,b,a) if a<b else (u,a,b)
    return hi if ha<0x7f800000 and ha-la>=(26<<23) else None

cases=set()
def add_pair(a,b):
    for sa in [0,0x80000000]:
        for sb in [0,0x80000000]:
            cases.add((a|sa,b|sb));cases.add((b|sb,a|sa))
edge_frac=[(0,0),(0,1),(1,0),(1,1),(0x7fffff,0),(0,0x7fffff),
           (0x7fffff,0x7fffff),(0x7ffffe,0x7fffff),(0x7fffff,0x7ffffe)]
for eh in [25,26,27,28,126,127,128,253,254]:
    for el in sorted({0,1,max(0,eh-27),max(0,eh-26),max(0,eh-25),eh}):
        for fh,fl in edge_frac:add_pair((eh<<23)|fh,(el<<23)|fl)
for lo in [0,1,0x7fffff,0x800000,0xffffff,0x32000000,0x327fffff,0x72000000]:
    for delta in [(26<<23)-1,26<<23,(26<<23)+1]:
        hi=lo+delta
        if hi<0x7f800000:add_pair(hi,lo)
for special in [0x7f800000,0x7f800001,0x7fc00000,0x7fffffff]:
    for lo in [0,1,0x800000,0x3f800000,0x7f7fffff]:add_pair(special,lo)
add_pair(0,0)
trace=hashlib.sha256();hits=0;misses=0;zero_lo=0;sub_lo=0;boundary={str(i):0 for i in [-1,0,1]}
for u,v in sorted(cases):
    out=selected(u,v);a=u&0x7fffffff;b=v&0x7fffffff
    hi=max(a,b);lo=min(a,b)
    if out is None:misses+=1
    else:
        hits+=1
        assert ((u>>23)&255)<255 and ((v>>23)&255)<255
        assert out==M.oracle(u,v),(hex(u),hex(v),hex(out),hex(M.oracle(u,v)))
        assert (hi>>23)-(lo>>23)>=26
        zero_lo+=lo==0;sub_lo+=0<lo<0x800000
    if hi>=0x7f800000 or (a==0 and b==0):assert out is None
    diff=hi-lo-(26<<23)
    if diff in [-1,0,1]:boundary[str(diff)]+=1
    trace.update(u.to_bytes(4,'little')+v.to_bytes(4,'little')+(0xffffffff if out is None else out).to_bytes(4,'little'))
bad_u,bad_v=0x3f800000,0xb3000001
assert selected(bad_u,bad_v) is None and M.oracle(bad_u,bad_v)==0x3f7fffff
runtime=D/'Runtime-far-only-add.lean.inc'
out={'at_utc':datetime.now(timezone.utc).isoformat(),'cases':len(cases),'hits':hits,'misses':misses,
     'hit_differences':0,'zero_low_hits':zero_lo,'subnormal_low_hits':sub_lo,
     'raw_difference_boundary_counts':boundary,'trace_sha256':trace.hexdigest(),
     'runtime_sha256':hashlib.sha256(runtime.read_bytes()).hexdigest(),
     'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
     'oracle_sha256':hashlib.sha256((D/'same_exponent_add.py').read_bytes()).hexdigest(),
     'exponent_gap25_counterexample':{'u':'3f800000','v':'b3000001','correct':'3f7fffff','bad_return_hi':'3f800000','new_guard':'MISS',
        'boundary':'Counterexample to exponent-gap25 absorption, not asserted to refute a different raw-distance25 guard. Threshold26 unchanged.'},
     'scope':'Fixed directed inputs only; exact integer minsub-unit addition/RNE oracle for accepted finite hits. Miss dispatch checked structurally and NaN/Inf/doublezero must miss. Original B2 fallback unchanged. No native host or Lean proof, no performance.',
     'random_cases':0}
(D/'far-only-add-model.json').write_text(json.dumps(out,indent=2)+'\n')
print(json.dumps({k:out[k] for k in ['cases','hits','misses','hit_differences','zero_low_hits','subnormal_low_hits','raw_difference_boundary_counts','runtime_sha256']}))
