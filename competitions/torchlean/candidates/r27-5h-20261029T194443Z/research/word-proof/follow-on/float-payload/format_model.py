"""Finite payload algebra; Python bit transport is not Lean FloatArray evidence."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import random
import struct

HERE = Path(__file__).resolve().parent
MASK64 = (1 << 64)-1
CENTER = 1 << 62


def roundtrip(payload):
    assert 0 <= payload < 1 << 52
    value = struct.unpack('<d', struct.pack('<Q', payload))[0]
    return struct.unpack('<Q', struct.pack('<d', value))[0]


def signed32(x):
    return x if x < 1 << 31 else x-(1 << 32)


def old_value(magnitude, negative, weight_negative):
    p = CENTER-magnitude if negative != weight_negative else CENTER+magnitude
    assert 0 <= p < 1 << 63
    return (p-CENTER)&MASK64


def main():
    rng = random.Random(0x405249)
    counts = {'dense40':0, 'sparse52':0, 'sparse49':0, 'raw_float_bit_transports':0}
    for _ in range(12000):
        magnitude = rng.randrange(1 << 39)
        negative = bool(rng.getrandbits(1))
        z = -magnitude if negative else magnitude
        payload = (1 << 39)+z
        got = roundtrip(payload)
        counts['raw_float_bit_transports'] += 1
        for weight_negative in [False, True]:
            decoded = got-(1 << 39)
            selected = (-decoded if weight_negative else decoded)&MASK64
            assert selected == old_value(magnitude, negative, weight_negative)
            counts['dense40'] += 1
        magnitude = rng.randrange(1 << 31)
        z = -magnitude if negative else magnitude
        index = rng.randrange(1 << 20)
        payload = (index << 32)+(z&0xffffffff)
        got = roundtrip(payload)
        assert got >> 32 == index and signed32(got&0xffffffff) == z
        for weight_negative in [False, True]:
            selected = (-z if weight_negative else z)&MASK64
            assert selected == old_value(magnitude, negative, weight_negative)
            counts['sparse52'] += 1
        counts['raw_float_bit_transports'] += 1
        mantissa = rng.randrange(1 << 24)
        delta = rng.randrange(16)
        payload = mantissa | (delta << 24) | (int(negative) << 28) | (index << 29)
        got = roundtrip(payload)
        assert got >> 29 == index
        decoded_magnitude = (got&0xffffff) << ((got >> 24)&15)
        decoded_negative = bool((got >> 28)&1)
        for weight_negative in [False, True]:
            assert old_value(decoded_magnitude, decoded_negative, weight_negative) == old_value(mantissa << delta, negative, weight_negative)
            counts['sparse49'] += 1
        counts['raw_float_bit_transports'] += 1
    for index in [0, (1 << 20)-1]:
        for z in [0, 1, -1, (1 << 31)-1, -(1 << 31)+1, -(1 << 31)]:
            p = (index << 32)+(z&0xffffffff)
            assert roundtrip(p) == p
            assert p >> 32 == index and signed32(p&0xffffffff) == z
    bad_magnitude = ((1 << 24)-1) << 8
    bad_decoded = signed32(bad_magnitude&0xffffffff)
    assert bad_decoded == -256 and bad_decoded != bad_magnitude
    numeric_one_bits = struct.unpack('<Q', struct.pack('<d', float(1)))[0]
    assert numeric_one_bits != 1
    negative_min = -(1 << 31)
    correct_extend_then_negate = -negative_min
    incorrect_negate32_then_extend = signed32((0-(negative_min&0xffffffff))&0xffffffff)
    assert correct_extend_then_negate != incorrect_negate32_then_extend
    result = {'at_utc':datetime.now(timezone.utc).isoformat(),
              'state':'FINITE_PAYLOAD_FORMAT_AND_RAW_PYTHON_TRANSPORT_NO_LEAN_NATIVE',
              'cases':counts,
              'old_smallNat_bound':{'center':CENTER,'max_input_magnitude_exclusive':1 << 39,'min_possible_old_entry':CENTER-((1 << 39)-1),'max_possible_old_entry':CENTER+(1 << 39)-1,'smallNat_limit_64bit':(1 << 63)-1},
              'counterexamples':{'span8_signed32_truncation':{'true_positive_magnitude':bad_magnitude,'decoded_signed32':bad_decoded,'high_raw_x':(127 << 23)|0x7fffff,'low_raw_x':(119 << 23)|1},'numeric_conversion_is_not_bit_transport':{'payload':1,'numeric_float_bits':numeric_one_bits},'index_overflow':{'index':1 << 20,'minimum_payload':1 << 52,'rejected_by_selected_payload_bound':True},'signed_min_negation_order':{'signed_input':negative_min,'correct_extend_then_negate64':correct_extend_then_negate,'incorrect_negate32_then_extend':incorrect_negate32_then_extend,'scope':'General signed32 codec edge, not a raw span<=7 generated factor. Current WordPayload source extends before applying weight sign.'}},
              'limits':['No actual FloatArray read/write, Lean theorem or new kernel was executed.',
                        'No native load/boxing/cycle count. Old Nat entries are immediate by the declared64bit bound, not per-entry big integers.',
                        'Current public23 generated C was unavailable; oldR26 FloatArray C supports only native-double getter type evidence.',
                        'Dense40 is paused without actual cost evidence; sparse52 may remove an index load only under its stricter input span guard.'],
              'source_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest()}
    (HERE/'format-model.json').write_text(json.dumps(result,indent=2),encoding='utf8')
    print(json.dumps({'cases':counts,'bad_span8':bad_decoded,'at_utc':result['at_utc']}))


if __name__ == '__main__':
    main()
