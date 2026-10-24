"""Collect a finished manual CI run and compute same-run A/B against the anchor.

Downloads the receipts artifact, hashes every file, then reports, for each
candidate in the batch, the public-v2 work-weighted cost ratio against the
anchor candidate (f01-d12-scalar-combined) and against the shipped reference.

Only the process environment carries the token; nothing is printed or written
except the original artifact under research/deepseek-20261025/ci-runs/<run>/.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import subprocess
import sys
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
    if p.returncode:
        raise SystemExit("git credential fill failed")
    fields = dict(x.split("=", 1) for x in p.stdout.splitlines() if "=" in x)
    if not fields.get("password"):
        raise SystemExit("no stored GitHub credential")
    return fields["password"]


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
    if not dirs:
        raise SystemExit("no downloaded artifact directory")
    suite = next((p for p in dirs[0].rglob("public-suite") if p.is_dir() and (p / "public-cell-work.json").exists()), None)
    if suite is None:
        raise SystemExit("public-suite directory not found")
    work = json.loads((suite / "public-cell-work.json").read_text(encoding="utf-8"))
    work = work.get("cell_work", work)

    verdicts = {}
    for v in sorted(suite.glob("*-verdict.json")):
        d = json.loads(v.read_text(encoding="utf-8"))
        if d.get("mode") == "diagnostic" or "classes" not in d:
            continue
        verdicts[d["submission"]] = d
    if a.anchor not in verdicts:
        raise SystemExit(f"anchor {a.anchor} missing: {sorted(verdicts)}")

    def totals(verdict):
        out = {"whole": 0.0}
        for cell, row in verdict["classes"].items():
            op = cell.split(":")[0]
            v = row["submission_ns"] * work[cell]
            out[op] = out.get(op, 0.0) + v
            out["whole"] += v
        return out

    anchor = totals(verdicts[a.anchor])
    report = {"run": int(a.run), "source_commit": meta["headSha"], "branch": meta["headBranch"],
              "anchor": a.anchor, "cells": len(work), "candidates": {}}
    print(f"\nanchor {a.anchor}: whole {anchor['whole']/1e6:.2f} ms")
    for name, d in verdicts.items():
        t = totals(d)
        rel = {op: t[op] / anchor[op] for op in ("add", "mul", "sum", "bmm", "whole")}
        report["candidates"][name] = {
            "kernel_sha256": d.get("submission_sha256") or d.get("candidate_sha256"),
            "verdict_ratio_vs_shipped": d.get("ratio"),
            "operation_ms": {k: v / 1e6 for k, v in t.items()},
            "ratio_vs_anchor": rel,
        }
        print(f"{name:34s} whole/df5c={rel['whole']:.4f} bmm/df5c={rel['bmm']:.4f} "
              f"add={rel['add']:.4f} mul={rel['mul']:.4f} sum={rel['sum']:.4f}")

    (target / "deepseek-ab-result.json").write_text(
        json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"\nreceipt: {target}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
