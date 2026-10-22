#!/usr/bin/env python3
"""Finite binary32 proof-aid checks of independent FPU anchor quantization."""
import json
import random
import secrets
from fractions import Fraction
from pathlib import Path

from verify_transition import L, U, add_words, hexword, one, q_units, rn_word, units


def main():
    seed = secrets.randbits(128)
    rng = random.Random(seed)
    terms = 0
    accepted = 0
    subnormal_terms = 0
    for _ in range(5000):
        Es = rng.randrange(3, 255)
        qu = q_units(Es - 150)
        H = Es << 23
        k = rng.randrange(L, U)
        start = H + (k - L)
        words = []
        total_delta = 0
        for _ in range(rng.randrange(1, 65)):
            Ex = rng.randrange(0, Es - 1)
            word = (Ex << 23) | (rng.getrandbits(23) | 1)
            if rng.randrange(8) == 0:
                word = 0
            words.append(word)
            delta = add_words(H, word) - H
            r = Fraction(units(word), qu)
            s = one(r)
            assert s.d[0] == s.d[1] == delta
            assert 0 <= delta <= (L // 2)
            total_delta += delta
            terms += 1
            subnormal_terms += int(word != 0 and word < L)
        accept = k + total_delta <= U if Es < 254 else k + total_delta < U
        if accept:
            actual = start
            for word in words:
                actual = add_words(actual, word)
            assert units(actual) == (k + total_delta) * qu
            accepted += 1
    examples = []
    for Es, start, x in [(128, 0x40000001, 0x3F800001),
                         (128, 0x40000001, 0x3F000002),
                         (2, 0x01000001, 0x00000001),
                         (3, 0x01800001, 0x00000003)]:
        anchor = Es << 23
        delta = add_words(anchor, x) - anchor
        predicted = start + delta
        actual = add_words(start, x)
        examples.append({"Es": Es, "start": hexword(start), "x": hexword(x),
                         "anchor_delta": delta, "predicted": hexword(predicted),
                         "actual": hexword(actual), "match": predicted == actual})
    result = {"fresh_random_seed_hex": f"{seed:032x}", "blocks": 5000,
              "terms": terms, "subnormal_terms": subnormal_terms,
              "accepted_blocks": accepted, "all_assertions_passed": True,
              "boundary_examples": examples,
              "limitation": "tests exact arithmetic identities, not hardware speed or a given runtime's vectorization"}
    path = Path(__file__).resolve().parent / "anchor_quantization_results.json"
    path.write_text(json.dumps(result, indent=2) + "\n")
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
