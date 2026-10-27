/- Diagnostic metadata only. Never part of Kernel.lean or the timed executable.
   Uses unchanged official operands and exact622d underflow predicate. NOT_RUN. -/
import Submission
import BenchSuite

open FloatLib.Floats Competition Lean

def routeLabel (c : Bench.Suite.Case) : String × Bool × Bool :=
  let a := Vector.ofFn (n := c.batch * c.m * c.n) fun i =>
    Bench.Suite.float (Bench.Suite.element c i.val 0 c.n)
  let b := Vector.ofFn (n := c.batch * c.n * c.p) fun i =>
    Bench.Suite.float (Bench.Suite.element c i.val 1 c.p)
  let aSmall := a.toArray.all Submission.UnderflowZero.small
  let bSmall := b.toArray.all Submission.UnderflowZero.small
  let route :=
    if aSmall && bSmall then "UnderflowZero"
    else if 2 ≤ c.p ∧ c.p ≤ 8 ∧ 1 < c.n ∧ 4 ≤ c.m then "B2"
    else if 4 ≤ c.m ∧ 1 < c.n ∧ 0 < c.p ∧ c.p ≤ 2 then "B1"
    else if (c.n ≤ 4 ∧ 2 < c.p) ∨ c.p ≤ 8 then "DirectContinuous"
    else if c.n ≤ 4 ∨ c.p ≤ 2 then "DirectSmall"
    else if c.batch * c.m * c.p = 0 then "Reference"
    else if c.n = 0 then "Reference"
    else "Packed10"
  (route, aSmall, bSmall)

def main (args : List String) : IO UInt32 := do
  let [path] := args | throw (IO.userError "expected exact seen plan path")
  let text ← IO.FS.readFile path
  let plan ← match Json.parse text >>= fromJson? (α := Bench.Suite.Plan) with
    | .ok p => pure p
    | .error e => throw (IO.userError e)
  if plan.version != "suite-v2" then throw (IO.userError "wrong plan version")
  for c in plan.cases do
    if c.kernel == "bmm" then
      let (route, aSmall, bSmall) := routeLabel c
      IO.println s!"ROUTE19 {c.name} {route} {aSmall} {bSmall}"
  return 0
