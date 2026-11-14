"""New normal-word transport model versus exact rational nearest-neighbor search.

No Lean/native toolchain or floating-point arithmetic is run. This is finite
boundary evidence, not all-input proof or performance validation.
"""
from pathlib import Path
from fractions import Fraction
from functools import lru_cache
from datetime import datetime,timezone
import hashlib,json,time
D=Path(__file__).resolve().parent
MASK=(1<<64)-1

def check(n,d,q):
    return n<1<<49 and 0<d<1<<25 and q<1<<25 and q*d<=n and n-q*d<d

def word(sign,n,d,q,e):
    r=(n-q*d)&MASK;c=(d-r)&MASK
    m=q if r<c else (q+1)&MASK if c<r else q if q%2==0 else (q+1)&MASK
    out=((e+1)<<23) if m==1<<24 else (e<<23)|max(0,m-(1<<23))
    return (sign<<31)|out

@lru_cache(maxsize=4096)
def magnitude(w):
    e=w>>23;f=w&0x7fffff
    m=f if e==0 else f+(1<<23)
    k=-149 if e==0 else e-150
    return Fraction(m<<k) if k>=0 else Fraction(m,1<<(-k))

def oracle(sign,value):
    assert value>0 and value<magnitude(0x7f7fffff)
    lo,hi=0,0x7f7fffff
    while lo<=hi:
        mid=(lo+hi)//2
        if magnitude(mid)<=value:lo=mid+1
        else:hi=mid-1
    a,b=hi,hi+1
    da,db=value-magnitude(a),magnitude(b)-value
    out=a if da<db else b if db<da else a if a%2==0 else b
    return (sign<<31)|out

def main():
    start=time.monotonic();count=ties=carry=reject=0;trace=hashlib.sha256()
    for den in [1,2,3,7,(1<<24)-1,1<<24,(1<<25)-1]:
        for q in [1<<23,(1<<23)+1,(1<<23)+2,(1<<24)-2,(1<<24)-1]:
            for rem in sorted({0,min(1,den-1),den//2,max(0,den//2-1),min(den-1,den//2+1),den-1}):
                n=q*den+rem
                assert check(n,den,q) and (1<<23)*den<=n<(1<<24)*den
                for bad in [max(0,q-1),q+1,(1<<25),MASK]:
                    assert not check(n,den,bad);reject+=1
                for e in [1,2,126,127,150,252,253]:
                    value=Fraction(n,den)*(Fraction(1<<(e-150)) if e>=150 else Fraction(1,1<<(150-e)))
                    for sign in [0,1]:
                        got=word(sign,n,den,q,e);want=oracle(sign,value)
                        assert got==want,(sign,n,den,q,e,hex(got),hex(want))
                        count+=1;ties+=2*rem==den;carry+=(got&0x7fffffff)>>23==e+1
                        trace.update(got.to_bytes(4,'little'))
    witness={'n':0,'d':1,'q':0,'e':127,'quotient_check':check(0,1,0),'normalization_guard':False,'unguarded_packed_word':hex(word(0,0,1,0,127)),'correct_word':'0x0'}
    assert witness['quotient_check'] and witness['unguarded_packed_word']=='0x3f800000'
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'FINITE_EXACT_RATIONAL_MODEL_PASS_NOT_LEAN','cases':count,'ties':ties,'carry_cases':carry,'wrong_quotient_rejections':reject,'differences':0,'trace_sha256':trace.hexdigest(),'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'fragment_sha256':hashlib.sha256((D/'NormalWord.lean.inc').read_bytes()).hexdigest(),'missing_normalization_guard_witness':witness,'elapsed_seconds':time.monotonic()-start,'scope':'New word packing compared with full positive binary32 exact-Fraction neighbor search, both signs and normal-boundary exponents. Not generated Lean, native timing or a complete RMS implementation.'}
    (D/'model-result.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8');print(json.dumps(out))
if __name__=='__main__':main()
