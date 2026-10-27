/- R19 dual temporal prototype. NOT_COMPILED.
   One flat A4 cache over rows/k; existing temporal B8 and two ordered chains.
   No cross-row result tiles, no per-row A array. New complete source needs gate. -/
namespace Submission.R19DualTemporal
open FloatLib.Floats Competition

structure A4 where
  a0 : Float32
  a1 : Float32
  a2 : Float32
  a3 : Float32

@[inline] def blocks (n : Nat) : Nat := (n+3)/4

@[inline] def packetA (n base t : Nat) (A : Array Binary32) : A4 :=
  let k := 4*t
  ⟨if k<n then R19Temporal.read A (base+k) else Packed10.zero32,
   if k+1<n then R19Temporal.read A (base+k+1) else Packed10.zero32,
   if k+2<n then R19Temporal.read A (base+k+2) else Packed10.zero32,
   if k+3<n then R19Temporal.read A (base+k+3) else Packed10.zero32⟩

def point (n : Nat) (A : Array Binary32) (q : Nat) : A4 :=
  packetA n ((q / blocks n)*n) (q % blocks n) A

theorem point_row (n : Nat) (A : Array Binary32) (r t : Nat) (ht : t<blocks n) :
    point n A (r*blocks n+t) = packetA n (r*n) t A := by
  have hT : 0<blocks n := Nat.zero_lt_of_lt ht
  have hd : (r*blocks n+t)/blocks n = r := by
    rw [Nat.mul_comm r (blocks n), Nat.mul_add_div hT, Nat.div_eq_of_lt ht, Nat.add_zero]
  have hm : (r*blocks n+t)%blocks n = t := Nat.mul_add_mod_of_lt ht
  simp only [point, hd, hm]

def APrefix (f : Nat → A4) (k : Nat) (out : Array A4) : Prop :=
  out.size=k ∧ ∀ j (hj : j<out.size), out[j]=f j

theorem prefix_push (f : Nat → A4) (k : Nat) (out : Array A4)
    (h : APrefix f k out) : APrefix f (k+1) (out.push (f k)) := by
  refine ⟨by simp only [Array.size_push, h.1], ?_⟩
  intro j hj
  have hj' : j<out.size+1 := by simpa only [Array.size_push] using hj
  by_cases hlt : j<out.size
  · rw [Array.getElem_push_lt hlt]
    exact h.2 j hlt
  · have he : j=out.size := by omega
    subst j
    rw [Array.getElem_push_eq, h.1]

@[inline] def packRow (n : Nat) (A : Array Binary32) (r : Nat) (out : Array A4) : Array A4 :=
  let base := r*n
  Fin.foldl (blocks n) (fun acc t => acc.push (packetA n base t.val A)) out

theorem packRow_prefix (n : Nat) (A : Array Binary32) (r : Nat) (out : Array A4)
    (hout : APrefix (point n A) (r*blocks n) out) :
    APrefix (point n A) ((r+1)*blocks n) (packRow n A r out) := by
  have h := RowStream.foldl_inv (blocks n)
    (fun acc t => acc.push (packetA n (r*n) t.val A))
    (fun t acc => APrefix (point n A) (r*blocks n+t) acc)
    (by
      intro t acc hacc
      rw [← point_row n A r t.val t.isLt]
      simpa only [Nat.add_assoc] using prefix_push (point n A) (r*blocks n+t.val) acc hacc)
    out (by simpa only [Nat.add_zero] using hout)
  simpa only [packRow, Nat.add_mul, Nat.one_mul] using h

def packOutput (rows n : Nat) (A : Array Binary32) : Array A4 :=
  Fin.foldl rows (fun acc r => packRow n A r.val acc) (Array.mkEmpty (rows*blocks n))

theorem packOutput_prefix (rows n : Nat) (A : Array Binary32) :
    APrefix (point n A) (rows*blocks n) (packOutput rows n A) := by
  exact RowStream.foldl_inv rows (fun acc r => packRow n A r.val acc)
    (fun r acc => APrefix (point n A) (r*blocks n) acc)
    (fun r acc hacc => packRow_prefix n A r.val acc hacc)
    (Array.mkEmpty (rows*blocks n))
    ⟨by simp, by intro j hj; simp at hj⟩

def packA (rows n : Nat) (A : Array Binary32) : Vector A4 (rows*blocks n) :=
  ⟨packOutput rows n A, (packOutput_prefix rows n A).1⟩

