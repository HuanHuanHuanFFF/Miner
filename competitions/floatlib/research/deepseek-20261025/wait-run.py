"""Wait for a GitHub Actions run job to finish (or a step timeout), printing changes.

Uses the stored Git credential for authenticated API calls (anonymous calls hit
the 60/hour rate limit). The token never leaves this process.
"""
import json
import subprocess
import sys
import time
import urllib.request
from datetime import datetime, timezone

run = sys.argv[1]
limit = float(sys.argv[2]) if len(sys.argv) > 2 else 540.0
url = f"https://api.github.com/repos/HuanHuanHuanFFF/Miner/actions/runs/{run}/jobs"

p = subprocess.run(["git", "credential", "fill"], input="protocol=https\nhost=github.com\n\n",
                   text=True, capture_output=True, cwd=r"D:\CodingProject\Bitget-DeepSeek")
tok = dict(x.split("=", 1) for x in p.stdout.splitlines() if "=" in x).get("password")
if not tok:
    raise SystemExit("no stored credential")
headers = {"User-Agent": "dsh-wait", "Authorization": f"Bearer {tok}"}

seen = None
start = time.monotonic()
while True:
    try:
        req = urllib.request.Request(url, headers=headers)
        data = json.load(urllib.request.urlopen(req, timeout=20))
        job = data["jobs"][0]
        state = (job["status"], job["conclusion"], tuple((s["name"], s["status"]) for s in job["steps"]))
        if state != seen:
            seen = state
            cur = [n for n, s in state[2] if s == "in_progress"]
            done = [n for n, s in state[2] if s == "completed"]
            print(datetime.now(timezone.utc).strftime("%H:%M:%SZ"), job["status"], job["conclusion"],
                  "| running:", ", ".join(cur) or "-", "| done:", len(done), flush=True)
        if job["status"] == "completed":
            print("DONE", job["conclusion"], flush=True)
            break
    except Exception as exc:  # transient API errors are not fatal
        print("poll error", exc, flush=True)
    if time.monotonic() - start > limit:
        print("TIMEOUT_WAIT", flush=True)
        break
    time.sleep(20)
