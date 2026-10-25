"""One proof-only repair from the original concrete compiler diagnostic."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
parent=C/'f01-r16-dev-a4b2-entry1';raw=(parent/'Kernel.lean').read_bytes()
assert sha(raw)=='5f53a9300f6554a80a68fcee5fda84dc4af063706c0b928be8ec9d7f1b81213c'
diagnostic=json.loads((HERE/'development-compiler-error-map-40182114389.json').read_bytes())['candidates'][0]
assert len(diagnostic['errors'])==1 and diagnostic['errors'][0]['declaration'].endswith('.wordLoop_row')
old=b'    dsimp only\n    rw [R15PackedB2.loop, dif_neg hkn]'
new=b'    rw [R15PackedB2.loop, dif_neg hkn]'
assert raw.count(old)==1
result=raw.replace(old,new);assert result.replace(new,old)==raw
folder=C/'f01-r16-dev-a4b2-entry2';assert not folder.exists();folder.mkdir()
(folder/'Kernel.lean').write_bytes(result)
meta=json.loads((parent/'manifest.json').read_bytes());parts=[]
for item in meta['components']:
    p=ROOT/item['path'];data=p.read_bytes();assert sha(data)==item['sha256']
    if old in data:
        assert data.count(old)==1
        data=data.replace(old,new);p=HERE/'development-a4b2-core-proof2.lean';assert not p.exists();p.write_bytes(data)
    parts.append(dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(data),bytes=len(data)))
meta.update(candidate=folder.name,candidate_sha256=sha(result),candidate_bytes=len(result),
    components=parts,parent=parent.name,parent_sha256=sha(raw),created_at_utc=datetime.now(timezone.utc).isoformat(),
    proof_status='PROOF_ONLY_REPAIRED_NOT_COMPILED',original_failure=40182114389,
    runtime_changed=False,repair='Delete redundant dsimp only in wordLoop_row terminal branch; original source and raw error retained.')
(folder/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps({k:meta[k] for k in ('candidate','candidate_sha256','candidate_bytes','runtime_changed')}))
