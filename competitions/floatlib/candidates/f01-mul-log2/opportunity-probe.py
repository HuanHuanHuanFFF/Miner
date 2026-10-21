"""Replay pinned public add generators to locate possible future helper work.

This records integer path frequencies only. It is not a performance benchmark.
"""

from collections import Counter
from datetime import datetime, timezone
from pathlib import Path
import hashlib
import json
import struct

MASK = (1 << 32) - 1
PAIRS = 500_000
SEED = 42


def generate(name, index, word):
    if name == "near-one":
        return (word & 0x807FFFFF) | ((124 + (word >> 23) % 7) << 23)
    if name == "wide-gap":
        exponent = 127 if index % 2 == 0 else 107 - (word >> 23) % 11
        return (word & 0x807FFFFF) | (exponent << 23)
    fraction = word & 0x7FFFFF if index % 2 == 0 else (word & 0x7FFFF8) | ((word >> 27) & 7)
    sign = 0 if index % 2 == 0 else 0x80000000
    return sign | (127 << 23) | fraction


def main():
    classes = {}
    for salt, name in enumerate(("near-one", "wide-gap", "cancel"), 1):
        state = SEED ^ ((salt * 0x9E3779B9) & MASK)
        words = []
        digest = hashlib.sha256()
        for index in range(PAIRS + 1):
            state = (state * 1664525 + 1013904223) & MASK
            word = generate(name, index, state)
            words.append(word)
            digest.update(struct.pack("<I", word))
        log2s = Counter()
        gaps = Counter()
        early_returns = zero_results = 0
        for x, y in zip(words, words[1:]):
            xe, ye = (x >> 23) & 255, (y >> 23) & 255
            assert 0 < xe < 255 and 0 < ye < 255
            xm, ym = (1 << 23) | (x & 0x7FFFFF), (1 << 23) | (y & 0x7FFFFF)
            xs, ys = xe - 1, ye - 1
            gap = abs(xs - ys)
            gaps[gap] += 1
            if gap > 39:
                early_returns += 1
                continue
            if xs <= ys:
                ym <<= ys - xs
            else:
                xm <<= xs - ys
            magnitude = xm + ym if x >> 31 == y >> 31 else abs(xm - ym)
            if magnitude == 0:
                zero_results += 1
            else:
                log2s[magnitude.bit_length() - 1] += 1
        classes[name] = {
            "pairs": PAIRS, "input_words_sha256_little_endian": digest.hexdigest(),
            "gap_histogram": dict(sorted(gaps.items())),
            "log2_input_histogram": dict(sorted(log2s.items())),
            "early_returns": early_returns, "zero_magnitudes": zero_results,
        }
    report = {
        "status": "OBSERVED_FINITE_PUBLIC_GENERATOR_MODEL",
        "executed_at_utc": datetime.now(timezone.utc).isoformat(), "seed": SEED,
        "source_repository": "conjectures-io/conjectures-optimisation-float-kernels",
        "source_commit": "978cc5b445edb9943fd9953b0a9037d97a9f33a8",
        "generator_source": "lean/bench/Bench.lean",
        "generator_git_blob": "6f7315b14015dcb5d836f98cb8320a9cdfb30f3b",
        "classes": classes,
        "scope": "Translated add integer-path frequencies. No Lean execution, checksums or timings.",
    }
    root = Path(__file__).resolve().parent
    (root / "opportunity-result.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report))


if __name__ == "__main__":
    main()
