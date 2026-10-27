"""One restricted MUL-only revisit; preserve exact B2 fallback and all other source."""
from pathlib import Path
import hashlib,json,datetime,re
HERE=Path(__file__).resolve().parent
ROOT=next(p for p in HERE.parents if (p/'DEVELOPMENT.md').exists())
sha=lambda b:hashlib.sha256(b).hexdigest()
base=ROOT/'competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean'
raw=base.read_bytes();assert sha(raw)=='622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58'
s=raw.decode();needle='@[inline] def mul (x y : Binary32) : Binary32 :=\n  let ex :='
assert s.count(needle)==1
start=s.index(needle);end=s.index('theorem add_eq :',start)
old=s[start:end]
renamed=old.replace('def mul (','def mulBeforePostguard (',1).replace('theorem mul_spec :','theorem mulBeforePostguard_spec :',1).replace('mul x y = ExecFloat.Spec.mul x y','mulBeforePostguard x y = ExecFloat.Spec.mul x y',1).replace('  unfold mul\n','  unfold mulBeforePostguard\n',1)
frag=(HERE/'Postguard-mul.lean.inc').read_text(encoding='utf-8')
new=s[:start]+renamed+frag+'\n'+s[end:]
b=new.encode();assert len(b)<=256000
p=HERE/'Kernel-postguard-mul-only.lean';p.write_bytes(b)
assert new.replace(renamed+frag+'\n',old,1).encode()==raw
roots=['Submission.R19PostguardMul.'+x for x in ['pairOK','normal_of_shift','pairOK_normal','finite_of_fastOK','finiteRoundtrip','table_eq_native','native_finite']]+['Submission.mulBeforePostguard','Submission.mulBeforePostguard_spec','Submission.add_spec','Submission.mul_spec','Submission.sum_spec','Submission.bmm_spec']
(HERE/'HelperAudit-postguard.lean.inc').write_text('\n'.join('#print axioms '+x for x in roots)+'\n',encoding='utf-8')
r={'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'state':'COMPLETE_SOURCE_PROOF_ATTEMPT_NOT_RUN','candidate':{'path':str(p),'bytes':len(b),'sha256':sha(b)},'baseline_sha256':sha(raw),'inverse_splice_exact':True,'explicit_helper_roots':roots,'mechanism':'R11 exact E64..191 joint OR input gate, MUL only, on the materially changed B2 numeric-decoder parent. Hit omits old exsum/LowScale decision, per-decoder eligibility and post-result self-BEq; native casts/table/scaling/product/codec remain. Miss uses exact renamed B2 mul.','not_novel':'Old guard and mathematical bridges are explicitly reused. No threshold, seed, compiler or float semantic change.','new_condition':'R11 parent nativeMul used two ofBits calls; B2 already uses two guarded numeric table decoders, so the front door can now remove work that did not exist in old parent. ADD has no corresponding new condition and is unchanged.','verification':{'lean':'NOT_RUN','codegen':'NOT_RUN','full_gate':'NOT_RUN','timing':'NOT_RUN'},'cost_limits':'Common-path source work only; actual selected MainFull compiler elimination, linked layout, missed-domain extra guard cost and whole gain UNKNOWN. Not claimed 10% whole.','formal_submission':'NOT_SUBMITTED','local_compiles':0,'CI_runs':0,'token_usage':'UNKNOWN'}
(HERE/'candidate-manifest.json').write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
print(json.dumps(r['candidate']))
