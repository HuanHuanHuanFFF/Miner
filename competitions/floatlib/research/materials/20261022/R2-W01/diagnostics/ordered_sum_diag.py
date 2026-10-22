#!/usr/bin/env python3
"""R2-W01: exact finite binary32 oracle and guarded fixed-grid diagnostics.

Only Python standard library. All reference arithmetic uses arbitrary-precision
integers, never host floating point. NaN payload policy is deliberately outside
this oracle: nonfinite operands are rejected by the proposed fast paths and must
go to the unmodified ContractTensor reference in a real implementation.
Synthetic seeds are independent of the official benchmark seeds.
"""
from __future__ import annotations
import argparse
import hashlib
import json
import random
import struct
from dataclasses import dataclass
from pathlib import Path

SIGN = 0x80000000
L = 1 << 23
U = 1 << 24


def exp(w: int) -> int:
    return (w >> 23) & 255


def finite(w: int) -> bool:
    return exp(w) != 255


def units(w: int) -> int:
    """Exact signed value / 2^-149; finite words only."""
    if not finite(w):
        raise ValueError("nonfinite oracle input: payload semantics not modeled")
    e, f = exp(w), w & (L - 1)
    a = f if e == 0 else (L + f) << (e - 1)
    return -a if w & SIGN else a


def rne_div(n: int, q: int) -> int:
    a, r = divmod(n, q)
    return a + int(2 * r > q or (2 * r == q and a & 1))


def encode_units(v: int, negative_zero: bool = False) -> int:
    """Round exact v*2^-149 to binary32, RN-even and gradual subnormal."""
    if v == 0:
        return SIGN if negative_zero else 0
    sign, a = (SIGN if v < 0 else 0), abs(v)
    if a < L:
        return sign | a
    shift = max(0, a.bit_length() - 24)
    m = rne_div(a, 1 << shift)
    if m == U:
        shift += 1
        m >>= 1
    e = shift + 1
    if e >= 255:
        return sign | 0x7F800000
    return sign | (e << 23) | (m - L)


def add(a: int, b: int) -> int:
    if not finite(a) or not finite(b):
        raise ValueError("nonfinite oracle input")
    v = units(a) + units(b)
    # RN-even exact cancellation gives +0; -0 + -0 alone keeps -0.
    nz = a == SIGN and b == SIGN
    return encode_units(v, nz)


def prefixes(xs: list[int], start: int = 0) -> list[int]:
    out = [start]
    for x in xs:
        out.append(add(out[-1], x))
    return out


def hexes(xs: list[int]) -> list[str]:
    return [f"0x{x:08x}" for x in xs]


@dataclass(frozen=True)
class Summary:
    # Bounds include the empty prefix; this weakens lower-bound acceptance only.
    d: tuple[int, int] = (0, 0)
    lo: tuple[int, int] = (0, 0)
    hi: tuple[int, int] = (0, 0)

    def apply(self, k: int) -> int:
        return k + self.d[k & 1]


def then(a: Summary, b: Summary) -> Summary:
    d, lo, hi = [], [], []
    for p in (0, 1):
        r = (p + a.d[p]) & 1
        d.append(a.d[p] + b.d[r])
        lo.append(min(a.lo[p], a.d[p] + b.lo[r]))
        hi.append(max(a.hi[p], a.d[p] + b.hi[r]))
    return Summary(tuple(d), tuple(lo), tuple(hi))


def atom(v: int, q: int) -> Summary:
    d = (rne_div(v, q), rne_div(q + v, q) - 1)
    return Summary(d, tuple(min(0, x) for x in d),
                   tuple(max(0, x) for x in d))


def summarize(vs: list[int], q: int) -> Summary:
    ans = Summary()
    for v in vs:
        ans = then(ans, atom(v, q))
    return ans


def start_grid(s: int):
    es = exp(s)
    if not 1 <= es <= 253:
        return None
    sign = -1 if s & SIGN else 1
    return sign, es, L + (s & (L - 1)), 1 << (es - 1)


def general_block(s: int, xs: list[int]):
    """Two-parity summary + all-prefix guard. Conservative lower boundary."""
    g = start_grid(s)
    if g is None or any(not finite(x) for x in xs):
        return None, "domain"
    sign, es, k, q = g
    a = summarize([sign * units(x) for x in xs], q)
    p = k & 1
    # Empty prefix is included, so entry exactly L falls back in this version.
    if k + a.lo[p] < L + 1 or k + a.hi[p] > U:
        return None, "prefix_range"
    return encode_units(sign * a.apply(k) * q), "accepted"


