import ContractExact

/- R24 portable actual Float64 fold. Input values are arbitrary finite Float
   values, bounded by a power of two; no widening or multiplication theorem is
   assumed. New declarations are NOT_RUN until the fixed helper gate checks them. -/
namespace Submission.R24RepresentationSum
open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange
open FloatLib.Floats.Formats.Flocq

abbrev native (x : Float) : Model FloatFormat.binary64 := Model.ofFloatModel x.toModel
noncomputable def rval (x : Float) : ℝ := Model.toReal (native x)
noncomputable def p2 (e : Int) : ℝ := bpow FloatLib.Numerics.binaryRadix e
noncomputable def exactSum (xs : List Float) : ℝ := (xs.map rval).sum

def loop : List Float → Float → Float
  | [], acc => acc
  | x :: xs, acc => loop xs (acc + x)

def sum (xs : List Float) : Float := loop xs (Float.ofBits 0)

theorem p2_pos (e : Int) : 0 < p2 e := bpow.pos _ _

theorem p2_mono {a b : Int} (h : a ≤ b) : p2 a ≤ p2 b :=
  (bpow_le_bpow_iff FloatLib.Numerics.binaryRadix a b).2 h

theorem p2_add (a b : Int) : p2 (a + b) = p2 a * p2 b :=
  bpow.add_exp _ _ _

theorem p2_nat (n : Nat) : p2 (n : Int) = ((2 ^ n : Nat) : ℝ) := by
  simp [p2, bpow, FloatLib.Numerics.binaryRadix, FloatLib.Numerics.Radix.toReal]

theorem scaled_count_le (j L : Nat) (k : Int) (hj : j ≤ 2 ^ L) :
    (j : ℝ) * p2 k ≤ p2 (k + (L : Int)) := by
  have hjR : (j : ℝ) ≤ ((2 ^ L : Nat) : ℝ) := by exact_mod_cast hj
  calc
    (j : ℝ) * p2 k ≤ ((2 ^ L : Nat) : ℝ) * p2 k :=
      mul_le_mul_of_nonneg_right hjR (p2_pos k).le
    _ = p2 (k + (L : Int)) := by
      rw [← p2_nat, ← p2_add]
      congr 1
      omega

theorem native_finite_eq (x : Float) : Model.isFinite (native x) = x.isFinite := by
  rw [← Model.toDyadic?_isSome_eq_isFinite,
    Model.toDyadic?_ieee_eq_model FloatFormat.binary64 (by decide),
    Model.toModel_ofFloatModel]
  change (Model.unpackedToDyadic? x.toModel.unpack).isSome = x.toModel.unpack.isFinite
  cases x.toModel.unpack <;> rfl

theorem native_add (x y : Float) (hx : x.isFinite = true) (hy : y.isFinite = true) :
    native (x + y) = Model.add (native x) (native y) := by
  change Model.ofFloatModel (Float.Model.add x.toModel y.toModel) = _
  rw [Float.Model.add, Model.ofFloatModel_pack]
  have h := Model.add_eq_ofModel_add_of_isFinite (fmt := FloatFormat.binary64)
    (by decide) (Model.ofFloatModel x.toModel) (Model.ofFloatModel y.toModel)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hx)
    (by simpa only [Model.toModel_ofFloatModel, Float.isFinite,
      Float.Model.isFinite] using hy)
  rw [Model.toModel_ofFloatModel, Model.toModel_ofFloatModel] at h
  exact h.symm

theorem max_finite_large : p2 286 ≤ Model.toReal (Model.posMaxFinite FloatFormat.binary64) := by
  change p2 286 ≤ Model.toReal
    (Model.ofFields FloatFormat.binary64 false 2046 4503599627370495)
  rw [Model.toReal_ofFields_normal FloatFormat.binary64 false 2046 4503599627370495
    (by decide) (by decide) (by decide)]
  change p2 286 ≤ (1 : ℝ) * 9007199254740991 * p2 971
  rw [one_mul]
  have hpow : p2 286 ≤ p2 971 := p2_mono (by omega)
  have hp := p2_pos 971
  nlinarith

