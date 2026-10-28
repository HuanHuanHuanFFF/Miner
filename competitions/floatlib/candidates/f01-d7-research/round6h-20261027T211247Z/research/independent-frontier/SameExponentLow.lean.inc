/- R22 E0/E254 field-level extension, NOT_RUN; no public ADD change. -/
namespace Submission.R22SameExponentMath
open FloatLib.Floats FloatLib.Numerics
open FloatLib.Floats.Formats.BinaryInterchange

theorem native_low_lattice (s : Bool) (n : Nat) (hn : n < 16777216) :
    Model.NativeBinary32.roundDyadic ⟨s, n, -149⟩ =
      Model.NativeBinary32.mkBits s (n / 8388608) (n % 8388608) := by
  by_cases hz : n = 0
  · subst n
    cases s <;> rfl
  by_cases hlo : n < 8388608
  · have hlog : n.log2 < 23 := (Nat.log2_lt hz).2 hlo
    have htotal : (n.log2 : Int) + (-149) < -126 := by omega
    have hne : n ≠ 8388608 := by omega
    simp [Model.NativeBinary32.roundDyadic, hz, htotal,
      Model.pow2_eq_two_pow, hne, Nat.div_eq_of_lt hlo, Nat.mod_eq_of_lt hlo]
  · have hlog : n.log2 = 23 := by
      apply (Nat.log2_eq_iff hz).2
      norm_num
      omega
    have hr : rounded n = n := by simp [rounded, hlog]
    have hc : carry n = 0 := by simp [carry, hr, show n ≠ 16777216 by omega]
    have hm : mantissa n = n := by simp [mantissa, hr, show n ≠ 16777216 by omega]
    have hd : n / 8388608 = 1 := by omega
    have hmod : n % 8388608 = n - 8388608 := by omega
    rw [nativeNormal s n (-149) hz (by omega)
      (by rw [hlog]; norm_num) (by rw [hlog, hc]; norm_num), hlog, hc, hm, hd, hmod]
    rfl

theorem low_lattice_round (s : Bool) (n : Nat) (hn : n < 16777216) :
    Model.roundDyadic FloatFormat.binary32 ⟨s, n, -149⟩ =
      Model.ofFields FloatFormat.binary32 s (n / 8388608) (n % 8388608) := by
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic,
      native_low_lattice s n hn, Model.NativeBinary32.ofUInt32_mkBits]

theorem subnormal_fields_nonzero_add (s : Bool) (f g : Nat)
    (hf0 : f ≠ 0) (hg0 : g ≠ 0) (hf : f < 8388608) (hg : g < 8388608) :
    Model.Spec.add (Model.ofFields FloatFormat.binary32 s 0 f)
      (Model.ofFields FloatFormat.binary32 s 0 g) =
      Model.ofFields FloatFormat.binary32 s ((f + g) / 8388608)
        ((f + g) % 8388608) := by
  have hdf := Model.toDyadic?_ofFields_subnormal FloatFormat.binary32 s f hf0 hf
  have hdg := Model.toDyadic?_ofFields_subnormal FloatFormat.binary32 s g hg0 hg
  change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s 0 f) =
    some ⟨s, f, -149⟩ at hdf
  change Model.toDyadic? (Model.ofFields FloatFormat.binary32 s 0 g) =
    some ⟨s, g, -149⟩ at hdg
  unfold Model.Spec.add
  rw [hdf, hdg, Model.addDyadic_sameSign_sameExponent s f g (-149) hf0 hg0]
  exact low_lattice_round s (f + g) (by omega)

theorem native_overflow (s : Bool) (t : Nat) (ht : t ≤ 16777214) :
    Model.NativeBinary32.roundDyadic ⟨s, 16777216 + t, 104⟩ =
      Model.NativeBinary32.mkBits s 255 0 := by
  have hlog := sum_log t ht
  have hr := half_round t
  have hb := half_bound t ht
  have hcarry : 8388608 + (t + (t / 2) % 2) / 2 ≠ 16777216 := by omega
  have hp : 16777216 + t ≠ 0 := by omega
  cases s <;> simp [Model.NativeBinary32.roundDyadic, hp, hlog,
    Model.pow2_eq_two_pow, hr, hcarry, Model.NativeBinary32.mkBits]

theorem overflow_fields_add (s : Bool) (f g : Nat)
    (hf : f < 8388608) (hg : g < 8388608) :
    Model.Spec.add (Model.ofFields FloatFormat.binary32 s 254 f)
      (Model.ofFields FloatFormat.binary32 s 254 g) =
      Model.ofFields FloatFormat.binary32 s 255 0 := by
  unfold Model.Spec.add
  rw [R2W01c.fields32_toDyadic s 254 f (by decide) (by decide) hf,
      R2W01c.fields32_toDyadic s 254 g (by decide) (by decide) hg]
  rw [Model.addDyadic_sameSign_sameExponent s (8388608 + f) (8388608 + g)
    ((254 : Int) - 150) (by omega) (by omega)]
  have hsum : 8388608 + f + (8388608 + g) = 16777216 + (f + g) := by omega
  rw [hsum]
  rw [← Model.NativeBinary32.ofUInt32_roundDyadic,
      native_overflow s (f + g) (by omega), Model.NativeBinary32.ofUInt32_mkBits]

end Submission.R22SameExponentMath
