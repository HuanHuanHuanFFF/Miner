"""Independently audit nine R26 C2/C3 benchmark streams and score projections.

The script recomputes per-file median-total-time ratios and equal-file means
from preserved JSONL, validates analysis projections, and replays them against
the captured 29953 and 29954 official frontiers. It is read-only outside its
score-audit JSON output.
"""
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
AUDIT_SPEC = importlib.util.spec_from_file_location(
    "r26_extension_score_audit", SCRIPTS / "r26-extension-score-audit.py"
)
assert AUDIT_SPEC and AUDIT_SPEC.loader
AUDIT = importlib.util.module_from_spec(AUDIT_SPEC)
AUDIT_SPEC.loader.exec_module(AUDIT)

RUN_ID = "38266836712"
GATE = ROOT / f"evidence/round26/{RUN_ID}/screen90-c23/gate"
ANALYSIS_PATH = ROOT / "evidence/round26/extension90m/c23-start-analysis.json"
OLD_CAPTURE = ROOT / "evidence/round26/extension90m/official-start"
NEW_CAPTURE = ROOT / "evidence/round26/extension90m/official-c23"
RULES = ROOT / "evidence/round26/extension90m/rules-start"
C4_SOURCE_CAPTURE = ROOT / "evidence/round26/extension1h/official-close"
C4_SOURCE_RULES = ROOT / "evidence/round26/extension1h/rules-close"
OUTPUT = ROOT / "evidence/round26/extension90m/score-audit/c23-raw-audit-29954.json"

