"""Bounded exact-dyadic cross-check of proposed LowScale guards; no Lean/timing."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import time

HERE = Path(__file__).resolve().parent
START = time.perf_counter()

def rne(n, shift):
    if shift <= 0:
        return n << -shift
    q, r = divmod(n, 1 << shift)
    half = 1 << (shift - 1)
    return q + (r > half or (r == half and q % 2 == 1))

def quantize(sign, product, scale):
    signword = int(sign) << 31
    if product == 0:
        return signword
    h = product.bit_length() - 1
    exponent = h + scale - 298
    if exponent < -126:
        fraction = rne(product, 149 - scale)
        assert fraction <= 1 << 23
        return signword | fraction
    mantissa = rne(product, h - 23)
    if mantissa == 1 << 24:
        mantissa >>= 1
        exponent += 1
    if exponent > 127:
        return signword | 0x7F800000
    return signword | ((exponent + 127) << 23) | (mantissa - (1 << 23))

def low(sign, product, scale):
    fraction = rne(product, 149 - scale)
    if fraction in (0, 1 << 23):
        return (int(sign) << 31) | fraction
    return (int(sign) << 31) | (fraction & 0x7FFFFF)

checks = []
for scale in (124, 125, 126):
    bound = 1 << (172 - scale)
    shift = 149 - scale
    values = {0, 1, (1 << 64) - 1}
    for k in range(65):
        for d in (-1, 0, 1):
            values.add((1 << k) + d)
    for q in (0, 1, (1 << 22) - 1, (1 << 23) - 1, 1 << 23, (1 << 23) + 1):
        for r in (0, 1, (1 << (shift - 1)) - 1, 1 << (shift - 1), (1 << (shift - 1)) + 1, (1 << shift) - 1):
            values.add((q << shift) + r)
    eligible = [v for v in sorted(values) if 0 <= v < min(bound, 1 << 64)]
    for product in eligible:
        assert time.perf_counter() - START < 4.4
        for sign in (False, True):
            assert low(sign, product, scale) == quantize(sign, product, scale)
    checks.append({'scale': scale, 'strict_product_bound_bits': 172 - scale,
                   'literal_rse_shift': shift, 'checks': 2 * len(eligible)})

counterexamples = []
for scale, product, note in [
    (125, (1 << 47) + (1 << 24), 'arbitrary UInt64: cannot widen48-bit bound to scale125'),
    (125, ((1 << 23) + 2) * ((1 << 24) - 1), 'valid normal mantissas; raw exponent sum127'),
    (126, ((1 << 22) + 2) * ((1 << 24) - 1), 'valid subnormal/normal mantissas; exponents0 and127'),
]:
    expected, incorrect = quantize(False, product, scale), low(False, product, scale)
    assert expected != incorrect
    counterexamples.append({'scale': scale, 'product': product,
                            'correct': hex(expected), 'incorrect_unconditional_low': hex(incorrect), 'note': note})

report = {'state': 'PASS_FINITE_EXACT_MODEL_NOT_LEAN',
          'created_at_utc': datetime.now(timezone.utc).isoformat(),
          'universal_paper_condition': 'For nonzero product<2^B, leading<=B-1. B+scale<=172 yields leading+scale<=171. scale<149; source UInt64 addition cannot wrap below172.',
          'guards': checks, 'counterexamples': counterexamples,
          'elapsed_seconds': time.perf_counter() - START,
          'external_timeout_ms': 5000,
          'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
          'scope': 'Existing exposed mathematical boundary cases. Independent exact-dyadic encoding compared to low-round branch. Not universal Lean acceptance, CPU timing, candidate performance or formal admission.'}
(HERE / 'astra-tight-rse-boundaries.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
print(json.dumps(report))
