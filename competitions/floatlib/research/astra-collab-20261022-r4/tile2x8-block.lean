namespace Submission.Tile2x8

open FloatLib.Floats Competition

structure F16 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32
  s4 : Float32
  s5 : Float32
  s6 : Float32
  s7 : Float32
  s8 : Float32
  s9 : Float32
  s10 : Float32
  s11 : Float32
  s12 : Float32
  s13 : Float32
  s14 : Float32
  s15 : Float32
abbrev zero32 : Float32 := Packed8.zero32

@[inline] def zero16 : F16 := ⟨zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32⟩

@[inline] def low (v : F16) : Packed8.F8 := ⟨v.s0, v.s1, v.s2, v.s3, v.s4, v.s5, v.s6, v.s7⟩
@[inline] def high (v : F16) : Packed8.F8 := ⟨v.s8, v.s9, v.s10, v.s11, v.s12, v.s13, v.s14, v.s15⟩

@[inline] def rowLane (v : F16) (r : Fin 2) (l : Fin 8) : Float32 :=
  if r.val = 0 then
    match l.val with
    | 0 => v.s0
    | 1 => v.s1
    | 2 => v.s2
    | 3 => v.s3
    | 4 => v.s4
    | 5 => v.s5
    | 6 => v.s6
    | _ => v.s7
  else
    match l.val with
    | 0 => v.s8
    | 1 => v.s9
    | 2 => v.s10
    | 3 => v.s11
    | 4 => v.s12
    | 5 => v.s13
    | 6 => v.s14
    | _ => v.s15

theorem rowLane_zero (r : Fin 2) (l : Fin 8) :
    rowLane zero16 r l = zero32 := by
  rcases r with ⟨r, hr⟩
  rcases l with ⟨l, hl⟩
  have hrr : r = 0 ∨ r = 1 := by omega
  have hll : l = 0 ∨ l = 1 ∨ l = 2 ∨ l = 3 ∨ l = 4 ∨ l = 5 ∨ l = 6 ∨ l = 7 := by omega
  rcases hrr with rfl | rfl <;> rcases hll with rfl | rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> rfl

/-- Each row has its own ordered accumulation, sharing the eight right-hand values. -/
def dotRows (n base0 base1 : Nat) (A : Array Float32) (B : Vector Packed8.F8 n)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 : Float32) : F16 :=
  if hk : k < n then
    let a0 := A.getD (base0 + k) zero32
    let a1 := A.getD (base1 + k) zero32
    let v := B.get ⟨k, hk⟩
    let b0 := v.s0
    let b1 := v.s1
    let b2 := v.s2
    let b3 := v.s3
    let b4 := v.s4
    let b5 := v.s5
    let b6 := v.s6
    let b7 := v.s7
    dotRows n base0 base1 A B (k + 1)
      (s0 + a0 * b0) (s1 + a0 * b1)
      (s2 + a0 * b2) (s3 + a0 * b3)
      (s4 + a0 * b4) (s5 + a0 * b5)
      (s6 + a0 * b6) (s7 + a0 * b7)
      (s8 + a1 * b0) (s9 + a1 * b1)
      (s10 + a1 * b2) (s11 + a1 * b3)
      (s12 + a1 * b4) (s13 + a1 * b5)
      (s14 + a1 * b6) (s15 + a1 * b7)
  else ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15⟩
termination_by n - k

theorem low_dotRows (n base0 base1 : Nat) (A : Array Float32) (B : Vector Packed8.F8 n)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 : Float32) :
    low (dotRows n base0 base1 A B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15) =
      Packed8.dot8 n base0 A B k s0 s1 s2 s3 s4 s5 s6 s7 := by
  by_cases hk : k < n
  · rw [dotRows, Packed8.dot8]
    simp only [dif_pos hk]
    try dsimp only
    exact low_dotRows n base0 base1 A B (k + 1)
      (s0 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s0)
      (s1 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s1)
      (s2 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s2)
      (s3 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s3)
      (s4 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s4)
      (s5 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s5)
      (s6 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s6)
      (s7 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s7)
      (s8 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s0)
      (s9 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s1)
      (s10 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s2)
      (s11 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s3)
      (s12 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s4)
      (s13 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s5)
      (s14 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s6)
      (s15 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s7)
  · rw [dotRows, Packed8.dot8]
    simp only [dif_neg hk]
    rfl
