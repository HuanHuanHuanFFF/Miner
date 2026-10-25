"""Authenticate collected original public runs without recalibrating B2."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
D7 = HERE.parent
digest = lambda p: hashlib.sha256(p.read_bytes()).hexdigest()
identity = json.loads((HERE / 'retained-estimate-freeze.json').read_bytes())
model = ROOT / identity['model_path']
before = model.read_bytes()
assert digest(model) == identity['model_sha256']
stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
log = HERE / ('development-public-index-refresh-' + stamp + '.log')
with log.open('xb') as stream:
    result = subprocess.run([sys.executable, '-B', str(D7 / 'audit-suites.py')],
                            cwd=ROOT, stdout=stream, stderr=subprocess.STDOUT)
assert result.returncode == 0, str(log)
assert model.read_bytes() == before
index = D7 / 'public-suite-results.json'
rows = json.loads(index.read_bytes())['records']
retained = [r for r in rows if r['kernel_sha256'] == identity['source_sha256'] and r.get('full_gate')]
receipt = dict(at_utc=datetime.now(timezone.utc).isoformat(),
               source_index=index.relative_to(ROOT).as_posix(), index_sha256=digest(index),
               records=len(rows), retained_runs=[r['run'] for r in retained],
               numeric_model_sha256_unchanged=digest(model),
               log=log.relative_to(ROOT).as_posix(), log_sha256=digest(log),
               scope='Authenticate every collected original record, including failures and slow samples; no source selection or numeric model recalibration.')
path = HERE / ('development-public-index-refresh-' + stamp + '.json')
with path.open('xb') as stream:
    stream.write((json.dumps(receipt, ensure_ascii=False, indent=2) + '\n').encode())
print(json.dumps(receipt))
