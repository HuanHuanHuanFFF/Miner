/- R20 diagnostic only. Raw A is decoded once per k across eight native scalar chains. NOT_RUN. -/
namespace Submission.R20RowBroadcast
open FloatLib.Floats Competition
structure F8 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32
  s4 : Float32
  s5 : Float32
  s6 : Float32
  s7 : Float32

@[inline] def join (x0 x1 x2 x3 : R15ThinPairs.F2) : F8 :=
  ⟨x0.s0, x0.s1, x1.s0, x1.s1, x2.s0, x2.s1, x3.s0, x3.s1⟩

def loop (n baseA : Nat) (A : Array Binary32)
    (B0 B1 B2 B3 : Vector R19Temporal.B8 ((n+3)/4))
    (t : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 : Float32) : F8 :=
  let k := 4*t
  if h3 : k+3<n then
    have ht : t<(n+3)/4 := by dsimp [k] at h3; omega
    let b0 := B0.get ⟨t,ht⟩
    let b1 := B1.get ⟨t,ht⟩
    let b2 := B2.get ⟨t,ht⟩
    let b3 := B3.get ⟨t,ht⟩
    let a0 := R19Temporal.read A (baseA+k)
    let s0 := s0+a0*b0.k0c0
    let s1 := s1+a0*b0.k0c1
    let s2 := s2+a0*b1.k0c0
    let s3 := s3+a0*b1.k0c1
    let s4 := s4+a0*b2.k0c0
    let s5 := s5+a0*b2.k0c1
    let s6 := s6+a0*b3.k0c0
    let s7 := s7+a0*b3.k0c1
    let a1 := R19Temporal.read A (baseA+k+1)
    let s0 := s0+a1*b0.k1c0
    let s1 := s1+a1*b0.k1c1
    let s2 := s2+a1*b1.k1c0
    let s3 := s3+a1*b1.k1c1
    let s4 := s4+a1*b2.k1c0
    let s5 := s5+a1*b2.k1c1
    let s6 := s6+a1*b3.k1c0
    let s7 := s7+a1*b3.k1c1
    let a2 := R19Temporal.read A (baseA+k+2)
    let s0 := s0+a2*b0.k2c0
    let s1 := s1+a2*b0.k2c1
    let s2 := s2+a2*b1.k2c0
    let s3 := s3+a2*b1.k2c1
    let s4 := s4+a2*b2.k2c0
    let s5 := s5+a2*b2.k2c1
    let s6 := s6+a2*b3.k2c0
    let s7 := s7+a2*b3.k2c1
    let a3 := R19Temporal.read A (baseA+k+3)
    let s0 := s0+a3*b0.k3c0
    let s1 := s1+a3*b0.k3c1
    let s2 := s2+a3*b1.k3c0
    let s3 := s3+a3*b1.k3c1
    let s4 := s4+a3*b2.k3c0
    let s5 := s5+a3*b2.k3c1
    let s6 := s6+a3*b3.k3c0
    let s7 := s7+a3*b3.k3c1
    loop n baseA A B0 B1 B2 B3 (t+1) s0 s1 s2 s3 s4 s5 s6 s7
  else if h0 : k<n then
    have ht : t<(n+3)/4 := by dsimp [k] at h0; omega
    let b0 := B0.get ⟨t,ht⟩
    let b1 := B1.get ⟨t,ht⟩
    let b2 := B2.get ⟨t,ht⟩
    let b3 := B3.get ⟨t,ht⟩
    let a0 := R19Temporal.read A (baseA+k)
    let s0 := s0+a0*b0.k0c0
    let s1 := s1+a0*b0.k0c1
    let s2 := s2+a0*b1.k0c0
    let s3 := s3+a0*b1.k0c1
    let s4 := s4+a0*b2.k0c0
    let s5 := s5+a0*b2.k0c1
    let s6 := s6+a0*b3.k0c0
    let s7 := s7+a0*b3.k0c1
    if k+1<n then
      let a1 := R19Temporal.read A (baseA+k+1)
      let s0 := s0+a1*b0.k1c0
      let s1 := s1+a1*b0.k1c1
      let s2 := s2+a1*b1.k1c0
      let s3 := s3+a1*b1.k1c1
      let s4 := s4+a1*b2.k1c0
      let s5 := s5+a1*b2.k1c1
      let s6 := s6+a1*b3.k1c0
      let s7 := s7+a1*b3.k1c1
      if k+2<n then
        let a2 := R19Temporal.read A (baseA+k+2)
        let s0 := s0+a2*b0.k2c0
        let s1 := s1+a2*b0.k2c1
        let s2 := s2+a2*b1.k2c0
        let s3 := s3+a2*b1.k2c1
        let s4 := s4+a2*b2.k2c0
        let s5 := s5+a2*b2.k2c1
        let s6 := s6+a2*b3.k2c0
        let s7 := s7+a2*b3.k2c1
        ⟨s0, s1, s2, s3, s4, s5, s6, s7⟩
      else ⟨s0, s1, s2, s3, s4, s5, s6, s7⟩
    else ⟨s0, s1, s2, s3, s4, s5, s6, s7⟩
  else ⟨s0, s1, s2, s3, s4, s5, s6, s7⟩
