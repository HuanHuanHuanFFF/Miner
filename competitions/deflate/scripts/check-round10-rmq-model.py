"""Lightweight differential model for the Round 10 eight-cell RMQ helper.

This checks the generated Rust arithmetic and sweep invariant against the scalar
minimum. It does not compile Rust, check Lean totality, or replace the official gate.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import random
from pathlib import Path
from typing import Callable

ROOT = Path(__file__).resolve().parents[1]
RING = 1024
MIN_BLOCKS = 128
U32 = (1 << 32) - 1
U64 = (1 << 64) - 1
USIZE = U64
D_UNSET = 0x3FFF_FFFF_0000_0000
DEFAULT_OUTPUT = ROOT / "evidence/round10/rmq-review.json"
BUILDER = ROOT / "scripts/build-round10-rmq.py"
CANDIDATE = ROOT / "candidates/r10-rmq8/parse.rs"
SCALAR = ROOT / "candidates/r9-block-scalar/parse.rs"
CANDIDATE_LEAN = ROOT / "candidates/r10-rmq8/Parse.lean"
SCALAR_LEAN = ROOT / "candidates/r9-block-scalar/Parse.lean"
MANIFEST = ROOT / "candidates/r10-rmq8/manifest.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def cell(cost: int, choice: int = 0) -> int:
    return ((cost & U32) << 32) | (choice & U32)


def word(value: int) -> int:
    return value & U64


def price_ends(lc: list[int], ends: list[int]) -> None:
    q = 512
    stop = 512
    while q > 0:
        q -= 1
        if q < 511 and lc[q] != lc[q + 1]:
            stop = q + 1
        ends[q] = stop


def commit(ring: list[int], mins: list[int], p: int) -> None:
    if p % 8 == 0:
        best = U64
        k = 0
        while k < 8:
            q = word(p + k)
            value = ((ring[q % RING] >> 32) << 3) | k
            if value < best:
                best = value
            k += 1
        mins[(p // 8) % MIN_BLOCKS] = best


def cost_at(lc: list[int], ring: list[int], p: int, length: int) -> int:
    q = word(p + length)
    return word((ring[q % RING] >> 32) + lc[length % 512])


def scalar_best(lc: list[int], ring: list[int], p: int, lo: int, e: int) -> int:
    """The parent's selected d_best_len behavior, including its old invalid-range fallback."""
    if not (lo < e and e <= 259):
        best = U64
        l = lo
        while l < e:
            value = word((cost_at(lc, ring, p, l) << 9) | l)
            if value < best:
                best = value
            l += 1
        return best
    best = cost_at(lc, ring, p, lo)
    best_len = lo
    l = lo + 1
    while l < e:
        value = cost_at(lc, ring, p, l)
        if value < best:
            best = value
            best_len = l
        l += 1
    return word((best << 9) | best_len)


