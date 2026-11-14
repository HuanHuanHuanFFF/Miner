LEAN_EXPORT lean_object* lp_competition_Submission_R22IndexedResident8_wordLoop___redArg(size_t v_count_15531_, size_t v_a0_15532_, size_t v_a1_15533_, size_t v_a2_15534_, size_t v_a3_15535_, size_t v_stride_15536_, lean_object* v_A_15537_, lean_object* v_cache_15538_, size_t v_k_15539_, size_t v_cursor_15540_, float v_q00_15541_, float v_q10_15542_, float v_q20_15543_, float v_q30_15544_, float v_q01_15545_, float v_q11_15546_, float v_q21_15547_, float v_q31_15548_){
_start:
{
float v___y_15550_; float v___y_15551_; float v___y_15552_; float v___y_15553_; float v___y_15578_; uint32_t v___y_15579_; float v___y_15580_; float v___y_15581_; uint8_t v___y_15582_; float v___y_15597_; float v___y_15598_; float v___y_15599_; float v___y_15614_; uint32_t v___y_15615_; float v___y_15616_; uint8_t v___y_15617_; float v___y_15632_; float v___y_15633_; float v___y_15648_; uint32_t v___y_15649_; uint8_t v___y_15650_; float v___y_15665_; uint8_t v___x_15679_; 
v___x_15679_ = lean_usize_dec_lt(v_k_15539_, v_count_15531_);
if (v___x_15679_ == 0)
{
lean_object* v___x_15680_; 
v___x_15680_ = lean_alloc_ctor(0, 0, 32);
lean_ctor_set_float32(v___x_15680_, 0, v_q00_15541_);
lean_ctor_set_float32(v___x_15680_, 4, v_q10_15542_);
lean_ctor_set_float32(v___x_15680_, 8, v_q20_15543_);
lean_ctor_set_float32(v___x_15680_, 12, v_q30_15544_);
lean_ctor_set_float32(v___x_15680_, 16, v_q01_15545_);
lean_ctor_set_float32(v___x_15680_, 20, v_q11_15546_);
lean_ctor_set_float32(v___x_15680_, 24, v_q21_15547_);
lean_ctor_set_float32(v___x_15680_, 28, v_q31_15548_);
return v___x_15680_;
}
else
{
size_t v___x_15681_; lean_object* v___x_15682_; uint8_t v___y_15684_; uint32_t v___x_15701_; uint32_t v___x_15702_; uint32_t v_a_15703_; uint32_t v___x_15704_; uint32_t v___x_15705_; uint32_t v___x_15706_; uint8_t v___x_15707_; 
v___x_15681_ = lean_usize_add(v_a0_15532_, v_k_15539_);
v___x_15682_ = lean_array_uget_borrowed(v_A_15537_, v___x_15681_);
v___x_15701_ = 2147483647;
v___x_15702_ = lean_unbox_uint32(v___x_15682_);
v_a_15703_ = lean_uint32_land(v___x_15702_, v___x_15701_);
v___x_15704_ = 201326591;
v___x_15705_ = 1;
v___x_15706_ = lean_uint32_sub(v_a_15703_, v___x_15705_);
v___x_15707_ = lean_uint32_dec_le(v___x_15704_, v___x_15706_);
if (v___x_15707_ == 0)
{
v___y_15684_ = v___x_15707_;
goto v___jp_15683_;
}
else
{
uint32_t v___x_15708_; uint8_t v___x_15709_; 
v___x_15708_ = 2139095040;
v___x_15709_ = lean_uint32_dec_lt(v_a_15703_, v___x_15708_);
v___y_15684_ = v___x_15709_;
goto v___jp_15683_;
}
v___jp_15683_:
{
if (v___y_15684_ == 0)
{
uint32_t v___x_15685_; float v___x_15686_; 
v___x_15685_ = lean_unbox_uint32(v___x_15682_);
v___x_15686_ = lean_float32_of_bits(v___x_15685_);
v___y_15665_ = v___x_15686_;
goto v___jp_15664_;
}
else
{
uint32_t v___x_15687_; uint32_t v___x_15688_; uint32_t v___x_15689_; uint32_t v___x_15690_; uint32_t v___x_15691_; float v___x_15692_; lean_object* v___x_15693_; uint32_t v___x_15694_; uint32_t v___x_15695_; uint32_t v___x_15696_; lean_object* v___x_15697_; lean_object* v___x_15698_; float v___x_15699_; float v___x_15700_; 
v___x_15687_ = 8388607;
v___x_15688_ = lean_unbox_uint32(v___x_15682_);
v___x_15689_ = lean_uint32_land(v___x_15688_, v___x_15687_);
v___x_15690_ = 8388608;
v___x_15691_ = lean_uint32_lor(v___x_15689_, v___x_15690_);
v___x_15692_ = lean_uint32_to_float32(v___x_15691_);
v___x_15693_ = lp_competition_R2W01b_scaleTable;
v___x_15694_ = 23;
v___x_15695_ = lean_unbox_uint32(v___x_15682_);
v___x_15696_ = lean_uint32_shift_right(v___x_15695_, v___x_15694_);
v___x_15697_ = lean_uint32_to_nat(v___x_15696_);
v___x_15698_ = lean_array_fget_borrowed(v___x_15693_, v___x_15697_);
lean_dec(v___x_15697_);
v___x_15699_ = lean_unbox_float32(v___x_15698_);
v___x_15700_ = lean_float32_mul(v___x_15692_, v___x_15699_);
v___y_15665_ = v___x_15700_;
goto v___jp_15664_;
}
}
}
v___jp_15549_:
{
lean_object* v_b_15554_; float v_s0_15555_; float v_s1_15556_; size_t v___x_15557_; size_t v___x_15558_; size_t v___x_15559_; float v___x_15560_; float v___x_15561_; float v___x_15562_; float v___x_15563_; float v___x_15564_; float v___x_15565_; float v___x_15566_; float v___x_15567_; float v___x_15568_; float v___x_15569_; float v___x_15570_; float v___x_15571_; float v___x_15572_; float v___x_15573_; float v___x_15574_; float v___x_15575_; 
v_b_15554_ = lean_array_uget_borrowed(v_cache_15538_, v_cursor_15540_);
v_s0_15555_ = lean_ctor_get_float32(v_b_15554_, 0);
v_s1_15556_ = lean_ctor_get_float32(v_b_15554_, 4);
v___x_15557_ = ((size_t)1ULL);
v___x_15558_ = lean_usize_add(v_k_15539_, v___x_15557_);
v___x_15559_ = lean_usize_add(v_cursor_15540_, v_stride_15536_);
v___x_15560_ = lean_float32_mul(v___y_15550_, v_s0_15555_);
v___x_15561_ = lean_float32_add(v_q00_15541_, v___x_15560_);
v___x_15562_ = lean_float32_mul(v___y_15552_, v_s0_15555_);
v___x_15563_ = lean_float32_add(v_q10_15542_, v___x_15562_);
v___x_15564_ = lean_float32_mul(v___y_15551_, v_s0_15555_);
v___x_15565_ = lean_float32_add(v_q20_15543_, v___x_15564_);
v___x_15566_ = lean_float32_mul(v___y_15553_, v_s0_15555_);
v___x_15567_ = lean_float32_add(v_q30_15544_, v___x_15566_);
v___x_15568_ = lean_float32_mul(v___y_15550_, v_s1_15556_);
v___x_15569_ = lean_float32_add(v_q01_15545_, v___x_15568_);
v___x_15570_ = lean_float32_mul(v___y_15552_, v_s1_15556_);
v___x_15571_ = lean_float32_add(v_q11_15546_, v___x_15570_);
v___x_15572_ = lean_float32_mul(v___y_15551_, v_s1_15556_);
v___x_15573_ = lean_float32_add(v_q21_15547_, v___x_15572_);
v___x_15574_ = lean_float32_mul(v___y_15553_, v_s1_15556_);
v___x_15575_ = lean_float32_add(v_q31_15548_, v___x_15574_);
v_k_15539_ = v___x_15558_;
v_cursor_15540_ = v___x_15559_;
v_q00_15541_ = v___x_15561_;
v_q10_15542_ = v___x_15563_;
v_q20_15543_ = v___x_15565_;
v_q30_15544_ = v___x_15567_;
v_q01_15545_ = v___x_15569_;
v_q11_15546_ = v___x_15571_;
v_q21_15547_ = v___x_15573_;
v_q31_15548_ = v___x_15575_;
goto _start;
}
v___jp_15577_:
{
if (v___y_15582_ == 0)
{
float v___x_15583_; 
v___x_15583_ = lean_float32_of_bits(v___y_15579_);
v___y_15550_ = v___y_15578_;
v___y_15551_ = v___y_15580_;
v___y_15552_ = v___y_15581_;
v___y_15553_ = v___x_15583_;
goto v___jp_15549_;
}
else
{
uint32_t v___x_15584_; uint32_t v___x_15585_; uint32_t v___x_15586_; uint32_t v___x_15587_; float v___x_15588_; lean_object* v___x_15589_; uint32_t v___x_15590_; uint32_t v___x_15591_; lean_object* v___x_15592_; lean_object* v___x_15593_; float v___x_15594_; float v___x_15595_; 
v___x_15584_ = 8388607;
v___x_15585_ = lean_uint32_land(v___y_15579_, v___x_15584_);
v___x_15586_ = 8388608;
v___x_15587_ = lean_uint32_lor(v___x_15585_, v___x_15586_);
v___x_15588_ = lean_uint32_to_float32(v___x_15587_);
v___x_15589_ = lp_competition_R2W01b_scaleTable;
v___x_15590_ = 23;
v___x_15591_ = lean_uint32_shift_right(v___y_15579_, v___x_15590_);
v___x_15592_ = lean_uint32_to_nat(v___x_15591_);
v___x_15593_ = lean_array_fget_borrowed(v___x_15589_, v___x_15592_);
lean_dec(v___x_15592_);
v___x_15594_ = lean_unbox_float32(v___x_15593_);
v___x_15595_ = lean_float32_mul(v___x_15588_, v___x_15594_);
v___y_15550_ = v___y_15578_;
v___y_15551_ = v___y_15580_;
v___y_15552_ = v___y_15581_;
v___y_15553_ = v___x_15595_;
goto v___jp_15549_;
}
}
v___jp_15596_:
{
size_t v___x_15600_; lean_object* v___x_15601_; uint32_t v___x_15602_; uint32_t v___x_15603_; uint32_t v_a_15604_; uint32_t v___x_15605_; uint32_t v___x_15606_; uint32_t v___x_15607_; uint8_t v___x_15608_; 
v___x_15600_ = lean_usize_add(v_a3_15535_, v_k_15539_);
v___x_15601_ = lean_array_uget_borrowed(v_A_15537_, v___x_15600_);
v___x_15602_ = 2147483647;
v___x_15603_ = lean_unbox_uint32(v___x_15601_);
v_a_15604_ = lean_uint32_land(v___x_15603_, v___x_15602_);
v___x_15605_ = 201326591;
v___x_15606_ = 1;
v___x_15607_ = lean_uint32_sub(v_a_15604_, v___x_15606_);
v___x_15608_ = lean_uint32_dec_le(v___x_15605_, v___x_15607_);
if (v___x_15608_ == 0)
{
uint32_t v___x_15609_; 
v___x_15609_ = lean_unbox_uint32(v___x_15601_);
v___y_15578_ = v___y_15597_;
v___y_15579_ = v___x_15609_;
v___y_15580_ = v___y_15599_;
v___y_15581_ = v___y_15598_;
v___y_15582_ = v___x_15608_;
goto v___jp_15577_;
}
else
{
uint32_t v___x_15610_; uint8_t v___x_15611_; uint32_t v___x_15612_; 
v___x_15610_ = 2139095040;
v___x_15611_ = lean_uint32_dec_lt(v_a_15604_, v___x_15610_);
v___x_15612_ = lean_unbox_uint32(v___x_15601_);
v___y_15578_ = v___y_15597_;
v___y_15579_ = v___x_15612_;
v___y_15580_ = v___y_15599_;
v___y_15581_ = v___y_15598_;
v___y_15582_ = v___x_15611_;
goto v___jp_15577_;
}
}
v___jp_15613_:
{
if (v___y_15617_ == 0)
{
float v___x_15618_; 
v___x_15618_ = lean_float32_of_bits(v___y_15615_);
v___y_15597_ = v___y_15614_;
v___y_15598_ = v___y_15616_;
v___y_15599_ = v___x_15618_;
goto v___jp_15596_;
}
else
{
uint32_t v___x_15619_; uint32_t v___x_15620_; uint32_t v___x_15621_; uint32_t v___x_15622_; float v___x_15623_; lean_object* v___x_15624_; uint32_t v___x_15625_; uint32_t v___x_15626_; lean_object* v___x_15627_; lean_object* v___x_15628_; float v___x_15629_; float v___x_15630_; 
v___x_15619_ = 8388607;
v___x_15620_ = lean_uint32_land(v___y_15615_, v___x_15619_);
v___x_15621_ = 8388608;
v___x_15622_ = lean_uint32_lor(v___x_15620_, v___x_15621_);
v___x_15623_ = lean_uint32_to_float32(v___x_15622_);
v___x_15624_ = lp_competition_R2W01b_scaleTable;
v___x_15625_ = 23;
v___x_15626_ = lean_uint32_shift_right(v___y_15615_, v___x_15625_);
v___x_15627_ = lean_uint32_to_nat(v___x_15626_);
v___x_15628_ = lean_array_fget_borrowed(v___x_15624_, v___x_15627_);
lean_dec(v___x_15627_);
v___x_15629_ = lean_unbox_float32(v___x_15628_);
v___x_15630_ = lean_float32_mul(v___x_15623_, v___x_15629_);
v___y_15597_ = v___y_15614_;
v___y_15598_ = v___y_15616_;
v___y_15599_ = v___x_15630_;
goto v___jp_15596_;
}
}
v___jp_15631_:
{
size_t v___x_15634_; lean_object* v___x_15635_; uint32_t v___x_15636_; uint32_t v___x_15637_; uint32_t v_a_15638_; uint32_t v___x_15639_; uint32_t v___x_15640_; uint32_t v___x_15641_; uint8_t v___x_15642_; 
v___x_15634_ = lean_usize_add(v_a2_15534_, v_k_15539_);
v___x_15635_ = lean_array_uget_borrowed(v_A_15537_, v___x_15634_);
v___x_15636_ = 2147483647;
v___x_15637_ = lean_unbox_uint32(v___x_15635_);
v_a_15638_ = lean_uint32_land(v___x_15637_, v___x_15636_);
v___x_15639_ = 201326591;
v___x_15640_ = 1;
v___x_15641_ = lean_uint32_sub(v_a_15638_, v___x_15640_);
v___x_15642_ = lean_uint32_dec_le(v___x_15639_, v___x_15641_);
if (v___x_15642_ == 0)
{
uint32_t v___x_15643_; 
v___x_15643_ = lean_unbox_uint32(v___x_15635_);
v___y_15614_ = v___y_15632_;
v___y_15615_ = v___x_15643_;
v___y_15616_ = v___y_15633_;
v___y_15617_ = v___x_15642_;
goto v___jp_15613_;
}
else
{
uint32_t v___x_15644_; uint8_t v___x_15645_; uint32_t v___x_15646_; 
v___x_15644_ = 2139095040;
v___x_15645_ = lean_uint32_dec_lt(v_a_15638_, v___x_15644_);
v___x_15646_ = lean_unbox_uint32(v___x_15635_);
v___y_15614_ = v___y_15632_;
v___y_15615_ = v___x_15646_;
v___y_15616_ = v___y_15633_;
v___y_15617_ = v___x_15645_;
goto v___jp_15613_;
}
}
v___jp_15647_:
{
if (v___y_15650_ == 0)
{
float v___x_15651_; 
v___x_15651_ = lean_float32_of_bits(v___y_15649_);
v___y_15632_ = v___y_15648_;
v___y_15633_ = v___x_15651_;
goto v___jp_15631_;
}
else
{
uint32_t v___x_15652_; uint32_t v___x_15653_; uint32_t v___x_15654_; uint32_t v___x_15655_; float v___x_15656_; lean_object* v___x_15657_; uint32_t v___x_15658_; uint32_t v___x_15659_; lean_object* v___x_15660_; lean_object* v___x_15661_; float v___x_15662_; float v___x_15663_; 
v___x_15652_ = 8388607;
v___x_15653_ = lean_uint32_land(v___y_15649_, v___x_15652_);
v___x_15654_ = 8388608;
v___x_15655_ = lean_uint32_lor(v___x_15653_, v___x_15654_);
v___x_15656_ = lean_uint32_to_float32(v___x_15655_);
v___x_15657_ = lp_competition_R2W01b_scaleTable;
v___x_15658_ = 23;
v___x_15659_ = lean_uint32_shift_right(v___y_15649_, v___x_15658_);
v___x_15660_ = lean_uint32_to_nat(v___x_15659_);
v___x_15661_ = lean_array_fget_borrowed(v___x_15657_, v___x_15660_);
lean_dec(v___x_15660_);
v___x_15662_ = lean_unbox_float32(v___x_15661_);
v___x_15663_ = lean_float32_mul(v___x_15656_, v___x_15662_);
v___y_15632_ = v___y_15648_;
v___y_15633_ = v___x_15663_;
goto v___jp_15631_;
}
}
v___jp_15664_:
{
size_t v___x_15666_; lean_object* v___x_15667_; uint32_t v___x_15668_; uint32_t v___x_15669_; uint32_t v_a_15670_; uint32_t v___x_15671_; uint32_t v___x_15672_; uint32_t v___x_15673_; uint8_t v___x_15674_; 
v___x_15666_ = lean_usize_add(v_a1_15533_, v_k_15539_);
v___x_15667_ = lean_array_uget_borrowed(v_A_15537_, v___x_15666_);
v___x_15668_ = 2147483647;
v___x_15669_ = lean_unbox_uint32(v___x_15667_);
v_a_15670_ = lean_uint32_land(v___x_15669_, v___x_15668_);
v___x_15671_ = 201326591;
v___x_15672_ = 1;
v___x_15673_ = lean_uint32_sub(v_a_15670_, v___x_15672_);
v___x_15674_ = lean_uint32_dec_le(v___x_15671_, v___x_15673_);
if (v___x_15674_ == 0)
{
uint32_t v___x_15675_; 
v___x_15675_ = lean_unbox_uint32(v___x_15667_);
v___y_15648_ = v___y_15665_;
v___y_15649_ = v___x_15675_;
v___y_15650_ = v___x_15674_;
goto v___jp_15647_;
}
else
{
uint32_t v___x_15676_; uint8_t v___x_15677_; uint32_t v___x_15678_; 
v___x_15676_ = 2139095040;
v___x_15677_ = lean_uint32_dec_lt(v_a_15670_, v___x_15676_);
v___x_15678_ = lean_unbox_uint32(v___x_15667_);
v___y_15648_ = v___y_15665_;
v___y_15649_ = v___x_15678_;
v___y_15650_ = v___x_15677_;
goto v___jp_15647_;
}
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22IndexedResident8_within___redArg(lean_object* v_p_15803_, lean_object* v_n_15804_, lean_object* v_baseA_15805_, lean_object* v_baseC_15806_, lean_object* v_A_15807_, lean_object* v_cache_15808_){
_start:
{
size_t v___x_15809_; size_t v___x_15810_; lean_object* v___x_15811_; size_t v___x_15812_; lean_object* v___x_15813_; lean_object* v___x_15814_; lean_object* v___x_15815_; size_t v___x_15816_; lean_object* v___x_15817_; lean_object* v___x_15818_; lean_object* v___x_15819_; size_t v___x_15820_; lean_object* v___x_15821_; size_t v___x_15822_; size_t v___x_15823_; size_t v___x_15824_; float v___x_15825_; lean_object* v___x_15826_; 
v___x_15809_ = lean_usize_of_nat(v_n_15804_);
v___x_15810_ = lean_usize_of_nat(v_baseA_15805_);
v___x_15811_ = lean_nat_add(v_baseA_15805_, v_n_15804_);
v___x_15812_ = lean_usize_of_nat(v___x_15811_);
lean_dec(v___x_15811_);
v___x_15813_ = lean_unsigned_to_nat(2u);
v___x_15814_ = lean_nat_mul(v___x_15813_, v_n_15804_);
v___x_15815_ = lean_nat_add(v_baseA_15805_, v___x_15814_);
lean_dec(v___x_15814_);
v___x_15816_ = lean_usize_of_nat(v___x_15815_);
lean_dec(v___x_15815_);
v___x_15817_ = lean_unsigned_to_nat(3u);
v___x_15818_ = lean_nat_mul(v___x_15817_, v_n_15804_);
v___x_15819_ = lean_nat_add(v_baseA_15805_, v___x_15818_);
lean_dec(v___x_15818_);
v___x_15820_ = lean_usize_of_nat(v___x_15819_);
lean_dec(v___x_15819_);
v___x_15821_ = lp_competition_Submission_R22Pair8_groups(v_p_15803_);
v___x_15822_ = lean_usize_of_nat(v___x_15821_);
lean_dec(v___x_15821_);
v___x_15823_ = ((size_t)0ULL);
v___x_15824_ = lean_usize_of_nat(v_baseC_15806_);
v___x_15825_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_15826_ = lp_competition_Submission_R22IndexedResident8_wordLoop___redArg(v___x_15809_, v___x_15810_, v___x_15812_, v___x_15816_, v___x_15820_, v___x_15822_, v_A_15807_, v_cache_15808_, v___x_15823_, v___x_15824_, v___x_15825_, v___x_15825_, v___x_15825_, v___x_15825_, v___x_15825_, v___x_15825_, v___x_15825_, v___x_15825_);
return v___x_15826_;
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22IndexedResident8_tile___redArg(lean_object* v_p_15850_, lean_object* v_n_15851_, lean_object* v_baseA_15852_, lean_object* v_baseB_15853_, lean_object* v_baseC_15854_, lean_object* v_A_15855_, lean_object* v_B_15856_, lean_object* v_cache_15857_, uint8_t v_second_15858_){
_start:
{
lean_object* v_r_15859_; float v_c00_15860_; float v_c10_15861_; float v_c20_15862_; float v_c30_15863_; float v_c01_15864_; float v_c11_15865_; float v_c21_15866_; float v_c31_15867_; lean_object* v___x_15869_; uint8_t v_isShared_15870_; uint8_t v_isSharedCheck_15895_; 
v_r_15859_ = lp_competition_Submission_R22IndexedResident8_within___redArg(v_p_15850_, v_n_15851_, v_baseA_15852_, v_baseC_15854_, v_A_15855_, v_cache_15857_);
v_c00_15860_ = lean_ctor_get_float32(v_r_15859_, 0);
v_c10_15861_ = lean_ctor_get_float32(v_r_15859_, 4);
v_c20_15862_ = lean_ctor_get_float32(v_r_15859_, 8);
v_c30_15863_ = lean_ctor_get_float32(v_r_15859_, 12);
v_c01_15864_ = lean_ctor_get_float32(v_r_15859_, 16);
v_c11_15865_ = lean_ctor_get_float32(v_r_15859_, 20);
v_c21_15866_ = lean_ctor_get_float32(v_r_15859_, 24);
v_c31_15867_ = lean_ctor_get_float32(v_r_15859_, 28);
v_isSharedCheck_15895_ = !lean_is_exclusive(v_r_15859_);
if (v_isSharedCheck_15895_ == 0)
{
v___x_15869_ = v_r_15859_;
v_isShared_15870_ = v_isSharedCheck_15895_;
goto v_resetjp_15868_;
}
else
{
lean_dec(v_r_15859_);
v___x_15869_ = lean_box(0);
v_isShared_15870_ = v_isSharedCheck_15895_;
goto v_resetjp_15868_;
}
v_resetjp_15868_:
{
uint32_t v_w00_15871_; lean_object* v___x_15872_; uint32_t v_w10_15873_; lean_object* v___x_15874_; lean_object* v___x_15875_; lean_object* v___x_15876_; uint32_t v_w20_15877_; lean_object* v___x_15878_; lean_object* v___x_15879_; lean_object* v___x_15880_; uint32_t v_w30_15881_; 
v_w00_15871_ = lp_competition_Submission_Packed10_finish(v_n_15851_, v_baseA_15852_, v_baseB_15853_, v_p_15850_, v_A_15855_, v_B_15856_, v_c00_15860_);
v___x_15872_ = lean_nat_add(v_baseA_15852_, v_n_15851_);
v_w10_15873_ = lp_competition_Submission_Packed10_finish(v_n_15851_, v___x_15872_, v_baseB_15853_, v_p_15850_, v_A_15855_, v_B_15856_, v_c10_15861_);
v___x_15874_ = lean_unsigned_to_nat(2u);
v___x_15875_ = lean_nat_mul(v___x_15874_, v_n_15851_);
v___x_15876_ = lean_nat_add(v_baseA_15852_, v___x_15875_);
lean_dec(v___x_15875_);
v_w20_15877_ = lp_competition_Submission_Packed10_finish(v_n_15851_, v___x_15876_, v_baseB_15853_, v_p_15850_, v_A_15855_, v_B_15856_, v_c20_15862_);
v___x_15878_ = lean_unsigned_to_nat(3u);
v___x_15879_ = lean_nat_mul(v___x_15878_, v_n_15851_);
v___x_15880_ = lean_nat_add(v_baseA_15852_, v___x_15879_);
lean_dec(v___x_15879_);
v_w30_15881_ = lp_competition_Submission_Packed10_finish(v_n_15851_, v___x_15880_, v_baseB_15853_, v_p_15850_, v_A_15855_, v_B_15856_, v_c30_15863_);
if (v_second_15858_ == 0)
{
uint32_t v___x_15882_; lean_object* v___x_15884_; 
lean_dec(v___x_15880_);
lean_dec(v___x_15876_);
lean_dec(v___x_15872_);
v___x_15882_ = 0;
if (v_isShared_15870_ == 0)
{
v___x_15884_ = v___x_15869_;
goto v_reusejp_15883_;
}
else
{
lean_object* v_reuseFailAlloc_15885_; 
v_reuseFailAlloc_15885_ = lean_alloc_ctor(0, 0, 32);
v___x_15884_ = v_reuseFailAlloc_15885_;
goto v_reusejp_15883_;
}
v_reusejp_15883_:
{
lean_ctor_set_uint32(v___x_15884_, 0, v_w00_15871_);
lean_ctor_set_uint32(v___x_15884_, 4, v_w10_15873_);
lean_ctor_set_uint32(v___x_15884_, 8, v_w20_15877_);
lean_ctor_set_uint32(v___x_15884_, 12, v_w30_15881_);
lean_ctor_set_uint32(v___x_15884_, 16, v___x_15882_);
lean_ctor_set_uint32(v___x_15884_, 20, v___x_15882_);
lean_ctor_set_uint32(v___x_15884_, 24, v___x_15882_);
lean_ctor_set_uint32(v___x_15884_, 28, v___x_15882_);
return v___x_15884_;
}
}
else
{
lean_object* v___x_15886_; lean_object* v___x_15887_; uint32_t v___x_15888_; uint32_t v___x_15889_; uint32_t v___x_15890_; uint32_t v___x_15891_; lean_object* v___x_15893_; 
v___x_15886_ = lean_unsigned_to_nat(1u);
v___x_15887_ = lean_nat_add(v_baseB_15853_, v___x_15886_);
v___x_15888_ = lp_competition_Submission_Packed10_finish(v_n_15851_, v_baseA_15852_, v___x_15887_, v_p_15850_, v_A_15855_, v_B_15856_, v_c01_15864_);
v___x_15889_ = lp_competition_Submission_Packed10_finish(v_n_15851_, v___x_15872_, v___x_15887_, v_p_15850_, v_A_15855_, v_B_15856_, v_c11_15865_);
lean_dec(v___x_15872_);
v___x_15890_ = lp_competition_Submission_Packed10_finish(v_n_15851_, v___x_15876_, v___x_15887_, v_p_15850_, v_A_15855_, v_B_15856_, v_c21_15866_);
lean_dec(v___x_15876_);
v___x_15891_ = lp_competition_Submission_Packed10_finish(v_n_15851_, v___x_15880_, v___x_15887_, v_p_15850_, v_A_15855_, v_B_15856_, v_c31_15867_);
lean_dec(v___x_15887_);
lean_dec(v___x_15880_);
if (v_isShared_15870_ == 0)
{
v___x_15893_ = v___x_15869_;
goto v_reusejp_15892_;
}
else
{
lean_object* v_reuseFailAlloc_15894_; 
v_reuseFailAlloc_15894_ = lean_alloc_ctor(0, 0, 32);
v___x_15893_ = v_reuseFailAlloc_15894_;
goto v_reusejp_15892_;
}
v_reusejp_15892_:
{
lean_ctor_set_uint32(v___x_15893_, 0, v_w00_15871_);
lean_ctor_set_uint32(v___x_15893_, 4, v_w10_15873_);
lean_ctor_set_uint32(v___x_15893_, 8, v_w20_15877_);
lean_ctor_set_uint32(v___x_15893_, 12, v_w30_15881_);
lean_ctor_set_uint32(v___x_15893_, 16, v___x_15888_);
lean_ctor_set_uint32(v___x_15893_, 20, v___x_15889_);
lean_ctor_set_uint32(v___x_15893_, 24, v___x_15890_);
lean_ctor_set_uint32(v___x_15893_, 28, v___x_15891_);
return v___x_15893_;
}
}
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22IndexedResident8_tiles___redArg(lean_object* v_p_15957_, lean_object* v_n_15958_, lean_object* v_baseA_15959_, lean_object* v_baseB_15960_, lean_object* v_baseC_15961_, lean_object* v_A_15962_, lean_object* v_B_15963_, lean_object* v_cache_15964_){
_start:
{
lean_object* v___f_15965_; lean_object* v___x_15966_; lean_object* v___x_15967_; 
lean_inc(v_p_15957_);
v___f_15965_ = lean_alloc_closure((void*)(lp_competition_Submission_R22IndexedResident8_tiles___redArg___lam__0___boxed), 9, 8);
lean_closure_set(v___f_15965_, 0, v_baseB_15960_);
lean_closure_set(v___f_15965_, 1, v_baseC_15961_);
lean_closure_set(v___f_15965_, 2, v_p_15957_);
lean_closure_set(v___f_15965_, 3, v_n_15958_);
lean_closure_set(v___f_15965_, 4, v_baseA_15959_);
lean_closure_set(v___f_15965_, 5, v_A_15962_);
lean_closure_set(v___f_15965_, 6, v_B_15963_);
lean_closure_set(v___f_15965_, 7, v_cache_15964_);
v___x_15966_ = lp_competition_Submission_R22Pair8_groups(v_p_15957_);
lean_dec(v_p_15957_);
v___x_15967_ = l_Array_ofFn___redArg(v___x_15966_, v___f_15965_);
return v___x_15967_;
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22IndexedResident8_rows4___redArg(lean_object* v_p_15978_, lean_object* v_n_15979_, lean_object* v_baseA_15980_, lean_object* v_baseB_15981_, lean_object* v_baseC_15982_, lean_object* v_A_15983_, lean_object* v_B_15984_, lean_object* v_cache_15985_, lean_object* v_out_15986_){
_start:
{
lean_object* v___x_15987_; uint8_t v___x_15988_; 
v___x_15987_ = lean_unsigned_to_nat(0u);
v___x_15988_ = lean_nat_dec_eq(v_p_15978_, v___x_15987_);
if (v___x_15988_ == 0)
{
lean_object* v_t_15989_; lean_object* v_out_15990_; lean_object* v_out_15991_; lean_object* v_out_15992_; lean_object* v___x_15993_; 
lean_inc(v_p_15978_);
v_t_15989_ = lp_competition_Submission_R22IndexedResident8_tiles___redArg(v_p_15978_, v_n_15979_, v_baseA_15980_, v_baseB_15981_, v_baseC_15982_, v_A_15983_, v_B_15984_, v_cache_15985_);
v_out_15990_ = lp_competition_Fin_foldl_loop___at___00Submission_R22Resident8_rows4_spec__0(v_t_15989_, v_p_15978_, v_out_15986_, v___x_15987_);
v_out_15991_ = lp_competition_Fin_foldl_loop___at___00Submission_R22Resident8_rows4_spec__1(v_t_15989_, v_p_15978_, v_out_15990_, v___x_15987_);
v_out_15992_ = lp_competition_Fin_foldl_loop___at___00Submission_R22Resident8_rows4_spec__2(v_t_15989_, v_p_15978_, v_out_15991_, v___x_15987_);
v___x_15993_ = lp_competition_Fin_foldl_loop___at___00Submission_R22Resident8_rows4_spec__3(v_t_15989_, v_p_15978_, v_out_15992_, v___x_15987_);
lean_dec(v_p_15978_);
lean_dec_ref(v_t_15989_);
return v___x_15993_;
}
else
{
lean_dec_ref(v_cache_15985_);
lean_dec_ref(v_B_15984_);
lean_dec_ref(v_A_15983_);
lean_dec(v_baseC_15982_);
lean_dec(v_baseB_15981_);
lean_dec(v_baseA_15980_);
lean_dec(v_n_15979_);
lean_dec(v_p_15978_);
return v_out_15986_;
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22IndexedResident8_core___redArg(lean_object* v_batch_16186_, lean_object* v_m_16187_, lean_object* v_n_16188_, lean_object* v_p_16189_, lean_object* v_A_16190_, lean_object* v_B_16191_){
_start:
{
lean_object* v_cache_16192_; lean_object* v___x_16193_; uint8_t v___x_16194_; 
v_cache_16192_ = lp_competition_Submission_R22Pair8_packB(v_batch_16186_, v_n_16188_, v_p_16189_, v_B_16191_);
v___x_16193_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_16194_ = lean_nat_dec_lt(v_n_16188_, v___x_16193_);
if (v___x_16194_ == 0)
{
lean_object* v___x_16195_; 
v___x_16195_ = lp_competition_Submission_R22Resident8_output(v_batch_16186_, v_m_16187_, v_n_16188_, v_p_16189_, v_A_16190_, v_B_16191_, v_cache_16192_);
return v___x_16195_;
}
else
{
lean_object* v___x_16196_; uint8_t v___x_16197_; 
v___x_16196_ = lean_array_get_size(v_A_16190_);
v___x_16197_ = lean_nat_dec_lt(v___x_16196_, v___x_16193_);
if (v___x_16197_ == 0)
{
lean_object* v___x_16198_; 
v___x_16198_ = lp_competition_Submission_R22Resident8_output(v_batch_16186_, v_m_16187_, v_n_16188_, v_p_16189_, v_A_16190_, v_B_16191_, v_cache_16192_);
return v___x_16198_;
}
else
{
lean_object* v___x_16199_; uint8_t v___x_16200_; 
v___x_16199_ = lean_array_get_size(v_cache_16192_);
v___x_16200_ = lean_nat_dec_lt(v___x_16199_, v___x_16193_);
if (v___x_16200_ == 0)
{
lean_object* v___x_16201_; 
v___x_16201_ = lp_competition_Submission_R22Resident8_output(v_batch_16186_, v_m_16187_, v_n_16188_, v_p_16189_, v_A_16190_, v_B_16191_, v_cache_16192_);
return v___x_16201_;
}
else
{
lean_object* v___x_16202_; 
v___x_16202_ = lp_competition_Submission_R22IndexedResident8_output___redArg(v_batch_16186_, v_m_16187_, v_n_16188_, v_p_16189_, v_A_16190_, v_B_16191_, v_cache_16192_);
return v___x_16202_;
}
}
}
}
}

LEAN_EXPORT lean_object* lp_competition_Submission_R22IndexedResident8_guarded(lean_object* v_batch_16228_, lean_object* v_m_16229_, lean_object* v_n_16230_, lean_object* v_p_16231_, lean_object* v_A_16232_, lean_object* v_B_16233_){
_start:
{
uint8_t v___y_16246_; lean_object* v___x_16256_; lean_object* v___x_16257_; uint8_t v___x_16258_; 
v___x_16256_ = lean_unsigned_to_nat(0u);
v___x_16257_ = lean_array_get_size(v_A_16232_);
v___x_16258_ = lean_nat_dec_lt(v___x_16256_, v___x_16257_);
if (v___x_16258_ == 0)
{
uint8_t v___x_16259_; 
v___x_16259_ = 1;
v___y_16246_ = v___x_16259_;
goto v___jp_16245_;
}
else
{
if (v___x_16258_ == 0)
{
v___y_16246_ = v___x_16258_;
goto v___jp_16245_;
}
else
{
size_t v___x_16260_; size_t v___x_16261_; uint8_t v___x_16262_; 
v___x_16260_ = ((size_t)0ULL);
v___x_16261_ = lean_usize_of_nat(v___x_16257_);
v___x_16262_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00Submission_bmm_spec__1(v_A_16232_, v___x_16260_, v___x_16261_);
if (v___x_16262_ == 0)
{
v___y_16246_ = v___x_16258_;
goto v___jp_16245_;
}
else
{
goto v___jp_16234_;
}
}
}
v___jp_16234_:
{
lean_object* v___x_16235_; uint8_t v___x_16236_; 
v___x_16235_ = lean_unsigned_to_nat(1u);
v___x_16236_ = lean_nat_dec_lt(v___x_16235_, v_n_16230_);
if (v___x_16236_ == 0)
{
lean_object* v___x_16237_; 
v___x_16237_ = lp_competition_Submission_bmm(v_batch_16228_, v_m_16229_, v_n_16230_, v_p_16231_, v_A_16232_, v_B_16233_);
return v___x_16237_;
}
else
{
lean_object* v___x_16238_; uint8_t v___x_16239_; 
v___x_16238_ = lean_unsigned_to_nat(4u);
v___x_16239_ = lean_nat_dec_le(v___x_16238_, v_m_16229_);
if (v___x_16239_ == 0)
{
lean_object* v___x_16240_; 
v___x_16240_ = lp_competition_Submission_bmm(v_batch_16228_, v_m_16229_, v_n_16230_, v_p_16231_, v_A_16232_, v_B_16233_);
return v___x_16240_;
}
else
{
lean_object* v___x_16241_; uint8_t v___x_16242_; 
v___x_16241_ = lean_unsigned_to_nat(2u);
v___x_16242_ = lean_nat_dec_le(v___x_16241_, v_p_16231_);
if (v___x_16242_ == 0)
{
lean_object* v___x_16243_; 
v___x_16243_ = lp_competition_Submission_bmm(v_batch_16228_, v_m_16229_, v_n_16230_, v_p_16231_, v_A_16232_, v_B_16233_);
return v___x_16243_;
}
else
{
lean_object* v___x_16244_; 
v___x_16244_ = lp_competition_Submission_R22IndexedResident8_core___redArg(v_batch_16228_, v_m_16229_, v_n_16230_, v_p_16231_, v_A_16232_, v_B_16233_);
lean_dec(v_m_16229_);
lean_dec(v_batch_16228_);
return v___x_16244_;
}
}
}
}
v___jp_16245_:
{
lean_object* v___x_16247_; lean_object* v___x_16248_; uint8_t v___x_16249_; 
v___x_16247_ = lean_unsigned_to_nat(0u);
v___x_16248_ = lean_array_get_size(v_B_16233_);
v___x_16249_ = lean_nat_dec_lt(v___x_16247_, v___x_16248_);
if (v___x_16249_ == 0)
{
lean_object* v___x_16250_; 
lean_dec_ref(v_B_16233_);
lean_dec_ref(v_A_16232_);
lean_dec(v_n_16230_);
v___x_16250_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_16228_, v_m_16229_, v_p_16231_);
lean_dec(v_p_16231_);
lean_dec(v_m_16229_);
lean_dec(v_batch_16228_);
return v___x_16250_;
}
else
{
if (v___x_16249_ == 0)
{
lean_object* v___x_16251_; 
lean_dec_ref(v_B_16233_);
lean_dec_ref(v_A_16232_);
lean_dec(v_n_16230_);
v___x_16251_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_16228_, v_m_16229_, v_p_16231_);
lean_dec(v_p_16231_);
lean_dec(v_m_16229_);
lean_dec(v_batch_16228_);
return v___x_16251_;
}
else
{
size_t v___x_16252_; size_t v___x_16253_; uint8_t v___x_16254_; 
v___x_16252_ = ((size_t)0ULL);
v___x_16253_ = lean_usize_of_nat(v___x_16248_);
v___x_16254_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00Submission_bmm_spec__0(v___y_16246_, v_B_16233_, v___x_16252_, v___x_16253_);
if (v___x_16254_ == 0)
{
lean_object* v___x_16255_; 
lean_dec_ref(v_B_16233_);
lean_dec_ref(v_A_16232_);
lean_dec(v_n_16230_);
v___x_16255_ = lp_competition_Submission_UnderflowZero_zeros(v_batch_16228_, v_m_16229_, v_p_16231_);
lean_dec(v_p_16231_);
lean_dec(v_m_16229_);
lean_dec(v_batch_16228_);
return v___x_16255_;
}
else
{
goto v___jp_16234_;
}
}
}
}
}
}