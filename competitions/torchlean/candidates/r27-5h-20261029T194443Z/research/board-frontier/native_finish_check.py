"""Finite replay of signed128 alignment, one's-complement bias, and correction.
No Lean or native endpoint is executed; this checks the new caller arithmetic.
"""
from datetime import datetime, timezone
import hashlib, json, random
from pathlib import Path
from norm_frontier import fields, round_ratio

U64 = (1 << 64) - 1
U192 = (1 << 192) - 1

def signed(words):
    top, high, low = words
    value = (top << 128) | (high << 64) | low
    return value - (1 << 192) if top >> 63 else value

def align(hi, lo, shift):
    top = U64 if hi >> 63 else 0
    if shift == 0:
        return top, hi, lo
    assert 0 < shift <= 63
    return (((top << shift) & U64) | (hi >> (64 - shift)),
            ((hi << shift) & U64) | (lo >> (64 - shift)),
            (lo << shift) & U64)

def add_bias(words, bias, low):
    sign, mantissa, index = fields(bias)
    shift = 126 + index - low
    assert 0 <= shift < 128
    product = (1 << 23) * mantissa
    remainder = shift & 63
    part0 = ((product << remainder) & U64) if shift < 64 else 0
    part1 = ((product >> 1) >> (63 - remainder)) if shift < 64 else ((product << remainder) & U64)
    part2 = 0 if shift < 64 else ((product >> 1) >> (63 - remainder))
    mask = U64 if sign < 0 else 0
    w2, w1, w0 = words
    z0 = (w0 + (part0 ^ mask)) & U64
    carry0 = int(z0 < w0)
    first = (w1 + (part1 ^ mask)) & U64
    carry1a = int(first < w1)
    z1 = (first + carry0) & U64
    carry1b = int(z1 < first)
    z2 = (w2 + (part2 ^ mask) + (carry1a | carry1b)) & U64
    correction = int(sign < 0)
    t0 = (z0 + correction) & U64
    t1 = (z1 + int(t0 < z0)) & U64
    t2 = (z2 + int(t1 < z1)) & U64
    return t2, t1, t0

def replay(body, product_index, bias):
    raw = body % (1 << 128)
    hi, lo = raw >> 64, raw & U64
    sign, mantissa, index = fields(bias)
    exact_low = min(product_index, index + 149)
    expected = (body << (product_index - exact_low)) + (sign * mantissa << (index + 149 - exact_low))
    expected_word = round_ratio(expected, 1, exact_low - 298)
    if mantissa == 0:
        actual = signed(align(hi, lo, 0))
        exponent = product_index - 298
        kind = 'zero_bias_native'
    else:
        low = min(product_index, 126 + index)
        body_shift = product_index - low
        bias_shift = 126 + index - low
        if body_shift > 63 or bias_shift >= 128:
            return 'fallback_gap', expected == 0
        words = add_bias(align(hi, lo, body_shift), bias, low)
        actual = signed(words)
        target = (body << body_shift) + sign * ((1 << 23) * mantissa << bias_shift)
        assert actual == target
        assert -(1 << 191) <= target < (1 << 191)
        exponent = low - 298
        kind = 'bias_native'
    if actual == 0:
        assert expected == 0
        return 'exact_zero_replay', True
    assert round_ratio(actual, 1, exponent) == expected_word
    return kind, False

def main():
    start = datetime.now(timezone.utc).isoformat()
    rng = random.Random(0x270739)
    counts = {}
    fixed_bodies = [0, 1, -1, (1 << 63) - 1, -(1 << 63), (1 << 127) - 1, -(1 << 127)]
    fixed_biases = [0, 0x80000000, 1, 0x80000001, 0x3f800000, 0xbf800000, 0x7f7fffff, 0xff7fffff]
    total = 0
    for body in fixed_bodies:
        for index in [0, 1, 62, 63, 64, 125, 126, 127, 252, 315, 316, 379, 508, 1020]:
            for bias in fixed_biases:
                kind, _ = replay(body, index, bias)
                counts[kind] = counts.get(kind, 0) + 1
                total += 1
    for _ in range(10000):
        body = rng.randrange(-(1 << 127), 1 << 127)
        bias = rng.getrandbits(32)
        if ((bias >> 23) & 255) == 255:
            bias ^= 0x00800000
        kind, _ = replay(body, rng.randrange(509), bias)
        counts[kind] = counts.get(kind, 0) + 1
        total += 1
    result = {'status': 'FINITE_CALLER_ALIGNMENT_REPLAY_ONLY', 'start_utc': start,
              'end_utc': datetime.now(timezone.utc).isoformat(),
              'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'cases': total, 'branches': counts,
              'limits': ['No Lean/native execution', 'Existing YL/YD names still need actual caller linkage',
                         'Zero result intentionally delegates original dot replay', 'No full12 proof or timing'],
              'universal_bound_argument': 'For signed128 body and bodyShift<=63, abs(bodyShifted)<=2^190; finite bias product<2^48 shifted<128 is<2^175; their sum lies strictly inside signed192.'}
    (Path(__file__).with_name('native-finish-result.json')).write_text(json.dumps(result, indent=2), encoding='utf-8')
    print(json.dumps(result))

if __name__ == '__main__':
    main()
