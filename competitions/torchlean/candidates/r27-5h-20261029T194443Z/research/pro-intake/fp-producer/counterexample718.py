#!/usr/bin/env python3
"""Exact-integer counterexample to radius constant 718 (NOT to 719/720).

All input words are positive normal binary32, with raw exponent 127.
Every exact product is p * 2**-46 for an integer p < 2**48.
All partial sums are normal binary64 and finite, so rounding their integer
coefficients to 53 significant bits models RN-even binary64 addition exactly.
No host floating point, numpy, Lean, native benchmark, or external package.
"""

import json


def rn53_integer(x):
    """RN-even to 53 significant bits, on an integer lattice."""
    if x == 0:
        return 0
    sign = -1 if x < 0 else 1
    v = abs(x)
    shift = max(0, v.bit_length() - 53)
    if shift == 0:
        return x
    q, rem = divmod(v, 1 << shift)
    half = 1 << (shift - 1)
    if rem > half or (rem == half and (q & 1)):
        q += 1
    return sign * (q << shift)


def mantissa_at_exponent127(word):
    assert word >> 31 == 0
    assert (word >> 23) & 255 == 127
    return (1 << 23) + (word & 0x7FFFFF)


def encode_accumulator_bits(integer_coefficient):
    # Actual real value is integer_coefficient * 2**-46.
    assert integer_coefficient > 0
    lead = integer_coefficient.bit_length() - 1
    shift = lead - 52
    assert shift >= 0
    assert integer_coefficient % (1 << shift) == 0
    mant = integer_coefficient >> shift
    exponent = lead - 46
    assert -1022 <= exponent <= 1023
    return ((exponent + 1023) << 52) | (mant - (1 << 52))


def main():
    a_word = 0x3FFFFFFF
    b_runs = [(128, 0x3FFFFFFF), (128, 0x3FFFFFFB), (256, 0x3FFFFFF7)]
    a = mantissa_at_exponent127(a_word)
    exact_sum = accumulator = n = 0
    checkpoints = []
    for count, b_word in b_runs:
        b = mantissa_at_exponent127(b_word)
        p = a * b
        assert 0 < p < (1 << 48)
        for _ in range(count):
            exact_sum += p
            accumulator = rn53_integer(accumulator + p)
            n += 1
        checkpoints.append({
            "n": n,
            "exact_sum_units": exact_sum,
            "accumulator_units": accumulator,
            "signed_error_units": accumulator - exact_sum,
        })
    H = 126 + 126
    L = (n - 1).bit_length()
    # Radius encoded with constant C is 2**(H+2L+C-1023).
    # The model's unit is 2**-46, so add 46 to obtain integer units.
    radii = {str(C): 1 << (H + 2 * L + C - 1023 + 46)
             for C in (718, 719, 720)}
    error = abs(accumulator - exact_sum)
    assert n == 512 and H == 252 and L == 9
    assert exact_sum == 144115127946316800
    assert accumulator == 144115127946318880
    assert error == 2080
    assert error > radii["718"] == 2048
    assert error < radii["719"] == 4096
    assert error < radii["720"] == 8192
    # The helper's proposal is only a raw-bit proposal. This checks the optional
    # narrower proposal guard, without proving or executing the consumer.
    bits = encode_accumulator_bits(accumulator)
    magnitude = (((((bits & 0x7FFFFFFFFFFFFFFF) + 0x10000000) >> 29)
                  & 0xFFFFFFFF) - 0xC0000000) & 0x7FFFFFFF
    proposal = (((bits >> 32) & 0x80000000) | magnitude)
    proposal_e = (proposal >> 23) & 255
    proposal_f = proposal & 0x7FFFFF
    assert 2 <= proposal_e <= 253 and proposal_f != 0
    print(json.dumps({
        "status": "EXACT_INTEGER_COUNTEREXAMPLE_TO_718_ONLY",
        "n": n, "H": H, "L": L,
        "a_word_repeated": f"0x{a_word:08x}",
        "b_word_runs": [{"count": count, "word": f"0x{w:08x}"}
                        for count, w in b_runs],
        "unit": "2^-46",
        "exact_sum_units": exact_sum,
        "accumulator_units": accumulator,
        "accumulator_binary64_bits": f"0x{encode_accumulator_bits(accumulator):016x}",
        "helper_proposal_bits": f"0x{proposal:08x}",
        "proposal_passes_E2_253_fraction_nonzero": True,
        "error_units": error,
        "radius_units_by_constant": radii,
        "block_checkpoints": checkpoints,
        "scope": "Refutes the 718 producer radius. Does not assert a false-positive consumer result.",
    }, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()

