#!/usr/bin/env python3
"""Read-only re-analysis of the one recorded experiment; never runs its binary."""

import csv
import hashlib
import json
from pathlib import Path
from statistics import median

ROOT = Path(__file__).resolve().parents[1]
RESULTS = ROOT / "results"


def rows(name):
    with (RESULTS / name).open() as stream:
        return list(csv.DictReader(stream))


def main():
    environment = json.loads((RESULTS / "probe_environment.json").read_text())
    for name, expected in environment["source_sha256"].items():
        assert hashlib.sha256((ROOT / "diagnostics" / name).read_bytes()).hexdigest() == expected
    timing = rows("probe_rounds.csv")
    assert len(timing) == 168
    keyed = {}
    for row in timing:
        key = int(row["round"]), row["class"], row["method"]
        assert key not in keyed
        keyed[key] = row
        assert (int(row["repetitions"]), int(row["vectors"]), int(row["length"])) == (80, 96, 1000)
        assert abs(float(row["ns_per_element"]) - int(row["elapsed_ns"]) / 7680000) < 5.1e-10
    classes = sorted({row["class"] for row in timing})
    assert len(classes) == 8
    methods = ["external_ofbits", "old_zero_branch", "merged_guard"]
    declared = json.loads((RESULTS / "probe_summary.json").read_text())
    summary = {}
    for cls in classes:
        ratios = []
        for rnd in range(7):
            sample = [keyed[rnd, cls, method] for method in methods]
            assert len({row["checksum"] for row in sample}) == 1
            assert {int(row["position"]) for row in sample} == {0, 1, 2}
            ratios.append(int(sample[2]["elapsed_ns"]) / int(sample[1]["elapsed_ns"]))
        reported = declared["classes"][cls]["merged_over_old_zero_branch"]
        assert reported["all_rounds_paired_ratio"] == ratios
        assert reported["median_paired_ratio"] == median(ratios)
        assert reported["rounds_merged_faster"] == sum(r < 1 for r in ratios)
        med_old = median(int(keyed[rnd, cls, "old_zero_branch"]["elapsed_ns"]) for rnd in range(7))
        med_new = median(int(keyed[rnd, cls, "merged_guard"]["elapsed_ns"]) for rnd in range(7))
        summary[cls] = {
            "median_paired_ratio": median(ratios),
            "ratio_of_separate_medians": med_new / med_old,
            "rounds_faster": sum(r < 1 for r in ratios),
            "all_round_ratios": ratios,
        }

    official = {"lcg_dense", "lcg_relu_alternating", "lcg_wide"}
    aggregate = []
    for rnd in range(7):
        def total(method):
            return sum(int(keyed[rnd, cls, method]["elapsed_ns"]) for cls in official)
        aggregate.append(total("merged_guard") / total("old_zero_branch"))
    assert aggregate == declared["equal_weight_official_shaped_three_class_aggregate"]["merged_over_old_zero_branch"]["all_rounds_paired_ratio"]
    vector_rows = rows("probe_vector_results.csv")
    assert len(vector_rows) == 768
    vector_keys = set()
    for row in vector_rows:
        key = row["class"], int(row["vector"])
        assert key not in vector_keys
        vector_keys.add(key)
        assert row["external_bits"] == row["old_bits"] == row["merged_bits"]
    assert vector_keys == {(cls, i) for cls in classes for i in range(96)}
    conversions = rows("probe_conversion_cases.csv")
    assert len(conversions) == 36
    for row in conversions:
        u = int(row["input_bits"], 16)
        a = u & 0x7FFFFFFF
        expected = 0x7FC00000 if 0x7F800000 < a else u
        assert int(row["external_bits"], 16) == expected
        assert row["external_bits"] == row["old_bits"] == row["merged_bits"]
        assert int(row["accepted"]) == (a == 0 or 0x0C000000 <= a < 0x7F800000)
    validity = json.loads((RESULTS / "probe_validation.json").read_text())
    assert validity["conversion_words_checked"] == 36 + 512 * 7 + 100000 + 768000 == 871620
    audit = {
        "mode": "read-only analysis of saved CSV/source/disassembly; no experiment rerun",
        "source_hashes_match_recorded_build": True,
        "timing_rows_checked": len(timing),
        "round_checksum_groups_checked": 56,
        "vector_sum_rows_checked": len(vector_rows),
        "saved_boundary_rows_checked": len(conversions),
        "conversion_check_count_includes_repeated_inputs": True,
        "class_recomputed_ratios": summary,
        "official_shape_aggregate": {
            "median_paired_ratio": median(aggregate),
            "all_round_ratios": aggregate,
            "rounds_faster": sum(r < 1 for r in aggregate),
            "proposed_3_percent_and_6_of_7_filter": median(aggregate) <= 0.97 and sum(r < 1 for r in aggregate) >= 6,
        },
        "recorded_compiler": environment["compiler"].splitlines()[0],
        "recorded_affinity": environment["probe_cpu_affinity"],
        "frequency_locked": environment["frequency_locking"],
        "disassembly_manual_review": {
            "external_call_and_scalar_add": ["0x2606", "0x260b"],
            "old_zero_test_then_scalar_add": ["0x2785", "0x2787->0x2772", "0x2776"],
            "merged_bounds": ["0x26a4", "0x26aa", "0x26ac", "0x26b1"],
            "merged_conversion_multiply_add": ["0x26ca", "0x26ce", "0x26d4"],
            "no_zero_add_elision_observed": True,
            "merged_is_not_branchless": True,
        },
    }
    Path(__file__).with_name("experiment_audit.json").write_text(json.dumps(audit, indent=2) + "\n")
    print(json.dumps({"rows": len(timing), "all_recomputed_values_match": True,
                      "official_shape": audit["official_shape_aggregate"],
                      "relu_median_vs_pairing": summary["lcg_relu_alternating"]}, indent=2))


if __name__ == "__main__":
    main()
