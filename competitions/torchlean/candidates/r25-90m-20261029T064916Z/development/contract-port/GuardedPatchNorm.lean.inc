/-! ## R25: share operand decoding across complete dense and convolution kernels

Only operand representation changes. Every product still reaches the shipped exact
accumulator, final rounding, zero-sign rule and original special-value fallback.
-/

structure DecodedWord where
  mant : Nat
  idx : Nat
  sign : Bool
  exp : UInt32

@[inline] def decodeWord (w : Word) : DecodedWord :=
  ⟨mantOf w, idxOf w, signOf w, expOf w⟩

local instance : Inhabited DecodedWord := ⟨decodeWord 0⟩

def cacheWords (a : Array Word) : Array DecodedWord := a.map decodeWord

theorem cacheWords_get (a : Array Word) (i : Nat) :
    (cacheWords a)[i]! = decodeWord (a[i]!) := by
  by_cases h : i < a.size
  · simp [cacheWords, getElem!_pos, h]
  · have hc : ¬i < (cacheWords a).size := by simpa [cacheWords] using h
    rw [getElem!_neg _ _ hc, getElem!_neg _ _ h]
    rfl

@[inline] def dotStepCached (acc : Acc) (a b : DecodedWord) : Acc :=
  if a.exp = 255 ∨ b.exp = 255 then acc.markSpecial
  else acc.add (a.mant * b.mant) (a.idx + b.idx) (Bool.xor a.sign b.sign)

theorem dotStepCached_decode (acc : Acc) (a b : Word) :
    dotStepCached acc (decodeWord a) (decodeWord b) = dotStep acc a b := rfl

@[specialize] def dotLoopCached (da db : Nat → DecodedWord) (pos neg : Array Nat)
    (sp nz : Bool) (index : Nat) : Nat → Acc
  | 0 => ⟨pos, neg, sp, nz⟩
  | count + 1 =>
    match dotStepCached ⟨pos, neg, sp, nz⟩ (da index) (db index) with
    | ⟨p, n, s, z⟩ => dotLoopCached da db p n s z (index + 1) count

theorem dotLoopCached_decode (fa fb : Nat → Word) (pos neg : Array Nat)
    (sp nz : Bool) (index count : Nat) :
    dotLoopCached (fun t => decodeWord (fa t)) (fun t => decodeWord (fb t))
      pos neg sp nz index count = dotLoop fa fb pos neg sp nz index count := by
  induction count generalizing pos neg sp nz index with
  | zero => rfl
  | succ count ih =>
    simp only [dotLoopCached, dotLoop, dotStepCached_decode]
    generalize dotStep ⟨pos, neg, sp, nz⟩ (fa index) (fb index) = r
    obtain ⟨p, n, s, z⟩ := r
    exact ih p n s z (index + 1)

@[inline] def dotCached (n : Nat) (fa fb : Nat → Word)
    (da db : Nat → DecodedWord) : Word :=
  let acc := dotLoopCached da db (Array.replicate 18 0) (Array.replicate 18 0) false true 0 n
  if acc.special then
    dotSpec (Array.ofFn (n := n) fun i => fa i) (Array.ofFn (n := n) fun i => fb i)
  else finishFast acc.pos acc.neg (-298) (n ≠ 0 && acc.negZero)

theorem dotCached_eq (n : Nat) (fa fb : Nat → Word) (da db : Nat → DecodedWord)
    (ha : ∀ t, da t = decodeWord (fa t)) (hb : ∀ t, db t = decodeWord (fb t)) :
    dotCached n fa fb da db = dotFn n fa fb := by
  have hda : da = fun t => decodeWord (fa t) := funext ha
  have hdb : db = fun t => decodeWord (fb t) := funext hb
  rw [hda, hdb]
  simp only [dotCached, dotFn, dotLoopCached_decode]

