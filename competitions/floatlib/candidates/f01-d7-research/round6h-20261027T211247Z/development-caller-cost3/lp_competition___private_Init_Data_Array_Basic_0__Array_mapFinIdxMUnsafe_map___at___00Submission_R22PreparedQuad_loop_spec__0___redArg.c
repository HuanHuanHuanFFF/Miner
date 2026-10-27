LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapFinIdxMUnsafe_map___at___00Submission_R22PreparedQuad_loop_spec__0___redArg(float v_a0_17820_, float v_a1_17821_, float v_a2_17822_, float v_a3_17823_, lean_object* v_rowB_17824_, lean_object* v_B_17825_, size_t v_sz_17826_, size_t v_i_17827_, lean_object* v_bs_17828_){
_start:
{
uint8_t v___x_17829_; 
v___x_17829_ = lean_usize_dec_lt(v_i_17827_, v_sz_17826_);
if (v___x_17829_ == 0)
{
return v_bs_17828_;
}
else
{
lean_object* v_v_17830_; lean_object* v___x_17831_; lean_object* v_bs_x27_17832_; float v___y_17834_; lean_object* v___x_17858_; lean_object* v___x_17859_; lean_object* v___x_17860_; uint8_t v___x_17861_; 
v_v_17830_ = lean_array_uget(v_bs_17828_, v_i_17827_);
v___x_17831_ = lean_unsigned_to_nat(0u);
v_bs_x27_17832_ = lean_array_uset(v_bs_17828_, v_i_17827_, v___x_17831_);
v___x_17858_ = lean_usize_to_nat(v_i_17827_);
v___x_17859_ = lean_nat_add(v_rowB_17824_, v___x_17858_);
lean_dec(v___x_17858_);
v___x_17860_ = lean_array_get_size(v_B_17825_);
v___x_17861_ = lean_nat_dec_lt(v___x_17859_, v___x_17860_);
if (v___x_17861_ == 0)
{
float v___x_17862_; 
lean_dec(v___x_17859_);
v___x_17862_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___y_17834_ = v___x_17862_;
goto v___jp_17833_;
}
else
{
lean_object* v___x_17863_; float v___x_17864_; 
v___x_17863_ = lean_array_fget_borrowed(v_B_17825_, v___x_17859_);
lean_dec(v___x_17859_);
v___x_17864_ = lean_unbox_float32(v___x_17863_);
v___y_17834_ = v___x_17864_;
goto v___jp_17833_;
}
v___jp_17833_:
{
float v_s0_17835_; float v_s1_17836_; float v_s2_17837_; float v_s3_17838_; lean_object* v___x_17840_; uint8_t v_isShared_17841_; uint8_t v_isSharedCheck_17857_; 
v_s0_17835_ = lean_ctor_get_float32(v_v_17830_, 0);
v_s1_17836_ = lean_ctor_get_float32(v_v_17830_, 4);
v_s2_17837_ = lean_ctor_get_float32(v_v_17830_, 8);
v_s3_17838_ = lean_ctor_get_float32(v_v_17830_, 12);
v_isSharedCheck_17857_ = !lean_is_exclusive(v_v_17830_);
if (v_isSharedCheck_17857_ == 0)
{
v___x_17840_ = v_v_17830_;
v_isShared_17841_ = v_isSharedCheck_17857_;
goto v_resetjp_17839_;
}
else
{
lean_dec(v_v_17830_);
v___x_17840_ = lean_box(0);
v_isShared_17841_ = v_isSharedCheck_17857_;
goto v_resetjp_17839_;
}
v_resetjp_17839_:
{
float v___x_17842_; float v___x_17843_; float v___x_17844_; float v___x_17845_; float v___x_17846_; float v___x_17847_; float v___x_17848_; float v___x_17849_; lean_object* v___x_17851_; 
v___x_17842_ = lean_float32_mul(v_a0_17820_, v___y_17834_);
v___x_17843_ = lean_float32_add(v_s0_17835_, v___x_17842_);
v___x_17844_ = lean_float32_mul(v_a1_17821_, v___y_17834_);
v___x_17845_ = lean_float32_add(v_s1_17836_, v___x_17844_);
v___x_17846_ = lean_float32_mul(v_a2_17822_, v___y_17834_);
v___x_17847_ = lean_float32_add(v_s2_17837_, v___x_17846_);
v___x_17848_ = lean_float32_mul(v_a3_17823_, v___y_17834_);
v___x_17849_ = lean_float32_add(v_s3_17838_, v___x_17848_);
if (v_isShared_17841_ == 0)
{
v___x_17851_ = v___x_17840_;
goto v_reusejp_17850_;
}
else
{
lean_object* v_reuseFailAlloc_17856_; 
v_reuseFailAlloc_17856_ = lean_alloc_ctor(0, 0, 16);
v___x_17851_ = v_reuseFailAlloc_17856_;
goto v_reusejp_17850_;
}
v_reusejp_17850_:
{
size_t v___x_17852_; size_t v___x_17853_; lean_object* v___x_17854_; 
lean_ctor_set_float32(v___x_17851_, 0, v___x_17843_);
lean_ctor_set_float32(v___x_17851_, 4, v___x_17845_);
lean_ctor_set_float32(v___x_17851_, 8, v___x_17847_);
lean_ctor_set_float32(v___x_17851_, 12, v___x_17849_);
v___x_17852_ = ((size_t)1ULL);
v___x_17853_ = lean_usize_add(v_i_17827_, v___x_17852_);
v___x_17854_ = lean_array_uset(v_bs_x27_17832_, v_i_17827_, v___x_17851_);
v_i_17827_ = v___x_17853_;
v_bs_17828_ = v___x_17854_;
goto _start;
}
}
}
}
}
}