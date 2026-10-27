/- CODEGEN_ONLY: unused machine-loop probe; original four entry points remain unchanged. -/
namespace Submission.R11WideRows4
open FloatLib.Floats Competition

/-- Column-major: four independent rows per column, ten columns. -/
structure F40 where
  c0r0 : Float32
  c0r1 : Float32
  c0r2 : Float32
  c0r3 : Float32
  c1r0 : Float32
  c1r1 : Float32
  c1r2 : Float32
  c1r3 : Float32
  c2r0 : Float32
  c2r1 : Float32
  c2r2 : Float32
  c2r3 : Float32
  c3r0 : Float32
  c3r1 : Float32
  c3r2 : Float32
  c3r3 : Float32
  c4r0 : Float32
  c4r1 : Float32
  c4r2 : Float32
  c4r3 : Float32
  c5r0 : Float32
  c5r1 : Float32
  c5r2 : Float32
  c5r3 : Float32
  c6r0 : Float32
  c6r1 : Float32
  c6r2 : Float32
  c6r3 : Float32
  c7r0 : Float32
  c7r1 : Float32
  c7r2 : Float32
  c7r3 : Float32
  c8r0 : Float32
  c8r1 : Float32
  c8r2 : Float32
  c8r3 : Float32
  c9r0 : Float32
  c9r1 : Float32
  c9r2 : Float32
  c9r3 : Float32

end Submission.R11WideRows4

namespace Submission.Panel4
open FloatLib.Floats Competition

/-- One input packet for four rows at the same k; preparation is outside the MAC loop. -/
structure F4 where
  r0 : Float32
  r1 : Float32
  r2 : Float32
  r3 : Float32

def wordLoop {n : Nat} (count : USize) (A : Vector F4 n)
    (B : Vector Packed10.F10 n) (hn : count.toNat = n) (k : USize)
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
    : R11WideRows4.F40 :=
  if hk : k < count then
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    let a := A.toArray.uget k (by simpa only [A.size_toArray] using hkn)
    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    let x0 := a.r0
    let x1 := a.r1
    let x2 := a.r2
    let x3 := a.r3
    let b0 := v.s0
    let b1 := v.s1
    let b2 := v.s2
    let b3 := v.s3
    let b4 := v.s4
    let b5 := v.s5
    let b6 := v.s6
    let b7 := v.s7
    let b8 := v.s8
    let b9 := v.s9
    wordLoop count A B hn (k + 1)
      (c0r0 + x0 * b0) (c0r1 + x1 * b0) (c0r2 + x2 * b0) (c0r3 + x3 * b0)
      (c1r0 + x0 * b1) (c1r1 + x1 * b1) (c1r2 + x2 * b1) (c1r3 + x3 * b1)
      (c2r0 + x0 * b2) (c2r1 + x1 * b2) (c2r2 + x2 * b2) (c2r3 + x3 * b2)
      (c3r0 + x0 * b3) (c3r1 + x1 * b3) (c3r2 + x2 * b3) (c3r3 + x3 * b3)
      (c4r0 + x0 * b4) (c4r1 + x1 * b4) (c4r2 + x2 * b4) (c4r3 + x3 * b4)
      (c5r0 + x0 * b5) (c5r1 + x1 * b5) (c5r2 + x2 * b5) (c5r3 + x3 * b5)
      (c6r0 + x0 * b6) (c6r1 + x1 * b6) (c6r2 + x2 * b6) (c6r3 + x3 * b6)
      (c7r0 + x0 * b7) (c7r1 + x1 * b7) (c7r2 + x2 * b7) (c7r3 + x3 * b7)
      (c8r0 + x0 * b8) (c8r1 + x1 * b8) (c8r2 + x2 * b8) (c8r3 + x3 * b8)
      (c9r0 + x0 * b9) (c9r1 + x1 * b9) (c9r2 + x2 * b9) (c9r3 + x3 * b9)
  else ⟨c0r0, c0r1, c0r2, c0r3, c1r0, c1r1, c1r2, c1r3, c2r0, c2r1, c2r2, c2r3, c3r0, c3r1, c3r2, c3r3, c4r0, c4r1, c4r2, c4r3, c5r0, c5r1, c5r2, c5r3, c6r0, c6r1, c6r2, c6r3, c7r0, c7r1, c7r2, c7r3, c8r0, c8r1, c8r2, c8r3, c9r0, c9r1, c9r2, c9r3⟩
