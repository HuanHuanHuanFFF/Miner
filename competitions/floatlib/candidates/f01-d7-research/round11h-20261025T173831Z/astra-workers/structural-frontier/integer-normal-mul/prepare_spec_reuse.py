"""Extract only exact old model/spec support; quantify source cost, never execute Lean or CI."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,re
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda x:hashlib.sha256(x).hexdigest()
oldpath=R/'competitions/floatlib/candidates/f01-r14-dev-mul-cache-rse2/Kernel.lean'
old=oldpath.read_bytes();assert sha(old)=='9038f8d653f030a8812c3187733488f70995253a1a7b284759c4f58b96378c19'
pieces=[];parts=[]
def take(name,start,end,namespace=None):
 lo=old.index(start);hi=old.index(end,lo);body=old[lo:hi]
 if namespace:
  body=('namespace '+namespace+'\nopen FloatLib.Floats Competition\nopen FloatLib.Floats.Formats.BinaryInterchange\n').encode()+body+('\nend '+namespace+'\n').encode()
 parts.append(body);pieces.append(dict(name=name,source_byte_start=lo,source_byte_end_exclusive=hi,
  copied_sha256=sha(old[lo:hi]),assembled_sha256=sha(body),bytes=len(body),namespace_wrapper=namespace))
take('generic decoded multiplication',b'namespace Submission.R14NativeProduct\n',b'namespace Submission.R14NatNormal\n')
take('normal input decode',b'theorem raw_normal_decode (u : UInt32)',b'end Submission.R14NatNormal', 'Submission.R14NatNormal')
take('raw exponent mapping',b'@[inline] def ex (u : UInt32)',b'@[inline] def sign (u v : UInt32)', 'Submission.R14ExponentShift')
take('restricted original multiplication model',b'theorem model_mul_normal_fields',b'theorem core_model (u v : UInt32)', 'Submission.R14ExponentShift')
take('unchanged eligibility and its full premises',b'@[inline] def eligible (u v : UInt32)',b'@[inline] def guardedMul (fallback', 'Submission.R14ExponentShift')
support=b'\n'.join(parts);(H/'Old-model-support-v1.lean.inc').write_bytes(support)
q=H.parent/'inline-u64-mul'
probe=q/'probe-b2-v1/Probe-b2-u64-roundtrip-v1.lean'
frags=[probe,q/'Runtime-u64-mul-integer-v3-lf.lean.inc',q/'Fields-u64-integer-v1.lean.inc',q/'Runtime-fields-bridge-v1.lean.inc',H/'Old-model-support-v1.lean.inc',H/'Public-numeric-mul-bridge-v1.lean.inc']
joined=b'\n'.join(p.read_bytes() for p in frags)
assert b'\r' not in joined
# This file is a size/layout preview, not a runnable/public candidate. No original is overwritten.
(H/'Public-math-layout-v1.lean.txt').write_bytes(joined)
record=dict(updated_utc=datetime.now(timezone.utc).isoformat(),state='MODEL_SPEC_REUSE_LAYOUT_NOT_FROZEN_FOR_CI',
 source=dict(path=str(oldpath.relative_to(R)),sha256=sha(old)),pieces=pieces,
 support=dict(path='Old-model-support-v1.lean.inc',sha256=sha(support),bytes=len(support)),
 fragments=[dict(path=str(p.relative_to(R)),bytes=p.stat().st_size,sha256=sha(p.read_bytes())) for p in frags],
 whole_untrimmed_bytes=len(joined),limit=256000,over_limit=max(0,len(joined)-256000),
 avoided_old_integer_runtime_proof_namespace_bytes=7864,
 reason='Reuse original finite-input model theorem and carrier proof pattern rather than duplicate old R14DIntegerNormal/rse runtime proof tree',
 prerequisite='Exact UInt64 reverse-cast Int.toNat normalization is known pending; do not mutate or requeue frozen9f9 from this preview',
 CI=False,Git=False,local_Lean=False)
(H/'spec-reuse-layout.json').write_bytes((json.dumps(record,indent=2)+'\n').encode())
print(json.dumps({k:record[k] for k in ('state','support','whole_untrimmed_bytes','over_limit','avoided_old_integer_runtime_proof_namespace_bytes')}))
