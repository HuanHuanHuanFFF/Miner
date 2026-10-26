"""Import only the three constructor-rewrite repairs against the actual source."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
old=C/'f01-r17-dev-u64-public1';before=(old/'Kernel.lean').read_bytes()
source=(HERE/'astra-workers/structural-frontier/integer-normal-mul/public-entry-repair1/Kernel.lean').read_bytes()
assert sha(before)=='23adf0984bef02e611143cfc7e40d64d65c99caa0f4d11a0648812b2fb6f1e73'
assert sha(source)=='00ab99c7ff16a8f0f58c5a0b6ad5c87c10c2407589ee17c5f9cba444b7cfd080' and len(source)==255728 and b'\r' not in source
a,b=before.decode().splitlines(),source.decode().splitlines();assert len(a)==len(b)
changes=[dict(line=i+1,old=x,new=y) for i,(x,y) in enumerate(zip(a,b)) if x!=y]
assert len(changes)==3 and [x['line'] for x in changes]==[6849,6873,6907]
for row in changes:
    assert 'rw [' in row['old'] and 'simp only [' in row['new'] and "UInt32.toNat_ofNat'" in row['new']
name='f01-r17-dev-u64-public2';folder=C/name;folder.mkdir();(folder/'Kernel.lean').write_bytes(source)
part=HERE/'development-u64-public2-source.lean';part.write_bytes(source)
meta=json.loads((old/'manifest.json').read_bytes());meta.update(candidate=name,candidate_sha256=sha(source),candidate_bytes=len(source),created_at_utc=datetime.now(timezone.utc).isoformat(),parent=old.name,parent_sha256=sha(before),components=[dict(path=part.relative_to(ROOT).as_posix(),sha256=sha(source),bytes=len(source))],helper_audit_source_sha256=sha(source),proof_status='NOT_COMPILED',performance='NOT_RUN',repair='Only three proof lines: generic explicit UInt32.ofNat constructor lemma, scope simp-only; runtime and premises unchanged.',repair_evidence=40307208739)
(folder/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
(HERE/'development-u64-public2-delta.json').write_bytes((json.dumps(dict(source_sha256=sha(source),changes=changes),ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name,sha256=sha(source),bytes=len(source),proof_lines=3)))
