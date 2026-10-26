"""Capture fresh root/track lightweight checks without starting Lean or CI."""
from datetime import datetime, timezone
from pathlib import Path
import hashlib
import json
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
log = HERE / 'development-closing-local-check.log'
with log.open('wb') as stream:
    result = subprocess.run([sys.executable, '-B', str(ROOT / 'scripts/project.py'), 'check'],
        cwd=ROOT, stdout=stream, stderr=subprocess.STDOUT)
receipt = {'at_utc': datetime.now(timezone.utc).isoformat(), 'exit_code': result.returncode,
    'log': log.relative_to(ROOT).as_posix(), 'log_sha256': hashlib.sha256(log.read_bytes()).hexdigest(),
    'scope': 'Root links, workflow policies, both track local checks and all candidate manifests; no local Lean or CI'}
(HERE / 'development-closing-local-check.json').write_bytes((json.dumps(receipt, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps(receipt))
if result.returncode:
    print(log.read_text('utf-8', errors='replace')[-6000:])
raise SystemExit(result.returncode)
