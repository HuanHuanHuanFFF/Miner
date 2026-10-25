/- R16 A4 x B2 core probe. Complete local projection proof attempt, NOT_COMPILED.
   Insert after Submission.R15PackedB2 in exact 622d. No new IEEE arithmetic.
   Four-row A panel is prepared once outside the column-group loop. -/
namespace Submission.R16A4B2
open FloatLib.Floats Competition

structure A4 where
  r0 : Float32
  r1 : Float32
  r2 : Float32
  r3 : Float32

structure F8 where
  c0r0 : Float32
  c0r1 : Float32
  c0r2 : Float32
  c0r3 : Float32
  c1r0 : Float32
  c1r1 : Float32
  c1r2 : Float32
  c1r3 : Float32

@[inline] def laneA (v : A4) (r : Fin 4) : Float32 :=
  match r.val with | 0 => v.r0 | 1 => v.r1 | 2 => v.r2 | _ => v.r3

@[inline] def projectRow (v : F8) (r : Fin 4) : R15ThinPairs.F2 :=
  match r.val with
  | 0 => ⟨v.c0r0,v.c1r0⟩
  | 1 => ⟨v.c0r1,v.c1r1⟩
  | 2 => ⟨v.c0r2,v.c1r2⟩
  | _ => ⟨v.c0r3,v.c1r3⟩

@[inline] def lane (v : F8) (r : Fin 4) (l : Nat) : Float32 :=
  match r.val with
  | 0 => if l=0 then v.c0r0 else v.c1r0
  | 1 => if l=0 then v.c0r1 else v.c1r1
  | 2 => if l=0 then v.c0r2 else v.c1r2
  | _ => if l=0 then v.c0r3 else v.c1r3

theorem lane_eq (v : F8) (r : Fin 4) (l : Nat) :
    lane v r l = R15ThinPairs.select (projectRow v r) l := by
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> rfl

