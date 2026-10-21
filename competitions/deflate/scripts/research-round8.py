"""CI-only candidate-cost counters; never timing, gate, or compression evidence."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
from datetime import datetime, timezone


ROOT = Path(__file__).resolve().parents[1]
CANDIDATE = Path("candidates/r8-mid361-cost-suffix/parse.rs")
TOOLCHAIN = "+nightly-2026-08-18"
EXPECTED_FILES = 28

# Exact source anchors deliberately reject candidate drift instead of guessing.
RC_SIGNATURE = """pub fn rc_seq(
    input: &[u8],
    pa: &mut [u64; RING],
    cands: &[u32; 16],
    nc: usize,
    lc: &[u32; 512],
    dtab: &[u8; 512],
    dcc: &[u32; 32],
    i: usize,
    s: usize,
    base: u32,
    pcd: usize,
    tmax: usize,
) {"""

SUFFIX_SIGNATURE = """pub fn rc_pick_suffix(cands: &[u32; 16], nc: usize, k0: usize, dtab: &[u8; 512], dcc: &[u32; 32]) -> u32 {
    let mut chosen = cands[k0 % 16];
    let mut price = dcc[dsym(dtab, (chosen >> 9) as usize) % 32];
    let mut k = k0;
    while k < nc && k < 16 {"""

FORWARD_CALL = """        let chosen = rc_pick_suffix(cands, nc, k, dtab, dcc);
        let fds = dsym(dtab, (chosen >> 9) as usize) % 32;
        let bd = base.wrapping_add(dcc[fds]);
        relax_seq(pa, lc, i, lo, len, bd, chosen & !511u32);"""

COUNTERS = [
    "rc_seq_calls",
    "retained_candidates_seen",
    "forward_segments",
    "forward_lengths",
    "cheaper_distance_segments",
    "cheaper_distance_lengths",
    "equal_price_nearer_segments",
    "equal_price_nearer_lengths",
    "sum_segment_price_delta_units16",
    "sum_edge_price_delta_units16",
    "suffix_helper_calls",
    "suffix_helper_iterations",
    "empty_forward_segments",
]

INSTRUMENTATION = r'''
// Round 8 diagnostics: present only in the RUNNER_TEMP source copy.
use std::sync::atomic::{AtomicU64, Ordering};
static R8_COUNTS: [AtomicU64; 13] = [const { AtomicU64::new(0) }; 13];
static R8_NC_HIST: [AtomicU64; 17] = [const { AtomicU64::new(0) }; 17];

#[inline(always)]
fn r8_inc(index: usize, value: u64) {
    R8_COUNTS[index].fetch_add(value, Ordering::Relaxed);
}

fn r8_rc_enter(nc: usize) {
    assert!(nc <= 16, "diagnostic candidate-count invariant");
    r8_inc(0, 1);
    r8_inc(1, nc as u64);
    R8_NC_HIST[nc].fetch_add(1, Ordering::Relaxed);
}

fn r8_forward(c: u32, chosen: u32, lo: usize, len: usize, old: u32, new: u32) {
    let width = if lo <= len { (len - lo + 1) as u64 } else { 0 };
    r8_inc(2, 1);
    r8_inc(3, width);
    if width == 0 { r8_inc(12, 1); }
    assert!(new <= old, "suffix selector increased distance price");
    if new < old {
        r8_inc(4, 1);
        r8_inc(5, width);
        r8_inc(8, (old - new) as u64);
        r8_inc(9, (old - new) as u64 * width);
    } else if (chosen >> 9) < (c >> 9) {
        r8_inc(6, 1);
        r8_inc(7, width);
    } else {
        assert_eq!(chosen >> 9, c >> 9, "suffix tie chose farther distance");
    }
}

pub fn r8_reset() {
    for counter in &R8_COUNTS { counter.store(0, Ordering::Relaxed); }
    for counter in &R8_NC_HIST { counter.store(0, Ordering::Relaxed); }
}

pub fn r8_snapshot() -> (Vec<u64>, Vec<u64>) {
    (R8_COUNTS.iter().map(|x| x.load(Ordering::Relaxed)).collect(),
     R8_NC_HIST.iter().map(|x| x.load(Ordering::Relaxed)).collect())
}
'''

HARNESS = r'''
#![allow(dead_code)]
#[path = "candidate-instrumented.rs"]
mod candidate;

fn decode_matches(input: &[u8], tokens: &[u32]) -> bool {
    let mut decoded = Vec::with_capacity(input.len());
    for &token in tokens {
        if token < 256 {
            if decoded.len() >= input.len() { return false; }
            decoded.push(token as u8);
        } else {
            if token < 16777216 { return false; }
            let value = token - 16777216;
            let distance = (value / 256 + 1) as usize;
            let length = (value % 256 + 3) as usize;
            if distance > 32768 || distance > decoded.len() || length > 258
                || decoded.len() + length > input.len() { return false; }
            for _ in 0..length {
                let byte = decoded[decoded.len() - distance];
                decoded.push(byte);
            }
        }
    }
    decoded == input
}

fn main() {
    let inputs: Vec<_> = std::env::args_os().skip(1).collect();
    assert_eq!(inputs.len(), 28, "public corpus file count");
    for (index, path) in inputs.iter().enumerate() {
        let input = std::fs::read(path).expect("read public corpus file");
        let mut tokens = vec![0u32; input.len()];
        candidate::r8_reset();
        // Exactly one instrumented parse per file; no warmup or timing.
        let count = candidate::parse(&input, &mut tokens);
        assert!(count <= tokens.len(), "token output capacity");
        tokens.truncate(count);
        let decoded = decode_matches(&input, &tokens);
        let (counts, histogram) = candidate::r8_snapshot();
        println!("R8_RESULT {{\"index\":{},\"input_bytes\":{},\"tokens\":{},\"decode_ok\":{},\"counts\":{:?},\"nc_hist\":{:?}}}",
                 index, input.len(), count, decoded, counts, histogram);
        assert!(decoded, "diagnostic round trip failed");
    }
}
'''


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def replace_once(source: str, before: str, after: str) -> str:
    count = source.count(before)
    if count != 1:
        raise ValueError(f"Expected one exact instrumentation anchor, got {count}: {before[:80]!r}")
    return source.replace(before, after, 1)


def instrument(source: str) -> str:
    if "r8_rc_enter" in source or "R8_COUNTS" in source:
        raise ValueError("Source already contains diagnostic instrumentation")
    source = replace_once(source, RC_SIGNATURE, RC_SIGNATURE + "\n    r8_rc_enter(nc);")
    helper = SUFFIX_SIGNATURE.replace(
        "    let mut chosen =", "    r8_inc(10, 1);\n    let mut chosen =", 1
    ) + "\n        r8_inc(11, 1);"
    source = replace_once(source, SUFFIX_SIGNATURE, helper)
    source = replace_once(
        source,
        FORWARD_CALL,
        FORWARD_CALL.replace(
            "        relax_seq(pa,",
            "        r8_forward(c, chosen, lo, len, dcc[ds], dcc[fds]);\n        relax_seq(pa,",
            1,
        ),
    )
    return source + "\n" + INSTRUMENTATION


def save(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, allow_nan=False) + "\n", encoding="utf-8")


def select_source(expected_hash: str, spec: dict | None) -> tuple[Path, str]:
    if spec is None:
        return ROOT / CANDIDATE, CANDIDATE.parent.name
    entries = [entry for entry in spec["entries"]
               if entry["hashes"]["parse.rs"] == expected_hash]
    if len(entries) != 1:
        raise ValueError("Current batch must contain exactly one parser matching the original suffix manifest")
    entry = entries[0]
    source = (ROOT / entry["path"] / "parse.rs").resolve()
    if not source.is_relative_to(ROOT.resolve()):
        raise ValueError("Selected candidate escaped the repository")
    return source, entry["name"]


def parse_results(stdout: str, inputs: list[dict]) -> list[dict]:
    rows = []
    for line in stdout.splitlines():
        if not line.startswith("R8_RESULT "):
            continue
        raw = json.loads(line[len("R8_RESULT "):])
        index = raw.pop("index")
        if index != len(rows) or index >= len(inputs):
            raise ValueError("Unexpected or duplicate corpus index in diagnostic output")
        counts = raw.pop("counts")
        histogram = raw.pop("nc_hist")
        if len(counts) != len(COUNTERS) or len(histogram) != 17:
            raise ValueError("Diagnostic counter schema mismatch")
        if any(type(value) is not int or value < 0 for value in counts + histogram):
            raise ValueError("Invalid diagnostic counter value")
        row = {**inputs[index], **raw, **dict(zip(COUNTERS, counts))}
        row["candidate_count_histogram"] = {str(i): value for i, value in enumerate(histogram)}
        if row["input_bytes"] != inputs[index]["input_bytes"]:
            raise ValueError("Input size does not match corpus manifest")
        if sum(histogram) != row["rc_seq_calls"]:
            raise ValueError("Candidate histogram does not match call count")
        if sum(i * value for i, value in enumerate(histogram)) != row["retained_candidates_seen"]:
            raise ValueError("Candidate histogram does not match candidate count")
        if row["forward_segments"] != row["retained_candidates_seen"]:
            raise ValueError("Forward segment count differs from retained-candidate count")
        if row["suffix_helper_calls"] != row["forward_segments"]:
            raise ValueError("Suffix helper call count differs from forward segments")
        if sum((i * (i + 1) // 2) * value for i, value in enumerate(histogram)) != row["suffix_helper_iterations"]:
            raise ValueError("Suffix scan iteration count differs from exact matched helper")
        row["mean_candidates_per_rc_seq_call"] = (
            row["retained_candidates_seen"] / row["rc_seq_calls"] if row["rc_seq_calls"] else None
        )
        row["sum_edge_model_saving_bits"] = row["sum_edge_price_delta_units16"] / 16
        rows.append(row)
    return rows


def run_logged(command: list[str], log: Path, timeout: int) -> subprocess.CompletedProcess:
    try:
        result = subprocess.run(command, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired as error:
        def text_part(value):
            return value.decode("utf-8", errors="replace") if isinstance(value, bytes) else (value or "")
        log.write_text(text_part(error.stdout) + text_part(error.stderr), encoding="utf-8")
        raise
    log.write_text(result.stdout + result.stderr, encoding="utf-8")
    return result


def main() -> None:
    if not (os.environ.get("GITHUB_ACTIONS") == "true"
            and os.environ.get("RUNNER_OS") == "Linux" and sys.platform == "linux"):
        raise SystemExit("This diagnostic may run only on a Linux GitHub Actions runner")
    if os.environ.get("GITHUB_REPOSITORY") != "HuanHuanHuanFFF/Miner":
        raise SystemExit("Unexpected diagnostic repository")

    spec = None
    if os.environ.get("ROUND4_SPEC"):
        from round4 import specification_path, validate
        requested = json.loads(specification_path(os.environ["ROUND4_SPEC"]).read_text(encoding="utf-8"))
        if requested.get("cost_diagnostics") is not True:
            print("ROUND8_COST_DIAGNOSTIC_NOT_REQUESTED", flush=True)
            return
        spec = validate(os.environ["ROUND4_SPEC"])

    manifest_path = ROOT / CANDIDATE.parent / "manifest.json"
    manifest_bytes = manifest_path.read_bytes()
    expected_hash = json.loads(manifest_bytes)["hashes"]["parse.rs"]
    source_path, candidate_name = select_source(expected_hash, spec)
    source_bytes = source_path.read_bytes()
    candidate_hash = sha256(source_bytes)
    if candidate_hash != expected_hash:
        raise ValueError("Selected parser bytes differ from the original suffix manifest")

    runner_temp = Path(os.environ["RUNNER_TEMP"]).resolve(strict=True)
    build = runner_temp / "round8-cost-diagnostic-build"
    output = runner_temp / "round4-receipts/cost-diagnostics"
    for path in (build, output):
        if not path.resolve().is_relative_to(runner_temp):
            raise ValueError("Diagnostic path escaped RUNNER_TEMP")
        path.mkdir(parents=True, exist_ok=True)

    report = {
        "status": "NOT_RUN",
        "scope": "Instrumented single parses of public stage1 inputs; no timing, encoder-size, Lean-gate, admission, or reward result",
        "price_units": "1/16 bit; edge savings sum alternatives at all visited segments, not selected-path or encoded-bit savings",
        "histogram_scope": "rc_seq calls only; continuation-only and take-as-is positions are excluded",
        "created_at": datetime.now(timezone.utc).isoformat(),
        "run_id": os.environ.get("GITHUB_RUN_ID"),
        "run_attempt": os.environ.get("GITHUB_RUN_ATTEMPT"),
        "git_sha": os.environ.get("GITHUB_SHA"),
        "round4_spec": os.environ.get("ROUND4_SPEC"),
        "candidate": source_path.relative_to(ROOT).as_posix(),
        "candidate_name": candidate_name,
        "original_suffix_manifest": manifest_path.relative_to(ROOT).as_posix(),
        "original_suffix_manifest_sha256": sha256(manifest_bytes),
        "expected_suffix_source_sha256": expected_hash,
        "uninstrumented_candidate_sha256": candidate_hash,
        "script_sha256": sha256(Path(__file__).read_bytes()),
        "toolchain": TOOLCHAIN,
        "compile_exit": None,
        "runtime_exit": None,
        "files": [],
    }
    receipt = output / "cost-diagnostics.json"
    save(receipt, report)
    try:
        upstream = Path(os.environ["DEFLATE_ROOT"]).resolve(strict=True)
        corpus = upstream / "data/benchmark/corpus-stage1"
        files = sorted(path for path in corpus.iterdir() if path.is_file())
        if len(files) != EXPECTED_FILES:
            raise ValueError(f"Expected {EXPECTED_FILES} public corpus files, found {len(files)}")
        inputs = [{"file": path.name, "input_bytes": path.stat().st_size,
                   "input_sha256": sha256(path.read_bytes())} for path in files]
        report["corpus_manifest"] = inputs
        report["corpus_total_bytes"] = sum(entry["input_bytes"] for entry in inputs)
        normalized = source_bytes.decode("utf-8").replace("\r\n", "\n")
        instrumented = instrument(normalized)
        candidate_copy = build / "candidate-instrumented.rs"
        source = build / "cost-diagnostics.rs"
        candidate_copy.write_text(instrumented, encoding="utf-8")
        source.write_text(HARNESS, encoding="utf-8")
        report["instrumented_source_sha256"] = sha256(candidate_copy.read_bytes())
        report["harness_sha256"] = sha256(source.read_bytes())
        report["status"] = "BUILD_PENDING"
        save(receipt, report)

        binary = build / "cost-diagnostics"
        command = ["rustc", TOOLCHAIN, "--edition=2021", "-O", "-C", "overflow-checks=yes",
                   str(source), "-o", str(binary)]
        report["compile_command"] = command
        compiled = run_logged(command, output / "build.log", 180)
        report["compile_exit"] = compiled.returncode
        if compiled.returncode:
            raise RuntimeError("Diagnostic Rust build failed; inspect build.log")
        report["status"] = "RUNTIME_PENDING"
        save(receipt, report)

        measured = run_logged([str(binary), *map(str, files)], output / "runtime.log", 240)
        report["runtime_exit"] = measured.returncode
        report["files"] = parse_results(measured.stdout, inputs)
        if measured.returncode or len(report["files"]) != EXPECTED_FILES:
            raise RuntimeError("Diagnostic corpus run incomplete; inspect runtime.log")
        if not all(row["decode_ok"] is True for row in report["files"]):
            raise RuntimeError("Diagnostic round trip failed")
        if sha256(source_path.read_bytes()) != candidate_hash:
            raise RuntimeError("Uninstrumented candidate changed during diagnostic")
        report["totals"] = {key: sum(row[key] for row in report["files"]) for key in COUNTERS}
        report["totals"]["candidate_count_histogram"] = {
            str(i): sum(row["candidate_count_histogram"][str(i)] for row in report["files"])
            for i in range(17)
        }
        report["status"] = "VERIFIED_PUBLIC_DIAGNOSTIC_ONLY"
        report["completed_at"] = datetime.now(timezone.utc).isoformat()
        save(receipt, report)
        print("ROUND8_COST_DIAGNOSTIC", json.dumps({"status": report["status"],
              "files": len(report["files"]), "candidate_sha256": candidate_hash,
              "totals": report["totals"]}), flush=True)
    except Exception as error:
        report["status"] = "DIAGNOSTIC_FAILED"
        report["error"] = f"{type(error).__name__}: {error}"
        save(receipt, report)
        raise


if __name__ == "__main__":
    main()