termination_by n-4*t
decreasing_by all_goals omega

theorem loop_eq (n baseA : Nat) (A : Array Binary32)
    (B0 B1 B2 B3 : Vector R19Temporal.B8 ((n+3)/4))
    (t : Nat) (s0 s1 s2 s3 s4 s5 s6 s7 : Float32) :
    loop n baseA A B0 B1 B2 B3 t s0 s1 s2 s3 s4 s5 s6 s7 =
      join (R19Temporal.loop n baseA A B0 t s0 s1) (R19Temporal.loop n baseA A B1 t s2 s3) (R19Temporal.loop n baseA A B2 t s4 s5) (R19Temporal.loop n baseA A B3 t s6 s7) := by
  have eN := @loop.eq_def n baseA A B0 B1 B2 B3 t s0 s1 s2 s3 s4 s5 s6 s7
  have e0 := @R19Temporal.loop.eq_def n baseA A B0 t s0 s1
  have e1 := @R19Temporal.loop.eq_def n baseA A B1 t s2 s3
  have e2 := @R19Temporal.loop.eq_def n baseA A B2 t s4 s5
  have e3 := @R19Temporal.loop.eq_def n baseA A B3 t s6 s7
  by_cases h3 : 4*t+3<n
  · rw [eN, e0, e1, e2, e3]
    simp only [h3, dite_true]
    exact loop_eq n baseA A B0 B1 B2 B3 (t+1) _ _ _ _ _ _ _ _
  · by_cases h0 : 4*t<n
    · by_cases h1 : 4*t+1<n
      · by_cases h2 : 4*t+2<n
        · rw [eN, e0, e1, e2, e3]
          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true, join] <;> rfl
        · rw [eN, e0, e1, e2, e3]
          simp only [h3, h0, h1, h2, dite_false, dite_true, ite_true, ite_false, join] <;> rfl
      · rw [eN, e0, e1, e2, e3]
        simp only [h3, h0, h1, dite_false, dite_true, ite_false, join] <;> rfl
    · rw [eN, e0, e1, e2, e3]
      simp only [h3, h0, dite_false, join] <;> rfl
termination_by n-4*t
decreasing_by all_goals omega

@[inline] def runDot (n baseA : Nat) (A : Array Binary32)
    (B0 B1 B2 B3 : Vector R19Temporal.B8 ((n+3)/4)) : F8 :=
  loop n baseA A B0 B1 B2 B3 0 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32

theorem runDot_eq (n baseA : Nat) (A : Array Binary32)
    (B0 B1 B2 B3 : Vector R19Temporal.B8 ((n+3)/4)) :
    runDot n baseA A B0 B1 B2 B3 =
      join (R19Temporal.loop n baseA A B0 0 Packed10.zero32 Packed10.zero32) (R19Temporal.loop n baseA A B1 0 Packed10.zero32 Packed10.zero32) (R19Temporal.loop n baseA A B2 0 Packed10.zero32 Packed10.zero32) (R19Temporal.loop n baseA A B3 0 Packed10.zero32 Packed10.zero32) := by
  exact loop_eq n baseA A B0 B1 B2 B3 0 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32

@[inline] def select (x : F8) (j : Nat) : Float32 :=
  if j=0 then x.s0 else if j=1 then x.s1 else if j=2 then x.s2 else if j=3 then x.s3 else if j=4 then x.s4 else if j=5 then x.s5 else if j=6 then x.s6 else x.s7

@[inline] def row8 (batch m n : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*8))
    (PB : Vector (Vector R19Temporal.B8 ((n+3)/4)) (batch*R15ThinPairs.groups 8))
    (out : Array Binary32) (r : Fin (batch*m)) : Array Binary32 :=
  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt
  let bi : Fin batch := ⟨r.val/m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let baseA := r.val*n
  let baseB := bi.val*n*8
  let B0 := PB.get (R15PackedB2.tileIndex batch 8 bi ⟨0,by decide⟩)
  let B1 := PB.get (R15PackedB2.tileIndex batch 8 bi ⟨1,by decide⟩)
  let B2 := PB.get (R15PackedB2.tileIndex batch 8 bi ⟨2,by decide⟩)
  let B3 := PB.get (R15PackedB2.tileIndex batch 8 bi ⟨3,by decide⟩)
  let result := runDot n baseA A.toArray B0 B1 B2 B3
  RowStream.emit 8 (fun j => Packed10.finish n baseA (baseB+j.val) 8
    A.toArray B.toArray (select result j.val)) out

def diagnosticBmm8 (batch m n : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*8)) : Array Binary32 :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    (UnderflowZero.zeros batch m 8).toArray
  else
    let PB := R19Temporal.packB batch n 8 B
    Fin.foldl (batch*m) (row8 batch m n A B PB) (Array.mkEmpty (batch*m*8))

end Submission.R20RowBroadcast