def rmq_best(lc: list[int], ring: list[int], mins: list[int], ends: list[int],
             p: int, lo: int, e: int, counters: dict[str, int] | None = None) -> int:
    if lo >= e or e > 259:
        return scalar_best(lc, ring, p, lo, e)
    best = U64
    l = lo
    outer_steps = 0
    while l < e:
        outer_steps += 1
        if outer_steps > e - lo + 1:
            raise AssertionError("outer segment loop did not progress")
        raw_stop = ends[l % 512]
        stop = min(raw_stop, e) if raw_stop > l else l + 1
        if stop <= l:
            raise AssertionError("price segment did not advance")
        price = lc[l % 512]
        inner_steps = 0
        while l < stop:
            inner_steps += 1
            if inner_steps > stop - lo + 1:
                raise AssertionError("within-segment loop did not progress")
            q = word(p + l)
            if q % 8 == 0 and stop - l >= 8:
                packed_min = mins[(q // 8) % MIN_BLOCKS]
                offset = packed_min % 8
                selected_len = l + offset
                if selected_len >= stop:
                    raise AssertionError(("summary offset escapes its constant-price run",
                                          p, lo, e, l, stop, offset))
                value = word(((packed_min >> 3) + price) << 9 | selected_len)
                l += 8
                if counters is not None:
                    counters["summary_queries"] = counters.get("summary_queries", 0) + 1
            else:
                value = word(((ring[q % RING] >> 32) + price) << 9 | l)
                l += 1
                if counters is not None:
                    counters["scalar_tail_queries"] = counters.get("scalar_tail_queries", 0) + 1
            if value < best:
                best = value
    return best


def expected_ends(lc: list[int], index: int) -> int:
    stop = index + 1
    while stop < 512 and lc[stop] == lc[index]:
        stop += 1
    return stop


def random_lc(rng: random.Random) -> list[int]:
    values = [0, 1, 2, 3, 7, 15, 255, 0x7FFF_FFFF, U32]
    result = [0] * 512
    i = 0
    while i < len(result):
        run = rng.randint(1, 47)
        price = rng.choice(values)
        end = min(len(result), i + run)
        result[i:end] = [price] * (end - i)
        i = end
    return result


def context(lc: list[int], p: int, max_end: int,
            cost_for_offset: Callable[[int], int]) -> tuple[list[int], list[int], list[int]]:
    ring = [D_UNSET] * RING
    mins = [0] * MIN_BLOCKS
    for offset in range(-8, max_end + 8):
        q = word(p + offset)
        payload = word((q * 0x9E37_79B1 + offset * 0x85EB_CA77) >> 3)
        ring[q % RING] = cell(cost_for_offset(offset), payload)
    for offset in range(max(0, max_end - 7)):
        q = word(p + offset)
        if q % 8 == 0 and offset + 7 < max_end:
            commit(ring, mins, q)
    ends = [0] * 512
    price_ends(lc, ends)
    return ring, mins, ends


def price_fixture(name: str, rng: random.Random) -> tuple[list[int], Callable[[int], int]]:
    if name == "constant-price-ties":
        lc = [17] * 512
        return lc, lambda _offset: 42
    if name == "segmented-cross-price-ties":
        cuts = [3, 4, 7, 8, 15, 16, 31, 32, 127, 128, 255, 256, 258, 259, 512]
        lc = [0] * 512
        start = 0
        for part, stop in enumerate(cuts):
            lc[start:stop] = [part % 8] * (stop - start)
            start = stop
        return lc, lambda offset: (10_000 - lc[offset % 512])
    if name == "long-runs-and-extremes":
        boundaries = [0, 3, 11, 19, 27, 35, 67, 131, 195, 259, 512]
        values = [U32, 0, 7, 0x7FFF_FFFF, 1, U32, 255, 2, 0, 3]
        lc = [0] * 512
        for i, (start, stop) in enumerate(zip(boundaries, boundaries[1:])):
            lc[start:stop] = [values[i]] * (stop - start)
        choices = [0, 1, 2, 3, 7, 0x3FFF_FFFE, 0x3FFF_FFFF, U32]
        table = [rng.choice(choices) for _ in range(280)]
        return lc, lambda offset: table[offset % len(table)]
    raise ValueError(name)


def check_price_ends(seed: int) -> dict[str, int]:
    rng = random.Random(seed)
    ends = [0] * 512
    checks = 0
    for cut in range(513):
        lc = [0 if i < cut else 1 for i in range(512)]
        price_ends(lc, ends)  # Reuse the buffer to model d_block price-table changes.
        for i in range(512):
            if ends[i] != expected_ends(lc, i):
                raise AssertionError(("price edge", cut, i, ends[i], expected_ends(lc, i)))
            checks += 1
    for _ in range(256):
        lc = random_lc(rng)
        price_ends(lc, ends)
        for i in range(512):
            if ends[i] != expected_ends(lc, i):
                raise AssertionError(("random price edge", i, ends[i], expected_ends(lc, i)))
            checks += 1
    return {"arrays_checked": 769, "endpoints_checked": checks, "reused_buffer_across_arrays": True}


def check_exhaustive_intervals() -> dict[str, int]:
    rng = random.Random(0x10_8A_2026)
    positions = [0, 1000, 1020, 2044, U64 - 100]
    fixtures = ["constant-price-ties", "segmented-cross-price-ties", "long-runs-and-extremes"]
    comparisons = 0
    summary_queries = 0
    tail_queries = 0
    interval_count = 0
    for position in positions:
        for fixture_name in fixtures:
            lc, cost_fn = price_fixture(fixture_name, rng)
            ring, mins, ends = context(lc, position, 259, cost_fn)
            for lo in range(3, 259):
                for e in range(lo + 1, 260):
                    counts: dict[str, int] = {}
                    expected = scalar_best(lc, ring, position, lo, e)
                    actual = rmq_best(lc, ring, mins, ends, position, lo, e, counts)
                    if actual != expected:
                        raise AssertionError({"fixture": fixture_name, "p": position, "lo": lo,
                                              "e": e, "scalar": expected, "rmq": actual})
                    comparisons += 1
                    interval_count += 1
                    summary_queries += counts.get("summary_queries", 0)
                    tail_queries += counts.get("scalar_tail_queries", 0)
    return {
        "fixtures": fixtures,
        "absolute_positions": positions,
        "intervals_per_position_fixture": sum(1 for lo in range(3, 259) for _e in range(lo + 1, 260)),
        "differential_comparisons": comparisons,
        "summary_queries": summary_queries,
        "scalar_tail_queries": tail_queries,
        "q_crosses_1024_ring_boundary": True,
        "usize_wrap_case_included": True,
    }


def check_random_intervals(seed: int, cases: int, queries_per_case: int) -> dict[str, int]:
    rng = random.Random(seed)
    positions = [0, 1016, 1020, 2044, U64 - 100]
    price_values = [0, 1, 2, 3, 7, 255, 0x7FFF_FFFF, U32]
    cost_values = [0, 1, 2, 7, 0x3FFF_FFFE, 0x3FFF_FFFF, U32]
    comparisons = 0
    for case_id in range(cases):
        lc = random_lc(rng)
        position = positions[case_id % len(positions)]
        table = [rng.choice(cost_values) for _ in range(280)]
        ring, mins, ends = context(lc, position, 259, lambda offset: table[offset % len(table)])
        intervals = set()
        for _ in range(queries_per_case):
            lo = rng.randint(3, 258)
            e = rng.randint(lo + 1, 259)
            intervals.add((lo, e))
        intervals.update({(3, 4), (3, 10), (251, 259), (258, 259)})
        for lo, e in intervals:
            expected = scalar_best(lc, ring, position, lo, e)
            actual = rmq_best(lc, ring, mins, ends, position, lo, e)
            if actual != expected:
                raise AssertionError({"random_case": case_id, "p": position, "lo": lo,
                                      "e": e, "scalar": expected, "rmq": actual})
            comparisons += 1
    return {"seed": seed, "cases": cases, "queries_per_case_requested": queries_per_case,
            "differential_comparisons": comparisons, "price_domain_includes_u32_max": True,
            "cost_domain_includes_unset_and_u32_max": True}


def check_invalid_fallbacks(seed: int) -> dict[str, int]:
    rng = random.Random(seed)
    lc = random_lc(rng)
    table = [rng.choice([0, 1, 7, 0x3FFF_FFFF, U32]) for _ in range(280)]
    position = 1019
    ring, mins, ends = context(lc, position, 268, lambda offset: table[offset % len(table)])
    intervals = [(0, 0), (7, 7), (4, 3), (3, 260), (258, 260), (260, 259), (1, 259)]
    for lo, e in intervals:
        expected = scalar_best(lc, ring, position, lo, e)
        actual = rmq_best(lc, ring, mins, ends, position, lo, e)
        if actual != expected:
            raise AssertionError(("invalid-range fallback", lo, e, expected, actual))
    return {"fallback_intervals_checked": len(intervals), "lo_ge_e": True, "e_above_259": True}


def update_ring_min(ring: list[int], p: int, value: int) -> None:
    slot = p % RING
    if value < ring[slot]:
        ring[slot] = value


def check_backward_pushes(seed: int) -> dict[str, int | bool]:
    rng = random.Random(seed)
    high_node = 2058
    lower_node = high_node - 258
    lc = [0] * 512
    for i in range(512):
        lc[i] = [0, 1, 2, 3, 7, 255, U32][(i // [3, 5, 8, 13, 21, 34, 55][i % 7]) % 7]
    ends = [0] * 512
    price_ends(lc, ends)
    ring = [D_UNSET] * RING
    mins = [0] * MIN_BLOCKS

    def base_cost(position: int) -> int:
        return [2, 80, 900, 0x3FFF_FFFE, 0x3FFF_FFFF, U32][position % 6]

    # Cells above the high node are already final and their aligned summaries are valid.
    for position in range(high_node + 1, high_node + 266):
        ring[position % RING] = cell(base_cost(position), position * 17)
    for position in range(high_node + 1, high_node + 259):
        if position % 8 == 0 and position + 7 < high_node + 266:
            commit(ring, mins, position)

    # A previous, higher node pushes its candidate ends into positions not finalized yet.
    pushes = 0
    for x in range(1, 256):  # len=3, so x <= 258-len as in d_push.
        position = high_node - x
        pushed_cost = word((10_000 + lc[(3 + x) % 512]) & U32)
        pushed = cell(pushed_cost, 0x8000_0000 + x)
        update_ring_min(ring, position, pushed)
        pushes += 1

    # The next gap finalizes those positions high-to-low, applying pushes before commit.
    finalized = 0
    for position in range(high_node, lower_node, -1):
        value = cell(base_cost(position), rng.getrandbits(32))
        update_ring_min(ring, position, value)
        if position % 8 == 0:
            commit(ring, mins, position)
        finalized += 1

    comparisons = 0
    for lo in range(3, 259):
        for e in range(lo + 1, 260):
            expected = scalar_best(lc, ring, lower_node, lo, e)
            actual = rmq_best(lc, ring, mins, ends, lower_node, lo, e)
            if actual != expected:
                raise AssertionError({"push_finalization": True, "lo": lo, "e": e,
                                      "scalar": expected, "rmq": actual})
            comparisons += 1

    # A candidate at lower_node reads its future cells before making its own backward pushes.
    committed_starts = [
        position for position in range(lower_node + 1, lower_node + 259)
        if position % 8 == 0 and position + 7 <= lower_node + 258
    ]
    future_cells = {
        position: ring[position % RING]
        for start in committed_starts for position in range(start, start + 8)
    }
    future_summaries = {start: mins[(start // 8) % MIN_BLOCKS] for start in committed_starts}
    before_query = rmq_best(lc, ring, mins, ends, lower_node, 3, 259)
    current_pushes = 0
    for x in range(1, 256):
        position = lower_node - x
        pushed_cost = word((20_000 + lc[(3 + x) % 512]) & U32)
        update_ring_min(ring, position, cell(pushed_cost, rng.getrandbits(32)))
        current_pushes += 1
    unchanged_cells = all(ring[position % RING] == value for position, value in future_cells.items())
    unchanged_summaries = all(
        mins[(start // 8) % MIN_BLOCKS] == value for start, value in future_summaries.items()
    )
    after_query = rmq_best(lc, ring, mins, ends, lower_node, 3, 259)
    if not unchanged_cells or not unchanged_summaries or after_query != before_query:
        raise AssertionError("a backward push changed an already-final future RMQ group")
    return {
        "previous_node": high_node,
        "lower_node": lower_node,
        "lower_node_ring_slot": lower_node % RING,
        "query_endpoint_ring_slots": [(lower_node + 3) % RING, (lower_node + 258) % RING],
        "previous_push_target_ring_slots": [(high_node - 255) % RING, (high_node - 1) % RING],
        "previous_pushes_applied": pushes,
        "gap_positions_finalized_high_to_low": finalized,
        "post_gap_all_interval_comparisons": comparisons,
        "current_node_pushes_applied_after_query": current_pushes,
        "committed_future_groups_unchanged": unchanged_summaries,
        "committed_future_cells_unchanged": unchanged_cells,
        "query_unchanged_by_earlier_pushes_below_current_node": before_query == after_query,
        "ring_wrap_crossed": lower_node % RING + 258 >= RING,
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--seed", type=int, default=20261008)
    parser.add_argument("--random-cases", type=int, default=256)
    parser.add_argument("--queries-per-case", type=int, default=64)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    args = parser.parse_args()

    price_report = check_price_ends(args.seed)
    exhaustive_report = check_exhaustive_intervals()
    random_report = check_random_intervals(args.seed, args.random_cases, args.queries_per_case)
    fallback_report = check_invalid_fallbacks(args.seed + 1)
    push_report = check_backward_pushes(args.seed + 2)

    builder = json.loads((ROOT / "candidates/r10-rmq8/manifest.json").read_bytes())
    if sha256(CANDIDATE) != builder["hashes"]["parse.rs"]:
        raise ValueError("candidate parse.rs does not match its manifest")
    if sha256(SCALAR) != builder["parent_hashes"]["parse.rs"]:
        raise ValueError("scalar parent parse.rs does not match candidate manifest")
    if sha256(CANDIDATE_LEAN) != builder["hashes"]["Parse.lean"]:
        raise ValueError("candidate Parse.lean does not match its manifest")
    if sha256(SCALAR_LEAN) != builder["parent_hashes"]["Parse.lean"]:
        raise ValueError("scalar parent Parse.lean does not match candidate manifest")
    result = {
        "status": "MODEL_DIFFERENTIAL_NO_COUNTEREXAMPLE",
        "scope": "Python model of the generated Rust RMQ helper and the scalar endpoint minimum only.",
        "input_files": {
            "builder": {"path": BUILDER.relative_to(ROOT).as_posix(), "sha256": sha256(BUILDER)},
            "candidate_parse_rs": {"path": CANDIDATE.relative_to(ROOT).as_posix(), "sha256": sha256(CANDIDATE)},
            "scalar_parse_rs": {"path": SCALAR.relative_to(ROOT).as_posix(), "sha256": sha256(SCALAR)},
            "candidate_parse_lean": {"path": CANDIDATE_LEAN.relative_to(ROOT).as_posix(), "sha256": sha256(CANDIDATE_LEAN)},
            "scalar_parse_lean": {"path": SCALAR_LEAN.relative_to(ROOT).as_posix(), "sha256": sha256(SCALAR_LEAN)},
            "candidate_manifest": {"path": MANIFEST.relative_to(ROOT).as_posix(), "candidate_hashes": builder["hashes"],
                                   "parent_hashes": builder["parent_hashes"]},
        },
        "model": {
            "usize_bits": 64,
            "ring_positions": RING,
            "summary_slots": MIN_BLOCKS,
            "summary_group_size": 8,
            "lengths_covered": "3..258 inclusive, queried as half-open [lo,e) with e <= 259",
            "costs": "high 32 bits of ring cells; low 32-bit choice payloads vary but are ignored by both scalar and RMQ queries",
            "price_domain": "u32, including 0 and u32::MAX",
        },
        "checks": {
            "price_runs": price_report,
            "exhaustive_intervals": exhaustive_report,
            "random_intervals": random_report,
            "invalid_range_fallbacks": fallback_report,
            "backward_push_sweep": push_report,
        },
        "review_findings": [
            "No output mismatch was found in the exercised scalar-versus-eight-summary model.",
            "Constant-price grouping is half-open and covers all 512 price slots; rebuilding the ends array overwrites every slot at each modeled block-price change.",
            "Packed summary cost is (high_cost << 3) | offset; low offset breaks cost ties toward the earliest endpoint, matching ascending scalar length order inside a constant-price run.",
            "The sweep model includes up to 255 backward pushes from a prior node, applies them before high-to-low gap finalization, and confirms committed future groups remain stable after later pushes strictly below the current node.",
        ],
        "review_boundaries": [
            "This Python model is not Rust execution, compiler checking, official re-extraction, Lean totality, proof-obligation coverage, or a public round-trip gate.",
            "The candidate copies the parent's Parse.lean unchanged although d_gap, d_cand, d_block, and d_dp interfaces plus new helpers changed; formal acceptance remains unverified.",
            "Price tables and rings are modeled at helper boundaries. Real block transitions, extracted dataflow, maximum-size input behavior, and full candidate outputs remain for the official gate.",
            "The ring-generation argument relies on D_RING=1024 exceeding the 258-byte forward query plus at most 255-byte backward push span; any future range or ring-size change requires rechecking this invariant.",
        ],
        "not_checked": ["Rust toolchain", "Lean", "candidate full parser", "official contract", "performance"],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({
        "status": result["status"],
        "price_endpoint_checks": price_report["endpoints_checked"],
        "exhaustive_differential_comparisons": exhaustive_report["differential_comparisons"],
        "random_differential_comparisons": random_report["differential_comparisons"],
        "push_sweep_comparisons": push_report["post_gap_all_interval_comparisons"],
        "summary_queries": exhaustive_report["summary_queries"],
        "scalar_tail_queries": exhaustive_report["scalar_tail_queries"],
        "output": args.output.relative_to(ROOT).as_posix() if args.output.is_relative_to(ROOT) else str(args.output),
    }, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
