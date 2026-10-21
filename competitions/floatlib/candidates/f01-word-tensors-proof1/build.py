"""Build an independent raw-word tensor candidate from the frozen official reference."""
from pathlib import Path
import hashlib,json

OWN=Path(__file__).resolve().parent
TRACK=OWN.parents[1]
base=(TRACK/'references/official-incumbent/Kernel.lean').read_text(encoding='utf-8')
assert hashlib.sha256(base.encode()).hexdigest()=='5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868'
start=base.index('/-- TorchLean\'s sum:')
head,tail=base[:start],base[start:]
tail=tail.replace('def sum {','def referenceSum {').replace('theorem sum_spec :','theorem referenceSum_spec :').replace('sum x = sumSpec','referenceSum x = sumSpec').replace('rw [sum,','rw [referenceSum,')
tail=tail.replace('def bmm (','def referenceBmm (').replace('theorem bmm_spec :','theorem referenceBmm_spec :').replace('(bmm batch','(referenceBmm batch').replace('[bmm, add_eq','[referenceBmm, add_eq')
tail=tail.removesuffix('end Submission\n')
new=r'''
namespace WordTensor

@[inline] def wrap (a : UInt32) : Binary32 := TunedAdd.ofBits a

theorem raw_wrap (a : UInt32) : (wrap a).raw.1 = a := by rfl
theorem wrap_raw (a : Binary32) : wrap a.raw.1 = a := by rfl

@[inline] def wordAdd (a b : UInt32) : UInt32 :=
  if TunedAdd.special a b then (ExecFloat.add (wrap a) (wrap b)).raw.1
  else TunedAdd.core a b

@[inline] def wordMul (a b : UInt32) : UInt32 :=
  if FastMul.special a b then (ExecFloat.mul (wrap a) (wrap b)).raw.1
  else FastMul.core a b

theorem wordAdd_wrap (a b : UInt32) :
    wrap (wordAdd a b) = add (wrap a) (wrap b) := by
  simp only [wordAdd, add, TunedAdd.add, raw_wrap]
  split <;> rfl

theorem wordMul_wrap (a b : UInt32) :
    wrap (wordMul a b) = mul (wrap a) (wrap b) := by
  simp only [wordMul, mul, FastMul.mul, raw_wrap]
  split <;> rfl

theorem fold_word {A : Type} (f : UInt32 → A → UInt32)
    (g : Binary32 → A → Binary32)
    (h : ∀ a x, wrap (f a x) = g (wrap a) x)
    (xs : List A) (a : UInt32) :
    wrap (xs.foldl f a) = xs.foldl g (wrap a) := by
  induction xs generalizing a with
  | nil => rfl
  | cons x xs ih =>
    simp only [List.foldl_cons]
    rw [ih, h]

end WordTensor

def sum {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  WordTensor.wrap (x.foldl (fun acc v => WordTensor.wordAdd acc v.raw.1) 0)

theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := by
  intro n x
  have h : sum x = referenceSum x := by
    unfold sum referenceSum
    rw [← Vector.foldl_toList, ← Vector.foldl_toList]
    apply WordTensor.fold_word
    intro a v
    rw [WordTensor.wordAdd_wrap, WordTensor.wrap_raw]
  exact h.trans (referenceSum_spec n x)

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    WordTensor.wrap (Fin.foldl n
      (fun acc k =>
        WordTensor.wordAdd acc (WordTensor.wordMul
          (A.toArray.getD ((b * m + i) * n + k.val) posZero).raw.1
          (B.toArray.getD ((b * n + k.val) * p + j) posZero).raw.1))
      0)

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : (bmm batch m n p A B).get = (referenceBmm batch m n p A B).get := by
    funext q
    simp only [bmm, referenceBmm, Vector.get, Vector.toArray_ofFn, Array.getElem_ofFn]
    rw [Fin.foldl_eq_finRange_foldl, Fin.foldl_eq_finRange_foldl]
    apply WordTensor.fold_word
    intro a k
    rw [WordTensor.wordAdd_wrap, WordTensor.wordMul_wrap]
    simp only [WordTensor.wrap_raw]
    all_goals rfl
  exact h.trans (referenceBmm_spec batch m n p A B)

end Submission
'''
source=head+tail+new
(OWN/'Kernel.lean').write_bytes(source.encode())
(OWN/'manifest.json').write_text(json.dumps({'candidate':OWN.name,'parent':'official-incumbent','candidate_file':'Kernel.lean','candidate_sha256':hashlib.sha256(source.encode()).hexdigest(),'candidate_bytes':len(source.encode()),'kernel_sha256':hashlib.sha256(source.encode()).hexdigest(),'kernel_bytes':len(source.encode()),'mechanism':'Same scalar algorithms; UInt32 accumulator and intermediate product in tensor loops, full fold-order bridge','proof_status':'NOT_RUN','benchmark':'NOT_RUN','source_attribution':'Official incumbent authors retained in source; raw tensor composition newly authored'},indent=2)+'\n',encoding='utf-8')
print(OWN.name,hashlib.sha256(source.encode()).hexdigest(),len(source.encode()))
