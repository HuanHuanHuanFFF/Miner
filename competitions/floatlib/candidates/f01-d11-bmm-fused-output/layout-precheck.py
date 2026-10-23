"""Finite diagnostic for the new write schedule; not a Lean or float proof."""
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

here = Path(__file__).resolve().parent
cases = 0
elements = 0
for batch in range(6):
    for m in range(6):
        for p in range(43):
            result = []
            tiles = 0
            for r in range(batch * m):
                assert len(result) == r * p
                for g in range((p + 9) // 10):
                    assert len(result) == r * p + min(10 * g, p)
                    tiles += 1
                    for lane in range(min(10, p - 10 * g)):
                        j = 10 * g + lane
                        q = r * p + j
                        decoded = (q // (m * p), (q % (m * p)) // p, q % p)
                        assert decoded == (r // m, r % m, j)
                        result.append(decoded)
                    assert len(result) == r * p + min(10 * (g + 1), p)
                assert len(result) == (r + 1) * p
            assert len(result) == batch * m * p
            assert tiles == batch * m * ((p + 9) // 10)
            assert result == [(q // (m * p), (q % (m * p)) // p, q % p)
                              for q in range(batch * m * p)]
            cases += 1
            elements += len(result)

# These are address/count spot checks, with no huge allocation.
large_nats = [2**64 + 1, 2**128 + 9, 2**256 + 13]
large_checks = 0
for p in large_nats:
    for g in [0, 1, p // 10, (p + 9) // 10 - 1]:
        if 0 <= g < (p + 9) // 10:
            assert 10 * g < p
            assert min(10 * g, p) + min(10, p - 10 * g) == min(10 * (g + 1), p)
            large_checks += 1
    assert min(10 * ((p + 9) // 10), p) == p

receipt = {
    'state': 'PASS_FINITE_LAYOUT_DIAGNOSTIC_ONLY',
    'updated_at_utc': datetime.now(timezone.utc).isoformat(),
    'kernel_sha256': sha256((here / 'Kernel.lean').read_bytes()).hexdigest(),
    'shapes': cases,
    'written_elements_checked': elements,
    'large_nat_count_spot_checks': large_checks,
    'scope': 'Prefix lengths, exact row-major coordinate mapping, no skipped/duplicated valid lanes, one tile computation per row/group. Python mathematical integers only.',
    'not_run': ['Lean statement elaboration', 'kernel replay', 'axiom audit', 'floating-point checksum', 'full gate', 'timing', 'generated-C allocation inspection'],
}
(here / 'layout-precheck.json').write_text(json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
print(json.dumps(receipt))
