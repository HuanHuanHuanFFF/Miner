namespace Submission.R26ProducerCheckerJoin
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Submission.R24PortableF64
open Submission.R26ProducerEnclosure
open Submission.R25OrderKey
open Submission.R25Checker

abbrev preparedSum (x y : Array UInt32) : Float :=
  sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size

abbrev preparedRadius (x y : Array UInt32) : Float :=
  Float.ofBits ((actualH x y + (actualL x + actualL x) + 720) <<< 52)

/-- This uses strict monotone pullback through RNE64. No assertion that the
two rounded native endpoints themselves enclose the target is needed. -/
theorem actual_acceptance_contains_rawSum (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) (q : UInt32)
    (hacc : R24PortableF64.certify (preparedSum x y) (preparedRadius x y)
      (preparedSum x y).toBits q = true) :
    value (lowerWord q) < exactRawSum x y ∧ exactRawSum x y < value (upperWord q) := by
  have hacc' : R25Checker.certify (preparedSum x y) (preparedRadius x y)
      (preparedSum x y).toBits q = true := by
    simpa only [certify_eq_runtime] using hacc
  obtain ⟨he0, he255, _⟩ := accepted_components _ _ _ q hacc'
  have hm := midpoint_finite_nonzero q he0 he255
  have hlfinite : Model.isFinite (raw (lowerWord q)) = true := finite64_model _ hm.1
  have hufinite : Model.isFinite (raw (upperWord q)) = true := finite64_model _ hm.2.1
  have hb := actual_acceptance_bounds _ _ _ q hacc
  have herr := (actual_tail_enclosure x y hx hy hsize).2
  have hend := actual_endpoints_finite_real x y hx hy hsize
  have hlo : nativeValue (preparedSum x y - preparedRadius x y) =
      Model.roundAt FloatFormat.binary64
        (nativeValue (preparedSum x y) - R24RadiusEndpoints.p2
          ((actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303)) := hend.2.2.1
  have hup : nativeValue (preparedSum x y + preparedRadius x y) =
      Model.roundAt FloatFormat.binary64
        (nativeValue (preparedSum x y) + R24RadiusEndpoints.p2
          ((actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303)) := hend.2.2.2
  rw [hlo, hup] at hb
  exact R24StrictEnclosure.strict_enclosure_of_rounded_bounds
    (nativeValue (preparedSum x y)) (exactRawSum x y)
    (R24RadiusEndpoints.p2 ((actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303))
    (raw (lowerWord q)) (raw (upperWord q)) hlfinite hufinite herr hb.1 hb.2

theorem attemptPrepared_contains_rawSum (x y : Array UInt32)
    (hnz : attemptPrepared (prepare x) (prepare y) ≠ 0) :
    value (lowerWord (attemptPrepared (prepare x) (prepare y))) < exactRawSum x y ∧
      exactRawSum x y < value (upperWord (attemptPrepared (prepare x) (prepare y))) := by
  have hg := R26AttemptGuards.attemptPrepared_guards (prepare x) (prepare y) hnz
  have hc := R26AttemptGuards.attemptPrepared_acceptance (prepare x) (prepare y) hnz
  have hs : x.size = y.size := by
    simpa only [R25PrepareAgreement.prepare_raw] using hg.2.1
  apply actual_acceptance_contains_rawSum x y hg.2.2.2.1 hg.2.2.2.2 hs
    (attemptPrepared (prepare x) (prepare y))
  simpa only [preparedSum, preparedRadius, R26AttemptGuards.cachedSum,
    R26AttemptGuards.cachedRadius, actualH, actualL, R25PrepareAgreement.prepare_raw] using hc

end Submission.R26ProducerCheckerJoin
