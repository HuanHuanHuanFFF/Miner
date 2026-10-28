
/- R24 diagnostic: both native inputs are prepared once per full callback.
   Array and checked contiguous FloatArray storage share the same two chains.
   Public endpoints below remain exact B2; new numerical BMM proof NOT_RUN. -/
namespace Submission.R24BroadSize
open FloatLib.Floats Competition
theorem emit_size (p : Nat) (read : Fin p → Binary32) (out : Array Binary32) :
    (RowStream.emit p read out).size = out.size + p := by
  unfold RowStream.emit
  exact RowStream.foldl_inv (β := Array Binary32) p
    (fun (acc : Array Binary32) (j : Fin p) => acc.push (read j))
    (fun k (acc : Array Binary32) => acc.size = out.size + k)
    (by intro j acc h; simp only [Array.size_push, h]; omega) out (by omega)
end Submission.R24BroadSize

namespace Submission.R24BroadChecked
open FloatLib.Floats Competition
@[inline] def check (f : Float32) (d : Float) : Bool :=
  (ExecFloat.Binary.ofFloat32 d.toFloat32).raw.1 ==
    (ExecFloat.Binary.ofFloat32 f).raw.1

theorem checked_native (f : Float32) (d : Float) (h : check f d = true) :
    d.toFloat32 = f := by
  have hi : ExecFloat.Binary.ofFloat32 d.toFloat32 = ExecFloat.Binary.ofFloat32 f := by
    apply ExecFloat.ext
    apply Subtype.ext
    simpa only [check, beq_iff_eq] using h
  have he := congrArg ExecFloat.Binary.toFloat32 hi
  simpa only [ExecFloat.Binary.toFloat32_ofFloat32] using he

def prepareLoop (raw : Array Binary32) (k : Nat) (out : FloatArray) : Option FloatArray :=
  if hk : k < raw.size then
    let f := ExecFloat.Binary.toFloat32 raw[k]
    let d := f.toFloat
    if check f d then prepareLoop raw (k + 1) (out.push d) else none
  else some out
termination_by raw.size - k

def prepare (raw : Array Binary32) : Option FloatArray :=
  prepareLoop raw 0 (FloatArray.emptyWithCapacity raw.size)

@[inline] def read (xs : FloatArray) (i : Nat) : Float32 :=
  if hi : i < xs.size then (xs.get i hi).toFloat32 else Packed10.zero32
end Submission.R24BroadChecked

namespace Submission.R24BroadArray
open FloatLib.Floats Competition

def loop (n baseA baseB p : Nat) (A B : Array Float32)
    (k : Nat) (s0 s1 : Float32) : R15ThinPairs.F2 :=
  if hk : k < n then
    let a := A.getD (baseA + k) Packed10.zero32
    let b0 := B.getD (baseB + k * p) Packed10.zero32
    let b1 := B.getD (baseB + 1 + k * p) Packed10.zero32
    loop n baseA baseB p A B (k + 1) (s0 + a * b0) (s1 + a * b1)
  else ⟨s0, s1⟩
termination_by n - k

def singleLoop (n baseA baseB p : Nat) (A B : Array Float32)
    (k : Nat) (s : Float32) : Float32 :=
  if hk : k < n then
    let a := A.getD (baseA + k) Packed10.zero32
    let b0 := B.getD (baseB + k * p) Packed10.zero32
    singleLoop n baseA baseB p A B (k + 1) (s + a * b0)
  else s
termination_by n - k

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : Array Float32) (r : Fin (batch * m))
    (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p + 2 * g.val
  let count := min 2 (p - 2 * g.val)
  if count = 1 then
    let result := singleLoop n baseA baseB p nativeA nativeB 0 Packed10.zero32
    RowStream.emit count (fun _ => Packed10.finish n baseA baseB p A.toArray B.toArray result) out
  else
    let result := loop n baseA baseB p nativeA nativeB 0 Packed10.zero32 Packed10.zero32
    RowStream.emit count (fun l => Packed10.finish n baseA (baseB + l.val) p A.toArray B.toArray
      (R15ThinPairs.select result l.val)) out

theorem group_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : Array Float32) (r : Fin (batch * m))
    (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    (group batch m n p A B nativeA nativeB r out g).size = out.size + min 2 (p - 2 * g.val) := by
  dsimp only [group]
  split <;> exact R24BroadSize.emit_size _ _ _

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : Array Float32) (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (group batch m n p A B nativeA nativeB r) out

theorem row_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : Array Float32) (out : Array Binary32) (r : Fin (batch * m)) :
    (row batch m n p A B nativeA nativeB out r).size = out.size + p := by
  have hlast : min (2 * R15ThinPairs.groups p) p = p := by unfold R15ThinPairs.groups; omega
  unfold row
  have h := RowStream.foldl_inv (R15ThinPairs.groups p)
    (group batch m n p A B nativeA nativeB r)
    (fun k (acc : Array Binary32) => acc.size = out.size + min (2 * k) p)
    (by intro g acc h; rw [group_size, h]; omega) out (by simp)
  simpa only [hlast] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : Array Float32) : Array Binary32 :=
  Fin.foldl (batch * m) (row batch m n p A B nativeA nativeB)
    (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : Array Float32) : (output batch m n p A B nativeA nativeB).size = batch * m * p := by
  unfold output
  exact RowStream.foldl_inv (batch * m) (row batch m n p A B nativeA nativeB)
    (fun k (acc : Array Binary32) => acc.size = k * p)
    (by intro r acc h; rw [row_size, h, Nat.add_mul]; simp)
    (Array.mkEmpty (batch * m * p)) (by simp)

