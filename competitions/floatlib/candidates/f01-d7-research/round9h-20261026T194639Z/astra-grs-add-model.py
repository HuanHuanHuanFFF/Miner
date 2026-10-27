"""Bounded exact-integer check of a broad normal ADD proposal; not Lean/performance."""
from pathlib import Path
from hashlib import sha256
from datetime import datetime, timezone
import json
import random
import time

HERE = Path(__file__).resolve().parent
BASE = 1 << 23
MASK = (1 << 32) - 1

def rne(n, shift):
    if shift <= 0:
        return n << -shift
    q, r = divmod(n, 1 << shift)
    half = 1 << (shift - 1)
    return q + (r > half or (r == half and q & 1))

def exact_add_normal(u, v):
    eu, ev = (u >> 23) & 255, (v >> 23) & 255
    mu, mv = BASE | (u & (BASE - 1)), BASE | (v & (BASE - 1))
    emin = min(eu, ev)
    n = (-1 if u >> 31 else 1) * (mu << (eu - emin))
    n += (-1 if v >> 31 else 1) * (mv << (ev - emin))
    if n == 0:
        return 0
    sign = (n < 0) << 31
    n = abs(n)
    scale = emin - 150
    h = n.bit_length() - 1
    if h + scale < -126:
        q = rne(n, -(scale + 149))
        assert 0 <= q <= BASE
        return sign | q
    q = rne(n, h - 23)
    if q == 2 * BASE:
        q >>= 1
        h += 1
    e = h + scale + 127
    if e >= 255:
        return sign | 0x7f800000
    assert 1 <= e <= 254 and BASE <= q < 2 * BASE
    return sign | (e << 23) | (q - BASE)

def uint32_to_float32_bits(n):
    assert 0 < n < 1 << 28
    h = n.bit_length() - 1
    q = rne(n, h - 23)
    if q == 2 * BASE:
        q >>= 1
        h += 1
    return ((h + 127) << 23) | (q - BASE)

def proposal(u, v):
    eu, ev = (u >> 23) & 255, (v >> 23) & 255
    if not (1 <= eu <= 254 and 1 <= ev <= 254):
        return None
    if (u & 0x7fffffff) < (v & 0x7fffffff):
        u, v, eu, ev = v, u, ev, eu
    d = eu - ev
    a = (BASE | (u & (BASE - 1))) << 3
    b = (BASE | (v & (BASE - 1))) << 3
    if d:
        b = (b >> d) | bool(b & ((1 << d) - 1))
    same_sign = (u >> 31) == (v >> 31)
    t = a + b if same_sign else a - b
    assert 0 <= t < 1 << 28
    if t == 0:
        return 0
    raw = uint32_to_float32_bits(t)
    # These are UInt32 modular operations, followed by a rejecting range test.
    e = ((raw >> 23) + eu - 153) & MASK
    if ((e - 1) & MASK) > 253:
        return None
    return (u & 0x80000000) | (e << 23) | (raw & (BASE - 1))

def main():
    started = time.monotonic()
    rng = random.Random(19272323)
    checked = hits = zero = fallback = 0
    failure = None
    mantissas = [BASE, BASE+1, BASE+2, BASE+3, BASE+7,
                 3*BASE//2-1, 3*BASE//2, 2*BASE-8, 2*BASE-4,
                 2*BASE-3, 2*BASE-2, 2*BASE-1]
    exponents = [1, 2, 3, 4, 23, 24, 25, 126, 127, 128, 252, 253, 254]
    pairs = []
    for e in exponents:
        for d in [0, 1, 2, 3, 4, 7, 23, 24, 25, 26, 31, 32, 33, 127, 253]:
            if e-d < 1:
                continue
            for m in mantissas:
                for n in mantissas:
                    for signs in range(4):
                        pairs.append((((signs & 1) << 31) | (e << 23) | (m-BASE),
                                      (((signs >> 1) & 1) << 31) | ((e-d) << 23) | (n-BASE)))
    directed_count = len(pairs)
    for _ in range(30000):
        u = (rng.randrange(2) << 31) | (rng.randrange(1,255) << 23) | rng.randrange(BASE)
        v = (rng.randrange(2) << 31) | (rng.randrange(1,255) << 23) | rng.randrange(BASE)
        pairs.append((u,v))
    for u,v in pairs:
        checked += 1
        result = proposal(u,v)
        if result is None:
            fallback += 1
            continue
        expected = exact_add_normal(u,v)
        hits += 1
        zero += result == 0
        if result != expected:
            failure = {'u':hex(u),'v':hex(v),'proposal':hex(result),'exact_integer_oracle':hex(expected)}
            break
    out = {'state':'BOUNDED_INTEGER_MODEL_ONLY', 'checked':checked, 'directed_pairs':directed_count,
           'random_pairs':30000, 'accepted':hits, 'fallback':fallback,'positive_zero':zero,
           'first_counterexample':failure,'elapsed_seconds':time.monotonic()-started,
           'seed':19272323,'source_sha256':sha256(Path(__file__).read_bytes()).hexdigest(),
           'observed_at_utc':datetime.now(timezone.utc).isoformat(),
           'domain':'Both input exponents1..254; raw-magnitude order; all signs; normal postE only or exact+0; all misses retainB2',
           'scope':'Exact-integer oracle and bounded model. Does not verify Lean UInt32 primitive, IEEE opaque cast, compiler path, coverage timing or full gate.',
           'next':'Paper RTO/subtraction and low-exponent/carry bridge, compare old same-signGRS and R16; no claim of performance or novelty.'}
    (HERE/'astra-grs-add-model.json').write_text(json.dumps(out,indent=2)+'\n')
    print(json.dumps(out,indent=2))
    if failure:
        raise SystemExit(1)

if __name__ == '__main__':
    main()
