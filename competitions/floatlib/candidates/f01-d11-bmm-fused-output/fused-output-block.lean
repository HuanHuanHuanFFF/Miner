namespace Submission.RowStream

open FloatLib.Floats Competition

/-- A growing output array contains exactly the reference prefix. -/
def Prefix (f : Nat → Binary32) (k : Nat) (out : Array Binary32) : Prop :=
  out.size = k ∧ ∀ j (hj : j < out.size), out[j] = f j

theorem prefix_push (f : Nat → Binary32) (k : Nat) (out : Array Binary32)
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

/-- The ordinary finite left fold preserves an indexed invariant. -/
theorem foldl_loop_inv {β : Type} (count : Nat) (step : β → Fin count → β)
    (P : Nat → β → Prop)
    (hstep : ∀ (i : Fin count) (x : β), P i.val x → P (i.val + 1) (step x i))
    (k : Nat) (hk : k ≤ count) (x : β) (hx : P k x) :
    P count (Fin.foldl.loop count step x k) := by
  by_cases hi : k < count
  · rw [Fin.foldl.loop, dif_pos hi]
    exact foldl_loop_inv count step P hstep (k + 1) (by omega)
      (step x ⟨k, hi⟩) (hstep ⟨k, hi⟩ x hx)
  · have he : k = count := by omega
    subst k
    rw [Fin.foldl.loop, dif_neg (Nat.lt_irrefl count)]
    exact hx
termination_by count - k

theorem foldl_inv {β : Type} (count : Nat) (step : β → Fin count → β)
    (P : Nat → β → Prop)
    (hstep : ∀ (i : Fin count) (x : β), P i.val x → P (i.val + 1) (step x i))
    (x : β) (hx : P 0 x) : P count (Fin.foldl count step x) := by
  exact foldl_loop_inv count step P hstep 0 (Nat.zero_le count) x hx

/-- Emit directly into the caller's array; no lane or row array is built. -/
@[inline] def emit (count : Nat) (read : Fin count → Binary32)
    (out : Array Binary32) : Array Binary32 :=
  Fin.foldl count (fun acc l => acc.push (read l)) out

theorem emit_prefix (f : Nat → Binary32) (k count : Nat)
    (read : Fin count → Binary32) (out : Array Binary32)
    (hout : Prefix f k out) (hread : ∀ l, read l = f (k + l.val)) :
    Prefix f (k + count) (emit count read out) := by
  apply foldl_inv count (fun acc l => acc.push (read l))
    (fun i acc => Prefix f (k + i) acc)
  · intro l acc hacc
    rw [hread l]
    simpa only [Nat.add_assoc] using prefix_push f (k + l.val) acc hacc
  · simpa only [Nat.add_zero] using hout

