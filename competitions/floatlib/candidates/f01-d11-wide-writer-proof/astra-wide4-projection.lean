/- NOT_RUN proof asset for exact eb9e codegen probe; no active entry is added. -/
namespace Submission.R11WideRows4
open FloatLib.Floats Competition

/-- Proof projection only; runtime output should read F40 lanes without constructing F10 rows. -/
def projectRow (s : F40) (r : Fin 4) : Packed10.F10 :=
  match r.val with
  | 0 => ⟨s.c0r0, s.c1r0, s.c2r0, s.c3r0, s.c4r0, s.c5r0, s.c6r0, s.c7r0, s.c8r0, s.c9r0⟩
  | 1 => ⟨s.c0r1, s.c1r1, s.c2r1, s.c3r1, s.c4r1, s.c5r1, s.c6r1, s.c7r1, s.c8r1, s.c9r1⟩
  | 2 => ⟨s.c0r2, s.c1r2, s.c2r2, s.c3r2, s.c4r2, s.c5r2, s.c6r2, s.c7r2, s.c8r2, s.c9r2⟩
  | _ => ⟨s.c0r3, s.c1r3, s.c2r3, s.c3r3, s.c4r3, s.c5r3, s.c6r3, s.c7r3, s.c8r3, s.c9r3⟩

def baseAt (a0 a1 a2 a3 : USize) (r : Fin 4) : USize :=
  match r.val with | 0 => a0 | 1 => a1 | 2 => a2 | _ => a3

theorem row_bound (count a0 a1 a2 a3 : USize) (A : Array Float32)
    (h0 : a0.toNat + (count.toNat - 1) < A.size)
    (h1 : a1.toNat + (count.toNat - 1) < A.size)
    (h2 : a2.toNat + (count.toNat - 1) < A.size)
    (h3 : a3.toNat + (count.toNat - 1) < A.size)
    (r : Fin 4) : (baseAt a0 a1 a2 a3 r).toNat + (count.toNat - 1) < A.size := by
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> first | exact h0 | exact h1 | exact h2 | exact h3

theorem wordLoop_row {n : Nat} (count a0 a1 a2 a3 : USize)
    (A : Array Float32) (B : Vector Packed10.F10 n) (hn : count.toNat = n)
    (h0 : a0.toNat + (count.toNat - 1) < A.size)
    (h1 : a1.toNat + (count.toNat - 1) < A.size)
    (h2 : a2.toNat + (count.toNat - 1) < A.size)
    (h3 : a3.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size) (k : USize)
    (c0r0 c0r1 c0r2 c0r3 : Float32)
    (c1r0 c1r1 c1r2 c1r3 : Float32)
    (c2r0 c2r1 c2r2 c2r3 : Float32)
    (c3r0 c3r1 c3r2 c3r3 : Float32)
    (c4r0 c4r1 c4r2 c4r3 : Float32)
    (c5r0 c5r1 c5r2 c5r3 : Float32)
    (c6r0 c6r1 c6r2 c6r3 : Float32)
    (c7r0 c7r1 c7r2 c7r3 : Float32)
    (c8r0 c8r1 c8r2 c8r3 : Float32)
    (c9r0 c9r1 c9r2 c9r3 : Float32)
    (r : Fin 4) :
    projectRow (wordLoop count a0 a1 a2 a3 A B hn h0 h1 h2 h3 hAS k
      c0r0 c0r1 c0r2 c0r3
      c1r0 c1r1 c1r2 c1r3
      c2r0 c2r1 c2r2 c2r3
      c3r0 c3r1 c3r2 c3r3
      c4r0 c4r1 c4r2 c4r3
      c5r0 c5r1 c5r2 c5r3
      c6r0 c6r1 c6r2 c6r3
      c7r0 c7r1 c7r2 c7r3
      c8r0 c8r1 c8r2 c8r3
      c9r0 c9r1 c9r2 c9r3
      ) r =
    let s := projectRow (⟨c0r0, c0r1, c0r2, c0r3, c1r0, c1r1, c1r2, c1r3, c2r0, c2r1, c2r2, c2r3, c3r0, c3r1, c3r2, c3r3, c4r0, c4r1, c4r2, c4r3, c5r0, c5r1, c5r2, c5r3, c6r0, c6r1, c6r2, c6r3, c7r0, c7r1, c7r2, c7r3, c8r0, c8r1, c8r2, c8r3, c9r0, c9r1, c9r2, c9r3⟩ : F40) r
    Packed10Index.loop count (baseAt a0 a1 a2 a3 r) A B hn
      (row_bound count a0 a1 a2 a3 A h0 h1 h2 h3 r) hAS k
      s.s0 s.s1 s.s2 s.s3 s.s4 s.s5 s.s6 s.s7 s.s8 s.s9 := by
  rw [wordLoop]
  split
  · rename_i hk
    dsimp only
    rw [Packed10Index.loop, dif_pos hk]
    dsimp only
    rw [wordLoop_row]
    rcases r with ⟨r,hr⟩
    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
    rcases h with rfl|rfl|rfl|rfl <;> rfl
  · rename_i hk
    dsimp only
    rw [Packed10Index.loop, dif_neg hk] <;> rfl
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

/-- The projection theorem entails all forty lanes, not an abstract read assumption. -/
theorem lane_of_row_eq (s t : F40) (h : ∀ r : Fin 4, projectRow s r = projectRow t r)
    (r : Fin 4) (j : Fin 10) :
    Packed10.lane (projectRow s r) j = Packed10.lane (projectRow t r) j := by
  rw [h r]

end Submission.R11WideRows4
