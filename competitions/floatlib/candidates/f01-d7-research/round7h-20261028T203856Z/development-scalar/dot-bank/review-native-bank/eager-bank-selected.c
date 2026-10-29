LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0(lean_object* v_as_8670_, size_t v_sz_8671_, size_t v_i_8672_, lean_object* v_b_8673_)
{
_start:
{
uint8_t v___x_8674_; 
v___x_8674_ = lean_usize_dec_lt(v_i_8672_, v_sz_8671_);
if (v___x_8674_ == 0)
{
return v_b_8673_;
}
else
{
lean_object* v_a_8675_; lean_object* v___x_8676_; lean_object* v___x_8677_; size_t v___x_8678_; size_t v___x_8679_; 
v_a_8675_ = lean_array_uget_borrowed(v_as_8670_, v_i_8672_);
lean_inc(v_a_8675_);
v___x_8676_ = lp_competition_Submission_R24DotProbe_prepareEagerOperand(v_a_8675_);
v___x_8677_ = lean_array_push(v_b_8673_, v___x_8676_);
v___x_8678_ = ((size_t)1ULL);
v___x_8679_ = lean_usize_add(v_i_8672_, v___x_8678_);
v_i_8672_ = v___x_8679_;
v_b_8673_ = v___x_8677_;
goto _start;
}
}
}

LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__1(lean_object* v_a_8688_, lean_object* v_as_8689_, size_t v_sz_8690_, size_t v_i_8691_, lean_object* v_b_8692_)
{
_start:
{
uint8_t v___x_8693_; 
v___x_8693_ = lean_usize_dec_lt(v_i_8691_, v_sz_8690_);
if (v___x_8693_ == 0)
{
lean_dec_ref(v_a_8688_);
return v_b_8692_;
}
else
{
lean_object* v_a_8694_; uint32_t v___x_8695_; lean_object* v___x_8696_; lean_object* v___x_8697_; size_t v___x_8698_; size_t v___x_8699_; 
v_a_8694_ = lean_array_uget_borrowed(v_as_8689_, v_i_8691_);
lean_inc(v_a_8694_);
lean_inc_ref(v_a_8688_);
v___x_8695_ = lp_competition_Submission_R24DotProbe_eagerPrepared(v_a_8688_, v_a_8694_);
v___x_8696_ = lean_box_uint32(v___x_8695_);
v___x_8697_ = lean_array_push(v_b_8692_, v___x_8696_);
v___x_8698_ = ((size_t)1ULL);
v___x_8699_ = lean_usize_add(v_i_8691_, v___x_8698_);
v_i_8691_ = v___x_8699_;
v_b_8692_ = v___x_8697_;
goto _start;
}
}
}

LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__2(lean_object* v___x_8709_, lean_object* v_as_8710_, size_t v_sz_8711_, size_t v_i_8712_, lean_object* v_b_8713_)
{
_start:
{
uint8_t v___x_8714_; 
v___x_8714_ = lean_usize_dec_lt(v_i_8712_, v_sz_8711_);
if (v___x_8714_ == 0)
{
return v_b_8713_;
}
else
{
lean_object* v_a_8715_; size_t v_sz_8716_; size_t v___x_8717_; lean_object* v___x_8718_; size_t v___x_8719_; size_t v___x_8720_; 
v_a_8715_ = lean_array_uget_borrowed(v_as_8710_, v_i_8712_);
v_sz_8716_ = lean_array_size(v___x_8709_);
v___x_8717_ = ((size_t)0ULL);
lean_inc(v_a_8715_);
v___x_8718_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__1(v_a_8715_, v___x_8709_, v_sz_8716_, v___x_8717_, v_b_8713_);
v___x_8719_ = ((size_t)1ULL);
v___x_8720_ = lean_usize_add(v_i_8712_, v___x_8719_);
v_i_8712_ = v___x_8720_;
v_b_8713_ = v___x_8718_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_eagerBank(lean_object* v_rowsA_8730_, lean_object* v_rowsB_8731_)
{
_start:
{
lean_object* v___x_8732_; lean_object* v_a_8733_; size_t v_sz_8734_; size_t v___x_8735_; lean_object* v___x_8736_; lean_object* v___x_8737_; lean_object* v___x_8738_; size_t v_sz_8739_; lean_object* v___x_8740_; lean_object* v___x_8741_; lean_object* v___x_8742_; size_t v_sz_8743_; lean_object* v___x_8744_; 
v___x_8732_ = lean_array_get_size(v_rowsA_8730_);
v_a_8733_ = lean_mk_empty_array_with_capacity(v___x_8732_);
v_sz_8734_ = lean_array_size(v_rowsA_8730_);
v___x_8735_ = ((size_t)0ULL);
v___x_8736_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0(v_rowsA_8730_, v_sz_8734_, v___x_8735_, v_a_8733_);
v___x_8737_ = lean_array_get_size(v_rowsB_8731_);
v___x_8738_ = lean_mk_empty_array_with_capacity(v___x_8737_);
v_sz_8739_ = lean_array_size(v_rowsB_8731_);
v___x_8740_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0(v_rowsB_8731_, v_sz_8739_, v___x_8735_, v___x_8738_);
v___x_8741_ = lean_nat_mul(v___x_8732_, v___x_8737_);
v___x_8742_ = lean_mk_empty_array_with_capacity(v___x_8741_);
lean_dec(v___x_8741_);
v_sz_8743_ = lean_array_size(v___x_8736_);
v___x_8744_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__2(v___x_8740_, v___x_8736_, v_sz_8743_, v___x_8735_, v___x_8742_);
lean_dec_ref(v___x_8736_);
lean_dec_ref(v___x_8740_);
return v___x_8744_;
}
}
