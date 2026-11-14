/- Conditional frontend alternative only: keep original preparation, proposal,
   radius, strict certificate and miss semantics. Do not benchmark or adopt
   unless actual selected C shows an avoidable state/boxing cost in the original.
   Typing/native equivalence/cost remain NOT_RUN. -/
namespace Submission.R24PortableF64Tail

/-- Structural recursion on remaining count; accumulator argument/result is Float. -/
def sumRemaining (a b : FloatArray) (index : Nat) (acc : Float) (remaining : Nat) : Float :=
  match remaining with
  | 0 => acc
  | rest + 1 =>
    sumRemaining a b (index + 1) (acc + a.get! index * b.get! index) rest

/-- Proof-side readings, never constructed by either attempt callback. -/
def readings (a b : FloatArray) (index : Nat) (remaining : Nat) : List Float :=
  match remaining with
  | 0 => []
  | rest + 1 => a.get! index * b.get! index :: readings a b (index + 1) rest

/-- Only an order-preserving fold refinement; no associativity or accuracy claim. -/
theorem sumRemaining_eq_foldl (a b : FloatArray) (index : Nat) (acc : Float) (remaining : Nat) :
    sumRemaining a b index acc remaining =
      (readings a b index remaining).foldl (fun value product => value + product) acc := by
  induction remaining generalizing index acc with
  | zero => rfl
  | succ rest ih =>
    simpa only [sumRemaining, readings, List.foldl_cons] using
      ih (index + 1) (acc + a.get! index * b.get! index)

def attemptPrepared (x y : R24PortableF64.Prepared) : UInt32 :=
  let n := x.raw.size
  if n == 0 || n != y.raw.size then 0
  else if n > 1073741824 then 0
  else if !(x.valid && y.valid) then 0
  else
    let sum := sumRemaining x.values y.values 0 (Float.ofBits 0) n
    let sumWord := sum.toBits
    let guess := R24PortableF64.proposal sumWord
    let L := R24PortableF64.ceilLog2 n
    let H := x.maxIndex.toUInt64 + y.maxIndex.toUInt64
    let radius := Float.ofBits ((H + (L + L) + 720) <<< 52)
    if R24PortableF64.certify sum radius sumWord guess then guess else 0

def attemptCold (x y : Array UInt32) : UInt32 :=
  if x.size == 0 || x.size != y.size then 0
  else if x.size > 1073741824 then 0
  else attemptPrepared (R24PortableF64.prepare x) (R24PortableF64.prepare y)

end Submission.R24PortableF64Tail
