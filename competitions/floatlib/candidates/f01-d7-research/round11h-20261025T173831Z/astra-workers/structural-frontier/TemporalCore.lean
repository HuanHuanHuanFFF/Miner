import ContractTensor

namespace R17Temporal
open FloatLib.Floats Competition

structure B2K4 where
  k0c0 : Float32
  k0c1 : Float32
  k1c0 : Float32
  k1c1 : Float32
  k2c0 : Float32
  k2c1 : Float32
  k3c0 : Float32
  k3c1 : Float32

structure Pair where
  c0 : Float32
  c1 : Float32

@[inline] def zero32 : Float32 := Float32.ofBits 0

@[inline] def read (xs : Array Binary32) (i : Nat) : Float32 :=
  ExecFloat.Binary.toFloat32 (xs.getD i posZero)

@[inline] def packet (n base p k : Nat) (B : Array Binary32) : B2K4 :=
  let b0 := if k < n then read B (base + k * p) else zero32
  let b1 := if k < n then read B (base + 1 + k * p) else zero32
  let b2 := if k + 1 < n then read B (base + (k + 1) * p) else zero32
  let b3 := if k + 1 < n then read B (base + 1 + (k + 1) * p) else zero32
  let b4 := if k + 2 < n then read B (base + (k + 2) * p) else zero32
  let b5 := if k + 2 < n then read B (base + 1 + (k + 2) * p) else zero32
  let b6 := if k + 3 < n then read B (base + (k + 3) * p) else zero32
  let b7 := if k + 3 < n then read B (base + 1 + (k + 3) * p) else zero32
  ⟨b0,b1,b2,b3,b4,b5,b6,b7⟩

def pack (n base p : Nat) (B : Array Binary32) : Vector B2K4 ((n + 3) / 4) :=
  Vector.ofFn fun t => packet n base p (4 * t.val) B

theorem pack_get (n base p : Nat) (B : Array Binary32) (t : Fin ((n + 3) / 4)) :
    (pack n base p B).get t = packet n base p (4 * t.val) B := by
  change (Vector.ofFn (fun t => packet n base p (4 * t.val) B))[t.val]'t.isLt = _
  exact Vector.getElem_ofFn t.isLt

@[inline] def step4 (b : B2K4) (a0 a1 a2 a3 s0 s1 : Float32) : Pair :=
  let s0 := s0 + a0 * b.k0c0
  let s1 := s1 + a0 * b.k0c1
  let s0 := s0 + a1 * b.k1c0
  let s1 := s1 + a1 * b.k1c1
  let s0 := s0 + a2 * b.k2c0
  let s1 := s1 + a2 * b.k2c1
  let s0 := s0 + a3 * b.k3c0
  let s1 := s1 + a3 * b.k3c1
  ⟨s0,s1⟩

theorem step4_c0 (b : B2K4) (a0 a1 a2 a3 s0 s1 : Float32) :
    (step4 b a0 a1 a2 a3 s0 s1).c0 =
      (((s0 + a0*b.k0c0) + a1*b.k1c0) + a2*b.k2c0) + a3*b.k3c0 := rfl

theorem step4_c1 (b : B2K4) (a0 a1 a2 a3 s0 s1 : Float32) :
    (step4 b a0 a1 a2 a3 s0 s1).c1 =
      (((s1 + a0*b.k0c1) + a1*b.k1c1) + a2*b.k2c1) + a3*b.k3c1 := rfl

def loop (n baseA : Nat) (A : Array Binary32)
    (B : Vector B2K4 ((n + 3) / 4)) (t : Nat) (s0 s1 : Float32) : Pair :=
  let k := 4 * t
  if hk3 : k + 3 < n then
    have ht : t < (n + 3) / 4 := by dsimp [k] at hk3; omega
    let b := B.get ⟨t,ht⟩
    let a0 := read A (baseA + k)
    let s0 := s0 + a0 * b.k0c0
    let s1 := s1 + a0 * b.k0c1
    let a1 := read A (baseA + k + 1)
    let s0 := s0 + a1 * b.k1c0
    let s1 := s1 + a1 * b.k1c1
    let a2 := read A (baseA + k + 2)
    let s0 := s0 + a2 * b.k2c0
    let s1 := s1 + a2 * b.k2c1
    let a3 := read A (baseA + k + 3)
    let s0 := s0 + a3 * b.k3c0
    let s1 := s1 + a3 * b.k3c1
    loop n baseA A B (t + 1) s0 s1
  else if hk : k < n then
    have ht : t < (n + 3) / 4 := by dsimp [k] at hk; omega
    let b := B.get ⟨t,ht⟩
    let a0 := read A (baseA + k)
    let s0 := s0 + a0 * b.k0c0
    let s1 := s1 + a0 * b.k0c1
    if k + 1 < n then
      let a1 := read A (baseA + k + 1)
      let s0 := s0 + a1 * b.k1c0
      let s1 := s1 + a1 * b.k1c1
      if k + 2 < n then
        let a2 := read A (baseA + k + 2)
        let s0 := s0 + a2 * b.k2c0
        let s1 := s1 + a2 * b.k2c1
        ⟨s0,s1⟩
      else ⟨s0,s1⟩
    else ⟨s0,s1⟩
  else ⟨s0,s1⟩
termination_by n - 4 * t
decreasing_by all_goals omega

def run (n baseA baseB p : Nat) (A B : Array Binary32) : Pair :=
  loop n baseA A (pack n baseB p B) 0 zero32 zero32

end R17Temporal
