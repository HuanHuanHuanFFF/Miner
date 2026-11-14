"""Self-authored exact finite model and guard census for R27 normalization.

Formula model follows pinned ContractExact/StableNorm and ExactSuite semantics.
It does not execute Lean and is not a proof, benchmark score or champion claim.
"""
from __future__ import annotations

import argparse
from collections import Counter
from datetime import datetime, timezone
from fractions import Fraction
import hashlib
import json
from math import isqrt
from pathlib import Path
import random
import struct

MASK = (1 << 32) - 1
EPS = 0x3727C5AC


def fields(w):
    e = (w >> 23) & 255
    return (-1 if w >> 31 else 1), ((w & 0x7FFFFF) | (0x800000 if e else 0)), max(0, e - 1)


def key(w):
    s, m, i = fields(w)
    return s * (m << i)


def floor_log_ratio(n, d):
    e = n.bit_length() - d.bit_length()
    if (n < d << e) if e >= 0 else (n << -e < d):
        e -= 1
    return e


def quotient_even(n, d):
    q, r = divmod(n, d)
    return q + (2 * r > d or (2 * r == d and q & 1))


def encode_integer(m, e, sign=0):
    if m == 0:
        return sign << 31
    while m >= 1 << 24:
        assert m & 1 == 0
        m >>= 1
        e += 1
    if e == -149 and m < 1 << 23:
        return (sign << 31) | m
    exponent = e + 150
    if exponent >= 255:
        return (sign << 31) | 0x7F800000
    assert 1 <= exponent <= 254 and (1 << 23) <= m < (1 << 24)
    return (sign << 31) | (exponent << 23) | (m - (1 << 23))


def round_ratio(n, d=1, e=0):
    if n == 0 or d == 0:
        return 0
    sign = int(n < 0)
    n = abs(n)
    target = max(-149, floor_log_ratio(n, d) + e - 23)
    shift = e - target
    m = quotient_even(n << shift, d) if shift >= 0 else quotient_even(n, d << -shift)
    return encode_integer(m, target, sign)


