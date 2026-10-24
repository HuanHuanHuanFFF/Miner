/- NOT_RUN future proof asset. Requires the exact28b819 declarations.
No runtime entry or dispatcher is replaced. -/
namespace Submission.R11WideGuardBridge
open FloatLib.Floats Competition

theorem block_span (batch m n : Nat) (A : Vector Binary32 (batch*m*n))
    (b : Fin batch) (h : Fin (m/4)) (hn : 0<n) :
    (b.val*m+4*h.val)*n + 3*n + (n-1) < (A.toArray.map ExecFloat.Binary.toFloat32).size := by
  have hb : 4*h.val+4≤m := by have hh:=h.isLt; omega
  have hs := R11WideLayout.nativeA_span batch m n A b (4*h.val) hb ⟨3,by decide⟩ hn
  simpa only [Nat.add_mul] using hs

theorem sized_block_span (batch m n : Nat) (A : Vector Binary32 (batch*m*n))
    (nativeA : Array Float32) (hsize : nativeA.size=A.toArray.size)
    (b : Fin batch) (h : Fin (m/4)) (hn : 0<n) :
    (b.val*m+4*h.val)*n + 3*n + (n-1) < nativeA.size := by
  rw [hsize]
  simpa only [Array.size_map] using block_span batch m n A b h hn

theorem sized_array_fits (batch m n : Nat) (A : Vector Binary32 (batch*m*n))
    (nativeA : Array Float32) (hsize : nativeA.size=A.toArray.size)
    (hA : A.toArray.size<USize.size) : nativeA.size<USize.size := by
  rw [hsize]
  exact hA

/-- Concrete prepared A/B, not an unclosed Projects premise. This vector occurs only in a theorem. -/
theorem direct_within_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (hn0 : 0<n) (hn : n<USize.size) (hA : A.toArray.size<USize.size)
    (b : Fin batch) (h : Fin (m/4)) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b (4*h.val)
      (Vector.ofFn fun g => R11WideRows4.within n ((b.val*m+4*h.val)*n)
        (A.toArray.map ExecFloat.Binary.toFloat32) (((Packed10.packB batch n p B).get b).get g)
        hn (block_span batch m n A b h hn0) (by simpa only [Array.size_map] using hA)) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [Packed10.vector_get_ofFn, R11WideRows4.within_row, Nat.add_mul]

end Submission.R11WideGuardBridge
