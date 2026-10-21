"""Restructure bmm indexing: loop-invariant bases computed outside the k fold."""
from pathlib import Path
import json,hashlib
OWN=Path(__file__).resolve().parent;TRACK=OWN.parents[1]
base=(TRACK/'references/official-incumbent/Kernel.lean').read_text(encoding='utf-8')
start=base.index('/-- TorchLean\'s batched matmul:');head,tail=base[:start],base[start:]
tail=tail.replace('def bmm (','def referenceBmm (').replace('theorem bmm_spec :','theorem referenceBmm_spec :').replace('(bmm batch','(referenceBmm batch').replace('[bmm, add_eq','[referenceBmm, add_eq').removesuffix('end Submission\n')
new=r'''
theorem index_address (a b c d : Nat) : (a + b) * c + d = (a * c + d) + b * c := by
  rw [Nat.add_mul]
  omega

/-- Preserve every reduction order while moving address products outside the inner loop. -/
def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    let baseA := (b * m + i) * n
    let baseB := b * n * p + j
    Fin.foldl n
      (fun acc k => add acc (mul (A.toArray.getD (baseA + k.val) posZero)
        (B.toArray.getD (baseB + k.val * p) posZero))) posZero

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = referenceBmm batch m n p A B := by
    unfold bmm referenceBmm
    apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
    funext q
    dsimp only
    apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
    funext acc k
    have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
      (bmmDecodeC m p q.val).2.2
    rw [hi]
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceBmm_spec batch m n p A B)

end Submission
'''
source=head+tail+new;(OWN/'Kernel.lean').write_bytes(source.encode())
(OWN/'manifest.json').write_bytes((json.dumps({'candidate':OWN.name,'kernel_sha256':hashlib.sha256(source.encode()).hexdigest(),'kernel_bytes':len(source.encode()),'parent':'official-incumbent','mechanism':'Hoist A/B base addresses out of the k-fold; same Binary32 scalar algorithms and exact reduction order','proof_status':'NOT_RUN','validation_mode':'full-gate'},indent=2)+'\n').encode())
print(OWN.name,hashlib.sha256(source.encode()).hexdigest(),len(source.encode()))
