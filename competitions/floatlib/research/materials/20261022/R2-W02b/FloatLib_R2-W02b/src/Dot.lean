namespace Packed4

open FloatLib.Floats Competition

/-- Mapping the input preserves the total read, including the positive-zero default. -/
theorem nativeA_getD (Araw : Array Binary32) (i : Nat) :
    (Araw.map ExecFloat.Binary.toFloat32).getD i zero32 =
      ExecFloat.Binary.toFloat32 (Araw.getD i posZero) := by
  by_cases hi : i < Araw.size
  · simp only [Array.getD, Array.size_map, dif_pos hi, Array.getElem_map]
  · simp only [Array.getD, Array.size_map, dif_neg hi] <;> rfl

/-- Four independent left folds share each input load from the left operand. -/
def dot4 (n baseA : Nat) (A : Array Float32) (B : Vector F4 n)
    (k : Nat) (s0 s1 s2 s3 : Float32) : F4 :=
  if hk : k < n then
    let sharedA := A.getD (baseA + k) zero32
    let v := B.get ⟨k, hk⟩
    dot4 n baseA A B (k + 1)
      (s0 + sharedA * v.s0)
      (s1 + sharedA * v.s1)
      (s2 + sharedA * v.s2)
      (s3 + sharedA * v.s3)
  else ⟨s0, s1, s2, s3⟩
termination_by n - k

/-- Each packed lane follows the corresponding scalar recurrence at every starting index. -/
theorem dot4_lane (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F4 n) (l : Fin 4)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero))
    (k : Nat) (s0 s1 s2 s3 : Float32) :
    lane (dot4 n baseA (Araw.map ExecFloat.Binary.toFloat32) B k s0 s1 s2 s3) l =
      NativeFinal.dotLoop n baseA baseB p Araw Braw k (lane ⟨s0, s1, s2, s3⟩ l) := by
  by_cases hk : k < n
  · rw [dot4, NativeFinal.dotLoop]
    simp only [dif_pos hk, if_pos hk]
    dsimp only
    have ih := dot4_lane n baseA baseB p Araw Braw B l hb (k + 1)
      (s0 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 *
        (B.get ⟨k, hk⟩).s0)
      (s1 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 *
        (B.get ⟨k, hk⟩).s1)
      (s2 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 *
        (B.get ⟨k, hk⟩).s2)
      (s3 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 *
        (B.get ⟨k, hk⟩).s3)
    have hacc :
        lane
          ⟨s0 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 *
              (B.get ⟨k, hk⟩).s0,
            s1 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 *
              (B.get ⟨k, hk⟩).s1,
            s2 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 *
              (B.get ⟨k, hk⟩).s2,
            s3 + (Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32 *
              (B.get ⟨k, hk⟩).s3⟩ l =
          lane ⟨s0, s1, s2, s3⟩ l +
            ExecFloat.Binary.toFloat32 (Araw.getD (baseA + k) posZero) *
              ExecFloat.Binary.toFloat32 (Braw.getD (baseB + k * p) posZero) := by
      change lane
        (update ⟨s0, s1, s2, s3⟩
          ((Araw.map ExecFloat.Binary.toFloat32).getD (baseA + k) zero32)
          (B.get ⟨k, hk⟩)) l = _
      rw [lane_update, nativeA_getD, hb ⟨k, hk⟩]
    rw [hacc] at ih
    exact ih
  · rw [dot4, NativeFinal.dotLoop]
    simp only [dif_neg hk, if_neg hk]
termination_by n - k

/-- The result guard and exact fallback are the same as in the scalar implementation. -/
def finish (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32) : Binary32 :=
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else Fin.foldl n
    (fun a i => Submission.add a
      (Submission.mul (Araw.getD (baseA + i.val) posZero)
        (Braw.getD (baseB + i.val * p) posZero))) posZero

theorem finish_eq_dot (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  rw [hs] <;> rfl

theorem finish_eq_fold (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      Fin.foldl n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (Araw.getD (baseA + i.val) posZero)
            (Braw.getD (baseB + i.val * p) posZero))) posZero := by
  rw [finish_eq_dot n baseA baseB p Araw Braw result hs, NativeFinal.dot_eq]

theorem finish_eq_kernel_fold (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      Fin.foldl n
        (fun a i => Submission.add a
          (Submission.mul (Araw.getD (baseA + i.val) posZero)
            (Braw.getD (baseB + i.val * p) posZero))) posZero := by
  rw [finish_eq_fold n baseA baseB p Araw Braw result hs]
  simp only [Submission.add_eq, Submission.mul_eq]

theorem finish_dot4_lane (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F4 n) (l : Fin 4)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero)) :
    finish n baseA baseB p Araw Braw
        (lane (dot4 n baseA (Araw.map ExecFloat.Binary.toFloat32) B 0
          zero32 zero32 zero32 zero32) l) =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  have hs := dot4_lane n baseA baseB p Araw Braw B l hb 0
    zero32 zero32 zero32 zero32
  have hz : lane (⟨zero32, zero32, zero32, zero32⟩ : F4) l = zero32 :=
    lane_zero4 l
  rw [hz] at hs
  exact finish_eq_dot n baseA baseB p Araw Braw _ hs

theorem finish_dot4_lane_fold (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector F4 n) (l : Fin 4)
    (hb : ∀ i : Fin n, lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero)) :
    finish n baseA baseB p Araw Braw
        (lane (dot4 n baseA (Araw.map ExecFloat.Binary.toFloat32) B 0
          zero32 zero32 zero32 zero32) l) =
      Fin.foldl n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (Araw.getD (baseA + i.val) posZero)
            (Braw.getD (baseB + i.val * p) posZero))) posZero := by
  rw [finish_dot4_lane n baseA baseB p Araw Braw B l hb, NativeFinal.dot_eq]

end Packed4
