"""Recompute round-1 public metrics from the CI log's raw measurements.

Usage: python scripts/analyze-round1.py evidence/round1/ci.log
The saved record files are independent of GitHub log availability and need no
local Rust/Lean environment. This does not predict official admission or rank.
"""

from __future__ import annotations

import json
import re
import statistics
import sys
from pathlib import Path


def median_total(method: dict) -> float:
    assert method["deterministic"] and not method["errors"]
    samples = [r for r in method["reps"] if r["phase"] == "measured"]
    assert len(samples) == 11
    assert all(r["total_s"] > 0 for r in samples)
    return statistics.median(r["total_s"] for r in samples)


def main() -> None:
    log = Path(sys.argv[1])
    records: dict[tuple[int, str], list[dict]] = {}
    reported = {}
    for line in log.read_text(encoding="utf-8-sig").splitlines():
        raw = re.search(r"RAW_EVIDENCE (\d+) (\S+) (\{.*\})$", line)
        if raw:
            key = int(raw[1]), raw[2]
            records.setdefault(key, []).append(json.loads(raw[3]))
        sample = re.search(r"MEASUREMENT (\{.*\})$", line)
        if sample:
            result = json.loads(sample[1])
            reported[result["round"], result["candidate"]] = result
    assert len(records) == len(reported) == 8, (len(records), len(reported))
    metrics = {}
    files_by_key = {}
    for key, raw in sorted(records.items()):
        round_number, name = key
        assert raw[0]["kind"] == "meta" and raw[0]["corpus"] == "corpus-stage1"
        files = [r for r in raw if r["kind"] == "file"]
        assert len(files) == 28 and sum(f["raw_bytes"] for f in files) == 15930000
        files_by_key[key] = {f["file"]: f for f in files}
        nonempty = [f for f in files if f["raw_bytes"] > 0]
        value = {
            "round": round_number,
            "candidate": name,
            "time": statistics.mean(
                median_total(f["methods"][name]) / median_total(f["methods"]["incumbent"])
                for f in nonempty
            ),
            "size_pct": statistics.mean(
                100 * f["methods"][name]["output_bytes"] / f["raw_bytes"] for f in nonempty
            ),
        }
        assert abs(value["time"] - reported[key]["balanced_time_ratio_public"]) < 1e-12
        assert abs(value["size_pct"] - reported[key]["mean_file_compression_pct_public"]) < 1e-12
        metrics[key] = value
        target = log.parent / f"round{round_number}-{name}.jsonl"
        target.write_text("".join(json.dumps(r, allow_nan=False) + "\n" for r in raw), encoding="utf-8")
    comparisons = []
    for round_number in (1, 2):
        reference = metrics[round_number, "submission-261"]
        for name in ("hash-wide", "probe2"):
            value = metrics[round_number, name]
            smaller = larger = identical = 0
            differences = []
            for filename, file in files_by_key[round_number, name].items():
                base = files_by_key[round_number, "submission-261"][filename]
                assert file["sha256"] == base["sha256"]
                delta = file["methods"][name]["output_bytes"] - base["methods"]["submission-261"]["output_bytes"]
                smaller += delta < 0
                larger += delta > 0
                identical += delta == 0
                if delta:
                    differences.append({"file": filename, "output_byte_delta": delta})
            comparisons.append({
                "round": round_number,
                "candidate": name,
                "time_change_pct_vs_reference": 100 * (value["time"] / reference["time"] - 1),
                "size_change_percentage_points_vs_reference": value["size_pct"] - reference["size_pct"],
                "files_smaller": smaller, "files_larger": larger, "files_same_size": identical,
                "output_changes": sorted(differences, key=lambda d: d["output_byte_delta"]),
            })
    output = {
        "scope": "public corpus on this CI host; no official rank/admission/reward prediction",
        "metrics": list(metrics.values()),
        "comparisons": comparisons,
    }
    (log.parent / "analysis.json").write_text(json.dumps(output, indent=2, allow_nan=False) + "\n", encoding="utf-8")
    print(json.dumps(output, indent=2, allow_nan=False))


if __name__ == "__main__":
    main()
