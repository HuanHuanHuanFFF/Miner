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
  dsimp only
  split_ifs <;> rfl

theorem prepare_overflow (raw : Array UInt32) (h : 1073741824 < raw.size) :
    prepare raw = ⟨raw, FloatArray.emptyWithCapacity 0, 0, false⟩ := by
  simp only [prepare, h, ite_true] <;> rfl

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
  simp only [prepare, hlarge, ite_false]
  rfl

theorem prepare_eq_fold (raw : Array UInt32) (h : raw.size ≤ 1073741824) :
    prepare raw =
      let s := raw.foldl step (FloatArray.emptyWithCapacity raw.size, 0, true)
      ⟨raw, s.1, s.2.1, s.2.2⟩ := by
  rw [prepare_eq_forIn raw h]
  have hb : body = (fun word s => (pure (.yield (step s word)) : Id (ForInStep State))) := by
    funext word s
    exact body_yields word s
  simp only [hb, Array.forIn_pure_yield_eq_foldl] <;> rfl

theorem step_values (s : State) (word : UInt32) :
    (step s word).1.data = s.1.data.push (stored word) := by
  rcases s with ⟨⟨values⟩, peak, valid⟩
  unfold step body stored expWord
  dsimp only
  split_ifs <;> rfl

theorem step_valid (s : State) (word : UInt32) :
    (step s word).2.2 = true ↔ s.2.2 = true ∧ expWord word ≠ 255 := by
  unfold step body expWord
  dsimp only
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
