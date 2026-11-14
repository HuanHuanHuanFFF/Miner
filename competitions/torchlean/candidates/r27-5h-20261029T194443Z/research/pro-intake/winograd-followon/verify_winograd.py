#!/usr/bin/env python3
"""Original, deterministic exact-integer audit of the supplied Winograd fragments.

No Lean execution, floating-point arithmetic, timing, benchmark seeds, or input
generation for a model board. Only finite mathematical boundary checks. The
supplied public YL/YD word arithmetic is modelled; existing Ybo rounding is
represented by an independent integer RNE oracle, not revalidated as Lean.
The missing R27PackedLinear helpers are NOT modelled or claimed verified.
"""
from __future__ import annotations

import argparse
from dataclasses import dataclass
import hashlib
import itertools
import json
from pathlib import Path
import re
import shutil

U32 = (1 << 32) - 1
U64 = (1 << 64) - 1
U128 = (1 << 128) - 1
U192 = (1 << 192) - 1
SENTINEL = 1 << 32
SIGNED63_PEAK_SUM = 3037000499
ONE = 0x3F800000


def finite(w):
    return ((w >> 23) & 255) != 255


def mant(w):
    return (w & 0x7FFFFF) + (0 if ((w >> 23) & 255) == 0 else 1 << 23)


def idx(w):
    return max(((w >> 23) & 255) - 1, 0)


def signed_mant(w):
    return -mant(w) if w >> 31 else mant(w)


def signed(z, bits):
    z &= (1 << bits) - 1
    return z - (1 << bits) if z >> (bits - 1) else z


def words128(z):
    z &= U128
    return z >> 64, z & U64


def value128(h, l):
    return signed((h << 64) | l, 128)


def add_signed(h, l, p, negative):
    assert 0 <= p <= U64
    if negative:
        return (h - int(l < p)) & U64, (l - p) & U64
    ll = (l + p) & U64
    return (h + int(ll < l)) & U64, ll


def subtract(h, l, rh, rl):
    return (h - rh - int(l < rl)) & U64, (l - rl) & U64


def add_twos_signed63(h, l, p):
    """QhiS-style update: requires the actual product in signed64 range."""
    p &= U64
    ll = (l + p) & U64
    return (h - (p >> 63) + int(ll < l)) & U64, ll


def shr(w, s):
    return w >> (s & 63)


def shl(w, s):
    return (w << (s & 63)) & U64


def round_shift_even(m, s):
    if s <= 0:
        return m << -s
    q, r = divmod(m, 1 << s)
    half = 1 << (s - 1)
    return q + int(r > half or (r == half and (q & 1)))


def round_binary32(z, e, negative_zero=False):
    """Round the exact dyadic z*2**e once, nearest ties to even."""
    if z == 0:
        return 0x80000000 if negative_zero else 0
    sign = 0x80000000 if z < 0 else 0
    m = abs(z)
    target = max(m.bit_length() - 1 + e - 23, -149)
    q = round_shift_even(m, target - e)
    if q == 0:
        return sign
    if q >= 1 << 24:
        assert q == 1 << 24
        q >>= 1
        target += 1
    if q < 1 << 23:
        assert target == -149
        return sign | q
    exponent = target + 150
    if exponent >= 255:
        return sign | 0x7F800000
    assert 1 <= exponent <= 254
    return sign | (exponent << 23) | (q - (1 << 23))


def act(relu, w):
    nan = ((w >> 23) & 255) == 255 and (w & 0x7FFFFF) != 0
    return 0 if relu and (w >> 31) and not nan else w


def exact_linear_word(x, w, bias):
    assert len(x) == len(w) and all(map(finite, (*x, *w, bias)))
    total, negative_zero = 0, True
    for a, b in zip((*x, ONE), (*w, bias)):
        product = mant(a) * mant(b)
        neg = bool((a ^ b) >> 31)
        total += (-product if neg else product) << (idx(a) + idx(b))
        negative_zero = negative_zero and product == 0 and neg
    return round_binary32(total, -298, negative_zero)


