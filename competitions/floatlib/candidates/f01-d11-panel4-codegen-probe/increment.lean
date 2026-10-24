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