termination_by count.toNat - k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

/-- Only the count is converted to a machine word; callers must prove it fits. -/
def runDot (n : Nat) (A : Vector F4 n) (B : Vector Packed10.F10 n)
    (hn : n < USize.size) : R11WideRows4.F40 :=
  wordLoop (USize.ofNat n) A B (USize.toNat_ofNat_of_lt' hn) 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32

/-- Four original words are converted once per k into one F4 record. -/
def packA (n base0 base1 base2 base3 : Nat) (Araw : Array Binary32) : Vector F4 n :=
  Vector.ofFn fun k =>
    ⟨ExecFloat.Binary.toFloat32 (Araw.getD (base0 + k.val) posZero),
     ExecFloat.Binary.toFloat32 (Araw.getD (base1 + k.val) posZero),
     ExecFloat.Binary.toFloat32 (Araw.getD (base2 + k.val) posZero),
     ExecFloat.Binary.toFloat32 (Araw.getD (base3 + k.val) posZero)⟩

theorem packA_get (n base0 base1 base2 base3 : Nat) (Araw : Array Binary32) (k : Fin n) :
    (packA n base0 base1 base2 base3 Araw).get k =
      ⟨ExecFloat.Binary.toFloat32 (Araw.getD (base0 + k.val) posZero),
       ExecFloat.Binary.toFloat32 (Araw.getD (base1 + k.val) posZero),
       ExecFloat.Binary.toFloat32 (Araw.getD (base2 + k.val) posZero),
       ExecFloat.Binary.toFloat32 (Araw.getD (base3 + k.val) posZero)⟩ := by
  simp only [packA, Packed10.vector_get_ofFn]

/-- Prepare this panel before traversing all existing B column packets. -/
def block (n p base0 base1 base2 base3 : Nat) (Araw : Array Binary32)
    (packedB : Vector (Vector Packed10.F10 n) (Packed10.groups p))
    (hn : n < USize.size) : Vector R11WideRows4.F40 (Packed10.groups p) :=
  let panel := packA n base0 base1 base2 base3 Araw
  Vector.ofFn fun g => runDot n panel (packedB.get g) hn

end Submission.Panel4

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

namespace Submission.R11WideRows4
open FloatLib.Floats Competition
@[inline] def lane40 (s : F40) (r : Fin 4) (l : Fin 10) : Float32 :=
  match r.val with
  | 0 => match l.val with
    | 0 => s.c0r0
    | 1 => s.c1r0
    | 2 => s.c2r0
    | 3 => s.c3r0
    | 4 => s.c4r0
    | 5 => s.c5r0
    | 6 => s.c6r0
    | 7 => s.c7r0
    | 8 => s.c8r0
    | _ => s.c9r0
  | 1 => match l.val with
    | 0 => s.c0r1
    | 1 => s.c1r1
    | 2 => s.c2r1
    | 3 => s.c3r1
    | 4 => s.c4r1
    | 5 => s.c5r1
    | 6 => s.c6r1
    | 7 => s.c7r1
    | 8 => s.c8r1
    | _ => s.c9r1
  | 2 => match l.val with
    | 0 => s.c0r2
    | 1 => s.c1r2
    | 2 => s.c2r2
    | 3 => s.c3r2
    | 4 => s.c4r2
    | 5 => s.c5r2
    | 6 => s.c6r2
    | 7 => s.c7r2
    | 8 => s.c8r2
    | _ => s.c9r2
  | _ => match l.val with
    | 0 => s.c0r3
    | 1 => s.c1r3
    | 2 => s.c2r3
    | 3 => s.c3r3
    | 4 => s.c4r3
    | 5 => s.c5r3
    | 6 => s.c6r3
    | 7 => s.c7r3
    | 8 => s.c8r3
    | _ => s.c9r3
theorem lane40_eq (s : F40) (r : Fin 4) (l : Fin 10) :
    lane40 s r l = Packed10.lane (projectRow s r) l := by
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> rfl
end Submission.R11WideRows4

namespace Submission.R11WideLayout

open FloatLib.Floats Competition

abbrev Tiles (p : Nat) := Vector R11WideRows4.F40 (Packed10.groups p)

/-- Once n>0 and a complete four-row block exists, all four A spans are valid.
With global A.size<USize.size, each of these bases also fits a machine word. -/
theorem nativeA_span (batch m n : Nat)
    (A : Vector Binary32 (batch * m * n)) (b : Fin batch)
    (first : Nat) (hblock : first + 4 ≤ m) (r : Fin 4) (hn : 0 < n) :
    (b.val * m + first + r.val) * n + (n - 1) <
      (A.toArray.map ExecFloat.Binary.toFloat32).size := by
  have hr := r.isLt
  have hb := Nat.mul_le_mul_right m b.isLt
  rw [Nat.succ_mul] at hb
  have hrow : b.val * m + first + r.val < batch * m := by omega
  have hs := Nat.mul_le_mul_right n (Nat.succ_le_of_lt hrow)
  rw [Nat.succ_mul] at hs
  simp only [Array.size_map, A.size_toArray]
  omega

/-- Independent of old optional O2 helpers, which may be pruned. -/
def groupFor (p : Nat) (j : Fin p) : Fin (Packed10.groups p) :=
  ⟨j.val / 10, by have hj := j.isLt; unfold Packed10.groups; omega⟩

def laneFor (p : Nat) (j : Fin p) : Fin 10 :=
  ⟨j.val % 10, Nat.mod_lt _ (by decide)⟩

theorem columnFor (p : Nat) (j : Fin p) :
    10 * (groupFor p j).val + (laneFor p j).val = j.val := by
  dsimp only [groupFor, laneFor]
  omega

/-- The exact projection contract: one computed F40, four old F10 dot results.
The actual buildTiles must be evaluated once per block, not substituted as a
function that recomputes the wide loop for every scalar output. -/
def Projects (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p) : Prop :=
  ∀ (g : Fin (Packed10.groups p)) (r : Fin 4) (l : Fin 10),
    lane40 (tiles.get g) r l = Packed10.lane
      (Packed10Index.runDot n ((b.val * m + first + r.val) * n)
        (A.toArray.map ExecFloat.Binary.toFloat32)
        (((Packed10.packB batch n p B).get b).get g)) l

theorem Projects_of_row_projection (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (row40 : R11WideRows4.F40 → Fin 4 → Packed10.F10)
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (hlane : ∀ v r l, lane40 v r l = Packed10.lane (row40 v r) l)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hrows : ∀ g r, row40 (tiles.get g) r =
      Packed10Index.runDot n ((b.val * m + first + r.val) * n)
        (A.toArray.map ExecFloat.Binary.toFloat32)
        (((Packed10.packB batch n p B).get b).get g)) :
    Projects batch m n p A B lane40 b first tiles := by
  intro g r l
  rw [hlane, hrows]

@[inline] def emitRow (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (out : Array Binary32) (r : Fin 4) : Array Binary32 :=
  RowStream.emit p (fun j =>
    Packed10.finish n ((b.val * m + first + r.val) * n)
      (b.val * n * p + j.val) p A.toArray B.toArray
      (lane40 (tiles.get (groupFor p j)) r (laneFor p j))) out

theorem finish_lane_eq_point (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first + 4 ≤ m) (hproj : Projects batch m n p A B lane40 b first tiles)
    (r : Fin 4) (j : Fin p) :
    Packed10.finish n ((b.val * m + first + r.val) * n)
      (b.val * n * p + j.val) p A.toArray B.toArray
      (lane40 (tiles.get (groupFor p j)) r (laneFor p j)) =
      RowStream.point batch m n p A B ((b.val * m + first + r.val) * p + j.val) := by
  have hr := r.isLt
  have hm : 0 < m := by omega
  have hp : 0 < p := Nat.zero_lt_of_lt j.isLt
  have hrow : first + r.val < m := by omega
  have hdiv : (b.val * m + first + r.val) / m = b.val := by
    rw [show b.val * m + first + r.val = b.val * m + (first + r.val) by omega,
      Nat.mul_comm b.val m, Nat.mul_add_div hm, Nat.div_eq_of_lt hrow, Nat.add_zero]
  rw [hproj (groupFor p j) r (laneFor p j), Packed10Index.runDot_eq]
  rw [RowStream.point_row batch m n p A B (b.val * m + first + r.val)
    j.val hm hp j.isLt, hdiv]
  apply Packed10.finish_dot10_lane
  intro k
  have hcol : 10 * (groupFor p j).val + (laneFor p j).val < p := by
    rw [columnFor]
    exact j.isLt
  rw [Packed10.packB_lane batch n p B b (groupFor p j) k (laneFor p j) hcol]
  rw [index_address (b.val * n) k.val p
    (10 * (groupFor p j).val + (laneFor p j).val), columnFor]

theorem emitRow_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first + 4 ≤ m) (hproj : Projects batch m n p A B lane40 b first tiles)
    (out : Array Binary32) (r : Fin 4)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r.val + 1) * p)
      (emitRow batch m n p A B lane40 b first tiles out r) := by
  have h := RowStream.emit_prefix (RowStream.point batch m n p A B)
    ((b.val * m + first + r.val) * p) p
    (fun j => Packed10.finish n ((b.val * m + first + r.val) * n)
      (b.val * n * p + j.val) p A.toArray B.toArray
      (lane40 (tiles.get (groupFor p j)) r (laneFor p j))) out hout
    (fun j => finish_lane_eq_point batch m n p A B lane40 b first tiles hblock hproj r j)
  simpa only [emitRow, Nat.add_mul, Nat.one_mul] using h

