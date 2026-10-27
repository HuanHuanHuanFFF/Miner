"""Render the four-operation dashboard using champion-relative time only."""
from datetime import datetime, timedelta, timezone
import hashlib
import json
import math
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "competitions/floatlib/candidates/f01-d7-research"


def main():
    view = json.loads((DATA / "multiplier-comparison.json").read_bytes())
    state = json.loads((ROOT / "competitions/floatlib/coordination/development-status.json").read_bytes())
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
    (ROOT / "dashboard.md").write_text("\n".join(lines), encoding="utf-8")


if __name__ == "__main__":
    main()
