"""Finite Python model for D1 subrelations, not Rust/Lean or performance evidence."""
from pathlib import Path
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/extension90m/route-d'


def gain(l, d, hlit=64):
    c = 168
    if 10 < l < 258:
        c += 16 * ((l - 3).bit_length() - 3)
    if d > 4:
        c += 16 * ((d - 1).bit_length() - 2)
    return l * hlit - c


def find(s, prev, p, st, have, minl, depth, nice, gm=0):
    cap = min(258, len(s) - p)
    best, bd, bg, c, k = max(have, minl - 1), 0, -1000000, st, depth
    stop = min(nice, cap)
    pb = s[p + best] if p + best < len(s) else 0
    while k > 0:
        d = p - c
        if 1 <= d <= 32768 and c + best < len(s):
            if s[c + best] == pb:
                l = 0
                while l < cap and s[c + l] == s[p + l]:
                    l += 1
                take = l > best
                if take and gm == 1:
                    g = gain(l, d)
                    if g > bg:
                        bg = g
                    else:
                        take = False
                if take:
                    best, bd = l, d
                    if l >= stop or p + l >= len(s):
                        k = 1
                    else:
                        pb = s[p + l]
            nx = prev[c % len(prev)]
            if nx < c:
                c, k = nx, k - 1
            else:
                k = 0
        else:
            k = 0
    return (best if bd else 0, bd)


def resume(s, prev, p, st, f, minl, depth, nice):
    l, d = f
    if depth > 1 and l < nice and l < len(s) - p and st < p and p - st <= 32768:
        nx = prev[st % len(prev)]
        if nx < st:
            g = find(s, prev, p, nx, l, minl, depth - 1, nice)
            if g[1] != 0:
                return g
    return f


def legal(s, p, f):
    l, d = f
    return l < 3 or (3 <= l <= 258 and 1 <= d <= min(32768, p)
                     and p + l <= len(s) and s[p-d:p-d+l] == s[p:p+l])


def key(s, p, h):
    return (((int.from_bytes(s[p:p+4], 'big') * 0x9E3779B97F4A7C15)
             & ((1 << 64) - 1)) >> 48) % h


def main():
    rng = random.Random(260901)
    counts = dict(queries=0, continuation_equal=0, valid_results=0,
                  deferred_current=0, unique_deeper_current_lost=0,
                  lazy_residual_improved_gain=0, ring_wrapped_queries=0)
    cases = []
    for n in [33, 65, 129, 257, 513, 1025, 4097]:
        for alphabet in [2, 4, 16, 256]:
            data = bytearray(rng.randrange(alphabet) for _ in range(n))
            # Mixture of overlap, repeated blocks and occasional disturbances.
            for i in range(17, n):
                if (i // 31) % 3 != 0 and rng.random() < 0.83:
                    data[i] = data[i - [1, 7, 16][(i // 31) % 3]]
            s = bytes(data)
            for w in [16, 64, 32768]:
                h, prev = [0] * 256, [0] * w
                for p in range(n - 8):
                    a = key(s, p, len(h))
                    st = h[a]
                    prev[p % w], h[a] = st, p
                    full = find(s, prev, p, st, 0, 4, 12, 128)
                    first = find(s, prev, p, st, 0, 4, 1, 128)
                    completed = resume(s, prev, p, st, first, 4, 12, 128)
                    assert full == completed, (n, alphabet, w, p, full, completed)
                    counts['queries'] += 1
                    counts['continuation_equal'] += 1
                    counts['ring_wrapped_queries'] += p >= w
                    f = completed
                    if 4 <= first[0] < 64 and p + 1 < n - 8:
                        q = p + 1
                        hq = h[key(s, q, len(h))]
                        g = find(s, prev, q, hq, first[0] - 1, 4, 1, 128, 1)
                        if g[0] >= 4 and gain(*g) > gain(*first):
                            f = first
                            counts['deferred_current'] += 1
                            counts['unique_deeper_current_lost'] += full != first
                            # Mirror q's real insertion before its remainder.
                            p2 = prev.copy()
                            p2[q % w] = hq
                            deeper = resume(s, p2, q, hq, g, 4, 12, 128)
                            chosen = deeper if gain(*deeper) > gain(*g) else g
                            assert legal(s, q, chosen)
                            counts['lazy_residual_improved_gain'] += chosen != g
                    assert legal(s, p, f)
                    counts['valid_results'] += 1
            cases.append({'n': n, 'alphabet': alphabet,
                          'input_sha256': hashlib.sha256(s).hexdigest()})
    raw = (ROOT / 'candidates/r26-d-658-selective-depth/parse.rs').read_bytes()
    receipt = {'status': 'PASS', 'candidate_sha256': hashlib.sha256(raw).hexdigest(),
               'model_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
               'seed': 260901, 'window_sizes': [16, 64, 32768], 'counts': counts,
               'input_cases': cases,
               'limits': 'Finite translated Python state model only. No actual Rust compilation, official corpus, time, score or Lean proof. All counts synthetic and not public-workload coverage.'}
    (OUT / 'd1-state-model.json').write_bytes((json.dumps(receipt, indent=2) + '\n').encode())
    print(json.dumps({'status': 'PASS', 'counts': counts}, indent=2))


if __name__ == '__main__':
    main()
