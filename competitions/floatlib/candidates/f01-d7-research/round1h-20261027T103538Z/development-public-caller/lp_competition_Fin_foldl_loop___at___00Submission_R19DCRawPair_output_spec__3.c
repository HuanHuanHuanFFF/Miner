LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__3(lean_object* v_n_14126_, lean_object* v_m_14127_, lean_object* v_p_14128_, lean_object* v_A_14129_, lean_object* v_B_14130_, lean_object* v_n_14131_, lean_object* v_x_14132_, lean_object* v_i_14133_){
_start:
{
uint8_t v___x_14134_; 
v___x_14134_ = lean_nat_dec_lt(v_i_14133_, v_n_14131_);
if (v___x_14134_ == 0)
{
lean_dec(v_i_14133_);
return v_x_14132_;
}
else
{
lean_object* v_baseA_14135_; lean_object* v___x_14136_; lean_object* v___x_14137_; lean_object* v_baseB_14138_; lean_object* v___x_14139_; lean_object* v___x_14140_; lean_object* v___x_14141_; lean_object* v___x_14142_; lean_object* v___x_14143_; lean_object* v___x_14144_; 
v_baseA_14135_ = lean_nat_mul(v_i_14133_, v_n_14126_);
v___x_14136_ = lean_nat_div(v_i_14133_, v_m_14127_);
v___x_14137_ = lean_nat_mul(v___x_14136_, v_n_14126_);
lean_dec(v___x_14136_);
v_baseB_14138_ = lean_nat_mul(v___x_14137_, v_p_14128_);
lean_dec(v___x_14137_);
v___x_14139_ = lean_unsigned_to_nat(1u);
v___x_14140_ = lean_nat_add(v_p_14128_, v___x_14139_);
v___x_14141_ = lean_nat_shiftr(v___x_14140_, v___x_14139_);
lean_dec(v___x_14140_);
v___x_14142_ = lean_unsigned_to_nat(0u);
v___x_14143_ = lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__2(v_baseB_14138_, v_n_14126_, v_baseA_14135_, v_p_14128_, v_A_14129_, v_B_14130_, v___x_14141_, v_x_14132_, v___x_14142_);
lean_dec(v___x_14141_);
lean_dec(v_baseA_14135_);
lean_dec(v_baseB_14138_);
v___x_14144_ = lean_nat_add(v_i_14133_, v___x_14139_);
lean_dec(v_i_14133_);
v_x_14132_ = v___x_14143_;
v_i_14133_ = v___x_14144_;
goto _start;
}
}
}
