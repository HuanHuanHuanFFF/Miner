"""Finite exact model for UInt64 reciprocal division; never native performance."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random

HERE = Path(__file__).resolve().parent
MASK32=(1<<32)-1
MASK64=(1<<64)-1

def mul_high(a,b):
    a0,a1=a&MASK32,a>>32
    b0,b1=b&MASK32,b>>32
    p00,p10,p01,p11=a0*b0,a1*b0,a0*b1,a1*b1
    mid=(p00>>32)+(p10&MASK32)+(p01&MASK32)
    return (p11+(p10>>32)+(p01>>32)+(mid>>32))&MASK64

def divrem(a,d):
    if not d:
        return 0,a
    reciprocal=MASK64//d
    q=mul_high(a,reciprocal)
    r=(a-q*d)&MASK64
    if d<=r:
        return q+1,r-d
    return q,r

def main():
    rng=random.Random(2710059)
    directed={0,1,2,3,5,7,31,32,63,64,(1<<23)-1,1<<23,(1<<24)-1,
              (1<<32)-1,1<<32,(1<<36)-1,1<<36,(1<<63)-1,1<<63,MASK64-1,MASK64}
    for k in range(1,64):
        directed.update({(1<<k)-1,1<<k,min((1<<k)+1,MASK64)})
    values=sorted(directed)
    pairs=[(a,d) for a in values for d in values if d]
    pairs.extend((rng.getrandbits(64),rng.randrange(1,1<<64)) for _ in range(50000))
    pairs.extend((rng.randrange(1<<63),rng.randrange(1,1<<36)) for _ in range(50000))
    errors=[]
    stream=hashlib.sha256()
    corrections=0
    for a,d in pairs:
        high=mul_high(a,d)
        expected_high=(a*d)>>64
        result=divrem(a,d)
        expected=divmod(a,d)
        reciprocal=MASK64//d
        corrections+=int(d<=a-mul_high(a,reciprocal)*d)
        stream.update(json.dumps([a,d,high,result],separators=(",",":")).encode()+b"\n")
        if high!=expected_high or result!=expected:
            errors.append({"a":a,"d":d,"high":high,"high_expected":expected_high,
                           "result":result,"expected":expected})
    exhaustive_small=0
    for bits in range(1,9):
        base=1<<bits
        for a in range(base):
            for d in range(1,base):
                reciprocal=(base-1)//d
                q=a*reciprocal//base
                r=a-q*d
                actual=(q+int(d<=r),r-d if d<=r else r)
                assert actual==divmod(a,d),(bits,a,d,actual)
                exhaustive_small+=1
    report={"at_utc":datetime.now(timezone.utc).isoformat(),
            "scope":"FINITE_EXACT_MODEL_NOT_LEAN_NATIVE_PROOF_OR_PERFORMANCE",
            "seed":2710059,"uint64_cases":len(pairs),"exhaustive_smallbase_cases":exhaustive_small,
            "corrections":corrections,"mismatches":errors,
            "result_stream_sha256":stream.hexdigest(),
            "runtime_sha256":hashlib.sha256((HERE/"Reciprocal64.lean.inc").read_bytes()).hexdigest(),
            "zero_divisor":"Runtime delegates to original UInt64 / and %, model does not claim its semantics",
            "cost":"one setup division per row; four32partial-products per mulHigh; one correction; actual C div/mod fusion UNKNOWN"}
    (HERE/"reciprocal-model.json").write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))
    if errors:
        raise SystemExit(1)

if __name__=="__main__":
    main()