termination_by n - k

theorem high_dotRows (n base0 base1 : Nat) (A : Array Float32) (B : Vector Packed8.F8 n)
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 : Float32) :
    high (dotRows n base0 base1 A B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15) =
      Packed8.dot8 n base1 A B k s8 s9 s10 s11 s12 s13 s14 s15 := by
  by_cases hk : k < n
  · rw [dotRows, Packed8.dot8]
    simp only [dif_pos hk]
    try dsimp only
    exact high_dotRows n base0 base1 A B (k + 1)
      (s0 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s0)
      (s1 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s1)
      (s2 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s2)
      (s3 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s3)
      (s4 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s4)
      (s5 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s5)
      (s6 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s6)
      (s7 + A.getD (base0 + k) zero32 * (B.get ⟨k, hk⟩).s7)
      (s8 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s0)
      (s9 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s1)
      (s10 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s2)
      (s11 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s3)
      (s12 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s4)
      (s13 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s5)
      (s14 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s6)
      (s15 + A.getD (base1 + k) zero32 * (B.get ⟨k, hk⟩).s7)
  · rw [dotRows, Packed8.dot8]
    simp only [dif_neg hk]
    rfl
termination_by n - k

theorem dotRows_lane (n base0 base1 baseB p : Nat) (Araw Braw : Array Binary32)
    (B : Vector Packed8.F8 n) (r : Fin 2) (l : Fin 8)
    (hb : ∀ i : Fin n, Packed8.lane (B.get i) l =
      ExecFloat.Binary.toFloat32 (Braw.getD (baseB + i.val * p) posZero))
    (k : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 : Float32) :
    rowLane (dotRows n base0 base1 (Araw.map ExecFloat.Binary.toFloat32)
      B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15) r l =
      NativeFinal.dotLoop n (if r.val = 0 then base0 else base1) baseB p Araw Braw k
        (rowLane ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15⟩ r l) := by
  rcases r with ⟨r, hr⟩
  have h : r = 0 ∨ r = 1 := by omega
  rcases h with rfl | rfl
  · change Packed8.lane
      (low (dotRows n base0 base1 (Araw.map ExecFloat.Binary.toFloat32)
        B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15)) l =
      NativeFinal.dotLoop n base0 baseB p Araw Braw k
        (Packed8.lane ⟨s0, s1, s2, s3, s4, s5, s6, s7⟩ l)
    rw [low_dotRows]
    exact Packed8.dot8_lane n base0 baseB p Araw Braw B l hb k s0 s1 s2 s3 s4 s5 s6 s7
  · change Packed8.lane
      (high (dotRows n base0 base1 (Araw.map ExecFloat.Binary.toFloat32)
        B k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15)) l =
      NativeFinal.dotLoop n base1 baseB p Araw Braw k
        (Packed8.lane ⟨s8, s9, s10, s11, s12, s13, s14, s15⟩ l)
    rw [high_dotRows]
    exact Packed8.dot8_lane n base1 baseB p Araw Braw B l hb k s8 s9 s10 s11 s12 s13 s14 s15

def wordLoop {n : Nat} (count base0 base1 : USize) (A : Array Float32)
    (B : Vector Packed8.F8 n) (hn : count.toNat = n)
    (h0 : base0.toNat + (count.toNat - 1) < A.size)
    (h1 : base1.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 : Float32) : F16 :=
  if hk : k < count then
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    have ha0 := Packed8Index.boundA base0.toNat count.toNat k.toNat A.size h0
      (USize.lt_iff_toNat_lt.mp hk)
    have ha1 := Packed8Index.boundA base1.toNat count.toNat k.toNat A.size h1
      (USize.lt_iff_toNat_lt.mp hk)
    let a0 := A.uget (base0 + k)
      (by rw [Packed8Index.addNat base0 k (Nat.lt_trans ha0 hAS)]; exact ha0)
    let a1 := A.uget (base1 + k)
      (by rw [Packed8Index.addNat base1 k (Nat.lt_trans ha1 hAS)]; exact ha1)
    let v := B.toArray.uget k (by simpa only [B.size_toArray] using hkn)
    let b0 := v.s0
    let b1 := v.s1
    let b2 := v.s2
    let b3 := v.s3
    let b4 := v.s4
    let b5 := v.s5
    let b6 := v.s6
    let b7 := v.s7
    wordLoop count base0 base1 A B hn h0 h1 hAS (k + 1)
      (s0 + a0 * b0) (s1 + a0 * b1)
      (s2 + a0 * b2) (s3 + a0 * b3)
      (s4 + a0 * b4) (s5 + a0 * b5)
      (s6 + a0 * b6) (s7 + a0 * b7)
      (s8 + a1 * b0) (s9 + a1 * b1)
      (s10 + a1 * b2) (s11 + a1 * b3)
      (s12 + a1 * b4) (s13 + a1 * b5)
      (s14 + a1 * b6) (s15 + a1 * b7)
  else ⟨s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15⟩