theorem native_add_finite_real (x y : Float)
    (hx : x.isFinite = true) (hy : y.isFinite = true)
    (hb : |rval x| + |rval y| ≤ p2 286) :
    (x + y).isFinite = true ∧
      rval (x + y) = Model.roundAt FloatFormat.binary64 (rval x + rval y) := by
  have hxm : Model.isFinite (native x) = true := by rw [native_finite_eq, hx]
  have hym : Model.isFinite (native y) = true := by rw [native_finite_eq, hy]
  have hbm : |Model.toReal (native x)| + |Model.toReal (native y)| ≤
      Model.toReal (Model.posMaxFinite FloatFormat.binary64) := hb.trans max_finite_large
  constructor
  · rw [← native_finite_eq, native_add x y hx hy]
    exact Model.isFinite_add_of_abs_add_le_posMaxFinite (native x) (native y)
      (by decide) hxm hym hbm
  · change Model.toReal (native (x + y)) =
      Model.roundAt FloatFormat.binary64 (Model.toReal (native x) + Model.toReal (native y))
    rw [native_add x y hx hy]
    exact Model.toReal_add_eq_roundAt_of_abs_add_le_posMaxFinite (native x) (native y)
      (by decide) hxm hym hbm

/- A bounded integer times the given power of two belongs to the actual
   binary64 gradual-underflow grid. This closes the j*M exactness premise. -/
theorem round_grid (j : Nat) (k : Int) (hj : j ≤ 2 ^ 30) (hk : -250 ≤ k) :
    Model.roundAt FloatFormat.binary64 ((j : ℝ) * p2 k) = (j : ℝ) * p2 k := by
  let d : FloatLib.Numerics.Dyadic := ⟨false, j, k⟩
  have hs : d.significand < 2 ^ (FloatFormat.binary64.fracWidth + 1) := by
    change j < 2 ^ 53
    exact lt_of_le_of_lt hj (by norm_num)
  have he : FloatFormat.binary64.minSubnormalExponent ≤ d.exponent := by
    change (-1074 : Int) ≤ k
    omega
  have hg := Model.Dyadic.genericFormat_of_significand_lt FloatFormat.binary64 d hs he
  have hv : d.toReal = (j : ℝ) * p2 k := by
    change (FloatLib.Numerics.Dyadic.mk false j k).toReal = _
    rw [FloatLib.Numerics.Dyadic.toReal_mk_false]
    rfl
  rw [hv] at hg
  exact round_preserves_generic nearestEven _ hg

/- This is obtained from the library's real RNE half-ULP bound, not assumed
   as a property of a hypothetical step operation. The looser full-ULP
   bound deliberately avoids extra one-bit engineering. -/
theorem round_error_power (x : ℝ) (K : Int) (hK : -250 ≤ K) (hx : |x| < p2 K) :
    |Model.roundAt FloatFormat.binary64 x - x| ≤ p2 (K - 53) := by
  by_cases hz : x = 0
  · subst x
    rw [Model.roundAt_zero, sub_self, abs_zero]
    exact (p2_pos _).le
  · have hm : magnitude FloatLib.Numerics.binaryRadix x ≤ K :=
      magnitude_le_of_abs_lt_bpow _ _ _ hz hx
    have hc : cexp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x ≤
        K - 53 := by
      change max (magnitude FloatLib.Numerics.binaryRadix x - 53) (-1074) ≤ K - 53
      exact max_le (by omega) (by omega)
    have hu : ulp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x ≤
        p2 (K - 53) := by
      rw [ulp.of_ne_zero _ _ _ hz]
      exact p2_mono hc
    have he := error_bound_ulp (β := FloatLib.Numerics.binaryRadix)
      (fexp := Model.fexpOf FloatFormat.binary64) nearestEven x
    have hn := ulp.nonneg FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x
    change |Model.roundAt FloatFormat.binary64 x - x| ≤
      ulp FloatLib.Numerics.binaryRadix (Model.fexpOf FloatFormat.binary64) x / 2 at he
    exact he.trans (by linarith)

theorem exactSum_nil : exactSum [] = 0 := rfl
theorem exactSum_cons (x : Float) (xs : List Float) :
    exactSum (x :: xs) = rval x + exactSum xs := rfl

theorem zero_native : native (Float.ofBits 0) = Model.zero FloatFormat.binary64 false := by
  decide

theorem zero_value : rval (Float.ofBits 0) = 0 := by
  unfold rval
  rw [zero_native, Model.toReal_zero]

theorem zero_finite : (Float.ofBits 0).isFinite = true := by decide

/- Actual loop invariant: the native addition, result finiteness, real RNE
   step, exact grid bounds, and local error are all proved inside the step. -/
