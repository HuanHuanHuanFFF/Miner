/- Original small additions for the supplied R27Winograd namespace.
NOT_COMPILED. This is a cost-probe patch, NOT a Correct submission.
Requires the frozen Cached/decode/cross and native-finish definitions.
The guards and exact-array invariants described in REVIEW.md are obligations.
SCOPE CORRECTION: these are archived research additions for the legacy isolated
fragments, not a patch applied to frozen candidate600eaaa1. Its builders already
wire totalWords->finishWords and v2 already has all-input-invalid whole fallback.
No wiring novelty or performance gain is claimed here; no queued variant changes.
-/

/-- Only select this loop when the actual two cached peaks sum to at most
3037000499. Under the wider <2^32 guard, it is UNSOUND; keep cross there. -/
@[specialize] def crossSigned63 {α : Type} (next : UInt64 → UInt64 → α)
    (a b : Array Nat) : Nat → Nat → UInt64 → UInt64 → α
  | 0, _, hi, lo => next hi lo
  | left+1, i, hi, lo =>
      let x := decode a[i]! + decode b[i+1]!
      let y := decode a[i+1]! + decode b[i]!
      let p := x*y
      let ll := lo+p
      let hh := hi+(0-(p >>> 63))+(if ll<lo then 1 else 0)
      crossSigned63 next a b left (i+2) hh ll

@[inline] def crossSelected {α : Type} (signed63 : Bool)
    (next : UInt64 → UInt64 → α) (a b : Array Nat)
    (left i : Nat) (hi lo : UInt64) : α :=
  if signed63 then crossSigned63 next a b left i hi lo
  else cross next a b left i hi lo

/-- Call only for a PROVED exact-zero sentinel of the complete biased sum.
Do not call for a zero cross subtotal or a rounded underflow-to-zero. -/
@[inline] def finishExactZero (relu : Bool) (replay : Unit → Word) : Word :=
  if relu then 0 else replay ()

/-- The signed128 invariant makes hi=lo=0 equivalent to an exact zero body.
The caller has already checked finite bias and still applies outer `act`.
The continuation preserves the old zero-sign replay when necessary. -/
@[inline] def finishZeroBodyOr (relu : Bool) (bw : Word) (hi lo : UInt64)
    (next : Unit → Word) : Word :=
  if (hi ||| lo) == 0 then
    if mantOf bw != 0 then bw else if relu then 0 else next ()
  else next ()

/- Exact edits to the supplied frozen fragments:

1. In totalWords, replace its initial
     cross (fun h l => ...)
   with
     crossSelected (decide (a.peak+b.peak ≤ 3037000499)) (fun h l => ...)
   Keep all corrections and the odd tail unchanged.

2. Add (relu : Bool) to finishWords's arguments. Replace BOTH zero-sentinel
   replay branches (not its wide-alignment fallback) by
     finishExactZero relu (fun _ => R27PackedLinear.exactZero X W b row n col)

   Immediately after `let bw := b[col]!`, wrap the remaining body in
     finishZeroBodyOr relu bw hi lo (fun _ => ...)
   The exact body is zero by the signed128 bound; a nonzero finite bias is
   already representable. This avoids the all-zero low=510 wide fallback.
   The outer `act relu` remains. For zero bias without ReLU, retain replay.

3. LEGACY FRAGMENT ASSEMBLY ONLY. Candidate600e already has this connection;
   this is not a new fix or effect, and must not be applied to it as a delta.
   For reproducing only the old isolated fragment, replace the expression
     act relu (R27PackedLinear.finish ... (total a w n))
   by
     act relu (totalWords
       (fun hi lo => finishWords relu X W b row n col (a.low+w.low) hi lo)
       a w n)
   This distinction concerned the old isolated Runtime, not the built600e.

4. Before any new preparation, bypass shapes with
     n < 2 || rows < 2 || outW < 2 || rows*outW ≤ rows+outW
   to the retained whole linear. These cannot reduce multiplication counts
   even at full admission. This is a cost guard, not a correctness premise.

In600e v2, all input caches invalid already returns the whole predecessor before
weight preparation. The remaining per-output YaU path, including mixed validity,
can lose packed/sparse/block scheduling. Its complete cost remains unmeasured.
The signed63/zero shortcuts here remain NOT_COMPILED research drafts, not600e.
-/
