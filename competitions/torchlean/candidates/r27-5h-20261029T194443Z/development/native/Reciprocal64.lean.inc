/- R27 owned primitive prototype. Pure word arithmetic only. Correctness bridge
   and emitted native cost remain to be accepted; never use retainedCorrect. -/
namespace R27Reciprocal

@[inline] def mulHigh (a b : UInt64) : UInt64 :=
  let mask : UInt64 := 0xffffffff
  let aLow := a &&& mask
  let bLow := b &&& mask
  let aHigh := a >>> 32
  let bHigh := b >>> 32
  let lowProduct := aLow * bLow
  let crossA := aHigh * bLow
  let crossB := aLow * bHigh
  let middle := (lowProduct >>> 32) + (crossA &&& mask) + (crossB &&& mask)
  aHigh * bHigh + (crossA >>> 32) + (crossB >>> 32) + (middle >>> 32)

@[inline] def prepare (denominator : UInt64) : UInt64 :=
  0xffffffffffffffff / denominator

@[inline] def divRem (numerator denominator reciprocal : UInt64) : UInt64 × UInt64 :=
  if denominator == 0 then (numerator / denominator, numerator % denominator)
  else
    let estimate := mulHigh numerator reciprocal
    let remainder := numerator - estimate * denominator
    if denominator ≤ remainder then (estimate + 1, remainder - denominator)
    else (estimate, remainder)

end R27Reciprocal
