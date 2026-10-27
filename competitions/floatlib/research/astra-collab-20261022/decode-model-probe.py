"""Finite diagnostic for a numeric binary32 decoder. Not a Lean proof or timing."""
from pathlib import Path
import datetime, hashlib, json, random, struct

HERE = Path(__file__).resolve().parent
def f32word(w):
    return struct.unpack('<f', struct.pack('<I', w))[0]
def word32(x):
    return struct.unpack('<I', struct.pack('<f', x))[0]
def decode(w):
    e = (w >> 23) & 255
    assert e < 255
    m = (w & 0x7fffff) | (0x800000 if e else 0)
    scale = 1 if e == 0 else (1 << (e - 1) if e < 24 else (e - 23) << 23)
    scale |= w & 0x80000000
    # M <= 2^24-1, so the first cast is exact. The double product is exact
    # for these binary32 operands; packing performs the final binary32 rounding.
    native_m = f32word(word32(float(m)))
    return word32(native_m * f32word(scale))

edges = {0,1,2,3,0x7fffff,0x7ffffe,0x400000,0x3fffff}
for k in range(23):
    for d in (-1,0,1):
        v=(1<<k)+d
        if 0 <= v <= 0x7fffff: edges.add(v)
words = [s | (e << 23) | f for s in (0,0x80000000) for e in range(255) for f in sorted(edges)]
edge_count = len(words)
rng=random.Random(20261022)
while len(words) < edge_count + 65536:
    w=rng.getrandbits(32)
    if ((w>>23)&255) < 255: words.append(w)
digest=hashlib.sha256()
failures=[]
for w in words:
    actual=decode(w)
    digest.update(struct.pack('<II',w,actual))
    if w != actual and len(failures)<16: failures.append({'input':f'{w:08x}','actual':f'{actual:08x}'})
result={'status':'PASS_FINITE_DIAGNOSTIC' if not failures else 'FAIL',
 'scope':'Numeric reconstruction of finite binary32 raw values including both signed zeros and subnormals; no Lean or target timing claim.',
 'cases':len(words),'systematic_cases':edge_count,'seeded_random_cases':65536,
 'biased_exponents':list(range(255)),'signs':[0,1],'systematic_fractions':sorted(edges),
 'trace_sha256':digest.hexdigest(),'first_failures':failures,
 'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
 'completed_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat()}
(HERE/'decode-model-probe.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8')
print(json.dumps({k:result[k] for k in ('status','cases','trace_sha256','first_failures')},indent=2))
