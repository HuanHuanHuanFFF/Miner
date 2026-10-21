"""Audit two-runner C23 confirmations from 36 raw streams and replay 29954 shares."""
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

ANALYSIS_PATH = ROOT / "evidence/round26/extension90m/c23-confirm-first-analysis.json"
LATEST_CHECK_DIR = ROOT / "evidence/round26/extension90m/latest-c23-confirm-check"
CAPTURE = ROOT / "evidence/round26/extension90m/official-e1"
RULES = ROOT / "evidence/round26/extension90m/rules-start"
RUN_GATES = {
    "38269106179": ROOT / "evidence/round26/38269106179/confirm90-c23-a/gate",
    "38269130947": ROOT / "evidence/round26/38269130947/confirm90-c23-b/gate",
}
OUTPUT_DIR = ROOT / "evidence/round26/extension90m/score-audit"
OUTPUT_JSON = OUTPUT_DIR / "c23-confirm-audit-29954.json"
OUTPUT_MD = OUTPUT_DIR / "c23-confirm-audit-29954.md"
EXPECTED_METHODS = {
    "probe3", "r3-432-fast3", "public432", "public658", "public658-shadow",
    "r26-c-658-fold-tail-proof1", "r26-c-658-fold-tail-proof1-shadow",
    "r26-c-658-deferred-extension-proof1", "r26-c-658-deferred-extension-proof1-shadow",
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
    assert len(methods) == 1, (path, methods)
    method = methods[0]
    assert meta["warmup_rounds"] == 1 and meta["measured_rounds"] == 11
    input_hashes, per_file_x, per_file_y = {}, [], []
    for row in rows:
        assert row["corpus"] == "corpus-stage1"
        assert row["file"] not in input_hashes
        input_hashes[row["file"]] = row["sha256"]
        candidate = row["methods"][method]
        incumbent = row["methods"]["incumbent"]
        candidate_total = [float(rep["total_s"]) for rep in candidate["reps"] if rep["phase"] == "measured"]
        incumbent_total = [float(rep["total_s"]) for rep in incumbent["reps"] if rep["phase"] == "measured"]
        assert len(candidate_total) == len(incumbent_total) == 11
        x = statistics.median(candidate_total) / statistics.median(incumbent_total)
        y = 100 * float(candidate["output_bytes"]) / float(row["raw_bytes"])
        per_file_x.append(x)
        per_file_y.append(y)
    return {
        "run_id": run_id, "block": block, "method": method,
        "process_role": "same_binary_copy_control" if method.endswith("-shadow") else "measurement_process",
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
        "x_balanced_time_ratio_equal_file_mean": statistics.mean(per_file_x),
        "y_mean_file_compression_pct": statistics.mean(per_file_y),
        "input_hashes_by_file": input_hashes,
    }


def geometric_score(replay, name: str, x: float, y: float) -> dict:
    return SCORE_AUDIT.score_one(replay, name, float(x), float(y))


def summarize(values: list[dict]) -> dict:
    shares = [float(row["share_pct"]) for row in values]
    positives = [x for x in shares if x > 0]
    return {
        "n_projection_rows": len(shares), "zero_count": sum(x == 0 for x in shares),
        "zero_fraction_of_views": sum(x == 0 for x in shares) / len(shares) if shares else None,
        "share_min_including_zero_pct": min(shares) if shares else None,
        "share_max_pct": max(shares) if shares else None,
        "positive_min_pct": min(positives) if positives else None,
        "positive_max_pct": max(positives) if positives else None,
        "positive_median_pct": statistics.median(positives) if positives else None,
    }


def verify_zero_counts(projections: list[dict]) -> dict:
    # Report candidate and same-binary copy distributions separately.
    groups: dict[tuple[str, str, str], list[dict]] = defaultdict(list)
    for row in projections:
        role = "candidate_main" if row["entry_role"] == "candidate" else "same_binary_copy_control"
        groups[(row["runner_id"], row["candidate"], role)].append(row)
        groups[("ALL", row["candidate"], role)].append(row)
    return [{"runner_id": run, "candidate": candidate, "sample_class": role, **summarize(rows)}
            for (run, candidate, role), rows in sorted(groups.items())]


def build_markdown(result: dict) -> str:
    lines = [
        "# C23 两 runner 原始确认审计", "",
        (f"Snapshot `{result['snapshot']['snapshot_id']}`，identity-check latest=`{result['latest_identity_check']['latest_snapshot_matches']}`，" 
         f"freshness `{result['snapshot'].get('freshness')}`。共 `{result['raw_stream_count']}` 条原始流程（每 runner 18），" 
         f"独立 API 前沿 `{result['api_replay']['reconstructed_frontier']}` 点；36 条 JSONL SHA 均与分析登记一致。"),
        ("Runner 硬件：" + ", ".join(f"`{runner['run_id']}`={runner['cpu_model']}"
                                      for runner in result["ci_runners"]) + "."),
        "原始 36 流的 X/Y、路径和 SHA-256 在机器 JSON `raw_processes` 列表中；这里不复制逐流大表。", "",
        "## 16 个候选主投影", "",
        "每个候选、runner、block、primary/shadow 各一行；同源码副本全部另列为 control。", "",
        "| Runner | Candidate | Block | Anchor | raw X | Projected X | Y (%) | Share (%) |",
        "|---|---|---:|---|---:|---:|---:|---:|",
    ]
    mains = [row for row in result["projections"] if row["entry_role"] == "candidate"]
    for row in mains:
        lines.append(f"| {row['runner_id']} | {row['candidate_short']} | {row['block']} | {row['calibration']} | {row['raw_x']:.9f} | {row['projected_x']:.12f} | {row['projected_y_pct']:.9f} | {row['recomputed_snapshot_29954_share_pct']:.9f} |")
    boundary = result["zero_share_boundary_at_projected_y"]
    lines += ["", "## 主候选与同二进制副本统计", "",
              (f"本批投影 Y 均为 `{boundary['projected_y_pct']:.12f}%`；真实时间零份额边界为 "
               f"#{','.join(boundary['frontier_ids'])} 的 X=`{boundary['boundary_x']:.12f}`。"),
              "关键分歧：C2 runner B block 2 两个主校准都越过该界；C3 runner A block 2 两个主校准都越界；C3 runner B block 2 主锚越界，但 shadow 锚仍在界内，份额 `0.783900%`。", "",
              "零次数与份额范围分别统计；shadow/copy 是同二进制控制，绝不并入独立候选样本数。", "",
              "| Runner | Candidate | 类别 | 份额行数 | 零次数 | 正份额范围 (%) |", "|---|---|---|---:|---:|---:|"]
    for stat in result["share_summaries_by_runner_candidate_and_sample_class"]:
        positive = stat["positive_share_range_pct"]
        positive_range = "—" if positive is None else f"{positive[0]:.6f}–{positive[1]:.6f}"
        lines.append(f"| {stat['runner_id']} | {stat['candidate_short']} | {stat['sample_class']} | {stat['n_views']} | {stat['zero_count']} | {positive_range} |")

    lines += ["", "## 同源码过程控制与证明状态", "",
              f"两个 runner 的 raw JSONL 共 `{len(result['same_binary_control_gaps'])}` 个已核验同二进制配对差；控制差全表在机器 JSON 中。",
              f"C2 proof1 exact gate 记录 `{result['proof_status']['c2_candidate']['exact_gate_verified_in_analysis']}`。C3 proof1 exact gate 记录 `{result['proof_status']['c3_candidate']['exact_gate_verified_in_analysis']}`；这批坐标只覆盖 proof1 源码，不能视作 proof2 后的最终确认（proof2 另一个 pair 仍在运行）。", "",
              "所有份额是 29954 当前真实几何的单点重放。主候选每个算法仅有两个 runner、两个 block 的 discovery/confirmation 主测量；四种投影不作为四份相互独立证据。", ""]
    return "\n".join(lines)


def main() -> None:
    analysis = read_json(ANALYSIS_PATH)
    assert str(analysis["snapshot"]["snapshot_id"]) == "29954"
    assert len(analysis["runs"]) == 2 and sum(int(x["paired_processes"]) for x in analysis["runs"]) == 36
    run_info = {str(run["run_id"]): run for run in analysis["runs"]}

    raw_processes = []
    for run_id, gate in RUN_GATES.items():
        assert str(run_info[run_id]["run_id"]) == run_id
        per_run = []
        for block in (1, 2):
            paths = sorted(gate.glob(f"round{block}-*.jsonl"))
            assert len(paths) == 9, (run_id, block, len(paths))
            block_rows = [parse_stream(path, run_id, block) for path in paths]
            assert {row["method"] for row in block_rows} == EXPECTED_METHODS
            first_hashes = block_rows[0]["input_hashes_by_file"]
            assert all(row["input_hashes_by_file"] == first_hashes for row in block_rows)
            assert len({(row["incumbent_source_sha256"], row["incumbent_library_sha256"])
                        for row in block_rows}) == 1
            per_run.extend(block_rows)
        assert len(per_run) == 18
        raw_processes.extend(per_run)
    assert len(raw_processes) == 36

    audit_inputs = {key.replace("\\", "/"): row
                    for key, row in analysis["raw_input_audit"].items()}
    raw_hash_checks = {}
    for process in raw_processes:
        expected = audit_inputs.get(process["path"])
        assert expected and expected["sha256"] == process["raw_jsonl_sha256"]
        assert expected["source_hashes"].get("parse.rs") == process["source_sha256"]
        raw_hash_checks[process["path"]] = {
            "sha256": process["raw_jsonl_sha256"], "matches_analysis": True,
        }
    raw_by_key = {(row["run_id"], row["block"], row["method"]): row for row in raw_processes}

    capture = M.Replay(CAPTURE, RULES)
    api_audit = M.audit(capture)
    assert str(capture.context["snapshot_id"]) == "29954"
    latest_identity = read_json(LATEST_CHECK_DIR / "receipt.json")
    assert latest_identity["status"] == "VERIFIED_OFFICIAL_LATEST_SNAPSHOT_IDENTITY_READ"
    assert latest_identity["latest_snapshot_matches"] is True
    assert latest_identity["current_snapshot_id"] == capture.context["snapshot_id"]
    anchor = capture.byid["658"]["metrics"]
    anchor_x = float(anchor["balanced_time_ratio"])
    anchor_y = float(anchor["mean_file_compression_pct"])
    zero_boundary_candidates = [row for row in capture.base if row[2] <= anchor_y]
    zero_boundary_x = min(row[1] for row in zero_boundary_candidates)
    zero_boundary_x_ids = [row[0] for row in zero_boundary_candidates if row[1] == zero_boundary_x]
    analysis_candidates = {candidate["candidate"]: candidate for candidate in analysis["candidates"]}

    projections, project_x_errors, project_y_errors, share_errors = [], [], [], []
    for candidate_name, candidate in analysis_candidates.items():
        candidate_short = "C2 fold-tail" if "fold-tail" in candidate_name else "C3 deferred-extension"
        for obs in candidate["observations"]:
            run_id, block = str(obs["run_id"]), int(obs["block"])
            method = obs["entry_name"]
            process = raw_by_key[(run_id, block, method)]
            anchor_proc = raw_by_key[(run_id, block, obs["anchor_name"])]
            projected_x = anchor_x * process["x_balanced_time_ratio_equal_file_mean"] / anchor_proc["x_balanced_time_ratio_equal_file_mean"]
            projected_y = anchor_y + process["y_mean_file_compression_pct"] - anchor_proc["y_mean_file_compression_pct"]
            project_x_errors.append(abs(projected_x - float(obs["projected_time"])))
            project_y_errors.append(abs(projected_y - float(obs["projected_size_pct"])))
            role_class = "candidate_main" if obs["entry_role"] == "candidate" else "same_binary_copy_control"
            score_name = f"{candidate_name}-{run_id}-{block}-{obs['entry_role']}-{obs['calibration']}"
            terms = SCORE_AUDIT.score_one(capture, score_name, projected_x, projected_y)
            share = float(terms.get("share_pct", 0.0))
            stored = float(obs["single_pool_share_pct"])
            zero_margin_x = zero_boundary_x - projected_x
            assert abs(projected_y - anchor_y) < 1e-10
            assert (share == 0.0) == (zero_margin_x <= 0.0)
            share_errors.append(abs(share - stored))
            projections.append({
                "candidate": candidate_name, "candidate_short": candidate_short,
                "runner_id": run_id, "cpu_model": run_info[run_id]["environment"]["cpu_model"],
                "block": block, "role": obs["role"], "entry_role": obs["entry_role"],
                "sample_class": role_class, "entry_name": method,
                "calibration": obs["calibration"], "anchor_process": obs["anchor_name"],
                "rust_source_sha256": process["source_sha256"],
                "executable_sha256": process["library_sha256"],
                "raw_x": process["x_balanced_time_ratio_equal_file_mean"],
                "raw_y_pct": process["y_mean_file_compression_pct"],
                "anchor_raw_x": anchor_proc["x_balanced_time_ratio_equal_file_mean"],
                "anchor_raw_y_pct": anchor_proc["y_mean_file_compression_pct"],
                "projected_x": projected_x, "projected_y_pct": projected_y,
                "analysis_projected_x": float(obs["projected_time"]),
                "analysis_projected_y_pct": float(obs["projected_size_pct"]),
                "analysis_stored_share_pct": stored,
                "recomputed_snapshot_29954_share_pct": share,
                "share_abs_error_pp": abs(share - stored),
                "recomputed_neighbors": [terms.get("predecessor"), terms.get("successor")],
                "on_geometric_frontier": bool(terms),
                "zero_share_boundary_at_fixed_projected_y": {
                    "frontier_ids": zero_boundary_x_ids, "boundary_x": zero_boundary_x,
                    "delta_x_boundary_minus_projected": zero_margin_x,
                    "relative_margin_pct": 100 * zero_margin_x / projected_x,
                    "relation": "before boundary" if zero_margin_x > 0 else "at or beyond boundary",
                },
            })
    assert len(projections) == 32
    main_rows = [row for row in projections if row["entry_role"] == "candidate"]
    copy_rows = [row for row in projections if row["entry_role"] == "control"]
    assert len(main_rows) == 16 and len(copy_rows) == 16
    assert max(project_x_errors, default=0) < 1e-10
    assert max(project_y_errors, default=0) < 1e-10
    assert max(share_errors, default=0) < 1e-9

    # Verify candidate/shadow source and executable identity for every runner/block.
    copy_pair_checks = []
    same_binary_control_gaps = []
    expected_control_records = {(str(x["run_id"]), int(x["block"]), x["shadow"]): x
                                for x in analysis["same_source_controls"]}
    for run_id in RUN_GATES:
        for block in (1, 2):
            for candidate_name in analysis_candidates:
                shadow_name = candidate_name + "-shadow"
                main = raw_by_key[(run_id, block, candidate_name)]
                shadow = raw_by_key[(run_id, block, shadow_name)]
                assert main["source_sha256"] == shadow["source_sha256"]
                assert main["library_sha256"] == shadow["library_sha256"]
                gap = 100 * (shadow["x_balanced_time_ratio_equal_file_mean"]
                             / main["x_balanced_time_ratio_equal_file_mean"] - 1)
                recorded = expected_control_records[(run_id, block, shadow_name)]
                assert abs(gap - float(recorded["relative_time_gap_pct"])) < 1e-10
                control_row = {"run_id": run_id, "block": block, "candidate": candidate_name,
                               "main_process": candidate_name, "copy_control_process": shadow_name,
                               "same_source_sha256": main["source_sha256"],
                               "same_executable_sha256": main["library_sha256"],
                               "main_raw_x": main["x_balanced_time_ratio_equal_file_mean"],
                               "copy_raw_x": shadow["x_balanced_time_ratio_equal_file_mean"],
                               "relative_copy_minus_main_time_pct": gap,
                               "analysis_gap_pct": float(recorded["relative_time_gap_pct"]),
                               "independent_candidate_sample_count": 1}
                copy_pair_checks.append(control_row)
                same_binary_control_gaps.append(control_row)

            # Also preserve each same-binary #658 main/shadow pairing.
            parent = raw_by_key[(run_id, block, "public658")]
            parent_shadow = raw_by_key[(run_id, block, "public658-shadow")]
            gap = 100 * (parent_shadow["x_balanced_time_ratio_equal_file_mean"]
                         / parent["x_balanced_time_ratio_equal_file_mean"] - 1)
            recorded = expected_control_records[(run_id, block, "public658-shadow")]
            assert abs(gap - float(recorded["relative_time_gap_pct"])) < 1e-10
            same_binary_control_gaps.append({"run_id": run_id, "block": block,
                                             "candidate": "public658 anchor control",
                                             "main_process": "public658", "copy_control_process": "public658-shadow",
                                             "same_executable_sha256": parent["library_sha256"],
                                             "relative_copy_minus_main_time_pct": gap,
                                             "analysis_gap_pct": float(recorded["relative_time_gap_pct"]),
                                             "independent_candidate_sample_count": 0})

    # Copy controls are separated before zero statistics are computed.
    summary_groups: dict[tuple[str, str, str], list[dict]] = defaultdict(list)
    for row in projections:
        summary_groups[(row["runner_id"], row["candidate_short"], row["sample_class"])].append(
            {"share_pct": row["recomputed_snapshot_29954_share_pct"]})
        summary_groups[("ALL", row["candidate_short"], row["sample_class"])].append(
            {"share_pct": row["recomputed_snapshot_29954_share_pct"]})
    share_summaries = []
    for (run_id, candidate_short, sample_class), values in sorted(summary_groups.items()):
        shares = [float(row["share_pct"]) for row in values]
        positive = [x for x in shares if x > 0]
        share_summaries.append({
            "runner_id": run_id, "candidate_short": candidate_short,
            "sample_class": sample_class, "n_views": len(shares),
            "zero_count": sum(x == 0 for x in shares),
            "share_range_including_zero_pct": [min(shares), max(shares)],
            "positive_share_range_pct": [min(positive), max(positive)] if positive else None,
            "positive_median_pct": statistics.median(positive) if positive else None,
        })

    proof_status = {}
    for candidate_name, candidate in analysis_candidates.items():
        exact_values = {bool(version.get("exact_gate_verified")) for version in candidate.get("source_versions", [])}
        assert len(exact_values) == 1
        proof_status[candidate_name] = {"exact_gate_verified_in_analysis": exact_values.pop(),
                                        "source_versions": candidate.get("source_versions", [])}
    c2_key = next(k for k in proof_status if "fold-tail" in k)
    c3_key = next(k for k in proof_status if "deferred-extension" in k)
    assert proof_status[c2_key]["exact_gate_verified_in_analysis"] is True
    assert proof_status[c3_key]["exact_gate_verified_in_analysis"] is False
    compact_raw_processes = []
    for process in raw_processes:
        compact = dict(process)
        compact.pop("input_hashes_by_file", None)
        compact_raw_processes.append(compact)

    identity_receipt = read_json(LATEST_CHECK_DIR / "receipt.json")
    capture_receipt = read_json(CAPTURE / "receipt.json")
    result = {
        "status": "VERIFIED_36_RAW_STREAMS_16_MAIN_PROJECTIONS_AND_COPY_SEPARATE_ZERO_STATS",
        "checked_utc": datetime.now(timezone.utc).isoformat(),
        "snapshot": capture.context,
        "latest_identity_check": {
            "status": identity_receipt["status"],
            "current_snapshot_id": identity_receipt["current_snapshot_id"],
            "expected_snapshot_id": identity_receipt["expected_snapshot_id"],
            "latest_snapshot_matches": identity_receipt["latest_snapshot_matches"],
            "policy_matches": identity_receipt["policy_matches"],
            "request_start_utc": identity_receipt["request_start_utc"],
            "request_end_utc": identity_receipt["request_end_utc"],
            "receipt_sha256": digest(LATEST_CHECK_DIR / "receipt.json"),
        },
        "official_capture": {
            "path": CAPTURE.relative_to(ROOT).as_posix(),
            "retrieval_start_utc": capture_receipt["retrieval_start_utc"],
            "retrieval_end_utc": capture_receipt["retrieval_end_utc"],
            "receipt_sha256": digest(CAPTURE / "receipt.json"),
        },
        "api_replay": {key: api_audit[key] for key in [
            "status", "input_rows", "admitted_bounded_rows", "reconstructed_frontier",
            "frontier_ids_match", "raw_and_derived_hashes_match",
            "max_independent_api_error_pp", "max_independent_official_scorer_error_pp",
            "max_api_payable_error_fraction", "max_weights_by_hotkey_error_fraction",
            "sum_geometric_fraction", "sum_payable_fraction"]},
        "ci_runners": [
            {"run_id": run_id, "batch": info["batch"], "role": info["role"],
             "conclusion": info["ci_conclusion"], "paired_process_count": info["paired_processes"],
             "cpu_model": info["environment"]["cpu_model"],
             "git_sha": info["git_sha"]}
            for run_id, info in run_info.items()
        ],
        "raw_stream_count": len(raw_processes),
        "raw_hashes_match_analysis": all(row["matches_analysis"] for row in raw_hash_checks.values()),
        "raw_hash_manifest": raw_hash_checks,
        "corpus_input_sha256_by_file": raw_processes[0]["input_hashes_by_file"],
        "raw_processes": compact_raw_processes,
        "projection_formula": "projected X = official #658 X * raw method X / same-run-block calibration process X; projected Y = official #658 Y + raw method Y - calibration process Y.",
        "projection_audit": {"main_candidate_projection_count": len(main_rows),
                              "same_binary_copy_control_projection_count": len(copy_rows),
                              "total_projection_views": len(projections),
                              "max_abs_projection_x_error": max(project_x_errors),
                              "max_abs_projection_y_error_pp": max(project_y_errors),
                              "max_abs_share_replay_error_pp": max(share_errors)},
        "projections": projections,
        "candidate_main_projections": main_rows,
        "same_binary_copy_control_projections": copy_rows,
        "share_summaries_by_runner_candidate_and_sample_class": share_summaries,
        "all_main_summary": [row for row in share_summaries if row["runner_id"] == "ALL" and row["sample_class"] == "candidate_main"],
        "all_copy_summary": [row for row in share_summaries if row["runner_id"] == "ALL" and row["sample_class"] == "same_binary_copy_control"],
        "same_binary_control_gaps": same_binary_control_gaps,
        "zero_share_boundary_at_projected_y": {"projected_y_pct": anchor_y,
                                                 "frontier_ids": zero_boundary_x_ids,
                                                 "boundary_x": zero_boundary_x,
                                                 "note": "Exact current 29954 frontier boundary for these equal-size projections; no synthetic coordinates."},
        "proof_status": {
            "c2_candidate": proof_status[c2_key],
            "c3_candidate": proof_status[c3_key],
            "c3_proof2_boundary": "This batch scores the proof1 Rust/Lean identity only; proof2 remains a separate running pair per parent task instruction, so this is not final post-proof2 confirmation.",
        },
        "sample_interpretation": {
            "candidate_algorithm_count": 2,
            "runner_count": 2,
            "block_count_per_runner": 2,
            "main_projection_views": 16,
            "main_algorithm_sample_count_per_candidate": 4,
            "copy_control_views": 16,
            "copies_are_independent_candidates": False,
            "projection_views_are_independent_samples": False,
            "note": "Each runner/block main candidate is one measurement; primary/shadow are alternate anchor calibrations. Same-source shadow rows are incidental controls and are summarized separately.",
        },
        "limits": [
            "The current latest identity receipt confirms snapshot 29954, but its freshness remains unknown.",
            "C2 rows refer to the exact proof1 sources whose full gate is accepted in the merged analysis; C3 rows refer to proof1 with exact_gate_verified=false.",
            "C3 values must not be promoted as final confirmation after proof2 until that distinct pair returns.",
            "No CI was run, no repository changes were made outside this audit output, and no copy control was counted as an independent candidate.",
        ],
    }
    write_json(OUTPUT_JSON, result)
    OUTPUT_MD.write_text(build_markdown(result), encoding="utf-8")
    print(json.dumps({"status": result["status"], "snapshot_id": result["snapshot"]["snapshot_id"],
                      "raw_process_count": len(raw_processes), "main_rows": len(main_rows), "copy_rows": len(copy_rows),
                      "max_projection_error_x": max(project_x_errors),
                      "max_projection_error_y_pp": max(project_y_errors),
                      "max_share_replay_error_pp": max(share_errors),
                      "share_summaries": share_summaries,
                      "proof_status": {key: value["exact_gate_verified_in_analysis"] for key, value in proof_status.items()},
                      "output": OUTPUT_JSON.relative_to(ROOT).as_posix()}, ensure_ascii=False))


if __name__ == "__main__":
    main()
