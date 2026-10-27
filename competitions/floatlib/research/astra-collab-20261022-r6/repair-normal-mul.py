from pathlib import Path
from datetime import datetime,timezone
import json,hashlib
ROOT=Path(__file__).resolve().parents[4]
d=ROOT/'competitions/floatlib/candidates/f01-r6-normal-mul'
b=(d/'Kernel.lean').read_bytes();assert hashlib.sha256(b).hexdigest()=='f6acc4bc211eb1724a4152a60f2dea391959c5ddfa9ba09b7b15455025563d8a'
s=b.decode();old='namespace R6NormalMul\n\nopen FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32'
new='namespace R6NormalMul\n\nopen FloatLib.Floats Competition\nopen FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32'
assert s.count(old)==1
out=s.replace(old,new).encode();dest=d.with_name(d.name+'-proof1');dest.mkdir(exist_ok=True)
(dest/'Kernel.lean').write_bytes(out)
m=json.loads((d/'manifest.json').read_text());m.update(candidate=dest.name,candidate_sha256=hashlib.sha256(out).hexdigest(),candidate_bytes=len(out),parent=d.name,parent_sha256=hashlib.sha256(b).hexdigest(),proof_status='NOT_RUN',created_at_utc=datetime.now(timezone.utc).isoformat(),repair='705 first error: Binary32 and ExecFloat names out of scope in newly inserted namespace. Add open FloatLib.Floats Competition; definitions and proofs otherwise byte-identical. Old failed source preserved.')
(dest/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
