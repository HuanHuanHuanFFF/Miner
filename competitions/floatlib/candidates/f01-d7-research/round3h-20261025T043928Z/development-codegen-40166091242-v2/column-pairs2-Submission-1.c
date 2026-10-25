LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rseAny(uint64_t v_value_3503_, uint64_t v_shift_3504_){
_start:
{
uint64_t v___x_3505_; uint8_t v___x_3506_; 
v___x_3505_ = 0ULL;
v___x_3506_ = lean_uint64_dec_eq(v_shift_3504_, v___x_3505_);
if (v___x_3506_ == 0)
{
uint64_t v___x_3507_; uint8_t v___x_3508_; 
v___x_3507_ = 64ULL;
v___x_3508_ = lean_uint64_dec_lt(v_shift_3504_, v___x_3507_);
if (v___x_3508_ == 0)
{
uint8_t v___x_3509_; 
v___x_3509_ = lean_uint64_dec_eq(v_shift_3504_, v___x_3507_);
if (v___x_3509_ == 0)
{
return v___x_3505_;
}
else
{
uint64_t v___x_3510_; uint8_t v___x_3511_; 
v___x_3510_ = 9223372036854775808ULL;
v___x_3511_ = lean_uint64_dec_lt(v___x_3510_, v_value_3503_);
if (v___x_3511_ == 0)
{
return v___x_3505_;
}
else
{
uint64_t v___x_3512_; 
v___x_3512_ = 1ULL;
return v___x_3512_;
}
}
}
else
{
uint64_t v_quotient_3513_; uint64_t v___x_3514_; uint64_t v___x_3515_; uint64_t v___x_3516_; uint64_t v_remainder_3517_; uint64_t v___x_3518_; uint64_t v_half_3519_; uint8_t v___x_3520_; 
v_quotient_3513_ = lean_uint64_shift_right(v_value_3503_, v_shift_3504_);
v___x_3514_ = 1ULL;
v___x_3515_ = lean_uint64_shift_left(v___x_3514_, v_shift_3504_);
v___x_3516_ = lean_uint64_sub(v___x_3515_, v___x_3514_);
v_remainder_3517_ = lean_uint64_land(v_value_3503_, v___x_3516_);
v___x_3518_ = lean_uint64_sub(v_shift_3504_, v___x_3514_);
v_half_3519_ = lean_uint64_shift_left(v___x_3514_, v___x_3518_);
v___x_3520_ = lean_uint64_dec_lt(v_remainder_3517_, v_half_3519_);
if (v___x_3520_ == 0)
{
uint8_t v___x_3521_; 
v___x_3521_ = lean_uint64_dec_lt(v_half_3519_, v_remainder_3517_);
if (v___x_3521_ == 0)
{
uint64_t v___x_3522_; uint8_t v___x_3523_; 
v___x_3522_ = lean_uint64_land(v_quotient_3513_, v___x_3514_);
v___x_3523_ = lean_uint64_dec_eq(v___x_3522_, v___x_3505_);
if (v___x_3523_ == 0)
{
uint64_t v___x_3524_; 
v___x_3524_ = lean_uint64_add(v_quotient_3513_, v___x_3514_);
return v___x_3524_;
}
else
{
return v_quotient_3513_;
}
}
else
{
uint64_t v___x_3525_; 
v___x_3525_ = lean_uint64_add(v_quotient_3513_, v___x_3514_);
return v___x_3525_;
}
}
else
{
return v_quotient_3513_;
}
}
}
else
{
return v_value_3503_;
}
}
}