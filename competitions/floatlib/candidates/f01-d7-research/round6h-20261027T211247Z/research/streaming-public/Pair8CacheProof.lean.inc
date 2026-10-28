/- Minimal cache-value proof for exact Pair8/cd0e3399. NOT_RUN.
   No state loop, writer, public binding, or runtime body is changed. -/
namespace Submission.R22Pair8
open FloatLib.Floats Competition

def CachePrefix (f : Nat → BP) (k : Nat) (out : Array BP) : Prop :=
  out.size = k ∧ ∀ i (hi : i < out.size), out[i] = f i

theorem cache_prefix_push (f : Nat → BP) (k : Nat) (out : Array BP)
    (h : CachePrefix f k out) : CachePrefix f (k + 1) (out.push (f k)) := by
  refine ⟨by simp only [Array.size_push, h.1], ?_⟩
  intro i hi
  have hi' : i < out.size + 1 := by simpa only [Array.size_push] using hi
  by_cases hlt : i < out.size
  · rw [Array.getElem_push_lt hlt]
    exact h.2 i hlt
  · have he : i = out.size := by omega
    subst i
    rw [Array.getElem_push_eq, h.1]

def cacheEntry (p base : Nat) (B : Array Binary32) (g : Nat) : BP :=
  ⟨ExecFloat.Binary.toFloat32 (B.getD (base + 2 * g) posZero),
   if 2 * g + 1 < p then ExecFloat.Binary.toFloat32 (B.getD (base + 2 * g + 1) posZero)
   else Packed10.zero32⟩

def cachePoint (p : Nat) (B : Array Binary32) (q : Nat) : BP :=
  cacheEntry p ((q / groups p) * p) B (q % groups p)

theorem cacheEntry_eq_point (p row : Nat) (B : Array Binary32) (g : Fin (groups p)) :
    cacheEntry p (row * p) B g.val = cachePoint p B (row * groups p + g.val) := by
  have hG : 0 < groups p := Nat.zero_lt_of_lt g.isLt
  have hd : (row * groups p + g.val) / groups p = row := by
    rw [Nat.mul_comm row (groups p), Nat.mul_add_div hG, Nat.div_eq_of_lt g.isLt, Nat.add_zero]
  have hm : (row * groups p + g.val) % groups p = g.val := Nat.mul_add_mod_of_lt g.isLt
  simp only [cachePoint, hd, hm]

theorem packRow_prefix (p row : Nat) (B : Array Binary32) (out : Array BP)
    (hout : CachePrefix (cachePoint p B) (row * groups p) out) :
    CachePrefix (cachePoint p B) ((row + 1) * groups p) (packRow p (row * p) B out) := by
  unfold packRow
  have h := RowStream.foldl_inv (β := Array BP) (groups p)
    (fun acc g => acc.push (cacheEntry p (row * p) B g.val))
    (fun g acc => CachePrefix (cachePoint p B) (row * groups p + g) acc)
    (by
      intro g acc hacc
      rw [cacheEntry_eq_point]
      simpa only [Nat.add_assoc] using cache_prefix_push (cachePoint p B)
        (row * groups p + g.val) acc hacc)
    out (by simpa only [Nat.add_zero] using hout)
  simpa only [cacheEntry, Nat.add_mul, Nat.one_mul] using h

theorem packB_prefix (batch n p : Nat) (B : Array Binary32) :
    CachePrefix (cachePoint p B) (batch * n * groups p) (packB batch n p B) := by
  unfold packB
  exact RowStream.foldl_inv (β := Array BP) (batch * n)
    (fun acc row => packRow p (row.val * p) B acc)
    (fun row acc => CachePrefix (cachePoint p B) (row * groups p) acc)
    (fun row acc hacc => packRow_prefix p row.val B acc hacc)
    (Array.mkEmpty (batch * n * groups p))
    ⟨by simp, by intro i hi; simp at hi⟩

theorem packB_get (batch n p : Nat) (B : Array Binary32)
    (row : Fin (batch * n)) (g : Fin (groups p)) :
    (packB batch n p B).getD (row.val * groups p + g.val) zeroPair =
      cacheEntry p (row.val * p) B g.val := by
  have hp := packB_prefix batch n p B
  have hrow := Nat.mul_le_mul_right (groups p) (Nat.succ_le_of_lt row.isLt)
  simp only [Nat.succ_mul] at hrow
  have hg := g.isLt
  have hi : row.val * groups p + g.val < (packB batch n p B).size := by
    rw [hp.1]
    omega
  have hv := hp.2 (row.val * groups p + g.val) hi
  have he : (packB batch n p B).getD (row.val * groups p + g.val) zeroPair =
      cachePoint p B (row.val * groups p + g.val) := by
    simpa [Array.getD, hi] using hv
  exact he.trans (cacheEntry_eq_point p row.val B g).symm

theorem packB_s0 (batch n p : Nat) (B : Array Binary32)
    (row : Fin (batch * n)) (g : Fin (groups p)) :
    ((packB batch n p B).getD (row.val * groups p + g.val) zeroPair).s0 =
      ExecFloat.Binary.toFloat32 (B.getD (row.val * p + 2 * g.val) posZero) := by
  rw [packB_get]
  rfl

theorem packB_s1 (batch n p : Nat) (B : Array Binary32)
    (row : Fin (batch * n)) (g : Fin (groups p)) (hc : 2 * g.val + 1 < p) :
    ((packB batch n p B).getD (row.val * groups p + g.val) zeroPair).s1 =
      ExecFloat.Binary.toFloat32 (B.getD (row.val * p + 2 * g.val + 1) posZero) := by
  rw [packB_get]
  simp only [cacheEntry, hc, ite_true]

end Submission.R22Pair8
