/- Repair from exact 5556 / run40149766137. Replace core_model only;
   do not append beside an existing declaration of the same name. NOT_RUN. -/
namespace Submission.R14ExponentShift
open FloatLib.Floats Competition
open FloatLib.Floats.Formats.BinaryInterchange

theorem core_model (u v : UInt32)
    (hu0 : 0 < R2W01c.wordExp u) (hu : R2W01c.wordExp u < 255)
    (hv0 : 0 < R2W01c.wordExp v) (hv : R2W01c.wordExp v < 255)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v)
    (hs' : R2W01c.wordExp u + R2W01c.wordExp v ≤ 380) :
    Model.NativeBinary32.ofUInt32 (core u v) =
      Model.mul (R2W01c.rawModel u) (R2W01c.rawModel v) := by
  let p := product (R2W01b.mantissa u) (R2W01b.mantissa v)
  let s := R2W01c.wordExp u + R2W01c.wordExp v
  have hmx := R2W01c.mantissa_bounds u
  have hmy := R2W01c.mantissa_bounds v
  have hp := product_bounds _ _ hmx.1 hmx.2 hmy.1 hmy.2
  have hpHi : p < 281474976710656 := by change product _ _ < _; omega
  have hp0 : p ≠ 0 := by change product _ _ ≠ 0; omega
  have hl := R14NatNormal.leading_bounds p hp.1 hpHi
  have hc := R14NatNormal.carry_le p
  have hmid := middle_bounds p hp.1 hp.2
  have hmin : -126 ≤ (p.log2 : Int) + ((s : Int) - 300) := by dsimp [s]; omega
  have hmax : (p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) ≤ 127 := by
    dsimp [middleExponent, s] at hmid ⊢
    omega
  have hx := R14NatNormal.raw_normal_decode u hu0 hu
  have hy := R14NatNormal.raw_normal_decode v hv0 hv
  have hm := R14NativeProduct.model_mul_of_nonzero_decodes
    (R2W01c.rawModel u) (R2W01c.rawModel v)
    ⟨R2W01c.wordSign u, (R2W01b.mantissa u).toNat, (R2W01c.wordExp u : Int) - 150⟩
    ⟨R2W01c.wordSign v, (R2W01b.mantissa v).toNat, (R2W01c.wordExp v : Int) - 150⟩
    hx hy
    (show (R2W01b.mantissa u).toNat ≠ 0 by omega)
    (show (R2W01b.mantissa v).toNat ≠ 0 by omega)
  change Model.mul (R2W01c.rawModel u) (R2W01c.rawModel v) =
    Model.roundDyadic FloatFormat.binary32
      ⟨Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v), p,
        (R2W01c.wordExp u : Int) - 150 + ((R2W01c.wordExp v : Int) - 150)⟩ at hm
  have heOrig : (R2W01c.wordExp u : Int) - 150 +
      ((R2W01c.wordExp v : Int) - 150) = (s : Int) - 300 := by dsimp [s]; omega
  rw [heOrig] at hm
  have heTarget :
      Int.toNat ((p.log2 : Int) + ((s : Int) - 300) + (R14NatNormal.carry p : Int) + 127) =
      middleExponent p + s - 300 := by dsimp [middleExponent, s]; omega
  rw [R14NatNormal.model_round_normal _ p ((s : Int) - 300)
    hp0 (by omega) hmin hmax, heTarget] at hm
  rw [core_word u v hs hs', Model.NativeBinary32.ofUInt32_mkBits]
  simpa only [p, s, storedFraction, Nat.add_assoc] using hm.symm

end Submission.R14ExponentShift
