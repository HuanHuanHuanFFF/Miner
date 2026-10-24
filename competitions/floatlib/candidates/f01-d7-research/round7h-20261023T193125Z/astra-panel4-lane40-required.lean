namespace Submission.R11WideRows4
open FloatLib.Floats Competition
@[inline] def lane40 (s : F40) (r : Fin 4) (l : Fin 10) : Float32 :=
  match r.val with
  | 0 => match l.val with
    | 0 => s.c0r0
    | 1 => s.c1r0
    | 2 => s.c2r0
    | 3 => s.c3r0
    | 4 => s.c4r0
    | 5 => s.c5r0
    | 6 => s.c6r0
    | 7 => s.c7r0
    | 8 => s.c8r0
    | _ => s.c9r0
  | 1 => match l.val with
    | 0 => s.c0r1
    | 1 => s.c1r1
    | 2 => s.c2r1
    | 3 => s.c3r1
    | 4 => s.c4r1
    | 5 => s.c5r1
    | 6 => s.c6r1
    | 7 => s.c7r1
    | 8 => s.c8r1
    | _ => s.c9r1
  | 2 => match l.val with
    | 0 => s.c0r2
    | 1 => s.c1r2
    | 2 => s.c2r2
    | 3 => s.c3r2
    | 4 => s.c4r2
    | 5 => s.c5r2
    | 6 => s.c6r2
    | 7 => s.c7r2
    | 8 => s.c8r2
    | _ => s.c9r2
  | _ => match l.val with
    | 0 => s.c0r3
    | 1 => s.c1r3
    | 2 => s.c2r3
    | 3 => s.c3r3
    | 4 => s.c4r3
    | 5 => s.c5r3
    | 6 => s.c6r3
    | 7 => s.c7r3
    | 8 => s.c8r3
    | _ => s.c9r3
theorem lane40_eq (s : F40) (r : Fin 4) (l : Fin 10) :
    lane40 s r l = Packed10.lane (projectRow s r) l := by
  rcases r with ⟨r,hr⟩
  have h : r=0 ∨ r=1 ∨ r=2 ∨ r=3 := by omega
  rcases h with rfl|rfl|rfl|rfl <;> rfl
end Submission.R11WideRows4
