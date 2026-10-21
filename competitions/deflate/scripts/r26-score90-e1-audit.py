"""Independently audit R26 E1's seven raw benchmark streams and 29954 score geometry."""
from __future__ import annotations

import hashlib
import importlib
import importlib.util
import json
import math
import statistics
import sys
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

RUN_ID = "38268487485"
GATE = ROOT / f"evidence/round26/{RUN_ID}/screen90-e1/gate"
ANALYSIS_PATH = ROOT / "evidence/round26/extension90m/e1-first-analysis.json"
CAPTURE = ROOT / "evidence/round26/extension90m/official-e1"
RULES = ROOT / "evidence/round26/extension90m/rules-start"
OUTPUT_DIR = ROOT / "evidence/round26/extension90m/score-audit"
OUTPUT_JSON = OUTPUT_DIR / "e1-audit-29954.json"
OUTPUT_MD = OUTPUT_DIR / "e1-audit-29954.md"

EXPECTED_PROCESSES = [
    "r26-e-658-short-same", "r26-e-658-short-same-shadow",
    "public658", "public658-shadow", "public432", "r3-432-fast3", "probe3",
]


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_json(path: Path):
    return json.loads(path.read_bytes())


def write_json(path: Path, value) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def read_process(path: Path) -> dict:
    objects = [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]
    assert objects and objects[0].get("kind") == "meta"
    meta = objects[0]
    rows = [obj for obj in objects[1:] if obj.get("kind") == "file"]
    assert len(rows) == 28, (path.name, len(rows))
    variants = [name for name in meta["methods"] if name != "incumbent"]
    assert len(variants) == 1, (path.name, variants)
    name = variants[0]
    assert meta["warmup_rounds"] == 1 and meta["measured_rounds"] == 11
    time_ratios, size_values, per_file, input_hashes = [], [], [], {}
    for row in rows:
        assert row["corpus"] == "corpus-stage1"
        assert row["file"] not in input_hashes
        input_hashes[row["file"]] = row["sha256"]
        incumbent = row["methods"]["incumbent"]
        candidate = row["methods"][name]
        inc_times = [float(r["total_s"]) for r in incumbent["reps"] if r["phase"] == "measured"]
        cand_times = [float(r["total_s"]) for r in candidate["reps"] if r["phase"] == "measured"]
        assert len(inc_times) == len(cand_times) == 11
        inc_median = statistics.median(inc_times)
        cand_median = statistics.median(cand_times)
        ratio = cand_median / inc_median
        size = 100.0 * float(candidate["output_bytes"]) / float(row["raw_bytes"])
        time_ratios.append(ratio)
        size_values.append(size)
        per_file.append({"file": row["file"], "raw_sha256": row["sha256"],
                         "candidate_median_total_s": cand_median,
                         "incumbent_median_total_s": inc_median,
                         "time_ratio": ratio, "output_bytes": candidate["output_bytes"],
                         "raw_bytes": row["raw_bytes"], "compression_pct": size})
    return {
        "process_name": name,
        "source_sha256": meta["methods"][name]["source_sha256"],
        "library_sha256": meta["methods"][name]["lib_sha256"],
        "incumbent_source_sha256": meta["methods"]["incumbent"]["source_sha256"],
        "incumbent_library_sha256": meta["methods"]["incumbent"]["lib_sha256"],
        "runner": {"cpu_model": meta["cpu_model"], "rustc_version": meta["rustc_version"],
                   "engine_sha256": meta["benchmark_provenance"]["engine_sha256"],
                   "template_sha256": meta["benchmark_provenance"]["template_sha256"],
                   "host_sha256": meta["benchmark_provenance"]["host_sha256"]},
        "jsonl_path": path.relative_to(ROOT).as_posix(), "jsonl_sha256": digest(path),
        "file_count": len(rows), "warmup_rounds": 1, "measured_rounds": 11,
        "x_balanced_time_ratio_equal_file_mean": statistics.mean(time_ratios),
        "y_mean_file_compression_pct": statistics.mean(size_values),
        "per_file": per_file, "input_hashes_by_file": input_hashes,
    }


