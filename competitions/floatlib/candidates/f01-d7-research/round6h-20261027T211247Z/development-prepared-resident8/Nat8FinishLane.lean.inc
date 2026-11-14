/- Requires Nat8Projection-v1 and Nat8ProjectionFacts. NOT_RUN.
   Uses the retained finish/replay theorem; no new IEEE arithmetic. -/
namespace Submission.R22Resident8Projection
open FloatLib.Floats Competition

theorem finish_lane (n p baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (r : Fin 4) (c : Fin 2)
    (hread : ∀ i : Fin n,
      R15ThinPairs.select ((cacheView n p baseC cache).get i) c.val =
        ExecFloat.Binary.toFloat32 (B.getD (baseB + c.val + i.val * p) posZero)) :
    Packed10.finish n (baseA + r.val * n) (baseB + c.val) p A B
      (R15ThinPairs.select (projectRow (R22Resident8.loop n baseA (baseA + n)
        (baseA + 2 * n) (baseA + 3 * n) (R22Pair8.groups p) A cache 0 baseC
        Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
        Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32) r) c.val) =
      NativeFinal.dot n (baseA + r.val * n) (baseB + c.val) p A B := by
  apply Packed10.finish_eq_dot
  have h := loop_lane n p baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
    baseB baseC A B cache r c hread 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
  simpa only [rowBase_consecutive, projectRow_diagonal, select_diagonal,
    Nat.zero_mul, Nat.add_zero] using h

end Submission.R22Resident8Projection
