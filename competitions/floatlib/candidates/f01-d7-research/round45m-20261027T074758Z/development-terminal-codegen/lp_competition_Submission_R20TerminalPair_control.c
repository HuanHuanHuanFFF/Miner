LEAN_EXPORT lean_object* lp_competition_Submission_R20TerminalPair_control(lean_object* v_n_14742_, lean_object* v_baseA_14743_, lean_object* v_baseB_14744_, lean_object* v_p_14745_, lean_object* v_A_14746_, lean_object* v_B_14747_, lean_object* v_out_14748_){
_start:
{
lean_object* v___x_14749_; float v___x_14750_; lean_object* v_r_14751_; float v_s0_14752_; float v_s1_14753_; uint32_t v___x_14754_; lean_object* v___x_14755_; lean_object* v_out_14756_; lean_object* v___x_14757_; lean_object* v___x_14758_; uint32_t v___x_14759_; lean_object* v___x_14760_; lean_object* v___x_14761_; 
v___x_14749_ = lean_unsigned_to_nat(0u);
v___x_14750_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_r_14751_ = lp_competition_Submission_R20TerminalPair_loopPair(v_n_14742_, v_baseA_14743_, v_baseB_14744_, v_p_14745_, v_A_14746_, v_B_14747_, v___x_14749_, v___x_14750_, v___x_14750_);
v_s0_14752_ = lean_ctor_get_float32(v_r_14751_, 0);
v_s1_14753_ = lean_ctor_get_float32(v_r_14751_, 4);
lean_dec_ref(v_r_14751_);
v___x_14754_ = lp_competition_Submission_Packed10_finish(v_n_14742_, v_baseA_14743_, v_baseB_14744_, v_p_14745_, v_A_14746_, v_B_14747_, v_s0_14752_);
v___x_14755_ = lean_box_uint32(v___x_14754_);
v_out_14756_ = lean_array_push(v_out_14748_, v___x_14755_);
v___x_14757_ = lean_unsigned_to_nat(1u);
v___x_14758_ = lean_nat_add(v_baseB_14744_, v___x_14757_);
v___x_14759_ = lp_competition_Submission_Packed10_finish(v_n_14742_, v_baseA_14743_, v___x_14758_, v_p_14745_, v_A_14746_, v_B_14747_, v_s1_14753_);
lean_dec(v___x_14758_);
v___x_14760_ = lean_box_uint32(v___x_14759_);
v___x_14761_ = lean_array_push(v_out_14756_, v___x_14760_);
return v___x_14761_;
}
}
