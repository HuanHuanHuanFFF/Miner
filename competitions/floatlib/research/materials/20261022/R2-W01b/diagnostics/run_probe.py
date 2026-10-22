#!/usr/bin/env python3
"""Compile and run the single, pre-specified C comparison; retain raw outputs."""
from pathlib import Path
import csv
import hashlib
import json
import os
import platform
import statistics
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "results"
OUT.mkdir(exist_ok=True)
FLAGS = ["-O3", "-std=c11", "-fno-fast-math", "-ffp-contract=off", "-fno-lto", "-Wall", "-Wextra"]
SOURCES = [ROOT / "diagnostics" / n for n in ("zero_merge_probe.c", "ofbits_external.c")]
EXE = OUT / "zero_merge_probe"
command = ["cc", *FLAGS, *(str(p) for p in SOURCES), "-lm", "-o", str(EXE)]
build = subprocess.run(command, text=True, capture_output=True)
(OUT / "compile_stdout.txt").write_text(build.stdout)
(OUT / "compile_stderr.txt").write_text(build.stderr)
if build.returncode:
    raise SystemExit(build.returncode)
assembly = subprocess.run(["objdump", "-d", "--no-show-raw-insn", str(EXE)], text=True, capture_output=True, check=True)
(OUT / "probe_disassembly.txt").write_text(assembly.stdout)
affinity = sorted(os.sched_getaffinity(0)) if hasattr(os, "sched_getaffinity") else []
pin = affinity[0] if affinity else None
metadata = {
    "compile_command": command,
    "compiler": subprocess.check_output(["cc", "--version"], text=True),
    "platform": platform.platform(),
    "python": sys.version,
    "allowed_cpus": affinity,
    "probe_cpu_affinity": [pin] if pin is not None else None,
    "frequency_locking": False,
    "run_command": [str(EXE), str(OUT), "80"],
    "source_sha256": {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in SOURCES},
    "table_representation": "flat float[512]; no Lean array boxing or once-cell operations",
    "experiment_count": 1,
    "official_environment_modified": False,
    "lean_compile": "NOT_RUN",
    "official_gate": "NOT_RUN",
}
(OUT / "probe_environment.json").write_text(json.dumps(metadata, indent=2))
def child_affinity():
    if pin is not None:
        os.sched_setaffinity(0, {pin})
run = subprocess.run(metadata["run_command"], text=True, capture_output=True,
                     preexec_fn=child_affinity if pin is not None else None)
(OUT / "probe_stdout.txt").write_text(run.stdout)
(OUT / "probe_stderr.txt").write_text(run.stderr)
print(run.stdout, end="")
if run.returncode:
    print(run.stderr, file=sys.stderr)
    raise SystemExit(run.returncode)
rows = list(csv.DictReader((OUT / "probe_rounds.csv").open()))
assert len(rows) == 7 * 8 * 3
classes = sorted({r["class"] for r in rows})
summary = {}
for c in classes:
    by_round = {int(r["round"]): {} for r in rows if r["class"] == c}
    for r in rows:
        if r["class"] == c:
            by_round[int(r["round"])][r["method"]] = r
    assert all(len({r["checksum"] for r in by_round[k].values()}) == 1 for k in by_round)
    item = {}
    for method in ("external_ofbits", "old_zero_branch", "merged_guard"):
        ns = [float(by_round[k][method]["ns_per_element"]) for k in sorted(by_round)]
        item[method] = {"median_ns_per_element": statistics.median(ns), "all_rounds_ns_per_element": ns}
    for denominator in ("external_ofbits", "old_zero_branch"):
        ratios = [int(by_round[k]["merged_guard"]["elapsed_ns"]) / int(by_round[k][denominator]["elapsed_ns"]) for k in sorted(by_round)]
        item["merged_over_" + denominator] = {
            "median_paired_ratio": statistics.median(ratios),
            "all_rounds_paired_ratio": ratios,
            "rounds_merged_faster": sum(x < 1 for x in ratios),
        }
    summary[c] = item
official_classes = ["lcg_dense", "lcg_relu_alternating", "lcg_wide"]
aggregate = {}
for denominator in ("external_ofbits", "old_zero_branch"):
    ratios = []
    for k in range(7):
        def total(method):
            return sum(int(r["elapsed_ns"]) for r in rows if int(r["round"]) == k and r["class"] in official_classes and r["method"] == method)
        ratios.append(total("merged_guard") / total(denominator))
    aggregate["merged_over_" + denominator] = {"median_paired_ratio": statistics.median(ratios), "all_rounds_paired_ratio": ratios}
result = {"classes": summary, "equal_weight_official_shaped_three_class_aggregate": aggregate,
          "interpretation": "finite C surrogate; no Lean or official target inference"}
(OUT / "probe_summary.json").write_text(json.dumps(result, indent=2))
for c, item in summary.items():
    print(c, "external/old/merged ns=", "/".join(f'{item[m]["median_ns_per_element"]:.6f}' for m in ("external_ofbits", "old_zero_branch", "merged_guard")), "merged/old=",f'{item["merged_over_old_zero_branch"]["median_paired_ratio"]:.6f}')