def metadata(words):
    """Public23 Yc/Yah for an in-bounds row below its USize index guard."""
    lo, hi = U32, 0
    for w in words:
        v = w & 0x7FFFFFFF
        lo, hi = min(lo, (v - 1) & U32), max(hi, v)
    return ((lo >> 23) << 16) + (hi >> 23)


def yk(k):
    return max(k - 1, 0)


def decode(payload):
    magnitude = payload & U32
    return (-magnitude if payload >> 32 else magnitude) & U64


def magnitude(v):
    return ((-v) & U64) if v >> 63 else v


@dataclass(frozen=True)
class Cache:
    low: int
    peak: int
    data: tuple[int, ...]
    self_hi: int
    self_lo: int
    valid: bool


def prepare(words, supplied_metadata=None):
    md = metadata(words) if supplied_metadata is None else supplied_metadata
    low, high = yk(md >> 16), yk(md & 0xFFFF)
    if max(high - low, 0) > 8:  # Lean Nat subtraction is truncated.
        return Cache(low, 0, (), 0, 0, False)
    peak, payloads = 0, []
    for w in words:
        m, e = mant(w), idx(w)
        if m == 0:
            payloads.append(0)  # Deliberate loss of +/-zero provenance.
        else:
            if e < low or e - low > 8:
                return Cache(low, 0, (), 0, 0, False)
            value = m << (e - low)
            assert value < 1 << 32
            peak = max(peak, value)
            payloads.append(value + ((1 << 32) if w >> 31 else 0))
    h, l = 0, 0
    for i in range(0, len(payloads) - 1, 2):
        x, y = payloads[i:i+2]
        h, l = add_signed(h, l, (x & U32) * (y & U32), bool((x ^ y) >> 32))
    return Cache(low, peak, tuple(payloads), h, l, True)


def total_words(a, b, mode="unsigned"):
    assert a.valid and b.valid and len(a.data) == len(b.data)
    assert a.peak + b.peak < 1 << 32
    n, h, l = len(a.data), 0, 0
    if mode == "signed63":
        assert a.peak + b.peak <= SIGNED63_PEAK_SUM
    for i in range(0, n-1, 2):
        x = (decode(a.data[i]) + decode(b.data[i+1])) & U64
        y = (decode(a.data[i+1]) + decode(b.data[i])) & U64
        if mode in ("signed63", "bad_unconditionally_signed"):
            h, l = add_twos_signed63(h, l, x*y)
        else:
            p = magnitude(x) * magnitude(y)
            assert p <= U64
            h, l = add_signed(h, l, p, bool((x ^ y) >> 63))
    h, l = subtract(h, l, a.self_hi, a.self_lo)
    h, l = subtract(h, l, b.self_hi, b.self_lo)
    if n % 2:
        x, y = a.data[-1], b.data[-1]
        h, l = add_signed(h, l, (x & U32)*(y & U32), bool((x ^ y) >> 32))
    return h, l


def yl(low, a, b, w2, w1, w0, c):
    """Word-for-word arithmetic shape of supplied public23 YL."""
    m = (mant(a)*mant(b)) & U64
    s = (idx(a)+idx(b)-low) & U64
    rr = s & 63
    x0, x1 = shl(m, rr), shr(m >> 1, 63-rr)
    y0, y1, y2 = (x0, x1, 0) if s < 64 else (0, x0, x1)
    ng = (a ^ b) >> 31
    mask = (-ng) & U64
    s0 = (w0+(y0 ^ mask)) & U64
    k0 = int(s0 < w0)
    u1 = (w1+(y1 ^ mask)) & U64
    ka = int(u1 < w1)
    s1 = (u1+k0) & U64
    kb = int(s1 < u1)
    return (w2+(y2 ^ mask)+(ka | kb)) & U64, s1, s0, (c+ng) & U64


