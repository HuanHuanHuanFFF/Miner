namespace CheckedFloatArray

@[inline] def encode (x : Binary32) : Float :=
  (ExecFloat.Binary.toFloat32 x).toFloat

def prepare (xs : Array Binary32) : FloatArray :=
  ⟨xs.map encode⟩

@[inline] def checkOne (x : Binary32) : Bool :=
  (ExecFloat.Binary.ofFloat32 (encode x).toFloat32).raw.1 == x.raw.1

def check (xs : Array Binary32) : Bool := xs.all checkOne

theorem checkOne_eq (x : Binary32) (h : checkOne x = true) :
    ExecFloat.Binary.ofFloat32 (encode x).toFloat32 = x := by
  apply ExecFloat.ext
  apply Subtype.ext
  simpa only [checkOne, beq_iff_eq] using h

@[inline] def read (xs : FloatArray) (i : Nat) : Float32 :=
  if hi : i < xs.size then (xs.get i hi).toFloat32
  else Float32.ofBits 0

theorem read_prepare_eq (xs : Array Binary32) (h : check xs = true) (i : Nat) :
    ExecFloat.Binary.ofFloat32 (read (prepare xs) i) = xs.getD i posZero := by
  have hall : xs.all checkOne = true := h
  by_cases hi : i < xs.size
  · have hone := (Array.all_eq_true.mp hall) i hi
    have heq := checkOne_eq xs[i] hone
    simpa [read, prepare, FloatArray.size, FloatArray.get, Array.getD, hi] using heq
  · simp [read, prepare, FloatArray.size, FloatArray.get, Array.getD, hi] <;> rfl

def dotLoop (n baseA baseB p : Nat) (AF BF : FloatArray)
    (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    dotLoop n baseA baseB p AF BF (k + 1)
      (acc + read AF (baseA + k) * read BF (baseB + k * p))
  else acc
termination_by n - k

theorem dotLoop_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (AF BF : FloatArray)
    (hA : ∀ i, ExecFloat.Binary.ofFloat32 (read AF i) = A.getD i posZero)
    (hB : ∀ i, ExecFloat.Binary.ofFloat32 (read BF i) = B.getD i posZero)
    (k : Nat) (acc result : Float32)
    (hs : dotLoop n baseA baseB p AF BF k acc = result)
    (hf : result.isFinite = true) :
    acc.isFinite = true ∧ ExecFloat.Binary.ofFloat32 result =
      Fin.foldl.loop n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (A.getD (baseA + i.val) posZero)
            (B.getD (baseB + i.val * p) posZero)))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [dotLoop] at hs
  split at hs
  · rename_i hk
    have ih := dotLoop_eq n baseA baseB p A B AF BF hA hB (k + 1)
      (acc + read AF (baseA + k) * read BF (baseB + k * p)) result hs hf
    have ha := FinalFinite.add_finite_inputs acc
      (read AF (baseA + k) * read BF (baseB + k * p)) ih.1
    have hm := FinalFinite.mul_finite_inputs
      (read AF (baseA + k)) (read BF (baseB + k * p)) ha.2
    refine ⟨ha.1, ?_⟩
    rw [Fin.foldl.loop, dif_pos hk]
    have hnext := ih.2
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ ha.1 ha.2,
      NativeBridge.ofFloat32Mul _ _ hm.1 hm.2,
      hA (baseA + k), hB (baseB + k * p)] at hnext
    exact hnext
  · rename_i hk
    refine ⟨?_, ?_⟩
    · simpa only [hs] using hf
    · rw [Fin.foldl.loop, dif_neg hk]
      exact congrArg ExecFloat.Binary.ofFloat32 hs.symm
termination_by n - k

def dot (n baseA baseB p : Nat) (A B : Array Binary32)
    (AF BF : FloatArray) : Binary32 :=
  let result := dotLoop n baseA baseB p AF BF 0 (Float32.ofBits 0)
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else Fin.foldl n
    (fun a i => add a (mul (A.getD (baseA + i.val) posZero)
      (B.getD (baseB + i.val * p) posZero))) posZero

theorem dot_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (AF BF : FloatArray)
    (hA : ∀ i, ExecFloat.Binary.ofFloat32 (read AF i) = A.getD i posZero)
    (hB : ∀ i, ExecFloat.Binary.ofFloat32 (read BF i) = B.getD i posZero) :
    dot n baseA baseB p A B AF BF = Fin.foldl n
      (fun a i => ExecFloat.add a (ExecFloat.mul (A.getD (baseA + i.val) posZero)
        (B.getD (baseB + i.val * p) posZero))) posZero := by
  unfold dot
  dsimp only
  split
  · rename_i hf
    have h := (dotLoop_eq n baseA baseB p A B AF BF hA hB
      0 (Float32.ofBits 0) _ rfl hf).2
    change ExecFloat.Binary.ofFloat32 _ = Fin.foldl n _ posZero at h
    exact h
  · simp only [add_eq, mul_eq]

end CheckedFloatArray

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if hValid : CheckedFloatArray.check A.toArray = true ∧
      CheckedFloatArray.check B.toArray = true then
    let AF := CheckedFloatArray.prepare A.toArray
    let BF := CheckedFloatArray.prepare B.toArray
    Vector.ofFn fun q =>
      let (b, i, j) := bmmDecodeC m p q.val
      CheckedFloatArray.dot n ((b * m + i) * n) (b * n * p + j) p
        A.toArray B.toArray AF BF
  else originalBmm batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rename_i hValid
    have hA := CheckedFloatArray.read_prepare_eq A.toArray hValid.1
    have hB := CheckedFloatArray.read_prepare_eq B.toArray hValid.2
    have heq : (Vector.ofFn fun q : Fin (batch * m * p) =>
        let (b, i, j) := bmmDecodeC m p q.val
        CheckedFloatArray.dot n ((b * m + i) * n) (b * n * p + j) p
          A.toArray B.toArray (CheckedFloatArray.prepare A.toArray)
            (CheckedFloatArray.prepare B.toArray)) = referenceBmm batch m n p A B := by
      unfold referenceBmm
      apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
      funext q
      dsimp only
      rw [CheckedFloatArray.dot_eq _ _ _ _ _ _ _ _ hA hB]
      simp only [add_eq, mul_eq]
      apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
      funext acc k
      have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
        (bmmDecodeC m p q.val).2.2
      rw [hi]
    exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) heq).trans
      (referenceBmm_spec batch m n p A B)
  · exact originalBmm_spec batch m n p A B
