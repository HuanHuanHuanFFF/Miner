/- Small fusion prototype and explicit contracts. NOT_RUN.
   prepare_spec is intentionally not claimed: the actual loop/map and Bool
   invariant must still be proved, and the new loop's full cost must be measured. -/
namespace Submission.R22FusedPreparedB
open FloatLib.Floats Competition

@[inline] def rawSafe (q : Binary32) : Bool := R7W12.rawNotNaN q.raw.1

structure Prepared where
  values : Array Float32
  allNonNaN : Bool

def prepareLoop (raw : Array Binary32) (i : Nat)
    (values : Array Float32) (good : Bool) : Prepared :=
  if hi : i < raw.size then
    let q := raw[i]
    let f := ExecFloat.Binary.toFloat32 q
    prepareLoop raw (i+1) (values.push f) (good && rawSafe q)
  else ⟨values,good⟩
termination_by raw.size-i

def prepare (raw : Array Binary32) : Prepared :=
  prepareLoop raw 0 (Array.mkEmpty raw.size) true

def Ready (raw : Array Binary32) (p : Prepared) : Prop :=
  p.values = raw.map ExecFloat.Binary.toFloat32 ∧ p.allNonNaN = raw.all rawSafe

theorem getD_of_ready (raw : Array Binary32) (p : Prepared)
    (hready : Ready raw p) (i : Nat) :
    p.values.getD i Packed10.zero32 = ExecFloat.Binary.toFloat32 (raw.getD i posZero) := by
  rw [hready.1]
  exact Packed10.nativeA_getD raw i

theorem safe_getD_of_ready (raw : Array Binary32) (p : Prepared)
    (hready : Ready raw p) (hsafe : p.allNonNaN = true) (i : Nat) :
    rawSafe (raw.getD i posZero) = true := by
  have hall : raw.all rawSafe = true := hready.2.symm.trans hsafe
  by_cases hi : i < raw.size
  · simpa [Array.getD,hi] using (Array.all_eq_true.mp hall) i hi
  · have hz : rawSafe posZero = true := by decide
    simp [Array.getD,hi,hz]

theorem native_getD_not_nan (raw : Array Binary32) (p : Prepared)
    (hready : Ready raw p) (hsafe : p.allNonNaN = true) (i : Nat) :
    (ExecFloat.Binary.toFloat32 (raw.getD i posZero)).isNaN = false := by
  have h := safe_getD_of_ready raw p hready hsafe i
  rw [rawSafe,R7W12.rawNotNaN_eq_native_classifier] at h
  simpa using h

theorem stored_value_import_eq_raw (raw : Array Binary32) (p : Prepared)
    (hready : Ready raw p) (hsafe : p.allNonNaN = true) (i : Nat) :
    ExecFloat.Binary.ofFloat32 (p.values.getD i Packed10.zero32) = raw.getD i posZero := by
  rw [getD_of_ready raw p hready i]
  exact NotNaNProbe.roundtrip _ (native_getD_not_nan raw p hready hsafe i)

end Submission.R22FusedPreparedB
