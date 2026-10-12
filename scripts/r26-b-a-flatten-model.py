"""Finite real overshoot/lane-mask/owner arithmetic model, against disjoint original offers."""
from datetime import datetime, timezone
from pathlib import Path
import argparse
import hashlib
import json
import random


def run():
    rng = random.Random(2631)
    totals = {'cases': 0, 'normal_cases': 0, 'fixed_fallback_cases': 0, 'tail_fallback_cases': 0}
    for _ in range(10000):
        cl = rng.randrange(4, 600)
        stop = 2
        records = []
        for _ in range(rng.randrange(0, 10)):
            if stop == 258:
                break
            nxt = min(258, stop+rng.randrange(1, 45))
            records.append((nxt, rng.getrandbits(32), rng.randrange(32768), rng.randrange(12)==0))
            stop = nxt
        ext = (rng.randrange(stop+1, 259), rng.getrandbits(32), rng.randrange(32768)) if stop < 258 and rng.randrange(2) else None
        costs = [rng.getrandbits(32) for _ in range(cl)]
        lc = [rng.getrandbits(32) for _ in range(512)]
        literal = rng.getrandbits(32)&0xfffffe00
        def term(l, base):
            return (((costs[l]+lc[l]+base)<<9)&0xffffffff)|l
        best, owner, prev = literal, 0, 2
        for hi, base, dist, fixed in records:
            value = min((term(l, base) for l in ([hi] if fixed else range(prev+1, hi+1))), default=0xffffffff) if hi < cl else 0xffffffff
            if value < best:
                best, owner = value, dist
            prev = max(prev, hi)
        if ext and ext[0] < cl:
            value = min(term(l,ext[1]) for l in range(prev+1, ext[0]+1))
            if value < best:
                best, owner = value, ext[2]
        odd = 267 > cl or any(fixed or hi>=cl for hi,base,dist,fixed in records)
        if odd:
            totals['fixed_fallback_cases'] += any(fixed for hi,base,dist,fixed in records)
            totals['tail_fallback_cases'] += 267>cl or any(hi>=cl for hi,base,dist,fixed in records)
        else:
            bl, dl = [rng.getrandbits(32) for _ in range(1024)], [rng.randrange(32768) for _ in range(1024)]
            def fill(lo, hi, base, dist):
                while lo <= hi:
                    for k in range(8):
                        bl[lo+k], dl[lo+k] = base, dist
                    lo += 8
            prev = 2
            for hi, base, dist, fixed in records:
                if hi > prev:
                    fill(prev+1,hi,base,dist)
                prev = max(prev,hi)
            hi = prev
            if ext:
                fill(prev+1,ext[0],ext[1],ext[2])
                hi = ext[0]
            packed = 0xffffffff
            if 3 <= hi <= 258:
                end = 3+((hi-3)//8+1)*8
                assert end <= cl
                packed = min((term(l,bl[l]) if l <= hi else 0xffffffff) for l in range(3,end))
            got = (packed, dl[packed&511]) if packed < literal else (literal,0)
            assert got == (best,owner), (cl,records,ext,got,(best,owner))
            totals['normal_cases'] += 1
        totals['cases'] += 1
    return totals


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    result = {'status': 'VERIFIED_FINITE_FILL_OVERSHOOT_MASK_PACKED_WRAP_TIE_OWNER_MODEL_ONLY',
              'computed_utc': datetime.now(timezone.utc).isoformat(), 'seed': 2631, 'totals': run(),
              'model_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'limits': ['Normal disjoint original offer domains plus exact odd/tail dispatch; actual XL/XD recurrence and all Rust DP-call cost/ch writes require native observer.',
                         'Finite arithmetic model is not complete gate or net performance.']}
    a.output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
