"""Restructure bmm indexing: loop-invariant bases computed outside the k fold."""
from pathlib import Path
import json,hashlib
OWN=Path(__file__).resolve().parent;TRACK=OWN.parents[1]
base=(TRACK/'references/official-incumbent/Kernel.lean').read_text(encoding='utf-8')
start=base.index('/-- TorchLean\'s batched matmul:');head,tail=base[:start],base[start:]
tail=tail.replace('def bmm (','def referenceBmm (').replace('theorem bmm_spec :','theorem referenceBmm_spec :').replace('(bmm batch','(referenceBmm batch').replace('[bmm, add_eq','[referenceBmm, add_eq').removesuffix('end Submission\n')
new=r'''
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
  have h : (bmm batch m n p A B).get = (referenceBmm batch m n p A B).get := by
    funext q
    simp only [bmm, referenceBmm, Vector.get, Vector.toArray_ofFn, Array.getElem_ofFn,
      Nat.add_mul, Nat.add_assoc, Nat.add_left_comm, Nat.add_comm]
  exact h.trans (referenceBmm_spec batch m n p A B)

end Submission
'''
source=head+tail+new;(OWN/'Kernel.lean').write_bytes(source.encode())
(OWN/'manifest.json').write_bytes((json.dumps({'candidate':OWN.name,'kernel_sha256':hashlib.sha256(source.encode()).hexdigest(),'kernel_bytes':len(source.encode()),'parent':'official-incumbent','mechanism':'Hoist A/B base addresses out of the k-fold; same Binary32 scalar algorithms and exact reduction order','proof_status':'NOT_RUN','validation_mode':'statement-only'},indent=2)+'\n').encode())
print(OWN.name,hashlib.sha256(source.encode()).hexdigest(),len(source.encode()))
