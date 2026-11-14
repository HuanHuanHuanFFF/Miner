import ContractExact

/- Original follow-on arithmetic bridges. NOT_COMPILED.
No new kernel, imported source copy, runtime replacement, or Correct claim.
Array getters, UInt64 refinements, and the final Submission wiring remain open.
-/
namespace WinogradFollowOn

def prefix (f : Nat → Int) : Nat → Int
  | 0 => 0
  | n+1 => prefix f n + f n

def crossSum (a b : Nat → Int) (k : Nat) : Int :=
  prefix (fun i => (a (2*i)+b (2*i+1)) * (a (2*i+1)+b (2*i))) k

def selfSum (a : Nat → Int) (k : Nat) : Int :=
  prefix (fun i => a (2*i)*a (2*i+1)) k

theorem pair_identity (a0 a1 b0 b1 : Int) :
    (a0+b1)*(a1+b0)-a0*a1-b0*b1 = a0*b0+a1*b1 := by ring

theorem even_prefix (a b : Nat → Int) (k : Nat) :
    prefix (fun i => a i*b i) (2*k) =
      crossSum a b k-selfSum a k-selfSum b k := by
  induction k with
  | zero => simp [prefix, crossSum, selfSum]
  | succ k ih =>
    rw [show 2*(k+1)=(2*k+1)+1 by omega, prefix, prefix, ih]
    simp only [crossSum, selfSum, prefix]
    ring

theorem odd_prefix (a b : Nat → Int) (k : Nat) :
    prefix (fun i => a i*b i) (2*k+1) =
      crossSum a b k-selfSum a k-selfSum b k+a (2*k)*b (2*k) := by
  rw [prefix, even_prefix]

theorem all_lengths (a b : Nat → Int) (n : Nat) :
    prefix (fun i => a i*b i) n =
      crossSum a b (n/2)-selfSum a (n/2)-selfSum b (n/2) +
        (if n%2=0 then 0 else a (n-1)*b (n-1)) := by
  have hm : n%2 < 2 := Nat.mod_lt n (by omega)
  by_cases h : n%2=0
  · have hn : n=2*(n/2) := by omega
    conv_lhs => rw [hn]
    rw [even_prefix, if_pos h, add_zero]
  · have hn : n=2*(n/2)+1 := by omega
    have ht : n-1=2*(n/2) := by omega
    conv_lhs => rw [hn]
    rw [odd_prefix, if_neg h, ht]

theorem abs_prefix_le (f : Nat → Int) (B : Int) (n : Nat)
    (h : ∀ i, i<n → |f i| ≤ B) :
    |prefix f n| ≤ (n : Int)*B := by
  revert h
  induction n with
  | zero => intro h; simp [prefix]
  | succ n ih =>
    intro h
    calc
      |prefix f (n+1)| = |prefix f n+f n| := rfl
      _ ≤ |prefix f n|+|f n| := abs_add _ _
      _ ≤ (n : Int)*B+B := add_le_add (ih (fun i hi => h i (by omega))) (h n (by omega))
      _ = ((n+1 : Nat) : Int)*B := by push_cast; ring

/-- The existing full admission guard implies an ordinary direct product is
already below signed63. It does NOT imply that a Winograd cross product is. -/
theorem direct_product_lt62 (A B : Int) (hA : 0≤A) (hB : 0≤B)
    (h : A+B < 4294967296) : A*B < (2 : Int)^62 := by
  have hs := sq_nonneg (A-B)
  have hu : A+B ≤ 4294967295 := by omega
  have ht : (A+B)*(A+B) ≤ (4294967295 : Int)*4294967295 :=
    mul_le_mul hu hu (add_nonneg hA hB) (by norm_num)
  norm_num at ht ⊢
  nlinarith

theorem cross_magnitude_lt64 (A B x0 x1 y0 y1 : Int)
    (hA : 0≤A) (hB : 0≤B) (h : A+B < 4294967296)
    (hx0 : |x0|≤A) (hx1 : |x1|≤A) (hy0 : |y0|≤B) (hy1 : |y1|≤B) :
    |(x0+y1)*(x1+y0)| < (2 : Int)^64 := by
  have hf : |x0+y1|≤A+B := (abs_add _ _).trans (add_le_add hx0 hy1)
  have hg : |x1+y0|≤A+B := (abs_add _ _).trans (add_le_add hx1 hy0)
  have hp : |x0+y1|*|x1+y0|≤(A+B)*(A+B) :=
    mul_le_mul hf hg (abs_nonneg _) (by omega)
  have hu : A+B ≤ 4294967295 := by omega
  calc
    |(x0+y1)*(x1+y0)| = |x0+y1|*|x1+y0| := abs_mul _ _
    _ ≤ (A+B)*(A+B) := hp
    _ ≤ (4294967295 : Int)*4294967295 :=
      mul_le_mul hu hu (add_nonneg hA hB) (by norm_num)
    _ < (2 : Int)^64 := by norm_num

