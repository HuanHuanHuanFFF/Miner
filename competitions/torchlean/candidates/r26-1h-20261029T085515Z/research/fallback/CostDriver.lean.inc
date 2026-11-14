namespace R26WordCost
open Submission.R26WordBlock ExactRuntime

structure Fixture where
  n : Nat
  outputs : Nat
  x : Array UInt32
  w : Array UInt32
  bias : Array UInt32
  expected : Array UInt32

structure Prepared where
  values : Array UInt32
  base : Nat
  maximum : UInt32
  deriving Inhabited

def scan (f : Nat → UInt32) : Nat → Nat → Nat → Nat → Bool → Bool → Nat × Nat × Bool × Bool
  | 0, _, low, high, seen, finite => (low, high, seen, finite)
  | count + 1, i, low, high, seen, finite =>
    let w := f i
    let active := mantOf w != 0
    let e := idxOf w
    scan f count (i + 1)
      (if active && (!seen || e < low) then e else low)
      (if active && (!seen || high < e) then e else high)
      (seen || active) (finite && expOf w != 255)

@[inline] def factor (w : UInt32) (base : Nat) : UInt32 :=
  let m := UInt32.ofNat (mantOf w * 2 ^ (idxOf w - base))
  if signOf w then 0 - m else m

@[noinline] def prepare (n : Nat) (f : Nat → UInt32) : Option Prepared :=
  let s := scan f n 0 0 0 false true
  if !s.2.2.2 || s.2.1 - s.1 > 7 then none else
    let values := Array.ofFn (n := n) fun i => factor (f i.val) s.1
    let mx := maxMagnitude (fun i => values[i]!) n 0 0
    some ⟨values, s.1, mx⟩

@[noinline] def output (blocked : Bool) (n : Nat) (x w : Prepared) (bias : UInt32) : UInt32 :=
  let pair := if blocked && canBlock16 n x.maximum w.maximum then
      body128 n (fun i => x.values[i]!) (fun i => w.values[i]!)
    else body128Each (fun i => x.values[i]!) (fun i => w.values[i]!) n 0 0 0
  let shift := idxOf bias + 149 - (x.base + w.base)
  let b : Int := sv bias * 2 ^ shift
  act true (finishWord (signed128 pair.1 pair.2 + b) (((x.base + w.base : Nat) : Int) - 298) false)

@[noinline] def runPrepared (blocked : Bool) (f : Fixture)
    (x : Prepared) (w : Array Prepared) : Array UInt32 :=
  Array.ofFn (n := f.outputs) fun j => output blocked f.n x w[j.val]! f.bias[j.val]!

@[noinline] def runFull (blocked : Bool) (f : Fixture) : Array UInt32 :=
  match prepare f.n (fun i => f.x[i]!) with
  | none => #[]
  | some x => Array.ofFn (n := f.outputs) fun j =>
    match prepare f.n (fun i => f.w[j.val * f.n + i]!) with
    | none => 0
    | some w => output blocked f.n x w f.bias[j.val]!

def parseWords (s : String) : Except String (Array UInt32) := do
  (s.splitOn ",").toArray.mapM fun part =>
    match part.toNat? with
    | some n => if n < 4294967296 then pure (UInt32.ofNat n) else throw "word overflow"
    | none => throw "not an unsigned integer"

def parseFixture (text : String) : Except String Fixture := do
  let lines := (text.splitOn "\n").toArray
  if lines.size < 6 then throw "fixture needs six lines"
  let some n := lines[0]!.toNat? | throw "invalid n"
  let some outputs := lines[1]!.toNat? | throw "invalid output count"
  let x ← parseWords lines[2]!
  let w ← parseWords lines[3]!
  let bias ← parseWords lines[4]!
  let expected ← parseWords lines[5]!
  if x.size != n || w.size != n * outputs || bias.size != outputs || expected.size != outputs then
    throw "shape mismatch"
  pure ⟨n, outputs, x, w, bias, expected⟩

def check (got expected : Array UInt32) : IO Unit := do
  if got.size != expected.size then throw (IO.userError "output size mismatch")
  for i in [:expected.size] do
    if got[i]! != expected[i]! then
      throw (IO.userError s!"word mismatch at {i}: {got[i]!.toNat} vs {expected[i]!.toNat}")

@[noinline] def checksum (out : Array UInt32) : UInt32 := out.foldl (fun acc w => acc + w) 0

def measure (name : String) (run : Unit → Array UInt32) (expected : Array UInt32)
    (trial : Nat) (repeats : Nat) : IO Unit := do
  let mut ns := 0
  let mut sink : UInt32 := 0
  for _ in [:repeats] do
    let start ← IO.monoNanosNow
    let out ← IO.lazyPure run
    let stop ← IO.monoNanosNow
    ns := ns + (stop - start)
    check out expected
    sink := sink + checksum out
  IO.println s!"R26_WORD_SAMPLE\t{name}\t{trial}\t{repeats}\t{ns}\t{sink.toNat}"

def main (args : List String) : IO Unit := do
  let path := args.headD "word-fixture-normal.txt"
  let text ← IO.FS.readFile (System.FilePath.mk path)
  let f ← match parseFixture text with
    | .ok value => pure value
    | .error err => throw (IO.userError err)
  let x ← match prepare f.n (fun i => f.x[i]!) with
    | some value => pure value
    | none => throw (IO.userError "input preparation rejected")
  let mut w : Array Prepared := #[]
  for j in [:f.outputs] do
    match prepare f.n (fun i => f.w[j * f.n + i]!) with
    | none => throw (IO.userError s!"weight row {j} rejected")
    | some row =>
      if !canBlock16 f.n x.maximum row.maximum then throw (IO.userError "block guard rejected")
      if idxOf f.bias[j]! + 149 < x.base + row.base then throw (IO.userError "negative bias shift")
      w := w.push row
  let ap := fun _ : Unit => runPrepared false f x w
  let bp := fun _ : Unit => runPrepared true f x w
  let af := fun _ : Unit => runFull false f
  let bf := fun _ : Unit => runFull true f
  for run in [ap, bp, af, bf] do
    check (← IO.lazyPure run) f.expected
  IO.println s!"R26_WORD_VERIFY\t{f.n}\t{f.outputs}\t4\ttrue"
  for trial in [:11] do
    if trial % 2 == 0 then
      measure "each_prepared" ap f.expected trial 3
      measure "block16_prepared" bp f.expected trial 3
      measure "each_full" af f.expected trial 3
      measure "block16_full" bf f.expected trial 3
    else
      measure "block16_prepared" bp f.expected trial 3
      measure "each_prepared" ap f.expected trial 3
      measure "block16_full" bf f.expected trial 3
      measure "each_full" af f.expected trial 3

end R26WordCost

def main (args : List String) : IO Unit := R26WordCost.main args
