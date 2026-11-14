LEAN_EXPORT lean_object* lp_competition_Submission_R21StreamingPair_advance___lam__0(float v_a0_14631_, float v_a1_14632_, lean_object* v_rowB_14633_, lean_object* v_B_14634_, uint32_t v___x_14635_, lean_object* v_i_14636_, lean_object* v_a_14637_, lean_object* v_x_14638_){
_start:
{
uint32_t v___y_14640_; lean_object* v___x_14655_; lean_object* v___x_14656_; uint8_t v___x_14657_; 
v___x_14655_ = lean_nat_add(v_rowB_14633_, v_i_14636_);
v___x_14656_ = lean_array_get_size(v_B_14634_);
v___x_14657_ = lean_nat_dec_lt(v___x_14655_, v___x_14656_);
if (v___x_14657_ == 0)
{
lean_dec(v___x_14655_);
v___y_14640_ = v___x_14635_;
goto v___jp_14639_;
}
else
{
lean_object* v___x_14658_; uint32_t v___x_14659_; 
v___x_14658_ = lean_array_fget_borrowed(v_B_14634_, v___x_14655_);
lean_dec(v___x_14655_);
v___x_14659_ = lean_unbox_uint32(v___x_14658_);
v___y_14640_ = v___x_14659_;
goto v___jp_14639_;
}
v___jp_14639_:
{
float v_s0_14641_; float v_s1_14642_; lean_object* v___x_14644_; uint8_t v_isShared_14645_; uint8_t v_isSharedCheck_14654_; 
v_s0_14641_ = lean_ctor_get_float32(v_a_14637_, 0);
v_s1_14642_ = lean_ctor_get_float32(v_a_14637_, 4);
v_isSharedCheck_14654_ = !lean_is_exclusive(v_a_14637_);
if (v_isSharedCheck_14654_ == 0)
{
v___x_14644_ = v_a_14637_;
v_isShared_14645_ = v_isSharedCheck_14654_;
goto v_resetjp_14643_;
}
else
{
lean_dec(v_a_14637_);
v___x_14644_ = lean_box(0);
v_isShared_14645_ = v_isSharedCheck_14654_;
goto v_resetjp_14643_;
}
v_resetjp_14643_:
{
float v___x_14646_; float v___x_14647_; float v___x_14648_; float v___x_14649_; float v___x_14650_; lean_object* v___x_14652_; 
v___x_14646_ = lean_float32_of_bits(v___y_14640_);
v___x_14647_ = lean_float32_mul(v_a0_14631_, v___x_14646_);
v___x_14648_ = lean_float32_add(v_s0_14641_, v___x_14647_);
v___x_14649_ = lean_float32_mul(v_a1_14632_, v___x_14646_);
v___x_14650_ = lean_float32_add(v_s1_14642_, v___x_14649_);
if (v_isShared_14645_ == 0)
{
v___x_14652_ = v___x_14644_;
goto v_reusejp_14651_;
}
else
{
lean_object* v_reuseFailAlloc_14653_; 
v_reuseFailAlloc_14653_ = lean_alloc_ctor(0, 0, 8);
v___x_14652_ = v_reuseFailAlloc_14653_;
goto v_reusejp_14651_;
}
v_reusejp_14651_:
{
lean_ctor_set_float32(v___x_14652_, 0, v___x_14648_);
lean_ctor_set_float32(v___x_14652_, 4, v___x_14650_);
return v___x_14652_;
}
}
}
}
}
