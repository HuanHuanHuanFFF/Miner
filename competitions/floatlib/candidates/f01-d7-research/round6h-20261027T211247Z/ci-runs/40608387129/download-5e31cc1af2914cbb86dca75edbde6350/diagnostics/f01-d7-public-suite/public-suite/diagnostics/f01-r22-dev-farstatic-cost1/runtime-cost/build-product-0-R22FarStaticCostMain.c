// Lean compiler output
// Module: R22FarStaticCostMain
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
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_io_getenv(lean_object*);
uint8_t l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(lean_object*, lean_object*);
uint32_t lp_competition_Submission_R22FarOnlyAdd_coldAdd(uint32_t, uint32_t);
LEAN_EXPORT uint32_t lp_competition_runControl___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runControl___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runControl___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runControl___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runControl___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runControl___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runControl___closed__0 = (const lean_object*)&lp_competition_runControl___closed__0_value;
static const lean_closure_object lp_competition_runControl___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runControl___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runControl___closed__1 = (const lean_object*)&lp_competition_runControl___closed__1_value;
static const lean_closure_object lp_competition_runControl___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runControl___closed__2 = (const lean_object*)&lp_competition_runControl___closed__2_value;
static const lean_closure_object lp_competition_runControl___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runControl___closed__3 = (const lean_object*)&lp_competition_runControl___closed__3_value;
LEAN_EXPORT lean_object* lp_competition_runControl();
LEAN_EXPORT lean_object* lp_competition_runControl___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runFar___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runFar___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_runFar___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_runFar___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_runFar___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runFar___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runFar___closed__0 = (const lean_object*)&lp_competition_runFar___closed__0_value;
static const lean_closure_object lp_competition_runFar___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_runFar___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_runFar___closed__1 = (const lean_object*)&lp_competition_runFar___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_runFar();
LEAN_EXPORT lean_object* lp_competition_runFar___boxed(lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "BENCH_VARIANT"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_string_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "control"};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_ctor_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__1_value)}};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_string_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 4, .m_capacity = 4, .m_length = 3, .m_data = "far"};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_ctor_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_main___closed__3_value)}};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 37, .m_capacity = 37, .m_length = 36, .m_data = "BENCH_VARIANT must be control or far"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_ctor_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__5_value)}};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_runControl___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
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
LEAN_EXPORT lean_object* lp_competition_runControl___lam__0___boxed(lean_object* v___y_124_, lean_object* v___y_125_){
_start:
{
uint32_t v___y_2190__boxed_126_; uint32_t v___y_2191__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_2190__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_2191__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_runControl___lam__0(v___y_2190__boxed_126_, v___y_2191__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_runControl___lam__1(uint32_t v___y_130_, uint32_t v___y_131_){
_start:
{
uint32_t v___y_133_; uint32_t v___y_137_; uint32_t v___y_141_; uint32_t v___y_142_; uint32_t v___y_143_; uint8_t v___y_147_; uint32_t v___y_148_; uint64_t v___y_149_; uint64_t v___y_150_; uint32_t v___y_162_; uint32_t v___y_163_; uint32_t v___y_164_; uint8_t v___y_168_; uint32_t v___y_169_; uint64_t v___y_170_; uint64_t v___y_171_; uint8_t v___y_183_; uint8_t v___y_199_; uint8_t v___y_213_; uint8_t v___y_230_; float v___y_237_; float v___y_238_; float v___y_252_; uint8_t v___y_253_; float v___y_268_; uint32_t v___x_277_; uint32_t v___x_278_; uint8_t v___y_280_; uint32_t v___x_292_; uint32_t v___y_294_; uint32_t v___y_295_; uint32_t v___y_296_; uint32_t v___y_297_; uint8_t v___y_304_; uint32_t v___y_305_; uint32_t v___y_306_; uint32_t v___y_307_; uint8_t v___y_311_; uint64_t v___y_312_; uint32_t v___y_313_; uint64_t v___y_314_; uint64_t v___y_315_; uint8_t v___y_325_; uint32_t v___y_326_; uint64_t v___y_327_; uint64_t v___y_328_; uint8_t v___y_329_; uint64_t v___y_330_; uint8_t v___y_337_; uint64_t v___y_338_; uint64_t v___y_339_; uint32_t v___y_340_; uint64_t v___y_341_; uint8_t v___y_347_; uint64_t v___y_348_; uint32_t v___y_349_; uint64_t v___y_350_; uint64_t v___y_351_; uint64_t v___y_352_; uint64_t v___y_407_; uint8_t v___y_408_; uint32_t v___y_409_; uint64_t v___y_410_; uint64_t v___y_411_; uint64_t v___y_412_; uint64_t v___y_413_; uint64_t v___y_419_; uint8_t v___y_420_; uint64_t v___y_421_; uint64_t v___y_422_; uint64_t v___y_423_; uint32_t v___y_424_; uint64_t v___y_425_; uint64_t v___y_426_; uint64_t v___y_427_; uint8_t v___y_432_; uint32_t v___y_433_; uint64_t v___y_434_; uint64_t v___y_435_; uint64_t v___y_436_; uint64_t v___y_437_; uint64_t v___y_438_; uint8_t v___y_443_; uint64_t v___y_444_; uint64_t v___y_445_; uint64_t v___y_446_; uint64_t v___y_447_; uint32_t v___y_448_; uint64_t v___y_449_; uint64_t v___y_450_; uint64_t v___y_451_; uint8_t v___y_456_; uint32_t v___y_457_; uint64_t v___y_458_; uint64_t v___y_459_; uint64_t v___y_460_; uint64_t v___y_461_; uint64_t v___y_462_; uint64_t v___y_467_; uint8_t v___y_468_; uint64_t v___y_469_; uint64_t v___y_470_; uint32_t v___y_471_; uint64_t v___y_472_; uint64_t v___y_473_; uint64_t v___y_474_; uint64_t v___y_475_; uint64_t v___y_480_; uint8_t v___y_481_; uint32_t v___y_482_; uint64_t v___y_483_; uint64_t v___y_484_; uint64_t v___y_485_; uint64_t v___y_486_; uint8_t v___y_491_; uint64_t v___y_492_; uint64_t v___y_493_; uint64_t v___y_494_; uint32_t v___y_495_; uint64_t v___y_496_; uint64_t v___y_497_; uint64_t v___y_498_; uint64_t v___y_499_; uint8_t v___y_504_; uint64_t v___y_505_; uint32_t v___y_506_; uint64_t v___y_507_; uint64_t v___y_508_; uint64_t v___y_509_; uint64_t v___y_510_; uint8_t v___y_515_; uint64_t v___y_516_; uint64_t v___y_517_; uint64_t v___y_518_; uint32_t v___y_519_; uint64_t v___y_520_; uint64_t v___y_521_; uint8_t v___y_525_; uint64_t v___y_526_; uint32_t v___y_527_; uint64_t v___y_528_; uint8_t v___y_537_; uint64_t v___y_538_; uint32_t v___y_539_; uint64_t v___y_540_; uint64_t v___y_541_; uint64_t v___y_542_; uint32_t v_ex_575_; uint32_t v___x_576_; uint32_t v_ey_577_; uint8_t v___y_579_; uint32_t v___y_580_; uint64_t v___y_581_; uint64_t v___y_582_; uint64_t v___y_583_; uint8_t v___y_590_; uint32_t v___y_591_; uint64_t v___y_592_; uint64_t v___y_593_; uint32_t v___y_600_; uint8_t v___y_601_; uint32_t v___y_602_; uint64_t v___y_603_; uint8_t v___y_611_; uint32_t v___x_621_; uint32_t v___x_622_; uint8_t v___x_623_; uint8_t v___y_625_; uint8_t v___y_626_; uint8_t v___y_628_; uint8_t v___y_629_; uint8_t v___y_630_; uint8_t v___y_632_; uint8_t v___y_633_; uint8_t v___y_639_; 
v___x_277_ = 23;
v___x_278_ = lean_uint32_shift_right(v___y_130_, v___x_277_);
v___x_292_ = 255;
v_ex_575_ = lean_uint32_land(v___x_278_, v___x_292_);
v___x_576_ = lean_uint32_shift_right(v___y_131_, v___x_277_);
v_ey_577_ = lean_uint32_land(v___x_576_, v___x_292_);
v___x_621_ = lean_uint32_add(v_ex_575_, v_ey_577_);
v___x_622_ = 128;
v___x_623_ = lean_uint32_dec_lt(v___x_621_, v___x_622_);
if (v___x_623_ == 0)
{
uint32_t v___x_648_; uint32_t v_a_649_; uint32_t v___x_650_; uint32_t v___x_651_; uint32_t v___x_652_; uint8_t v___x_653_; 
v___x_648_ = 2147483647;
v_a_649_ = lean_uint32_land(v___y_130_, v___x_648_);
v___x_650_ = 201326591;
v___x_651_ = 1;
v___x_652_ = lean_uint32_sub(v_a_649_, v___x_651_);
v___x_653_ = lean_uint32_dec_le(v___x_650_, v___x_652_);
if (v___x_653_ == 0)
{
v___y_280_ = v___x_653_;
goto v___jp_279_;
}
else
{
uint32_t v___x_654_; uint8_t v___x_655_; 
v___x_654_ = 2139095040;
v___x_655_ = lean_uint32_dec_lt(v_a_649_, v___x_654_);
v___y_280_ = v___x_655_;
goto v___jp_279_;
}
}
else
{
uint32_t v___x_656_; uint32_t v___x_657_; uint32_t v___x_658_; uint8_t v___x_659_; 
v___x_656_ = 4278190080;
v___x_657_ = 1;
v___x_658_ = lean_uint32_shift_left(v___y_130_, v___x_657_);
v___x_659_ = lean_uint32_dec_le(v___x_656_, v___x_658_);
if (v___x_659_ == 0)
{
uint32_t v___x_660_; uint8_t v___x_661_; 
v___x_660_ = lean_uint32_shift_left(v___y_131_, v___x_657_);
v___x_661_ = lean_uint32_dec_le(v___x_656_, v___x_660_);
v___y_639_ = v___x_661_;
goto v___jp_638_;
}
else
{
v___y_639_ = v___x_659_;
goto v___jp_638_;
}
}
v___jp_132_:
{
uint32_t v___x_134_; uint32_t v___x_135_; 
v___x_134_ = 8388608;
v___x_135_ = lean_uint32_lor(v___y_133_, v___x_134_);
return v___x_135_;
}
v___jp_136_:
{
uint32_t v___x_138_; uint32_t v___x_139_; 
v___x_138_ = 8388608;
v___x_139_ = lean_uint32_lor(v___y_137_, v___x_138_);
return v___x_139_;
}
v___jp_140_:
{
uint32_t v___x_144_; uint32_t v___x_145_; 
v___x_144_ = lean_uint32_land(v___y_141_, v___y_142_);
v___x_145_ = lean_uint32_lor(v___y_143_, v___x_144_);
return v___x_145_;
}
v___jp_146_:
{
uint8_t v___x_151_; 
v___x_151_ = lean_uint64_dec_eq(v___y_150_, v___y_149_);
if (v___x_151_ == 0)
{
uint64_t v___x_152_; uint8_t v___x_153_; 
v___x_152_ = 8388608ULL;
v___x_153_ = lean_uint64_dec_eq(v___y_150_, v___x_152_);
if (v___x_153_ == 0)
{
uint32_t v___x_154_; 
v___x_154_ = lean_uint64_to_uint32(v___y_150_);
if (v___y_147_ == 0)
{
uint32_t v___x_155_; 
v___x_155_ = 0;
v___y_141_ = v___x_154_;
v___y_142_ = v___y_148_;
v___y_143_ = v___x_155_;
goto v___jp_140_;
}
else
{
uint32_t v___x_156_; 
v___x_156_ = 2147483648;
v___y_141_ = v___x_154_;
v___y_142_ = v___y_148_;
v___y_143_ = v___x_156_;
goto v___jp_140_;
}
}
else
{
if (v___y_147_ == 0)
{
uint32_t v___x_157_; 
v___x_157_ = 0;
v___y_137_ = v___x_157_;
goto v___jp_136_;
}
else
{
uint32_t v___x_158_; 
v___x_158_ = 2147483648;
v___y_137_ = v___x_158_;
goto v___jp_136_;
}
}
}
else
{
if (v___y_147_ == 0)
{
uint32_t v___x_159_; 
v___x_159_ = 0;
return v___x_159_;
}
else
{
uint32_t v___x_160_; 
v___x_160_ = 2147483648;
return v___x_160_;
}
}
}
v___jp_161_:
{
uint32_t v___x_165_; uint32_t v___x_166_; 
v___x_165_ = lean_uint32_land(v___y_162_, v___y_163_);
v___x_166_ = lean_uint32_lor(v___y_164_, v___x_165_);
return v___x_166_;
}
v___jp_167_:
{
uint8_t v___x_172_; 
v___x_172_ = lean_uint64_dec_eq(v___y_171_, v___y_170_);
if (v___x_172_ == 0)
{
uint64_t v___x_173_; uint8_t v___x_174_; 
v___x_173_ = 8388608ULL;
v___x_174_ = lean_uint64_dec_eq(v___y_171_, v___x_173_);
if (v___x_174_ == 0)
{
uint32_t v___x_175_; 
v___x_175_ = lean_uint64_to_uint32(v___y_171_);
if (v___y_168_ == 0)
{
uint32_t v___x_176_; 
v___x_176_ = 0;
v___y_162_ = v___x_175_;
v___y_163_ = v___y_169_;
v___y_164_ = v___x_176_;
goto v___jp_161_;
}
else
{
uint32_t v___x_177_; 
v___x_177_ = 2147483648;
v___y_162_ = v___x_175_;
v___y_163_ = v___y_169_;
v___y_164_ = v___x_177_;
goto v___jp_161_;
}
}
else
{
if (v___y_168_ == 0)
{
uint32_t v___x_178_; 
v___x_178_ = 0;
v___y_133_ = v___x_178_;
goto v___jp_132_;
}
else
{
uint32_t v___x_179_; 
v___x_179_ = 2147483648;
v___y_133_ = v___x_179_;
goto v___jp_132_;
}
}
}
else
{
if (v___y_168_ == 0)
{
uint32_t v___x_180_; 
v___x_180_ = 0;
return v___x_180_;
}
else
{
uint32_t v___x_181_; 
v___x_181_ = 2147483648;
return v___x_181_;
}
}
}
v___jp_182_:
{
if (v___y_183_ == 0)
{
uint32_t v___x_184_; 
v___x_184_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_184_;
}
else
{
uint32_t v___x_185_; uint32_t v___x_186_; 
v___x_185_ = 4194304;
v___x_186_ = lean_uint32_lor(v___y_131_, v___x_185_);
return v___x_186_;
}
}
v___jp_187_:
{
uint32_t v___x_188_; uint32_t v___x_189_; uint32_t v___x_190_; uint32_t v___x_191_; uint8_t v___x_192_; 
v___x_188_ = 23;
v___x_189_ = lean_uint32_shift_right(v___y_131_, v___x_188_);
v___x_190_ = 255;
v___x_191_ = lean_uint32_land(v___x_189_, v___x_190_);
v___x_192_ = lean_uint32_dec_eq(v___x_191_, v___x_190_);
if (v___x_192_ == 0)
{
v___y_183_ = v___x_192_;
goto v___jp_182_;
}
else
{
uint32_t v___x_193_; uint32_t v___x_194_; uint32_t v___x_195_; uint8_t v___x_196_; 
v___x_193_ = 8388607;
v___x_194_ = lean_uint32_land(v___y_131_, v___x_193_);
v___x_195_ = 0;
v___x_196_ = lean_uint32_dec_eq(v___x_194_, v___x_195_);
if (v___x_196_ == 0)
{
v___y_183_ = v___x_192_;
goto v___jp_182_;
}
else
{
uint32_t v___x_197_; 
v___x_197_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_197_;
}
}
}
v___jp_198_:
{
if (v___y_199_ == 0)
{
goto v___jp_187_;
}
else
{
uint32_t v___x_200_; uint32_t v___x_201_; 
v___x_200_ = 4194304;
v___x_201_ = lean_uint32_lor(v___y_130_, v___x_200_);
return v___x_201_;
}
}
v___jp_202_:
{
uint32_t v___x_203_; uint32_t v___x_204_; uint32_t v___x_205_; uint32_t v___x_206_; uint8_t v___x_207_; 
v___x_203_ = 23;
v___x_204_ = lean_uint32_shift_right(v___y_130_, v___x_203_);
v___x_205_ = 255;
v___x_206_ = lean_uint32_land(v___x_204_, v___x_205_);
v___x_207_ = lean_uint32_dec_eq(v___x_206_, v___x_205_);
if (v___x_207_ == 0)
{
v___y_199_ = v___x_207_;
goto v___jp_198_;
}
else
{
uint32_t v___x_208_; uint32_t v___x_209_; uint32_t v___x_210_; uint8_t v___x_211_; 
v___x_208_ = 8388607;
v___x_209_ = lean_uint32_land(v___y_130_, v___x_208_);
v___x_210_ = 0;
v___x_211_ = lean_uint32_dec_eq(v___x_209_, v___x_210_);
if (v___x_211_ == 0)
{
v___y_199_ = v___x_207_;
goto v___jp_198_;
}
else
{
goto v___jp_187_;
}
}
}
v___jp_212_:
{
if (v___y_213_ == 0)
{
goto v___jp_202_;
}
else
{
uint32_t v___x_214_; uint32_t v___x_215_; uint32_t v___x_216_; uint8_t v___x_217_; 
v___x_214_ = 4194304;
v___x_215_ = lean_uint32_land(v___y_131_, v___x_214_);
v___x_216_ = 0;
v___x_217_ = lean_uint32_dec_eq(v___x_215_, v___x_216_);
if (v___x_217_ == 0)
{
goto v___jp_202_;
}
else
{
uint32_t v___x_218_; 
v___x_218_ = lean_uint32_lor(v___y_131_, v___x_214_);
return v___x_218_;
}
}
}
v___jp_219_:
{
uint32_t v___x_220_; uint32_t v___x_221_; uint32_t v___x_222_; uint32_t v___x_223_; uint8_t v___x_224_; 
v___x_220_ = 23;
v___x_221_ = lean_uint32_shift_right(v___y_131_, v___x_220_);
v___x_222_ = 255;
v___x_223_ = lean_uint32_land(v___x_221_, v___x_222_);
v___x_224_ = lean_uint32_dec_eq(v___x_223_, v___x_222_);
if (v___x_224_ == 0)
{
v___y_213_ = v___x_224_;
goto v___jp_212_;
}
else
{
uint32_t v___x_225_; uint32_t v___x_226_; uint32_t v___x_227_; uint8_t v___x_228_; 
v___x_225_ = 8388607;
v___x_226_ = lean_uint32_land(v___y_131_, v___x_225_);
v___x_227_ = 0;
v___x_228_ = lean_uint32_dec_eq(v___x_226_, v___x_227_);
if (v___x_228_ == 0)
{
v___y_213_ = v___x_224_;
goto v___jp_212_;
}
else
{
goto v___jp_202_;
}
}
}
v___jp_229_:
{
if (v___y_230_ == 0)
{
goto v___jp_219_;
}
else
{
uint32_t v___x_231_; uint32_t v___x_232_; uint32_t v___x_233_; uint8_t v___x_234_; 
v___x_231_ = 4194304;
v___x_232_ = lean_uint32_land(v___y_130_, v___x_231_);
v___x_233_ = 0;
v___x_234_ = lean_uint32_dec_eq(v___x_232_, v___x_233_);
if (v___x_234_ == 0)
{
goto v___jp_219_;
}
else
{
uint32_t v___x_235_; 
v___x_235_ = lean_uint32_lor(v___y_130_, v___x_231_);
return v___x_235_;
}
}
}
v___jp_236_:
{
float v_result_239_; uint8_t v___x_240_; 
v_result_239_ = lean_float32_mul(v___y_237_, v___y_238_);
v___x_240_ = lean_float32_beq(v_result_239_, v_result_239_);
if (v___x_240_ == 0)
{
uint32_t v___x_241_; uint32_t v___x_242_; uint32_t v___x_243_; uint32_t v___x_244_; uint8_t v___x_245_; 
v___x_241_ = 23;
v___x_242_ = lean_uint32_shift_right(v___y_130_, v___x_241_);
v___x_243_ = 255;
v___x_244_ = lean_uint32_land(v___x_242_, v___x_243_);
v___x_245_ = lean_uint32_dec_eq(v___x_244_, v___x_243_);
if (v___x_245_ == 0)
{
v___y_230_ = v___x_245_;
goto v___jp_229_;
}
else
{
uint32_t v___x_246_; uint32_t v___x_247_; uint32_t v___x_248_; uint8_t v___x_249_; 
v___x_246_ = 8388607;
v___x_247_ = lean_uint32_land(v___y_130_, v___x_246_);
v___x_248_ = 0;
v___x_249_ = lean_uint32_dec_eq(v___x_247_, v___x_248_);
if (v___x_249_ == 0)
{
v___y_230_ = v___x_245_;
goto v___jp_229_;
}
else
{
goto v___jp_219_;
}
}
}
else
{
uint32_t v___x_250_; 
v___x_250_ = lean_float32_to_bits(v_result_239_);
return v___x_250_;
}
}
v___jp_251_:
{
if (v___y_253_ == 0)
{
float v___x_254_; 
v___x_254_ = lean_float32_of_bits(v___y_131_);
v___y_237_ = v___y_252_;
v___y_238_ = v___x_254_;
goto v___jp_236_;
}
else
{
uint32_t v___x_255_; uint32_t v___x_256_; uint32_t v___x_257_; uint32_t v___x_258_; float v___x_259_; lean_object* v___x_260_; uint32_t v___x_261_; uint32_t v___x_262_; lean_object* v___x_263_; lean_object* v___x_264_; float v___x_265_; float v___x_266_; 
v___x_255_ = 8388607;
v___x_256_ = lean_uint32_land(v___y_131_, v___x_255_);
v___x_257_ = 8388608;
v___x_258_ = lean_uint32_lor(v___x_256_, v___x_257_);
v___x_259_ = lean_uint32_to_float32(v___x_258_);
v___x_260_ = lp_competition_R2W01b_scaleTable;
v___x_261_ = 23;
v___x_262_ = lean_uint32_shift_right(v___y_131_, v___x_261_);
v___x_263_ = lean_uint32_to_nat(v___x_262_);
v___x_264_ = lean_array_fget_borrowed(v___x_260_, v___x_263_);
lean_dec(v___x_263_);
v___x_265_ = lean_unbox_float32(v___x_264_);
v___x_266_ = lean_float32_mul(v___x_259_, v___x_265_);
v___y_237_ = v___y_252_;
v___y_238_ = v___x_266_;
goto v___jp_236_;
}
}
v___jp_267_:
{
uint32_t v___x_269_; uint32_t v_a_270_; uint32_t v___x_271_; uint32_t v___x_272_; uint32_t v___x_273_; uint8_t v___x_274_; 
v___x_269_ = 2147483647;
v_a_270_ = lean_uint32_land(v___y_131_, v___x_269_);
v___x_271_ = 201326591;
v___x_272_ = 1;
v___x_273_ = lean_uint32_sub(v_a_270_, v___x_272_);
v___x_274_ = lean_uint32_dec_le(v___x_271_, v___x_273_);
if (v___x_274_ == 0)
{
v___y_252_ = v___y_268_;
v___y_253_ = v___x_274_;
goto v___jp_251_;
}
else
{
uint32_t v___x_275_; uint8_t v___x_276_; 
v___x_275_ = 2139095040;
v___x_276_ = lean_uint32_dec_lt(v_a_270_, v___x_275_);
v___y_252_ = v___y_268_;
v___y_253_ = v___x_276_;
goto v___jp_251_;
}
}
v___jp_279_:
{
if (v___y_280_ == 0)
{
float v___x_281_; 
v___x_281_ = lean_float32_of_bits(v___y_130_);
v___y_268_ = v___x_281_;
goto v___jp_267_;
}
else
{
uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint32_t v___x_285_; float v___x_286_; lean_object* v___x_287_; lean_object* v___x_288_; lean_object* v___x_289_; float v___x_290_; float v___x_291_; 
v___x_282_ = 8388607;
v___x_283_ = lean_uint32_land(v___y_130_, v___x_282_);
v___x_284_ = 8388608;
v___x_285_ = lean_uint32_lor(v___x_283_, v___x_284_);
v___x_286_ = lean_uint32_to_float32(v___x_285_);
v___x_287_ = lp_competition_R2W01b_scaleTable;
v___x_288_ = lean_uint32_to_nat(v___x_278_);
v___x_289_ = lean_array_fget_borrowed(v___x_287_, v___x_288_);
lean_dec(v___x_288_);
v___x_290_ = lean_unbox_float32(v___x_289_);
v___x_291_ = lean_float32_mul(v___x_286_, v___x_290_);
v___y_268_ = v___x_291_;
goto v___jp_267_;
}
}
v___jp_293_:
{
uint32_t v___x_298_; uint32_t v___x_299_; uint32_t v___x_300_; uint32_t v___x_301_; uint32_t v___x_302_; 
v___x_298_ = lean_uint32_land(v___y_296_, v___x_292_);
v___x_299_ = lean_uint32_shift_left(v___x_298_, v___x_277_);
v___x_300_ = lean_uint32_lor(v___y_297_, v___x_299_);
v___x_301_ = lean_uint32_land(v___y_294_, v___y_295_);
v___x_302_ = lean_uint32_lor(v___x_300_, v___x_301_);
return v___x_302_;
}
v___jp_303_:
{
if (v___y_304_ == 0)
{
uint32_t v___x_308_; 
v___x_308_ = 0;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_305_;
v___y_296_ = v___y_306_;
v___y_297_ = v___x_308_;
goto v___jp_293_;
}
else
{
uint32_t v___x_309_; 
v___x_309_ = 2147483648;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_305_;
v___y_296_ = v___y_306_;
v___y_297_ = v___x_309_;
goto v___jp_293_;
}
}
v___jp_310_:
{
uint64_t v___x_316_; uint64_t v_encodedExponent_317_; uint32_t v___x_318_; uint64_t v___x_319_; uint8_t v___x_320_; 
v___x_316_ = 171ULL;
v_encodedExponent_317_ = lean_uint64_sub(v___y_314_, v___x_316_);
v___x_318_ = lean_uint64_to_uint32(v_encodedExponent_317_);
v___x_319_ = 8388608ULL;
v___x_320_ = lean_uint64_dec_lt(v___y_315_, v___x_319_);
if (v___x_320_ == 0)
{
uint64_t v___x_321_; uint32_t v___x_322_; 
v___x_321_ = lean_uint64_sub(v___y_315_, v___x_319_);
v___x_322_ = lean_uint64_to_uint32(v___x_321_);
v___y_304_ = v___y_311_;
v___y_305_ = v___y_313_;
v___y_306_ = v___x_318_;
v___y_307_ = v___x_322_;
goto v___jp_303_;
}
else
{
uint32_t v___x_323_; 
v___x_323_ = lean_uint64_to_uint32(v___y_312_);
v___y_304_ = v___y_311_;
v___y_305_ = v___y_313_;
v___y_306_ = v___x_318_;
v___y_307_ = v___x_323_;
goto v___jp_303_;
}
}
v___jp_324_:
{
uint64_t v___x_331_; uint8_t v___x_332_; 
v___x_331_ = 425ULL;
v___x_332_ = lean_uint64_dec_lt(v___x_331_, v___y_330_);
if (v___x_332_ == 0)
{
if (v___y_329_ == 0)
{
v___y_311_ = v___y_325_;
v___y_312_ = v___y_327_;
v___y_313_ = v___y_326_;
v___y_314_ = v___y_330_;
v___y_315_ = v___y_328_;
goto v___jp_310_;
}
else
{
uint64_t v___x_333_; 
v___x_333_ = 8388608ULL;
v___y_311_ = v___y_325_;
v___y_312_ = v___y_327_;
v___y_313_ = v___y_326_;
v___y_314_ = v___y_330_;
v___y_315_ = v___x_333_;
goto v___jp_310_;
}
}
else
{
if (v___y_325_ == 0)
{
uint32_t v___x_334_; 
v___x_334_ = 2139095040;
return v___x_334_;
}
else
{
uint32_t v___x_335_; 
v___x_335_ = 4286578688;
return v___x_335_;
}
}
}
v___jp_336_:
{
uint64_t v___x_342_; uint8_t v_carry_343_; 
v___x_342_ = 16777216ULL;
v_carry_343_ = lean_uint64_dec_eq(v___y_341_, v___x_342_);
if (v_carry_343_ == 0)
{
v___y_325_ = v___y_337_;
v___y_326_ = v___y_340_;
v___y_327_ = v___y_339_;
v___y_328_ = v___y_341_;
v___y_329_ = v_carry_343_;
v___y_330_ = v___y_338_;
goto v___jp_324_;
}
else
{
uint64_t v___x_344_; uint64_t v___x_345_; 
v___x_344_ = 1ULL;
v___x_345_ = lean_uint64_add(v___y_338_, v___x_344_);
v___y_325_ = v___y_337_;
v___y_326_ = v___y_340_;
v___y_327_ = v___y_339_;
v___y_328_ = v___y_341_;
v___y_329_ = v_carry_343_;
v___y_330_ = v___x_345_;
goto v___jp_324_;
}
}
v___jp_346_:
{
uint64_t v_position_353_; uint64_t v___x_354_; uint8_t v___x_355_; 
v_position_353_ = lean_uint64_add(v___y_352_, v___y_351_);
v___x_354_ = 172ULL;
v___x_355_ = lean_uint64_dec_lt(v_position_353_, v___x_354_);
if (v___x_355_ == 0)
{
uint64_t v___x_356_; uint8_t v___x_357_; 
v___x_356_ = 23ULL;
v___x_357_ = lean_uint64_dec_lt(v___y_352_, v___x_356_);
if (v___x_357_ == 0)
{
uint64_t v___x_358_; uint8_t v___x_359_; 
v___x_358_ = lean_uint64_sub(v___y_352_, v___x_356_);
v___x_359_ = lean_uint64_dec_eq(v___x_358_, v___y_350_);
if (v___x_359_ == 0)
{
uint64_t v___x_360_; uint8_t v___x_361_; 
v___x_360_ = 64ULL;
v___x_361_ = lean_uint64_dec_lt(v___x_358_, v___x_360_);
if (v___x_361_ == 0)
{
uint8_t v___x_362_; 
v___x_362_ = lean_uint64_dec_eq(v___x_358_, v___x_360_);
if (v___x_362_ == 0)
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_350_;
goto v___jp_336_;
}
else
{
uint64_t v___x_363_; uint8_t v___x_364_; 
v___x_363_ = 9223372036854775808ULL;
v___x_364_ = lean_uint64_dec_lt(v___x_363_, v___y_348_);
if (v___x_364_ == 0)
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_350_;
goto v___jp_336_;
}
else
{
uint64_t v___x_365_; 
v___x_365_ = 1ULL;
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_365_;
goto v___jp_336_;
}
}
}
else
{
uint64_t v_quotient_366_; uint64_t v___x_367_; uint64_t v___x_368_; uint64_t v___x_369_; uint64_t v_remainder_370_; uint64_t v___x_371_; uint64_t v_half_372_; uint8_t v___x_373_; 
v_quotient_366_ = lean_uint64_shift_right(v___y_348_, v___x_358_);
v___x_367_ = 1ULL;
v___x_368_ = lean_uint64_shift_left(v___x_367_, v___x_358_);
v___x_369_ = lean_uint64_sub(v___x_368_, v___x_367_);
v_remainder_370_ = lean_uint64_land(v___y_348_, v___x_369_);
v___x_371_ = lean_uint64_sub(v___x_358_, v___x_367_);
v_half_372_ = lean_uint64_shift_left(v___x_367_, v___x_371_);
v___x_373_ = lean_uint64_dec_lt(v_remainder_370_, v_half_372_);
if (v___x_373_ == 0)
{
uint8_t v___x_374_; 
v___x_374_ = lean_uint64_dec_lt(v_half_372_, v_remainder_370_);
if (v___x_374_ == 0)
{
uint64_t v___x_375_; uint8_t v___x_376_; 
v___x_375_ = lean_uint64_land(v_quotient_366_, v___x_367_);
v___x_376_ = lean_uint64_dec_eq(v___x_375_, v___y_350_);
if (v___x_376_ == 0)
{
uint64_t v___x_377_; 
v___x_377_ = lean_uint64_add(v_quotient_366_, v___x_367_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_377_;
goto v___jp_336_;
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v_quotient_366_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_378_; 
v___x_378_ = lean_uint64_add(v_quotient_366_, v___x_367_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_378_;
goto v___jp_336_;
}
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v_quotient_366_;
goto v___jp_336_;
}
}
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_348_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_379_; uint64_t v___x_380_; 
v___x_379_ = lean_uint64_sub(v___x_356_, v___y_352_);
v___x_380_ = lean_uint64_shift_left(v___y_348_, v___x_379_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_380_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_381_; uint8_t v___x_382_; 
v___x_381_ = 149ULL;
v___x_382_ = lean_uint64_dec_lt(v___y_351_, v___x_381_);
if (v___x_382_ == 0)
{
uint64_t v___x_383_; uint64_t v___x_384_; 
v___x_383_ = lean_uint64_sub(v___y_351_, v___x_381_);
v___x_384_ = lean_uint64_shift_left(v___y_348_, v___x_383_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_384_;
goto v___jp_146_;
}
else
{
uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_385_ = lean_uint64_sub(v___x_381_, v___y_351_);
v___x_386_ = lean_uint64_dec_eq(v___x_385_, v___y_350_);
if (v___x_386_ == 0)
{
uint64_t v___x_387_; uint8_t v___x_388_; 
v___x_387_ = 64ULL;
v___x_388_ = lean_uint64_dec_lt(v___x_385_, v___x_387_);
if (v___x_388_ == 0)
{
uint8_t v___x_389_; 
v___x_389_ = lean_uint64_dec_eq(v___x_385_, v___x_387_);
if (v___x_389_ == 0)
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_350_;
goto v___jp_146_;
}
else
{
uint64_t v___x_390_; uint8_t v___x_391_; 
v___x_390_ = 9223372036854775808ULL;
v___x_391_ = lean_uint64_dec_lt(v___x_390_, v___y_348_);
if (v___x_391_ == 0)
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_350_;
goto v___jp_146_;
}
else
{
uint64_t v___x_392_; 
v___x_392_ = 1ULL;
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_392_;
goto v___jp_146_;
}
}
}
else
{
uint64_t v_quotient_393_; uint64_t v___x_394_; uint64_t v___x_395_; uint64_t v___x_396_; uint64_t v_remainder_397_; uint64_t v___x_398_; uint64_t v_half_399_; uint8_t v___x_400_; 
v_quotient_393_ = lean_uint64_shift_right(v___y_348_, v___x_385_);
v___x_394_ = 1ULL;
v___x_395_ = lean_uint64_shift_left(v___x_394_, v___x_385_);
v___x_396_ = lean_uint64_sub(v___x_395_, v___x_394_);
v_remainder_397_ = lean_uint64_land(v___y_348_, v___x_396_);
v___x_398_ = lean_uint64_sub(v___x_385_, v___x_394_);
v_half_399_ = lean_uint64_shift_left(v___x_394_, v___x_398_);
v___x_400_ = lean_uint64_dec_lt(v_remainder_397_, v_half_399_);
if (v___x_400_ == 0)
{
uint8_t v___x_401_; 
v___x_401_ = lean_uint64_dec_lt(v_half_399_, v_remainder_397_);
if (v___x_401_ == 0)
{
uint64_t v___x_402_; uint8_t v___x_403_; 
v___x_402_ = lean_uint64_land(v_quotient_393_, v___x_394_);
v___x_403_ = lean_uint64_dec_eq(v___x_402_, v___y_350_);
if (v___x_403_ == 0)
{
uint64_t v___x_404_; 
v___x_404_ = lean_uint64_add(v_quotient_393_, v___x_394_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_404_;
goto v___jp_146_;
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v_quotient_393_;
goto v___jp_146_;
}
}
else
{
uint64_t v___x_405_; 
v___x_405_ = lean_uint64_add(v_quotient_393_, v___x_394_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_405_;
goto v___jp_146_;
}
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v_quotient_393_;
goto v___jp_146_;
}
}
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_348_;
goto v___jp_146_;
}
}
}
}
v___jp_406_:
{
uint64_t v___x_414_; uint64_t v___x_415_; uint8_t v___x_416_; 
v___x_414_ = 1ULL;
v___x_415_ = lean_uint64_shift_right(v___y_407_, v___x_414_);
v___x_416_ = lean_uint64_dec_eq(v___x_415_, v___y_411_);
if (v___x_416_ == 0)
{
uint64_t v___x_417_; 
v___x_417_ = lean_uint64_add(v___y_413_, v___x_414_);
v___y_347_ = v___y_408_;
v___y_348_ = v___y_410_;
v___y_349_ = v___y_409_;
v___y_350_ = v___y_411_;
v___y_351_ = v___y_412_;
v___y_352_ = v___x_417_;
goto v___jp_346_;
}
else
{
v___y_347_ = v___y_408_;
v___y_348_ = v___y_410_;
v___y_349_ = v___y_409_;
v___y_350_ = v___y_411_;
v___y_351_ = v___y_412_;
v___y_352_ = v___y_413_;
goto v___jp_346_;
}
}
v___jp_418_:
{
uint64_t v___x_428_; uint8_t v___x_429_; 
v___x_428_ = lean_uint64_shift_right(v___y_425_, v___y_419_);
v___x_429_ = lean_uint64_dec_eq(v___x_428_, v___y_422_);
if (v___x_429_ == 0)
{
uint64_t v___x_430_; 
v___x_430_ = lean_uint64_add(v___y_421_, v___y_419_);
v___y_407_ = v___y_427_;
v___y_408_ = v___y_420_;
v___y_409_ = v___y_424_;
v___y_410_ = v___y_423_;
v___y_411_ = v___y_422_;
v___y_412_ = v___y_426_;
v___y_413_ = v___x_430_;
goto v___jp_406_;
}
else
{
v___y_407_ = v___y_427_;
v___y_408_ = v___y_420_;
v___y_409_ = v___y_424_;
v___y_410_ = v___y_423_;
v___y_411_ = v___y_422_;
v___y_412_ = v___y_426_;
v___y_413_ = v___y_421_;
goto v___jp_406_;
}
}
v___jp_431_:
{
uint64_t v___x_439_; uint64_t v___x_440_; uint8_t v___x_441_; 
v___x_439_ = 2ULL;
v___x_440_ = lean_uint64_shift_right(v___y_436_, v___x_439_);
v___x_441_ = lean_uint64_dec_eq(v___x_440_, v___y_435_);
if (v___x_441_ == 0)
{
v___y_419_ = v___x_439_;
v___y_420_ = v___y_432_;
v___y_421_ = v___y_438_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_434_;
v___y_424_ = v___y_433_;
v___y_425_ = v___y_436_;
v___y_426_ = v___y_437_;
v___y_427_ = v___x_440_;
goto v___jp_418_;
}
else
{
v___y_419_ = v___x_439_;
v___y_420_ = v___y_432_;
v___y_421_ = v___y_438_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_434_;
v___y_424_ = v___y_433_;
v___y_425_ = v___y_436_;
v___y_426_ = v___y_437_;
v___y_427_ = v___y_436_;
goto v___jp_418_;
}
}
v___jp_442_:
{
uint64_t v___x_452_; uint8_t v___x_453_; 
v___x_452_ = lean_uint64_shift_right(v___y_449_, v___y_444_);
v___x_453_ = lean_uint64_dec_eq(v___x_452_, v___y_446_);
if (v___x_453_ == 0)
{
uint64_t v___x_454_; 
v___x_454_ = lean_uint64_add(v___y_445_, v___y_444_);
v___y_432_ = v___y_443_;
v___y_433_ = v___y_448_;
v___y_434_ = v___y_447_;
v___y_435_ = v___y_446_;
v___y_436_ = v___y_451_;
v___y_437_ = v___y_450_;
v___y_438_ = v___x_454_;
goto v___jp_431_;
}
else
{
v___y_432_ = v___y_443_;
v___y_433_ = v___y_448_;
v___y_434_ = v___y_447_;
v___y_435_ = v___y_446_;
v___y_436_ = v___y_451_;
v___y_437_ = v___y_450_;
v___y_438_ = v___y_445_;
goto v___jp_431_;
}
}
v___jp_455_:
{
uint64_t v___x_463_; uint64_t v___x_464_; uint8_t v___x_465_; 
v___x_463_ = 4ULL;
v___x_464_ = lean_uint64_shift_right(v___y_460_, v___x_463_);
v___x_465_ = lean_uint64_dec_eq(v___x_464_, v___y_459_);
if (v___x_465_ == 0)
{
v___y_443_ = v___y_456_;
v___y_444_ = v___x_463_;
v___y_445_ = v___y_462_;
v___y_446_ = v___y_459_;
v___y_447_ = v___y_458_;
v___y_448_ = v___y_457_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___x_464_;
goto v___jp_442_;
}
else
{
v___y_443_ = v___y_456_;
v___y_444_ = v___x_463_;
v___y_445_ = v___y_462_;
v___y_446_ = v___y_459_;
v___y_447_ = v___y_458_;
v___y_448_ = v___y_457_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___y_460_;
goto v___jp_442_;
}
}
v___jp_466_:
{
uint64_t v___x_476_; uint8_t v___x_477_; 
v___x_476_ = lean_uint64_shift_right(v___y_467_, v___y_474_);
v___x_477_ = lean_uint64_dec_eq(v___x_476_, v___y_469_);
if (v___x_477_ == 0)
{
uint64_t v___x_478_; 
v___x_478_ = lean_uint64_add(v___y_472_, v___y_474_);
v___y_456_ = v___y_468_;
v___y_457_ = v___y_471_;
v___y_458_ = v___y_470_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_475_;
v___y_461_ = v___y_473_;
v___y_462_ = v___x_478_;
goto v___jp_455_;
}
else
{
v___y_456_ = v___y_468_;
v___y_457_ = v___y_471_;
v___y_458_ = v___y_470_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_475_;
v___y_461_ = v___y_473_;
v___y_462_ = v___y_472_;
goto v___jp_455_;
}
}
v___jp_479_:
{
uint64_t v___x_487_; uint64_t v___x_488_; uint8_t v___x_489_; 
v___x_487_ = 8ULL;
v___x_488_ = lean_uint64_shift_right(v___y_480_, v___x_487_);
v___x_489_ = lean_uint64_dec_eq(v___x_488_, v___y_484_);
if (v___x_489_ == 0)
{
v___y_467_ = v___y_480_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_484_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_486_;
v___y_473_ = v___y_485_;
v___y_474_ = v___x_487_;
v___y_475_ = v___x_488_;
goto v___jp_466_;
}
else
{
v___y_467_ = v___y_480_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_484_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_486_;
v___y_473_ = v___y_485_;
v___y_474_ = v___x_487_;
v___y_475_ = v___y_480_;
goto v___jp_466_;
}
}
v___jp_490_:
{
uint64_t v___x_500_; uint8_t v___x_501_; 
v___x_500_ = lean_uint64_shift_right(v___y_492_, v___y_497_);
v___x_501_ = lean_uint64_dec_eq(v___x_500_, v___y_493_);
if (v___x_501_ == 0)
{
uint64_t v___x_502_; 
v___x_502_ = lean_uint64_add(v___y_498_, v___y_497_);
v___y_480_ = v___y_499_;
v___y_481_ = v___y_491_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_494_;
v___y_484_ = v___y_493_;
v___y_485_ = v___y_496_;
v___y_486_ = v___x_502_;
goto v___jp_479_;
}
else
{
v___y_480_ = v___y_499_;
v___y_481_ = v___y_491_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_494_;
v___y_484_ = v___y_493_;
v___y_485_ = v___y_496_;
v___y_486_ = v___y_498_;
goto v___jp_479_;
}
}
v___jp_503_:
{
uint64_t v___x_511_; uint64_t v___x_512_; uint8_t v___x_513_; 
v___x_511_ = 16ULL;
v___x_512_ = lean_uint64_shift_right(v___y_505_, v___x_511_);
v___x_513_ = lean_uint64_dec_eq(v___x_512_, v___y_508_);
if (v___x_513_ == 0)
{
v___y_491_ = v___y_504_;
v___y_492_ = v___y_505_;
v___y_493_ = v___y_508_;
v___y_494_ = v___y_507_;
v___y_495_ = v___y_506_;
v___y_496_ = v___y_509_;
v___y_497_ = v___x_511_;
v___y_498_ = v___y_510_;
v___y_499_ = v___x_512_;
goto v___jp_490_;
}
else
{
v___y_491_ = v___y_504_;
v___y_492_ = v___y_505_;
v___y_493_ = v___y_508_;
v___y_494_ = v___y_507_;
v___y_495_ = v___y_506_;
v___y_496_ = v___y_509_;
v___y_497_ = v___x_511_;
v___y_498_ = v___y_510_;
v___y_499_ = v___y_505_;
goto v___jp_490_;
}
}
v___jp_514_:
{
uint64_t v___x_522_; uint8_t v___x_523_; 
v___x_522_ = lean_uint64_shift_right(v___y_518_, v___y_516_);
v___x_523_ = lean_uint64_dec_eq(v___x_522_, v___y_517_);
if (v___x_523_ == 0)
{
v___y_504_ = v___y_515_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_519_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_517_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_516_;
goto v___jp_503_;
}
else
{
v___y_504_ = v___y_515_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_519_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_517_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_517_;
goto v___jp_503_;
}
}
v___jp_524_:
{
uint64_t v___x_529_; uint8_t v___x_530_; 
v___x_529_ = 0ULL;
v___x_530_ = lean_uint64_dec_eq(v___y_526_, v___x_529_);
if (v___x_530_ == 0)
{
uint64_t v___x_531_; uint64_t v___x_532_; uint8_t v___x_533_; 
v___x_531_ = 32ULL;
v___x_532_ = lean_uint64_shift_right(v___y_526_, v___x_531_);
v___x_533_ = lean_uint64_dec_eq(v___x_532_, v___x_529_);
if (v___x_533_ == 0)
{
v___y_515_ = v___y_525_;
v___y_516_ = v___x_531_;
v___y_517_ = v___x_529_;
v___y_518_ = v___y_526_;
v___y_519_ = v___y_527_;
v___y_520_ = v___y_528_;
v___y_521_ = v___x_532_;
goto v___jp_514_;
}
else
{
v___y_515_ = v___y_525_;
v___y_516_ = v___x_531_;
v___y_517_ = v___x_529_;
v___y_518_ = v___y_526_;
v___y_519_ = v___y_527_;
v___y_520_ = v___y_528_;
v___y_521_ = v___y_526_;
goto v___jp_514_;
}
}
else
{
if (v___y_525_ == 0)
{
uint32_t v___x_534_; 
v___x_534_ = 0;
return v___x_534_;
}
else
{
uint32_t v___x_535_; 
v___x_535_ = 2147483648;
return v___x_535_;
}
}
}
v___jp_536_:
{
uint64_t v___x_543_; uint64_t v___x_544_; uint64_t v___x_545_; uint8_t v___x_546_; 
v___x_543_ = lean_uint64_mul(v___y_541_, v___y_540_);
v___x_544_ = lean_uint64_add(v___y_538_, v___y_542_);
v___x_545_ = 281474976710656ULL;
v___x_546_ = lean_uint64_dec_lt(v___x_543_, v___x_545_);
if (v___x_546_ == 0)
{
v___y_525_ = v___y_537_;
v___y_526_ = v___x_543_;
v___y_527_ = v___y_539_;
v___y_528_ = v___x_544_;
goto v___jp_524_;
}
else
{
uint64_t v___x_547_; uint8_t v___x_548_; 
v___x_547_ = 123ULL;
v___x_548_ = lean_uint64_dec_le(v___x_544_, v___x_547_);
if (v___x_548_ == 0)
{
v___y_525_ = v___y_537_;
v___y_526_ = v___x_543_;
v___y_527_ = v___y_539_;
v___y_528_ = v___x_544_;
goto v___jp_524_;
}
else
{
uint64_t v___x_549_; uint8_t v___x_550_; 
v___x_549_ = 0ULL;
v___x_550_ = lean_uint64_dec_eq(v___x_543_, v___x_549_);
if (v___x_550_ == 0)
{
uint64_t v___x_551_; uint64_t v___x_552_; uint8_t v___x_553_; 
v___x_551_ = 149ULL;
v___x_552_ = lean_uint64_sub(v___x_551_, v___x_544_);
v___x_553_ = lean_uint64_dec_eq(v___x_552_, v___x_549_);
if (v___x_553_ == 0)
{
uint64_t v___x_554_; uint8_t v___x_555_; 
v___x_554_ = 64ULL;
v___x_555_ = lean_uint64_dec_lt(v___x_552_, v___x_554_);
if (v___x_555_ == 0)
{
uint8_t v___x_556_; 
v___x_556_ = lean_uint64_dec_eq(v___x_552_, v___x_554_);
if (v___x_556_ == 0)
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_549_;
goto v___jp_167_;
}
else
{
uint64_t v___x_557_; uint8_t v___x_558_; 
v___x_557_ = 9223372036854775808ULL;
v___x_558_ = lean_uint64_dec_lt(v___x_557_, v___x_543_);
if (v___x_558_ == 0)
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_549_;
goto v___jp_167_;
}
else
{
uint64_t v___x_559_; 
v___x_559_ = 1ULL;
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_559_;
goto v___jp_167_;
}
}
}
else
{
uint64_t v_quotient_560_; uint64_t v___x_561_; uint64_t v___x_562_; uint64_t v___x_563_; uint64_t v_remainder_564_; uint64_t v___x_565_; uint64_t v_half_566_; uint8_t v___x_567_; 
v_quotient_560_ = lean_uint64_shift_right(v___x_543_, v___x_552_);
v___x_561_ = 1ULL;
v___x_562_ = lean_uint64_shift_left(v___x_561_, v___x_552_);
v___x_563_ = lean_uint64_sub(v___x_562_, v___x_561_);
v_remainder_564_ = lean_uint64_land(v___x_543_, v___x_563_);
v___x_565_ = lean_uint64_sub(v___x_552_, v___x_561_);
v_half_566_ = lean_uint64_shift_left(v___x_561_, v___x_565_);
v___x_567_ = lean_uint64_dec_lt(v_remainder_564_, v_half_566_);
if (v___x_567_ == 0)
{
uint8_t v___x_568_; 
v___x_568_ = lean_uint64_dec_lt(v_half_566_, v_remainder_564_);
if (v___x_568_ == 0)
{
uint64_t v___x_569_; uint8_t v___x_570_; 
v___x_569_ = lean_uint64_land(v_quotient_560_, v___x_561_);
v___x_570_ = lean_uint64_dec_eq(v___x_569_, v___x_549_);
if (v___x_570_ == 0)
{
uint64_t v___x_571_; 
v___x_571_ = lean_uint64_add(v_quotient_560_, v___x_561_);
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_571_;
goto v___jp_167_;
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v_quotient_560_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_572_; 
v___x_572_ = lean_uint64_add(v_quotient_560_, v___x_561_);
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_572_;
goto v___jp_167_;
}
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v_quotient_560_;
goto v___jp_167_;
}
}
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_543_;
goto v___jp_167_;
}
}
else
{
if (v___y_537_ == 0)
{
uint32_t v___x_573_; 
v___x_573_ = 0;
return v___x_573_;
}
else
{
uint32_t v___x_574_; 
v___x_574_ = 2147483648;
return v___x_574_;
}
}
}
}
}
v___jp_578_:
{
uint64_t v___x_584_; uint64_t v___x_585_; uint8_t v___x_586_; 
v___x_584_ = lean_uint32_to_uint64(v_ey_577_);
v___x_585_ = 0ULL;
v___x_586_ = lean_uint64_dec_eq(v___x_584_, v___x_585_);
if (v___x_586_ == 0)
{
uint64_t v___x_587_; uint64_t v___x_588_; 
v___x_587_ = 1ULL;
v___x_588_ = lean_uint64_sub(v___x_584_, v___x_587_);
v___y_537_ = v___y_579_;
v___y_538_ = v___y_583_;
v___y_539_ = v___y_580_;
v___y_540_ = v___y_581_;
v___y_541_ = v___y_582_;
v___y_542_ = v___x_588_;
goto v___jp_536_;
}
else
{
v___y_537_ = v___y_579_;
v___y_538_ = v___y_583_;
v___y_539_ = v___y_580_;
v___y_540_ = v___y_581_;
v___y_541_ = v___y_582_;
v___y_542_ = v___x_585_;
goto v___jp_536_;
}
}
v___jp_589_:
{
uint64_t v___x_594_; uint64_t v___x_595_; uint8_t v___x_596_; 
v___x_594_ = lean_uint32_to_uint64(v_ex_575_);
v___x_595_ = 0ULL;
v___x_596_ = lean_uint64_dec_eq(v___x_594_, v___x_595_);
if (v___x_596_ == 0)
{
uint64_t v___x_597_; uint64_t v___x_598_; 
v___x_597_ = 1ULL;
v___x_598_ = lean_uint64_sub(v___x_594_, v___x_597_);
v___y_579_ = v___y_590_;
v___y_580_ = v___y_591_;
v___y_581_ = v___y_593_;
v___y_582_ = v___y_592_;
v___y_583_ = v___x_598_;
goto v___jp_578_;
}
else
{
v___y_579_ = v___y_590_;
v___y_580_ = v___y_591_;
v___y_581_ = v___y_593_;
v___y_582_ = v___y_592_;
v___y_583_ = v___x_595_;
goto v___jp_578_;
}
}
v___jp_599_:
{
uint32_t v___x_604_; uint8_t v___x_605_; 
v___x_604_ = 0;
v___x_605_ = lean_uint32_dec_eq(v_ey_577_, v___x_604_);
if (v___x_605_ == 0)
{
uint64_t v___x_606_; uint64_t v___x_607_; uint64_t v___x_608_; 
v___x_606_ = lean_uint32_to_uint64(v___y_600_);
v___x_607_ = 8388608ULL;
v___x_608_ = lean_uint64_lor(v___x_606_, v___x_607_);
v___y_590_ = v___y_601_;
v___y_591_ = v___y_602_;
v___y_592_ = v___y_603_;
v___y_593_ = v___x_608_;
goto v___jp_589_;
}
else
{
uint64_t v___x_609_; 
v___x_609_ = lean_uint32_to_uint64(v___y_600_);
v___y_590_ = v___y_601_;
v___y_591_ = v___y_602_;
v___y_592_ = v___y_603_;
v___y_593_ = v___x_609_;
goto v___jp_589_;
}
}
v___jp_610_:
{
uint32_t v___x_612_; uint32_t v_xFraction_613_; uint32_t v_yFraction_614_; uint32_t v___x_615_; uint8_t v___x_616_; 
v___x_612_ = 8388607;
v_xFraction_613_ = lean_uint32_land(v___y_130_, v___x_612_);
v_yFraction_614_ = lean_uint32_land(v___y_131_, v___x_612_);
v___x_615_ = 0;
v___x_616_ = lean_uint32_dec_eq(v_ex_575_, v___x_615_);
if (v___x_616_ == 0)
{
uint64_t v___x_617_; uint64_t v___x_618_; uint64_t v___x_619_; 
v___x_617_ = lean_uint32_to_uint64(v_xFraction_613_);
v___x_618_ = 8388608ULL;
v___x_619_ = lean_uint64_lor(v___x_617_, v___x_618_);
v___y_600_ = v_yFraction_614_;
v___y_601_ = v___y_611_;
v___y_602_ = v___x_612_;
v___y_603_ = v___x_619_;
goto v___jp_599_;
}
else
{
uint64_t v___x_620_; 
v___x_620_ = lean_uint32_to_uint64(v_xFraction_613_);
v___y_600_ = v_yFraction_614_;
v___y_601_ = v___y_611_;
v___y_602_ = v___x_612_;
v___y_603_ = v___x_620_;
goto v___jp_599_;
}
}
v___jp_624_:
{
if (v___y_626_ == 0)
{
v___y_611_ = v___x_623_;
goto v___jp_610_;
}
else
{
v___y_611_ = v___y_625_;
goto v___jp_610_;
}
}
v___jp_627_:
{
if (v___y_628_ == 0)
{
if (v___y_630_ == 0)
{
v___y_625_ = v___y_629_;
v___y_626_ = v___x_623_;
goto v___jp_624_;
}
else
{
v___y_611_ = v___x_623_;
goto v___jp_610_;
}
}
else
{
v___y_625_ = v___y_629_;
v___y_626_ = v___y_630_;
goto v___jp_624_;
}
}
v___jp_631_:
{
uint32_t v___x_634_; uint32_t v___x_635_; uint32_t v___x_636_; uint8_t v___x_637_; 
v___x_634_ = 2147483648;
v___x_635_ = lean_uint32_land(v___y_131_, v___x_634_);
v___x_636_ = 0;
v___x_637_ = lean_uint32_dec_eq(v___x_635_, v___x_636_);
if (v___x_637_ == 0)
{
v___y_628_ = v___y_633_;
v___y_629_ = v___y_632_;
v___y_630_ = v___x_623_;
goto v___jp_627_;
}
else
{
v___y_628_ = v___y_633_;
v___y_629_ = v___y_632_;
v___y_630_ = v___y_632_;
goto v___jp_627_;
}
}
v___jp_638_:
{
if (v___y_639_ == 0)
{
uint32_t v___x_640_; uint32_t v___x_641_; uint32_t v___x_642_; uint8_t v___x_643_; 
v___x_640_ = 2147483648;
v___x_641_ = lean_uint32_land(v___y_130_, v___x_640_);
v___x_642_ = 0;
v___x_643_ = lean_uint32_dec_eq(v___x_641_, v___x_642_);
if (v___x_643_ == 0)
{
v___y_632_ = v___y_639_;
v___y_633_ = v___x_623_;
goto v___jp_631_;
}
else
{
v___y_632_ = v___y_639_;
v___y_633_ = v___y_639_;
goto v___jp_631_;
}
}
else
{
lean_object* v___x_644_; lean_object* v___x_645_; lean_object* v___x_646_; uint32_t v___x_647_; 
v___x_644_ = lean_uint32_to_nat(v___y_130_);
v___x_645_ = lean_uint32_to_nat(v___y_131_);
v___x_646_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_644_, v___x_645_);
v___x_647_ = lean_uint32_of_nat(v___x_646_);
lean_dec(v___x_646_);
return v___x_647_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runControl___lam__1___boxed(lean_object* v___y_662_, lean_object* v___y_663_){
_start:
{
uint32_t v___y_2432__boxed_664_; uint32_t v___y_2433__boxed_665_; uint32_t v_res_666_; lean_object* v_r_667_; 
v___y_2432__boxed_664_ = lean_unbox_uint32(v___y_662_);
lean_dec(v___y_662_);
v___y_2433__boxed_665_ = lean_unbox_uint32(v___y_663_);
lean_dec(v___y_663_);
v_res_666_ = lp_competition_runControl___lam__1(v___y_2432__boxed_664_, v___y_2433__boxed_665_);
v_r_667_ = lean_box_uint32(v_res_666_);
return v_r_667_;
}
}
LEAN_EXPORT lean_object* lp_competition_runControl(){
_start:
{
lean_object* v___f_673_; lean_object* v___f_674_; lean_object* v___x_675_; lean_object* v___x_676_; lean_object* v___x_677_; 
v___f_673_ = ((lean_object*)(lp_competition_runControl___closed__0));
v___f_674_ = ((lean_object*)(lp_competition_runControl___closed__1));
v___x_675_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_676_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_677_ = lp_competition_Bench_Suite_run(v___f_673_, v___f_674_, v___x_675_, v___x_676_);
return v___x_677_;
}
}
LEAN_EXPORT lean_object* lp_competition_runControl___boxed(lean_object* v_a_678_){
_start:
{
lean_object* v_res_679_; 
v_res_679_ = lp_competition_runControl();
return v_res_679_;
}
}
LEAN_EXPORT uint32_t lp_competition_runFar___lam__0(uint32_t v___y_680_, uint32_t v___y_681_){
_start:
{
uint32_t v___y_683_; uint8_t v___y_684_; uint32_t v___y_687_; uint32_t v___y_688_; uint32_t v___y_689_; uint32_t v___x_695_; uint32_t v_a_696_; uint32_t v_b_697_; uint8_t v_swap_698_; uint32_t v___y_700_; uint32_t v___y_701_; uint32_t v___y_703_; 
v___x_695_ = 2147483647;
v_a_696_ = lean_uint32_land(v___y_680_, v___x_695_);
v_b_697_ = lean_uint32_land(v___y_681_, v___x_695_);
v_swap_698_ = lean_uint32_dec_lt(v_a_696_, v_b_697_);
if (v_swap_698_ == 0)
{
v___y_703_ = v___y_680_;
goto v___jp_702_;
}
else
{
v___y_703_ = v___y_681_;
goto v___jp_702_;
}
v___jp_682_:
{
if (v___y_684_ == 0)
{
uint32_t v___x_685_; 
v___x_685_ = lp_competition_Submission_R22FarOnlyAdd_coldAdd(v___y_680_, v___y_681_);
return v___x_685_;
}
else
{
return v___y_683_;
}
}
v___jp_686_:
{
uint32_t v___x_690_; uint8_t v___x_691_; 
v___x_690_ = 2139095040;
v___x_691_ = lean_uint32_dec_lt(v___y_688_, v___x_690_);
if (v___x_691_ == 0)
{
v___y_683_ = v___y_687_;
v___y_684_ = v___x_691_;
goto v___jp_682_;
}
else
{
uint32_t v___x_692_; uint32_t v___x_693_; uint8_t v___x_694_; 
v___x_692_ = 218103808;
v___x_693_ = lean_uint32_sub(v___y_688_, v___y_689_);
v___x_694_ = lean_uint32_dec_le(v___x_692_, v___x_693_);
v___y_683_ = v___y_687_;
v___y_684_ = v___x_694_;
goto v___jp_682_;
}
}
v___jp_699_:
{
if (v_swap_698_ == 0)
{
v___y_687_ = v___y_700_;
v___y_688_ = v___y_701_;
v___y_689_ = v_b_697_;
goto v___jp_686_;
}
else
{
v___y_687_ = v___y_700_;
v___y_688_ = v___y_701_;
v___y_689_ = v_a_696_;
goto v___jp_686_;
}
}
v___jp_702_:
{
if (v_swap_698_ == 0)
{
v___y_700_ = v___y_703_;
v___y_701_ = v_a_696_;
goto v___jp_699_;
}
else
{
v___y_700_ = v___y_703_;
v___y_701_ = v_b_697_;
goto v___jp_699_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runFar___lam__0___boxed(lean_object* v___y_704_, lean_object* v___y_705_){
_start:
{
uint32_t v___y_1645__boxed_706_; uint32_t v___y_1646__boxed_707_; uint32_t v_res_708_; lean_object* v_r_709_; 
v___y_1645__boxed_706_ = lean_unbox_uint32(v___y_704_);
lean_dec(v___y_704_);
v___y_1646__boxed_707_ = lean_unbox_uint32(v___y_705_);
lean_dec(v___y_705_);
v_res_708_ = lp_competition_runFar___lam__0(v___y_1645__boxed_706_, v___y_1646__boxed_707_);
v_r_709_ = lean_box_uint32(v_res_708_);
return v_r_709_;
}
}
LEAN_EXPORT uint32_t lp_competition_runFar___lam__1(uint32_t v___y_710_, uint32_t v___y_711_){
_start:
{
uint32_t v___y_713_; uint32_t v___y_717_; uint32_t v___y_721_; uint32_t v___y_722_; uint32_t v___y_723_; uint64_t v___y_727_; uint8_t v___y_728_; uint32_t v___y_729_; uint64_t v___y_730_; uint32_t v___y_742_; uint32_t v___y_743_; uint32_t v___y_744_; uint64_t v___y_748_; uint8_t v___y_749_; uint32_t v___y_750_; uint64_t v___y_751_; uint8_t v___y_763_; uint8_t v___y_779_; uint8_t v___y_793_; uint8_t v___y_810_; float v___y_817_; float v___y_818_; float v___y_832_; uint8_t v___y_833_; float v___y_848_; uint32_t v___x_857_; uint32_t v___x_858_; uint8_t v___y_860_; uint32_t v___x_872_; uint32_t v___y_874_; uint32_t v___y_875_; uint32_t v___y_876_; uint32_t v___y_877_; uint32_t v___y_884_; uint8_t v___y_885_; uint32_t v___y_886_; uint32_t v___y_887_; uint64_t v___y_891_; uint64_t v___y_892_; uint8_t v___y_893_; uint32_t v___y_894_; uint64_t v___y_895_; uint64_t v___y_905_; uint64_t v___y_906_; uint8_t v___y_907_; uint8_t v___y_908_; uint32_t v___y_909_; uint64_t v___y_910_; uint64_t v___y_917_; uint64_t v___y_918_; uint8_t v___y_919_; uint32_t v___y_920_; uint64_t v___y_921_; uint64_t v___y_927_; uint64_t v___y_928_; uint64_t v___y_929_; uint8_t v___y_930_; uint32_t v___y_931_; uint64_t v___y_932_; uint64_t v___y_987_; uint64_t v___y_988_; uint64_t v___y_989_; uint64_t v___y_990_; uint8_t v___y_991_; uint32_t v___y_992_; uint64_t v___y_993_; uint64_t v___y_999_; uint64_t v___y_1000_; uint64_t v___y_1001_; uint64_t v___y_1002_; uint64_t v___y_1003_; uint8_t v___y_1004_; uint64_t v___y_1005_; uint32_t v___y_1006_; uint64_t v___y_1007_; uint64_t v___y_1012_; uint64_t v___y_1013_; uint64_t v___y_1014_; uint64_t v___y_1015_; uint8_t v___y_1016_; uint32_t v___y_1017_; uint64_t v___y_1018_; uint64_t v___y_1023_; uint64_t v___y_1024_; uint64_t v___y_1025_; uint64_t v___y_1026_; uint64_t v___y_1027_; uint8_t v___y_1028_; uint64_t v___y_1029_; uint32_t v___y_1030_; uint64_t v___y_1031_; uint64_t v___y_1036_; uint64_t v___y_1037_; uint64_t v___y_1038_; uint64_t v___y_1039_; uint8_t v___y_1040_; uint32_t v___y_1041_; uint64_t v___y_1042_; uint64_t v___y_1047_; uint64_t v___y_1048_; uint64_t v___y_1049_; uint64_t v___y_1050_; uint64_t v___y_1051_; uint8_t v___y_1052_; uint64_t v___y_1053_; uint32_t v___y_1054_; uint64_t v___y_1055_; uint64_t v___y_1060_; uint64_t v___y_1061_; uint64_t v___y_1062_; uint8_t v___y_1063_; uint64_t v___y_1064_; uint32_t v___y_1065_; uint64_t v___y_1066_; uint64_t v___y_1071_; uint64_t v___y_1072_; uint64_t v___y_1073_; uint64_t v___y_1074_; uint64_t v___y_1075_; uint64_t v___y_1076_; uint8_t v___y_1077_; uint32_t v___y_1078_; uint64_t v___y_1079_; uint64_t v___y_1084_; uint64_t v___y_1085_; uint64_t v___y_1086_; uint8_t v___y_1087_; uint64_t v___y_1088_; uint32_t v___y_1089_; uint64_t v___y_1090_; uint64_t v___y_1095_; uint64_t v___y_1096_; uint64_t v___y_1097_; uint64_t v___y_1098_; uint8_t v___y_1099_; uint32_t v___y_1100_; uint64_t v___y_1101_; uint64_t v___y_1105_; uint64_t v___y_1106_; uint8_t v___y_1107_; uint32_t v___y_1108_; uint64_t v___y_1117_; uint64_t v___y_1118_; uint64_t v___y_1119_; uint8_t v___y_1120_; uint32_t v___y_1121_; uint64_t v___y_1122_; uint32_t v_ex_1155_; uint32_t v___x_1156_; uint32_t v_ey_1157_; uint64_t v___y_1159_; uint64_t v___y_1160_; uint8_t v___y_1161_; uint32_t v___y_1162_; uint64_t v___y_1163_; uint64_t v___y_1170_; uint8_t v___y_1171_; uint32_t v___y_1172_; uint64_t v___y_1173_; uint8_t v___y_1180_; uint32_t v___y_1181_; uint32_t v___y_1182_; uint64_t v___y_1183_; uint8_t v___y_1191_; uint32_t v___x_1201_; uint32_t v___x_1202_; uint8_t v___x_1203_; uint8_t v___y_1205_; uint8_t v___y_1206_; uint8_t v___y_1208_; uint8_t v___y_1209_; uint8_t v___y_1210_; uint8_t v___y_1212_; uint8_t v___y_1213_; uint8_t v___y_1219_; 
v___x_857_ = 23;
v___x_858_ = lean_uint32_shift_right(v___y_710_, v___x_857_);
v___x_872_ = 255;
v_ex_1155_ = lean_uint32_land(v___x_858_, v___x_872_);
v___x_1156_ = lean_uint32_shift_right(v___y_711_, v___x_857_);
v_ey_1157_ = lean_uint32_land(v___x_1156_, v___x_872_);
v___x_1201_ = lean_uint32_add(v_ex_1155_, v_ey_1157_);
v___x_1202_ = 128;
v___x_1203_ = lean_uint32_dec_lt(v___x_1201_, v___x_1202_);
if (v___x_1203_ == 0)
{
uint32_t v___x_1228_; uint32_t v_a_1229_; uint32_t v___x_1230_; uint32_t v___x_1231_; uint32_t v___x_1232_; uint8_t v___x_1233_; 
v___x_1228_ = 2147483647;
v_a_1229_ = lean_uint32_land(v___y_710_, v___x_1228_);
v___x_1230_ = 201326591;
v___x_1231_ = 1;
v___x_1232_ = lean_uint32_sub(v_a_1229_, v___x_1231_);
v___x_1233_ = lean_uint32_dec_le(v___x_1230_, v___x_1232_);
if (v___x_1233_ == 0)
{
v___y_860_ = v___x_1233_;
goto v___jp_859_;
}
else
{
uint32_t v___x_1234_; uint8_t v___x_1235_; 
v___x_1234_ = 2139095040;
v___x_1235_ = lean_uint32_dec_lt(v_a_1229_, v___x_1234_);
v___y_860_ = v___x_1235_;
goto v___jp_859_;
}
}
else
{
uint32_t v___x_1236_; uint32_t v___x_1237_; uint32_t v___x_1238_; uint8_t v___x_1239_; 
v___x_1236_ = 4278190080;
v___x_1237_ = 1;
v___x_1238_ = lean_uint32_shift_left(v___y_710_, v___x_1237_);
v___x_1239_ = lean_uint32_dec_le(v___x_1236_, v___x_1238_);
if (v___x_1239_ == 0)
{
uint32_t v___x_1240_; uint8_t v___x_1241_; 
v___x_1240_ = lean_uint32_shift_left(v___y_711_, v___x_1237_);
v___x_1241_ = lean_uint32_dec_le(v___x_1236_, v___x_1240_);
v___y_1219_ = v___x_1241_;
goto v___jp_1218_;
}
else
{
v___y_1219_ = v___x_1239_;
goto v___jp_1218_;
}
}
v___jp_712_:
{
uint32_t v___x_714_; uint32_t v___x_715_; 
v___x_714_ = 8388608;
v___x_715_ = lean_uint32_lor(v___y_713_, v___x_714_);
return v___x_715_;
}
v___jp_716_:
{
uint32_t v___x_718_; uint32_t v___x_719_; 
v___x_718_ = 8388608;
v___x_719_ = lean_uint32_lor(v___y_717_, v___x_718_);
return v___x_719_;
}
v___jp_720_:
{
uint32_t v___x_724_; uint32_t v___x_725_; 
v___x_724_ = lean_uint32_land(v___y_721_, v___y_722_);
v___x_725_ = lean_uint32_lor(v___y_723_, v___x_724_);
return v___x_725_;
}
v___jp_726_:
{
uint8_t v___x_731_; 
v___x_731_ = lean_uint64_dec_eq(v___y_730_, v___y_727_);
if (v___x_731_ == 0)
{
uint64_t v___x_732_; uint8_t v___x_733_; 
v___x_732_ = 8388608ULL;
v___x_733_ = lean_uint64_dec_eq(v___y_730_, v___x_732_);
if (v___x_733_ == 0)
{
uint32_t v___x_734_; 
v___x_734_ = lean_uint64_to_uint32(v___y_730_);
if (v___y_728_ == 0)
{
uint32_t v___x_735_; 
v___x_735_ = 0;
v___y_721_ = v___x_734_;
v___y_722_ = v___y_729_;
v___y_723_ = v___x_735_;
goto v___jp_720_;
}
else
{
uint32_t v___x_736_; 
v___x_736_ = 2147483648;
v___y_721_ = v___x_734_;
v___y_722_ = v___y_729_;
v___y_723_ = v___x_736_;
goto v___jp_720_;
}
}
else
{
if (v___y_728_ == 0)
{
uint32_t v___x_737_; 
v___x_737_ = 0;
v___y_717_ = v___x_737_;
goto v___jp_716_;
}
else
{
uint32_t v___x_738_; 
v___x_738_ = 2147483648;
v___y_717_ = v___x_738_;
goto v___jp_716_;
}
}
}
else
{
if (v___y_728_ == 0)
{
uint32_t v___x_739_; 
v___x_739_ = 0;
return v___x_739_;
}
else
{
uint32_t v___x_740_; 
v___x_740_ = 2147483648;
return v___x_740_;
}
}
}
v___jp_741_:
{
uint32_t v___x_745_; uint32_t v___x_746_; 
v___x_745_ = lean_uint32_land(v___y_742_, v___y_743_);
v___x_746_ = lean_uint32_lor(v___y_744_, v___x_745_);
return v___x_746_;
}
v___jp_747_:
{
uint8_t v___x_752_; 
v___x_752_ = lean_uint64_dec_eq(v___y_751_, v___y_748_);
if (v___x_752_ == 0)
{
uint64_t v___x_753_; uint8_t v___x_754_; 
v___x_753_ = 8388608ULL;
v___x_754_ = lean_uint64_dec_eq(v___y_751_, v___x_753_);
if (v___x_754_ == 0)
{
uint32_t v___x_755_; 
v___x_755_ = lean_uint64_to_uint32(v___y_751_);
if (v___y_749_ == 0)
{
uint32_t v___x_756_; 
v___x_756_ = 0;
v___y_742_ = v___x_755_;
v___y_743_ = v___y_750_;
v___y_744_ = v___x_756_;
goto v___jp_741_;
}
else
{
uint32_t v___x_757_; 
v___x_757_ = 2147483648;
v___y_742_ = v___x_755_;
v___y_743_ = v___y_750_;
v___y_744_ = v___x_757_;
goto v___jp_741_;
}
}
else
{
if (v___y_749_ == 0)
{
uint32_t v___x_758_; 
v___x_758_ = 0;
v___y_713_ = v___x_758_;
goto v___jp_712_;
}
else
{
uint32_t v___x_759_; 
v___x_759_ = 2147483648;
v___y_713_ = v___x_759_;
goto v___jp_712_;
}
}
}
else
{
if (v___y_749_ == 0)
{
uint32_t v___x_760_; 
v___x_760_ = 0;
return v___x_760_;
}
else
{
uint32_t v___x_761_; 
v___x_761_ = 2147483648;
return v___x_761_;
}
}
}
v___jp_762_:
{
if (v___y_763_ == 0)
{
uint32_t v___x_764_; 
v___x_764_ = lp_competition_Submission_FastMul_mul(v___y_710_, v___y_711_);
return v___x_764_;
}
else
{
uint32_t v___x_765_; uint32_t v___x_766_; 
v___x_765_ = 4194304;
v___x_766_ = lean_uint32_lor(v___y_711_, v___x_765_);
return v___x_766_;
}
}
v___jp_767_:
{
uint32_t v___x_768_; uint32_t v___x_769_; uint32_t v___x_770_; uint32_t v___x_771_; uint8_t v___x_772_; 
v___x_768_ = 23;
v___x_769_ = lean_uint32_shift_right(v___y_711_, v___x_768_);
v___x_770_ = 255;
v___x_771_ = lean_uint32_land(v___x_769_, v___x_770_);
v___x_772_ = lean_uint32_dec_eq(v___x_771_, v___x_770_);
if (v___x_772_ == 0)
{
v___y_763_ = v___x_772_;
goto v___jp_762_;
}
else
{
uint32_t v___x_773_; uint32_t v___x_774_; uint32_t v___x_775_; uint8_t v___x_776_; 
v___x_773_ = 8388607;
v___x_774_ = lean_uint32_land(v___y_711_, v___x_773_);
v___x_775_ = 0;
v___x_776_ = lean_uint32_dec_eq(v___x_774_, v___x_775_);
if (v___x_776_ == 0)
{
v___y_763_ = v___x_772_;
goto v___jp_762_;
}
else
{
uint32_t v___x_777_; 
v___x_777_ = lp_competition_Submission_FastMul_mul(v___y_710_, v___y_711_);
return v___x_777_;
}
}
}
v___jp_778_:
{
if (v___y_779_ == 0)
{
goto v___jp_767_;
}
else
{
uint32_t v___x_780_; uint32_t v___x_781_; 
v___x_780_ = 4194304;
v___x_781_ = lean_uint32_lor(v___y_710_, v___x_780_);
return v___x_781_;
}
}
v___jp_782_:
{
uint32_t v___x_783_; uint32_t v___x_784_; uint32_t v___x_785_; uint32_t v___x_786_; uint8_t v___x_787_; 
v___x_783_ = 23;
v___x_784_ = lean_uint32_shift_right(v___y_710_, v___x_783_);
v___x_785_ = 255;
v___x_786_ = lean_uint32_land(v___x_784_, v___x_785_);
v___x_787_ = lean_uint32_dec_eq(v___x_786_, v___x_785_);
if (v___x_787_ == 0)
{
v___y_779_ = v___x_787_;
goto v___jp_778_;
}
else
{
uint32_t v___x_788_; uint32_t v___x_789_; uint32_t v___x_790_; uint8_t v___x_791_; 
v___x_788_ = 8388607;
v___x_789_ = lean_uint32_land(v___y_710_, v___x_788_);
v___x_790_ = 0;
v___x_791_ = lean_uint32_dec_eq(v___x_789_, v___x_790_);
if (v___x_791_ == 0)
{
v___y_779_ = v___x_787_;
goto v___jp_778_;
}
else
{
goto v___jp_767_;
}
}
}
v___jp_792_:
{
if (v___y_793_ == 0)
{
goto v___jp_782_;
}
else
{
uint32_t v___x_794_; uint32_t v___x_795_; uint32_t v___x_796_; uint8_t v___x_797_; 
v___x_794_ = 4194304;
v___x_795_ = lean_uint32_land(v___y_711_, v___x_794_);
v___x_796_ = 0;
v___x_797_ = lean_uint32_dec_eq(v___x_795_, v___x_796_);
if (v___x_797_ == 0)
{
goto v___jp_782_;
}
else
{
uint32_t v___x_798_; 
v___x_798_ = lean_uint32_lor(v___y_711_, v___x_794_);
return v___x_798_;
}
}
}
v___jp_799_:
{
uint32_t v___x_800_; uint32_t v___x_801_; uint32_t v___x_802_; uint32_t v___x_803_; uint8_t v___x_804_; 
v___x_800_ = 23;
v___x_801_ = lean_uint32_shift_right(v___y_711_, v___x_800_);
v___x_802_ = 255;
v___x_803_ = lean_uint32_land(v___x_801_, v___x_802_);
v___x_804_ = lean_uint32_dec_eq(v___x_803_, v___x_802_);
if (v___x_804_ == 0)
{
v___y_793_ = v___x_804_;
goto v___jp_792_;
}
else
{
uint32_t v___x_805_; uint32_t v___x_806_; uint32_t v___x_807_; uint8_t v___x_808_; 
v___x_805_ = 8388607;
v___x_806_ = lean_uint32_land(v___y_711_, v___x_805_);
v___x_807_ = 0;
v___x_808_ = lean_uint32_dec_eq(v___x_806_, v___x_807_);
if (v___x_808_ == 0)
{
v___y_793_ = v___x_804_;
goto v___jp_792_;
}
else
{
goto v___jp_782_;
}
}
}
v___jp_809_:
{
if (v___y_810_ == 0)
{
goto v___jp_799_;
}
else
{
uint32_t v___x_811_; uint32_t v___x_812_; uint32_t v___x_813_; uint8_t v___x_814_; 
v___x_811_ = 4194304;
v___x_812_ = lean_uint32_land(v___y_710_, v___x_811_);
v___x_813_ = 0;
v___x_814_ = lean_uint32_dec_eq(v___x_812_, v___x_813_);
if (v___x_814_ == 0)
{
goto v___jp_799_;
}
else
{
uint32_t v___x_815_; 
v___x_815_ = lean_uint32_lor(v___y_710_, v___x_811_);
return v___x_815_;
}
}
}
v___jp_816_:
{
float v_result_819_; uint8_t v___x_820_; 
v_result_819_ = lean_float32_mul(v___y_817_, v___y_818_);
v___x_820_ = lean_float32_beq(v_result_819_, v_result_819_);
if (v___x_820_ == 0)
{
uint32_t v___x_821_; uint32_t v___x_822_; uint32_t v___x_823_; uint32_t v___x_824_; uint8_t v___x_825_; 
v___x_821_ = 23;
v___x_822_ = lean_uint32_shift_right(v___y_710_, v___x_821_);
v___x_823_ = 255;
v___x_824_ = lean_uint32_land(v___x_822_, v___x_823_);
v___x_825_ = lean_uint32_dec_eq(v___x_824_, v___x_823_);
if (v___x_825_ == 0)
{
v___y_810_ = v___x_825_;
goto v___jp_809_;
}
else
{
uint32_t v___x_826_; uint32_t v___x_827_; uint32_t v___x_828_; uint8_t v___x_829_; 
v___x_826_ = 8388607;
v___x_827_ = lean_uint32_land(v___y_710_, v___x_826_);
v___x_828_ = 0;
v___x_829_ = lean_uint32_dec_eq(v___x_827_, v___x_828_);
if (v___x_829_ == 0)
{
v___y_810_ = v___x_825_;
goto v___jp_809_;
}
else
{
goto v___jp_799_;
}
}
}
else
{
uint32_t v___x_830_; 
v___x_830_ = lean_float32_to_bits(v_result_819_);
return v___x_830_;
}
}
v___jp_831_:
{
if (v___y_833_ == 0)
{
float v___x_834_; 
v___x_834_ = lean_float32_of_bits(v___y_711_);
v___y_817_ = v___y_832_;
v___y_818_ = v___x_834_;
goto v___jp_816_;
}
else
{
uint32_t v___x_835_; uint32_t v___x_836_; uint32_t v___x_837_; uint32_t v___x_838_; float v___x_839_; lean_object* v___x_840_; uint32_t v___x_841_; uint32_t v___x_842_; lean_object* v___x_843_; lean_object* v___x_844_; float v___x_845_; float v___x_846_; 
v___x_835_ = 8388607;
v___x_836_ = lean_uint32_land(v___y_711_, v___x_835_);
v___x_837_ = 8388608;
v___x_838_ = lean_uint32_lor(v___x_836_, v___x_837_);
v___x_839_ = lean_uint32_to_float32(v___x_838_);
v___x_840_ = lp_competition_R2W01b_scaleTable;
v___x_841_ = 23;
v___x_842_ = lean_uint32_shift_right(v___y_711_, v___x_841_);
v___x_843_ = lean_uint32_to_nat(v___x_842_);
v___x_844_ = lean_array_fget_borrowed(v___x_840_, v___x_843_);
lean_dec(v___x_843_);
v___x_845_ = lean_unbox_float32(v___x_844_);
v___x_846_ = lean_float32_mul(v___x_839_, v___x_845_);
v___y_817_ = v___y_832_;
v___y_818_ = v___x_846_;
goto v___jp_816_;
}
}
v___jp_847_:
{
uint32_t v___x_849_; uint32_t v_a_850_; uint32_t v___x_851_; uint32_t v___x_852_; uint32_t v___x_853_; uint8_t v___x_854_; 
v___x_849_ = 2147483647;
v_a_850_ = lean_uint32_land(v___y_711_, v___x_849_);
v___x_851_ = 201326591;
v___x_852_ = 1;
v___x_853_ = lean_uint32_sub(v_a_850_, v___x_852_);
v___x_854_ = lean_uint32_dec_le(v___x_851_, v___x_853_);
if (v___x_854_ == 0)
{
v___y_832_ = v___y_848_;
v___y_833_ = v___x_854_;
goto v___jp_831_;
}
else
{
uint32_t v___x_855_; uint8_t v___x_856_; 
v___x_855_ = 2139095040;
v___x_856_ = lean_uint32_dec_lt(v_a_850_, v___x_855_);
v___y_832_ = v___y_848_;
v___y_833_ = v___x_856_;
goto v___jp_831_;
}
}
v___jp_859_:
{
if (v___y_860_ == 0)
{
float v___x_861_; 
v___x_861_ = lean_float32_of_bits(v___y_710_);
v___y_848_ = v___x_861_;
goto v___jp_847_;
}
else
{
uint32_t v___x_862_; uint32_t v___x_863_; uint32_t v___x_864_; uint32_t v___x_865_; float v___x_866_; lean_object* v___x_867_; lean_object* v___x_868_; lean_object* v___x_869_; float v___x_870_; float v___x_871_; 
v___x_862_ = 8388607;
v___x_863_ = lean_uint32_land(v___y_710_, v___x_862_);
v___x_864_ = 8388608;
v___x_865_ = lean_uint32_lor(v___x_863_, v___x_864_);
v___x_866_ = lean_uint32_to_float32(v___x_865_);
v___x_867_ = lp_competition_R2W01b_scaleTable;
v___x_868_ = lean_uint32_to_nat(v___x_858_);
v___x_869_ = lean_array_fget_borrowed(v___x_867_, v___x_868_);
lean_dec(v___x_868_);
v___x_870_ = lean_unbox_float32(v___x_869_);
v___x_871_ = lean_float32_mul(v___x_866_, v___x_870_);
v___y_848_ = v___x_871_;
goto v___jp_847_;
}
}
v___jp_873_:
{
uint32_t v___x_878_; uint32_t v___x_879_; uint32_t v___x_880_; uint32_t v___x_881_; uint32_t v___x_882_; 
v___x_878_ = lean_uint32_land(v___y_874_, v___x_872_);
v___x_879_ = lean_uint32_shift_left(v___x_878_, v___x_857_);
v___x_880_ = lean_uint32_lor(v___y_877_, v___x_879_);
v___x_881_ = lean_uint32_land(v___y_875_, v___y_876_);
v___x_882_ = lean_uint32_lor(v___x_880_, v___x_881_);
return v___x_882_;
}
v___jp_883_:
{
if (v___y_885_ == 0)
{
uint32_t v___x_888_; 
v___x_888_ = 0;
v___y_874_ = v___y_884_;
v___y_875_ = v___y_887_;
v___y_876_ = v___y_886_;
v___y_877_ = v___x_888_;
goto v___jp_873_;
}
else
{
uint32_t v___x_889_; 
v___x_889_ = 2147483648;
v___y_874_ = v___y_884_;
v___y_875_ = v___y_887_;
v___y_876_ = v___y_886_;
v___y_877_ = v___x_889_;
goto v___jp_873_;
}
}
v___jp_890_:
{
uint64_t v___x_896_; uint64_t v_encodedExponent_897_; uint32_t v___x_898_; uint64_t v___x_899_; uint8_t v___x_900_; 
v___x_896_ = 171ULL;
v_encodedExponent_897_ = lean_uint64_sub(v___y_892_, v___x_896_);
v___x_898_ = lean_uint64_to_uint32(v_encodedExponent_897_);
v___x_899_ = 8388608ULL;
v___x_900_ = lean_uint64_dec_lt(v___y_895_, v___x_899_);
if (v___x_900_ == 0)
{
uint64_t v___x_901_; uint32_t v___x_902_; 
v___x_901_ = lean_uint64_sub(v___y_895_, v___x_899_);
v___x_902_ = lean_uint64_to_uint32(v___x_901_);
v___y_884_ = v___x_898_;
v___y_885_ = v___y_893_;
v___y_886_ = v___y_894_;
v___y_887_ = v___x_902_;
goto v___jp_883_;
}
else
{
uint32_t v___x_903_; 
v___x_903_ = lean_uint64_to_uint32(v___y_891_);
v___y_884_ = v___x_898_;
v___y_885_ = v___y_893_;
v___y_886_ = v___y_894_;
v___y_887_ = v___x_903_;
goto v___jp_883_;
}
}
v___jp_904_:
{
uint64_t v___x_911_; uint8_t v___x_912_; 
v___x_911_ = 425ULL;
v___x_912_ = lean_uint64_dec_lt(v___x_911_, v___y_910_);
if (v___x_912_ == 0)
{
if (v___y_907_ == 0)
{
v___y_891_ = v___y_906_;
v___y_892_ = v___y_910_;
v___y_893_ = v___y_908_;
v___y_894_ = v___y_909_;
v___y_895_ = v___y_905_;
goto v___jp_890_;
}
else
{
uint64_t v___x_913_; 
v___x_913_ = 8388608ULL;
v___y_891_ = v___y_906_;
v___y_892_ = v___y_910_;
v___y_893_ = v___y_908_;
v___y_894_ = v___y_909_;
v___y_895_ = v___x_913_;
goto v___jp_890_;
}
}
else
{
if (v___y_908_ == 0)
{
uint32_t v___x_914_; 
v___x_914_ = 2139095040;
return v___x_914_;
}
else
{
uint32_t v___x_915_; 
v___x_915_ = 4286578688;
return v___x_915_;
}
}
}
v___jp_916_:
{
uint64_t v___x_922_; uint8_t v_carry_923_; 
v___x_922_ = 16777216ULL;
v_carry_923_ = lean_uint64_dec_eq(v___y_921_, v___x_922_);
if (v_carry_923_ == 0)
{
v___y_905_ = v___y_921_;
v___y_906_ = v___y_917_;
v___y_907_ = v_carry_923_;
v___y_908_ = v___y_919_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_918_;
goto v___jp_904_;
}
else
{
uint64_t v___x_924_; uint64_t v___x_925_; 
v___x_924_ = 1ULL;
v___x_925_ = lean_uint64_add(v___y_918_, v___x_924_);
v___y_905_ = v___y_921_;
v___y_906_ = v___y_917_;
v___y_907_ = v_carry_923_;
v___y_908_ = v___y_919_;
v___y_909_ = v___y_920_;
v___y_910_ = v___x_925_;
goto v___jp_904_;
}
}
v___jp_926_:
{
uint64_t v_position_933_; uint64_t v___x_934_; uint8_t v___x_935_; 
v_position_933_ = lean_uint64_add(v___y_932_, v___y_929_);
v___x_934_ = 172ULL;
v___x_935_ = lean_uint64_dec_lt(v_position_933_, v___x_934_);
if (v___x_935_ == 0)
{
uint64_t v___x_936_; uint8_t v___x_937_; 
v___x_936_ = 23ULL;
v___x_937_ = lean_uint64_dec_lt(v___y_932_, v___x_936_);
if (v___x_937_ == 0)
{
uint64_t v___x_938_; uint8_t v___x_939_; 
v___x_938_ = lean_uint64_sub(v___y_932_, v___x_936_);
v___x_939_ = lean_uint64_dec_eq(v___x_938_, v___y_928_);
if (v___x_939_ == 0)
{
uint64_t v___x_940_; uint8_t v___x_941_; 
v___x_940_ = 64ULL;
v___x_941_ = lean_uint64_dec_lt(v___x_938_, v___x_940_);
if (v___x_941_ == 0)
{
uint8_t v___x_942_; 
v___x_942_ = lean_uint64_dec_eq(v___x_938_, v___x_940_);
if (v___x_942_ == 0)
{
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___y_928_;
goto v___jp_916_;
}
else
{
uint64_t v___x_943_; uint8_t v___x_944_; 
v___x_943_ = 9223372036854775808ULL;
v___x_944_ = lean_uint64_dec_lt(v___x_943_, v___y_927_);
if (v___x_944_ == 0)
{
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___y_928_;
goto v___jp_916_;
}
else
{
uint64_t v___x_945_; 
v___x_945_ = 1ULL;
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___x_945_;
goto v___jp_916_;
}
}
}
else
{
uint64_t v_quotient_946_; uint64_t v___x_947_; uint64_t v___x_948_; uint64_t v___x_949_; uint64_t v_remainder_950_; uint64_t v___x_951_; uint64_t v_half_952_; uint8_t v___x_953_; 
v_quotient_946_ = lean_uint64_shift_right(v___y_927_, v___x_938_);
v___x_947_ = 1ULL;
v___x_948_ = lean_uint64_shift_left(v___x_947_, v___x_938_);
v___x_949_ = lean_uint64_sub(v___x_948_, v___x_947_);
v_remainder_950_ = lean_uint64_land(v___y_927_, v___x_949_);
v___x_951_ = lean_uint64_sub(v___x_938_, v___x_947_);
v_half_952_ = lean_uint64_shift_left(v___x_947_, v___x_951_);
v___x_953_ = lean_uint64_dec_lt(v_remainder_950_, v_half_952_);
if (v___x_953_ == 0)
{
uint8_t v___x_954_; 
v___x_954_ = lean_uint64_dec_lt(v_half_952_, v_remainder_950_);
if (v___x_954_ == 0)
{
uint64_t v___x_955_; uint8_t v___x_956_; 
v___x_955_ = lean_uint64_land(v_quotient_946_, v___x_947_);
v___x_956_ = lean_uint64_dec_eq(v___x_955_, v___y_928_);
if (v___x_956_ == 0)
{
uint64_t v___x_957_; 
v___x_957_ = lean_uint64_add(v_quotient_946_, v___x_947_);
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___x_957_;
goto v___jp_916_;
}
else
{
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v_quotient_946_;
goto v___jp_916_;
}
}
else
{
uint64_t v___x_958_; 
v___x_958_ = lean_uint64_add(v_quotient_946_, v___x_947_);
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___x_958_;
goto v___jp_916_;
}
}
else
{
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v_quotient_946_;
goto v___jp_916_;
}
}
}
else
{
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___y_927_;
goto v___jp_916_;
}
}
else
{
uint64_t v___x_959_; uint64_t v___x_960_; 
v___x_959_ = lean_uint64_sub(v___x_936_, v___y_932_);
v___x_960_ = lean_uint64_shift_left(v___y_927_, v___x_959_);
v___y_917_ = v___y_928_;
v___y_918_ = v_position_933_;
v___y_919_ = v___y_930_;
v___y_920_ = v___y_931_;
v___y_921_ = v___x_960_;
goto v___jp_916_;
}
}
else
{
uint64_t v___x_961_; uint8_t v___x_962_; 
v___x_961_ = 149ULL;
v___x_962_ = lean_uint64_dec_lt(v___y_929_, v___x_961_);
if (v___x_962_ == 0)
{
uint64_t v___x_963_; uint64_t v___x_964_; 
v___x_963_ = lean_uint64_sub(v___y_929_, v___x_961_);
v___x_964_ = lean_uint64_shift_left(v___y_927_, v___x_963_);
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v___x_964_;
goto v___jp_726_;
}
else
{
uint64_t v___x_965_; uint8_t v___x_966_; 
v___x_965_ = lean_uint64_sub(v___x_961_, v___y_929_);
v___x_966_ = lean_uint64_dec_eq(v___x_965_, v___y_928_);
if (v___x_966_ == 0)
{
uint64_t v___x_967_; uint8_t v___x_968_; 
v___x_967_ = 64ULL;
v___x_968_ = lean_uint64_dec_lt(v___x_965_, v___x_967_);
if (v___x_968_ == 0)
{
uint8_t v___x_969_; 
v___x_969_ = lean_uint64_dec_eq(v___x_965_, v___x_967_);
if (v___x_969_ == 0)
{
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v___y_928_;
goto v___jp_726_;
}
else
{
uint64_t v___x_970_; uint8_t v___x_971_; 
v___x_970_ = 9223372036854775808ULL;
v___x_971_ = lean_uint64_dec_lt(v___x_970_, v___y_927_);
if (v___x_971_ == 0)
{
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v___y_928_;
goto v___jp_726_;
}
else
{
uint64_t v___x_972_; 
v___x_972_ = 1ULL;
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v___x_972_;
goto v___jp_726_;
}
}
}
else
{
uint64_t v_quotient_973_; uint64_t v___x_974_; uint64_t v___x_975_; uint64_t v___x_976_; uint64_t v_remainder_977_; uint64_t v___x_978_; uint64_t v_half_979_; uint8_t v___x_980_; 
v_quotient_973_ = lean_uint64_shift_right(v___y_927_, v___x_965_);
v___x_974_ = 1ULL;
v___x_975_ = lean_uint64_shift_left(v___x_974_, v___x_965_);
v___x_976_ = lean_uint64_sub(v___x_975_, v___x_974_);
v_remainder_977_ = lean_uint64_land(v___y_927_, v___x_976_);
v___x_978_ = lean_uint64_sub(v___x_965_, v___x_974_);
v_half_979_ = lean_uint64_shift_left(v___x_974_, v___x_978_);
v___x_980_ = lean_uint64_dec_lt(v_remainder_977_, v_half_979_);
if (v___x_980_ == 0)
{
uint8_t v___x_981_; 
v___x_981_ = lean_uint64_dec_lt(v_half_979_, v_remainder_977_);
if (v___x_981_ == 0)
{
uint64_t v___x_982_; uint8_t v___x_983_; 
v___x_982_ = lean_uint64_land(v_quotient_973_, v___x_974_);
v___x_983_ = lean_uint64_dec_eq(v___x_982_, v___y_928_);
if (v___x_983_ == 0)
{
uint64_t v___x_984_; 
v___x_984_ = lean_uint64_add(v_quotient_973_, v___x_974_);
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v___x_984_;
goto v___jp_726_;
}
else
{
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v_quotient_973_;
goto v___jp_726_;
}
}
else
{
uint64_t v___x_985_; 
v___x_985_ = lean_uint64_add(v_quotient_973_, v___x_974_);
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v___x_985_;
goto v___jp_726_;
}
}
else
{
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v_quotient_973_;
goto v___jp_726_;
}
}
}
else
{
v___y_727_ = v___y_928_;
v___y_728_ = v___y_930_;
v___y_729_ = v___y_931_;
v___y_730_ = v___y_927_;
goto v___jp_726_;
}
}
}
}
v___jp_986_:
{
uint64_t v___x_994_; uint64_t v___x_995_; uint8_t v___x_996_; 
v___x_994_ = 1ULL;
v___x_995_ = lean_uint64_shift_right(v___y_990_, v___x_994_);
v___x_996_ = lean_uint64_dec_eq(v___x_995_, v___y_988_);
if (v___x_996_ == 0)
{
uint64_t v___x_997_; 
v___x_997_ = lean_uint64_add(v___y_993_, v___x_994_);
v___y_927_ = v___y_987_;
v___y_928_ = v___y_988_;
v___y_929_ = v___y_989_;
v___y_930_ = v___y_991_;
v___y_931_ = v___y_992_;
v___y_932_ = v___x_997_;
goto v___jp_926_;
}
else
{
v___y_927_ = v___y_987_;
v___y_928_ = v___y_988_;
v___y_929_ = v___y_989_;
v___y_930_ = v___y_991_;
v___y_931_ = v___y_992_;
v___y_932_ = v___y_993_;
goto v___jp_926_;
}
}
v___jp_998_:
{
uint64_t v___x_1008_; uint8_t v___x_1009_; 
v___x_1008_ = lean_uint64_shift_right(v___y_999_, v___y_1005_);
v___x_1009_ = lean_uint64_dec_eq(v___x_1008_, v___y_1000_);
if (v___x_1009_ == 0)
{
uint64_t v___x_1010_; 
v___x_1010_ = lean_uint64_add(v___y_1003_, v___y_1005_);
v___y_987_ = v___y_1001_;
v___y_988_ = v___y_1000_;
v___y_989_ = v___y_1002_;
v___y_990_ = v___y_1007_;
v___y_991_ = v___y_1004_;
v___y_992_ = v___y_1006_;
v___y_993_ = v___x_1010_;
goto v___jp_986_;
}
else
{
v___y_987_ = v___y_1001_;
v___y_988_ = v___y_1000_;
v___y_989_ = v___y_1002_;
v___y_990_ = v___y_1007_;
v___y_991_ = v___y_1004_;
v___y_992_ = v___y_1006_;
v___y_993_ = v___y_1003_;
goto v___jp_986_;
}
}
v___jp_1011_:
{
uint64_t v___x_1019_; uint64_t v___x_1020_; uint8_t v___x_1021_; 
v___x_1019_ = 2ULL;
v___x_1020_ = lean_uint64_shift_right(v___y_1012_, v___x_1019_);
v___x_1021_ = lean_uint64_dec_eq(v___x_1020_, v___y_1014_);
if (v___x_1021_ == 0)
{
v___y_999_ = v___y_1012_;
v___y_1000_ = v___y_1014_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1015_;
v___y_1003_ = v___y_1018_;
v___y_1004_ = v___y_1016_;
v___y_1005_ = v___x_1019_;
v___y_1006_ = v___y_1017_;
v___y_1007_ = v___x_1020_;
goto v___jp_998_;
}
else
{
v___y_999_ = v___y_1012_;
v___y_1000_ = v___y_1014_;
v___y_1001_ = v___y_1013_;
v___y_1002_ = v___y_1015_;
v___y_1003_ = v___y_1018_;
v___y_1004_ = v___y_1016_;
v___y_1005_ = v___x_1019_;
v___y_1006_ = v___y_1017_;
v___y_1007_ = v___y_1012_;
goto v___jp_998_;
}
}
v___jp_1022_:
{
uint64_t v___x_1032_; uint8_t v___x_1033_; 
v___x_1032_ = lean_uint64_shift_right(v___y_1027_, v___y_1029_);
v___x_1033_ = lean_uint64_dec_eq(v___x_1032_, v___y_1024_);
if (v___x_1033_ == 0)
{
uint64_t v___x_1034_; 
v___x_1034_ = lean_uint64_add(v___y_1023_, v___y_1029_);
v___y_1012_ = v___y_1031_;
v___y_1013_ = v___y_1025_;
v___y_1014_ = v___y_1024_;
v___y_1015_ = v___y_1026_;
v___y_1016_ = v___y_1028_;
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___x_1034_;
goto v___jp_1011_;
}
else
{
v___y_1012_ = v___y_1031_;
v___y_1013_ = v___y_1025_;
v___y_1014_ = v___y_1024_;
v___y_1015_ = v___y_1026_;
v___y_1016_ = v___y_1028_;
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___y_1023_;
goto v___jp_1011_;
}
}
v___jp_1035_:
{
uint64_t v___x_1043_; uint64_t v___x_1044_; uint8_t v___x_1045_; 
v___x_1043_ = 4ULL;
v___x_1044_ = lean_uint64_shift_right(v___y_1039_, v___x_1043_);
v___x_1045_ = lean_uint64_dec_eq(v___x_1044_, v___y_1037_);
if (v___x_1045_ == 0)
{
v___y_1023_ = v___y_1042_;
v___y_1024_ = v___y_1037_;
v___y_1025_ = v___y_1036_;
v___y_1026_ = v___y_1038_;
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1040_;
v___y_1029_ = v___x_1043_;
v___y_1030_ = v___y_1041_;
v___y_1031_ = v___x_1044_;
goto v___jp_1022_;
}
else
{
v___y_1023_ = v___y_1042_;
v___y_1024_ = v___y_1037_;
v___y_1025_ = v___y_1036_;
v___y_1026_ = v___y_1038_;
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1040_;
v___y_1029_ = v___x_1043_;
v___y_1030_ = v___y_1041_;
v___y_1031_ = v___y_1039_;
goto v___jp_1022_;
}
}
v___jp_1046_:
{
uint64_t v___x_1056_; uint8_t v___x_1057_; 
v___x_1056_ = lean_uint64_shift_right(v___y_1053_, v___y_1051_);
v___x_1057_ = lean_uint64_dec_eq(v___x_1056_, v___y_1048_);
if (v___x_1057_ == 0)
{
uint64_t v___x_1058_; 
v___x_1058_ = lean_uint64_add(v___y_1047_, v___y_1051_);
v___y_1036_ = v___y_1049_;
v___y_1037_ = v___y_1048_;
v___y_1038_ = v___y_1050_;
v___y_1039_ = v___y_1055_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___y_1054_;
v___y_1042_ = v___x_1058_;
goto v___jp_1035_;
}
else
{
v___y_1036_ = v___y_1049_;
v___y_1037_ = v___y_1048_;
v___y_1038_ = v___y_1050_;
v___y_1039_ = v___y_1055_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___y_1054_;
v___y_1042_ = v___y_1047_;
goto v___jp_1035_;
}
}
v___jp_1059_:
{
uint64_t v___x_1067_; uint64_t v___x_1068_; uint8_t v___x_1069_; 
v___x_1067_ = 8ULL;
v___x_1068_ = lean_uint64_shift_right(v___y_1064_, v___x_1067_);
v___x_1069_ = lean_uint64_dec_eq(v___x_1068_, v___y_1061_);
if (v___x_1069_ == 0)
{
v___y_1047_ = v___y_1066_;
v___y_1048_ = v___y_1061_;
v___y_1049_ = v___y_1060_;
v___y_1050_ = v___y_1062_;
v___y_1051_ = v___x_1067_;
v___y_1052_ = v___y_1063_;
v___y_1053_ = v___y_1064_;
v___y_1054_ = v___y_1065_;
v___y_1055_ = v___x_1068_;
goto v___jp_1046_;
}
else
{
v___y_1047_ = v___y_1066_;
v___y_1048_ = v___y_1061_;
v___y_1049_ = v___y_1060_;
v___y_1050_ = v___y_1062_;
v___y_1051_ = v___x_1067_;
v___y_1052_ = v___y_1063_;
v___y_1053_ = v___y_1064_;
v___y_1054_ = v___y_1065_;
v___y_1055_ = v___y_1064_;
goto v___jp_1046_;
}
}
v___jp_1070_:
{
uint64_t v___x_1080_; uint8_t v___x_1081_; 
v___x_1080_ = lean_uint64_shift_right(v___y_1076_, v___y_1071_);
v___x_1081_ = lean_uint64_dec_eq(v___x_1080_, v___y_1072_);
if (v___x_1081_ == 0)
{
uint64_t v___x_1082_; 
v___x_1082_ = lean_uint64_add(v___y_1075_, v___y_1071_);
v___y_1060_ = v___y_1073_;
v___y_1061_ = v___y_1072_;
v___y_1062_ = v___y_1074_;
v___y_1063_ = v___y_1077_;
v___y_1064_ = v___y_1079_;
v___y_1065_ = v___y_1078_;
v___y_1066_ = v___x_1082_;
goto v___jp_1059_;
}
else
{
v___y_1060_ = v___y_1073_;
v___y_1061_ = v___y_1072_;
v___y_1062_ = v___y_1074_;
v___y_1063_ = v___y_1077_;
v___y_1064_ = v___y_1079_;
v___y_1065_ = v___y_1078_;
v___y_1066_ = v___y_1075_;
goto v___jp_1059_;
}
}
v___jp_1083_:
{
uint64_t v___x_1091_; uint64_t v___x_1092_; uint8_t v___x_1093_; 
v___x_1091_ = 16ULL;
v___x_1092_ = lean_uint64_shift_right(v___y_1088_, v___x_1091_);
v___x_1093_ = lean_uint64_dec_eq(v___x_1092_, v___y_1085_);
if (v___x_1093_ == 0)
{
v___y_1071_ = v___x_1091_;
v___y_1072_ = v___y_1085_;
v___y_1073_ = v___y_1084_;
v___y_1074_ = v___y_1086_;
v___y_1075_ = v___y_1090_;
v___y_1076_ = v___y_1088_;
v___y_1077_ = v___y_1087_;
v___y_1078_ = v___y_1089_;
v___y_1079_ = v___x_1092_;
goto v___jp_1070_;
}
else
{
v___y_1071_ = v___x_1091_;
v___y_1072_ = v___y_1085_;
v___y_1073_ = v___y_1084_;
v___y_1074_ = v___y_1086_;
v___y_1075_ = v___y_1090_;
v___y_1076_ = v___y_1088_;
v___y_1077_ = v___y_1087_;
v___y_1078_ = v___y_1089_;
v___y_1079_ = v___y_1088_;
goto v___jp_1070_;
}
}
v___jp_1094_:
{
uint64_t v___x_1102_; uint8_t v___x_1103_; 
v___x_1102_ = lean_uint64_shift_right(v___y_1097_, v___y_1095_);
v___x_1103_ = lean_uint64_dec_eq(v___x_1102_, v___y_1096_);
if (v___x_1103_ == 0)
{
v___y_1084_ = v___y_1097_;
v___y_1085_ = v___y_1096_;
v___y_1086_ = v___y_1098_;
v___y_1087_ = v___y_1099_;
v___y_1088_ = v___y_1101_;
v___y_1089_ = v___y_1100_;
v___y_1090_ = v___y_1095_;
goto v___jp_1083_;
}
else
{
v___y_1084_ = v___y_1097_;
v___y_1085_ = v___y_1096_;
v___y_1086_ = v___y_1098_;
v___y_1087_ = v___y_1099_;
v___y_1088_ = v___y_1101_;
v___y_1089_ = v___y_1100_;
v___y_1090_ = v___y_1096_;
goto v___jp_1083_;
}
}
v___jp_1104_:
{
uint64_t v___x_1109_; uint8_t v___x_1110_; 
v___x_1109_ = 0ULL;
v___x_1110_ = lean_uint64_dec_eq(v___y_1105_, v___x_1109_);
if (v___x_1110_ == 0)
{
uint64_t v___x_1111_; uint64_t v___x_1112_; uint8_t v___x_1113_; 
v___x_1111_ = 32ULL;
v___x_1112_ = lean_uint64_shift_right(v___y_1105_, v___x_1111_);
v___x_1113_ = lean_uint64_dec_eq(v___x_1112_, v___x_1109_);
if (v___x_1113_ == 0)
{
v___y_1095_ = v___x_1111_;
v___y_1096_ = v___x_1109_;
v___y_1097_ = v___y_1105_;
v___y_1098_ = v___y_1106_;
v___y_1099_ = v___y_1107_;
v___y_1100_ = v___y_1108_;
v___y_1101_ = v___x_1112_;
goto v___jp_1094_;
}
else
{
v___y_1095_ = v___x_1111_;
v___y_1096_ = v___x_1109_;
v___y_1097_ = v___y_1105_;
v___y_1098_ = v___y_1106_;
v___y_1099_ = v___y_1107_;
v___y_1100_ = v___y_1108_;
v___y_1101_ = v___y_1105_;
goto v___jp_1094_;
}
}
else
{
if (v___y_1107_ == 0)
{
uint32_t v___x_1114_; 
v___x_1114_ = 0;
return v___x_1114_;
}
else
{
uint32_t v___x_1115_; 
v___x_1115_ = 2147483648;
return v___x_1115_;
}
}
}
v___jp_1116_:
{
uint64_t v___x_1123_; uint64_t v___x_1124_; uint64_t v___x_1125_; uint8_t v___x_1126_; 
v___x_1123_ = lean_uint64_mul(v___y_1117_, v___y_1119_);
v___x_1124_ = lean_uint64_add(v___y_1118_, v___y_1122_);
v___x_1125_ = 281474976710656ULL;
v___x_1126_ = lean_uint64_dec_lt(v___x_1123_, v___x_1125_);
if (v___x_1126_ == 0)
{
v___y_1105_ = v___x_1123_;
v___y_1106_ = v___x_1124_;
v___y_1107_ = v___y_1120_;
v___y_1108_ = v___y_1121_;
goto v___jp_1104_;
}
else
{
uint64_t v___x_1127_; uint8_t v___x_1128_; 
v___x_1127_ = 123ULL;
v___x_1128_ = lean_uint64_dec_le(v___x_1124_, v___x_1127_);
if (v___x_1128_ == 0)
{
v___y_1105_ = v___x_1123_;
v___y_1106_ = v___x_1124_;
v___y_1107_ = v___y_1120_;
v___y_1108_ = v___y_1121_;
goto v___jp_1104_;
}
else
{
uint64_t v___x_1129_; uint8_t v___x_1130_; 
v___x_1129_ = 0ULL;
v___x_1130_ = lean_uint64_dec_eq(v___x_1123_, v___x_1129_);
if (v___x_1130_ == 0)
{
uint64_t v___x_1131_; uint64_t v___x_1132_; uint8_t v___x_1133_; 
v___x_1131_ = 149ULL;
v___x_1132_ = lean_uint64_sub(v___x_1131_, v___x_1124_);
v___x_1133_ = lean_uint64_dec_eq(v___x_1132_, v___x_1129_);
if (v___x_1133_ == 0)
{
uint64_t v___x_1134_; uint8_t v___x_1135_; 
v___x_1134_ = 64ULL;
v___x_1135_ = lean_uint64_dec_lt(v___x_1132_, v___x_1134_);
if (v___x_1135_ == 0)
{
uint8_t v___x_1136_; 
v___x_1136_ = lean_uint64_dec_eq(v___x_1132_, v___x_1134_);
if (v___x_1136_ == 0)
{
v___y_748_ = v___x_1129_;
v___y_749_ = v___y_1120_;
v___y_750_ = v___y_1121_;
v___y_751_ = v___x_1129_;
goto v___jp_747_;
}
else
{
uint64_t v___x_1137_; uint8_t v___x_1138_; 
v___x_1137_ = 9223372036854775808ULL;
v___x_1138_ = lean_uint64_dec_lt(v___x_1137_, v___x_1123_);
if (v___x_1138_ == 0)
{
v___y_748_ = v___x_1129_;
v___y_749_ = v___y_1120_;
v___y_750_ = v___y_1121_;
v___y_751_ = v___x_1129_;
goto v___jp_747_;
}
else
{
uint64_t v___x_1139_; 
v___x_1139_ = 1ULL;
v___y_748_ = v___x_1129_;
v___y_749_ = v___y_1120_;
v___y_750_ = v___y_1121_;
v___y_751_ = v___x_1139_;
goto v___jp_747_;
}
}
}
else
{
uint64_t v_quotient_1140_; uint64_t v___x_1141_; uint64_t v___x_1142_; uint64_t v___x_1143_; uint64_t v_remainder_1144_; uint64_t v___x_1145_; uint64_t v_half_1146_; uint8_t v___x_1147_; 
v_quotient_1140_ = lean_uint64_shift_right(v___x_1123_, v___x_1132_);
v___x_1141_ = 1ULL;
v___x_1142_ = lean_uint64_shift_left(v___x_1141_, v___x_1132_);
v___x_1143_ = lean_uint64_sub(v___x_1142_, v___x_1141_);
v_remainder_1144_ = lean_uint64_land(v___x_1123_, v___x_1143_);
v___x_1145_ = lean_uint64_sub(v___x_1132_, v___x_1141_);
v_half_1146_ = lean_uint64_shift_left(v___x_1141_, v___x_1145_);
v___x_1147_ = lean_uint64_dec_lt(v_remainder_1144_, v_half_1146_);
if (v___x_1147_ == 0)
{
uint8_t v___x_1148_; 
v___x_1148_ = lean_uint64_dec_lt(v_half_1146_, v_remainder_1144_);
if (v___x_1148_ == 0)
{
uint64_t v___x_1149_; uint8_t v___x_1150_; 
v___x_1149_ = lean_uint64_land(v_quotient_1140_, v___x_1141_);
v___x_1150_ = lean_uint64_dec_eq(v___x_1149_, v___x_1129_);
if (v___x_1150_ == 0)
{
uint64_t v___x_1151_; 
v___x_1151_ = lean_uint64_add(v_quotient_1140_, v___x_1141_);
v___y_748_ = v___x_1129_;
v___y_749_ = v___y_1120_;
v___y_750_ = v___y_1121_;
v___y_751_ = v___x_1151_;
goto v___jp_747_;
}
else
{
v___y_748_ = v___x_1129_;
v___y_749_ = v___y_1120_;
v___y_750_ = v___y_1121_;
v___y_751_ = v_quotient_1140_;
goto v___jp_747_;
}
}
else
{
uint64_t v___x_1152_; 
v___x_1152_ = lean_uint64_add(v_quotient_1140_, v___x_1141_);
v___y_748_ = v___x_1129_;
v___y_749_ = v___y_1120_;
v___y_750_ = v___y_1121_;
v___y_751_ = v___x_1152_;
goto v___jp_747_;
}
}
else
{
v___y_748_ = v___x_1129_;
v___y_749_ = v___y_1120_;
v___y_750_ = v___y_1121_;
v___y_751_ = v_quotient_1140_;
goto v___jp_747_;
}
}
}
else
{
v___y_748_ = v___x_1129_;
v___y_749_ = v___y_1120_;
v___y_750_ = v___y_1121_;
v___y_751_ = v___x_1123_;
goto v___jp_747_;
}
}
else
{
if (v___y_1120_ == 0)
{
uint32_t v___x_1153_; 
v___x_1153_ = 0;
return v___x_1153_;
}
else
{
uint32_t v___x_1154_; 
v___x_1154_ = 2147483648;
return v___x_1154_;
}
}
}
}
}
v___jp_1158_:
{
uint64_t v___x_1164_; uint64_t v___x_1165_; uint8_t v___x_1166_; 
v___x_1164_ = lean_uint32_to_uint64(v_ey_1157_);
v___x_1165_ = 0ULL;
v___x_1166_ = lean_uint64_dec_eq(v___x_1164_, v___x_1165_);
if (v___x_1166_ == 0)
{
uint64_t v___x_1167_; uint64_t v___x_1168_; 
v___x_1167_ = 1ULL;
v___x_1168_ = lean_uint64_sub(v___x_1164_, v___x_1167_);
v___y_1117_ = v___y_1159_;
v___y_1118_ = v___y_1163_;
v___y_1119_ = v___y_1160_;
v___y_1120_ = v___y_1161_;
v___y_1121_ = v___y_1162_;
v___y_1122_ = v___x_1168_;
goto v___jp_1116_;
}
else
{
v___y_1117_ = v___y_1159_;
v___y_1118_ = v___y_1163_;
v___y_1119_ = v___y_1160_;
v___y_1120_ = v___y_1161_;
v___y_1121_ = v___y_1162_;
v___y_1122_ = v___x_1165_;
goto v___jp_1116_;
}
}
v___jp_1169_:
{
uint64_t v___x_1174_; uint64_t v___x_1175_; uint8_t v___x_1176_; 
v___x_1174_ = lean_uint32_to_uint64(v_ex_1155_);
v___x_1175_ = 0ULL;
v___x_1176_ = lean_uint64_dec_eq(v___x_1174_, v___x_1175_);
if (v___x_1176_ == 0)
{
uint64_t v___x_1177_; uint64_t v___x_1178_; 
v___x_1177_ = 1ULL;
v___x_1178_ = lean_uint64_sub(v___x_1174_, v___x_1177_);
v___y_1159_ = v___y_1170_;
v___y_1160_ = v___y_1173_;
v___y_1161_ = v___y_1171_;
v___y_1162_ = v___y_1172_;
v___y_1163_ = v___x_1178_;
goto v___jp_1158_;
}
else
{
v___y_1159_ = v___y_1170_;
v___y_1160_ = v___y_1173_;
v___y_1161_ = v___y_1171_;
v___y_1162_ = v___y_1172_;
v___y_1163_ = v___x_1175_;
goto v___jp_1158_;
}
}
v___jp_1179_:
{
uint32_t v___x_1184_; uint8_t v___x_1185_; 
v___x_1184_ = 0;
v___x_1185_ = lean_uint32_dec_eq(v_ey_1157_, v___x_1184_);
if (v___x_1185_ == 0)
{
uint64_t v___x_1186_; uint64_t v___x_1187_; uint64_t v___x_1188_; 
v___x_1186_ = lean_uint32_to_uint64(v___y_1181_);
v___x_1187_ = 8388608ULL;
v___x_1188_ = lean_uint64_lor(v___x_1186_, v___x_1187_);
v___y_1170_ = v___y_1183_;
v___y_1171_ = v___y_1180_;
v___y_1172_ = v___y_1182_;
v___y_1173_ = v___x_1188_;
goto v___jp_1169_;
}
else
{
uint64_t v___x_1189_; 
v___x_1189_ = lean_uint32_to_uint64(v___y_1181_);
v___y_1170_ = v___y_1183_;
v___y_1171_ = v___y_1180_;
v___y_1172_ = v___y_1182_;
v___y_1173_ = v___x_1189_;
goto v___jp_1169_;
}
}
v___jp_1190_:
{
uint32_t v___x_1192_; uint32_t v_xFraction_1193_; uint32_t v_yFraction_1194_; uint32_t v___x_1195_; uint8_t v___x_1196_; 
v___x_1192_ = 8388607;
v_xFraction_1193_ = lean_uint32_land(v___y_710_, v___x_1192_);
v_yFraction_1194_ = lean_uint32_land(v___y_711_, v___x_1192_);
v___x_1195_ = 0;
v___x_1196_ = lean_uint32_dec_eq(v_ex_1155_, v___x_1195_);
if (v___x_1196_ == 0)
{
uint64_t v___x_1197_; uint64_t v___x_1198_; uint64_t v___x_1199_; 
v___x_1197_ = lean_uint32_to_uint64(v_xFraction_1193_);
v___x_1198_ = 8388608ULL;
v___x_1199_ = lean_uint64_lor(v___x_1197_, v___x_1198_);
v___y_1180_ = v___y_1191_;
v___y_1181_ = v_yFraction_1194_;
v___y_1182_ = v___x_1192_;
v___y_1183_ = v___x_1199_;
goto v___jp_1179_;
}
else
{
uint64_t v___x_1200_; 
v___x_1200_ = lean_uint32_to_uint64(v_xFraction_1193_);
v___y_1180_ = v___y_1191_;
v___y_1181_ = v_yFraction_1194_;
v___y_1182_ = v___x_1192_;
v___y_1183_ = v___x_1200_;
goto v___jp_1179_;
}
}
v___jp_1204_:
{
if (v___y_1206_ == 0)
{
v___y_1191_ = v___x_1203_;
goto v___jp_1190_;
}
else
{
v___y_1191_ = v___y_1205_;
goto v___jp_1190_;
}
}
v___jp_1207_:
{
if (v___y_1208_ == 0)
{
if (v___y_1210_ == 0)
{
v___y_1205_ = v___y_1209_;
v___y_1206_ = v___x_1203_;
goto v___jp_1204_;
}
else
{
v___y_1191_ = v___x_1203_;
goto v___jp_1190_;
}
}
else
{
v___y_1205_ = v___y_1209_;
v___y_1206_ = v___y_1210_;
goto v___jp_1204_;
}
}
v___jp_1211_:
{
uint32_t v___x_1214_; uint32_t v___x_1215_; uint32_t v___x_1216_; uint8_t v___x_1217_; 
v___x_1214_ = 2147483648;
v___x_1215_ = lean_uint32_land(v___y_711_, v___x_1214_);
v___x_1216_ = 0;
v___x_1217_ = lean_uint32_dec_eq(v___x_1215_, v___x_1216_);
if (v___x_1217_ == 0)
{
v___y_1208_ = v___y_1213_;
v___y_1209_ = v___y_1212_;
v___y_1210_ = v___x_1203_;
goto v___jp_1207_;
}
else
{
v___y_1208_ = v___y_1213_;
v___y_1209_ = v___y_1212_;
v___y_1210_ = v___y_1212_;
goto v___jp_1207_;
}
}
v___jp_1218_:
{
if (v___y_1219_ == 0)
{
uint32_t v___x_1220_; uint32_t v___x_1221_; uint32_t v___x_1222_; uint8_t v___x_1223_; 
v___x_1220_ = 2147483648;
v___x_1221_ = lean_uint32_land(v___y_710_, v___x_1220_);
v___x_1222_ = 0;
v___x_1223_ = lean_uint32_dec_eq(v___x_1221_, v___x_1222_);
if (v___x_1223_ == 0)
{
v___y_1212_ = v___y_1219_;
v___y_1213_ = v___x_1203_;
goto v___jp_1211_;
}
else
{
v___y_1212_ = v___y_1219_;
v___y_1213_ = v___y_1219_;
goto v___jp_1211_;
}
}
else
{
lean_object* v___x_1224_; lean_object* v___x_1225_; lean_object* v___x_1226_; uint32_t v___x_1227_; 
v___x_1224_ = lean_uint32_to_nat(v___y_710_);
v___x_1225_ = lean_uint32_to_nat(v___y_711_);
v___x_1226_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1224_, v___x_1225_);
v___x_1227_ = lean_uint32_of_nat(v___x_1226_);
lean_dec(v___x_1226_);
return v___x_1227_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_runFar___lam__1___boxed(lean_object* v___y_1242_, lean_object* v___y_1243_){
_start:
{
uint32_t v___y_1689__boxed_1244_; uint32_t v___y_1690__boxed_1245_; uint32_t v_res_1246_; lean_object* v_r_1247_; 
v___y_1689__boxed_1244_ = lean_unbox_uint32(v___y_1242_);
lean_dec(v___y_1242_);
v___y_1690__boxed_1245_ = lean_unbox_uint32(v___y_1243_);
lean_dec(v___y_1243_);
v_res_1246_ = lp_competition_runFar___lam__1(v___y_1689__boxed_1244_, v___y_1690__boxed_1245_);
v_r_1247_ = lean_box_uint32(v_res_1246_);
return v_r_1247_;
}
}
LEAN_EXPORT lean_object* lp_competition_runFar(){
_start:
{
lean_object* v___f_1251_; lean_object* v___f_1252_; lean_object* v___x_1253_; lean_object* v___x_1254_; lean_object* v___x_1255_; 
v___f_1251_ = ((lean_object*)(lp_competition_runFar___closed__0));
v___f_1252_ = ((lean_object*)(lp_competition_runFar___closed__1));
v___x_1253_ = ((lean_object*)(lp_competition_runControl___closed__2));
v___x_1254_ = ((lean_object*)(lp_competition_runControl___closed__3));
v___x_1255_ = lp_competition_Bench_Suite_run(v___f_1251_, v___f_1252_, v___x_1253_, v___x_1254_);
return v___x_1255_;
}
}
LEAN_EXPORT lean_object* lp_competition_runFar___boxed(lean_object* v_a_1256_){
_start:
{
lean_object* v_res_1257_; 
v_res_1257_ = lp_competition_runFar();
return v_res_1257_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1269_; lean_object* v___x_1270_; lean_object* v___x_1271_; uint8_t v___x_1272_; 
v___x_1269_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1270_ = lean_io_getenv(v___x_1269_);
v___x_1271_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1272_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1270_, v___x_1271_);
if (v___x_1272_ == 0)
{
lean_object* v___x_1273_; uint8_t v___x_1274_; 
v___x_1273_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1274_ = l_Option_instBEq_beq___at___00Lean_Server_moduleFromDocumentUri_spec__0(v___x_1270_, v___x_1273_);
lean_dec(v___x_1270_);
if (v___x_1274_ == 0)
{
lean_object* v___x_1275_; lean_object* v___x_1276_; 
v___x_1275_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_1276_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1276_, 0, v___x_1275_);
return v___x_1276_;
}
else
{
lean_object* v___x_1277_; 
v___x_1277_ = lp_competition_runFar();
return v___x_1277_;
}
}
else
{
lean_object* v___x_1278_; 
lean_dec(v___x_1270_);
v___x_1278_ = lp_competition_runControl();
return v___x_1278_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1279_){
_start:
{
lean_object* v_res_1280_; 
v_res_1280_ = _lean_main();
return v_res_1280_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R22FarStaticCostMain(uint8_t builtin) {
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
  res = initialize_competition_R22FarStaticCostMain(1 /* builtin */);
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