theorem loop_invariant (xs : List Float) (acc : Float) (j L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hcount : j + xs.length ≤ 2 ^ L)
    (hacc : acc.isFinite = true) (hmag : |rval acc| ≤ (j : ℝ) * p2 k)
    (hxs : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k) :
    (loop xs acc).isFinite = true ∧
      |rval (loop xs acc)| ≤ ((j + xs.length : Nat) : ℝ) * p2 k ∧
      |rval (loop xs acc) - (rval acc + exactSum xs)| ≤
        (xs.length : ℝ) * p2 (k + (L : Int) - 53) := by
  induction xs generalizing acc j with
  | nil =>
    simpa only [loop, List.length_nil, Nat.add_zero, exactSum_nil, add_zero,
      sub_self, abs_zero, Nat.cast_zero, zero_mul, le_refl, and_true] using And.intro hacc hmag
  | cons x xs ih =>
    have hx := hxs x (by simp)
    have htail : ∀ y ∈ xs, y.isFinite = true ∧ |rval y| < p2 k := by
      intro y hy
      exact hxs y (by simp [hy])
    have hj : j + 1 ≤ 2 ^ L := by simp only [List.length_cons] at hcount; omega
    have hj30 : j + 1 ≤ 2 ^ 30 :=
      hj.trans (Nat.pow_le_pow_right (by decide) hL)
    have hnextCount : (j + 1) + xs.length ≤ 2 ^ L := by
      simp only [List.length_cons] at hcount
      omega
    have htri : |rval acc| + |rval x| < ((j + 1 : Nat) : ℝ) * p2 k := by
      have hh := add_lt_add_of_le_of_lt hmag hx.2
      convert hh using 1 <;> push_cast <;> ring
    have hglobal : ((j + 1 : Nat) : ℝ) * p2 k ≤ p2 (k + (L : Int)) :=
      scaled_count_le _ _ _ hj
    have htop : p2 (k + (L : Int)) ≤ p2 286 := p2_mono (by omega)
    have hstep := native_add_finite_real acc x hacc hx.1
      (htri.le.trans (hglobal.trans htop))
    have hinput : |rval acc + rval x| < ((j + 1 : Nat) : ℝ) * p2 k :=
      (abs_add_le _ _).trans_lt htri
    have hgrid := round_grid (j + 1) k hj30 hklo
    have hnextMag : |rval (acc + x)| ≤ ((j + 1 : Nat) : ℝ) * p2 k := by
      rw [hstep.2]
      obtain ⟨hlo, hhi⟩ := abs_le.mp hinput.le
      have a := Model.roundAt_mono FloatFormat.binary64 hlo
      have b := Model.roundAt_mono FloatFormat.binary64 hhi
      rw [Model.roundAt_neg, hgrid] at a
      rw [hgrid] at b
      exact abs_le.mpr ⟨a, b⟩
    have herr : |rval (acc + x) - (rval acc + rval x)| ≤
        p2 (k + (L : Int) - 53) := by
      rw [hstep.2]
      exact round_error_power _ _ (by omega) (hinput.trans_le hglobal)
    have hout := ih (acc + x) (j + 1) hnextCount hstep.1 hnextMag htail
    refine ⟨hout.1, ?_, ?_⟩
    · simpa only [loop, List.length_cons, Nat.add_assoc, Nat.add_comm, Nat.add_left_comm]
        using hout.2.1
    · have heq : rval (loop xs (acc + x)) - (rval acc + exactSum (x :: xs)) =
          (rval (loop xs (acc + x)) - (rval (acc + x) + exactSum xs)) +
            (rval (acc + x) - (rval acc + rval x)) := by
        rw [exactSum_cons]
        ring
      change |rval (loop xs (acc + x)) - (rval acc + exactSum (x :: xs))| ≤ _
      rw [heq]
      calc
        _ ≤ |rval (loop xs (acc + x)) - (rval (acc + x) + exactSum xs)| +
              |rval (acc + x) - (rval acc + rval x)| := abs_add_le _ _
        _ ≤ (xs.length : ℝ) * p2 (k + (L : Int) - 53) +
              p2 (k + (L : Int) - 53) := add_le_add hout.2.2 herr
        _ = ((x :: xs).length : ℝ) * p2 (k + (L : Int) - 53) := by
          simp only [List.length_cons, Nat.cast_add, Nat.cast_one]
          ring

theorem sum_enclosure (xs : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hcount : xs.length ≤ 2 ^ L)
    (hxs : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k) :
    (sum xs).isFinite = true ∧
      |rval (sum xs) - exactSum xs| ≤ p2 (k + 2 * (L : Int) - 53) := by
  have h := loop_invariant xs (Float.ofBits 0) 0 L k hklo hkhi hL
    (by simpa using hcount) zero_finite (by simp [zero_value]) hxs
  refine ⟨h.1, ?_⟩
  have he : |rval (sum xs) - exactSum xs| ≤
      (xs.length : ℝ) * p2 (k + (L : Int) - 53) := by
    simpa only [sum, zero_value, zero_add] using h.2.2
  have hc : (xs.length : ℝ) ≤ ((2 ^ L : Nat) : ℝ) := by exact_mod_cast hcount
  calc
    _ ≤ (xs.length : ℝ) * p2 (k + (L : Int) - 53) := he
    _ ≤ ((2 ^ L : Nat) : ℝ) * p2 (k + (L : Int) - 53) :=
      mul_le_mul_of_nonneg_right hc (p2_pos _).le
    _ = p2 (k + 2 * (L : Int) - 53) := by
      rw [← p2_nat, ← p2_add]
      congr 1
      ring

