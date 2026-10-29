"""Bounded exact midpoint/source-cost review; no Lean execution or timing."""
from fractions import Fraction
from pathlib import Path
import hashlib
import importlib.util
import json
import math
import re
import struct

HERE = Path(__file__).resolve().parent
ROUND = HERE.parent.parent
FP = ROUND / 'development-scalar/PortableF64Dot.lean.inc'
ADAPTER = ROUND / 'development-dot-cost/Adapters.lean.inc'
spec = importlib.util.spec_from_file_location('r24_review_oracle', HERE.parent / 'exact_dot_baseline_model.py')
oracle = importlib.util.module_from_spec(spec)
spec.loader.exec_module(oracle)
sha = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()


def f64_value(bits):
    exponent, fraction = (bits >> 52) & 2047, bits & ((1 << 52) - 1)
    assert exponent != 2047
    mantissa = fraction if exponent == 0 else fraction | (1 << 52)
    return (-mantissa if bits >> 63 else mantissa) * oracle.p2((1 if exponent == 0 else exponent) - 1075)


def bits(value):
    return struct.unpack('<Q', struct.pack('<d', value))[0]


def order_key(word):
    return word ^ ((1 << 63) if word >> 63 == 0 else (1 << 64) - 1)


def proposed(word):
    magnitude = (((((word & ((1 << 63) - 1)) + 0x10000000) & ((1 << 64) - 1)) >> 29) & 0xffffffff)
    magnitude = (magnitude - 0xc0000000) & 0x7fffffff
    return ((word >> 32) & 0x80000000) | magnitude


def certified(total, radius, guess, bad_uniform_lower=False):
    magnitude = guess & 0x7fffffff
    e = magnitude >> 23
    if e in (0, 255):
        return False
    base = ((e + 896) << 52) | ((magnitude & 0x7fffff) << 29)
    delta = 0x20000000 if magnitude == 0x00800000 or bad_uniform_lower else 0x10000000
    lower, upper = base - delta, base + 0x10000000
    if guess >> 31:
        lower, upper = upper | (1 << 63), lower | (1 << 63)
    return order_key(lower) < order_key(bits(total - radius)) and order_key(bits(total + radius)) < order_key(upper)


def main():
    assert sha(FP) == 'dd775683cade6e575dc6f0684f9216742e1c772c3cf7460b0c53c54e4e3eff04'
    assert sha(ADAPTER) == '4ac3cf62b0a66bcc82acec505e2ee9dc54eb1d507dfd424cb33777cf83e337cf'
    checked = 0
    for e in range(1, 255):
        for fraction in (0, 1, 0x3fffff, 0x7ffffe, 0x7fffff):
            word = (e << 23) | fraction
            actual = oracle.value(word)
            previous = oracle.value(word - 1)
            following = oracle.p2(128) if word == 0x7f7fffff else oracle.value(word + 1)
            lo, hi = (previous + actual) / 2, (actual + following) / 2
            base = ((e + 896) << 52) | (fraction << 29)
            below = base - (0x20000000 if word == 0x00800000 else 0x10000000)
            above = base + 0x10000000
            assert f64_value(below) == lo and f64_value(above) == hi
            assert f64_value(above | (1 << 63)) == -hi
            assert f64_value(below | (1 << 63)) == -lo
            checked += 2
    one = 0x3f800000
    x = [one, ((-25 + 127) << 23) | 0x80000000, ((-100 + 127) << 23) | 0x80000000]
    y = [one] * 3
    total = 0.0
    for a, b in zip(x, y):
        total = total + float(oracle.value(a)) * float(oracle.value(b))
    H, L = 252, 2
    radius = math.ldexp(1.0, H + 2 * L - 303)
    guess = proposed(bits(total))
    expected, _ = oracle.oracle(x, y)
    assert guess == one and expected == one - 1
    assert not certified(total, radius, guess)
    assert certified(total, radius, guess, bad_uniform_lower=True)
    source = FP.read_text(encoding='utf-8')
    forbidden = re.findall(r'Float32\.toFloat|Float\.toFloat32|Float\.scaleB|\bunsafe\b|\bextern\b', source)
    assert not forbidden
    adapters = ADAPTER.read_text(encoding='utf-8')
    assert 'def eagerPrepared (a b : EagerOperand)' in adapters
    assert 'prepareEagerOperand a' in adapters and 'prepareEagerOperand b' in adapters
    assert adapters.count('R24ExactDotTiered.fullv2') == 3
    assert adapters.count('R24ExactDotTiered.prepared2v2') == 2
    report = {'scope': 'One independent exact/source cost review, not Lean proof, selected C/ASM or timing.',
              'sources': {'fp_sha256': sha(FP), 'adapter_sha256': sha(ADAPTER), 'review_script_sha256': sha(Path(__file__))},
              'exact_signed_midpoint_field_cases': checked,
              'whole_dot_wrong_lower_mutant': {'x': x, 'y': y, 'H': H, 'L': L,
                                               'radius_exponent': H + 2 * L - 303,
                                               'guess': guess, 'exact_expected': expected,
                                               'current_rejects': True, 'incorrect_uniform_half_lower_accepts': True},
              'radius_bound': {'n_cap': 1 << 30, 'L_max': 30, 'H_max': 506,
                               'radius_biased_exp_range': [720, 1286],
                               'paper_error_bound': '2^(H+2L-304), source radius2^(H+2L-303) conservative'},
              'step_count': 'All n products/adds included, no hidden bias seed; zero terms retained in n.',
              'no_opaque_cross_width_cast_found_in_body': True,
              'per_operand_preparation_no_prepaid_paired_scan': True,
              'fallbacks': 'All miss branches use best64/128 full orprepared2v2; cold lazy charges integer prep onmiss, eagercold charges bothcachetypes always.',
              'adapter_finding': 'Unary precombined eager v1 repaired to2independent EagerOperands before freeze; latest hash reviewed.',
              'remaining_blocker_from_bounded_review': None,
              'pending': ['Actual typing/numerical validation', 'Uniform barrier and selected caller C/ASM', 'Actual cache drop placement and bounded cold/prepared times'],
              'no_correctness_or_official_score_claim': True}
    (HERE / 'fp64-cost-critical-review.json').write_bytes((json.dumps(report, indent=2) + '\n').encode())
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