def score(replay, name: str, x: float, y: float) -> dict:
    return SCORE_AUDIT.score_one(replay, name, float(x), float(y))


def boundary_distances(replay, name: str, x: float, y: float) -> dict:
    """Find the first actual dominated coordinate on each worsening axis."""
    time_limits = [(point_name, time_x, size_y) for point_name, time_x, size_y in replay.base
                   if size_y <= y]
    size_limits = [(point_name, time_x, size_y) for point_name, time_x, size_y in replay.base
                   if time_x <= x]
    assert time_limits and size_limits
    boundary_x = min(row[1] for row in time_limits)
    x_ids = [row[0] for row in time_limits if row[1] == boundary_x]
    boundary_y = min(row[2] for row in size_limits)
    y_ids = [row[0] for row in size_limits if row[2] == boundary_y]
    assert boundary_x > x and boundary_y > y

    current = score(replay, f"{name}-current", x, y)
    at_x = score(replay, f"{name}-x-boundary", boundary_x, y)
    just_inside_x = score(replay, f"{name}-x-inside", math.nextafter(boundary_x, 0.0), y)
    at_y = score(replay, f"{name}-y-boundary", x, boundary_y)
    just_inside_y = score(replay, f"{name}-y-inside", x, math.nextafter(boundary_y, 0.0))
    assert current and not at_x and not at_y
    assert just_inside_x and just_inside_y
    return {
        "basis": "First actual captured frontier point that dominates when only this coordinate is worsened; no synthetic pressure scenario.",
        "time_axis": {
            "boundary_x": boundary_x, "dominating_frontier_ids": x_ids,
            "distance_x": boundary_x - x,
            "distance_relative_to_current_x_pct": 100 * (boundary_x - x) / x,
            "share_at_boundary_pct": float(at_x.get("share_pct", 0.0)),
            "share_one_float_step_inside_pct": float(just_inside_x.get("share_pct", 0.0)),
            "inside_neighbors": [just_inside_x.get("predecessor"), just_inside_x.get("successor")],
        },
        "size_axis": {
            "boundary_y_pct": boundary_y, "dominating_frontier_ids": y_ids,
            "distance_y_percentage_points": boundary_y - y,
            "distance_relative_to_current_y_pct": 100 * (boundary_y - y) / y,
            "share_at_boundary_pct": float(at_y.get("share_pct", 0.0)),
            "share_one_float_step_inside_pct": float(just_inside_y.get("share_pct", 0.0)),
            "inside_neighbors": [just_inside_y.get("predecessor"), just_inside_y.get("successor")],
        },
    }


