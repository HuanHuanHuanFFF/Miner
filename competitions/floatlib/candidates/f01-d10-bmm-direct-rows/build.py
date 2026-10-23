from pathlib import Path
import datetime, hashlib, json

out=Path(__file__).resolve().parent
parent=out.parent/'f01-r8-combined-result-guard/Kernel.lean'
original=parent.read_bytes()
assert hashlib.sha256(original).hexdigest()=='41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7'
assert not (out/'Kernel.lean').exists(), 'Frozen candidates cannot be overwritten'
s=original.decode()
start=s.index('\ndef bmm (batch m n p : Nat)',s.index('end Submission.DirectSmall'))
end=s.index('\nend Submission',start)
old=s[start:end]
renamed=old.replace('def bmm (','def bmmBeforeDirectRows (').replace('theorem bmm_spec','theorem bmmBeforeDirectRows_spec').replace('(bmm batch','(bmmBeforeDirectRows batch').replace('  unfold bmm\n','  unfold bmmBeforeDirectRows\n')
s=s[:start]+renamed+s[end:]
block='''

namespace Submission.DirectRows
open FloatLib.Floats Competition

def core (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  (Vector.ofFn fun r : Fin (batch * m) => r).flatMap fun r =>
    let b := r.val / m
    let i := r.val % m
    let baseA := (b * m + i) * n
    let baseB := b * n * p
    Vector.ofFn fun j : Fin p =>
      NativeFinal.dot n baseA (baseB + j.val) p A.toArray B.toArray

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = DirectSmall.core batch m n p A B := by
  apply Vector.ext
  intro q hq
  have hmp : m * p ≠ 0 := by
    intro h
    have hq' : q < batch * (m * p) := by simpa only [Nat.mul_assoc] using hq
    rw [h, Nat.mul_zero] at hq'
    omega
  have hp : p ≠ 0 := by
    intro h
    apply hmp
    simp only [h, Nat.mul_zero]
  simp only [core, DirectSmall.core, Vector.getElem_flatMap,
    Vector.getElem_ofFn, bmmDecodeC, hmp, hp, if_false,
    Nat.div_div_eq_div_mul, Nat.mul_comm p m,
    Nat.mod_mul_left_div_self, Nat.mod_mul_left_mod]

end Submission.DirectRows

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if n ≤ 4 ∧ 2 < p then DirectRows.core batch m n p A B
  else bmmBeforeDirectRows batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rw [DirectRows.core_eq, DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeDirectRows_spec batch m n p A B

end Submission
'''
data=(s+block).encode()
assert len(data)<=256000
(out/'Kernel.lean').write_bytes(data)
manifest={'candidate':out.name,'candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(data).hexdigest(),'candidate_bytes':len(data),
    'created_at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'parent':parent.parent.name,'parent_sha256':hashlib.sha256(original).hexdigest(),
    'mechanism':'For n<=4 and p>2 only, traverse rows and share batch/row/address decoding across p outputs. Same original NativeFinal.dot, native MAC order and exact NaN replay. Other shapes use unchanged41 dispatcher. Full row-vector allocation remains inside entry.',
    'proof':'Vector.ext and existing rowstream div/mod address identities prove DirectRows.core=DirectSmall.core. No new floating-point equivalence.',
    'validation_mode':'full-gate','proof_status':'NOT_RUN','performance':'UNKNOWN','formal_submission':'NOT_SUBMITTED'}
(out/'manifest.json').write_bytes((json.dumps(manifest,indent=2)+'\n').encode())
print(json.dumps(manifest))
