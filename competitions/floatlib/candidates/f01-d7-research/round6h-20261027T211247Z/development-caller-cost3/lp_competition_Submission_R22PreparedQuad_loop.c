LEAN_EXPORT lean_object* lp_competition_Submission_R22PreparedQuad_loop(lean_object* v_p_17881_, lean_object* v_n_17882_, lean_object* v_baseA_17883_, lean_object* v_baseB_17884_, lean_object* v_A_17885_, lean_object* v_B_17886_, lean_object* v_k_17887_, lean_object* v_s_17888_){
_start:
{
uint8_t v___x_17889_; 
v___x_17889_ = lean_nat_dec_lt(v_k_17887_, v_n_17882_);
if (v___x_17889_ == 0)
{
lean_dec(v_k_17887_);
return v_s_17888_;
}
else
{
lean_object* v___x_17890_; lean_object* v___x_17891_; float v___y_17893_; float v___y_17894_; float v___y_17895_; uint32_t v___y_17896_; lean_object* v___x_17904_; uint32_t v___x_17905_; float v___y_17907_; float v___y_17908_; uint32_t v___y_17909_; float v___y_17920_; uint32_t v___y_17921_; uint32_t v___y_17932_; lean_object* v___x_17940_; uint8_t v___x_17941_; 
v___x_17890_ = lean_unsigned_to_nat(1u);
v___x_17891_ = lean_nat_add(v_k_17887_, v___x_17890_);
v___x_17904_ = lean_nat_add(v_baseA_17883_, v_k_17887_);
v___x_17905_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_17940_ = lean_array_get_size(v_A_17885_);
v___x_17941_ = lean_nat_dec_lt(v___x_17904_, v___x_17940_);
if (v___x_17941_ == 0)
{
lean_dec(v___x_17904_);
v___y_17932_ = v___x_17905_;
goto v___jp_17931_;
}
else
{
lean_object* v___x_17942_; uint32_t v___x_17943_; 
v___x_17942_ = lean_array_fget_borrowed(v_A_17885_, v___x_17904_);
lean_dec(v___x_17904_);
v___x_17943_ = lean_unbox_uint32(v___x_17942_);
v___y_17932_ = v___x_17943_;
goto v___jp_17931_;
}
v___jp_17892_:
{
float v_a3_17897_; lean_object* v___x_17898_; lean_object* v_rowB_17899_; size_t v_sz_17900_; size_t v___x_17901_; lean_object* v___x_17902_; 
v_a3_17897_ = lean_float32_of_bits(v___y_17896_);
v___x_17898_ = lean_nat_mul(v_k_17887_, v_p_17881_);
lean_dec(v_k_17887_);
v_rowB_17899_ = lean_nat_add(v_baseB_17884_, v___x_17898_);
lean_dec(v___x_17898_);
v_sz_17900_ = lean_array_size(v_s_17888_);
v___x_17901_ = ((size_t)0ULL);
v___x_17902_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapFinIdxMUnsafe_map___at___00Submission_R22PreparedQuad_loop_spec__0___redArg(v___y_17895_, v___y_17894_, v___y_17893_, v_a3_17897_, v_rowB_17899_, v_B_17886_, v_sz_17900_, v___x_17901_, v_s_17888_);
lean_dec(v_rowB_17899_);
v_k_17887_ = v___x_17891_;
v_s_17888_ = v___x_17902_;
goto _start;
}
v___jp_17906_:
{
float v_a2_17910_; lean_object* v___x_17911_; lean_object* v___x_17912_; lean_object* v___x_17913_; lean_object* v___x_17914_; lean_object* v___x_17915_; uint8_t v___x_17916_; 
v_a2_17910_ = lean_float32_of_bits(v___y_17909_);
v___x_17911_ = lean_unsigned_to_nat(3u);
v___x_17912_ = lean_nat_mul(v___x_17911_, v_n_17882_);
v___x_17913_ = lean_nat_add(v_baseA_17883_, v___x_17912_);
lean_dec(v___x_17912_);
v___x_17914_ = lean_nat_add(v___x_17913_, v_k_17887_);
lean_dec(v___x_17913_);
v___x_17915_ = lean_array_get_size(v_A_17885_);
v___x_17916_ = lean_nat_dec_lt(v___x_17914_, v___x_17915_);
if (v___x_17916_ == 0)
{
lean_dec(v___x_17914_);
v___y_17893_ = v_a2_17910_;
v___y_17894_ = v___y_17907_;
v___y_17895_ = v___y_17908_;
v___y_17896_ = v___x_17905_;
goto v___jp_17892_;
}
else
{
lean_object* v___x_17917_; uint32_t v___x_17918_; 
v___x_17917_ = lean_array_fget_borrowed(v_A_17885_, v___x_17914_);
lean_dec(v___x_17914_);
v___x_17918_ = lean_unbox_uint32(v___x_17917_);
v___y_17893_ = v_a2_17910_;
v___y_17894_ = v___y_17907_;
v___y_17895_ = v___y_17908_;
v___y_17896_ = v___x_17918_;
goto v___jp_17892_;
}
}
v___jp_17919_:
{
float v_a1_17922_; lean_object* v___x_17923_; lean_object* v___x_17924_; lean_object* v___x_17925_; lean_object* v___x_17926_; lean_object* v___x_17927_; uint8_t v___x_17928_; 
v_a1_17922_ = lean_float32_of_bits(v___y_17921_);
v___x_17923_ = lean_unsigned_to_nat(2u);
v___x_17924_ = lean_nat_mul(v___x_17923_, v_n_17882_);
v___x_17925_ = lean_nat_add(v_baseA_17883_, v___x_17924_);
lean_dec(v___x_17924_);
v___x_17926_ = lean_nat_add(v___x_17925_, v_k_17887_);
lean_dec(v___x_17925_);
v___x_17927_ = lean_array_get_size(v_A_17885_);
v___x_17928_ = lean_nat_dec_lt(v___x_17926_, v___x_17927_);
if (v___x_17928_ == 0)
{
lean_dec(v___x_17926_);
v___y_17907_ = v_a1_17922_;
v___y_17908_ = v___y_17920_;
v___y_17909_ = v___x_17905_;
goto v___jp_17906_;
}
else
{
lean_object* v___x_17929_; uint32_t v___x_17930_; 
v___x_17929_ = lean_array_fget_borrowed(v_A_17885_, v___x_17926_);
lean_dec(v___x_17926_);
v___x_17930_ = lean_unbox_uint32(v___x_17929_);
v___y_17907_ = v_a1_17922_;
v___y_17908_ = v___y_17920_;
v___y_17909_ = v___x_17930_;
goto v___jp_17906_;
}
}
v___jp_17931_:
{
float v_a0_17933_; lean_object* v___x_17934_; lean_object* v___x_17935_; lean_object* v___x_17936_; uint8_t v___x_17937_; 
v_a0_17933_ = lean_float32_of_bits(v___y_17932_);
v___x_17934_ = lean_nat_add(v_baseA_17883_, v_n_17882_);
v___x_17935_ = lean_nat_add(v___x_17934_, v_k_17887_);
lean_dec(v___x_17934_);
v___x_17936_ = lean_array_get_size(v_A_17885_);
v___x_17937_ = lean_nat_dec_lt(v___x_17935_, v___x_17936_);
if (v___x_17937_ == 0)
{
lean_dec(v___x_17935_);
v___y_17920_ = v_a0_17933_;
v___y_17921_ = v___x_17905_;
goto v___jp_17919_;
}
else
{
lean_object* v___x_17938_; uint32_t v___x_17939_; 
v___x_17938_ = lean_array_fget_borrowed(v_A_17885_, v___x_17935_);
lean_dec(v___x_17935_);
v___x_17939_ = lean_unbox_uint32(v___x_17938_);
v___y_17920_ = v_a0_17933_;
v___y_17921_ = v___x_17939_;
goto v___jp_17919_;
}
}
}
}
}