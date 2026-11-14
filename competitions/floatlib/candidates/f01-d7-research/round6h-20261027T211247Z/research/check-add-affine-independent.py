"""Independent same-exponent check via exact binary64 sum then binary32 pack.

For two finite binary32 inputs of the same exponent the exact 25-bit integer
sum fits binary64. This is finite corroboration, not the all-input Lean bridge.
"""
import struct
import random
import json
from pathlib import Path
from datetime import datetime, timezone

def f32(u):
    return struct.unpack('<f', struct.pack('<I', u))[0]

def bits(x):
    try:
        return struct.unpack('<I', struct.pack('<f', x))[0]
    except OverflowError:
        return (0x80000000 if x < 0 else 0) | 0x7f800000

def proposed(u, v):
    e = (u >> 23) & 255
    assert (u ^ v) < (1 << 23) and e != 255
    sign = u & 0x80000000
    f = (u & 0x7fffff) + (v & 0x7fffff)
    if e == 0:
        return sign | f
    if e == 254:
        return sign | 0x7f800000
    t = f >> 1
    return sign | ((e + 1) << 23) | (t + ((f & 1) & (t & 1)))

def main():
    rng = random.Random(2220321)
    fractions = [0, 1, 2, 3, 0x3fffff, 0x400000, 0x7ffffd, 0x7ffffe, 0x7fffff]
    cases = [(s | (e << 23) | a, s | (e << 23) | b)
             for s in (0, 0x80000000) for e in (0, 1, 2, 126, 127, 128, 252, 253, 254)
             for a in fractions for b in fractions]
    cases += [(s | (e << 23) | rng.getrandbits(23), s | (e << 23) | rng.getrandbits(23))
              for s in (0, 0x80000000) for e in range(255)]
    failures = []
    for u, v in cases:
        observed = bits(f32(u) + f32(v))
        actual = proposed(u, v)
        if actual != observed:
            failures.append({'u': hex(u), 'v': hex(v), 'actual': hex(actual), 'host': hex(observed)})
    # Detect incorrect RNE tie handling and conflation of subnormal/normal bands.
    witnesses = []
    for u, v in [(0x00800000, 0x00800001), (0x00800001, 0x00800002),
                 (1, 1), (0x7f000000, 0x7f000000), (0x80000000, 0x80000000)]:
        witnesses.append({'u': hex(u), 'v': hex(v), 'output': hex(proposed(u, v)),
                          'host': hex(bits(f32(u) + f32(v)))})
    result = {'utc': datetime.now(timezone.utc).isoformat(), 'cases': len(cases),
              'differences': failures, 'boundary_witnesses': witnesses,
              'reference': 'binary64 exact finite same-exponent sum, binary32 RNE packing',
              'scope': 'Same sign and exponent, E 0..254 only; E255 NaN payload excluded',
              'Lean': 'NOT_RUN', 'performance': 'UNKNOWN'}
    Path(__file__).with_name('add-affine-independent-review.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result, indent=2))
    assert not failures

if __name__ == '__main__':
    main()