def monotone_block(s: int, xs: list[int], odd_only: bool = False):
    """No-tie same-sign path; no prefixes need inspection once end fits.

    odd_only is the proposed cheapest narrow guard:
    zero, or normal same-sign odd significand and E_x <= E_s-2.
    For d>=25 the integer increment is zero. No variable shift >=word width
    is required by a word implementation. Python itself has no shift UB.
    """
    g = start_grid(s)
    if g is None:
        return None, "entry"
    sign, es, k, q = g
    total = 0
    for x in xs:
        if not finite(x):
            return None, "nonfinite"
        v = sign * units(x)
        if v < 0:
            return None, "opposite_sign"
        if v == 0:
            continue
        if odd_only:
            ex, m = exp(x), L + (x & (L - 1))
            if ex == 0 or not (m & 1) or ex > es - 2:
                return None, "odd_exponent_guard"
            d = es - ex
            delta = 0 if d >= 25 else (m + (1 << (d - 1))) >> d
        else:
            a, r = divmod(v, q)
            if 2 * r == q:
                return None, "midpoint"
            delta = a + int(2 * r > q)
        total += delta
    if k + total > U:
        return None, "end_range"
    return encode_units(sign * (k + total) * q), "accepted"


def anchor_block(s: int, xs: list[int]):
    """Same increments via independent RN(H+abs(x)), including odd subnormals.
    Es>=3 is essential: Es=2 admits half-ulp odd subnormal counterexamples.
    This diagnostic uses exact integer add as the native-add semantic oracle.
    """
    g=start_grid(s)
    if g is None or g[1]<3 or len(xs)>64:
        return None,"entry_or_capacity"
    sign,es,k,q=g
    anchor=es<<23
    limit=((es-1)<<23)-1
    total=0
    for x in xs:
        mag=x&0x7fffffff
        if mag and (((x&SIGN)!=(s&SIGN)) or not(mag&1) or mag>limit):
            return None,"domain"
        result=add(anchor,mag)
        delta=result-anchor
        assert 0<=delta<=(1<<22)
        total+=delta
    assert total<=(1<<28)
    if k+total>U:
        return None,"end_range"
    return (s&SIGN)|((s&0x7fffffff)+total),"accepted"


def make_vector(rng: random.Random, kind: str, n: int) -> list[int]:
    words = [rng.getrandbits(32) for _ in range(n)]
    if kind == "dense":
        return [(w & 0x807FFFFF) | ((124 + (w >> 23) % 7) << 23)
                for w in words]
    if kind == "relu":
        return [0 if w & 1 == 0 else
                (w & 0x7FFFFF) | ((124 + (w >> 23) % 7) << 23)
                for w in words]
    if kind == "wide":
        return [(w & 0x807FFFFF) | ((102 + (w >> 23) % 50) << 23)
                for w in words]
    raise ValueError(kind)