EXPECTED_PROCESSES = [
    "r26-c-658-fold-tail",
    "r26-c-658-fold-tail-shadow",
    "r26-c-658-deferred-extension",
    "r26-c-658-deferred-extension-shadow",
    "public658",
    "public658-shadow",
    "public432",
    "r3-432-fast3",
    "probe3",
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
    names = list(meta["methods"])
    variants = [name for name in names if name != "incumbent"]
    assert len(variants) == 1, (path.name, names)
    variant = variants[0]
    assert meta["warmup_rounds"] == 1 and meta["measured_rounds"] == 11
    time_ratios, size_pct, file_rows, input_hashes = [], [], [], {}
    for row in rows:
        assert row["corpus"] == "corpus-stage1"
        file_name = row["file"]
        assert file_name not in input_hashes
        input_hashes[file_name] = row["sha256"]
        incumbent = row["methods"]["incumbent"]
        candidate = row["methods"][variant]
        inc_measured = [float(rep["total_s"]) for rep in incumbent["reps"] if rep["phase"] == "measured"]
        cand_measured = [float(rep["total_s"]) for rep in candidate["reps"] if rep["phase"] == "measured"]
        assert len(inc_measured) == len(cand_measured) == 11
        inc_median, cand_median = statistics.median(inc_measured), statistics.median(cand_measured)
        ratio = cand_median / inc_median
        size = 100.0 * float(candidate["output_bytes"]) / float(row["raw_bytes"])
        time_ratios.append(ratio)
        size_pct.append(size)
        file_rows.append({"file": file_name, "raw_sha256": row["sha256"],
                          "candidate_median_total_s": cand_median,
                          "incumbent_median_total_s": inc_median,
                          "time_ratio": ratio, "output_bytes": candidate["output_bytes"],
                          "raw_bytes": row["raw_bytes"], "compression_pct": size})
    assert set(input_hashes) == {row["file"] for row in file_rows}
    return {
        "process_name": variant, "source_sha256": meta["methods"][variant]["source_sha256"],
        "library_sha256": meta["methods"][variant]["lib_sha256"],
        "incumbent_source_sha256": meta["methods"]["incumbent"]["source_sha256"],
        "incumbent_library_sha256": meta["methods"]["incumbent"]["lib_sha256"],
        "runner": {"cpu_model": meta["cpu_model"], "rustc_version": meta["rustc_version"],
                   "engine_sha256": meta["benchmark_provenance"]["engine_sha256"],
                   "template_sha256": meta["benchmark_provenance"]["template_sha256"],
                   "host_sha256": meta["benchmark_provenance"]["host_sha256"]},
        "jsonl_path": path.relative_to(ROOT).as_posix(), "jsonl_sha256": digest(path),
        "file_count": len(rows), "warmup_rounds": meta["warmup_rounds"],
        "measured_rounds": meta["measured_rounds"],
        "x_balanced_time_ratio_equal_file_mean": statistics.mean(time_ratios),
        "y_mean_file_compression_pct": statistics.mean(size_pct),
        "per_file": file_rows, "input_hashes_by_file": input_hashes,
    }


def main() -> None:
    analysis = read_json(ANALYSIS_PATH)
    assert str(analysis["runs"][0]["run_id"]) == RUN_ID
    assert analysis["runs"][0]["ci_conclusion"] == "success"
    assert analysis["runs"][0]["paired_processes"] == 9
    files = sorted(GATE.glob("round1-*.jsonl"))
    processes = {}
    for path in files:
        process = read_process(path)
        processes[process["process_name"]] = process
    assert len(files) == len(processes) == 9
    assert set(processes) == set(EXPECTED_PROCESSES), sorted(processes)

    # Every process is paired on the same 28 public inputs and uses the exact
    # same incumbent sources; raw evidence hashes are checked against analysis.
    first_hashes = processes[EXPECTED_PROCESSES[0]]["input_hashes_by_file"]
    incumbent_sources = {(p["incumbent_source_sha256"], p["incumbent_library_sha256"])
                         for p in processes.values()}
    assert len(incumbent_sources) == 1
    for process in processes.values():
        assert process["input_hashes_by_file"] == first_hashes
    analyzed_raw = {Path(key.replace("\\", "/")).name: value
                    for key, value in analysis["raw_input_audit"].items()}
    raw_hash_checks = {}
    for process in processes.values():
        expected = analyzed_raw.get(Path(process["jsonl_path"]).name)
        assert expected and expected["sha256"] == process["jsonl_sha256"]
        raw_hash_checks[Path(process["jsonl_path"]).name] = {
            "analysis_sha256": expected["sha256"], "observed_sha256": process["jsonl_sha256"],
            "match": True,
        }

    # Confirm each candidate and its shadow are byte-identical executables,
    # then calculate their copy-to-main control delta from the raw X values.
    copy_controls = {}
    for main_name in ["r26-c-658-fold-tail", "r26-c-658-deferred-extension"]:
        shadow_name = main_name + "-shadow"
        main, shadow = processes[main_name], processes[shadow_name]
        assert main["source_sha256"] == shadow["source_sha256"]
        assert main["library_sha256"] == shadow["library_sha256"]
        copy_controls[main_name] = {
            "main_process": main_name, "copy_control_process": shadow_name,
            "same_rust_source_sha256": main["source_sha256"],
            "same_executable_sha256": main["library_sha256"],
            "relative_copy_time_gap_pct": 100 * (
                shadow["x_balanced_time_ratio_equal_file_mean"]
                / main["x_balanced_time_ratio_equal_file_mean"] - 1
            ),
            "independent_sample_count": 1,
            "interpretation": "Same-binary copy/control pair in one runner block; not two independent candidate samples.",
        }

    public_pair = processes["public658"]
    public_shadow = processes["public658-shadow"]
    assert public_pair["source_sha256"] == public_shadow["source_sha256"]
    assert public_pair["library_sha256"] == public_shadow["library_sha256"]
    public_control_gap = 100 * (public_shadow["x_balanced_time_ratio_equal_file_mean"]
                                / public_pair["x_balanced_time_ratio_equal_file_mean"] - 1)

    # Existing analysis should match independently recomputed raw X/Y.
    analyzed_observations = {}
    for candidate in analysis["candidates"]:
        for obs in candidate["observations"]:
            analyzed_observations[(candidate["candidate"], obs["entry_role"], obs["calibration"])] = obs

    old_replay = M.Replay(OLD_CAPTURE, RULES)
    new_replay = M.Replay(NEW_CAPTURE, RULES)
    assert str(old_replay.context["snapshot_id"]) == str(analysis["snapshot"]["snapshot_id"])
    assert str(new_replay.context["snapshot_id"]) == "29954"
    old_api_audit = M.audit(old_replay)
    new_api_audit = M.audit(new_replay)
    assert old_api_audit["frontier_ids_match"] and new_api_audit["frontier_ids_match"]
    old_frontier = {row["id"]: row for row in old_api_audit["frontier"]}
    new_frontier = {row["id"]: row for row in new_api_audit["frontier"]}
    assert set(old_frontier) == set(new_frontier)
    old_payable = {str(row["id"]): float(row["recomputed_payable_pct"])
                   for row in old_api_audit["payment_disposition"]}
    new_payable = {str(row["id"]): float(row["recomputed_payable_pct"])
                   for row in new_api_audit["payment_disposition"]}
    assert set(old_payable) == set(new_payable)
    frontier_deltas = [
        {"id": name,
         "abs_x_delta": abs(float(old_frontier[name]["x"]) - float(new_frontier[name]["x"])),
         "abs_y_delta_pp": abs(float(old_frontier[name]["y_pct"]) - float(new_frontier[name]["y_pct"])),
         "abs_geometric_share_delta_pp": abs(float(old_frontier[name]["share_pct"]) - float(new_frontier[name]["share_pct"])),
         "abs_payable_share_delta_pp": abs(old_payable[name] - new_payable[name])}
        for name in old_frontier
    ]
    anchor_x = float(old_replay.byid["658"]["metrics"]["balanced_time_ratio"])
    anchor_y = float(old_replay.byid["658"]["metrics"]["mean_file_compression_pct"])
    projection_rows = []
    projection_x_errors, projection_y_errors = [], []
    share_errors = []
    for candidate in analysis["candidates"]:
        candidate_name = candidate["candidate"]
        for role, process_name in [("candidate", candidate_name),
                                   ("same_binary_copy_control", candidate_name + "-shadow")]:
            measured = processes[process_name]
            for calibration, anchor_name in [("primary", "public658"),
                                             ("shadow", "public658-shadow")]:
                parent = processes[anchor_name]
                projected_x = anchor_x * measured["x_balanced_time_ratio_equal_file_mean"] / parent["x_balanced_time_ratio_equal_file_mean"]
                projected_y = anchor_y + measured["y_mean_file_compression_pct"] - parent["y_mean_file_compression_pct"]
                obs = analyzed_observations[(candidate_name, "candidate" if role == "candidate" else "control", calibration)]
                x_error = abs(projected_x - float(obs["projected_time"]))
                y_error = abs(projected_y - float(obs["projected_size_pct"]))
                projection_x_errors.append(x_error)
                projection_y_errors.append(y_error)
                old_score = AUDIT.score_one(old_replay, f"{candidate_name}-{role}-{calibration}-old",
                                            projected_x, projected_y)
                new_score = AUDIT.score_one(new_replay, f"{candidate_name}-{role}-{calibration}-new",
                                            projected_x, projected_y)
                old_share = float(old_score.get("share_pct", 0.0))
                new_share = float(new_score.get("share_pct", 0.0))
                stored_share = float(obs["single_pool_share_pct"])
                share_errors.append(abs(old_share - stored_share))
                projection_rows.append({
                    "candidate": candidate_name, "role": role,
                    "process_name": process_name, "rust_source_sha256": measured["source_sha256"],
                    "executable_sha256": measured["library_sha256"],
                    "calibration": calibration, "anchor_process": anchor_name,
                    "raw_x": measured["x_balanced_time_ratio_equal_file_mean"],
                    "raw_y_pct": measured["y_mean_file_compression_pct"],
                    "projected_x": projected_x, "projected_y_pct": projected_y,
                    "analysis_projected_x": float(obs["projected_time"]),
                    "analysis_projected_y_pct": float(obs["projected_size_pct"]),
                    "projection_abs_error_x": x_error, "projection_abs_error_y_pp": y_error,
                    "old_snapshot_29953_recomputed_share_pct": old_share,
                    "analysis_stored_29953_share_pct": stored_share,
                    "latest_snapshot_29954_geometric_share_pct": new_share,
                    "latest_snapshot_neighbors": [new_score.get("predecessor"), new_score.get("successor")],
                    "latest_snapshot_on_frontier": bool(new_score),
                })
    assert max(projection_x_errors, default=0) < 1e-10
    assert max(projection_y_errors, default=0) < 1e-10
    assert max(share_errors, default=0) < 1e-9

    # Carry the previous C4 discovery coordinates forward to the newest
    # capture as well; unchanged values still describe the old measured block.
    c4_analysis = read_json(ROOT / "evidence/round26/extension1h/c4-final-analysis.json")
    c4_source_replay = M.Replay(C4_SOURCE_CAPTURE, C4_SOURCE_RULES)
    c4_source_audit = M.audit(c4_source_replay)
    assert str(c4_analysis["snapshot"]["snapshot_id"]) == str(c4_source_replay.context["snapshot_id"])
    c4_rows = []
    for candidate in c4_analysis["candidates"]:
        for obs in candidate["observations"]:
            x, y = float(obs["projected_time"]), float(obs["projected_size_pct"])
            source_share = float(AUDIT.score_one(c4_source_replay, f"c4-{len(c4_rows)}-source", x, y).get("share_pct", 0.0))
            intermediate_share = float(AUDIT.score_one(old_replay, f"c4-{len(c4_rows)}-29953", x, y).get("share_pct", 0.0))
            latest_share = float(AUDIT.score_one(new_replay, f"c4-{len(c4_rows)}-29954", x, y).get("share_pct", 0.0))
            recorded_share = float(obs["single_pool_share_pct"])
            c4_rows.append({"entry_role": obs["entry_role"], "calibration": obs["calibration"],
                            "x": x, "y_pct": y, "source_snapshot_29924_recorded_share_pct": recorded_share,
                            "source_snapshot_29924_recomputed_share_pct": source_share,
                            "share_snapshot_29953_pct": intermediate_share,
                            "share_snapshot_29954_pct": latest_share,
                            "status": "HISTORICAL_C4_DISCOVERY_BLOCK_NOT_NEW_CONFIRMATION"})

    c2_main = processes["r26-c-658-fold-tail"]
    c3_main = processes["r26-c-658-deferred-extension"]
    c2_primary_gain = 100 * (c2_main["x_balanced_time_ratio_equal_file_mean"]
                             / public_pair["x_balanced_time_ratio_equal_file_mean"] - 1)
    c3_primary_gain = 100 * (c3_main["x_balanced_time_ratio_equal_file_mean"]
                             / public_pair["x_balanced_time_ratio_equal_file_mean"] - 1)

    latest_receipt = read_json(NEW_CAPTURE / "receipt.json")
    latest_capture_hash = digest(NEW_CAPTURE / "receipt.json")
    latest_context = new_replay.context
    null_score_rows = [row for row in new_replay.rows if row.get("score") is None]
    null_admitted_bounded = [row for row in null_score_rows
                             if (row.get("admission") or {}).get("admitted") is True
                             and (row.get("bounds") or {}).get("eligible") is True]

    result = {
        "status": "VERIFIED_NINE_RAW_METHODS_PROJECTIONS_AND_29954_REPLAY",
        "checked_utc": datetime.now(timezone.utc).isoformat(),
        "ci_run": {"run_id": RUN_ID, "batch": "screen90-c23", "conclusion": "success",
                   "role": "discovery", "paired_processes": 9,
                   "source": "evidence/round26/extension90m/c23-start-analysis.json"},
        "raw_benchmark_protocol": {
            "process_count": len(processes), "process_names": EXPECTED_PROCESSES,
            "files_per_process": 28, "warmup_rounds": 1, "measured_rounds_per_file": 11,
            "metric_formula": "X = equal-file mean(candidate median measured total_s / incumbent median measured total_s); Y = equal-file mean(100 * output_bytes / raw_bytes). Total time includes parser plus encoder.",
            "same_28_inputs_and_sha256_across_processes": True,
            "incumbent_source_and_library_identical_across_processes": len(incumbent_sources) == 1,
            "raw_hashes_match_analysis_record": all(item["match"] for item in raw_hash_checks.values()),
            "raw_hash_checks": raw_hash_checks,
            "processes": list(processes.values()),
        },
        "same_binary_controls": {
            "candidate_main_vs_copy": copy_controls,
            "public658_main_vs_shadow_relative_time_gap_pct": public_control_gap,
            "public658_main_source_sha256": public_pair["source_sha256"],
            "public658_main_executable_sha256": public_pair["library_sha256"],
            "interpretation": "The -0.384% #658 main/shadow gap is an observed same-binary control in this one runner block. Candidate/copy rows are controls sharing the same source and are not independent candidate samples.",
        },
        "candidate_raw_x_y_and_parent_delta": {
            "parent_process": "public658",
            "parent_raw_x": public_pair["x_balanced_time_ratio_equal_file_mean"],
            "parent_raw_y_pct": public_pair["y_mean_file_compression_pct"],
            "c2_main_raw_x": c2_main["x_balanced_time_ratio_equal_file_mean"],
            "c2_main_raw_y_pct": c2_main["y_mean_file_compression_pct"],
            "c2_main_time_delta_vs_parent_pct": c2_primary_gain,
            "c3_main_raw_x": c3_main["x_balanced_time_ratio_equal_file_mean"],
            "c3_main_raw_y_pct": c3_main["y_mean_file_compression_pct"],
            "c3_main_time_delta_vs_parent_pct": c3_primary_gain,
            "candidate_y_delta_vs_parent_pp": {
                "c2": c2_main["y_mean_file_compression_pct"] - public_pair["y_mean_file_compression_pct"],
                "c3": c3_main["y_mean_file_compression_pct"] - public_pair["y_mean_file_compression_pct"],
            },
        },
        "projection_formula_audit": {
            "anchor_snapshot_id": str(old_replay.context["snapshot_id"]),
            "anchor_id": "658", "anchor_x": anchor_x, "anchor_y_pct": anchor_y,
            "formula": "projected X = formal #658 X * raw process X / selected #658 calibration process X; projected Y = formal #658 Y + raw process Y - selected calibration process Y.",
            "max_abs_projection_x_error": max(projection_x_errors),
            "max_abs_projection_y_error_pp": max(projection_y_errors),
            "max_29953_share_replay_error_pp": max(share_errors),
            "rows": projection_rows,
        },
        "snapshot_29953_start": {"snapshot": old_replay.context,
                                 "independent_api_replay": {key: old_api_audit[key] for key in [
                                     "status", "input_rows", "admitted_bounded_rows", "reconstructed_frontier",
                                     "frontier_ids_match", "max_independent_api_error_pp",
                                     "max_independent_official_scorer_error_pp"]}},
        "snapshot_29954_c23_capture": {
            "snapshot": latest_context,
            "retrieval_start_utc": latest_receipt["retrieval_start_utc"],
            "retrieval_end_utc": latest_receipt["retrieval_end_utc"],
            "receipt_sha256": latest_capture_hash,
            "pagination": latest_receipt["pagination"],
            "score_null_row_count": len(null_score_rows),
            "score_null_admitted_and_bounded_count": len(null_admitted_bounded),
            "independent_api_replay": {key: new_api_audit[key] for key in [
                "status", "input_rows", "admitted_bounded_rows", "reconstructed_frontier",
                "frontier_ids_match", "max_independent_api_error_pp",
                "max_independent_official_scorer_error_pp", "max_api_payable_error_fraction",
                "max_weights_by_hotkey_error_fraction", "sum_geometric_fraction", "sum_payable_fraction"]},
        },
        "frontier_comparison_29953_to_29954": {
            "same_frontier_ids": True, "frontier_count": len(old_frontier),
            "max_abs_x_delta": max((row["abs_x_delta"] for row in frontier_deltas), default=0.0),
            "max_abs_y_delta_pp": max((row["abs_y_delta_pp"] for row in frontier_deltas), default=0.0),
            "max_abs_geometric_share_delta_pp": max((row["abs_geometric_share_delta_pp"] for row in frontier_deltas), default=0.0),
            "max_abs_payable_share_delta_pp": max((row["abs_payable_share_delta_pp"] for row in frontier_deltas), default=0.0),
            "all_coordinate_and_share_deltas_zero": all(
                row["abs_x_delta"] == row["abs_y_delta_pp"] == row["abs_geometric_share_delta_pp"] == row["abs_payable_share_delta_pp"] == 0
                for row in frontier_deltas),
        },
        "historical_c4_latest_snapshot_replay": {
            "source_snapshot_id": str(c4_analysis["snapshot"]["snapshot_id"]),
            "source_run_id": "38248399555", "source_role": "discovery", "source_block": 1,
            "source_snapshot_audit_status": c4_source_audit["status"],
            "max_source_snapshot_share_error_pp": max(abs(row["source_snapshot_29924_recorded_share_pct"]
                                                           - row["source_snapshot_29924_recomputed_share_pct"])
                                                       for row in c4_rows),
            "rows": c4_rows,
            "latest_snapshot_shares_equal_29953": all(
                row["share_snapshot_29953_pct"] == row["share_snapshot_29954_pct"] for row in c4_rows),
        },
        "interpretation_limits": [
            "All nine source entries are from one CI run and one runner; only candidate main streams are candidate discovery samples.",
            "Each candidate shadow is a same-binary process control, not an independent implementation or independent candidate confirmation.",
            "The primary timing gains are smaller than the observed -0.38427% same-binary #658 control gap; this block cannot distinguish a mechanism gain from control movement.",
            "29954 shares are standalone hypothetical geometric projections on the captured public frontier, not admission, payment, or realized reward.",
            "The 11 API score:null rows are excluded from scored admitted-and-bounded points; none is admitted and bounds-eligible. Reconstructed official frontier IDs match the API flags.",
            "No new private performance or independent runner confirmation is inferred.",
        ],
    }
    assert len(null_admitted_bounded) == 0
    write_json(OUTPUT, result)
    print(json.dumps({"status": result["status"], "snapshot_id": latest_context["snapshot_id"],
                      "raw_processes": len(processes), "main_candidate_x_y": {
                          "c2": [c2_main["x_balanced_time_ratio_equal_file_mean"], c2_main["y_mean_file_compression_pct"]],
                          "c3": [c3_main["x_balanced_time_ratio_equal_file_mean"], c3_main["y_mean_file_compression_pct"]]},
                      "public658_shadow_gap_pct": public_control_gap,
                      "projection_error_x": max(projection_x_errors),
                      "projection_error_y_pp": max(projection_y_errors),
                      "historical_score_error_pp": max(share_errors),
                      "frontier_29953_29954_same": all(
                          row["abs_x_delta"] == row["abs_y_delta_pp"] == row["abs_geometric_share_delta_pp"] == row["abs_payable_share_delta_pp"] == 0
                          for row in frontier_deltas),
                      "c4_latest_snapshot_shares_equal": all(
                          row["share_snapshot_29953_pct"] == row["share_snapshot_29954_pct"] for row in c4_rows),
                      "null_score_rows": len(null_score_rows),
                      "null_admitted_bounded": len(null_admitted_bounded),
                      "output": str(OUTPUT)}, ensure_ascii=False))


if __name__ == "__main__":
    main()
