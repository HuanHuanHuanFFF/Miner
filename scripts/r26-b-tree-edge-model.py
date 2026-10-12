"""Finite edge-prefix metadata and rewiring model; no performance/proof claim."""
from datetime import datetime, timezone
from pathlib import Path
import argparse
import hashlib
import json
import random

ROOT = Path(__file__).resolve().parents[1]


def run(seed=2619):
    rng = random.Random(seed)
    count = {'inputs': 0, 'positions': 0, 'probes': 0, 'shortcuts': 0,
             'active_edge_checks': 0, 'copy_checks': 0, 'rewire_checks': 0, 'expired_links': 0}
    for case in range(120):
        n = rng.randrange(120, 900)
        alphabet = rng.choice([1, 2, 4, 16, 256])
        data = bytes(rng.randrange(alphabet) for _ in range(n))
        if case % 3 == 0:
            motif = bytes(rng.randrange(256) for _ in range(rng.randrange(1, 40)))
            data = (motif * (n // len(motif) + 1))[:n]
        window = rng.choice([16, 32, 64])
        cap = rng.choice([16, 32, 64])
        nice = rng.choice([4, 8, 16])
        depth = rng.choice([1, 4, 12, 32])
        head, kid, edge = [0] * 16, [0] * (2 * window), [(0, False)] * (2 * window)
        owner = [-1] * window

        def probe(a, b):
            k = 0
            while k < cap and data[a + k] == data[b + k]:
                k += 1
            return k, int(data[a:a + cap] < data[b:b + cap])

        def pair(l, p):
            low = min(l, p)
            return low, l != p and low < cap

        def join(l, tag):
            t, exact = tag
            return min(l, t), (l < t and l < cap) or (t < l and exact)

        def check(at, parent, oldest, pos):
            child = kid[at]
            if child > oldest and child <= pos:
                actual = probe(parent, child - 1)[0]
                bound, exact = edge[at]
                assert actual >= bound, (case, at, parent, child, actual, edge[at])
                if exact:
                    assert actual == bound and bound < cap
                count['active_edge_checks'] += 1

        for pos in range(n - cap - 1):
            count['positions'] += 1
            oldest = max(0, pos - (window - 1))
            h = (data[pos] * 31 + data[pos + 1]) % 16
            cur, head[h] = head[h], pos + 1
            lo_at, hi_at = 2 * (pos % window), 2 * (pos % window) + 1
            root_lo, root_hi = lo_at, hi_at
            lo_len = hi_len = 0
            incoming = None
            last_l = last_cmp = 0
            owner[pos % window] = pos
            steps = 0
            while steps < depth and cur > oldest and cur <= pos:
                p = cur - 1
                l, cmp = probe(p, pos)
                count['probes'] += 1
                assert l >= min(lo_len, hi_len)
                if incoming is not None:
                    t, exact = incoming
                    if (exact and t < last_l) or t > last_l:
                        predicted = (t, 1 - last_cmp) if t < last_l else (last_l, last_cmp)
                        assert (l, cmp) == predicted, (case, pos, p, incoming, last_l, last_cmp, (l, cmp), predicted)
                        count['shortcuts'] += 1
                pk = 2 * (p % window)
                if l >= nice or l >= cap:
                    for dest, src in [(lo_at, pk), (hi_at, pk + 1)]:
                        parent_l = cap if dest in (root_lo, root_hi) else (lo_len if dest == lo_at else hi_len)
                        kid[dest], edge[dest] = kid[src], join(parent_l, join(l, edge[src]))
                        parent = pos if dest in (root_lo, root_hi) else owner[dest // 2]
                        check(dest, parent, oldest, pos)
                        count['copy_checks'] += 1
                    lo_at = len(kid)
                    cur = 0
                elif cmp == 1:
                    parent = pos if lo_at == root_lo else owner[lo_at // 2]
                    edge[lo_at] = pair(l, cap if lo_at == root_lo else lo_len)
                    kid[lo_at] = cur
                    check(lo_at, parent, oldest, pos)
                    count['rewire_checks'] += 1
                    lo_at, lo_len = pk + 1, l
                    incoming = edge[lo_at]
                    last_l, last_cmp = l, cmp
                    cur = kid[lo_at]
                else:
                    parent = pos if hi_at == root_hi else owner[hi_at // 2]
                    edge[hi_at] = pair(l, cap if hi_at == root_hi else hi_len)
                    kid[hi_at] = cur
                    check(hi_at, parent, oldest, pos)
                    count['rewire_checks'] += 1
                    hi_at, hi_len = pk, l
                    incoming = edge[hi_at]
                    last_l, last_cmp = l, cmp
                    cur = kid[hi_at]
                steps += 1
            if cur > 0 and (cur <= oldest or cur > pos):
                count['expired_links'] += 1
            if lo_at < len(kid):
                kid[lo_at] = kid[hi_at] = 0
                edge[lo_at] = edge[hi_at] = (0, False)
        count['inputs'] += 1
    return count


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    totals = run()
    result = {'status': 'VERIFIED_FINITE_STRING_TREE_REWIRING_MODEL_ONLY', 'computed_utc': datetime.now(timezone.utc).isoformat(),
              'seed': 2619, 'totals': totals, 'model_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'scope': 'Small windows/depths/NICE caps with actual suffix comparisons; not production Rust, encoder performance or formal proof.'}
    a.output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
