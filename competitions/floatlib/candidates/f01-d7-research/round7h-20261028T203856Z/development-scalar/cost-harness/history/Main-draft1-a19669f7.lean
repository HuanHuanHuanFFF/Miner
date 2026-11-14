import BenchFull
import BenchSuite
import Submission
import R24DotBarrier
open Lean
namespace R24DotCostHarness
open Submission
open R24DotBarrier
structure DotCase where
  name : String
  group : String
  kind : String
  x : Array Nat
  y : Array Nat
  expected : Nat
  fast_result : Option Nat
  timed : Bool
  deriving FromJson
structure RoundCase where
  id : String
  negative : Bool
  lo : Nat
  hi : Nat
  base : Int
  expected : Nat
  deriving FromJson
structure Plan where
  cases : Array DotCase
  round_cases : Array RoundCase
  deriving FromJson
structure Sample where
  trial : Nat
  n : Nat
  iters : Nat
  ns : Nat
  sink : UInt32
  expectedSink : UInt32
  keepWord : UInt32

def words (xs : Array Nat) : Array UInt32 := xs.map UInt32.ofNat
def supported (a b : Array UInt32) : Bool :=
  a.size != 0 && a.size == b.size &&
    a.all (fun w => (w >>> 23) &&& 255 != 255) &&
    b.all (fun w => (w >>> 23) &&& 255 != 255)
def repeats (macs n : Nat) : Nat := max 1 ((macs + max 1 n - 1) / max 1 n)
def seed (trial : Nat) : UInt32 := UInt32.ofNat (2654435769 + 1664525 * trial)
def sinkExpected (s expected : UInt32) (iters : Nat) : UInt32 :=
  s + UInt32.ofNat iters * expected
def checkWord (name stage : String) (got expected : UInt32) : IO Unit :=
  unless got == expected do
    throw (IO.userError s!"{name}: {stage} got={got.toNat} expected={expected.toNat}")
def emit (c : DotCase) (variant boundary : String) (prep life : Nat) (rows : Array Sample) : IO Unit := do
  let mut last : UInt32 := 0
  for r in rows do
    IO.println s!"DOT_SAMPLE\t{c.name}\t{c.group}\t{variant}\t{boundary}\t{r.trial}\t{r.n}\t{r.iters}\t{r.n * r.iters}\t{r.ns}\t{r.sink.toNat}\t{r.expectedSink.toNat}\t{r.keepWord.toNat}"
    last := r.keepWord
  IO.println s!"DOT_SETUP\t{c.name}\t{c.group}\t{variant}\t{boundary}\t{prep}\t{life}\t{rows.size}\t{last.toNat}"

@[noinline] def passExactFull (p : RawPair) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchRaw remaining p
    let word := R24DotProbe.exactFull p.1 p.2
    passExactFull p (s + word) remaining

@[noinline] def benchExactFull (c : DotCase) (a b : Array UInt32) (macs : Nat) : IO Unit := do
  let expected := UInt32.ofNat c.expected
  let iters := repeats macs a.size
  let lifeStart ← IO.monoNanosNow
  let (prepNs, rows) ← do
    let prepStart ← IO.monoNanosNow
    let p : RawPair ← IO.lazyPure fun _ => (a, b)
    let prepEnd ← IO.monoNanosNow
    let mut rows : Array Sample := #[]
    for trial in [0:3] do
      let warm ← IO.lazyPure fun _ => R24DotProbe.exactFull p.1 p.2
      checkWord c.name "ExactFull:warm" warm expected
      let s := seed trial
      let wanted := sinkExpected s expected iters
      let start ← IO.monoNanosNow
      let sink ← IO.lazyPure fun _ => passExactFull p s iters
      let finish ← IO.monoNanosNow
      checkWord c.name "ExactFull:sink" sink wanted
      let keep ← IO.lazyPure fun _ => R24DotProbe.exactFull p.1 p.2
      checkWord c.name "ExactFull:keep" keep expected
      rows := rows.push ⟨trial, a.size, iters, finish - start, sink, wanted, keep⟩
    pure ((0 : Nat), rows)
  let lifeEnd ← IO.monoNanosNow
  emit c "exact" "full" prepNs (lifeEnd - lifeStart) rows

@[noinline] def passEagerFull (p : RawPair) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchRaw remaining p
    let word := R24DotProbe.eagerFull p.1 p.2
    passEagerFull p (s + word) remaining

