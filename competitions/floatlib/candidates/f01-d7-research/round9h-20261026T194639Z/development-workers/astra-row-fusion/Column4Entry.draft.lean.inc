namespace Submission.R19Column4Temporal
open FloatLib.Floats Competition
open R19DualTemporal (A4 blocks)
@[inline] def groups (p : Nat) := (p+3)/4
abbrev AC (r n : Nat) := Vector A4 (r*blocks n)
abbrev BC (b n p : Nat) := Vector (Vector B16 (blocks n)) (b*groups p)
def ix (b p : Nat) (i : Fin b) (g : Fin (groups p)) : Fin (b*groups p) :=
  ⟨i.val*groups p+g.val, by
    have h := Nat.mul_le_mul_right (groups p) i.isLt
    rw [Nat.succ_mul] at h
    omega⟩
def packB (b n p : Nat) (B : Vector Binary32 (b*n*p)) : BC b n p :=
  Vector.ofFn fun q => pack n (q.val/groups p*n*p+4*(q.val%groups p)) p B.toArray
theorem packB_get (b n p : Nat) (B : Vector Binary32 (b*n*p))
    (i : Fin b) (g : Fin (groups p)) :
    (packB b n p B).get (ix b p i g) = pack n (i.val*n*p+4*g.val) p B.toArray := by
  have hg := g.isLt
  have hG : 0<groups p := Nat.zero_lt_of_lt hg
  have hd : (i.val*groups p+g.val)/groups p=i.val := by
    rw [Nat.mul_comm i.val (groups p), Nat.mul_add_div hG, Nat.div_eq_of_lt hg, Nat.add_zero]
  have hm : (i.val*groups p+g.val)%groups p=g.val := Nat.mul_add_mod_of_lt hg
  simp only [packB, ix, Packed10.vector_get_ofFn, hd, hm]
@[inline] def select (x : F4) (j : Nat) : Float32 :=
  if j=0 then x.s0 else if j=1 then x.s1 else if j=2 then x.s2 else x.s3
theorem finish_select (rows n : Nat) (r : Fin rows) (base p : Nat)
    (A B : Array Binary32) (j : Nat) (hj : j<4) :
    Packed10.finish n (r.val*n) (base+j) p A B
      (select (runDot rows n r (R19DualTemporal.packA rows n A) (pack n base p B)) j) =
    NativeFinal.dot n (r.val*n) (base+j) p A B := by
  rw [runDot_pack_eq]
  simp only [R19DualTemporal.runDot_eq, R19Temporal.loop_eq, Nat.mul_zero]
  have h : j=0 ∨ j=1 ∨ j=2 ∨ j=3 := by omega
  rcases h with h|h|h|h <;> subst j
  · simpa [select, join, R15ThinPairs.select] using
      R15ThinPairs.finish_select n (r.val*n) base p A B 0 (by omega)
  · simpa [select, join, R15ThinPairs.select] using
      R15ThinPairs.finish_select n (r.val*n) base p A B 1 (by omega)
  · simpa [select, join, R15ThinPairs.select] using
      R15ThinPairs.finish_select n (r.val*n) (base+2) p A B 0 (by omega)
  · simpa [select, join, R15ThinPairs.select, Nat.add_assoc] using
      R15ThinPairs.finish_select n (r.val*n) (base+2) p A B 1 (by omega)
variable {b m n p : Nat}
variable (A : Vector Binary32 (b*m*n)) (B : Vector Binary32 (b*n*p))
@[inline] def group (PA : AC (b*m) n) (PB : BC b n p)
    (r : Fin (b*m)) (out : Array Binary32) (g : Fin (groups p)) : Array Binary32 :=
  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt
  let bi : Fin b := ⟨r.val/m,(Nat.div_lt_iff_lt_mul hm).2 r.isLt⟩
  let v := runDot (b*m) n r PA (PB.get (ix b p bi g))
  RowStream.emit (min 4 (p-4*g.val)) (fun j =>
    Packed10.finish n (r.val*n) (bi.val*n*p+4*g.val+j.val) p A.toArray B.toArray
      (select v j.val)) out