def build_markdown(result: dict) -> str:
    snap = result["snapshot"]
    lines = [
        "# E1 首次实测信号独立审计", "",
        f"Official snapshot `{snap['snapshot_id']}`，计算时间 `{snap['computed_at']}`，freshness `{snap.get('freshness')}`。",
        f"采集时间 `{result['capture']['retrieval_start_utc']}`–`{result['capture']['retrieval_end_utc']}` UTC；" 
        f"API 前沿 `{result['api_replay']['reconstructed_frontier']}` 点，独立回放误差 `{result['api_replay']['max_independent_official_scorer_error_pp']:.3g}` pp。", "",
        "X 是 28 个文件的等权平均（每文件先取 11 次 measured total_s 中位数，再除以 incumbent 中位数）；Y 是 28 个文件压缩字节比例的等权平均。", "",
        "## 七条原始流程", "",
        "| 流程 | X | Y (%) | source SHA-256 |", "|---|---:|---:|---|"]
    for process in result["raw_processes"]:
        lines.append(f"| {process['process_name']} | {process['x_balanced_time_ratio_equal_file_mean']:.12f} | {process['y_mean_file_compression_pct']:.9f} | `{process['source_sha256']}` |")
    ctrl = result["same_binary_controls"]
    lines += ["", "## 同二进制对照", "",
              (f"E1 主版本 raw X 相对 #658 main 为 `{ctrl['candidate_vs_public658_main_relative_time_pct']:.6f}%`；" 
               f"E1 主版本与 shadow 的 raw X 差 `{ctrl['candidate_copy_relative_time_gap_pct']:.6f}%`；" 
               f"同一 #658 binary 的 primary/shadow 差 `{ctrl['public658_main_shadow_relative_time_gap_pct']:.6f}%`。"),
              (f"主版本与 shadow SHA 完全相同，来自同一个 runner block；copy的zero boundary余量仅 "
               f"主/影子投影 X 的 `{100*ctrl['copy_primary_zero_margin_relative_pct']:.6f}%` / "
               f"`{100*ctrl['copy_shadow_zero_margin_relative_pct']:.6f}%`，观测主副本差分别是余量的 "
               f"`{ctrl['candidate_copy_gap_multiple_of_primary_zero_margin']:.2f}x` / "
               f"`{ctrl['candidate_copy_gap_multiple_of_shadow_zero_margin']:.2f}x`。"),
              "这只是同一runner块的观察差；只计一个算法发现和一个同二进制过程对照。", "",
              "## 四个坐标和 29954 份额", "",
              "| 流程身份 | 校准锚点 | X | Y (%) | 记录份额 (%) | 重算份额 (%) |", "|---|---|---:|---:|---:|---:|"]
    for row in result["projections"]:
        lines.append(f"| {row['role']} | {row['calibration']} | {row['projected_x']:.12f} | {row['projected_y_pct']:.12f} | {row['analysis_stored_share_pct']:.9f} | {row['snapshot_29954_geometric_share_pct']:.9f} |")
    lines += ["", "## 到最近实际零份额边界的距离", "",
              "下表分别固定另一坐标，只沿变差方向移动到当前真实前沿首次支配该点的位置；这是 29954 几何边界，不是压力情景。X/Y 轴单位不同，分轴报告距离，不合成任意尺度。", "",
              "| 流程身份 / 校准 | X 边界 ID | ΔX | 相对 ΔX (%) | Y 边界 ID | ΔY (百分点) | 相对 ΔY (%) |",
              "|---|---|---:|---:|---|---:|---:|"]
    for row in result["projections"]:
        b = row["zero_share_boundary"]
        tx, ty = b["time_axis"], b["size_axis"]
        lines.append(f"| {row['role']} / {row['calibration']} | {','.join(tx['dominating_frontier_ids'])} | {tx['distance_x']:.12f} | {tx['distance_relative_to_current_x_pct']:.6f}% | {','.join(ty['dominating_frontier_ids'])} | {ty['distance_y_percentage_points']:.9f} | {ty['distance_relative_to_current_y_pct']:.6f}% |")
    lines += ["", "四个份额行来自一份候选源码和一个同二进制 shadow 控制的两个校准视图，不是四个独立样本。零份额边界上的份额已用 scorer 核实为 0；边界内侧浮点步仍在前沿。", ""]
    return "\n".join(lines)