def linearBothCached (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  let dx := cacheWords X
  let dw := cacheWords W
  Array.ofFn (n := rows * outW) fun q =>
    let i := q.val / outW
    let j := q.val % outW
    act relu <| dotCached (inW + 1)
      (fun t => if t < inW then X[i * inW + t]! else oneW)
      (fun t => if t < inW then W[j * inW + t]! else b[j]!)
      (fun t => if t < inW then dx[i * inW + t]! else decodeWord oneW)
      (fun t => if t < inW then dw[j * inW + t]! else decodeWord b[j]!)

theorem linearBothCached_eq : linearBothCached = linearWith dotFn := by
  funext rows inW outW relu X W b
  unfold linearBothCached linearWith
  apply congrArg (fun f : Fin (rows * outW) → Word => Array.ofFn f)
  funext q
  dsimp only
  apply congrArg (act relu)
  apply dotCached_eq <;> intro t <;> split_ifs <;> simp only [cacheWords_get]

def gemmPreGuard (batch m k n : Nat) (A B : Array Word) : Array Word :=
  let da := cacheWords A
  let db := cacheWords B
  Array.ofFn (n := batch * (m * n)) fun q =>
    let β := q.val / (m * n)
    let i := q.val / n % m
    let j := q.val % n
    dotCached k (fun t => A[(β * m + i) * k + t]!) (fun t => B[(β * k + t) * n + j]!)
      (fun t => da[(β * m + i) * k + t]!) (fun t => db[(β * k + t) * n + j]!)

theorem gemmPreGuard_eq : gemmPreGuard = gemmWith dotFn := by
  funext batch m k n A B
  unfold gemmPreGuard gemmWith
  apply congrArg (fun f : Fin (batch * (m * n)) → Word => Array.ofFn f)
  funext q
  dsimp only
  apply dotCached_eq <;> intro t <;> exact cacheWords_get _ _

@[inline] def windowCached (s : ConvShape) (dinp : Array DecodedWord) (y x t : Nat) : DecodedWord :=
  let c := t / (s.kh * s.kw)
  let dy := t / s.kw % s.kh
  let dx := t % s.kw
  let yy := y * s.stride + dy
  let xx := x * s.stride + dx
  if yy < s.pad ∨ xx < s.pad ∨ yy - s.pad ≥ s.h ∨ xx - s.pad ≥ s.w then decodeWord 0
  else dinp[(c * s.h + (yy - s.pad)) * s.w + (xx - s.pad)]!

theorem windowCached_eq (s : ConvShape) (inp : Array Word) (y x t : Nat) :
    windowCached s (cacheWords inp) y x t = decodeWord (windowAt s inp y x t) := by
  unfold windowCached windowAt
  split_ifs <;> simp only [cacheWords_get]

def conv2dTensorCached (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  let dinp := cacheWords inp
  let dwts := cacheWords wts
  let k := s.cin * s.kh * s.kw
  Array.ofFn (n := s.cout * (s.ho * s.wo)) fun q =>
    let o := q.val / (s.ho * s.wo)
    let y := q.val / s.wo % s.ho
    let x := q.val % s.wo
    act relu <| dotCached (k + 1)
      (fun t => if t < k then windowAt s inp y x t else oneW)
      (fun t => if t < k then wts[o * k + t]! else b[o]!)
      (fun t => if t < k then windowCached s dinp y x t else decodeWord oneW)
      (fun t => if t < k then dwts[o * k + t]! else decodeWord b[o]!)

theorem conv2dTensorCached_eq : conv2dTensorCached = conv2dWith dotFn := by
  funext s relu inp wts b
  unfold conv2dTensorCached conv2dWith
  apply congrArg (fun f : Fin (s.cout * (s.ho * s.wo)) → Word => Array.ofFn f)
  funext q
  dsimp only
  apply congrArg (act relu)
  apply dotCached_eq <;> intro t <;> split_ifs <;> simp only [windowCached_eq, cacheWords_get]

def depthwisePreGuard (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  let dinp := cacheWords inp
  let dwts := cacheWords wts
  let k := s.kh * s.kw
  Array.ofFn (n := s.cin * (s.ho * s.wo)) fun q =>
    let c := q.val / (s.ho * s.wo)
    let y := q.val / s.wo % s.ho
    let x := q.val % s.wo
    act relu <| dotCached (k + 1)
      (fun t => if t < k then windowAt s inp y x (c * k + t) else oneW)
      (fun t => if t < k then wts[c * k + t]! else b[c]!)
      (fun t => if t < k then windowCached s dinp y x (c * k + t) else decodeWord oneW)
      (fun t => if t < k then dwts[c * k + t]! else decodeWord b[c]!)

theorem depthwisePreGuard_eq : depthwisePreGuard = depthwiseWith dotFn := by
  funext s relu inp wts b
  unfold depthwisePreGuard depthwiseWith
  apply congrArg (fun f : Fin (s.cin * (s.ho * s.wo)) → Word => Array.ofFn f)
  funext q
  dsimp only
  apply congrArg (act relu)
  apply dotCached_eq <;> intro t <;> split_ifs <;> simp only [windowCached_eq, cacheWords_get]


/-! One-row dense calls reuse X across output channels but do not reuse W. -/
def linearInputCached (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  let dx := cacheWords X
  Array.ofFn (n := rows * outW) fun q =>
    let i := q.val / outW
    let j := q.val % outW
    act relu <| dotCached (inW + 1)
      (fun t => if t < inW then X[i * inW + t]! else oneW)
      (fun t => if t < inW then W[j * inW + t]! else b[j]!)
      (fun t => if t < inW then dx[i * inW + t]! else decodeWord oneW)
      (fun t => decodeWord (if t < inW then W[j * inW + t]! else b[j]!))

theorem linearInputCached_eq : linearInputCached = linearWith dotFn := by
  funext rows inW outW relu X W b
  unfold linearInputCached linearWith
  apply congrArg (fun f : Fin (rows * outW) → Word => Array.ofFn f)
  funext q
  dsimp only
  apply congrArg (act relu)
  apply dotCached_eq
  · intro t
    split_ifs <;> simp only [cacheWords_get]
  · intro t; rfl

def linearPreGuard (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if rows ≤ 1 then linearInputCached rows inW outW relu X W b
  else linearBothCached rows inW outW relu X W b

theorem linearPreGuard_eq : linearPreGuard = linearWith dotFn := by
  funext rows inW outW relu X W b
  simp only [linearPreGuard, linearInputCached_eq, linearBothCached_eq, ite_self]

/-! Precompute each spatial input window once, sharing its indices across output channels.
The patch arrays hold references to the shared decoded input words.
-/

def patchWords (s : ConvShape) (inp : Array Word) : Array (Array DecodedWord) :=
  let dinp := cacheWords inp
  Array.ofFn (n := s.ho * s.wo) fun p =>
    Array.ofFn (n := s.cin * s.kh * s.kw) fun t =>
      windowCached s dinp (p.val / s.wo % s.ho) (p.val % s.wo) t.val

theorem patchWords_get (s : ConvShape) (inp : Array Word) (p : Nat)
    (hp : p < s.ho * s.wo) (t : Nat) (ht : t < s.cin * s.kh * s.kw) :
    (patchWords s inp)[p]![t]! =
      decodeWord (windowAt s inp (p / s.wo % s.ho) (p % s.wo) t) := by
  simp [patchWords, getElem!_pos, hp, ht, windowCached_eq]

theorem patch_row (q h w : Nat) : (q % (h * w)) / w % h = q / w % h := by
  rw [Nat.mul_comm h w, Nat.mod_mul_right_div_self, Nat.mod_mod]

theorem patch_col (q h w : Nat) : (q % (h * w)) % w = q % w := by
  rw [Nat.mul_comm h w, Nat.mod_mul_right_mod]

def conv2dPreGuard (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  let patches := patchWords s inp
  let dwts := cacheWords wts
  let k := s.cin * s.kh * s.kw
  Array.ofFn (n := s.cout * (s.ho * s.wo)) fun q =>
    let o := q.val / (s.ho * s.wo)
    let y := q.val / s.wo % s.ho
    let x := q.val % s.wo
    let dp := patches[q.val % (s.ho * s.wo)]!
    act relu <| dotCached (k + 1)
      (fun t => if t < k then windowAt s inp y x t else oneW)
      (fun t => if t < k then wts[o * k + t]! else b[o]!)
      (fun t => if t < k then dp[t]! else decodeWord oneW)
      (fun t => if t < k then dwts[o * k + t]! else decodeWord b[o]!)

theorem conv2dPreGuard_eq : conv2dPreGuard = conv2dWith dotFn := by
  funext s relu inp wts b
  unfold conv2dPreGuard conv2dWith
  apply congrArg (fun f : Fin (s.cout * (s.ho * s.wo)) → Word => Array.ofFn f)
  funext q
  have hsize : 0 < s.ho * s.wo := by
    by_contra hn
    have hz : s.ho * s.wo = 0 := Nat.eq_zero_of_not_pos hn
    have hq := q.isLt
    simp [hz] at hq
  have hp : q.val % (s.ho * s.wo) < s.ho * s.wo := Nat.mod_lt _ hsize
  dsimp only
  apply congrArg (act relu)
  apply dotCached_eq
  · intro t
    by_cases ht : t < s.cin * s.kh * s.kw
    · simp only [ht, ite_true]
      rw [patchWords_get s inp _ hp t ht, patch_row, patch_col]
    · simp only [ht, ite_false]
  · intro t
    split_ifs <;> simp only [cacheWords_get]

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

def rmsnormPreGuard (rows n : Nat) (eps : Word) (x g : Array Word) : Array Word :=
  if stableNormDomain rows n eps x g then rmsnormStableCached rows n eps x g
  else rmsnormLegacyWith dotFn rows n eps x g

theorem rmsnormPreGuard_eq : rmsnormPreGuard = rmsnormWith dotFn := by
  funext rows n eps x g
  simp only [rmsnormPreGuard, rmsnormWith, rmsnormStableCached_eq]

def layernormPreGuard (rows n : Nat) (eps : Word) (x g b : Array Word) : Array Word :=
  if stableNormDomain rows n eps x g && b.size == n && b.all finiteWord then
    layernormStableCached rows n eps x g b
  else layernormLegacyWith dotFn rows n eps x g b

theorem layernormPreGuard_eq : layernormPreGuard = layernormWith dotFn := by
  funext rows n eps x g b
  simp only [layernormPreGuard, layernormWith, layernormStableCached_eq]

/-! Return empty outputs before constructing caches or input windows. -/

theorem array_empty_of_size (a : Array Word) (h : a.size = 0) : a = #[] := by
  apply Array.ext (by simpa using h)
  intro i h1 h2
  simp at h2

def linearCached (rows inW outW : Nat) (relu : Bool) (X W b : Array Word) : Array Word :=
  if rows * outW = 0 then #[] else linearPreGuard rows inW outW relu X W b

theorem linearCached_eq : linearCached = linearWith dotFn := by
  funext rows inW outW relu X W b
  unfold linearCached
  split_ifs with hz
  · symm; apply array_empty_of_size; simp [linearWith, hz]
  · rw [linearPreGuard_eq]

def gemmCached (batch m k n : Nat) (A B : Array Word) : Array Word :=
  if batch * (m * n) = 0 then #[] else gemmPreGuard batch m k n A B

theorem gemmCached_eq : gemmCached = gemmWith dotFn := by
  funext batch m k n A B
  unfold gemmCached
  split_ifs with hz
  · symm; apply array_empty_of_size; simp [gemmWith, hz]
  · rw [gemmPreGuard_eq]

def conv2dCached (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  if s.cout * (s.ho * s.wo) = 0 then #[] else conv2dPreGuard s relu inp wts b

theorem conv2dCached_eq : conv2dCached = conv2dWith dotFn := by
  funext s relu inp wts b
  unfold conv2dCached
  split_ifs with hz
  · symm; apply array_empty_of_size; simp [conv2dWith, hz]
  · rw [conv2dPreGuard_eq]

def depthwiseCached (s : ConvShape) (relu : Bool) (inp wts b : Array Word) : Array Word :=
  if s.cin * (s.ho * s.wo) = 0 then #[] else depthwisePreGuard s relu inp wts b

theorem depthwiseCached_eq : depthwiseCached = depthwiseWith dotFn := by
  funext s relu inp wts b
  unfold depthwiseCached
  split_ifs with hz
  · symm; apply array_empty_of_size; simp [depthwiseWith, hz]
  · rw [depthwisePreGuard_eq]

def rmsnormCached (rows n : Nat) (eps : Word) (x g : Array Word) : Array Word :=
  if rows * n = 0 then #[] else rmsnormPreGuard rows n eps x g

theorem rmsnormCached_eq : rmsnormCached = rmsnormWith dotFn := by
  funext rows n eps x g
  unfold rmsnormCached
  split_ifs with hz
  · symm
    apply array_empty_of_size
    simp only [rmsnormWith]
    split_ifs <;> simp [rmsnormStable, rmsnormLegacyWith, hz]
  · rw [rmsnormPreGuard_eq]

def layernormCached (rows n : Nat) (eps : Word) (x g b : Array Word) : Array Word :=
  if rows * n = 0 then #[] else layernormPreGuard rows n eps x g b

theorem layernormCached_eq : layernormCached = layernormWith dotFn := by
  funext rows n eps x g b
  unfold layernormCached
  split_ifs with hz
  · symm
    apply array_empty_of_size
    simp only [layernormWith]
    split_ifs <;> simp [layernormStable, layernormLegacyWith, hz]
  · rw [layernormPreGuard_eq]