def index (rows n : Nat) (r : Fin rows) (t : Fin (blocks n)) : Fin (rows*blocks n) :=
  ⟨r.val*blocks n+t.val, by
    have h := Nat.mul_le_mul_right (blocks n) r.isLt
    rw [Nat.succ_mul] at h
    have ht := t.isLt
    omega⟩

theorem packA_get (rows n : Nat) (A : Array Binary32) (r : Fin rows) (t : Fin (blocks n)) :
    (packA rows n A).get (index rows n r t) = packetA n (r.val*n) t.val A := by
  have hp := packOutput_prefix rows n A
  have hi : r.val*blocks n+t.val < (packOutput rows n A).size := by
    rw [hp.1]
    exact (index rows n r t).isLt
  change (packOutput rows n A)[r.val*blocks n+t.val]'hi = _
  exact (hp.2 _ hi).trans (point_row n A r.val t.val t.isLt)

theorem row_bound (rows n : Nat) (A : Vector A4 (rows*blocks n)) (r : Fin rows) :
    r.val*blocks n+blocks n ≤ A.toArray.size := by
  rw [A.size_toArray]
  have h := Nat.mul_le_mul_right (blocks n) r.isLt
  rw [Nat.succ_mul] at h
  exact h

def loop (n basePacket : Nat) (A : Array A4)
    (B : Vector R19Temporal.B8 (blocks n))
    (hA : basePacket+blocks n ≤ A.size)
    (t : Nat) (s0 s1 : Float32) : R15ThinPairs.F2 :=
  let k := 4*t
  if h3 : k+3<n then
    have ht : t<blocks n := by dsimp [k] at h3; unfold blocks; omega
    let a := A[basePacket+t]'(by omega)
    let b := B.get ⟨t,ht⟩
    let s0 := s0+a.a0*b.k0c0
    let s1 := s1+a.a0*b.k0c1
    let s0 := s0+a.a1*b.k1c0
    let s1 := s1+a.a1*b.k1c1
    let s0 := s0+a.a2*b.k2c0
    let s1 := s1+a.a2*b.k2c1
    loop n basePacket A B hA (t+1) (s0+a.a3*b.k3c0) (s1+a.a3*b.k3c1)
  else if h0 : k<n then
    have ht : t<blocks n := by dsimp [k] at h0; unfold blocks; omega
    let a := A[basePacket+t]'(by omega)
    let b := B.get ⟨t,ht⟩
    let s0 := s0+a.a0*b.k0c0
    let s1 := s1+a.a0*b.k0c1
    if k+1<n then
      let s0 := s0+a.a1*b.k1c0
      let s1 := s1+a.a1*b.k1c1
      if k+2<n then ⟨s0+a.a2*b.k2c0,s1+a.a2*b.k2c1⟩ else ⟨s0,s1⟩
    else ⟨s0,s1⟩
  else ⟨s0,s1⟩
termination_by n-4*t
decreasing_by all_goals omega

theorem loop_eq (n basePacket baseA : Nat) (Araw : Array Binary32) (A : Array A4)
    (B : Vector R19Temporal.B8 (blocks n))
    (hA : basePacket+blocks n ≤ A.size)
    (hread : ∀ i : Fin (blocks n),
      A[basePacket+i.val]'(by have := i.isLt; omega) = packetA n baseA i.val Araw)
    (t : Nat) (s0 s1 : Float32) :
    loop n basePacket A B hA t s0 s1 = R19Temporal.loop n baseA Araw B t s0 s1 := by
  by_cases h3 : 4*t+3<n
  · have h0 : 4*t<n := by omega
    have h1 : 4*t+1<n := by omega
    have h2 : 4*t+2<n := by omega
    have ht : t<blocks n := by unfold blocks; omega
    rw [loop, R19Temporal.loop]
    simp only [h3, dite_true]
    simp only [hread ⟨t,ht⟩]
    simp only [packetA, h0, h1, h2, h3, ite_true]
    exact loop_eq n basePacket baseA Araw A B hA hread (t+1) _ _
  · by_cases h0 : 4*t<n
    · have ht : t<blocks n := by unfold blocks; omega
      by_cases h1 : 4*t+1<n
      · by_cases h2 : 4*t+2<n
        · rw [loop, R19Temporal.loop]
          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true]
          simp only [hread ⟨t,ht⟩]
          simp only [packetA, h0, h1, h2, ite_true]
        · rw [loop, R19Temporal.loop]
          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true, ite_false]
          simp only [hread ⟨t,ht⟩]
          simp only [packetA, h0, h1, ite_true]
      · rw [loop, R19Temporal.loop]
        simp only [h3, h0, h1, dite_false, dite_true, ite_false]
        simp only [hread ⟨t,ht⟩]
        simp only [packetA, h0, ite_true]
    · rw [loop, R19Temporal.loop]
      simp only [h3, h0, dite_false]
