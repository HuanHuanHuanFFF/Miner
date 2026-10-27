/- R19 temporal B2: full source draft, NOT_COMPILED.
   Four consecutive k positions share one prepared record; two ordered chains.
   Authored from retained B2 and the local R18 temporal prototype. -/
namespace Submission.R19Temporal
open FloatLib.Floats Competition

structure B8 where
  k0c0 : Float32
  k0c1 : Float32
  k1c0 : Float32
  k1c1 : Float32
  k2c0 : Float32
  k2c1 : Float32
  k3c0 : Float32
  k3c1 : Float32

@[inline] def read (A : Array Binary32) (i : Nat) : Float32 :=
  ExecFloat.Binary.toFloat32 (A.getD i posZero)

@[inline] def packet (n base p k : Nat) (B : Array Binary32) : B8 :=
  ⟨if k < n then read B (base + k*p) else Packed10.zero32,
   if k < n then read B (base + 1 + k*p) else Packed10.zero32,
   if k+1 < n then read B (base + (k+1)*p) else Packed10.zero32,
   if k+1 < n then read B (base + 1 + (k+1)*p) else Packed10.zero32,
   if k+2 < n then read B (base + (k+2)*p) else Packed10.zero32,
   if k+2 < n then read B (base + 1 + (k+2)*p) else Packed10.zero32,
   if k+3 < n then read B (base + (k+3)*p) else Packed10.zero32,
   if k+3 < n then read B (base + 1 + (k+3)*p) else Packed10.zero32⟩

def pack (n base p : Nat) (B : Array Binary32) : Vector B8 ((n+3)/4) :=
  Vector.ofFn fun t => packet n base p (4*t.val) B

theorem pack_get (n base p : Nat) (B : Array Binary32) (t : Fin ((n+3)/4)) :
    (pack n base p B).get t = packet n base p (4*t.val) B := by
  simp only [pack, Packed10.vector_get_ofFn]

def loop (n baseA : Nat) (A : Array Binary32)
    (B : Vector B8 ((n+3)/4)) (t : Nat) (s0 s1 : Float32) : R15ThinPairs.F2 :=
  let k := 4*t
  if h3 : k+3 < n then
    have ht : t < (n+3)/4 := by dsimp [k] at h3; omega
    let b := B.get ⟨t,ht⟩
    let a0 := read A (baseA+k)
    let s0 := s0+a0*b.k0c0
    let s1 := s1+a0*b.k0c1
    let a1 := read A (baseA+k+1)
    let s0 := s0+a1*b.k1c0
    let s1 := s1+a1*b.k1c1
    let a2 := read A (baseA+k+2)
    let s0 := s0+a2*b.k2c0
    let s1 := s1+a2*b.k2c1
    let a3 := read A (baseA+k+3)
    loop n baseA A B (t+1) (s0+a3*b.k3c0) (s1+a3*b.k3c1)
  else if h0 : k < n then
    have ht : t < (n+3)/4 := by dsimp [k] at h0; omega
    let b := B.get ⟨t,ht⟩
    let a0 := read A (baseA+k)
    let s0 := s0+a0*b.k0c0
    let s1 := s1+a0*b.k0c1
    if k+1 < n then
      let a1 := read A (baseA+k+1)
      let s0 := s0+a1*b.k1c0
      let s1 := s1+a1*b.k1c1
      if k+2 < n then
        let a2 := read A (baseA+k+2)
        ⟨s0+a2*b.k2c0,s1+a2*b.k2c1⟩
      else ⟨s0,s1⟩
    else ⟨s0,s1⟩
  else ⟨s0,s1⟩
termination_by n-4*t
decreasing_by all_goals omega

theorem loop_eq (n baseA baseB p : Nat) (A B : Array Binary32)
    (t : Nat) (s0 s1 : Float32) :
    loop n baseA A (pack n baseB p B) t s0 s1 =
      R15ThinPairs.loop n baseA baseB p A (B.map ExecFloat.Binary.toFloat32)
        (4*t) s0 s1 := by
  by_cases h3 : 4*t+3 < n
  · have h0 : 4*t < n := by omega
    have h1 : 4*t+1 < n := by omega
    have h2 : 4*t+2 < n := by omega
    rw [loop]
    simp only [h3, dite_true]
    rw [loop_eq]
    conv_rhs =>
      rw [R15ThinPairs.loop, dif_pos h0]
      rw [R15ThinPairs.loop, dif_pos h1]
      simp only [Nat.add_assoc, Nat.reduceAdd]
      rw [R15ThinPairs.loop, dif_pos h2]
      simp only [Nat.add_assoc, Nat.reduceAdd]
      rw [R15ThinPairs.loop, dif_pos h3]
    simp only [pack_get, packet, h0, h1, h2, h3, ite_true, read,
      Packed10.nativeA_getD, Nat.mul_add, Nat.mul_one, Nat.add_assoc, Nat.reduceAdd]
  · by_cases h0 : 4*t < n
    · by_cases h1 : 4*t+1 < n
      · by_cases h2 : 4*t+2 < n
        · rw [loop]
          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true]
          conv_rhs =>
            rw [R15ThinPairs.loop, dif_pos h0]
            rw [R15ThinPairs.loop, dif_pos h1]
            simp only [Nat.add_assoc, Nat.reduceAdd]
            rw [R15ThinPairs.loop, dif_pos h2]
            simp only [Nat.add_assoc, Nat.reduceAdd]
            rw [R15ThinPairs.loop, dif_neg h3]
          simp only [pack_get, packet, h0, h1, h2, ite_true, read,
            Packed10.nativeA_getD, Nat.add_assoc, Nat.reduceAdd]
        · rw [loop]
          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true, ite_false]
          conv_rhs =>
            rw [R15ThinPairs.loop, dif_pos h0]
            rw [R15ThinPairs.loop, dif_pos h1]
            simp only [Nat.add_assoc, Nat.reduceAdd]
            rw [R15ThinPairs.loop, dif_neg h2]
          simp only [pack_get, packet, h0, h1, ite_true, read,
            Packed10.nativeA_getD, Nat.add_assoc, Nat.reduceAdd]
      · rw [loop]
        simp only [h3, h0, h1, dite_false, dite_true, ite_false]
        conv_rhs =>
          rw [R15ThinPairs.loop, dif_pos h0]
          rw [R15ThinPairs.loop, dif_neg h1]
        simp only [pack_get, packet, h0, ite_true, read, Packed10.nativeA_getD]
    · rw [loop, R15ThinPairs.loop]
      simp only [h3, h0, dite_false]
