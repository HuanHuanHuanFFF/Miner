"""Finite exact a_probe word-step model for raised valid prefixes."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json
import random


def run():
    rng = random.Random(2620)
    totals = {'cases': 0, 'capped258_cases': 0, 'capped258_unused_direction_differences': 0,
              'saved_word_pairs': 0}

    def probe(s, p, q, k):
        def word(i):
            return int.from_bytes(s[i:i+8], 'big') if i+8 <= len(s) else 0
        a, b = word(p+k), word(q+k)
        pairs = 1
        while a == b and k < 250:
            k += 8
            a, b = word(p+k), word(q+k)
            pairs += 1
        l = 258 if a == b else k + (64-(a^b).bit_length())//8
        return min(l, 258), int(a < b), pairs

    for _ in range(12000):
        shared = rng.randrange(0, 320)
        a = bytearray(rng.randbytes(400))
        b = bytearray(a[:shared] + rng.randbytes(400-shared))
        if shared < 400 and a[shared] == b[shared]:
            b[shared] ^= 1
        s = bytes(a+b)
        seed = rng.randrange(min(shared, 258)+1)
        raised = rng.randrange(seed, min(shared, 258)+1)
        old, new = probe(s, 0, 400, seed), probe(s, 0, 400, raised)
        assert old[0] == new[0] and new[2] <= old[2]
        if old[0] < 258:
            assert old[1] == new[1]
        else:
            totals['capped258_cases'] += 1
            totals['capped258_unused_direction_differences'] += old[1] != new[1]
        totals['saved_word_pairs'] += old[2] - new[2]
        totals['cases'] += 1
    return totals


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--output', type=Path, required=True)
    a = ap.parse_args()
    assert not a.output.exists()
    result = {'status': 'VERIFIED_FINITE_VALID_PREFIX_WORD_STEP_MODEL_ONLY', 'computed_utc': datetime.now(timezone.utc).isoformat(),
              'seed': 2620, 'totals': run(), 'model_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              'scope': 'Assumes prefix validity; B19 tree-rewiring model and B20 actual active-link assertions separately establish finite metadata consumption. Not a Rust proof or performance result.'}
    a.output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
