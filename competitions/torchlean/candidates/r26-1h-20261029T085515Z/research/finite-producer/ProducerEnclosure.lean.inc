namespace Submission.R26ProducerEnclosure
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open Submission.R24PortableF64
open Submission.R25PrepareAgreement
open Submission.R26PreparePeak
open Submission.R26PreparedParameters
open Submission.R26ProducerNumerics
open Submission.R26TailAgreement

abbrev actualH (x y : Array UInt32) : UInt64 :=
  (prepare x).maxIndex.toUInt64 + (prepare y).maxIndex.toUInt64

abbrev actualL (x : Array UInt32) : UInt64 := ceilLog2 (prepare x).raw.size

noncomputable def exactRawSum (x y : Array UInt32) : Real :=
  ((List.range' 0 x.size).map (fun i => rawValue x[i]! * rawValue y[i]!)).sum

theorem prepared_product_bounded (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (i : Nat) (hix : i < x.size) (hiy : i < y.size) :
    ((prepare x).values.get! i * (prepare y).values.get! i).isFinite = true ∧
      |Submission.R24RepresentationSum.rval
        ((prepare x).values.get! i * (prepare y).values.get! i)| <
      Submission.R24RepresentationSum.p2 ((actualH x y).toNat - (250 : Int)) := by
  have hp := prepared_product_exact x y hx hy i hix hiy
  have hmx := prepared_raw_magnitude x hx i hix
  have hmy := prepared_raw_magnitude y hy i hiy
  refine ⟨hp.1, ?_⟩
  change |Submission.R24NativeMul.value
    ((prepare x).values.get! i * (prepare y).values.get! i)| < _
  rw [hp.2, abs_mul]
  calc
    _ ≤ |rawValue x[i]| * p2 ((prepare y).maxIndex.toNat - (125 : Int)) :=
      mul_le_mul_of_nonneg_left hmy.le (abs_nonneg _)
    _ < p2 ((prepare x).maxIndex.toNat - (125 : Int)) *
        p2 ((prepare y).maxIndex.toNat - (125 : Int)) :=
      mul_lt_mul_of_pos_right hmx (Model.bpow_pos _)
    _ = Submission.R24RepresentationSum.p2 ((actualH x y).toNat - (250 : Int)) := by
      change Model.bpow _ * Model.bpow _ = Model.bpow _
      rw [← Model.bpow_add, prepared_H_nat]
      congr 1
      push_cast
      ring

theorem actualTerms_spec (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    ∀ term ∈ actualTerms (prepare x).values (prepare y).values 0 x.size,
      term.isFinite = true ∧
      |Submission.R24RepresentationSum.rval term| <
        Submission.R24RepresentationSum.p2 ((actualH x y).toNat - (250 : Int)) := by
  intro term hm
  obtain ⟨i, hi, rfl⟩ := List.mem_map.mp hm
  have hix : i < x.size := by
    have h := (List.mem_range'.mp hi).2
    omega
  have hiy : i < y.size := by omega
  exact prepared_product_bounded x y hx hy i hix hiy

theorem actualTerms_exactSum (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    Submission.R24RepresentationSum.exactSum
      (actualTerms (prepare x).values (prepare y).values 0 x.size) = exactRawSum x y := by
  unfold Submission.R24RepresentationSum.exactSum actualTerms exactRawSum
  rw [List.map_map]
  congr 1
  apply List.map_congr_left
  intro i hi
  have hix : i < x.size := by
    have h := (List.mem_range'.mp hi).2
    omega
  have hiy : i < y.size := by omega
  have hp := prepared_product_exact x y hx hy i hix hiy
  simpa only [Function.comp_apply, getElem!_pos _ i hix, getElem!_pos _ i hiy] using hp.2

theorem actual_tail_enclosure (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    let out := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
    out.isFinite = true ∧
      |Submission.R24RepresentationSum.rval out - exactRawSum x y| ≤
        Submission.R24RepresentationSum.p2
          ((actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303) := by
  have hp := actual_parameters x y hx
  have hcap := prepare_valid_sizecap x hx
  have hL : (actualL x).toNat ≤ 30 := hp.2.1
  have hH : (actualH x y).toNat ≤ 506 := hp.1
  have hc : x.size ≤ 2 ^ (actualL x).toNat := by
    simpa only [prepare_raw] using hp.2.2
  have hs := Submission.R24RepresentationSum.sum_enclosure
    (actualTerms (prepare x).values (prepare y).values 0 x.size)
    (actualL x).toNat ((actualH x y).toNat - (250 : Int))
    (by omega) (by omega) hL
    (by simpa only [actualTerms_length] using hc) (actualTerms_spec x y hx hy hsize)
  dsimp only
  rw [sumRemaining_zero_eq_sum]
  rw [actualTerms_exactSum x y hx hy hsize] at hs
  have hexp : ((actualH x y).toNat - (250 : Int)) +
      2 * ((actualL x).toNat : Int) - 53 =
      (actualH x y).toNat + 2 * ((actualL x).toNat : Int) - 303 := by ring
  simpa only [hexp] using hs

theorem actual_tail_magnitude (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    |Submission.R24RepresentationSum.rval
      (sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size)| ≤
      Submission.R24RepresentationSum.p2 286 := by
  have hp := actual_parameters x y hx
  have hc : x.size ≤ 2 ^ (actualL x).toNat := by
    simpa only [prepare_raw] using hp.2.2
  have hi := Submission.R24RepresentationSum.loop_invariant
    (actualTerms (prepare x).values (prepare y).values 0 x.size) (Float.ofBits 0) 0
    (actualL x).toNat ((actualH x y).toNat - (250 : Int))
    (by omega) (by have hh := hp.1; omega) hp.2.1
    (by simpa only [Nat.zero_add, actualTerms_length] using hc)
    Submission.R24RepresentationSum.zero_finite
    (by simp only [Submission.R24RepresentationSum.zero_value, abs_zero,
      Nat.cast_zero, zero_mul, le_refl]) (actualTerms_spec x y hx hy hsize)
  have hmag : |Submission.R24RepresentationSum.rval
      (sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size)| ≤
      (x.size : Real) * Submission.R24RepresentationSum.p2 ((actualH x y).toNat - (250 : Int)) := by
    simpa only [sumRemaining_eq_loop, actualTerms_length, Nat.zero_add] using hi.2.1
  refine hmag.trans ((Submission.R24RepresentationSum.scaled_count_le
    x.size (actualL x).toNat ((actualH x y).toNat - (250 : Int)) hc).trans ?_)
  apply Submission.R24RepresentationSum.p2_mono
  have hh := hp.1
  have hl := hp.2.1
  omega

theorem actual_radius_finite_value (x y : Array UInt32)
    (hx : (prepare x).valid = true) :
    let H := actualH x y
    let L := actualL x
    let r := Float.ofBits ((H + (L + L) + 720) <<< 52)
    r.isFinite = true ∧
      Submission.R24RadiusEndpoints.rval r =
        Submission.R24RadiusEndpoints.p2 ((H.toNat : Int) + 2 * (L.toNat : Int) - 303) ∧
      0 < Submission.R24RadiusEndpoints.rval r := by
  have hp := actual_parameters x y hx
  exact Submission.R24RadiusEndpoints.radius_finite_value (actualH x y) (actualL x) hp.1 hp.2.1

theorem actual_endpoints_finite_real (x y : Array UInt32)
    (hx : (prepare x).valid = true) (hy : (prepare y).valid = true)
    (hsize : x.size = y.size) :
    let s := sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size
    let H := actualH x y
    let L := actualL x
    let r := Float.ofBits ((H + (L + L) + 720) <<< 52)
    (s - r).isFinite = true ∧ (s + r).isFinite = true ∧
      Submission.R24RadiusEndpoints.rval (s - r) =
        Model.roundAt FloatFormat.binary64
          (Submission.R24RadiusEndpoints.rval s - Submission.R24RadiusEndpoints.p2
            ((H.toNat : Int) + 2 * (L.toNat : Int) - 303)) ∧
      Submission.R24RadiusEndpoints.rval (s + r) =
        Model.roundAt FloatFormat.binary64
          (Submission.R24RadiusEndpoints.rval s + Submission.R24RadiusEndpoints.p2
            ((H.toNat : Int) + 2 * (L.toNat : Int) - 303)) := by
  have hp := actual_parameters x y hx
  have hs := actual_tail_enclosure x y hx hy hsize
  have hm := actual_tail_magnitude x y hx hy hsize
  exact Submission.R24RadiusEndpoints.native_endpoints_finite_real
    (sumRemaining (prepare x).values (prepare y).values 0 (Float.ofBits 0) x.size)
    (actualH x y) (actualL x) hp.1 hp.2.1 hs.1 hm

end Submission.R26ProducerEnclosure
