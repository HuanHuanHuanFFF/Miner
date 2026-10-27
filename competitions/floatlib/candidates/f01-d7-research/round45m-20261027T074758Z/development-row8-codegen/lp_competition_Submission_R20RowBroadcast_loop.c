LEAN_EXPORT lean_object* lp_competition_Submission_R20RowBroadcast_loop(lean_object* v_n_15238_, lean_object* v_baseA_15239_, lean_object* v_A_15240_, lean_object* v_B0_15241_, lean_object* v_B1_15242_, lean_object* v_B2_15243_, lean_object* v_B3_15244_, lean_object* v_t_15245_, float v_s0_15246_, float v_s1_15247_, float v_s2_15248_, float v_s3_15249_, float v_s4_15250_, float v_s5_15251_, float v_s6_15252_, float v_s7_15253_){
_start:
{
float v___y_15255_; float v___y_15256_; float v___y_15257_; float v___y_15258_; float v___y_15259_; float v___y_15260_; float v___y_15261_; float v___y_15262_; float v___y_15263_; float v___y_15264_; float v___y_15265_; lean_object* v___y_15266_; float v___y_15267_; float v___y_15268_; float v___y_15269_; float v___y_15270_; float v___y_15271_; uint32_t v___y_15272_; float v___y_15293_; float v___y_15294_; float v___y_15295_; float v___y_15296_; float v___y_15297_; float v___y_15298_; float v___y_15299_; float v___y_15300_; float v___y_15301_; float v___y_15302_; float v___y_15303_; float v___y_15304_; float v___y_15305_; float v___y_15306_; float v___y_15307_; float v___y_15308_; uint32_t v___y_15309_; lean_object* v___x_15328_; lean_object* v_k_15329_; lean_object* v___x_15330_; lean_object* v___x_15331_; uint8_t v___x_15332_; 
v___x_15328_ = lean_unsigned_to_nat(4u);
v_k_15329_ = lean_nat_mul(v___x_15328_, v_t_15245_);
v___x_15330_ = lean_unsigned_to_nat(3u);
v___x_15331_ = lean_nat_add(v_k_15329_, v___x_15330_);
v___x_15332_ = lean_nat_dec_lt(v___x_15331_, v_n_15238_);
lean_dec(v___x_15331_);
if (v___x_15332_ == 0)
{
uint8_t v___x_15333_; 
v___x_15333_ = lean_nat_dec_lt(v_k_15329_, v_n_15238_);
if (v___x_15333_ == 0)
{
lean_object* v___x_15334_; 
lean_dec(v_k_15329_);
lean_dec(v_t_15245_);
v___x_15334_ = lean_alloc_ctor(0, 0, 32);
lean_ctor_set_float32(v___x_15334_, 0, v_s0_15246_);
lean_ctor_set_float32(v___x_15334_, 4, v_s1_15247_);
lean_ctor_set_float32(v___x_15334_, 8, v_s2_15248_);
lean_ctor_set_float32(v___x_15334_, 12, v_s3_15249_);
lean_ctor_set_float32(v___x_15334_, 16, v_s4_15250_);
lean_ctor_set_float32(v___x_15334_, 20, v_s5_15251_);
lean_ctor_set_float32(v___x_15334_, 24, v_s6_15252_);
lean_ctor_set_float32(v___x_15334_, 28, v_s7_15253_);
return v___x_15334_;
}
else
{
lean_object* v_b0_15335_; lean_object* v_b1_15336_; lean_object* v_b2_15337_; lean_object* v_b3_15338_; lean_object* v___x_15339_; float v___y_15341_; float v___y_15342_; float v___y_15343_; float v___y_15344_; float v___y_15345_; float v___y_15346_; float v___y_15347_; float v___y_15348_; float v___y_15349_; float v___y_15350_; float v___y_15351_; float v___y_15352_; float v___y_15353_; float v___y_15354_; float v___y_15355_; float v___y_15356_; float v___y_15357_; float v___y_15358_; float v___y_15359_; float v___y_15360_; float v___y_15361_; float v___y_15362_; float v___y_15363_; float v___y_15364_; uint32_t v___y_15365_; uint32_t v___y_15394_; lean_object* v___x_15452_; uint8_t v___x_15453_; 
v_b0_15335_ = lean_array_fget_borrowed(v_B0_15241_, v_t_15245_);
v_b1_15336_ = lean_array_fget_borrowed(v_B1_15242_, v_t_15245_);
v_b2_15337_ = lean_array_fget_borrowed(v_B2_15243_, v_t_15245_);
v_b3_15338_ = lean_array_fget(v_B3_15244_, v_t_15245_);
lean_dec(v_t_15245_);
v___x_15339_ = lean_nat_add(v_baseA_15239_, v_k_15329_);
v___x_15452_ = lean_array_get_size(v_A_15240_);
v___x_15453_ = lean_nat_dec_lt(v___x_15339_, v___x_15452_);
if (v___x_15453_ == 0)
{
uint32_t v___x_15454_; 
v___x_15454_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15394_ = v___x_15454_;
goto v___jp_15393_;
}
else
{
lean_object* v___x_15455_; uint32_t v___x_15456_; 
v___x_15455_ = lean_array_fget_borrowed(v_A_15240_, v___x_15339_);
v___x_15456_ = lean_unbox_uint32(v___x_15455_);
v___y_15394_ = v___x_15456_;
goto v___jp_15393_;
}
v___jp_15340_:
{
float v___x_15366_; float v___x_15367_; float v_s0_15368_; float v___x_15369_; float v_s1_15370_; float v___x_15371_; float v_s2_15372_; float v___x_15373_; float v_s3_15374_; float v___x_15375_; float v_s4_15376_; float v___x_15377_; float v_s5_15378_; float v___x_15379_; float v_s6_15380_; float v___x_15381_; float v_s7_15382_; lean_object* v___x_15383_; lean_object* v___x_15384_; uint8_t v___x_15385_; 
v___x_15366_ = lean_float32_of_bits(v___y_15365_);
v___x_15367_ = lean_float32_mul(v___x_15366_, v___y_15354_);
v_s0_15368_ = lean_float32_add(v___y_15360_, v___x_15367_);
v___x_15369_ = lean_float32_mul(v___x_15366_, v___y_15348_);
v_s1_15370_ = lean_float32_add(v___y_15364_, v___x_15369_);
v___x_15371_ = lean_float32_mul(v___x_15366_, v___y_15353_);
v_s2_15372_ = lean_float32_add(v___y_15350_, v___x_15371_);
v___x_15373_ = lean_float32_mul(v___x_15366_, v___y_15356_);
v_s3_15374_ = lean_float32_add(v___y_15343_, v___x_15373_);
v___x_15375_ = lean_float32_mul(v___x_15366_, v___y_15341_);
v_s4_15376_ = lean_float32_add(v___y_15357_, v___x_15375_);
v___x_15377_ = lean_float32_mul(v___x_15366_, v___y_15363_);
v_s5_15378_ = lean_float32_add(v___y_15342_, v___x_15377_);
v___x_15379_ = lean_float32_mul(v___x_15366_, v___y_15345_);
v_s6_15380_ = lean_float32_add(v___y_15352_, v___x_15379_);
v___x_15381_ = lean_float32_mul(v___x_15366_, v___y_15359_);
v_s7_15382_ = lean_float32_add(v___y_15361_, v___x_15381_);
v___x_15383_ = lean_unsigned_to_nat(2u);
v___x_15384_ = lean_nat_add(v_k_15329_, v___x_15383_);
lean_dec(v_k_15329_);
v___x_15385_ = lean_nat_dec_lt(v___x_15384_, v_n_15238_);
lean_dec(v___x_15384_);
if (v___x_15385_ == 0)
{
lean_object* v___x_15386_; 
lean_dec(v___x_15339_);
v___x_15386_ = lean_alloc_ctor(0, 0, 32);
lean_ctor_set_float32(v___x_15386_, 0, v_s0_15368_);
lean_ctor_set_float32(v___x_15386_, 4, v_s1_15370_);
lean_ctor_set_float32(v___x_15386_, 8, v_s2_15372_);
lean_ctor_set_float32(v___x_15386_, 12, v_s3_15374_);
lean_ctor_set_float32(v___x_15386_, 16, v_s4_15376_);
lean_ctor_set_float32(v___x_15386_, 20, v_s5_15378_);
lean_ctor_set_float32(v___x_15386_, 24, v_s6_15380_);
lean_ctor_set_float32(v___x_15386_, 28, v_s7_15382_);
return v___x_15386_;
}
else
{
lean_object* v___x_15387_; lean_object* v___x_15388_; uint8_t v___x_15389_; 
v___x_15387_ = lean_nat_add(v___x_15339_, v___x_15383_);
lean_dec(v___x_15339_);
v___x_15388_ = lean_array_get_size(v_A_15240_);
v___x_15389_ = lean_nat_dec_lt(v___x_15387_, v___x_15388_);
if (v___x_15389_ == 0)
{
uint32_t v___x_15390_; 
lean_dec(v___x_15387_);
v___x_15390_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15293_ = v_s6_15380_;
v___y_15294_ = v___y_15344_;
v___y_15295_ = v___y_15346_;
v___y_15296_ = v_s3_15374_;
v___y_15297_ = v___y_15347_;
v___y_15298_ = v___y_15349_;
v___y_15299_ = v_s2_15372_;
v___y_15300_ = v___y_15351_;
v___y_15301_ = v_s4_15376_;
v___y_15302_ = v___y_15355_;
v___y_15303_ = v___y_15358_;
v___y_15304_ = v_s1_15370_;
v___y_15305_ = v_s7_15382_;
v___y_15306_ = v___y_15362_;
v___y_15307_ = v_s0_15368_;
v___y_15308_ = v_s5_15378_;
v___y_15309_ = v___x_15390_;
goto v___jp_15292_;
}
else
{
lean_object* v___x_15391_; uint32_t v___x_15392_; 
v___x_15391_ = lean_array_fget_borrowed(v_A_15240_, v___x_15387_);
lean_dec(v___x_15387_);
v___x_15392_ = lean_unbox_uint32(v___x_15391_);
v___y_15293_ = v_s6_15380_;
v___y_15294_ = v___y_15344_;
v___y_15295_ = v___y_15346_;
v___y_15296_ = v_s3_15374_;
v___y_15297_ = v___y_15347_;
v___y_15298_ = v___y_15349_;
v___y_15299_ = v_s2_15372_;
v___y_15300_ = v___y_15351_;
v___y_15301_ = v_s4_15376_;
v___y_15302_ = v___y_15355_;
v___y_15303_ = v___y_15358_;
v___y_15304_ = v_s1_15370_;
v___y_15305_ = v_s7_15382_;
v___y_15306_ = v___y_15362_;
v___y_15307_ = v_s0_15368_;
v___y_15308_ = v_s5_15378_;
v___y_15309_ = v___x_15392_;
goto v___jp_15292_;
}
}
}
v___jp_15393_:
{
float v_k0c0_15395_; float v_k0c1_15396_; float v_k1c0_15397_; float v_k1c1_15398_; float v_k2c0_15399_; float v_k2c1_15400_; float v_k0c0_15401_; float v_k0c1_15402_; float v_k1c0_15403_; float v_k1c1_15404_; float v_k2c0_15405_; float v_k2c1_15406_; float v___x_15407_; float v___x_15408_; float v___x_15409_; float v_k0c0_15410_; float v_k0c1_15411_; float v_k1c0_15412_; float v_k1c1_15413_; float v_k2c0_15414_; float v_k2c1_15415_; float v___x_15416_; float v___x_15417_; float v_k0c0_15418_; float v_k0c1_15419_; float v_k1c0_15420_; float v_k1c1_15421_; float v_k2c0_15422_; float v_k2c1_15423_; lean_object* v___x_15425_; uint8_t v_isShared_15426_; uint8_t v_isSharedCheck_15451_; 
v_k0c0_15395_ = lean_ctor_get_float32(v_b0_15335_, 0);
v_k0c1_15396_ = lean_ctor_get_float32(v_b0_15335_, 4);
v_k1c0_15397_ = lean_ctor_get_float32(v_b0_15335_, 8);
v_k1c1_15398_ = lean_ctor_get_float32(v_b0_15335_, 12);
v_k2c0_15399_ = lean_ctor_get_float32(v_b0_15335_, 16);
v_k2c1_15400_ = lean_ctor_get_float32(v_b0_15335_, 20);
v_k0c0_15401_ = lean_ctor_get_float32(v_b1_15336_, 0);
v_k0c1_15402_ = lean_ctor_get_float32(v_b1_15336_, 4);
v_k1c0_15403_ = lean_ctor_get_float32(v_b1_15336_, 8);
v_k1c1_15404_ = lean_ctor_get_float32(v_b1_15336_, 12);
v_k2c0_15405_ = lean_ctor_get_float32(v_b1_15336_, 16);
v_k2c1_15406_ = lean_ctor_get_float32(v_b1_15336_, 20);
v___x_15407_ = lean_float32_of_bits(v___y_15394_);
v___x_15408_ = lean_float32_mul(v___x_15407_, v_k0c0_15395_);
v___x_15409_ = lean_float32_mul(v___x_15407_, v_k0c1_15396_);
v_k0c0_15410_ = lean_ctor_get_float32(v_b2_15337_, 0);
v_k0c1_15411_ = lean_ctor_get_float32(v_b2_15337_, 4);
v_k1c0_15412_ = lean_ctor_get_float32(v_b2_15337_, 8);
v_k1c1_15413_ = lean_ctor_get_float32(v_b2_15337_, 12);
v_k2c0_15414_ = lean_ctor_get_float32(v_b2_15337_, 16);
v_k2c1_15415_ = lean_ctor_get_float32(v_b2_15337_, 20);
v___x_15416_ = lean_float32_mul(v___x_15407_, v_k0c0_15401_);
v___x_15417_ = lean_float32_mul(v___x_15407_, v_k0c1_15402_);
v_k0c0_15418_ = lean_ctor_get_float32(v_b3_15338_, 0);
v_k0c1_15419_ = lean_ctor_get_float32(v_b3_15338_, 4);
v_k1c0_15420_ = lean_ctor_get_float32(v_b3_15338_, 8);
v_k1c1_15421_ = lean_ctor_get_float32(v_b3_15338_, 12);
v_k2c0_15422_ = lean_ctor_get_float32(v_b3_15338_, 16);
v_k2c1_15423_ = lean_ctor_get_float32(v_b3_15338_, 20);
v_isSharedCheck_15451_ = !lean_is_exclusive(v_b3_15338_);
if (v_isSharedCheck_15451_ == 0)
{
v___x_15425_ = v_b3_15338_;
v_isShared_15426_ = v_isSharedCheck_15451_;
goto v_resetjp_15424_;
}
else
{
lean_dec(v_b3_15338_);
v___x_15425_ = lean_box(0);
v_isShared_15426_ = v_isSharedCheck_15451_;
goto v_resetjp_15424_;
}
v_resetjp_15424_:
{
float v___x_15427_; float v_s0_15428_; float v_s1_15429_; float v_s2_15430_; float v_s3_15431_; float v_s4_15432_; float v___x_15433_; float v_s5_15434_; float v___x_15435_; float v_s6_15436_; float v___x_15437_; float v_s7_15438_; lean_object* v___x_15439_; lean_object* v___x_15440_; uint8_t v___x_15441_; 
v___x_15427_ = lean_float32_mul(v___x_15407_, v_k0c0_15410_);
v_s0_15428_ = lean_float32_add(v_s0_15246_, v___x_15408_);
v_s1_15429_ = lean_float32_add(v_s1_15247_, v___x_15409_);
v_s2_15430_ = lean_float32_add(v_s2_15248_, v___x_15416_);
v_s3_15431_ = lean_float32_add(v_s3_15249_, v___x_15417_);
v_s4_15432_ = lean_float32_add(v_s4_15250_, v___x_15427_);
v___x_15433_ = lean_float32_mul(v___x_15407_, v_k0c1_15411_);
v_s5_15434_ = lean_float32_add(v_s5_15251_, v___x_15433_);
v___x_15435_ = lean_float32_mul(v___x_15407_, v_k0c0_15418_);
v_s6_15436_ = lean_float32_add(v_s6_15252_, v___x_15435_);
v___x_15437_ = lean_float32_mul(v___x_15407_, v_k0c1_15419_);
v_s7_15438_ = lean_float32_add(v_s7_15253_, v___x_15437_);
v___x_15439_ = lean_unsigned_to_nat(1u);
v___x_15440_ = lean_nat_add(v_k_15329_, v___x_15439_);
v___x_15441_ = lean_nat_dec_lt(v___x_15440_, v_n_15238_);
lean_dec(v___x_15440_);
if (v___x_15441_ == 0)
{
lean_object* v___x_15443_; 
lean_dec(v___x_15339_);
lean_dec(v_k_15329_);
if (v_isShared_15426_ == 0)
{
v___x_15443_ = v___x_15425_;
goto v_reusejp_15442_;
}
else
{
lean_object* v_reuseFailAlloc_15444_; 
v_reuseFailAlloc_15444_ = lean_alloc_ctor(0, 0, 32);
v___x_15443_ = v_reuseFailAlloc_15444_;
goto v_reusejp_15442_;
}
v_reusejp_15442_:
{
lean_ctor_set_float32(v___x_15443_, 0, v_s0_15428_);
lean_ctor_set_float32(v___x_15443_, 4, v_s1_15429_);
lean_ctor_set_float32(v___x_15443_, 8, v_s2_15430_);
lean_ctor_set_float32(v___x_15443_, 12, v_s3_15431_);
lean_ctor_set_float32(v___x_15443_, 16, v_s4_15432_);
lean_ctor_set_float32(v___x_15443_, 20, v_s5_15434_);
lean_ctor_set_float32(v___x_15443_, 24, v_s6_15436_);
lean_ctor_set_float32(v___x_15443_, 28, v_s7_15438_);
return v___x_15443_;
}
}
else
{
lean_object* v___x_15445_; lean_object* v___x_15446_; uint8_t v___x_15447_; 
lean_del_object(v___x_15425_);
v___x_15445_ = lean_nat_add(v___x_15339_, v___x_15439_);
v___x_15446_ = lean_array_get_size(v_A_15240_);
v___x_15447_ = lean_nat_dec_lt(v___x_15445_, v___x_15446_);
if (v___x_15447_ == 0)
{
uint32_t v___x_15448_; 
lean_dec(v___x_15445_);
v___x_15448_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15341_ = v_k1c0_15412_;
v___y_15342_ = v_s5_15434_;
v___y_15343_ = v_s3_15431_;
v___y_15344_ = v_k2c0_15422_;
v___y_15345_ = v_k1c0_15420_;
v___y_15346_ = v_k2c1_15406_;
v___y_15347_ = v_k2c1_15415_;
v___y_15348_ = v_k1c1_15398_;
v___y_15349_ = v_k2c0_15405_;
v___y_15350_ = v_s2_15430_;
v___y_15351_ = v_k2c0_15414_;
v___y_15352_ = v_s6_15436_;
v___y_15353_ = v_k1c0_15403_;
v___y_15354_ = v_k1c0_15397_;
v___y_15355_ = v_k2c1_15400_;
v___y_15356_ = v_k1c1_15404_;
v___y_15357_ = v_s4_15432_;
v___y_15358_ = v_k2c0_15399_;
v___y_15359_ = v_k1c1_15421_;
v___y_15360_ = v_s0_15428_;
v___y_15361_ = v_s7_15438_;
v___y_15362_ = v_k2c1_15423_;
v___y_15363_ = v_k1c1_15413_;
v___y_15364_ = v_s1_15429_;
v___y_15365_ = v___x_15448_;
goto v___jp_15340_;
}
else
{
lean_object* v___x_15449_; uint32_t v___x_15450_; 
v___x_15449_ = lean_array_fget_borrowed(v_A_15240_, v___x_15445_);
lean_dec(v___x_15445_);
v___x_15450_ = lean_unbox_uint32(v___x_15449_);
v___y_15341_ = v_k1c0_15412_;
v___y_15342_ = v_s5_15434_;
v___y_15343_ = v_s3_15431_;
v___y_15344_ = v_k2c0_15422_;
v___y_15345_ = v_k1c0_15420_;
v___y_15346_ = v_k2c1_15406_;
v___y_15347_ = v_k2c1_15415_;
v___y_15348_ = v_k1c1_15398_;
v___y_15349_ = v_k2c0_15405_;
v___y_15350_ = v_s2_15430_;
v___y_15351_ = v_k2c0_15414_;
v___y_15352_ = v_s6_15436_;
v___y_15353_ = v_k1c0_15403_;
v___y_15354_ = v_k1c0_15397_;
v___y_15355_ = v_k2c1_15400_;
v___y_15356_ = v_k1c1_15404_;
v___y_15357_ = v_s4_15432_;
v___y_15358_ = v_k2c0_15399_;
v___y_15359_ = v_k1c1_15421_;
v___y_15360_ = v_s0_15428_;
v___y_15361_ = v_s7_15438_;
v___y_15362_ = v_k2c1_15423_;
v___y_15363_ = v_k1c1_15413_;
v___y_15364_ = v_s1_15429_;
v___y_15365_ = v___x_15450_;
goto v___jp_15340_;
}
}
}
}
}
}
else
{
lean_object* v_b0_15457_; lean_object* v_b1_15458_; lean_object* v_b2_15459_; lean_object* v_b3_15460_; lean_object* v___x_15461_; float v___y_15463_; float v___y_15464_; float v___y_15465_; float v___y_15466_; float v___y_15467_; float v___y_15468_; float v___y_15469_; float v___y_15470_; float v___y_15471_; lean_object* v___y_15472_; float v___y_15473_; float v___y_15474_; float v___y_15475_; float v___y_15476_; float v___y_15477_; float v___y_15478_; float v___y_15479_; float v___y_15480_; float v___y_15481_; float v___y_15482_; float v___y_15483_; float v___y_15484_; float v___y_15485_; float v___y_15486_; float v___y_15487_; uint32_t v___y_15488_; float v___y_15513_; float v___y_15514_; float v___y_15515_; float v___y_15516_; float v___y_15517_; float v___y_15518_; float v___y_15519_; float v___y_15520_; float v___y_15521_; float v___y_15522_; float v___y_15523_; float v___y_15524_; float v___y_15525_; float v___y_15526_; float v___y_15527_; float v___y_15528_; float v___y_15529_; lean_object* v___y_15530_; float v___y_15531_; float v___y_15532_; float v___y_15533_; float v___y_15534_; float v___y_15535_; float v___y_15536_; float v___y_15537_; float v___y_15538_; float v___y_15539_; float v___y_15540_; float v___y_15541_; float v___y_15542_; float v___y_15543_; float v___y_15544_; float v___y_15545_; uint32_t v___y_15546_; uint32_t v___y_15572_; lean_object* v___x_15629_; uint8_t v___x_15630_; 
v_b0_15457_ = lean_array_fget_borrowed(v_B0_15241_, v_t_15245_);
v_b1_15458_ = lean_array_fget_borrowed(v_B1_15242_, v_t_15245_);
v_b2_15459_ = lean_array_fget_borrowed(v_B2_15243_, v_t_15245_);
v_b3_15460_ = lean_array_fget_borrowed(v_B3_15244_, v_t_15245_);
v___x_15461_ = lean_nat_add(v_baseA_15239_, v_k_15329_);
lean_dec(v_k_15329_);
v___x_15629_ = lean_array_get_size(v_A_15240_);
v___x_15630_ = lean_nat_dec_lt(v___x_15461_, v___x_15629_);
if (v___x_15630_ == 0)
{
uint32_t v___x_15631_; 
v___x_15631_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15572_ = v___x_15631_;
goto v___jp_15571_;
}
else
{
lean_object* v___x_15632_; uint32_t v___x_15633_; 
v___x_15632_ = lean_array_fget_borrowed(v_A_15240_, v___x_15461_);
v___x_15633_ = lean_unbox_uint32(v___x_15632_);
v___y_15572_ = v___x_15633_;
goto v___jp_15571_;
}
v___jp_15462_:
{
float v___x_15489_; float v___x_15490_; float v_s0_15491_; float v___x_15492_; float v_s1_15493_; float v___x_15494_; float v_s2_15495_; float v___x_15496_; float v_s3_15497_; float v___x_15498_; float v_s4_15499_; float v___x_15500_; float v_s5_15501_; float v___x_15502_; float v_s6_15503_; float v___x_15504_; float v_s7_15505_; lean_object* v___x_15506_; lean_object* v___x_15507_; uint8_t v___x_15508_; 
v___x_15489_ = lean_float32_of_bits(v___y_15488_);
v___x_15490_ = lean_float32_mul(v___x_15489_, v___y_15471_);
v_s0_15491_ = lean_float32_add(v___y_15481_, v___x_15490_);
v___x_15492_ = lean_float32_mul(v___x_15489_, v___y_15480_);
v_s1_15493_ = lean_float32_add(v___y_15483_, v___x_15492_);
v___x_15494_ = lean_float32_mul(v___x_15489_, v___y_15468_);
v_s2_15495_ = lean_float32_add(v___y_15482_, v___x_15494_);
v___x_15496_ = lean_float32_mul(v___x_15489_, v___y_15467_);
v_s3_15497_ = lean_float32_add(v___y_15475_, v___x_15496_);
v___x_15498_ = lean_float32_mul(v___x_15489_, v___y_15477_);
v_s4_15499_ = lean_float32_add(v___y_15486_, v___x_15498_);
v___x_15500_ = lean_float32_mul(v___x_15489_, v___y_15479_);
v_s5_15501_ = lean_float32_add(v___y_15476_, v___x_15500_);
v___x_15502_ = lean_float32_mul(v___x_15489_, v___y_15487_);
v_s6_15503_ = lean_float32_add(v___y_15485_, v___x_15502_);
v___x_15504_ = lean_float32_mul(v___x_15489_, v___y_15469_);
v_s7_15505_ = lean_float32_add(v___y_15478_, v___x_15504_);
v___x_15506_ = lean_nat_add(v___x_15461_, v___x_15330_);
lean_dec(v___x_15461_);
v___x_15507_ = lean_array_get_size(v_A_15240_);
v___x_15508_ = lean_nat_dec_lt(v___x_15506_, v___x_15507_);
if (v___x_15508_ == 0)
{
uint32_t v___x_15509_; 
lean_dec(v___x_15506_);
v___x_15509_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15255_ = v___y_15463_;
v___y_15256_ = v___y_15464_;
v___y_15257_ = v___y_15465_;
v___y_15258_ = v___y_15466_;
v___y_15259_ = v_s1_15493_;
v___y_15260_ = v_s6_15503_;
v___y_15261_ = v_s3_15497_;
v___y_15262_ = v_s5_15501_;
v___y_15263_ = v___y_15470_;
v___y_15264_ = v___y_15484_;
v___y_15265_ = v_s4_15499_;
v___y_15266_ = v___y_15472_;
v___y_15267_ = v___y_15473_;
v___y_15268_ = v_s7_15505_;
v___y_15269_ = v_s2_15495_;
v___y_15270_ = v___y_15474_;
v___y_15271_ = v_s0_15491_;
v___y_15272_ = v___x_15509_;
goto v___jp_15254_;
}
else
{
lean_object* v___x_15510_; uint32_t v___x_15511_; 
v___x_15510_ = lean_array_fget_borrowed(v_A_15240_, v___x_15506_);
lean_dec(v___x_15506_);
v___x_15511_ = lean_unbox_uint32(v___x_15510_);
v___y_15255_ = v___y_15463_;
v___y_15256_ = v___y_15464_;
v___y_15257_ = v___y_15465_;
v___y_15258_ = v___y_15466_;
v___y_15259_ = v_s1_15493_;
v___y_15260_ = v_s6_15503_;
v___y_15261_ = v_s3_15497_;
v___y_15262_ = v_s5_15501_;
v___y_15263_ = v___y_15470_;
v___y_15264_ = v___y_15484_;
v___y_15265_ = v_s4_15499_;
v___y_15266_ = v___y_15472_;
v___y_15267_ = v___y_15473_;
v___y_15268_ = v_s7_15505_;
v___y_15269_ = v_s2_15495_;
v___y_15270_ = v___y_15474_;
v___y_15271_ = v_s0_15491_;
v___y_15272_ = v___x_15511_;
goto v___jp_15254_;
}
}
v___jp_15512_:
{
float v___x_15547_; float v___x_15548_; float v_s0_15549_; float v___x_15550_; float v_s1_15551_; float v___x_15552_; float v_s2_15553_; float v___x_15554_; float v_s3_15555_; float v___x_15556_; float v_s4_15557_; float v___x_15558_; float v_s5_15559_; float v___x_15560_; float v_s6_15561_; float v___x_15562_; float v_s7_15563_; lean_object* v___x_15564_; lean_object* v___x_15565_; lean_object* v___x_15566_; uint8_t v___x_15567_; 
v___x_15547_ = lean_float32_of_bits(v___y_15546_);
v___x_15548_ = lean_float32_mul(v___x_15547_, v___y_15518_);
v_s0_15549_ = lean_float32_add(v___y_15538_, v___x_15548_);
v___x_15550_ = lean_float32_mul(v___x_15547_, v___y_15533_);
v_s1_15551_ = lean_float32_add(v___y_15534_, v___x_15550_);
v___x_15552_ = lean_float32_mul(v___x_15547_, v___y_15527_);
v_s2_15553_ = lean_float32_add(v___y_15513_, v___x_15552_);
v___x_15554_ = lean_float32_mul(v___x_15547_, v___y_15544_);
v_s3_15555_ = lean_float32_add(v___y_15535_, v___x_15554_);
v___x_15556_ = lean_float32_mul(v___x_15547_, v___y_15540_);
v_s4_15557_ = lean_float32_add(v___y_15528_, v___x_15556_);
v___x_15558_ = lean_float32_mul(v___x_15547_, v___y_15520_);
v_s5_15559_ = lean_float32_add(v___y_15531_, v___x_15558_);
v___x_15560_ = lean_float32_mul(v___x_15547_, v___y_15519_);
v_s6_15561_ = lean_float32_add(v___y_15536_, v___x_15560_);
v___x_15562_ = lean_float32_mul(v___x_15547_, v___y_15522_);
v_s7_15563_ = lean_float32_add(v___y_15543_, v___x_15562_);
v___x_15564_ = lean_unsigned_to_nat(2u);
v___x_15565_ = lean_nat_add(v___x_15461_, v___x_15564_);
v___x_15566_ = lean_array_get_size(v_A_15240_);
v___x_15567_ = lean_nat_dec_lt(v___x_15565_, v___x_15566_);
if (v___x_15567_ == 0)
{
uint32_t v___x_15568_; 
lean_dec(v___x_15565_);
v___x_15568_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15463_ = v___y_15514_;
v___y_15464_ = v___y_15515_;
v___y_15465_ = v___y_15516_;
v___y_15466_ = v___y_15517_;
v___y_15467_ = v___y_15521_;
v___y_15468_ = v___y_15523_;
v___y_15469_ = v___y_15524_;
v___y_15470_ = v___y_15525_;
v___y_15471_ = v___y_15526_;
v___y_15472_ = v___y_15530_;
v___y_15473_ = v___y_15529_;
v___y_15474_ = v___y_15532_;
v___y_15475_ = v_s3_15555_;
v___y_15476_ = v_s5_15559_;
v___y_15477_ = v___y_15537_;
v___y_15478_ = v_s7_15563_;
v___y_15479_ = v___y_15539_;
v___y_15480_ = v___y_15541_;
v___y_15481_ = v_s0_15549_;
v___y_15482_ = v_s2_15553_;
v___y_15483_ = v_s1_15551_;
v___y_15484_ = v___y_15542_;
v___y_15485_ = v_s6_15561_;
v___y_15486_ = v_s4_15557_;
v___y_15487_ = v___y_15545_;
v___y_15488_ = v___x_15568_;
goto v___jp_15462_;
}
else
{
lean_object* v___x_15569_; uint32_t v___x_15570_; 
v___x_15569_ = lean_array_fget_borrowed(v_A_15240_, v___x_15565_);
lean_dec(v___x_15565_);
v___x_15570_ = lean_unbox_uint32(v___x_15569_);
v___y_15463_ = v___y_15514_;
v___y_15464_ = v___y_15515_;
v___y_15465_ = v___y_15516_;
v___y_15466_ = v___y_15517_;
v___y_15467_ = v___y_15521_;
v___y_15468_ = v___y_15523_;
v___y_15469_ = v___y_15524_;
v___y_15470_ = v___y_15525_;
v___y_15471_ = v___y_15526_;
v___y_15472_ = v___y_15530_;
v___y_15473_ = v___y_15529_;
v___y_15474_ = v___y_15532_;
v___y_15475_ = v_s3_15555_;
v___y_15476_ = v_s5_15559_;
v___y_15477_ = v___y_15537_;
v___y_15478_ = v_s7_15563_;
v___y_15479_ = v___y_15539_;
v___y_15480_ = v___y_15541_;
v___y_15481_ = v_s0_15549_;
v___y_15482_ = v_s2_15553_;
v___y_15483_ = v_s1_15551_;
v___y_15484_ = v___y_15542_;
v___y_15485_ = v_s6_15561_;
v___y_15486_ = v_s4_15557_;
v___y_15487_ = v___y_15545_;
v___y_15488_ = v___x_15570_;
goto v___jp_15462_;
}
}
v___jp_15571_:
{
float v_k0c0_15573_; float v_k0c1_15574_; float v_k1c0_15575_; float v_k1c1_15576_; float v_k2c0_15577_; float v_k2c1_15578_; float v_k3c0_15579_; float v_k3c1_15580_; float v_k0c0_15581_; float v_k0c1_15582_; float v_k1c0_15583_; float v_k1c1_15584_; float v_k2c0_15585_; float v_k2c1_15586_; float v_k3c0_15587_; float v_k3c1_15588_; float v___x_15589_; float v___x_15590_; float v___x_15591_; float v_k0c0_15592_; float v_k0c1_15593_; float v_k1c0_15594_; float v_k1c1_15595_; float v_k2c0_15596_; float v_k2c1_15597_; float v_k3c0_15598_; float v_k3c1_15599_; float v___x_15600_; float v___x_15601_; float v_k0c0_15602_; float v_k0c1_15603_; float v_k1c0_15604_; float v_k1c1_15605_; float v_k2c0_15606_; float v_k2c1_15607_; float v_k3c0_15608_; float v_k3c1_15609_; float v___x_15610_; float v_s0_15611_; float v_s1_15612_; float v_s2_15613_; float v_s3_15614_; float v_s4_15615_; float v___x_15616_; float v_s5_15617_; float v___x_15618_; float v_s6_15619_; float v___x_15620_; float v_s7_15621_; lean_object* v___x_15622_; lean_object* v___x_15623_; lean_object* v___x_15624_; uint8_t v___x_15625_; 
v_k0c0_15573_ = lean_ctor_get_float32(v_b0_15457_, 0);
v_k0c1_15574_ = lean_ctor_get_float32(v_b0_15457_, 4);
v_k1c0_15575_ = lean_ctor_get_float32(v_b0_15457_, 8);
v_k1c1_15576_ = lean_ctor_get_float32(v_b0_15457_, 12);
v_k2c0_15577_ = lean_ctor_get_float32(v_b0_15457_, 16);
v_k2c1_15578_ = lean_ctor_get_float32(v_b0_15457_, 20);
v_k3c0_15579_ = lean_ctor_get_float32(v_b0_15457_, 24);
v_k3c1_15580_ = lean_ctor_get_float32(v_b0_15457_, 28);
v_k0c0_15581_ = lean_ctor_get_float32(v_b1_15458_, 0);
v_k0c1_15582_ = lean_ctor_get_float32(v_b1_15458_, 4);
v_k1c0_15583_ = lean_ctor_get_float32(v_b1_15458_, 8);
v_k1c1_15584_ = lean_ctor_get_float32(v_b1_15458_, 12);
v_k2c0_15585_ = lean_ctor_get_float32(v_b1_15458_, 16);
v_k2c1_15586_ = lean_ctor_get_float32(v_b1_15458_, 20);
v_k3c0_15587_ = lean_ctor_get_float32(v_b1_15458_, 24);
v_k3c1_15588_ = lean_ctor_get_float32(v_b1_15458_, 28);
v___x_15589_ = lean_float32_of_bits(v___y_15572_);
v___x_15590_ = lean_float32_mul(v___x_15589_, v_k0c0_15573_);
v___x_15591_ = lean_float32_mul(v___x_15589_, v_k0c1_15574_);
v_k0c0_15592_ = lean_ctor_get_float32(v_b2_15459_, 0);
v_k0c1_15593_ = lean_ctor_get_float32(v_b2_15459_, 4);
v_k1c0_15594_ = lean_ctor_get_float32(v_b2_15459_, 8);
v_k1c1_15595_ = lean_ctor_get_float32(v_b2_15459_, 12);
v_k2c0_15596_ = lean_ctor_get_float32(v_b2_15459_, 16);
v_k2c1_15597_ = lean_ctor_get_float32(v_b2_15459_, 20);
v_k3c0_15598_ = lean_ctor_get_float32(v_b2_15459_, 24);
v_k3c1_15599_ = lean_ctor_get_float32(v_b2_15459_, 28);
v___x_15600_ = lean_float32_mul(v___x_15589_, v_k0c0_15581_);
v___x_15601_ = lean_float32_mul(v___x_15589_, v_k0c1_15582_);
v_k0c0_15602_ = lean_ctor_get_float32(v_b3_15460_, 0);
v_k0c1_15603_ = lean_ctor_get_float32(v_b3_15460_, 4);
v_k1c0_15604_ = lean_ctor_get_float32(v_b3_15460_, 8);
v_k1c1_15605_ = lean_ctor_get_float32(v_b3_15460_, 12);
v_k2c0_15606_ = lean_ctor_get_float32(v_b3_15460_, 16);
v_k2c1_15607_ = lean_ctor_get_float32(v_b3_15460_, 20);
v_k3c0_15608_ = lean_ctor_get_float32(v_b3_15460_, 24);
v_k3c1_15609_ = lean_ctor_get_float32(v_b3_15460_, 28);
v___x_15610_ = lean_float32_mul(v___x_15589_, v_k0c0_15592_);
v_s0_15611_ = lean_float32_add(v_s0_15246_, v___x_15590_);
v_s1_15612_ = lean_float32_add(v_s1_15247_, v___x_15591_);
v_s2_15613_ = lean_float32_add(v_s2_15248_, v___x_15600_);
v_s3_15614_ = lean_float32_add(v_s3_15249_, v___x_15601_);
v_s4_15615_ = lean_float32_add(v_s4_15250_, v___x_15610_);
v___x_15616_ = lean_float32_mul(v___x_15589_, v_k0c1_15593_);
v_s5_15617_ = lean_float32_add(v_s5_15251_, v___x_15616_);
v___x_15618_ = lean_float32_mul(v___x_15589_, v_k0c0_15602_);
v_s6_15619_ = lean_float32_add(v_s6_15252_, v___x_15618_);
v___x_15620_ = lean_float32_mul(v___x_15589_, v_k0c1_15603_);
v_s7_15621_ = lean_float32_add(v_s7_15253_, v___x_15620_);
v___x_15622_ = lean_unsigned_to_nat(1u);
v___x_15623_ = lean_nat_add(v___x_15461_, v___x_15622_);
v___x_15624_ = lean_array_get_size(v_A_15240_);
v___x_15625_ = lean_nat_dec_lt(v___x_15623_, v___x_15624_);
if (v___x_15625_ == 0)
{
uint32_t v___x_15626_; 
lean_dec(v___x_15623_);
v___x_15626_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___y_15513_ = v_s2_15613_;
v___y_15514_ = v_k3c0_15587_;
v___y_15515_ = v_k3c1_15599_;
v___y_15516_ = v_k3c0_15579_;
v___y_15517_ = v_k3c0_15598_;
v___y_15518_ = v_k1c0_15575_;
v___y_15519_ = v_k1c0_15604_;
v___y_15520_ = v_k1c1_15595_;
v___y_15521_ = v_k2c1_15586_;
v___y_15522_ = v_k1c1_15605_;
v___y_15523_ = v_k2c0_15585_;
v___y_15524_ = v_k2c1_15607_;
v___y_15525_ = v_k3c1_15609_;
v___y_15526_ = v_k2c0_15577_;
v___y_15527_ = v_k1c0_15583_;
v___y_15528_ = v_s4_15615_;
v___y_15529_ = v_k3c1_15580_;
v___y_15530_ = v___x_15622_;
v___y_15531_ = v_s5_15617_;
v___y_15532_ = v_k3c1_15588_;
v___y_15533_ = v_k1c1_15576_;
v___y_15534_ = v_s1_15612_;
v___y_15535_ = v_s3_15614_;
v___y_15536_ = v_s6_15619_;
v___y_15537_ = v_k2c0_15596_;
v___y_15538_ = v_s0_15611_;
v___y_15539_ = v_k2c1_15597_;
v___y_15540_ = v_k1c0_15594_;
v___y_15541_ = v_k2c1_15578_;
v___y_15542_ = v_k3c0_15608_;
v___y_15543_ = v_s7_15621_;
v___y_15544_ = v_k1c1_15584_;
v___y_15545_ = v_k2c0_15606_;
v___y_15546_ = v___x_15626_;
goto v___jp_15512_;
}
else
{
lean_object* v___x_15627_; uint32_t v___x_15628_; 
v___x_15627_ = lean_array_fget_borrowed(v_A_15240_, v___x_15623_);
lean_dec(v___x_15623_);
v___x_15628_ = lean_unbox_uint32(v___x_15627_);
v___y_15513_ = v_s2_15613_;
v___y_15514_ = v_k3c0_15587_;
v___y_15515_ = v_k3c1_15599_;
v___y_15516_ = v_k3c0_15579_;
v___y_15517_ = v_k3c0_15598_;
v___y_15518_ = v_k1c0_15575_;
v___y_15519_ = v_k1c0_15604_;
v___y_15520_ = v_k1c1_15595_;
v___y_15521_ = v_k2c1_15586_;
v___y_15522_ = v_k1c1_15605_;
v___y_15523_ = v_k2c0_15585_;
v___y_15524_ = v_k2c1_15607_;
v___y_15525_ = v_k3c1_15609_;
v___y_15526_ = v_k2c0_15577_;
v___y_15527_ = v_k1c0_15583_;
v___y_15528_ = v_s4_15615_;
v___y_15529_ = v_k3c1_15580_;
v___y_15530_ = v___x_15622_;
v___y_15531_ = v_s5_15617_;
v___y_15532_ = v_k3c1_15588_;
v___y_15533_ = v_k1c1_15576_;
v___y_15534_ = v_s1_15612_;
v___y_15535_ = v_s3_15614_;
v___y_15536_ = v_s6_15619_;
v___y_15537_ = v_k2c0_15596_;
v___y_15538_ = v_s0_15611_;
v___y_15539_ = v_k2c1_15597_;
v___y_15540_ = v_k1c0_15594_;
v___y_15541_ = v_k2c1_15578_;
v___y_15542_ = v_k3c0_15608_;
v___y_15543_ = v_s7_15621_;
v___y_15544_ = v_k1c1_15584_;
v___y_15545_ = v_k2c0_15606_;
v___y_15546_ = v___x_15628_;
goto v___jp_15512_;
}
}
}
v___jp_15254_:
{
float v___x_15273_; float v___x_15274_; float v_s0_15275_; float v___x_15276_; float v_s1_15277_; float v___x_15278_; float v_s2_15279_; float v___x_15280_; float v_s3_15281_; float v___x_15282_; float v_s4_15283_; float v___x_15284_; float v_s5_15285_; float v___x_15286_; float v_s6_15287_; float v___x_15288_; float v_s7_15289_; lean_object* v___x_15290_; 
v___x_15273_ = lean_float32_of_bits(v___y_15272_);
v___x_15274_ = lean_float32_mul(v___x_15273_, v___y_15257_);
v_s0_15275_ = lean_float32_add(v___y_15271_, v___x_15274_);
v___x_15276_ = lean_float32_mul(v___x_15273_, v___y_15267_);
v_s1_15277_ = lean_float32_add(v___y_15259_, v___x_15276_);
v___x_15278_ = lean_float32_mul(v___x_15273_, v___y_15255_);
v_s2_15279_ = lean_float32_add(v___y_15269_, v___x_15278_);
v___x_15280_ = lean_float32_mul(v___x_15273_, v___y_15270_);
v_s3_15281_ = lean_float32_add(v___y_15261_, v___x_15280_);
v___x_15282_ = lean_float32_mul(v___x_15273_, v___y_15258_);
v_s4_15283_ = lean_float32_add(v___y_15265_, v___x_15282_);
v___x_15284_ = lean_float32_mul(v___x_15273_, v___y_15256_);
v_s5_15285_ = lean_float32_add(v___y_15262_, v___x_15284_);
v___x_15286_ = lean_float32_mul(v___x_15273_, v___y_15264_);
v_s6_15287_ = lean_float32_add(v___y_15260_, v___x_15286_);
v___x_15288_ = lean_float32_mul(v___x_15273_, v___y_15263_);
v_s7_15289_ = lean_float32_add(v___y_15268_, v___x_15288_);
v___x_15290_ = lean_nat_add(v_t_15245_, v___y_15266_);
lean_dec(v_t_15245_);
v_t_15245_ = v___x_15290_;
v_s0_15246_ = v_s0_15275_;
v_s1_15247_ = v_s1_15277_;
v_s2_15248_ = v_s2_15279_;
v_s3_15249_ = v_s3_15281_;
v_s4_15250_ = v_s4_15283_;
v_s5_15251_ = v_s5_15285_;
v_s6_15252_ = v_s6_15287_;
v_s7_15253_ = v_s7_15289_;
goto _start;
}
v___jp_15292_:
{
float v___x_15310_; float v___x_15311_; float v_s0_15312_; float v___x_15313_; float v_s1_15314_; float v___x_15315_; float v_s2_15316_; float v___x_15317_; float v_s3_15318_; float v___x_15319_; float v_s4_15320_; float v___x_15321_; float v_s5_15322_; float v___x_15323_; float v_s6_15324_; float v___x_15325_; float v_s7_15326_; lean_object* v___x_15327_; 
v___x_15310_ = lean_float32_of_bits(v___y_15309_);
v___x_15311_ = lean_float32_mul(v___x_15310_, v___y_15303_);
v_s0_15312_ = lean_float32_add(v___y_15307_, v___x_15311_);
v___x_15313_ = lean_float32_mul(v___x_15310_, v___y_15302_);
v_s1_15314_ = lean_float32_add(v___y_15304_, v___x_15313_);
v___x_15315_ = lean_float32_mul(v___x_15310_, v___y_15298_);
v_s2_15316_ = lean_float32_add(v___y_15299_, v___x_15315_);
v___x_15317_ = lean_float32_mul(v___x_15310_, v___y_15295_);
v_s3_15318_ = lean_float32_add(v___y_15296_, v___x_15317_);
v___x_15319_ = lean_float32_mul(v___x_15310_, v___y_15300_);
v_s4_15320_ = lean_float32_add(v___y_15301_, v___x_15319_);
v___x_15321_ = lean_float32_mul(v___x_15310_, v___y_15297_);
v_s5_15322_ = lean_float32_add(v___y_15308_, v___x_15321_);
v___x_15323_ = lean_float32_mul(v___x_15310_, v___y_15294_);
v_s6_15324_ = lean_float32_add(v___y_15293_, v___x_15323_);
v___x_15325_ = lean_float32_mul(v___x_15310_, v___y_15306_);
v_s7_15326_ = lean_float32_add(v___y_15305_, v___x_15325_);
v___x_15327_ = lean_alloc_ctor(0, 0, 32);
lean_ctor_set_float32(v___x_15327_, 0, v_s0_15312_);
lean_ctor_set_float32(v___x_15327_, 4, v_s1_15314_);
lean_ctor_set_float32(v___x_15327_, 8, v_s2_15316_);
lean_ctor_set_float32(v___x_15327_, 12, v_s3_15318_);
lean_ctor_set_float32(v___x_15327_, 16, v_s4_15320_);
lean_ctor_set_float32(v___x_15327_, 20, v_s5_15322_);
lean_ctor_set_float32(v___x_15327_, 24, v_s6_15324_);
lean_ctor_set_float32(v___x_15327_, 28, v_s7_15326_);
return v___x_15327_;
}
}
}
