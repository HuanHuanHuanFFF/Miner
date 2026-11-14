namespace Submission.R26TailAgreement
open Submission.R24PortableF64
open Submission.R24RepresentationSum

def actualTerms (a b : FloatArray) (index count : Nat) : List Float :=
  (List.range' index count).map (fun i => a.get! i * b.get! i)

theorem sumRemaining_eq_loop (a b : FloatArray) (count index : Nat) (acc : Float) :
    sumRemaining a b index acc count = loop (actualTerms a b index count) acc := by
  induction count generalizing index acc with
  | zero => rfl
  | succ count ih =>
    simpa only [sumRemaining, actualTerms, List.range'_succ, List.map_cons, loop] using
      ih (index + 1) (acc + a.get! index * b.get! index)

theorem actualTerms_length (a b : FloatArray) (index count : Nat) :
    (actualTerms a b index count).length = count := by
  simp only [actualTerms, List.length_map, List.length_range']

theorem sumRemaining_zero_eq_sum (a b : FloatArray) (count : Nat) :
    sumRemaining a b 0 (Float.ofBits 0) count = sum (actualTerms a b 0 count) := by
  exact sumRemaining_eq_loop a b count 0 (Float.ofBits 0)

end Submission.R26TailAgreement