def yd(w2, w1, w0, c, e):
    """Public23 YD carry propagation; Ybo replaced by integer RNE oracle."""
    t0 = (w0+c) & U64
    t1 = (w1+int(t0 < w0)) & U64
    t2 = (w2+int(t1 < w1)) & U64
    raw = (t2 << 128) | (t1 << 64) | t0
    return (SENTINEL if raw == 0 else round_binary32(signed(raw, 192), e)), raw


def finish_native(product_index, h, l, bias):
    """Return None on missing wide-Int helper; never call it verified."""
    top = (-(h >> 63)) & U64
    body = value128(h, l)
    if mant(bias) == 0:
        value, raw = yd(top, h, l, 0, product_index-298)
        assert signed(raw, 192) == body
        return value, "zero_bias"
    bias_index = 126+idx(bias)
    low = min(product_index, bias_index)
    bs, zs = product_index-low, bias_index-low
    if bs > 63 or zs >= 128:
        return None, "wide_fallback_unverified"
    if bs == 0:
        w2, w1, w0 = top, h, l
    else:
        w2 = shl(top, bs) | shr(h, 64-bs)
        w1 = shl(h, bs) | shr(l, 64-bs)
        w0 = shl(l, bs)
    state = yl(low, ONE, bias, w2, w1, w0, 0)
    value, raw = yd(*state, low-298)
    exact = (body << bs) + (signed_mant(bias) << (23+zs))
    assert -(1 << 191) <= exact < 1 << 191
    assert signed(raw, 192) == exact
    return value, "native_bias"


def wrapper_route(rows, n, outw, x, w, b):
    if rows == 0 or outw == 0:
        return "empty"
    if (n == 0 or n >= 1 << 30 or len(x) != rows*n or len(w) != outw*n
            or len(b) != outw or not all(map(finite, (*x, *w, *b)))):
        return "retained_whole_kernel"
    return "prepare"


def finish_zero_body_shortcut(relu, h, l, bias):
    if (h | l) == 0:
        if mant(bias) != 0:
            return bias
        if relu:
            return 0
    return None


def audit_old_counts(path):
    text = path.read_text()
    if path.suffix == ".json":
        data = json.loads(text)
    else:
        m = re.search(r"=====BEGIN winograd-discriminator-result\.json[^\n]*\n(.*?)\n=====END", text, re.S)
        if not m:
            raise ValueError("Frozen discriminator JSON block not found")
        data = json.loads(m.group(1))
    answer = {"cell_count": len(data["cells"]), "scope": "arithmetic on attached old summaries; no input replay"}
    for which in ("linear1", "linear2"):
        c0 = prep = eligible = outputs = complete = weighted = 0
        for cell in data["cells"]:
            d = cell[which]
            r, n, o = d["shape"]
            e, q, t = d["eligible_outputs"], n//2, n%2
            c0 += r*n*o
            prep += (r+o)*q
            eligible += e
            outputs += r*o
            weighted += e*n
            c = (r+o)*q+e*(q+t)+(r*o-e)*n
            assert r*n*o-c == q*(e-r-o)
            complete += c
        answer[which] = dict(dense_baseline_products=c0, all_rows_prepared_products=prep,
                            all_rows_prepared_count_model=complete, count_model_over_dense=complete/c0,
                            eligible_outputs=eligible, outputs=outputs,
                            eligible_output_fraction=eligible/outputs,
                            product_weighted_eligibility=weighted/c0)
    return answer