def sqrt_ratio(n, d):
    if n <= 0:
        return 0
    target = max(-149, floor_log_ratio(n, d) // 2 - 23)
    a, b = (n << (-2 * target), d) if target <= 0 else (n, d << (2 * target))
    r = isqrt(a // b)
    midpoint = (2 * r + 1) ** 2 * b
    rounded = r + (4 * a > midpoint or (4 * a == midpoint and r & 1))
    return encode_integer(rounded, target)


def lcg(n, seed):
    out = []
    for _ in range(n):
        seed = (seed * 1664525 + 1013904223) & MASK
        out.append(seed)
    return out


def gen(kind, n, seed):
    out = []
    for w in lcg(n, seed):
        low, span = (87, 40) if kind == "wide" else (121, 6)
        v = (w & 0x807FFFFF) | ((low + (w >> 23) % span) << 23)
        out.append(0 if kind == "sparse" and ((w >> 9) & 1) == 0 else v)
    return out


def weights(kind, seed, layer, fan, count):
    scale = key(round_ratio(4, max(1, isqrt(fan))))
    return [round_ratio(key(w) * scale, 1, -298)
            for w in gen("sparse" if kind == "sparse" else "normal", count,
                         (seed + 101 * layer) & MASK)]


def bias(seed, layer, n):
    return [round_ratio(key(w), 1, -157) for w in gen("normal", n, (seed + 101 * layer) & MASK)]


def scale(seed, n):
    return [(w & 0x7FFFFF) | 0x3F800000 for w in gen("normal", n, seed)]


def linear(x, rows, k, out, w, b, relu):
    xk = list(map(key, x)); wk = list(map(key, w)); bk = [key(z) << 149 for z in b]
    result = []
    for r in range(rows):
        for j in range(out):
            total = sum(xk[r*k+i] * wk[j*k+i] for i in range(k)) + bk[j]
            result.append(0 if relu and total <= 0 else round_ratio(total, 1, -298))
    return result


def guard_state(n, w, gw, bw, b0, S1, dw, cap):
    sw, mw, iw = fields(w); sg, mg, ig = fields(gw); sb, mb, ib = fields(bw)
    sd, md, idd = fields(dw); ed = (dw >> 23) & 255
    if not (1 <= ed <= 254 and sd > 0 and 0 < n < 4096 and abs(S1) < 1 << 60):
        return "row_guard", None
    if not (mw == 0 or (b0 <= iw and iw - b0 <= 24)):
        return "input_span", None
    cv = abs(n * sw * (mw << max(0, iw - b0)) - S1)
    D = n * md
    c2 = min(b0 + ig, ib + idd)
    ks, bs = b0 + ig - c2, ib + idd - c2
    q0, r0 = divmod(cv, D)
    r0 *= mg
    qq = q0 * mg + r0 // D
    if ks > cap:
        return "ks", ks
    if qq >= 1 << (61 - ks):
        return "quotient_width", ks
    if bs > 37:
        return "bias_span", ks
    return "inner_fast", ks


def norm(x, rows, n, g, b=None, census=None):
    result = []
    ek = key(EPS)
    for row in range(rows):
        words = x[row*n:(row+1)*n]
        values = list(map(key, words))
        S = sum(values); Q = sum(v*v for v in values)
        if b is None:
            den = sqrt_ratio(Q + n * ek * (1 << 149), n << 298)
        else:
            den = sqrt_ratio(n*Q-S*S+n*n*ek*(1 << 149), n*n << 298)
        dk = key(den)
        b0 = min((fields(w)[2] for w in words if fields(w)[1]), default=255)
        s1 = sum(s * (m << max(0, i-b0)) for s, m, i in map(fields, words))
        if census is not None:
            census["rows"] += 1
            census["row_lengths"][n] += 1
            census["stats_fast_nlt256"] += n < 256 and all(m == 0 or i-b0 <= 36 for s,m,i in map(fields,words))
        for j, value in enumerate(values):
            if b is None:
                result.append(round_ratio(value*key(g[j]), dk, -149))
            else:
                result.append(round_ratio((n*value-S)*key(g[j])+n*dk*key(b[j]), n*dk, -149))
                if census is not None:
                    for cap in [8, 26, 28]:
                        state, ks = guard_state(n, words[j], g[j], b[j], b0, s1, den, cap)
                        census[f"cap{cap}"][state] += 1
                        if cap == 8 and ks is not None:
                            census["ks_distribution"][ks] += 1
    return result


def dimensions(seed, profile):
    r = lcg(8, seed ^ 0x5BD1E995)
    draw = lambda i, span: r[i] % span
    edge = lambda base, i: base - 1 if (r[i] & 0x1000) == 0 else base + 1
    h = edge((8+draw(1,25))*8,3) if profile == "boundary" else ((2+draw(1,7))*16 if profile == "scale" else (8+draw(1,25))*8)
    h2 = edge((4+draw(2,13))*8,4) if profile == "boundary" else ((1+draw(2,4))*16 if profile == "scale" else (4+draw(2,13))*8)
    i = edge((16+draw(0,49))*8,2) if profile == "boundary" else ((4+draw(0,45))*16 if profile == "scale" else (16+draw(0,49))*8)
    return i,h,h2


def fixture_checks():
    rng = random.Random(0x2704)
    checked = 0
    for _ in range(2000):
        w = rng.getrandbits(32)
        if ((w >> 23) & 255) == 255:
            continue
        assert round_ratio(key(w), 1, -149) == (w if w & 0x7FFFFFFF else 0)
        checked += 1
    for n in [1,2,3,7,32,97,256]:
        words = gen("wide", n, 270501+n)
        vals = [Fraction(key(w),1<<149) for w in words]
        s,q = sum(map(key,words)),sum(key(w)**2 for w in words)
        mean = sum(vals)/n
        assert sum((v-mean)**2 for v in vals)/n == Fraction(n*q-s*s, n*n << 298)
        checked += 1
    return checked


def main():
    p=argparse.ArgumentParser();p.add_argument("--seeds",type=int,default=3);args=p.parse_args()
    start=datetime.now(timezone.utc).isoformat(); results=[]
    checks=fixture_checks()
    for seed in [27051001+i*100003 for i in range(args.seeds)]:
        for profile in ["typical","scale","boundary"]:
            i,h,h2=dimensions(seed,profile)
            for kind in ["normal","wide","sparse"]:
                for rows in [1,8]:
                    c={"rows":0,"stats_fast_nlt256":0,"row_lengths":Counter(),"ks_distribution":Counter(),
                       **{f"cap{k}":Counter() for k in [8,26,28]}}
                    x=gen(kind,rows*i,seed+999)
                    x=linear(x,rows,i,h,weights(kind,seed,1,i,h*i),bias(seed,2,h),True)
                    x=norm(x,rows,h,scale(seed+3,h),census=c)
                    x=linear(x,rows,h,h2,weights(kind,seed,4,h,h2*h),bias(seed,5,h2),True)
                    x=norm(x,rows,h2,scale(seed+6,h2),bias(seed,7,h2),census=c)
                    x=linear(x,rows,h2,10,weights(kind,seed,8,h2,10*h2),bias(seed,9,10),False)
                    results.append({"seed":seed,"profile":profile,"kind":kind,"rows":rows,
                        "shape":[i,h,h2,10],"census":c,"output_sha256":hashlib.sha256(b''.join(struct.pack('<I',w)for w in x)).hexdigest()})
    out={"status":"EXACT_FINITE_FORMULA_MODEL_NOT_LEAN","start_utc":start,"end_utc":datetime.now(timezone.utc).isoformat(),
         "source_sha256":hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),"fixture_checks":checks,"cells":results,
         "excluded_claims":["No Lean runtime validation","No original full gate","No champion timing","Guard counts omit downstream rrsG fallback"]}
    dest=Path(__file__).with_name("norm-frontier-result.json");dest.write_text(json.dumps(out,indent=2),encoding="utf-8")
    print(json.dumps({"output":str(dest),"cells":len(results),"fixture_checks":checks}))


if __name__=="__main__":main()
