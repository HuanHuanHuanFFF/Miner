"""Tail a live GitHub Actions run log without printing credentials."""
import json
import os
import subprocess
import sys

run = sys.argv[1]
lines = int(sys.argv[2]) if len(sys.argv) > 2 else 25

p = subprocess.run(["git", "credential", "fill"], input="protocol=https\nhost=github.com\n\n",
                   text=True, capture_output=True, cwd=r"D:\CodingProject\Bitget-DeepSeek")
fields = dict(x.split("=", 1) for x in p.stdout.splitlines() if "=" in x)
tok = fields.get("password")
if not tok:
    raise SystemExit("no credential")
env = os.environ.copy()
env["GH_TOKEN"] = tok
r = subprocess.run(["gh", "run", "view", run, "--repo", "HuanHuanHuanFFF/Miner", "--log"],
                   capture_output=True, text=True, encoding="utf-8", env=env)
text = r.stdout or r.stderr
print("\n".join(text.splitlines()[-lines:]))