@[noinline] def benchEagerFull (c : DotCase) (a b : Array UInt32) (macs : Nat) : IO Unit := do
  let expected := UInt32.ofNat c.expected
  let iters := repeats macs a.size
  let lifeStart ← IO.monoNanosNow
  let (prepNs, rows) ← do
    let prepStart ← IO.monoNanosNow
    let p : RawPair ← IO.lazyPure fun _ => (a, b)
    let prepEnd ← IO.monoNanosNow
    let mut rows : Array Sample := #[]
    for trial in [0:3] do
      let warm ← IO.lazyPure fun _ => R24DotProbe.eagerFull p.1 p.2
      checkWord c.name "EagerFull:warm" warm expected
      let s := seed trial
      let wanted := sinkExpected s expected iters
      let start ← IO.monoNanosNow
      let sink ← IO.lazyPure fun _ => passEagerFull p s iters
      let finish ← IO.monoNanosNow
      checkWord c.name "EagerFull:sink" sink wanted
      let keep ← IO.lazyPure fun _ => R24DotProbe.eagerFull p.1 p.2
      checkWord c.name "EagerFull:keep" keep expected
      rows := rows.push ⟨trial, a.size, iters, finish - start, sink, wanted, keep⟩
    pure ((0 : Nat), rows)
  let lifeEnd ← IO.monoNanosNow
  emit c "eager" "full" prepNs (lifeEnd - lifeStart) rows

@[noinline] def passLazyFull (p : RawPair) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchRaw remaining p
    let word := R24DotProbe.lazyFull p.1 p.2
    passLazyFull p (s + word) remaining

@[noinline] def benchLazyFull (c : DotCase) (a b : Array UInt32) (macs : Nat) : IO Unit := do
  let expected := UInt32.ofNat c.expected
  let iters := repeats macs a.size
  let lifeStart ← IO.monoNanosNow
  let (prepNs, rows) ← do
    let prepStart ← IO.monoNanosNow
    let p : RawPair ← IO.lazyPure fun _ => (a, b)
    let prepEnd ← IO.monoNanosNow
    let mut rows : Array Sample := #[]
    for trial in [0:3] do
      let warm ← IO.lazyPure fun _ => R24DotProbe.lazyFull p.1 p.2
      checkWord c.name "LazyFull:warm" warm expected
      let s := seed trial
      let wanted := sinkExpected s expected iters
      let start ← IO.monoNanosNow
      let sink ← IO.lazyPure fun _ => passLazyFull p s iters
      let finish ← IO.monoNanosNow
      checkWord c.name "LazyFull:sink" sink wanted
      let keep ← IO.lazyPure fun _ => R24DotProbe.lazyFull p.1 p.2
      checkWord c.name "LazyFull:keep" keep expected
      rows := rows.push ⟨trial, a.size, iters, finish - start, sink, wanted, keep⟩
    pure ((0 : Nat), rows)
  let lifeEnd ← IO.monoNanosNow
  emit c "lazy" "full" prepNs (lifeEnd - lifeStart) rows

@[noinline] def passExactPrepared (p : ExactPair) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchExact remaining p
    let word := R24DotProbe.exactPrepared p.1 p.2
    passExactPrepared p (s + word) remaining

@[noinline] def benchExactPrepared (c : DotCase) (a b : Array UInt32) (macs : Nat) : IO Unit := do
  let expected := UInt32.ofNat c.expected
  let iters := repeats macs a.size
  let lifeStart ← IO.monoNanosNow
  let (prepNs, rows) ← do
    let prepStart ← IO.monoNanosNow
    let p : ExactPair ← IO.lazyPure fun _ => (R24ExactDotCost.prepareOperand a, R24ExactDotCost.prepareOperand b)
    let prepEnd ← IO.monoNanosNow
    let mut rows : Array Sample := #[]
    for trial in [0:3] do
      let warm ← IO.lazyPure fun _ => R24DotProbe.exactPrepared p.1 p.2
      checkWord c.name "ExactPrepared:warm" warm expected
      let s := seed trial
      let wanted := sinkExpected s expected iters
      let start ← IO.monoNanosNow
      let sink ← IO.lazyPure fun _ => passExactPrepared p s iters
      let finish ← IO.monoNanosNow
      checkWord c.name "ExactPrepared:sink" sink wanted
      let keep ← IO.lazyPure fun _ => R24DotProbe.exactPrepared p.1 p.2
      checkWord c.name "ExactPrepared:keep" keep expected
      rows := rows.push ⟨trial, a.size, iters, finish - start, sink, wanted, keep⟩
    pure (prepEnd - prepStart, rows)
  let lifeEnd ← IO.monoNanosNow
  emit c "exact" "prepared" prepNs (lifeEnd - lifeStart) rows

@[noinline] def passEagerPrepared (p : R24DotProbe.Eager) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchEager remaining p
    let word := R24DotProbe.eagerPrepared p
    passEagerPrepared p (s + word) remaining

