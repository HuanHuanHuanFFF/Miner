/- Generic research caller only, not a competition matrix kernel.
   Primary operand-row caches are prepared once inside each whole call.
   Lazy misses retain the selected Probe's full exact fallback and its cost.
   All new equivalence/caller/native/cost claims are UNPROVED/NOT_RUN. -/
namespace Submission.R24GenericDotBank

/-- Row-major flattened all-pairs dot results; integer row caches built here. -/
@[noinline] def exactBank (rowsA rowsB : Array (Array UInt32)) : Array UInt32 := Id.run do
  let mut a : Array R24DotProbe.ExactOperand := Array.emptyWithCapacity rowsA.size
  for row in rowsA do
    a := a.push (R24ExactDotCost.prepareOperand row)
  let mut b : Array R24DotProbe.ExactOperand := Array.emptyWithCapacity rowsB.size
  for row in rowsB do
    b := b.push (R24ExactDotCost.prepareOperand row)
  let mut out : Array UInt32 := Array.emptyWithCapacity (rowsA.size * rowsB.size)
  for left in a do
    for right in b do
      out := out.push (R24DotProbe.exactPrepared left right)
  return out

/-- Both exact and FP caches prepared once per independent input row. -/
@[noinline] def eagerBank (rowsA rowsB : Array (Array UInt32)) : Array UInt32 := Id.run do
  let mut a : Array R24DotProbe.EagerOperand := Array.emptyWithCapacity rowsA.size
  for row in rowsA do
    a := a.push (R24DotProbe.prepareEagerOperand row)
  let mut b : Array R24DotProbe.EagerOperand := Array.emptyWithCapacity rowsB.size
  for row in rowsB do
    b := b.push (R24DotProbe.prepareEagerOperand row)
  let mut out : Array UInt32 := Array.emptyWithCapacity (rowsA.size * rowsB.size)
  for left in a do
    for right in b do
      out := out.push (R24DotProbe.eagerPrepared left right)
  return out

/-- FP row caches only; exact preparation on a miss stays inside lazyPrepared. -/
@[noinline] def lazyBank (rowsA rowsB : Array (Array UInt32)) : Array UInt32 := Id.run do
  let mut a : Array R24DotProbe.FpPrepared := Array.emptyWithCapacity rowsA.size
  for row in rowsA do
    a := a.push (R24PortableF64.prepare row)
  let mut b : Array R24DotProbe.FpPrepared := Array.emptyWithCapacity rowsB.size
  for row in rowsB do
    b := b.push (R24PortableF64.prepare row)
  let mut out : Array UInt32 := Array.emptyWithCapacity (rowsA.size * rowsB.size)
  for left in a do
    for right in b do
      out := out.push (R24DotProbe.lazyPrepared left right)
  return out

end Submission.R24GenericDotBank