@[inline] def emitBlock (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl 4 (emitRow batch m n p A B lane40 b first tiles) out

theorem emitBlock_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (b : Fin batch) (first : Nat) (tiles : Tiles p)
    (hblock : first + 4 ≤ m) (hproj : Projects batch m n p A B lane40 b first tiles)
    (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + first) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + first + 4) * p)
      (emitBlock batch m n p A B lane40 b first tiles out) := by
  exact RowStream.foldl_inv 4 (emitRow batch m n p A B lane40 b first tiles)
    (fun r acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + r) * p) acc)
    (fun r acc hacc => by
      simpa only [Nat.add_assoc] using
        emitRow_prefix batch m n p A B lane40 b first tiles hblock hproj acc r hacc)
    out (by simpa only [Nat.add_zero] using hout)

def rowIndex (batch m : Nat) (b : Fin batch) (i : Fin m) : Fin (batch * m) :=
  ⟨b.val * m + i.val, by
    have h := Nat.mul_le_mul_right m b.isLt
    rw [Nat.succ_mul] at h
    omega⟩

/-- Existing Packed10 path handles exactly the remaining zero to three rows.
nativeA and packedB are the same global values used by buildTiles. -/
def emitTail (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (b : Fin batch)
    (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (first : Nat) (out : Array Binary32) : Array Binary32 :=
  Fin.foldl (m - first) (fun acc i =>
    RowStream.row batch m n p A B nativeA packedB acc
      (rowIndex batch m b ⟨first + i.val, by have hi := i.isLt; omega⟩)) out

theorem emitTail_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (b : Fin batch)
    (first : Nat) (hfirst : first ≤ m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + first) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (emitTail batch m n p A B b (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) first out) := by
  have h := RowStream.foldl_inv (m - first)
    (fun acc i => RowStream.row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B) acc
      (rowIndex batch m b ⟨first + i.val, by have hi := i.isLt; omega⟩))
    (fun i acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + first + i) * p) acc)
    (fun i acc hacc => by
      have hrow := RowStream.row_prefix batch m n p A B
        (rowIndex batch m b ⟨first + i.val, by have hi := i.isLt; omega⟩) acc
        (by simpa only [rowIndex, Nat.add_assoc] using hacc)
      simpa only [rowIndex, Nat.add_assoc] using
        hrow)
    out (by simpa only [Nat.add_zero] using hout)
  have hend : b.val * m + first + (m - first) = (b.val + 1) * m := by
    rw [Nat.add_mul, Nat.one_mul]
    omega
  simpa only [emitTail, hend] using h

