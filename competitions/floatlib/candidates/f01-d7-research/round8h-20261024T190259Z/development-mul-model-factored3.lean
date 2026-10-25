/- Actual recursion-depth repair attempt, NOT_COMPILED.
   Keep machine-word expressions outside the generic Nat/Model proof so the
   kernel checks an opaque lemma application rather than a fully unfolded term. -/
namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem model_mul_normal_fields (x y : Model FloatFormat.binary32)
    (sx sy : Bool) (a b eu ev : Nat)
    (ha0 : 8388608 ≤ a) (ha : a < 16777216)
    (hb0 : 8388608 ≤ b) (hb : b < 16777216)
    (hs : 128 ≤ eu + ev) (hs' : eu + ev ≤ 380)
    (hx : Model.toDyadic? x = some ⟨sx, a, (eu : Int) - 150⟩)
    (hy : Model.toDyadic? y = some ⟨sy, b, (ev : Int) - 150⟩) :
    Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
      (middleExponent (a * b) + eu + ev - 300) (storedFraction (a * b)) := by
  let p := a * b
  let s := eu + ev
  have hpLo : 70368744177664 ≤ p := by
    have h := Nat.mul_le_mul ha0 hb0
    norm_num at h
    exact h
  have hpHi : p ≤ 281474943156225 := by
    have h := Nat.mul_le_mul (show a ≤ 16777215 by omega) (show b ≤ 16777215 by omega)
    norm_num at h
    exact h
  have hpFit : p < 281474976710656 := by omega
  have hp0 : p ≠ 0 := by omega
  have hl := R14NatNormal.leading_bounds p hpLo hpFit
  have hc := R14NatNormal.carry_le p
  have hmRange := middle_bounds p hpLo hpHi
  have hmin : -126 ≤ (p.log2 : Int) + ((s : Int) - 300) := by dsimp [s]; omega
  have hmax : (p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) ≤ 127 := by
    dsimp [middleExponent, s] at hmRange ⊢
    omega
  have hm := R14NativeProduct.model_mul_of_nonzero_decodes x y
    ⟨sx, a, (eu : Int) - 150⟩ ⟨sy, b, (ev : Int) - 150⟩
    hx hy (show a ≠ 0 by omega) (show b ≠ 0 by omega)
  change Model.mul x y = Model.roundDyadic FloatFormat.binary32
    ⟨Bool.xor sx sy, p, (eu : Int) - 150 + ((ev : Int) - 150)⟩ at hm
  have hExp : (eu : Int) - 150 + ((ev : Int) - 150) = (s : Int) - 300 := by dsimp [s]; omega
  rw [hExp] at hm
  have hTarget : Int.toNat ((p.log2 : Int) + ((s : Int) - 300) +
      (R14NatNormal.carry p : Int) + 127) = middleExponent p + s - 300 := by
    dsimp [middleExponent, s]
    omega
  rw [R14NatNormal.model_round_normal _ p ((s : Int) - 300)
    hp0 (by omega) hmin hmax, hTarget] at hm
  have hmFields : Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
      (middleExponent p + s - 300) (storedFraction p) := hm
  change Model.mul x y = Model.ofFields FloatFormat.binary32 (Bool.xor sx sy)
    (middleExponent p + eu + ev - 300) (storedFraction p)
  rw [Nat.add_assoc (middleExponent p) eu ev]
  exact hmFields

theorem core_model (u v : UInt32)
    (hu0 : 0 < R2W01c.wordExp u) (hu : R2W01c.wordExp u < 255)
    (hv0 : 0 < R2W01c.wordExp v) (hv : R2W01c.wordExp v < 255)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    Model.NativeBinary32.ofUInt32 (core u v) =
      Model.mul (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  have hx := R14NatNormal.raw_normal_decode u hu0 hu
  have hy := R14NatNormal.raw_normal_decode v hv0 hv
  have ha := R2W01c.mantissa_bounds u
  have hb := R2W01c.mantissa_bounds v
  have hm := model_mul_normal_fields (R2W01c.rawModel u) (R2W01c.rawModel v)
    (R2W01c.wordSign u) (R2W01c.wordSign v)
    (R2W01b.mantissa u).toNat (R2W01b.mantissa v).toNat
    (R2W01c.wordExp u) (R2W01c.wordExp v)
    ha.1 ha.2 hb.1 hb.2 hs hs' hx hy
  rw [core_word u v hs hs', Model.NativeBinary32.ofUInt32_mkBits]
  exact hm.symm

end Submission.R14ExponentShift
