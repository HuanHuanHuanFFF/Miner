namespace Submission.Packed4.MatrixBounds

open FloatLib.Floats

/-- A valid batch and row select a valid flattened row. -/
theorem row_lt {batch m b i : Nat} (hb : b < batch) (hi : i < m) :
    b * m + i < batch * m := by
  calc
    b * m + i < b * m + m := Nat.add_lt_add_left hi (b * m)
    _ = (b + 1) * m := by simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m := Nat.mul_le_mul_right m (by omega)

/-- The exclusive end of a valid row is at most the matrix length. -/
theorem row_end_le {batch m n b i : Nat} (hb : b < batch) (hi : i < m) :
    (b * m + i) * n + n ≤ batch * m * n := by
  have hr := row_lt hb hi
  calc
    (b * m + i) * n + n = (b * m + i + 1) * n := by
      simp only [Nat.add_mul, Nat.one_mul]
    _ ≤ batch * m * n := Nat.mul_le_mul_right n (by omega)

/-- Every position in a valid row lies in the matrix. -/
theorem point_bound {batch m n b i k : Nat}
    (hb : b < batch) (hi : i < m) (hk : k < n) :
    (b * m + i) * n + k < batch * m * n := by
  calc
    (b * m + i) * n + k < (b * m + i) * n + n :=
      Nat.add_lt_add_left hk ((b * m + i) * n)
    _ ≤ batch * m * n := row_end_le hb hi

/-- The final position of a nonempty valid row lies in the matrix. -/
theorem row_span {batch m n b i : Nat}
    (hb : b < batch) (hi : i < m) (hn : 0 < n) :
    (b * m + i) * n + (n - 1) < batch * m * n := by
  exact point_bound hb hi (by omega)

/-- One valid row contains n entries, even when n is zero. -/
theorem row_count_le {batch m n b i : Nat} (hb : b < batch) (hi : i < m) :
    n ≤ batch * m * n := by
  have he := row_end_le (n := n) hb hi
  omega

/-- Mapping changes elements but preserves the input vector length. -/
theorem nativeA_size (batch m n : Nat) (A : Vector Binary32 (batch * m * n)) :
    (A.toArray.map ExecFloat.Binary.toFloat32).size = batch * m * n := by
  rw [Array.size_map]
  exact A.size_toArray

/-- A matrix length check supplies all row admission evidence. -/
theorem array_row_bounds (batch m n : Nat) (A : Array Float32)
    (hsize : A.size = batch * m * n) (b : Fin batch) (i : Fin m)
    (hn : 0 < n) (hAS : A.size < USize.size) :
    n < USize.size ∧
      (b.val * m + i.val) * n < USize.size ∧
      (b.val * m + i.val) * n + (n - 1) < A.size := by
  have htotal : batch * m * n < USize.size := by
    simpa only [hsize] using hAS
  have hc := row_count_le (n := n) b.isLt i.isLt
  have hbase : (b.val * m + i.val) * n < batch * m * n := by
    simpa only [Nat.add_zero] using
      (point_bound (k := 0) b.isLt i.isLt hn)
  have hlast := row_span b.isLt i.isLt hn
  refine ⟨Nat.lt_of_le_of_lt hc htotal, Nat.lt_trans hbase htotal, ?_⟩
  simpa only [hsize] using hlast

/-- The original typed input supplies the array length evidence. -/
theorem native_row_bounds (batch m n : Nat)
    (A : Vector Binary32 (batch * m * n)) (b : Fin batch) (i : Fin m)
    (hn : 0 < n)
    (hAS : (A.toArray.map ExecFloat.Binary.toFloat32).size < USize.size) :
    n < USize.size ∧
      (b.val * m + i.val) * n < USize.size ∧
      (b.val * m + i.val) * n + (n - 1) <
        (A.toArray.map ExecFloat.Binary.toFloat32).size := by
  exact array_row_bounds batch m n (A.toArray.map ExecFloat.Binary.toFloat32)
    (nativeA_size batch m n A) b i hn hAS

/-- The same single length check also bounds every actual row address. -/
theorem array_point_bounds (batch m n : Nat) (A : Array Float32)
    (hsize : A.size = batch * m * n) (b : Fin batch) (i : Fin m)
    (k : Nat) (hk : k < n) (hAS : A.size < USize.size) :
    (b.val * m + i.val) * n + k < A.size ∧
      (b.val * m + i.val) * n + k < USize.size := by
  have ha : (b.val * m + i.val) * n + k < A.size := by
    simpa only [hsize] using (point_bound b.isLt i.isLt hk)
  exact ⟨ha, Nat.lt_trans ha hAS⟩

end Submission.Packed4.MatrixBounds

namespace Submission.Packed4.WholeCall

open FloatLib.Floats Competition