end Submission.R24RepresentationSum

/- Four native Float64 fold results can be merged under the existing radius.
   Array-lane partition, runtime selection, and full kernels remain separate. -/
namespace Submission.R27FourChain
open FloatLib.Floats FloatLib.Floats.Formats.BinaryInterchange
open Submission.R24RepresentationSum

private theorem p2_one : p2 1 = (2 : Real) := by simpa using p2_nat 1
private theorem p2_two : p2 2 = (4 : Real) := by simpa using p2_nat 2
private theorem p2_three : p2 3 = (8 : Real) := by simpa using p2_nat 3

/-- A native merge preserves the exact count-grid magnitude bound. -/
theorem merge_grid (a b : Float) (i j L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hc : i + j ≤ 2 ^ L)
    (ha : a.isFinite = true) (hb : b.isFinite = true)
    (hma : |rval a| ≤ (i : Real) * p2 k)
    (hmb : |rval b| ≤ (j : Real) * p2 k) :
    (a + b).isFinite = true ∧
      |rval (a + b)| ≤ ((i + j : Nat) : Real) * p2 k ∧
      |rval (a + b) - (rval a + rval b)| ≤ p2 (k + (L : Int) - 52) := by
  have hpre : |rval a| + |rval b| ≤ ((i + j : Nat) : Real) * p2 k := by
    convert add_le_add hma hmb using 1 <;> push_cast <;> ring
  have hglobal := scaled_count_le (i + j) L k hc
  have htop : p2 (k + (L : Int)) ≤ p2 286 := p2_mono (by omega)
  have step := native_add_finite_real a b ha hb (hpre.trans (hglobal.trans htop))
  have hinput : |rval a + rval b| ≤ ((i + j : Nat) : Real) * p2 k :=
    (abs_add_le _ _).trans hpre
  have hc30 : i + j ≤ 2 ^ 30 := hc.trans (Nat.pow_le_pow_right (by decide) hL)
  have grid := round_grid (i + j) k hc30 hklo
  have hmag : |rval (a + b)| ≤ ((i + j : Nat) : Real) * p2 k := by
    rw [step.2]
    obtain ⟨hl, hu⟩ := abs_le.mp hinput
    have lo := Model.roundAt_mono FloatFormat.binary64 hl
    have hi := Model.roundAt_mono FloatFormat.binary64 hu
    rw [Model.roundAt_neg, grid] at lo
    rw [grid] at hi
    exact abs_le.mpr ⟨lo, hi⟩
  have hpower : p2 (k + (L : Int)) < p2 (k + (L : Int) + 1) := by
    rw [p2_add (k + (L : Int)) 1, p2_one]
    have hp := p2_pos (k + (L : Int))
    nlinarith
  have herr := round_error_power (rval a + rval b) (k + (L : Int) + 1)
    (by omega) ((hinput.trans hglobal).trans_lt hpower)
  have hshift : k + (L : Int) + 1 - 53 = k + (L : Int) - 52 := by omega
  refine ⟨step.1, hmag, ?_⟩
  rw [step.2, ← hshift]
  exact herr

private theorem merge_error (a b : Float) (A B E ea eb : Real)
    (h : |rval (a + b) - (rval a + rval b)| ≤ E)
    (ha : |rval a - A| ≤ ea) (hb : |rval b - B| ≤ eb) :
    |rval (a + b) - (A + B)| ≤ E + ea + eb := by
  have heq : rval (a + b) - (A + B) =
      (rval (a + b) - (rval a + rval b)) + ((rval a - A) + (rval b - B)) := by ring
  rw [heq]
  calc
    _ ≤ |rval (a + b) - (rval a + rval b)| + |(rval a - A) + (rval b - B)| := abs_add_le _ _
    _ ≤ E + (ea + eb) := add_le_add h ((abs_add_le _ _).trans (add_le_add ha hb))
    _ = E + ea + eb := by ring

