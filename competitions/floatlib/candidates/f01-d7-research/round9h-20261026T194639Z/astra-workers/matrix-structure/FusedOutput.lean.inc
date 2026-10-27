/- R19 output fusion probe. NOT_COMPILED. Retains original B2 packing and MACs;
   consumes the output array at the numeric loop terminal, with explicit pushes. -/
namespace Submission.R19FusedOutput
open FloatLib.Floats Competition

@[inline] def emitPair (n baseA baseB p : Nat) (A B : Array Binary32)
    (second : Bool) (s0 s1 : Float32) (out : Array Binary32) : Array Binary32 :=
  let out := out.push (Packed10.finish n baseA baseB p A B s0)
  if second then out.push (Packed10.finish n baseA (baseB+1) p A B s1) else out

theorem emitPair_eq (n baseA baseB p j : Nat) (A B : Array Binary32)
    (s0 s1 : Float32) (out : Array Binary32) (hj : j<p) :
    emitPair n baseA baseB p A B (decide (j+1<p)) s0 s1 out =
      RowStream.emit (min 2 (p-j)) (fun l =>
        Packed10.finish n baseA (baseB+l.val) p A B
          (R15ThinPairs.select ⟨s0,s1⟩ l.val)) out := by
  by_cases h : j+1<p
  · have hc : min 2 (p-j) = 2 := by omega
    simp [emitPair, h, hc, RowStream.emit, Fin.foldl, Fin.foldl.loop, R15ThinPairs.select]
  · have hc : min 2 (p-j) = 1 := by omega
    simp [emitPair, h, hc, RowStream.emit, Fin.foldl, Fin.foldl.loop, R15ThinPairs.select]

def loopEmit (n baseA baseB p : Nat) (A Braw : Array Binary32)
    (packed : Vector R15PackedB2.B2 n) (second : Bool) (out : Array Binary32)
    (k : Nat) (s0 s1 : Float32) : Array Binary32 :=
  if hk : k<n then
    let a := ExecFloat.Binary.toFloat32 (A.getD (baseA+k) posZero)
    let b := packed.get ⟨k,hk⟩
    loopEmit n baseA baseB p A Braw packed second out (k+1)
      (s0+a*b.s0) (s1+a*b.s1)
  else emitPair n baseA baseB p A Braw second s0 s1 out
termination_by n-k

theorem loopEmit_eq (n baseA baseB p : Nat) (A Braw : Array Binary32)
    (packed : Vector R15PackedB2.B2 n) (second : Bool) (out : Array Binary32)
    (k : Nat) (s0 s1 : Float32) :
    loopEmit n baseA baseB p A Braw packed second out k s0 s1 =
      let result := R15PackedB2.loop n baseA A packed k s0 s1
      emitPair n baseA baseB p A Braw second result.s0 result.s1 out := by
  by_cases hk : k<n
  · rw [loopEmit, R15PackedB2.loop, dif_pos hk, dif_pos hk]
    exact loopEmit_eq n baseA baseB p A Braw packed second out (k+1) _ _
  · rw [loopEmit, R15PackedB2.loop, dif_neg hk, dif_neg hk]
termination_by n-k

@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : Vector (Vector R15PackedB2.B2 n) (batch*R15ThinPairs.groups p))
    (r : Fin (batch*m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    Array Binary32 :=
  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt
  let b : Fin batch := ⟨r.val/m,(Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let baseA := r.val*n
  let baseB := b.val*n*p+2*g.val
  loopEmit n baseA baseB p A.toArray B.toArray
    (packedB.get (R15PackedB2.tileIndex batch p b g))
    (decide (2*g.val+1<p)) out 0 Packed10.zero32 Packed10.zero32

theorem group_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : Vector (Vector R15PackedB2.B2 n) (batch*R15ThinPairs.groups p))
    (r : Fin (batch*m)) (out : Array Binary32) (g : Fin (R15ThinPairs.groups p)) :
    group batch m n p A B packedB r out g =
      R15PackedB2.group batch m n p A B packedB r out g := by
  have hg : 2*g.val<p := by
    have h := g.isLt
    unfold R15ThinPairs.groups at h
    omega
  simp only [group, R15PackedB2.group, loopEmit_eq]
  rw [emitPair_eq _ _ _ _ _ _ _ _ _ _ hg]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : Vector (Vector R15PackedB2.B2 n) (batch*R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch*m)) : Array Binary32 :=
  Fin.foldl (R15ThinPairs.groups p) (group batch m n p A B packedB r) out

theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p))
    (packedB : Vector (Vector R15PackedB2.B2 n) (batch*R15ThinPairs.groups p))
    (out : Array Binary32) (r : Fin (batch*m)) :
    row batch m n p A B packedB out r = R15PackedB2.row batch m n p A B packedB out r := by
  unfold row R15PackedB2.row
  apply congrArg (fun step : Array Binary32 → Fin (R15ThinPairs.groups p) → Array Binary32 =>
    Fin.foldl (R15ThinPairs.groups p) step out)
  funext acc g
  exact group_eq batch m n p A B packedB r acc g

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) : Array Binary32 :=
  let packedB := R15PackedB2.packB batch n p B
  Fin.foldl (batch*m) (row batch m n p A B packedB) (Array.mkEmpty (batch*m*p))

theorem output_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    output batch m n p A B = R15PackedB2.output batch m n p A B := by
  unfold output R15PackedB2.output
  apply congrArg (fun step : Array Binary32 → Fin (batch*m) → Array Binary32 =>
    Fin.foldl (batch*m) step (Array.mkEmpty (batch*m*p)))
  funext acc r
  exact row_eq batch m n p A B (R15PackedB2.packB batch n p B) acc r

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch*m*n)) (B : Vector Binary32 (batch*n*p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch*m*p) (output batch m n p A B) := by
  rw [output_eq]
  exact R15PackedB2.output_prefix batch m n p A B

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
end Submission.R19FusedOutput

namespace Submission
open FloatLib.Floats Competition

def bmm (batch m n p : Nat) (A : Vector Binary32 (batch*m*n))
    (B : Vector Binary32 (batch*n*p)) : Vector Binary32 (batch*m*p) :=
  if A.toArray.all UnderflowZero.small && B.toArray.all UnderflowZero.small then
    UnderflowZero.zeros batch m p
  else R19FusedOutput.dispatch batch m n p A B

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
  · exact R19FusedOutput.dispatch_spec batch m n p A B
end Submission
