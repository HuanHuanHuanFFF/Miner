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
    label = {
        "f01-r8-combined-result-guard": "单遍求和＋矩阵优化＋结果守卫组合",
        "f01-d7-direct-singlepass-proof2": "单遍求和＋直接点积完整包",
    }.get(view["candidate"], view["candidate"])
    lines = [
        "# FloatLib 冲冠看板", "",
        f"现任冠军 [#{number}](https://conjectures.io/v1/competitions/floatlib/submissions/{number})｜{checked}核对。", "",
        f"我方首选：[{label}]({source.relative_to(ROOT).as_posix()})。", "",
        "| 运算 | 冠军耗时 | 我方耗时（冠军倍数） |",
        "| --- | ---: | ---: |",
    ]
    for op, name in (("add", "加法 add"), ("mul", "乘法 mul"), ("sum", "求和 sum"), ("bmm", "矩阵乘法 bmm")):
        value = champion["candidate_over_champion_time_by_operation"][op]
        if value == "UNKNOWN":
            display = "—"
        else:
            assert type(value) in (int, float) and math.isfinite(value) and value > 0
            display = f"{value:.2f}×"
        lines.append(f"| {name} | 1.00× | {display} |")
    lines += ["", "耗时倍数＝我方耗时÷冠军耗时，越小越快；“—”表示暂无同口径数据。", "",
              f"**结论：尚无取代#{number}的已验方案。** [数据](competitions/floatlib/candidates/f01-d7-research/multiplier-comparison.json)", ""]
    (ROOT / "dashboard.md").write_text("\n".join(lines), encoding="utf-8")


if __name__ == "__main__":
    main()
