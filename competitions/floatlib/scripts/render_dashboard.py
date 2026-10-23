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
    run_count = len(set(view["full_gate_runs"]))
    labels = policy["candidate_labels_by_operation"]
    receipt = champion["receipts"]
    lines = [
        "# FloatLib 冲冠看板", "",
        f"冠军核对：[{checked} 北京时间]({receipt})｜各项均以现任完整包冠军为 1.00×，耗时越低越好。", "",
        "| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时 | 验证 |",
        "| --- | --- | --- | ---: | --- |",
    ]
    for op, name in (("add", "加法 add"), ("mul", "乘法 mul"), ("sum", "求和 sum"), ("bmm", "矩阵乘法 bmm")):
        value = champion["candidate_over_champion_time_by_operation"][op]
        if value == "UNKNOWN":
            display = policy["missing_value"]
        else:
            assert type(value) in (int, float) and math.isfinite(value) and value > 0
            display = f"**约 {value:.1f}×**"
        champion_link = f"[#{number}](https://conjectures.io/v1/competitions/floatlib/submissions/{number})" if op == "add" else f"#{number}"
        candidate_link = f"[{labels[op]}]({source.relative_to(ROOT).as_posix()})"
        lines.append(f"| {name} | {champion_link} | {candidate_link} | {display} | 完整通过{run_count}次 |")
    lines += ["",
              f"**结论：尚无取代#{number}的已验方案。** [数据](competitions/floatlib/candidates/f01-d7-research/multiplier-comparison.json)", ""]
    (ROOT / "dashboard.md").write_text("\n".join(lines), encoding="utf-8")


if __name__ == "__main__":
    main()
