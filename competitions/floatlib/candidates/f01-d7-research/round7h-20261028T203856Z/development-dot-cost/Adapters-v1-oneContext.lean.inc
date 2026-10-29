/- Generic cost-probe adapters. The original four public callbacks are unchanged.
   All new runtime bodies and their composition remain unproved. -/
namespace Submission.R24DotProbe

abbrev ExactOperand := R24ExactDotCost.Operand
abbrev FpPrepared := R24PortableF64.Prepared

structure Eager where
  exactA : ExactOperand
  exactB : ExactOperand
  fpA : FpPrepared
  fpB : FpPrepared

def prepareEager (a b : Array UInt32) : Eager :=
  ⟨R24ExactDotCost.prepareOperand a, R24ExactDotCost.prepareOperand b,
    R24PortableF64.prepare a, R24PortableF64.prepare b⟩

@[noinline] def exactFull (a b : Array UInt32) : UInt32 :=
  R24ExactDotTiered.fullv2 a b

@[noinline] def exactPrepared (a b : ExactOperand) : UInt32 :=
  R24ExactDotTiered.prepared2v2 a b

@[noinline] def eagerPrepared (c : Eager) : UInt32 :=
  let q := R24PortableF64.attemptPrepared c.fpA c.fpB
  if q == 0 then R24ExactDotTiered.prepared2v2 c.exactA c.exactB else q

@[noinline] def eagerFull (a b : Array UInt32) : UInt32 :=
  eagerPrepared (prepareEager a b)

@[noinline] def lazyPrepared (a b : FpPrepared) : UInt32 :=
  let q := R24PortableF64.attemptPrepared a b
  if q == 0 then R24ExactDotTiered.fullv2 a.raw b.raw else q

@[noinline] def lazyFull (a b : Array UInt32) : UInt32 :=
  let q := R24PortableF64.attemptCold a b
  if q == 0 then R24ExactDotTiered.fullv2 a b else q

end Submission.R24DotProbe
