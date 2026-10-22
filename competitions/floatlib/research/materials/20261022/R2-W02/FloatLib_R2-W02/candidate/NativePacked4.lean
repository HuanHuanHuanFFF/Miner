import ContractTensor

/-!
R2-W02, executable/code-generation candidate, NOT a gate-ready submission.

No elaboration, generated C, runtime benchmark or gate has been run here.
The finite-result-to-exact-dot theorem is an integration dependency supplied
by the other developer's work.  This file intentionally does not declare a
`bmm_correct` theorem or pretend that this integration is already proved.

Only public APIs of the pinned ContractTensor / FloatLib / Lean are used.
The code has no new trusted declarations and contains no admitted proofs.
-/

namespace R2W02

open Competition FloatLib.Floats

/-- Scalar fields are constructed at block boundaries, never at each MAC. -/
structure F4 where
  s0 : Float32
  s1 : Float32
  s2 : Float32
  s3 : Float32

def zero32 : Float32 := Float32.ofBits 0

def zero4 : F4 := ⟨zero32, zero32, zero32, zero32⟩

/-- Row-major B is converted and packed as [batch][column-block][k].
    Padding is by the column predicate; flat getD alone is insufficient. -/
def packB (batch n p : Nat) (B : Vector Binary32 (batch * n * p)) : Array F4 :=
  let blocks := (p + 3) / 4
  Array.ofFn fun (t : Fin (batch * blocks * n)) =>
    let b := t.val / (blocks * n)
    let r := t.val % (blocks * n)
    let g := r / n
    let k := r % n
    let col := g * 4
    let base := (b * n + k) * p
    let read := fun (j : Nat) =>
      if j < p then
        ExecFloat.Binary.toFloat32 (B.toArray.getD (base + j) posZero)
      else zero32
    ⟨read col, read (col + 1), read (col + 2), read (col + 3)⟩

/-- Four independent accumulators; each follows the original ascending k.
    The only F4 construction is in the zero-fuel return branch. -/
def dot4 (A : Array Float32) (B : Array F4) :
    (fuel aIndex bIndex : Nat) →
    (s0 s1 s2 s3 : Float32) → F4
  | 0, _, _, s0, s1, s2, s3 => ⟨s0, s1, s2, s3⟩
  | fuel + 1, aIndex, bIndex, s0, s1, s2, s3 =>
    let a := A.getD aIndex zero32
    let v := B.getD bIndex zero4
    let m0 := a * v.s0
    let m1 := a * v.s1
    let m2 := a * v.s2
    let m3 := a * v.s3
    let t0 := s0 + m0
    let t1 := s1 + m1
    let t2 := s2 + m2
    let t3 := s3 + m3
    dot4 A B fuel (aIndex + 1) (bIndex + 1) t0 t1 t2 t3

/-- Original software reference at a Nat output index.  It retains raw A/B.
    A valid output index specializes this definition to bmmSpec by rfl. -/
def exactAt (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (q : Nat) : Binary32 :=
  let (b, i, j) := bmmDecodeC m p q
  (List.finRange n).foldl
    (fun acc k =>
      ExecFloat.add acc
        (ExecFloat.mul
          (getD A.get (bmmAIndex m n b i k.val))
          (getD B.get (bmmBIndex n p b k.val j))))
    posZero

theorem exactAt_eq_spec (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (q : Fin (batch * m * p)) :
    exactAt batch m n p A B q.val = bmmSpec batch m n p A.get B.get q := by
  rfl

/-- Integration point: terminal finite acceptance, per output.
    Its safety is NOT asserted in this executable candidate file. -/
def finish (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (q : Nat) (x : Float32) : Binary32 :=
  if x.isFinite then ExecFloat.Binary.ofFloat32 x
  else exactAt batch m n p A B q

/-- Append a real lane; padded lanes cause neither output nor fallback. -/
def pushLane (batch m n p row col : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (x : Float32) (out : Array Binary32) : Array Binary32 :=
  if col < p then
    out.push (finish batch m n p A B (row * p + col) x)
  else out

def blocksGo (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (nativeA : Array Float32) (packedB : Array F4)
    (row : Nat) : (fuel block : Nat) → Array Binary32 → Array Binary32
  | 0, _, out => out
  | fuel + 1, block, out =>
    let blocks := (p + 3) / 4
    let b := row / m
    let s := dot4 nativeA packedB n (row * n)
      ((b * blocks + block) * n) zero32 zero32 zero32 zero32
    let col := block * 4
    let out := pushLane batch m n p row col A B s.s0 out
    let out := pushLane batch m n p row (col + 1) A B s.s1 out
    let out := pushLane batch m n p row (col + 2) A B s.s2 out
    let out := pushLane batch m n p row (col + 3) A B s.s3 out
    blocksGo batch m n p A B nativeA packedB row fuel (block + 1) out

def rowsGo (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (nativeA : Array Float32) (packedB : Array F4) :
    (fuel row : Nat) → Array Binary32 → Array Binary32
  | 0, _, out => out
  | fuel + 1, row, out =>
    let out := blocksGo batch m n p A B nativeA packedB row ((p + 3) / 4) 0 out
    rowsGo batch m n p A B nativeA packedB fuel (row + 1) out

/-- Complete candidate call: includes all conversions, packing, allocation,
    terminal checks, output conversion and exact per-lane fallback.
    It handles zero output dimensions and n=0 before touching A or B.
    Nat arithmetic is intentional: no truncating USize conversion.
    The shape check prevents an unproved Array-size equality from being hidden.
    Remove it only after proving the builder's size invariant. -/
def bmmDraft (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  if batch * m * p = 0 then Vector.replicate (batch * m * p) posZero
  else if n = 0 then Vector.replicate (batch * m * p) posZero
  else
    let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
    let packedB := packB batch n p B
    let out := rowsGo batch m n p A B nativeA packedB
      (batch * m) 0 (Array.emptyWithCapacity (batch * m * p))
    if h : out.size = batch * m * p then ⟨out, h⟩
    else Vector.ofFn (bmmSpec batch m n p A.get B.get)

end R2W02
