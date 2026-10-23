"""Finite UInt32 guard diagnostic only; no Lean or float arithmetic claim."""
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json
import random

HERE = Path(__file__).resolve().parent
MASK = 0xffffffff

def guard(x, y):
    a = ((x & 0x7fffffff) - 0x20000000) & MASK
    b = ((y & 0x7fffffff) - 0x20000000) & MASK
    return (a | b) < 0x40000000

def band(x):
    return 0x20000000 <= (x & 0x7fffffff) < 0x60000000

words = [(s << 31) | (e << 23) | f for s in range(2)
         for e in range(256) for f in (0, 1, 0x7fffff)]
count = hits = 0
for x in words:
    for y in words:
        h = guard(x, y)
        assert h == (band(x) and band(y))
        if h:
            ex, ey = (x >> 23) & 255, (y >> 23) & 255
            assert 64 <= ex <= 191 and 64 <= ey <= 191
            assert ex + ey >= 128
            hits += 1
        count += 1
rng = random.Random(0xBADD11)
for _ in range(20000):
    x, y = rng.getrandbits(32), rng.getrandbits(32)
    assert guard(x, y) == (band(x) and band(y))
    count += 1

report = {
    'state': 'PASS_FINITE_WORD_GUARD_DIAGNOSTIC_ONLY',
    'updated_at_utc': datetime.now(timezone.utc).isoformat(),
    'kernel_sha256': sha256((HERE / 'Kernel.lean').read_bytes()).hexdigest(),
    'boundary_input_words': len(words),
    'word_pairs_checked': count,
    'boundary_pair_hits': hits,
    'random_seed': 0xBADD11,
    'properties': ['Joint bit-OR guard equals both E64..191 interval tests in sampled model', 'No positive hit enters existing exsum<128 LowScale', 'Sign bits do not affect eligibility; NaN/Inf/zero/subnormal samples reject'],
    'not_run': ['Lean exact statement', 'kernel replay', 'axiom audit', 'floating-point checksum', 'full gate', 'generated code', 'timing'],
}
(HERE / 'guard-precheck.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
print(json.dumps({k: report[k] for k in ('state', 'kernel_sha256', 'word_pairs_checked', 'boundary_pair_hits')}))
