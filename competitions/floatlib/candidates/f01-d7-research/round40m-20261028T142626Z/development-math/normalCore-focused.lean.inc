set_option maxHeartbeats 1000000 in
theorem normalCore_eq_roundP (s u v : UInt32) (sign : Bool)
    (hs0 : 128 ≤ s.toNat) (hs1 : s.toNat ≤ 380)
    (hsign : ((u ^^^ v) &&& (0x80000000 : UInt32)) =
      (if sign then (0x80000000 : UInt32) else 0)) :
    normalCore s u v = FastMul.roundP sign
      ((R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64) (s.toUInt64-2) := by
  let p := (R2W01b.mantissa u).toUInt64 * (R2W01b.mantissa v).toUInt64
  have hp := product_bounds u v
  have hb := output_bounds p s hp.1 hp.2 hs0 hs1
  conv_rhs => rw [roundP_normal sign p s hp.1 hp.2 hs0 hs1]
  change ((u ^^^ v) &&& (0x80000000 : UInt32)) |||
      (exponentWord s p <<< 23) ||| (mantissaWord p-8388608) =
    FastMul.mkW sign (oldPosition p s-171).toUInt32 (FastMul.fracW (oldMantissa p))
  rw [hsign,← mkW_eq_unmasked sign _ _ hb.1 hb.2,
    exponentWord_eq_old p s hp.1 hp.2 hs0 hs1,fractionWord_eq_old p hp.1 hp.2]
