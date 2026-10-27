"""Bounded source-translated runtime classifier and accepted-output checks; no benchmark data."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import math
import random
import struct
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
U32 = (1 << 32) - 1
SIGN, MANT, HIDDEN = 1 << 31, (1 << 23) - 1, 1 << 23
SEED = 0x523137

def bits_float(x):
    return struct.unpack('>f', struct.pack('>I', x))[0]

def float_bits(x):
    try:
        return struct.unpack('>I', struct.pack('>f', x))[0]
    except OverflowError:
        return 0xff800000 if x < 0 else 0x7f800000

def sort_and_magnitude(u, v):
    eu, ev = (u >> 23) & 255, (v >> 23) & 255
    if not (((eu - 1) & U32) <= 253 and ((ev - 1) & U32) <= 253):
        return None, 'normal_guard'
    hi, lo, ehi, elo = (v, u, ev, eu) if eu < ev else (u, v, eu, ev)
    d = ehi - elo
    highsign, lowsign = hi >= SIGN, lo >= SIGN
    same = highsign == lowsign
    adjust = 0 if same else 1
    if not (d <= 7 and adjust <= d):
        return None, 'domain_guard'
    ma, mb = (hi & MANT) | HIDDEN, (lo & MANT) | HIDDEN
    left = (ma << d) & U32
    n = ((left + mb) if same else (left - mb)) & U32
    if n < HIDDEN:
        return None, 'high_N_guard'
    return (hi, lo, ehi, elo, d, highsign, same, adjust, n), None

def runtime(u, v):
    data, rejected = sort_and_magnitude(u, v)
    if rejected:
        return None, rejected, data
    hi, lo, ehi, elo, d, highsign, same, adjust, n = data
    # Exact translation of the two numeric casts in the retained domain.
    f = bits_float(float_bits(float(n)))
    r = min(U32, int(f)) if f >= 0 else 0
    baseshift = (d - adjust) & U32
    threshold = (1 << ((baseshift + 24) & 31)) & U32
    bump = int(threshold <= r)
    shift = (baseshift + bump) & U32
    e = (((ehi - adjust) & U32) + bump) & U32
    assert 1 <= e <= 255
    if e > 254:
        return None, 'upper_E_guard', data
    word = ((SIGN if highsign else 0) | ((e & 255) << 23) | ((r >> (shift & 31)) & MANT))
    assert shift <= 8
    assert (r >> shift) >= HIDDEN and (r >> shift) < (1 << 24)
    assert r % (1 << shift) == 0
    return word, 'accepted', data

def old_path(u, v):
    # Reproduce the old expressions independently, including the old domain OR;
    # do not share the new classifier or magnitude routine with this oracle.
    ex = lambda w: (w >> 23) & 255
    if not (((ex(u) - 1) & U32) <= 253 and ((ex(v) - 1) & U32) <= 253):
        return None, 'normal_guard'
    high = v if ex(u) < ex(v) else u
    low = u if ex(u) < ex(v) else v
    gap = (ex(high) - ex(low)) & U32
    same = not ((u >= SIGN) != (v >= SIGN))
    if not (gap <= 7 and (same or 1 <= gap)):
        return None, 'domain_guard'
    left = ((((high & MANT) | HIDDEN) << (gap & 31)) & U32)
    right = (low & MANT) | HIDDEN
    n = ((left + right) if same else (left - right)) & U32
    if n < HIDDEN:
        return None, 'high_N_guard'
    mid = float_bits(float(n))
    e = ((((mid >> 23) & 255) + ex(low)) - 150) & U32
    if ((e - 1) & U32) > 253:
        return None, 'upper_E_guard'
    return ((SIGN if high >= SIGN else 0) | ((e & 255) << 23) | (mid & MANT)), 'accepted'

def construct_inputs():
    rng = random.Random(SEED)
    for _ in range(100000):
        yield rng.getrandbits(32), rng.getrandbits(32)
    specials = [0, 0x80000000, 1, 0x007fffff, 0x00800000, 0x7f7fffff,
                0x7f800000, 0xff800000, 0x7fc00000, 0x7f800001, 0xffffffff]
    for u in specials:
        for v in specials:
            yield u, v
    # Explicit exponent/rounding boundaries and both original input orders.
    mantissas = [HIDDEN, HIDDEN + 1, HIDDEN + 63, HIDDEN + 64, HIDDEN + 127,
                 HIDDEN + 128, (3 << 22), (1 << 24) - 129, (1 << 24) - 128,
                 (1 << 24) - 65, (1 << 24) - 64, (1 << 24) - 3,
                 (1 << 24) - 2, (1 << 24) - 1]
    for d in range(8):
        for ehi in sorted({d + 1, 127, 253, 254}):
            for ma in mantissas:
                for mb in mantissas:
                    for sh, sl in [(0, 0), (1, 1), (0, 1), (1, 0)]:
                        u = (sh << 31) | (ehi << 23) | (ma - HIDDEN)
                        v = (sl << 31) | ((ehi - d) << 23) | (mb - HIDDEN)
                        yield u, v
                        yield v, u

def worker():
    start = time.perf_counter()
    counts = {'total': 0, 'accepted': 0, 'normal_guard': 0, 'domain_guard': 0,
              'high_N_guard': 0, 'upper_E_guard': 0, 'accepted_old_word_equal': 0,
              'accepted_direct_binary32_equal': 0, 'classifier_equal': 0}
    for u, v in construct_inputs():
        word, state, data = runtime(u, v)
        previous, oldstate = old_path(u, v)
        counts['total'] += 1
        counts[state] += 1
        assert state == oldstate, (u, v, state, oldstate)
        counts['classifier_equal'] += 1
        if word is not None:
            assert word == previous, (u, v, word, previous)
            counts['accepted_old_word_equal'] += 1
            # Both finite normal operands have exponent gap <=7, hence their exact
            # sum needs <=32 significant binary digits and is exact in binary64.
            direct = float_bits(bits_float(u) + bits_float(v))
            assert word == direct, (u, v, word, direct, data)
            counts['accepted_direct_binary32_equal'] += 1
    print(json.dumps({'counts': counts, 'worker_seconds': time.perf_counter() - start}))

if '--worker' in sys.argv:
    worker()
else:
    start = time.perf_counter()
    child = subprocess.run([sys.executable, str(Path(__file__).resolve()), '--worker'],
                           capture_output=True, text=True, timeout=5)
    (HERE / 'runtime-flow-v1-raw.json').write_bytes(child.stdout.encode('utf-8'))
    (HERE / 'runtime-flow-v1-stderr.txt').write_bytes(child.stderr.encode('utf-8'))
    assert child.returncode == 0, child.stderr
    out = json.loads(child.stdout)
    out.update({'checked_utc': datetime.now(timezone.utc).isoformat(), 'seed': SEED,
                'input_source': '100000 reproducible arbitrary words plus explicit constructed IEEE/normal/rounding boundaries; research-only, not benchmark inputs',
                'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                'runtime_fragment_sha256': hashlib.sha256((HERE / 'Runtime-sorted-roundtrip-v1.lean.inc').read_bytes()).hexdigest(),
                'raw_sha256': hashlib.sha256(child.stdout.encode('utf-8')).hexdigest(),
                'actual_timeout_seconds': 5, 'wall_seconds': time.perf_counter() - start,
                'evidence': 'Finite independently transcribed word model; original and new classifier equality, accepted output bit equality; fallback implementation not executed',
                'Lean': 'NOT_RUN', 'C': 'NOT_RUN', 'assembly': 'NOT_RUN', 'performance': 'NOT_RUN'})
    (HERE / 'runtime-flow-v1-check.json').write_bytes((json.dumps(out, indent=2) + '\n').encode('utf-8'))
    print(json.dumps(out, indent=2))
