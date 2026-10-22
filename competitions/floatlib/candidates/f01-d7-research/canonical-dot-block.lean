/- New actual-loop refinement. All new declarations are NOT_RUN. -/
open FloatLib.Floats.Formats.BinaryInterchange

theorem raw_nonNaN_native_nonNaN (q : Binary32)
    (h : Model.isNaN (Model.NativeBinary32.ofUInt32 q.raw.1) = false) :
    (ExecFloat.Binary.toFloat32 q).isNaN = false := by
  rw [R7W05.toFloat32_isNaN, DWordNaN.exec_toModel_eq_rawModel]
  exact h

/- The native seed is arbitrary. Each original raw operand must be non-NaN;
the accumulated native state and final native result may already be NaNs. -/
theorem dotLoop_eq_of_whole_nonNaN
    (n baseA baseB p : Nat) (A B : Array Binary32) (k : Nat) (acc : Float32)
    (hscan : DDotNonNaNScan.whole n baseA baseB p A B = true) :
    ExecFloat.Binary.ofFloat32 (dotLoop n baseA baseB p A B k acc) =
      Fin.foldl.loop n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (A.getD (baseA + i.val) posZero)
            (B.getD (baseB + i.val * p) posZero)))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [dotLoop]
  split
  · rename_i hk
    dsimp only
    have hraw := DDotNonNaNScan.whole_model_nonNaN n baseA baseB p A B hscan ⟨k, hk⟩
    have ha := raw_nonNaN_native_nonNaN (A.getD (baseA + k) posZero) hraw.1
    have hb := raw_nonNaN_native_nonNaN (B.getD (baseB + k * p) posZero) hraw.2
    have ih := dotLoop_eq_of_whole_nonNaN n baseA baseB p A B (k + 1)
      (acc + ExecFloat.Binary.toFloat32 (A.getD (baseA + k) posZero) *
        ExecFloat.Binary.toFloat32 (B.getD (baseB + k * p) posZero)) hscan
    rw [R7W12.ofFloat32_add, R7W12.ofFloat32_mul,
      NotNaNProbe.roundtrip _ ha, NotNaNProbe.roundtrip _ hb] at ih
    rw [Fin.foldl.loop, dif_pos hk]
    exact ih
  · rename_i hk
    rw [Fin.foldl.loop, dif_neg hk]
termination_by n - k
decreasing_by omega

/- Only the actual original positive-zero initial state is used by this bridge.
It establishes carrier equality, without asserting that the output is a NaN. -/
theorem dot_eq_of_whole_nonNaN
    (n baseA baseB p : Nat) (A B : Array Binary32)
    (hscan : DDotNonNaNScan.whole n baseA baseB p A B = true) :
    ExecFloat.Binary.ofFloat32 (dotLoop n baseA baseB p A B 0 (Float32.ofBits 0)) =
      Fin.foldl n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (A.getD (baseA + i.val) posZero)
            (B.getD (baseB + i.val * p) posZero))) posZero := by
  have h := dotLoop_eq_of_whole_nonNaN n baseA baseB p A B 0 (Float32.ofBits 0) hscan
  change ExecFloat.Binary.ofFloat32 _ = Fin.foldl n _ posZero at h
  exact h
