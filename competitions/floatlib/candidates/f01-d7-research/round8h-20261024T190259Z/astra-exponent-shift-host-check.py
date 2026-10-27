"""Bounded search-stage independent host rounding crosscheck; no Lean or compilation."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import platform
import random
import struct
import sys
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
ORACLE = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/nonfinite-oracle.py'
raw = ORACLE.read_bytes()
assert hashlib.sha256(raw).hexdigest() == '3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72'
needed = {'exp', 'frac', 'nan', 'snan', 'inf', 'zero', 'canon', 'choose', 'unpack', 'rounded', 'mul'}
env = {}
exec(compile(ast.Module(body=[n for n in ast.parse(raw).body if isinstance(n, ast.FunctionDef)
                             and n.name in needed], type_ignores=[]), str(ORACLE), 'exec'), env)

M, MASK = 1 << 23, (1 << 32) - 1


def to_word(x):
    return struct.unpack('<I', struct.pack('<f', x))[0]


def from_word(u):
    return struct.unpack('<f', struct.pack('<I', u))[0]


assert struct.calcsize('<f') == 4
assert sys.float_info.mant_dig >= 48 and sys.float_info.min_exp <= -252
assert sys.float_info.max_exp >= 256
sentinels = [to_word(1.0), to_word(1.0 + 2.0 ** -24),
             to_word(1.0 + 3.0 * 2.0 ** -24)]
assert sentinels == [0x3f800000, 0x3f800000, 0x3f800002]
start = time.monotonic()
limit_seconds, maximum_cases = 2.0, 10000
count = 0
trace = hashlib.sha256()


def check(ex, ey, mx, my, sx, sy):
    global count
    assert count < maximum_cases and time.monotonic() - start < limit_seconds
    a, b = (sx << 31) | (ex << 23) | (mx - M), (sy << 31) | (ey << 23) | (my - M)
    # Each binary32 input is exact in binary64; its 24x24 significand product occupies
    # at most48 bits, and its exponent remains inside binary64 normal range. Thus this
    # double product is exact before the separate C pack4 rounding operation.
    direct_host = to_word(from_word(a) * from_word(b))
    middle_host = to_word(float(mx) * float(my))
    shifted = ((middle_host + ((((ex + ey - 300) & MASK) << 23) & MASK)) & MASK)
    shifted |= ((sx ^ sy) << 31)
    direct_integer = env['mul'](a, b)
    assert shifted == direct_host == direct_integer, (
        hex(a), hex(b), hex(shifted), hex(direct_host), hex(direct_integer))
    for v in (a, b, middle_host, shifted, direct_host):
        trace.update(v.to_bytes(4, 'little'))
    count += 1


mantissas = [M, M + 1, M + 3, 3 * (1 << 22), 2 * M - 2, 2 * M - 1]
for s in [128, 174, 254, 299, 300, 379, 380]:
    for ex in sorted({max(1, s - 254), min(254, s - 1), s // 2}):
        for mx in mantissas:
            for my in mantissas:
                for sx in range(2):
                    for sy in range(2):
                        check(ex, s - ex, mx, my, sx, sy)
rng = random.Random(202610242100)
for _ in range(2048):
    s = rng.randint(128, 380)
    ex = rng.randint(max(1, s - 254), min(254, s - 1))
    check(ex, s - ex, rng.randrange(M, 2 * M), rng.randrange(M, 2 * M),
          rng.randrange(2), rng.randrange(2))
result = {
    'state': 'SELECTED_HOST_C_PACK4_AND_INTEGER_ORACLE_AGREE',
    'at_utc': datetime.now(timezone.utc).isoformat(), 'cases': count,
    'maximum_cases': maximum_cases, 'wall_limit_seconds': limit_seconds,
    'elapsed_seconds': time.monotonic() - start,
    'purpose': 'Address shared source-integer-oracle implementation risk before further integration.',
    'host': {'python': sys.version, 'platform': platform.platform(),
             'double_mantissa_bits': sys.float_info.mant_dig,
             'double_min_exp': sys.float_info.min_exp, 'double_max_exp': sys.float_info.max_exp,
             'pack4_rne_sentinels': [hex(v) for v in sentinels]},
    'domain': 'Two original normal binary32 words, raw exponent sum128..380, all signs.',
    'trace_sha256': trace.hexdigest(), 'seed': 202610242100,
    'source_oracle_sha256': hashlib.sha256(raw).hexdigest(),
    'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    'limitation': 'Search-stage finite crosscheck. Host products use exact binary64 intermediates then C pack4 rounding; this is not execution of the pinned Lean-generated Float32 multiply, a general Float64 Lean bridge, a universal proof, a benchmark, or independent final confirmation. Both host paths use the same C pack4, but its implementation differs from the frozen integer oracle.',
}
(HERE / 'astra-exponent-shift-host-check.json').write_text(
    json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
print(json.dumps({'cases': count, 'elapsed_seconds': result['elapsed_seconds'],
                  'host_sentinels': result['host']['pack4_rne_sentinels'], 'state': result['state']}))
