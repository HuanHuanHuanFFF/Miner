/- R11 cross-row p=2 kernel. Four independent row instances, including across
   batch boundaries; each output retains its own ordered mul/add chain. -/
namespace Submission.R11CrossRows
open FloatLib.Floats Competition

structure P12 where
  a0 : Float32
  a1 : Float32
  a2 : Float32
  a3 : Float32
  b0 : Float32
  b1 : Float32
  b2 : Float32
  b3 : Float32
  b4 : Float32
  b5 : Float32
  b6 : Float32
  b7 : Float32

structure F8 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32
  s4 : Float32
  s5 : Float32
  s6 : Float32
  s7 : Float32

structure W8 where
  w0 : UInt32
  w1 : UInt32
  w2 : UInt32
  w3 : UInt32
  w4 : UInt32
  w5 : UInt32
  w6 : UInt32
  w7 : UInt32

def select4 (x0 x1 x2 x3 r : Nat) : Nat :=
  match r with | 0 => x0 | 1 => x1 | 2 => x2 | _ => x3

def lane (v : F8) (l : Fin 8) : Float32 :=
  match l.val with
  | 0 => v.s0 | 1 => v.s1 | 2 => v.s2 | 3 => v.s3
  | 4 => v.s4 | 5 => v.s5 | 6 => v.s6 | _ => v.s7

def inputA (v : P12) (l : Fin 8) : Float32 :=
  match l.val % 4 with | 0 => v.a0 | 1 => v.a1 | 2 => v.a2 | _ => v.a3

def inputB (v : P12) (l : Fin 8) : Float32 :=
  match l.val with
  | 0 => v.b0 | 1 => v.b1 | 2 => v.b2 | 3 => v.b3
  | 4 => v.b4 | 5 => v.b5 | 6 => v.b6 | _ => v.b7

def zero8 : F8 :=
  let z := Float32.ofBits 0
  ⟨z,z,z,z,z,z,z,z⟩

def update (s : F8) (v : P12) : F8 :=
  ⟨s.s0 + v.a0 * v.b0, s.s1 + v.a1 * v.b1,
   s.s2 + v.a2 * v.b2, s.s3 + v.a3 * v.b3,
   s.s4 + v.a0 * v.b4, s.s5 + v.a1 * v.b5,
   s.s6 + v.a2 * v.b6, s.s7 + v.a3 * v.b7⟩

theorem lane_zero (l : Fin 8) : lane zero8 l = Float32.ofBits 0 := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;> rfl

theorem lane_update (s : F8) (v : P12) (l : Fin 8) :
    lane (update s v) l = lane s l + inputA v l * inputB v l := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;> rfl

