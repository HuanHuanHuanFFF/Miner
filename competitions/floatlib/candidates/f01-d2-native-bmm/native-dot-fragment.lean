
namespace NativeTensor

/-- Float32 accumulator, preserving each multiplication and addition separately. -/
def dotTry (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc : Float32) : Option Float32 :=
  if hk : k < n then
    let a := A.getD (baseA + k) posZero
    let b := B.getD (baseB + k * p) posZero
    let fa := ExecFloat.Binary.toFloat32 a
    let fb := ExecFloat.Binary.toFloat32 b
    if hf : fa.isFinite = true ∧ fb.isFinite = true ∧ acc.isFinite = true then
      if hw : (ExecFloat.Binary.ofFloat32 fa).raw.1 = a.raw.1 ∧
          (ExecFloat.Binary.ofFloat32 fb).raw.1 = b.raw.1 then
        let prod := fa * fb
        if hp : prod.isFinite = true then
          dotTry n baseA baseB p A B (k + 1) (acc + prod)
        else none
      else none
    else none
  else some acc
termination_by n - k

theorem dotTry_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (k : Nat) (acc result : Float32)
    (hs : dotTry n baseA baseB p A B k acc = some result) :
    ExecFloat.Binary.ofFloat32 result =
      Fin.foldl.loop n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (A.getD (baseA + i.val) posZero)
            (B.getD (baseB + i.val * p) posZero)))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [dotTry] at hs
  split at hs
  · rename_i hk
    dsimp only at hs
    split at hs
    · rename_i hf
      split at hs
      · rename_i hw
        split at hs
        · rename_i hp
          have ha : ExecFloat.Binary.ofFloat32
              (ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero)) =
              A.getD (baseA + k) posZero := by
            apply ExecFloat.ext
            apply Subtype.ext
            exact hw.1
          have hb : ExecFloat.Binary.ofFloat32
              (ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) =
              B.getD (baseB + k * p) posZero := by
            apply ExecFloat.ext
            apply Subtype.ext
            exact hw.2
          rw [Fin.foldl.loop, dif_pos hk]
          have hnext := dotTry_eq n baseA baseB p A B (k + 1)
            (acc + ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
              ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) result hs
          rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ hf.2.2 hp,
            NativeBridge.ofFloat32Mul _ _ hf.1 hf.2.1, ha, hb] at hnext
          exact hnext
        · cases hs
      · cases hs
    · cases hs
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
    exact congrArg ExecFloat.Binary.ofFloat32 (Option.some.inj hs).symm
termination_by n - k

def dot (n baseA baseB p : Nat) (A B : Array Binary32) : Binary32 :=
  match dotTry n baseA baseB p A B 0 (Float32.ofBits 0) with
  | some result => ExecFloat.Binary.ofFloat32 result
  | none => Fin.foldl n
      (fun a i => add a (mul (A.getD (baseA + i.val) posZero)
        (B.getD (baseB + i.val * p) posZero))) posZero

theorem dot_eq (n baseA baseB p : Nat) (A B : Array Binary32) :
    dot n baseA baseB p A B = Fin.foldl n
      (fun a i => ExecFloat.add a (ExecFloat.mul (A.getD (baseA + i.val) posZero)
        (B.getD (baseB + i.val * p) posZero))) posZero := by
  unfold dot
  cases hs : dotTry n baseA baseB p A B 0 (Float32.ofBits 0) with
  | none => simp only [add_eq, mul_eq]
  | some result =>
    have h := dotTry_eq n baseA baseB p A B 0 (Float32.ofBits 0) result hs
    change ExecFloat.Binary.ofFloat32 result = Fin.foldl n _ posZero at h
    exact h

end NativeTensor

theorem index_address (a b c d : Nat) : (a + b) * c + d = (a * c + d) + b * c := by
  rw [Nat.add_mul]
  omega

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  Vector.ofFn fun q =>
    let (b, i, j) := bmmDecodeC m p q.val
    NativeTensor.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = referenceBmm batch m n p A B := by
    unfold bmm referenceBmm
    apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
    funext q
    dsimp only
    rw [NativeTensor.dot_eq]
    simp only [add_eq, mul_eq]
    apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
    funext acc k
    have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
      (bmmDecodeC m p q.val).2.2
    rw [hi]
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceBmm_spec batch m n p A B)
