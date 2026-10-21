"""Independently replay the R26 90-minute-window opening score snapshot.

Reads captured official API/rules data and historical C4 evidence only. It does
not access the network, run benchmarks, or modify candidate sources.
"""
from __future__ import annotations

import hashlib
import importlib
import importlib.util
import json
import math
import re
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

CURRENT_CAPTURE = ROOT / "evidence/round26/extension90m/official-start"
CURRENT_RULES = ROOT / "evidence/round26/extension90m/rules-start"
PREVIOUS_CAPTURE = ROOT / "evidence/round26/extension1h/official-close"
PREVIOUS_RULES = ROOT / "evidence/round26/extension1h/rules-close"
HISTORICAL_C4 = ROOT / "evidence/round26/extension1h/c4-final-analysis.json"
ANALYZE_SCRIPT = ROOT / "scripts/analyze-round26.py"
OUTPUT = ROOT / "evidence/round26/extension90m/score-audit"
FOLLOWUP_C23 = OUTPUT / "c23-raw-audit-29954.json"


def read_json(path: Path):
    return json.loads(path.read_bytes())


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write_json(path: Path, value) -> None:
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def scored(replay, name: str, x: float, y: float) -> dict:
    return AUDIT.score_one(replay, name, float(x), float(y))


def qualifies(value: float, target: float) -> bool:
    return value > 0.0 if target == 0 else value >= target


def find_rightmost_threshold(replay, name: str, fixed: float, axis: str,
                             target: float, lo: float, hi: float, step: float) -> dict:
    """Sample a bounded one-dimensional slice, then refine its right edge."""
    count = math.ceil((hi - lo) / step)
    samples = []
    for i in range(count + 1):
        value = min(hi, lo + i * step)
        x, y = (value, fixed) if axis == "x" else (fixed, value)
        share = float(scored(replay, name, x, y).get("share_pct", 0.0))
        samples.append((value, share))

    groups = []
    current = []
    for row in samples:
        if qualifies(row[1], target):
            current.append(row)
        elif current:
            groups.append(current)
            current = []
    if current:
        groups.append(current)
    if not groups:
        return {"target_pct": target, "found": False, "search_domain": [lo, hi],
                "sample_step": step, "qualifying_intervals": []}

    intervals = []
    for group in groups:
        left, right = group[0][0], group[-1][0]
        left_inside, right_inside = group[0][1], group[-1][1]
        first_index = samples.index(group[0])
        last_index = first_index + len(group) - 1
        if first_index > 0:
            left_outside = samples[first_index - 1]
        else:
            left_outside = None
        if last_index + 1 < len(samples):
            right_outside = samples[last_index + 1]
        else:
            right_outside = None

        # Refine boundaries only inside the local sampled bracket. This avoids
        # assuming global monotonicity across frontier-neighbor changes.
        if left_outside is not None:
            bad, good = left_outside[0], left
            for _ in range(70):
                if good - bad <= 1e-12:
                    break
                mid = (bad + good) / 2
                x, y = (mid, fixed) if axis == "x" else (fixed, mid)
                value = float(scored(replay, name, x, y).get("share_pct", 0.0))
                if qualifies(value, target):
                    good = mid
                else:
                    bad = mid
            left, left_inside = good, float(scored(
                replay, name, *((good, fixed) if axis == "x" else (fixed, good))
            ).get("share_pct", 0.0))

        if right_outside is not None:
            good, bad = right, right_outside[0]
            for _ in range(70):
                if bad - good <= 1e-12:
                    break
                mid = (good + bad) / 2
                x, y = (mid, fixed) if axis == "x" else (fixed, mid)
                value = float(scored(replay, name, x, y).get("share_pct", 0.0))
                if qualifies(value, target):
                    good = mid
                else:
                    bad = mid
            right, right_inside = good, float(scored(
                replay, name, *((good, fixed) if axis == "x" else (fixed, good))
            ).get("share_pct", 0.0))

        high_x, high_y = (right, fixed) if axis == "x" else (fixed, right)
        right_terms = scored(replay, name, high_x, high_y)
        if right_outside is not None:
            outside_x, outside_y = ((right_outside[0], fixed) if axis == "x"
                                    else (fixed, right_outside[0]))
            outside_terms = scored(replay, name, outside_x, outside_y)
        else:
            outside_terms = {}
        intervals.append({
            "low": left, "high": right,
            "low_boundary_share_pct": left_inside,
            "high_boundary_share_pct": right_inside,
            "high_boundary_neighbors": [right_terms.get("predecessor"), right_terms.get("successor")],
            "right_outside": right_outside[0] if right_outside else None,
            "right_outside_share_pct": right_outside[1] if right_outside else None,
            "right_outside_neighbors": [outside_terms.get("predecessor"), outside_terms.get("successor")],
        })

    return {"target_pct": target, "found": True, "search_domain": [lo, hi],
            "sample_step": step, "qualifying_intervals": intervals,
            "rightmost_qualifying_value": intervals[-1]["high"]}


