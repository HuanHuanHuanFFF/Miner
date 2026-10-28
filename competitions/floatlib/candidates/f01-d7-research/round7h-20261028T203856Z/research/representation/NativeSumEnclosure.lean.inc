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
  simpa only [ExecFloat.Binary.toModel_ofFloat] using
    ExecFloat.Binary.toModel_ofFloat_add_of_isFinite x y hx hy

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
  have hfmt : FLTFormat (β := FloatLib.Numerics.binaryRadix) (-1074) 53
      ((j : ℝ) * p2 k) := by
    refine ⟨by norm_num, ⟨(j : Int), k⟩, ?_, ?_, by omega⟩
    · simp only [FloatLib.Floats.Formats.Flocq.toReal, Int.cast_natCast]
      rfl
    · change j < 2 ^ 53
      exact lt_of_le_of_lt hj (by decide)
  apply round_preserves_generic
  exact generic_of_fltFormat (-1074) 53 (by norm_num) _ hfmt

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
    · convert hout.2.1 using 1 <;> simp only [List.length_cons] <;> push_cast <;> ring
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

theorem actual_sum_enclosure (xs : List Float) (L : Nat) (k : Int)
    (hklo : -250 ≤ k) (hkhi : k ≤ 256) (hL : L ≤ 30)
    (hcount : xs.length ≤ 2 ^ L)
    (hxs : ∀ x ∈ xs, x.isFinite = true ∧
      |Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat x))| < p2 k) :
    (sum xs).isFinite = true ∧
      |Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat (sum xs))) -
        (xs.map (fun x => Model.toReal (ExecFloat.Binary.toModel (ExecFloat.Binary.ofFloat x)))).sum|
        ≤ p2 (k + 2 * (L : Int) - 53) := by
  have hx : ∀ x ∈ xs, x.isFinite = true ∧ |rval x| < p2 k := by
    simpa only [ExecFloat.Binary.toModel_ofFloat, rval] using hxs
  simpa only [ExecFloat.Binary.toModel_ofFloat, rval, exactSum] using
    sum_enclosure xs L k hklo hkhi hL hcount hx

end Submission.R24RepresentationSum
