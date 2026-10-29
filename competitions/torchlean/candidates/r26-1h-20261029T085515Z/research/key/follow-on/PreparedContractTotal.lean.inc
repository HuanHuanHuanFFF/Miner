/- Joins the actual producer's raw sum to the official integer total. -/
namespace Submission.R26PreparedContractTotal
open ExactRuntime
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R24PortableF64 Submission.R25PrepareAgreement
open Submission.R26ProducerEnclosure Submission.R25OrderKey

theorem exactRawSum_eq_scaled_dsum (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    exactRawSum x y = (dsum x y 0 x.size : Real) * (2 : Real) ^ (-298 : Int) := by
  have ha : 0 + x.size ≤ (x.map (Model.ofUInt32 (fmt := Fmt))).size := by simp
  have hb : 0 + x.size ≤ (y.map (Model.ofUInt32 (fmt := Fmt))).size := by simp [hsize]
  have hf : ∀ k, 0 ≤ k → k < 0 + x.size → expOf x[k]! ≠ 255 ∧ expOf y[k]! ≠ 255 := by
    intro k _ hk
    have hkx : k < x.size := by omega
    have hky : k < y.size := by omega
    constructor
    · change R24RepresentationWiden.expWord x[k]! ≠ 255
      rw [getElem!_pos x k hkx]
      exact prepare_valid_rawfinite x hx k hkx
    · change R24RepresentationWiden.expWord y[k]! ≠ 255
      rw [getElem!_pos y k hky]
      exact prepare_valid_rawfinite y hy k hky
  have h := R26ExactRawTotal.slice_eq_scaled_dsum x y 0 x.size ha hb hf
  exact h

/-- This statement uses the exact actual dsum, actual arrays, actual native tail,
actual radius and runtime checker. The zero flag is irrelevant on accepted
normal proposals because the exact total's nonzero property is derived. -/
theorem actual_prepared_accepted_finishWord (x y : Array UInt32) (q : UInt32)
    (negZero : Bool)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size)
    (hacc :
      let s := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
      let r := Float.ofBits ((actualH x y + (actualL x + actualL x) + 720) <<< 52)
      R24PortableF64.certify s r s.toBits q = true) :
    finishWord (dsum x y 0 x.size) (-298) negZero = q := by
  let s := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
  let r := Float.ofBits ((actualH x y + (actualL x + actualL x) + 720) <<< 52)
  let R := R24RepresentationSum.p2
    ((actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303)
  have herr := actual_tail_enclosure x y hx hy hsize
  change s.isFinite = true ∧ |nativeValue s - exactRawSum x y| ≤ R at herr
  rw [exactRawSum_eq_scaled_dsum x y hx hy hsize] at herr
  have hend := actual_endpoints_finite_real x y hx hy hsize
  change (s - r).isFinite = true ∧ (s + r).isFinite = true ∧
    nativeValue (s - r) = Model.roundAt F64 (nativeValue s - R) ∧
    nativeValue (s + r) = Model.roundAt F64 (nativeValue s + R) at hend
  change R24PortableF64.certify s r s.toBits q = true at hacc
  exact R26RneToContract.actual_accepted_finishWord s r s.toBits q
    (dsum x y 0 x.size) (-298) negZero R herr.2 hend.2.2.1 hend.2.2.2 hacc

/-- The accepted actual prepared fast branch returns the actual official dotSpec.
This is a source theorem awaiting the entire dependency closure's acceptance. -/
theorem actual_prepared_accepted_dotSpec (x y : Array UInt32) (q : UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size)
    (hacc :
      let s := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
      let r := Float.ofBits ((actualH x y + (actualL x + actualL x) + 720) <<< 52)
      R24PortableF64.certify s r s.toBits q = true) : dotSpec x y = q := by
  have hfinish := actual_prepared_accepted_finishWord x y q false hx hy hsize hacc
  have hT : dsum x y 0 x.size ≠ 0 := by
    intro hz
    have hq : q = 0 := by simpa [hz, finishWord] using hfinish.symm
    subst q
    let s := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
    let r := Float.ofBits ((actualH x y + (actualL x + actualL x) + 720) <<< 52)
    change R24PortableF64.certify s r s.toBits 0 = true at hacc
    have hfalse : R24PortableF64.certify s r s.toBits 0 = false := rfl
    rw [hfalse] at hacc
    cases hacc
  have hxf : ∀ i (hi : i < x.size), expOf x[i] ≠ 255 := by
    intro i hi
    exact prepare_valid_rawfinite x hx i hi
  have hyf : ∀ i (hi : i < y.size), expOf y[i] ≠ 255 := by
    intro i hi
    exact prepare_valid_rawfinite y hy i hi
  rw [R26FiniteDotFinish.dotSpec_eq_finishWord_nonzero x y false hsize hxf hyf hT]
  exact hfinish

end Submission.R26PreparedContractTotal
