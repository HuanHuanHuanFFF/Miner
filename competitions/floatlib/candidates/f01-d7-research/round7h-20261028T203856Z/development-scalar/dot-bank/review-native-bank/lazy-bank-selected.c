LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0(lean_object* v_as_8748_, size_t v_sz_8749_, size_t v_i_8750_, lean_object* v_b_8751_)
{
_start:
{
uint8_t v___x_8752_; 
v___x_8752_ = lean_usize_dec_lt(v_i_8750_, v_sz_8749_);
if (v___x_8752_ == 0)
{
return v_b_8751_;
}
else
{
lean_object* v_a_8753_; lean_object* v___x_8754_; lean_object* v___x_8755_; size_t v___x_8756_; size_t v___x_8757_; 
v_a_8753_ = lean_array_uget_borrowed(v_as_8748_, v_i_8750_);
lean_inc(v_a_8753_);
v___x_8754_ = lp_competition_Submission_R24PortableF64_prepare(v_a_8753_);
v___x_8755_ = lean_array_push(v_b_8751_, v___x_8754_);
v___x_8756_ = ((size_t)1ULL);
v___x_8757_ = lean_usize_add(v_i_8750_, v___x_8756_);
v_i_8750_ = v___x_8757_;
v_b_8751_ = v___x_8755_;
goto _start;
}
}
}

LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__1(lean_object* v_a_8766_, lean_object* v_as_8767_, size_t v_sz_8768_, size_t v_i_8769_, lean_object* v_b_8770_)
{
_start:
{
uint8_t v___x_8771_; 
v___x_8771_ = lean_usize_dec_lt(v_i_8769_, v_sz_8768_);
if (v___x_8771_ == 0)
{
lean_dec_ref(v_a_8766_);
return v_b_8770_;
}
else
{
lean_object* v_a_8772_; uint32_t v___x_8773_; lean_object* v___x_8774_; lean_object* v___x_8775_; size_t v___x_8776_; size_t v___x_8777_; 
v_a_8772_ = lean_array_uget_borrowed(v_as_8767_, v_i_8769_);
lean_inc(v_a_8772_);
lean_inc_ref(v_a_8766_);
v___x_8773_ = lp_competition_Submission_R24DotProbe_lazyPrepared(v_a_8766_, v_a_8772_);
v___x_8774_ = lean_box_uint32(v___x_8773_);
v___x_8775_ = lean_array_push(v_b_8770_, v___x_8774_);
v___x_8776_ = ((size_t)1ULL);
v___x_8777_ = lean_usize_add(v_i_8769_, v___x_8776_);
v_i_8769_ = v___x_8777_;
v_b_8770_ = v___x_8775_;
goto _start;
}
}
}

LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__2(lean_object* v___x_8787_, lean_object* v_as_8788_, size_t v_sz_8789_, size_t v_i_8790_, lean_object* v_b_8791_)
{
_start:
{
uint8_t v___x_8792_; 
v___x_8792_ = lean_usize_dec_lt(v_i_8790_, v_sz_8789_);
if (v___x_8792_ == 0)
{
return v_b_8791_;
}
else
{
lean_object* v_a_8793_; size_t v_sz_8794_; size_t v___x_8795_; lean_object* v___x_8796_; size_t v___x_8797_; size_t v___x_8798_; 
v_a_8793_ = lean_array_uget_borrowed(v_as_8788_, v_i_8790_);
v_sz_8794_ = lean_array_size(v___x_8787_);
v___x_8795_ = ((size_t)0ULL);
lean_inc(v_a_8793_);
v___x_8796_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__1(v_a_8793_, v___x_8787_, v_sz_8794_, v___x_8795_, v_b_8791_);
v___x_8797_ = ((size_t)1ULL);
v___x_8798_ = lean_usize_add(v_i_8790_, v___x_8797_);
v_i_8790_ = v___x_8798_;
v_b_8791_ = v___x_8796_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_lazyBank(lean_object* v_rowsA_8808_, lean_object* v_rowsB_8809_)
{
_start:
{
lean_object* v___x_8810_; lean_object* v_a_8811_; size_t v_sz_8812_; size_t v___x_8813_; lean_object* v___x_8814_; lean_object* v___x_8815_; lean_object* v___x_8816_; size_t v_sz_8817_; lean_object* v___x_8818_; lean_object* v___x_8819_; lean_object* v___x_8820_; size_t v_sz_8821_; lean_object* v___x_8822_; 
v___x_8810_ = lean_array_get_size(v_rowsA_8808_);
v_a_8811_ = lean_mk_empty_array_with_capacity(v___x_8810_);
v_sz_8812_ = lean_array_size(v_rowsA_8808_);
v___x_8813_ = ((size_t)0ULL);
v___x_8814_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0(v_rowsA_8808_, v_sz_8812_, v___x_8813_, v_a_8811_);
v___x_8815_ = lean_array_get_size(v_rowsB_8809_);
v___x_8816_ = lean_mk_empty_array_with_capacity(v___x_8815_);
v_sz_8817_ = lean_array_size(v_rowsB_8809_);
v___x_8818_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0(v_rowsB_8809_, v_sz_8817_, v___x_8813_, v___x_8816_);
v___x_8819_ = lean_nat_mul(v___x_8810_, v___x_8815_);
v___x_8820_ = lean_mk_empty_array_with_capacity(v___x_8819_);
lean_dec(v___x_8819_);
v_sz_8821_ = lean_array_size(v___x_8814_);
v___x_8822_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__2(v___x_8818_, v___x_8814_, v_sz_8821_, v___x_8813_, v___x_8820_);
lean_dec_ref(v___x_8814_);
lean_dec_ref(v___x_8818_);
return v___x_8822_;
}
}