termination_by count.toNat - k.toNat
decreasing_by
  apply Packed8Index.next_decreases
  assumption

theorem wordLoop_eq {n : Nat} (count base0 base1 : USize) (A : Array Float32)
    (B : Vector Packed8.F8 n) (hn : count.toNat = n)
    (h0 : base0.toNat + (count.toNat - 1) < A.size)
    (h1 : base1.toNat + (count.toNat - 1) < A.size)
    (hAS : A.size < USize.size)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 : Float32) :
    wordLoop count base0 base1 A B hn h0 h1 hAS k s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 =
      dotRows n base0.toNat base1.toNat A B k.toNat s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 := by
  rw [wordLoop]
  split
  · rename_i hk
    have hkn : k.toNat < n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    have ha0 := Packed8Index.boundA base0.toNat count.toNat k.toNat A.size h0
      (USize.lt_iff_toNat_lt.mp hk)
    have ha1 := Packed8Index.boundA base1.toNat count.toNat k.toNat A.size h1
      (USize.lt_iff_toNat_lt.mp hk)
    rw [dotRows, dif_pos hkn]
    try dsimp only
    rw [wordLoop_eq, Packed8Index.stepNat hk]
    simp only [Packed8Index.ugetA_getD,
      Packed8Index.addNat base0 k (Nat.lt_trans ha0 hAS),
      Packed8Index.addNat base1 k (Nat.lt_trans ha1 hAS)]
    rfl
  · rename_i hk
    have hkn : ¬ k.toNat < n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [dotRows, dif_neg hkn]
termination_by count.toNat - k.toNat
decreasing_by
  apply Packed8Index.next_decreases
  assumption

@[inline] def within (n base0 base1 : Nat) (A : Array Float32) (B : Vector Packed8.F8 n)
    (hn : n < USize.size) (hbase0 : base0 < USize.size) (hbase1 : base1 < USize.size)
    (h0 : base0 + (n - 1) < A.size) (h1 : base1 + (n - 1) < A.size)
    (hAS : A.size < USize.size) : F16 :=
  wordLoop (USize.ofNat n) (USize.ofNat base0) (USize.ofNat base1) A B
    (USize.toNat_ofNat_of_lt' hn)
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' hbase0] using h0)
    (by simpa only [USize.toNat_ofNat_of_lt' hn, USize.toNat_ofNat_of_lt' hbase1] using h1)
    hAS 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32

theorem within_eq (n base0 base1 : Nat) (A : Array Float32) (B : Vector Packed8.F8 n)
    (hn : n < USize.size) (hbase0 : base0 < USize.size) (hbase1 : base1 < USize.size)
    (h0 : base0 + (n - 1) < A.size) (h1 : base1 + (n - 1) < A.size)
    (hAS : A.size < USize.size) :
    within n base0 base1 A B hn hbase0 hbase1 h0 h1 hAS =
      dotRows n base0 base1 A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 := by
  simp only [within, wordLoop_eq, USize.toNat_ofNat_of_lt' hn,
    USize.toNat_ofNat_of_lt' hbase0, USize.toNat_ofNat_of_lt' hbase1, USize.toNat_zero]

@[inline] def runDot (n base0 base1 : Nat) (A : Array Float32) (B : Vector Packed8.F8 n) : F16 :=
  if h : n < USize.size ∧ base0 < USize.size ∧ base1 < USize.size ∧
      base0 + (n - 1) < A.size ∧ base1 + (n - 1) < A.size ∧ A.size < USize.size then
    within n base0 base1 A B h.1 h.2.1 h.2.2.1 h.2.2.2.1 h.2.2.2.2.1 h.2.2.2.2.2
  else dotRows n base0 base1 A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32

theorem runDot_eq (n base0 base1 : Nat) (A : Array Float32) (B : Vector Packed8.F8 n) :
    runDot n base0 base1 A B =
      dotRows n base0 base1 A B 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 := by
  unfold runDot
  split
  · rename_i h
    exact within_eq n base0 base1 A B h.1 h.2.1 h.2.2.1 h.2.2.2.1 h.2.2.2.2.1 h.2.2.2.2.2
  · rfl

@[inline] def rowGroups (m : Nat) : Nat := (m + 1) / 2

theorem row_group_bound (m i : Nat) (hi : i < m) : i / 2 < rowGroups m := by
  unfold rowGroups
  omega

theorem row_decomposition (i : Nat) : 2 * (i / 2) + i % 2 = i := by omega

theorem rowBase_eq (b m h n : Nat) (r : Fin 2) :
    (if r.val = 0 then (b * m + 2 * h) * n else (b * m + 2 * h) * n + n) =
      (b * m + (2 * h + r.val)) * n := by
  rcases r with ⟨r, hr⟩
  have h : r = 0 ∨ r = 1 := by omega
  rcases h with rfl | rfl <;> simp [Nat.add_mul, Nat.add_assoc]

def tileResults (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector Packed8.F8 n) (Packed8.groups p)) batch) :
    Vector (Vector (Vector F16 (Packed8.groups p)) (rowGroups m)) batch :=
  Vector.ofFn fun b =>
    Vector.ofFn fun h =>
      let base0 := (b.val * m + 2 * h.val) * n
      Vector.ofFn fun g => runDot n base0 (base0 + n) A ((B.get b).get g)

