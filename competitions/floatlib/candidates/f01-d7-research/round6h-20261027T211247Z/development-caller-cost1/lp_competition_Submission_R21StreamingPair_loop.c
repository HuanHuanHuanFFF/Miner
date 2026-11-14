LEAN_EXPORT lean_object* lp_competition_Submission_R21StreamingPair_loop(lean_object* v_p_14827_, lean_object* v_n_14828_, lean_object* v_baseA0_14829_, lean_object* v_baseA1_14830_, lean_object* v_baseB_14831_, lean_object* v_A_14832_, lean_object* v_B_14833_, lean_object* v_k_14834_, lean_object* v_s_14835_){
_start:
{
uint8_t v___x_14836_; 
v___x_14836_ = lean_nat_dec_lt(v_k_14834_, v_n_14828_);
if (v___x_14836_ == 0)
{
lean_dec(v_k_14834_);
return v_s_14835_;
}
else
{
lean_object* v___x_14837_; lean_object* v___x_14838_; float v___y_14840_; uint32_t v___y_14841_; lean_object* v___x_14849_; uint32_t v___x_14850_; uint32_t v___y_14852_; lean_object* v___x_14859_; uint8_t v___x_14860_; 
v___x_14837_ = lean_unsigned_to_nat(1u);
v___x_14838_ = lean_nat_add(v_k_14834_, v___x_14837_);
v___x_14849_ = lean_nat_add(v_baseA0_14829_, v_k_14834_);
v___x_14850_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_14859_ = lean_array_get_size(v_A_14832_);
v___x_14860_ = lean_nat_dec_lt(v___x_14849_, v___x_14859_);
if (v___x_14860_ == 0)
{
lean_dec(v___x_14849_);
v___y_14852_ = v___x_14850_;
goto v___jp_14851_;
}
else
{
lean_object* v___x_14861_; uint32_t v___x_14862_; 
v___x_14861_ = lean_array_fget_borrowed(v_A_14832_, v___x_14849_);
lean_dec(v___x_14849_);
v___x_14862_ = lean_unbox_uint32(v___x_14861_);
v___y_14852_ = v___x_14862_;
goto v___jp_14851_;
}
v___jp_14839_:
{
float v_a1_14842_; lean_object* v___x_14843_; lean_object* v_rowB_14844_; size_t v_sz_14845_; size_t v___x_14846_; lean_object* v___x_14847_; 
v_a1_14842_ = lean_float32_of_bits(v___y_14841_);
v___x_14843_ = lean_nat_mul(v_k_14834_, v_p_14827_);
lean_dec(v_k_14834_);
v_rowB_14844_ = lean_nat_add(v_baseB_14831_, v___x_14843_);
lean_dec(v___x_14843_);
v_sz_14845_ = lean_array_size(v_s_14835_);
v___x_14846_ = ((size_t)0ULL);
v___x_14847_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapFinIdxMUnsafe_map___at___00Submission_R21StreamingPair_loop_spec__0___redArg(v___y_14840_, v_a1_14842_, v_rowB_14844_, v_B_14833_, v_sz_14845_, v___x_14846_, v_s_14835_);
lean_dec(v_rowB_14844_);
v_k_14834_ = v___x_14838_;
v_s_14835_ = v___x_14847_;
goto _start;
}
v___jp_14851_:
{
float v_a0_14853_; lean_object* v___x_14854_; lean_object* v___x_14855_; uint8_t v___x_14856_; 
v_a0_14853_ = lean_float32_of_bits(v___y_14852_);
v___x_14854_ = lean_nat_add(v_baseA1_14830_, v_k_14834_);
v___x_14855_ = lean_array_get_size(v_A_14832_);
v___x_14856_ = lean_nat_dec_lt(v___x_14854_, v___x_14855_);
if (v___x_14856_ == 0)
{
lean_dec(v___x_14854_);
v___y_14840_ = v_a0_14853_;
v___y_14841_ = v___x_14850_;
goto v___jp_14839_;
}
else
{
lean_object* v___x_14857_; uint32_t v___x_14858_; 
v___x_14857_ = lean_array_fget_borrowed(v_A_14832_, v___x_14854_);
lean_dec(v___x_14854_);
v___x_14858_ = lean_unbox_uint32(v___x_14857_);
v___y_14840_ = v_a0_14853_;
v___y_14841_ = v___x_14858_;
goto v___jp_14839_;
}
}
}
}
}