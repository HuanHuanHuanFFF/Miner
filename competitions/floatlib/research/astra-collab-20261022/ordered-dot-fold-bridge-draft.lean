namespace OrderedDotBridge

/-- Conditional decoding suffices: the final finite result certifies each used factor. -/
theorem fold_finite {ι : Type} (indices : List ι)
    (da db : ι → Float32) (a b : ι → Binary32)
    (hA : ∀ i, (da i).isFinite = true → ExecFloat.Binary.ofFloat32 (da i) = a i)
    (hB : ∀ i, (db i).isFinite = true → ExecFloat.Binary.ofFloat32 (db i) = b i)
    (acc : Float32)
    (hf : (indices.foldl (fun s i => s + da i * db i) acc).isFinite = true) :
    acc.isFinite = true ∧
      ExecFloat.Binary.ofFloat32 (indices.foldl (fun s i => s + da i * db i) acc) =
        indices.foldl (fun s i => ExecFloat.add s (ExecFloat.mul (a i) (b i)))
          (ExecFloat.Binary.ofFloat32 acc) := by
  induction indices generalizing acc with
  | nil => exact ⟨hf, rfl⟩
  | cons i rest ih =>
    change (rest.foldl (fun s j => s + da j * db j) (acc + da i * db i)).isFinite = true at hf
    have hi := ih (acc + da i * db i) hf
    have ha := FinalFinite.add_finite_inputs acc (da i * db i) hi.1
    have hm := FinalFinite.mul_finite_inputs (da i) (db i) ha.2
    refine ⟨ha.1, ?_⟩
    have hnext := hi.2
    rw [ExecFloat.Binary.ofFloat32_add_of_isFinite _ _ ha.1 ha.2,
      NativeBridge.ofFloat32Mul _ _ hm.1 hm.2, hA i hm.1, hB i hm.2] at hnext
    exact hnext

end OrderedDotBridge
