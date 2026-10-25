"""Verify public mathematical artifacts by exact hash, without Lean or private URLs."""
from pathlib import Path
import hashlib
import json

OUT = Path(__file__).resolve().parent
ROOT = OUT.parents[4]
index = json.loads((OUT / 'development-web-materials-public/index.json').read_bytes())
for record in index['artifacts']:
    path = ROOT / record['path']
    assert path.resolve().is_relative_to(OUT)
    raw = path.read_bytes()
    assert len(raw) == record['bytes'] and hashlib.sha256(raw).hexdigest() == record['sha256']
print(json.dumps({'status':'PASS_BYTES_ONLY','artifacts':len(index['artifacts']),'original_math_files':index['original_artifact_count'],'lean_or_performance_test':False}))
