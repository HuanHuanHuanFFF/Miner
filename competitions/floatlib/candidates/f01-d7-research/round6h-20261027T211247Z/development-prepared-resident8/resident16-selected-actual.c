LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_wordLoop___redArg(size_t v_count_18992_, lean_object* v_A_18993_, lean_object* v_B_18994_, size_t v_k_18995_, float v_q00_18996_, float v_q10_18997_, float v_q20_18998_, float v_q30_18999_, float v_q01_19000_, float v_q11_19001_, float v_q21_19002_, float v_q31_19003_, float v_q02_19004_, float v_q12_19005_, float v_q22_19006_, float v_q32_19007_, float v_q03_19008_, float v_q13_19009_, float v_q23_19010_, float v_q33_19011_){
_start:
{
uint8_t v___x_19012_; 
v___x_19012_ = lean_usize_dec_lt(v_k_18995_, v_count_18992_);
if (v___x_19012_ == 0)
{
lean_object* v___x_19013_; 
v___x_19013_ = lean_alloc_ctor(0, 0, 64);
lean_ctor_set_float32(v___x_19013_, 0, v_q00_18996_);
lean_ctor_set_float32(v___x_19013_, 4, v_q10_18997_);
lean_ctor_set_float32(v___x_19013_, 8, v_q20_18998_);
lean_ctor_set_float32(v___x_19013_, 12, v_q30_18999_);
lean_ctor_set_float32(v___x_19013_, 16, v_q01_19000_);
lean_ctor_set_float32(v___x_19013_, 20, v_q11_19001_);
lean_ctor_set_float32(v___x_19013_, 24, v_q21_19002_);
lean_ctor_set_float32(v___x_19013_, 28, v_q31_19003_);
lean_ctor_set_float32(v___x_19013_, 32, v_q02_19004_);
lean_ctor_set_float32(v___x_19013_, 36, v_q12_19005_);
lean_ctor_set_float32(v___x_19013_, 40, v_q22_19006_);
lean_ctor_set_float32(v___x_19013_, 44, v_q32_19007_);
lean_ctor_set_float32(v___x_19013_, 48, v_q03_19008_);
lean_ctor_set_float32(v___x_19013_, 52, v_q13_19009_);
lean_ctor_set_float32(v___x_19013_, 56, v_q23_19010_);
lean_ctor_set_float32(v___x_19013_, 60, v_q33_19011_);
return v___x_19013_;
}
else
{
lean_object* v_a_19014_; float v_r0_19015_; float v_r1_19016_; float v_r2_19017_; float v_r3_19018_; lean_object* v_b_19019_; float v_s0_19020_; float v_s1_19021_; float v_s2_19022_; float v_s3_19023_; size_t v___x_19024_; size_t v___x_19025_; float v___x_19026_; float v___x_19027_; float v___x_19028_; float v___x_19029_; float v___x_19030_; float v___x_19031_; float v___x_19032_; float v___x_19033_; float v___x_19034_; float v___x_19035_; float v___x_19036_; float v___x_19037_; float v___x_19038_; float v___x_19039_; float v___x_19040_; float v___x_19041_; float v___x_19042_; float v___x_19043_; float v___x_19044_; float v___x_19045_; float v___x_19046_; float v___x_19047_; float v___x_19048_; float v___x_19049_; float v___x_19050_; float v___x_19051_; float v___x_19052_; float v___x_19053_; float v___x_19054_; float v___x_19055_; float v___x_19056_; float v___x_19057_; 
v_a_19014_ = lean_array_uget_borrowed(v_A_18993_, v_k_18995_);
v_r0_19015_ = lean_ctor_get_float32(v_a_19014_, 0);
v_r1_19016_ = lean_ctor_get_float32(v_a_19014_, 4);
v_r2_19017_ = lean_ctor_get_float32(v_a_19014_, 8);
v_r3_19018_ = lean_ctor_get_float32(v_a_19014_, 12);
v_b_19019_ = lean_array_uget_borrowed(v_B_18994_, v_k_18995_);
v_s0_19020_ = lean_ctor_get_float32(v_b_19019_, 0);
v_s1_19021_ = lean_ctor_get_float32(v_b_19019_, 4);
v_s2_19022_ = lean_ctor_get_float32(v_b_19019_, 8);
v_s3_19023_ = lean_ctor_get_float32(v_b_19019_, 12);
v___x_19024_ = ((size_t)1ULL);
v___x_19025_ = lean_usize_add(v_k_18995_, v___x_19024_);
v___x_19026_ = lean_float32_mul(v_r0_19015_, v_s0_19020_);
v___x_19027_ = lean_float32_add(v_q00_18996_, v___x_19026_);
v___x_19028_ = lean_float32_mul(v_r1_19016_, v_s0_19020_);
v___x_19029_ = lean_float32_add(v_q10_18997_, v___x_19028_);
v___x_19030_ = lean_float32_mul(v_r2_19017_, v_s0_19020_);
v___x_19031_ = lean_float32_add(v_q20_18998_, v___x_19030_);
v___x_19032_ = lean_float32_mul(v_r3_19018_, v_s0_19020_);
v___x_19033_ = lean_float32_add(v_q30_18999_, v___x_19032_);
v___x_19034_ = lean_float32_mul(v_r0_19015_, v_s1_19021_);
v___x_19035_ = lean_float32_add(v_q01_19000_, v___x_19034_);
v___x_19036_ = lean_float32_mul(v_r1_19016_, v_s1_19021_);
v___x_19037_ = lean_float32_add(v_q11_19001_, v___x_19036_);
v___x_19038_ = lean_float32_mul(v_r2_19017_, v_s1_19021_);
v___x_19039_ = lean_float32_add(v_q21_19002_, v___x_19038_);
v___x_19040_ = lean_float32_mul(v_r3_19018_, v_s1_19021_);
v___x_19041_ = lean_float32_add(v_q31_19003_, v___x_19040_);
v___x_19042_ = lean_float32_mul(v_r0_19015_, v_s2_19022_);
v___x_19043_ = lean_float32_add(v_q02_19004_, v___x_19042_);
v___x_19044_ = lean_float32_mul(v_r1_19016_, v_s2_19022_);
v___x_19045_ = lean_float32_add(v_q12_19005_, v___x_19044_);
v___x_19046_ = lean_float32_mul(v_r2_19017_, v_s2_19022_);
v___x_19047_ = lean_float32_add(v_q22_19006_, v___x_19046_);
v___x_19048_ = lean_float32_mul(v_r3_19018_, v_s2_19022_);
v___x_19049_ = lean_float32_add(v_q32_19007_, v___x_19048_);
v___x_19050_ = lean_float32_mul(v_r0_19015_, v_s3_19023_);
v___x_19051_ = lean_float32_add(v_q03_19008_, v___x_19050_);
v___x_19052_ = lean_float32_mul(v_r1_19016_, v_s3_19023_);
v___x_19053_ = lean_float32_add(v_q13_19009_, v___x_19052_);
v___x_19054_ = lean_float32_mul(v_r2_19017_, v_s3_19023_);
v___x_19055_ = lean_float32_add(v_q23_19010_, v___x_19054_);
v___x_19056_ = lean_float32_mul(v_r3_19018_, v_s3_19023_);
v___x_19057_ = lean_float32_add(v_q33_19011_, v___x_19056_);
v_k_18995_ = v___x_19025_;
v_q00_18996_ = v___x_19027_;
v_q10_18997_ = v___x_19029_;
v_q20_18998_ = v___x_19031_;
v_q30_18999_ = v___x_19033_;
v_q01_19000_ = v___x_19035_;
v_q11_19001_ = v___x_19037_;
v_q21_19002_ = v___x_19039_;
v_q31_19003_ = v___x_19041_;
v_q02_19004_ = v___x_19043_;
v_q12_19005_ = v___x_19045_;
v_q22_19006_ = v___x_19047_;
v_q32_19007_ = v___x_19049_;
v_q03_19008_ = v___x_19051_;
v_q13_19009_ = v___x_19053_;
v_q23_19010_ = v___x_19055_;
v_q33_19011_ = v___x_19057_;
goto _start;
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_runDot___redArg(lean_object* v_n_19162_, lean_object* v_A_19163_, lean_object* v_B_19164_){
_start:
{
size_t v___x_19165_; size_t v___x_19166_; float v___x_19167_; lean_object* v___x_19168_; 
v___x_19165_ = lean_usize_of_nat(v_n_19162_);
v___x_19166_ = ((size_t)0ULL);
v___x_19167_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_19168_ = lp_competition_Submission_R22Resident16_wordLoop___redArg(v___x_19165_, v_A_19163_, v_B_19164_, v___x_19166_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_, v___x_19167_);
return v___x_19168_;
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_tile___redArg(lean_object* v_p_19185_, lean_object* v_n_19186_, lean_object* v_baseA_19187_, lean_object* v_baseB_19188_, lean_object* v_valid_19189_, lean_object* v_A_19190_, lean_object* v_B_19191_, lean_object* v_PA_19192_, lean_object* v_PB_19193_){
_start:
{
lean_object* v_q_19194_; float v_q00_19195_; float v_q10_19196_; float v_q20_19197_; float v_q30_19198_; float v_q01_19199_; float v_q11_19200_; float v_q21_19201_; float v_q31_19202_; float v_q02_19203_; float v_q12_19204_; float v_q22_19205_; float v_q32_19206_; float v_q03_19207_; float v_q13_19208_; float v_q23_19209_; float v_q33_19210_; lean_object* v___x_19212_; uint8_t v_isShared_19213_; uint8_t v_isSharedCheck_19381_; 
v_q_19194_ = lp_competition_Submission_R22Resident16_runDot___redArg(v_n_19186_, v_PA_19192_, v_PB_19193_);
v_q00_19195_ = lean_ctor_get_float32(v_q_19194_, 0);
v_q10_19196_ = lean_ctor_get_float32(v_q_19194_, 4);
v_q20_19197_ = lean_ctor_get_float32(v_q_19194_, 8);
v_q30_19198_ = lean_ctor_get_float32(v_q_19194_, 12);
v_q01_19199_ = lean_ctor_get_float32(v_q_19194_, 16);
v_q11_19200_ = lean_ctor_get_float32(v_q_19194_, 20);
v_q21_19201_ = lean_ctor_get_float32(v_q_19194_, 24);
v_q31_19202_ = lean_ctor_get_float32(v_q_19194_, 28);
v_q02_19203_ = lean_ctor_get_float32(v_q_19194_, 32);
v_q12_19204_ = lean_ctor_get_float32(v_q_19194_, 36);
v_q22_19205_ = lean_ctor_get_float32(v_q_19194_, 40);
v_q32_19206_ = lean_ctor_get_float32(v_q_19194_, 44);
v_q03_19207_ = lean_ctor_get_float32(v_q_19194_, 48);
v_q13_19208_ = lean_ctor_get_float32(v_q_19194_, 52);
v_q23_19209_ = lean_ctor_get_float32(v_q_19194_, 56);
v_q33_19210_ = lean_ctor_get_float32(v_q_19194_, 60);
v_isSharedCheck_19381_ = !lean_is_exclusive(v_q_19194_);
if (v_isSharedCheck_19381_ == 0)
{
v___x_19212_ = v_q_19194_;
v_isShared_19213_ = v_isSharedCheck_19381_;
goto v_resetjp_19211_;
}
else
{
lean_dec(v_q_19194_);
v___x_19212_ = lean_box(0);
v_isShared_19213_ = v_isSharedCheck_19381_;
goto v_resetjp_19211_;
}
v_resetjp_19211_:
{
lean_object* v___x_19214_; uint32_t v_w00_19215_; lean_object* v___x_19216_; uint32_t v_w10_19217_; lean_object* v___x_19218_; lean_object* v___x_19219_; lean_object* v___x_19220_; uint32_t v_w20_19221_; lean_object* v___x_19222_; lean_object* v___x_19223_; lean_object* v___x_19224_; uint32_t v_w30_19225_; uint8_t v___x_19226_; uint8_t v___x_19227_; uint8_t v___x_19228_; lean_object* v___y_19230_; lean_object* v___y_19231_; lean_object* v___y_19232_; lean_object* v___y_19233_; lean_object* v___y_19234_; lean_object* v___y_19235_; lean_object* v___y_19236_; lean_object* v___y_19237_; lean_object* v___y_19238_; lean_object* v___y_19239_; lean_object* v___y_19240_; lean_object* v___y_19273_; lean_object* v___y_19274_; lean_object* v___y_19275_; lean_object* v___y_19276_; lean_object* v___y_19277_; lean_object* v___y_19278_; lean_object* v___y_19279_; lean_object* v___y_19280_; lean_object* v___y_19281_; lean_object* v___y_19282_; lean_object* v___y_19288_; lean_object* v___y_19289_; lean_object* v___y_19290_; lean_object* v___y_19291_; lean_object* v___y_19292_; lean_object* v___y_19293_; lean_object* v___y_19294_; lean_object* v___y_19295_; lean_object* v___y_19296_; lean_object* v___y_19302_; lean_object* v___y_19303_; lean_object* v___y_19304_; lean_object* v___y_19305_; lean_object* v___y_19306_; lean_object* v___y_19307_; lean_object* v___y_19308_; lean_object* v___y_19309_; lean_object* v___y_19315_; lean_object* v___y_19316_; lean_object* v___y_19317_; lean_object* v___y_19318_; lean_object* v___y_19319_; lean_object* v___y_19320_; lean_object* v___y_19321_; lean_object* v___y_19327_; lean_object* v___y_19328_; lean_object* v___y_19329_; lean_object* v___y_19330_; lean_object* v___y_19331_; lean_object* v___y_19332_; lean_object* v___y_19338_; lean_object* v___y_19339_; lean_object* v___y_19340_; lean_object* v___y_19341_; lean_object* v___y_19342_; lean_object* v___y_19348_; lean_object* v___y_19349_; lean_object* v___y_19350_; lean_object* v___y_19351_; lean_object* v___y_19357_; lean_object* v___y_19358_; lean_object* v___y_19359_; lean_object* v___y_19365_; lean_object* v___y_19366_; lean_object* v___y_19372_; 
v___x_19214_ = lean_unsigned_to_nat(1u);
v_w00_19215_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v_baseA_19187_, v_baseB_19188_, v_p_19185_, v_A_19190_, v_B_19191_, v_q00_19195_);
v___x_19216_ = lean_nat_add(v_baseA_19187_, v_n_19186_);
v_w10_19217_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19216_, v_baseB_19188_, v_p_19185_, v_A_19190_, v_B_19191_, v_q10_19196_);
v___x_19218_ = lean_unsigned_to_nat(2u);
v___x_19219_ = lean_nat_mul(v___x_19218_, v_n_19186_);
v___x_19220_ = lean_nat_add(v_baseA_19187_, v___x_19219_);
lean_dec(v___x_19219_);
v_w20_19221_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19220_, v_baseB_19188_, v_p_19185_, v_A_19190_, v_B_19191_, v_q20_19197_);
v___x_19222_ = lean_unsigned_to_nat(3u);
v___x_19223_ = lean_nat_mul(v___x_19222_, v_n_19186_);
v___x_19224_ = lean_nat_add(v_baseA_19187_, v___x_19223_);
lean_dec(v___x_19223_);
v_w30_19225_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19224_, v_baseB_19188_, v_p_19185_, v_A_19190_, v_B_19191_, v_q30_19198_);
v___x_19226_ = lean_nat_dec_lt(v___x_19214_, v_valid_19189_);
v___x_19227_ = lean_nat_dec_lt(v___x_19218_, v_valid_19189_);
v___x_19228_ = lean_nat_dec_lt(v___x_19222_, v_valid_19189_);
if (v___x_19226_ == 0)
{
lean_object* v___x_19377_; 
v___x_19377_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19372_ = v___x_19377_;
goto v___jp_19371_;
}
else
{
lean_object* v___x_19378_; uint32_t v___x_19379_; lean_object* v___x_19380_; 
v___x_19378_ = lean_nat_add(v_baseB_19188_, v___x_19214_);
v___x_19379_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v_baseA_19187_, v___x_19378_, v_p_19185_, v_A_19190_, v_B_19191_, v_q01_19199_);
lean_dec(v___x_19378_);
v___x_19380_ = lean_box_uint32(v___x_19379_);
v___y_19372_ = v___x_19380_;
goto v___jp_19371_;
}
v___jp_19229_:
{
if (v___x_19228_ == 0)
{
uint32_t v___x_19241_; lean_object* v___x_19243_; 
lean_dec(v___x_19224_);
v___x_19241_ = 0;
if (v_isShared_19213_ == 0)
{
v___x_19243_ = v___x_19212_;
goto v_reusejp_19242_;
}
else
{
lean_object* v_reuseFailAlloc_19255_; 
v_reuseFailAlloc_19255_ = lean_alloc_ctor(0, 0, 64);
v___x_19243_ = v_reuseFailAlloc_19255_;
goto v_reusejp_19242_;
}
v_reusejp_19242_:
{
uint32_t v___x_19244_; uint32_t v___x_19245_; uint32_t v___x_19246_; uint32_t v___x_19247_; uint32_t v___x_19248_; uint32_t v___x_19249_; uint32_t v___x_19250_; uint32_t v___x_19251_; uint32_t v___x_19252_; uint32_t v___x_19253_; uint32_t v___x_19254_; 
lean_ctor_set_uint32(v___x_19243_, 0, v_w00_19215_);
lean_ctor_set_uint32(v___x_19243_, 4, v_w10_19217_);
lean_ctor_set_uint32(v___x_19243_, 8, v_w20_19221_);
lean_ctor_set_uint32(v___x_19243_, 12, v_w30_19225_);
v___x_19244_ = lean_unbox_uint32(v___y_19233_);
lean_dec(v___y_19233_);
lean_ctor_set_uint32(v___x_19243_, 16, v___x_19244_);
v___x_19245_ = lean_unbox_uint32(v___y_19234_);
lean_dec(v___y_19234_);
lean_ctor_set_uint32(v___x_19243_, 20, v___x_19245_);
v___x_19246_ = lean_unbox_uint32(v___y_19237_);
lean_dec(v___y_19237_);
lean_ctor_set_uint32(v___x_19243_, 24, v___x_19246_);
v___x_19247_ = lean_unbox_uint32(v___y_19239_);
lean_dec(v___y_19239_);
lean_ctor_set_uint32(v___x_19243_, 28, v___x_19247_);
v___x_19248_ = lean_unbox_uint32(v___y_19235_);
lean_dec(v___y_19235_);
lean_ctor_set_uint32(v___x_19243_, 32, v___x_19248_);
v___x_19249_ = lean_unbox_uint32(v___y_19238_);
lean_dec(v___y_19238_);
lean_ctor_set_uint32(v___x_19243_, 36, v___x_19249_);
v___x_19250_ = lean_unbox_uint32(v___y_19231_);
lean_dec(v___y_19231_);
lean_ctor_set_uint32(v___x_19243_, 40, v___x_19250_);
v___x_19251_ = lean_unbox_uint32(v___y_19230_);
lean_dec(v___y_19230_);
lean_ctor_set_uint32(v___x_19243_, 44, v___x_19251_);
v___x_19252_ = lean_unbox_uint32(v___y_19236_);
lean_dec(v___y_19236_);
lean_ctor_set_uint32(v___x_19243_, 48, v___x_19252_);
v___x_19253_ = lean_unbox_uint32(v___y_19232_);
lean_dec(v___y_19232_);
lean_ctor_set_uint32(v___x_19243_, 52, v___x_19253_);
v___x_19254_ = lean_unbox_uint32(v___y_19240_);
lean_dec(v___y_19240_);
lean_ctor_set_uint32(v___x_19243_, 56, v___x_19254_);
lean_ctor_set_uint32(v___x_19243_, 60, v___x_19241_);
return v___x_19243_;
}
}
else
{
lean_object* v___x_19256_; uint32_t v___x_19257_; lean_object* v___x_19259_; 
v___x_19256_ = lean_nat_add(v_baseB_19188_, v___x_19222_);
v___x_19257_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19224_, v___x_19256_, v_p_19185_, v_A_19190_, v_B_19191_, v_q33_19210_);
lean_dec(v___x_19256_);
lean_dec(v___x_19224_);
if (v_isShared_19213_ == 0)
{
v___x_19259_ = v___x_19212_;
goto v_reusejp_19258_;
}
else
{
lean_object* v_reuseFailAlloc_19271_; 
v_reuseFailAlloc_19271_ = lean_alloc_ctor(0, 0, 64);
v___x_19259_ = v_reuseFailAlloc_19271_;
goto v_reusejp_19258_;
}
v_reusejp_19258_:
{
uint32_t v___x_19260_; uint32_t v___x_19261_; uint32_t v___x_19262_; uint32_t v___x_19263_; uint32_t v___x_19264_; uint32_t v___x_19265_; uint32_t v___x_19266_; uint32_t v___x_19267_; uint32_t v___x_19268_; uint32_t v___x_19269_; uint32_t v___x_19270_; 
lean_ctor_set_uint32(v___x_19259_, 0, v_w00_19215_);
lean_ctor_set_uint32(v___x_19259_, 4, v_w10_19217_);
lean_ctor_set_uint32(v___x_19259_, 8, v_w20_19221_);
lean_ctor_set_uint32(v___x_19259_, 12, v_w30_19225_);
v___x_19260_ = lean_unbox_uint32(v___y_19233_);
lean_dec(v___y_19233_);
lean_ctor_set_uint32(v___x_19259_, 16, v___x_19260_);
v___x_19261_ = lean_unbox_uint32(v___y_19234_);
lean_dec(v___y_19234_);
lean_ctor_set_uint32(v___x_19259_, 20, v___x_19261_);
v___x_19262_ = lean_unbox_uint32(v___y_19237_);
lean_dec(v___y_19237_);
lean_ctor_set_uint32(v___x_19259_, 24, v___x_19262_);
v___x_19263_ = lean_unbox_uint32(v___y_19239_);
lean_dec(v___y_19239_);
lean_ctor_set_uint32(v___x_19259_, 28, v___x_19263_);
v___x_19264_ = lean_unbox_uint32(v___y_19235_);
lean_dec(v___y_19235_);
lean_ctor_set_uint32(v___x_19259_, 32, v___x_19264_);
v___x_19265_ = lean_unbox_uint32(v___y_19238_);
lean_dec(v___y_19238_);
lean_ctor_set_uint32(v___x_19259_, 36, v___x_19265_);
v___x_19266_ = lean_unbox_uint32(v___y_19231_);
lean_dec(v___y_19231_);
lean_ctor_set_uint32(v___x_19259_, 40, v___x_19266_);
v___x_19267_ = lean_unbox_uint32(v___y_19230_);
lean_dec(v___y_19230_);
lean_ctor_set_uint32(v___x_19259_, 44, v___x_19267_);
v___x_19268_ = lean_unbox_uint32(v___y_19236_);
lean_dec(v___y_19236_);
lean_ctor_set_uint32(v___x_19259_, 48, v___x_19268_);
v___x_19269_ = lean_unbox_uint32(v___y_19232_);
lean_dec(v___y_19232_);
lean_ctor_set_uint32(v___x_19259_, 52, v___x_19269_);
v___x_19270_ = lean_unbox_uint32(v___y_19240_);
lean_dec(v___y_19240_);
lean_ctor_set_uint32(v___x_19259_, 56, v___x_19270_);
lean_ctor_set_uint32(v___x_19259_, 60, v___x_19257_);
return v___x_19259_;
}
}
}
v___jp_19272_:
{
if (v___x_19228_ == 0)
{
lean_object* v___x_19283_; 
lean_dec(v___x_19220_);
v___x_19283_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19230_ = v___y_19274_;
v___y_19231_ = v___y_19273_;
v___y_19232_ = v___y_19282_;
v___y_19233_ = v___y_19275_;
v___y_19234_ = v___y_19276_;
v___y_19235_ = v___y_19277_;
v___y_19236_ = v___y_19278_;
v___y_19237_ = v___y_19279_;
v___y_19238_ = v___y_19280_;
v___y_19239_ = v___y_19281_;
v___y_19240_ = v___x_19283_;
goto v___jp_19229_;
}
else
{
lean_object* v___x_19284_; uint32_t v___x_19285_; lean_object* v___x_19286_; 
v___x_19284_ = lean_nat_add(v_baseB_19188_, v___x_19222_);
v___x_19285_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19220_, v___x_19284_, v_p_19185_, v_A_19190_, v_B_19191_, v_q23_19209_);
lean_dec(v___x_19284_);
lean_dec(v___x_19220_);
v___x_19286_ = lean_box_uint32(v___x_19285_);
v___y_19230_ = v___y_19274_;
v___y_19231_ = v___y_19273_;
v___y_19232_ = v___y_19282_;
v___y_19233_ = v___y_19275_;
v___y_19234_ = v___y_19276_;
v___y_19235_ = v___y_19277_;
v___y_19236_ = v___y_19278_;
v___y_19237_ = v___y_19279_;
v___y_19238_ = v___y_19280_;
v___y_19239_ = v___y_19281_;
v___y_19240_ = v___x_19286_;
goto v___jp_19229_;
}
}
v___jp_19287_:
{
if (v___x_19228_ == 0)
{
lean_object* v___x_19297_; 
lean_dec(v___x_19216_);
v___x_19297_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19273_ = v___y_19289_;
v___y_19274_ = v___y_19288_;
v___y_19275_ = v___y_19290_;
v___y_19276_ = v___y_19291_;
v___y_19277_ = v___y_19292_;
v___y_19278_ = v___y_19296_;
v___y_19279_ = v___y_19293_;
v___y_19280_ = v___y_19294_;
v___y_19281_ = v___y_19295_;
v___y_19282_ = v___x_19297_;
goto v___jp_19272_;
}
else
{
lean_object* v___x_19298_; uint32_t v___x_19299_; lean_object* v___x_19300_; 
v___x_19298_ = lean_nat_add(v_baseB_19188_, v___x_19222_);
v___x_19299_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19216_, v___x_19298_, v_p_19185_, v_A_19190_, v_B_19191_, v_q13_19208_);
lean_dec(v___x_19298_);
lean_dec(v___x_19216_);
v___x_19300_ = lean_box_uint32(v___x_19299_);
v___y_19273_ = v___y_19289_;
v___y_19274_ = v___y_19288_;
v___y_19275_ = v___y_19290_;
v___y_19276_ = v___y_19291_;
v___y_19277_ = v___y_19292_;
v___y_19278_ = v___y_19296_;
v___y_19279_ = v___y_19293_;
v___y_19280_ = v___y_19294_;
v___y_19281_ = v___y_19295_;
v___y_19282_ = v___x_19300_;
goto v___jp_19272_;
}
}
v___jp_19301_:
{
if (v___x_19228_ == 0)
{
lean_object* v___x_19310_; 
v___x_19310_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19288_ = v___y_19309_;
v___y_19289_ = v___y_19302_;
v___y_19290_ = v___y_19303_;
v___y_19291_ = v___y_19304_;
v___y_19292_ = v___y_19305_;
v___y_19293_ = v___y_19306_;
v___y_19294_ = v___y_19307_;
v___y_19295_ = v___y_19308_;
v___y_19296_ = v___x_19310_;
goto v___jp_19287_;
}
else
{
lean_object* v___x_19311_; uint32_t v___x_19312_; lean_object* v___x_19313_; 
v___x_19311_ = lean_nat_add(v_baseB_19188_, v___x_19222_);
v___x_19312_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v_baseA_19187_, v___x_19311_, v_p_19185_, v_A_19190_, v_B_19191_, v_q03_19207_);
lean_dec(v___x_19311_);
v___x_19313_ = lean_box_uint32(v___x_19312_);
v___y_19288_ = v___y_19309_;
v___y_19289_ = v___y_19302_;
v___y_19290_ = v___y_19303_;
v___y_19291_ = v___y_19304_;
v___y_19292_ = v___y_19305_;
v___y_19293_ = v___y_19306_;
v___y_19294_ = v___y_19307_;
v___y_19295_ = v___y_19308_;
v___y_19296_ = v___x_19313_;
goto v___jp_19287_;
}
}
v___jp_19314_:
{
if (v___x_19227_ == 0)
{
lean_object* v___x_19322_; 
v___x_19322_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19302_ = v___y_19321_;
v___y_19303_ = v___y_19315_;
v___y_19304_ = v___y_19316_;
v___y_19305_ = v___y_19317_;
v___y_19306_ = v___y_19318_;
v___y_19307_ = v___y_19319_;
v___y_19308_ = v___y_19320_;
v___y_19309_ = v___x_19322_;
goto v___jp_19301_;
}
else
{
lean_object* v___x_19323_; uint32_t v___x_19324_; lean_object* v___x_19325_; 
v___x_19323_ = lean_nat_add(v_baseB_19188_, v___x_19218_);
v___x_19324_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19224_, v___x_19323_, v_p_19185_, v_A_19190_, v_B_19191_, v_q32_19206_);
lean_dec(v___x_19323_);
v___x_19325_ = lean_box_uint32(v___x_19324_);
v___y_19302_ = v___y_19321_;
v___y_19303_ = v___y_19315_;
v___y_19304_ = v___y_19316_;
v___y_19305_ = v___y_19317_;
v___y_19306_ = v___y_19318_;
v___y_19307_ = v___y_19319_;
v___y_19308_ = v___y_19320_;
v___y_19309_ = v___x_19325_;
goto v___jp_19301_;
}
}
v___jp_19326_:
{
if (v___x_19227_ == 0)
{
lean_object* v___x_19333_; 
v___x_19333_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19315_ = v___y_19327_;
v___y_19316_ = v___y_19328_;
v___y_19317_ = v___y_19329_;
v___y_19318_ = v___y_19330_;
v___y_19319_ = v___y_19332_;
v___y_19320_ = v___y_19331_;
v___y_19321_ = v___x_19333_;
goto v___jp_19314_;
}
else
{
lean_object* v___x_19334_; uint32_t v___x_19335_; lean_object* v___x_19336_; 
v___x_19334_ = lean_nat_add(v_baseB_19188_, v___x_19218_);
v___x_19335_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19220_, v___x_19334_, v_p_19185_, v_A_19190_, v_B_19191_, v_q22_19205_);
lean_dec(v___x_19334_);
v___x_19336_ = lean_box_uint32(v___x_19335_);
v___y_19315_ = v___y_19327_;
v___y_19316_ = v___y_19328_;
v___y_19317_ = v___y_19329_;
v___y_19318_ = v___y_19330_;
v___y_19319_ = v___y_19332_;
v___y_19320_ = v___y_19331_;
v___y_19321_ = v___x_19336_;
goto v___jp_19314_;
}
}
v___jp_19337_:
{
if (v___x_19227_ == 0)
{
lean_object* v___x_19343_; 
v___x_19343_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19327_ = v___y_19338_;
v___y_19328_ = v___y_19339_;
v___y_19329_ = v___y_19342_;
v___y_19330_ = v___y_19340_;
v___y_19331_ = v___y_19341_;
v___y_19332_ = v___x_19343_;
goto v___jp_19326_;
}
else
{
lean_object* v___x_19344_; uint32_t v___x_19345_; lean_object* v___x_19346_; 
v___x_19344_ = lean_nat_add(v_baseB_19188_, v___x_19218_);
v___x_19345_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19216_, v___x_19344_, v_p_19185_, v_A_19190_, v_B_19191_, v_q12_19204_);
lean_dec(v___x_19344_);
v___x_19346_ = lean_box_uint32(v___x_19345_);
v___y_19327_ = v___y_19338_;
v___y_19328_ = v___y_19339_;
v___y_19329_ = v___y_19342_;
v___y_19330_ = v___y_19340_;
v___y_19331_ = v___y_19341_;
v___y_19332_ = v___x_19346_;
goto v___jp_19326_;
}
}
v___jp_19347_:
{
if (v___x_19227_ == 0)
{
lean_object* v___x_19352_; 
v___x_19352_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19338_ = v___y_19348_;
v___y_19339_ = v___y_19349_;
v___y_19340_ = v___y_19350_;
v___y_19341_ = v___y_19351_;
v___y_19342_ = v___x_19352_;
goto v___jp_19337_;
}
else
{
lean_object* v___x_19353_; uint32_t v___x_19354_; lean_object* v___x_19355_; 
v___x_19353_ = lean_nat_add(v_baseB_19188_, v___x_19218_);
v___x_19354_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v_baseA_19187_, v___x_19353_, v_p_19185_, v_A_19190_, v_B_19191_, v_q02_19203_);
lean_dec(v___x_19353_);
v___x_19355_ = lean_box_uint32(v___x_19354_);
v___y_19338_ = v___y_19348_;
v___y_19339_ = v___y_19349_;
v___y_19340_ = v___y_19350_;
v___y_19341_ = v___y_19351_;
v___y_19342_ = v___x_19355_;
goto v___jp_19337_;
}
}
v___jp_19356_:
{
if (v___x_19226_ == 0)
{
lean_object* v___x_19360_; 
v___x_19360_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19348_ = v___y_19357_;
v___y_19349_ = v___y_19358_;
v___y_19350_ = v___y_19359_;
v___y_19351_ = v___x_19360_;
goto v___jp_19347_;
}
else
{
lean_object* v___x_19361_; uint32_t v___x_19362_; lean_object* v___x_19363_; 
v___x_19361_ = lean_nat_add(v_baseB_19188_, v___x_19214_);
v___x_19362_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19224_, v___x_19361_, v_p_19185_, v_A_19190_, v_B_19191_, v_q31_19202_);
lean_dec(v___x_19361_);
v___x_19363_ = lean_box_uint32(v___x_19362_);
v___y_19348_ = v___y_19357_;
v___y_19349_ = v___y_19358_;
v___y_19350_ = v___y_19359_;
v___y_19351_ = v___x_19363_;
goto v___jp_19347_;
}
}
v___jp_19364_:
{
if (v___x_19226_ == 0)
{
lean_object* v___x_19367_; 
v___x_19367_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19357_ = v___y_19365_;
v___y_19358_ = v___y_19366_;
v___y_19359_ = v___x_19367_;
goto v___jp_19356_;
}
else
{
lean_object* v___x_19368_; uint32_t v___x_19369_; lean_object* v___x_19370_; 
v___x_19368_ = lean_nat_add(v_baseB_19188_, v___x_19214_);
v___x_19369_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19220_, v___x_19368_, v_p_19185_, v_A_19190_, v_B_19191_, v_q21_19201_);
lean_dec(v___x_19368_);
v___x_19370_ = lean_box_uint32(v___x_19369_);
v___y_19357_ = v___y_19365_;
v___y_19358_ = v___y_19366_;
v___y_19359_ = v___x_19370_;
goto v___jp_19356_;
}
}
v___jp_19371_:
{
if (v___x_19226_ == 0)
{
lean_object* v___x_19373_; 
v___x_19373_ = lp_competition_Submission_R22Resident16_tile___redArg___boxed__const__1;
v___y_19365_ = v___y_19372_;
v___y_19366_ = v___x_19373_;
goto v___jp_19364_;
}
else
{
lean_object* v___x_19374_; uint32_t v___x_19375_; lean_object* v___x_19376_; 
v___x_19374_ = lean_nat_add(v_baseB_19188_, v___x_19214_);
v___x_19375_ = lp_competition_Submission_Packed10_finish(v_n_19186_, v___x_19216_, v___x_19374_, v_p_19185_, v_A_19190_, v_B_19191_, v_q11_19200_);
lean_dec(v___x_19374_);
v___x_19376_ = lean_box_uint32(v___x_19375_);
v___y_19365_ = v___y_19372_;
v___y_19366_ = v___x_19376_;
goto v___jp_19364_;
}
}
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_tiles___redArg(lean_object* v_m_19445_, lean_object* v_n_19446_, lean_object* v_p_19447_, lean_object* v_A_19448_, lean_object* v_B_19449_, lean_object* v_PB_19450_, lean_object* v_b_19451_, lean_object* v_first_19452_){
_start:
{
lean_object* v___x_19453_; lean_object* v___x_19454_; lean_object* v_baseA_19455_; lean_object* v_PA_19456_; lean_object* v___f_19457_; lean_object* v___x_19458_; lean_object* v___x_19459_; 
v___x_19453_ = lean_nat_mul(v_b_19451_, v_m_19445_);
v___x_19454_ = lean_nat_add(v___x_19453_, v_first_19452_);
lean_dec(v___x_19453_);
v_baseA_19455_ = lean_nat_mul(v___x_19454_, v_n_19446_);
lean_dec(v___x_19454_);
lean_inc_ref(v_A_19448_);
lean_inc(v_baseA_19455_);
lean_inc(v_n_19446_);
v_PA_19456_ = lp_competition_Submission_R22Resident16_packA(v_n_19446_, v_baseA_19455_, v_A_19448_);
lean_inc(v_p_19447_);
v___f_19457_ = lean_alloc_closure((void*)(lp_competition_Submission_R22Resident16_tiles___redArg___lam__0___boxed), 9, 8);
lean_closure_set(v___f_19457_, 0, v_b_19451_);
lean_closure_set(v___f_19457_, 1, v_n_19446_);
lean_closure_set(v___f_19457_, 2, v_p_19447_);
lean_closure_set(v___f_19457_, 3, v_PB_19450_);
lean_closure_set(v___f_19457_, 4, v_baseA_19455_);
lean_closure_set(v___f_19457_, 5, v_A_19448_);
lean_closure_set(v___f_19457_, 6, v_B_19449_);
lean_closure_set(v___f_19457_, 7, v_PA_19456_);
v___x_19458_ = lp_competition_Submission_R22Resident16_groups(v_p_19447_);
lean_dec(v_p_19447_);
v___x_19459_ = l_Array_ofFn___redArg(v___x_19458_, v___f_19457_);
return v___x_19459_;
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_tiles___redArg___lam__0(lean_object* v_b_19414_, lean_object* v_n_19415_, lean_object* v_p_19416_, lean_object* v_PB_19417_, lean_object* v_baseA_19418_, lean_object* v_A_19419_, lean_object* v_B_19420_, lean_object* v_PA_19421_, lean_object* v_g_19422_){
_start:
{
lean_object* v___x_19423_; lean_object* v___x_19424_; lean_object* v___x_19425_; lean_object* v___x_19426_; lean_object* v___x_19427_; lean_object* v___y_19429_; lean_object* v___x_19433_; uint8_t v___x_19434_; 
v___x_19423_ = lean_nat_mul(v_b_19414_, v_n_19415_);
v___x_19424_ = lean_nat_mul(v___x_19423_, v_p_19416_);
lean_dec(v___x_19423_);
v___x_19425_ = lean_unsigned_to_nat(4u);
v___x_19426_ = lean_nat_mul(v___x_19425_, v_g_19422_);
v___x_19427_ = lean_nat_add(v___x_19424_, v___x_19426_);
lean_dec(v___x_19424_);
v___x_19433_ = lean_nat_sub(v_p_19416_, v___x_19426_);
lean_dec(v___x_19426_);
v___x_19434_ = lean_nat_dec_le(v___x_19425_, v___x_19433_);
if (v___x_19434_ == 0)
{
v___y_19429_ = v___x_19433_;
goto v___jp_19428_;
}
else
{
lean_dec(v___x_19433_);
v___y_19429_ = v___x_19425_;
goto v___jp_19428_;
}
v___jp_19428_:
{
lean_object* v___x_19430_; lean_object* v___x_19431_; lean_object* v___x_19432_; 
v___x_19430_ = lp_competition_Submission_R22Resident16_tileIndex___redArg(v_p_19416_, v_b_19414_, v_g_19422_);
v___x_19431_ = lean_array_fget_borrowed(v_PB_19417_, v___x_19430_);
lean_dec(v___x_19430_);
v___x_19432_ = lp_competition_Submission_R22Resident16_tile___redArg(v_p_19416_, v_n_19415_, v_baseA_19418_, v___x_19427_, v___y_19429_, v_A_19419_, v_B_19420_, v_PA_19421_, v___x_19431_);
lean_dec(v___y_19429_);
lean_dec(v___x_19427_);
return v___x_19432_;
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_rows4___redArg(lean_object* v_m_19801_, lean_object* v_n_19802_, lean_object* v_p_19803_, lean_object* v_A_19804_, lean_object* v_B_19805_, lean_object* v_PB_19806_, lean_object* v_b_19807_, lean_object* v_first_19808_, lean_object* v_out_19809_){
_start:
{
lean_object* v___x_19810_; uint8_t v___x_19811_; 
v___x_19810_ = lean_unsigned_to_nat(0u);
v___x_19811_ = lean_nat_dec_eq(v_p_19803_, v___x_19810_);
if (v___x_19811_ == 0)
{
lean_object* v_t_19812_; lean_object* v_out_19813_; lean_object* v_out_19814_; lean_object* v_out_19815_; lean_object* v___x_19816_; 
lean_inc(v_p_19803_);
v_t_19812_ = lp_competition_Submission_R22Resident16_tiles___redArg(v_m_19801_, v_n_19802_, v_p_19803_, v_A_19804_, v_B_19805_, v_PB_19806_, v_b_19807_, v_first_19808_);
v_out_19813_ = lp_competition_Fin_foldl_loop___at___00Submission_R22Resident16_rows4_spec__0(v_t_19812_, v_p_19803_, v_out_19809_, v___x_19810_);
v_out_19814_ = lp_competition_Fin_foldl_loop___at___00Submission_R22Resident16_rows4_spec__1(v_t_19812_, v_p_19803_, v_out_19813_, v___x_19810_);
v_out_19815_ = lp_competition_Fin_foldl_loop___at___00Submission_R22Resident16_rows4_spec__2(v_t_19812_, v_p_19803_, v_out_19814_, v___x_19810_);
v___x_19816_ = lp_competition_Fin_foldl_loop___at___00Submission_R22Resident16_rows4_spec__3(v_t_19812_, v_p_19803_, v_out_19815_, v___x_19810_);
lean_dec(v_p_19803_);
lean_dec_ref(v_t_19812_);
return v___x_19816_;
}
else
{
lean_dec(v_b_19807_);
lean_dec_ref(v_PB_19806_);
lean_dec_ref(v_B_19805_);
lean_dec_ref(v_A_19804_);
lean_dec(v_p_19803_);
lean_dec(v_n_19802_);
return v_out_19809_;
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_packA(lean_object* v_n_18805_, lean_object* v_base_18806_, lean_object* v_A_18807_){
_start:
{
lean_object* v___f_18808_; lean_object* v___x_18809_; 
lean_inc(v_n_18805_);
v___f_18808_ = lean_alloc_closure((void*)(lp_competition_Submission_R22Resident16_packA___lam__0___boxed), 4, 3);
lean_closure_set(v___f_18808_, 0, v_base_18806_);
lean_closure_set(v___f_18808_, 1, v_n_18805_);
lean_closure_set(v___f_18808_, 2, v_A_18807_);
v___x_18809_ = l_Array_ofFn___redArg(v_n_18805_, v___f_18808_);
return v___x_18809_;
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_packA___lam__0(lean_object* v_base_18749_, lean_object* v_n_18750_, lean_object* v_A_18751_, lean_object* v_k_18752_){
_start:
{
float v___y_18754_; float v___y_18755_; float v___y_18756_; uint32_t v___y_18757_; lean_object* v___x_18760_; uint32_t v___x_18761_; float v___y_18763_; float v___y_18764_; uint32_t v___y_18765_; float v___y_18776_; uint32_t v___y_18777_; uint32_t v___y_18788_; lean_object* v___x_18796_; uint8_t v___x_18797_; 
v___x_18760_ = lean_nat_add(v_base_18749_, v_k_18752_);
v___x_18761_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_18796_ = lean_array_get_size(v_A_18751_);
v___x_18797_ = lean_nat_dec_lt(v___x_18760_, v___x_18796_);
if (v___x_18797_ == 0)
{
lean_dec(v___x_18760_);
v___y_18788_ = v___x_18761_;
goto v___jp_18787_;
}
else
{
lean_object* v___x_18798_; uint32_t v___x_18799_; 
v___x_18798_ = lean_array_fget_borrowed(v_A_18751_, v___x_18760_);
lean_dec(v___x_18760_);
v___x_18799_ = lean_unbox_uint32(v___x_18798_);
v___y_18788_ = v___x_18799_;
goto v___jp_18787_;
}
v___jp_18753_:
{
float v___x_18758_; lean_object* v___x_18759_; 
v___x_18758_ = lean_float32_of_bits(v___y_18757_);
v___x_18759_ = lean_alloc_ctor(0, 0, 16);
lean_ctor_set_float32(v___x_18759_, 0, v___y_18756_);
lean_ctor_set_float32(v___x_18759_, 4, v___y_18755_);
lean_ctor_set_float32(v___x_18759_, 8, v___y_18754_);
lean_ctor_set_float32(v___x_18759_, 12, v___x_18758_);
return v___x_18759_;
}
v___jp_18762_:
{
float v___x_18766_; lean_object* v___x_18767_; lean_object* v___x_18768_; lean_object* v___x_18769_; lean_object* v___x_18770_; lean_object* v___x_18771_; uint8_t v___x_18772_; 
v___x_18766_ = lean_float32_of_bits(v___y_18765_);
v___x_18767_ = lean_unsigned_to_nat(3u);
v___x_18768_ = lean_nat_mul(v___x_18767_, v_n_18750_);
v___x_18769_ = lean_nat_add(v_base_18749_, v___x_18768_);
lean_dec(v___x_18768_);
v___x_18770_ = lean_nat_add(v___x_18769_, v_k_18752_);
lean_dec(v___x_18769_);
v___x_18771_ = lean_array_get_size(v_A_18751_);
v___x_18772_ = lean_nat_dec_lt(v___x_18770_, v___x_18771_);
if (v___x_18772_ == 0)
{
lean_dec(v___x_18770_);
v___y_18754_ = v___x_18766_;
v___y_18755_ = v___y_18763_;
v___y_18756_ = v___y_18764_;
v___y_18757_ = v___x_18761_;
goto v___jp_18753_;
}
else
{
lean_object* v___x_18773_; uint32_t v___x_18774_; 
v___x_18773_ = lean_array_fget_borrowed(v_A_18751_, v___x_18770_);
lean_dec(v___x_18770_);
v___x_18774_ = lean_unbox_uint32(v___x_18773_);
v___y_18754_ = v___x_18766_;
v___y_18755_ = v___y_18763_;
v___y_18756_ = v___y_18764_;
v___y_18757_ = v___x_18774_;
goto v___jp_18753_;
}
}
v___jp_18775_:
{
float v___x_18778_; lean_object* v___x_18779_; lean_object* v___x_18780_; lean_object* v___x_18781_; lean_object* v___x_18782_; lean_object* v___x_18783_; uint8_t v___x_18784_; 
v___x_18778_ = lean_float32_of_bits(v___y_18777_);
v___x_18779_ = lean_unsigned_to_nat(2u);
v___x_18780_ = lean_nat_mul(v___x_18779_, v_n_18750_);
v___x_18781_ = lean_nat_add(v_base_18749_, v___x_18780_);
lean_dec(v___x_18780_);
v___x_18782_ = lean_nat_add(v___x_18781_, v_k_18752_);
lean_dec(v___x_18781_);
v___x_18783_ = lean_array_get_size(v_A_18751_);
v___x_18784_ = lean_nat_dec_lt(v___x_18782_, v___x_18783_);
if (v___x_18784_ == 0)
{
lean_dec(v___x_18782_);
v___y_18763_ = v___x_18778_;
v___y_18764_ = v___y_18776_;
v___y_18765_ = v___x_18761_;
goto v___jp_18762_;
}
else
{
lean_object* v___x_18785_; uint32_t v___x_18786_; 
v___x_18785_ = lean_array_fget_borrowed(v_A_18751_, v___x_18782_);
lean_dec(v___x_18782_);
v___x_18786_ = lean_unbox_uint32(v___x_18785_);
v___y_18763_ = v___x_18778_;
v___y_18764_ = v___y_18776_;
v___y_18765_ = v___x_18786_;
goto v___jp_18762_;
}
}
v___jp_18787_:
{
float v___x_18789_; lean_object* v___x_18790_; lean_object* v___x_18791_; lean_object* v___x_18792_; uint8_t v___x_18793_; 
v___x_18789_ = lean_float32_of_bits(v___y_18788_);
v___x_18790_ = lean_nat_add(v_base_18749_, v_n_18750_);
v___x_18791_ = lean_nat_add(v___x_18790_, v_k_18752_);
lean_dec(v___x_18790_);
v___x_18792_ = lean_array_get_size(v_A_18751_);
v___x_18793_ = lean_nat_dec_lt(v___x_18791_, v___x_18792_);
if (v___x_18793_ == 0)
{
lean_dec(v___x_18791_);
v___y_18776_ = v___x_18789_;
v___y_18777_ = v___x_18761_;
goto v___jp_18775_;
}
else
{
lean_object* v___x_18794_; uint32_t v___x_18795_; 
v___x_18794_ = lean_array_fget_borrowed(v_A_18751_, v___x_18791_);
lean_dec(v___x_18791_);
v___x_18795_ = lean_unbox_uint32(v___x_18794_);
v___y_18776_ = v___x_18789_;
v___y_18777_ = v___x_18795_;
goto v___jp_18775_;
}
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_packBGroup(lean_object* v_n_18879_, lean_object* v_p_18880_, lean_object* v_base_18881_, lean_object* v_B_18882_, lean_object* v_valid_18883_){
_start:
{
lean_object* v___f_18884_; lean_object* v___x_18885_; 
v___f_18884_ = lean_alloc_closure((void*)(lp_competition_Submission_R22Resident16_packBGroup___lam__0___boxed), 5, 4);
lean_closure_set(v___f_18884_, 0, v_p_18880_);
lean_closure_set(v___f_18884_, 1, v_base_18881_);
lean_closure_set(v___f_18884_, 2, v_valid_18883_);
lean_closure_set(v___f_18884_, 3, v_B_18882_);
v___x_18885_ = l_Array_ofFn___redArg(v_n_18879_, v___f_18884_);
return v___x_18885_;
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_packBGroup___lam__0(lean_object* v_p_18810_, lean_object* v_base_18811_, lean_object* v_valid_18812_, lean_object* v_B_18813_, lean_object* v_k_18814_){
_start:
{
float v___y_18816_; float v___y_18817_; float v___y_18818_; uint32_t v___y_18819_; lean_object* v___x_18822_; lean_object* v_i_18823_; uint32_t v___x_18824_; float v___y_18826_; float v___y_18827_; float v___y_18828_; float v___y_18839_; float v___y_18840_; uint32_t v___y_18841_; float v___y_18844_; float v___y_18845_; float v___y_18855_; uint32_t v___y_18856_; uint32_t v___y_18859_; lean_object* v___x_18869_; uint8_t v___x_18870_; 
v___x_18822_ = lean_nat_mul(v_k_18814_, v_p_18810_);
v_i_18823_ = lean_nat_add(v_base_18811_, v___x_18822_);
lean_dec(v___x_18822_);
v___x_18824_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_18869_ = lean_array_get_size(v_B_18813_);
v___x_18870_ = lean_nat_dec_lt(v_i_18823_, v___x_18869_);
if (v___x_18870_ == 0)
{
v___y_18859_ = v___x_18824_;
goto v___jp_18858_;
}
else
{
lean_object* v___x_18871_; uint32_t v___x_18872_; 
v___x_18871_ = lean_array_fget_borrowed(v_B_18813_, v_i_18823_);
v___x_18872_ = lean_unbox_uint32(v___x_18871_);
v___y_18859_ = v___x_18872_;
goto v___jp_18858_;
}
v___jp_18815_:
{
float v___x_18820_; lean_object* v___x_18821_; 
v___x_18820_ = lean_float32_of_bits(v___y_18819_);
v___x_18821_ = lean_alloc_ctor(0, 0, 16);
lean_ctor_set_float32(v___x_18821_, 0, v___y_18817_);
lean_ctor_set_float32(v___x_18821_, 4, v___y_18816_);
lean_ctor_set_float32(v___x_18821_, 8, v___y_18818_);
lean_ctor_set_float32(v___x_18821_, 12, v___x_18820_);
return v___x_18821_;
}
v___jp_18825_:
{
lean_object* v___x_18829_; uint8_t v___x_18830_; 
v___x_18829_ = lean_unsigned_to_nat(3u);
v___x_18830_ = lean_nat_dec_lt(v___x_18829_, v_valid_18812_);
if (v___x_18830_ == 0)
{
float v___x_18831_; lean_object* v___x_18832_; 
lean_dec(v_i_18823_);
v___x_18831_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_18832_ = lean_alloc_ctor(0, 0, 16);
lean_ctor_set_float32(v___x_18832_, 0, v___y_18827_);
lean_ctor_set_float32(v___x_18832_, 4, v___y_18826_);
lean_ctor_set_float32(v___x_18832_, 8, v___y_18828_);
lean_ctor_set_float32(v___x_18832_, 12, v___x_18831_);
return v___x_18832_;
}
else
{
lean_object* v___x_18833_; lean_object* v___x_18834_; uint8_t v___x_18835_; 
v___x_18833_ = lean_nat_add(v_i_18823_, v___x_18829_);
lean_dec(v_i_18823_);
v___x_18834_ = lean_array_get_size(v_B_18813_);
v___x_18835_ = lean_nat_dec_lt(v___x_18833_, v___x_18834_);
if (v___x_18835_ == 0)
{
lean_dec(v___x_18833_);
v___y_18816_ = v___y_18826_;
v___y_18817_ = v___y_18827_;
v___y_18818_ = v___y_18828_;
v___y_18819_ = v___x_18824_;
goto v___jp_18815_;
}
else
{
lean_object* v___x_18836_; uint32_t v___x_18837_; 
v___x_18836_ = lean_array_fget_borrowed(v_B_18813_, v___x_18833_);
lean_dec(v___x_18833_);
v___x_18837_ = lean_unbox_uint32(v___x_18836_);
v___y_18816_ = v___y_18826_;
v___y_18817_ = v___y_18827_;
v___y_18818_ = v___y_18828_;
v___y_18819_ = v___x_18837_;
goto v___jp_18815_;
}
}
}
v___jp_18838_:
{
float v___x_18842_; 
v___x_18842_ = lean_float32_of_bits(v___y_18841_);
v___y_18826_ = v___y_18839_;
v___y_18827_ = v___y_18840_;
v___y_18828_ = v___x_18842_;
goto v___jp_18825_;
}
v___jp_18843_:
{
lean_object* v___x_18846_; uint8_t v___x_18847_; 
v___x_18846_ = lean_unsigned_to_nat(2u);
v___x_18847_ = lean_nat_dec_lt(v___x_18846_, v_valid_18812_);
if (v___x_18847_ == 0)
{
float v___x_18848_; 
v___x_18848_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___y_18826_ = v___y_18845_;
v___y_18827_ = v___y_18844_;
v___y_18828_ = v___x_18848_;
goto v___jp_18825_;
}
else
{
lean_object* v___x_18849_; lean_object* v___x_18850_; uint8_t v___x_18851_; 
v___x_18849_ = lean_nat_add(v_i_18823_, v___x_18846_);
v___x_18850_ = lean_array_get_size(v_B_18813_);
v___x_18851_ = lean_nat_dec_lt(v___x_18849_, v___x_18850_);
if (v___x_18851_ == 0)
{
lean_dec(v___x_18849_);
v___y_18839_ = v___y_18845_;
v___y_18840_ = v___y_18844_;
v___y_18841_ = v___x_18824_;
goto v___jp_18838_;
}
else
{
lean_object* v___x_18852_; uint32_t v___x_18853_; 
v___x_18852_ = lean_array_fget_borrowed(v_B_18813_, v___x_18849_);
lean_dec(v___x_18849_);
v___x_18853_ = lean_unbox_uint32(v___x_18852_);
v___y_18839_ = v___y_18845_;
v___y_18840_ = v___y_18844_;
v___y_18841_ = v___x_18853_;
goto v___jp_18838_;
}
}
}
v___jp_18854_:
{
float v___x_18857_; 
v___x_18857_ = lean_float32_of_bits(v___y_18856_);
v___y_18844_ = v___y_18855_;
v___y_18845_ = v___x_18857_;
goto v___jp_18843_;
}
v___jp_18858_:
{
float v___x_18860_; lean_object* v___x_18861_; uint8_t v___x_18862_; 
v___x_18860_ = lean_float32_of_bits(v___y_18859_);
v___x_18861_ = lean_unsigned_to_nat(1u);
v___x_18862_ = lean_nat_dec_lt(v___x_18861_, v_valid_18812_);
if (v___x_18862_ == 0)
{
float v___x_18863_; 
v___x_18863_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___y_18844_ = v___x_18860_;
v___y_18845_ = v___x_18863_;
goto v___jp_18843_;
}
else
{
lean_object* v___x_18864_; lean_object* v___x_18865_; uint8_t v___x_18866_; 
v___x_18864_ = lean_nat_add(v_i_18823_, v___x_18861_);
v___x_18865_ = lean_array_get_size(v_B_18813_);
v___x_18866_ = lean_nat_dec_lt(v___x_18864_, v___x_18865_);
if (v___x_18866_ == 0)
{
lean_dec(v___x_18864_);
v___y_18855_ = v___x_18860_;
v___y_18856_ = v___x_18824_;
goto v___jp_18854_;
}
else
{
lean_object* v___x_18867_; uint32_t v___x_18868_; 
v___x_18867_ = lean_array_fget_borrowed(v_B_18813_, v___x_18864_);
lean_dec(v___x_18864_);
v___x_18868_ = lean_unbox_uint32(v___x_18867_);
v___y_18855_ = v___x_18860_;
v___y_18856_ = v___x_18868_;
goto v___jp_18854_;
}
}
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_core___redArg(lean_object* v_batch_20098_, lean_object* v_m_20099_, lean_object* v_n_20100_, lean_object* v_p_20101_, lean_object* v_A_20102_, lean_object* v_B_20103_){
_start:
{
lean_object* v_PB_20104_; lean_object* v___x_20105_; 
lean_inc_ref(v_B_20103_);
lean_inc(v_p_20101_);
lean_inc(v_n_20100_);
v_PB_20104_ = lp_competition_Submission_R22Resident16_packBData(v_batch_20098_, v_n_20100_, v_p_20101_, v_B_20103_);
v___x_20105_ = lp_competition_Submission_R22Resident16_output___redArg(v_batch_20098_, v_m_20099_, v_n_20100_, v_p_20101_, v_A_20102_, v_B_20103_, v_PB_20104_);
return v___x_20105_;
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22Resident16_guarded(lean_object* v_batch_20129_, lean_object* v_m_20130_, lean_object* v_n_20131_, lean_object* v_p_20132_, lean_object* v_A_20133_, lean_object* v_B_20134_){
_start:
{
uint8_t v___y_20149_; lean_object* v___x_20159_; lean_object* v___x_20160_; uint8_t v___x_20161_; 
v___x_20159_ = lean_unsigned_to_nat(0u);
v___x_20160_ = lean_array_get_size(v_A_20133_);
v___x_20161_ = lean_nat_dec_lt(v___x_20159_, v___x_20160_);
if (v___x_20161_ == 0)
{
uint8_t v___x_20162_; 
v___x_20162_ = 1;
v___y_20149_ = v___x_20162_;
goto v___jp_20148_;
}
else
{
if (v___x_20161_ == 0)
{
v___y_20149_ = v___x_20161_;
goto v___jp_20148_;
}
else
{
size_t v___x_20163_; size_t v___x_20164_; uint8_t v___x_20165_; 
v___x_20163_ = ((size_t)0ULL);
v___x_20164_ = lean_usize_of_nat(v___x_20160_);
v___x_20165_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00Submission_bmm_spec__1(v_A_20133_, v___x_20163_, v___x_20164_);
if (v___x_20165_ == 0)
{
v___y_20149_ = v___x_20161_;
goto v___jp_20148_;
}
else
{
goto v___jp_20135_;
}
}
}
v___jp_20135_:
{
lean_object* v___x_20136_; uint8_t v___x_20137_; 
v___x_20136_ = lean_unsigned_to_nat(1u);
v___x_20137_ = lean_nat_dec_lt(v___x_20136_, v_n_20131_);
if (v___x_20137_ == 0)
{
lean_object* v___x_20138_; 
v___x_20138_ = lp_competition_Submission_bmm(v_batch_20129_, v_m_20130_, v_n_20131_, v_p_20132_, v_A_20133_, v_B_20134_);
return v___x_20138_;
}
else
{
lean_object* v___x_20139_; uint8_t v___x_20140_; 
v___x_20139_ = lean_unsigned_to_nat(4u);
v___x_20140_ = lean_nat_dec_le(v___x_20139_, v_m_20130_);
if (v___x_20140_ == 0)
{
lean_object* v___x_20141_; 
v___x_20141_ = lp_competition_Submission_bmm(v_batch_20129_, v_m_20130_, v_n_20131_, v_p_20132_, v_A_20133_, v_B_20134_);
return v___x_20141_;
}
else
{
uint8_t v___x_20142_; 
v___x_20142_ = lean_nat_dec_le(v___x_20139_, v_p_20132_);
if (v___x_20142_ == 0)
{
lean_object* v___x_20143_; 
v___x_20143_ = lp_competition_Submission_bmm(v_batch_20129_, v_m_20130_, v_n_20131_, v_p_20132_, v_A_20133_, v_B_20134_);
return v___x_20143_;
}
else
{
lean_object* v___x_20144_; uint8_t v___x_20145_; 
v___x_20144_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_20145_ = lean_nat_dec_lt(v_n_20131_, v___x_20144_);
if (v___x_20145_ == 0)
{
lean_object* v___x_20146_; 
v___x_20146_ = lp_competition_Submission_bmm(v_batch_20129_, v_m_20130_, v_n_20131_, v_p_20132_, v_A_20133_, v_B_20134_);
return v___x_20146_;
}
else
{
lean_object* v___x_20147_; 
v___x_20147_ = lp_competition_Submission_R22Resident16_core___redArg(v_batch_20129_, v_m_20130_, v_n_20131_, v_p_20132_, v_A_20133_, v_B_20134_);
lean_dec(v_m_20130_);
lean_dec(v_batch_20129_);
return v___x_20147_;
}
}
}
}
}
v___jp_20148_:
{
lean_object* v___x_20150_; lean_object* v___x_20151_; uint8_t v___x_20152_; 
v___x_20150_ = lean_unsigned_to_nat(0u);
v___x_20151_ = lean_array_get_size(v_B_20134_);
v___x_20152_ = lean_nat_dec_lt(v___x_20150_, v___x_20151_);
if (v___x_20152_ == 0)
{
lean_object* v___x_20153_; 
lean_dec_ref(v_B_20134_);
lean_dec_ref(v_A_20133_);
lean_dec(v_n_20131_);
v___x_20153_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_20129_, v_m_20130_, v_p_20132_);
lean_dec(v_p_20132_);
lean_dec(v_m_20130_);
lean_dec(v_batch_20129_);
return v___x_20153_;
}
else
{
if (v___x_20152_ == 0)
{
lean_object* v___x_20154_; 
lean_dec_ref(v_B_20134_);
lean_dec_ref(v_A_20133_);
lean_dec(v_n_20131_);
v___x_20154_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_20129_, v_m_20130_, v_p_20132_);
lean_dec(v_p_20132_);
lean_dec(v_m_20130_);
lean_dec(v_batch_20129_);
return v___x_20154_;
}
else
{
size_t v___x_20155_; size_t v___x_20156_; uint8_t v___x_20157_; 
v___x_20155_ = ((size_t)0ULL);
v___x_20156_ = lean_usize_of_nat(v___x_20151_);
v___x_20157_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00Submission_bmm_spec__0(v___y_20149_, v_B_20134_, v___x_20155_, v___x_20156_);
if (v___x_20157_ == 0)
{
lean_object* v___x_20158_; 
lean_dec_ref(v_B_20134_);
lean_dec_ref(v_A_20133_);
lean_dec(v_n_20131_);
v___x_20158_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_20129_, v_m_20130_, v_p_20132_);
lean_dec(v_p_20132_);
lean_dec(v_m_20130_);
lean_dec(v_batch_20129_);
return v___x_20158_;
}
else
{
goto v___jp_20135_;
}
}
}
}
}
}