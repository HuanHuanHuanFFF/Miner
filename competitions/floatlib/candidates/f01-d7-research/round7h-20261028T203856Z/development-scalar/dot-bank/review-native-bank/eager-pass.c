LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passEager(lean_object* v_p_1274_, uint32_t v_s_1275_, lean_object* v_iters_1276_)
{
_start:
{
lean_object* v_zero_1277_; uint8_t v_isZero_1278_; 
v_zero_1277_ = lean_unsigned_to_nat(0u);
v_isZero_1278_ = lean_nat_dec_eq(v_iters_1276_, v_zero_1277_);
if (v_isZero_1278_ == 1)
{
lean_dec(v_iters_1276_);
lean_dec_ref(v_p_1274_);
return v_s_1275_;
}
else
{
lean_object* v_one_1279_; lean_object* v_n_1280_; lean_object* v_p_1281_; lean_object* v_fst_1282_; lean_object* v_snd_1283_; lean_object* v_out_1284_; uint32_t v_word_1285_; uint32_t v___x_1286_; 
v_one_1279_ = lean_unsigned_to_nat(1u);
v_n_1280_ = lean_nat_sub(v_iters_1276_, v_one_1279_);
lean_dec(v_iters_1276_);
v_p_1281_ = lp_competition_R24DotBarrier_touchBank(v_n_1280_, v_p_1274_);
v_fst_1282_ = lean_ctor_get(v_p_1281_, 0);
lean_inc(v_fst_1282_);
v_snd_1283_ = lean_ctor_get(v_p_1281_, 1);
lean_inc(v_snd_1283_);
v_out_1284_ = lp_competition_Submission_R24GenericDotBank_eagerBank(v_fst_1282_, v_snd_1283_);
lean_dec(v_snd_1283_);
lean_dec(v_fst_1282_);
v_word_1285_ = lp_competition_R24DotBankHarness_hashAll(v_out_1284_);
lean_dec_ref(v_out_1284_);
v___x_1286_ = lean_uint32_add(v_s_1275_, v_word_1285_);
v_p_1274_ = v_p_1281_;
v_s_1275_ = v___x_1286_;
v_iters_1276_ = v_n_1280_;
goto _start;
}
}
}
