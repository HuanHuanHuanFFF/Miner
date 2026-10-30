import ContractExact

namespace Submission.R27MulHigh

def low (a : Nat) : Nat := a % 4294967296
def high (a : Nat) : Nat := a / 4294967296

def highProduct (a b : Nat) : Nat :=
  let p := low a * low b
  let u := high a * low b + high p
  let v := low a * high b + low u
  high a * high b + high u + high v

def lowProduct (a b : Nat) : Nat :=
  let p := low a * low b
  let u := high a * low b + high p
  let v := low a * high b + low u
  low p + low v * 4294967296

theorem split (a : Nat) : low a + high a * 4294967296 = a := by
  simpa only [low, high, Nat.mul_comm] using Nat.mod_add_div a 4294967296

theorem product_identity (a b : Nat) :
    highProduct a b * 18446744073709551616 + lowProduct a b = a * b := by
  have ha := split a
  have hb := split b
  let p := low a * low b
  let u := high a * low b + high p
  let v := low a * high b + low u
  have hp := split p
  have hu := split u
  have hv := split v
  change (high a * high b + high u + high v) * 18446744073709551616 +
    (low p + low v * 4294967296) = a * b
  calc
    _ = low p + v * 4294967296 +
        (high a * high b + high u) * 18446744073709551616 := by
      omega
    _ = low p + u * 4294967296 + low a * high b * 4294967296 +
        high a * high b * 18446744073709551616 := by
      dsimp only [v]
      omega
    _ = p + (high a * low b + low a * high b) * 4294967296 +
        high a * high b * 18446744073709551616 := by
      dsimp only [u]
      omega
    _ = (low a + high a * 4294967296) *
        (low b + high b * 4294967296) := by dsimp only [p]; ring
    _ = a * b := by rw [ha, hb]

theorem lowProduct_bound (a b : Nat) : lowProduct a b < 18446744073709551616 := by
  have hp := Nat.mod_lt (low a * low b) (by decide : 0 < 4294967296)
  have hv := Nat.mod_lt
    (low a * high b + low (high a * low b + high (low a * low b)))
    (by decide : 0 < 4294967296)
  unfold lowProduct low at *
  omega

theorem highProduct_exact (a b : Nat) :
    highProduct a b = a * b / 18446744073709551616 := by
  have he := product_identity a b
  have hl := lowProduct_bound a b
  omega

end Submission.R27MulHigh
