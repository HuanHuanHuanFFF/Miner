"""Bounded independent binary32 packing check; no Lean, compile or timing claim."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,random,struct,sys,time
OUT=Path(__file__).resolve().parent;M=1<<23;MASK=M-1;MOD=(1<<32)-1
assert sys.float_info.radix==2 and sys.float_info.mant_dig==53 and sys.float_info.max_exp>=1024
def bits(v):
    try:return struct.unpack('<I',struct.pack('<f',v))[0]
    except OverflowError:return 0xff800000 if v<0 else 0x7f800000
def value(w):return struct.unpack('<f',struct.pack('<I',w))[0]
assert bits(1+2**-24)==0x3f800000 and bits(1+3*2**-24)==0x3f800002
def test(ex,ey,mx,my,sx,sy):
    a=(sx<<31)|(ex<<23)|(mx-M);b=(sy<<31)|(ey<<23)|(my-M)
    # Every binary32 finite operand is exact in binary64 and its24x24 product
    # has at most48 significant bits, so the reference has one final32bit rounding.
    expected=bits(value(a)*value(b))
    first=bits(float(mx)*float(my))
    got=((first+(((ex+ey-300)&MOD)<<23))&MOD)|((a^b)&0x80000000)
    return a,b,first,got,expected
start=time.perf_counter();trace=hashlib.sha256();count=0
mant=[M,M+1,M+2,M+3,3*(1<<22),3*(1<<22)+2,3*(1<<22)+6,2*M-2,2*M-1]
def checked(*args):
    global count
    row=test(*args);assert row[-1]==row[-2],tuple(hex(v) for v in row)
    assert 1<=((row[-1]>>23)&255)<=254
    assert ((row[2]>>23)&255) in (173,174)
    for v in row:trace.update(v.to_bytes(4,'little'))
    count+=1
    if count%1024==0:assert time.perf_counter()-start<5,'Local check exceeded5second cap'
for s in [128,129,173,174,254,299,300,301,379,380]:
    for ex in sorted({max(1,s-254),min(254,s-1),s//2}):
        for mx in mant:
            for my in mant:
                for sx in range(2):
                    for sy in range(2):checked(ex,s-ex,mx,my,sx,sy)
r=random.Random(202610242100)
for _ in range(30000):
    s=r.randint(128,380);ex=r.randint(max(1,s-254),min(254,s-1));checked(ex,s-ex,r.randrange(M,2*M),r.randrange(M,2*M),r.randrange(2),r.randrange(2))
outside=[test(63,64,M,M,0,0),test(190,191,2*M-1,2*M-1,0,0)]
assert all(row[-1]!=row[-2] for row in outside)
result={'state':'INDEPENDENT_HOST_BINARY32_PACK_SELECTED_CHECK_PASS','at_utc':datetime.now(timezone.utc).isoformat(),'cases':count,'wall_seconds':time.perf_counter()-start,'trace_sha256':trace.hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'python':sys.version.split()[0],
        'domain':'Both inputsnormal exponents1..254 and sum128..380, signs arbitrary. First rounded mantissa product has exponent173or174.',
        'reference':'Host Python binary64 exact48bit finite product followed by standard binary32 pack; independent of the source-derived integer oracle used by previous finite probes.',
        'outside_guard_counterexamples':[[hex(v) for v in row] for row in outside],
        'scope':'Selected independent host format/arithmetic check only. Not all-input Lean proof, fixed-runner execution, actual Lean ABI lowering, or performance. No local Lean or heavy compiler was run.'}
(OUT/'development-host-exponent-shift-check.json').write_bytes((json.dumps(result,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps(result))
