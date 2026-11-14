"""Finite falsifier for RMS-only projection and UInt64 carry boundaries.

Not a Lean proof, native checksum result or performance measurement.
"""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random

HERE = Path(__file__).resolve().parent
MASK = (1 << 64)-1

def mantissa(word):
    exp = (word >> 23) & 255
    return (word & 0x7fffff)+(0 if exp == 0 else 1 << 23)

def index(word):
    exp = (word >> 23) & 255
    return 0 if exp == 0 else exp-1

def shift_left(word, amount):
    return (word << (amount & 63)) & MASK

def shift_right(word, amount):
    return word >> (amount & 63)

def add128(high, low, term):
    nxt = (low + term) & MASK
    return (high + int(nxt < low)) & MASK, nxt

def original(words, base, n, exponent, j, state, valid):
    ph, pl, nh, nl, qh, ql = state
    for t in range(j,n):
        w = words[base+t] if base+t < len(words) else 0
        m = mantissa(w)
        s = max(index(w)-exponent,0)
        term = shift_left(m,s)
        square = m*m
        s2 = 2*s
        low_term = shift_left(square,s2) if s2 < 64 else 0
        qh,ql = add128(qh,ql,low_term)
        hi_term = shift_right(square >> 1,63-s2) if s2 < 64 else shift_left(square,s2-64)
        qh = (qh+hi_term)&MASK
        valid = valid and (m == 0 or s <= 36)
        if w >> 31:
            nh,nl = add128(nh,nl,term)
        else:
            ph,pl = add128(ph,pl,term)
    return bool(valid and n < 256),(qh << 64)+ql

def squares(words, base, n, exponent, j, state, valid):
    qh,ql = state
    for t in range(j,n):
        w = words[base+t] if base+t < len(words) else 0
        m = mantissa(w)
        s2 = 2*max(index(w)-exponent,0)
        square = m*m
        lo = shift_left(square,s2) if s2 < 64 else 0
        hi = shift_right(square >> 1,63-s2) if s2 < 64 else shift_left(square,s2-64)
        nxt = (ql+lo)&MASK
        qh = (qh+int(nxt < ql)+hi)&MASK
        ql = nxt
        valid = valid and (m == 0 or max(index(w)-exponent,0) <= 36)
    return bool(valid and n < 256),(qh << 64)+ql

def main():
    rng = random.Random(2700057)
    cases = []
    fixtures = [0,0x80000000,1,0x007fffff,0x00800000,0x3f800000,
                0x3fffffff,0x7f7fffff,0x7f800000,0x7fc00001,0xff800000,0xffffffff]
    boundary_states = [0,1,(1<<63)-1,1<<63,MASK-1,MASK]
    for w in fixtures:
        for exp in [0,1,16,31,32,36,64,126,253,255,1<<64]:
            for high in boundary_states:
                cases.append(([w,w^0x80000000,w,0],0,4,exp,0,
                              (high,MASK,high,0,high,MASK),True))
    for _ in range(4000):
        length = rng.randrange(0,129)
        words = [rng.getrandbits(32) for _ in range(length)]
        n = rng.choice([0,1,2,31,32,63,64,127,128,255,256,257])
        j = rng.randrange(0,n+1)
        state = tuple(rng.choice(boundary_states) if rng.randrange(3)==0 else rng.getrandbits(64) for _ in range(6))
        cases.append((words,rng.randrange(0,7),n,rng.randrange(0,300),j,state,bool(rng.getrandbits(1))))
    h = hashlib.sha256()
    mismatch = []
    for case in cases:
        words,base,n,exp,j,state,valid = case
        expected = original(*case)
        actual = squares(words,base,n,exp,j,state[4:],valid)
        h.update(json.dumps([case,expected,actual],separators=(",", ":")).encode()+b"\n")
        if expected != actual:
            mismatch.append({"case":case,"expected":expected,"actual":actual})
    report = {
        "at_utc":datetime.now(timezone.utc).isoformat(),
        "scope":"FINITE_UINT64_PROJECTION_MODEL_ONLY_NOT_LEAN_NATIVE_PROOF_SPEED",
        "seed":2700057,"cases":len(cases),"mismatches":mismatch,
        "case_result_stream_sha256":h.hexdigest(),
        "source_sha256":hashlib.sha256((HERE/"SquareOnlyLoop.lean.inc").read_bytes()).hexdigest(),
        "coverage":["zero/sign/subnormal/normal/nonfinite raw words", "128-bit carry/wrap boundary states",
                    "n0/n255/n256/n257", "out-of-bounds getter defaults", "arbitrary starting first moments discarded",
                    "alignment0..299 and huge exponent Nat", "initial valid false/true"],
    }
    (HERE/"square-projection-model.json").write_text(json.dumps(report,indent=2)+"\n",encoding="utf-8")
    print(json.dumps(report,indent=2))
    if mismatch:
        raise SystemExit(1)

if __name__ == "__main__":
    main()
