LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22PreparedQuad_rows4_spec__1(lean_object* v_baseA_18046_, lean_object* v_n_18047_, lean_object* v_baseB_18048_, lean_object* v_s_18049_, lean_object* v_p_18050_, lean_object* v_A_18051_, lean_object* v_B_18052_, lean_object* v_n_18053_, lean_object* v_x_18054_, lean_object* v_i_18055_){
_start:
{
uint8_t v___x_18056_; 
v___x_18056_ = lean_nat_dec_lt(v_i_18055_, v_n_18053_);
if (v___x_18056_ == 0)
{
lean_dec(v_i_18055_);
return v_x_18054_;
}
else
{
lean_object* v___x_18057_; float v_s1_18058_; lean_object* v___x_18059_; lean_object* v___x_18060_; uint32_t v___x_18061_; lean_object* v___x_18062_; lean_object* v___x_18063_; lean_object* v___x_18064_; lean_object* v___x_18065_; 
v___x_18057_ = lean_array_fget_borrowed(v_s_18049_, v_i_18055_);
v_s1_18058_ = lean_ctor_get_float32(v___x_18057_, 4);
v___x_18059_ = lean_nat_add(v_baseA_18046_, v_n_18047_);
v___x_18060_ = lean_nat_add(v_baseB_18048_, v_i_18055_);
v___x_18061_ = lp_competition_Submission_Packed10_finish(v_n_18047_, v___x_18059_, v___x_18060_, v_p_18050_, v_A_18051_, v_B_18052_, v_s1_18058_);
lean_dec(v___x_18060_);
lean_dec(v___x_18059_);
v___x_18062_ = lean_box_uint32(v___x_18061_);
v___x_18063_ = lean_array_push(v_x_18054_, v___x_18062_);
v___x_18064_ = lean_unsigned_to_nat(1u);
v___x_18065_ = lean_nat_add(v_i_18055_, v___x_18064_);
lean_dec(v_i_18055_);
v_x_18054_ = v___x_18063_;
v_i_18055_ = v___x_18065_;
goto _start;
}
}
}