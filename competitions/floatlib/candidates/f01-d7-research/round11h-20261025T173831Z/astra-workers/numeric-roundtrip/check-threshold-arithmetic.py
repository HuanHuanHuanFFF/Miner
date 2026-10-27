"""Check finite exponent-case constants used by the paper derivation; no input enumeration or Lean."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

HERE = Path(__file__).resolve().parent
rows = []
for d in range(8):
    maximum = ((1 << 24) - 1) * ((1 << d) + 1)
    if d == 0:
        residue_cases = []
        for residue in range(4):
            n = maximum - (maximum - residue) % 4
            q = n // 2 + (residue == 3)
            residue_cases.append({'residue': residue, 'maximum_N': n, 'maximum_q': q})
        bound = max(x['maximum_q'] for x in residue_cases)
    else:
        residue_cases = None
        bound = maximum // (1 << (d + 1)) + 1
        assert bound == (1 << 23) + (1 << (23 - d))
    assert bound < (1 << 24)
    row = {'d': d, 'same_maximum_N': maximum, 'same_top_shift': d + 1,
           'same_q_upper': bound, 'd0_exact_residue_cases': residue_cases}
    if d >= 1:
        opposite_maximum = (((1 << 24) - 1) << d) - (1 << 23)
        opposite_bound = opposite_maximum // (1 << d) + 1
        assert opposite_bound == (1 << 24) - (1 << (23 - d))
        assert opposite_bound < (1 << 24)
        row.update(opposite_maximum_N=opposite_maximum, opposite_top_shift=d,
                   opposite_q_upper=opposite_bound)
    rows.append(row)
result = {'checked_utc': datetime.now(timezone.utc).isoformat(),
          'source_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
          'scope': 'Exact integer constants for all 8 permitted d values, including all 4 residues in the d=0 one-bit formula. Paper-bound arithmetic check, not Lean or native-cast validation.',
          'rows': rows, 'Lean': 'NOT_RUN'}
(HERE / 'threshold-arithmetic-check.json').write_bytes((json.dumps(result, indent=2) + '\n').encode('utf-8'))
print(json.dumps(result, indent=2))
