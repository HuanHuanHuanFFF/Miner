/- Proof-only closure interface for exact R22Resident8 tiles and readers.
   NOT_RUN. Requires NatPrefix and indexed output_eq_nat. -/
namespace Submission.R23NatReaderBridge
open FloatLib.Floats Competition

def DotReads (p n a b c : Nat) (A B : Array Binary32) (cache : Array R22Pair8.BP) : Prop :=
  ∀ j : Fin p,
    let t := R22Resident8.tiles p n a b c A B cache
    R22Resident8.read0 t j = NativeFinal.dot n a (b+j.val) p A B ∧
    R22Resident8.read1 t j = NativeFinal.dot n (a+n) (b+j.val) p A B ∧
    R22Resident8.read2 t j = NativeFinal.dot n (a+2*n) (b+j.val) p A B ∧
    R22Resident8.read3 t j = NativeFinal.dot n (a+3*n) (b+j.val) p A B

theorem dot_point (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Nat) (r : Fin (m/4)) (lane : Fin 4) (j : Fin p) :
    NativeFinal.dot n (((b*m+4*r.val)*n)+lane.val*n) (b*n*p+j.val) p A.toArray B.toArray =
      RowStream.point batch m n p A B (b*m*p+r.val*(4*p)+lane.val*p+j.val) := by
  have hr : 4*r.val+4≤m := by have hh := r.isLt; omega
  have hi : 4*r.val+lane.val<m := by have hh := lane.isLt; omega
  have hh := R23NatPrefix.batch_point batch m n p A B b (4*r.val+lane.val) j.val hi j.isLt
  simpa only [Nat.add_mul, Nat.mul_assoc, Nat.mul_left_comm, Nat.mul_comm, Nat.add_assoc] using hh.symm

theorem block_reads (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Nat) (cache : Array R22Pair8.BP)
    (hr : ∀ r : Fin (m/4), DotReads p n ((b*m+4*r.val)*n) (b*n*p)
      (b*n*R22Pair8.groups p) A.toArray B.toArray cache) :
    R23NatPrefix.BlockReads (RowStream.point batch m n p A B) (b*m*p) m n p b
      A.toArray B.toArray cache := by
  intro r
  refine ⟨?_, ?_, ?_, ?_⟩
  · intro j
    rw [(hr r j).1]
    simpa only [Nat.zero_mul, Nat.add_zero] using dot_point batch m n p A B b r ⟨0, by decide⟩ j
  · intro j
    rw [(hr r j).2.1]
    simpa only [Nat.one_mul] using dot_point batch m n p A B b r ⟨1, by decide⟩ j
  · intro j
    rw [(hr r j).2.2.1]
    have hh := dot_point batch m n p A B b r ⟨2, by decide⟩ j
    have he : (2:Nat)*p=p+p := by omega
    simpa only [he, Nat.add_assoc] using hh
  · intro j
    rw [(hr r j).2.2.2]
    have hh := dot_point batch m n p A B b r ⟨3, by decide⟩ j
    have he : (3:Nat)*p=p+p+p := by omega
    simpa only [he, Nat.add_assoc] using hh

def AllReads (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) : Prop :=
  ∀ b : Fin batch, ∀ r : Fin (m/4),
    DotReads p n ((b.val*m+4*r.val)*n) (b.val*n*p) (b.val*n*R22Pair8.groups p)
      A.toArray B.toArray (R22Pair8.packB batch n p B.toArray)

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn : 1<n) (hp : 2≤p) (hr : AllReads batch m n p A B) :
    R22IndexedResident8.core batch m n p A B hn hp = referenceBmm batch m n p A B := by
  have href := R23NatPrefix.output_eq_reference batch m n p A B
    (R22Pair8.packB batch n p B.toArray)
    (fun b => block_reads batch m n p A B b.val _ (hr b))
  unfold R22IndexedResident8.core
  split
  · simpa only [R22IndexedResident8.output_eq_nat] using href
  · exact href

theorem guarded_spec (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hr : AllReads batch m n p A B) :
    (R22IndexedResident8.guarded batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  unfold R22IndexedResident8.guarded
  split
  · rename_i h
    have hh : A.toArray.all UnderflowZero.small = true ∧
        B.toArray.all UnderflowZero.small = true := by
      simpa only [Bool.and_eq_true] using h
    rw [UnderflowZero.zeros_eq_reference batch m n p A B hh.1 hh.2]
    exact referenceBmm_spec batch m n p A B
  · split
    · rw [core_eq_reference batch m n p A B _ _ hr]
      exact referenceBmm_spec batch m n p A B
    · exact Submission.bmm_spec batch m n p A B
end Submission.R23NatReaderBridge
