/- R27 runtime research. Scan actual nonzero product exponents, then perform a
   primitive-word exact accumulation. No temporary operand arrays or FloatArray.
   The original finishWord executes once, including bias in the same dot. -/
namespace Submission.R27DirectWord
open ExactRuntime
open R24ExactDotCost
open R26RawWord (finishOfficial64 finishOfficial128)

structure Range where
  low : UInt32
  high : UInt32
  finite : Bool
  seen : Bool

@[specialize] def scan (fa fb : Nat → Word) (i : Nat)
    (low high : UInt32) (valid seen : Bool) : Nat → Range
  | 0 => ⟨low, high, valid, seen⟩
  | rest + 1 =>
    let a := fa i
    let b := fb i
    if rawExp a == 255 || rawExp b == 255 then
      scan fa fb (i + 1) low high false seen rest
    else if rawMant a == 0 || rawMant b == 0 then
      scan fa fb (i + 1) low high valid seen rest
    else
      let e := rawIdx a + rawIdx b
      scan fa fb (i + 1) (if e < low then e else low)
        (if high < e then e else high) valid true rest

@[specialize] def loop64 (fa fb : Nat → Word) (base : UInt32) (i : Nat)
    (negativeZero : Bool) (acc : UInt64) : Nat → Word
  | 0 => finishOfficial64 base negativeZero acc
  | rest + 1 =>
    let a := fa i
    let b := fb i
    let product := rawMant a * rawMant b
    let negative := Bool.xor (neg a) (neg b)
    let signBit : UInt64 := if negative then 1 else 0
    let mask := 0 - signBit
    let shift := (rawIdx a + rawIdx b - base).toUInt64
    let term := ((product <<< shift) ^^^ mask) + signBit
    loop64 fa fb base (i + 1)
      (negativeZero && product == 0 && negative) (acc + term) rest

@[specialize] def loop128 (fa fb : Nat → Word) (base : UInt32) (i : Nat)
    (negativeZero : Bool) (pLo pHi nLo nHi : UInt64) : Nat → Word
  | 0 => finishOfficial128 base negativeZero pLo pHi nLo nHi
  | rest + 1 =>
    let a := fa i
    let b := fb i
    let product := rawMant a * rawMant b
    let negative := Bool.xor (neg a) (neg b)
    if product == 0 then
      loop128 fa fb base (i + 1) (negativeZero && negative) pLo pHi nLo nHi rest
    else
      let shift := (rawIdx a + rawIdx b - base).toUInt64
      let lo := if shift < 64 then product <<< shift else 0
      let hi := if shift == 0 then 0 else if shift < 64 then product >>> (64 - shift)
        else product <<< (shift - 64)
      if negative then
        let nextLo := nLo + lo
        let nextHi := nHi + hi + (if nextLo < nLo then 1 else 0)
        loop128 fa fb base (i + 1) false pLo pHi nextLo nextHi rest
      else
        let nextLo := pLo + lo
        let nextHi := pHi + hi + (if nextLo < pLo then 1 else 0)
        loop128 fa fb base (i + 1) false nextLo nextHi nLo nHi rest

@[specialize] def dot (n : Nat) (fa fb : Nat → Word) : Word :=
  if n > 1048576 then dotFn n fa fb
  else
    let bounds := scan fa fb 0 510 0 true false n
    if !bounds.finite then dotFn n fa fb
    else
      let base := if bounds.seen then bounds.low else 0
      let high := if bounds.seen then bounds.high else 0
      let width := 48 + high.toNat - base.toNat + ceilLog2 n
      if width ≤ 62 then loop64 fa fb base 0 (n != 0) 0 n
      else if width ≤ 128 then loop128 fa fb base 0 (n != 0) 0 0 0 0 n
      else dotFn n fa fb

@[noinline] def linear (rows inW outW : Nat) (relu : Bool)
    (X W bias : Array Word) : Array Word :=
  Array.ofFn (n := rows * outW) fun q =>
    let row := q.val / outW
    let col := q.val % outW
    act relu (dot (inW + 1)
      (fun t => if t < inW then X[row * inW + t]! else oneW)
      (fun t => if t < inW then W[col * inW + t]! else bias[col]!))

@[noinline] def gemm (batch m k n : Nat) (A B : Array Word) : Array Word :=
  Array.ofFn (n := batch * (m * n)) fun q =>
    let beta := q.val / (m * n)
    let row := q.val / n % m
    let col := q.val % n
    dot k (fun t => A[(beta * m + row) * k + t]!)
      (fun t => B[(beta * k + t) * n + col]!)

end Submission.R27DirectWord
