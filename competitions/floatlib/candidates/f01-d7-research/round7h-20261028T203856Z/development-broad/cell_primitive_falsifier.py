"""Small exact arithmetic falsifier for the proposed real-rounder interfaces."""
from pathlib import Path
from fractions import Fraction
import hashlib
import importlib.util
import json
import random

HERE=Path(__file__).resolve().parent
s=importlib.util.spec_from_file_location('r24_cell_math',HERE/'certificates.py');c=importlib.util.module_from_spec(s);s.loader.exec_module(c)

def rq(p,d):
    q,r=divmod(p,d)
    return q+(2*r>d or (2*r==d and bool(q&1)))

def main():
    rng=random.Random(24293017);normal=0;strict=0;ties=0
    for _ in range(2000):
        d=rng.randrange(1,1<<20);m=rng.randrange(8388609,16777216);e=rng.randrange(-149,105)
        p=m*d+rng.randrange(-(d//2),d//2+1)
        if d*(2*m-1)<2*p<d*(2*m+1):
            assert rq(p,d)==m;strict+=1
            for sign in (False,True):
                q=Fraction(p,d)*c.pow2(e)*(-1 if sign else 1)
                expected=(int(sign)<<31)|((e+150)<<23)|(m-8388608)
                assert c.rn_rational(q)==expected;normal+=1
    for m in range(2,100,2):
        for lower in (True,False):
            d=2;p=(2*m-1) if lower else (2*m+1)
            assert d*(2*m-1)<=2*p<=d*(2*m+1) and rq(p,d)==m;ties+=1
    # Dropping parity from a closed midpoint certificate is false.
    assert rq(3,2)!=1
    report={'scope':'Finite exact arithmetic only. Lean source typing, replay and axioms NOT_RUN.',
        'strict_cases':strict,'normal_word_signed_cases':normal,'even_midpoint_cases':ties,
        'odd_tie_mutant_caught':True,'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'lean_fragment_sha256':hashlib.sha256((HERE/'CellPrimitive.lean.inc').read_bytes()).hexdigest()}
    (HERE/'cell-primitive-model.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(report,indent=2))

if __name__=='__main__':main()