def main() -> None:
    analysis = read_json(ANALYSIS_PATH)
    assert str(analysis["runs"][0]["run_id"]) == RUN_ID
    assert analysis["runs"][0]["ci_conclusion"] == "success"
    assert analysis["runs"][0]["role"] == "discovery"
    assert analysis["runs"][0]["paired_processes"] == 7

    process_files = sorted(GATE.glob("round1-*.jsonl"))
    processes = {}
    for path in process_files:
        process = read_process(path)
        processes[process["process_name"]] = process
    assert len(processes) == 7 and set(processes) == set(EXPECTED_PROCESSES)
    input_hashes = processes[EXPECTED_PROCESSES[0]]["input_hashes_by_file"]
    assert all(p["input_hashes_by_file"] == input_hashes for p in processes.values())
    incumbent_ids = {(p["incumbent_source_sha256"], p["incumbent_library_sha256"])
                     for p in processes.values()}
    assert len(incumbent_ids) == 1

    recorded_raw = {Path(key.replace("\\", "/")).name: value
                    for key, value in analysis["raw_input_audit"].items()}
    raw_hash_checks = {}
    for process in processes.values():
        entry = recorded_raw[Path(process["jsonl_path"]).name]
        assert entry["sha256"] == process["jsonl_sha256"]
        raw_hash_checks[Path(process["jsonl_path"]).name] = {
            "recorded_sha256": entry["sha256"], "observed_sha256": process["jsonl_sha256"], "match": True}

    main = processes["r26-e-658-short-same"]
    copy = processes["r26-e-658-short-same-shadow"]
    assert main["source_sha256"] == copy["source_sha256"]
    assert main["library_sha256"] == copy["library_sha256"]
    public_main, public_shadow = processes["public658"], processes["public658-shadow"]
    assert public_main["source_sha256"] == public_shadow["source_sha256"]
    assert public_main["library_sha256"] == public_shadow["library_sha256"]

    replay = M.Replay(CAPTURE, RULES)
    api_audit = M.audit(replay)
    assert str(replay.context["snapshot_id"]) == str(analysis["snapshot"]["snapshot_id"]) == "29954"
    formal_anchor = replay.byid["658"]["metrics"]
    anchor_x, anchor_y = float(formal_anchor["balanced_time_ratio"]), float(formal_anchor["mean_file_compression_pct"])
    observations = {}
    for candidate in analysis["candidates"]:
        for obs in candidate["observations"]:
            observations[(obs["entry_role"], obs["calibration"])] = obs

    projections, projection_x_errors, projection_y_errors, share_errors = [], [], [], []
    role_process = {"candidate": main, "same_binary_copy_control": copy}
    analysis_role = {"candidate": "candidate", "same_binary_copy_control": "control"}
    for role, process in role_process.items():
        for calibration, anchor_process_name in [("primary", "public658"), ("shadow", "public658-shadow")]:
            anchor_process = processes[anchor_process_name]
            x = anchor_x * process["x_balanced_time_ratio_equal_file_mean"] / anchor_process["x_balanced_time_ratio_equal_file_mean"]
            y = anchor_y + process["y_mean_file_compression_pct"] - anchor_process["y_mean_file_compression_pct"]
            obs = observations[(analysis_role[role], calibration)]
            projection_x_errors.append(abs(x - float(obs["projected_time"])))
            projection_y_errors.append(abs(y - float(obs["projected_size_pct"])))
            stored_share = float(obs["single_pool_share_pct"])
            actual_name = f"e1-{role}-{calibration}"
            latest_terms = score(replay, actual_name, x, y)
            current_share = float(latest_terms.get("share_pct", 0.0))
            share_errors.append(abs(current_share - stored_share))
            projections.append({
                "role": role, "entry_role": obs["entry_role"], "entry_name": obs["entry_name"],
                "calibration": calibration, "anchor_process": anchor_process_name,
                "source_sha256": process["source_sha256"], "library_sha256": process["library_sha256"],
                "raw_x": process["x_balanced_time_ratio_equal_file_mean"],
                "raw_y_pct": process["y_mean_file_compression_pct"],
                "projected_x": x, "projected_y_pct": y,
                "analysis_projected_x": float(obs["projected_time"]),
                "analysis_projected_y_pct": float(obs["projected_size_pct"]),
                "analysis_stored_share_pct": stored_share,
                "snapshot_29954_geometric_share_pct": current_share,
                "analysis_recomputed_share_abs_error_pp": abs(current_share - stored_share),
                "snapshot_29954_neighbors": [latest_terms.get("predecessor"), latest_terms.get("successor")],
                "zero_share_boundary": boundary_distances(replay, actual_name, x, y),
            })
    assert max(projection_x_errors, default=0) < 1e-10
    assert max(projection_y_errors, default=0) < 1e-10
    assert max(share_errors, default=0) < 1e-9

    time_copy_gap_pct = 100 * (copy["x_balanced_time_ratio_equal_file_mean"] / main["x_balanced_time_ratio_equal_file_mean"] - 1)
    public658_gap_pct = 100 * (public_shadow["x_balanced_time_ratio_equal_file_mean"] / public_main["x_balanced_time_ratio_equal_file_mean"] - 1)
    candidate_vs_parent_pct = 100 * (main["x_balanced_time_ratio_equal_file_mean"] / public_main["x_balanced_time_ratio_equal_file_mean"] - 1)
    analysis_control_gaps = {row["shadow"]: float(row["relative_time_gap_pct"])
                             for row in analysis["same_source_controls"]}
    assert abs(time_copy_gap_pct - analysis_control_gaps["r26-e-658-short-same-shadow"]) < 1e-10
    assert abs(public658_gap_pct - analysis_control_gaps["public658-shadow"]) < 1e-10
    copy_primary = next(p for p in projections if p["role"] == "same_binary_copy_control" and p["calibration"] == "primary")
    copy_shadow = next(p for p in projections if p["role"] == "same_binary_copy_control" and p["calibration"] == "shadow")
    copy_main = next(p for p in projections if p["role"] == "candidate" and p["calibration"] == "primary")
    copy_margins = {
        "primary": copy_primary["zero_share_boundary"]["time_axis"]["distance_x"],
        "shadow": copy_shadow["zero_share_boundary"]["time_axis"]["distance_x"],
    }

    capture_receipt = read_json(CAPTURE / "receipt.json")
    result = {
        "status": "VERIFIED_E1_SEVEN_RAW_STREAMS_SCORE_REPLAY_AND_ACTUAL_ZERO_BOUNDARIES",
        "checked_utc": datetime.now(timezone.utc).isoformat(),
        "ci_run": {"run_id": RUN_ID, "batch": "screen90-e1", "conclusion": "success",
                   "role": "discovery", "paired_processes": 7},
        "snapshot": replay.context,
        "capture": {"path": CAPTURE.relative_to(ROOT).as_posix(),
                    "retrieval_start_utc": capture_receipt["retrieval_start_utc"],
                    "retrieval_end_utc": capture_receipt["retrieval_end_utc"],
                    "receipt_sha256": digest(CAPTURE / "receipt.json"),
                    "pareto_rows": capture_receipt["pagination"]["pareto"]["rows"],
                    "leaderboard_rows": capture_receipt["pagination"]["leaderboard"]["rows"]},
        "api_replay": {key: api_audit[key] for key in [
            "status", "input_rows", "admitted_bounded_rows", "reconstructed_frontier",
            "frontier_ids_match", "raw_and_derived_hashes_match",
            "max_independent_api_error_pp", "max_independent_official_scorer_error_pp",
            "max_api_payable_error_fraction", "max_weights_by_hotkey_error_fraction",
            "sum_geometric_fraction", "sum_payable_fraction"]},
        "benchmark_formula": "X = equal-file mean(median of 11 measured candidate total_s / median of 11 measured incumbent total_s); Y = equal-file mean(100 * output_bytes / raw_bytes).",
        "raw_process_count": 7,
        "same_28_inputs_and_incumbent_sources": True,
        "raw_hashes_match_analysis": all(row["match"] for row in raw_hash_checks.values()),
        "raw_hash_checks": raw_hash_checks,
        "raw_processes": list(processes.values()),
        "projection_formula_audit": {"anchor_id": "658", "anchor_x": anchor_x, "anchor_y_pct": anchor_y,
                                      "max_abs_projected_x_error": max(projection_x_errors),
                                      "max_abs_projected_y_error_pp": max(projection_y_errors),
                                      "max_abs_29954_share_error_pp": max(share_errors)},
        "projections": projections,
        "same_binary_controls": {
            "candidate_source_sha256": main["source_sha256"],
            "candidate_executable_sha256": main["library_sha256"],
            "candidate_and_copy_byte_identical": True,
            "candidate_copy_relative_time_gap_pct": time_copy_gap_pct,
            "candidate_vs_public658_main_relative_time_pct": candidate_vs_parent_pct,
            "candidate_copy_vs_public658_main_relative_time_pct": 100 * (copy["x_balanced_time_ratio_equal_file_mean"] / public_main["x_balanced_time_ratio_equal_file_mean"] - 1),
            "public658_source_sha256": public_main["source_sha256"],
            "public658_executable_sha256": public_main["library_sha256"],
            "public658_main_shadow_relative_time_gap_pct": public658_gap_pct,
            "candidate_copy_gap_multiple_of_primary_zero_margin": time_copy_gap_pct / (100 * copy_margins["primary"] / copy_primary["projected_x"]),
            "candidate_copy_gap_multiple_of_shadow_zero_margin": time_copy_gap_pct / (100 * copy_margins["shadow"] / copy_shadow["projected_x"]),
            "copy_primary_zero_margin_relative_pct": 100 * copy_margins["primary"] / copy_primary["projected_x"],
            "copy_shadow_zero_margin_relative_pct": 100 * copy_margins["shadow"] / copy_shadow["projected_x"],
            "independent_candidate_algorithm_count": 1,
            "independent_runner_block_count": 1,
            "interpretation": "The shadow is the same binary and is a process/control observation, not another independent candidate sample. The two anchor rows are alternate coordinate calibrations of the same run.",
        },
        "nearest_zero_share_frontier_edges": {
            "method": "For each positive projected coordinate, hold the other axis fixed and find the first actual 29954 frontier point that dominates as that axis worsens; verify score=0 at equality and positive at the immediately interior floating-point value.",
            "actual_frontier_edges": {
                "nearest_time_dominator": {"id": projections[0]["zero_share_boundary"]["time_axis"]["dominating_frontier_ids"],
                                            "x": projections[0]["zero_share_boundary"]["time_axis"]["boundary_x"]},
                "nearest_size_dominator": {"id": projections[0]["zero_share_boundary"]["size_axis"]["dominating_frontier_ids"],
                                           "y_pct": projections[0]["zero_share_boundary"]["size_axis"]["boundary_y_pct"]},
            },
            "projection_distances": [{"role": p["role"], "calibration": p["calibration"],
                                      "time_axis": p["zero_share_boundary"]["time_axis"],
                                      "size_axis": p["zero_share_boundary"]["size_axis"]}
                                     for p in projections],
            "no_combined_distance": "Time and compression axes have different units; exact per-axis distances are reported without an arbitrary weighting or stress scenario.",
        },
        "interpretation_limits": [
            "All four scored rows are projections from one candidate discovery run; they are two anchor calibrations for the candidate and the same-binary copy control, not four independent samples.",
            "The nearest zero-share edges are deterministic boundaries on captured snapshot 29954, not independent confirmation, admission, private performance, or expected reward.",
            "API freshness remains unknown; the public scorer replay does not prove exact deployed configuration or wallet receipt.",
        ],
    }
    write_json(OUTPUT_JSON, result)
    OUTPUT_MD.write_text(build_markdown(result), encoding="utf-8")
    print(json.dumps({"status": result["status"], "snapshot_id": replay.context["snapshot_id"],
                      "raw_streams": len(processes), "projection_count": len(projections),
                      "shares": [p["snapshot_29954_geometric_share_pct"] for p in projections],
                      "raw_copy_gap_pct": time_copy_gap_pct,
                      "public658_gap_pct": public658_gap_pct,
                      "time_boundary_ids": result["nearest_zero_share_frontier_edges"]["actual_frontier_edges"]["nearest_time_dominator"]["id"],
                      "size_boundary_ids": result["nearest_zero_share_frontier_edges"]["actual_frontier_edges"]["nearest_size_dominator"]["id"],
                      "output": OUTPUT_JSON.relative_to(ROOT).as_posix()}, ensure_ascii=False))


if __name__ == "__main__":
    main()
