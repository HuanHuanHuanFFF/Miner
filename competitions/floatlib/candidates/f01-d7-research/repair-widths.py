"""Repair the exact constructor-arity proof failure; preserve original failed sources."""
from pathlib import Path
import json,hashlib

ROOT=Path(__file__).resolve().parents[1]
expected={4:'d9526a34d6626a7417e5f3c61a02e8d840f9b1fbcaed2df7f3f558c751d6a959',8:'f36c6cab0a4f14fc9be838297f0dd8700c25e8669aa112f5419c0bf3dffd175b'}
for width,digest in expected.items():
    parent=ROOT/f'f01-d7-width{width}';raw=(parent/'Kernel.lean').read_bytes();assert hashlib.sha256(raw).hexdigest()==digest
    old='⟨'+', '.join(['zero32']*10)+f'⟩ : F{width}'
    source=raw.decode('utf-8');assert source.count(old)==1
    source=source.replace(old,f'zero{width} : F{width}')
    out=ROOT/f'f01-d7-width{width}-proof1';out.mkdir(exist_ok=True);payload=source.encode('utf-8');(out/'Kernel.lean').write_bytes(payload)
    manifest=json.loads((parent/'manifest.json').read_text('utf-8'));manifest.update(candidate=out.name,candidate_sha256=hashlib.sha256(payload).hexdigest(),candidate_bytes=len(payload),proof_status='NOT_RUN',failed_parent_sha256=digest,proof_repair='Only hz constructor: replace stale ten zero fields by the matching already defined zero4/zero8; runtime definitions unchanged',failed_run=39832394805)
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n','utf-8')
    print(out.name,manifest['candidate_sha256'],len(payload))
