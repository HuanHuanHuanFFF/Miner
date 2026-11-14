import ContractExact

namespace Submission.R27WordPayload

@[inline] def densePack (magnitude:UInt64) (negative:Bool):UInt64 :=
 let center:UInt64:=0x8000000000
 if negative then center-magnitude else center+magnitude

@[inline] def denseSelected (payload:UInt64) (weightNegative:Bool):UInt64 :=
 let z:=payload-0x8000000000
 if weightNegative then (0:UInt64)-z else z

@[inline] def indexedPack (index factor:UInt32):UInt64 :=
 (index.toUInt64 <<< 32) ||| factor.toUInt64

@[inline] def indexedIndex (payload:UInt64):UInt32 := (payload >>> 32).toUInt32

@[inline] def indexedSelected (payload:UInt64) (weightNegative:Bool):UInt64 :=
 let z:=(payload.toUInt32.toUInt64 ^^^ 0x80000000)-0x80000000
 if weightNegative then (0:UInt64)-z else z

@[inline] def shiftedPack (mantissa delta index:UInt32) (negative:Bool):UInt64 :=
 mantissa.toUInt64 ||| (delta.toUInt64 <<< 24) |||
 ((if negative then (1:UInt64) else 0) <<< 28) ||| (index.toUInt64 <<< 29)

@[inline] def shiftedIndex (payload:UInt64):UInt32 := (payload >>> 29).toUInt32

@[inline] def shiftedSelected (payload:UInt64) (weightNegative:Bool):UInt64 :=
 let m:=(payload &&& 0xffffff) <<< ((payload >>> 24) &&& 15)
 let negative:=((payload >>> 28) &&& 1) != 0
 if negative != weightNegative then (0:UInt64)-m else m

end Submission.R27WordPayload
