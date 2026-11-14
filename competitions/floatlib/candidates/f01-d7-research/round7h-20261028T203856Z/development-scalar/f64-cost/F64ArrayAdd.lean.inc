
/- R24 finite F64 numerical decoder: COST DIAGNOSTIC ONLY, not a proved ADD.
   Imported Float.toFloat32 is opaque. Four public functions/specs stay B2. -/
namespace Submission.R24F64Add
open FloatLib.Floats Competition
@[inline] def scaleWord (j : UInt32) : UInt64 :=
  let e := (j &&& 255).toUInt64
  let s := (j &&& 256).toUInt64 <<< 55
  let E := if e == 0 then (874 : UInt64) else e+873
  s ||| (E <<< 52)
def boxedScales : Array Float :=
  Array.ofFn (n := 512) fun j => Float.ofBits (scaleWord (UInt32.ofNat j.val))
def nativeScales : FloatArray :=
  (List.range 512).foldl
    (fun (a : FloatArray) j => a.push (Float.ofBits (scaleWord (UInt32.ofNat j))))
    (FloatArray.emptyWithCapacity 512)
@[inline] def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x7fffff) ||| (if u &&& 0x7f800000 == 0 then 0 else 0x800000)
@[inline] def finite (u : UInt32) : Bool :=
  u &&& (0x7f800000 : UInt32) != 0x7f800000
@[inline] def decodeNative (u : UInt32) : Float :=
  (mantissa u).toFloat * nativeScales.get! ((u >>> 23).toNat)
@[inline] def decodeBoxed (u : UInt32) : Float :=
  (mantissa u).toFloat * boxedScales[(u >>> 23).toNat]!
/- Finite binary64 word to nearest-even binary32 word. New unproved GRS core.
   Unlike the cast control, every operation here has a fixed Lean model. -/
@[inline] def narrowWord (w : UInt64) : UInt32 :=
  let sign := (w >>> 32).toUInt32 &&& (0x80000000 : UInt32)
  let e := (w >>> 52) &&& (2047 : UInt64)
  if e < 873 then sign
  else if e > 1150 then sign ||| 0x7f800000
  else
    let m := (w &&& (0xfffffffffffff : UInt64)) ||| (0x10000000000000 : UInt64)
    if e < 897 then
      let d := (926 : UInt64)-e
      let q := (m + (((1 : UInt64) <<< (d-1))-1) + ((m >>> d) &&& 1)) >>> d
      sign ||| q.toUInt32
    else
      let q := ((m + (0xfffffff : UInt64) + ((m >>> 29) &&& 1)) >>> 29).toUInt32
      sign ||| (((e.toUInt32-897) <<< 23)+q)
@[noinline] def retainedAdd (x y : Binary32) : Binary32 := Submission.add x y
@[inline] def nativeArrayAdd (x y : Binary32) : Binary32 :=
  if finite x.raw.1 && finite y.raw.1 then
    R7W02.fromRaw (narrowWord (decodeNative x.raw.1 + decodeNative y.raw.1).toBits)
  else retainedAdd x y
@[inline] def boxedArrayAdd (x y : Binary32) : Binary32 :=
  if finite x.raw.1 && finite y.raw.1 then
    R7W02.fromRaw (narrowWord (decodeBoxed x.raw.1 + decodeBoxed y.raw.1).toBits)
  else retainedAdd x y
/- Engineering lower-bound control only: opaque narrowing cannot justify adoption. -/
@[inline] def nativeCastAdd (x y : Binary32) : Binary32 :=
  if finite x.raw.1 && finite y.raw.1 then
    R7W02.fromRaw ((decodeNative x.raw.1 + decodeNative y.raw.1).toFloat32.toBits)
  else retainedAdd x y
end Submission.R24F64Add
