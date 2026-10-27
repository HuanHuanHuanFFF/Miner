namespace NativeFold

@[inline] def step (acc : Float32) (x : Binary32) : Float32 :=
  acc + ExecFloat.Binary.toFloat32 x

theorem list_fold_finite (xs : List Binary32) (acc : Float32)
    (hf : (xs.foldl step acc).isFinite = true) :
    acc.isFinite = true ∧ ExecFloat.Binary.ofFloat32 (xs.foldl step acc) =
      xs.foldl ExecFloat.add (ExecFloat.Binary.ofFloat32 acc) := by
  induction xs generalizing acc with
  | nil => exact ⟨hf, rfl⟩
  | cons x xs ih =>
    change (xs.foldl step (step acc x)).isFinite = true at hf
    have hi := ih (step acc x) hf
    have ha := FinalFinite.add_finite_inputs acc (ExecFloat.Binary.toFloat32 x) hi.1
    refine ⟨ha.1, ?_⟩
    have hnext := hi.2
    simp only [step] at hnext
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ ha.1 ha.2,
      GuardBridge.finiteRoundtrip x ha.2] at hnext
    exact hnext

end NativeFold

def sum {n : Nat} (x : Vector Binary32 n) : Binary32 :=
  let result := x.foldl NativeFold.step (Float32.ofBits 0)
  if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
  else referenceSum x

theorem sum_spec : ∀ (n : Nat) (x : Vector Binary32 n), sum x = sumSpec x.get := by
  intro n x
  unfold sum
  dsimp only
  split
  · rename_i hf
    have hf' : (x.toList.foldl NativeFold.step (Float32.ofBits 0)).isFinite = true := by
      simpa only [Vector.foldl_toList] using hf
    have h := (NativeFold.list_fold_finite x.toList (Float32.ofBits 0) hf').2
    have heq : ExecFloat.Binary.ofFloat32
        (x.foldl NativeFold.step (Float32.ofBits 0)) = referenceSum x := by
      simpa only [referenceSum, add_eq, Vector.foldl_toList] using h
    exact heq.trans (referenceSum_spec n x)
  · exact referenceSum_spec n x