def run(materials=None):
    counts = {"ring_pairs": 0, "word_updates": 0, "finite_outputs_admitted": 0,
              "finite_outputs_guard_miss": 0, "signed63_outputs": 0,
              "native_finishes": 0, "wide_finish_routes_not_verified": 0,
              "exact_zero_sentinels": 0, "abstract_finish_cases": 0,
              "zero_body_shortcut_checks": 0}
    # Literal IEEE RNE boundary answers check the rounding oracle separately.
    assert round_binary32(1, -150) == 0
    assert round_binary32(3, -150) == 2
    assert round_binary32(-1, -150) == 0x80000000
    assert round_binary32((1 << 24)-1, -150) == 0x00800000
    assert round_binary32((1 << 24)+1, -24) == ONE
    assert round_binary32((1 << 24)+3, -24) == ONE+2
    assert round_binary32((1 << 25)-1, 103) == 0x7F800000
    assert round_binary32((1 << 26)-3, 102) == 0x7F7FFFFF
    for a, b, c, d in itertools.product(range(-2, 3), repeat=4):
        assert (a+d)*(b+c)-a*b-c*d == a*c+b*d
        counts["ring_pairs"] += 1
    for z, p, neg in itertools.product([-(1 << 94), -(1 << 64), -1, 0, 1, (1 << 64)-1, 1 << 94],
                                      [0, 1, (1 << 63)-1, 1 << 63, (1 << 64)-1], [False, True]):
        assert value128(*add_signed(*words128(z), p, neg)) == z+(-p if neg else p)
        counts["word_updates"] += 1
    # No benchmark distribution: a fixed algebraic binary32 boundary alphabet.
    pool = [0, 0x80000000, 1, 0x80000001, 0x007FFFFF, 0x00800000,
            0x80800000, 0x33800000, ONE, ONE+1, 0xBF800000,
            0x40000000, 0x7F7FFFFF, 0xFF7FFFFF]
    biases = [0, 0x80000000, 1, 0x80000001, ONE, 0xBF800000, 0x7F7FFFFF]
    cases = [([x, y], [y, x], b) for x, y, b in itertools.product(pool, pool, biases)]
    cases += [([ONE], [ONE], b) for b in [0x1F000000, 0x1E800000, 0x3E000000,
                                         0x3E800000, 0x3F000000, 0x5E000000,
                                         0x5E800000, 0x7E000000, 0x7E800000]]
    cases += [([0x36000000, 0x36000000, 0x32800000], [0x35FFFFFF, 0x35FFFFFF, 0x32800000], 0),
              ([ONE, ONE], [ONE, 0xBF800000], 0x80000000),
              ([0x00800000], [0x33800000], 0),
              ([0x01400000], [0x33800000], 0),
              ([0x7F7FFFFF], [0x40000000], 0),
              ([0xFF7FFFFF], [0x40000000], 0),
              ([1, 1], [1, 1], 0), ([0x80000001, 0x80000001], [1, 1], 0)]
    for x, w, bias in cases:
        a, b = prepare(x), prepare(w)
        if not (a.valid and b.valid and a.peak+b.peak < 1 << 32):
            counts["finite_outputs_guard_miss"] += 1
            continue
        counts["finite_outputs_admitted"] += 1
        h, l = total_words(a, b)
        direct = sum(signed(decode(u), 64)*signed(decode(v), 64) for u, v in zip(a.data, b.data))
        assert value128(h, l) == direct
        if a.peak+b.peak <= SIGNED63_PEAK_SUM:
            assert total_words(a, b, "signed63") == (h, l)
            counts["signed63_outputs"] += 1
        expected = exact_linear_word(x, w, bias)
        for relu in (False, True):
            shortcut = finish_zero_body_shortcut(relu, h, l, bias)
            if shortcut is not None:
                assert act(relu, shortcut) == act(relu, expected)
                counts["zero_body_shortcut_checks"] += 1
        result, route = finish_native(a.low+b.low, h, l, bias)
        if result is None:
            counts["wide_finish_routes_not_verified"] += 1
            continue
        counts["native_finishes"] += 1
        if result == SENTINEL:
            counts["exact_zero_sentinels"] += 1
            assert expected in (0, 0x80000000)
            assert act(True, expected) == 0
        else:
            assert result == expected, (x, w, bias, result, expected, route)
    # Generic terminal boundary algebra; these are not claimed reachable rows.
    for t, pi, bw in itertools.product([-(1 << 92)+1, -1, 0, 1, (1 << 92)-1],
                                      [0, 125, 250, 506, 635, 1020],
                                      biases+[0x1F000000, 0x1E800000, 0x3E800000,
                                              0x3F000000, 0x5E000000, 0x5E800000,
                                              0x7E000000, 0x7E800000]):
        v, route = finish_native(pi, *words128(t), bw)
        exact = (t << pi)+(signed_mant(bw) << (149+idx(bw)))
        if v is not None:
            expected = round_binary32(exact, -298)
            assert (v == SENTINEL and exact == 0) or v == expected
        counts["abstract_finish_cases"] += 1
    # Previously attached counterexample: reproduced, not a new discovery.
    x = [0x36000000, 0x36000000, 0x32800000]
    w = [0x35FFFFFF, 0x35FFFFFF, 0x32800000]
    a, b = prepare(x), prepare(w)
    good = round_binary32(value128(*total_words(a, b)), a.low+b.low-298)
    bad = round_binary32(value128(*total_words(a, b, "bad_unconditionally_signed")), a.low+b.low-298)
    assert (good, bad, a.peak+b.peak) == (0x2D000100, 0xACFFFE01, 4294967168)
    assert a.peak+b.peak > SIGNED63_PEAK_SUM
    assert SIGNED63_PEAK_SUM**2 < 1 << 63 <= (SIGNED63_PEAK_SUM+1)**2
    # Cache-zero provenance is insufficient without ReLU or replay.
    minus, plus, ww = [0x80000000]*2, [0]*2, [ONE]*2
    assert prepare(minus) == prepare(plus)
    assert exact_linear_word(minus, ww, 0x80000000) == 0x80000000
    assert exact_linear_word(plus, ww, 0x80000000) == 0
    dx, dw_neg, dw_pos = [ONE, 0], [0x80000000, 0xBF800000], [0, 0xBF800000]
    assert prepare(dw_neg) == prepare(dw_pos)
    assert prepare(dx).peak > 0 and prepare(dw_neg).peak > 0
    assert exact_linear_word(dx, dw_neg, 0x80000000) == 0x80000000
    assert exact_linear_word(dx, dw_pos, 0x80000000) == 0
    # All-zero metadata is 510, because Yc uses (absWord-1) modulo 2**32.
    az, aw = prepare(plus), prepare(ww)
    assert az.low == 510 and aw.low == 125
    v, rt = finish_native(az.low+aw.low, 0, 0, ONE)
    assert v is None and rt == "wide_fallback_unverified"
    assert exact_linear_word(plus, ww, ONE) == ONE
    # Nonzero underflow-to-zero is an ordinary word, never the exact-zero sentinel.
    ua, ub = prepare([1, 1]), prepare([1, 1])
    uv, _ = finish_native(ua.low+ub.low, *total_words(ua, ub), 0)
    assert uv == 0 and value128(*total_words(ua, ub)) != 0
    # Fixed strong-sparse counterexample: verify QPS and QPa guard ingredients.
    r, n, o = 8, 20, 40
    sx, sw, sb = [ONE]+[0]*(n-1), [ONE]*n, ONE
    mx, mw = metadata(sx), metadata(sw)
    xm, wm = yk(mx >> 16), yk(mw >> 16)
    dx, dw = yk(mx & 0xFFFF)-xm, yk(mw & 0xFFFF)-wm
    assert n >= 16 and dx+dw <= 15 and 4 <= 3*n and wm >= 1
    assert xm+wm <= 126+idx(sb) < xm+wm+80
    ca, cb = prepare(sx), prepare(sw)
    assert ca.valid and cb.valid and ca.peak+cb.peak < 1 << 32
    assert exact_linear_word(sx, sw, sb) == 0x40000000
    win_products = (r+o)*(n//2)+r*o*(n//2)
    strong_sparse_products = r*o
    assert (win_products, strong_sparse_products) == (3680, 320)
    # Dispatch-only checks: no claims about missing retained nonfinite semantics.
    for special in [0x7F800000, 0xFF800000, 0x7FC00001, 0x7F800001]:
        assert wrapper_route(1, 1, 1, [special], [ONE], [0]) == "retained_whole_kernel"
        assert wrapper_route(1, 1, 1, [ONE], [ONE], [special]) == "retained_whole_kernel"
    assert wrapper_route(0, 0, 1, [], [], []) == "empty"
    assert wrapper_route(1, 0, 1, [], [], [0]) == "retained_whole_kernel"
    assert wrapper_route(1, 1 << 30, 1, [], [], []) == "retained_whole_kernel"
    assert wrapper_route(1, 2, 1, [ONE], [ONE, ONE], [0]) == "retained_whole_kernel"
    # Yc's out-of-bounds/USize sentinel cannot admit a nonzero finite row.
    assert not prepare([ONE], 0x01FF00FF).valid
    assert prepare([0], 0x01FF00FF).valid
    # Closed-form endpoint bounds, not 2**30-sized array execution.
    nn, q, peak = (1 << 30)-1, ((1 << 30)-1)//2, (1 << 32)-1
    assert q*peak*peak < 1 << 93
    assert 3*q*peak*peak+peak*peak < 1 << 95
    assert nn*((1 << 31)-1)*(1 << 31) < 1 << 92
    # Bias index conventions require changing coefficient and index together.
    for bi, low in itertools.product([0, 1, 126, 253], [0, 1, 63, 126]):
        if low <= 126+bi:
            assert ((1 << 23)*12345 << (126+bi-low)) == 12345 << (149+bi-low)
    report = {
        "status": "FINITE_EXACT_INTEGER_MODEL_PASSED",
        "lean_status": "NOT_COMPILED", "native_performance": "UNKNOWN",
        "scope": "Own deterministic algebraic/binary32 boundaries only; no current confirmation data or benchmark grid",
        "checks": counts,
        "old_signed_product_counterexample_reproduced": {"good": f"{good:08x}", "bad": f"{bad:08x}", "peak_sum": a.peak+b.peak},
        "new_strong_sparse_counterexample": {"shape": [r, n, o], "winograd_products": win_products,
            "strong_sparse_products": strong_sparse_products, "ratio": win_products/strong_sparse_products,
            "ratio_including_one_bias_product_per_output": (win_products+r*o)/(strong_sparse_products+r*o),
            "output_hex": "40000000", "bias_hex": "3f800000"},
        "zero_provenance": {"same_cache": True, "negative_output_hex": "80000000", "positive_output_hex": "00000000",
                            "also_demonstrated_with_both_peaks_nonzero": True},
        "all_zero_metadata": {"low": az.low, "weight_low": aw.low,
            "body_shift_with_bias_one": az.low+aw.low-(126+idx(ONE)), "current_finish": rt,
            "proved_zero_body_nonzero_bias_result_hex": "3f800000"},
        "environment": {"lean": shutil.which("lean"), "lake": shutil.which("lake"),
                        "note": "No toolchain installed; no compiler or timing command executed"},
        "limitations": ["Finite checking is not the universal Contract proof",
            "R27PackedLinear.finish/exactZero and retainedKernels definitions are absent",
            "YL/YD word arithmetic checked against exact integers; Ybo implementation reused abstractly, not independently proved here",
            "Wide finish routes counted but their missing Int helper is not verified",
            "Old summary counts do not contain raw arrays, bias/finish coverage, or native times",
            "Old count ratios charge self-products for every row; actual invalid prepares stop before self-products, so this is a conservative count model, not an observed native count"]}
    if materials:
        report["attached_old_summary_recount"] = audit_old_counts(materials)
    return report


if __name__ == "__main__":
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--materials", type=Path, help="Optional frozen attachment text or extracted old discriminator JSON")
    p.add_argument("--out", type=Path)
    args = p.parse_args()
    result = run(args.materials)
    result["script_sha256"] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    text = json.dumps(result, ensure_ascii=False, indent=2)+"\n"
    if args.out:
        args.out.write_text(text)
    print(text, end="")
