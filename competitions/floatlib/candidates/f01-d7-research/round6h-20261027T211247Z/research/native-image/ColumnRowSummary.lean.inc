/- Per-batch/per-column summary sketch. NOT_RUN; no full candidate.
   All arrays and scalar counters are separate recursive arguments; the result
   structure is formed at exit. Actual lowering and the Ready proof are missing. -/
namespace Submission.R22ColumnRowSummary
open FloatLib.Floats Competition

@[inline] def rawSafe (q : Binary32) : Bool := R7W12.rawNotNaN q.raw.1

structure Prepared where
  values : Array Float32
  colSafe : Array Bool

def prepareLoop (raw : Array Binary32) (n p : Nat)
    (left sourceIndex row col flagBase : Nat)
    (values : Array Float32) (flags : Array Bool) : Prepared :=
  match left with
  | 0 => ⟨values,flags⟩
  | left+1 =>
    let q := raw.getD sourceIndex posZero
    let values := values.push (ExecFloat.Binary.toFloat32 q)
    let flags := flags.modify (flagBase+col) (fun good => good && rawSafe q)
    if col+1 < p then
      prepareLoop raw n p left (sourceIndex+1) row (col+1) flagBase values flags
    else if row+1 < n then
      prepareLoop raw n p left (sourceIndex+1) (row+1) 0 flagBase values flags
    else
      prepareLoop raw n p left (sourceIndex+1) 0 0 (flagBase+p) values flags

def prepare (batch n p : Nat) (raw : Array Binary32) : Prepared :=
  prepareLoop raw n p (batch*n*p) 0 0 0 0
    (Array.mkEmpty (batch*n*p)) (Array.replicate (batch*p) true)

def Ready (batch n p : Nat) (raw : Array Binary32) (prepared : Prepared) : Prop :=
  raw.size = batch*n*p ∧
  prepared.values = raw.map ExecFloat.Binary.toFloat32 ∧
  prepared.colSafe.size = batch*p ∧
  ∀ (b : Fin batch) (j : Fin p),
    prepared.colSafe.getD (b.val*p+j.val) false = true ↔
      ∀ k : Fin n, rawSafe (raw.getD (b.val*n*p+k.val*p+j.val) posZero) = true

theorem getD_of_ready (batch n p : Nat) (raw : Array Binary32) (prepared : Prepared)
    (hready : Ready batch n p raw prepared) (i : Nat) :
    prepared.values.getD i Packed10.zero32 = ExecFloat.Binary.toFloat32 (raw.getD i posZero) := by
  rw [hready.2.1]
  exact Packed10.nativeA_getD raw i

theorem column_read_not_nan (batch n p : Nat) (raw : Array Binary32) (prepared : Prepared)
    (hready : Ready batch n p raw prepared) (b : Fin batch) (j : Fin p)
    (hsafe : prepared.colSafe.getD (b.val*p+j.val) false = true) (k : Fin n) :
    (ExecFloat.Binary.toFloat32 (raw.getD (b.val*n*p+k.val*p+j.val) posZero)).isNaN = false := by
  have h := ((hready.2.2.2 b j).mp hsafe) k
  rw [rawSafe,R7W12.rawNotNaN_eq_native_classifier] at h
  simpa using h

@[inline] def rowMaskStep (mask : UInt8) (a0 a1 a2 a3 : Binary32) : UInt8 :=
  mask &&& ((if rawSafe a0 then (1 : UInt8) else 0) |||
    (if rawSafe a1 then (2 : UInt8) else 0) |||
    (if rawSafe a2 then (4 : UInt8) else 0) |||
    (if rawSafe a3 then (8 : UInt8) else 0))

def RowMaskReady (n baseA : Nat) (A : Array Binary32) (mask : UInt8) : Prop :=
  ∀ lane : Fin 4, ((mask &&& ((1 : UInt8) <<< UInt8.ofNat lane.val)) != 0) = true ↔
    ∀ k : Fin n, rawSafe (A.getD (baseA+lane.val*n+k.val) posZero) = true

theorem row_read_not_nan (n baseA : Nat) (A : Array Binary32) (mask : UInt8)
    (hready : RowMaskReady n baseA A mask) (lane : Fin 4)
    (hsafe : ((mask &&& ((1 : UInt8) <<< UInt8.ofNat lane.val)) != 0) = true)
    (k : Fin n) :
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+lane.val*n+k.val) posZero)).isNaN = false := by
  have h := ((hready lane).mp hsafe) k
  rw [rawSafe,R7W12.rawNotNaN_eq_native_classifier] at h
  simpa using h

theorem column_dot_read_not_nan (batch n p : Nat) (raw : Array Binary32) (prepared : Prepared)
    (hready : Ready batch n p raw prepared) (b : Fin batch) (j : Fin p)
    (hsafe : prepared.colSafe.getD (b.val*p+j.val) false = true) (k : Fin n) :
    (ExecFloat.Binary.toFloat32 (raw.getD (b.val*n*p+j.val+k.val*p) posZero)).isNaN = false := by
  have h := column_read_not_nan batch n p raw prepared hready b j hsafe k
  have haddr : b.val*n*p+k.val*p+j.val = b.val*n*p+j.val+k.val*p := by omega
  simpa only [haddr] using h

end Submission.R22ColumnRowSummary
