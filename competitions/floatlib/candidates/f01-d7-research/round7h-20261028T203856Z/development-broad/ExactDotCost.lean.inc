/- Research exact-dot cost baseline. Original four public callbacks unchanged.
   Native128 rounding/accumulation equivalence is NOT_PROVED; fixtures and cost
   are diagnostics. Nonfinite/mismatched inputs use explicit research rejection. -/
namespace Submission.R24ExactDotCost

open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

@[inline] def rawExp (w : UInt32) : UInt32 := (w >>> 23) &&& 255
@[inline] def rawFrac (w : UInt32) : UInt32 := w &&& 0x7fffff
@[inline] def neg (w : UInt32) : Bool := (w &&& 0x80000000) != 0
@[inline] def rawMant (w : UInt32) : UInt64 :=
  if rawExp w == 0 then (rawFrac w).toUInt64
  else ((rawFrac w) ||| 0x800000).toUInt64
@[inline] def rawIdx (w : UInt32) : UInt32 := if rawExp w == 0 then 0 else rawExp w - 1
@[inline] def idx (w : UInt32) : UInt32 := (w >>> 23) &&& 255
@[inline] def mant (w : UInt32) : UInt64 :=
  if idx w == 254 then 0 else ((w &&& 0x7fffff) ||| 0x800000).toUInt64
@[inline] def encode (w : UInt32) : UInt32 :=
  if rawMant w == 0 then (w &&& 0x80000000) ||| 0x7f000000 else w - 0x00800000

structure Operand where
  raw : Array UInt32
  data : Array UInt32
  minIdx : UInt32
  maxIdx : UInt32
  normal : Bool
  finite : Bool
  hasNonzero : Bool

def prepareOperand (raw : Array UInt32) : Operand := Id.run do
  let mut data : Array UInt32 := Array.emptyWithCapacity raw.size
  let mut low : UInt32 := 255
  let mut high : UInt32 := 0
  let mut normal := true
  let mut finite := true
  let mut seen := false
  for w in raw do
    let e := rawExp w
    let f := rawFrac w
    finite := finite && e != 255
    normal := normal && e != 255 && (e != 0 || f == 0)
    data := data.push (encode w)
    if e != 255 && rawMant w != 0 then
      let k := rawIdx w
      low := if k < low then k else low
      high := if high < k then k else high
      seen := true
  return ⟨raw, data, if seen then low else 0, if seen then high else 0, normal, finite, seen⟩

structure Cache where
  left : Operand
  right : Operand
  minScale : UInt32
  maxScale : UInt32
  matched : Bool

@[inline] def pair (left right : Operand) : Cache :=
  let active := left.hasNonzero && right.hasNonzero
  ⟨left, right, if active then left.minIdx + right.minIdx else 0,
    if active then left.maxIdx + right.maxIdx else 0, left.raw.size == right.raw.size⟩
@[inline] def prepare (rawA rawB : Array UInt32) : Cache :=
  pair (prepareOperand rawA) (prepareOperand rawB)
@[inline] def Cache.rawA (c : Cache) : Array UInt32 := c.left.raw
@[inline] def Cache.rawB (c : Cache) : Array UInt32 := c.right.raw
@[inline] def Cache.a (c : Cache) : Array UInt32 := c.left.data
@[inline] def Cache.b (c : Cache) : Array UInt32 := c.right.data
@[inline] def Cache.normal (c : Cache) : Bool := c.left.normal && c.right.normal
@[inline] def Cache.finite (c : Cache) : Bool := c.left.finite && c.right.finite

@[inline] def ceilLog2 (n : Nat) : Nat :=
  if n ≤ 1 then 0 else (Submission.FastMul.fastLog2 (UInt64.ofNat (n - 1))).toNat + 1

@[inline] def fastEligible (c : Cache) : Bool :=
  if c.matched && c.normal then
    if c.a.size ≤ 1048576 then
      decide (48 + (c.maxScale.toNat - c.minScale.toNat) + ceilLog2 c.a.size ≤ 128)
    else false
  else false

@[inline] def signWord (negative : Bool) : UInt32 := if negative then 0x80000000 else 0
@[inline] def pack (negative : Bool) (exponent fraction : UInt32) : UInt32 :=
  signWord negative ||| (exponent <<< 23) ||| fraction

@[inline] def quotientLo (lo hi shift : UInt64) : UInt64 :=
  if shift == 0 then lo
  else if shift < 64 then (lo >>> shift) ||| (hi <<< (64 - shift))
  else if shift == 64 then hi
  else if shift < 128 then hi >>> (shift - 64)
  else 0

