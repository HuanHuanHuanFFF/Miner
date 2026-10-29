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