/-- buildTiles closes over the single global nativeA/packedB preparation.
It returns an evaluated vector once per complete four-row block. -/
@[inline] def writeBatch (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (buildTiles : Fin batch → Fin (m / 4) → Tiles p)
    (out : Array Binary32) (b : Fin batch) : Array Binary32 :=
  let afterBlocks := Fin.foldl (m / 4) (fun acc h =>
    let tiles := buildTiles b h
    emitBlock batch m n p A B lane40 b (4 * h.val) tiles acc) out
  emitTail batch m n p A B b nativeA packedB (4 * (m / 4)) afterBlocks

theorem writeBatch_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Fin batch → Fin (m / 4) → Tiles p)
    (hproj : ∀ (b : Fin batch) (h : Fin (m / 4)),
      Projects batch m n p A B lane40 b (4 * h.val) (buildTiles b h))
    (out : Array Binary32) (b : Fin batch)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (b.val * m * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (writeBatch batch m n p A B lane40 (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) buildTiles out b) := by
  have hblocks := RowStream.foldl_inv (m / 4)
    (fun acc h => emitBlock batch m n p A B lane40 b (4 * h.val) (buildTiles b h) acc)
    (fun h acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + 4 * h) * p) acc)
    (fun h acc hacc => by
      have hh := h.isLt
      have hblock : 4 * h.val + 4 ≤ m := by omega
      simpa only [Nat.mul_add, Nat.mul_one, Nat.add_assoc] using
        emitBlock_prefix batch m n p A B lane40 b (4 * h.val) (buildTiles b h)
          hblock (hproj b h) acc hacc)
    out (by simpa only [Nat.mul_zero, Nat.add_zero] using hout)
  have hfirst : 4 * (m / 4) ≤ m := by omega
  exact emitTail_prefix batch m n p A B b (4 * (m / 4)) hfirst _ hblocks

