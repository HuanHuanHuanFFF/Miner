"""Collect a finished manual CI run and compute same-run A/B against the anchor.

Downloads the receipts artifact, hashes every file, then reports:
- official pinned-gate rows from summary.json (12 classes), and
- when the nested public-v2 entry was used, work-weighted class ratios.

The token stays in this process; only the original artifact and derived JSON
are written under research/deepseek-20261025/ci-runs/<run>/.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import subprocess
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
REPO = "HuanHuanHuanFFF/Miner"
RECEIPTS = ROOT / "competitions/floatlib/research/deepseek-20261025/ci-runs"
ANCHOR = "f01-d12-scalar-combined"


def token() -> str:
    p = subprocess.run(
        ["git", "credential", "fill"],
        input="protocol=https\nhost=github.com\n\n", text=True, capture_output=True, cwd=ROOT)
    fields = dict(x.split("=", 1) for x in p.stdout.splitlines() if "=" in x)
    tok = fields.get("password")
    if not tok:
        raise SystemExit("no stored GitHub credential")
    return tok


def gh(args, tok):
    env = os.environ.copy()
    env["GH_TOKEN"] = tok
    p = subprocess.run(["gh", *args], cwd=ROOT, env=env, capture_output=True, text=True, encoding="utf-8")
    if p.returncode:
        raise SystemExit(f"gh failed: {p.stderr[:400]}")
    return p.stdout


def sha256(b: bytes) -> str:
    return hashlib.sha256(b).hexdigest()


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--run", required=True)
    ap.add_argument("--anchor", default=ANCHOR)
    a = ap.parse_args()
    assert a.run.isdecimal()
    tok = token()

    meta = json.loads(gh(["run", "view", a.run, "--repo", REPO,
                          "--json", "databaseId,headSha,headBranch,event,status,conclusion,url"], tok))
    print(json.dumps(meta, ensure_ascii=False))
    if meta["status"] != "completed":
        raise SystemExit("run not terminal; do not collect yet")

    target = RECEIPTS / a.run
    if not (target / "ci-run.json").exists():
        target.mkdir(parents=True, exist_ok=True)
        (target / "ci-run.json").write_text(json.dumps(meta, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        arts = json.loads(gh(["api", f"repos/{REPO}/actions/runs/{a.run}/artifacts"], tok))
        (target / "artifacts.json").write_text(json.dumps(arts, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        art = next((x for x in arts["artifacts"] if x["name"] == f"floatlib-{a.run}-receipts" and not x["expired"]), None)
        if not art:
            raise SystemExit("no unexpired receipts artifact")
        stage = target / ("download-" + uuid.uuid4().hex)
        stage.mkdir()
        gh(["run", "download", a.run, "--repo", REPO, "--name", art["name"], "--dir", str(stage)], tok)
        files = {}
        for p in sorted(stage.rglob("*")):
            if p.is_file():
                files[p.relative_to(stage).as_posix()] = {"sha256": sha256(p.read_bytes()), "bytes": p.stat().st_size}
        (target / "original-artifact-hashes.json").write_text(
            json.dumps({"artifact": art, "directory": stage.name, "files": files}, ensure_ascii=False, indent=2) + "\n",
            encoding="utf-8")
        (target / "ci.log").write_text(gh(["run", "view", a.run, "--repo", REPO, "--log"], tok), encoding="utf-8")

    dirs = [p for p in target.glob("download-*") if p.is_dir()]
    stage = dirs[0]
    summary_path = stage / "summary.json"
    if not summary_path.exists():
        raise SystemExit("summary.json missing")
    summary = json.loads(summary_path.read_text(encoding="utf-8"))
    rows = {r["candidate"]: r for r in summary.get("results", [])}
    print("mode:", summary.get("scope", "")[:120])
    for name, r in rows.items():
        print(f"{name:34s} full={r.get('full_gate')} stmt={r.get('compile_pass')} "
              f"ratio={r.get('ratio')} p05={r.get('paired_gain_p05')} wall={r.get('wall_seconds')}")

    official = {n: r for n, r in rows.items() if r.get("full_gate") and r.get("classes")}
    if official and a.anchor in official:
        anchor_classes = official[a.anchor]["classes"]

        def op_totals(classes):
            out = {}
            for cell, row in classes.items():
                op = cell.split(":")[0]
                out[op] = out.get(op, 0.0) + row["submission_ns"]
                out["whole"] = out.get("whole", 0.0) + row["submission_ns"]
            return out

        base = op_totals(anchor_classes)
        report = {"run": int(a.run), "mode": "official-pinned-12class", "anchor": a.anchor, "candidates": {}}
        print(f"\nofficial pinned gate, anchor {a.anchor}: whole {base['whole']/1e6:.2f} ms")
        for name, r in official.items():
            t = op_totals(r["classes"])
            rel = {op: t[op] / base[op] for op in ("add", "mul", "sum", "bmm", "whole")}
            report["candidates"][name] = {"ratio_vs_shipped": r.get("ratio"), "p05": r.get("paired_gain_p05"),
                                          "ratio_vs_anchor": rel, "operation_ms": {k: v / 1e6 for k, v in t.items()}}
            print(f"{name:34s} whole/df5c={rel['whole']:.4f} bmm/df5c={rel['bmm']:.4f} "
                  f"add={rel['add']:.4f} mul={rel['mul']:.4f} sum={rel['sum']:.4f} p05={r.get('paired_gain_p05')}")
        (target / "deepseek-ab-result.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

    # Nested public-v2 (if present): work-weighted class totals.
    suite = next((p for p in stage.rglob("public-suite") if p.is_dir() and (p / "public-cell-work.json").exists()), None)
    if suite:
        work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))
        verdicts = {}
        for v in sorted(suite.glob("*-verdict.json")):
            d = json.loads(v.read_text(encoding="utf-8"))
            if d.get("mode") == "diagnostic-statement-only" or "classes" not in d:
                continue
            verdicts[d["submission"]] = d
        if a.anchor in verdicts:
            def totals(verdict):
                out = {"whole": 0.0}
                for cell, row in verdict["classes"].items():
                    op = cell.split(":")[0]
                    v = row["submission_ns"] * work[cell]
                    out[op] = out.get(op, 0.0) + v
                    out["whole"] += v
                return out

            anchor = totals(verdicts[a.anchor])
            preport = {"run": int(a.run), "mode": "public-v2-work-weighted", "anchor": a.anchor, "candidates": {}}
            print(f"\npublic-v2, anchor {a.anchor}: whole {anchor['whole']/1e6:.2f} ms")
            for name, d in verdicts.items():
                t = totals(d)
                rel = {op: t[op] / anchor[op] for op in ("add", "mul", "sum", "bmm", "whole")}
                preport["candidates"][name] = {"ratio_vs_shipped": d.get("ratio"),
                                               "ratio_vs_anchor": rel,
                                               "operation_ms": {k: v / 1e6 for k, v in t.items()}}
                print(f"{name:34s} whole/df5c={rel['whole']:.4f} bmm/df5c={rel['bmm']:.4f}")
            (target / "deepseek-public-v2-ab.json").write_text(json.dumps(preport, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"\nreceipt: {target}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
