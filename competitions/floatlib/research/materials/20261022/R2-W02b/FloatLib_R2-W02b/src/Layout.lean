namespace Packed4

structure F4 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32

@[inline] def zero32 : Float32 := Float32.ofBits 0

@[inline] def zero4 : F4 := ⟨zero32, zero32, zero32, zero32⟩

@[inline] def lane (v : F4) (l : Fin 4) : Float32 :=
  match l.val with
  | 0 => v.s0
  | 1 => v.s1
  | 2 => v.s2
  | _ => v.s3

@[inline] def packet (read : Nat → Float32) (col : Nat) : F4 :=
  ⟨read col, read (col + 1), read (col + 2), read (col + 3)⟩

@[inline] def update (acc : F4) (a : Float32) (v : F4) : F4 :=
  ⟨acc.s0 + a * v.s0, acc.s1 + a * v.s1,
    acc.s2 + a * v.s2, acc.s3 + a * v.s3⟩

theorem lane_packet (read : Nat → Float32) (col : Nat) (l : Fin 4) :
    lane (packet read col) l = read (col + l.val) := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;> rfl

theorem lane_zero4 (l : Fin 4) : lane zero4 l = zero32 := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;> rfl

theorem lane_zero (l : Fin 4) : lane zero4 l = zero32 :=
  lane_zero4 l

theorem lane_update (acc : F4) (a : Float32) (v : F4) (l : Fin 4) :
    lane (update acc a v) l = lane acc l + a * lane v l := by
  rcases l with ⟨l, hl⟩
  have h : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 := by omega
  rcases h with rfl | rfl | rfl | rfl <;> rfl

@[inline] def groups (p : Nat) : Nat := (p + 3) / 4

theorem groups_pos_of_col (p j : Nat) (hj : j < p) :
    j / 4 < groups p := by
  unfold groups
  omega

theorem column_decomposition (j : Nat) :
    4 * (j / 4) + j % 4 = j := by
  omega

theorem vector_get_ofFn {α : Type} {n : Nat}
    (f : Fin n → α) (i : Fin n) : (Vector.ofFn f).get i = f i := by
  change (Vector.ofFn f)[i.val]'i.isLt = f i
  exact Vector.getElem_ofFn i.isLt

def packB (batch n p : Nat) (B : Vector Binary32 (batch * n * p)) :
    Vector (Vector (Vector F4 n) (groups p)) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun g =>
      Vector.ofFn fun k =>
        packet (fun j =>
          if j < p then
            ExecFloat.Binary.toFloat32
              (B.toArray.getD ((b.val * n + k.val) * p + j) posZero)
          else zero32) (4 * g.val)

theorem packB_get (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (g : Fin (groups p)) (k : Fin n) :
    (((packB batch n p B).get b).get g).get k =
      packet (fun j =>
        if j < p then
          ExecFloat.Binary.toFloat32
            (B.toArray.getD ((b.val * n + k.val) * p + j) posZero)
        else zero32) (4 * g.val) := by
  simp only [packB, vector_get_ofFn]

theorem packB_lane (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (g : Fin (groups p)) (k : Fin n) (l : Fin 4)
    (hcol : 4 * g.val + l.val < p) :
    lane ((((packB batch n p B).get b).get g).get k) l =
      ExecFloat.Binary.toFloat32
        (B.toArray.getD
          ((b.val * n + k.val) * p + (4 * g.val + l.val)) posZero) := by
  rw [packB_get, lane_packet, if_pos hcol]

end Packed4
