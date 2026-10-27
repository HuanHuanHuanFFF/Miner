// Lean compiler output
// Module: R19AddCostMain
// Imports: public import Init public meta import Init public import BenchFull public import BenchSuite public import Submission
#include <lean/lean.h>
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-label"
#elif defined(__GNUC__) && !defined(__CLANG__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
#ifdef __cplusplus
extern "C" {
#endif
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
float lean_float32_mul(float, float);
uint8_t lean_float32_beq(float, float);
uint32_t lean_float32_to_bits(float);
float lean_float32_of_bits(uint32_t);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint64_t lean_uint64_sub(uint64_t, uint64_t);
uint8_t lean_uint64_dec_lt(uint64_t, uint64_t);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint64_t lean_uint64_shift_left(uint64_t, uint64_t);
uint64_t lean_uint64_land(uint64_t, uint64_t);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
uint64_t lean_uint32_to_uint64(uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
float lean_float32_add(float, float);
uint32_t lean_uint32_xor(uint32_t, uint32_t);
lean_object* lean_io_getenv(lean_object*);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_r19CostControlAdd(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_r19CostControlAdd___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_r19CostGuardedAdd(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_r19CostGuardedAdd___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_closure_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_closure_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_closure_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_string_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_ctor_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__4_value)}};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_string_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "guarded"};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_ctor_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__6_value)}};
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_string_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 41, .m_capacity = 41, .m_length = 40, .m_data = "BENCH_VARIANT must be control or guarded"};
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_ctor_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__8_value)}};
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
static const lean_closure_object lp_competition_main___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_r19CostGuardedAdd___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__10 = (const lean_object*)&lp_competition_main___closed__10_value;
static const lean_closure_object lp_competition_main___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_r19CostControlAdd___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__11 = (const lean_object*)&lp_competition_main___closed__11_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_r19CostControlAdd(uint32_t v_x_1_, uint32_t v_y_2_){
_start:
{
uint8_t v___y_9_; uint8_t v___y_23_; uint8_t v___y_37_; uint8_t v___y_54_; float v___y_61_; float v___y_62_; float v___y_76_; uint8_t v___y_77_; float v___y_92_; uint8_t v___y_102_; uint32_t v___x_116_; uint32_t v_a_117_; uint32_t v___x_118_; uint32_t v___x_119_; uint32_t v___x_120_; uint8_t v___x_121_; 
v___x_116_ = 2147483647;
v_a_117_ = lean_uint32_land(v_x_1_, v___x_116_);
v___x_118_ = 201326591;
v___x_119_ = 1;
v___x_120_ = lean_uint32_sub(v_a_117_, v___x_119_);
v___x_121_ = lean_uint32_dec_le(v___x_118_, v___x_120_);
if (v___x_121_ == 0)
{
v___y_102_ = v___x_121_;
goto v___jp_101_;
}
else
{
uint32_t v___x_122_; uint8_t v___x_123_; 
v___x_122_ = 2139095040;
v___x_123_ = lean_uint32_dec_lt(v_a_117_, v___x_122_);
v___y_102_ = v___x_123_;
goto v___jp_101_;
}
v___jp_3_:
{
lean_object* v___x_4_; lean_object* v___x_5_; lean_object* v___x_6_; uint32_t v___x_7_; 
v___x_4_ = lean_uint32_to_nat(v_x_1_);
v___x_5_ = lean_uint32_to_nat(v_y_2_);
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
v___x_11_ = lean_uint32_lor(v_y_2_, v___x_10_);
return v___x_11_;
}
}
v___jp_12_:
{
uint32_t v___x_13_; uint32_t v___x_14_; uint32_t v___x_15_; uint32_t v___x_16_; uint8_t v___x_17_; 
v___x_13_ = 23;
v___x_14_ = lean_uint32_shift_right(v_y_2_, v___x_13_);
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
v___x_19_ = lean_uint32_land(v_y_2_, v___x_18_);
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
v___x_25_ = lean_uint32_lor(v_x_1_, v___x_24_);
return v___x_25_;
}
}
v___jp_26_:
{
uint32_t v___x_27_; uint32_t v___x_28_; uint32_t v___x_29_; uint32_t v___x_30_; uint8_t v___x_31_; 
v___x_27_ = 23;
v___x_28_ = lean_uint32_shift_right(v_x_1_, v___x_27_);
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
v___x_33_ = lean_uint32_land(v_x_1_, v___x_32_);
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
v___x_39_ = lean_uint32_land(v_y_2_, v___x_38_);
v___x_40_ = 0;
v___x_41_ = lean_uint32_dec_eq(v___x_39_, v___x_40_);
if (v___x_41_ == 0)
{
goto v___jp_26_;
}
else
{
uint32_t v___x_42_; 
v___x_42_ = lean_uint32_lor(v_y_2_, v___x_38_);
return v___x_42_;
}
}
}
v___jp_43_:
{
uint32_t v___x_44_; uint32_t v___x_45_; uint32_t v___x_46_; uint32_t v___x_47_; uint8_t v___x_48_; 
v___x_44_ = 23;
v___x_45_ = lean_uint32_shift_right(v_y_2_, v___x_44_);
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
v___x_50_ = lean_uint32_land(v_y_2_, v___x_49_);
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
v___x_56_ = lean_uint32_land(v_x_1_, v___x_55_);
v___x_57_ = 0;
v___x_58_ = lean_uint32_dec_eq(v___x_56_, v___x_57_);
if (v___x_58_ == 0)
{
goto v___jp_43_;
}
else
{
uint32_t v___x_59_; 
v___x_59_ = lean_uint32_lor(v_x_1_, v___x_55_);
return v___x_59_;
}
}
}
v___jp_60_:
{
float v_result_63_; uint8_t v___x_64_; 
v_result_63_ = lean_float32_add(v___y_61_, v___y_62_);
v___x_64_ = lean_float32_beq(v_result_63_, v_result_63_);
if (v___x_64_ == 0)
{
uint32_t v___x_65_; uint32_t v___x_66_; uint32_t v___x_67_; uint32_t v___x_68_; uint8_t v___x_69_; 
v___x_65_ = 23;
v___x_66_ = lean_uint32_shift_right(v_x_1_, v___x_65_);
v___x_67_ = 255;
v___x_68_ = lean_uint32_land(v___x_66_, v___x_67_);
v___x_69_ = lean_uint32_dec_eq(v___x_68_, v___x_67_);
if (v___x_69_ == 0)
{
v___y_54_ = v___x_69_;
goto v___jp_53_;
}
else
{
uint32_t v___x_70_; uint32_t v___x_71_; uint32_t v___x_72_; uint8_t v___x_73_; 
v___x_70_ = 8388607;
v___x_71_ = lean_uint32_land(v_x_1_, v___x_70_);
v___x_72_ = 0;
v___x_73_ = lean_uint32_dec_eq(v___x_71_, v___x_72_);
if (v___x_73_ == 0)
{
v___y_54_ = v___x_69_;
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
uint32_t v___x_74_; 
v___x_74_ = lean_float32_to_bits(v_result_63_);
return v___x_74_;
}
}
v___jp_75_:
{
if (v___y_77_ == 0)
{
float v___x_78_; 
v___x_78_ = lean_float32_of_bits(v_y_2_);
v___y_61_ = v___y_76_;
v___y_62_ = v___x_78_;
goto v___jp_60_;
}
else
{
uint32_t v___x_79_; uint32_t v___x_80_; uint32_t v___x_81_; uint32_t v___x_82_; float v___x_83_; lean_object* v___x_84_; uint32_t v___x_85_; uint32_t v___x_86_; lean_object* v___x_87_; lean_object* v___x_88_; float v___x_89_; float v___x_90_; 
v___x_79_ = 8388607;
v___x_80_ = lean_uint32_land(v_y_2_, v___x_79_);
v___x_81_ = 8388608;
v___x_82_ = lean_uint32_lor(v___x_80_, v___x_81_);
v___x_83_ = lean_uint32_to_float32(v___x_82_);
v___x_84_ = lp_competition_R2W01b_scaleTable;
v___x_85_ = 23;
v___x_86_ = lean_uint32_shift_right(v_y_2_, v___x_85_);
v___x_87_ = lean_uint32_to_nat(v___x_86_);
v___x_88_ = lean_array_fget_borrowed(v___x_84_, v___x_87_);
lean_dec(v___x_87_);
v___x_89_ = lean_unbox_float32(v___x_88_);
v___x_90_ = lean_float32_mul(v___x_83_, v___x_89_);
v___y_61_ = v___y_76_;
v___y_62_ = v___x_90_;
goto v___jp_60_;
}
}
v___jp_91_:
{
uint32_t v___x_93_; uint32_t v_a_94_; uint32_t v___x_95_; uint32_t v___x_96_; uint32_t v___x_97_; uint8_t v___x_98_; 
v___x_93_ = 2147483647;
v_a_94_ = lean_uint32_land(v_y_2_, v___x_93_);
v___x_95_ = 201326591;
v___x_96_ = 1;
v___x_97_ = lean_uint32_sub(v_a_94_, v___x_96_);
v___x_98_ = lean_uint32_dec_le(v___x_95_, v___x_97_);
if (v___x_98_ == 0)
{
v___y_76_ = v___y_92_;
v___y_77_ = v___x_98_;
goto v___jp_75_;
}
else
{
uint32_t v___x_99_; uint8_t v___x_100_; 
v___x_99_ = 2139095040;
v___x_100_ = lean_uint32_dec_lt(v_a_94_, v___x_99_);
v___y_76_ = v___y_92_;
v___y_77_ = v___x_100_;
goto v___jp_75_;
}
}
v___jp_101_:
{
if (v___y_102_ == 0)
{
float v___x_103_; 
v___x_103_ = lean_float32_of_bits(v_x_1_);
v___y_92_ = v___x_103_;
goto v___jp_91_;
}
else
{
uint32_t v___x_104_; uint32_t v___x_105_; uint32_t v___x_106_; uint32_t v___x_107_; float v___x_108_; lean_object* v___x_109_; uint32_t v___x_110_; uint32_t v___x_111_; lean_object* v___x_112_; lean_object* v___x_113_; float v___x_114_; float v___x_115_; 
v___x_104_ = 8388607;
v___x_105_ = lean_uint32_land(v_x_1_, v___x_104_);
v___x_106_ = 8388608;
v___x_107_ = lean_uint32_lor(v___x_105_, v___x_106_);
v___x_108_ = lean_uint32_to_float32(v___x_107_);
v___x_109_ = lp_competition_R2W01b_scaleTable;
v___x_110_ = 23;
v___x_111_ = lean_uint32_shift_right(v_x_1_, v___x_110_);
v___x_112_ = lean_uint32_to_nat(v___x_111_);
v___x_113_ = lean_array_fget_borrowed(v___x_109_, v___x_112_);
lean_dec(v___x_112_);
v___x_114_ = lean_unbox_float32(v___x_113_);
v___x_115_ = lean_float32_mul(v___x_108_, v___x_114_);
v___y_92_ = v___x_115_;
goto v___jp_91_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_r19CostControlAdd___boxed(lean_object* v_x_124_, lean_object* v_y_125_){
_start:
{
uint32_t v_x_boxed_126_; uint32_t v_y_boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v_x_boxed_126_ = lean_unbox_uint32(v_x_124_);
lean_dec(v_x_124_);
v_y_boxed_127_ = lean_unbox_uint32(v_y_125_);
lean_dec(v_y_125_);
v_res_128_ = lp_competition_r19CostControlAdd(v_x_boxed_126_, v_y_boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_r19CostGuardedAdd(uint32_t v_x_130_, uint32_t v_y_131_){
_start:
{
uint8_t v___y_138_; uint8_t v___y_152_; uint8_t v___y_166_; uint8_t v___y_183_; float v___y_190_; float v___y_191_; float v___y_205_; uint8_t v___y_206_; float v___y_221_; uint8_t v___y_236_; uint8_t v___y_250_; uint8_t v___y_264_; uint8_t v___y_281_; float v___y_288_; float v___y_289_; float v___y_303_; uint8_t v___y_304_; float v___y_319_; uint8_t v___y_334_; uint8_t v___y_348_; uint8_t v___y_362_; uint8_t v___y_379_; float v___y_386_; float v___y_387_; float v___y_401_; uint8_t v___y_402_; float v___y_417_; uint32_t v___x_426_; uint32_t v___x_427_; uint8_t v___y_429_; uint8_t v___y_442_; uint32_t v___y_455_; uint32_t v___y_456_; uint8_t v___y_457_; uint32_t v___x_467_; uint32_t v_eu_468_; uint32_t v___x_469_; uint32_t v___y_471_; uint32_t v___y_472_; uint32_t v___y_473_; uint32_t v___y_474_; uint32_t v___y_475_; uint32_t v___y_476_; uint32_t v___y_477_; uint32_t v___y_499_; uint32_t v___y_500_; uint32_t v___y_501_; uint32_t v___y_502_; uint32_t v___y_503_; uint32_t v___y_504_; uint32_t v___y_513_; uint32_t v___y_514_; uint32_t v___y_515_; uint32_t v___y_516_; uint32_t v___x_536_; uint32_t v___x_537_; uint8_t v___x_538_; 
v___x_426_ = 23;
v___x_427_ = lean_uint32_shift_right(v_x_130_, v___x_426_);
v___x_467_ = 255;
v_eu_468_ = lean_uint32_land(v___x_427_, v___x_467_);
v___x_469_ = 1;
v___x_536_ = lean_uint32_sub(v_eu_468_, v___x_469_);
v___x_537_ = 253;
v___x_538_ = lean_uint32_dec_le(v___x_536_, v___x_537_);
if (v___x_538_ == 0)
{
uint32_t v___x_539_; uint32_t v_a_540_; uint32_t v___x_541_; uint32_t v___x_542_; uint8_t v___x_543_; 
v___x_539_ = 2147483647;
v_a_540_ = lean_uint32_land(v_x_130_, v___x_539_);
v___x_541_ = 201326591;
v___x_542_ = lean_uint32_sub(v_a_540_, v___x_469_);
v___x_543_ = lean_uint32_dec_le(v___x_541_, v___x_542_);
if (v___x_543_ == 0)
{
v___y_429_ = v___x_543_;
goto v___jp_428_;
}
else
{
uint32_t v___x_544_; uint8_t v___x_545_; 
v___x_544_ = 2139095040;
v___x_545_ = lean_uint32_dec_lt(v_a_540_, v___x_544_);
v___y_429_ = v___x_545_;
goto v___jp_428_;
}
}
else
{
uint32_t v___x_546_; uint32_t v_ev_547_; uint32_t v___x_548_; uint8_t v___x_549_; 
v___x_546_ = lean_uint32_shift_right(v_y_131_, v___x_426_);
v_ev_547_ = lean_uint32_land(v___x_546_, v___x_467_);
v___x_548_ = lean_uint32_sub(v_ev_547_, v___x_469_);
v___x_549_ = lean_uint32_dec_le(v___x_548_, v___x_537_);
if (v___x_549_ == 0)
{
uint32_t v___x_550_; uint32_t v_a_551_; uint32_t v___x_552_; uint32_t v___x_553_; uint8_t v___x_554_; 
v___x_550_ = 2147483647;
v_a_551_ = lean_uint32_land(v_x_130_, v___x_550_);
v___x_552_ = 201326591;
v___x_553_ = lean_uint32_sub(v_a_551_, v___x_469_);
v___x_554_ = lean_uint32_dec_le(v___x_552_, v___x_553_);
if (v___x_554_ == 0)
{
v___y_442_ = v___x_554_;
goto v___jp_441_;
}
else
{
uint32_t v___x_555_; uint8_t v___x_556_; 
v___x_555_ = 2139095040;
v___x_556_ = lean_uint32_dec_lt(v_a_551_, v___x_555_);
v___y_442_ = v___x_556_;
goto v___jp_441_;
}
}
else
{
uint32_t v___x_557_; uint32_t v___x_558_; uint32_t v___x_559_; uint8_t v_swap_560_; uint32_t v___y_562_; uint32_t v___y_563_; uint32_t v___y_564_; uint32_t v___y_566_; uint32_t v___y_567_; uint32_t v___y_569_; 
v___x_557_ = 2147483647;
v___x_558_ = lean_uint32_land(v_x_130_, v___x_557_);
v___x_559_ = lean_uint32_land(v_y_131_, v___x_557_);
v_swap_560_ = lean_uint32_dec_lt(v___x_558_, v___x_559_);
if (v_swap_560_ == 0)
{
v___y_569_ = v_x_130_;
goto v___jp_568_;
}
else
{
v___y_569_ = v_y_131_;
goto v___jp_568_;
}
v___jp_561_:
{
if (v_swap_560_ == 0)
{
v___y_513_ = v___y_564_;
v___y_514_ = v___y_562_;
v___y_515_ = v___y_563_;
v___y_516_ = v_ev_547_;
goto v___jp_512_;
}
else
{
v___y_513_ = v___y_564_;
v___y_514_ = v___y_562_;
v___y_515_ = v___y_563_;
v___y_516_ = v_eu_468_;
goto v___jp_512_;
}
}
v___jp_565_:
{
if (v_swap_560_ == 0)
{
v___y_562_ = v___y_567_;
v___y_563_ = v___y_566_;
v___y_564_ = v_eu_468_;
goto v___jp_561_;
}
else
{
v___y_562_ = v___y_567_;
v___y_563_ = v___y_566_;
v___y_564_ = v_ev_547_;
goto v___jp_561_;
}
}
v___jp_568_:
{
if (v_swap_560_ == 0)
{
v___y_566_ = v___y_569_;
v___y_567_ = v_y_131_;
goto v___jp_565_;
}
else
{
v___y_566_ = v___y_569_;
v___y_567_ = v_x_130_;
goto v___jp_565_;
}
}
}
}
v___jp_132_:
{
lean_object* v___x_133_; lean_object* v___x_134_; lean_object* v___x_135_; uint32_t v___x_136_; 
v___x_133_ = lean_uint32_to_nat(v_x_130_);
v___x_134_ = lean_uint32_to_nat(v_y_131_);
v___x_135_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_133_, v___x_134_);
v___x_136_ = lean_uint32_of_nat(v___x_135_);
lean_dec(v___x_135_);
return v___x_136_;
}
v___jp_137_:
{
if (v___y_138_ == 0)
{
goto v___jp_132_;
}
else
{
uint32_t v___x_139_; uint32_t v___x_140_; 
v___x_139_ = 4194304;
v___x_140_ = lean_uint32_lor(v_y_131_, v___x_139_);
return v___x_140_;
}
}
v___jp_141_:
{
uint32_t v___x_142_; uint32_t v___x_143_; uint32_t v___x_144_; uint32_t v___x_145_; uint8_t v___x_146_; 
v___x_142_ = 23;
v___x_143_ = lean_uint32_shift_right(v_y_131_, v___x_142_);
v___x_144_ = 255;
v___x_145_ = lean_uint32_land(v___x_143_, v___x_144_);
v___x_146_ = lean_uint32_dec_eq(v___x_145_, v___x_144_);
if (v___x_146_ == 0)
{
v___y_138_ = v___x_146_;
goto v___jp_137_;
}
else
{
uint32_t v___x_147_; uint32_t v___x_148_; uint32_t v___x_149_; uint8_t v___x_150_; 
v___x_147_ = 8388607;
v___x_148_ = lean_uint32_land(v_y_131_, v___x_147_);
v___x_149_ = 0;
v___x_150_ = lean_uint32_dec_eq(v___x_148_, v___x_149_);
if (v___x_150_ == 0)
{
v___y_138_ = v___x_146_;
goto v___jp_137_;
}
else
{
goto v___jp_132_;
}
}
}
v___jp_151_:
{
if (v___y_152_ == 0)
{
goto v___jp_141_;
}
else
{
uint32_t v___x_153_; uint32_t v___x_154_; 
v___x_153_ = 4194304;
v___x_154_ = lean_uint32_lor(v_x_130_, v___x_153_);
return v___x_154_;
}
}
v___jp_155_:
{
uint32_t v___x_156_; uint32_t v___x_157_; uint32_t v___x_158_; uint32_t v___x_159_; uint8_t v___x_160_; 
v___x_156_ = 23;
v___x_157_ = lean_uint32_shift_right(v_x_130_, v___x_156_);
v___x_158_ = 255;
v___x_159_ = lean_uint32_land(v___x_157_, v___x_158_);
v___x_160_ = lean_uint32_dec_eq(v___x_159_, v___x_158_);
if (v___x_160_ == 0)
{
v___y_152_ = v___x_160_;
goto v___jp_151_;
}
else
{
uint32_t v___x_161_; uint32_t v___x_162_; uint32_t v___x_163_; uint8_t v___x_164_; 
v___x_161_ = 8388607;
v___x_162_ = lean_uint32_land(v_x_130_, v___x_161_);
v___x_163_ = 0;
v___x_164_ = lean_uint32_dec_eq(v___x_162_, v___x_163_);
if (v___x_164_ == 0)
{
v___y_152_ = v___x_160_;
goto v___jp_151_;
}
else
{
goto v___jp_141_;
}
}
}
v___jp_165_:
{
if (v___y_166_ == 0)
{
goto v___jp_155_;
}
else
{
uint32_t v___x_167_; uint32_t v___x_168_; uint32_t v___x_169_; uint8_t v___x_170_; 
v___x_167_ = 4194304;
v___x_168_ = lean_uint32_land(v_y_131_, v___x_167_);
v___x_169_ = 0;
v___x_170_ = lean_uint32_dec_eq(v___x_168_, v___x_169_);
if (v___x_170_ == 0)
{
goto v___jp_155_;
}
else
{
uint32_t v___x_171_; 
v___x_171_ = lean_uint32_lor(v_y_131_, v___x_167_);
return v___x_171_;
}
}
}
v___jp_172_:
{
uint32_t v___x_173_; uint32_t v___x_174_; uint32_t v___x_175_; uint32_t v___x_176_; uint8_t v___x_177_; 
v___x_173_ = 23;
v___x_174_ = lean_uint32_shift_right(v_y_131_, v___x_173_);
v___x_175_ = 255;
v___x_176_ = lean_uint32_land(v___x_174_, v___x_175_);
v___x_177_ = lean_uint32_dec_eq(v___x_176_, v___x_175_);
if (v___x_177_ == 0)
{
v___y_166_ = v___x_177_;
goto v___jp_165_;
}
else
{
uint32_t v___x_178_; uint32_t v___x_179_; uint32_t v___x_180_; uint8_t v___x_181_; 
v___x_178_ = 8388607;
v___x_179_ = lean_uint32_land(v_y_131_, v___x_178_);
v___x_180_ = 0;
v___x_181_ = lean_uint32_dec_eq(v___x_179_, v___x_180_);
if (v___x_181_ == 0)
{
v___y_166_ = v___x_177_;
goto v___jp_165_;
}
else
{
goto v___jp_155_;
}
}
}
v___jp_182_:
{
if (v___y_183_ == 0)
{
goto v___jp_172_;
}
else
{
uint32_t v___x_184_; uint32_t v___x_185_; uint32_t v___x_186_; uint8_t v___x_187_; 
v___x_184_ = 4194304;
v___x_185_ = lean_uint32_land(v_x_130_, v___x_184_);
v___x_186_ = 0;
v___x_187_ = lean_uint32_dec_eq(v___x_185_, v___x_186_);
if (v___x_187_ == 0)
{
goto v___jp_172_;
}
else
{
uint32_t v___x_188_; 
v___x_188_ = lean_uint32_lor(v_x_130_, v___x_184_);
return v___x_188_;
}
}
}
v___jp_189_:
{
float v_result_192_; uint8_t v___x_193_; 
v_result_192_ = lean_float32_add(v___y_190_, v___y_191_);
v___x_193_ = lean_float32_beq(v_result_192_, v_result_192_);
if (v___x_193_ == 0)
{
uint32_t v___x_194_; uint32_t v___x_195_; uint32_t v___x_196_; uint32_t v___x_197_; uint8_t v___x_198_; 
v___x_194_ = 23;
v___x_195_ = lean_uint32_shift_right(v_x_130_, v___x_194_);
v___x_196_ = 255;
v___x_197_ = lean_uint32_land(v___x_195_, v___x_196_);
v___x_198_ = lean_uint32_dec_eq(v___x_197_, v___x_196_);
if (v___x_198_ == 0)
{
v___y_183_ = v___x_198_;
goto v___jp_182_;
}
else
{
uint32_t v___x_199_; uint32_t v___x_200_; uint32_t v___x_201_; uint8_t v___x_202_; 
v___x_199_ = 8388607;
v___x_200_ = lean_uint32_land(v_x_130_, v___x_199_);
v___x_201_ = 0;
v___x_202_ = lean_uint32_dec_eq(v___x_200_, v___x_201_);
if (v___x_202_ == 0)
{
v___y_183_ = v___x_198_;
goto v___jp_182_;
}
else
{
goto v___jp_172_;
}
}
}
else
{
uint32_t v___x_203_; 
v___x_203_ = lean_float32_to_bits(v_result_192_);
return v___x_203_;
}
}
v___jp_204_:
{
if (v___y_206_ == 0)
{
float v___x_207_; 
v___x_207_ = lean_float32_of_bits(v_y_131_);
v___y_190_ = v___y_205_;
v___y_191_ = v___x_207_;
goto v___jp_189_;
}
else
{
uint32_t v___x_208_; uint32_t v___x_209_; uint32_t v___x_210_; uint32_t v___x_211_; float v___x_212_; lean_object* v___x_213_; uint32_t v___x_214_; uint32_t v___x_215_; lean_object* v___x_216_; lean_object* v___x_217_; float v___x_218_; float v___x_219_; 
v___x_208_ = 8388607;
v___x_209_ = lean_uint32_land(v_y_131_, v___x_208_);
v___x_210_ = 8388608;
v___x_211_ = lean_uint32_lor(v___x_209_, v___x_210_);
v___x_212_ = lean_uint32_to_float32(v___x_211_);
v___x_213_ = lp_competition_R2W01b_scaleTable;
v___x_214_ = 23;
v___x_215_ = lean_uint32_shift_right(v_y_131_, v___x_214_);
v___x_216_ = lean_uint32_to_nat(v___x_215_);
v___x_217_ = lean_array_fget_borrowed(v___x_213_, v___x_216_);
lean_dec(v___x_216_);
v___x_218_ = lean_unbox_float32(v___x_217_);
v___x_219_ = lean_float32_mul(v___x_212_, v___x_218_);
v___y_190_ = v___y_205_;
v___y_191_ = v___x_219_;
goto v___jp_189_;
}
}
v___jp_220_:
{
uint32_t v___x_222_; uint32_t v_a_223_; uint32_t v___x_224_; uint32_t v___x_225_; uint32_t v___x_226_; uint8_t v___x_227_; 
v___x_222_ = 2147483647;
v_a_223_ = lean_uint32_land(v_y_131_, v___x_222_);
v___x_224_ = 201326591;
v___x_225_ = 1;
v___x_226_ = lean_uint32_sub(v_a_223_, v___x_225_);
v___x_227_ = lean_uint32_dec_le(v___x_224_, v___x_226_);
if (v___x_227_ == 0)
{
v___y_205_ = v___y_221_;
v___y_206_ = v___x_227_;
goto v___jp_204_;
}
else
{
uint32_t v___x_228_; uint8_t v___x_229_; 
v___x_228_ = 2139095040;
v___x_229_ = lean_uint32_dec_lt(v_a_223_, v___x_228_);
v___y_205_ = v___y_221_;
v___y_206_ = v___x_229_;
goto v___jp_204_;
}
}
v___jp_230_:
{
lean_object* v___x_231_; lean_object* v___x_232_; lean_object* v___x_233_; uint32_t v___x_234_; 
v___x_231_ = lean_uint32_to_nat(v_x_130_);
v___x_232_ = lean_uint32_to_nat(v_y_131_);
v___x_233_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_231_, v___x_232_);
v___x_234_ = lean_uint32_of_nat(v___x_233_);
lean_dec(v___x_233_);
return v___x_234_;
}
v___jp_235_:
{
if (v___y_236_ == 0)
{
goto v___jp_230_;
}
else
{
uint32_t v___x_237_; uint32_t v___x_238_; 
v___x_237_ = 4194304;
v___x_238_ = lean_uint32_lor(v_y_131_, v___x_237_);
return v___x_238_;
}
}
v___jp_239_:
{
uint32_t v___x_240_; uint32_t v___x_241_; uint32_t v___x_242_; uint32_t v___x_243_; uint8_t v___x_244_; 
v___x_240_ = 23;
v___x_241_ = lean_uint32_shift_right(v_y_131_, v___x_240_);
v___x_242_ = 255;
v___x_243_ = lean_uint32_land(v___x_241_, v___x_242_);
v___x_244_ = lean_uint32_dec_eq(v___x_243_, v___x_242_);
if (v___x_244_ == 0)
{
v___y_236_ = v___x_244_;
goto v___jp_235_;
}
else
{
uint32_t v___x_245_; uint32_t v___x_246_; uint32_t v___x_247_; uint8_t v___x_248_; 
v___x_245_ = 8388607;
v___x_246_ = lean_uint32_land(v_y_131_, v___x_245_);
v___x_247_ = 0;
v___x_248_ = lean_uint32_dec_eq(v___x_246_, v___x_247_);
if (v___x_248_ == 0)
{
v___y_236_ = v___x_244_;
goto v___jp_235_;
}
else
{
goto v___jp_230_;
}
}
}
v___jp_249_:
{
if (v___y_250_ == 0)
{
goto v___jp_239_;
}
else
{
uint32_t v___x_251_; uint32_t v___x_252_; 
v___x_251_ = 4194304;
v___x_252_ = lean_uint32_lor(v_x_130_, v___x_251_);
return v___x_252_;
}
}
v___jp_253_:
{
uint32_t v___x_254_; uint32_t v___x_255_; uint32_t v___x_256_; uint32_t v___x_257_; uint8_t v___x_258_; 
v___x_254_ = 23;
v___x_255_ = lean_uint32_shift_right(v_x_130_, v___x_254_);
v___x_256_ = 255;
v___x_257_ = lean_uint32_land(v___x_255_, v___x_256_);
v___x_258_ = lean_uint32_dec_eq(v___x_257_, v___x_256_);
if (v___x_258_ == 0)
{
v___y_250_ = v___x_258_;
goto v___jp_249_;
}
else
{
uint32_t v___x_259_; uint32_t v___x_260_; uint32_t v___x_261_; uint8_t v___x_262_; 
v___x_259_ = 8388607;
v___x_260_ = lean_uint32_land(v_x_130_, v___x_259_);
v___x_261_ = 0;
v___x_262_ = lean_uint32_dec_eq(v___x_260_, v___x_261_);
if (v___x_262_ == 0)
{
v___y_250_ = v___x_258_;
goto v___jp_249_;
}
else
{
goto v___jp_239_;
}
}
}
v___jp_263_:
{
if (v___y_264_ == 0)
{
goto v___jp_253_;
}
else
{
uint32_t v___x_265_; uint32_t v___x_266_; uint32_t v___x_267_; uint8_t v___x_268_; 
v___x_265_ = 4194304;
v___x_266_ = lean_uint32_land(v_y_131_, v___x_265_);
v___x_267_ = 0;
v___x_268_ = lean_uint32_dec_eq(v___x_266_, v___x_267_);
if (v___x_268_ == 0)
{
goto v___jp_253_;
}
else
{
uint32_t v___x_269_; 
v___x_269_ = lean_uint32_lor(v_y_131_, v___x_265_);
return v___x_269_;
}
}
}
v___jp_270_:
{
uint32_t v___x_271_; uint32_t v___x_272_; uint32_t v___x_273_; uint32_t v___x_274_; uint8_t v___x_275_; 
v___x_271_ = 23;
v___x_272_ = lean_uint32_shift_right(v_y_131_, v___x_271_);
v___x_273_ = 255;
v___x_274_ = lean_uint32_land(v___x_272_, v___x_273_);
v___x_275_ = lean_uint32_dec_eq(v___x_274_, v___x_273_);
if (v___x_275_ == 0)
{
v___y_264_ = v___x_275_;
goto v___jp_263_;
}
else
{
uint32_t v___x_276_; uint32_t v___x_277_; uint32_t v___x_278_; uint8_t v___x_279_; 
v___x_276_ = 8388607;
v___x_277_ = lean_uint32_land(v_y_131_, v___x_276_);
v___x_278_ = 0;
v___x_279_ = lean_uint32_dec_eq(v___x_277_, v___x_278_);
if (v___x_279_ == 0)
{
v___y_264_ = v___x_275_;
goto v___jp_263_;
}
else
{
goto v___jp_253_;
}
}
}
v___jp_280_:
{
if (v___y_281_ == 0)
{
goto v___jp_270_;
}
else
{
uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint8_t v___x_285_; 
v___x_282_ = 4194304;
v___x_283_ = lean_uint32_land(v_x_130_, v___x_282_);
v___x_284_ = 0;
v___x_285_ = lean_uint32_dec_eq(v___x_283_, v___x_284_);
if (v___x_285_ == 0)
{
goto v___jp_270_;
}
else
{
uint32_t v___x_286_; 
v___x_286_ = lean_uint32_lor(v_x_130_, v___x_282_);
return v___x_286_;
}
}
}
v___jp_287_:
{
float v_result_290_; uint8_t v___x_291_; 
v_result_290_ = lean_float32_add(v___y_288_, v___y_289_);
v___x_291_ = lean_float32_beq(v_result_290_, v_result_290_);
if (v___x_291_ == 0)
{
uint32_t v___x_292_; uint32_t v___x_293_; uint32_t v___x_294_; uint32_t v___x_295_; uint8_t v___x_296_; 
v___x_292_ = 23;
v___x_293_ = lean_uint32_shift_right(v_x_130_, v___x_292_);
v___x_294_ = 255;
v___x_295_ = lean_uint32_land(v___x_293_, v___x_294_);
v___x_296_ = lean_uint32_dec_eq(v___x_295_, v___x_294_);
if (v___x_296_ == 0)
{
v___y_281_ = v___x_296_;
goto v___jp_280_;
}
else
{
uint32_t v___x_297_; uint32_t v___x_298_; uint32_t v___x_299_; uint8_t v___x_300_; 
v___x_297_ = 8388607;
v___x_298_ = lean_uint32_land(v_x_130_, v___x_297_);
v___x_299_ = 0;
v___x_300_ = lean_uint32_dec_eq(v___x_298_, v___x_299_);
if (v___x_300_ == 0)
{
v___y_281_ = v___x_296_;
goto v___jp_280_;
}
else
{
goto v___jp_270_;
}
}
}
else
{
uint32_t v___x_301_; 
v___x_301_ = lean_float32_to_bits(v_result_290_);
return v___x_301_;
}
}
v___jp_302_:
{
if (v___y_304_ == 0)
{
float v___x_305_; 
v___x_305_ = lean_float32_of_bits(v_y_131_);
v___y_288_ = v___y_303_;
v___y_289_ = v___x_305_;
goto v___jp_287_;
}
else
{
uint32_t v___x_306_; uint32_t v___x_307_; uint32_t v___x_308_; uint32_t v___x_309_; float v___x_310_; lean_object* v___x_311_; uint32_t v___x_312_; uint32_t v___x_313_; lean_object* v___x_314_; lean_object* v___x_315_; float v___x_316_; float v___x_317_; 
v___x_306_ = 8388607;
v___x_307_ = lean_uint32_land(v_y_131_, v___x_306_);
v___x_308_ = 8388608;
v___x_309_ = lean_uint32_lor(v___x_307_, v___x_308_);
v___x_310_ = lean_uint32_to_float32(v___x_309_);
v___x_311_ = lp_competition_R2W01b_scaleTable;
v___x_312_ = 23;
v___x_313_ = lean_uint32_shift_right(v_y_131_, v___x_312_);
v___x_314_ = lean_uint32_to_nat(v___x_313_);
v___x_315_ = lean_array_fget_borrowed(v___x_311_, v___x_314_);
lean_dec(v___x_314_);
v___x_316_ = lean_unbox_float32(v___x_315_);
v___x_317_ = lean_float32_mul(v___x_310_, v___x_316_);
v___y_288_ = v___y_303_;
v___y_289_ = v___x_317_;
goto v___jp_287_;
}
}
v___jp_318_:
{
uint32_t v___x_320_; uint32_t v_a_321_; uint32_t v___x_322_; uint32_t v___x_323_; uint32_t v___x_324_; uint8_t v___x_325_; 
v___x_320_ = 2147483647;
v_a_321_ = lean_uint32_land(v_y_131_, v___x_320_);
v___x_322_ = 201326591;
v___x_323_ = 1;
v___x_324_ = lean_uint32_sub(v_a_321_, v___x_323_);
v___x_325_ = lean_uint32_dec_le(v___x_322_, v___x_324_);
if (v___x_325_ == 0)
{
v___y_303_ = v___y_319_;
v___y_304_ = v___x_325_;
goto v___jp_302_;
}
else
{
uint32_t v___x_326_; uint8_t v___x_327_; 
v___x_326_ = 2139095040;
v___x_327_ = lean_uint32_dec_lt(v_a_321_, v___x_326_);
v___y_303_ = v___y_319_;
v___y_304_ = v___x_327_;
goto v___jp_302_;
}
}
v___jp_328_:
{
lean_object* v___x_329_; lean_object* v___x_330_; lean_object* v___x_331_; uint32_t v___x_332_; 
v___x_329_ = lean_uint32_to_nat(v_x_130_);
v___x_330_ = lean_uint32_to_nat(v_y_131_);
v___x_331_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_329_, v___x_330_);
v___x_332_ = lean_uint32_of_nat(v___x_331_);
lean_dec(v___x_331_);
return v___x_332_;
}
v___jp_333_:
{
if (v___y_334_ == 0)
{
goto v___jp_328_;
}
else
{
uint32_t v___x_335_; uint32_t v___x_336_; 
v___x_335_ = 4194304;
v___x_336_ = lean_uint32_lor(v_y_131_, v___x_335_);
return v___x_336_;
}
}
v___jp_337_:
{
uint32_t v___x_338_; uint32_t v___x_339_; uint32_t v___x_340_; uint32_t v___x_341_; uint8_t v___x_342_; 
v___x_338_ = 23;
v___x_339_ = lean_uint32_shift_right(v_y_131_, v___x_338_);
v___x_340_ = 255;
v___x_341_ = lean_uint32_land(v___x_339_, v___x_340_);
v___x_342_ = lean_uint32_dec_eq(v___x_341_, v___x_340_);
if (v___x_342_ == 0)
{
v___y_334_ = v___x_342_;
goto v___jp_333_;
}
else
{
uint32_t v___x_343_; uint32_t v___x_344_; uint32_t v___x_345_; uint8_t v___x_346_; 
v___x_343_ = 8388607;
v___x_344_ = lean_uint32_land(v_y_131_, v___x_343_);
v___x_345_ = 0;
v___x_346_ = lean_uint32_dec_eq(v___x_344_, v___x_345_);
if (v___x_346_ == 0)
{
v___y_334_ = v___x_342_;
goto v___jp_333_;
}
else
{
goto v___jp_328_;
}
}
}
v___jp_347_:
{
if (v___y_348_ == 0)
{
goto v___jp_337_;
}
else
{
uint32_t v___x_349_; uint32_t v___x_350_; 
v___x_349_ = 4194304;
v___x_350_ = lean_uint32_lor(v_x_130_, v___x_349_);
return v___x_350_;
}
}
v___jp_351_:
{
uint32_t v___x_352_; uint32_t v___x_353_; uint32_t v___x_354_; uint32_t v___x_355_; uint8_t v___x_356_; 
v___x_352_ = 23;
v___x_353_ = lean_uint32_shift_right(v_x_130_, v___x_352_);
v___x_354_ = 255;
v___x_355_ = lean_uint32_land(v___x_353_, v___x_354_);
v___x_356_ = lean_uint32_dec_eq(v___x_355_, v___x_354_);
if (v___x_356_ == 0)
{
v___y_348_ = v___x_356_;
goto v___jp_347_;
}
else
{
uint32_t v___x_357_; uint32_t v___x_358_; uint32_t v___x_359_; uint8_t v___x_360_; 
v___x_357_ = 8388607;
v___x_358_ = lean_uint32_land(v_x_130_, v___x_357_);
v___x_359_ = 0;
v___x_360_ = lean_uint32_dec_eq(v___x_358_, v___x_359_);
if (v___x_360_ == 0)
{
v___y_348_ = v___x_356_;
goto v___jp_347_;
}
else
{
goto v___jp_337_;
}
}
}
v___jp_361_:
{
if (v___y_362_ == 0)
{
goto v___jp_351_;
}
else
{
uint32_t v___x_363_; uint32_t v___x_364_; uint32_t v___x_365_; uint8_t v___x_366_; 
v___x_363_ = 4194304;
v___x_364_ = lean_uint32_land(v_y_131_, v___x_363_);
v___x_365_ = 0;
v___x_366_ = lean_uint32_dec_eq(v___x_364_, v___x_365_);
if (v___x_366_ == 0)
{
goto v___jp_351_;
}
else
{
uint32_t v___x_367_; 
v___x_367_ = lean_uint32_lor(v_y_131_, v___x_363_);
return v___x_367_;
}
}
}
v___jp_368_:
{
uint32_t v___x_369_; uint32_t v___x_370_; uint32_t v___x_371_; uint32_t v___x_372_; uint8_t v___x_373_; 
v___x_369_ = 23;
v___x_370_ = lean_uint32_shift_right(v_y_131_, v___x_369_);
v___x_371_ = 255;
v___x_372_ = lean_uint32_land(v___x_370_, v___x_371_);
v___x_373_ = lean_uint32_dec_eq(v___x_372_, v___x_371_);
if (v___x_373_ == 0)
{
v___y_362_ = v___x_373_;
goto v___jp_361_;
}
else
{
uint32_t v___x_374_; uint32_t v___x_375_; uint32_t v___x_376_; uint8_t v___x_377_; 
v___x_374_ = 8388607;
v___x_375_ = lean_uint32_land(v_y_131_, v___x_374_);
v___x_376_ = 0;
v___x_377_ = lean_uint32_dec_eq(v___x_375_, v___x_376_);
if (v___x_377_ == 0)
{
v___y_362_ = v___x_373_;
goto v___jp_361_;
}
else
{
goto v___jp_351_;
}
}
}
v___jp_378_:
{
if (v___y_379_ == 0)
{
goto v___jp_368_;
}
else
{
uint32_t v___x_380_; uint32_t v___x_381_; uint32_t v___x_382_; uint8_t v___x_383_; 
v___x_380_ = 4194304;
v___x_381_ = lean_uint32_land(v_x_130_, v___x_380_);
v___x_382_ = 0;
v___x_383_ = lean_uint32_dec_eq(v___x_381_, v___x_382_);
if (v___x_383_ == 0)
{
goto v___jp_368_;
}
else
{
uint32_t v___x_384_; 
v___x_384_ = lean_uint32_lor(v_x_130_, v___x_380_);
return v___x_384_;
}
}
}
v___jp_385_:
{
float v_result_388_; uint8_t v___x_389_; 
v_result_388_ = lean_float32_add(v___y_386_, v___y_387_);
v___x_389_ = lean_float32_beq(v_result_388_, v_result_388_);
if (v___x_389_ == 0)
{
uint32_t v___x_390_; uint32_t v___x_391_; uint32_t v___x_392_; uint32_t v___x_393_; uint8_t v___x_394_; 
v___x_390_ = 23;
v___x_391_ = lean_uint32_shift_right(v_x_130_, v___x_390_);
v___x_392_ = 255;
v___x_393_ = lean_uint32_land(v___x_391_, v___x_392_);
v___x_394_ = lean_uint32_dec_eq(v___x_393_, v___x_392_);
if (v___x_394_ == 0)
{
v___y_379_ = v___x_394_;
goto v___jp_378_;
}
else
{
uint32_t v___x_395_; uint32_t v___x_396_; uint32_t v___x_397_; uint8_t v___x_398_; 
v___x_395_ = 8388607;
v___x_396_ = lean_uint32_land(v_x_130_, v___x_395_);
v___x_397_ = 0;
v___x_398_ = lean_uint32_dec_eq(v___x_396_, v___x_397_);
if (v___x_398_ == 0)
{
v___y_379_ = v___x_394_;
goto v___jp_378_;
}
else
{
goto v___jp_368_;
}
}
}
else
{
uint32_t v___x_399_; 
v___x_399_ = lean_float32_to_bits(v_result_388_);
return v___x_399_;
}
}
v___jp_400_:
{
if (v___y_402_ == 0)
{
float v___x_403_; 
v___x_403_ = lean_float32_of_bits(v_y_131_);
v___y_386_ = v___y_401_;
v___y_387_ = v___x_403_;
goto v___jp_385_;
}
else
{
uint32_t v___x_404_; uint32_t v___x_405_; uint32_t v___x_406_; uint32_t v___x_407_; float v___x_408_; lean_object* v___x_409_; uint32_t v___x_410_; uint32_t v___x_411_; lean_object* v___x_412_; lean_object* v___x_413_; float v___x_414_; float v___x_415_; 
v___x_404_ = 8388607;
v___x_405_ = lean_uint32_land(v_y_131_, v___x_404_);
v___x_406_ = 8388608;
v___x_407_ = lean_uint32_lor(v___x_405_, v___x_406_);
v___x_408_ = lean_uint32_to_float32(v___x_407_);
v___x_409_ = lp_competition_R2W01b_scaleTable;
v___x_410_ = 23;
v___x_411_ = lean_uint32_shift_right(v_y_131_, v___x_410_);
v___x_412_ = lean_uint32_to_nat(v___x_411_);
v___x_413_ = lean_array_fget_borrowed(v___x_409_, v___x_412_);
lean_dec(v___x_412_);
v___x_414_ = lean_unbox_float32(v___x_413_);
v___x_415_ = lean_float32_mul(v___x_408_, v___x_414_);
v___y_386_ = v___y_401_;
v___y_387_ = v___x_415_;
goto v___jp_385_;
}
}
v___jp_416_:
{
uint32_t v___x_418_; uint32_t v_a_419_; uint32_t v___x_420_; uint32_t v___x_421_; uint32_t v___x_422_; uint8_t v___x_423_; 
v___x_418_ = 2147483647;
v_a_419_ = lean_uint32_land(v_y_131_, v___x_418_);
v___x_420_ = 201326591;
v___x_421_ = 1;
v___x_422_ = lean_uint32_sub(v_a_419_, v___x_421_);
v___x_423_ = lean_uint32_dec_le(v___x_420_, v___x_422_);
if (v___x_423_ == 0)
{
v___y_401_ = v___y_417_;
v___y_402_ = v___x_423_;
goto v___jp_400_;
}
else
{
uint32_t v___x_424_; uint8_t v___x_425_; 
v___x_424_ = 2139095040;
v___x_425_ = lean_uint32_dec_lt(v_a_419_, v___x_424_);
v___y_401_ = v___y_417_;
v___y_402_ = v___x_425_;
goto v___jp_400_;
}
}
v___jp_428_:
{
if (v___y_429_ == 0)
{
float v___x_430_; 
v___x_430_ = lean_float32_of_bits(v_x_130_);
v___y_221_ = v___x_430_;
goto v___jp_220_;
}
else
{
uint32_t v___x_431_; uint32_t v___x_432_; uint32_t v___x_433_; uint32_t v___x_434_; float v___x_435_; lean_object* v___x_436_; lean_object* v___x_437_; lean_object* v___x_438_; float v___x_439_; float v___x_440_; 
v___x_431_ = 8388607;
v___x_432_ = lean_uint32_land(v_x_130_, v___x_431_);
v___x_433_ = 8388608;
v___x_434_ = lean_uint32_lor(v___x_432_, v___x_433_);
v___x_435_ = lean_uint32_to_float32(v___x_434_);
v___x_436_ = lp_competition_R2W01b_scaleTable;
v___x_437_ = lean_uint32_to_nat(v___x_427_);
v___x_438_ = lean_array_fget_borrowed(v___x_436_, v___x_437_);
lean_dec(v___x_437_);
v___x_439_ = lean_unbox_float32(v___x_438_);
v___x_440_ = lean_float32_mul(v___x_435_, v___x_439_);
v___y_221_ = v___x_440_;
goto v___jp_220_;
}
}
v___jp_441_:
{
if (v___y_442_ == 0)
{
float v___x_443_; 
v___x_443_ = lean_float32_of_bits(v_x_130_);
v___y_319_ = v___x_443_;
goto v___jp_318_;
}
else
{
uint32_t v___x_444_; uint32_t v___x_445_; uint32_t v___x_446_; uint32_t v___x_447_; float v___x_448_; lean_object* v___x_449_; lean_object* v___x_450_; lean_object* v___x_451_; float v___x_452_; float v___x_453_; 
v___x_444_ = 8388607;
v___x_445_ = lean_uint32_land(v_x_130_, v___x_444_);
v___x_446_ = 8388608;
v___x_447_ = lean_uint32_lor(v___x_445_, v___x_446_);
v___x_448_ = lean_uint32_to_float32(v___x_447_);
v___x_449_ = lp_competition_R2W01b_scaleTable;
v___x_450_ = lean_uint32_to_nat(v___x_427_);
v___x_451_ = lean_array_fget_borrowed(v___x_449_, v___x_450_);
lean_dec(v___x_450_);
v___x_452_ = lean_unbox_float32(v___x_451_);
v___x_453_ = lean_float32_mul(v___x_448_, v___x_452_);
v___y_319_ = v___x_453_;
goto v___jp_318_;
}
}
v___jp_454_:
{
if (v___y_457_ == 0)
{
float v___x_458_; 
v___x_458_ = lean_float32_of_bits(v_x_130_);
v___y_417_ = v___x_458_;
goto v___jp_416_;
}
else
{
uint32_t v___x_459_; uint32_t v___x_460_; float v___x_461_; lean_object* v___x_462_; lean_object* v___x_463_; lean_object* v___x_464_; float v___x_465_; float v___x_466_; 
v___x_459_ = lean_uint32_land(v_x_130_, v___y_456_);
v___x_460_ = lean_uint32_lor(v___x_459_, v___y_455_);
v___x_461_ = lean_uint32_to_float32(v___x_460_);
v___x_462_ = lp_competition_R2W01b_scaleTable;
v___x_463_ = lean_uint32_to_nat(v___x_427_);
v___x_464_ = lean_array_fget_borrowed(v___x_462_, v___x_463_);
lean_dec(v___x_463_);
v___x_465_ = lean_unbox_float32(v___x_464_);
v___x_466_ = lean_float32_mul(v___x_461_, v___x_465_);
v___y_417_ = v___x_466_;
goto v___jp_416_;
}
}
v___jp_470_:
{
uint8_t v___x_478_; 
v___x_478_ = lean_uint32_dec_eq(v___y_477_, v___y_475_);
if (v___x_478_ == 0)
{
uint32_t v___x_479_; uint32_t v___x_480_; uint32_t v___x_481_; uint8_t v___x_482_; 
v___x_479_ = 25;
v___x_480_ = lean_uint32_sub(v___y_471_, v___x_479_);
v___x_481_ = 228;
v___x_482_ = lean_uint32_dec_le(v___x_480_, v___x_481_);
if (v___x_482_ == 0)
{
uint32_t v___x_483_; uint32_t v_a_484_; uint32_t v___x_485_; uint32_t v___x_486_; uint8_t v___x_487_; 
v___x_483_ = 2147483647;
v_a_484_ = lean_uint32_land(v_x_130_, v___x_483_);
v___x_485_ = 201326591;
v___x_486_ = lean_uint32_sub(v_a_484_, v___x_469_);
v___x_487_ = lean_uint32_dec_le(v___x_485_, v___x_486_);
if (v___x_487_ == 0)
{
v___y_455_ = v___y_473_;
v___y_456_ = v___y_474_;
v___y_457_ = v___x_487_;
goto v___jp_454_;
}
else
{
uint32_t v___x_488_; uint8_t v___x_489_; 
v___x_488_ = 2139095040;
v___x_489_ = lean_uint32_dec_lt(v_a_484_, v___x_488_);
v___y_455_ = v___y_473_;
v___y_456_ = v___y_474_;
v___y_457_ = v___x_489_;
goto v___jp_454_;
}
}
else
{
uint32_t v___x_490_; uint32_t v___x_491_; uint32_t v___x_492_; uint32_t v___x_493_; uint32_t v_delta_494_; float v___x_495_; uint32_t v_mid_496_; uint32_t v___x_497_; 
v___x_490_ = 153;
v___x_491_ = lean_uint32_sub(v___y_471_, v___x_490_);
v___x_492_ = lean_uint32_shift_left(v___x_491_, v___x_426_);
v___x_493_ = lean_uint32_land(v___y_476_, v___y_472_);
v_delta_494_ = lean_uint32_add(v___x_492_, v___x_493_);
v___x_495_ = lean_uint32_to_float32(v___y_477_);
v_mid_496_ = lean_float32_to_bits(v___x_495_);
v___x_497_ = lean_uint32_add(v_mid_496_, v_delta_494_);
return v___x_497_;
}
}
else
{
return v___y_475_;
}
}
v___jp_498_:
{
uint32_t v___x_505_; uint32_t v___x_506_; uint32_t v___x_507_; uint32_t v___x_508_; uint8_t v_same_509_; 
v___x_505_ = lean_uint32_xor(v_x_130_, v_y_131_);
v___x_506_ = 2147483648;
v___x_507_ = lean_uint32_land(v___x_505_, v___x_506_);
v___x_508_ = 0;
v_same_509_ = lean_uint32_dec_eq(v___x_507_, v___x_508_);
if (v_same_509_ == 0)
{
uint32_t v___x_510_; 
v___x_510_ = lean_uint32_sub(v___y_500_, v___y_504_);
v___y_471_ = v___y_499_;
v___y_472_ = v___x_506_;
v___y_473_ = v___y_501_;
v___y_474_ = v___y_502_;
v___y_475_ = v___x_508_;
v___y_476_ = v___y_503_;
v___y_477_ = v___x_510_;
goto v___jp_470_;
}
else
{
uint32_t v___x_511_; 
v___x_511_ = lean_uint32_add(v___y_500_, v___y_504_);
v___y_471_ = v___y_499_;
v___y_472_ = v___x_506_;
v___y_473_ = v___y_501_;
v___y_474_ = v___y_502_;
v___y_475_ = v___x_508_;
v___y_476_ = v___y_503_;
v___y_477_ = v___x_511_;
goto v___jp_470_;
}
}
v___jp_512_:
{
uint32_t v___x_517_; uint32_t v___x_518_; uint32_t v___x_519_; uint32_t v___x_520_; uint32_t v___x_521_; uint32_t v_a_522_; uint32_t v___x_523_; uint32_t v___x_524_; uint8_t v___x_525_; 
v___x_517_ = 8388607;
v___x_518_ = lean_uint32_land(v___y_515_, v___x_517_);
v___x_519_ = 8388608;
v___x_520_ = lean_uint32_lor(v___x_518_, v___x_519_);
v___x_521_ = 3;
v_a_522_ = lean_uint32_shift_left(v___x_520_, v___x_521_);
v___x_523_ = lean_uint32_sub(v___y_513_, v___y_516_);
v___x_524_ = 32;
v___x_525_ = lean_uint32_dec_lt(v___x_523_, v___x_524_);
if (v___x_525_ == 0)
{
v___y_499_ = v___y_513_;
v___y_500_ = v_a_522_;
v___y_501_ = v___x_519_;
v___y_502_ = v___x_517_;
v___y_503_ = v___y_515_;
v___y_504_ = v___x_469_;
goto v___jp_498_;
}
else
{
uint32_t v___x_526_; uint32_t v___x_527_; uint32_t v_b_528_; uint32_t v___x_529_; uint32_t v___x_530_; uint32_t v___x_531_; uint32_t v___x_532_; uint32_t v___x_533_; uint8_t v___x_534_; 
v___x_526_ = lean_uint32_land(v___y_514_, v___x_517_);
v___x_527_ = lean_uint32_lor(v___x_526_, v___x_519_);
v_b_528_ = lean_uint32_shift_left(v___x_527_, v___x_521_);
v___x_529_ = lean_uint32_shift_right(v_b_528_, v___x_523_);
v___x_530_ = lean_uint32_shift_left(v___x_469_, v___x_523_);
v___x_531_ = lean_uint32_sub(v___x_530_, v___x_469_);
v___x_532_ = lean_uint32_land(v_b_528_, v___x_531_);
v___x_533_ = 0;
v___x_534_ = lean_uint32_dec_eq(v___x_532_, v___x_533_);
if (v___x_534_ == 0)
{
uint32_t v___x_535_; 
v___x_535_ = lean_uint32_lor(v___x_529_, v___x_469_);
v___y_499_ = v___y_513_;
v___y_500_ = v_a_522_;
v___y_501_ = v___x_519_;
v___y_502_ = v___x_517_;
v___y_503_ = v___y_515_;
v___y_504_ = v___x_535_;
goto v___jp_498_;
}
else
{
v___y_499_ = v___y_513_;
v___y_500_ = v_a_522_;
v___y_501_ = v___x_519_;
v___y_502_ = v___x_517_;
v___y_503_ = v___y_515_;
v___y_504_ = v___x_529_;
goto v___jp_498_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_r19CostGuardedAdd___boxed(lean_object* v_x_570_, lean_object* v_y_571_){
_start:
{
uint32_t v_x_boxed_572_; uint32_t v_y_boxed_573_; uint32_t v_res_574_; lean_object* v_r_575_; 
v_x_boxed_572_ = lean_unbox_uint32(v_x_570_);
lean_dec(v_x_570_);
v_y_boxed_573_ = lean_unbox_uint32(v_y_571_);
lean_dec(v_y_571_);
v_res_574_ = lp_competition_r19CostGuardedAdd(v_x_boxed_572_, v_y_boxed_573_);
v_r_575_ = lean_box_uint32(v_res_574_);
return v_r_575_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_576_, uint32_t v___y_577_){
_start:
{
uint32_t v___y_579_; uint32_t v___y_583_; uint32_t v___y_587_; uint32_t v___y_588_; uint32_t v___y_589_; uint64_t v___y_593_; uint32_t v___y_594_; uint8_t v___y_595_; uint64_t v___y_596_; uint32_t v___y_608_; uint32_t v___y_609_; uint32_t v___y_610_; uint64_t v___y_614_; uint32_t v___y_615_; uint8_t v___y_616_; uint64_t v___y_617_; uint8_t v___y_629_; uint8_t v___y_645_; uint8_t v___y_659_; uint8_t v___y_676_; float v___y_683_; float v___y_684_; float v___y_698_; uint8_t v___y_699_; float v___y_714_; uint32_t v___x_723_; uint32_t v___x_724_; uint8_t v___y_726_; uint32_t v___x_738_; uint32_t v___y_740_; uint32_t v___y_741_; uint32_t v___y_742_; uint32_t v___y_743_; uint32_t v___y_750_; uint32_t v___y_751_; uint8_t v___y_752_; uint32_t v___y_753_; uint64_t v___y_757_; uint64_t v___y_758_; uint32_t v___y_759_; uint8_t v___y_760_; uint64_t v___y_761_; uint8_t v___y_771_; uint64_t v___y_772_; uint64_t v___y_773_; uint32_t v___y_774_; uint8_t v___y_775_; uint64_t v___y_776_; uint64_t v___y_783_; uint64_t v___y_784_; uint32_t v___y_785_; uint8_t v___y_786_; uint64_t v___y_787_; uint64_t v___y_793_; uint64_t v___y_794_; uint64_t v___y_795_; uint32_t v___y_796_; uint8_t v___y_797_; uint64_t v___y_798_; uint64_t v___y_853_; uint64_t v___y_854_; uint64_t v___y_855_; uint64_t v___y_856_; uint32_t v___y_857_; uint8_t v___y_858_; uint64_t v___y_859_; uint64_t v___y_865_; uint64_t v___y_866_; uint64_t v___y_867_; uint64_t v___y_868_; uint64_t v___y_869_; uint64_t v___y_870_; uint32_t v___y_871_; uint8_t v___y_872_; uint64_t v___y_873_; uint64_t v___y_878_; uint64_t v___y_879_; uint64_t v___y_880_; uint64_t v___y_881_; uint32_t v___y_882_; uint8_t v___y_883_; uint64_t v___y_884_; uint64_t v___y_889_; uint64_t v___y_890_; uint64_t v___y_891_; uint64_t v___y_892_; uint64_t v___y_893_; uint64_t v___y_894_; uint32_t v___y_895_; uint8_t v___y_896_; uint64_t v___y_897_; uint64_t v___y_902_; uint64_t v___y_903_; uint64_t v___y_904_; uint64_t v___y_905_; uint32_t v___y_906_; uint8_t v___y_907_; uint64_t v___y_908_; uint64_t v___y_913_; uint64_t v___y_914_; uint64_t v___y_915_; uint64_t v___y_916_; uint32_t v___y_917_; uint64_t v___y_918_; uint8_t v___y_919_; uint64_t v___y_920_; uint64_t v___y_921_; uint64_t v___y_926_; uint64_t v___y_927_; uint64_t v___y_928_; uint32_t v___y_929_; uint8_t v___y_930_; uint64_t v___y_931_; uint64_t v___y_932_; uint64_t v___y_937_; uint64_t v___y_938_; uint64_t v___y_939_; uint64_t v___y_940_; uint64_t v___y_941_; uint32_t v___y_942_; uint8_t v___y_943_; uint64_t v___y_944_; uint64_t v___y_945_; uint64_t v___y_950_; uint64_t v___y_951_; uint64_t v___y_952_; uint64_t v___y_953_; uint32_t v___y_954_; uint8_t v___y_955_; uint64_t v___y_956_; uint64_t v___y_961_; uint64_t v___y_962_; uint64_t v___y_963_; uint64_t v___y_964_; uint32_t v___y_965_; uint8_t v___y_966_; uint64_t v___y_967_; uint64_t v___y_971_; uint64_t v___y_972_; uint32_t v___y_973_; uint8_t v___y_974_; uint64_t v___y_983_; uint64_t v___y_984_; uint32_t v___y_985_; uint8_t v___y_986_; uint64_t v___y_987_; uint64_t v___y_988_; uint32_t v_ex_1021_; uint32_t v___x_1022_; uint32_t v_ey_1023_; uint64_t v___y_1025_; uint32_t v___y_1026_; uint8_t v___y_1027_; uint64_t v___y_1028_; uint64_t v___y_1029_; uint64_t v___y_1036_; uint32_t v___y_1037_; uint8_t v___y_1038_; uint64_t v___y_1039_; uint32_t v___y_1046_; uint32_t v___y_1047_; uint8_t v___y_1048_; uint64_t v___y_1049_; uint8_t v___y_1057_; uint32_t v___x_1067_; uint32_t v___x_1068_; uint8_t v___x_1069_; uint8_t v___y_1071_; uint8_t v___y_1072_; uint8_t v___y_1074_; uint8_t v___y_1075_; uint8_t v___y_1076_; uint8_t v___y_1078_; uint8_t v___y_1079_; uint8_t v___y_1085_; 
v___x_723_ = 23;
v___x_724_ = lean_uint32_shift_right(v___y_576_, v___x_723_);
v___x_738_ = 255;
v_ex_1021_ = lean_uint32_land(v___x_724_, v___x_738_);
v___x_1022_ = lean_uint32_shift_right(v___y_577_, v___x_723_);
v_ey_1023_ = lean_uint32_land(v___x_1022_, v___x_738_);
v___x_1067_ = lean_uint32_add(v_ex_1021_, v_ey_1023_);
v___x_1068_ = 128;
v___x_1069_ = lean_uint32_dec_lt(v___x_1067_, v___x_1068_);
if (v___x_1069_ == 0)
{
uint32_t v___x_1094_; uint32_t v_a_1095_; uint32_t v___x_1096_; uint32_t v___x_1097_; uint32_t v___x_1098_; uint8_t v___x_1099_; 
v___x_1094_ = 2147483647;
v_a_1095_ = lean_uint32_land(v___y_576_, v___x_1094_);
v___x_1096_ = 201326591;
v___x_1097_ = 1;
v___x_1098_ = lean_uint32_sub(v_a_1095_, v___x_1097_);
v___x_1099_ = lean_uint32_dec_le(v___x_1096_, v___x_1098_);
if (v___x_1099_ == 0)
{
v___y_726_ = v___x_1099_;
goto v___jp_725_;
}
else
{
uint32_t v___x_1100_; uint8_t v___x_1101_; 
v___x_1100_ = 2139095040;
v___x_1101_ = lean_uint32_dec_lt(v_a_1095_, v___x_1100_);
v___y_726_ = v___x_1101_;
goto v___jp_725_;
}
}
else
{
uint32_t v___x_1102_; uint32_t v___x_1103_; uint32_t v___x_1104_; uint8_t v___x_1105_; 
v___x_1102_ = 4278190080;
v___x_1103_ = 1;
v___x_1104_ = lean_uint32_shift_left(v___y_576_, v___x_1103_);
v___x_1105_ = lean_uint32_dec_le(v___x_1102_, v___x_1104_);
if (v___x_1105_ == 0)
{
uint32_t v___x_1106_; uint8_t v___x_1107_; 
v___x_1106_ = lean_uint32_shift_left(v___y_577_, v___x_1103_);
v___x_1107_ = lean_uint32_dec_le(v___x_1102_, v___x_1106_);
v___y_1085_ = v___x_1107_;
goto v___jp_1084_;
}
else
{
v___y_1085_ = v___x_1105_;
goto v___jp_1084_;
}
}
v___jp_578_:
{
uint32_t v___x_580_; uint32_t v___x_581_; 
v___x_580_ = 8388608;
v___x_581_ = lean_uint32_lor(v___y_579_, v___x_580_);
return v___x_581_;
}
v___jp_582_:
{
uint32_t v___x_584_; uint32_t v___x_585_; 
v___x_584_ = 8388608;
v___x_585_ = lean_uint32_lor(v___y_583_, v___x_584_);
return v___x_585_;
}
v___jp_586_:
{
uint32_t v___x_590_; uint32_t v___x_591_; 
v___x_590_ = lean_uint32_land(v___y_587_, v___y_588_);
v___x_591_ = lean_uint32_lor(v___y_589_, v___x_590_);
return v___x_591_;
}
v___jp_592_:
{
uint8_t v___x_597_; 
v___x_597_ = lean_uint64_dec_eq(v___y_596_, v___y_593_);
if (v___x_597_ == 0)
{
uint64_t v___x_598_; uint8_t v___x_599_; 
v___x_598_ = 8388608ULL;
v___x_599_ = lean_uint64_dec_eq(v___y_596_, v___x_598_);
if (v___x_599_ == 0)
{
uint32_t v___x_600_; 
v___x_600_ = lean_uint64_to_uint32(v___y_596_);
if (v___y_595_ == 0)
{
uint32_t v___x_601_; 
v___x_601_ = 0;
v___y_587_ = v___x_600_;
v___y_588_ = v___y_594_;
v___y_589_ = v___x_601_;
goto v___jp_586_;
}
else
{
uint32_t v___x_602_; 
v___x_602_ = 2147483648;
v___y_587_ = v___x_600_;
v___y_588_ = v___y_594_;
v___y_589_ = v___x_602_;
goto v___jp_586_;
}
}
else
{
if (v___y_595_ == 0)
{
uint32_t v___x_603_; 
v___x_603_ = 0;
v___y_583_ = v___x_603_;
goto v___jp_582_;
}
else
{
uint32_t v___x_604_; 
v___x_604_ = 2147483648;
v___y_583_ = v___x_604_;
goto v___jp_582_;
}
}
}
else
{
if (v___y_595_ == 0)
{
uint32_t v___x_605_; 
v___x_605_ = 0;
return v___x_605_;
}
else
{
uint32_t v___x_606_; 
v___x_606_ = 2147483648;
return v___x_606_;
}
}
}
v___jp_607_:
{
uint32_t v___x_611_; uint32_t v___x_612_; 
v___x_611_ = lean_uint32_land(v___y_609_, v___y_608_);
v___x_612_ = lean_uint32_lor(v___y_610_, v___x_611_);
return v___x_612_;
}
v___jp_613_:
{
uint8_t v___x_618_; 
v___x_618_ = lean_uint64_dec_eq(v___y_617_, v___y_614_);
if (v___x_618_ == 0)
{
uint64_t v___x_619_; uint8_t v___x_620_; 
v___x_619_ = 8388608ULL;
v___x_620_ = lean_uint64_dec_eq(v___y_617_, v___x_619_);
if (v___x_620_ == 0)
{
uint32_t v___x_621_; 
v___x_621_ = lean_uint64_to_uint32(v___y_617_);
if (v___y_616_ == 0)
{
uint32_t v___x_622_; 
v___x_622_ = 0;
v___y_608_ = v___y_615_;
v___y_609_ = v___x_621_;
v___y_610_ = v___x_622_;
goto v___jp_607_;
}
else
{
uint32_t v___x_623_; 
v___x_623_ = 2147483648;
v___y_608_ = v___y_615_;
v___y_609_ = v___x_621_;
v___y_610_ = v___x_623_;
goto v___jp_607_;
}
}
else
{
if (v___y_616_ == 0)
{
uint32_t v___x_624_; 
v___x_624_ = 0;
v___y_579_ = v___x_624_;
goto v___jp_578_;
}
else
{
uint32_t v___x_625_; 
v___x_625_ = 2147483648;
v___y_579_ = v___x_625_;
goto v___jp_578_;
}
}
}
else
{
if (v___y_616_ == 0)
{
uint32_t v___x_626_; 
v___x_626_ = 0;
return v___x_626_;
}
else
{
uint32_t v___x_627_; 
v___x_627_ = 2147483648;
return v___x_627_;
}
}
}
v___jp_628_:
{
if (v___y_629_ == 0)
{
uint32_t v___x_630_; 
v___x_630_ = lp_competition_Submission_FastMul_mul(v___y_576_, v___y_577_);
return v___x_630_;
}
else
{
uint32_t v___x_631_; uint32_t v___x_632_; 
v___x_631_ = 4194304;
v___x_632_ = lean_uint32_lor(v___y_577_, v___x_631_);
return v___x_632_;
}
}
v___jp_633_:
{
uint32_t v___x_634_; uint32_t v___x_635_; uint32_t v___x_636_; uint32_t v___x_637_; uint8_t v___x_638_; 
v___x_634_ = 23;
v___x_635_ = lean_uint32_shift_right(v___y_577_, v___x_634_);
v___x_636_ = 255;
v___x_637_ = lean_uint32_land(v___x_635_, v___x_636_);
v___x_638_ = lean_uint32_dec_eq(v___x_637_, v___x_636_);
if (v___x_638_ == 0)
{
v___y_629_ = v___x_638_;
goto v___jp_628_;
}
else
{
uint32_t v___x_639_; uint32_t v___x_640_; uint32_t v___x_641_; uint8_t v___x_642_; 
v___x_639_ = 8388607;
v___x_640_ = lean_uint32_land(v___y_577_, v___x_639_);
v___x_641_ = 0;
v___x_642_ = lean_uint32_dec_eq(v___x_640_, v___x_641_);
if (v___x_642_ == 0)
{
v___y_629_ = v___x_638_;
goto v___jp_628_;
}
else
{
uint32_t v___x_643_; 
v___x_643_ = lp_competition_Submission_FastMul_mul(v___y_576_, v___y_577_);
return v___x_643_;
}
}
}
v___jp_644_:
{
if (v___y_645_ == 0)
{
goto v___jp_633_;
}
else
{
uint32_t v___x_646_; uint32_t v___x_647_; 
v___x_646_ = 4194304;
v___x_647_ = lean_uint32_lor(v___y_576_, v___x_646_);
return v___x_647_;
}
}
v___jp_648_:
{
uint32_t v___x_649_; uint32_t v___x_650_; uint32_t v___x_651_; uint32_t v___x_652_; uint8_t v___x_653_; 
v___x_649_ = 23;
v___x_650_ = lean_uint32_shift_right(v___y_576_, v___x_649_);
v___x_651_ = 255;
v___x_652_ = lean_uint32_land(v___x_650_, v___x_651_);
v___x_653_ = lean_uint32_dec_eq(v___x_652_, v___x_651_);
if (v___x_653_ == 0)
{
v___y_645_ = v___x_653_;
goto v___jp_644_;
}
else
{
uint32_t v___x_654_; uint32_t v___x_655_; uint32_t v___x_656_; uint8_t v___x_657_; 
v___x_654_ = 8388607;
v___x_655_ = lean_uint32_land(v___y_576_, v___x_654_);
v___x_656_ = 0;
v___x_657_ = lean_uint32_dec_eq(v___x_655_, v___x_656_);
if (v___x_657_ == 0)
{
v___y_645_ = v___x_653_;
goto v___jp_644_;
}
else
{
goto v___jp_633_;
}
}
}
v___jp_658_:
{
if (v___y_659_ == 0)
{
goto v___jp_648_;
}
else
{
uint32_t v___x_660_; uint32_t v___x_661_; uint32_t v___x_662_; uint8_t v___x_663_; 
v___x_660_ = 4194304;
v___x_661_ = lean_uint32_land(v___y_577_, v___x_660_);
v___x_662_ = 0;
v___x_663_ = lean_uint32_dec_eq(v___x_661_, v___x_662_);
if (v___x_663_ == 0)
{
goto v___jp_648_;
}
else
{
uint32_t v___x_664_; 
v___x_664_ = lean_uint32_lor(v___y_577_, v___x_660_);
return v___x_664_;
}
}
}
v___jp_665_:
{
uint32_t v___x_666_; uint32_t v___x_667_; uint32_t v___x_668_; uint32_t v___x_669_; uint8_t v___x_670_; 
v___x_666_ = 23;
v___x_667_ = lean_uint32_shift_right(v___y_577_, v___x_666_);
v___x_668_ = 255;
v___x_669_ = lean_uint32_land(v___x_667_, v___x_668_);
v___x_670_ = lean_uint32_dec_eq(v___x_669_, v___x_668_);
if (v___x_670_ == 0)
{
v___y_659_ = v___x_670_;
goto v___jp_658_;
}
else
{
uint32_t v___x_671_; uint32_t v___x_672_; uint32_t v___x_673_; uint8_t v___x_674_; 
v___x_671_ = 8388607;
v___x_672_ = lean_uint32_land(v___y_577_, v___x_671_);
v___x_673_ = 0;
v___x_674_ = lean_uint32_dec_eq(v___x_672_, v___x_673_);
if (v___x_674_ == 0)
{
v___y_659_ = v___x_670_;
goto v___jp_658_;
}
else
{
goto v___jp_648_;
}
}
}
v___jp_675_:
{
if (v___y_676_ == 0)
{
goto v___jp_665_;
}
else
{
uint32_t v___x_677_; uint32_t v___x_678_; uint32_t v___x_679_; uint8_t v___x_680_; 
v___x_677_ = 4194304;
v___x_678_ = lean_uint32_land(v___y_576_, v___x_677_);
v___x_679_ = 0;
v___x_680_ = lean_uint32_dec_eq(v___x_678_, v___x_679_);
if (v___x_680_ == 0)
{
goto v___jp_665_;
}
else
{
uint32_t v___x_681_; 
v___x_681_ = lean_uint32_lor(v___y_576_, v___x_677_);
return v___x_681_;
}
}
}
v___jp_682_:
{
float v_result_685_; uint8_t v___x_686_; 
v_result_685_ = lean_float32_mul(v___y_683_, v___y_684_);
v___x_686_ = lean_float32_beq(v_result_685_, v_result_685_);
if (v___x_686_ == 0)
{
uint32_t v___x_687_; uint32_t v___x_688_; uint32_t v___x_689_; uint32_t v___x_690_; uint8_t v___x_691_; 
v___x_687_ = 23;
v___x_688_ = lean_uint32_shift_right(v___y_576_, v___x_687_);
v___x_689_ = 255;
v___x_690_ = lean_uint32_land(v___x_688_, v___x_689_);
v___x_691_ = lean_uint32_dec_eq(v___x_690_, v___x_689_);
if (v___x_691_ == 0)
{
v___y_676_ = v___x_691_;
goto v___jp_675_;
}
else
{
uint32_t v___x_692_; uint32_t v___x_693_; uint32_t v___x_694_; uint8_t v___x_695_; 
v___x_692_ = 8388607;
v___x_693_ = lean_uint32_land(v___y_576_, v___x_692_);
v___x_694_ = 0;
v___x_695_ = lean_uint32_dec_eq(v___x_693_, v___x_694_);
if (v___x_695_ == 0)
{
v___y_676_ = v___x_691_;
goto v___jp_675_;
}
else
{
goto v___jp_665_;
}
}
}
else
{
uint32_t v___x_696_; 
v___x_696_ = lean_float32_to_bits(v_result_685_);
return v___x_696_;
}
}
v___jp_697_:
{
if (v___y_699_ == 0)
{
float v___x_700_; 
v___x_700_ = lean_float32_of_bits(v___y_577_);
v___y_683_ = v___y_698_;
v___y_684_ = v___x_700_;
goto v___jp_682_;
}
else
{
uint32_t v___x_701_; uint32_t v___x_702_; uint32_t v___x_703_; uint32_t v___x_704_; float v___x_705_; lean_object* v___x_706_; uint32_t v___x_707_; uint32_t v___x_708_; lean_object* v___x_709_; lean_object* v___x_710_; float v___x_711_; float v___x_712_; 
v___x_701_ = 8388607;
v___x_702_ = lean_uint32_land(v___y_577_, v___x_701_);
v___x_703_ = 8388608;
v___x_704_ = lean_uint32_lor(v___x_702_, v___x_703_);
v___x_705_ = lean_uint32_to_float32(v___x_704_);
v___x_706_ = lp_competition_R2W01b_scaleTable;
v___x_707_ = 23;
v___x_708_ = lean_uint32_shift_right(v___y_577_, v___x_707_);
v___x_709_ = lean_uint32_to_nat(v___x_708_);
v___x_710_ = lean_array_fget_borrowed(v___x_706_, v___x_709_);
lean_dec(v___x_709_);
v___x_711_ = lean_unbox_float32(v___x_710_);
v___x_712_ = lean_float32_mul(v___x_705_, v___x_711_);
v___y_683_ = v___y_698_;
v___y_684_ = v___x_712_;
goto v___jp_682_;
}
}
v___jp_713_:
{
uint32_t v___x_715_; uint32_t v_a_716_; uint32_t v___x_717_; uint32_t v___x_718_; uint32_t v___x_719_; uint8_t v___x_720_; 
v___x_715_ = 2147483647;
v_a_716_ = lean_uint32_land(v___y_577_, v___x_715_);
v___x_717_ = 201326591;
v___x_718_ = 1;
v___x_719_ = lean_uint32_sub(v_a_716_, v___x_718_);
v___x_720_ = lean_uint32_dec_le(v___x_717_, v___x_719_);
if (v___x_720_ == 0)
{
v___y_698_ = v___y_714_;
v___y_699_ = v___x_720_;
goto v___jp_697_;
}
else
{
uint32_t v___x_721_; uint8_t v___x_722_; 
v___x_721_ = 2139095040;
v___x_722_ = lean_uint32_dec_lt(v_a_716_, v___x_721_);
v___y_698_ = v___y_714_;
v___y_699_ = v___x_722_;
goto v___jp_697_;
}
}
v___jp_725_:
{
if (v___y_726_ == 0)
{
float v___x_727_; 
v___x_727_ = lean_float32_of_bits(v___y_576_);
v___y_714_ = v___x_727_;
goto v___jp_713_;
}
else
{
uint32_t v___x_728_; uint32_t v___x_729_; uint32_t v___x_730_; uint32_t v___x_731_; float v___x_732_; lean_object* v___x_733_; lean_object* v___x_734_; lean_object* v___x_735_; float v___x_736_; float v___x_737_; 
v___x_728_ = 8388607;
v___x_729_ = lean_uint32_land(v___y_576_, v___x_728_);
v___x_730_ = 8388608;
v___x_731_ = lean_uint32_lor(v___x_729_, v___x_730_);
v___x_732_ = lean_uint32_to_float32(v___x_731_);
v___x_733_ = lp_competition_R2W01b_scaleTable;
v___x_734_ = lean_uint32_to_nat(v___x_724_);
v___x_735_ = lean_array_fget_borrowed(v___x_733_, v___x_734_);
lean_dec(v___x_734_);
v___x_736_ = lean_unbox_float32(v___x_735_);
v___x_737_ = lean_float32_mul(v___x_732_, v___x_736_);
v___y_714_ = v___x_737_;
goto v___jp_713_;
}
}
v___jp_739_:
{
uint32_t v___x_744_; uint32_t v___x_745_; uint32_t v___x_746_; uint32_t v___x_747_; uint32_t v___x_748_; 
v___x_744_ = lean_uint32_land(v___y_740_, v___x_738_);
v___x_745_ = lean_uint32_shift_left(v___x_744_, v___x_723_);
v___x_746_ = lean_uint32_lor(v___y_743_, v___x_745_);
v___x_747_ = lean_uint32_land(v___y_741_, v___y_742_);
v___x_748_ = lean_uint32_lor(v___x_746_, v___x_747_);
return v___x_748_;
}
v___jp_749_:
{
if (v___y_752_ == 0)
{
uint32_t v___x_754_; 
v___x_754_ = 0;
v___y_740_ = v___y_750_;
v___y_741_ = v___y_753_;
v___y_742_ = v___y_751_;
v___y_743_ = v___x_754_;
goto v___jp_739_;
}
else
{
uint32_t v___x_755_; 
v___x_755_ = 2147483648;
v___y_740_ = v___y_750_;
v___y_741_ = v___y_753_;
v___y_742_ = v___y_751_;
v___y_743_ = v___x_755_;
goto v___jp_739_;
}
}
v___jp_756_:
{
uint64_t v___x_762_; uint64_t v_encodedExponent_763_; uint32_t v___x_764_; uint64_t v___x_765_; uint8_t v___x_766_; 
v___x_762_ = 171ULL;
v_encodedExponent_763_ = lean_uint64_sub(v___y_757_, v___x_762_);
v___x_764_ = lean_uint64_to_uint32(v_encodedExponent_763_);
v___x_765_ = 8388608ULL;
v___x_766_ = lean_uint64_dec_lt(v___y_761_, v___x_765_);
if (v___x_766_ == 0)
{
uint64_t v___x_767_; uint32_t v___x_768_; 
v___x_767_ = lean_uint64_sub(v___y_761_, v___x_765_);
v___x_768_ = lean_uint64_to_uint32(v___x_767_);
v___y_750_ = v___x_764_;
v___y_751_ = v___y_759_;
v___y_752_ = v___y_760_;
v___y_753_ = v___x_768_;
goto v___jp_749_;
}
else
{
uint32_t v___x_769_; 
v___x_769_ = lean_uint64_to_uint32(v___y_758_);
v___y_750_ = v___x_764_;
v___y_751_ = v___y_759_;
v___y_752_ = v___y_760_;
v___y_753_ = v___x_769_;
goto v___jp_749_;
}
}
v___jp_770_:
{
uint64_t v___x_777_; uint8_t v___x_778_; 
v___x_777_ = 425ULL;
v___x_778_ = lean_uint64_dec_lt(v___x_777_, v___y_776_);
if (v___x_778_ == 0)
{
if (v___y_771_ == 0)
{
v___y_757_ = v___y_776_;
v___y_758_ = v___y_773_;
v___y_759_ = v___y_774_;
v___y_760_ = v___y_775_;
v___y_761_ = v___y_772_;
goto v___jp_756_;
}
else
{
uint64_t v___x_779_; 
v___x_779_ = 8388608ULL;
v___y_757_ = v___y_776_;
v___y_758_ = v___y_773_;
v___y_759_ = v___y_774_;
v___y_760_ = v___y_775_;
v___y_761_ = v___x_779_;
goto v___jp_756_;
}
}
else
{
if (v___y_775_ == 0)
{
uint32_t v___x_780_; 
v___x_780_ = 2139095040;
return v___x_780_;
}
else
{
uint32_t v___x_781_; 
v___x_781_ = 4286578688;
return v___x_781_;
}
}
}
v___jp_782_:
{
uint64_t v___x_788_; uint8_t v_carry_789_; 
v___x_788_ = 16777216ULL;
v_carry_789_ = lean_uint64_dec_eq(v___y_787_, v___x_788_);
if (v_carry_789_ == 0)
{
v___y_771_ = v_carry_789_;
v___y_772_ = v___y_787_;
v___y_773_ = v___y_783_;
v___y_774_ = v___y_785_;
v___y_775_ = v___y_786_;
v___y_776_ = v___y_784_;
goto v___jp_770_;
}
else
{
uint64_t v___x_790_; uint64_t v___x_791_; 
v___x_790_ = 1ULL;
v___x_791_ = lean_uint64_add(v___y_784_, v___x_790_);
v___y_771_ = v_carry_789_;
v___y_772_ = v___y_787_;
v___y_773_ = v___y_783_;
v___y_774_ = v___y_785_;
v___y_775_ = v___y_786_;
v___y_776_ = v___x_791_;
goto v___jp_770_;
}
}
v___jp_792_:
{
uint64_t v_position_799_; uint64_t v___x_800_; uint8_t v___x_801_; 
v_position_799_ = lean_uint64_add(v___y_798_, v___y_793_);
v___x_800_ = 172ULL;
v___x_801_ = lean_uint64_dec_lt(v_position_799_, v___x_800_);
if (v___x_801_ == 0)
{
uint64_t v___x_802_; uint8_t v___x_803_; 
v___x_802_ = 23ULL;
v___x_803_ = lean_uint64_dec_lt(v___y_798_, v___x_802_);
if (v___x_803_ == 0)
{
uint64_t v___x_804_; uint8_t v___x_805_; 
v___x_804_ = lean_uint64_sub(v___y_798_, v___x_802_);
v___x_805_ = lean_uint64_dec_eq(v___x_804_, v___y_795_);
if (v___x_805_ == 0)
{
uint64_t v___x_806_; uint8_t v___x_807_; 
v___x_806_ = 64ULL;
v___x_807_ = lean_uint64_dec_lt(v___x_804_, v___x_806_);
if (v___x_807_ == 0)
{
uint8_t v___x_808_; 
v___x_808_ = lean_uint64_dec_eq(v___x_804_, v___x_806_);
if (v___x_808_ == 0)
{
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v___y_795_;
goto v___jp_782_;
}
else
{
uint64_t v___x_809_; uint8_t v___x_810_; 
v___x_809_ = 9223372036854775808ULL;
v___x_810_ = lean_uint64_dec_lt(v___x_809_, v___y_794_);
if (v___x_810_ == 0)
{
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v___y_795_;
goto v___jp_782_;
}
else
{
uint64_t v___x_811_; 
v___x_811_ = 1ULL;
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v___x_811_;
goto v___jp_782_;
}
}
}
else
{
uint64_t v_quotient_812_; uint64_t v___x_813_; uint64_t v___x_814_; uint64_t v___x_815_; uint64_t v_remainder_816_; uint64_t v___x_817_; uint64_t v_half_818_; uint8_t v___x_819_; 
v_quotient_812_ = lean_uint64_shift_right(v___y_794_, v___x_804_);
v___x_813_ = 1ULL;
v___x_814_ = lean_uint64_shift_left(v___x_813_, v___x_804_);
v___x_815_ = lean_uint64_sub(v___x_814_, v___x_813_);
v_remainder_816_ = lean_uint64_land(v___y_794_, v___x_815_);
v___x_817_ = lean_uint64_sub(v___x_804_, v___x_813_);
v_half_818_ = lean_uint64_shift_left(v___x_813_, v___x_817_);
v___x_819_ = lean_uint64_dec_lt(v_remainder_816_, v_half_818_);
if (v___x_819_ == 0)
{
uint8_t v___x_820_; 
v___x_820_ = lean_uint64_dec_lt(v_half_818_, v_remainder_816_);
if (v___x_820_ == 0)
{
uint64_t v___x_821_; uint8_t v___x_822_; 
v___x_821_ = lean_uint64_land(v_quotient_812_, v___x_813_);
v___x_822_ = lean_uint64_dec_eq(v___x_821_, v___y_795_);
if (v___x_822_ == 0)
{
uint64_t v___x_823_; 
v___x_823_ = lean_uint64_add(v_quotient_812_, v___x_813_);
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v___x_823_;
goto v___jp_782_;
}
else
{
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v_quotient_812_;
goto v___jp_782_;
}
}
else
{
uint64_t v___x_824_; 
v___x_824_ = lean_uint64_add(v_quotient_812_, v___x_813_);
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v___x_824_;
goto v___jp_782_;
}
}
else
{
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v_quotient_812_;
goto v___jp_782_;
}
}
}
else
{
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v___y_794_;
goto v___jp_782_;
}
}
else
{
uint64_t v___x_825_; uint64_t v___x_826_; 
v___x_825_ = lean_uint64_sub(v___x_802_, v___y_798_);
v___x_826_ = lean_uint64_shift_left(v___y_794_, v___x_825_);
v___y_783_ = v___y_795_;
v___y_784_ = v_position_799_;
v___y_785_ = v___y_796_;
v___y_786_ = v___y_797_;
v___y_787_ = v___x_826_;
goto v___jp_782_;
}
}
else
{
uint64_t v___x_827_; uint8_t v___x_828_; 
v___x_827_ = 149ULL;
v___x_828_ = lean_uint64_dec_lt(v___y_793_, v___x_827_);
if (v___x_828_ == 0)
{
uint64_t v___x_829_; uint64_t v___x_830_; 
v___x_829_ = lean_uint64_sub(v___y_793_, v___x_827_);
v___x_830_ = lean_uint64_shift_left(v___y_794_, v___x_829_);
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v___x_830_;
goto v___jp_592_;
}
else
{
uint64_t v___x_831_; uint8_t v___x_832_; 
v___x_831_ = lean_uint64_sub(v___x_827_, v___y_793_);
v___x_832_ = lean_uint64_dec_eq(v___x_831_, v___y_795_);
if (v___x_832_ == 0)
{
uint64_t v___x_833_; uint8_t v___x_834_; 
v___x_833_ = 64ULL;
v___x_834_ = lean_uint64_dec_lt(v___x_831_, v___x_833_);
if (v___x_834_ == 0)
{
uint8_t v___x_835_; 
v___x_835_ = lean_uint64_dec_eq(v___x_831_, v___x_833_);
if (v___x_835_ == 0)
{
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v___y_795_;
goto v___jp_592_;
}
else
{
uint64_t v___x_836_; uint8_t v___x_837_; 
v___x_836_ = 9223372036854775808ULL;
v___x_837_ = lean_uint64_dec_lt(v___x_836_, v___y_794_);
if (v___x_837_ == 0)
{
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v___y_795_;
goto v___jp_592_;
}
else
{
uint64_t v___x_838_; 
v___x_838_ = 1ULL;
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v___x_838_;
goto v___jp_592_;
}
}
}
else
{
uint64_t v_quotient_839_; uint64_t v___x_840_; uint64_t v___x_841_; uint64_t v___x_842_; uint64_t v_remainder_843_; uint64_t v___x_844_; uint64_t v_half_845_; uint8_t v___x_846_; 
v_quotient_839_ = lean_uint64_shift_right(v___y_794_, v___x_831_);
v___x_840_ = 1ULL;
v___x_841_ = lean_uint64_shift_left(v___x_840_, v___x_831_);
v___x_842_ = lean_uint64_sub(v___x_841_, v___x_840_);
v_remainder_843_ = lean_uint64_land(v___y_794_, v___x_842_);
v___x_844_ = lean_uint64_sub(v___x_831_, v___x_840_);
v_half_845_ = lean_uint64_shift_left(v___x_840_, v___x_844_);
v___x_846_ = lean_uint64_dec_lt(v_remainder_843_, v_half_845_);
if (v___x_846_ == 0)
{
uint8_t v___x_847_; 
v___x_847_ = lean_uint64_dec_lt(v_half_845_, v_remainder_843_);
if (v___x_847_ == 0)
{
uint64_t v___x_848_; uint8_t v___x_849_; 
v___x_848_ = lean_uint64_land(v_quotient_839_, v___x_840_);
v___x_849_ = lean_uint64_dec_eq(v___x_848_, v___y_795_);
if (v___x_849_ == 0)
{
uint64_t v___x_850_; 
v___x_850_ = lean_uint64_add(v_quotient_839_, v___x_840_);
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v___x_850_;
goto v___jp_592_;
}
else
{
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v_quotient_839_;
goto v___jp_592_;
}
}
else
{
uint64_t v___x_851_; 
v___x_851_ = lean_uint64_add(v_quotient_839_, v___x_840_);
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v___x_851_;
goto v___jp_592_;
}
}
else
{
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v_quotient_839_;
goto v___jp_592_;
}
}
}
else
{
v___y_593_ = v___y_795_;
v___y_594_ = v___y_796_;
v___y_595_ = v___y_797_;
v___y_596_ = v___y_794_;
goto v___jp_592_;
}
}
}
}
v___jp_852_:
{
uint64_t v___x_860_; uint64_t v___x_861_; uint8_t v___x_862_; 
v___x_860_ = 1ULL;
v___x_861_ = lean_uint64_shift_right(v___y_853_, v___x_860_);
v___x_862_ = lean_uint64_dec_eq(v___x_861_, v___y_856_);
if (v___x_862_ == 0)
{
uint64_t v___x_863_; 
v___x_863_ = lean_uint64_add(v___y_859_, v___x_860_);
v___y_793_ = v___y_854_;
v___y_794_ = v___y_855_;
v___y_795_ = v___y_856_;
v___y_796_ = v___y_857_;
v___y_797_ = v___y_858_;
v___y_798_ = v___x_863_;
goto v___jp_792_;
}
else
{
v___y_793_ = v___y_854_;
v___y_794_ = v___y_855_;
v___y_795_ = v___y_856_;
v___y_796_ = v___y_857_;
v___y_797_ = v___y_858_;
v___y_798_ = v___y_859_;
goto v___jp_792_;
}
}
v___jp_864_:
{
uint64_t v___x_874_; uint8_t v___x_875_; 
v___x_874_ = lean_uint64_shift_right(v___y_870_, v___y_866_);
v___x_875_ = lean_uint64_dec_eq(v___x_874_, v___y_867_);
if (v___x_875_ == 0)
{
uint64_t v___x_876_; 
v___x_876_ = lean_uint64_add(v___y_869_, v___y_866_);
v___y_853_ = v___y_873_;
v___y_854_ = v___y_865_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_867_;
v___y_857_ = v___y_871_;
v___y_858_ = v___y_872_;
v___y_859_ = v___x_876_;
goto v___jp_852_;
}
else
{
v___y_853_ = v___y_873_;
v___y_854_ = v___y_865_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_867_;
v___y_857_ = v___y_871_;
v___y_858_ = v___y_872_;
v___y_859_ = v___y_869_;
goto v___jp_852_;
}
}
v___jp_877_:
{
uint64_t v___x_885_; uint64_t v___x_886_; uint8_t v___x_887_; 
v___x_885_ = 2ULL;
v___x_886_ = lean_uint64_shift_right(v___y_881_, v___x_885_);
v___x_887_ = lean_uint64_dec_eq(v___x_886_, v___y_880_);
if (v___x_887_ == 0)
{
v___y_865_ = v___y_878_;
v___y_866_ = v___x_885_;
v___y_867_ = v___y_880_;
v___y_868_ = v___y_879_;
v___y_869_ = v___y_884_;
v___y_870_ = v___y_881_;
v___y_871_ = v___y_882_;
v___y_872_ = v___y_883_;
v___y_873_ = v___x_886_;
goto v___jp_864_;
}
else
{
v___y_865_ = v___y_878_;
v___y_866_ = v___x_885_;
v___y_867_ = v___y_880_;
v___y_868_ = v___y_879_;
v___y_869_ = v___y_884_;
v___y_870_ = v___y_881_;
v___y_871_ = v___y_882_;
v___y_872_ = v___y_883_;
v___y_873_ = v___y_881_;
goto v___jp_864_;
}
}
v___jp_888_:
{
uint64_t v___x_898_; uint8_t v___x_899_; 
v___x_898_ = lean_uint64_shift_right(v___y_889_, v___y_891_);
v___x_899_ = lean_uint64_dec_eq(v___x_898_, v___y_892_);
if (v___x_899_ == 0)
{
uint64_t v___x_900_; 
v___x_900_ = lean_uint64_add(v___y_894_, v___y_891_);
v___y_878_ = v___y_890_;
v___y_879_ = v___y_893_;
v___y_880_ = v___y_892_;
v___y_881_ = v___y_897_;
v___y_882_ = v___y_895_;
v___y_883_ = v___y_896_;
v___y_884_ = v___x_900_;
goto v___jp_877_;
}
else
{
v___y_878_ = v___y_890_;
v___y_879_ = v___y_893_;
v___y_880_ = v___y_892_;
v___y_881_ = v___y_897_;
v___y_882_ = v___y_895_;
v___y_883_ = v___y_896_;
v___y_884_ = v___y_894_;
goto v___jp_877_;
}
}
v___jp_901_:
{
uint64_t v___x_909_; uint64_t v___x_910_; uint8_t v___x_911_; 
v___x_909_ = 4ULL;
v___x_910_ = lean_uint64_shift_right(v___y_902_, v___x_909_);
v___x_911_ = lean_uint64_dec_eq(v___x_910_, v___y_905_);
if (v___x_911_ == 0)
{
v___y_889_ = v___y_902_;
v___y_890_ = v___y_903_;
v___y_891_ = v___x_909_;
v___y_892_ = v___y_905_;
v___y_893_ = v___y_904_;
v___y_894_ = v___y_908_;
v___y_895_ = v___y_906_;
v___y_896_ = v___y_907_;
v___y_897_ = v___x_910_;
goto v___jp_888_;
}
else
{
v___y_889_ = v___y_902_;
v___y_890_ = v___y_903_;
v___y_891_ = v___x_909_;
v___y_892_ = v___y_905_;
v___y_893_ = v___y_904_;
v___y_894_ = v___y_908_;
v___y_895_ = v___y_906_;
v___y_896_ = v___y_907_;
v___y_897_ = v___y_902_;
goto v___jp_888_;
}
}
v___jp_912_:
{
uint64_t v___x_922_; uint8_t v___x_923_; 
v___x_922_ = lean_uint64_shift_right(v___y_920_, v___y_914_);
v___x_923_ = lean_uint64_dec_eq(v___x_922_, v___y_915_);
if (v___x_923_ == 0)
{
uint64_t v___x_924_; 
v___x_924_ = lean_uint64_add(v___y_918_, v___y_914_);
v___y_902_ = v___y_921_;
v___y_903_ = v___y_913_;
v___y_904_ = v___y_916_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_917_;
v___y_907_ = v___y_919_;
v___y_908_ = v___x_924_;
goto v___jp_901_;
}
else
{
v___y_902_ = v___y_921_;
v___y_903_ = v___y_913_;
v___y_904_ = v___y_916_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_917_;
v___y_907_ = v___y_919_;
v___y_908_ = v___y_918_;
goto v___jp_901_;
}
}
v___jp_925_:
{
uint64_t v___x_933_; uint64_t v___x_934_; uint8_t v___x_935_; 
v___x_933_ = 8ULL;
v___x_934_ = lean_uint64_shift_right(v___y_931_, v___x_933_);
v___x_935_ = lean_uint64_dec_eq(v___x_934_, v___y_928_);
if (v___x_935_ == 0)
{
v___y_913_ = v___y_926_;
v___y_914_ = v___x_933_;
v___y_915_ = v___y_928_;
v___y_916_ = v___y_927_;
v___y_917_ = v___y_929_;
v___y_918_ = v___y_932_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___x_934_;
goto v___jp_912_;
}
else
{
v___y_913_ = v___y_926_;
v___y_914_ = v___x_933_;
v___y_915_ = v___y_928_;
v___y_916_ = v___y_927_;
v___y_917_ = v___y_929_;
v___y_918_ = v___y_932_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___y_931_;
goto v___jp_912_;
}
}
v___jp_936_:
{
uint64_t v___x_946_; uint8_t v___x_947_; 
v___x_946_ = lean_uint64_shift_right(v___y_938_, v___y_944_);
v___x_947_ = lean_uint64_dec_eq(v___x_946_, v___y_940_);
if (v___x_947_ == 0)
{
uint64_t v___x_948_; 
v___x_948_ = lean_uint64_add(v___y_939_, v___y_944_);
v___y_926_ = v___y_937_;
v___y_927_ = v___y_941_;
v___y_928_ = v___y_940_;
v___y_929_ = v___y_942_;
v___y_930_ = v___y_943_;
v___y_931_ = v___y_945_;
v___y_932_ = v___x_948_;
goto v___jp_925_;
}
else
{
v___y_926_ = v___y_937_;
v___y_927_ = v___y_941_;
v___y_928_ = v___y_940_;
v___y_929_ = v___y_942_;
v___y_930_ = v___y_943_;
v___y_931_ = v___y_945_;
v___y_932_ = v___y_939_;
goto v___jp_925_;
}
}
v___jp_949_:
{
uint64_t v___x_957_; uint64_t v___x_958_; uint8_t v___x_959_; 
v___x_957_ = 16ULL;
v___x_958_ = lean_uint64_shift_right(v___y_951_, v___x_957_);
v___x_959_ = lean_uint64_dec_eq(v___x_958_, v___y_953_);
if (v___x_959_ == 0)
{
v___y_937_ = v___y_950_;
v___y_938_ = v___y_951_;
v___y_939_ = v___y_956_;
v___y_940_ = v___y_953_;
v___y_941_ = v___y_952_;
v___y_942_ = v___y_954_;
v___y_943_ = v___y_955_;
v___y_944_ = v___x_957_;
v___y_945_ = v___x_958_;
goto v___jp_936_;
}
else
{
v___y_937_ = v___y_950_;
v___y_938_ = v___y_951_;
v___y_939_ = v___y_956_;
v___y_940_ = v___y_953_;
v___y_941_ = v___y_952_;
v___y_942_ = v___y_954_;
v___y_943_ = v___y_955_;
v___y_944_ = v___x_957_;
v___y_945_ = v___y_951_;
goto v___jp_936_;
}
}
v___jp_960_:
{
uint64_t v___x_968_; uint8_t v___x_969_; 
v___x_968_ = lean_uint64_shift_right(v___y_963_, v___y_964_);
v___x_969_ = lean_uint64_dec_eq(v___x_968_, v___y_962_);
if (v___x_969_ == 0)
{
v___y_950_ = v___y_961_;
v___y_951_ = v___y_967_;
v___y_952_ = v___y_963_;
v___y_953_ = v___y_962_;
v___y_954_ = v___y_965_;
v___y_955_ = v___y_966_;
v___y_956_ = v___y_964_;
goto v___jp_949_;
}
else
{
v___y_950_ = v___y_961_;
v___y_951_ = v___y_967_;
v___y_952_ = v___y_963_;
v___y_953_ = v___y_962_;
v___y_954_ = v___y_965_;
v___y_955_ = v___y_966_;
v___y_956_ = v___y_962_;
goto v___jp_949_;
}
}
v___jp_970_:
{
uint64_t v___x_975_; uint8_t v___x_976_; 
v___x_975_ = 0ULL;
v___x_976_ = lean_uint64_dec_eq(v___y_972_, v___x_975_);
if (v___x_976_ == 0)
{
uint64_t v___x_977_; uint64_t v___x_978_; uint8_t v___x_979_; 
v___x_977_ = 32ULL;
v___x_978_ = lean_uint64_shift_right(v___y_972_, v___x_977_);
v___x_979_ = lean_uint64_dec_eq(v___x_978_, v___x_975_);
if (v___x_979_ == 0)
{
v___y_961_ = v___y_971_;
v___y_962_ = v___x_975_;
v___y_963_ = v___y_972_;
v___y_964_ = v___x_977_;
v___y_965_ = v___y_973_;
v___y_966_ = v___y_974_;
v___y_967_ = v___x_978_;
goto v___jp_960_;
}
else
{
v___y_961_ = v___y_971_;
v___y_962_ = v___x_975_;
v___y_963_ = v___y_972_;
v___y_964_ = v___x_977_;
v___y_965_ = v___y_973_;
v___y_966_ = v___y_974_;
v___y_967_ = v___y_972_;
goto v___jp_960_;
}
}
else
{
if (v___y_974_ == 0)
{
uint32_t v___x_980_; 
v___x_980_ = 0;
return v___x_980_;
}
else
{
uint32_t v___x_981_; 
v___x_981_ = 2147483648;
return v___x_981_;
}
}
}
v___jp_982_:
{
uint64_t v___x_989_; uint64_t v___x_990_; uint64_t v___x_991_; uint8_t v___x_992_; 
v___x_989_ = lean_uint64_mul(v___y_984_, v___y_987_);
v___x_990_ = lean_uint64_add(v___y_983_, v___y_988_);
v___x_991_ = 281474976710656ULL;
v___x_992_ = lean_uint64_dec_lt(v___x_989_, v___x_991_);
if (v___x_992_ == 0)
{
v___y_971_ = v___x_990_;
v___y_972_ = v___x_989_;
v___y_973_ = v___y_985_;
v___y_974_ = v___y_986_;
goto v___jp_970_;
}
else
{
uint64_t v___x_993_; uint8_t v___x_994_; 
v___x_993_ = 123ULL;
v___x_994_ = lean_uint64_dec_le(v___x_990_, v___x_993_);
if (v___x_994_ == 0)
{
v___y_971_ = v___x_990_;
v___y_972_ = v___x_989_;
v___y_973_ = v___y_985_;
v___y_974_ = v___y_986_;
goto v___jp_970_;
}
else
{
uint64_t v___x_995_; uint8_t v___x_996_; 
v___x_995_ = 0ULL;
v___x_996_ = lean_uint64_dec_eq(v___x_989_, v___x_995_);
if (v___x_996_ == 0)
{
uint64_t v___x_997_; uint64_t v___x_998_; uint8_t v___x_999_; 
v___x_997_ = 149ULL;
v___x_998_ = lean_uint64_sub(v___x_997_, v___x_990_);
v___x_999_ = lean_uint64_dec_eq(v___x_998_, v___x_995_);
if (v___x_999_ == 0)
{
uint64_t v___x_1000_; uint8_t v___x_1001_; 
v___x_1000_ = 64ULL;
v___x_1001_ = lean_uint64_dec_lt(v___x_998_, v___x_1000_);
if (v___x_1001_ == 0)
{
uint8_t v___x_1002_; 
v___x_1002_ = lean_uint64_dec_eq(v___x_998_, v___x_1000_);
if (v___x_1002_ == 0)
{
v___y_614_ = v___x_995_;
v___y_615_ = v___y_985_;
v___y_616_ = v___y_986_;
v___y_617_ = v___x_995_;
goto v___jp_613_;
}
else
{
uint64_t v___x_1003_; uint8_t v___x_1004_; 
v___x_1003_ = 9223372036854775808ULL;
v___x_1004_ = lean_uint64_dec_lt(v___x_1003_, v___x_989_);
if (v___x_1004_ == 0)
{
v___y_614_ = v___x_995_;
v___y_615_ = v___y_985_;
v___y_616_ = v___y_986_;
v___y_617_ = v___x_995_;
goto v___jp_613_;
}
else
{
uint64_t v___x_1005_; 
v___x_1005_ = 1ULL;
v___y_614_ = v___x_995_;
v___y_615_ = v___y_985_;
v___y_616_ = v___y_986_;
v___y_617_ = v___x_1005_;
goto v___jp_613_;
}
}
}
else
{
uint64_t v_quotient_1006_; uint64_t v___x_1007_; uint64_t v___x_1008_; uint64_t v___x_1009_; uint64_t v_remainder_1010_; uint64_t v___x_1011_; uint64_t v_half_1012_; uint8_t v___x_1013_; 
v_quotient_1006_ = lean_uint64_shift_right(v___x_989_, v___x_998_);
v___x_1007_ = 1ULL;
v___x_1008_ = lean_uint64_shift_left(v___x_1007_, v___x_998_);
v___x_1009_ = lean_uint64_sub(v___x_1008_, v___x_1007_);
v_remainder_1010_ = lean_uint64_land(v___x_989_, v___x_1009_);
v___x_1011_ = lean_uint64_sub(v___x_998_, v___x_1007_);
v_half_1012_ = lean_uint64_shift_left(v___x_1007_, v___x_1011_);
v___x_1013_ = lean_uint64_dec_lt(v_remainder_1010_, v_half_1012_);
if (v___x_1013_ == 0)
{
uint8_t v___x_1014_; 
v___x_1014_ = lean_uint64_dec_lt(v_half_1012_, v_remainder_1010_);
if (v___x_1014_ == 0)
{
uint64_t v___x_1015_; uint8_t v___x_1016_; 
v___x_1015_ = lean_uint64_land(v_quotient_1006_, v___x_1007_);
v___x_1016_ = lean_uint64_dec_eq(v___x_1015_, v___x_995_);
if (v___x_1016_ == 0)
{
uint64_t v___x_1017_; 
v___x_1017_ = lean_uint64_add(v_quotient_1006_, v___x_1007_);
v___y_614_ = v___x_995_;
v___y_615_ = v___y_985_;
v___y_616_ = v___y_986_;
v___y_617_ = v___x_1017_;
goto v___jp_613_;
}
else
{
v___y_614_ = v___x_995_;
v___y_615_ = v___y_985_;
v___y_616_ = v___y_986_;
v___y_617_ = v_quotient_1006_;
goto v___jp_613_;
}
}
else
{
uint64_t v___x_1018_; 
v___x_1018_ = lean_uint64_add(v_quotient_1006_, v___x_1007_);
v___y_614_ = v___x_995_;
v___y_615_ = v___y_985_;
v___y_616_ = v___y_986_;
v___y_617_ = v___x_1018_;
goto v___jp_613_;
}
}
else
{
v___y_614_ = v___x_995_;
v___y_615_ = v___y_985_;
v___y_616_ = v___y_986_;
v___y_617_ = v_quotient_1006_;
goto v___jp_613_;
}
}
}
else
{
v___y_614_ = v___x_995_;
v___y_615_ = v___y_985_;
v___y_616_ = v___y_986_;
v___y_617_ = v___x_989_;
goto v___jp_613_;
}
}
else
{
if (v___y_986_ == 0)
{
uint32_t v___x_1019_; 
v___x_1019_ = 0;
return v___x_1019_;
}
else
{
uint32_t v___x_1020_; 
v___x_1020_ = 2147483648;
return v___x_1020_;
}
}
}
}
}
v___jp_1024_:
{
uint64_t v___x_1030_; uint64_t v___x_1031_; uint8_t v___x_1032_; 
v___x_1030_ = lean_uint32_to_uint64(v_ey_1023_);
v___x_1031_ = 0ULL;
v___x_1032_ = lean_uint64_dec_eq(v___x_1030_, v___x_1031_);
if (v___x_1032_ == 0)
{
uint64_t v___x_1033_; uint64_t v___x_1034_; 
v___x_1033_ = 1ULL;
v___x_1034_ = lean_uint64_sub(v___x_1030_, v___x_1033_);
v___y_983_ = v___y_1029_;
v___y_984_ = v___y_1025_;
v___y_985_ = v___y_1026_;
v___y_986_ = v___y_1027_;
v___y_987_ = v___y_1028_;
v___y_988_ = v___x_1034_;
goto v___jp_982_;
}
else
{
v___y_983_ = v___y_1029_;
v___y_984_ = v___y_1025_;
v___y_985_ = v___y_1026_;
v___y_986_ = v___y_1027_;
v___y_987_ = v___y_1028_;
v___y_988_ = v___x_1031_;
goto v___jp_982_;
}
}
v___jp_1035_:
{
uint64_t v___x_1040_; uint64_t v___x_1041_; uint8_t v___x_1042_; 
v___x_1040_ = lean_uint32_to_uint64(v_ex_1021_);
v___x_1041_ = 0ULL;
v___x_1042_ = lean_uint64_dec_eq(v___x_1040_, v___x_1041_);
if (v___x_1042_ == 0)
{
uint64_t v___x_1043_; uint64_t v___x_1044_; 
v___x_1043_ = 1ULL;
v___x_1044_ = lean_uint64_sub(v___x_1040_, v___x_1043_);
v___y_1025_ = v___y_1036_;
v___y_1026_ = v___y_1037_;
v___y_1027_ = v___y_1038_;
v___y_1028_ = v___y_1039_;
v___y_1029_ = v___x_1044_;
goto v___jp_1024_;
}
else
{
v___y_1025_ = v___y_1036_;
v___y_1026_ = v___y_1037_;
v___y_1027_ = v___y_1038_;
v___y_1028_ = v___y_1039_;
v___y_1029_ = v___x_1041_;
goto v___jp_1024_;
}
}
v___jp_1045_:
{
uint32_t v___x_1050_; uint8_t v___x_1051_; 
v___x_1050_ = 0;
v___x_1051_ = lean_uint32_dec_eq(v_ey_1023_, v___x_1050_);
if (v___x_1051_ == 0)
{
uint64_t v___x_1052_; uint64_t v___x_1053_; uint64_t v___x_1054_; 
v___x_1052_ = lean_uint32_to_uint64(v___y_1046_);
v___x_1053_ = 8388608ULL;
v___x_1054_ = lean_uint64_lor(v___x_1052_, v___x_1053_);
v___y_1036_ = v___y_1049_;
v___y_1037_ = v___y_1047_;
v___y_1038_ = v___y_1048_;
v___y_1039_ = v___x_1054_;
goto v___jp_1035_;
}
else
{
uint64_t v___x_1055_; 
v___x_1055_ = lean_uint32_to_uint64(v___y_1046_);
v___y_1036_ = v___y_1049_;
v___y_1037_ = v___y_1047_;
v___y_1038_ = v___y_1048_;
v___y_1039_ = v___x_1055_;
goto v___jp_1035_;
}
}
v___jp_1056_:
{
uint32_t v___x_1058_; uint32_t v_xFraction_1059_; uint32_t v_yFraction_1060_; uint32_t v___x_1061_; uint8_t v___x_1062_; 
v___x_1058_ = 8388607;
v_xFraction_1059_ = lean_uint32_land(v___y_576_, v___x_1058_);
v_yFraction_1060_ = lean_uint32_land(v___y_577_, v___x_1058_);
v___x_1061_ = 0;
v___x_1062_ = lean_uint32_dec_eq(v_ex_1021_, v___x_1061_);
if (v___x_1062_ == 0)
{
uint64_t v___x_1063_; uint64_t v___x_1064_; uint64_t v___x_1065_; 
v___x_1063_ = lean_uint32_to_uint64(v_xFraction_1059_);
v___x_1064_ = 8388608ULL;
v___x_1065_ = lean_uint64_lor(v___x_1063_, v___x_1064_);
v___y_1046_ = v_yFraction_1060_;
v___y_1047_ = v___x_1058_;
v___y_1048_ = v___y_1057_;
v___y_1049_ = v___x_1065_;
goto v___jp_1045_;
}
else
{
uint64_t v___x_1066_; 
v___x_1066_ = lean_uint32_to_uint64(v_xFraction_1059_);
v___y_1046_ = v_yFraction_1060_;
v___y_1047_ = v___x_1058_;
v___y_1048_ = v___y_1057_;
v___y_1049_ = v___x_1066_;
goto v___jp_1045_;
}
}
v___jp_1070_:
{
if (v___y_1072_ == 0)
{
v___y_1057_ = v___x_1069_;
goto v___jp_1056_;
}
else
{
v___y_1057_ = v___y_1071_;
goto v___jp_1056_;
}
}
v___jp_1073_:
{
if (v___y_1075_ == 0)
{
if (v___y_1076_ == 0)
{
v___y_1071_ = v___y_1074_;
v___y_1072_ = v___x_1069_;
goto v___jp_1070_;
}
else
{
v___y_1057_ = v___x_1069_;
goto v___jp_1056_;
}
}
else
{
v___y_1071_ = v___y_1074_;
v___y_1072_ = v___y_1076_;
goto v___jp_1070_;
}
}
v___jp_1077_:
{
uint32_t v___x_1080_; uint32_t v___x_1081_; uint32_t v___x_1082_; uint8_t v___x_1083_; 
v___x_1080_ = 2147483648;
v___x_1081_ = lean_uint32_land(v___y_577_, v___x_1080_);
v___x_1082_ = 0;
v___x_1083_ = lean_uint32_dec_eq(v___x_1081_, v___x_1082_);
if (v___x_1083_ == 0)
{
v___y_1074_ = v___y_1078_;
v___y_1075_ = v___y_1079_;
v___y_1076_ = v___x_1069_;
goto v___jp_1073_;
}
else
{
v___y_1074_ = v___y_1078_;
v___y_1075_ = v___y_1079_;
v___y_1076_ = v___y_1078_;
goto v___jp_1073_;
}
}
v___jp_1084_:
{
if (v___y_1085_ == 0)
{
uint32_t v___x_1086_; uint32_t v___x_1087_; uint32_t v___x_1088_; uint8_t v___x_1089_; 
v___x_1086_ = 2147483648;
v___x_1087_ = lean_uint32_land(v___y_576_, v___x_1086_);
v___x_1088_ = 0;
v___x_1089_ = lean_uint32_dec_eq(v___x_1087_, v___x_1088_);
if (v___x_1089_ == 0)
{
v___y_1078_ = v___y_1085_;
v___y_1079_ = v___x_1069_;
goto v___jp_1077_;
}
else
{
v___y_1078_ = v___y_1085_;
v___y_1079_ = v___y_1085_;
goto v___jp_1077_;
}
}
else
{
lean_object* v___x_1090_; lean_object* v___x_1091_; lean_object* v___x_1092_; uint32_t v___x_1093_; 
v___x_1090_ = lean_uint32_to_nat(v___y_576_);
v___x_1091_ = lean_uint32_to_nat(v___y_577_);
v___x_1092_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1090_, v___x_1091_);
v___x_1093_ = lean_uint32_of_nat(v___x_1092_);
lean_dec(v___x_1092_);
return v___x_1093_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_1108_, lean_object* v___y_1109_){
_start:
{
uint32_t v___y_1921__boxed_1110_; uint32_t v___y_1922__boxed_1111_; uint32_t v_res_1112_; lean_object* v_r_1113_; 
v___y_1921__boxed_1110_ = lean_unbox_uint32(v___y_1108_);
lean_dec(v___y_1108_);
v___y_1922__boxed_1111_ = lean_unbox_uint32(v___y_1109_);
lean_dec(v___y_1109_);
v_res_1112_ = lp_competition_main___lam__0(v___y_1921__boxed_1110_, v___y_1922__boxed_1111_);
v_r_1113_ = lean_box_uint32(v_res_1112_);
return v_r_1113_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1130_; lean_object* v___x_1131_; lean_object* v___f_1132_; lean_object* v_add_1134_; lean_object* v___x_1138_; uint8_t v___x_1139_; 
v___x_1130_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1131_ = lean_io_getenv(v___x_1130_);
v___f_1132_ = ((lean_object*)(lp_competition_main___closed__1));
v___x_1138_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1139_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1131_, v___x_1138_);
if (v___x_1139_ == 0)
{
lean_object* v___x_1140_; uint8_t v___x_1141_; 
v___x_1140_ = ((lean_object*)(lp_competition_main___closed__7));
v___x_1141_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1131_, v___x_1140_);
lean_dec(v___x_1131_);
if (v___x_1141_ == 0)
{
lean_object* v___x_1142_; lean_object* v___x_1143_; 
v___x_1142_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_1143_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1143_, 0, v___x_1142_);
return v___x_1143_;
}
else
{
lean_object* v___x_1144_; 
v___x_1144_ = ((lean_object*)(lp_competition_main___closed__10));
v_add_1134_ = v___x_1144_;
goto v___jp_1133_;
}
}
else
{
lean_object* v___x_1145_; 
lean_dec(v___x_1131_);
v___x_1145_ = ((lean_object*)(lp_competition_main___closed__11));
v_add_1134_ = v___x_1145_;
goto v___jp_1133_;
}
v___jp_1133_:
{
lean_object* v___x_1135_; lean_object* v___x_1136_; lean_object* v___x_1137_; 
v___x_1135_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1136_ = ((lean_object*)(lp_competition_main___closed__3));
lean_inc_ref(v_add_1134_);
v___x_1137_ = lp_competition_Bench_Suite_run(v_add_1134_, v___f_1132_, v___x_1135_, v___x_1136_);
return v___x_1137_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1146_){
_start:
{
lean_object* v_res_1147_; 
v_res_1147_ = _lean_main();
return v_res_1147_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R19AddCostMain(uint8_t builtin) {
lean_object * res;
if (_G_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_initialized = true;
lean_initialize();
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_competition_BenchFull(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_competition_BenchSuite(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_competition_Submission(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return lean_io_result_mk_ok(lean_box(0));
}
char ** lean_setup_args(int argc, char ** argv);
#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif
lean_object* run_main(int argc, char ** argv) {
    return _lean_main();
}
int main(int argc, char ** argv) {
#if defined(WIN32) || defined(_WIN32)
  SetErrorMode(SEM_FAILCRITICALERRORS);
  SetConsoleOutputCP(CP_UTF8);
#endif
  lean_object* res;
  argv = lean_setup_args(argc, argv);
  res = initialize_competition_R19AddCostMain(1 /* builtin */);
  lean_io_mark_end_initialization();
  if (lean_io_result_is_ok(res)) {
    lean_dec_ref(res);
    lean_init_task_manager();
    res = lean_run_main(&run_main, argc, argv);
  }
  lean_finalize_task_manager();
  if (lean_io_result_is_ok(res)) {
    int ret = lean_unbox_uint32(lean_io_result_get_value(res));
    lean_dec_ref(res);
    return ret;
  } else {
    lean_io_result_show_error(res);
    lean_dec_ref(res);
    return 1;
  }
}
#ifdef __cplusplus
}
#endif
