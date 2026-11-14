import ContractExact

namespace Submission.FastMul

@[inline] def sx (k x : UInt64) : UInt64 := bif x >>> k == 0 then x else x >>> k


@[inline] def sr (k x r : UInt64) : UInt64 := bif x >>> k == 0 then r else r + k


@[inline] def fastLog2 (x0 : UInt64) : UInt64 :=
  let x1 := sx 32 x0
  let r1 := sr 32 x0 0
  let x2 := sx 16 x1
  let r2 := sr 16 x1 r1
  let x3 := sx 8 x2
  let r3 := sr 8 x2 r2
  let x4 := sx 4 x3
  let r4 := sr 4 x3 r3
  let x5 := sx 2 x4
  let r5 := sr 2 x4 r4
  sr 1 x5 r5

end Submission.FastMul

namespace Submission.R24PortableF64

@[inline] def widenBits (word : UInt32) : UInt64 :=
  let sign := (word.toUInt64 &&& 0x80000000) <<< 32
  let e := (word >>> 23) &&& 255
  let f := (word &&& 0x7fffff).toUInt64
  if e == 0 then
    if f == 0 then sign
    else
      let leading := Submission.FastMul.fastLog2 f
      sign ||| ((leading + 874) <<< 52) |||
        ((f - ((1 : UInt64) <<< leading)) <<< (52 - leading))
  else sign ||| ((e.toUInt64 + 896) <<< 52) ||| (f <<< 29)

end Submission.R24PortableF64

namespace Submission.R24PortableF64

structure Prepared where
  raw : Array UInt32
  values : FloatArray
  maxIndex : UInt32
  valid : Bool

@[inline] def index32 (word : UInt32) : UInt32 :=
  let e := (word >>> 23) &&& 255
  if e == 0 then 0 else e - 1

def prepare (raw : Array UInt32) : Prepared := Id.run do
  if raw.size > 1073741824 then
    return ⟨raw, FloatArray.emptyWithCapacity 0, 0, false⟩
  let mut values := FloatArray.emptyWithCapacity raw.size
  let mut peak : UInt32 := 0
  let mut valid := true
  for word in raw do
    let e := (word >>> 23) &&& 255
    if e == 255 then
      valid := false
      values := values.push (Float.ofBits 0)
    else
      let idx := if e == 0 then 0 else e - 1
      if peak < idx then peak := idx
      values := values.push (Float.ofBits (widenBits word))
  return ⟨raw, values, peak, valid⟩

end Submission.R24PortableF64

namespace Submission.R24RepresentationWiden
@[inline] def expWord (u : UInt32) : UInt32 := (u >>> 23) &&& 255
end Submission.R24RepresentationWiden

/- Proof-only views of the original mutable preparation loop. -/
namespace Submission.R25PrepareAgreement
open Submission.R24PortableF64
open Submission.R24RepresentationWiden (expWord)

abbrev State := FloatArray × UInt32 × Bool

def body (word : UInt32) (s : State) : Id (ForInStep State) :=
  let e := (word >>> 23) &&& 255
  if e == 255 then
    pure (.yield (s.1.push (Float.ofBits 0), s.2.1, false))
  else
    let idx := if e == 0 then 0 else e - 1
    if s.2.1 < idx then
      pure (.yield (s.1.push (Float.ofBits (widenBits word)), idx, s.2.2))
    else
      pure (.yield (s.1.push (Float.ofBits (widenBits word)), s.2.1, s.2.2))

def step (s : State) (word : UInt32) : State := (body word s).run.value

def stored (word : UInt32) : Float :=
  if expWord word == 255 then Float.ofBits 0 else Float.ofBits (widenBits word)

theorem body_yields (word : UInt32) (s : State) :
    body word s = pure (.yield (step s word)) := by
  unfold step body
  split_ifs <;> rfl

theorem prepare_overflow (raw : Array UInt32) (h : 1073741824 < raw.size) :
    prepare raw = ⟨raw, FloatArray.emptyWithCapacity 0, 0, false⟩ := by
  simp only [prepare, h, ite_true]

theorem prepare_valid_sizecap (raw : Array UInt32) (h : (prepare raw).valid = true) :
    raw.size ≤ 1073741824 := by
  by_contra hn
  have hp := prepare_overflow raw (by omega)
  rw [hp] at h
  cases h

/- The source-level connection to the original producer is this equality.
   No conclusion below bypasses it by assuming a replacement producer. -/
