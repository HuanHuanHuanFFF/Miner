import BenchFull
import BenchSuite
import Submission
import R24DotBarrier
open Lean
namespace R24DotBankHarness
open Submission R24DotBarrier
structure BankCase where
  name : String
  group : String
  inner : Nat
  rows : Nat
  cols : Nat
  rowsA : Array (Array Nat)
  rowsB : Array (Array Nat)
  expected : Array Nat
  deriving FromJson
structure Plan where
  cases : Array BankCase
  deriving FromJson
structure Sample where
  trial : Nat
  work : Nat
  iters : Nat
  ns : Nat
  sink : UInt32
  expectedSink : UInt32
  keepWord : UInt32
def words (xs : Array (Array Nat)) : RawBank := xs.map (fun row => row.map UInt32.ofNat)
def outputWords (xs : Array Nat) : Array UInt32 := xs.map UInt32.ofNat
def sumRemaining (out : Array UInt32) (index : Nat) (acc : UInt32) (remaining : Nat) : UInt32 :=
  match remaining with
  | 0 => acc
  | rest + 1 => sumRemaining out (index + 1) (acc + out[index]!) rest
@[noinline] def hashAll (out : Array UInt32) : UInt32 := sumRemaining out 0 0 out.size
def seed (trial : Nat) : UInt32 := UInt32.ofNat (2654435769 + 1664525 * trial)
def repeats (macs work : Nat) : Nat := max 1 ((macs + max 1 work - 1) / max 1 work)
def checkWord (name stage : String) (got expected : UInt32) : IO Unit := do
  unless got == expected do
    throw (IO.userError s!"{name}: {stage} got={got.toNat} expected={expected.toNat}")
def checkArray (name stage : String) (got expected : Array UInt32) : IO Unit := do
  if got.size != expected.size then throw (IO.userError s!"{name}: {stage} output length")
  for i in [:expected.size] do
    unless got[i]! == expected[i]! do
      throw (IO.userError s!"{name}: {stage} output {i} differs")
def checkCase (c : BankCase) : IO Unit := do
  if c.rowsA.size != c.rows || c.rowsB.size != c.cols || c.expected.size != c.rows * c.cols then
    throw (IO.userError s!"{c.name}: shape metadata differs")
  if c.inner == 0 || c.rows == 0 || c.cols == 0 then throw (IO.userError s!"{c.name}: empty bank")
  if c.rowsA.any (fun row => row.size != c.inner || row.any (fun w => decide (w > 4294967295))) ||
      c.rowsB.any (fun row => row.size != c.inner || row.any (fun w => decide (w > 4294967295))) ||
      c.expected.any (fun w => decide (w > 4294967295)) then
    throw (IO.userError s!"{c.name}: invalid row or word")
def emit (c : BankCase) (variant : String) (life : Nat) (rows : Array Sample) : IO Unit := do
  let mut last : UInt32 := 0
  for r in rows do
    IO.println s!"BANK_SAMPLE\t{c.name}\t{c.group}\t{variant}\tfull\t{r.trial}\t{r.work}\t{r.iters}\t{r.work*r.iters}\t{r.ns}\t{r.sink.toNat}\t{r.expectedSink.toNat}\t{r.keepWord.toNat}"
    last := r.keepWord
  IO.println s!"BANK_SETUP\t{c.name}\t{c.group}\t{variant}\tfull\t0\t{life}\t{rows.size}\t{last.toNat}"

@[noinline] def passExact (p : BankPair) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchBank remaining p
    let out := R24GenericDotBank.exactBank p.1 p.2
    let word := hashAll out
    passExact p (s + word) remaining
@[noinline] def benchExact (c : BankCase) (a b : RawBank) (macs : Nat) (expected : UInt32) : IO Unit := do
  let work := c.rows * c.cols * c.inner
  let iters := repeats macs work
  let p : BankPair ← IO.lazyPure fun _ => (a, b)
  let lifeStart ← IO.monoNanosNow
  let mut rows : Array Sample := #[]
  for trial in [0:3] do
    let warm ← IO.lazyPure fun _ => hashAll (R24GenericDotBank.exactBank p.1 p.2)
    checkWord c.name "exact:warm" warm expected
    let s := seed trial
    let wanted := s + UInt32.ofNat iters * expected
    let start ← IO.monoNanosNow
    let sink ← IO.lazyPure fun _ => passExact p s iters
    let finish ← IO.monoNanosNow
    checkWord c.name "exact:sink" sink wanted
    let keep ← IO.lazyPure fun _ => hashAll (R24GenericDotBank.exactBank p.1 p.2)
    checkWord c.name "exact:keep" keep expected
    rows := rows.push ⟨trial, work, iters, finish-start, sink, wanted, keep⟩
  let lifeEnd ← IO.monoNanosNow
  emit c "exact" (lifeEnd-lifeStart) rows

@[noinline] def passEager (p : BankPair) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchBank remaining p
    let out := R24GenericDotBank.eagerBank p.1 p.2
    let word := hashAll out
    passEager p (s + word) remaining
