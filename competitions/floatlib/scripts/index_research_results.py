"""Build a source-bound catalogue from saved FloatLib candidates and CI receipts."""
import hashlib
import json
from datetime import datetime, timezone
from pathlib import Path
import re
import subprocess
from collections import Counter, defaultdict

ROOT = Path(__file__).resolve().parents[3]
TRACK = ROOT / "competitions/floatlib"
OUT = TRACK / "research/results"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def rel(path):
    return path.relative_to(ROOT).as_posix()


def main():
    index_blobs = {}
    for line in subprocess.check_output(['git', 'ls-files', '--stage', '--', 'competitions/floatlib/candidates/*/Kernel.lean'], cwd=ROOT, text=True).splitlines():
        metadata, path = line.split('\t', 1)
        index_blobs[path] = metadata.split()[1]
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
    # Current official public-suite gates have a separate original checkout and
    # bind each nested source through the frozen requested plan plus input bytes.
    for path in sorted(runs.glob("[0-9]*/download-*/diagnostics/f01-d[67]-public-suite/public-suite/*-verdict.json")):
        candidate = path.name.removesuffix("-verdict.json")
        plan_path = path.parent / "requested-plan.json"
        source_path = path.parent / "inputs" / candidate / "Kernel.lean"
        if not plan_path.exists() or not source_path.exists():
            continue
        plan = json.loads(plan_path.read_bytes())
        requested = next((r for r in plan["candidates"] if r["candidate"] == candidate), None)
        assert requested is not None, (candidate, plan_path)
        expected = requested["sha256"]
        source_sha = sha(source_path.read_bytes())
        assert source_sha == expected, source_path
        verdict = json.loads(path.read_bytes())
        by_sha[source_sha].append({
            "run": path.parents[4].name, "candidate": candidate,
            "mode": verdict.get("mode"), "stage": verdict.get("stage"),
            "passed": verdict.get("passed"), "reason": verdict.get("reason"),
            "classes": len(verdict.get("classes", {})), "rounds": len(verdict.get("rounds", [])),
            "suite": verdict.get("suite", {}), "protocol": "current official public-v2",
            "official_commit": plan["official_commit"],
            "requested_validation_mode": requested.get("validation_mode", "full-gate"),
            "verdict": rel(path), "verdict_sha256": sha(path.read_bytes()),
            "source_manifest": rel(plan_path), "source_manifest_sha256": sha(plan_path.read_bytes()),
        })
    items = []
    for source in sorted((TRACK / "candidates").glob("*/Kernel.lean")):
        data = source.read_bytes()
        source_sha = sha(data)
        blob = index_blobs.get(rel(source))
        git_raw = b'blob ' + str(len(data)).encode() + b'\0' + data
        git_digest = hashlib.sha1(git_raw).hexdigest() if blob and len(blob) == 40 else hashlib.sha256(git_raw).hexdigest()
        source_scope = 'GIT_EXACT_BYTES' if blob == git_digest else 'WORKING_BYTES_DIFFER_FROM_INDEX' if blob else 'LOCAL_ONLY'
        receipts = by_sha[source_sha]
        full = [r for r in receipts if r["mode"] == "gate" and r["stage"] == "score"
                and r["passed"] is True and r["rounds"] == 25
                and r.get("requested_validation_mode", "full-gate") == "full-gate"
                and (r["classes"] == 12 or (r["classes"] == 26
                     and r.get("suite", {}).get("version") == "public-v2"
                     and r["suite"].get("sha256") == "a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a"))]
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
                      "source_scope": source_scope, "git_index_blob": blob,
                      "sha256": source_sha, "bytes": len(data), "evidence_state": state,
                      "full_gate_runs": sorted(set(r["run"] for r in full)),
                      "statement_runs": sorted(set(r["run"] for r in statement)),
                      "mechanism": metadata.get("mechanism", "UNKNOWN"),
                      "manifest_historical_status": metadata.get("proof_status", "UNKNOWN"),
                      "theorems": declarations, "receipts": receipts})
    OUT.mkdir(parents=True, exist_ok=True)
    counts = dict(Counter(i["evidence_state"] for i in items))
    payload = {"as_of": datetime.now(timezone.utc).isoformat(), "candidate_count": len(items), "counts": counts,
               "method": "Legacy verdicts bind archived manifest SHA256; nested current-official public-v2 gates bind the exact requested plan and saved input bytes. Aliases with identical source bytes share receipts. Protocol/suite fields stay separate; this catalogue does not rerun Lean or replace complete gate audit or private champion evaluation.",
               "items": items}
    (OUT / "candidate-catalog.json").write_text(json.dumps(payload, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    lines = ["# 候选与证明目录", "", "[返回数学结论](../RESULTS.md)。按源码 SHA-256 关联已保存的实际 CI 回执；同字节别名共享证据。完整通过、仅编译、失败及无匹配回执分列。这里不重新运行 Lean。", "",
             f"共 {len(items)} 份候选。机器可读的定理行号、源码哈希与全部成功/失败回执见 [candidate-catalog.json](candidate-catalog.json)。", "",
             "`无匹配回执`表示本目录没有找到对应源码的回执，不表示数学不成立。完整通过仍须结合原回执中的内核、公理和计时审计。仅本地或尚未冻结的源码只列名称；JSON保留路径、字节范围与SHA。", "",
             "| 候选 | 当前证据 | 完整通过次数 | 原始回执 |", "|---|---|---:|---|"]
    labels = {"FULL_GATE_PASS": "完整通过", "STATEMENT_PASS": "仅编译通过", "FAILED": "已失败", "NO_MATCHED_RECEIPT": "无匹配回执"}
    for i in items:
        evidence = i["receipts"][-1] if i["receipts"] else None
        if i["full_gate_runs"]:
            evidence = next(r for r in reversed(i["receipts"]) if r["run"] == i["full_gate_runs"][-1] and r["passed"])
        link = "—" if evidence is None else f"[{evidence['run']}](../../{evidence['verdict'].split('competitions/floatlib/',1)[1]})"
        name = f"[{i['candidate']}](../../candidates/{i['candidate']}/Kernel.lean)" if i['source_scope'] == 'GIT_EXACT_BYTES' else i['candidate'] + '（本地字节）'
        lines.append(f"| {name} | {labels[i['evidence_state']]} | {len(i['full_gate_runs'])} | {link} |")
    (OUT / "CANDIDATES.md").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(json.dumps({"candidates": len(items), "counts": counts}))


if __name__ == "__main__":
    main()
