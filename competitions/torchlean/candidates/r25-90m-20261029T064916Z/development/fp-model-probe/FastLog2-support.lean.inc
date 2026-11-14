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
