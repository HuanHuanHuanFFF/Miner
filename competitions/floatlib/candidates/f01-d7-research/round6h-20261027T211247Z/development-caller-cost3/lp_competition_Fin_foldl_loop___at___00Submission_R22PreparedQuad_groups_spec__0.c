LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R22PreparedQuad_groups_spec__0(lean_object* v_b_18137_, lean_object* v_m_18138_, lean_object* v_n_18139_, lean_object* v_p_18140_, lean_object* v_A_18141_, lean_object* v_B_18142_, lean_object* v_prepared_18143_, lean_object* v_n_18144_, lean_object* v_x_18145_, lean_object* v_i_18146_){
_start:
{
uint8_t v___x_18147_; 
v___x_18147_ = lean_nat_dec_lt(v_i_18146_, v_n_18144_);
if (v___x_18147_ == 0)
{
lean_dec(v_i_18146_);
lean_dec(v_p_18140_);
return v_x_18145_;
}
else
{
lean_object* v___x_18148_; lean_object* v___x_18149_; lean_object* v___x_18150_; lean_object* v___x_18151_; lean_object* v___x_18152_; lean_object* v___x_18153_; lean_object* v___x_18154_; lean_object* v___x_18155_; lean_object* v___x_18156_; lean_object* v___x_18157_; 
v___x_18148_ = lean_unsigned_to_nat(4u);
v___x_18149_ = lean_nat_mul(v_b_18137_, v_m_18138_);
v___x_18150_ = lean_nat_mul(v___x_18148_, v_i_18146_);
v___x_18151_ = lean_nat_add(v___x_18149_, v___x_18150_);
lean_dec(v___x_18150_);
lean_dec(v___x_18149_);
v___x_18152_ = lean_nat_mul(v___x_18151_, v_n_18139_);
lean_dec(v___x_18151_);
v___x_18153_ = lean_nat_mul(v_b_18137_, v_n_18139_);
v___x_18154_ = lean_nat_mul(v___x_18153_, v_p_18140_);
lean_dec(v___x_18153_);
lean_inc(v_p_18140_);
v___x_18155_ = lp_competition_Submission_R22PreparedQuad_rows4(v_p_18140_, v_n_18139_, v___x_18152_, v___x_18154_, v_A_18141_, v_B_18142_, v_prepared_18143_, v_x_18145_);
lean_dec(v___x_18154_);
lean_dec(v___x_18152_);
v___x_18156_ = lean_unsigned_to_nat(1u);
v___x_18157_ = lean_nat_add(v_i_18146_, v___x_18156_);
lean_dec(v_i_18146_);
v_x_18145_ = v___x_18155_;
v_i_18146_ = v___x_18157_;
goto _start;
}
}
}