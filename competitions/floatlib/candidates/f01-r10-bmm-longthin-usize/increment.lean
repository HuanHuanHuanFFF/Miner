/- R10: machine indices for the existing long-thin DirectSmall path.
   Floating arithmetic, the final NaN decision and exact raw replay are unchanged. -/
namespace Submission.R10DirectMachine

open FloatLib.Floats Competition

theorem row_lt (b i batch width : Nat) (hb : b < batch) (hi : i < width) :
    b * width + i < batch * width := by
  have hnext : b + 1 ≤ batch := by omega
  have hbound := Nat.mul_le_mul_right width hnext
  rw [Nat.add_mul, Nat.one_mul] at hbound
  have hstep := Nat.add_lt_add_left hi (b * width)
  omega

theorem matrix_bounds (batch m n p : Nat) (q : Fin (batch * m * p))
    (k : Nat) (hk : k < n) :
    let d := bmmDecodeC m p q.val
    ((d.1 * m + d.2.1) * n + k < batch * m * n) ∧
      (d.1 * n * p + d.2.2 + k * p < batch * n * p) := by
  dsimp only
  have hd := Packed10.decode_bounds batch m p q
  constructor
  · exact row_lt _ k (batch * m) n
      (row_lt _ _ batch m hd.1 hd.2.1) hk
  · rw [← index_address ((bmmDecodeC m p q.val).1 * n) k p
      (bmmDecodeC m p q.val).2.2]
    exact row_lt _ _ (batch * n) p (row_lt _ k batch n hd.1 hk) hd.2.2

theorem strided_nat (base k stride : USize)
    (h : base.toNat + k.toNat * stride.toNat < USize.size) :
    (base + k * stride).toNat = base.toNat + k.toNat * stride.toNat := by
  have hmul : k.toNat * stride.toNat < USize.size := by omega
  have hmul_eq : (k * stride).toNat = k.toNat * stride.toNat := by
    rw [USize.toNat_mul]
    exact Nat.mod_eq_of_lt hmul
  rw [USize.toNat_add, hmul_eq]
  exact Nat.mod_eq_of_lt h

theorem raw_uget_eq_getD (A : Array Binary32) (i : USize) (h : i.toNat < A.size) :
    A.uget i h = A.getD i.toNat posZero := by
  simp [Array.uget, Array.getD, h]

def loop (count baseA baseB stride : USize) (A B : Array Binary32)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size)
    (bounds : ∀ j : Nat, j < count.toNat →
      baseA.toNat + j < A.size ∧ baseB.toNat + j * stride.toNat < B.size)
    (k : USize) (acc : Float32) : Float32 :=
  if hk : k < count then
    have hkn : k.toNat < count.toNat := USize.lt_iff_toNat_lt.mp hk
    have ha := (bounds k.toNat hkn).1
    have hb := (bounds k.toNat hkn).2
    have hia := Packed10Index.addNat baseA k (Nat.lt_trans ha hAS)
    have hib := strided_nat baseB k stride (Nat.lt_trans hb hBS)
    let x := A.uget (baseA + k) (by rw [hia]; exact ha)
    let y := B.uget (baseB + k * stride) (by rw [hib]; exact hb)
    let product := ExecFloat.Binary.toFloat32 x * ExecFloat.Binary.toFloat32 y
    loop count baseA baseB stride A B hAS hBS bounds (k + 1) (acc + product)
  else acc
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

