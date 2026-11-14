/-! Optional second-generation exact normalization statistics.

NOT_RUN. This fragment is absent from the first frozen candidates. It removes
per-term rational reduction: words are accumulated on the common binary32
integer lattice, and only row totals become rationals. No float approximation.
-/

def wordScale : ℚ := (2 : ℚ) ^ (-149 : ℤ)

theorem rationalWord_key (w : Word) : rationalWord w = (keyOf w : ℚ) * wordScale := by
  unfold rationalWord
  rw [decodeD_toRat, keyOf_eq]
  push_cast
  simp only [wordScale, zpow_sub₀ (by norm_num : (2 : ℚ) ≠ 0),
    zpow_natCast, zpow_neg, zpow_ofNat]
  ring

theorem keyFold_toRat (l : List Nat) (f : Nat → Word) (a : Int) :
    ((l.foldl (fun total j => total + keyOf (f j)) a : Int) : ℚ) * wordScale =
      l.foldl (fun total j => total + rationalWord (f j)) ((a : ℚ) * wordScale) := by
  induction l generalizing a with
  | nil => rfl
  | cons j l ih =>
    simp only [List.foldl_cons]
    rw [ih]
    apply congrArg (fun startVal : ℚ => l.foldl (fun total j => total + rationalWord (f j)) startVal)
    rw [rationalWord_key]
    push_cast
    ring

theorem keySqFold_toRat (l : List Nat) (f : Nat → Word) (a : Int) :
    ((l.foldl (fun total j => let v := keyOf (f j); total + v * v) a : Int) : ℚ) * wordScale ^ 2 =
      l.foldl (fun total j => total + rationalWord (f j) ^ 2) ((a : ℚ) * wordScale ^ 2) := by
  induction l generalizing a with
  | nil => rfl
  | cons j l ih =>
    simp only [List.foldl_cons]
    rw [ih]
    apply congrArg (fun startVal : ℚ => l.foldl (fun total j => total + rationalWord (f j) ^ 2) startVal)
    rw [rationalWord_key]
    push_cast
    ring

def rowKeySum (n : Nat) (x : Array Word) (row : Nat) : Int :=
  (List.range n).foldl (fun total j => total + keyOf x[row * n + j]!) 0

def rowKeySqSum (n : Nat) (x : Array Word) (row : Nat) : Int :=
  (List.range n).foldl (fun total j => let v := keyOf x[row * n + j]!; total + v * v) 0

def rowKeyMean (n : Nat) (x : Array Word) (row : Nat) : ℚ :=
  ((rowKeySum n x row : ℚ) * wordScale) / n

def rowKeySecondMoment (n : Nat) (x : Array Word) (row : Nat) : ℚ :=
  ((rowKeySqSum n x row : ℚ) * wordScale ^ 2) / n

theorem rowKeyMean_eq (n : Nat) (x : Array Word) (row : Nat) :
    rowKeyMean n x row = rowMean n x row := by
  simp only [rowKeyMean, rowKeySum, rowMean, keyFold_toRat, Int.cast_zero, zero_mul]

theorem rowKeySecondMoment_eq (n : Nat) (x : Array Word) (row : Nat) :
    rowKeySecondMoment n x row = rowVariance n x row 0 := by
  simp only [rowKeySecondMoment, rowKeySqSum, rowVariance, keySqFold_toRat,
    Int.cast_zero, zero_mul, sub_zero]

theorem foldl_add_to_sum (l : List Nat) (f : Nat → ℚ) (a : ℚ) :
    l.foldl (fun total j => total + f j) a = a + (l.map f).sum := by
  induction l generalizing a with
  | nil => simp
  | cons j l ih =>
    simp only [List.foldl_cons, ih, List.map_cons, List.sum_cons]
    ring

theorem sum_centered_square (l : List Nat) (f : Nat → ℚ) (mean : ℚ) :
    (l.map (fun j => (f j - mean) ^ 2)).sum =
      (l.map (fun j => f j ^ 2)).sum - 2 * mean * (l.map f).sum +
        (l.length : ℚ) * mean ^ 2 := by
  induction l with
  | nil => simp
  | cons j l ih =>
    simp only [List.map_cons, List.sum_cons, List.length_cons, ih, Nat.cast_add, Nat.cast_one]
    ring

theorem rowVariance_atMean (n : Nat) (x : Array Word) (row : Nat) (hn : n ≠ 0) :
    rowVariance n x row (rowMean n x row) =
      rowVariance n x row 0 - rowMean n x row ^ 2 := by
  have hnq : (n : ℚ) ≠ 0 := by exact_mod_cast hn
  simp only [rowVariance, rowMean, foldl_add_to_sum, zero_add, sub_zero]
  rw [sum_centered_square, List.length_range]
  field_simp [hnq]
  ring

def rowKeyVariance (n : Nat) (x : Array Word) (row : Nat) : ℚ :=
  rowKeySecondMoment n x row - rowKeyMean n x row ^ 2

theorem rowKeyVariance_eq (n : Nat) (x : Array Word) (row : Nat) (hn : n ≠ 0) :
    rowKeyVariance n x row = rowVariance n x row (rowMean n x row) := by
  rw [rowKeyVariance, rowKeySecondMoment_eq, rowKeyMean_eq, rowVariance_atMean n x row hn]
