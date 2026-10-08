"""CI-only D record codec checks for the packed-record candidate.

This checks first-plan and recorded-node identity against the frozen
record-nonempty parent. It does not benchmark or replace the full parse gate.
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

SYNTHETIC_ROWS = (1, 5, 8)
PACK_LIMIT = 1 << 27
PUBLIC_TOTAL_BYTES = 15_930_000

HARNESS = r'''
#![allow(dead_code, unused_variables)]
#[path = "frozen.rs"] mod frozen;
#[path = "packed.rs"] mod packed;

#[derive(Clone, Debug, PartialEq, Eq)]
struct Node { position: usize, payload: Vec<u32> }

fn quote(s: &str) -> String {
    format!("\"{}\"", s.replace('\\', "\\\\").replace('"', "\\\""))
}

fn stop(message: &str) -> ! { panic!("R10_PACKED_CHECK_FAILED: {}", message); }

fn frozen_nodes(rs: &[u32]) -> Vec<Node> {
    let mut e = rs.len();
    let mut reversed = Vec::new();
    while e >= 2 {
        let count = rs[e - 1] as usize;
        let position = rs[e - 2] as usize;
        let end = e - 2;
        if count > end { stop("frozen record payload exceeds prefix"); }
        let start = end - count;
        reversed.push(Node { position, payload: rs[start..end].to_vec() });
        e = start;
    }
    if e != 0 { stop("frozen record stream has a partial header"); }
    reversed.reverse();
    reversed
}

fn packed_nodes(rs: &[u32], n: usize) -> Vec<Node> {
    let words = packed::d_header_words(n);
    if words != 1 && words != 2 { stop("packed header width is not 1 or 2"); }
    let mut e = rs.len();
    let mut reversed = Vec::new();
    while e >= words {
        let (count, position) = packed::d_read_header(rs, e, words);
        let end = e - words;
        if count > end { stop("packed record payload exceeds prefix"); }
        let start = end - count;
        reversed.push(Node { position, payload: rs[start..end].to_vec() });
        e = start;
    }
    if e != 0 { stop("packed record stream has a partial header"); }
    reversed.reverse();
    reversed
}

fn parse_d_frozen(input: &[u8], row: usize) -> (Vec<u32>, Vec<u32>) {
    let k = &frozen::D_KNOBS[row % frozen::D_NK];
    let mut plan = Vec::with_capacity(input.len() / 2 + 16);
    let mut rs = Vec::with_capacity(input.len() / 2 + 64);
    frozen::d_parse(input, &mut plan, &mut rs,
        k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[9], k[10], k[11],
        k[12], k[13], k[14], k[15]);
    (plan, rs)
}

fn parse_d_packed(input: &[u8], row: usize) -> (Vec<u32>, Vec<u32>) {
    let k = &packed::D_KNOBS[row % packed::D_NK];
    let mut plan = Vec::with_capacity(input.len() / 2 + 16);
    let mut rs = Vec::with_capacity(input.len() / 2 + 64);
    packed::d_parse(input, &mut plan, &mut rs,
        k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[9], k[10], k[11],
        k[12], k[13], k[14], k[15]);
    (plan, rs)
}

fn compare(input: &[u8], row: usize) -> (usize, usize, usize, usize, usize) {
    if input.len() < 16 { stop("D parser caller requires input length >= 16"); }
    if row >= frozen::D_NK || row >= packed::D_NK { stop("D row out of range"); }
    if frozen::D_KNOBS[row] != packed::D_KNOBS[row] { stop("candidate changed D knob row"); }
    let (frozen_plan, frozen_rs) = parse_d_frozen(input, row);
    let (packed_plan, packed_rs) = parse_d_packed(input, row);
    if frozen_plan != packed_plan { stop("firstplan differs"); }
    let old_nodes = frozen_nodes(&frozen_rs);
    let new_nodes = packed_nodes(&packed_rs, input.len());
    if old_nodes != new_nodes { stop("decoded position/payload node stream differs"); }
    let nodes = old_nodes.len();
    let old_words = frozen_rs.len();
    let new_words = packed_rs.len();
    let saved_words = old_words.checked_sub(new_words).unwrap_or_else(|| stop("packed stream grew"));
    if input.len() < packed::D_PACK_LIMIT {
        if saved_words != nodes { stop("small-input word savings do not equal retained node count"); }
    } else if saved_words != 0 {
        stop("large-input fallback must retain two words per node");
    }
    (nodes, old_words, new_words, saved_words, 4 * saved_words)
}

fn boundary_checks() -> usize {
    if packed::D_PACK_LIMIT != (1usize << 27) { stop("unexpected pack limit"); }
    let ns = [1usize, 16, packed::D_PACK_LIMIT - 1, packed::D_PACK_LIMIT,
              packed::D_PACK_LIMIT + 1];
    let counts = [0u32, 1, 16];
    let mut cases = 0usize;
    for n in ns {
        let expected_words = if n < packed::D_PACK_LIMIT { 1 } else { 2 };
        if packed::d_header_words(n) != expected_words { stop("d_header_words boundary mismatch"); }
        let mut positions = vec![0usize];
        if n > 1 { positions.push(1); positions.push(n - 1); }
        positions.sort_unstable(); positions.dedup();
        for p in positions {
            if p >= n { stop("boundary test generated invalid position"); }
            for count in counts {
                let mut rs = Vec::new();
                packed::d_write_header(&mut rs, p, count, n);
                if rs.len() != expected_words { stop("d_write_header emitted wrong width"); }
                let (got_count, got_position) = packed::d_read_header(&rs, rs.len(), expected_words);
                if got_count != count as usize || got_position != p { stop("header round trip mismatch"); }
                if expected_words == 1 && (rs.len() != 1 || rs[0] != (((p as u32) << 5) | count)) {
                    stop("small-input packed header bits changed");
                }
                if expected_words == 2 && (rs.len() != 2 || rs[0] != p as u32 || rs[1] != count) {
                    stop("large-input header fallback changed");
                }
                cases += 1;
            }
        }
    }
    let mut zero = Vec::new();
    packed::d_write_header(&mut zero, 0, 0, 1);
    let zero_nodes = packed_nodes(&zero, 1);
    if zero.len() != 1 || zero[0] != 0 || zero_nodes.len() != 1
        || zero_nodes[0].position != 0 || !zero_nodes[0].payload.is_empty() {
        stop("single-word zero node did not decode");
    }
    println!("R10_PACKED_BOUNDARY {{\"cases\":{},\"single_word_zero_node\":true,\"allocated_input_bytes\":0}}", cases);
    cases
}

fn run_public(files: &[String]) {
    boundary_checks();
    let mut d_count = 0usize;
    let mut skipped = 0usize;
    for (index, file) in files.iter().enumerate() {
        let input = std::fs::read(file).unwrap_or_else(|_| stop("cannot read public corpus file"));
        let frozen_class = frozen::route_class(&input);
        let packed_class = packed::route_class(&input);
        if frozen_class != packed_class { stop("route_class differs between sources"); }
        let frozen_route = frozen::CLASS_TAB[frozen_class % 16];
        let packed_route = packed::CLASS_TAB[packed_class % 16];
        if frozen_route != packed_route { stop("CLASS_TAB route differs between sources"); }
        if frozen_route[0] != 2 {
            println!("R10_PACKED_PUBLIC_SKIP {{\"file_index\":{},\"file\":{},\"bytes\":{},\"route_class\":{},\"engine\":{}}}",
                index, quote(file), input.len(), frozen_class, frozen_route[0]);
            skipped += 1;
            continue;
        }
        let row = frozen_route[1];
        let (nodes, old_words, new_words, saved_words, saved_bytes) = compare(&input, row);
        println!("R10_PACKED_PUBLIC {{\"file_index\":{},\"file\":{},\"bytes\":{},\"route_class\":{},\"row\":{},\"nodes\":{},\"old_words\":{},\"new_words\":{},\"saved_words\":{},\"saved_bytes\":{},\"firstplan_equal\":true,\"node_stream_equal\":true}}",
            index, quote(file), input.len(), frozen_class, row, nodes, old_words, new_words, saved_words, saved_bytes);
        d_count += 1;
    }
    println!("R10_PACKED_PUBLIC_TOTAL {{\"files\":{},\"d_routes\":{},\"skipped_non_d\":{}}}", files.len(), d_count, skipped);
}

fn run_synthetic(files: &[String]) {
    let rows = [1usize, 5, 8];
    for (index, file) in files.iter().enumerate() {
        let input = std::fs::read(file).unwrap_or_else(|_| stop("cannot read generated synthetic input"));
        for row in rows {
            let (nodes, old_words, new_words, saved_words, saved_bytes) = compare(&input, row);
            println!("R10_PACKED_SYNTHETIC {{\"file_index\":{},\"file\":{},\"bytes\":{},\"forced_d_row\":{},\"nodes\":{},\"old_words\":{},\"new_words\":{},\"saved_words\":{},\"saved_bytes\":{},\"firstplan_equal\":true,\"node_stream_equal\":true}}",
                index, quote(file), input.len(), row, nodes, old_words, new_words, saved_words, saved_bytes);
        }
    }
}

fn main() {
    let mut args = std::env::args().skip(1);
    let mode = args.next().unwrap_or_else(|| stop("missing mode"));
    let files: Vec<String> = args.collect();
    if mode == "public" { run_public(&files); }
    else if mode == "synthetic" { run_synthetic(&files); }
    else { stop("unknown mode"); }
}
'''


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def import_synthetic_inputs():
    sys.path.insert(0, str(ROOT / "scripts"))
    import round3_synthetic
    return round3_synthetic.inputs()


def parse_rows(stdout: str, prefix: str):
    rows = []
    for line in stdout.splitlines():
        if line.startswith(prefix + " "):
            rows.append(json.loads(line[len(prefix) + 1:]))
    return rows


def main():
    assert os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux"
    assert os.environ.get("GITHUB_REPOSITORY") == "HuanHuanHuanFFF/Miner"
    spec = validate(os.environ["ROUND4_SPEC"])
    if not spec.get("packed_record_diagnostics"):
        print("ROUND10_PACKED_NOT_REQUESTED")
        return

    entries = {entry["name"]: entry for entry in spec["entries"]}
    candidate = entries["r10-record-packed"]
    parent = entries["r10-record-nonempty"]
    candidate_path = ROOT / candidate["path"]
    parent_path = ROOT / parent["path"]
    candidate_raw = (candidate_path / "parse.rs").read_bytes()
    parent_raw = (parent_path / "parse.rs").read_bytes()
    candidate_lean = (candidate_path / "Parse.lean").read_bytes()
    parent_lean = (parent_path / "Parse.lean").read_bytes()
    candidate_manifest = json.loads((candidate_path / "manifest.json").read_bytes())
    assert sha256(candidate_raw) == candidate["hashes"]["parse.rs"] == candidate_manifest["hashes"]["parse.rs"]
    assert sha256(parent_raw) == parent["hashes"]["parse.rs"] == candidate_manifest["parent_hashes"]["parse.rs"]
    assert sha256(candidate_lean) == candidate["hashes"]["Parse.lean"] == candidate_manifest["hashes"]["Parse.lean"]
    assert sha256(parent_lean) == parent["hashes"]["Parse.lean"] == candidate_manifest["parent_hashes"]["Parse.lean"]

    public_dir = Path(os.environ["DEFLATE_ROOT"]) / "data/benchmark/corpus-stage1"
    public_files = sorted(p for p in public_dir.iterdir() if p.is_file())
    assert len(public_files) == 28 and sum(p.stat().st_size for p in public_files) == PUBLIC_TOTAL_BYTES
    public_inputs = [{"file": p.name, "bytes": p.stat().st_size, "sha256": sha256(p.read_bytes())}
                     for p in public_files]

    synthetic_values = import_synthetic_inputs()
    build = Path(os.environ["RUNNER_TEMP"]) / "round10-packed-build"
    generated = build / "generated-synthetic-inputs"
    output = Path(os.environ["RUNNER_TEMP"]) / "round4-receipts/packed-record-diagnostics"
    build.mkdir(parents=True, exist_ok=True)
    generated.mkdir(parents=True, exist_ok=True)
    output.mkdir(parents=True, exist_ok=True)
    synthetic_files = []
    synthetic_inputs = []
    for name, data in synthetic_values.items():
        path = generated / name
        path.write_bytes(data)
        synthetic_files.append(path)
        synthetic_inputs.append({"file": name, "bytes": len(data), "sha256": sha256(data)})
    generator_path = ROOT / "scripts/round3_synthetic.py"

    (build / "frozen.rs").write_bytes(parent_raw)
    (build / "packed.rs").write_bytes(candidate_raw)
    harness_raw = HARNESS.encode("utf-8")
    (build / "main.rs").write_bytes(harness_raw)
    report = {
        "status": "PENDING",
        "run_id": os.environ["GITHUB_RUN_ID"],
        "git_sha": os.environ["GITHUB_SHA"],
        "candidate": candidate["name"],
        "parent": parent["name"],
        "candidate_source_sha256": sha256(candidate_raw),
        "candidate_proof_sha256": sha256(candidate_lean),
        "parent_source_sha256": sha256(parent_raw),
        "parent_proof_sha256": sha256(parent_lean),
        "candidate_manifest_sha256": sha256((candidate_path / "manifest.json").read_bytes()),
        "harness_sha256": sha256(harness_raw),
        "compiled_source_copies": {
            "frozen_rs_sha256": sha256((build / "frozen.rs").read_bytes()),
            "packed_rs_sha256": sha256((build / "packed.rs").read_bytes()),
            "main_rs_sha256": sha256((build / "main.rs").read_bytes()),
        },
        "rust_toolchain": "nightly-2026-08-18",
        "generator": {"path": "scripts/round3_synthetic.py", "sha256": sha256(generator_path.read_bytes())},
        "scope": "Native finite comparison of D firstplan and decoded [position,payload] node streams. No token equivalence replay, timers, performance claim, all-input theorem, proof gate, or leaderboard estimate.",
        "public_corpus": public_inputs,
        "synthetic_transfer_inputs": synthetic_inputs,
        "forced_synthetic_d_rows": list(SYNTHETIC_ROWS),
        "pack_limit": PACK_LIMIT,
        "expected_header_savings": "For n < 2^27, saved_words must equal retained node count; for n >= 2^27 the two-word fallback must save zero words.",
        "build_dir": str(build),
        "output_dir": str(output),
    }
    report_path = output / "packed-record.json"
    save(report_path, report)
    with failure_receipt(report, report_path):
        binary = build / "packed-record-check"
        compile_proc = run_logged(
            ["rustc", "+nightly-2026-08-18", "--edition=2021", "-O", "-C", "overflow-checks=yes",
             str(build / "main.rs"), "-o", str(binary)],
            output / "build.log", 180)
        report["compile_exit"] = compile_proc.returncode
        if compile_proc.returncode:
            raise RuntimeError("Packed-record Rust harness compilation failed; retained build.log")

        public_proc = run_logged([str(binary), "public", *map(str, public_files)], output / "public-runtime.log", 180)
        report["public_runtime_exit"] = public_proc.returncode
        if public_proc.returncode:
            raise RuntimeError("Packed-record public D diagnostic failed; retained public-runtime.log")
        public_rows = parse_rows(public_proc.stdout, "R10_PACKED_PUBLIC")
        public_skips = parse_rows(public_proc.stdout, "R10_PACKED_PUBLIC_SKIP")
        public_totals = parse_rows(public_proc.stdout, "R10_PACKED_PUBLIC_TOTAL")
        boundary_rows = parse_rows(public_proc.stdout, "R10_PACKED_BOUNDARY")
        assert len(public_rows) + len(public_skips) == 28
        assert [r["file_index"] for r in sorted(public_rows + public_skips, key=lambda x: x["file_index"])] == list(range(28))
        assert len(public_totals) == len(boundary_rows) == 1
        assert public_totals[0]["files"] == 28
        assert public_totals[0]["d_routes"] == len(public_rows)
        assert public_totals[0]["skipped_non_d"] == len(public_skips)
        assert boundary_rows[0]["single_word_zero_node"] and boundary_rows[0]["cases"] > 0
        assert all(r["firstplan_equal"] and r["node_stream_equal"] for r in public_rows)
        assert all(r["saved_words"] == r["nodes"] for r in public_rows if r["bytes"] < PACK_LIMIT)
        for row in public_rows + public_skips:
            row["corpus_file"] = public_inputs[row["file_index"]]["file"]
            row["input_sha256"] = public_inputs[row["file_index"]]["sha256"]
            row["input_size_verified"] = row["bytes"] == public_inputs[row["file_index"]]["bytes"]
            assert row["input_size_verified"]
        assert all(r["saved_bytes"] == 4 * r["saved_words"] for r in public_rows)

        synthetic_proc = run_logged([str(binary), "synthetic", *map(str, synthetic_files)], output / "synthetic-runtime.log", 180)
        report["synthetic_runtime_exit"] = synthetic_proc.returncode
        if synthetic_proc.returncode:
            raise RuntimeError("Packed-record fixed synthetic D diagnostic failed; retained synthetic-runtime.log")
        synthetic_rows = parse_rows(synthetic_proc.stdout, "R10_PACKED_SYNTHETIC")
        assert len(synthetic_rows) == len(synthetic_inputs) * len(SYNTHETIC_ROWS)
        assert {(r["file_index"], r["forced_d_row"]) for r in synthetic_rows} == {
            (i, row) for i in range(len(synthetic_inputs)) for row in SYNTHETIC_ROWS
        }
        assert all(r["firstplan_equal"] and r["node_stream_equal"] for r in synthetic_rows)
        assert all(r["saved_words"] == r["nodes"] for r in synthetic_rows if r["bytes"] < PACK_LIMIT)
        for row in synthetic_rows:
            source = synthetic_inputs[row["file_index"]]
            row["corpus_file"] = source["file"]
            row["input_sha256"] = source["sha256"]
            row["input_size_verified"] = row["bytes"] == source["bytes"]
            assert row["input_size_verified"]
        assert all(r["saved_bytes"] == 4 * r["saved_words"] for r in synthetic_rows)

        report.update(
            status="VERIFIED_FINITE_PACKED_RECORD_NODE_STREAMS",
            public_route_total=public_totals[0],
            public_d_route_results=public_rows,
            public_non_d_skips=public_skips,
            header_boundary_checks=boundary_rows[0],
            synthetic_d_row_results=synthetic_rows,
            limits=[
                "Finite native node-stream and firstplan equality on observed public D routes and eight fixed generated inputs at D rows 1, 5, and 8.",
                "Fixed generated inputs are public diagnostics, not held-out/private/stage2 or leaderboard estimates.",
                "Does not repeat the existing 444-case full-parser token/decode check or prove all-input equivalence.",
                "Does not run a timer or imply a total-compression-time benefit.",
                "A full official extraction and original obligation gate remain separate."
            ])
        save(report_path, report)
        print("ROUND10_PACKED", json.dumps({
            "status": report["status"], "public_d_routes": len(public_rows), "public_non_d": len(public_skips),
            "synthetic_inputs": len(synthetic_inputs), "synthetic_forced_rows": list(SYNTHETIC_ROWS),
            "synthetic_cases": len(synthetic_rows), "boundary_cases": boundary_rows[0]["cases"]
        }))


if __name__ == "__main__":
    main()