def packGeneral (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32) : Vector P12 n :=
  Vector.ofFn fun k =>
    let kp := k.val * p
    ⟨ExecFloat.Binary.toFloat32 (A.getD (a0+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a1+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a2+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a3+k.val) posZero),
     ExecFloat.Binary.toFloat32 (B.getD (b0+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD (b1+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD (b2+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD (b3+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD ((b0+1)+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD ((b1+1)+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD ((b2+1)+kp) posZero),
     ExecFloat.Binary.toFloat32 (B.getD ((b3+1)+kp) posZero)⟩

theorem packGeneral_a (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Fin n) (l : Fin 8) :
    inputA ((packGeneral n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get k) l =
      ExecFloat.Binary.toFloat32 (A.getD (select4 a0 a1 a2 a3 (l.val%4)+k.val) posZero) := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;>
    simp [packGeneral, Packed10.vector_get_ofFn, inputA, select4]

theorem packGeneral_b (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Fin n) (l : Fin 8) :
    inputB ((packGeneral n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get k) l =
      ExecFloat.Binary.toFloat32
        (B.getD ((select4 b0 b1 b2 b3 (l.val%4)+l.val/4)+k.val*p) posZero) := by
  rcases l with ⟨l,hl⟩
  have h : l=0 ∨ l=1 ∨ l=2 ∨ l=3 ∨ l=4 ∨ l=5 ∨ l=6 ∨ l=7 := by omega
  rcases h with rfl|rfl|rfl|rfl|rfl|rfl|rfl|rfl <;>
    simp [packGeneral, Packed10.vector_get_ofFn, inputB, select4]


def packShared (n p a0 a1 a2 a3 b0 : Nat) (A B : Array Binary32) : Vector P12 n :=
  Vector.ofFn fun k =>
    let kp := k.val*p
    let c0 := ExecFloat.Binary.toFloat32 (B.getD (b0+kp) posZero)
    let c1 := ExecFloat.Binary.toFloat32 (B.getD ((b0+1)+kp) posZero)
    ⟨ExecFloat.Binary.toFloat32 (A.getD (a0+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a1+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a2+k.val) posZero),
     ExecFloat.Binary.toFloat32 (A.getD (a3+k.val) posZero),
     c0,c0,c0,c0,c1,c1,c1,c1⟩

theorem packShared_eq (n p a0 a1 a2 a3 b0 : Nat) (A B : Array Binary32) :
    packShared n p a0 a1 a2 a3 b0 A B =
      packGeneral n p a0 a1 a2 a3 b0 b0 b0 b0 A B := by rfl

def pack (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32) : Vector P12 n :=
  if b1=b0 ∧ b2=b0 ∧ b3=b0 then packShared n p a0 a1 a2 a3 b0 A B
  else packGeneral n p a0 a1 a2 a3 b0 b1 b2 b3 A B

theorem pack_eq_general (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32) :
    pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B = packGeneral n p a0 a1 a2 a3 b0 b1 b2 b3 A B := by
  unfold pack
  split
  · rename_i h
    rcases h with ⟨h1,h2,h3⟩
    subst b1; subst b2; subst b3
    exact packShared_eq n p a0 a1 a2 a3 b0 A B
  · rfl

theorem pack_a (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Fin n) (l : Fin 8) :
    inputA ((pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get k) l =
      ExecFloat.Binary.toFloat32 (A.getD (select4 a0 a1 a2 a3 (l.val%4)+k.val) posZero) := by
  rw [pack_eq_general]
  exact packGeneral_a n p a0 a1 a2 a3 b0 b1 b2 b3 A B k l

theorem pack_b (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Fin n) (l : Fin 8) :
    inputB ((pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get k) l =
      ExecFloat.Binary.toFloat32
        (B.getD ((select4 b0 b1 b2 b3 (l.val%4)+l.val/4)+k.val*p) posZero) := by
  rw [pack_eq_general]
  exact packGeneral_b n p a0 a1 a2 a3 b0 b1 b2 b3 A B k l

def natLoop (n : Nat) (v : Vector P12 n) (k : Nat) (s : F8) : F8 :=
  if hk : k<n then natLoop n v (k+1) (update s (v.get ⟨k,hk⟩)) else s
termination_by n-k

theorem natLoop_lane (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (k : Nat) (s : F8) (l : Fin 8) :
    lane (natLoop n (pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B) k s) l =
      NativeFinal.dotLoop n (select4 a0 a1 a2 a3 (l.val%4))
        (select4 b0 b1 b2 b3 (l.val%4)+l.val/4) p A B k (lane s l) := by
  rw [natLoop]
  split
  · rename_i hk
    rw [NativeFinal.dotLoop, dif_pos hk]
    dsimp only
    have ih := natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B (k+1)
      (update s ((pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B).get ⟨k,hk⟩)) l
    rw [lane_update, pack_a, pack_b] at ih
    exact ih
  · rename_i hk
    rw [NativeFinal.dotLoop, dif_neg hk]
termination_by n-k

def wordLoop (n : Nat) (v : Vector P12 n) (count : USize) (hn : count.toNat=n)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 : Float32) : F8 :=
  if hk : k<count then
    have hkn : k.toNat<n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    let t := v.toArray.uget k (by simpa only [v.size_toArray] using hkn)
    wordLoop n v count hn (k+1)
      (s0+t.a0*t.b0) (s1+t.a1*t.b1) (s2+t.a2*t.b2) (s3+t.a3*t.b3)
      (s4+t.a0*t.b4) (s5+t.a1*t.b5) (s6+t.a2*t.b6) (s7+t.a3*t.b7)
  else ⟨s0,s1,s2,s3,s4,s5,s6,s7⟩
termination_by count.toNat-k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

theorem wordLoop_eq (n : Nat) (v : Vector P12 n) (count : USize) (hn : count.toNat=n)
    (k : USize) (s0 s1 s2 s3 s4 s5 s6 s7 : Float32) :
    wordLoop n v count hn k s0 s1 s2 s3 s4 s5 s6 s7 =
      natLoop n v k.toNat ⟨s0,s1,s2,s3,s4,s5,s6,s7⟩ := by
  rw [wordLoop]
  split
  · rename_i hk
    have hkn : k.toNat<n := by rw [← hn]; exact USize.lt_iff_toNat_lt.mp hk
    have hread : v.toArray.uget k (by simpa only [v.size_toArray] using hkn) =
        v.get ⟨k.toNat,hkn⟩ := rfl
    rw [natLoop, dif_pos hkn]
    dsimp only [update]
    rw [hread, wordLoop_eq, Packed10Index.stepNat hk]
  · rename_i hk
    have hkn : ¬k.toNat<n := by
      rw [← hn]
      simpa only [USize.lt_iff_toNat_lt] using hk
    rw [natLoop, dif_neg hkn]
termination_by count.toNat-k.toNat
decreasing_by all_goals exact Packed10Index.next_decreases (by assumption)

def dot8 (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) : F8 :=
  let v := pack n p a0 a1 a2 a3 b0 b1 b2 b3 A B
  let z := Float32.ofBits 0
  wordLoop n v (USize.ofNat n) (USize.toNat_ofNat_of_lt' hn) 0 z z z z z z z z

theorem dot8_lane (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) (l : Fin 8) :
    lane (dot8 n p a0 a1 a2 a3 b0 b1 b2 b3 A B hn) l =
      NativeFinal.dotLoop n (select4 a0 a1 a2 a3 (l.val%4))
        (select4 b0 b1 b2 b3 (l.val%4)+l.val/4) p A B 0 (Float32.ofBits 0) := by
  unfold dot8
  rw [wordLoop_eq, USize.toNat_zero]
  simpa only [lane_zero] using
    natLoop_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B 0 zero8 l

def laneIndex (r : Fin 4) (j : Fin 2) : Fin 8 :=
  ⟨r.val+4*j.val, by have hr:=r.isLt; have hj:=j.isLt; omega⟩

def wordAt (v : W8) (r : Fin 4) (j : Fin 2) : UInt32 :=
  match r.val with
  | 0 => if j.val=0 then v.w0 else v.w1
  | 1 => if j.val=0 then v.w2 else v.w3
  | 2 => if j.val=0 then v.w4 else v.w5
  | _ => if j.val=0 then v.w6 else v.w7

theorem rebuild (q : Binary32) : ExecFloat.Binary.ofBits32 q.raw.1 = q :=
  ExecFloat.Binary.ofBits32_toBits32 q

def finish8 (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32) (s : F8) : W8 :=
  ⟨(Packed10.finish n a0 b0 p A B s.s0).raw.1,
   (Packed10.finish n a0 (b0+1) p A B s.s4).raw.1,
   (Packed10.finish n a1 b1 p A B s.s1).raw.1,
   (Packed10.finish n a1 (b1+1) p A B s.s5).raw.1,
   (Packed10.finish n a2 b2 p A B s.s2).raw.1,
   (Packed10.finish n a2 (b2+1) p A B s.s6).raw.1,
   (Packed10.finish n a3 b3 p A B s.s3).raw.1,
   (Packed10.finish n a3 (b3+1) p A B s.s7).raw.1⟩

theorem finish8_word (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (s : F8) (r : Fin 4) (j : Fin 2) :
    ExecFloat.Binary.ofBits32 (wordAt (finish8 n p a0 a1 a2 a3 b0 b1 b2 b3 A B s) r j) =
      Packed10.finish n (select4 a0 a1 a2 a3 r.val) (select4 b0 b1 b2 b3 r.val+j.val)
        p A B (lane s (laneIndex r j)) := by
  rcases r with ⟨r,hr⟩; rcases j with ⟨j,hj⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  have hc : j=0 ∨ j=1 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> rcases hc with rfl|rfl <;>
    simp [finish8, wordAt, select4, lane, laneIndex, rebuild]

def blockAt (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) : W8 :=
  finish8 n p a0 a1 a2 a3 b0 b1 b2 b3 A B
    (dot8 n p a0 a1 a2 a3 b0 b1 b2 b3 A B hn)

theorem blockAt_word (n p a0 a1 a2 a3 b0 b1 b2 b3 : Nat) (A B : Array Binary32)
    (hn : n<USize.size) (r : Fin 4) (j : Fin 2) :
    ExecFloat.Binary.ofBits32 (wordAt (blockAt n p a0 a1 a2 a3 b0 b1 b2 b3 A B hn) r j) =
      NativeFinal.dot n (select4 a0 a1 a2 a3 r.val) (select4 b0 b1 b2 b3 r.val+j.val) p A B := by
  unfold blockAt
  rw [finish8_word]
  apply Packed10.finish_eq_dot
  have h := dot8_lane n p a0 a1 a2 a3 b0 b1 b2 b3 A B hn (laneIndex r j)
  rcases r with ⟨r,hr⟩; rcases j with ⟨j,hj⟩
  have hrow : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  have hcol : j=0 ∨ j=1 := by omega
  rcases hrow with rfl|rfl|rfl|rfl <;> rcases hcol with rfl|rfl <;>
    simpa [laneIndex, select4, Packed10.zero32] using h

def blockRows (m n p g : Nat) (A B : Array Binary32) (hn : n<USize.size) : W8 :=
  let r0 := 4*g
  let r1 := 4*g+1
  let r2 := 4*g+2
  let r3 := 4*g+3
  blockAt n p (r0*n) (r1*n) (r2*n) (r3*n)
    (r0/m*n*p) (r1/m*n*p) (r2/m*n*p) (r3/m*n*p) A B hn

theorem blockRows_word (m n p g : Nat) (A B : Array Binary32) (hn : n<USize.size)
    (r : Fin 4) (j : Fin 2) :
    ExecFloat.Binary.ofBits32 (wordAt (blockRows m n p g A B hn) r j) =
      NativeFinal.dot n ((4*g+r.val)*n) (((4*g+r.val)/m)*n*p+j.val) p A B := by
  unfold blockRows
  rw [blockAt_word]
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> simp [select4]

def groups (rows : Nat) : Nat := (rows+3)/4

theorem group_bound (rows r : Nat) (hr : r<rows) : r/4 < groups rows := by
  unfold groups
  omega

theorem row_decomposition (r : Nat) : 4*(r/4)+r%4=r := by omega

def words (batch m n p : Nat) (A B : Array Binary32) (hn : n<USize.size) :
    Vector W8 (groups (batch*m)) :=
  Vector.ofFn fun g => blockRows m n p g.val A B hn

def rowWord (batch m p : Nat) (v : Vector W8 (groups (batch*m)))
    (r : Fin (batch*m)) (j : Fin p) (hp : p≤2) : Binary32 :=
  let g : Fin (groups (batch*m)) := ⟨r.val/4, group_bound _ _ r.isLt⟩
  let rr : Fin 4 := ⟨r.val%4, Nat.mod_lt _ (by decide)⟩
  let jj : Fin 2 := ⟨j.val, Nat.lt_of_lt_of_le j.isLt hp⟩
  ExecFloat.Binary.ofBits32 (wordAt (v.get g) rr jj)

theorem rowWord_eq (batch m n p : Nat) (A B : Array Binary32) (hn : n<USize.size)
    (r : Fin (batch*m)) (j : Fin p) (hp : p≤2) :
    rowWord batch m p (words batch m n p A B hn) r j hp =
      NativeFinal.dot n ((r.val/m*m+r.val%m)*n) (r.val/m*n*p+j.val) p A B := by
  unfold rowWord words
  rw [Packed10.vector_get_ofFn, blockRows_word]
  have hr : r.val/m*m+r.val%m=r.val := by
    simpa only [Nat.mul_comm] using Nat.div_add_mod r.val m
  simp only [row_decomposition, hr]

def core (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) (hp : p≤2) :
    Vector Binary32 (batch*m*p) :=
  let v := words batch m n p A.toArray B.toArray hn
  Vector.ofFn fun q =>
    have hp0 : 0<p := by
      have hq := q.isLt
      by_contra h
      have hz : p=0 := by omega
      simp [hz] at hq
    let r : Fin (batch*m) := ⟨q.val/p, (Nat.div_lt_iff_lt_mul hp0).2 q.isLt⟩
    let j : Fin p := ⟨q.val%p, Nat.mod_lt _ hp0⟩
    rowWord batch m p v r j hp

theorem core_eq_rows (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) (hn : n<USize.size) (hp : p≤2) :
    core batch m n p A B hn hp = DirectRows.core batch m n p A B := by
  apply Vector.ext
  intro q hq
  have hp0 : 0<p := by
    by_contra h
    have hz : p=0 := by omega
    simp [hz] at hq
  have hr : q/p < batch*m := (Nat.div_lt_iff_lt_mul hp0).2 hq
  have hj : q%p < p := Nat.mod_lt _ hp0
  have h := rowWord_eq batch m n p A.toArray B.toArray hn ⟨q/p,hr⟩ ⟨q%p,hj⟩ hp
  simpa only [core, DirectRows.core, Vector.getElem_ofFn, Vector.getElem_flatMap] using h

end Submission.R11CrossRows

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  if h : p=2 ∧ 4≤batch*m ∧ 0<n ∧ n<USize.size ∧
      A.toArray.size<USize.size ∧ B.toArray.size<USize.size ∧ batch*m*p<USize.size then
    R11CrossRows.core batch m n p A B h.2.2.2.1 (Nat.le_of_eq h.1)
  else bmmBeforeR11Cross batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rw [R11CrossRows.core_eq_rows, DirectRows.core_eq, DirectSmall.core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeR11Cross_spec batch m n p A B

end Submission
