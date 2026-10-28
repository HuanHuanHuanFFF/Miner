"""Render the four-operation dashboard using champion-relative time only."""
from datetime import datetime, timedelta, timezone
import hashlib
import json
import math
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "competitions/floatlib/candidates/f01-d7-research"


def load_development_forecast(entry, result, champion):
    path = ROOT / entry["evidence"]
    assert hashlib.sha256(path.read_bytes()).hexdigest() == entry["evidence_sha256"]
    forecast = json.loads(path.read_bytes())
    assert forecast["status"] == "INFERRED"
    assert forecast["kernel_sha256"] == entry["kernel_sha256"]
    assert hashlib.sha256((ROOT / forecast["kernel"]).read_bytes()).hexdigest() == forecast["kernel_sha256"]
    assert forecast["baseline_kernel_sha256"] == result["kernel_sha256"]
    assert forecast["champion_submission"] == result["champion"]
    assert forecast["champion_digest"] == champion["digest"]
    for key in ("baseline_official_comparison", "public_discovery"):
        evidence = ROOT / forecast[key]
        assert hashlib.sha256(evidence.read_bytes()).hexdigest() == forecast[key + "_sha256"]
    discovery = json.loads((ROOT / forecast["public_discovery"]).read_bytes())
    assert discovery["full_gate_both"] and discovery["paired_rounds_each"] == 25
    assert discovery["sha256"] == forecast["kernel_sha256"]
    return forecast


def render_official(view, state):
    entry = view.get("official_submission")
    if not entry:
        return False
    path = ROOT / entry["evidence"]
    assert hashlib.sha256(path.read_bytes()).hexdigest() == entry["evidence_sha256"]
    result = json.loads(path.read_bytes())
    assert result["kernel_sha256"] == state["kernel_sha256"] == view["kernel_sha256"]
    assert hashlib.sha256((ROOT / state["kernel"]).read_bytes()).hexdigest() == result["kernel_sha256"]
    assert result["passed"] and result["state"] == "accepted" and result["same_champion_digest"]
    receipts = json.loads((path.parent / "receipts.json").read_bytes())
    for name in ("status", "report", "leaderboard"):
        assert hashlib.sha256((path.parent / (name + ".raw")).read_bytes()).hexdigest() == receipts[name]["sha256"]
    envelope = json.loads((path.parent / "report.raw").read_bytes())
    report = envelope["report"]
    report = json.loads(report) if isinstance(report, str) else report
    assert report["passed"] and report["ratio"] == result["official_whole_ratio"]
    assert report["mode"] == "gate" and report["stage"] == "score"
    assert report["verifier_fingerprint"] == report["verifier_fingerprint_end"]
    assert report["champion_sha256"] == view["champion"]["digest"]
    champion, submission = result["champion"], result["submission"]
    checked = datetime.fromisoformat(result["checked_at_utc"]).astimezone(timezone(timedelta(hours=8))).strftime("%Y-%m-%d %H:%M")
    labels = view["dashboard_policy"]["candidate_labels_by_operation"]
    development = view["dashboard_policy"].get("development_forecast")
    if development:
        forecast = load_development_forecast(development, result, view["champion"])
        names = {"add": "加法 add", "mul": "乘法 mul", "sum": "求和 sum", "bmm": "矩阵乘法 bmm"}
        dev_labels = {"add": "原生冷尾加法", "mul": "原生冷尾乘法", "sum": "保留单遍求和", "bmm": "保留B2双列"}
        lines = ["# FloatLib 冲冠看板", "",
                 f"冠军核对：[{checked} 北京时间]({entry['evidence']})；冠军为 **1.00×**，耗时越低越好。", "",
                 "| 运算 | 现任冠军 | 当前开发 | 开发／冠军（预估） | 保留版／冠军（官方） |",
                 "| --- | --- | --- | ---: | ---: |"]
        for op, name in names.items():
            values = forecast["operations"][op]
            low, high = values["ratio_min"], values["ratio_max"]
            assert all(type(x) in (int, float) and math.isfinite(x) and x > 0 for x in (low, high)) and low <= high
            base = result["operations"][op]
            candidate = f"[{dev_labels[op]}]({forecast['kernel']})"
            progress = view["dashboard_policy"].get("research_progress_by_operation", {}).get(op)
            if progress:
                assert hashlib.sha256((ROOT / progress["evidence"]).read_bytes()).hexdigest() == progress["evidence_sha256"]
                candidate += f"；[{progress['text']}]({progress['evidence']})"
            lines.append(f"| {name} | #{champion} | {candidate} | **{low:.2f}–{high:.2f}×** | {base['official_group_ratio_min']:.2f}–{base['official_group_ratio_max']:.2f}× |")
        lines += ["", f"整包：保留版官方 **{result['official_whole_ratio']:.2f}×**；当前开发预估 **{forecast['whole']['ratio_point']:.2f}×**。[依据]({development['evidence']})", "",
                  f"**结论：仍不能取代#{champion}；开发组合完整验证通过，稳定性门槛未过，保留B2。**", ""]
        (ROOT / "dashboard.md").write_text("\n".join(lines), encoding="utf-8", newline="\n")
        return True
    lines = ["# FloatLib 冲冠看板", "",
             f"官方核对：[{checked} 北京时间]({entry['evidence']})｜冠军为1.00×；四项显示官方各输入组的耗时比范围，越低越好。", "",
             "| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时（官方各组） | 验证 |",
             "| --- | --- | --- | ---: | --- |"]
    for op, name in (("add", "加法 add"), ("mul", "乘法 mul"), ("sum", "求和 sum"), ("bmm", "矩阵乘法 bmm")):
        ratios = [cell["ratio"] for key, cell in report["classes"].items() if key.startswith(op + ":")]
        assert ratios and all(math.isfinite(value) and value > 0 for value in ratios)
        official = result["operations"][op]
        assert min(ratios) == official["official_group_ratio_min"] and max(ratios) == official["official_group_ratio_max"]
        validation = f"[#{submission} 官方通过](https://conjectures.io/v1/competitions/floatlib/submissions/{submission})"
        progress = view["dashboard_policy"].get("research_progress_by_operation", {}).get(op)
        if progress:
            progress_path = ROOT / progress["evidence"]
            assert hashlib.sha256(progress_path.read_bytes()).hexdigest() == progress["evidence_sha256"]
            validation += f"；[{progress['text']}]({progress['evidence']})"
        lines.append(f"| {name} | #{champion} | [{labels[op]}]({state['kernel']}) | **{min(ratios):.2f}–{max(ratios):.2f}×** | {validation} |")
    ratio = result["official_whole_ratio"]
    lines += ["", f"整包官方耗时：冠军的 **{ratio:.2f}×**。", "",
              f"**结论：官方验证通过，当前第{result['rank']}；尚不能取代#{champion}，主要差距仍在矩阵乘法。**", ""]
    (ROOT / "dashboard.md").write_text("\n".join(lines), encoding="utf-8", newline="\n")
    return True


