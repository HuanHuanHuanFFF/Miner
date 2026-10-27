
/- Draft dependencies: native-product1 and nat-normal-form-draft.
This general form covers both integer mantissas (a=b=0) and unit mantissas (a=b=-23). -/
namespace Submission.R14GeneralFusion

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

/-- Actual first rounding followed by exact rescaling. First and target normal/finite
conditions are explicit; the factor's actual decode supplies representability and finiteness. -/
theorem native_scale_fusion (x y factor : Float32) (mx my : Nat) (sign : Bool)
    (a b e : Int)
    (hmx : 8388608 ≤ mx) (hmx' : mx < 16777216)
    (hmy : 8388608 ≤ my) (hmy' : my < 16777216)
    (hfirstLo : -126 ≤ ((mx * my).log2 : Int) + (a + b))
    (hfirstHi : ((mx * my).log2 : Int) + (a + b) +
      (R14NatNormal.carry (mx * my) : Int) ≤ 127)
    (hfinalLo : -126 ≤ ((mx * my).log2 : Int) + e)
    (hfinalHi : ((mx * my).log2 : Int) + e +
      (R14NatNormal.carry (mx * my) : Int) ≤ 127)
    (hx : Model.toDyadic? (R2W01c.nativeModel x) = some ⟨false, mx, a⟩)
    (hy : Model.toDyadic? (R2W01c.nativeModel y) = some ⟨false, my, b⟩)
    (hf : Model.toDyadic? (R2W01c.nativeModel factor) =
      some ⟨sign, 2 ^ 23, e - a - b - 23⟩) :
    R2W01c.nativeModel ((x * y) * factor) =
      Model.roundDyadic FloatFormat.binary32 ⟨sign, mx * my, e⟩ := by
  let p := mx * my
  have hlow := Nat.mul_le_mul hmx hmy
  have hupp := Nat.mul_le_mul (show mx ≤ 16777215 by omega)
    (show my ≤ 16777215 by omega)
  have hpLo : 70368744177664 ≤ p := by simpa [p] using hlow
  have hpHi : p < 281474976710656 := by norm_num at hupp; dsimp [p]; omega
  have hm := R14NatNormal.mantissa_bounds p hpLo hpHi
  have hmid : R2W01c.nativeModel (x * y) =
      Model.roundDyadic FloatFormat.binary32 ⟨false, p, a + b⟩ := by
    rw [native_model_mul_of_decodes x y hx hy]
    simpa [p] using R14NativeProduct.model_mul_of_nonzero_decodes
      (R2W01c.nativeModel x) (R2W01c.nativeModel y)
      ⟨false, mx, a⟩ ⟨false, my, b⟩ hx hy (by omega) (by omega)
  have hmidDecode := R14NatNormal.round_normal_decode false p (a + b)
    hpLo hpHi hfirstLo hfirstHi
  rw [← hmid] at hmidDecode
  have htargetDecode := R14NatNormal.round_normal_decode sign p e
    hpLo hpHi hfinalLo hfinalHi
  let emid : Int := (p.log2 : Int) + (a + b) + (R14NatNormal.carry p : Int) - 23
  let escale : Int := e - a - b - 23
  have hexp : emid + escale + ((23 : Nat) : Int) =
      (p.log2 : Int) + e + (R14NatNormal.carry p : Int) - 23 := by
    dsimp [emid, escale]
    ring
  have hz : Model.toDyadic?
      (Model.roundDyadic FloatFormat.binary32 ⟨sign, p, e⟩) =
      some ⟨sign, R14NatNormal.mantissa p, emid + escale + ((23 : Nat) : Int)⟩ := by
    rw [hexp]
    exact htargetDecode
  rw [native_model_mul_of_decodes (x * y) factor hmidDecode hf]
  exact R14NativeProduct.model_mul_of_general_scale_decodes
    (R2W01c.nativeModel (x * y)) (R2W01c.nativeModel factor)
    (Model.roundDyadic FloatFormat.binary32 ⟨sign, p, e⟩)
    (by decide) sign (R14NatNormal.mantissa p) 23 emid escale (by omega)
    hmidDecode hf hz

theorem factor_integer_decode (sign : Bool) (s : Nat) (hs : 174 ≤ s) (hs' : s ≤ 380) :
    Model.toDyadic? (R2W01c.nativeModel
      (Float32.ofBits (Model.NativeBinary32.mkBits sign (s - 173) 0))) =
      some ⟨sign, 2 ^ 23, (s : Int) - 323⟩ := by
  apply R2W01c.nativeModel_ofBits_decode
  have he0 : 0 < s - 173 := by omega
  have hehi : s - 173 < 255 := by omega
  have hd := R14NatNormal.raw_mkBits_decode sign (s - 173) 0 he0 hehi (by decide)
  have he : ((s - 173 : Nat) : Int) - 150 = (s : Int) - 323 := by omega
  simpa only [he, Nat.add_zero, show 2 ^ 23 = 8388608 from rfl] using hd

theorem integer_mantissa_fusion (mx my : UInt32) (s : Nat) (sign : Bool)
    (hmx : 8388608 ≤ mx.toNat) (hmx' : mx.toNat < 16777216)
    (hmy : 8388608 ≤ my.toNat) (hmy' : my.toNat < 16777216)
    (hs : 174 ≤ s) (hs' : s ≤ 380) :
    R2W01c.nativeModel
      ((mx.toFloat32 * my.toFloat32) *
        Float32.ofBits (Model.NativeBinary32.mkBits sign (s - 173) 0)) =
      Model.roundDyadic FloatFormat.binary32
        ⟨sign, mx.toNat * my.toNat, (s : Int) - 300⟩ := by
  let p := mx.toNat * my.toNat
  have hlow := Nat.mul_le_mul hmx hmy
  have hupp := Nat.mul_le_mul (show mx.toNat ≤ 16777215 by omega)
    (show my.toNat ≤ 16777215 by omega)
  have hpLo : 70368744177664 ≤ p := by simpa [p] using hlow
  have hpMax : p ≤ 281474943156225 := by norm_num at hupp; exact hupp
  have hpHi : p < 281474976710656 := by omega
  have hl := R14NatNormal.leading_bounds p hpLo hpHi
  have hc := R14NatNormal.carry_le p
  have hfirstLo : -126 ≤ (p.log2 : Int) + (0 + 0) := by omega
  have hfirstHi : (p.log2 : Int) + (0 + 0) + (R14NatNormal.carry p : Int) ≤ 127 := by omega
  have hfinalLo : -126 ≤ (p.log2 : Int) + ((s : Int) - 300) := by omega
  have hfinalHi :
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
  have hf := factor_integer_decode sign s hs hs'
  have h := native_scale_fusion mx.toFloat32 my.toFloat32 _ mx.toNat my.toNat sign
    0 0 ((s : Int) - 300) hmx hmx' hmy hmy'
    hfirstLo hfirstHi hfinalLo hfinalHi
    (R2W01c.uint32_mantissa_model_decode mx hmx hmx')
    (R2W01c.uint32_mantissa_model_decode my hmy hmy')
    (by simpa using hf)
  exact h

end Submission.R14GeneralFusion
