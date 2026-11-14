/- A clean word-level bridge to separately aligned/cached factors.
   It does not reproduce any packed-array storage or anonymous caller code. -/
namespace Submission.R24TwoChain128Encoder

@[inline] def splitGuard (sa sb : UInt64) : Bool :=
  decide (sa ≤ 14) && decide (sb ≤ 14) && decide (sa + sb ≤ 14)

@[inline] def splitEncode (negative : Bool) (a b sa sb : UInt64) : UInt64 :=
  (if negative then 0 - (a <<< sa) else (a <<< sa)) * (b <<< sb)

theorem splitGuard_bound (sa sb : UInt64) (h : splitGuard sa sb = true) :
    sa.toNat + sb.toNat ≤ 14 := by
  have hh : sa ≤ 14 ∧ sb ≤ 14 ∧ sa + sb ≤ 14 := by
    simpa [splitGuard, and_assoc] using h
  have ha : sa.toNat ≤ 14 := UInt64.le_iff_toNat_le.mp hh.1
  have hb : sb.toNat ≤ 14 := UInt64.le_iff_toNat_le.mp hh.2.1
  have hc := UInt64.le_iff_toNat_le.mp hh.2.2
  rw [UInt64.toNat_add] at hc
  change (sa.toNat + sb.toNat) % 18446744073709551616 ≤ 14 at hc
  omega

theorem zero_shift_word (s : UInt64) : (0 : UInt64) <<< s = 0 := by
  apply UInt64.toNat_inj.mp
  simp [UInt64.toNat_shiftLeft]

theorem shift_factor_toNat (a s : UInt64) (ha : a.toNat < 2 ^ 24) (hs : s.toNat ≤ 14) :
    (a <<< s).toNat = a.toNat * 2 ^ s.toNat := by
  have h : Guard ⟨false, a, 1, s⟩ := ⟨ha, by decide, Or.inr (Or.inr hs)⟩
  have hw := wordMagnitude_toNat ⟨false, a, 1, s⟩ h
  simpa only [wordMagnitude, mathematicalMagnitude, UInt64.mul_one,
    UInt64.toNat_one, mul_one] using hw

theorem splitEncode_eq_encode (negative : Bool) (a b sa sb : UInt64)
    (ha : a.toNat < 2 ^ 24) (hb : b.toNat < 2 ^ 24)
    (hs : a = 0 ∨ b = 0 ∨ splitGuard sa sb = true) :
    splitEncode negative a b sa sb = encode ⟨negative, a, b, sa + sb⟩ := by
  rcases hs with hz | hz | hs
  · cases negative <;> simp [splitEncode, encode, wordMagnitude, hz, zero_shift_word]
  · cases negative <;> simp [splitEncode, encode, wordMagnitude, hz, zero_shift_word]
  · have hn := splitGuard_bound sa sb hs
    have hsum : (sa + sb).toNat = sa.toNat + sb.toNat :=
      FloatLib.Numerics.FixedWord.uint64_add_toNat_of_lt _ _ (by omega)
    have ht : Guard ⟨negative, a, b, sa + sb⟩ := by
      refine ⟨ha, hb, Or.inr (Or.inr ?_)⟩
      simpa only [hsum] using hn
    have hA := shift_factor_toNat a sa ha (by omega)
    have hB := shift_factor_toNat b sb hb (by omega)
    have hbound := mathematicalMagnitude_lt_62 ⟨negative, a, b, sa + sb⟩ ht
    change a.toNat * b.toNat * 2 ^ (sa + sb).toNat < 2 ^ 62 at hbound
    rw [hsum] at hbound
    have halgebra : (a.toNat * 2 ^ sa.toNat) * (b.toNat * 2 ^ sb.toNat) =
        a.toNat * b.toNat * 2 ^ (sa.toNat + sb.toNat) := by rw [pow_add]; ring
    have hp : (a <<< sa) * (b <<< sb) = wordMagnitude ⟨negative, a, b, sa + sb⟩ := by
      apply UInt64.toNat_inj.mp
      rw [FloatLib.Numerics.FixedWord.uint64_mul_toNat_of_lt _ _ (by
        rw [hA, hB, halgebra]
        omega), hA, hB, wordMagnitude_toNat _ ht]
      change (a.toNat * 2 ^ sa.toNat) * (b.toNat * 2 ^ sb.toNat) =
        a.toNat * b.toNat * 2 ^ (sa + sb).toNat
      rw [hsum, halgebra]
    cases negative with
    | false => simpa only [splitEncode, encode] using hp
    | true =>
      change (0 - (a <<< sa)) * (b <<< sb) = 0 - wordMagnitude ⟨true, a, b, sa + sb⟩
      rw [UInt64.sub_mul, UInt64.zero_mul, hp]

theorem splitEncode_exact (negative : Bool) (a b sa sb : UInt64)
    (ha : a.toNat < 2 ^ 24) (hb : b.toNat < 2 ^ 24)
    (hs : a = 0 ∨ b = 0 ∨ splitGuard sa sb = true) :
    Submission.R24TwoChain128.signed64 (splitEncode negative a b sa sb) =
        integerTerm ⟨negative, a, b, sa + sb⟩ ∧
      |Submission.R24TwoChain128.signed64 (splitEncode negative a b sa sb)| < (2 ^ 62 : Int) := by
  have ht : Guard ⟨negative, a, b, sa + sb⟩ := by
    refine ⟨ha, hb, ?_⟩
    rcases hs with hz | hz | hh
    · exact Or.inl hz
    · exact Or.inr (Or.inl hz)
    · have hn := splitGuard_bound sa sb hh
      have hsum : (sa + sb).toNat = sa.toNat + sb.toNat :=
        FloatLib.Numerics.FixedWord.uint64_add_toNat_of_lt _ _ (by omega)
      exact Or.inr (Or.inr (by simpa only [hsum] using hn))
  rw [splitEncode_eq_encode negative a b sa sb ha hb hs]
  exact ⟨encode_exact _ ht, encode_bound _ ht⟩

theorem run2_split_exact {α : Type} (ts : List α) (negative : α → Bool)
    (a b sa sb : α → UInt64) (hn : ts.length < 2 ^ 20)
    (hg : ∀ t ∈ ts, (a t).toNat < 2 ^ 24 ∧ (b t).toNat < 2 ^ 24 ∧
      (a t = 0 ∨ b t = 0 ∨ splitGuard (sa t) (sb t) = true)) :
    Submission.R24TwoChain128.signed128
      (Submission.R24TwoChain128.run2
        (ts.map (fun t => splitEncode (negative t) (a t) (b t) (sa t) (sb t)))) =
      (ts.map (fun t => integerTerm ⟨negative t, a t, b t, sa t + sb t⟩)).sum := by
  have hp (t : α) (ht : t ∈ ts) :=
    splitEncode_exact (negative t) (a t) (b t) (sa t) (sb t)
      (hg t ht).1 (hg t ht).2.1 (hg t ht).2.2
  have hh := Submission.R24TwoChain128.run2_exact_signed_sum
    (ts.map (fun t => splitEncode (negative t) (a t) (b t) (sa t) (sb t)))
    (by simpa using hn) (by
      intro q hq
      obtain ⟨t, ht, rfl⟩ := List.mem_map.mp hq
      exact (hp t ht).2)
  rw [hh, List.map_map]
  congr 1
  apply List.map_congr_left
  intro t ht
  exact (hp t ht).1

end Submission.R24TwoChain128Encoder