@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Array Float32 →
      Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch →
      Fin batch → Fin (m / 4) → Tiles p) : Array Binary32 :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed10.packB batch n p B
  Fin.foldl batch (writeBatch batch m n p A B lane40 nativeA packedB
    (buildTiles nativeA packedB)) (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (lane40 : R11WideRows4.F40 → Fin 4 → Fin 10 → Float32)
    (buildTiles : Array Float32 →
      Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch →
      Fin batch → Fin (m / 4) → Tiles p)
    (hproj : ∀ (b : Fin batch) (h : Fin (m / 4)), Projects batch m n p A B lane40 b (4 * h.val)
      (buildTiles (A.toArray.map ExecFloat.Binary.toFloat32) (Packed10.packB batch n p B) b h)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B lane40 buildTiles) := by
  exact RowStream.foldl_inv batch
    (writeBatch batch m n p A B lane40 (A.toArray.map ExecFloat.Binary.toFloat32)
      (Packed10.packB batch n p B)
      (buildTiles (A.toArray.map ExecFloat.Binary.toFloat32) (Packed10.packB batch n p B)))
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b * m * p) acc)
    (fun b acc hacc => writeBatch_prefix batch m n p A B lane40 _ hproj acc b hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

end Submission.R11WideLayout

/- NOT_RUN proof/implementation asset, not a new Kernel or an active entry.
Requires the retained Packed10/Packed10Index/RowStream interfaces of749b.
All appearances of a global native map below are in proofs, not tail runtime. -/
namespace Submission.Panel4Tail
open FloatLib.Floats Competition

/-- At most three rows in the intended caller; total reads retain +0 defaults. -/
def prepare (rows n rawBase : Nat) (Araw : Array Binary32) : Array Float32 :=
  Array.ofFn fun q : Fin (rows * n) =>
    ExecFloat.Binary.toFloat32 (Araw.getD (rawBase + q.val) posZero)

theorem prepare_getD (rows n rawBase : Nat) (Araw : Array Binary32)
    (i : Nat) (hi : i < rows * n) :
    (prepare rows n rawBase Araw).getD i Packed10.zero32 =
      ExecFloat.Binary.toFloat32 (Araw.getD (rawBase + i) posZero) := by
  simp [prepare, Array.getD, hi, Array.size_ofFn, Array.getElem_ofFn]

theorem prepare_read (rows n rawBase : Nat) (Araw : Array Binary32)
    (r : Fin rows) (k : Fin n) :
    (prepare rows n rawBase Araw).getD (r.val * n + k.val) Packed10.zero32 =
      (Araw.map ExecFloat.Binary.toFloat32).getD (rawBase + r.val * n + k.val) Packed10.zero32 := by
  have hs := Nat.mul_le_mul_right n r.isLt
  rw [Nat.succ_mul] at hs
  have hi : r.val * n + k.val < rows * n := by have hk := k.isLt; omega
  rw [prepare_getD rows n rawBase Araw _ hi, Packed10.nativeA_getD]
  simp only [Nat.add_assoc]

/-- Only equality of the actually read A words is needed. No FP reassociation. -/
theorem dot10_shift (n localBase rawBase : Nat) (tailA source : Array Float32)
    (B : Vector Packed10.F10 n)
    (hread : ∀ i : Fin n, tailA.getD (localBase + i.val) Packed10.zero32 =
      source.getD (rawBase + i.val) Packed10.zero32)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 : Float32) :
    Packed10.dot10 n localBase tailA B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 =
      Packed10.dot10 n rawBase source B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 := by
  by_cases hk : k < n
  · conv_lhs => rw [Packed10.dot10]
    conv_rhs => rw [Packed10.dot10]
    simp only [dif_pos hk]
    rw [hread ⟨k, hk⟩]
    exact dot10_shift n localBase rawBase tailA source B hread (k + 1)
      _ _ _ _ _ _ _ _ _ _
  · conv_lhs => rw [Packed10.dot10]
    conv_rhs => rw [Packed10.dot10]
    simp only [dif_neg hk]
