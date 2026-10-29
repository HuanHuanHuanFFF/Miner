/- Portable original-ContractTensor traversal component. No new kernel record.
   `readings` is proof material; the executable fold reads each term directly.
   Finite/value bounds remain explicit premises, not assumed rounding errors. -/
namespace Submission.R24ReadFold

open Submission.R24RepresentationSum

@[specialize] def foldRead (reader : Nat → Float) : Nat → Nat → Float → Float
  | 0, _, acc => acc
  | n + 1, offset, acc => foldRead reader n (offset + 1) (acc + reader offset)

def run (reader : Nat → Float) (count offset : Nat) : Float :=
  foldRead reader count offset (Float.ofBits 0)

def readings (reader : Nat → Float) : Nat → Nat → List Float
  | 0, _ => []
  | n + 1, offset => reader offset :: readings reader n (offset + 1)

theorem readings_length (reader : Nat → Float) (count offset : Nat) :
    (readings reader count offset).length = count := by
  induction count generalizing offset with
  | zero => rfl
  | succ count ih => simp only [readings, List.length_cons, ih]

theorem foldRead_eq_loop (reader : Nat → Float) (count offset : Nat) (acc : Float) :
    foldRead reader count offset acc =
      loop (readings reader count offset) acc := by
  induction count generalizing offset acc with
  | zero => rfl
  | succ count ih =>
      simp only [foldRead, readings, loop]
      exact ih (offset + 1) (acc + reader offset)

theorem run_eq_sum (reader : Nat → Float) (count offset : Nat) :
    run reader count offset = sum (readings reader count offset) :=
  foldRead_eq_loop reader count offset (Float.ofBits 0)

theorem actual_read_enclosure (reader : Nat → Float) (count offset L : Nat) (k : Int)
    (hk0 : -250 ≤ k) (hk1 : k ≤ 256) (hL : L ≤ 30) (hn : count ≤ 2 ^ L)
    (hx : ∀ x ∈ readings reader count offset,
      x.isFinite = true ∧ |rval x| < p2 k) :
    (run reader count offset).isFinite = true ∧
      |rval (run reader count offset) - exactSum (readings reader count offset)| ≤
        p2 (k + 2 * (L : Int) - 53) := by
  have hlen : (readings reader count offset).length ≤ 2 ^ L := by
    simpa only [readings_length] using hn
  have h := sum_enclosure (readings reader count offset) L k hk0 hk1 hL hlen hx
  rw [← run_eq_sum reader count offset] at h
  exact h

@[inline] def arrayProduct (a b : Array Float) (i : Nat) : Float :=
  a.getD i (Float.ofBits 0) * b.getD i (Float.ofBits 0)

def dotArrays (a b : Array Float) (count : Nat) : Float :=
  run (arrayProduct a b) count 0

theorem dotArrays_eq_fold (a b : Array Float) (count : Nat) :
    dotArrays a b count = sum (readings (arrayProduct a b) count 0) :=
  run_eq_sum (arrayProduct a b) count 0

end Submission.R24ReadFold
