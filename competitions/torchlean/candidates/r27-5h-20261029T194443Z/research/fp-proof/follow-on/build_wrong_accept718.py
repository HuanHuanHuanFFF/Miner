from pathlib import Path
from fractions import Fraction
import datetime
import hashlib
import importlib.util
import json
import math
import struct
import sys

sys.dont_write_bytecode = True
H = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('fp_frozen_formula', H.parent / 'census/fp_replay-frozen.py')
c = importlib.util.module_from_spec(spec)
spec.loader.exec_module(c)
counter_path = H.parent.parent / 'fp-cost/counterexample-radius718.json'
parent = json.loads(counter_path.read_text())
assert parent['at_utc'] < '2026-10-29T23:20:00Z'
x_words = [int(parent['xword_repeated'], 16)] * 510
y_words = [int(w, 16) for w in parent['ywords'][:510]]
prefix_exact = sum(((1 << 23) + (a & 0x7fffff)) * ((1 << 23) + (b & 0x7fffff))
                   for a, b in zip(x_words, y_words))

# The prefix lies in [1024,2048). Binary32 ULP is2^-13, or2^33 units2^-46.
assert (1024 << 46) < prefix_exact < (2047 << 46)
spacing = 1 << 33
half = spacing // 2
midpoint = ((prefix_exact - half) // spacing + 1) * spacing + half
correction = midpoint - 1 - prefix_exact
assert 0 < correction < spacing
shift = max(correction.bit_length() - 24, 4)
coarse = (correction >> shift) << shift
fine = correction - coarse
assert coarse > 0 and fine > 0
coarse_word = c.m.round_ratio(coarse, 1, -46)
fine_word = c.m.round_ratio(fine, 1, -46)

def scaled_word(word):
    exponent = (word >> 23) & 255
    fraction = word & 0x7fffff
    assert 0 < exponent < 255 and word >> 31 == 0
    return Fraction((1 << 23) + fraction) * Fraction(2) ** (exponent - 150 + 46)

assert scaled_word(coarse_word) == coarse
assert scaled_word(fine_word) == fine
x_words += [0x3f800000, 0x3f800000]
y_words += [coarse_word, fine_word]
assert len(x_words) == len(y_words) == 512
assert all(0 < ((w >> 23) & 255) < 255 for w in x_words + y_words)

def round53(value):
    shift = max(value.bit_length() - 53, 0)
    if shift == 0:
        return value
    quotient, remainder = divmod(value, 1 << shift)
    halfway = 1 << (shift - 1)
    return (quotient + (remainder > halfway or (remainder == halfway and quotient & 1))) << shift

exact = accumulator = 0
host = 0.0
widen_matches = True
for a, b in zip(x_words, y_words):
    va = scaled_word(a)
    vb = scaled_word(b)
    product = va * vb / (1 << 46)
    assert product.denominator == 1
    exact += product.numerator
    accumulator = round53(accumulator + product.numerator)
    fa = struct.unpack('<f', struct.pack('<I', a))[0]
    fb = struct.unpack('<f', struct.pack('<I', b))[0]
    host = host + fa * fb
    for word, value in [(a, fa), (b, fb)]:
        exponent = (word >> 23) & 255
        fraction = word & 0x7fffff
        actual_widen_bits = ((exponent + 896) << 52) | (fraction << 29)
        widen_matches &= actual_widen_bits == struct.unpack('<Q', struct.pack('<d', value))[0]

assert exact == midpoint - 1
assert accumulator == midpoint + 2704
assert accumulator - exact == 2705
host_bits = struct.unpack('<Q', struct.pack('<d', host))[0]
model_bits = c.bits64(accumulator << (303 - 46))
assert host_bits == model_bits and widen_matches
q = c.proposal(model_bits)
expected = c.m.round_ratio(exact, 1, -46)
assert q == expected + 1
assert (scaled_word(q) + scaled_word(expected)) / 2 == midpoint
results = []
for offset in [718, 719, 720]:
    radius_units = 1 << (252 + 18 + offset - 1023 + 46)
    low = c.bits64(round53(accumulator - radius_units) << (303 - 46))
    high = c.bits64(round53(accumulator + radius_units) << (303 - 46))
    accepted, reason = c.certify(model_bits, low, high, q)
    radius = math.ldexp(1.0, 252 + 18 + offset - 1023)
    assert struct.unpack('<Q', struct.pack('<d', host - radius))[0] == low
    assert struct.unpack('<Q', struct.pack('<d', host + radius))[0] == high
    results.append({'offset': offset, 'radius_units': radius_units, 'accepted': accepted,
                    'reason': reason, 'lower_endpoint_bits': hex(low), 'upper_endpoint_bits': hex(high)})
assert results[0]['accepted'] and not results[1]['accepted'] and not results[2]['accepted']

def rle_pairs(xs, ys):
    out = []
    for a, b in zip(xs, ys):
        if out and out[-1]['x'] == hex(a) and out[-1]['y'] == hex(b):
            out[-1]['count'] += 1
        else:
            out.append({'count': 1, 'x': hex(a), 'y': hex(b)})
    return out

result = {
    'at_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(),
    'state': 'FINITE_WRONG_ACCEPT_COUNTEREXAMPLE_TO_HYPOTHETICAL_RADIUS718',
    'n': 512, 'H': 252, 'L': 9, 'all_operands_normal': True,
    'arrays_rle_pairs': rle_pairs(x_words, y_words),
    'unit': '2^-46', 'exact_total_units': str(exact), 'midpoint_units': str(midpoint),
    'rounded_sum_units': str(accumulator), 'error_units': 2705,
    'native_sum_bits': hex(model_bits), 'proposed_and_718_accepted_word': hex(q),
    'exact_correct_word': hex(expected), 'adjacent_words_midpoint_verified_exactly': True,
    'offset_outcomes': results,
    'host_IEEE_double_replay_matches_integer_model': True,
    'normal_widen_bit_formula_matches_host_for_all_inputs': True,
    'official_total_integer_for_scale_minus298': str(exact << 252),
    'parent_prefreeze_counter_sha256': hashlib.sha256(counter_path.read_bytes()).hexdigest(),
    'scope': 'Constructed actual bit-checker formula replay plus host IEEE double arithmetic. No Lean/native candidate compilation, no universal proof, no current-champion performance claim. Unlike a bare error-bound violation, this produces an accepted adjacent wrong binary32 word for the hypothetical718 radius.',
    'frozen720_unchanged_and_rejects': True,
    'research_inputs': 'Prefreeze512-term arithmetic witness and existing owned bit-checker formula; no batch9 confirmation data or FP23 timing data used to construct this witness.'
}
(H / 'WRONG-ACCEPT-718.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(result, indent=2))
