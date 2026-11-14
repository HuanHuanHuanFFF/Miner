LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__1(lean_object* v_a_8592_, lean_object* v_as_8593_, size_t v_sz_8594_, size_t v_i_8595_, lean_object* v_b_8596_)
{
_start:
{
uint8_t v___x_8597_; 
v___x_8597_ = lean_usize_dec_lt(v_i_8595_, v_sz_8594_);
if (v___x_8597_ == 0)
{
lean_dec_ref(v_a_8592_);
return v_b_8596_;
}
else
{
lean_object* v_a_8598_; uint32_t v___x_8599_; lean_object* v___x_8600_; lean_object* v___x_8601_; size_t v___x_8602_; size_t v___x_8603_; 
v_a_8598_ = lean_array_uget_borrowed(v_as_8593_, v_i_8595_);
lean_inc(v_a_8598_);
lean_inc_ref(v_a_8592_);
v___x_8599_ = lp_competition_Submission_R24DotProbe_exactPrepared(v_a_8592_, v_a_8598_);
v___x_8600_ = lean_box_uint32(v___x_8599_);
v___x_8601_ = lean_array_push(v_b_8596_, v___x_8600_);
v___x_8602_ = ((size_t)1ULL);
v___x_8603_ = lean_usize_add(v_i_8595_, v___x_8602_);
v_i_8595_ = v___x_8603_;
v_b_8596_ = v___x_8601_;
goto _start;
}
}
}

LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__2(lean_object* v___x_8613_, lean_object* v_as_8614_, size_t v_sz_8615_, size_t v_i_8616_, lean_object* v_b_8617_)
{
_start:
{
uint8_t v___x_8618_; 
v___x_8618_ = lean_usize_dec_lt(v_i_8616_, v_sz_8615_);
if (v___x_8618_ == 0)
{
return v_b_8617_;
}
else
{
lean_object* v_a_8619_; size_t v_sz_8620_; size_t v___x_8621_; lean_object* v___x_8622_; size_t v___x_8623_; size_t v___x_8624_; 
v_a_8619_ = lean_array_uget_borrowed(v_as_8614_, v_i_8616_);
v_sz_8620_ = lean_array_size(v___x_8613_);
v___x_8621_ = ((size_t)0ULL);
lean_inc(v_a_8619_);
v___x_8622_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__1(v_a_8619_, v___x_8613_, v_sz_8620_, v___x_8621_, v_b_8617_);
v___x_8623_ = ((size_t)1ULL);
v___x_8624_ = lean_usize_add(v_i_8616_, v___x_8623_);
v_i_8616_ = v___x_8624_;
v_b_8617_ = v___x_8622_;
goto _start;
}
}
}

LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0(lean_object* v_as_8634_, size_t v_sz_8635_, size_t v_i_8636_, lean_object* v_b_8637_)
{
_start:
{
uint8_t v___x_8638_; 
v___x_8638_ = lean_usize_dec_lt(v_i_8636_, v_sz_8635_);
if (v___x_8638_ == 0)
{
return v_b_8637_;
}
else
{
lean_object* v_a_8639_; lean_object* v___x_8640_; lean_object* v___x_8641_; size_t v___x_8642_; size_t v___x_8643_; 
v_a_8639_ = lean_array_uget_borrowed(v_as_8634_, v_i_8636_);
lean_inc(v_a_8639_);
v___x_8640_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_a_8639_);
v___x_8641_ = lean_array_push(v_b_8637_, v___x_8640_);
v___x_8642_ = ((size_t)1ULL);
v___x_8643_ = lean_usize_add(v_i_8636_, v___x_8642_);
v_i_8636_ = v___x_8643_;
v_b_8637_ = v___x_8641_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_exactBank(lean_object* v_rowsA_8652_, lean_object* v_rowsB_8653_)
{
_start:
{
lean_object* v___x_8654_; lean_object* v_a_8655_; size_t v_sz_8656_; size_t v___x_8657_; lean_object* v___x_8658_; lean_object* v___x_8659_; lean_object* v___x_8660_; size_t v_sz_8661_; lean_object* v___x_8662_; lean_object* v___x_8663_; lean_object* v___x_8664_; size_t v_sz_8665_; lean_object* v___x_8666_; 
v___x_8654_ = lean_array_get_size(v_rowsA_8652_);
v_a_8655_ = lean_mk_empty_array_with_capacity(v___x_8654_);
v_sz_8656_ = lean_array_size(v_rowsA_8652_);
v___x_8657_ = ((size_t)0ULL);
v___x_8658_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0(v_rowsA_8652_, v_sz_8656_, v___x_8657_, v_a_8655_);
v___x_8659_ = lean_array_get_size(v_rowsB_8653_);
v___x_8660_ = lean_mk_empty_array_with_capacity(v___x_8659_);
v_sz_8661_ = lean_array_size(v_rowsB_8653_);
v___x_8662_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0(v_rowsB_8653_, v_sz_8661_, v___x_8657_, v___x_8660_);
v___x_8663_ = lean_nat_mul(v___x_8654_, v___x_8659_);
v___x_8664_ = lean_mk_empty_array_with_capacity(v___x_8663_);
lean_dec(v___x_8663_);
v_sz_8665_ = lean_array_size(v___x_8658_);
v___x_8666_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__2(v___x_8662_, v___x_8658_, v_sz_8665_, v___x_8657_, v___x_8664_);
lean_dec_ref(v___x_8658_);
lean_dec_ref(v___x_8662_);
return v___x_8666_;
}
}
