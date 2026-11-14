namespace Submission.R26PreparePeak
open Submission.R24PortableF64
open Submission.R24RepresentationWiden (expWord)
open Submission.R25PrepareAgreement

theorem exponent_lt (word : UInt32) : (expWord word).toNat < 256 := by
  unfold expWord
  rw [UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (word.toNat >>> 23) &&& (2 ^ 8 - 1) < 2 ^ 8
  rw [Nat.and_two_pow_sub_one_eq_mod]
  exact Nat.mod_lt _ (by decide)

theorem index_nat (word : UInt32) :
    (index32 word).toNat = (expWord word).toNat - 1 := by
  by_cases he : expWord word = 0
  · simp [index32, expWord] at he ⊢
    simp [he]
  · have heNat : 0 < (expWord word).toNat := by
      have hn : (expWord word).toNat ≠ 0 := by
        intro hz
        apply he
        apply UInt32.toNat_inj.mp
        simpa using hz
      omega
    have hle : (1 : UInt32) ≤ expWord word := by
      apply UInt32.le_iff_toNat_le.mpr
      simpa using heNat
    change ((if expWord word == 0 then 0 else expWord word - 1) : UInt32).toNat = _
    rw [if_neg (by simpa using he)]
    rw [UInt32.toNat_sub_of_le _ _ hle]
    rfl

theorem index_bound (word : UInt32) (hf : expWord word ≠ 255) :
    (index32 word).toNat ≤ 253 := by
  have he := exponent_lt word
  have hne : (expWord word).toNat ≠ 255 := by
    intro h
    apply hf
    apply UInt32.toNat_inj.mp
    simpa using h
  rw [index_nat]
  omega

theorem step_peak (s : State) (word : UInt32) :
    (step s word).2.1 =
      if expWord word = 255 then s.2.1
      else if s.2.1 < index32 word then index32 word else s.2.1 := by
  unfold step body expWord index32
  simp only [beq_iff_eq]
  split_ifs <;> rfl

theorem step_peak_bound (s : State) (word : UInt32) (hs : s.2.1.toNat ≤ 253) :
    (step s word).2.1.toNat ≤ 253 := by
  rw [step_peak]
  split_ifs with he hi
  · exact hs
  · exact index_bound word he
  · exact hs

theorem step_peak_mono (s : State) (word : UInt32) :
    s.2.1.toNat ≤ (step s word).2.1.toNat := by
  rw [step_peak]
  split_ifs with he hi
  · exact Nat.le_refl _
  · exact (UInt32.lt_iff_toNat_lt.mp hi).le
  · exact Nat.le_refl _

theorem step_peak_contains (s : State) (word : UInt32) (hf : expWord word ≠ 255) :
    (index32 word).toNat ≤ (step s word).2.1.toNat := by
  rw [step_peak, if_neg hf]
  split_ifs with hi
  · exact Nat.le_refl _
  · have hnot : ¬ s.2.1.toNat < (index32 word).toNat := by
      simpa only [UInt32.lt_iff_toNat_lt] using hi
    omega

theorem fold_peak_bound (xs : List UInt32) (s : State) (hs : s.2.1.toNat ≤ 253) :
    (xs.foldl step s).2.1.toNat ≤ 253 := by
  induction xs generalizing s with
  | nil => exact hs
  | cons word xs ih =>
    rw [List.foldl_cons]
    exact ih _ (step_peak_bound s word hs)

theorem fold_peak_mono (xs : List UInt32) (s : State) :
    s.2.1.toNat ≤ (xs.foldl step s).2.1.toNat := by
  induction xs generalizing s with
  | nil => exact Nat.le_refl _
  | cons word xs ih =>
    rw [List.foldl_cons]
    exact (step_peak_mono s word).trans (ih _)

theorem fold_peak_contains (xs : List UInt32) (s : State) (word : UInt32)
    (hm : word ∈ xs) (hf : expWord word ≠ 255) :
    (index32 word).toNat ≤ (xs.foldl step s).2.1.toNat := by
  induction xs generalizing s with
  | nil => simp at hm
  | cons head tail ih =>
    rw [List.foldl_cons]
    rcases List.mem_cons.mp hm with h | h
    · subst word
      exact (step_peak_contains s head hf).trans (fold_peak_mono tail _)
    · exact ih _ h

theorem prepare_peak_bound (raw : Array UInt32) : (prepare raw).maxIndex.toNat ≤ 253 := by
  by_cases h : raw.size ≤ 1073741824
  · rw [prepare_eq_fold raw h]
    change (raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)).2.1.toNat ≤ 253
    rw [← Array.foldl_toList]
    exact fold_peak_bound _ _ (by decide)
  · rw [prepare_overflow raw (by omega)]
    decide

theorem prepare_index_bound (raw : Array UInt32) (hv : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) :
    (index32 raw[i]).toNat ≤ (prepare raw).maxIndex.toNat := by
  have hcap := prepare_valid_sizecap raw hv
  have hf := prepare_valid_rawfinite raw hv i hi
  rw [prepare_eq_fold raw hcap]
  change (index32 raw[i]).toNat ≤
    (raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)).2.1.toNat
  rw [← Array.foldl_toList]
  exact fold_peak_contains _ _ raw[i] (Array.getElem_mem_toList hi) hf

theorem prepare_full_interface (raw : Array UInt32) (hv : (prepare raw).valid = true) :
    (prepare raw).raw = raw ∧
    raw.size ≤ 1073741824 ∧
    (prepare raw).values.size = raw.size ∧
    (prepare raw).maxIndex.toNat ≤ 253 ∧
    ∀ (i : Nat) (hi : i < raw.size),
      expWord raw[i] ≠ 255 ∧
      (prepare raw).values.get! i = Float.ofBits (widenBits raw[i]) ∧
      (index32 raw[i]).toNat ≤ (prepare raw).maxIndex.toNat := by
  have hcap := prepare_valid_sizecap raw hv
  exact ⟨prepare_raw raw, hcap, prepare_values_size raw hcap, prepare_peak_bound raw,
    fun i hi => ⟨prepare_valid_rawfinite raw hv i hi, prepare_get raw hv i hi,
      prepare_index_bound raw hv i hi⟩⟩

end Submission.R26PreparePeak