termination_by n-4*t
decreasing_by all_goals omega

def packB (batch n p : Nat) (B : Vector Binary32 (batch*n*p)) :
    Vector (Vector B8 ((n+3)/4)) (batch*R15ThinPairs.groups p) :=
  Vector.ofFn fun t =>
    let b := t.val / R15ThinPairs.groups p
    let g := t.val % R15ThinPairs.groups p
    pack n (b*n*p+2*g) p B.toArray

theorem packB_get (batch n p : Nat) (B : Vector Binary32 (batch*n*p))
    (b : Fin batch) (g : Fin (R15ThinPairs.groups p)) :
    (packB batch n p B).get (R15PackedB2.tileIndex batch p b g) =
      pack n (b.val*n*p+2*g.val) p B.toArray := by
  have hG : 0 < R15ThinPairs.groups p := Nat.zero_lt_of_lt g.isLt
  have hd : (b.val*R15ThinPairs.groups p+g.val)/R15ThinPairs.groups p = b.val := by
    rw [Nat.mul_comm b.val (R15ThinPairs.groups p), Nat.mul_add_div hG,
      Nat.div_eq_of_lt g.isLt, Nat.add_zero]
  have hm : (b.val*R15ThinPairs.groups p+g.val)%R15ThinPairs.groups p = g.val :=
    Nat.mul_add_mod_of_lt g.isLt
  simp only [packB, R15PackedB2.tileIndex, Packed10.vector_get_ofFn, hd, hm]

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : Vector (Vector B8 ((n+3)/4)) (batch*R15ThinPairs.groups p))
    (r : Fin (batch*m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    Array Binary32 :=
  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt
  let b : Fin batch := ⟨r.val/m,(Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let baseA := r.val*n
  let baseB := b.val*n*p+2*g.val
  let result := loop n baseA A.toArray
    (packedB.get (R15PackedB2.tileIndex batch p b g)) 0 Packed10.zero32 Packed10.zero32
  RowStream.emit (min 2 (p-2*g.val)) (fun l =>
    Packed10.finish n baseA (baseB+l.val) p A.toArray B.toArray
      (R15ThinPairs.select result l.val)) out

theorem group_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (r : Fin (batch*m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    group batch m n p A B (packB batch n p B) r out g =
      R15ThinPairs.group batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) r out g := by
  simp only [group, R15ThinPairs.group, packB_get, loop_eq, Nat.mul_zero]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : Vector (Vector B8 ((n+3)/4)) (batch*R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch*m)) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (group batch m n p A B packedB r) out

theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (out : Array Binary32) (r : Fin (batch*m)) :
    row batch m n p A B (packB batch n p B) out r =
      R15ThinPairs.row batch m n p A B (B.toArray.map ExecFloat.Binary.toFloat32) out r := by
  unfold row R15ThinPairs.row
  apply congrArg (fun step : Array Binary32 → Fin (R15ThinPairs.groups p) → Array Binary32 =>
    Fin.foldl (R15ThinPairs.groups p) step out)
  funext acc g
  exact group_eq batch m n p A B r acc g

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) : Array Binary32 :=
  let packedB := packB batch n p B
  Fin.foldl (batch*m) (row batch m n p A B packedB) (Array.mkEmpty (batch*m*p))

theorem output_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    output batch m n p A B = R15ThinPairs.output batch m n p A B := by
  unfold output R15ThinPairs.output
  apply congrArg (fun step : Array Binary32 → Fin (batch*m) → Array Binary32 =>
    Fin.foldl (batch*m) step (Array.mkEmpty (batch*m*p)))
  funext acc r
  exact row_eq batch m n p A B acc r

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p) (output batch m n p A B) := by
  rw [output_eq]
  exact R15ThinPairs.output_prefix batch m n p A B

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    Vector Binary32 (batch*m*p) :=
  ⟨output batch m n p A B,(output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch*m*p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

def dispatch (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    Vector Binary32 (batch*m*p) :=
  if 2≤p ∧ p≤8 ∧ 1<n ∧ 4≤m then core batch m n p A B
  else bmmBeforeUnderflowZero batch m n p A B

theorem dispatch_spec (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    (dispatch batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  unfold dispatch
  split
  · rw [core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact bmmBeforeUnderflowZero_spec batch m n p A B
end Submission.R19Temporal

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else R19Temporal.dispatch batch m n p A B

theorem bmm_spec : ∀ (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)),
    (bmm batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  intro batch m n p A B
  unfold bmm
  split
  · rename_i h
    have hh : A.toArray.all UnderflowZero.small = true ∧
        B.toArray.all UnderflowZero.small = true := by
      simpa only [Bool.and_eq_true] using h
    rw [UnderflowZero.zeros_eq_reference batch m n p A B hh.1 hh.2]
    exact referenceBmm_spec batch m n p A B
  · exact R19Temporal.dispatch_spec batch m n p A B
end Submission
