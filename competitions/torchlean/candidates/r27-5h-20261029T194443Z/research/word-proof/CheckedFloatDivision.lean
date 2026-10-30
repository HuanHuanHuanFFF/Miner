import ContractExact

namespace Submission.R27CheckedDivision

@[inline] def accepts (a : UInt64) (d q : UInt32) : Prop :=
  q.toUInt64 * d.toUInt64 ≤ a ∧ a - q.toUInt64 * d.toUInt64 < d.toUInt64

theorem accepts_exact (a : UInt64) (d q : UInt32) (h : accepts a d q) :
    (q.toUInt64, a - q.toUInt64 * d.toUInt64) =
      (a / d.toUInt64, a % d.toUInt64) := by
  have hpBound : q.toNat * d.toNat < 18446744073709551616 := by
    have hh := Nat.mul_lt_mul'' q.toNat_lt d.toNat_lt
    simpa using hh
  have hp : (q.toUInt64 * d.toUInt64).toNat = q.toNat * d.toNat := by
    rw [UInt64.toNat_mul, UInt32.toNat_toUInt64, UInt32.toNat_toUInt64,
      Nat.mod_eq_of_lt hpBound]
  have hlo : q.toNat * d.toNat ≤ a.toNat := by
    have hh := UInt64.le_iff_toNat_le.mp h.1
    rwa [hp] at hh
  have hr : (a - q.toUInt64 * d.toUInt64).toNat = a.toNat - q.toNat * d.toNat := by
    rw [UInt64.toNat_sub_of_le _ _ h.1, hp]
  have hsmall : a.toNat - q.toNat * d.toNat < d.toNat := by
    have hh := UInt64.lt_iff_toNat_lt.mp h.2
    rwa [hr, UInt32.toNat_toUInt64] at hh
  have hq : a.toNat / d.toNat = q.toNat := Nat.div_eq_of_lt_le hlo (by
    have hs := Nat.sub_add_cancel hlo
    rw [Nat.add_mul, Nat.one_mul]
    omega)
  have hm : a.toNat % d.toNat = a.toNat - q.toNat * d.toNat := by
    have hs := Nat.mod_add_div a.toNat d.toNat
    rw [hq, Nat.mul_comm d.toNat q.toNat] at hs
    omega
  apply Prod.ext
  · apply UInt64.toNat_inj.mp
    rw [UInt32.toNat_toUInt64, UInt64.toNat_div, UInt32.toNat_toUInt64, hq]
  · apply UInt64.toNat_inj.mp
    rw [hr, UInt64.toNat_mod, UInt32.toNat_toUInt64, hm]

@[inline] def fromProposal (a : UInt64) (d q : UInt32) : UInt64 × UInt64 :=
  if accepts a d q then (q.toUInt64, a - q.toUInt64 * d.toUInt64)
  else if accepts a d (q + 1) then ((q + 1).toUInt64, a - (q + 1).toUInt64 * d.toUInt64)
  else if accepts a d (q - 1) then ((q - 1).toUInt64, a - (q - 1).toUInt64 * d.toUInt64)
  else (a / d.toUInt64, a % d.toUInt64)

theorem fromProposal_exact (a : UInt64) (d q : UInt32) :
    fromProposal a d q = (a / d.toUInt64, a % d.toUInt64) := by
  unfold fromProposal
  split_ifs with h0 h1 h2
  · exact accepts_exact a d q h0
  · exact accepts_exact a d (q + 1) h1
  · exact accepts_exact a d (q - 1) h2
  · rfl

@[inline] def prepare (d : UInt64) : Float := 1.0 / d.toFloat

@[inline] def fromFloat (a d : UInt64) (reciprocal : Float) : UInt64 × UInt64 :=
  if d < 0x100000000 then
    fromProposal a d.toUInt32 (a.toFloat * reciprocal).toUInt32
  else (a / d, a % d)

theorem fromFloat_exact (a d : UInt64) (reciprocal : Float) :
    fromFloat a d reciprocal = (a / d, a % d) := by
  unfold fromFloat
  split_ifs with hd
  · have hdNat : d.toNat < 4294967296 := UInt64.lt_iff_toNat_lt.mp hd
    have hround : d.toUInt32.toUInt64 = d := by
      apply UInt64.toNat_inj.mp
      rw [UInt32.toNat_toUInt64, UInt64.toNat_toUInt32, Nat.mod_eq_of_lt hdNat]
    rw [fromProposal_exact, hround]
  · rfl

end Submission.R27CheckedDivision
