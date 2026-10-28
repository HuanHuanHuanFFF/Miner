"""Host reference and source-guard boundary checks; no native Lean benchmark."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import struct

HERE = Path(__file__).resolve().parent
FRONT = HERE / 'independent-frontier'

def fp(u):
    return struct.unpack('<f', struct.pack('<I', u))[0]

def bits(x):
    try:
        return struct.unpack('<I', struct.pack('<f', x))[0]
    except OverflowError:
        return (0x80000000 if x < 0 else 0) | 0x7f800000

def selected(u, v, threshold=26):
    a, b = u & 0x7fffffff, v & 0x7fffffff
    hi, high, low = (v, b, a) if a < b else (u, a, b)
    return hi if high < 0x7f800000 and high - low >= threshold << 23 else None

def main():
    cases = set()
    fractions = [0, 1, 0x3fffff, 0x7fffff]
    for high_e in (25, 26, 27, 63, 64, 126, 127, 128, 253, 254):
        for gap in (0, 1, 24, 25, 26, 27, 28, 63, 127, 253, 254):
            low_e = max(0, high_e - gap)
            for a in fractions:
                for b in fractions:
                    for su, sv in ((0, 0), (0, 1), (1, 0), (1, 1)):
                        u, v = (su << 31) | (high_e << 23) | a, (sv << 31) | (low_e << 23) | b
                        cases.add((u, v)); cases.add((v, u))
    cases |= {(0x7f7fffff, 1), (0xff7fffff, 0x80000001), (0x3f800000, 0xb3000001)}
    hits = 0
    trace = hashlib.sha256()
    for u, v in sorted(cases):
        got = selected(u, v)
        if got is None:
            continue
        want = bits(fp(u) + fp(v))
        assert got == want, (hex(u), hex(v), hex(got), hex(want))
        trace.update(struct.pack('<III', u, v, got)); hits += 1
    rejected = [(0, 0x80000000), (0x80000000, 0x80000000),
                (0x7f800000, 1), (0xff800000, 0x00800000),
                (0x7f800001, 1), (0x7fc00001, 0x00800000)]
    assert all(selected(u, v) is None for u, v in rejected)
    # Raw-distance25 and exponent-gap25 are different predicates. Test24 only
    # as an incorrect weaker guard; keep the requested26 frozen.
    u, v = 0x3f800001, 0x33800001
    wrong, want = selected(u, v, 24), bits(fp(u) + fp(v))
    assert wrong is not None and wrong != want
    sign_u, sign_v = 0xbf800000, 0x00800000
    correct_sign = selected(sign_u, sign_v)
    assert correct_sign == 0xbf800000 and (correct_sign & 0x7fffffff) != bits(fp(sign_u) + fp(sign_v))
    kernel = FRONT / 'Kernel-far-only-add-probe.lean'
    base = next(p for p in HERE.parents if p.name == 'candidates') / 'f01-r15-dev-packed-b2-1/Kernel.lean'
    assert kernel.read_bytes().startswith(base.read_bytes())
    assert hashlib.sha256(kernel.read_bytes()).hexdigest() == 'c809dc3cfd97d7088b0259348fdef4b422ed3560a4849b9a6720ae884db59850'
    result = {'verified_utc': datetime.now(timezone.utc).isoformat(), 'cases': len(cases), 'guard_hits': hits,
              'hit_differences': 0, 'reference': 'Binary64 sum of binary32 inputs followed by binary32 RNE packing',
              'trace_sha256': trace.hexdigest(), 'kernel_sha256': hashlib.sha256(kernel.read_bytes()).hexdigest(),
              'runtime_sha256': hashlib.sha256((FRONT / 'Runtime-far-only-add.lean.inc').read_bytes()).hexdigest(),
              'exact_B2_prefix': True, 'exceptional_and_signed_zero_guard_rejections': True,
              'raw_threshold24_counterexample': {'u': hex(u), 'v': hex(v), 'wrong': hex(wrong), 'correct': hex(want)},
              'negative_result_sign_checked': True, 'Lean': 'NOT_RUN', 'performance': 'UNKNOWN',
              'scope': 'Finite directed guard hits and source fallback only. No all-input proof or current/private prevalence claim.'}
    (HERE / 'far-only-add-independent-review.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result, indent=2))

if __name__ == '__main__':
    main()
