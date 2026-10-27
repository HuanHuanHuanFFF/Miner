/- R19 cost discriminator only: normal-input UInt32 GRS followed by one
   numerical conversion and one native bit codec. No equivalence proof yet.
   If used as a diagnostic append, the public four B2 entries stay unchanged. -/
namespace Submission.R19GRS32Add
open FloatLib.Floats Competition

/- The only caller supplies a normal significand shifted by3, hence v>0.
   d=0 gives the original v because the low-bit mask is0. d>=32 must not
   enter UInt32's modulo32 shift path; its nonzero sticky result is1. -/
@[inline] def alignNonzero (v d : UInt32) : UInt32 :=
  if d < (32 : UInt32) then
    (v >>> d) ||| (if v &&& (((1 : UInt32) <<< d) - 1) == 0 then 0 else 1)
  else 1

@[inline] def guardedAdd
    (fallback : Binary32 → Binary32 → Binary32) (x y : Binary32) : Binary32 :=
  let u := x.raw.1
  let v := y.raw.1
  let eu := (u >>> 23) &&& (255 : UInt32)
  let ev := (v >>> 23) &&& (255 : UInt32)
  if eu - 1 ≤ (253 : UInt32) ∧ ev - 1 ≤ (253 : UInt32) then
    let swap : Bool := decide ((u &&& 0x7fffffff) < (v &&& 0x7fffffff))
    let hi := if swap then v else u
    let lo := if swap then u else v
    let eh := if swap then ev else eu
    let el := if swap then eu else ev
    let a := (((hi &&& 0x7fffff) ||| 0x800000) : UInt32) <<< 3
    let b := (((lo &&& 0x7fffff) ||| 0x800000) : UInt32) <<< 3
    let j := alignNonzero b (eh - el)
    let same := (u ^^^ v) &&& (0x80000000 : UInt32) == 0
    let t := if same then a + j else a - j
    if t == 0 then R7W02.fromRaw 0
    else
      let mid := t.toFloat32.toBits
      let e := (mid >>> 23) + eh - (153 : UInt32)
      if e - 1 ≤ (253 : UInt32) then
        R7W02.fromRaw ((hi &&& 0x80000000) ||| (e <<< 23) ||| (mid &&& 0x7fffff))
      else fallback x y
  else fallback x y

def diagnosticEntry (x y : Binary32) : Binary32 := guardedAdd Submission.add x y

end Submission.R19GRS32Add
