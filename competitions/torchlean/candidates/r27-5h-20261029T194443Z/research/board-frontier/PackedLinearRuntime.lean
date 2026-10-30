import ContractExact

/- Self-authored R27 finite-native discriminator. No Submission.correct is
claimed. This module is NOT an admissible submission. The actual fallback,
bias, output order, terminal rounding and preparation are included. -/

namespace R27PackedLinear
open ExactRuntime FloatLib.Floats.Formats.BinaryInterchange FloatLib.Floats

def minIndex (a : Array Word) : Nat :=
  a.foldl (fun z w => if mantOf w = 0 then z else min z (idxOf w)) 254

def maxIndex (a : Array Word) : Nat :=
  a.foldl (fun z w => if mantOf w = 0 then z else max z (idxOf w)) 0

def factors (a : Array Word) (low : Nat) : Array Int :=
  a.map (fun w => sv w <<< (idxOf w - low))

def packColumn (W : Array Int) (k start count stride coordinate : Nat) : Int := Id.run do
  let mut p : Int := 0
  for j in [0:count] do
    p := (p <<< stride) + W[(start + count - 1 - j) * k + coordinate]!
  return p

def rowProduct (A P : Array Int) (row k : Nat) : Int := Id.run do
  let mut total : Int := 0
  for i in [0:k] do
    total := total + A[row * k + i]! * P[i]!
  return total

def offset (stride count : Nat) : Nat := Id.run do
  let half := 2 ^ (stride - 1)
  let mut p := 0
  for _ in [0:count] do
    p := (p <<< stride) + half
  return p

def exactZero (X W b : Array Word) (row k col : Nat) : Word :=
  dotOf (k + 1)
    (fun i => if i < k then X[row * k + i]! else oneW)
    (fun i => if i < k then W[col * k + i]! else b[col]!)

def finish (X W b : Array Word) (row k col productIndex : Nat) (total : Int) : Word :=
  let bw := b[col]!
  let biasIndex := idxOf bw + 149
  let low := min productIndex biasIndex
  let joined := (total <<< (productIndex - low)) + (sv bw <<< (biasIndex - low))
  if joined = 0 then exactZero X W b row k col
  else finishWord joined ((low : Int) - 298) false

def linear (tile rows k outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if rows = 0 || outW = 0 then #[]
  else if k = 0 || tile = 0 ||
    !(X.size == rows * k && W.size == outW * k && b.size == outW &&
      X.all finiteWord && W.all finiteWord && b.all finiteWord) then
    linearSpec rows k outW relu X W b
  else Id.run do
    let ax := minIndex X
    let aw := minIndex W
    let width := 50 + (maxIndex X - ax) + (maxIndex W - aw) + k.log2
    let half := 2 ^ (width - 1)
    let mask := 2 ^ width - 1
    let A := factors X ax
    let V := factors W aw
    let mut result : Array Word := Array.replicate (rows * outW) 0
    for block in [0:(outW + tile - 1) / tile] do
      let start := block * tile
      let count := min tile (outW - start)
      let P := Array.ofFn (n := k) (fun i => packColumn V k start count width i.val)
      let shift := offset width count
      for row in [0:rows] do
        let mut packed := (rowProduct A P row k + (shift : Int)).toNat
        for col in [0:count] do
          let total := ((packed &&& mask : Nat) : Int) - (half : Int)
          result := result.set! (row * outW + start + col)
            (act relu (finish X W b row k (start + col) (ax + aw) total))
          packed := packed >>> width
    return result

end R27PackedLinear