def build_report(result: dict) -> str:
    snap = result["snapshot"]
    audit = result["api_replay"]
    lines = [
        "# R26 90 分钟窗：官方评分与读数审计", "",
        f"核验时间：`{result['checked_utc']}`。本报告只复算已保存的官方响应和历史测量。", "",
        "## 最新官方快照复算", "",
        (f"Snapshot `{snap['snapshot_id']}`，官方计算时间 `{snap['computed_at']}`；" 
         f"API 捕获 `{result['capture']['retrieval_start_utc']}`–`{result['capture']['retrieval_end_utc']}` UTC。"),
        f"Pareto `{audit['input_rows']}` 行，榜单 `{result['capture']['leaderboard_rows']}` 行，重建前沿 `{audit['reconstructed_frontier']}` 点；freshness 为 `{snap.get('freshness', 'UNKNOWN')}`。",
        (f"独立代数对 API 几何份额最大误差 `{audit['max_independent_api_error_pp']:.3g}` 个百分点；" 
         f"捕获官方 scorer 最大误差 `{audit['max_independent_official_scorer_error_pp']:.3g}` 个百分点。"),
        (f"几何 Pareto 池合计 `{100*audit['sum_geometric_fraction']:.9f}%`；" 
         f"API payable 合计 `{100*audit['sum_payable_fraction']:.9f}%`，未支付分配 `{100*audit['api_unpaid_competition_weight']:.9f}%`。"),
        f"`weights/current` 的捕获字段 `chain_accepted={audit['api_chain_accepted']}`；这只是 API 状态，不在本审计中推断钱包到账。", "",
        "## 最新真实前沿", "",
        "X/Y 为同一 snapshot 的官方 `balanced_time_ratio` / `mean_file_compression_pct`。几何份额按官方 Pareto 池归一；payable 列逐条复现 API 当前权重。", "",
        "| ID | X | Y (%) | 几何池份额 (%) | API payable (%) |",
        "|---:|---:|---:|---:|---:|",
    ]
    for row in result["frontier"]:
        lines.append(f"| {row['id']} | {row['x']:.9f} | {row['y_pct']:.9f} | {row['geometric_share_pct']:.9f} | {row['payable_share_pct']:.9f} |")

    followup = result.get("subsequent_official_capture")
    if followup:
        lines += [
            "",
            (f"后续 `official-c23` 捕获为 snapshot `{followup['snapshot_id']}`，查询时间 "
             f"`{followup['retrieval_start_utc']}`–`{followup['retrieval_end_utc']}` UTC。"),
            (f"与起始 snapshot `{snap['snapshot_id']}` 相比，前沿 ID、X、Y、几何及 payable 份额均逐点不变 "
             f"（105 点，最大差值 0）；因此上表也适用于该较新快照。九流程原始计时与重评分见 `c23-raw-audit-29954.json`。"),
        ]

    lines += ["", "## #658 坐标反推（假设几何，不是实测）", "",
              (f"锚点 #658 的官方坐标是 X `{result['anchor_658']['x']:.12f}`、" 
               f"Y `{result['anchor_658']['y_pct']:.12f}%`。以下只把假想点放进 snapshot `{snap['snapshot_id']}` 的几何公式，" 
               "假设其已准入、可支付且使用独立 hotkey；不表示候选实测、正式准入或成功概率。"), "",
              "固定 #658 的大小 Y，得到目标份额所需的最慢 X：", "",
              "| 几何份额目标 | 最大 X | 相对 #658 需快 | 边界解释 | 右边界邻居 → 其外侧 |",
              "|---:|---:|---:|---|---|"]
    for row in result["hypothetical_thresholds"]["same_size_as_658"]["targets"]:
        regime = row.get("searched_intervals", [{}])[-1]
        neighbors = f"{regime.get('high_boundary_neighbors')} → {regime.get('right_outside_neighbors')}"
        if row.get("one_sided_boundary"):
            probes = row["one_sided_boundary"]
            neighbors = (f"{probes['equal']['neighbors']} ({probes['equal']['share_pct']:.6f}%) → "
                         f"{probes['immediately_slower']['neighbors']} ({probes['immediately_slower']['share_pct']:.6f}%)")
        lines.append(f"| {row['target_pct'] if row['target_pct'] else '>0'}% | {row['max_x']:.12f} | {row['speedup_vs_658_pct']:.6f}% | {row['boundary_note']} | `{neighbors}` |")
    positive_x = result["hypothetical_thresholds"]["same_size_as_658"]["targets"][0]
    lines += ["", (f"正份额边界是严格条件：在 #562 的 X `{positive_x['max_x']:.12f}` 恰为 0%；" 
                     f"快一个浮点步长时为 `{positive_x['share_immediately_faster_pct']:.6f}%`，邻居为 `#669/#562`。"), ""]
    lines += ["", "固定 #658 的速度 X，得到各目标允许的最大大小轴 Y：", "",
              "| 几何份额目标 | 最大 Y (%) | 相对 #658 需少 | 边界解释 | 右边界邻居 → 其外侧 |",
              "|---:|---:|---:|---|---|"]
    for row in result["hypothetical_thresholds"]["same_speed_as_658"]["targets"]:
        regime = row.get("searched_intervals", [{}])[-1]
        neighbors = f"{regime.get('high_boundary_neighbors')} → {regime.get('right_outside_neighbors')}"
        lines.append(f"| {row['target_pct'] if row['target_pct'] else '>0'}% | {row['max_y_pct']:.12f} | {row['quality_improvement_pp']:.9f} pp | {row['boundary_note']} | `{neighbors}` |")
    positive_y = result["hypothetical_thresholds"]["same_speed_as_658"]["targets"][0]
    lines += ["", (f"大小边界同样严格：Y `{positive_y['max_y_pct']:.12f}%` 恰为 0%；" 
                     f"减小一个浮点步长时为 `{positive_y['share_immediately_smaller_y_pct']:.6f}%`。"), ""]

    lines += ["", "## 上一窗 C4 旧块按新快照重评分", "",
              (f"输入是上一窗 discovery run `{result['historical_c4']['source_run_id']}`、旧快照 "
               f"`{result['historical_c4']['source_snapshot_id']}` 的四个 primary/shadow 评分坐标。" 
               "现行份额按 29953 和后续 29954 重算，两快照前沿及份额逐点一致；旧块仍不是新测量或新确认。"), "",
              "| C4 条目 | 校准 | X | Y (%) | 旧快照份额 (%) | 29953/29954 几何份额 (%) | 原公共实测 X / Y (%) |",
              "|---|---|---:|---:|---:|---:|---:|"]
    for row in result["historical_c4"]["rows"]:
        lines.append(f"| {row['entry_role']} | {row['calibration']} | {row['x']:.12f} | {row['y_pct']:.12f} | {row['old_snapshot_share_pct']:.9f} | {row['latest_snapshot_geometric_share_pct']:.9f} | {row['public_measured_x']:.9f} / {row['public_measured_y_pct']:.9f} |")
    lines += ["", (f"旧份额公式回放与原记录最大差 `{result['historical_c4']['old_snapshot_max_abs_error_pp']:.3g}` 个百分点。" 
               "四行来自同一个 discovery block；public 实测坐标不是正式竞赛坐标，且不能当作本窗独立确认。"), "",
              "## Scorer 字节核对", "",
              (f"当前捕获 scorer SHA-256 `{result['scorer_byte_comparison']['latest_sha256']}`；" 
               f"`analyze-round26.py` 硬编码路径的 scorer SHA-256 `{result['scorer_byte_comparison']['analyze_round26_sha256']}`；" 
               f"逐字节一致：`{result['scorer_byte_comparison']['byte_identical']}`。旧脚本未修改。"), "",
              "证据和可重跑脚本见 `score-audit.json` 与 `scripts/r26-score90-audit.py`。", ""]
    return "\n".join(lines)


