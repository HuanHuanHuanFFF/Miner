"""Audit two-runner E1 proof2 raw receipts and replay coordinates on official snapshot 29966."""
from __future__ import annotations

import hashlib
import importlib
import importlib.util
import json
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

ANALYSIS_PATH = ROOT / "evidence/round26/extension90m/e1-confirm-first-analysis.json"
CAPTURE = ROOT / "evidence/round26/extension90m/official-e2"
RULES = ROOT / "evidence/round26/extension90m/rules-start"
RUN_GATES = {
    "38270719542": ROOT / "evidence/round26/38270719542/confirm90-e1-a/gate",
    "38270747043": ROOT / "evidence/round26/38270747043/confirm90-e1-b/gate",
}
PROOF2_RECEIPT = ROOT / "evidence/round26/38270692372/gate-90-e1-proof2/exact-gate/exact-gate/gate-receipt.json"
PROOF2_LOG = ROOT / "evidence/round26/38270692372/gate-90-e1-proof2/exact-gate/exact-gate/logs/005-lake.log"
PROOF2_ENTRY = ROOT / "evidence/round26/extension90m/route-e/e1-proof2-entry.json"
PROOF3_ENTRY = ROOT / "evidence/round26/extension90m/route-e/e1-proof3-entry.json"
OUTPUT_DIR = ROOT / "evidence/round26/extension90m/score-audit"
OUTPUT_JSON = OUTPUT_DIR / "e1-confirm-29966.json"
OUTPUT_MD = OUTPUT_DIR / "e1-confirm-29966.md"
EXPECTED_METHODS = {
    "probe3", "r3-432-fast3", "public432", "public658", "public658-shadow",
    "r26-e-658-short-same-proof2", "r26-e-658-short-same-proof2-shadow",
}


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_json(path: Path):
    return json.loads(path.read_bytes())


def write_json(path: Path, value) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def parse_stream(path: Path, run_id: str, block: int) -> dict:
    objects = [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]
    assert objects and objects[0].get("kind") == "meta"
    meta = objects[0]
    rows = [obj for obj in objects[1:] if obj.get("kind") == "file"]
    assert len(rows) == 28, (path, len(rows))
    methods = [name for name in meta["methods"] if name != "incumbent"]
    assert len(methods) == 1
    method = methods[0]
    assert meta["warmup_rounds"] == 1 and meta["measured_rounds"] == 11
    time_values, size_values, input_hashes = [], [], {}
    for row in rows:
        assert row["corpus"] == "corpus-stage1"
        assert row["file"] not in input_hashes
        input_hashes[row["file"]] = row["sha256"]
        measured = row["methods"][method]
        incumbent = row["methods"]["incumbent"]
        candidate_times = [float(x["total_s"]) for x in measured["reps"] if x["phase"] == "measured"]
        incumbent_times = [float(x["total_s"]) for x in incumbent["reps"] if x["phase"] == "measured"]
        assert len(candidate_times) == len(incumbent_times) == 11
        time_values.append(statistics.median(candidate_times) / statistics.median(incumbent_times))
        size_values.append(100.0 * float(measured["output_bytes"]) / float(row["raw_bytes"]))
    return {
        "run_id": run_id, "block": block, "method": method,
        "process_role": "same_binary_copy_control" if method.endswith("-shadow") else "original_protocol_process",
        "source_sha256": meta["methods"][method]["source_sha256"],
        "library_sha256": meta["methods"][method]["lib_sha256"],
        "incumbent_source_sha256": meta["methods"]["incumbent"]["source_sha256"],
        "incumbent_library_sha256": meta["methods"]["incumbent"]["lib_sha256"],
        "cpu_model": meta["cpu_model"], "rustc_version": meta["rustc_version"],
        "engine_sha256": meta["benchmark_provenance"]["engine_sha256"],
        "template_sha256": meta["benchmark_provenance"]["template_sha256"],
        "host_sha256": meta["benchmark_provenance"]["host_sha256"],
        "path": path.relative_to(ROOT).as_posix(), "raw_jsonl_sha256": digest(path),
        "file_count": len(rows), "warmup_rounds": 1, "measured_rounds": 11,
        "x_balanced_time_ratio_equal_file_mean": statistics.mean(time_values),
        "y_mean_file_compression_pct": statistics.mean(size_values),
        "input_hashes_by_file": input_hashes,
    }