def counterexamples():
    cases = []
    xs=[0x41000001,0x3F800003,0x3F800003]
    cases.append(dict(name="odd_positive_relu_reassociation_and_exact_total",
        inputs=hexes(xs),ordered=f"0x{prefixes(xs)[-1]:08x}",
        reordered=f"0x{prefixes([xs[1],xs[2],xs[0]])[-1]:08x}",
        one_final_round=f"0x{encode_units(sum(map(units,xs))):08x}",
        sound_anchor=f"0x{anchor_block(xs[0],xs[1:])[0]:08x}"))
    xs = [0x4B800000, 0x3F800000, 0xCB800000]
    ps = prefixes(xs)
    cases.append(dict(name="exact_total_does_not_determine_ordered_sum",
        inputs=hexes(xs), ordered=hexes(ps),
        one_final_round=f"0x{encode_units(sum(map(units, xs))):08x}"))
    xs = [0x41000000, 0xC1000000, 0x3E000001]
    cases.append(dict(name="dense_domain_reassociation",
        inputs=hexes(xs), left=f"0x{prefixes(xs)[-1]:08x}",
        right=f"0x{add(xs[0], add(xs[1], xs[2])):08x}"))
    s, x = 0x3F800001, 0x33800000
    q, k = 1 << 126, L + 1
    cases.append(dict(name="tie_requires_start_parity", start=f"0x{s:08x}",
        input=f"0x{x:08x}", ordered=f"0x{add(s,x):08x}",
        independent_rounded_increment=f"0x{encode_units((k+rne_div(units(x),q))*q):08x}"))
    s, xs = 0x3F800001, [0xB4400000, 0x34000000]
    q, k = 1 << 126, L + 1
    ss = summarize(list(map(units, xs)), q)
    cases.append(dict(name="lower_binade_boundary_endpoint_test_unsound",
        start=f"0x{s:08x}", inputs=hexes(xs), ordered=hexes(prefixes(xs,s)),
        predicted_final=f"0x{encode_units(ss.apply(k)*q):08x}",
        predicted_min=k+ss.lo[k&1], predicted_max=k+ss.hi[k&1],
        sound_guard=general_block(s,xs)[1]))
    a = 0x7F7FFFFF
    cases.append(dict(name="intermediate_overflow_hidden_by_exact_total",
        inputs=hexes([a,a,a|SIGN]), first_overflow=f"0x{add(a,a):08x}",
        exact_total=f"0x{encode_units(units(a)):08x}",
        fast_path=monotone_block(a,[a,a|SIGN],True)[1],
        final_ordered="+Inf (IEEE finite-input overflow; NaN payload irrelevant)"))
    cases.append(dict(name="signed_zero_is_not_real_equality",
        input="0x80000000", ordered_from_poszero=f"0x{add(0,SIGN):08x}",
        return_input_wrong="0x80000000"))
    cases.append(dict(name="gradual_subnormal_cancellation",
        inputs=hexes([0x00800000,0x807FFFFF]),
        ordered=f"0x{add(0x00800000,0x807FFFFF):08x}",
        odd_guard=monotone_block(0x00800000,[0x807FFFFF],True)[1]))
    s,x=0x01000001,0x00000001
    a=0x01000000
    cases.append(dict(name="anchor_Es2_subnormal_tie_requires_rejection",
        start=f"0x{s:08x}",input=f"0x{x:08x}",
        true_result=f"0x{add(s,x):08x}",
        wrong_without_Es3_guard=f"0x{s+(add(a,x)-a):08x}",
        actual_guard=anchor_block(s,[x])[1]))
    return cases


def finite_checks(rng: random.Random, count: int):
    accepted = {"general":0,"monotone":0,"odd":0,"anchor":0}
    checked = 0
    for _ in range(count):
        es = rng.randrange(1,254)
        sw = (es<<23) | rng.randrange(L)
        if rng.randrange(2):
            sw |= SIGN
        # Cluster half of tests around binade edges and very small contributions.
        if rng.randrange(4)==0:
            sw = (sw & 0xFF800000) | rng.choice([0,1,2,L-2,L-1])
        xs=[]
        for _ in range(rng.randrange(1,9)):
            ex=max(0,min(254,es-rng.randrange(0,30)))
            x=(ex<<23)|rng.randrange(L)
            if rng.randrange(3)==0:
                x |= SIGN
            xs.append(x)
        for name,fn in [("general",general_block),("monotone",monotone_block),
                        ("odd",lambda s,x:monotone_block(s,x,True)),
                        ("anchor",anchor_block)]:
            out,why=fn(sw,xs)
            if out is not None:
                ps=prefixes(xs,sw)
                if out!=ps[-1]:
                    raise AssertionError((name,hexes([sw]+xs),hex(out),hex(ps[-1])))
                accepted[name]+=1
        checked+=1
    # Nonfinite words are each rejected regardless of payload and sign.
    raw=[0x7F800000,0xFF800000,0x7FC00001,0x7FA00001,0xFFC12345,0xFF800001]
    for w in raw:
        assert general_block(0x40000000,[w])[0] is None
        assert monotone_block(0x40000000,[w],True)[0] is None
        assert anchor_block(0x40000000,[w])[0] is None
    return dict(blocks=checked,accepted=accepted,accepted_mismatches=0,
                nonfinite_rejection_examples=hexes(raw))


def oracle_sanity(seed: int):
    rng=random.Random(seed)
    pairs=0
    for _ in range(50000):
        a,b=rng.getrandbits(32),rng.getrandbits(32)
        if not finite(a) or not finite(b):continue
        assert encode_units(units(a),a==SIGN)==a
        fa=struct.unpack('<f',struct.pack('<I',a))[0]
        fb=struct.unpack('<f',struct.pack('<I',b))[0]
        f=fa+fb
        try: host=struct.unpack('<I',struct.pack('<f',f))[0]
        except OverflowError: host=(SIGN if f<0 else 0)|0x7f800000
        assert add(a,b)==host,(hex(a),hex(b),hex(add(a,b)),hex(host))
        pairs+=1
    return dict(finite_pairs=pairs,integer_vs_host_add_mismatches=0,
                note="Independent sanity check, not a formal floating-point theorem")


