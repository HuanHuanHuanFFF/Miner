LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapFinIdxMUnsafe_map___at___00Submission_R21StreamingPair_loop_spec__0___redArg(float v_a0_14777_, float v_a1_14778_, lean_object* v_rowB_14779_, lean_object* v_B_14780_, size_t v_sz_14781_, size_t v_i_14782_, lean_object* v_bs_14783_){
_start:
{
uint8_t v___x_14784_; 
v___x_14784_ = lean_usize_dec_lt(v_i_14782_, v_sz_14781_);
if (v___x_14784_ == 0)
{
return v_bs_14783_;
}
else
{
lean_object* v_v_14785_; lean_object* v___x_14786_; lean_object* v_bs_x27_14787_; uint32_t v___y_14789_; lean_object* v___x_14808_; lean_object* v___x_14809_; lean_object* v___x_14810_; uint8_t v___x_14811_; 
v_v_14785_ = lean_array_uget(v_bs_14783_, v_i_14782_);
v___x_14786_ = lean_unsigned_to_nat(0u);
v_bs_x27_14787_ = lean_array_uset(v_bs_14783_, v_i_14782_, v___x_14786_);
v___x_14808_ = lean_usize_to_nat(v_i_14782_);
v___x_14809_ = lean_nat_add(v_rowB_14779_, v___x_14808_);
lean_dec(v___x_14808_);
v___x_14810_ = lean_array_get_size(v_B_14780_);
v___x_14811_ = lean_nat_dec_lt(v___x_14809_, v___x_14810_);
if (v___x_14811_ == 0)
{
uint32_t v___x_14812_; 
lean_dec(v___x_14809_);
v___x_14812_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_14789_ = v___x_14812_;
goto v___jp_14788_;
}
else
{
lean_object* v___x_14813_; uint32_t v___x_14814_; 
v___x_14813_ = lean_array_fget_borrowed(v_B_14780_, v___x_14809_);
lean_dec(v___x_14809_);
v___x_14814_ = lean_unbox_uint32(v___x_14813_);
v___y_14789_ = v___x_14814_;
goto v___jp_14788_;
}
v___jp_14788_:
{
float v_s0_14790_; float v_s1_14791_; lean_object* v___x_14793_; uint8_t v_isShared_14794_; uint8_t v_isSharedCheck_14807_; 
v_s0_14790_ = lean_ctor_get_float32(v_v_14785_, 0);
v_s1_14791_ = lean_ctor_get_float32(v_v_14785_, 4);
v_isSharedCheck_14807_ = !lean_is_exclusive(v_v_14785_);
if (v_isSharedCheck_14807_ == 0)
{
v___x_14793_ = v_v_14785_;
v_isShared_14794_ = v_isSharedCheck_14807_;
goto v_resetjp_14792_;
}
else
{
lean_dec(v_v_14785_);
v___x_14793_ = lean_box(0);
v_isShared_14794_ = v_isSharedCheck_14807_;
goto v_resetjp_14792_;
}
v_resetjp_14792_:
{
float v___x_14795_; float v___x_14796_; float v___x_14797_; float v___x_14798_; float v___x_14799_; lean_object* v___x_14801_; 
v___x_14795_ = lean_float32_of_bits(v___y_14789_);
v___x_14796_ = lean_float32_mul(v_a0_14777_, v___x_14795_);
v___x_14797_ = lean_float32_add(v_s0_14790_, v___x_14796_);
v___x_14798_ = lean_float32_mul(v_a1_14778_, v___x_14795_);
v___x_14799_ = lean_float32_add(v_s1_14791_, v___x_14798_);
if (v_isShared_14794_ == 0)
{
v___x_14801_ = v___x_14793_;
goto v_reusejp_14800_;
}
else
{
lean_object* v_reuseFailAlloc_14806_; 
v_reuseFailAlloc_14806_ = lean_alloc_ctor(0, 0, 8);
v___x_14801_ = v_reuseFailAlloc_14806_;
goto v_reusejp_14800_;
}
v_reusejp_14800_:
{
size_t v___x_14802_; size_t v___x_14803_; lean_object* v___x_14804_; 
lean_ctor_set_float32(v___x_14801_, 0, v___x_14797_);
lean_ctor_set_float32(v___x_14801_, 4, v___x_14799_);
v___x_14802_ = ((size_t)1ULL);
v___x_14803_ = lean_usize_add(v_i_14782_, v___x_14802_);
v___x_14804_ = lean_array_uset(v_bs_x27_14787_, v_i_14782_, v___x_14801_);
v_i_14782_ = v___x_14803_;
v_bs_14783_ = v___x_14804_;
goto _start;
}
}
}
}
}
}