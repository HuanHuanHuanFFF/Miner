import ContractExact

/- Original R25 actual UInt64 block-loop probe. NOT_COMPILED.
   The arithmetic fold and unique signed decoding are explicit. An integrating
   kernel must still establish the block bound from its actual prepared values,
   transport its indexed getter sequence, and connect the wide terminal. -/
namespace R25Block64Fold

def signed64 (q : UInt64) : Int :=
  if q.toNat < 2 ^ 63 then (q.toNat : Int) else (q.toNat : Int) - 2 ^ 64

def Represents (q : UInt64) (z : Int) : Prop :=
  ∃ k : Int, (q.toNat : Int) = z + k * 2 ^ 64

def total : List UInt64 → Int
  | [] => 0
  | q :: qs => signed64 q + total qs

def mass : List UInt64 → Int
  | [] => 0
  | q :: qs => |signed64 q| + mass qs

def loop : List UInt64 → UInt64 → UInt64
  | [], acc => acc
  | q :: qs, acc => loop qs (acc + q)

def run (qs : List UInt64) : UInt64 := loop qs 0

theorem signed_represents (q : UInt64) : Represents q (signed64 q) := by
  unfold Represents signed64
  split_ifs with h
  · exact ⟨0, by omega⟩
  · exact ⟨1, by omega⟩

theorem add_represents (a b : UInt64) (x y : Int)
    (ha : Represents a x) (hb : Represents b y) :
    Represents (a + b) (x + y) := by
  obtain ⟨ka, ha⟩ := ha
  obtain ⟨kb, hb⟩ := hb
  have hnat : (a + b).toNat + 2 ^ 64 * ((a.toNat + b.toNat) / 2 ^ 64) =
      a.toNat + b.toNat := by
    rw [UInt64.toNat_add]
    exact Nat.mod_add_div _ _
  have hint : ((a + b).toNat : Int) +
      2 ^ 64 * (((a.toNat + b.toNat) / 2 ^ 64 : Nat) : Int) =
      (a.toNat : Int) + b.toNat := by exact_mod_cast hnat
  refine ⟨ka + kb - (((a.toNat + b.toNat) / 2 ^ 64 : Nat) : Int), ?_⟩
  omega

theorem loop_represents (qs : List UInt64) (acc : UInt64) (initial : Int)
    (h : Represents acc initial) :
    Represents (loop qs acc) (initial + total qs) := by
  induction qs generalizing acc initial with
  | nil => simpa [loop, total] using h
  | cons q qs ih =>
    have hstep := add_represents acc q initial (signed64 q) h (signed_represents q)
    simpa only [loop, total, Int.add_assoc] using
      ih (acc + q) (initial + signed64 q) hstep

theorem run_represents (qs : List UInt64) : Represents (run qs) (total qs) := by
  have hz : Represents (0 : UInt64) 0 := ⟨0, by simp⟩
  simpa [run] using loop_represents qs 0 0 hz

theorem signed_of_represents (q : UInt64) (z : Int) (h : Represents q z)
    (hz : -(2 ^ 63 : Int) ≤ z ∧ z < 2 ^ 63) : signed64 q = z := by
  obtain ⟨k, hk⟩ := h
  have hu := q.toNat_lt
  have hn : (0 : Int) ≤ q.toNat := by omega
  unfold signed64
  split_ifs with hs <;> omega

theorem abs_total_le_mass (qs : List UInt64) : |total qs| ≤ mass qs := by
  induction qs with
  | nil => simp [total, mass]
  | cons q qs ih =>
    calc
      |total (q :: qs)| = |signed64 q + total qs| := rfl
      _ ≤ |signed64 q| + |total qs| := abs_add _ _
      _ ≤ |signed64 q| + mass qs := add_le_add_left ih _
      _ = mass (q :: qs) := rfl

/-- Actual machine fold equals the exact block sum under its absolute bound.
    Intermediate UInt64 wrapping is allowed and does not need per-term checks. -/
theorem run_exact (qs : List UInt64) (h : mass qs < (2 ^ 63 : Int)) :
    signed64 (run qs) = total qs := by
  have hb : |total qs| < (2 ^ 63 : Int) := lt_of_le_of_lt (abs_total_le_mass qs) h
  exact signed_of_represents (run qs) (total qs) (run_represents qs)
    ⟨(abs_lt.mp hb).1.le, (abs_lt.mp hb).2⟩

theorem mass_le_uniform (qs : List UInt64) (bound : Int)
    (h : ∀ q ∈ qs, |signed64 q| < bound) :
    mass qs ≤ (qs.length : Int) * (bound - 1) := by
  induction qs with
  | nil => simp [mass]
  | cons q qs ih =>
    have hq : |signed64 q| ≤ bound - 1 := by have := h q (by simp); omega
    have htail := ih (by intro a ha; exact h a (by simp [ha]))
    calc
      mass (q :: qs) = |signed64 q| + mass qs := rfl
      _ ≤ (bound - 1) + (qs.length : Int) * (bound - 1) := add_le_add hq htail
      _ = ((q :: qs).length : Int) * (bound - 1) := by
        simp only [List.length_cons, Nat.cast_add, Nat.cast_one]
        ring

/-- The inexpensive length-times-uniform-bound premise is sufficient; there is
    no assumed exact L1 scan or cancellation test. A prepared caller supplies
    bound=2^(48+spanX+spanY) and a power-of-two block length. -/
theorem run_exact_of_uniform (qs : List UInt64) (bound : Int)
    (hterm : ∀ q ∈ qs, |signed64 q| < bound)
    (hblock : (qs.length : Int) * bound ≤ 2 ^ 63) :
    signed64 (run qs) = total qs := by
  apply run_exact
  cases qs with
  | nil => norm_num [mass]
  | cons q qs =>
    have hm := mass_le_uniform (q :: qs) bound hterm
    have hn : (1 : Int) ≤ (q :: qs).length := by simp
    nlinarith

end R25Block64Fold
