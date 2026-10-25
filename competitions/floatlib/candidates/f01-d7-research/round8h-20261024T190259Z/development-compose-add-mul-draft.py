"""Read-only-parent composition for size analysis; output is not a candidate."""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json

OUT=Path(__file__).resolve().parent
ROOT=OUT.parents[4]
C=ROOT/'competitions/floatlib/candidates'
sha=lambda raw:hashlib.sha256(raw).hexdigest()
add=(C/'f01-r14-dev-word-add-entry1/Kernel.lean').read_bytes()
mul=(C/'f01-r14-dev-combined-headroom3/Kernel.lean').read_bytes()
foundation=(OUT/'development-word-add-foundation3.lean').read_bytes()
assert sha(add)=='a2342948257d2e2e2011f0fe941bd2b692e70604b915734f4538b5efd1e69372'
assert sha(mul)=='d2b8a436c051c035d1e206f1b8bdec03c2840c0324e459436bb886e5fae32274'
text=mul.decode()
begin=text.index('namespace Submission.R14NativeProduct\n')
end=text.index('\nnamespace Submission\nopen FloatLib.Floats Competition\n\n@[inline] def mul ',begin)
math=text[begin:end]
removed=[]
def cut(first,last,verify_in_foundation=False):
    global math
    lo=math.index(first);hi=math.index(last,lo)
    block=math[lo:hi]
    if verify_in_foundation:assert block.encode() in foundation
    removed.append(dict(first=first,bytes=len(block.encode()),sha256=sha(block.encode()),identical_in_add_foundation=verify_in_foundation))
    math=math[:lo]+math[hi:]
cut('def rounded (p : Nat)', 'theorem leading_bounds (p : Nat)',True)
cut('theorem native_round_normal ', 'theorem round_normal_decode ',False)
cut('theorem raw_normal_decode ', 'end Submission.R14NatNormal',True)
cut('@[inline] def ex (u : UInt32)', 'end Submission.R14ExponentShift',True)
assert math.count('def core (u v : UInt32)')==2
assert 'def rounded (p : Nat)' not in math and '@[inline] def ex ' not in math
text=add.decode()
first=text.index('@[inline] def mul (x y : Binary32) : Binary32 :=\n  let ex :=')
last=text.index('theorem add_eq :',first)
old=text[first:last]
assert old.count('theorem mul_spec ')==1
fallback=old.replace('def mul (','def mulBeforeExponent (').replace('theorem mul_spec (','theorem mulBeforeExponent_spec (')
fallback=fallback.replace(': mul x y = ExecFloat.Spec.mul x y',': mulBeforeExponent x y = ExecFloat.Spec.mul x y')
fallback=fallback.replace('  unfold mul\n','  unfold mulBeforeExponent\n')
wrapper='''
namespace Submission
open FloatLib.Floats Competition

@[inline] def mul (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul mulBeforeExponent x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  exact R14ExponentShift.guardedMul_spec mulBeforeExponent mulBeforeExponent_spec x y

'''
result=(text[:first]+fallback+'\nend Submission\n\n'+math+wrapper+text[last:]).encode()
assert result.count(b'import ContractTensor')==1 and result.count(b'namespace Submission.R14NatNormal')==2
destination=OUT/'development-combined-add-mul-draft1.lean'
assert not destination.exists();destination.write_bytes(result)
record=dict(at_utc=datetime.now(timezone.utc).isoformat(),state='SIZE_ANALYSIS_DRAFT_NOT_A_CANDIDATE',
            source=destination.relative_to(ROOT).as_posix(),source_sha256=sha(result),bytes=len(result),over_limit=max(0,len(result)-256000),
            parent_add=dict(sha256=sha(add),candidate='f01-r14-dev-word-add-entry1'),
            parent_mul=dict(sha256=sha(mul),candidate='f01-r14-dev-combined-headroom3'),common_removals=removed,
            integration='Reuse the already defined add foundation rounded/carry/mantissa/normal-round/raw-decode/exponent/sign declarations; preserve product-only helper declarations and the complete mul core/model/guard chain. Restore actual public mul before mul_eq/referenceBmm.',
            scope='No Kernel, parent, gate, pin or workflow changed. This oversized analysis draft has not been parsed, compiled or measured; cannot be dispatched as a candidate.')
(OUT/'development-combined-add-mul-composition1.json').write_bytes((json.dumps(record,ensure_ascii=False,indent=2)+'\n').encode())
print(json.dumps({k:v for k,v in record.items() if k not in ('common_removals',)}))
