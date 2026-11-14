"""Independent host exact-product corroboration of frozen29d09f diagnostic.
All two24-bit significand products fit binary64 exactly; no timing claim.
"""
from pathlib import Path
import datetime, hashlib, json, random, struct, sys
HERE=Path(__file__).resolve().parent
ROOT=Path(__file__).resolve().parents[6]
SOURCE=ROOT/'competitions/floatlib/candidates/f01-r21-r-scaled-u32-probe1/Kernel.lean'
assert hashlib.sha256(SOURCE.read_bytes()).hexdigest()=='29d09f90c3116932461df2cc64e773e59873922dfe0a8714e4880214a1de7f2b'
assert sys.float_info.mant_dig==53 and struct.calcsize('<f')==4
U32=(1<<32)-1
def val(u): return struct.unpack('<f',struct.pack('<I',u))[0]
def bits(f): return struct.unpack('<I',struct.pack('<f',f))[0]
def rn(f): return val(bits(f))
def core(u,v,mode='correct'):
    eu=(u>>23)&255; ev=(v>>23)&255
    if not(1<=eu<=254 and 1<=ev<=254 and 128<=eu+ev<=380): return None
    p=((u&0x7fffff)|0x800000)*((v&0x7fffff)|0x800000)
    rounded=rn(float(p))
    scale=2.0**(-24 if mode=='wrong_scale' else -23)
    z=int(rn(rounded*scale)) if mode!='missing_scale' else min(int(rounded),U32)
    if mode=='correct': assert (1<<23)<=z<(1<<25) and (z<(1<<24) or z%2==0)
    high=(p>>47) if mode=='pre_round_high' else z>>24
    q=z>>(high&31)
    e=(eu+ev-127+high)&U32
    return (((u^v)&0x80000000)|((e<<23)&U32)|((q-0x800000)&U32))&U32
rng=random.Random(2120004); pairs=[]
for eu,ev in [(1,127),(1,254),(64,64),(127,127),(126,254),(127,253),(254,126)]:
 for fu in [0,1,2,0x3fffff,0x7ffffe,0x7fffff]:
  for fv in [0,1,2,0x3fffff,0x7ffffe,0x7fffff]:
   for su in (0,0x80000000):
    for sv in (0,0x80000000): pairs.append((su|(eu<<23)|fu,sv|(ev<<23)|fv))
for _ in range(30000):
    eu=rng.randrange(1,255); ev=rng.randrange(1,255)
    pairs.append(((rng.randrange(2)<<31)|(eu<<23)|rng.randrange(1<<23),(rng.randrange(2)<<31)|(ev<<23)|rng.randrange(1<<23)))
checked=0; mutants={}; trace=hashlib.sha256()
for u,v in pairs:
    actual=core(u,v)
    if actual is None: continue
    expected=bits(val(u)*val(v)); checked+=1
    assert actual==expected,(hex(u),hex(v),hex(actual),hex(expected))
    trace.update(struct.pack('<III',u,v,actual))
    for mode in ('wrong_scale','missing_scale','pre_round_high'):
        if mode not in mutants:
            wrong=core(u,v,mode)
            if wrong!=expected: mutants[mode]={'u':f'{u:08x}','v':f'{v:08x}','expected':f'{expected:08x}','mutant':f'{wrong:08x}'}
assert len(mutants)==3
out={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'source_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),'scope':'Bounded independent host exact-product corroboration only. No Lean/publicMUL proof, workload coverage, timing or adoption.','guarded_pairs_checked':checked,'considered_pairs':len(pairs),'mismatches':0,'detected_mutants':mutants,'trace_sha256':trace.hexdigest(),'formal_bridge':'Still requires actual scaled_decode/cast and publicmul connection.'}
(HERE/'scaled-u32-controller-review.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out))