theorem group_prefix (r : Fin (b*m)) (g : Fin (groups p)) (out : Array Binary32)
    (ho : RowStream.Prefix (RowStream.point b m n p A B) (r.val*p+min (4*g.val) p) out) :
    RowStream.Prefix (RowStream.point b m n p A B) (r.val*p+min (4*(g.val+1)) p)
      (group A B (R19DualTemporal.packA (b*m) n A.toArray) (packB b n p B) r out g) := by
  have hm : 0<m := Nat.pos_of_lt_mul_left r.isLt
  have hg : 4*g.val<p := by have h := g.isLt; unfold groups at h; omega
  have hp : 0<p := by omega
  have hs : min (4*g.val) p=4*g.val := by omega
  have he : r.val*p+min (4*(g.val+1)) p=(r.val*p+4*g.val)+min 4 (p-4*g.val) := by omega
  rw [he]
  unfold group
  dsimp only
  rw [packB_get]
  apply RowStream.emit_prefix
  · simpa only [hs] using ho
  · intro j
    have hj := j.isLt
    have hc : 4*g.val+j.val<p := by omega
    rw [show r.val*p+4*g.val+j.val=r.val*p+(4*g.val+j.val) by omega,
      RowStream.point_row b m n p A B r.val (4*g.val+j.val) hm hp hc]
    simpa only [Nat.add_assoc] using finish_select (b*m) n r (r.val/m*n*p+4*g.val) p
      A.toArray B.toArray j.val (Nat.lt_of_lt_of_le hj (Nat.min_le_left _ _))
@[inline] def row (PA : AC (b*m) n) (PB : BC b n p)
    (out : Array Binary32) (r : Fin (b*m)) : Array Binary32 :=
  Fin.foldl (groups p) (group A B PA PB r) out
theorem row_prefix (r : Fin (b*m)) (out : Array Binary32)
    (ho : RowStream.Prefix (RowStream.point b m n p A B) (r.val*p) out) :
    RowStream.Prefix (RowStream.point b m n p A B) ((r.val+1)*p)
      (row A B (R19DualTemporal.packA (b*m) n A.toArray) (packB b n p B) out r) := by
  have hl : min (4*groups p) p=p := by unfold groups; omega
  have h := RowStream.foldl_inv (groups p)
    (group A B (R19DualTemporal.packA (b*m) n A.toArray) (packB b n p B) r)
    (fun g acc => RowStream.Prefix (RowStream.point b m n p A B) (r.val*p+min (4*g) p) acc)
    (fun g acc ha => group_prefix A B r g acc ha) out
    (by simpa only [Nat.mul_zero, Nat.zero_min, Nat.add_zero] using ho)
  simpa only [row, hl, Nat.add_mul, Nat.one_mul] using h
def output : Array Binary32 :=
  let PA := R19DualTemporal.packA (b*m) n A.toArray
  let PB := packB b n p B
  Fin.foldl (b*m) (row A B PA PB) (Array.mkEmpty (b*m*p))
theorem output_prefix : RowStream.Prefix (RowStream.point b m n p A B) (b*m*p) (output A B) := by
  exact RowStream.foldl_inv (b*m)
    (row A B (R19DualTemporal.packA (b*m) n A.toArray) (packB b n p B))
    (fun r acc => RowStream.Prefix (RowStream.point b m n p A B) (r*p) acc)
    (fun r acc ha => row_prefix A B r acc ha) (Array.mkEmpty (b*m*p))
    ⟨by simp, by intro j hj; simp at hj⟩
def core : Vector Binary32 (b*m*p) := ⟨output A B,(output_prefix A B).1⟩
theorem core_eq_reference : core A B=referenceBmm b m n p A B := by
  exact (RowStream.prefix_vector_eq_ofFn (RowStream.point b m n p A B) (b*m*p)
    (output A B) (output_prefix A B)).trans (RowStream.points_eq_reference b m n p A B)
def dispatch : Vector Binary32 (b*m*p) :=
  if 3≤p ∧ p≤8 ∧ 1<n ∧ 4≤m ∧ 4*((p+3)/4)=2*((p+1)/2) then core A B
  else R19DualTemporal.dispatch b m n p A B
theorem dispatch_spec : (dispatch A B).get=bmmSpec b m n p A.get B.get := by
  unfold dispatch
  split
  · rw [core_eq_reference]; exact referenceBmm_spec b m n p A B
  · exact R19DualTemporal.dispatch_spec b m n p A B
end Submission.R19Column4Temporal
