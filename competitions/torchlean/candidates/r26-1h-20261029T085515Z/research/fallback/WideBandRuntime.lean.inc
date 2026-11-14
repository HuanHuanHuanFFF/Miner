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
