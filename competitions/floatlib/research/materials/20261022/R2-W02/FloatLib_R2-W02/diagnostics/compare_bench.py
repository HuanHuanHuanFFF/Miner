#!/usr/bin/env python3
"""Run two normally built, unmodified BenchBmm executables.

This is an UNPROVED native timing diagnostic, not gate.py, not a promotion
verdict, and not a replacement for its proof/resource-isolation checks.
Default workload and inner timing are held at 500000 MAC and 3 sweeps.
No compiler, dependency, benchmark source or installed setting is modified.
"""
import argparse
import hashlib
import json
import os
import platform
import secrets
import shutil
import subprocess
import sys
from pathlib import Path


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def parse(text):
    result = {}
    for line in text.splitlines():
        fields = line.split()
        if len(fields) == 4 and fields[1] in ("true", "false") and fields[2].isdigit() and fields[3].isdigit():
            name, timed, ns, checksum = fields
            if name in result:
                raise ValueError("duplicate benchmark class " + name)
            result[name] = {"timed": timed == "true", "ns": int(ns), "checksum": int(checksum)}
    if set(result) != {"dense", "relu", "wide", "raw"}:
        raise ValueError("expected exactly the original four benchmark classes")
    for name in ("dense", "relu", "wide"):
        if not result[name]["timed"] or result[name]["ns"] <= 0:
            raise ValueError("invalid timed class " + name)
    if result["raw"]["timed"] or result["raw"]["ns"] != 0:
        raise ValueError("raw must remain untimed")
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("baseline", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--cpu", type=int, default=3)
    parser.add_argument("--seed", type=int, default=None)
    args = parser.parse_args()
    if args.seed is not None and not 0 <= args.seed < 2**32:
        parser.error("seed must be a UInt32")
    for key, expected in (("BENCH_PAIRS", "500000"), ("BENCH_INNER", "3")):
        if key in os.environ and os.environ[key] != expected:
            parser.error("conflicting " + key + ": this request keeps the original default workload")
    if not shutil.which("taskset"):
        parser.error("existing taskset required; no installation attempted")
    if hasattr(os, "sched_getaffinity") and args.cpu not in os.sched_getaffinity(0):
        parser.error("choose an existing allowed CPU, matching the comparison environment")
    binaries = {"baseline": args.baseline.resolve(), "candidate": args.candidate.resolve()}
    for path in binaries.values():
        if not path.is_file() or not os.access(path, os.X_OK):
            parser.error("missing executable " + str(path))
    args.output.mkdir(parents=True, exist_ok=False)
    seed = args.seed if args.seed is not None else secrets.randbelow(2**32)
    env = os.environ.copy()
    env.update(BENCH_PAIRS="500000", BENCH_INNER="3", BENCH_SEED=str(seed), LEAN_ABORT_ON_PANIC="1")
    evidence = {
        "status": "UNPROVED_DIRECT_NATIVE_BENCH_DIAGNOSTIC",
        "seed": seed, "paired_rounds": 25, "pairs": 500000, "inner": 3,
        "cpu": args.cpu, "platform": platform.platform(), "python": sys.version,
        "binaries": {name: {"path": str(path), "sha256": sha(path)} for name, path in binaries.items()},
        "runs": [],
        "limitation": "Uses original BenchBmm binaries; does not reproduce gate proof checks, sandbox/resource limits, or statistical admission.",
    }
    (args.output / "environment.json").write_text(json.dumps(evidence, indent=2) + "\n")
    expected_checksums = None
    for round_id in range(25):
        record = {"round": round_id, "order": ["baseline", "candidate"] if round_id % 2 == 0 else ["candidate", "baseline"]}
        for name in record["order"]:
            run = subprocess.run(["taskset", "-c", str(args.cpu), str(binaries[name])],
                                 env=env, capture_output=True, text=True, timeout=300, check=False)
            stem = f"round_{round_id:02d}_{name}"
            (args.output / (stem + ".stdout.txt")).write_text(run.stdout)
            (args.output / (stem + ".stderr.txt")).write_text(run.stderr)
            if run.returncode != 0:
                raise RuntimeError(f"{stem}: exit {run.returncode}; raw output retained")
            parsed = parse(run.stdout)
            checksums = {key: value["checksum"] for key, value in parsed.items()}
            if expected_checksums is None:
                expected_checksums = checksums
            elif checksums != expected_checksums:
                raise RuntimeError(f"{stem}: checksum mismatch; do not promote")
            record[name] = parsed
        evidence["runs"].append(record)
        (args.output / "partial_results.json").write_text(json.dumps(evidence, indent=2) + "\n")
    names = ("dense", "relu", "wide")
    evidence["classes"] = {}
    for name in names:
        lo = {who: min(r[who][name]["ns"] for r in evidence["runs"]) for who in binaries}
        evidence["classes"][name] = {"best_full_call_ns": lo, "ratio": lo["candidate"] / lo["baseline"]}
    totals = {who: sum(evidence["classes"][name]["best_full_call_ns"][who] for name in names) for who in binaries}
    evidence["minimum_class_sum_ratio"] = totals["candidate"] / totals["baseline"]
    evidence["paired_totals_ns"] = [[sum(r[who][name]["ns"] for name in names) for who in binaries] for r in evidence["runs"]]
    evidence["raw_checksums"] = expected_checksums
    (args.output / "results.json").write_text(json.dumps(evidence, indent=2) + "\n")
    print(json.dumps({"status": evidence["status"], "seed": seed,
                      "minimum_class_sum_ratio": evidence["minimum_class_sum_ratio"],
                      "classes": evidence["classes"]}, indent=2))


if __name__ == "__main__":
    main()
