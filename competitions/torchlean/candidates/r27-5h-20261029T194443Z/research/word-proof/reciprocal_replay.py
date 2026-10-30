from pathlib import Path
import datetime
import hashlib
import json
import random

HERE = Path(__file__).resolve().parent


def high_product(a, b, bits):
    base = 1 << (bits // 2)
    p = (a % base) * (b % base)
    u = (a // base) * (b % base) + p // base
    v = (a % base) * (b // base) + u % base
    return (a // base) * (b // base) + u // base + v // base


def corrected(a, d, bits):
    if d == 0:
        return 0, a
    radix = 1 << bits
    reciprocal = (radix - 1) // d
    q = high_product(a, reciprocal, bits)
    r = a - q * d
    assert q * d <= a < (q + 2) * d
    assert 0 <= r < radix and r < 2 * d
    return (q + 1, r - d) if d <= r else (q, r)


def main():
    seed = 27102912
    rng = random.Random(seed)
    counts = {}
    for bits in (4, 8):
        radix = 1 << bits
        for a in range(radix):
            for b in range(radix):
                assert high_product(a, b, bits) == a * b // radix
                assert corrected(a, b, bits) == (divmod(a, b) if b else (0, a))
        counts[f'exhaustive_mulhigh_and_divrem_{bits}'] = radix * radix
    radix = 1 << 64
    edge = [0, 1, 2, (1 << 32)-1, 1 << 32, (1 << 32)+1,
            (1 << 63)-1, 1 << 63, radix-2, radix-1]
    pairs = [(a, b) for a in edge for b in edge]
    pairs += [(rng.randrange(radix), rng.randrange(radix)) for _ in range(20000)]
    for a, b in pairs:
        assert high_product(a, b, 64) == a * b // radix
        assert corrected(a, b, 64) == (divmod(a, b) if b else (0, a))
    counts['mulhigh_and_divrem64_boundary_random'] = len(pairs)
    sources = {p.name: dict(bytes=p.stat().st_size,
                           sha256=hashlib.sha256(p.read_bytes()).hexdigest())
               for p in (Path(__file__), HERE/'ReciprocalNatCore.lean', HERE/'MulHighNatCore.lean')}
    result = dict(at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), seed=seed,
                  classification='FINITE_INTEGER_MODEL_ONLY_NOT_LEAN_OR_NATIVE', counts=counts,
                  sources=sources,
                  pending=['Lean compilation', 'Actual UInt64 multiplication and no-wrap bridge',
                           'Integrated original all12 gate', 'Complete-call native measurement'])
    (HERE/'reciprocal-finite-replay.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(counts,indent=2))


if __name__ == '__main__':
    main()
