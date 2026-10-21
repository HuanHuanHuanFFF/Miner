-- Integration fragment only; requires the original referenceSum/referenceSum_spec.
-- Not compiled. Keep outside candidate packages until native-add feasibility is resolved.

namespace NativeTensor

open FloatLib.Floats Competition

def sumTry {n : Nat} (x : Vector Binary32 n) (k : Nat) (acc : Float32) : Option Float32 :=
  if hk : k < n then
    let v := x.get ⟨k, hk⟩
    let fv := ExecFloat.Binary.toFloat32 v
    if hf : acc.isFinite = true ∧ fv.isFinite = true then
      if hw : (ExecFloat.Binary.ofFloat32 fv).raw.1 = v.raw.1 then
        sumTry x (k + 1) (acc + fv)
      else none
    else none
  else some acc
termination_by n - k

theorem sumTry_eq {n : Nat} (x : Vector Binary32 n) (k : Nat)
    (acc result : Float32) (hs : sumTry x k acc = some result) :
    ExecFloat.Binary.ofFloat32 result =
      Fin.foldl.loop n (fun a i => ExecFloat.add a (x.get i))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [sumTry] at hs
  split at hs
  · rename_i hk
    dsimp only at hs
    split at hs
    · rename_i hf
      split at hs
      · rename_i hw
        have hv : ExecFloat.Binary.ofFloat32
            (ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩)) = x.get ⟨k, hk⟩ := by
          apply ExecFloat.ext
          apply Subtype.ext
          exact hw
        rw [Fin.foldl.loop, dif_pos hk]
        have hnext := sumTry_eq x (k + 1)
          (acc + ExecFloat.Binary.toFloat32 (x.get ⟨k, hk⟩)) result hs
        rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ hf.1 hf.2, hv] at hnext
        exact hnext
      · cases hs
    · cases hs
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
    exact congrArg ExecFloat.Binary.ofFloat32 (Option.some.inj hs).symm
termination_by n - k

end NativeTensor

def sum {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  match NativeTensor.sumTry x 0 (Float32.ofBits 0) with
  | some result => ExecFloat.Binary.ofFloat32 result
  | none => referenceSum x

theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := by
  intro n x
  unfold sum
  cases hs : NativeTensor.sumTry x 0 (Float32.ofBits 0) with
  | none => exact referenceSum_spec n x
  | some result =>
    have h := NativeTensor.sumTry_eq x 0 (Float32.ofBits 0) result hs
    change ExecFloat.Binary.ofFloat32 result =
      Fin.foldl n (fun a i => ExecFloat.add a (x.get i)) posZero at h
    rw [Fin.foldl_eq_finRange_foldl] at h
    exact h
