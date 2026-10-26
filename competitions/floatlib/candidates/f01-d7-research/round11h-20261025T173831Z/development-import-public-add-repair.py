from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent;ROOT=HERE.parents[4];C=ROOT/'competitions/floatlib/candidates'
sha=lambda b:hashlib.sha256(b).hexdigest()
old=C/'f01-r17-dev-add-public1';before=(old/'Kernel.lean').read_bytes();assert sha(before)=='7e1524c818285ce2c7721140fd0cff23560416abc6ea9a2c72ddf1be9a588be7'
worker=HERE/'astra-workers/numeric-roundtrip/public-add-v2';source=(worker/'Kernel.lean').read_bytes()
assert sha(source)=='93cc191a74b3b12a70770ffcce2eeb0c60519f5b5daec69e17100fa775d6be5e' and len(source)==255148 and b'\r' not in source
name='f01-r17-dev-add-public2';folder=C/name;folder.mkdir();(folder/'Kernel.lean').write_bytes(source)
part=HERE/'development-add-public2-source.lean';part.write_bytes(source)
meta=json.loads((old/'manifest.json').read_bytes());meta.update(candidate=name,candidate_sha256=sha(source),candidate_bytes=len(source),created_at_utc=datetime.now(timezone.utc).isoformat(),parent=old.name,parent_sha256=sha(before),components=[dict(path=part.relative_to(ROOT).as_posix(),sha256=sha(source),bytes=len(source))],helper_audit_source_sha256=sha(source),proof_status='NOT_COMPILED',performance='NOT_RUN',repair='Producer proof-only fixes for all six actual40307208739 goals; original input domain and runtime retained. Fixed Nat.shiftRight/Bool.and API plus normalized model equality.',repair_evidence=40307208739)
(folder/'manifest.json').write_bytes((json.dumps(meta,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps(dict(candidate=name,sha256=sha(source),bytes=len(source))))
