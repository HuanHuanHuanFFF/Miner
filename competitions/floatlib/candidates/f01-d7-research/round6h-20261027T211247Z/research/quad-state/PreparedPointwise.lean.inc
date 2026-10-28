/- Minimal pointwise bridge only; no second full public candidate. NOT_RUN. -/
namespace Submission.R22PreparedQuad
open FloatLib.Floats Competition

theorem prepared_getD (B : Array Binary32) (i : Nat) :
    (B.map ExecFloat.Binary.toFloat32).getD i Packed10.zero32 =
      ExecFloat.Binary.toFloat32 (B.getD i posZero) :=
  Packed10.nativeA_getD B i

theorem advance_get_of_prepared (p n baseA baseB : Nat)
    (A B : Array Binary32) (prepared : Array Float32)
    (hprepared : ∀ i, prepared.getD i Packed10.zero32 =
      ExecFloat.Binary.toFloat32 (B.getD i posZero))
    (k : Nat) (s : State p) (j : Fin p) :
    (advance p n baseA baseB A prepared k s).get j =
      update (ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+n+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+2*n+k) posZero))
        (ExecFloat.Binary.toFloat32 (A.getD (baseA+3*n+k) posZero))
        (ExecFloat.Binary.toFloat32 (B.getD (baseB+j.val+k*p) posZero)) (s.get j) := by
  change (s.toArray.mapIdx (fun i cell => update
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+n+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+2*n+k) posZero))
    (ExecFloat.Binary.toFloat32 (A.getD (baseA+3*n+k) posZero))
    (prepared.getD (baseB+k*p+i) Packed10.zero32) cell))[j.val] = _
  rw [Array.getElem_mapIdx]
  have haddr : baseB+k*p+j.val = baseB+j.val+k*p := by omega
  rw [haddr,hprepared]
  rfl

end Submission.R22PreparedQuad
