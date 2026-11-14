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

namespace Submission.R27MulHigh

theorem native_bounds (a b : Nat) (ha : a < 18446744073709551616)
    (hb : b < 18446744073709551616) :
    let p := low a * low b
    let u := high a * low b + high p
    let v := low a * high b + low u
    p < 18446744073709551616 ∧
    high a * low b < 18446744073709551616 ∧
    low a * high b < 18446744073709551616 ∧
    high a * high b < 18446744073709551616 ∧
    u < 18446744073709551616 ∧ v < 18446744073709551616 ∧
    high a * high b + high u + high v < 18446744073709551616 := by
  have ha0 : low a < 4294967296 := Nat.mod_lt _ (by decide)
  have hb0 : low b < 4294967296 := Nat.mod_lt _ (by decide)
  have ha1 : high a < 4294967296 := by change a / 4294967296 < 4294967296; omega
  have hb1 : high b < 4294967296 := by change b / 4294967296 < 4294967296; omega
  have bound : ∀ x y : Nat, x < 4294967296 → y < 4294967296 →
      x * y ≤ 18446744065119617025 := by
    intro x y hx hy
    have h := Nat.mul_le_mul (show x ≤ 4294967295 by omega)
      (show y ≤ 4294967295 by omega)
    exact h
  have hp := bound _ _ ha0 hb0
  have hab := bound _ _ ha1 hb0
  have hba := bound _ _ ha0 hb1
  have hhh := bound _ _ ha1 hb1
  have hph : high (low a * low b) < 4294967296 := by
    change (low a * low b) / 4294967296 < 4294967296
    omega
  have hu : high a * low b + high (low a * low b) < 18446744073709551616 := by omega
  have hul : low (high a * low b + high (low a * low b)) < 4294967296 :=
    Nat.mod_lt _ (by decide)
  have hv : low a * high b + low (high a * low b + high (low a * low b)) <
      18446744073709551616 := by omega
  have huh : high (high a * low b + high (low a * low b)) < 4294967296 := by
    change (high a * low b + high (low a * low b)) / 4294967296 < 4294967296
    omega
  have hvh : high (low a * high b + low (high a * low b + high (low a * low b))) <
      4294967296 := by
    change (low a * high b + low (high a * low b + high (low a * low b))) /
      4294967296 < 4294967296
    omega
  dsimp only
  exact ⟨by omega, by omega, by omega, by omega, hu, hv, by omega⟩

@[inline] def lowWord (a : UInt64) : UInt64 := a.toUInt32.toUInt64
@[inline] def highWord (a : UInt64) : UInt64 := a >>> 32

theorem lowWord_value (a : UInt64) : (lowWord a).toNat = low a.toNat := by
  simp only [lowWord, UInt32.toNat_toUInt64, UInt64.toNat_toUInt32]
  rfl

theorem highWord_value (a : UInt64) : (highWord a).toNat = high a.toNat := by
  simp only [highWord, UInt64.toNat_shiftRight, Nat.shiftRight_eq_div_pow]
  rfl

@[inline] def mulHigh (a b : UInt64) : UInt64 :=
  let p := lowWord a * lowWord b
  let u := highWord a * lowWord b + highWord p
  let v := lowWord a * highWord b + lowWord u
  highWord a * highWord b + highWord u + highWord v

theorem mulHigh_exact (a b : UInt64) :
    (mulHigh a b).toNat = a.toNat * b.toNat / 18446744073709551616 := by
  have hb := native_bounds a.toNat b.toNat a.toNat_lt b.toNat_lt
  dsimp only at hb
  obtain ⟨hp0, hab0, hba0, hhh0, hu0, hv0, htop⟩ := hb
  have hp : (lowWord a * lowWord b).toNat = low a.toNat * low b.toNat := by
    rw [UInt64.toNat_mul, lowWord_value, lowWord_value, Nat.mod_eq_of_lt hp0]
  have hab : (highWord a * lowWord b).toNat = high a.toNat * low b.toNat := by
    rw [UInt64.toNat_mul, highWord_value, lowWord_value, Nat.mod_eq_of_lt hab0]
  have hba : (lowWord a * highWord b).toNat = low a.toNat * high b.toNat := by
    rw [UInt64.toNat_mul, lowWord_value, highWord_value, Nat.mod_eq_of_lt hba0]
  have hhh : (highWord a * highWord b).toNat = high a.toNat * high b.toNat := by
    rw [UInt64.toNat_mul, highWord_value, highWord_value, Nat.mod_eq_of_lt hhh0]
  let u := highWord a * lowWord b + highWord (lowWord a * lowWord b)
  have hu : u.toNat = high a.toNat * low b.toNat + high (low a.toNat * low b.toNat) := by
    dsimp only [u]
    rw [UInt64.toNat_add, hab, highWord_value, hp, Nat.mod_eq_of_lt hu0]
  let v := lowWord a * highWord b + lowWord u
  have hv : v.toNat = low a.toNat * high b.toNat +
      low (high a.toNat * low b.toNat + high (low a.toNat * low b.toNat)) := by
    dsimp only [v]
    rw [UInt64.toNat_add, hba, lowWord_value, hu, Nat.mod_eq_of_lt hv0]
  have hmid : high a.toNat * high b.toNat +
      high (high a.toNat * low b.toNat + high (low a.toNat * low b.toNat)) <
      18446744073709551616 := by omega
  change (highWord a * highWord b + highWord u + highWord v).toNat = _
  rw [UInt64.toNat_add, UInt64.toNat_add, hhh, highWord_value, highWord_value, hu, hv,
    Nat.mod_eq_of_lt hmid, Nat.mod_eq_of_lt htop]
  exact highProduct_exact a.toNat b.toNat

end Submission.R27MulHigh
