LEAN_EXPORT lean_object* lp_competition_Submission_R20TerminalPair_emit2(lean_object* v_n_14642_, lean_object* v_baseA_14643_, lean_object* v_baseB_14644_, lean_object* v_p_14645_, lean_object* v_A_14646_, lean_object* v_B_14647_, lean_object* v_out_14648_, float v_s0_14649_, float v_s1_14650_){
_start:
{
uint32_t v___x_14651_; lean_object* v___x_14652_; lean_object* v_out_14653_; lean_object* v___x_14654_; lean_object* v___x_14655_; uint32_t v___x_14656_; lean_object* v___x_14657_; lean_object* v___x_14658_; 
v___x_14651_ = lp_competition_Submission_Packed10_finish(v_n_14642_, v_baseA_14643_, v_baseB_14644_, v_p_14645_, v_A_14646_, v_B_14647_, v_s0_14649_);
v___x_14652_ = lean_box_uint32(v___x_14651_);
v_out_14653_ = lean_array_push(v_out_14648_, v___x_14652_);
v___x_14654_ = lean_unsigned_to_nat(1u);
v___x_14655_ = lean_nat_add(v_baseB_14644_, v___x_14654_);
v___x_14656_ = lp_competition_Submission_Packed10_finish(v_n_14642_, v_baseA_14643_, v___x_14655_, v_p_14645_, v_A_14646_, v_B_14647_, v_s1_14650_);
lean_dec(v___x_14655_);
v___x_14657_ = lean_box_uint32(v___x_14656_);
v___x_14658_ = lean_array_push(v_out_14653_, v___x_14657_);
return v___x_14658_;
}
}
