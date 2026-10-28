import BenchFull
import BenchSuite
import Submission
open Competition Lean
def main : IO UInt32 := do
  let some text ← IO.getEnv "BENCH_PLAN"
    | throw (IO.userError "BENCH_PLAN is required")
  let plan ← match Json.parse text >>= fromJson? (α := Bench.Suite.Plan) with
    | .ok p => pure p
    | .error e => throw (IO.userError e)
  if plan.version != "suite-v2" then throw (IO.userError "plan version")
  for c in plan.cases do
    if c.kernel == "mul" then
      let mut both := 0
      let mut integerOnly := 0
      let mut nativeOnly := 0
      let mut neither := 0
      let mut sink : UInt32 := 0
      let mut bu : UInt32 := 0
      let mut bv : UInt32 := 0
      let mut iu : UInt32 := 0
      let mut iv : UInt32 := 0
      let mut nu : UInt32 := 0
      let mut nv : UInt32 := 0
      let mut zu : UInt32 := 0
      let mut zv : UInt32 := 0
      for i in [0:c.work] do
        let u := Bench.Suite.element c i 0 31
        let v := Bench.Suite.partner c i u
        let native := Submission.R24Scalar.pairOK u v
        let eu := (u >>> 23) &&& (255 : UInt32)
        let ev := (v >>> 23) &&& (255 : UInt32)
        let integer := eu-1 ≤ (253 : UInt32) && ev-1 ≤ (253 : UInt32) && eu+ev-128 ≤ (252 : UInt32)
        if native && integer then
          if both == 0 then
            bu := u
            bv := v
          both := both+1
        else if integer then
          if integerOnly == 0 then
            iu := u
            iv := v
          integerOnly := integerOnly+1
        else if native then
          if nativeOnly == 0 then
            nu := u
            nv := v
          nativeOnly := nativeOnly+1
        else
          if neither == 0 then
            zu := u
            zv := v
          neither := neither+1
        sink := (sink ^^^ u ^^^ v) * 16777619
      IO.println s!"DOMAIN {c.name} {c.work} {both} {integerOnly} {nativeOnly} {neither} {sink}"
      IO.println s!"EXAMPLE {c.name} {bu} {bv} {iu} {iv} {nu} {nv} {zu} {zv}"
  return 0
