/- Four-column assets adapted from f01-d7-width4-proof2 (96131686),
validated there under 4b7/public-v2. The current complete integration is NOT_RUN. -/
namespace Packed4
open Packed10 (vector_get_ofFn)
structure F4 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32
abbrev zero32 : Float32 := Packed10.zero32
@[inline] def zero4 : F4 := ⟨zero32, zero32, zero32, zero32⟩
@[inline] def lane (v : F4) (l : Fin 4) : Float32 :=
  match l.val with
  | 0 => v.s0
  | 1 => v.s1
  | 2 => v.s2
  | _ => v.s3
@[inline] def packet (read : Nat → Float32) (col : Nat) : F4 :=
  ⟨read col, read (col + 1), read (col + 2), read (col + 3)⟩
@[inline] def update (acc : F4) (a : Float32) (v : F4) : F4 :=
  ⟨acc.s0 + a * v.s0, acc.s1 + a * v.s1, acc.s2 + a * v.s2, acc.s3 + a * v.s3⟩
theorem lane_packet (read : Nat → Float32) (col : Nat) (l : Fin 4) :
    lane (packet read col) l = read (col + l.val) := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;> rfl
theorem lane_zero4 (l : Fin 4) : lane zero4 l = zero32 := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;> rfl
theorem lane_update (acc : F4) (a : Float32) (v : F4) (l : Fin 4) :
    lane (update acc a v) l = lane acc l + a * lane v l := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;> rfl
@[inline] def groups (p : Nat) : Nat := (p + 3) / 4
def packB (batch n p : Nat) (B : Vector Binary32 (batch * n * p)) :
    Vector (Vector (Vector F4 n) (groups p)) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun g =>
      Vector.ofFn fun k =>
        let base := (b.val * n + k.val) * p
        packet (fun j =>
          if hj : j < p then
            have hbn : (b.val + 1) * n ≤ batch * n := Nat.mul_le_mul_right n b.isLt
            have hbk : b.val * n + k.val < batch * n := by
              rw [Nat.add_mul] at hbn
              omega
            have hp : (b.val * n + k.val + 1) * p ≤ batch * n * p :=
              Nat.mul_le_mul_right p (Nat.succ_le_of_lt hbk)
            have hi : base + j < B.toArray.size := by
              rw [B.size_toArray]
              dsimp [base]
              rw [Nat.add_mul] at hp
              omega
            ExecFloat.Binary.toFloat32 B.toArray[base + j]
          else zero32) (4 * g.val)
