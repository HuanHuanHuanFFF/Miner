"""Materialize complete same-E ADD proof attempt. No Lean, Git or CI execution."""
import hashlib,json,re
from pathlib import Path
from datetime import datetime,timezone
D=Path(__file__).resolve().parent
R=next(p for p in D.parents if (p/'AGENTS.md').exists())
B=R/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean';base=B.read_bytes()
assert hashlib.sha256(base).hexdigest()=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
names=['Runtime-same-exponent.lean.inc','SameExponentMath.lean.inc','SameExponentGuard.lean.inc','SameExponentLow.lean.inc','SameExponentZero.lean.inc','SameExponentPack.lean.inc','SameExponentFinish.lean.inc']
parts=[(D/n).read_bytes() for n in names]
carrier=base+b'\n'+b'\n'.join(parts)
assert b'R22Base' not in carrier
body=carrier.replace(b'Submission',b'R22Base')
footer=b'''\nnamespace Submission
open FloatLib.Floats Competition
@[inline] def add (x y : Binary32) : Binary32 := R22Base.R22SameExponent.diagnosticEntry x y
theorem add_spec : \xe2\x88\x80 x y : Binary32, add x y = ExecFloat.Spec.add x y :=
  R22Base.R22SameExponentGuard.diagnosticEntry_spec
@[inline] def mul := R22Base.mul
theorem mul_spec := R22Base.mul_spec
@[inline] def sum {n : Nat} (x : Vector Binary32 n) : Binary32 := R22Base.sum x
theorem sum_spec := R22Base.sum_spec
@[inline] def bmm := R22Base.bmm
theorem bmm_spec := R22Base.bmm_spec
end Submission
'''
out=body+footer
assert len(out)<256000,len(out)
assert body.replace(b'R22Base',b'Submission')==carrier
P=D/'Kernel-same-exponent-full-v1.lean';P.write_bytes(out)
roots=['Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec']
for part in parts:
    ns=None
    for line in part.decode().splitlines():
        m=re.match(r'namespace (\S+)',line)
        if m:ns=m.group(1).replace('Submission','R22Base')
        m=re.match(r'(?:@\[inline\] )?(?:def|theorem) (\w+)',line)
        if m and ns:roots.append(ns+'.'+m.group(1))
assert len(roots)==len(set(roots)),roots
(D/'HelperAudit-same-exponent-full-v1.lean.inc').write_text('import Kernel\n'+''.join('#print axioms '+x+'\n' for x in roots),encoding='utf8',newline='\n')
for bad in [rb'\bsorry\b',rb'\badmit\b',rb'\bunsafe\b',rb'\baxiom\b',rb'\bimplemented_by\b']:
    assert not re.search(bad,out),bad
assert re.findall(rb'^import .+$',out,re.M)==[b'import ContractTensor']
m={'at_utc':datetime.now(timezone.utc).isoformat(),'status':'FULL_PUBLIC_ADD_PROOF_ATTEMPT_NOT_RUN','kernel':str(P.relative_to(R)),'kernel_sha256':hashlib.sha256(out).hexdigest(),'kernel_bytes':len(out),'base_sha256':hashlib.sha256(base).hexdigest(),'runtime_vs_c37':'Same original runtime; original B2 body is namespace-renamed, new public ADD calls its complete guarded entry. No predicates, formulas, fallback bodies or other three public operation bodies changed.','reconstruction':'Global Submission->R22Base rename of exact B2+listed components, then explicit public alias footer; reverse rename exactly recovered carrier.','roots':roots,'root_count':len(roots),'scope':'Four current public obligations plus new runtime/mathematical roots. These include reused normal proof and helper definitions, not all new substantive math.','missing_validation':['Lean statement','Full original kernel replay and allowed-axiom audit','Checksum','Actual complete guarded cost','Original full25-round benchmark and independent frozen confirmation if selected'],'model_evidence':'same-exponent-add.json + parent add-affine-independent-review.json; finite only; no new enumeration','files':{p.name:{'bytes':len(p.read_bytes()),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in [P,D/'HelperAudit-same-exponent-full-v1.lean.inc',*[D/n for n in names]]}}
(D/'same-exponent-full-v1-manifest.json').write_text(json.dumps(m,indent=2)+'\n',encoding='utf8',newline='\n')
print(json.dumps({k:m[k] for k in ['kernel_sha256','kernel_bytes','root_count','status']}))
