import ContractTensor

/-
FloatLib R2-W03: executable conversion candidates for local diagnosis only.
STATUS: NOT_RUN. No Lean compiler was available during this research.
The uniform all-input equivalence theorem is NOT supplied in this file.
These definitions are NOT an accepted Kernel.lean and do not establish
Competition.SumObligation or Competition.BmmObligation.

All constants are pure and independent of the input. The wrappers expose
the straightforward form; a production loop should bind its constants/table
once per invocation and call the corresponding With function after inlining.
The table accessor deliberately uses getD: its remaining bounds/default cost
must be inspected rather than silently assumed to vanish.

Keep the caller's existing raw-FloatLib fallback and finite-native admission
conditions. Equality to native ofBits does not preserve arbitrary NaN payloads.
-/

namespace R2W03

def zero32 : Float32 := Float32.ofBits 0x00000000
def denseScale : Float32 := Float32.ofBits 0x32800000 -- 2^-26
def wideLowScale : Float32 := Float32.ofBits 0x27800000 -- 2^-48
def wideHighScale : Float32 := Float32.ofBits 0x37800000 -- 2^-16

@[inline] def exponent (u : UInt32) : UInt32 := (u >>> 23) &&& 255
@[inline] def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x007fffff) ||| 0x00800000

@[inline] def withSign (u : UInt32) (x : Float32) : Float32 :=
  if u &&& 0x80000000 == 0 then x else -x

/-- 512 pure slots indexed by the original sign and exponent, u >>> 23.
    Only exponents 24..254 are consumed; unused slots are signed zero.
    This constructs the table, including all native ofBits calls, at its
    actual initialization point. Include that cost in cold measurements. -/
def signedScaleTable : Array Float32 :=
  Array.ofFn fun (i : Fin 512) =>
    let j := UInt32.ofNat i.val
    let e := j &&& 255
    let s := (j &&& 256) <<< 23
    let b := if 24 <= e ∧ e <= 254 then s ||| ((e - 23) <<< 23) else s
    Float32.ofBits b

@[inline] def fromBitsTableWith
    (table : @& Array Float32) (z : Float32) (u : UInt32) : Float32 :=
  if u == 0 then z
  else
    let e := exponent u
    if 24 <= e ∧ e <= 254 then
      (mantissa u).toFloat32 * table.getD (u >>> 23).toNat z
    else Float32.ofBits u

@[inline] def fromBitsTable (u : UInt32) : Float32 :=
  fromBitsTableWith signedScaleTable zero32 u

/-- 7-binade, one-constant unsigned version. All other inputs use ofBits. -/
@[inline] def fromBitsDenseWith
    (z scale : Float32) (u : UInt32) : Float32 :=
  if u == 0 then z
  else
    let e := exponent u
    if 124 <= e ∧ e <= 130 then
      let n := mantissa u <<< (e - 124)
      withSign u (n.toFloat32 * scale)
    else Float32.ofBits u

@[inline] def fromBitsDense (u : UInt32) : Float32 :=
  fromBitsDenseWith zero32 denseScale u

/-- Two's-complement sign application is another proof obligation.
    N < 2^30 on the admitted domain; negative zero never enters this path. -/
@[inline] def fromBitsDenseSignedWith
    (z scale : Float32) (u : UInt32) : Float32 :=
  if u == 0 then z
  else
    let e := exponent u
    if 124 <= e ∧ e <= 130 then
      let n := mantissa u <<< (e - 124)
      let mask : UInt32 := 0 - (u >>> 31)
      let signedN := ((n ^^^ mask) - mask).toInt32
      signedN.toFloat32 * scale
    else Float32.ofBits u

@[inline] def fromBitsDenseSigned (u : UInt32) : Float32 :=
  fromBitsDenseSignedWith zero32 denseScale u

/-- Wide domain, 32-binade first bucket and 18-binade second bucket.
    UInt64 M << r is below 2^55 and still has at most 24 significant bits. -/
@[inline] def fromBitsWide64With
    (z lowScale highScale : Float32) (u : UInt32) : Float32 :=
  if u == 0 then z
  else
    let e := exponent u
    if 102 <= e ∧ e <= 151 then
      let r := if e <= 133 then e - 102 else e - 134
      let scale := if e <= 133 then lowScale else highScale
      let n := (mantissa u).toUInt64 <<< r.toUInt64
      withSign u (n.toFloat32 * scale)
    else Float32.ofBits u

@[inline] def fromBitsWide64 (u : UInt32) : Float32 :=
  fromBitsWide64With zero32 wideLowScale wideHighScale u

@[inline] def fromBitsWide64SignedWith
    (z lowScale highScale : Float32) (u : UInt32) : Float32 :=
  if u == 0 then z
  else
    let e := exponent u
    if 102 <= e ∧ e <= 151 then
      let r := if e <= 133 then e - 102 else e - 134
      let scale := if e <= 133 then lowScale else highScale
      let n := (mantissa u).toUInt64 <<< r.toUInt64
      let mask : UInt64 := 0 - (u >>> 31).toUInt64
      let signedN := ((n ^^^ mask) - mask).toInt64
      signedN.toFloat32 * scale
    else Float32.ofBits u

@[inline] def fromBitsWide64Signed (u : UInt32) : Float32 :=
  fromBitsWide64SignedWith zero32 wideLowScale wideHighScale u

/-- This names the missing result; it is a definition of a proposition,
    not a theorem, an axiom, or an assumption used to claim completion. -/
def ConversionObligation (f : UInt32 → Float32) : Prop :=
  ∀ u, f u = Float32.ofBits u

-- No theorem claiming ConversionObligation is asserted here.
-- These commands only ask the fixed environment to resolve the public APIs.
#check UInt32.toFloat32
#check UInt64.toFloat32
#check Int32.toFloat32
#check Int64.toFloat32
#check FloatLib.Floats.ExecFloat.Binary.toModel_ofFloat32_int32ToFloat32
#check FloatLib.Floats.ExecFloat.Binary.toModel_ofFloat32_int64ToFloat32

end R2W03
