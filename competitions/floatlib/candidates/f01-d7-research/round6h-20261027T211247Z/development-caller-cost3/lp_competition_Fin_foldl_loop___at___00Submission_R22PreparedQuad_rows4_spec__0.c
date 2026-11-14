LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22PreparedQuad_rows4_spec__0(lean_object* v_baseB_18015_, lean_object* v_s_18016_, lean_object* v_n_18017_, lean_object* v_baseA_18018_, lean_object* v_p_18019_, lean_object* v_A_18020_, lean_object* v_B_18021_, lean_object* v_n_18022_, lean_object* v_x_18023_, lean_object* v_i_18024_){
_start:
{
uint8_t v___x_18025_; 
v___x_18025_ = lean_nat_dec_lt(v_i_18024_, v_n_18022_);
if (v___x_18025_ == 0)
{
lean_dec(v_i_18024_);
return v_x_18023_;
}
else
{
lean_object* v___x_18026_; float v_s0_18027_; lean_object* v___x_18028_; uint32_t v___x_18029_; lean_object* v___x_18030_; lean_object* v___x_18031_; lean_object* v___x_18032_; lean_object* v___x_18033_; 
v___x_18026_ = lean_array_fget_borrowed(v_s_18016_, v_i_18024_);
v_s0_18027_ = lean_ctor_get_float32(v___x_18026_, 0);
v___x_18028_ = lean_nat_add(v_baseB_18015_, v_i_18024_);
v___x_18029_ = lp_competition_Submission_Packed10_finish(v_n_18017_, v_baseA_18018_, v___x_18028_, v_p_18019_, v_A_18020_, v_B_18021_, v_s0_18027_);
lean_dec(v___x_18028_);
v___x_18030_ = lean_box_uint32(v___x_18029_);
v___x_18031_ = lean_array_push(v_x_18023_, v___x_18030_);
v___x_18032_ = lean_unsigned_to_nat(1u);
v___x_18033_ = lean_nat_add(v_i_18024_, v___x_18032_);
lean_dec(v_i_18024_);
v_x_18023_ = v___x_18031_;
v_i_18024_ = v___x_18033_;
goto _start;
}
}
}