/-- A fixed mathematical threshold, not a tuned block/window parameter. -/
theorem signed63_threshold :
    (3037000499 : Int)^2 < 2^63 ∧ 2^63 ≤ (3037000500 : Int)^2 := by norm_num

theorem cross_signed63 (A B x0 x1 y0 y1 : Int)
    (hA : 0≤A) (hB : 0≤B) (h : A+B≤3037000499)
    (hx0 : |x0|≤A) (hx1 : |x1|≤A) (hy0 : |y0|≤B) (hy1 : |y1|≤B) :
    |(x0+y1)*(x1+y0)| < (2 : Int)^63 := by
  have hf : |x0+y1|≤A+B := (abs_add _ _).trans (add_le_add hx0 hy1)
  have hg : |x1+y0|≤A+B := (abs_add _ _).trans (add_le_add hx1 hy0)
  have hp : |x0+y1|*|x1+y0|≤(A+B)*(A+B) :=
    mul_le_mul hf hg (abs_nonneg _) (by omega)
  calc
    |(x0+y1)*(x1+y0)| = |x0+y1|*|x1+y0| := abs_mul _ _
    _ ≤ (A+B)*(A+B) := hp
    _ ≤ (3037000499 : Int)*3037000499 :=
      mul_le_mul h h (add_nonneg hA hB) (by norm_num)
    _ < (2 : Int)^63 := by norm_num

def signedRepresentative (bits : Nat) (z : Int) : Int :=
  let r := z % (2 : Int)^bits
  if r < (2 : Int)^(bits-1) then r else r-(2 : Int)^bits

theorem signed64_exact (z : Int) (lo : -(2 : Int)^63≤z) (hi : z<(2 : Int)^63) :
    signedRepresentative 64 z=z := by
  unfold signedRepresentative
  norm_num at lo hi ⊢
  split_ifs <;> omega

theorem signed128_exact (z : Int) (lo : -(2 : Int)^127≤z) (hi : z<(2 : Int)^127) :
    signedRepresentative 128 z=z := by
  unfold signedRepresentative
  norm_num at lo hi ⊢
  split_ifs <;> omega

/-- YL(oneW,bias) uses a 2^23 coefficient and index126+idx(bias).
Replacing only its index by149+idx(bias) adds a spurious factor2^23. -/
theorem bias_units (m i low : Nat) (h : low≤126+i) :
    (2 : Int)^23*(m : Int)*2^(126+i-low) = (m : Int)*2^(149+i-low) := by
  rw [show 149+i-low=23+(126+i-low) by omega, pow_add]
  ring

/-- Source-level multiplication count. k=floor(n/2), t=n%2, E=admitted
outputs. Does not count sparse skipping, zero replay, allocation, or time. -/
theorem count_identity (R O k t E : Int) :
    R*O*(2*k+t) - ((R+O)*k + E*(k+t) + (R*O-E)*(2*k+t)) =
      k*(E-R-O) := by ring

/-- Invalid preparations return before selfSum. `prepared` is the number
of successfully prepared input and weight rows, not always R+O. -/
theorem prepared_count_identity (R O prepared k t E : Int) :
    R*O*(2*k+t) - (prepared*k + E*(k+t) + (R*O-E)*(2*k+t)) =
      k*(E-prepared) := by ring

/-- Uniform sparse-input count, assuming the old QPa sparse guard succeeds.
Misses in the supplied candidate use n-term YaU, so they lose sparse skipping. -/
theorem sparse_count_identity (R O prepared k t E nnz : Int) :
    R*O*nnz - (prepared*k + E*(k+t) + (R*O-E)*(2*k+t)) =
      E*(nnz-(k+t))-(R*O-E)*((2*k+t)-nnz)-prepared*k := by ring

/-- For rows=1, even perfect admission cannot save multiplication work. -/
theorem one_row_count (O k t : Int) :
    ((1+O)*k+O*(k+t)) - O*(2*k+t) = k := by ring

/-- Exact-zero replay is unnecessary after a proved zero sentinel if ReLU
is enabled. This does not identify whether a computed zero is genuine. -/
theorem relu_signed_zero (negative : Bool) :
    ExactRuntime.act true (if negative then (0x80000000 : UInt32) else 0) = 0 := by
  cases negative <;> decide

/-- A different dense-work elimination route if bilinear full cost fails:
an exact upper tail bound certifies nonpositivity before visiting the tail.
The FloatLib/ReLU bridge and a cheap native bound representation remain open. -/
theorem nonpositive_tail_certificate (prefixValue tail upper : Int)
    (hTail : |tail| ≤ upper) (hGate : prefixValue+upper ≤ 0) :
    prefixValue+tail ≤ 0 := by
  have ht : tail ≤ upper := (le_abs_self tail).trans hTail
  omega

end WinogradFollowOn
