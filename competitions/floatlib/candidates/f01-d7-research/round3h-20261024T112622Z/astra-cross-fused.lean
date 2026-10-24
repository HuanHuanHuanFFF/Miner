/- R13: emit each existing CrossRows block into the final array. Input packing,
   ordered Float32 recurrence, finish8 and raw NaN replay stay unchanged. -/
namespace Submission.R13CrossFused
open FloatLib.Floats Competition
open RowStream (Prefix prefix_push)

@[inline] def pushPair (out : Array Binary32) (a b : UInt32) : Array Binary32 :=
  (out.push (ExecFloat.Binary.ofBits32 a)).push (ExecFloat.Binary.ofBits32 b)

theorem pushPair_prefix (f : Nat → Binary32) (k : Nat) (out : Array Binary32)
    (a b : UInt32) (hout : Prefix f k out)
    (ha : ExecFloat.Binary.ofBits32 a = f k)
    (hb : ExecFloat.Binary.ofBits32 b = f (k + 1)) :
    Prefix f (k + 1 + 1) (pushPair out a b) := by
  rw [pushPair, ha, hb]
  exact prefix_push f (k + 1) (out.push (f k)) (prefix_push f k out hout)

/-- Proof-facing row step; the runtime block below uses the eight fields directly. -/
def emitRow (rows g : Nat) (w : R11CrossRows.W8) (out : Array Binary32)
    (i : Fin 4) : Array Binary32 :=
  if 4 * g + i.val < rows then
    pushPair out (R11CrossRows.wordAt w i ⟨0, by decide⟩)
      (R11CrossRows.wordAt w i ⟨1, by decide⟩)
  else out

@[inline] def emitBlock (rows g : Nat) (w : R11CrossRows.W8)
    (out : Array Binary32) : Array Binary32 :=
  let o0 := if 4 * g < rows then pushPair out w.w0 w.w1 else out
  let o1 := if 4 * g + 1 < rows then pushPair o0 w.w2 w.w3 else o0
  let o2 := if 4 * g + 2 < rows then pushPair o1 w.w4 w.w5 else o1
  if 4 * g + 3 < rows then pushPair o2 w.w6 w.w7 else o2

theorem emitBlock_eq (rows g : Nat) (w : R11CrossRows.W8) (out : Array Binary32) :
    emitBlock rows g w out =
      emitRow rows g w
        (emitRow rows g w
          (emitRow rows g w (emitRow rows g w out ⟨0, by decide⟩) ⟨1, by decide⟩)
          ⟨2, by decide⟩) ⟨3, by decide⟩ := by
  rfl

theorem word_point (batch m n p g : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) (hp : p = 2)
    (i : Fin 4) (j : Fin 2) (hr : 4 * g + i.val < batch * m) :
    ExecFloat.Binary.ofBits32
      (R11CrossRows.wordAt (R11CrossRows.blockRows m n p g A.toArray B.toArray hn) i j) =
      RowStream.point batch m n p A B ((4 * g + i.val) * p + j.val) := by
  rw [R11CrossRows.blockRows_word]
  have hm : 0 < m := Nat.pos_of_lt_mul_left hr
  have hp0 : 0 < p := by omega
  have hj : j.val < p := by rw [hp]; exact j.isLt
  exact (RowStream.point_row batch m n p A B (4 * g + i.val) j.val hm hp0 hj).symm

theorem emitRow_prefix (batch m n p g : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) (hp : p = 2)
    (out : Array Binary32) (i : Fin 4)
    (hout : Prefix (RowStream.point batch m n p A B)
      (min (4 * g + i.val) (batch * m) * p) out) :
    Prefix (RowStream.point batch m n p A B)
      (min (4 * g + i.val + 1) (batch * m) * p)
      (emitRow (batch * m) g
        (R11CrossRows.blockRows m n p g A.toArray B.toArray hn) out i) := by
  by_cases hr : 4 * g + i.val < batch * m
  · have hmin : min (4 * g + i.val) (batch * m) = 4 * g + i.val :=
      Nat.min_eq_left (Nat.le_of_lt hr)
    have hmin' : min (4 * g + i.val + 1) (batch * m) = 4 * g + i.val + 1 :=
      Nat.min_eq_left (by omega)
    rw [hmin] at hout
    rw [emitRow, if_pos hr, hmin']
    have ha := word_point batch m n p g A B hn hp i ⟨0, by decide⟩ hr
    have hb := word_point batch m n p g A B hn hp i ⟨1, by decide⟩ hr
    have h := pushPair_prefix (RowStream.point batch m n p A B)
      ((4 * g + i.val) * p) out _ _ hout
      (by simpa only [Nat.add_zero] using ha) hb
    have hlen : (4 * g + i.val + 1) * p = (4 * g + i.val) * p + 1 + 1 := by
      rw [hp]
      omega
    rw [hlen]
    exact h
  · have hmin : min (4 * g + i.val) (batch * m) = batch * m :=
      Nat.min_eq_right (by omega)
    have hmin' : min (4 * g + i.val + 1) (batch * m) = batch * m :=
      Nat.min_eq_right (by omega)
    simpa only [emitRow, if_neg hr, hmin, hmin'] using hout

theorem emitBlock_prefix (batch m n p g : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) (hp : p = 2)
    (out : Array Binary32)
    (hout : Prefix (RowStream.point batch m n p A B)
      (min (4 * g) (batch * m) * p) out) :
    Prefix (RowStream.point batch m n p A B)
      (min (4 * (g + 1)) (batch * m) * p)
      (emitBlock (batch * m) g
        (R11CrossRows.blockRows m n p g A.toArray B.toArray hn) out) := by
  have h0 := emitRow_prefix batch m n p g A B hn hp out ⟨0, by decide⟩ hout
  have h1 := emitRow_prefix batch m n p g A B hn hp _ ⟨1, by decide⟩ h0
  have h2 := emitRow_prefix batch m n p g A B hn hp _ ⟨2, by decide⟩ h1
  have h3 := emitRow_prefix batch m n p g A B hn hp _ ⟨3, by decide⟩ h2
  have hend : 4 * g + 3 + 1 = 4 * (g + 1) := by omega
  simpa only [emitBlock_eq, hend] using h3

@[inline] def step (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size)
    (out : Array Binary32) (g : Fin (R11CrossRows.groups (batch * m))) : Array Binary32 :=
  let w := R11CrossRows.blockRows m n p g.val A.toArray B.toArray hn
  emitBlock (batch * m) g.val w out

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) : Array Binary32 :=
  Fin.foldl (R11CrossRows.groups (batch * m)) (step batch m n p A B hn)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) (hp : p = 2) :
    Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B hn) := by
  have hlast : min (4 * R11CrossRows.groups (batch * m)) (batch * m) = batch * m := by
    unfold R11CrossRows.groups
    omega
  have h := RowStream.foldl_inv (R11CrossRows.groups (batch * m))
    (step batch m n p A B hn)
    (fun g acc => Prefix (RowStream.point batch m n p A B)
      (min (4 * g) (batch * m) * p) acc)
    (fun g acc hacc => emitBlock_prefix batch m n p g.val A B hn hp acc hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩
  simpa only [output, hlast] using h

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) (hp : p = 2) :
    Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B hn, (output_prefix batch m n p A B hn hp).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) (hp : p = 2) :
    core batch m n p A B hn hp = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B hn) (output_prefix batch m n p A B hn hp)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.R13CrossFused
