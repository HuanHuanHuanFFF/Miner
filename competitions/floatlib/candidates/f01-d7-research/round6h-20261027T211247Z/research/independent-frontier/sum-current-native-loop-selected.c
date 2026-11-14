LEAN_EXPORT uint32_t lp_competition_Submission_R7SinglePassSum_loop___redArg(lean_object* v_n_13015_, lean_object* v_x_13016_, size_t v_count_13017_, size_t v_k_13018_, float v_acc_13019_){
_start:
{
uint8_t v___x_13020_; 
v___x_13020_ = lean_usize_dec_lt(v_k_13018_, v_count_13017_);
if (v___x_13020_ == 0)
{
uint32_t v___x_13021_; 
v___x_13021_ = lean_float32_to_bits(v_acc_13019_);
return v___x_13021_;
}
else
{
lean_object* v_q_13022_; uint32_t v___x_13023_; uint32_t v___x_13024_; uint32_t v_a_13025_; uint32_t v___x_13026_; uint32_t v___x_13027_; uint32_t v___x_13028_; uint8_t v___x_13029_; 
v_q_13022_ = lean_array_uget_borrowed(v_x_13016_, v_k_13018_);
v___x_13023_ = 2147483647;
v___x_13024_ = lean_unbox_uint32(v_q_13022_);
v_a_13025_ = lean_uint32_land(v___x_13024_, v___x_13023_);
v___x_13026_ = 201326591;
v___x_13027_ = 1;
v___x_13028_ = lean_uint32_sub(v_a_13025_, v___x_13027_);
v___x_13029_ = lean_uint32_dec_le(v___x_13026_, v___x_13028_);
if (v___x_13029_ == 0)
{
size_t v___x_13030_; size_t v___x_13031_; uint32_t v___x_13032_; float v___x_13033_; float v___x_13034_; 
v___x_13030_ = ((size_t)1ULL);
v___x_13031_ = lean_usize_add(v_k_13018_, v___x_13030_);
v___x_13032_ = lean_unbox_uint32(v_q_13022_);
v___x_13033_ = lean_float32_of_bits(v___x_13032_);
v___x_13034_ = lean_float32_add(v_acc_13019_, v___x_13033_);
v_k_13018_ = v___x_13031_;
v_acc_13019_ = v___x_13034_;
goto _start;
}
else
{
uint32_t v___x_13036_; uint8_t v___x_13037_; 
v___x_13036_ = 2139095040;
v___x_13037_ = lean_uint32_dec_lt(v_a_13025_, v___x_13036_);
if (v___x_13037_ == 0)
{
uint8_t v___x_13038_; 
v___x_13038_ = lean_uint32_dec_eq(v_a_13025_, v___x_13036_);
if (v___x_13038_ == 0)
{
lean_object* v___x_13039_; lean_object* v___x_13040_; lean_object* v___x_13041_; uint32_t v___x_13042_; uint8_t v___y_13051_; uint8_t v___y_13069_; uint8_t v___y_13084_; uint8_t v___y_13106_; float v___y_13114_; float v___y_13115_; float v___y_13130_; uint8_t v___y_13131_; float v___y_13149_; uint8_t v___y_13151_; uint32_t v_a_13165_; uint32_t v___x_13166_; uint8_t v___x_13167_; 
v___x_13039_ = lean_unsigned_to_nat(1u);
v___x_13040_ = lean_usize_to_nat(v_k_13018_);
v___x_13041_ = lean_nat_add(v___x_13040_, v___x_13039_);
lean_dec(v___x_13040_);
v___x_13042_ = lean_float32_to_bits(v_acc_13019_);
v_a_13165_ = lean_uint32_land(v___x_13042_, v___x_13023_);
v___x_13166_ = lean_uint32_sub(v_a_13165_, v___x_13027_);
v___x_13167_ = lean_uint32_dec_le(v___x_13026_, v___x_13166_);
if (v___x_13167_ == 0)
{
v___y_13151_ = v___x_13167_;
goto v___jp_13150_;
}
else
{
uint8_t v___x_13168_; 
v___x_13168_ = lean_uint32_dec_lt(v_a_13165_, v___x_13036_);
v___y_13151_ = v___x_13168_;
goto v___jp_13150_;
}
v___jp_13043_:
{
lean_object* v___x_13044_; uint32_t v___x_13045_; lean_object* v___x_13046_; lean_object* v___x_13047_; uint32_t v___x_13048_; uint32_t v___x_13049_; 
v___x_13044_ = lean_uint32_to_nat(v___x_13042_);
v___x_13045_ = lean_unbox_uint32(v_q_13022_);
v___x_13046_ = lean_uint32_to_nat(v___x_13045_);
v___x_13047_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_13044_, v___x_13046_);
v___x_13048_ = lean_uint32_of_nat(v___x_13047_);
lean_dec(v___x_13047_);
v___x_13049_ = lp_competition_Submission_R7SumRepair_suffixLoop(v_n_13015_, v_x_13016_, v___x_13041_, v___x_13048_);
return v___x_13049_;
}
v___jp_13050_:
{
if (v___y_13051_ == 0)
{
goto v___jp_13043_;
}
else
{
uint32_t v___x_13052_; uint32_t v___x_13053_; uint32_t v___x_13054_; uint32_t v___x_13055_; 
v___x_13052_ = 4194304;
v___x_13053_ = lean_unbox_uint32(v_q_13022_);
v___x_13054_ = lean_uint32_lor(v___x_13053_, v___x_13052_);
v___x_13055_ = lp_competition_Submission_R7SumRepair_suffixLoop(v_n_13015_, v_x_13016_, v___x_13041_, v___x_13054_);
return v___x_13055_;
}
}
v___jp_13056_:
{
uint32_t v___x_13057_; uint32_t v___x_13058_; uint32_t v___x_13059_; uint32_t v___x_13060_; uint32_t v___x_13061_; uint8_t v___x_13062_; 
v___x_13057_ = 23;
v___x_13058_ = lean_unbox_uint32(v_q_13022_);
v___x_13059_ = lean_uint32_shift_right(v___x_13058_, v___x_13057_);
v___x_13060_ = 255;
v___x_13061_ = lean_uint32_land(v___x_13059_, v___x_13060_);
v___x_13062_ = lean_uint32_dec_eq(v___x_13061_, v___x_13060_);
if (v___x_13062_ == 0)
{
v___y_13051_ = v___x_13062_;
goto v___jp_13050_;
}
else
{
uint32_t v___x_13063_; uint32_t v___x_13064_; uint32_t v___x_13065_; uint32_t v___x_13066_; uint8_t v___x_13067_; 
v___x_13063_ = 8388607;
v___x_13064_ = lean_unbox_uint32(v_q_13022_);
v___x_13065_ = lean_uint32_land(v___x_13064_, v___x_13063_);
v___x_13066_ = 0;
v___x_13067_ = lean_uint32_dec_eq(v___x_13065_, v___x_13066_);
if (v___x_13067_ == 0)
{
v___y_13051_ = v___x_13062_;
goto v___jp_13050_;
}
else
{
goto v___jp_13043_;
}
}
}
v___jp_13068_:
{
if (v___y_13069_ == 0)
{
goto v___jp_13056_;
}
else
{
uint32_t v___x_13070_; uint32_t v___x_13071_; uint32_t v___x_13072_; 
v___x_13070_ = 4194304;
v___x_13071_ = lean_uint32_lor(v___x_13042_, v___x_13070_);
v___x_13072_ = lp_competition_Submission_R7SumRepair_suffixLoop(v_n_13015_, v_x_13016_, v___x_13041_, v___x_13071_);
return v___x_13072_;
}
}
v___jp_13073_:
{
uint32_t v___x_13074_; uint32_t v___x_13075_; uint32_t v___x_13076_; uint32_t v___x_13077_; uint8_t v___x_13078_; 
v___x_13074_ = 23;
v___x_13075_ = lean_uint32_shift_right(v___x_13042_, v___x_13074_);
v___x_13076_ = 255;
v___x_13077_ = lean_uint32_land(v___x_13075_, v___x_13076_);
v___x_13078_ = lean_uint32_dec_eq(v___x_13077_, v___x_13076_);
if (v___x_13078_ == 0)
{
v___y_13069_ = v___x_13078_;
goto v___jp_13068_;
}
else
{
uint32_t v___x_13079_; uint32_t v___x_13080_; uint32_t v___x_13081_; uint8_t v___x_13082_; 
v___x_13079_ = 8388607;
v___x_13080_ = lean_uint32_land(v___x_13042_, v___x_13079_);
v___x_13081_ = 0;
v___x_13082_ = lean_uint32_dec_eq(v___x_13080_, v___x_13081_);
if (v___x_13082_ == 0)
{
v___y_13069_ = v___x_13078_;
goto v___jp_13068_;
}
else
{
goto v___jp_13056_;
}
}
}
v___jp_13083_:
{
if (v___y_13084_ == 0)
{
goto v___jp_13073_;
}
else
{
uint32_t v___x_13085_; uint32_t v___x_13086_; uint32_t v___x_13087_; uint32_t v___x_13088_; uint8_t v___x_13089_; 
v___x_13085_ = 4194304;
v___x_13086_ = lean_unbox_uint32(v_q_13022_);
v___x_13087_ = lean_uint32_land(v___x_13086_, v___x_13085_);
v___x_13088_ = 0;
v___x_13089_ = lean_uint32_dec_eq(v___x_13087_, v___x_13088_);
if (v___x_13089_ == 0)
{
goto v___jp_13073_;
}
else
{
uint32_t v___x_13090_; uint32_t v___x_13091_; uint32_t v___x_13092_; 
v___x_13090_ = lean_unbox_uint32(v_q_13022_);
v___x_13091_ = lean_uint32_lor(v___x_13090_, v___x_13085_);
v___x_13092_ = lp_competition_Submission_R7SumRepair_suffixLoop(v_n_13015_, v_x_13016_, v___x_13041_, v___x_13091_);
return v___x_13092_;
}
}
}
v___jp_13093_:
{
uint32_t v___x_13094_; uint32_t v___x_13095_; uint32_t v___x_13096_; uint32_t v___x_13097_; uint32_t v___x_13098_; uint8_t v___x_13099_; 
v___x_13094_ = 23;
v___x_13095_ = lean_unbox_uint32(v_q_13022_);
v___x_13096_ = lean_uint32_shift_right(v___x_13095_, v___x_13094_);
v___x_13097_ = 255;
v___x_13098_ = lean_uint32_land(v___x_13096_, v___x_13097_);
v___x_13099_ = lean_uint32_dec_eq(v___x_13098_, v___x_13097_);
if (v___x_13099_ == 0)
{
v___y_13084_ = v___x_13099_;
goto v___jp_13083_;
}
else
{
uint32_t v___x_13100_; uint32_t v___x_13101_; uint32_t v___x_13102_; uint32_t v___x_13103_; uint8_t v___x_13104_; 
v___x_13100_ = 8388607;
v___x_13101_ = lean_unbox_uint32(v_q_13022_);
v___x_13102_ = lean_uint32_land(v___x_13101_, v___x_13100_);
v___x_13103_ = 0;
v___x_13104_ = lean_uint32_dec_eq(v___x_13102_, v___x_13103_);
if (v___x_13104_ == 0)
{
v___y_13084_ = v___x_13099_;
goto v___jp_13083_;
}
else
{
goto v___jp_13073_;
}
}
}
v___jp_13105_:
{
if (v___y_13106_ == 0)
{
goto v___jp_13093_;
}
else
{
uint32_t v___x_13107_; uint32_t v___x_13108_; uint32_t v___x_13109_; uint8_t v___x_13110_; 
v___x_13107_ = 4194304;
v___x_13108_ = lean_uint32_land(v___x_13042_, v___x_13107_);
v___x_13109_ = 0;
v___x_13110_ = lean_uint32_dec_eq(v___x_13108_, v___x_13109_);
if (v___x_13110_ == 0)
{
goto v___jp_13093_;
}
else
{
uint32_t v___x_13111_; uint32_t v___x_13112_; 
v___x_13111_ = lean_uint32_lor(v___x_13042_, v___x_13107_);
v___x_13112_ = lp_competition_Submission_R7SumRepair_suffixLoop(v_n_13015_, v_x_13016_, v___x_13041_, v___x_13111_);
return v___x_13112_;
}
}
}
v___jp_13113_:
{
float v_result_13116_; uint8_t v___x_13117_; 
v_result_13116_ = lean_float32_add(v___y_13114_, v___y_13115_);
v___x_13117_ = lean_float32_beq(v_result_13116_, v_result_13116_);
if (v___x_13117_ == 0)
{
uint32_t v___x_13118_; uint32_t v___x_13119_; uint32_t v___x_13120_; uint32_t v___x_13121_; uint8_t v___x_13122_; 
v___x_13118_ = 23;
v___x_13119_ = lean_uint32_shift_right(v___x_13042_, v___x_13118_);
v___x_13120_ = 255;
v___x_13121_ = lean_uint32_land(v___x_13119_, v___x_13120_);
v___x_13122_ = lean_uint32_dec_eq(v___x_13121_, v___x_13120_);
if (v___x_13122_ == 0)
{
v___y_13106_ = v___x_13122_;
goto v___jp_13105_;
}
else
{
uint32_t v___x_13123_; uint32_t v___x_13124_; uint32_t v___x_13125_; uint8_t v___x_13126_; 
v___x_13123_ = 8388607;
v___x_13124_ = lean_uint32_land(v___x_13042_, v___x_13123_);
v___x_13125_ = 0;
v___x_13126_ = lean_uint32_dec_eq(v___x_13124_, v___x_13125_);
if (v___x_13126_ == 0)
{
v___y_13106_ = v___x_13122_;
goto v___jp_13105_;
}
else
{
goto v___jp_13093_;
}
}
}
else
{
uint32_t v___x_13127_; uint32_t v___x_13128_; 
v___x_13127_ = lean_float32_to_bits(v_result_13116_);
v___x_13128_ = lp_competition_Submission_R7SumRepair_suffixLoop(v_n_13015_, v_x_13016_, v___x_13041_, v___x_13127_);
return v___x_13128_;
}
}
v___jp_13129_:
{
if (v___y_13131_ == 0)
{
uint32_t v___x_13132_; float v___x_13133_; 
v___x_13132_ = lean_unbox_uint32(v_q_13022_);
v___x_13133_ = lean_float32_of_bits(v___x_13132_);
v___y_13114_ = v___y_13130_;
v___y_13115_ = v___x_13133_;
goto v___jp_13113_;
}
else
{
uint32_t v___x_13134_; uint32_t v___x_13135_; uint32_t v___x_13136_; uint32_t v___x_13137_; uint32_t v___x_13138_; float v___x_13139_; lean_object* v___x_13140_; uint32_t v___x_13141_; uint32_t v___x_13142_; uint32_t v___x_13143_; lean_object* v___x_13144_; lean_object* v___x_13145_; float v___x_13146_; float v___x_13147_; 
v___x_13134_ = 8388607;
v___x_13135_ = lean_unbox_uint32(v_q_13022_);
v___x_13136_ = lean_uint32_land(v___x_13135_, v___x_13134_);
v___x_13137_ = 8388608;
v___x_13138_ = lean_uint32_lor(v___x_13136_, v___x_13137_);
v___x_13139_ = lean_uint32_to_float32(v___x_13138_);
v___x_13140_ = lp_competition_R2W01b_scaleTable;
v___x_13141_ = 23;
v___x_13142_ = lean_unbox_uint32(v_q_13022_);
v___x_13143_ = lean_uint32_shift_right(v___x_13142_, v___x_13141_);
v___x_13144_ = lean_uint32_to_nat(v___x_13143_);
v___x_13145_ = lean_array_fget_borrowed(v___x_13140_, v___x_13144_);
lean_dec(v___x_13144_);
v___x_13146_ = lean_unbox_float32(v___x_13145_);
v___x_13147_ = lean_float32_mul(v___x_13139_, v___x_13146_);
v___y_13114_ = v___y_13130_;
v___y_13115_ = v___x_13147_;
goto v___jp_13113_;
}
}
v___jp_13148_:
{
if (v___x_13029_ == 0)
{
v___y_13130_ = v___y_13149_;
v___y_13131_ = v___x_13029_;
goto v___jp_13129_;
}
else
{
v___y_13130_ = v___y_13149_;
v___y_13131_ = v___x_13037_;
goto v___jp_13129_;
}
}
v___jp_13150_:
{
if (v___y_13151_ == 0)
{
float v___x_13152_; 
v___x_13152_ = lean_float32_of_bits(v___x_13042_);
v___y_13149_ = v___x_13152_;
goto v___jp_13148_;
}
else
{
uint32_t v___x_13153_; uint32_t v___x_13154_; uint32_t v___x_13155_; uint32_t v___x_13156_; float v___x_13157_; lean_object* v___x_13158_; uint32_t v___x_13159_; uint32_t v___x_13160_; lean_object* v___x_13161_; lean_object* v___x_13162_; float v___x_13163_; float v___x_13164_; 
v___x_13153_ = 8388607;
v___x_13154_ = lean_uint32_land(v___x_13042_, v___x_13153_);
v___x_13155_ = 8388608;
v___x_13156_ = lean_uint32_lor(v___x_13154_, v___x_13155_);
v___x_13157_ = lean_uint32_to_float32(v___x_13156_);
v___x_13158_ = lp_competition_R2W01b_scaleTable;
v___x_13159_ = 23;
v___x_13160_ = lean_uint32_shift_right(v___x_13042_, v___x_13159_);
v___x_13161_ = lean_uint32_to_nat(v___x_13160_);
v___x_13162_ = lean_array_fget_borrowed(v___x_13158_, v___x_13161_);
lean_dec(v___x_13161_);
v___x_13163_ = lean_unbox_float32(v___x_13162_);
v___x_13164_ = lean_float32_mul(v___x_13157_, v___x_13163_);
v___y_13149_ = v___x_13164_;
goto v___jp_13148_;
}
}
}
else
{
size_t v___x_13169_; size_t v___x_13170_; uint32_t v___x_13171_; float v___x_13172_; float v___x_13173_; 
v___x_13169_ = ((size_t)1ULL);
v___x_13170_ = lean_usize_add(v_k_13018_, v___x_13169_);
v___x_13171_ = lean_unbox_uint32(v_q_13022_);
v___x_13172_ = lean_float32_of_bits(v___x_13171_);
v___x_13173_ = lean_float32_add(v_acc_13019_, v___x_13172_);
v_k_13018_ = v___x_13170_;
v_acc_13019_ = v___x_13173_;
goto _start;
}
}
else
{
size_t v___x_13175_; size_t v___x_13176_; uint32_t v___x_13177_; uint32_t v___x_13178_; uint32_t v___x_13179_; uint32_t v___x_13180_; uint32_t v___x_13181_; float v___x_13182_; lean_object* v___x_13183_; uint32_t v___x_13184_; uint32_t v___x_13185_; uint32_t v___x_13186_; lean_object* v___x_13187_; lean_object* v___x_13188_; float v___x_13189_; float v___x_13190_; float v___x_13191_; 
v___x_13175_ = ((size_t)1ULL);
v___x_13176_ = lean_usize_add(v_k_13018_, v___x_13175_);
v___x_13177_ = 8388607;
v___x_13178_ = lean_unbox_uint32(v_q_13022_);
v___x_13179_ = lean_uint32_land(v___x_13178_, v___x_13177_);
v___x_13180_ = 8388608;
v___x_13181_ = lean_uint32_lor(v___x_13179_, v___x_13180_);
v___x_13182_ = lean_uint32_to_float32(v___x_13181_);
v___x_13183_ = lp_competition_R2W01b_scaleTable;
v___x_13184_ = 23;
v___x_13185_ = lean_unbox_uint32(v_q_13022_);
v___x_13186_ = lean_uint32_shift_right(v___x_13185_, v___x_13184_);
v___x_13187_ = lean_uint32_to_nat(v___x_13186_);
v___x_13188_ = lean_array_fget_borrowed(v___x_13183_, v___x_13187_);
lean_dec(v___x_13187_);
v___x_13189_ = lean_unbox_float32(v___x_13188_);
v___x_13190_ = lean_float32_mul(v___x_13182_, v___x_13189_);
v___x_13191_ = lean_float32_add(v_acc_13019_, v___x_13190_);
v_k_13018_ = v___x_13176_;
v_acc_13019_ = v___x_13191_;
goto _start;
}
}
}
}
}
