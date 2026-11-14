"""Independent integer rounding/carry screen for D's fixed word-MUL proposal."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random
import struct

HERE = Path(__file__).resolve().parent


def old_core(p, total, sign):
    biased = p + ((1 << 22) - 1 if p < 1 << 47 else (1 << 23) - 1)
    biased += (p >> (23 if p < 1 << 47 else 24)) & 1
    high = biased >> 47
    q = biased >> (23 + high)
    return sign | ((total - 127 + high) << 23) | (q - (1 << 23))


def proposed(p, total, sign, wrong_or=False):
    h = p >> 47
    biased = p + ((1 << 22) - 1 if h == 0 else (1 << 23) - 1)
    biased += (p >> (23 + h)) & 1
    q = biased >> (23 + h)
    base = (total - 128 + h) << 23
    return sign | ((base | q) if wrong_or else base + q)


def oracle(p, total, sign):
    # General exact-integer RNE; does not use the proposed bias or implicit-bit packing.
    lead = p.bit_length() - 1
    shift = lead - 23
    q, remainder = divmod(p, 1 << shift)
    half = 1 << (shift - 1)
    q += remainder > half or remainder == half and q & 1
    if q == 1 << 24:
        q >>= 1
        lead += 1
    exponent = lead + total - 300 + 127
    assert 1 <= exponent <= 254 and 1 << 23 <= q < 1 << 24
    return sign | (exponent << 23) | (q - (1 << 23))


if __name__ == '__main__':
    upper = ((1 << 24) - 1) ** 2
    rng = random.Random(220027)
    products = {1 << 46, upper}
    for center in (1 << 46, (1 << 47) - (1 << 22), 1 << 47,
                   (1 << 47) + (1 << 23), upper):
        products.update(p for p in range(center - 32, center + 33) if 1 << 46 <= p <= upper)
    products.update(rng.randrange(1 << 46, upper + 1) for _ in range(30000))
    products.add(((1 << 23) + 1) * ((1 << 24) - 2))
    trace = hashlib.sha256()
    checked = 0
    for p in sorted(products):
        for total in (128, 129, 130, 253, 254, 379, 380):
            for sign in (0, 0x80000000):
                result = proposed(p, total, sign)
                assert result == old_core(p, total, sign) == oracle(p, total, sign)
                assert result <= 0xffffffff
                trace.update(struct.pack('<QIII', p, total, sign, result))
                checked += 1
    witnesses = []
    for a, b, total in (((1 << 23) + 1, (1 << 24) - 2, 130), (1 << 23, 1 << 23, 129)):
        p = a * b
        expected, wrong = oracle(p, total, 0), proposed(p, total, 0, True)
        assert expected != wrong
        witnesses.append({'mantissa_a': a, 'mantissa_b': b, 'S': total, 'P': p,
                          'initial_h': p >> 47, 'correct': hex(expected), 'wrong_OR_pack': hex(wrong)})
    out = {'utc': datetime.now(timezone.utc).isoformat(), 'state': 'FINITE_INDEPENDENT_INTEGER_ORACLE_PASS',
           'cases': checked, 'differences': 0, 'trace_sha256': trace.hexdigest(),
           'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
           'mutations_detected': witnesses,
           'universal_paper_argument': 'wordcarry-independent-proof.md',
           'limits': 'Arbitrary P samples inside the mathematical product bounds plus directed carries. Universal proof argument is paper only; Lean elaboration, exact new caller, full cost and public acceptance NOT_RUN. No Kernel created or old proof accepted by inference.'}
    (HERE / 'wordcarry-independent-review.json').write_text(json.dumps(out, indent=2) + '\n')
    print(json.dumps({'cases': checked, 'differences': 0, 'mutations_detected': witnesses}))
