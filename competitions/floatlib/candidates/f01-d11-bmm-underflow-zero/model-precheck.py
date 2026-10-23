"""Finite exact-integer boundary diagnostic; never a replacement for Lean/gate."""
from datetime import datetime, timezone
from hashlib import sha256
from pathlib import Path
import json

here = Path(__file__).resolve().parent
threshold = 0x16000000

def small(word):
    return (word & 0x7fffffff) < threshold

def product_word(a, b):
    ex, ey = (a >> 23) & 255, (b >> 23) & 255
    assert ex != 255 and ey != 255
    mx = (a & 0x7fffff) | (0x800000 if ex else 0)
    my = (b & 0x7fffff) | (0x800000 if ey else 0)
    scale = (ex - 1 if ex else 0) + (ey - 1 if ey else 0)
    shift = 149 - scale
    assert shift > 0
    product = mx * my
    quotient, remainder = divmod(product, 1 << shift)
    half = 1 << (shift - 1)
    rounded = quotient + (remainder > half or (remainder == half and quotient % 2 == 1))
    assert rounded < 0x800000
    return ((a ^ b) & 0x80000000) | rounded

words = [(sign << 31) | (e << 23) | frac
         for sign in range(2) for e in range(44)
         for frac in (0, 1, 0x3fffff, 0x7fffff)]
pair_count = 0
for a in words:
    assert small(a)
    assert ((a >> 23) & 255) <= 43
    for b in words:
        result = product_word(a, b)
        assert result in (0, 0x80000000)
        pair_count += 1

rejected = [0x16000000, 0x96000000, 0x7f800000, 0xff800000, 0x7fc00000,
            0xffc00000, 0x7f800001, 0xffffffff]
assert all(not small(w) for w in rejected)
assert small(0) and small(0x80000000)
assert small(0x15ffffff) and small(0x95ffffff)

upstream = here.parent.parent / 'research/astra-collab-20261022-r6/web/R6-W01/original-extracted/R6-W01/upstream/FiniteProof.lean'
report = {
    'state': 'PASS_FINITE_INTEGER_BOUNDARY_DIAGNOSTIC_ONLY',
    'updated_at_utc': datetime.now(timezone.utc).isoformat(),
    'kernel_sha256': sha256((here / 'Kernel.lean').read_bytes()).hexdigest(),
    'sampled_input_words': len(words),
    'sampled_signed_products': pair_count,
    'rejected_special_and_threshold_words': [f'{w:08x}' for w in rejected],
    'maximum_accepted_positive_word': '15ffffff',
    'maximum_accepted_negative_magnitude_word': '95ffffff',
    'finiteScale_proof_source': str(upstream.resolve()),
    'finiteScale_proof_source_sha256': sha256(upstream.read_bytes()).hexdigest(),
    'finiteScale_source_license_author': 'MIT; Copyright2026 FloatLib; Authors FloatLib Team; source header inspected',
    'scope': 'Exact integer subnormal quantization only, four fractions for every accepted exponent/sign and all sampled pairs. Does not execute actual ExecFloat.mul, add, Lean or baseline.',
    'Lean': 'NOT_RUN',
    'full_gate_checksum_axioms': 'NOT_RUN',
    'performance': 'UNKNOWN',
}
(here / 'model-precheck.json').write_text(json.dumps(report, indent=2) + '\n', encoding='utf-8')
print(json.dumps({k: report[k] for k in ('state', 'kernel_sha256', 'sampled_input_words', 'sampled_signed_products')}))
