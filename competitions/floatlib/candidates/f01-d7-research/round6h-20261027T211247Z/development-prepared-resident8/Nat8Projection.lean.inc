/- Exact8e raw8 projection leaf. NOT_COMPILED, no public BMM proof.
   The only numerical rewrite is the already accepted all-word decoder equality. -/
namespace Submission.R22Resident8Projection
open FloatLib.Floats Competition

abbrev BP := R22Pair8.BP
abbrev Acc := R22Pair8.Cell

@[inline] def projectRow (q : Acc) (r : Fin 4) : R15ThinPairs.F2 :=
  match r.val with
  | 0 => ⟨q.c00, q.c01⟩
  | 1 => ⟨q.c10, q.c11⟩
  | 2 => ⟨q.c20, q.c21⟩
  | _ => ⟨q.c30, q.c31⟩

@[inline] def rowBase (a0 a1 a2 a3 : Nat) (r : Fin 4) : Nat :=
  match r.val with | 0 => a0 | 1 => a1 | 2 => a2 | _ => a3

/- Proof-only view of exactly the existing row-major cache; no runtime pack. -/
def cacheView (n p baseC : Nat) (cache : Array BP) : Vector BP n :=
  Vector.ofFn fun k => cache.getD (baseC + k.val * R22Pair8.groups p) R22Pair8.zeroPair

theorem cacheView_get (n p baseC : Nat) (cache : Array BP) (k : Fin n) :
    (cacheView n p baseC cache).get k =
      cache.getD (baseC + k.val * R22Pair8.groups p) R22Pair8.zeroPair := by
  simp only [cacheView, Packed10.vector_get_ofFn]

theorem decode_eq (a : Binary32) : R2W01b.convert a.raw.1 = ExecFloat.Binary.toFloat32 a := by
  rw [R2W01c.convert_eq]
  rfl

theorem loop_row (n p a0 a1 a2 a3 baseC : Nat) (A : Array Binary32) (cache : Array BP)
    (r : Fin 4) (k : Nat) (q00 q10 q20 q30 q01 q11 q21 q31 : Float32) :
    projectRow (R22Resident8.loop n a0 a1 a2 a3 (R22Pair8.groups p) A cache
      k (baseC + k * R22Pair8.groups p) q00 q10 q20 q30 q01 q11 q21 q31) r =
    R15PackedB2.loop n (rowBase a0 a1 a2 a3 r) A (cacheView n p baseC cache) k
      (projectRow ⟨q00,q10,q20,q30,q01,q11,q21,q31⟩ r).s0
      (projectRow ⟨q00,q10,q20,q30,q01,q11,q21,q31⟩ r).s1 := by
  by_cases hk : k < n
  · rw [R22Resident8.loop, dif_pos hk, R15PackedB2.loop, dif_pos hk]
    dsimp only
    have hstep : baseC + k * R22Pair8.groups p + R22Pair8.groups p =
        baseC + (k + 1) * R22Pair8.groups p := by
      rw [Nat.add_mul, Nat.one_mul]
      omega
    rw [hstep, loop_row n p a0 a1 a2 a3 baseC A cache r (k + 1)]
    simp only [cacheView_get]
    rcases r with ⟨r, hr⟩
    have hcases : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
    rcases hcases with rfl | rfl | rfl | rfl <;>
      simp only [projectRow, rowBase, decode_eq]
  · rw [R22Resident8.loop, dif_neg hk, R15PackedB2.loop, dif_neg hk]
termination_by n - k
decreasing_by omega

/- Only the selected field needs raw-B agreement. The padded right field is
   not required to equal an invalid cross-row/cross-batch raw address. -/
theorem loop_lane (n p a0 a1 a2 a3 baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (r : Fin 4) (c : Fin 2)
    (hread : ∀ i : Fin n,
      R15ThinPairs.select ((cacheView n p baseC cache).get i) c.val =
        ExecFloat.Binary.toFloat32 (B.getD (baseB + c.val + i.val * p) posZero))
    (k : Nat) (q00 q10 q20 q30 q01 q11 q21 q31 : Float32) :
    R15ThinPairs.select (projectRow (R22Resident8.loop n a0 a1 a2 a3
      (R22Pair8.groups p) A cache k (baseC + k * R22Pair8.groups p)
      q00 q10 q20 q30 q01 q11 q21 q31) r) c.val =
    NativeFinal.dotLoop n (rowBase a0 a1 a2 a3 r) (baseB + c.val) p A B k
      (R15ThinPairs.select (projectRow ⟨q00,q10,q20,q30,q01,q11,q21,q31⟩ r) c.val) := by
  rw [loop_row]
  rcases c with ⟨c, hc⟩
  have hcases : c = 0 ∨ c = 1 := by omega
  rcases hcases with rfl | rfl
  · have h0 : ∀ i : Fin n, ((cacheView n p baseC cache).get i).s0 =
        ExecFloat.Binary.toFloat32 (B.getD (baseB + i.val * p) posZero) := by
      intro i
      simpa only [R15ThinPairs.select, ↓reduceIte, Nat.add_zero] using hread i
    simpa only [R15ThinPairs.select, ↓reduceIte, Nat.add_zero] using
      R15PackedB2.loop_s0 n (rowBase a0 a1 a2 a3 r) baseB p A B
        (cacheView n p baseC cache) h0 k
        (projectRow ⟨q00,q10,q20,q30,q01,q11,q21,q31⟩ r).s0
        (projectRow ⟨q00,q10,q20,q30,q01,q11,q21,q31⟩ r).s1
  · have h1 : ∀ i : Fin n, ((cacheView n p baseC cache).get i).s1 =
        ExecFloat.Binary.toFloat32 (B.getD (baseB + 1 + i.val * p) posZero) := by
      intro i
      simpa only [R15ThinPairs.select, if_neg Nat.one_ne_zero] using hread i
    simpa only [R15ThinPairs.select, if_neg Nat.one_ne_zero] using
      R15PackedB2.loop_s1 n (rowBase a0 a1 a2 a3 r) (baseB + 1) p A B
        (cacheView n p baseC cache) h1 k
        (projectRow ⟨q00,q10,q20,q30,q01,q11,q21,q31⟩ r).s0
        (projectRow ⟨q00,q10,q20,q30,q01,q11,q21,q31⟩ r).s1

end Submission.R22Resident8Projection