def main() -> None:
    OUTPUT.mkdir(parents=True, exist_ok=True)
    current = M.Replay(CURRENT_CAPTURE, CURRENT_RULES)
    previous = M.Replay(PREVIOUS_CAPTURE, PREVIOUS_RULES)
    current_audit = M.audit(current)
    previous_audit = M.audit(previous)

    current_receipt = read_json(CURRENT_CAPTURE / "receipt.json")
    current_rules_receipt = read_json(CURRENT_RULES / "receipt.json")
    snapshot = current.context
    assert str(snapshot["snapshot_id"]) == str(current_receipt["snapshot_id"])
    assert current_receipt["weights_same_snapshot"] is True
    assert len(current.rows) == current_receipt["pagination"]["pareto"]["rows"]

    api_by_id = current.byid
    payable = {row["id"]: row["recomputed_payable_pct"]
               for row in current_audit["payment_disposition"]}
    frontier = []
    for name, x, y in current.base:
        term = current.initial[name]
        api_score = api_by_id[name].get("score") or {}
        frontier.append({
            "id": name, "x": x, "y_pct": y,
            "geometric_share_pct": term["share_pct"],
            "api_geometric_share_pct": 100 * float(api_score.get("pareto_weight", 0.0)),
            "payable_share_pct": payable.get(name, 0.0),
            "payment_eligible": bool(api_score.get("payment_eligible")),
            "predecessor": term.get("predecessor"), "successor": term.get("successor"),
        })

    # Cross-check the independent replay against the captured current scorer.
    from round3 import load_scorer
    scorer_path = CURRENT_RULES / "validator--scoring--pareto.py"
    scorer = load_scorer(scorer_path)
    bounds = scorer.Boundaries(current.policy["max_balanced_time_ratio"],
                               current.policy["max_mean_file_compression_pct"])
    official_weights = scorer.local_global_improvement_space_log_weights(
        scorer.pareto_front([scorer.Point(*point) for point in current.all_points]), bounds
    )
    explicit_errors = [abs(100 * float(official_weights.get(name, 0.0))
                           - current.initial.get(name, {}).get("share_pct", 0.0))
                       for name in current.byid]
    assert max(explicit_errors) < 1e-10

    # Reproduce all stored C4 discovery coordinates on both its old and current snapshots.
    old_analysis = read_json(HISTORICAL_C4)
    assert str(old_analysis["snapshot"]["snapshot_id"]) == str(previous.context["snapshot_id"])
    old_share_errors = []
    old_rows, c4_run_id = [], None
    for candidate in old_analysis["candidates"]:
        for obs in candidate["observations"]:
            c4_run_id = str(obs["run_id"])
            x, y = float(obs["projected_time"]), float(obs["projected_size_pct"])
            old_calc = scored(previous, f"old-{len(old_rows)}", x, y)
            latest_calc = scored(current, f"latest-{len(old_rows)}", x, y)
            old_share = float(old_calc.get("share_pct", 0.0))
            recorded = float(obs["single_pool_share_pct"])
            old_share_errors.append(abs(old_share - recorded))
            old_rows.append({
                "candidate": candidate["candidate"], "entry_role": obs["entry_role"],
                "calibration": obs["calibration"], "anchor_name": obs["anchor_name"],
                "run_id": obs["run_id"], "block": obs["block"], "role": obs["role"],
                "x": x, "y_pct": y, "old_snapshot_share_pct": old_share,
                "recorded_old_snapshot_share_pct": recorded,
                "latest_snapshot_geometric_share_pct": float(latest_calc.get("share_pct", 0.0)),
                "latest_neighbors": [latest_calc.get("predecessor"), latest_calc.get("successor")],
                "public_measured_x": float(obs["public_time"]),
                "public_measured_y_pct": float(obs["public_size_pct"]),
                "status": "HISTORICAL_DISCOVERY_COORDINATE_REPLAY_NOT_NEW_MEASUREMENT_OR_CONFIRMATION",
            })
    assert max(old_share_errors, default=0.0) < 1e-9

    # Verify the historical API snapshot receipt separately from the current one.
    assert previous_audit["frontier_ids_match"] is True

    # The #658 time/size inversions are geometry-only sensitivity calculations.
    anchor = api_by_id["658"]["metrics"]
    anchor_x = float(anchor["balanced_time_ratio"])
    anchor_y = float(anchor["mean_file_compression_pct"])
    same_size_name = "hypothetical-same-size-658"
    same_size_results = {
        target: find_rightmost_threshold(current, same_size_name, anchor_y, "x", target,
                                         0.40, 0.48, 0.00002)
        for target in (0.0, 5.0, 10.0)
    }
    same_speed_name = "hypothetical-same-speed-658"
    same_speed_results = {
        target: find_rightmost_threshold(current, same_speed_name, anchor_x, "y", target,
                                         35.0, 35.60, 0.00005)
        for target in (0.0, 5.0, 10.0)
    }

    # The right edge for a merely positive geometric share is bounded exactly by
    # the faster, smaller #562 frontier point; equality is dominated.
    row562 = next(row for row in frontier if row["id"] == "562")
    x562, y562 = float(row562["x"]), float(row562["y_pct"])
    x_left = math.nextafter(x562, 0.0)
    x_at = x562
    y_left = math.nextafter(y562, 0.0)
    positive_x_left = scored(current, "positive-left-of-562", x_left, anchor_y)
    positive_x_at = scored(current, "positive-at-562", x_at, anchor_y)
    positive_y_left = scored(current, "positive-left-of-562-y", anchor_x, y_left)
    positive_y_at = scored(current, "positive-at-562-y", anchor_x, y562)
    assert float(positive_x_left.get("share_pct", 0.0)) > 0 and not positive_x_at
    assert float(positive_y_left.get("share_pct", 0.0)) > 0 and not positive_y_at

    def threshold_row(target: float, searched: dict, axis: str) -> dict:
        assert searched["found"]
        maximum = float(searched["rightmost_qualifying_value"])
        if axis == "x":
            return {"target_pct": target, "max_x": maximum,
                    "speedup_vs_658_pct": 100 * (1 - maximum / anchor_x),
                    "boundary_note": "strictly faster than the first dominating #562 point" if target == 0 else "rightmost sampled interval refined by bisection",
                    "searched_intervals": searched["qualifying_intervals"]}
        return {"target_pct": target, "max_y_pct": maximum,
                "quality_improvement_pp": anchor_y - maximum,
                "boundary_note": "strictly smaller than #562 Y to avoid domination" if target == 0 else "rightmost sampled interval refined by bisection",
                "searched_intervals": searched["qualifying_intervals"]}

    same_size = [threshold_row(t, same_size_results[t], "x") for t in (0.0, 5.0, 10.0)]
    same_speed = [threshold_row(t, same_speed_results[t], "y") for t in (0.0, 5.0, 10.0)]
    same_size[0].update({"max_x": x562, "strict": True,
                         "boundary_share_at_equal_x_pct": float(positive_x_at.get("share_pct", 0.0)),
                         "share_immediately_faster_pct": float(positive_x_left["share_pct"])})
    same_speed[0].update({"max_y_pct": y562, "strict": True,
                          "boundary_share_at_equal_y_pct": float(positive_y_at.get("share_pct", 0.0)),
                          "share_immediately_smaller_y_pct": float(positive_y_left["share_pct"])})

    def point_probe(name: str, x: float, y: float) -> dict:
        row = current.describe([(name, x, y)])["points"][name]
        term = row.get("terms") or {}
        return {"x": x, "y_pct": y, "share_pct": row["share_pct"],
                "neighbors": [term.get("predecessor"), term.get("successor")],
                "dominator_ids": row["dominator_ids"],
                "removed_existing_ids": row["removed_existing_ids"]}

    x659 = float(api_by_id["659"]["metrics"]["balanced_time_ratio"])
    row659_probes = {
        "immediately_faster": point_probe("at-659-left", math.nextafter(x659, 0.0), anchor_y),
        "equal": point_probe("at-659-equal", x659, anchor_y),
        "immediately_slower": point_probe("at-659-right", math.nextafter(x659, math.inf), anchor_y),
    }
    assert row659_probes["equal"]["share_pct"] >= 10.0
    assert row659_probes["immediately_slower"]["share_pct"] < 10.0
    same_size[2]["max_x"] = x659
    same_size[2]["speedup_vs_658_pct"] = 100 * (1 - x659 / anchor_x)
    same_size[2]["boundary_note"] = "exactly at #659 X; one floating-point step slower falls below 10%"
    same_size[2]["one_sided_boundary"] = row659_probes

    latest_commit = next(f for f in current_rules_receipt["files"]
                         if f["file"] == "validator--scoring--pareto.py")
    match = re.search(r"SCORER_PATH\s*=\s*ROOT\s*/\s*['\"]([^'\"]+)['\"]",
                      ANALYZE_SCRIPT.read_text(encoding="utf-8"))
    assert match, "Could not locate analyze-round26.py hardcoded scorer path"
    analyze_scorer_path = ROOT / match.group(1)
    latest_bytes = scorer_path.read_bytes()
    analyze_bytes = analyze_scorer_path.read_bytes()
    scorer_comparison = {
        "latest_capture_path": scorer_path.relative_to(ROOT).as_posix(),
        "latest_sha256": sha256(scorer_path), "latest_bytes": len(latest_bytes),
        "analyze_round26_path": analyze_scorer_path.relative_to(ROOT).as_posix(),
        "analyze_round26_sha256": sha256(analyze_scorer_path),
        "analyze_round26_bytes": len(analyze_bytes),
        "byte_identical": latest_bytes == analyze_bytes,
        "receipt_sha256_matches": sha256(scorer_path) == latest_commit["sha256"],
        "analyze_round26_modified": False,
    }
    followup_summary = None
    if FOLLOWUP_C23.exists():
        followup = read_json(FOLLOWUP_C23)
        assert followup["status"] == "VERIFIED_NINE_RAW_METHODS_PROJECTIONS_AND_29954_REPLAY"
        comparison = followup["frontier_comparison_29953_to_29954"]
        assert comparison["same_frontier_ids"] and comparison["all_coordinate_and_share_deltas_zero"]
        followup = followup["snapshot_29954_c23_capture"]
        followup_summary = {
            "snapshot_id": str(followup["snapshot"]["snapshot_id"]),
            "retrieval_start_utc": followup["retrieval_start_utc"],
            "retrieval_end_utc": followup["retrieval_end_utc"],
            "frontier_count": comparison["frontier_count"],
            "same_frontier_ids": comparison["same_frontier_ids"],
            "max_abs_x_delta": comparison["max_abs_x_delta"],
            "max_abs_y_delta_pp": comparison["max_abs_y_delta_pp"],
            "max_abs_geometric_share_delta_pp": comparison["max_abs_geometric_share_delta_pp"],
            "max_abs_payable_share_delta_pp": comparison["max_abs_payable_share_delta_pp"],
            "source_machine_audit": FOLLOWUP_C23.relative_to(ROOT).as_posix(),
        }

    result = {
        "status": "VERIFIED_CURRENT_SNAPSHOT_GEOMETRY_API_PAYOUT_AND_HISTORICAL_C4_REPLAY",
        "checked_utc": datetime.now(timezone.utc).isoformat(),
        "snapshot": snapshot,
        "capture": {
            "path": CURRENT_CAPTURE.relative_to(ROOT).as_posix(),
            "retrieval_start_utc": current_receipt["retrieval_start_utc"],
            "retrieval_end_utc": current_receipt["retrieval_end_utc"],
            "leaderboard_rows": current_receipt["pagination"]["leaderboard"]["rows"],
            "pareto_rows": current_receipt["pagination"]["pareto"]["rows"],
            "receipt_sha256": sha256(CURRENT_CAPTURE / "receipt.json"),
            "competition_response_sha256": next(f["sha256"] for f in current_receipt["raw_response_files"] if f["file"] == "competition.response.json"),
        },
        "rules": {"path": CURRENT_RULES.relative_to(ROOT).as_posix(),
                  "commit": current_rules_receipt["commit"],
                  "scorer_sha256": sha256(scorer_path),
                  "scorer_receipt_sha256": latest_commit["sha256"],
                  "rules_receipt_sha256": sha256(CURRENT_RULES / "receipt.json")},
        "api_replay": {key: current_audit[key] for key in [
            "status", "input_rows", "admitted_bounded_rows", "reconstructed_frontier",
            "frontier_ids_match", "raw_and_derived_hashes_match",
            "max_independent_api_error_pp", "max_independent_official_scorer_error_pp",
            "max_api_payable_error_fraction", "max_weights_by_hotkey_error_fraction",
            "sum_geometric_fraction", "sum_payable_fraction",
            "api_payable_competition_weight", "api_unpaid_competition_weight", "api_chain_accepted"]},
        "frontier": frontier,
        "frontier_summary": {"count": len(frontier),
                             "geometric_share_sum_pct": sum(x["geometric_share_pct"] for x in frontier),
                             "payable_share_sum_pct": sum(x["payable_share_pct"] for x in frontier),
                             "frontier_ids": [x["id"] for x in frontier],
                             "official_scorer_max_abs_error_pp": max(explicit_errors)},
        "anchor_658": {"x": anchor_x, "y_pct": anchor_y,
                       "current_api_admitted": bool((api_by_id["658"].get("admission") or {}).get("admitted")),
                       "current_api_on_frontier": bool((api_by_id["658"].get("score") or {}).get("on_frontier")),
                       "current_api_payable_share_pct": 100 * float((api_by_id["658"].get("score") or {}).get("payable_weight", 0.0))},
        "hypothetical_thresholds": {
            "scoring_basis": "Standalone geometric pool re-score against the captured 29953 frontier; assumes admitted, payment-eligible, independently keyed hypothetical point. Not measurement, probability, or realized payout.",
            "same_size_as_658": {"fixed_y_pct": anchor_y, "targets": same_size,
                                  "search_domain_x": [0.40, 0.48], "sample_step": 0.00002},
            "same_speed_as_658": {"fixed_x": anchor_x, "targets": same_speed,
                                   "search_domain_y_pct": [35.0, 35.60], "sample_step": 0.00005},
            "positive_share_dominator": {"id": "562", "x": x562, "y_pct": y562,
                                         "at_equal_x_share_pct": float(positive_x_at.get("share_pct", 0.0)),
                                         "immediately_faster_share_pct": float(positive_x_left["share_pct"]),
                                         "at_equal_y_share_pct": float(positive_y_at.get("share_pct", 0.0)),
                                         "immediately_smaller_y_share_pct": float(positive_y_left["share_pct"]),
                                         "x_immediately_faster_neighbors": [positive_x_left.get("predecessor"), positive_x_left.get("successor")],
                                         "y_immediately_smaller_neighbors": [positive_y_left.get("predecessor"), positive_y_left.get("successor")]},
            "neighbor_switch_at_659": {"id": "659", "probes": row659_probes},
        },
        "historical_c4": {"source": HISTORICAL_C4.relative_to(ROOT).as_posix(),
                          "source_snapshot_id": str(old_analysis["snapshot"]["snapshot_id"]),
                          "source_run_id": c4_run_id, "source_role": "discovery",
                          "source_block": 1, "source_kind": "HISTORICAL_DISCOVERY_NOT_NEW_CONFIRMATION",
                          "old_snapshot_audit_status": previous_audit["status"],
                          "old_snapshot_max_abs_error_pp": max(old_share_errors, default=0.0),
                          "rows": old_rows},
        "scorer_byte_comparison": scorer_comparison,
        "subsequent_official_capture": followup_summary,
        "limits": [
            "Snapshot freshness is the captured API value (unknown); exact deployed scorer configuration is not inferred from public source bytes.",
            "Geometric pool weights are not a wallet receipt; API payable weights are shown separately.",
            "#658 inversions are hypothetical geometry only and assume admission, payment eligibility, and an independent hotkey.",
            "C4 rows replay a previous discovery block; changing the scoring snapshot does not create new performance observations or independent confirmation.",
            "Raw public measurement coordinates are reported as historical measurements and are not substituted for official projected X/Y coordinates.",
        ],
    }
    assert scorer_comparison["receipt_sha256_matches"]
    write_json(OUTPUT / "score-audit.json", result)
    (OUTPUT / "score-audit-report.md").write_text(build_report(result), encoding="utf-8")
    print(json.dumps({"status": result["status"], "snapshot_id": snapshot["snapshot_id"],
                      "frontier_points": len(frontier),
                      "geometric_sum_pct": result["frontier_summary"]["geometric_share_sum_pct"],
                      "payable_sum_pct": result["frontier_summary"]["payable_share_sum_pct"],
                      "same_size_thresholds": same_size,
                      "same_speed_thresholds": same_speed,
                      "scorer_byte_identical": scorer_comparison["byte_identical"],
                      "historical_c4_max_error_pp": max(old_share_errors, default=0.0),
                      "output": str(OUTPUT)}, ensure_ascii=False))


if __name__ == "__main__":
    main()
