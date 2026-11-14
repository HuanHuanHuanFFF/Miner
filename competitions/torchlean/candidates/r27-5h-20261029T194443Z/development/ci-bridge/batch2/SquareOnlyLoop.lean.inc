/- Own R27 RMS refinement. RMS consumes only the sum of squares from the
   six-word moment accumulator; this loop omits both signed first moments. -/
def r27SquareLoop (x : Array Word) (base n exponent index : Nat)
    (sumHigh sumLow : UInt64) (valid : Bool) : Bool × Nat :=
  if index < n then
    let word := x[base + index]!
    let mantissa := (mantOf word).toUInt64
    let shift := 2 * (idxOf word - exponent).toUInt64
    let square := mantissa * mantissa
    let lowTerm := if shift < 64 then square <<< shift else 0
    let highTerm := if shift < 64 then (square >>> 1) >>> (63 - shift)
      else square <<< (shift - 64)
    let low := sumLow + lowTerm
    let high := sumHigh + (if low < sumLow then 1 else 0) + highTerm
    let nextValid := valid && (mantOf word = 0 || idxOf word - exponent ≤ 36)
    r27SquareLoop x base n exponent (index + 1) high low nextValid
  else (valid && n < 256, sumHigh.toNat <<< 64 + sumLow.toNat)
termination_by n - index

theorem r27SquareLoop_projection (x : Array Word) (base n exponent count : Nat) :
    ∀ index ph pl nh nl qh ql valid, n - index = count →
      r27SquareLoop x base n exponent index qh ql valid =
        let original := rsU x base n exponent index ph pl nh nl qh ql valid
        (original.1, original.2.2.2) := by
  induction count with
  | zero =>
    intro index ph pl nh nl qh ql valid remaining
    rw [r27SquareLoop, rsU, if_neg (by omega), if_neg (by omega)]
    rfl
  | succ count ih =>
    intro index ph pl nh nl qh ql valid remaining
    rw [r27SquareLoop, rsU, if_pos (by omega), if_pos (by omega)]
    dsimp only
    by_cases negative : signOf x[base + index]! = true
    · rw [if_pos negative]
      simpa only [u2a] using
        ih (index + 1) ph pl
          (u2a nh nl ((mantOf x[base + index]!).toUInt64 <<<
            (idxOf x[base + index]! - exponent).toUInt64)).1
          (u2a nh nl ((mantOf x[base + index]!).toUInt64 <<<
            (idxOf x[base + index]! - exponent).toUInt64)).2
          _ _ _ (by omega)
    · rw [if_neg negative]
      simpa only [u2a] using
        ih (index + 1)
          (u2a ph pl ((mantOf x[base + index]!).toUInt64 <<<
            (idxOf x[base + index]! - exponent).toUInt64)).1
          (u2a ph pl ((mantOf x[base + index]!).toUInt64 <<<
            (idxOf x[base + index]! - exponent).toUInt64)).2
          nh nl _ _ _ (by omega)

theorem r27SquareLoop_eq (x : Array Word) (base n exponent : Nat) :
    r27SquareLoop x base n exponent 0 0 0 true =
      let original := rsU x base n exponent 0 0 0 0 0 0 0 true
      (original.1, original.2.2.2) :=
  r27SquareLoop_projection x base n exponent n 0 0 0 0 0 0 0 true (by omega)
