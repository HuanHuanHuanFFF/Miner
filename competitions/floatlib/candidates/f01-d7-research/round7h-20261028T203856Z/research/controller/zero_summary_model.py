"""A valid guard/summary mismatch witness, not a theorem counterexample."""
from fractions import Fraction
from pathlib import Path
import hashlib
import json
from midpoint_word_model import value32, cell_words, value64, dyadic

pairs = [(0, 0x7f7fffff), (0x30800000, 0x30800000)]
target = sum(value32(a) * value32(b) for a, b in pairs)
assert target == dyadic(1, -60)
proposal = 0x21800000
lo_word, hi_word = cell_words(proposal)
lo, hi = value64(lo_word), value64(hi_word)
indices = [max(0, (a >> 23 & 255) - 1) + max(0, (b >> 23 & 255) - 1) for a, b in pairs]
nonzero = [i for (a, b), i in zip(pairs, indices) if value32(a) * value32(b) != 0]
rows = []
for name, h in [('current_pairguard_all_indices', max(indices)),
                ('nonzero_product_summary_not_yet_linked', max(nonzero))]:
    radius = dyadic(1, h + 2 - 303)  # length2, L1
    lower, upper = target - radius, target + radius
    # Each endpoint here has <=50 significand bits, and is finite normal64.
    for x in (lower, upper):
        n, d = x.numerator, x.denominator
        while n and n % 2 == 0:
            n //= 2
        assert abs(n).bit_length() <= 53
        assert d.bit_length() < 1075
    rows.append({'summary': name, 'H': h, 'radius': str(radius),
                 'strict_certificate_accepts': lo < lower and upper < hi})
assert rows[0]['strict_certificate_accepts'] is False
assert rows[1]['strict_certificate_accepts'] is True
result = {'scope': 'Exact compatible-input witness for coverage loss; not performance or unsoundness',
          'pairs_raw32': [[hex(a), hex(b)] for a, b in pairs],
          'exact_target': str(target), 'proposal': hex(proposal), 'L': 1,
          'pair_indices': indices, 'rows': rows,
          'conclusion': 'dot1 guard is sound with H253. It cannot justify an H192 summary that ignores zero products. Such a runtime summary needs a different proven guard.',
          'script_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
Path(__file__).with_name('zero-summary-model-results.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({'H_all': rows[0]['H'], 'H_nonzero': rows[1]['H'], 'acceptance': [x['strict_certificate_accepts'] for x in rows]}))
