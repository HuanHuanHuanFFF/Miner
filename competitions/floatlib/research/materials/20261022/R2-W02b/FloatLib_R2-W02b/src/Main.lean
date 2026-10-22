namespace Packed4

def tileResults (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch) :
    Vector (Vector (Vector F4 (groups p)) m) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun i =>
      Vector.ofFn fun g =>
        dot4 n ((b.val * m + i.val) * n) A ((B.get b).get g) 0
          zero32 zero32 zero32 zero32

theorem tileResults_get (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector F4 n) (groups p)) batch)
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) :
    (((tileResults batch m n p A B).get b).get i).get g =
      dot4 n ((b.val * m + i.val) * n) A ((B.get b).get g) 0
        zero32 zero32 zero32 zero32 := by
  simp only [tileResults, vector_get_ofFn]

theorem tile_finish (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (i : Fin m) (g : Fin (groups p)) (l : Fin 4)
    (hcol : 4 * g.val + l.val < p) :
    finish n ((b.val * m + i.val) * n)
        (b.val * n * p + (4 * g.val + l.val)) p A.toArray B.toArray
        (lane ((((tileResults batch m n p
          (A.toArray.map ExecFloat.Binary.toFloat32) (packB batch n p B)).get b).get i).get g) l) =
      NativeFinal.dot n ((b.val * m + i.val) * n)
        (b.val * n * p + (4 * g.val + l.val)) p A.toArray B.toArray := by
  rw [tileResults_get]
  apply finish_dot4_lane
  intro k
  rw [packB_lane batch n p B b g k l hcol]
  rw [index_address (b.val * n) k.val p (4 * g.val + l.val)]

def outputFromTiles (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector F4 (groups p)) m) batch)
    (q : Fin (batch * m * p)) : Binary32 :=
  let d := bmmDecodeC m p q.val
  let b : Fin batch := ⟨d.1, (decode_bounds batch m p q).1⟩
  let i : Fin m := ⟨d.2.1, (decode_bounds batch m p q).2.1⟩
  let g : Fin (groups p) :=
    ⟨d.2.2 / 4, groups_pos_of_col p d.2.2 (decode_bounds batch m p q).2.2⟩
  let l : Fin 4 := ⟨d.2.2 % 4, Nat.mod_lt _ (by decide)⟩
  finish n ((d.1 * m + d.2.1) * n) (d.1 * n * p + d.2.2) p A.toArray B.toArray
    (lane (((tiles.get b).get i).get g) l)

theorem outputFromTiles_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (q : Fin (batch * m * p)) :
    outputFromTiles batch m n p A B
        (tileResults batch m n p (A.toArray.map ExecFloat.Binary.toFloat32)
          (packB batch n p B)) q =
      let (b, i, j) := bmmDecodeC m p q.val
      NativeFinal.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray := by
  let d := bmmDecodeC m p q.val
  let b : Fin batch := ⟨d.1, (decode_bounds batch m p q).1⟩
  let i : Fin m := ⟨d.2.1, (decode_bounds batch m p q).2.1⟩
  let g : Fin (groups p) :=
    ⟨d.2.2 / 4, groups_pos_of_col p d.2.2 (decode_bounds batch m p q).2.2⟩
  let l : Fin 4 := ⟨d.2.2 % 4, Nat.mod_lt _ (by decide)⟩
  have hc : 4 * g.val + l.val = d.2.2 := column_decomposition d.2.2
  have hcol : 4 * g.val + l.val < p := by
    rw [hc]
    exact (decode_bounds batch m p q).2.2
  have ht := tile_finish batch m n p A B b i g l hcol
  change finish n ((b.val * m + i.val) * n) (b.val * n * p + d.2.2) p
      A.toArray B.toArray
      (lane ((((tileResults batch m n p
        (A.toArray.map ExecFloat.Binary.toFloat32) (packB batch n p B)).get b).get i).get g) l) =
    NativeFinal.dot n ((b.val * m + i.val) * n) (b.val * n * p + d.2.2) p
      A.toArray B.toArray
  simpa only [hc] using ht

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := packB batch n p B
  let tiles := tileResults batch m n p nativeA packedB
  Vector.ofFn (outputFromTiles batch m n p A B tiles)

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  unfold core referenceBmm
  dsimp only
  apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
  funext q
  rw [outputFromTiles_eq]
  dsimp only
  rw [NativeFinal.dot_eq]
  simp only [add_eq, mul_eq]
  apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
  funext acc k
  have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
    (bmmDecodeC m p q.val).2.2
  rw [hi]

end Packed4

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else Packed4.core batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = referenceBmm batch m n p A B := by
    unfold bmm
    split
    · rfl
    · split
      · rfl
      · exact Packed4.core_eq_reference batch m n p A B
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceBmm_spec batch m n p A B)
