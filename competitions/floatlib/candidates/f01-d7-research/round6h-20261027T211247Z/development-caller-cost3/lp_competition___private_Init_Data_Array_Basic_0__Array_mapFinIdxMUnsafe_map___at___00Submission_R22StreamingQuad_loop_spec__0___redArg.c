LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapFinIdxMUnsafe_map___at___00Submission_R22StreamingQuad_loop_spec__0___redArg(float v_a0_17139_, float v_a1_17140_, float v_a2_17141_, float v_a3_17142_, lean_object* v_rowB_17143_, lean_object* v_B_17144_, size_t v_sz_17145_, size_t v_i_17146_, lean_object* v_bs_17147_){
_start:
{
uint8_t v___x_17148_; 
v___x_17148_ = lean_usize_dec_lt(v_i_17146_, v_sz_17145_);
if (v___x_17148_ == 0)
{
return v_bs_17147_;
}
else
{
lean_object* v_v_17149_; lean_object* v___x_17150_; lean_object* v_bs_x27_17151_; uint32_t v___y_17153_; lean_object* v___x_17178_; lean_object* v___x_17179_; lean_object* v___x_17180_; uint8_t v___x_17181_; 
v_v_17149_ = lean_array_uget(v_bs_17147_, v_i_17146_);
v___x_17150_ = lean_unsigned_to_nat(0u);
v_bs_x27_17151_ = lean_array_uset(v_bs_17147_, v_i_17146_, v___x_17150_);
v___x_17178_ = lean_usize_to_nat(v_i_17146_);
v___x_17179_ = lean_nat_add(v_rowB_17143_, v___x_17178_);
lean_dec(v___x_17178_);
v___x_17180_ = lean_array_get_size(v_B_17144_);
v___x_17181_ = lean_nat_dec_lt(v___x_17179_, v___x_17180_);
if (v___x_17181_ == 0)
{
uint32_t v___x_17182_; 
lean_dec(v___x_17179_);
v___x_17182_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_17153_ = v___x_17182_;
goto v___jp_17152_;
}
else
{
lean_object* v___x_17183_; uint32_t v___x_17184_; 
v___x_17183_ = lean_array_fget_borrowed(v_B_17144_, v___x_17179_);
lean_dec(v___x_17179_);
v___x_17184_ = lean_unbox_uint32(v___x_17183_);
v___y_17153_ = v___x_17184_;
goto v___jp_17152_;
}
v___jp_17152_:
{
float v_s0_17154_; float v_s1_17155_; float v_s2_17156_; float v_s3_17157_; lean_object* v___x_17159_; uint8_t v_isShared_17160_; uint8_t v_isSharedCheck_17177_; 
v_s0_17154_ = lean_ctor_get_float32(v_v_17149_, 0);
v_s1_17155_ = lean_ctor_get_float32(v_v_17149_, 4);
v_s2_17156_ = lean_ctor_get_float32(v_v_17149_, 8);
v_s3_17157_ = lean_ctor_get_float32(v_v_17149_, 12);
v_isSharedCheck_17177_ = !lean_is_exclusive(v_v_17149_);
if (v_isSharedCheck_17177_ == 0)
{
v___x_17159_ = v_v_17149_;
v_isShared_17160_ = v_isSharedCheck_17177_;
goto v_resetjp_17158_;
}
else
{
lean_dec(v_v_17149_);
v___x_17159_ = lean_box(0);
v_isShared_17160_ = v_isSharedCheck_17177_;
goto v_resetjp_17158_;
}
v_resetjp_17158_:
{
float v___x_17161_; float v___x_17162_; float v___x_17163_; float v___x_17164_; float v___x_17165_; float v___x_17166_; float v___x_17167_; float v___x_17168_; float v___x_17169_; lean_object* v___x_17171_; 
v___x_17161_ = lean_float32_of_bits(v___y_17153_);
v___x_17162_ = lean_float32_mul(v_a0_17139_, v___x_17161_);
v___x_17163_ = lean_float32_add(v_s0_17154_, v___x_17162_);
v___x_17164_ = lean_float32_mul(v_a1_17140_, v___x_17161_);
v___x_17165_ = lean_float32_add(v_s1_17155_, v___x_17164_);
v___x_17166_ = lean_float32_mul(v_a2_17141_, v___x_17161_);
v___x_17167_ = lean_float32_add(v_s2_17156_, v___x_17166_);
v___x_17168_ = lean_float32_mul(v_a3_17142_, v___x_17161_);
v___x_17169_ = lean_float32_add(v_s3_17157_, v___x_17168_);
if (v_isShared_17160_ == 0)
{
v___x_17171_ = v___x_17159_;
goto v_reusejp_17170_;
}
else
{
lean_object* v_reuseFailAlloc_17176_; 
v_reuseFailAlloc_17176_ = lean_alloc_ctor(0, 0, 16);
v___x_17171_ = v_reuseFailAlloc_17176_;
goto v_reusejp_17170_;
}
v_reusejp_17170_:
{
size_t v___x_17172_; size_t v___x_17173_; lean_object* v___x_17174_; 
lean_ctor_set_float32(v___x_17171_, 0, v___x_17163_);
lean_ctor_set_float32(v___x_17171_, 4, v___x_17165_);
lean_ctor_set_float32(v___x_17171_, 8, v___x_17167_);
lean_ctor_set_float32(v___x_17171_, 12, v___x_17169_);
v___x_17172_ = ((size_t)1ULL);
v___x_17173_ = lean_usize_add(v_i_17146_, v___x_17172_);
v___x_17174_ = lean_array_uset(v_bs_x27_17151_, v_i_17146_, v___x_17171_);
v_i_17146_ = v___x_17173_;
v_bs_17147_ = v___x_17174_;
goto _start;
}
}
}
}
}
}