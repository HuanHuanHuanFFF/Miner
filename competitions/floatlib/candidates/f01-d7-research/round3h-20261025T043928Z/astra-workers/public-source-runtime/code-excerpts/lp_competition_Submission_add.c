LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t v_x_6101_, uint32_t v_y_6102_){
_start:
{
uint8_t v___y_6110_; uint8_t v___y_6124_; uint8_t v___y_6138_; uint8_t v___y_6155_; float v___y_6162_; float v___y_6163_; float v___y_6177_; uint8_t v___y_6178_; float v___y_6193_; uint8_t v___y_6203_; uint32_t v___x_6217_; uint32_t v_a_6218_; uint32_t v___x_6219_; uint32_t v___x_6220_; uint32_t v___x_6221_; uint8_t v___x_6222_; 
v___x_6217_ = 2147483647;
v_a_6218_ = lean_uint32_land(v_x_6101_, v___x_6217_);
v___x_6219_ = 201326591;
v___x_6220_ = 1;
v___x_6221_ = lean_uint32_sub(v_a_6218_, v___x_6220_);
v___x_6222_ = lean_uint32_dec_le(v___x_6219_, v___x_6221_);
if (v___x_6222_ == 0)
{
v___y_6203_ = v___x_6222_;
goto v___jp_6202_;
}
else
{
uint32_t v___x_6223_; uint8_t v___x_6224_; 
v___x_6223_ = 2139095040;
v___x_6224_ = lean_uint32_dec_lt(v_a_6218_, v___x_6223_);
v___y_6203_ = v___x_6224_;
goto v___jp_6202_;
}
v___jp_6103_:
{
lean_object* v___x_6104_; lean_object* v___x_6105_; lean_object* v___x_6106_; lean_object* v___x_6107_; uint32_t v___x_6108_; 
v___x_6104_ = ((lean_object*)(lp_competition_R7W01_F32___closed__0));
v___x_6105_ = lean_uint32_to_nat(v_x_6101_);
v___x_6106_ = lean_uint32_to_nat(v_y_6102_);
v___x_6107_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(v___x_6104_, v___x_6105_, v___x_6106_);
v___x_6108_ = lean_uint32_of_nat(v___x_6107_);
lean_dec(v___x_6107_);
return v___x_6108_;
}
v___jp_6109_:
{
if (v___y_6110_ == 0)
{
goto v___jp_6103_;
}
else
{
uint32_t v___x_6111_; uint32_t v___x_6112_; 
v___x_6111_ = 4194304;
v___x_6112_ = lean_uint32_lor(v_y_6102_, v___x_6111_);
return v___x_6112_;
}
}
v___jp_6113_:
{
uint32_t v___x_6114_; uint32_t v___x_6115_; uint32_t v___x_6116_; uint32_t v___x_6117_; uint8_t v___x_6118_; 
v___x_6114_ = 23;
v___x_6115_ = lean_uint32_shift_right(v_y_6102_, v___x_6114_);
v___x_6116_ = 255;
v___x_6117_ = lean_uint32_land(v___x_6115_, v___x_6116_);
v___x_6118_ = lean_uint32_dec_eq(v___x_6117_, v___x_6116_);
if (v___x_6118_ == 0)
{
v___y_6110_ = v___x_6118_;
goto v___jp_6109_;
}
else
{
uint32_t v___x_6119_; uint32_t v___x_6120_; uint32_t v___x_6121_; uint8_t v___x_6122_; 
v___x_6119_ = 8388607;
v___x_6120_ = lean_uint32_land(v_y_6102_, v___x_6119_);
v___x_6121_ = 0;
v___x_6122_ = lean_uint32_dec_eq(v___x_6120_, v___x_6121_);
if (v___x_6122_ == 0)
{
v___y_6110_ = v___x_6118_;
goto v___jp_6109_;
}
else
{
goto v___jp_6103_;
}
}
}
v___jp_6123_:
{
if (v___y_6124_ == 0)
{
goto v___jp_6113_;
}
else
{
uint32_t v___x_6125_; uint32_t v___x_6126_; 
v___x_6125_ = 4194304;
v___x_6126_ = lean_uint32_lor(v_x_6101_, v___x_6125_);
return v___x_6126_;
}
}
v___jp_6127_:
{
uint32_t v___x_6128_; uint32_t v___x_6129_; uint32_t v___x_6130_; uint32_t v___x_6131_; uint8_t v___x_6132_; 
v___x_6128_ = 23;
v___x_6129_ = lean_uint32_shift_right(v_x_6101_, v___x_6128_);
v___x_6130_ = 255;
v___x_6131_ = lean_uint32_land(v___x_6129_, v___x_6130_);
v___x_6132_ = lean_uint32_dec_eq(v___x_6131_, v___x_6130_);
if (v___x_6132_ == 0)
{
v___y_6124_ = v___x_6132_;
goto v___jp_6123_;
}
else
{
uint32_t v___x_6133_; uint32_t v___x_6134_; uint32_t v___x_6135_; uint8_t v___x_6136_; 
v___x_6133_ = 8388607;
v___x_6134_ = lean_uint32_land(v_x_6101_, v___x_6133_);
v___x_6135_ = 0;
v___x_6136_ = lean_uint32_dec_eq(v___x_6134_, v___x_6135_);
if (v___x_6136_ == 0)
{
v___y_6124_ = v___x_6132_;
goto v___jp_6123_;
}
else
{
goto v___jp_6113_;
}
}
}
v___jp_6137_:
{
if (v___y_6138_ == 0)
{
goto v___jp_6127_;
}
else
{
uint32_t v___x_6139_; uint32_t v___x_6140_; uint32_t v___x_6141_; uint8_t v___x_6142_; 
v___x_6139_ = 4194304;
v___x_6140_ = lean_uint32_land(v_y_6102_, v___x_6139_);
v___x_6141_ = 0;
v___x_6142_ = lean_uint32_dec_eq(v___x_6140_, v___x_6141_);
if (v___x_6142_ == 0)
{
goto v___jp_6127_;
}
else
{
uint32_t v___x_6143_; 
v___x_6143_ = lean_uint32_lor(v_y_6102_, v___x_6139_);
return v___x_6143_;
}
}
}
v___jp_6144_:
{
uint32_t v___x_6145_; uint32_t v___x_6146_; uint32_t v___x_6147_; uint32_t v___x_6148_; uint8_t v___x_6149_; 
v___x_6145_ = 23;
v___x_6146_ = lean_uint32_shift_right(v_y_6102_, v___x_6145_);
v___x_6147_ = 255;
v___x_6148_ = lean_uint32_land(v___x_6146_, v___x_6147_);
v___x_6149_ = lean_uint32_dec_eq(v___x_6148_, v___x_6147_);
if (v___x_6149_ == 0)
{
v___y_6138_ = v___x_6149_;
goto v___jp_6137_;
}
else
{
uint32_t v___x_6150_; uint32_t v___x_6151_; uint32_t v___x_6152_; uint8_t v___x_6153_; 
v___x_6150_ = 8388607;
v___x_6151_ = lean_uint32_land(v_y_6102_, v___x_6150_);
v___x_6152_ = 0;
v___x_6153_ = lean_uint32_dec_eq(v___x_6151_, v___x_6152_);
if (v___x_6153_ == 0)
{
v___y_6138_ = v___x_6149_;
goto v___jp_6137_;
}
else
{
goto v___jp_6127_;
}
}
}
v___jp_6154_:
{
if (v___y_6155_ == 0)
{
goto v___jp_6144_;
}
else
{
uint32_t v___x_6156_; uint32_t v___x_6157_; uint32_t v___x_6158_; uint8_t v___x_6159_; 
v___x_6156_ = 4194304;
v___x_6157_ = lean_uint32_land(v_x_6101_, v___x_6156_);
v___x_6158_ = 0;
v___x_6159_ = lean_uint32_dec_eq(v___x_6157_, v___x_6158_);
if (v___x_6159_ == 0)
{
goto v___jp_6144_;
}
else
{
uint32_t v___x_6160_; 
v___x_6160_ = lean_uint32_lor(v_x_6101_, v___x_6156_);
return v___x_6160_;
}
}
}
v___jp_6161_:
{
float v_result_6164_; uint8_t v___x_6165_; 
v_result_6164_ = lean_float32_add(v___y_6162_, v___y_6163_);
v___x_6165_ = lean_float32_beq(v_result_6164_, v_result_6164_);
if (v___x_6165_ == 0)
{
uint32_t v___x_6166_; uint32_t v___x_6167_; uint32_t v___x_6168_; uint32_t v___x_6169_; uint8_t v___x_6170_; 
v___x_6166_ = 23;
v___x_6167_ = lean_uint32_shift_right(v_x_6101_, v___x_6166_);
v___x_6168_ = 255;
v___x_6169_ = lean_uint32_land(v___x_6167_, v___x_6168_);
v___x_6170_ = lean_uint32_dec_eq(v___x_6169_, v___x_6168_);
if (v___x_6170_ == 0)
{
v___y_6155_ = v___x_6170_;
goto v___jp_6154_;
}
else
{
uint32_t v___x_6171_; uint32_t v___x_6172_; uint32_t v___x_6173_; uint8_t v___x_6174_; 
v___x_6171_ = 8388607;
v___x_6172_ = lean_uint32_land(v_x_6101_, v___x_6171_);
v___x_6173_ = 0;
v___x_6174_ = lean_uint32_dec_eq(v___x_6172_, v___x_6173_);
if (v___x_6174_ == 0)
{
v___y_6155_ = v___x_6170_;
goto v___jp_6154_;
}
else
{
goto v___jp_6144_;
}
}
}
else
{
uint32_t v___x_6175_; 
v___x_6175_ = lean_float32_to_bits(v_result_6164_);
return v___x_6175_;
}
}
v___jp_6176_:
{
if (v___y_6178_ == 0)
{
float v___x_6179_; 
v___x_6179_ = lean_float32_of_bits(v_y_6102_);
v___y_6162_ = v___y_6177_;
v___y_6163_ = v___x_6179_;
goto v___jp_6161_;
}
else
{
uint32_t v___x_6180_; uint32_t v___x_6181_; uint32_t v___x_6182_; uint32_t v___x_6183_; float v___x_6184_; lean_object* v___x_6185_; uint32_t v___x_6186_; uint32_t v___x_6187_; lean_object* v___x_6188_; lean_object* v___x_6189_; float v___x_6190_; float v___x_6191_; 
v___x_6180_ = 8388607;
v___x_6181_ = lean_uint32_land(v_y_6102_, v___x_6180_);
v___x_6182_ = 8388608;
v___x_6183_ = lean_uint32_lor(v___x_6181_, v___x_6182_);
v___x_6184_ = lean_uint32_to_float32(v___x_6183_);
v___x_6185_ = lp_competition_R2W01b_scaleTable;
v___x_6186_ = 23;
v___x_6187_ = lean_uint32_shift_right(v_y_6102_, v___x_6186_);
v___x_6188_ = lean_uint32_to_nat(v___x_6187_);
v___x_6189_ = lean_array_fget_borrowed(v___x_6185_, v___x_6188_);
lean_dec(v___x_6188_);
v___x_6190_ = lean_unbox_float32(v___x_6189_);
v___x_6191_ = lean_float32_mul(v___x_6184_, v___x_6190_);
v___y_6162_ = v___y_6177_;
v___y_6163_ = v___x_6191_;
goto v___jp_6161_;
}
}
v___jp_6192_:
{
uint32_t v___x_6194_; uint32_t v_a_6195_; uint32_t v___x_6196_; uint32_t v___x_6197_; uint32_t v___x_6198_; uint8_t v___x_6199_; 
v___x_6194_ = 2147483647;
v_a_6195_ = lean_uint32_land(v_y_6102_, v___x_6194_);
v___x_6196_ = 201326591;
v___x_6197_ = 1;
v___x_6198_ = lean_uint32_sub(v_a_6195_, v___x_6197_);
v___x_6199_ = lean_uint32_dec_le(v___x_6196_, v___x_6198_);
if (v___x_6199_ == 0)
{
v___y_6177_ = v___y_6193_;
v___y_6178_ = v___x_6199_;
goto v___jp_6176_;
}
else
{
uint32_t v___x_6200_; uint8_t v___x_6201_; 
v___x_6200_ = 2139095040;
v___x_6201_ = lean_uint32_dec_lt(v_a_6195_, v___x_6200_);
v___y_6177_ = v___y_6193_;
v___y_6178_ = v___x_6201_;
goto v___jp_6176_;
}
}
v___jp_6202_:
{
if (v___y_6203_ == 0)
{
float v___x_6204_; 
v___x_6204_ = lean_float32_of_bits(v_x_6101_);
v___y_6193_ = v___x_6204_;
goto v___jp_6192_;
}
else
{
uint32_t v___x_6205_; uint32_t v___x_6206_; uint32_t v___x_6207_; uint32_t v___x_6208_; float v___x_6209_; lean_object* v___x_6210_; uint32_t v___x_6211_; uint32_t v___x_6212_; lean_object* v___x_6213_; lean_object* v___x_6214_; float v___x_6215_; float v___x_6216_; 
v___x_6205_ = 8388607;
v___x_6206_ = lean_uint32_land(v_x_6101_, v___x_6205_);
v___x_6207_ = 8388608;
v___x_6208_ = lean_uint32_lor(v___x_6206_, v___x_6207_);
v___x_6209_ = lean_uint32_to_float32(v___x_6208_);
v___x_6210_ = lp_competition_R2W01b_scaleTable;
v___x_6211_ = 23;
v___x_6212_ = lean_uint32_shift_right(v_x_6101_, v___x_6211_);
v___x_6213_ = lean_uint32_to_nat(v___x_6212_);
v___x_6214_ = lean_array_fget_borrowed(v___x_6210_, v___x_6213_);
lean_dec(v___x_6213_);
v___x_6215_ = lean_unbox_float32(v___x_6214_);
v___x_6216_ = lean_float32_mul(v___x_6209_, v___x_6215_);
v___y_6193_ = v___x_6216_;
goto v___jp_6192_;
}
}
}
}