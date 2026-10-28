"""Math-carrier for minimal normal-field formula. No public ADD replacement."""
from pathlib import Path
import hashlib,json
from datetime import datetime,timezone
D=Path(__file__).resolve().parent
B=(D/'Kernel-same-exponent-probe.lean').read_bytes()
assert hashlib.sha256(B).hexdigest()=='c37e74cafd26a4ee14ba9987e052b757a311d4507ab3f21d4f2ed9a9e1802c3b'
inc=(D/'SameExponentMath.lean.inc').read_bytes();out=B+b'\n'+inc;P=D/'Kernel-same-exponent-math.lean';P.write_bytes(out)
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec','Submission.R22SameExponent.eligible','Submission.R22SameExponent.core','Submission.R22SameExponent.diagnosticEntry','Submission.R22SameExponentMath.nativeNormal','Submission.R22SameExponentMath.half_round','Submission.R22SameExponentMath.half_bound','Submission.R22SameExponentMath.sum_log','Submission.R22SameExponentMath.normal_round','Submission.R22SameExponentMath.normal_fields_add']
(D/'HelperAudit-same-exponent-math.lean.inc').write_text('import Kernel\n'+''.join('#print axioms '+r+'\n' for r in roots),encoding='utf8',newline='\n')
m={'at_utc':datetime.now(timezone.utc).isoformat(),'kernel':P.name,'kernel_bytes':len(out),'kernel_sha256':hashlib.sha256(out).hexdigest(),'runtime_probe_prefix_sha256':hashlib.sha256(B).hexdigest(),'roots':roots,'new_mathematical_claim':'Normal fields e1..253: exact Model.Spec.add is e+1 and 1-bit ties-even sum of fractions. Actual raw guard/packing, E0, E254 and public ADD composition remain missing.','status':'NOT_RUN','root_accounting':'4 old specs + 3 runtime definitions + 1 reused normal-rounding proof + 5 new math lemmas; not thirteen new results','runtime_change':'None relative to c37e74ca diagnostic; four public entries still B2','files':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [P,D/'SameExponentMath.lean.inc',D/'HelperAudit-same-exponent-math.lean.inc']}}
(D/'same-exponent-math-manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({k:m[k] for k in ['kernel','kernel_bytes','kernel_sha256','status']}))
