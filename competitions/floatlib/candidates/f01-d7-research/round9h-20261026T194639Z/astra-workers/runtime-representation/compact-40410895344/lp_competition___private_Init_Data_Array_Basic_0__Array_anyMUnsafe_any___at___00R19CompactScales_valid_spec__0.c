LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R19CompactScales_valid_spec__0(lean_object* v_as_3417_, size_t v_i_3418_, size_t v_stop_3419_){
_start:
{
uint8_t v___x_3420_; 
v___x_3420_ = lean_usize_dec_eq(v_i_3418_, v_stop_3419_);
if (v___x_3420_ == 0)
{
uint8_t v___x_3421_; lean_object* v___x_3422_; float v___x_3423_; double v___x_3424_; float v___x_3425_; uint32_t v___x_3426_; float v___x_3427_; uint32_t v___x_3428_; uint8_t v___x_3429_; 
v___x_3421_ = 1;
v___x_3422_ = lean_array_uget_borrowed(v_as_3417_, v_i_3418_);
v___x_3423_ = lean_unbox_float32(v___x_3422_);
v___x_3424_ = lean_float32_to_float(v___x_3423_);
v___x_3425_ = lean_float_to_float32(v___x_3424_);
v___x_3426_ = lean_float32_to_bits(v___x_3425_);
v___x_3427_ = lean_unbox_float32(v___x_3422_);
v___x_3428_ = lean_float32_to_bits(v___x_3427_);
v___x_3429_ = lean_uint32_dec_eq(v___x_3426_, v___x_3428_);
if (v___x_3429_ == 0)
{
return v___x_3421_;
}
else
{
if (v___x_3420_ == 0)
{
size_t v___x_3430_; size_t v___x_3431_; 
v___x_3430_ = ((size_t)1ULL);
v___x_3431_ = lean_usize_add(v_i_3418_, v___x_3430_);
v_i_3418_ = v___x_3431_;
goto _start;
}
else
{
return v___x_3421_;
}
}
}
else
{
uint8_t v___x_3433_; 
v___x_3433_ = 0;
return v___x_3433_;
}
}
}