@[inline] def roundRight128 (lo hi shift : UInt64) : UInt64 :=
  if shift == 0 then lo
  else if 128 < shift then 0
  else
    let q := quotientLo lo hi shift
    let guard := if shift ≤ 64 then ((lo >>> (shift - 1)) &&& 1) != 0
      else ((hi >>> (shift - 65)) &&& 1) != 0
    let sticky := if shift ≤ 64 then (lo &&& (((1 : UInt64) <<< (shift - 1)) - 1)) != 0
      else lo != 0 || (hi &&& (((1 : UInt64) <<< (shift - 65)) - 1)) != 0
    if guard && (sticky || (q &&& 1) != 0) then q + 1 else q

def round128 (negative : Bool) (lo hi : UInt64) (base : Int) : UInt32 :=
  if lo == 0 && hi == 0 then signWord negative
  else
    let leading := if hi == 0 then (Submission.FastMul.fastLog2 lo).toNat
      else 64 + (Submission.FastMul.fastLog2 hi).toNat
    let total : Int := base + (leading : Int)
    if 127 < total then pack negative 255 0
    else
      let target : Int := max (total - 23) (-149)
      let delta := target - base
      let m := if delta ≤ 0 then lo <<< UInt64.ofNat ((-delta).toNat)
        else if 128 < delta then 0
        else roundRight128 lo hi (UInt64.ofNat delta.toNat)
      let carry := m == 0x1000000
      let normalized := if carry then m >>> 1 else m
      let encoded := target + 150 + (if carry then 1 else 0)
      if normalized < 0x800000 then pack negative 0 normalized.toUInt32
      else if 255 ≤ encoded then pack negative 255 0
      else pack negative (UInt32.ofNat encoded.toNat) (normalized - 0x800000).toUInt32

@[inline] def finish (base : UInt32) (negZero : Bool) (pLo pHi nLo nHi : UInt64) : UInt32 :=
  if pLo == nLo && pHi == nHi then signWord negZero
  else if pHi < nHi || (pHi == nHi && pLo < nLo) then
    round128 true (nLo - pLo) (nHi - pHi - (if nLo < pLo then 1 else 0))
      ((base.toNat : Int) - 298)
  else
    round128 false (pLo - nLo) (pHi - nHi - (if pLo < nLo then 1 else 0))
      ((base.toNat : Int) - 298)

def nativeLoop (a b : Array UInt32) (base : UInt32) (index : Nat)
    (negZero : Bool) (pLo pHi nLo nHi : UInt64) : Nat → UInt32
  | 0 => finish base negZero pLo pHi nLo nHi
  | remaining + 1 =>
    let wa := a[index]!
    let wb := b[index]!
    let product := mant wa * mant wb
    let negative := Bool.xor (neg wa) (neg wb)
    if product == 0 then
      nativeLoop a b base (index + 1) (negZero && negative) pLo pHi nLo nHi remaining
    else
      let shift := (idx wa + idx wb - base).toUInt64
      let lo := if shift < 64 then product <<< shift else 0
      let hi := if shift == 0 then 0 else if shift < 64 then product >>> (64 - shift)
        else product <<< (shift - 64)
      if negative then
        let nextLo := nLo + lo
        let nextHi := nHi + hi + (if nextLo < nLo then 1 else 0)
        nativeLoop a b base (index + 1) false pLo pHi nextLo nextHi remaining
      else
        let nextLo := pLo + lo
        let nextHi := pHi + hi + (if nextLo < pLo then 1 else 0)
        nativeLoop a b base (index + 1) false nextLo nextHi nLo nHi remaining

def referencePrepared (c : Cache) : UInt32 := Id.run do
  if !c.matched || !c.finite then return 0x7fc00000
  let mut total : Int := 0
  let mut negZero := c.rawA.size != 0
  for i in [:c.rawA.size] do
    let wa := c.rawA[i]!
    let wb := c.rawB[i]!
    let product := rawMant wa * rawMant wb
    let negative := Bool.xor (neg wa) (neg wb)
    if product == 0 then
      negZero := negZero && negative
    else
      negZero := false
      let shift := (rawIdx wa + rawIdx wb - c.minScale).toNat
      let term := product.toNat <<< shift
      total := total + (if negative then -(term : Int) else (term : Int))
  let negative := if total == 0 then negZero else decide (total < 0)
  return Model.NativeBinary32.roundDyadic
    ⟨negative, total.natAbs, (c.minScale.toNat : Int) - 298⟩

@[inline] def exactPrepared (c : Cache) : UInt32 :=
  if fastEligible c then nativeLoop c.a c.b c.minScale 0 (c.a.size != 0) 0 0 0 0 c.a.size
  else referencePrepared c

@[noinline] def full (rawA rawB : Array UInt32) : UInt32 := exactPrepared (prepare rawA rawB)

@[noinline] def prepared2 (left right : Operand) : UInt32 := exactPrepared (pair left right)

/-- Intended complete equivalence on canonically prepared finite data; no proof claimed. -/
def equivalenceStatement : Prop := ∀ (rawA rawB : Array UInt32),
  let c := prepare rawA rawB
  c.matched = true → c.finite = true → exactPrepared c = referencePrepared c

end Submission.R24ExactDotCost
