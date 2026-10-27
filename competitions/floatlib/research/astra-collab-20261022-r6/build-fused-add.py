from pathlib import Path
import hashlib, json, re
from datetime import datetime, timezone
ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
parent = ROOT / 'competitions/floatlib/candidates/f01-d5-stream-pack/Kernel.lean'
b = parent.read_bytes()
assert hashlib.sha256(b).hexdigest() == '8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
s = b.decode()
start = s.index('/-- Raw exponent tests establish both native input conditions. -/')
end = s.index('namespace NativeBridge', start)
old = s[start:end]
old = old.replace('def add (', 'def addR6Parent (').replace('theorem add_spec', 'theorem addR6Parent_spec').replace('add x y = ExecFloat.Spec.add x y', 'addR6Parent x y = ExecFloat.Spec.add x y').replace('unfold add\n', 'unfold addR6Parent\n')
new = s[:start] + old + (HERE / 'fused-add-block.lean').read_text() + '\n' + s[end:]
dest = ROOT / 'competitions/floatlib/candidates/f01-r6-fused-add'
dest.mkdir(exist_ok=True)
out = new.encode()
(dest/'Kernel.lean').write_bytes(out)
manifest = {'candidate':dest.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(out).hexdigest(),'candidate_bytes':len(out),'parent':'f01-d5-stream-pack','parent_sha256':hashlib.sha256(b).hexdigest(),'created_at_utc':datetime.now(timezone.utc).isoformat(),'proof_status':'NOT_RUN','validation_mode':'full-gate','mechanism':'Fuse fast numeric conversion eligibility and finite-input guard for scalar add; direct tableProduct on both eligible operands, unchanged parent fallback otherwise. Existing arithmetic and all non-add entry points preserved.','expected_gain':'UNKNOWN; add share39.7%, changed path removes redundant finite tests and decoder rechecks, adds one combined guard on fallback. Need full same-batch cost including missed paths.','formal_submission':'NOT_SUBMITTED'}
(dest/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
print(json.dumps(manifest,indent=2))
