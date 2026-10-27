LEAN_EXPORT uint32_t lp_competition_Submission_R14ExponentShift_core(uint32_t v_u_7046_, uint32_t v_v_7047_){
_start:
{
uint32_t v___x_7048_; uint32_t v___y_7050_; uint32_t v___y_7051_; uint32_t v___y_7052_; uint32_t v___y_7053_; uint32_t v___y_7054_; uint32_t v___x_7060_; uint32_t v___x_7061_; uint32_t v___x_7062_; float v___x_7063_; uint32_t v___x_7064_; uint32_t v___x_7065_; float v___x_7066_; float v___x_7067_; uint32_t v_mid_7068_; uint8_t v___y_7070_; uint8_t v___y_7089_; uint32_t v___x_7091_; uint8_t v___x_7092_; uint8_t v___x_7093_; 
v___x_7048_ = 8388607;
v___x_7060_ = lean_uint32_land(v_u_7046_, v___x_7048_);
v___x_7061_ = 8388608;
v___x_7062_ = lean_uint32_lor(v___x_7060_, v___x_7061_);
v___x_7063_ = lean_uint32_to_float32(v___x_7062_);
v___x_7064_ = lean_uint32_land(v_v_7047_, v___x_7048_);
v___x_7065_ = lean_uint32_lor(v___x_7064_, v___x_7061_);
v___x_7066_ = lean_uint32_to_float32(v___x_7065_);
v___x_7067_ = lean_float32_mul(v___x_7063_, v___x_7066_);
v_mid_7068_ = lean_float32_to_bits(v___x_7067_);
v___x_7091_ = 2147483648;
v___x_7092_ = lean_uint32_dec_le(v___x_7091_, v_u_7046_);
v___x_7093_ = lean_uint32_dec_le(v___x_7091_, v_v_7047_);
if (v___x_7092_ == 0)
{
if (v___x_7093_ == 0)
{
goto v___jp_7086_;
}
else
{
v___y_7089_ = v___x_7092_;
goto v___jp_7088_;
}
}
else
{
v___y_7089_ = v___x_7093_;
goto v___jp_7088_;
}
v___jp_7049_:
{
uint32_t v___x_7055_; uint32_t v___x_7056_; uint32_t v___x_7057_; uint32_t v___x_7058_; uint32_t v___x_7059_; 
v___x_7055_ = lean_uint32_land(v___y_7051_, v___y_7053_);
v___x_7056_ = lean_uint32_shift_left(v___x_7055_, v___y_7050_);
v___x_7057_ = lean_uint32_lor(v___y_7054_, v___x_7056_);
v___x_7058_ = lean_uint32_land(v___y_7052_, v___x_7048_);
v___x_7059_ = lean_uint32_lor(v___x_7057_, v___x_7058_);
return v___x_7059_;
}
v___jp_7069_:
{
uint32_t v___x_7071_; uint32_t v___x_7072_; uint32_t v___x_7073_; uint32_t v___x_7074_; uint32_t v___x_7075_; uint32_t v___x_7076_; uint32_t v___x_7077_; uint32_t v___x_7078_; uint32_t v___x_7079_; uint32_t v___x_7080_; uint32_t v___x_7081_; uint32_t v___x_7082_; uint32_t v___x_7083_; 
v___x_7071_ = 23;
v___x_7072_ = lean_uint32_shift_right(v_mid_7068_, v___x_7071_);
v___x_7073_ = 255;
v___x_7074_ = lean_uint32_land(v___x_7072_, v___x_7073_);
v___x_7075_ = lean_uint32_shift_right(v_u_7046_, v___x_7071_);
v___x_7076_ = lean_uint32_land(v___x_7075_, v___x_7073_);
v___x_7077_ = lean_uint32_add(v___x_7074_, v___x_7076_);
v___x_7078_ = lean_uint32_shift_right(v_v_7047_, v___x_7071_);
v___x_7079_ = lean_uint32_land(v___x_7078_, v___x_7073_);
v___x_7080_ = lean_uint32_add(v___x_7077_, v___x_7079_);
v___x_7081_ = 300;
v___x_7082_ = lean_uint32_sub(v___x_7080_, v___x_7081_);
v___x_7083_ = lean_uint32_land(v_mid_7068_, v___x_7048_);
if (v___y_7070_ == 0)
{
uint32_t v___x_7084_; 
v___x_7084_ = 0;
v___y_7050_ = v___x_7071_;
v___y_7051_ = v___x_7082_;
v___y_7052_ = v___x_7083_;
v___y_7053_ = v___x_7073_;
v___y_7054_ = v___x_7084_;
goto v___jp_7049_;
}
else
{
uint32_t v___x_7085_; 
v___x_7085_ = 2147483648;
v___y_7050_ = v___x_7071_;
v___y_7051_ = v___x_7082_;
v___y_7052_ = v___x_7083_;
v___y_7053_ = v___x_7073_;
v___y_7054_ = v___x_7085_;
goto v___jp_7049_;
}
}
v___jp_7086_:
{
uint8_t v___x_7087_; 
v___x_7087_ = 0;
v___y_7070_ = v___x_7087_;
goto v___jp_7069_;
}
v___jp_7088_:
{
if (v___y_7089_ == 0)
{
uint8_t v___x_7090_; 
v___x_7090_ = 1;
v___y_7070_ = v___x_7090_;
goto v___jp_7069_;
}
else
{
goto v___jp_7086_;
}
}
}
}
