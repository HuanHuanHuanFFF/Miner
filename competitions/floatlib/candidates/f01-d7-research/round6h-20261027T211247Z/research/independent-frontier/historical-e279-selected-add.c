LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
float v___y_4_; float v___y_5_; float v___y_11_; uint8_t v___y_12_; float v___y_27_; uint8_t v___y_37_; uint32_t v___x_51_; uint32_t v___x_52_; uint32_t v___x_53_; uint32_t v___x_54_; uint32_t v___x_55_; uint32_t v___x_56_; uint32_t v___x_57_; uint32_t v___x_58_; uint8_t v___x_59_; 
v___x_51_ = 2147483647;
v___x_52_ = lean_uint32_land(v___y_1_, v___x_51_);
v___x_53_ = 536870912;
v___x_54_ = lean_uint32_sub(v___x_52_, v___x_53_);
v___x_55_ = lean_uint32_land(v___y_2_, v___x_51_);
v___x_56_ = lean_uint32_sub(v___x_55_, v___x_53_);
v___x_57_ = lean_uint32_lor(v___x_54_, v___x_56_);
v___x_58_ = 1073741824;
v___x_59_ = lean_uint32_dec_lt(v___x_57_, v___x_58_);
if (v___x_59_ == 0)
{
uint32_t v___x_60_; uint32_t v___x_61_; uint32_t v___x_62_; uint8_t v___x_63_; 
v___x_60_ = 201326591;
v___x_61_ = 1;
v___x_62_ = lean_uint32_sub(v___x_52_, v___x_61_);
v___x_63_ = lean_uint32_dec_le(v___x_60_, v___x_62_);
if (v___x_63_ == 0)
{
v___y_37_ = v___x_63_;
goto v___jp_36_;
}
else
{
uint32_t v___x_64_; uint8_t v___x_65_; 
v___x_64_ = 2139095040;
v___x_65_ = lean_uint32_dec_lt(v___x_52_, v___x_64_);
v___y_37_ = v___x_65_;
goto v___jp_36_;
}
}
else
{
uint32_t v___x_66_; uint32_t v___x_67_; uint32_t v___x_68_; uint32_t v___x_69_; float v___x_70_; lean_object* v___x_71_; uint32_t v___x_72_; uint32_t v___x_73_; lean_object* v___x_74_; lean_object* v___x_75_; float v___x_76_; float v___x_77_; uint32_t v___x_78_; uint32_t v___x_79_; float v___x_80_; uint32_t v___x_81_; lean_object* v___x_82_; lean_object* v___x_83_; float v___x_84_; float v___x_85_; float v___x_86_; uint32_t v___x_87_; 
v___x_66_ = 8388607;
v___x_67_ = lean_uint32_land(v___y_1_, v___x_66_);
v___x_68_ = 8388608;
v___x_69_ = lean_uint32_lor(v___x_67_, v___x_68_);
v___x_70_ = lean_uint32_to_float32(v___x_69_);
v___x_71_ = lp_competition_R2W01b_scaleTable;
v___x_72_ = 23;
v___x_73_ = lean_uint32_shift_right(v___y_1_, v___x_72_);
v___x_74_ = lean_uint32_to_nat(v___x_73_);
v___x_75_ = lean_array_fget_borrowed(v___x_71_, v___x_74_);
lean_dec(v___x_74_);
v___x_76_ = lean_unbox_float32(v___x_75_);
v___x_77_ = lean_float32_mul(v___x_70_, v___x_76_);
v___x_78_ = lean_uint32_land(v___y_2_, v___x_66_);
v___x_79_ = lean_uint32_lor(v___x_78_, v___x_68_);
v___x_80_ = lean_uint32_to_float32(v___x_79_);
v___x_81_ = lean_uint32_shift_right(v___y_2_, v___x_72_);
v___x_82_ = lean_uint32_to_nat(v___x_81_);
v___x_83_ = lean_array_fget_borrowed(v___x_71_, v___x_82_);
lean_dec(v___x_82_);
v___x_84_ = lean_unbox_float32(v___x_83_);
v___x_85_ = lean_float32_mul(v___x_80_, v___x_84_);
v___x_86_ = lean_float32_add(v___x_77_, v___x_85_);
v___x_87_ = lean_float32_to_bits(v___x_86_);
return v___x_87_;
}
v___jp_3_:
{
float v_result_6_; uint8_t v___x_7_; 
v_result_6_ = lean_float32_add(v___y_4_, v___y_5_);
v___x_7_ = lean_float32_beq(v_result_6_, v_result_6_);
if (v___x_7_ == 0)
{
uint32_t v___x_8_; 
v___x_8_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_8_;
}
else
{
uint32_t v___x_9_; 
v___x_9_ = lean_float32_to_bits(v_result_6_);
return v___x_9_;
}
}
v___jp_10_:
{
if (v___y_12_ == 0)
{
float v___x_13_; 
v___x_13_ = lean_float32_of_bits(v___y_2_);
v___y_4_ = v___y_11_;
v___y_5_ = v___x_13_;
goto v___jp_3_;
}
else
{
uint32_t v___x_14_; uint32_t v___x_15_; uint32_t v___x_16_; uint32_t v___x_17_; float v___x_18_; lean_object* v___x_19_; uint32_t v___x_20_; uint32_t v___x_21_; lean_object* v___x_22_; lean_object* v___x_23_; float v___x_24_; float v___x_25_; 
v___x_14_ = 8388607;
v___x_15_ = lean_uint32_land(v___y_2_, v___x_14_);
v___x_16_ = 8388608;
v___x_17_ = lean_uint32_lor(v___x_15_, v___x_16_);
v___x_18_ = lean_uint32_to_float32(v___x_17_);
v___x_19_ = lp_competition_R2W01b_scaleTable;
v___x_20_ = 23;
v___x_21_ = lean_uint32_shift_right(v___y_2_, v___x_20_);
v___x_22_ = lean_uint32_to_nat(v___x_21_);
v___x_23_ = lean_array_fget_borrowed(v___x_19_, v___x_22_);
lean_dec(v___x_22_);
v___x_24_ = lean_unbox_float32(v___x_23_);
v___x_25_ = lean_float32_mul(v___x_18_, v___x_24_);
v___y_4_ = v___y_11_;
v___y_5_ = v___x_25_;
goto v___jp_3_;
}
}
v___jp_26_:
{
uint32_t v___x_28_; uint32_t v_a_29_; uint32_t v___x_30_; uint32_t v___x_31_; uint32_t v___x_32_; uint8_t v___x_33_; 
v___x_28_ = 2147483647;
v_a_29_ = lean_uint32_land(v___y_2_, v___x_28_);
v___x_30_ = 201326591;
v___x_31_ = 1;
v___x_32_ = lean_uint32_sub(v_a_29_, v___x_31_);
v___x_33_ = lean_uint32_dec_le(v___x_30_, v___x_32_);
if (v___x_33_ == 0)
{
v___y_11_ = v___y_27_;
v___y_12_ = v___x_33_;
goto v___jp_10_;
}
else
{
uint32_t v___x_34_; uint8_t v___x_35_; 
v___x_34_ = 2139095040;
v___x_35_ = lean_uint32_dec_lt(v_a_29_, v___x_34_);
v___y_11_ = v___y_27_;
v___y_12_ = v___x_35_;
goto v___jp_10_;
}
}
v___jp_36_:
{
if (v___y_37_ == 0)
{
float v___x_38_; 
v___x_38_ = lean_float32_of_bits(v___y_1_);
v___y_27_ = v___x_38_;
goto v___jp_26_;
}
else
{
uint32_t v___x_39_; uint32_t v___x_40_; uint32_t v___x_41_; uint32_t v___x_42_; float v___x_43_; lean_object* v___x_44_; uint32_t v___x_45_; uint32_t v___x_46_; lean_object* v___x_47_; lean_object* v___x_48_; float v___x_49_; float v___x_50_; 
v___x_39_ = 8388607;
v___x_40_ = lean_uint32_land(v___y_1_, v___x_39_);
v___x_41_ = 8388608;
v___x_42_ = lean_uint32_lor(v___x_40_, v___x_41_);
v___x_43_ = lean_uint32_to_float32(v___x_42_);
v___x_44_ = lp_competition_R2W01b_scaleTable;
v___x_45_ = 23;
v___x_46_ = lean_uint32_shift_right(v___y_1_, v___x_45_);
v___x_47_ = lean_uint32_to_nat(v___x_46_);
v___x_48_ = lean_array_fget_borrowed(v___x_44_, v___x_47_);
lean_dec(v___x_47_);
v___x_49_ = lean_unbox_float32(v___x_48_);
v___x_50_ = lean_float32_mul(v___x_43_, v___x_49_);
v___y_27_ = v___x_50_;
goto v___jp_26_;
}
}
}
}
