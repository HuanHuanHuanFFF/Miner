
namespace Submission.R23IndexedProducer
open FloatLib.Floats Competition
abbrev BP := R22Pair8.BP

def Prefix (f : Nat → BP) (k : Nat) (out : Array BP) : Prop :=
  out.size = k ∧ ∀ j (hj : j < out.size), out[j] = f j

theorem prefix_push (f : Nat → BP) (k : Nat) (out : Array BP)
    (h : Prefix f k out) : Prefix f (k + 1) (out.push (f k)) := by
  refine ⟨by simp only [Array.size_push, h.1], ?_⟩
  intro j hj
  have hj' : j < out.size + 1 := by simpa only [Array.size_push] using hj
  by_cases hlt : j < out.size
  · rw [Array.getElem_push_lt hlt]
    exact h.2 j hlt
  · have he : j = out.size := by omega
    subst j
    rw [Array.getElem_push_eq, h.1]

def point (p : Nat) (B : Array Binary32) (q : Nat) : BP :=
  let row := q / R22Pair8.groups p
  let g := q % R22Pair8.groups p
  ⟨ExecFloat.Binary.toFloat32 (B.getD (row * p + 2 * g) posZero),
    if 2 * g + 1 < p then
      ExecFloat.Binary.toFloat32 (B.getD (row * p + 2 * g + 1) posZero)
    else Packed10.zero32⟩

theorem point_pair (p row : Nat) (B : Array Binary32) (g : Fin (R22Pair8.groups p)) :
    point p B (row * R22Pair8.groups p + g.val) =
      (⟨ExecFloat.Binary.toFloat32 (B.getD (row * p + 2 * g.val) posZero),
        if 2 * g.val + 1 < p then
          ExecFloat.Binary.toFloat32 (B.getD (row * p + 2 * g.val + 1) posZero)
        else Packed10.zero32⟩ : BP) := by
  have hG : 0 < R22Pair8.groups p := Nat.zero_lt_of_lt g.isLt
  have hd : (row * R22Pair8.groups p + g.val) / R22Pair8.groups p = row := by
    rw [Nat.mul_comm row (R22Pair8.groups p), Nat.mul_add_div hG,
      Nat.div_eq_of_lt g.isLt, Nat.add_zero]
  have hm : (row * R22Pair8.groups p + g.val) % R22Pair8.groups p = g.val :=
    Nat.mul_add_mod_of_lt g.isLt
  simp only [point, hd, hm]

theorem packRow_prefix (p row : Nat) (B : Array Binary32) (out : Array BP)
    (h : Prefix (point p B) (row * R22Pair8.groups p) out) :
    Prefix (point p B) ((row + 1) * R22Pair8.groups p)
      (R22Pair8.packRow p (row * p) B out) := by
  have hh : Prefix (point p B) (row * R22Pair8.groups p + R22Pair8.groups p)
      (R22Pair8.packRow p (row * p) B out) := by
    unfold R22Pair8.packRow
    apply RowStream.foldl_inv (R22Pair8.groups p) _
      (fun j acc => Prefix (point p B) (row * R22Pair8.groups p + j) acc)
    · intro j acc hacc
      dsimp only
      rw [← point_pair p row B j]
      simpa only [Nat.add_assoc] using
        prefix_push (point p B) (row * R22Pair8.groups p + j.val) acc hacc
    · simpa only [Nat.add_zero] using h
  simpa only [Nat.add_mul, Nat.one_mul] using hh

theorem packB_prefix (batch n p : Nat) (B : Array Binary32) :
    Prefix (point p B) (batch * n * R22Pair8.groups p) (R22Pair8.packB batch n p B) := by
  unfold R22Pair8.packB
  apply RowStream.foldl_inv (batch * n) _
    (fun row acc => Prefix (point p B) (row * R22Pair8.groups p) acc)
  · intro row acc hacc
    exact packRow_prefix p row.val B acc hacc
  · constructor
    · simp
    · intro j hj
      simp at hj

theorem packB_get (batch n p : Nat) (B : Array Binary32)
    (row : Fin (batch * n)) (g : Fin (R22Pair8.groups p)) :
    (R22Pair8.packB batch n p B).getD (row.val * R22Pair8.groups p + g.val)
      R22Pair8.zeroPair =
      (⟨ExecFloat.Binary.toFloat32 (B.getD (row.val * p + 2 * g.val) posZero),
        if 2 * g.val + 1 < p then
          ExecFloat.Binary.toFloat32 (B.getD (row.val * p + 2 * g.val + 1) posZero)
        else Packed10.zero32⟩ : BP) := by
  have h := packB_prefix batch n p B
  have hx := Nat.mul_le_mul_right (R22Pair8.groups p) row.isLt
  rw [Nat.succ_mul] at hx
  have hi : row.val * R22Pair8.groups p + g.val < (R22Pair8.packB batch n p B).size := by
    rw [h.1]
    have hg := g.isLt
    omega
  rw [Array.getD, dif_pos hi, h.2 _ hi]
  exact point_pair p row.val B g

theorem packB_read (batch n p : Nat) (B : Array Binary32) (b : Fin batch)
    (g : Fin (R22Pair8.groups p)) (k : Fin n) (c : Fin 2) (hc : 2 * g.val + c.val < p) :
    R15ThinPairs.select ((R22Pair8.packB batch n p B).getD
      (b.val * n * R22Pair8.groups p + g.val + k.val * R22Pair8.groups p)
      R22Pair8.zeroPair) c.val =
      ExecFloat.Binary.toFloat32 (B.getD (b.val * n * p + 2 * g.val + c.val + k.val * p) posZero) := by
  have hb := Nat.mul_le_mul_right n b.isLt
  rw [Nat.succ_mul] at hb
  have hrow : b.val * n + k.val < batch * n := by have hk := k.isLt; omega
  have ha : b.val * n * R22Pair8.groups p + g.val + k.val * R22Pair8.groups p =
      (b.val * n + k.val) * R22Pair8.groups p + g.val := by
    rw [Nat.add_mul]
    omega
  rw [ha, packB_get batch n p B ⟨b.val * n + k.val, hrow⟩ g]
  have hcases : c.val = 0 ∨ c.val = 1 := by have hh := c.isLt; omega
  rcases hcases with he | he
  · simp only [he, R15ThinPairs.select, ↓reduceIte, Nat.add_zero, Nat.add_mul]
    congr 2
    omega
  · have hsecond : 2 * g.val + 1 < p := by simpa only [he] using hc
    simp only [he, R15ThinPairs.select, if_neg Nat.one_ne_zero, if_pos hsecond, Nat.add_mul]
    congr 2
    omega

end Submission.R23IndexedProducer
