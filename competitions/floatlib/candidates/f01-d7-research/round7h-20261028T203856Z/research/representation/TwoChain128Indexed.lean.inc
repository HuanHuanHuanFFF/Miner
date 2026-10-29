/- Actual indexed getter bridge. The runtime path does not construct a List
   of terms: that sequence appears only on the specification side. Nat
   indices avoid a hidden USize increment-wrap premise. No caller/ABI cost
   or original terminal semantics is assumed by the equality theorem. -/
namespace Submission.R24TwoChain128Indexed
open FloatLib.Numerics.FixedWord
open Submission.R24TwoChain128

def readSequence {α : Type} (get : Nat → α) (start count : Nat) : List α :=
  (List.range' start count).map get

@[specialize] def indexedLoop (get : Nat → UInt64) :
    Nat → Nat → UInt64 → UInt64 → UInt64 → UInt64 → UInt128
  | 0, _, alo, ahi, blo, bhi => merge ahi alo bhi blo
  | remaining + 1, i, alo, ahi, blo, bhi =>
    let q := get i
    let lo := alo + q
    let carry : UInt64 := if lo < alo then 1 else 0
    let hi := ahi + high q + carry
    indexedLoop get remaining (i + 1) blo bhi lo hi

@[inline] def runIndexed (n : Nat) (get : Nat → UInt64) : UInt128 :=
  indexedLoop get n 0 0 0 0 0

theorem indexedLoop_eq_loop (get : Nat → UInt64) (count start : Nat)
    (alo ahi blo bhi : UInt64) :
    indexedLoop get count start alo ahi blo bhi =
      loop (readSequence get start count) alo ahi blo bhi := by
  induction count generalizing start alo ahi blo bhi with
  | zero => rfl
  | succ count ih =>
    simpa only [indexedLoop, readSequence, List.range'_succ, List.map_cons, loop] using
      ih (start + 1) blo bhi (alo + get start)
        (ahi + high (get start) + (if alo + get start < alo then (1 : UInt64) else 0))

/- Word identity needs no term-magnitude or no-overflow assumption. It
   compares two concrete loops with the same reads and actual final merge. -/
theorem runIndexed_eq_run2 (n : Nat) (get : Nat → UInt64) :
    runIndexed n get = run2 (readSequence get 0 n) := by
  simpa only [runIndexed, run2] using indexedLoop_eq_loop get n 0 0 0 0 0

theorem terminal_transport {β : Type} (finish : UInt128 → β)
    (n : Nat) (get : Nat → UInt64) :
    finish (runIndexed n get) = finish (run2 (readSequence get 0 n)) :=
  congrArg finish (runIndexed_eq_run2 n get)

theorem terminal_fields_transport {β : Type} (finish : UInt64 → UInt64 → β)
    (n : Nat) (get : Nat → UInt64) :
    finish (runIndexed n get).hi (runIndexed n get).lo =
      finish (run2 (readSequence get 0 n)).hi (run2 (readSequence get 0 n)).lo :=
  congrArg (fun v : UInt128 => finish v.hi v.lo) (runIndexed_eq_run2 n get)

open Submission.R24TwoChain128Encoder

@[inline] def runEncodedIndexed (n : Nat) (get : Nat → Term) : UInt128 :=
  runIndexed n (fun i => encode (get i))

/- Actual per-index Boolean checks derive term exactness and signed62 bounds
   through the existing encoder. The getter's sum is not a new hypothesis. -/
theorem runEncodedIndexed_exact (n : Nat) (get : Nat → Term) (hn : n < 2 ^ 20)
    (hg : ∀ i, i < n → guard (get i) = true) :
    signed128 (runEncodedIndexed n get) =
      ((List.range' 0 n).map (fun i => integerTerm (get i))).sum := by
  have hs : ∀ t ∈ readSequence get 0 n, guard t = true := by
    intro t ht
    obtain ⟨i, hi, rfl⟩ := List.mem_map.mp ht
    obtain ⟨j, hj, hij⟩ := List.mem_range'.mp hi
    have he : i = j := by simpa using hij
    exact hg i (by omega)
  have h := runEncoded_exact (readSequence get 0 n) (by
    simpa only [readSequence, List.length_map, List.length_range'] using hn) hs
  rw [runEncodedIndexed, runIndexed_eq_run2]
  simpa only [runEncoded, readSequence, List.map_map, Function.comp_def] using h

end Submission.R24TwoChain128Indexed
