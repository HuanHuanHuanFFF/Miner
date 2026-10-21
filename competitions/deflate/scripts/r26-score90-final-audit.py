"""Independently replay a completed R26 extension90m scoring analysis.

The audit consumes only a finalized analysis JSON, a saved official API capture,
and a saved rules capture. It never contacts services, starts CI, or benchmarks.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib
import importlib.util
import json
import math
import statistics
import sys
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SCRIPTS = ROOT / "scripts"
sys.path.insert(0, str(SCRIPTS))
M = importlib.import_module("r26-score-map")
SPEC = importlib.util.spec_from_file_location(
    "r26_extension_score_audit", SCRIPTS / "r26-extension-score-audit.py"
)
assert SPEC and SPEC.loader
SCORE_AUDIT = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(SCORE_AUDIT)

EXPECTED_RUNS = 11
EXPECTED_PROCESSES = 132
EXPECTED_MECHANISMS = 6
TOL = 1e-10


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_json(path: Path):
    return json.loads(path.read_bytes())


def write_json(path: Path, value) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def resolve_evidence_path(value: str) -> Path:
    normalized = value.replace("\\", "/")
    path = Path(normalized)
    if not path.is_absolute():
        path = ROOT / path
    resolved = path.resolve()
    resolved.relative_to(ROOT.resolve())
    return resolved


def parse_stream(path: Path, run_id: str) -> dict:
    objects = [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]
    assert objects and objects[0].get("kind") == "meta", path
    meta = objects[0]
    rows = [obj for obj in objects[1:] if obj.get("kind") == "file"]
    assert len(rows) == 28, (path, len(rows))
    method_names = [name for name in meta["methods"] if name != "incumbent"]
    assert len(method_names) == 1, (path, method_names)
    method = method_names[0]
    assert meta["warmup_rounds"] == 1 and meta["measured_rounds"] == 11, path
    block = 2 if path.name.startswith("round2-") else 1 if path.name.startswith("round1-") else None
    assert block in (1, 2), path
    x_values, y_values, input_hashes = [], [], {}
    for row in rows:
        assert row.get("corpus") == "corpus-stage1", path
        assert row["file"] not in input_hashes, (path, row["file"])
        input_hashes[row["file"]] = row["sha256"]
        candidate = row["methods"][method]
        incumbent = row["methods"]["incumbent"]
        candidate_times = [float(rep["total_s"]) for rep in candidate["reps"] if rep["phase"] == "measured"]
        incumbent_times = [float(rep["total_s"]) for rep in incumbent["reps"] if rep["phase"] == "measured"]
        assert len(candidate_times) == len(incumbent_times) == 11, path
        x_values.append(statistics.median(candidate_times) / statistics.median(incumbent_times))
        y_values.append(100.0 * float(candidate["output_bytes"]) / float(row["raw_bytes"]))
    meta_method = meta["methods"][method]
    incumbent_meta = meta["methods"]["incumbent"]
    return {
        "run_id": str(run_id), "block": block, "method": method,
        "process_role": "same_binary_copy_control" if method.endswith("-shadow") else "original_protocol_process",
        "source_sha256": meta_method["source_sha256"], "library_sha256": meta_method["lib_sha256"],
        "incumbent_source_sha256": incumbent_meta["source_sha256"],
        "incumbent_library_sha256": incumbent_meta["lib_sha256"],
        "cpu_model": meta.get("cpu_model"), "rustc_version": meta.get("rustc_version"),
        "engine_sha256": (meta.get("benchmark_provenance") or {}).get("engine_sha256"),
        "template_sha256": (meta.get("benchmark_provenance") or {}).get("template_sha256"),
        "host_sha256": (meta.get("benchmark_provenance") or {}).get("host_sha256"),
        "path": path.relative_to(ROOT).as_posix(), "raw_jsonl_sha256": digest(path),
        "file_count": len(rows), "warmup_rounds": 1, "measured_rounds": 11,
        "x_equal_file_mean_of_file_medians": statistics.mean(x_values),
        "y_mean_file_compression_pct": statistics.mean(y_values),
        "input_hashes_by_file": input_hashes,
    }


def summarize_shares(rows: list[dict], share_key: str) -> dict:
    values = [float(row[share_key]) for row in rows]
    positive = [v for v in values if v > 0.0]
    return {
        "view_count": len(values), "zero_count": sum(v == 0.0 for v in values),
        "median_including_zero_pct": statistics.median(values) if values else None,
        "positive_min_pct": min(positive) if positive else None,
        "positive_max_pct": max(positive) if positive else None,
        "share_range_including_zero_pct": [min(values), max(values)] if values else None,
    }


def make_markdown(result: dict) -> str:
    lines = [
        "# Extension90m 评分层独立复核（gate 状态另行判断）", "",
        f"- 官方快照：`{result['current_snapshot']['snapshot_id']}`；捕获目录 `{result['official_capture']['path']}`。",
        f"- 标准 run：{result['run_audit']['run_count']}；原协议配对进程：{result['run_audit']['original_protocol_paired_process_count']}。",
        f"- 原始 JSONL 哈希：{result['run_audit']['all_raw_hashes_match_analysis']}；评分坐标/份额重算误差最大值：X `{result['projection_audit']['max_abs_x_error']:.3g}`，Y `{result['projection_audit']['max_abs_y_error_pp']:.3g}` pp，份额 `{result['projection_audit']['max_abs_share_error_pp']:.3g}` pp。",
        f"- 唯一 Rust 哈希数：{result['mechanism_audit']['unique_rust_hash_count']}；同版本副本始终单列控制，不并入候选主版本样本。",
        "",
        "| 机制 | Rust SHA-256 | 样本身份 | run角色 | 校准 | 视图数 | 零份额 | 中位份额 (%) | 正份额范围 (%) |",
        "|---|---|---|---|---|---:|---:|---:|---:|",
    ]
    for row in result["share_summaries"]:
        rg = row["current_replayed"]
        interval = "—" if rg["positive_min_pct"] is None else f"{rg['positive_min_pct']:.6f}–{rg['positive_max_pct']:.6f}"
        lines.append(f"| {row['mechanism_id']} | `{row['rust_sha256'][:12]}…` | {row['sample_class']} | {row['run_role']} | {row['calibration']} | {rg['view_count']} | {rg['zero_count']} | {rg['median_including_zero_pct']:.6f} | {interval} |")
    lines += [
        "", "## 评分器来源字节核对", "",
        f"当前 close rules scorer `{result['scorer_byte_comparison']['latest_rules_scorer_sha256']}`；`analyze-round26.py` 指向的 scorer `{result['scorer_byte_comparison']['analyze_round26_scorer_sha256']}`；字节一致：`{result['scorer_byte_comparison']['byte_identical']}`。旧脚本未修改。",
        "", "完整逐流程 X/Y、候选与同 binary copy 的投影坐标、raw receipt 哈希、官方 scorer replay 见同名机器 JSON。所有份额均为该官方快照下的几何单点投影；gate/proof 状态不由本评分审计推断。", "",
    ]
    return "\n".join(lines)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--analysis", type=Path, required=True, help="final-analysis.json")
    parser.add_argument("--capture", type=Path, required=True, help="saved official API capture directory")
    parser.add_argument("--rules", type=Path, required=True, help="saved official rules capture directory")
    parser.add_argument("--output", type=Path, required=True, help="machine JSON output file; Markdown sibling is also written")
    parser.add_argument("--expected-runs", type=int, default=EXPECTED_RUNS)
    parser.add_argument("--expected-processes", type=int, default=EXPECTED_PROCESSES)
    parser.add_argument("--expected-mechanisms", type=int, default=EXPECTED_MECHANISMS)
    args = parser.parse_args()

    analysis_path, capture_path, rules_path = map(lambda p: p.resolve(), (args.analysis, args.capture, args.rules))
    for path in (analysis_path, capture_path, rules_path):
        path.relative_to(ROOT.resolve())
    analysis = read_json(analysis_path)
    raw_audit = {str(key).replace("\\", "/"): value for key, value in analysis["raw_input_audit"].items()}
    runs = {str(row["run_id"]): row for row in analysis["runs"]}
    assert len(runs) == len(analysis["runs"]), "duplicate run IDs in analysis"
    assert len(runs) == args.expected_runs, (len(runs), args.expected_runs)
    assert len(raw_audit) == args.expected_processes, (len(raw_audit), args.expected_processes)
    assert int(analysis.get("paired_processes", -1)) == args.expected_processes

    raw_processes = []
    by_key = {}
    actual_paths = set()
    for rel_path, expected in raw_audit.items():
        path = resolve_evidence_path(rel_path)
        process = parse_stream(path, str(path.parts[-4]))
        assert process["raw_jsonl_sha256"] == expected["sha256"], (rel_path, "raw hash mismatch")
        assert process["source_sha256"] == expected["source_hashes"]["parse.rs"], (rel_path, "Rust hash mismatch")
        method = process["method"]
        key = (process["run_id"], process["block"], method)
        assert key not in by_key, ("duplicate process key", key)
        assert process["run_id"] in runs, ("run absent from analysis", process["run_id"])
        by_key[key] = process
        actual_paths.add(process["path"].replace("\\", "/"))
        raw_processes.append(process)
    assert len(raw_processes) == args.expected_processes

    for run_id, run in runs.items():
        observed = sum(row["run_id"] == run_id for row in raw_processes)
        assert observed == int(run["paired_processes"]), (run_id, observed, run["paired_processes"])
    input_hashes = raw_processes[0]["input_hashes_by_file"]
    assert all(row["input_hashes_by_file"] == input_hashes for row in raw_processes), "corpus input hashes differ"

    mechanisms = {}
    observations = []
    observation_keys = set()
    for candidate in analysis["candidates"]:
        rust_hash = candidate["rust_sha256"]
        mechanisms.setdefault(rust_hash, set()).add(candidate["candidate"])
        for obs in candidate["observations"]:
            run_id, block, method = str(obs["run_id"]), int(obs["block"]), obs["entry_name"]
            process = by_key[(run_id, block, method)]
            anchor = by_key[(run_id, block, obs["anchor_name"])]
            assert process["source_sha256"] == rust_hash, (candidate["candidate"], method, "Rust hash mismatch")
            assert obs["entry_role"] in ("candidate", "control")
            expected_class = "candidate_main" if obs["entry_role"] == "candidate" else "same_binary_copy_control"
            key = (rust_hash, run_id, block, method, obs["calibration"])
            assert key not in observation_keys, ("duplicate candidate observation", key)
            observation_keys.add(key)
            # The raw projection is completed after the official capture is replayed below.
            observations.append({
                "mechanism_id": None, "candidate": candidate["candidate"], "rust_sha256": rust_hash,
                "run_id": run_id, "block": block, "role": obs.get("role"),
                "entry_role": obs["entry_role"], "sample_class": expected_class,
                "method": method, "calibration": obs["calibration"], "anchor_method": obs["anchor_name"],
                "raw_x": process["x_equal_file_mean_of_file_medians"],
                "raw_y_pct": process["y_mean_file_compression_pct"],
                "anchor_raw_x": anchor["x_equal_file_mean_of_file_medians"],
                "anchor_raw_y_pct": anchor["y_mean_file_compression_pct"],
                "analysis_x": float(obs["projected_time"]), "analysis_y_pct": float(obs["projected_size_pct"]),
                "analysis_share_pct": float(obs["single_pool_share_pct"]),
            })
    assert len(mechanisms) == args.expected_mechanisms, (len(mechanisms), args.expected_mechanisms)

    # Ensure each observed main/copy pair really is the same binary in its own run/block.
    binary_pair_checks = []
    for rust_hash, candidate_names in mechanisms.items():
        name_prefixes = set(candidate_names)
        possible_mains = {row["method"] for row in raw_processes
                          if row["source_sha256"] == rust_hash and not row["method"].endswith("-shadow")}
        for main_name in sorted(possible_mains):
            copy_name = main_name + "-shadow"
            for run_id, block, _ in {(p["run_id"], p["block"], p["method"]) for p in raw_processes
                                     if p["method"] == main_name}:
                main = by_key.get((run_id, block, main_name))
                copy = by_key.get((run_id, block, copy_name))
                if copy is not None:
                    assert main["source_sha256"] == copy["source_sha256"] == rust_hash
                    assert main["library_sha256"] == copy["library_sha256"]
                    binary_pair_checks.append({"run_id": run_id, "block": block,
                                               "main": main_name, "copy": copy_name,
                                               "rust_sha256": rust_hash,
                                               "binary_sha256": main["library_sha256"],
                                               "same_binary": True})

    replay = M.Replay(capture_path, rules_path)
    api_audit = M.audit(replay)
    analysis_snapshot = analysis.get("snapshot", {}).get("snapshot_id")
    assert str(analysis_snapshot) == str(replay.context["snapshot_id"]), (analysis_snapshot, replay.context["snapshot_id"])
    capture_receipt = read_json(capture_path / "receipt.json")
    anchor_metrics = replay.byid["658"]["metrics"]
    anchor_official_x = float(anchor_metrics["balanced_time_ratio"])
    anchor_official_y = float(anchor_metrics["mean_file_compression_pct"])

    x_errors, y_errors, share_errors = [], [], []
    for row in observations:
        projected_x = anchor_official_x * row["raw_x"] / row["anchor_raw_x"]
        projected_y = anchor_official_y * row["raw_y_pct"] / row["anchor_raw_y_pct"]
        terms = SCORE_AUDIT.score_one(replay, f"final-{len(x_errors)}", projected_x, projected_y)
        replayed_share = float(terms.get("share_pct", 0.0))
        x_errors.append(abs(projected_x - row["analysis_x"]))
        y_errors.append(abs(projected_y - row["analysis_y_pct"]))
        share_errors.append(abs(replayed_share - row["analysis_share_pct"]))
        row.update({
            "projected_x": projected_x, "projected_y_pct": projected_y,
            "replayed_share_pct": replayed_share,
            "replayed_predecessor": terms.get("predecessor"),
            "replayed_successor": terms.get("successor"),
            "coordinate_x_error": projected_x - row["analysis_x"],
            "coordinate_y_error_pp": projected_y - row["analysis_y_pct"],
            "share_error_pp": replayed_share - row["analysis_share_pct"],
        })
    assert max(x_errors, default=0) < TOL
    assert max(y_errors, default=0) < TOL
    assert max(share_errors, default=0) < TOL

    tested_mechanisms_path = ROOT / "evidence/round26/extension90m/score-audit/tested-mechanisms.json"
    tested_mechanisms = read_json(tested_mechanisms_path) if tested_mechanisms_path.exists() else None
    mechanism_map = {}
    if tested_mechanisms:
        for item in tested_mechanisms.get("tested_mechanisms", []):
            mechanism_map[item["rust_sha256"]] = item["id"]
        assert set(mechanisms).issubset(mechanism_map), "analysis contains a Rust hash absent from tested-mechanisms map"
    for row in observations:
        row["mechanism_id"] = mechanism_map.get(row["rust_sha256"], ", ".join(sorted(mechanisms[row["rust_sha256"]])))

    summary_groups = defaultdict(list)
    for row in observations:
        group = (row["mechanism_id"], row["rust_sha256"], row["sample_class"], row["role"], row["calibration"])
        summary_groups[group].append(row)
    share_summaries = []
    for (mechanism_id, rust_hash, sample_class, run_role, calibration), rows in sorted(summary_groups.items()):
        share_summaries.append({
            "mechanism_id": mechanism_id, "rust_sha256": rust_hash,
            "sample_class": sample_class, "run_role": run_role, "calibration": calibration,
            "current_replayed": summarize_shares(rows, "replayed_share_pct"),
            "analysis_values": summarize_shares(rows, "analysis_share_pct"),
            "sample_warning": "These are run/block × calibration views; primary/shadow are alternate anchor projections, not independent samples. Copy-control views are not candidate confirmation samples.",
        })

    rules_scorer = rules_path / "validator--scoring--pareto.py"
    analyze26_scorer = ROOT / "evidence/round26/official-rules-start-live/validator--scoring--pareto.py"
    rules_scorer_sha = digest(rules_scorer)
    analyze26_scorer_sha = digest(analyze26_scorer) if analyze26_scorer.exists() else None
    capture_receipt_sha = digest(capture_path / "receipt.json")
    rules_receipt_sha = digest(rules_path / "receipt.json")
    raw_hash_manifest = {row["path"]: {"sha256": row["raw_jsonl_sha256"], "matches_analysis": True}
                         for row in raw_processes}
    result = {
        "status": "VERIFIED_SCORING_REPLAY_ONLY_GATES_NOT_ASSESSED",
        "checked_utc": datetime.now(timezone.utc).isoformat(),
        "analysis": {"path": analysis_path.relative_to(ROOT).as_posix(), "sha256": digest(analysis_path),
                     "snapshot_id": analysis_snapshot, "status": analysis.get("status")},
        "current_snapshot": replay.context,
        "official_capture": {
            "path": capture_path.relative_to(ROOT).as_posix(),
            "receipt_sha256": capture_receipt_sha,
            "retrieval_start_utc": capture_receipt.get("retrieval_start_utc"),
            "retrieval_end_utc": capture_receipt.get("retrieval_end_utc"),
            "raw_response_files": capture_receipt.get("raw_response_files"),
        },
        "official_rules": {"path": rules_path.relative_to(ROOT).as_posix(),
                           "receipt_sha256": rules_receipt_sha,
                           "scoring_source_sha256": rules_scorer_sha},
        "run_audit": {
            "run_count": len(runs), "expected_run_count": args.expected_runs,
            "original_protocol_paired_process_count": len(raw_processes),
            "expected_process_count": args.expected_processes,
            "analysis_paired_process_count": analysis.get("paired_processes"),
            "per_run": [{"run_id": run_id, "batch": row.get("batch"), "role": row.get("role"),
                         "declared_processes": int(row["paired_processes"]),
                         "raw_processes_verified": sum(p["run_id"] == run_id for p in raw_processes),
                         "ci_conclusion_recorded": row.get("ci_conclusion"),
                         "failure_count_recorded": len(row.get("failures", [])),
                         "cpu_model": row.get("environment", {}).get("cpu_model"),
                         "rustc_version": row.get("environment", {}).get("rustc_version")}
                        for run_id, row in runs.items()],
            "all_raw_hashes_match_analysis": len(raw_hash_manifest) == args.expected_processes,
            "raw_hash_manifest": raw_hash_manifest,
            "raw_processes": [{k: v for k, v in row.items() if k != "input_hashes_by_file"}
                               for row in raw_processes],
            "corpus_file_count": len(input_hashes), "corpus_input_sha256_by_file": input_hashes,
        },
        "mechanism_audit": {
            "unique_rust_hash_count": len(mechanisms),
            "mechanisms": [{"mechanism_id": mechanism_map.get(rust_hash, ", ".join(sorted(names))),
                            "rust_sha256": rust_hash, "candidate_alias_names": sorted(names),
                            "observation_count": sum(row["rust_sha256"] == rust_hash for row in observations)}
                           for rust_hash, names in sorted(mechanisms.items())],
            "same_binary_main_copy_pairs_verified": len(binary_pair_checks),
            "same_binary_main_copy_checks": binary_pair_checks,
            "tested_mechanisms_map_path": tested_mechanisms_path.relative_to(ROOT).as_posix() if tested_mechanisms else None,
            "tested_mechanisms_map_sha256": digest(tested_mechanisms_path) if tested_mechanisms else None,
        },
        "projection_formula": {
            "x": "official #658 balanced_time_ratio * measured method equal-file mean(median(candidate total_s reps)/median(incumbent total_s reps)) / same-run-block calibration anchor raw X",
            "y": "official #658 mean_file_compression_pct * measured method mean file compression pct / same-run-block calibration anchor raw Y",
            "pool_share": "independently recomputed from captured Pareto base plus one point using the captured official bounds and local-global-improvement-space-log rule",
        },
        "projection_audit": {
            "observation_count": len(observations),
            "candidate_main_observation_count": sum(row["sample_class"] == "candidate_main" for row in observations),
            "same_binary_copy_control_observation_count": sum(row["sample_class"] == "same_binary_copy_control" for row in observations),
            "max_abs_x_error": max(x_errors, default=0),
            "max_abs_y_error_pp": max(y_errors, default=0),
            "max_abs_share_error_pp": max(share_errors, default=0),
            "observations": observations,
        },
        "share_summaries": share_summaries,
        "official_api_replay": {k: api_audit[k] for k in [
            "status", "input_rows", "admitted_bounded_rows", "reconstructed_frontier",
            "frontier_ids_match", "raw_and_derived_hashes_match",
            "max_independent_api_error_pp", "max_independent_official_scorer_error_pp",
            "max_api_payable_error_fraction", "max_weights_by_hotkey_error_fraction",
            "sum_geometric_fraction", "sum_payable_fraction", "api_payable_competition_weight",
            "api_unpaid_competition_weight", "api_chain_accepted"]},
        "scorer_byte_comparison": {
            "latest_rules_scorer_path": rules_scorer.relative_to(ROOT).as_posix(),
            "latest_rules_scorer_sha256": rules_scorer_sha,
            "analyze_round26_scorer_path": analyze26_scorer.relative_to(ROOT).as_posix(),
            "analyze_round26_scorer_sha256": analyze26_scorer_sha,
            "byte_identical": (rules_scorer_sha == analyze26_scorer_sha) if analyze26_scorer_sha else None,
            "analyze_round26_script_sha256": digest(SCRIPTS / "analyze-round26.py"),
            "old_script_modified": False,
        },
        "limitations": [
            "This verifies public snapshot geometry, source-backed two-axis projections, raw receipt identity, and scoring replay only.",
            "Candidate main and same-binary copy control are kept separate; calibration views do not create independent samples.",
            "Formal gate/proof acceptance, admission, registration attribution, and realized payout are not inferred from this scoring audit.",
            "A mismatch between the latest scorer and analyze-round26's previously configured scorer is reported only; the old script is not modified.",
        ],
    }
    out = args.output.resolve()
    out.relative_to(ROOT.resolve())
    write_json(out, result)
    markdown_path = out.with_suffix(".md")
    markdown_path.write_text(make_markdown(result), encoding="utf-8")
    print(json.dumps({"status": result["status"], "snapshot_id": replay.context["snapshot_id"],
                      "runs": len(runs), "raw_processes": len(raw_processes),
                      "unique_rust_hashes": len(mechanisms),
                      "observations": len(observations),
                      "max_x_error": max(x_errors, default=0),
                      "max_y_error_pp": max(y_errors, default=0),
                      "max_share_error_pp": max(share_errors, default=0),
                      "analyze26_scorer_bytes_identical": result["scorer_byte_comparison"]["byte_identical"],
                      "output": out.relative_to(ROOT).as_posix()}, ensure_ascii=False))


if __name__ == "__main__":
    main()
