namespace Submission.R26PreparedParameters
open Submission.R24PortableF64
open Submission.R25PrepareAgreement
open Submission.R26PreparePeak

theorem ceilLog2_nat (n : Nat) (hcap : n ≤ 1073741824) :
    (ceilLog2 n).toNat = if n ≤ 1 then 0 else (n - 1).log2 + 1 := by
  by_cases hn : n ≤ 1
  · simp only [ceilLog2, hn, ite_true]
    rfl
  · have hn64 : (UInt64.ofNat n).toNat = n :=
      UInt64.toNat_ofNat_of_lt' (by omega)
    have hone : (1 : UInt64) ≤ UInt64.ofNat n := by
      rw [UInt64.le_iff_toNat_le, hn64]
      change 1 ≤ n
      omega
    have hsub : (UInt64.ofNat n - 1).toNat = n - 1 := by
      rw [UInt64.toNat_sub_of_le _ _ hone, hn64]
      rfl
    have hlog : (n - 1).log2 < 30 :=
      (Nat.log2_lt (by omega : n - 1 ≠ 0)).mpr (by omega)
    simp only [ceilLog2, hn, ite_false]
    rw [UInt64.toNat_add, Submission.FastMul.fastLog2_eq]
    change ((UInt64.ofNat n - 1).toNat.log2 + 1) % 18446744073709551616 = _
    rw [hsub]
    exact Nat.mod_eq_of_lt (by omega)

theorem ceilLog2_bound (n : Nat) (hcap : n ≤ 1073741824) :
    (ceilLog2 n).toNat ≤ 30 := by
  rw [ceilLog2_nat n hcap]
  split_ifs with hn
  · decide
  · have hl : (n - 1).log2 < 30 :=
      (Nat.log2_lt (by omega : n - 1 ≠ 0)).mpr (by omega)
    omega

theorem ceilLog2_covers (n : Nat) (hcap : n ≤ 1073741824) :
    n ≤ 2 ^ (ceilLog2 n).toNat := by
  rw [ceilLog2_nat n hcap]
  split_ifs with hn
  · simpa using hn
  · have hl : n - 1 < 2 ^ ((n - 1).log2 + 1) := Nat.lt_log2_self
    omega

theorem prepared_H_nat (rawX rawY : Array UInt32) :
    ((prepare rawX).maxIndex.toUInt64 + (prepare rawY).maxIndex.toUInt64).toNat =
      (prepare rawX).maxIndex.toNat + (prepare rawY).maxIndex.toNat := by
  have hx := prepare_peak_bound rawX
  have hy := prepare_peak_bound rawY
  rw [UInt64.toNat_add, UInt32.toNat_toUInt64, UInt32.toNat_toUInt64]
  change (_ + _) % 18446744073709551616 = _
  exact Nat.mod_eq_of_lt (by omega)

theorem prepared_H_bound (rawX rawY : Array UInt32) :
    ((prepare rawX).maxIndex.toUInt64 + (prepare rawY).maxIndex.toUInt64).toNat ≤ 506 := by
  rw [prepared_H_nat]
  have hx := prepare_peak_bound rawX
  have hy := prepare_peak_bound rawY
  omega

theorem actual_parameters (rawX rawY : Array UInt32)
    (hv : (prepare rawX).valid = true) :
    let H := (prepare rawX).maxIndex.toUInt64 + (prepare rawY).maxIndex.toUInt64
    let L := ceilLog2 (prepare rawX).raw.size
    H.toNat ≤ 506 ∧ L.toNat ≤ 30 ∧ (prepare rawX).raw.size ≤ 2 ^ L.toNat := by
  dsimp only
  rw [prepare_raw]
  have hcap := prepare_valid_sizecap rawX hv
  exact ⟨prepared_H_bound rawX rawY, ceilLog2_bound _ hcap, ceilLog2_covers _ hcap⟩

end Submission.R26PreparedParameters
