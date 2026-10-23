/-- A flattened row is used only in the proof bridge, never in the new writer. -/
def batchRowIndex (batch m : Nat) (b : Fin batch) (i : Fin m) :
    Fin (batch * m) :=
  ⟨b.val * m + i.val, by
    have h := Nat.mul_le_mul_right m b.isLt
    rw [Nat.add_mul] at h
    omega⟩

/-- Both input batch bases are captured once; rows advance by the stride n. -/
@[inline] def batchRow (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (baseA baseB : Nat)
    (out : Array Binary32) (i : Fin m) : Array Binary32 :=
  RowStream.emit p (fun j =>
    NativeFinal.dot n (baseA + i.val * n) (baseB + j.val) p A.toArray B.toArray) out

theorem batchRow_eq_row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (out : Array Binary32) (i : Fin m) :
    batchRow batch m n p A B (b.val * m * n) (b.val * n * p) out i =
      row batch m n p A B out (batchRowIndex batch m b i) := by
  have hm : 0 < m := Nat.zero_lt_of_lt i.isLt
  have hdiv : (b.val * m + i.val) / m = b.val := by
    rw [Nat.mul_comm b.val m, Nat.mul_add_div hm, Nat.div_eq_of_lt i.isLt,
      Nat.add_zero]
  change RowStream.emit p (fun j =>
    NativeFinal.dot n (b.val * m * n + i.val * n) (b.val * n * p + j.val)
      p A.toArray B.toArray) out =
    RowStream.emit p (fun j =>
      NativeFinal.dot n ((b.val * m + i.val) * n)
        ((b.val * m + i.val) / m * n * p + j.val) p A.toArray B.toArray) out
  rw [hdiv, Nat.add_mul]

theorem batchRow_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (out : Array Binary32) (i : Fin m)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + i.val) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + i.val + 1) * p)
      (batchRow batch m n p A B (b.val * m * n) (b.val * n * p) out i) := by
  rw [batchRow_eq_row]
  exact row_prefix batch m n p A B out (batchRowIndex batch m b i) hout

/-- No division or preparation is performed in the nested direct writer. -/
def batchStep (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (out : Array Binary32) (b : Fin batch) : Array Binary32 :=
  let baseA := b.val * m * n
  let baseB := b.val * n * p
  Fin.foldl m (batchRow batch m n p A B baseA baseB) out

theorem batchStep_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (out : Array Binary32) (b : Fin batch)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (b.val * m * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (batchStep batch m n p A B out b) := by
  have h := RowStream.foldl_inv m
    (batchRow batch m n p A B (b.val * m * n) (b.val * n * p))
    (fun i acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + i) * p) acc)
    (fun i acc hacc => by
      simpa only [Nat.add_assoc] using batchRow_prefix batch m n p A B b acc i hacc)
    out (by simpa only [Nat.add_zero] using hout)
  simpa only [batchStep, Nat.add_mul, Nat.one_mul] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  Fin.foldl batch (batchStep batch m n p A B)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B) := by
  exact RowStream.foldl_inv batch (batchStep batch m n p A B)
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b * m * p) acc)
    (fun b acc hacc => batchStep_prefix batch m n p A B acc b hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

