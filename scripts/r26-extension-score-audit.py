"""Re-audit the live R26 extension capture and map hypothetical score space.

This reads only captured API/rules/R26 evidence. It performs no network access,
benchmarking, candidate edits, CI, submission, or wallet operations.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import importlib
import json
import math
import statistics
from datetime import datetime, timezone
from pathlib import Path

M = importlib.import_module("r26-score-map")
ROOT = M.ROOT
DEFAULT_CAPTURE = ROOT / "evidence/round26/extension4h/official-reserve-start"
DEFAULT_RULES = ROOT / "evidence/round26/extension4h/rules-start"
DEFAULT_OUT = ROOT / "evidence/round26/extension4h/score-audit-29883"
DEFAULT_ROLES = ROOT / "evidence/round26/extension4h/all-roles-29883.json"
DEFAULT_ANALYSIS = ROOT / "evidence/round26/extension4h/all-analysis-29883.json"
DEFAULT_LEDGER = ROOT / "evidence/round26/extension4h/candidate-ledger-29883.json"
DEFAULT_SOURCE_AUDIT = ROOT / "evidence/round26/extension4h/new-source-audit/audit.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write_json(path: Path, value) -> None:
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def segments(rows, target, value_key):
    groups, current = [], []
    for row in rows:
        if row[value_key] is not None and row[value_key] >= target:
            current.append(row)
        elif current:
            groups.append(current)
            current = []
    if current:
        groups.append(current)
    out = []
    for group in groups:
        neighbor_regimes = list(dict.fromkeys(
            (p.get("predecessor"), p.get("successor")) for p in group
        ))
        out.append({
            "sampled_x_low": group[0]["x"],
            "sampled_x_high": group[-1]["x"],
            "sampled_width_x": group[-1]["x"] - group[0]["x"],
            "min_sample_share_pct": min(p[value_key] for p in group),
            "max_sample_share_pct": max(p[value_key] for p in group),
            "neighbor_regimes": [list(pair) for pair in neighbor_regimes],
            "neighbor_regime_switches": max(0, len(neighbor_regimes) - 1),
        })
    return out


def read_noise_controls(path):
    raw = json.loads(path.read_bytes())
    gaps = [float(row["relative_time_gap_pct"]) for row in raw["all_same_source_controls"]]
    return raw, gaps


def selected_noise(raw, noise_pair, runner_id, evidence_path):
    if not noise_pair or not runner_id:
        return {"source": "no_anchor_source_control_for_selected_runner", "source_name": None,
                "run_id": runner_id, "control_count": 0, "run_ids": [],
                "source_sha256": sha256(evidence_path)}, []
    source_name, copy_name = noise_pair
    controls = [row for row in raw["all_same_source_controls"]
                if row["main"] == source_name and row["copy"] == copy_name
                and str(row["run_id"]) == str(runner_id)] if runner_id else []
    if controls:
        gaps = [float(row["relative_time_gap_pct"]) for row in controls]
        source = "anchor_source_same_binary_controls_one_runner"
    else:
        gaps = []
        source = "no_anchor_source_control_for_selected_runner"
    if not gaps:
        return {"source": source, "source_name": source_name, "run_id": runner_id,
                "control_count": 0, "run_ids": [], "source_sha256": sha256(evidence_path)}, []
    lo, hi = min(gaps), max(gaps)
    run = next((r for r in raw.get("runs", []) if str(r.get("run_id")) == str(runner_id)), {})
    runner_model = run.get("environment", {}).get("cpu_model")
    runner_host = run.get("environment", {}).get("benchmark_provenance", {}).get("host_sha256")
    # Observed control ranges are sensitivity inputs, not error bounds or
    # guarantees for algorithm changes, this parent, or future runner results.
    factors = {1.0 + lo / 100.0 + i * (hi - lo) / 100.0 / 16 for i in range(17)}
    factors.add(1.0)
    basis = {"source": source, "source_name": source_name, "control_count": len(gaps),
             "run_id": str(runner_id),
             "runner_model": runner_model, "runner_host_sha256": runner_host,
             "run_ids": sorted(set(row["run_id"] for row in controls)),
             "relative_time_gap_pct_min": lo, "relative_time_gap_pct_max": hi,
             "relative_time_gap_samples_pct": gaps, "source_sha256": sha256(evidence_path)}
    return basis, sorted(factors)


def robust_share(replay, name, x, y, factors):
    varied = [x * f for f in factors]
    left, right = min(varied), max(varied)
    probes = set(varied)
    for _, boundary_x, _ in replay.base:
        if left <= boundary_x <= right:
            probes.add(math.nextafter(boundary_x, 0.0))
            probes.add(boundary_x)
            probes.add(math.nextafter(boundary_x, math.inf))
    observed = []
    for actual_x in probes:
        term = score_one(replay, name, actual_x, y)
        observed.append({
            "x": actual_x,
            "share_pct": term.get("share_pct", 0.0),
            "predecessor": term.get("predecessor"),
            "successor": term.get("successor"),
            "on_frontier": bool(term),
        })
    return min(observed, key=lambda item: item["share_pct"]), max(observed, key=lambda item: item["share_pct"]), len(observed)


def score_one(replay, name, x, y):
    """Score one hypothetical point, including the official singleton case."""
    if not (0 < x <= replay.policy["max_balanced_time_ratio"]
            and 0 < y <= replay.policy["max_mean_file_compression_pct"]):
        return {}
    if any(t <= x and q <= y for _, t, q in replay.base):
        return {}
    if all(x <= t and y <= q for _, t, q in replay.base):
        return {"share_pct": 100.0, "on_frontier": True,
                "predecessor": None, "successor": None, "singleton_frontier": True}
    return replay.score([(name, x, y)]).get(name, {})


def route_configs(replay):
    specs = [
        {"name": "fast-641", "anchor_id": "641", "x_domain": [0.38, 0.65], "x_step": 0.00025,
         "noise_pair": ["public641", "public641-shadow"], "noise_runner_id": "38215452345",
         "quality_deltas_pp": [0, .05, .10, .20, .30, .40, .50, .60, .80, 1.0]},
        {"name": "fast-658", "anchor_id": "658", "x_domain": [0.38, 0.65], "x_step": 0.00025,
         "noise_pair": ["public658", "public658-shadow"], "noise_runner_id": "38224543411",
         "quality_deltas_pp": [0, .05, .10, .20, .30, .40, .60, .80, 1.0]},
        {"name": "slower-552", "anchor_id": "552", "x_domain": [0.10, 4.20], "x_step": 0.01,
         "noise_pair": ["public552", "public552-shadow"], "noise_runner_id": "38227360774",
         "quality_deltas_pp": [0, .0025, .005, .01, .02, .03, .04, .05, .075, .10]},
        {"name": "slower-628", "anchor_id": "628", "x_domain": [.10, 7.00], "x_step": 0.01,
         "noise_pair": ["public628", "public628-shadow"], "noise_runner_id": "38177780351",
         "quality_deltas_pp": [0, .0001, .00025, .0005, .001, .0015, .002, .003, .005, .01]},
        {"name": "middle-361", "anchor_id": "361", "x_domain": [.10, 1.65], "x_step": 0.005,
         "noise_pair": None, "noise_runner_id": None,
         "quality_deltas_pp": [0, .005, .01, .015, .02, .025, .03, .04, .05, .06, .08, .10]},
    ]
    for spec in specs:
        row = replay.byid[spec["anchor_id"]]
        spec["anchor_x"] = row["metrics"]["balanced_time_ratio"]
        spec["anchor_y_pct"] = row["metrics"]["mean_file_compression_pct"]
        spec["anchor_admitted"] = (row.get("admission") or {}).get("admitted") is True
        spec["anchor_on_frontier"] = (row.get("score") or {}).get("on_frontier") is True
        spec["anchor_payable_pct"] = 100 * (row.get("score") or {}).get("payable_weight", 0)
        spec["anchor_payment_eligible"] = (row.get("score") or {}).get("payment_eligible") is True
        spec["quality_slices_pct"] = [spec["anchor_y_pct"] - d for d in spec["quality_deltas_pp"]]
    return specs


def same_source_control_table(raw, roles_path):
    assert all(row.get("same_binary_sha256") is True for row in raw["all_same_source_controls"])
    runs = {str(run["run_id"]): run for run in raw.get("runs", [])}
    groups = {}
    for row in raw["all_same_source_controls"]:
        key = (row["main"], row["copy"], str(row["run_id"]))
        groups.setdefault(key, []).append(row)
    result = []
    for (main, copy, run_id), rows in sorted(groups.items()):
        gaps = [float(row["relative_time_gap_pct"]) for row in rows]
        run = runs.get(run_id, {})
        env = run.get("environment", {})
        prov = env.get("benchmark_provenance", {})
        result.append({
            "source_main": main, "source_copy": copy, "run_id": run_id,
            "runner_model": env.get("cpu_model"), "runner_host_sha256": prov.get("host_sha256"),
            "same_binary": all(row.get("same_binary_sha256") is True for row in rows),
            "binary_hashes": sorted(set(h for row in rows for h in row.get("binary_hashes", []))),
            "control_count": len(rows), "relative_time_gap_pct_min": min(gaps),
            "relative_time_gap_pct_max": max(gaps), "relative_time_gap_samples_pct": gaps,
        })
    return {"source_file": str(roles_path), "source_sha256": sha256(roles_path),
            "group_count": len(result), "groups": result}


def candidate_projection_audit(replay, analysis_path, ledger_path, source_audit_path):
    analysis = json.loads(analysis_path.read_bytes())
    ledger = json.loads(ledger_path.read_bytes())
    source_audit = json.loads(source_audit_path.read_bytes())
    assert str(analysis.get("snapshot", {}).get("snapshot_id")) == str(replay.context["snapshot_id"])
    assert str(ledger.get("projection_snapshot", {}).get("snapshot_id")) == str(replay.context["snapshot_id"])
    all_observations, a19_observations, b37_observations = [], [], []
    a19_name = "r26-a-658-safe-word-offsets"
    b37_run = "38227360774"
    for candidate in analysis["candidates"]:
        for obs in candidate["observations"]:
            scored = score_one(replay, f"replay-{len(all_observations)}",
                               float(obs["projected_time"]), float(obs["projected_size_pct"]))
            record = {
                "candidate": candidate["candidate"], "path": candidate["path"],
                "rust_sha256": candidate["rust_sha256"], "run_id": str(obs["run_id"]),
                "block": obs["block"], "role": obs["role"], "entry_role": obs["entry_role"],
                "calibration": obs["calibration"], "anchor_name": obs.get("anchor_name"),
                "x": obs["projected_time"], "y_pct": obs["projected_size_pct"],
                "source_replay_share_pct": obs["single_pool_share_pct"],
                "current_api_replay_share_pct": scored.get("share_pct", 0.0),
                "share_replay_error_pp": scored.get("share_pct", 0.0) - obs["single_pool_share_pct"],
                "time_change_pct_vs_parent": obs.get("time_change_pct_vs_parent"),
                "quality_change_pp_vs_parent": obs.get("size_change_pp_vs_parent"),
                "predecessor": scored.get("predecessor"), "successor": scored.get("successor"),
                "on_frontier": bool(scored),
                "new_frontier_count": len(obs.get("new_frontier_ids", [])),
            }
            all_observations.append(record)
            if candidate["candidate"] == a19_name and obs.get("entry_role") == "candidate":
                a19_observations.append(record)
            if str(obs["run_id"]) == b37_run and obs.get("entry_role") == "candidate":
                b37_observations.append(record)
    source_meta = {str(k): {
        "snapshot_id": v.get("snapshot_id"), "http_status": v.get("http_status"), "capture_id_matches": v.get("checks", {}).get("capture_id_matches"),
        "raw_response_path": v.get("raw_response_path"), "raw_response_sha256": v.get("raw_response_sha256"),
        "raw_response_bytes": v.get("raw_response_bytes"), "rust_sha256": v.get("parse_sha256"),
        "lean_sha256": v.get("lean_sha256"), "all_checks_pass": v.get("all_checks_pass")}
        for k, v in source_audit.get("capture_integrity", {}).items() if str(k) in {"652", "658"}}
    assert source_audit.get("status") == "VERIFIED_STATIC_SOURCE_LINEAGE_AUDIT"
    assert set(source_meta) == {"652", "658"} and all(v.get("all_checks_pass") for v in source_meta.values())
    top_candidate = max((row for row in all_observations if row["entry_role"] == "candidate"),
                        key=lambda row: row["source_replay_share_pct"], default=None)
    top_any = max(all_observations, key=lambda row: row["source_replay_share_pct"], default=None)
    b37_groups = {}
    for row in b37_observations:
        key = (row["candidate"], row["calibration"])
        b37_groups.setdefault(key, []).append(row)
    ledger_sources = ledger.get("sources", [])
    ledger_crosscheck = {}
    for name in (a19_name, "r26-b-552-a-no-owner"):
        source = next((item for item in ledger_sources
                       if any(str(package.get("path", "")).replace("\\", "/").endswith("/" + name)
                              for package in item.get("packages", []))), None)
        ledger_crosscheck[name] = ({"rust_sha256": source.get("rust_sha256"),
                                    "package_paths": [p.get("path") for p in source.get("packages", [])],
                                    "matching_analysis_rust_sha256": next((c["rust_sha256"] for c in analysis["candidates"] if c["candidate"] == name), None),
                                    "observed_main_count": len(source.get("original_protocol_main_observations", [])),
                                    "source_sha256": sha256(ledger_path)} if source else None)
        if ledger_crosscheck[name]:
            assert ledger_crosscheck[name]["rust_sha256"] == ledger_crosscheck[name]["matching_analysis_rust_sha256"]
    replay_error = max((abs(row["share_replay_error_pp"]) for row in all_observations), default=0.0)
    assert replay_error < 1e-10
    assert b37_observations and all(abs(row["source_replay_share_pct"]) < 1e-12 for row in b37_observations)
    return {
        "analysis_path": str(analysis_path), "analysis_sha256": sha256(analysis_path),
        "ledger_path": str(ledger_path), "ledger_sha256": sha256(ledger_path),
        "snapshot_id": analysis.get("snapshot", {}).get("snapshot_id"),
        "ledger_crosscheck": ledger_crosscheck,
        "current_api_share_replay_max_abs_error_pp": replay_error,
        "global_candidate_projection_peak": top_candidate,
        "global_all_roles_projection_peak": top_any,
        "a19": {
            "candidate": a19_name,
            "rust_sha256": next((c["rust_sha256"] for c in analysis["candidates"] if c["candidate"] == a19_name), None),
            "observations": a19_observations,
            "primary_peak_pct": max((r["source_replay_share_pct"] for r in a19_observations if r["calibration"] == "primary"), default=0),
            "shadow_peak_pct": max((r["source_replay_share_pct"] for r in a19_observations if r["calibration"] == "shadow"), default=0),
        },
        "b37": {
            "run_id": b37_run, "candidate_observation_count": len(b37_observations),
            "zero_observation_count": sum(abs(r["source_replay_share_pct"]) < 1e-12 for r in b37_observations),
            "all_candidate_projected_shares_zero": bool(b37_observations) and all(abs(r["source_replay_share_pct"]) < 1e-12 for r in b37_observations),
            "groups": [{"candidate": key[0], "calibration": key[1], "count": len(rows),
                        "shares_pct": [r["source_replay_share_pct"] for r in rows],
                        "zero_count": sum(abs(r["source_replay_share_pct"]) < 1e-12 for r in rows)}
                       for key, rows in sorted(b37_groups.items())],
            "observations": b37_observations,
        },
        "public_source_receipts": {"source_audit_path": str(source_audit_path),
                                   "source_audit_sha256": sha256(source_audit_path),
                                   "targets_652_658": source_meta},
        "limits": ["These are current-snapshot conditional public projections; they are not formal submissions, private results, independent confirmations, or payout guarantees."]
    }


def run_route(replay, spec, factors, noise_basis):
    name, lo, hi, step = spec["name"], *spec["x_domain"], spec["x_step"]
    noise_lo = noise_basis.get("relative_time_gap_pct_min")
    noise_hi = noise_basis.get("relative_time_gap_pct_max")
    n = round((hi - lo) / step)
    all_rows, summaries = [], []
    for y in spec["quality_slices_pct"]:
        line = []
        for i in range(n + 1):
            x = lo + i * step
            term = score_one(replay, name, x, y)
            share = term.get("share_pct", 0.0)
            row = {"route": name, "anchor_id": spec["anchor_id"], "x": x, "y_pct": y,
                   "share_pct": share, "on_frontier": bool(term),
                   "predecessor": term.get("predecessor"), "successor": term.get("successor"),
                   "quality_gain_vs_anchor_pp": spec["anchor_y_pct"] - y,
                   "observed_control_envelope_lo_pct": noise_lo,
                   "observed_control_envelope_hi_pct": noise_hi,
                   "sensitivity_min_share_pct": None, "sensitivity_worst_x": None,
                   "sensitivity_worst_predecessor": None, "sensitivity_worst_successor": None,
                   "sensitivity_probe_count": 0}
            if share >= 5 and factors:
                worst, best, probes = robust_share(replay, name, x, y, factors)
                row.update({"sensitivity_min_share_pct": worst["share_pct"],
                            "sensitivity_worst_x": worst["x"],
                            "sensitivity_worst_predecessor": worst["predecessor"],
                            "sensitivity_worst_successor": worst["successor"],
                            "sensitivity_max_share_pct": best["share_pct"],
                            "sensitivity_probe_count": probes})
            line.append(row)
            all_rows.append(row)
        center = {str(t): segments(line, t, "share_pct") for t in (5, 10)}
        sensitivity = {str(t): segments(line, t, "sensitivity_min_share_pct") for t in (5, 10)}
        peak = max(line, key=lambda r: r["share_pct"])
        sensitivity_peak = max((r for r in line if r["sensitivity_min_share_pct"] is not None),
                               key=lambda r: r["sensitivity_min_share_pct"], default=None)
        noise_span_x_at_anchor = (spec["anchor_x"] * (noise_hi - noise_lo) / 100.0
                                  if noise_lo is not None and noise_hi is not None else None)
        narrow_sensitivity = []
        for threshold, found in sensitivity.items():
            for segment in found:
                segment = dict(segment)
                segment["x_noise_span_at_anchor"] = noise_span_x_at_anchor
                segment["width_vs_noise_span_ratio"] = (segment["sampled_width_x"] / noise_span_x_at_anchor
                                                          if noise_span_x_at_anchor else None)
                if noise_span_x_at_anchor is not None and segment["sampled_width_x"] <= noise_span_x_at_anchor:
                    narrow_sensitivity.append({"target_pct": int(threshold), **segment})
        summaries.append({
            "y_pct": y,
            "quality_gain_vs_anchor_pp": spec["anchor_y_pct"] - y,
            "center_share_target_segments": center,
            "observed_control_envelope_sensitivity_segments": sensitivity,
            "center_peak_sample": {k: peak[k] for k in ("x", "y_pct", "share_pct", "predecessor", "successor")},
            "sensitivity_peak_sample": ({k: sensitivity_peak[k] for k in ("x", "y_pct", "sensitivity_min_share_pct", "sensitivity_worst_x",
                                                                            "sensitivity_worst_predecessor", "sensitivity_worst_successor")}
                                         if sensitivity_peak else None),
            "narrow_sensitivity_windows_at_or_below_observed_control_envelope_width": narrow_sensitivity,
            "normalization_scope": "All surviving eligible frontier points are scored and normalized together for every coordinate."
        })
    return {"route": name, "anchor": {k: spec[k] for k in
            ("anchor_id", "anchor_x", "anchor_y_pct", "anchor_admitted", "anchor_on_frontier",
             "anchor_payable_pct", "anchor_payment_eligible")},
            "x_domain": spec["x_domain"], "x_step": step,
            "quality_slices_pct": spec["quality_slices_pct"], "slices": summaries,
            "grid_rows": all_rows,
            "sensitivity_basis": noise_basis,
            "interpretation": "INFERRED sampled sensitivity planning only; observed same-source timing ranges are not error bounds, stability guarantees, or candidate measurements."}


def render_note(result):
    snapshot = result["snapshot"]["snapshot_id"]
    def first_window(route, target, mode):
        key = "center_share_target_segments" if mode == "center" else "observed_control_envelope_sensitivity_segments"
        for item in route["slices"]:
            spans = item[key][str(target)]
            if spans:
                span = spans[0]
                low_mark = "≥" if span["sampled_x_low"] <= route["x_domain"][0] + route["x_step"] / 2 else ""
                high_mark = "≤" if span["sampled_x_high"] >= route["x_domain"][1] - route["x_step"] / 2 else ""
                return (f"Δy={item['quality_gain_vs_anchor_pp']:.5g}pp, x {low_mark}{span['sampled_x_low']:.6g}–"
                        f"{high_mark}{span['sampled_x_high']:.6g} (min {span['min_sample_share_pct']:.3f}%, "
                        f"{span['neighbor_regime_switches']} 邻居切换)")
        return "本扫描域无命中"

    lines = [
        f"# R26 评分与投入空间核验（snapshot {snapshot}）", "",
        f"**VERIFIED API replay**：计算时间 `{result['snapshot']['computed_at']}`，freshness `{result['snapshot'].get('freshness', 'unknown')}`；捕获 UTC `{result['source_receipts']['official_capture']['retrieval_start_utc']}`–`{result['source_receipts']['official_capture']['retrieval_end_utc']}`，receipt SHA-256 `{result['source_receipts']['official_capture']['sha256']}`。规则 commit `{result['source_receipts']['public_rules']['commit']}`。",
        f"独立核对 {result['verified_api']['input_rows']} 行、{result['verified_api']['admitted_bounded_rows']} 个 admitted+bounds 合格点、{result['verified_api']['reconstructed_frontier']} 点前沿；ID 一致，API 最大误差 `{result['verified_api']['max_independent_api_error_pp']:.3g}pp`，weights/current payable 最大误差 `{result['verified_api']['max_weights_by_hotkey_error_fraction']:.3g}`。池内最高当前可支付点 #{result['api_payable_top12'][0]['id']} = `{result['api_payable_top12'][0]['payable_pct']:.6f}%`；API `chain_accepted={result['verified_api']['api_chain_accepted']}`，因此这是公开快照重放，不代表已链上接受。",
        f"R26 原块候选视图最高条件投影为 `{result['candidate_projection_audit']['global_candidate_projection_peak']['source_replay_share_pct']:.6f}%`（{result['candidate_projection_audit']['global_candidate_projection_peak']['candidate']} / {result['candidate_projection_audit']['global_candidate_projection_peak']['calibration']}）；连同控制视图的最高值 `{result['candidate_projection_audit']['global_all_roles_projection_peak']['source_replay_share_pct']:.6f}%`（{result['candidate_projection_audit']['global_all_roles_projection_peak']['candidate']} / {result['candidate_projection_audit']['global_all_roles_projection_peak']['entry_role']}），均低于 5%，不代表正式准入或奖励。",
        "", "下表为**INFERRED**假设坐标的取样目标空间；中心格点与单源码/单 runner 同源包络敏感性分开。采样窗不是连续边界，不是误差界、稳定收益保证或正式奖励。质量 y 按切片固定，所有新增点都与当前完整前沿重新评分归一化。API 报告池内可支付权重，而 `source_code` 列表字段为空不能否定单独 `/source` 抓取；#652/#658 源码回执见后文。",
        "", "| 当前锚点 | 首个中心 ≥5% / ≥10% 空间 | 同源码单runner敏感性 ≥5% / ≥10% | API锚点状态 |",
        "|---|---|---|---|"
    ]
    for route in result["routes"]:
        a, b = route["anchor"], route["sensitivity_basis"]
        basis = (f"{b['source_name']} @ {b.get('run_id')} ({b.get('runner_model','?')}，n={b['control_count']}，"
                 f"{b.get('relative_time_gap_pct_min',0):+.3f}…{b.get('relative_time_gap_pct_max',0):+.3f}%)"
                 if b["control_count"] else "无该锚点同源码同runner对照")
        if not a["anchor_admitted"]:
            status = "未准入锚点"
        elif not a["anchor_payment_eligible"]:
            status = "当前不可支付锚点"
        elif not a["anchor_on_frontier"]:
            status = "已准入但非前沿"
        else:
            status = f"当前可支付 {a['anchor_payable_pct']:.3f}%"
        center = f"5% {first_window(route,5,'center')} / 10% {first_window(route,10,'center')}"
        sensitivity = f"{basis}；5% {first_window(route,5,'sensitivity')} / 10% {first_window(route,10,'sensitivity')}"
        lines.append(f"| #{a['anchor_id']} `x={a['anchor_x']:.6g}, y={a['anchor_y_pct']:.8f}%` | {center} | {sensitivity} | {status} |")

    a19 = result["candidate_projection_audit"]["a19"]
    primary = [r for r in a19["observations"] if r["calibration"] == "primary"]
    shadow = [r for r in a19["observations"] if r["calibration"] == "shadow"]
    peak = max(primary, key=lambda row: row["source_replay_share_pct"], default=None)
    a19_controls = [g for g in result["same_source_controls"]["groups"]
                    if g["run_id"] == "38224543411" and g["source_main"] in
                    ("public658", "r26-a-658-safe-word-offsets")]
    lines.extend(["", "x 段触及格点域边缘时以 `≥`/`≤` 标出；边缘值不是完整目标窗边界。",
                  "", "**A19 微峰复核**："])
    if peak:
        regimes = sorted({(r["predecessor"], r["successor"]) for r in primary}, key=lambda p: (str(p[0]),str(p[1])))
        lines.append(f"- primary observed peak `{peak['source_replay_share_pct']:.6f}%`（block {peak['block']}, x={peak['x']:.9f}, y={peak['y_pct']:.8f}%）；按 snapshot {snapshot} 当前 API 前沿重放 `{peak['current_api_replay_share_pct']:.6f}%`，邻居 `({peak['predecessor']},{peak['successor']})`。{len(a19['observations'])} 个 A19 原视图对当前公式重放最大差 `{result['candidate_projection_audit']['current_api_share_replay_max_abs_error_pp']:.3g}pp`。shadow peak `{a19['shadow_peak_pct']:.6f}%`; {len(primary)} 个 primary 点仅 {sum(r['source_replay_share_pct']==0 for r in primary)} 个为 0，邻居组合有 {len(regimes)} 种。")
    for control in a19_controls:
        lines.append(f"- 同 runner `{control['run_id']}` 的 `{control['source_main']}` / `{control['source_copy']}` 同二进制对照：{control['control_count']} 对，时间差 `{control['relative_time_gap_pct_min']:+.6f}%…{control['relative_time_gap_pct_max']:+.6f}%`。两组范围不得跨源合并；同源差、候选/父版的真实代码差及前沿邻居切换是不同证据。")
    lines.extend(["", "**B37 与公开源码**："])
    b37 = result["candidate_projection_audit"]["b37"]
    lines.append(f"- B37 run `{b37['run_id']}` 的 `r26-b-552-a-no-owner` 为 `{b37['zero_observation_count']}/{b37['candidate_observation_count']}` 零份额投影视图，当前 API 前沿重放也全为 0；两块 quality change 均为 0pp、time change 分别 `+1.408720%` 和 `+0.154823%`，所以相对 #552 同质量且更慢，0 可由支配关系复算。")
    src = result["candidate_projection_audit"]["public_source_receipts"]["targets_652_658"]
    if all(v.get("all_checks_pass") for v in src.values()):
        lines.append(f"- API 列表字段 `source_code` 为空，但在 snapshot {src['652']['snapshot_id']} 捕获的 `/source` 回执 #652/#658 均成功且内容/哈希核对通过。静态审计判 #652 有未命中参考库的活跃函数变化；#658 主要是已有 kernel 的路由/参数组合。源码谱系证据不等于性能证据。")

    lines.extend([
        "", "**下一轮路线比较与再启条件**：",
        "- **A路线 owner**：A18 已把 D 式必要窗口迁到 658 U118，实测新增 1,458,709 次 query-word 读取只覆盖 59,350／614,598 次 common；覆盖过薄，已停止配对，不扫窗口参数。A19 两块主总轴 `+0.277417%／−0.148876%`，row2 ASM 未变、row9 main word loop 未变；只保留窄安全算术，不继续同输出 offset/wrap 变体或 full gate。仅当新代码生成证据显示真实热路径改变，且同源码、原协议配对总时间跨块同向改善、质量不退并进入当前目标区，才重开性能候选；若 A19 式分歧仍决定晋升，再由 owner 判断是否执行 A20 建议但尚未做的逐阶段 CPU 前后关联诊断。",
        "- **B路线 owner**：#652 的 A-DP/per-position base-owner flatten 已在 B31/B33 完整消费并回退；B36/B37 删除 owner 仍同质量慢 `+1.408720%／+0.154823%`。不得据函数新颖性、坐标图或 B37 全零反复重做这些结构。仅当另一种维护设计先展示能实质减少已测剩余约 564M base 写入或约 74.5M 无效 rounded 扫描，并预先闭合 winner/tie、wrap、odd、fixed 与继承回退语义，才值得启动一次计数加完整消费；树边prefix/31-cap须先消除已测读写打包负担或出现真实新消费者，price-group须有单遍延迟消费且避免全域peek/vectorization须确认新工具链下原循环不再向量化。#652 word4目前只有源码预审；先证明caller需要高位且该读未被编译器消除，并区别已有q复用，再讨论一次原协议测量。否则维持 B 路线关闭。",
        f"这些再启条件来自 [B路线收尾](../../route-b/b41-extension-route-close.md) 与 [A14–A20路线总结](../../route-a/a14-a20-route-summary.md)；#652 的静态函数变化和本次评分空间本身都不构成重做理由。",
        "", "限制：敏感性只用所列源码/单 runner 的同二进制观测，采样格点不覆盖连续坐标；不推断未来运行概率。新候选仍需真实原协议、冻结后独立 runner 复测、完整 gate 与正式 admission；同 hotkey/失注册等支付排除不重归一化。",
        f"复核材料：[API审计](api-audit-{snapshot}.json)、[二维评分 JSON](score-map-{snapshot}.json)、[逐格 CSV](coordinate-grid-{snapshot}.csv)、[A19/B37 projection replay](round-projections-{snapshot}.json)。CSV SHA-256 `{result['coordinate_grid_csv']['sha256']}`。脚本 `scripts/r26-extension-score-audit.py`。"
    ])
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--capture", type=Path, default=DEFAULT_CAPTURE)
    parser.add_argument("--rules", type=Path, default=DEFAULT_RULES)
    parser.add_argument("--roles", type=Path, default=DEFAULT_ROLES)
    parser.add_argument("--analysis", type=Path, default=DEFAULT_ANALYSIS)
    parser.add_argument("--ledger", type=Path, default=DEFAULT_LEDGER)
    parser.add_argument("--source-audit", type=Path, default=DEFAULT_SOURCE_AUDIT)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUT)
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    assert not any(args.output.iterdir()), "Preserve earlier audits; use a fresh output directory"

    replay = M.Replay(args.capture, args.rules)
    audit = M.audit(replay)
    audit["status"] = "VERIFIED_INDEPENDENT_CURRENT_FRONTIER_AND_API_PAYOUT_REPLAY"
    audit["capture_receipt_sha256"] = sha256(args.capture / "receipt.json")
    audit["rules_receipt_sha256"] = sha256(args.rules / "receipt.json")
    snapshot = str(replay.context["snapshot_id"])
    write_json(args.output / f"api-audit-{snapshot}.json", audit)

    noise, gaps = read_noise_controls(args.roles)
    run_context = {str(r["run_id"]): r for r in noise.get("runs", [])}
    specs = route_configs(replay)
    routes = []
    for spec in specs:
        basis, factors = selected_noise(noise, spec.get("noise_pair"), spec.get("noise_runner_id"), args.roles)
        run = run_context.get(str(spec.get("noise_runner_id")), {})
        if run:
            basis["runner_model"] = run.get("environment", {}).get("cpu_model")
            basis["runner_host_sha256"] = run.get("environment", {}).get("benchmark_provenance", {}).get("host_sha256")
        routes.append(run_route(replay, spec, factors, basis))
    # Keep the full sampled map reviewable without duplicating it in two files.
    csv_path = args.output / f"coordinate-grid-{snapshot}.csv"
    fields = ["route", "anchor_id", "x", "y_pct", "share_pct", "on_frontier", "predecessor", "successor",
              "quality_gain_vs_anchor_pp", "observed_control_envelope_lo_pct", "observed_control_envelope_hi_pct",
              "sensitivity_min_share_pct", "sensitivity_worst_x", "sensitivity_worst_predecessor",
              "sensitivity_worst_successor", "sensitivity_max_share_pct", "sensitivity_probe_count"]
    with csv_path.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields)
        writer.writeheader()
        for route in routes:
            writer.writerows({k: row.get(k) for k in fields} for row in route["grid_rows"])
    for route in routes:
        del route["grid_rows"]

    top_payable = sorted((r for r in replay.rows if (r.get("score") or {}).get("payable_weight", 0) > 0),
                         key=lambda r: (r["score"]["payable_weight"], int(r["id"])), reverse=True)[:12]
    current_frontier = [{"id": n, "x": x, "y_pct": y, "payable_pct": 100 * (replay.byid[n].get("score") or {}).get("payable_weight", 0),
                        "predecessor": replay.initial[n].get("predecessor"),
                        "successor": replay.initial[n].get("successor")}
                       for n, x, y in replay.base]
    capture_receipt = json.loads((args.capture / "receipt.json").read_bytes())
    rules_receipt = json.loads((args.rules / "receipt.json").read_bytes())
    candidate_audit = candidate_projection_audit(replay, args.analysis, args.ledger, args.source_audit)
    control_table = same_source_control_table(noise, args.roles)
    result = {
        "status": "VERIFIED_CURRENT_API_REPLAY_AND_INFERRED_COORDINATE_GRID",
        "generated_utc": datetime.now(timezone.utc).isoformat(),
        "snapshot": replay.context,
        "source_receipts": {
            "official_capture": {"path": str(args.capture / "receipt.json"), "sha256": sha256(args.capture / "receipt.json"),
                                 "status": capture_receipt["status"], "retrieval_start_utc": capture_receipt["retrieval_start_utc"],
                                 "retrieval_end_utc": capture_receipt["retrieval_end_utc"],
                                 "raw_response_hashes": [{"file": f["file"], "sha256": f["sha256"], "bytes": f["bytes"]}
                                                          for f in capture_receipt["raw_response_files"]]},
            "public_rules": {"commit": rules_receipt["commit"], "receipt_sha256": sha256(args.rules / "receipt.json"),
                             "scoring_source_sha256": next(f["sha256"] for f in rules_receipt["files"]
                                                            if f["file"] == "validator--scoring--pareto.py")},
        },
        "verified_api": {k: audit[k] for k in ("input_rows", "admitted_bounded_rows", "reconstructed_frontier",
                    "frontier_ids_match", "max_independent_api_error_pp", "max_independent_official_scorer_error_pp",
                    "max_api_payable_error_fraction", "max_weights_by_hotkey_error_fraction", "sum_geometric_fraction",
                    "sum_payable_fraction", "api_payable_competition_weight", "api_unpaid_competition_weight", "api_chain_accepted")},
        "analysis_inputs": {
            "all_roles": {"path": str(args.roles), "sha256": sha256(args.roles), "same_source_control_count": len(noise["all_same_source_controls"])},
            "all_analysis": {"path": str(args.analysis), "sha256": sha256(args.analysis)},
            "candidate_ledger": {"path": str(args.ledger), "sha256": sha256(args.ledger)},
            "public_source_audit": {"path": str(args.source_audit), "sha256": sha256(args.source_audit)},
        },
        "api_payable_top12": [{"id": r["id"], "payable_pct": 100 * r["score"]["payable_weight"],
                               "source_code_present": r.get("source_code") is not None,
                               "metrics": r.get("metrics")} for r in top_payable],
        "current_frontier": current_frontier,
        "same_source_controls": control_table,
        "candidate_projection_audit": candidate_audit,
        "measured_noise": {
            "source": "R26 all-roles-29883.json; same-binary controls grouped without pooling by source, run_id, runner model, and host hash.",
            "source_sha256": sha256(args.roles), "control_count": len(gaps),
            "group_count": control_table["group_count"],
            "application": "Each route uses only its configured source pair within one run_id; there is no pooled cross-source/cross-run noise range. These are sensitivity inputs, not error bounds or stability guarantees. Only x is varied; y is held exact.",
        },
        "routes": routes,
        "coordinate_grid_csv": {"path": str(csv_path), "sha256": sha256(csv_path), "rows": sum(len(r["quality_slices_pct"]) * (round((r["x_domain"][1]-r["x_domain"][0])/r["x_step"])+1) for r in routes)},
        "limits": [
            "Coordinate grids and control-envelope sensitivity results are INFERRED sampled planning, not measured candidates, continuous bounds, admission, stability, or realized reward.",
            "Same-binary timing ranges do not bound candidate-to-parent or future-run variation; output quality is held exact at each hypothetical y slice.",
            "Future candidates are assumed to be admitted, independently payable, uncapped, and on fresh eligible hotkeys. API payment exclusions burn their allocation without renormalizing.",
            "Freshness is reported exactly as the API supplied it; exact live deployment bytes and finalized chain payment are not established by this capture."
        ]
    }
    write_json(args.output / f"round-projections-{snapshot}.json", candidate_audit)
    write_json(args.output / f"score-map-{snapshot}.json", result)
    (args.output / "decision-note.md").write_text(render_note(result), encoding="utf-8")
    print(json.dumps({"status": result["status"], "snapshot_id": replay.context["snapshot_id"],
                      "frontier": len(replay.base), "rows": result["coordinate_grid_csv"]["rows"],
                      "control_groups": control_table["group_count"],
                      "api_max_error_pp": audit["max_independent_api_error_pp"],
                      "output": str(args.output / f"score-map-{snapshot}.json")}, ensure_ascii=False), flush=True)


if __name__ == "__main__":
    main()
