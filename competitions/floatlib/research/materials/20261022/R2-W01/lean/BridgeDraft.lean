import ContractTensor

/-!
UNCOMPILED DRAFT, pinned FloatLib 0d91825727839f597fd06b22fdd038ea21480f0c.
No Lean executable was found. These wrappers do not prove the missing fixed-binade
rounding lemma or the executable block-certificate checker. They isolate that work.
-/

namespace R2W01BridgeDraft

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.Flocq

private abbrev plan32 : Configured.StoragePlan FloatFormat.binary32 :=
  .word32 (by decide)

/-- The contract operation reaches the descriptor model through the lossless codec.
The native binary32 capability fixes its `spec` field to `Configured.Spec.add`.
This is deliberately about `ExecFloat.add`, not the separate explicitly rounded
`ExecFloat.Binary.add` API. -/
theorem toModel_exec_add (x y : Competition.Binary32) :
    ExecFloat.Binary.toModel (ExecFloat.add x y) =
      Model.add (ExecFloat.Binary.toModel x) (ExecFloat.Binary.toModel y) := by
  rw [ExecFloat.Proof.add_eq_spec, Model.Proof.add_eq_spec]
  exact ExecFloat.ModelCodec.decode_liftBinary
    (plan := plan32) Model.Spec.add x y

/-- A finite nonzero model-value equality restores all configured bits. -/
theorem eq_of_nonzero_model_real {x y : Competition.Binary32}
    (hx : Model.isFinite (ExecFloat.Binary.toModel x) = true)
    (hy : Model.isFinite (ExecFloat.Binary.toModel y) = true)
    (hvalue : Model.toReal (ExecFloat.Binary.toModel x) =
      Model.toReal (ExecFloat.Binary.toModel y))
    (hzero : Model.toReal (ExecFloat.Binary.toModel x) ≠ 0) : x = y := by
  apply (ExecFloat.Binary.toModel_inj).mp
  exact Model.eq_of_toReal_eq_of_nonzero hx hy hvalue hzero

/-- The exact point where a fixed-grid rounding proof can enter the scalar model.
`hround` is the unproved, application-specific binade theorem. -/
theorem model_add_eq_from_roundAt {fmt : FloatFormat} (x y z : Model fmt)
    (hfmt : fmt.isIEEE = true)
    (hx : Model.isFinite x = true) (hy : Model.isFinite y = true)
    (hfin : Model.isFinite (Model.add x y) = true)
    (hz : Model.isFinite z = true)
    (hround : Model.roundAt fmt (Model.toReal x + Model.toReal y) = Model.toReal z)
    (hnonzero : Model.toReal z ≠ 0) : Model.add x y = z := by
  have hv : Model.toReal (Model.add x y) = Model.toReal z :=
    (Model.toReal_add_eq_roundAt x y hfmt hx hy hfin).trans hround
  exact Model.eq_of_toReal_eq_of_nonzero hfin hz hv (hv.trans_ne hnonzero)

/-- Symbolic no-overflow can replace observation of the reference addition result.
For the proposed positive-binade region, `hbound` follows from its endpoint bound. -/
theorem model_add_eq_from_bound_and_roundAt {fmt : FloatFormat} (x y z : Model fmt)
    (hfmt : fmt.isIEEE = true)
    (hx : Model.isFinite x = true) (hy : Model.isFinite y = true)
    (hbound : |Model.toReal x + Model.toReal y| ≤ Model.toReal (Model.posMaxFinite fmt))
    (hz : Model.isFinite z = true)
    (hround : Model.roundAt fmt (Model.toReal x + Model.toReal y) = Model.toReal z)
    (hnonzero : Model.toReal z ≠ 0) : Model.add x y = z := by
  exact model_add_eq_from_roundAt x y z hfmt hx hy
    (Model.isFinite_add_of_abs_toReal_add_le_posMaxFinite x y hfmt hx hy hbound)
    hz hround hnonzero

/-- The only state-dependent part of fixed-grid nearest-even rounding is the
parity of the complete floor, which is `K + floor(x/q)`, not merely `floor(x/q)`. -/
theorem nearestEven_eq_floor_plus_increment (v r : ℝ) (z : ℤ)
    (hfloor : ⌊v⌋ = z) (hfrac : v - (z : ℝ) = r) :
    nearestEven v = z +
      (if r < 1 / 2 then (0 : ℤ)
       else if 1 / 2 < r then 1
       else if Even z then 0 else 1) := by
  simp only [nearestEven, hfloor, hfrac]
  split_ifs <;> omega

/-- Standard list induction lifts a verified state-machine step to the ordered fold.
Choose `I` to include the current binade, exact encoding relation, and the remaining
certificate. No change of addition order is used. -/
theorem foldl_simulation {S A : Type}
    (repr : S → Competition.Binary32) (step : S → A → S)
    (term : A → Competition.Binary32) (I : S → Prop)
    (hstep : ∀ s a, I s →
      I (step s a) ∧ repr (step s a) = ExecFloat.add (repr s) (term a))
    (xs : List A) (s : S) (hs : I s) :
    repr (xs.foldl step s) =
      xs.foldl (fun acc a => ExecFloat.add acc (term a)) (repr s) := by
  induction xs generalizing s with
  | nil => rfl
  | cons a xs ih =>
      simp only [List.foldl_cons]
      rw [ih (step s a) (hstep s a hs).1, (hstep s a hs).2]

/-- A boolean guard with an in-scope equality certificate preserves the complete
contract, including all exceptional inputs routed to the original reference. -/
theorem guarded_sum_obligation
    (fast : {n : Nat} → Vector Competition.Binary32 n → Competition.Binary32)
    (guard : {n : Nat} → Vector Competition.Binary32 n → Bool)
    (hsound : ∀ (n : Nat) (x : Vector Competition.Binary32 n),
      guard x = true → fast x = Competition.sumSpec x.get) :
    Competition.SumObligation
      (fun x => if guard x then fast x else Competition.sumSpec x.get) := by
  intro n x
  by_cases h : guard x = true
  · simpa [h] using hsound n x h
  · simp [h]

end R2W01BridgeDraft
