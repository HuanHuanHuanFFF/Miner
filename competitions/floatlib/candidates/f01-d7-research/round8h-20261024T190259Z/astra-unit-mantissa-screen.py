"""Bounded exact-word counterexample screen; no Lean, native float, or benchmark."""
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
tree = ast.parse(raw)
exec(compile(ast.Module(body=[n for n in tree.body if isinstance(n, ast.FunctionDef)
                             and n.name in needed], type_ignores=[]), str(ORACLE), 'exec'), env)
mul = env['mul']
M = 1 << 23


def word(e, m, sign=0):
    return (sign << 31) | (e << 23) | (m - M)


def unit_fused(a, b):
    s = env['exp'](a) + env['exp'](b)
    ua, ub = (127 << 23) | (a & (M - 1)), (127 << 23) | (b & (M - 1))
    factor = ((a ^ b) & 0x80000000) | ((s - 127) << 23)
    middle = mul(ua, ub)
    return mul(middle, factor), middle, factor


start = time.monotonic()
limit_seconds = 2.0
maximum_cases = 10000
trace = hashlib.sha256()
count = 0


def check(ex, ey, mx, my, sx, sy):
    global count
    assert 1 <= ex <= 254 and 1 <= ey <= 254 and 128 <= ex + ey <= 380
    assert count < maximum_cases and time.monotonic() - start < limit_seconds
    a, b = word(ex, mx, sx), word(ey, my, sy)
    fused, mid, factor = unit_fused(a, b)
    direct = mul(a, b)
    assert fused == direct, (hex(a), hex(b), hex(fused), hex(direct))
    assert 1 <= env['exp'](fused) <= 254
    for v in (a, b, mid, factor, fused):
        trace.update(v.to_bytes(4, 'little'))
    count += 1


mantissas = [M, M + 1, M + 2, 3 * (1 << 22), 2 * M - 2, 2 * M - 1]
for s in [128, 129, 150, 173, 174, 254, 379, 380]:
    for ex in sorted({max(1, s - 254), min(254, s - 1), s // 2}):
        for mx in mantissas:
            for my in mantissas:
                for sx in range(2):
                    for sy in range(2):
                        check(ex, s - ex, mx, my, sx, sy)
rng = random.Random(202610241920)
for _ in range(2048):
    s = rng.randint(128, 380)
    ex = rng.randint(max(1, s - 254), min(254, s - 1))
    check(ex, s - ex, rng.randrange(M, 2 * M), rng.randrange(M, 2 * M),
          rng.randrange(2), rng.randrange(2))

a, b = word(63, M), word(64, M)
outside127 = {'a': hex(a), 'b': hex(b), 'original': hex(mul(a, b)),
              'unguarded_normal_factor_result': hex(unit_fused(a, b)[0])}
assert outside127['original'] != outside127['unguarded_normal_factor_result']
edges = {
    'unit_max380': hex(unit_fused(word(190, 2 * M - 1), word(190, 2 * M - 1))[0]),
    'sum381_finite': hex(mul(word(190, M), word(191, M))),
    'sum381_overflow': hex(mul(word(190, 2 * M - 1), word(191, 2 * M - 1))),
    'sum382_min_overflow': hex(mul(word(191, M), word(191, M))),
    'sum102_max_zero': hex(mul(word(51, 2 * M - 1), word(51, 2 * M - 1))),
    'sum103_max_subnormal': hex(mul(word(51, 2 * M - 1), word(52, 2 * M - 1))),
}
assert edges == {'unit_max380': '0x7f7ffffe', 'sum381_finite': '0x7f000000',
                 'sum381_overflow': '0x7f800000', 'sum382_min_overflow': '0x7f800000',
                 'sum102_max_zero': '0x0', 'sum103_max_subnormal': '0x1'}
result = {
    'state': 'FINITE_WORD_MODEL_ONLY_NOT_LEAN_OR_NATIVE_VALIDATION',
    'at_utc': datetime.now(timezone.utc).isoformat(),
    'cases': count, 'maximum_cases': maximum_cases, 'wall_limit_seconds': limit_seconds,
    'elapsed_seconds': time.monotonic() - start,
    'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    'oracle_sha256': hashlib.sha256(raw).hexdigest(),
    'trace_sha256': trace.hexdigest(), 'seed': 202610241920,
    'domain': 'Both input raw E1..254; sum128..380; all signs; selected directed mantissas plus2048 random.',
    'outside127': outside127, 'edges': edges,
    'limitation': 'Both sides use the same frozen source-derived integer oracle. No independent hardware oracle, complete enumeration, Lean proof, lowering or performance result.',
}
(HERE / 'astra-unit-mantissa-screen.json').write_text(
    json.dumps(result, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
print(json.dumps({'cases': count, 'elapsed_seconds': result['elapsed_seconds'],
                  'outside127': outside127, 'edges': edges}))