private theorem sum_info (xs : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hc : xs.length ≤ 2 ^ L)
    (hx : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k) :
    (sum xs).isFinite = true ∧ |rval (sum xs)| ≤ (xs.length : Real) * p2 k ∧
      |rval (sum xs) - exactSum xs| ≤ p2 (k + 2 * (L : Int) - 53) := by
  have he := sum_enclosure xs L k hklo hkhi hL hc hx
  have hm := loop_invariant xs (Float.ofBits 0) 0 L k hklo hkhi hL
    (by simpa using hc) zero_finite (by simp [zero_value]) hx
  exact ⟨he.1, by simpa only [sum, Nat.zero_add] using hm.2.1, he.2⟩

/-- Four partitioned native folds need at most half the old radius when L>=5. The final target is the exact sum
    of all four lane targets; no native associativity assumption is used. -/
theorem four_sums_half_radius (x0 x1 x2 x3 : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hLlo : 5 ≤ L) (hLhi : L ≤ 30)
    (hc0 : x0.length ≤ 2 ^ (L - 2)) (hc1 : x1.length ≤ 2 ^ (L - 2))
    (hc2 : x2.length ≤ 2 ^ (L - 2)) (hc3 : x3.length ≤ 2 ^ (L - 2))
    (hx0 : ∀ x ∈ x0, x.isFinite = true ∧ |rval x| < p2 k)
    (hx1 : ∀ x ∈ x1, x.isFinite = true ∧ |rval x| < p2 k)
    (hx2 : ∀ x ∈ x2, x.isFinite = true ∧ |rval x| < p2 k)
    (hx3 : ∀ x ∈ x3, x.isFinite = true ∧ |rval x| < p2 k) :
    ((sum x0 + sum x1) + (sum x2 + sum x3)).isFinite = true ∧
      |rval ((sum x0 + sum x1) + (sum x2 + sum x3)) -
        ((exactSum x0 + exactSum x1) + (exactSum x2 + exactSum x3))| ≤
          p2 (k + 2 * (L : Int) - 54) := by
  have hLs : L - 2 ≤ 30 := by omega
  have s0 := sum_info x0 (L - 2) k hklo hkhi hLs hc0 hx0
  have s1 := sum_info x1 (L - 2) k hklo hkhi hLs hc1 hx1
  have s2 := sum_info x2 (L - 2) k hklo hkhi hLs hc2 hx2
  have s3 := sum_info x3 (L - 2) k hklo hkhi hLs hc3 hx3
  have hp : 4 * 2 ^ (L - 2) = 2 ^ L := by
    have hsplit : L = (L - 2) + 2 := by omega
    conv_rhs => rw [hsplit, Nat.pow_add]
    norm_num <;> ring
  have hcount : (x0.length + x1.length) + (x2.length + x3.length) ≤ 2 ^ L := by omega
  have p01 := merge_grid (sum x0) (sum x1) x0.length x1.length L k
    hklo hkhi hLhi (by omega) s0.1 s1.1 s0.2.1 s1.2.1
  have p23 := merge_grid (sum x2) (sum x3) x2.length x3.length L k
    hklo hkhi hLhi (by omega) s2.1 s3.1 s2.2.1 s3.2.1
  have pAll := merge_grid (sum x0 + sum x1) (sum x2 + sum x3)
    (x0.length + x1.length) (x2.length + x3.length) L k hklo hkhi hLhi
    hcount p01.1 p23.1 p01.2.1 p23.2.1
  let G := p2 (k + 2 * ((L - 2 : Nat) : Int) - 53)
  let J := p2 (k + (L : Int) - 52)
  have e01 := merge_error (sum x0) (sum x1) (exactSum x0) (exactSum x1)
    J G G p01.2.2 s0.2.2 s1.2.2
  have e23 := merge_error (sum x2) (sum x3) (exactSum x2) (exactSum x3)
    J G G p23.2.2 s2.2.2 s3.2.2
  have eAll := merge_error (sum x0 + sum x1) (sum x2 + sum x3)
    (exactSum x0 + exactSum x1) (exactSum x2 + exactSum x3)
    J (J + G + G) (J + G + G) pAll.2.2 e01 e23
  have hJ : J ≤ G := p2_mono (by omega)
  have hGp : 0 < G := p2_pos _
  have hR : p2 (k + 2 * (L : Int) - 54) = 8 * G := by
    rw [show k + 2 * (L : Int) - 54 =
      (k + 2 * ((L - 2 : Nat) : Int) - 53) + 3 by omega, p2_add, p2_three]
    dsimp [G]
    ring
  refine ⟨pAll.1, eAll.trans ?_⟩
  rw [hR]
  linarith

end Submission.R27FourChain
