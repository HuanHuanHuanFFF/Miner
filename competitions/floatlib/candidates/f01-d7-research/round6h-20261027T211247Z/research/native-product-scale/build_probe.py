from pathlib import Path
from datetime import datetime,timezone
import hashlib,json
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'AGENTS.md').exists())
BASE=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
base=BASE.read_bytes();runtime=(HERE/'Runtime.lean.inc').read_bytes()
sha=lambda b:hashlib.sha256(b).hexdigest()
assert sha(base)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
assert len(runtime)<=1500
kernel=base+b'\n'+runtime
assert len(kernel)<=256000 and b'\r' not in kernel
(HERE/'Kernel-probe1.lean').write_bytes(kernel)
roots=['Submission.'+x+'_spec' for x in ['add','mul','sum','bmm']]+[
 'Submission.R22NativeProductScale.'+x for x in ['normalCore','guardedMul','diagnosticEntry']]
(HERE/'HelperAudit.lean.inc').write_text(''.join('#print axioms '+r+'\n' for r in roots),encoding='utf-8')
out={
 'created_utc':datetime.now(timezone.utc).isoformat(),'state':'COMPLETE_GUARDED_RUNTIME_PROBE_NOT_RUN',
 'start_utc':'2026-10-27T23:25:59Z','bound_utc':'2026-10-27T23:45:59Z','shared_deadline_utc':'2026-10-28T03:12:47Z',
 'base_sha256':sha(base),'base_prefix_identical':True,
 'runtime_bytes':len(runtime),'runtime_sha256':sha(runtime),
 'kernel_bytes':len(kernel),'kernel_sha256':sha(kernel),
 'explicit_helper_audit':roots,'helper_audit_sha256':sha((HERE/'HelperAudit.lean.inc').read_bytes()),
 'roots_meaning':'4unchangedpublicspecs+3runtime definitions; not a newMUL correctnessproof',
 'public_four_operations':'UNCHANGED_B2',
 'domain':'Both originalbiasedexponents1..254; sum174..380; arbitrarysign/fraction. Everythingelse callsoldB2mul.',
 'mechanism':'ExactUInt64 24x24product -> nativeFloat32 RNE -> oneexisting signedpower2 scale lookup/multiply -> directnative carrier. No reverseintegercast ormanualoutputpack.',
 'old_formula':'R13 combined-scale paper/8852modelcases wasuncompiled/untimed; newfront-end usesactualU64product decode acceptedin6589. No noveltyclaim.',
 'new_Lean':'NOT_RUN','full_new_mul_spec':'NOT_PROVED','performance':'UNKNOWN','CI':False,'local_Lean':False,
 'missing':['synthetic scale/sign word bridge','exactsecondFloat32 multiplication and originalmul transport','newsource fullgate/cost/confirmation'],
}
(HERE/'manifest.json').write_text(json.dumps(out,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,indent=2))
