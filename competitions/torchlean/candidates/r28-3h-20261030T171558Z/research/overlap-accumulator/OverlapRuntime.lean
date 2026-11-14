import ContractExact

/- Runtime draft only. NOT_COMPILED; no actual kernels or proof root. -/
namespace R28Overlap

@[inline] def signedTop32 (p : UInt64) : UInt64 :=
  (p.toInt64 >>> (32 : Int64)).toUInt64

@[inline] def nextLow (l p : UInt64) : UInt64 := l + p

@[inline] def nextSignedHighSum (q p : UInt64) : UInt64 := q + signedTop32 p

@[inline] def nextUnsignedHighSum (q p : UInt64) : UInt64 := q + (p >>> 32)

/-- Caller must establish n<2^32 and the right signed-product interpretation. -/
@[inline] def finishSigned (l q : UInt64) : UInt64 × UInt64 :=
  let a := q <<< 32
  ((q.toInt64 >>> (32 : Int64)).toUInt64 + (if l < a then 1 else 0), l)

@[inline] def finishUnsigned (l q : UInt64) : UInt64 × UInt64 :=
  let a := q <<< 32
  ((q >>> 32) + (if l < a then 1 else 0), l)

end R28Overlap