@[noinline] def benchEager (c : BankCase) (a b : RawBank) (macs : Nat) (expected : UInt32) : IO Unit := do
  let work := c.rows * c.cols * c.inner
  let iters := repeats macs work
  let p : BankPair ← IO.lazyPure fun _ => (a, b)
  let lifeStart ← IO.monoNanosNow
  let mut rows : Array Sample := #[]
  for trial in [0:3] do
    let warm ← IO.lazyPure fun _ => hashAll (R24GenericDotBank.eagerBank p.1 p.2)
    checkWord c.name "eager:warm" warm expected
    let s := seed trial
    let wanted := s + UInt32.ofNat iters * expected
    let start ← IO.monoNanosNow
    let sink ← IO.lazyPure fun _ => passEager p s iters
    let finish ← IO.monoNanosNow
    checkWord c.name "eager:sink" sink wanted
    let keep ← IO.lazyPure fun _ => hashAll (R24GenericDotBank.eagerBank p.1 p.2)
    checkWord c.name "eager:keep" keep expected
    rows := rows.push ⟨trial, work, iters, finish-start, sink, wanted, keep⟩
  let lifeEnd ← IO.monoNanosNow
  emit c "eager" (lifeEnd-lifeStart) rows

@[noinline] def passLazy (p : BankPair) (s : UInt32) (iters : Nat) : UInt32 :=
  match iters with
  | 0 => s
  | remaining + 1 =>
    let p := touchBank remaining p
    let out := R24GenericDotBank.lazyBank p.1 p.2
    let word := hashAll out
    passLazy p (s + word) remaining
@[noinline] def benchLazy (c : BankCase) (a b : RawBank) (macs : Nat) (expected : UInt32) : IO Unit := do
  let work := c.rows * c.cols * c.inner
  let iters := repeats macs work
  let p : BankPair ← IO.lazyPure fun _ => (a, b)
  let lifeStart ← IO.monoNanosNow
  let mut rows : Array Sample := #[]
  for trial in [0:3] do
    let warm ← IO.lazyPure fun _ => hashAll (R24GenericDotBank.lazyBank p.1 p.2)
    checkWord c.name "lazy:warm" warm expected
    let s := seed trial
    let wanted := s + UInt32.ofNat iters * expected
    let start ← IO.monoNanosNow
    let sink ← IO.lazyPure fun _ => passLazy p s iters
    let finish ← IO.monoNanosNow
    checkWord c.name "lazy:sink" sink wanted
    let keep ← IO.lazyPure fun _ => hashAll (R24GenericDotBank.lazyBank p.1 p.2)
    checkWord c.name "lazy:keep" keep expected
    rows := rows.push ⟨trial, work, iters, finish-start, sink, wanted, keep⟩
  let lifeEnd ← IO.monoNanosNow
  emit c "lazy" (lifeEnd-lifeStart) rows

def verify (plan : Plan) : IO Unit := do
  let mut total := 0
  for c in plan.cases do
    checkCase c
    let a := words c.rowsA
    let b := words c.rowsB
    let expected := outputWords c.expected
    let q0 ← IO.lazyPure fun _ => R24GenericDotBank.exactBank a b
    let q1 ← IO.lazyPure fun _ => R24GenericDotBank.eagerBank a b
    let q2 ← IO.lazyPure fun _ => R24GenericDotBank.lazyBank a b
    checkArray c.name "exact" q0 expected
    checkArray c.name "eager" q1 expected
    checkArray c.name "lazy" q2 expected
    let want := hashAll expected
    let h0 := hashAll q0
    let h1 := hashAll q1
    let h2 := hashAll q2
    checkWord c.name "exactSum" h0 want
    checkWord c.name "eagerSum" h1 want
    checkWord c.name "lazySum" h2 want
    total := total + c.expected.size
    IO.println s!"BANK_VERIFY\t{c.name}\t{c.expected.size}\t{want.toNat}\t{h0.toNat}\t{h1.toNat}\t{h2.toNat}\ttrue"
  IO.println s!"BANK_VERIFY_DONE\t{plan.cases.size}\t{total}\t3"
def env (name : String) : IO String := do
  let some v ← IO.getEnv name | throw (IO.userError s!"Missing {name}")
  return v
def run : IO UInt32 := do
  let path ← env "BENCH_DOT_FIXTURE"
  let text ← IO.FS.readFile (System.FilePath.mk path)
  let plan ← match Json.parse text >>= fromJson? (α := Plan) with
    | .ok p => pure p
    | .error e => throw (IO.userError s!"bank fixture: {e}")
  let mode := (← IO.getEnv "BENCH_DOT_MODE").getD "verify"
  if mode == "verify" then
    verify plan
    return 0
  if mode != "measure" then throw (IO.userError "Invalid BENCH_DOT_MODE")
  let group ← env "BENCH_DOT_GROUP"
  let variant ← env "BENCH_DOT_VARIANT"
  let boundary := (← IO.getEnv "BENCH_DOT_BOUNDARY").getD "full"
  if group != "24282601" && group != "24282603" then throw (IO.userError "Invalid bank group")
  if variant != "exact" && variant != "eager" && variant != "lazy" then throw (IO.userError "Invalid bank variant")
  if boundary != "full" then throw (IO.userError "Bank has no prepared boundary")
  let macText := (← IO.getEnv "BENCH_DOT_MACS").getD "131072"
  let some macs := macText.toNat? | throw (IO.userError "Invalid BENCH_DOT_MACS")
  if macs > 16777216 then throw (IO.userError "MACS exceeds2^24")
  let mut count := 0
  for c in plan.cases do
    if c.group == group then
      checkCase c
      let a ← IO.lazyPure fun _ => words c.rowsA
      let b ← IO.lazyPure fun _ => words c.rowsB
      let expected := hashAll (outputWords c.expected)
      if variant == "exact" then benchExact c a b macs expected
      else if variant == "eager" then benchEager c a b macs expected
      else benchLazy c a b macs expected
      count := count + 1
  IO.println s!"BANK_MEASURE_DONE\t{group}\t{variant}\tfull\t{count}\t3"
  return 0
end R24DotBankHarness
def main : IO UInt32 := R24DotBankHarness.run
