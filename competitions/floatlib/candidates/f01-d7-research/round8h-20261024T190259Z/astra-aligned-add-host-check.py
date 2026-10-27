"""Bounded paper-prototype check, not a Lean/runtime candidate or speed test.

The host first converts exact UInt32 magnitude N to binary32, then shifts raw
exponent bits. For the original add, binary64 addition is exact when raw input
exponents differ by at most7 (aligned significands need at most32 bits <53).
Both host paths share C pack32; the separate exact integer oracle is retained.
"""
import ast
import hashlib
import json
import random
import struct
import time
from datetime import datetime, timezone
from pathlib import Path

HERE = Path(__file__).resolve().parent
ORACLE = HERE.parents[4] / 'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
raw = ORACLE.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
needed = {'exp', 'frac', 'nan', 'snan', 'inf', 'zero', 'choose', 'unpack', 'rounded', 'add'}
env = {}
exec(compile(ast.Module(body=[n for n in ast.parse(raw).body if isinstance(n, ast.FunctionDef) and n.name in needed], type_ignores=[]), str(ORACLE), 'exec'), env)
U32, M = (1 << 32) - 1, 1 << 23


def value(w):
    return struct.unpack('<f', struct.pack('<I', w))[0]


def bits(f):
    try:
        return struct.unpack('<I', struct.pack('<f', f))[0]
    except OverflowError:
        return 0xff800000 if f < 0 else 0x7f800000


def prototype(a, b):
    ex, ey = env['exp'](a), env['exp'](b)
    e = min(ex, ey)
    left = (M + env['frac'](a)) << (ex - e)
    right = (M + env['frac'](b)) << (ey - e)
    signed = (-left if a >> 31 else left) + (-right if b >> 31 else right)
    n = abs(signed)
    if n == 0:
        return 0, n
    mid = bits(float(n & U32))
    delta = (((e - 150) & U32) << 23) & U32
    return ((mid + delta) & U32) | (0x80000000 if signed < 0 else 0), n


started = time.perf_counter()
limit_seconds, maximum_cases = 2.0, 2500
count = small = zeros = 0
trace = hashlib.sha256()


def check(a, b):
    global count, small, zeros
    assert count < maximum_cases and time.perf_counter() - started < limit_seconds
    ex, ey = env['exp'](a), env['exp'](b)
    assert 24 <= min(ex, ey) and max(ex, ey) <= 252 and abs(ex - ey) <= 7
    result, n = prototype(a, b)
    assert n <= 2164260735 < (1 << 32)
    reference = env['add'](a, b)
    host = bits(value(a) + value(b))
    assert result == reference == host, (hex(a), hex(b), hex(result), hex(reference), hex(host))
    assert result == 0 or 1 <= env['exp'](result) <= 254
    small += int(0 < n < M)
    zeros += int(n == 0)
    for v in (a, b, result):
        trace.update(v.to_bytes(4, 'little'))
    count += 1


mantissas = [M, M + 1, 2 * M - 2, 2 * M - 1]
for d in range(8):
    for e in [24, 127, 245]:
        for mx in mantissas:
            for my in mantissas:
                for sx in range(2):
                    for sy in range(2):
                        check((sx << 31) | ((e + d) << 23) | (mx - M),
                              (sy << 31) | (e << 23) | (my - M))
rng = random.Random(202610242142)
for _ in range(256):
    d = rng.randrange(8)
    e = rng.randint(24, 252 - d)
    check((rng.randrange(2) << 31) | ((e + d) << 23) | rng.randrange(M),
          (rng.randrange(2) << 31) | (e << 23) | rng.randrange(M))
outside = []
for reason, a, b in [
    ('a23 cancellation needs subnormal rounding', (23 << 23) | 1, 0x80000000 | (23 << 23)),
    ('d8 same-sign sum exceeds UInt32', (135 << 23) | (M - 1), (127 << 23) | (M - 1)),
    ('E254 same-sign sum overflows Inf', (254 << 23) | (M - 1), (254 << 23) | (M - 1)),
]:
    wrong, n = prototype(a, b)
    expected = env['add'](a, b)
    assert wrong != expected
    outside.append({'reason': reason, 'a': hex(a), 'b': hex(b), 'magnitude': n,
                    'wrong_unguarded_word': hex(wrong), 'expected': hex(expected)})
result = {
    'at_utc': datetime.now(timezone.utc).isoformat(), 'cases': count,
    'limits': {'seconds': limit_seconds, 'cases': maximum_cases},
    'elapsed_seconds': time.perf_counter() - started,
    'seed': 202610242142, 'small_nonzero_magnitudes_below_2pow23': small,
    'exact_cancellations': zeros, 'outside_domain_counterexamples': outside,
    'trace_sha256': trace.hexdigest(), 'oracle_sha256': hashlib.sha256(raw).hexdigest(),
    'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    'proof_status': 'PAPER_PROTOTYPE_SELECTED_HOST_AND_INTEGER_ORACLE_CHECK; no Lean candidate or compiled all-input statement.',
    'performance_status': 'NOT_RUN',
    'limits_of_evidence': 'CPython C pack32 and binary64 addition are host diagnostics; both host paths share pack32. Exactness of bounded binary64 intermediate is a paper argument, not a general Lean Float64 bridge. This test does not validate any new runtime implementation.'
}
Path(__file__).with_suffix('.json').write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
print(json.dumps(result))
