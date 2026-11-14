LEAN_EXPORT uint32_t lp_competition_runOutline___lam__1(uint32_t v___y_4033_, uint32_t v___y_4034_){
_start:
{
uint32_t v___x_4035_; uint32_t v___x_4036_; uint32_t v___x_4037_; uint32_t v_eu_4038_; uint32_t v___x_4039_; uint32_t v___x_4040_; uint32_t v___x_4041_; uint8_t v___x_4042_; 
v___x_4035_ = 23;
v___x_4036_ = lean_uint32_shift_right(v___y_4033_, v___x_4035_);
v___x_4037_ = 255;
v_eu_4038_ = lean_uint32_land(v___x_4036_, v___x_4037_);
v___x_4039_ = 1;
v___x_4040_ = lean_uint32_sub(v_eu_4038_, v___x_4039_);
v___x_4041_ = 253;
v___x_4042_ = lean_uint32_dec_le(v___x_4040_, v___x_4041_);
if (v___x_4042_ == 0)
{
uint32_t v___x_4043_; 
v___x_4043_ = lp_competition_Submission_R22OutlineMul_retainedMul(v___y_4033_, v___y_4034_);
return v___x_4043_;
}
else
{
uint32_t v___x_4044_; uint32_t v_ev_4045_; uint32_t v___x_4046_; uint8_t v___x_4047_; 
v___x_4044_ = lean_uint32_shift_right(v___y_4034_, v___x_4035_);
v_ev_4045_ = lean_uint32_land(v___x_4044_, v___x_4037_);
v___x_4046_ = lean_uint32_sub(v_ev_4045_, v___x_4039_);
v___x_4047_ = lean_uint32_dec_le(v___x_4046_, v___x_4041_);
if (v___x_4047_ == 0)
{
uint32_t v___x_4048_; 
v___x_4048_ = lp_competition_Submission_R22OutlineMul_retainedMul(v___y_4033_, v___y_4034_);
return v___x_4048_;
}
else
{
uint32_t v_s_4049_; uint32_t v___x_4050_; uint32_t v___x_4051_; uint32_t v___x_4052_; uint8_t v___x_4053_; 
v_s_4049_ = lean_uint32_add(v_eu_4038_, v_ev_4045_);
v___x_4050_ = 128;
v___x_4051_ = lean_uint32_sub(v_s_4049_, v___x_4050_);
v___x_4052_ = 252;
v___x_4053_ = lean_uint32_dec_le(v___x_4051_, v___x_4052_);
if (v___x_4053_ == 0)
{
uint32_t v___x_4054_; 
v___x_4054_ = lp_competition_Submission_R22OutlineMul_retainedMul(v___y_4033_, v___y_4034_);
return v___x_4054_;
}
else
{
uint32_t v___x_4055_; uint32_t v___x_4056_; uint32_t v___x_4057_; uint64_t v___y_4059_; uint32_t v_a_4077_; uint32_t v___x_4078_; uint32_t v_b_4079_; uint64_t v___x_4080_; uint64_t v___x_4081_; uint64_t v_p_4082_; uint64_t v___x_4083_; uint8_t v___x_4084_; 
v___x_4055_ = 8388607;
v___x_4056_ = lean_uint32_land(v___y_4033_, v___x_4055_);
v___x_4057_ = 8388608;
v_a_4077_ = lean_uint32_lor(v___x_4056_, v___x_4057_);
v___x_4078_ = lean_uint32_land(v___y_4034_, v___x_4055_);
v_b_4079_ = lean_uint32_lor(v___x_4078_, v___x_4057_);
v___x_4080_ = lean_uint32_to_uint64(v_a_4077_);
v___x_4081_ = lean_uint32_to_uint64(v_b_4079_);
v_p_4082_ = lean_uint64_mul(v___x_4080_, v___x_4081_);
v___x_4083_ = 140737488355328ULL;
v___x_4084_ = lean_uint64_dec_lt(v_p_4082_, v___x_4083_);
if (v___x_4084_ == 0)
{
uint64_t v___x_4085_; uint64_t v___x_4086_; uint64_t v___x_4087_; uint64_t v___x_4088_; uint64_t v___x_4089_; uint64_t v___x_4090_; uint64_t v___x_4091_; 
v___x_4085_ = 8388607ULL;
v___x_4086_ = lean_uint64_add(v_p_4082_, v___x_4085_);
v___x_4087_ = 24ULL;
v___x_4088_ = lean_uint64_shift_right(v_p_4082_, v___x_4087_);
v___x_4089_ = 1ULL;
v___x_4090_ = lean_uint64_land(v___x_4088_, v___x_4089_);
v___x_4091_ = lean_uint64_add(v___x_4086_, v___x_4090_);
v___y_4059_ = v___x_4091_;
goto v___jp_4058_;
}
else
{
uint64_t v___x_4092_; uint64_t v___x_4093_; uint64_t v___x_4094_; uint64_t v___x_4095_; uint64_t v___x_4096_; uint64_t v___x_4097_; uint64_t v___x_4098_; 
v___x_4092_ = 4194303ULL;
v___x_4093_ = lean_uint64_add(v_p_4082_, v___x_4092_);
v___x_4094_ = 23ULL;
v___x_4095_ = lean_uint64_shift_right(v_p_4082_, v___x_4094_);
v___x_4096_ = 1ULL;
v___x_4097_ = lean_uint64_land(v___x_4095_, v___x_4096_);
v___x_4098_ = lean_uint64_add(v___x_4093_, v___x_4097_);
v___y_4059_ = v___x_4098_;
goto v___jp_4058_;
}
v___jp_4058_:
{
uint64_t v___x_4060_; uint64_t v_high_4061_; uint64_t v___x_4062_; uint64_t v___x_4063_; uint64_t v___x_4064_; uint32_t v_q_4065_; uint32_t v___x_4066_; uint32_t v___x_4067_; uint32_t v___x_4068_; uint32_t v_e_4069_; uint32_t v___x_4070_; uint32_t v___x_4071_; uint32_t v___x_4072_; uint32_t v___x_4073_; uint32_t v___x_4074_; uint32_t v___x_4075_; uint32_t v___x_4076_; 
v___x_4060_ = 47ULL;
v_high_4061_ = lean_uint64_shift_right(v___y_4059_, v___x_4060_);
v___x_4062_ = 23ULL;
v___x_4063_ = lean_uint64_add(v___x_4062_, v_high_4061_);
v___x_4064_ = lean_uint64_shift_right(v___y_4059_, v___x_4063_);
v_q_4065_ = lean_uint64_to_uint32(v___x_4064_);
v___x_4066_ = 127;
v___x_4067_ = lean_uint32_sub(v_s_4049_, v___x_4066_);
v___x_4068_ = lean_uint64_to_uint32(v_high_4061_);
v_e_4069_ = lean_uint32_add(v___x_4067_, v___x_4068_);
v___x_4070_ = lean_uint32_xor(v___y_4033_, v___y_4034_);
v___x_4071_ = 2147483648;
v___x_4072_ = lean_uint32_land(v___x_4070_, v___x_4071_);
v___x_4073_ = lean_uint32_shift_left(v_e_4069_, v___x_4035_);
v___x_4074_ = lean_uint32_lor(v___x_4072_, v___x_4073_);
v___x_4075_ = lean_uint32_sub(v_q_4065_, v___x_4057_);
v___x_4076_ = lean_uint32_lor(v___x_4074_, v___x_4075_);
return v___x_4076_;
}
}
}
}
}
}
