/- Actual-loop interface using W12 closure already present in current B2.
   This does not reprove W12 or claim a public candidate. NOT_RUN. -/
namespace Submission.R22DotImage
open FloatLib.Floats Competition

theorem dotLoop_image_of_reads
    (n baseA baseB p : Nat) (A B : Array Binary32)
    (ha : ∀ i : Fin n,
      (ExecFloat.Binary.toFloat32 (A.getD (baseA+i.val) posZero)).isNaN = false)
    (hb : ∀ i : Fin n,
      (ExecFloat.Binary.toFloat32 (B.getD (baseB+i.val*p) posZero)).isNaN = false)
    (k : Nat) (acc : Float32) :
    ExecFloat.Binary.ofFloat32 (NativeFinal.dotLoop n baseA baseB p A B k acc) =
      Fin.foldl.loop n
        (fun a i => ExecFloat.add a
          (ExecFloat.mul (A.getD (baseA+i.val) posZero)
            (B.getD (baseB+i.val*p) posZero)))
        (ExecFloat.Binary.ofFloat32 acc) k := by
  rw [NativeFinal.dotLoop]
  split
  · rename_i hk
    dsimp only
    have ih := dotLoop_image_of_reads n baseA baseB p A B ha hb (k+1)
      (acc+ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero)*
        ExecFloat.Binary.toFloat32 (B.getD (baseB+k*p) posZero))
    rw [R7W12.ofFloat32_add,R7W12.ofFloat32_mul,
      NotNaNProbe.roundtrip _ (ha ⟨k,hk⟩),NotNaNProbe.roundtrip _ (hb ⟨k,hk⟩)] at ih
    rw [Fin.foldl.loop,dif_pos hk]
    exact ih
  · rename_i hk
    rw [Fin.foldl.loop,dif_neg hk]
termination_by n-k
decreasing_by omega

theorem dot_import_eq_of_reads
    (n baseA baseB p : Nat) (A B : Array Binary32)
    (ha : ∀ i : Fin n,
      (ExecFloat.Binary.toFloat32 (A.getD (baseA+i.val) posZero)).isNaN = false)
    (hb : ∀ i : Fin n,
      (ExecFloat.Binary.toFloat32 (B.getD (baseB+i.val*p) posZero)).isNaN = false) :
    ExecFloat.Binary.ofFloat32
      (NativeFinal.dotLoop n baseA baseB p A B 0 Packed10.zero32) =
      Fin.foldl n (fun a i => ExecFloat.add a
        (ExecFloat.mul (A.getD (baseA+i.val) posZero)
          (B.getD (baseB+i.val*p) posZero))) posZero := by
  have h := dotLoop_image_of_reads n baseA baseB p A B ha hb 0 Packed10.zero32
  change ExecFloat.Binary.ofFloat32 _ = Fin.foldl n _ posZero at h
  exact h

theorem direct_import_eq_finish
    (n baseA baseB p : Nat) (A B : Array Binary32) (result : Float32)
    (hresult : result = NativeFinal.dotLoop n baseA baseB p A B 0 Packed10.zero32)
    (ha : ∀ i : Fin n,
      (ExecFloat.Binary.toFloat32 (A.getD (baseA+i.val) posZero)).isNaN = false)
    (hb : ∀ i : Fin n,
      (ExecFloat.Binary.toFloat32 (B.getD (baseB+i.val*p) posZero)).isNaN = false) :
    ExecFloat.Binary.ofFloat32 result = Packed10.finish n baseA baseB p A B result := by
  rw [Packed10.finish_eq_dot n baseA baseB p A B result hresult,NativeFinal.dot_eq,hresult]
  exact dot_import_eq_of_reads n baseA baseB p A B ha hb

end Submission.R22DotImage
