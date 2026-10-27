LEAN_EXPORT lean_object* lp_competition_Submission_R19Temporal_loop(lean_object* v_n_15011_, lean_object* v_baseA_15012_, lean_object* v_A_15013_, lean_object* v_B_15014_, lean_object* v_t_15015_, float v_s0_15016_, float v_s1_15017_){
_start:
{
float v___y_15019_; float v___y_15020_; float v___y_15021_; float v___y_15022_; lean_object* v___y_15023_; uint32_t v___y_15024_; float v___y_15033_; float v___y_15034_; float v___y_15035_; float v___y_15036_; uint32_t v___y_15037_; lean_object* v___x_15044_; lean_object* v_k_15045_; lean_object* v___x_15046_; lean_object* v___x_15047_; uint8_t v___x_15048_; 
v___x_15044_ = lean_unsigned_to_nat(4u);
v_k_15045_ = lean_nat_mul(v___x_15044_, v_t_15015_);
v___x_15046_ = lean_unsigned_to_nat(3u);
v___x_15047_ = lean_nat_add(v_k_15045_, v___x_15046_);
v___x_15048_ = lean_nat_dec_lt(v___x_15047_, v_n_15011_);
lean_dec(v___x_15047_);
if (v___x_15048_ == 0)
{
uint8_t v___x_15049_; 
v___x_15049_ = lean_nat_dec_lt(v_k_15045_, v_n_15011_);
if (v___x_15049_ == 0)
{
lean_object* v___x_15050_; 
lean_dec(v_k_15045_);
lean_dec(v_t_15015_);
v___x_15050_ = lean_alloc_ctor(0, 0, 8);
lean_ctor_set_float32(v___x_15050_, 0, v_s0_15016_);
lean_ctor_set_float32(v___x_15050_, 4, v_s1_15017_);
return v___x_15050_;
}
else
{
lean_object* v_b_15051_; lean_object* v___x_15052_; float v___y_15054_; float v___y_15055_; float v___y_15056_; float v___y_15057_; float v___y_15058_; float v___y_15059_; uint32_t v___y_15060_; uint32_t v___y_15077_; lean_object* v___x_15099_; uint8_t v___x_15100_; 
v_b_15051_ = lean_array_fget_borrowed(v_B_15014_, v_t_15015_);
lean_dec(v_t_15015_);
v___x_15052_ = lean_nat_add(v_baseA_15012_, v_k_15045_);
v___x_15099_ = lean_array_get_size(v_A_15013_);
v___x_15100_ = lean_nat_dec_lt(v___x_15052_, v___x_15099_);
if (v___x_15100_ == 0)
{
uint32_t v___x_15101_; 
v___x_15101_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15077_ = v___x_15101_;
goto v___jp_15076_;
}
else
{
lean_object* v___x_15102_; uint32_t v___x_15103_; 
v___x_15102_ = lean_array_fget_borrowed(v_A_15013_, v___x_15052_);
v___x_15103_ = lean_unbox_uint32(v___x_15102_);
v___y_15077_ = v___x_15103_;
goto v___jp_15076_;
}
v___jp_15053_:
{
float v___x_15061_; float v___x_15062_; float v_s0_15063_; float v___x_15064_; float v_s1_15065_; lean_object* v___x_15066_; lean_object* v___x_15067_; uint8_t v___x_15068_; 
v___x_15061_ = lean_float32_of_bits(v___y_15060_);
v___x_15062_ = lean_float32_mul(v___x_15061_, v___y_15059_);
v_s0_15063_ = lean_float32_add(v___y_15058_, v___x_15062_);
v___x_15064_ = lean_float32_mul(v___x_15061_, v___y_15054_);
v_s1_15065_ = lean_float32_add(v___y_15055_, v___x_15064_);
v___x_15066_ = lean_unsigned_to_nat(2u);
v___x_15067_ = lean_nat_add(v_k_15045_, v___x_15066_);
lean_dec(v_k_15045_);
v___x_15068_ = lean_nat_dec_lt(v___x_15067_, v_n_15011_);
lean_dec(v___x_15067_);
if (v___x_15068_ == 0)
{
lean_object* v___x_15069_; 
lean_dec(v___x_15052_);
v___x_15069_ = lean_alloc_ctor(0, 0, 8);
lean_ctor_set_float32(v___x_15069_, 0, v_s0_15063_);
lean_ctor_set_float32(v___x_15069_, 4, v_s1_15065_);
return v___x_15069_;
}
else
{
lean_object* v___x_15070_; lean_object* v___x_15071_; uint8_t v___x_15072_; 
v___x_15070_ = lean_nat_add(v___x_15052_, v___x_15066_);
lean_dec(v___x_15052_);
v___x_15071_ = lean_array_get_size(v_A_15013_);
v___x_15072_ = lean_nat_dec_lt(v___x_15070_, v___x_15071_);
if (v___x_15072_ == 0)
{
uint32_t v___x_15073_; 
lean_dec(v___x_15070_);
v___x_15073_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15033_ = v_s0_15063_;
v___y_15034_ = v_s1_15065_;
v___y_15035_ = v___y_15056_;
v___y_15036_ = v___y_15057_;
v___y_15037_ = v___x_15073_;
goto v___jp_15032_;
}
else
{
lean_object* v___x_15074_; uint32_t v___x_15075_; 
v___x_15074_ = lean_array_fget_borrowed(v_A_15013_, v___x_15070_);
lean_dec(v___x_15070_);
v___x_15075_ = lean_unbox_uint32(v___x_15074_);
v___y_15033_ = v_s0_15063_;
v___y_15034_ = v_s1_15065_;
v___y_15035_ = v___y_15056_;
v___y_15036_ = v___y_15057_;
v___y_15037_ = v___x_15075_;
goto v___jp_15032_;
}
}
}
v___jp_15076_:
{
float v_k0c0_15078_; float v_k0c1_15079_; float v_k1c0_15080_; float v_k1c1_15081_; float v_k2c0_15082_; float v_k2c1_15083_; float v___x_15084_; float v___x_15085_; float v_s0_15086_; float v___x_15087_; float v_s1_15088_; lean_object* v___x_15089_; lean_object* v___x_15090_; uint8_t v___x_15091_; 
v_k0c0_15078_ = lean_ctor_get_float32(v_b_15051_, 0);
v_k0c1_15079_ = lean_ctor_get_float32(v_b_15051_, 4);
v_k1c0_15080_ = lean_ctor_get_float32(v_b_15051_, 8);
v_k1c1_15081_ = lean_ctor_get_float32(v_b_15051_, 12);
v_k2c0_15082_ = lean_ctor_get_float32(v_b_15051_, 16);
v_k2c1_15083_ = lean_ctor_get_float32(v_b_15051_, 20);
v___x_15084_ = lean_float32_of_bits(v___y_15077_);
v___x_15085_ = lean_float32_mul(v___x_15084_, v_k0c0_15078_);
v_s0_15086_ = lean_float32_add(v_s0_15016_, v___x_15085_);
v___x_15087_ = lean_float32_mul(v___x_15084_, v_k0c1_15079_);
v_s1_15088_ = lean_float32_add(v_s1_15017_, v___x_15087_);
v___x_15089_ = lean_unsigned_to_nat(1u);
v___x_15090_ = lean_nat_add(v_k_15045_, v___x_15089_);
v___x_15091_ = lean_nat_dec_lt(v___x_15090_, v_n_15011_);
lean_dec(v___x_15090_);
if (v___x_15091_ == 0)
{
lean_object* v___x_15092_; 
lean_dec(v___x_15052_);
lean_dec(v_k_15045_);
v___x_15092_ = lean_alloc_ctor(0, 0, 8);
lean_ctor_set_float32(v___x_15092_, 0, v_s0_15086_);
lean_ctor_set_float32(v___x_15092_, 4, v_s1_15088_);
return v___x_15092_;
}
else
{
lean_object* v___x_15093_; lean_object* v___x_15094_; uint8_t v___x_15095_; 
v___x_15093_ = lean_nat_add(v___x_15052_, v___x_15089_);
v___x_15094_ = lean_array_get_size(v_A_15013_);
v___x_15095_ = lean_nat_dec_lt(v___x_15093_, v___x_15094_);
if (v___x_15095_ == 0)
{
uint32_t v___x_15096_; 
lean_dec(v___x_15093_);
v___x_15096_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15054_ = v_k1c1_15081_;
v___y_15055_ = v_s1_15088_;
v___y_15056_ = v_k2c0_15082_;
v___y_15057_ = v_k2c1_15083_;
v___y_15058_ = v_s0_15086_;
v___y_15059_ = v_k1c0_15080_;
v___y_15060_ = v___x_15096_;
goto v___jp_15053_;
}
else
{
lean_object* v___x_15097_; uint32_t v___x_15098_; 
v___x_15097_ = lean_array_fget_borrowed(v_A_15013_, v___x_15093_);
lean_dec(v___x_15093_);
v___x_15098_ = lean_unbox_uint32(v___x_15097_);
v___y_15054_ = v_k1c1_15081_;
v___y_15055_ = v_s1_15088_;
v___y_15056_ = v_k2c0_15082_;
v___y_15057_ = v_k2c1_15083_;
v___y_15058_ = v_s0_15086_;
v___y_15059_ = v_k1c0_15080_;
v___y_15060_ = v___x_15098_;
goto v___jp_15053_;
}
}
}
}
}
else
{
lean_object* v_b_15104_; lean_object* v___x_15105_; float v___y_15107_; float v___y_15108_; float v___y_15109_; float v___y_15110_; float v___y_15111_; lean_object* v___y_15112_; float v___y_15113_; uint32_t v___y_15114_; float v___y_15127_; float v___y_15128_; float v___y_15129_; float v___y_15130_; float v___y_15131_; float v___y_15132_; float v___y_15133_; float v___y_15134_; lean_object* v___y_15135_; uint32_t v___y_15136_; uint32_t v___y_15150_; lean_object* v___x_15171_; uint8_t v___x_15172_; 
v_b_15104_ = lean_array_fget_borrowed(v_B_15014_, v_t_15015_);
v___x_15105_ = lean_nat_add(v_baseA_15012_, v_k_15045_);
lean_dec(v_k_15045_);
v___x_15171_ = lean_array_get_size(v_A_15013_);
v___x_15172_ = lean_nat_dec_lt(v___x_15105_, v___x_15171_);
if (v___x_15172_ == 0)
{
uint32_t v___x_15173_; 
v___x_15173_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15150_ = v___x_15173_;
goto v___jp_15149_;
}
else
{
lean_object* v___x_15174_; uint32_t v___x_15175_; 
v___x_15174_ = lean_array_fget_borrowed(v_A_15013_, v___x_15105_);
v___x_15175_ = lean_unbox_uint32(v___x_15174_);
v___y_15150_ = v___x_15175_;
goto v___jp_15149_;
}
v___jp_15106_:
{
float v___x_15115_; float v___x_15116_; float v_s0_15117_; float v___x_15118_; float v_s1_15119_; lean_object* v___x_15120_; lean_object* v___x_15121_; uint8_t v___x_15122_; 
v___x_15115_ = lean_float32_of_bits(v___y_15114_);
v___x_15116_ = lean_float32_mul(v___x_15115_, v___y_15111_);
v_s0_15117_ = lean_float32_add(v___y_15110_, v___x_15116_);
v___x_15118_ = lean_float32_mul(v___x_15115_, v___y_15108_);
v_s1_15119_ = lean_float32_add(v___y_15107_, v___x_15118_);
v___x_15120_ = lean_nat_add(v___x_15105_, v___x_15046_);
lean_dec(v___x_15105_);
v___x_15121_ = lean_array_get_size(v_A_15013_);
v___x_15122_ = lean_nat_dec_lt(v___x_15120_, v___x_15121_);
if (v___x_15122_ == 0)
{
uint32_t v___x_15123_; 
lean_dec(v___x_15120_);
v___x_15123_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15019_ = v_s1_15119_;
v___y_15020_ = v_s0_15117_;
v___y_15021_ = v___y_15109_;
v___y_15022_ = v___y_15113_;
v___y_15023_ = v___y_15112_;
v___y_15024_ = v___x_15123_;
goto v___jp_15018_;
}
else
{
lean_object* v___x_15124_; uint32_t v___x_15125_; 
v___x_15124_ = lean_array_fget_borrowed(v_A_15013_, v___x_15120_);
lean_dec(v___x_15120_);
v___x_15125_ = lean_unbox_uint32(v___x_15124_);
v___y_15019_ = v_s1_15119_;
v___y_15020_ = v_s0_15117_;
v___y_15021_ = v___y_15109_;
v___y_15022_ = v___y_15113_;
v___y_15023_ = v___y_15112_;
v___y_15024_ = v___x_15125_;
goto v___jp_15018_;
}
}
v___jp_15126_:
{
float v___x_15137_; float v___x_15138_; float v_s0_15139_; float v___x_15140_; float v_s1_15141_; lean_object* v___x_15142_; lean_object* v___x_15143_; lean_object* v___x_15144_; uint8_t v___x_15145_; 
v___x_15137_ = lean_float32_of_bits(v___y_15136_);
v___x_15138_ = lean_float32_mul(v___x_15137_, v___y_15128_);
v_s0_15139_ = lean_float32_add(v___y_15133_, v___x_15138_);
v___x_15140_ = lean_float32_mul(v___x_15137_, v___y_15127_);
v_s1_15141_ = lean_float32_add(v___y_15131_, v___x_15140_);
v___x_15142_ = lean_unsigned_to_nat(2u);
v___x_15143_ = lean_nat_add(v___x_15105_, v___x_15142_);
v___x_15144_ = lean_array_get_size(v_A_15013_);
v___x_15145_ = lean_nat_dec_lt(v___x_15143_, v___x_15144_);
if (v___x_15145_ == 0)
{
uint32_t v___x_15146_; 
lean_dec(v___x_15143_);
v___x_15146_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15107_ = v_s1_15141_;
v___y_15108_ = v___y_15129_;
v___y_15109_ = v___y_15130_;
v___y_15110_ = v_s0_15139_;
v___y_15111_ = v___y_15132_;
v___y_15112_ = v___y_15135_;
v___y_15113_ = v___y_15134_;
v___y_15114_ = v___x_15146_;
goto v___jp_15106_;
}
else
{
lean_object* v___x_15147_; uint32_t v___x_15148_; 
v___x_15147_ = lean_array_fget_borrowed(v_A_15013_, v___x_15143_);
lean_dec(v___x_15143_);
v___x_15148_ = lean_unbox_uint32(v___x_15147_);
v___y_15107_ = v_s1_15141_;
v___y_15108_ = v___y_15129_;
v___y_15109_ = v___y_15130_;
v___y_15110_ = v_s0_15139_;
v___y_15111_ = v___y_15132_;
v___y_15112_ = v___y_15135_;
v___y_15113_ = v___y_15134_;
v___y_15114_ = v___x_15148_;
goto v___jp_15106_;
}
}
v___jp_15149_:
{
float v_k0c0_15151_; float v_k0c1_15152_; float v_k1c0_15153_; float v_k1c1_15154_; float v_k2c0_15155_; float v_k2c1_15156_; float v_k3c0_15157_; float v_k3c1_15158_; float v___x_15159_; float v___x_15160_; float v_s0_15161_; float v___x_15162_; float v_s1_15163_; lean_object* v___x_15164_; lean_object* v___x_15165_; lean_object* v___x_15166_; uint8_t v___x_15167_; 
v_k0c0_15151_ = lean_ctor_get_float32(v_b_15104_, 0);
v_k0c1_15152_ = lean_ctor_get_float32(v_b_15104_, 4);
v_k1c0_15153_ = lean_ctor_get_float32(v_b_15104_, 8);
v_k1c1_15154_ = lean_ctor_get_float32(v_b_15104_, 12);
v_k2c0_15155_ = lean_ctor_get_float32(v_b_15104_, 16);
v_k2c1_15156_ = lean_ctor_get_float32(v_b_15104_, 20);
v_k3c0_15157_ = lean_ctor_get_float32(v_b_15104_, 24);
v_k3c1_15158_ = lean_ctor_get_float32(v_b_15104_, 28);
v___x_15159_ = lean_float32_of_bits(v___y_15150_);
v___x_15160_ = lean_float32_mul(v___x_15159_, v_k0c0_15151_);
v_s0_15161_ = lean_float32_add(v_s0_15016_, v___x_15160_);
v___x_15162_ = lean_float32_mul(v___x_15159_, v_k0c1_15152_);
v_s1_15163_ = lean_float32_add(v_s1_15017_, v___x_15162_);
v___x_15164_ = lean_unsigned_to_nat(1u);
v___x_15165_ = lean_nat_add(v___x_15105_, v___x_15164_);
v___x_15166_ = lean_array_get_size(v_A_15013_);
v___x_15167_ = lean_nat_dec_lt(v___x_15165_, v___x_15166_);
if (v___x_15167_ == 0)
{
uint32_t v___x_15168_; 
lean_dec(v___x_15165_);
v___x_15168_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15127_ = v_k1c1_15154_;
v___y_15128_ = v_k1c0_15153_;
v___y_15129_ = v_k2c1_15156_;
v___y_15130_ = v_k3c1_15158_;
v___y_15131_ = v_s1_15163_;
v___y_15132_ = v_k2c0_15155_;
v___y_15133_ = v_s0_15161_;
v___y_15134_ = v_k3c0_15157_;
v___y_15135_ = v___x_15164_;
v___y_15136_ = v___x_15168_;
goto v___jp_15126_;
}
else
{
lean_object* v___x_15169_; uint32_t v___x_15170_; 
v___x_15169_ = lean_array_fget_borrowed(v_A_15013_, v___x_15165_);
lean_dec(v___x_15165_);
v___x_15170_ = lean_unbox_uint32(v___x_15169_);
v___y_15127_ = v_k1c1_15154_;
v___y_15128_ = v_k1c0_15153_;
v___y_15129_ = v_k2c1_15156_;
v___y_15130_ = v_k3c1_15158_;
v___y_15131_ = v_s1_15163_;
v___y_15132_ = v_k2c0_15155_;
v___y_15133_ = v_s0_15161_;
v___y_15134_ = v_k3c0_15157_;
v___y_15135_ = v___x_15164_;
v___y_15136_ = v___x_15170_;
goto v___jp_15126_;
}
}
}
v___jp_15018_:
{
float v___x_15025_; lean_object* v___x_15026_; float v___x_15027_; float v___x_15028_; float v___x_15029_; float v___x_15030_; 
v___x_15025_ = lean_float32_of_bits(v___y_15024_);
v___x_15026_ = lean_nat_add(v_t_15015_, v___y_15023_);
lean_dec(v_t_15015_);
v___x_15027_ = lean_float32_mul(v___x_15025_, v___y_15022_);
v___x_15028_ = lean_float32_add(v___y_15020_, v___x_15027_);
v___x_15029_ = lean_float32_mul(v___x_15025_, v___y_15021_);
v___x_15030_ = lean_float32_add(v___y_15019_, v___x_15029_);
v_t_15015_ = v___x_15026_;
v_s0_15016_ = v___x_15028_;
v_s1_15017_ = v___x_15030_;
goto _start;
}
v___jp_15032_:
{
float v___x_15038_; float v___x_15039_; float v___x_15040_; float v___x_15041_; float v___x_15042_; lean_object* v___x_15043_; 
v___x_15038_ = lean_float32_of_bits(v___y_15037_);
v___x_15039_ = lean_float32_mul(v___x_15038_, v___y_15035_);
v___x_15040_ = lean_float32_add(v___y_15033_, v___x_15039_);
v___x_15041_ = lean_float32_mul(v___x_15038_, v___y_15036_);
v___x_15042_ = lean_float32_add(v___y_15034_, v___x_15041_);
v___x_15043_ = lean_alloc_ctor(0, 0, 8);
lean_ctor_set_float32(v___x_15043_, 0, v___x_15040_);
lean_ctor_set_float32(v___x_15043_, 4, v___x_15042_);
return v___x_15043_;
}
}
}
