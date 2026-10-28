/- Requires accepted Nat8Projection-v179574fb1. NOT_RUN.
   Structural word selection only; right-column evaluation remains guarded. -/
namespace Submission.R22Resident8Projection
open FloatLib.Floats Competition

def selectWords (w : R22Resident8.Words) (r : Fin 4) (c : Fin 2) : UInt32 :=
  match r.val with
  | 0 => if c.val = 0 then w.w00 else w.w01
  | 1 => if c.val = 0 then w.w10 else w.w11
  | 2 => if c.val = 0 then w.w20 else w.w21
  | _ => if c.val = 0 then w.w30 else w.w31

theorem tile_word (p n baseA baseB baseC : Nat) (A B : Array Binary32)
    (cache : Array BP) (second : Bool) (r : Fin 4) (c : Fin 2)
    (hright : c.val = 1 → second = true) :
    selectWords (R22Resident8.tile p n baseA baseB baseC A B cache second) r c =
      (Packed10.finish n (baseA + r.val * n) (baseB + c.val) p A B
        (R15ThinPairs.select
          (projectRow (R22Resident8.loop n baseA (baseA + n) (baseA + 2 * n)
            (baseA + 3 * n) (R22Pair8.groups p) A cache 0 baseC
            Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
            Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32) r) c.val)).raw.1 := by
  unfold R22Resident8.tile
  generalize R22Resident8.loop n baseA (baseA + n) (baseA + 2 * n) (baseA + 3 * n)
    (R22Pair8.groups p) A cache 0 baseC
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32
    Packed10.zero32 Packed10.zero32 Packed10.zero32 Packed10.zero32 = q
  rcases q with ⟨q00, q10, q20, q30, q01, q11, q21, q31⟩
  rcases r with ⟨r, hr⟩
  rcases c with ⟨c, hc⟩
  have hrs : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 := by omega
  have hcs : c = 0 ∨ c = 1 := by omega
  rcases hrs with rfl | rfl | rfl | rfl <;>
    rcases hcs with rfl | rfl <;>
    cases second <;>
    simp_all [selectWords, projectRow, R15ThinPairs.select]

end Submission.R22Resident8Projection
