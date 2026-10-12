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
DEFAULT_CAPTURE = ROOT / "evidence/round26/extension4h/official-start"
DEFAULT_RULES = ROOT / "evidence/round26/extension4h/rules-start"
DEFAULT_OUT = ROOT / "evidence/round26/extension4h/score-audit"
NOISE_EVIDENCE = ROOT / "evidence/round26/role-summary-29870.json"


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


def read_noise_controls():
    raw = json.loads(NOISE_EVIDENCE.read_bytes())
    gaps = [float(row["relative_time_gap_pct"]) for row in raw["all_same_source_controls"]]
    return raw, gaps


def selected_noise(raw, anchor_id, pooled_gaps):
    source_name = f"public{anchor_id}"
    controls = [row for row in raw["all_same_source_controls"]
                if row["main"] == source_name and row["copy"] == f"{source_name}-shadow"]
    if controls:
        gaps = [float(row["relative_time_gap_pct"]) for row in controls]
        source = "anchor_source_same_binary_controls"
    else:
        controls = raw["all_same_source_controls"]
        gaps = pooled_gaps
        source = "cross_route_R26_controls_sensitivity_only"
    lo, hi = min(gaps), max(gaps)
    # Observed control ranges are sensitivity inputs, not error bounds or
    # guarantees for algorithm changes, this parent, or future runner results.
    factors = {1.0 + lo / 100.0 + i * (hi - lo) / 100.0 / 16 for i in range(17)}
    factors.add(1.0)
    basis = {"source": source, "source_name": source_name, "control_count": len(gaps),
             "run_ids": sorted(set(row["run_id"] for row in controls)),
             "relative_time_gap_pct_min": lo, "relative_time_gap_pct_max": hi,
             "relative_time_gap_samples_pct": gaps, "source_sha256": sha256(NOISE_EVIDENCE)}
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
         "quality_deltas_pp": [0, .05, .10, .20, .30, .40, .50, .60, .80, 1.0, 1.25]},
        {"name": "slower-552", "anchor_id": "552", "x_domain": [0.10, 4.20], "x_step": 0.01,
         "quality_deltas_pp": [0, .0025, .005, .01, .02, .03, .04, .05, .075, .10]},
        {"name": "slower-628", "anchor_id": "628", "x_domain": [.10, 7.00], "x_step": 0.01,
         "quality_deltas_pp": [0, .0001, .00025, .0005, .001, .0015, .002, .003, .005, .01, .02]},
        {"name": "middle-361", "anchor_id": "361", "x_domain": [.10, 1.65], "x_step": 0.005,
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


def run_route(replay, spec, factors, noise_basis):
    name, lo, hi, step = spec["name"], *spec["x_domain"], spec["x_step"]
    noise_lo, noise_hi = noise_basis["relative_time_gap_pct_min"], noise_basis["relative_time_gap_pct_max"]
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
            if share >= 5:
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
        noise_span_x_at_anchor = spec["anchor_x"] * (noise_hi - noise_lo) / 100.0
        narrow_sensitivity = []
        for threshold, found in sensitivity.items():
            for segment in found:
                segment = dict(segment)
                segment["x_noise_span_at_anchor"] = noise_span_x_at_anchor
                segment["width_vs_noise_span_ratio"] = (segment["sampled_width_x"] / noise_span_x_at_anchor
                                                          if noise_span_x_at_anchor else None)
                if segment["sampled_width_x"] <= noise_span_x_at_anchor:
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
    lines = [
        "# R26 追加 4h：当前 API 评分核验与两轴投入空间",
        "",
        f"**VERIFIED API replay**：snapshot `{result['snapshot']['snapshot_id']}`，计算时间 `{result['snapshot']['computed_at']}`，freshness `{result['snapshot'].get('freshness', 'unknown')}`。",
        f"捕获 UTC `{result['source_receipts']['official_capture']['retrieval_start_utc']}` 至 `{result['source_receipts']['official_capture']['retrieval_end_utc']}`；原始响应 receipt SHA-256 `{result['source_receipts']['official_capture']['sha256']}`。规则 commit `{result['source_receipts']['public_rules']['commit']}`。",
        f"独立展开重算 {result['verified_api']['admitted_bounded_rows']} 个合格点并复核 {result['verified_api']['input_rows']} 行，重建前沿 {result['verified_api']['reconstructed_frontier']} 点；前沿 ID 与 API 一致。独立公式相对 API 最大误差 `{result['verified_api']['max_independent_api_error_pp']:.3g}` 个百分点，按 hotkey 汇总 payable 与 weights/current 最大误差 `{result['verified_api']['max_weights_by_hotkey_error_fraction']:.3g}`。当前可支付最高点 `{result['api_payable_top12'][0]['id']}` 为 `{result['api_payable_top12'][0]['payable_pct']:.6f}%`。",
        "",
        f"**R26 同源对照**：全体 {result['measured_noise']['control_count']} 组相同二进制 main/shadow 对照的相对时间差范围 `{result['measured_noise']['relative_time_gap_pct_min']:.6f}%` 至 `+{result['measured_noise']['relative_time_gap_pct_max']:.6f}%`，绝对值中位数 `{result['measured_noise']['median_absolute_gap_pct']:.6f}%`。这些值只作敏感性规划输入，不是测量误差界或未来稳定性保证。各锚点采用专属同源范围（有记录时），缺失时才使用跨路线范围；质量 y 固定在每个假设切片。",
        "",
        "以下格点及包络敏感性下界均为 **INFERRED**，不是候选实测或成功概率。区间是 CSV 格点命中范围，不是连续边界；每点均与该快照完整前沿一起重新归一化。",
        "",
        "| 路线锚点 | 敏感性 ≥5% 的首个采样切片 | 敏感性 ≥10% 的首个采样切片 | 锚点现状 |",
        "|---|---|---|---|",
    ]
    for route in result["routes"]:
        first = {}
        for target in ("5", "10"):
            found = None
            for slice_row in route["slices"]:
                segments_ = slice_row["observed_control_envelope_sensitivity_segments"][target]
                if segments_:
                    found = (slice_row, segments_)
                    break
            first[target] = found
        def text_window(found):
            if not found:
                return "本扫描域无敏感性窗"
            slice_row, spans = found
            desc = " / ".join(
                f"x={'≥' if s['sampled_x_low'] <= route['x_domain'][0] + route['x_step'] / 2 else ''}{s['sampled_x_low']:.6g}–{'≤' if s['sampled_x_high'] >= route['x_domain'][1] - route['x_step'] / 2 else ''}{s['sampled_x_high']:.6g} (min {s['min_sample_share_pct']:.3f}%, {s['neighbor_regime_switches']} 邻居切换)"
                for s in spans
            )
            gain = slice_row["quality_gain_vs_anchor_pp"]
            return f"y={slice_row['y_pct']:.8f}% (改善 {gain:.6g} pp)：{desc}"
        a = route["anchor"]
        b = route["sensitivity_basis"]
        basis_label = (f"{b['control_count']} 对 {b['relative_time_gap_pct_min']:+.3f}%…{b['relative_time_gap_pct_max']:+.3f}%"
                       if b["source"] == "anchor_source_same_binary_controls"
                       else f"跨路线 {b['control_count']} 对敏感性")
        if not a["anchor_admitted"]:
            status = "API 未准入"
        elif not a["anchor_payment_eligible"]:
            status = "API 当前不可支付"
        elif not a["anchor_on_frontier"]:
            status = "已准入，但当前非前沿"
        else:
            status = f"当前 payable {a['anchor_payable_pct']:.4f}%"
        lines.append(f"| #{a['anchor_id']} `{a['anchor_x']:.6g}, {a['anchor_y_pct']:.8f}%`；{basis_label} | {text_window(first['5'])} | {text_window(first['10'])} | {status} |")
    fast = next(route for route in result["routes"] if route["route"] == "fast-641")
    same_y = fast["slices"][0]
    center5 = same_y["center_share_target_segments"]["5"]
    center10 = same_y["center_share_target_segments"]["10"]
    sens5 = same_y["observed_control_envelope_sensitivity_segments"]["5"]
    sens10 = same_y["observed_control_envelope_sensitivity_segments"]["10"]
    def interval_text(parts):
        return "、".join(f"{part['sampled_x_low']:.6f}–{part['sampled_x_high']:.6f}" for part in parts) or "无"
    lines.extend(["", f"#641 同质量切片 `{same_y['y_pct']:.8f}%`（x步长 `{fast['x_step']}`）：中心格点 ≥5% 为 `{interval_text(center5)}`，≥10% 为 `{interval_text(center10)}`；在该父源码 10 组对照范围下，敏感性 ≥5% 为 `{interval_text(sens5)}`，≥10% 为 `{interval_text(sens10)}`。这只是连贯格点区和观测敏感性复算，不代表真实候选能到达该坐标。",
                  "触及 x 扫描域边缘的区间会用 `≥` 或 `≤` 标出，不能把边缘当作目标窗的完整边界。"])
    narrow = []
    for route in result["routes"]:
        for slice_row in route["slices"]:
            for span in slice_row["narrow_sensitivity_windows_at_or_below_observed_control_envelope_width"]:
                narrow.append((route["route"], slice_row, span))
    lines.extend(["", "**邻居切换与窄窗**：每个敏感性段记录新候选左右邻居；首达段的切换数已列于表中。宽度不超过对应观测同源时间跨度的敏感性窗如下："])
    if narrow:
        for name, slice_row, span in narrow:
            lines.append(f"- {name}，目标 {span['target_pct']}%，质量改善 {slice_row['quality_gain_vs_anchor_pp']:.6g} pp：x `{span['sampled_x_low']:.6g}–{span['sampled_x_high']:.6g}`，宽度/噪声跨度 `{span['width_vs_noise_span_ratio']:.3f}`。")
    else:
        lines.append("- 当前采样范围未发现宽度不超过观测同源时间跨度的敏感性段。")
    lines.extend([
        "",
        "**当前 API 增量**：与旧 snapshot 29785（最大 submission ID 645）相比，新出现 #646–#658。#646–#657 有正式记录，其中 #652 不在前沿，其余在当前前沿；#658 当前未准入。所有新增行的 API `source_code` 均为空，未发现可由该 API 直接取得的新公开源码机会。公开规则 commit 与此前相同。",
        "",
        "**限制**：候选仍需真实原协议测量、冻结后独立确认和完整 gate。观测包络没有覆盖算法变化或未来运行，敏感性窗不构成稳定达标保证。未来假设点需独立 eligible hotkey、通过 admission、未封顶；注销/重复 hotkey 等支付剔除会 burn 已分配值，不会把分母重归一化。#641 当前不准入，#361 当前因 deregistered 不可支付；它们只作坐标锚。",
        "",
        f"复核文件：[API 独立审计](api-audit-29870.json)，[完整坐标 JSON](score-map-29870.json)，[逐格 CSV](coordinate-grid-29870.csv)。CSV SHA-256 `{result['coordinate_grid_csv']['sha256']}`。脚本 `scripts/r26-extension-score-audit.py`。",
    ])
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--capture", type=Path, default=DEFAULT_CAPTURE)
    parser.add_argument("--rules", type=Path, default=DEFAULT_RULES)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUT)
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)

    replay = M.Replay(args.capture, args.rules)
    audit = M.audit(replay)
    audit["status"] = "VERIFIED_INDEPENDENT_CURRENT_FRONTIER_AND_API_PAYOUT_REPLAY"
    audit["capture_receipt_sha256"] = sha256(args.capture / "receipt.json")
    audit["rules_receipt_sha256"] = sha256(args.rules / "receipt.json")
    write_json(args.output / "api-audit-29870.json", audit)

    noise, gaps = read_noise_controls()
    noise_lo, noise_hi = min(gaps), max(gaps)
    specs = route_configs(replay)
    routes = []
    for spec in specs:
        basis, factors = selected_noise(noise, spec["anchor_id"], gaps)
        routes.append(run_route(replay, spec, factors, basis))
    # Keep the full sampled map reviewable without duplicating it in two files.
    csv_path = args.output / "coordinate-grid-29870.csv"
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

    current_weights = json.loads((args.capture / "weights-current.json").read_bytes())
    top_payable = sorted((r for r in replay.rows if (r.get("score") or {}).get("payable_weight", 0) > 0),
                         key=lambda r: (r["score"]["payable_weight"], int(r["id"])), reverse=True)[:12]
    current_frontier = [{"id": n, "x": x, "y_pct": y, "payable_pct": 100 * (replay.byid[n].get("score") or {}).get("payable_weight", 0),
                        "predecessor": replay.initial[n].get("predecessor"),
                        "successor": replay.initial[n].get("successor")}
                       for n, x, y in replay.base]
    capture_receipt = json.loads((args.capture / "receipt.json").read_bytes())
    rules_receipt = json.loads((args.rules / "receipt.json").read_bytes())
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
        "api_payable_top12": [{"id": r["id"], "payable_pct": 100 * r["score"]["payable_weight"],
                               "source_code_present": r.get("source_code") is not None,
                               "metrics": r.get("metrics")} for r in top_payable],
        "current_frontier": current_frontier,
        "measured_noise": {
            "source": "R26 same-binary main/shadow controls in role-summary-29870.json; each row asserts identical binary SHA-256.",
            "source_sha256": sha256(NOISE_EVIDENCE), "control_count": len(gaps),
            "relative_time_gap_pct_min": noise_lo, "relative_time_gap_pct_max": noise_hi,
            "median_absolute_gap_pct": statistics.median(abs(g) for g in gaps),
            "relative_time_gap_samples_pct": gaps,
            "application": "Control ranges are sensitivity inputs only, not errors/uncertainty bounds or stability guarantees. Each exact-anchor source with controls uses its own range; anchors without source-specific controls use the pooled R26 range and are labeled cross-route sensitivity. Only x is varied; y is held exact.",
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
    write_json(args.output / "score-map-29870.json", result)
    (args.output / "decision-note.md").write_text(render_note(result), encoding="utf-8")
    print(json.dumps({"status": result["status"], "snapshot_id": replay.context["snapshot_id"],
                      "frontier": len(replay.base), "rows": result["coordinate_grid_csv"]["rows"],
                      "pooled_control_sensitivity_envelope": [noise_lo, noise_hi],
                      "api_max_error_pp": audit["max_independent_api_error_pp"],
                      "output": str(args.output / "score-map-29870.json")}, ensure_ascii=False), flush=True)


if __name__ == "__main__":
    main()
