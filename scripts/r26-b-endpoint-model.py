"""Finite independent retained-set/minimum model for B11, not full-length equivalence."""
from pathlib import Path
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]


def main():
    candidate = ROOT / 'candidates/r26-b-552-endpoint-fit'
    raw = (candidate / 'parse.rs').read_bytes()
    source = raw.decode()
    manifest = json.loads((candidate / 'manifest.json').read_bytes())
    assert hashlib.sha256(raw).hexdigest() == manifest['hashes']['parse.rs']
    table = re.search(r'pub const R26_A_NEXT_END:\[usize;259\]=\[(.*?)\];', source, re.S)
    next_end = list(map(int, table.group(1).split(',')))
    # The reference is the declared semantic set, rather than a second next-end table.
    code_ends = [3,4,5,6,7,8,9,10,12,14,16,18,22,26,30,34,42,50,58,66,82,98,114,130,162,194,226,257,258]
    def observed(lo, hi):
        result = []
        length = lo
        while length <= hi and length <= 258:
            result.append(length)
            assert len(result) <= 256
            new = 259 if length == hi else min(next_end[length], hi)
            assert new > length
            length = new
        return result
    domains = 0
    maximum_points = 0
    for lo in range(3, 259):
        for hi in range(3, 259):
            expected = sorted({lo, hi} | {end for end in code_ends if lo <= end <= hi}) if lo <= hi else []
            actual = observed(lo, hi)
            assert actual == expected
            domains += 1
            maximum_points = max(maximum_points, len(actual))
    def packed(cost, price, base, length):
        return (((cost + price + base) & 0xFFFFFFFF) << 9 & 0xFFFFFFFF) | length
    comparisons = 0
    for seed in range(2048):
        lo = 3 + seed % 256
        hi = lo + (seed * 17 % (259 - lo))
        base = (seed * 0x9E3779B1) & 0xFFFFFFFF
        values = {length: packed((length * 0x85EBCA6B + seed) & 0xFFFFFFFF,
                                 (seed * 0xC2B2AE35 + length * 64) & 0xFFFFFFFF, base, length)
                  for length in range(lo, hi + 1)}
        actual = min((values[length] for length in observed(lo, hi)), default=0xFFFFFFFF)
        reference = min(values[length] for length in values if length in (lo, hi) or length in code_ends)
        assert actual == reference
        comparisons += 1
    # A deliberate interior minimum proves that no full-length equality is claimed.
    values = {length: packed(0 if length == 11 else 100, 0, 0, length) for length in range(3, 17)}
    full = min(values.values())
    sampled = min(values[length] for length in observed(3, 16))
    assert full < sampled and full & 511 == 11
    result = {'status': 'VERIFIED_FINITE_B11_RETAINED_SET_PROGRESS_AND_WRAP_PACKING_MODEL_ONLY',
              'source_hashes': manifest['hashes'], 'interval_cases': domains,
              'wrapped_packed_minimum_cases': comparisons, 'maximum_sampled_points': maximum_points,
              'declared_set': 'lo,hi,globalDEFLATE length-code ends within [lo,hi]',
              'non_equivalence_witness': {'lo': 3, 'hi': 16, 'interior_full_argmin': 11,
                                          'full_packed_minimum': full, 'sampled_packed_minimum': sampled},
              'limits': ['No native Rust, parser identity, optimal firstpass, proof/gate, performance or private/reward claim.',
                         'New sampler intentionally changes only statistical firstpass; original finalfullDP is unchanged.']}
    target = ROOT / 'evidence/round26/route-b/endpoint-b11-model.json'
    target.write_bytes((json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps(result))


if __name__ == '__main__':
    main()