termination_by n - k
decreasing_by omega

theorem runDot_shift (n localBase rawBase : Nat) (tailA source : Array Float32)
    (B : Vector Packed10.F10 n)
    (hread : ∀ i : Fin n, tailA.getD (localBase + i.val) Packed10.zero32 =
      source.getD (rawBase + i.val) Packed10.zero32) :
    Packed10Index.runDot n localBase tailA B = Packed10Index.runDot n rawBase source B := by
  rw [Packed10Index.runDot_eq, Packed10Index.runDot_eq]
  exact dot10_shift n localBase rawBase tailA source B hread 0 _ _ _ _ _ _ _ _ _ _

theorem runDot_prepared (rows n rawBase : Nat) (Araw : Array Binary32)
    (r : Fin rows) (B : Vector Packed10.F10 n) :
    Packed10Index.runDot n (r.val * n) (prepare rows n rawBase Araw) B =
      Packed10Index.runDot n (rawBase + r.val * n) (Araw.map ExecFloat.Binary.toFloat32) B := by
  apply runDot_shift
  intro k
  exact prepare_read rows n rawBase Araw r k

variable {batch m n p : Nat}
variable (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
variable (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
variable (b : Fin batch) (first : Nat)

@[inline] def group (tailA : Array Float32) (r : Fin (m-first))
    (out : Array Binary32) (g : Fin (Packed10.groups p)) : Array Binary32 :=
  let result := Packed10Index.runDot n (r.val*n) tailA ((packedB.get b).get g)
  RowStream.emit (min 10 (p-10*g.val)) (fun l =>
    Packed10.finish n ((b.val*m+first+r.val)*n) (b.val*n*p+10*g.val+l.val)
      p A.toArray B.toArray (Packed10.lane result
        ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩)) out

@[inline] def row (tailA : Array Float32) (out : Array Binary32) (r : Fin (m-first)) :=
  Fin.foldl (Packed10.groups p) (group A B packedB b first tailA r) out

theorem group_eq (r : Fin (m-first)) (out : Array Binary32) (g : Fin (Packed10.groups p)) :
    group A B packedB b first (prepare (m-first) n ((b.val*m+first)*n) A.toArray) r out g =
      RowStream.group batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32) packedB
        (R11WideLayout.rowIndex batch m b ⟨first+r.val, by have h:=r.isLt; omega⟩) out g := by
  have hr : first+r.val<m := by have h:=r.isLt; omega
  have hm : 0<m := by omega
  have hd : (b.val*m+(first+r.val))/m=b.val := by
    rw [Nat.mul_comm b.val m, Nat.mul_add_div hm, Nat.div_eq_of_lt hr, Nat.add_zero]
  simp only [group, RowStream.group, R11WideLayout.rowIndex, Nat.add_assoc, hd]
  rw [runDot_prepared]
  simp only [Nat.add_mul, Nat.add_assoc]

theorem row_eq (out : Array Binary32) (r : Fin (m-first)) :
    row A B packedB b first (prepare (m-first) n ((b.val*m+first)*n) A.toArray) out r =
      RowStream.row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32) packedB out
        (R11WideLayout.rowIndex batch m b ⟨first+r.val, by have h:=r.isLt; omega⟩) := by
  unfold row RowStream.row
  apply congrArg (fun f => Fin.foldl (Packed10.groups p) f out)
  funext acc g
  exact group_eq A B packedB b first r acc g

