
/- Draft dependencies, appended after retained df5c:
astra-native-product1.lean and astra-nat-normal-form-draft.lean.
This file does not change the public mul runtime. -/
namespace Submission.R14UnitFusion

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Numerics

theorem native_model_mul_of_decodes (x y : Float32) {dx dy : Dyadic}
    (hx : Model.toDyadic? (R2W01c.nativeModel x) = some dx)
    (hy : Model.toDyadic? (R2W01c.nativeModel y) = some dy) :
    R2W01c.nativeModel (x * y) =
      Model.mul (R2W01c.nativeModel x) (R2W01c.nativeModel y) := by
  have h := R2W01c.NativeBridge.toModelNativeMul x y
    (R2W01c.nativeFinite_of_decode x hx) (R2W01c.nativeFinite_of_decode y hy)
  simpa only [ExecFloat.Binary.toModel_ofFloat32, R2W01c.nativeModel] using h

/-- A conditional composition theorem about two ACTUAL Float32 multiplications.
All input decode hypotheses are instantiated by packed normal words below. -/
theorem fused_unit_model (x y factor : Float32) (mx my s : Nat) (sign : Bool)
    (hmx : 8388608 ≤ mx) (hmx' : mx < 16777216)
    (hmy : 8388608 ≤ my) (hmy' : my < 16777216)
    (hs : 128 ≤ s) (hs' : s ≤ 380)
    (hx : Model.toDyadic? (R2W01c.nativeModel x) = some ⟨false, mx, -23⟩)
    (hy : Model.toDyadic? (R2W01c.nativeModel y) = some ⟨false, my, -23⟩)
    (hf : Model.toDyadic? (R2W01c.nativeModel factor) =
      some ⟨sign, 2 ^ 23, (s : Int) - 277⟩) :
    R2W01c.nativeModel ((x * y) * factor) =
      Model.roundDyadic FloatFormat.binary32
        ⟨sign, mx * my, (s : Int) - 300⟩ := by
  let p := mx * my
  have hlow := Nat.mul_le_mul hmx hmy
  have hupp := Nat.mul_le_mul (show mx ≤ 16777215 by omega)
    (show my ≤ 16777215 by omega)
  have hpLo : 70368744177664 ≤ p := by simpa [p] using hlow
  have hpHi : p < 281474976710656 := by
    norm_num at hupp
    dsimp [p]
    omega
  have hpMax : p ≤ 281474943156225 := by
    dsimp [p]
    norm_num at hupp
    exact hupp
  have hl := R14NatNormal.leading_bounds p hpLo hpHi
  have hc := R14NatNormal.carry_le p
  have hm := R14NatNormal.mantissa_bounds p hpLo hpHi
  have hmx0 : mx ≠ 0 := by omega
  have hmy0 : my ≠ 0 := by omega
  have hmid : R2W01c.nativeModel (x * y) =
      Model.roundDyadic FloatFormat.binary32 ⟨false, p, -46⟩ := by
    rw [native_model_mul_of_decodes x y hx hy]
    simpa [p] using R14NativeProduct.model_mul_of_nonzero_decodes
      (R2W01c.nativeModel x) (R2W01c.nativeModel y)
      ⟨false, mx, -23⟩ ⟨false, my, -23⟩ hx hy hmx0 hmy0
  have hmidMin : -126 ≤ (p.log2 : Int) + (-46) := by omega
  have hmidMax : (p.log2 : Int) + (-46) + (R14NatNormal.carry p : Int) ≤ 127 := by
    omega
  have hmidDecode := R14NatNormal.round_normal_decode false p (-46)
    hpLo hpHi hmidMin hmidMax
  rw [← hmid] at hmidDecode
  have htargetMin : -126 ≤ (p.log2 : Int) + ((s : Int) - 300) := by omega
  have htargetMax :
      (p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) ≤ 127 := by
    have hcases : p.log2 = 46 ∨ p.log2 = 47 := by omega
    rcases hcases with h46 | h47
    · rw [h46]
      norm_num
      omega
    · have hc0 := R14NatNormal.no_carry_at_47 p hpMax h47
      rw [h47, hc0]
      norm_num
      omega
  have htargetDecode := R14NatNormal.round_normal_decode sign p ((s : Int) - 300)
    hpLo hpHi htargetMin htargetMax
  let a : Int := (p.log2 : Int) + (-46) + (R14NatNormal.carry p : Int) - 23
  let b : Int := (s : Int) - 277
  have hexp : a + b + ((23 : Nat) : Int) =
      (p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) - 23 := by
    dsimp [a, b]
    ring
  have hz : Model.toDyadic?
      (Model.roundDyadic FloatFormat.binary32 ⟨sign, p, (s : Int) - 300⟩) =
      some ⟨sign, R14NatNormal.mantissa p, a + b + ((23 : Nat) : Int)⟩ := by
    rw [hexp]
    exact htargetDecode
  rw [native_model_mul_of_decodes (x * y) factor hmidDecode hf]
  exact R14NativeProduct.model_mul_of_general_scale_decodes
    (R2W01c.nativeModel (x * y)) (R2W01c.nativeModel factor)
    (Model.roundDyadic FloatFormat.binary32 ⟨sign, p, (s : Int) - 300⟩)
    (by decide) sign (R14NatNormal.mantissa p) 23 a b (by omega)
    hmidDecode hf hz

theorem unit_word_decode (f : Nat) (hf : f < 8388608) :
    Model.toDyadic? (R2W01c.nativeModel
      (Float32.ofBits (Model.NativeBinary32.mkBits false 127 f))) =
      some ⟨false, 8388608 + f, -23⟩ := by
  apply R2W01c.nativeModel_ofBits_decode
  simpa using R14NatNormal.raw_mkBits_decode false 127 f (by decide) (by decide) hf

theorem factor_word_decode (sign : Bool) (s : Nat) (hs : 128 ≤ s) (hs' : s ≤ 380) :
    Model.toDyadic? (R2W01c.nativeModel
      (Float32.ofBits (Model.NativeBinary32.mkBits sign (s - 127) 0))) =
      some ⟨sign, 2 ^ 23, (s : Int) - 277⟩ := by
  apply R2W01c.nativeModel_ofBits_decode
  have he0 : 0 < s - 127 := by omega
  have hehi : s - 127 < 255 := by omega
  have hd := R14NatNormal.raw_mkBits_decode sign (s - 127) 0 he0 hehi (by decide)
  have he : ((s - 127 : Nat) : Int) - 150 = (s : Int) - 277 := by omega
  simpa only [he, Nat.add_zero, show 2 ^ 23 = 8388608 from rfl] using hd

/-- The conditional native composition now has explicit actual packed-word inputs. -/
theorem packed_unit_fusion (fx fy s : Nat) (sign : Bool)
    (hfx : fx < 8388608) (hfy : fy < 8388608)
    (hs : 128 ≤ s) (hs' : s ≤ 380) :
    R2W01c.nativeModel
      ((Float32.ofBits (Model.NativeBinary32.mkBits false 127 fx) *
        Float32.ofBits (Model.NativeBinary32.mkBits false 127 fy)) *
        Float32.ofBits (Model.NativeBinary32.mkBits sign (s - 127) 0)) =
      Model.roundDyadic FloatFormat.binary32
        ⟨sign, (8388608 + fx) * (8388608 + fy), (s : Int) - 300⟩ := by
  exact fused_unit_model _ _ _ (8388608 + fx) (8388608 + fy) s sign
    (by omega) (by omega) (by omega) (by omega) hs hs'
    (unit_word_decode fx hfx) (unit_word_decode fy hfy)
    (factor_word_decode sign s hs (by omega))

end Submission.R14UnitFusion
