"""Bounded exact-word test of one native-rounded integer product plus exponent-bit shift."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import random
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
mul = env['mul']
M = 1 << 23
MASK = (1 << 32) - 1
word = lambda e, m, sign=0: (sign << 31) | (e << 23) | (m - M)


def shifted(a, b):
    s = env['exp'](a) + env['exp'](b)
    # Integer mantissa conversion is exact; first native multiplication rounds P once.
    mid = mul(word(150, M + env['frac'](a)), word(150, M + env['frac'](b)))
    delta = (((s - 300) & MASK) << 23) & MASK
    magnitude = (mid + delta) & MASK
    return magnitude | ((a ^ b) & 0x80000000), mid, delta


start = time.monotonic()
limit_seconds, maximum_cases = 2.0, 10000
count = 0
trace = hashlib.sha256()
mantissas = [M, M + 1, M + 2, M + 3, 3 * (1 << 22), 2 * M - 2, 2 * M - 1]


def check(ex, ey, mx, my, sx, sy):
    global count
    assert count < maximum_cases and time.monotonic() - start < limit_seconds
    a, b = word(ex, mx, sx), word(ey, my, sy)
    result, mid, delta = shifted(a, b)
    assert result == mul(a, b), (hex(a), hex(b), hex(result), hex(mul(a, b)))
    assert 1 <= env['exp'](result) <= 254
    for v in (a, b, mid, delta, result):
        trace.update(v.to_bytes(4, 'little'))
    count += 1


for s in [128, 129, 173, 174, 254, 299, 300, 379, 380]:
    for ex in sorted({max(1, s - 254), min(254, s - 1), s // 2}):
        for mx in mantissas:
            for my in mantissas:
                for sx in range(2):
                    for sy in range(2):
                        check(ex, s - ex, mx, my, sx, sy)
rng = random.Random(202610242020)
for _ in range(2048):
    s = rng.randint(128, 380)
    ex = rng.randint(max(1, s - 254), min(254, s - 1))
    check(ex, s - ex, rng.randrange(M, 2 * M), rng.randrange(M, 2 * M),
          rng.randrange(2), rng.randrange(2))

outside = []
for a, b in [(word(63, M), word(64, M)),
             (word(190, 2 * M - 1), word(191, 2 * M - 1))]:
    out = shifted(a, b)[0]
    expected = mul(a, b)
    assert out != expected
    outside.append({'a': hex(a), 'b': hex(b), 'original': hex(expected),
                    'wrong_unguarded_shift': hex(out)})
result = {
    'state': 'EXACT_WORD_SCREEN_NOT_LEAN_OR_HARDWARE_VALIDATION',
    'at_utc': datetime.now(timezone.utc).isoformat(), 'cases': count,
    'domain': 'Raw normal inputs E1..254; exponent sum128..380; all signs.',
    'maximum_cases': maximum_cases, 'wall_limit_seconds': limit_seconds,
    'elapsed_seconds': time.monotonic() - start,
    'seed': 202610242020, 'trace_sha256': trace.hexdigest(),
    'oracle_sha256': hashlib.sha256(raw).hexdigest(),
    'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    'outside_domain_counterexamples': outside,
    'limitation': 'One source-derived integer oracle supplies both original and first rounded product. No complete enumeration, Lean, native code, or performance evidence.',
}
(HERE / 'astra-exponent-shift-screen.json').write_text(
    json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
print(json.dumps({'cases': count, 'elapsed_seconds': result['elapsed_seconds'], 'outside': outside}))
