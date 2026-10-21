
namespace NativeFinal

def sumLoop {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    sumLoop x (k + 1) (acc + ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩))
  else acc
termination_by n - k

theorem sumLoop_eq {n : Nat} (x : Vector Binary32 n) (k : Nat)
    (acc result : Float32) (hs : sumLoop x k acc = result)
    (hf : result.isFinite = true) :
    acc.isFinite = true ∧ ExecFloat.Binary.ofFloat32 result =
      Fin.foldl.loop n (fun a i => ExecFloat.add a (x.get i))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [sumLoop] at hs
  split at hs
  · rename_i hk
    have ih := sumLoop_eq x (k + 1)
      (acc + ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩)) result hs hf
    have ha := FinalFinite.add_finite_inputs acc
      (ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩)) ih.1
    refine ⟨ha.1, ?_⟩
    rw [Fin.foldl.loop, dif_pos hk]
    have hnext := ih.2
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ ha.1 ha.2,
      GuardBridge.finiteRoundtrip _ ha.2] at hnext
    exact hnext
  · rename_i hk
    refine ⟨?_, ?_⟩
    · simpa only [hs] using hf
    · rw [Fin.foldl.loop, dif_neg hk]
      exact congrArg ExecFloat.Binary.ofFloat32 hs.symm
termination_by n - k

def dotLoop (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Float32) : Float32 :=
  if hk : k < n then
    let fa := ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)
    let fb := ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)
    dotLoop n baseA baseB p A B (k + 1) (acc + fa * fb)
  else acc
termination_by n - k

theorem dotLoop_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc result : Float32)
    (hs : dotLoop n baseA baseB p A B k acc = result) (hf : result.isFinite = true) :
    acc.isFinite = true ∧ ExecFloat.Binary.ofFloat32 result =
      Fin.foldl.loop n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (A.getD (baseA + i.val) posZero)
            (B.getD (baseB + i.val * p) posZero)))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [dotLoop] at hs
  split at hs
  · rename_i hk
    dsimp only at hs
    have ih := dotLoop_eq n baseA baseB p A B (k + 1)
      (acc + ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) result hs hf
    have ha := FinalFinite.add_finite_inputs acc
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) ih.1
    have hm := FinalFinite.mul_finite_inputs
      (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero))
      (ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) ha.2
    refine ⟨ha.1, ?_⟩
    rw [Fin.foldl.loop, dif_pos hk]
    have hnext := ih.2
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ ha.1 ha.2,
      NativeBridge.ofFloat32Mul _ _ hm.1 hm.2,
      GuardBridge.finiteRoundtrip _ hm.1, GuardBridge.finiteRoundtrip _ hm.2] at hnext
    exact hnext
  · rename_i hk
    refine ⟨?_, ?_⟩
    · simpa only [hs] using hf
    · rw [Fin.foldl.loop, dif_neg hk]
      exact congrArg ExecFloat.Binary.ofFloat32 hs.symm
termination_by n - k

def dot (n baseA baseB p : Nat) (A B : Array Binary32) : Binary32 :=
  let result := dotLoop n baseA baseB p A B 0 (Float32.ofBits 0)
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else Fin.foldl n
    (fun a i => add a (mul (A.getD (baseA + i.val) posZero)
      (B.getD (baseB + i.val * p) posZero))) posZero

theorem dot_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    dot n baseA baseB p A B = Fin.foldl n
      (fun a i => ExecFloat.add a (ExecFloat.mul (A.getD (baseA + i.val) posZero)
        (B.getD (baseB + i.val * p) posZero))) posZero := by
  unfold dot
  dsimp only
  split
  · rename_i hf
    have h := (dotLoop_eq n baseA baseB p A B 0 (Float32.ofBits 0) _ rfl hf).2
    change ExecFloat.Binary.ofFloat32 _ = Fin.foldl n _ posZero at h
    exact h
  · simp only [add_eq, mul_eq]

end NativeFinal

def sum {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  let result := NativeFinal.sumLoop x 0 (Float32.ofBits 0)
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else referenceSum x

theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := by
  intro n x
  unfold sum
  dsimp only
  split
  · rename_i hf
    have h := (NativeFinal.sumLoop_eq x 0 (Float32.ofBits 0) _ rfl hf).2
    change ExecFloat.Binary.ofFloat32 _ = Fin.foldl n _ posZero at h
    rw [Fin.foldl_eq_finRange_foldl] at h
    exact h
  · exact referenceSum_spec n x

theorem index_address (a b c d : Nat) : (a + b) * c + d = (a * c + d) + b * c := by
  rw [Nat.add_mul]
  omega

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    NativeFinal.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = referenceBmm batch m n p A B := by
    unfold bmm referenceBmm
    apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
    funext q
    dsimp only
    rw [NativeFinal.dot_eq]
    simp only [add_eq, mul_eq]
    apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
    funext acc k
    have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
      (bmmDecodeC m p q.val).2.2
    rw [hi]
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceBmm_spec batch m n p A B)