def summarize(rows: list[dict], key: str) -> dict:
    values = [float(row[key]) for row in rows]
    positive = [value for value in values if value > 0]
    return {
        "n_views": len(values), "zero_count": sum(value == 0 for value in values),
        "min_including_zero_pct": min(values) if values else None,
        "max_pct": max(values) if values else None,
        "positive_range_pct": [min(positive), max(positive)] if positive else None,
    }


def build_markdown(result: dict) -> str:
    lines = [
        "# E1 双 runner 确认原始审计", "",
        (f"原始确认分析引用 snapshot `{result['analysis_snapshot']['snapshot_id']}`（freshness `{result['analysis_snapshot'].get('freshness')}`）；" 
         f"现按最新完整官方捕获 `{result['current_snapshot']['snapshot_id']}` 重算，identity 与 capture 均为 29966。"),
        (f"两 runner `{result['raw_process_count']}` 条原始流程，JSONL 哈希全部匹配分析清单；" 
         f"X 投影误差 `{result['projection_audit']['max_abs_projection_x_error']:.3g}`，Y 误差 "
         f"`{result['projection_audit']['max_abs_projection_y_error_pp']:.3g}` pp；当前份额按完整 snapshot 29966 重算。"),
        "逐流 X/Y 和哈希见机器 JSON `raw_processes` / `raw_hash_manifest`。", "",
        "## E1 主版本和副本投影", "",
        "candidate 与同 Rust/同 binary 的 shadow 分开列；primary/shadow 是两种锚点校准，不是独立样本。", "",
        "| Runner | Block | 流程身份 | 校准 | raw X | raw Y (%) | Projected X | Old 29957 share (%) | Current 29966 share (%) |",
        "|---|---:|---|---|---:|---:|---:|---:|---:|",
    ]
    for row in result["projections"]:
        lines.append(f"| {row['runner_id']} | {row['block']} | {row['sample_class']} | {row['calibration']} | {row['raw_x']:.9f} | {row['raw_y_pct']:.9f} | {row['projected_x']:.12f} | {row['stored_29957_share_pct']:.9f} | {row['recomputed_29966_share_pct']:.9f} |")
    lines += ["", "## 零次数与份额范围", "",
              "以下每组按 runner × main/copy × 校准统计两个 block；ALL 按四个 block 汇总。", "",
              "| Runner | 流程身份 | 校准 | 行数 | Old 29957 零数 | Old 正份额范围 (%) | Current 29966 零数 | Current 正份额范围 (%) |",
              "|---|---|---|---:|---:|---:|---:|---:|"]
    for row in result["share_summaries_by_runner_role_calibration"]:
        old = row["stored_29957"]
        current = row["current_29966"]
        old_range = "—" if old["positive_range_pct"] is None else f"{old['positive_range_pct'][0]:.6f}–{old['positive_range_pct'][1]:.6f}"
        current_range = "—" if current["positive_range_pct"] is None else f"{current['positive_range_pct'][0]:.6f}–{current['positive_range_pct'][1]:.6f}"
        lines.append(f"| {row['runner_id']} | {row['sample_class']} | {row['calibration']} | {row['n_views']} | {old['zero_count']} | {old_range} | {current['zero_count']} | {current_range} |")
    lines += ["", "## 同二进制控制与证明边界", "",
              f"E1 main/copy 的同 binary 时间差范围 `{result['same_binary_controls']['candidate_copy_gap_range_pct'][0]:.6f}%` 到 `{result['same_binary_controls']['candidate_copy_gap_range_pct'][1]:.6f}%`；#658 anchor main/shadow 差范围 `{result['same_binary_controls']['public658_gap_range_pct'][0]:.6f}%` 到 `{result['same_binary_controls']['public658_gap_range_pct'][1]:.6f}%`。", 
              f"被测 Rust `{result['proof_binding']['measured_rust_sha256']}`，Lean `{result['proof_binding']['measured_lean_sha256']}`。proof2 gate 状态 `{result['proof_binding']['proof2_gate_receipt_status']}`（receipt `38270692372`），原始日志记录 `{result['proof_binding']['no_goals_error_count']}` 次 `No goals to be solved`；当前 proof3 Lean `{result['proof_binding']['proof3_lean_sha256']}` 尚无其精确 pair 的最终验收回执，因此本批不是 proof3 最终确认。", "",
              "保留旧 29957 记录作为历史列；29966 重算不覆盖旧报告。份额为几何单点投影，不是正式 admission 或实际奖励。", ""]
    return "\n".join(lines)


