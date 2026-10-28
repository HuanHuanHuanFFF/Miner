"""Bounded integer-index counterexample check, not a Lean/IEEE proof."""
from pathlib import Path
import hashlib, json
from datetime import datetime, timezone

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[6]
KERNEL = ROOT / 'competitions/floatlib/candidates/f01-r23-research-indexed-producer/Kernel.lean'
sha = lambda b: hashlib.sha256(b).hexdigest()
counts = dict(shapes_and_lengths=0, produced_pairs=0, valid_lane_reads=0, padded_right_fields=0)
for batch in range(5):
    for n in range(7):
        for p in range(12):
            groups = (p + 1) // 2
            for length in range(batch * n * p + 4):
                raw = list(range(1, length + 1))
                get = lambda index: raw[index] if index < len(raw) else 0
                cache = []
                for row in range(batch * n):
                    for g in range(groups):
                        c = 2 * g
                        cache.append((get(row * p + c), get(row * p + c + 1) if c + 1 < p else 0))
                assert len(cache) == batch * n * groups
                counts['shapes_and_lengths'] += 1
                for row in range(batch * n):
                    for g in range(groups):
                        expected = (get(row * p + 2 * g), get(row * p + 2 * g + 1) if 2 * g + 1 < p else 0)
                        assert cache[row * groups + g] == expected
                        counts['produced_pairs'] += 1
                        if 2 * g + 1 >= p:
                            assert expected[1] == 0
                            counts['padded_right_fields'] += 1
                for b in range(batch):
                    for k in range(n):
                        for g in range(groups):
                            for c in range(2):
                                if 2 * g + c < p:
                                    assert cache[b * n * groups + g + k * groups][c] == get(b * n * p + 2 * g + c + k * p)
                                    counts['valid_lane_reads'] += 1
result = dict(status='PASS_BOUNDED_INDEX_MODEL_ONLY', checked_at_utc=datetime.now(timezone.utc).isoformat(),
    script_sha256=sha(Path(__file__).read_bytes()), kernel_sha256=sha(KERNEL.read_bytes()),
    domain=dict(batch='0..4', n='0..6', p='0..11', array_length='0..batch*n*p+3', values='index+1; default0'),
    counts=counts,
    odd_padding_counterexample=dict(batch=1,n=2,p=3,B=[1,2,3,4,5,6],g=1,k=0,c=1,
        packed_right=0,unrestricted_raw_read=4,valid_lane_condition=False),
    scope='Checks only address algebra, default handling, and odd padding. Does not check Lean typing, replay, axioms, IEEE operations, full BMM, or runtime performance.')
(HERE / 'producer-model-check.json').write_text(json.dumps(result, indent=2)+'\n', encoding='utf-8')
print(json.dumps(result))
