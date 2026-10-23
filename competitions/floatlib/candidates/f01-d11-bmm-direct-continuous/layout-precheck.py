"""Finite integer scheduling/address diagnostic; not Lean or float validation."""
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

HERE = Path(__file__).resolve().parent
shapes = outputs = addresses = selected_shapes = 0
for batch in range(5):
    for m in range(6):
        for n in range(6):
            for p in range(16):
                emitted = []
                selected_shapes += n <= 4 and p > 2
                for r in range(batch * m):
                    assert len(emitted) == r * p
                    b, i = r // m, r % m
                    old_a, new_a = (b * m + i) * n, r * n
                    old_b, new_b = b * n * p, (r // m) * n * p
                    assert old_a == new_a and old_b == new_b
                    for j in range(p):
                        assert len(emitted) == r * p + j
                        q = r * p + j
                        assert (q // (m * p), (q % (m * p)) // p, q % p) == (b, i, j)
                        for k in range(n):
                            assert new_a + k == old_a + k
                            assert new_b + j + k * p == (b * n + k) * p + j
                            addresses += 1
                        emitted.append(q)
                    assert len(emitted) == (r + 1) * p
                assert emitted == list(range(batch * m * p))
                shapes += 1
                outputs += len(emitted)

large_checks = 0
for m in (2**64 + 1, 2**128 + 9):
    for b in (0, 2**80 + 3):
        for i in (0, 1, m - 1):
            r = b * m + i
            assert r // m == b and r % m == i
            assert (r // m * m + r % m) * (2**96 + 1) == r * (2**96 + 1)
            large_checks += 1

report = {
    'state': 'PASS_FINITE_LAYOUT_AND_ADDRESS_DIAGNOSTIC_ONLY',
    'updated_at_utc': datetime.now(timezone.utc).isoformat(),
    'kernel_sha256': sha256((HERE / 'Kernel.lean').read_bytes()).hexdigest(),
    'all_dimension_shapes': shapes,
    'dispatcher_selected_shapes': selected_shapes,
    'output_positions_checked': outputs,
    'original_ordered_address_pairs_checked': addresses,
    'large_Nat_identity_spot_checks': large_checks,
    'scope': 'Compare original DirectRows row decoding/base addresses with flat-r writer; every emitted prefix and original reference B address in finite mathematical integer model. New dispatcher only n<=4,p>2.',
    'not_run': ['Lean statement', 'kernel replay', 'axiom audit', 'floating-point checksums', 'full gate', 'actual C allocation/closure inspection', 'timing'],
}
(HERE / 'layout-precheck.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
print(json.dumps({k: report[k] for k in ('state', 'kernel_sha256', 'all_dimension_shapes', 'output_positions_checked', 'original_ordered_address_pairs_checked')}))