def packA (n base : Nat) (A : Array Binary32) : Vector A4 n :=
  Vector.ofFn fun k =>
    ⟨ExecFloat.Binary.toFloat32 (A.getD (base+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base+n+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base+2*n+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (base+3*n+k.val) posZero)⟩

theorem packA_read (n base : Nat) (A : Array Binary32) (r : Fin 4) (k : Fin n) :
    laneA ((packA n base A).get k) r =
      ExecFloat.Binary.toFloat32 (A.getD (base+r.val*n+k.val) posZero) := by
  simp only [packA, Packed10.vector_get_ofFn]
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;>
    simp only [laneA, Nat.zero_mul, Nat.one_mul, Nat.add_zero]

def wordLoop {n : Nat} (count : USize) (A : Vector A4 n)
    (B : Vector R15PackedB2.B2 n) (hn : count.toNat=n) (k : USize)
    (c0r0 c0r1 c0r2 c0r3 c1r0 c1r1 c1r2 c1r3 : Float32) : F8 :=
  if hk : k < count then
    have hkn : k.toNat<n := by rw [←hn]; exact USize.lt_iff_toNat_lt.mp hk
    let a := A.toArray.uget k (by simpa only [A.size_toArray] using hkn)
    let b := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    wordLoop count A B hn (k+1)
      (c0r0+a.r0*b.s0) (c0r1+a.r1*b.s0) (c0r2+a.r2*b.s0) (c0r3+a.r3*b.s0)
      (c1r0+a.r0*b.s1) (c1r1+a.r1*b.s1) (c1r2+a.r2*b.s1) (c1r3+a.r3*b.s1)
  else ⟨c0r0,c0r1,c0r2,c0r3,c1r0,c1r1,c1r2,c1r3⟩
termination_by count.toNat-k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

theorem wordLoop_row {n : Nat} (count : USize) (panel : Vector A4 n)
    (B : Vector R15PackedB2.B2 n) (hn : count.toNat=n)
    (Araw : Array Binary32) (base : Nat) (r : Fin 4)
    (hread : ∀ i : Fin n, laneA (panel.get i) r =
      ExecFloat.Binary.toFloat32 (Araw.getD (base+i.val) posZero))
    (k : USize) (c0r0 c0r1 c0r2 c0r3 c1r0 c1r1 c1r2 c1r3 : Float32) :
    projectRow (wordLoop count panel B hn k c0r0 c0r1 c0r2 c0r3 c1r0 c1r1 c1r2 c1r3) r =
      R15PackedB2.loop n base Araw B k.toNat
        (projectRow ⟨c0r0,c0r1,c0r2,c0r3,c1r0,c1r1,c1r2,c1r3⟩ r).s0
        (projectRow ⟨c0r0,c0r1,c0r2,c0r3,c1r0,c1r1,c1r2,c1r3⟩ r).s1 := by
  rw [wordLoop]
  split
  · rename_i hk
    have hkn : k.toNat<n := by rw [←hn]; exact USize.lt_iff_toNat_lt.mp hk
    dsimp only
    rw [R15PackedB2.loop, dif_pos hkn]
    dsimp only
    rw [wordLoop_row count panel B hn Araw base r hread, Packed10Index.stepNat hk]
    have ha : panel.toArray.uget k (by simpa only [panel.size_toArray] using hkn) =
        panel.get ⟨k.toNat,hkn⟩ := by rfl
    have hb : B.toArray.uget k (by simpa only [B.size_toArray] using hkn) =
        B.get ⟨k.toNat,hkn⟩ := by rfl
    rw [ha,hb]
    have hh := hread ⟨k.toNat,hkn⟩
    rcases r with ⟨r,hr⟩
    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
    rcases h with rfl|rfl|rfl|rfl <;>
      simp only [projectRow,laneA] at hh ⊢ <;> simp only [hh]
  · rename_i hk
    have hkn : ¬ k.toNat<n := by
      rw [←hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    dsimp only
    rw [R15PackedB2.loop, dif_neg hkn]
    rcases r with ⟨r,hr⟩
    have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
    rcases h with rfl|rfl|rfl|rfl <;> rfl
termination_by count.toNat-k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

def runDot (n : Nat) (A : Vector A4 n) (B : Vector R15PackedB2.B2 n)
    (hn : n<USize.size) : F8 :=
  wordLoop (USize.ofNat n) A B (USize.toNat_ofNat_of_lt' hn) 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32

theorem runDot_row (n base : Nat) (A : Array Binary32)
    (B : Vector R15PackedB2.B2 n) (hn : n<USize.size) (r : Fin 4) :
    projectRow (runDot n (packA n base A) B hn) r =
      R15PackedB2.loop n (base+r.val*n) A B 0 Packed10.zero32 Packed10.zero32 := by
  have h := wordLoop_row (USize.ofNat n) (packA n base A) B
    (USize.toNat_ofNat_of_lt' hn) A (base+r.val*n) r (packA_read n base A r) 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
  change projectRow (runDot n (packA n base A) B hn) r = _ at h
  rw [h]
  rcases r with ⟨r,hr⟩
  have hr' : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases hr' with rfl|rfl|rfl|rfl <;> simp only [projectRow,USize.toNat_zero]

abbrev Tiles (p : Nat) := Vector F8 (R15ThinPairs.groups p)
abbrev PackedB (batch n p : Nat) := Vector (Vector R15PackedB2.B2 n) (batch*R15ThinPairs.groups p)

@[inline] def buildTiles (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : PackedB batch n p)
    (hn : n<USize.size) (b : Fin batch) (first : Nat) : Tiles p :=
  let panel := packA n ((b.val*m+first)*n) A.toArray
  Vector.ofFn fun g => runDot n panel (B.get (R15PackedB2.tileIndex batch p b g)) hn

theorem buildTiles_row (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : PackedB batch n p)
    (hn : n<USize.size) (b : Fin batch) (first : Nat)
    (g : Fin (R15ThinPairs.groups p)) (r : Fin 4) :
    projectRow ((buildTiles batch m n p A B hn b first).get g) r =
      R15PackedB2.loop n ((b.val*m+first+r.val)*n) A.toArray
        (B.get (R15PackedB2.tileIndex batch p b g)) 0 Packed10.zero32 Packed10.zero32 := by
  simp only [buildTiles,Packed10.vector_get_ofFn,runDot_row,Nat.add_mul]

end Submission.R16A4B2
