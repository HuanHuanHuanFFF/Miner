LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22StreamingQuad_rows4_spec__2(lean_object* v_n_17301_, lean_object* v_baseA_17302_, lean_object* v_baseB_17303_, lean_object* v_s_17304_, lean_object* v_p_17305_, lean_object* v_A_17306_, lean_object* v_B_17307_, lean_object* v_n_17308_, lean_object* v_x_17309_, lean_object* v_i_17310_){
_start:
{
uint8_t v___x_17311_; 
v___x_17311_ = lean_nat_dec_lt(v_i_17310_, v_n_17308_);
if (v___x_17311_ == 0)
{
lean_dec(v_i_17310_);
return v_x_17309_;
}
else
{
lean_object* v___x_17312_; float v_s2_17313_; lean_object* v___x_17314_; lean_object* v___x_17315_; lean_object* v___x_17316_; lean_object* v___x_17317_; uint32_t v___x_17318_; lean_object* v___x_17319_; lean_object* v___x_17320_; lean_object* v___x_17321_; lean_object* v___x_17322_; 
v___x_17312_ = lean_array_fget_borrowed(v_s_17304_, v_i_17310_);
v_s2_17313_ = lean_ctor_get_float32(v___x_17312_, 8);
v___x_17314_ = lean_unsigned_to_nat(2u);
v___x_17315_ = lean_nat_mul(v___x_17314_, v_n_17301_);
v___x_17316_ = lean_nat_add(v_baseA_17302_, v___x_17315_);
lean_dec(v___x_17315_);
v___x_17317_ = lean_nat_add(v_baseB_17303_, v_i_17310_);
v___x_17318_ = lp_competition_Submission_Packed10_finish(v_n_17301_, v___x_17316_, v___x_17317_, v_p_17305_, v_A_17306_, v_B_17307_, v_s2_17313_);
lean_dec(v___x_17317_);
lean_dec(v___x_17316_);
v___x_17319_ = lean_box_uint32(v___x_17318_);
v___x_17320_ = lean_array_push(v_x_17309_, v___x_17319_);
v___x_17321_ = lean_unsigned_to_nat(1u);
v___x_17322_ = lean_nat_add(v_i_17310_, v___x_17321_);
lean_dec(v_i_17310_);
v_x_17309_ = v___x_17320_;
v_i_17310_ = v___x_17322_;
goto _start;
}
}
}