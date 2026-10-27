LEAN_EXPORT uint32_t lp_competition_Submission_R19GRS32Add_diagnosticEntry(uint32_t v_x_14704_, uint32_t v_y_14705_){
_start:
{
uint8_t v___y_14712_; uint8_t v___y_14726_; uint8_t v___y_14740_; uint8_t v___y_14757_; float v___y_14764_; float v___y_14765_; float v___y_14779_; uint8_t v___y_14780_; float v___y_14795_; uint8_t v___y_14810_; uint8_t v___y_14824_; uint8_t v___y_14838_; uint8_t v___y_14855_; float v___y_14862_; float v___y_14863_; float v___y_14877_; uint8_t v___y_14878_; float v___y_14893_; uint8_t v___y_14908_; uint8_t v___y_14922_; uint8_t v___y_14936_; uint8_t v___y_14953_; float v___y_14960_; float v___y_14961_; float v___y_14975_; uint8_t v___y_14976_; float v___y_14991_; uint32_t v___x_15000_; uint32_t v___x_15001_; uint32_t v___y_15003_; uint32_t v___y_15004_; uint8_t v___y_15005_; uint8_t v___y_15016_; uint8_t v___y_15029_; uint32_t v___x_15041_; uint32_t v_eu_15042_; uint32_t v___x_15043_; uint32_t v___x_15044_; uint32_t v___x_15045_; uint32_t v___y_15047_; uint32_t v___y_15048_; uint32_t v___y_15049_; uint32_t v___y_15050_; uint32_t v___y_15051_; uint32_t v___y_15052_; uint32_t v___y_15053_; uint32_t v___y_15076_; uint32_t v___y_15077_; uint32_t v___y_15078_; uint32_t v___y_15079_; uint32_t v___y_15080_; uint32_t v___y_15081_; uint32_t v___y_15090_; uint32_t v___y_15091_; uint32_t v___y_15092_; uint32_t v___y_15093_; uint8_t v___x_15113_; 
v___x_15000_ = 23;
v___x_15001_ = lean_uint32_shift_right(v_x_14704_, v___x_15000_);
v___x_15041_ = 255;
v_eu_15042_ = lean_uint32_land(v___x_15001_, v___x_15041_);
v___x_15043_ = 1;
v___x_15044_ = lean_uint32_sub(v_eu_15042_, v___x_15043_);
v___x_15045_ = 253;
v___x_15113_ = lean_uint32_dec_le(v___x_15044_, v___x_15045_);
if (v___x_15113_ == 0)
{
uint32_t v___x_15114_; uint32_t v_a_15115_; uint32_t v___x_15116_; uint32_t v___x_15117_; uint8_t v___x_15118_; 
v___x_15114_ = 2147483647;
v_a_15115_ = lean_uint32_land(v_x_14704_, v___x_15114_);
v___x_15116_ = 201326591;
v___x_15117_ = lean_uint32_sub(v_a_15115_, v___x_15043_);
v___x_15118_ = lean_uint32_dec_le(v___x_15116_, v___x_15117_);
if (v___x_15118_ == 0)
{
v___y_15029_ = v___x_15118_;
goto v___jp_15028_;
}
else
{
uint32_t v___x_15119_; uint8_t v___x_15120_; 
v___x_15119_ = 2139095040;
v___x_15120_ = lean_uint32_dec_lt(v_a_15115_, v___x_15119_);
v___y_15029_ = v___x_15120_;
goto v___jp_15028_;
}
}
else
{
uint32_t v___x_15121_; uint32_t v_ev_15122_; uint32_t v___x_15123_; uint8_t v___x_15124_; 
v___x_15121_ = lean_uint32_shift_right(v_y_14705_, v___x_15000_);
v_ev_15122_ = lean_uint32_land(v___x_15121_, v___x_15041_);
v___x_15123_ = lean_uint32_sub(v_ev_15122_, v___x_15043_);
v___x_15124_ = lean_uint32_dec_le(v___x_15123_, v___x_15045_);
if (v___x_15124_ == 0)
{
uint32_t v___x_15125_; uint32_t v_a_15126_; uint32_t v___x_15127_; uint32_t v___x_15128_; uint8_t v___x_15129_; 
v___x_15125_ = 2147483647;
v_a_15126_ = lean_uint32_land(v_x_14704_, v___x_15125_);
v___x_15127_ = 201326591;
v___x_15128_ = lean_uint32_sub(v_a_15126_, v___x_15043_);
v___x_15129_ = lean_uint32_dec_le(v___x_15127_, v___x_15128_);
if (v___x_15129_ == 0)
{
v___y_15016_ = v___x_15129_;
goto v___jp_15015_;
}
else
{
uint32_t v___x_15130_; uint8_t v___x_15131_; 
v___x_15130_ = 2139095040;
v___x_15131_ = lean_uint32_dec_lt(v_a_15126_, v___x_15130_);
v___y_15016_ = v___x_15131_;
goto v___jp_15015_;
}
}
else
{
uint32_t v___x_15132_; uint32_t v___x_15133_; uint32_t v___x_15134_; uint8_t v_swap_15135_; uint32_t v___y_15137_; uint32_t v___y_15138_; uint32_t v___y_15139_; uint32_t v___y_15141_; uint32_t v___y_15142_; uint32_t v___y_15144_; 
v___x_15132_ = 2147483647;
v___x_15133_ = lean_uint32_land(v_x_14704_, v___x_15132_);
v___x_15134_ = lean_uint32_land(v_y_14705_, v___x_15132_);
v_swap_15135_ = lean_uint32_dec_lt(v___x_15133_, v___x_15134_);
if (v_swap_15135_ == 0)
{
v___y_15144_ = v_x_14704_;
goto v___jp_15143_;
}
else
{
v___y_15144_ = v_y_14705_;
goto v___jp_15143_;
}
v___jp_15136_:
{
if (v_swap_15135_ == 0)
{
v___y_15090_ = v___y_15137_;
v___y_15091_ = v___y_15138_;
v___y_15092_ = v___y_15139_;
v___y_15093_ = v_ev_15122_;
goto v___jp_15089_;
}
else
{
v___y_15090_ = v___y_15137_;
v___y_15091_ = v___y_15138_;
v___y_15092_ = v___y_15139_;
v___y_15093_ = v_eu_15042_;
goto v___jp_15089_;
}
}
v___jp_15140_:
{
if (v_swap_15135_ == 0)
{
v___y_15137_ = v___y_15141_;
v___y_15138_ = v___y_15142_;
v___y_15139_ = v_eu_15042_;
goto v___jp_15136_;
}
else
{
v___y_15137_ = v___y_15141_;
v___y_15138_ = v___y_15142_;
v___y_15139_ = v_ev_15122_;
goto v___jp_15136_;
}
}
v___jp_15143_:
{
if (v_swap_15135_ == 0)
{
v___y_15141_ = v___y_15144_;
v___y_15142_ = v_y_14705_;
goto v___jp_15140_;
}
else
{
v___y_15141_ = v___y_15144_;
v___y_15142_ = v_x_14704_;
goto v___jp_15140_;
}
}
}
}
v___jp_14706_:
{
lean_object* v___x_14707_; lean_object* v___x_14708_; lean_object* v___x_14709_; uint32_t v___x_14710_; 
v___x_14707_ = lean_uint32_to_nat(v_x_14704_);
v___x_14708_ = lean_uint32_to_nat(v_y_14705_);
v___x_14709_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_14707_, v___x_14708_);
v___x_14710_ = lean_uint32_of_nat(v___x_14709_);
lean_dec(v___x_14709_);
return v___x_14710_;
}
v___jp_14711_:
{
if (v___y_14712_ == 0)
{
goto v___jp_14706_;
}
else
{
uint32_t v___x_14713_; uint32_t v___x_14714_; 
v___x_14713_ = 4194304;
v___x_14714_ = lean_uint32_lor(v_y_14705_, v___x_14713_);
return v___x_14714_;
}
}
v___jp_14715_:
{
uint32_t v___x_14716_; uint32_t v___x_14717_; uint32_t v___x_14718_; uint32_t v___x_14719_; uint8_t v___x_14720_; 
v___x_14716_ = 23;
v___x_14717_ = lean_uint32_shift_right(v_y_14705_, v___x_14716_);
v___x_14718_ = 255;
v___x_14719_ = lean_uint32_land(v___x_14717_, v___x_14718_);
v___x_14720_ = lean_uint32_dec_eq(v___x_14719_, v___x_14718_);
if (v___x_14720_ == 0)
{
v___y_14712_ = v___x_14720_;
goto v___jp_14711_;
}
else
{
uint32_t v___x_14721_; uint32_t v___x_14722_; uint32_t v___x_14723_; uint8_t v___x_14724_; 
v___x_14721_ = 8388607;
v___x_14722_ = lean_uint32_land(v_y_14705_, v___x_14721_);
v___x_14723_ = 0;
v___x_14724_ = lean_uint32_dec_eq(v___x_14722_, v___x_14723_);
if (v___x_14724_ == 0)
{
v___y_14712_ = v___x_14720_;
goto v___jp_14711_;
}
else
{
goto v___jp_14706_;
}
}
}
v___jp_14725_:
{
if (v___y_14726_ == 0)
{
goto v___jp_14715_;
}
else
{
uint32_t v___x_14727_; uint32_t v___x_14728_; 
v___x_14727_ = 4194304;
v___x_14728_ = lean_uint32_lor(v_x_14704_, v___x_14727_);
return v___x_14728_;
}
}
v___jp_14729_:
{
uint32_t v___x_14730_; uint32_t v___x_14731_; uint32_t v___x_14732_; uint32_t v___x_14733_; uint8_t v___x_14734_; 
v___x_14730_ = 23;
v___x_14731_ = lean_uint32_shift_right(v_x_14704_, v___x_14730_);
v___x_14732_ = 255;
v___x_14733_ = lean_uint32_land(v___x_14731_, v___x_14732_);
v___x_14734_ = lean_uint32_dec_eq(v___x_14733_, v___x_14732_);
if (v___x_14734_ == 0)
{
v___y_14726_ = v___x_14734_;
goto v___jp_14725_;
}
else
{
uint32_t v___x_14735_; uint32_t v___x_14736_; uint32_t v___x_14737_; uint8_t v___x_14738_; 
v___x_14735_ = 8388607;
v___x_14736_ = lean_uint32_land(v_x_14704_, v___x_14735_);
v___x_14737_ = 0;
v___x_14738_ = lean_uint32_dec_eq(v___x_14736_, v___x_14737_);
if (v___x_14738_ == 0)
{
v___y_14726_ = v___x_14734_;
goto v___jp_14725_;
}
else
{
goto v___jp_14715_;
}
}
}
v___jp_14739_:
{
if (v___y_14740_ == 0)
{
goto v___jp_14729_;
}
else
{
uint32_t v___x_14741_; uint32_t v___x_14742_; uint32_t v___x_14743_; uint8_t v___x_14744_; 
v___x_14741_ = 4194304;
v___x_14742_ = lean_uint32_land(v_y_14705_, v___x_14741_);
v___x_14743_ = 0;
v___x_14744_ = lean_uint32_dec_eq(v___x_14742_, v___x_14743_);
if (v___x_14744_ == 0)
{
goto v___jp_14729_;
}
else
{
uint32_t v___x_14745_; 
v___x_14745_ = lean_uint32_lor(v_y_14705_, v___x_14741_);
return v___x_14745_;
}
}
}
v___jp_14746_:
{
uint32_t v___x_14747_; uint32_t v___x_14748_; uint32_t v___x_14749_; uint32_t v___x_14750_; uint8_t v___x_14751_; 
v___x_14747_ = 23;
v___x_14748_ = lean_uint32_shift_right(v_y_14705_, v___x_14747_);
v___x_14749_ = 255;
v___x_14750_ = lean_uint32_land(v___x_14748_, v___x_14749_);
v___x_14751_ = lean_uint32_dec_eq(v___x_14750_, v___x_14749_);
if (v___x_14751_ == 0)
{
v___y_14740_ = v___x_14751_;
goto v___jp_14739_;
}
else
{
uint32_t v___x_14752_; uint32_t v___x_14753_; uint32_t v___x_14754_; uint8_t v___x_14755_; 
v___x_14752_ = 8388607;
v___x_14753_ = lean_uint32_land(v_y_14705_, v___x_14752_);
v___x_14754_ = 0;
v___x_14755_ = lean_uint32_dec_eq(v___x_14753_, v___x_14754_);
if (v___x_14755_ == 0)
{
v___y_14740_ = v___x_14751_;
goto v___jp_14739_;
}
else
{
goto v___jp_14729_;
}
}
}
v___jp_14756_:
{
if (v___y_14757_ == 0)
{
goto v___jp_14746_;
}
else
{
uint32_t v___x_14758_; uint32_t v___x_14759_; uint32_t v___x_14760_; uint8_t v___x_14761_; 
v___x_14758_ = 4194304;
v___x_14759_ = lean_uint32_land(v_x_14704_, v___x_14758_);
v___x_14760_ = 0;
v___x_14761_ = lean_uint32_dec_eq(v___x_14759_, v___x_14760_);
if (v___x_14761_ == 0)
{
goto v___jp_14746_;
}
else
{
uint32_t v___x_14762_; 
v___x_14762_ = lean_uint32_lor(v_x_14704_, v___x_14758_);
return v___x_14762_;
}
}
}
v___jp_14763_:
{
float v_result_14766_; uint8_t v___x_14767_; 
v_result_14766_ = lean_float32_add(v___y_14764_, v___y_14765_);
v___x_14767_ = lean_float32_beq(v_result_14766_, v_result_14766_);
if (v___x_14767_ == 0)
{
uint32_t v___x_14768_; uint32_t v___x_14769_; uint32_t v___x_14770_; uint32_t v___x_14771_; uint8_t v___x_14772_; 
v___x_14768_ = 23;
v___x_14769_ = lean_uint32_shift_right(v_x_14704_, v___x_14768_);
v___x_14770_ = 255;
v___x_14771_ = lean_uint32_land(v___x_14769_, v___x_14770_);
v___x_14772_ = lean_uint32_dec_eq(v___x_14771_, v___x_14770_);
if (v___x_14772_ == 0)
{
v___y_14757_ = v___x_14772_;
goto v___jp_14756_;
}
else
{
uint32_t v___x_14773_; uint32_t v___x_14774_; uint32_t v___x_14775_; uint8_t v___x_14776_; 
v___x_14773_ = 8388607;
v___x_14774_ = lean_uint32_land(v_x_14704_, v___x_14773_);
v___x_14775_ = 0;
v___x_14776_ = lean_uint32_dec_eq(v___x_14774_, v___x_14775_);
if (v___x_14776_ == 0)
{
v___y_14757_ = v___x_14772_;
goto v___jp_14756_;
}
else
{
goto v___jp_14746_;
}
}
}
else
{
uint32_t v___x_14777_; 
v___x_14777_ = lean_float32_to_bits(v_result_14766_);
return v___x_14777_;
}
}
v___jp_14778_:
{
if (v___y_14780_ == 0)
{
float v___x_14781_; 
v___x_14781_ = lean_float32_of_bits(v_y_14705_);
v___y_14764_ = v___y_14779_;
v___y_14765_ = v___x_14781_;
goto v___jp_14763_;
}
else
{
uint32_t v___x_14782_; uint32_t v___x_14783_; uint32_t v___x_14784_; uint32_t v___x_14785_; float v___x_14786_; lean_object* v___x_14787_; uint32_t v___x_14788_; uint32_t v___x_14789_; lean_object* v___x_14790_; lean_object* v___x_14791_; float v___x_14792_; float v___x_14793_; 
v___x_14782_ = 8388607;
v___x_14783_ = lean_uint32_land(v_y_14705_, v___x_14782_);
v___x_14784_ = 8388608;
v___x_14785_ = lean_uint32_lor(v___x_14783_, v___x_14784_);
v___x_14786_ = lean_uint32_to_float32(v___x_14785_);
v___x_14787_ = lp_competition_R2W01b_scaleTable;
v___x_14788_ = 23;
v___x_14789_ = lean_uint32_shift_right(v_y_14705_, v___x_14788_);
v___x_14790_ = lean_uint32_to_nat(v___x_14789_);
v___x_14791_ = lean_array_fget_borrowed(v___x_14787_, v___x_14790_);
lean_dec(v___x_14790_);
v___x_14792_ = lean_unbox_float32(v___x_14791_);
v___x_14793_ = lean_float32_mul(v___x_14786_, v___x_14792_);
v___y_14764_ = v___y_14779_;
v___y_14765_ = v___x_14793_;
goto v___jp_14763_;
}
}
v___jp_14794_:
{
uint32_t v___x_14796_; uint32_t v_a_14797_; uint32_t v___x_14798_; uint32_t v___x_14799_; uint32_t v___x_14800_; uint8_t v___x_14801_; 
v___x_14796_ = 2147483647;
v_a_14797_ = lean_uint32_land(v_y_14705_, v___x_14796_);
v___x_14798_ = 201326591;
v___x_14799_ = 1;
v___x_14800_ = lean_uint32_sub(v_a_14797_, v___x_14799_);
v___x_14801_ = lean_uint32_dec_le(v___x_14798_, v___x_14800_);
if (v___x_14801_ == 0)
{
v___y_14779_ = v___y_14795_;
v___y_14780_ = v___x_14801_;
goto v___jp_14778_;
}
else
{
uint32_t v___x_14802_; uint8_t v___x_14803_; 
v___x_14802_ = 2139095040;
v___x_14803_ = lean_uint32_dec_lt(v_a_14797_, v___x_14802_);
v___y_14779_ = v___y_14795_;
v___y_14780_ = v___x_14803_;
goto v___jp_14778_;
}
}
v___jp_14804_:
{
lean_object* v___x_14805_; lean_object* v___x_14806_; lean_object* v___x_14807_; uint32_t v___x_14808_; 
v___x_14805_ = lean_uint32_to_nat(v_x_14704_);
v___x_14806_ = lean_uint32_to_nat(v_y_14705_);
v___x_14807_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_14805_, v___x_14806_);
v___x_14808_ = lean_uint32_of_nat(v___x_14807_);
lean_dec(v___x_14807_);
return v___x_14808_;
}
v___jp_14809_:
{
if (v___y_14810_ == 0)
{
goto v___jp_14804_;
}
else
{
uint32_t v___x_14811_; uint32_t v___x_14812_; 
v___x_14811_ = 4194304;
v___x_14812_ = lean_uint32_lor(v_y_14705_, v___x_14811_);
return v___x_14812_;
}
}
v___jp_14813_:
{
uint32_t v___x_14814_; uint32_t v___x_14815_; uint32_t v___x_14816_; uint32_t v___x_14817_; uint8_t v___x_14818_; 
v___x_14814_ = 23;
v___x_14815_ = lean_uint32_shift_right(v_y_14705_, v___x_14814_);
v___x_14816_ = 255;
v___x_14817_ = lean_uint32_land(v___x_14815_, v___x_14816_);
v___x_14818_ = lean_uint32_dec_eq(v___x_14817_, v___x_14816_);
if (v___x_14818_ == 0)
{
v___y_14810_ = v___x_14818_;
goto v___jp_14809_;
}
else
{
uint32_t v___x_14819_; uint32_t v___x_14820_; uint32_t v___x_14821_; uint8_t v___x_14822_; 
v___x_14819_ = 8388607;
v___x_14820_ = lean_uint32_land(v_y_14705_, v___x_14819_);
v___x_14821_ = 0;
v___x_14822_ = lean_uint32_dec_eq(v___x_14820_, v___x_14821_);
if (v___x_14822_ == 0)
{
v___y_14810_ = v___x_14818_;
goto v___jp_14809_;
}
else
{
goto v___jp_14804_;
}
}
}
v___jp_14823_:
{
if (v___y_14824_ == 0)
{
goto v___jp_14813_;
}
else
{
uint32_t v___x_14825_; uint32_t v___x_14826_; 
v___x_14825_ = 4194304;
v___x_14826_ = lean_uint32_lor(v_x_14704_, v___x_14825_);
return v___x_14826_;
}
}
v___jp_14827_:
{
uint32_t v___x_14828_; uint32_t v___x_14829_; uint32_t v___x_14830_; uint32_t v___x_14831_; uint8_t v___x_14832_; 
v___x_14828_ = 23;
v___x_14829_ = lean_uint32_shift_right(v_x_14704_, v___x_14828_);
v___x_14830_ = 255;
v___x_14831_ = lean_uint32_land(v___x_14829_, v___x_14830_);
v___x_14832_ = lean_uint32_dec_eq(v___x_14831_, v___x_14830_);
if (v___x_14832_ == 0)
{
v___y_14824_ = v___x_14832_;
goto v___jp_14823_;
}
else
{
uint32_t v___x_14833_; uint32_t v___x_14834_; uint32_t v___x_14835_; uint8_t v___x_14836_; 
v___x_14833_ = 8388607;
v___x_14834_ = lean_uint32_land(v_x_14704_, v___x_14833_);
v___x_14835_ = 0;
v___x_14836_ = lean_uint32_dec_eq(v___x_14834_, v___x_14835_);
if (v___x_14836_ == 0)
{
v___y_14824_ = v___x_14832_;
goto v___jp_14823_;
}
else
{
goto v___jp_14813_;
}
}
}
v___jp_14837_:
{
if (v___y_14838_ == 0)
{
goto v___jp_14827_;
}
else
{
uint32_t v___x_14839_; uint32_t v___x_14840_; uint32_t v___x_14841_; uint8_t v___x_14842_; 
v___x_14839_ = 4194304;
v___x_14840_ = lean_uint32_land(v_y_14705_, v___x_14839_);
v___x_14841_ = 0;
v___x_14842_ = lean_uint32_dec_eq(v___x_14840_, v___x_14841_);
if (v___x_14842_ == 0)
{
goto v___jp_14827_;
}
else
{
uint32_t v___x_14843_; 
v___x_14843_ = lean_uint32_lor(v_y_14705_, v___x_14839_);
return v___x_14843_;
}
}
}
v___jp_14844_:
{
uint32_t v___x_14845_; uint32_t v___x_14846_; uint32_t v___x_14847_; uint32_t v___x_14848_; uint8_t v___x_14849_; 
v___x_14845_ = 23;
v___x_14846_ = lean_uint32_shift_right(v_y_14705_, v___x_14845_);
v___x_14847_ = 255;
v___x_14848_ = lean_uint32_land(v___x_14846_, v___x_14847_);
v___x_14849_ = lean_uint32_dec_eq(v___x_14848_, v___x_14847_);
if (v___x_14849_ == 0)
{
v___y_14838_ = v___x_14849_;
goto v___jp_14837_;
}
else
{
uint32_t v___x_14850_; uint32_t v___x_14851_; uint32_t v___x_14852_; uint8_t v___x_14853_; 
v___x_14850_ = 8388607;
v___x_14851_ = lean_uint32_land(v_y_14705_, v___x_14850_);
v___x_14852_ = 0;
v___x_14853_ = lean_uint32_dec_eq(v___x_14851_, v___x_14852_);
if (v___x_14853_ == 0)
{
v___y_14838_ = v___x_14849_;
goto v___jp_14837_;
}
else
{
goto v___jp_14827_;
}
}
}
v___jp_14854_:
{
if (v___y_14855_ == 0)
{
goto v___jp_14844_;
}
else
{
uint32_t v___x_14856_; uint32_t v___x_14857_; uint32_t v___x_14858_; uint8_t v___x_14859_; 
v___x_14856_ = 4194304;
v___x_14857_ = lean_uint32_land(v_x_14704_, v___x_14856_);
v___x_14858_ = 0;
v___x_14859_ = lean_uint32_dec_eq(v___x_14857_, v___x_14858_);
if (v___x_14859_ == 0)
{
goto v___jp_14844_;
}
else
{
uint32_t v___x_14860_; 
v___x_14860_ = lean_uint32_lor(v_x_14704_, v___x_14856_);
return v___x_14860_;
}
}
}
v___jp_14861_:
{
float v_result_14864_; uint8_t v___x_14865_; 
v_result_14864_ = lean_float32_add(v___y_14862_, v___y_14863_);
v___x_14865_ = lean_float32_beq(v_result_14864_, v_result_14864_);
if (v___x_14865_ == 0)
{
uint32_t v___x_14866_; uint32_t v___x_14867_; uint32_t v___x_14868_; uint32_t v___x_14869_; uint8_t v___x_14870_; 
v___x_14866_ = 23;
v___x_14867_ = lean_uint32_shift_right(v_x_14704_, v___x_14866_);
v___x_14868_ = 255;
v___x_14869_ = lean_uint32_land(v___x_14867_, v___x_14868_);
v___x_14870_ = lean_uint32_dec_eq(v___x_14869_, v___x_14868_);
if (v___x_14870_ == 0)
{
v___y_14855_ = v___x_14870_;
goto v___jp_14854_;
}
else
{
uint32_t v___x_14871_; uint32_t v___x_14872_; uint32_t v___x_14873_; uint8_t v___x_14874_; 
v___x_14871_ = 8388607;
v___x_14872_ = lean_uint32_land(v_x_14704_, v___x_14871_);
v___x_14873_ = 0;
v___x_14874_ = lean_uint32_dec_eq(v___x_14872_, v___x_14873_);
if (v___x_14874_ == 0)
{
v___y_14855_ = v___x_14870_;
goto v___jp_14854_;
}
else
{
goto v___jp_14844_;
}
}
}
else
{
uint32_t v___x_14875_; 
v___x_14875_ = lean_float32_to_bits(v_result_14864_);
return v___x_14875_;
}
}
v___jp_14876_:
{
if (v___y_14878_ == 0)
{
float v___x_14879_; 
v___x_14879_ = lean_float32_of_bits(v_y_14705_);
v___y_14862_ = v___y_14877_;
v___y_14863_ = v___x_14879_;
goto v___jp_14861_;
}
else
{
uint32_t v___x_14880_; uint32_t v___x_14881_; uint32_t v___x_14882_; uint32_t v___x_14883_; float v___x_14884_; lean_object* v___x_14885_; uint32_t v___x_14886_; uint32_t v___x_14887_; lean_object* v___x_14888_; lean_object* v___x_14889_; float v___x_14890_; float v___x_14891_; 
v___x_14880_ = 8388607;
v___x_14881_ = lean_uint32_land(v_y_14705_, v___x_14880_);
v___x_14882_ = 8388608;
v___x_14883_ = lean_uint32_lor(v___x_14881_, v___x_14882_);
v___x_14884_ = lean_uint32_to_float32(v___x_14883_);
v___x_14885_ = lp_competition_R2W01b_scaleTable;
v___x_14886_ = 23;
v___x_14887_ = lean_uint32_shift_right(v_y_14705_, v___x_14886_);
v___x_14888_ = lean_uint32_to_nat(v___x_14887_);
v___x_14889_ = lean_array_fget_borrowed(v___x_14885_, v___x_14888_);
lean_dec(v___x_14888_);
v___x_14890_ = lean_unbox_float32(v___x_14889_);
v___x_14891_ = lean_float32_mul(v___x_14884_, v___x_14890_);
v___y_14862_ = v___y_14877_;
v___y_14863_ = v___x_14891_;
goto v___jp_14861_;
}
}
v___jp_14892_:
{
uint32_t v___x_14894_; uint32_t v_a_14895_; uint32_t v___x_14896_; uint32_t v___x_14897_; uint32_t v___x_14898_; uint8_t v___x_14899_; 
v___x_14894_ = 2147483647;
v_a_14895_ = lean_uint32_land(v_y_14705_, v___x_14894_);
v___x_14896_ = 201326591;
v___x_14897_ = 1;
v___x_14898_ = lean_uint32_sub(v_a_14895_, v___x_14897_);
v___x_14899_ = lean_uint32_dec_le(v___x_14896_, v___x_14898_);
if (v___x_14899_ == 0)
{
v___y_14877_ = v___y_14893_;
v___y_14878_ = v___x_14899_;
goto v___jp_14876_;
}
else
{
uint32_t v___x_14900_; uint8_t v___x_14901_; 
v___x_14900_ = 2139095040;
v___x_14901_ = lean_uint32_dec_lt(v_a_14895_, v___x_14900_);
v___y_14877_ = v___y_14893_;
v___y_14878_ = v___x_14901_;
goto v___jp_14876_;
}
}
v___jp_14902_:
{
lean_object* v___x_14903_; lean_object* v___x_14904_; lean_object* v___x_14905_; uint32_t v___x_14906_; 
v___x_14903_ = lean_uint32_to_nat(v_x_14704_);
v___x_14904_ = lean_uint32_to_nat(v_y_14705_);
v___x_14905_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_14903_, v___x_14904_);
v___x_14906_ = lean_uint32_of_nat(v___x_14905_);
lean_dec(v___x_14905_);
return v___x_14906_;
}
v___jp_14907_:
{
if (v___y_14908_ == 0)
{
goto v___jp_14902_;
}
else
{
uint32_t v___x_14909_; uint32_t v___x_14910_; 
v___x_14909_ = 4194304;
v___x_14910_ = lean_uint32_lor(v_y_14705_, v___x_14909_);
return v___x_14910_;
}
}
v___jp_14911_:
{
uint32_t v___x_14912_; uint32_t v___x_14913_; uint32_t v___x_14914_; uint32_t v___x_14915_; uint8_t v___x_14916_; 
v___x_14912_ = 23;
v___x_14913_ = lean_uint32_shift_right(v_y_14705_, v___x_14912_);
v___x_14914_ = 255;
v___x_14915_ = lean_uint32_land(v___x_14913_, v___x_14914_);
v___x_14916_ = lean_uint32_dec_eq(v___x_14915_, v___x_14914_);
if (v___x_14916_ == 0)
{
v___y_14908_ = v___x_14916_;
goto v___jp_14907_;
}
else
{
uint32_t v___x_14917_; uint32_t v___x_14918_; uint32_t v___x_14919_; uint8_t v___x_14920_; 
v___x_14917_ = 8388607;
v___x_14918_ = lean_uint32_land(v_y_14705_, v___x_14917_);
v___x_14919_ = 0;
v___x_14920_ = lean_uint32_dec_eq(v___x_14918_, v___x_14919_);
if (v___x_14920_ == 0)
{
v___y_14908_ = v___x_14916_;
goto v___jp_14907_;
}
else
{
goto v___jp_14902_;
}
}
}
v___jp_14921_:
{
if (v___y_14922_ == 0)
{
goto v___jp_14911_;
}
else
{
uint32_t v___x_14923_; uint32_t v___x_14924_; 
v___x_14923_ = 4194304;
v___x_14924_ = lean_uint32_lor(v_x_14704_, v___x_14923_);
return v___x_14924_;
}
}
v___jp_14925_:
{
uint32_t v___x_14926_; uint32_t v___x_14927_; uint32_t v___x_14928_; uint32_t v___x_14929_; uint8_t v___x_14930_; 
v___x_14926_ = 23;
v___x_14927_ = lean_uint32_shift_right(v_x_14704_, v___x_14926_);
v___x_14928_ = 255;
v___x_14929_ = lean_uint32_land(v___x_14927_, v___x_14928_);
v___x_14930_ = lean_uint32_dec_eq(v___x_14929_, v___x_14928_);
if (v___x_14930_ == 0)
{
v___y_14922_ = v___x_14930_;
goto v___jp_14921_;
}
else
{
uint32_t v___x_14931_; uint32_t v___x_14932_; uint32_t v___x_14933_; uint8_t v___x_14934_; 
v___x_14931_ = 8388607;
v___x_14932_ = lean_uint32_land(v_x_14704_, v___x_14931_);
v___x_14933_ = 0;
v___x_14934_ = lean_uint32_dec_eq(v___x_14932_, v___x_14933_);
if (v___x_14934_ == 0)
{
v___y_14922_ = v___x_14930_;
goto v___jp_14921_;
}
else
{
goto v___jp_14911_;
}
}
}
v___jp_14935_:
{
if (v___y_14936_ == 0)
{
goto v___jp_14925_;
}
else
{
uint32_t v___x_14937_; uint32_t v___x_14938_; uint32_t v___x_14939_; uint8_t v___x_14940_; 
v___x_14937_ = 4194304;
v___x_14938_ = lean_uint32_land(v_y_14705_, v___x_14937_);
v___x_14939_ = 0;
v___x_14940_ = lean_uint32_dec_eq(v___x_14938_, v___x_14939_);
if (v___x_14940_ == 0)
{
goto v___jp_14925_;
}
else
{
uint32_t v___x_14941_; 
v___x_14941_ = lean_uint32_lor(v_y_14705_, v___x_14937_);
return v___x_14941_;
}
}
}
v___jp_14942_:
{
uint32_t v___x_14943_; uint32_t v___x_14944_; uint32_t v___x_14945_; uint32_t v___x_14946_; uint8_t v___x_14947_; 
v___x_14943_ = 23;
v___x_14944_ = lean_uint32_shift_right(v_y_14705_, v___x_14943_);
v___x_14945_ = 255;
v___x_14946_ = lean_uint32_land(v___x_14944_, v___x_14945_);
v___x_14947_ = lean_uint32_dec_eq(v___x_14946_, v___x_14945_);
if (v___x_14947_ == 0)
{
v___y_14936_ = v___x_14947_;
goto v___jp_14935_;
}
else
{
uint32_t v___x_14948_; uint32_t v___x_14949_; uint32_t v___x_14950_; uint8_t v___x_14951_; 
v___x_14948_ = 8388607;
v___x_14949_ = lean_uint32_land(v_y_14705_, v___x_14948_);
v___x_14950_ = 0;
v___x_14951_ = lean_uint32_dec_eq(v___x_14949_, v___x_14950_);
if (v___x_14951_ == 0)
{
v___y_14936_ = v___x_14947_;
goto v___jp_14935_;
}
else
{
goto v___jp_14925_;
}
}
}
v___jp_14952_:
{
if (v___y_14953_ == 0)
{
goto v___jp_14942_;
}
else
{
uint32_t v___x_14954_; uint32_t v___x_14955_; uint32_t v___x_14956_; uint8_t v___x_14957_; 
v___x_14954_ = 4194304;
v___x_14955_ = lean_uint32_land(v_x_14704_, v___x_14954_);
v___x_14956_ = 0;
v___x_14957_ = lean_uint32_dec_eq(v___x_14955_, v___x_14956_);
if (v___x_14957_ == 0)
{
goto v___jp_14942_;
}
else
{
uint32_t v___x_14958_; 
v___x_14958_ = lean_uint32_lor(v_x_14704_, v___x_14954_);
return v___x_14958_;
}
}
}
v___jp_14959_:
{
float v_result_14962_; uint8_t v___x_14963_; 
v_result_14962_ = lean_float32_add(v___y_14960_, v___y_14961_);
v___x_14963_ = lean_float32_beq(v_result_14962_, v_result_14962_);
if (v___x_14963_ == 0)
{
uint32_t v___x_14964_; uint32_t v___x_14965_; uint32_t v___x_14966_; uint32_t v___x_14967_; uint8_t v___x_14968_; 
v___x_14964_ = 23;
v___x_14965_ = lean_uint32_shift_right(v_x_14704_, v___x_14964_);
v___x_14966_ = 255;
v___x_14967_ = lean_uint32_land(v___x_14965_, v___x_14966_);
v___x_14968_ = lean_uint32_dec_eq(v___x_14967_, v___x_14966_);
if (v___x_14968_ == 0)
{
v___y_14953_ = v___x_14968_;
goto v___jp_14952_;
}
else
{
uint32_t v___x_14969_; uint32_t v___x_14970_; uint32_t v___x_14971_; uint8_t v___x_14972_; 
v___x_14969_ = 8388607;
v___x_14970_ = lean_uint32_land(v_x_14704_, v___x_14969_);
v___x_14971_ = 0;
v___x_14972_ = lean_uint32_dec_eq(v___x_14970_, v___x_14971_);
if (v___x_14972_ == 0)
{
v___y_14953_ = v___x_14968_;
goto v___jp_14952_;
}
else
{
goto v___jp_14942_;
}
}
}
else
{
uint32_t v___x_14973_; 
v___x_14973_ = lean_float32_to_bits(v_result_14962_);
return v___x_14973_;
}
}
v___jp_14974_:
{
if (v___y_14976_ == 0)
{
float v___x_14977_; 
v___x_14977_ = lean_float32_of_bits(v_y_14705_);
v___y_14960_ = v___y_14975_;
v___y_14961_ = v___x_14977_;
goto v___jp_14959_;
}
else
{
uint32_t v___x_14978_; uint32_t v___x_14979_; uint32_t v___x_14980_; uint32_t v___x_14981_; float v___x_14982_; lean_object* v___x_14983_; uint32_t v___x_14984_; uint32_t v___x_14985_; lean_object* v___x_14986_; lean_object* v___x_14987_; float v___x_14988_; float v___x_14989_; 
v___x_14978_ = 8388607;
v___x_14979_ = lean_uint32_land(v_y_14705_, v___x_14978_);
v___x_14980_ = 8388608;
v___x_14981_ = lean_uint32_lor(v___x_14979_, v___x_14980_);
v___x_14982_ = lean_uint32_to_float32(v___x_14981_);
v___x_14983_ = lp_competition_R2W01b_scaleTable;
v___x_14984_ = 23;
v___x_14985_ = lean_uint32_shift_right(v_y_14705_, v___x_14984_);
v___x_14986_ = lean_uint32_to_nat(v___x_14985_);
v___x_14987_ = lean_array_fget_borrowed(v___x_14983_, v___x_14986_);
lean_dec(v___x_14986_);
v___x_14988_ = lean_unbox_float32(v___x_14987_);
v___x_14989_ = lean_float32_mul(v___x_14982_, v___x_14988_);
v___y_14960_ = v___y_14975_;
v___y_14961_ = v___x_14989_;
goto v___jp_14959_;
}
}
v___jp_14990_:
{
uint32_t v___x_14992_; uint32_t v_a_14993_; uint32_t v___x_14994_; uint32_t v___x_14995_; uint32_t v___x_14996_; uint8_t v___x_14997_; 
v___x_14992_ = 2147483647;
v_a_14993_ = lean_uint32_land(v_y_14705_, v___x_14992_);
v___x_14994_ = 201326591;
v___x_14995_ = 1;
v___x_14996_ = lean_uint32_sub(v_a_14993_, v___x_14995_);
v___x_14997_ = lean_uint32_dec_le(v___x_14994_, v___x_14996_);
if (v___x_14997_ == 0)
{
v___y_14975_ = v___y_14991_;
v___y_14976_ = v___x_14997_;
goto v___jp_14974_;
}
else
{
uint32_t v___x_14998_; uint8_t v___x_14999_; 
v___x_14998_ = 2139095040;
v___x_14999_ = lean_uint32_dec_lt(v_a_14993_, v___x_14998_);
v___y_14975_ = v___y_14991_;
v___y_14976_ = v___x_14999_;
goto v___jp_14974_;
}
}
v___jp_15002_:
{
if (v___y_15005_ == 0)
{
float v___x_15006_; 
v___x_15006_ = lean_float32_of_bits(v_x_14704_);
v___y_14795_ = v___x_15006_;
goto v___jp_14794_;
}
else
{
uint32_t v___x_15007_; uint32_t v___x_15008_; float v___x_15009_; lean_object* v___x_15010_; lean_object* v___x_15011_; lean_object* v___x_15012_; float v___x_15013_; float v___x_15014_; 
v___x_15007_ = lean_uint32_land(v_x_14704_, v___y_15004_);
v___x_15008_ = lean_uint32_lor(v___x_15007_, v___y_15003_);
v___x_15009_ = lean_uint32_to_float32(v___x_15008_);
v___x_15010_ = lp_competition_R2W01b_scaleTable;
v___x_15011_ = lean_uint32_to_nat(v___x_15001_);
v___x_15012_ = lean_array_fget_borrowed(v___x_15010_, v___x_15011_);
lean_dec(v___x_15011_);
v___x_15013_ = lean_unbox_float32(v___x_15012_);
v___x_15014_ = lean_float32_mul(v___x_15009_, v___x_15013_);
v___y_14795_ = v___x_15014_;
goto v___jp_14794_;
}
}
v___jp_15015_:
{
if (v___y_15016_ == 0)
{
float v___x_15017_; 
v___x_15017_ = lean_float32_of_bits(v_x_14704_);
v___y_14893_ = v___x_15017_;
goto v___jp_14892_;
}
else
{
uint32_t v___x_15018_; uint32_t v___x_15019_; uint32_t v___x_15020_; uint32_t v___x_15021_; float v___x_15022_; lean_object* v___x_15023_; lean_object* v___x_15024_; lean_object* v___x_15025_; float v___x_15026_; float v___x_15027_; 
v___x_15018_ = 8388607;
v___x_15019_ = lean_uint32_land(v_x_14704_, v___x_15018_);
v___x_15020_ = 8388608;
v___x_15021_ = lean_uint32_lor(v___x_15019_, v___x_15020_);
v___x_15022_ = lean_uint32_to_float32(v___x_15021_);
v___x_15023_ = lp_competition_R2W01b_scaleTable;
v___x_15024_ = lean_uint32_to_nat(v___x_15001_);
v___x_15025_ = lean_array_fget_borrowed(v___x_15023_, v___x_15024_);
lean_dec(v___x_15024_);
v___x_15026_ = lean_unbox_float32(v___x_15025_);
v___x_15027_ = lean_float32_mul(v___x_15022_, v___x_15026_);
v___y_14893_ = v___x_15027_;
goto v___jp_14892_;
}
}
v___jp_15028_:
{
if (v___y_15029_ == 0)
{
float v___x_15030_; 
v___x_15030_ = lean_float32_of_bits(v_x_14704_);
v___y_14991_ = v___x_15030_;
goto v___jp_14990_;
}
else
{
uint32_t v___x_15031_; uint32_t v___x_15032_; uint32_t v___x_15033_; uint32_t v___x_15034_; float v___x_15035_; lean_object* v___x_15036_; lean_object* v___x_15037_; lean_object* v___x_15038_; float v___x_15039_; float v___x_15040_; 
v___x_15031_ = 8388607;
v___x_15032_ = lean_uint32_land(v_x_14704_, v___x_15031_);
v___x_15033_ = 8388608;
v___x_15034_ = lean_uint32_lor(v___x_15032_, v___x_15033_);
v___x_15035_ = lean_uint32_to_float32(v___x_15034_);
v___x_15036_ = lp_competition_R2W01b_scaleTable;
v___x_15037_ = lean_uint32_to_nat(v___x_15001_);
v___x_15038_ = lean_array_fget_borrowed(v___x_15036_, v___x_15037_);
lean_dec(v___x_15037_);
v___x_15039_ = lean_unbox_float32(v___x_15038_);
v___x_15040_ = lean_float32_mul(v___x_15035_, v___x_15039_);
v___y_14991_ = v___x_15040_;
goto v___jp_14990_;
}
}
v___jp_15046_:
{
uint8_t v___x_15054_; 
v___x_15054_ = lean_uint32_dec_eq(v___y_15053_, v___y_15047_);
if (v___x_15054_ == 0)
{
float v___x_15055_; uint32_t v_mid_15056_; uint32_t v___x_15057_; uint32_t v___x_15058_; uint32_t v___x_15059_; uint32_t v_e_15060_; uint32_t v___x_15061_; uint8_t v___x_15062_; 
v___x_15055_ = lean_uint32_to_float32(v___y_15053_);
v_mid_15056_ = lean_float32_to_bits(v___x_15055_);
v___x_15057_ = lean_uint32_shift_right(v_mid_15056_, v___x_15000_);
v___x_15058_ = lean_uint32_add(v___x_15057_, v___y_15051_);
v___x_15059_ = 153;
v_e_15060_ = lean_uint32_sub(v___x_15058_, v___x_15059_);
v___x_15061_ = lean_uint32_sub(v_e_15060_, v___x_15043_);
v___x_15062_ = lean_uint32_dec_le(v___x_15061_, v___x_15045_);
if (v___x_15062_ == 0)
{
uint32_t v___x_15063_; uint32_t v_a_15064_; uint32_t v___x_15065_; uint32_t v___x_15066_; uint8_t v___x_15067_; 
v___x_15063_ = 2147483647;
v_a_15064_ = lean_uint32_land(v_x_14704_, v___x_15063_);
v___x_15065_ = 201326591;
v___x_15066_ = lean_uint32_sub(v_a_15064_, v___x_15043_);
v___x_15067_ = lean_uint32_dec_le(v___x_15065_, v___x_15066_);
if (v___x_15067_ == 0)
{
v___y_15003_ = v___y_15049_;
v___y_15004_ = v___y_15050_;
v___y_15005_ = v___x_15067_;
goto v___jp_15002_;
}
else
{
uint32_t v___x_15068_; uint8_t v___x_15069_; 
v___x_15068_ = 2139095040;
v___x_15069_ = lean_uint32_dec_lt(v_a_15064_, v___x_15068_);
v___y_15003_ = v___y_15049_;
v___y_15004_ = v___y_15050_;
v___y_15005_ = v___x_15069_;
goto v___jp_15002_;
}
}
else
{
uint32_t v___x_15070_; uint32_t v___x_15071_; uint32_t v___x_15072_; uint32_t v___x_15073_; uint32_t v___x_15074_; 
v___x_15070_ = lean_uint32_land(v___y_15048_, v___y_15052_);
v___x_15071_ = lean_uint32_shift_left(v_e_15060_, v___x_15000_);
v___x_15072_ = lean_uint32_lor(v___x_15070_, v___x_15071_);
v___x_15073_ = lean_uint32_land(v_mid_15056_, v___y_15050_);
v___x_15074_ = lean_uint32_lor(v___x_15072_, v___x_15073_);
return v___x_15074_;
}
}
else
{
return v___y_15047_;
}
}
v___jp_15075_:
{
uint32_t v___x_15082_; uint32_t v___x_15083_; uint32_t v___x_15084_; uint32_t v___x_15085_; uint8_t v_same_15086_; 
v___x_15082_ = lean_uint32_xor(v_x_14704_, v_y_14705_);
v___x_15083_ = 2147483648;
v___x_15084_ = lean_uint32_land(v___x_15082_, v___x_15083_);
v___x_15085_ = 0;
v_same_15086_ = lean_uint32_dec_eq(v___x_15084_, v___x_15085_);
if (v_same_15086_ == 0)
{
uint32_t v___x_15087_; 
v___x_15087_ = lean_uint32_sub(v___y_15080_, v___y_15081_);
v___y_15047_ = v___x_15085_;
v___y_15048_ = v___y_15076_;
v___y_15049_ = v___y_15077_;
v___y_15050_ = v___y_15078_;
v___y_15051_ = v___y_15079_;
v___y_15052_ = v___x_15083_;
v___y_15053_ = v___x_15087_;
goto v___jp_15046_;
}
else
{
uint32_t v___x_15088_; 
v___x_15088_ = lean_uint32_add(v___y_15080_, v___y_15081_);
v___y_15047_ = v___x_15085_;
v___y_15048_ = v___y_15076_;
v___y_15049_ = v___y_15077_;
v___y_15050_ = v___y_15078_;
v___y_15051_ = v___y_15079_;
v___y_15052_ = v___x_15083_;
v___y_15053_ = v___x_15088_;
goto v___jp_15046_;
}
}
v___jp_15089_:
{
uint32_t v___x_15094_; uint32_t v___x_15095_; uint32_t v___x_15096_; uint32_t v___x_15097_; uint32_t v___x_15098_; uint32_t v_a_15099_; uint32_t v___x_15100_; uint32_t v___x_15101_; uint8_t v___x_15102_; 
v___x_15094_ = 8388607;
v___x_15095_ = lean_uint32_land(v___y_15090_, v___x_15094_);
v___x_15096_ = 8388608;
v___x_15097_ = lean_uint32_lor(v___x_15095_, v___x_15096_);
v___x_15098_ = 3;
v_a_15099_ = lean_uint32_shift_left(v___x_15097_, v___x_15098_);
v___x_15100_ = lean_uint32_sub(v___y_15092_, v___y_15093_);
v___x_15101_ = 32;
v___x_15102_ = lean_uint32_dec_lt(v___x_15100_, v___x_15101_);
if (v___x_15102_ == 0)
{
v___y_15076_ = v___y_15090_;
v___y_15077_ = v___x_15096_;
v___y_15078_ = v___x_15094_;
v___y_15079_ = v___y_15092_;
v___y_15080_ = v_a_15099_;
v___y_15081_ = v___x_15043_;
goto v___jp_15075_;
}
else
{
uint32_t v___x_15103_; uint32_t v___x_15104_; uint32_t v_b_15105_; uint32_t v___x_15106_; uint32_t v___x_15107_; uint32_t v___x_15108_; uint32_t v___x_15109_; uint32_t v___x_15110_; uint8_t v___x_15111_; 
v___x_15103_ = lean_uint32_land(v___y_15091_, v___x_15094_);
v___x_15104_ = lean_uint32_lor(v___x_15103_, v___x_15096_);
v_b_15105_ = lean_uint32_shift_left(v___x_15104_, v___x_15098_);
v___x_15106_ = lean_uint32_shift_right(v_b_15105_, v___x_15100_);
v___x_15107_ = lean_uint32_shift_left(v___x_15043_, v___x_15100_);
v___x_15108_ = lean_uint32_sub(v___x_15107_, v___x_15043_);
v___x_15109_ = lean_uint32_land(v_b_15105_, v___x_15108_);
v___x_15110_ = 0;
v___x_15111_ = lean_uint32_dec_eq(v___x_15109_, v___x_15110_);
if (v___x_15111_ == 0)
{
uint32_t v___x_15112_; 
v___x_15112_ = lean_uint32_lor(v___x_15106_, v___x_15043_);
v___y_15076_ = v___y_15090_;
v___y_15077_ = v___x_15096_;
v___y_15078_ = v___x_15094_;
v___y_15079_ = v___y_15092_;
v___y_15080_ = v_a_15099_;
v___y_15081_ = v___x_15112_;
goto v___jp_15075_;
}
else
{
v___y_15076_ = v___y_15090_;
v___y_15077_ = v___x_15096_;
v___y_15078_ = v___x_15094_;
v___y_15079_ = v___y_15092_;
v___y_15080_ = v_a_15099_;
v___y_15081_ = v___x_15106_;
goto v___jp_15075_;
}
}
}
}
}
