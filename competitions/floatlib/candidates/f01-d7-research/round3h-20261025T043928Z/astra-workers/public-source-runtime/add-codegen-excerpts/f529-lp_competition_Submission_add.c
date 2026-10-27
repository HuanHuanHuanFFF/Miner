LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t v_x_6083_, uint32_t v_y_6084_){
_start:
{
uint8_t v___y_6092_; uint8_t v___y_6106_; uint8_t v___y_6120_; uint8_t v___y_6137_; float v___y_6144_; float v___y_6145_; float v___y_6159_; uint8_t v___y_6160_; float v___y_6175_; uint8_t v___y_6185_; uint32_t v___x_6199_; uint32_t v_a_6200_; uint32_t v___x_6201_; uint32_t v___x_6202_; uint32_t v___x_6203_; uint8_t v___x_6204_; 
v___x_6199_ = 2147483647;
v_a_6200_ = lean_uint32_land(v_x_6083_, v___x_6199_);
v___x_6201_ = 201326591;
v___x_6202_ = 1;
v___x_6203_ = lean_uint32_sub(v_a_6200_, v___x_6202_);
v___x_6204_ = lean_uint32_dec_le(v___x_6201_, v___x_6203_);
if (v___x_6204_ == 0)
{
v___y_6185_ = v___x_6204_;
goto v___jp_6184_;
}
else
{
uint32_t v___x_6205_; uint8_t v___x_6206_; 
v___x_6205_ = 2139095040;
v___x_6206_ = lean_uint32_dec_lt(v_a_6200_, v___x_6205_);
v___y_6185_ = v___x_6206_;
goto v___jp_6184_;
}
v___jp_6085_:
{
lean_object* v___x_6086_; lean_object* v___x_6087_; lean_object* v___x_6088_; lean_object* v___x_6089_; uint32_t v___x_6090_; 
v___x_6086_ = ((lean_object*)(lp_competition_R7W01_F32___closed__0));
v___x_6087_ = lean_uint32_to_nat(v_x_6083_);
v___x_6088_ = lean_uint32_to_nat(v_y_6084_);
v___x_6089_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(v___x_6086_, v___x_6087_, v___x_6088_);
v___x_6090_ = lean_uint32_of_nat(v___x_6089_);
lean_dec(v___x_6089_);
return v___x_6090_;
}
v___jp_6091_:
{
if (v___y_6092_ == 0)
{
goto v___jp_6085_;
}
else
{
uint32_t v___x_6093_; uint32_t v___x_6094_; 
v___x_6093_ = 4194304;
v___x_6094_ = lean_uint32_lor(v_y_6084_, v___x_6093_);
return v___x_6094_;
}
}
v___jp_6095_:
{
uint32_t v___x_6096_; uint32_t v___x_6097_; uint32_t v___x_6098_; uint32_t v___x_6099_; uint8_t v___x_6100_; 
v___x_6096_ = 23;
v___x_6097_ = lean_uint32_shift_right(v_y_6084_, v___x_6096_);
v___x_6098_ = 255;
v___x_6099_ = lean_uint32_land(v___x_6097_, v___x_6098_);
v___x_6100_ = lean_uint32_dec_eq(v___x_6099_, v___x_6098_);
if (v___x_6100_ == 0)
{
v___y_6092_ = v___x_6100_;
goto v___jp_6091_;
}
else
{
uint32_t v___x_6101_; uint32_t v___x_6102_; uint32_t v___x_6103_; uint8_t v___x_6104_; 
v___x_6101_ = 8388607;
v___x_6102_ = lean_uint32_land(v_y_6084_, v___x_6101_);
v___x_6103_ = 0;
v___x_6104_ = lean_uint32_dec_eq(v___x_6102_, v___x_6103_);
if (v___x_6104_ == 0)
{
v___y_6092_ = v___x_6100_;
goto v___jp_6091_;
}
else
{
goto v___jp_6085_;
}
}
}
v___jp_6105_:
{
if (v___y_6106_ == 0)
{
goto v___jp_6095_;
}
else
{
uint32_t v___x_6107_; uint32_t v___x_6108_; 
v___x_6107_ = 4194304;
v___x_6108_ = lean_uint32_lor(v_x_6083_, v___x_6107_);
return v___x_6108_;
}
}
v___jp_6109_:
{
uint32_t v___x_6110_; uint32_t v___x_6111_; uint32_t v___x_6112_; uint32_t v___x_6113_; uint8_t v___x_6114_; 
v___x_6110_ = 23;
v___x_6111_ = lean_uint32_shift_right(v_x_6083_, v___x_6110_);
v___x_6112_ = 255;
v___x_6113_ = lean_uint32_land(v___x_6111_, v___x_6112_);
v___x_6114_ = lean_uint32_dec_eq(v___x_6113_, v___x_6112_);
if (v___x_6114_ == 0)
{
v___y_6106_ = v___x_6114_;
goto v___jp_6105_;
}
else
{
uint32_t v___x_6115_; uint32_t v___x_6116_; uint32_t v___x_6117_; uint8_t v___x_6118_; 
v___x_6115_ = 8388607;
v___x_6116_ = lean_uint32_land(v_x_6083_, v___x_6115_);
v___x_6117_ = 0;
v___x_6118_ = lean_uint32_dec_eq(v___x_6116_, v___x_6117_);
if (v___x_6118_ == 0)
{
v___y_6106_ = v___x_6114_;
goto v___jp_6105_;
}
else
{
goto v___jp_6095_;
}
}
}
v___jp_6119_:
{
if (v___y_6120_ == 0)
{
goto v___jp_6109_;
}
else
{
uint32_t v___x_6121_; uint32_t v___x_6122_; uint32_t v___x_6123_; uint8_t v___x_6124_; 
v___x_6121_ = 4194304;
v___x_6122_ = lean_uint32_land(v_y_6084_, v___x_6121_);
v___x_6123_ = 0;
v___x_6124_ = lean_uint32_dec_eq(v___x_6122_, v___x_6123_);
if (v___x_6124_ == 0)
{
goto v___jp_6109_;
}
else
{
uint32_t v___x_6125_; 
v___x_6125_ = lean_uint32_lor(v_y_6084_, v___x_6121_);
return v___x_6125_;
}
}
}
v___jp_6126_:
{
uint32_t v___x_6127_; uint32_t v___x_6128_; uint32_t v___x_6129_; uint32_t v___x_6130_; uint8_t v___x_6131_; 
v___x_6127_ = 23;
v___x_6128_ = lean_uint32_shift_right(v_y_6084_, v___x_6127_);
v___x_6129_ = 255;
v___x_6130_ = lean_uint32_land(v___x_6128_, v___x_6129_);
v___x_6131_ = lean_uint32_dec_eq(v___x_6130_, v___x_6129_);
if (v___x_6131_ == 0)
{
v___y_6120_ = v___x_6131_;
goto v___jp_6119_;
}
else
{
uint32_t v___x_6132_; uint32_t v___x_6133_; uint32_t v___x_6134_; uint8_t v___x_6135_; 
v___x_6132_ = 8388607;
v___x_6133_ = lean_uint32_land(v_y_6084_, v___x_6132_);
v___x_6134_ = 0;
v___x_6135_ = lean_uint32_dec_eq(v___x_6133_, v___x_6134_);
if (v___x_6135_ == 0)
{
v___y_6120_ = v___x_6131_;
goto v___jp_6119_;
}
else
{
goto v___jp_6109_;
}
}
}
v___jp_6136_:
{
if (v___y_6137_ == 0)
{
goto v___jp_6126_;
}
else
{
uint32_t v___x_6138_; uint32_t v___x_6139_; uint32_t v___x_6140_; uint8_t v___x_6141_; 
v___x_6138_ = 4194304;
v___x_6139_ = lean_uint32_land(v_x_6083_, v___x_6138_);
v___x_6140_ = 0;
v___x_6141_ = lean_uint32_dec_eq(v___x_6139_, v___x_6140_);
if (v___x_6141_ == 0)
{
goto v___jp_6126_;
}
else
{
uint32_t v___x_6142_; 
v___x_6142_ = lean_uint32_lor(v_x_6083_, v___x_6138_);
return v___x_6142_;
}
}
}
v___jp_6143_:
{
float v_result_6146_; uint8_t v___x_6147_; 
v_result_6146_ = lean_float32_add(v___y_6144_, v___y_6145_);
v___x_6147_ = lean_float32_beq(v_result_6146_, v_result_6146_);
if (v___x_6147_ == 0)
{
uint32_t v___x_6148_; uint32_t v___x_6149_; uint32_t v___x_6150_; uint32_t v___x_6151_; uint8_t v___x_6152_; 
v___x_6148_ = 23;
v___x_6149_ = lean_uint32_shift_right(v_x_6083_, v___x_6148_);
v___x_6150_ = 255;
v___x_6151_ = lean_uint32_land(v___x_6149_, v___x_6150_);
v___x_6152_ = lean_uint32_dec_eq(v___x_6151_, v___x_6150_);
if (v___x_6152_ == 0)
{
v___y_6137_ = v___x_6152_;
goto v___jp_6136_;
}
else
{
uint32_t v___x_6153_; uint32_t v___x_6154_; uint32_t v___x_6155_; uint8_t v___x_6156_; 
v___x_6153_ = 8388607;
v___x_6154_ = lean_uint32_land(v_x_6083_, v___x_6153_);
v___x_6155_ = 0;
v___x_6156_ = lean_uint32_dec_eq(v___x_6154_, v___x_6155_);
if (v___x_6156_ == 0)
{
v___y_6137_ = v___x_6152_;
goto v___jp_6136_;
}
else
{
goto v___jp_6126_;
}
}
}
else
{
uint32_t v___x_6157_; 
v___x_6157_ = lean_float32_to_bits(v_result_6146_);
return v___x_6157_;
}
}
v___jp_6158_:
{
if (v___y_6160_ == 0)
{
float v___x_6161_; 
v___x_6161_ = lean_float32_of_bits(v_y_6084_);
v___y_6144_ = v___y_6159_;
v___y_6145_ = v___x_6161_;
goto v___jp_6143_;
}
else
{
uint32_t v___x_6162_; uint32_t v___x_6163_; uint32_t v___x_6164_; uint32_t v___x_6165_; float v___x_6166_; lean_object* v___x_6167_; uint32_t v___x_6168_; uint32_t v___x_6169_; lean_object* v___x_6170_; lean_object* v___x_6171_; float v___x_6172_; float v___x_6173_; 
v___x_6162_ = 8388607;
v___x_6163_ = lean_uint32_land(v_y_6084_, v___x_6162_);
v___x_6164_ = 8388608;
v___x_6165_ = lean_uint32_lor(v___x_6163_, v___x_6164_);
v___x_6166_ = lean_uint32_to_float32(v___x_6165_);
v___x_6167_ = lp_competition_R2W01b_scaleTable;
v___x_6168_ = 23;
v___x_6169_ = lean_uint32_shift_right(v_y_6084_, v___x_6168_);
v___x_6170_ = lean_uint32_to_nat(v___x_6169_);
v___x_6171_ = lean_array_fget_borrowed(v___x_6167_, v___x_6170_);
lean_dec(v___x_6170_);
v___x_6172_ = lean_unbox_float32(v___x_6171_);
v___x_6173_ = lean_float32_mul(v___x_6166_, v___x_6172_);
v___y_6144_ = v___y_6159_;
v___y_6145_ = v___x_6173_;
goto v___jp_6143_;
}
}
v___jp_6174_:
{
uint32_t v___x_6176_; uint32_t v_a_6177_; uint32_t v___x_6178_; uint32_t v___x_6179_; uint32_t v___x_6180_; uint8_t v___x_6181_; 
v___x_6176_ = 2147483647;
v_a_6177_ = lean_uint32_land(v_y_6084_, v___x_6176_);
v___x_6178_ = 201326591;
v___x_6179_ = 1;
v___x_6180_ = lean_uint32_sub(v_a_6177_, v___x_6179_);
v___x_6181_ = lean_uint32_dec_le(v___x_6178_, v___x_6180_);
if (v___x_6181_ == 0)
{
v___y_6159_ = v___y_6175_;
v___y_6160_ = v___x_6181_;
goto v___jp_6158_;
}
else
{
uint32_t v___x_6182_; uint8_t v___x_6183_; 
v___x_6182_ = 2139095040;
v___x_6183_ = lean_uint32_dec_lt(v_a_6177_, v___x_6182_);
v___y_6159_ = v___y_6175_;
v___y_6160_ = v___x_6183_;
goto v___jp_6158_;
}
}
v___jp_6184_:
{
if (v___y_6185_ == 0)
{
float v___x_6186_; 
v___x_6186_ = lean_float32_of_bits(v_x_6083_);
v___y_6175_ = v___x_6186_;
goto v___jp_6174_;
}
else
{
uint32_t v___x_6187_; uint32_t v___x_6188_; uint32_t v___x_6189_; uint32_t v___x_6190_; float v___x_6191_; lean_object* v___x_6192_; uint32_t v___x_6193_; uint32_t v___x_6194_; lean_object* v___x_6195_; lean_object* v___x_6196_; float v___x_6197_; float v___x_6198_; 
v___x_6187_ = 8388607;
v___x_6188_ = lean_uint32_land(v_x_6083_, v___x_6187_);
v___x_6189_ = 8388608;
v___x_6190_ = lean_uint32_lor(v___x_6188_, v___x_6189_);
v___x_6191_ = lean_uint32_to_float32(v___x_6190_);
v___x_6192_ = lp_competition_R2W01b_scaleTable;
v___x_6193_ = 23;
v___x_6194_ = lean_uint32_shift_right(v_x_6083_, v___x_6193_);
v___x_6195_ = lean_uint32_to_nat(v___x_6194_);
v___x_6196_ = lean_array_fget_borrowed(v___x_6192_, v___x_6195_);
lean_dec(v___x_6195_);
v___x_6197_ = lean_unbox_float32(v___x_6196_);
v___x_6198_ = lean_float32_mul(v___x_6191_, v___x_6197_);
v___y_6175_ = v___x_6198_;
goto v___jp_6174_;
}
}
}
}