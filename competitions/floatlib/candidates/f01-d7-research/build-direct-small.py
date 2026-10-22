"""Avoid packing/preparation for short inner dimensions or very narrow outputs."""
from pathlib import Path
import json,hashlib,re

ROOT=Path(__file__).resolve().parents[1]
parent=ROOT/'f01-d5-stream-pack/Kernel.lean';raw=parent.read_bytes()
assert hashlib.sha256(raw).hexdigest()=='8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045'
s=raw.decode('utf-8')
pos=s.rindex('def bmm (')
s=s[:pos]+re.sub(r'\bbmm\b','bmmPackedBase',s[pos:]).replace('bmm_spec','bmmPackedBase_spec')
s+='''

namespace Submission.DirectSmall

open FloatLib.Floats Competition

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    NativeFinal.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  unfold core referenceBmm
  apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
  funext q
  dsimp only
  rw [NativeFinal.dot_eq]
  simp only [add_eq, mul_eq]
  apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
  funext acc k
  have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
    (bmmDecodeC m p q.val).2.2
  rw [hi]

end Submission.DirectSmall

namespace Submission

open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if n ≤ 4 ∨ p ≤ 2 then DirectSmall.core batch m n p A B
  else bmmPackedBase batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rw [DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmPackedBase_spec batch m n p A B

end Submission
'''
out=ROOT/'f01-d7-direct-small';out.mkdir(exist_ok=True);payload=s.encode('utf-8');(out/'Kernel.lean').write_bytes(payload)
manifest={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(payload).hexdigest(),'candidate_bytes':len(payload),'validation_mode':'full-gate','proof_status':'NOT_RUN','parent_sha256':hashlib.sha256(raw).hexdigest(),'mechanism':'Shape-only dispatch n<=4 or p<=2 bypasses whole-array nativeA/packedB preparation and row tiles; direct ordered dot uses existing exact native result guard/fallback; other dimensions retain exact original stream-pack path','scope':'General all-input/all-dimension proof, no input data or seed dispatch, no benchmark changes','expected_gain':'UNKNOWN; measure complete preparation plus compute/fallback costs on paired current public-v2','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n','utf-8')
print(json.dumps(manifest))
