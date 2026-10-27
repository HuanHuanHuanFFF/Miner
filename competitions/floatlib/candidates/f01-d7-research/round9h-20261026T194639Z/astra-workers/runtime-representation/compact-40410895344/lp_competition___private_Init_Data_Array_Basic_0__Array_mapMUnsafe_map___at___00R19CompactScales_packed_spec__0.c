LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R19CompactScales_packed_spec__0(size_t v_sz_3369_, size_t v_i_3370_, lean_object* v_bs_3371_){
_start:
{
uint8_t v___x_3372_; 
v___x_3372_ = lean_usize_dec_lt(v_i_3370_, v_sz_3369_);
if (v___x_3372_ == 0)
{
return v_bs_3371_;
}
else
{
lean_object* v_v_3373_; lean_object* v___x_3374_; lean_object* v_bs_x27_3375_; float v___x_3376_; double v___x_3377_; size_t v___x_3378_; size_t v___x_3379_; lean_object* v___x_3380_; lean_object* v___x_3381_; 
v_v_3373_ = lean_array_uget(v_bs_3371_, v_i_3370_);
v___x_3374_ = lean_unsigned_to_nat(0u);
v_bs_x27_3375_ = lean_array_uset(v_bs_3371_, v_i_3370_, v___x_3374_);
v___x_3376_ = lean_unbox_float32(v_v_3373_);
lean_dec(v_v_3373_);
v___x_3377_ = lean_float32_to_float(v___x_3376_);
v___x_3378_ = ((size_t)1ULL);
v___x_3379_ = lean_usize_add(v_i_3370_, v___x_3378_);
v___x_3380_ = lean_box_float(v___x_3377_);
v___x_3381_ = lean_array_uset(v_bs_x27_3375_, v_i_3370_, v___x_3380_);
v_i_3370_ = v___x_3379_;
v_bs_3371_ = v___x_3381_;
goto _start;
}
}
}