theorem packB_get (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (g : Fin (groups p)) (k : Fin n) :
    (((packB batch n p B).get b).get g).get k =
      packet (fun j =>
        if j < p then
          ExecFloat.Binary.toFloat32
            (B.toArray.getD ((b.val * n + k.val) * p + j) posZero)
        else zero32) (4 * g.val) := by
  simp only [packB, vector_get_ofFn]
  congr 1
  funext j
  split
  · rename_i hj
    have hbn : (b.val + 1) * n ≤ batch * n := Nat.mul_le_mul_right n b.isLt
    have hbk : b.val * n + k.val < batch * n := by
      rw [Nat.add_mul] at hbn
      omega
    have hp : (b.val * n + k.val + 1) * p ≤ batch * n * p :=
      Nat.mul_le_mul_right p (Nat.succ_le_of_lt hbk)
    have hi : (b.val * n + k.val) * p + j < B.toArray.size := by
      rw [B.size_toArray]
      rw [Nat.add_mul] at hp
      omega
    have hidx : (b.val * n + k.val) * p + j < batch * n * p := by
      simpa only [B.size_toArray] using hi
    simp [Array.getD, hidx, hj]
  · rename_i hj
    simp only [dif_neg hj, if_neg hj]
theorem packB_lane (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (g : Fin (groups p)) (k : Fin n) (l : Fin 4)
    (hcol : 4 * g.val + l.val < p) :
    lane ((((packB batch n p B).get b).get g).get k) l =
      ExecFloat.Binary.toFloat32
        (B.toArray.getD
          ((b.val * n + k.val) * p + (4 * g.val + l.val)) posZero) := by
  rw [packB_get, lane_packet, if_pos hcol]
end Packed4
namespace Packed4
open Packed10 (nativeA_getD)
def dot4 (n baseA : Nat) (A : Array Float32) (B : Vector F4 n)
    (k : Nat) (s0 s1 s2 s3 : Float32) : F4 :=
  if hk : k < n then
    let sharedA := A.getD (baseA + k) zero32
    let v := B.get ⟨k, hk⟩
    dot4 n baseA A B (k + 1)
      (s0 + sharedA * v.s0)
      (s1 + sharedA * v.s1)
      (s2 + sharedA * v.s2)
      (s3 + sharedA * v.s3)
  else ⟨s0, s1, s2, s3⟩
termination_by n - k
theorem dot4_lane (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F4 n) (l : Fin 4)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero))
    (k : Nat) (s0 s1 s2 s3 : Float32) :
    lane (dot4 n baseA (Araw.map ExecFloat.Binary.toFloat32) B k s0 s1 s2 s3) l =
      NativeFinal.dotLoop n baseA baseB p Araw Braw k (lane ⟨s0, s1, s2, s3⟩ l) := by
  by_cases hk : k < n
  · rw [dot4, NativeFinal.dotLoop]
    simp only [dif_pos hk, if_pos hk]
    try dsimp only
    have ih := dot4_lane n baseA baseB p Araw Braw B l hb (k + 1)
      (s0 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s0)
      (s1 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s1)
      (s2 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s2)
      (s3 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s3)
    have hacc :
        lane ⟨s0 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s0, s1 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s1, s2 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s2, s3 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 * (B.get ⟨k, hk⟩).s3⟩ l =
          lane ⟨s0, s1, s2, s3⟩ l +
            ExecFloat.Binary.toFloat32 (Araw.getD (baseA + k) posZero) *
              ExecFloat.Binary.toFloat32 (Braw.getD (baseB + k * p) posZero) := by
      change lane (update ⟨s0, s1, s2, s3⟩
        ((Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32)
        (B.get ⟨k, hk⟩)) l = _
      rw [lane_update, nativeA_getD, hb ⟨k, hk⟩]
    rw [hacc] at ih
    exact ih
  · rw [dot4, NativeFinal.dotLoop]
    simp only [dif_neg hk, if_neg hk]
termination_by n - k
end Packed4
namespace Packed4Index
open Packed4
open Packed10Index (addNat stepNat next_decreases boundA ugetA_getD)
theorem ugetB_get {n : Nat} (B : Vector F4 n) (i : USize)
    (hi : i.toNat < n) :
    B.toArray.uget i (by simpa only [B.size_toArray] using hi) =
      B.get ⟨i.toNat, hi⟩ := by
  rfl
/-- The bounds are established once; each iteration reads with machine-word indices. -/
def loop {n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F4 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 : Float32) : F4 :=
  if hk : k < count then
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    let a := A.uget (baseA + k)
      (by rw [addNat baseA k (Nat.lt_trans ha hAS)]; exact ha)
    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    loop count baseA A B hn hA hAS (k + 1)
      (s0 + a * v.s0) (s1 + a * v.s1)
      (s2 + a * v.s2) (s3 + a * v.s3)
  else ⟨s0, s1, s2, s3⟩
termination_by count.toNat - k.toNat
decreasing_by
  apply next_decreases
  assumption
theorem loop_eq {n : Nat} (count baseA : USize) (A : Array Float32) (B : Vector F4 n)
    (hn : count.toNat = n)
    (hA : baseA.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 : Float32) :
    loop count baseA A B hn hA hAS k s0 s1 s2 s3 =
      Packed4.dot4 n baseA.toNat A B k.toNat s0 s1 s2 s3 := by
  rw [loop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat count.toNat k.toNat A.size hA
      (USize.lt_iff_toNat_lt.mp hk)
    rw [Packed4.dot4, dif_pos hkn]
    dsimp only
    rw [loop_eq, stepNat hk]
    simp only [ugetA_getD, addNat baseA k (Nat.lt_trans ha hAS), ugetB_get]
    rfl
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [Packed4.dot4, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by
  apply next_decreases
  assumption
@[inline] def within (n baseA : Nat) (A : Array Float32) (B : Vector F4 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) : F4 :=
  loop (USize.ofNat n) (USize.ofNat baseA) A B
    (USize.toNat_ofNat_of_lt' hn)
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' ha] using hA)
    hAS 0 zero32 zero32 zero32 zero32
theorem within_eq (n baseA : Nat) (A : Array Float32) (B : Vector F4 n)
    (hn : n < USize.size) (ha : baseA < USize.size)
    (hA : baseA + (n - 1) < A.size) (hAS : A.size < USize.size) :
    within n baseA A B hn ha hA hAS =
      Packed4.dot4 n baseA A B 0 zero32 zero32 zero32 zero32 := by
  simp only [within, loop_eq, USize.toNat_ofNat_of_lt' hn,
    USize.toNat_ofNat_of_lt' ha, USize.toNat_zero]
@[inline] def runDot (n baseA : Nat) (A : Array Float32) (B : Vector F4 n) : F4 :=
  if h : n < USize.size ∧ baseA < USize.size ∧
      baseA + (n - 1) < A.size ∧ A.size < USize.size then
    within n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  else Packed4.dot4 n baseA A B 0 zero32 zero32 zero32 zero32
theorem runDot_eq (n baseA : Nat) (A : Array Float32) (B : Vector F4 n) :
    runDot n baseA A B =
      Packed4.dot4 n baseA A B 0 zero32 zero32 zero32 zero32 := by
  unfold runDot
  split
  · rename_i h
    exact within_eq n baseA A B h.1 h.2.1 h.2.2.1 h.2.2.2
  · rfl
end Packed4Index
