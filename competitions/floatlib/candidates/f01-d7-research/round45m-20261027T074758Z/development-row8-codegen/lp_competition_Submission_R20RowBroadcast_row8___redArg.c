LEAN_EXPORT lean_object* lp_competition_Submission_R20RowBroadcast_row8___redArg(lean_object* v_m_15776_, lean_object* v_n_15777_, lean_object* v_A_15778_, lean_object* v_B_15779_, lean_object* v_PB_15780_, lean_object* v_out_15781_, lean_object* v_r_15782_){
_start:
{
lean_object* v_bi_15783_; lean_object* v_baseA_15784_; lean_object* v___x_15785_; lean_object* v___x_15786_; lean_object* v_baseB_15787_; lean_object* v___x_15788_; lean_object* v___x_15789_; lean_object* v___x_15790_; lean_object* v_B0_15791_; lean_object* v___x_15792_; lean_object* v___x_15793_; lean_object* v_B1_15794_; lean_object* v___x_15795_; lean_object* v___x_15796_; lean_object* v_B2_15797_; lean_object* v___x_15798_; lean_object* v___x_15799_; lean_object* v_B3_15800_; float v___x_15801_; lean_object* v_result_15802_; lean_object* v___f_15803_; lean_object* v___x_15804_; 
v_bi_15783_ = lean_nat_div(v_r_15782_, v_m_15776_);
v_baseA_15784_ = lean_nat_mul(v_r_15782_, v_n_15777_);
v___x_15785_ = lean_nat_mul(v_bi_15783_, v_n_15777_);
v___x_15786_ = lean_unsigned_to_nat(8u);
v_baseB_15787_ = lean_nat_mul(v___x_15785_, v___x_15786_);
lean_dec(v___x_15785_);
v___x_15788_ = lean_unsigned_to_nat(4u);
v___x_15789_ = lean_unsigned_to_nat(0u);
v___x_15790_ = lp_competition_Submission_R15PackedB2_tileIndex___redArg(v___x_15786_, v_bi_15783_, v___x_15789_);
v_B0_15791_ = lean_array_fget_borrowed(v_PB_15780_, v___x_15790_);
lean_dec(v___x_15790_);
v___x_15792_ = lean_unsigned_to_nat(1u);
v___x_15793_ = lp_competition_Submission_R15PackedB2_tileIndex___redArg(v___x_15786_, v_bi_15783_, v___x_15792_);
v_B1_15794_ = lean_array_fget_borrowed(v_PB_15780_, v___x_15793_);
lean_dec(v___x_15793_);
v___x_15795_ = lean_unsigned_to_nat(2u);
v___x_15796_ = lp_competition_Submission_R15PackedB2_tileIndex___redArg(v___x_15786_, v_bi_15783_, v___x_15795_);
v_B2_15797_ = lean_array_fget_borrowed(v_PB_15780_, v___x_15796_);
lean_dec(v___x_15796_);
v___x_15798_ = lean_unsigned_to_nat(3u);
v___x_15799_ = lp_competition_Submission_R15PackedB2_tileIndex___redArg(v___x_15786_, v_bi_15783_, v___x_15798_);
lean_dec(v_bi_15783_);
v_B3_15800_ = lean_array_fget_borrowed(v_PB_15780_, v___x_15799_);
lean_dec(v___x_15799_);
v___x_15801_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_result_15802_ = lp_competition_Submission_R20RowBroadcast_loop(v_n_15777_, v_baseA_15784_, v_A_15778_, v_B0_15791_, v_B1_15794_, v_B2_15797_, v_B3_15800_, v___x_15789_, v___x_15801_, v___x_15801_, v___x_15801_, v___x_15801_, v___x_15801_, v___x_15801_, v___x_15801_, v___x_15801_);
v___f_15803_ = lean_alloc_closure((void*)(lp_competition_Submission_R20RowBroadcast_row8___redArg___lam__0___boxed), 14, 12);
lean_closure_set(v___f_15803_, 0, v_baseB_15787_);
lean_closure_set(v___f_15803_, 1, v___x_15789_);
lean_closure_set(v___f_15803_, 2, v___x_15792_);
lean_closure_set(v___f_15803_, 3, v___x_15795_);
lean_closure_set(v___f_15803_, 4, v___x_15798_);
lean_closure_set(v___f_15803_, 5, v___x_15788_);
lean_closure_set(v___f_15803_, 6, v_result_15802_);
lean_closure_set(v___f_15803_, 7, v_n_15777_);
lean_closure_set(v___f_15803_, 8, v_baseA_15784_);
lean_closure_set(v___f_15803_, 9, v___x_15786_);
lean_closure_set(v___f_15803_, 10, v_A_15778_);
lean_closure_set(v___f_15803_, 11, v_B_15779_);
v___x_15804_ = l_Fin_foldl_loop___redArg(v___x_15786_, v___f_15803_, v_out_15781_, v___x_15789_);
return v___x_15804_;
}
}
