"""Finite exact boundary evidence for the new signed real-cell wrapper only.

The independent oracle searches raw positive binary32 neighbors and handles
overflow separately. No Lean, compiler, native floating arithmetic, random
sampling, benchmark, or existing checker revalidation is performed.
"""
from pathlib import Path
from fractions import Fraction as F
from datetime import datetime, timezone
from functools import lru_cache
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = Path(__file__).resolve().parents[8]
ROUND = HERE.parents[2]

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def p2(k):
    return F(1 << k) if k >= 0 else F(1, 1 << -k)

@lru_cache(maxsize=4096)
def value(raw):
    e, f = raw >> 23, raw & 0x7fffff
    return (f if e == 0 else (1 << 23) + f) * p2(-149 if e == 0 else e - 150)

def boundaries(q):
    sign = q >> 31
    e, f = (q >> 23) & 255, q & 0x7fffff
    m, quantum = (1 << 23) + f, p2(e - 150)
    lower = (m - (F(1, 4) if f == 0 and e > 1 else F(1, 2))) * quantum
    upper = (m + F(1, 2)) * quantum
    return (-upper, -lower) if sign else (lower, upper)

def oracle(s):
    sign, a = int(s < 0), abs(s)
    top = value(0x7f7fffff)
    overflow_midpoint = (top + p2(128)) / 2
    if a >= overflow_midpoint:
        return (sign << 31) | 0x7f800000
    if a >= top:
        return (sign << 31) | 0x7f7fffff
    lo, hi = 0, 0x7f7fffff
    while lo <= hi:
        mid = (lo + hi) // 2
        if value(mid) <= a:
            lo = mid + 1
        else:
            hi = mid - 1
    low, high = hi, hi + 1
    dl, dh = a - value(low), value(high) - a
    raw = low if dl < dh else high if dh < dl else low if low % 2 == 0 else high
    return (sign << 31) | raw

def main():
    count = rejected_ties = rejected_signs = max_den_bits = 0
    trace = hashlib.sha256()
    for e in [1, 2, 127, 253, 254]:
        for f in [0, 1, (1 << 23) - 2, (1 << 23) - 1]:
            for sign in [0, 1]:
                q = (sign << 31) | (e << 23) | f
                lower, upper = boundaries(q)
                for alpha in [F(1, 4), F(1, 2), F(3, 4)]:
                    s = lower + alpha * (upper - lower)
                    assert lower < s < upper
                    assert oracle(s) == q, (hex(q), s, hex(oracle(s)))
                    assert not lower < -s < upper
                    rejected_signs += 1
                    for source in [-600, 0, 600]:
                        rational = abs(s) / p2(source)
                        n, d = rational.numerator, rational.denominator
                        represented = (-1 if sign else 1) * F(n, d) * p2(source)
                        assert represented == s and d > 0
                        max_den_bits = max(max_den_bits, d.bit_length())
                        count += 1
                        trace.update(q.to_bytes(4, 'little'))
                for tie in [lower, upper]:
                    assert not lower < tie < upper
                    rejected_ties += 1
                assert not lower < 0 < upper

    top = value(0x7f7fffff)
    above_top = top + p2(104) / 4
    assert above_top > top and oracle(above_top) == 0x7f7fffff
    assert boundaries(0x7f7fffff)[0] < above_top < boundaries(0x7f7fffff)[1]
    assert oracle(-above_top) == 0xff7fffff
    max_witness = {
        'positive_target': '0x7f7fffff', 'negative_target': '0xff7fffff',
        'exact_magnitude': str(above_top), 'largest_finite_magnitude': str(top),
        'strict_cell_accepts_above_maxfinite': True,
        'abs_le_maxfinite_sufficient_guard_would_reject': True,
        'upper_tie_rounds_to_infinity': hex(oracle(boundaries(0x7f7fffff)[1]))
    }
    dependencies = [
        ROUND / 'development-broad/CellPrimitive-v2.lean.inc',
        HERE / 'PowerCell-v3.lean.inc',
        ROUND / 'development-broad/ScaledCell.lean.inc',
        ROUND / 'development-scalar/quotient-boundary/RescaleNative32.lean.inc'
    ]
    source = HERE / 'NormalCell.lean.inc'
    result = {
        'at_utc': datetime.now(timezone.utc).isoformat(),
        'status': 'FINITE_EXACT_FRACTION_BOUNDARIES_PASS_NOT_LEAN',
        'strict_inputs_with_exact_source_representation': count,
        'rejected_exact_midpoints': rejected_ties,
        'rejected_opposite_signs': rejected_signs,
        'zero_rejected_for_all_selected_normal_targets': True,
        'max_logical_denominator_bits': max_den_bits,
        'maxfinite_witness': max_witness,
        'trace_sha256': trace.hexdigest(),
        'script_sha256': sha(Path(__file__)),
        'source': {'path': str(source.relative_to(ROOT)).replace('\\', '/'), 'bytes': source.stat().st_size, 'sha256': sha(source)},
        'dependencies': [{'path': str(p.relative_to(ROOT)).replace('\\', '/'), 'bytes': p.stat().st_size, 'sha256': sha(p)} for p in dependencies],
        'roots': ['Submission.R24NormalCell.native32_field_strict', 'Submission.R24NormalCell.native32_raw_strict'],
        'verification': {'Lean': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN', 'performance': 'NOT_RUN'},
        'explicit_remaining_bridge': 'NativeBinary32.roundDyadic at arbitrary exponent is not equated to denominator-one roundRatScaled by this fragment.',
        'scope': 'Old ContractTensor mathematical component; all normal q fields 1..254, strict ties rejected, both signs. No source publication, CI, candidate runtime, or adoption.'
    }
    (HERE / 'normal-cell-model-receipt.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({k: result[k] for k in ['status', 'strict_inputs_with_exact_source_representation', 'max_logical_denominator_bits', 'source']}))

if __name__ == '__main__':
    main()
