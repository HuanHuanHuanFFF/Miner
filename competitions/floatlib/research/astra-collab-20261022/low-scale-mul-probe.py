"""Finite diagnosis of a uniform-subnormal-lattice multiply route, not a proof or timing."""
from pathlib import Path
import datetime,hashlib,json,random,runpy,struct

HERE=Path(__file__).resolve().parent
oracle_path=HERE/'web/R2-W02/original-extracted/FloatLib_R2-W02/diagnostics/diagnose_layout.py'
oracle=runpy.run_path(str(oracle_path),run_name='audited_oracle')
def rne(p,k):
    q,r=divmod(p,1<<k)
    half=1<<(k-1)
    return q+int(r>half or (r==half and q&1))
def low_round(sign,p,scale):
    assert 0<=p<1<<48 and 0<=scale<=123
    fraction=rne(p,149-scale)
    assert fraction<=1<<22
    return (sign<<31)|fraction
def fields(w):
    e=(w>>23)&255
    f=w&0x7fffff
    return ((f if e==0 else f|0x800000),max(e,1)-1)
def word(x):return struct.unpack('<I',struct.pack('<f',x))[0]
def value(w):return struct.unpack('<f',struct.pack('<I',w))[0]

trace=hashlib.sha256();count=0
products={0,1,2,3,(1<<48)-1,(1<<48)-2,1<<46,1<<47}
for k in range(1,49):
    for d in (-1,0,1):
        p=(1<<k)+d
        if 0<=p<1<<48:products.add(p)
for scale in range(124):
    for p in sorted(products):
        for sign in (0,1):
            got=low_round(sign,p,scale)
            expected=oracle['round_dyadic'](-p if sign else p,scale-298,bool(sign))
            assert got==expected,(sign,p,scale,got,expected)
            trace.update(struct.pack('<QBBI',p,scale,sign,got));count+=1
rng=random.Random(2026102205);scalar_count=0
for _ in range(65536):
    ea=rng.randrange(125)
    eb=rng.randrange(125)
    a=(rng.randrange(2)<<31)|(ea<<23)|rng.getrandbits(23)
    b=(rng.randrange(2)<<31)|(eb<<23)|rng.getrandbits(23)
    ma,sa=fields(a);mb,sb=fields(b)
    if sa+sb>123:continue
    got=low_round((a^b)>>31,ma*mb,sa+sb)
    expected=oracle['mul'](a,b)
    host=word(value(a)*value(b))
    assert got==expected==host,(a,b,got,expected,host)
    trace.update(struct.pack('<III',a,b,got));scalar_count+=1
for a,b in [(0,0),(0x80000000,0),(0,0x80000000),(0x80000000,0x80000000),(1,0x80000001)]:
    ma,sa=fields(a);mb,sb=fields(b);got=low_round((a^b)>>31,ma*mb,sa+sb)
    assert got==oracle['mul'](a,b)==word(value(a)*value(b));trace.update(struct.pack('<III',a,b,got));scalar_count+=1
result={'status':'PASS_FINITE_DIAGNOSTIC','rounder_cases':count,'finite_scalar_cases':scalar_count,'trace_sha256':trace.hexdigest(),'seed':2026102205,'premises':'product<2^48; scale<=123; represented exact dyadic value=(-1)^sign product*2^(scale-298)','conclusion_tested':'raw result=sign-bit OR RN-even(product/2^(149-scale)); fraction<=2^22','scope':'Full IEEE finite dyadic oracle and host exact-double product crosscheck; no Lean or performance claim','oracle_source_sha256':hashlib.sha256(oracle_path.read_bytes()).hexdigest(),'probe_source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'completed_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat()}
(HERE/'low-scale-mul-probe.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf8');print(json.dumps(result,indent=2))
