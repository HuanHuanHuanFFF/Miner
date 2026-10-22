import Submission

example : Competition.Obligation Submission.add := Submission.add_spec
example : Competition.MulObligation Submission.mul := Submission.mul_spec
example : Competition.SumObligation Submission.sum := Submission.sum_spec
example : Competition.BmmObligation Submission.bmm := Submission.bmm_spec

theorem r2w02b_four_obligations :
    Competition.Obligation Submission.add ∧ Competition.MulObligation Submission.mul ∧
      Competition.SumObligation Submission.sum ∧ Competition.BmmObligation Submission.bmm :=
  ⟨Submission.add_spec, Submission.mul_spec, Submission.sum_spec, Submission.bmm_spec⟩

#check Submission.Packed4.packB_lane
#check Submission.Packed4.nativeA_getD
#check Submission.Packed4.dot4_lane
#check Submission.Packed4.finish_dot4_lane
#check Submission.Packed4.decode_bounds
#check Submission.Packed4.tile_finish
#check Submission.Packed4.outputFromTiles_eq
#check Submission.Packed4.core_eq_reference
#print axioms Submission.bmm_spec
#print axioms r2w02b_four_obligations
