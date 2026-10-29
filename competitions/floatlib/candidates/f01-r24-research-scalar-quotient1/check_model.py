"""Bounded UInt64 model of this new checker; not a Lean proof or timing test."""
from pathlib import Path
import hashlib,json
from datetime import datetime,timezone

D=Path(__file__).resolve().parent
MASK=(1<<64)-1

def check(n,d,q):
    return n<1<<49 and 0<d<1<<25 and q<1<<25 and ((q*d)&MASK)<=n and ((n-((q*d)&MASK))&MASK)<d

def rounded(n,d,q):
    r=(n-((q*d)&MASK))&MASK;c=(d-r)&MASK
    return q if r<c else ((q+1)&MASK) if c<r else q if q%2==0 else (q+1)&MASK

def oracle(n,d):
    q,r=divmod(n,d)
    return q+int(2*r>d or (2*r==d and q%2==1))

def main():
    ns=[0,1,2,3,5,7,(1<<25)-1,(1<<48)-1,(1<<49)-2,(1<<49)-1,1<<49,MASK]
    ds=[0,1,2,3,7,(1<<24)-1,1<<24,(1<<25)-1,1<<25,MASK]
    cases=accepted=ties_even=ties_odd=0; trace=hashlib.sha256()
    for n in ns:
        for d in ds:
            q0=n//d if d else 0
            for q in sorted({0,1,max(0,q0-1),q0,min(MASK,q0+1),(1<<25)-1,1<<25,1<<40,MASK}):
                if q>MASK:continue
                valid=check(n,d,q);cases+=1
                if valid:
                    accepted+=1
                    assert q==n//d and ((n-q*d)&MASK)==n%d
                    assert rounded(n,d,q)==oracle(n,d)
                    ties_even+=2*(n%d)==d and q%2==0
                    ties_odd+=2*(n%d)==d and q%2==1
                trace.update(f'{n},{d},{q},{int(valid)},{rounded(n,d,q) if valid else -1}\n'.encode())
    assert check(5,2,2) and rounded(5,2,2)==2
    assert check(7,2,3) and rounded(7,2,3)==4
    n,d,q=0,1<<24,1<<40
    unchecked=((q*d)&MASK)<=n and ((n-((q*d)&MASK))&MASK)<d
    assert unchecked and not check(n,d,q) and q!=n//d
    source=(D/'Kernel.lean').read_bytes();fragment=(D/'Quotient.lean.inc').read_bytes()
    out={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'FINITE_MODEL_PASS_NOT_LEAN',
         'cases':cases,'accepted':accepted,'ties_even':ties_even,'ties_odd':ties_odd,'mismatches':0,
         'trace_sha256':trace.hexdigest(),'candidate_sha256':hashlib.sha256(source).hexdigest(),
         'fragment_sha256':hashlib.sha256(fragment).hexdigest(),
         'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
         'unguarded_product_wrap_witness':{'n':n,'d':d,'q':q,'wrapped_product':0,'unguarded_accepts':True,'actual_checker_accepts':False},
         'scope':'Fixed boundary corpus only, emulating UInt64 multiplication/subtraction/wrap. No native proposal accuracy, compiler performance, Lean or all-input proof acceptance.'}
    (D/'model-result.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf8')
    print(json.dumps(out))

if __name__=='__main__':main()
