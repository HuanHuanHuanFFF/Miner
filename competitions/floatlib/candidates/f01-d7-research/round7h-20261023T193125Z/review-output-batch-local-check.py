"""Finite logical packing/schedule check only; no Lean or float execution."""
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

here = Path(__file__).resolve().parent
shapes = 0
packets = 0
positions = 0
for batch in range(5):
    for m in range(5):
        for n in range(6):
            for p in range(25):
                def one_batch(b):
                    return [[[(b, k, 10 * g + lane) if 10 * g + lane < p else None
                              for lane in range(10)] for k in range(n)]
                            for g in range((p + 9) // 10)]
                global_pack = [one_batch(b) for b in range(batch)]
                result = []
                for b in range(batch):
                    assert len(result) == b * m * p
                    local_pack = one_batch(b)
                    assert local_pack == global_pack[b]
                    packets += len(local_pack) * n
                    for i in range(m):
                        r = b * m + i
                        assert r < batch * m and r // m == b
                        assert len(result) == r * p
                        for g in range((p + 9) // 10):
                            for lane in range(min(10, p - 10 * g)):
                                j = 10 * g + lane
                                for k in range(n):
                                    assert local_pack[g][k][lane] == (b, k, j)
                                result.append((b, i, j))
                        assert len(result) == (r + 1) * p
                    assert len(result) == (b + 1) * m * p
                    del local_pack
                assert result == [(q // (m * p), (q % (m * p)) // p, q % p)
                                  for q in range(batch * m * p)]
                shapes += 1
                positions += len(result)

draft = here / 'review-output-batch-local.lean'
report = {
    'state': 'PASS_FINITE_LOGICAL_PACKING_AND_LAYOUT_ONLY',
    'updated_at_utc': datetime.now(timezone.utc).isoformat(),
    'draft_sha256': sha256(draft.read_bytes()).hexdigest(),
    'draft_bytes': draft.stat().st_size,
    'shapes': shapes,
    'batch_packets_checked': packets,
    'output_positions_checked': positions,
    'new_Kernel_generated': False,
    'Lean': 'NOT_RUN',
    'floating_point_and_gate': 'NOT_RUN',
    'C_lifecycle_and_performance': 'NOT_RUN',
}
(here / 'review-output-batch-local-check.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
print(json.dumps(report))
