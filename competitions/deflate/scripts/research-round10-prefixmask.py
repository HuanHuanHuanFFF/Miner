"""CI-only operation counts for the frozen backward prefix-mask candidate.

Counters are diagnostic instrumentation only. They are not timers or time
fractions. Frozen and instrumented parsers must produce the same public tokens
and decode to the same input before counts are retained.
"""
from __future__ import annotations

import hashlib
import importlib.util
import json
import os
from pathlib import Path
import sys

from round4 import ROOT, save, validate

_helper_spec = importlib.util.spec_from_file_location(
    "round9_log_helpers", ROOT / "scripts/research-round9-phases.py"
)
_helper = importlib.util.module_from_spec(_helper_spec)
assert _helper_spec.loader is not None
_helper_spec.loader.exec_module(_helper)
run_logged = _helper.run_logged
failure_receipt = _helper.failure_receipt

FIELDS = (
    "pm_publish_calls",
    "pm_publish_disabled_calls",
    "pm_publish_bad_order_calls",
    "pm_publish_while_condition_checks",
    "pm_publish_successful_pops",
    "pm_best_len_calls",
    "pm_best_len_valid_range_calls",
    "pm_best_len_valid_range_lengths_sum",
    "pm_best_len_singleton_calls",
    "pm_prefix_offset_calls",
    "d_best_len_fallback_calls",
    "pm_cost_calls",
    "d_bcost_calls",
)

COUNTERS = r'''
use std::sync::atomic::{AtomicU64, Ordering};
static R10_PREFIXMASK_COUNTS: [AtomicU64; 13] = [const { AtomicU64::new(0) }; 13];
pub fn r10_prefixmask_reset() {
    for value in &R10_PREFIXMASK_COUNTS { value.store(0, Ordering::Relaxed); }
}
pub fn r10_prefixmask_counts() -> [u64; 13] {
    std::array::from_fn(|i| R10_PREFIXMASK_COUNTS[i].load(Ordering::Relaxed))
}
'''

HARNESS = r'''
#![allow(dead_code, unused_variables)]
#[path = "frozen.rs"] mod frozen;
#[path = "instrumented.rs"] mod instrumented;

fn quote(s: &str) -> String {
    format!("\"{}\"", s.replace('\\', "\\\\").replace('"', "\\\""))
}

fn decode(src: &[u8], tokens: &[u32]) -> bool {
    let mut out = Vec::with_capacity(src.len());
    for &token in tokens {
        if token < 256 {
            out.push(token as u8);
        } else {
            if token < 16777216 { return false; }
            let value = token - 16777216;
            let distance = (value / 256 + 1) as usize;
            let length = (value % 256 + 3) as usize;
            if distance == 0 || distance > 32768 || distance > out.len()
                || length > 258 || out.len().saturating_add(length) > src.len() {
                return false;
            }
            for _ in 0..length {
                let byte = out[out.len() - distance];
                out.push(byte);
            }
        }
    }
    out == src
}

fn main() {
    for (index, file) in std::env::args_os().skip(1).enumerate() {
        let name = file.to_string_lossy().into_owned();
        let input = std::fs::read(&file).unwrap_or_else(|_| panic!("cannot read input {}", name));
        let mut frozen_tokens = vec![0u32; input.len()];
        let mut instrumented_tokens = vec![0u32; input.len()];
        let frozen_len = frozen::parse(&input, &mut frozen_tokens);
        instrumented::r10_prefixmask_reset();
        let instrumented_len = instrumented::parse(&input, &mut instrumented_tokens);
        if frozen_len > input.len() || instrumented_len > input.len() {
            panic!("token count exceeds input length for {}", name);
        }
        if frozen_tokens[..frozen_len] != instrumented_tokens[..instrumented_len] {
            panic!("instrumentation changed tokens for {}", name);
        }
        if !decode(&input, &frozen_tokens[..frozen_len])
            || !decode(&input, &instrumented_tokens[..instrumented_len]) {
            panic!("token stream failed decode for {}", name);
        }
        let counts = instrumented::r10_prefixmask_counts();
        println!("R10_PREFIXMASK {{\"file_index\":{},\"file\":{},\"bytes\":{},\"tokens\":{},\"counts\":{:?},\"tokens_equal\":true,\"decode\":true}}",
            index, quote(&name), input.len(), frozen_len, counts);
    }
}
'''


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def replace_once(source: str, old: str, new: str, label: str) -> str:
    count = source.count(old)
    assert count == 1, f"{label}: expected one anchor, found {count}"
    return source.replace(old, new, 1)


