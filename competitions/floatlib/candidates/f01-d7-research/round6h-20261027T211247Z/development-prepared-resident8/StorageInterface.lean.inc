/- Separate reusable proof/interface attempt. NOT_COMPILED; not in timed source.
   Cost must be established before extending this into a whole-output proof. -/
namespace Submission.R22Resident16
open FloatLib.Floats Competition

@[inline] def laneA (v : A4) (r : Fin 4) : Float32 :=
  match r.val with | 0 => v.r0 | 1 => v.r1 | 2 => v.r2 | _ => v.r3

@[inline] def laneB (v : B4) (c : Fin 4) : Float32 :=
  match c.val with | 0 => v.s0 | 1 => v.s1 | 2 => v.s2 | _ => v.s3

@[inline] def laneQ (v : Acc) (r c : Fin 4) : Float32 :=
  match c.val with
  | 0 => match r.val with | 0 => v.q00 | 1 => v.q10 | 2 => v.q20 | _ => v.q30
  | 1 => match r.val with | 0 => v.q01 | 1 => v.q11 | 2 => v.q21 | _ => v.q31
  | 2 => match r.val with | 0 => v.q02 | 1 => v.q12 | 2 => v.q22 | _ => v.q32
  | _ => match r.val with | 0 => v.q03 | 1 => v.q13 | 2 => v.q23 | _ => v.q33

theorem packA_lane (n base : Nat) (A : Array Binary32) (r : Fin 4) (k : Fin n) :
    laneA ((packA n base A).get k) r =
      ExecFloat.Binary.toFloat32 (A.getD (base + r.val * n + k.val) posZero) := by
  simp only [packA, Packed10.vector_get_ofFn]
  rcases r with ⟨r, hr⟩
  have h : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;>
    simp only [laneA, Nat.zero_mul, Nat.one_mul, Nat.add_zero]

theorem packBGroup_lane (n p base valid : Nat) (B : Array Binary32)
    (c : Fin 4) (hc : c.val < valid) (k : Fin n) :
    laneB ((packBGroup n p base B valid).get k) c =
      ExecFloat.Binary.toFloat32 (B.getD (base + k.val * p + c.val) posZero) := by
  simp only [packBGroup, Packed10.vector_get_ofFn]
  rcases c with ⟨c, h4⟩
  have h : c = 0 ∨ c = 1 ∨ c = 2 ∨ c = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;>
    simp only [laneB, Nat.add_zero] <;> simp_all

def scalarLoop (n : Nat) (A : Vector A4 n) (B : Vector B4 n)
    (r c : Fin 4) (k : Nat) (q : Float32) : Float32 :=
  if hk : k < n then
    scalarLoop n A B r c (k + 1)
      (q + laneA (A.get ⟨k, hk⟩) r * laneB (B.get ⟨k, hk⟩) c)
  else q
termination_by n - k

theorem scalarLoop_raw (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (A : Vector A4 n) (B : Vector B4 n) (r c : Fin 4)
    (hA : ∀ i : Fin n, laneA (A.get i) r =
      ExecFloat.Binary.toFloat32 (Araw.getD (baseA + i.val) posZero))
    (hB : ∀ i : Fin n, laneB (B.get i) c =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero))
    (k : Nat) (q : Float32) :
    scalarLoop n A B r c k q = NativeFinal.dotLoop n baseA baseB p Araw Braw k q := by
  by_cases hk : k < n
  · rw [scalarLoop, NativeFinal.dotLoop]
    simp only [dif_pos hk]
    rw [hA ⟨k, hk⟩, hB ⟨k, hk⟩]
    exact scalarLoop_raw n baseA baseB p Araw Braw A B r c hA hB (k + 1) _
  · rw [scalarLoop, NativeFinal.dotLoop]
    simp only [dif_neg hk]
termination_by n - k

/- Remaining active-runtime obligations (not axioms or admitted declarations):
1. wordLoop projection to scalarLoop for sixteen native scalar parameters.
2. packBData get at tileIndex equals packBGroup at the exact raw batch/group base.
3. runDot projection; lane-specific Packed10.finish_eq_dot.
4. Words read/tiles relation; RowStream prefix for four rows, then raw tail.
5. Whole output/reference and guarded_spec; full exact source/replay/axiom gate.
These do not follow from this file existing or from finite address checks. -/

end Submission.R22Resident16
