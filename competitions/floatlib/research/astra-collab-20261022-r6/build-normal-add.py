from pathlib import Path
import hashlib,json
from datetime import datetime, timezone
ROOT=Path(__file__).resolve().parents[4]
HERE=Path(__file__).resolve().parent
p=ROOT/'competitions/floatlib/candidates/f01-r6-fused-add/Kernel.lean'
b=p.read_bytes()
assert hashlib.sha256(b).hexdigest()=='b911f8d7ef9bb31d22f2fad3dc15a04556e7b9e1d00144a1d3b225168c9f1343'
s=b.decode()
a=s.index('/-- Fuse conversion eligibility with finiteness')
z=s.index('namespace NativeBridge',a)
out=(s[:a]+(HERE/'normal-add-block.lean').read_text()+'\n'+s[z:]).encode()
d=ROOT/'competitions/floatlib/candidates/f01-r6-normal-add'
d.mkdir(exist_ok=True)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':'f01-r6-fused-add','parent_sha256':hashlib.sha256(b).hexdigest(),'validated_base':'f01-d5-stream-pack','validated_base_sha256':'8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045','created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN','validation_mode':'full-gate','mechanism':'Two single unsigned interval compares fuse normal numeric decoder eligibility and finite input checks. Raw ±0 and all inputs outside exponent24..254 use unchanged parent add. All scored add inputs eligible, proven from fixed generator exponent ranges.','expected_gain':'UNKNOWN; predicted guard operation reduction only; full same-batch total timings required.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
print(json.dumps(m,indent=2))
