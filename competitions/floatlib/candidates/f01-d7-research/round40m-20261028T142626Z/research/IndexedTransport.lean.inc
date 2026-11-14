namespace Submission.R22IndexedResident8
open FloatLib.Floats Competition

theorem tile_eq_nat (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (h : TileBounds p n baseA baseC A.size cache.size) (second : Bool) :
    tile p n baseA baseB baseC A B cache h second =
      R22Resident8.tile p n baseA baseB baseC A B cache second := by
  unfold tile R22Resident8.tile
  rw [within_eq]

theorem tiles_eq_nat (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (h : BlockBounds p n baseA baseC A.size cache.size) :
    tiles p n baseA baseB baseC A B cache h =
      R22Resident8.tiles p n baseA baseB baseC A B cache := by
  unfold tiles R22Resident8.tiles
  congr 1
  funext g
  exact tile_eq_nat p n baseA (baseB + 2 * g.val) (baseC + g.val) A B cache _ _

theorem output_eq_nat (batch m n p : Nat) (A B : Array Binary32) (cache : Array BP)
    (h : ∀ b : Fin batch, RowBounds m n p b.val A cache) :
    output batch m n p A B cache h = R22Resident8.output batch m n p A B cache := by
  simp only [output, R22Resident8.output, rows, R22Resident8.rows, blocks,
    R22Resident8.blocks, rows4, R22Resident8.rows4, tiles_eq_nat]

end Submission.R22IndexedResident8
