/-!
Append this file after NativePacked4.lean, preserving its only import,
`import ContractTensor`.  It is a source-level proof draft, NOT_RUN: this
environment has no Lean executable.  No claim of elaboration or gate success
is made.  These lemmas prove scheduling/structural facts only; they do not
silently assume the finite-result arithmetic bridge has been integrated.
-/

namespace R2W02

open Competition FloatLib.Floats

/-- A single component of exactly the same packed traversal as dot4. -/
def dotLane (pick : F4 → Float32) (A : Array Float32) (B : Array F4) :
    (fuel aIndex bIndex : Nat) → Float32 → Float32
  | 0, _, _, s => s
  | fuel + 1, aIndex, bIndex, s =>
    dotLane pick A B fuel (aIndex + 1) (bIndex + 1)
      (s + A.getD aIndex zero32 * pick (B.getD bIndex zero4))

/-- Projection uses only induction and definitional equality.
    No associative law and no floating-point theorem occurs here. -/
theorem dot4_projection (A : Array Float32) (B : Array F4)
    (fuel aIndex bIndex : Nat) (s0 s1 s2 s3 : Float32) :
    dot4 A B fuel aIndex bIndex s0 s1 s2 s3 =
      ⟨dotLane F4.s0 A B fuel aIndex bIndex s0,
       dotLane F4.s1 A B fuel aIndex bIndex s1,
       dotLane F4.s2 A B fuel aIndex bIndex s2,
       dotLane F4.s3 A B fuel aIndex bIndex s3⟩ := by
  induction fuel generalizing aIndex bIndex s0 s1 s2 s3 with
  | zero => rfl
  | succ fuel ih =>
      simpa only [dot4, dotLane] using
        ih (aIndex + 1) (bIndex + 1)
          (s0 + A.getD aIndex zero32 * (B.getD bIndex zero4).s0)
          (s1 + A.getD aIndex zero32 * (B.getD bIndex zero4).s1)
          (s2 + A.getD aIndex zero32 * (B.getD bIndex zero4).s2)
          (s3 + A.getD aIndex zero32 * (B.getD bIndex zero4).s3)

/-- The Nat tail recursion has exactly ContractTensor's increasing Fin order. -/
theorem dotLane_eq_finRange (pick : F4 → Float32)
    (A : Array Float32) (B : Array F4)
    (fuel aIndex bIndex : Nat) (s : Float32) :
    dotLane pick A B fuel aIndex bIndex s =
      (List.finRange fuel).foldl
        (fun acc k => acc +
          A.getD (aIndex + k.val) zero32 *
          pick (B.getD (bIndex + k.val) zero4)) s := by
  induction fuel generalizing aIndex bIndex s with
  | zero => simp [dotLane]
  | succ fuel ih =>
      simp only [dotLane, List.finRange_succ,
        List.foldl_cons, List.foldl_map]
      rw [ih]
      simp only [Fin.val_zero, Fin.val_succ, Nat.add_zero]
      congr 1
      funext acc k
      have ha : aIndex + 1 + k.val = aIndex + (k.val + 1) := by omega
      have hb : bIndex + 1 + k.val = bIndex + (k.val + 1) := by omega
      rw [ha, hb]

/-- Total reads commute with a map only when the default is mapped as well.
    This lemma is independent of floating-point representation. -/
def totalRead {α : Type} {n : Nat}
    (v : Fin n → α) (default : α) (i : Nat) : α :=
  if h : i < n then v ⟨i, h⟩ else default

theorem totalRead_map {α β : Type} {n : Nat}
    (f : α → β) (v : Fin n → α) (default : α) (i : Nat) :
    totalRead (fun j => f (v j)) (f default) i =
      f (totalRead v default i) := by
  unfold totalRead
  split <;> rfl

/-- Concrete Array form, using lemmas present in Lean v4.34.0. -/
theorem array_getD_map {α β : Type}
    (f : α → β) (xs : Array α) (default : α) (i : Nat) :
    (xs.map f).getD i (f default) = f (xs.getD i default) := by
  simp only [Array.getD_eq_getD_getElem?, Array.getElem?_map]
  cases xs[i]? <;> rfl

/-- Explicit theorem interface, not an axiom: the caller must supply `sound`.
    The executable fallback is in the else branch, so it is not eager. -/
theorem finish_eq_exactAt (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (q : Nat) (x : Float32)
    (sound : x.isFinite = true →
      ExecFloat.Binary.ofFloat32 x = exactAt batch m n p A B q) :
    finish batch m n p A B q x = exactAt batch m n p A B q := by
  unfold finish
  split
  · exact sound ‹x.isFinite = true›
  · rfl

theorem pushLane_size (batch m n p row col : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (x : Float32) (out : Array Binary32) :
    (pushLane batch m n p row col A B x out).size =
      out.size + (if col < p then 1 else 0) := by
  unfold pushLane
  split <;> simp_all

end R2W02
