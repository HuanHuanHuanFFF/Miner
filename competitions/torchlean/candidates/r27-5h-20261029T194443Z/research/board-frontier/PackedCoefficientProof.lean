import ContractExact

/- Minimal mathematical bridge, not the actual caller's all-input theorem.
No source from an external predecessor is embedded. -/
namespace R27PackedCoefficient

def pack (base : Int) : List Int → Int
  | [] => 0
  | x :: xs => x + base * pack base xs

theorem pack_add (base : Int) (a b : List Int) (h : a.length = b.length) :
    pack base (List.zipWith (· + ·) a b) = pack base a + pack base b := by
  induction a generalizing b with
  | nil => cases b <;> simp_all [pack]
  | cons x xs ih =>
    cases b with
    | nil => simp at h
    | cons y ys =>
      simp only [List.length_cons, Nat.add_right_cancel_iff] at h
      simp only [List.zipWith_cons_cons, pack, ih ys h]
      ring

theorem pack_scale (base c : Int) (a : List Int) :
    pack base (a.map (c * ·)) = c * pack base a := by
  induction a with
  | nil => simp [pack]
  | cons x xs ih => simp only [List.map_cons, pack, ih]; ring

theorem centered_digit (base half digit tail : Int)
    (hlo : 0 ≤ digit + half) (hhi : digit + half < base) :
    ((digit + base * tail + half) % base) - half = digit := by
  have hr : (digit + half) % base = digit + half := Int.emod_eq_of_lt hlo hhi
  rw [show digit + base * tail + half = digit + half + tail * base by ring,
    Int.add_mul_emod_self_right, hr]
  omega

theorem coefficient_two_dot (base a0 a1 b00 b01 b10 b11 : Int) :
    a0 * (b00 + base * b01) + a1 * (b10 + base * b11) =
      (a0*b00+a1*b10) + base*(a0*b01+a1*b11) := by ring

end R27PackedCoefficient
