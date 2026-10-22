import ContractTensor

/-
Original R2-W02 code-generation probe, not a submitted kernel.
No correctness bridge or benchmark claim is asserted here.
Compiled status in this environment: NOT_RUN (Lean/lake unavailable).
-/
namespace R2W02CodegenProbe

structure F4 where
  x0 : Float32
  x1 : Float32
  x2 : Float32
  x3 : Float32

private def zero32 : Float32 := Float32.ofBits 0
private def zero4 : F4 := ⟨zero32, zero32, zero32, zero32⟩

/-- Static B blocks are laid out as (batch, column-block, k).
    All four accumulators remain separate function arguments. -/
def packed4Loop (A : Array Float32) (B : Array F4) :
    Nat → Nat → Nat → Float32 → Float32 → Float32 → Float32 → F4
  | 0, _, _, s0, s1, s2, s3 => ⟨s0, s1, s2, s3⟩
  | fuel + 1, ai, bi, s0, s1, s2, s3 =>
      let a := A.getD ai zero32
      let b := B.getD bi zero4
      let t0 := a * b.x0
      let t1 := a * b.x1
      let t2 := a * b.x2
      let t3 := a * b.x3
      packed4Loop A B fuel (ai + 1) (bi + 1)
        (s0 + t0) (s1 + t1) (s2 + t2) (s3 + t3)

/-- Deliberately contrasting state-as-structure probe.
    The compiler may reuse the state object; allocation per step is NOT assumed. -/
def state4Loop (A : Array Float32) (B : Array F4) :
    Nat → Nat → Nat → F4 → F4
  | 0, _, _, s => s
  | fuel + 1, ai, bi, s =>
      let a := A.getD ai zero32
      let b := B.getD bi zero4
      state4Loop A B fuel (ai + 1) (bi + 1)
        ⟨s.x0 + a * b.x0, s.x1 + a * b.x1,
         s.x2 + a * b.x2, s.x3 + a * b.x3⟩

/-- Plain preconverted B control: row-major pointer array, four reads per step. -/
def plain4Loop (A B : Array Float32) (p : Nat) :
    Nat → Nat → Nat → Float32 → Float32 → Float32 → Float32 → F4
  | 0, _, _, s0, s1, s2, s3 => ⟨s0, s1, s2, s3⟩
  | fuel + 1, ai, bi, s0, s1, s2, s3 =>
      let a := A.getD ai zero32
      let b0 := B.getD bi zero32
      let b1 := B.getD (bi + 1) zero32
      let b2 := B.getD (bi + 2) zero32
      let b3 := B.getD (bi + 3) zero32
      plain4Loop A B p fuel (ai + 1) (bi + p)
        (s0 + a * b0) (s1 + a * b1)
        (s2 + a * b2) (s3 + a * b3)

end R2W02CodegenProbe
