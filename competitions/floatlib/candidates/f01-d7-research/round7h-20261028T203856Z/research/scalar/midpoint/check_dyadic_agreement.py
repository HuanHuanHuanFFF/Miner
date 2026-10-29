"""New finite model of both actual native32 rounder branch structures.

No Lean or compiler is executed. This is deterministic boundary evidence,
not the acceptance of the source theorem or the old competition gate.
"""
from pathlib import Path
from fractions import Fraction as F
from datetime import datetime, timezone
from collections import Counter
import hashlib
import json
import importlib.util

HERE = Path(__file__).resolve().parent
ROOT = Path(__file__).resolve().parents[8]
spec = importlib.util.spec_from_file_location('normal_cell_boundary_model', HERE / 'check_normal_cell.py')
boundary = importlib.util.module_from_spec(spec)
spec.loader.exec_module(boundary)

def rne(x):
    q, r = divmod(x.numerator, x.denominator)
    return q if 2 * r < x.denominator else q + 1 if x.denominator < 2 * r else q + (q % 2)

def shifted(num, shift):
    return rne(F(num) * boundary.p2(shift))

def dyadic(sign, num, exponent, counts):
    s = sign << 31
    if num == 0:
        counts['dyadic_signed_zero'] += 1
        return s
    leading = num.bit_length() - 1
    total = leading + exponent
    if total < -126:
        fraction = shifted(num, exponent + 149)
        counts['dyadic_subnormal_branch'] += 1
        if fraction == 0:
            counts['dyadic_underflow_zero'] += 1
            return s
        if fraction == 1 << 23:
            counts['dyadic_subnormal_to_minnormal'] += 1
            return s | (1 << 23)
        assert fraction < 1 << 23
        return s | fraction
    mantissa = shifted(num, 23 - leading)
    carry = mantissa == 1 << 24
    total += int(carry)
    if total > 127:
        counts['dyadic_overflow'] += 1
        return s | 0x7f800000
    counts['dyadic_normal_carry' if carry else 'dyadic_normal'] += 1
    if carry:
        mantissa = 1 << 23
    return s | ((total + 127) << 23) | (mantissa - (1 << 23))

def rational(sign, num, exponent, counts):
    s = sign << 31
    if num == 0:
        return s
    leading = num.bit_length() - 1
    total = leading + exponent
    if total > 127:
        counts['rational_early_overflow'] += 1
        return s | 0x7f800000
    if total < -150:
        counts['rational_early_underflow'] += 1
        return s
    if total < -126:
        fraction = shifted(num, exponent + 149)
        if fraction == 0:
            return s
        return s | ((1 << 23) if fraction >= 1 << 23 else fraction)
    mantissa = shifted(num, 23 - leading)
    carry = mantissa == 1 << 24
    total += int(carry)
    if total > 127:
        counts['rational_carry_overflow'] += 1
        return s | 0x7f800000
    if carry:
        mantissa = 1 << 23
    return s | ((total + 127) << 23) | (mantissa - (1 << 23))

def main():
    cases = set()
    numbers = [0, 1, 2, 3, 7, (1 << 23) - 1, 1 << 23, (1 << 23) + 1,
               (1 << 24) - 1, (1 << 24) + 1, (1 << 25) - 1,
               (1 << 49) + 1, (1 << 127) - 1, 1 << 128, (1 << 300) - 1]
    exponents = [-1000, -500, -300, -151, -150, -149, -127, -126, -125,
                 -24, -23, -1, 0, 1, 23, 100, 127, 128, 1000]
    for n in numbers:
        for e in exponents:
            for s in [0, 1]:
                cases.add((s, n, e))
    # Explicit lower/upper ties and carried transition to normal/overflow.
    for n, e in [((1 << 24) - 1, -150), ((1 << 24) + 1, -150),
                 ((1 << 25) - 1, 103), ((1 << 26) - 3, 102),
                 ((1 << 25) - 1, -24)]:
        for s in [0, 1]:
            cases.add((s, n, e))
    counts, trace = Counter(), hashlib.sha256()
    for s, n, e in sorted(cases):
        d = dyadic(s, n, e, counts)
        r = rational(s, n, e, counts)
        exact = F(n) * boundary.p2(e)
        want = (s << 31) if n == 0 else boundary.oracle(-exact if s else exact)
        assert d == r == want, (s, n, e, hex(d), hex(r), hex(want))
        trace.update(d.to_bytes(4, 'little'))
    required = ['dyadic_signed_zero', 'dyadic_subnormal_branch', 'dyadic_underflow_zero',
                'dyadic_subnormal_to_minnormal', 'dyadic_overflow', 'dyadic_normal_carry',
                'rational_early_overflow', 'rational_early_underflow', 'rational_carry_overflow']
    assert all(counts[k] > 0 for k in required), counts
    sources = []
    for name in ['DyadicAgreement.lean.inc', 'DyadicCell.lean.inc', 'NormalCell.lean.inc']:
        p = HERE / name
        b = p.read_bytes()
        sources.append({'path': str(p.relative_to(ROOT)).replace('\\', '/'), 'bytes': len(b),
                        'sha256': hashlib.sha256(b).hexdigest()})
    result = {'observed_at_utc': datetime.now(timezone.utc).isoformat(),
              'status': 'FINITE_EXACT_BRANCH_MODEL_PASS_NOT_LEAN', 'cases': len(cases),
              'branch_counts': dict(counts), 'differences': 0, 'trace_sha256': trace.hexdigest(),
              'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'oracle_module_sha256': hashlib.sha256((HERE / 'check_normal_cell.py').read_bytes()).hexdigest(),
              'sources': sources,
              'roots': ['Submission.R24DyadicAgreement.roundDyadic_eq_roundRatScaled',
                        'Submission.R24DyadicCell.native32_dyadic_raw_strict'],
              'verification': {'Lean': 'NOT_RUN', 'replay': 'NOT_RUN', 'axioms': 'NOT_RUN', 'performance': 'NOT_RUN'},
              'scope': 'New branch-level finite model; includes both signs, signed zeros, subnormal/minnormal, normal carry, early overflow/underflow, overflow tie. No general proof acceptance.'}
    (HERE / 'dyadic-model-receipt.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(json.dumps({'status': result['status'], 'cases': len(cases), 'branches': dict(counts), 'sources': sources[:2]}))

if __name__ == '__main__':
    main()
