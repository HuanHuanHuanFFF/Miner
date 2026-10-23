/-- Abstract array-to-vector bridge: keep the concrete output loop opaque. -/
theorem prefix_vector_eq_ofFn (f : Nat → Binary32) (count : Nat)
    (out : Array Binary32) (h : Prefix f count out) :
    (Vector.mk out h.1 : Vector Binary32 count) =
      Vector.ofFn (fun q : Fin count => f q.val) := by
  apply Vector.ext
  intro q hq
  rw [Vector.getElem_mk, Vector.getElem_ofFn]
  exact h.2 q (by rw [h.1]; exact hq)

/-- Scalar address/float bridge, without the concrete writer in its goal. -/
theorem points_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    Vector.ofFn (fun q : Fin (batch * m * p) => point batch m n p A B q.val) =
      referenceBmm batch m n p A B := by
  unfold referenceBmm
  apply congrArg (fun (f : Fin (batch * m * p) → Binary32) => Vector.ofFn f)
  funext q
  dsimp only [point]
  rw [NativeFinal.dot_eq]
  simp only [add_eq, mul_eq]
  apply congrArg (fun (f : Binary32 → Fin n → Binary32) => Fin.foldl n f posZero)
  funext acc k
  rw [index_address ((bmmDecodeC m p q.val).1 * n) k.val p
    (bmmDecodeC m p q.val).2.2]

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (prefix_vector_eq_ofFn (point batch m n p A B) (batch * m * p)
    (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (points_eq_reference batch m n p A B)