/-- Row evidence is passed to the existing word loop without local tests. -/
def tileResultsWithin (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n)
    (hAS : A.size < USize.size) :
    Vector (Vector (Vector F4 (groups p)) m) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun i =>
      let h := MatrixBounds.array_row_bounds batch m n A hsize b i hn hAS
      Vector.ofFn fun g =>
        Submission.Packed4.within n ((b.val * m + i.val) * n)
          A ((B.get b).get g) h.1 h.2.1 h.2.2 hAS

theorem tileResultsWithin_eq (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n)
    (hAS : A.size < USize.size) :
    tileResultsWithin batch m n p A B hn hsize hAS =
      tileResults batch m n p A B := by
  unfold tileResultsWithin tileResults
  apply congrArg (fun f : Fin batch → Vector (Vector F4 (groups p)) m => Vector.ofFn f)
  funext b
  apply congrArg (fun f : Fin m → Vector F4 (groups p) => Vector.ofFn f)
  funext i
  dsimp only
  apply congrArg (fun f : Fin (groups p) → F4 => Vector.ofFn f)
  funext g
  apply Submission.Packed4.within_eq

theorem tileResultsWithin_get (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n)
    (hAS : A.size < USize.size)
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) :
    (((tileResultsWithin batch m n p A B hn hsize hAS).get b).get i).get g =
      dot4 n ((b.val * m + i.val) * n) A ((B.get b).get g) 0
        zero32 zero32 zero32 zero32 := by
  rw [tileResultsWithin_eq]
  exact tileResults_get batch m n p A B b i g

theorem tileResultsWithin_lane (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n)
    (hAS : A.size < USize.size)
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) (l : Fin 4) :
    lane ((((tileResultsWithin batch m n p A B hn hsize hAS).get b).get i).get g) l =
      lane (dot4 n ((b.val * m + i.val) * n) A ((B.get b).get g) 0
        zero32 zero32 zero32 zero32) l := by
  rw [tileResultsWithin_get]

theorem tileResultsWithin_finish (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : 0 < n)
    (hAS : (A.toArray.map ExecFloat.Binary.toFloat32).size < USize.size)
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) (l : Fin 4)
    (hcol : 4 * g.val + l.val < p) :
    finish n ((b.val * m + i.val) * n)
        (b.val * n * p + (4 * g.val + l.val)) p A.toArray B.toArray
        (lane ((((tileResultsWithin batch m n p
          (A.toArray.map ExecFloat.Binary.toFloat32) (packB batch n p B)
          hn (MatrixBounds.nativeA_size batch m n A) hAS).get b).get i).get g) l) =
      NativeFinal.dot n ((b.val * m + i.val) * n)
        (b.val * n * p + (4 * g.val + l.val)) p A.toArray B.toArray := by
  rw [tileResultsWithin_eq]
  exact tile_finish batch m n p A B b i g l hcol

/-- This is the only new run-time admission branch. -/
def selectTiles (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n) :
    Vector (Vector (Vector F4 (groups p)) m) batch :=
  if hAS : A.size < USize.size then
    tileResultsWithin batch m n p A B hn hsize hAS
  else tileResults batch m n p A B

theorem selectTiles_eq (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (hn : 0 < n) (hsize : A.size = batch * m * n) :
    selectTiles batch m n p A B hn hsize = tileResults batch m n p A B := by
  unfold selectTiles
  split
  · exact tileResultsWithin_eq batch m n p A B hn hsize _
  · rfl

def coreOnce (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : 0 < n) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := packB batch n p B
  let tiles := selectTiles batch m n p nativeA packedB hn
    (MatrixBounds.nativeA_size batch m n A)
  Vector.ofFn (outputFromTiles batch m n p A B tiles)

theorem coreOnce_eq_core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : 0 < n) :
    coreOnce batch m n p A B hn = Submission.Packed4.core batch m n p A B := by
  unfold coreOnce Submission.Packed4.core
  dsimp only
  rw [selectTiles_eq]

end Submission.Packed4.WholeCall

namespace Submission

open FloatLib.Floats Competition

/-- The existing empty-output and empty-reduction branches remain outside the fast path. -/
def bmmOnce (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if hn : n = 0 then referenceBmm batch m n p A B
  else Packed4.WholeCall.coreOnce batch m n p A B (by omega)

theorem bmmOnce_eq (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    bmmOnce batch m n p A B = bmm batch m n p A B := by
  by_cases he : batch * m * p = 0
  · simp only [bmmOnce, bmm, if_pos he, dif_pos he]
  · by_cases hn : n = 0
    · simp only [bmmOnce, bmm, if_neg he, dif_neg he, if_pos hn, dif_pos hn]
    · simp only [bmmOnce, bmm, if_neg he, dif_neg he, if_neg hn, dif_neg hn]
      exact Packed4.WholeCall.coreOnce_eq_core batch m n p A B (by omega)

theorem bmmOnce_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmmOnce batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  rw [bmmOnce_eq]
  exact bmm_spec batch m n p A B

end Submission
