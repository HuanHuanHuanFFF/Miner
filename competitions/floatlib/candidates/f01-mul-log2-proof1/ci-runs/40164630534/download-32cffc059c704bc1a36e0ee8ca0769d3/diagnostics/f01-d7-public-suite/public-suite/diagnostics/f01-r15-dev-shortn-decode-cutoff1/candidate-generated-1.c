// Lean compiler output
// Module: MainFull
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
lean_object* lean_io_getenv(lean_object*);
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
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_runFull(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "BENCH_PLAN"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_closure_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_closure_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_closure_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_closure_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_closure_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__3___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
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
uint32_t v___y_4667__boxed_126_; uint32_t v___y_4668__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_4667__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_4668__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_main___lam__0(v___y_4667__boxed_126_, v___y_4668__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_130_, uint32_t v___y_131_){
_start:
{
uint8_t v___y_133_; uint8_t v___y_149_; uint8_t v___y_163_; uint8_t v___y_180_; float v___y_187_; float v___y_188_; float v___y_202_; uint8_t v___y_203_; float v___y_218_; uint32_t v___y_228_; uint32_t v___y_232_; uint32_t v___y_236_; uint32_t v___y_237_; uint32_t v___y_238_; uint64_t v___y_242_; uint8_t v___y_243_; uint32_t v___y_244_; uint64_t v___y_245_; uint32_t v___y_257_; uint32_t v___y_258_; uint32_t v___y_259_; uint8_t v___y_263_; uint64_t v___y_264_; uint32_t v___y_265_; uint64_t v___y_266_; uint8_t v___y_278_; uint8_t v___y_279_; uint32_t v___x_284_; uint32_t v___x_285_; uint8_t v___y_287_; uint32_t v___x_299_; uint32_t v___y_301_; uint32_t v___y_302_; uint32_t v___y_303_; uint32_t v___y_304_; uint32_t v___y_311_; uint8_t v___y_312_; uint32_t v___y_313_; uint32_t v___y_314_; uint64_t v___y_318_; uint64_t v___y_319_; uint8_t v___y_320_; uint32_t v___y_321_; uint64_t v___y_322_; uint8_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint8_t v___y_335_; uint32_t v___y_336_; uint64_t v___y_337_; uint64_t v___y_344_; uint64_t v___y_345_; uint8_t v___y_346_; uint32_t v___y_347_; uint64_t v___y_348_; uint64_t v___y_354_; uint64_t v___y_355_; uint8_t v___y_356_; uint64_t v___y_357_; uint32_t v___y_358_; uint64_t v___y_359_; uint64_t v___y_414_; uint64_t v___y_415_; uint8_t v___y_416_; uint64_t v___y_417_; uint64_t v___y_418_; uint32_t v___y_419_; uint64_t v___y_420_; uint64_t v___y_426_; uint64_t v___y_427_; uint64_t v___y_428_; uint8_t v___y_429_; uint64_t v___y_430_; uint64_t v___y_431_; uint32_t v___y_432_; uint64_t v___y_433_; uint64_t v___y_434_; uint64_t v___y_439_; uint64_t v___y_440_; uint8_t v___y_441_; uint64_t v___y_442_; uint64_t v___y_443_; uint32_t v___y_444_; uint64_t v___y_445_; uint64_t v___y_450_; uint64_t v___y_451_; uint64_t v___y_452_; uint64_t v___y_453_; uint64_t v___y_454_; uint8_t v___y_455_; uint64_t v___y_456_; uint32_t v___y_457_; uint64_t v___y_458_; uint64_t v___y_463_; uint64_t v___y_464_; uint64_t v___y_465_; uint8_t v___y_466_; uint64_t v___y_467_; uint32_t v___y_468_; uint64_t v___y_469_; uint64_t v___y_474_; uint64_t v___y_475_; uint64_t v___y_476_; uint64_t v___y_477_; uint64_t v___y_478_; uint8_t v___y_479_; uint64_t v___y_480_; uint32_t v___y_481_; uint64_t v___y_482_; uint64_t v___y_487_; uint64_t v___y_488_; uint64_t v___y_489_; uint8_t v___y_490_; uint64_t v___y_491_; uint32_t v___y_492_; uint64_t v___y_493_; uint64_t v___y_498_; uint64_t v___y_499_; uint8_t v___y_500_; uint64_t v___y_501_; uint64_t v___y_502_; uint64_t v___y_503_; uint64_t v___y_504_; uint32_t v___y_505_; uint64_t v___y_506_; uint64_t v___y_511_; uint64_t v___y_512_; uint8_t v___y_513_; uint64_t v___y_514_; uint64_t v___y_515_; uint32_t v___y_516_; uint64_t v___y_517_; uint64_t v___y_522_; uint64_t v___y_523_; uint64_t v___y_524_; uint8_t v___y_525_; uint64_t v___y_526_; uint32_t v___y_527_; uint64_t v___y_528_; uint64_t v___y_532_; uint8_t v___y_533_; uint64_t v___y_534_; uint32_t v___y_535_; uint64_t v___y_544_; uint64_t v___y_545_; uint8_t v___y_546_; uint32_t v___y_547_; uint64_t v___y_548_; uint64_t v___y_549_; uint32_t v_ex_582_; uint32_t v___x_583_; uint32_t v_ey_584_; uint64_t v___y_586_; uint8_t v___y_587_; uint32_t v___y_588_; uint64_t v___y_589_; uint64_t v___y_590_; uint8_t v___y_597_; uint32_t v___y_598_; uint64_t v___y_599_; uint64_t v___y_600_; uint32_t v___y_607_; uint8_t v___y_608_; uint32_t v___y_609_; uint64_t v___y_610_; uint8_t v___y_618_; uint32_t v___x_628_; uint32_t v___x_629_; uint8_t v___x_630_; uint8_t v___y_632_; uint8_t v___y_633_; uint8_t v___y_635_; uint8_t v___y_636_; uint8_t v___y_637_; uint8_t v___y_639_; uint8_t v___y_640_; uint8_t v___y_646_; 
v___x_284_ = 23;
v___x_285_ = lean_uint32_shift_right(v___y_130_, v___x_284_);
v___x_299_ = 255;
v_ex_582_ = lean_uint32_land(v___x_285_, v___x_299_);
v___x_583_ = lean_uint32_shift_right(v___y_131_, v___x_284_);
v_ey_584_ = lean_uint32_land(v___x_583_, v___x_299_);
v___x_628_ = lean_uint32_add(v_ex_582_, v_ey_584_);
v___x_629_ = 128;
v___x_630_ = lean_uint32_dec_lt(v___x_628_, v___x_629_);
if (v___x_630_ == 0)
{
uint32_t v___x_655_; uint32_t v_a_656_; uint32_t v___x_657_; uint32_t v___x_658_; uint32_t v___x_659_; uint8_t v___x_660_; 
v___x_655_ = 2147483647;
v_a_656_ = lean_uint32_land(v___y_130_, v___x_655_);
v___x_657_ = 201326591;
v___x_658_ = 1;
v___x_659_ = lean_uint32_sub(v_a_656_, v___x_658_);
v___x_660_ = lean_uint32_dec_le(v___x_657_, v___x_659_);
if (v___x_660_ == 0)
{
v___y_287_ = v___x_660_;
goto v___jp_286_;
}
else
{
uint32_t v___x_661_; uint8_t v___x_662_; 
v___x_661_ = 2139095040;
v___x_662_ = lean_uint32_dec_lt(v_a_656_, v___x_661_);
v___y_287_ = v___x_662_;
goto v___jp_286_;
}
}
else
{
uint32_t v___x_663_; uint8_t v___x_664_; uint8_t v___y_666_; 
v___x_663_ = 84;
v___x_664_ = lean_uint32_dec_le(v___x_628_, v___x_663_);
if (v___x_664_ == 0)
{
uint32_t v___x_672_; uint32_t v___x_673_; uint32_t v___x_674_; uint8_t v___x_675_; 
v___x_672_ = 4278190080;
v___x_673_ = 1;
v___x_674_ = lean_uint32_shift_left(v___y_130_, v___x_673_);
v___x_675_ = lean_uint32_dec_le(v___x_672_, v___x_674_);
if (v___x_675_ == 0)
{
uint32_t v___x_676_; uint8_t v___x_677_; 
v___x_676_ = lean_uint32_shift_left(v___y_131_, v___x_673_);
v___x_677_ = lean_uint32_dec_le(v___x_672_, v___x_676_);
v___y_646_ = v___x_677_;
goto v___jp_645_;
}
else
{
v___y_646_ = v___x_675_;
goto v___jp_645_;
}
}
else
{
uint32_t v___x_678_; uint32_t v___x_679_; uint32_t v___x_680_; uint8_t v___x_681_; 
v___x_678_ = 2147483648;
v___x_679_ = lean_uint32_land(v___y_130_, v___x_678_);
v___x_680_ = 0;
v___x_681_ = lean_uint32_dec_eq(v___x_679_, v___x_680_);
if (v___x_681_ == 0)
{
v___y_666_ = v___x_664_;
goto v___jp_665_;
}
else
{
uint8_t v___x_682_; 
v___x_682_ = 0;
v___y_666_ = v___x_682_;
goto v___jp_665_;
}
}
v___jp_665_:
{
uint32_t v___x_667_; uint32_t v___x_668_; uint32_t v___x_669_; uint8_t v___x_670_; 
v___x_667_ = 2147483648;
v___x_668_ = lean_uint32_land(v___y_131_, v___x_667_);
v___x_669_ = 0;
v___x_670_ = lean_uint32_dec_eq(v___x_668_, v___x_669_);
if (v___x_670_ == 0)
{
v___y_278_ = v___y_666_;
v___y_279_ = v___x_664_;
goto v___jp_277_;
}
else
{
uint8_t v___x_671_; 
v___x_671_ = 0;
v___y_278_ = v___y_666_;
v___y_279_ = v___x_671_;
goto v___jp_277_;
}
}
}
v___jp_132_:
{
if (v___y_133_ == 0)
{
uint32_t v___x_134_; 
v___x_134_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_134_;
}
else
{
uint32_t v___x_135_; uint32_t v___x_136_; 
v___x_135_ = 4194304;
v___x_136_ = lean_uint32_lor(v___y_131_, v___x_135_);
return v___x_136_;
}
}
v___jp_137_:
{
uint32_t v___x_138_; uint32_t v___x_139_; uint32_t v___x_140_; uint32_t v___x_141_; uint8_t v___x_142_; 
v___x_138_ = 23;
v___x_139_ = lean_uint32_shift_right(v___y_131_, v___x_138_);
v___x_140_ = 255;
v___x_141_ = lean_uint32_land(v___x_139_, v___x_140_);
v___x_142_ = lean_uint32_dec_eq(v___x_141_, v___x_140_);
if (v___x_142_ == 0)
{
v___y_133_ = v___x_142_;
goto v___jp_132_;
}
else
{
uint32_t v___x_143_; uint32_t v___x_144_; uint32_t v___x_145_; uint8_t v___x_146_; 
v___x_143_ = 8388607;
v___x_144_ = lean_uint32_land(v___y_131_, v___x_143_);
v___x_145_ = 0;
v___x_146_ = lean_uint32_dec_eq(v___x_144_, v___x_145_);
if (v___x_146_ == 0)
{
v___y_133_ = v___x_142_;
goto v___jp_132_;
}
else
{
uint32_t v___x_147_; 
v___x_147_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_147_;
}
}
}
v___jp_148_:
{
if (v___y_149_ == 0)
{
goto v___jp_137_;
}
else
{
uint32_t v___x_150_; uint32_t v___x_151_; 
v___x_150_ = 4194304;
v___x_151_ = lean_uint32_lor(v___y_130_, v___x_150_);
return v___x_151_;
}
}
v___jp_152_:
{
uint32_t v___x_153_; uint32_t v___x_154_; uint32_t v___x_155_; uint32_t v___x_156_; uint8_t v___x_157_; 
v___x_153_ = 23;
v___x_154_ = lean_uint32_shift_right(v___y_130_, v___x_153_);
v___x_155_ = 255;
v___x_156_ = lean_uint32_land(v___x_154_, v___x_155_);
v___x_157_ = lean_uint32_dec_eq(v___x_156_, v___x_155_);
if (v___x_157_ == 0)
{
v___y_149_ = v___x_157_;
goto v___jp_148_;
}
else
{
uint32_t v___x_158_; uint32_t v___x_159_; uint32_t v___x_160_; uint8_t v___x_161_; 
v___x_158_ = 8388607;
v___x_159_ = lean_uint32_land(v___y_130_, v___x_158_);
v___x_160_ = 0;
v___x_161_ = lean_uint32_dec_eq(v___x_159_, v___x_160_);
if (v___x_161_ == 0)
{
v___y_149_ = v___x_157_;
goto v___jp_148_;
}
else
{
goto v___jp_137_;
}
}
}
v___jp_162_:
{
if (v___y_163_ == 0)
{
goto v___jp_152_;
}
else
{
uint32_t v___x_164_; uint32_t v___x_165_; uint32_t v___x_166_; uint8_t v___x_167_; 
v___x_164_ = 4194304;
v___x_165_ = lean_uint32_land(v___y_131_, v___x_164_);
v___x_166_ = 0;
v___x_167_ = lean_uint32_dec_eq(v___x_165_, v___x_166_);
if (v___x_167_ == 0)
{
goto v___jp_152_;
}
else
{
uint32_t v___x_168_; 
v___x_168_ = lean_uint32_lor(v___y_131_, v___x_164_);
return v___x_168_;
}
}
}
v___jp_169_:
{
uint32_t v___x_170_; uint32_t v___x_171_; uint32_t v___x_172_; uint32_t v___x_173_; uint8_t v___x_174_; 
v___x_170_ = 23;
v___x_171_ = lean_uint32_shift_right(v___y_131_, v___x_170_);
v___x_172_ = 255;
v___x_173_ = lean_uint32_land(v___x_171_, v___x_172_);
v___x_174_ = lean_uint32_dec_eq(v___x_173_, v___x_172_);
if (v___x_174_ == 0)
{
v___y_163_ = v___x_174_;
goto v___jp_162_;
}
else
{
uint32_t v___x_175_; uint32_t v___x_176_; uint32_t v___x_177_; uint8_t v___x_178_; 
v___x_175_ = 8388607;
v___x_176_ = lean_uint32_land(v___y_131_, v___x_175_);
v___x_177_ = 0;
v___x_178_ = lean_uint32_dec_eq(v___x_176_, v___x_177_);
if (v___x_178_ == 0)
{
v___y_163_ = v___x_174_;
goto v___jp_162_;
}
else
{
goto v___jp_152_;
}
}
}
v___jp_179_:
{
if (v___y_180_ == 0)
{
goto v___jp_169_;
}
else
{
uint32_t v___x_181_; uint32_t v___x_182_; uint32_t v___x_183_; uint8_t v___x_184_; 
v___x_181_ = 4194304;
v___x_182_ = lean_uint32_land(v___y_130_, v___x_181_);
v___x_183_ = 0;
v___x_184_ = lean_uint32_dec_eq(v___x_182_, v___x_183_);
if (v___x_184_ == 0)
{
goto v___jp_169_;
}
else
{
uint32_t v___x_185_; 
v___x_185_ = lean_uint32_lor(v___y_130_, v___x_181_);
return v___x_185_;
}
}
}
v___jp_186_:
{
float v_result_189_; uint8_t v___x_190_; 
v_result_189_ = lean_float32_mul(v___y_187_, v___y_188_);
v___x_190_ = lean_float32_beq(v_result_189_, v_result_189_);
if (v___x_190_ == 0)
{
uint32_t v___x_191_; uint32_t v___x_192_; uint32_t v___x_193_; uint32_t v___x_194_; uint8_t v___x_195_; 
v___x_191_ = 23;
v___x_192_ = lean_uint32_shift_right(v___y_130_, v___x_191_);
v___x_193_ = 255;
v___x_194_ = lean_uint32_land(v___x_192_, v___x_193_);
v___x_195_ = lean_uint32_dec_eq(v___x_194_, v___x_193_);
if (v___x_195_ == 0)
{
v___y_180_ = v___x_195_;
goto v___jp_179_;
}
else
{
uint32_t v___x_196_; uint32_t v___x_197_; uint32_t v___x_198_; uint8_t v___x_199_; 
v___x_196_ = 8388607;
v___x_197_ = lean_uint32_land(v___y_130_, v___x_196_);
v___x_198_ = 0;
v___x_199_ = lean_uint32_dec_eq(v___x_197_, v___x_198_);
if (v___x_199_ == 0)
{
v___y_180_ = v___x_195_;
goto v___jp_179_;
}
else
{
goto v___jp_169_;
}
}
}
else
{
uint32_t v___x_200_; 
v___x_200_ = lean_float32_to_bits(v_result_189_);
return v___x_200_;
}
}
v___jp_201_:
{
if (v___y_203_ == 0)
{
float v___x_204_; 
v___x_204_ = lean_float32_of_bits(v___y_131_);
v___y_187_ = v___y_202_;
v___y_188_ = v___x_204_;
goto v___jp_186_;
}
else
{
uint32_t v___x_205_; uint32_t v___x_206_; uint32_t v___x_207_; uint32_t v___x_208_; float v___x_209_; lean_object* v___x_210_; uint32_t v___x_211_; uint32_t v___x_212_; lean_object* v___x_213_; lean_object* v___x_214_; float v___x_215_; float v___x_216_; 
v___x_205_ = 8388607;
v___x_206_ = lean_uint32_land(v___y_131_, v___x_205_);
v___x_207_ = 8388608;
v___x_208_ = lean_uint32_lor(v___x_206_, v___x_207_);
v___x_209_ = lean_uint32_to_float32(v___x_208_);
v___x_210_ = lp_competition_R2W01b_scaleTable;
v___x_211_ = 23;
v___x_212_ = lean_uint32_shift_right(v___y_131_, v___x_211_);
v___x_213_ = lean_uint32_to_nat(v___x_212_);
v___x_214_ = lean_array_fget_borrowed(v___x_210_, v___x_213_);
lean_dec(v___x_213_);
v___x_215_ = lean_unbox_float32(v___x_214_);
v___x_216_ = lean_float32_mul(v___x_209_, v___x_215_);
v___y_187_ = v___y_202_;
v___y_188_ = v___x_216_;
goto v___jp_186_;
}
}
v___jp_217_:
{
uint32_t v___x_219_; uint32_t v_a_220_; uint32_t v___x_221_; uint32_t v___x_222_; uint32_t v___x_223_; uint8_t v___x_224_; 
v___x_219_ = 2147483647;
v_a_220_ = lean_uint32_land(v___y_131_, v___x_219_);
v___x_221_ = 201326591;
v___x_222_ = 1;
v___x_223_ = lean_uint32_sub(v_a_220_, v___x_222_);
v___x_224_ = lean_uint32_dec_le(v___x_221_, v___x_223_);
if (v___x_224_ == 0)
{
v___y_202_ = v___y_218_;
v___y_203_ = v___x_224_;
goto v___jp_201_;
}
else
{
uint32_t v___x_225_; uint8_t v___x_226_; 
v___x_225_ = 2139095040;
v___x_226_ = lean_uint32_dec_lt(v_a_220_, v___x_225_);
v___y_202_ = v___y_218_;
v___y_203_ = v___x_226_;
goto v___jp_201_;
}
}
v___jp_227_:
{
uint32_t v___x_229_; uint32_t v___x_230_; 
v___x_229_ = 8388608;
v___x_230_ = lean_uint32_lor(v___y_228_, v___x_229_);
return v___x_230_;
}
v___jp_231_:
{
uint32_t v___x_233_; uint32_t v___x_234_; 
v___x_233_ = 8388608;
v___x_234_ = lean_uint32_lor(v___y_232_, v___x_233_);
return v___x_234_;
}
v___jp_235_:
{
uint32_t v___x_239_; uint32_t v___x_240_; 
v___x_239_ = lean_uint32_land(v___y_236_, v___y_237_);
v___x_240_ = lean_uint32_lor(v___y_238_, v___x_239_);
return v___x_240_;
}
v___jp_241_:
{
uint8_t v___x_246_; 
v___x_246_ = lean_uint64_dec_eq(v___y_245_, v___y_242_);
if (v___x_246_ == 0)
{
uint64_t v___x_247_; uint8_t v___x_248_; 
v___x_247_ = 8388608ULL;
v___x_248_ = lean_uint64_dec_eq(v___y_245_, v___x_247_);
if (v___x_248_ == 0)
{
uint32_t v___x_249_; 
v___x_249_ = lean_uint64_to_uint32(v___y_245_);
if (v___y_243_ == 0)
{
uint32_t v___x_250_; 
v___x_250_ = 0;
v___y_236_ = v___x_249_;
v___y_237_ = v___y_244_;
v___y_238_ = v___x_250_;
goto v___jp_235_;
}
else
{
uint32_t v___x_251_; 
v___x_251_ = 2147483648;
v___y_236_ = v___x_249_;
v___y_237_ = v___y_244_;
v___y_238_ = v___x_251_;
goto v___jp_235_;
}
}
else
{
if (v___y_243_ == 0)
{
uint32_t v___x_252_; 
v___x_252_ = 0;
v___y_228_ = v___x_252_;
goto v___jp_227_;
}
else
{
uint32_t v___x_253_; 
v___x_253_ = 2147483648;
v___y_228_ = v___x_253_;
goto v___jp_227_;
}
}
}
else
{
if (v___y_243_ == 0)
{
uint32_t v___x_254_; 
v___x_254_ = 0;
return v___x_254_;
}
else
{
uint32_t v___x_255_; 
v___x_255_ = 2147483648;
return v___x_255_;
}
}
}
v___jp_256_:
{
uint32_t v___x_260_; uint32_t v___x_261_; 
v___x_260_ = lean_uint32_land(v___y_258_, v___y_257_);
v___x_261_ = lean_uint32_lor(v___y_259_, v___x_260_);
return v___x_261_;
}
v___jp_262_:
{
uint8_t v___x_267_; 
v___x_267_ = lean_uint64_dec_eq(v___y_266_, v___y_264_);
if (v___x_267_ == 0)
{
uint64_t v___x_268_; uint8_t v___x_269_; 
v___x_268_ = 8388608ULL;
v___x_269_ = lean_uint64_dec_eq(v___y_266_, v___x_268_);
if (v___x_269_ == 0)
{
uint32_t v___x_270_; 
v___x_270_ = lean_uint64_to_uint32(v___y_266_);
if (v___y_263_ == 0)
{
uint32_t v___x_271_; 
v___x_271_ = 0;
v___y_257_ = v___y_265_;
v___y_258_ = v___x_270_;
v___y_259_ = v___x_271_;
goto v___jp_256_;
}
else
{
uint32_t v___x_272_; 
v___x_272_ = 2147483648;
v___y_257_ = v___y_265_;
v___y_258_ = v___x_270_;
v___y_259_ = v___x_272_;
goto v___jp_256_;
}
}
else
{
if (v___y_263_ == 0)
{
uint32_t v___x_273_; 
v___x_273_ = 0;
v___y_232_ = v___x_273_;
goto v___jp_231_;
}
else
{
uint32_t v___x_274_; 
v___x_274_ = 2147483648;
v___y_232_ = v___x_274_;
goto v___jp_231_;
}
}
}
else
{
if (v___y_263_ == 0)
{
uint32_t v___x_275_; 
v___x_275_ = 0;
return v___x_275_;
}
else
{
uint32_t v___x_276_; 
v___x_276_ = 2147483648;
return v___x_276_;
}
}
}
v___jp_277_:
{
if (v___y_278_ == 0)
{
if (v___y_279_ == 0)
{
uint32_t v___x_280_; 
v___x_280_ = 0;
return v___x_280_;
}
else
{
uint32_t v___x_281_; 
v___x_281_ = 2147483648;
return v___x_281_;
}
}
else
{
if (v___y_279_ == 0)
{
uint32_t v___x_282_; 
v___x_282_ = 2147483648;
return v___x_282_;
}
else
{
uint32_t v___x_283_; 
v___x_283_ = 0;
return v___x_283_;
}
}
}
v___jp_286_:
{
if (v___y_287_ == 0)
{
float v___x_288_; 
v___x_288_ = lean_float32_of_bits(v___y_130_);
v___y_218_ = v___x_288_;
goto v___jp_217_;
}
else
{
uint32_t v___x_289_; uint32_t v___x_290_; uint32_t v___x_291_; uint32_t v___x_292_; float v___x_293_; lean_object* v___x_294_; lean_object* v___x_295_; lean_object* v___x_296_; float v___x_297_; float v___x_298_; 
v___x_289_ = 8388607;
v___x_290_ = lean_uint32_land(v___y_130_, v___x_289_);
v___x_291_ = 8388608;
v___x_292_ = lean_uint32_lor(v___x_290_, v___x_291_);
v___x_293_ = lean_uint32_to_float32(v___x_292_);
v___x_294_ = lp_competition_R2W01b_scaleTable;
v___x_295_ = lean_uint32_to_nat(v___x_285_);
v___x_296_ = lean_array_fget_borrowed(v___x_294_, v___x_295_);
lean_dec(v___x_295_);
v___x_297_ = lean_unbox_float32(v___x_296_);
v___x_298_ = lean_float32_mul(v___x_293_, v___x_297_);
v___y_218_ = v___x_298_;
goto v___jp_217_;
}
}
v___jp_300_:
{
uint32_t v___x_305_; uint32_t v___x_306_; uint32_t v___x_307_; uint32_t v___x_308_; uint32_t v___x_309_; 
v___x_305_ = lean_uint32_land(v___y_301_, v___x_299_);
v___x_306_ = lean_uint32_shift_left(v___x_305_, v___x_284_);
v___x_307_ = lean_uint32_lor(v___y_304_, v___x_306_);
v___x_308_ = lean_uint32_land(v___y_302_, v___y_303_);
v___x_309_ = lean_uint32_lor(v___x_307_, v___x_308_);
return v___x_309_;
}
v___jp_310_:
{
if (v___y_312_ == 0)
{
uint32_t v___x_315_; 
v___x_315_ = 0;
v___y_301_ = v___y_311_;
v___y_302_ = v___y_314_;
v___y_303_ = v___y_313_;
v___y_304_ = v___x_315_;
goto v___jp_300_;
}
else
{
uint32_t v___x_316_; 
v___x_316_ = 2147483648;
v___y_301_ = v___y_311_;
v___y_302_ = v___y_314_;
v___y_303_ = v___y_313_;
v___y_304_ = v___x_316_;
goto v___jp_300_;
}
}
v___jp_317_:
{
uint64_t v___x_323_; uint64_t v_encodedExponent_324_; uint32_t v___x_325_; uint64_t v___x_326_; uint8_t v___x_327_; 
v___x_323_ = 171ULL;
v_encodedExponent_324_ = lean_uint64_sub(v___y_319_, v___x_323_);
v___x_325_ = lean_uint64_to_uint32(v_encodedExponent_324_);
v___x_326_ = 8388608ULL;
v___x_327_ = lean_uint64_dec_lt(v___y_322_, v___x_326_);
if (v___x_327_ == 0)
{
uint64_t v___x_328_; uint32_t v___x_329_; 
v___x_328_ = lean_uint64_sub(v___y_322_, v___x_326_);
v___x_329_ = lean_uint64_to_uint32(v___x_328_);
v___y_311_ = v___x_325_;
v___y_312_ = v___y_320_;
v___y_313_ = v___y_321_;
v___y_314_ = v___x_329_;
goto v___jp_310_;
}
else
{
uint32_t v___x_330_; 
v___x_330_ = lean_uint64_to_uint32(v___y_318_);
v___y_311_ = v___x_325_;
v___y_312_ = v___y_320_;
v___y_313_ = v___y_321_;
v___y_314_ = v___x_330_;
goto v___jp_310_;
}
}
v___jp_331_:
{
uint64_t v___x_338_; uint8_t v___x_339_; 
v___x_338_ = 425ULL;
v___x_339_ = lean_uint64_dec_lt(v___x_338_, v___y_337_);
if (v___x_339_ == 0)
{
if (v___y_332_ == 0)
{
v___y_318_ = v___y_333_;
v___y_319_ = v___y_337_;
v___y_320_ = v___y_335_;
v___y_321_ = v___y_336_;
v___y_322_ = v___y_334_;
goto v___jp_317_;
}
else
{
uint64_t v___x_340_; 
v___x_340_ = 8388608ULL;
v___y_318_ = v___y_333_;
v___y_319_ = v___y_337_;
v___y_320_ = v___y_335_;
v___y_321_ = v___y_336_;
v___y_322_ = v___x_340_;
goto v___jp_317_;
}
}
else
{
if (v___y_335_ == 0)
{
uint32_t v___x_341_; 
v___x_341_ = 2139095040;
return v___x_341_;
}
else
{
uint32_t v___x_342_; 
v___x_342_ = 4286578688;
return v___x_342_;
}
}
}
v___jp_343_:
{
uint64_t v___x_349_; uint8_t v_carry_350_; 
v___x_349_ = 16777216ULL;
v_carry_350_ = lean_uint64_dec_eq(v___y_348_, v___x_349_);
if (v_carry_350_ == 0)
{
v___y_332_ = v_carry_350_;
v___y_333_ = v___y_344_;
v___y_334_ = v___y_348_;
v___y_335_ = v___y_346_;
v___y_336_ = v___y_347_;
v___y_337_ = v___y_345_;
goto v___jp_331_;
}
else
{
uint64_t v___x_351_; uint64_t v___x_352_; 
v___x_351_ = 1ULL;
v___x_352_ = lean_uint64_add(v___y_345_, v___x_351_);
v___y_332_ = v_carry_350_;
v___y_333_ = v___y_344_;
v___y_334_ = v___y_348_;
v___y_335_ = v___y_346_;
v___y_336_ = v___y_347_;
v___y_337_ = v___x_352_;
goto v___jp_331_;
}
}
v___jp_353_:
{
uint64_t v_position_360_; uint64_t v___x_361_; uint8_t v___x_362_; 
v_position_360_ = lean_uint64_add(v___y_359_, v___y_355_);
v___x_361_ = 172ULL;
v___x_362_ = lean_uint64_dec_lt(v_position_360_, v___x_361_);
if (v___x_362_ == 0)
{
uint64_t v___x_363_; uint8_t v___x_364_; 
v___x_363_ = 23ULL;
v___x_364_ = lean_uint64_dec_lt(v___y_359_, v___x_363_);
if (v___x_364_ == 0)
{
uint64_t v___x_365_; uint8_t v___x_366_; 
v___x_365_ = lean_uint64_sub(v___y_359_, v___x_363_);
v___x_366_ = lean_uint64_dec_eq(v___x_365_, v___y_354_);
if (v___x_366_ == 0)
{
uint64_t v___x_367_; uint8_t v___x_368_; 
v___x_367_ = 64ULL;
v___x_368_ = lean_uint64_dec_lt(v___x_365_, v___x_367_);
if (v___x_368_ == 0)
{
uint8_t v___x_369_; 
v___x_369_ = lean_uint64_dec_eq(v___x_365_, v___x_367_);
if (v___x_369_ == 0)
{
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v___y_354_;
goto v___jp_343_;
}
else
{
uint64_t v___x_370_; uint8_t v___x_371_; 
v___x_370_ = 9223372036854775808ULL;
v___x_371_ = lean_uint64_dec_lt(v___x_370_, v___y_357_);
if (v___x_371_ == 0)
{
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v___y_354_;
goto v___jp_343_;
}
else
{
uint64_t v___x_372_; 
v___x_372_ = 1ULL;
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v___x_372_;
goto v___jp_343_;
}
}
}
else
{
uint64_t v_quotient_373_; uint64_t v___x_374_; uint64_t v___x_375_; uint64_t v___x_376_; uint64_t v_remainder_377_; uint64_t v___x_378_; uint64_t v_half_379_; uint8_t v___x_380_; 
v_quotient_373_ = lean_uint64_shift_right(v___y_357_, v___x_365_);
v___x_374_ = 1ULL;
v___x_375_ = lean_uint64_shift_left(v___x_374_, v___x_365_);
v___x_376_ = lean_uint64_sub(v___x_375_, v___x_374_);
v_remainder_377_ = lean_uint64_land(v___y_357_, v___x_376_);
v___x_378_ = lean_uint64_sub(v___x_365_, v___x_374_);
v_half_379_ = lean_uint64_shift_left(v___x_374_, v___x_378_);
v___x_380_ = lean_uint64_dec_lt(v_remainder_377_, v_half_379_);
if (v___x_380_ == 0)
{
uint8_t v___x_381_; 
v___x_381_ = lean_uint64_dec_lt(v_half_379_, v_remainder_377_);
if (v___x_381_ == 0)
{
uint64_t v___x_382_; uint8_t v___x_383_; 
v___x_382_ = lean_uint64_land(v_quotient_373_, v___x_374_);
v___x_383_ = lean_uint64_dec_eq(v___x_382_, v___y_354_);
if (v___x_383_ == 0)
{
uint64_t v___x_384_; 
v___x_384_ = lean_uint64_add(v_quotient_373_, v___x_374_);
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v___x_384_;
goto v___jp_343_;
}
else
{
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v_quotient_373_;
goto v___jp_343_;
}
}
else
{
uint64_t v___x_385_; 
v___x_385_ = lean_uint64_add(v_quotient_373_, v___x_374_);
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v___x_385_;
goto v___jp_343_;
}
}
else
{
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v_quotient_373_;
goto v___jp_343_;
}
}
}
else
{
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v___y_357_;
goto v___jp_343_;
}
}
else
{
uint64_t v___x_386_; uint64_t v___x_387_; 
v___x_386_ = lean_uint64_sub(v___x_363_, v___y_359_);
v___x_387_ = lean_uint64_shift_left(v___y_357_, v___x_386_);
v___y_344_ = v___y_354_;
v___y_345_ = v_position_360_;
v___y_346_ = v___y_356_;
v___y_347_ = v___y_358_;
v___y_348_ = v___x_387_;
goto v___jp_343_;
}
}
else
{
uint64_t v___x_388_; uint8_t v___x_389_; 
v___x_388_ = 149ULL;
v___x_389_ = lean_uint64_dec_lt(v___y_355_, v___x_388_);
if (v___x_389_ == 0)
{
uint64_t v___x_390_; uint64_t v___x_391_; 
v___x_390_ = lean_uint64_sub(v___y_355_, v___x_388_);
v___x_391_ = lean_uint64_shift_left(v___y_357_, v___x_390_);
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v___x_391_;
goto v___jp_241_;
}
else
{
uint64_t v___x_392_; uint8_t v___x_393_; 
v___x_392_ = lean_uint64_sub(v___x_388_, v___y_355_);
v___x_393_ = lean_uint64_dec_eq(v___x_392_, v___y_354_);
if (v___x_393_ == 0)
{
uint64_t v___x_394_; uint8_t v___x_395_; 
v___x_394_ = 64ULL;
v___x_395_ = lean_uint64_dec_lt(v___x_392_, v___x_394_);
if (v___x_395_ == 0)
{
uint8_t v___x_396_; 
v___x_396_ = lean_uint64_dec_eq(v___x_392_, v___x_394_);
if (v___x_396_ == 0)
{
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v___y_354_;
goto v___jp_241_;
}
else
{
uint64_t v___x_397_; uint8_t v___x_398_; 
v___x_397_ = 9223372036854775808ULL;
v___x_398_ = lean_uint64_dec_lt(v___x_397_, v___y_357_);
if (v___x_398_ == 0)
{
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v___y_354_;
goto v___jp_241_;
}
else
{
uint64_t v___x_399_; 
v___x_399_ = 1ULL;
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v___x_399_;
goto v___jp_241_;
}
}
}
else
{
uint64_t v_quotient_400_; uint64_t v___x_401_; uint64_t v___x_402_; uint64_t v___x_403_; uint64_t v_remainder_404_; uint64_t v___x_405_; uint64_t v_half_406_; uint8_t v___x_407_; 
v_quotient_400_ = lean_uint64_shift_right(v___y_357_, v___x_392_);
v___x_401_ = 1ULL;
v___x_402_ = lean_uint64_shift_left(v___x_401_, v___x_392_);
v___x_403_ = lean_uint64_sub(v___x_402_, v___x_401_);
v_remainder_404_ = lean_uint64_land(v___y_357_, v___x_403_);
v___x_405_ = lean_uint64_sub(v___x_392_, v___x_401_);
v_half_406_ = lean_uint64_shift_left(v___x_401_, v___x_405_);
v___x_407_ = lean_uint64_dec_lt(v_remainder_404_, v_half_406_);
if (v___x_407_ == 0)
{
uint8_t v___x_408_; 
v___x_408_ = lean_uint64_dec_lt(v_half_406_, v_remainder_404_);
if (v___x_408_ == 0)
{
uint64_t v___x_409_; uint8_t v___x_410_; 
v___x_409_ = lean_uint64_land(v_quotient_400_, v___x_401_);
v___x_410_ = lean_uint64_dec_eq(v___x_409_, v___y_354_);
if (v___x_410_ == 0)
{
uint64_t v___x_411_; 
v___x_411_ = lean_uint64_add(v_quotient_400_, v___x_401_);
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v___x_411_;
goto v___jp_241_;
}
else
{
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v_quotient_400_;
goto v___jp_241_;
}
}
else
{
uint64_t v___x_412_; 
v___x_412_ = lean_uint64_add(v_quotient_400_, v___x_401_);
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v___x_412_;
goto v___jp_241_;
}
}
else
{
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v_quotient_400_;
goto v___jp_241_;
}
}
}
else
{
v___y_242_ = v___y_354_;
v___y_243_ = v___y_356_;
v___y_244_ = v___y_358_;
v___y_245_ = v___y_357_;
goto v___jp_241_;
}
}
}
}
v___jp_413_:
{
uint64_t v___x_421_; uint64_t v___x_422_; uint8_t v___x_423_; 
v___x_421_ = 1ULL;
v___x_422_ = lean_uint64_shift_right(v___y_418_, v___x_421_);
v___x_423_ = lean_uint64_dec_eq(v___x_422_, v___y_414_);
if (v___x_423_ == 0)
{
uint64_t v___x_424_; 
v___x_424_ = lean_uint64_add(v___y_420_, v___x_421_);
v___y_354_ = v___y_414_;
v___y_355_ = v___y_415_;
v___y_356_ = v___y_416_;
v___y_357_ = v___y_417_;
v___y_358_ = v___y_419_;
v___y_359_ = v___x_424_;
goto v___jp_353_;
}
else
{
v___y_354_ = v___y_414_;
v___y_355_ = v___y_415_;
v___y_356_ = v___y_416_;
v___y_357_ = v___y_417_;
v___y_358_ = v___y_419_;
v___y_359_ = v___y_420_;
goto v___jp_353_;
}
}
v___jp_425_:
{
uint64_t v___x_435_; uint8_t v___x_436_; 
v___x_435_ = lean_uint64_shift_right(v___y_431_, v___y_433_);
v___x_436_ = lean_uint64_dec_eq(v___x_435_, v___y_427_);
if (v___x_436_ == 0)
{
uint64_t v___x_437_; 
v___x_437_ = lean_uint64_add(v___y_426_, v___y_433_);
v___y_414_ = v___y_427_;
v___y_415_ = v___y_428_;
v___y_416_ = v___y_429_;
v___y_417_ = v___y_430_;
v___y_418_ = v___y_434_;
v___y_419_ = v___y_432_;
v___y_420_ = v___x_437_;
goto v___jp_413_;
}
else
{
v___y_414_ = v___y_427_;
v___y_415_ = v___y_428_;
v___y_416_ = v___y_429_;
v___y_417_ = v___y_430_;
v___y_418_ = v___y_434_;
v___y_419_ = v___y_432_;
v___y_420_ = v___y_426_;
goto v___jp_413_;
}
}
v___jp_438_:
{
uint64_t v___x_446_; uint64_t v___x_447_; uint8_t v___x_448_; 
v___x_446_ = 2ULL;
v___x_447_ = lean_uint64_shift_right(v___y_443_, v___x_446_);
v___x_448_ = lean_uint64_dec_eq(v___x_447_, v___y_439_);
if (v___x_448_ == 0)
{
v___y_426_ = v___y_445_;
v___y_427_ = v___y_439_;
v___y_428_ = v___y_440_;
v___y_429_ = v___y_441_;
v___y_430_ = v___y_442_;
v___y_431_ = v___y_443_;
v___y_432_ = v___y_444_;
v___y_433_ = v___x_446_;
v___y_434_ = v___x_447_;
goto v___jp_425_;
}
else
{
v___y_426_ = v___y_445_;
v___y_427_ = v___y_439_;
v___y_428_ = v___y_440_;
v___y_429_ = v___y_441_;
v___y_430_ = v___y_442_;
v___y_431_ = v___y_443_;
v___y_432_ = v___y_444_;
v___y_433_ = v___x_446_;
v___y_434_ = v___y_443_;
goto v___jp_425_;
}
}
v___jp_449_:
{
uint64_t v___x_459_; uint8_t v___x_460_; 
v___x_459_ = lean_uint64_shift_right(v___y_452_, v___y_451_);
v___x_460_ = lean_uint64_dec_eq(v___x_459_, v___y_450_);
if (v___x_460_ == 0)
{
uint64_t v___x_461_; 
v___x_461_ = lean_uint64_add(v___y_454_, v___y_451_);
v___y_439_ = v___y_450_;
v___y_440_ = v___y_453_;
v___y_441_ = v___y_455_;
v___y_442_ = v___y_456_;
v___y_443_ = v___y_458_;
v___y_444_ = v___y_457_;
v___y_445_ = v___x_461_;
goto v___jp_438_;
}
else
{
v___y_439_ = v___y_450_;
v___y_440_ = v___y_453_;
v___y_441_ = v___y_455_;
v___y_442_ = v___y_456_;
v___y_443_ = v___y_458_;
v___y_444_ = v___y_457_;
v___y_445_ = v___y_454_;
goto v___jp_438_;
}
}
v___jp_462_:
{
uint64_t v___x_470_; uint64_t v___x_471_; uint8_t v___x_472_; 
v___x_470_ = 4ULL;
v___x_471_ = lean_uint64_shift_right(v___y_464_, v___x_470_);
v___x_472_ = lean_uint64_dec_eq(v___x_471_, v___y_463_);
if (v___x_472_ == 0)
{
v___y_450_ = v___y_463_;
v___y_451_ = v___x_470_;
v___y_452_ = v___y_464_;
v___y_453_ = v___y_465_;
v___y_454_ = v___y_469_;
v___y_455_ = v___y_466_;
v___y_456_ = v___y_467_;
v___y_457_ = v___y_468_;
v___y_458_ = v___x_471_;
goto v___jp_449_;
}
else
{
v___y_450_ = v___y_463_;
v___y_451_ = v___x_470_;
v___y_452_ = v___y_464_;
v___y_453_ = v___y_465_;
v___y_454_ = v___y_469_;
v___y_455_ = v___y_466_;
v___y_456_ = v___y_467_;
v___y_457_ = v___y_468_;
v___y_458_ = v___y_464_;
goto v___jp_449_;
}
}
v___jp_473_:
{
uint64_t v___x_483_; uint8_t v___x_484_; 
v___x_483_ = lean_uint64_shift_right(v___y_478_, v___y_476_);
v___x_484_ = lean_uint64_dec_eq(v___x_483_, v___y_474_);
if (v___x_484_ == 0)
{
uint64_t v___x_485_; 
v___x_485_ = lean_uint64_add(v___y_475_, v___y_476_);
v___y_463_ = v___y_474_;
v___y_464_ = v___y_482_;
v___y_465_ = v___y_477_;
v___y_466_ = v___y_479_;
v___y_467_ = v___y_480_;
v___y_468_ = v___y_481_;
v___y_469_ = v___x_485_;
goto v___jp_462_;
}
else
{
v___y_463_ = v___y_474_;
v___y_464_ = v___y_482_;
v___y_465_ = v___y_477_;
v___y_466_ = v___y_479_;
v___y_467_ = v___y_480_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_475_;
goto v___jp_462_;
}
}
v___jp_486_:
{
uint64_t v___x_494_; uint64_t v___x_495_; uint8_t v___x_496_; 
v___x_494_ = 8ULL;
v___x_495_ = lean_uint64_shift_right(v___y_489_, v___x_494_);
v___x_496_ = lean_uint64_dec_eq(v___x_495_, v___y_487_);
if (v___x_496_ == 0)
{
v___y_474_ = v___y_487_;
v___y_475_ = v___y_493_;
v___y_476_ = v___x_494_;
v___y_477_ = v___y_488_;
v___y_478_ = v___y_489_;
v___y_479_ = v___y_490_;
v___y_480_ = v___y_491_;
v___y_481_ = v___y_492_;
v___y_482_ = v___x_495_;
goto v___jp_473_;
}
else
{
v___y_474_ = v___y_487_;
v___y_475_ = v___y_493_;
v___y_476_ = v___x_494_;
v___y_477_ = v___y_488_;
v___y_478_ = v___y_489_;
v___y_479_ = v___y_490_;
v___y_480_ = v___y_491_;
v___y_481_ = v___y_492_;
v___y_482_ = v___y_489_;
goto v___jp_473_;
}
}
v___jp_497_:
{
uint64_t v___x_507_; uint8_t v___x_508_; 
v___x_507_ = lean_uint64_shift_right(v___y_504_, v___y_502_);
v___x_508_ = lean_uint64_dec_eq(v___x_507_, v___y_498_);
if (v___x_508_ == 0)
{
uint64_t v___x_509_; 
v___x_509_ = lean_uint64_add(v___y_501_, v___y_502_);
v___y_487_ = v___y_498_;
v___y_488_ = v___y_499_;
v___y_489_ = v___y_506_;
v___y_490_ = v___y_500_;
v___y_491_ = v___y_503_;
v___y_492_ = v___y_505_;
v___y_493_ = v___x_509_;
goto v___jp_486_;
}
else
{
v___y_487_ = v___y_498_;
v___y_488_ = v___y_499_;
v___y_489_ = v___y_506_;
v___y_490_ = v___y_500_;
v___y_491_ = v___y_503_;
v___y_492_ = v___y_505_;
v___y_493_ = v___y_501_;
goto v___jp_486_;
}
}
v___jp_510_:
{
uint64_t v___x_518_; uint64_t v___x_519_; uint8_t v___x_520_; 
v___x_518_ = 16ULL;
v___x_519_ = lean_uint64_shift_right(v___y_515_, v___x_518_);
v___x_520_ = lean_uint64_dec_eq(v___x_519_, v___y_511_);
if (v___x_520_ == 0)
{
v___y_498_ = v___y_511_;
v___y_499_ = v___y_512_;
v___y_500_ = v___y_513_;
v___y_501_ = v___y_517_;
v___y_502_ = v___x_518_;
v___y_503_ = v___y_514_;
v___y_504_ = v___y_515_;
v___y_505_ = v___y_516_;
v___y_506_ = v___x_519_;
goto v___jp_497_;
}
else
{
v___y_498_ = v___y_511_;
v___y_499_ = v___y_512_;
v___y_500_ = v___y_513_;
v___y_501_ = v___y_517_;
v___y_502_ = v___x_518_;
v___y_503_ = v___y_514_;
v___y_504_ = v___y_515_;
v___y_505_ = v___y_516_;
v___y_506_ = v___y_515_;
goto v___jp_497_;
}
}
v___jp_521_:
{
uint64_t v___x_529_; uint8_t v___x_530_; 
v___x_529_ = lean_uint64_shift_right(v___y_526_, v___y_522_);
v___x_530_ = lean_uint64_dec_eq(v___x_529_, v___y_523_);
if (v___x_530_ == 0)
{
v___y_511_ = v___y_523_;
v___y_512_ = v___y_524_;
v___y_513_ = v___y_525_;
v___y_514_ = v___y_526_;
v___y_515_ = v___y_528_;
v___y_516_ = v___y_527_;
v___y_517_ = v___y_522_;
goto v___jp_510_;
}
else
{
v___y_511_ = v___y_523_;
v___y_512_ = v___y_524_;
v___y_513_ = v___y_525_;
v___y_514_ = v___y_526_;
v___y_515_ = v___y_528_;
v___y_516_ = v___y_527_;
v___y_517_ = v___y_523_;
goto v___jp_510_;
}
}
v___jp_531_:
{
uint64_t v___x_536_; uint8_t v___x_537_; 
v___x_536_ = 0ULL;
v___x_537_ = lean_uint64_dec_eq(v___y_534_, v___x_536_);
if (v___x_537_ == 0)
{
uint64_t v___x_538_; uint64_t v___x_539_; uint8_t v___x_540_; 
v___x_538_ = 32ULL;
v___x_539_ = lean_uint64_shift_right(v___y_534_, v___x_538_);
v___x_540_ = lean_uint64_dec_eq(v___x_539_, v___x_536_);
if (v___x_540_ == 0)
{
v___y_522_ = v___x_538_;
v___y_523_ = v___x_536_;
v___y_524_ = v___y_532_;
v___y_525_ = v___y_533_;
v___y_526_ = v___y_534_;
v___y_527_ = v___y_535_;
v___y_528_ = v___x_539_;
goto v___jp_521_;
}
else
{
v___y_522_ = v___x_538_;
v___y_523_ = v___x_536_;
v___y_524_ = v___y_532_;
v___y_525_ = v___y_533_;
v___y_526_ = v___y_534_;
v___y_527_ = v___y_535_;
v___y_528_ = v___y_534_;
goto v___jp_521_;
}
}
else
{
if (v___y_533_ == 0)
{
uint32_t v___x_541_; 
v___x_541_ = 0;
return v___x_541_;
}
else
{
uint32_t v___x_542_; 
v___x_542_ = 2147483648;
return v___x_542_;
}
}
}
v___jp_543_:
{
uint64_t v___x_550_; uint64_t v___x_551_; uint64_t v___x_552_; uint8_t v___x_553_; 
v___x_550_ = lean_uint64_mul(v___y_548_, v___y_545_);
v___x_551_ = lean_uint64_add(v___y_544_, v___y_549_);
v___x_552_ = 281474976710656ULL;
v___x_553_ = lean_uint64_dec_lt(v___x_550_, v___x_552_);
if (v___x_553_ == 0)
{
v___y_532_ = v___x_551_;
v___y_533_ = v___y_546_;
v___y_534_ = v___x_550_;
v___y_535_ = v___y_547_;
goto v___jp_531_;
}
else
{
uint64_t v___x_554_; uint8_t v___x_555_; 
v___x_554_ = 123ULL;
v___x_555_ = lean_uint64_dec_le(v___x_551_, v___x_554_);
if (v___x_555_ == 0)
{
v___y_532_ = v___x_551_;
v___y_533_ = v___y_546_;
v___y_534_ = v___x_550_;
v___y_535_ = v___y_547_;
goto v___jp_531_;
}
else
{
uint64_t v___x_556_; uint8_t v___x_557_; 
v___x_556_ = 0ULL;
v___x_557_ = lean_uint64_dec_eq(v___x_550_, v___x_556_);
if (v___x_557_ == 0)
{
uint64_t v___x_558_; uint64_t v___x_559_; uint8_t v___x_560_; 
v___x_558_ = 149ULL;
v___x_559_ = lean_uint64_sub(v___x_558_, v___x_551_);
v___x_560_ = lean_uint64_dec_eq(v___x_559_, v___x_556_);
if (v___x_560_ == 0)
{
uint64_t v___x_561_; uint8_t v___x_562_; 
v___x_561_ = 64ULL;
v___x_562_ = lean_uint64_dec_lt(v___x_559_, v___x_561_);
if (v___x_562_ == 0)
{
uint8_t v___x_563_; 
v___x_563_ = lean_uint64_dec_eq(v___x_559_, v___x_561_);
if (v___x_563_ == 0)
{
v___y_263_ = v___y_546_;
v___y_264_ = v___x_556_;
v___y_265_ = v___y_547_;
v___y_266_ = v___x_556_;
goto v___jp_262_;
}
else
{
uint64_t v___x_564_; uint8_t v___x_565_; 
v___x_564_ = 9223372036854775808ULL;
v___x_565_ = lean_uint64_dec_lt(v___x_564_, v___x_550_);
if (v___x_565_ == 0)
{
v___y_263_ = v___y_546_;
v___y_264_ = v___x_556_;
v___y_265_ = v___y_547_;
v___y_266_ = v___x_556_;
goto v___jp_262_;
}
else
{
uint64_t v___x_566_; 
v___x_566_ = 1ULL;
v___y_263_ = v___y_546_;
v___y_264_ = v___x_556_;
v___y_265_ = v___y_547_;
v___y_266_ = v___x_566_;
goto v___jp_262_;
}
}
}
else
{
uint64_t v_quotient_567_; uint64_t v___x_568_; uint64_t v___x_569_; uint64_t v___x_570_; uint64_t v_remainder_571_; uint64_t v___x_572_; uint64_t v_half_573_; uint8_t v___x_574_; 
v_quotient_567_ = lean_uint64_shift_right(v___x_550_, v___x_559_);
v___x_568_ = 1ULL;
v___x_569_ = lean_uint64_shift_left(v___x_568_, v___x_559_);
v___x_570_ = lean_uint64_sub(v___x_569_, v___x_568_);
v_remainder_571_ = lean_uint64_land(v___x_550_, v___x_570_);
v___x_572_ = lean_uint64_sub(v___x_559_, v___x_568_);
v_half_573_ = lean_uint64_shift_left(v___x_568_, v___x_572_);
v___x_574_ = lean_uint64_dec_lt(v_remainder_571_, v_half_573_);
if (v___x_574_ == 0)
{
uint8_t v___x_575_; 
v___x_575_ = lean_uint64_dec_lt(v_half_573_, v_remainder_571_);
if (v___x_575_ == 0)
{
uint64_t v___x_576_; uint8_t v___x_577_; 
v___x_576_ = lean_uint64_land(v_quotient_567_, v___x_568_);
v___x_577_ = lean_uint64_dec_eq(v___x_576_, v___x_556_);
if (v___x_577_ == 0)
{
uint64_t v___x_578_; 
v___x_578_ = lean_uint64_add(v_quotient_567_, v___x_568_);
v___y_263_ = v___y_546_;
v___y_264_ = v___x_556_;
v___y_265_ = v___y_547_;
v___y_266_ = v___x_578_;
goto v___jp_262_;
}
else
{
v___y_263_ = v___y_546_;
v___y_264_ = v___x_556_;
v___y_265_ = v___y_547_;
v___y_266_ = v_quotient_567_;
goto v___jp_262_;
}
}
else
{
uint64_t v___x_579_; 
v___x_579_ = lean_uint64_add(v_quotient_567_, v___x_568_);
v___y_263_ = v___y_546_;
v___y_264_ = v___x_556_;
v___y_265_ = v___y_547_;
v___y_266_ = v___x_579_;
goto v___jp_262_;
}
}
else
{
v___y_263_ = v___y_546_;
v___y_264_ = v___x_556_;
v___y_265_ = v___y_547_;
v___y_266_ = v_quotient_567_;
goto v___jp_262_;
}
}
}
else
{
v___y_263_ = v___y_546_;
v___y_264_ = v___x_556_;
v___y_265_ = v___y_547_;
v___y_266_ = v___x_550_;
goto v___jp_262_;
}
}
else
{
if (v___y_546_ == 0)
{
uint32_t v___x_580_; 
v___x_580_ = 0;
return v___x_580_;
}
else
{
uint32_t v___x_581_; 
v___x_581_ = 2147483648;
return v___x_581_;
}
}
}
}
}
v___jp_585_:
{
uint64_t v___x_591_; uint64_t v___x_592_; uint8_t v___x_593_; 
v___x_591_ = lean_uint32_to_uint64(v_ey_584_);
v___x_592_ = 0ULL;
v___x_593_ = lean_uint64_dec_eq(v___x_591_, v___x_592_);
if (v___x_593_ == 0)
{
uint64_t v___x_594_; uint64_t v___x_595_; 
v___x_594_ = 1ULL;
v___x_595_ = lean_uint64_sub(v___x_591_, v___x_594_);
v___y_544_ = v___y_590_;
v___y_545_ = v___y_586_;
v___y_546_ = v___y_587_;
v___y_547_ = v___y_588_;
v___y_548_ = v___y_589_;
v___y_549_ = v___x_595_;
goto v___jp_543_;
}
else
{
v___y_544_ = v___y_590_;
v___y_545_ = v___y_586_;
v___y_546_ = v___y_587_;
v___y_547_ = v___y_588_;
v___y_548_ = v___y_589_;
v___y_549_ = v___x_592_;
goto v___jp_543_;
}
}
v___jp_596_:
{
uint64_t v___x_601_; uint64_t v___x_602_; uint8_t v___x_603_; 
v___x_601_ = lean_uint32_to_uint64(v_ex_582_);
v___x_602_ = 0ULL;
v___x_603_ = lean_uint64_dec_eq(v___x_601_, v___x_602_);
if (v___x_603_ == 0)
{
uint64_t v___x_604_; uint64_t v___x_605_; 
v___x_604_ = 1ULL;
v___x_605_ = lean_uint64_sub(v___x_601_, v___x_604_);
v___y_586_ = v___y_600_;
v___y_587_ = v___y_597_;
v___y_588_ = v___y_598_;
v___y_589_ = v___y_599_;
v___y_590_ = v___x_605_;
goto v___jp_585_;
}
else
{
v___y_586_ = v___y_600_;
v___y_587_ = v___y_597_;
v___y_588_ = v___y_598_;
v___y_589_ = v___y_599_;
v___y_590_ = v___x_602_;
goto v___jp_585_;
}
}
v___jp_606_:
{
uint32_t v___x_611_; uint8_t v___x_612_; 
v___x_611_ = 0;
v___x_612_ = lean_uint32_dec_eq(v_ey_584_, v___x_611_);
if (v___x_612_ == 0)
{
uint64_t v___x_613_; uint64_t v___x_614_; uint64_t v___x_615_; 
v___x_613_ = lean_uint32_to_uint64(v___y_607_);
v___x_614_ = 8388608ULL;
v___x_615_ = lean_uint64_lor(v___x_613_, v___x_614_);
v___y_597_ = v___y_608_;
v___y_598_ = v___y_609_;
v___y_599_ = v___y_610_;
v___y_600_ = v___x_615_;
goto v___jp_596_;
}
else
{
uint64_t v___x_616_; 
v___x_616_ = lean_uint32_to_uint64(v___y_607_);
v___y_597_ = v___y_608_;
v___y_598_ = v___y_609_;
v___y_599_ = v___y_610_;
v___y_600_ = v___x_616_;
goto v___jp_596_;
}
}
v___jp_617_:
{
uint32_t v___x_619_; uint32_t v_xFraction_620_; uint32_t v_yFraction_621_; uint32_t v___x_622_; uint8_t v___x_623_; 
v___x_619_ = 8388607;
v_xFraction_620_ = lean_uint32_land(v___y_130_, v___x_619_);
v_yFraction_621_ = lean_uint32_land(v___y_131_, v___x_619_);
v___x_622_ = 0;
v___x_623_ = lean_uint32_dec_eq(v_ex_582_, v___x_622_);
if (v___x_623_ == 0)
{
uint64_t v___x_624_; uint64_t v___x_625_; uint64_t v___x_626_; 
v___x_624_ = lean_uint32_to_uint64(v_xFraction_620_);
v___x_625_ = 8388608ULL;
v___x_626_ = lean_uint64_lor(v___x_624_, v___x_625_);
v___y_607_ = v_yFraction_621_;
v___y_608_ = v___y_618_;
v___y_609_ = v___x_619_;
v___y_610_ = v___x_626_;
goto v___jp_606_;
}
else
{
uint64_t v___x_627_; 
v___x_627_ = lean_uint32_to_uint64(v_xFraction_620_);
v___y_607_ = v_yFraction_621_;
v___y_608_ = v___y_618_;
v___y_609_ = v___x_619_;
v___y_610_ = v___x_627_;
goto v___jp_606_;
}
}
v___jp_631_:
{
if (v___y_633_ == 0)
{
v___y_618_ = v___x_630_;
goto v___jp_617_;
}
else
{
v___y_618_ = v___y_632_;
goto v___jp_617_;
}
}
v___jp_634_:
{
if (v___y_635_ == 0)
{
if (v___y_637_ == 0)
{
v___y_632_ = v___y_636_;
v___y_633_ = v___x_630_;
goto v___jp_631_;
}
else
{
v___y_618_ = v___x_630_;
goto v___jp_617_;
}
}
else
{
v___y_632_ = v___y_636_;
v___y_633_ = v___y_637_;
goto v___jp_631_;
}
}
v___jp_638_:
{
uint32_t v___x_641_; uint32_t v___x_642_; uint32_t v___x_643_; uint8_t v___x_644_; 
v___x_641_ = 2147483648;
v___x_642_ = lean_uint32_land(v___y_131_, v___x_641_);
v___x_643_ = 0;
v___x_644_ = lean_uint32_dec_eq(v___x_642_, v___x_643_);
if (v___x_644_ == 0)
{
v___y_635_ = v___y_640_;
v___y_636_ = v___y_639_;
v___y_637_ = v___x_630_;
goto v___jp_634_;
}
else
{
v___y_635_ = v___y_640_;
v___y_636_ = v___y_639_;
v___y_637_ = v___y_639_;
goto v___jp_634_;
}
}
v___jp_645_:
{
if (v___y_646_ == 0)
{
uint32_t v___x_647_; uint32_t v___x_648_; uint32_t v___x_649_; uint8_t v___x_650_; 
v___x_647_ = 2147483648;
v___x_648_ = lean_uint32_land(v___y_130_, v___x_647_);
v___x_649_ = 0;
v___x_650_ = lean_uint32_dec_eq(v___x_648_, v___x_649_);
if (v___x_650_ == 0)
{
v___y_639_ = v___y_646_;
v___y_640_ = v___x_630_;
goto v___jp_638_;
}
else
{
v___y_639_ = v___y_646_;
v___y_640_ = v___y_646_;
goto v___jp_638_;
}
}
else
{
lean_object* v___x_651_; lean_object* v___x_652_; lean_object* v___x_653_; uint32_t v___x_654_; 
v___x_651_ = lean_uint32_to_nat(v___y_130_);
v___x_652_ = lean_uint32_to_nat(v___y_131_);
v___x_653_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_651_, v___x_652_);
v___x_654_ = lean_uint32_of_nat(v___x_653_);
lean_dec(v___x_653_);
return v___x_654_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_683_, lean_object* v___y_684_){
_start:
{
uint32_t v___y_4909__boxed_685_; uint32_t v___y_4910__boxed_686_; uint32_t v_res_687_; lean_object* v_r_688_; 
v___y_4909__boxed_685_ = lean_unbox_uint32(v___y_683_);
lean_dec(v___y_683_);
v___y_4910__boxed_686_ = lean_unbox_uint32(v___y_684_);
lean_dec(v___y_684_);
v_res_687_ = lp_competition_main___lam__1(v___y_4909__boxed_685_, v___y_4910__boxed_686_);
v_r_688_ = lean_box_uint32(v_res_687_);
return v_r_688_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_689_, uint32_t v___y_690_){
_start:
{
uint8_t v___y_692_; uint8_t v___y_708_; uint8_t v___y_722_; uint8_t v___y_739_; float v___y_746_; float v___y_747_; float v___y_761_; uint8_t v___y_762_; float v___y_777_; uint32_t v___y_787_; uint32_t v___y_791_; uint32_t v___y_795_; uint32_t v___y_796_; uint32_t v___y_797_; uint32_t v___y_801_; uint8_t v___y_802_; uint64_t v___y_803_; uint64_t v___y_804_; uint32_t v___y_816_; uint32_t v___y_817_; uint32_t v___y_818_; uint64_t v___y_822_; uint32_t v___y_823_; uint8_t v___y_824_; uint64_t v___y_825_; uint8_t v___y_837_; uint8_t v___y_838_; uint32_t v___x_843_; uint32_t v___x_844_; uint8_t v___y_846_; uint32_t v___x_858_; uint32_t v___y_860_; uint32_t v___y_861_; uint32_t v___y_862_; uint32_t v___y_863_; uint32_t v___y_870_; uint8_t v___y_871_; uint32_t v___y_872_; uint32_t v___y_873_; uint64_t v___y_877_; uint32_t v___y_878_; uint8_t v___y_879_; uint64_t v___y_880_; uint64_t v___y_881_; uint32_t v___y_891_; uint64_t v___y_892_; uint8_t v___y_893_; uint8_t v___y_894_; uint64_t v___y_895_; uint64_t v___y_896_; uint64_t v___y_903_; uint32_t v___y_904_; uint8_t v___y_905_; uint64_t v___y_906_; uint64_t v___y_907_; uint64_t v___y_913_; uint32_t v___y_914_; uint8_t v___y_915_; uint64_t v___y_916_; uint64_t v___y_917_; uint64_t v___y_918_; uint64_t v___y_973_; uint32_t v___y_974_; uint8_t v___y_975_; uint64_t v___y_976_; uint64_t v___y_977_; uint64_t v___y_978_; uint64_t v___y_979_; uint64_t v___y_985_; uint64_t v___y_986_; uint32_t v___y_987_; uint64_t v___y_988_; uint8_t v___y_989_; uint64_t v___y_990_; uint64_t v___y_991_; uint64_t v___y_992_; uint64_t v___y_993_; uint64_t v___y_998_; uint32_t v___y_999_; uint8_t v___y_1000_; uint64_t v___y_1001_; uint64_t v___y_1002_; uint64_t v___y_1003_; uint64_t v___y_1004_; uint64_t v___y_1009_; uint64_t v___y_1010_; uint64_t v___y_1011_; uint32_t v___y_1012_; uint8_t v___y_1013_; uint64_t v___y_1014_; uint64_t v___y_1015_; uint64_t v___y_1016_; uint64_t v___y_1017_; uint64_t v___y_1022_; uint32_t v___y_1023_; uint8_t v___y_1024_; uint64_t v___y_1025_; uint64_t v___y_1026_; uint64_t v___y_1027_; uint64_t v___y_1028_; uint64_t v___y_1033_; uint64_t v___y_1034_; uint64_t v___y_1035_; uint32_t v___y_1036_; uint8_t v___y_1037_; uint64_t v___y_1038_; uint64_t v___y_1039_; uint64_t v___y_1040_; uint64_t v___y_1041_; uint64_t v___y_1046_; uint64_t v___y_1047_; uint32_t v___y_1048_; uint8_t v___y_1049_; uint64_t v___y_1050_; uint64_t v___y_1051_; uint64_t v___y_1052_; uint64_t v___y_1057_; uint64_t v___y_1058_; uint64_t v___y_1059_; uint32_t v___y_1060_; uint8_t v___y_1061_; uint64_t v___y_1062_; uint64_t v___y_1063_; uint64_t v___y_1064_; uint64_t v___y_1065_; uint64_t v___y_1070_; uint32_t v___y_1071_; uint8_t v___y_1072_; uint64_t v___y_1073_; uint64_t v___y_1074_; uint64_t v___y_1075_; uint64_t v___y_1076_; uint64_t v___y_1081_; uint64_t v___y_1082_; uint32_t v___y_1083_; uint8_t v___y_1084_; uint64_t v___y_1085_; uint64_t v___y_1086_; uint64_t v___y_1087_; uint64_t v___y_1091_; uint32_t v___y_1092_; uint8_t v___y_1093_; uint64_t v___y_1094_; uint64_t v___y_1103_; uint64_t v___y_1104_; uint64_t v___y_1105_; uint32_t v___y_1106_; uint8_t v___y_1107_; uint64_t v___y_1108_; uint32_t v_ex_1141_; uint32_t v___x_1142_; uint32_t v_ey_1143_; uint64_t v___y_1145_; uint64_t v___y_1146_; uint32_t v___y_1147_; uint8_t v___y_1148_; uint64_t v___y_1149_; uint64_t v___y_1156_; uint32_t v___y_1157_; uint8_t v___y_1158_; uint64_t v___y_1159_; uint32_t v___y_1166_; uint32_t v___y_1167_; uint8_t v___y_1168_; uint64_t v___y_1169_; uint8_t v___y_1177_; uint32_t v___x_1187_; uint32_t v___x_1188_; uint8_t v___x_1189_; uint8_t v___y_1191_; uint8_t v___y_1192_; uint8_t v___y_1194_; uint8_t v___y_1195_; uint8_t v___y_1196_; uint8_t v___y_1198_; uint8_t v___y_1199_; uint8_t v___y_1205_; 
v___x_843_ = 23;
v___x_844_ = lean_uint32_shift_right(v___y_689_, v___x_843_);
v___x_858_ = 255;
v_ex_1141_ = lean_uint32_land(v___x_844_, v___x_858_);
v___x_1142_ = lean_uint32_shift_right(v___y_690_, v___x_843_);
v_ey_1143_ = lean_uint32_land(v___x_1142_, v___x_858_);
v___x_1187_ = lean_uint32_add(v_ex_1141_, v_ey_1143_);
v___x_1188_ = 128;
v___x_1189_ = lean_uint32_dec_lt(v___x_1187_, v___x_1188_);
if (v___x_1189_ == 0)
{
uint32_t v___x_1214_; uint32_t v_a_1215_; uint32_t v___x_1216_; uint32_t v___x_1217_; uint32_t v___x_1218_; uint8_t v___x_1219_; 
v___x_1214_ = 2147483647;
v_a_1215_ = lean_uint32_land(v___y_689_, v___x_1214_);
v___x_1216_ = 201326591;
v___x_1217_ = 1;
v___x_1218_ = lean_uint32_sub(v_a_1215_, v___x_1217_);
v___x_1219_ = lean_uint32_dec_le(v___x_1216_, v___x_1218_);
if (v___x_1219_ == 0)
{
v___y_846_ = v___x_1219_;
goto v___jp_845_;
}
else
{
uint32_t v___x_1220_; uint8_t v___x_1221_; 
v___x_1220_ = 2139095040;
v___x_1221_ = lean_uint32_dec_lt(v_a_1215_, v___x_1220_);
v___y_846_ = v___x_1221_;
goto v___jp_845_;
}
}
else
{
uint32_t v___x_1222_; uint8_t v___x_1223_; uint8_t v___y_1225_; 
v___x_1222_ = 84;
v___x_1223_ = lean_uint32_dec_le(v___x_1187_, v___x_1222_);
if (v___x_1223_ == 0)
{
uint32_t v___x_1231_; uint32_t v___x_1232_; uint32_t v___x_1233_; uint8_t v___x_1234_; 
v___x_1231_ = 4278190080;
v___x_1232_ = 1;
v___x_1233_ = lean_uint32_shift_left(v___y_689_, v___x_1232_);
v___x_1234_ = lean_uint32_dec_le(v___x_1231_, v___x_1233_);
if (v___x_1234_ == 0)
{
uint32_t v___x_1235_; uint8_t v___x_1236_; 
v___x_1235_ = lean_uint32_shift_left(v___y_690_, v___x_1232_);
v___x_1236_ = lean_uint32_dec_le(v___x_1231_, v___x_1235_);
v___y_1205_ = v___x_1236_;
goto v___jp_1204_;
}
else
{
v___y_1205_ = v___x_1234_;
goto v___jp_1204_;
}
}
else
{
uint32_t v___x_1237_; uint32_t v___x_1238_; uint32_t v___x_1239_; uint8_t v___x_1240_; 
v___x_1237_ = 2147483648;
v___x_1238_ = lean_uint32_land(v___y_689_, v___x_1237_);
v___x_1239_ = 0;
v___x_1240_ = lean_uint32_dec_eq(v___x_1238_, v___x_1239_);
if (v___x_1240_ == 0)
{
v___y_1225_ = v___x_1223_;
goto v___jp_1224_;
}
else
{
uint8_t v___x_1241_; 
v___x_1241_ = 0;
v___y_1225_ = v___x_1241_;
goto v___jp_1224_;
}
}
v___jp_1224_:
{
uint32_t v___x_1226_; uint32_t v___x_1227_; uint32_t v___x_1228_; uint8_t v___x_1229_; 
v___x_1226_ = 2147483648;
v___x_1227_ = lean_uint32_land(v___y_690_, v___x_1226_);
v___x_1228_ = 0;
v___x_1229_ = lean_uint32_dec_eq(v___x_1227_, v___x_1228_);
if (v___x_1229_ == 0)
{
v___y_837_ = v___y_1225_;
v___y_838_ = v___x_1223_;
goto v___jp_836_;
}
else
{
uint8_t v___x_1230_; 
v___x_1230_ = 0;
v___y_837_ = v___y_1225_;
v___y_838_ = v___x_1230_;
goto v___jp_836_;
}
}
}
v___jp_691_:
{
if (v___y_692_ == 0)
{
uint32_t v___x_693_; 
v___x_693_ = lp_competition_Submission_FastMul_mul(v___y_689_, v___y_690_);
return v___x_693_;
}
else
{
uint32_t v___x_694_; uint32_t v___x_695_; 
v___x_694_ = 4194304;
v___x_695_ = lean_uint32_lor(v___y_690_, v___x_694_);
return v___x_695_;
}
}
v___jp_696_:
{
uint32_t v___x_697_; uint32_t v___x_698_; uint32_t v___x_699_; uint32_t v___x_700_; uint8_t v___x_701_; 
v___x_697_ = 23;
v___x_698_ = lean_uint32_shift_right(v___y_690_, v___x_697_);
v___x_699_ = 255;
v___x_700_ = lean_uint32_land(v___x_698_, v___x_699_);
v___x_701_ = lean_uint32_dec_eq(v___x_700_, v___x_699_);
if (v___x_701_ == 0)
{
v___y_692_ = v___x_701_;
goto v___jp_691_;
}
else
{
uint32_t v___x_702_; uint32_t v___x_703_; uint32_t v___x_704_; uint8_t v___x_705_; 
v___x_702_ = 8388607;
v___x_703_ = lean_uint32_land(v___y_690_, v___x_702_);
v___x_704_ = 0;
v___x_705_ = lean_uint32_dec_eq(v___x_703_, v___x_704_);
if (v___x_705_ == 0)
{
v___y_692_ = v___x_701_;
goto v___jp_691_;
}
else
{
uint32_t v___x_706_; 
v___x_706_ = lp_competition_Submission_FastMul_mul(v___y_689_, v___y_690_);
return v___x_706_;
}
}
}
v___jp_707_:
{
if (v___y_708_ == 0)
{
goto v___jp_696_;
}
else
{
uint32_t v___x_709_; uint32_t v___x_710_; 
v___x_709_ = 4194304;
v___x_710_ = lean_uint32_lor(v___y_689_, v___x_709_);
return v___x_710_;
}
}
v___jp_711_:
{
uint32_t v___x_712_; uint32_t v___x_713_; uint32_t v___x_714_; uint32_t v___x_715_; uint8_t v___x_716_; 
v___x_712_ = 23;
v___x_713_ = lean_uint32_shift_right(v___y_689_, v___x_712_);
v___x_714_ = 255;
v___x_715_ = lean_uint32_land(v___x_713_, v___x_714_);
v___x_716_ = lean_uint32_dec_eq(v___x_715_, v___x_714_);
if (v___x_716_ == 0)
{
v___y_708_ = v___x_716_;
goto v___jp_707_;
}
else
{
uint32_t v___x_717_; uint32_t v___x_718_; uint32_t v___x_719_; uint8_t v___x_720_; 
v___x_717_ = 8388607;
v___x_718_ = lean_uint32_land(v___y_689_, v___x_717_);
v___x_719_ = 0;
v___x_720_ = lean_uint32_dec_eq(v___x_718_, v___x_719_);
if (v___x_720_ == 0)
{
v___y_708_ = v___x_716_;
goto v___jp_707_;
}
else
{
goto v___jp_696_;
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
v___x_724_ = lean_uint32_land(v___y_690_, v___x_723_);
v___x_725_ = 0;
v___x_726_ = lean_uint32_dec_eq(v___x_724_, v___x_725_);
if (v___x_726_ == 0)
{
goto v___jp_711_;
}
else
{
uint32_t v___x_727_; 
v___x_727_ = lean_uint32_lor(v___y_690_, v___x_723_);
return v___x_727_;
}
}
}
v___jp_728_:
{
uint32_t v___x_729_; uint32_t v___x_730_; uint32_t v___x_731_; uint32_t v___x_732_; uint8_t v___x_733_; 
v___x_729_ = 23;
v___x_730_ = lean_uint32_shift_right(v___y_690_, v___x_729_);
v___x_731_ = 255;
v___x_732_ = lean_uint32_land(v___x_730_, v___x_731_);
v___x_733_ = lean_uint32_dec_eq(v___x_732_, v___x_731_);
if (v___x_733_ == 0)
{
v___y_722_ = v___x_733_;
goto v___jp_721_;
}
else
{
uint32_t v___x_734_; uint32_t v___x_735_; uint32_t v___x_736_; uint8_t v___x_737_; 
v___x_734_ = 8388607;
v___x_735_ = lean_uint32_land(v___y_690_, v___x_734_);
v___x_736_ = 0;
v___x_737_ = lean_uint32_dec_eq(v___x_735_, v___x_736_);
if (v___x_737_ == 0)
{
v___y_722_ = v___x_733_;
goto v___jp_721_;
}
else
{
goto v___jp_711_;
}
}
}
v___jp_738_:
{
if (v___y_739_ == 0)
{
goto v___jp_728_;
}
else
{
uint32_t v___x_740_; uint32_t v___x_741_; uint32_t v___x_742_; uint8_t v___x_743_; 
v___x_740_ = 4194304;
v___x_741_ = lean_uint32_land(v___y_689_, v___x_740_);
v___x_742_ = 0;
v___x_743_ = lean_uint32_dec_eq(v___x_741_, v___x_742_);
if (v___x_743_ == 0)
{
goto v___jp_728_;
}
else
{
uint32_t v___x_744_; 
v___x_744_ = lean_uint32_lor(v___y_689_, v___x_740_);
return v___x_744_;
}
}
}
v___jp_745_:
{
float v_result_748_; uint8_t v___x_749_; 
v_result_748_ = lean_float32_mul(v___y_746_, v___y_747_);
v___x_749_ = lean_float32_beq(v_result_748_, v_result_748_);
if (v___x_749_ == 0)
{
uint32_t v___x_750_; uint32_t v___x_751_; uint32_t v___x_752_; uint32_t v___x_753_; uint8_t v___x_754_; 
v___x_750_ = 23;
v___x_751_ = lean_uint32_shift_right(v___y_689_, v___x_750_);
v___x_752_ = 255;
v___x_753_ = lean_uint32_land(v___x_751_, v___x_752_);
v___x_754_ = lean_uint32_dec_eq(v___x_753_, v___x_752_);
if (v___x_754_ == 0)
{
v___y_739_ = v___x_754_;
goto v___jp_738_;
}
else
{
uint32_t v___x_755_; uint32_t v___x_756_; uint32_t v___x_757_; uint8_t v___x_758_; 
v___x_755_ = 8388607;
v___x_756_ = lean_uint32_land(v___y_689_, v___x_755_);
v___x_757_ = 0;
v___x_758_ = lean_uint32_dec_eq(v___x_756_, v___x_757_);
if (v___x_758_ == 0)
{
v___y_739_ = v___x_754_;
goto v___jp_738_;
}
else
{
goto v___jp_728_;
}
}
}
else
{
uint32_t v___x_759_; 
v___x_759_ = lean_float32_to_bits(v_result_748_);
return v___x_759_;
}
}
v___jp_760_:
{
if (v___y_762_ == 0)
{
float v___x_763_; 
v___x_763_ = lean_float32_of_bits(v___y_690_);
v___y_746_ = v___y_761_;
v___y_747_ = v___x_763_;
goto v___jp_745_;
}
else
{
uint32_t v___x_764_; uint32_t v___x_765_; uint32_t v___x_766_; uint32_t v___x_767_; float v___x_768_; lean_object* v___x_769_; uint32_t v___x_770_; uint32_t v___x_771_; lean_object* v___x_772_; lean_object* v___x_773_; float v___x_774_; float v___x_775_; 
v___x_764_ = 8388607;
v___x_765_ = lean_uint32_land(v___y_690_, v___x_764_);
v___x_766_ = 8388608;
v___x_767_ = lean_uint32_lor(v___x_765_, v___x_766_);
v___x_768_ = lean_uint32_to_float32(v___x_767_);
v___x_769_ = lp_competition_R2W01b_scaleTable;
v___x_770_ = 23;
v___x_771_ = lean_uint32_shift_right(v___y_690_, v___x_770_);
v___x_772_ = lean_uint32_to_nat(v___x_771_);
v___x_773_ = lean_array_fget_borrowed(v___x_769_, v___x_772_);
lean_dec(v___x_772_);
v___x_774_ = lean_unbox_float32(v___x_773_);
v___x_775_ = lean_float32_mul(v___x_768_, v___x_774_);
v___y_746_ = v___y_761_;
v___y_747_ = v___x_775_;
goto v___jp_745_;
}
}
v___jp_776_:
{
uint32_t v___x_778_; uint32_t v_a_779_; uint32_t v___x_780_; uint32_t v___x_781_; uint32_t v___x_782_; uint8_t v___x_783_; 
v___x_778_ = 2147483647;
v_a_779_ = lean_uint32_land(v___y_690_, v___x_778_);
v___x_780_ = 201326591;
v___x_781_ = 1;
v___x_782_ = lean_uint32_sub(v_a_779_, v___x_781_);
v___x_783_ = lean_uint32_dec_le(v___x_780_, v___x_782_);
if (v___x_783_ == 0)
{
v___y_761_ = v___y_777_;
v___y_762_ = v___x_783_;
goto v___jp_760_;
}
else
{
uint32_t v___x_784_; uint8_t v___x_785_; 
v___x_784_ = 2139095040;
v___x_785_ = lean_uint32_dec_lt(v_a_779_, v___x_784_);
v___y_761_ = v___y_777_;
v___y_762_ = v___x_785_;
goto v___jp_760_;
}
}
v___jp_786_:
{
uint32_t v___x_788_; uint32_t v___x_789_; 
v___x_788_ = 8388608;
v___x_789_ = lean_uint32_lor(v___y_787_, v___x_788_);
return v___x_789_;
}
v___jp_790_:
{
uint32_t v___x_792_; uint32_t v___x_793_; 
v___x_792_ = 8388608;
v___x_793_ = lean_uint32_lor(v___y_791_, v___x_792_);
return v___x_793_;
}
v___jp_794_:
{
uint32_t v___x_798_; uint32_t v___x_799_; 
v___x_798_ = lean_uint32_land(v___y_795_, v___y_796_);
v___x_799_ = lean_uint32_lor(v___y_797_, v___x_798_);
return v___x_799_;
}
v___jp_800_:
{
uint8_t v___x_805_; 
v___x_805_ = lean_uint64_dec_eq(v___y_804_, v___y_803_);
if (v___x_805_ == 0)
{
uint64_t v___x_806_; uint8_t v___x_807_; 
v___x_806_ = 8388608ULL;
v___x_807_ = lean_uint64_dec_eq(v___y_804_, v___x_806_);
if (v___x_807_ == 0)
{
uint32_t v___x_808_; 
v___x_808_ = lean_uint64_to_uint32(v___y_804_);
if (v___y_802_ == 0)
{
uint32_t v___x_809_; 
v___x_809_ = 0;
v___y_795_ = v___x_808_;
v___y_796_ = v___y_801_;
v___y_797_ = v___x_809_;
goto v___jp_794_;
}
else
{
uint32_t v___x_810_; 
v___x_810_ = 2147483648;
v___y_795_ = v___x_808_;
v___y_796_ = v___y_801_;
v___y_797_ = v___x_810_;
goto v___jp_794_;
}
}
else
{
if (v___y_802_ == 0)
{
uint32_t v___x_811_; 
v___x_811_ = 0;
v___y_787_ = v___x_811_;
goto v___jp_786_;
}
else
{
uint32_t v___x_812_; 
v___x_812_ = 2147483648;
v___y_787_ = v___x_812_;
goto v___jp_786_;
}
}
}
else
{
if (v___y_802_ == 0)
{
uint32_t v___x_813_; 
v___x_813_ = 0;
return v___x_813_;
}
else
{
uint32_t v___x_814_; 
v___x_814_ = 2147483648;
return v___x_814_;
}
}
}
v___jp_815_:
{
uint32_t v___x_819_; uint32_t v___x_820_; 
v___x_819_ = lean_uint32_land(v___y_816_, v___y_817_);
v___x_820_ = lean_uint32_lor(v___y_818_, v___x_819_);
return v___x_820_;
}
v___jp_821_:
{
uint8_t v___x_826_; 
v___x_826_ = lean_uint64_dec_eq(v___y_825_, v___y_822_);
if (v___x_826_ == 0)
{
uint64_t v___x_827_; uint8_t v___x_828_; 
v___x_827_ = 8388608ULL;
v___x_828_ = lean_uint64_dec_eq(v___y_825_, v___x_827_);
if (v___x_828_ == 0)
{
uint32_t v___x_829_; 
v___x_829_ = lean_uint64_to_uint32(v___y_825_);
if (v___y_824_ == 0)
{
uint32_t v___x_830_; 
v___x_830_ = 0;
v___y_816_ = v___x_829_;
v___y_817_ = v___y_823_;
v___y_818_ = v___x_830_;
goto v___jp_815_;
}
else
{
uint32_t v___x_831_; 
v___x_831_ = 2147483648;
v___y_816_ = v___x_829_;
v___y_817_ = v___y_823_;
v___y_818_ = v___x_831_;
goto v___jp_815_;
}
}
else
{
if (v___y_824_ == 0)
{
uint32_t v___x_832_; 
v___x_832_ = 0;
v___y_791_ = v___x_832_;
goto v___jp_790_;
}
else
{
uint32_t v___x_833_; 
v___x_833_ = 2147483648;
v___y_791_ = v___x_833_;
goto v___jp_790_;
}
}
}
else
{
if (v___y_824_ == 0)
{
uint32_t v___x_834_; 
v___x_834_ = 0;
return v___x_834_;
}
else
{
uint32_t v___x_835_; 
v___x_835_ = 2147483648;
return v___x_835_;
}
}
}
v___jp_836_:
{
if (v___y_837_ == 0)
{
if (v___y_838_ == 0)
{
uint32_t v___x_839_; 
v___x_839_ = 0;
return v___x_839_;
}
else
{
uint32_t v___x_840_; 
v___x_840_ = 2147483648;
return v___x_840_;
}
}
else
{
if (v___y_838_ == 0)
{
uint32_t v___x_841_; 
v___x_841_ = 2147483648;
return v___x_841_;
}
else
{
uint32_t v___x_842_; 
v___x_842_ = 0;
return v___x_842_;
}
}
}
v___jp_845_:
{
if (v___y_846_ == 0)
{
float v___x_847_; 
v___x_847_ = lean_float32_of_bits(v___y_689_);
v___y_777_ = v___x_847_;
goto v___jp_776_;
}
else
{
uint32_t v___x_848_; uint32_t v___x_849_; uint32_t v___x_850_; uint32_t v___x_851_; float v___x_852_; lean_object* v___x_853_; lean_object* v___x_854_; lean_object* v___x_855_; float v___x_856_; float v___x_857_; 
v___x_848_ = 8388607;
v___x_849_ = lean_uint32_land(v___y_689_, v___x_848_);
v___x_850_ = 8388608;
v___x_851_ = lean_uint32_lor(v___x_849_, v___x_850_);
v___x_852_ = lean_uint32_to_float32(v___x_851_);
v___x_853_ = lp_competition_R2W01b_scaleTable;
v___x_854_ = lean_uint32_to_nat(v___x_844_);
v___x_855_ = lean_array_fget_borrowed(v___x_853_, v___x_854_);
lean_dec(v___x_854_);
v___x_856_ = lean_unbox_float32(v___x_855_);
v___x_857_ = lean_float32_mul(v___x_852_, v___x_856_);
v___y_777_ = v___x_857_;
goto v___jp_776_;
}
}
v___jp_859_:
{
uint32_t v___x_864_; uint32_t v___x_865_; uint32_t v___x_866_; uint32_t v___x_867_; uint32_t v___x_868_; 
v___x_864_ = lean_uint32_land(v___y_861_, v___x_858_);
v___x_865_ = lean_uint32_shift_left(v___x_864_, v___x_843_);
v___x_866_ = lean_uint32_lor(v___y_863_, v___x_865_);
v___x_867_ = lean_uint32_land(v___y_862_, v___y_860_);
v___x_868_ = lean_uint32_lor(v___x_866_, v___x_867_);
return v___x_868_;
}
v___jp_869_:
{
if (v___y_871_ == 0)
{
uint32_t v___x_874_; 
v___x_874_ = 0;
v___y_860_ = v___y_870_;
v___y_861_ = v___y_872_;
v___y_862_ = v___y_873_;
v___y_863_ = v___x_874_;
goto v___jp_859_;
}
else
{
uint32_t v___x_875_; 
v___x_875_ = 2147483648;
v___y_860_ = v___y_870_;
v___y_861_ = v___y_872_;
v___y_862_ = v___y_873_;
v___y_863_ = v___x_875_;
goto v___jp_859_;
}
}
v___jp_876_:
{
uint64_t v___x_882_; uint64_t v_encodedExponent_883_; uint32_t v___x_884_; uint64_t v___x_885_; uint8_t v___x_886_; 
v___x_882_ = 171ULL;
v_encodedExponent_883_ = lean_uint64_sub(v___y_877_, v___x_882_);
v___x_884_ = lean_uint64_to_uint32(v_encodedExponent_883_);
v___x_885_ = 8388608ULL;
v___x_886_ = lean_uint64_dec_lt(v___y_881_, v___x_885_);
if (v___x_886_ == 0)
{
uint64_t v___x_887_; uint32_t v___x_888_; 
v___x_887_ = lean_uint64_sub(v___y_881_, v___x_885_);
v___x_888_ = lean_uint64_to_uint32(v___x_887_);
v___y_870_ = v___y_878_;
v___y_871_ = v___y_879_;
v___y_872_ = v___x_884_;
v___y_873_ = v___x_888_;
goto v___jp_869_;
}
else
{
uint32_t v___x_889_; 
v___x_889_ = lean_uint64_to_uint32(v___y_880_);
v___y_870_ = v___y_878_;
v___y_871_ = v___y_879_;
v___y_872_ = v___x_884_;
v___y_873_ = v___x_889_;
goto v___jp_869_;
}
}
v___jp_890_:
{
uint64_t v___x_897_; uint8_t v___x_898_; 
v___x_897_ = 425ULL;
v___x_898_ = lean_uint64_dec_lt(v___x_897_, v___y_896_);
if (v___x_898_ == 0)
{
if (v___y_894_ == 0)
{
v___y_877_ = v___y_896_;
v___y_878_ = v___y_891_;
v___y_879_ = v___y_893_;
v___y_880_ = v___y_895_;
v___y_881_ = v___y_892_;
goto v___jp_876_;
}
else
{
uint64_t v___x_899_; 
v___x_899_ = 8388608ULL;
v___y_877_ = v___y_896_;
v___y_878_ = v___y_891_;
v___y_879_ = v___y_893_;
v___y_880_ = v___y_895_;
v___y_881_ = v___x_899_;
goto v___jp_876_;
}
}
else
{
if (v___y_893_ == 0)
{
uint32_t v___x_900_; 
v___x_900_ = 2139095040;
return v___x_900_;
}
else
{
uint32_t v___x_901_; 
v___x_901_ = 4286578688;
return v___x_901_;
}
}
}
v___jp_902_:
{
uint64_t v___x_908_; uint8_t v_carry_909_; 
v___x_908_ = 16777216ULL;
v_carry_909_ = lean_uint64_dec_eq(v___y_907_, v___x_908_);
if (v_carry_909_ == 0)
{
v___y_891_ = v___y_904_;
v___y_892_ = v___y_907_;
v___y_893_ = v___y_905_;
v___y_894_ = v_carry_909_;
v___y_895_ = v___y_906_;
v___y_896_ = v___y_903_;
goto v___jp_890_;
}
else
{
uint64_t v___x_910_; uint64_t v___x_911_; 
v___x_910_ = 1ULL;
v___x_911_ = lean_uint64_add(v___y_903_, v___x_910_);
v___y_891_ = v___y_904_;
v___y_892_ = v___y_907_;
v___y_893_ = v___y_905_;
v___y_894_ = v_carry_909_;
v___y_895_ = v___y_906_;
v___y_896_ = v___x_911_;
goto v___jp_890_;
}
}
v___jp_912_:
{
uint64_t v_position_919_; uint64_t v___x_920_; uint8_t v___x_921_; 
v_position_919_ = lean_uint64_add(v___y_918_, v___y_913_);
v___x_920_ = 172ULL;
v___x_921_ = lean_uint64_dec_lt(v_position_919_, v___x_920_);
if (v___x_921_ == 0)
{
uint64_t v___x_922_; uint8_t v___x_923_; 
v___x_922_ = 23ULL;
v___x_923_ = lean_uint64_dec_lt(v___y_918_, v___x_922_);
if (v___x_923_ == 0)
{
uint64_t v___x_924_; uint8_t v___x_925_; 
v___x_924_ = lean_uint64_sub(v___y_918_, v___x_922_);
v___x_925_ = lean_uint64_dec_eq(v___x_924_, v___y_916_);
if (v___x_925_ == 0)
{
uint64_t v___x_926_; uint8_t v___x_927_; 
v___x_926_ = 64ULL;
v___x_927_ = lean_uint64_dec_lt(v___x_924_, v___x_926_);
if (v___x_927_ == 0)
{
uint8_t v___x_928_; 
v___x_928_ = lean_uint64_dec_eq(v___x_924_, v___x_926_);
if (v___x_928_ == 0)
{
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v___y_916_;
goto v___jp_902_;
}
else
{
uint64_t v___x_929_; uint8_t v___x_930_; 
v___x_929_ = 9223372036854775808ULL;
v___x_930_ = lean_uint64_dec_lt(v___x_929_, v___y_917_);
if (v___x_930_ == 0)
{
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v___y_916_;
goto v___jp_902_;
}
else
{
uint64_t v___x_931_; 
v___x_931_ = 1ULL;
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v___x_931_;
goto v___jp_902_;
}
}
}
else
{
uint64_t v_quotient_932_; uint64_t v___x_933_; uint64_t v___x_934_; uint64_t v___x_935_; uint64_t v_remainder_936_; uint64_t v___x_937_; uint64_t v_half_938_; uint8_t v___x_939_; 
v_quotient_932_ = lean_uint64_shift_right(v___y_917_, v___x_924_);
v___x_933_ = 1ULL;
v___x_934_ = lean_uint64_shift_left(v___x_933_, v___x_924_);
v___x_935_ = lean_uint64_sub(v___x_934_, v___x_933_);
v_remainder_936_ = lean_uint64_land(v___y_917_, v___x_935_);
v___x_937_ = lean_uint64_sub(v___x_924_, v___x_933_);
v_half_938_ = lean_uint64_shift_left(v___x_933_, v___x_937_);
v___x_939_ = lean_uint64_dec_lt(v_remainder_936_, v_half_938_);
if (v___x_939_ == 0)
{
uint8_t v___x_940_; 
v___x_940_ = lean_uint64_dec_lt(v_half_938_, v_remainder_936_);
if (v___x_940_ == 0)
{
uint64_t v___x_941_; uint8_t v___x_942_; 
v___x_941_ = lean_uint64_land(v_quotient_932_, v___x_933_);
v___x_942_ = lean_uint64_dec_eq(v___x_941_, v___y_916_);
if (v___x_942_ == 0)
{
uint64_t v___x_943_; 
v___x_943_ = lean_uint64_add(v_quotient_932_, v___x_933_);
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v___x_943_;
goto v___jp_902_;
}
else
{
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v_quotient_932_;
goto v___jp_902_;
}
}
else
{
uint64_t v___x_944_; 
v___x_944_ = lean_uint64_add(v_quotient_932_, v___x_933_);
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v___x_944_;
goto v___jp_902_;
}
}
else
{
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v_quotient_932_;
goto v___jp_902_;
}
}
}
else
{
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v___y_917_;
goto v___jp_902_;
}
}
else
{
uint64_t v___x_945_; uint64_t v___x_946_; 
v___x_945_ = lean_uint64_sub(v___x_922_, v___y_918_);
v___x_946_ = lean_uint64_shift_left(v___y_917_, v___x_945_);
v___y_903_ = v_position_919_;
v___y_904_ = v___y_914_;
v___y_905_ = v___y_915_;
v___y_906_ = v___y_916_;
v___y_907_ = v___x_946_;
goto v___jp_902_;
}
}
else
{
uint64_t v___x_947_; uint8_t v___x_948_; 
v___x_947_ = 149ULL;
v___x_948_ = lean_uint64_dec_lt(v___y_913_, v___x_947_);
if (v___x_948_ == 0)
{
uint64_t v___x_949_; uint64_t v___x_950_; 
v___x_949_ = lean_uint64_sub(v___y_913_, v___x_947_);
v___x_950_ = lean_uint64_shift_left(v___y_917_, v___x_949_);
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v___x_950_;
goto v___jp_800_;
}
else
{
uint64_t v___x_951_; uint8_t v___x_952_; 
v___x_951_ = lean_uint64_sub(v___x_947_, v___y_913_);
v___x_952_ = lean_uint64_dec_eq(v___x_951_, v___y_916_);
if (v___x_952_ == 0)
{
uint64_t v___x_953_; uint8_t v___x_954_; 
v___x_953_ = 64ULL;
v___x_954_ = lean_uint64_dec_lt(v___x_951_, v___x_953_);
if (v___x_954_ == 0)
{
uint8_t v___x_955_; 
v___x_955_ = lean_uint64_dec_eq(v___x_951_, v___x_953_);
if (v___x_955_ == 0)
{
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v___y_916_;
goto v___jp_800_;
}
else
{
uint64_t v___x_956_; uint8_t v___x_957_; 
v___x_956_ = 9223372036854775808ULL;
v___x_957_ = lean_uint64_dec_lt(v___x_956_, v___y_917_);
if (v___x_957_ == 0)
{
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v___y_916_;
goto v___jp_800_;
}
else
{
uint64_t v___x_958_; 
v___x_958_ = 1ULL;
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v___x_958_;
goto v___jp_800_;
}
}
}
else
{
uint64_t v_quotient_959_; uint64_t v___x_960_; uint64_t v___x_961_; uint64_t v___x_962_; uint64_t v_remainder_963_; uint64_t v___x_964_; uint64_t v_half_965_; uint8_t v___x_966_; 
v_quotient_959_ = lean_uint64_shift_right(v___y_917_, v___x_951_);
v___x_960_ = 1ULL;
v___x_961_ = lean_uint64_shift_left(v___x_960_, v___x_951_);
v___x_962_ = lean_uint64_sub(v___x_961_, v___x_960_);
v_remainder_963_ = lean_uint64_land(v___y_917_, v___x_962_);
v___x_964_ = lean_uint64_sub(v___x_951_, v___x_960_);
v_half_965_ = lean_uint64_shift_left(v___x_960_, v___x_964_);
v___x_966_ = lean_uint64_dec_lt(v_remainder_963_, v_half_965_);
if (v___x_966_ == 0)
{
uint8_t v___x_967_; 
v___x_967_ = lean_uint64_dec_lt(v_half_965_, v_remainder_963_);
if (v___x_967_ == 0)
{
uint64_t v___x_968_; uint8_t v___x_969_; 
v___x_968_ = lean_uint64_land(v_quotient_959_, v___x_960_);
v___x_969_ = lean_uint64_dec_eq(v___x_968_, v___y_916_);
if (v___x_969_ == 0)
{
uint64_t v___x_970_; 
v___x_970_ = lean_uint64_add(v_quotient_959_, v___x_960_);
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v___x_970_;
goto v___jp_800_;
}
else
{
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v_quotient_959_;
goto v___jp_800_;
}
}
else
{
uint64_t v___x_971_; 
v___x_971_ = lean_uint64_add(v_quotient_959_, v___x_960_);
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v___x_971_;
goto v___jp_800_;
}
}
else
{
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v_quotient_959_;
goto v___jp_800_;
}
}
}
else
{
v___y_801_ = v___y_914_;
v___y_802_ = v___y_915_;
v___y_803_ = v___y_916_;
v___y_804_ = v___y_917_;
goto v___jp_800_;
}
}
}
}
v___jp_972_:
{
uint64_t v___x_980_; uint64_t v___x_981_; uint8_t v___x_982_; 
v___x_980_ = 1ULL;
v___x_981_ = lean_uint64_shift_right(v___y_976_, v___x_980_);
v___x_982_ = lean_uint64_dec_eq(v___x_981_, v___y_977_);
if (v___x_982_ == 0)
{
uint64_t v___x_983_; 
v___x_983_ = lean_uint64_add(v___y_979_, v___x_980_);
v___y_913_ = v___y_973_;
v___y_914_ = v___y_974_;
v___y_915_ = v___y_975_;
v___y_916_ = v___y_977_;
v___y_917_ = v___y_978_;
v___y_918_ = v___x_983_;
goto v___jp_912_;
}
else
{
v___y_913_ = v___y_973_;
v___y_914_ = v___y_974_;
v___y_915_ = v___y_975_;
v___y_916_ = v___y_977_;
v___y_917_ = v___y_978_;
v___y_918_ = v___y_979_;
goto v___jp_912_;
}
}
v___jp_984_:
{
uint64_t v___x_994_; uint8_t v___x_995_; 
v___x_994_ = lean_uint64_shift_right(v___y_992_, v___y_988_);
v___x_995_ = lean_uint64_dec_eq(v___x_994_, v___y_990_);
if (v___x_995_ == 0)
{
uint64_t v___x_996_; 
v___x_996_ = lean_uint64_add(v___y_985_, v___y_988_);
v___y_973_ = v___y_986_;
v___y_974_ = v___y_987_;
v___y_975_ = v___y_989_;
v___y_976_ = v___y_993_;
v___y_977_ = v___y_990_;
v___y_978_ = v___y_991_;
v___y_979_ = v___x_996_;
goto v___jp_972_;
}
else
{
v___y_973_ = v___y_986_;
v___y_974_ = v___y_987_;
v___y_975_ = v___y_989_;
v___y_976_ = v___y_993_;
v___y_977_ = v___y_990_;
v___y_978_ = v___y_991_;
v___y_979_ = v___y_985_;
goto v___jp_972_;
}
}
v___jp_997_:
{
uint64_t v___x_1005_; uint64_t v___x_1006_; uint8_t v___x_1007_; 
v___x_1005_ = 2ULL;
v___x_1006_ = lean_uint64_shift_right(v___y_1003_, v___x_1005_);
v___x_1007_ = lean_uint64_dec_eq(v___x_1006_, v___y_1001_);
if (v___x_1007_ == 0)
{
v___y_985_ = v___y_1004_;
v___y_986_ = v___y_998_;
v___y_987_ = v___y_999_;
v___y_988_ = v___x_1005_;
v___y_989_ = v___y_1000_;
v___y_990_ = v___y_1001_;
v___y_991_ = v___y_1002_;
v___y_992_ = v___y_1003_;
v___y_993_ = v___x_1006_;
goto v___jp_984_;
}
else
{
v___y_985_ = v___y_1004_;
v___y_986_ = v___y_998_;
v___y_987_ = v___y_999_;
v___y_988_ = v___x_1005_;
v___y_989_ = v___y_1000_;
v___y_990_ = v___y_1001_;
v___y_991_ = v___y_1002_;
v___y_992_ = v___y_1003_;
v___y_993_ = v___y_1003_;
goto v___jp_984_;
}
}
v___jp_1008_:
{
uint64_t v___x_1018_; uint8_t v___x_1019_; 
v___x_1018_ = lean_uint64_shift_right(v___y_1015_, v___y_1009_);
v___x_1019_ = lean_uint64_dec_eq(v___x_1018_, v___y_1014_);
if (v___x_1019_ == 0)
{
uint64_t v___x_1020_; 
v___x_1020_ = lean_uint64_add(v___y_1011_, v___y_1009_);
v___y_998_ = v___y_1010_;
v___y_999_ = v___y_1012_;
v___y_1000_ = v___y_1013_;
v___y_1001_ = v___y_1014_;
v___y_1002_ = v___y_1016_;
v___y_1003_ = v___y_1017_;
v___y_1004_ = v___x_1020_;
goto v___jp_997_;
}
else
{
v___y_998_ = v___y_1010_;
v___y_999_ = v___y_1012_;
v___y_1000_ = v___y_1013_;
v___y_1001_ = v___y_1014_;
v___y_1002_ = v___y_1016_;
v___y_1003_ = v___y_1017_;
v___y_1004_ = v___y_1011_;
goto v___jp_997_;
}
}
v___jp_1021_:
{
uint64_t v___x_1029_; uint64_t v___x_1030_; uint8_t v___x_1031_; 
v___x_1029_ = 4ULL;
v___x_1030_ = lean_uint64_shift_right(v___y_1027_, v___x_1029_);
v___x_1031_ = lean_uint64_dec_eq(v___x_1030_, v___y_1025_);
if (v___x_1031_ == 0)
{
v___y_1009_ = v___x_1029_;
v___y_1010_ = v___y_1022_;
v___y_1011_ = v___y_1028_;
v___y_1012_ = v___y_1023_;
v___y_1013_ = v___y_1024_;
v___y_1014_ = v___y_1025_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1026_;
v___y_1017_ = v___x_1030_;
goto v___jp_1008_;
}
else
{
v___y_1009_ = v___x_1029_;
v___y_1010_ = v___y_1022_;
v___y_1011_ = v___y_1028_;
v___y_1012_ = v___y_1023_;
v___y_1013_ = v___y_1024_;
v___y_1014_ = v___y_1025_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1026_;
v___y_1017_ = v___y_1027_;
goto v___jp_1008_;
}
}
v___jp_1032_:
{
uint64_t v___x_1042_; uint8_t v___x_1043_; 
v___x_1042_ = lean_uint64_shift_right(v___y_1033_, v___y_1035_);
v___x_1043_ = lean_uint64_dec_eq(v___x_1042_, v___y_1038_);
if (v___x_1043_ == 0)
{
uint64_t v___x_1044_; 
v___x_1044_ = lean_uint64_add(v___y_1040_, v___y_1035_);
v___y_1022_ = v___y_1034_;
v___y_1023_ = v___y_1036_;
v___y_1024_ = v___y_1037_;
v___y_1025_ = v___y_1038_;
v___y_1026_ = v___y_1039_;
v___y_1027_ = v___y_1041_;
v___y_1028_ = v___x_1044_;
goto v___jp_1021_;
}
else
{
v___y_1022_ = v___y_1034_;
v___y_1023_ = v___y_1036_;
v___y_1024_ = v___y_1037_;
v___y_1025_ = v___y_1038_;
v___y_1026_ = v___y_1039_;
v___y_1027_ = v___y_1041_;
v___y_1028_ = v___y_1040_;
goto v___jp_1021_;
}
}
v___jp_1045_:
{
uint64_t v___x_1053_; uint64_t v___x_1054_; uint8_t v___x_1055_; 
v___x_1053_ = 8ULL;
v___x_1054_ = lean_uint64_shift_right(v___y_1046_, v___x_1053_);
v___x_1055_ = lean_uint64_dec_eq(v___x_1054_, v___y_1050_);
if (v___x_1055_ == 0)
{
v___y_1033_ = v___y_1046_;
v___y_1034_ = v___y_1047_;
v___y_1035_ = v___x_1053_;
v___y_1036_ = v___y_1048_;
v___y_1037_ = v___y_1049_;
v___y_1038_ = v___y_1050_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___x_1054_;
goto v___jp_1032_;
}
else
{
v___y_1033_ = v___y_1046_;
v___y_1034_ = v___y_1047_;
v___y_1035_ = v___x_1053_;
v___y_1036_ = v___y_1048_;
v___y_1037_ = v___y_1049_;
v___y_1038_ = v___y_1050_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___y_1046_;
goto v___jp_1032_;
}
}
v___jp_1056_:
{
uint64_t v___x_1066_; uint8_t v___x_1067_; 
v___x_1066_ = lean_uint64_shift_right(v___y_1064_, v___y_1057_);
v___x_1067_ = lean_uint64_dec_eq(v___x_1066_, v___y_1062_);
if (v___x_1067_ == 0)
{
uint64_t v___x_1068_; 
v___x_1068_ = lean_uint64_add(v___y_1059_, v___y_1057_);
v___y_1046_ = v___y_1065_;
v___y_1047_ = v___y_1058_;
v___y_1048_ = v___y_1060_;
v___y_1049_ = v___y_1061_;
v___y_1050_ = v___y_1062_;
v___y_1051_ = v___y_1063_;
v___y_1052_ = v___x_1068_;
goto v___jp_1045_;
}
else
{
v___y_1046_ = v___y_1065_;
v___y_1047_ = v___y_1058_;
v___y_1048_ = v___y_1060_;
v___y_1049_ = v___y_1061_;
v___y_1050_ = v___y_1062_;
v___y_1051_ = v___y_1063_;
v___y_1052_ = v___y_1059_;
goto v___jp_1045_;
}
}
v___jp_1069_:
{
uint64_t v___x_1077_; uint64_t v___x_1078_; uint8_t v___x_1079_; 
v___x_1077_ = 16ULL;
v___x_1078_ = lean_uint64_shift_right(v___y_1075_, v___x_1077_);
v___x_1079_ = lean_uint64_dec_eq(v___x_1078_, v___y_1073_);
if (v___x_1079_ == 0)
{
v___y_1057_ = v___x_1077_;
v___y_1058_ = v___y_1070_;
v___y_1059_ = v___y_1076_;
v___y_1060_ = v___y_1071_;
v___y_1061_ = v___y_1072_;
v___y_1062_ = v___y_1073_;
v___y_1063_ = v___y_1074_;
v___y_1064_ = v___y_1075_;
v___y_1065_ = v___x_1078_;
goto v___jp_1056_;
}
else
{
v___y_1057_ = v___x_1077_;
v___y_1058_ = v___y_1070_;
v___y_1059_ = v___y_1076_;
v___y_1060_ = v___y_1071_;
v___y_1061_ = v___y_1072_;
v___y_1062_ = v___y_1073_;
v___y_1063_ = v___y_1074_;
v___y_1064_ = v___y_1075_;
v___y_1065_ = v___y_1075_;
goto v___jp_1056_;
}
}
v___jp_1080_:
{
uint64_t v___x_1088_; uint8_t v___x_1089_; 
v___x_1088_ = lean_uint64_shift_right(v___y_1086_, v___y_1082_);
v___x_1089_ = lean_uint64_dec_eq(v___x_1088_, v___y_1085_);
if (v___x_1089_ == 0)
{
v___y_1070_ = v___y_1081_;
v___y_1071_ = v___y_1083_;
v___y_1072_ = v___y_1084_;
v___y_1073_ = v___y_1085_;
v___y_1074_ = v___y_1086_;
v___y_1075_ = v___y_1087_;
v___y_1076_ = v___y_1082_;
goto v___jp_1069_;
}
else
{
v___y_1070_ = v___y_1081_;
v___y_1071_ = v___y_1083_;
v___y_1072_ = v___y_1084_;
v___y_1073_ = v___y_1085_;
v___y_1074_ = v___y_1086_;
v___y_1075_ = v___y_1087_;
v___y_1076_ = v___y_1085_;
goto v___jp_1069_;
}
}
v___jp_1090_:
{
uint64_t v___x_1095_; uint8_t v___x_1096_; 
v___x_1095_ = 0ULL;
v___x_1096_ = lean_uint64_dec_eq(v___y_1094_, v___x_1095_);
if (v___x_1096_ == 0)
{
uint64_t v___x_1097_; uint64_t v___x_1098_; uint8_t v___x_1099_; 
v___x_1097_ = 32ULL;
v___x_1098_ = lean_uint64_shift_right(v___y_1094_, v___x_1097_);
v___x_1099_ = lean_uint64_dec_eq(v___x_1098_, v___x_1095_);
if (v___x_1099_ == 0)
{
v___y_1081_ = v___y_1091_;
v___y_1082_ = v___x_1097_;
v___y_1083_ = v___y_1092_;
v___y_1084_ = v___y_1093_;
v___y_1085_ = v___x_1095_;
v___y_1086_ = v___y_1094_;
v___y_1087_ = v___x_1098_;
goto v___jp_1080_;
}
else
{
v___y_1081_ = v___y_1091_;
v___y_1082_ = v___x_1097_;
v___y_1083_ = v___y_1092_;
v___y_1084_ = v___y_1093_;
v___y_1085_ = v___x_1095_;
v___y_1086_ = v___y_1094_;
v___y_1087_ = v___y_1094_;
goto v___jp_1080_;
}
}
else
{
if (v___y_1093_ == 0)
{
uint32_t v___x_1100_; 
v___x_1100_ = 0;
return v___x_1100_;
}
else
{
uint32_t v___x_1101_; 
v___x_1101_ = 2147483648;
return v___x_1101_;
}
}
}
v___jp_1102_:
{
uint64_t v___x_1109_; uint64_t v___x_1110_; uint64_t v___x_1111_; uint8_t v___x_1112_; 
v___x_1109_ = lean_uint64_mul(v___y_1104_, v___y_1103_);
v___x_1110_ = lean_uint64_add(v___y_1105_, v___y_1108_);
v___x_1111_ = 281474976710656ULL;
v___x_1112_ = lean_uint64_dec_lt(v___x_1109_, v___x_1111_);
if (v___x_1112_ == 0)
{
v___y_1091_ = v___x_1110_;
v___y_1092_ = v___y_1106_;
v___y_1093_ = v___y_1107_;
v___y_1094_ = v___x_1109_;
goto v___jp_1090_;
}
else
{
uint64_t v___x_1113_; uint8_t v___x_1114_; 
v___x_1113_ = 123ULL;
v___x_1114_ = lean_uint64_dec_le(v___x_1110_, v___x_1113_);
if (v___x_1114_ == 0)
{
v___y_1091_ = v___x_1110_;
v___y_1092_ = v___y_1106_;
v___y_1093_ = v___y_1107_;
v___y_1094_ = v___x_1109_;
goto v___jp_1090_;
}
else
{
uint64_t v___x_1115_; uint8_t v___x_1116_; 
v___x_1115_ = 0ULL;
v___x_1116_ = lean_uint64_dec_eq(v___x_1109_, v___x_1115_);
if (v___x_1116_ == 0)
{
uint64_t v___x_1117_; uint64_t v___x_1118_; uint8_t v___x_1119_; 
v___x_1117_ = 149ULL;
v___x_1118_ = lean_uint64_sub(v___x_1117_, v___x_1110_);
v___x_1119_ = lean_uint64_dec_eq(v___x_1118_, v___x_1115_);
if (v___x_1119_ == 0)
{
uint64_t v___x_1120_; uint8_t v___x_1121_; 
v___x_1120_ = 64ULL;
v___x_1121_ = lean_uint64_dec_lt(v___x_1118_, v___x_1120_);
if (v___x_1121_ == 0)
{
uint8_t v___x_1122_; 
v___x_1122_ = lean_uint64_dec_eq(v___x_1118_, v___x_1120_);
if (v___x_1122_ == 0)
{
v___y_822_ = v___x_1115_;
v___y_823_ = v___y_1106_;
v___y_824_ = v___y_1107_;
v___y_825_ = v___x_1115_;
goto v___jp_821_;
}
else
{
uint64_t v___x_1123_; uint8_t v___x_1124_; 
v___x_1123_ = 9223372036854775808ULL;
v___x_1124_ = lean_uint64_dec_lt(v___x_1123_, v___x_1109_);
if (v___x_1124_ == 0)
{
v___y_822_ = v___x_1115_;
v___y_823_ = v___y_1106_;
v___y_824_ = v___y_1107_;
v___y_825_ = v___x_1115_;
goto v___jp_821_;
}
else
{
uint64_t v___x_1125_; 
v___x_1125_ = 1ULL;
v___y_822_ = v___x_1115_;
v___y_823_ = v___y_1106_;
v___y_824_ = v___y_1107_;
v___y_825_ = v___x_1125_;
goto v___jp_821_;
}
}
}
else
{
uint64_t v_quotient_1126_; uint64_t v___x_1127_; uint64_t v___x_1128_; uint64_t v___x_1129_; uint64_t v_remainder_1130_; uint64_t v___x_1131_; uint64_t v_half_1132_; uint8_t v___x_1133_; 
v_quotient_1126_ = lean_uint64_shift_right(v___x_1109_, v___x_1118_);
v___x_1127_ = 1ULL;
v___x_1128_ = lean_uint64_shift_left(v___x_1127_, v___x_1118_);
v___x_1129_ = lean_uint64_sub(v___x_1128_, v___x_1127_);
v_remainder_1130_ = lean_uint64_land(v___x_1109_, v___x_1129_);
v___x_1131_ = lean_uint64_sub(v___x_1118_, v___x_1127_);
v_half_1132_ = lean_uint64_shift_left(v___x_1127_, v___x_1131_);
v___x_1133_ = lean_uint64_dec_lt(v_remainder_1130_, v_half_1132_);
if (v___x_1133_ == 0)
{
uint8_t v___x_1134_; 
v___x_1134_ = lean_uint64_dec_lt(v_half_1132_, v_remainder_1130_);
if (v___x_1134_ == 0)
{
uint64_t v___x_1135_; uint8_t v___x_1136_; 
v___x_1135_ = lean_uint64_land(v_quotient_1126_, v___x_1127_);
v___x_1136_ = lean_uint64_dec_eq(v___x_1135_, v___x_1115_);
if (v___x_1136_ == 0)
{
uint64_t v___x_1137_; 
v___x_1137_ = lean_uint64_add(v_quotient_1126_, v___x_1127_);
v___y_822_ = v___x_1115_;
v___y_823_ = v___y_1106_;
v___y_824_ = v___y_1107_;
v___y_825_ = v___x_1137_;
goto v___jp_821_;
}
else
{
v___y_822_ = v___x_1115_;
v___y_823_ = v___y_1106_;
v___y_824_ = v___y_1107_;
v___y_825_ = v_quotient_1126_;
goto v___jp_821_;
}
}
else
{
uint64_t v___x_1138_; 
v___x_1138_ = lean_uint64_add(v_quotient_1126_, v___x_1127_);
v___y_822_ = v___x_1115_;
v___y_823_ = v___y_1106_;
v___y_824_ = v___y_1107_;
v___y_825_ = v___x_1138_;
goto v___jp_821_;
}
}
else
{
v___y_822_ = v___x_1115_;
v___y_823_ = v___y_1106_;
v___y_824_ = v___y_1107_;
v___y_825_ = v_quotient_1126_;
goto v___jp_821_;
}
}
}
else
{
v___y_822_ = v___x_1115_;
v___y_823_ = v___y_1106_;
v___y_824_ = v___y_1107_;
v___y_825_ = v___x_1109_;
goto v___jp_821_;
}
}
else
{
if (v___y_1107_ == 0)
{
uint32_t v___x_1139_; 
v___x_1139_ = 0;
return v___x_1139_;
}
else
{
uint32_t v___x_1140_; 
v___x_1140_ = 2147483648;
return v___x_1140_;
}
}
}
}
}
v___jp_1144_:
{
uint64_t v___x_1150_; uint64_t v___x_1151_; uint8_t v___x_1152_; 
v___x_1150_ = lean_uint32_to_uint64(v_ey_1143_);
v___x_1151_ = 0ULL;
v___x_1152_ = lean_uint64_dec_eq(v___x_1150_, v___x_1151_);
if (v___x_1152_ == 0)
{
uint64_t v___x_1153_; uint64_t v___x_1154_; 
v___x_1153_ = 1ULL;
v___x_1154_ = lean_uint64_sub(v___x_1150_, v___x_1153_);
v___y_1103_ = v___y_1145_;
v___y_1104_ = v___y_1146_;
v___y_1105_ = v___y_1149_;
v___y_1106_ = v___y_1147_;
v___y_1107_ = v___y_1148_;
v___y_1108_ = v___x_1154_;
goto v___jp_1102_;
}
else
{
v___y_1103_ = v___y_1145_;
v___y_1104_ = v___y_1146_;
v___y_1105_ = v___y_1149_;
v___y_1106_ = v___y_1147_;
v___y_1107_ = v___y_1148_;
v___y_1108_ = v___x_1151_;
goto v___jp_1102_;
}
}
v___jp_1155_:
{
uint64_t v___x_1160_; uint64_t v___x_1161_; uint8_t v___x_1162_; 
v___x_1160_ = lean_uint32_to_uint64(v_ex_1141_);
v___x_1161_ = 0ULL;
v___x_1162_ = lean_uint64_dec_eq(v___x_1160_, v___x_1161_);
if (v___x_1162_ == 0)
{
uint64_t v___x_1163_; uint64_t v___x_1164_; 
v___x_1163_ = 1ULL;
v___x_1164_ = lean_uint64_sub(v___x_1160_, v___x_1163_);
v___y_1145_ = v___y_1159_;
v___y_1146_ = v___y_1156_;
v___y_1147_ = v___y_1157_;
v___y_1148_ = v___y_1158_;
v___y_1149_ = v___x_1164_;
goto v___jp_1144_;
}
else
{
v___y_1145_ = v___y_1159_;
v___y_1146_ = v___y_1156_;
v___y_1147_ = v___y_1157_;
v___y_1148_ = v___y_1158_;
v___y_1149_ = v___x_1161_;
goto v___jp_1144_;
}
}
v___jp_1165_:
{
uint32_t v___x_1170_; uint8_t v___x_1171_; 
v___x_1170_ = 0;
v___x_1171_ = lean_uint32_dec_eq(v_ey_1143_, v___x_1170_);
if (v___x_1171_ == 0)
{
uint64_t v___x_1172_; uint64_t v___x_1173_; uint64_t v___x_1174_; 
v___x_1172_ = lean_uint32_to_uint64(v___y_1167_);
v___x_1173_ = 8388608ULL;
v___x_1174_ = lean_uint64_lor(v___x_1172_, v___x_1173_);
v___y_1156_ = v___y_1169_;
v___y_1157_ = v___y_1166_;
v___y_1158_ = v___y_1168_;
v___y_1159_ = v___x_1174_;
goto v___jp_1155_;
}
else
{
uint64_t v___x_1175_; 
v___x_1175_ = lean_uint32_to_uint64(v___y_1167_);
v___y_1156_ = v___y_1169_;
v___y_1157_ = v___y_1166_;
v___y_1158_ = v___y_1168_;
v___y_1159_ = v___x_1175_;
goto v___jp_1155_;
}
}
v___jp_1176_:
{
uint32_t v___x_1178_; uint32_t v_xFraction_1179_; uint32_t v_yFraction_1180_; uint32_t v___x_1181_; uint8_t v___x_1182_; 
v___x_1178_ = 8388607;
v_xFraction_1179_ = lean_uint32_land(v___y_689_, v___x_1178_);
v_yFraction_1180_ = lean_uint32_land(v___y_690_, v___x_1178_);
v___x_1181_ = 0;
v___x_1182_ = lean_uint32_dec_eq(v_ex_1141_, v___x_1181_);
if (v___x_1182_ == 0)
{
uint64_t v___x_1183_; uint64_t v___x_1184_; uint64_t v___x_1185_; 
v___x_1183_ = lean_uint32_to_uint64(v_xFraction_1179_);
v___x_1184_ = 8388608ULL;
v___x_1185_ = lean_uint64_lor(v___x_1183_, v___x_1184_);
v___y_1166_ = v___x_1178_;
v___y_1167_ = v_yFraction_1180_;
v___y_1168_ = v___y_1177_;
v___y_1169_ = v___x_1185_;
goto v___jp_1165_;
}
else
{
uint64_t v___x_1186_; 
v___x_1186_ = lean_uint32_to_uint64(v_xFraction_1179_);
v___y_1166_ = v___x_1178_;
v___y_1167_ = v_yFraction_1180_;
v___y_1168_ = v___y_1177_;
v___y_1169_ = v___x_1186_;
goto v___jp_1165_;
}
}
v___jp_1190_:
{
if (v___y_1192_ == 0)
{
v___y_1177_ = v___x_1189_;
goto v___jp_1176_;
}
else
{
v___y_1177_ = v___y_1191_;
goto v___jp_1176_;
}
}
v___jp_1193_:
{
if (v___y_1195_ == 0)
{
if (v___y_1196_ == 0)
{
v___y_1191_ = v___y_1194_;
v___y_1192_ = v___x_1189_;
goto v___jp_1190_;
}
else
{
v___y_1177_ = v___x_1189_;
goto v___jp_1176_;
}
}
else
{
v___y_1191_ = v___y_1194_;
v___y_1192_ = v___y_1196_;
goto v___jp_1190_;
}
}
v___jp_1197_:
{
uint32_t v___x_1200_; uint32_t v___x_1201_; uint32_t v___x_1202_; uint8_t v___x_1203_; 
v___x_1200_ = 2147483648;
v___x_1201_ = lean_uint32_land(v___y_690_, v___x_1200_);
v___x_1202_ = 0;
v___x_1203_ = lean_uint32_dec_eq(v___x_1201_, v___x_1202_);
if (v___x_1203_ == 0)
{
v___y_1194_ = v___y_1198_;
v___y_1195_ = v___y_1199_;
v___y_1196_ = v___x_1189_;
goto v___jp_1193_;
}
else
{
v___y_1194_ = v___y_1198_;
v___y_1195_ = v___y_1199_;
v___y_1196_ = v___y_1198_;
goto v___jp_1193_;
}
}
v___jp_1204_:
{
if (v___y_1205_ == 0)
{
uint32_t v___x_1206_; uint32_t v___x_1207_; uint32_t v___x_1208_; uint8_t v___x_1209_; 
v___x_1206_ = 2147483648;
v___x_1207_ = lean_uint32_land(v___y_689_, v___x_1206_);
v___x_1208_ = 0;
v___x_1209_ = lean_uint32_dec_eq(v___x_1207_, v___x_1208_);
if (v___x_1209_ == 0)
{
v___y_1198_ = v___y_1205_;
v___y_1199_ = v___x_1189_;
goto v___jp_1197_;
}
else
{
v___y_1198_ = v___y_1205_;
v___y_1199_ = v___y_1205_;
goto v___jp_1197_;
}
}
else
{
lean_object* v___x_1210_; lean_object* v___x_1211_; lean_object* v___x_1212_; uint32_t v___x_1213_; 
v___x_1210_ = lean_uint32_to_nat(v___y_689_);
v___x_1211_ = lean_uint32_to_nat(v___y_690_);
v___x_1212_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1210_, v___x_1211_);
v___x_1213_ = lean_uint32_of_nat(v___x_1212_);
lean_dec(v___x_1212_);
return v___x_1213_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_1242_, lean_object* v___y_1243_){
_start:
{
uint32_t v___y_5979__boxed_1244_; uint32_t v___y_5980__boxed_1245_; uint32_t v_res_1246_; lean_object* v_r_1247_; 
v___y_5979__boxed_1244_ = lean_unbox_uint32(v___y_1242_);
lean_dec(v___y_1242_);
v___y_5980__boxed_1245_ = lean_unbox_uint32(v___y_1243_);
lean_dec(v___y_1243_);
v_res_1246_ = lp_competition_main___lam__3(v___y_5979__boxed_1244_, v___y_5980__boxed_1245_);
v_r_1247_ = lean_box_uint32(v_res_1246_);
return v_r_1247_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1255_; lean_object* v___x_1256_; 
v___x_1255_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1256_ = lean_io_getenv(v___x_1255_);
if (lean_obj_tag(v___x_1256_) == 0)
{
lean_object* v___f_1257_; lean_object* v___f_1258_; lean_object* v___x_1259_; lean_object* v___x_1260_; lean_object* v___x_1261_; 
v___f_1257_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1258_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1259_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1260_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1261_ = lp_competition_Bench_runFull(v___f_1257_, v___f_1258_, v___x_1259_, v___x_1260_);
return v___x_1261_;
}
else
{
lean_object* v___f_1262_; lean_object* v___f_1263_; lean_object* v___x_1264_; lean_object* v___x_1265_; lean_object* v___x_1266_; 
lean_dec_ref_known(v___x_1256_, 1);
v___f_1262_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1263_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1264_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1265_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1266_ = lp_competition_Bench_Suite_run(v___f_1262_, v___f_1263_, v___x_1264_, v___x_1265_);
return v___x_1266_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1267_){
_start:
{
lean_object* v_res_1268_; 
v_res_1268_ = _lean_main();
return v_res_1268_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_MainFull(uint8_t builtin) {
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
  res = initialize_competition_MainFull(1 /* builtin */);
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
