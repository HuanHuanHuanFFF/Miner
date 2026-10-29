"""Finite exact-integer/host-double check of a total normal-input MUL core.

No Lean, native compilation, timing, new-track implementation or gate claims.
The input factors are binary32, so their finite product has at most48bits and is
exact in binary64 before the final struct binary32 conversion.
"""
from pathlib import Path
from collections import Counter
import hashlib
import json
import random
import struct
import time

HERE=Path(__file__).resolve().parent
MASK=0x7fffff

def rne_shift(n,d):
    if d<=0:return n<<(-d)
    q,r=divmod(n,1<<d)
    return q+int(r>(1<<(d-1)) or r==(1<<(d-1)) and q&1)

def normal_all(u,v):
    eu,ev=u>>23&255,v>>23&255
    assert 1<=eu<=254 and 1<=ev<=254
    s=eu+ev;sign=(u^v)&0x80000000
    if s<103:return sign
    if s<128:
        p=((u&MASK)|0x800000)*((v&MASK)|0x800000)
        d=151-s
        return sign|((p+((1<<(d-1))-1)+((p>>d)&1))>>d)
    if 381<s:return sign|0x7f800000
    p=((u&MASK)|0x800000)*((v&MASK)|0x800000)
    t=23 if p<(1<<47) else 24
    biased=p+((1<<(t-1))-1)+((p>>t)&1)
    high=biased>>47
    q=biased>>(23+high)
    e=s-127+high
    return sign|(0x7f800000 if e>=255 else (e<<23)|(q-0x800000))

def generic_exact(u,v):
    s=(u>>23&255)+(v>>23&255)
    sign=(u^v)&0x80000000
    p=((u&MASK)|0x800000)*((v&MASK)|0x800000)
    power=s-300
    leading=p.bit_length()-1+power
    if leading < -126:
        q=rne_shift(p,-149-power)
        return sign|q
    q=rne_shift(p,p.bit_length()-24)
    if q==1<<24:q>>=1;leading+=1
    if leading>127:return sign|0x7f800000
    return sign|((leading+127)<<23)|(q-(1<<23))

def host_exact(u,v):
    x=struct.unpack('<f',struct.pack('<I',u))[0]
    y=struct.unpack('<f',struct.pack('<I',v))[0]
    try:return struct.unpack('<I',struct.pack('<f',x*y))[0]
    except OverflowError:return ((u^v)&0x80000000)|0x7f800000

def main():
    started=time.monotonic();counts=Counter();trace=hashlib.sha256();n=0;counterexamples=[]
    fractions=((0,0),(MASK,MASK),(0,MASK),(MASK,0),(1,MASK-1),(0x400000,0x400000),(0x3fffff,0x7ffffe),(0x7ffffe,0x3fffff))
    def check(u,v):
        nonlocal n
        a,b,c=normal_all(u,v),generic_exact(u,v),host_exact(u,v)
        trace.update(struct.pack('<IIIII',u,v,a,b,c));n+=1
        if a!=b or b!=c:counterexamples.append({'u':hex(u),'v':hex(v),'new':hex(a),'generic':hex(b),'host':hex(c)})
    for eu in range(1,255):
        for ev in range(1,255):
            s=eu+ev
            category='zero' if s<103 else 'subnormal_lattice' if s<128 else 'normal_original' if s<=380 else 'overflow_boundary' if s==381 else 'overflow'
            counts[category]+=1
            for i,(fu,fv) in enumerate(fractions):
                check((eu<<23)|fu|((i&1)<<31),(ev<<23)|fv|(((i>>1)&1)<<31))
    rng=random.Random(240000103381)
    for _ in range(100000):
        u=(rng.randrange(1,255)<<23)|rng.getrandbits(23)|(rng.getrandbits(1)<<31)
        v=(rng.randrange(1,255)<<23)|rng.getrandbits(23)|(rng.getrandbits(1)<<31)
        check(u,v)
    directed=[]
    for u,v in ((0x00800000,0x00800000),(0x00800000,0x32800000),(0x1f800000,0x1f800000),
            (0x1fffffff,0x1fffffff),(0x3fffffff,0x007fffff|0x3f800000),
            (0x5f000000,0x5f800000),(0x5f7fffff,0x5fffffff),(0x5fffffff,0x5fffffff)):
        check(u,v);directed.append({'u':hex(u),'v':hex(v),'sum':(u>>23&255)+(v>>23&255),'out':hex(normal_all(u,v))})
    record={'status':'FINITE_MODEL_PASS' if not counterexamples else 'COUNTEREXAMPLES',
        'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'cases':n,'exponent_pairs':dict(counts),'counterexamples':counterexamples[:20],
        'trace_sha256':trace.hexdigest(),'directed':directed,'seconds':time.monotonic()-started,
        'old_domain':'Only normal pairs E1..254,S128..380;48259 exponent pairs',
        'new_domain':'All normal pairs E1..254,S2..508;64516 exponent pairs; zero/subnormal/nonfinite inputs still fallback',
        'newly_covered_exponent_pairs':64516-48259,
        'Lean_proof':'NOT_RUN_AND_NOT_WRITTEN','native_cost':'UNKNOWN','full_gate':'NOT_RUN',
        'scope':'Finite source-level arithmetic discrimination only, no acceptance/performance/new-track claim. Host product is exactly representable in binary64; final binary32 conversion is an additional finite oracle.'}
    (HERE/'normal-all-model.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:record[k] for k in ('status','cases','exponent_pairs','newly_covered_exponent_pairs','seconds','trace_sha256')}))
if __name__=='__main__':main()
