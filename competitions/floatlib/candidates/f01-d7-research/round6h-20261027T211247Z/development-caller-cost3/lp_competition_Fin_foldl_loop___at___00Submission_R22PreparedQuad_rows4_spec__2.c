LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22PreparedQuad_rows4_spec__2(lean_object* v_n_18078_, lean_object* v_baseA_18079_, lean_object* v_baseB_18080_, lean_object* v_s_18081_, lean_object* v_p_18082_, lean_object* v_A_18083_, lean_object* v_B_18084_, lean_object* v_n_18085_, lean_object* v_x_18086_, lean_object* v_i_18087_){
_start:
{
uint8_t v___x_18088_; 
v___x_18088_ = lean_nat_dec_lt(v_i_18087_, v_n_18085_);
if (v___x_18088_ == 0)
{
lean_dec(v_i_18087_);
return v_x_18086_;
}
else
{
lean_object* v___x_18089_; float v_s2_18090_; lean_object* v___x_18091_; lean_object* v___x_18092_; lean_object* v___x_18093_; lean_object* v___x_18094_; uint32_t v___x_18095_; lean_object* v___x_18096_; lean_object* v___x_18097_; lean_object* v___x_18098_; lean_object* v___x_18099_; 
v___x_18089_ = lean_array_fget_borrowed(v_s_18081_, v_i_18087_);
v_s2_18090_ = lean_ctor_get_float32(v___x_18089_, 8);
v___x_18091_ = lean_unsigned_to_nat(2u);
v___x_18092_ = lean_nat_mul(v___x_18091_, v_n_18078_);
v___x_18093_ = lean_nat_add(v_baseA_18079_, v___x_18092_);
lean_dec(v___x_18092_);
v___x_18094_ = lean_nat_add(v_baseB_18080_, v_i_18087_);
v___x_18095_ = lp_competition_Submission_Packed10_finish(v_n_18078_, v___x_18093_, v___x_18094_, v_p_18082_, v_A_18083_, v_B_18084_, v_s2_18090_);
lean_dec(v___x_18094_);
lean_dec(v___x_18093_);
v___x_18096_ = lean_box_uint32(v___x_18095_);
v___x_18097_ = lean_array_push(v_x_18086_, v___x_18096_);
v___x_18098_ = lean_unsigned_to_nat(1u);
v___x_18099_ = lean_nat_add(v_i_18087_, v___x_18098_);
lean_dec(v_i_18087_);
v_x_18086_ = v___x_18097_;
v_i_18087_ = v___x_18099_;
goto _start;
}
}
}