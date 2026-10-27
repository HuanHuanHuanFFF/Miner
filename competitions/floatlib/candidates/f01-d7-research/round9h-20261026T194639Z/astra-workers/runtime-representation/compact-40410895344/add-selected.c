LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
uint8_t v___y_9_; uint8_t v___y_23_; uint8_t v___y_37_; uint8_t v___y_54_; float v___y_61_; float v___y_74_; uint8_t v___y_75_; float v___y_92_; uint8_t v___y_102_; float v___y_117_; uint8_t v___y_118_; float v___y_135_; uint8_t v___y_145_; uint8_t v___x_159_; 
v___x_159_ = lp_competition_R19CompactScales_valid;
if (v___x_159_ == 0)
{
uint32_t v___x_160_; uint32_t v_a_161_; uint32_t v___x_162_; uint32_t v___x_163_; uint32_t v___x_164_; uint8_t v___x_165_; 
v___x_160_ = 2147483647;
v_a_161_ = lean_uint32_land(v___y_1_, v___x_160_);
v___x_162_ = 201326591;
v___x_163_ = 1;
v___x_164_ = lean_uint32_sub(v_a_161_, v___x_163_);
v___x_165_ = lean_uint32_dec_le(v___x_162_, v___x_164_);
if (v___x_165_ == 0)
{
v___y_102_ = v___x_165_;
goto v___jp_101_;
}
else
{
uint32_t v___x_166_; uint8_t v___x_167_; 
v___x_166_ = 2139095040;
v___x_167_ = lean_uint32_dec_lt(v_a_161_, v___x_166_);
v___y_102_ = v___x_167_;
goto v___jp_101_;
}
}
else
{
uint32_t v___x_168_; uint32_t v_a_169_; uint32_t v___x_170_; uint32_t v___x_171_; uint32_t v___x_172_; uint8_t v___x_173_; 
v___x_168_ = 2147483647;
v_a_169_ = lean_uint32_land(v___y_1_, v___x_168_);
v___x_170_ = 201326591;
v___x_171_ = 1;
v___x_172_ = lean_uint32_sub(v_a_169_, v___x_171_);
v___x_173_ = lean_uint32_dec_le(v___x_170_, v___x_172_);
if (v___x_173_ == 0)
{
v___y_145_ = v___x_173_;
goto v___jp_144_;
}
else
{
uint32_t v___x_174_; uint8_t v___x_175_; 
v___x_174_ = 2139095040;
v___x_175_ = lean_uint32_dec_lt(v_a_169_, v___x_174_);
v___y_145_ = v___x_175_;
goto v___jp_144_;
}
}
v___jp_3_:
{
lean_object* v___x_4_; lean_object* v___x_5_; lean_object* v___x_6_; uint32_t v___x_7_; 
v___x_4_ = lean_uint32_to_nat(v___y_1_);
v___x_5_ = lean_uint32_to_nat(v___y_2_);
v___x_6_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_4_, v___x_5_);
v___x_7_ = lean_uint32_of_nat(v___x_6_);
lean_dec(v___x_6_);
return v___x_7_;
}
v___jp_8_:
{
if (v___y_9_ == 0)
{
goto v___jp_3_;
}
else
{
uint32_t v___x_10_; uint32_t v___x_11_; 
v___x_10_ = 4194304;
v___x_11_ = lean_uint32_lor(v___y_2_, v___x_10_);
return v___x_11_;
}
}
v___jp_12_:
{
uint32_t v___x_13_; uint32_t v___x_14_; uint32_t v___x_15_; uint32_t v___x_16_; uint8_t v___x_17_; 
v___x_13_ = 23;
v___x_14_ = lean_uint32_shift_right(v___y_2_, v___x_13_);
v___x_15_ = 255;
v___x_16_ = lean_uint32_land(v___x_14_, v___x_15_);
v___x_17_ = lean_uint32_dec_eq(v___x_16_, v___x_15_);
if (v___x_17_ == 0)
{
v___y_9_ = v___x_17_;
goto v___jp_8_;
}
else
{
uint32_t v___x_18_; uint32_t v___x_19_; uint32_t v___x_20_; uint8_t v___x_21_; 
v___x_18_ = 8388607;
v___x_19_ = lean_uint32_land(v___y_2_, v___x_18_);
v___x_20_ = 0;
v___x_21_ = lean_uint32_dec_eq(v___x_19_, v___x_20_);
if (v___x_21_ == 0)
{
v___y_9_ = v___x_17_;
goto v___jp_8_;
}
else
{
goto v___jp_3_;
}
}
}
v___jp_22_:
{
if (v___y_23_ == 0)
{
goto v___jp_12_;
}
else
{
uint32_t v___x_24_; uint32_t v___x_25_; 
v___x_24_ = 4194304;
v___x_25_ = lean_uint32_lor(v___y_1_, v___x_24_);
return v___x_25_;
}
}
v___jp_26_:
{
uint32_t v___x_27_; uint32_t v___x_28_; uint32_t v___x_29_; uint32_t v___x_30_; uint8_t v___x_31_; 
v___x_27_ = 23;
v___x_28_ = lean_uint32_shift_right(v___y_1_, v___x_27_);
v___x_29_ = 255;
v___x_30_ = lean_uint32_land(v___x_28_, v___x_29_);
v___x_31_ = lean_uint32_dec_eq(v___x_30_, v___x_29_);
if (v___x_31_ == 0)
{
v___y_23_ = v___x_31_;
goto v___jp_22_;
}
else
{
uint32_t v___x_32_; uint32_t v___x_33_; uint32_t v___x_34_; uint8_t v___x_35_; 
v___x_32_ = 8388607;
v___x_33_ = lean_uint32_land(v___y_1_, v___x_32_);
v___x_34_ = 0;
v___x_35_ = lean_uint32_dec_eq(v___x_33_, v___x_34_);
if (v___x_35_ == 0)
{
v___y_23_ = v___x_31_;
goto v___jp_22_;
}
else
{
goto v___jp_12_;
}
}
}
v___jp_36_:
{
if (v___y_37_ == 0)
{
goto v___jp_26_;
}
else
{
uint32_t v___x_38_; uint32_t v___x_39_; uint32_t v___x_40_; uint8_t v___x_41_; 
v___x_38_ = 4194304;
v___x_39_ = lean_uint32_land(v___y_2_, v___x_38_);
v___x_40_ = 0;
v___x_41_ = lean_uint32_dec_eq(v___x_39_, v___x_40_);
if (v___x_41_ == 0)
{
goto v___jp_26_;
}
else
{
uint32_t v___x_42_; 
v___x_42_ = lean_uint32_lor(v___y_2_, v___x_38_);
return v___x_42_;
}
}
}
v___jp_43_:
{
uint32_t v___x_44_; uint32_t v___x_45_; uint32_t v___x_46_; uint32_t v___x_47_; uint8_t v___x_48_; 
v___x_44_ = 23;
v___x_45_ = lean_uint32_shift_right(v___y_2_, v___x_44_);
v___x_46_ = 255;
v___x_47_ = lean_uint32_land(v___x_45_, v___x_46_);
v___x_48_ = lean_uint32_dec_eq(v___x_47_, v___x_46_);
if (v___x_48_ == 0)
{
v___y_37_ = v___x_48_;
goto v___jp_36_;
}
else
{
uint32_t v___x_49_; uint32_t v___x_50_; uint32_t v___x_51_; uint8_t v___x_52_; 
v___x_49_ = 8388607;
v___x_50_ = lean_uint32_land(v___y_2_, v___x_49_);
v___x_51_ = 0;
v___x_52_ = lean_uint32_dec_eq(v___x_50_, v___x_51_);
if (v___x_52_ == 0)
{
v___y_37_ = v___x_48_;
goto v___jp_36_;
}
else
{
goto v___jp_26_;
}
}
}
v___jp_53_:
{
if (v___y_54_ == 0)
{
goto v___jp_43_;
}
else
{
uint32_t v___x_55_; uint32_t v___x_56_; uint32_t v___x_57_; uint8_t v___x_58_; 
v___x_55_ = 4194304;
v___x_56_ = lean_uint32_land(v___y_1_, v___x_55_);
v___x_57_ = 0;
v___x_58_ = lean_uint32_dec_eq(v___x_56_, v___x_57_);
if (v___x_58_ == 0)
{
goto v___jp_43_;
}
else
{
uint32_t v___x_59_; 
v___x_59_ = lean_uint32_lor(v___y_1_, v___x_55_);
return v___x_59_;
}
}
}
v___jp_60_:
{
uint8_t v___x_62_; 
v___x_62_ = lean_float32_beq(v___y_61_, v___y_61_);
if (v___x_62_ == 0)
{
uint32_t v___x_63_; uint32_t v___x_64_; uint32_t v___x_65_; uint32_t v___x_66_; uint8_t v___x_67_; 
v___x_63_ = 23;
v___x_64_ = lean_uint32_shift_right(v___y_1_, v___x_63_);
v___x_65_ = 255;
v___x_66_ = lean_uint32_land(v___x_64_, v___x_65_);
v___x_67_ = lean_uint32_dec_eq(v___x_66_, v___x_65_);
if (v___x_67_ == 0)
{
v___y_54_ = v___x_67_;
goto v___jp_53_;
}
else
{
uint32_t v___x_68_; uint32_t v___x_69_; uint32_t v___x_70_; uint8_t v___x_71_; 
v___x_68_ = 8388607;
v___x_69_ = lean_uint32_land(v___y_1_, v___x_68_);
v___x_70_ = 0;
v___x_71_ = lean_uint32_dec_eq(v___x_69_, v___x_70_);
if (v___x_71_ == 0)
{
v___y_54_ = v___x_67_;
goto v___jp_53_;
}
else
{
goto v___jp_43_;
}
}
}
else
{
uint32_t v___x_72_; 
v___x_72_ = lean_float32_to_bits(v___y_61_);
return v___x_72_;
}
}
v___jp_73_:
{
if (v___y_75_ == 0)
{
float v___x_76_; float v___x_77_; 
v___x_76_ = lean_float32_of_bits(v___y_2_);
v___x_77_ = lean_float32_add(v___y_74_, v___x_76_);
v___y_61_ = v___x_77_;
goto v___jp_60_;
}
else
{
uint32_t v___x_78_; uint32_t v___x_79_; uint32_t v___x_80_; uint32_t v___x_81_; float v___x_82_; lean_object* v___x_83_; uint32_t v___x_84_; uint32_t v___x_85_; lean_object* v___x_86_; lean_object* v___x_87_; float v___x_88_; float v___x_89_; float v___x_90_; 
v___x_78_ = 8388607;
v___x_79_ = lean_uint32_land(v___y_2_, v___x_78_);
v___x_80_ = 8388608;
v___x_81_ = lean_uint32_lor(v___x_79_, v___x_80_);
v___x_82_ = lean_uint32_to_float32(v___x_81_);
v___x_83_ = lp_competition_R2W01b_scaleTable;
v___x_84_ = 23;
v___x_85_ = lean_uint32_shift_right(v___y_2_, v___x_84_);
v___x_86_ = lean_uint32_to_nat(v___x_85_);
v___x_87_ = lean_array_fget_borrowed(v___x_83_, v___x_86_);
lean_dec(v___x_86_);
v___x_88_ = lean_unbox_float32(v___x_87_);
v___x_89_ = lean_float32_mul(v___x_82_, v___x_88_);
v___x_90_ = lean_float32_add(v___y_74_, v___x_89_);
v___y_61_ = v___x_90_;
goto v___jp_60_;
}
}
v___jp_91_:
{
uint32_t v___x_93_; uint32_t v_a_94_; uint32_t v___x_95_; uint32_t v___x_96_; uint32_t v___x_97_; uint8_t v___x_98_; 
v___x_93_ = 2147483647;
v_a_94_ = lean_uint32_land(v___y_2_, v___x_93_);
v___x_95_ = 201326591;
v___x_96_ = 1;
v___x_97_ = lean_uint32_sub(v_a_94_, v___x_96_);
v___x_98_ = lean_uint32_dec_le(v___x_95_, v___x_97_);
if (v___x_98_ == 0)
{
v___y_74_ = v___y_92_;
v___y_75_ = v___x_98_;
goto v___jp_73_;
}
else
{
uint32_t v___x_99_; uint8_t v___x_100_; 
v___x_99_ = 2139095040;
v___x_100_ = lean_uint32_dec_lt(v_a_94_, v___x_99_);
v___y_74_ = v___y_92_;
v___y_75_ = v___x_100_;
goto v___jp_73_;
}
}
v___jp_101_:
{
if (v___y_102_ == 0)
{
float v___x_103_; 
v___x_103_ = lean_float32_of_bits(v___y_1_);
v___y_92_ = v___x_103_;
goto v___jp_91_;
}
else
{
uint32_t v___x_104_; uint32_t v___x_105_; uint32_t v___x_106_; uint32_t v___x_107_; float v___x_108_; lean_object* v___x_109_; uint32_t v___x_110_; uint32_t v___x_111_; lean_object* v___x_112_; lean_object* v___x_113_; float v___x_114_; float v___x_115_; 
v___x_104_ = 8388607;
v___x_105_ = lean_uint32_land(v___y_1_, v___x_104_);
v___x_106_ = 8388608;
v___x_107_ = lean_uint32_lor(v___x_105_, v___x_106_);
v___x_108_ = lean_uint32_to_float32(v___x_107_);
v___x_109_ = lp_competition_R2W01b_scaleTable;
v___x_110_ = 23;
v___x_111_ = lean_uint32_shift_right(v___y_1_, v___x_110_);
v___x_112_ = lean_uint32_to_nat(v___x_111_);
v___x_113_ = lean_array_fget_borrowed(v___x_109_, v___x_112_);
lean_dec(v___x_112_);
v___x_114_ = lean_unbox_float32(v___x_113_);
v___x_115_ = lean_float32_mul(v___x_108_, v___x_114_);
v___y_92_ = v___x_115_;
goto v___jp_91_;
}
}
v___jp_116_:
{
if (v___y_118_ == 0)
{
float v___x_119_; float v___x_120_; 
v___x_119_ = lean_float32_of_bits(v___y_2_);
v___x_120_ = lean_float32_add(v___y_117_, v___x_119_);
v___y_61_ = v___x_120_;
goto v___jp_60_;
}
else
{
uint32_t v___x_121_; uint32_t v___x_122_; uint32_t v___x_123_; uint32_t v___x_124_; float v___x_125_; lean_object* v___x_126_; uint32_t v___x_127_; uint32_t v___x_128_; lean_object* v___x_129_; double v___x_130_; float v___x_131_; float v___x_132_; float v___x_133_; 
v___x_121_ = 8388607;
v___x_122_ = lean_uint32_land(v___y_2_, v___x_121_);
v___x_123_ = 8388608;
v___x_124_ = lean_uint32_lor(v___x_122_, v___x_123_);
v___x_125_ = lean_uint32_to_float32(v___x_124_);
v___x_126_ = lp_competition_R19CompactScales_packed;
v___x_127_ = 23;
v___x_128_ = lean_uint32_shift_right(v___y_2_, v___x_127_);
v___x_129_ = lean_uint32_to_nat(v___x_128_);
v___x_130_ = lean_float_array_fget(v___x_126_, v___x_129_);
lean_dec(v___x_129_);
v___x_131_ = lean_float_to_float32(v___x_130_);
v___x_132_ = lean_float32_mul(v___x_125_, v___x_131_);
v___x_133_ = lean_float32_add(v___y_117_, v___x_132_);
v___y_61_ = v___x_133_;
goto v___jp_60_;
}
}
v___jp_134_:
{
uint32_t v___x_136_; uint32_t v_a_137_; uint32_t v___x_138_; uint32_t v___x_139_; uint32_t v___x_140_; uint8_t v___x_141_; 
v___x_136_ = 2147483647;
v_a_137_ = lean_uint32_land(v___y_2_, v___x_136_);
v___x_138_ = 201326591;
v___x_139_ = 1;
v___x_140_ = lean_uint32_sub(v_a_137_, v___x_139_);
v___x_141_ = lean_uint32_dec_le(v___x_138_, v___x_140_);
if (v___x_141_ == 0)
{
v___y_117_ = v___y_135_;
v___y_118_ = v___x_141_;
goto v___jp_116_;
}
else
{
uint32_t v___x_142_; uint8_t v___x_143_; 
v___x_142_ = 2139095040;
v___x_143_ = lean_uint32_dec_lt(v_a_137_, v___x_142_);
v___y_117_ = v___y_135_;
v___y_118_ = v___x_143_;
goto v___jp_116_;
}
}
v___jp_144_:
{
if (v___y_145_ == 0)
{
float v___x_146_; 
v___x_146_ = lean_float32_of_bits(v___y_1_);
v___y_135_ = v___x_146_;
goto v___jp_134_;
}
else
{
uint32_t v___x_147_; uint32_t v___x_148_; uint32_t v___x_149_; uint32_t v___x_150_; float v___x_151_; lean_object* v___x_152_; uint32_t v___x_153_; uint32_t v___x_154_; lean_object* v___x_155_; double v___x_156_; float v___x_157_; float v___x_158_; 
v___x_147_ = 8388607;
v___x_148_ = lean_uint32_land(v___y_1_, v___x_147_);
v___x_149_ = 8388608;
v___x_150_ = lean_uint32_lor(v___x_148_, v___x_149_);
v___x_151_ = lean_uint32_to_float32(v___x_150_);
v___x_152_ = lp_competition_R19CompactScales_packed;
v___x_153_ = 23;
v___x_154_ = lean_uint32_shift_right(v___y_1_, v___x_153_);
v___x_155_ = lean_uint32_to_nat(v___x_154_);
v___x_156_ = lean_float_array_fget(v___x_152_, v___x_155_);
lean_dec(v___x_155_);
v___x_157_ = lean_float_to_float32(v___x_156_);
v___x_158_ = lean_float32_mul(v___x_151_, v___x_157_);
v___y_135_ = v___x_158_;
goto v___jp_134_;
}
}
}
}
