namespace R6FusedAdd

open FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32

theorem finite_of_fastOK (u : UInt32) (h : R2W01b.fastOK u = true) :
    expField u ≠ 0xff := by
  have hm := R2W01b.magnitude_toNat u
  have he := TunedAdd.expField_toNat u
  have hu := u.toNat_lt_size
  have hb : (R2W01b.magnitude u).toNat < 2139095040 := by
    rcases (R2W01b.fastOK_iff u).mp h with hz | hn
    · rw [hz]; decide
    · have ht := hn.2
      rw [UInt32.lt_iff_toNat_lt] at ht
      exact ht
  intro hf
  have hf' := congrArg UInt32.toNat hf
  change (expField u).toNat = 255 at hf'
  change u.toNat < 4294967296 at hu
  rw [he] at hf'
  norm_num at hf'
  omega

end R6FusedAdd

/-- Fuse conversion eligibility with finiteness on the common numeric-decoding path. -/
@[inline] def add (x y : Binary32) : Binary32 :=
  if R2W01b.fastOK x.raw.1 && R2W01b.fastOK y.raw.1 then
    ExecFloat.Binary.ofFloat32 (R2W01b.tableProduct x.raw.1 + R2W01b.tableProduct y.raw.1)
  else addR6Parent x y

theorem add_eq_parent (x y : Binary32) : add x y = addR6Parent x y := by
  unfold add
  split
  · rename_i h
    have hx := (Bool.and_eq_true.mp h).1
    have hy := (Bool.and_eq_true.mp h).2
    rw [addR6Parent, dif_pos ⟨R6FusedAdd.finite_of_fastOK _ hx,
      R6FusedAdd.finite_of_fastOK _ hy⟩]
    simp only [R2W01b.convert, hx, hy, ite_true]
  · rfl

theorem add_spec (x y : Binary32) : add x y = ExecFloat.Spec.add x y := by
  rw [add_eq_parent]
  exact addR6Parent_spec x y

