LEAN_EXPORT lean_object* lp_competition_Submission_R19DCRawPair_output(lean_object* v_batch_14155_, lean_object* v_m_14156_, lean_object* v_n_14157_, lean_object* v_p_14158_, lean_object* v_A_14159_, lean_object* v_B_14160_){
_start:
{
lean_object* v___x_14161_; lean_object* v___x_14162_; lean_object* v___x_14163_; lean_object* v___x_14164_; lean_object* v___x_14165_; 
v___x_14161_ = lean_nat_mul(v_batch_14155_, v_m_14156_);
v___x_14162_ = lean_nat_mul(v___x_14161_, v_p_14158_);
v___x_14163_ = lean_mk_empty_array_with_capacity(v___x_14162_);
lean_dec(v___x_14162_);
v___x_14164_ = lean_unsigned_to_nat(0u);
v___x_14165_ = lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__3(v_n_14157_, v_m_14156_, v_p_14158_, v_A_14159_, v_B_14160_, v___x_14161_, v___x_14163_, v___x_14164_);
lean_dec(v___x_14161_);
return v___x_14165_;
}
}
