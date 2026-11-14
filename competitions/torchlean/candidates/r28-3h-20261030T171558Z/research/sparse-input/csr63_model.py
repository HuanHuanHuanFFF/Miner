"""Owned 63-bit biased factor+index model; finite checks, no native timing."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random

C=1<<55
Z=1<<57
MASK=(1<<64)-1
LOW=(1<<56)-1

def encode(i,m):
    assert 0<=i<128 and -C<m<C
    p=(i<<56)+(C+m)
    assert 0<p<(1<<63)
    return p

def decode(p):
    return p>>56,(p&LOW)+3*C

def step(acc,x,w,u):
    l=x&((1<<25)-1);h=((x>>25)-(1<<32))&MASK
    return ((acc[0]+l*((w-(1<<31))&MASK))&MASK,
            (acc[1]+h*((w-(1<<31))&MASK))&MASK,
            (acc[2]+l*((u-(1<<31))&MASK))&MASK,
            (acc[3]+h*((u-(1<<31))&MASK))&MASK)

def main():
    start=datetime.now(timezone.utc).isoformat();rng=random.Random(0x28363)
    checks=0;folds=0
    for i in [0,1,63,64,126,127]:
      for m in [-C+1,-(1<<54),-1,0,1,(1<<54),C-1]:
        p=encode(i,m);assert decode(p)==(i,Z+m);checks+=1
    for _ in range(100000):
        i=rng.randrange(128);m=rng.randrange(-C+1,C)
        assert decode(encode(i,m))==(i,Z+m);checks+=1
    # Actual F32 mantissa+31-bit exponent-span bound, both signs.
    for e in range(32):
      for m in [1,(1<<23)-1,1<<23,(1<<24)-1]:
       for sign in [-1,1]:
        q=sign*(m<<e);assert -C<q<C
        assert decode(encode(127,q))==(127,Z+q);checks+=1
    for k in [1,2,3,4,8,9,16,31,64,127,128]:
      for _ in range(100):
        mm=[0 if rng.randrange(2) else rng.randrange(-C+1,C) for _ in range(k)]
        w=[rng.getrandbits(64) for _ in range(k)];u=[rng.getrandbits(64) for _ in range(k)]
        a=tuple(rng.getrandbits(64) for _ in range(4));dense=a;compact=a
        for m,ww,uu in zip(mm,w,u):dense=step(dense,Z+m,ww,uu)
        support=[encode(i,m) for i,m in enumerate(mm) if m]
        assert [decode(p)[0] for p in support]==[i for i,m in enumerate(mm) if m]
        for p in support:
            i,x=decode(p);compact=step(compact,x,w[i],u[i])
        assert dense==compact;folds+=1
    # Failure controls: index128 does not fit smallNat63; shift32 can exceed55 magnitude bits.
    assert (128<<56)+(C+1)>=(1<<63)
    assert ((1<<24)-1)<<32>=C
    body={'state':'FINITE_MODEL_ONLY_NOT_LEAN_NATIVE_OR_KERNEL','start_utc':start,
        'end_utc':datetime.now(timezone.utc).isoformat(),'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'pack_decode_checks':checks,'arbitrary_UInt64_four_accumulator_fold_checks':folds,
        'failure_controls':['index128 violates smallNat63','input span32 violates chosen magnitude guard'],
        'word_semantics':'UInt64 mod2^64, shifts25/56<64, encodedzero=2^57',
        'all12':'NOT_IMPLEMENTED','Lean':'NOT_COMPILED','native':'NOT_RUN'}
    Path(__file__).with_name('csr63-result.json').write_text(json.dumps(body,indent=2)+'\n')
    print(json.dumps(body))

if __name__=='__main__':main()
