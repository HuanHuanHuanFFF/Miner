/- R15 development: a different normal-MUL rounding runtime, proved by equality
   to the already full-gated R14 rounder. No new bias/RNE identity is assumed.
   The three UInt64 flags use 0/1 and bitwise operations so the generated code
   can materialize comparisons rather than follow the old nested return tree.
   Actual machine shape and complete performance are NOT_RUN. -/
namespace R15BranchlessNormal

@[inline] def round (value shift : UInt64) : UInt64 :=
  let q := value >>> shift
  let r := value &&& ((1 <<< shift) - 1)
  let half := (1 : UInt64) <<< (shift - 1)
  let notLess : UInt64 := if r < half then 0 else 1
  let greater : UInt64 := if r > half then 1 else 0
  let odd : UInt64 := if (q &&& 1) == 0 then 0 else 1
  q + (notLess &&& (greater ||| odd))

theorem round_eq_rse (value shift : UInt64) :
    round value shift = FastMul.rse value shift := by
  unfold round FastMul.rse
  dsimp only
  split <;> split <;> split <;> simp_all

@[inline] def roundedWord (u v : UInt32) : UInt64 :=
  let product := R14DIntegerNormal.productWord u v
  if R14DIntegerNormal.shiftWord u v = 23 then round product 23
  else round product 24

theorem roundedWord_eq (u v : UInt32) :
    roundedWord u v = R14DIntegerNormal.roundedWord u v := by
  rcases R14DIntegerNormal.shiftWord_values u v with h | h
  · simp [roundedWord, h, round_eq_rse, R14DIntegerNormal.roundedWord, FastMul.rseAny]
  · simp [roundedWord, h, round_eq_rse, R14DIntegerNormal.roundedWord, FastMul.rseAny]

@[inline] def core (u v : UInt32) : UInt32 :=
  let rounded := roundedWord u v
  let high := R14DIntegerNormal.highWord u v
  let carry := rounded >>> 24
  FastMul.mkW (R14ExponentShift.sign u v)
    (R14ExponentShift.ex u + R14ExponentShift.ex v - 127 +
      high.toUInt32 + carry.toUInt32)
    (rounded.toUInt32 &&& 0x007fffff)

theorem core_eq (u v : UInt32) : core u v = R14DIntegerNormal.core u v := by
  simp only [core, roundedWord_eq, R14DIntegerNormal.core,
    R14DIntegerNormal.exponentWord, R14DIntegerNormal.fractionWord,
    R14DIntegerNormal.carryWord]

@[inline] def guardedMul (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) : Binary32 :=
  if R14ExponentShift.eligible x.raw.1 y.raw.1 then
    R7W02.fromRaw (core x.raw.1 y.raw.1)
  else fallback x y

theorem guardedMul_eq (fallback : Binary32 → Binary32 → Binary32)
    (x y : Binary32) :
    guardedMul fallback x y = R14ExponentShift.guardedMul fallback x y := by
  unfold guardedMul R14ExponentShift.guardedMul R14ExponentShift.core
  rw [core_eq]

end R15BranchlessNormal

@[inline] def mul (x y : Binary32) : Binary32 :=
  R15BranchlessNormal.guardedMul mulBeforeExponent x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  rw [mul, R15BranchlessNormal.guardedMul_eq]
  exact R14ExponentShift.guardedMul_spec mulBeforeExponent mulBeforeExponent_spec x y
