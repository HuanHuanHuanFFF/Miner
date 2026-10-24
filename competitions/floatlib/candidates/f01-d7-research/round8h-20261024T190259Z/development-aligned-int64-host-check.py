"""Bounded signed64 aligned-add model, independent exact host reference."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random
import struct
import sys
import time

OUT = Path(__file__).resolve().parent
M, U32, U64 = 1 << 23, (1 << 32) - 1, (1 << 64) - 1
assert sys.float_info.radix == 2 and sys.float_info.mant_dig == 53


def value(w):
    return struct.unpack('<f', struct.pack('<I', w))[0]


def bits(x):
    try:
        return struct.unpack('<I', struct.pack('<f', x))[0]
    except OverflowError:
        return 0xff800000 if x < 0 else 0x7f800000


def prototype(a, b):
    ex, ey = (a >> 23) & 255, (b >> 23) & 255
    small = min(ex, ey)
    ma, mb = (a & (M - 1)) | M, (b & (M - 1)) | M
    amask, bmask = (-(a >> 31)) & U64, (-(b >> 31)) & U64
    wa, wb = ((ma ^ amask) - amask) & U64, ((mb ^ bmask) - bmask) & U64
    word = ((wa << (ex - small)) + (wb << (ey - small))) & U64
    signed = word - (1 << 64) if word >> 63 else word
    mathematical = ((-ma if a >> 31 else ma) << (ex - small)) + ((-mb if b >> 31 else mb) << (ey - small))
    assert signed == mathematical and abs(signed) < (1 << 50)
    if not signed:
        return 0, True, 0, None
    mid = bits(float(signed))
    final_exp = ((mid >> 23) & 255) + small - 150
    word_guard = ((((mid >> 23) & 255) + small - 151) & U32) < 254
    assert word_guard == (1 <= final_exp <= 254)
    shifted = (mid + (((small - 150) & U32) << 23)) & U32
    return shifted, word_guard, signed, final_exp


started = time.perf_counter()
trace = hashlib.sha256()
counts = dict(cases=0, accepted_normal=0, accepted_cancel=0, fallback_subnormal=0, fallback_overflow=0, negative=0, gap_over7=0)


def check(ex, ey, ma, mb, sa, sb):
    a, b = (sa << 31) | (ex << 23) | (ma - M), (sb << 31) | (ey << 23) | (mb - M)
    assert 1 <= ex <= 254 and 1 <= ey <= 254 and abs(ex - ey) <= 25
    got, accept, signed, final_exp = prototype(a, b)
    # At most50 significant aligned bits. Binary64 addition is exact, then
    # struct.pack supplies a single independent final binary32 rounding.
    expected = bits(value(a) + value(b))
    if accept:
        assert got == expected, (hex(a), hex(b), hex(got), hex(expected))
        if signed:
            assert 1 <= ((got >> 23) & 255) <= 254
            assert (got >> 31) == (signed < 0)
            counts['accepted_normal'] += 1
        else:
            assert got == 0
            counts['accepted_cancel'] += 1
    elif final_exp <= 0:
        assert ((expected >> 23) & 255) == 0
        counts['fallback_subnormal'] += 1
    else:
        assert (expected & 0x7fffffff) == 0x7f800000
        counts['fallback_overflow'] += 1
    counts['cases'] += 1
    counts['negative'] += signed < 0
    counts['gap_over7'] += abs(ex - ey) > 7
    trace.update(struct.pack('<IIIB', a, b, expected, accept))
    if counts['cases'] % 1024 == 0:
        assert time.perf_counter() - started < 5, 'Local model exceeded5second cap'


mantissas = [M, M + 1, M + 2, M + 3, 3 * (1 << 22), 2 * M - 2, 2 * M - 1]
for gap in [0, 1, 6, 7, 8, 16, 24, 25]:
    for low in sorted({1, 2, 23, 24, 127, 254 - gap}):
        if not 1 <= low <= 254 - gap:
            continue
        for ma in mantissas:
            for mb in mantissas:
                for sa in range(2):
                    for sb in range(2):
                        check(low + gap, low, ma, mb, sa, sb)
                        check(low, low + gap, ma, mb, sa, sb)
rng = random.Random(202610242150)
for _ in range(20000):
    gap = rng.randrange(26)
    low = rng.randint(1, 254 - gap)
    check(low, low + gap, rng.randrange(M, 2 * M), rng.randrange(M, 2 * M), rng.randrange(2), rng.randrange(2))
outside = []
for a, b in [(0x00800001, 0x80800000), (0x7f7fffff, 0x7f7fffff)]:
    got, accept, signed, final_exp = prototype(a, b)
    expected = bits(value(a) + value(b))
    assert not accept and got != expected
    outside.append(dict(a=hex(a), b=hex(b), wrong_without_guard=hex(got), expected=hex(expected), unreduced_final_exponent=final_exp))
result = dict(state='SELECTED_HOST_CHECK_PASS', at_utc=datetime.now(timezone.utc).isoformat(), counts=counts,
              wall_seconds=time.perf_counter() - started, trace_sha256=trace.hexdigest(),
              script_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              domain='Normal inputs, gap<=25; exact signed64 aligned sum, cancel=>+0, otherwise accept only unreduced final exponent1..254.',
              outside_guard_counterexamples=outside,
              scope='Finite host arithmetic and bitcast model only. No Lean, runtime compilation, benchmark, new holdout, or proof claim.')
(OUT / 'development-aligned-int64-host-check.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
print(json.dumps(result))