theorem loop_eq (count baseA baseB stride : USize) (A B : Array Binary32)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size)
    (bounds : ∀ j : Nat, j < count.toNat →
      baseA.toNat + j < A.size ∧ baseB.toNat + j * stride.toNat < B.size)
    (k : USize) (acc : Float32) :
    loop count baseA baseB stride A B hAS hBS bounds k acc =
      NativeFinal.dotLoop count.toNat baseA.toNat baseB.toNat stride.toNat A B k.toNat acc := by
  rw [loop]
  split
  · rename_i hk
    have hkn : k.toNat < count.toNat := USize.lt_iff_toNat_lt.mp hk
    have ha := (bounds k.toNat hkn).1
    have hb := (bounds k.toNat hkn).2
    have hia := Packed10Index.addNat baseA k (Nat.lt_trans ha hAS)
    have hib := strided_nat baseB k stride (Nat.lt_trans hb hBS)
    rw [NativeFinal.dotLoop, dif_pos hkn]
    dsimp only
    rw [loop_eq, Packed10Index.stepNat hk]
    simp only [raw_uget_eq_getD, hia, hib]
  · rename_i hk
    have hkn : ¬ k.toNat < count.toNat := by
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [NativeFinal.dotLoop, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

def nativeWithin (n baseA baseB p : Nat) (A B : Array Binary32)
    (hn : n < USize.size) (hp : p < USize.size)
    (ha : baseA < USize.size) (hb : baseB < USize.size)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size)
    (bounds : ∀ j : Nat, j < n → baseA + j < A.size ∧ baseB + j * p < B.size) : Float32 :=
  loop (USize.ofNat n) (USize.ofNat baseA) (USize.ofNat baseB) (USize.ofNat p) A B hAS hBS
    (by
      intro j hj
      have hjn : j < n := by simpa only [USize.toNat_ofNat_of_lt' hn] using hj
      simpa only [USize.toNat_ofNat_of_lt' ha, USize.toNat_ofNat_of_lt' hb,
        USize.toNat_ofNat_of_lt' hp] using bounds j hjn)
    0 (Float32.ofBits 0)

theorem nativeWithin_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (hn : n < USize.size) (hp : p < USize.size)
    (ha : baseA < USize.size) (hb : baseB < USize.size)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size)
    (bounds : ∀ j : Nat, j < n → baseA + j < A.size ∧ baseB + j * p < B.size) :
    nativeWithin n baseA baseB p A B hn hp ha hb hAS hBS bounds =
      NativeFinal.dotLoop n baseA baseB p A B 0 (Float32.ofBits 0) := by
  unfold nativeWithin
  rw [loop_eq]
  simp only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' ha,
    USize.toNat_ofNat_of_lt' hb, USize.toNat_ofNat_of_lt' hp, USize.toNat_zero]

def dotWithin (n baseA baseB p : Nat) (A B : Array Binary32)
    (hn : n < USize.size) (hp : p < USize.size)
    (ha : baseA < USize.size) (hb : baseB < USize.size)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size)
    (bounds : ∀ j : Nat, j < n → baseA + j < A.size ∧ baseB + j * p < B.size) : Binary32 :=
  let result := nativeWithin n baseA baseB p A B hn hp ha hb hAS hBS bounds
  if hf : result.isNaN = false then ExecFloat.Binary.ofFloat32 result
  else R7NaNReplay.replayEarly n baseA baseB p A B

theorem dotWithin_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (hn : n < USize.size) (hp : p < USize.size)
    (ha : baseA < USize.size) (hb : baseB < USize.size)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size)
    (bounds : ∀ j : Nat, j < n → baseA + j < A.size ∧ baseB + j * p < B.size) :
    dotWithin n baseA baseB p A B hn hp ha hb hAS hBS bounds = NativeFinal.dot n baseA baseB p A B := by
  unfold dotWithin NativeFinal.dot
  rw [nativeWithin_eq]

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (hpos : 0 < n) (hn : n < USize.size) (hp : p < USize.size)
    (hAS : A.toArray.size < USize.size) (hBS : B.toArray.size < USize.size) :
    Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let d := bmmDecodeC m p q.val
    let baseA := (d.1 * m + d.2.1) * n
    let baseB := d.1 * n * p + d.2.2
    have bounds : ∀ j : Nat, j < n →
        baseA + j < A.toArray.size ∧ baseB + j * p < B.toArray.size := by
      intro j hj
      simpa only [A.size_toArray, B.size_toArray] using matrix_bounds batch m n p q j hj
    have ha0 : baseA < A.toArray.size := by simpa only [Nat.add_zero] using (bounds 0 hpos).1
    have hb0 : baseB < B.toArray.size := by
      simpa only [Nat.zero_mul, Nat.add_zero] using (bounds 0 hpos).2
    dotWithin n baseA baseB p A.toArray B.toArray hn hp
      (Nat.lt_trans ha0 hAS) (Nat.lt_trans hb0 hBS) hAS hBS bounds

theorem core_eq_direct (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (hpos : 0 < n) (hn : n < USize.size) (hp : p < USize.size)
    (hAS : A.toArray.size < USize.size) (hBS : B.toArray.size < USize.size) :
    core batch m n p A B hpos hn hp hAS hBS = DirectSmall.core batch m n p A B := by
  unfold core DirectSmall.core
  apply congrArg (fun f : Fin (batch * m * p) → Binary32 => Vector.ofFn f)
  funext q
  dsimp only
  apply dotWithin_eq

end Submission.R10DirectMachine

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if h : 4 < n ∧ p ≤ 2 ∧ n < USize.size ∧ p < USize.size ∧
      A.toArray.size < USize.size ∧ B.toArray.size < USize.size then
    R10DirectMachine.core batch m n p A B (Nat.lt_trans (by decide : 0 < 4) h.1)
      h.2.2.1 h.2.2.2.1 h.2.2.2.2.1 h.2.2.2.2.2
  else bmmBeforeR10Machine batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rw [R10DirectMachine.core_eq_direct, DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeR10Machine_spec batch m n p A B

end Submission
