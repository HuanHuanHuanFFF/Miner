/- R23 proof-only caller transport. Exact Nat resident8 fallback runtime is unchanged.
   NOT_RUN: selected roots require the pinned public runner. -/
namespace Submission.R23NatPrefix
open FloatLib.Floats Competition
open R22Resident8

def Reads (f : Nat → Binary32) (start p : Nat)
    (t : Vector R22Resident8.Words (R22Pair8.groups p)) : Prop :=
  (∀ j, R22Resident8.read0 t j = f (start + j.val)) ∧
  (∀ j, R22Resident8.read1 t j = f (start + p + j.val)) ∧
  (∀ j, R22Resident8.read2 t j = f (start + p + p + j.val)) ∧
  (∀ j, R22Resident8.read3 t j = f (start + p + p + p + j.val))

theorem rows4_prefix (f : Nat → Binary32) (start p n a b c : Nat)
    (A B : Array Binary32) (cache : Array R22Pair8.BP)
    (hr : Reads f start p (tiles p n a b c A B cache))
    (out : Array Binary32) (ho : RowStream.Prefix f start out) :
    RowStream.Prefix f (start + 4 * p) (rows4 p n a b c A B cache out) := by
  unfold rows4
  split
  · rename_i hp
    simpa only [hp, Nat.mul_zero, Nat.add_zero] using ho
  · let t := tiles p n a b c A B cache
    have h0 := RowStream.emit_prefix f start p (R22Resident8.read0 t) out ho hr.1
    have h1 := RowStream.emit_prefix f (start+p) p (R22Resident8.read1 t) _ h0 hr.2.1
    have h2 := RowStream.emit_prefix f (start+p+p) p (R22Resident8.read2 t) _ h1 hr.2.2.1
    have h3 := RowStream.emit_prefix f (start+p+p+p) p (R22Resident8.read3 t) _ h2 hr.2.2.2
    have he : start+p+p+p+p = start+4*p := by omega
    simpa only [he] using h3

def BlockReads (f : Nat → Binary32) (start m n p b : Nat)
    (A B : Array Binary32) (cache : Array R22Pair8.BP)
    : Prop :=
  ∀ r : Fin (m/4), Reads f (start + r.val * (4*p)) p
    (tiles p n ((b*m+4*r.val)*n) (b*n*p) (b*n*R22Pair8.groups p) A B cache)

theorem blocks_prefix (f : Nat → Binary32) (start m n p b : Nat)
    (A B : Array Binary32) (cache : Array R22Pair8.BP)
    (hr : BlockReads f start m n p b A B cache)
    (out : Array Binary32) (ho : RowStream.Prefix f start out) :
    RowStream.Prefix f (start + (m/4)*(4*p)) (blocks m n p b A B cache out) := by
  unfold blocks
  apply RowStream.foldl_inv (m/4) _
    (fun k acc => RowStream.Prefix f (start+k*(4*p)) acc)
  · intro r acc ha
    have hs := rows4_prefix f (start+r.val*(4*p)) p n
      ((b*m+4*r.val)*n) (b*n*p) (b*n*R22Pair8.groups p) A B cache (hr r) acc ha
    simpa only [Nat.add_mul, Nat.one_mul, Nat.add_assoc] using hs
  · simpa only [Nat.zero_mul, Nat.add_zero] using ho

theorem batch_point (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b i j : Nat) (hi : i<m) (hj : j<p) :
    RowStream.point batch m n p A B ((b*m+i)*p+j) =
      NativeFinal.dot n ((b*m+i)*n) (b*n*p+j) p A.toArray B.toArray := by
  have hm : 0<m := Nat.zero_lt_of_lt hi
  have hp : 0<p := Nat.zero_lt_of_lt hj
  have hq : (b*m+i)/m=b := by
    rw [Nat.mul_comm b m, Nat.mul_add_div hm, Nat.div_eq_of_lt hi, Nat.add_zero]
  rw [RowStream.point_row batch m n p A B (b*m+i) j hm hp hj, hq]

