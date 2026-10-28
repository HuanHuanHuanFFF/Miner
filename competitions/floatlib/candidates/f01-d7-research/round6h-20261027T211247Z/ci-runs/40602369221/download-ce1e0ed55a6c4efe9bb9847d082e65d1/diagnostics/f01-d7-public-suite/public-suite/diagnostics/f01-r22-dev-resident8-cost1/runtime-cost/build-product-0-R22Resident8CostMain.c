// Lean compiler output
// Module: R22Resident8CostMain
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
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
float lean_float32_add(float, float);
uint8_t lean_float32_beq(float, float);
uint32_t lean_float32_to_bits(float);
float lean_float32_of_bits(uint32_t);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
float lean_float32_mul(float, float);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
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
lean_object* lp_competition_Submission_R22Resident8_guarded(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Submission_R22Pair8_guarded(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__4(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__4___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "pair8"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "resident8"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_string_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 22, .m_capacity = 22, .m_length = 21, .m_data = "Unknown BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_ctor_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__7_value)}};
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_closure_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
static const lean_closure_object lp_competition_main___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__10 = (const lean_object*)&lp_competition_main___closed__10_value;
static const lean_closure_object lp_competition_main___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_R22Resident8_guarded, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__11 = (const lean_object*)&lp_competition_main___closed__11_value;
static const lean_closure_object lp_competition_main___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_R22Pair8_guarded, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__12 = (const lean_object*)&lp_competition_main___closed__12_value;
static const lean_closure_object lp_competition_main___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__13 = (const lean_object*)&lp_competition_main___closed__13_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
uint8_t v___y_9_; uint8_t v___y_23_; uint8_t v___y_37_; uint8_t v___y_54_; float v___y_61_; float v___y_62_; float v___y_76_; uint8_t v___y_77_; float v___y_92_; uint8_t v___y_102_; uint32_t v___x_116_; uint32_t v_a_117_; uint32_t v___x_118_; uint32_t v___x_119_; uint32_t v___x_120_; uint8_t v___x_121_; 
v___x_116_ = 2147483647;
v_a_117_ = lean_uint32_land(v___y_1_, v___x_116_);
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
float v_result_63_; uint8_t v___x_64_; 
v_result_63_ = lean_float32_add(v___y_61_, v___y_62_);
v___x_64_ = lean_float32_beq(v_result_63_, v_result_63_);
if (v___x_64_ == 0)
{
uint32_t v___x_65_; uint32_t v___x_66_; uint32_t v___x_67_; uint32_t v___x_68_; uint8_t v___x_69_; 
v___x_65_ = 23;
v___x_66_ = lean_uint32_shift_right(v___y_1_, v___x_65_);
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
v___x_71_ = lean_uint32_land(v___y_1_, v___x_70_);
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
v___x_78_ = lean_float32_of_bits(v___y_2_);
v___y_61_ = v___y_76_;
v___y_62_ = v___x_78_;
goto v___jp_60_;
}
else
{
uint32_t v___x_79_; uint32_t v___x_80_; uint32_t v___x_81_; uint32_t v___x_82_; float v___x_83_; lean_object* v___x_84_; uint32_t v___x_85_; uint32_t v___x_86_; lean_object* v___x_87_; lean_object* v___x_88_; float v___x_89_; float v___x_90_; 
v___x_79_ = 8388607;
v___x_80_ = lean_uint32_land(v___y_2_, v___x_79_);
v___x_81_ = 8388608;
v___x_82_ = lean_uint32_lor(v___x_80_, v___x_81_);
v___x_83_ = lean_uint32_to_float32(v___x_82_);
v___x_84_ = lp_competition_R2W01b_scaleTable;
v___x_85_ = 23;
v___x_86_ = lean_uint32_shift_right(v___y_2_, v___x_85_);
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
v_a_94_ = lean_uint32_land(v___y_2_, v___x_93_);
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
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_124_, lean_object* v___y_125_){
_start:
{
uint32_t v___y_7242__boxed_126_; uint32_t v___y_7243__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_7242__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_7243__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_main___lam__0(v___y_7242__boxed_126_, v___y_7243__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint8_t v___x_130_, uint32_t v___y_131_, uint32_t v___y_132_){
_start:
{
uint8_t v___y_134_; uint8_t v___y_150_; uint8_t v___y_164_; uint8_t v___y_181_; float v___y_188_; float v___y_189_; float v___y_203_; uint8_t v___y_204_; float v___y_219_; uint32_t v___y_229_; uint32_t v___y_233_; uint32_t v___y_237_; uint32_t v___y_238_; uint32_t v___y_239_; uint64_t v___y_243_; uint32_t v___y_244_; uint8_t v___y_245_; uint64_t v___y_246_; uint32_t v___y_258_; uint32_t v___y_259_; uint32_t v___y_260_; uint32_t v___y_264_; uint64_t v___y_265_; uint8_t v___y_266_; uint64_t v___y_267_; uint32_t v___x_278_; uint32_t v___x_279_; uint8_t v___y_281_; uint32_t v___x_293_; uint32_t v___y_295_; uint32_t v___y_296_; uint32_t v___y_297_; uint32_t v___y_298_; uint32_t v___y_305_; uint32_t v___y_306_; uint8_t v___y_307_; uint32_t v___y_308_; uint64_t v___y_312_; uint64_t v___y_313_; uint32_t v___y_314_; uint8_t v___y_315_; uint64_t v___y_316_; uint64_t v___y_326_; uint8_t v___y_327_; uint64_t v___y_328_; uint32_t v___y_329_; uint8_t v___y_330_; uint64_t v___y_331_; uint64_t v___y_338_; uint32_t v___y_339_; uint64_t v___y_340_; uint8_t v___y_341_; uint64_t v___y_342_; uint64_t v___y_348_; uint64_t v___y_349_; uint64_t v___y_350_; uint32_t v___y_351_; uint8_t v___y_352_; uint64_t v___y_353_; uint64_t v___y_408_; uint64_t v___y_409_; uint64_t v___y_410_; uint64_t v___y_411_; uint32_t v___y_412_; uint8_t v___y_413_; uint64_t v___y_414_; uint64_t v___y_420_; uint64_t v___y_421_; uint64_t v___y_422_; uint64_t v___y_423_; uint64_t v___y_424_; uint64_t v___y_425_; uint32_t v___y_426_; uint8_t v___y_427_; uint64_t v___y_428_; uint64_t v___y_433_; uint64_t v___y_434_; uint64_t v___y_435_; uint64_t v___y_436_; uint32_t v___y_437_; uint8_t v___y_438_; uint64_t v___y_439_; uint64_t v___y_444_; uint64_t v___y_445_; uint64_t v___y_446_; uint64_t v___y_447_; uint64_t v___y_448_; uint32_t v___y_449_; uint8_t v___y_450_; uint64_t v___y_451_; uint64_t v___y_452_; uint64_t v___y_457_; uint64_t v___y_458_; uint64_t v___y_459_; uint32_t v___y_460_; uint8_t v___y_461_; uint64_t v___y_462_; uint64_t v___y_463_; uint64_t v___y_468_; uint64_t v___y_469_; uint64_t v___y_470_; uint64_t v___y_471_; uint64_t v___y_472_; uint32_t v___y_473_; uint64_t v___y_474_; uint8_t v___y_475_; uint64_t v___y_476_; uint64_t v___y_481_; uint64_t v___y_482_; uint64_t v___y_483_; uint64_t v___y_484_; uint32_t v___y_485_; uint8_t v___y_486_; uint64_t v___y_487_; uint64_t v___y_492_; uint64_t v___y_493_; uint64_t v___y_494_; uint64_t v___y_495_; uint64_t v___y_496_; uint64_t v___y_497_; uint32_t v___y_498_; uint8_t v___y_499_; uint64_t v___y_500_; uint64_t v___y_505_; uint64_t v___y_506_; uint64_t v___y_507_; uint64_t v___y_508_; uint32_t v___y_509_; uint8_t v___y_510_; uint64_t v___y_511_; uint64_t v___y_516_; uint64_t v___y_517_; uint64_t v___y_518_; uint64_t v___y_519_; uint32_t v___y_520_; uint8_t v___y_521_; uint64_t v___y_522_; uint64_t v___y_526_; uint64_t v___y_527_; uint32_t v___y_528_; uint8_t v___y_529_; uint64_t v___y_538_; uint32_t v___y_539_; uint64_t v___y_540_; uint8_t v___y_541_; uint64_t v___y_542_; uint64_t v___y_543_; uint32_t v_ex_576_; uint32_t v___x_577_; uint32_t v_ey_578_; uint64_t v___y_580_; uint32_t v___y_581_; uint8_t v___y_582_; uint64_t v___y_583_; uint64_t v___y_584_; uint32_t v___y_591_; uint8_t v___y_592_; uint64_t v___y_593_; uint64_t v___y_594_; uint32_t v___y_601_; uint32_t v___y_602_; uint8_t v___y_603_; uint64_t v___y_604_; uint8_t v___y_612_; uint8_t v___y_623_; uint8_t v___y_624_; uint32_t v___x_625_; uint32_t v___x_626_; uint8_t v___x_627_; uint8_t v___y_629_; uint8_t v___y_630_; uint8_t v___y_631_; uint8_t v___y_633_; uint8_t v___y_634_; uint8_t v___y_640_; 
v___x_278_ = 23;
v___x_279_ = lean_uint32_shift_right(v___y_131_, v___x_278_);
v___x_293_ = 255;
v_ex_576_ = lean_uint32_land(v___x_279_, v___x_293_);
v___x_577_ = lean_uint32_shift_right(v___y_132_, v___x_278_);
v_ey_578_ = lean_uint32_land(v___x_577_, v___x_293_);
v___x_625_ = lean_uint32_add(v_ex_576_, v_ey_578_);
v___x_626_ = 128;
v___x_627_ = lean_uint32_dec_lt(v___x_625_, v___x_626_);
if (v___x_627_ == 0)
{
uint32_t v___x_649_; uint32_t v_a_650_; uint32_t v___x_651_; uint32_t v___x_652_; uint32_t v___x_653_; uint8_t v___x_654_; 
v___x_649_ = 2147483647;
v_a_650_ = lean_uint32_land(v___y_131_, v___x_649_);
v___x_651_ = 201326591;
v___x_652_ = 1;
v___x_653_ = lean_uint32_sub(v_a_650_, v___x_652_);
v___x_654_ = lean_uint32_dec_le(v___x_651_, v___x_653_);
if (v___x_654_ == 0)
{
v___y_281_ = v___x_654_;
goto v___jp_280_;
}
else
{
uint32_t v___x_655_; uint8_t v___x_656_; 
v___x_655_ = 2139095040;
v___x_656_ = lean_uint32_dec_lt(v_a_650_, v___x_655_);
v___y_281_ = v___x_656_;
goto v___jp_280_;
}
}
else
{
uint32_t v___x_657_; uint32_t v___x_658_; uint32_t v___x_659_; uint8_t v___x_660_; 
v___x_657_ = 4278190080;
v___x_658_ = 1;
v___x_659_ = lean_uint32_shift_left(v___y_131_, v___x_658_);
v___x_660_ = lean_uint32_dec_le(v___x_657_, v___x_659_);
if (v___x_660_ == 0)
{
uint32_t v___x_661_; uint8_t v___x_662_; 
v___x_661_ = lean_uint32_shift_left(v___y_132_, v___x_658_);
v___x_662_ = lean_uint32_dec_le(v___x_657_, v___x_661_);
v___y_640_ = v___x_662_;
goto v___jp_639_;
}
else
{
v___y_640_ = v___x_660_;
goto v___jp_639_;
}
}
v___jp_133_:
{
if (v___y_134_ == 0)
{
uint32_t v___x_135_; 
v___x_135_ = lp_competition_Submission_FastMul_mul(v___y_131_, v___y_132_);
return v___x_135_;
}
else
{
uint32_t v___x_136_; uint32_t v___x_137_; 
v___x_136_ = 4194304;
v___x_137_ = lean_uint32_lor(v___y_132_, v___x_136_);
return v___x_137_;
}
}
v___jp_138_:
{
uint32_t v___x_139_; uint32_t v___x_140_; uint32_t v___x_141_; uint32_t v___x_142_; uint8_t v___x_143_; 
v___x_139_ = 23;
v___x_140_ = lean_uint32_shift_right(v___y_132_, v___x_139_);
v___x_141_ = 255;
v___x_142_ = lean_uint32_land(v___x_140_, v___x_141_);
v___x_143_ = lean_uint32_dec_eq(v___x_142_, v___x_141_);
if (v___x_143_ == 0)
{
v___y_134_ = v___x_143_;
goto v___jp_133_;
}
else
{
uint32_t v___x_144_; uint32_t v___x_145_; uint32_t v___x_146_; uint8_t v___x_147_; 
v___x_144_ = 8388607;
v___x_145_ = lean_uint32_land(v___y_132_, v___x_144_);
v___x_146_ = 0;
v___x_147_ = lean_uint32_dec_eq(v___x_145_, v___x_146_);
if (v___x_147_ == 0)
{
v___y_134_ = v___x_143_;
goto v___jp_133_;
}
else
{
uint32_t v___x_148_; 
v___x_148_ = lp_competition_Submission_FastMul_mul(v___y_131_, v___y_132_);
return v___x_148_;
}
}
}
v___jp_149_:
{
if (v___y_150_ == 0)
{
goto v___jp_138_;
}
else
{
uint32_t v___x_151_; uint32_t v___x_152_; 
v___x_151_ = 4194304;
v___x_152_ = lean_uint32_lor(v___y_131_, v___x_151_);
return v___x_152_;
}
}
v___jp_153_:
{
uint32_t v___x_154_; uint32_t v___x_155_; uint32_t v___x_156_; uint32_t v___x_157_; uint8_t v___x_158_; 
v___x_154_ = 23;
v___x_155_ = lean_uint32_shift_right(v___y_131_, v___x_154_);
v___x_156_ = 255;
v___x_157_ = lean_uint32_land(v___x_155_, v___x_156_);
v___x_158_ = lean_uint32_dec_eq(v___x_157_, v___x_156_);
if (v___x_158_ == 0)
{
v___y_150_ = v___x_158_;
goto v___jp_149_;
}
else
{
uint32_t v___x_159_; uint32_t v___x_160_; uint32_t v___x_161_; uint8_t v___x_162_; 
v___x_159_ = 8388607;
v___x_160_ = lean_uint32_land(v___y_131_, v___x_159_);
v___x_161_ = 0;
v___x_162_ = lean_uint32_dec_eq(v___x_160_, v___x_161_);
if (v___x_162_ == 0)
{
v___y_150_ = v___x_158_;
goto v___jp_149_;
}
else
{
goto v___jp_138_;
}
}
}
v___jp_163_:
{
if (v___y_164_ == 0)
{
goto v___jp_153_;
}
else
{
uint32_t v___x_165_; uint32_t v___x_166_; uint32_t v___x_167_; uint8_t v___x_168_; 
v___x_165_ = 4194304;
v___x_166_ = lean_uint32_land(v___y_132_, v___x_165_);
v___x_167_ = 0;
v___x_168_ = lean_uint32_dec_eq(v___x_166_, v___x_167_);
if (v___x_168_ == 0)
{
goto v___jp_153_;
}
else
{
uint32_t v___x_169_; 
v___x_169_ = lean_uint32_lor(v___y_132_, v___x_165_);
return v___x_169_;
}
}
}
v___jp_170_:
{
uint32_t v___x_171_; uint32_t v___x_172_; uint32_t v___x_173_; uint32_t v___x_174_; uint8_t v___x_175_; 
v___x_171_ = 23;
v___x_172_ = lean_uint32_shift_right(v___y_132_, v___x_171_);
v___x_173_ = 255;
v___x_174_ = lean_uint32_land(v___x_172_, v___x_173_);
v___x_175_ = lean_uint32_dec_eq(v___x_174_, v___x_173_);
if (v___x_175_ == 0)
{
v___y_164_ = v___x_175_;
goto v___jp_163_;
}
else
{
uint32_t v___x_176_; uint32_t v___x_177_; uint32_t v___x_178_; uint8_t v___x_179_; 
v___x_176_ = 8388607;
v___x_177_ = lean_uint32_land(v___y_132_, v___x_176_);
v___x_178_ = 0;
v___x_179_ = lean_uint32_dec_eq(v___x_177_, v___x_178_);
if (v___x_179_ == 0)
{
v___y_164_ = v___x_175_;
goto v___jp_163_;
}
else
{
goto v___jp_153_;
}
}
}
v___jp_180_:
{
if (v___y_181_ == 0)
{
goto v___jp_170_;
}
else
{
uint32_t v___x_182_; uint32_t v___x_183_; uint32_t v___x_184_; uint8_t v___x_185_; 
v___x_182_ = 4194304;
v___x_183_ = lean_uint32_land(v___y_131_, v___x_182_);
v___x_184_ = 0;
v___x_185_ = lean_uint32_dec_eq(v___x_183_, v___x_184_);
if (v___x_185_ == 0)
{
goto v___jp_170_;
}
else
{
uint32_t v___x_186_; 
v___x_186_ = lean_uint32_lor(v___y_131_, v___x_182_);
return v___x_186_;
}
}
}
v___jp_187_:
{
float v_result_190_; uint8_t v___x_191_; 
v_result_190_ = lean_float32_mul(v___y_188_, v___y_189_);
v___x_191_ = lean_float32_beq(v_result_190_, v_result_190_);
if (v___x_191_ == 0)
{
uint32_t v___x_192_; uint32_t v___x_193_; uint32_t v___x_194_; uint32_t v___x_195_; uint8_t v___x_196_; 
v___x_192_ = 23;
v___x_193_ = lean_uint32_shift_right(v___y_131_, v___x_192_);
v___x_194_ = 255;
v___x_195_ = lean_uint32_land(v___x_193_, v___x_194_);
v___x_196_ = lean_uint32_dec_eq(v___x_195_, v___x_194_);
if (v___x_196_ == 0)
{
v___y_181_ = v___x_196_;
goto v___jp_180_;
}
else
{
uint32_t v___x_197_; uint32_t v___x_198_; uint32_t v___x_199_; uint8_t v___x_200_; 
v___x_197_ = 8388607;
v___x_198_ = lean_uint32_land(v___y_131_, v___x_197_);
v___x_199_ = 0;
v___x_200_ = lean_uint32_dec_eq(v___x_198_, v___x_199_);
if (v___x_200_ == 0)
{
v___y_181_ = v___x_196_;
goto v___jp_180_;
}
else
{
goto v___jp_170_;
}
}
}
else
{
uint32_t v___x_201_; 
v___x_201_ = lean_float32_to_bits(v_result_190_);
return v___x_201_;
}
}
v___jp_202_:
{
if (v___y_204_ == 0)
{
float v___x_205_; 
v___x_205_ = lean_float32_of_bits(v___y_132_);
v___y_188_ = v___y_203_;
v___y_189_ = v___x_205_;
goto v___jp_187_;
}
else
{
uint32_t v___x_206_; uint32_t v___x_207_; uint32_t v___x_208_; uint32_t v___x_209_; float v___x_210_; lean_object* v___x_211_; uint32_t v___x_212_; uint32_t v___x_213_; lean_object* v___x_214_; lean_object* v___x_215_; float v___x_216_; float v___x_217_; 
v___x_206_ = 8388607;
v___x_207_ = lean_uint32_land(v___y_132_, v___x_206_);
v___x_208_ = 8388608;
v___x_209_ = lean_uint32_lor(v___x_207_, v___x_208_);
v___x_210_ = lean_uint32_to_float32(v___x_209_);
v___x_211_ = lp_competition_R2W01b_scaleTable;
v___x_212_ = 23;
v___x_213_ = lean_uint32_shift_right(v___y_132_, v___x_212_);
v___x_214_ = lean_uint32_to_nat(v___x_213_);
v___x_215_ = lean_array_fget_borrowed(v___x_211_, v___x_214_);
lean_dec(v___x_214_);
v___x_216_ = lean_unbox_float32(v___x_215_);
v___x_217_ = lean_float32_mul(v___x_210_, v___x_216_);
v___y_188_ = v___y_203_;
v___y_189_ = v___x_217_;
goto v___jp_187_;
}
}
v___jp_218_:
{
uint32_t v___x_220_; uint32_t v_a_221_; uint32_t v___x_222_; uint32_t v___x_223_; uint32_t v___x_224_; uint8_t v___x_225_; 
v___x_220_ = 2147483647;
v_a_221_ = lean_uint32_land(v___y_132_, v___x_220_);
v___x_222_ = 201326591;
v___x_223_ = 1;
v___x_224_ = lean_uint32_sub(v_a_221_, v___x_223_);
v___x_225_ = lean_uint32_dec_le(v___x_222_, v___x_224_);
if (v___x_225_ == 0)
{
v___y_203_ = v___y_219_;
v___y_204_ = v___x_225_;
goto v___jp_202_;
}
else
{
uint32_t v___x_226_; uint8_t v___x_227_; 
v___x_226_ = 2139095040;
v___x_227_ = lean_uint32_dec_lt(v_a_221_, v___x_226_);
v___y_203_ = v___y_219_;
v___y_204_ = v___x_227_;
goto v___jp_202_;
}
}
v___jp_228_:
{
uint32_t v___x_230_; uint32_t v___x_231_; 
v___x_230_ = 8388608;
v___x_231_ = lean_uint32_lor(v___y_229_, v___x_230_);
return v___x_231_;
}
v___jp_232_:
{
uint32_t v___x_234_; uint32_t v___x_235_; 
v___x_234_ = 8388608;
v___x_235_ = lean_uint32_lor(v___y_233_, v___x_234_);
return v___x_235_;
}
v___jp_236_:
{
uint32_t v___x_240_; uint32_t v___x_241_; 
v___x_240_ = lean_uint32_land(v___y_237_, v___y_238_);
v___x_241_ = lean_uint32_lor(v___y_239_, v___x_240_);
return v___x_241_;
}
v___jp_242_:
{
uint8_t v___x_247_; 
v___x_247_ = lean_uint64_dec_eq(v___y_246_, v___y_243_);
if (v___x_247_ == 0)
{
uint64_t v___x_248_; uint8_t v___x_249_; 
v___x_248_ = 8388608ULL;
v___x_249_ = lean_uint64_dec_eq(v___y_246_, v___x_248_);
if (v___x_249_ == 0)
{
uint32_t v___x_250_; 
v___x_250_ = lean_uint64_to_uint32(v___y_246_);
if (v___y_245_ == 0)
{
uint32_t v___x_251_; 
v___x_251_ = 0;
v___y_237_ = v___x_250_;
v___y_238_ = v___y_244_;
v___y_239_ = v___x_251_;
goto v___jp_236_;
}
else
{
uint32_t v___x_252_; 
v___x_252_ = 2147483648;
v___y_237_ = v___x_250_;
v___y_238_ = v___y_244_;
v___y_239_ = v___x_252_;
goto v___jp_236_;
}
}
else
{
if (v___y_245_ == 0)
{
uint32_t v___x_253_; 
v___x_253_ = 0;
v___y_233_ = v___x_253_;
goto v___jp_232_;
}
else
{
uint32_t v___x_254_; 
v___x_254_ = 2147483648;
v___y_233_ = v___x_254_;
goto v___jp_232_;
}
}
}
else
{
if (v___y_245_ == 0)
{
uint32_t v___x_255_; 
v___x_255_ = 0;
return v___x_255_;
}
else
{
uint32_t v___x_256_; 
v___x_256_ = 2147483648;
return v___x_256_;
}
}
}
v___jp_257_:
{
uint32_t v___x_261_; uint32_t v___x_262_; 
v___x_261_ = lean_uint32_land(v___y_258_, v___y_259_);
v___x_262_ = lean_uint32_lor(v___y_260_, v___x_261_);
return v___x_262_;
}
v___jp_263_:
{
uint8_t v___x_268_; 
v___x_268_ = lean_uint64_dec_eq(v___y_267_, v___y_265_);
if (v___x_268_ == 0)
{
uint64_t v___x_269_; uint8_t v___x_270_; 
v___x_269_ = 8388608ULL;
v___x_270_ = lean_uint64_dec_eq(v___y_267_, v___x_269_);
if (v___x_270_ == 0)
{
uint32_t v___x_271_; 
v___x_271_ = lean_uint64_to_uint32(v___y_267_);
if (v___y_266_ == 0)
{
uint32_t v___x_272_; 
v___x_272_ = 0;
v___y_258_ = v___x_271_;
v___y_259_ = v___y_264_;
v___y_260_ = v___x_272_;
goto v___jp_257_;
}
else
{
uint32_t v___x_273_; 
v___x_273_ = 2147483648;
v___y_258_ = v___x_271_;
v___y_259_ = v___y_264_;
v___y_260_ = v___x_273_;
goto v___jp_257_;
}
}
else
{
if (v___y_266_ == 0)
{
uint32_t v___x_274_; 
v___x_274_ = 0;
v___y_229_ = v___x_274_;
goto v___jp_228_;
}
else
{
uint32_t v___x_275_; 
v___x_275_ = 2147483648;
v___y_229_ = v___x_275_;
goto v___jp_228_;
}
}
}
else
{
if (v___y_266_ == 0)
{
uint32_t v___x_276_; 
v___x_276_ = 0;
return v___x_276_;
}
else
{
uint32_t v___x_277_; 
v___x_277_ = 2147483648;
return v___x_277_;
}
}
}
v___jp_280_:
{
if (v___y_281_ == 0)
{
float v___x_282_; 
v___x_282_ = lean_float32_of_bits(v___y_131_);
v___y_219_ = v___x_282_;
goto v___jp_218_;
}
else
{
uint32_t v___x_283_; uint32_t v___x_284_; uint32_t v___x_285_; uint32_t v___x_286_; float v___x_287_; lean_object* v___x_288_; lean_object* v___x_289_; lean_object* v___x_290_; float v___x_291_; float v___x_292_; 
v___x_283_ = 8388607;
v___x_284_ = lean_uint32_land(v___y_131_, v___x_283_);
v___x_285_ = 8388608;
v___x_286_ = lean_uint32_lor(v___x_284_, v___x_285_);
v___x_287_ = lean_uint32_to_float32(v___x_286_);
v___x_288_ = lp_competition_R2W01b_scaleTable;
v___x_289_ = lean_uint32_to_nat(v___x_279_);
v___x_290_ = lean_array_fget_borrowed(v___x_288_, v___x_289_);
lean_dec(v___x_289_);
v___x_291_ = lean_unbox_float32(v___x_290_);
v___x_292_ = lean_float32_mul(v___x_287_, v___x_291_);
v___y_219_ = v___x_292_;
goto v___jp_218_;
}
}
v___jp_294_:
{
uint32_t v___x_299_; uint32_t v___x_300_; uint32_t v___x_301_; uint32_t v___x_302_; uint32_t v___x_303_; 
v___x_299_ = lean_uint32_land(v___y_295_, v___x_293_);
v___x_300_ = lean_uint32_shift_left(v___x_299_, v___x_278_);
v___x_301_ = lean_uint32_lor(v___y_298_, v___x_300_);
v___x_302_ = lean_uint32_land(v___y_297_, v___y_296_);
v___x_303_ = lean_uint32_lor(v___x_301_, v___x_302_);
return v___x_303_;
}
v___jp_304_:
{
if (v___y_307_ == 0)
{
uint32_t v___x_309_; 
v___x_309_ = 0;
v___y_295_ = v___y_305_;
v___y_296_ = v___y_306_;
v___y_297_ = v___y_308_;
v___y_298_ = v___x_309_;
goto v___jp_294_;
}
else
{
uint32_t v___x_310_; 
v___x_310_ = 2147483648;
v___y_295_ = v___y_305_;
v___y_296_ = v___y_306_;
v___y_297_ = v___y_308_;
v___y_298_ = v___x_310_;
goto v___jp_294_;
}
}
v___jp_311_:
{
uint64_t v___x_317_; uint64_t v_encodedExponent_318_; uint32_t v___x_319_; uint64_t v___x_320_; uint8_t v___x_321_; 
v___x_317_ = 171ULL;
v_encodedExponent_318_ = lean_uint64_sub(v___y_312_, v___x_317_);
v___x_319_ = lean_uint64_to_uint32(v_encodedExponent_318_);
v___x_320_ = 8388608ULL;
v___x_321_ = lean_uint64_dec_lt(v___y_316_, v___x_320_);
if (v___x_321_ == 0)
{
uint64_t v___x_322_; uint32_t v___x_323_; 
v___x_322_ = lean_uint64_sub(v___y_316_, v___x_320_);
v___x_323_ = lean_uint64_to_uint32(v___x_322_);
v___y_305_ = v___x_319_;
v___y_306_ = v___y_314_;
v___y_307_ = v___y_315_;
v___y_308_ = v___x_323_;
goto v___jp_304_;
}
else
{
uint32_t v___x_324_; 
v___x_324_ = lean_uint64_to_uint32(v___y_313_);
v___y_305_ = v___x_319_;
v___y_306_ = v___y_314_;
v___y_307_ = v___y_315_;
v___y_308_ = v___x_324_;
goto v___jp_304_;
}
}
v___jp_325_:
{
uint64_t v___x_332_; uint8_t v___x_333_; 
v___x_332_ = 425ULL;
v___x_333_ = lean_uint64_dec_lt(v___x_332_, v___y_331_);
if (v___x_333_ == 0)
{
if (v___y_327_ == 0)
{
v___y_312_ = v___y_331_;
v___y_313_ = v___y_328_;
v___y_314_ = v___y_329_;
v___y_315_ = v___y_330_;
v___y_316_ = v___y_326_;
goto v___jp_311_;
}
else
{
uint64_t v___x_334_; 
v___x_334_ = 8388608ULL;
v___y_312_ = v___y_331_;
v___y_313_ = v___y_328_;
v___y_314_ = v___y_329_;
v___y_315_ = v___y_330_;
v___y_316_ = v___x_334_;
goto v___jp_311_;
}
}
else
{
if (v___y_330_ == 0)
{
uint32_t v___x_335_; 
v___x_335_ = 2139095040;
return v___x_335_;
}
else
{
uint32_t v___x_336_; 
v___x_336_ = 4286578688;
return v___x_336_;
}
}
}
v___jp_337_:
{
uint64_t v___x_343_; uint8_t v_carry_344_; 
v___x_343_ = 16777216ULL;
v_carry_344_ = lean_uint64_dec_eq(v___y_342_, v___x_343_);
if (v_carry_344_ == 0)
{
v___y_326_ = v___y_342_;
v___y_327_ = v_carry_344_;
v___y_328_ = v___y_338_;
v___y_329_ = v___y_339_;
v___y_330_ = v___y_341_;
v___y_331_ = v___y_340_;
goto v___jp_325_;
}
else
{
uint64_t v___x_345_; uint64_t v___x_346_; 
v___x_345_ = 1ULL;
v___x_346_ = lean_uint64_add(v___y_340_, v___x_345_);
v___y_326_ = v___y_342_;
v___y_327_ = v_carry_344_;
v___y_328_ = v___y_338_;
v___y_329_ = v___y_339_;
v___y_330_ = v___y_341_;
v___y_331_ = v___x_346_;
goto v___jp_325_;
}
}
v___jp_347_:
{
uint64_t v_position_354_; uint64_t v___x_355_; uint8_t v___x_356_; 
v_position_354_ = lean_uint64_add(v___y_353_, v___y_348_);
v___x_355_ = 172ULL;
v___x_356_ = lean_uint64_dec_lt(v_position_354_, v___x_355_);
if (v___x_356_ == 0)
{
uint64_t v___x_357_; uint8_t v___x_358_; 
v___x_357_ = 23ULL;
v___x_358_ = lean_uint64_dec_lt(v___y_353_, v___x_357_);
if (v___x_358_ == 0)
{
uint64_t v___x_359_; uint8_t v___x_360_; 
v___x_359_ = lean_uint64_sub(v___y_353_, v___x_357_);
v___x_360_ = lean_uint64_dec_eq(v___x_359_, v___y_350_);
if (v___x_360_ == 0)
{
uint64_t v___x_361_; uint8_t v___x_362_; 
v___x_361_ = 64ULL;
v___x_362_ = lean_uint64_dec_lt(v___x_359_, v___x_361_);
if (v___x_362_ == 0)
{
uint8_t v___x_363_; 
v___x_363_ = lean_uint64_dec_eq(v___x_359_, v___x_361_);
if (v___x_363_ == 0)
{
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v___y_350_;
goto v___jp_337_;
}
else
{
uint64_t v___x_364_; uint8_t v___x_365_; 
v___x_364_ = 9223372036854775808ULL;
v___x_365_ = lean_uint64_dec_lt(v___x_364_, v___y_349_);
if (v___x_365_ == 0)
{
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v___y_350_;
goto v___jp_337_;
}
else
{
uint64_t v___x_366_; 
v___x_366_ = 1ULL;
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v___x_366_;
goto v___jp_337_;
}
}
}
else
{
uint64_t v_quotient_367_; uint64_t v___x_368_; uint64_t v___x_369_; uint64_t v___x_370_; uint64_t v_remainder_371_; uint64_t v___x_372_; uint64_t v_half_373_; uint8_t v___x_374_; 
v_quotient_367_ = lean_uint64_shift_right(v___y_349_, v___x_359_);
v___x_368_ = 1ULL;
v___x_369_ = lean_uint64_shift_left(v___x_368_, v___x_359_);
v___x_370_ = lean_uint64_sub(v___x_369_, v___x_368_);
v_remainder_371_ = lean_uint64_land(v___y_349_, v___x_370_);
v___x_372_ = lean_uint64_sub(v___x_359_, v___x_368_);
v_half_373_ = lean_uint64_shift_left(v___x_368_, v___x_372_);
v___x_374_ = lean_uint64_dec_lt(v_remainder_371_, v_half_373_);
if (v___x_374_ == 0)
{
uint8_t v___x_375_; 
v___x_375_ = lean_uint64_dec_lt(v_half_373_, v_remainder_371_);
if (v___x_375_ == 0)
{
uint64_t v___x_376_; uint8_t v___x_377_; 
v___x_376_ = lean_uint64_land(v_quotient_367_, v___x_368_);
v___x_377_ = lean_uint64_dec_eq(v___x_376_, v___y_350_);
if (v___x_377_ == 0)
{
uint64_t v___x_378_; 
v___x_378_ = lean_uint64_add(v_quotient_367_, v___x_368_);
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v___x_378_;
goto v___jp_337_;
}
else
{
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v_quotient_367_;
goto v___jp_337_;
}
}
else
{
uint64_t v___x_379_; 
v___x_379_ = lean_uint64_add(v_quotient_367_, v___x_368_);
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v___x_379_;
goto v___jp_337_;
}
}
else
{
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v_quotient_367_;
goto v___jp_337_;
}
}
}
else
{
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v___y_349_;
goto v___jp_337_;
}
}
else
{
uint64_t v___x_380_; uint64_t v___x_381_; 
v___x_380_ = lean_uint64_sub(v___x_357_, v___y_353_);
v___x_381_ = lean_uint64_shift_left(v___y_349_, v___x_380_);
v___y_338_ = v___y_350_;
v___y_339_ = v___y_351_;
v___y_340_ = v_position_354_;
v___y_341_ = v___y_352_;
v___y_342_ = v___x_381_;
goto v___jp_337_;
}
}
else
{
uint64_t v___x_382_; uint8_t v___x_383_; 
v___x_382_ = 149ULL;
v___x_383_ = lean_uint64_dec_lt(v___y_348_, v___x_382_);
if (v___x_383_ == 0)
{
uint64_t v___x_384_; uint64_t v___x_385_; 
v___x_384_ = lean_uint64_sub(v___y_348_, v___x_382_);
v___x_385_ = lean_uint64_shift_left(v___y_349_, v___x_384_);
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v___x_385_;
goto v___jp_242_;
}
else
{
uint64_t v___x_386_; uint8_t v___x_387_; 
v___x_386_ = lean_uint64_sub(v___x_382_, v___y_348_);
v___x_387_ = lean_uint64_dec_eq(v___x_386_, v___y_350_);
if (v___x_387_ == 0)
{
uint64_t v___x_388_; uint8_t v___x_389_; 
v___x_388_ = 64ULL;
v___x_389_ = lean_uint64_dec_lt(v___x_386_, v___x_388_);
if (v___x_389_ == 0)
{
uint8_t v___x_390_; 
v___x_390_ = lean_uint64_dec_eq(v___x_386_, v___x_388_);
if (v___x_390_ == 0)
{
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v___y_350_;
goto v___jp_242_;
}
else
{
uint64_t v___x_391_; uint8_t v___x_392_; 
v___x_391_ = 9223372036854775808ULL;
v___x_392_ = lean_uint64_dec_lt(v___x_391_, v___y_349_);
if (v___x_392_ == 0)
{
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v___y_350_;
goto v___jp_242_;
}
else
{
uint64_t v___x_393_; 
v___x_393_ = 1ULL;
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v___x_393_;
goto v___jp_242_;
}
}
}
else
{
uint64_t v_quotient_394_; uint64_t v___x_395_; uint64_t v___x_396_; uint64_t v___x_397_; uint64_t v_remainder_398_; uint64_t v___x_399_; uint64_t v_half_400_; uint8_t v___x_401_; 
v_quotient_394_ = lean_uint64_shift_right(v___y_349_, v___x_386_);
v___x_395_ = 1ULL;
v___x_396_ = lean_uint64_shift_left(v___x_395_, v___x_386_);
v___x_397_ = lean_uint64_sub(v___x_396_, v___x_395_);
v_remainder_398_ = lean_uint64_land(v___y_349_, v___x_397_);
v___x_399_ = lean_uint64_sub(v___x_386_, v___x_395_);
v_half_400_ = lean_uint64_shift_left(v___x_395_, v___x_399_);
v___x_401_ = lean_uint64_dec_lt(v_remainder_398_, v_half_400_);
if (v___x_401_ == 0)
{
uint8_t v___x_402_; 
v___x_402_ = lean_uint64_dec_lt(v_half_400_, v_remainder_398_);
if (v___x_402_ == 0)
{
uint64_t v___x_403_; uint8_t v___x_404_; 
v___x_403_ = lean_uint64_land(v_quotient_394_, v___x_395_);
v___x_404_ = lean_uint64_dec_eq(v___x_403_, v___y_350_);
if (v___x_404_ == 0)
{
uint64_t v___x_405_; 
v___x_405_ = lean_uint64_add(v_quotient_394_, v___x_395_);
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v___x_405_;
goto v___jp_242_;
}
else
{
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v_quotient_394_;
goto v___jp_242_;
}
}
else
{
uint64_t v___x_406_; 
v___x_406_ = lean_uint64_add(v_quotient_394_, v___x_395_);
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v___x_406_;
goto v___jp_242_;
}
}
else
{
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v_quotient_394_;
goto v___jp_242_;
}
}
}
else
{
v___y_243_ = v___y_350_;
v___y_244_ = v___y_351_;
v___y_245_ = v___y_352_;
v___y_246_ = v___y_349_;
goto v___jp_242_;
}
}
}
}
v___jp_407_:
{
uint64_t v___x_415_; uint64_t v___x_416_; uint8_t v___x_417_; 
v___x_415_ = 1ULL;
v___x_416_ = lean_uint64_shift_right(v___y_411_, v___x_415_);
v___x_417_ = lean_uint64_dec_eq(v___x_416_, v___y_410_);
if (v___x_417_ == 0)
{
uint64_t v___x_418_; 
v___x_418_ = lean_uint64_add(v___y_414_, v___x_415_);
v___y_348_ = v___y_408_;
v___y_349_ = v___y_409_;
v___y_350_ = v___y_410_;
v___y_351_ = v___y_412_;
v___y_352_ = v___y_413_;
v___y_353_ = v___x_418_;
goto v___jp_347_;
}
else
{
v___y_348_ = v___y_408_;
v___y_349_ = v___y_409_;
v___y_350_ = v___y_410_;
v___y_351_ = v___y_412_;
v___y_352_ = v___y_413_;
v___y_353_ = v___y_414_;
goto v___jp_347_;
}
}
v___jp_419_:
{
uint64_t v___x_429_; uint8_t v___x_430_; 
v___x_429_ = lean_uint64_shift_right(v___y_420_, v___y_424_);
v___x_430_ = lean_uint64_dec_eq(v___x_429_, v___y_425_);
if (v___x_430_ == 0)
{
uint64_t v___x_431_; 
v___x_431_ = lean_uint64_add(v___y_423_, v___y_424_);
v___y_408_ = v___y_421_;
v___y_409_ = v___y_422_;
v___y_410_ = v___y_425_;
v___y_411_ = v___y_428_;
v___y_412_ = v___y_426_;
v___y_413_ = v___y_427_;
v___y_414_ = v___x_431_;
goto v___jp_407_;
}
else
{
v___y_408_ = v___y_421_;
v___y_409_ = v___y_422_;
v___y_410_ = v___y_425_;
v___y_411_ = v___y_428_;
v___y_412_ = v___y_426_;
v___y_413_ = v___y_427_;
v___y_414_ = v___y_423_;
goto v___jp_407_;
}
}
v___jp_432_:
{
uint64_t v___x_440_; uint64_t v___x_441_; uint8_t v___x_442_; 
v___x_440_ = 2ULL;
v___x_441_ = lean_uint64_shift_right(v___y_433_, v___x_440_);
v___x_442_ = lean_uint64_dec_eq(v___x_441_, v___y_436_);
if (v___x_442_ == 0)
{
v___y_420_ = v___y_433_;
v___y_421_ = v___y_434_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_439_;
v___y_424_ = v___x_440_;
v___y_425_ = v___y_436_;
v___y_426_ = v___y_437_;
v___y_427_ = v___y_438_;
v___y_428_ = v___x_441_;
goto v___jp_419_;
}
else
{
v___y_420_ = v___y_433_;
v___y_421_ = v___y_434_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_439_;
v___y_424_ = v___x_440_;
v___y_425_ = v___y_436_;
v___y_426_ = v___y_437_;
v___y_427_ = v___y_438_;
v___y_428_ = v___y_433_;
goto v___jp_419_;
}
}
v___jp_443_:
{
uint64_t v___x_453_; uint8_t v___x_454_; 
v___x_453_ = lean_uint64_shift_right(v___y_451_, v___y_445_);
v___x_454_ = lean_uint64_dec_eq(v___x_453_, v___y_448_);
if (v___x_454_ == 0)
{
uint64_t v___x_455_; 
v___x_455_ = lean_uint64_add(v___y_444_, v___y_445_);
v___y_433_ = v___y_452_;
v___y_434_ = v___y_446_;
v___y_435_ = v___y_447_;
v___y_436_ = v___y_448_;
v___y_437_ = v___y_449_;
v___y_438_ = v___y_450_;
v___y_439_ = v___x_455_;
goto v___jp_432_;
}
else
{
v___y_433_ = v___y_452_;
v___y_434_ = v___y_446_;
v___y_435_ = v___y_447_;
v___y_436_ = v___y_448_;
v___y_437_ = v___y_449_;
v___y_438_ = v___y_450_;
v___y_439_ = v___y_444_;
goto v___jp_432_;
}
}
v___jp_456_:
{
uint64_t v___x_464_; uint64_t v___x_465_; uint8_t v___x_466_; 
v___x_464_ = 4ULL;
v___x_465_ = lean_uint64_shift_right(v___y_462_, v___x_464_);
v___x_466_ = lean_uint64_dec_eq(v___x_465_, v___y_459_);
if (v___x_466_ == 0)
{
v___y_444_ = v___y_463_;
v___y_445_ = v___x_464_;
v___y_446_ = v___y_457_;
v___y_447_ = v___y_458_;
v___y_448_ = v___y_459_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___y_462_;
v___y_452_ = v___x_465_;
goto v___jp_443_;
}
else
{
v___y_444_ = v___y_463_;
v___y_445_ = v___x_464_;
v___y_446_ = v___y_457_;
v___y_447_ = v___y_458_;
v___y_448_ = v___y_459_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___y_462_;
v___y_452_ = v___y_462_;
goto v___jp_443_;
}
}
v___jp_467_:
{
uint64_t v___x_477_; uint8_t v___x_478_; 
v___x_477_ = lean_uint64_shift_right(v___y_470_, v___y_468_);
v___x_478_ = lean_uint64_dec_eq(v___x_477_, v___y_472_);
if (v___x_478_ == 0)
{
uint64_t v___x_479_; 
v___x_479_ = lean_uint64_add(v___y_474_, v___y_468_);
v___y_457_ = v___y_469_;
v___y_458_ = v___y_471_;
v___y_459_ = v___y_472_;
v___y_460_ = v___y_473_;
v___y_461_ = v___y_475_;
v___y_462_ = v___y_476_;
v___y_463_ = v___x_479_;
goto v___jp_456_;
}
else
{
v___y_457_ = v___y_469_;
v___y_458_ = v___y_471_;
v___y_459_ = v___y_472_;
v___y_460_ = v___y_473_;
v___y_461_ = v___y_475_;
v___y_462_ = v___y_476_;
v___y_463_ = v___y_474_;
goto v___jp_456_;
}
}
v___jp_480_:
{
uint64_t v___x_488_; uint64_t v___x_489_; uint8_t v___x_490_; 
v___x_488_ = 8ULL;
v___x_489_ = lean_uint64_shift_right(v___y_483_, v___x_488_);
v___x_490_ = lean_uint64_dec_eq(v___x_489_, v___y_484_);
if (v___x_490_ == 0)
{
v___y_468_ = v___x_488_;
v___y_469_ = v___y_481_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_484_;
v___y_473_ = v___y_485_;
v___y_474_ = v___y_487_;
v___y_475_ = v___y_486_;
v___y_476_ = v___x_489_;
goto v___jp_467_;
}
else
{
v___y_468_ = v___x_488_;
v___y_469_ = v___y_481_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_484_;
v___y_473_ = v___y_485_;
v___y_474_ = v___y_487_;
v___y_475_ = v___y_486_;
v___y_476_ = v___y_483_;
goto v___jp_467_;
}
}
v___jp_491_:
{
uint64_t v___x_501_; uint8_t v___x_502_; 
v___x_501_ = lean_uint64_shift_right(v___y_492_, v___y_497_);
v___x_502_ = lean_uint64_dec_eq(v___x_501_, v___y_496_);
if (v___x_502_ == 0)
{
uint64_t v___x_503_; 
v___x_503_ = lean_uint64_add(v___y_495_, v___y_497_);
v___y_481_ = v___y_493_;
v___y_482_ = v___y_494_;
v___y_483_ = v___y_500_;
v___y_484_ = v___y_496_;
v___y_485_ = v___y_498_;
v___y_486_ = v___y_499_;
v___y_487_ = v___x_503_;
goto v___jp_480_;
}
else
{
v___y_481_ = v___y_493_;
v___y_482_ = v___y_494_;
v___y_483_ = v___y_500_;
v___y_484_ = v___y_496_;
v___y_485_ = v___y_498_;
v___y_486_ = v___y_499_;
v___y_487_ = v___y_495_;
goto v___jp_480_;
}
}
v___jp_504_:
{
uint64_t v___x_512_; uint64_t v___x_513_; uint8_t v___x_514_; 
v___x_512_ = 16ULL;
v___x_513_ = lean_uint64_shift_right(v___y_506_, v___x_512_);
v___x_514_ = lean_uint64_dec_eq(v___x_513_, v___y_508_);
if (v___x_514_ == 0)
{
v___y_492_ = v___y_506_;
v___y_493_ = v___y_505_;
v___y_494_ = v___y_507_;
v___y_495_ = v___y_511_;
v___y_496_ = v___y_508_;
v___y_497_ = v___x_512_;
v___y_498_ = v___y_509_;
v___y_499_ = v___y_510_;
v___y_500_ = v___x_513_;
goto v___jp_491_;
}
else
{
v___y_492_ = v___y_506_;
v___y_493_ = v___y_505_;
v___y_494_ = v___y_507_;
v___y_495_ = v___y_511_;
v___y_496_ = v___y_508_;
v___y_497_ = v___x_512_;
v___y_498_ = v___y_509_;
v___y_499_ = v___y_510_;
v___y_500_ = v___y_506_;
goto v___jp_491_;
}
}
v___jp_515_:
{
uint64_t v___x_523_; uint8_t v___x_524_; 
v___x_523_ = lean_uint64_shift_right(v___y_518_, v___y_516_);
v___x_524_ = lean_uint64_dec_eq(v___x_523_, v___y_519_);
if (v___x_524_ == 0)
{
v___y_505_ = v___y_517_;
v___y_506_ = v___y_522_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_519_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_521_;
v___y_511_ = v___y_516_;
goto v___jp_504_;
}
else
{
v___y_505_ = v___y_517_;
v___y_506_ = v___y_522_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_519_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_521_;
v___y_511_ = v___y_519_;
goto v___jp_504_;
}
}
v___jp_525_:
{
uint64_t v___x_530_; uint8_t v___x_531_; 
v___x_530_ = 0ULL;
v___x_531_ = lean_uint64_dec_eq(v___y_527_, v___x_530_);
if (v___x_531_ == 0)
{
uint64_t v___x_532_; uint64_t v___x_533_; uint8_t v___x_534_; 
v___x_532_ = 32ULL;
v___x_533_ = lean_uint64_shift_right(v___y_527_, v___x_532_);
v___x_534_ = lean_uint64_dec_eq(v___x_533_, v___x_530_);
if (v___x_534_ == 0)
{
v___y_516_ = v___x_532_;
v___y_517_ = v___y_526_;
v___y_518_ = v___y_527_;
v___y_519_ = v___x_530_;
v___y_520_ = v___y_528_;
v___y_521_ = v___y_529_;
v___y_522_ = v___x_533_;
goto v___jp_515_;
}
else
{
v___y_516_ = v___x_532_;
v___y_517_ = v___y_526_;
v___y_518_ = v___y_527_;
v___y_519_ = v___x_530_;
v___y_520_ = v___y_528_;
v___y_521_ = v___y_529_;
v___y_522_ = v___y_527_;
goto v___jp_515_;
}
}
else
{
if (v___y_529_ == 0)
{
uint32_t v___x_535_; 
v___x_535_ = 0;
return v___x_535_;
}
else
{
uint32_t v___x_536_; 
v___x_536_ = 2147483648;
return v___x_536_;
}
}
}
v___jp_537_:
{
uint64_t v___x_544_; uint64_t v___x_545_; uint64_t v___x_546_; uint8_t v___x_547_; 
v___x_544_ = lean_uint64_mul(v___y_542_, v___y_538_);
v___x_545_ = lean_uint64_add(v___y_540_, v___y_543_);
v___x_546_ = 281474976710656ULL;
v___x_547_ = lean_uint64_dec_lt(v___x_544_, v___x_546_);
if (v___x_547_ == 0)
{
v___y_526_ = v___x_545_;
v___y_527_ = v___x_544_;
v___y_528_ = v___y_539_;
v___y_529_ = v___y_541_;
goto v___jp_525_;
}
else
{
uint64_t v___x_548_; uint8_t v___x_549_; 
v___x_548_ = 123ULL;
v___x_549_ = lean_uint64_dec_le(v___x_545_, v___x_548_);
if (v___x_549_ == 0)
{
v___y_526_ = v___x_545_;
v___y_527_ = v___x_544_;
v___y_528_ = v___y_539_;
v___y_529_ = v___y_541_;
goto v___jp_525_;
}
else
{
uint64_t v___x_550_; uint8_t v___x_551_; 
v___x_550_ = 0ULL;
v___x_551_ = lean_uint64_dec_eq(v___x_544_, v___x_550_);
if (v___x_551_ == 0)
{
uint64_t v___x_552_; uint64_t v___x_553_; uint8_t v___x_554_; 
v___x_552_ = 149ULL;
v___x_553_ = lean_uint64_sub(v___x_552_, v___x_545_);
v___x_554_ = lean_uint64_dec_eq(v___x_553_, v___x_550_);
if (v___x_554_ == 0)
{
uint64_t v___x_555_; uint8_t v___x_556_; 
v___x_555_ = 64ULL;
v___x_556_ = lean_uint64_dec_lt(v___x_553_, v___x_555_);
if (v___x_556_ == 0)
{
uint8_t v___x_557_; 
v___x_557_ = lean_uint64_dec_eq(v___x_553_, v___x_555_);
if (v___x_557_ == 0)
{
v___y_264_ = v___y_539_;
v___y_265_ = v___x_550_;
v___y_266_ = v___y_541_;
v___y_267_ = v___x_550_;
goto v___jp_263_;
}
else
{
uint64_t v___x_558_; uint8_t v___x_559_; 
v___x_558_ = 9223372036854775808ULL;
v___x_559_ = lean_uint64_dec_lt(v___x_558_, v___x_544_);
if (v___x_559_ == 0)
{
v___y_264_ = v___y_539_;
v___y_265_ = v___x_550_;
v___y_266_ = v___y_541_;
v___y_267_ = v___x_550_;
goto v___jp_263_;
}
else
{
uint64_t v___x_560_; 
v___x_560_ = 1ULL;
v___y_264_ = v___y_539_;
v___y_265_ = v___x_550_;
v___y_266_ = v___y_541_;
v___y_267_ = v___x_560_;
goto v___jp_263_;
}
}
}
else
{
uint64_t v_quotient_561_; uint64_t v___x_562_; uint64_t v___x_563_; uint64_t v___x_564_; uint64_t v_remainder_565_; uint64_t v___x_566_; uint64_t v_half_567_; uint8_t v___x_568_; 
v_quotient_561_ = lean_uint64_shift_right(v___x_544_, v___x_553_);
v___x_562_ = 1ULL;
v___x_563_ = lean_uint64_shift_left(v___x_562_, v___x_553_);
v___x_564_ = lean_uint64_sub(v___x_563_, v___x_562_);
v_remainder_565_ = lean_uint64_land(v___x_544_, v___x_564_);
v___x_566_ = lean_uint64_sub(v___x_553_, v___x_562_);
v_half_567_ = lean_uint64_shift_left(v___x_562_, v___x_566_);
v___x_568_ = lean_uint64_dec_lt(v_remainder_565_, v_half_567_);
if (v___x_568_ == 0)
{
uint8_t v___x_569_; 
v___x_569_ = lean_uint64_dec_lt(v_half_567_, v_remainder_565_);
if (v___x_569_ == 0)
{
uint64_t v___x_570_; uint8_t v___x_571_; 
v___x_570_ = lean_uint64_land(v_quotient_561_, v___x_562_);
v___x_571_ = lean_uint64_dec_eq(v___x_570_, v___x_550_);
if (v___x_571_ == 0)
{
uint64_t v___x_572_; 
v___x_572_ = lean_uint64_add(v_quotient_561_, v___x_562_);
v___y_264_ = v___y_539_;
v___y_265_ = v___x_550_;
v___y_266_ = v___y_541_;
v___y_267_ = v___x_572_;
goto v___jp_263_;
}
else
{
v___y_264_ = v___y_539_;
v___y_265_ = v___x_550_;
v___y_266_ = v___y_541_;
v___y_267_ = v_quotient_561_;
goto v___jp_263_;
}
}
else
{
uint64_t v___x_573_; 
v___x_573_ = lean_uint64_add(v_quotient_561_, v___x_562_);
v___y_264_ = v___y_539_;
v___y_265_ = v___x_550_;
v___y_266_ = v___y_541_;
v___y_267_ = v___x_573_;
goto v___jp_263_;
}
}
else
{
v___y_264_ = v___y_539_;
v___y_265_ = v___x_550_;
v___y_266_ = v___y_541_;
v___y_267_ = v_quotient_561_;
goto v___jp_263_;
}
}
}
else
{
v___y_264_ = v___y_539_;
v___y_265_ = v___x_550_;
v___y_266_ = v___y_541_;
v___y_267_ = v___x_544_;
goto v___jp_263_;
}
}
else
{
if (v___y_541_ == 0)
{
uint32_t v___x_574_; 
v___x_574_ = 0;
return v___x_574_;
}
else
{
uint32_t v___x_575_; 
v___x_575_ = 2147483648;
return v___x_575_;
}
}
}
}
}
v___jp_579_:
{
uint64_t v___x_585_; uint64_t v___x_586_; uint8_t v___x_587_; 
v___x_585_ = lean_uint32_to_uint64(v_ey_578_);
v___x_586_ = 0ULL;
v___x_587_ = lean_uint64_dec_eq(v___x_585_, v___x_586_);
if (v___x_587_ == 0)
{
uint64_t v___x_588_; uint64_t v___x_589_; 
v___x_588_ = 1ULL;
v___x_589_ = lean_uint64_sub(v___x_585_, v___x_588_);
v___y_538_ = v___y_580_;
v___y_539_ = v___y_581_;
v___y_540_ = v___y_584_;
v___y_541_ = v___y_582_;
v___y_542_ = v___y_583_;
v___y_543_ = v___x_589_;
goto v___jp_537_;
}
else
{
v___y_538_ = v___y_580_;
v___y_539_ = v___y_581_;
v___y_540_ = v___y_584_;
v___y_541_ = v___y_582_;
v___y_542_ = v___y_583_;
v___y_543_ = v___x_586_;
goto v___jp_537_;
}
}
v___jp_590_:
{
uint64_t v___x_595_; uint64_t v___x_596_; uint8_t v___x_597_; 
v___x_595_ = lean_uint32_to_uint64(v_ex_576_);
v___x_596_ = 0ULL;
v___x_597_ = lean_uint64_dec_eq(v___x_595_, v___x_596_);
if (v___x_597_ == 0)
{
uint64_t v___x_598_; uint64_t v___x_599_; 
v___x_598_ = 1ULL;
v___x_599_ = lean_uint64_sub(v___x_595_, v___x_598_);
v___y_580_ = v___y_594_;
v___y_581_ = v___y_591_;
v___y_582_ = v___y_592_;
v___y_583_ = v___y_593_;
v___y_584_ = v___x_599_;
goto v___jp_579_;
}
else
{
v___y_580_ = v___y_594_;
v___y_581_ = v___y_591_;
v___y_582_ = v___y_592_;
v___y_583_ = v___y_593_;
v___y_584_ = v___x_596_;
goto v___jp_579_;
}
}
v___jp_600_:
{
uint32_t v___x_605_; uint8_t v___x_606_; 
v___x_605_ = 0;
v___x_606_ = lean_uint32_dec_eq(v_ey_578_, v___x_605_);
if (v___x_606_ == 0)
{
uint64_t v___x_607_; uint64_t v___x_608_; uint64_t v___x_609_; 
v___x_607_ = lean_uint32_to_uint64(v___y_602_);
v___x_608_ = 8388608ULL;
v___x_609_ = lean_uint64_lor(v___x_607_, v___x_608_);
v___y_591_ = v___y_601_;
v___y_592_ = v___y_603_;
v___y_593_ = v___y_604_;
v___y_594_ = v___x_609_;
goto v___jp_590_;
}
else
{
uint64_t v___x_610_; 
v___x_610_ = lean_uint32_to_uint64(v___y_602_);
v___y_591_ = v___y_601_;
v___y_592_ = v___y_603_;
v___y_593_ = v___y_604_;
v___y_594_ = v___x_610_;
goto v___jp_590_;
}
}
v___jp_611_:
{
uint32_t v___x_613_; uint32_t v_xFraction_614_; uint32_t v_yFraction_615_; uint32_t v___x_616_; uint8_t v___x_617_; 
v___x_613_ = 8388607;
v_xFraction_614_ = lean_uint32_land(v___y_131_, v___x_613_);
v_yFraction_615_ = lean_uint32_land(v___y_132_, v___x_613_);
v___x_616_ = 0;
v___x_617_ = lean_uint32_dec_eq(v_ex_576_, v___x_616_);
if (v___x_617_ == 0)
{
uint64_t v___x_618_; uint64_t v___x_619_; uint64_t v___x_620_; 
v___x_618_ = lean_uint32_to_uint64(v_xFraction_614_);
v___x_619_ = 8388608ULL;
v___x_620_ = lean_uint64_lor(v___x_618_, v___x_619_);
v___y_601_ = v___x_613_;
v___y_602_ = v_yFraction_615_;
v___y_603_ = v___y_612_;
v___y_604_ = v___x_620_;
goto v___jp_600_;
}
else
{
uint64_t v___x_621_; 
v___x_621_ = lean_uint32_to_uint64(v_xFraction_614_);
v___y_601_ = v___x_613_;
v___y_602_ = v_yFraction_615_;
v___y_603_ = v___y_612_;
v___y_604_ = v___x_621_;
goto v___jp_600_;
}
}
v___jp_622_:
{
if (v___y_624_ == 0)
{
v___y_612_ = v___x_130_;
goto v___jp_611_;
}
else
{
v___y_612_ = v___y_623_;
goto v___jp_611_;
}
}
v___jp_628_:
{
if (v___y_629_ == 0)
{
if (v___y_631_ == 0)
{
v___y_623_ = v___y_630_;
v___y_624_ = v___x_627_;
goto v___jp_622_;
}
else
{
v___y_612_ = v___x_130_;
goto v___jp_611_;
}
}
else
{
v___y_623_ = v___y_630_;
v___y_624_ = v___y_631_;
goto v___jp_622_;
}
}
v___jp_632_:
{
uint32_t v___x_635_; uint32_t v___x_636_; uint32_t v___x_637_; uint8_t v___x_638_; 
v___x_635_ = 2147483648;
v___x_636_ = lean_uint32_land(v___y_132_, v___x_635_);
v___x_637_ = 0;
v___x_638_ = lean_uint32_dec_eq(v___x_636_, v___x_637_);
if (v___x_638_ == 0)
{
v___y_629_ = v___y_634_;
v___y_630_ = v___y_633_;
v___y_631_ = v___x_130_;
goto v___jp_628_;
}
else
{
v___y_629_ = v___y_634_;
v___y_630_ = v___y_633_;
v___y_631_ = v___y_633_;
goto v___jp_628_;
}
}
v___jp_639_:
{
if (v___y_640_ == 0)
{
uint32_t v___x_641_; uint32_t v___x_642_; uint32_t v___x_643_; uint8_t v___x_644_; 
v___x_641_ = 2147483648;
v___x_642_ = lean_uint32_land(v___y_131_, v___x_641_);
v___x_643_ = 0;
v___x_644_ = lean_uint32_dec_eq(v___x_642_, v___x_643_);
if (v___x_644_ == 0)
{
v___y_633_ = v___y_640_;
v___y_634_ = v___x_130_;
goto v___jp_632_;
}
else
{
v___y_633_ = v___y_640_;
v___y_634_ = v___y_640_;
goto v___jp_632_;
}
}
else
{
lean_object* v___x_645_; lean_object* v___x_646_; lean_object* v___x_647_; uint32_t v___x_648_; 
v___x_645_ = lean_uint32_to_nat(v___y_131_);
v___x_646_ = lean_uint32_to_nat(v___y_132_);
v___x_647_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_645_, v___x_646_);
v___x_648_ = lean_uint32_of_nat(v___x_647_);
lean_dec(v___x_647_);
return v___x_648_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___x_663_, lean_object* v___y_664_, lean_object* v___y_665_){
_start:
{
uint8_t v___x_7484__boxed_666_; uint32_t v___y_7485__boxed_667_; uint32_t v___y_7486__boxed_668_; uint32_t v_res_669_; lean_object* v_r_670_; 
v___x_7484__boxed_666_ = lean_unbox(v___x_663_);
v___y_7485__boxed_667_ = lean_unbox_uint32(v___y_664_);
lean_dec(v___y_664_);
v___y_7486__boxed_668_ = lean_unbox_uint32(v___y_665_);
lean_dec(v___y_665_);
v_res_669_ = lp_competition_main___lam__1(v___x_7484__boxed_666_, v___y_7485__boxed_667_, v___y_7486__boxed_668_);
v_r_670_ = lean_box_uint32(v_res_669_);
return v_r_670_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint8_t v___x_671_, uint32_t v___y_672_, uint32_t v___y_673_){
_start:
{
uint8_t v___y_675_; uint8_t v___y_691_; uint8_t v___y_705_; uint8_t v___y_722_; float v___y_729_; float v___y_730_; float v___y_744_; uint8_t v___y_745_; float v___y_760_; uint32_t v___y_770_; uint32_t v___y_774_; uint32_t v___y_778_; uint32_t v___y_779_; uint32_t v___y_780_; uint8_t v___y_784_; uint32_t v___y_785_; uint64_t v___y_786_; uint64_t v___y_787_; uint32_t v___y_799_; uint32_t v___y_800_; uint32_t v___y_801_; uint8_t v___y_805_; uint32_t v___y_806_; uint64_t v___y_807_; uint64_t v___y_808_; uint32_t v___x_819_; uint32_t v___x_820_; uint8_t v___y_822_; uint32_t v___x_834_; uint32_t v___y_836_; uint32_t v___y_837_; uint32_t v___y_838_; uint32_t v___y_839_; uint8_t v___y_846_; uint32_t v___y_847_; uint32_t v___y_848_; uint32_t v___y_849_; uint8_t v___y_853_; uint32_t v___y_854_; uint64_t v___y_855_; uint64_t v___y_856_; uint64_t v___y_857_; uint8_t v___y_867_; uint32_t v___y_868_; uint64_t v___y_869_; uint64_t v___y_870_; uint8_t v___y_871_; uint64_t v___y_872_; uint8_t v___y_879_; uint64_t v___y_880_; uint32_t v___y_881_; uint64_t v___y_882_; uint64_t v___y_883_; uint8_t v___y_889_; uint64_t v___y_890_; uint32_t v___y_891_; uint64_t v___y_892_; uint64_t v___y_893_; uint64_t v___y_894_; uint64_t v___y_949_; uint8_t v___y_950_; uint32_t v___y_951_; uint64_t v___y_952_; uint64_t v___y_953_; uint64_t v___y_954_; uint64_t v___y_955_; uint8_t v___y_961_; uint64_t v___y_962_; uint32_t v___y_963_; uint64_t v___y_964_; uint64_t v___y_965_; uint64_t v___y_966_; uint64_t v___y_967_; uint64_t v___y_968_; uint64_t v___y_969_; uint64_t v___y_974_; uint8_t v___y_975_; uint32_t v___y_976_; uint64_t v___y_977_; uint64_t v___y_978_; uint64_t v___y_979_; uint64_t v___y_980_; uint8_t v___y_985_; uint64_t v___y_986_; uint64_t v___y_987_; uint32_t v___y_988_; uint64_t v___y_989_; uint64_t v___y_990_; uint64_t v___y_991_; uint64_t v___y_992_; uint64_t v___y_993_; uint64_t v___y_998_; uint8_t v___y_999_; uint32_t v___y_1000_; uint64_t v___y_1001_; uint64_t v___y_1002_; uint64_t v___y_1003_; uint64_t v___y_1004_; uint8_t v___y_1009_; uint64_t v___y_1010_; uint64_t v___y_1011_; uint32_t v___y_1012_; uint64_t v___y_1013_; uint64_t v___y_1014_; uint64_t v___y_1015_; uint64_t v___y_1016_; uint64_t v___y_1017_; uint64_t v___y_1022_; uint8_t v___y_1023_; uint64_t v___y_1024_; uint32_t v___y_1025_; uint64_t v___y_1026_; uint64_t v___y_1027_; uint64_t v___y_1028_; uint8_t v___y_1033_; uint64_t v___y_1034_; uint64_t v___y_1035_; uint32_t v___y_1036_; uint64_t v___y_1037_; uint64_t v___y_1038_; uint64_t v___y_1039_; uint64_t v___y_1040_; uint64_t v___y_1041_; uint64_t v___y_1046_; uint8_t v___y_1047_; uint64_t v___y_1048_; uint32_t v___y_1049_; uint64_t v___y_1050_; uint64_t v___y_1051_; uint64_t v___y_1052_; uint8_t v___y_1057_; uint64_t v___y_1058_; uint64_t v___y_1059_; uint32_t v___y_1060_; uint64_t v___y_1061_; uint64_t v___y_1062_; uint64_t v___y_1063_; uint64_t v___y_1067_; uint8_t v___y_1068_; uint32_t v___y_1069_; uint64_t v___y_1070_; uint8_t v___y_1079_; uint64_t v___y_1080_; uint32_t v___y_1081_; uint64_t v___y_1082_; uint64_t v___y_1083_; uint64_t v___y_1084_; uint32_t v_ex_1117_; uint32_t v___x_1118_; uint32_t v_ey_1119_; uint8_t v___y_1121_; uint64_t v___y_1122_; uint64_t v___y_1123_; uint32_t v___y_1124_; uint64_t v___y_1125_; uint8_t v___y_1132_; uint32_t v___y_1133_; uint64_t v___y_1134_; uint64_t v___y_1135_; uint8_t v___y_1142_; uint32_t v___y_1143_; uint32_t v___y_1144_; uint64_t v___y_1145_; uint8_t v___y_1153_; uint8_t v___y_1164_; uint8_t v___y_1165_; uint32_t v___x_1166_; uint32_t v___x_1167_; uint8_t v___x_1168_; uint8_t v___y_1170_; uint8_t v___y_1171_; uint8_t v___y_1172_; uint8_t v___y_1174_; uint8_t v___y_1175_; uint8_t v___y_1181_; 
v___x_819_ = 23;
v___x_820_ = lean_uint32_shift_right(v___y_672_, v___x_819_);
v___x_834_ = 255;
v_ex_1117_ = lean_uint32_land(v___x_820_, v___x_834_);
v___x_1118_ = lean_uint32_shift_right(v___y_673_, v___x_819_);
v_ey_1119_ = lean_uint32_land(v___x_1118_, v___x_834_);
v___x_1166_ = lean_uint32_add(v_ex_1117_, v_ey_1119_);
v___x_1167_ = 128;
v___x_1168_ = lean_uint32_dec_lt(v___x_1166_, v___x_1167_);
if (v___x_1168_ == 0)
{
uint32_t v___x_1190_; uint32_t v_a_1191_; uint32_t v___x_1192_; uint32_t v___x_1193_; uint32_t v___x_1194_; uint8_t v___x_1195_; 
v___x_1190_ = 2147483647;
v_a_1191_ = lean_uint32_land(v___y_672_, v___x_1190_);
v___x_1192_ = 201326591;
v___x_1193_ = 1;
v___x_1194_ = lean_uint32_sub(v_a_1191_, v___x_1193_);
v___x_1195_ = lean_uint32_dec_le(v___x_1192_, v___x_1194_);
if (v___x_1195_ == 0)
{
v___y_822_ = v___x_1195_;
goto v___jp_821_;
}
else
{
uint32_t v___x_1196_; uint8_t v___x_1197_; 
v___x_1196_ = 2139095040;
v___x_1197_ = lean_uint32_dec_lt(v_a_1191_, v___x_1196_);
v___y_822_ = v___x_1197_;
goto v___jp_821_;
}
}
else
{
uint32_t v___x_1198_; uint32_t v___x_1199_; uint32_t v___x_1200_; uint8_t v___x_1201_; 
v___x_1198_ = 4278190080;
v___x_1199_ = 1;
v___x_1200_ = lean_uint32_shift_left(v___y_672_, v___x_1199_);
v___x_1201_ = lean_uint32_dec_le(v___x_1198_, v___x_1200_);
if (v___x_1201_ == 0)
{
uint32_t v___x_1202_; uint8_t v___x_1203_; 
v___x_1202_ = lean_uint32_shift_left(v___y_673_, v___x_1199_);
v___x_1203_ = lean_uint32_dec_le(v___x_1198_, v___x_1202_);
v___y_1181_ = v___x_1203_;
goto v___jp_1180_;
}
else
{
v___y_1181_ = v___x_1201_;
goto v___jp_1180_;
}
}
v___jp_674_:
{
if (v___y_675_ == 0)
{
uint32_t v___x_676_; 
v___x_676_ = lp_competition_Submission_FastMul_mul(v___y_672_, v___y_673_);
return v___x_676_;
}
else
{
uint32_t v___x_677_; uint32_t v___x_678_; 
v___x_677_ = 4194304;
v___x_678_ = lean_uint32_lor(v___y_673_, v___x_677_);
return v___x_678_;
}
}
v___jp_679_:
{
uint32_t v___x_680_; uint32_t v___x_681_; uint32_t v___x_682_; uint32_t v___x_683_; uint8_t v___x_684_; 
v___x_680_ = 23;
v___x_681_ = lean_uint32_shift_right(v___y_673_, v___x_680_);
v___x_682_ = 255;
v___x_683_ = lean_uint32_land(v___x_681_, v___x_682_);
v___x_684_ = lean_uint32_dec_eq(v___x_683_, v___x_682_);
if (v___x_684_ == 0)
{
v___y_675_ = v___x_684_;
goto v___jp_674_;
}
else
{
uint32_t v___x_685_; uint32_t v___x_686_; uint32_t v___x_687_; uint8_t v___x_688_; 
v___x_685_ = 8388607;
v___x_686_ = lean_uint32_land(v___y_673_, v___x_685_);
v___x_687_ = 0;
v___x_688_ = lean_uint32_dec_eq(v___x_686_, v___x_687_);
if (v___x_688_ == 0)
{
v___y_675_ = v___x_684_;
goto v___jp_674_;
}
else
{
uint32_t v___x_689_; 
v___x_689_ = lp_competition_Submission_FastMul_mul(v___y_672_, v___y_673_);
return v___x_689_;
}
}
}
v___jp_690_:
{
if (v___y_691_ == 0)
{
goto v___jp_679_;
}
else
{
uint32_t v___x_692_; uint32_t v___x_693_; 
v___x_692_ = 4194304;
v___x_693_ = lean_uint32_lor(v___y_672_, v___x_692_);
return v___x_693_;
}
}
v___jp_694_:
{
uint32_t v___x_695_; uint32_t v___x_696_; uint32_t v___x_697_; uint32_t v___x_698_; uint8_t v___x_699_; 
v___x_695_ = 23;
v___x_696_ = lean_uint32_shift_right(v___y_672_, v___x_695_);
v___x_697_ = 255;
v___x_698_ = lean_uint32_land(v___x_696_, v___x_697_);
v___x_699_ = lean_uint32_dec_eq(v___x_698_, v___x_697_);
if (v___x_699_ == 0)
{
v___y_691_ = v___x_699_;
goto v___jp_690_;
}
else
{
uint32_t v___x_700_; uint32_t v___x_701_; uint32_t v___x_702_; uint8_t v___x_703_; 
v___x_700_ = 8388607;
v___x_701_ = lean_uint32_land(v___y_672_, v___x_700_);
v___x_702_ = 0;
v___x_703_ = lean_uint32_dec_eq(v___x_701_, v___x_702_);
if (v___x_703_ == 0)
{
v___y_691_ = v___x_699_;
goto v___jp_690_;
}
else
{
goto v___jp_679_;
}
}
}
v___jp_704_:
{
if (v___y_705_ == 0)
{
goto v___jp_694_;
}
else
{
uint32_t v___x_706_; uint32_t v___x_707_; uint32_t v___x_708_; uint8_t v___x_709_; 
v___x_706_ = 4194304;
v___x_707_ = lean_uint32_land(v___y_673_, v___x_706_);
v___x_708_ = 0;
v___x_709_ = lean_uint32_dec_eq(v___x_707_, v___x_708_);
if (v___x_709_ == 0)
{
goto v___jp_694_;
}
else
{
uint32_t v___x_710_; 
v___x_710_ = lean_uint32_lor(v___y_673_, v___x_706_);
return v___x_710_;
}
}
}
v___jp_711_:
{
uint32_t v___x_712_; uint32_t v___x_713_; uint32_t v___x_714_; uint32_t v___x_715_; uint8_t v___x_716_; 
v___x_712_ = 23;
v___x_713_ = lean_uint32_shift_right(v___y_673_, v___x_712_);
v___x_714_ = 255;
v___x_715_ = lean_uint32_land(v___x_713_, v___x_714_);
v___x_716_ = lean_uint32_dec_eq(v___x_715_, v___x_714_);
if (v___x_716_ == 0)
{
v___y_705_ = v___x_716_;
goto v___jp_704_;
}
else
{
uint32_t v___x_717_; uint32_t v___x_718_; uint32_t v___x_719_; uint8_t v___x_720_; 
v___x_717_ = 8388607;
v___x_718_ = lean_uint32_land(v___y_673_, v___x_717_);
v___x_719_ = 0;
v___x_720_ = lean_uint32_dec_eq(v___x_718_, v___x_719_);
if (v___x_720_ == 0)
{
v___y_705_ = v___x_716_;
goto v___jp_704_;
}
else
{
goto v___jp_694_;
}
}
}
v___jp_721_:
{
if (v___y_722_ == 0)
{
goto v___jp_711_;
}
else
{
uint32_t v___x_723_; uint32_t v___x_724_; uint32_t v___x_725_; uint8_t v___x_726_; 
v___x_723_ = 4194304;
v___x_724_ = lean_uint32_land(v___y_672_, v___x_723_);
v___x_725_ = 0;
v___x_726_ = lean_uint32_dec_eq(v___x_724_, v___x_725_);
if (v___x_726_ == 0)
{
goto v___jp_711_;
}
else
{
uint32_t v___x_727_; 
v___x_727_ = lean_uint32_lor(v___y_672_, v___x_723_);
return v___x_727_;
}
}
}
v___jp_728_:
{
float v_result_731_; uint8_t v___x_732_; 
v_result_731_ = lean_float32_mul(v___y_729_, v___y_730_);
v___x_732_ = lean_float32_beq(v_result_731_, v_result_731_);
if (v___x_732_ == 0)
{
uint32_t v___x_733_; uint32_t v___x_734_; uint32_t v___x_735_; uint32_t v___x_736_; uint8_t v___x_737_; 
v___x_733_ = 23;
v___x_734_ = lean_uint32_shift_right(v___y_672_, v___x_733_);
v___x_735_ = 255;
v___x_736_ = lean_uint32_land(v___x_734_, v___x_735_);
v___x_737_ = lean_uint32_dec_eq(v___x_736_, v___x_735_);
if (v___x_737_ == 0)
{
v___y_722_ = v___x_737_;
goto v___jp_721_;
}
else
{
uint32_t v___x_738_; uint32_t v___x_739_; uint32_t v___x_740_; uint8_t v___x_741_; 
v___x_738_ = 8388607;
v___x_739_ = lean_uint32_land(v___y_672_, v___x_738_);
v___x_740_ = 0;
v___x_741_ = lean_uint32_dec_eq(v___x_739_, v___x_740_);
if (v___x_741_ == 0)
{
v___y_722_ = v___x_737_;
goto v___jp_721_;
}
else
{
goto v___jp_711_;
}
}
}
else
{
uint32_t v___x_742_; 
v___x_742_ = lean_float32_to_bits(v_result_731_);
return v___x_742_;
}
}
v___jp_743_:
{
if (v___y_745_ == 0)
{
float v___x_746_; 
v___x_746_ = lean_float32_of_bits(v___y_673_);
v___y_729_ = v___y_744_;
v___y_730_ = v___x_746_;
goto v___jp_728_;
}
else
{
uint32_t v___x_747_; uint32_t v___x_748_; uint32_t v___x_749_; uint32_t v___x_750_; float v___x_751_; lean_object* v___x_752_; uint32_t v___x_753_; uint32_t v___x_754_; lean_object* v___x_755_; lean_object* v___x_756_; float v___x_757_; float v___x_758_; 
v___x_747_ = 8388607;
v___x_748_ = lean_uint32_land(v___y_673_, v___x_747_);
v___x_749_ = 8388608;
v___x_750_ = lean_uint32_lor(v___x_748_, v___x_749_);
v___x_751_ = lean_uint32_to_float32(v___x_750_);
v___x_752_ = lp_competition_R2W01b_scaleTable;
v___x_753_ = 23;
v___x_754_ = lean_uint32_shift_right(v___y_673_, v___x_753_);
v___x_755_ = lean_uint32_to_nat(v___x_754_);
v___x_756_ = lean_array_fget_borrowed(v___x_752_, v___x_755_);
lean_dec(v___x_755_);
v___x_757_ = lean_unbox_float32(v___x_756_);
v___x_758_ = lean_float32_mul(v___x_751_, v___x_757_);
v___y_729_ = v___y_744_;
v___y_730_ = v___x_758_;
goto v___jp_728_;
}
}
v___jp_759_:
{
uint32_t v___x_761_; uint32_t v_a_762_; uint32_t v___x_763_; uint32_t v___x_764_; uint32_t v___x_765_; uint8_t v___x_766_; 
v___x_761_ = 2147483647;
v_a_762_ = lean_uint32_land(v___y_673_, v___x_761_);
v___x_763_ = 201326591;
v___x_764_ = 1;
v___x_765_ = lean_uint32_sub(v_a_762_, v___x_764_);
v___x_766_ = lean_uint32_dec_le(v___x_763_, v___x_765_);
if (v___x_766_ == 0)
{
v___y_744_ = v___y_760_;
v___y_745_ = v___x_766_;
goto v___jp_743_;
}
else
{
uint32_t v___x_767_; uint8_t v___x_768_; 
v___x_767_ = 2139095040;
v___x_768_ = lean_uint32_dec_lt(v_a_762_, v___x_767_);
v___y_744_ = v___y_760_;
v___y_745_ = v___x_768_;
goto v___jp_743_;
}
}
v___jp_769_:
{
uint32_t v___x_771_; uint32_t v___x_772_; 
v___x_771_ = 8388608;
v___x_772_ = lean_uint32_lor(v___y_770_, v___x_771_);
return v___x_772_;
}
v___jp_773_:
{
uint32_t v___x_775_; uint32_t v___x_776_; 
v___x_775_ = 8388608;
v___x_776_ = lean_uint32_lor(v___y_774_, v___x_775_);
return v___x_776_;
}
v___jp_777_:
{
uint32_t v___x_781_; uint32_t v___x_782_; 
v___x_781_ = lean_uint32_land(v___y_779_, v___y_778_);
v___x_782_ = lean_uint32_lor(v___y_780_, v___x_781_);
return v___x_782_;
}
v___jp_783_:
{
uint8_t v___x_788_; 
v___x_788_ = lean_uint64_dec_eq(v___y_787_, v___y_786_);
if (v___x_788_ == 0)
{
uint64_t v___x_789_; uint8_t v___x_790_; 
v___x_789_ = 8388608ULL;
v___x_790_ = lean_uint64_dec_eq(v___y_787_, v___x_789_);
if (v___x_790_ == 0)
{
uint32_t v___x_791_; 
v___x_791_ = lean_uint64_to_uint32(v___y_787_);
if (v___y_784_ == 0)
{
uint32_t v___x_792_; 
v___x_792_ = 0;
v___y_778_ = v___y_785_;
v___y_779_ = v___x_791_;
v___y_780_ = v___x_792_;
goto v___jp_777_;
}
else
{
uint32_t v___x_793_; 
v___x_793_ = 2147483648;
v___y_778_ = v___y_785_;
v___y_779_ = v___x_791_;
v___y_780_ = v___x_793_;
goto v___jp_777_;
}
}
else
{
if (v___y_784_ == 0)
{
uint32_t v___x_794_; 
v___x_794_ = 0;
v___y_774_ = v___x_794_;
goto v___jp_773_;
}
else
{
uint32_t v___x_795_; 
v___x_795_ = 2147483648;
v___y_774_ = v___x_795_;
goto v___jp_773_;
}
}
}
else
{
if (v___y_784_ == 0)
{
uint32_t v___x_796_; 
v___x_796_ = 0;
return v___x_796_;
}
else
{
uint32_t v___x_797_; 
v___x_797_ = 2147483648;
return v___x_797_;
}
}
}
v___jp_798_:
{
uint32_t v___x_802_; uint32_t v___x_803_; 
v___x_802_ = lean_uint32_land(v___y_800_, v___y_799_);
v___x_803_ = lean_uint32_lor(v___y_801_, v___x_802_);
return v___x_803_;
}
v___jp_804_:
{
uint8_t v___x_809_; 
v___x_809_ = lean_uint64_dec_eq(v___y_808_, v___y_807_);
if (v___x_809_ == 0)
{
uint64_t v___x_810_; uint8_t v___x_811_; 
v___x_810_ = 8388608ULL;
v___x_811_ = lean_uint64_dec_eq(v___y_808_, v___x_810_);
if (v___x_811_ == 0)
{
uint32_t v___x_812_; 
v___x_812_ = lean_uint64_to_uint32(v___y_808_);
if (v___y_805_ == 0)
{
uint32_t v___x_813_; 
v___x_813_ = 0;
v___y_799_ = v___y_806_;
v___y_800_ = v___x_812_;
v___y_801_ = v___x_813_;
goto v___jp_798_;
}
else
{
uint32_t v___x_814_; 
v___x_814_ = 2147483648;
v___y_799_ = v___y_806_;
v___y_800_ = v___x_812_;
v___y_801_ = v___x_814_;
goto v___jp_798_;
}
}
else
{
if (v___y_805_ == 0)
{
uint32_t v___x_815_; 
v___x_815_ = 0;
v___y_770_ = v___x_815_;
goto v___jp_769_;
}
else
{
uint32_t v___x_816_; 
v___x_816_ = 2147483648;
v___y_770_ = v___x_816_;
goto v___jp_769_;
}
}
}
else
{
if (v___y_805_ == 0)
{
uint32_t v___x_817_; 
v___x_817_ = 0;
return v___x_817_;
}
else
{
uint32_t v___x_818_; 
v___x_818_ = 2147483648;
return v___x_818_;
}
}
}
v___jp_821_:
{
if (v___y_822_ == 0)
{
float v___x_823_; 
v___x_823_ = lean_float32_of_bits(v___y_672_);
v___y_760_ = v___x_823_;
goto v___jp_759_;
}
else
{
uint32_t v___x_824_; uint32_t v___x_825_; uint32_t v___x_826_; uint32_t v___x_827_; float v___x_828_; lean_object* v___x_829_; lean_object* v___x_830_; lean_object* v___x_831_; float v___x_832_; float v___x_833_; 
v___x_824_ = 8388607;
v___x_825_ = lean_uint32_land(v___y_672_, v___x_824_);
v___x_826_ = 8388608;
v___x_827_ = lean_uint32_lor(v___x_825_, v___x_826_);
v___x_828_ = lean_uint32_to_float32(v___x_827_);
v___x_829_ = lp_competition_R2W01b_scaleTable;
v___x_830_ = lean_uint32_to_nat(v___x_820_);
v___x_831_ = lean_array_fget_borrowed(v___x_829_, v___x_830_);
lean_dec(v___x_830_);
v___x_832_ = lean_unbox_float32(v___x_831_);
v___x_833_ = lean_float32_mul(v___x_828_, v___x_832_);
v___y_760_ = v___x_833_;
goto v___jp_759_;
}
}
v___jp_835_:
{
uint32_t v___x_840_; uint32_t v___x_841_; uint32_t v___x_842_; uint32_t v___x_843_; uint32_t v___x_844_; 
v___x_840_ = lean_uint32_land(v___y_836_, v___x_834_);
v___x_841_ = lean_uint32_shift_left(v___x_840_, v___x_819_);
v___x_842_ = lean_uint32_lor(v___y_839_, v___x_841_);
v___x_843_ = lean_uint32_land(v___y_838_, v___y_837_);
v___x_844_ = lean_uint32_lor(v___x_842_, v___x_843_);
return v___x_844_;
}
v___jp_845_:
{
if (v___y_846_ == 0)
{
uint32_t v___x_850_; 
v___x_850_ = 0;
v___y_836_ = v___y_847_;
v___y_837_ = v___y_848_;
v___y_838_ = v___y_849_;
v___y_839_ = v___x_850_;
goto v___jp_835_;
}
else
{
uint32_t v___x_851_; 
v___x_851_ = 2147483648;
v___y_836_ = v___y_847_;
v___y_837_ = v___y_848_;
v___y_838_ = v___y_849_;
v___y_839_ = v___x_851_;
goto v___jp_835_;
}
}
v___jp_852_:
{
uint64_t v___x_858_; uint64_t v_encodedExponent_859_; uint32_t v___x_860_; uint64_t v___x_861_; uint8_t v___x_862_; 
v___x_858_ = 171ULL;
v_encodedExponent_859_ = lean_uint64_sub(v___y_856_, v___x_858_);
v___x_860_ = lean_uint64_to_uint32(v_encodedExponent_859_);
v___x_861_ = 8388608ULL;
v___x_862_ = lean_uint64_dec_lt(v___y_857_, v___x_861_);
if (v___x_862_ == 0)
{
uint64_t v___x_863_; uint32_t v___x_864_; 
v___x_863_ = lean_uint64_sub(v___y_857_, v___x_861_);
v___x_864_ = lean_uint64_to_uint32(v___x_863_);
v___y_846_ = v___y_853_;
v___y_847_ = v___x_860_;
v___y_848_ = v___y_854_;
v___y_849_ = v___x_864_;
goto v___jp_845_;
}
else
{
uint32_t v___x_865_; 
v___x_865_ = lean_uint64_to_uint32(v___y_855_);
v___y_846_ = v___y_853_;
v___y_847_ = v___x_860_;
v___y_848_ = v___y_854_;
v___y_849_ = v___x_865_;
goto v___jp_845_;
}
}
v___jp_866_:
{
uint64_t v___x_873_; uint8_t v___x_874_; 
v___x_873_ = 425ULL;
v___x_874_ = lean_uint64_dec_lt(v___x_873_, v___y_872_);
if (v___x_874_ == 0)
{
if (v___y_871_ == 0)
{
v___y_853_ = v___y_867_;
v___y_854_ = v___y_868_;
v___y_855_ = v___y_869_;
v___y_856_ = v___y_872_;
v___y_857_ = v___y_870_;
goto v___jp_852_;
}
else
{
uint64_t v___x_875_; 
v___x_875_ = 8388608ULL;
v___y_853_ = v___y_867_;
v___y_854_ = v___y_868_;
v___y_855_ = v___y_869_;
v___y_856_ = v___y_872_;
v___y_857_ = v___x_875_;
goto v___jp_852_;
}
}
else
{
if (v___y_867_ == 0)
{
uint32_t v___x_876_; 
v___x_876_ = 2139095040;
return v___x_876_;
}
else
{
uint32_t v___x_877_; 
v___x_877_ = 4286578688;
return v___x_877_;
}
}
}
v___jp_878_:
{
uint64_t v___x_884_; uint8_t v_carry_885_; 
v___x_884_ = 16777216ULL;
v_carry_885_ = lean_uint64_dec_eq(v___y_883_, v___x_884_);
if (v_carry_885_ == 0)
{
v___y_867_ = v___y_879_;
v___y_868_ = v___y_881_;
v___y_869_ = v___y_882_;
v___y_870_ = v___y_883_;
v___y_871_ = v_carry_885_;
v___y_872_ = v___y_880_;
goto v___jp_866_;
}
else
{
uint64_t v___x_886_; uint64_t v___x_887_; 
v___x_886_ = 1ULL;
v___x_887_ = lean_uint64_add(v___y_880_, v___x_886_);
v___y_867_ = v___y_879_;
v___y_868_ = v___y_881_;
v___y_869_ = v___y_882_;
v___y_870_ = v___y_883_;
v___y_871_ = v_carry_885_;
v___y_872_ = v___x_887_;
goto v___jp_866_;
}
}
v___jp_888_:
{
uint64_t v_position_895_; uint64_t v___x_896_; uint8_t v___x_897_; 
v_position_895_ = lean_uint64_add(v___y_894_, v___y_890_);
v___x_896_ = 172ULL;
v___x_897_ = lean_uint64_dec_lt(v_position_895_, v___x_896_);
if (v___x_897_ == 0)
{
uint64_t v___x_898_; uint8_t v___x_899_; 
v___x_898_ = 23ULL;
v___x_899_ = lean_uint64_dec_lt(v___y_894_, v___x_898_);
if (v___x_899_ == 0)
{
uint64_t v___x_900_; uint8_t v___x_901_; 
v___x_900_ = lean_uint64_sub(v___y_894_, v___x_898_);
v___x_901_ = lean_uint64_dec_eq(v___x_900_, v___y_892_);
if (v___x_901_ == 0)
{
uint64_t v___x_902_; uint8_t v___x_903_; 
v___x_902_ = 64ULL;
v___x_903_ = lean_uint64_dec_lt(v___x_900_, v___x_902_);
if (v___x_903_ == 0)
{
uint8_t v___x_904_; 
v___x_904_ = lean_uint64_dec_eq(v___x_900_, v___x_902_);
if (v___x_904_ == 0)
{
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v___y_892_;
goto v___jp_878_;
}
else
{
uint64_t v___x_905_; uint8_t v___x_906_; 
v___x_905_ = 9223372036854775808ULL;
v___x_906_ = lean_uint64_dec_lt(v___x_905_, v___y_893_);
if (v___x_906_ == 0)
{
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v___y_892_;
goto v___jp_878_;
}
else
{
uint64_t v___x_907_; 
v___x_907_ = 1ULL;
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v___x_907_;
goto v___jp_878_;
}
}
}
else
{
uint64_t v_quotient_908_; uint64_t v___x_909_; uint64_t v___x_910_; uint64_t v___x_911_; uint64_t v_remainder_912_; uint64_t v___x_913_; uint64_t v_half_914_; uint8_t v___x_915_; 
v_quotient_908_ = lean_uint64_shift_right(v___y_893_, v___x_900_);
v___x_909_ = 1ULL;
v___x_910_ = lean_uint64_shift_left(v___x_909_, v___x_900_);
v___x_911_ = lean_uint64_sub(v___x_910_, v___x_909_);
v_remainder_912_ = lean_uint64_land(v___y_893_, v___x_911_);
v___x_913_ = lean_uint64_sub(v___x_900_, v___x_909_);
v_half_914_ = lean_uint64_shift_left(v___x_909_, v___x_913_);
v___x_915_ = lean_uint64_dec_lt(v_remainder_912_, v_half_914_);
if (v___x_915_ == 0)
{
uint8_t v___x_916_; 
v___x_916_ = lean_uint64_dec_lt(v_half_914_, v_remainder_912_);
if (v___x_916_ == 0)
{
uint64_t v___x_917_; uint8_t v___x_918_; 
v___x_917_ = lean_uint64_land(v_quotient_908_, v___x_909_);
v___x_918_ = lean_uint64_dec_eq(v___x_917_, v___y_892_);
if (v___x_918_ == 0)
{
uint64_t v___x_919_; 
v___x_919_ = lean_uint64_add(v_quotient_908_, v___x_909_);
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v___x_919_;
goto v___jp_878_;
}
else
{
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v_quotient_908_;
goto v___jp_878_;
}
}
else
{
uint64_t v___x_920_; 
v___x_920_ = lean_uint64_add(v_quotient_908_, v___x_909_);
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v___x_920_;
goto v___jp_878_;
}
}
else
{
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v_quotient_908_;
goto v___jp_878_;
}
}
}
else
{
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v___y_893_;
goto v___jp_878_;
}
}
else
{
uint64_t v___x_921_; uint64_t v___x_922_; 
v___x_921_ = lean_uint64_sub(v___x_898_, v___y_894_);
v___x_922_ = lean_uint64_shift_left(v___y_893_, v___x_921_);
v___y_879_ = v___y_889_;
v___y_880_ = v_position_895_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_892_;
v___y_883_ = v___x_922_;
goto v___jp_878_;
}
}
else
{
uint64_t v___x_923_; uint8_t v___x_924_; 
v___x_923_ = 149ULL;
v___x_924_ = lean_uint64_dec_lt(v___y_890_, v___x_923_);
if (v___x_924_ == 0)
{
uint64_t v___x_925_; uint64_t v___x_926_; 
v___x_925_ = lean_uint64_sub(v___y_890_, v___x_923_);
v___x_926_ = lean_uint64_shift_left(v___y_893_, v___x_925_);
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v___x_926_;
goto v___jp_783_;
}
else
{
uint64_t v___x_927_; uint8_t v___x_928_; 
v___x_927_ = lean_uint64_sub(v___x_923_, v___y_890_);
v___x_928_ = lean_uint64_dec_eq(v___x_927_, v___y_892_);
if (v___x_928_ == 0)
{
uint64_t v___x_929_; uint8_t v___x_930_; 
v___x_929_ = 64ULL;
v___x_930_ = lean_uint64_dec_lt(v___x_927_, v___x_929_);
if (v___x_930_ == 0)
{
uint8_t v___x_931_; 
v___x_931_ = lean_uint64_dec_eq(v___x_927_, v___x_929_);
if (v___x_931_ == 0)
{
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v___y_892_;
goto v___jp_783_;
}
else
{
uint64_t v___x_932_; uint8_t v___x_933_; 
v___x_932_ = 9223372036854775808ULL;
v___x_933_ = lean_uint64_dec_lt(v___x_932_, v___y_893_);
if (v___x_933_ == 0)
{
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v___y_892_;
goto v___jp_783_;
}
else
{
uint64_t v___x_934_; 
v___x_934_ = 1ULL;
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v___x_934_;
goto v___jp_783_;
}
}
}
else
{
uint64_t v_quotient_935_; uint64_t v___x_936_; uint64_t v___x_937_; uint64_t v___x_938_; uint64_t v_remainder_939_; uint64_t v___x_940_; uint64_t v_half_941_; uint8_t v___x_942_; 
v_quotient_935_ = lean_uint64_shift_right(v___y_893_, v___x_927_);
v___x_936_ = 1ULL;
v___x_937_ = lean_uint64_shift_left(v___x_936_, v___x_927_);
v___x_938_ = lean_uint64_sub(v___x_937_, v___x_936_);
v_remainder_939_ = lean_uint64_land(v___y_893_, v___x_938_);
v___x_940_ = lean_uint64_sub(v___x_927_, v___x_936_);
v_half_941_ = lean_uint64_shift_left(v___x_936_, v___x_940_);
v___x_942_ = lean_uint64_dec_lt(v_remainder_939_, v_half_941_);
if (v___x_942_ == 0)
{
uint8_t v___x_943_; 
v___x_943_ = lean_uint64_dec_lt(v_half_941_, v_remainder_939_);
if (v___x_943_ == 0)
{
uint64_t v___x_944_; uint8_t v___x_945_; 
v___x_944_ = lean_uint64_land(v_quotient_935_, v___x_936_);
v___x_945_ = lean_uint64_dec_eq(v___x_944_, v___y_892_);
if (v___x_945_ == 0)
{
uint64_t v___x_946_; 
v___x_946_ = lean_uint64_add(v_quotient_935_, v___x_936_);
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v___x_946_;
goto v___jp_783_;
}
else
{
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v_quotient_935_;
goto v___jp_783_;
}
}
else
{
uint64_t v___x_947_; 
v___x_947_ = lean_uint64_add(v_quotient_935_, v___x_936_);
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v___x_947_;
goto v___jp_783_;
}
}
else
{
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v_quotient_935_;
goto v___jp_783_;
}
}
}
else
{
v___y_784_ = v___y_889_;
v___y_785_ = v___y_891_;
v___y_786_ = v___y_892_;
v___y_787_ = v___y_893_;
goto v___jp_783_;
}
}
}
}
v___jp_948_:
{
uint64_t v___x_956_; uint64_t v___x_957_; uint8_t v___x_958_; 
v___x_956_ = 1ULL;
v___x_957_ = lean_uint64_shift_right(v___y_953_, v___x_956_);
v___x_958_ = lean_uint64_dec_eq(v___x_957_, v___y_952_);
if (v___x_958_ == 0)
{
uint64_t v___x_959_; 
v___x_959_ = lean_uint64_add(v___y_955_, v___x_956_);
v___y_889_ = v___y_950_;
v___y_890_ = v___y_949_;
v___y_891_ = v___y_951_;
v___y_892_ = v___y_952_;
v___y_893_ = v___y_954_;
v___y_894_ = v___x_959_;
goto v___jp_888_;
}
else
{
v___y_889_ = v___y_950_;
v___y_890_ = v___y_949_;
v___y_891_ = v___y_951_;
v___y_892_ = v___y_952_;
v___y_893_ = v___y_954_;
v___y_894_ = v___y_955_;
goto v___jp_888_;
}
}
v___jp_960_:
{
uint64_t v___x_970_; uint8_t v___x_971_; 
v___x_970_ = lean_uint64_shift_right(v___y_964_, v___y_965_);
v___x_971_ = lean_uint64_dec_eq(v___x_970_, v___y_966_);
if (v___x_971_ == 0)
{
uint64_t v___x_972_; 
v___x_972_ = lean_uint64_add(v___y_967_, v___y_965_);
v___y_949_ = v___y_962_;
v___y_950_ = v___y_961_;
v___y_951_ = v___y_963_;
v___y_952_ = v___y_966_;
v___y_953_ = v___y_969_;
v___y_954_ = v___y_968_;
v___y_955_ = v___x_972_;
goto v___jp_948_;
}
else
{
v___y_949_ = v___y_962_;
v___y_950_ = v___y_961_;
v___y_951_ = v___y_963_;
v___y_952_ = v___y_966_;
v___y_953_ = v___y_969_;
v___y_954_ = v___y_968_;
v___y_955_ = v___y_967_;
goto v___jp_948_;
}
}
v___jp_973_:
{
uint64_t v___x_981_; uint64_t v___x_982_; uint8_t v___x_983_; 
v___x_981_ = 2ULL;
v___x_982_ = lean_uint64_shift_right(v___y_977_, v___x_981_);
v___x_983_ = lean_uint64_dec_eq(v___x_982_, v___y_978_);
if (v___x_983_ == 0)
{
v___y_961_ = v___y_975_;
v___y_962_ = v___y_974_;
v___y_963_ = v___y_976_;
v___y_964_ = v___y_977_;
v___y_965_ = v___x_981_;
v___y_966_ = v___y_978_;
v___y_967_ = v___y_980_;
v___y_968_ = v___y_979_;
v___y_969_ = v___x_982_;
goto v___jp_960_;
}
else
{
v___y_961_ = v___y_975_;
v___y_962_ = v___y_974_;
v___y_963_ = v___y_976_;
v___y_964_ = v___y_977_;
v___y_965_ = v___x_981_;
v___y_966_ = v___y_978_;
v___y_967_ = v___y_980_;
v___y_968_ = v___y_979_;
v___y_969_ = v___y_977_;
goto v___jp_960_;
}
}
v___jp_984_:
{
uint64_t v___x_994_; uint8_t v___x_995_; 
v___x_994_ = lean_uint64_shift_right(v___y_989_, v___y_987_);
v___x_995_ = lean_uint64_dec_eq(v___x_994_, v___y_990_);
if (v___x_995_ == 0)
{
uint64_t v___x_996_; 
v___x_996_ = lean_uint64_add(v___y_991_, v___y_987_);
v___y_974_ = v___y_986_;
v___y_975_ = v___y_985_;
v___y_976_ = v___y_988_;
v___y_977_ = v___y_993_;
v___y_978_ = v___y_990_;
v___y_979_ = v___y_992_;
v___y_980_ = v___x_996_;
goto v___jp_973_;
}
else
{
v___y_974_ = v___y_986_;
v___y_975_ = v___y_985_;
v___y_976_ = v___y_988_;
v___y_977_ = v___y_993_;
v___y_978_ = v___y_990_;
v___y_979_ = v___y_992_;
v___y_980_ = v___y_991_;
goto v___jp_973_;
}
}
v___jp_997_:
{
uint64_t v___x_1005_; uint64_t v___x_1006_; uint8_t v___x_1007_; 
v___x_1005_ = 4ULL;
v___x_1006_ = lean_uint64_shift_right(v___y_1001_, v___x_1005_);
v___x_1007_ = lean_uint64_dec_eq(v___x_1006_, v___y_1002_);
if (v___x_1007_ == 0)
{
v___y_985_ = v___y_999_;
v___y_986_ = v___y_998_;
v___y_987_ = v___x_1005_;
v___y_988_ = v___y_1000_;
v___y_989_ = v___y_1001_;
v___y_990_ = v___y_1002_;
v___y_991_ = v___y_1004_;
v___y_992_ = v___y_1003_;
v___y_993_ = v___x_1006_;
goto v___jp_984_;
}
else
{
v___y_985_ = v___y_999_;
v___y_986_ = v___y_998_;
v___y_987_ = v___x_1005_;
v___y_988_ = v___y_1000_;
v___y_989_ = v___y_1001_;
v___y_990_ = v___y_1002_;
v___y_991_ = v___y_1004_;
v___y_992_ = v___y_1003_;
v___y_993_ = v___y_1001_;
goto v___jp_984_;
}
}
v___jp_1008_:
{
uint64_t v___x_1018_; uint8_t v___x_1019_; 
v___x_1018_ = lean_uint64_shift_right(v___y_1011_, v___y_1014_);
v___x_1019_ = lean_uint64_dec_eq(v___x_1018_, v___y_1013_);
if (v___x_1019_ == 0)
{
uint64_t v___x_1020_; 
v___x_1020_ = lean_uint64_add(v___y_1016_, v___y_1014_);
v___y_998_ = v___y_1010_;
v___y_999_ = v___y_1009_;
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1017_;
v___y_1002_ = v___y_1013_;
v___y_1003_ = v___y_1015_;
v___y_1004_ = v___x_1020_;
goto v___jp_997_;
}
else
{
v___y_998_ = v___y_1010_;
v___y_999_ = v___y_1009_;
v___y_1000_ = v___y_1012_;
v___y_1001_ = v___y_1017_;
v___y_1002_ = v___y_1013_;
v___y_1003_ = v___y_1015_;
v___y_1004_ = v___y_1016_;
goto v___jp_997_;
}
}
v___jp_1021_:
{
uint64_t v___x_1029_; uint64_t v___x_1030_; uint8_t v___x_1031_; 
v___x_1029_ = 8ULL;
v___x_1030_ = lean_uint64_shift_right(v___y_1024_, v___x_1029_);
v___x_1031_ = lean_uint64_dec_eq(v___x_1030_, v___y_1026_);
if (v___x_1031_ == 0)
{
v___y_1009_ = v___y_1023_;
v___y_1010_ = v___y_1022_;
v___y_1011_ = v___y_1024_;
v___y_1012_ = v___y_1025_;
v___y_1013_ = v___y_1026_;
v___y_1014_ = v___x_1029_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1028_;
v___y_1017_ = v___x_1030_;
goto v___jp_1008_;
}
else
{
v___y_1009_ = v___y_1023_;
v___y_1010_ = v___y_1022_;
v___y_1011_ = v___y_1024_;
v___y_1012_ = v___y_1025_;
v___y_1013_ = v___y_1026_;
v___y_1014_ = v___x_1029_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1028_;
v___y_1017_ = v___y_1024_;
goto v___jp_1008_;
}
}
v___jp_1032_:
{
uint64_t v___x_1042_; uint8_t v___x_1043_; 
v___x_1042_ = lean_uint64_shift_right(v___y_1035_, v___y_1037_);
v___x_1043_ = lean_uint64_dec_eq(v___x_1042_, v___y_1038_);
if (v___x_1043_ == 0)
{
uint64_t v___x_1044_; 
v___x_1044_ = lean_uint64_add(v___y_1040_, v___y_1037_);
v___y_1022_ = v___y_1034_;
v___y_1023_ = v___y_1033_;
v___y_1024_ = v___y_1041_;
v___y_1025_ = v___y_1036_;
v___y_1026_ = v___y_1038_;
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___x_1044_;
goto v___jp_1021_;
}
else
{
v___y_1022_ = v___y_1034_;
v___y_1023_ = v___y_1033_;
v___y_1024_ = v___y_1041_;
v___y_1025_ = v___y_1036_;
v___y_1026_ = v___y_1038_;
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1040_;
goto v___jp_1021_;
}
}
v___jp_1045_:
{
uint64_t v___x_1053_; uint64_t v___x_1054_; uint8_t v___x_1055_; 
v___x_1053_ = 16ULL;
v___x_1054_ = lean_uint64_shift_right(v___y_1048_, v___x_1053_);
v___x_1055_ = lean_uint64_dec_eq(v___x_1054_, v___y_1050_);
if (v___x_1055_ == 0)
{
v___y_1033_ = v___y_1047_;
v___y_1034_ = v___y_1046_;
v___y_1035_ = v___y_1048_;
v___y_1036_ = v___y_1049_;
v___y_1037_ = v___x_1053_;
v___y_1038_ = v___y_1050_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___x_1054_;
goto v___jp_1032_;
}
else
{
v___y_1033_ = v___y_1047_;
v___y_1034_ = v___y_1046_;
v___y_1035_ = v___y_1048_;
v___y_1036_ = v___y_1049_;
v___y_1037_ = v___x_1053_;
v___y_1038_ = v___y_1050_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___y_1048_;
goto v___jp_1032_;
}
}
v___jp_1056_:
{
uint64_t v___x_1064_; uint8_t v___x_1065_; 
v___x_1064_ = lean_uint64_shift_right(v___y_1062_, v___y_1059_);
v___x_1065_ = lean_uint64_dec_eq(v___x_1064_, v___y_1061_);
if (v___x_1065_ == 0)
{
v___y_1046_ = v___y_1058_;
v___y_1047_ = v___y_1057_;
v___y_1048_ = v___y_1063_;
v___y_1049_ = v___y_1060_;
v___y_1050_ = v___y_1061_;
v___y_1051_ = v___y_1062_;
v___y_1052_ = v___y_1059_;
goto v___jp_1045_;
}
else
{
v___y_1046_ = v___y_1058_;
v___y_1047_ = v___y_1057_;
v___y_1048_ = v___y_1063_;
v___y_1049_ = v___y_1060_;
v___y_1050_ = v___y_1061_;
v___y_1051_ = v___y_1062_;
v___y_1052_ = v___y_1061_;
goto v___jp_1045_;
}
}
v___jp_1066_:
{
uint64_t v___x_1071_; uint8_t v___x_1072_; 
v___x_1071_ = 0ULL;
v___x_1072_ = lean_uint64_dec_eq(v___y_1070_, v___x_1071_);
if (v___x_1072_ == 0)
{
uint64_t v___x_1073_; uint64_t v___x_1074_; uint8_t v___x_1075_; 
v___x_1073_ = 32ULL;
v___x_1074_ = lean_uint64_shift_right(v___y_1070_, v___x_1073_);
v___x_1075_ = lean_uint64_dec_eq(v___x_1074_, v___x_1071_);
if (v___x_1075_ == 0)
{
v___y_1057_ = v___y_1068_;
v___y_1058_ = v___y_1067_;
v___y_1059_ = v___x_1073_;
v___y_1060_ = v___y_1069_;
v___y_1061_ = v___x_1071_;
v___y_1062_ = v___y_1070_;
v___y_1063_ = v___x_1074_;
goto v___jp_1056_;
}
else
{
v___y_1057_ = v___y_1068_;
v___y_1058_ = v___y_1067_;
v___y_1059_ = v___x_1073_;
v___y_1060_ = v___y_1069_;
v___y_1061_ = v___x_1071_;
v___y_1062_ = v___y_1070_;
v___y_1063_ = v___y_1070_;
goto v___jp_1056_;
}
}
else
{
if (v___y_1068_ == 0)
{
uint32_t v___x_1076_; 
v___x_1076_ = 0;
return v___x_1076_;
}
else
{
uint32_t v___x_1077_; 
v___x_1077_ = 2147483648;
return v___x_1077_;
}
}
}
v___jp_1078_:
{
uint64_t v___x_1085_; uint64_t v___x_1086_; uint64_t v___x_1087_; uint8_t v___x_1088_; 
v___x_1085_ = lean_uint64_mul(v___y_1082_, v___y_1080_);
v___x_1086_ = lean_uint64_add(v___y_1083_, v___y_1084_);
v___x_1087_ = 281474976710656ULL;
v___x_1088_ = lean_uint64_dec_lt(v___x_1085_, v___x_1087_);
if (v___x_1088_ == 0)
{
v___y_1067_ = v___x_1086_;
v___y_1068_ = v___y_1079_;
v___y_1069_ = v___y_1081_;
v___y_1070_ = v___x_1085_;
goto v___jp_1066_;
}
else
{
uint64_t v___x_1089_; uint8_t v___x_1090_; 
v___x_1089_ = 123ULL;
v___x_1090_ = lean_uint64_dec_le(v___x_1086_, v___x_1089_);
if (v___x_1090_ == 0)
{
v___y_1067_ = v___x_1086_;
v___y_1068_ = v___y_1079_;
v___y_1069_ = v___y_1081_;
v___y_1070_ = v___x_1085_;
goto v___jp_1066_;
}
else
{
uint64_t v___x_1091_; uint8_t v___x_1092_; 
v___x_1091_ = 0ULL;
v___x_1092_ = lean_uint64_dec_eq(v___x_1085_, v___x_1091_);
if (v___x_1092_ == 0)
{
uint64_t v___x_1093_; uint64_t v___x_1094_; uint8_t v___x_1095_; 
v___x_1093_ = 149ULL;
v___x_1094_ = lean_uint64_sub(v___x_1093_, v___x_1086_);
v___x_1095_ = lean_uint64_dec_eq(v___x_1094_, v___x_1091_);
if (v___x_1095_ == 0)
{
uint64_t v___x_1096_; uint8_t v___x_1097_; 
v___x_1096_ = 64ULL;
v___x_1097_ = lean_uint64_dec_lt(v___x_1094_, v___x_1096_);
if (v___x_1097_ == 0)
{
uint8_t v___x_1098_; 
v___x_1098_ = lean_uint64_dec_eq(v___x_1094_, v___x_1096_);
if (v___x_1098_ == 0)
{
v___y_805_ = v___y_1079_;
v___y_806_ = v___y_1081_;
v___y_807_ = v___x_1091_;
v___y_808_ = v___x_1091_;
goto v___jp_804_;
}
else
{
uint64_t v___x_1099_; uint8_t v___x_1100_; 
v___x_1099_ = 9223372036854775808ULL;
v___x_1100_ = lean_uint64_dec_lt(v___x_1099_, v___x_1085_);
if (v___x_1100_ == 0)
{
v___y_805_ = v___y_1079_;
v___y_806_ = v___y_1081_;
v___y_807_ = v___x_1091_;
v___y_808_ = v___x_1091_;
goto v___jp_804_;
}
else
{
uint64_t v___x_1101_; 
v___x_1101_ = 1ULL;
v___y_805_ = v___y_1079_;
v___y_806_ = v___y_1081_;
v___y_807_ = v___x_1091_;
v___y_808_ = v___x_1101_;
goto v___jp_804_;
}
}
}
else
{
uint64_t v_quotient_1102_; uint64_t v___x_1103_; uint64_t v___x_1104_; uint64_t v___x_1105_; uint64_t v_remainder_1106_; uint64_t v___x_1107_; uint64_t v_half_1108_; uint8_t v___x_1109_; 
v_quotient_1102_ = lean_uint64_shift_right(v___x_1085_, v___x_1094_);
v___x_1103_ = 1ULL;
v___x_1104_ = lean_uint64_shift_left(v___x_1103_, v___x_1094_);
v___x_1105_ = lean_uint64_sub(v___x_1104_, v___x_1103_);
v_remainder_1106_ = lean_uint64_land(v___x_1085_, v___x_1105_);
v___x_1107_ = lean_uint64_sub(v___x_1094_, v___x_1103_);
v_half_1108_ = lean_uint64_shift_left(v___x_1103_, v___x_1107_);
v___x_1109_ = lean_uint64_dec_lt(v_remainder_1106_, v_half_1108_);
if (v___x_1109_ == 0)
{
uint8_t v___x_1110_; 
v___x_1110_ = lean_uint64_dec_lt(v_half_1108_, v_remainder_1106_);
if (v___x_1110_ == 0)
{
uint64_t v___x_1111_; uint8_t v___x_1112_; 
v___x_1111_ = lean_uint64_land(v_quotient_1102_, v___x_1103_);
v___x_1112_ = lean_uint64_dec_eq(v___x_1111_, v___x_1091_);
if (v___x_1112_ == 0)
{
uint64_t v___x_1113_; 
v___x_1113_ = lean_uint64_add(v_quotient_1102_, v___x_1103_);
v___y_805_ = v___y_1079_;
v___y_806_ = v___y_1081_;
v___y_807_ = v___x_1091_;
v___y_808_ = v___x_1113_;
goto v___jp_804_;
}
else
{
v___y_805_ = v___y_1079_;
v___y_806_ = v___y_1081_;
v___y_807_ = v___x_1091_;
v___y_808_ = v_quotient_1102_;
goto v___jp_804_;
}
}
else
{
uint64_t v___x_1114_; 
v___x_1114_ = lean_uint64_add(v_quotient_1102_, v___x_1103_);
v___y_805_ = v___y_1079_;
v___y_806_ = v___y_1081_;
v___y_807_ = v___x_1091_;
v___y_808_ = v___x_1114_;
goto v___jp_804_;
}
}
else
{
v___y_805_ = v___y_1079_;
v___y_806_ = v___y_1081_;
v___y_807_ = v___x_1091_;
v___y_808_ = v_quotient_1102_;
goto v___jp_804_;
}
}
}
else
{
v___y_805_ = v___y_1079_;
v___y_806_ = v___y_1081_;
v___y_807_ = v___x_1091_;
v___y_808_ = v___x_1085_;
goto v___jp_804_;
}
}
else
{
if (v___y_1079_ == 0)
{
uint32_t v___x_1115_; 
v___x_1115_ = 0;
return v___x_1115_;
}
else
{
uint32_t v___x_1116_; 
v___x_1116_ = 2147483648;
return v___x_1116_;
}
}
}
}
}
v___jp_1120_:
{
uint64_t v___x_1126_; uint64_t v___x_1127_; uint8_t v___x_1128_; 
v___x_1126_ = lean_uint32_to_uint64(v_ey_1119_);
v___x_1127_ = 0ULL;
v___x_1128_ = lean_uint64_dec_eq(v___x_1126_, v___x_1127_);
if (v___x_1128_ == 0)
{
uint64_t v___x_1129_; uint64_t v___x_1130_; 
v___x_1129_ = 1ULL;
v___x_1130_ = lean_uint64_sub(v___x_1126_, v___x_1129_);
v___y_1079_ = v___y_1121_;
v___y_1080_ = v___y_1122_;
v___y_1081_ = v___y_1124_;
v___y_1082_ = v___y_1123_;
v___y_1083_ = v___y_1125_;
v___y_1084_ = v___x_1130_;
goto v___jp_1078_;
}
else
{
v___y_1079_ = v___y_1121_;
v___y_1080_ = v___y_1122_;
v___y_1081_ = v___y_1124_;
v___y_1082_ = v___y_1123_;
v___y_1083_ = v___y_1125_;
v___y_1084_ = v___x_1127_;
goto v___jp_1078_;
}
}
v___jp_1131_:
{
uint64_t v___x_1136_; uint64_t v___x_1137_; uint8_t v___x_1138_; 
v___x_1136_ = lean_uint32_to_uint64(v_ex_1117_);
v___x_1137_ = 0ULL;
v___x_1138_ = lean_uint64_dec_eq(v___x_1136_, v___x_1137_);
if (v___x_1138_ == 0)
{
uint64_t v___x_1139_; uint64_t v___x_1140_; 
v___x_1139_ = 1ULL;
v___x_1140_ = lean_uint64_sub(v___x_1136_, v___x_1139_);
v___y_1121_ = v___y_1132_;
v___y_1122_ = v___y_1135_;
v___y_1123_ = v___y_1134_;
v___y_1124_ = v___y_1133_;
v___y_1125_ = v___x_1140_;
goto v___jp_1120_;
}
else
{
v___y_1121_ = v___y_1132_;
v___y_1122_ = v___y_1135_;
v___y_1123_ = v___y_1134_;
v___y_1124_ = v___y_1133_;
v___y_1125_ = v___x_1137_;
goto v___jp_1120_;
}
}
v___jp_1141_:
{
uint32_t v___x_1146_; uint8_t v___x_1147_; 
v___x_1146_ = 0;
v___x_1147_ = lean_uint32_dec_eq(v_ey_1119_, v___x_1146_);
if (v___x_1147_ == 0)
{
uint64_t v___x_1148_; uint64_t v___x_1149_; uint64_t v___x_1150_; 
v___x_1148_ = lean_uint32_to_uint64(v___y_1143_);
v___x_1149_ = 8388608ULL;
v___x_1150_ = lean_uint64_lor(v___x_1148_, v___x_1149_);
v___y_1132_ = v___y_1142_;
v___y_1133_ = v___y_1144_;
v___y_1134_ = v___y_1145_;
v___y_1135_ = v___x_1150_;
goto v___jp_1131_;
}
else
{
uint64_t v___x_1151_; 
v___x_1151_ = lean_uint32_to_uint64(v___y_1143_);
v___y_1132_ = v___y_1142_;
v___y_1133_ = v___y_1144_;
v___y_1134_ = v___y_1145_;
v___y_1135_ = v___x_1151_;
goto v___jp_1131_;
}
}
v___jp_1152_:
{
uint32_t v___x_1154_; uint32_t v_xFraction_1155_; uint32_t v_yFraction_1156_; uint32_t v___x_1157_; uint8_t v___x_1158_; 
v___x_1154_ = 8388607;
v_xFraction_1155_ = lean_uint32_land(v___y_672_, v___x_1154_);
v_yFraction_1156_ = lean_uint32_land(v___y_673_, v___x_1154_);
v___x_1157_ = 0;
v___x_1158_ = lean_uint32_dec_eq(v_ex_1117_, v___x_1157_);
if (v___x_1158_ == 0)
{
uint64_t v___x_1159_; uint64_t v___x_1160_; uint64_t v___x_1161_; 
v___x_1159_ = lean_uint32_to_uint64(v_xFraction_1155_);
v___x_1160_ = 8388608ULL;
v___x_1161_ = lean_uint64_lor(v___x_1159_, v___x_1160_);
v___y_1142_ = v___y_1153_;
v___y_1143_ = v_yFraction_1156_;
v___y_1144_ = v___x_1154_;
v___y_1145_ = v___x_1161_;
goto v___jp_1141_;
}
else
{
uint64_t v___x_1162_; 
v___x_1162_ = lean_uint32_to_uint64(v_xFraction_1155_);
v___y_1142_ = v___y_1153_;
v___y_1143_ = v_yFraction_1156_;
v___y_1144_ = v___x_1154_;
v___y_1145_ = v___x_1162_;
goto v___jp_1141_;
}
}
v___jp_1163_:
{
if (v___y_1165_ == 0)
{
v___y_1153_ = v___x_671_;
goto v___jp_1152_;
}
else
{
v___y_1153_ = v___y_1164_;
goto v___jp_1152_;
}
}
v___jp_1169_:
{
if (v___y_1170_ == 0)
{
if (v___y_1172_ == 0)
{
v___y_1164_ = v___y_1171_;
v___y_1165_ = v___x_1168_;
goto v___jp_1163_;
}
else
{
v___y_1153_ = v___x_671_;
goto v___jp_1152_;
}
}
else
{
v___y_1164_ = v___y_1171_;
v___y_1165_ = v___y_1172_;
goto v___jp_1163_;
}
}
v___jp_1173_:
{
uint32_t v___x_1176_; uint32_t v___x_1177_; uint32_t v___x_1178_; uint8_t v___x_1179_; 
v___x_1176_ = 2147483648;
v___x_1177_ = lean_uint32_land(v___y_673_, v___x_1176_);
v___x_1178_ = 0;
v___x_1179_ = lean_uint32_dec_eq(v___x_1177_, v___x_1178_);
if (v___x_1179_ == 0)
{
v___y_1170_ = v___y_1175_;
v___y_1171_ = v___y_1174_;
v___y_1172_ = v___x_671_;
goto v___jp_1169_;
}
else
{
v___y_1170_ = v___y_1175_;
v___y_1171_ = v___y_1174_;
v___y_1172_ = v___y_1174_;
goto v___jp_1169_;
}
}
v___jp_1180_:
{
if (v___y_1181_ == 0)
{
uint32_t v___x_1182_; uint32_t v___x_1183_; uint32_t v___x_1184_; uint8_t v___x_1185_; 
v___x_1182_ = 2147483648;
v___x_1183_ = lean_uint32_land(v___y_672_, v___x_1182_);
v___x_1184_ = 0;
v___x_1185_ = lean_uint32_dec_eq(v___x_1183_, v___x_1184_);
if (v___x_1185_ == 0)
{
v___y_1174_ = v___y_1181_;
v___y_1175_ = v___x_671_;
goto v___jp_1173_;
}
else
{
v___y_1174_ = v___y_1181_;
v___y_1175_ = v___y_1181_;
goto v___jp_1173_;
}
}
else
{
lean_object* v___x_1186_; lean_object* v___x_1187_; lean_object* v___x_1188_; uint32_t v___x_1189_; 
v___x_1186_ = lean_uint32_to_nat(v___y_672_);
v___x_1187_ = lean_uint32_to_nat(v___y_673_);
v___x_1188_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1186_, v___x_1187_);
v___x_1189_ = lean_uint32_of_nat(v___x_1188_);
lean_dec(v___x_1188_);
return v___x_1189_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___x_1204_, lean_object* v___y_1205_, lean_object* v___y_1206_){
_start:
{
uint8_t v___x_8515__boxed_1207_; uint32_t v___y_8516__boxed_1208_; uint32_t v___y_8517__boxed_1209_; uint32_t v_res_1210_; lean_object* v_r_1211_; 
v___x_8515__boxed_1207_ = lean_unbox(v___x_1204_);
v___y_8516__boxed_1208_ = lean_unbox_uint32(v___y_1205_);
lean_dec(v___y_1205_);
v___y_8517__boxed_1209_ = lean_unbox_uint32(v___y_1206_);
lean_dec(v___y_1206_);
v_res_1210_ = lp_competition_main___lam__3(v___x_8515__boxed_1207_, v___y_8516__boxed_1208_, v___y_8517__boxed_1209_);
v_r_1211_ = lean_box_uint32(v_res_1210_);
return v_r_1211_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__4(uint8_t v___x_1212_, uint32_t v___y_1213_, uint32_t v___y_1214_){
_start:
{
uint8_t v___y_1216_; uint8_t v___y_1232_; uint8_t v___y_1246_; uint8_t v___y_1263_; float v___y_1270_; float v___y_1271_; float v___y_1285_; uint8_t v___y_1286_; float v___y_1301_; uint32_t v___y_1311_; uint32_t v___y_1315_; uint32_t v___y_1319_; uint32_t v___y_1320_; uint32_t v___y_1321_; uint8_t v___y_1325_; uint64_t v___y_1326_; uint32_t v___y_1327_; uint64_t v___y_1328_; uint32_t v___y_1340_; uint32_t v___y_1341_; uint32_t v___y_1342_; uint8_t v___y_1346_; uint64_t v___y_1347_; uint32_t v___y_1348_; uint64_t v___y_1349_; uint32_t v___x_1360_; uint32_t v___x_1361_; uint8_t v___y_1363_; uint32_t v___x_1375_; uint32_t v___y_1377_; uint32_t v___y_1378_; uint32_t v___y_1379_; uint32_t v___y_1380_; uint32_t v___y_1387_; uint8_t v___y_1388_; uint32_t v___y_1389_; uint32_t v___y_1390_; uint8_t v___y_1394_; uint64_t v___y_1395_; uint64_t v___y_1396_; uint32_t v___y_1397_; uint64_t v___y_1398_; uint8_t v___y_1408_; uint8_t v___y_1409_; uint64_t v___y_1410_; uint32_t v___y_1411_; uint64_t v___y_1412_; uint64_t v___y_1413_; uint8_t v___y_1420_; uint64_t v___y_1421_; uint32_t v___y_1422_; uint64_t v___y_1423_; uint64_t v___y_1424_; uint64_t v___y_1430_; uint8_t v___y_1431_; uint64_t v___y_1432_; uint32_t v___y_1433_; uint64_t v___y_1434_; uint64_t v___y_1435_; uint64_t v___y_1490_; uint8_t v___y_1491_; uint64_t v___y_1492_; uint32_t v___y_1493_; uint64_t v___y_1494_; uint64_t v___y_1495_; uint64_t v___y_1496_; uint64_t v___y_1502_; uint64_t v___y_1503_; uint8_t v___y_1504_; uint64_t v___y_1505_; uint64_t v___y_1506_; uint32_t v___y_1507_; uint64_t v___y_1508_; uint64_t v___y_1509_; uint64_t v___y_1510_; uint64_t v___y_1515_; uint8_t v___y_1516_; uint64_t v___y_1517_; uint32_t v___y_1518_; uint64_t v___y_1519_; uint64_t v___y_1520_; uint64_t v___y_1521_; uint64_t v___y_1526_; uint8_t v___y_1527_; uint64_t v___y_1528_; uint64_t v___y_1529_; uint32_t v___y_1530_; uint64_t v___y_1531_; uint64_t v___y_1532_; uint64_t v___y_1533_; uint64_t v___y_1534_; uint64_t v___y_1539_; uint8_t v___y_1540_; uint64_t v___y_1541_; uint32_t v___y_1542_; uint64_t v___y_1543_; uint64_t v___y_1544_; uint64_t v___y_1545_; uint64_t v___y_1550_; uint8_t v___y_1551_; uint64_t v___y_1552_; uint64_t v___y_1553_; uint64_t v___y_1554_; uint32_t v___y_1555_; uint64_t v___y_1556_; uint64_t v___y_1557_; uint64_t v___y_1558_; uint64_t v___y_1563_; uint8_t v___y_1564_; uint64_t v___y_1565_; uint32_t v___y_1566_; uint64_t v___y_1567_; uint64_t v___y_1568_; uint64_t v___y_1569_; uint64_t v___y_1574_; uint8_t v___y_1575_; uint64_t v___y_1576_; uint64_t v___y_1577_; uint64_t v___y_1578_; uint32_t v___y_1579_; uint64_t v___y_1580_; uint64_t v___y_1581_; uint64_t v___y_1582_; uint64_t v___y_1587_; uint8_t v___y_1588_; uint64_t v___y_1589_; uint64_t v___y_1590_; uint32_t v___y_1591_; uint64_t v___y_1592_; uint64_t v___y_1593_; uint64_t v___y_1598_; uint8_t v___y_1599_; uint64_t v___y_1600_; uint64_t v___y_1601_; uint32_t v___y_1602_; uint64_t v___y_1603_; uint64_t v___y_1604_; uint64_t v___y_1608_; uint8_t v___y_1609_; uint32_t v___y_1610_; uint64_t v___y_1611_; uint8_t v___y_1620_; uint32_t v___y_1621_; uint64_t v___y_1622_; uint64_t v___y_1623_; uint64_t v___y_1624_; uint64_t v___y_1625_; uint32_t v_ex_1658_; uint32_t v___x_1659_; uint32_t v_ey_1660_; uint8_t v___y_1662_; uint32_t v___y_1663_; uint64_t v___y_1664_; uint64_t v___y_1665_; uint64_t v___y_1666_; uint8_t v___y_1673_; uint32_t v___y_1674_; uint64_t v___y_1675_; uint64_t v___y_1676_; uint8_t v___y_1683_; uint32_t v___y_1684_; uint32_t v___y_1685_; uint64_t v___y_1686_; uint8_t v___y_1694_; uint8_t v___y_1705_; uint8_t v___y_1706_; uint32_t v___x_1707_; uint32_t v___x_1708_; uint8_t v___x_1709_; uint8_t v___y_1711_; uint8_t v___y_1712_; uint8_t v___y_1713_; uint8_t v___y_1715_; uint8_t v___y_1716_; uint8_t v___y_1722_; 
v___x_1360_ = 23;
v___x_1361_ = lean_uint32_shift_right(v___y_1213_, v___x_1360_);
v___x_1375_ = 255;
v_ex_1658_ = lean_uint32_land(v___x_1361_, v___x_1375_);
v___x_1659_ = lean_uint32_shift_right(v___y_1214_, v___x_1360_);
v_ey_1660_ = lean_uint32_land(v___x_1659_, v___x_1375_);
v___x_1707_ = lean_uint32_add(v_ex_1658_, v_ey_1660_);
v___x_1708_ = 128;
v___x_1709_ = lean_uint32_dec_lt(v___x_1707_, v___x_1708_);
if (v___x_1709_ == 0)
{
uint32_t v___x_1731_; uint32_t v_a_1732_; uint32_t v___x_1733_; uint32_t v___x_1734_; uint32_t v___x_1735_; uint8_t v___x_1736_; 
v___x_1731_ = 2147483647;
v_a_1732_ = lean_uint32_land(v___y_1213_, v___x_1731_);
v___x_1733_ = 201326591;
v___x_1734_ = 1;
v___x_1735_ = lean_uint32_sub(v_a_1732_, v___x_1734_);
v___x_1736_ = lean_uint32_dec_le(v___x_1733_, v___x_1735_);
if (v___x_1736_ == 0)
{
v___y_1363_ = v___x_1736_;
goto v___jp_1362_;
}
else
{
uint32_t v___x_1737_; uint8_t v___x_1738_; 
v___x_1737_ = 2139095040;
v___x_1738_ = lean_uint32_dec_lt(v_a_1732_, v___x_1737_);
v___y_1363_ = v___x_1738_;
goto v___jp_1362_;
}
}
else
{
uint32_t v___x_1739_; uint32_t v___x_1740_; uint32_t v___x_1741_; uint8_t v___x_1742_; 
v___x_1739_ = 4278190080;
v___x_1740_ = 1;
v___x_1741_ = lean_uint32_shift_left(v___y_1213_, v___x_1740_);
v___x_1742_ = lean_uint32_dec_le(v___x_1739_, v___x_1741_);
if (v___x_1742_ == 0)
{
uint32_t v___x_1743_; uint8_t v___x_1744_; 
v___x_1743_ = lean_uint32_shift_left(v___y_1214_, v___x_1740_);
v___x_1744_ = lean_uint32_dec_le(v___x_1739_, v___x_1743_);
v___y_1722_ = v___x_1744_;
goto v___jp_1721_;
}
else
{
v___y_1722_ = v___x_1742_;
goto v___jp_1721_;
}
}
v___jp_1215_:
{
if (v___y_1216_ == 0)
{
uint32_t v___x_1217_; 
v___x_1217_ = lp_competition_Submission_FastMul_mul(v___y_1213_, v___y_1214_);
return v___x_1217_;
}
else
{
uint32_t v___x_1218_; uint32_t v___x_1219_; 
v___x_1218_ = 4194304;
v___x_1219_ = lean_uint32_lor(v___y_1214_, v___x_1218_);
return v___x_1219_;
}
}
v___jp_1220_:
{
uint32_t v___x_1221_; uint32_t v___x_1222_; uint32_t v___x_1223_; uint32_t v___x_1224_; uint8_t v___x_1225_; 
v___x_1221_ = 23;
v___x_1222_ = lean_uint32_shift_right(v___y_1214_, v___x_1221_);
v___x_1223_ = 255;
v___x_1224_ = lean_uint32_land(v___x_1222_, v___x_1223_);
v___x_1225_ = lean_uint32_dec_eq(v___x_1224_, v___x_1223_);
if (v___x_1225_ == 0)
{
v___y_1216_ = v___x_1225_;
goto v___jp_1215_;
}
else
{
uint32_t v___x_1226_; uint32_t v___x_1227_; uint32_t v___x_1228_; uint8_t v___x_1229_; 
v___x_1226_ = 8388607;
v___x_1227_ = lean_uint32_land(v___y_1214_, v___x_1226_);
v___x_1228_ = 0;
v___x_1229_ = lean_uint32_dec_eq(v___x_1227_, v___x_1228_);
if (v___x_1229_ == 0)
{
v___y_1216_ = v___x_1225_;
goto v___jp_1215_;
}
else
{
uint32_t v___x_1230_; 
v___x_1230_ = lp_competition_Submission_FastMul_mul(v___y_1213_, v___y_1214_);
return v___x_1230_;
}
}
}
v___jp_1231_:
{
if (v___y_1232_ == 0)
{
goto v___jp_1220_;
}
else
{
uint32_t v___x_1233_; uint32_t v___x_1234_; 
v___x_1233_ = 4194304;
v___x_1234_ = lean_uint32_lor(v___y_1213_, v___x_1233_);
return v___x_1234_;
}
}
v___jp_1235_:
{
uint32_t v___x_1236_; uint32_t v___x_1237_; uint32_t v___x_1238_; uint32_t v___x_1239_; uint8_t v___x_1240_; 
v___x_1236_ = 23;
v___x_1237_ = lean_uint32_shift_right(v___y_1213_, v___x_1236_);
v___x_1238_ = 255;
v___x_1239_ = lean_uint32_land(v___x_1237_, v___x_1238_);
v___x_1240_ = lean_uint32_dec_eq(v___x_1239_, v___x_1238_);
if (v___x_1240_ == 0)
{
v___y_1232_ = v___x_1240_;
goto v___jp_1231_;
}
else
{
uint32_t v___x_1241_; uint32_t v___x_1242_; uint32_t v___x_1243_; uint8_t v___x_1244_; 
v___x_1241_ = 8388607;
v___x_1242_ = lean_uint32_land(v___y_1213_, v___x_1241_);
v___x_1243_ = 0;
v___x_1244_ = lean_uint32_dec_eq(v___x_1242_, v___x_1243_);
if (v___x_1244_ == 0)
{
v___y_1232_ = v___x_1240_;
goto v___jp_1231_;
}
else
{
goto v___jp_1220_;
}
}
}
v___jp_1245_:
{
if (v___y_1246_ == 0)
{
goto v___jp_1235_;
}
else
{
uint32_t v___x_1247_; uint32_t v___x_1248_; uint32_t v___x_1249_; uint8_t v___x_1250_; 
v___x_1247_ = 4194304;
v___x_1248_ = lean_uint32_land(v___y_1214_, v___x_1247_);
v___x_1249_ = 0;
v___x_1250_ = lean_uint32_dec_eq(v___x_1248_, v___x_1249_);
if (v___x_1250_ == 0)
{
goto v___jp_1235_;
}
else
{
uint32_t v___x_1251_; 
v___x_1251_ = lean_uint32_lor(v___y_1214_, v___x_1247_);
return v___x_1251_;
}
}
}
v___jp_1252_:
{
uint32_t v___x_1253_; uint32_t v___x_1254_; uint32_t v___x_1255_; uint32_t v___x_1256_; uint8_t v___x_1257_; 
v___x_1253_ = 23;
v___x_1254_ = lean_uint32_shift_right(v___y_1214_, v___x_1253_);
v___x_1255_ = 255;
v___x_1256_ = lean_uint32_land(v___x_1254_, v___x_1255_);
v___x_1257_ = lean_uint32_dec_eq(v___x_1256_, v___x_1255_);
if (v___x_1257_ == 0)
{
v___y_1246_ = v___x_1257_;
goto v___jp_1245_;
}
else
{
uint32_t v___x_1258_; uint32_t v___x_1259_; uint32_t v___x_1260_; uint8_t v___x_1261_; 
v___x_1258_ = 8388607;
v___x_1259_ = lean_uint32_land(v___y_1214_, v___x_1258_);
v___x_1260_ = 0;
v___x_1261_ = lean_uint32_dec_eq(v___x_1259_, v___x_1260_);
if (v___x_1261_ == 0)
{
v___y_1246_ = v___x_1257_;
goto v___jp_1245_;
}
else
{
goto v___jp_1235_;
}
}
}
v___jp_1262_:
{
if (v___y_1263_ == 0)
{
goto v___jp_1252_;
}
else
{
uint32_t v___x_1264_; uint32_t v___x_1265_; uint32_t v___x_1266_; uint8_t v___x_1267_; 
v___x_1264_ = 4194304;
v___x_1265_ = lean_uint32_land(v___y_1213_, v___x_1264_);
v___x_1266_ = 0;
v___x_1267_ = lean_uint32_dec_eq(v___x_1265_, v___x_1266_);
if (v___x_1267_ == 0)
{
goto v___jp_1252_;
}
else
{
uint32_t v___x_1268_; 
v___x_1268_ = lean_uint32_lor(v___y_1213_, v___x_1264_);
return v___x_1268_;
}
}
}
v___jp_1269_:
{
float v_result_1272_; uint8_t v___x_1273_; 
v_result_1272_ = lean_float32_mul(v___y_1270_, v___y_1271_);
v___x_1273_ = lean_float32_beq(v_result_1272_, v_result_1272_);
if (v___x_1273_ == 0)
{
uint32_t v___x_1274_; uint32_t v___x_1275_; uint32_t v___x_1276_; uint32_t v___x_1277_; uint8_t v___x_1278_; 
v___x_1274_ = 23;
v___x_1275_ = lean_uint32_shift_right(v___y_1213_, v___x_1274_);
v___x_1276_ = 255;
v___x_1277_ = lean_uint32_land(v___x_1275_, v___x_1276_);
v___x_1278_ = lean_uint32_dec_eq(v___x_1277_, v___x_1276_);
if (v___x_1278_ == 0)
{
v___y_1263_ = v___x_1278_;
goto v___jp_1262_;
}
else
{
uint32_t v___x_1279_; uint32_t v___x_1280_; uint32_t v___x_1281_; uint8_t v___x_1282_; 
v___x_1279_ = 8388607;
v___x_1280_ = lean_uint32_land(v___y_1213_, v___x_1279_);
v___x_1281_ = 0;
v___x_1282_ = lean_uint32_dec_eq(v___x_1280_, v___x_1281_);
if (v___x_1282_ == 0)
{
v___y_1263_ = v___x_1278_;
goto v___jp_1262_;
}
else
{
goto v___jp_1252_;
}
}
}
else
{
uint32_t v___x_1283_; 
v___x_1283_ = lean_float32_to_bits(v_result_1272_);
return v___x_1283_;
}
}
v___jp_1284_:
{
if (v___y_1286_ == 0)
{
float v___x_1287_; 
v___x_1287_ = lean_float32_of_bits(v___y_1214_);
v___y_1270_ = v___y_1285_;
v___y_1271_ = v___x_1287_;
goto v___jp_1269_;
}
else
{
uint32_t v___x_1288_; uint32_t v___x_1289_; uint32_t v___x_1290_; uint32_t v___x_1291_; float v___x_1292_; lean_object* v___x_1293_; uint32_t v___x_1294_; uint32_t v___x_1295_; lean_object* v___x_1296_; lean_object* v___x_1297_; float v___x_1298_; float v___x_1299_; 
v___x_1288_ = 8388607;
v___x_1289_ = lean_uint32_land(v___y_1214_, v___x_1288_);
v___x_1290_ = 8388608;
v___x_1291_ = lean_uint32_lor(v___x_1289_, v___x_1290_);
v___x_1292_ = lean_uint32_to_float32(v___x_1291_);
v___x_1293_ = lp_competition_R2W01b_scaleTable;
v___x_1294_ = 23;
v___x_1295_ = lean_uint32_shift_right(v___y_1214_, v___x_1294_);
v___x_1296_ = lean_uint32_to_nat(v___x_1295_);
v___x_1297_ = lean_array_fget_borrowed(v___x_1293_, v___x_1296_);
lean_dec(v___x_1296_);
v___x_1298_ = lean_unbox_float32(v___x_1297_);
v___x_1299_ = lean_float32_mul(v___x_1292_, v___x_1298_);
v___y_1270_ = v___y_1285_;
v___y_1271_ = v___x_1299_;
goto v___jp_1269_;
}
}
v___jp_1300_:
{
uint32_t v___x_1302_; uint32_t v_a_1303_; uint32_t v___x_1304_; uint32_t v___x_1305_; uint32_t v___x_1306_; uint8_t v___x_1307_; 
v___x_1302_ = 2147483647;
v_a_1303_ = lean_uint32_land(v___y_1214_, v___x_1302_);
v___x_1304_ = 201326591;
v___x_1305_ = 1;
v___x_1306_ = lean_uint32_sub(v_a_1303_, v___x_1305_);
v___x_1307_ = lean_uint32_dec_le(v___x_1304_, v___x_1306_);
if (v___x_1307_ == 0)
{
v___y_1285_ = v___y_1301_;
v___y_1286_ = v___x_1307_;
goto v___jp_1284_;
}
else
{
uint32_t v___x_1308_; uint8_t v___x_1309_; 
v___x_1308_ = 2139095040;
v___x_1309_ = lean_uint32_dec_lt(v_a_1303_, v___x_1308_);
v___y_1285_ = v___y_1301_;
v___y_1286_ = v___x_1309_;
goto v___jp_1284_;
}
}
v___jp_1310_:
{
uint32_t v___x_1312_; uint32_t v___x_1313_; 
v___x_1312_ = 8388608;
v___x_1313_ = lean_uint32_lor(v___y_1311_, v___x_1312_);
return v___x_1313_;
}
v___jp_1314_:
{
uint32_t v___x_1316_; uint32_t v___x_1317_; 
v___x_1316_ = 8388608;
v___x_1317_ = lean_uint32_lor(v___y_1315_, v___x_1316_);
return v___x_1317_;
}
v___jp_1318_:
{
uint32_t v___x_1322_; uint32_t v___x_1323_; 
v___x_1322_ = lean_uint32_land(v___y_1319_, v___y_1320_);
v___x_1323_ = lean_uint32_lor(v___y_1321_, v___x_1322_);
return v___x_1323_;
}
v___jp_1324_:
{
uint8_t v___x_1329_; 
v___x_1329_ = lean_uint64_dec_eq(v___y_1328_, v___y_1326_);
if (v___x_1329_ == 0)
{
uint64_t v___x_1330_; uint8_t v___x_1331_; 
v___x_1330_ = 8388608ULL;
v___x_1331_ = lean_uint64_dec_eq(v___y_1328_, v___x_1330_);
if (v___x_1331_ == 0)
{
uint32_t v___x_1332_; 
v___x_1332_ = lean_uint64_to_uint32(v___y_1328_);
if (v___y_1325_ == 0)
{
uint32_t v___x_1333_; 
v___x_1333_ = 0;
v___y_1319_ = v___x_1332_;
v___y_1320_ = v___y_1327_;
v___y_1321_ = v___x_1333_;
goto v___jp_1318_;
}
else
{
uint32_t v___x_1334_; 
v___x_1334_ = 2147483648;
v___y_1319_ = v___x_1332_;
v___y_1320_ = v___y_1327_;
v___y_1321_ = v___x_1334_;
goto v___jp_1318_;
}
}
else
{
if (v___y_1325_ == 0)
{
uint32_t v___x_1335_; 
v___x_1335_ = 0;
v___y_1315_ = v___x_1335_;
goto v___jp_1314_;
}
else
{
uint32_t v___x_1336_; 
v___x_1336_ = 2147483648;
v___y_1315_ = v___x_1336_;
goto v___jp_1314_;
}
}
}
else
{
if (v___y_1325_ == 0)
{
uint32_t v___x_1337_; 
v___x_1337_ = 0;
return v___x_1337_;
}
else
{
uint32_t v___x_1338_; 
v___x_1338_ = 2147483648;
return v___x_1338_;
}
}
}
v___jp_1339_:
{
uint32_t v___x_1343_; uint32_t v___x_1344_; 
v___x_1343_ = lean_uint32_land(v___y_1341_, v___y_1340_);
v___x_1344_ = lean_uint32_lor(v___y_1342_, v___x_1343_);
return v___x_1344_;
}
v___jp_1345_:
{
uint8_t v___x_1350_; 
v___x_1350_ = lean_uint64_dec_eq(v___y_1349_, v___y_1347_);
if (v___x_1350_ == 0)
{
uint64_t v___x_1351_; uint8_t v___x_1352_; 
v___x_1351_ = 8388608ULL;
v___x_1352_ = lean_uint64_dec_eq(v___y_1349_, v___x_1351_);
if (v___x_1352_ == 0)
{
uint32_t v___x_1353_; 
v___x_1353_ = lean_uint64_to_uint32(v___y_1349_);
if (v___y_1346_ == 0)
{
uint32_t v___x_1354_; 
v___x_1354_ = 0;
v___y_1340_ = v___y_1348_;
v___y_1341_ = v___x_1353_;
v___y_1342_ = v___x_1354_;
goto v___jp_1339_;
}
else
{
uint32_t v___x_1355_; 
v___x_1355_ = 2147483648;
v___y_1340_ = v___y_1348_;
v___y_1341_ = v___x_1353_;
v___y_1342_ = v___x_1355_;
goto v___jp_1339_;
}
}
else
{
if (v___y_1346_ == 0)
{
uint32_t v___x_1356_; 
v___x_1356_ = 0;
v___y_1311_ = v___x_1356_;
goto v___jp_1310_;
}
else
{
uint32_t v___x_1357_; 
v___x_1357_ = 2147483648;
v___y_1311_ = v___x_1357_;
goto v___jp_1310_;
}
}
}
else
{
if (v___y_1346_ == 0)
{
uint32_t v___x_1358_; 
v___x_1358_ = 0;
return v___x_1358_;
}
else
{
uint32_t v___x_1359_; 
v___x_1359_ = 2147483648;
return v___x_1359_;
}
}
}
v___jp_1362_:
{
if (v___y_1363_ == 0)
{
float v___x_1364_; 
v___x_1364_ = lean_float32_of_bits(v___y_1213_);
v___y_1301_ = v___x_1364_;
goto v___jp_1300_;
}
else
{
uint32_t v___x_1365_; uint32_t v___x_1366_; uint32_t v___x_1367_; uint32_t v___x_1368_; float v___x_1369_; lean_object* v___x_1370_; lean_object* v___x_1371_; lean_object* v___x_1372_; float v___x_1373_; float v___x_1374_; 
v___x_1365_ = 8388607;
v___x_1366_ = lean_uint32_land(v___y_1213_, v___x_1365_);
v___x_1367_ = 8388608;
v___x_1368_ = lean_uint32_lor(v___x_1366_, v___x_1367_);
v___x_1369_ = lean_uint32_to_float32(v___x_1368_);
v___x_1370_ = lp_competition_R2W01b_scaleTable;
v___x_1371_ = lean_uint32_to_nat(v___x_1361_);
v___x_1372_ = lean_array_fget_borrowed(v___x_1370_, v___x_1371_);
lean_dec(v___x_1371_);
v___x_1373_ = lean_unbox_float32(v___x_1372_);
v___x_1374_ = lean_float32_mul(v___x_1369_, v___x_1373_);
v___y_1301_ = v___x_1374_;
goto v___jp_1300_;
}
}
v___jp_1376_:
{
uint32_t v___x_1381_; uint32_t v___x_1382_; uint32_t v___x_1383_; uint32_t v___x_1384_; uint32_t v___x_1385_; 
v___x_1381_ = lean_uint32_land(v___y_1377_, v___x_1375_);
v___x_1382_ = lean_uint32_shift_left(v___x_1381_, v___x_1360_);
v___x_1383_ = lean_uint32_lor(v___y_1380_, v___x_1382_);
v___x_1384_ = lean_uint32_land(v___y_1379_, v___y_1378_);
v___x_1385_ = lean_uint32_lor(v___x_1383_, v___x_1384_);
return v___x_1385_;
}
v___jp_1386_:
{
if (v___y_1388_ == 0)
{
uint32_t v___x_1391_; 
v___x_1391_ = 0;
v___y_1377_ = v___y_1387_;
v___y_1378_ = v___y_1389_;
v___y_1379_ = v___y_1390_;
v___y_1380_ = v___x_1391_;
goto v___jp_1376_;
}
else
{
uint32_t v___x_1392_; 
v___x_1392_ = 2147483648;
v___y_1377_ = v___y_1387_;
v___y_1378_ = v___y_1389_;
v___y_1379_ = v___y_1390_;
v___y_1380_ = v___x_1392_;
goto v___jp_1376_;
}
}
v___jp_1393_:
{
uint64_t v___x_1399_; uint64_t v_encodedExponent_1400_; uint32_t v___x_1401_; uint64_t v___x_1402_; uint8_t v___x_1403_; 
v___x_1399_ = 171ULL;
v_encodedExponent_1400_ = lean_uint64_sub(v___y_1395_, v___x_1399_);
v___x_1401_ = lean_uint64_to_uint32(v_encodedExponent_1400_);
v___x_1402_ = 8388608ULL;
v___x_1403_ = lean_uint64_dec_lt(v___y_1398_, v___x_1402_);
if (v___x_1403_ == 0)
{
uint64_t v___x_1404_; uint32_t v___x_1405_; 
v___x_1404_ = lean_uint64_sub(v___y_1398_, v___x_1402_);
v___x_1405_ = lean_uint64_to_uint32(v___x_1404_);
v___y_1387_ = v___x_1401_;
v___y_1388_ = v___y_1394_;
v___y_1389_ = v___y_1397_;
v___y_1390_ = v___x_1405_;
goto v___jp_1386_;
}
else
{
uint32_t v___x_1406_; 
v___x_1406_ = lean_uint64_to_uint32(v___y_1396_);
v___y_1387_ = v___x_1401_;
v___y_1388_ = v___y_1394_;
v___y_1389_ = v___y_1397_;
v___y_1390_ = v___x_1406_;
goto v___jp_1386_;
}
}
v___jp_1407_:
{
uint64_t v___x_1414_; uint8_t v___x_1415_; 
v___x_1414_ = 425ULL;
v___x_1415_ = lean_uint64_dec_lt(v___x_1414_, v___y_1413_);
if (v___x_1415_ == 0)
{
if (v___y_1408_ == 0)
{
v___y_1394_ = v___y_1409_;
v___y_1395_ = v___y_1413_;
v___y_1396_ = v___y_1410_;
v___y_1397_ = v___y_1411_;
v___y_1398_ = v___y_1412_;
goto v___jp_1393_;
}
else
{
uint64_t v___x_1416_; 
v___x_1416_ = 8388608ULL;
v___y_1394_ = v___y_1409_;
v___y_1395_ = v___y_1413_;
v___y_1396_ = v___y_1410_;
v___y_1397_ = v___y_1411_;
v___y_1398_ = v___x_1416_;
goto v___jp_1393_;
}
}
else
{
if (v___y_1409_ == 0)
{
uint32_t v___x_1417_; 
v___x_1417_ = 2139095040;
return v___x_1417_;
}
else
{
uint32_t v___x_1418_; 
v___x_1418_ = 4286578688;
return v___x_1418_;
}
}
}
v___jp_1419_:
{
uint64_t v___x_1425_; uint8_t v_carry_1426_; 
v___x_1425_ = 16777216ULL;
v_carry_1426_ = lean_uint64_dec_eq(v___y_1424_, v___x_1425_);
if (v_carry_1426_ == 0)
{
v___y_1408_ = v_carry_1426_;
v___y_1409_ = v___y_1420_;
v___y_1410_ = v___y_1421_;
v___y_1411_ = v___y_1422_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1423_;
goto v___jp_1407_;
}
else
{
uint64_t v___x_1427_; uint64_t v___x_1428_; 
v___x_1427_ = 1ULL;
v___x_1428_ = lean_uint64_add(v___y_1423_, v___x_1427_);
v___y_1408_ = v_carry_1426_;
v___y_1409_ = v___y_1420_;
v___y_1410_ = v___y_1421_;
v___y_1411_ = v___y_1422_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___x_1428_;
goto v___jp_1407_;
}
}
v___jp_1429_:
{
uint64_t v_position_1436_; uint64_t v___x_1437_; uint8_t v___x_1438_; 
v_position_1436_ = lean_uint64_add(v___y_1435_, v___y_1434_);
v___x_1437_ = 172ULL;
v___x_1438_ = lean_uint64_dec_lt(v_position_1436_, v___x_1437_);
if (v___x_1438_ == 0)
{
uint64_t v___x_1439_; uint8_t v___x_1440_; 
v___x_1439_ = 23ULL;
v___x_1440_ = lean_uint64_dec_lt(v___y_1435_, v___x_1439_);
if (v___x_1440_ == 0)
{
uint64_t v___x_1441_; uint8_t v___x_1442_; 
v___x_1441_ = lean_uint64_sub(v___y_1435_, v___x_1439_);
v___x_1442_ = lean_uint64_dec_eq(v___x_1441_, v___y_1432_);
if (v___x_1442_ == 0)
{
uint64_t v___x_1443_; uint8_t v___x_1444_; 
v___x_1443_ = 64ULL;
v___x_1444_ = lean_uint64_dec_lt(v___x_1441_, v___x_1443_);
if (v___x_1444_ == 0)
{
uint8_t v___x_1445_; 
v___x_1445_ = lean_uint64_dec_eq(v___x_1441_, v___x_1443_);
if (v___x_1445_ == 0)
{
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v___y_1432_;
goto v___jp_1419_;
}
else
{
uint64_t v___x_1446_; uint8_t v___x_1447_; 
v___x_1446_ = 9223372036854775808ULL;
v___x_1447_ = lean_uint64_dec_lt(v___x_1446_, v___y_1430_);
if (v___x_1447_ == 0)
{
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v___y_1432_;
goto v___jp_1419_;
}
else
{
uint64_t v___x_1448_; 
v___x_1448_ = 1ULL;
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v___x_1448_;
goto v___jp_1419_;
}
}
}
else
{
uint64_t v_quotient_1449_; uint64_t v___x_1450_; uint64_t v___x_1451_; uint64_t v___x_1452_; uint64_t v_remainder_1453_; uint64_t v___x_1454_; uint64_t v_half_1455_; uint8_t v___x_1456_; 
v_quotient_1449_ = lean_uint64_shift_right(v___y_1430_, v___x_1441_);
v___x_1450_ = 1ULL;
v___x_1451_ = lean_uint64_shift_left(v___x_1450_, v___x_1441_);
v___x_1452_ = lean_uint64_sub(v___x_1451_, v___x_1450_);
v_remainder_1453_ = lean_uint64_land(v___y_1430_, v___x_1452_);
v___x_1454_ = lean_uint64_sub(v___x_1441_, v___x_1450_);
v_half_1455_ = lean_uint64_shift_left(v___x_1450_, v___x_1454_);
v___x_1456_ = lean_uint64_dec_lt(v_remainder_1453_, v_half_1455_);
if (v___x_1456_ == 0)
{
uint8_t v___x_1457_; 
v___x_1457_ = lean_uint64_dec_lt(v_half_1455_, v_remainder_1453_);
if (v___x_1457_ == 0)
{
uint64_t v___x_1458_; uint8_t v___x_1459_; 
v___x_1458_ = lean_uint64_land(v_quotient_1449_, v___x_1450_);
v___x_1459_ = lean_uint64_dec_eq(v___x_1458_, v___y_1432_);
if (v___x_1459_ == 0)
{
uint64_t v___x_1460_; 
v___x_1460_ = lean_uint64_add(v_quotient_1449_, v___x_1450_);
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v___x_1460_;
goto v___jp_1419_;
}
else
{
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v_quotient_1449_;
goto v___jp_1419_;
}
}
else
{
uint64_t v___x_1461_; 
v___x_1461_ = lean_uint64_add(v_quotient_1449_, v___x_1450_);
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v___x_1461_;
goto v___jp_1419_;
}
}
else
{
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v_quotient_1449_;
goto v___jp_1419_;
}
}
}
else
{
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v___y_1430_;
goto v___jp_1419_;
}
}
else
{
uint64_t v___x_1462_; uint64_t v___x_1463_; 
v___x_1462_ = lean_uint64_sub(v___x_1439_, v___y_1435_);
v___x_1463_ = lean_uint64_shift_left(v___y_1430_, v___x_1462_);
v___y_1420_ = v___y_1431_;
v___y_1421_ = v___y_1432_;
v___y_1422_ = v___y_1433_;
v___y_1423_ = v_position_1436_;
v___y_1424_ = v___x_1463_;
goto v___jp_1419_;
}
}
else
{
uint64_t v___x_1464_; uint8_t v___x_1465_; 
v___x_1464_ = 149ULL;
v___x_1465_ = lean_uint64_dec_lt(v___y_1434_, v___x_1464_);
if (v___x_1465_ == 0)
{
uint64_t v___x_1466_; uint64_t v___x_1467_; 
v___x_1466_ = lean_uint64_sub(v___y_1434_, v___x_1464_);
v___x_1467_ = lean_uint64_shift_left(v___y_1430_, v___x_1466_);
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v___x_1467_;
goto v___jp_1324_;
}
else
{
uint64_t v___x_1468_; uint8_t v___x_1469_; 
v___x_1468_ = lean_uint64_sub(v___x_1464_, v___y_1434_);
v___x_1469_ = lean_uint64_dec_eq(v___x_1468_, v___y_1432_);
if (v___x_1469_ == 0)
{
uint64_t v___x_1470_; uint8_t v___x_1471_; 
v___x_1470_ = 64ULL;
v___x_1471_ = lean_uint64_dec_lt(v___x_1468_, v___x_1470_);
if (v___x_1471_ == 0)
{
uint8_t v___x_1472_; 
v___x_1472_ = lean_uint64_dec_eq(v___x_1468_, v___x_1470_);
if (v___x_1472_ == 0)
{
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v___y_1432_;
goto v___jp_1324_;
}
else
{
uint64_t v___x_1473_; uint8_t v___x_1474_; 
v___x_1473_ = 9223372036854775808ULL;
v___x_1474_ = lean_uint64_dec_lt(v___x_1473_, v___y_1430_);
if (v___x_1474_ == 0)
{
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v___y_1432_;
goto v___jp_1324_;
}
else
{
uint64_t v___x_1475_; 
v___x_1475_ = 1ULL;
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v___x_1475_;
goto v___jp_1324_;
}
}
}
else
{
uint64_t v_quotient_1476_; uint64_t v___x_1477_; uint64_t v___x_1478_; uint64_t v___x_1479_; uint64_t v_remainder_1480_; uint64_t v___x_1481_; uint64_t v_half_1482_; uint8_t v___x_1483_; 
v_quotient_1476_ = lean_uint64_shift_right(v___y_1430_, v___x_1468_);
v___x_1477_ = 1ULL;
v___x_1478_ = lean_uint64_shift_left(v___x_1477_, v___x_1468_);
v___x_1479_ = lean_uint64_sub(v___x_1478_, v___x_1477_);
v_remainder_1480_ = lean_uint64_land(v___y_1430_, v___x_1479_);
v___x_1481_ = lean_uint64_sub(v___x_1468_, v___x_1477_);
v_half_1482_ = lean_uint64_shift_left(v___x_1477_, v___x_1481_);
v___x_1483_ = lean_uint64_dec_lt(v_remainder_1480_, v_half_1482_);
if (v___x_1483_ == 0)
{
uint8_t v___x_1484_; 
v___x_1484_ = lean_uint64_dec_lt(v_half_1482_, v_remainder_1480_);
if (v___x_1484_ == 0)
{
uint64_t v___x_1485_; uint8_t v___x_1486_; 
v___x_1485_ = lean_uint64_land(v_quotient_1476_, v___x_1477_);
v___x_1486_ = lean_uint64_dec_eq(v___x_1485_, v___y_1432_);
if (v___x_1486_ == 0)
{
uint64_t v___x_1487_; 
v___x_1487_ = lean_uint64_add(v_quotient_1476_, v___x_1477_);
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v___x_1487_;
goto v___jp_1324_;
}
else
{
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v_quotient_1476_;
goto v___jp_1324_;
}
}
else
{
uint64_t v___x_1488_; 
v___x_1488_ = lean_uint64_add(v_quotient_1476_, v___x_1477_);
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v___x_1488_;
goto v___jp_1324_;
}
}
else
{
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v_quotient_1476_;
goto v___jp_1324_;
}
}
}
else
{
v___y_1325_ = v___y_1431_;
v___y_1326_ = v___y_1432_;
v___y_1327_ = v___y_1433_;
v___y_1328_ = v___y_1430_;
goto v___jp_1324_;
}
}
}
}
v___jp_1489_:
{
uint64_t v___x_1497_; uint64_t v___x_1498_; uint8_t v___x_1499_; 
v___x_1497_ = 1ULL;
v___x_1498_ = lean_uint64_shift_right(v___y_1495_, v___x_1497_);
v___x_1499_ = lean_uint64_dec_eq(v___x_1498_, v___y_1492_);
if (v___x_1499_ == 0)
{
uint64_t v___x_1500_; 
v___x_1500_ = lean_uint64_add(v___y_1496_, v___x_1497_);
v___y_1430_ = v___y_1490_;
v___y_1431_ = v___y_1491_;
v___y_1432_ = v___y_1492_;
v___y_1433_ = v___y_1493_;
v___y_1434_ = v___y_1494_;
v___y_1435_ = v___x_1500_;
goto v___jp_1429_;
}
else
{
v___y_1430_ = v___y_1490_;
v___y_1431_ = v___y_1491_;
v___y_1432_ = v___y_1492_;
v___y_1433_ = v___y_1493_;
v___y_1434_ = v___y_1494_;
v___y_1435_ = v___y_1496_;
goto v___jp_1429_;
}
}
v___jp_1501_:
{
uint64_t v___x_1511_; uint8_t v___x_1512_; 
v___x_1511_ = lean_uint64_shift_right(v___y_1508_, v___y_1502_);
v___x_1512_ = lean_uint64_dec_eq(v___x_1511_, v___y_1506_);
if (v___x_1512_ == 0)
{
uint64_t v___x_1513_; 
v___x_1513_ = lean_uint64_add(v___y_1505_, v___y_1502_);
v___y_1490_ = v___y_1503_;
v___y_1491_ = v___y_1504_;
v___y_1492_ = v___y_1506_;
v___y_1493_ = v___y_1507_;
v___y_1494_ = v___y_1509_;
v___y_1495_ = v___y_1510_;
v___y_1496_ = v___x_1513_;
goto v___jp_1489_;
}
else
{
v___y_1490_ = v___y_1503_;
v___y_1491_ = v___y_1504_;
v___y_1492_ = v___y_1506_;
v___y_1493_ = v___y_1507_;
v___y_1494_ = v___y_1509_;
v___y_1495_ = v___y_1510_;
v___y_1496_ = v___y_1505_;
goto v___jp_1489_;
}
}
v___jp_1514_:
{
uint64_t v___x_1522_; uint64_t v___x_1523_; uint8_t v___x_1524_; 
v___x_1522_ = 2ULL;
v___x_1523_ = lean_uint64_shift_right(v___y_1519_, v___x_1522_);
v___x_1524_ = lean_uint64_dec_eq(v___x_1523_, v___y_1517_);
if (v___x_1524_ == 0)
{
v___y_1502_ = v___x_1522_;
v___y_1503_ = v___y_1515_;
v___y_1504_ = v___y_1516_;
v___y_1505_ = v___y_1521_;
v___y_1506_ = v___y_1517_;
v___y_1507_ = v___y_1518_;
v___y_1508_ = v___y_1519_;
v___y_1509_ = v___y_1520_;
v___y_1510_ = v___x_1523_;
goto v___jp_1501_;
}
else
{
v___y_1502_ = v___x_1522_;
v___y_1503_ = v___y_1515_;
v___y_1504_ = v___y_1516_;
v___y_1505_ = v___y_1521_;
v___y_1506_ = v___y_1517_;
v___y_1507_ = v___y_1518_;
v___y_1508_ = v___y_1519_;
v___y_1509_ = v___y_1520_;
v___y_1510_ = v___y_1519_;
goto v___jp_1501_;
}
}
v___jp_1525_:
{
uint64_t v___x_1535_; uint8_t v___x_1536_; 
v___x_1535_ = lean_uint64_shift_right(v___y_1531_, v___y_1528_);
v___x_1536_ = lean_uint64_dec_eq(v___x_1535_, v___y_1529_);
if (v___x_1536_ == 0)
{
uint64_t v___x_1537_; 
v___x_1537_ = lean_uint64_add(v___y_1533_, v___y_1528_);
v___y_1515_ = v___y_1526_;
v___y_1516_ = v___y_1527_;
v___y_1517_ = v___y_1529_;
v___y_1518_ = v___y_1530_;
v___y_1519_ = v___y_1534_;
v___y_1520_ = v___y_1532_;
v___y_1521_ = v___x_1537_;
goto v___jp_1514_;
}
else
{
v___y_1515_ = v___y_1526_;
v___y_1516_ = v___y_1527_;
v___y_1517_ = v___y_1529_;
v___y_1518_ = v___y_1530_;
v___y_1519_ = v___y_1534_;
v___y_1520_ = v___y_1532_;
v___y_1521_ = v___y_1533_;
goto v___jp_1514_;
}
}
v___jp_1538_:
{
uint64_t v___x_1546_; uint64_t v___x_1547_; uint8_t v___x_1548_; 
v___x_1546_ = 4ULL;
v___x_1547_ = lean_uint64_shift_right(v___y_1543_, v___x_1546_);
v___x_1548_ = lean_uint64_dec_eq(v___x_1547_, v___y_1541_);
if (v___x_1548_ == 0)
{
v___y_1526_ = v___y_1539_;
v___y_1527_ = v___y_1540_;
v___y_1528_ = v___x_1546_;
v___y_1529_ = v___y_1541_;
v___y_1530_ = v___y_1542_;
v___y_1531_ = v___y_1543_;
v___y_1532_ = v___y_1544_;
v___y_1533_ = v___y_1545_;
v___y_1534_ = v___x_1547_;
goto v___jp_1525_;
}
else
{
v___y_1526_ = v___y_1539_;
v___y_1527_ = v___y_1540_;
v___y_1528_ = v___x_1546_;
v___y_1529_ = v___y_1541_;
v___y_1530_ = v___y_1542_;
v___y_1531_ = v___y_1543_;
v___y_1532_ = v___y_1544_;
v___y_1533_ = v___y_1545_;
v___y_1534_ = v___y_1543_;
goto v___jp_1525_;
}
}
v___jp_1549_:
{
uint64_t v___x_1559_; uint8_t v___x_1560_; 
v___x_1559_ = lean_uint64_shift_right(v___y_1557_, v___y_1552_);
v___x_1560_ = lean_uint64_dec_eq(v___x_1559_, v___y_1553_);
if (v___x_1560_ == 0)
{
uint64_t v___x_1561_; 
v___x_1561_ = lean_uint64_add(v___y_1554_, v___y_1552_);
v___y_1539_ = v___y_1550_;
v___y_1540_ = v___y_1551_;
v___y_1541_ = v___y_1553_;
v___y_1542_ = v___y_1555_;
v___y_1543_ = v___y_1558_;
v___y_1544_ = v___y_1556_;
v___y_1545_ = v___x_1561_;
goto v___jp_1538_;
}
else
{
v___y_1539_ = v___y_1550_;
v___y_1540_ = v___y_1551_;
v___y_1541_ = v___y_1553_;
v___y_1542_ = v___y_1555_;
v___y_1543_ = v___y_1558_;
v___y_1544_ = v___y_1556_;
v___y_1545_ = v___y_1554_;
goto v___jp_1538_;
}
}
v___jp_1562_:
{
uint64_t v___x_1570_; uint64_t v___x_1571_; uint8_t v___x_1572_; 
v___x_1570_ = 8ULL;
v___x_1571_ = lean_uint64_shift_right(v___y_1568_, v___x_1570_);
v___x_1572_ = lean_uint64_dec_eq(v___x_1571_, v___y_1565_);
if (v___x_1572_ == 0)
{
v___y_1550_ = v___y_1563_;
v___y_1551_ = v___y_1564_;
v___y_1552_ = v___x_1570_;
v___y_1553_ = v___y_1565_;
v___y_1554_ = v___y_1569_;
v___y_1555_ = v___y_1566_;
v___y_1556_ = v___y_1567_;
v___y_1557_ = v___y_1568_;
v___y_1558_ = v___x_1571_;
goto v___jp_1549_;
}
else
{
v___y_1550_ = v___y_1563_;
v___y_1551_ = v___y_1564_;
v___y_1552_ = v___x_1570_;
v___y_1553_ = v___y_1565_;
v___y_1554_ = v___y_1569_;
v___y_1555_ = v___y_1566_;
v___y_1556_ = v___y_1567_;
v___y_1557_ = v___y_1568_;
v___y_1558_ = v___y_1568_;
goto v___jp_1549_;
}
}
v___jp_1573_:
{
uint64_t v___x_1583_; uint8_t v___x_1584_; 
v___x_1583_ = lean_uint64_shift_right(v___y_1576_, v___y_1577_);
v___x_1584_ = lean_uint64_dec_eq(v___x_1583_, v___y_1578_);
if (v___x_1584_ == 0)
{
uint64_t v___x_1585_; 
v___x_1585_ = lean_uint64_add(v___y_1580_, v___y_1577_);
v___y_1563_ = v___y_1574_;
v___y_1564_ = v___y_1575_;
v___y_1565_ = v___y_1578_;
v___y_1566_ = v___y_1579_;
v___y_1567_ = v___y_1581_;
v___y_1568_ = v___y_1582_;
v___y_1569_ = v___x_1585_;
goto v___jp_1562_;
}
else
{
v___y_1563_ = v___y_1574_;
v___y_1564_ = v___y_1575_;
v___y_1565_ = v___y_1578_;
v___y_1566_ = v___y_1579_;
v___y_1567_ = v___y_1581_;
v___y_1568_ = v___y_1582_;
v___y_1569_ = v___y_1580_;
goto v___jp_1562_;
}
}
v___jp_1586_:
{
uint64_t v___x_1594_; uint64_t v___x_1595_; uint8_t v___x_1596_; 
v___x_1594_ = 16ULL;
v___x_1595_ = lean_uint64_shift_right(v___y_1589_, v___x_1594_);
v___x_1596_ = lean_uint64_dec_eq(v___x_1595_, v___y_1590_);
if (v___x_1596_ == 0)
{
v___y_1574_ = v___y_1587_;
v___y_1575_ = v___y_1588_;
v___y_1576_ = v___y_1589_;
v___y_1577_ = v___x_1594_;
v___y_1578_ = v___y_1590_;
v___y_1579_ = v___y_1591_;
v___y_1580_ = v___y_1593_;
v___y_1581_ = v___y_1592_;
v___y_1582_ = v___x_1595_;
goto v___jp_1573_;
}
else
{
v___y_1574_ = v___y_1587_;
v___y_1575_ = v___y_1588_;
v___y_1576_ = v___y_1589_;
v___y_1577_ = v___x_1594_;
v___y_1578_ = v___y_1590_;
v___y_1579_ = v___y_1591_;
v___y_1580_ = v___y_1593_;
v___y_1581_ = v___y_1592_;
v___y_1582_ = v___y_1589_;
goto v___jp_1573_;
}
}
v___jp_1597_:
{
uint64_t v___x_1605_; uint8_t v___x_1606_; 
v___x_1605_ = lean_uint64_shift_right(v___y_1598_, v___y_1600_);
v___x_1606_ = lean_uint64_dec_eq(v___x_1605_, v___y_1601_);
if (v___x_1606_ == 0)
{
v___y_1587_ = v___y_1598_;
v___y_1588_ = v___y_1599_;
v___y_1589_ = v___y_1604_;
v___y_1590_ = v___y_1601_;
v___y_1591_ = v___y_1602_;
v___y_1592_ = v___y_1603_;
v___y_1593_ = v___y_1600_;
goto v___jp_1586_;
}
else
{
v___y_1587_ = v___y_1598_;
v___y_1588_ = v___y_1599_;
v___y_1589_ = v___y_1604_;
v___y_1590_ = v___y_1601_;
v___y_1591_ = v___y_1602_;
v___y_1592_ = v___y_1603_;
v___y_1593_ = v___y_1601_;
goto v___jp_1586_;
}
}
v___jp_1607_:
{
uint64_t v___x_1612_; uint8_t v___x_1613_; 
v___x_1612_ = 0ULL;
v___x_1613_ = lean_uint64_dec_eq(v___y_1608_, v___x_1612_);
if (v___x_1613_ == 0)
{
uint64_t v___x_1614_; uint64_t v___x_1615_; uint8_t v___x_1616_; 
v___x_1614_ = 32ULL;
v___x_1615_ = lean_uint64_shift_right(v___y_1608_, v___x_1614_);
v___x_1616_ = lean_uint64_dec_eq(v___x_1615_, v___x_1612_);
if (v___x_1616_ == 0)
{
v___y_1598_ = v___y_1608_;
v___y_1599_ = v___y_1609_;
v___y_1600_ = v___x_1614_;
v___y_1601_ = v___x_1612_;
v___y_1602_ = v___y_1610_;
v___y_1603_ = v___y_1611_;
v___y_1604_ = v___x_1615_;
goto v___jp_1597_;
}
else
{
v___y_1598_ = v___y_1608_;
v___y_1599_ = v___y_1609_;
v___y_1600_ = v___x_1614_;
v___y_1601_ = v___x_1612_;
v___y_1602_ = v___y_1610_;
v___y_1603_ = v___y_1611_;
v___y_1604_ = v___y_1608_;
goto v___jp_1597_;
}
}
else
{
if (v___y_1609_ == 0)
{
uint32_t v___x_1617_; 
v___x_1617_ = 0;
return v___x_1617_;
}
else
{
uint32_t v___x_1618_; 
v___x_1618_ = 2147483648;
return v___x_1618_;
}
}
}
v___jp_1619_:
{
uint64_t v___x_1626_; uint64_t v___x_1627_; uint64_t v___x_1628_; uint8_t v___x_1629_; 
v___x_1626_ = lean_uint64_mul(v___y_1624_, v___y_1623_);
v___x_1627_ = lean_uint64_add(v___y_1622_, v___y_1625_);
v___x_1628_ = 281474976710656ULL;
v___x_1629_ = lean_uint64_dec_lt(v___x_1626_, v___x_1628_);
if (v___x_1629_ == 0)
{
v___y_1608_ = v___x_1626_;
v___y_1609_ = v___y_1620_;
v___y_1610_ = v___y_1621_;
v___y_1611_ = v___x_1627_;
goto v___jp_1607_;
}
else
{
uint64_t v___x_1630_; uint8_t v___x_1631_; 
v___x_1630_ = 123ULL;
v___x_1631_ = lean_uint64_dec_le(v___x_1627_, v___x_1630_);
if (v___x_1631_ == 0)
{
v___y_1608_ = v___x_1626_;
v___y_1609_ = v___y_1620_;
v___y_1610_ = v___y_1621_;
v___y_1611_ = v___x_1627_;
goto v___jp_1607_;
}
else
{
uint64_t v___x_1632_; uint8_t v___x_1633_; 
v___x_1632_ = 0ULL;
v___x_1633_ = lean_uint64_dec_eq(v___x_1626_, v___x_1632_);
if (v___x_1633_ == 0)
{
uint64_t v___x_1634_; uint64_t v___x_1635_; uint8_t v___x_1636_; 
v___x_1634_ = 149ULL;
v___x_1635_ = lean_uint64_sub(v___x_1634_, v___x_1627_);
v___x_1636_ = lean_uint64_dec_eq(v___x_1635_, v___x_1632_);
if (v___x_1636_ == 0)
{
uint64_t v___x_1637_; uint8_t v___x_1638_; 
v___x_1637_ = 64ULL;
v___x_1638_ = lean_uint64_dec_lt(v___x_1635_, v___x_1637_);
if (v___x_1638_ == 0)
{
uint8_t v___x_1639_; 
v___x_1639_ = lean_uint64_dec_eq(v___x_1635_, v___x_1637_);
if (v___x_1639_ == 0)
{
v___y_1346_ = v___y_1620_;
v___y_1347_ = v___x_1632_;
v___y_1348_ = v___y_1621_;
v___y_1349_ = v___x_1632_;
goto v___jp_1345_;
}
else
{
uint64_t v___x_1640_; uint8_t v___x_1641_; 
v___x_1640_ = 9223372036854775808ULL;
v___x_1641_ = lean_uint64_dec_lt(v___x_1640_, v___x_1626_);
if (v___x_1641_ == 0)
{
v___y_1346_ = v___y_1620_;
v___y_1347_ = v___x_1632_;
v___y_1348_ = v___y_1621_;
v___y_1349_ = v___x_1632_;
goto v___jp_1345_;
}
else
{
uint64_t v___x_1642_; 
v___x_1642_ = 1ULL;
v___y_1346_ = v___y_1620_;
v___y_1347_ = v___x_1632_;
v___y_1348_ = v___y_1621_;
v___y_1349_ = v___x_1642_;
goto v___jp_1345_;
}
}
}
else
{
uint64_t v_quotient_1643_; uint64_t v___x_1644_; uint64_t v___x_1645_; uint64_t v___x_1646_; uint64_t v_remainder_1647_; uint64_t v___x_1648_; uint64_t v_half_1649_; uint8_t v___x_1650_; 
v_quotient_1643_ = lean_uint64_shift_right(v___x_1626_, v___x_1635_);
v___x_1644_ = 1ULL;
v___x_1645_ = lean_uint64_shift_left(v___x_1644_, v___x_1635_);
v___x_1646_ = lean_uint64_sub(v___x_1645_, v___x_1644_);
v_remainder_1647_ = lean_uint64_land(v___x_1626_, v___x_1646_);
v___x_1648_ = lean_uint64_sub(v___x_1635_, v___x_1644_);
v_half_1649_ = lean_uint64_shift_left(v___x_1644_, v___x_1648_);
v___x_1650_ = lean_uint64_dec_lt(v_remainder_1647_, v_half_1649_);
if (v___x_1650_ == 0)
{
uint8_t v___x_1651_; 
v___x_1651_ = lean_uint64_dec_lt(v_half_1649_, v_remainder_1647_);
if (v___x_1651_ == 0)
{
uint64_t v___x_1652_; uint8_t v___x_1653_; 
v___x_1652_ = lean_uint64_land(v_quotient_1643_, v___x_1644_);
v___x_1653_ = lean_uint64_dec_eq(v___x_1652_, v___x_1632_);
if (v___x_1653_ == 0)
{
uint64_t v___x_1654_; 
v___x_1654_ = lean_uint64_add(v_quotient_1643_, v___x_1644_);
v___y_1346_ = v___y_1620_;
v___y_1347_ = v___x_1632_;
v___y_1348_ = v___y_1621_;
v___y_1349_ = v___x_1654_;
goto v___jp_1345_;
}
else
{
v___y_1346_ = v___y_1620_;
v___y_1347_ = v___x_1632_;
v___y_1348_ = v___y_1621_;
v___y_1349_ = v_quotient_1643_;
goto v___jp_1345_;
}
}
else
{
uint64_t v___x_1655_; 
v___x_1655_ = lean_uint64_add(v_quotient_1643_, v___x_1644_);
v___y_1346_ = v___y_1620_;
v___y_1347_ = v___x_1632_;
v___y_1348_ = v___y_1621_;
v___y_1349_ = v___x_1655_;
goto v___jp_1345_;
}
}
else
{
v___y_1346_ = v___y_1620_;
v___y_1347_ = v___x_1632_;
v___y_1348_ = v___y_1621_;
v___y_1349_ = v_quotient_1643_;
goto v___jp_1345_;
}
}
}
else
{
v___y_1346_ = v___y_1620_;
v___y_1347_ = v___x_1632_;
v___y_1348_ = v___y_1621_;
v___y_1349_ = v___x_1626_;
goto v___jp_1345_;
}
}
else
{
if (v___y_1620_ == 0)
{
uint32_t v___x_1656_; 
v___x_1656_ = 0;
return v___x_1656_;
}
else
{
uint32_t v___x_1657_; 
v___x_1657_ = 2147483648;
return v___x_1657_;
}
}
}
}
}
v___jp_1661_:
{
uint64_t v___x_1667_; uint64_t v___x_1668_; uint8_t v___x_1669_; 
v___x_1667_ = lean_uint32_to_uint64(v_ey_1660_);
v___x_1668_ = 0ULL;
v___x_1669_ = lean_uint64_dec_eq(v___x_1667_, v___x_1668_);
if (v___x_1669_ == 0)
{
uint64_t v___x_1670_; uint64_t v___x_1671_; 
v___x_1670_ = 1ULL;
v___x_1671_ = lean_uint64_sub(v___x_1667_, v___x_1670_);
v___y_1620_ = v___y_1662_;
v___y_1621_ = v___y_1663_;
v___y_1622_ = v___y_1666_;
v___y_1623_ = v___y_1664_;
v___y_1624_ = v___y_1665_;
v___y_1625_ = v___x_1671_;
goto v___jp_1619_;
}
else
{
v___y_1620_ = v___y_1662_;
v___y_1621_ = v___y_1663_;
v___y_1622_ = v___y_1666_;
v___y_1623_ = v___y_1664_;
v___y_1624_ = v___y_1665_;
v___y_1625_ = v___x_1668_;
goto v___jp_1619_;
}
}
v___jp_1672_:
{
uint64_t v___x_1677_; uint64_t v___x_1678_; uint8_t v___x_1679_; 
v___x_1677_ = lean_uint32_to_uint64(v_ex_1658_);
v___x_1678_ = 0ULL;
v___x_1679_ = lean_uint64_dec_eq(v___x_1677_, v___x_1678_);
if (v___x_1679_ == 0)
{
uint64_t v___x_1680_; uint64_t v___x_1681_; 
v___x_1680_ = 1ULL;
v___x_1681_ = lean_uint64_sub(v___x_1677_, v___x_1680_);
v___y_1662_ = v___y_1673_;
v___y_1663_ = v___y_1674_;
v___y_1664_ = v___y_1676_;
v___y_1665_ = v___y_1675_;
v___y_1666_ = v___x_1681_;
goto v___jp_1661_;
}
else
{
v___y_1662_ = v___y_1673_;
v___y_1663_ = v___y_1674_;
v___y_1664_ = v___y_1676_;
v___y_1665_ = v___y_1675_;
v___y_1666_ = v___x_1678_;
goto v___jp_1661_;
}
}
v___jp_1682_:
{
uint32_t v___x_1687_; uint8_t v___x_1688_; 
v___x_1687_ = 0;
v___x_1688_ = lean_uint32_dec_eq(v_ey_1660_, v___x_1687_);
if (v___x_1688_ == 0)
{
uint64_t v___x_1689_; uint64_t v___x_1690_; uint64_t v___x_1691_; 
v___x_1689_ = lean_uint32_to_uint64(v___y_1684_);
v___x_1690_ = 8388608ULL;
v___x_1691_ = lean_uint64_lor(v___x_1689_, v___x_1690_);
v___y_1673_ = v___y_1683_;
v___y_1674_ = v___y_1685_;
v___y_1675_ = v___y_1686_;
v___y_1676_ = v___x_1691_;
goto v___jp_1672_;
}
else
{
uint64_t v___x_1692_; 
v___x_1692_ = lean_uint32_to_uint64(v___y_1684_);
v___y_1673_ = v___y_1683_;
v___y_1674_ = v___y_1685_;
v___y_1675_ = v___y_1686_;
v___y_1676_ = v___x_1692_;
goto v___jp_1672_;
}
}
v___jp_1693_:
{
uint32_t v___x_1695_; uint32_t v_xFraction_1696_; uint32_t v_yFraction_1697_; uint32_t v___x_1698_; uint8_t v___x_1699_; 
v___x_1695_ = 8388607;
v_xFraction_1696_ = lean_uint32_land(v___y_1213_, v___x_1695_);
v_yFraction_1697_ = lean_uint32_land(v___y_1214_, v___x_1695_);
v___x_1698_ = 0;
v___x_1699_ = lean_uint32_dec_eq(v_ex_1658_, v___x_1698_);
if (v___x_1699_ == 0)
{
uint64_t v___x_1700_; uint64_t v___x_1701_; uint64_t v___x_1702_; 
v___x_1700_ = lean_uint32_to_uint64(v_xFraction_1696_);
v___x_1701_ = 8388608ULL;
v___x_1702_ = lean_uint64_lor(v___x_1700_, v___x_1701_);
v___y_1683_ = v___y_1694_;
v___y_1684_ = v_yFraction_1697_;
v___y_1685_ = v___x_1695_;
v___y_1686_ = v___x_1702_;
goto v___jp_1682_;
}
else
{
uint64_t v___x_1703_; 
v___x_1703_ = lean_uint32_to_uint64(v_xFraction_1696_);
v___y_1683_ = v___y_1694_;
v___y_1684_ = v_yFraction_1697_;
v___y_1685_ = v___x_1695_;
v___y_1686_ = v___x_1703_;
goto v___jp_1682_;
}
}
v___jp_1704_:
{
if (v___y_1706_ == 0)
{
v___y_1694_ = v___x_1212_;
goto v___jp_1693_;
}
else
{
v___y_1694_ = v___y_1705_;
goto v___jp_1693_;
}
}
v___jp_1710_:
{
if (v___y_1712_ == 0)
{
if (v___y_1713_ == 0)
{
v___y_1705_ = v___y_1711_;
v___y_1706_ = v___x_1709_;
goto v___jp_1704_;
}
else
{
v___y_1694_ = v___x_1212_;
goto v___jp_1693_;
}
}
else
{
v___y_1705_ = v___y_1711_;
v___y_1706_ = v___y_1713_;
goto v___jp_1704_;
}
}
v___jp_1714_:
{
uint32_t v___x_1717_; uint32_t v___x_1718_; uint32_t v___x_1719_; uint8_t v___x_1720_; 
v___x_1717_ = 2147483648;
v___x_1718_ = lean_uint32_land(v___y_1214_, v___x_1717_);
v___x_1719_ = 0;
v___x_1720_ = lean_uint32_dec_eq(v___x_1718_, v___x_1719_);
if (v___x_1720_ == 0)
{
v___y_1711_ = v___y_1715_;
v___y_1712_ = v___y_1716_;
v___y_1713_ = v___x_1212_;
goto v___jp_1710_;
}
else
{
v___y_1711_ = v___y_1715_;
v___y_1712_ = v___y_1716_;
v___y_1713_ = v___y_1715_;
goto v___jp_1710_;
}
}
v___jp_1721_:
{
if (v___y_1722_ == 0)
{
uint32_t v___x_1723_; uint32_t v___x_1724_; uint32_t v___x_1725_; uint8_t v___x_1726_; 
v___x_1723_ = 2147483648;
v___x_1724_ = lean_uint32_land(v___y_1213_, v___x_1723_);
v___x_1725_ = 0;
v___x_1726_ = lean_uint32_dec_eq(v___x_1724_, v___x_1725_);
if (v___x_1726_ == 0)
{
v___y_1715_ = v___y_1722_;
v___y_1716_ = v___x_1212_;
goto v___jp_1714_;
}
else
{
v___y_1715_ = v___y_1722_;
v___y_1716_ = v___y_1722_;
goto v___jp_1714_;
}
}
else
{
lean_object* v___x_1727_; lean_object* v___x_1728_; lean_object* v___x_1729_; uint32_t v___x_1730_; 
v___x_1727_ = lean_uint32_to_nat(v___y_1213_);
v___x_1728_ = lean_uint32_to_nat(v___y_1214_);
v___x_1729_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1727_, v___x_1728_);
v___x_1730_ = lean_uint32_of_nat(v___x_1729_);
lean_dec(v___x_1729_);
return v___x_1730_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__4___boxed(lean_object* v___x_1745_, lean_object* v___y_1746_, lean_object* v___y_1747_){
_start:
{
uint8_t v___x_9546__boxed_1748_; uint32_t v___y_9547__boxed_1749_; uint32_t v___y_9548__boxed_1750_; uint32_t v_res_1751_; lean_object* v_r_1752_; 
v___x_9546__boxed_1748_ = lean_unbox(v___x_1745_);
v___y_9547__boxed_1749_ = lean_unbox_uint32(v___y_1746_);
lean_dec(v___y_1746_);
v___y_9548__boxed_1750_ = lean_unbox_uint32(v___y_1747_);
lean_dec(v___y_1747_);
v_res_1751_ = lp_competition_main___lam__4(v___x_9546__boxed_1748_, v___y_9547__boxed_1749_, v___y_9548__boxed_1750_);
v_r_1752_ = lean_box_uint32(v_res_1751_);
return v_r_1752_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1772_; lean_object* v___x_1773_; lean_object* v___x_1774_; uint8_t v___x_1775_; 
v___x_1772_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1773_ = lean_io_getenv(v___x_1772_);
v___x_1774_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1775_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1773_, v___x_1774_);
if (v___x_1775_ == 0)
{
lean_object* v___x_1776_; uint8_t v___x_1777_; 
v___x_1776_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1777_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1773_, v___x_1776_);
if (v___x_1777_ == 0)
{
lean_object* v___x_1778_; uint8_t v___x_1779_; 
v___x_1778_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_1779_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1773_, v___x_1778_);
lean_dec(v___x_1773_);
if (v___x_1779_ == 0)
{
lean_object* v___x_1780_; lean_object* v___x_1781_; 
v___x_1780_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_1781_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1781_, 0, v___x_1780_);
return v___x_1781_;
}
else
{
lean_object* v___f_1782_; lean_object* v___x_1783_; lean_object* v___f_1784_; lean_object* v___x_1785_; lean_object* v___x_1786_; lean_object* v___x_1787_; 
v___f_1782_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_1783_ = lean_box(v___x_1779_);
v___f_1784_ = lean_alloc_closure((void*)(lp_competition_main___lam__1___boxed), 3, 1);
lean_closure_set(v___f_1784_, 0, v___x_1783_);
v___x_1785_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_1786_ = ((lean_object*)(lp_competition_main___closed__11));
v___x_1787_ = lp_competition_Bench_Suite_run(v___f_1782_, v___f_1784_, v___x_1785_, v___x_1786_);
return v___x_1787_;
}
}
else
{
lean_object* v___f_1788_; lean_object* v___x_1789_; lean_object* v___f_1790_; lean_object* v___x_1791_; lean_object* v___x_1792_; lean_object* v___x_1793_; 
lean_dec(v___x_1773_);
v___f_1788_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_1789_ = lean_box(v___x_1777_);
v___f_1790_ = lean_alloc_closure((void*)(lp_competition_main___lam__3___boxed), 3, 1);
lean_closure_set(v___f_1790_, 0, v___x_1789_);
v___x_1791_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_1792_ = ((lean_object*)(lp_competition_main___closed__12));
v___x_1793_ = lp_competition_Bench_Suite_run(v___f_1788_, v___f_1790_, v___x_1791_, v___x_1792_);
return v___x_1793_;
}
}
else
{
lean_object* v___f_1794_; lean_object* v___x_1795_; lean_object* v___f_1796_; lean_object* v___x_1797_; lean_object* v___x_1798_; lean_object* v___x_1799_; 
lean_dec(v___x_1773_);
v___f_1794_ = ((lean_object*)(lp_competition_main___closed__9));
v___x_1795_ = lean_box(v___x_1775_);
v___f_1796_ = lean_alloc_closure((void*)(lp_competition_main___lam__4___boxed), 3, 1);
lean_closure_set(v___f_1796_, 0, v___x_1795_);
v___x_1797_ = ((lean_object*)(lp_competition_main___closed__10));
v___x_1798_ = ((lean_object*)(lp_competition_main___closed__13));
v___x_1799_ = lp_competition_Bench_Suite_run(v___f_1794_, v___f_1796_, v___x_1797_, v___x_1798_);
return v___x_1799_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1800_){
_start:
{
lean_object* v_res_1801_; 
v_res_1801_ = _lean_main();
return v_res_1801_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R22Resident8CostMain(uint8_t builtin) {
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
  res = initialize_competition_R22Resident8CostMain(1 /* builtin */);
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