def tail (out : Array Binary32) : Array Binary32 :=
  let tailA := prepare (m-first) n ((b.val*m+first)*n) A.toArray
  Fin.foldl (m-first) (row A B packedB b first tailA) out

theorem tail_eq (out : Array Binary32) :
    tail A B packedB b first out = R11WideLayout.emitTail batch m n p A B b
      (A.toArray.map ExecFloat.Binary.toFloat32) packedB first out := by
  simp only [tail, R11WideLayout.emitTail]
  apply congrArg (fun f => Fin.foldl (m-first) f out)
  funext acc r
  exact row_eq A B packedB b first acc r

theorem tail_prefix (hfirst : first≤m) (out : Array Binary32)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) ((b.val*m+first)*p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val+1)*m*p)
      (tail A B (Packed10.packB batch n p B) b first out) := by
  rw [tail_eq]
  exact R11WideLayout.emitTail_prefix batch m n p A B b first hfirst out hout

end Submission.Panel4Tail

/- R15 proof/entry asset, NOT_COMPILED and not wired into Submission.bmm.
   Reuses exact R11 Panel4, projection, lane40, layout, and factored-tail assets.
   Runtime prepares packed B globally; A is prepared only inside Panel4.block
   or Panel4Tail.tail. Global A.map appears only in proofs and is erased. -/
namespace Submission.R15PanelEntry
open FloatLib.Floats Competition

@[inline] def buildTiles (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (hn : n < USize.size) (b : Fin batch) (h : Fin (m / 4)) :
    R11WideLayout.Tiles p :=
  let base := (b.val * m + 4 * h.val) * n
  Panel4.block n p base (base + n) (base + 2 * n) (base + 3 * n)
    A.toArray (packedB.get b) hn

theorem buildTiles_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : n < USize.size) (b : Fin batch) (h : Fin (m / 4)) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b (4 * h.val)
      (buildTiles batch m n p A (Packed10.packB batch n p B) hn b h) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [buildTiles, Panel4Bridge.block_row, Panel4Bridge.baseFor_rows, Nat.add_mul]

@[inline] def writeBatch (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (hn : n < USize.size) (out : Array Binary32) (b : Fin batch) : Array Binary32 :=
  let afterBlocks := Fin.foldl (m / 4) (fun acc h =>
    let tiles := buildTiles batch m n p A packedB hn b h
    R11WideLayout.emitBlock batch m n p A B R11WideRows4.lane40
      b (4 * h.val) tiles acc) out
  Panel4Tail.tail A B packedB b (4 * (m / 4)) afterBlocks

theorem writeBatch_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (hn : n < USize.size) (out : Array Binary32) (b : Fin batch) :
    writeBatch batch m n p A B packedB hn out b =
      R11WideLayout.writeBatch batch m n p A B R11WideRows4.lane40
        (A.toArray.map ExecFloat.Binary.toFloat32) packedB
        (buildTiles batch m n p A packedB hn) out b := by
  unfold writeBatch R11WideLayout.writeBatch
  exact Panel4Tail.tail_eq A B packedB b (4 * (m / 4)) _

theorem writeBatch_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (hn : n < USize.size) (out : Array Binary32) (b : Fin batch)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (b.val * m * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (writeBatch batch m n p A B (Packed10.packB batch n p B) hn out b) := by
  rw [writeBatch_eq]
  exact R11WideLayout.writeBatch_prefix batch m n p A B R11WideRows4.lane40
    (buildTiles batch m n p A (Packed10.packB batch n p B) hn)
    (fun bb h => buildTiles_projects batch m n p A B hn bb h) out b hout

@[inline] def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) : Array Binary32 :=
  let packedB := Packed10.packB batch n p B
  Fin.foldl batch (writeBatch batch m n p A B packedB hn)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B hn) := by
  exact RowStream.foldl_inv batch
    (writeBatch batch m n p A B (Packed10.packB batch n p B) hn)
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b * m * p) acc)
    (fun b acc hacc => writeBatch_prefix batch m n p A B hn acc b hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) :
    Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B hn, (output_prefix batch m n p A B hn).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (hn : n < USize.size) :
    core batch m n p A B hn = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B hn) (output_prefix batch m n p A B hn)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.R15PanelEntry
