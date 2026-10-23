/-
R11 DESIGN DRAFT ONLY. No Kernel package is generated from this file.
Intended insertion after the frozen proof3 RowStream declarations.
Requires all new proof3 bridges to pass the exact statement check first.
No new import, axiom, environment option, or floating-point implementation.
-/

namespace Submission.BatchLocalPacked

open FloatLib.Floats Competition

/-- Construct only b's groups and k-packets, never the whole batch Vector. -/
def packBatch (batch n p : Nat) (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) : Vector (Vector Packed10.F10 n) (Packed10.groups p) :=
  Vector.ofFn fun g =>
    Vector.ofFn fun k =>
      let base := (b.val * n + k.val) * p
      Packed10.packet (fun j =>
        if hj : j < p then
          have hbn : (b.val + 1) * n ≤ batch * n := Nat.mul_le_mul_right n b.isLt
          have hbk : b.val * n + k.val < batch * n := by
            rw [Nat.add_mul] at hbn
            omega
          have hp : (b.val * n + k.val + 1) * p ≤ batch * n * p :=
            Nat.mul_le_mul_right p (Nat.succ_le_of_lt hbk)
          have hi : base + j < B.toArray.size := by
            rw [B.size_toArray]
            dsimp [base]
            rw [Nat.add_mul] at hp
            omega
          ExecFloat.Binary.toFloat32 B.toArray[base + j]
        else Packed10.zero32) (10 * g.val)

/-- Full packB appears only in this erased proof, not the new preparation. -/
theorem packBatch_eq (batch n p : Nat)
    (B : Vector Binary32 (batch * n * p)) (b : Fin batch) :
    packBatch batch n p B b = (Packed10.packB batch n p B).get b := by
  simp only [packBatch, Packed10.packB, Packed10.vector_get_ofFn]

@[inline] def rowIndex (batch m : Nat) (b : Fin batch) (i : Fin m) :
    Fin (batch * m) :=
  ⟨b.val * m + i.val, by
    have h := Nat.mul_le_mul_right m b.isLt
    rw [Nat.add_mul] at h
    omega⟩

theorem rowIndex_batch (batch m : Nat) (b : Fin batch) (i : Fin m) :
    (rowIndex batch m b i).val / m = b.val := by
  have hm : 0 < m := Nat.zero_lt_of_lt i.isLt
  change (b.val * m + i.val) / m = b.val
  rw [Nat.mul_comm b.val m, Nat.mul_add_div hm, Nat.div_eq_of_lt i.isLt,
    Nat.add_zero]

