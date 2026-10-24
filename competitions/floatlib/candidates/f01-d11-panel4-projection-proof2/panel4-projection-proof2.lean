namespace Submission.R11WideRows4
open FloatLib.Floats Competition
def projectRow (s : F40) (r : Fin 4) : Packed10.F10 :=
  match r.val with
  | 0 => ⟨s.c0r0, s.c1r0, s.c2r0, s.c3r0, s.c4r0, s.c5r0, s.c6r0, s.c7r0, s.c8r0, s.c9r0⟩
  | 1 => ⟨s.c0r1, s.c1r1, s.c2r1, s.c3r1, s.c4r1, s.c5r1, s.c6r1, s.c7r1, s.c8r1, s.c9r1⟩
  | 2 => ⟨s.c0r2, s.c1r2, s.c2r2, s.c3r2, s.c4r2, s.c5r2, s.c6r2, s.c7r2, s.c8r2, s.c9r2⟩
  | _ => ⟨s.c0r3, s.c1r3, s.c2r3, s.c3r3, s.c4r3, s.c5r3, s.c6r3, s.c7r3, s.c8r3, s.c9r3⟩

end Submission.R11WideRows4
/- NOT_RUN future proof fragment; requires Panel4 from9a and the retained projectRow definition. -/
namespace Submission.Panel4Bridge
open FloatLib.Floats Competition
open R11WideRows4

/-- Proof-only selection of one prepared row. No row array is built. -/
def laneA (a : Panel4.F4) (r : Fin 4) : Float32 :=
  match r.val with | 0 => a.r0 | 1 => a.r1 | 2 => a.r2 | _ => a.r3

def baseFor (b0 b1 b2 b3 : Nat) (r : Fin 4) : Nat :=
  match r.val with | 0 => b0 | 1 => b1 | 2 => b2 | _ => b3

theorem packA_read (n b0 b1 b2 b3 : Nat) (Araw : Array Binary32)
    (r : Fin 4) (k : Fin n) :
    laneA ((Panel4.packA n b0 b1 b2 b3 Araw).get k) r =
      (Araw.map ExecFloat.Binary.toFloat32).getD (baseFor b0 b1 b2 b3 r+k.val) Packed10.zero32 := by
  rw [Panel4.packA_get, Packed10.nativeA_getD]
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> rfl

/-- Exact native recurrence; hread is closed by packA_read below. -/
theorem wordLoop_row {n : Nat} (count : USize) (panel : Vector Panel4.F4 n)
    (B : Vector Packed10.F10 n) (hn : count.toNat=n)
    (source : Array Float32) (base : Nat) (r : Fin 4)
    (hread : ∀ i : Fin n, laneA (panel.get i) r = source.getD (base+i.val) Packed10.zero32)
    (k : USize)
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
    : projectRow (Panel4.wordLoop count panel B hn k
        c0r0 c0r1 c0r2 c0r3 c1r0 c1r1 c1r2 c1r3 c2r0 c2r1 c2r2 c2r3 c3r0 c3r1 c3r2 c3r3 c4r0 c4r1 c4r2 c4r3 c5r0 c5r1 c5r2 c5r3 c6r0 c6r1 c6r2 c6r3 c7r0 c7r1 c7r2 c7r3 c8r0 c8r1 c8r2 c8r3 c9r0 c9r1 c9r2 c9r3) r =
      let s := projectRow (⟨c0r0, c0r1, c0r2, c0r3, c1r0, c1r1, c1r2, c1r3, c2r0, c2r1, c2r2, c2r3, c3r0, c3r1, c3r2, c3r3, c4r0, c4r1, c4r2, c4r3, c5r0, c5r1, c5r2, c5r3, c6r0, c6r1, c6r2, c6r3, c7r0, c7r1, c7r2, c7r3, c8r0, c8r1, c8r2, c8r3, c9r0, c9r1, c9r2, c9r3⟩ : F40) r
      Packed10.dot10 n base source B k.toNat s.s0 s.s1 s.s2 s.s3 s.s4 s.s5 s.s6 s.s7 s.s8 s.s9 := by
  rw [Panel4.wordLoop]
  split
  · rename_i hk
    have hkn : k.toNat<n := by rw [←hn]; exact USize.lt_iff_toNat_lt.mp hk
    dsimp only
    rw [Packed10.dot10, dif_pos hkn]
    dsimp only
    rw [wordLoop_row count panel B hn source base r hread, Packed10Index.stepNat hk]
    have ha : panel.toArray.uget k (by simpa only [panel.size_toArray] using hkn) =
        panel.get ⟨k.toNat,hkn⟩ := by rfl
    rw [ha, Packed10Index.ugetB_get B k hkn]
    have hh := hread ⟨k.toNat,hkn⟩
    rcases r with ⟨r,hr⟩
    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
    rcases h with rfl|rfl|rfl|rfl <;>
      simp only [projectRow, laneA] at hh ⊢ <;> simp only [hh]
  · rename_i hk
    have hkn : ¬ k.toNat<n := by
      rw [←hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    dsimp only
    rw [Packed10.dot10, dif_neg hkn]
termination_by count.toNat-k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

theorem runDot_row (n b0 b1 b2 b3 : Nat) (Araw : Array Binary32)
    (B : Vector Packed10.F10 n) (hn : n<USize.size) (r : Fin 4) :
    projectRow (Panel4.runDot n (Panel4.packA n b0 b1 b2 b3 Araw) B hn) r =
      Packed10Index.runDot n (baseFor b0 b1 b2 b3 r) (Araw.map ExecFloat.Binary.toFloat32) B := by
  have h := wordLoop_row (USize.ofNat n) (Panel4.packA n b0 b1 b2 b3 Araw) B
    (USize.toNat_ofNat_of_lt' hn) (Araw.map ExecFloat.Binary.toFloat32)
    (baseFor b0 b1 b2 b3 r) r (packA_read n b0 b1 b2 b3 Araw r) 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
  change projectRow (Panel4.runDot n (Panel4.packA n b0 b1 b2 b3 Araw) B hn) r = _ at h
  rw [h]
  clear h
  dsimp only
  rw [Packed10Index.runDot_eq]
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> simp only [projectRow, USize.toNat_zero]

theorem block_row (n p b0 b1 b2 b3 : Nat) (Araw : Array Binary32)
    (packedB : Vector (Vector Packed10.F10 n) (Packed10.groups p)) (hn : n<USize.size)
    (g : Fin (Packed10.groups p)) (r : Fin 4) :
    projectRow ((Panel4.block n p b0 b1 b2 b3 Araw packedB hn).get g) r =
      Packed10Index.runDot n (baseFor b0 b1 b2 b3 r)
        (Araw.map ExecFloat.Binary.toFloat32) (packedB.get g) := by
  simp only [Panel4.block, Packed10.vector_get_ofFn, runDot_row]

theorem baseFor_rows (n base : Nat) (r : Fin 4) :
    baseFor base (base+n) (base+2*n) (base+3*n) r = base+r.val*n := by
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> simp only [baseFor, Nat.zero_mul, Nat.one_mul, Nat.add_zero]

end Submission.Panel4Bridge
