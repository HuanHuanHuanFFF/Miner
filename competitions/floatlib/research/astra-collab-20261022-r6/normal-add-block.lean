namespace R6NormalAdd

/-- One unsigned interval test for the normal numeric-conversion band. -/
@[inline] def normalOK (u : UInt32) : Bool :=
  (R2W01b.magnitude u - 0x0c000000) < (0x73800000 : UInt32)

theorem normalOK_iff (u : UInt32) : normalOK u = true ↔ R2W01b.NormalBand u := by
  have hu := (R2W01b.magnitude u).toNat_lt_size
  simp only [normalOK, decide_eq_true_eq, R2W01b.NormalBand,
    UInt32.lt_iff_toNat_lt, UInt32.le_iff_toNat_le, UInt32.toNat_sub]
  change (R2W01b.magnitude u).toNat < 4294967296 at hu
  change ((4093640704 + (R2W01b.magnitude u).toNat) % 4294967296 < 1937768448) ↔
    (201326592 ≤ (R2W01b.magnitude u).toNat ∧ (R2W01b.magnitude u).toNat < 2139095040)
  omega

theorem fastOK_of_normalOK (u : UInt32) (h : normalOK u = true) :
    R2W01b.fastOK u = true :=
  (R2W01b.fastOK_iff u).mpr (Or.inr ((normalOK_iff u).mp h))

end R6NormalAdd

/-- Direct numeric addition after two single-compare interval tests. -/
@[inline] def add (x y : Binary32) : Binary32 :=
  if R6NormalAdd.normalOK x.raw.1 && R6NormalAdd.normalOK y.raw.1 then
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 + R2W01b.tableProduct y.raw.1)
  else addR6Parent x y

theorem add_eq_parent (x y : Binary32) : add x y = addR6Parent x y := by
  unfold add
  split
  · rename_i h
    have hx := R6NormalAdd.fastOK_of_normalOK _ (Bool.and_eq_true.mp h).1
    have hy := R6NormalAdd.fastOK_of_normalOK _ (Bool.and_eq_true.mp h).2
    rw [addR6Parent, dif_pos ⟨R6FusedAdd.finite_of_fastOK _ hx,
      R6FusedAdd.finite_of_fastOK _ hy⟩]
    simp only [R2W01b.convert, hx, hy, ite_true]
  · rfl

theorem add_spec (x y : Binary32) : add x y = ExecFloat.Spec.add x y := by
  rw [add_eq_parent]
  exact addR6Parent_spec x y

