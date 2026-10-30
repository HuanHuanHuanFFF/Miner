import ContractExact

/- Original minimal rebase interface using the actual pinned finisher theorem.
   UNCOMPILED. Does not establish the transform producer or new kernel equality. -/
namespace R28SpatialRebase
open ExactRuntime

theorem finish_four (S e : Int) (negZero : Bool) :
    finishWord (4*S) (e-2) negZero=finishWord S e negZero := by
  have h:=finishWord_scale S (e-2) 2 negZero
  simpa [mul_comm] using h.symm

theorem finish_four_with_bias (S B e : Int) (negZero : Bool) :
    finishWord (4*S+4*B) (e-2) negZero=finishWord (S+B) e negZero := by
  rw [←mul_add]
  exact finish_four (S+B) e negZero

theorem zero_condition (S B : Int) : 4*S+4*B=0 ↔ S+B=0 := by omega

theorem lowered_index (B0 : Nat) (h : 2≤B0) :
    ((B0-2:Nat):Int)-298=((B0:Int)-298)-2 := by omega

theorem bias_shift (B0 biasIndex : Nat) (h : 2≤B0)
    (low : B0≤126+biasIndex) (high : 126+biasIndex-B0≤76) :
    126+biasIndex-(B0-2)=(126+biasIndex-B0)+2 ∧
    126+biasIndex-(B0-2)≤78 := by omega

theorem nonzero_bias_integer (M : Int) (B0 biasIndex : Nat)
    (h : 2≤B0) (low : B0≤126+biasIndex) :
    M*2^(126+biasIndex-(B0-2))=4*(M*2^(126+biasIndex-B0)) := by
  have he:126+biasIndex-(B0-2)=(126+biasIndex-B0)+2 := by omega
  rw [he,pow_add]
  norm_num
  ring

/-- A zero body at any new bias context has the same zero-sign decision only if
the raw flag is retained. The integer representation itself cannot reconstruct it. -/
theorem keep_raw_zero_flag (e : Int) (rawFlag : Bool) :
    finishWord 0 (e-2) rawFlag=finishWord 0 e rawFlag := by simp [finishWord]

end R28SpatialRebase
