LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passLazy(lean_object* v_p_1573_, uint32_t v_s_1574_, lean_object* v_iters_1575_)
{
_start:
{
lean_object* v_zero_1576_; uint8_t v_isZero_1577_; 
v_zero_1576_ = lean_unsigned_to_nat(0u);
v_isZero_1577_ = lean_nat_dec_eq(v_iters_1575_, v_zero_1576_);
if (v_isZero_1577_ == 1)
{
lean_dec(v_iters_1575_);
lean_dec_ref(v_p_1573_);
return v_s_1574_;
}
else
{
lean_object* v_one_1578_; lean_object* v_n_1579_; lean_object* v_p_1580_; lean_object* v_fst_1581_; lean_object* v_snd_1582_; lean_object* v_out_1583_; uint32_t v_word_1584_; uint32_t v___x_1585_; 
v_one_1578_ = lean_unsigned_to_nat(1u);
v_n_1579_ = lean_nat_sub(v_iters_1575_, v_one_1578_);
lean_dec(v_iters_1575_);
v_p_1580_ = lp_competition_R24DotBarrier_touchBank(v_n_1579_, v_p_1573_);
v_fst_1581_ = lean_ctor_get(v_p_1580_, 0);
lean_inc(v_fst_1581_);
v_snd_1582_ = lean_ctor_get(v_p_1580_, 1);
lean_inc(v_snd_1582_);
v_out_1583_ = lp_competition_Submission_R24GenericDotBank_lazyBank(v_fst_1581_, v_snd_1582_);
lean_dec(v_snd_1582_);
lean_dec(v_fst_1581_);
v_word_1584_ = lp_competition_R24DotBankHarness_hashAll(v_out_1583_);
lean_dec_ref(v_out_1583_);
v___x_1585_ = lean_uint32_add(v_s_1574_, v_word_1584_);
v_p_1573_ = v_p_1580_;
v_s_1574_ = v___x_1585_;
v_iters_1575_ = v_n_1579_;
goto _start;
}
}
}
