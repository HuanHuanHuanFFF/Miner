LEAN_EXPORT lean_object* lp_competition_Submission_R15ThinPairs_loop(lean_object* v_n_13785_, lean_object* v_baseA_13786_, lean_object* v_baseB_13787_, lean_object* v_p_13788_, lean_object* v_A_13789_, lean_object* v_B_13790_, lean_object* v_k_13791_, float v_s0_13792_, float v_s1_13793_){
_start:
{
float v___y_13795_; float v___y_13796_; lean_object* v___y_13797_; float v___y_13798_; lean_object* v___y_13806_; float v___y_13807_; float v___y_13808_; float v___y_13809_; uint32_t v___y_13818_; uint8_t v___x_13827_; 
v___x_13827_ = lean_nat_dec_lt(v_k_13791_, v_n_13785_);
if (v___x_13827_ == 0)
{
lean_object* v___x_13828_; 
lean_dec(v_k_13791_);
v___x_13828_ = lean_alloc_ctor(0, 0, 8);
lean_ctor_set_float32(v___x_13828_, 0, v_s0_13792_);
lean_ctor_set_float32(v___x_13828_, 4, v_s1_13793_);
return v___x_13828_;
}
else
{
lean_object* v___x_13829_; lean_object* v___x_13830_; uint8_t v___x_13831_; 
v___x_13829_ = lean_nat_add(v_baseA_13786_, v_k_13791_);
v___x_13830_ = lean_array_get_size(v_A_13789_);
v___x_13831_ = lean_nat_dec_lt(v___x_13829_, v___x_13830_);
if (v___x_13831_ == 0)
{
uint32_t v___x_13832_; 
lean_dec(v___x_13829_);
v___x_13832_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_13818_ = v___x_13832_;
goto v___jp_13817_;
}
else
{
lean_object* v___x_13833_; uint32_t v___x_13834_; 
v___x_13833_ = lean_array_fget_borrowed(v_A_13789_, v___x_13829_);
lean_dec(v___x_13829_);
v___x_13834_ = lean_unbox_uint32(v___x_13833_);
v___y_13818_ = v___x_13834_;
goto v___jp_13817_;
}
}
v___jp_13794_:
{
lean_object* v___x_13799_; float v___x_13800_; float v___x_13801_; float v___x_13802_; float v___x_13803_; 
v___x_13799_ = lean_nat_add(v_k_13791_, v___y_13797_);
lean_dec(v_k_13791_);
v___x_13800_ = lean_float32_mul(v___y_13796_, v___y_13795_);
v___x_13801_ = lean_float32_add(v_s0_13792_, v___x_13800_);
v___x_13802_ = lean_float32_mul(v___y_13796_, v___y_13798_);
v___x_13803_ = lean_float32_add(v_s1_13793_, v___x_13802_);
v_k_13791_ = v___x_13799_;
v_s0_13792_ = v___x_13801_;
v_s1_13793_ = v___x_13803_;
goto _start;
}
v___jp_13805_:
{
lean_object* v___x_13810_; lean_object* v___x_13811_; lean_object* v___x_13812_; lean_object* v___x_13813_; uint8_t v___x_13814_; 
v___x_13810_ = lean_unsigned_to_nat(1u);
v___x_13811_ = lean_nat_add(v_baseB_13787_, v___x_13810_);
v___x_13812_ = lean_nat_add(v___x_13811_, v___y_13806_);
lean_dec(v___y_13806_);
lean_dec(v___x_13811_);
v___x_13813_ = lean_array_get_size(v_B_13790_);
v___x_13814_ = lean_nat_dec_lt(v___x_13812_, v___x_13813_);
if (v___x_13814_ == 0)
{
lean_dec(v___x_13812_);
v___y_13795_ = v___y_13809_;
v___y_13796_ = v___y_13807_;
v___y_13797_ = v___x_13810_;
v___y_13798_ = v___y_13808_;
goto v___jp_13794_;
}
else
{
lean_object* v___x_13815_; float v___x_13816_; 
v___x_13815_ = lean_array_fget_borrowed(v_B_13790_, v___x_13812_);
lean_dec(v___x_13812_);
v___x_13816_ = lean_unbox_float32(v___x_13815_);
v___y_13795_ = v___y_13809_;
v___y_13796_ = v___y_13807_;
v___y_13797_ = v___x_13810_;
v___y_13798_ = v___x_13816_;
goto v___jp_13794_;
}
}
v___jp_13817_:
{
float v_a_13819_; lean_object* v___x_13820_; lean_object* v___x_13821_; float v___x_13822_; lean_object* v___x_13823_; uint8_t v___x_13824_; 
v_a_13819_ = lean_float32_of_bits(v___y_13818_);
v___x_13820_ = lean_nat_mul(v_k_13791_, v_p_13788_);
v___x_13821_ = lean_nat_add(v_baseB_13787_, v___x_13820_);
v___x_13822_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_13823_ = lean_array_get_size(v_B_13790_);
v___x_13824_ = lean_nat_dec_lt(v___x_13821_, v___x_13823_);
if (v___x_13824_ == 0)
{
lean_dec(v___x_13821_);
v___y_13806_ = v___x_13820_;
v___y_13807_ = v_a_13819_;
v___y_13808_ = v___x_13822_;
v___y_13809_ = v___x_13822_;
goto v___jp_13805_;
}
else
{
lean_object* v___x_13825_; float v___x_13826_; 
v___x_13825_ = lean_array_fget_borrowed(v_B_13790_, v___x_13821_);
lean_dec(v___x_13821_);
v___x_13826_ = lean_unbox_float32(v___x_13825_);
v___y_13806_ = v___x_13820_;
v___y_13807_ = v_a_13819_;
v___y_13808_ = v___x_13822_;
v___y_13809_ = v___x_13826_;
goto v___jp_13805_;
}
}
}
}