/-- Consume a packet from this batch's local preparation and emit immediately. -/
@[inline] def group (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (b : Fin batch)
    (packed : Vector (Vector Packed10.F10 n) (Packed10.groups p))
    (r : Fin (batch * m)) (out : Array Binary32) (g : Fin (Packed10.groups p)) :
    Array Binary32 :=
  let result := Packed10Index.runDot n (r.val * n) nativeA (packed.get g)
  let count := min 10 (p - 10 * g.val)
  RowStream.emit count (fun l =>
    let j := 10 * g.val + l.val
    Packed10.finish n (r.val * n) (b.val * n * p + j) p A.toArray B.toArray
      (Packed10.lane result ⟨l.val, Nat.lt_of_lt_of_le l.isLt (Nat.min_le_left _ _)⟩)) out

/-- Transfer the already established group prefix through equal preparation. -/
theorem group_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (b : Fin batch) (r : Fin (batch * m)) (hb : r.val / m = b.val)
    (out : Array Binary32) (g : Fin (Packed10.groups p)) :
    group batch m n p A B nativeA b (packBatch batch n p B b) r out g =
      RowStream.group batch m n p A B nativeA (Packed10.packB batch n p B) r out g := by
  have hm : 0 < m := Nat.pos_of_lt_mul_left r.isLt
  have hbb : (⟨r.val / m, (Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩ : Fin batch) = b :=
    Fin.ext hb
  unfold group RowStream.group
  dsimp only
  rw [hbb, packBatch_eq]

@[inline] def row (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (b : Fin batch)
    (packed : Vector (Vector Packed10.F10 n) (Packed10.groups p))
    (out : Array Binary32) (i : Fin m) : Array Binary32 :=
  Fin.foldl (Packed10.groups p)
    (group batch m n p A B nativeA b packed (rowIndex batch m b i)) out

theorem row_eq (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (b : Fin batch) (out : Array Binary32) (i : Fin m) :
    row batch m n p A B nativeA b (packBatch batch n p B b) out i =
      RowStream.row batch m n p A B nativeA (Packed10.packB batch n p B)
        out (rowIndex batch m b i) := by
  unfold row RowStream.row
  apply congrArg (fun (step : Array Binary32 → Fin (Packed10.groups p) → Array Binary32) =>
    Fin.foldl (Packed10.groups p) step out)
  funext acc g
  exact group_eq batch m n p A B nativeA b (rowIndex batch m b i)
    (rowIndex_batch batch m b i) acc g

theorem row_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p))
    (b : Fin batch) (out : Array Binary32) (i : Fin m)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + i.val) * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val * m + i.val + 1) * p)
      (row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
        b (packBatch batch n p B b) out i) := by
  rw [row_eq]
  exact RowStream.row_prefix batch m n p A B (rowIndex batch m b i) out hout

/-- The local packedB is scoped to one batch step, not carried by the fold. -/
def batchStep (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (nativeA : Array Float32)
    (out : Array Binary32) (b : Fin batch) : Array Binary32 :=
  let packed := packBatch batch n p B b
  Fin.foldl m (row batch m n p A B nativeA b packed) out

theorem batch_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) (out : Array Binary32) (b : Fin batch)
    (hout : RowStream.Prefix (RowStream.point batch m n p A B) (b.val * m * p) out) :
    RowStream.Prefix (RowStream.point batch m n p A B) ((b.val + 1) * m * p)
      (batchStep batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32) out b) := by
  have h := RowStream.foldl_inv m
    (row batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32)
      b (packBatch batch n p B b))
    (fun i acc => RowStream.Prefix (RowStream.point batch m n p A B)
      ((b.val * m + i) * p) acc)
    (fun i acc hacc => by
      simpa only [Nat.add_assoc] using row_prefix batch m n p A B b acc i hacc)
    out (by simpa only [Nat.add_zero] using hout)
  simpa only [batchStep, Nat.add_mul, Nat.one_mul] using h

def output (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Array Binary32 :=
  let nativeA := A.toArray.map ExecFloat.Binary.toFloat32
  Fin.foldl batch (batchStep batch m n p A B nativeA)
    (Array.mkEmpty (batch * m * p))

theorem output_prefix (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    RowStream.Prefix (RowStream.point batch m n p A B) (batch * m * p)
      (output batch m n p A B) := by
  exact RowStream.foldl_inv batch
    (batchStep batch m n p A B (A.toArray.map ExecFloat.Binary.toFloat32))
    (fun b acc => RowStream.Prefix (RowStream.point batch m n p A B) (b * m * p) acc)
    (fun b acc hacc => batch_prefix batch m n p A B acc b hacc)
    (Array.mkEmpty (batch * m * p))
    ⟨by simp, by intro j hj; simp at hj⟩

def core (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) : Vector Binary32 (batch * m * p) :=
  ⟨output batch m n p A B, (output_prefix batch m n p A B).1⟩

theorem core_eq_reference (batch m n p : Nat)
    (A : Vector Binary32 (batch * m * n))
    (B : Vector Binary32 (batch * n * p)) :
    core batch m n p A B = referenceBmm batch m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point batch m n p A B)
    (batch * m * p) (output batch m n p A B) (output_prefix batch m n p A B)).trans
    (RowStream.points_eq_reference batch m n p A B)

end Submission.BatchLocalPacked
