"""Small arithmetic screen only; never a substitute for Lean/all-input proof."""
from pathlib import Path
import hashlib
import json
from datetime import datetime, timezone

here = Path(__file__).resolve().parent
counts = {'block_read': 0, 'tail_read': 0, 'column_pair': 0}
for m in range(19):
    for p in range(19):
        for b in range(5):
            for block in range(m // 4):
                for lane in range(4):
                    for j in range(p):
                        q = b*m*p + block*(4*p) + lane*p + j
                        expected = (b*m + 4*block + lane)*p + j
                        assert q == expected
                        assert (q // (m*p), (q % (m*p)) // p, q % p) == (b, 4*block+lane, j)
                        counts['block_read'] += 1
            for j in range((m % 4)*p):
                q = b*m*p + (m//4)*(4*p) + j
                i = (m//4)*4 + j//p
                c = j % p
                assert (q // (m*p), (q % (m*p)) // p, q % p) == (b, i, c)
                assert i < m and c < p
                counts['tail_read'] += 1
        for j in range(p):
            group, lane = j//2, j%2
            assert group < (p+1)//2
            assert 2*group+lane == j
            assert lane == 0 or 2*group+1 < p
            counts['column_pair'] += 1

receipt = dict(
    status='PASS_FINITE_ARITHMETIC_SCREEN_ONLY',
    checked_at_utc=datetime.now(timezone.utc).isoformat(),
    script_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
    domain=dict(m='0..18', p='0..18', b='0..4', all_valid_blocks_lanes_columns=True),
    cases=counts,
    lean_status='NOT_RUN',
    claim='Finite validation of exact batch, block, tail and paired-column index formulas; no numerical or all-input equivalence claim.',
)
(here/'index-screen.json').write_text(json.dumps(receipt, indent=2)+'\n', encoding='utf-8')
print(json.dumps(receipt, indent=2))
