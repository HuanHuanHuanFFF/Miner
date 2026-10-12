"""Finite original packed-cost offer/owner model for equal-base adjacent run reduction."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import random


def run():
    rng = random.Random(2630)
    cases = 0
    merged_distinct = 0
    for _ in range(8000):
        stop = 2
        offers = []
        for _ in range(rng.randrange(1, 10)):
            if stop == 258:
                break
            nxt = min(258, stop+rng.randrange(1, 32))
            price = rng.randrange(0, 5)*64
            distance = rng.randrange(0, 32768)
            fixed = rng.randrange(8) == 0
            offers.append((stop+1, nxt, price, distance, fixed))
            stop = nxt
        costs = [rng.getrandbits(32) for _ in range(259)]
        lc = [rng.getrandbits(32) for _ in range(259)]
        bias = rng.getrandbits(32)
        literal = rng.getrandbits(32)

        def term(l, price):
            return (((costs[l]+lc[l]+price+bias)<<9)&0xffffffff)|l

        old_best, old_owner = literal, 0
        for lo, hi, price, distance, fixed in offers:
            best = min(term(l,price) for l in ([hi] if fixed else range(lo,hi+1)))
            if best < old_best:
                old_best, old_owner = best, distance
        groups = []
        for item in offers:
            lo, hi, price, distance, fixed = item
            if groups and not fixed and not groups[-1][-1][4] and groups[-1][-1][2] == price and groups[-1][-1][1]+1 == lo:
                groups[-1].append(item)
            else:
                groups.append([item])
        new_best, new_owner = literal, 0
        for group in groups:
            first, last = group[0], group[-1]
            if first[4]:
                best = term(first[1],first[2])
            else:
                best = min(term(l,first[2]) for l in range(first[0],last[1]+1))
            if best < new_best:
                length = best&511
                owner = next(item[3] for item in group if item[0] <= length <= item[1])
                new_best, new_owner = best, owner
            if len(group)>1 and len({item[3] for item in group})>1:
                merged_distinct += 1
        assert (old_best, old_owner) == (new_best, new_owner)
        cases += 1
    return {'cases': cases, 'equal_price_groups_with_distinct_distances': merged_distinct}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    result = {'status': 'VERIFIED_FINITE_PACKED_WRAP_TIE_AND_ORIGINAL_OWNER_GROUP_MODEL_ONLY',
              'computed_utc': datetime.now(timezone.utc).isoformat(), 'seed': 2630, 'totals': run(),
              'model_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'limits': ['Finite random32bit packed terms/ties/fixed-only breaks, no original Rust parser or performance claim.',
                         'Original prev/pd/XL/XD recurrence remains separate; groupmin owner is recovered from its original disjoint length domain.']}
    a.output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