def main():
    view = json.loads((DATA / "multiplier-comparison.json").read_bytes())
    state = json.loads((ROOT / "competitions/floatlib/coordination/development-status.json").read_bytes())
    if render_official(view, state):
        return
    snapshot = json.loads((DATA / "current-official-snapshot.json").read_bytes())
    source = ROOT / state["kernel"]
    assert hashlib.sha256(source.read_bytes()).hexdigest() == view["kernel_sha256"] == state["kernel_sha256"]
    champion = view["champion"]
    number = champion["submission"]
    assert number == snapshot["champion"]
    assert view["dashboard_policy"]["baseline"] == "current_champion"
    checked = datetime.fromisoformat(snapshot["queried_at_utc"]).astimezone(timezone(timedelta(hours=8))).strftime("%Y-%m-%d %H:%M")
    assert champion["official_normalized_self_time"] == 1.0
    policy = view["dashboard_policy"]
    assert policy["layout"] == "legacy_four_operations"
    progress = policy.get("research_progress_by_operation", {})
    for item in progress.values():
        assert hashlib.sha256((ROOT / item["evidence"]).read_bytes()).hexdigest() == item["evidence_sha256"]
    run_count = len(set(view["full_gate_runs"]))
    labels = policy["candidate_labels_by_operation"]
    receipt = champion["receipts"]
    estimate = view.get("champion_time_estimate")
    if estimate:
        assert estimate["status"] == "INFERRED" and estimate["champion_submission"] == number
        assert estimate["champion_digest"] == champion["digest"] and estimate["kernel_sha256"] == view["kernel_sha256"]
        assert hashlib.sha256((ROOT / estimate["evidence"]).read_bytes()).hexdigest() == estimate["evidence_sha256"]
    direct_times = champion["candidate_over_champion_time_by_operation"]
    research = view.get("dashboard_research_candidate")
    if research:
        path = ROOT / research["evidence"]
        assert hashlib.sha256(path.read_bytes()).hexdigest() == research["evidence_sha256"]
        measured = json.loads(path.read_bytes())
        assert measured["status"] == "INFERRED" and measured["champion_submission"] == number
        assert measured["champion_digest"] == champion["digest"]
        assert measured["candidate"] == research["candidate"] and measured["kernel_sha256"] == research["kernel_sha256"]
        actual = {r["run"] for r in json.loads((ROOT / view["public_results"]).read_bytes())["records"]
                  if r.get("full_gate") and r["kernel_sha256"] == research["kernel_sha256"]}
        frozen_runs = set(research["full_gate_runs"])
        assert frozen_runs == set(measured["full_gate_runs"]) and frozen_runs <= actual and len(frozen_runs) >= 3
        assert measured["whole"]["ratio_median"] < estimate["whole"]["ratio_median"]
        source = ROOT / research["kernel"]
        assert hashlib.sha256(source.read_bytes()).hexdigest() == research["kernel_sha256"]
        estimate = dict(measured, evidence=research["evidence"])
        # Later same-source controls stay in the raw index; the displayed model
        # remains bound to its frozen validation groups and original values.
        run_count = len(frozen_runs)
        labels = dict(labels, bmm=research["bmm_label"])
        direct_times = {op: "UNKNOWN" for op in ("add", "mul", "sum", "bmm")}
    lines = [
        "# FloatLib 冲冠看板", "",
        f"冠军核对：[{checked} 北京时间]({receipt})｜各项均以现任完整包冠军为 1.00×，耗时越低越好。", "",
        "| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时（预估） | 验证 |",
        "| --- | --- | --- | ---: | --- |",
    ]
    for op, name in (("add", "加法 add"), ("mul", "乘法 mul"), ("sum", "求和 sum"), ("bmm", "矩阵乘法 bmm")):
        value = direct_times[op]
        if value == "UNKNOWN" and policy.get("use_estimates_when_direct_unknown") and estimate:
            value = estimate["operations"][op]["ratio_median"]
        if value == "UNKNOWN":
            display = policy["missing_value"]
        else:
            assert type(value) in (int, float) and math.isfinite(value) and value > 0
            display = f"**约 {value:.2f}×**"
        champion_link = f"[#{number}](https://conjectures.io/v1/competitions/floatlib/submissions/{number})" if op == "add" else f"#{number}"
        candidate_link = f"[{labels[op]}]({source.relative_to(ROOT).as_posix()})"
        validation = f"完整通过{run_count}次"
        if op in progress:
            item = progress[op]
            validation += f"；[{item['text']}]({item['evidence']})"
        lines.append(f"| {name} | {champion_link} | {candidate_link} | {display} | {validation} |")
    if estimate and policy.get("use_estimates_when_direct_unknown"):
        whole = estimate["whole"]["ratio_median"]
        worst = max(estimate["operations"], key=lambda op: estimate["operations"][op]["ratio_median"])
        names = {"add": "加法", "mul": "乘法", "sum": "求和", "bmm": "矩阵乘法"}
        gap = estimate["operations"][worst]["ratio_median"]
        result = f"预估暂不能取代#{number}" if whole > 0.97 else f"预估达到耗时门槛，仍需与#{number}同场验收"
        lines += ["", f"整包预估耗时：冠军的 **约 {whole:.2f}×**。",
                  "", f"**结论：{result}；主要差距在{names[worst]}（约{gap:.2f}倍耗时）。** [计算依据]({estimate['evidence']})", ""]
    else:
        lines += ["", f"**结论：尚无取代#{number}的已验方案。** [数据](competitions/floatlib/candidates/f01-d7-research/multiplier-comparison.json)", ""]
    (ROOT / "dashboard.md").write_text("\n".join(lines), encoding="utf-8", newline="\n")


if __name__ == "__main__":
    main()
