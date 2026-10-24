from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
OUT=Path(__file__).resolve().parent;ROOT=OUT.parents[4];C=ROOT/'competitions/floatlib/candidates'
old=C/'f01-r14-dev-early-nan';raw=(old/'Kernel.lean').read_bytes();assert hashlib.sha256(raw).hexdigest()=='398d4d2a01b239df0d0c046ffe93b00c2f910716485d581f3783d921d6b27cf3'
needle='theorem addBeforeRawSelect_spec : ∀ x y : Binary32, add x y ='.encode();replacement='theorem addBeforeRawSelect_spec : ∀ x y : Binary32, addBeforeRawSelect x y ='.encode()
assert raw.count(needle)==1;fixed=raw.replace(needle,replacement)
assert fixed.replace(replacement,needle)==raw
folder=C/'f01-r14-dev-early-nan-proof2';assert not folder.exists();folder.mkdir()
(folder/'Kernel.lean').write_bytes(fixed)
meta=json.loads((old/'manifest.json').read_bytes());meta.update(candidate=folder.name,candidate_sha256=hashlib.sha256(fixed).hexdigest(),candidate_bytes=len(fixed),validation_mode='statement-only',proof_status='NOT_RUN_ONE_PROOF_TYPE_NAME_FIX',parent=old.name,parent_sha256=hashlib.sha256(raw).hexdigest(),created_at_utc=datetime.now(timezone.utc).isoformat(),runtime_identical_parent=True,correction='Exact original statement error3118: old helper theorem type still mentioned future add; rename its type to addBeforeRawSelect, leaving every executable declaration byte-identical.')
(folder/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
(OUT/'development-early-nan-proof2.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode());print(json.dumps(meta,ensure_ascii=False))
