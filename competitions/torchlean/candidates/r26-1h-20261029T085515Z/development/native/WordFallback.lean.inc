/- Runtime research only. A strict eligible64/128 guard selects plain word loops.
   All other inputs, including nonfinite and nonzero subnormal operands, use the
   original dotFn. No old canonical-NaN research replay is called or included. -/
namespace Submission.R26WordFallback
open ExactRuntime
open R24ExactDotCost

@[inline] def original (c : Cache) : UInt32 :=
  dotFn c.rawA.size (fun i => c.rawA[i]!) (fun i => c.rawB[i]!)

@[inline] def exact (c : Cache) : UInt32 :=
  if R24ExactDotTiered.eligible64 c then
    R24ExactDotTiered.native64Loop c.a c.b c.minScale 0 (c.a.size != 0) 0 c.a.size
  else if fastEligible c then
    nativeLoop c.a c.b c.minScale 0 (c.a.size != 0) 0 0 0 0 c.a.size
  else original c

structure Prepared where
  fp : R24PortableF64.Prepared
  word : Operand

instance : Inhabited Prepared :=
  ⟨⟨⟨#[], FloatArray.emptyWithCapacity 0, 0, false⟩,
    ⟨#[], #[], 0, 0, true, true, false⟩⟩⟩

def prepare (raw : Array UInt32) : Prepared :=
  ⟨R24PortableF64.prepare raw, prepareOperand raw⟩

@[inline] def dotPrepared (left right : Prepared) : UInt32 :=
  let guess := R24PortableF64.attemptPrepared left.fp right.fp
  if guess == 0 then exact (pair left.word right.word) else guess

end Submission.R26WordFallback
