/- Adapter from the actual prepared arrays and tail, retaining their source proofs. -/
namespace Submission.R26ProducerChecker
open Submission.R24PortableF64
open Submission.R26ProducerEnclosure
open Submission.R25OrderKey Submission.R25Checker
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange

theorem actual_prepared_acceptance_cell (x y : Array UInt32) (q : UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size)
    (hacc :
      let s := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
      let r := Float.ofBits ((actualH x y + (actualL x + actualL x) + 720) <<< 52)
      R24PortableF64.certify s r s.toBits q = true) :
    value (lowerWord q) < exactRawSum x y ∧ exactRawSum x y < value (upperWord q) := by
  let s := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
  let r := Float.ofBits ((actualH x y + (actualL x + actualL x) + 720) <<< 52)
  let R := R24RepresentationSum.p2
    ((actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303)
  have herr := actual_tail_enclosure x y hx hy hsize
  change s.isFinite = true ∧ |nativeValue s - exactRawSum x y| ≤ R at herr
  have hend := actual_endpoints_finite_real x y hx hy hsize
  change (s - r).isFinite = true ∧ (s + r).isFinite = true ∧
    nativeValue (s - r) = Model.roundAt F64 (nativeValue s - R) ∧
    nativeValue (s + r) = Model.roundAt F64 (nativeValue s + R) at hend
  have hc : R25Checker.certify s r s.toBits q = true := by
    change R24PortableF64.certify s r s.toBits q = true at hacc
    simpa only [certify_eq_runtime] using hacc
  exact R26RnePullback.accepted_contains_exact s r s.toBits q (exactRawSum x y) R
    herr.2 hend.2.2.1 hend.2.2.2 hc

end Submission.R26ProducerChecker
