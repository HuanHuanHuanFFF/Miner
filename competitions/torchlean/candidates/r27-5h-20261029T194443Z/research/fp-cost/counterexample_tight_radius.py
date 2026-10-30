"""Construct a reproducible all-normal counterexample to radius offset718.

The construction is independent of unseen Pro artifacts and uses the fixed
exact-integer RN64 model. No native Lean timing or correctness is claimed.
"""
from pathlib import Path
import datetime
import hashlib
import json
import struct
from fractions import Fraction
from power_endpoint_model import decode32, round64


def f32(word):
    return struct.unpack("<f", struct.pack("<I", word))[0]


def main():
    n, mantissa = 512, (1 << 24) - 1
    xword = 0x3fffffff
    acc = exact = 0
    ys = []
    # All words lie in [1,2), so no domain exception or subnormal is used.
    for _ in range(n):
        options = []
        for m in range(mantissa - 127, mantissa + 1):
            product = mantissa * m
            z = acc + product
            rounded = round64(z)
            options.append((rounded - z, product, m, rounded))
        error, product, m, rounded = max(options)
        ys.append((127 << 23) | (m - (1 << 23)))
        acc, exact = rounded, exact + product
    h, ell = 252, 9
    # Products above are represented in units2^-46. General model uses2^-298.
    error_units = abs(acc - exact)
    radius718 = Fraction(1 << 11)  # 2^(H+2L-305+46)
    radius719 = Fraction(1 << 12)
    radius720 = Fraction(1 << 13)
    assert error_units > radius718
    assert error_units <= radius719 <= radius720
    native_sum = 0.0
    for y in ys:
        native_sum = native_sum + f32(xword) * f32(y)
    expected = acc * 2.0**-46
    assert struct.pack("<d", native_sum) == struct.pack("<d", expected)
    # Replay again in the independent common2^-298 coefficient model.
    actual = total = 0
    for y in ys:
        product = decode32(xword) * decode32(y)
        assert round64(product) == product
        actual = round64(actual + product)
        total += product
    assert actual == acc << 252 and total == exact << 252
    result = {"at_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
              "state": "VERIFIED_FINITE_COUNTEREXAMPLE_TO_OFFSET718_ONLY",
              "construction_source_sha256": hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
              "n": n, "H": h, "L": ell, "xword_repeated": f"0x{xword:08x}",
              "ywords": [f"0x{y:08x}" for y in ys],
              "all_operands_normal": True, "product_unit_exponent": -46,
              "exact_sum_coefficient": str(exact), "rounded_sum_coefficient": str(acc),
              "absolute_error_coefficient": error_units,
              "radius718_coefficient": int(radius718),
              "radius719_coefficient": int(radius719),
              "radius720_coefficient": int(radius720),
              "native_python_binary64_sum_bits": struct.pack(">d", native_sum).hex(),
              "independent_common_unit_replay": "PASS",
              "limits": "Refutes universal718errorenclosure evenonall-normal inputs; doesnotprove719foralldomains, Leanacceptance or nativeperformance"}
    Path(__file__).with_name("counterexample-radius718.json").write_text(
        json.dumps(result, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(json.dumps({k: v for k, v in result.items() if k != "ywords"}))


if __name__ == "__main__":
    main()
