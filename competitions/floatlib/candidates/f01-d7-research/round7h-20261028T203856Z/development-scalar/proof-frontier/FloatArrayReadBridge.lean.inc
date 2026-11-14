/- Proof-only bridge draft. NOT_COMPILED; no runtime replacement or CI.
   Requires Root's selected R24PortableF64.sumRemaining from exact98784d4e
   plus the existing R24ReadFold/R24RepresentationSum proof component.
   Does NOT apply to original dd775 while source, which lacks sumRemaining. -/
namespace Submission.R24FloatArrayReadBridge

/-- Instantiate the reader with native FloatArray getters only in an erased proof. -/
theorem actual_worker_eq_readFold (a b : FloatArray) (index : Nat)
    (acc : Float) (remaining : Nat) :
    R24PortableF64.sumRemaining a b index acc remaining =
      R24ReadFold.foldRead (fun i => a.get! i * b.get! i) remaining index acc := by
  induction remaining generalizing index acc with
  | zero => rfl
  | succ remaining ih =>
    simpa only [R24PortableF64.sumRemaining, R24ReadFold.foldRead] using
      ih (index + 1) (acc + a.get! index * b.get! index)

/-- The product finite/bound premise stays explicit until the raw widening/MUL
    bridge proves it for canonical caches. No FloatArray.data is executed. -/
theorem actual_worker_enclosure (a b : FloatArray) (count L : Nat) (k : Int)
    (hk0 : -250 ≤ k) (hk1 : k ≤ 256) (hL : L ≤ 30) (hn : count ≤ 2 ^ L)
    (hx : ∀ x ∈ R24ReadFold.readings (fun i => a.get! i * b.get! i) count 0,
      x.isFinite = true ∧ |R24RepresentationSum.rval x| < R24RepresentationSum.p2 k) :
    (R24PortableF64.sumRemaining a b 0 (Float.ofBits 0) count).isFinite = true ∧
      |R24RepresentationSum.rval
          (R24PortableF64.sumRemaining a b 0 (Float.ofBits 0) count) -
        R24RepresentationSum.exactSum
          (R24ReadFold.readings (fun i => a.get! i * b.get! i) count 0)| ≤
        R24RepresentationSum.p2 (k + 2 * (L : Int) - 53) := by
  have h := R24ReadFold.actual_read_enclosure
    (fun i => a.get! i * b.get! i) count 0 L k hk0 hk1 hL hn hx
  have hr : R24ReadFold.run (fun i => a.get! i * b.get! i) count 0 =
      R24PortableF64.sumRemaining a b 0 (Float.ofBits 0) count := by
    unfold R24ReadFold.run
    exact (actual_worker_eq_readFold a b 0 (Float.ofBits 0) count).symm
  rw [hr] at h
  exact h

end Submission.R24FloatArrayReadBridge