theorem tail_read (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Nat) (j : Fin ((m%4)*p)) :
    NativeFinal.dot n ((b*m+m/4*4+j.val/p)*n) (b*n*p+j.val%p) p A.toArray B.toArray =
      RowStream.point batch m n p A B (b*m*p+(m/4)*(4*p)+j.val) := by
  have hp : 0<p := by
    have hh := j.isLt
    by_contra hn
    have hz : p=0 := by omega
    simp only [hz, Nat.mul_zero] at hh
    omega
  have hjq : j.val/p < m%4 := (Nat.div_lt_iff_lt_mul hp).2 j.isLt
  have hi : m/4*4+j.val/p<m := by omega
  have hj : j.val%p<p := Nat.mod_lt _ hp
  have he : (b*m+(m/4*4+j.val/p))*p+j.val%p = b*m*p+(m/4)*(4*p)+j.val := by
    have hd := Nat.div_add_mod j.val p
    have hc : j.val/p*p+j.val%p=j.val := by simpa only [Nat.mul_comm] using hd
    simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc, hc]
  have hh := batch_point batch m n p A B b (m/4*4+j.val/p) (j.val%p) hi hj
  rw [he] at hh
  simpa only [Nat.add_assoc] using hh.symm

theorem rows_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Nat) (cache : Array R22Pair8.BP)
    (hr : BlockReads (RowStream.point batch m n p A B) (b*m*p) m n p b
      A.toArray B.toArray cache) (out : Array Binary32)
    (ho : RowStream.Prefix (RowStream.point batch m n p A B) (b*m*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b+1)*m*p)
      (rows m n p b A.toArray B.toArray cache out) := by
  have hb := blocks_prefix (RowStream.point batch m n p A B) (b*m*p) m n p b
    A.toArray B.toArray cache hr out ho
  have ht := RowStream.emit_prefix (RowStream.point batch m n p A B)
    (b*m*p+(m/4)*(4*p)) ((m%4)*p)
    (fun j => NativeFinal.dot n ((b*m+m/4*4+j.val/p)*n) (b*n*p+j.val%p) p A.toArray B.toArray)
    _ hb (tail_read batch m n p A B b)
  have hd : m/4*4+m%4=m := by omega
  have he : b*m*p+(m/4)*(4*p)+(m%4)*p=(b+1)*m*p := by
    calc
      _ = b*m*p+(m/4*4+m%4)*p := by simp only [Nat.add_mul, Nat.mul_assoc, Nat.add_assoc]
      _ = (b+1)*m*p := by rw [hd]; simp only [Nat.add_mul, Nat.one_mul]
  simpa only [rows, he] using ht

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (cache : Array R22Pair8.BP)
    (hr : ∀ b : Fin batch, BlockReads (RowStream.point batch m n p A B) (b.val*m*p)
      m n p b.val A.toArray B.toArray cache) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p)
      (output batch m n p A.toArray B.toArray cache) := by
  unfold output
  exact RowStream.foldl_inv batch _
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b*m*p) acc)
    (fun b acc ha => rows_prefix batch m n p A B b.val cache (hr b) acc ha)
    (Array.mkEmpty (batch*m*p)) ⟨by simp, by intro j hj; simp at hj⟩

theorem output_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (cache : Array R22Pair8.BP)
    (hr : ∀ b : Fin batch, BlockReads (RowStream.point batch m n p A B) (b.val*m*p)
      m n p b.val A.toArray B.toArray cache) :
    (⟨output batch m n p A.toArray B.toArray cache,
      output_size batch m n p A.toArray B.toArray cache⟩ : Vector Binary32 (batch*m*p)) =
      referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch*m*p) _ (output_prefix batch m n p A B cache hr)).trans
    (RowStream.points_eq_reference batch m n p A B)
end Submission.R23NatPrefix
