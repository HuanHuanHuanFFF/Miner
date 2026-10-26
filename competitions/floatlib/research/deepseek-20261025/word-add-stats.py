"""Boundary statistics for the pure-word add domain (companion to check-word-add.py)."""
import random
import time

MASK24 = (1 << 24) - 1
T0 = time.monotonic()
LIMIT = 10.0


def round_value(N, elo):
    h = N.bit_length() - 1
    if h > 23:
        shift = h - 23
        m = N >> shift
        rem = N & ((1 << shift) - 1)
        half = 1 << (shift - 1)
        if rem > half or (rem == half and (m & 1)):
            m += 1
        if m == (1 << 24):
            m >>= 1
            h += 1
    else:
        m = N << (23 - h)
    E = h + elo - 23
    return (E, m & 0x7fffff) if 1 <= E <= 254 else None


def model(ehi, Mhi, elo, Mlo, same):
    d = ehi - elo
    L, R = Mhi << d, Mlo
    N = L + R if same else L - R
    base = (23 if same else 22) + d
    h = base + (N >> (base + 1))
    t = h - 23
    r = (N + (1 << (t - 1)) - 1 + ((N >> t) & 1)) >> t
    return N, h, t, r >> 24, h + elo - 23 + (r >> 24), r & 0x7fffff


def main():
    rng = random.Random(7)
    stats = {"tested": 0, "accepted": 0, "fallback_low": 0, "fallback_high": 0,
             "mismatch": 0, "maxN": 0, "maxE": 0, "minE": 999}
    examples = {"low": None, "high": None}
    while time.monotonic() - T0 < LIMIT:
        ehi = rng.randrange(1, 255)
        d = rng.randrange(0, 8)
        elo = ehi - d
        if elo < 1:
            continue
        Mhi = rng.randrange(1 << 23, 1 << 24)
        Mlo = rng.randrange(1 << 23, 1 << 24)
        same = rng.random() < 0.5
        if not same and d < 2:
            continue
        N, h, t, carry, E, frac = model(ehi, Mhi, elo, Mlo, same)
        stats["tested"] += 1
        stats["maxN"] = max(stats["maxN"], N)
        stats["maxE"] = max(stats["maxE"], E)
        stats["minE"] = min(stats["minE"], E)
        if h != N.bit_length() - 1 or not 1 <= t <= 8:
            stats["mismatch"] += 1
        exact = round_value(N, elo)
        if exact is None:
            if E < 1:
                stats["fallback_low"] += 1
                examples["low"] = examples["low"] or (ehi, Mhi, elo, Mlo, same, E, N)
            else:
                stats["fallback_high"] += 1
                examples["high"] = examples["high"] or (ehi, Mhi, elo, Mlo, same, E, N)
        else:
            stats["accepted"] += 1
            if (E, frac) != exact:
                stats["mismatch"] += 1
    print(stats)
    print("examples", examples)


if __name__ == "__main__":
    main()