termination_by n-4*t
decreasing_by all_goals omega

@[inline] def runDot (rows n : Nat) (r : Fin rows) (A : Vector A4 (rows*blocks n))
    (B : Vector R19Temporal.B8 (blocks n)) : R15ThinPairs.F2 :=
  loop n (r.val*blocks n) A.toArray B (row_bound rows n A r)
    0 Packed10.zero32 Packed10.zero32

theorem runDot_eq (rows n : Nat) (r : Fin rows) (Araw : Array Binary32)
    (B : Vector R19Temporal.B8 (blocks n)) :
    runDot rows n r (packA rows n Araw) B =
      R19Temporal.loop n (r.val*n) Araw B 0 Packed10.zero32 Packed10.zero32 := by
  apply loop_eq
  intro i
  exact packA_get rows n Araw r i

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedA : Vector A4 ((batch*m)*blocks n))
    (packedB : Vector (Vector R19Temporal.B8 (blocks n)) (batch*R15ThinPairs.groups p))
    (r : Fin (batch*m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    Array Binary32 :=
  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt
  let b : Fin batch := ⟨r.val/m,(Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let baseA := r.val*n
  let baseB := b.val*n*p+2*g.val
  let result := runDot (batch*m) n r packedA
    (packedB.get (R15PackedB2.tileIndex batch p b g))
  RowStream.emit (min 2 (p-2*g.val)) (fun l =>
    Packed10.finish n baseA (baseB+l.val) p A.toArray B.toArray
      (R15ThinPairs.select result l.val)) out

theorem group_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : Vector (Vector R19Temporal.B8 (blocks n)) (batch*R15ThinPairs.groups p))
    (r : Fin (batch*m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    group batch m n p A B (packA (batch*m) n A.toArray) packedB r out g =
      R19Temporal.group batch m n p A B packedB r out g := by
  simp only [group, R19Temporal.group, runDot_eq]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedA : Vector A4 ((batch*m)*blocks n))
    (packedB : Vector (Vector R19Temporal.B8 (blocks n)) (batch*R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch*m)) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (group batch m n p A B packedA packedB r) out

theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : Vector (Vector R19Temporal.B8 (blocks n)) (batch*R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch*m)) :
    row batch m n p A B (packA (batch*m) n A.toArray) packedB out r =
      R19Temporal.row batch m n p A B packedB out r := by
  unfold row R19Temporal.row
  apply congrArg (fun step : Array Binary32 → Fin (R15ThinPairs.groups p) → Array Binary32 =>
    Fin.foldl (R15ThinPairs.groups p) step out)
  funext acc g
  exact group_eq batch m n p A B packedB r acc g

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) : Array Binary32 :=
  let packedA := packA (batch*m) n A.toArray
  let packedB := R19Temporal.packB batch n p B
  Fin.foldl (batch*m) (row batch m n p A B packedA packedB) (Array.mkEmpty (batch*m*p))

theorem output_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    output batch m n p A B = R19Temporal.output batch m n p A B := by
  unfold output R19Temporal.output
  apply congrArg (fun step : Array Binary32 → Fin (batch*m) → Array Binary32 =>
    Fin.foldl (batch*m) step (Array.mkEmpty (batch*m*p)))
  funext acc r
  exact row_eq batch m n p A B (R19Temporal.packB batch n p B) acc r

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p) (output batch m n p A B) := by
  rw [output_eq]
  exact R19Temporal.output_prefix batch m n p A B

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
  if 3≤p ∧ p≤8 ∧ 1<n ∧ 4≤m then core batch m n p A B
  else R19Temporal.dispatch batch m n p A B

theorem dispatch_spec (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    (dispatch batch m n p A B).get = bmmSpec batch m n p A.get B.get := by
  unfold dispatch
  split
  · rw [core_eq_reference]
    exact referenceBmm_spec batch m n p A B
  · exact R19Temporal.dispatch_spec batch m n p A B
end Submission.R19DualTemporal

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else R19DualTemporal.dispatch batch m n p A B

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
  · exact R19DualTemporal.dispatch_spec batch m n p A B
end Submission
