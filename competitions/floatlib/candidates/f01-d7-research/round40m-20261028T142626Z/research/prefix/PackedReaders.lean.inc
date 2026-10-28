/- Actual producer/tile to all four column readers. NOT_RUN.
   Requires NatTileBinding, NatPrefix, NatReaderBridge and indexed output_eq_nat. -/
namespace Submission.R23NatReaderBridge
open FloatLib.Floats Competition

theorem packed_getTile_word (batch n p a : Nat) (A B : Array Binary32)
    (b : Fin batch) (r : Fin 4) (j : Fin p) :
    FastMul.ofBits (R23IndexedProducer.wordAt
      (R22Resident8.getTile (R22Resident8.tiles p n a (b.val*n*p)
        (b.val*n*R22Pair8.groups p) A B (R22Pair8.packB batch n p B)) j)
      r ⟨j.val%2, Nat.mod_lt _ (by decide)⟩) =
    NativeFinal.dot n (R22Resident8Projection.rowBase a (a+n) (a+2*n) (a+3*n) r)
      (b.val*n*p+j.val) p A B := by
  let g : Fin (R22Pair8.groups p) := ⟨j.val/2, by
    have hj := j.isLt
    unfold R22Pair8.groups
    omega⟩
  let c : Fin 2 := ⟨j.val%2, Nat.mod_lt _ (by decide)⟩
  have hcol : 2*g.val+c.val=j.val := by dsimp only [g,c]; omega
  have hh := R23IndexedProducer.tile_word batch n p a A B b g r c
    (by rw [hcol]; exact j.isLt)
  have haddr : b.val*n*p+2*g.val+c.val=b.val*n*p+j.val := by
    rw [Nat.add_assoc, hcol]
  rw [haddr] at hh
  simpa only [R22Resident8.getTile, R22Resident8.tiles, Packed10.vector_get_ofFn, g, c] using hh

theorem packed_dot_reads (batch n p a : Nat) (A B : Array Binary32) (b : Fin batch) :
    DotReads p n a (b.val*n*p) (b.val*n*R22Pair8.groups p) A B (R22Pair8.packB batch n p B) := by
  intro j
  refine ⟨?_, ?_, ?_, ?_⟩
  · simpa only [R22Resident8.read0, R23IndexedProducer.wordAt, R22Resident8Projection.rowBase]
      using packed_getTile_word batch n p a A B b ⟨0, by decide⟩ j
  · simpa only [R22Resident8.read1, R23IndexedProducer.wordAt, R22Resident8Projection.rowBase]
      using packed_getTile_word batch n p a A B b ⟨1, by decide⟩ j
  · simpa only [R22Resident8.read2, R23IndexedProducer.wordAt, R22Resident8Projection.rowBase]
      using packed_getTile_word batch n p a A B b ⟨2, by decide⟩ j
  · simpa only [R22Resident8.read3, R23IndexedProducer.wordAt, R22Resident8Projection.rowBase]
      using packed_getTile_word batch n p a A B b ⟨3, by decide⟩ j

theorem all_reads (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    AllReads batch m n p A B := by
  intro b r
  exact packed_dot_reads batch n p ((b.val*m+4*r.val)*n) A.toArray B.toArray b

theorem indexed_guarded_spec (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    (R22IndexedResident8.guarded batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  exact guarded_spec batch m n p A B (all_reads batch m n p A B)

end Submission.R23NatReaderBridge
