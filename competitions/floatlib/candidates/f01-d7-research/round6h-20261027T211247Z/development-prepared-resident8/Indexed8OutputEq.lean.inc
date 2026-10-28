/- Requires Indexed8LoopEq-v2ccee65d4. NOT_RUN.
   Congruence lift only; neither runtime nor shape/word guards are changed. -/
namespace Submission.R22IndexedResident8
open FloatLib.Floats Competition

theorem tile_eq (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (h : TileBounds p n baseA baseC A.size cache.size) (second : Bool) :
    tile p n baseA baseB baseC A B cache h second =
      R22Resident8.tile p n baseA baseB baseC A B cache second := by
  unfold tile R22Resident8.tile
  rw [within_eq]

theorem tiles_eq (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (h : BlockBounds p n baseA baseC A.size cache.size) :
    tiles p n baseA baseB baseC A B cache h =
      R22Resident8.tiles p n baseA baseB baseC A B cache := by
  unfold tiles R22Resident8.tiles
  congr 1
  funext g
  exact tile_eq p n baseA (baseB + 2 * g.val) (baseC + g.val) A B cache _ _

theorem rows4_eq (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (h : BlockBounds p n baseA baseC A.size cache.size)
    (out : Array Binary32) :
    rows4 p n baseA baseB baseC A B cache h out =
      R22Resident8.rows4 p n baseA baseB baseC A B cache out := by
  unfold rows4 R22Resident8.rows4
  rw [tiles_eq]

theorem blocks_eq (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : RowBounds m n p b A cache) (out : Array Binary32) :
    blocks m n p b A B cache h out = R22Resident8.blocks m n p b A B cache out := by
  unfold blocks R22Resident8.blocks
  congr 1
  funext acc r
  exact rows4_eq p n ((b * m + 4 * r.val) * n)
    (b * n * p) (b * n * R22Pair8.groups p) A B cache (h r) acc

theorem rows_eq (m n p b : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : RowBounds m n p b A cache) (out : Array Binary32) :
    rows m n p b A B cache h out = R22Resident8.rows m n p b A B cache out := by
  unfold rows R22Resident8.rows
  rw [blocks_eq]

theorem output_eq (batch m n p : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : ∀ b : Fin batch, RowBounds m n p b.val A cache) :
    output batch m n p A B cache h = R22Resident8.output batch m n p A B cache := by
  unfold output R22Resident8.output
  congr 1
  funext acc b
  exact rows_eq m n p b.val A B cache (h b) acc

end Submission.R22IndexedResident8
