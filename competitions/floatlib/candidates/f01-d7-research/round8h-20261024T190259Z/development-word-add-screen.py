"""Bounded integer-only add domain on already exposed public inputs."""
from pathlib import Path
from datetime import datetime, timezone
import ast
import hashlib
import json
import random
import struct
import time

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
M, U32, SIGN = 1 << 23, (1 << 32) - 1, 1 << 31


def functions(path, names, constants=()):
    tree = ast.parse(path.read_bytes())
    nodes = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in names
             or isinstance(n, ast.Assign) and any(isinstance(t, ast.Name) and t.id in constants for t in n.targets)]
    env = {}
    exec(compile(ast.Module(body=nodes, type_ignores=[]), str(path), 'exec'), env)
    return env


def bits(number):
    try:
        return struct.unpack('<I', struct.pack('<f', number))[0]
    except OverflowError:
        return 0xff800000 if number < 0 else 0x7f800000


def value(word):
    return struct.unpack('<f', struct.pack('<I', word))[0]


def fast(a, b):
    ex, ey = (a >> 23) & 255, (b >> 23) & 255
    if not (1 <= ex <= 254 and 1 <= ey <= 254):
        return None, 'input-not-normal'
    high, low = (a, b) if ex >= ey else (b, a)
    eh, el = max(ex, ey), min(ex, ey)
    gap = eh - el
    same = ((a ^ b) & SIGN) == 0
    if gap > 7 or not (same or gap >= 2):
        return None, 'gap-or-cancellation-domain'
    left = ((high & (M - 1)) | M) << gap
    right = (low & (M - 1)) | M
    magnitude = left + right if same else left - right
    assert 0 < magnitude <= 2164260735
    base = (23 if same else 22) + gap
    leading = base + (magnitude >> (base + 1))
    assert leading == magnitude.bit_length() - 1 and 24 <= leading <= 31
    shift = leading - 23
    assert 1 <= shift <= 8
    biased = magnitude + (1 << (shift - 1)) - 1 + ((magnitude >> shift) & 1)
    rounded = biased >> shift
    carry = rounded >> 24
    exponent = leading + el - 23 + carry
    assert M <= rounded <= 2 * M and 2 <= exponent <= 256
    word = (high & SIGN) | ((exponent & 255) << 23) | (rounded & (M - 1))
    packed_exp = (word >> 23) & 255
    assert (1 <= packed_exp <= 254) == (exponent <= 254)
    if exponent > 254:
        return None, 'overflow-fallback'
    assert word == bits(value(a) + value(b)), (hex(a), hex(b), hex(word))
    return word, 'same-sign' if same else 'opposite-gap-ge2'


generator = ROOT / 'competitions/floatlib/research/astra-collab-20261023-r7/public-nonfinite-opportunity.py'
assert hashlib.sha256(generator.read_bytes()).hexdigest() == '28eb38c9388f595960ea039e18b5783984cb2a0b0cdb182011449a0cd146e7a1'
g = functions(generator, {'word', 'ctz', 'element'}, {'M32', 'M64'})
support = functions(ROOT / 'competitions/floatlib/candidates/f01-d7-research/scalar-opportunity.py', {'partner'}, {'M32'})
base = ROOT / 'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40124283357'
index = json.loads((base / 'original-artifact-hashes.json').read_bytes())
plan_path = base / index['directory'] / 'diagnostics/f01-d7-public-suite/public-suite/public-drawn-plan.json'
plan = json.loads(plan_path.read_bytes())
rng = random.Random(202610242300)
started = time.perf_counter()
rows, trace = [], hashlib.sha256()
for case in plan['cases']:
    if case['kernel'] != 'add' or not case['timed']:
        continue
    length = case['work']
    n = min(length, 256)
    positions = list(range(length)) if length <= n else [0, length - 1] + rng.sample(range(1, length - 1), n - 2)
    counts = dict(accepted=0, same_sign=0, opposite_gap_ge2=0, overflow_fallback=0)
    fixed_b = g['element'](case, 0, 1, 31)
    for position in positions:
        a = g['element'](case, position, 0, 31)
        b = support['partner'](case, position, a, g['element'], g['word'], fixed_b)
        got, reason = fast(a, b)
        counts['accepted'] += got is not None
        counts['same_sign'] += reason == 'same-sign'
        counts['opposite_gap_ge2'] += reason == 'opposite-gap-ge2'
        counts['overflow_fallback'] += reason == 'overflow-fallback'
        trace.update(struct.pack('<III', a, b, got if got is not None else 0))
    rows.append(dict(case=case['name'], work=case['work'], samples=n, counts=counts))
    assert time.perf_counter() - started < 5
weight = sum(row['work'] for row in rows)
fractions = {key: sum(row['work'] * row['counts'][key] / row['samples'] for row in rows) / weight for key in rows[0]['counts']}
record = dict(at_utc=datetime.now(timezone.utc).isoformat(), state='FINITE_EXPOSED_INPUT_AND_HOST_SCREEN_ONLY', run=40124283357,
              samples=sum(row['samples'] for row in rows), work_weighted_input_fractions=fractions,
              wall_seconds=time.perf_counter() - started, trace_sha256=trace.hexdigest(),
              script_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(), plan_sha256=hashlib.sha256(plan_path.read_bytes()).hexdigest(),
              cases=rows, scope='Already exposed D1 samples, at most256 positions/case. Normal input exponents, gap<=7, same sign or gap>=2. Pure integer align/RNE/pack; all accepted samples match independent exact binary64 addition then32bit pack. Input fractions are not elapsed time shares, all-input proofs or actual speedups.')
(OUT / 'development-word-add-screen.json').write_bytes((json.dumps(record, indent=2) + '\n').encode())
print(json.dumps({key: val for key, val in record.items() if key != 'cases'}))
