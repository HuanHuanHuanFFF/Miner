/- Generic cost-probe adapters. The original four public callbacks are unchanged.
   All new runtime bodies and their composition remain unproved. -/
namespace Submission.R24DotProbe

abbrev ExactOperand := R24ExactDotCost.Operand
abbrev FpPrepared := R24PortableF64.Prepared

structure EagerOperand where
  exact : ExactOperand
  fp : FpPrepared

def prepareEagerOperand (a : Array UInt32) : EagerOperand :=
  ⟨R24ExactDotCost.prepareOperand a, R24PortableF64.prepare a⟩

@[noinline] def exactFull (a b : Array UInt32) : UInt32 :=
  R24ExactDotTiered.fullv2 a b

@[noinline] def exactPrepared (a b : ExactOperand) : UInt32 :=
  R24ExactDotTiered.prepared2v2 a b

@[noinline] def eagerPrepared (a b : EagerOperand) : UInt32 :=
  let q := R24PortableF64.attemptPrepared a.fp b.fp
  if q == 0 then R24ExactDotTiered.prepared2v2 a.exact b.exact else q

@[noinline] def eagerFull (a b : Array UInt32) : UInt32 :=
  eagerPrepared (prepareEagerOperand a) (prepareEagerOperand b)

@[noinline] def lazyPrepared (a b : FpPrepared) : UInt32 :=
  let q := R24PortableF64.attemptPrepared a b
  if q == 0 then R24ExactDotTiered.fullv2 a.raw b.raw else q

@[noinline] def lazyFull (a b : Array UInt32) : UInt32 :=
  let q := R24PortableF64.attemptCold a b
  if q == 0 then R24ExactDotTiered.fullv2 a b else q

end Submission.R24DotProbe
