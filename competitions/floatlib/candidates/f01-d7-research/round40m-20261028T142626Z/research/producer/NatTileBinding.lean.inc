
/- NOT_RUN. Exact producer to Nat tile; no word-fit assumption. -/
namespace Submission.R23IndexedProducer
open FloatLib.Floats Competition

theorem nat_loop_lane (batch n p baseA : Nat) (A B : Array Binary32) (b : Fin batch)
    (g : Fin (R22Pair8.groups p)) (r : Fin 4) (c : Fin 2) (hc : 2 * g.val + c.val < p) :
    R15ThinPairs.select (R22Resident8Projection.projectRow
      (R22Resident8.loop n baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
        (R22Pair8.groups p) A (R22Pair8.packB batch n p B) 0
        (b.val * n * R22Pair8.groups p + g.val)
        Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
        Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32) r) c.val =
      NativeFinal.dotLoop n
        (R22Resident8Projection.rowBase baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n) r)
        (b.val * n * p + 2 * g.val + c.val) p A B 0 Packed10.zero32 := by
  have h := R22Resident8Projection.loop_lane n p
    baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
    (b.val * n * p + 2 * g.val) (b.val * n * R22Pair8.groups p + g.val)
    A B (R22Pair8.packB batch n p B) r c
    (fun k => cacheView_read batch n p B b g k c hc) 0
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
  simpa only [Nat.zero_mul, Nat.add_zero, zero_lane] using h

theorem nat_finish_lane (batch n p baseA : Nat) (A B : Array Binary32) (b : Fin batch)
    (g : Fin (R22Pair8.groups p)) (r : Fin 4) (c : Fin 2) (hc : 2 * g.val + c.val < p) :
    Packed10.finish n
      (R22Resident8Projection.rowBase baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n) r)
      (b.val * n * p + 2 * g.val + c.val) p A B
      (R15ThinPairs.select (R22Resident8Projection.projectRow
        (R22Resident8.loop n baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
          (R22Pair8.groups p) A (R22Pair8.packB batch n p B) 0
          (b.val * n * R22Pair8.groups p + g.val)
          Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
          Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32) r) c.val) =
      NativeFinal.dot n
        (R22Resident8Projection.rowBase baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n) r)
        (b.val * n * p + 2 * g.val + c.val) p A B := by
  exact Packed10.finish_eq_dot _ _ _ _ _ _ _ (nat_loop_lane batch n p baseA A B b g r c hc)

def wordAt (w : R22Resident8.Words) (r : Fin 4) (c : Fin 2) : UInt32 :=
  match r.val with
  | 0 => if c.val = 0 then w.w00 else w.w01
  | 1 => if c.val = 0 then w.w10 else w.w11
  | 2 => if c.val = 0 then w.w20 else w.w21
  | _ => if c.val = 0 then w.w30 else w.w31

theorem ofBits_raw (x : Binary32) : FastMul.ofBits x.raw.1 = x := by
  apply ExecFloat.ModelCodec.decode_injective
    (F := FastMul.Fam) (plan := FastMul.Plan)
    (Model := FloatLib.Floats.Formats.BinaryInterchange.Model FastMul.Fmt)
  change FastMul.dec (FastMul.ofBits x.raw.1) = FastMul.dec x
  rw [FastMul.dec_ofBits, FastMul.dec_eq]

theorem tile_word (batch n p baseA : Nat) (A B : Array Binary32) (b : Fin batch)
    (g : Fin (R22Pair8.groups p)) (r : Fin 4) (c : Fin 2) (hc : 2 * g.val + c.val < p) :
    FastMul.ofBits (wordAt
      (R22Resident8.tile p n baseA (b.val * n * p + 2 * g.val)
        (b.val * n * R22Pair8.groups p + g.val) A B (R22Pair8.packB batch n p B)
        (decide (2 * g.val + 1 < p))) r c) =
      NativeFinal.dot n
        (R22Resident8Projection.rowBase baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n) r)
        (b.val * n * p + 2 * g.val + c.val) p A B := by
  have hf := nat_finish_lane batch n p baseA A B b g r c hc
  cases hq : R22Resident8.loop n baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
      (R22Pair8.groups p) A (R22Pair8.packB batch n p B) 0
      (b.val * n * R22Pair8.groups p + g.val)
      Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
      Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 with
  | mk q00 q10 q20 q30 q01 q11 q21 q31 =>
    simp only [hq] at hf
    rcases r with ⟨r, hr⟩
    rcases c with ⟨c, hclt⟩
    have hrs : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
    have hcs : c = 0 ∨ c = 1 := by omega
    rcases hrs with rfl | rfl | rfl | rfl <;>
      rcases hcs with rfl | rfl <;>
      by_cases hs : 2 * g.val + 1 < p
    all_goals try omega
    all_goals
      simpa [R22Resident8.tile, hq, wordAt, R22Resident8Projection.projectRow,
        R22Resident8Projection.rowBase, R15ThinPairs.select, Nat.add_zero,
        hs, ofBits_raw] using hf

end Submission.R23IndexedProducer
