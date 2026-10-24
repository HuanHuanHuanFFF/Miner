"""Source-derived binary32 word oracle; finite testing, never Lean/host evidence."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,random
HERE=Path(__file__).resolve().parent
def exp(w):return (w>>23)&255
def frac(w):return w&0x7fffff
def nan(w):return exp(w)==255 and frac(w)!=0
def snan(w):return nan(w) and (w&0x400000)==0
def inf(w):return (w&0x7fffffff)==0x7f800000
def zero(w):return (w&0x7fffffff)==0
def canon(w):return 0x7fc00000 if nan(w) else w
def choose(a,b):
    for test in [snan,nan]:
        for w in [a,b]:
            if test(w):return w|0x400000
    return None
def unpack(w):
    assert exp(w)!=255
    m=frac(w) if exp(w)==0 else frac(w)|(1<<23)
    return (-m if w>>31 else m),(-149 if exp(w)==0 else exp(w)-150)
def rounded(v,e,nz=False):
    sign=0x80000000 if v<0 or (v==0 and nz) else 0
    v=abs(v)
    if not v:return sign
    out_e=max(-149,e+v.bit_length()-24);shift=out_e-e
    if shift<=0:q=v<<(-shift)
    else:
        q,r=divmod(v,1<<shift);half=1<<(shift-1)
        q+=int(r>half or (r==half and q&1))
    if not q:return sign
    if q>=1<<24:q>>=1;out_e+=1
    if q<1<<23:
        assert out_e==-149
        return sign|q
    E=out_e+150
    if E>=255:return sign|0x7f800000
    assert 1<=E<255
    return sign|(E<<23)|(q-(1<<23))
def add(a,b):
    n=choose(a,b)
    if n is not None:return n
    if inf(a):return 0x7fc00000 if inf(b) and (a^b)>>31 else a
    if inf(b):return b
    x,ex=unpack(a);y,ey=unpack(b);e=min(ex,ey)
    return rounded((x<<(ex-e))+(y<<(ey-e)),e,bool((a&b)>>31))
def mul(a,b):
    n=choose(a,b)
    if n is not None:return n
    sign=(a^b)&0x80000000
    if inf(a) or inf(b):return 0x7fc00000 if zero(a) or zero(b) else sign|0x7f800000
    x,ex=unpack(a);y,ey=unpack(b)
    return rounded(x*y,ex+ey,bool(sign))
def native_model(op,a,b):return canon(op(canon(a),canon(b)))
def summation(xs,op=add):
    a=0
    for x in xs:a=op(a,x)
    return a
def dot(xs,ys,ao=add,mo=mul):
    a=0
    for x,y in zip(xs,ys):a=ao(a,mo(x,y))
    return a
def main():
    r=random.Random(2026102301);trace=hashlib.sha256()
    edge=[0,0x80000000,1,0x80000001,0x007fffff,0x807fffff,0x00800000,0x80800000,0x3f800000,0xbf800000,0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc00000,0xffc00001,0x7f800001,0xff800002,0x7fffffff,0xffffffff]
    pairs=[(a,b) for a in edge for b in edge]+[(r.getrandbits(32),r.getrandbits(32)) for _ in range(50000)]
    nonnan_pairs=0;native_mismatches=[]
    for a,b in pairs:
        for name,op in [('add',add),('mul',mul)]:
            exact=op(a,b);native=native_model(op,a,b)
            assert not snan(exact)
            if not nan(a) and not nan(b):assert native==exact; nonnan_pairs+=1
            if not nan(native):assert native==exact
            if native!=exact and len(native_mismatches)<8:native_mismatches.append({'op':name,'a':hex(a),'b':hex(b),'exact':hex(exact),'canonical_native_model':hex(native)})
            trace.update(a.to_bytes(4,'little')+b.to_bytes(4,'little')+exact.to_bytes(4,'little'))
    counts={'sum':0,'dot':0,'infinity_endpoints':0,'nan_fallbacks':0}
    for n in [0,1,2,3,8,16,64]:
        for _ in range(500):
            xs=[r.choice(edge) if r.randrange(3)==0 else r.getrandbits(32) for _ in range(n)]
            ys=[r.choice(edge) if r.randrange(3)==0 else r.getrandbits(32) for _ in range(n)]
            values=[('sum',summation(xs),summation(xs,lambda a,b:native_model(add,a,b))),('dot',dot(xs,ys),dot(xs,ys,lambda a,b:native_model(add,a,b),lambda a,b:native_model(mul,a,b)))]
            for name,exact,native in values:
                guarded=exact if nan(native) else native
                assert guarded==exact
                counts[name]+=1;counts['infinity_endpoints']+=inf(native);counts['nan_fallbacks']+=nan(native)
                trace.update(exact.to_bytes(4,'little')+native.to_bytes(4,'little'))
    q,s,one=0x7fc00001,0xff800002,0x3f800000
    witnesses={'sum_later_signaling':hex(add(q,s)),'dot_product_quieted':hex(mul(s,one)),'dot_absorption':hex(add(q,mul(s,one))),'overflow_sum':hex(add(0x7f7fffff,0x7f7fffff)),'opposite_inf':hex(add(0x7f800000,0xff800000))}
    out={'status':'PASS_FINITE_SOURCE_DERIVED_WORD_MODEL','completed_at_utc':datetime.now(timezone.utc).isoformat(),'seed':2026102301,'pair_count':len(pairs),'nonnan_operation_cases':nonnan_pairs,'sequence_counts':counts,'witnesses':witnesses,'unconditional_canonical_native_counterexamples':native_mismatches,'trace_sha256':trace.hexdigest(),'scope':'Own exact integer/special-value transcription of fixed public Model.Spec. Native is modeled as canonicalized exact operations, not actual Lean Float32 runtime. No proof, kernel replay, hardware, or performance claim; match must still be established by actual Lean bridge.'}
    (HERE/'nonfinite-oracle.json').write_text(json.dumps(out,indent=2)+'\n');print(json.dumps(out,indent=2))
if __name__=='__main__':main()
