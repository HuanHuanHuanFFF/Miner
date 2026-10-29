"""Exact boundary discriminator for copied PortableF64 midpoint expressions."""
from pathlib import Path
from fractions import Fraction
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
S32,S64=1<<31,1<<63
def p2(k): return Fraction(1<<max(k,0),1<<max(-k,0))
def decode64(w):
    e=(w>>52)&2047;f=w&((1<<52)-1)
    assert e!=2047
    z=1-1023-52 if e==0 else e-1023-52
    v=(f if e==0 else (1<<52)+f)*p2(z)
    return -v if w&S64 else v
def midpoint(q):
    mag=q&0x7fffffff;e=(mag>>23)&255;f=mag&0x7fffff
    base=((e+896)<<52)|(f<<29)
    below=base-(0x20000000 if mag==0x00800000 else 0x10000000)
    above=base+0x10000000
    return (above|S64,below|S64) if q&S32 else (below,above)
rows=[]
for e in range(1,255):
    for f in [0,1,2,(1<<23)-2,(1<<23)-1]:
        unsigned=((1<<23)+f)*p2(e-150)
        low=(Fraction((1<<23)+f)- (Fraction(1,4) if f==0 and e>1 else Fraction(1,2)))*p2(e-150)
        high=(Fraction((1<<23)+f)+Fraction(1,2))*p2(e-150)
        for s in [0,S32]:
            q=s|(e<<23)|f
            lo,hi=midpoint(q)
            expected=(-high,-low) if s else (low,high)
            actual=decode64(lo),decode64(hi)
            assert actual==expected,(q,lo,hi,actual,expected)
            assert actual[0]<(-unsigned if s else unsigned)<actual[1]
            assert lo&((1<<63)-1)>0 and hi&((1<<63)-1)>0
            assert (lo>>52)&2047!=2047 and (hi>>52)&2047!=2047
            if (e,f) in [(1,0),(1,1),(2,0),(254,0),(254,(1<<23)-1)]:
                rows.append(dict(q_hex=f"0x{q:08x}",lower_hex=f"0x{lo:016x}",upper_hex=f"0x{hi:016x}",
                                 lower_exact=str(actual[0]),upper_exact=str(actual[1])))
receipt=dict(at_utc=datetime.now(timezone.utc).isoformat(),arithmetic="exact fractions.Fraction",
    status="PASS_FINITE_BOUNDARY_DISCRIMINATOR",cases=254*5*2,
    enumerated="Every normal binary32 exponent 1..254; f in {0,1,2,2^23-2,2^23-1}; both signs",
    source="Copied old dd775 certify midpoint arithmetic, independently compared to exact signed cell formulas",
    not_claimed="No all-input Lean acceptance, producer enclosure, or actual native Float execution.",
    v2_actual_checker_sha256=hashlib.sha256((HERE/"v2/ActualChecker.lean.inc").read_bytes()).hexdigest(),
    examples=rows)
(HERE/"checker-boundaries.json").write_text(json.dumps(receipt,indent=2)+"\n",encoding="utf-8")
print(json.dumps({k:v for k,v in receipt.items() if k!="examples"},indent=2))