@[noinline] def benchEagerPrepared (c : DotCase) (a b : Array UInt32) (macs : Nat) : IO Unit := do
  let expected := UInt32.ofNat c.expected
  let iters := repeats macs a.size
  let lifeStart ← IO.monoNanosNow
  let (prepNs, rows) ← do
    let prepStart ← IO.monoNanosNow
    let p : R24DotProbe.Eager ← IO.lazyPure fun _ => R24DotProbe.prepareEager a b
    let prepEnd ← IO.monoNanosNow
    let mut rows : Array Sample := #[]
    for trial in [0:3] do
      let warm ← IO.lazyPure fun _ => R24DotProbe.eagerPrepared p
      checkWord c.name "EagerPrepared:warm" warm expected
      let s := seed trial
      let wanted := sinkExpected s expected iters
      let start ← IO.monoNanosNow
      let sink ← IO.lazyPure fun _ => passEagerPrepared p s iters
      let finish ← IO.monoNanosNow
      checkWord c.name "EagerPrepared:sink" sink wanted
      let keep ← IO.lazyPure fun _ => R24DotProbe.eagerPrepared p
      checkWord c.name "EagerPrepared:keep" keep expected
      rows := rows.push ⟨trial, a.size, iters, finish - start, sink, wanted, keep⟩
    pure (prepEnd - prepStart, rows)
  let lifeEnd ← IO.monoNanosNow
  emit c "eager" "prepared" prepNs (lifeEnd - lifeStart) rows

@[noinline] def passLazyPrepared (p : LazyPair) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchLazy remaining p
    let word := R24DotProbe.lazyPrepared p.1 p.2
    passLazyPrepared p (s + word) remaining

@[noinline] def benchLazyPrepared (c : DotCase) (a b : Array UInt32) (macs : Nat) : IO Unit := do
  let expected := UInt32.ofNat c.expected
  let iters := repeats macs a.size
  let lifeStart ← IO.monoNanosNow
  let (prepNs, rows) ← do
    let prepStart ← IO.monoNanosNow
    let p : LazyPair ← IO.lazyPure fun _ => (R24PortableF64.prepare a, R24PortableF64.prepare b)
    let prepEnd ← IO.monoNanosNow
    let mut rows : Array Sample := #[]
    for trial in [0:3] do
      let warm ← IO.lazyPure fun _ => R24DotProbe.lazyPrepared p.1 p.2
      checkWord c.name "LazyPrepared:warm" warm expected
      let s := seed trial
      let wanted := sinkExpected s expected iters
      let start ← IO.monoNanosNow
      let sink ← IO.lazyPure fun _ => passLazyPrepared p s iters
      let finish ← IO.monoNanosNow
      checkWord c.name "LazyPrepared:sink" sink wanted
      let keep ← IO.lazyPure fun _ => R24DotProbe.lazyPrepared p.1 p.2
      checkWord c.name "LazyPrepared:keep" keep expected
      rows := rows.push ⟨trial, a.size, iters, finish - start, sink, wanted, keep⟩
    pure (prepEnd - prepStart, rows)
  let lifeEnd ← IO.monoNanosNow
  emit c "lazy" "prepared" prepNs (lifeEnd - lifeStart) rows

