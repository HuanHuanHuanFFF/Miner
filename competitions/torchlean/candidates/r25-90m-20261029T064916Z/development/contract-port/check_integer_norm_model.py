"""Finite independent numeric model of integer row moments, not a Lean gate."""
from pathlib import Path
from fractions import Fraction
import hashlib
import json
import random
import struct

HERE = Path(__file__).resolve().parent
SEED = 20261029


def key(word: int) -> int:
    exp = (word >> 23) & 255
    mant = word & 0x7fffff
    if exp:
        mant += 1 << 23
    value = mant << max(0, exp - 1)
    return -value if word >> 31 else value


def native_fraction(word: int) -> Fraction:
    # Every finite binary32 value is exactly representable by Python binary64.
    value = struct.unpack("<f", struct.pack("<I", word))[0]
    return Fraction.from_float(value)


def main() -> None:
    rng = random.Random(SEED)
    directed = [0, 0x80000000, 1, 0x80000001, 0x007fffff, 0x807fffff,
                0x00800000, 0x80800000, 0x3f800000, 0xbf800000,
                0x7f7fffff, 0xff7fffff, 0x3f000001, 0xbf000001]
    words = directed[:]
    while len(words) < 1038:
        w = rng.getrandbits(32)
        if (w >> 23) & 255 != 255:
            words.append(w)
    scale = Fraction(1, 1 << 149)
    for w in words:
        assert key(w) * scale == native_fraction(w), hex(w)
    groups = []
    for n in [1, 2, 3, 7, 16, 31, 128]:
        for case in range(12):
            row = [words[rng.randrange(len(words))] for _ in range(n)]
            if case == 0:
                row = [directed[i % len(directed)] for i in range(n)]
            values = list(map(native_fraction, row))
            mean = sum(values, Fraction()) / n
            variance = sum(((v - mean) ** 2 for v in values), Fraction()) / n
            total = sum(map(key, row))
            square = sum(key(w) * key(w) for w in row)
            fast_mean = total * scale / n
            second = square * scale * scale / n
            fast_variance = second - fast_mean * fast_mean
            assert fast_mean == mean
            assert fast_variance == variance
            assert second == sum((v * v for v in values), Fraction()) / n
            groups.append({"n": n, "case": case, "sha256": hashlib.sha256(
                struct.pack("<" + "I" * n, *row)).hexdigest()})
    source = HERE / "integer-norm/Kernel.lean"
    result = {"status": "FINITE_MODEL_PASS", "seed": SEED, "word_cases": len(words),
              "row_cases": len(groups), "groups": groups,
              "words_sha256": hashlib.sha256(struct.pack("<" + "I" * len(words), *words)).hexdigest(),
              "candidate_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
              "scope": "Python exact Fraction model versus independent IEEE binary32 decode; not actual Lean producer execution",
              "lean": "NOT_RUN", "native_candidate": "NOT_RUN", "gate": "NOT_RUN",
              "sqrt_and_output_rounding": "NOT_EXERCISED"}
    (HERE / "integer-norm-model.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({k: v for k, v in result.items() if k != "groups"}, indent=2))


if __name__ == "__main__":
    main()
