"""Build a source-bound catalogue from saved FloatLib candidates and CI receipts."""
import hashlib
import json
from pathlib import Path
import re
from collections import Counter, defaultdict

ROOT = Path(__file__).resolve().parents[3]
TRACK = ROOT / "competitions/floatlib"
OUT = TRACK / "research/results"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def rel(path):
    return path.relative_to(ROOT).as_posix()


def main():
    by_sha = defaultdict(list)
    runs = TRACK / "candidates/f01-mul-log2-proof1/ci-runs"
    for path in sorted(runs.glob("[0-9]*/download-*/*-verdict.json")):
        candidate = path.name.removesuffix("-verdict.json")
        manifest_path = path.with_name(candidate + "-manifest.json")
        if not manifest_path.exists():
            continue
        manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
        source_sha = manifest.get("candidate_sha256")
        if not source_sha:
            continue
        verdict = json.loads(path.read_text(encoding="utf-8"))
        by_sha[source_sha].append({
            "run": path.parent.parent.name, "candidate": candidate,
            "mode": verdict.get("mode"), "stage": verdict.get("stage"),
            "passed": verdict.get("passed"), "reason": verdict.get("reason"),
            "classes": len(verdict.get("classes", {})), "rounds": len(verdict.get("rounds", [])),
            "verdict": rel(path), "verdict_sha256": sha(path.read_bytes()),
            "source_manifest": rel(manifest_path), "source_manifest_sha256": sha(manifest_path.read_bytes()),
        })
    items = []
    for source in sorted((TRACK / "candidates").glob("*/Kernel.lean")):
        data = source.read_bytes()
        source_sha = sha(data)
        receipts = by_sha[source_sha]
        full = [r for r in receipts if r["mode"] == "gate" and r["stage"] == "score"
                and r["passed"] is True and r["classes"] == 12 and r["rounds"] == 25]
        statement = [r for r in receipts if r["mode"] == "diagnostic-statement-only"
                     and r["stage"] == "statement" and r["passed"] is True]
        failed = [r for r in receipts if r["passed"] is False]
        state = "FULL_GATE_PASS" if full else "STATEMENT_PASS" if statement else "FAILED" if failed else "NO_MATCHED_RECEIPT"
        mp = source.with_name("manifest.json")
        metadata = json.loads(mp.read_text(encoding="utf-8")) if mp.exists() else {}
        declarations = []
        for line, text in enumerate(data.decode("utf-8-sig").splitlines(), 1):
            match = re.match(r"\s*(?:private\s+)?theorem\s+(\S+)", text)
            if match:
                declarations.append({"name_as_written": match[1], "line": line})
        items.append({"candidate": source.parent.name, "source": rel(source),
                      "sha256": source_sha, "bytes": len(data), "evidence_state": state,
                      "full_gate_runs": sorted(set(r["run"] for r in full)),
                      "statement_runs": sorted(set(r["run"] for r in statement)),
                      "mechanism": metadata.get("mechanism", "UNKNOWN"),
                      "manifest_historical_status": metadata.get("proof_status", "UNKNOWN"),
                      "theorems": declarations, "receipts": receipts})
    OUT.mkdir(parents=True, exist_ok=True)
    counts = dict(Counter(i["evidence_state"] for i in items))
    payload = {"as_of": "2026-10-22", "candidate_count": len(items), "counts": counts,
               "method": "Saved top-level verdicts matched by archived candidate_manifest SHA256; aliases with identical source bytes share receipts. This catalogue does not rerun Lean or replace the complete gate audit.",
               "items": items}
    (OUT / "candidate-catalog.json").write_text(json.dumps(payload, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    lines = ["# 候选与证明目录", "", "[返回数学结论](../RESULTS.md)。按源码 SHA-256 关联已保存的实际 CI 回执；同字节别名共享证据。完整通过、仅编译、失败及无匹配回执分列。这里不重新运行 Lean。", "", 
             f"共 {len(items)} 份候选。机器可读的定理行号、源码哈希与全部成功/失败回执见 [candidate-catalog.json](candidate-catalog.json)。", "",
             "`无匹配回执`表示本目录没有找到对应源码的回执，不表示数学不成立。完整通过仍须结合原回执中的内核、公理和计时审计。", "",
             "| 候选 | 当前证据 | 完整通过次数 | 原始回执 |", "|---|---|---:|---|"]
    labels = {"FULL_GATE_PASS": "完整通过", "STATEMENT_PASS": "仅编译通过", "FAILED": "已失败", "NO_MATCHED_RECEIPT": "无匹配回执"}
    for i in items:
        evidence = i["receipts"][-1] if i["receipts"] else None
        if i["full_gate_runs"]:
            evidence = next(r for r in reversed(i["receipts"]) if r["run"] == i["full_gate_runs"][-1] and r["passed"])
        link = "—" if evidence is None else f"[{evidence['run']}](../../{evidence['verdict'].split('competitions/floatlib/',1)[1]})"
        lines.append(f"| [{i['candidate']}](../../candidates/{i['candidate']}/Kernel.lean) | {labels[i['evidence_state']]} | {len(i['full_gate_runs'])} | {link} |")
    (OUT / "CANDIDATES.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(json.dumps({"candidates": len(items), "counts": counts}))


if __name__ == "__main__":
    main()
