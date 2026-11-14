/- Self-authored native-only paired-product experiment. This is not a proven
submission. Requires the original predecessor27 runtime and R27PackedLinear's
complete bias/zero/terminal helper. -/
namespace R27Winograd
open ExactRuntime

@[inline] def addSigned {α : Type} (hi lo p : UInt64) (negative : Bool)
    (next : UInt64 → UInt64 → α) : α :=
  if negative then next (hi - (if lo < p then 1 else 0)) (lo - p)
  else let ll := lo + p; next (hi + (if ll < lo then 1 else 0)) ll

@[inline] def subtract {α : Type} (hi lo rh rl : UInt64)
    (next : UInt64 → UInt64 → α) : α :=
  next (hi-rh-(if lo < rl then 1 else 0)) (lo-rl)

@[inline] def decode (c : Nat) : UInt64 :=
  let word := c.toUInt64
  let magnitude := word &&& 0xFFFFFFFF
  if word >>> 32 == 0 then magnitude else 0-magnitude

@[inline] def magnitude (v : UInt64) : UInt64 :=
  if v >>> 63 == 0 then v else 0-v

@[specialize] def selfSum {α : Type} (next : UInt64 → UInt64 → α) (a : Array Nat) :
    Nat → Nat → UInt64 → UInt64 → α
  | 0, _, hi, lo => next hi lo
  | left+1, i, hi, lo =>
      let x := a[i]!.toUInt64
      let y := a[i+1]!.toUInt64
      let p := (x &&& 0xFFFFFFFF) * (y &&& 0xFFFFFFFF)
      addSigned hi lo p (((x ^^^ y) >>> 32) != 0)
        (fun h l => selfSum next a left (i+2) h l)

structure Cached where
  low : Nat
  peak : UInt64
  data : Array Nat
  selfHi : UInt64
  selfLo : UInt64
  valid : Bool

def invalid (low : Nat) : Cached := ⟨low,0,#[],0,0,false⟩
local instance : Inhabited Cached := ⟨invalid 0⟩

def prepare (a : Array Word) (base n : Nat) (metadata : UInt32) : Cached := Id.run do
  let low := (Submission.Yk (metadata >>> 16)).toNat
  let high := (Submission.Yk (metadata &&& 0xFFFF)).toNat
  if 8 < high-low then return invalid low
  let mut peak : UInt64 := 0
  let mut data : Array Nat := Array.mkEmpty n
  for i in [0:n] do
    let w := a[base+i]!
    let m := mantOf w
    let e := idxOf w
    if m == 0 then data := data.push 0
    else
      if e < low || 8 < e-low then return invalid low
      let value := m.toUInt64 <<< (e-low).toUInt64
      peak := max peak value
      data := data.push (value + (if signOf w then 0x100000000 else 0)).toNat
  return selfSum (fun h l => ⟨low,peak,data,h,l,true⟩) data (n/2) 0 0 0

@[specialize] def cross {α : Type} (next : UInt64 → UInt64 → α) (a b : Array Nat) :
    Nat → Nat → UInt64 → UInt64 → α
  | 0, _, hi, lo => next hi lo
  | left+1, i, hi, lo =>
      let x := decode a[i]! + decode b[i+1]!
      let y := decode a[i+1]! + decode b[i]!
      let p := magnitude x * magnitude y
      addSigned hi lo p (((x ^^^ y) >>> 63) != 0)
        (fun h l => cross next a b left (i+2) h l)

@[inline] def signed128 (hi lo : UInt64) : Int :=
  let z : Int := Int.ofNat ((hi.toNat <<< 64)+lo.toNat)
  if hi >>> 63 == 0 then z else z-340282366920938463463374607431768211456

def total (a b : Cached) (n : Nat) : Int :=
  cross (fun h l => subtract h l a.selfHi a.selfLo fun h l =>
    subtract h l b.selfHi b.selfLo fun h l =>
      if n % 2 == 0 then signed128 h l
      else
        let x := a.data[n-1]!.toUInt64
        let y := b.data[n-1]!.toUInt64
        addSigned h l ((x &&& 0xFFFFFFFF)*(y &&& 0xFFFFFFFF))
          (((x ^^^ y) >>> 32) != 0) signed128)
    a.data b.data (n/2) 0 0 0

def linear (rows n outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if rows == 0 || outW == 0 then #[]
  else if n == 0 || 1073741824 ≤ n ||
    !(X.size == rows*n && W.size == outW*n && b.size == outW &&
      X.all finiteWord && W.all finiteWord && b.all finiteWord) then
    Submission.retainedKernels.dense.linear rows n outW relu X W b
  else
    let BX := Array.ofFn (n := rows) (fun r => Submission.Yc X n r.val)
    let BW := Array.ofFn (n := outW) (fun j => Submission.Yc W n j.val)
    let A := Array.ofFn (n := rows) (fun r => prepare X (r.val*n) n BX[r.val]!)
    let B := Array.ofFn (n := outW) (fun j => prepare W (j.val*n) n BW[j.val]!)
    Array.ofFn (n := rows*outW) fun q =>
      let row := q.val/outW
      let col := q.val%outW
      let a := A[row]!
      let w := B[col]!
      if a.valid && w.valid && a.peak+w.peak < 0x100000000 then
        act relu (R27PackedLinear.finish X W b row n col (a.low+w.low) (total a w n))
      else act relu (Submission.YaU X W b n row col BX[row]! BW[col]!)

end R27Winograd
