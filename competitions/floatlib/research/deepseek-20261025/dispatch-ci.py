"""Dispatch the authorized manual FloatLib workflow from the DeepSeek branch.

The shared scripts/github-ci.py hardcodes codex/multi-track-floatlib. This
wrapper keeps the same safety checks but binds the run to the actual branch and
appends a DeepSeek receipt under research/deepseek-20261025/ci-runs/.

Credentials: read from the local Git credential service into this process only.
They are never written to disk or printed.
"""
from __future__ import annotations

import argparse
import datetime as dt
import hashlib
import json
import os
import re
import subprocess
import sys
import time
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]  # repo root
TRACK = ROOT / "competitions/floatlib"
REPO = "HuanHuanHuanFFF/Miner"
BRANCH = "huan/dhs-deepseek"
WORKFLOW = "floatlib-validate.yml"
RECEIPTS = TRACK / "research/deepseek-20261025/ci-runs"
CANDIDATE_RE = re.compile(r"(?:baseline|f01-[a-z0-9-]+)(?:,(?:baseline|f01-[a-z0-9-]+))*")


def run(cmd, **kw):
    return subprocess.run(cmd, check=True, capture_output=True, text=True, cwd=ROOT, **kw)


def token() -> str:
    p = subprocess.run(
        ["git", "credential", "fill"],
        input="protocol=https\nhost=github.com\n\n",
        text=True,
        capture_output=True,
        cwd=ROOT,
    )
    if p.returncode:
        raise SystemExit("git credential fill failed")
    fields = dict(x.split("=", 1) for x in p.stdout.splitlines() if "=" in x)
    if not fields.get("password"):
        raise SystemExit("no stored GitHub credential")
    return fields["password"]


def gh(args, tok):
    env = os.environ.copy()
    env["GH_TOKEN"] = tok
    env.pop("GITHUB_TOKEN", None)
    p = subprocess.run(["gh", *args], cwd=ROOT, env=env, capture_output=True, text=True, encoding="utf-8")
    if p.returncode:
        raise SystemExit(f"gh {' '.join(args[:2])} failed: {p.stderr[:400]}")
    return p.stdout


def sha256(b: bytes) -> str:
    return hashlib.sha256(b).hexdigest()


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--candidates", required=True)
    ap.add_argument("--seed", required=True)
    ap.add_argument("--workflow", default=WORKFLOW)
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()

    assert CANDIDATE_RE.fullmatch(a.candidates), a.candidates
    assert a.seed.isdecimal() and 0 <= int(a.seed) < 2**32
    assert a.workflow in {"floatlib-validate.yml", "deflate-baseline.yml"}

    branch = run(["git", "rev-parse", "--abbrev-ref", "HEAD"]).stdout.strip()
    assert branch == BRANCH, f"branch {branch} != {BRANCH}"
    status = run(["git", "status", "--porcelain=v1"]).stdout.splitlines()
    allowed = (
        "?? competitions/floatlib/research/deepseek-20261025/ci-runs/",
        "?? competitions/floatlib/evidence/",
    )
    offending = [line for line in status if not line.startswith(allowed)]
    assert not offending, "worktree not clean:\n" + "\n".join(offending)
    commit = run(["git", "rev-parse", "HEAD"]).stdout.strip()

    tok = token()
    repo = json.loads(gh(["api", f"repos/{REPO}"], tok))
    assert repo["private"] is False
    repo_bytes = json.dumps(repo, ensure_ascii=False).encode()

    remote = json.loads(gh(["api", f"repos/{REPO}/commits/{branch}"], tok))
    assert remote["sha"] == commit, f"remote {remote['sha']} != local {commit}; push first"

    frozen = {}
    paths = [
        "competitions/floatlib/pins.json",
        f".github/workflows/{a.workflow}",
        "competitions/floatlib/scripts/ci-prepare.sh",
        "competitions/floatlib/scripts/ci-setup.sh",
        "competitions/floatlib/scripts/ci-validate.sh",
        "competitions/floatlib/scripts/run-gates.py",
    ]
    for name in a.candidates.split(","):
        if name != "baseline":
            paths.append(f"competitions/floatlib/candidates/{name}/Kernel.lean")
            paths.append(f"competitions/floatlib/candidates/{name}/manifest.json")
    for path in paths:
        blob = subprocess.check_output(["git", "show", f"{commit}:{path}"], cwd=ROOT)
        disk = (ROOT / path).read_bytes()
        assert blob == disk, f"{path} differs between HEAD and worktree"
        frozen[path] = sha256(blob)

    listing = [
        "run", "list", "--repo", REPO, "--branch", branch,
        "--workflow", a.workflow, "--limit", "20",
        "--json", "databaseId,headSha,status,conclusion,createdAt,url",
    ]
    rows = json.loads(gh(listing, tok))
    active = [r for r in rows if r["status"] != "completed"]
    if active:
        raise SystemExit(f"active run already in flight: {active[0]['databaseId']} {active[0]['url']}")
    seen = {r["databaseId"] for r in rows}

    inputs = {"candidates": a.candidates, "seed": a.seed, "allow_private": "false"}
    if a.workflow == "deflate-baseline.yml":
        inputs["competition"] = "floatlib"
    body = {"ref": branch, "inputs": inputs}
    stamp = dt.datetime.now(dt.timezone.utc).strftime("%Y%m%dT%H%M%SZ")
    receipt = RECEIPTS / f"dispatch-{stamp}-{uuid.uuid4().hex[:8]}"
    base = {
        "prepared_at_utc": dt.datetime.now(dt.timezone.utc).isoformat(),
        "branch": branch,
        "source_commit": commit,
        "workflow": a.workflow,
        "inputs": inputs,
        "frozen_file_sha256": frozen,
        "repository_response_sha256": sha256(repo_bytes),
        "request_sha256": sha256(json.dumps(body, sort_keys=True).encode()),
    }
    print(json.dumps({"prepared": base, "active_runs": 0}, ensure_ascii=False, indent=1))

    if a.dry_run:
        base["state"] = "PREFLIGHT_PASS_DRY_RUN"
        receipt.mkdir(parents=True, exist_ok=True)
        (receipt / "dispatch.json").write_text(json.dumps(base, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(f"dry run receipt: {receipt}")
        return 0

    receipt.mkdir(parents=True, exist_ok=False)
    req = receipt / "request.json"
    req.write_text(json.dumps(body, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    (receipt / "dispatch.json").write_text(
        json.dumps({**base, "state": "REQUEST_PREPARED"}, ensure_ascii=False, indent=2) + "\n", encoding="utf-8"
    )
    gh(
        ["api", "--method", "POST", f"repos/{REPO}/actions/workflows/{a.workflow}/dispatches",
         "--input", str(req)],
        tok,
    )
    (receipt / "dispatch.json").write_text(
        json.dumps({**base, "state": "DISPATCH_SENT_NO_AUTOMATIC_RETRY"}, ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )
    for _ in range(15):
        rows = json.loads(gh(listing, tok))
        new = [r for r in rows if r["databaseId"] not in seen and r["headSha"] == commit]
        if new:
            assert len(new) == 1, new
            out = {**base, "state": "RUN_IDENTIFIED", "run": new[0]}
            (receipt / "dispatch.json").write_text(json.dumps(out, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
            print(json.dumps({"receipt": str(receipt), "run": new[0]}, ensure_ascii=False, indent=1))
            return 0
        time.sleep(2)
    raise SystemExit("dispatch sent but run not identified; inspect before any retry")


if __name__ == "__main__":
    raise SystemExit(main())
