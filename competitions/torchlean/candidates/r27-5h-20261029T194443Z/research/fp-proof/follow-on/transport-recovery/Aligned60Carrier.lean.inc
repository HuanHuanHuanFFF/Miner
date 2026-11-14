import ContractExact

/- Isolated representation draft, NOT_COMPILED. No Float arithmetic and no kernel. -/
namespace Submission.R27Aligned60

/-- Public23 aligned magnitude is <2^39 under the original input-span<=15.
    With index<2^20 this biased signed40+index20 payload is <2^60. -/
@[inline] def pack (index : UInt32) (magnitude : UInt64) (negative : Bool) : UInt64 :=
  let center : UInt64 := 0x8000000000
  let factor := if negative then center - magnitude else center + magnitude
  (index.toUInt64 <<< 40) ||| factor

@[inline] def index (payload : UInt64) : UInt32 :=
  (payload >>> 40).toUInt32

/-- The original aligned factor, including weight-sign selection, modulo2^64.
    No variable shift of the input magnitude is performed in this getter. -/
@[inline] def selected (payload : UInt64) (weightNegative : Bool) : UInt64 :=
  let z := (payload &&& 0xffffffffff) - 0x8000000000
  if weightNegative then (0 : UInt64) - z else z

/-- Same payload, same8-byte element slot on64-bit, immediate Nat control.
    Its semantic correctness does not require the smallNat performance bound. -/
@[specialize] def prepareNat {α : Type} (encode : α → UInt64) (xs : Array α) : Array Nat :=
  xs.foldl (fun a x => a.push (encode x).toNat) (Array.emptyWithCapacity xs.size)

@[inline] def loadNat (xs : Array Nat) (i : Nat) (h : i < xs.size) : UInt64 :=
  UInt64.ofNat xs[i]

/-- These Float wrappers are only meaningful with the actual producer bounds;
    the transport proof source supplies the finite-prefix theorem. -/
@[specialize] def prepareFloat {α : Type} (encode : α → UInt64) (xs : Array α) : FloatArray :=
  xs.foldl (fun a x => a.push (Float.ofBits (encode x))) (FloatArray.emptyWithCapacity xs.size)

@[inline] def loadFloat (xs : FloatArray) (i : USize) (h : i.toNat < xs.size) : UInt64 :=
  (xs.uget i h).toBits

end Submission.R27Aligned60

