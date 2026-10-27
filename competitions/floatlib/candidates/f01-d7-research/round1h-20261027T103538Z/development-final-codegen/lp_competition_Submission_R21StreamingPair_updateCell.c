LEAN_EXPORT lean_object* lp_competition_Submission_R21StreamingPair_updateCell(float v_a0_14606_, float v_a1_14607_, float v_b_14608_, lean_object* v_s_14609_){
_start:
{
float v_s0_14610_; float v_s1_14611_; lean_object* v___x_14613_; uint8_t v_isShared_14614_; uint8_t v_isSharedCheck_14622_; 
v_s0_14610_ = lean_ctor_get_float32(v_s_14609_, 0);
v_s1_14611_ = lean_ctor_get_float32(v_s_14609_, 4);
v_isSharedCheck_14622_ = !lean_is_exclusive(v_s_14609_);
if (v_isSharedCheck_14622_ == 0)
{
v___x_14613_ = v_s_14609_;
v_isShared_14614_ = v_isSharedCheck_14622_;
goto v_resetjp_14612_;
}
else
{
lean_dec(v_s_14609_);
v___x_14613_ = lean_box(0);
v_isShared_14614_ = v_isSharedCheck_14622_;
goto v_resetjp_14612_;
}
v_resetjp_14612_:
{
float v___x_14615_; float v___x_14616_; float v___x_14617_; float v___x_14618_; lean_object* v___x_14620_; 
v___x_14615_ = lean_float32_mul(v_a0_14606_, v_b_14608_);
v___x_14616_ = lean_float32_add(v_s0_14610_, v___x_14615_);
v___x_14617_ = lean_float32_mul(v_a1_14607_, v_b_14608_);
v___x_14618_ = lean_float32_add(v_s1_14611_, v___x_14617_);
if (v_isShared_14614_ == 0)
{
v___x_14620_ = v___x_14613_;
goto v_reusejp_14619_;
}
else
{
lean_object* v_reuseFailAlloc_14621_; 
v_reuseFailAlloc_14621_ = lean_alloc_ctor(0, 0, 8);
v___x_14620_ = v_reuseFailAlloc_14621_;
goto v_reusejp_14619_;
}
v_reusejp_14619_:
{
lean_ctor_set_float32(v___x_14620_, 0, v___x_14616_);
lean_ctor_set_float32(v___x_14620_, 4, v___x_14618_);
return v___x_14620_;
}
}
}
}
