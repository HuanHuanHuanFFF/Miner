
namespace NativeIndex

theorem addNat (a b : USize) (h : a.toNat + b.toNat < USize.size) :
    (a + b).toNat = a.toNat + b.toNat := by
  rw [USize.toNat_add]
  exact Nat.mod_eq_of_lt h

theorem indexB (base k stride : USize)
    (h : base.toNat + k.toNat * stride.toNat < USize.size) :
    (base + k * stride).toNat = base.toNat + k.toNat * stride.toNat := by
  rw [USize.toNat_add, USize.toNat_mul,
    Nat.mod_eq_of_lt (show k.toNat * stride.toNat < USize.size by omega)]
  exact Nat.mod_eq_of_lt h

theorem stepNat {n k : USize} (hk : k < n) : (k + 1).toNat = k.toNat + 1 := by
  rw [USize.toNat_add, USize.toNat_one]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  have hn := USize.toNat_lt_size n
  exact Nat.mod_eq_of_lt (by omega)

theorem next_decreases {n k : USize} (hk : k < n) :
    n.toNat - (k + 1).toNat < n.toNat - k.toNat := by
  rw [stepNat hk]
  have hkn := USize.lt_iff_toNat_lt.mp hk
  omega

theorem boundA (base n k size : Nat) (h : base + (n - 1) < size) (hk : k < n) :
    base + k < size := by omega

theorem boundB (base n k stride size : Nat)
    (h : base + (n - 1) * stride < size) (hk : k < n) :
    base + k * stride < size := by
  have hm := Nat.mul_le_mul_right stride (show k ≤ n - 1 by omega)
  omega

theorem uget_getD (A : Array Binary32) (i : USize) (h : i.toNat < A.size) :
    A.uget i h = A.getD i.toNat posZero := by
  simp [Array.uget, Array.getD, h]

def loop (n baseA baseB stride : USize) (A B : Array Binary32)
    (hA : baseA.toNat + (n.toNat - 1) < A.size)
    (hB : baseB.toNat + (n.toNat - 1) * stride.toNat < B.size)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size)
    (k : USize) (acc : Float32) : Float32 :=
  if hk : k < n then
    have ha := boundA baseA.toNat n.toNat k.toNat A.size hA (USize.lt_iff_toNat_lt.mp hk)
    have hb := boundB baseB.toNat n.toNat k.toNat stride.toNat B.size hB
      (USize.lt_iff_toNat_lt.mp hk)
    let a := A.uget (baseA + k) (by rw [addNat baseA k (Nat.lt_trans ha hAS)]; exact ha)
    let b := B.uget (baseB + k * stride)
      (by rw [indexB baseB k stride (Nat.lt_trans hb hBS)]; exact hb)
    loop n baseA baseB stride A B hA hB hAS hBS (k + 1)
      (acc + ExecFloat.Binary.toFloat32 a * ExecFloat.Binary.toFloat32 b)
  else acc
termination_by n.toNat - k.toNat
decreasing_by exact next_decreases hk

theorem loop_eq (n baseA baseB stride : USize) (A B : Array Binary32)
    (hA : baseA.toNat + (n.toNat - 1) < A.size)
    (hB : baseB.toNat + (n.toNat - 1) * stride.toNat < B.size)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size)
    (k : USize) (acc : Float32) :
    loop n baseA baseB stride A B hA hB hAS hBS k acc =
      NativeFinal.dotLoop n.toNat baseA.toNat baseB.toNat stride.toNat A B k.toNat acc := by
  rw [loop]
  split
  · rename_i hk
    have hkn := USize.lt_iff_toNat_lt.mp hk
    have ha := boundA baseA.toNat n.toNat k.toNat A.size hA hkn
    have hb := boundB baseB.toNat n.toNat k.toNat stride.toNat B.size hB hkn
    rw [NativeFinal.dotLoop, dif_pos hkn]
    dsimp only
    rw [loop_eq, stepNat hk]
    simp only [uget_getD, addNat baseA k (Nat.lt_trans ha hAS),
      indexB baseB k stride (Nat.lt_trans hb hBS)]
  · rename_i hk
    rw [NativeFinal.dotLoop, dif_neg (by simpa only [USize.lt_iff_toNat_lt] using hk)]
termination_by n.toNat - k.toNat
decreasing_by exact next_decreases hk

@[inline] def within (n baseA baseB stride : Nat) (A B : Array Binary32)
    (hn : n < USize.size) (ha : baseA < USize.size) (hb : baseB < USize.size)
    (hp : stride < USize.size) (hA : baseA + (n - 1) < A.size)
    (hB : baseB + (n - 1) * stride < B.size)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size) : Binary32 :=
  let result := loop (USize.ofNat n) (USize.ofNat baseA) (USize.ofNat baseB)
    (USize.ofNat stride) A B
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' ha] using hA)
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' hb,
      USize.toNat_ofNat_of_lt' hp] using hB) hAS hBS 0 (Float32.ofBits 0)
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else NativeFinal.dot n baseA baseB stride A B

theorem within_eq (n baseA baseB stride : Nat) (A B : Array Binary32)
    (hn : n < USize.size) (ha : baseA < USize.size) (hb : baseB < USize.size)
    (hp : stride < USize.size) (hA : baseA + (n - 1) < A.size)
    (hB : baseB + (n - 1) * stride < B.size)
    (hAS : A.size < USize.size) (hBS : B.size < USize.size) :
    within n baseA baseB stride A B hn ha hb hp hA hB hAS hBS =
      NativeFinal.dot n baseA baseB stride A B := by
  unfold within
  dsimp only
  simp only [loop_eq, USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' ha,
    USize.toNat_ofNat_of_lt' hb, USize.toNat_ofNat_of_lt' hp, USize.toNat_zero]
  unfold NativeFinal.dot
  split <;> simp_all

@[inline] def dot (n baseA baseB stride : Nat) (A B : Array Binary32) : Binary32 :=
  if h : n < USize.size ∧ baseA < USize.size ∧ baseB < USize.size ∧ stride < USize.size ∧
      baseA + (n - 1) < A.size ∧ baseB + (n - 1) * stride < B.size ∧
      A.size < USize.size ∧ B.size < USize.size then
    within n baseA baseB stride A B h.1 h.2.1 h.2.2.1 h.2.2.2.1 h.2.2.2.2.1
      h.2.2.2.2.2.1 h.2.2.2.2.2.2.1 h.2.2.2.2.2.2.2
  else NativeFinal.dot n baseA baseB stride A B

theorem dot_eq (n baseA baseB stride : Nat) (A B : Array Binary32) :
    dot n baseA baseB stride A B = NativeFinal.dot n baseA baseB stride A B := by
  unfold dot
  split
  · rename_i h
    exact within_eq n baseA baseB stride A B h.1 h.2.1 h.2.2.1 h.2.2.2.1
      h.2.2.2.2.1 h.2.2.2.2.2.1 h.2.2.2.2.2.2.1 h.2.2.2.2.2.2.2
  · rfl

end NativeIndex

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    NativeIndex.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = referenceNativeBmm batch m n p A B := by
    unfold bmm referenceNativeBmm
    apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
    funext q
    dsimp only
    exact NativeIndex.dot_eq _ _ _ _ _ _
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceNativeBmm_spec batch m n p A B)
