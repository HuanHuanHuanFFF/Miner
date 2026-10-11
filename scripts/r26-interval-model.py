"""Bounded model of #552 D forward sampled relaxations; not a parser or gate.

Run with the system Python. Reads the pinned reference only and writes one JSON
receipt under evidence/round26/interval-review. No native compiler or CI calls.
"""
from __future__ import annotations

import ast
import hashlib
import json
import random
import re
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "references/round24-public-552/parse.rs"
EXPECTED_SHA = "5adaaeac471b86128778bf6b67f786542f5c8e079adbf1160f0502309f7befb9"
U32 = (1 << 32) - 1
INF = 0x3FFFFFFF
UNREACHED = INF << 32


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    assert sha(SOURCE) == EXPECTED_SHA, "Reference changed; review source before rerunning"
    source = SOURCE.read_text(encoding="utf-8")
    lbase = ast.literal_eval(re.search(r"pub const LBASE:.*?=\s*(\[.*?\]);", source, re.S)[1])
    lextra = ast.literal_eval(re.search(r"pub const LEXTRA:.*?=\s*(\[.*?\]);", source, re.S)[1])
    dextra = ast.literal_eval(re.search(r"pub const DEXTRA:.*?=\s*(\[.*?\]);", source, re.S)[1])
    knobs = ast.literal_eval(re.search(r"pub const D_KNOBS:.*?=\s*(\[.*?\]);", source, re.S)[1])
    flens = sorted({row[8] for row in knobs})
    assert flens == [8, 16]
    lsym = [0] * 512
    code = 0
    for length in range(259):
        if code < 28 and length >= lbase[code + 1]:
            code += 1
        lsym[length] = code
    ends = [length for length in range(3, 259) if length == 258 or lsym[length] != lsym[length + 1]]

    def next_table(flen: int) -> list[int]:
        result = []
        for length in range(512):
            if length < flen or length >= 257:
                result.append(length + 1)
            else:
                end = length + 1
                while end < 258 and lsym[end + 1] == lsym[length + 1]:
                    end += 1
                result.append(end)
        return result

    def sampled(lo: int, hi: int, nxt: list[int]) -> list[int]:
        result = []
        length = lo
        while length < hi:
            result.append(length)
            length = nxt[length % 512]
        if hi >= lo:
            result.append(hi)
        return result

    def endpoint_formula(lo: int, hi: int, flen: int) -> list[int]:
        if hi < lo:
            return []
        return sorted({lo, hi} | set(range(lo, min(hi, flen) + 1)) | {e for e in ends if max(lo, flen) < e < hi})

    def packed(base: int, price: int, distance: int, length: int) -> int:
        return (((base + price) & U32) << 32) | (distance << 9) | length

    exhaustive = []
    for flen in flens:
        nxt = next_table(flen)
        pairs = 0
        maximum_long_domain_visits = 0
        for lo in range(3, 259):
            for hi in range(3, 259):
                actual = sampled(lo, hi, nxt)
                assert actual == endpoint_formula(lo, hi, flen), (flen, lo, hi)
                assert len(actual) == len(set(actual))
                per_code = {}
                for length in actual:
                    if length > flen:
                        per_code[lsym[length]] = per_code.get(lsym[length], 0) + 1
                maximum_long_domain_visits = max(maximum_long_domain_visits, max(per_code.values(), default=0))
                pairs += 1
        assert maximum_long_domain_visits <= 2
        exhaustive.append({"flen": flen, "all_ordered_lo_hi_pairs": pairs,
                           "domain": "lo, hi in 3..258 inclusive, including empty hi < lo",
                           "max_visits_in_one_length_code_above_flen": maximum_long_domain_visits,
                           "samples_3_258": sampled(3, 258, nxt),
                           "samples_19_22": sampled(19, 22, nxt)})

    rng = random.Random(260012)
    random_cases = 5000
    for case in range(random_cases):
        flen = rng.choice(flens)
        nxt = next_table(flen)
        lo, hi = rng.randrange(3, 259), rng.randrange(3, 259)
        start = rng.choice([0, 1, 8190, 8191, 8192, 16383])
        base = rng.choice([0, 1, INF - 1, INF, U32 - 1, U32, rng.randrange(1 << 32)])
        distance = rng.randrange(1, 32769)
        prices = [rng.randrange(1 << 32) for _ in range(29)]
        old = {((start + length) % 8192): rng.randrange(1 << 64) for length in range(3, 259)}
        actual, formula = old.copy(), old.copy()
        for length in sampled(lo, hi, nxt):
            slot = (start + length) % 8192
            actual[slot] = min(actual[slot], packed(base, prices[lsym[length]], distance, length))
        for length in endpoint_formula(lo, hi, flen):
            slot = (start + length) % 8192
            formula[slot] = min(formula[slot], packed(base, prices[lsym[length]], distance, length))
        assert actual == formula, case

    samples = sampled(19, 22, next_table(16))
    dense_extra = sorted(set(range(19, 23)) - set(samples))
    assert dense_extra == [20, 21]
    dense_original = UNREACHED
    dense_changed = packed(0, 1, 1, 20)
    assert dense_changed < dense_original
    # A same-code [lo, hi] need not contain its code endpoint: both endpoints matter.
    assert sampled(19, 21, next_table(16)) == [19, 21]
    # Tie: literal first; then smaller distance; then shorter length / newer start.
    assert packed(0, 7, 0, 0) < packed(0, 7, 1, 3)
    assert packed(0, 7, 1, 258) < packed(0, 7, 2, 3)
    assert packed(0, 7, 2, 19) < packed(0, 7, 2, 20)
    # Sorting unwrapped bases before adding a common length price is unsound.
    assert 0 < U32 and ((0 + 1) & U32) > ((U32 + 1) & U32)
    # A deferred event must freeze the emission-time price, not consult the new table.
    old_event, competitor, new_event = packed(0, 32, 1, 19), packed(0, 50, 1, 19), packed(0, 80, 1, 19)
    assert old_event < competitor < new_event
    # open_chunk clears future arrivals; stale epoch events cannot be applied later.
    assert min(UNREACHED, packed(0, 7, 1, 20)) != UNREACHED
    # back_best uses strict subtotal < INF, first t on ties, before distance cost.
    best_t, best_value = 0, INF
    for t, value in enumerate([10, 10], 1):
        if value < best_value:
            best_t, best_value = t, value
    assert best_t == 1
    assert not INF < INF
    literal_bound = 320
    length_bound = literal_bound + 16 * max(lextra)
    distance_bound = literal_bound + 16 * max(dextra)
    proposed_arrival_bound = literal_bound * 4096 + length_bound + distance_bound
    assert (length_bound, distance_bound, proposed_arrival_bound) == (400, 528, 1311648)
    assert proposed_arrival_bound < INF

    receipt = {
        "status": "VERIFIED_BOUNDED_HELPER_MODEL_ONLY",
        "generated_at_utc": datetime.now(timezone.utc).isoformat(),
        "source": {"path": SOURCE.relative_to(ROOT).as_posix(), "sha256": sha(SOURCE),
                   "lean_path": "references/round24-public-552/Parse.lean",
                   "lean_sha256": sha(ROOT / "references/round24-public-552/Parse.lean")},
        "script_sha256": sha(Path(__file__)),
        "sampling": {"D_KNOBS_flens": flens, "length_code_ends": ends, "exhaustive": exhaustive,
                     "all_pairs_total": sum(x["all_ordered_lo_hi_pairs"] for x in exhaustive)},
        "packed_differential": {"seed": 260012, "cases": random_cases, "ring": 8192,
                                "start_positions": [0, 1, 8190, 8191, 8192, 16383],
                                "costs": "u32 including deliberate wrapping and arbitrary same-code prices",
                                "purpose": "endpoint formula vs exact nextl traversal, not an optimized implementation"},
        "counterexamples": {
            "dense_interval_changes_edge_set": {"lo": 19, "hi": 22, "flen": 16,
                                                 "original_lengths": samples, "new_lengths": dense_extra,
                                                 "at_length_20_original_cell": dense_original,
                                                 "at_length_20_dense_cell": dense_changed},
            "only_global_endpoints_loses_edges": {"lo": 19, "hi": 21, "original_lengths": [19, 21]},
            "tie": "equal cost: literal, then lower distance, then shorter length; fixed destination means newer source",
            "base_min_before_common_add": {"bases": [0, U32], "common_price": 1, "wrapped_totals": [1, 0]},
            "generation_price_must_be_frozen": {"old_price": 32, "competing_price": 50, "new_price": 80},
            "epoch_reset": "an old pending price 7 arrival must not survive open_chunk reset to UNREACHED",
            "back_best_tie": {"subtotals": [10, 10], "selected_t": best_t, "strict_initial_cutoff": INF},
        },
        "paper_bound_for_D_only": {
            "status": "INFERRED_REACHABLE_STATE_INDUCTION_NOT_FORMALIZED",
            "numeric_arithmetic_checked": True,
            "literal_price_bound": literal_bound, "length_price_bound": length_bound,
            "distance_price_bound": distance_bound, "coarse_arrival_bound": proposed_arrival_bound,
            "premises": ["d_parse fixes huff=0; costs_from clamps symbol prices to 8..320",
                         "every current-chunk processed position is reachable via literal edges",
                         "chunk age is bounded by CHUNK=4096; skip resets chunk",
                         "backward-extension reads stay within the current chunk"],
            "scope": "A proof route for D-specific no-wrap simplification; the Python model does not prove reachability."
        },
        "limits": ["This models helper semantics on bounded lengths, not reachable whole-parser input states.",
                   "No Rust or Lean compile; no official extraction, obligations, gate, codec round trip, or timing.",
                   "No event queue implementation; no proof of full-parser byte identity or speed.",
                   "No public corpus frequency or stage-cost claims; route_b owns that separate diagnostic."]
    }
    output = ROOT / "evidence/round26/interval-review/model-receipt.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(receipt, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"status": receipt["status"], "all_pairs": receipt["sampling"]["all_pairs_total"],
                      "random_cases": random_cases, "samples_3_258": {x["flen"]: len(x["samples_3_258"]) for x in exhaustive},
                      "receipt": output.relative_to(ROOT).as_posix()}, ensure_ascii=False))


if __name__ == "__main__":
    main()