theorem tileResults_get (batch m n p : Nat) (A : Array Float32)
    (B : Vector (Vector (Vector Packed8.F8 n) (Packed8.groups p)) batch)
    (b : Fin batch) (h : Fin (rowGroups m)) (g : Fin (Packed8.groups p)) :
    (((tileResults batch m n p A B).get b).get h).get g =
      dotRows n ((b.val * m + 2 * h.val) * n) ((b.val * m + 2 * h.val) * n + n)
        A ((B.get b).get g) 0 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 := by
  simp only [tileResults, Packed8.vector_get_ofFn, runDot_eq]

theorem tile_finish (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (h : Fin (rowGroups m)) (g : Fin (Packed8.groups p))
    (r : Fin 2) (l : Fin 8) (hcol : 8 * g.val + l.val < p) :
    Packed8.finish n ((b.val * m + (2 * h.val + r.val)) * n)
      (b.val * n * p + (8 * g.val + l.val)) p A.toArray B.toArray
      (rowLane ((((tileResults batch m n p (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed8.packB batch n p B)).get b).get h).get g) r l) =
      NativeFinal.dot n ((b.val * m + (2 * h.val + r.val)) * n)
        (b.val * n * p + (8 * g.val + l.val)) p A.toArray B.toArray := by
  rw [tileResults_get]
  apply Packed8.finish_eq_dot
  have hb : ∀ k : Fin n,
      Packed8.lane ((((Packed8.packB batch n p B).get b).get g).get k) l =
        ExecFloat.Binary.toFloat32
          (B.toArray.getD ((b.val * n * p + (8 * g.val + l.val)) + k.val * p) posZero) := by
    intro k
    rw [Packed8.packB_lane batch n p B b g k l hcol]
    rw [index_address (b.val * n) k.val p (8 * g.val + l.val)]
  have hs := dotRows_lane n ((b.val * m + 2 * h.val) * n)
    ((b.val * m + 2 * h.val) * n + n)
    (b.val * n * p + (8 * g.val + l.val)) p A.toArray B.toArray
    (((Packed8.packB batch n p B).get b).get g) r l hb 0
    zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32 zero32
  have hz : rowLane (⟨zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32, zero32⟩ : F16)
      r l = zero32 := rowLane_zero r l
  rw [hz, rowBase_eq] at hs
  exact hs

def outputFromTiles (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (tiles : Vector (Vector (Vector F16 (Packed8.groups p)) (rowGroups m)) batch)
    (q : Fin (batch * m * p)) : Binary32 :=
  let d := bmmDecodeC m p q.val
  let b : Fin batch := ⟨d.1, (Packed8.decode_bounds batch m p q).1⟩
  let h : Fin (rowGroups m) :=
    ⟨d.2.1 / 2, row_group_bound m d.2.1 (Packed8.decode_bounds batch m p q).2.1⟩
  let g : Fin (Packed8.groups p) :=
    ⟨d.2.2 / 8, Packed8.groups_pos_of_col p d.2.2 (Packed8.decode_bounds batch m p q).2.2⟩
  let r : Fin 2 := ⟨d.2.1 % 2, Nat.mod_lt _ (by decide)⟩
  let l : Fin 8 := ⟨d.2.2 % 8, Nat.mod_lt _ (by decide)⟩
  Packed8.finish n ((d.1 * m + d.2.1) * n) (d.1 * n * p + d.2.2) p A.toArray B.toArray
    (rowLane (((tiles.get b).get h).get g) r l)

theorem outputFromTiles_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (q : Fin (batch * m * p)) :
    outputFromTiles batch m n p A B
      (tileResults batch m n p (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed8.packB batch n p B)) q =
      let (b, i, j) := bmmDecodeC m p q.val
      NativeFinal.dot n ((b * m + i) * n) (b * n * p + j) p A.toArray B.toArray := by
  let d := bmmDecodeC m p q.val
  let b : Fin batch := ⟨d.1, (Packed8.decode_bounds batch m p q).1⟩
  let h : Fin (rowGroups m) :=
    ⟨d.2.1 / 2, row_group_bound m d.2.1 (Packed8.decode_bounds batch m p q).2.1⟩
  let g : Fin (Packed8.groups p) :=
    ⟨d.2.2 / 8, Packed8.groups_pos_of_col p d.2.2 (Packed8.decode_bounds batch m p q).2.2⟩
  let r : Fin 2 := ⟨d.2.1 % 2, Nat.mod_lt _ (by decide)⟩
  let l : Fin 8 := ⟨d.2.2 % 8, Nat.mod_lt _ (by decide)⟩
  have hr : 2 * h.val + r.val = d.2.1 := row_decomposition d.2.1
  have hc : 8 * g.val + l.val = d.2.2 := Packed8.column_decomposition d.2.2
  have hcol : 8 * g.val + l.val < p := by
    rw [hc]
    exact (Packed8.decode_bounds batch m p q).2.2
  have ht := tile_finish batch m n p A B b h g r l hcol
  change Packed8.finish n ((b.val * m + d.2.1) * n) (b.val * n * p + d.2.2) p
      A.toArray B.toArray
      (rowLane ((((tileResults batch m n p (A.toArray.map ExecFloat.Binary.toFloat32)
        (Packed8.packB batch n p B)).get b).get h).get g) r l) =
    NativeFinal.dot n ((b.val * m + d.2.1) * n) (b.val * n * p + d.2.2) p A.toArray B.toArray
  simpa only [hr, hc] using ht

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    Vector Binary32 (batch * m * p) :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  let packedB := Packed8.packB batch n p B
  let tiles := tileResults batch m n p nativeA packedB
  Vector.ofFn (outputFromTiles batch m n p A B tiles)

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  unfold core referenceBmm
  try dsimp only
  apply congrArg (fun f : Fin (batch * m * p) → Binary32 => Vector.ofFn f)
  funext q
  rw [outputFromTiles_eq]
  try dsimp only
  rw [NativeFinal.dot_eq]
  simp only [add_eq, mul_eq]
  apply congrArg (fun f : Binary32 → Fin n → Binary32 => Fin.foldl n f posZero)
  funext acc k
  have hi := index_address ((bmmDecodeC m p q.val).1 * n) k.val p
    (bmmDecodeC m p q.val).2.2
  rw [hi]

end Submission.Tile2x8

namespace Submission

open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then referenceBmm batch m n p A B
  else if n = 0 then referenceBmm batch m n p A B
  else Tile2x8.core batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  have h : bmm batch m n p A B = referenceBmm batch m n p A B := by
    unfold bmm
    split
    · rfl
    · split
      · rfl
      · exact Tile2x8.core_eq_reference batch m n p A B
  exact (congrArg (fun v : Vector Binary32 (batch * m * p) => v.get) h).trans
    (referenceBmm_spec batch m n p A B)

end Submission
