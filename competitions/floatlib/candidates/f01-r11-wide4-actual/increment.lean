/- Four-row machine loop now called by the concrete wide BMM entry below. -/
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

def wordLoop {n : Nat} (count a0 a1 a2 a3 : USize)
    (A : Array Float32) (B : Vector Packed10.F10 n)
    (hn : count.toNat = n)
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
    : F40 :=
  if hk : k < count then
    have hkn : k.toNat < n := by
      rw [← hn]
      exact USize.lt_iff_toNat_lt.mp hk
    have ha0 := Packed10Index.boundA a0.toNat count.toNat k.toNat A.size h0
      (USize.lt_iff_toNat_lt.mp hk)
    let x0 := A.uget (a0 + k)
      (by rw [Packed10Index.addNat a0 k (Nat.lt_trans ha0 hAS)]; exact ha0)
    have ha1 := Packed10Index.boundA a1.toNat count.toNat k.toNat A.size h1
      (USize.lt_iff_toNat_lt.mp hk)
    let x1 := A.uget (a1 + k)
      (by rw [Packed10Index.addNat a1 k (Nat.lt_trans ha1 hAS)]; exact ha1)
    have ha2 := Packed10Index.boundA a2.toNat count.toNat k.toNat A.size h2
      (USize.lt_iff_toNat_lt.mp hk)
    let x2 := A.uget (a2 + k)
      (by rw [Packed10Index.addNat a2 k (Nat.lt_trans ha2 hAS)]; exact ha2)
    have ha3 := Packed10Index.boundA a3.toNat count.toNat k.toNat A.size h3
      (USize.lt_iff_toNat_lt.mp hk)
    let x3 := A.uget (a3 + k)
      (by rw [Packed10Index.addNat a3 k (Nat.lt_trans ha3 hAS)]; exact ha3)
    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
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
    wordLoop count a0 a1 a2 a3 A B hn h0 h1 h2 h3 hAS (k + 1)
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

end Submission.R11WideRows4


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

def joinRows (s0 s1 s2 s3 : Packed10.F10) : F40 :=
  ⟨s0.s0, s1.s0, s2.s0, s3.s0, s0.s1, s1.s1, s2.s1, s3.s1, s0.s2, s1.s2, s2.s2, s3.s2, s0.s3, s1.s3, s2.s3, s3.s3, s0.s4, s1.s4, s2.s4, s3.s4, s0.s5, s1.s5, s2.s5, s3.s5, s0.s6, s1.s6, s2.s6, s3.s6, s0.s7, s1.s7, s2.s7, s3.s7, s0.s8, s1.s8, s2.s8, s3.s8, s0.s9, s1.s9, s2.s9, s3.s9⟩

def within (n base : Nat) (A : Array Float32) (B : Vector Packed10.F10 n)
    (hn : n < USize.size) (hA : base + 3*n + (n-1) < A.size)
    (hAS : A.size < USize.size) : F40 :=
  have h0 : base < USize.size := by omega
  have h1 : base+n < USize.size := by omega
  have h2 : base+2*n < USize.size := by omega
  have h3 : base+3*n < USize.size := by omega
  wordLoop (USize.ofNat n) (USize.ofNat (base)) (USize.ofNat (base+n)) (USize.ofNat (base+2*n)) (USize.ofNat (base+3*n))
    A B (USize.toNat_ofNat_of_lt' hn)
    (by simp only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' h0]; omega)
    (by simp only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' h1]; omega)
    (by simp only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' h2]; omega)
    (by simp only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' h3]; omega)
    hAS 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32

theorem within_row (n base : Nat) (A : Array Float32) (B : Vector Packed10.F10 n)
    (hn : n < USize.size) (hA : base + 3*n + (n-1) < A.size)
    (hAS : A.size < USize.size) (r : Fin 4) :
    projectRow (within n base A B hn hA hAS) r =
      Packed10Index.runDot n (base + r.val*n) A B := by
  have h0 : base < USize.size := by omega
  have h1 : base+n < USize.size := by omega
  have h2 : base+2*n < USize.size := by omega
  have h3 : base+3*n < USize.size := by omega
  rw [Packed10Index.runDot_eq]
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;>
    simp only [within, wordLoop_row, Packed10Index.loop_eq, projectRow, baseAt,
      USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' h0,
      USize.toNat_ofNat_of_lt' h1, USize.toNat_ofNat_of_lt' h2,
      USize.toNat_ofNat_of_lt' h3, USize.toNat_zero, Nat.zero_mul, Nat.one_mul, Nat.add_zero]

def run (n base : Nat) (A : Array Float32) (B : Vector Packed10.F10 n) : F40 :=
  if h : n < USize.size ∧ base + 3*n + (n-1) < A.size ∧ A.size < USize.size then
    within n base A B h.1 h.2.1 h.2.2
  else joinRows (Packed10Index.runDot n (base) A B) (Packed10Index.runDot n (base+n) A B) (Packed10Index.runDot n (base+2*n) A B) (Packed10Index.runDot n (base+3*n) A B)

theorem run_row (n base : Nat) (A : Array Float32) (B : Vector Packed10.F10 n)
    (r : Fin 4) : projectRow (run n base A B) r =
      Packed10Index.runDot n (base + r.val*n) A B := by
  unfold run
  split
  · exact within_row n base A B _ _ _ r
  · rcases r with ⟨r,hr⟩
    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
    rcases h with rfl|rfl|rfl|rfl <;>
      simp only [joinRows, projectRow, Nat.zero_mul, Nat.one_mul, Nat.add_zero]

end Submission.R11WideRows4


/- NOT_RUN design/proof asset. Append after compact RowStream and the exact
wide4 probe. This file is not a second Kernel or an implemented BMM entry.
The projection premise below is the explicit remaining interface owned by Astra.
It is a theorem parameter, never an added global assumption. -/
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

def emitBlock (batch m n p : Nat)
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
def writeBatch (batch m n p : Nat)
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

def output (batch m n p : Nat)
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


namespace Submission.R11WideActual
open FloatLib.Floats Competition

def buildTiles (batch m n p : Nat) (nativeA : Array Float32)
    (packedB : Vector (Vector (Vector Packed10.F10 n) (Packed10.groups p)) batch)
    (b : Fin batch) (h : Fin (m / 4)) : R11WideLayout.Tiles p :=
  Vector.ofFn fun g => R11WideRows4.run n ((b.val*m + 4*h.val)*n)
    nativeA ((packedB.get b).get g)

theorem buildTiles_projects (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (h : Fin (m / 4)) :
    R11WideLayout.Projects batch m n p A B R11WideRows4.lane40 b (4*h.val)
      (buildTiles batch m n p (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed10.packB batch n p B) b h) := by
  apply R11WideLayout.Projects_of_row_projection batch m n p A B
    R11WideRows4.projectRow R11WideRows4.lane40 R11WideRows4.lane40_eq
  intro g r
  simp only [buildTiles, Packed10.vector_get_ofFn, R11WideRows4.run_row, Nat.add_mul]

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) : Array Binary32 :=
  R11WideLayout.output batch m n p A B R11WideRows4.lane40 (buildTiles batch m n p)

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p) (output batch m n p A B) := by
  exact R11WideLayout.output_prefix batch m n p A B R11WideRows4.lane40
    (buildTiles batch m n p) (buildTiles_projects batch m n p A B)

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    Vector Binary32 (batch*m*p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch*m*p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.R11WideActual


