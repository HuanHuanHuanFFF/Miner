import ContractExact

namespace R28SparseInput

def denseFold {A S : Type} (step : S → A → S) : List A → S → S
  | [], s => s
  | a :: rest, s => denseFold step rest (step s a)

def retainedFold {A S : Type} (step : S → A → S) (keep : A → Bool) :
    List A → S → S
  | [], s => s
  | a :: rest, s =>
    retainedFold step keep rest (if keep a then step s a else s)

/-- Abstract deletion of identity updates, not an actual cache/getter theorem.
    NOT_COMPILED: source is a proposed proof interface, no gate claim. -/
theorem retainedFold_eq {A S : Type} (step : S → A → S) (keep : A → Bool)
    (identity : ∀ a, keep a = false → ∀ s, step s a = s)
    (xs : List A) (s : S) : retainedFold step keep xs s = denseFold step xs s := by
  induction xs generalizing s with
  | nil => rfl
  | cons a rest ih =>
    cases h : keep a with
    | false => simp [retainedFold, denseFold, h, identity a h, ih]
    | true => simp [retainedFold, denseFold, h, ih]

end R28SparseInput