def instrument(source: str) -> str:
    """Add relaxed counters while preserving each original decision/return."""
    assert "R10_PREFIXMASK_COUNTS" not in source
    start = source.index("pub fn pm_publish(")
    opening = source.index("{", start) + 1
    source = source[:opening] + "\n    R10_PREFIXMASK_COUNTS[0].fetch_add(1, Ordering::Relaxed);" + source[opening:]

    source = replace_once(
        source,
        """if pm_state_get(state, 2) != 1 {
        return;
    }""",
        """if pm_state_get(state, 2) != 1 {
        R10_PREFIXMASK_COUNTS[1].fetch_add(1, Ordering::Relaxed);
        return;
    }""",
        "disabled publish",
    )
    source = replace_once(
        source,
        """if (old == 0 && p != front) || (old != 0 && p.wrapping_add(1) != front) {
        state[2] = 0;""",
        """if (old == 0 && p != front) || (old != 0 && p.wrapping_add(1) != front) {
        R10_PREFIXMASK_COUNTS[2].fetch_add(1, Ordering::Relaxed);
        state[2] = 0;""",
        "publish order violation",
    )
    source = replace_once(
        source,
        "while m != 0 && fuel > 0 {",
        """while {
        R10_PREFIXMASK_COUNTS[3].fetch_add(1, Ordering::Relaxed);
        m != 0 && fuel > 0
    } {""",
        "publish mask loop condition",
    )
    source = replace_once(
        source,
        """if pm_cost(ring, p.wrapping_add(offset)) >= cost {
            m &= m.wrapping_sub(1);""",
        """if pm_cost(ring, p.wrapping_add(offset)) >= cost {
            R10_PREFIXMASK_COUNTS[4].fetch_add(1, Ordering::Relaxed);
            m &= m.wrapping_sub(1);""",
        "successful prefix-mask pop",
    )

    start = source.index("pub fn pm_best_len(")
    opening = source.index("{", start) + 1
    source = source[:opening] + "\n    R10_PREFIXMASK_COUNTS[5].fetch_add(1, Ordering::Relaxed);" + source[opening:]
    source = replace_once(
        source,
        """    if lo >= e || e > 259 {
        return d_best_len(lc, ring, p, lo, e);
    }
    if e - lo == 1 {""",
        """    if lo < e && e <= 259 {
        R10_PREFIXMASK_COUNTS[6].fetch_add(1, Ordering::Relaxed);
        R10_PREFIXMASK_COUNTS[7].fetch_add((e - lo) as u64, Ordering::Relaxed);
        if e - lo == 1 {
            R10_PREFIXMASK_COUNTS[8].fetch_add(1, Ordering::Relaxed);
        }
    }
    if lo >= e || e > 259 {
        return d_best_len(lc, ring, p, lo, e);
    }
    if e - lo == 1 {""",
        "effective pm_best_len interval",
    )

    start = source.index("pub fn pm_prefix_offset(")
    opening = source.index("{", start) + 1
    source = source[:opening] + "\n    R10_PREFIXMASK_COUNTS[9].fetch_add(1, Ordering::Relaxed);" + source[opening:]
    start = source.index("pub fn d_best_len(")
    opening = source.index("{", start) + 1
    source = source[:opening] + "\n    R10_PREFIXMASK_COUNTS[10].fetch_add(1, Ordering::Relaxed);" + source[opening:]

    start = source.index("pub fn pm_cost(")
    opening = source.index("{", start) + 1
    source = source[:opening] + "\n    R10_PREFIXMASK_COUNTS[11].fetch_add(1, Ordering::Relaxed);" + source[opening:]
    start = source.index("pub fn d_bcost(")
    opening = source.index("{", start) + 1
    source = source[:opening] + "\n    R10_PREFIXMASK_COUNTS[12].fetch_add(1, Ordering::Relaxed);" + source[opening:]
    return source + COUNTERS


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    assert os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"
    spec = validate(os.environ["ROUND4_SPEC"])
    if not spec.get("prefixmask_diagnostics"):
        print("ROUND10_PREFIXMASK_NOT_REQUESTED")
        return

    entry = next(e for e in spec["entries"] if e["name"] == "r10-backward-prefixmask")
    raw = (ROOT / entry["path"] / "parse.rs").read_bytes()
    assert hashlib.sha256(raw).hexdigest() == entry["hashes"]["parse.rs"] == \
        "5a4b534b9966d21f06f8cde90fe0c5c6f5d6c4429c2c19c57a2a1e300c9993c1"
    source = raw.decode("utf-8")
    instrumented_source = instrument(source)
    assert source.encode("utf-8") == raw, "frozen candidate bytes changed during instrumentation"

    files = sorted(p for p in (Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1").iterdir() if p.is_file())
    assert len(files) == 28 and sum(p.stat().st_size for p in files) == 15_930_000
    build = Path(os.environ["RUNNER_TEMP"]) / "round10-prefixmask-build"
    output = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/prefixmask-diagnostics"
    build.mkdir(parents=True, exist_ok=True)
    output.mkdir(parents=True, exist_ok=True)
    frozen_path = build / "frozen.rs"
    instrumented_path = build / "instrumented.rs"
    harness_path = build / "main.rs"
    frozen_path.write_bytes(raw)
    instrumented_path.write_text(instrumented_source, encoding="utf-8")
    harness_path.write_text(HARNESS, encoding="utf-8")
    assert frozen_path.read_bytes() == raw

    report = {
        "status": "PENDING",
        "run_id": os.environ["GITHUB_RUN_ID"],
        "git_sha": os.environ["GITHUB_SHA"],
        "candidate": entry["name"],
        "frozen_source_sha256": hashlib.sha256(raw).hexdigest(),
        "instrumented_source_sha256": hashlib.sha256(instrumented_path.read_bytes()).hexdigest(),
        "harness_sha256": hashlib.sha256(harness_path.read_bytes()).hexdigest(),
        "counter_fields": list(FIELDS),
        "scope": "Actual prefix-mask operation/function-call counts on instrumented copy, with frozen/instrumented token equality and decode checks. Counts are not hardware load counts, elapsed time, or time fractions.",
        "corpus": [{"file": p.name, "bytes": p.stat().st_size, "sha256": hashlib.sha256(p.read_bytes()).hexdigest()} for p in files],
        "build_dir": str(build),
        "output_dir": str(output),
    }
    report_path = output / "prefixmask.json"
    save(report_path, report)
    with failure_receipt(report, report_path):
        binary = build / "prefixmask-counts"
        compile_proc = run_logged(
            ["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes",
             str(harness_path), "-o", str(binary)], output / "build.log", 180)
        report["compile_exit"] = compile_proc.returncode
        if compile_proc.returncode:
            raise RuntimeError("Prefix-mask Rust harness compilation failed; retained build.log")
        runtime = run_logged([str(binary), *map(str, files)], output / "runtime.log", 180)
        report["runtime_exit"] = runtime.returncode
        if runtime.returncode:
            raise RuntimeError("Prefix-mask public token/decode run failed; retained runtime.log")
        rows = [json.loads(line.removeprefix("R10_PREFIXMASK "))
                for line in runtime.stdout.splitlines() if line.startswith("R10_PREFIXMASK ")]
        assert len(rows) == 28 and [r["file_index"] for r in rows] == list(range(28))
        assert all(r["tokens_equal"] and r["decode"] and len(r["counts"]) == len(FIELDS) for r in rows)
        for row in rows:
            row["file_name"] = files[row["file_index"]].name
            row["input_sha256"] = report["corpus"][row["file_index"]]["sha256"]
            row["named_counts"] = dict(zip(FIELDS, row.pop("counts")))
        totals = {key: sum(r["named_counts"][key] for r in rows) for key in FIELDS}
        report.update(status="VERIFIED_FINITE_PREFIXMASK_OPERATION_COUNTS", files=rows, totals=totals,
                      tokens_equal_all_files=True, all_decoded=True,
                      limits=[
                          "Relaxed atomic instrumentation can perturb execution; no timers or runtime-share inference are made.",
                          "pm_cost and d_bcost are function invocation counts, not actual machine loads or hardware event counts.",
                          "Finite 28-file token/decode equality does not establish all-input equivalence or replace the separate native 444-case check.",
                          "The source copy frozen before injection is hash-bound to the candidate; the original candidate file is not modified."
                      ])
        save(report_path, report)
        print("ROUND10_PREFIXMASK", json.dumps({"status": report["status"], "files": 28, "totals": totals}))


if __name__ == "__main__":
    main()
