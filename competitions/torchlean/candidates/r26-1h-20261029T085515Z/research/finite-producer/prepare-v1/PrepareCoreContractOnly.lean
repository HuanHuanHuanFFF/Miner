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


end Submission.R25PrepareAgreement
