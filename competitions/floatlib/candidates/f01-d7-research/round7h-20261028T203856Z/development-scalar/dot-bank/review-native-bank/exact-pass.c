LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passExact(lean_object* v_p_960_, uint32_t v_s_961_, lean_object* v_iters_962_)
{
_start:
{
lean_object* v_zero_963_; uint8_t v_isZero_964_; 
v_zero_963_ = lean_unsigned_to_nat(0u);
v_isZero_964_ = lean_nat_dec_eq(v_iters_962_, v_zero_963_);
if (v_isZero_964_ == 1)
{
lean_dec(v_iters_962_);
lean_dec_ref(v_p_960_);
return v_s_961_;
}
else
{
lean_object* v_one_965_; lean_object* v_n_966_; lean_object* v_p_967_; lean_object* v_fst_968_; lean_object* v_snd_969_; lean_object* v_out_970_; uint32_t v_word_971_; uint32_t v___x_972_; 
v_one_965_ = lean_unsigned_to_nat(1u);
v_n_966_ = lean_nat_sub(v_iters_962_, v_one_965_);
lean_dec(v_iters_962_);
v_p_967_ = lp_competition_R24DotBarrier_touchBank(v_n_966_, v_p_960_);
v_fst_968_ = lean_ctor_get(v_p_967_, 0);
lean_inc(v_fst_968_);
v_snd_969_ = lean_ctor_get(v_p_967_, 1);
lean_inc(v_snd_969_);
v_out_970_ = lp_competition_Submission_R24GenericDotBank_exactBank(v_fst_968_, v_snd_969_);
lean_dec(v_snd_969_);
lean_dec(v_fst_968_);
v_word_971_ = lp_competition_R24DotBankHarness_hashAll(v_out_970_);
lean_dec_ref(v_out_970_);
v___x_972_ = lean_uint32_add(v_s_961_, v_word_971_);
v_p_960_ = v_p_967_;
v_s_961_ = v___x_972_;
v_iters_962_ = v_n_966_;
goto _start;
}
}
}
