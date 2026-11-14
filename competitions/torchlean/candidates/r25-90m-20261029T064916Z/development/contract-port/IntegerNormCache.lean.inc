/-! Cache the pinned exact rational values across normalization statistics and outputs. -/

theorem rationalWord_zero : rationalWord (0 : Word) = 0 := by
  unfold rationalWord
  rw [decodeD_toRat]
  have hz : sv (0 : Word) = 0 := rfl
  rw [hz]
  simp

def cacheRats (a : Array Word) : Array ℚ := a.map rationalWord

theorem cacheRats_get (a : Array Word) (i : Nat) :
    (cacheRats a)[i]! = rationalWord (a[i]!) := by
  by_cases h : i < a.size
  · simp [cacheRats, getElem!_pos, h]
  · have hc : ¬i < (cacheRats a).size := by simpa [cacheRats] using h
    rw [getElem!_neg _ _ hc, getElem!_neg _ _ h]
    exact rationalWord_zero.symm

def rowMeanCached (n : Nat) (x : Array ℚ) (row : Nat) : ℚ :=
  ((List.range n).foldl (fun total j => total + x[row * n + j]!) 0) / n

def rowVarianceCached (n : Nat) (x : Array ℚ) (row : Nat) (mean : ℚ) : ℚ :=
  ((List.range n).foldl (fun total j => total + (x[row * n + j]! - mean) ^ 2) 0) / n

theorem rowMeanCached_eq (n : Nat) (x : Array Word) (row : Nat) :
    rowMeanCached n (cacheRats x) row = rowMean n x row := by
  simp only [rowMeanCached, rowMean, cacheRats_get]

theorem rowVarianceCached_eq (n : Nat) (x : Array Word) (row : Nat) (mean : ℚ) :
    rowVarianceCached n (cacheRats x) row mean = rowVariance n x row mean := by
  simp only [rowVarianceCached, rowVariance, cacheRats_get]


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

/-! Second-generation full normalization path: exact integer row moments, then
the original rational denominator/output operations. No approximate arithmetic.
-/

theorem rat_getElem_ofFn (n : Nat) (f : Nat → ℚ) (i : Nat) (hi : i < n) :
    (Array.ofFn (n := n) fun q => f q.val)[i]! = f i := by
  rw [getElem!_pos _ i (by simpa using hi), Array.getElem_ofFn]

def rmsnormStableCached (rows n : Nat) (eps : Word) (x g : Array Word) : Array Word :=
  let rg := cacheRats g
  let den := Array.ofFn (n := rows) fun r =>
    sqrtRational (rowKeySecondMoment n x r.val + rationalWord eps)
  let rd := cacheRats den
  Array.ofFn (n := rows * n) fun q =>
    roundRational (rationalWord x[q.val]! * rg[q.val % n]! / rd[q.val / n]!)

theorem rmsnormStableCached_eq : rmsnormStableCached = rmsnormStable := by
  funext rows n eps x g
  simp only [rmsnormStableCached, rmsnormStable, rowKeySecondMoment_eq, cacheRats_get]

theorem integerNormDen_eq (rows n : Nat) (eps : Word) (x : Array Word) (hn : n ≠ 0) :
    (Array.ofFn (n := rows) fun r =>
      sqrtRational (rowKeySecondMoment n x r.val -
        (Array.ofFn (n := rows) fun j => rowMean n x j.val)[r.val]! ^ 2 + rationalWord eps)) =
    (Array.ofFn (n := rows) fun r =>
      sqrtRational (rowVariance n x r.val
        (Array.ofFn (n := rows) fun j => rowMean n x j.val)[r.val]! + rationalWord eps)) := by
  apply congrArg (fun f : Fin rows → Word => Array.ofFn f)
  funext r
  rw [rat_getElem_ofFn rows (fun j => rowMean n x j) r.val r.isLt,
    rowKeySecondMoment_eq, rowVariance_atMean n x r.val hn]

def layernormStableCached (rows n : Nat) (eps : Word) (x g b : Array Word) : Array Word :=
  if n = 0 then layernormStable rows n eps x g b
  else
    let rg := cacheRats g
    let rb := cacheRats b
    let means := Array.ofFn (n := rows) fun r => rowKeyMean n x r.val
    let den := Array.ofFn (n := rows) fun r =>
      sqrtRational (rowKeySecondMoment n x r.val - means[r.val]! ^ 2 + rationalWord eps)
    let rd := cacheRats den
    Array.ofFn (n := rows * n) fun q =>
      roundRational ((rationalWord x[q.val]! - means[q.val / n]!) * rg[q.val % n]! /
        rd[q.val / n]! + rb[q.val % n]!)

theorem layernormStableCached_eq : layernormStableCached = layernormStable := by
  funext rows n eps x g b
  unfold layernormStableCached
  split_ifs with hn
  · rfl
  · simp only [rowKeyMean_eq, integerNormDen_eq rows n eps x hn, cacheRats_get, layernormStable]

def rmsnormCached (rows n : Nat) (eps : Word) (x g : Array Word) : Array Word :=
  if stableNormDomain rows n eps x g then rmsnormStableCached rows n eps x g
  else rmsnormLegacyWith dotFn rows n eps x g

theorem rmsnormCached_eq : rmsnormCached = rmsnormWith dotFn := by
  funext rows n eps x g
  simp only [rmsnormCached, rmsnormWith, rmsnormStableCached_eq]

def layernormCached (rows n : Nat) (eps : Word) (x g b : Array Word) : Array Word :=
  if stableNormDomain rows n eps x g && b.size == n && b.all finiteWord then
    layernormStableCached rows n eps x g b
  else layernormLegacyWith dotFn rows n eps x g b

theorem layernormCached_eq : layernormCached = layernormWith dotFn := by
  funext rows n eps x g b
  simp only [layernormCached, layernormWith, layernormStableCached_eq]
