"""Directed compiler-boundary diagnostic, not an attribute sweep."""
from pathlib import Path
import json,hashlib
OWN=Path(__file__).resolve().parent
source=(OWN.parent/'f01-word-tensors-proof1/Kernel.lean').read_text(encoding='utf-8')
assert hashlib.sha256(source.encode()).hexdigest()=='5b6091b27780d9cd5e6fd1d406660bb7a929a8550bf15e82f511305522d3eb1b'
source=source.replace('def sum {n : Nat}','@[inline] def sum {n : Nat}').replace('def bmm (batch','@[inline] def bmm (batch')
digest=hashlib.sha256(source.encode()).hexdigest();(OWN/'Kernel.lean').write_bytes(source.encode())
(OWN/'manifest.json').write_bytes((json.dumps({'candidate':OWN.name,'candidate_file':'Kernel.lean','candidate_sha256':digest,'candidate_bytes':len(source.encode()),'kernel_sha256':digest,'kernel_bytes':len(source.encode()),'parent':'f01-word-tensors-proof1','mechanism':'One directed compiler-boundary experiment: expose sum/bmm bodies to caller specialization, arithmetic and proofs unchanged','purpose':'Diagnose whether pure tensor specialization affects work placement relative to timing; no arithmetic-speed claim without code inspection','proof_status':'UNVERIFIED_THIS_EXACT_SOURCE','validation_mode':'full-gate','independent_confirmation':'NOT_RUN'},indent=2)+'\n').encode());print(OWN.name,digest)
