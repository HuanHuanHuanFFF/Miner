/- Diagnostic metadata only. Never part of Kernel.lean or the timed executable.
   Uses unchanged official operands and exact622d underflow predicate. NOT_RUN. -/
import Submission
import BenchSuite

open FloatLib.Floats Competition Lean

def allSmallFrom (c : Bench.Suite.Case) (count role row k : Nat) : Bool :=
  if hk : k < count then
    if Submission.UnderflowZero.small
        (Bench.Suite.float (Bench.Suite.element c k role row)) then
      allSmallFrom c count role row (k + 1)
    else false
  else true
termination_by count - k
decreasing_by omega

def routeLabel (c : Bench.Suite.Case) : String × Bool × Bool :=
  let aSmall := allSmallFrom c (c.batch * c.m * c.n) 0 c.n 0
  let bSmall := allSmallFrom c (c.batch * c.n * c.p) 1 c.p 0
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
