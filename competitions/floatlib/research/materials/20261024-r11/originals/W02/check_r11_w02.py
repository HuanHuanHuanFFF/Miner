#!/usr/bin/env python3
"""Finite raw-word category checks; NOT a FloatLib executor."""
from itertools import product
POS_ZERO=0x00000000; NEG_ZERO=0x80000000; POS_INF=0x7f800000; CANON_QNAN=0x7fc00000; QBIT=0x00400000

def exp(u): return (u >> 23) & 255
def frac(u): return u & 0x7fffff
def isnan(u): return exp(u)==255 and frac(u)!=0
def isinf(u): return exp(u)==255 and frac(u)==0
def quiet(u): return u | QBIT

def summary(xs):
    for k,x in enumerate(xs):
        if isnan(x): return ('qnan',k,quiet(x))
        if isinf(x): return ('qnan',k,CANON_QNAN)
    return ('zero',None,POS_ZERO)

def main():
    alphabet=[POS_ZERO,NEG_ZERO,0x3f800000,0x7fc00001,0x7f800001,POS_INF]
    count=0
    for n in range(5):
        for xs in product(alphabet, repeat=n):
            got=summary(xs); t=next((i for i,x in enumerate(xs) if exp(x)==255),None)
            want=('zero',None,POS_ZERO) if t is None else (('qnan',t,quiet(xs[t])) if isnan(xs[t]) else ('qnan',t,CANON_QNAN))
            assert got==want,(xs,got,want); count+=1
    snan=0x7f800001
    assert summary([POS_INF]) == ('qnan',0,CANON_QNAN)
    assert summary([snan,POS_INF])[2] == 0x7fc00001
    assert summary([POS_INF,snan])[2] == CANON_QNAN
    print('FINITE_CATEGORY_CHECKS_PASS',count)
    print('infinity * signed zero => canonical qNaN:',hex(summary([POS_INF])[2]))
    print('sNaN then infinity:',hex(summary([snan,POS_INF])[2]))
    print('infinity then sNaN:',hex(summary([POS_INF,snan])[2]))
    print('scope: bounded category model only; not Lean, not FloatLib execution, not a full-word proof')
if __name__=='__main__': main()