def summary_checks(rng: random.Random, count: int):
    for _ in range(count):
        q=1<<rng.randrange(0,12)
        chunks=[[rng.randrange(-100*q,100*q+1) for _ in range(rng.randrange(0,10))]
                for _ in range(3)]
        a,b,c=map(lambda xs:summarize(xs,q),chunks)
        assert then(then(a,b),c)==then(a,then(b,c))
        allxs=sum(chunks,[])
        ss=then(then(a,b),c)
        for k in (-101,-100,0,1,100,101):
            z=k; lo=k; hi=k
            for v in allxs:
                z=rne_div(z*q+v,q);lo=min(lo,z);hi=max(hi,z)
            assert (z,lo,hi)==(ss.apply(k),k+ss.lo[k&1],k+ss.hi[k&1])
    return dict(composition_trials=count,integer_start_values_per_trial=6,
                associativity_or_prefix_mismatches=0)


def coverage(vectors: int, n: int, blocks: list[int], seed: int):
    output={}
    for ci,kind in enumerate(["dense","relu","wide"]):
        rng=random.Random(seed+ci*100003)
        records={str(b):{name:dict(attempted=0,accepted=0,accepted_elements=0,
                    rejected={},mismatches=0) for name in ["general","monotone","odd","anchor"]}
                 for b in blocks}
        h=hashlib.sha256()
        first_at_least_32=[]
        for trial in range(vectors):
            xs=make_vector(rng,kind,n)
            for w in xs: h.update(struct.pack('<I',w))
            ps=prefixes(xs)
            if kind=="relu":
                first_at_least_32.append(next((i for i,s in enumerate(ps)
                                              if exp(s)>=132),n+1))
            for b in blocks:
                for i in range(1,n,b):
                    xx=xs[i:i+b]
                    for name,fn in [("general",general_block),("monotone",monotone_block),
                                    ("odd",lambda s,x:monotone_block(s,x,True)),
                                    ("anchor",anchor_block)]:
                        r=records[str(b)][name]
                        r["attempted"]+=1
                        out,why=fn(ps[i],xx)
                        if out is None:
                            r["rejected"][why]=r["rejected"].get(why,0)+1
                        else:
                            r["accepted"]+=1;r["accepted_elements"]+=len(xx)
                            if out!=ps[i+len(xx)]:
                                r["mismatches"]+=1
                                raise AssertionError((kind,b,trial,i,name))
        output[kind]=dict(vectors=vectors,length=n,words_sha256=h.hexdigest(),blocks=records)
        if first_at_least_32:
            output[kind]["first_prefix_at_least_32"]={
                "min":min(first_at_least_32),"max":max(first_at_least_32),
                "mean":sum(first_at_least_32)/len(first_at_least_32)}
    return output


def main():
    p=argparse.ArgumentParser()
    p.add_argument('--vectors',type=int,default=100)
    p.add_argument('--length',type=int,default=1000)
    p.add_argument('--seed',type=int,default=927401)
    p.add_argument('--output',default='results/diagnostics.json')
    a=p.parse_args()
    rng=random.Random(a.seed+999983)
    data=dict(status="FINITE_DIAGNOSTIC_EXECUTED_NOT_LEAN_OR_TARGET_PERFORMANCE",
        source="Fresh synthetic words, official word transformations, independent Python RNG",
        seed=a.seed,counterexamples=counterexamples(),
        oracle_sanity=oracle_sanity(a.seed+634781),
        summary_checks=summary_checks(rng,5000),
        finite_checks=finite_checks(rng,20000),
        coverage=coverage(a.vectors,a.length,[8,16,32,64],a.seed),
        limitations=["Not an exhaustive binary32 proof",
          "No NaN payload reference implementation; fast path rejection only",
          "No official LCG inputs, no saved answers, no Lean compilation",
          "No target performance or predicted speedup"])
    out=Path(a.output);out.parent.mkdir(parents=True,exist_ok=True)
    out.write_text(json.dumps(data,indent=2,ensure_ascii=False)+'\n')
    print(json.dumps({"output":str(out),"finite_checks":data['finite_checks'],
                      "summary_checks":data['summary_checks']},ensure_ascii=False))


if __name__=='__main__':main()
