"""Literal source36 producer and terminal-word refinement, finite evidence only.

Compares the exact UInt64 h/l passed to unchanged YL/YD, not only a rounded
numeric result. This keeps exact-zero, underflow and signed-zero callbacks in
the statement rather than assuming a Python rounding model proves them.
"""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import random
import sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
spec=importlib.util.spec_from_file_location('centered_model',HERE/'centered_dot_model.py')
c=importlib.util.module_from_spec(spec);spec.loader.exec_module(c)
m=c.m;mask=(1<<64)-1;offset=1<<62


def original_prep(words):
    minimum,maximum,expmax=c.model.metadata(words)
    out=[]
    for word in words:
        sign,mant,index=m.fields(word)
        value=(mant<<((index-minimum)&63))&mask
        out.append(((offset-value) if sign<0 else (offset+value))&mask)
    return out,(minimum,maximum,expmax)


def actual_center(words):
    old,(minimum,maximum,expmax)=original_prep(words)
    bits=0 if maximum<minimum else 24+maximum-minimum
    if bits>39 or expmax==255:return None
    q=1<<bits
    values=[(word-offset+q)&mask for word in old]
    expected=[c.model.prepared_value(word,minimum)+q for word in words]
    assert values==expected
    assert all(0<=value<2*q for value in values)
    total=0
    for value in values:total=(total+value)&mask
    assert total==sum(values)<1<<60
    return values,total,bits,old,(minimum,maximum,expmax)


def old_loop(a,b,d):
    h=l=0
    for x,y in zip(a,b):
        product=((((x-offset)&mask)*((y-offset)&mask))<<d)&mask
        low=(l+product)&mask
        h=(h-(product>>63)+(low<l))&mask
        l=low
    return h,l


def new_loop(a,b):
    h=l=0
    for x,y in zip(a,b):
        product=x*y
        assert product<1<<63
        low=(l+product)&mask
        h=(h+(low<l))&mask
        l=low
    return h,l


def terminal(h,l,n,xb,wb,xs,ws,d):
    # Same sequential subtraction/addition and special-zero shifts as fragment.
    aL=(xs<<wb)&mask;aH=0 if wb==0 else xs>>(64-wb)
    la=(l-aL)&mask;ha=(h-aH-(l<aL))&mask
    bL=(ws<<xb)&mask;bH=0 if xb==0 else ws>>(64-xb)
    lb=(la-bL)&mask;hb=(ha-bH-(la<bL))&mask
    bits=xb+wb;cL=(n<<bits)&mask;cH=0 if bits==0 else n>>(64-bits)
    lc=(lb+cL)&mask;hc=(hb+cH+(lc<lb))&mask
    ld=(lc<<d)&mask;hd=hc if d==0 else ((hc<<d)|(lc>>(64-d)))&mask
    return hd,ld


def word(sign,exp,frac):return (sign<<31)|(exp<<23)|frac


def main():
    rng=random.Random(28010336)
    accepted=0;rejected=0;zero=0;nonzero_d=0;products=0;domain=set()
    samples=[]
    # Zero, subnormal, exact powers, ordinary finite, extremes, and mixed signs.
    for index in range(12000):
        n=rng.choice([1,2,3,7,16,31,64])
        ea=rng.choice([0,1,2,32,90,120,126,180,247,253])
        eb=rng.choice([0,1,3,64,110,121,127,200,248,253])
        span_a=rng.randrange(10);span_b=rng.randrange(10)
        if index%17==0:
            a=[rng.randrange(2)<<31 for _ in range(n)]
        else:
            a=[word(rng.randrange(2),min(254,ea+rng.randrange(span_a+1)),rng.choice([0,1,0x7fffff,rng.randrange(1<<23)])) for _ in range(n)]
        if index%23==0:
            b=[rng.randrange(2)<<31 for _ in range(n)]
        else:
            b=[word(rng.randrange(2),min(254,eb+rng.randrange(span_b+1)),rng.choice([0,1,0x7fffff,rng.randrange(1<<23)])) for _ in range(n)]
        bias=0 if index%3 else word(rng.randrange(2),rng.randrange(1,255),rng.randrange(1<<23))
        pa=actual_center(a);pb=actual_center(b)
        if pa is None or pb is None:rejected+=1;continue
        av,sa,ba,oa,(ma,ha,exa)=pa;bv,sb,bb,ob,(mb,hb,exb)=pb
        _,bm,bi=m.fields(bias)
        lo=min(ma+mb,126+bi) if bm else ma+mb
        hi=max(ha+hb,126+bi) if bm else ha+hb
        d=ma+mb-lo
        if hi<lo or hi-lo>15 or ba+bb>61 or d>=64:
            rejected+=1;continue
        old=old_loop(oa,ob,d)
        new=terminal(*new_loop(av,bv),n,ba,bb,sa,sb,d)
        assert new==old,(a,b,bias,d,new,old)
        # This exact pair, lo, bias and exponent is the old YL/YD call tuple.
        assert ((0-(new[0]>>63))&mask)==((0-(old[0]>>63))&mask)
        accepted+=1;products+=n;nonzero_d+=d!=0;zero+=new==(0,0)
        if ea==0 or eb==0:domain.add('subnormal-capable')
        if any((x&0x7fffffff)==0 for x in a+b):domain.add('signed-zero-input')
        if any((x&0x7fffff)==0 and x&0x7f800000 for x in a+b):domain.add('exact-power')
        if max(ea,eb)>=247:domain.add('large-exponent')
        if len(samples)<16:samples.append({'n':n,'d':d,'offset_bits':[ba,bb],'terminal_pair':list(new),'lo':lo,'bias':bias})
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'LITERAL_PRODUCER_AND_TERMINAL_WORD_FINITE_REFINEMENT_NOT_LEAN',
         'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),'fragment_sha256':hashlib.sha256((HERE/'CenteredDotRuntime.leanfrag').read_bytes()).hexdigest(),
         'generated_cases':12000,'accepted':accepted,'original_or_new_guard_rejected':rejected,'products_checked':products,
         'body_exact_zero_cases':zero,'nonzero_body_shift_cases':nonzero_d,'covered_categories':sorted(domain),'examples':samples,
         'conclusion':'On every accepted fixture, the original and centered loops pass identical high/low/sign words, bias, lo and final exponent to the unchanged YL/YD terminal. Numeric rounding, exactzero and signedzero behavior therefore need not be re-modelled for these fixtures.',
         'limits':['Finite producer/word equality only; not allinput proof or actual Lean runtime','NaN/infinity/invalid dimensions still follow unchanged outer fallback but are not exercised by this accepted-domain loop fixture','No timing conclusion']}
    (HERE/'literal-centered-replay.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({k:out[k]for k in ['generated_cases','accepted','original_or_new_guard_rejected','products_checked','body_exact_zero_cases','nonzero_body_shift_cases','covered_categories']}))


if __name__=='__main__':main()
