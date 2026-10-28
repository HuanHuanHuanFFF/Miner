"""Build one B2-prefix diagnostic; no public correctness claim and no CI/Git."""
import hashlib,json
from pathlib import Path
from datetime import datetime,timezone
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
B=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
base=B.read_bytes();assert hashlib.sha256(base).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
inc=(D/'Runtime-same-exponent.lean.inc').read_bytes();out=base+b'\n'+inc
P=D/'Kernel-same-exponent-probe.lean';P.write_bytes(out)
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec','Submission.R22SameExponent.eligible','Submission.R22SameExponent.core','Submission.R22SameExponent.diagnosticEntry']
audit='import Kernel\n'+''.join('#print axioms '+r+'\n' for r in roots)
(D/'HelperAudit-same-exponent.lean.inc').write_text(audit,encoding='utf8',newline='\n')
manifest={'at_utc':datetime.now(timezone.utc).isoformat(),'state':'COST_DISCRIMINATOR_NOT_RUN','kernel':str(P.relative_to(R)),'kernel_sha256':hashlib.sha256(out).hexdigest(),'kernel_bytes':len(out),'base_sha256':hashlib.sha256(base).hexdigest(),'prefix_exact':out[:len(base)]==base,'public_entries':'Four original B2 entries unchanged; seven audit roots are four old specs plus three new definitions, not a new add_spec','roots':roots,'complete_new_entry':'Submission.R22SameExponent.diagnosticEntry','domain':'Same sign and raw exponent, exponent <=254; includes subnormal/zero and overflow e254. All other inputs original B2 fallback.','comparison':'Do not import R18 broad-sorted-add performance; same-exponent idea appeared R14 but this runtime has no sorting, variable alignment, native cast, FP op, table read or toBits in accepted arm.','lean':'NOT_RUN','equivalence':'FINITE_MODEL_ONLY; semantic proof incomplete','performance':'UNKNOWN','restrictions':'Diagnostic only; candidate cannot be adopted or submitted before full new public add_spec and original gate.','files':{p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in [P,D/'Runtime-same-exponent.lean.inc',D/'HelperAudit-same-exponent.lean.inc',D/'same_exponent_add.py',D/'same-exponent-add.json']}}
(D/'same-exponent-probe-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({k:manifest[k] for k in ['kernel_sha256','kernel_bytes','state','public_entries']}))