def main() -> None:
    analysis = read_json(ANALYSIS_PATH)
    assert str(analysis["snapshot"]["snapshot_id"]) == "29957"
    assert len(analysis["runs"]) == 2 and sum(int(row["paired_processes"]) for row in analysis["runs"]) == 28
    run_info = {str(row["run_id"]): row for row in analysis["runs"]}

    raw_processes = []
    for run_id, gate in RUN_GATES.items():
        run_rows = []
        for block in (1, 2):
            paths = sorted(gate.glob(f"round{block}-*.jsonl"))
            assert len(paths) == 7
            block_rows = [parse_stream(path, run_id, block) for path in paths]
            assert {row["method"] for row in block_rows} == EXPECTED_METHODS
            file_hashes = block_rows[0]["input_hashes_by_file"]
            assert all(row["input_hashes_by_file"] == file_hashes for row in block_rows)
            assert len({(row["incumbent_source_sha256"], row["incumbent_library_sha256"])
                        for row in block_rows}) == 1
            run_rows.extend(block_rows)
        assert len(run_rows) == 14
        raw_processes.extend(run_rows)
    assert len(raw_processes) == 28

    audit_inputs = {key.replace("\\", "/"): value
                    for key, value in analysis["raw_input_audit"].items()}
    raw_hash_manifest = {}
    for process in raw_processes:
        expected = audit_inputs.get(process["path"])
        assert expected and expected["sha256"] == process["raw_jsonl_sha256"]
        assert expected["source_hashes"]["parse.rs"] == process["source_sha256"]
        raw_hash_manifest[process["path"]] = {
            "sha256": process["raw_jsonl_sha256"], "matches_analysis": True,
        }
    raw_by_key = {(row["run_id"], row["block"], row["method"]): row for row in raw_processes}

    replay = M.Replay(CAPTURE, RULES)
    api_audit = M.audit(replay)
    assert str(replay.context["snapshot_id"]) == "29966"
    capture_receipt = read_json(CAPTURE / "receipt.json")
    anchor = replay.byid["658"]["metrics"]
    anchor_x = float(anchor["balanced_time_ratio"])
    anchor_y = float(anchor["mean_file_compression_pct"])
    candidate = analysis["candidates"][0]
    candidate_name = candidate["candidate"]
    projections, x_errors, y_errors = [], [], []
    for obs in candidate["observations"]:
        run_id, block = str(obs["run_id"]), int(obs["block"])
        method = obs["entry_name"]
        process = raw_by_key[(run_id, block, method)]
        anchor_process = raw_by_key[(run_id, block, obs["anchor_name"])]
        x = anchor_x * process["x_balanced_time_ratio_equal_file_mean"] / anchor_process["x_balanced_time_ratio_equal_file_mean"]
        y = anchor_y + process["y_mean_file_compression_pct"] - anchor_process["y_mean_file_compression_pct"]
        x_errors.append(abs(x - float(obs["projected_time"])))
        y_errors.append(abs(y - float(obs["projected_size_pct"])))
        share_name = f"e1-{run_id}-{block}-{obs['entry_role']}-{obs['calibration']}"
        terms = SCORE_AUDIT.score_one(replay, share_name, x, y)
        projections.append({
            "runner_id": run_id, "cpu_model": run_info[run_id]["environment"]["cpu_model"],
            "block": block, "role": obs["role"], "entry_role": obs["entry_role"],
            "sample_class": "candidate_main" if obs["entry_role"] == "candidate" else "same_binary_copy_control",
            "method": method, "calibration": obs["calibration"], "anchor_process": obs["anchor_name"],
            "rust_sha256": process["source_sha256"], "library_sha256": process["library_sha256"],
            "raw_x": process["x_balanced_time_ratio_equal_file_mean"],
            "raw_y_pct": process["y_mean_file_compression_pct"],
            "anchor_raw_x": anchor_process["x_balanced_time_ratio_equal_file_mean"],
            "anchor_raw_y_pct": anchor_process["y_mean_file_compression_pct"],
            "projected_x": x, "projected_y_pct": y,
            "analysis_projected_x": float(obs["projected_time"]),
            "analysis_projected_y_pct": float(obs["projected_size_pct"]),
            "stored_29957_share_pct": float(obs["single_pool_share_pct"]),
            "recomputed_29966_share_pct": float(terms.get("share_pct", 0.0)),
            "recomputed_29966_neighbors": [terms.get("predecessor"), terms.get("successor")],
        })
    assert len(projections) == 16
    assert sum(row["entry_role"] == "candidate" for row in projections) == 8
    assert sum(row["entry_role"] == "control" for row in projections) == 8

    # Verify identical Rust/binary candidates and all recorded same-binary timing gaps.
    controls_in_analysis = {(str(row["run_id"]), int(row["block"]), row["shadow"]): row
                            for row in analysis["same_source_controls"]}
    same_binary_controls = []
    for run_id in RUN_GATES:
        for block in (1, 2):
            main = raw_by_key[(run_id, block, candidate_name)]
            copy = raw_by_key[(run_id, block, candidate_name + "-shadow")]
            assert main["source_sha256"] == copy["source_sha256"]
            assert main["library_sha256"] == copy["library_sha256"]
            for parent_name, shadow_name in [(candidate_name, candidate_name + "-shadow"),
                                             ("public658", "public658-shadow")]:
                parent = raw_by_key[(run_id, block, parent_name)]
                shadow = raw_by_key[(run_id, block, shadow_name)]
                gap = 100 * (shadow["x_balanced_time_ratio_equal_file_mean"]
                             / parent["x_balanced_time_ratio_equal_file_mean"] - 1)
                recorded = controls_in_analysis[(run_id, block, shadow_name)]
                assert abs(gap - float(recorded["relative_time_gap_pct"])) < 1e-10
                same_binary_controls.append({
                    "run_id": run_id, "block": block, "parent": parent_name, "shadow": shadow_name,
                    "parent_executable_sha256": parent["library_sha256"],
                    "shadow_executable_sha256": shadow["library_sha256"],
                    "relative_shadow_minus_parent_time_pct": gap,
                    "analysis_relative_gap_pct": float(recorded["relative_time_gap_pct"]),
                })

    candidate_copy_gaps = [row["relative_shadow_minus_parent_time_pct"] for row in same_binary_controls
                           if row["parent"].startswith("r26-e-")]
    public658_gaps = [row["relative_shadow_minus_parent_time_pct"] for row in same_binary_controls
                      if row["parent"] == "public658"]

    summary_groups = defaultdict(list)
    for row in projections:
        key = (row["runner_id"], row["sample_class"], row["calibration"])
        summary_groups[key].append(row)
        summary_groups[("ALL", row["sample_class"], row["calibration"])].append(row)
    summaries = []
    for (run_id, sample_class, calibration), rows in sorted(summary_groups.items()):
        summaries.append({
            "runner_id": run_id, "sample_class": sample_class, "calibration": calibration,
            "n_views": len(rows),
            "stored_29957": summarize([{"share_pct": row["stored_29957_share_pct"]} for row in rows], "share_pct"),
            "current_29966": summarize([{"share_pct": row["recomputed_29966_share_pct"]} for row in rows], "share_pct"),
        })

    proof2_entry = read_json(PROOF2_ENTRY)
    proof3_entry = read_json(PROOF3_ENTRY)
    proof2_receipt = read_json(PROOF2_RECEIPT)
    proof2_log = PROOF2_LOG.read_text(encoding="utf-8", errors="replace")
    no_goals_lines = [line.strip() for line in proof2_log.splitlines() if "No goals to be solved" in line]
    assert proof2_entry["hashes"]["parse.rs"] == candidate["rust_sha256"]
    assert proof2_entry["hashes"]["Parse.lean"] == candidate["source_versions"][0]["files"]["Parse.lean"]
    proof3_manifest = read_json(ROOT / "candidates/r26-e-658-short-same-proof3/manifest.json")
    assert proof3_manifest["hashes"]["parse.rs"] == candidate["rust_sha256"]
    result = {
        "status": "VERIFIED_E1_TWO_RUNNER_RAW_CONFIRMATION_AND_29966_REPLAY",
        "checked_utc": datetime.now(timezone.utc).isoformat(),
        "analysis_snapshot": analysis["snapshot"],
        "current_snapshot": replay.context,
        "official_capture": {
            "path": CAPTURE.relative_to(ROOT).as_posix(),
            "retrieval_start_utc": capture_receipt["retrieval_start_utc"],
            "retrieval_end_utc": capture_receipt["retrieval_end_utc"],
            "receipt_sha256": digest(CAPTURE / "receipt.json"),
            "pareto_rows": capture_receipt["pagination"]["pareto"]["rows"],
            "leaderboard_rows": capture_receipt["pagination"]["leaderboard"]["rows"],
        },
        "api_replay": {key: api_audit[key] for key in [
            "status", "input_rows", "admitted_bounded_rows", "reconstructed_frontier",
            "frontier_ids_match", "raw_and_derived_hashes_match",
            "max_independent_api_error_pp", "max_independent_official_scorer_error_pp",
            "max_api_payable_error_fraction", "max_weights_by_hotkey_error_fraction"]},
        "runner_count": 2, "block_count_per_runner": 2,
        "raw_process_count": len(raw_processes),
        "raw_hashes_match_analysis": all(row["matches_analysis"] for row in raw_hash_manifest.values()),
        "raw_hash_manifest": raw_hash_manifest,
        "raw_processes": [
            {key: value for key, value in row.items() if key != "input_hashes_by_file"}
            for row in raw_processes
        ],
        "corpus_input_sha256_by_file": raw_processes[0]["input_hashes_by_file"],
        "projection_formula": "projected X = official #658 X * raw method X / same-run-block selected public658 process X; projected Y = official #658 Y + method raw Y - selected calibration raw Y.",
        "projection_audit": {
            "projection_count": len(projections),
            "candidate_main_views": sum(row["entry_role"] == "candidate" for row in projections),
            "same_binary_copy_control_views": sum(row["entry_role"] == "control" for row in projections),
            "max_abs_projection_x_error": max(x_errors, default=0),
            "max_abs_projection_y_error_pp": max(y_errors, default=0),
        },
        "projections": projections,
        "share_summaries_by_runner_role_calibration": summaries,
        "same_binary_controls": {
            "candidate_copy_gap_range_pct": [min(candidate_copy_gaps), max(candidate_copy_gaps)],
            "public658_gap_range_pct": [min(public658_gaps), max(public658_gaps)],
            "pair_observations": same_binary_controls,
        },
        "proof_binding": {
            "measured_rust_sha256": candidate["rust_sha256"],
            "measured_lean_sha256": proof2_entry["hashes"]["Parse.lean"],
            "proof2_entry_status": proof2_entry["status"],
            "proof2_gate_receipt_status": proof2_receipt["status"],
            "proof2_gate_run_id": proof2_receipt["run_id"],
            "proof2_gate_receipt_sha256": digest(PROOF2_RECEIPT),
            "proof2_gate_log_path": PROOF2_LOG.relative_to(ROOT).as_posix(),
            "proof2_gate_log_sha256": digest(PROOF2_LOG),
            "no_goals_error_count": len(no_goals_lines),
            "no_goals_error_lines": no_goals_lines,
            "proof3_rust_sha256": proof3_manifest["hashes"]["parse.rs"],
            "proof3_lean_sha256": proof3_manifest["hashes"]["Parse.lean"],
            "proof3_entry_status_in_repo": proof3_entry["status"],
            "final_proof3_acceptance": "PENDING_PER_PARENT_TASK_INSTRUCTION; this receipt set is proof2-bound, not an exact proof3 pair.",
        },
        "limits": [
            "Stored 29957 shares are carried from the stale historical analysis; current shares are independently replayed on complete official snapshot 29966.",
            "Candidate and same-binary copy control are separate; the copy is not an independent candidate or confirmation sample.",
            "Primary/shadow are alternate calibrations of each raw runner/block, not independent measurements.",
            "Proof2's exact gate was rejected/incomplete; proof3 exact-pair acceptance remains pending. No final proof3 confirmation is claimed.",
            "Shares are conditional geometric pool weights, not admission or realized payout.",
        ],
    }
    write_json(OUTPUT_JSON, result)
    OUTPUT_MD.write_text(build_markdown(result), encoding="utf-8")
    main_primary_old = next(row for row in summaries if row["runner_id"] == "ALL" and row["sample_class"] == "candidate_main" and row["calibration"] == "primary")["stored_29957"]
    main_primary_new = next(row for row in summaries if row["runner_id"] == "ALL" and row["sample_class"] == "candidate_main" and row["calibration"] == "primary")["current_29966"]
    print(json.dumps({"status": result["status"], "snapshot_id": replay.context["snapshot_id"],
                      "raw_processes": len(raw_processes), "projections": len(projections),
                      "stored_primary_29957": main_primary_old,
                      "current_primary_29966": main_primary_new,
                      "max_projection_error_x": max(x_errors, default=0),
                      "max_projection_error_y_pp": max(y_errors, default=0),
                      "output": OUTPUT_JSON.relative_to(ROOT).as_posix()}, ensure_ascii=False))


if __name__ == "__main__":
    main()
