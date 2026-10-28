"""Independent binary32 host reference for the direct combined-scale probe."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import struct

HERE = Path(__file__).resolve().parent
PART = HERE / 'native-product-scale'

def fp(u):
    return struct.unpack('<f', struct.pack('<I', u))[0]

def bits(x):
    try:
        return struct.unpack('<I', struct.pack('<f', x))[0]
    except OverflowError:
        return (0x80000000 if x < 0 else 0) | 0x7f800000

def proposed(u, v, mutation=None):
    s = ((u >> 23) & 255) + ((v >> 23) & 255)
    p = ((u & 0x7fffff) | 0x800000) * ((v & 0x7fffff) | 0x800000)
    first = fp(bits(float(p)))
    if mutation == 'truncate_product':
        shift = max(0, p.bit_length() - 24)
        first = float((p >> shift) << shift)
    sign = (u ^ v) & 0x80000000
    if mutation == 'OR_input_signs':
        sign = (u | v) & 0x80000000
    scale_word = ((s - (172 if mutation == 'double_scale' else 173)) << 23) | sign
    return bits(first * fp(scale_word))

def main():
    pairs = [(0x800000, 0x800000), (0x800000, 0x800001), (0x800001, 0xfffffe),
             (0xffffff, 0xffffff), (0x800800, 0x800800), (0x800800, 0x801800),
             (0xc00800, 0xc01000), (0xc01800, 0xc03000)]
    count = 0
    trace = hashlib.sha256()
    for total in range(174, 381):
        for eu in sorted({max(1, total - 254), total // 2, min(254, total - 1)}):
            ev = total - eu
            if not (1 <= eu <= 254 and 1 <= ev <= 254):
                continue
            for a, b in pairs:
                for su, sv in ((0, 0), (0, 1), (1, 0), (1, 1)):
                    u, v = (su << 31) | (eu << 23) | (a - 0x800000), (sv << 31) | (ev << 23) | (b - 0x800000)
                    actual = proposed(u, v)
                    reference = bits(fp(u) * fp(v))
                    assert actual == reference, (hex(u), hex(v), hex(actual), hex(reference))
                    assert 0 < ((actual >> 23) & 255) < 255
                    trace.update(struct.pack('<III', u, v, actual))
                    count += 1
    witnesses = []
    for kind, u, v in [('double_scale', 87 << 23, 87 << 23),
                       ('OR_input_signs', 0x80000000 | (87 << 23), 0x80000000 | (87 << 23)),
                       ('truncate_product', (87 << 23) | 1, (87 << 23) | 0x7ffffe)]:
        expected, wrong = bits(fp(u) * fp(v)), proposed(u, v, kind)
        assert expected != wrong
        witnesses.append({'kind': kind, 'u': hex(u), 'v': hex(v), 'reference': hex(expected), 'mutant': hex(wrong)})
    kernel = PART / 'Kernel-probe1.lean'
    base = next(p for p in HERE.parents if p.name == 'candidates') / 'f01-r15-dev-packed-b2-1/Kernel.lean'
    assert kernel.read_bytes().startswith(base.read_bytes())
    assert hashlib.sha256(kernel.read_bytes()).hexdigest() == '92ff7182e76609c72a3f2a77a326e2fee86e70aad1c24fa4247e590e74b20f31'
    result = {'verified_utc': datetime.now(timezone.utc).isoformat(), 'cases': count, 'differences': 0,
              'reference': 'Host binary64 exact product of two binary32 inputs then binary32 RNE packing',
              'candidate_model': 'Exact48bit UInt64 product rounded to32 then multiplied by signed exact normal power2',
              'runtime_sha256': hashlib.sha256((PART / 'Runtime.lean.inc').read_bytes()).hexdigest(),
              'kernel_sha256': hashlib.sha256(kernel.read_bytes()).hexdigest(), 'base_exact_prefix': True,
              'trace_sha256': trace.hexdigest(), 'mutations_detected': witnesses,
              'Lean': 'NOT_RUN', 'performance': 'UNKNOWN', 'public_MUL_spec': 'MISSING',
              'scope': 'Finite directed normal-input cases across every admitted exponent sum; no all-input or timing claim'}
    (HERE / 'native-product-scale-independent-review.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result, indent=2))

if __name__ == '__main__':
    main()
