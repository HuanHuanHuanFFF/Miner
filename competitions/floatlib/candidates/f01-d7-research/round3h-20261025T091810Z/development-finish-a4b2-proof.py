"""Remove only tactics after the real compiler reports the goal already closed."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
parent=C/'f01-r16-dev-a4b2-entry2';raw=(parent/'Kernel.lean').read_bytes()
assert sha(raw)=='e49cbc90ee9d40ede5117cc69145f5215900ff755c845e6443b7356efb0de000'
report=json.loads((HERE/'development-compiler-error-map-40182931528.json').read_bytes())['candidates'][0]
assert len(report['errors'])==1 and report['errors'][0]['message']=='No goals to be solved'
old='''    rw [R15PackedB2.loop, dif_neg hkn]
    rcases r with ⟨r,hr⟩
    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
    rcases h with rfl|rfl|rfl|rfl <;> rfl
'''.encode()
new=b'    rw [R15PackedB2.loop, dif_neg hkn]\n'
assert raw.count(old)==1
result=raw.replace(old,new)
folder=C/'f01-r16-dev-a4b2-entry3';assert not folder.exists();folder.mkdir();(folder/'Kernel.lean').write_bytes(result)
meta=json.loads((parent/'manifest.json').read_bytes());parts=[]
for part in meta['components']:
    p=ROOT/part['path'];data=p.read_bytes();assert sha(data)==part['sha256']
    if old in data:
        data=data.replace(old,new);p=HERE/'development-a4b2-core-proof3.lean';assert not p.exists();p.write_bytes(data)
    parts.append(dict(path=p.relative_to(ROOT).as_posix(),sha256=sha(data),bytes=len(data)))
meta.update(candidate=folder.name,candidate_sha256=sha(result),candidate_bytes=len(result),components=parts,
    parent=parent.name,parent_sha256=sha(raw),created_at_utc=datetime.now(timezone.utc).isoformat(),
    proof_status='DEAD_TACTICS_REMOVED_PENDING_FULL_GATE',runtime_changed=False,
    original_failure=40182931528,repair='Terminal rw already closes the proof; remove its three unreachable subsequent tactics. All runtime definitions unchanged.')
(folder/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps({k:meta[k] for k in ('candidate','candidate_sha256','candidate_bytes','runtime_changed')}))
