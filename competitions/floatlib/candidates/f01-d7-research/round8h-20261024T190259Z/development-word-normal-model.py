"""One bounded finite model of a specialized normal-output word multiplier."""
from pathlib import Path
from datetime import datetime,timezone
import ast,hashlib,json,random,time
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4]
oracle=ROOT/'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py';raw=oracle.read_bytes();assert hashlib.sha256(raw).hexdigest()=='3dfaeec2bde1364a4f06abd292f0ba265376da79e678d38219ad72'.replace('bde1364a4f06abd292f0ba265376da79e678d38219ad72','bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72')
needed={'exp','frac','nan','snan','inf','zero','choose','unpack','rounded','mul'}
tree=ast.parse(raw);env={};exec(compile(ast.Module(body=[x for x in tree.body if isinstance(x,ast.FunctionDef) and x.name in needed],type_ignores=[]),str(oracle),'exec'),env)
M=1<<23;MASK=M-1;SIGN=1<<31
def fast(a,b):
    ex=(a>>23)&255;ey=(b>>23)&255;s=ex+ey
    if not (1<=ex<=254 and 1<=ey<=254 and 128<=s<=379):return None
    p=((a&MASK)|M)*((b&MASK)|M)
    high=p>>47;shift=23+high;half=(1<<22)<<high
    q=(p+half-1+((p>>shift)&1))>>shift
    carry=q>>24;e=s-127+high+carry
    assert 1<=e<=254 and high in (0,1) and carry in (0,1)
    return ((a^b)&SIGN)|(e<<23)|(q&MASK)
start=time.perf_counter();trace=hashlib.sha256();count=even=odd=carry=0
def test(ex,ey,mx,my,sx,sy):
    global count,even,odd,carry
    a=(sx<<31)|(ex<<23)|(mx-M);b=(sy<<31)|(ey<<23)|(my-M)
    got=fast(a,b);want=env['mul'](a,b);assert got==want,(hex(a),hex(b),hex(got),hex(want))
    p=mx*my;shift=23+(p>>47);q,r=divmod(p,1<<shift);half=1<<(shift-1)
    even+=r==half and q%2==0;odd+=r==half and q%2==1;carry+=(p+half-1+(q&1))>>shift==1<<24
    for v in (a,b,got):trace.update(v.to_bytes(4,'little'))
    count+=1
    if count%1024==0:assert time.perf_counter()-start<5,'Bounded local model exceeded5seconds'
mant=[M,M+1,M+2,M+3,M+16,3*(1<<22),3*(1<<22)+2,3*(1<<22)+6,2*M-2,2*M-1]
for s in [128,129,173,174,175,254,300,378,379]:
    for ex in sorted({max(1,s-254),min(254,s-1),s//2}):
        for mx in mant:
            for my in mant:
                for sx in range(2):
                    for sy in range(2):test(ex,s-ex,mx,my,sx,sy)
r=random.Random(202610242020)
for _ in range(20000):
    s=r.randint(128,379);ex=r.randint(max(1,s-254),min(254,s-1));test(ex,s-ex,r.randrange(M,2*M),r.randrange(M,2*M),r.randrange(2),r.randrange(2))
assert min(even,odd,carry)>0 and oracle.read_bytes()==raw
record={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'FINITE_WORD_MODEL_ONLY','cases':count,'ties_even':even,'ties_odd':odd,'carry_cases':carry,'wall_seconds':time.perf_counter()-start,'trace_sha256':trace.hexdigest(),'oracle_sha256':hashlib.sha256(raw).hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'domain':'Both normal inputs exponent1..254, raw exponent sum128..379; signs arbitrary. Other inputs require unchanged fallback.',
        'mechanism':'P=24x24 product; high=P>>47; shift=23+high; q=(P+half-1+((P>>shift)&1))>>shift; carry=q>>24; exponent=sum-127+high+carry; fraction=q&0x7fffff. No generic zero/subnormal/overflow/log2 branches or native casts on this domain.',
        'old_route_difference':'R6 normal-mul only shortens log2 and retains the generic rounder branches/product range check; that old negative result is not reused as a positive prediction.',
        'limitation':'Source-derived exact integer oracle, not independent hardware, Lean, all-input proof or performance. Need no-wrap+bias-RNE identity, guard normal-output proof, actual UInt32 packing/spec composition, and full original gates/timing.'}
(OUT/'development-word-normal-model.json').write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps(record))
