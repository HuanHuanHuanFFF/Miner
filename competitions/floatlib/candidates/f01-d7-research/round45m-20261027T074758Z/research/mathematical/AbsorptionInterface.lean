import ContractTensor

/- Interface only, NOT_RUN. The raw-word scalar soundness bridge is deliberately
   an explicit parameter below; this is NOT a public SUM proof or candidate. -/
namespace R20Absorption
open FloatLib.Floats Competition

def RawSmall (a x : UInt32) : Prop :=
  let e := (a >>> 23) &&& (255 : UInt32)
  (26 : UInt32) ≤ e ∧ e ≤ (254 : UInt32) ∧
    (x &&& (0x7fffffff : UInt32)) < ((e-(25 : UInt32)) <<< 23)

theorem fold_fixed {α β : Type} (step : α → β → α) (a : α) (xs : List β)
    (h : ∀ x ∈ xs, step a x = a) : xs.foldl step a = a := by
  revert h
  induction xs with
  | nil => intro h; rfl
  | cons x xs ih =>
      intro h
      change xs.foldl step (step a x) = a
      rw [h x (by simp)]
      exact ih (fun y hy => h y (by simp [hy]))

theorem sum_block_from_scalar
    (scalar_sound : ∀ a x : Binary32,
      RawSmall a.raw.1 x.raw.1 → ExecFloat.add a x = a)
    (a : Binary32) (xs : List Binary32)
    (h : ∀ x ∈ xs, RawSmall a.raw.1 x.raw.1) :
    xs.foldl ExecFloat.add a = a :=
  fold_fixed ExecFloat.add a xs (fun x hx => scalar_sound a x (h x hx))

/-- Reuse the actual upstream same-sign half-ulp interface, without claiming
    that the new all-sign raw guard has already been connected to it. -/
theorem same_sign_aligned (sign : Bool) (small large gap : Nat) (exponent : Int)
    (hlo : 2^23 ≤ large) (hhi : large < 2^24)
    (hgap : 0 < gap) (hsmall : small < 2^(gap-1))
    (hnormal : -126 ≤ Int.ofNat (23+gap)+exponent)
    (hfinite : Int.ofNat (23+gap)+exponent ≤ 127) :
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundDyadic
      {negative := sign, significand := (large <<< gap)+small, exponent := exponent} =
    FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.mkBits sign
      (Int.toNat (Int.ofNat (23+gap)+exponent+127)) (large-2^23) :=
  FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.roundDyadic_shiftLeft_add_of_lt_half
    sign small large gap exponent hlo hhi hgap hsmall hnormal hfinite

/-- Equal term sequences can share a result without associativity or a change
    in k order. This is the clean interface for exact row/column deduplication. -/
theorem ordered_terms_eq {α β ι : Type} (step : α → β → α)
    (left right : ι → β) (indices : List ι)
    (h : ∀ i ∈ indices, left i = right i) (a : α) :
    indices.foldl (fun acc i => step acc (left i)) a =
      indices.foldl (fun acc i => step acc (right i)) a := by
  revert h a
  induction indices with
  | nil => intro h a; rfl
  | cons i rest ih =>
      intro h a
      change rest.foldl (fun acc j => step acc (left j)) (step a (left i)) =
        rest.foldl (fun acc j => step acc (right j)) (step a (right i))
      rw [h i (by simp)]
      exact ih (fun j hj => h j (by simp [hj])) _

end R20Absorption
