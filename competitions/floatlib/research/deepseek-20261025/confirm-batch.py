"""Run the pre-registered three-seed confirmation batch for f01-deepseek-p2contp8.

For each seed: rewrite the DeepSeek suite plan, commit+push, dispatch the manual
workflow, wait for terminal state, collect the artifact, and append the A/B line
to a batch log. Stops on the first failure and leaves all receipts in place.
"""
import json
import subprocess
import sys
import time
import urllib.request
from pathlib import Path

ROOT = Path(r"D:\CodingProject\Bitget-DeepSeek")
TRACK = ROOT / "competitions/floatlib"
PLAN = TRACK / "candidates/f01-d7-public-suite/suite-plan.json"
RESEARCH = TRACK / "research/deepseek-20261025"
SEEDS = [1525006, 1525007, 1525008]
CANDIDATES = [
    {"candidate": "f01-d12-scalar-combined",
     "sha256": "df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172",
     "capture_codegen": False},
    {"candidate": "f01-deepseek-p2contp8",
     "sha256": "699017452ec031efd8f0f161c944c4f45aab4c4eed8fff88f30faac533354049",
     "capture_codegen": False},
]


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=ROOT, check=True, capture_output=True, text=True, **kw)


def token():
    p = subprocess.run(["git", "credential", "fill"], input="protocol=https\nhost=github.com\n\n",
                       text=True, capture_output=True, cwd=ROOT)
    fields = dict(x.split("=", 1) for x in p.stdout.splitlines() if "=" in x)
    if not fields.get("password"):
        raise SystemExit("no credential")
    return fields["password"]


def run_status(run_id, tok):
    url = f"https://api.github.com/repos/HuanHuanHuanFFF/Miner/actions/runs/{run_id}"
    req = urllib.request.Request(url, headers={"User-Agent": "dsh-batch", "Authorization": f"Bearer {tok}"})
    d = json.load(urllib.request.urlopen(req, timeout=20))
    return d["status"], d["conclusion"]


def existing_run(seed):
    """Return a run id already dispatched for this seed, if any."""
    for d in sorted((RESEARCH / "ci-runs").glob("dispatch-*")):
        rec = d / "dispatch.json"
        if not rec.exists():
            continue
        try:
            data = json.loads(rec.read_text(encoding="utf-8"))
        except Exception:
            continue
        if (data.get("inputs", {}).get("seed") == str(seed)
                and data.get("state") == "RUN_IDENTIFIED"):
            return data["run"]["databaseId"]
    return None


def main():
    existing = json.loads(PLAN.read_text(encoding="utf-8"))
    log_path = RESEARCH / "confirmation-batch-runs.json"
    log = json.loads(log_path.read_text(encoding="utf-8")) if log_path.exists() else {"batch": [], "state": "RUNNING"}
    tok = token()
    for seed in SEEDS:
        if any(x["seed"] == seed for x in log["batch"]):
            continue
        plan = dict(existing)
        plan["seed"] = seed
        plan["candidates"] = CANDIDATES
        plan["sample_role"] = "CONFIRMATION"
        plan["authorization_receipt"] = "competitions/floatlib/research/deepseek-20261025/run9-plan.md"
        plan["purpose"] = "Pre-registered confirmation seed for f01-deepseek-p2contp8; all seeds reported."
        plan.pop("confirmation_candidates", None)
        new_text = json.dumps(plan, ensure_ascii=False, indent=2) + "\n"
        changed = PLAN.read_text(encoding="utf-8") != new_text
        if changed:
            PLAN.write_text(new_text, encoding="utf-8")
            sh(["git", "add", str(PLAN.relative_to(ROOT))])
            sh(["git", "-c", "core.quotepath=false", "commit", "-m",
                f"实验: 预注册确认seed {seed} [skip ci]"])
            sh(["git", "push"])
            time.sleep(2)
        status_lines = sh(["git", "status", "--porcelain=v1"]).stdout.splitlines()
        dirty = [line for line in status_lines
                 if not line.startswith(("?? competitions/floatlib/research/deepseek-20261025/ci-runs/",
                                         "?? competitions/floatlib/evidence/"))]
        if dirty:
            raise SystemExit("worktree dirty before dispatch:\n" + "\n".join(dirty))
        run_id = existing_run(seed)
        if run_id is None:
            sh([sys.executable, str(RESEARCH / "dispatch-ci.py"),
                "--candidates", "f01-d7-public-suite", "--seed", str(seed)])
            run_id = existing_run(seed)
        if run_id is None:
            raise SystemExit(f"no run identified for seed {seed}")
        print(f"seed {seed}: run {run_id}", flush=True)
        started = time.monotonic()
        while True:
            status, conclusion = run_status(run_id, tok)
            if status == "completed":
                break
            if time.monotonic() - started > 1800:
                raise SystemExit(f"run {run_id} not terminal after 30 min")
            time.sleep(20)
        print(f"seed {seed}: {conclusion}", flush=True)
        if conclusion != "success":
            log["batch"].append({"seed": seed, "run": run_id, "state": conclusion})
            log_path.write_text(json.dumps(log, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
            raise SystemExit(f"run {run_id} ended {conclusion}")
        out = sh([sys.executable, str(RESEARCH / "collect-run.py"), "--run", str(run_id)]).stdout
        print(out[-1200:], flush=True)
        data = json.loads((RESEARCH / "ci-runs" / str(run_id) / "deepseek-public-v2-ab.json").read_text(encoding="utf-8"))
        cand = data["candidates"].get("f01-deepseek-p2contp8", {})
        log["batch"].append({"seed": seed, "run": run_id, "state": "COLLECTED",
                             "ratios": cand.get("ratio_vs_anchor")})
        log_path.write_text(json.dumps(log, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    log["state"] = "DONE"
    log_path.write_text(json.dumps(log, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print("BATCH_DONE", flush=True)


if __name__ == "__main__":
    main()
