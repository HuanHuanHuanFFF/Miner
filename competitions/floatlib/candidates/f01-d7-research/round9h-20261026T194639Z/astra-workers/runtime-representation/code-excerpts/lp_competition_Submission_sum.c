LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object* v_n_13236_, lean_object* v_x_13237_){
_start:
{
lean_object* v___x_13238_; uint8_t v___x_13239_; 
v___x_13238_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_13239_ = lean_nat_dec_lt(v_n_13236_, v___x_13238_);
if (v___x_13239_ == 0)
{
lean_object* v___x_13240_; float v___x_13241_; uint32_t v___x_13242_; 
v___x_13240_ = lean_unsigned_to_nat(0u);
v___x_13241_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_13242_ = lp_competition_Submission_R7SinglePassSum_natLoop(v_n_13236_, v_x_13237_, v___x_13240_, v___x_13241_);
return v___x_13242_;
}
else
{
size_t v___x_13243_; size_t v___x_13244_; float v___x_13245_; uint32_t v___x_13246_; 
v___x_13243_ = lean_usize_of_nat(v_n_13236_);
v___x_13244_ = ((size_t)0ULL);
v___x_13245_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_13246_ = lp_competition_Submission_R7SinglePassSum_loop___redArg(v_n_13236_, v_x_13237_, v___x_13243_, v___x_13244_, v___x_13245_);
return v___x_13246_;
}
}
}
