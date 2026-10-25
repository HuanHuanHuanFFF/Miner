/- Draft / NOT_RUN. Connect exact aligned finite addition to the public Model.add.
   Needs R14WordAddAlignment.spec_add_of_decodes and R14NatNormal.model_round_normal.
   Explicit finite decodes preserve original input order at the public boundary. -/
namespace Submission.R14WordAddAlignment

open FloatLib.Floats
open FloatLib.Floats.Formats.BinaryInterchange

theorem spec_add_normal (x y : Model FloatFormat.binary32)
    (dx dy : FloatLib.Numerics.Dyadic) (sign : Bool) (n elo : Nat)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy)
    (hsum : Model.addDyadic dx dy =
      { negative := sign, significand := n, exponent := (elo : Int) - 150 })
    (hn : n ≠ 0) (hh : 24 ≤ n.log2) (helo : 1 ≤ elo)
    (hupper : n.log2 + elo - 23 + R14NatNormal.carry n ≤ 254) :
    Model.Spec.add x y = Model.ofFields FloatFormat.binary32 sign
      (n.log2 + elo - 23 + R14NatNormal.carry n)
      (R14NatNormal.mantissa n - 8388608) := by
  have hmin : -126 ≤ (n.log2 : Int) + ((elo : Int) - 150) := by omega
  have hmax : (n.log2 : Int) + ((elo : Int) - 150) +
      (R14NatNormal.carry n : Int) ≤ 127 := by omega
  have hexp : Int.toNat ((n.log2 : Int) + ((elo : Int) - 150) +
      (R14NatNormal.carry n : Int) + 127) =
      n.log2 + elo - 23 + R14NatNormal.carry n := by omega
  rw [spec_add_of_decodes x y dx dy hx hy, hsum,
    R14NatNormal.model_round_normal sign n ((elo : Int) - 150) hn
      (by omega) hmin hmax, hexp]

theorem model_add_normal (x y : Model FloatFormat.binary32)
    (dx dy : FloatLib.Numerics.Dyadic) (sign : Bool) (n elo : Nat)
    (hx : Model.toDyadic? x = some dx) (hy : Model.toDyadic? y = some dy)
    (hsum : Model.addDyadic dx dy =
      { negative := sign, significand := n, exponent := (elo : Int) - 150 })
    (hn : n ≠ 0) (hh : 24 ≤ n.log2) (helo : 1 ≤ elo)
    (hupper : n.log2 + elo - 23 + R14NatNormal.carry n ≤ 254) :
    Model.add x y = Model.ofFields FloatFormat.binary32 sign
      (n.log2 + elo - 23 + R14NatNormal.carry n)
      (R14NatNormal.mantissa n - 8388608) := by
  rw [Model.Proof.add_eq_spec]
  exact spec_add_normal x y dx dy sign n elo hx hy hsum hn hh helo hupper

end Submission.R14WordAddAlignment