def point (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (q : Nat) : Binary32 :=
  let (b, i, j) := bmmDecodeC m p q
  NativeFinal.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray

theorem decode_row (m p r j : Nat) (hm : 0 < m) (hp : 0 < p) (hj : j < p) :
    bmmDecodeC m p (r * p + j) = (r / m, r % m, j) := by
  have hmp : m * p ≠ 0 := Nat.ne_of_gt (Nat.mul_pos hm hp)
  have hp0 : p ≠ 0 := Nat.ne_of_gt hp
  have hd : (r * p + j) / p = r := by
    rw [Nat.mul_comm r p, Nat.mul_add_div hp, Nat.div_eq_of_lt hj, Nat.add_zero]
  have hb : (r * p + j) / (m * p) = r / m := by
    rw [Nat.mul_comm m p, ← Nat.div_div_eq_div_mul, hd]
  simp only [bmmDecodeC, hmp, hp0, if_false, hb,
    Nat.mod_mul_left_div_self, Nat.mod_mul_left_mod, hd,
    Nat.mul_add_mod_of_lt hj]

theorem point_row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (r j : Nat)
    (hm : 0 < m) (hp : 0 < p) (hj : j < p) :
    point batch m n p A B (r * p + j) =
      NativeFinal.dot n (r * n) (r / m * n * p + j) p A.toArray B.toArray := by
  simp only [point, decode_row m p r j hm hp hj, Nat.div_add_mod']

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (Packed10.groups p)) :
    Array Binary32 :=
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  let b : Fin batch := ⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let result := Packed10Index.runDot n (r.val * n) nativeA ((packedB.get b).get g)
  let count := min 10 (p - 10 * g.val)
  emit count (fun l =>
    let j := 10 * g.val + l.val
    Packed10.finish n (r.val * n) (b.val * n * p + j) p A.toArray B.toArray
      (Packed10.lane result ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩)) out

theorem group_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (r : Fin (batch * m))
    (g : Fin (Packed10.groups p)) (out : Array Binary32)
    (hout : Prefix (point batch m n p A B) (r.val * p + min (10 * g.val) p) out) :
    Prefix (point batch m n p A B) (r.val * p + min (10 * (g.val + 1)) p)
      (group batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) r out g) := by
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  have hg : 10 * g.val < p := by
    have h := g.isLt
    unfold Packed10.groups at h
    omega
  have hp : 0 < p := by omega
  have hstart : min (10 * g.val) p = 10 * g.val := by omega
  have hend : r.val * p + min (10 * (g.val + 1)) p =
      (r.val * p + 10 * g.val) + min 10 (p - 10 * g.val) := by omega
  rw [hend]
  unfold group
  dsimp only
  apply emit_prefix
  · simpa only [hstart] using hout
  · intro l
    have hcol : 10 * g.val + l.val < p := by
      have hl := l.isLt
      omega
    rw [show r.val * p + 10 * g.val + l.val =
      r.val * p + (10 * g.val + l.val) by omega,
      point_row batch m n p A B r.val (10 * g.val + l.val) hm hp hcol,
      Packed10Index.runDot_eq]
    apply Packed10.finish_dot10_lane
    intro k
    rw [Packed10.packB_lane batch n p B
      ⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩ g k
      ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩ hcol]
    rw [index_address (r.val / m * n) k.val p (10 * g.val + l.val)]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  Fin.foldl (Packed10.groups p) (group batch m n p A B nativeA packedB r) out

theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (r : Fin (batch * m)) (out : Array Binary32)
    (hout : Prefix (point batch m n p A B) (r.val * p) out) :
    Prefix (point batch m n p A B) ((r.val + 1) * p)
      (row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) out r) := by
  have hlast : min (10 * Packed10.groups p) p = p := by
    unfold Packed10.groups
    omega
  have h := foldl_inv (Packed10.groups p)
    (group batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B) r)
    (fun g acc => Prefix (point batch m n p A B) (r.val * p + min (10 * g) p) acc)
    (fun g acc hacc => group_prefix batch m n p A B r g acc hacc) out
    (by simpa only [Nat.mul_zero, Nat.zero_min, Nat.add_zero] using hout)
  simpa only [row, hlast, Nat.add_mul, Nat.one_mul] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  Fin.foldl (batch * m) (row batch m n p A B nativeA packedB)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    Prefix (point batch m n p A B) (batch * m * p) (output batch m n p A B) := by
  exact foldl_inv (batch * m)
    (row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B))
    (fun r acc => Prefix (point batch m n p A B) (r * p) acc)
    (fun r acc hacc => row_prefix batch m n p A B r acc hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  apply Vector.ext
  intro q hq
  change (output batch m n p A B)[q] = _
  rw [(output_prefix batch m n p A B).2 q (by
    rw [(output_prefix batch m n p A B).1]
    exact hq)]
  simp only [referenceBmm, Vector.getElem_ofFn, point]
  rw [NativeFinal.dot_eq]
  simp only [add_eq, mul_eq]
  apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
  funext acc k
  rw [index_address ((bmmDecodeC m p q).1 * n) k.val p
    (bmmDecodeC m p q).2.2]

theorem core_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = Packed10.core batch m n p A B := by
  exact (core_eq_reference batch m n p A B).trans
    (Packed10.core_eq_reference batch m n p A B).symm

end Submission.RowStream
