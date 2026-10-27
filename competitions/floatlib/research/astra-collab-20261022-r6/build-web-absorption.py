from pathlib import Path
import json,hashlib
from datetime import datetime,timezone
ROOT=Path(__file__).resolve().parents[4]
HERE=Path(__file__).resolve().parent
p=HERE/'web/R6-W02/original-extracted/R6-W02/candidate/Kernel.lean'
b=p.read_bytes();assert hashlib.sha256(b).hexdigest()=='ca586a4293842efccc0178c345b9c4629636b6b959ed548a797776205af13eb3'
s=b.decode()
old='Only the enclosing parent import ContractTensor is required; no imports are added here.'
assert s.count(old)==1
out=s.replace(old,'Only the enclosing parent contract is required; no dependency is added here.').encode()
d=ROOT/'competitions/floatlib/candidates/f01-r6-web-absorption26';d.mkdir(exist_ok=True)
(d/'Kernel.lean').write_bytes(out)
m={'candidate':d.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':'f01-d5-stream-pack','parent_sha256':'8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045','web_original_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN','validation_mode':'full-gate','mechanism':'For finite normal operands with exponent gap>=26 return larger raw operand; exact dyadic proof adapted from fixed FloatLib far-gap39 proof. Original scalar add remains fallback; other functions unchanged.','repair':'One comment-only edit removes import keyword which original policy would reject atline2068. Original web source preserved. No theorem/runtime edits.','expected_gain':'UNKNOWN; old wide-gap sample coverage44.84% is legacy-only; public-v2 suite costs and private suite distributions not measured here.','formal_submission':'NOT_SUBMITTED'}
(d/'manifest.json').write_text(json.dumps(m,indent=2)+'\n');print(json.dumps(m,indent=2))
