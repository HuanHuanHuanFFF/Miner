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
