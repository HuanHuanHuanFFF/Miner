LEAN_EXPORT float lp_competition_R2W01b_convert(uint32_t v_u_3317_){
_start:
{
uint8_t v___y_3319_; uint32_t v___x_3333_; uint32_t v_a_3334_; uint32_t v___x_3335_; uint32_t v___x_3336_; uint32_t v___x_3337_; uint8_t v___x_3338_; 
v___x_3333_ = 2147483647;
v_a_3334_ = lean_uint32_land(v_u_3317_, v___x_3333_);
v___x_3335_ = 201326591;
v___x_3336_ = 1;
v___x_3337_ = lean_uint32_sub(v_a_3334_, v___x_3336_);
v___x_3338_ = lean_uint32_dec_le(v___x_3335_, v___x_3337_);
if (v___x_3338_ == 0)
{
v___y_3319_ = v___x_3338_;
goto v___jp_3318_;
}
else
{
uint32_t v___x_3339_; uint8_t v___x_3340_; 
v___x_3339_ = 2139095040;
v___x_3340_ = lean_uint32_dec_lt(v_a_3334_, v___x_3339_);
v___y_3319_ = v___x_3340_;
goto v___jp_3318_;
}
v___jp_3318_:
{
if (v___y_3319_ == 0)
{
float v___x_3320_; 
v___x_3320_ = lean_float32_of_bits(v_u_3317_);
return v___x_3320_;
}
else
{
uint32_t v___x_3321_; uint32_t v___x_3322_; uint32_t v___x_3323_; uint32_t v___x_3324_; float v___x_3325_; lean_object* v___x_3326_; uint32_t v___x_3327_; uint32_t v___x_3328_; lean_object* v___x_3329_; lean_object* v___x_3330_; float v___x_3331_; float v___x_3332_; 
v___x_3321_ = 8388607;
v___x_3322_ = lean_uint32_land(v_u_3317_, v___x_3321_);
v___x_3323_ = 8388608;
v___x_3324_ = lean_uint32_lor(v___x_3322_, v___x_3323_);
v___x_3325_ = lean_uint32_to_float32(v___x_3324_);
v___x_3326_ = lp_competition_R2W01b_scaleTable;
v___x_3327_ = 23;
v___x_3328_ = lean_uint32_shift_right(v_u_3317_, v___x_3327_);
v___x_3329_ = lean_uint32_to_nat(v___x_3328_);
v___x_3330_ = lean_array_fget_borrowed(v___x_3326_, v___x_3329_);
lean_dec(v___x_3329_);
v___x_3331_ = lean_unbox_float32(v___x_3330_);
v___x_3332_ = lean_float32_mul(v___x_3325_, v___x_3331_);
return v___x_3332_;
}
}
}
}