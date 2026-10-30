import ContractExact

/-!
ORIGINAL R28 RESEARCH DRAFT. NOT_COMPILED; NATIVE_TIMING_NOT_RUN.
This standalone file is not a proved submission and does not change kernels.
The interface consumes exact row data supplied by the existing Y8f path.
It may be used for a local cost discriminator only after pinned compilation.
The corresponding accepted-word theorem and Submission.correct are OPEN.

Word 0 is a miss sentinel; a successful result always has normal magnitude.
All floating-point operations are untrusted proposal generation. The intended
correctness proof must quantify over ANY proposed UInt32.
-/

namespace R28NativeCell
open ExactRuntime

abbrev Wide := UInt64 × UInt64

@[inline] def less (a b : Wide) : Bool :=
  a.1 < b.1 || (a.1 == b.1 && a.2 < b.2)

@[inline] def addWide (a b : Wide) : Wide :=
  let l := a.2 + b.2
  (a.1 + b.1 + (if l < a.2 then 1 else 0), l)

@[inline] def subWide (a b : Wide) : Wide :=
  (a.1 - b.1 - (if a.2 < b.2 then 1 else 0), a.2 - b.2)

/-- Requires b<2^24; two 32x24 products, followed by one carry. -/
@[inline] def mul64x24 (a b : UInt64) : Wide :=
  let p := (a &&& 0xffffffff) * b
  let q := (a >>> 32) * b
  let l := p + (q <<< 32)
  ((q >>> 32) + (if l < p then 1 else 0), l)

@[inline] def fits (a : Wide) (s : UInt64) : Bool :=
  if s == 0 then true
  else if s < 64 then a.1 >>> (64-s) == 0
  else if s == 64 then a.1 == 0
  else if s < 128 then a.1 == 0 && a.2 >>> (128-s) == 0
  else false

/-- Call only after fits; no limb shift by 64 is evaluated. -/
@[inline] def shift (a : Wide) (s : UInt64) : Wide :=
  if s == 0 then a
  else if s < 64 then ((a.1 <<< s) ||| (a.2 >>> (64-s)), a.2 <<< s)
  else (a.2 <<< (s-64), 0)

@[inline] def signedAdd (sa : Bool) (a : Wide) (sb : Bool) (b : Wide) : Bool × Wide :=
  if sa == sb then (sa, addWide a b)
  else if less a b then (sb, subWide b a) else (sa, subWide a b)

@[inline] def exponent (w : Word) : UInt64 := ((w >>> 23) &&& 255).toUInt64
@[inline] def index (w : Word) : UInt64 :=
  let e := exponent w
  if e == 0 then 0 else e-1
@[inline] def mantissa (w : Word) : UInt64 :=
  let f := (w &&& 0x7fffff).toUInt64
  if exponent w == 0 then f else 8388608+f
@[inline] def negative (w : Word) : Bool := w &&& 0x80000000 != 0

/-- E=c-149-id. Call with c<=508 and id<=253, so E+1023 is a
positive finite binary64 exponent. The proposal need not be accurate. -/
@[inline] def propose (s : Bool) (p : Wide) (d c id : UInt64) : Word :=
  let v := p.1.toFloat * Float.ofBits 0x43f0000000000000 + p.2.toFloat
  let z := (v / d.toFloat) * Float.ofBits ((c+874-id) <<< 52)
  let w := z.toFloat32.toBits &&& 0x7fffffff
  (if s then 0x80000000 else 0) ||| w

/-- Strict midpoint certificate: ties, zero, subnormal and nonfinite guesses
miss. The proof must establish exact p/d * 2^(c-149-id) first. -/
@[inline] def certify (s : Bool) (p : Wide) (d c id : UInt64) (q : Word) : Bool :=
  let e := exponent q
  if e == 0 || e == 255 || negative q != s || d == 0 || d >= 0x1000000000 ||
      (p.1 == 0 && p.2 == 0) then false
  else
    let f := (q &&& 0x7fffff).toUInt64
    let m := 8388608+f
    let l : Wide := (0, d * (4*m-(if f == 0 && 1 < e then 1 else 2)))
    let u : Wide := (0, d * (4*m+2))
    if id+e <= c+3 then
      let k := c+3-(id+e)
      if fits p k then
        let v := shift p k
        less l v && less v u
      else false
    else
      let k := id+e-(c+3)
      if fits u k then less (shift l k) p && less p (shift u k) else false

/-- Interface invariants for eventual integration:
* outer stable/legacy split remains exactly the original split;
* n,b0,Ssign,Sabs represent the actual Nat n, Y8f base and exact Int S1;
* dw is the original Y8f denominator word, not a new native sqrt;
* w/g/b are the same actual indexed words as the existing Ya7G call.
Returning 0 tells the caller to execute the original whole element function.
-/
@[inline] def attempt (n b0 : UInt64) (Ssign : Bool) (Sabs : UInt64)
    (dw w g b : Word) : Word :=
  let ed := exponent dw
  if n == 0 || 4096 <= n || 255 < b0 || 0x1000000000000000 <= Sabs ||
      ed == 0 || ed == 255 || negative dw || exponent w == 255 ||
      exponent g == 255 || exponent b == 255 then 0
  else
    let mw := mantissa w
    let iw := index w
    if mw != 0 && (!(b0 <= iw) || 24 < iw-b0) then 0
    else
      let x := if mw == 0 then 0 else n * (mw <<< (iw-b0))
      let sw := negative w
      let cs := if sw == Ssign then (if Sabs <= x then sw else !sw) else sw
      let cv := if sw == Ssign then (if Sabs <= x then x-Sabs else Sabs-x) else x+Sabs
      let mg := mantissa g
      let mb := mantissa b
      let az := cv == 0 || mg == 0
      let bz := mb == 0
      if az && bz then 0
      else
        let id := ed-1
        let d := n * mantissa dw
        let alpha := b0+index g
        let beta := index b+id
        let c := if az then beta else if bz then alpha else min alpha beta
        let ks := if az then 0 else alpha-c
        let bs := if bz then 0 else beta-c
        let a0 := mul64x24 cv mg
        let b0w : Wide := (0, d*mb)
        if !(fits a0 ks && fits b0w bs) then 0
        else
          let a := shift a0 ks
          let bb := shift b0w bs
          if a.1 >>> 63 != 0 || bb.1 >>> 63 != 0 then 0
          else
            let sp := signedAdd (cs != negative g) a (negative b) bb
            if sp.2.1 == 0 && sp.2.2 == 0 then 0
            else
              let q := propose sp.1 sp.2 d c id
              if certify sp.1 sp.2 d c id q then q else 0

end R28NativeCell
