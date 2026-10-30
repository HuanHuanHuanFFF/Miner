"""Finite exact integer check of the separately derived paired15 identity."""
from pathlib import Path
import datetime
import hashlib
import itertools
import json
import random

M = 1 << 14
MASK = (1 << 64) - 1


def pair(a, b, c, d):
    aa, bb, cc, dd = a + M, b + M, c + M, d + M
    assert all(0 <= t < 2*M for t in [aa, bb, cc, dd])
    left = aa + (bb << 32)
    right = dd + (cc << 32)
    assert left < 1 << 47 and right < 1 << 47
    middle = ((left * right) & MASK) >> 32
    assert middle == aa*cc + bb*dd < 1 << 31
    result = middle - M*(aa+bb+cc+dd) + 2*M*M
    assert result == a*c + b*d
    return middle


def main():
    edge = [-M, -M+1, -1, 0, 1, M-1]
    count = 0
    for values in itertools.product(edge, repeat=4):
        pair(*values)
        count += 1
    rng = random.Random(2026103000)
    for _ in range(20000):
        pair(*(rng.randrange(-M, M) for _ in range(4)))
        count += 1
    aggregate = 0
    for n in [1, 2, 3, 7, 16, 31, 64, 257, 608, 1023]:
        xs = [rng.randrange(-M, M) for _ in range(n)]
        ys = [rng.randrange(-M, M) for _ in range(n)]
        padded = n + (n & 1)
        if n & 1:
            xs.append(0)
            ys.append(0)
        unsigned = sum(pair(xs[i], xs[i+1], ys[i], ys[i+1]) for i in range(0, padded, 2))
        correction = M*(sum(x+M for x in xs) + sum(y+M for y in ys))
        assert unsigned - correction + padded*M*M == sum(x*y for x, y in zip(xs, ys))
        assert unsigned < 1 << 60 and correction < 1 << 60
        aggregate += 1
    n = 1 << 30
    assert (n//2)*(2*(2*M-1)**2) < 1 << 60
    assert M*(2*n*(2*M-1)) < 1 << 60
    assert n*M*M == 1 << 58
    result = {"at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
              "state": "FINITE_INTEGER_MODEL_PASS_UNIVERSAL_IDENTITY_WRITTEN_ON_PAPER",
              "source_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              "pair_cases": count, "aggregate_cases": aggregate,
              "length_limit": "Symbolic bound only, no billion-term execution",
              "Lean": "NOT_WRITTEN_NOT_COMPILED", "native_cost": "UNKNOWN",
              "actual_ReLU_certificate_and_Kernel": "NOT_IMPLEMENTED",
              "no_confirmation_inputs_used": True}
    Path(__file__).with_name("pair15-result.json").write_text(
        json.dumps(result, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps(result))


if __name__ == "__main__":
    main()
