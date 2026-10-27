"""Exact word-boundary preflight with independent IEEE-neighbor search; not Lean."""
from pathlib import Path
from hashlib import sha256
import json
import random
import time

HERE = Path(__file__).resolve().parent
MASK = (1 << 32) - 1
BASE = 1 << 23

def guard(eu, ev):
    return ((eu-1)&MASK) <= 253 and ((ev-1)&MASK) <= 253 and (((eu+ev)-128)&MASK) <= 252

def direct(u, v, use_pre_round_high=False):
    eu, ev = (u>>23)&255, (v>>23)&255
    if not guard(eu,ev):
        return None
    p = (BASE | (u&(BASE-1))) * (BASE | (v&(BASE-1)))
    t = 23 if p < 1<<47 else 24
    biased = p + (1<<(t-1))-1 + ((p>>t)&1)
    high = (p if use_pre_round_high else biased)>>47
    q = (biased>>(23+high)) & MASK
    e = (eu+ev-127+high)&MASK
    return ((u^v)&0x80000000) | (e<<23) | ((q-BASE)&MASK)

def ieee_units298(bits):
    e, f = bits>>23, bits&(BASE-1)
    units149 = f if e == 0 else (BASE|f)<<(e-1)
    return units149<<149

def independent_product(u,v):
    eu,ev=(u>>23)&255,(v>>23)&255
    n=(BASE|(u&(BASE-1)))*(BASE|(v&(BASE-1)))
    n <<= eu+ev-2
    sign=(u^v)&0x80000000
    maxword=0x7f7fffff
    if n >= ieee_units298(maxword)+(1<<401):
        return sign|0x7f800000
    if n >= ieee_units298(maxword):
        return sign|maxword
    lo,hi=0,maxword
    while lo+1<hi:
        mid=(lo+hi)//2
        if ieee_units298(mid)<=n:lo=mid
        else:hi=mid
    twice=ieee_units298(lo)+ieee_units298(hi)
    upper=2*n>twice or (2*n==twice and lo&1)
    return sign|(hi if upper else lo)

def main():
    started=time.monotonic();accepted=0
    for eu in range(256):
        for ev in range(256):
            g=guard(eu,ev)
            assert g == (1<=eu<=254 and 1<=ev<=254 and 128<=eu+ev<=380)
            accepted+=g
    cases=[]
    mantissas=[BASE,BASE+1,BASE+2,3*BASE//2-1,3*BASE//2,2*BASE-3,2*BASE-2,2*BASE-1]
    for eu,ev in [(1,127),(64,64),(127,127),(126,254),(254,126),(254,1),(1,254)]:
        for a in mantissas:
            for b in mantissas:
                for signs in range(4):
                    cases.append((((signs&1)<<31)|(eu<<23)|(a-BASE),
                                  (((signs>>1)&1)<<31)|(ev<<23)|(b-BASE)))
    rng=random.Random(19272400)
    while len(cases)<4096:
        eu,ev=rng.randrange(1,255),rng.randrange(1,255)
        if not guard(eu,ev):continue
        cases.append(((rng.randrange(2)<<31)|(eu<<23)|rng.randrange(BASE),
                      (rng.randrange(2)<<31)|(ev<<23)|rng.randrange(BASE)))
    for u,v in cases:
        actual,expected=direct(u,v),independent_product(u,v)
        assert actual==expected,(hex(u),hex(v),hex(actual),hex(expected))
    special_words=[0,0x80000000,1,0x007fffff,0x7f800000,0xff800000,0x7f800001,0x7fc00001]
    assert all(direct(x,0x3f800000)is None and direct(0x3f800000,x)is None for x in special_words)
    u,v=(64<<23)|1,(64<<23)|(BASE-2)
    good,bad,expected=direct(u,v),direct(u,v,True),independent_product(u,v)
    assert good==expected and bad!=expected
    out={'state':'EXHAUSTIVE_EXPONENT_GUARD_AND_BOUNDED_WORD_MODEL_ONLY',
         'exponent_pairs':65536,'guard_accepted':accepted,'eligible_model_products':len(cases),
         'differences':0,'special_fallback_word_pairs':2*len(special_words),
         'legitimate_postcarry_negative_control':{'u':hex(u),'v':hex(v),'exact_product':(BASE+1)*(2*BASE-2),
               'product_identity':'2^47-2','correct':hex(good),'wrong_pre_round_high':hex(bad),'oracle':hex(expected)},
         'oracle':'Binary search IEEE positive word neighbors using exact product units2^-298; no reuse of bias or quotient-round code',
         'elapsed_seconds':time.monotonic()-started,'source_sha256':sha256(Path(__file__).read_bytes()).hexdigest(),
         'scope':'Guard truth table covers all extracted exponent pairs. Product correctness is only4096 cases; no Lean/native primitive, performance or adoption claim. No new acceptance gate.'}
    (HERE/'astra-direct-bias-boundary-check.json').write_text(json.dumps(out,indent=2)+'\n')
    print(json.dumps(out,indent=2))

if __name__=='__main__':main()
