/- Research cost control with a signed62-bit one-chain tier, then the frozen128
   tier and finite exact replay. Numerical equivalence is NOT_PROVED. -/
namespace Submission.R24ExactDotTiered
open Submission.R24ExactDotCost

@[inline] def eligible64 (c : Cache) : Bool :=
  if c.matched && c.normal then
    if c.a.size ≤ 1048576 then
      decide (48 + (c.maxScale.toNat - c.minScale.toNat) + ceilLog2 c.a.size ≤ 62)
    else false
  else false

@[inline] def finish64 (base : UInt32) (negZero : Bool) (acc : UInt64) : UInt32 :=
  if acc == 0 then signWord negZero
  else
    let negative := (acc &&& 0x8000000000000000) != 0
    let magnitude := if negative then 0 - acc else acc
    round128 negative magnitude 0 ((base.toNat : Int) - 298)

def native64Loop (a b : Array UInt32) (base : UInt32) (index : Nat)
    (negZero : Bool) (acc : UInt64) : Nat → UInt32
  | 0 => finish64 base negZero acc
  | remaining + 1 =>
    let wa := a[index]!
    let wb := b[index]!
    let product := mant wa * mant wb
    let negative := Bool.xor (neg wa) (neg wb)
    let signBit : UInt64 := if negative then 1 else 0
    let signMask := 0 - signBit
    let shift := (idx wa + idx wb - base).toUInt64
    let term := ((product <<< shift) ^^^ signMask) + signBit
    let nextNegZero := negZero && product == 0 && negative
    native64Loop a b base (index + 1) nextNegZero (acc + term) remaining

@[inline] def exactPreparedV2 (c : Cache) : UInt32 :=
  if eligible64 c then native64Loop c.a c.b c.minScale 0 (c.a.size != 0) 0 c.a.size
  else Submission.R24ExactDotCost.exactPrepared c

@[noinline] def fullv2 (rawA rawB : Array UInt32) : UInt32 :=
  exactPreparedV2 (prepare rawA rawB)

@[noinline] def prepared2v2 (left right : Operand) : UInt32 :=
  exactPreparedV2 (pair left right)

def equivalenceStatementV2 : Prop := ∀ (rawA rawB : Array UInt32),
  let c := prepare rawA rawB
  c.matched = true → c.finite = true → exactPreparedV2 c = referencePrepared c

end Submission.R24ExactDotTiered
