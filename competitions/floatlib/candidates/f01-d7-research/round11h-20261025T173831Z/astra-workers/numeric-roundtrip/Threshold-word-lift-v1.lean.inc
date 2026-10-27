/- R17 word lift for the input-derived thresholds. Fixed-environment elaboration is pending. -/
namespace Submission.R17Threshold

theorem word_threshold_toNat (n base : UInt32)
    (hbase : base.toNat ≤ 7)
    (hlo : 8388608 ≤ n.toNat) (hhi : n.toNat ≤ 2164260735) :
    (base + (if (1 : UInt32) <<< (base + 24) ≤ n.toFloat32.toUInt32
        then (1 : UInt32) else 0)).toNat =
      base.toNat + (if 2 ^ (base.toNat + 24) ≤ rounded n.toNat then 1 else 0) := by
  let threshold : UInt32 := (1 : UInt32) <<< (base + 24)
  have hs : (base + 24).toNat = base.toNat + 24 := by
    rw [UInt32.toNat_add]
    change (base.toNat + 24) % 4294967296 = base.toNat + 24
    exact Nat.mod_eq_of_lt (by omega)
  have hp : 2 ^ (base.toNat + 24) < UInt32.size := by
    change 2 ^ (base.toNat + 24) < 2 ^ 32
    exact Nat.pow_lt_pow_right (by decide) (by omega)
  have htval : threshold.toNat = 2 ^ (base.toNat + 24) := by
    dsimp only [threshold]
    rw [UInt32.toNat_shiftLeft, hs,
      Nat.mod_eq_of_lt (show base.toNat + 24 < 32 by omega)]
    change (1 <<< (base.toNat + 24)) % UInt32.size = 2 ^ (base.toNat + 24)
    rw [Nat.shiftLeft_eq, Nat.one_mul, Nat.mod_eq_of_lt hp]
  have ht : threshold ≤ n.toFloat32.toUInt32 ↔
      2 ^ (base.toNat + 24) ≤ rounded n.toNat := by
    rw [UInt32.le_iff_toNat_le, htval, R16UInt32Roundtrip.high_roundtrip n hlo hhi]
  have hb : (if threshold ≤ n.toFloat32.toUInt32 then (1 : UInt32) else 0).toNat =
      (if 2 ^ (base.toNat + 24) ≤ rounded n.toNat then 1 else 0) := by
    by_cases h : 2 ^ (base.toNat + 24) ≤ rounded n.toNat
    · have hw := ht.mpr h
      simp [h, hw]
    · have hw : ¬threshold ≤ n.toFloat32.toUInt32 := fun hh => h (ht.mp hh)
      simp [h, hw]
  have hble : (if 2 ^ (base.toNat + 24) ≤ rounded n.toNat then 1 else 0) ≤ 1 := by
    split <;> omega
  change (base + (if threshold ≤ n.toFloat32.toUInt32 then (1 : UInt32) else 0)).toNat = _
  rw [UInt32.toNat_add, hb]
  exact Nat.mod_eq_of_lt (by change _ < 4294967296; omega)

theorem same_word_shift_from_inputs (n gap : UInt32) (a b : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216)
    (hd : gap.toNat ≤ 7) (hmag : n.toNat = a * 2 ^ gap.toNat + b) :
    (gap + (if (1 : UInt32) <<< (gap + 24) ≤ n.toFloat32.toUInt32
        then (1 : UInt32) else 0)).toNat = R16UInt32Roundtrip.roundedShift n.toNat := by
  have hN := same_magnitude_bounds a b gap.toNat ha ha' hb hb' hd
  have hlo : 8388608 ≤ n.toNat := by rw [hmag]; exact hN.1
  have hhi : n.toNat ≤ 2164260735 := by rw [hmag]; exact hN.2.1
  have hr := word_threshold_toNat n gap hd hlo hhi
  have ht := same_threshold_from_inputs a b gap.toNat ha ha' hb hb' hd
  calc
    _ = gap.toNat + (if 2 ^ (gap.toNat + 24) ≤ rounded n.toNat then 1 else 0) := hr
    _ = _ := by
      rw [hmag]
      have he : gap.toNat + 24 = 24 + gap.toNat := by omega
      rw [he]
      exact ht.2.symm

theorem opposite_word_shift_from_inputs (n gap : UInt32) (a b : Nat)
    (ha : 8388608 ≤ a) (ha' : a < 16777216)
    (hb : 8388608 ≤ b) (hb' : b < 16777216)
    (hd0 : 1 ≤ gap.toNat) (hd : gap.toNat ≤ 7)
    (hmag : n.toNat = a * 2 ^ gap.toNat - b) (hlo : 8388608 ≤ n.toNat) :
    ((gap - 1) + (if (1 : UInt32) <<< ((gap - 1) + 24) ≤ n.toFloat32.toUInt32
        then (1 : UInt32) else 0)).toNat = R16UInt32Roundtrip.roundedShift n.toNat := by
  have hgle : (1 : UInt32) ≤ gap := UInt32.le_iff_toNat_le.mpr hd0
  have hbase : (gap - 1).toNat = gap.toNat - 1 := by
    rw [UInt32.toNat_sub_of_le _ _ hgle]
  have hbasemax : (gap - 1).toNat ≤ 7 := by rw [hbase]; omega
  have hN : 8388608 ≤ a * 2 ^ gap.toNat - b := by rw [← hmag]; exact hlo
  have hM := opposite_magnitude_bounds a b gap.toNat ha ha' hb hb' hd0 hd hN
  have hhi : n.toNat ≤ 2164260735 := by rw [hmag]; exact hM.1
  have hr := word_threshold_toNat n (gap - 1) hbasemax hlo hhi
  have ht := opposite_threshold_from_inputs a b gap.toNat ha ha' hb hb' hd0 hd hN
  calc
    _ = (gap - 1).toNat +
        (if 2 ^ ((gap - 1).toNat + 24) ≤ rounded n.toNat then 1 else 0) := hr
    _ = _ := by
      rw [hbase, hmag]
      have he : gap.toNat - 1 + 24 = 23 + gap.toNat := by omega
      rw [he]
      exact ht.2.symm

end Submission.R17Threshold
