namespace Submission.R11WideRows4
open FloatLib.Floats Competition
def projectRow (s : F40) (r : Fin 4) : Packed10.F10 :=
  match r.val with
  | 0 => ⟨s.c0r0, s.c1r0, s.c2r0, s.c3r0, s.c4r0, s.c5r0, s.c6r0, s.c7r0, s.c8r0, s.c9r0⟩
  | 1 => ⟨s.c0r1, s.c1r1, s.c2r1, s.c3r1, s.c4r1, s.c5r1, s.c6r1, s.c7r1, s.c8r1, s.c9r1⟩
  | 2 => ⟨s.c0r2, s.c1r2, s.c2r2, s.c3r2, s.c4r2, s.c5r2, s.c6r2, s.c7r2, s.c8r2, s.c9r2⟩
  | _ => ⟨s.c0r3, s.c1r3, s.c2r3, s.c3r3, s.c4r3, s.c5r3, s.c6r3, s.c7r3, s.c8r3, s.c9r3⟩

end Submission.R11WideRows4
