import ContractExact

/- Own R27 native-only cost discriminator. Shared bit checker/loop derives
from project-owned R26 ad9bde3e; preparation representation is new here.
No Submission.correct for the new runtime is claimed. -/

namespace Submission.R24PortableF64

@[inline] def log2word (word : UInt64) : UInt64 :=
  UInt64.ofNat word.toNat.log2

structure Prepared where
  raw : Array UInt32
  values : FloatArray
  maxIndex : UInt32
  valid : Bool

@[inline] def index32 (word : UInt32) : UInt32 :=
  let e := (word >>> 23) &&& 255
  if e == 0 then 0 else e - 1

/-- Exact finite-word widening recipe; exponent255 is handled by the caller. -/
@[inline] def widenBits (word : UInt32) : UInt64 :=
  let sign := (word.toUInt64 &&& 0x80000000) <<< 32
  let e := (word >>> 23) &&& 255
  let f := (word &&& 0x7fffff).toUInt64
  if e == 0 then
    if f == 0 then sign
    else
      let leading := log2word f
      sign ||| ((leading + 874) <<< 52) |||
        ((f - ((1 : UInt64) <<< leading)) <<< (52 - leading))
  else sign ||| ((e.toUInt64 + 896) <<< 52) ||| (f <<< 29)

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

@[inline] def ceilLog2 (n : Nat) : UInt64 :=
  if n ≤ 1 then 0
  else log2word (UInt64.ofNat n - 1) + 1

@[inline] def finite64 (word : UInt64) : Bool :=
  word &&& 0x7ff0000000000000 != 0x7ff0000000000000

/-- Arbitrary midpoint-up proposal, deliberately not a proved RN32 conversion. -/
@[inline] def proposal (word : UInt64) : UInt32 :=
  let magnitude :=
    (((((word &&& 0x7fffffffffffffff) + 0x10000000) >>> 29).toUInt32) - 0xc0000000) &&& 0x7fffffff
  ((word >>> 32).toUInt32 &&& 0x80000000) ||| magnitude

@[inline] def orderKey (word : UInt64) : UInt64 :=
  if word &&& 0x8000000000000000 == 0 then word ^^^ 0x8000000000000000
  else word ^^^ 0xffffffffffffffff

/-- Strict midpoint word checker, including the minimum-normal lower spacing. -/
@[inline] def certify (sum radius : Float) (sumWord : UInt64) (guess : UInt32) : Bool :=
  let magnitude := guess &&& 0x7fffffff
  let e := (magnitude >>> 23) &&& 255
  if e == 0 || e == 255 then false
  else
    let lowerEndpoint := (sum - radius).toBits
    let upperEndpoint := (sum + radius).toBits
    if !(finite64 sumWord && (finite64 lowerEndpoint && finite64 upperEndpoint)) then false
    else
      let base := ((e.toUInt64 + 896) <<< 52) ||| ((magnitude &&& 0x7fffff).toUInt64 <<< 29)
      let lowerDelta : UInt64 := if magnitude == 0x00800000 then 0x20000000 else 0x10000000
      let below := base - lowerDelta
      let above := base + 0x10000000
      let negative := guess &&& 0x80000000 != 0
      let lower := if negative then above ||| 0x8000000000000000 else below
      let upper := if negative then below ||| 0x8000000000000000 else above
      decide (orderKey lower < orderKey lowerEndpoint) &&
        decide (orderKey upperEndpoint < orderKey upper)

def sumRemaining (a b : FloatArray) (index : Nat) (acc : Float) (remaining : Nat) : Float :=
  match remaining with
  | 0 => acc
  | rest + 1 =>
    sumRemaining a b (index + 1) (acc + a.get! index * b.get! index) rest

/-- Zero is a miss sentinel. Every accepted guess has normal nonzero magnitude. -/
def attemptPrepared (x y : Prepared) : UInt32 := Id.run do
  let n := x.raw.size
  if n == 0 || n != y.raw.size then return 0
  if n > 1073741824 then return 0
  if !(x.valid && y.valid) then return 0
  let sum := sumRemaining x.values y.values 0 (Float.ofBits 0) n
  let sumWord := sum.toBits
  let guess := proposal sumWord
  let L := ceilLog2 n
  let H := x.maxIndex.toUInt64 + y.maxIndex.toUInt64
  let radius := Float.ofBits ((H + (L + L) + 720) <<< 52)
  if certify sum radius sumWord guess then return guess else return 0

/-- Preparation and dropping the two temporary caches are part of this call. -/
def attemptCold (x y : Array UInt32) : UInt32 :=
  if x.size == 0 || x.size != y.size then 0
  else if x.size > 1073741824 then 0
  else attemptPrepared (prepare x) (prepare y)

end Submission.R24PortableF64

namespace R27FPOnly
open ExactRuntime Submission.R24PortableF64

structure ThinPrepared where
  n : Nat
  values : FloatArray
  maxIndex : UInt32
  valid : Bool

local instance : Inhabited ThinPrepared :=
  ⟨⟨0, FloatArray.emptyWithCapacity 0, 0, false⟩⟩

/-- Direct original-array getter: no temporary raw slice or encoded-word cache. -/
@[specialize] def prepareFn (n : Nat) (get : Nat → Word) : ThinPrepared := Id.run do
  if n > 1073741824 then
    return ⟨n, FloatArray.emptyWithCapacity 0, 0, false⟩
  let mut values := FloatArray.emptyWithCapacity n
  let mut peak : UInt32 := 0
  let mut valid := true
  for i in [0:n] do
    let word := get i
    let e := (word >>> 23) &&& 255
    if e == 255 then
      valid := false
      values := values.push (Float.ofBits 0)
    else
      let idx := if e == 0 then 0 else e - 1
      if peak < idx then peak := idx
      values := values.push (Float.ofBits (widenBits word))
  return ⟨n, values, peak, valid⟩

def attempt (x y : ThinPrepared) : Word := Id.run do
  let n := x.n
  if n == 0 || n != y.n || n > 1073741824 then return 0
  if !(x.valid && y.valid) then return 0
  let s := sumRemaining x.values y.values 0 (Float.ofBits 0) n
  let q := proposal s.toBits
  let L := ceilLog2 n
  let H := x.maxIndex.toUInt64 + y.maxIndex.toUInt64
  let r := Float.ofBits ((H + (L + L) + 720) <<< 52)
  if certify s r s.toBits q then return q else return 0

/-- `slow row col` must be the exact unactivated dot including bias.
Only an unproved full-boundary native discriminator; no new correct claimed. -/
def linear (slow : Nat → Nat → Word) (rows k outW : Nat) (relu : Bool)
    (X W b : Array Word) : Array Word :=
  if rows == 0 || outW == 0 then #[]
  else
    let xs := Array.ofFn (n := rows) fun row =>
      prepareFn (k + 1) (fun t => if t < k then X[row.val * k + t]! else oneW)
    let ws := Array.ofFn (n := outW) fun col =>
      prepareFn (k + 1) (fun t => if t < k then W[col.val * k + t]! else b[col.val]!)
    Array.ofFn (n := rows * outW) fun q =>
      let row := q.val / outW
      let col := q.val % outW
      let guess := attempt xs[row]! ws[col]!
      act relu (if guess == 0 then slow row col else guess)

end R27FPOnly
