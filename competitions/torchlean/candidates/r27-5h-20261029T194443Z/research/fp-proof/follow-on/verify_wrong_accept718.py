"""Read-only second implementation: exact Fraction cells plus host IEEE operations."""
import sys
sys.dont_write_bytecode = True
from pathlib import Path
from fractions import Fraction
import argparse
import hashlib
import json
import struct

parser = argparse.ArgumentParser()
parser.add_argument('--witness', type=Path, default=Path(__file__).with_name('WRONG-ACCEPT-718.json'))
args = parser.parse_args()
raw = args.witness.read_bytes()
witness = json.loads(raw)

def decode32(word):
    exponent = (word >> 23) & 255
    fraction = word & 0x7fffff
    assert 0 < exponent < 255
    sign = -1 if word >> 31 else 1
    return sign * Fraction((1 << 23) + fraction) * Fraction(2) ** (exponent - 150)

def decode64(word):
    exponent = (word >> 52) & 2047
    fraction = word & ((1 << 52) - 1)
    assert 0 < exponent < 2047
    sign = -1 if word >> 63 else 1
    return sign * Fraction((1 << 52) + fraction) * Fraction(2) ** (exponent - 1075)

def float32(word):
    return struct.unpack('<f', struct.pack('<I', word))[0]

def float64(word):
    return struct.unpack('<d', struct.pack('<Q', word))[0]

def bits64(value):
    return struct.unpack('<Q', struct.pack('<d', value))[0]

exact = Fraction(0)
native_sum = 0.0
n = 0
peak_x = peak_y = 0
for row in witness['arrays_rle_pairs']:
    x = int(row['x'], 16)
    y = int(row['y'], 16)
    vx, vy = decode32(x), decode32(y)
    peak_x = max(peak_x, ((x >> 23) & 255) - 1)
    peak_y = max(peak_y, ((y >> 23) & 255) - 1)
    for _ in range(row['count']):
        exact += vx * vy
        native_sum = native_sum + float32(x) * float32(y)
        n += 1
assert n == 512
H = peak_x + peak_y
L = (n - 1).bit_length()
assert (H, L) == (252, 9)
s_word = bits64(native_sum)
assert s_word == int(witness['native_sum_bits'], 16)
assert exact * (1 << 46) == int(witness['exact_total_units'])

# Re-evaluate the actual proposal's integer operations, not the stored proposal.
magnitude = (((((s_word & 0x7fffffffffffffff) + 0x10000000) & ((1 << 64) - 1)) >> 29) & 0xffffffff)
magnitude = (magnitude - 0xc0000000) & 0x7fffffff
q = ((s_word >> 32) & 0x80000000) | magnitude
q_lower = q - 1
assert q == int(witness['proposed_and_718_accepted_word'], 16)
assert q_lower == int(witness['exact_correct_word'], 16)
assert q >> 31 == 0
E = (q >> 23) & 255
F = q & 0x7fffff
assert 2 <= E <= 253 and F != 0
v_lower, v_upper = decode32(q_lower), decode32(q)
midpoint = (v_lower + v_upper) / 2
assert v_lower < exact < midpoint < v_upper
# This proves q_lower is the nearest binary32 neighbor, with no Float64-to-Float32 double rounding.
assert exact - v_lower < v_upper - exact
ulp = v_upper - v_lower
base = ((E + 896) << 52) | (F << 29)
lower_word = base - (1 << 28)
upper_word = base + (1 << 28)
assert decode64(lower_word) == midpoint
assert decode64(upper_word) == midpoint + ulp

outcomes = []
for offset in [718, 719, 720]:
    radius_word = (H + 2 * L + offset) << 52
    radius = float64(radius_word)
    lo, hi = bits64(native_sum - radius), bits64(native_sum + radius)
    # All words are positive finite here, so unsigned order and the XOR order key agree.
    assert 0 < ((lo >> 52) & 2047) < 2047
    assert 0 < ((hi >> 52) & 2047) < 2047
    assert lo >> 63 == hi >> 63 == 0
    raw_accept = lower_word < lo and hi < upper_word
    real_accept = midpoint < decode64(lo) and decode64(hi) < midpoint + ulp
    assert raw_accept == real_accept
    recorded = next(x for x in witness['offset_outcomes'] if x['offset'] == offset)
    assert raw_accept == recorded['accepted']
    assert lo == int(recorded['lower_endpoint_bits'], 16)
    assert hi == int(recorded['upper_endpoint_bits'], 16)
    outcomes.append({'offset': offset, 'accepts': raw_accept})

assert [x['accepts'] for x in outcomes] == [True, False, False]
print(json.dumps({
    'status': 'READ_ONLY_FRACTION_AND_HOST_IEEE_VERIFICATION_PASS',
    'witness_sha256': hashlib.sha256(raw).hexdigest(),
    'n': n, 'H': H, 'L': L,
    'exact_nearest_word': hex(q_lower), 'actual_proposal_word': hex(q),
    'offset_outcomes': outcomes,
    'file_writes': 0,
    'scope': 'Second finite implementation, not Lean acceptance or native candidate execution.'
}, indent=2))
