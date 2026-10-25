"""Bounded raw UInt64 normal-multiply prototype vs exact host product/pack."""
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


def value(word):
    return struct.unpack('<f', struct.pack('<I', word))[0]


def bits(number):
    try:
        return struct.unpack('<I', struct.pack('<f', number))[0]
    except OverflowError:
        return 0xff800000 if number < 0 else 0x7f800000


def test(ex, ey, mx, my, sx, sy):
    a, b = (sx << 31) | (ex << 23) | (mx - M), (sy << 31) | (ey << 23) | (my - M)
    product = (mx * my) & U64
    high = product >> 47
    shift = 23 + high
    intermediate = (product + (1 << (shift - 1))) & U64
    intermediate = (intermediate - 1) & U64
    intermediate = (intermediate + ((product >> shift) & 1)) & U64
    rounded = intermediate >> shift
    carry = rounded >> 24
    exponent = (ex + ey - 127 + high + carry) & U32
    got = ((a ^ b) & 0x80000000) | ((exponent & 255) << 23) | (rounded & (M - 1))
    expected = bits(value(a) * value(b))
    return a, b, got, expected, product, shift, rounded, exponent


started = time.perf_counter()
trace = hashlib.sha256()
counts = dict(cases=0, ties_even=0, ties_odd=0, rounding_carry=0, sum380=0)


def check(*arguments):
    a, b, got, expected, product, shift, rounded, exponent = test(*arguments)
    assert got == expected, (hex(a), hex(b), hex(got), hex(expected))
    assert 1 <= exponent <= 254 and 70368744177664 <= product <= 281474943156225
    assert product + (1 << (shift - 1)) <= U64 and shift in (23, 24)
    assert M <= rounded <= 2 * M
    assert not (product >> 47 and rounded == 2 * M)
    quotient, remainder = divmod(product, 1 << shift)
    tie = remainder == 1 << (shift - 1)
    counts['ties_even'] += tie and quotient % 2 == 0
    counts['ties_odd'] += tie and quotient % 2 == 1
    counts['rounding_carry'] += rounded == 2 * M
    counts['sum380'] += arguments[0] + arguments[1] == 380
    counts['cases'] += 1
    trace.update(struct.pack('<IIII', a, b, got, expected))
    if counts['cases'] % 1024 == 0:
        assert counts['cases'] <= 50000 and time.perf_counter() - started < 5


mantissas = [M, M + 1, M + 2, M + 3, 3 * (1 << 22), 3 * (1 << 22) + 2, 3 * (1 << 22) + 6, 2 * M - 2, 2 * M - 1]
for total in [128, 129, 173, 174, 254, 299, 300, 301, 379, 380]:
    for ex in sorted({max(1, total - 254), min(254, total - 1), total // 2}):
        for mx in mantissas:
            for my in mantissas:
                for sx in range(2):
                    for sy in range(2):
                        check(ex, total - ex, mx, my, sx, sy)
rng = random.Random(202610242230)
for _ in range(30000):
    total = rng.randint(128, 380)
    ex = rng.randint(max(1, total - 254), min(254, total - 1))
    check(ex, total - ex, rng.randrange(M, 2 * M), rng.randrange(M, 2 * M), rng.randrange(2), rng.randrange(2))
assert min(counts['ties_even'], counts['ties_odd'], counts['rounding_carry'], counts['sum380']) > 0
outside = [test(63, 64, M, M, 0, 0), test(190, 191, 2 * M - 1, 2 * M - 1, 0, 0)]
assert all(row[2] != row[3] for row in outside)
result = dict(state='INDEPENDENT_SELECTED_HOST_CHECK_PASS', at_utc=datetime.now(timezone.utc).isoformat(), counts=counts,
              wall_seconds=time.perf_counter() - started, trace_sha256=trace.hexdigest(),
              script_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              domain='Both normal input exponents1..254 and sum128..380; all signs. Explicit UInt64/UInt32 modular operations.',
              outside_guard_counterexamples=[dict(a=hex(row[0]), b=hex(row[1]), wrong_without_guard=hex(row[2]), expected=hex(row[3])) for row in outside],
              scope='Finite independent host binary64 exact48bit multiplication followed by one final binary32 pack. Prototype is all integer. Not Lean acceptance, actual candidate execution, full input proof, holdout or timing.')
(OUT / 'development-integer-normal-host-check.json').write_bytes((json.dumps(result, indent=2) + '\n').encode())
print(json.dumps(result))
