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
    rw [getElem!_neg (cacheRats a) i hc, getElem!_neg a i h]
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

def rmsnormStableCached (rows n : Nat) (eps : Word) (x g : Array Word) : Array Word :=
  let rx := cacheRats x
  let rg := cacheRats g
  let den := Array.ofFn (n := rows) fun r =>
    sqrtRational (rowVarianceCached n rx r.val 0 + rationalWord eps)
  let rd := cacheRats den
  Array.ofFn (n := rows * n) fun q =>
    roundRational (rx[q.val]! * rg[q.val % n]! / rd[q.val / n]!)

theorem rmsnormStableCached_eq : rmsnormStableCached = rmsnormStable := by
  funext rows n eps x g
  simp only [rmsnormStableCached, rmsnormStable, rowVarianceCached_eq, cacheRats_get]

def layernormStableCached (rows n : Nat) (eps : Word) (x g b : Array Word) : Array Word :=
  let rx := cacheRats x
  let rg := cacheRats g
  let rb := cacheRats b
  let means := Array.ofFn (n := rows) fun r => rowMeanCached n rx r.val
  let den := Array.ofFn (n := rows) fun r =>
    sqrtRational (rowVarianceCached n rx r.val means[r.val]! + rationalWord eps)
  let rd := cacheRats den
  Array.ofFn (n := rows * n) fun q =>
    roundRational ((rx[q.val]! - means[q.val / n]!) * rg[q.val % n]! /
      rd[q.val / n]! + rb[q.val % n]!)

theorem layernormStableCached_eq : layernormStableCached = layernormStable := by
  funext rows n eps x g b
  simp only [layernormStableCached, layernormStable, rowMeanCached_eq,
    rowVarianceCached_eq, cacheRats_get]

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
