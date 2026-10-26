"""Independent boundary check of the proposed pure-word float32 add fast domain.

Domain (developer message 2026-10-24T23:58Z):
  both inputs normal binary32, gap d=ehi-elo in 0..7, same sign or (opposite and d>=2)
  L = Mhi<<d, R = Mlo, N = L+R or L-R
  base = (same ? 23 : 22) + d, h = base + (N >> (base+1)), t = h-23 in 1..8
  r = (N + 2^(t-1) - 1 + ((N>>t)&1)) >> t, carry = r>>24
  E = h + elo - 23 + carry, frac = r & 0x7fffff
  accept only if packed raw exponent E in 1..254

This script compares against exact integer RNE arithmetic. No Lean, no CI, wall-clock capped.
"""
import random
import time

MASK24 = (1 << 24) - 1
T0 = time.monotonic()
LIMIT = 20.0


def exact(E, F):
    """Return (E_biased, frac) of the correctly rounded binary32 value for a normal input."""
    pass


def round_value(N, elo):
    """Round value = N * 2^(elo-150), N>0, to binary32; return (E, frac) or None if out of range."""
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
    if E < 1 or E > 254:
        return None, (E, m)
    return (E, m & 0x7fffff), (E, m)


def model(ehi, Mhi, elo, Mlo, same):
    d = ehi - elo
    L = Mhi << d
    R = Mlo
    if same:
        N = L + R
    else:
        if L <= R:
            return {"invalid_domain": True, "d": d, "L": L, "R": R}
        N = L - R
    base = (23 if same else 22) + d
    h = base + (N >> (base + 1))
    t = h - 23
    r = (N + (1 << (t - 1)) - 1 + ((N >> t) & 1)) >> t
    carry = r >> 24
    E = h + elo - 23 + carry
    frac = r & 0x7fffff
    return {"N": N, "h": h, "t": t, "r": r, "carry": carry, "E": E, "frac": frac}


def check_case(ehi, Mhi, elo, Mlo, same):
    out = model(ehi, Mhi, elo, Mlo, same)
    if out.get("invalid_domain"):
        return ("INVALID_DOMAIN", out)
    N, h, t, E, frac = out["N"], out["h"], out["t"], out["E"], out["frac"]
    if h != N.bit_length() - 1:
        return ("LOG2_MISMATCH", {**out, "bitlen": N.bit_length() - 1})
    if not 1 <= t <= 8:
        return ("T_RANGE", out)
    exact_pair, raw = round_value(N, elo)
    if exact_pair is None:
        # exact result is subnormal or overflow: model must not claim a normal word
        if 1 <= E <= 254:
            return ("ACCEPTED_OUT_OF_RANGE", {**out, "exact": raw})
        return None
    if (E, frac) != exact_pair:
        return ("MISMATCH", {**out, "exact": exact_pair})
    return None


def main():
    rng = random.Random(20261024)
    tested = rejected = 0
    failures = []
    mantissas = [1 << 23, (1 << 23) + 1, (1 << 23) + (1 << 22), (1 << 24) - 1, (1 << 24) - 2]
    exps = [1, 2, 3, 23, 24, 25, 100, 126, 127, 200, 252, 253, 254]
    for ehi in exps:
        for d in range(0, 8):
            elo = ehi - d
            if elo < 1:
                continue
            for Mhi in mantissas:
                for Mlo in mantissas:
                    for same in (True, False):
                        if not same and d < 2:
                            continue
                        tested += 1
                        res = check_case(ehi, Mhi, elo, Mlo, same)
                        if res:
                            failures.append((ehi, Mhi, elo, Mlo, same, res))
                        if time.monotonic() - T0 > LIMIT:
                            break
    while time.monotonic() - T0 < LIMIT:
        ehi = rng.choice(exps)
        d = rng.randrange(0, 8)
        elo = ehi - d
        if elo < 1:
            continue
        Mhi = rng.randrange(1 << 23, 1 << 24)
        Mlo = rng.randrange(1 << 23, 1 << 24)
        same = rng.random() < 0.5
        if not same and d < 2:
            continue
        tested += 1
        res = check_case(ehi, Mhi, elo, Mlo, same)
        if res:
            failures.append((ehi, Mhi, elo, Mlo, same, res))
    print(f"tested={tested} failures={len(failures)} elapsed={time.monotonic()-T0:.1f}s")
    for f in failures[:10]:
        print("FAIL", f)


if __name__ == "__main__":
    main()
