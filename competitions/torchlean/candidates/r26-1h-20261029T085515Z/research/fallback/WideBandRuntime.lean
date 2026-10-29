import ContractExact

namespace Submission.R26WordBlock

@[inline] def extend32 (w : UInt32) : UInt64 :=
  (w.toUInt64 ^^^ 0x80000000) - 0x80000000

@[inline] def negative64 (w : UInt64) : Bool :=
  if w < 0x8000000000000000 then false else true

@[inline] def mergeHi (lo hi q : UInt64) : UInt64 :=
  let next := lo + q
  hi + (if negative64 q then 0xffffffffffffffff else 0) +
    (if next < lo then 1 else 0)

def signed64 (q : UInt64) : Int :=
  if q.toNat < 9223372036854775808 then (q.toNat : Int)
  else (q.toNat : Int) - 18446744073709551616

def signed128 (lo hi : UInt64) : Int :=
  (lo.toNat : Int) + signed64 hi * 18446744073709551616

@[specialize] def block (a b : Nat → UInt32) : Nat → Nat → UInt64 → UInt64
  | 0, _, acc => acc
  | fuel + 1, i, acc =>
    block a b fuel (i + 1) (acc + extend32 (a i) * extend32 (b i))

@[specialize] def blocks (a b : Nat → UInt32) : Nat → Nat → UInt64 → UInt64 → UInt64 × UInt64
  | 0, _, lo, hi => (lo, hi)
  | count + 1, i, lo, hi =>
    let q := block a b 16 i 0
    blocks a b count (i + 16) (lo + q) (mergeHi lo hi q)

@[specialize] def body128 (n : Nat) (a b : Nat → UInt32) : UInt64 × UInt64 :=
  let full := blocks a b (n / 16) 0 0 0
  let q := block a b (n % 16) (n / 16 * 16) 0
  (full.1 + q, mergeHi full.1 full.2 q)

@[specialize] def body128Each (a b : Nat → UInt32) : Nat → Nat → UInt64 → UInt64 → UInt64 × UInt64
  | 0, _, lo, hi => (lo, hi)
  | fuel + 1, i, lo, hi =>
    let q := extend32 (a i) * extend32 (b i)
    body128Each a b fuel (i + 1) (lo + q) (mergeHi lo hi q)

@[inline] def magnitude32 (w : UInt32) : UInt32 :=
  if w &&& 0x80000000 != 0 then 0 - w else w

@[specialize] def maxMagnitude (f : Nat → UInt32) : Nat → Nat → UInt32 → UInt32
  | 0, _, mx => mx
  | fuel + 1, i, mx =>
    let v := magnitude32 (f i)
    maxMagnitude f fuel (i + 1) (if mx < v then v else mx)

@[inline] def canBlock16 (n : Nat) (ma mb : UInt32) : Bool :=
  n <= 1048576 && ma.toUInt64 * mb.toUInt64 < 576460752303423488

@[specialize] def preparedBody (n : Nat) (a b : Nat → UInt32) : UInt64 × UInt64 :=
  let ma := maxMagnitude a n 0 0
  let mb := maxMagnitude b n 0 0
  if canBlock16 n ma mb then body128 n a b else body128Each a b n 0 0 0

@[specialize] def preparedFinish (n : Nat) (a b : Nat → UInt32)
    (bias : Int) (exponent : Int) (negativeZero : Bool) : UInt32 :=
  let total := preparedBody n a b
  ExactRuntime.finishWord (signed128 total.1 total.2 + bias) exponent negativeZero

@[specialize] def guardedFinish (guard : Bool) (n : Nat) (a b : Nat → UInt32)
    (bias : Int) (exponent : Int) (negativeZero : Bool)
    (shipped : Unit → UInt32) : UInt32 :=
  if guard then preparedFinish n a b bias exponent negativeZero else shipped ()

theorem guardedFinish_false (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (negativeZero : Bool) (shipped : Unit → UInt32) :
    guardedFinish false n a b bias exponent negativeZero shipped = shipped () := by
  rfl

theorem guardedFinish_true (n : Nat) (a b : Nat → UInt32)
    (bias exponent : Int) (negativeZero : Bool) (shipped : Unit → UInt32) :
    guardedFinish true n a b bias exponent negativeZero shipped =
      preparedFinish n a b bias exponent negativeZero := by
  rfl

end Submission.R26WordBlock

namespace Submission.R26WordBand
open Submission.R26WordBlock

@[specialize] def indexedBlock (a indices b : Array UInt32) : Nat → Nat → UInt64 → UInt64
  | 0, _, acc => acc
  | fuel + 1, i, acc =>
    indexedBlock a indices b fuel (i + 1)
      (acc + extend32 a[i]! * extend32 b[indices[i]!.toNat]!)

@[specialize] def groupBlocks (a indices b : Array UInt32) :
    Nat → Nat → UInt64 → UInt64 → UInt64 × UInt64
  | 0, _, lo, hi => (lo, hi)
  | count + 1, i, lo, hi =>
    let q := indexedBlock a indices b 64 i 0
    groupBlocks a indices b count (i + 64) (lo + q) (mergeHi lo hi q)

@[specialize] def group128 (a indices b : Array UInt32) (start n : Nat) : UInt64 × UInt64 :=
  let full := groupBlocks a indices b (n / 64) start 0 0
  let tail := n % 64
  if tail = 0 then full else
    let q := indexedBlock a indices b tail (start + n / 64 * 64) 0
    (full.1 + q, mergeHi full.1 full.2 q)

@[inline] def shiftLo (lo : UInt64) (delta : Nat) : UInt64 :=
  if delta < 64 then lo <<< UInt64.ofNat delta else 0

@[inline] def shiftHi (lo hi : UInt64) (delta : Nat) : UInt64 :=
  if delta = 0 then hi
  else if delta < 64 then
    (hi <<< UInt64.ofNat delta) ||| (lo >>> UInt64.ofNat (64 - delta))
  else if delta < 128 then lo <<< UInt64.ofNat (delta - 64)
  else 0

@[specialize] def bandLoop (a indices b starts lengths shifts : Array UInt32) :
    Nat → Nat → UInt64 → UInt64 → UInt64 × UInt64
  | 0, _, lo, hi => (lo, hi)
  | count + 1, band, lo, hi =>
    let group := group128 a indices b starts[band]!.toNat lengths[band]!.toNat
    let delta := shifts[band]!.toNat
    let gl := shiftLo group.1 delta
    let gh := shiftHi group.1 group.2 delta
    let next := lo + gl
    bandLoop a indices b starts lengths shifts count (band + 1) next
      (hi + gh + (if next < lo then 1 else 0))

end Submission.R26WordBand
