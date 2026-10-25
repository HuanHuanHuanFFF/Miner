/-
R14 integer mul review: replacement proof fragment, NOT_RUN.

Base SHA256:
6f8808d0a6ea0c05e0ba2416a583e5ce388fa75f2ce62b04c408d2699b048dc3

Inside the existing namespace Submission.R14DIntegerNormal, replace only
the core_word declaration (original lines 3634-3650) with the theorem below.
Do not append a second declaration or add another namespace wrapper.
The sole substantive edit is FastMul.mkW_eq -> FastMul.mkW_ofNat.
All runtime definitions remain byte-identical. This fragment has no imports
and depends on the declarations already present before the replacement site.
-/

theorem core_word (u v : UInt32)
    (hs : 128 ≤ R2W01c.wordExp u + R2W01c.wordExp v) :
    core u v = Model.NativeBinary32.mkBits
      (Bool.xor (R2W01c.wordSign u) (R2W01c.wordSign v))
      (R14ExponentShift.middleExponent (productNat u v) +
        R2W01c.wordExp u + R2W01c.wordExp v - 300)
      (R14ExponentShift.storedFraction (productNat u v)) := by
  calc
    core u v = FastMul.mkW (R14ExponentShift.sign u v)
        (UInt32.ofNat (exponentWord u v).toNat)
        (UInt32.ofNat (fractionWord u v).toNat) := by
          rw [UInt32.ofNat_toNat, UInt32.ofNat_toNat]
          rfl
    _ = Model.NativeBinary32.mkBits (R14ExponentShift.sign u v)
        (exponentWord u v).toNat (fractionWord u v).toNat :=
          FastMul.mkW_ofNat _ _ _
    _ = _ := by rw [exponentWord_nat u v hs, fractionWord_nat, R14ExponentShift.sign_eq]
