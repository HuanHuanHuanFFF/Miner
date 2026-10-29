/- Runtime research: raw UInt32 factors, including finite subnormals, and no
   materialized encoded-word array. All arithmetic refinements remain UNPROVED. -/
namespace Submission.R26RawWord
open ExactRuntime
open R24ExactDotCost

structure Prepared where
  raw : Array UInt32
  values : FloatArray
  minIndex : UInt32
  maxIndex : UInt32
  finite : Bool
  hasNonzero : Bool

instance : Inhabited Prepared :=
  ⟨⟨#[], FloatArray.emptyWithCapacity 0, 0, 0, true, false⟩⟩

def prepare (raw : Array UInt32) : Prepared := Id.run do
  if raw.size > 1073741824 then
    return ⟨raw, FloatArray.emptyWithCapacity 0, 0, 0, false, false⟩
  let mut values := FloatArray.emptyWithCapacity raw.size
  let mut low : UInt32 := 255
  let mut high : UInt32 := 0
  let mut valid := true
  let mut seen := false
  for word in raw do
    let e := rawExp word
    if e == 255 then
      valid := false
      values := values.push (Float.ofBits 0)
    else
      values := values.push (Float.ofBits (R24PortableF64.widenBits word))
      if rawMant word != 0 then
        let k := rawIdx word
        if k < low then low := k
        if high < k then high := k
        seen := true
  return ⟨raw, values, if seen then low else 0, if seen then high else 0, valid, seen⟩

@[inline] def baseIndex (left right : Prepared) : UInt32 :=
  if left.hasNonzero && right.hasNonzero then left.minIndex + right.minIndex else 0

@[inline] def peakIndex (left right : Prepared) : UInt32 :=
  if left.hasNonzero && right.hasNonzero then left.maxIndex + right.maxIndex else 0

def native64 (a b : Array UInt32) (base : UInt32) (index : Nat)
    (negZero : Bool) (acc : UInt64) : Nat → UInt32
  | 0 => R24ExactDotTiered.finish64 base negZero acc
  | rest + 1 =>
    let wa := a[index]!
    let wb := b[index]!
    let product := rawMant wa * rawMant wb
    let negative := Bool.xor (neg wa) (neg wb)
    let signBit : UInt64 := if negative then 1 else 0
    let mask := 0 - signBit
    let shift := (rawIdx wa + rawIdx wb - base).toUInt64
    let term := ((product <<< shift) ^^^ mask) + signBit
    native64 a b base (index + 1) (negZero && product == 0 && negative) (acc + term) rest

def native128 (a b : Array UInt32) (base : UInt32) (index : Nat)
    (negZero : Bool) (pLo pHi nLo nHi : UInt64) : Nat → UInt32
  | 0 => finish base negZero pLo pHi nLo nHi
  | rest + 1 =>
    let wa := a[index]!
    let wb := b[index]!
    let product := rawMant wa * rawMant wb
    let negative := Bool.xor (neg wa) (neg wb)
    if product == 0 then
      native128 a b base (index + 1) (negZero && negative) pLo pHi nLo nHi rest
    else
      let shift := (rawIdx wa + rawIdx wb - base).toUInt64
      let lo := if shift < 64 then product <<< shift else 0
      let hi := if shift == 0 then 0 else if shift < 64 then product >>> (64 - shift)
        else product <<< (shift - 64)
      if negative then
        let nextLo := nLo + lo
        let nextHi := nHi + hi + (if nextLo < nLo then 1 else 0)
        native128 a b base (index + 1) false pLo pHi nextLo nextHi rest
      else
        let nextLo := pLo + lo
        let nextHi := pHi + hi + (if nextLo < pLo then 1 else 0)
        native128 a b base (index + 1) false nextLo nextHi nLo nHi rest

@[inline] def original (left right : Prepared) : UInt32 :=
  dotFn left.raw.size (fun i => left.raw[i]!) (fun i => right.raw[i]!)

@[inline] def exact (left right : Prepared) : UInt32 :=
  let n := left.raw.size
  if !(left.finite && right.finite) || n > 1048576 then original left right
  else
    let base := baseIndex left right
    let width := 48 + (peakIndex left right).toNat - base.toNat + ceilLog2 n
    if width ≤ 62 then native64 left.raw right.raw base 0 (n != 0) 0 n
    else if width ≤ 128 then native128 left.raw right.raw base 0 (n != 0) 0 0 0 0 n
    else original left right

@[inline] def attempt (left right : Prepared) : UInt32 :=
  let n := left.raw.size
  if n == 0 || n > 1073741824 || !(left.finite && right.finite) then 0
  else
    let sum := R24PortableF64.sumRemaining left.values right.values 0 (Float.ofBits 0) n
    let sumWord := sum.toBits
    let guess := R24PortableF64.proposal sumWord
    let L := R24PortableF64.ceilLog2 n
    let H := (peakIndex left right).toUInt64
    let radius := Float.ofBits ((H + (L + L) + 720) <<< 52)
    if R24PortableF64.certify sum radius sumWord guess then guess else 0

@[inline] def dotPrepared (left right : Prepared) : UInt32 :=
  if left.raw.size != right.raw.size then dotSpec left.raw right.raw
  else
    let guess := attempt left right
    if guess == 0 then exact left right else guess

end Submission.R26RawWord