def guarded (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if 1 < n then
    let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
    let nativeB := B.toArray.map ExecFloat.Binary.toFloat32
    ⟨output batch m n p A B nativeA nativeB, output_size batch m n p A B nativeA nativeB⟩
  else Submission.bmm batch m n p A B

end Submission.R24BroadArray

namespace Submission.R24BroadFlat
open FloatLib.Floats Competition

def loop (n baseA baseB p : Nat) (A B : FloatArray)
    (k : Nat) (s0 s1 : Float32) : R15ThinPairs.F2 :=
  if hk : k < n then
    let a := R24BroadChecked.read A (baseA + k)
    let b0 := R24BroadChecked.read B (baseB + k * p)
    let b1 := R24BroadChecked.read B (baseB + 1 + k * p)
    loop n baseA baseB p A B (k + 1) (s0 + a * b0) (s1 + a * b1)
  else ⟨s0, s1⟩
termination_by n - k

def singleLoop (n baseA baseB p : Nat) (A B : FloatArray)
    (k : Nat) (s : Float32) : Float32 :=
  if hk : k < n then
    let a := R24BroadChecked.read A (baseA + k)
    let b0 := R24BroadChecked.read B (baseB + k * p)
    singleLoop n baseA baseB p A B (k + 1) (s + a * b0)
  else s
termination_by n - k

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : FloatArray) (r : Fin (batch * m))
    (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) : Array Binary32 :=
  let baseA := r.val * n
  let baseB := r.val / m * n * p + 2 * g.val
  let count := min 2 (p - 2 * g.val)
  if count = 1 then
    let result := singleLoop n baseA baseB p nativeA nativeB 0 Packed10.zero32
    RowStream.emit count (fun _ => Packed10.finish n baseA baseB p A.toArray B.toArray result) out
  else
    let result := loop n baseA baseB p nativeA nativeB 0 Packed10.zero32 Packed10.zero32
    RowStream.emit count (fun l => Packed10.finish n baseA (baseB + l.val) p A.toArray B.toArray
      (R15ThinPairs.select result l.val)) out

theorem group_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : FloatArray) (r : Fin (batch * m))
    (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    (group batch m n p A B nativeA nativeB r out g).size = out.size + min 2 (p - 2 * g.val) := by
  dsimp only [group]
  split <;> exact R24BroadSize.emit_size _ _ _

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : FloatArray) (out : Array Binary32) (r : Fin (batch * m)) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (group batch m n p A B nativeA nativeB r) out

theorem row_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : FloatArray) (out : Array Binary32) (r : Fin (batch * m)) :
    (row batch m n p A B nativeA nativeB out r).size = out.size + p := by
  have hlast : min (2 * R15ThinPairs.groups p) p = p := by unfold R15ThinPairs.groups; omega
  unfold row
  have h := RowStream.foldl_inv (R15ThinPairs.groups p)
    (group batch m n p A B nativeA nativeB r)
    (fun k (acc : Array Binary32) => acc.size = out.size + min (2 * k) p)
    (by intro g acc h; rw [group_size, h]; omega) out (by simp)
  simpa only [hlast] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : FloatArray) : Array Binary32 :=
  Fin.foldl (batch * m) (row batch m n p A B nativeA nativeB)
    (Array.mkEmpty (batch * m * p))

theorem output_size (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p))
    (nativeA nativeB : FloatArray) : (output batch m n p A B nativeA nativeB).size = batch * m * p := by
  unfold output
  exact RowStream.foldl_inv (batch * m) (row batch m n p A B nativeA nativeB)
    (fun k (acc : Array Binary32) => acc.size = k * p)
    (by intro r acc h; rw [row_size, h, Nat.add_mul]; simp)
    (Array.mkEmpty (batch * m * p)) (by simp)

def guarded (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n)) (B : Vector Binary32 (batch * n * p)) :
    Vector Binary32 (batch * m * p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else if 1 < n then
    match R24BroadChecked.prepare A.toArray with
    | none => Submission.bmm batch m n p A B
    | some nativeA =>
      match R24BroadChecked.prepare B.toArray with
      | none => Submission.bmm batch m n p A B
      | some nativeB =>
        ⟨output batch m n p A B nativeA nativeB, output_size batch m n p A B nativeA nativeB⟩
  else Submission.bmm batch m n p A B

end Submission.R24BroadFlat