def verify (plan : Plan) : IO Unit := do
  let mut accepts := 0
  let mut unknown := 0
  for c in plan.cases do
    if c.expected > 4294967295 || c.x.any (fun w => decide (w > 4294967295)) ||
        c.y.any (fun w => decide (w > 4294967295)) then
      throw (IO.userError s!"{c.name}: fixture word exceeds UInt32")
    let a := words c.x
    let b := words c.y
    let want := UInt32.ofNat c.expected
    let ea := R24ExactDotCost.prepareOperand a
    let eb := R24ExactDotCost.prepareOperand b
    let fa := R24PortableF64.prepare a
    let fb := R24PortableF64.prepare b
    let eager : R24DotProbe.Eager := ⟨ea, eb, fa, fb⟩
    let cache := R24ExactDotCost.pair ea eb
    let fastCold ← IO.lazyPure fun _ => R24PortableF64.attemptCold a b
    let fastPrepared ← IO.lazyPure fun _ => R24PortableF64.attemptPrepared fa fb
    match c.fast_result with
    | some e =>
      if e > 4294967295 then throw (IO.userError s!"{c.name}: fast_result exceeds UInt32")
      checkWord c.name "fastCold" fastCold (UInt32.ofNat e)
      checkWord c.name "fastPrepared" fastPrepared (UInt32.ofNat e)
    | none =>
      unknown := unknown + 1
      if (fastCold != 0 && fastCold != want) || (fastPrepared != 0 && fastPrepared != want) then
        throw (IO.userError s!"{c.name}: unknown fast proposal is incorrect")
    let x0 ← IO.lazyPure fun _ => R24DotProbe.exactFull a b
    let x1 ← IO.lazyPure fun _ => R24DotProbe.eagerFull a b
    let x2 ← IO.lazyPure fun _ => R24DotProbe.lazyFull a b
    let x3 ← IO.lazyPure fun _ => R24DotProbe.exactPrepared ea eb
    let x4 ← IO.lazyPure fun _ => R24DotProbe.eagerPrepared eager
    let x5 ← IO.lazyPure fun _ => R24DotProbe.lazyPrepared fa fb
    let old ← IO.lazyPure fun _ => R24ExactDotCost.exactPrepared cache
    let reference ← IO.lazyPure fun _ => R24ExactDotCost.referencePrepared cache
    checkWord c.name "exactFull" x0 want
    checkWord c.name "eagerFull" x1 want
    checkWord c.name "lazyFull" x2 want
    checkWord c.name "exactPrepared" x3 want
    checkWord c.name "eagerPrepared" x4 want
    checkWord c.name "lazyPrepared" x5 want
    checkWord c.name "baseline128" old want
    checkWord c.name "reference" reference want
    if fastPrepared != 0 then accepts := accepts + 1
    IO.println s!"DOT_VERIFY\t{c.name}\t{want.toNat}\t{fastCold.toNat}\t{fastPrepared.toNat}\t{x0.toNat}\t{x1.toNat}\t{x2.toNat}\t{x3.toNat}\t{x4.toNat}\t{x5.toNat}\t{old.toNat}\t{reference.toNat}\ttrue"
  for c in plan.round_cases do
    if c.lo > 18446744073709551615 || c.hi > 18446744073709551615 || c.expected > 4294967295 then
      throw (IO.userError s!"{c.id}: round fixture word out of range")
    let q ← IO.lazyPure fun _ => R24ExactDotCost.round128 c.negative (UInt64.ofNat c.lo) (UInt64.ofNat c.hi) c.base
    checkWord c.id "round128" q (UInt32.ofNat c.expected)
    IO.println s!"DOT_ROUND\t{c.id}\t{c.expected}\t{q.toNat}\ttrue"
  IO.println s!"DOT_VERIFY_DONE\t{plan.cases.size}\t{plan.round_cases.size}\t{accepts}\t{unknown}"

def env (name : String) : IO String := do
  let some value ← IO.getEnv name | throw (IO.userError s!"Missing {name}")
  return value

def run : IO UInt32 := do
  let path ← env "BENCH_DOT_FIXTURE"
  let text ← IO.FS.readFile (System.FilePath.mk path)
  let plan ← match Json.parse text >>= fromJson? (α := Plan) with
    | .ok p => pure p
    | .error e => throw (IO.userError s!"BENCH_DOT_FIXTURE: {e}")
  let mode := (← IO.getEnv "BENCH_DOT_MODE").getD "verify"
  if mode == "verify" then
    verify plan
    return 0
  if mode != "measure" then throw (IO.userError "BENCH_DOT_MODE must be verify or measure")
  let group ← env "BENCH_DOT_GROUP"
  let variant ← env "BENCH_DOT_VARIANT"
  let boundary ← env "BENCH_DOT_BOUNDARY"
  if group != "24282403" && group != "24282405" then throw (IO.userError "Invalid BENCH_DOT_GROUP")
  if variant != "exact" && variant != "eager" && variant != "lazy" then throw (IO.userError "Invalid BENCH_DOT_VARIANT")
  if boundary != "full" && boundary != "prepared" then throw (IO.userError "Invalid BENCH_DOT_BOUNDARY")
  let macText := (← IO.getEnv "BENCH_DOT_MACS").getD "131072"
  let some macs := macText.toNat? | throw (IO.userError "Invalid BENCH_DOT_MACS")
  if macs > 16777216 then throw (IO.userError "BENCH_DOT_MACS exceeds2^24")
  let mut count := 0
  for c in plan.cases do
    if c.timed && (c.group == group || c.group == "directed") then
      let a ← IO.lazyPure fun _ => words c.x
      let b ← IO.lazyPure fun _ => words c.y
      if supported a b then
        if variant == "exact" && boundary == "full" then benchExactFull c a b macs
        else if variant == "eager" && boundary == "full" then benchEagerFull c a b macs
        else if variant == "lazy" && boundary == "full" then benchLazyFull c a b macs
        else if variant == "exact" && boundary == "prepared" then benchExactPrepared c a b macs
        else if variant == "eager" && boundary == "prepared" then benchEagerPrepared c a b macs
        else if variant == "lazy" && boundary == "prepared" then benchLazyPrepared c a b macs
        else throw (IO.userError "Unreachable dot mode")
        count := count + 1
      else IO.println s!"DOT_SKIP\t{c.name}\t{c.group}\tunsupported_or_empty"
  IO.println s!"DOT_MEASURE_DONE\t{group}\t{variant}\t{boundary}\t{count}\t3"
  return 0
end R24DotCostHarness
def main : IO UInt32 := R24DotCostHarness.run
