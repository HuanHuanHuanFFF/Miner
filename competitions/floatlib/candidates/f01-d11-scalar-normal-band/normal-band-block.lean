namespace ScalarNormalBand

open R2W01b

/-- Both magnitudes lie in [0x20000000,0x60000000), using one joint comparison. -/
@[inline] def pairOK (x y : UInt32) : Bool :=
  ((magnitude x - 0x20000000) ||| (magnitude y - 0x20000000)) <
    (0x40000000 : UInt32)

theorem normal_of_shift (u : UInt32)
    (h : (magnitude u - 0x20000000).toNat < 1073741824) : NormalBand u := by
  have hu := (magnitude u).toNat_lt_size
  rw [UInt32.toNat_sub] at h
  simp only [NormalBand, UInt32.le_iff_toNat_le, UInt32.lt_iff_toNat_lt]
  change (magnitude u).toNat < 4294967296 at hu
  change (3758096384 + (magnitude u).toNat) % 4294967296 < 1073741824 at h
  change 201326592 ≤ (magnitude u).toNat ∧ (magnitude u).toNat < 2139095040
  omega

theorem pairOK_normal (x y : UInt32) (h : pairOK x y = true) :
    NormalBand x ∧ NormalBand y := by
  unfold pairOK at h
  simp only [decide_eq_true_eq, UInt32.lt_iff_toNat_lt, UInt32.toNat_or] at h
  refine ⟨normal_of_shift x ?_, normal_of_shift y ?_⟩
  · exact Nat.lt_of_le_of_lt Nat.left_le_or h
  · exact Nat.lt_of_le_of_lt Nat.right_le_or h

theorem table_eq_native (x : Binary32) (hx : NormalBand x.raw.1) :
    tableProduct x.raw.1 = ExecFloat.Binary.toFloat32 x := by
  rw [R2W01c.normal_eq x.raw.1 hx]
  rfl

theorem native_finite (x : Binary32) (hx : NormalBand x.raw.1) :
    (ExecFloat.Binary.toFloat32 x).isFinite = true := by
  rw [← table_eq_native x hx]
  exact R2W01c.normal_finite x.raw.1 hx

end ScalarNormalBand

/-- The narrow ordinary front door bypasses per-decoder and result classification. -/
@[inline] def add (x y : Binary32) : Binary32 :=
  if ScalarNormalBand.pairOK x.raw.1 y.raw.1 then
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 + R2W01b.tableProduct y.raw.1)
  else addBeforeNormalBand x y

theorem add_spec : ∀ x y : Binary32, add x y = ExecFloat.Spec.add x y := by
  intro x y
  unfold add
  split
  · rename_i h
    have hh := ScalarNormalBand.pairOK_normal x.raw.1 y.raw.1 h
    have hx := ScalarNormalBand.native_finite x hh.1
    have hy := ScalarNormalBand.native_finite y hh.2
    rw [ScalarNormalBand.table_eq_native x hh.1, ScalarNormalBand.table_eq_native y hh.2]
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ hx hy,
      GuardBridge.finiteRoundtrip x hx, GuardBridge.finiteRoundtrip y hy]
    exact ExecFloat.Proof.add_eq_spec x y
  · exact addBeforeNormalBand_spec x y

@[inline] def mul (x y : Binary32) : Binary32 :=
  if ScalarNormalBand.pairOK x.raw.1 y.raw.1 then
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 * R2W01b.tableProduct y.raw.1)
  else mulBeforeNormalBand x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  unfold mul
  split
  · rename_i h
    have hh := ScalarNormalBand.pairOK_normal x.raw.1 y.raw.1 h
    have hx := ScalarNormalBand.native_finite x hh.1
    have hy := ScalarNormalBand.native_finite y hh.2
    rw [ScalarNormalBand.table_eq_native x hh.1, ScalarNormalBand.table_eq_native y hh.2]
    rw [NativeBridge.ofFloat32Mul _ _ hx hy,
      GuardBridge.finiteRoundtrip x hx, GuardBridge.finiteRoundtrip y hy]
    exact ExecFloat.Proof.mul_eq_spec x y
  · exact mulBeforeNormalBand_spec x y

