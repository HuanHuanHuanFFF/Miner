/- Reusable actual-producer read interface. NOT_COMPILED; not in timed source.
   The generic append-prefix pattern follows the separately retained R22
   Pair8CacheProof source, whose acceptance is not inherited here. -/
namespace Submission.R22Resident16
open FloatLib.Floats Competition

def PackedPrefix {α : Type} (f : Nat → α) (k : Nat) (out : Array α) : Prop :=
  out.size = k ∧ ∀ i (hi : i < out.size), out[i] = f i

theorem packed_prefix_push {α : Type} (f : Nat → α) (k : Nat) (out : Array α)
    (h : PackedPrefix f k out) : PackedPrefix f (k + 1) (out.push (f k)) := by
  refine ⟨by simp only [Array.size_push, h.1], ?_⟩
  intro i hi
  have hi' : i < out.size + 1 := by simpa only [Array.size_push] using hi
  by_cases hlt : i < out.size
  · rw [Array.getElem_push_lt hlt]
    exact h.2 i hlt
  · have he : i = out.size := by omega
    subst i
    rw [Array.getElem_push_eq, h.1]

def packedBPoint (n p : Nat) (B : Array Binary32) (q : Nat) : Vector B4 n :=
  packBGroup n p ((q / groups p) * n * p + 4 * (q % groups p)) B
    (min 4 (p - 4 * (q % groups p)))

theorem packedBGroup_eq_point (n p b : Nat) (B : Array Binary32) (g : Fin (groups p)) :
    packBGroup n p (b * n * p + 4 * g.val) B (min 4 (p - 4 * g.val)) =
      packedBPoint n p B (b * groups p + g.val) := by
  have hG : 0 < groups p := Nat.zero_lt_of_lt g.isLt
  have hd : (b * groups p + g.val) / groups p = b := by
    rw [Nat.mul_comm b (groups p), Nat.mul_add_div hG,
      Nat.div_eq_of_lt g.isLt, Nat.add_zero]
  have hm : (b * groups p + g.val) % groups p = g.val :=
    Nat.mul_add_mod_of_lt g.isLt
  simp only [packedBPoint, hd, hm]

theorem packBBatch_prefix (n p b : Nat) (B : Array Binary32) (out : Array (Vector B4 n))
    (hout : PackedPrefix (packedBPoint n p B) (b * groups p) out) :
    PackedPrefix (packedBPoint n p B) ((b + 1) * groups p) (packBBatch n p b B out) := by
  unfold packBBatch
  have h := RowStream.foldl_inv (β := Array (Vector B4 n)) (groups p)
    (fun acc g => acc.push
      (packBGroup n p (b * n * p + 4 * g.val) B (min 4 (p - 4 * g.val))))
    (fun g acc => PackedPrefix (packedBPoint n p B) (b * groups p + g) acc)
    (by
      intro g acc hacc
      rw [packedBGroup_eq_point]
      simpa only [Nat.add_assoc] using
        packed_prefix_push (packedBPoint n p B) (b * groups p + g.val) acc hacc)
    out (by simpa only [Nat.add_zero] using hout)
  simpa only [Nat.add_mul, Nat.one_mul] using h

theorem packBData_prefix (batch n p : Nat) (B : Array Binary32) :
    PackedPrefix (packedBPoint n p B) (batch * groups p) (packBData batch n p B) := by
  unfold packBData
  exact RowStream.foldl_inv (β := Array (Vector B4 n)) batch
    (fun acc b => packBBatch n p b.val B acc)
    (fun b acc => PackedPrefix (packedBPoint n p B) (b * groups p) acc)
    (fun b acc hacc => packBBatch_prefix n p b.val B acc hacc)
    (Array.mkEmpty (batch * groups p))
    ⟨by simp, by intro i hi; simp at hi⟩

theorem packB_get (batch n p : Nat) (B : Array Binary32)
    (b : Fin batch) (g : Fin (groups p)) :
    (packB batch n p B).get (tileIndex batch p b g) =
      packBGroup n p (b.val * n * p + 4 * g.val) B (min 4 (p - 4 * g.val)) := by
  have hp := packBData_prefix batch n p B
  have hi : b.val * groups p + g.val < (packBData batch n p B).size := by
    rw [hp.1]
    exact (tileIndex batch p b g).isLt
  have hv := hp.2 (b.val * groups p + g.val) hi
  have he : (packB batch n p B).get (tileIndex batch p b g) =
      packedBPoint n p B (b.val * groups p + g.val) := by
    exact hv
  exact he.trans (packedBGroup_eq_point n p b.val B g).symm

/- Requires StorageInterface.lean.inc for laneB and packBGroup_lane. -/
theorem packB_selected (batch n p : Nat) (B : Array Binary32)
    (b : Fin batch) (k : Fin n) (j : Fin p) :
    laneB (((packB batch n p B).get
      (tileIndex batch p b ⟨j.val / 4, by have hj := j.isLt; unfold groups; omega⟩)).get k)
      ⟨j.val % 4, Nat.mod_lt j.val (by decide : 0 < 4)⟩ =
      ExecFloat.Binary.toFloat32 (B.getD (b.val * n * p + k.val * p + j.val) posZero) := by
  have hj := j.isLt
  have hd := Nat.div_add_mod j.val 4
  have hmod := Nat.mod_lt j.val (by decide : 0 < 4)
  have hg : j.val / 4 < groups p := by unfold groups; omega
  have hv : j.val % 4 < min 4 (p - 4 * (j.val / 4)) := by omega
  rw [packB_get]
  have h := packBGroup_lane n p (b.val * n * p + 4 * (j.val / 4))
    (min 4 (p - 4 * (j.val / 4))) B ⟨j.val % 4, hmod⟩ hv k
  have ha : b.val * n * p + 4 * (j.val / 4) + k.val * p + j.val % 4 =
      b.val * n * p + k.val * p + j.val := by omega
  simpa only [ha] using h

end Submission.R22Resident16