theorem prepare_eq_forIn (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    prepare raw =
      let s := (ForIn.forIn raw
        ((FloatArray.emptyWithCapacity raw.size, (0 : UInt32), true) : State) body : Id State).run
      ⟨raw, s.1, s.2.1, s.2.2⟩ := by
  have hlarge : ¬ 1073741824 < raw.size := by omega
  simpa only [prepare, hlarge, ite_false, body]

theorem prepare_eq_fold (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    prepare raw =
      let s := raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)
      ⟨raw, s.1, s.2.1, s.2.2⟩ := by
  rw [prepare_eq_forIn raw h]
  have hb : body = (fun word s => (pure (.yield (step s word)) : Id (ForInStep State))) := by
    funext word s
    exact body_yields word s
  simpa only [hb, Array.forIn_pure_yield_eq_foldl]

theorem step_values (s : State) (word : UInt32) :
    (step s word).1.data = s.1.data.push (stored word) := by
  rcases s with ⟨⟨values⟩, peak, valid⟩
  unfold step body stored expWord
  split_ifs <;> rfl

theorem step_valid (s : State) (word : UInt32) :
    (step s word).2.2 = true ↔ s.2.2 = true ∧ expWord word ≠ 255 := by
  unfold step body expWord
  split_ifs <;> simp_all [beq_iff_eq]

theorem fold_values (xs : List UInt32) (s : State) :
    (xs.foldl step s).1.data.toList = s.1.data.toList ++ xs.map stored := by
  induction xs generalizing s with
  | nil => simp only [List.foldl_nil, List.map_nil, List.append_nil]
  | cons word xs ih =>
    rw [List.foldl_cons, ih, step_values, Array.toList_push, List.map_cons]
    simp only [List.append_assoc, List.singleton_append]

theorem fold_valid (xs : List UInt32) (s : State) :
    (xs.foldl step s).2.2 = true ↔
      s.2.2 = true ∧ ∀ word ∈ xs, expWord word ≠ 255 := by
  induction xs generalizing s with
  | nil => simp
  | cons word xs ih =>
    rw [List.foldl_cons, ih, step_valid]
    simp only [List.forall_mem_cons, and_assoc]

theorem prepare_raw (raw : Array UInt32) : (prepare raw).raw = raw := by
  by_cases h : raw.size ≤ 1073741824
  · rw [prepare_eq_forIn raw h]
  · rw [prepare_overflow raw (by omega)]

theorem prepare_values_data (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    (prepare raw).values.data = raw.map stored := by
  rw [prepare_eq_fold raw h]
  change (raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)).1.data = _
  apply Array.toList_inj.mp
  rw [← Array.foldl_toList, fold_values, Array.toList_map]
  simp only [FloatArray.emptyWithCapacity, List.nil_append]

private theorem size_data (a : FloatArray) : a.size = a.data.size := by
  cases a
  rfl

private theorem get_data (a : FloatArray) (i : Nat) : a.get! i = a.data[i]! := by
  cases a
  rfl

theorem prepare_values_size (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    (prepare raw).values.size = raw.size := by
  rw [size_data, prepare_values_data raw h, Array.size_map]

theorem prepare_valid_iff (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    (prepare raw).valid = true ↔ ∀ word ∈ raw.toList, expWord word ≠ 255 := by
  rw [prepare_eq_fold raw h]
  change (raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)).2.2 = true ↔ _
  rw [← Array.foldl_toList, fold_valid]
  simp

theorem prepare_valid_rawfinite (raw : Array UInt32) (h : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) : expWord raw[i] ≠ 255 := by
  have hf := (prepare_valid_iff raw (prepare_valid_sizecap raw h)).mp h
  exact hf raw[i] (Array.getElem_mem_toList hi)

theorem prepare_get (raw : Array UInt32) (h : (prepare raw).valid = true)
    (i : Nat) (hi : i < raw.size) :
    (prepare raw).values.get! i = Float.ofBits (widenBits raw[i]) := by
  have hcap := prepare_valid_sizecap raw h
  have hf := prepare_valid_rawfinite raw h i hi
  rw [get_data, prepare_values_data raw hcap]
  rw [getElem!_pos _ i (by simpa only [Array.size_map] using hi), Array.getElem_map]
  simp only [stored, beq_iff_eq, hf, ite_false]

theorem prepare_getter_interface (raw : Array UInt32) (h : (prepare raw).valid = true) :
    (prepare raw).raw = raw ∧
    raw.size ≤ 1073741824 ∧
    (prepare raw).values.size = raw.size ∧
    ∀ (i : Nat) (hi : i < raw.size),
      expWord raw[i] ≠ 255 ∧
      (prepare raw).values.get! i = Float.ofBits (widenBits raw[i]) := by
  have hcap := prepare_valid_sizecap raw h
  exact ⟨prepare_raw raw, hcap, prepare_values_size raw hcap,
    fun i hi => ⟨prepare_valid_rawfinite raw h i hi, prepare_get raw h i hi⟩⟩

end Submission.R25PrepareAgreement

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
