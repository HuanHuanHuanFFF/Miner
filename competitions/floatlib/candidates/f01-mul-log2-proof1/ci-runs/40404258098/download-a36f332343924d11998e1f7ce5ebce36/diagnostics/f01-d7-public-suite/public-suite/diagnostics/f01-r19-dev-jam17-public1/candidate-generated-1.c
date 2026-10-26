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
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
uint32_t lp_competition_R19Base_FastMul_mul(uint32_t, uint32_t);
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
uint32_t lean_float32_to_uint32(float);
uint32_t lean_uint32_xor(uint32_t, uint32_t);
lean_object* lp_competition_R19Base_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_R19Base_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
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
static const lean_closure_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_R19Base_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_closure_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_R19Base_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
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
uint32_t v___y_10885__boxed_126_; uint32_t v___y_10886__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_10885__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_10886__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_main___lam__0(v___y_10885__boxed_126_, v___y_10886__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_130_, uint32_t v___y_131_){
_start:
{
uint32_t v___y_133_; uint32_t v___y_137_; uint32_t v___y_141_; uint32_t v___y_142_; uint32_t v___y_143_; uint32_t v___y_147_; uint64_t v___y_148_; uint8_t v___y_149_; uint64_t v___y_150_; uint32_t v___y_162_; uint32_t v___y_163_; uint32_t v___y_164_; uint32_t v___y_168_; uint64_t v___y_169_; uint8_t v___y_170_; uint64_t v___y_171_; uint8_t v___y_183_; uint8_t v___y_199_; uint8_t v___y_213_; uint8_t v___y_230_; float v___y_237_; float v___y_238_; float v___y_252_; uint8_t v___y_253_; float v___y_268_; uint32_t v___y_278_; uint32_t v___y_282_; uint32_t v___y_286_; uint32_t v___y_287_; uint32_t v___y_288_; uint64_t v___y_292_; uint32_t v___y_293_; uint8_t v___y_294_; uint64_t v___y_295_; uint32_t v___y_307_; uint32_t v___y_308_; uint32_t v___y_309_; uint32_t v___y_313_; uint64_t v___y_314_; uint8_t v___y_315_; uint64_t v___y_316_; uint8_t v___y_328_; uint8_t v___y_344_; uint8_t v___y_358_; uint8_t v___y_375_; float v___y_382_; float v___y_383_; float v___y_397_; uint8_t v___y_398_; float v___y_413_; uint32_t v___y_423_; uint32_t v___y_427_; uint32_t v___y_431_; uint32_t v___y_432_; uint32_t v___y_433_; uint8_t v___y_437_; uint64_t v___y_438_; uint32_t v___y_439_; uint64_t v___y_440_; uint32_t v___y_452_; uint32_t v___y_453_; uint32_t v___y_454_; uint8_t v___y_458_; uint64_t v___y_459_; uint32_t v___y_460_; uint64_t v___y_461_; uint8_t v___y_473_; uint8_t v___y_489_; uint8_t v___y_503_; uint8_t v___y_520_; float v___y_527_; float v___y_528_; float v___y_542_; uint8_t v___y_543_; float v___y_558_; uint32_t v___x_567_; uint32_t v___x_568_; uint8_t v___y_570_; uint8_t v___y_583_; uint8_t v___y_596_; uint32_t v___x_608_; uint32_t v___y_610_; uint32_t v___y_611_; uint32_t v___y_612_; uint32_t v___y_613_; uint32_t v___y_620_; uint8_t v___y_621_; uint32_t v___y_622_; uint32_t v___y_623_; uint64_t v___y_627_; uint32_t v___y_628_; uint8_t v___y_629_; uint64_t v___y_630_; uint64_t v___y_631_; uint32_t v___y_641_; uint64_t v___y_642_; uint8_t v___y_643_; uint8_t v___y_644_; uint64_t v___y_645_; uint64_t v___y_646_; uint64_t v___y_653_; uint32_t v___y_654_; uint8_t v___y_655_; uint64_t v___y_656_; uint64_t v___y_657_; uint64_t v___y_663_; uint32_t v___y_664_; uint64_t v___y_665_; uint8_t v___y_666_; uint64_t v___y_667_; uint64_t v___y_668_; uint64_t v___y_723_; uint32_t v___y_724_; uint64_t v___y_725_; uint8_t v___y_726_; uint64_t v___y_727_; uint64_t v___y_728_; uint64_t v___y_729_; uint64_t v___y_735_; uint64_t v___y_736_; uint64_t v___y_737_; uint32_t v___y_738_; uint8_t v___y_739_; uint64_t v___y_740_; uint64_t v___y_741_; uint64_t v___y_742_; uint64_t v___y_743_; uint64_t v___y_748_; uint64_t v___y_749_; uint32_t v___y_750_; uint64_t v___y_751_; uint8_t v___y_752_; uint64_t v___y_753_; uint64_t v___y_754_; uint64_t v___y_759_; uint64_t v___y_760_; uint64_t v___y_761_; uint32_t v___y_762_; uint8_t v___y_763_; uint64_t v___y_764_; uint64_t v___y_765_; uint64_t v___y_766_; uint64_t v___y_767_; uint64_t v___y_772_; uint64_t v___y_773_; uint32_t v___y_774_; uint64_t v___y_775_; uint8_t v___y_776_; uint64_t v___y_777_; uint64_t v___y_778_; uint64_t v___y_783_; uint64_t v___y_784_; uint64_t v___y_785_; uint64_t v___y_786_; uint32_t v___y_787_; uint8_t v___y_788_; uint64_t v___y_789_; uint64_t v___y_790_; uint64_t v___y_791_; uint64_t v___y_796_; uint64_t v___y_797_; uint32_t v___y_798_; uint64_t v___y_799_; uint8_t v___y_800_; uint64_t v___y_801_; uint64_t v___y_802_; uint64_t v___y_807_; uint64_t v___y_808_; uint64_t v___y_809_; uint32_t v___y_810_; uint8_t v___y_811_; uint64_t v___y_812_; uint64_t v___y_813_; uint64_t v___y_814_; uint64_t v___y_815_; uint64_t v___y_820_; uint32_t v___y_821_; uint64_t v___y_822_; uint8_t v___y_823_; uint64_t v___y_824_; uint64_t v___y_825_; uint64_t v___y_826_; uint64_t v___y_831_; uint64_t v___y_832_; uint32_t v___y_833_; uint8_t v___y_834_; uint64_t v___y_835_; uint64_t v___y_836_; uint64_t v___y_837_; uint64_t v___y_841_; uint32_t v___y_842_; uint8_t v___y_843_; uint64_t v___y_844_; uint64_t v___y_853_; uint32_t v___y_854_; uint8_t v___y_855_; uint64_t v___y_856_; uint64_t v___y_857_; uint64_t v___y_858_; uint32_t v___y_892_; uint32_t v___y_893_; uint32_t v___y_894_; uint32_t v___y_895_; uint32_t v___y_902_; uint32_t v___y_903_; uint8_t v___y_904_; uint32_t v___y_905_; uint64_t v___y_909_; uint32_t v___y_910_; uint8_t v___y_911_; uint64_t v___y_912_; uint64_t v___y_913_; uint8_t v___y_923_; uint64_t v___y_924_; uint64_t v___y_925_; uint32_t v___y_926_; uint8_t v___y_927_; uint64_t v___y_928_; uint64_t v___y_935_; uint32_t v___y_936_; uint64_t v___y_937_; uint8_t v___y_938_; uint64_t v___y_939_; uint64_t v___y_945_; uint64_t v___y_946_; uint32_t v___y_947_; uint64_t v___y_948_; uint8_t v___y_949_; uint64_t v___y_950_; uint64_t v___y_1005_; uint64_t v___y_1006_; uint64_t v___y_1007_; uint32_t v___y_1008_; uint64_t v___y_1009_; uint8_t v___y_1010_; uint64_t v___y_1011_; uint64_t v___y_1017_; uint64_t v___y_1018_; uint64_t v___y_1019_; uint64_t v___y_1020_; uint64_t v___y_1021_; uint32_t v___y_1022_; uint64_t v___y_1023_; uint8_t v___y_1024_; uint64_t v___y_1025_; uint64_t v___y_1030_; uint64_t v___y_1031_; uint64_t v___y_1032_; uint32_t v___y_1033_; uint64_t v___y_1034_; uint8_t v___y_1035_; uint64_t v___y_1036_; uint64_t v___y_1041_; uint64_t v___y_1042_; uint64_t v___y_1043_; uint64_t v___y_1044_; uint64_t v___y_1045_; uint32_t v___y_1046_; uint64_t v___y_1047_; uint8_t v___y_1048_; uint64_t v___y_1049_; uint64_t v___y_1054_; uint64_t v___y_1055_; uint32_t v___y_1056_; uint64_t v___y_1057_; uint64_t v___y_1058_; uint8_t v___y_1059_; uint64_t v___y_1060_; uint64_t v___y_1065_; uint64_t v___y_1066_; uint64_t v___y_1067_; uint64_t v___y_1068_; uint32_t v___y_1069_; uint64_t v___y_1070_; uint8_t v___y_1071_; uint64_t v___y_1072_; uint64_t v___y_1073_; uint64_t v___y_1078_; uint64_t v___y_1079_; uint32_t v___y_1080_; uint64_t v___y_1081_; uint8_t v___y_1082_; uint64_t v___y_1083_; uint64_t v___y_1084_; uint64_t v___y_1089_; uint64_t v___y_1090_; uint64_t v___y_1091_; uint32_t v___y_1092_; uint64_t v___y_1093_; uint64_t v___y_1094_; uint64_t v___y_1095_; uint8_t v___y_1096_; uint64_t v___y_1097_; uint64_t v___y_1102_; uint64_t v___y_1103_; uint32_t v___y_1104_; uint64_t v___y_1105_; uint64_t v___y_1106_; uint8_t v___y_1107_; uint64_t v___y_1108_; uint64_t v___y_1113_; uint64_t v___y_1114_; uint64_t v___y_1115_; uint32_t v___y_1116_; uint64_t v___y_1117_; uint8_t v___y_1118_; uint64_t v___y_1119_; uint64_t v___y_1123_; uint32_t v___y_1124_; uint64_t v___y_1125_; uint8_t v___y_1126_; uint64_t v___y_1135_; uint64_t v___y_1136_; uint32_t v___y_1137_; uint64_t v___y_1138_; uint8_t v___y_1139_; uint64_t v___y_1140_; uint32_t v___y_1174_; uint32_t v___y_1175_; uint32_t v___y_1176_; uint32_t v___y_1177_; uint8_t v___y_1184_; uint32_t v___y_1185_; uint32_t v___y_1186_; uint32_t v___y_1187_; uint64_t v___y_1191_; uint8_t v___y_1192_; uint64_t v___y_1193_; uint32_t v___y_1194_; uint64_t v___y_1195_; uint64_t v___y_1205_; uint8_t v___y_1206_; uint8_t v___y_1207_; uint64_t v___y_1208_; uint32_t v___y_1209_; uint64_t v___y_1210_; uint64_t v___y_1217_; uint8_t v___y_1218_; uint64_t v___y_1219_; uint32_t v___y_1220_; uint64_t v___y_1221_; uint64_t v___y_1227_; uint8_t v___y_1228_; uint64_t v___y_1229_; uint64_t v___y_1230_; uint32_t v___y_1231_; uint64_t v___y_1232_; uint64_t v___y_1287_; uint8_t v___y_1288_; uint64_t v___y_1289_; uint64_t v___y_1290_; uint64_t v___y_1291_; uint32_t v___y_1292_; uint64_t v___y_1293_; uint64_t v___y_1299_; uint64_t v___y_1300_; uint64_t v___y_1301_; uint8_t v___y_1302_; uint64_t v___y_1303_; uint64_t v___y_1304_; uint64_t v___y_1305_; uint32_t v___y_1306_; uint64_t v___y_1307_; uint64_t v___y_1312_; uint64_t v___y_1313_; uint8_t v___y_1314_; uint64_t v___y_1315_; uint64_t v___y_1316_; uint32_t v___y_1317_; uint64_t v___y_1318_; uint64_t v___y_1323_; uint64_t v___y_1324_; uint8_t v___y_1325_; uint64_t v___y_1326_; uint64_t v___y_1327_; uint64_t v___y_1328_; uint64_t v___y_1329_; uint32_t v___y_1330_; uint64_t v___y_1331_; uint64_t v___y_1336_; uint64_t v___y_1337_; uint8_t v___y_1338_; uint64_t v___y_1339_; uint64_t v___y_1340_; uint32_t v___y_1341_; uint64_t v___y_1342_; uint64_t v___y_1347_; uint8_t v___y_1348_; uint64_t v___y_1349_; uint64_t v___y_1350_; uint64_t v___y_1351_; uint64_t v___y_1352_; uint64_t v___y_1353_; uint32_t v___y_1354_; uint64_t v___y_1355_; uint64_t v___y_1360_; uint8_t v___y_1361_; uint64_t v___y_1362_; uint64_t v___y_1363_; uint64_t v___y_1364_; uint32_t v___y_1365_; uint64_t v___y_1366_; uint64_t v___y_1371_; uint64_t v___y_1372_; uint64_t v___y_1373_; uint8_t v___y_1374_; uint64_t v___y_1375_; uint64_t v___y_1376_; uint64_t v___y_1377_; uint32_t v___y_1378_; uint64_t v___y_1379_; uint64_t v___y_1384_; uint8_t v___y_1385_; uint64_t v___y_1386_; uint64_t v___y_1387_; uint64_t v___y_1388_; uint32_t v___y_1389_; uint64_t v___y_1390_; uint64_t v___y_1395_; uint8_t v___y_1396_; uint64_t v___y_1397_; uint64_t v___y_1398_; uint64_t v___y_1399_; uint32_t v___y_1400_; uint64_t v___y_1401_; uint64_t v___y_1405_; uint8_t v___y_1406_; uint64_t v___y_1407_; uint32_t v___y_1408_; uint64_t v___y_1417_; uint8_t v___y_1418_; uint64_t v___y_1419_; uint64_t v___y_1420_; uint32_t v___y_1421_; uint64_t v___y_1422_; uint32_t v_eu_1455_; uint32_t v___x_1456_; uint32_t v___x_1457_; uint32_t v___x_1458_; uint8_t v___x_1459_; 
v___x_567_ = 23;
v___x_568_ = lean_uint32_shift_right(v___y_130_, v___x_567_);
v___x_608_ = 255;
v_eu_1455_ = lean_uint32_land(v___x_568_, v___x_608_);
v___x_1456_ = 1;
v___x_1457_ = lean_uint32_sub(v_eu_1455_, v___x_1456_);
v___x_1458_ = 253;
v___x_1459_ = lean_uint32_dec_le(v___x_1457_, v___x_1458_);
if (v___x_1459_ == 0)
{
uint32_t v___x_1460_; uint32_t v_ey_1461_; uint64_t v___y_1463_; uint8_t v___y_1464_; uint64_t v___y_1465_; uint32_t v___y_1466_; uint64_t v___y_1467_; uint64_t v___y_1474_; uint8_t v___y_1475_; uint32_t v___y_1476_; uint64_t v___y_1477_; uint8_t v___y_1484_; uint32_t v___y_1485_; uint32_t v___y_1486_; uint64_t v___y_1487_; uint8_t v___y_1495_; uint32_t v___x_1505_; uint32_t v___x_1506_; uint8_t v___x_1507_; uint8_t v___y_1509_; uint8_t v___y_1510_; uint8_t v___y_1511_; uint8_t v___y_1513_; uint8_t v___y_1514_; uint8_t v___y_1520_; 
v___x_1460_ = lean_uint32_shift_right(v___y_131_, v___x_567_);
v_ey_1461_ = lean_uint32_land(v___x_1460_, v___x_608_);
v___x_1505_ = lean_uint32_add(v_eu_1455_, v_ey_1461_);
v___x_1506_ = 128;
v___x_1507_ = lean_uint32_dec_lt(v___x_1505_, v___x_1506_);
if (v___x_1507_ == 0)
{
uint32_t v___x_1529_; uint32_t v_a_1530_; uint32_t v___x_1531_; uint32_t v___x_1532_; uint8_t v___x_1533_; 
v___x_1529_ = 2147483647;
v_a_1530_ = lean_uint32_land(v___y_130_, v___x_1529_);
v___x_1531_ = 201326591;
v___x_1532_ = lean_uint32_sub(v_a_1530_, v___x_1456_);
v___x_1533_ = lean_uint32_dec_le(v___x_1531_, v___x_1532_);
if (v___x_1533_ == 0)
{
v___y_596_ = v___x_1533_;
goto v___jp_595_;
}
else
{
uint32_t v___x_1534_; uint8_t v___x_1535_; 
v___x_1534_ = 2139095040;
v___x_1535_ = lean_uint32_dec_lt(v_a_1530_, v___x_1534_);
v___y_596_ = v___x_1535_;
goto v___jp_595_;
}
}
else
{
uint32_t v___x_1536_; uint32_t v___x_1537_; uint8_t v___x_1538_; 
v___x_1536_ = 4278190080;
v___x_1537_ = lean_uint32_shift_left(v___y_130_, v___x_1456_);
v___x_1538_ = lean_uint32_dec_le(v___x_1536_, v___x_1537_);
if (v___x_1538_ == 0)
{
uint32_t v___x_1539_; uint8_t v___x_1540_; 
v___x_1539_ = lean_uint32_shift_left(v___y_131_, v___x_1456_);
v___x_1540_ = lean_uint32_dec_le(v___x_1536_, v___x_1539_);
v___y_1520_ = v___x_1540_;
goto v___jp_1519_;
}
else
{
v___y_1520_ = v___x_1538_;
goto v___jp_1519_;
}
}
v___jp_1462_:
{
uint64_t v___x_1468_; uint64_t v___x_1469_; uint8_t v___x_1470_; 
v___x_1468_ = lean_uint32_to_uint64(v_ey_1461_);
v___x_1469_ = 0ULL;
v___x_1470_ = lean_uint64_dec_eq(v___x_1468_, v___x_1469_);
if (v___x_1470_ == 0)
{
uint64_t v___x_1471_; uint64_t v___x_1472_; 
v___x_1471_ = 1ULL;
v___x_1472_ = lean_uint64_sub(v___x_1468_, v___x_1471_);
v___y_1417_ = v___y_1463_;
v___y_1418_ = v___y_1464_;
v___y_1419_ = v___y_1465_;
v___y_1420_ = v___y_1467_;
v___y_1421_ = v___y_1466_;
v___y_1422_ = v___x_1472_;
goto v___jp_1416_;
}
else
{
v___y_1417_ = v___y_1463_;
v___y_1418_ = v___y_1464_;
v___y_1419_ = v___y_1465_;
v___y_1420_ = v___y_1467_;
v___y_1421_ = v___y_1466_;
v___y_1422_ = v___x_1469_;
goto v___jp_1416_;
}
}
v___jp_1473_:
{
uint64_t v___x_1478_; uint64_t v___x_1479_; uint8_t v___x_1480_; 
v___x_1478_ = lean_uint32_to_uint64(v_eu_1455_);
v___x_1479_ = 0ULL;
v___x_1480_ = lean_uint64_dec_eq(v___x_1478_, v___x_1479_);
if (v___x_1480_ == 0)
{
uint64_t v___x_1481_; uint64_t v___x_1482_; 
v___x_1481_ = 1ULL;
v___x_1482_ = lean_uint64_sub(v___x_1478_, v___x_1481_);
v___y_1463_ = v___y_1474_;
v___y_1464_ = v___y_1475_;
v___y_1465_ = v___y_1477_;
v___y_1466_ = v___y_1476_;
v___y_1467_ = v___x_1482_;
goto v___jp_1462_;
}
else
{
v___y_1463_ = v___y_1474_;
v___y_1464_ = v___y_1475_;
v___y_1465_ = v___y_1477_;
v___y_1466_ = v___y_1476_;
v___y_1467_ = v___x_1479_;
goto v___jp_1462_;
}
}
v___jp_1483_:
{
uint32_t v___x_1488_; uint8_t v___x_1489_; 
v___x_1488_ = 0;
v___x_1489_ = lean_uint32_dec_eq(v_ey_1461_, v___x_1488_);
if (v___x_1489_ == 0)
{
uint64_t v___x_1490_; uint64_t v___x_1491_; uint64_t v___x_1492_; 
v___x_1490_ = lean_uint32_to_uint64(v___y_1485_);
v___x_1491_ = 8388608ULL;
v___x_1492_ = lean_uint64_lor(v___x_1490_, v___x_1491_);
v___y_1474_ = v___y_1487_;
v___y_1475_ = v___y_1484_;
v___y_1476_ = v___y_1486_;
v___y_1477_ = v___x_1492_;
goto v___jp_1473_;
}
else
{
uint64_t v___x_1493_; 
v___x_1493_ = lean_uint32_to_uint64(v___y_1485_);
v___y_1474_ = v___y_1487_;
v___y_1475_ = v___y_1484_;
v___y_1476_ = v___y_1486_;
v___y_1477_ = v___x_1493_;
goto v___jp_1473_;
}
}
v___jp_1494_:
{
uint32_t v___x_1496_; uint32_t v_xFraction_1497_; uint32_t v_yFraction_1498_; uint32_t v___x_1499_; uint8_t v___x_1500_; 
v___x_1496_ = 8388607;
v_xFraction_1497_ = lean_uint32_land(v___y_130_, v___x_1496_);
v_yFraction_1498_ = lean_uint32_land(v___y_131_, v___x_1496_);
v___x_1499_ = 0;
v___x_1500_ = lean_uint32_dec_eq(v_eu_1455_, v___x_1499_);
if (v___x_1500_ == 0)
{
uint64_t v___x_1501_; uint64_t v___x_1502_; uint64_t v___x_1503_; 
v___x_1501_ = lean_uint32_to_uint64(v_xFraction_1497_);
v___x_1502_ = 8388608ULL;
v___x_1503_ = lean_uint64_lor(v___x_1501_, v___x_1502_);
v___y_1484_ = v___y_1495_;
v___y_1485_ = v_yFraction_1498_;
v___y_1486_ = v___x_1496_;
v___y_1487_ = v___x_1503_;
goto v___jp_1483_;
}
else
{
uint64_t v___x_1504_; 
v___x_1504_ = lean_uint32_to_uint64(v_xFraction_1497_);
v___y_1484_ = v___y_1495_;
v___y_1485_ = v_yFraction_1498_;
v___y_1486_ = v___x_1496_;
v___y_1487_ = v___x_1504_;
goto v___jp_1483_;
}
}
v___jp_1508_:
{
if (v___y_1510_ == 0)
{
if (v___y_1511_ == 0)
{
v___y_1495_ = v___y_1509_;
goto v___jp_1494_;
}
else
{
v___y_1495_ = v___x_1507_;
goto v___jp_1494_;
}
}
else
{
if (v___y_1511_ == 0)
{
v___y_1495_ = v___x_1507_;
goto v___jp_1494_;
}
else
{
v___y_1495_ = v___y_1509_;
goto v___jp_1494_;
}
}
}
v___jp_1512_:
{
uint32_t v___x_1515_; uint32_t v___x_1516_; uint32_t v___x_1517_; uint8_t v___x_1518_; 
v___x_1515_ = 2147483648;
v___x_1516_ = lean_uint32_land(v___y_131_, v___x_1515_);
v___x_1517_ = 0;
v___x_1518_ = lean_uint32_dec_eq(v___x_1516_, v___x_1517_);
if (v___x_1518_ == 0)
{
v___y_1509_ = v___y_1513_;
v___y_1510_ = v___y_1514_;
v___y_1511_ = v___x_1507_;
goto v___jp_1508_;
}
else
{
v___y_1509_ = v___y_1513_;
v___y_1510_ = v___y_1514_;
v___y_1511_ = v___y_1513_;
goto v___jp_1508_;
}
}
v___jp_1519_:
{
if (v___y_1520_ == 0)
{
uint32_t v___x_1521_; uint32_t v___x_1522_; uint32_t v___x_1523_; uint8_t v___x_1524_; 
v___x_1521_ = 2147483648;
v___x_1522_ = lean_uint32_land(v___y_130_, v___x_1521_);
v___x_1523_ = 0;
v___x_1524_ = lean_uint32_dec_eq(v___x_1522_, v___x_1523_);
if (v___x_1524_ == 0)
{
v___y_1513_ = v___y_1520_;
v___y_1514_ = v___x_1507_;
goto v___jp_1512_;
}
else
{
v___y_1513_ = v___y_1520_;
v___y_1514_ = v___y_1520_;
goto v___jp_1512_;
}
}
else
{
lean_object* v___x_1525_; lean_object* v___x_1526_; lean_object* v___x_1527_; uint32_t v___x_1528_; 
v___x_1525_ = lean_uint32_to_nat(v___y_130_);
v___x_1526_ = lean_uint32_to_nat(v___y_131_);
v___x_1527_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1525_, v___x_1526_);
v___x_1528_ = lean_uint32_of_nat(v___x_1527_);
lean_dec(v___x_1527_);
return v___x_1528_;
}
}
}
else
{
uint32_t v___x_1541_; uint32_t v_ev_1542_; uint32_t v___y_1544_; uint8_t v___y_1545_; uint64_t v___y_1546_; uint64_t v___y_1547_; uint64_t v___y_1548_; uint32_t v___y_1555_; uint8_t v___y_1556_; uint64_t v___y_1557_; uint64_t v___y_1558_; uint32_t v___y_1565_; uint32_t v___y_1566_; uint8_t v___y_1567_; uint64_t v___y_1568_; uint8_t v___y_1576_; uint64_t v___y_1587_; uint32_t v___y_1588_; uint64_t v___y_1589_; uint8_t v___y_1590_; uint64_t v___y_1591_; uint32_t v___y_1598_; uint64_t v___y_1599_; uint8_t v___y_1600_; uint64_t v___y_1601_; uint32_t v___y_1608_; uint32_t v___y_1609_; uint8_t v___y_1610_; uint64_t v___y_1611_; uint8_t v___y_1619_; uint8_t v___y_1630_; uint8_t v___y_1631_; uint8_t v___y_1633_; uint8_t v___y_1634_; uint8_t v___y_1635_; uint8_t v___y_1637_; uint8_t v___y_1638_; uint8_t v___y_1644_; uint32_t v___x_1653_; uint8_t v___x_1654_; uint8_t v___y_1656_; uint8_t v___y_1657_; uint8_t v___y_1659_; uint8_t v___y_1660_; uint8_t v___y_1661_; uint8_t v___y_1663_; uint8_t v___y_1664_; uint8_t v___y_1670_; 
v___x_1541_ = lean_uint32_shift_right(v___y_131_, v___x_567_);
v_ev_1542_ = lean_uint32_land(v___x_1541_, v___x_608_);
v___x_1653_ = lean_uint32_sub(v_ev_1542_, v___x_1456_);
v___x_1654_ = lean_uint32_dec_le(v___x_1653_, v___x_1458_);
if (v___x_1654_ == 0)
{
uint32_t v___x_1679_; uint32_t v___x_1680_; uint8_t v___x_1681_; 
v___x_1679_ = lean_uint32_add(v_eu_1455_, v_ev_1542_);
v___x_1680_ = 128;
v___x_1681_ = lean_uint32_dec_lt(v___x_1679_, v___x_1680_);
if (v___x_1681_ == 0)
{
uint32_t v___x_1682_; uint32_t v_a_1683_; uint32_t v___x_1684_; uint32_t v___x_1685_; uint8_t v___x_1686_; 
v___x_1682_ = 2147483647;
v_a_1683_ = lean_uint32_land(v___y_130_, v___x_1682_);
v___x_1684_ = 201326591;
v___x_1685_ = lean_uint32_sub(v_a_1683_, v___x_1456_);
v___x_1686_ = lean_uint32_dec_le(v___x_1684_, v___x_1685_);
if (v___x_1686_ == 0)
{
v___y_583_ = v___x_1686_;
goto v___jp_582_;
}
else
{
uint32_t v___x_1687_; uint8_t v___x_1688_; 
v___x_1687_ = 2139095040;
v___x_1688_ = lean_uint32_dec_lt(v_a_1683_, v___x_1687_);
v___y_583_ = v___x_1688_;
goto v___jp_582_;
}
}
else
{
uint32_t v___x_1689_; uint32_t v___x_1690_; uint8_t v___x_1691_; 
v___x_1689_ = 4278190080;
v___x_1690_ = lean_uint32_shift_left(v___y_130_, v___x_1456_);
v___x_1691_ = lean_uint32_dec_le(v___x_1689_, v___x_1690_);
if (v___x_1691_ == 0)
{
uint32_t v___x_1692_; uint8_t v___x_1693_; 
v___x_1692_ = lean_uint32_shift_left(v___y_131_, v___x_1456_);
v___x_1693_ = lean_uint32_dec_le(v___x_1689_, v___x_1692_);
v___y_1644_ = v___x_1693_;
goto v___jp_1643_;
}
else
{
v___y_1644_ = v___x_1691_;
goto v___jp_1643_;
}
}
}
else
{
uint32_t v_s_1694_; uint32_t v___x_1695_; uint32_t v___x_1696_; uint32_t v___x_1697_; uint8_t v___x_1698_; 
v_s_1694_ = lean_uint32_add(v_eu_1455_, v_ev_1542_);
v___x_1695_ = 128;
v___x_1696_ = lean_uint32_sub(v_s_1694_, v___x_1695_);
v___x_1697_ = 252;
v___x_1698_ = lean_uint32_dec_le(v___x_1696_, v___x_1697_);
if (v___x_1698_ == 0)
{
uint8_t v___x_1699_; 
v___x_1699_ = lean_uint32_dec_lt(v_s_1694_, v___x_1695_);
if (v___x_1699_ == 0)
{
uint32_t v___x_1700_; uint32_t v_a_1701_; uint32_t v___x_1702_; uint32_t v___x_1703_; uint8_t v___x_1704_; 
v___x_1700_ = 2147483647;
v_a_1701_ = lean_uint32_land(v___y_130_, v___x_1700_);
v___x_1702_ = 201326591;
v___x_1703_ = lean_uint32_sub(v_a_1701_, v___x_1456_);
v___x_1704_ = lean_uint32_dec_le(v___x_1702_, v___x_1703_);
if (v___x_1704_ == 0)
{
v___y_570_ = v___x_1704_;
goto v___jp_569_;
}
else
{
uint32_t v___x_1705_; uint8_t v___x_1706_; 
v___x_1705_ = 2139095040;
v___x_1706_ = lean_uint32_dec_lt(v_a_1701_, v___x_1705_);
v___y_570_ = v___x_1706_;
goto v___jp_569_;
}
}
else
{
uint32_t v___x_1707_; uint32_t v___x_1708_; uint8_t v___x_1709_; 
v___x_1707_ = 4278190080;
v___x_1708_ = lean_uint32_shift_left(v___y_130_, v___x_1456_);
v___x_1709_ = lean_uint32_dec_le(v___x_1707_, v___x_1708_);
if (v___x_1709_ == 0)
{
uint32_t v___x_1710_; uint8_t v___x_1711_; 
v___x_1710_ = lean_uint32_shift_left(v___y_131_, v___x_1456_);
v___x_1711_ = lean_uint32_dec_le(v___x_1707_, v___x_1710_);
v___y_1670_ = v___x_1711_;
goto v___jp_1669_;
}
else
{
v___y_1670_ = v___x_1709_;
goto v___jp_1669_;
}
}
}
else
{
uint32_t v___x_1712_; uint32_t v___x_1713_; uint32_t v___x_1714_; uint32_t v___y_1716_; uint32_t v_a_1734_; uint32_t v___x_1735_; uint32_t v_b_1736_; uint64_t v___x_1737_; uint64_t v___x_1738_; uint64_t v_product_1739_; uint64_t v___x_1740_; uint64_t v___x_1741_; uint32_t v___x_1742_; uint64_t v___x_1743_; uint64_t v___x_1744_; uint64_t v___x_1745_; uint8_t v___x_1746_; 
v___x_1712_ = 8388607;
v___x_1713_ = lean_uint32_land(v___y_130_, v___x_1712_);
v___x_1714_ = 8388608;
v_a_1734_ = lean_uint32_lor(v___x_1713_, v___x_1714_);
v___x_1735_ = lean_uint32_land(v___y_131_, v___x_1712_);
v_b_1736_ = lean_uint32_lor(v___x_1735_, v___x_1714_);
v___x_1737_ = lean_uint32_to_uint64(v_a_1734_);
v___x_1738_ = lean_uint32_to_uint64(v_b_1736_);
v_product_1739_ = lean_uint64_mul(v___x_1737_, v___x_1738_);
v___x_1740_ = 17ULL;
v___x_1741_ = lean_uint64_shift_right(v_product_1739_, v___x_1740_);
v___x_1742_ = lean_uint64_to_uint32(v___x_1741_);
v___x_1743_ = 131071ULL;
v___x_1744_ = lean_uint64_land(v_product_1739_, v___x_1743_);
v___x_1745_ = 0ULL;
v___x_1746_ = lean_uint64_dec_eq(v___x_1744_, v___x_1745_);
if (v___x_1746_ == 0)
{
uint32_t v___x_1747_; 
v___x_1747_ = lean_uint32_lor(v___x_1742_, v___x_1456_);
v___y_1716_ = v___x_1747_;
goto v___jp_1715_;
}
else
{
v___y_1716_ = v___x_1742_;
goto v___jp_1715_;
}
v___jp_1715_:
{
float v___x_1717_; uint32_t v_r_1718_; uint32_t v___x_1719_; uint32_t v_high_1720_; uint32_t v___x_1721_; uint32_t v___x_1722_; uint32_t v_q_1723_; uint32_t v___x_1724_; uint32_t v___x_1725_; uint32_t v_e_1726_; uint32_t v___x_1727_; uint32_t v___x_1728_; uint32_t v___x_1729_; uint32_t v___x_1730_; uint32_t v___x_1731_; uint32_t v___x_1732_; uint32_t v___x_1733_; 
v___x_1717_ = lean_uint32_to_float32(v___y_1716_);
v_r_1718_ = lean_float32_to_uint32(v___x_1717_);
v___x_1719_ = 30;
v_high_1720_ = lean_uint32_shift_right(v_r_1718_, v___x_1719_);
v___x_1721_ = 6;
v___x_1722_ = lean_uint32_add(v___x_1721_, v_high_1720_);
v_q_1723_ = lean_uint32_shift_right(v_r_1718_, v___x_1722_);
v___x_1724_ = 127;
v___x_1725_ = lean_uint32_sub(v_s_1694_, v___x_1724_);
v_e_1726_ = lean_uint32_add(v___x_1725_, v_high_1720_);
v___x_1727_ = lean_uint32_xor(v___y_130_, v___y_131_);
v___x_1728_ = 2147483648;
v___x_1729_ = lean_uint32_land(v___x_1727_, v___x_1728_);
v___x_1730_ = lean_uint32_shift_left(v_e_1726_, v___x_567_);
v___x_1731_ = lean_uint32_lor(v___x_1729_, v___x_1730_);
v___x_1732_ = lean_uint32_sub(v_q_1723_, v___x_1714_);
v___x_1733_ = lean_uint32_lor(v___x_1731_, v___x_1732_);
return v___x_1733_;
}
}
}
v___jp_1543_:
{
uint64_t v___x_1549_; uint64_t v___x_1550_; uint8_t v___x_1551_; 
v___x_1549_ = lean_uint32_to_uint64(v_ev_1542_);
v___x_1550_ = 0ULL;
v___x_1551_ = lean_uint64_dec_eq(v___x_1549_, v___x_1550_);
if (v___x_1551_ == 0)
{
uint64_t v___x_1552_; uint64_t v___x_1553_; 
v___x_1552_ = 1ULL;
v___x_1553_ = lean_uint64_sub(v___x_1549_, v___x_1552_);
v___y_853_ = v___y_1548_;
v___y_854_ = v___y_1544_;
v___y_855_ = v___y_1545_;
v___y_856_ = v___y_1546_;
v___y_857_ = v___y_1547_;
v___y_858_ = v___x_1553_;
goto v___jp_852_;
}
else
{
v___y_853_ = v___y_1548_;
v___y_854_ = v___y_1544_;
v___y_855_ = v___y_1545_;
v___y_856_ = v___y_1546_;
v___y_857_ = v___y_1547_;
v___y_858_ = v___x_1550_;
goto v___jp_852_;
}
}
v___jp_1554_:
{
uint64_t v___x_1559_; uint64_t v___x_1560_; uint8_t v___x_1561_; 
v___x_1559_ = lean_uint32_to_uint64(v_eu_1455_);
v___x_1560_ = 0ULL;
v___x_1561_ = lean_uint64_dec_eq(v___x_1559_, v___x_1560_);
if (v___x_1561_ == 0)
{
uint64_t v___x_1562_; uint64_t v___x_1563_; 
v___x_1562_ = 1ULL;
v___x_1563_ = lean_uint64_sub(v___x_1559_, v___x_1562_);
v___y_1544_ = v___y_1555_;
v___y_1545_ = v___y_1556_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1557_;
v___y_1548_ = v___x_1563_;
goto v___jp_1543_;
}
else
{
v___y_1544_ = v___y_1555_;
v___y_1545_ = v___y_1556_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1557_;
v___y_1548_ = v___x_1560_;
goto v___jp_1543_;
}
}
v___jp_1564_:
{
uint32_t v___x_1569_; uint8_t v___x_1570_; 
v___x_1569_ = 0;
v___x_1570_ = lean_uint32_dec_eq(v_ev_1542_, v___x_1569_);
if (v___x_1570_ == 0)
{
uint64_t v___x_1571_; uint64_t v___x_1572_; uint64_t v___x_1573_; 
v___x_1571_ = lean_uint32_to_uint64(v___y_1565_);
v___x_1572_ = 8388608ULL;
v___x_1573_ = lean_uint64_lor(v___x_1571_, v___x_1572_);
v___y_1555_ = v___y_1566_;
v___y_1556_ = v___y_1567_;
v___y_1557_ = v___y_1568_;
v___y_1558_ = v___x_1573_;
goto v___jp_1554_;
}
else
{
uint64_t v___x_1574_; 
v___x_1574_ = lean_uint32_to_uint64(v___y_1565_);
v___y_1555_ = v___y_1566_;
v___y_1556_ = v___y_1567_;
v___y_1557_ = v___y_1568_;
v___y_1558_ = v___x_1574_;
goto v___jp_1554_;
}
}
v___jp_1575_:
{
uint32_t v___x_1577_; uint32_t v_xFraction_1578_; uint32_t v_yFraction_1579_; uint32_t v___x_1580_; uint8_t v___x_1581_; 
v___x_1577_ = 8388607;
v_xFraction_1578_ = lean_uint32_land(v___y_130_, v___x_1577_);
v_yFraction_1579_ = lean_uint32_land(v___y_131_, v___x_1577_);
v___x_1580_ = 0;
v___x_1581_ = lean_uint32_dec_eq(v_eu_1455_, v___x_1580_);
if (v___x_1581_ == 0)
{
uint64_t v___x_1582_; uint64_t v___x_1583_; uint64_t v___x_1584_; 
v___x_1582_ = lean_uint32_to_uint64(v_xFraction_1578_);
v___x_1583_ = 8388608ULL;
v___x_1584_ = lean_uint64_lor(v___x_1582_, v___x_1583_);
v___y_1565_ = v_yFraction_1579_;
v___y_1566_ = v___x_1577_;
v___y_1567_ = v___y_1576_;
v___y_1568_ = v___x_1584_;
goto v___jp_1564_;
}
else
{
uint64_t v___x_1585_; 
v___x_1585_ = lean_uint32_to_uint64(v_xFraction_1578_);
v___y_1565_ = v_yFraction_1579_;
v___y_1566_ = v___x_1577_;
v___y_1567_ = v___y_1576_;
v___y_1568_ = v___x_1585_;
goto v___jp_1564_;
}
}
v___jp_1586_:
{
uint64_t v___x_1592_; uint64_t v___x_1593_; uint8_t v___x_1594_; 
v___x_1592_ = lean_uint32_to_uint64(v_ev_1542_);
v___x_1593_ = 0ULL;
v___x_1594_ = lean_uint64_dec_eq(v___x_1592_, v___x_1593_);
if (v___x_1594_ == 0)
{
uint64_t v___x_1595_; uint64_t v___x_1596_; 
v___x_1595_ = 1ULL;
v___x_1596_ = lean_uint64_sub(v___x_1592_, v___x_1595_);
v___y_1135_ = v___y_1591_;
v___y_1136_ = v___y_1587_;
v___y_1137_ = v___y_1588_;
v___y_1138_ = v___y_1589_;
v___y_1139_ = v___y_1590_;
v___y_1140_ = v___x_1596_;
goto v___jp_1134_;
}
else
{
v___y_1135_ = v___y_1591_;
v___y_1136_ = v___y_1587_;
v___y_1137_ = v___y_1588_;
v___y_1138_ = v___y_1589_;
v___y_1139_ = v___y_1590_;
v___y_1140_ = v___x_1593_;
goto v___jp_1134_;
}
}
v___jp_1597_:
{
uint64_t v___x_1602_; uint64_t v___x_1603_; uint8_t v___x_1604_; 
v___x_1602_ = lean_uint32_to_uint64(v_eu_1455_);
v___x_1603_ = 0ULL;
v___x_1604_ = lean_uint64_dec_eq(v___x_1602_, v___x_1603_);
if (v___x_1604_ == 0)
{
uint64_t v___x_1605_; uint64_t v___x_1606_; 
v___x_1605_ = 1ULL;
v___x_1606_ = lean_uint64_sub(v___x_1602_, v___x_1605_);
v___y_1587_ = v___y_1601_;
v___y_1588_ = v___y_1598_;
v___y_1589_ = v___y_1599_;
v___y_1590_ = v___y_1600_;
v___y_1591_ = v___x_1606_;
goto v___jp_1586_;
}
else
{
v___y_1587_ = v___y_1601_;
v___y_1588_ = v___y_1598_;
v___y_1589_ = v___y_1599_;
v___y_1590_ = v___y_1600_;
v___y_1591_ = v___x_1603_;
goto v___jp_1586_;
}
}
v___jp_1607_:
{
uint32_t v___x_1612_; uint8_t v___x_1613_; 
v___x_1612_ = 0;
v___x_1613_ = lean_uint32_dec_eq(v_ev_1542_, v___x_1612_);
if (v___x_1613_ == 0)
{
uint64_t v___x_1614_; uint64_t v___x_1615_; uint64_t v___x_1616_; 
v___x_1614_ = lean_uint32_to_uint64(v___y_1609_);
v___x_1615_ = 8388608ULL;
v___x_1616_ = lean_uint64_lor(v___x_1614_, v___x_1615_);
v___y_1598_ = v___y_1608_;
v___y_1599_ = v___y_1611_;
v___y_1600_ = v___y_1610_;
v___y_1601_ = v___x_1616_;
goto v___jp_1597_;
}
else
{
uint64_t v___x_1617_; 
v___x_1617_ = lean_uint32_to_uint64(v___y_1609_);
v___y_1598_ = v___y_1608_;
v___y_1599_ = v___y_1611_;
v___y_1600_ = v___y_1610_;
v___y_1601_ = v___x_1617_;
goto v___jp_1597_;
}
}
v___jp_1618_:
{
uint32_t v___x_1620_; uint32_t v_xFraction_1621_; uint32_t v_yFraction_1622_; uint32_t v___x_1623_; uint8_t v___x_1624_; 
v___x_1620_ = 8388607;
v_xFraction_1621_ = lean_uint32_land(v___y_130_, v___x_1620_);
v_yFraction_1622_ = lean_uint32_land(v___y_131_, v___x_1620_);
v___x_1623_ = 0;
v___x_1624_ = lean_uint32_dec_eq(v_eu_1455_, v___x_1623_);
if (v___x_1624_ == 0)
{
uint64_t v___x_1625_; uint64_t v___x_1626_; uint64_t v___x_1627_; 
v___x_1625_ = lean_uint32_to_uint64(v_xFraction_1621_);
v___x_1626_ = 8388608ULL;
v___x_1627_ = lean_uint64_lor(v___x_1625_, v___x_1626_);
v___y_1608_ = v___x_1620_;
v___y_1609_ = v_yFraction_1622_;
v___y_1610_ = v___y_1619_;
v___y_1611_ = v___x_1627_;
goto v___jp_1607_;
}
else
{
uint64_t v___x_1628_; 
v___x_1628_ = lean_uint32_to_uint64(v_xFraction_1621_);
v___y_1608_ = v___x_1620_;
v___y_1609_ = v_yFraction_1622_;
v___y_1610_ = v___y_1619_;
v___y_1611_ = v___x_1628_;
goto v___jp_1607_;
}
}
v___jp_1629_:
{
if (v___y_1631_ == 0)
{
v___y_1619_ = v___x_1459_;
goto v___jp_1618_;
}
else
{
v___y_1619_ = v___y_1630_;
goto v___jp_1618_;
}
}
v___jp_1632_:
{
if (v___y_1633_ == 0)
{
if (v___y_1635_ == 0)
{
v___y_1630_ = v___y_1634_;
v___y_1631_ = v___x_1459_;
goto v___jp_1629_;
}
else
{
v___y_1619_ = v___x_1459_;
goto v___jp_1618_;
}
}
else
{
v___y_1630_ = v___y_1634_;
v___y_1631_ = v___y_1635_;
goto v___jp_1629_;
}
}
v___jp_1636_:
{
uint32_t v___x_1639_; uint32_t v___x_1640_; uint32_t v___x_1641_; uint8_t v___x_1642_; 
v___x_1639_ = 2147483648;
v___x_1640_ = lean_uint32_land(v___y_131_, v___x_1639_);
v___x_1641_ = 0;
v___x_1642_ = lean_uint32_dec_eq(v___x_1640_, v___x_1641_);
if (v___x_1642_ == 0)
{
v___y_1633_ = v___y_1638_;
v___y_1634_ = v___y_1637_;
v___y_1635_ = v___x_1459_;
goto v___jp_1632_;
}
else
{
v___y_1633_ = v___y_1638_;
v___y_1634_ = v___y_1637_;
v___y_1635_ = v___y_1637_;
goto v___jp_1632_;
}
}
v___jp_1643_:
{
if (v___y_1644_ == 0)
{
uint32_t v___x_1645_; uint32_t v___x_1646_; uint32_t v___x_1647_; uint8_t v___x_1648_; 
v___x_1645_ = 2147483648;
v___x_1646_ = lean_uint32_land(v___y_130_, v___x_1645_);
v___x_1647_ = 0;
v___x_1648_ = lean_uint32_dec_eq(v___x_1646_, v___x_1647_);
if (v___x_1648_ == 0)
{
v___y_1637_ = v___y_1644_;
v___y_1638_ = v___x_1459_;
goto v___jp_1636_;
}
else
{
v___y_1637_ = v___y_1644_;
v___y_1638_ = v___y_1644_;
goto v___jp_1636_;
}
}
else
{
lean_object* v___x_1649_; lean_object* v___x_1650_; lean_object* v___x_1651_; uint32_t v___x_1652_; 
v___x_1649_ = lean_uint32_to_nat(v___y_130_);
v___x_1650_ = lean_uint32_to_nat(v___y_131_);
v___x_1651_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1649_, v___x_1650_);
v___x_1652_ = lean_uint32_of_nat(v___x_1651_);
lean_dec(v___x_1651_);
return v___x_1652_;
}
}
v___jp_1655_:
{
if (v___y_1657_ == 0)
{
v___y_1576_ = v___x_1654_;
goto v___jp_1575_;
}
else
{
v___y_1576_ = v___y_1656_;
goto v___jp_1575_;
}
}
v___jp_1658_:
{
if (v___y_1660_ == 0)
{
if (v___y_1661_ == 0)
{
v___y_1656_ = v___y_1659_;
v___y_1657_ = v___x_1654_;
goto v___jp_1655_;
}
else
{
v___y_1576_ = v___x_1654_;
goto v___jp_1575_;
}
}
else
{
v___y_1656_ = v___y_1659_;
v___y_1657_ = v___y_1661_;
goto v___jp_1655_;
}
}
v___jp_1662_:
{
uint32_t v___x_1665_; uint32_t v___x_1666_; uint32_t v___x_1667_; uint8_t v___x_1668_; 
v___x_1665_ = 2147483648;
v___x_1666_ = lean_uint32_land(v___y_131_, v___x_1665_);
v___x_1667_ = 0;
v___x_1668_ = lean_uint32_dec_eq(v___x_1666_, v___x_1667_);
if (v___x_1668_ == 0)
{
v___y_1659_ = v___y_1663_;
v___y_1660_ = v___y_1664_;
v___y_1661_ = v___x_1654_;
goto v___jp_1658_;
}
else
{
v___y_1659_ = v___y_1663_;
v___y_1660_ = v___y_1664_;
v___y_1661_ = v___y_1663_;
goto v___jp_1658_;
}
}
v___jp_1669_:
{
if (v___y_1670_ == 0)
{
uint32_t v___x_1671_; uint32_t v___x_1672_; uint32_t v___x_1673_; uint8_t v___x_1674_; 
v___x_1671_ = 2147483648;
v___x_1672_ = lean_uint32_land(v___y_130_, v___x_1671_);
v___x_1673_ = 0;
v___x_1674_ = lean_uint32_dec_eq(v___x_1672_, v___x_1673_);
if (v___x_1674_ == 0)
{
v___y_1663_ = v___y_1670_;
v___y_1664_ = v___x_1654_;
goto v___jp_1662_;
}
else
{
v___y_1663_ = v___y_1670_;
v___y_1664_ = v___y_1670_;
goto v___jp_1662_;
}
}
else
{
lean_object* v___x_1675_; lean_object* v___x_1676_; lean_object* v___x_1677_; uint32_t v___x_1678_; 
v___x_1675_ = lean_uint32_to_nat(v___y_130_);
v___x_1676_ = lean_uint32_to_nat(v___y_131_);
v___x_1677_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1675_, v___x_1676_);
v___x_1678_ = lean_uint32_of_nat(v___x_1677_);
lean_dec(v___x_1677_);
return v___x_1678_;
}
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
v___x_144_ = lean_uint32_land(v___y_142_, v___y_141_);
v___x_145_ = lean_uint32_lor(v___y_143_, v___x_144_);
return v___x_145_;
}
v___jp_146_:
{
uint8_t v___x_151_; 
v___x_151_ = lean_uint64_dec_eq(v___y_150_, v___y_148_);
if (v___x_151_ == 0)
{
uint64_t v___x_152_; uint8_t v___x_153_; 
v___x_152_ = 8388608ULL;
v___x_153_ = lean_uint64_dec_eq(v___y_150_, v___x_152_);
if (v___x_153_ == 0)
{
uint32_t v___x_154_; 
v___x_154_ = lean_uint64_to_uint32(v___y_150_);
if (v___y_149_ == 0)
{
uint32_t v___x_155_; 
v___x_155_ = 0;
v___y_141_ = v___y_147_;
v___y_142_ = v___x_154_;
v___y_143_ = v___x_155_;
goto v___jp_140_;
}
else
{
uint32_t v___x_156_; 
v___x_156_ = 2147483648;
v___y_141_ = v___y_147_;
v___y_142_ = v___x_154_;
v___y_143_ = v___x_156_;
goto v___jp_140_;
}
}
else
{
if (v___y_149_ == 0)
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
if (v___y_149_ == 0)
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
v___x_165_ = lean_uint32_land(v___y_163_, v___y_162_);
v___x_166_ = lean_uint32_lor(v___y_164_, v___x_165_);
return v___x_166_;
}
v___jp_167_:
{
uint8_t v___x_172_; 
v___x_172_ = lean_uint64_dec_eq(v___y_171_, v___y_169_);
if (v___x_172_ == 0)
{
uint64_t v___x_173_; uint8_t v___x_174_; 
v___x_173_ = 8388608ULL;
v___x_174_ = lean_uint64_dec_eq(v___y_171_, v___x_173_);
if (v___x_174_ == 0)
{
uint32_t v___x_175_; 
v___x_175_ = lean_uint64_to_uint32(v___y_171_);
if (v___y_170_ == 0)
{
uint32_t v___x_176_; 
v___x_176_ = 0;
v___y_162_ = v___y_168_;
v___y_163_ = v___x_175_;
v___y_164_ = v___x_176_;
goto v___jp_161_;
}
else
{
uint32_t v___x_177_; 
v___x_177_ = 2147483648;
v___y_162_ = v___y_168_;
v___y_163_ = v___x_175_;
v___y_164_ = v___x_177_;
goto v___jp_161_;
}
}
else
{
if (v___y_170_ == 0)
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
if (v___y_170_ == 0)
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
v___x_184_ = lp_competition_R19Base_FastMul_mul(v___y_130_, v___y_131_);
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
v___x_197_ = lp_competition_R19Base_FastMul_mul(v___y_130_, v___y_131_);
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
v___jp_277_:
{
uint32_t v___x_279_; uint32_t v___x_280_; 
v___x_279_ = 8388608;
v___x_280_ = lean_uint32_lor(v___y_278_, v___x_279_);
return v___x_280_;
}
v___jp_281_:
{
uint32_t v___x_283_; uint32_t v___x_284_; 
v___x_283_ = 8388608;
v___x_284_ = lean_uint32_lor(v___y_282_, v___x_283_);
return v___x_284_;
}
v___jp_285_:
{
uint32_t v___x_289_; uint32_t v___x_290_; 
v___x_289_ = lean_uint32_land(v___y_286_, v___y_287_);
v___x_290_ = lean_uint32_lor(v___y_288_, v___x_289_);
return v___x_290_;
}
v___jp_291_:
{
uint8_t v___x_296_; 
v___x_296_ = lean_uint64_dec_eq(v___y_295_, v___y_292_);
if (v___x_296_ == 0)
{
uint64_t v___x_297_; uint8_t v___x_298_; 
v___x_297_ = 8388608ULL;
v___x_298_ = lean_uint64_dec_eq(v___y_295_, v___x_297_);
if (v___x_298_ == 0)
{
uint32_t v___x_299_; 
v___x_299_ = lean_uint64_to_uint32(v___y_295_);
if (v___y_294_ == 0)
{
uint32_t v___x_300_; 
v___x_300_ = 0;
v___y_286_ = v___x_299_;
v___y_287_ = v___y_293_;
v___y_288_ = v___x_300_;
goto v___jp_285_;
}
else
{
uint32_t v___x_301_; 
v___x_301_ = 2147483648;
v___y_286_ = v___x_299_;
v___y_287_ = v___y_293_;
v___y_288_ = v___x_301_;
goto v___jp_285_;
}
}
else
{
if (v___y_294_ == 0)
{
uint32_t v___x_302_; 
v___x_302_ = 0;
v___y_278_ = v___x_302_;
goto v___jp_277_;
}
else
{
uint32_t v___x_303_; 
v___x_303_ = 2147483648;
v___y_278_ = v___x_303_;
goto v___jp_277_;
}
}
}
else
{
if (v___y_294_ == 0)
{
uint32_t v___x_304_; 
v___x_304_ = 0;
return v___x_304_;
}
else
{
uint32_t v___x_305_; 
v___x_305_ = 2147483648;
return v___x_305_;
}
}
}
v___jp_306_:
{
uint32_t v___x_310_; uint32_t v___x_311_; 
v___x_310_ = lean_uint32_land(v___y_308_, v___y_307_);
v___x_311_ = lean_uint32_lor(v___y_309_, v___x_310_);
return v___x_311_;
}
v___jp_312_:
{
uint8_t v___x_317_; 
v___x_317_ = lean_uint64_dec_eq(v___y_316_, v___y_314_);
if (v___x_317_ == 0)
{
uint64_t v___x_318_; uint8_t v___x_319_; 
v___x_318_ = 8388608ULL;
v___x_319_ = lean_uint64_dec_eq(v___y_316_, v___x_318_);
if (v___x_319_ == 0)
{
uint32_t v___x_320_; 
v___x_320_ = lean_uint64_to_uint32(v___y_316_);
if (v___y_315_ == 0)
{
uint32_t v___x_321_; 
v___x_321_ = 0;
v___y_307_ = v___y_313_;
v___y_308_ = v___x_320_;
v___y_309_ = v___x_321_;
goto v___jp_306_;
}
else
{
uint32_t v___x_322_; 
v___x_322_ = 2147483648;
v___y_307_ = v___y_313_;
v___y_308_ = v___x_320_;
v___y_309_ = v___x_322_;
goto v___jp_306_;
}
}
else
{
if (v___y_315_ == 0)
{
uint32_t v___x_323_; 
v___x_323_ = 0;
v___y_282_ = v___x_323_;
goto v___jp_281_;
}
else
{
uint32_t v___x_324_; 
v___x_324_ = 2147483648;
v___y_282_ = v___x_324_;
goto v___jp_281_;
}
}
}
else
{
if (v___y_315_ == 0)
{
uint32_t v___x_325_; 
v___x_325_ = 0;
return v___x_325_;
}
else
{
uint32_t v___x_326_; 
v___x_326_ = 2147483648;
return v___x_326_;
}
}
}
v___jp_327_:
{
if (v___y_328_ == 0)
{
uint32_t v___x_329_; 
v___x_329_ = lp_competition_R19Base_FastMul_mul(v___y_130_, v___y_131_);
return v___x_329_;
}
else
{
uint32_t v___x_330_; uint32_t v___x_331_; 
v___x_330_ = 4194304;
v___x_331_ = lean_uint32_lor(v___y_131_, v___x_330_);
return v___x_331_;
}
}
v___jp_332_:
{
uint32_t v___x_333_; uint32_t v___x_334_; uint32_t v___x_335_; uint32_t v___x_336_; uint8_t v___x_337_; 
v___x_333_ = 23;
v___x_334_ = lean_uint32_shift_right(v___y_131_, v___x_333_);
v___x_335_ = 255;
v___x_336_ = lean_uint32_land(v___x_334_, v___x_335_);
v___x_337_ = lean_uint32_dec_eq(v___x_336_, v___x_335_);
if (v___x_337_ == 0)
{
v___y_328_ = v___x_337_;
goto v___jp_327_;
}
else
{
uint32_t v___x_338_; uint32_t v___x_339_; uint32_t v___x_340_; uint8_t v___x_341_; 
v___x_338_ = 8388607;
v___x_339_ = lean_uint32_land(v___y_131_, v___x_338_);
v___x_340_ = 0;
v___x_341_ = lean_uint32_dec_eq(v___x_339_, v___x_340_);
if (v___x_341_ == 0)
{
v___y_328_ = v___x_337_;
goto v___jp_327_;
}
else
{
uint32_t v___x_342_; 
v___x_342_ = lp_competition_R19Base_FastMul_mul(v___y_130_, v___y_131_);
return v___x_342_;
}
}
}
v___jp_343_:
{
if (v___y_344_ == 0)
{
goto v___jp_332_;
}
else
{
uint32_t v___x_345_; uint32_t v___x_346_; 
v___x_345_ = 4194304;
v___x_346_ = lean_uint32_lor(v___y_130_, v___x_345_);
return v___x_346_;
}
}
v___jp_347_:
{
uint32_t v___x_348_; uint32_t v___x_349_; uint32_t v___x_350_; uint32_t v___x_351_; uint8_t v___x_352_; 
v___x_348_ = 23;
v___x_349_ = lean_uint32_shift_right(v___y_130_, v___x_348_);
v___x_350_ = 255;
v___x_351_ = lean_uint32_land(v___x_349_, v___x_350_);
v___x_352_ = lean_uint32_dec_eq(v___x_351_, v___x_350_);
if (v___x_352_ == 0)
{
v___y_344_ = v___x_352_;
goto v___jp_343_;
}
else
{
uint32_t v___x_353_; uint32_t v___x_354_; uint32_t v___x_355_; uint8_t v___x_356_; 
v___x_353_ = 8388607;
v___x_354_ = lean_uint32_land(v___y_130_, v___x_353_);
v___x_355_ = 0;
v___x_356_ = lean_uint32_dec_eq(v___x_354_, v___x_355_);
if (v___x_356_ == 0)
{
v___y_344_ = v___x_352_;
goto v___jp_343_;
}
else
{
goto v___jp_332_;
}
}
}
v___jp_357_:
{
if (v___y_358_ == 0)
{
goto v___jp_347_;
}
else
{
uint32_t v___x_359_; uint32_t v___x_360_; uint32_t v___x_361_; uint8_t v___x_362_; 
v___x_359_ = 4194304;
v___x_360_ = lean_uint32_land(v___y_131_, v___x_359_);
v___x_361_ = 0;
v___x_362_ = lean_uint32_dec_eq(v___x_360_, v___x_361_);
if (v___x_362_ == 0)
{
goto v___jp_347_;
}
else
{
uint32_t v___x_363_; 
v___x_363_ = lean_uint32_lor(v___y_131_, v___x_359_);
return v___x_363_;
}
}
}
v___jp_364_:
{
uint32_t v___x_365_; uint32_t v___x_366_; uint32_t v___x_367_; uint32_t v___x_368_; uint8_t v___x_369_; 
v___x_365_ = 23;
v___x_366_ = lean_uint32_shift_right(v___y_131_, v___x_365_);
v___x_367_ = 255;
v___x_368_ = lean_uint32_land(v___x_366_, v___x_367_);
v___x_369_ = lean_uint32_dec_eq(v___x_368_, v___x_367_);
if (v___x_369_ == 0)
{
v___y_358_ = v___x_369_;
goto v___jp_357_;
}
else
{
uint32_t v___x_370_; uint32_t v___x_371_; uint32_t v___x_372_; uint8_t v___x_373_; 
v___x_370_ = 8388607;
v___x_371_ = lean_uint32_land(v___y_131_, v___x_370_);
v___x_372_ = 0;
v___x_373_ = lean_uint32_dec_eq(v___x_371_, v___x_372_);
if (v___x_373_ == 0)
{
v___y_358_ = v___x_369_;
goto v___jp_357_;
}
else
{
goto v___jp_347_;
}
}
}
v___jp_374_:
{
if (v___y_375_ == 0)
{
goto v___jp_364_;
}
else
{
uint32_t v___x_376_; uint32_t v___x_377_; uint32_t v___x_378_; uint8_t v___x_379_; 
v___x_376_ = 4194304;
v___x_377_ = lean_uint32_land(v___y_130_, v___x_376_);
v___x_378_ = 0;
v___x_379_ = lean_uint32_dec_eq(v___x_377_, v___x_378_);
if (v___x_379_ == 0)
{
goto v___jp_364_;
}
else
{
uint32_t v___x_380_; 
v___x_380_ = lean_uint32_lor(v___y_130_, v___x_376_);
return v___x_380_;
}
}
}
v___jp_381_:
{
float v_result_384_; uint8_t v___x_385_; 
v_result_384_ = lean_float32_mul(v___y_382_, v___y_383_);
v___x_385_ = lean_float32_beq(v_result_384_, v_result_384_);
if (v___x_385_ == 0)
{
uint32_t v___x_386_; uint32_t v___x_387_; uint32_t v___x_388_; uint32_t v___x_389_; uint8_t v___x_390_; 
v___x_386_ = 23;
v___x_387_ = lean_uint32_shift_right(v___y_130_, v___x_386_);
v___x_388_ = 255;
v___x_389_ = lean_uint32_land(v___x_387_, v___x_388_);
v___x_390_ = lean_uint32_dec_eq(v___x_389_, v___x_388_);
if (v___x_390_ == 0)
{
v___y_375_ = v___x_390_;
goto v___jp_374_;
}
else
{
uint32_t v___x_391_; uint32_t v___x_392_; uint32_t v___x_393_; uint8_t v___x_394_; 
v___x_391_ = 8388607;
v___x_392_ = lean_uint32_land(v___y_130_, v___x_391_);
v___x_393_ = 0;
v___x_394_ = lean_uint32_dec_eq(v___x_392_, v___x_393_);
if (v___x_394_ == 0)
{
v___y_375_ = v___x_390_;
goto v___jp_374_;
}
else
{
goto v___jp_364_;
}
}
}
else
{
uint32_t v___x_395_; 
v___x_395_ = lean_float32_to_bits(v_result_384_);
return v___x_395_;
}
}
v___jp_396_:
{
if (v___y_398_ == 0)
{
float v___x_399_; 
v___x_399_ = lean_float32_of_bits(v___y_131_);
v___y_382_ = v___y_397_;
v___y_383_ = v___x_399_;
goto v___jp_381_;
}
else
{
uint32_t v___x_400_; uint32_t v___x_401_; uint32_t v___x_402_; uint32_t v___x_403_; float v___x_404_; lean_object* v___x_405_; uint32_t v___x_406_; uint32_t v___x_407_; lean_object* v___x_408_; lean_object* v___x_409_; float v___x_410_; float v___x_411_; 
v___x_400_ = 8388607;
v___x_401_ = lean_uint32_land(v___y_131_, v___x_400_);
v___x_402_ = 8388608;
v___x_403_ = lean_uint32_lor(v___x_401_, v___x_402_);
v___x_404_ = lean_uint32_to_float32(v___x_403_);
v___x_405_ = lp_competition_R2W01b_scaleTable;
v___x_406_ = 23;
v___x_407_ = lean_uint32_shift_right(v___y_131_, v___x_406_);
v___x_408_ = lean_uint32_to_nat(v___x_407_);
v___x_409_ = lean_array_fget_borrowed(v___x_405_, v___x_408_);
lean_dec(v___x_408_);
v___x_410_ = lean_unbox_float32(v___x_409_);
v___x_411_ = lean_float32_mul(v___x_404_, v___x_410_);
v___y_382_ = v___y_397_;
v___y_383_ = v___x_411_;
goto v___jp_381_;
}
}
v___jp_412_:
{
uint32_t v___x_414_; uint32_t v_a_415_; uint32_t v___x_416_; uint32_t v___x_417_; uint32_t v___x_418_; uint8_t v___x_419_; 
v___x_414_ = 2147483647;
v_a_415_ = lean_uint32_land(v___y_131_, v___x_414_);
v___x_416_ = 201326591;
v___x_417_ = 1;
v___x_418_ = lean_uint32_sub(v_a_415_, v___x_417_);
v___x_419_ = lean_uint32_dec_le(v___x_416_, v___x_418_);
if (v___x_419_ == 0)
{
v___y_397_ = v___y_413_;
v___y_398_ = v___x_419_;
goto v___jp_396_;
}
else
{
uint32_t v___x_420_; uint8_t v___x_421_; 
v___x_420_ = 2139095040;
v___x_421_ = lean_uint32_dec_lt(v_a_415_, v___x_420_);
v___y_397_ = v___y_413_;
v___y_398_ = v___x_421_;
goto v___jp_396_;
}
}
v___jp_422_:
{
uint32_t v___x_424_; uint32_t v___x_425_; 
v___x_424_ = 8388608;
v___x_425_ = lean_uint32_lor(v___y_423_, v___x_424_);
return v___x_425_;
}
v___jp_426_:
{
uint32_t v___x_428_; uint32_t v___x_429_; 
v___x_428_ = 8388608;
v___x_429_ = lean_uint32_lor(v___y_427_, v___x_428_);
return v___x_429_;
}
v___jp_430_:
{
uint32_t v___x_434_; uint32_t v___x_435_; 
v___x_434_ = lean_uint32_land(v___y_431_, v___y_432_);
v___x_435_ = lean_uint32_lor(v___y_433_, v___x_434_);
return v___x_435_;
}
v___jp_436_:
{
uint8_t v___x_441_; 
v___x_441_ = lean_uint64_dec_eq(v___y_440_, v___y_438_);
if (v___x_441_ == 0)
{
uint64_t v___x_442_; uint8_t v___x_443_; 
v___x_442_ = 8388608ULL;
v___x_443_ = lean_uint64_dec_eq(v___y_440_, v___x_442_);
if (v___x_443_ == 0)
{
uint32_t v___x_444_; 
v___x_444_ = lean_uint64_to_uint32(v___y_440_);
if (v___y_437_ == 0)
{
uint32_t v___x_445_; 
v___x_445_ = 0;
v___y_431_ = v___x_444_;
v___y_432_ = v___y_439_;
v___y_433_ = v___x_445_;
goto v___jp_430_;
}
else
{
uint32_t v___x_446_; 
v___x_446_ = 2147483648;
v___y_431_ = v___x_444_;
v___y_432_ = v___y_439_;
v___y_433_ = v___x_446_;
goto v___jp_430_;
}
}
else
{
if (v___y_437_ == 0)
{
uint32_t v___x_447_; 
v___x_447_ = 0;
v___y_427_ = v___x_447_;
goto v___jp_426_;
}
else
{
uint32_t v___x_448_; 
v___x_448_ = 2147483648;
v___y_427_ = v___x_448_;
goto v___jp_426_;
}
}
}
else
{
if (v___y_437_ == 0)
{
uint32_t v___x_449_; 
v___x_449_ = 0;
return v___x_449_;
}
else
{
uint32_t v___x_450_; 
v___x_450_ = 2147483648;
return v___x_450_;
}
}
}
v___jp_451_:
{
uint32_t v___x_455_; uint32_t v___x_456_; 
v___x_455_ = lean_uint32_land(v___y_452_, v___y_453_);
v___x_456_ = lean_uint32_lor(v___y_454_, v___x_455_);
return v___x_456_;
}
v___jp_457_:
{
uint8_t v___x_462_; 
v___x_462_ = lean_uint64_dec_eq(v___y_461_, v___y_459_);
if (v___x_462_ == 0)
{
uint64_t v___x_463_; uint8_t v___x_464_; 
v___x_463_ = 8388608ULL;
v___x_464_ = lean_uint64_dec_eq(v___y_461_, v___x_463_);
if (v___x_464_ == 0)
{
uint32_t v___x_465_; 
v___x_465_ = lean_uint64_to_uint32(v___y_461_);
if (v___y_458_ == 0)
{
uint32_t v___x_466_; 
v___x_466_ = 0;
v___y_452_ = v___x_465_;
v___y_453_ = v___y_460_;
v___y_454_ = v___x_466_;
goto v___jp_451_;
}
else
{
uint32_t v___x_467_; 
v___x_467_ = 2147483648;
v___y_452_ = v___x_465_;
v___y_453_ = v___y_460_;
v___y_454_ = v___x_467_;
goto v___jp_451_;
}
}
else
{
if (v___y_458_ == 0)
{
uint32_t v___x_468_; 
v___x_468_ = 0;
v___y_423_ = v___x_468_;
goto v___jp_422_;
}
else
{
uint32_t v___x_469_; 
v___x_469_ = 2147483648;
v___y_423_ = v___x_469_;
goto v___jp_422_;
}
}
}
else
{
if (v___y_458_ == 0)
{
uint32_t v___x_470_; 
v___x_470_ = 0;
return v___x_470_;
}
else
{
uint32_t v___x_471_; 
v___x_471_ = 2147483648;
return v___x_471_;
}
}
}
v___jp_472_:
{
if (v___y_473_ == 0)
{
uint32_t v___x_474_; 
v___x_474_ = lp_competition_R19Base_FastMul_mul(v___y_130_, v___y_131_);
return v___x_474_;
}
else
{
uint32_t v___x_475_; uint32_t v___x_476_; 
v___x_475_ = 4194304;
v___x_476_ = lean_uint32_lor(v___y_131_, v___x_475_);
return v___x_476_;
}
}
v___jp_477_:
{
uint32_t v___x_478_; uint32_t v___x_479_; uint32_t v___x_480_; uint32_t v___x_481_; uint8_t v___x_482_; 
v___x_478_ = 23;
v___x_479_ = lean_uint32_shift_right(v___y_131_, v___x_478_);
v___x_480_ = 255;
v___x_481_ = lean_uint32_land(v___x_479_, v___x_480_);
v___x_482_ = lean_uint32_dec_eq(v___x_481_, v___x_480_);
if (v___x_482_ == 0)
{
v___y_473_ = v___x_482_;
goto v___jp_472_;
}
else
{
uint32_t v___x_483_; uint32_t v___x_484_; uint32_t v___x_485_; uint8_t v___x_486_; 
v___x_483_ = 8388607;
v___x_484_ = lean_uint32_land(v___y_131_, v___x_483_);
v___x_485_ = 0;
v___x_486_ = lean_uint32_dec_eq(v___x_484_, v___x_485_);
if (v___x_486_ == 0)
{
v___y_473_ = v___x_482_;
goto v___jp_472_;
}
else
{
uint32_t v___x_487_; 
v___x_487_ = lp_competition_R19Base_FastMul_mul(v___y_130_, v___y_131_);
return v___x_487_;
}
}
}
v___jp_488_:
{
if (v___y_489_ == 0)
{
goto v___jp_477_;
}
else
{
uint32_t v___x_490_; uint32_t v___x_491_; 
v___x_490_ = 4194304;
v___x_491_ = lean_uint32_lor(v___y_130_, v___x_490_);
return v___x_491_;
}
}
v___jp_492_:
{
uint32_t v___x_493_; uint32_t v___x_494_; uint32_t v___x_495_; uint32_t v___x_496_; uint8_t v___x_497_; 
v___x_493_ = 23;
v___x_494_ = lean_uint32_shift_right(v___y_130_, v___x_493_);
v___x_495_ = 255;
v___x_496_ = lean_uint32_land(v___x_494_, v___x_495_);
v___x_497_ = lean_uint32_dec_eq(v___x_496_, v___x_495_);
if (v___x_497_ == 0)
{
v___y_489_ = v___x_497_;
goto v___jp_488_;
}
else
{
uint32_t v___x_498_; uint32_t v___x_499_; uint32_t v___x_500_; uint8_t v___x_501_; 
v___x_498_ = 8388607;
v___x_499_ = lean_uint32_land(v___y_130_, v___x_498_);
v___x_500_ = 0;
v___x_501_ = lean_uint32_dec_eq(v___x_499_, v___x_500_);
if (v___x_501_ == 0)
{
v___y_489_ = v___x_497_;
goto v___jp_488_;
}
else
{
goto v___jp_477_;
}
}
}
v___jp_502_:
{
if (v___y_503_ == 0)
{
goto v___jp_492_;
}
else
{
uint32_t v___x_504_; uint32_t v___x_505_; uint32_t v___x_506_; uint8_t v___x_507_; 
v___x_504_ = 4194304;
v___x_505_ = lean_uint32_land(v___y_131_, v___x_504_);
v___x_506_ = 0;
v___x_507_ = lean_uint32_dec_eq(v___x_505_, v___x_506_);
if (v___x_507_ == 0)
{
goto v___jp_492_;
}
else
{
uint32_t v___x_508_; 
v___x_508_ = lean_uint32_lor(v___y_131_, v___x_504_);
return v___x_508_;
}
}
}
v___jp_509_:
{
uint32_t v___x_510_; uint32_t v___x_511_; uint32_t v___x_512_; uint32_t v___x_513_; uint8_t v___x_514_; 
v___x_510_ = 23;
v___x_511_ = lean_uint32_shift_right(v___y_131_, v___x_510_);
v___x_512_ = 255;
v___x_513_ = lean_uint32_land(v___x_511_, v___x_512_);
v___x_514_ = lean_uint32_dec_eq(v___x_513_, v___x_512_);
if (v___x_514_ == 0)
{
v___y_503_ = v___x_514_;
goto v___jp_502_;
}
else
{
uint32_t v___x_515_; uint32_t v___x_516_; uint32_t v___x_517_; uint8_t v___x_518_; 
v___x_515_ = 8388607;
v___x_516_ = lean_uint32_land(v___y_131_, v___x_515_);
v___x_517_ = 0;
v___x_518_ = lean_uint32_dec_eq(v___x_516_, v___x_517_);
if (v___x_518_ == 0)
{
v___y_503_ = v___x_514_;
goto v___jp_502_;
}
else
{
goto v___jp_492_;
}
}
}
v___jp_519_:
{
if (v___y_520_ == 0)
{
goto v___jp_509_;
}
else
{
uint32_t v___x_521_; uint32_t v___x_522_; uint32_t v___x_523_; uint8_t v___x_524_; 
v___x_521_ = 4194304;
v___x_522_ = lean_uint32_land(v___y_130_, v___x_521_);
v___x_523_ = 0;
v___x_524_ = lean_uint32_dec_eq(v___x_522_, v___x_523_);
if (v___x_524_ == 0)
{
goto v___jp_509_;
}
else
{
uint32_t v___x_525_; 
v___x_525_ = lean_uint32_lor(v___y_130_, v___x_521_);
return v___x_525_;
}
}
}
v___jp_526_:
{
float v_result_529_; uint8_t v___x_530_; 
v_result_529_ = lean_float32_mul(v___y_527_, v___y_528_);
v___x_530_ = lean_float32_beq(v_result_529_, v_result_529_);
if (v___x_530_ == 0)
{
uint32_t v___x_531_; uint32_t v___x_532_; uint32_t v___x_533_; uint32_t v___x_534_; uint8_t v___x_535_; 
v___x_531_ = 23;
v___x_532_ = lean_uint32_shift_right(v___y_130_, v___x_531_);
v___x_533_ = 255;
v___x_534_ = lean_uint32_land(v___x_532_, v___x_533_);
v___x_535_ = lean_uint32_dec_eq(v___x_534_, v___x_533_);
if (v___x_535_ == 0)
{
v___y_520_ = v___x_535_;
goto v___jp_519_;
}
else
{
uint32_t v___x_536_; uint32_t v___x_537_; uint32_t v___x_538_; uint8_t v___x_539_; 
v___x_536_ = 8388607;
v___x_537_ = lean_uint32_land(v___y_130_, v___x_536_);
v___x_538_ = 0;
v___x_539_ = lean_uint32_dec_eq(v___x_537_, v___x_538_);
if (v___x_539_ == 0)
{
v___y_520_ = v___x_535_;
goto v___jp_519_;
}
else
{
goto v___jp_509_;
}
}
}
else
{
uint32_t v___x_540_; 
v___x_540_ = lean_float32_to_bits(v_result_529_);
return v___x_540_;
}
}
v___jp_541_:
{
if (v___y_543_ == 0)
{
float v___x_544_; 
v___x_544_ = lean_float32_of_bits(v___y_131_);
v___y_527_ = v___y_542_;
v___y_528_ = v___x_544_;
goto v___jp_526_;
}
else
{
uint32_t v___x_545_; uint32_t v___x_546_; uint32_t v___x_547_; uint32_t v___x_548_; float v___x_549_; lean_object* v___x_550_; uint32_t v___x_551_; uint32_t v___x_552_; lean_object* v___x_553_; lean_object* v___x_554_; float v___x_555_; float v___x_556_; 
v___x_545_ = 8388607;
v___x_546_ = lean_uint32_land(v___y_131_, v___x_545_);
v___x_547_ = 8388608;
v___x_548_ = lean_uint32_lor(v___x_546_, v___x_547_);
v___x_549_ = lean_uint32_to_float32(v___x_548_);
v___x_550_ = lp_competition_R2W01b_scaleTable;
v___x_551_ = 23;
v___x_552_ = lean_uint32_shift_right(v___y_131_, v___x_551_);
v___x_553_ = lean_uint32_to_nat(v___x_552_);
v___x_554_ = lean_array_fget_borrowed(v___x_550_, v___x_553_);
lean_dec(v___x_553_);
v___x_555_ = lean_unbox_float32(v___x_554_);
v___x_556_ = lean_float32_mul(v___x_549_, v___x_555_);
v___y_527_ = v___y_542_;
v___y_528_ = v___x_556_;
goto v___jp_526_;
}
}
v___jp_557_:
{
uint32_t v___x_559_; uint32_t v_a_560_; uint32_t v___x_561_; uint32_t v___x_562_; uint32_t v___x_563_; uint8_t v___x_564_; 
v___x_559_ = 2147483647;
v_a_560_ = lean_uint32_land(v___y_131_, v___x_559_);
v___x_561_ = 201326591;
v___x_562_ = 1;
v___x_563_ = lean_uint32_sub(v_a_560_, v___x_562_);
v___x_564_ = lean_uint32_dec_le(v___x_561_, v___x_563_);
if (v___x_564_ == 0)
{
v___y_542_ = v___y_558_;
v___y_543_ = v___x_564_;
goto v___jp_541_;
}
else
{
uint32_t v___x_565_; uint8_t v___x_566_; 
v___x_565_ = 2139095040;
v___x_566_ = lean_uint32_dec_lt(v_a_560_, v___x_565_);
v___y_542_ = v___y_558_;
v___y_543_ = v___x_566_;
goto v___jp_541_;
}
}
v___jp_569_:
{
if (v___y_570_ == 0)
{
float v___x_571_; 
v___x_571_ = lean_float32_of_bits(v___y_130_);
v___y_268_ = v___x_571_;
goto v___jp_267_;
}
else
{
uint32_t v___x_572_; uint32_t v___x_573_; uint32_t v___x_574_; uint32_t v___x_575_; float v___x_576_; lean_object* v___x_577_; lean_object* v___x_578_; lean_object* v___x_579_; float v___x_580_; float v___x_581_; 
v___x_572_ = 8388607;
v___x_573_ = lean_uint32_land(v___y_130_, v___x_572_);
v___x_574_ = 8388608;
v___x_575_ = lean_uint32_lor(v___x_573_, v___x_574_);
v___x_576_ = lean_uint32_to_float32(v___x_575_);
v___x_577_ = lp_competition_R2W01b_scaleTable;
v___x_578_ = lean_uint32_to_nat(v___x_568_);
v___x_579_ = lean_array_fget_borrowed(v___x_577_, v___x_578_);
lean_dec(v___x_578_);
v___x_580_ = lean_unbox_float32(v___x_579_);
v___x_581_ = lean_float32_mul(v___x_576_, v___x_580_);
v___y_268_ = v___x_581_;
goto v___jp_267_;
}
}
v___jp_582_:
{
if (v___y_583_ == 0)
{
float v___x_584_; 
v___x_584_ = lean_float32_of_bits(v___y_130_);
v___y_413_ = v___x_584_;
goto v___jp_412_;
}
else
{
uint32_t v___x_585_; uint32_t v___x_586_; uint32_t v___x_587_; uint32_t v___x_588_; float v___x_589_; lean_object* v___x_590_; lean_object* v___x_591_; lean_object* v___x_592_; float v___x_593_; float v___x_594_; 
v___x_585_ = 8388607;
v___x_586_ = lean_uint32_land(v___y_130_, v___x_585_);
v___x_587_ = 8388608;
v___x_588_ = lean_uint32_lor(v___x_586_, v___x_587_);
v___x_589_ = lean_uint32_to_float32(v___x_588_);
v___x_590_ = lp_competition_R2W01b_scaleTable;
v___x_591_ = lean_uint32_to_nat(v___x_568_);
v___x_592_ = lean_array_fget_borrowed(v___x_590_, v___x_591_);
lean_dec(v___x_591_);
v___x_593_ = lean_unbox_float32(v___x_592_);
v___x_594_ = lean_float32_mul(v___x_589_, v___x_593_);
v___y_413_ = v___x_594_;
goto v___jp_412_;
}
}
v___jp_595_:
{
if (v___y_596_ == 0)
{
float v___x_597_; 
v___x_597_ = lean_float32_of_bits(v___y_130_);
v___y_558_ = v___x_597_;
goto v___jp_557_;
}
else
{
uint32_t v___x_598_; uint32_t v___x_599_; uint32_t v___x_600_; uint32_t v___x_601_; float v___x_602_; lean_object* v___x_603_; lean_object* v___x_604_; lean_object* v___x_605_; float v___x_606_; float v___x_607_; 
v___x_598_ = 8388607;
v___x_599_ = lean_uint32_land(v___y_130_, v___x_598_);
v___x_600_ = 8388608;
v___x_601_ = lean_uint32_lor(v___x_599_, v___x_600_);
v___x_602_ = lean_uint32_to_float32(v___x_601_);
v___x_603_ = lp_competition_R2W01b_scaleTable;
v___x_604_ = lean_uint32_to_nat(v___x_568_);
v___x_605_ = lean_array_fget_borrowed(v___x_603_, v___x_604_);
lean_dec(v___x_604_);
v___x_606_ = lean_unbox_float32(v___x_605_);
v___x_607_ = lean_float32_mul(v___x_602_, v___x_606_);
v___y_558_ = v___x_607_;
goto v___jp_557_;
}
}
v___jp_609_:
{
uint32_t v___x_614_; uint32_t v___x_615_; uint32_t v___x_616_; uint32_t v___x_617_; uint32_t v___x_618_; 
v___x_614_ = lean_uint32_land(v___y_612_, v___x_608_);
v___x_615_ = lean_uint32_shift_left(v___x_614_, v___x_567_);
v___x_616_ = lean_uint32_lor(v___y_613_, v___x_615_);
v___x_617_ = lean_uint32_land(v___y_610_, v___y_611_);
v___x_618_ = lean_uint32_lor(v___x_616_, v___x_617_);
return v___x_618_;
}
v___jp_619_:
{
if (v___y_621_ == 0)
{
uint32_t v___x_624_; 
v___x_624_ = 0;
v___y_610_ = v___y_623_;
v___y_611_ = v___y_620_;
v___y_612_ = v___y_622_;
v___y_613_ = v___x_624_;
goto v___jp_609_;
}
else
{
uint32_t v___x_625_; 
v___x_625_ = 2147483648;
v___y_610_ = v___y_623_;
v___y_611_ = v___y_620_;
v___y_612_ = v___y_622_;
v___y_613_ = v___x_625_;
goto v___jp_609_;
}
}
v___jp_626_:
{
uint64_t v___x_632_; uint64_t v_encodedExponent_633_; uint32_t v___x_634_; uint64_t v___x_635_; uint8_t v___x_636_; 
v___x_632_ = 171ULL;
v_encodedExponent_633_ = lean_uint64_sub(v___y_630_, v___x_632_);
v___x_634_ = lean_uint64_to_uint32(v_encodedExponent_633_);
v___x_635_ = 8388608ULL;
v___x_636_ = lean_uint64_dec_lt(v___y_631_, v___x_635_);
if (v___x_636_ == 0)
{
uint64_t v___x_637_; uint32_t v___x_638_; 
v___x_637_ = lean_uint64_sub(v___y_631_, v___x_635_);
v___x_638_ = lean_uint64_to_uint32(v___x_637_);
v___y_620_ = v___y_628_;
v___y_621_ = v___y_629_;
v___y_622_ = v___x_634_;
v___y_623_ = v___x_638_;
goto v___jp_619_;
}
else
{
uint32_t v___x_639_; 
v___x_639_ = lean_uint64_to_uint32(v___y_627_);
v___y_620_ = v___y_628_;
v___y_621_ = v___y_629_;
v___y_622_ = v___x_634_;
v___y_623_ = v___x_639_;
goto v___jp_619_;
}
}
v___jp_640_:
{
uint64_t v___x_647_; uint8_t v___x_648_; 
v___x_647_ = 425ULL;
v___x_648_ = lean_uint64_dec_lt(v___x_647_, v___y_646_);
if (v___x_648_ == 0)
{
if (v___y_644_ == 0)
{
v___y_627_ = v___y_642_;
v___y_628_ = v___y_641_;
v___y_629_ = v___y_643_;
v___y_630_ = v___y_646_;
v___y_631_ = v___y_645_;
goto v___jp_626_;
}
else
{
uint64_t v___x_649_; 
v___x_649_ = 8388608ULL;
v___y_627_ = v___y_642_;
v___y_628_ = v___y_641_;
v___y_629_ = v___y_643_;
v___y_630_ = v___y_646_;
v___y_631_ = v___x_649_;
goto v___jp_626_;
}
}
else
{
if (v___y_643_ == 0)
{
uint32_t v___x_650_; 
v___x_650_ = 2139095040;
return v___x_650_;
}
else
{
uint32_t v___x_651_; 
v___x_651_ = 4286578688;
return v___x_651_;
}
}
}
v___jp_652_:
{
uint64_t v___x_658_; uint8_t v_carry_659_; 
v___x_658_ = 16777216ULL;
v_carry_659_ = lean_uint64_dec_eq(v___y_657_, v___x_658_);
if (v_carry_659_ == 0)
{
v___y_641_ = v___y_654_;
v___y_642_ = v___y_653_;
v___y_643_ = v___y_655_;
v___y_644_ = v_carry_659_;
v___y_645_ = v___y_657_;
v___y_646_ = v___y_656_;
goto v___jp_640_;
}
else
{
uint64_t v___x_660_; uint64_t v___x_661_; 
v___x_660_ = 1ULL;
v___x_661_ = lean_uint64_add(v___y_656_, v___x_660_);
v___y_641_ = v___y_654_;
v___y_642_ = v___y_653_;
v___y_643_ = v___y_655_;
v___y_644_ = v_carry_659_;
v___y_645_ = v___y_657_;
v___y_646_ = v___x_661_;
goto v___jp_640_;
}
}
v___jp_662_:
{
uint64_t v_position_669_; uint64_t v___x_670_; uint8_t v___x_671_; 
v_position_669_ = lean_uint64_add(v___y_668_, v___y_663_);
v___x_670_ = 172ULL;
v___x_671_ = lean_uint64_dec_lt(v_position_669_, v___x_670_);
if (v___x_671_ == 0)
{
uint64_t v___x_672_; uint8_t v___x_673_; 
v___x_672_ = 23ULL;
v___x_673_ = lean_uint64_dec_lt(v___y_668_, v___x_672_);
if (v___x_673_ == 0)
{
uint64_t v___x_674_; uint8_t v___x_675_; 
v___x_674_ = lean_uint64_sub(v___y_668_, v___x_672_);
v___x_675_ = lean_uint64_dec_eq(v___x_674_, v___y_665_);
if (v___x_675_ == 0)
{
uint64_t v___x_676_; uint8_t v___x_677_; 
v___x_676_ = 64ULL;
v___x_677_ = lean_uint64_dec_lt(v___x_674_, v___x_676_);
if (v___x_677_ == 0)
{
uint8_t v___x_678_; 
v___x_678_ = lean_uint64_dec_eq(v___x_674_, v___x_676_);
if (v___x_678_ == 0)
{
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v___y_665_;
goto v___jp_652_;
}
else
{
uint64_t v___x_679_; uint8_t v___x_680_; 
v___x_679_ = 9223372036854775808ULL;
v___x_680_ = lean_uint64_dec_lt(v___x_679_, v___y_667_);
if (v___x_680_ == 0)
{
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v___y_665_;
goto v___jp_652_;
}
else
{
uint64_t v___x_681_; 
v___x_681_ = 1ULL;
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v___x_681_;
goto v___jp_652_;
}
}
}
else
{
uint64_t v_quotient_682_; uint64_t v___x_683_; uint64_t v___x_684_; uint64_t v___x_685_; uint64_t v_remainder_686_; uint64_t v___x_687_; uint64_t v_half_688_; uint8_t v___x_689_; 
v_quotient_682_ = lean_uint64_shift_right(v___y_667_, v___x_674_);
v___x_683_ = 1ULL;
v___x_684_ = lean_uint64_shift_left(v___x_683_, v___x_674_);
v___x_685_ = lean_uint64_sub(v___x_684_, v___x_683_);
v_remainder_686_ = lean_uint64_land(v___y_667_, v___x_685_);
v___x_687_ = lean_uint64_sub(v___x_674_, v___x_683_);
v_half_688_ = lean_uint64_shift_left(v___x_683_, v___x_687_);
v___x_689_ = lean_uint64_dec_lt(v_remainder_686_, v_half_688_);
if (v___x_689_ == 0)
{
uint8_t v___x_690_; 
v___x_690_ = lean_uint64_dec_lt(v_half_688_, v_remainder_686_);
if (v___x_690_ == 0)
{
uint64_t v___x_691_; uint8_t v___x_692_; 
v___x_691_ = lean_uint64_land(v_quotient_682_, v___x_683_);
v___x_692_ = lean_uint64_dec_eq(v___x_691_, v___y_665_);
if (v___x_692_ == 0)
{
uint64_t v___x_693_; 
v___x_693_ = lean_uint64_add(v_quotient_682_, v___x_683_);
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v___x_693_;
goto v___jp_652_;
}
else
{
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v_quotient_682_;
goto v___jp_652_;
}
}
else
{
uint64_t v___x_694_; 
v___x_694_ = lean_uint64_add(v_quotient_682_, v___x_683_);
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v___x_694_;
goto v___jp_652_;
}
}
else
{
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v_quotient_682_;
goto v___jp_652_;
}
}
}
else
{
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v___y_667_;
goto v___jp_652_;
}
}
else
{
uint64_t v___x_695_; uint64_t v___x_696_; 
v___x_695_ = lean_uint64_sub(v___x_672_, v___y_668_);
v___x_696_ = lean_uint64_shift_left(v___y_667_, v___x_695_);
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_666_;
v___y_656_ = v_position_669_;
v___y_657_ = v___x_696_;
goto v___jp_652_;
}
}
else
{
uint64_t v___x_697_; uint8_t v___x_698_; 
v___x_697_ = 149ULL;
v___x_698_ = lean_uint64_dec_lt(v___y_663_, v___x_697_);
if (v___x_698_ == 0)
{
uint64_t v___x_699_; uint64_t v___x_700_; 
v___x_699_ = lean_uint64_sub(v___y_663_, v___x_697_);
v___x_700_ = lean_uint64_shift_left(v___y_667_, v___x_699_);
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v___x_700_;
goto v___jp_146_;
}
else
{
uint64_t v___x_701_; uint8_t v___x_702_; 
v___x_701_ = lean_uint64_sub(v___x_697_, v___y_663_);
v___x_702_ = lean_uint64_dec_eq(v___x_701_, v___y_665_);
if (v___x_702_ == 0)
{
uint64_t v___x_703_; uint8_t v___x_704_; 
v___x_703_ = 64ULL;
v___x_704_ = lean_uint64_dec_lt(v___x_701_, v___x_703_);
if (v___x_704_ == 0)
{
uint8_t v___x_705_; 
v___x_705_ = lean_uint64_dec_eq(v___x_701_, v___x_703_);
if (v___x_705_ == 0)
{
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v___y_665_;
goto v___jp_146_;
}
else
{
uint64_t v___x_706_; uint8_t v___x_707_; 
v___x_706_ = 9223372036854775808ULL;
v___x_707_ = lean_uint64_dec_lt(v___x_706_, v___y_667_);
if (v___x_707_ == 0)
{
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v___y_665_;
goto v___jp_146_;
}
else
{
uint64_t v___x_708_; 
v___x_708_ = 1ULL;
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v___x_708_;
goto v___jp_146_;
}
}
}
else
{
uint64_t v_quotient_709_; uint64_t v___x_710_; uint64_t v___x_711_; uint64_t v___x_712_; uint64_t v_remainder_713_; uint64_t v___x_714_; uint64_t v_half_715_; uint8_t v___x_716_; 
v_quotient_709_ = lean_uint64_shift_right(v___y_667_, v___x_701_);
v___x_710_ = 1ULL;
v___x_711_ = lean_uint64_shift_left(v___x_710_, v___x_701_);
v___x_712_ = lean_uint64_sub(v___x_711_, v___x_710_);
v_remainder_713_ = lean_uint64_land(v___y_667_, v___x_712_);
v___x_714_ = lean_uint64_sub(v___x_701_, v___x_710_);
v_half_715_ = lean_uint64_shift_left(v___x_710_, v___x_714_);
v___x_716_ = lean_uint64_dec_lt(v_remainder_713_, v_half_715_);
if (v___x_716_ == 0)
{
uint8_t v___x_717_; 
v___x_717_ = lean_uint64_dec_lt(v_half_715_, v_remainder_713_);
if (v___x_717_ == 0)
{
uint64_t v___x_718_; uint8_t v___x_719_; 
v___x_718_ = lean_uint64_land(v_quotient_709_, v___x_710_);
v___x_719_ = lean_uint64_dec_eq(v___x_718_, v___y_665_);
if (v___x_719_ == 0)
{
uint64_t v___x_720_; 
v___x_720_ = lean_uint64_add(v_quotient_709_, v___x_710_);
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v___x_720_;
goto v___jp_146_;
}
else
{
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v_quotient_709_;
goto v___jp_146_;
}
}
else
{
uint64_t v___x_721_; 
v___x_721_ = lean_uint64_add(v_quotient_709_, v___x_710_);
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v___x_721_;
goto v___jp_146_;
}
}
else
{
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v_quotient_709_;
goto v___jp_146_;
}
}
}
else
{
v___y_147_ = v___y_664_;
v___y_148_ = v___y_665_;
v___y_149_ = v___y_666_;
v___y_150_ = v___y_667_;
goto v___jp_146_;
}
}
}
}
v___jp_722_:
{
uint64_t v___x_730_; uint64_t v___x_731_; uint8_t v___x_732_; 
v___x_730_ = 1ULL;
v___x_731_ = lean_uint64_shift_right(v___y_727_, v___x_730_);
v___x_732_ = lean_uint64_dec_eq(v___x_731_, v___y_725_);
if (v___x_732_ == 0)
{
uint64_t v___x_733_; 
v___x_733_ = lean_uint64_add(v___y_729_, v___x_730_);
v___y_663_ = v___y_723_;
v___y_664_ = v___y_724_;
v___y_665_ = v___y_725_;
v___y_666_ = v___y_726_;
v___y_667_ = v___y_728_;
v___y_668_ = v___x_733_;
goto v___jp_662_;
}
else
{
v___y_663_ = v___y_723_;
v___y_664_ = v___y_724_;
v___y_665_ = v___y_725_;
v___y_666_ = v___y_726_;
v___y_667_ = v___y_728_;
v___y_668_ = v___y_729_;
goto v___jp_662_;
}
}
v___jp_734_:
{
uint64_t v___x_744_; uint8_t v___x_745_; 
v___x_744_ = lean_uint64_shift_right(v___y_736_, v___y_740_);
v___x_745_ = lean_uint64_dec_eq(v___x_744_, v___y_737_);
if (v___x_745_ == 0)
{
uint64_t v___x_746_; 
v___x_746_ = lean_uint64_add(v___y_742_, v___y_740_);
v___y_723_ = v___y_735_;
v___y_724_ = v___y_738_;
v___y_725_ = v___y_737_;
v___y_726_ = v___y_739_;
v___y_727_ = v___y_743_;
v___y_728_ = v___y_741_;
v___y_729_ = v___x_746_;
goto v___jp_722_;
}
else
{
v___y_723_ = v___y_735_;
v___y_724_ = v___y_738_;
v___y_725_ = v___y_737_;
v___y_726_ = v___y_739_;
v___y_727_ = v___y_743_;
v___y_728_ = v___y_741_;
v___y_729_ = v___y_742_;
goto v___jp_722_;
}
}
v___jp_747_:
{
uint64_t v___x_755_; uint64_t v___x_756_; uint8_t v___x_757_; 
v___x_755_ = 2ULL;
v___x_756_ = lean_uint64_shift_right(v___y_749_, v___x_755_);
v___x_757_ = lean_uint64_dec_eq(v___x_756_, v___y_751_);
if (v___x_757_ == 0)
{
v___y_735_ = v___y_748_;
v___y_736_ = v___y_749_;
v___y_737_ = v___y_751_;
v___y_738_ = v___y_750_;
v___y_739_ = v___y_752_;
v___y_740_ = v___x_755_;
v___y_741_ = v___y_753_;
v___y_742_ = v___y_754_;
v___y_743_ = v___x_756_;
goto v___jp_734_;
}
else
{
v___y_735_ = v___y_748_;
v___y_736_ = v___y_749_;
v___y_737_ = v___y_751_;
v___y_738_ = v___y_750_;
v___y_739_ = v___y_752_;
v___y_740_ = v___x_755_;
v___y_741_ = v___y_753_;
v___y_742_ = v___y_754_;
v___y_743_ = v___y_749_;
goto v___jp_734_;
}
}
v___jp_758_:
{
uint64_t v___x_768_; uint8_t v___x_769_; 
v___x_768_ = lean_uint64_shift_right(v___y_760_, v___y_766_);
v___x_769_ = lean_uint64_dec_eq(v___x_768_, v___y_761_);
if (v___x_769_ == 0)
{
uint64_t v___x_770_; 
v___x_770_ = lean_uint64_add(v___y_764_, v___y_766_);
v___y_748_ = v___y_759_;
v___y_749_ = v___y_767_;
v___y_750_ = v___y_762_;
v___y_751_ = v___y_761_;
v___y_752_ = v___y_763_;
v___y_753_ = v___y_765_;
v___y_754_ = v___x_770_;
goto v___jp_747_;
}
else
{
v___y_748_ = v___y_759_;
v___y_749_ = v___y_767_;
v___y_750_ = v___y_762_;
v___y_751_ = v___y_761_;
v___y_752_ = v___y_763_;
v___y_753_ = v___y_765_;
v___y_754_ = v___y_764_;
goto v___jp_747_;
}
}
v___jp_771_:
{
uint64_t v___x_779_; uint64_t v___x_780_; uint8_t v___x_781_; 
v___x_779_ = 4ULL;
v___x_780_ = lean_uint64_shift_right(v___y_773_, v___x_779_);
v___x_781_ = lean_uint64_dec_eq(v___x_780_, v___y_775_);
if (v___x_781_ == 0)
{
v___y_759_ = v___y_772_;
v___y_760_ = v___y_773_;
v___y_761_ = v___y_775_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_776_;
v___y_764_ = v___y_778_;
v___y_765_ = v___y_777_;
v___y_766_ = v___x_779_;
v___y_767_ = v___x_780_;
goto v___jp_758_;
}
else
{
v___y_759_ = v___y_772_;
v___y_760_ = v___y_773_;
v___y_761_ = v___y_775_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_776_;
v___y_764_ = v___y_778_;
v___y_765_ = v___y_777_;
v___y_766_ = v___x_779_;
v___y_767_ = v___y_773_;
goto v___jp_758_;
}
}
v___jp_782_:
{
uint64_t v___x_792_; uint8_t v___x_793_; 
v___x_792_ = lean_uint64_shift_right(v___y_785_, v___y_784_);
v___x_793_ = lean_uint64_dec_eq(v___x_792_, v___y_786_);
if (v___x_793_ == 0)
{
uint64_t v___x_794_; 
v___x_794_ = lean_uint64_add(v___y_789_, v___y_784_);
v___y_772_ = v___y_783_;
v___y_773_ = v___y_791_;
v___y_774_ = v___y_787_;
v___y_775_ = v___y_786_;
v___y_776_ = v___y_788_;
v___y_777_ = v___y_790_;
v___y_778_ = v___x_794_;
goto v___jp_771_;
}
else
{
v___y_772_ = v___y_783_;
v___y_773_ = v___y_791_;
v___y_774_ = v___y_787_;
v___y_775_ = v___y_786_;
v___y_776_ = v___y_788_;
v___y_777_ = v___y_790_;
v___y_778_ = v___y_789_;
goto v___jp_771_;
}
}
v___jp_795_:
{
uint64_t v___x_803_; uint64_t v___x_804_; uint8_t v___x_805_; 
v___x_803_ = 8ULL;
v___x_804_ = lean_uint64_shift_right(v___y_797_, v___x_803_);
v___x_805_ = lean_uint64_dec_eq(v___x_804_, v___y_799_);
if (v___x_805_ == 0)
{
v___y_783_ = v___y_796_;
v___y_784_ = v___x_803_;
v___y_785_ = v___y_797_;
v___y_786_ = v___y_799_;
v___y_787_ = v___y_798_;
v___y_788_ = v___y_800_;
v___y_789_ = v___y_802_;
v___y_790_ = v___y_801_;
v___y_791_ = v___x_804_;
goto v___jp_782_;
}
else
{
v___y_783_ = v___y_796_;
v___y_784_ = v___x_803_;
v___y_785_ = v___y_797_;
v___y_786_ = v___y_799_;
v___y_787_ = v___y_798_;
v___y_788_ = v___y_800_;
v___y_789_ = v___y_802_;
v___y_790_ = v___y_801_;
v___y_791_ = v___y_797_;
goto v___jp_782_;
}
}
v___jp_806_:
{
uint64_t v___x_816_; uint8_t v___x_817_; 
v___x_816_ = lean_uint64_shift_right(v___y_812_, v___y_814_);
v___x_817_ = lean_uint64_dec_eq(v___x_816_, v___y_809_);
if (v___x_817_ == 0)
{
uint64_t v___x_818_; 
v___x_818_ = lean_uint64_add(v___y_808_, v___y_814_);
v___y_796_ = v___y_807_;
v___y_797_ = v___y_815_;
v___y_798_ = v___y_810_;
v___y_799_ = v___y_809_;
v___y_800_ = v___y_811_;
v___y_801_ = v___y_813_;
v___y_802_ = v___x_818_;
goto v___jp_795_;
}
else
{
v___y_796_ = v___y_807_;
v___y_797_ = v___y_815_;
v___y_798_ = v___y_810_;
v___y_799_ = v___y_809_;
v___y_800_ = v___y_811_;
v___y_801_ = v___y_813_;
v___y_802_ = v___y_808_;
goto v___jp_795_;
}
}
v___jp_819_:
{
uint64_t v___x_827_; uint64_t v___x_828_; uint8_t v___x_829_; 
v___x_827_ = 16ULL;
v___x_828_ = lean_uint64_shift_right(v___y_824_, v___x_827_);
v___x_829_ = lean_uint64_dec_eq(v___x_828_, v___y_822_);
if (v___x_829_ == 0)
{
v___y_807_ = v___y_820_;
v___y_808_ = v___y_826_;
v___y_809_ = v___y_822_;
v___y_810_ = v___y_821_;
v___y_811_ = v___y_823_;
v___y_812_ = v___y_824_;
v___y_813_ = v___y_825_;
v___y_814_ = v___x_827_;
v___y_815_ = v___x_828_;
goto v___jp_806_;
}
else
{
v___y_807_ = v___y_820_;
v___y_808_ = v___y_826_;
v___y_809_ = v___y_822_;
v___y_810_ = v___y_821_;
v___y_811_ = v___y_823_;
v___y_812_ = v___y_824_;
v___y_813_ = v___y_825_;
v___y_814_ = v___x_827_;
v___y_815_ = v___y_824_;
goto v___jp_806_;
}
}
v___jp_830_:
{
uint64_t v___x_838_; uint8_t v___x_839_; 
v___x_838_ = lean_uint64_shift_right(v___y_835_, v___y_836_);
v___x_839_ = lean_uint64_dec_eq(v___x_838_, v___y_832_);
if (v___x_839_ == 0)
{
v___y_820_ = v___y_831_;
v___y_821_ = v___y_833_;
v___y_822_ = v___y_832_;
v___y_823_ = v___y_834_;
v___y_824_ = v___y_837_;
v___y_825_ = v___y_835_;
v___y_826_ = v___y_836_;
goto v___jp_819_;
}
else
{
v___y_820_ = v___y_831_;
v___y_821_ = v___y_833_;
v___y_822_ = v___y_832_;
v___y_823_ = v___y_834_;
v___y_824_ = v___y_837_;
v___y_825_ = v___y_835_;
v___y_826_ = v___y_832_;
goto v___jp_819_;
}
}
v___jp_840_:
{
uint64_t v___x_845_; uint8_t v___x_846_; 
v___x_845_ = 0ULL;
v___x_846_ = lean_uint64_dec_eq(v___y_844_, v___x_845_);
if (v___x_846_ == 0)
{
uint64_t v___x_847_; uint64_t v___x_848_; uint8_t v___x_849_; 
v___x_847_ = 32ULL;
v___x_848_ = lean_uint64_shift_right(v___y_844_, v___x_847_);
v___x_849_ = lean_uint64_dec_eq(v___x_848_, v___x_845_);
if (v___x_849_ == 0)
{
v___y_831_ = v___y_841_;
v___y_832_ = v___x_845_;
v___y_833_ = v___y_842_;
v___y_834_ = v___y_843_;
v___y_835_ = v___y_844_;
v___y_836_ = v___x_847_;
v___y_837_ = v___x_848_;
goto v___jp_830_;
}
else
{
v___y_831_ = v___y_841_;
v___y_832_ = v___x_845_;
v___y_833_ = v___y_842_;
v___y_834_ = v___y_843_;
v___y_835_ = v___y_844_;
v___y_836_ = v___x_847_;
v___y_837_ = v___y_844_;
goto v___jp_830_;
}
}
else
{
if (v___y_843_ == 0)
{
uint32_t v___x_850_; 
v___x_850_ = 0;
return v___x_850_;
}
else
{
uint32_t v___x_851_; 
v___x_851_ = 2147483648;
return v___x_851_;
}
}
}
v___jp_852_:
{
uint64_t v___x_859_; uint64_t v___x_860_; uint64_t v___x_861_; uint8_t v___x_862_; 
v___x_859_ = lean_uint64_mul(v___y_857_, v___y_856_);
v___x_860_ = lean_uint64_add(v___y_853_, v___y_858_);
v___x_861_ = 281474976710656ULL;
v___x_862_ = lean_uint64_dec_lt(v___x_859_, v___x_861_);
if (v___x_862_ == 0)
{
v___y_841_ = v___x_860_;
v___y_842_ = v___y_854_;
v___y_843_ = v___y_855_;
v___y_844_ = v___x_859_;
goto v___jp_840_;
}
else
{
uint64_t v___x_863_; uint8_t v___x_864_; 
v___x_863_ = 123ULL;
v___x_864_ = lean_uint64_dec_le(v___x_860_, v___x_863_);
if (v___x_864_ == 0)
{
v___y_841_ = v___x_860_;
v___y_842_ = v___y_854_;
v___y_843_ = v___y_855_;
v___y_844_ = v___x_859_;
goto v___jp_840_;
}
else
{
uint64_t v___x_865_; uint8_t v___x_866_; 
v___x_865_ = 0ULL;
v___x_866_ = lean_uint64_dec_eq(v___x_859_, v___x_865_);
if (v___x_866_ == 0)
{
uint64_t v___x_867_; uint64_t v___x_868_; uint8_t v___x_869_; 
v___x_867_ = 149ULL;
v___x_868_ = lean_uint64_sub(v___x_867_, v___x_860_);
v___x_869_ = lean_uint64_dec_eq(v___x_868_, v___x_865_);
if (v___x_869_ == 0)
{
uint64_t v___x_870_; uint8_t v___x_871_; 
v___x_870_ = 64ULL;
v___x_871_ = lean_uint64_dec_lt(v___x_868_, v___x_870_);
if (v___x_871_ == 0)
{
uint8_t v___x_872_; 
v___x_872_ = lean_uint64_dec_eq(v___x_868_, v___x_870_);
if (v___x_872_ == 0)
{
v___y_168_ = v___y_854_;
v___y_169_ = v___x_865_;
v___y_170_ = v___y_855_;
v___y_171_ = v___x_865_;
goto v___jp_167_;
}
else
{
uint64_t v___x_873_; uint8_t v___x_874_; 
v___x_873_ = 9223372036854775808ULL;
v___x_874_ = lean_uint64_dec_lt(v___x_873_, v___x_859_);
if (v___x_874_ == 0)
{
v___y_168_ = v___y_854_;
v___y_169_ = v___x_865_;
v___y_170_ = v___y_855_;
v___y_171_ = v___x_865_;
goto v___jp_167_;
}
else
{
uint64_t v___x_875_; 
v___x_875_ = 1ULL;
v___y_168_ = v___y_854_;
v___y_169_ = v___x_865_;
v___y_170_ = v___y_855_;
v___y_171_ = v___x_875_;
goto v___jp_167_;
}
}
}
else
{
uint64_t v_quotient_876_; uint64_t v___x_877_; uint64_t v___x_878_; uint64_t v___x_879_; uint64_t v_remainder_880_; uint64_t v___x_881_; uint64_t v_half_882_; uint8_t v___x_883_; 
v_quotient_876_ = lean_uint64_shift_right(v___x_859_, v___x_868_);
v___x_877_ = 1ULL;
v___x_878_ = lean_uint64_shift_left(v___x_877_, v___x_868_);
v___x_879_ = lean_uint64_sub(v___x_878_, v___x_877_);
v_remainder_880_ = lean_uint64_land(v___x_859_, v___x_879_);
v___x_881_ = lean_uint64_sub(v___x_868_, v___x_877_);
v_half_882_ = lean_uint64_shift_left(v___x_877_, v___x_881_);
v___x_883_ = lean_uint64_dec_lt(v_remainder_880_, v_half_882_);
if (v___x_883_ == 0)
{
uint8_t v___x_884_; 
v___x_884_ = lean_uint64_dec_lt(v_half_882_, v_remainder_880_);
if (v___x_884_ == 0)
{
uint64_t v___x_885_; uint8_t v___x_886_; 
v___x_885_ = lean_uint64_land(v_quotient_876_, v___x_877_);
v___x_886_ = lean_uint64_dec_eq(v___x_885_, v___x_865_);
if (v___x_886_ == 0)
{
uint64_t v___x_887_; 
v___x_887_ = lean_uint64_add(v_quotient_876_, v___x_877_);
v___y_168_ = v___y_854_;
v___y_169_ = v___x_865_;
v___y_170_ = v___y_855_;
v___y_171_ = v___x_887_;
goto v___jp_167_;
}
else
{
v___y_168_ = v___y_854_;
v___y_169_ = v___x_865_;
v___y_170_ = v___y_855_;
v___y_171_ = v_quotient_876_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_888_; 
v___x_888_ = lean_uint64_add(v_quotient_876_, v___x_877_);
v___y_168_ = v___y_854_;
v___y_169_ = v___x_865_;
v___y_170_ = v___y_855_;
v___y_171_ = v___x_888_;
goto v___jp_167_;
}
}
else
{
v___y_168_ = v___y_854_;
v___y_169_ = v___x_865_;
v___y_170_ = v___y_855_;
v___y_171_ = v_quotient_876_;
goto v___jp_167_;
}
}
}
else
{
v___y_168_ = v___y_854_;
v___y_169_ = v___x_865_;
v___y_170_ = v___y_855_;
v___y_171_ = v___x_859_;
goto v___jp_167_;
}
}
else
{
if (v___y_855_ == 0)
{
uint32_t v___x_889_; 
v___x_889_ = 0;
return v___x_889_;
}
else
{
uint32_t v___x_890_; 
v___x_890_ = 2147483648;
return v___x_890_;
}
}
}
}
}
v___jp_891_:
{
uint32_t v___x_896_; uint32_t v___x_897_; uint32_t v___x_898_; uint32_t v___x_899_; uint32_t v___x_900_; 
v___x_896_ = lean_uint32_land(v___y_894_, v___x_608_);
v___x_897_ = lean_uint32_shift_left(v___x_896_, v___x_567_);
v___x_898_ = lean_uint32_lor(v___y_895_, v___x_897_);
v___x_899_ = lean_uint32_land(v___y_892_, v___y_893_);
v___x_900_ = lean_uint32_lor(v___x_898_, v___x_899_);
return v___x_900_;
}
v___jp_901_:
{
if (v___y_904_ == 0)
{
uint32_t v___x_906_; 
v___x_906_ = 0;
v___y_892_ = v___y_905_;
v___y_893_ = v___y_902_;
v___y_894_ = v___y_903_;
v___y_895_ = v___x_906_;
goto v___jp_891_;
}
else
{
uint32_t v___x_907_; 
v___x_907_ = 2147483648;
v___y_892_ = v___y_905_;
v___y_893_ = v___y_902_;
v___y_894_ = v___y_903_;
v___y_895_ = v___x_907_;
goto v___jp_891_;
}
}
v___jp_908_:
{
uint64_t v___x_914_; uint64_t v_encodedExponent_915_; uint32_t v___x_916_; uint64_t v___x_917_; uint8_t v___x_918_; 
v___x_914_ = 171ULL;
v_encodedExponent_915_ = lean_uint64_sub(v___y_912_, v___x_914_);
v___x_916_ = lean_uint64_to_uint32(v_encodedExponent_915_);
v___x_917_ = 8388608ULL;
v___x_918_ = lean_uint64_dec_lt(v___y_913_, v___x_917_);
if (v___x_918_ == 0)
{
uint64_t v___x_919_; uint32_t v___x_920_; 
v___x_919_ = lean_uint64_sub(v___y_913_, v___x_917_);
v___x_920_ = lean_uint64_to_uint32(v___x_919_);
v___y_902_ = v___y_910_;
v___y_903_ = v___x_916_;
v___y_904_ = v___y_911_;
v___y_905_ = v___x_920_;
goto v___jp_901_;
}
else
{
uint32_t v___x_921_; 
v___x_921_ = lean_uint64_to_uint32(v___y_909_);
v___y_902_ = v___y_910_;
v___y_903_ = v___x_916_;
v___y_904_ = v___y_911_;
v___y_905_ = v___x_921_;
goto v___jp_901_;
}
}
v___jp_922_:
{
uint64_t v___x_929_; uint8_t v___x_930_; 
v___x_929_ = 425ULL;
v___x_930_ = lean_uint64_dec_lt(v___x_929_, v___y_928_);
if (v___x_930_ == 0)
{
if (v___y_923_ == 0)
{
v___y_909_ = v___y_925_;
v___y_910_ = v___y_926_;
v___y_911_ = v___y_927_;
v___y_912_ = v___y_928_;
v___y_913_ = v___y_924_;
goto v___jp_908_;
}
else
{
uint64_t v___x_931_; 
v___x_931_ = 8388608ULL;
v___y_909_ = v___y_925_;
v___y_910_ = v___y_926_;
v___y_911_ = v___y_927_;
v___y_912_ = v___y_928_;
v___y_913_ = v___x_931_;
goto v___jp_908_;
}
}
else
{
if (v___y_927_ == 0)
{
uint32_t v___x_932_; 
v___x_932_ = 2139095040;
return v___x_932_;
}
else
{
uint32_t v___x_933_; 
v___x_933_ = 4286578688;
return v___x_933_;
}
}
}
v___jp_934_:
{
uint64_t v___x_940_; uint8_t v_carry_941_; 
v___x_940_ = 16777216ULL;
v_carry_941_ = lean_uint64_dec_eq(v___y_939_, v___x_940_);
if (v_carry_941_ == 0)
{
v___y_923_ = v_carry_941_;
v___y_924_ = v___y_939_;
v___y_925_ = v___y_935_;
v___y_926_ = v___y_936_;
v___y_927_ = v___y_938_;
v___y_928_ = v___y_937_;
goto v___jp_922_;
}
else
{
uint64_t v___x_942_; uint64_t v___x_943_; 
v___x_942_ = 1ULL;
v___x_943_ = lean_uint64_add(v___y_937_, v___x_942_);
v___y_923_ = v_carry_941_;
v___y_924_ = v___y_939_;
v___y_925_ = v___y_935_;
v___y_926_ = v___y_936_;
v___y_927_ = v___y_938_;
v___y_928_ = v___x_943_;
goto v___jp_922_;
}
}
v___jp_944_:
{
uint64_t v_position_951_; uint64_t v___x_952_; uint8_t v___x_953_; 
v_position_951_ = lean_uint64_add(v___y_950_, v___y_948_);
v___x_952_ = 172ULL;
v___x_953_ = lean_uint64_dec_lt(v_position_951_, v___x_952_);
if (v___x_953_ == 0)
{
uint64_t v___x_954_; uint8_t v___x_955_; 
v___x_954_ = 23ULL;
v___x_955_ = lean_uint64_dec_lt(v___y_950_, v___x_954_);
if (v___x_955_ == 0)
{
uint64_t v___x_956_; uint8_t v___x_957_; 
v___x_956_ = lean_uint64_sub(v___y_950_, v___x_954_);
v___x_957_ = lean_uint64_dec_eq(v___x_956_, v___y_945_);
if (v___x_957_ == 0)
{
uint64_t v___x_958_; uint8_t v___x_959_; 
v___x_958_ = 64ULL;
v___x_959_ = lean_uint64_dec_lt(v___x_956_, v___x_958_);
if (v___x_959_ == 0)
{
uint8_t v___x_960_; 
v___x_960_ = lean_uint64_dec_eq(v___x_956_, v___x_958_);
if (v___x_960_ == 0)
{
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v___y_945_;
goto v___jp_934_;
}
else
{
uint64_t v___x_961_; uint8_t v___x_962_; 
v___x_961_ = 9223372036854775808ULL;
v___x_962_ = lean_uint64_dec_lt(v___x_961_, v___y_946_);
if (v___x_962_ == 0)
{
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v___y_945_;
goto v___jp_934_;
}
else
{
uint64_t v___x_963_; 
v___x_963_ = 1ULL;
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v___x_963_;
goto v___jp_934_;
}
}
}
else
{
uint64_t v_quotient_964_; uint64_t v___x_965_; uint64_t v___x_966_; uint64_t v___x_967_; uint64_t v_remainder_968_; uint64_t v___x_969_; uint64_t v_half_970_; uint8_t v___x_971_; 
v_quotient_964_ = lean_uint64_shift_right(v___y_946_, v___x_956_);
v___x_965_ = 1ULL;
v___x_966_ = lean_uint64_shift_left(v___x_965_, v___x_956_);
v___x_967_ = lean_uint64_sub(v___x_966_, v___x_965_);
v_remainder_968_ = lean_uint64_land(v___y_946_, v___x_967_);
v___x_969_ = lean_uint64_sub(v___x_956_, v___x_965_);
v_half_970_ = lean_uint64_shift_left(v___x_965_, v___x_969_);
v___x_971_ = lean_uint64_dec_lt(v_remainder_968_, v_half_970_);
if (v___x_971_ == 0)
{
uint8_t v___x_972_; 
v___x_972_ = lean_uint64_dec_lt(v_half_970_, v_remainder_968_);
if (v___x_972_ == 0)
{
uint64_t v___x_973_; uint8_t v___x_974_; 
v___x_973_ = lean_uint64_land(v_quotient_964_, v___x_965_);
v___x_974_ = lean_uint64_dec_eq(v___x_973_, v___y_945_);
if (v___x_974_ == 0)
{
uint64_t v___x_975_; 
v___x_975_ = lean_uint64_add(v_quotient_964_, v___x_965_);
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v___x_975_;
goto v___jp_934_;
}
else
{
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v_quotient_964_;
goto v___jp_934_;
}
}
else
{
uint64_t v___x_976_; 
v___x_976_ = lean_uint64_add(v_quotient_964_, v___x_965_);
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v___x_976_;
goto v___jp_934_;
}
}
else
{
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v_quotient_964_;
goto v___jp_934_;
}
}
}
else
{
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v___y_946_;
goto v___jp_934_;
}
}
else
{
uint64_t v___x_977_; uint64_t v___x_978_; 
v___x_977_ = lean_uint64_sub(v___x_954_, v___y_950_);
v___x_978_ = lean_uint64_shift_left(v___y_946_, v___x_977_);
v___y_935_ = v___y_945_;
v___y_936_ = v___y_947_;
v___y_937_ = v_position_951_;
v___y_938_ = v___y_949_;
v___y_939_ = v___x_978_;
goto v___jp_934_;
}
}
else
{
uint64_t v___x_979_; uint8_t v___x_980_; 
v___x_979_ = 149ULL;
v___x_980_ = lean_uint64_dec_lt(v___y_948_, v___x_979_);
if (v___x_980_ == 0)
{
uint64_t v___x_981_; uint64_t v___x_982_; 
v___x_981_ = lean_uint64_sub(v___y_948_, v___x_979_);
v___x_982_ = lean_uint64_shift_left(v___y_946_, v___x_981_);
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v___x_982_;
goto v___jp_291_;
}
else
{
uint64_t v___x_983_; uint8_t v___x_984_; 
v___x_983_ = lean_uint64_sub(v___x_979_, v___y_948_);
v___x_984_ = lean_uint64_dec_eq(v___x_983_, v___y_945_);
if (v___x_984_ == 0)
{
uint64_t v___x_985_; uint8_t v___x_986_; 
v___x_985_ = 64ULL;
v___x_986_ = lean_uint64_dec_lt(v___x_983_, v___x_985_);
if (v___x_986_ == 0)
{
uint8_t v___x_987_; 
v___x_987_ = lean_uint64_dec_eq(v___x_983_, v___x_985_);
if (v___x_987_ == 0)
{
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v___y_945_;
goto v___jp_291_;
}
else
{
uint64_t v___x_988_; uint8_t v___x_989_; 
v___x_988_ = 9223372036854775808ULL;
v___x_989_ = lean_uint64_dec_lt(v___x_988_, v___y_946_);
if (v___x_989_ == 0)
{
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v___y_945_;
goto v___jp_291_;
}
else
{
uint64_t v___x_990_; 
v___x_990_ = 1ULL;
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v___x_990_;
goto v___jp_291_;
}
}
}
else
{
uint64_t v_quotient_991_; uint64_t v___x_992_; uint64_t v___x_993_; uint64_t v___x_994_; uint64_t v_remainder_995_; uint64_t v___x_996_; uint64_t v_half_997_; uint8_t v___x_998_; 
v_quotient_991_ = lean_uint64_shift_right(v___y_946_, v___x_983_);
v___x_992_ = 1ULL;
v___x_993_ = lean_uint64_shift_left(v___x_992_, v___x_983_);
v___x_994_ = lean_uint64_sub(v___x_993_, v___x_992_);
v_remainder_995_ = lean_uint64_land(v___y_946_, v___x_994_);
v___x_996_ = lean_uint64_sub(v___x_983_, v___x_992_);
v_half_997_ = lean_uint64_shift_left(v___x_992_, v___x_996_);
v___x_998_ = lean_uint64_dec_lt(v_remainder_995_, v_half_997_);
if (v___x_998_ == 0)
{
uint8_t v___x_999_; 
v___x_999_ = lean_uint64_dec_lt(v_half_997_, v_remainder_995_);
if (v___x_999_ == 0)
{
uint64_t v___x_1000_; uint8_t v___x_1001_; 
v___x_1000_ = lean_uint64_land(v_quotient_991_, v___x_992_);
v___x_1001_ = lean_uint64_dec_eq(v___x_1000_, v___y_945_);
if (v___x_1001_ == 0)
{
uint64_t v___x_1002_; 
v___x_1002_ = lean_uint64_add(v_quotient_991_, v___x_992_);
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v___x_1002_;
goto v___jp_291_;
}
else
{
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v_quotient_991_;
goto v___jp_291_;
}
}
else
{
uint64_t v___x_1003_; 
v___x_1003_ = lean_uint64_add(v_quotient_991_, v___x_992_);
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v___x_1003_;
goto v___jp_291_;
}
}
else
{
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v_quotient_991_;
goto v___jp_291_;
}
}
}
else
{
v___y_292_ = v___y_945_;
v___y_293_ = v___y_947_;
v___y_294_ = v___y_949_;
v___y_295_ = v___y_946_;
goto v___jp_291_;
}
}
}
}
v___jp_1004_:
{
uint64_t v___x_1012_; uint64_t v___x_1013_; uint8_t v___x_1014_; 
v___x_1012_ = 1ULL;
v___x_1013_ = lean_uint64_shift_right(v___y_1007_, v___x_1012_);
v___x_1014_ = lean_uint64_dec_eq(v___x_1013_, v___y_1005_);
if (v___x_1014_ == 0)
{
uint64_t v___x_1015_; 
v___x_1015_ = lean_uint64_add(v___y_1011_, v___x_1012_);
v___y_945_ = v___y_1005_;
v___y_946_ = v___y_1006_;
v___y_947_ = v___y_1008_;
v___y_948_ = v___y_1009_;
v___y_949_ = v___y_1010_;
v___y_950_ = v___x_1015_;
goto v___jp_944_;
}
else
{
v___y_945_ = v___y_1005_;
v___y_946_ = v___y_1006_;
v___y_947_ = v___y_1008_;
v___y_948_ = v___y_1009_;
v___y_949_ = v___y_1010_;
v___y_950_ = v___y_1011_;
goto v___jp_944_;
}
}
v___jp_1016_:
{
uint64_t v___x_1026_; uint8_t v___x_1027_; 
v___x_1026_ = lean_uint64_shift_right(v___y_1020_, v___y_1021_);
v___x_1027_ = lean_uint64_dec_eq(v___x_1026_, v___y_1017_);
if (v___x_1027_ == 0)
{
uint64_t v___x_1028_; 
v___x_1028_ = lean_uint64_add(v___y_1019_, v___y_1021_);
v___y_1005_ = v___y_1017_;
v___y_1006_ = v___y_1018_;
v___y_1007_ = v___y_1025_;
v___y_1008_ = v___y_1022_;
v___y_1009_ = v___y_1023_;
v___y_1010_ = v___y_1024_;
v___y_1011_ = v___x_1028_;
goto v___jp_1004_;
}
else
{
v___y_1005_ = v___y_1017_;
v___y_1006_ = v___y_1018_;
v___y_1007_ = v___y_1025_;
v___y_1008_ = v___y_1022_;
v___y_1009_ = v___y_1023_;
v___y_1010_ = v___y_1024_;
v___y_1011_ = v___y_1019_;
goto v___jp_1004_;
}
}
v___jp_1029_:
{
uint64_t v___x_1037_; uint64_t v___x_1038_; uint8_t v___x_1039_; 
v___x_1037_ = 2ULL;
v___x_1038_ = lean_uint64_shift_right(v___y_1032_, v___x_1037_);
v___x_1039_ = lean_uint64_dec_eq(v___x_1038_, v___y_1030_);
if (v___x_1039_ == 0)
{
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___y_1031_;
v___y_1019_ = v___y_1036_;
v___y_1020_ = v___y_1032_;
v___y_1021_ = v___x_1037_;
v___y_1022_ = v___y_1033_;
v___y_1023_ = v___y_1034_;
v___y_1024_ = v___y_1035_;
v___y_1025_ = v___x_1038_;
goto v___jp_1016_;
}
else
{
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___y_1031_;
v___y_1019_ = v___y_1036_;
v___y_1020_ = v___y_1032_;
v___y_1021_ = v___x_1037_;
v___y_1022_ = v___y_1033_;
v___y_1023_ = v___y_1034_;
v___y_1024_ = v___y_1035_;
v___y_1025_ = v___y_1032_;
goto v___jp_1016_;
}
}
v___jp_1040_:
{
uint64_t v___x_1050_; uint8_t v___x_1051_; 
v___x_1050_ = lean_uint64_shift_right(v___y_1045_, v___y_1044_);
v___x_1051_ = lean_uint64_dec_eq(v___x_1050_, v___y_1041_);
if (v___x_1051_ == 0)
{
uint64_t v___x_1052_; 
v___x_1052_ = lean_uint64_add(v___y_1042_, v___y_1044_);
v___y_1030_ = v___y_1041_;
v___y_1031_ = v___y_1043_;
v___y_1032_ = v___y_1049_;
v___y_1033_ = v___y_1046_;
v___y_1034_ = v___y_1047_;
v___y_1035_ = v___y_1048_;
v___y_1036_ = v___x_1052_;
goto v___jp_1029_;
}
else
{
v___y_1030_ = v___y_1041_;
v___y_1031_ = v___y_1043_;
v___y_1032_ = v___y_1049_;
v___y_1033_ = v___y_1046_;
v___y_1034_ = v___y_1047_;
v___y_1035_ = v___y_1048_;
v___y_1036_ = v___y_1042_;
goto v___jp_1029_;
}
}
v___jp_1053_:
{
uint64_t v___x_1061_; uint64_t v___x_1062_; uint8_t v___x_1063_; 
v___x_1061_ = 4ULL;
v___x_1062_ = lean_uint64_shift_right(v___y_1057_, v___x_1061_);
v___x_1063_ = lean_uint64_dec_eq(v___x_1062_, v___y_1054_);
if (v___x_1063_ == 0)
{
v___y_1041_ = v___y_1054_;
v___y_1042_ = v___y_1060_;
v___y_1043_ = v___y_1055_;
v___y_1044_ = v___x_1061_;
v___y_1045_ = v___y_1057_;
v___y_1046_ = v___y_1056_;
v___y_1047_ = v___y_1058_;
v___y_1048_ = v___y_1059_;
v___y_1049_ = v___x_1062_;
goto v___jp_1040_;
}
else
{
v___y_1041_ = v___y_1054_;
v___y_1042_ = v___y_1060_;
v___y_1043_ = v___y_1055_;
v___y_1044_ = v___x_1061_;
v___y_1045_ = v___y_1057_;
v___y_1046_ = v___y_1056_;
v___y_1047_ = v___y_1058_;
v___y_1048_ = v___y_1059_;
v___y_1049_ = v___y_1057_;
goto v___jp_1040_;
}
}
v___jp_1064_:
{
uint64_t v___x_1074_; uint8_t v___x_1075_; 
v___x_1074_ = lean_uint64_shift_right(v___y_1072_, v___y_1068_);
v___x_1075_ = lean_uint64_dec_eq(v___x_1074_, v___y_1065_);
if (v___x_1075_ == 0)
{
uint64_t v___x_1076_; 
v___x_1076_ = lean_uint64_add(v___y_1066_, v___y_1068_);
v___y_1054_ = v___y_1065_;
v___y_1055_ = v___y_1067_;
v___y_1056_ = v___y_1069_;
v___y_1057_ = v___y_1073_;
v___y_1058_ = v___y_1070_;
v___y_1059_ = v___y_1071_;
v___y_1060_ = v___x_1076_;
goto v___jp_1053_;
}
else
{
v___y_1054_ = v___y_1065_;
v___y_1055_ = v___y_1067_;
v___y_1056_ = v___y_1069_;
v___y_1057_ = v___y_1073_;
v___y_1058_ = v___y_1070_;
v___y_1059_ = v___y_1071_;
v___y_1060_ = v___y_1066_;
goto v___jp_1053_;
}
}
v___jp_1077_:
{
uint64_t v___x_1085_; uint64_t v___x_1086_; uint8_t v___x_1087_; 
v___x_1085_ = 8ULL;
v___x_1086_ = lean_uint64_shift_right(v___y_1083_, v___x_1085_);
v___x_1087_ = lean_uint64_dec_eq(v___x_1086_, v___y_1078_);
if (v___x_1087_ == 0)
{
v___y_1065_ = v___y_1078_;
v___y_1066_ = v___y_1084_;
v___y_1067_ = v___y_1079_;
v___y_1068_ = v___x_1085_;
v___y_1069_ = v___y_1080_;
v___y_1070_ = v___y_1081_;
v___y_1071_ = v___y_1082_;
v___y_1072_ = v___y_1083_;
v___y_1073_ = v___x_1086_;
goto v___jp_1064_;
}
else
{
v___y_1065_ = v___y_1078_;
v___y_1066_ = v___y_1084_;
v___y_1067_ = v___y_1079_;
v___y_1068_ = v___x_1085_;
v___y_1069_ = v___y_1080_;
v___y_1070_ = v___y_1081_;
v___y_1071_ = v___y_1082_;
v___y_1072_ = v___y_1083_;
v___y_1073_ = v___y_1083_;
goto v___jp_1064_;
}
}
v___jp_1088_:
{
uint64_t v___x_1098_; uint8_t v___x_1099_; 
v___x_1098_ = lean_uint64_shift_right(v___y_1093_, v___y_1091_);
v___x_1099_ = lean_uint64_dec_eq(v___x_1098_, v___y_1089_);
if (v___x_1099_ == 0)
{
uint64_t v___x_1100_; 
v___x_1100_ = lean_uint64_add(v___y_1094_, v___y_1091_);
v___y_1078_ = v___y_1089_;
v___y_1079_ = v___y_1090_;
v___y_1080_ = v___y_1092_;
v___y_1081_ = v___y_1095_;
v___y_1082_ = v___y_1096_;
v___y_1083_ = v___y_1097_;
v___y_1084_ = v___x_1100_;
goto v___jp_1077_;
}
else
{
v___y_1078_ = v___y_1089_;
v___y_1079_ = v___y_1090_;
v___y_1080_ = v___y_1092_;
v___y_1081_ = v___y_1095_;
v___y_1082_ = v___y_1096_;
v___y_1083_ = v___y_1097_;
v___y_1084_ = v___y_1094_;
goto v___jp_1077_;
}
}
v___jp_1101_:
{
uint64_t v___x_1109_; uint64_t v___x_1110_; uint8_t v___x_1111_; 
v___x_1109_ = 16ULL;
v___x_1110_ = lean_uint64_shift_right(v___y_1105_, v___x_1109_);
v___x_1111_ = lean_uint64_dec_eq(v___x_1110_, v___y_1102_);
if (v___x_1111_ == 0)
{
v___y_1089_ = v___y_1102_;
v___y_1090_ = v___y_1103_;
v___y_1091_ = v___x_1109_;
v___y_1092_ = v___y_1104_;
v___y_1093_ = v___y_1105_;
v___y_1094_ = v___y_1108_;
v___y_1095_ = v___y_1106_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___x_1110_;
goto v___jp_1088_;
}
else
{
v___y_1089_ = v___y_1102_;
v___y_1090_ = v___y_1103_;
v___y_1091_ = v___x_1109_;
v___y_1092_ = v___y_1104_;
v___y_1093_ = v___y_1105_;
v___y_1094_ = v___y_1108_;
v___y_1095_ = v___y_1106_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___y_1105_;
goto v___jp_1088_;
}
}
v___jp_1112_:
{
uint64_t v___x_1120_; uint8_t v___x_1121_; 
v___x_1120_ = lean_uint64_shift_right(v___y_1114_, v___y_1115_);
v___x_1121_ = lean_uint64_dec_eq(v___x_1120_, v___y_1113_);
if (v___x_1121_ == 0)
{
v___y_1102_ = v___y_1113_;
v___y_1103_ = v___y_1114_;
v___y_1104_ = v___y_1116_;
v___y_1105_ = v___y_1119_;
v___y_1106_ = v___y_1117_;
v___y_1107_ = v___y_1118_;
v___y_1108_ = v___y_1115_;
goto v___jp_1101_;
}
else
{
v___y_1102_ = v___y_1113_;
v___y_1103_ = v___y_1114_;
v___y_1104_ = v___y_1116_;
v___y_1105_ = v___y_1119_;
v___y_1106_ = v___y_1117_;
v___y_1107_ = v___y_1118_;
v___y_1108_ = v___y_1113_;
goto v___jp_1101_;
}
}
v___jp_1122_:
{
uint64_t v___x_1127_; uint8_t v___x_1128_; 
v___x_1127_ = 0ULL;
v___x_1128_ = lean_uint64_dec_eq(v___y_1123_, v___x_1127_);
if (v___x_1128_ == 0)
{
uint64_t v___x_1129_; uint64_t v___x_1130_; uint8_t v___x_1131_; 
v___x_1129_ = 32ULL;
v___x_1130_ = lean_uint64_shift_right(v___y_1123_, v___x_1129_);
v___x_1131_ = lean_uint64_dec_eq(v___x_1130_, v___x_1127_);
if (v___x_1131_ == 0)
{
v___y_1113_ = v___x_1127_;
v___y_1114_ = v___y_1123_;
v___y_1115_ = v___x_1129_;
v___y_1116_ = v___y_1124_;
v___y_1117_ = v___y_1125_;
v___y_1118_ = v___y_1126_;
v___y_1119_ = v___x_1130_;
goto v___jp_1112_;
}
else
{
v___y_1113_ = v___x_1127_;
v___y_1114_ = v___y_1123_;
v___y_1115_ = v___x_1129_;
v___y_1116_ = v___y_1124_;
v___y_1117_ = v___y_1125_;
v___y_1118_ = v___y_1126_;
v___y_1119_ = v___y_1123_;
goto v___jp_1112_;
}
}
else
{
if (v___y_1126_ == 0)
{
uint32_t v___x_1132_; 
v___x_1132_ = 0;
return v___x_1132_;
}
else
{
uint32_t v___x_1133_; 
v___x_1133_ = 2147483648;
return v___x_1133_;
}
}
}
v___jp_1134_:
{
uint64_t v___x_1141_; uint64_t v___x_1142_; uint64_t v___x_1143_; uint8_t v___x_1144_; 
v___x_1141_ = lean_uint64_mul(v___y_1138_, v___y_1136_);
v___x_1142_ = lean_uint64_add(v___y_1135_, v___y_1140_);
v___x_1143_ = 281474976710656ULL;
v___x_1144_ = lean_uint64_dec_lt(v___x_1141_, v___x_1143_);
if (v___x_1144_ == 0)
{
v___y_1123_ = v___x_1141_;
v___y_1124_ = v___y_1137_;
v___y_1125_ = v___x_1142_;
v___y_1126_ = v___y_1139_;
goto v___jp_1122_;
}
else
{
uint64_t v___x_1145_; uint8_t v___x_1146_; 
v___x_1145_ = 123ULL;
v___x_1146_ = lean_uint64_dec_le(v___x_1142_, v___x_1145_);
if (v___x_1146_ == 0)
{
v___y_1123_ = v___x_1141_;
v___y_1124_ = v___y_1137_;
v___y_1125_ = v___x_1142_;
v___y_1126_ = v___y_1139_;
goto v___jp_1122_;
}
else
{
uint64_t v___x_1147_; uint8_t v___x_1148_; 
v___x_1147_ = 0ULL;
v___x_1148_ = lean_uint64_dec_eq(v___x_1141_, v___x_1147_);
if (v___x_1148_ == 0)
{
uint64_t v___x_1149_; uint64_t v___x_1150_; uint8_t v___x_1151_; 
v___x_1149_ = 149ULL;
v___x_1150_ = lean_uint64_sub(v___x_1149_, v___x_1142_);
v___x_1151_ = lean_uint64_dec_eq(v___x_1150_, v___x_1147_);
if (v___x_1151_ == 0)
{
uint64_t v___x_1152_; uint8_t v___x_1153_; 
v___x_1152_ = 64ULL;
v___x_1153_ = lean_uint64_dec_lt(v___x_1150_, v___x_1152_);
if (v___x_1153_ == 0)
{
uint8_t v___x_1154_; 
v___x_1154_ = lean_uint64_dec_eq(v___x_1150_, v___x_1152_);
if (v___x_1154_ == 0)
{
v___y_313_ = v___y_1137_;
v___y_314_ = v___x_1147_;
v___y_315_ = v___y_1139_;
v___y_316_ = v___x_1147_;
goto v___jp_312_;
}
else
{
uint64_t v___x_1155_; uint8_t v___x_1156_; 
v___x_1155_ = 9223372036854775808ULL;
v___x_1156_ = lean_uint64_dec_lt(v___x_1155_, v___x_1141_);
if (v___x_1156_ == 0)
{
v___y_313_ = v___y_1137_;
v___y_314_ = v___x_1147_;
v___y_315_ = v___y_1139_;
v___y_316_ = v___x_1147_;
goto v___jp_312_;
}
else
{
uint64_t v___x_1157_; 
v___x_1157_ = 1ULL;
v___y_313_ = v___y_1137_;
v___y_314_ = v___x_1147_;
v___y_315_ = v___y_1139_;
v___y_316_ = v___x_1157_;
goto v___jp_312_;
}
}
}
else
{
uint64_t v_quotient_1158_; uint64_t v___x_1159_; uint64_t v___x_1160_; uint64_t v___x_1161_; uint64_t v_remainder_1162_; uint64_t v___x_1163_; uint64_t v_half_1164_; uint8_t v___x_1165_; 
v_quotient_1158_ = lean_uint64_shift_right(v___x_1141_, v___x_1150_);
v___x_1159_ = 1ULL;
v___x_1160_ = lean_uint64_shift_left(v___x_1159_, v___x_1150_);
v___x_1161_ = lean_uint64_sub(v___x_1160_, v___x_1159_);
v_remainder_1162_ = lean_uint64_land(v___x_1141_, v___x_1161_);
v___x_1163_ = lean_uint64_sub(v___x_1150_, v___x_1159_);
v_half_1164_ = lean_uint64_shift_left(v___x_1159_, v___x_1163_);
v___x_1165_ = lean_uint64_dec_lt(v_remainder_1162_, v_half_1164_);
if (v___x_1165_ == 0)
{
uint8_t v___x_1166_; 
v___x_1166_ = lean_uint64_dec_lt(v_half_1164_, v_remainder_1162_);
if (v___x_1166_ == 0)
{
uint64_t v___x_1167_; uint8_t v___x_1168_; 
v___x_1167_ = lean_uint64_land(v_quotient_1158_, v___x_1159_);
v___x_1168_ = lean_uint64_dec_eq(v___x_1167_, v___x_1147_);
if (v___x_1168_ == 0)
{
uint64_t v___x_1169_; 
v___x_1169_ = lean_uint64_add(v_quotient_1158_, v___x_1159_);
v___y_313_ = v___y_1137_;
v___y_314_ = v___x_1147_;
v___y_315_ = v___y_1139_;
v___y_316_ = v___x_1169_;
goto v___jp_312_;
}
else
{
v___y_313_ = v___y_1137_;
v___y_314_ = v___x_1147_;
v___y_315_ = v___y_1139_;
v___y_316_ = v_quotient_1158_;
goto v___jp_312_;
}
}
else
{
uint64_t v___x_1170_; 
v___x_1170_ = lean_uint64_add(v_quotient_1158_, v___x_1159_);
v___y_313_ = v___y_1137_;
v___y_314_ = v___x_1147_;
v___y_315_ = v___y_1139_;
v___y_316_ = v___x_1170_;
goto v___jp_312_;
}
}
else
{
v___y_313_ = v___y_1137_;
v___y_314_ = v___x_1147_;
v___y_315_ = v___y_1139_;
v___y_316_ = v_quotient_1158_;
goto v___jp_312_;
}
}
}
else
{
v___y_313_ = v___y_1137_;
v___y_314_ = v___x_1147_;
v___y_315_ = v___y_1139_;
v___y_316_ = v___x_1141_;
goto v___jp_312_;
}
}
else
{
if (v___y_1139_ == 0)
{
uint32_t v___x_1171_; 
v___x_1171_ = 0;
return v___x_1171_;
}
else
{
uint32_t v___x_1172_; 
v___x_1172_ = 2147483648;
return v___x_1172_;
}
}
}
}
}
v___jp_1173_:
{
uint32_t v___x_1178_; uint32_t v___x_1179_; uint32_t v___x_1180_; uint32_t v___x_1181_; uint32_t v___x_1182_; 
v___x_1178_ = lean_uint32_land(v___y_1175_, v___x_608_);
v___x_1179_ = lean_uint32_shift_left(v___x_1178_, v___x_567_);
v___x_1180_ = lean_uint32_lor(v___y_1177_, v___x_1179_);
v___x_1181_ = lean_uint32_land(v___y_1174_, v___y_1176_);
v___x_1182_ = lean_uint32_lor(v___x_1180_, v___x_1181_);
return v___x_1182_;
}
v___jp_1183_:
{
if (v___y_1184_ == 0)
{
uint32_t v___x_1188_; 
v___x_1188_ = 0;
v___y_1174_ = v___y_1187_;
v___y_1175_ = v___y_1185_;
v___y_1176_ = v___y_1186_;
v___y_1177_ = v___x_1188_;
goto v___jp_1173_;
}
else
{
uint32_t v___x_1189_; 
v___x_1189_ = 2147483648;
v___y_1174_ = v___y_1187_;
v___y_1175_ = v___y_1185_;
v___y_1176_ = v___y_1186_;
v___y_1177_ = v___x_1189_;
goto v___jp_1173_;
}
}
v___jp_1190_:
{
uint64_t v___x_1196_; uint64_t v_encodedExponent_1197_; uint32_t v___x_1198_; uint64_t v___x_1199_; uint8_t v___x_1200_; 
v___x_1196_ = 171ULL;
v_encodedExponent_1197_ = lean_uint64_sub(v___y_1191_, v___x_1196_);
v___x_1198_ = lean_uint64_to_uint32(v_encodedExponent_1197_);
v___x_1199_ = 8388608ULL;
v___x_1200_ = lean_uint64_dec_lt(v___y_1195_, v___x_1199_);
if (v___x_1200_ == 0)
{
uint64_t v___x_1201_; uint32_t v___x_1202_; 
v___x_1201_ = lean_uint64_sub(v___y_1195_, v___x_1199_);
v___x_1202_ = lean_uint64_to_uint32(v___x_1201_);
v___y_1184_ = v___y_1192_;
v___y_1185_ = v___x_1198_;
v___y_1186_ = v___y_1194_;
v___y_1187_ = v___x_1202_;
goto v___jp_1183_;
}
else
{
uint32_t v___x_1203_; 
v___x_1203_ = lean_uint64_to_uint32(v___y_1193_);
v___y_1184_ = v___y_1192_;
v___y_1185_ = v___x_1198_;
v___y_1186_ = v___y_1194_;
v___y_1187_ = v___x_1203_;
goto v___jp_1183_;
}
}
v___jp_1204_:
{
uint64_t v___x_1211_; uint8_t v___x_1212_; 
v___x_1211_ = 425ULL;
v___x_1212_ = lean_uint64_dec_lt(v___x_1211_, v___y_1210_);
if (v___x_1212_ == 0)
{
if (v___y_1207_ == 0)
{
v___y_1191_ = v___y_1210_;
v___y_1192_ = v___y_1206_;
v___y_1193_ = v___y_1208_;
v___y_1194_ = v___y_1209_;
v___y_1195_ = v___y_1205_;
goto v___jp_1190_;
}
else
{
uint64_t v___x_1213_; 
v___x_1213_ = 8388608ULL;
v___y_1191_ = v___y_1210_;
v___y_1192_ = v___y_1206_;
v___y_1193_ = v___y_1208_;
v___y_1194_ = v___y_1209_;
v___y_1195_ = v___x_1213_;
goto v___jp_1190_;
}
}
else
{
if (v___y_1206_ == 0)
{
uint32_t v___x_1214_; 
v___x_1214_ = 2139095040;
return v___x_1214_;
}
else
{
uint32_t v___x_1215_; 
v___x_1215_ = 4286578688;
return v___x_1215_;
}
}
}
v___jp_1216_:
{
uint64_t v___x_1222_; uint8_t v_carry_1223_; 
v___x_1222_ = 16777216ULL;
v_carry_1223_ = lean_uint64_dec_eq(v___y_1221_, v___x_1222_);
if (v_carry_1223_ == 0)
{
v___y_1205_ = v___y_1221_;
v___y_1206_ = v___y_1218_;
v___y_1207_ = v_carry_1223_;
v___y_1208_ = v___y_1219_;
v___y_1209_ = v___y_1220_;
v___y_1210_ = v___y_1217_;
goto v___jp_1204_;
}
else
{
uint64_t v___x_1224_; uint64_t v___x_1225_; 
v___x_1224_ = 1ULL;
v___x_1225_ = lean_uint64_add(v___y_1217_, v___x_1224_);
v___y_1205_ = v___y_1221_;
v___y_1206_ = v___y_1218_;
v___y_1207_ = v_carry_1223_;
v___y_1208_ = v___y_1219_;
v___y_1209_ = v___y_1220_;
v___y_1210_ = v___x_1225_;
goto v___jp_1204_;
}
}
v___jp_1226_:
{
uint64_t v_position_1233_; uint64_t v___x_1234_; uint8_t v___x_1235_; 
v_position_1233_ = lean_uint64_add(v___y_1232_, v___y_1227_);
v___x_1234_ = 172ULL;
v___x_1235_ = lean_uint64_dec_lt(v_position_1233_, v___x_1234_);
if (v___x_1235_ == 0)
{
uint64_t v___x_1236_; uint8_t v___x_1237_; 
v___x_1236_ = 23ULL;
v___x_1237_ = lean_uint64_dec_lt(v___y_1232_, v___x_1236_);
if (v___x_1237_ == 0)
{
uint64_t v___x_1238_; uint8_t v___x_1239_; 
v___x_1238_ = lean_uint64_sub(v___y_1232_, v___x_1236_);
v___x_1239_ = lean_uint64_dec_eq(v___x_1238_, v___y_1229_);
if (v___x_1239_ == 0)
{
uint64_t v___x_1240_; uint8_t v___x_1241_; 
v___x_1240_ = 64ULL;
v___x_1241_ = lean_uint64_dec_lt(v___x_1238_, v___x_1240_);
if (v___x_1241_ == 0)
{
uint8_t v___x_1242_; 
v___x_1242_ = lean_uint64_dec_eq(v___x_1238_, v___x_1240_);
if (v___x_1242_ == 0)
{
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___y_1229_;
goto v___jp_1216_;
}
else
{
uint64_t v___x_1243_; uint8_t v___x_1244_; 
v___x_1243_ = 9223372036854775808ULL;
v___x_1244_ = lean_uint64_dec_lt(v___x_1243_, v___y_1230_);
if (v___x_1244_ == 0)
{
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___y_1229_;
goto v___jp_1216_;
}
else
{
uint64_t v___x_1245_; 
v___x_1245_ = 1ULL;
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___x_1245_;
goto v___jp_1216_;
}
}
}
else
{
uint64_t v_quotient_1246_; uint64_t v___x_1247_; uint64_t v___x_1248_; uint64_t v___x_1249_; uint64_t v_remainder_1250_; uint64_t v___x_1251_; uint64_t v_half_1252_; uint8_t v___x_1253_; 
v_quotient_1246_ = lean_uint64_shift_right(v___y_1230_, v___x_1238_);
v___x_1247_ = 1ULL;
v___x_1248_ = lean_uint64_shift_left(v___x_1247_, v___x_1238_);
v___x_1249_ = lean_uint64_sub(v___x_1248_, v___x_1247_);
v_remainder_1250_ = lean_uint64_land(v___y_1230_, v___x_1249_);
v___x_1251_ = lean_uint64_sub(v___x_1238_, v___x_1247_);
v_half_1252_ = lean_uint64_shift_left(v___x_1247_, v___x_1251_);
v___x_1253_ = lean_uint64_dec_lt(v_remainder_1250_, v_half_1252_);
if (v___x_1253_ == 0)
{
uint8_t v___x_1254_; 
v___x_1254_ = lean_uint64_dec_lt(v_half_1252_, v_remainder_1250_);
if (v___x_1254_ == 0)
{
uint64_t v___x_1255_; uint8_t v___x_1256_; 
v___x_1255_ = lean_uint64_land(v_quotient_1246_, v___x_1247_);
v___x_1256_ = lean_uint64_dec_eq(v___x_1255_, v___y_1229_);
if (v___x_1256_ == 0)
{
uint64_t v___x_1257_; 
v___x_1257_ = lean_uint64_add(v_quotient_1246_, v___x_1247_);
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___x_1257_;
goto v___jp_1216_;
}
else
{
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v_quotient_1246_;
goto v___jp_1216_;
}
}
else
{
uint64_t v___x_1258_; 
v___x_1258_ = lean_uint64_add(v_quotient_1246_, v___x_1247_);
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___x_1258_;
goto v___jp_1216_;
}
}
else
{
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v_quotient_1246_;
goto v___jp_1216_;
}
}
}
else
{
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___y_1230_;
goto v___jp_1216_;
}
}
else
{
uint64_t v___x_1259_; uint64_t v___x_1260_; 
v___x_1259_ = lean_uint64_sub(v___x_1236_, v___y_1232_);
v___x_1260_ = lean_uint64_shift_left(v___y_1230_, v___x_1259_);
v___y_1217_ = v_position_1233_;
v___y_1218_ = v___y_1228_;
v___y_1219_ = v___y_1229_;
v___y_1220_ = v___y_1231_;
v___y_1221_ = v___x_1260_;
goto v___jp_1216_;
}
}
else
{
uint64_t v___x_1261_; uint8_t v___x_1262_; 
v___x_1261_ = 149ULL;
v___x_1262_ = lean_uint64_dec_lt(v___y_1227_, v___x_1261_);
if (v___x_1262_ == 0)
{
uint64_t v___x_1263_; uint64_t v___x_1264_; 
v___x_1263_ = lean_uint64_sub(v___y_1227_, v___x_1261_);
v___x_1264_ = lean_uint64_shift_left(v___y_1230_, v___x_1263_);
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v___x_1264_;
goto v___jp_436_;
}
else
{
uint64_t v___x_1265_; uint8_t v___x_1266_; 
v___x_1265_ = lean_uint64_sub(v___x_1261_, v___y_1227_);
v___x_1266_ = lean_uint64_dec_eq(v___x_1265_, v___y_1229_);
if (v___x_1266_ == 0)
{
uint64_t v___x_1267_; uint8_t v___x_1268_; 
v___x_1267_ = 64ULL;
v___x_1268_ = lean_uint64_dec_lt(v___x_1265_, v___x_1267_);
if (v___x_1268_ == 0)
{
uint8_t v___x_1269_; 
v___x_1269_ = lean_uint64_dec_eq(v___x_1265_, v___x_1267_);
if (v___x_1269_ == 0)
{
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v___y_1229_;
goto v___jp_436_;
}
else
{
uint64_t v___x_1270_; uint8_t v___x_1271_; 
v___x_1270_ = 9223372036854775808ULL;
v___x_1271_ = lean_uint64_dec_lt(v___x_1270_, v___y_1230_);
if (v___x_1271_ == 0)
{
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v___y_1229_;
goto v___jp_436_;
}
else
{
uint64_t v___x_1272_; 
v___x_1272_ = 1ULL;
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v___x_1272_;
goto v___jp_436_;
}
}
}
else
{
uint64_t v_quotient_1273_; uint64_t v___x_1274_; uint64_t v___x_1275_; uint64_t v___x_1276_; uint64_t v_remainder_1277_; uint64_t v___x_1278_; uint64_t v_half_1279_; uint8_t v___x_1280_; 
v_quotient_1273_ = lean_uint64_shift_right(v___y_1230_, v___x_1265_);
v___x_1274_ = 1ULL;
v___x_1275_ = lean_uint64_shift_left(v___x_1274_, v___x_1265_);
v___x_1276_ = lean_uint64_sub(v___x_1275_, v___x_1274_);
v_remainder_1277_ = lean_uint64_land(v___y_1230_, v___x_1276_);
v___x_1278_ = lean_uint64_sub(v___x_1265_, v___x_1274_);
v_half_1279_ = lean_uint64_shift_left(v___x_1274_, v___x_1278_);
v___x_1280_ = lean_uint64_dec_lt(v_remainder_1277_, v_half_1279_);
if (v___x_1280_ == 0)
{
uint8_t v___x_1281_; 
v___x_1281_ = lean_uint64_dec_lt(v_half_1279_, v_remainder_1277_);
if (v___x_1281_ == 0)
{
uint64_t v___x_1282_; uint8_t v___x_1283_; 
v___x_1282_ = lean_uint64_land(v_quotient_1273_, v___x_1274_);
v___x_1283_ = lean_uint64_dec_eq(v___x_1282_, v___y_1229_);
if (v___x_1283_ == 0)
{
uint64_t v___x_1284_; 
v___x_1284_ = lean_uint64_add(v_quotient_1273_, v___x_1274_);
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v___x_1284_;
goto v___jp_436_;
}
else
{
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v_quotient_1273_;
goto v___jp_436_;
}
}
else
{
uint64_t v___x_1285_; 
v___x_1285_ = lean_uint64_add(v_quotient_1273_, v___x_1274_);
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v___x_1285_;
goto v___jp_436_;
}
}
else
{
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v_quotient_1273_;
goto v___jp_436_;
}
}
}
else
{
v___y_437_ = v___y_1228_;
v___y_438_ = v___y_1229_;
v___y_439_ = v___y_1231_;
v___y_440_ = v___y_1230_;
goto v___jp_436_;
}
}
}
}
v___jp_1286_:
{
uint64_t v___x_1294_; uint64_t v___x_1295_; uint8_t v___x_1296_; 
v___x_1294_ = 1ULL;
v___x_1295_ = lean_uint64_shift_right(v___y_1289_, v___x_1294_);
v___x_1296_ = lean_uint64_dec_eq(v___x_1295_, v___y_1290_);
if (v___x_1296_ == 0)
{
uint64_t v___x_1297_; 
v___x_1297_ = lean_uint64_add(v___y_1293_, v___x_1294_);
v___y_1227_ = v___y_1287_;
v___y_1228_ = v___y_1288_;
v___y_1229_ = v___y_1290_;
v___y_1230_ = v___y_1291_;
v___y_1231_ = v___y_1292_;
v___y_1232_ = v___x_1297_;
goto v___jp_1226_;
}
else
{
v___y_1227_ = v___y_1287_;
v___y_1228_ = v___y_1288_;
v___y_1229_ = v___y_1290_;
v___y_1230_ = v___y_1291_;
v___y_1231_ = v___y_1292_;
v___y_1232_ = v___y_1293_;
goto v___jp_1226_;
}
}
v___jp_1298_:
{
uint64_t v___x_1308_; uint8_t v___x_1309_; 
v___x_1308_ = lean_uint64_shift_right(v___y_1299_, v___y_1301_);
v___x_1309_ = lean_uint64_dec_eq(v___x_1308_, v___y_1304_);
if (v___x_1309_ == 0)
{
uint64_t v___x_1310_; 
v___x_1310_ = lean_uint64_add(v___y_1303_, v___y_1301_);
v___y_1287_ = v___y_1300_;
v___y_1288_ = v___y_1302_;
v___y_1289_ = v___y_1307_;
v___y_1290_ = v___y_1304_;
v___y_1291_ = v___y_1305_;
v___y_1292_ = v___y_1306_;
v___y_1293_ = v___x_1310_;
goto v___jp_1286_;
}
else
{
v___y_1287_ = v___y_1300_;
v___y_1288_ = v___y_1302_;
v___y_1289_ = v___y_1307_;
v___y_1290_ = v___y_1304_;
v___y_1291_ = v___y_1305_;
v___y_1292_ = v___y_1306_;
v___y_1293_ = v___y_1303_;
goto v___jp_1286_;
}
}
v___jp_1311_:
{
uint64_t v___x_1319_; uint64_t v___x_1320_; uint8_t v___x_1321_; 
v___x_1319_ = 2ULL;
v___x_1320_ = lean_uint64_shift_right(v___y_1313_, v___x_1319_);
v___x_1321_ = lean_uint64_dec_eq(v___x_1320_, v___y_1315_);
if (v___x_1321_ == 0)
{
v___y_1299_ = v___y_1313_;
v___y_1300_ = v___y_1312_;
v___y_1301_ = v___x_1319_;
v___y_1302_ = v___y_1314_;
v___y_1303_ = v___y_1318_;
v___y_1304_ = v___y_1315_;
v___y_1305_ = v___y_1316_;
v___y_1306_ = v___y_1317_;
v___y_1307_ = v___x_1320_;
goto v___jp_1298_;
}
else
{
v___y_1299_ = v___y_1313_;
v___y_1300_ = v___y_1312_;
v___y_1301_ = v___x_1319_;
v___y_1302_ = v___y_1314_;
v___y_1303_ = v___y_1318_;
v___y_1304_ = v___y_1315_;
v___y_1305_ = v___y_1316_;
v___y_1306_ = v___y_1317_;
v___y_1307_ = v___y_1313_;
goto v___jp_1298_;
}
}
v___jp_1322_:
{
uint64_t v___x_1332_; uint8_t v___x_1333_; 
v___x_1332_ = lean_uint64_shift_right(v___y_1324_, v___y_1326_);
v___x_1333_ = lean_uint64_dec_eq(v___x_1332_, v___y_1327_);
if (v___x_1333_ == 0)
{
uint64_t v___x_1334_; 
v___x_1334_ = lean_uint64_add(v___y_1328_, v___y_1326_);
v___y_1312_ = v___y_1323_;
v___y_1313_ = v___y_1331_;
v___y_1314_ = v___y_1325_;
v___y_1315_ = v___y_1327_;
v___y_1316_ = v___y_1329_;
v___y_1317_ = v___y_1330_;
v___y_1318_ = v___x_1334_;
goto v___jp_1311_;
}
else
{
v___y_1312_ = v___y_1323_;
v___y_1313_ = v___y_1331_;
v___y_1314_ = v___y_1325_;
v___y_1315_ = v___y_1327_;
v___y_1316_ = v___y_1329_;
v___y_1317_ = v___y_1330_;
v___y_1318_ = v___y_1328_;
goto v___jp_1311_;
}
}
v___jp_1335_:
{
uint64_t v___x_1343_; uint64_t v___x_1344_; uint8_t v___x_1345_; 
v___x_1343_ = 4ULL;
v___x_1344_ = lean_uint64_shift_right(v___y_1337_, v___x_1343_);
v___x_1345_ = lean_uint64_dec_eq(v___x_1344_, v___y_1339_);
if (v___x_1345_ == 0)
{
v___y_1323_ = v___y_1336_;
v___y_1324_ = v___y_1337_;
v___y_1325_ = v___y_1338_;
v___y_1326_ = v___x_1343_;
v___y_1327_ = v___y_1339_;
v___y_1328_ = v___y_1342_;
v___y_1329_ = v___y_1340_;
v___y_1330_ = v___y_1341_;
v___y_1331_ = v___x_1344_;
goto v___jp_1322_;
}
else
{
v___y_1323_ = v___y_1336_;
v___y_1324_ = v___y_1337_;
v___y_1325_ = v___y_1338_;
v___y_1326_ = v___x_1343_;
v___y_1327_ = v___y_1339_;
v___y_1328_ = v___y_1342_;
v___y_1329_ = v___y_1340_;
v___y_1330_ = v___y_1341_;
v___y_1331_ = v___y_1337_;
goto v___jp_1322_;
}
}
v___jp_1346_:
{
uint64_t v___x_1356_; uint8_t v___x_1357_; 
v___x_1356_ = lean_uint64_shift_right(v___y_1352_, v___y_1349_);
v___x_1357_ = lean_uint64_dec_eq(v___x_1356_, v___y_1351_);
if (v___x_1357_ == 0)
{
uint64_t v___x_1358_; 
v___x_1358_ = lean_uint64_add(v___y_1350_, v___y_1349_);
v___y_1336_ = v___y_1347_;
v___y_1337_ = v___y_1355_;
v___y_1338_ = v___y_1348_;
v___y_1339_ = v___y_1351_;
v___y_1340_ = v___y_1353_;
v___y_1341_ = v___y_1354_;
v___y_1342_ = v___x_1358_;
goto v___jp_1335_;
}
else
{
v___y_1336_ = v___y_1347_;
v___y_1337_ = v___y_1355_;
v___y_1338_ = v___y_1348_;
v___y_1339_ = v___y_1351_;
v___y_1340_ = v___y_1353_;
v___y_1341_ = v___y_1354_;
v___y_1342_ = v___y_1350_;
goto v___jp_1335_;
}
}
v___jp_1359_:
{
uint64_t v___x_1367_; uint64_t v___x_1368_; uint8_t v___x_1369_; 
v___x_1367_ = 8ULL;
v___x_1368_ = lean_uint64_shift_right(v___y_1364_, v___x_1367_);
v___x_1369_ = lean_uint64_dec_eq(v___x_1368_, v___y_1362_);
if (v___x_1369_ == 0)
{
v___y_1347_ = v___y_1360_;
v___y_1348_ = v___y_1361_;
v___y_1349_ = v___x_1367_;
v___y_1350_ = v___y_1366_;
v___y_1351_ = v___y_1362_;
v___y_1352_ = v___y_1364_;
v___y_1353_ = v___y_1363_;
v___y_1354_ = v___y_1365_;
v___y_1355_ = v___x_1368_;
goto v___jp_1346_;
}
else
{
v___y_1347_ = v___y_1360_;
v___y_1348_ = v___y_1361_;
v___y_1349_ = v___x_1367_;
v___y_1350_ = v___y_1366_;
v___y_1351_ = v___y_1362_;
v___y_1352_ = v___y_1364_;
v___y_1353_ = v___y_1363_;
v___y_1354_ = v___y_1365_;
v___y_1355_ = v___y_1364_;
goto v___jp_1346_;
}
}
v___jp_1370_:
{
uint64_t v___x_1380_; uint8_t v___x_1381_; 
v___x_1380_ = lean_uint64_shift_right(v___y_1373_, v___y_1372_);
v___x_1381_ = lean_uint64_dec_eq(v___x_1380_, v___y_1375_);
if (v___x_1381_ == 0)
{
uint64_t v___x_1382_; 
v___x_1382_ = lean_uint64_add(v___y_1376_, v___y_1372_);
v___y_1360_ = v___y_1371_;
v___y_1361_ = v___y_1374_;
v___y_1362_ = v___y_1375_;
v___y_1363_ = v___y_1377_;
v___y_1364_ = v___y_1379_;
v___y_1365_ = v___y_1378_;
v___y_1366_ = v___x_1382_;
goto v___jp_1359_;
}
else
{
v___y_1360_ = v___y_1371_;
v___y_1361_ = v___y_1374_;
v___y_1362_ = v___y_1375_;
v___y_1363_ = v___y_1377_;
v___y_1364_ = v___y_1379_;
v___y_1365_ = v___y_1378_;
v___y_1366_ = v___y_1376_;
goto v___jp_1359_;
}
}
v___jp_1383_:
{
uint64_t v___x_1391_; uint64_t v___x_1392_; uint8_t v___x_1393_; 
v___x_1391_ = 16ULL;
v___x_1392_ = lean_uint64_shift_right(v___y_1386_, v___x_1391_);
v___x_1393_ = lean_uint64_dec_eq(v___x_1392_, v___y_1387_);
if (v___x_1393_ == 0)
{
v___y_1371_ = v___y_1384_;
v___y_1372_ = v___x_1391_;
v___y_1373_ = v___y_1386_;
v___y_1374_ = v___y_1385_;
v___y_1375_ = v___y_1387_;
v___y_1376_ = v___y_1390_;
v___y_1377_ = v___y_1388_;
v___y_1378_ = v___y_1389_;
v___y_1379_ = v___x_1392_;
goto v___jp_1370_;
}
else
{
v___y_1371_ = v___y_1384_;
v___y_1372_ = v___x_1391_;
v___y_1373_ = v___y_1386_;
v___y_1374_ = v___y_1385_;
v___y_1375_ = v___y_1387_;
v___y_1376_ = v___y_1390_;
v___y_1377_ = v___y_1388_;
v___y_1378_ = v___y_1389_;
v___y_1379_ = v___y_1386_;
goto v___jp_1370_;
}
}
v___jp_1394_:
{
uint64_t v___x_1402_; uint8_t v___x_1403_; 
v___x_1402_ = lean_uint64_shift_right(v___y_1399_, v___y_1397_);
v___x_1403_ = lean_uint64_dec_eq(v___x_1402_, v___y_1398_);
if (v___x_1403_ == 0)
{
v___y_1384_ = v___y_1395_;
v___y_1385_ = v___y_1396_;
v___y_1386_ = v___y_1401_;
v___y_1387_ = v___y_1398_;
v___y_1388_ = v___y_1399_;
v___y_1389_ = v___y_1400_;
v___y_1390_ = v___y_1397_;
goto v___jp_1383_;
}
else
{
v___y_1384_ = v___y_1395_;
v___y_1385_ = v___y_1396_;
v___y_1386_ = v___y_1401_;
v___y_1387_ = v___y_1398_;
v___y_1388_ = v___y_1399_;
v___y_1389_ = v___y_1400_;
v___y_1390_ = v___y_1398_;
goto v___jp_1383_;
}
}
v___jp_1404_:
{
uint64_t v___x_1409_; uint8_t v___x_1410_; 
v___x_1409_ = 0ULL;
v___x_1410_ = lean_uint64_dec_eq(v___y_1407_, v___x_1409_);
if (v___x_1410_ == 0)
{
uint64_t v___x_1411_; uint64_t v___x_1412_; uint8_t v___x_1413_; 
v___x_1411_ = 32ULL;
v___x_1412_ = lean_uint64_shift_right(v___y_1407_, v___x_1411_);
v___x_1413_ = lean_uint64_dec_eq(v___x_1412_, v___x_1409_);
if (v___x_1413_ == 0)
{
v___y_1395_ = v___y_1405_;
v___y_1396_ = v___y_1406_;
v___y_1397_ = v___x_1411_;
v___y_1398_ = v___x_1409_;
v___y_1399_ = v___y_1407_;
v___y_1400_ = v___y_1408_;
v___y_1401_ = v___x_1412_;
goto v___jp_1394_;
}
else
{
v___y_1395_ = v___y_1405_;
v___y_1396_ = v___y_1406_;
v___y_1397_ = v___x_1411_;
v___y_1398_ = v___x_1409_;
v___y_1399_ = v___y_1407_;
v___y_1400_ = v___y_1408_;
v___y_1401_ = v___y_1407_;
goto v___jp_1394_;
}
}
else
{
if (v___y_1406_ == 0)
{
uint32_t v___x_1414_; 
v___x_1414_ = 0;
return v___x_1414_;
}
else
{
uint32_t v___x_1415_; 
v___x_1415_ = 2147483648;
return v___x_1415_;
}
}
}
v___jp_1416_:
{
uint64_t v___x_1423_; uint64_t v___x_1424_; uint64_t v___x_1425_; uint8_t v___x_1426_; 
v___x_1423_ = lean_uint64_mul(v___y_1417_, v___y_1419_);
v___x_1424_ = lean_uint64_add(v___y_1420_, v___y_1422_);
v___x_1425_ = 281474976710656ULL;
v___x_1426_ = lean_uint64_dec_lt(v___x_1423_, v___x_1425_);
if (v___x_1426_ == 0)
{
v___y_1405_ = v___x_1424_;
v___y_1406_ = v___y_1418_;
v___y_1407_ = v___x_1423_;
v___y_1408_ = v___y_1421_;
goto v___jp_1404_;
}
else
{
uint64_t v___x_1427_; uint8_t v___x_1428_; 
v___x_1427_ = 123ULL;
v___x_1428_ = lean_uint64_dec_le(v___x_1424_, v___x_1427_);
if (v___x_1428_ == 0)
{
v___y_1405_ = v___x_1424_;
v___y_1406_ = v___y_1418_;
v___y_1407_ = v___x_1423_;
v___y_1408_ = v___y_1421_;
goto v___jp_1404_;
}
else
{
uint64_t v___x_1429_; uint8_t v___x_1430_; 
v___x_1429_ = 0ULL;
v___x_1430_ = lean_uint64_dec_eq(v___x_1423_, v___x_1429_);
if (v___x_1430_ == 0)
{
uint64_t v___x_1431_; uint64_t v___x_1432_; uint8_t v___x_1433_; 
v___x_1431_ = 149ULL;
v___x_1432_ = lean_uint64_sub(v___x_1431_, v___x_1424_);
v___x_1433_ = lean_uint64_dec_eq(v___x_1432_, v___x_1429_);
if (v___x_1433_ == 0)
{
uint64_t v___x_1434_; uint8_t v___x_1435_; 
v___x_1434_ = 64ULL;
v___x_1435_ = lean_uint64_dec_lt(v___x_1432_, v___x_1434_);
if (v___x_1435_ == 0)
{
uint8_t v___x_1436_; 
v___x_1436_ = lean_uint64_dec_eq(v___x_1432_, v___x_1434_);
if (v___x_1436_ == 0)
{
v___y_458_ = v___y_1418_;
v___y_459_ = v___x_1429_;
v___y_460_ = v___y_1421_;
v___y_461_ = v___x_1429_;
goto v___jp_457_;
}
else
{
uint64_t v___x_1437_; uint8_t v___x_1438_; 
v___x_1437_ = 9223372036854775808ULL;
v___x_1438_ = lean_uint64_dec_lt(v___x_1437_, v___x_1423_);
if (v___x_1438_ == 0)
{
v___y_458_ = v___y_1418_;
v___y_459_ = v___x_1429_;
v___y_460_ = v___y_1421_;
v___y_461_ = v___x_1429_;
goto v___jp_457_;
}
else
{
uint64_t v___x_1439_; 
v___x_1439_ = 1ULL;
v___y_458_ = v___y_1418_;
v___y_459_ = v___x_1429_;
v___y_460_ = v___y_1421_;
v___y_461_ = v___x_1439_;
goto v___jp_457_;
}
}
}
else
{
uint64_t v_quotient_1440_; uint64_t v___x_1441_; uint64_t v___x_1442_; uint64_t v___x_1443_; uint64_t v_remainder_1444_; uint64_t v___x_1445_; uint64_t v_half_1446_; uint8_t v___x_1447_; 
v_quotient_1440_ = lean_uint64_shift_right(v___x_1423_, v___x_1432_);
v___x_1441_ = 1ULL;
v___x_1442_ = lean_uint64_shift_left(v___x_1441_, v___x_1432_);
v___x_1443_ = lean_uint64_sub(v___x_1442_, v___x_1441_);
v_remainder_1444_ = lean_uint64_land(v___x_1423_, v___x_1443_);
v___x_1445_ = lean_uint64_sub(v___x_1432_, v___x_1441_);
v_half_1446_ = lean_uint64_shift_left(v___x_1441_, v___x_1445_);
v___x_1447_ = lean_uint64_dec_lt(v_remainder_1444_, v_half_1446_);
if (v___x_1447_ == 0)
{
uint8_t v___x_1448_; 
v___x_1448_ = lean_uint64_dec_lt(v_half_1446_, v_remainder_1444_);
if (v___x_1448_ == 0)
{
uint64_t v___x_1449_; uint8_t v___x_1450_; 
v___x_1449_ = lean_uint64_land(v_quotient_1440_, v___x_1441_);
v___x_1450_ = lean_uint64_dec_eq(v___x_1449_, v___x_1429_);
if (v___x_1450_ == 0)
{
uint64_t v___x_1451_; 
v___x_1451_ = lean_uint64_add(v_quotient_1440_, v___x_1441_);
v___y_458_ = v___y_1418_;
v___y_459_ = v___x_1429_;
v___y_460_ = v___y_1421_;
v___y_461_ = v___x_1451_;
goto v___jp_457_;
}
else
{
v___y_458_ = v___y_1418_;
v___y_459_ = v___x_1429_;
v___y_460_ = v___y_1421_;
v___y_461_ = v_quotient_1440_;
goto v___jp_457_;
}
}
else
{
uint64_t v___x_1452_; 
v___x_1452_ = lean_uint64_add(v_quotient_1440_, v___x_1441_);
v___y_458_ = v___y_1418_;
v___y_459_ = v___x_1429_;
v___y_460_ = v___y_1421_;
v___y_461_ = v___x_1452_;
goto v___jp_457_;
}
}
else
{
v___y_458_ = v___y_1418_;
v___y_459_ = v___x_1429_;
v___y_460_ = v___y_1421_;
v___y_461_ = v_quotient_1440_;
goto v___jp_457_;
}
}
}
else
{
v___y_458_ = v___y_1418_;
v___y_459_ = v___x_1429_;
v___y_460_ = v___y_1421_;
v___y_461_ = v___x_1423_;
goto v___jp_457_;
}
}
else
{
if (v___y_1418_ == 0)
{
uint32_t v___x_1453_; 
v___x_1453_ = 0;
return v___x_1453_;
}
else
{
uint32_t v___x_1454_; 
v___x_1454_ = 2147483648;
return v___x_1454_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_1748_, lean_object* v___y_1749_){
_start:
{
uint32_t v___y_11127__boxed_1750_; uint32_t v___y_11128__boxed_1751_; uint32_t v_res_1752_; lean_object* v_r_1753_; 
v___y_11127__boxed_1750_ = lean_unbox_uint32(v___y_1748_);
lean_dec(v___y_1748_);
v___y_11128__boxed_1751_ = lean_unbox_uint32(v___y_1749_);
lean_dec(v___y_1749_);
v_res_1752_ = lp_competition_main___lam__1(v___y_11127__boxed_1750_, v___y_11128__boxed_1751_);
v_r_1753_ = lean_box_uint32(v_res_1752_);
return v_r_1753_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_1754_, uint32_t v___y_1755_){
_start:
{
uint32_t v___y_1757_; uint32_t v___y_1761_; uint32_t v___y_1765_; uint32_t v___y_1766_; uint32_t v___y_1767_; uint8_t v___y_1771_; uint32_t v___y_1772_; uint64_t v___y_1773_; uint64_t v___y_1774_; uint32_t v___y_1786_; uint32_t v___y_1787_; uint32_t v___y_1788_; uint8_t v___y_1792_; uint32_t v___y_1793_; uint64_t v___y_1794_; uint64_t v___y_1795_; uint8_t v___y_1807_; uint8_t v___y_1823_; uint8_t v___y_1837_; uint8_t v___y_1854_; float v___y_1861_; float v___y_1862_; float v___y_1876_; uint8_t v___y_1877_; float v___y_1892_; uint32_t v___y_1902_; uint32_t v___y_1906_; uint32_t v___y_1910_; uint32_t v___y_1911_; uint32_t v___y_1912_; uint8_t v___y_1916_; uint32_t v___y_1917_; uint64_t v___y_1918_; uint64_t v___y_1919_; uint32_t v___y_1931_; uint32_t v___y_1932_; uint32_t v___y_1933_; uint8_t v___y_1937_; uint32_t v___y_1938_; uint64_t v___y_1939_; uint64_t v___y_1940_; uint8_t v___y_1952_; uint8_t v___y_1968_; uint8_t v___y_1982_; uint8_t v___y_1999_; float v___y_2006_; float v___y_2007_; float v___y_2021_; uint8_t v___y_2022_; float v___y_2037_; uint32_t v___y_2047_; uint32_t v___y_2051_; uint32_t v___y_2055_; uint32_t v___y_2056_; uint32_t v___y_2057_; uint32_t v___y_2061_; uint64_t v___y_2062_; uint8_t v___y_2063_; uint64_t v___y_2064_; uint32_t v___y_2076_; uint32_t v___y_2077_; uint32_t v___y_2078_; uint32_t v___y_2082_; uint8_t v___y_2083_; uint64_t v___y_2084_; uint64_t v___y_2085_; uint8_t v___y_2097_; uint8_t v___y_2113_; uint8_t v___y_2127_; uint8_t v___y_2144_; float v___y_2151_; float v___y_2152_; float v___y_2166_; uint8_t v___y_2167_; float v___y_2182_; uint32_t v___x_2191_; uint32_t v___x_2192_; uint8_t v___y_2194_; uint8_t v___y_2207_; uint8_t v___y_2220_; uint32_t v___x_2232_; uint32_t v___y_2234_; uint32_t v___y_2235_; uint32_t v___y_2236_; uint32_t v___y_2237_; uint8_t v___y_2244_; uint32_t v___y_2245_; uint32_t v___y_2246_; uint32_t v___y_2247_; uint8_t v___y_2251_; uint64_t v___y_2252_; uint32_t v___y_2253_; uint64_t v___y_2254_; uint64_t v___y_2255_; uint8_t v___y_2265_; uint8_t v___y_2266_; uint32_t v___y_2267_; uint64_t v___y_2268_; uint64_t v___y_2269_; uint64_t v___y_2270_; uint8_t v___y_2277_; uint32_t v___y_2278_; uint64_t v___y_2279_; uint64_t v___y_2280_; uint64_t v___y_2281_; uint8_t v___y_2287_; uint32_t v___y_2288_; uint64_t v___y_2289_; uint64_t v___y_2290_; uint64_t v___y_2291_; uint64_t v___y_2292_; uint8_t v___y_2347_; uint64_t v___y_2348_; uint32_t v___y_2349_; uint64_t v___y_2350_; uint64_t v___y_2351_; uint64_t v___y_2352_; uint64_t v___y_2353_; uint64_t v___y_2359_; uint8_t v___y_2360_; uint32_t v___y_2361_; uint64_t v___y_2362_; uint64_t v___y_2363_; uint64_t v___y_2364_; uint64_t v___y_2365_; uint64_t v___y_2366_; uint64_t v___y_2367_; uint8_t v___y_2372_; uint32_t v___y_2373_; uint64_t v___y_2374_; uint64_t v___y_2375_; uint64_t v___y_2376_; uint64_t v___y_2377_; uint64_t v___y_2378_; uint8_t v___y_2383_; uint64_t v___y_2384_; uint32_t v___y_2385_; uint64_t v___y_2386_; uint64_t v___y_2387_; uint64_t v___y_2388_; uint64_t v___y_2389_; uint64_t v___y_2390_; uint64_t v___y_2391_; uint8_t v___y_2396_; uint32_t v___y_2397_; uint64_t v___y_2398_; uint64_t v___y_2399_; uint64_t v___y_2400_; uint64_t v___y_2401_; uint64_t v___y_2402_; uint8_t v___y_2407_; uint32_t v___y_2408_; uint64_t v___y_2409_; uint64_t v___y_2410_; uint64_t v___y_2411_; uint64_t v___y_2412_; uint64_t v___y_2413_; uint64_t v___y_2414_; uint64_t v___y_2415_; uint8_t v___y_2420_; uint32_t v___y_2421_; uint64_t v___y_2422_; uint64_t v___y_2423_; uint64_t v___y_2424_; uint64_t v___y_2425_; uint64_t v___y_2426_; uint64_t v___y_2431_; uint8_t v___y_2432_; uint64_t v___y_2433_; uint32_t v___y_2434_; uint64_t v___y_2435_; uint64_t v___y_2436_; uint64_t v___y_2437_; uint64_t v___y_2438_; uint64_t v___y_2439_; uint8_t v___y_2444_; uint64_t v___y_2445_; uint32_t v___y_2446_; uint64_t v___y_2447_; uint64_t v___y_2448_; uint64_t v___y_2449_; uint64_t v___y_2450_; uint8_t v___y_2455_; uint64_t v___y_2456_; uint32_t v___y_2457_; uint64_t v___y_2458_; uint64_t v___y_2459_; uint64_t v___y_2460_; uint64_t v___y_2461_; uint8_t v___y_2465_; uint32_t v___y_2466_; uint64_t v___y_2467_; uint64_t v___y_2468_; uint8_t v___y_2477_; uint64_t v___y_2478_; uint32_t v___y_2479_; uint64_t v___y_2480_; uint64_t v___y_2481_; uint64_t v___y_2482_; uint32_t v___y_2516_; uint32_t v___y_2517_; uint32_t v___y_2518_; uint32_t v___y_2519_; uint8_t v___y_2526_; uint32_t v___y_2527_; uint32_t v___y_2528_; uint32_t v___y_2529_; uint8_t v___y_2533_; uint64_t v___y_2534_; uint32_t v___y_2535_; uint64_t v___y_2536_; uint64_t v___y_2537_; uint8_t v___y_2547_; uint32_t v___y_2548_; uint64_t v___y_2549_; uint64_t v___y_2550_; uint8_t v___y_2551_; uint64_t v___y_2552_; uint8_t v___y_2559_; uint32_t v___y_2560_; uint64_t v___y_2561_; uint64_t v___y_2562_; uint64_t v___y_2563_; uint8_t v___y_2569_; uint64_t v___y_2570_; uint32_t v___y_2571_; uint64_t v___y_2572_; uint64_t v___y_2573_; uint64_t v___y_2574_; uint8_t v___y_2629_; uint64_t v___y_2630_; uint32_t v___y_2631_; uint64_t v___y_2632_; uint64_t v___y_2633_; uint64_t v___y_2634_; uint64_t v___y_2635_; uint8_t v___y_2641_; uint64_t v___y_2642_; uint64_t v___y_2643_; uint32_t v___y_2644_; uint64_t v___y_2645_; uint64_t v___y_2646_; uint64_t v___y_2647_; uint64_t v___y_2648_; uint64_t v___y_2649_; uint8_t v___y_2654_; uint64_t v___y_2655_; uint64_t v___y_2656_; uint32_t v___y_2657_; uint64_t v___y_2658_; uint64_t v___y_2659_; uint64_t v___y_2660_; uint8_t v___y_2665_; uint64_t v___y_2666_; uint32_t v___y_2667_; uint64_t v___y_2668_; uint64_t v___y_2669_; uint64_t v___y_2670_; uint64_t v___y_2671_; uint64_t v___y_2672_; uint64_t v___y_2673_; uint8_t v___y_2678_; uint64_t v___y_2679_; uint32_t v___y_2680_; uint64_t v___y_2681_; uint64_t v___y_2682_; uint64_t v___y_2683_; uint64_t v___y_2684_; uint8_t v___y_2689_; uint64_t v___y_2690_; uint32_t v___y_2691_; uint64_t v___y_2692_; uint64_t v___y_2693_; uint64_t v___y_2694_; uint64_t v___y_2695_; uint64_t v___y_2696_; uint64_t v___y_2697_; uint8_t v___y_2702_; uint64_t v___y_2703_; uint32_t v___y_2704_; uint64_t v___y_2705_; uint64_t v___y_2706_; uint64_t v___y_2707_; uint64_t v___y_2708_; uint8_t v___y_2713_; uint64_t v___y_2714_; uint32_t v___y_2715_; uint64_t v___y_2716_; uint64_t v___y_2717_; uint64_t v___y_2718_; uint64_t v___y_2719_; uint64_t v___y_2720_; uint64_t v___y_2721_; uint8_t v___y_2726_; uint64_t v___y_2727_; uint32_t v___y_2728_; uint64_t v___y_2729_; uint64_t v___y_2730_; uint64_t v___y_2731_; uint64_t v___y_2732_; uint8_t v___y_2737_; uint64_t v___y_2738_; uint64_t v___y_2739_; uint32_t v___y_2740_; uint64_t v___y_2741_; uint64_t v___y_2742_; uint64_t v___y_2743_; uint8_t v___y_2747_; uint64_t v___y_2748_; uint32_t v___y_2749_; uint64_t v___y_2750_; uint64_t v___y_2759_; uint8_t v___y_2760_; uint64_t v___y_2761_; uint32_t v___y_2762_; uint64_t v___y_2763_; uint64_t v___y_2764_; uint32_t v___y_2798_; uint32_t v___y_2799_; uint32_t v___y_2800_; uint32_t v___y_2801_; uint32_t v___y_2808_; uint32_t v___y_2809_; uint8_t v___y_2810_; uint32_t v___y_2811_; uint64_t v___y_2815_; uint32_t v___y_2816_; uint64_t v___y_2817_; uint8_t v___y_2818_; uint64_t v___y_2819_; uint8_t v___y_2829_; uint64_t v___y_2830_; uint32_t v___y_2831_; uint64_t v___y_2832_; uint8_t v___y_2833_; uint64_t v___y_2834_; uint64_t v___y_2841_; uint32_t v___y_2842_; uint64_t v___y_2843_; uint8_t v___y_2844_; uint64_t v___y_2845_; uint32_t v___y_2851_; uint64_t v___y_2852_; uint64_t v___y_2853_; uint64_t v___y_2854_; uint8_t v___y_2855_; uint64_t v___y_2856_; uint64_t v___y_2911_; uint32_t v___y_2912_; uint64_t v___y_2913_; uint64_t v___y_2914_; uint64_t v___y_2915_; uint8_t v___y_2916_; uint64_t v___y_2917_; uint64_t v___y_2923_; uint64_t v___y_2924_; uint64_t v___y_2925_; uint32_t v___y_2926_; uint64_t v___y_2927_; uint64_t v___y_2928_; uint64_t v___y_2929_; uint8_t v___y_2930_; uint64_t v___y_2931_; uint64_t v___y_2936_; uint32_t v___y_2937_; uint64_t v___y_2938_; uint64_t v___y_2939_; uint64_t v___y_2940_; uint8_t v___y_2941_; uint64_t v___y_2942_; uint64_t v___y_2947_; uint64_t v___y_2948_; uint64_t v___y_2949_; uint32_t v___y_2950_; uint64_t v___y_2951_; uint64_t v___y_2952_; uint64_t v___y_2953_; uint8_t v___y_2954_; uint64_t v___y_2955_; uint64_t v___y_2960_; uint32_t v___y_2961_; uint64_t v___y_2962_; uint64_t v___y_2963_; uint64_t v___y_2964_; uint8_t v___y_2965_; uint64_t v___y_2966_; uint64_t v___y_2971_; uint64_t v___y_2972_; uint64_t v___y_2973_; uint32_t v___y_2974_; uint64_t v___y_2975_; uint64_t v___y_2976_; uint64_t v___y_2977_; uint8_t v___y_2978_; uint64_t v___y_2979_; uint64_t v___y_2984_; uint32_t v___y_2985_; uint64_t v___y_2986_; uint64_t v___y_2987_; uint64_t v___y_2988_; uint8_t v___y_2989_; uint64_t v___y_2990_; uint64_t v___y_2995_; uint64_t v___y_2996_; uint64_t v___y_2997_; uint32_t v___y_2998_; uint64_t v___y_2999_; uint64_t v___y_3000_; uint64_t v___y_3001_; uint8_t v___y_3002_; uint64_t v___y_3003_; uint64_t v___y_3008_; uint32_t v___y_3009_; uint64_t v___y_3010_; uint64_t v___y_3011_; uint64_t v___y_3012_; uint8_t v___y_3013_; uint64_t v___y_3014_; uint64_t v___y_3019_; uint32_t v___y_3020_; uint64_t v___y_3021_; uint64_t v___y_3022_; uint64_t v___y_3023_; uint8_t v___y_3024_; uint64_t v___y_3025_; uint32_t v___y_3029_; uint64_t v___y_3030_; uint64_t v___y_3031_; uint8_t v___y_3032_; uint64_t v___y_3041_; uint64_t v___y_3042_; uint32_t v___y_3043_; uint64_t v___y_3044_; uint8_t v___y_3045_; uint64_t v___y_3046_; uint32_t v_eu_3079_; uint32_t v___x_3080_; uint32_t v___x_3081_; uint32_t v___x_3082_; uint8_t v___x_3083_; 
v___x_2191_ = 23;
v___x_2192_ = lean_uint32_shift_right(v___y_1754_, v___x_2191_);
v___x_2232_ = 255;
v_eu_3079_ = lean_uint32_land(v___x_2192_, v___x_2232_);
v___x_3080_ = 1;
v___x_3081_ = lean_uint32_sub(v_eu_3079_, v___x_3080_);
v___x_3082_ = 253;
v___x_3083_ = lean_uint32_dec_le(v___x_3081_, v___x_3082_);
if (v___x_3083_ == 0)
{
uint32_t v___x_3084_; uint32_t v_ey_3085_; uint64_t v___y_3087_; uint64_t v___y_3088_; uint32_t v___y_3089_; uint8_t v___y_3090_; uint64_t v___y_3091_; uint32_t v___y_3098_; uint64_t v___y_3099_; uint8_t v___y_3100_; uint64_t v___y_3101_; uint32_t v___y_3108_; uint32_t v___y_3109_; uint8_t v___y_3110_; uint64_t v___y_3111_; uint8_t v___y_3119_; uint32_t v___x_3129_; uint32_t v___x_3130_; uint8_t v___x_3131_; uint8_t v___y_3133_; uint8_t v___y_3134_; uint8_t v___y_3135_; uint8_t v___y_3137_; uint8_t v___y_3138_; uint8_t v___y_3144_; 
v___x_3084_ = lean_uint32_shift_right(v___y_1755_, v___x_2191_);
v_ey_3085_ = lean_uint32_land(v___x_3084_, v___x_2232_);
v___x_3129_ = lean_uint32_add(v_eu_3079_, v_ey_3085_);
v___x_3130_ = 128;
v___x_3131_ = lean_uint32_dec_lt(v___x_3129_, v___x_3130_);
if (v___x_3131_ == 0)
{
uint32_t v___x_3153_; uint32_t v_a_3154_; uint32_t v___x_3155_; uint32_t v___x_3156_; uint8_t v___x_3157_; 
v___x_3153_ = 2147483647;
v_a_3154_ = lean_uint32_land(v___y_1754_, v___x_3153_);
v___x_3155_ = 201326591;
v___x_3156_ = lean_uint32_sub(v_a_3154_, v___x_3080_);
v___x_3157_ = lean_uint32_dec_le(v___x_3155_, v___x_3156_);
if (v___x_3157_ == 0)
{
v___y_2220_ = v___x_3157_;
goto v___jp_2219_;
}
else
{
uint32_t v___x_3158_; uint8_t v___x_3159_; 
v___x_3158_ = 2139095040;
v___x_3159_ = lean_uint32_dec_lt(v_a_3154_, v___x_3158_);
v___y_2220_ = v___x_3159_;
goto v___jp_2219_;
}
}
else
{
uint32_t v___x_3160_; uint32_t v___x_3161_; uint8_t v___x_3162_; 
v___x_3160_ = 4278190080;
v___x_3161_ = lean_uint32_shift_left(v___y_1754_, v___x_3080_);
v___x_3162_ = lean_uint32_dec_le(v___x_3160_, v___x_3161_);
if (v___x_3162_ == 0)
{
uint32_t v___x_3163_; uint8_t v___x_3164_; 
v___x_3163_ = lean_uint32_shift_left(v___y_1755_, v___x_3080_);
v___x_3164_ = lean_uint32_dec_le(v___x_3160_, v___x_3163_);
v___y_3144_ = v___x_3164_;
goto v___jp_3143_;
}
else
{
v___y_3144_ = v___x_3162_;
goto v___jp_3143_;
}
}
v___jp_3086_:
{
uint64_t v___x_3092_; uint64_t v___x_3093_; uint8_t v___x_3094_; 
v___x_3092_ = lean_uint32_to_uint64(v_ey_3085_);
v___x_3093_ = 0ULL;
v___x_3094_ = lean_uint64_dec_eq(v___x_3092_, v___x_3093_);
if (v___x_3094_ == 0)
{
uint64_t v___x_3095_; uint64_t v___x_3096_; 
v___x_3095_ = 1ULL;
v___x_3096_ = lean_uint64_sub(v___x_3092_, v___x_3095_);
v___y_3041_ = v___y_3087_;
v___y_3042_ = v___y_3091_;
v___y_3043_ = v___y_3089_;
v___y_3044_ = v___y_3088_;
v___y_3045_ = v___y_3090_;
v___y_3046_ = v___x_3096_;
goto v___jp_3040_;
}
else
{
v___y_3041_ = v___y_3087_;
v___y_3042_ = v___y_3091_;
v___y_3043_ = v___y_3089_;
v___y_3044_ = v___y_3088_;
v___y_3045_ = v___y_3090_;
v___y_3046_ = v___x_3093_;
goto v___jp_3040_;
}
}
v___jp_3097_:
{
uint64_t v___x_3102_; uint64_t v___x_3103_; uint8_t v___x_3104_; 
v___x_3102_ = lean_uint32_to_uint64(v_eu_3079_);
v___x_3103_ = 0ULL;
v___x_3104_ = lean_uint64_dec_eq(v___x_3102_, v___x_3103_);
if (v___x_3104_ == 0)
{
uint64_t v___x_3105_; uint64_t v___x_3106_; 
v___x_3105_ = 1ULL;
v___x_3106_ = lean_uint64_sub(v___x_3102_, v___x_3105_);
v___y_3087_ = v___y_3101_;
v___y_3088_ = v___y_3099_;
v___y_3089_ = v___y_3098_;
v___y_3090_ = v___y_3100_;
v___y_3091_ = v___x_3106_;
goto v___jp_3086_;
}
else
{
v___y_3087_ = v___y_3101_;
v___y_3088_ = v___y_3099_;
v___y_3089_ = v___y_3098_;
v___y_3090_ = v___y_3100_;
v___y_3091_ = v___x_3103_;
goto v___jp_3086_;
}
}
v___jp_3107_:
{
uint32_t v___x_3112_; uint8_t v___x_3113_; 
v___x_3112_ = 0;
v___x_3113_ = lean_uint32_dec_eq(v_ey_3085_, v___x_3112_);
if (v___x_3113_ == 0)
{
uint64_t v___x_3114_; uint64_t v___x_3115_; uint64_t v___x_3116_; 
v___x_3114_ = lean_uint32_to_uint64(v___y_3109_);
v___x_3115_ = 8388608ULL;
v___x_3116_ = lean_uint64_lor(v___x_3114_, v___x_3115_);
v___y_3098_ = v___y_3108_;
v___y_3099_ = v___y_3111_;
v___y_3100_ = v___y_3110_;
v___y_3101_ = v___x_3116_;
goto v___jp_3097_;
}
else
{
uint64_t v___x_3117_; 
v___x_3117_ = lean_uint32_to_uint64(v___y_3109_);
v___y_3098_ = v___y_3108_;
v___y_3099_ = v___y_3111_;
v___y_3100_ = v___y_3110_;
v___y_3101_ = v___x_3117_;
goto v___jp_3097_;
}
}
v___jp_3118_:
{
uint32_t v___x_3120_; uint32_t v_xFraction_3121_; uint32_t v_yFraction_3122_; uint32_t v___x_3123_; uint8_t v___x_3124_; 
v___x_3120_ = 8388607;
v_xFraction_3121_ = lean_uint32_land(v___y_1754_, v___x_3120_);
v_yFraction_3122_ = lean_uint32_land(v___y_1755_, v___x_3120_);
v___x_3123_ = 0;
v___x_3124_ = lean_uint32_dec_eq(v_eu_3079_, v___x_3123_);
if (v___x_3124_ == 0)
{
uint64_t v___x_3125_; uint64_t v___x_3126_; uint64_t v___x_3127_; 
v___x_3125_ = lean_uint32_to_uint64(v_xFraction_3121_);
v___x_3126_ = 8388608ULL;
v___x_3127_ = lean_uint64_lor(v___x_3125_, v___x_3126_);
v___y_3108_ = v___x_3120_;
v___y_3109_ = v_yFraction_3122_;
v___y_3110_ = v___y_3119_;
v___y_3111_ = v___x_3127_;
goto v___jp_3107_;
}
else
{
uint64_t v___x_3128_; 
v___x_3128_ = lean_uint32_to_uint64(v_xFraction_3121_);
v___y_3108_ = v___x_3120_;
v___y_3109_ = v_yFraction_3122_;
v___y_3110_ = v___y_3119_;
v___y_3111_ = v___x_3128_;
goto v___jp_3107_;
}
}
v___jp_3132_:
{
if (v___y_3133_ == 0)
{
if (v___y_3135_ == 0)
{
v___y_3119_ = v___y_3134_;
goto v___jp_3118_;
}
else
{
v___y_3119_ = v___x_3131_;
goto v___jp_3118_;
}
}
else
{
if (v___y_3135_ == 0)
{
v___y_3119_ = v___x_3131_;
goto v___jp_3118_;
}
else
{
v___y_3119_ = v___y_3134_;
goto v___jp_3118_;
}
}
}
v___jp_3136_:
{
uint32_t v___x_3139_; uint32_t v___x_3140_; uint32_t v___x_3141_; uint8_t v___x_3142_; 
v___x_3139_ = 2147483648;
v___x_3140_ = lean_uint32_land(v___y_1755_, v___x_3139_);
v___x_3141_ = 0;
v___x_3142_ = lean_uint32_dec_eq(v___x_3140_, v___x_3141_);
if (v___x_3142_ == 0)
{
v___y_3133_ = v___y_3138_;
v___y_3134_ = v___y_3137_;
v___y_3135_ = v___x_3131_;
goto v___jp_3132_;
}
else
{
v___y_3133_ = v___y_3138_;
v___y_3134_ = v___y_3137_;
v___y_3135_ = v___y_3137_;
goto v___jp_3132_;
}
}
v___jp_3143_:
{
if (v___y_3144_ == 0)
{
uint32_t v___x_3145_; uint32_t v___x_3146_; uint32_t v___x_3147_; uint8_t v___x_3148_; 
v___x_3145_ = 2147483648;
v___x_3146_ = lean_uint32_land(v___y_1754_, v___x_3145_);
v___x_3147_ = 0;
v___x_3148_ = lean_uint32_dec_eq(v___x_3146_, v___x_3147_);
if (v___x_3148_ == 0)
{
v___y_3137_ = v___y_3144_;
v___y_3138_ = v___x_3131_;
goto v___jp_3136_;
}
else
{
v___y_3137_ = v___y_3144_;
v___y_3138_ = v___y_3144_;
goto v___jp_3136_;
}
}
else
{
lean_object* v___x_3149_; lean_object* v___x_3150_; lean_object* v___x_3151_; uint32_t v___x_3152_; 
v___x_3149_ = lean_uint32_to_nat(v___y_1754_);
v___x_3150_ = lean_uint32_to_nat(v___y_1755_);
v___x_3151_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3149_, v___x_3150_);
v___x_3152_ = lean_uint32_of_nat(v___x_3151_);
lean_dec(v___x_3151_);
return v___x_3152_;
}
}
}
else
{
uint32_t v___x_3165_; uint32_t v_ev_3166_; uint8_t v___y_3168_; uint32_t v___y_3169_; uint64_t v___y_3170_; uint64_t v___y_3171_; uint64_t v___y_3172_; uint8_t v___y_3179_; uint32_t v___y_3180_; uint64_t v___y_3181_; uint64_t v___y_3182_; uint8_t v___y_3189_; uint32_t v___y_3190_; uint32_t v___y_3191_; uint64_t v___y_3192_; uint8_t v___y_3200_; uint64_t v___y_3211_; uint8_t v___y_3212_; uint32_t v___y_3213_; uint64_t v___y_3214_; uint64_t v___y_3215_; uint8_t v___y_3222_; uint64_t v___y_3223_; uint32_t v___y_3224_; uint64_t v___y_3225_; uint32_t v___y_3232_; uint8_t v___y_3233_; uint32_t v___y_3234_; uint64_t v___y_3235_; uint8_t v___y_3243_; uint8_t v___y_3254_; uint8_t v___y_3255_; uint8_t v___y_3257_; uint8_t v___y_3258_; uint8_t v___y_3259_; uint8_t v___y_3261_; uint8_t v___y_3262_; uint8_t v___y_3268_; uint32_t v___x_3277_; uint8_t v___x_3278_; uint8_t v___y_3280_; uint8_t v___y_3281_; uint8_t v___y_3283_; uint8_t v___y_3284_; uint8_t v___y_3285_; uint8_t v___y_3287_; uint8_t v___y_3288_; uint8_t v___y_3294_; 
v___x_3165_ = lean_uint32_shift_right(v___y_1755_, v___x_2191_);
v_ev_3166_ = lean_uint32_land(v___x_3165_, v___x_2232_);
v___x_3277_ = lean_uint32_sub(v_ev_3166_, v___x_3080_);
v___x_3278_ = lean_uint32_dec_le(v___x_3277_, v___x_3082_);
if (v___x_3278_ == 0)
{
uint32_t v___x_3303_; uint32_t v___x_3304_; uint8_t v___x_3305_; 
v___x_3303_ = lean_uint32_add(v_eu_3079_, v_ev_3166_);
v___x_3304_ = 128;
v___x_3305_ = lean_uint32_dec_lt(v___x_3303_, v___x_3304_);
if (v___x_3305_ == 0)
{
uint32_t v___x_3306_; uint32_t v_a_3307_; uint32_t v___x_3308_; uint32_t v___x_3309_; uint8_t v___x_3310_; 
v___x_3306_ = 2147483647;
v_a_3307_ = lean_uint32_land(v___y_1754_, v___x_3306_);
v___x_3308_ = 201326591;
v___x_3309_ = lean_uint32_sub(v_a_3307_, v___x_3080_);
v___x_3310_ = lean_uint32_dec_le(v___x_3308_, v___x_3309_);
if (v___x_3310_ == 0)
{
v___y_2207_ = v___x_3310_;
goto v___jp_2206_;
}
else
{
uint32_t v___x_3311_; uint8_t v___x_3312_; 
v___x_3311_ = 2139095040;
v___x_3312_ = lean_uint32_dec_lt(v_a_3307_, v___x_3311_);
v___y_2207_ = v___x_3312_;
goto v___jp_2206_;
}
}
else
{
uint32_t v___x_3313_; uint32_t v___x_3314_; uint8_t v___x_3315_; 
v___x_3313_ = 4278190080;
v___x_3314_ = lean_uint32_shift_left(v___y_1754_, v___x_3080_);
v___x_3315_ = lean_uint32_dec_le(v___x_3313_, v___x_3314_);
if (v___x_3315_ == 0)
{
uint32_t v___x_3316_; uint8_t v___x_3317_; 
v___x_3316_ = lean_uint32_shift_left(v___y_1755_, v___x_3080_);
v___x_3317_ = lean_uint32_dec_le(v___x_3313_, v___x_3316_);
v___y_3268_ = v___x_3317_;
goto v___jp_3267_;
}
else
{
v___y_3268_ = v___x_3315_;
goto v___jp_3267_;
}
}
}
else
{
uint32_t v_s_3318_; uint32_t v___x_3319_; uint32_t v___x_3320_; uint32_t v___x_3321_; uint8_t v___x_3322_; 
v_s_3318_ = lean_uint32_add(v_eu_3079_, v_ev_3166_);
v___x_3319_ = 128;
v___x_3320_ = lean_uint32_sub(v_s_3318_, v___x_3319_);
v___x_3321_ = 252;
v___x_3322_ = lean_uint32_dec_le(v___x_3320_, v___x_3321_);
if (v___x_3322_ == 0)
{
uint8_t v___x_3323_; 
v___x_3323_ = lean_uint32_dec_lt(v_s_3318_, v___x_3319_);
if (v___x_3323_ == 0)
{
uint32_t v___x_3324_; uint32_t v_a_3325_; uint32_t v___x_3326_; uint32_t v___x_3327_; uint8_t v___x_3328_; 
v___x_3324_ = 2147483647;
v_a_3325_ = lean_uint32_land(v___y_1754_, v___x_3324_);
v___x_3326_ = 201326591;
v___x_3327_ = lean_uint32_sub(v_a_3325_, v___x_3080_);
v___x_3328_ = lean_uint32_dec_le(v___x_3326_, v___x_3327_);
if (v___x_3328_ == 0)
{
v___y_2194_ = v___x_3328_;
goto v___jp_2193_;
}
else
{
uint32_t v___x_3329_; uint8_t v___x_3330_; 
v___x_3329_ = 2139095040;
v___x_3330_ = lean_uint32_dec_lt(v_a_3325_, v___x_3329_);
v___y_2194_ = v___x_3330_;
goto v___jp_2193_;
}
}
else
{
uint32_t v___x_3331_; uint32_t v___x_3332_; uint8_t v___x_3333_; 
v___x_3331_ = 4278190080;
v___x_3332_ = lean_uint32_shift_left(v___y_1754_, v___x_3080_);
v___x_3333_ = lean_uint32_dec_le(v___x_3331_, v___x_3332_);
if (v___x_3333_ == 0)
{
uint32_t v___x_3334_; uint8_t v___x_3335_; 
v___x_3334_ = lean_uint32_shift_left(v___y_1755_, v___x_3080_);
v___x_3335_ = lean_uint32_dec_le(v___x_3331_, v___x_3334_);
v___y_3294_ = v___x_3335_;
goto v___jp_3293_;
}
else
{
v___y_3294_ = v___x_3333_;
goto v___jp_3293_;
}
}
}
else
{
uint32_t v___x_3336_; uint32_t v___x_3337_; uint32_t v___x_3338_; uint32_t v___y_3340_; uint32_t v_a_3358_; uint32_t v___x_3359_; uint32_t v_b_3360_; uint64_t v___x_3361_; uint64_t v___x_3362_; uint64_t v_product_3363_; uint64_t v___x_3364_; uint64_t v___x_3365_; uint32_t v___x_3366_; uint64_t v___x_3367_; uint64_t v___x_3368_; uint64_t v___x_3369_; uint8_t v___x_3370_; 
v___x_3336_ = 8388607;
v___x_3337_ = lean_uint32_land(v___y_1754_, v___x_3336_);
v___x_3338_ = 8388608;
v_a_3358_ = lean_uint32_lor(v___x_3337_, v___x_3338_);
v___x_3359_ = lean_uint32_land(v___y_1755_, v___x_3336_);
v_b_3360_ = lean_uint32_lor(v___x_3359_, v___x_3338_);
v___x_3361_ = lean_uint32_to_uint64(v_a_3358_);
v___x_3362_ = lean_uint32_to_uint64(v_b_3360_);
v_product_3363_ = lean_uint64_mul(v___x_3361_, v___x_3362_);
v___x_3364_ = 17ULL;
v___x_3365_ = lean_uint64_shift_right(v_product_3363_, v___x_3364_);
v___x_3366_ = lean_uint64_to_uint32(v___x_3365_);
v___x_3367_ = 131071ULL;
v___x_3368_ = lean_uint64_land(v_product_3363_, v___x_3367_);
v___x_3369_ = 0ULL;
v___x_3370_ = lean_uint64_dec_eq(v___x_3368_, v___x_3369_);
if (v___x_3370_ == 0)
{
uint32_t v___x_3371_; 
v___x_3371_ = lean_uint32_lor(v___x_3366_, v___x_3080_);
v___y_3340_ = v___x_3371_;
goto v___jp_3339_;
}
else
{
v___y_3340_ = v___x_3366_;
goto v___jp_3339_;
}
v___jp_3339_:
{
float v___x_3341_; uint32_t v_r_3342_; uint32_t v___x_3343_; uint32_t v_high_3344_; uint32_t v___x_3345_; uint32_t v___x_3346_; uint32_t v_q_3347_; uint32_t v___x_3348_; uint32_t v___x_3349_; uint32_t v_e_3350_; uint32_t v___x_3351_; uint32_t v___x_3352_; uint32_t v___x_3353_; uint32_t v___x_3354_; uint32_t v___x_3355_; uint32_t v___x_3356_; uint32_t v___x_3357_; 
v___x_3341_ = lean_uint32_to_float32(v___y_3340_);
v_r_3342_ = lean_float32_to_uint32(v___x_3341_);
v___x_3343_ = 30;
v_high_3344_ = lean_uint32_shift_right(v_r_3342_, v___x_3343_);
v___x_3345_ = 6;
v___x_3346_ = lean_uint32_add(v___x_3345_, v_high_3344_);
v_q_3347_ = lean_uint32_shift_right(v_r_3342_, v___x_3346_);
v___x_3348_ = 127;
v___x_3349_ = lean_uint32_sub(v_s_3318_, v___x_3348_);
v_e_3350_ = lean_uint32_add(v___x_3349_, v_high_3344_);
v___x_3351_ = lean_uint32_xor(v___y_1754_, v___y_1755_);
v___x_3352_ = 2147483648;
v___x_3353_ = lean_uint32_land(v___x_3351_, v___x_3352_);
v___x_3354_ = lean_uint32_shift_left(v_e_3350_, v___x_2191_);
v___x_3355_ = lean_uint32_lor(v___x_3353_, v___x_3354_);
v___x_3356_ = lean_uint32_sub(v_q_3347_, v___x_3338_);
v___x_3357_ = lean_uint32_lor(v___x_3355_, v___x_3356_);
return v___x_3357_;
}
}
}
v___jp_3167_:
{
uint64_t v___x_3173_; uint64_t v___x_3174_; uint8_t v___x_3175_; 
v___x_3173_ = lean_uint32_to_uint64(v_ev_3166_);
v___x_3174_ = 0ULL;
v___x_3175_ = lean_uint64_dec_eq(v___x_3173_, v___x_3174_);
if (v___x_3175_ == 0)
{
uint64_t v___x_3176_; uint64_t v___x_3177_; 
v___x_3176_ = 1ULL;
v___x_3177_ = lean_uint64_sub(v___x_3173_, v___x_3176_);
v___y_2477_ = v___y_3168_;
v___y_2478_ = v___y_3172_;
v___y_2479_ = v___y_3169_;
v___y_2480_ = v___y_3170_;
v___y_2481_ = v___y_3171_;
v___y_2482_ = v___x_3177_;
goto v___jp_2476_;
}
else
{
v___y_2477_ = v___y_3168_;
v___y_2478_ = v___y_3172_;
v___y_2479_ = v___y_3169_;
v___y_2480_ = v___y_3170_;
v___y_2481_ = v___y_3171_;
v___y_2482_ = v___x_3174_;
goto v___jp_2476_;
}
}
v___jp_3178_:
{
uint64_t v___x_3183_; uint64_t v___x_3184_; uint8_t v___x_3185_; 
v___x_3183_ = lean_uint32_to_uint64(v_eu_3079_);
v___x_3184_ = 0ULL;
v___x_3185_ = lean_uint64_dec_eq(v___x_3183_, v___x_3184_);
if (v___x_3185_ == 0)
{
uint64_t v___x_3186_; uint64_t v___x_3187_; 
v___x_3186_ = 1ULL;
v___x_3187_ = lean_uint64_sub(v___x_3183_, v___x_3186_);
v___y_3168_ = v___y_3179_;
v___y_3169_ = v___y_3180_;
v___y_3170_ = v___y_3182_;
v___y_3171_ = v___y_3181_;
v___y_3172_ = v___x_3187_;
goto v___jp_3167_;
}
else
{
v___y_3168_ = v___y_3179_;
v___y_3169_ = v___y_3180_;
v___y_3170_ = v___y_3182_;
v___y_3171_ = v___y_3181_;
v___y_3172_ = v___x_3184_;
goto v___jp_3167_;
}
}
v___jp_3188_:
{
uint32_t v___x_3193_; uint8_t v___x_3194_; 
v___x_3193_ = 0;
v___x_3194_ = lean_uint32_dec_eq(v_ev_3166_, v___x_3193_);
if (v___x_3194_ == 0)
{
uint64_t v___x_3195_; uint64_t v___x_3196_; uint64_t v___x_3197_; 
v___x_3195_ = lean_uint32_to_uint64(v___y_3191_);
v___x_3196_ = 8388608ULL;
v___x_3197_ = lean_uint64_lor(v___x_3195_, v___x_3196_);
v___y_3179_ = v___y_3189_;
v___y_3180_ = v___y_3190_;
v___y_3181_ = v___y_3192_;
v___y_3182_ = v___x_3197_;
goto v___jp_3178_;
}
else
{
uint64_t v___x_3198_; 
v___x_3198_ = lean_uint32_to_uint64(v___y_3191_);
v___y_3179_ = v___y_3189_;
v___y_3180_ = v___y_3190_;
v___y_3181_ = v___y_3192_;
v___y_3182_ = v___x_3198_;
goto v___jp_3178_;
}
}
v___jp_3199_:
{
uint32_t v___x_3201_; uint32_t v_xFraction_3202_; uint32_t v_yFraction_3203_; uint32_t v___x_3204_; uint8_t v___x_3205_; 
v___x_3201_ = 8388607;
v_xFraction_3202_ = lean_uint32_land(v___y_1754_, v___x_3201_);
v_yFraction_3203_ = lean_uint32_land(v___y_1755_, v___x_3201_);
v___x_3204_ = 0;
v___x_3205_ = lean_uint32_dec_eq(v_eu_3079_, v___x_3204_);
if (v___x_3205_ == 0)
{
uint64_t v___x_3206_; uint64_t v___x_3207_; uint64_t v___x_3208_; 
v___x_3206_ = lean_uint32_to_uint64(v_xFraction_3202_);
v___x_3207_ = 8388608ULL;
v___x_3208_ = lean_uint64_lor(v___x_3206_, v___x_3207_);
v___y_3189_ = v___y_3200_;
v___y_3190_ = v___x_3201_;
v___y_3191_ = v_yFraction_3203_;
v___y_3192_ = v___x_3208_;
goto v___jp_3188_;
}
else
{
uint64_t v___x_3209_; 
v___x_3209_ = lean_uint32_to_uint64(v_xFraction_3202_);
v___y_3189_ = v___y_3200_;
v___y_3190_ = v___x_3201_;
v___y_3191_ = v_yFraction_3203_;
v___y_3192_ = v___x_3209_;
goto v___jp_3188_;
}
}
v___jp_3210_:
{
uint64_t v___x_3216_; uint64_t v___x_3217_; uint8_t v___x_3218_; 
v___x_3216_ = lean_uint32_to_uint64(v_ev_3166_);
v___x_3217_ = 0ULL;
v___x_3218_ = lean_uint64_dec_eq(v___x_3216_, v___x_3217_);
if (v___x_3218_ == 0)
{
uint64_t v___x_3219_; uint64_t v___x_3220_; 
v___x_3219_ = 1ULL;
v___x_3220_ = lean_uint64_sub(v___x_3216_, v___x_3219_);
v___y_2759_ = v___y_3215_;
v___y_2760_ = v___y_3212_;
v___y_2761_ = v___y_3211_;
v___y_2762_ = v___y_3213_;
v___y_2763_ = v___y_3214_;
v___y_2764_ = v___x_3220_;
goto v___jp_2758_;
}
else
{
v___y_2759_ = v___y_3215_;
v___y_2760_ = v___y_3212_;
v___y_2761_ = v___y_3211_;
v___y_2762_ = v___y_3213_;
v___y_2763_ = v___y_3214_;
v___y_2764_ = v___x_3217_;
goto v___jp_2758_;
}
}
v___jp_3221_:
{
uint64_t v___x_3226_; uint64_t v___x_3227_; uint8_t v___x_3228_; 
v___x_3226_ = lean_uint32_to_uint64(v_eu_3079_);
v___x_3227_ = 0ULL;
v___x_3228_ = lean_uint64_dec_eq(v___x_3226_, v___x_3227_);
if (v___x_3228_ == 0)
{
uint64_t v___x_3229_; uint64_t v___x_3230_; 
v___x_3229_ = 1ULL;
v___x_3230_ = lean_uint64_sub(v___x_3226_, v___x_3229_);
v___y_3211_ = v___y_3223_;
v___y_3212_ = v___y_3222_;
v___y_3213_ = v___y_3224_;
v___y_3214_ = v___y_3225_;
v___y_3215_ = v___x_3230_;
goto v___jp_3210_;
}
else
{
v___y_3211_ = v___y_3223_;
v___y_3212_ = v___y_3222_;
v___y_3213_ = v___y_3224_;
v___y_3214_ = v___y_3225_;
v___y_3215_ = v___x_3227_;
goto v___jp_3210_;
}
}
v___jp_3231_:
{
uint32_t v___x_3236_; uint8_t v___x_3237_; 
v___x_3236_ = 0;
v___x_3237_ = lean_uint32_dec_eq(v_ev_3166_, v___x_3236_);
if (v___x_3237_ == 0)
{
uint64_t v___x_3238_; uint64_t v___x_3239_; uint64_t v___x_3240_; 
v___x_3238_ = lean_uint32_to_uint64(v___y_3232_);
v___x_3239_ = 8388608ULL;
v___x_3240_ = lean_uint64_lor(v___x_3238_, v___x_3239_);
v___y_3222_ = v___y_3233_;
v___y_3223_ = v___y_3235_;
v___y_3224_ = v___y_3234_;
v___y_3225_ = v___x_3240_;
goto v___jp_3221_;
}
else
{
uint64_t v___x_3241_; 
v___x_3241_ = lean_uint32_to_uint64(v___y_3232_);
v___y_3222_ = v___y_3233_;
v___y_3223_ = v___y_3235_;
v___y_3224_ = v___y_3234_;
v___y_3225_ = v___x_3241_;
goto v___jp_3221_;
}
}
v___jp_3242_:
{
uint32_t v___x_3244_; uint32_t v_xFraction_3245_; uint32_t v_yFraction_3246_; uint32_t v___x_3247_; uint8_t v___x_3248_; 
v___x_3244_ = 8388607;
v_xFraction_3245_ = lean_uint32_land(v___y_1754_, v___x_3244_);
v_yFraction_3246_ = lean_uint32_land(v___y_1755_, v___x_3244_);
v___x_3247_ = 0;
v___x_3248_ = lean_uint32_dec_eq(v_eu_3079_, v___x_3247_);
if (v___x_3248_ == 0)
{
uint64_t v___x_3249_; uint64_t v___x_3250_; uint64_t v___x_3251_; 
v___x_3249_ = lean_uint32_to_uint64(v_xFraction_3245_);
v___x_3250_ = 8388608ULL;
v___x_3251_ = lean_uint64_lor(v___x_3249_, v___x_3250_);
v___y_3232_ = v_yFraction_3246_;
v___y_3233_ = v___y_3243_;
v___y_3234_ = v___x_3244_;
v___y_3235_ = v___x_3251_;
goto v___jp_3231_;
}
else
{
uint64_t v___x_3252_; 
v___x_3252_ = lean_uint32_to_uint64(v_xFraction_3245_);
v___y_3232_ = v_yFraction_3246_;
v___y_3233_ = v___y_3243_;
v___y_3234_ = v___x_3244_;
v___y_3235_ = v___x_3252_;
goto v___jp_3231_;
}
}
v___jp_3253_:
{
if (v___y_3255_ == 0)
{
v___y_3243_ = v___x_3083_;
goto v___jp_3242_;
}
else
{
v___y_3243_ = v___y_3254_;
goto v___jp_3242_;
}
}
v___jp_3256_:
{
if (v___y_3258_ == 0)
{
if (v___y_3259_ == 0)
{
v___y_3254_ = v___y_3257_;
v___y_3255_ = v___x_3083_;
goto v___jp_3253_;
}
else
{
v___y_3243_ = v___x_3083_;
goto v___jp_3242_;
}
}
else
{
v___y_3254_ = v___y_3257_;
v___y_3255_ = v___y_3259_;
goto v___jp_3253_;
}
}
v___jp_3260_:
{
uint32_t v___x_3263_; uint32_t v___x_3264_; uint32_t v___x_3265_; uint8_t v___x_3266_; 
v___x_3263_ = 2147483648;
v___x_3264_ = lean_uint32_land(v___y_1755_, v___x_3263_);
v___x_3265_ = 0;
v___x_3266_ = lean_uint32_dec_eq(v___x_3264_, v___x_3265_);
if (v___x_3266_ == 0)
{
v___y_3257_ = v___y_3261_;
v___y_3258_ = v___y_3262_;
v___y_3259_ = v___x_3083_;
goto v___jp_3256_;
}
else
{
v___y_3257_ = v___y_3261_;
v___y_3258_ = v___y_3262_;
v___y_3259_ = v___y_3261_;
goto v___jp_3256_;
}
}
v___jp_3267_:
{
if (v___y_3268_ == 0)
{
uint32_t v___x_3269_; uint32_t v___x_3270_; uint32_t v___x_3271_; uint8_t v___x_3272_; 
v___x_3269_ = 2147483648;
v___x_3270_ = lean_uint32_land(v___y_1754_, v___x_3269_);
v___x_3271_ = 0;
v___x_3272_ = lean_uint32_dec_eq(v___x_3270_, v___x_3271_);
if (v___x_3272_ == 0)
{
v___y_3261_ = v___y_3268_;
v___y_3262_ = v___x_3083_;
goto v___jp_3260_;
}
else
{
v___y_3261_ = v___y_3268_;
v___y_3262_ = v___y_3268_;
goto v___jp_3260_;
}
}
else
{
lean_object* v___x_3273_; lean_object* v___x_3274_; lean_object* v___x_3275_; uint32_t v___x_3276_; 
v___x_3273_ = lean_uint32_to_nat(v___y_1754_);
v___x_3274_ = lean_uint32_to_nat(v___y_1755_);
v___x_3275_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3273_, v___x_3274_);
v___x_3276_ = lean_uint32_of_nat(v___x_3275_);
lean_dec(v___x_3275_);
return v___x_3276_;
}
}
v___jp_3279_:
{
if (v___y_3281_ == 0)
{
v___y_3200_ = v___x_3278_;
goto v___jp_3199_;
}
else
{
v___y_3200_ = v___y_3280_;
goto v___jp_3199_;
}
}
v___jp_3282_:
{
if (v___y_3283_ == 0)
{
if (v___y_3285_ == 0)
{
v___y_3280_ = v___y_3284_;
v___y_3281_ = v___x_3278_;
goto v___jp_3279_;
}
else
{
v___y_3200_ = v___x_3278_;
goto v___jp_3199_;
}
}
else
{
v___y_3280_ = v___y_3284_;
v___y_3281_ = v___y_3285_;
goto v___jp_3279_;
}
}
v___jp_3286_:
{
uint32_t v___x_3289_; uint32_t v___x_3290_; uint32_t v___x_3291_; uint8_t v___x_3292_; 
v___x_3289_ = 2147483648;
v___x_3290_ = lean_uint32_land(v___y_1755_, v___x_3289_);
v___x_3291_ = 0;
v___x_3292_ = lean_uint32_dec_eq(v___x_3290_, v___x_3291_);
if (v___x_3292_ == 0)
{
v___y_3283_ = v___y_3288_;
v___y_3284_ = v___y_3287_;
v___y_3285_ = v___x_3278_;
goto v___jp_3282_;
}
else
{
v___y_3283_ = v___y_3288_;
v___y_3284_ = v___y_3287_;
v___y_3285_ = v___y_3287_;
goto v___jp_3282_;
}
}
v___jp_3293_:
{
if (v___y_3294_ == 0)
{
uint32_t v___x_3295_; uint32_t v___x_3296_; uint32_t v___x_3297_; uint8_t v___x_3298_; 
v___x_3295_ = 2147483648;
v___x_3296_ = lean_uint32_land(v___y_1754_, v___x_3295_);
v___x_3297_ = 0;
v___x_3298_ = lean_uint32_dec_eq(v___x_3296_, v___x_3297_);
if (v___x_3298_ == 0)
{
v___y_3287_ = v___y_3294_;
v___y_3288_ = v___x_3278_;
goto v___jp_3286_;
}
else
{
v___y_3287_ = v___y_3294_;
v___y_3288_ = v___y_3294_;
goto v___jp_3286_;
}
}
else
{
lean_object* v___x_3299_; lean_object* v___x_3300_; lean_object* v___x_3301_; uint32_t v___x_3302_; 
v___x_3299_ = lean_uint32_to_nat(v___y_1754_);
v___x_3300_ = lean_uint32_to_nat(v___y_1755_);
v___x_3301_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3299_, v___x_3300_);
v___x_3302_ = lean_uint32_of_nat(v___x_3301_);
lean_dec(v___x_3301_);
return v___x_3302_;
}
}
}
v___jp_1756_:
{
uint32_t v___x_1758_; uint32_t v___x_1759_; 
v___x_1758_ = 8388608;
v___x_1759_ = lean_uint32_lor(v___y_1757_, v___x_1758_);
return v___x_1759_;
}
v___jp_1760_:
{
uint32_t v___x_1762_; uint32_t v___x_1763_; 
v___x_1762_ = 8388608;
v___x_1763_ = lean_uint32_lor(v___y_1761_, v___x_1762_);
return v___x_1763_;
}
v___jp_1764_:
{
uint32_t v___x_1768_; uint32_t v___x_1769_; 
v___x_1768_ = lean_uint32_land(v___y_1766_, v___y_1765_);
v___x_1769_ = lean_uint32_lor(v___y_1767_, v___x_1768_);
return v___x_1769_;
}
v___jp_1770_:
{
uint8_t v___x_1775_; 
v___x_1775_ = lean_uint64_dec_eq(v___y_1774_, v___y_1773_);
if (v___x_1775_ == 0)
{
uint64_t v___x_1776_; uint8_t v___x_1777_; 
v___x_1776_ = 8388608ULL;
v___x_1777_ = lean_uint64_dec_eq(v___y_1774_, v___x_1776_);
if (v___x_1777_ == 0)
{
uint32_t v___x_1778_; 
v___x_1778_ = lean_uint64_to_uint32(v___y_1774_);
if (v___y_1771_ == 0)
{
uint32_t v___x_1779_; 
v___x_1779_ = 0;
v___y_1765_ = v___y_1772_;
v___y_1766_ = v___x_1778_;
v___y_1767_ = v___x_1779_;
goto v___jp_1764_;
}
else
{
uint32_t v___x_1780_; 
v___x_1780_ = 2147483648;
v___y_1765_ = v___y_1772_;
v___y_1766_ = v___x_1778_;
v___y_1767_ = v___x_1780_;
goto v___jp_1764_;
}
}
else
{
if (v___y_1771_ == 0)
{
uint32_t v___x_1781_; 
v___x_1781_ = 0;
v___y_1761_ = v___x_1781_;
goto v___jp_1760_;
}
else
{
uint32_t v___x_1782_; 
v___x_1782_ = 2147483648;
v___y_1761_ = v___x_1782_;
goto v___jp_1760_;
}
}
}
else
{
if (v___y_1771_ == 0)
{
uint32_t v___x_1783_; 
v___x_1783_ = 0;
return v___x_1783_;
}
else
{
uint32_t v___x_1784_; 
v___x_1784_ = 2147483648;
return v___x_1784_;
}
}
}
v___jp_1785_:
{
uint32_t v___x_1789_; uint32_t v___x_1790_; 
v___x_1789_ = lean_uint32_land(v___y_1787_, v___y_1786_);
v___x_1790_ = lean_uint32_lor(v___y_1788_, v___x_1789_);
return v___x_1790_;
}
v___jp_1791_:
{
uint8_t v___x_1796_; 
v___x_1796_ = lean_uint64_dec_eq(v___y_1795_, v___y_1794_);
if (v___x_1796_ == 0)
{
uint64_t v___x_1797_; uint8_t v___x_1798_; 
v___x_1797_ = 8388608ULL;
v___x_1798_ = lean_uint64_dec_eq(v___y_1795_, v___x_1797_);
if (v___x_1798_ == 0)
{
uint32_t v___x_1799_; 
v___x_1799_ = lean_uint64_to_uint32(v___y_1795_);
if (v___y_1792_ == 0)
{
uint32_t v___x_1800_; 
v___x_1800_ = 0;
v___y_1786_ = v___y_1793_;
v___y_1787_ = v___x_1799_;
v___y_1788_ = v___x_1800_;
goto v___jp_1785_;
}
else
{
uint32_t v___x_1801_; 
v___x_1801_ = 2147483648;
v___y_1786_ = v___y_1793_;
v___y_1787_ = v___x_1799_;
v___y_1788_ = v___x_1801_;
goto v___jp_1785_;
}
}
else
{
if (v___y_1792_ == 0)
{
uint32_t v___x_1802_; 
v___x_1802_ = 0;
v___y_1757_ = v___x_1802_;
goto v___jp_1756_;
}
else
{
uint32_t v___x_1803_; 
v___x_1803_ = 2147483648;
v___y_1757_ = v___x_1803_;
goto v___jp_1756_;
}
}
}
else
{
if (v___y_1792_ == 0)
{
uint32_t v___x_1804_; 
v___x_1804_ = 0;
return v___x_1804_;
}
else
{
uint32_t v___x_1805_; 
v___x_1805_ = 2147483648;
return v___x_1805_;
}
}
}
v___jp_1806_:
{
if (v___y_1807_ == 0)
{
uint32_t v___x_1808_; 
v___x_1808_ = lp_competition_R19Base_FastMul_mul(v___y_1754_, v___y_1755_);
return v___x_1808_;
}
else
{
uint32_t v___x_1809_; uint32_t v___x_1810_; 
v___x_1809_ = 4194304;
v___x_1810_ = lean_uint32_lor(v___y_1755_, v___x_1809_);
return v___x_1810_;
}
}
v___jp_1811_:
{
uint32_t v___x_1812_; uint32_t v___x_1813_; uint32_t v___x_1814_; uint32_t v___x_1815_; uint8_t v___x_1816_; 
v___x_1812_ = 23;
v___x_1813_ = lean_uint32_shift_right(v___y_1755_, v___x_1812_);
v___x_1814_ = 255;
v___x_1815_ = lean_uint32_land(v___x_1813_, v___x_1814_);
v___x_1816_ = lean_uint32_dec_eq(v___x_1815_, v___x_1814_);
if (v___x_1816_ == 0)
{
v___y_1807_ = v___x_1816_;
goto v___jp_1806_;
}
else
{
uint32_t v___x_1817_; uint32_t v___x_1818_; uint32_t v___x_1819_; uint8_t v___x_1820_; 
v___x_1817_ = 8388607;
v___x_1818_ = lean_uint32_land(v___y_1755_, v___x_1817_);
v___x_1819_ = 0;
v___x_1820_ = lean_uint32_dec_eq(v___x_1818_, v___x_1819_);
if (v___x_1820_ == 0)
{
v___y_1807_ = v___x_1816_;
goto v___jp_1806_;
}
else
{
uint32_t v___x_1821_; 
v___x_1821_ = lp_competition_R19Base_FastMul_mul(v___y_1754_, v___y_1755_);
return v___x_1821_;
}
}
}
v___jp_1822_:
{
if (v___y_1823_ == 0)
{
goto v___jp_1811_;
}
else
{
uint32_t v___x_1824_; uint32_t v___x_1825_; 
v___x_1824_ = 4194304;
v___x_1825_ = lean_uint32_lor(v___y_1754_, v___x_1824_);
return v___x_1825_;
}
}
v___jp_1826_:
{
uint32_t v___x_1827_; uint32_t v___x_1828_; uint32_t v___x_1829_; uint32_t v___x_1830_; uint8_t v___x_1831_; 
v___x_1827_ = 23;
v___x_1828_ = lean_uint32_shift_right(v___y_1754_, v___x_1827_);
v___x_1829_ = 255;
v___x_1830_ = lean_uint32_land(v___x_1828_, v___x_1829_);
v___x_1831_ = lean_uint32_dec_eq(v___x_1830_, v___x_1829_);
if (v___x_1831_ == 0)
{
v___y_1823_ = v___x_1831_;
goto v___jp_1822_;
}
else
{
uint32_t v___x_1832_; uint32_t v___x_1833_; uint32_t v___x_1834_; uint8_t v___x_1835_; 
v___x_1832_ = 8388607;
v___x_1833_ = lean_uint32_land(v___y_1754_, v___x_1832_);
v___x_1834_ = 0;
v___x_1835_ = lean_uint32_dec_eq(v___x_1833_, v___x_1834_);
if (v___x_1835_ == 0)
{
v___y_1823_ = v___x_1831_;
goto v___jp_1822_;
}
else
{
goto v___jp_1811_;
}
}
}
v___jp_1836_:
{
if (v___y_1837_ == 0)
{
goto v___jp_1826_;
}
else
{
uint32_t v___x_1838_; uint32_t v___x_1839_; uint32_t v___x_1840_; uint8_t v___x_1841_; 
v___x_1838_ = 4194304;
v___x_1839_ = lean_uint32_land(v___y_1755_, v___x_1838_);
v___x_1840_ = 0;
v___x_1841_ = lean_uint32_dec_eq(v___x_1839_, v___x_1840_);
if (v___x_1841_ == 0)
{
goto v___jp_1826_;
}
else
{
uint32_t v___x_1842_; 
v___x_1842_ = lean_uint32_lor(v___y_1755_, v___x_1838_);
return v___x_1842_;
}
}
}
v___jp_1843_:
{
uint32_t v___x_1844_; uint32_t v___x_1845_; uint32_t v___x_1846_; uint32_t v___x_1847_; uint8_t v___x_1848_; 
v___x_1844_ = 23;
v___x_1845_ = lean_uint32_shift_right(v___y_1755_, v___x_1844_);
v___x_1846_ = 255;
v___x_1847_ = lean_uint32_land(v___x_1845_, v___x_1846_);
v___x_1848_ = lean_uint32_dec_eq(v___x_1847_, v___x_1846_);
if (v___x_1848_ == 0)
{
v___y_1837_ = v___x_1848_;
goto v___jp_1836_;
}
else
{
uint32_t v___x_1849_; uint32_t v___x_1850_; uint32_t v___x_1851_; uint8_t v___x_1852_; 
v___x_1849_ = 8388607;
v___x_1850_ = lean_uint32_land(v___y_1755_, v___x_1849_);
v___x_1851_ = 0;
v___x_1852_ = lean_uint32_dec_eq(v___x_1850_, v___x_1851_);
if (v___x_1852_ == 0)
{
v___y_1837_ = v___x_1848_;
goto v___jp_1836_;
}
else
{
goto v___jp_1826_;
}
}
}
v___jp_1853_:
{
if (v___y_1854_ == 0)
{
goto v___jp_1843_;
}
else
{
uint32_t v___x_1855_; uint32_t v___x_1856_; uint32_t v___x_1857_; uint8_t v___x_1858_; 
v___x_1855_ = 4194304;
v___x_1856_ = lean_uint32_land(v___y_1754_, v___x_1855_);
v___x_1857_ = 0;
v___x_1858_ = lean_uint32_dec_eq(v___x_1856_, v___x_1857_);
if (v___x_1858_ == 0)
{
goto v___jp_1843_;
}
else
{
uint32_t v___x_1859_; 
v___x_1859_ = lean_uint32_lor(v___y_1754_, v___x_1855_);
return v___x_1859_;
}
}
}
v___jp_1860_:
{
float v_result_1863_; uint8_t v___x_1864_; 
v_result_1863_ = lean_float32_mul(v___y_1861_, v___y_1862_);
v___x_1864_ = lean_float32_beq(v_result_1863_, v_result_1863_);
if (v___x_1864_ == 0)
{
uint32_t v___x_1865_; uint32_t v___x_1866_; uint32_t v___x_1867_; uint32_t v___x_1868_; uint8_t v___x_1869_; 
v___x_1865_ = 23;
v___x_1866_ = lean_uint32_shift_right(v___y_1754_, v___x_1865_);
v___x_1867_ = 255;
v___x_1868_ = lean_uint32_land(v___x_1866_, v___x_1867_);
v___x_1869_ = lean_uint32_dec_eq(v___x_1868_, v___x_1867_);
if (v___x_1869_ == 0)
{
v___y_1854_ = v___x_1869_;
goto v___jp_1853_;
}
else
{
uint32_t v___x_1870_; uint32_t v___x_1871_; uint32_t v___x_1872_; uint8_t v___x_1873_; 
v___x_1870_ = 8388607;
v___x_1871_ = lean_uint32_land(v___y_1754_, v___x_1870_);
v___x_1872_ = 0;
v___x_1873_ = lean_uint32_dec_eq(v___x_1871_, v___x_1872_);
if (v___x_1873_ == 0)
{
v___y_1854_ = v___x_1869_;
goto v___jp_1853_;
}
else
{
goto v___jp_1843_;
}
}
}
else
{
uint32_t v___x_1874_; 
v___x_1874_ = lean_float32_to_bits(v_result_1863_);
return v___x_1874_;
}
}
v___jp_1875_:
{
if (v___y_1877_ == 0)
{
float v___x_1878_; 
v___x_1878_ = lean_float32_of_bits(v___y_1755_);
v___y_1861_ = v___y_1876_;
v___y_1862_ = v___x_1878_;
goto v___jp_1860_;
}
else
{
uint32_t v___x_1879_; uint32_t v___x_1880_; uint32_t v___x_1881_; uint32_t v___x_1882_; float v___x_1883_; lean_object* v___x_1884_; uint32_t v___x_1885_; uint32_t v___x_1886_; lean_object* v___x_1887_; lean_object* v___x_1888_; float v___x_1889_; float v___x_1890_; 
v___x_1879_ = 8388607;
v___x_1880_ = lean_uint32_land(v___y_1755_, v___x_1879_);
v___x_1881_ = 8388608;
v___x_1882_ = lean_uint32_lor(v___x_1880_, v___x_1881_);
v___x_1883_ = lean_uint32_to_float32(v___x_1882_);
v___x_1884_ = lp_competition_R2W01b_scaleTable;
v___x_1885_ = 23;
v___x_1886_ = lean_uint32_shift_right(v___y_1755_, v___x_1885_);
v___x_1887_ = lean_uint32_to_nat(v___x_1886_);
v___x_1888_ = lean_array_fget_borrowed(v___x_1884_, v___x_1887_);
lean_dec(v___x_1887_);
v___x_1889_ = lean_unbox_float32(v___x_1888_);
v___x_1890_ = lean_float32_mul(v___x_1883_, v___x_1889_);
v___y_1861_ = v___y_1876_;
v___y_1862_ = v___x_1890_;
goto v___jp_1860_;
}
}
v___jp_1891_:
{
uint32_t v___x_1893_; uint32_t v_a_1894_; uint32_t v___x_1895_; uint32_t v___x_1896_; uint32_t v___x_1897_; uint8_t v___x_1898_; 
v___x_1893_ = 2147483647;
v_a_1894_ = lean_uint32_land(v___y_1755_, v___x_1893_);
v___x_1895_ = 201326591;
v___x_1896_ = 1;
v___x_1897_ = lean_uint32_sub(v_a_1894_, v___x_1896_);
v___x_1898_ = lean_uint32_dec_le(v___x_1895_, v___x_1897_);
if (v___x_1898_ == 0)
{
v___y_1876_ = v___y_1892_;
v___y_1877_ = v___x_1898_;
goto v___jp_1875_;
}
else
{
uint32_t v___x_1899_; uint8_t v___x_1900_; 
v___x_1899_ = 2139095040;
v___x_1900_ = lean_uint32_dec_lt(v_a_1894_, v___x_1899_);
v___y_1876_ = v___y_1892_;
v___y_1877_ = v___x_1900_;
goto v___jp_1875_;
}
}
v___jp_1901_:
{
uint32_t v___x_1903_; uint32_t v___x_1904_; 
v___x_1903_ = 8388608;
v___x_1904_ = lean_uint32_lor(v___y_1902_, v___x_1903_);
return v___x_1904_;
}
v___jp_1905_:
{
uint32_t v___x_1907_; uint32_t v___x_1908_; 
v___x_1907_ = 8388608;
v___x_1908_ = lean_uint32_lor(v___y_1906_, v___x_1907_);
return v___x_1908_;
}
v___jp_1909_:
{
uint32_t v___x_1913_; uint32_t v___x_1914_; 
v___x_1913_ = lean_uint32_land(v___y_1910_, v___y_1911_);
v___x_1914_ = lean_uint32_lor(v___y_1912_, v___x_1913_);
return v___x_1914_;
}
v___jp_1915_:
{
uint8_t v___x_1920_; 
v___x_1920_ = lean_uint64_dec_eq(v___y_1919_, v___y_1918_);
if (v___x_1920_ == 0)
{
uint64_t v___x_1921_; uint8_t v___x_1922_; 
v___x_1921_ = 8388608ULL;
v___x_1922_ = lean_uint64_dec_eq(v___y_1919_, v___x_1921_);
if (v___x_1922_ == 0)
{
uint32_t v___x_1923_; 
v___x_1923_ = lean_uint64_to_uint32(v___y_1919_);
if (v___y_1916_ == 0)
{
uint32_t v___x_1924_; 
v___x_1924_ = 0;
v___y_1910_ = v___x_1923_;
v___y_1911_ = v___y_1917_;
v___y_1912_ = v___x_1924_;
goto v___jp_1909_;
}
else
{
uint32_t v___x_1925_; 
v___x_1925_ = 2147483648;
v___y_1910_ = v___x_1923_;
v___y_1911_ = v___y_1917_;
v___y_1912_ = v___x_1925_;
goto v___jp_1909_;
}
}
else
{
if (v___y_1916_ == 0)
{
uint32_t v___x_1926_; 
v___x_1926_ = 0;
v___y_1902_ = v___x_1926_;
goto v___jp_1901_;
}
else
{
uint32_t v___x_1927_; 
v___x_1927_ = 2147483648;
v___y_1902_ = v___x_1927_;
goto v___jp_1901_;
}
}
}
else
{
if (v___y_1916_ == 0)
{
uint32_t v___x_1928_; 
v___x_1928_ = 0;
return v___x_1928_;
}
else
{
uint32_t v___x_1929_; 
v___x_1929_ = 2147483648;
return v___x_1929_;
}
}
}
v___jp_1930_:
{
uint32_t v___x_1934_; uint32_t v___x_1935_; 
v___x_1934_ = lean_uint32_land(v___y_1931_, v___y_1932_);
v___x_1935_ = lean_uint32_lor(v___y_1933_, v___x_1934_);
return v___x_1935_;
}
v___jp_1936_:
{
uint8_t v___x_1941_; 
v___x_1941_ = lean_uint64_dec_eq(v___y_1940_, v___y_1939_);
if (v___x_1941_ == 0)
{
uint64_t v___x_1942_; uint8_t v___x_1943_; 
v___x_1942_ = 8388608ULL;
v___x_1943_ = lean_uint64_dec_eq(v___y_1940_, v___x_1942_);
if (v___x_1943_ == 0)
{
uint32_t v___x_1944_; 
v___x_1944_ = lean_uint64_to_uint32(v___y_1940_);
if (v___y_1937_ == 0)
{
uint32_t v___x_1945_; 
v___x_1945_ = 0;
v___y_1931_ = v___x_1944_;
v___y_1932_ = v___y_1938_;
v___y_1933_ = v___x_1945_;
goto v___jp_1930_;
}
else
{
uint32_t v___x_1946_; 
v___x_1946_ = 2147483648;
v___y_1931_ = v___x_1944_;
v___y_1932_ = v___y_1938_;
v___y_1933_ = v___x_1946_;
goto v___jp_1930_;
}
}
else
{
if (v___y_1937_ == 0)
{
uint32_t v___x_1947_; 
v___x_1947_ = 0;
v___y_1906_ = v___x_1947_;
goto v___jp_1905_;
}
else
{
uint32_t v___x_1948_; 
v___x_1948_ = 2147483648;
v___y_1906_ = v___x_1948_;
goto v___jp_1905_;
}
}
}
else
{
if (v___y_1937_ == 0)
{
uint32_t v___x_1949_; 
v___x_1949_ = 0;
return v___x_1949_;
}
else
{
uint32_t v___x_1950_; 
v___x_1950_ = 2147483648;
return v___x_1950_;
}
}
}
v___jp_1951_:
{
if (v___y_1952_ == 0)
{
uint32_t v___x_1953_; 
v___x_1953_ = lp_competition_R19Base_FastMul_mul(v___y_1754_, v___y_1755_);
return v___x_1953_;
}
else
{
uint32_t v___x_1954_; uint32_t v___x_1955_; 
v___x_1954_ = 4194304;
v___x_1955_ = lean_uint32_lor(v___y_1755_, v___x_1954_);
return v___x_1955_;
}
}
v___jp_1956_:
{
uint32_t v___x_1957_; uint32_t v___x_1958_; uint32_t v___x_1959_; uint32_t v___x_1960_; uint8_t v___x_1961_; 
v___x_1957_ = 23;
v___x_1958_ = lean_uint32_shift_right(v___y_1755_, v___x_1957_);
v___x_1959_ = 255;
v___x_1960_ = lean_uint32_land(v___x_1958_, v___x_1959_);
v___x_1961_ = lean_uint32_dec_eq(v___x_1960_, v___x_1959_);
if (v___x_1961_ == 0)
{
v___y_1952_ = v___x_1961_;
goto v___jp_1951_;
}
else
{
uint32_t v___x_1962_; uint32_t v___x_1963_; uint32_t v___x_1964_; uint8_t v___x_1965_; 
v___x_1962_ = 8388607;
v___x_1963_ = lean_uint32_land(v___y_1755_, v___x_1962_);
v___x_1964_ = 0;
v___x_1965_ = lean_uint32_dec_eq(v___x_1963_, v___x_1964_);
if (v___x_1965_ == 0)
{
v___y_1952_ = v___x_1961_;
goto v___jp_1951_;
}
else
{
uint32_t v___x_1966_; 
v___x_1966_ = lp_competition_R19Base_FastMul_mul(v___y_1754_, v___y_1755_);
return v___x_1966_;
}
}
}
v___jp_1967_:
{
if (v___y_1968_ == 0)
{
goto v___jp_1956_;
}
else
{
uint32_t v___x_1969_; uint32_t v___x_1970_; 
v___x_1969_ = 4194304;
v___x_1970_ = lean_uint32_lor(v___y_1754_, v___x_1969_);
return v___x_1970_;
}
}
v___jp_1971_:
{
uint32_t v___x_1972_; uint32_t v___x_1973_; uint32_t v___x_1974_; uint32_t v___x_1975_; uint8_t v___x_1976_; 
v___x_1972_ = 23;
v___x_1973_ = lean_uint32_shift_right(v___y_1754_, v___x_1972_);
v___x_1974_ = 255;
v___x_1975_ = lean_uint32_land(v___x_1973_, v___x_1974_);
v___x_1976_ = lean_uint32_dec_eq(v___x_1975_, v___x_1974_);
if (v___x_1976_ == 0)
{
v___y_1968_ = v___x_1976_;
goto v___jp_1967_;
}
else
{
uint32_t v___x_1977_; uint32_t v___x_1978_; uint32_t v___x_1979_; uint8_t v___x_1980_; 
v___x_1977_ = 8388607;
v___x_1978_ = lean_uint32_land(v___y_1754_, v___x_1977_);
v___x_1979_ = 0;
v___x_1980_ = lean_uint32_dec_eq(v___x_1978_, v___x_1979_);
if (v___x_1980_ == 0)
{
v___y_1968_ = v___x_1976_;
goto v___jp_1967_;
}
else
{
goto v___jp_1956_;
}
}
}
v___jp_1981_:
{
if (v___y_1982_ == 0)
{
goto v___jp_1971_;
}
else
{
uint32_t v___x_1983_; uint32_t v___x_1984_; uint32_t v___x_1985_; uint8_t v___x_1986_; 
v___x_1983_ = 4194304;
v___x_1984_ = lean_uint32_land(v___y_1755_, v___x_1983_);
v___x_1985_ = 0;
v___x_1986_ = lean_uint32_dec_eq(v___x_1984_, v___x_1985_);
if (v___x_1986_ == 0)
{
goto v___jp_1971_;
}
else
{
uint32_t v___x_1987_; 
v___x_1987_ = lean_uint32_lor(v___y_1755_, v___x_1983_);
return v___x_1987_;
}
}
}
v___jp_1988_:
{
uint32_t v___x_1989_; uint32_t v___x_1990_; uint32_t v___x_1991_; uint32_t v___x_1992_; uint8_t v___x_1993_; 
v___x_1989_ = 23;
v___x_1990_ = lean_uint32_shift_right(v___y_1755_, v___x_1989_);
v___x_1991_ = 255;
v___x_1992_ = lean_uint32_land(v___x_1990_, v___x_1991_);
v___x_1993_ = lean_uint32_dec_eq(v___x_1992_, v___x_1991_);
if (v___x_1993_ == 0)
{
v___y_1982_ = v___x_1993_;
goto v___jp_1981_;
}
else
{
uint32_t v___x_1994_; uint32_t v___x_1995_; uint32_t v___x_1996_; uint8_t v___x_1997_; 
v___x_1994_ = 8388607;
v___x_1995_ = lean_uint32_land(v___y_1755_, v___x_1994_);
v___x_1996_ = 0;
v___x_1997_ = lean_uint32_dec_eq(v___x_1995_, v___x_1996_);
if (v___x_1997_ == 0)
{
v___y_1982_ = v___x_1993_;
goto v___jp_1981_;
}
else
{
goto v___jp_1971_;
}
}
}
v___jp_1998_:
{
if (v___y_1999_ == 0)
{
goto v___jp_1988_;
}
else
{
uint32_t v___x_2000_; uint32_t v___x_2001_; uint32_t v___x_2002_; uint8_t v___x_2003_; 
v___x_2000_ = 4194304;
v___x_2001_ = lean_uint32_land(v___y_1754_, v___x_2000_);
v___x_2002_ = 0;
v___x_2003_ = lean_uint32_dec_eq(v___x_2001_, v___x_2002_);
if (v___x_2003_ == 0)
{
goto v___jp_1988_;
}
else
{
uint32_t v___x_2004_; 
v___x_2004_ = lean_uint32_lor(v___y_1754_, v___x_2000_);
return v___x_2004_;
}
}
}
v___jp_2005_:
{
float v_result_2008_; uint8_t v___x_2009_; 
v_result_2008_ = lean_float32_mul(v___y_2006_, v___y_2007_);
v___x_2009_ = lean_float32_beq(v_result_2008_, v_result_2008_);
if (v___x_2009_ == 0)
{
uint32_t v___x_2010_; uint32_t v___x_2011_; uint32_t v___x_2012_; uint32_t v___x_2013_; uint8_t v___x_2014_; 
v___x_2010_ = 23;
v___x_2011_ = lean_uint32_shift_right(v___y_1754_, v___x_2010_);
v___x_2012_ = 255;
v___x_2013_ = lean_uint32_land(v___x_2011_, v___x_2012_);
v___x_2014_ = lean_uint32_dec_eq(v___x_2013_, v___x_2012_);
if (v___x_2014_ == 0)
{
v___y_1999_ = v___x_2014_;
goto v___jp_1998_;
}
else
{
uint32_t v___x_2015_; uint32_t v___x_2016_; uint32_t v___x_2017_; uint8_t v___x_2018_; 
v___x_2015_ = 8388607;
v___x_2016_ = lean_uint32_land(v___y_1754_, v___x_2015_);
v___x_2017_ = 0;
v___x_2018_ = lean_uint32_dec_eq(v___x_2016_, v___x_2017_);
if (v___x_2018_ == 0)
{
v___y_1999_ = v___x_2014_;
goto v___jp_1998_;
}
else
{
goto v___jp_1988_;
}
}
}
else
{
uint32_t v___x_2019_; 
v___x_2019_ = lean_float32_to_bits(v_result_2008_);
return v___x_2019_;
}
}
v___jp_2020_:
{
if (v___y_2022_ == 0)
{
float v___x_2023_; 
v___x_2023_ = lean_float32_of_bits(v___y_1755_);
v___y_2006_ = v___y_2021_;
v___y_2007_ = v___x_2023_;
goto v___jp_2005_;
}
else
{
uint32_t v___x_2024_; uint32_t v___x_2025_; uint32_t v___x_2026_; uint32_t v___x_2027_; float v___x_2028_; lean_object* v___x_2029_; uint32_t v___x_2030_; uint32_t v___x_2031_; lean_object* v___x_2032_; lean_object* v___x_2033_; float v___x_2034_; float v___x_2035_; 
v___x_2024_ = 8388607;
v___x_2025_ = lean_uint32_land(v___y_1755_, v___x_2024_);
v___x_2026_ = 8388608;
v___x_2027_ = lean_uint32_lor(v___x_2025_, v___x_2026_);
v___x_2028_ = lean_uint32_to_float32(v___x_2027_);
v___x_2029_ = lp_competition_R2W01b_scaleTable;
v___x_2030_ = 23;
v___x_2031_ = lean_uint32_shift_right(v___y_1755_, v___x_2030_);
v___x_2032_ = lean_uint32_to_nat(v___x_2031_);
v___x_2033_ = lean_array_fget_borrowed(v___x_2029_, v___x_2032_);
lean_dec(v___x_2032_);
v___x_2034_ = lean_unbox_float32(v___x_2033_);
v___x_2035_ = lean_float32_mul(v___x_2028_, v___x_2034_);
v___y_2006_ = v___y_2021_;
v___y_2007_ = v___x_2035_;
goto v___jp_2005_;
}
}
v___jp_2036_:
{
uint32_t v___x_2038_; uint32_t v_a_2039_; uint32_t v___x_2040_; uint32_t v___x_2041_; uint32_t v___x_2042_; uint8_t v___x_2043_; 
v___x_2038_ = 2147483647;
v_a_2039_ = lean_uint32_land(v___y_1755_, v___x_2038_);
v___x_2040_ = 201326591;
v___x_2041_ = 1;
v___x_2042_ = lean_uint32_sub(v_a_2039_, v___x_2041_);
v___x_2043_ = lean_uint32_dec_le(v___x_2040_, v___x_2042_);
if (v___x_2043_ == 0)
{
v___y_2021_ = v___y_2037_;
v___y_2022_ = v___x_2043_;
goto v___jp_2020_;
}
else
{
uint32_t v___x_2044_; uint8_t v___x_2045_; 
v___x_2044_ = 2139095040;
v___x_2045_ = lean_uint32_dec_lt(v_a_2039_, v___x_2044_);
v___y_2021_ = v___y_2037_;
v___y_2022_ = v___x_2045_;
goto v___jp_2020_;
}
}
v___jp_2046_:
{
uint32_t v___x_2048_; uint32_t v___x_2049_; 
v___x_2048_ = 8388608;
v___x_2049_ = lean_uint32_lor(v___y_2047_, v___x_2048_);
return v___x_2049_;
}
v___jp_2050_:
{
uint32_t v___x_2052_; uint32_t v___x_2053_; 
v___x_2052_ = 8388608;
v___x_2053_ = lean_uint32_lor(v___y_2051_, v___x_2052_);
return v___x_2053_;
}
v___jp_2054_:
{
uint32_t v___x_2058_; uint32_t v___x_2059_; 
v___x_2058_ = lean_uint32_land(v___y_2055_, v___y_2056_);
v___x_2059_ = lean_uint32_lor(v___y_2057_, v___x_2058_);
return v___x_2059_;
}
v___jp_2060_:
{
uint8_t v___x_2065_; 
v___x_2065_ = lean_uint64_dec_eq(v___y_2064_, v___y_2062_);
if (v___x_2065_ == 0)
{
uint64_t v___x_2066_; uint8_t v___x_2067_; 
v___x_2066_ = 8388608ULL;
v___x_2067_ = lean_uint64_dec_eq(v___y_2064_, v___x_2066_);
if (v___x_2067_ == 0)
{
uint32_t v___x_2068_; 
v___x_2068_ = lean_uint64_to_uint32(v___y_2064_);
if (v___y_2063_ == 0)
{
uint32_t v___x_2069_; 
v___x_2069_ = 0;
v___y_2055_ = v___x_2068_;
v___y_2056_ = v___y_2061_;
v___y_2057_ = v___x_2069_;
goto v___jp_2054_;
}
else
{
uint32_t v___x_2070_; 
v___x_2070_ = 2147483648;
v___y_2055_ = v___x_2068_;
v___y_2056_ = v___y_2061_;
v___y_2057_ = v___x_2070_;
goto v___jp_2054_;
}
}
else
{
if (v___y_2063_ == 0)
{
uint32_t v___x_2071_; 
v___x_2071_ = 0;
v___y_2051_ = v___x_2071_;
goto v___jp_2050_;
}
else
{
uint32_t v___x_2072_; 
v___x_2072_ = 2147483648;
v___y_2051_ = v___x_2072_;
goto v___jp_2050_;
}
}
}
else
{
if (v___y_2063_ == 0)
{
uint32_t v___x_2073_; 
v___x_2073_ = 0;
return v___x_2073_;
}
else
{
uint32_t v___x_2074_; 
v___x_2074_ = 2147483648;
return v___x_2074_;
}
}
}
v___jp_2075_:
{
uint32_t v___x_2079_; uint32_t v___x_2080_; 
v___x_2079_ = lean_uint32_land(v___y_2076_, v___y_2077_);
v___x_2080_ = lean_uint32_lor(v___y_2078_, v___x_2079_);
return v___x_2080_;
}
v___jp_2081_:
{
uint8_t v___x_2086_; 
v___x_2086_ = lean_uint64_dec_eq(v___y_2085_, v___y_2084_);
if (v___x_2086_ == 0)
{
uint64_t v___x_2087_; uint8_t v___x_2088_; 
v___x_2087_ = 8388608ULL;
v___x_2088_ = lean_uint64_dec_eq(v___y_2085_, v___x_2087_);
if (v___x_2088_ == 0)
{
uint32_t v___x_2089_; 
v___x_2089_ = lean_uint64_to_uint32(v___y_2085_);
if (v___y_2083_ == 0)
{
uint32_t v___x_2090_; 
v___x_2090_ = 0;
v___y_2076_ = v___x_2089_;
v___y_2077_ = v___y_2082_;
v___y_2078_ = v___x_2090_;
goto v___jp_2075_;
}
else
{
uint32_t v___x_2091_; 
v___x_2091_ = 2147483648;
v___y_2076_ = v___x_2089_;
v___y_2077_ = v___y_2082_;
v___y_2078_ = v___x_2091_;
goto v___jp_2075_;
}
}
else
{
if (v___y_2083_ == 0)
{
uint32_t v___x_2092_; 
v___x_2092_ = 0;
v___y_2047_ = v___x_2092_;
goto v___jp_2046_;
}
else
{
uint32_t v___x_2093_; 
v___x_2093_ = 2147483648;
v___y_2047_ = v___x_2093_;
goto v___jp_2046_;
}
}
}
else
{
if (v___y_2083_ == 0)
{
uint32_t v___x_2094_; 
v___x_2094_ = 0;
return v___x_2094_;
}
else
{
uint32_t v___x_2095_; 
v___x_2095_ = 2147483648;
return v___x_2095_;
}
}
}
v___jp_2096_:
{
if (v___y_2097_ == 0)
{
uint32_t v___x_2098_; 
v___x_2098_ = lp_competition_R19Base_FastMul_mul(v___y_1754_, v___y_1755_);
return v___x_2098_;
}
else
{
uint32_t v___x_2099_; uint32_t v___x_2100_; 
v___x_2099_ = 4194304;
v___x_2100_ = lean_uint32_lor(v___y_1755_, v___x_2099_);
return v___x_2100_;
}
}
v___jp_2101_:
{
uint32_t v___x_2102_; uint32_t v___x_2103_; uint32_t v___x_2104_; uint32_t v___x_2105_; uint8_t v___x_2106_; 
v___x_2102_ = 23;
v___x_2103_ = lean_uint32_shift_right(v___y_1755_, v___x_2102_);
v___x_2104_ = 255;
v___x_2105_ = lean_uint32_land(v___x_2103_, v___x_2104_);
v___x_2106_ = lean_uint32_dec_eq(v___x_2105_, v___x_2104_);
if (v___x_2106_ == 0)
{
v___y_2097_ = v___x_2106_;
goto v___jp_2096_;
}
else
{
uint32_t v___x_2107_; uint32_t v___x_2108_; uint32_t v___x_2109_; uint8_t v___x_2110_; 
v___x_2107_ = 8388607;
v___x_2108_ = lean_uint32_land(v___y_1755_, v___x_2107_);
v___x_2109_ = 0;
v___x_2110_ = lean_uint32_dec_eq(v___x_2108_, v___x_2109_);
if (v___x_2110_ == 0)
{
v___y_2097_ = v___x_2106_;
goto v___jp_2096_;
}
else
{
uint32_t v___x_2111_; 
v___x_2111_ = lp_competition_R19Base_FastMul_mul(v___y_1754_, v___y_1755_);
return v___x_2111_;
}
}
}
v___jp_2112_:
{
if (v___y_2113_ == 0)
{
goto v___jp_2101_;
}
else
{
uint32_t v___x_2114_; uint32_t v___x_2115_; 
v___x_2114_ = 4194304;
v___x_2115_ = lean_uint32_lor(v___y_1754_, v___x_2114_);
return v___x_2115_;
}
}
v___jp_2116_:
{
uint32_t v___x_2117_; uint32_t v___x_2118_; uint32_t v___x_2119_; uint32_t v___x_2120_; uint8_t v___x_2121_; 
v___x_2117_ = 23;
v___x_2118_ = lean_uint32_shift_right(v___y_1754_, v___x_2117_);
v___x_2119_ = 255;
v___x_2120_ = lean_uint32_land(v___x_2118_, v___x_2119_);
v___x_2121_ = lean_uint32_dec_eq(v___x_2120_, v___x_2119_);
if (v___x_2121_ == 0)
{
v___y_2113_ = v___x_2121_;
goto v___jp_2112_;
}
else
{
uint32_t v___x_2122_; uint32_t v___x_2123_; uint32_t v___x_2124_; uint8_t v___x_2125_; 
v___x_2122_ = 8388607;
v___x_2123_ = lean_uint32_land(v___y_1754_, v___x_2122_);
v___x_2124_ = 0;
v___x_2125_ = lean_uint32_dec_eq(v___x_2123_, v___x_2124_);
if (v___x_2125_ == 0)
{
v___y_2113_ = v___x_2121_;
goto v___jp_2112_;
}
else
{
goto v___jp_2101_;
}
}
}
v___jp_2126_:
{
if (v___y_2127_ == 0)
{
goto v___jp_2116_;
}
else
{
uint32_t v___x_2128_; uint32_t v___x_2129_; uint32_t v___x_2130_; uint8_t v___x_2131_; 
v___x_2128_ = 4194304;
v___x_2129_ = lean_uint32_land(v___y_1755_, v___x_2128_);
v___x_2130_ = 0;
v___x_2131_ = lean_uint32_dec_eq(v___x_2129_, v___x_2130_);
if (v___x_2131_ == 0)
{
goto v___jp_2116_;
}
else
{
uint32_t v___x_2132_; 
v___x_2132_ = lean_uint32_lor(v___y_1755_, v___x_2128_);
return v___x_2132_;
}
}
}
v___jp_2133_:
{
uint32_t v___x_2134_; uint32_t v___x_2135_; uint32_t v___x_2136_; uint32_t v___x_2137_; uint8_t v___x_2138_; 
v___x_2134_ = 23;
v___x_2135_ = lean_uint32_shift_right(v___y_1755_, v___x_2134_);
v___x_2136_ = 255;
v___x_2137_ = lean_uint32_land(v___x_2135_, v___x_2136_);
v___x_2138_ = lean_uint32_dec_eq(v___x_2137_, v___x_2136_);
if (v___x_2138_ == 0)
{
v___y_2127_ = v___x_2138_;
goto v___jp_2126_;
}
else
{
uint32_t v___x_2139_; uint32_t v___x_2140_; uint32_t v___x_2141_; uint8_t v___x_2142_; 
v___x_2139_ = 8388607;
v___x_2140_ = lean_uint32_land(v___y_1755_, v___x_2139_);
v___x_2141_ = 0;
v___x_2142_ = lean_uint32_dec_eq(v___x_2140_, v___x_2141_);
if (v___x_2142_ == 0)
{
v___y_2127_ = v___x_2138_;
goto v___jp_2126_;
}
else
{
goto v___jp_2116_;
}
}
}
v___jp_2143_:
{
if (v___y_2144_ == 0)
{
goto v___jp_2133_;
}
else
{
uint32_t v___x_2145_; uint32_t v___x_2146_; uint32_t v___x_2147_; uint8_t v___x_2148_; 
v___x_2145_ = 4194304;
v___x_2146_ = lean_uint32_land(v___y_1754_, v___x_2145_);
v___x_2147_ = 0;
v___x_2148_ = lean_uint32_dec_eq(v___x_2146_, v___x_2147_);
if (v___x_2148_ == 0)
{
goto v___jp_2133_;
}
else
{
uint32_t v___x_2149_; 
v___x_2149_ = lean_uint32_lor(v___y_1754_, v___x_2145_);
return v___x_2149_;
}
}
}
v___jp_2150_:
{
float v_result_2153_; uint8_t v___x_2154_; 
v_result_2153_ = lean_float32_mul(v___y_2151_, v___y_2152_);
v___x_2154_ = lean_float32_beq(v_result_2153_, v_result_2153_);
if (v___x_2154_ == 0)
{
uint32_t v___x_2155_; uint32_t v___x_2156_; uint32_t v___x_2157_; uint32_t v___x_2158_; uint8_t v___x_2159_; 
v___x_2155_ = 23;
v___x_2156_ = lean_uint32_shift_right(v___y_1754_, v___x_2155_);
v___x_2157_ = 255;
v___x_2158_ = lean_uint32_land(v___x_2156_, v___x_2157_);
v___x_2159_ = lean_uint32_dec_eq(v___x_2158_, v___x_2157_);
if (v___x_2159_ == 0)
{
v___y_2144_ = v___x_2159_;
goto v___jp_2143_;
}
else
{
uint32_t v___x_2160_; uint32_t v___x_2161_; uint32_t v___x_2162_; uint8_t v___x_2163_; 
v___x_2160_ = 8388607;
v___x_2161_ = lean_uint32_land(v___y_1754_, v___x_2160_);
v___x_2162_ = 0;
v___x_2163_ = lean_uint32_dec_eq(v___x_2161_, v___x_2162_);
if (v___x_2163_ == 0)
{
v___y_2144_ = v___x_2159_;
goto v___jp_2143_;
}
else
{
goto v___jp_2133_;
}
}
}
else
{
uint32_t v___x_2164_; 
v___x_2164_ = lean_float32_to_bits(v_result_2153_);
return v___x_2164_;
}
}
v___jp_2165_:
{
if (v___y_2167_ == 0)
{
float v___x_2168_; 
v___x_2168_ = lean_float32_of_bits(v___y_1755_);
v___y_2151_ = v___y_2166_;
v___y_2152_ = v___x_2168_;
goto v___jp_2150_;
}
else
{
uint32_t v___x_2169_; uint32_t v___x_2170_; uint32_t v___x_2171_; uint32_t v___x_2172_; float v___x_2173_; lean_object* v___x_2174_; uint32_t v___x_2175_; uint32_t v___x_2176_; lean_object* v___x_2177_; lean_object* v___x_2178_; float v___x_2179_; float v___x_2180_; 
v___x_2169_ = 8388607;
v___x_2170_ = lean_uint32_land(v___y_1755_, v___x_2169_);
v___x_2171_ = 8388608;
v___x_2172_ = lean_uint32_lor(v___x_2170_, v___x_2171_);
v___x_2173_ = lean_uint32_to_float32(v___x_2172_);
v___x_2174_ = lp_competition_R2W01b_scaleTable;
v___x_2175_ = 23;
v___x_2176_ = lean_uint32_shift_right(v___y_1755_, v___x_2175_);
v___x_2177_ = lean_uint32_to_nat(v___x_2176_);
v___x_2178_ = lean_array_fget_borrowed(v___x_2174_, v___x_2177_);
lean_dec(v___x_2177_);
v___x_2179_ = lean_unbox_float32(v___x_2178_);
v___x_2180_ = lean_float32_mul(v___x_2173_, v___x_2179_);
v___y_2151_ = v___y_2166_;
v___y_2152_ = v___x_2180_;
goto v___jp_2150_;
}
}
v___jp_2181_:
{
uint32_t v___x_2183_; uint32_t v_a_2184_; uint32_t v___x_2185_; uint32_t v___x_2186_; uint32_t v___x_2187_; uint8_t v___x_2188_; 
v___x_2183_ = 2147483647;
v_a_2184_ = lean_uint32_land(v___y_1755_, v___x_2183_);
v___x_2185_ = 201326591;
v___x_2186_ = 1;
v___x_2187_ = lean_uint32_sub(v_a_2184_, v___x_2186_);
v___x_2188_ = lean_uint32_dec_le(v___x_2185_, v___x_2187_);
if (v___x_2188_ == 0)
{
v___y_2166_ = v___y_2182_;
v___y_2167_ = v___x_2188_;
goto v___jp_2165_;
}
else
{
uint32_t v___x_2189_; uint8_t v___x_2190_; 
v___x_2189_ = 2139095040;
v___x_2190_ = lean_uint32_dec_lt(v_a_2184_, v___x_2189_);
v___y_2166_ = v___y_2182_;
v___y_2167_ = v___x_2190_;
goto v___jp_2165_;
}
}
v___jp_2193_:
{
if (v___y_2194_ == 0)
{
float v___x_2195_; 
v___x_2195_ = lean_float32_of_bits(v___y_1754_);
v___y_1892_ = v___x_2195_;
goto v___jp_1891_;
}
else
{
uint32_t v___x_2196_; uint32_t v___x_2197_; uint32_t v___x_2198_; uint32_t v___x_2199_; float v___x_2200_; lean_object* v___x_2201_; lean_object* v___x_2202_; lean_object* v___x_2203_; float v___x_2204_; float v___x_2205_; 
v___x_2196_ = 8388607;
v___x_2197_ = lean_uint32_land(v___y_1754_, v___x_2196_);
v___x_2198_ = 8388608;
v___x_2199_ = lean_uint32_lor(v___x_2197_, v___x_2198_);
v___x_2200_ = lean_uint32_to_float32(v___x_2199_);
v___x_2201_ = lp_competition_R2W01b_scaleTable;
v___x_2202_ = lean_uint32_to_nat(v___x_2192_);
v___x_2203_ = lean_array_fget_borrowed(v___x_2201_, v___x_2202_);
lean_dec(v___x_2202_);
v___x_2204_ = lean_unbox_float32(v___x_2203_);
v___x_2205_ = lean_float32_mul(v___x_2200_, v___x_2204_);
v___y_1892_ = v___x_2205_;
goto v___jp_1891_;
}
}
v___jp_2206_:
{
if (v___y_2207_ == 0)
{
float v___x_2208_; 
v___x_2208_ = lean_float32_of_bits(v___y_1754_);
v___y_2037_ = v___x_2208_;
goto v___jp_2036_;
}
else
{
uint32_t v___x_2209_; uint32_t v___x_2210_; uint32_t v___x_2211_; uint32_t v___x_2212_; float v___x_2213_; lean_object* v___x_2214_; lean_object* v___x_2215_; lean_object* v___x_2216_; float v___x_2217_; float v___x_2218_; 
v___x_2209_ = 8388607;
v___x_2210_ = lean_uint32_land(v___y_1754_, v___x_2209_);
v___x_2211_ = 8388608;
v___x_2212_ = lean_uint32_lor(v___x_2210_, v___x_2211_);
v___x_2213_ = lean_uint32_to_float32(v___x_2212_);
v___x_2214_ = lp_competition_R2W01b_scaleTable;
v___x_2215_ = lean_uint32_to_nat(v___x_2192_);
v___x_2216_ = lean_array_fget_borrowed(v___x_2214_, v___x_2215_);
lean_dec(v___x_2215_);
v___x_2217_ = lean_unbox_float32(v___x_2216_);
v___x_2218_ = lean_float32_mul(v___x_2213_, v___x_2217_);
v___y_2037_ = v___x_2218_;
goto v___jp_2036_;
}
}
v___jp_2219_:
{
if (v___y_2220_ == 0)
{
float v___x_2221_; 
v___x_2221_ = lean_float32_of_bits(v___y_1754_);
v___y_2182_ = v___x_2221_;
goto v___jp_2181_;
}
else
{
uint32_t v___x_2222_; uint32_t v___x_2223_; uint32_t v___x_2224_; uint32_t v___x_2225_; float v___x_2226_; lean_object* v___x_2227_; lean_object* v___x_2228_; lean_object* v___x_2229_; float v___x_2230_; float v___x_2231_; 
v___x_2222_ = 8388607;
v___x_2223_ = lean_uint32_land(v___y_1754_, v___x_2222_);
v___x_2224_ = 8388608;
v___x_2225_ = lean_uint32_lor(v___x_2223_, v___x_2224_);
v___x_2226_ = lean_uint32_to_float32(v___x_2225_);
v___x_2227_ = lp_competition_R2W01b_scaleTable;
v___x_2228_ = lean_uint32_to_nat(v___x_2192_);
v___x_2229_ = lean_array_fget_borrowed(v___x_2227_, v___x_2228_);
lean_dec(v___x_2228_);
v___x_2230_ = lean_unbox_float32(v___x_2229_);
v___x_2231_ = lean_float32_mul(v___x_2226_, v___x_2230_);
v___y_2182_ = v___x_2231_;
goto v___jp_2181_;
}
}
v___jp_2233_:
{
uint32_t v___x_2238_; uint32_t v___x_2239_; uint32_t v___x_2240_; uint32_t v___x_2241_; uint32_t v___x_2242_; 
v___x_2238_ = lean_uint32_land(v___y_2235_, v___x_2232_);
v___x_2239_ = lean_uint32_shift_left(v___x_2238_, v___x_2191_);
v___x_2240_ = lean_uint32_lor(v___y_2237_, v___x_2239_);
v___x_2241_ = lean_uint32_land(v___y_2236_, v___y_2234_);
v___x_2242_ = lean_uint32_lor(v___x_2240_, v___x_2241_);
return v___x_2242_;
}
v___jp_2243_:
{
if (v___y_2244_ == 0)
{
uint32_t v___x_2248_; 
v___x_2248_ = 0;
v___y_2234_ = v___y_2245_;
v___y_2235_ = v___y_2246_;
v___y_2236_ = v___y_2247_;
v___y_2237_ = v___x_2248_;
goto v___jp_2233_;
}
else
{
uint32_t v___x_2249_; 
v___x_2249_ = 2147483648;
v___y_2234_ = v___y_2245_;
v___y_2235_ = v___y_2246_;
v___y_2236_ = v___y_2247_;
v___y_2237_ = v___x_2249_;
goto v___jp_2233_;
}
}
v___jp_2250_:
{
uint64_t v___x_2256_; uint64_t v_encodedExponent_2257_; uint32_t v___x_2258_; uint64_t v___x_2259_; uint8_t v___x_2260_; 
v___x_2256_ = 171ULL;
v_encodedExponent_2257_ = lean_uint64_sub(v___y_2252_, v___x_2256_);
v___x_2258_ = lean_uint64_to_uint32(v_encodedExponent_2257_);
v___x_2259_ = 8388608ULL;
v___x_2260_ = lean_uint64_dec_lt(v___y_2255_, v___x_2259_);
if (v___x_2260_ == 0)
{
uint64_t v___x_2261_; uint32_t v___x_2262_; 
v___x_2261_ = lean_uint64_sub(v___y_2255_, v___x_2259_);
v___x_2262_ = lean_uint64_to_uint32(v___x_2261_);
v___y_2244_ = v___y_2251_;
v___y_2245_ = v___y_2253_;
v___y_2246_ = v___x_2258_;
v___y_2247_ = v___x_2262_;
goto v___jp_2243_;
}
else
{
uint32_t v___x_2263_; 
v___x_2263_ = lean_uint64_to_uint32(v___y_2254_);
v___y_2244_ = v___y_2251_;
v___y_2245_ = v___y_2253_;
v___y_2246_ = v___x_2258_;
v___y_2247_ = v___x_2263_;
goto v___jp_2243_;
}
}
v___jp_2264_:
{
uint64_t v___x_2271_; uint8_t v___x_2272_; 
v___x_2271_ = 425ULL;
v___x_2272_ = lean_uint64_dec_lt(v___x_2271_, v___y_2270_);
if (v___x_2272_ == 0)
{
if (v___y_2266_ == 0)
{
v___y_2251_ = v___y_2265_;
v___y_2252_ = v___y_2270_;
v___y_2253_ = v___y_2267_;
v___y_2254_ = v___y_2268_;
v___y_2255_ = v___y_2269_;
goto v___jp_2250_;
}
else
{
uint64_t v___x_2273_; 
v___x_2273_ = 8388608ULL;
v___y_2251_ = v___y_2265_;
v___y_2252_ = v___y_2270_;
v___y_2253_ = v___y_2267_;
v___y_2254_ = v___y_2268_;
v___y_2255_ = v___x_2273_;
goto v___jp_2250_;
}
}
else
{
if (v___y_2265_ == 0)
{
uint32_t v___x_2274_; 
v___x_2274_ = 2139095040;
return v___x_2274_;
}
else
{
uint32_t v___x_2275_; 
v___x_2275_ = 4286578688;
return v___x_2275_;
}
}
}
v___jp_2276_:
{
uint64_t v___x_2282_; uint8_t v_carry_2283_; 
v___x_2282_ = 16777216ULL;
v_carry_2283_ = lean_uint64_dec_eq(v___y_2281_, v___x_2282_);
if (v_carry_2283_ == 0)
{
v___y_2265_ = v___y_2277_;
v___y_2266_ = v_carry_2283_;
v___y_2267_ = v___y_2278_;
v___y_2268_ = v___y_2279_;
v___y_2269_ = v___y_2281_;
v___y_2270_ = v___y_2280_;
goto v___jp_2264_;
}
else
{
uint64_t v___x_2284_; uint64_t v___x_2285_; 
v___x_2284_ = 1ULL;
v___x_2285_ = lean_uint64_add(v___y_2280_, v___x_2284_);
v___y_2265_ = v___y_2277_;
v___y_2266_ = v_carry_2283_;
v___y_2267_ = v___y_2278_;
v___y_2268_ = v___y_2279_;
v___y_2269_ = v___y_2281_;
v___y_2270_ = v___x_2285_;
goto v___jp_2264_;
}
}
v___jp_2286_:
{
uint64_t v_position_2293_; uint64_t v___x_2294_; uint8_t v___x_2295_; 
v_position_2293_ = lean_uint64_add(v___y_2292_, v___y_2291_);
v___x_2294_ = 172ULL;
v___x_2295_ = lean_uint64_dec_lt(v_position_2293_, v___x_2294_);
if (v___x_2295_ == 0)
{
uint64_t v___x_2296_; uint8_t v___x_2297_; 
v___x_2296_ = 23ULL;
v___x_2297_ = lean_uint64_dec_lt(v___y_2292_, v___x_2296_);
if (v___x_2297_ == 0)
{
uint64_t v___x_2298_; uint8_t v___x_2299_; 
v___x_2298_ = lean_uint64_sub(v___y_2292_, v___x_2296_);
v___x_2299_ = lean_uint64_dec_eq(v___x_2298_, v___y_2290_);
if (v___x_2299_ == 0)
{
uint64_t v___x_2300_; uint8_t v___x_2301_; 
v___x_2300_ = 64ULL;
v___x_2301_ = lean_uint64_dec_lt(v___x_2298_, v___x_2300_);
if (v___x_2301_ == 0)
{
uint8_t v___x_2302_; 
v___x_2302_ = lean_uint64_dec_eq(v___x_2298_, v___x_2300_);
if (v___x_2302_ == 0)
{
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v___y_2290_;
goto v___jp_2276_;
}
else
{
uint64_t v___x_2303_; uint8_t v___x_2304_; 
v___x_2303_ = 9223372036854775808ULL;
v___x_2304_ = lean_uint64_dec_lt(v___x_2303_, v___y_2289_);
if (v___x_2304_ == 0)
{
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v___y_2290_;
goto v___jp_2276_;
}
else
{
uint64_t v___x_2305_; 
v___x_2305_ = 1ULL;
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v___x_2305_;
goto v___jp_2276_;
}
}
}
else
{
uint64_t v_quotient_2306_; uint64_t v___x_2307_; uint64_t v___x_2308_; uint64_t v___x_2309_; uint64_t v_remainder_2310_; uint64_t v___x_2311_; uint64_t v_half_2312_; uint8_t v___x_2313_; 
v_quotient_2306_ = lean_uint64_shift_right(v___y_2289_, v___x_2298_);
v___x_2307_ = 1ULL;
v___x_2308_ = lean_uint64_shift_left(v___x_2307_, v___x_2298_);
v___x_2309_ = lean_uint64_sub(v___x_2308_, v___x_2307_);
v_remainder_2310_ = lean_uint64_land(v___y_2289_, v___x_2309_);
v___x_2311_ = lean_uint64_sub(v___x_2298_, v___x_2307_);
v_half_2312_ = lean_uint64_shift_left(v___x_2307_, v___x_2311_);
v___x_2313_ = lean_uint64_dec_lt(v_remainder_2310_, v_half_2312_);
if (v___x_2313_ == 0)
{
uint8_t v___x_2314_; 
v___x_2314_ = lean_uint64_dec_lt(v_half_2312_, v_remainder_2310_);
if (v___x_2314_ == 0)
{
uint64_t v___x_2315_; uint8_t v___x_2316_; 
v___x_2315_ = lean_uint64_land(v_quotient_2306_, v___x_2307_);
v___x_2316_ = lean_uint64_dec_eq(v___x_2315_, v___y_2290_);
if (v___x_2316_ == 0)
{
uint64_t v___x_2317_; 
v___x_2317_ = lean_uint64_add(v_quotient_2306_, v___x_2307_);
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v___x_2317_;
goto v___jp_2276_;
}
else
{
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v_quotient_2306_;
goto v___jp_2276_;
}
}
else
{
uint64_t v___x_2318_; 
v___x_2318_ = lean_uint64_add(v_quotient_2306_, v___x_2307_);
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v___x_2318_;
goto v___jp_2276_;
}
}
else
{
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v_quotient_2306_;
goto v___jp_2276_;
}
}
}
else
{
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v___y_2289_;
goto v___jp_2276_;
}
}
else
{
uint64_t v___x_2319_; uint64_t v___x_2320_; 
v___x_2319_ = lean_uint64_sub(v___x_2296_, v___y_2292_);
v___x_2320_ = lean_uint64_shift_left(v___y_2289_, v___x_2319_);
v___y_2277_ = v___y_2287_;
v___y_2278_ = v___y_2288_;
v___y_2279_ = v___y_2290_;
v___y_2280_ = v_position_2293_;
v___y_2281_ = v___x_2320_;
goto v___jp_2276_;
}
}
else
{
uint64_t v___x_2321_; uint8_t v___x_2322_; 
v___x_2321_ = 149ULL;
v___x_2322_ = lean_uint64_dec_lt(v___y_2291_, v___x_2321_);
if (v___x_2322_ == 0)
{
uint64_t v___x_2323_; uint64_t v___x_2324_; 
v___x_2323_ = lean_uint64_sub(v___y_2291_, v___x_2321_);
v___x_2324_ = lean_uint64_shift_left(v___y_2289_, v___x_2323_);
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v___x_2324_;
goto v___jp_1770_;
}
else
{
uint64_t v___x_2325_; uint8_t v___x_2326_; 
v___x_2325_ = lean_uint64_sub(v___x_2321_, v___y_2291_);
v___x_2326_ = lean_uint64_dec_eq(v___x_2325_, v___y_2290_);
if (v___x_2326_ == 0)
{
uint64_t v___x_2327_; uint8_t v___x_2328_; 
v___x_2327_ = 64ULL;
v___x_2328_ = lean_uint64_dec_lt(v___x_2325_, v___x_2327_);
if (v___x_2328_ == 0)
{
uint8_t v___x_2329_; 
v___x_2329_ = lean_uint64_dec_eq(v___x_2325_, v___x_2327_);
if (v___x_2329_ == 0)
{
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v___y_2290_;
goto v___jp_1770_;
}
else
{
uint64_t v___x_2330_; uint8_t v___x_2331_; 
v___x_2330_ = 9223372036854775808ULL;
v___x_2331_ = lean_uint64_dec_lt(v___x_2330_, v___y_2289_);
if (v___x_2331_ == 0)
{
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v___y_2290_;
goto v___jp_1770_;
}
else
{
uint64_t v___x_2332_; 
v___x_2332_ = 1ULL;
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v___x_2332_;
goto v___jp_1770_;
}
}
}
else
{
uint64_t v_quotient_2333_; uint64_t v___x_2334_; uint64_t v___x_2335_; uint64_t v___x_2336_; uint64_t v_remainder_2337_; uint64_t v___x_2338_; uint64_t v_half_2339_; uint8_t v___x_2340_; 
v_quotient_2333_ = lean_uint64_shift_right(v___y_2289_, v___x_2325_);
v___x_2334_ = 1ULL;
v___x_2335_ = lean_uint64_shift_left(v___x_2334_, v___x_2325_);
v___x_2336_ = lean_uint64_sub(v___x_2335_, v___x_2334_);
v_remainder_2337_ = lean_uint64_land(v___y_2289_, v___x_2336_);
v___x_2338_ = lean_uint64_sub(v___x_2325_, v___x_2334_);
v_half_2339_ = lean_uint64_shift_left(v___x_2334_, v___x_2338_);
v___x_2340_ = lean_uint64_dec_lt(v_remainder_2337_, v_half_2339_);
if (v___x_2340_ == 0)
{
uint8_t v___x_2341_; 
v___x_2341_ = lean_uint64_dec_lt(v_half_2339_, v_remainder_2337_);
if (v___x_2341_ == 0)
{
uint64_t v___x_2342_; uint8_t v___x_2343_; 
v___x_2342_ = lean_uint64_land(v_quotient_2333_, v___x_2334_);
v___x_2343_ = lean_uint64_dec_eq(v___x_2342_, v___y_2290_);
if (v___x_2343_ == 0)
{
uint64_t v___x_2344_; 
v___x_2344_ = lean_uint64_add(v_quotient_2333_, v___x_2334_);
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v___x_2344_;
goto v___jp_1770_;
}
else
{
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v_quotient_2333_;
goto v___jp_1770_;
}
}
else
{
uint64_t v___x_2345_; 
v___x_2345_ = lean_uint64_add(v_quotient_2333_, v___x_2334_);
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v___x_2345_;
goto v___jp_1770_;
}
}
else
{
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v_quotient_2333_;
goto v___jp_1770_;
}
}
}
else
{
v___y_1771_ = v___y_2287_;
v___y_1772_ = v___y_2288_;
v___y_1773_ = v___y_2290_;
v___y_1774_ = v___y_2289_;
goto v___jp_1770_;
}
}
}
}
v___jp_2346_:
{
uint64_t v___x_2354_; uint64_t v___x_2355_; uint8_t v___x_2356_; 
v___x_2354_ = 1ULL;
v___x_2355_ = lean_uint64_shift_right(v___y_2348_, v___x_2354_);
v___x_2356_ = lean_uint64_dec_eq(v___x_2355_, v___y_2351_);
if (v___x_2356_ == 0)
{
uint64_t v___x_2357_; 
v___x_2357_ = lean_uint64_add(v___y_2353_, v___x_2354_);
v___y_2287_ = v___y_2347_;
v___y_2288_ = v___y_2349_;
v___y_2289_ = v___y_2350_;
v___y_2290_ = v___y_2351_;
v___y_2291_ = v___y_2352_;
v___y_2292_ = v___x_2357_;
goto v___jp_2286_;
}
else
{
v___y_2287_ = v___y_2347_;
v___y_2288_ = v___y_2349_;
v___y_2289_ = v___y_2350_;
v___y_2290_ = v___y_2351_;
v___y_2291_ = v___y_2352_;
v___y_2292_ = v___y_2353_;
goto v___jp_2286_;
}
}
v___jp_2358_:
{
uint64_t v___x_2368_; uint8_t v___x_2369_; 
v___x_2368_ = lean_uint64_shift_right(v___y_2365_, v___y_2359_);
v___x_2369_ = lean_uint64_dec_eq(v___x_2368_, v___y_2364_);
if (v___x_2369_ == 0)
{
uint64_t v___x_2370_; 
v___x_2370_ = lean_uint64_add(v___y_2363_, v___y_2359_);
v___y_2347_ = v___y_2360_;
v___y_2348_ = v___y_2367_;
v___y_2349_ = v___y_2361_;
v___y_2350_ = v___y_2362_;
v___y_2351_ = v___y_2364_;
v___y_2352_ = v___y_2366_;
v___y_2353_ = v___x_2370_;
goto v___jp_2346_;
}
else
{
v___y_2347_ = v___y_2360_;
v___y_2348_ = v___y_2367_;
v___y_2349_ = v___y_2361_;
v___y_2350_ = v___y_2362_;
v___y_2351_ = v___y_2364_;
v___y_2352_ = v___y_2366_;
v___y_2353_ = v___y_2363_;
goto v___jp_2346_;
}
}
v___jp_2371_:
{
uint64_t v___x_2379_; uint64_t v___x_2380_; uint8_t v___x_2381_; 
v___x_2379_ = 2ULL;
v___x_2380_ = lean_uint64_shift_right(v___y_2376_, v___x_2379_);
v___x_2381_ = lean_uint64_dec_eq(v___x_2380_, v___y_2375_);
if (v___x_2381_ == 0)
{
v___y_2359_ = v___x_2379_;
v___y_2360_ = v___y_2372_;
v___y_2361_ = v___y_2373_;
v___y_2362_ = v___y_2374_;
v___y_2363_ = v___y_2378_;
v___y_2364_ = v___y_2375_;
v___y_2365_ = v___y_2376_;
v___y_2366_ = v___y_2377_;
v___y_2367_ = v___x_2380_;
goto v___jp_2358_;
}
else
{
v___y_2359_ = v___x_2379_;
v___y_2360_ = v___y_2372_;
v___y_2361_ = v___y_2373_;
v___y_2362_ = v___y_2374_;
v___y_2363_ = v___y_2378_;
v___y_2364_ = v___y_2375_;
v___y_2365_ = v___y_2376_;
v___y_2366_ = v___y_2377_;
v___y_2367_ = v___y_2376_;
goto v___jp_2358_;
}
}
v___jp_2382_:
{
uint64_t v___x_2392_; uint8_t v___x_2393_; 
v___x_2392_ = lean_uint64_shift_right(v___y_2387_, v___y_2389_);
v___x_2393_ = lean_uint64_dec_eq(v___x_2392_, v___y_2388_);
if (v___x_2393_ == 0)
{
uint64_t v___x_2394_; 
v___x_2394_ = lean_uint64_add(v___y_2384_, v___y_2389_);
v___y_2372_ = v___y_2383_;
v___y_2373_ = v___y_2385_;
v___y_2374_ = v___y_2386_;
v___y_2375_ = v___y_2388_;
v___y_2376_ = v___y_2391_;
v___y_2377_ = v___y_2390_;
v___y_2378_ = v___x_2394_;
goto v___jp_2371_;
}
else
{
v___y_2372_ = v___y_2383_;
v___y_2373_ = v___y_2385_;
v___y_2374_ = v___y_2386_;
v___y_2375_ = v___y_2388_;
v___y_2376_ = v___y_2391_;
v___y_2377_ = v___y_2390_;
v___y_2378_ = v___y_2384_;
goto v___jp_2371_;
}
}
v___jp_2395_:
{
uint64_t v___x_2403_; uint64_t v___x_2404_; uint8_t v___x_2405_; 
v___x_2403_ = 4ULL;
v___x_2404_ = lean_uint64_shift_right(v___y_2399_, v___x_2403_);
v___x_2405_ = lean_uint64_dec_eq(v___x_2404_, v___y_2400_);
if (v___x_2405_ == 0)
{
v___y_2383_ = v___y_2396_;
v___y_2384_ = v___y_2402_;
v___y_2385_ = v___y_2397_;
v___y_2386_ = v___y_2398_;
v___y_2387_ = v___y_2399_;
v___y_2388_ = v___y_2400_;
v___y_2389_ = v___x_2403_;
v___y_2390_ = v___y_2401_;
v___y_2391_ = v___x_2404_;
goto v___jp_2382_;
}
else
{
v___y_2383_ = v___y_2396_;
v___y_2384_ = v___y_2402_;
v___y_2385_ = v___y_2397_;
v___y_2386_ = v___y_2398_;
v___y_2387_ = v___y_2399_;
v___y_2388_ = v___y_2400_;
v___y_2389_ = v___x_2403_;
v___y_2390_ = v___y_2401_;
v___y_2391_ = v___y_2399_;
goto v___jp_2382_;
}
}
v___jp_2406_:
{
uint64_t v___x_2416_; uint8_t v___x_2417_; 
v___x_2416_ = lean_uint64_shift_right(v___y_2410_, v___y_2413_);
v___x_2417_ = lean_uint64_dec_eq(v___x_2416_, v___y_2411_);
if (v___x_2417_ == 0)
{
uint64_t v___x_2418_; 
v___x_2418_ = lean_uint64_add(v___y_2412_, v___y_2413_);
v___y_2396_ = v___y_2407_;
v___y_2397_ = v___y_2408_;
v___y_2398_ = v___y_2409_;
v___y_2399_ = v___y_2415_;
v___y_2400_ = v___y_2411_;
v___y_2401_ = v___y_2414_;
v___y_2402_ = v___x_2418_;
goto v___jp_2395_;
}
else
{
v___y_2396_ = v___y_2407_;
v___y_2397_ = v___y_2408_;
v___y_2398_ = v___y_2409_;
v___y_2399_ = v___y_2415_;
v___y_2400_ = v___y_2411_;
v___y_2401_ = v___y_2414_;
v___y_2402_ = v___y_2412_;
goto v___jp_2395_;
}
}
v___jp_2419_:
{
uint64_t v___x_2427_; uint64_t v___x_2428_; uint8_t v___x_2429_; 
v___x_2427_ = 8ULL;
v___x_2428_ = lean_uint64_shift_right(v___y_2424_, v___x_2427_);
v___x_2429_ = lean_uint64_dec_eq(v___x_2428_, v___y_2423_);
if (v___x_2429_ == 0)
{
v___y_2407_ = v___y_2420_;
v___y_2408_ = v___y_2421_;
v___y_2409_ = v___y_2422_;
v___y_2410_ = v___y_2424_;
v___y_2411_ = v___y_2423_;
v___y_2412_ = v___y_2426_;
v___y_2413_ = v___x_2427_;
v___y_2414_ = v___y_2425_;
v___y_2415_ = v___x_2428_;
goto v___jp_2406_;
}
else
{
v___y_2407_ = v___y_2420_;
v___y_2408_ = v___y_2421_;
v___y_2409_ = v___y_2422_;
v___y_2410_ = v___y_2424_;
v___y_2411_ = v___y_2423_;
v___y_2412_ = v___y_2426_;
v___y_2413_ = v___x_2427_;
v___y_2414_ = v___y_2425_;
v___y_2415_ = v___y_2424_;
goto v___jp_2406_;
}
}
v___jp_2430_:
{
uint64_t v___x_2440_; uint8_t v___x_2441_; 
v___x_2440_ = lean_uint64_shift_right(v___y_2433_, v___y_2436_);
v___x_2441_ = lean_uint64_dec_eq(v___x_2440_, v___y_2437_);
if (v___x_2441_ == 0)
{
uint64_t v___x_2442_; 
v___x_2442_ = lean_uint64_add(v___y_2431_, v___y_2436_);
v___y_2420_ = v___y_2432_;
v___y_2421_ = v___y_2434_;
v___y_2422_ = v___y_2435_;
v___y_2423_ = v___y_2437_;
v___y_2424_ = v___y_2439_;
v___y_2425_ = v___y_2438_;
v___y_2426_ = v___x_2442_;
goto v___jp_2419_;
}
else
{
v___y_2420_ = v___y_2432_;
v___y_2421_ = v___y_2434_;
v___y_2422_ = v___y_2435_;
v___y_2423_ = v___y_2437_;
v___y_2424_ = v___y_2439_;
v___y_2425_ = v___y_2438_;
v___y_2426_ = v___y_2431_;
goto v___jp_2419_;
}
}
v___jp_2443_:
{
uint64_t v___x_2451_; uint64_t v___x_2452_; uint8_t v___x_2453_; 
v___x_2451_ = 16ULL;
v___x_2452_ = lean_uint64_shift_right(v___y_2445_, v___x_2451_);
v___x_2453_ = lean_uint64_dec_eq(v___x_2452_, v___y_2448_);
if (v___x_2453_ == 0)
{
v___y_2431_ = v___y_2450_;
v___y_2432_ = v___y_2444_;
v___y_2433_ = v___y_2445_;
v___y_2434_ = v___y_2446_;
v___y_2435_ = v___y_2447_;
v___y_2436_ = v___x_2451_;
v___y_2437_ = v___y_2448_;
v___y_2438_ = v___y_2449_;
v___y_2439_ = v___x_2452_;
goto v___jp_2430_;
}
else
{
v___y_2431_ = v___y_2450_;
v___y_2432_ = v___y_2444_;
v___y_2433_ = v___y_2445_;
v___y_2434_ = v___y_2446_;
v___y_2435_ = v___y_2447_;
v___y_2436_ = v___x_2451_;
v___y_2437_ = v___y_2448_;
v___y_2438_ = v___y_2449_;
v___y_2439_ = v___y_2445_;
goto v___jp_2430_;
}
}
v___jp_2454_:
{
uint64_t v___x_2462_; uint8_t v___x_2463_; 
v___x_2462_ = lean_uint64_shift_right(v___y_2458_, v___y_2456_);
v___x_2463_ = lean_uint64_dec_eq(v___x_2462_, v___y_2459_);
if (v___x_2463_ == 0)
{
v___y_2444_ = v___y_2455_;
v___y_2445_ = v___y_2461_;
v___y_2446_ = v___y_2457_;
v___y_2447_ = v___y_2458_;
v___y_2448_ = v___y_2459_;
v___y_2449_ = v___y_2460_;
v___y_2450_ = v___y_2456_;
goto v___jp_2443_;
}
else
{
v___y_2444_ = v___y_2455_;
v___y_2445_ = v___y_2461_;
v___y_2446_ = v___y_2457_;
v___y_2447_ = v___y_2458_;
v___y_2448_ = v___y_2459_;
v___y_2449_ = v___y_2460_;
v___y_2450_ = v___y_2459_;
goto v___jp_2443_;
}
}
v___jp_2464_:
{
uint64_t v___x_2469_; uint8_t v___x_2470_; 
v___x_2469_ = 0ULL;
v___x_2470_ = lean_uint64_dec_eq(v___y_2467_, v___x_2469_);
if (v___x_2470_ == 0)
{
uint64_t v___x_2471_; uint64_t v___x_2472_; uint8_t v___x_2473_; 
v___x_2471_ = 32ULL;
v___x_2472_ = lean_uint64_shift_right(v___y_2467_, v___x_2471_);
v___x_2473_ = lean_uint64_dec_eq(v___x_2472_, v___x_2469_);
if (v___x_2473_ == 0)
{
v___y_2455_ = v___y_2465_;
v___y_2456_ = v___x_2471_;
v___y_2457_ = v___y_2466_;
v___y_2458_ = v___y_2467_;
v___y_2459_ = v___x_2469_;
v___y_2460_ = v___y_2468_;
v___y_2461_ = v___x_2472_;
goto v___jp_2454_;
}
else
{
v___y_2455_ = v___y_2465_;
v___y_2456_ = v___x_2471_;
v___y_2457_ = v___y_2466_;
v___y_2458_ = v___y_2467_;
v___y_2459_ = v___x_2469_;
v___y_2460_ = v___y_2468_;
v___y_2461_ = v___y_2467_;
goto v___jp_2454_;
}
}
else
{
if (v___y_2465_ == 0)
{
uint32_t v___x_2474_; 
v___x_2474_ = 0;
return v___x_2474_;
}
else
{
uint32_t v___x_2475_; 
v___x_2475_ = 2147483648;
return v___x_2475_;
}
}
}
v___jp_2476_:
{
uint64_t v___x_2483_; uint64_t v___x_2484_; uint64_t v___x_2485_; uint8_t v___x_2486_; 
v___x_2483_ = lean_uint64_mul(v___y_2481_, v___y_2480_);
v___x_2484_ = lean_uint64_add(v___y_2478_, v___y_2482_);
v___x_2485_ = 281474976710656ULL;
v___x_2486_ = lean_uint64_dec_lt(v___x_2483_, v___x_2485_);
if (v___x_2486_ == 0)
{
v___y_2465_ = v___y_2477_;
v___y_2466_ = v___y_2479_;
v___y_2467_ = v___x_2483_;
v___y_2468_ = v___x_2484_;
goto v___jp_2464_;
}
else
{
uint64_t v___x_2487_; uint8_t v___x_2488_; 
v___x_2487_ = 123ULL;
v___x_2488_ = lean_uint64_dec_le(v___x_2484_, v___x_2487_);
if (v___x_2488_ == 0)
{
v___y_2465_ = v___y_2477_;
v___y_2466_ = v___y_2479_;
v___y_2467_ = v___x_2483_;
v___y_2468_ = v___x_2484_;
goto v___jp_2464_;
}
else
{
uint64_t v___x_2489_; uint8_t v___x_2490_; 
v___x_2489_ = 0ULL;
v___x_2490_ = lean_uint64_dec_eq(v___x_2483_, v___x_2489_);
if (v___x_2490_ == 0)
{
uint64_t v___x_2491_; uint64_t v___x_2492_; uint8_t v___x_2493_; 
v___x_2491_ = 149ULL;
v___x_2492_ = lean_uint64_sub(v___x_2491_, v___x_2484_);
v___x_2493_ = lean_uint64_dec_eq(v___x_2492_, v___x_2489_);
if (v___x_2493_ == 0)
{
uint64_t v___x_2494_; uint8_t v___x_2495_; 
v___x_2494_ = 64ULL;
v___x_2495_ = lean_uint64_dec_lt(v___x_2492_, v___x_2494_);
if (v___x_2495_ == 0)
{
uint8_t v___x_2496_; 
v___x_2496_ = lean_uint64_dec_eq(v___x_2492_, v___x_2494_);
if (v___x_2496_ == 0)
{
v___y_1792_ = v___y_2477_;
v___y_1793_ = v___y_2479_;
v___y_1794_ = v___x_2489_;
v___y_1795_ = v___x_2489_;
goto v___jp_1791_;
}
else
{
uint64_t v___x_2497_; uint8_t v___x_2498_; 
v___x_2497_ = 9223372036854775808ULL;
v___x_2498_ = lean_uint64_dec_lt(v___x_2497_, v___x_2483_);
if (v___x_2498_ == 0)
{
v___y_1792_ = v___y_2477_;
v___y_1793_ = v___y_2479_;
v___y_1794_ = v___x_2489_;
v___y_1795_ = v___x_2489_;
goto v___jp_1791_;
}
else
{
uint64_t v___x_2499_; 
v___x_2499_ = 1ULL;
v___y_1792_ = v___y_2477_;
v___y_1793_ = v___y_2479_;
v___y_1794_ = v___x_2489_;
v___y_1795_ = v___x_2499_;
goto v___jp_1791_;
}
}
}
else
{
uint64_t v_quotient_2500_; uint64_t v___x_2501_; uint64_t v___x_2502_; uint64_t v___x_2503_; uint64_t v_remainder_2504_; uint64_t v___x_2505_; uint64_t v_half_2506_; uint8_t v___x_2507_; 
v_quotient_2500_ = lean_uint64_shift_right(v___x_2483_, v___x_2492_);
v___x_2501_ = 1ULL;
v___x_2502_ = lean_uint64_shift_left(v___x_2501_, v___x_2492_);
v___x_2503_ = lean_uint64_sub(v___x_2502_, v___x_2501_);
v_remainder_2504_ = lean_uint64_land(v___x_2483_, v___x_2503_);
v___x_2505_ = lean_uint64_sub(v___x_2492_, v___x_2501_);
v_half_2506_ = lean_uint64_shift_left(v___x_2501_, v___x_2505_);
v___x_2507_ = lean_uint64_dec_lt(v_remainder_2504_, v_half_2506_);
if (v___x_2507_ == 0)
{
uint8_t v___x_2508_; 
v___x_2508_ = lean_uint64_dec_lt(v_half_2506_, v_remainder_2504_);
if (v___x_2508_ == 0)
{
uint64_t v___x_2509_; uint8_t v___x_2510_; 
v___x_2509_ = lean_uint64_land(v_quotient_2500_, v___x_2501_);
v___x_2510_ = lean_uint64_dec_eq(v___x_2509_, v___x_2489_);
if (v___x_2510_ == 0)
{
uint64_t v___x_2511_; 
v___x_2511_ = lean_uint64_add(v_quotient_2500_, v___x_2501_);
v___y_1792_ = v___y_2477_;
v___y_1793_ = v___y_2479_;
v___y_1794_ = v___x_2489_;
v___y_1795_ = v___x_2511_;
goto v___jp_1791_;
}
else
{
v___y_1792_ = v___y_2477_;
v___y_1793_ = v___y_2479_;
v___y_1794_ = v___x_2489_;
v___y_1795_ = v_quotient_2500_;
goto v___jp_1791_;
}
}
else
{
uint64_t v___x_2512_; 
v___x_2512_ = lean_uint64_add(v_quotient_2500_, v___x_2501_);
v___y_1792_ = v___y_2477_;
v___y_1793_ = v___y_2479_;
v___y_1794_ = v___x_2489_;
v___y_1795_ = v___x_2512_;
goto v___jp_1791_;
}
}
else
{
v___y_1792_ = v___y_2477_;
v___y_1793_ = v___y_2479_;
v___y_1794_ = v___x_2489_;
v___y_1795_ = v_quotient_2500_;
goto v___jp_1791_;
}
}
}
else
{
v___y_1792_ = v___y_2477_;
v___y_1793_ = v___y_2479_;
v___y_1794_ = v___x_2489_;
v___y_1795_ = v___x_2483_;
goto v___jp_1791_;
}
}
else
{
if (v___y_2477_ == 0)
{
uint32_t v___x_2513_; 
v___x_2513_ = 0;
return v___x_2513_;
}
else
{
uint32_t v___x_2514_; 
v___x_2514_ = 2147483648;
return v___x_2514_;
}
}
}
}
}
v___jp_2515_:
{
uint32_t v___x_2520_; uint32_t v___x_2521_; uint32_t v___x_2522_; uint32_t v___x_2523_; uint32_t v___x_2524_; 
v___x_2520_ = lean_uint32_land(v___y_2518_, v___x_2232_);
v___x_2521_ = lean_uint32_shift_left(v___x_2520_, v___x_2191_);
v___x_2522_ = lean_uint32_lor(v___y_2519_, v___x_2521_);
v___x_2523_ = lean_uint32_land(v___y_2516_, v___y_2517_);
v___x_2524_ = lean_uint32_lor(v___x_2522_, v___x_2523_);
return v___x_2524_;
}
v___jp_2525_:
{
if (v___y_2526_ == 0)
{
uint32_t v___x_2530_; 
v___x_2530_ = 0;
v___y_2516_ = v___y_2529_;
v___y_2517_ = v___y_2527_;
v___y_2518_ = v___y_2528_;
v___y_2519_ = v___x_2530_;
goto v___jp_2515_;
}
else
{
uint32_t v___x_2531_; 
v___x_2531_ = 2147483648;
v___y_2516_ = v___y_2529_;
v___y_2517_ = v___y_2527_;
v___y_2518_ = v___y_2528_;
v___y_2519_ = v___x_2531_;
goto v___jp_2515_;
}
}
v___jp_2532_:
{
uint64_t v___x_2538_; uint64_t v_encodedExponent_2539_; uint32_t v___x_2540_; uint64_t v___x_2541_; uint8_t v___x_2542_; 
v___x_2538_ = 171ULL;
v_encodedExponent_2539_ = lean_uint64_sub(v___y_2534_, v___x_2538_);
v___x_2540_ = lean_uint64_to_uint32(v_encodedExponent_2539_);
v___x_2541_ = 8388608ULL;
v___x_2542_ = lean_uint64_dec_lt(v___y_2537_, v___x_2541_);
if (v___x_2542_ == 0)
{
uint64_t v___x_2543_; uint32_t v___x_2544_; 
v___x_2543_ = lean_uint64_sub(v___y_2537_, v___x_2541_);
v___x_2544_ = lean_uint64_to_uint32(v___x_2543_);
v___y_2526_ = v___y_2533_;
v___y_2527_ = v___y_2535_;
v___y_2528_ = v___x_2540_;
v___y_2529_ = v___x_2544_;
goto v___jp_2525_;
}
else
{
uint32_t v___x_2545_; 
v___x_2545_ = lean_uint64_to_uint32(v___y_2536_);
v___y_2526_ = v___y_2533_;
v___y_2527_ = v___y_2535_;
v___y_2528_ = v___x_2540_;
v___y_2529_ = v___x_2545_;
goto v___jp_2525_;
}
}
v___jp_2546_:
{
uint64_t v___x_2553_; uint8_t v___x_2554_; 
v___x_2553_ = 425ULL;
v___x_2554_ = lean_uint64_dec_lt(v___x_2553_, v___y_2552_);
if (v___x_2554_ == 0)
{
if (v___y_2551_ == 0)
{
v___y_2533_ = v___y_2547_;
v___y_2534_ = v___y_2552_;
v___y_2535_ = v___y_2548_;
v___y_2536_ = v___y_2549_;
v___y_2537_ = v___y_2550_;
goto v___jp_2532_;
}
else
{
uint64_t v___x_2555_; 
v___x_2555_ = 8388608ULL;
v___y_2533_ = v___y_2547_;
v___y_2534_ = v___y_2552_;
v___y_2535_ = v___y_2548_;
v___y_2536_ = v___y_2549_;
v___y_2537_ = v___x_2555_;
goto v___jp_2532_;
}
}
else
{
if (v___y_2547_ == 0)
{
uint32_t v___x_2556_; 
v___x_2556_ = 2139095040;
return v___x_2556_;
}
else
{
uint32_t v___x_2557_; 
v___x_2557_ = 4286578688;
return v___x_2557_;
}
}
}
v___jp_2558_:
{
uint64_t v___x_2564_; uint8_t v_carry_2565_; 
v___x_2564_ = 16777216ULL;
v_carry_2565_ = lean_uint64_dec_eq(v___y_2563_, v___x_2564_);
if (v_carry_2565_ == 0)
{
v___y_2547_ = v___y_2559_;
v___y_2548_ = v___y_2560_;
v___y_2549_ = v___y_2561_;
v___y_2550_ = v___y_2563_;
v___y_2551_ = v_carry_2565_;
v___y_2552_ = v___y_2562_;
goto v___jp_2546_;
}
else
{
uint64_t v___x_2566_; uint64_t v___x_2567_; 
v___x_2566_ = 1ULL;
v___x_2567_ = lean_uint64_add(v___y_2562_, v___x_2566_);
v___y_2547_ = v___y_2559_;
v___y_2548_ = v___y_2560_;
v___y_2549_ = v___y_2561_;
v___y_2550_ = v___y_2563_;
v___y_2551_ = v_carry_2565_;
v___y_2552_ = v___x_2567_;
goto v___jp_2546_;
}
}
v___jp_2568_:
{
uint64_t v_position_2575_; uint64_t v___x_2576_; uint8_t v___x_2577_; 
v_position_2575_ = lean_uint64_add(v___y_2574_, v___y_2570_);
v___x_2576_ = 172ULL;
v___x_2577_ = lean_uint64_dec_lt(v_position_2575_, v___x_2576_);
if (v___x_2577_ == 0)
{
uint64_t v___x_2578_; uint8_t v___x_2579_; 
v___x_2578_ = 23ULL;
v___x_2579_ = lean_uint64_dec_lt(v___y_2574_, v___x_2578_);
if (v___x_2579_ == 0)
{
uint64_t v___x_2580_; uint8_t v___x_2581_; 
v___x_2580_ = lean_uint64_sub(v___y_2574_, v___x_2578_);
v___x_2581_ = lean_uint64_dec_eq(v___x_2580_, v___y_2572_);
if (v___x_2581_ == 0)
{
uint64_t v___x_2582_; uint8_t v___x_2583_; 
v___x_2582_ = 64ULL;
v___x_2583_ = lean_uint64_dec_lt(v___x_2580_, v___x_2582_);
if (v___x_2583_ == 0)
{
uint8_t v___x_2584_; 
v___x_2584_ = lean_uint64_dec_eq(v___x_2580_, v___x_2582_);
if (v___x_2584_ == 0)
{
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v___y_2572_;
goto v___jp_2558_;
}
else
{
uint64_t v___x_2585_; uint8_t v___x_2586_; 
v___x_2585_ = 9223372036854775808ULL;
v___x_2586_ = lean_uint64_dec_lt(v___x_2585_, v___y_2573_);
if (v___x_2586_ == 0)
{
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v___y_2572_;
goto v___jp_2558_;
}
else
{
uint64_t v___x_2587_; 
v___x_2587_ = 1ULL;
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v___x_2587_;
goto v___jp_2558_;
}
}
}
else
{
uint64_t v_quotient_2588_; uint64_t v___x_2589_; uint64_t v___x_2590_; uint64_t v___x_2591_; uint64_t v_remainder_2592_; uint64_t v___x_2593_; uint64_t v_half_2594_; uint8_t v___x_2595_; 
v_quotient_2588_ = lean_uint64_shift_right(v___y_2573_, v___x_2580_);
v___x_2589_ = 1ULL;
v___x_2590_ = lean_uint64_shift_left(v___x_2589_, v___x_2580_);
v___x_2591_ = lean_uint64_sub(v___x_2590_, v___x_2589_);
v_remainder_2592_ = lean_uint64_land(v___y_2573_, v___x_2591_);
v___x_2593_ = lean_uint64_sub(v___x_2580_, v___x_2589_);
v_half_2594_ = lean_uint64_shift_left(v___x_2589_, v___x_2593_);
v___x_2595_ = lean_uint64_dec_lt(v_remainder_2592_, v_half_2594_);
if (v___x_2595_ == 0)
{
uint8_t v___x_2596_; 
v___x_2596_ = lean_uint64_dec_lt(v_half_2594_, v_remainder_2592_);
if (v___x_2596_ == 0)
{
uint64_t v___x_2597_; uint8_t v___x_2598_; 
v___x_2597_ = lean_uint64_land(v_quotient_2588_, v___x_2589_);
v___x_2598_ = lean_uint64_dec_eq(v___x_2597_, v___y_2572_);
if (v___x_2598_ == 0)
{
uint64_t v___x_2599_; 
v___x_2599_ = lean_uint64_add(v_quotient_2588_, v___x_2589_);
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v___x_2599_;
goto v___jp_2558_;
}
else
{
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v_quotient_2588_;
goto v___jp_2558_;
}
}
else
{
uint64_t v___x_2600_; 
v___x_2600_ = lean_uint64_add(v_quotient_2588_, v___x_2589_);
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v___x_2600_;
goto v___jp_2558_;
}
}
else
{
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v_quotient_2588_;
goto v___jp_2558_;
}
}
}
else
{
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v___y_2573_;
goto v___jp_2558_;
}
}
else
{
uint64_t v___x_2601_; uint64_t v___x_2602_; 
v___x_2601_ = lean_uint64_sub(v___x_2578_, v___y_2574_);
v___x_2602_ = lean_uint64_shift_left(v___y_2573_, v___x_2601_);
v___y_2559_ = v___y_2569_;
v___y_2560_ = v___y_2571_;
v___y_2561_ = v___y_2572_;
v___y_2562_ = v_position_2575_;
v___y_2563_ = v___x_2602_;
goto v___jp_2558_;
}
}
else
{
uint64_t v___x_2603_; uint8_t v___x_2604_; 
v___x_2603_ = 149ULL;
v___x_2604_ = lean_uint64_dec_lt(v___y_2570_, v___x_2603_);
if (v___x_2604_ == 0)
{
uint64_t v___x_2605_; uint64_t v___x_2606_; 
v___x_2605_ = lean_uint64_sub(v___y_2570_, v___x_2603_);
v___x_2606_ = lean_uint64_shift_left(v___y_2573_, v___x_2605_);
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v___x_2606_;
goto v___jp_1915_;
}
else
{
uint64_t v___x_2607_; uint8_t v___x_2608_; 
v___x_2607_ = lean_uint64_sub(v___x_2603_, v___y_2570_);
v___x_2608_ = lean_uint64_dec_eq(v___x_2607_, v___y_2572_);
if (v___x_2608_ == 0)
{
uint64_t v___x_2609_; uint8_t v___x_2610_; 
v___x_2609_ = 64ULL;
v___x_2610_ = lean_uint64_dec_lt(v___x_2607_, v___x_2609_);
if (v___x_2610_ == 0)
{
uint8_t v___x_2611_; 
v___x_2611_ = lean_uint64_dec_eq(v___x_2607_, v___x_2609_);
if (v___x_2611_ == 0)
{
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v___y_2572_;
goto v___jp_1915_;
}
else
{
uint64_t v___x_2612_; uint8_t v___x_2613_; 
v___x_2612_ = 9223372036854775808ULL;
v___x_2613_ = lean_uint64_dec_lt(v___x_2612_, v___y_2573_);
if (v___x_2613_ == 0)
{
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v___y_2572_;
goto v___jp_1915_;
}
else
{
uint64_t v___x_2614_; 
v___x_2614_ = 1ULL;
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v___x_2614_;
goto v___jp_1915_;
}
}
}
else
{
uint64_t v_quotient_2615_; uint64_t v___x_2616_; uint64_t v___x_2617_; uint64_t v___x_2618_; uint64_t v_remainder_2619_; uint64_t v___x_2620_; uint64_t v_half_2621_; uint8_t v___x_2622_; 
v_quotient_2615_ = lean_uint64_shift_right(v___y_2573_, v___x_2607_);
v___x_2616_ = 1ULL;
v___x_2617_ = lean_uint64_shift_left(v___x_2616_, v___x_2607_);
v___x_2618_ = lean_uint64_sub(v___x_2617_, v___x_2616_);
v_remainder_2619_ = lean_uint64_land(v___y_2573_, v___x_2618_);
v___x_2620_ = lean_uint64_sub(v___x_2607_, v___x_2616_);
v_half_2621_ = lean_uint64_shift_left(v___x_2616_, v___x_2620_);
v___x_2622_ = lean_uint64_dec_lt(v_remainder_2619_, v_half_2621_);
if (v___x_2622_ == 0)
{
uint8_t v___x_2623_; 
v___x_2623_ = lean_uint64_dec_lt(v_half_2621_, v_remainder_2619_);
if (v___x_2623_ == 0)
{
uint64_t v___x_2624_; uint8_t v___x_2625_; 
v___x_2624_ = lean_uint64_land(v_quotient_2615_, v___x_2616_);
v___x_2625_ = lean_uint64_dec_eq(v___x_2624_, v___y_2572_);
if (v___x_2625_ == 0)
{
uint64_t v___x_2626_; 
v___x_2626_ = lean_uint64_add(v_quotient_2615_, v___x_2616_);
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v___x_2626_;
goto v___jp_1915_;
}
else
{
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v_quotient_2615_;
goto v___jp_1915_;
}
}
else
{
uint64_t v___x_2627_; 
v___x_2627_ = lean_uint64_add(v_quotient_2615_, v___x_2616_);
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v___x_2627_;
goto v___jp_1915_;
}
}
else
{
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v_quotient_2615_;
goto v___jp_1915_;
}
}
}
else
{
v___y_1916_ = v___y_2569_;
v___y_1917_ = v___y_2571_;
v___y_1918_ = v___y_2572_;
v___y_1919_ = v___y_2573_;
goto v___jp_1915_;
}
}
}
}
v___jp_2628_:
{
uint64_t v___x_2636_; uint64_t v___x_2637_; uint8_t v___x_2638_; 
v___x_2636_ = 1ULL;
v___x_2637_ = lean_uint64_shift_right(v___y_2633_, v___x_2636_);
v___x_2638_ = lean_uint64_dec_eq(v___x_2637_, v___y_2632_);
if (v___x_2638_ == 0)
{
uint64_t v___x_2639_; 
v___x_2639_ = lean_uint64_add(v___y_2635_, v___x_2636_);
v___y_2569_ = v___y_2629_;
v___y_2570_ = v___y_2630_;
v___y_2571_ = v___y_2631_;
v___y_2572_ = v___y_2632_;
v___y_2573_ = v___y_2634_;
v___y_2574_ = v___x_2639_;
goto v___jp_2568_;
}
else
{
v___y_2569_ = v___y_2629_;
v___y_2570_ = v___y_2630_;
v___y_2571_ = v___y_2631_;
v___y_2572_ = v___y_2632_;
v___y_2573_ = v___y_2634_;
v___y_2574_ = v___y_2635_;
goto v___jp_2568_;
}
}
v___jp_2640_:
{
uint64_t v___x_2650_; uint8_t v___x_2651_; 
v___x_2650_ = lean_uint64_shift_right(v___y_2643_, v___y_2646_);
v___x_2651_ = lean_uint64_dec_eq(v___x_2650_, v___y_2647_);
if (v___x_2651_ == 0)
{
uint64_t v___x_2652_; 
v___x_2652_ = lean_uint64_add(v___y_2645_, v___y_2646_);
v___y_2629_ = v___y_2641_;
v___y_2630_ = v___y_2642_;
v___y_2631_ = v___y_2644_;
v___y_2632_ = v___y_2647_;
v___y_2633_ = v___y_2649_;
v___y_2634_ = v___y_2648_;
v___y_2635_ = v___x_2652_;
goto v___jp_2628_;
}
else
{
v___y_2629_ = v___y_2641_;
v___y_2630_ = v___y_2642_;
v___y_2631_ = v___y_2644_;
v___y_2632_ = v___y_2647_;
v___y_2633_ = v___y_2649_;
v___y_2634_ = v___y_2648_;
v___y_2635_ = v___y_2645_;
goto v___jp_2628_;
}
}
v___jp_2653_:
{
uint64_t v___x_2661_; uint64_t v___x_2662_; uint8_t v___x_2663_; 
v___x_2661_ = 2ULL;
v___x_2662_ = lean_uint64_shift_right(v___y_2656_, v___x_2661_);
v___x_2663_ = lean_uint64_dec_eq(v___x_2662_, v___y_2658_);
if (v___x_2663_ == 0)
{
v___y_2641_ = v___y_2654_;
v___y_2642_ = v___y_2655_;
v___y_2643_ = v___y_2656_;
v___y_2644_ = v___y_2657_;
v___y_2645_ = v___y_2660_;
v___y_2646_ = v___x_2661_;
v___y_2647_ = v___y_2658_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___x_2662_;
goto v___jp_2640_;
}
else
{
v___y_2641_ = v___y_2654_;
v___y_2642_ = v___y_2655_;
v___y_2643_ = v___y_2656_;
v___y_2644_ = v___y_2657_;
v___y_2645_ = v___y_2660_;
v___y_2646_ = v___x_2661_;
v___y_2647_ = v___y_2658_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___y_2656_;
goto v___jp_2640_;
}
}
v___jp_2664_:
{
uint64_t v___x_2674_; uint8_t v___x_2675_; 
v___x_2674_ = lean_uint64_shift_right(v___y_2668_, v___y_2670_);
v___x_2675_ = lean_uint64_dec_eq(v___x_2674_, v___y_2669_);
if (v___x_2675_ == 0)
{
uint64_t v___x_2676_; 
v___x_2676_ = lean_uint64_add(v___y_2671_, v___y_2670_);
v___y_2654_ = v___y_2665_;
v___y_2655_ = v___y_2666_;
v___y_2656_ = v___y_2673_;
v___y_2657_ = v___y_2667_;
v___y_2658_ = v___y_2669_;
v___y_2659_ = v___y_2672_;
v___y_2660_ = v___x_2676_;
goto v___jp_2653_;
}
else
{
v___y_2654_ = v___y_2665_;
v___y_2655_ = v___y_2666_;
v___y_2656_ = v___y_2673_;
v___y_2657_ = v___y_2667_;
v___y_2658_ = v___y_2669_;
v___y_2659_ = v___y_2672_;
v___y_2660_ = v___y_2671_;
goto v___jp_2653_;
}
}
v___jp_2677_:
{
uint64_t v___x_2685_; uint64_t v___x_2686_; uint8_t v___x_2687_; 
v___x_2685_ = 4ULL;
v___x_2686_ = lean_uint64_shift_right(v___y_2681_, v___x_2685_);
v___x_2687_ = lean_uint64_dec_eq(v___x_2686_, v___y_2682_);
if (v___x_2687_ == 0)
{
v___y_2665_ = v___y_2678_;
v___y_2666_ = v___y_2679_;
v___y_2667_ = v___y_2680_;
v___y_2668_ = v___y_2681_;
v___y_2669_ = v___y_2682_;
v___y_2670_ = v___x_2685_;
v___y_2671_ = v___y_2684_;
v___y_2672_ = v___y_2683_;
v___y_2673_ = v___x_2686_;
goto v___jp_2664_;
}
else
{
v___y_2665_ = v___y_2678_;
v___y_2666_ = v___y_2679_;
v___y_2667_ = v___y_2680_;
v___y_2668_ = v___y_2681_;
v___y_2669_ = v___y_2682_;
v___y_2670_ = v___x_2685_;
v___y_2671_ = v___y_2684_;
v___y_2672_ = v___y_2683_;
v___y_2673_ = v___y_2681_;
goto v___jp_2664_;
}
}
v___jp_2688_:
{
uint64_t v___x_2698_; uint8_t v___x_2699_; 
v___x_2698_ = lean_uint64_shift_right(v___y_2694_, v___y_2692_);
v___x_2699_ = lean_uint64_dec_eq(v___x_2698_, v___y_2693_);
if (v___x_2699_ == 0)
{
uint64_t v___x_2700_; 
v___x_2700_ = lean_uint64_add(v___y_2696_, v___y_2692_);
v___y_2678_ = v___y_2689_;
v___y_2679_ = v___y_2690_;
v___y_2680_ = v___y_2691_;
v___y_2681_ = v___y_2697_;
v___y_2682_ = v___y_2693_;
v___y_2683_ = v___y_2695_;
v___y_2684_ = v___x_2700_;
goto v___jp_2677_;
}
else
{
v___y_2678_ = v___y_2689_;
v___y_2679_ = v___y_2690_;
v___y_2680_ = v___y_2691_;
v___y_2681_ = v___y_2697_;
v___y_2682_ = v___y_2693_;
v___y_2683_ = v___y_2695_;
v___y_2684_ = v___y_2696_;
goto v___jp_2677_;
}
}
v___jp_2701_:
{
uint64_t v___x_2709_; uint64_t v___x_2710_; uint8_t v___x_2711_; 
v___x_2709_ = 8ULL;
v___x_2710_ = lean_uint64_shift_right(v___y_2706_, v___x_2709_);
v___x_2711_ = lean_uint64_dec_eq(v___x_2710_, v___y_2705_);
if (v___x_2711_ == 0)
{
v___y_2689_ = v___y_2702_;
v___y_2690_ = v___y_2703_;
v___y_2691_ = v___y_2704_;
v___y_2692_ = v___x_2709_;
v___y_2693_ = v___y_2705_;
v___y_2694_ = v___y_2706_;
v___y_2695_ = v___y_2707_;
v___y_2696_ = v___y_2708_;
v___y_2697_ = v___x_2710_;
goto v___jp_2688_;
}
else
{
v___y_2689_ = v___y_2702_;
v___y_2690_ = v___y_2703_;
v___y_2691_ = v___y_2704_;
v___y_2692_ = v___x_2709_;
v___y_2693_ = v___y_2705_;
v___y_2694_ = v___y_2706_;
v___y_2695_ = v___y_2707_;
v___y_2696_ = v___y_2708_;
v___y_2697_ = v___y_2706_;
goto v___jp_2688_;
}
}
v___jp_2712_:
{
uint64_t v___x_2722_; uint8_t v___x_2723_; 
v___x_2722_ = lean_uint64_shift_right(v___y_2720_, v___y_2719_);
v___x_2723_ = lean_uint64_dec_eq(v___x_2722_, v___y_2716_);
if (v___x_2723_ == 0)
{
uint64_t v___x_2724_; 
v___x_2724_ = lean_uint64_add(v___y_2717_, v___y_2719_);
v___y_2702_ = v___y_2713_;
v___y_2703_ = v___y_2714_;
v___y_2704_ = v___y_2715_;
v___y_2705_ = v___y_2716_;
v___y_2706_ = v___y_2721_;
v___y_2707_ = v___y_2718_;
v___y_2708_ = v___x_2724_;
goto v___jp_2701_;
}
else
{
v___y_2702_ = v___y_2713_;
v___y_2703_ = v___y_2714_;
v___y_2704_ = v___y_2715_;
v___y_2705_ = v___y_2716_;
v___y_2706_ = v___y_2721_;
v___y_2707_ = v___y_2718_;
v___y_2708_ = v___y_2717_;
goto v___jp_2701_;
}
}
v___jp_2725_:
{
uint64_t v___x_2733_; uint64_t v___x_2734_; uint8_t v___x_2735_; 
v___x_2733_ = 16ULL;
v___x_2734_ = lean_uint64_shift_right(v___y_2731_, v___x_2733_);
v___x_2735_ = lean_uint64_dec_eq(v___x_2734_, v___y_2729_);
if (v___x_2735_ == 0)
{
v___y_2713_ = v___y_2726_;
v___y_2714_ = v___y_2727_;
v___y_2715_ = v___y_2728_;
v___y_2716_ = v___y_2729_;
v___y_2717_ = v___y_2732_;
v___y_2718_ = v___y_2730_;
v___y_2719_ = v___x_2733_;
v___y_2720_ = v___y_2731_;
v___y_2721_ = v___x_2734_;
goto v___jp_2712_;
}
else
{
v___y_2713_ = v___y_2726_;
v___y_2714_ = v___y_2727_;
v___y_2715_ = v___y_2728_;
v___y_2716_ = v___y_2729_;
v___y_2717_ = v___y_2732_;
v___y_2718_ = v___y_2730_;
v___y_2719_ = v___x_2733_;
v___y_2720_ = v___y_2731_;
v___y_2721_ = v___y_2731_;
goto v___jp_2712_;
}
}
v___jp_2736_:
{
uint64_t v___x_2744_; uint8_t v___x_2745_; 
v___x_2744_ = lean_uint64_shift_right(v___y_2742_, v___y_2738_);
v___x_2745_ = lean_uint64_dec_eq(v___x_2744_, v___y_2741_);
if (v___x_2745_ == 0)
{
v___y_2726_ = v___y_2737_;
v___y_2727_ = v___y_2739_;
v___y_2728_ = v___y_2740_;
v___y_2729_ = v___y_2741_;
v___y_2730_ = v___y_2742_;
v___y_2731_ = v___y_2743_;
v___y_2732_ = v___y_2738_;
goto v___jp_2725_;
}
else
{
v___y_2726_ = v___y_2737_;
v___y_2727_ = v___y_2739_;
v___y_2728_ = v___y_2740_;
v___y_2729_ = v___y_2741_;
v___y_2730_ = v___y_2742_;
v___y_2731_ = v___y_2743_;
v___y_2732_ = v___y_2741_;
goto v___jp_2725_;
}
}
v___jp_2746_:
{
uint64_t v___x_2751_; uint8_t v___x_2752_; 
v___x_2751_ = 0ULL;
v___x_2752_ = lean_uint64_dec_eq(v___y_2750_, v___x_2751_);
if (v___x_2752_ == 0)
{
uint64_t v___x_2753_; uint64_t v___x_2754_; uint8_t v___x_2755_; 
v___x_2753_ = 32ULL;
v___x_2754_ = lean_uint64_shift_right(v___y_2750_, v___x_2753_);
v___x_2755_ = lean_uint64_dec_eq(v___x_2754_, v___x_2751_);
if (v___x_2755_ == 0)
{
v___y_2737_ = v___y_2747_;
v___y_2738_ = v___x_2753_;
v___y_2739_ = v___y_2748_;
v___y_2740_ = v___y_2749_;
v___y_2741_ = v___x_2751_;
v___y_2742_ = v___y_2750_;
v___y_2743_ = v___x_2754_;
goto v___jp_2736_;
}
else
{
v___y_2737_ = v___y_2747_;
v___y_2738_ = v___x_2753_;
v___y_2739_ = v___y_2748_;
v___y_2740_ = v___y_2749_;
v___y_2741_ = v___x_2751_;
v___y_2742_ = v___y_2750_;
v___y_2743_ = v___y_2750_;
goto v___jp_2736_;
}
}
else
{
if (v___y_2747_ == 0)
{
uint32_t v___x_2756_; 
v___x_2756_ = 0;
return v___x_2756_;
}
else
{
uint32_t v___x_2757_; 
v___x_2757_ = 2147483648;
return v___x_2757_;
}
}
}
v___jp_2758_:
{
uint64_t v___x_2765_; uint64_t v___x_2766_; uint64_t v___x_2767_; uint8_t v___x_2768_; 
v___x_2765_ = lean_uint64_mul(v___y_2761_, v___y_2763_);
v___x_2766_ = lean_uint64_add(v___y_2759_, v___y_2764_);
v___x_2767_ = 281474976710656ULL;
v___x_2768_ = lean_uint64_dec_lt(v___x_2765_, v___x_2767_);
if (v___x_2768_ == 0)
{
v___y_2747_ = v___y_2760_;
v___y_2748_ = v___x_2766_;
v___y_2749_ = v___y_2762_;
v___y_2750_ = v___x_2765_;
goto v___jp_2746_;
}
else
{
uint64_t v___x_2769_; uint8_t v___x_2770_; 
v___x_2769_ = 123ULL;
v___x_2770_ = lean_uint64_dec_le(v___x_2766_, v___x_2769_);
if (v___x_2770_ == 0)
{
v___y_2747_ = v___y_2760_;
v___y_2748_ = v___x_2766_;
v___y_2749_ = v___y_2762_;
v___y_2750_ = v___x_2765_;
goto v___jp_2746_;
}
else
{
uint64_t v___x_2771_; uint8_t v___x_2772_; 
v___x_2771_ = 0ULL;
v___x_2772_ = lean_uint64_dec_eq(v___x_2765_, v___x_2771_);
if (v___x_2772_ == 0)
{
uint64_t v___x_2773_; uint64_t v___x_2774_; uint8_t v___x_2775_; 
v___x_2773_ = 149ULL;
v___x_2774_ = lean_uint64_sub(v___x_2773_, v___x_2766_);
v___x_2775_ = lean_uint64_dec_eq(v___x_2774_, v___x_2771_);
if (v___x_2775_ == 0)
{
uint64_t v___x_2776_; uint8_t v___x_2777_; 
v___x_2776_ = 64ULL;
v___x_2777_ = lean_uint64_dec_lt(v___x_2774_, v___x_2776_);
if (v___x_2777_ == 0)
{
uint8_t v___x_2778_; 
v___x_2778_ = lean_uint64_dec_eq(v___x_2774_, v___x_2776_);
if (v___x_2778_ == 0)
{
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___y_2762_;
v___y_1939_ = v___x_2771_;
v___y_1940_ = v___x_2771_;
goto v___jp_1936_;
}
else
{
uint64_t v___x_2779_; uint8_t v___x_2780_; 
v___x_2779_ = 9223372036854775808ULL;
v___x_2780_ = lean_uint64_dec_lt(v___x_2779_, v___x_2765_);
if (v___x_2780_ == 0)
{
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___y_2762_;
v___y_1939_ = v___x_2771_;
v___y_1940_ = v___x_2771_;
goto v___jp_1936_;
}
else
{
uint64_t v___x_2781_; 
v___x_2781_ = 1ULL;
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___y_2762_;
v___y_1939_ = v___x_2771_;
v___y_1940_ = v___x_2781_;
goto v___jp_1936_;
}
}
}
else
{
uint64_t v_quotient_2782_; uint64_t v___x_2783_; uint64_t v___x_2784_; uint64_t v___x_2785_; uint64_t v_remainder_2786_; uint64_t v___x_2787_; uint64_t v_half_2788_; uint8_t v___x_2789_; 
v_quotient_2782_ = lean_uint64_shift_right(v___x_2765_, v___x_2774_);
v___x_2783_ = 1ULL;
v___x_2784_ = lean_uint64_shift_left(v___x_2783_, v___x_2774_);
v___x_2785_ = lean_uint64_sub(v___x_2784_, v___x_2783_);
v_remainder_2786_ = lean_uint64_land(v___x_2765_, v___x_2785_);
v___x_2787_ = lean_uint64_sub(v___x_2774_, v___x_2783_);
v_half_2788_ = lean_uint64_shift_left(v___x_2783_, v___x_2787_);
v___x_2789_ = lean_uint64_dec_lt(v_remainder_2786_, v_half_2788_);
if (v___x_2789_ == 0)
{
uint8_t v___x_2790_; 
v___x_2790_ = lean_uint64_dec_lt(v_half_2788_, v_remainder_2786_);
if (v___x_2790_ == 0)
{
uint64_t v___x_2791_; uint8_t v___x_2792_; 
v___x_2791_ = lean_uint64_land(v_quotient_2782_, v___x_2783_);
v___x_2792_ = lean_uint64_dec_eq(v___x_2791_, v___x_2771_);
if (v___x_2792_ == 0)
{
uint64_t v___x_2793_; 
v___x_2793_ = lean_uint64_add(v_quotient_2782_, v___x_2783_);
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___y_2762_;
v___y_1939_ = v___x_2771_;
v___y_1940_ = v___x_2793_;
goto v___jp_1936_;
}
else
{
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___y_2762_;
v___y_1939_ = v___x_2771_;
v___y_1940_ = v_quotient_2782_;
goto v___jp_1936_;
}
}
else
{
uint64_t v___x_2794_; 
v___x_2794_ = lean_uint64_add(v_quotient_2782_, v___x_2783_);
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___y_2762_;
v___y_1939_ = v___x_2771_;
v___y_1940_ = v___x_2794_;
goto v___jp_1936_;
}
}
else
{
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___y_2762_;
v___y_1939_ = v___x_2771_;
v___y_1940_ = v_quotient_2782_;
goto v___jp_1936_;
}
}
}
else
{
v___y_1937_ = v___y_2760_;
v___y_1938_ = v___y_2762_;
v___y_1939_ = v___x_2771_;
v___y_1940_ = v___x_2765_;
goto v___jp_1936_;
}
}
else
{
if (v___y_2760_ == 0)
{
uint32_t v___x_2795_; 
v___x_2795_ = 0;
return v___x_2795_;
}
else
{
uint32_t v___x_2796_; 
v___x_2796_ = 2147483648;
return v___x_2796_;
}
}
}
}
}
v___jp_2797_:
{
uint32_t v___x_2802_; uint32_t v___x_2803_; uint32_t v___x_2804_; uint32_t v___x_2805_; uint32_t v___x_2806_; 
v___x_2802_ = lean_uint32_land(v___y_2800_, v___x_2232_);
v___x_2803_ = lean_uint32_shift_left(v___x_2802_, v___x_2191_);
v___x_2804_ = lean_uint32_lor(v___y_2801_, v___x_2803_);
v___x_2805_ = lean_uint32_land(v___y_2798_, v___y_2799_);
v___x_2806_ = lean_uint32_lor(v___x_2804_, v___x_2805_);
return v___x_2806_;
}
v___jp_2807_:
{
if (v___y_2810_ == 0)
{
uint32_t v___x_2812_; 
v___x_2812_ = 0;
v___y_2798_ = v___y_2811_;
v___y_2799_ = v___y_2808_;
v___y_2800_ = v___y_2809_;
v___y_2801_ = v___x_2812_;
goto v___jp_2797_;
}
else
{
uint32_t v___x_2813_; 
v___x_2813_ = 2147483648;
v___y_2798_ = v___y_2811_;
v___y_2799_ = v___y_2808_;
v___y_2800_ = v___y_2809_;
v___y_2801_ = v___x_2813_;
goto v___jp_2797_;
}
}
v___jp_2814_:
{
uint64_t v___x_2820_; uint64_t v_encodedExponent_2821_; uint32_t v___x_2822_; uint64_t v___x_2823_; uint8_t v___x_2824_; 
v___x_2820_ = 171ULL;
v_encodedExponent_2821_ = lean_uint64_sub(v___y_2815_, v___x_2820_);
v___x_2822_ = lean_uint64_to_uint32(v_encodedExponent_2821_);
v___x_2823_ = 8388608ULL;
v___x_2824_ = lean_uint64_dec_lt(v___y_2819_, v___x_2823_);
if (v___x_2824_ == 0)
{
uint64_t v___x_2825_; uint32_t v___x_2826_; 
v___x_2825_ = lean_uint64_sub(v___y_2819_, v___x_2823_);
v___x_2826_ = lean_uint64_to_uint32(v___x_2825_);
v___y_2808_ = v___y_2816_;
v___y_2809_ = v___x_2822_;
v___y_2810_ = v___y_2818_;
v___y_2811_ = v___x_2826_;
goto v___jp_2807_;
}
else
{
uint32_t v___x_2827_; 
v___x_2827_ = lean_uint64_to_uint32(v___y_2817_);
v___y_2808_ = v___y_2816_;
v___y_2809_ = v___x_2822_;
v___y_2810_ = v___y_2818_;
v___y_2811_ = v___x_2827_;
goto v___jp_2807_;
}
}
v___jp_2828_:
{
uint64_t v___x_2835_; uint8_t v___x_2836_; 
v___x_2835_ = 425ULL;
v___x_2836_ = lean_uint64_dec_lt(v___x_2835_, v___y_2834_);
if (v___x_2836_ == 0)
{
if (v___y_2829_ == 0)
{
v___y_2815_ = v___y_2834_;
v___y_2816_ = v___y_2831_;
v___y_2817_ = v___y_2832_;
v___y_2818_ = v___y_2833_;
v___y_2819_ = v___y_2830_;
goto v___jp_2814_;
}
else
{
uint64_t v___x_2837_; 
v___x_2837_ = 8388608ULL;
v___y_2815_ = v___y_2834_;
v___y_2816_ = v___y_2831_;
v___y_2817_ = v___y_2832_;
v___y_2818_ = v___y_2833_;
v___y_2819_ = v___x_2837_;
goto v___jp_2814_;
}
}
else
{
if (v___y_2833_ == 0)
{
uint32_t v___x_2838_; 
v___x_2838_ = 2139095040;
return v___x_2838_;
}
else
{
uint32_t v___x_2839_; 
v___x_2839_ = 4286578688;
return v___x_2839_;
}
}
}
v___jp_2840_:
{
uint64_t v___x_2846_; uint8_t v_carry_2847_; 
v___x_2846_ = 16777216ULL;
v_carry_2847_ = lean_uint64_dec_eq(v___y_2845_, v___x_2846_);
if (v_carry_2847_ == 0)
{
v___y_2829_ = v_carry_2847_;
v___y_2830_ = v___y_2845_;
v___y_2831_ = v___y_2842_;
v___y_2832_ = v___y_2843_;
v___y_2833_ = v___y_2844_;
v___y_2834_ = v___y_2841_;
goto v___jp_2828_;
}
else
{
uint64_t v___x_2848_; uint64_t v___x_2849_; 
v___x_2848_ = 1ULL;
v___x_2849_ = lean_uint64_add(v___y_2841_, v___x_2848_);
v___y_2829_ = v_carry_2847_;
v___y_2830_ = v___y_2845_;
v___y_2831_ = v___y_2842_;
v___y_2832_ = v___y_2843_;
v___y_2833_ = v___y_2844_;
v___y_2834_ = v___x_2849_;
goto v___jp_2828_;
}
}
v___jp_2850_:
{
uint64_t v_position_2857_; uint64_t v___x_2858_; uint8_t v___x_2859_; 
v_position_2857_ = lean_uint64_add(v___y_2856_, v___y_2853_);
v___x_2858_ = 172ULL;
v___x_2859_ = lean_uint64_dec_lt(v_position_2857_, v___x_2858_);
if (v___x_2859_ == 0)
{
uint64_t v___x_2860_; uint8_t v___x_2861_; 
v___x_2860_ = 23ULL;
v___x_2861_ = lean_uint64_dec_lt(v___y_2856_, v___x_2860_);
if (v___x_2861_ == 0)
{
uint64_t v___x_2862_; uint8_t v___x_2863_; 
v___x_2862_ = lean_uint64_sub(v___y_2856_, v___x_2860_);
v___x_2863_ = lean_uint64_dec_eq(v___x_2862_, v___y_2854_);
if (v___x_2863_ == 0)
{
uint64_t v___x_2864_; uint8_t v___x_2865_; 
v___x_2864_ = 64ULL;
v___x_2865_ = lean_uint64_dec_lt(v___x_2862_, v___x_2864_);
if (v___x_2865_ == 0)
{
uint8_t v___x_2866_; 
v___x_2866_ = lean_uint64_dec_eq(v___x_2862_, v___x_2864_);
if (v___x_2866_ == 0)
{
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v___y_2854_;
goto v___jp_2840_;
}
else
{
uint64_t v___x_2867_; uint8_t v___x_2868_; 
v___x_2867_ = 9223372036854775808ULL;
v___x_2868_ = lean_uint64_dec_lt(v___x_2867_, v___y_2852_);
if (v___x_2868_ == 0)
{
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v___y_2854_;
goto v___jp_2840_;
}
else
{
uint64_t v___x_2869_; 
v___x_2869_ = 1ULL;
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v___x_2869_;
goto v___jp_2840_;
}
}
}
else
{
uint64_t v_quotient_2870_; uint64_t v___x_2871_; uint64_t v___x_2872_; uint64_t v___x_2873_; uint64_t v_remainder_2874_; uint64_t v___x_2875_; uint64_t v_half_2876_; uint8_t v___x_2877_; 
v_quotient_2870_ = lean_uint64_shift_right(v___y_2852_, v___x_2862_);
v___x_2871_ = 1ULL;
v___x_2872_ = lean_uint64_shift_left(v___x_2871_, v___x_2862_);
v___x_2873_ = lean_uint64_sub(v___x_2872_, v___x_2871_);
v_remainder_2874_ = lean_uint64_land(v___y_2852_, v___x_2873_);
v___x_2875_ = lean_uint64_sub(v___x_2862_, v___x_2871_);
v_half_2876_ = lean_uint64_shift_left(v___x_2871_, v___x_2875_);
v___x_2877_ = lean_uint64_dec_lt(v_remainder_2874_, v_half_2876_);
if (v___x_2877_ == 0)
{
uint8_t v___x_2878_; 
v___x_2878_ = lean_uint64_dec_lt(v_half_2876_, v_remainder_2874_);
if (v___x_2878_ == 0)
{
uint64_t v___x_2879_; uint8_t v___x_2880_; 
v___x_2879_ = lean_uint64_land(v_quotient_2870_, v___x_2871_);
v___x_2880_ = lean_uint64_dec_eq(v___x_2879_, v___y_2854_);
if (v___x_2880_ == 0)
{
uint64_t v___x_2881_; 
v___x_2881_ = lean_uint64_add(v_quotient_2870_, v___x_2871_);
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v___x_2881_;
goto v___jp_2840_;
}
else
{
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v_quotient_2870_;
goto v___jp_2840_;
}
}
else
{
uint64_t v___x_2882_; 
v___x_2882_ = lean_uint64_add(v_quotient_2870_, v___x_2871_);
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v___x_2882_;
goto v___jp_2840_;
}
}
else
{
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v_quotient_2870_;
goto v___jp_2840_;
}
}
}
else
{
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v___y_2852_;
goto v___jp_2840_;
}
}
else
{
uint64_t v___x_2883_; uint64_t v___x_2884_; 
v___x_2883_ = lean_uint64_sub(v___x_2860_, v___y_2856_);
v___x_2884_ = lean_uint64_shift_left(v___y_2852_, v___x_2883_);
v___y_2841_ = v_position_2857_;
v___y_2842_ = v___y_2851_;
v___y_2843_ = v___y_2854_;
v___y_2844_ = v___y_2855_;
v___y_2845_ = v___x_2884_;
goto v___jp_2840_;
}
}
else
{
uint64_t v___x_2885_; uint8_t v___x_2886_; 
v___x_2885_ = 149ULL;
v___x_2886_ = lean_uint64_dec_lt(v___y_2853_, v___x_2885_);
if (v___x_2886_ == 0)
{
uint64_t v___x_2887_; uint64_t v___x_2888_; 
v___x_2887_ = lean_uint64_sub(v___y_2853_, v___x_2885_);
v___x_2888_ = lean_uint64_shift_left(v___y_2852_, v___x_2887_);
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v___x_2888_;
goto v___jp_2060_;
}
else
{
uint64_t v___x_2889_; uint8_t v___x_2890_; 
v___x_2889_ = lean_uint64_sub(v___x_2885_, v___y_2853_);
v___x_2890_ = lean_uint64_dec_eq(v___x_2889_, v___y_2854_);
if (v___x_2890_ == 0)
{
uint64_t v___x_2891_; uint8_t v___x_2892_; 
v___x_2891_ = 64ULL;
v___x_2892_ = lean_uint64_dec_lt(v___x_2889_, v___x_2891_);
if (v___x_2892_ == 0)
{
uint8_t v___x_2893_; 
v___x_2893_ = lean_uint64_dec_eq(v___x_2889_, v___x_2891_);
if (v___x_2893_ == 0)
{
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v___y_2854_;
goto v___jp_2060_;
}
else
{
uint64_t v___x_2894_; uint8_t v___x_2895_; 
v___x_2894_ = 9223372036854775808ULL;
v___x_2895_ = lean_uint64_dec_lt(v___x_2894_, v___y_2852_);
if (v___x_2895_ == 0)
{
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v___y_2854_;
goto v___jp_2060_;
}
else
{
uint64_t v___x_2896_; 
v___x_2896_ = 1ULL;
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v___x_2896_;
goto v___jp_2060_;
}
}
}
else
{
uint64_t v_quotient_2897_; uint64_t v___x_2898_; uint64_t v___x_2899_; uint64_t v___x_2900_; uint64_t v_remainder_2901_; uint64_t v___x_2902_; uint64_t v_half_2903_; uint8_t v___x_2904_; 
v_quotient_2897_ = lean_uint64_shift_right(v___y_2852_, v___x_2889_);
v___x_2898_ = 1ULL;
v___x_2899_ = lean_uint64_shift_left(v___x_2898_, v___x_2889_);
v___x_2900_ = lean_uint64_sub(v___x_2899_, v___x_2898_);
v_remainder_2901_ = lean_uint64_land(v___y_2852_, v___x_2900_);
v___x_2902_ = lean_uint64_sub(v___x_2889_, v___x_2898_);
v_half_2903_ = lean_uint64_shift_left(v___x_2898_, v___x_2902_);
v___x_2904_ = lean_uint64_dec_lt(v_remainder_2901_, v_half_2903_);
if (v___x_2904_ == 0)
{
uint8_t v___x_2905_; 
v___x_2905_ = lean_uint64_dec_lt(v_half_2903_, v_remainder_2901_);
if (v___x_2905_ == 0)
{
uint64_t v___x_2906_; uint8_t v___x_2907_; 
v___x_2906_ = lean_uint64_land(v_quotient_2897_, v___x_2898_);
v___x_2907_ = lean_uint64_dec_eq(v___x_2906_, v___y_2854_);
if (v___x_2907_ == 0)
{
uint64_t v___x_2908_; 
v___x_2908_ = lean_uint64_add(v_quotient_2897_, v___x_2898_);
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v___x_2908_;
goto v___jp_2060_;
}
else
{
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v_quotient_2897_;
goto v___jp_2060_;
}
}
else
{
uint64_t v___x_2909_; 
v___x_2909_ = lean_uint64_add(v_quotient_2897_, v___x_2898_);
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v___x_2909_;
goto v___jp_2060_;
}
}
else
{
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v_quotient_2897_;
goto v___jp_2060_;
}
}
}
else
{
v___y_2061_ = v___y_2851_;
v___y_2062_ = v___y_2854_;
v___y_2063_ = v___y_2855_;
v___y_2064_ = v___y_2852_;
goto v___jp_2060_;
}
}
}
}
v___jp_2910_:
{
uint64_t v___x_2918_; uint64_t v___x_2919_; uint8_t v___x_2920_; 
v___x_2918_ = 1ULL;
v___x_2919_ = lean_uint64_shift_right(v___y_2911_, v___x_2918_);
v___x_2920_ = lean_uint64_dec_eq(v___x_2919_, v___y_2915_);
if (v___x_2920_ == 0)
{
uint64_t v___x_2921_; 
v___x_2921_ = lean_uint64_add(v___y_2917_, v___x_2918_);
v___y_2851_ = v___y_2912_;
v___y_2852_ = v___y_2913_;
v___y_2853_ = v___y_2914_;
v___y_2854_ = v___y_2915_;
v___y_2855_ = v___y_2916_;
v___y_2856_ = v___x_2921_;
goto v___jp_2850_;
}
else
{
v___y_2851_ = v___y_2912_;
v___y_2852_ = v___y_2913_;
v___y_2853_ = v___y_2914_;
v___y_2854_ = v___y_2915_;
v___y_2855_ = v___y_2916_;
v___y_2856_ = v___y_2917_;
goto v___jp_2850_;
}
}
v___jp_2922_:
{
uint64_t v___x_2932_; uint8_t v___x_2933_; 
v___x_2932_ = lean_uint64_shift_right(v___y_2923_, v___y_2924_);
v___x_2933_ = lean_uint64_dec_eq(v___x_2932_, v___y_2929_);
if (v___x_2933_ == 0)
{
uint64_t v___x_2934_; 
v___x_2934_ = lean_uint64_add(v___y_2925_, v___y_2924_);
v___y_2911_ = v___y_2931_;
v___y_2912_ = v___y_2926_;
v___y_2913_ = v___y_2927_;
v___y_2914_ = v___y_2928_;
v___y_2915_ = v___y_2929_;
v___y_2916_ = v___y_2930_;
v___y_2917_ = v___x_2934_;
goto v___jp_2910_;
}
else
{
v___y_2911_ = v___y_2931_;
v___y_2912_ = v___y_2926_;
v___y_2913_ = v___y_2927_;
v___y_2914_ = v___y_2928_;
v___y_2915_ = v___y_2929_;
v___y_2916_ = v___y_2930_;
v___y_2917_ = v___y_2925_;
goto v___jp_2910_;
}
}
v___jp_2935_:
{
uint64_t v___x_2943_; uint64_t v___x_2944_; uint8_t v___x_2945_; 
v___x_2943_ = 2ULL;
v___x_2944_ = lean_uint64_shift_right(v___y_2936_, v___x_2943_);
v___x_2945_ = lean_uint64_dec_eq(v___x_2944_, v___y_2940_);
if (v___x_2945_ == 0)
{
v___y_2923_ = v___y_2936_;
v___y_2924_ = v___x_2943_;
v___y_2925_ = v___y_2942_;
v___y_2926_ = v___y_2937_;
v___y_2927_ = v___y_2938_;
v___y_2928_ = v___y_2939_;
v___y_2929_ = v___y_2940_;
v___y_2930_ = v___y_2941_;
v___y_2931_ = v___x_2944_;
goto v___jp_2922_;
}
else
{
v___y_2923_ = v___y_2936_;
v___y_2924_ = v___x_2943_;
v___y_2925_ = v___y_2942_;
v___y_2926_ = v___y_2937_;
v___y_2927_ = v___y_2938_;
v___y_2928_ = v___y_2939_;
v___y_2929_ = v___y_2940_;
v___y_2930_ = v___y_2941_;
v___y_2931_ = v___y_2936_;
goto v___jp_2922_;
}
}
v___jp_2946_:
{
uint64_t v___x_2956_; uint8_t v___x_2957_; 
v___x_2956_ = lean_uint64_shift_right(v___y_2949_, v___y_2948_);
v___x_2957_ = lean_uint64_dec_eq(v___x_2956_, v___y_2953_);
if (v___x_2957_ == 0)
{
uint64_t v___x_2958_; 
v___x_2958_ = lean_uint64_add(v___y_2947_, v___y_2948_);
v___y_2936_ = v___y_2955_;
v___y_2937_ = v___y_2950_;
v___y_2938_ = v___y_2951_;
v___y_2939_ = v___y_2952_;
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___y_2954_;
v___y_2942_ = v___x_2958_;
goto v___jp_2935_;
}
else
{
v___y_2936_ = v___y_2955_;
v___y_2937_ = v___y_2950_;
v___y_2938_ = v___y_2951_;
v___y_2939_ = v___y_2952_;
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___y_2954_;
v___y_2942_ = v___y_2947_;
goto v___jp_2935_;
}
}
v___jp_2959_:
{
uint64_t v___x_2967_; uint64_t v___x_2968_; uint8_t v___x_2969_; 
v___x_2967_ = 4ULL;
v___x_2968_ = lean_uint64_shift_right(v___y_2960_, v___x_2967_);
v___x_2969_ = lean_uint64_dec_eq(v___x_2968_, v___y_2964_);
if (v___x_2969_ == 0)
{
v___y_2947_ = v___y_2966_;
v___y_2948_ = v___x_2967_;
v___y_2949_ = v___y_2960_;
v___y_2950_ = v___y_2961_;
v___y_2951_ = v___y_2962_;
v___y_2952_ = v___y_2963_;
v___y_2953_ = v___y_2964_;
v___y_2954_ = v___y_2965_;
v___y_2955_ = v___x_2968_;
goto v___jp_2946_;
}
else
{
v___y_2947_ = v___y_2966_;
v___y_2948_ = v___x_2967_;
v___y_2949_ = v___y_2960_;
v___y_2950_ = v___y_2961_;
v___y_2951_ = v___y_2962_;
v___y_2952_ = v___y_2963_;
v___y_2953_ = v___y_2964_;
v___y_2954_ = v___y_2965_;
v___y_2955_ = v___y_2960_;
goto v___jp_2946_;
}
}
v___jp_2970_:
{
uint64_t v___x_2980_; uint8_t v___x_2981_; 
v___x_2980_ = lean_uint64_shift_right(v___y_2973_, v___y_2971_);
v___x_2981_ = lean_uint64_dec_eq(v___x_2980_, v___y_2977_);
if (v___x_2981_ == 0)
{
uint64_t v___x_2982_; 
v___x_2982_ = lean_uint64_add(v___y_2972_, v___y_2971_);
v___y_2960_ = v___y_2979_;
v___y_2961_ = v___y_2974_;
v___y_2962_ = v___y_2975_;
v___y_2963_ = v___y_2976_;
v___y_2964_ = v___y_2977_;
v___y_2965_ = v___y_2978_;
v___y_2966_ = v___x_2982_;
goto v___jp_2959_;
}
else
{
v___y_2960_ = v___y_2979_;
v___y_2961_ = v___y_2974_;
v___y_2962_ = v___y_2975_;
v___y_2963_ = v___y_2976_;
v___y_2964_ = v___y_2977_;
v___y_2965_ = v___y_2978_;
v___y_2966_ = v___y_2972_;
goto v___jp_2959_;
}
}
v___jp_2983_:
{
uint64_t v___x_2991_; uint64_t v___x_2992_; uint8_t v___x_2993_; 
v___x_2991_ = 8ULL;
v___x_2992_ = lean_uint64_shift_right(v___y_2984_, v___x_2991_);
v___x_2993_ = lean_uint64_dec_eq(v___x_2992_, v___y_2988_);
if (v___x_2993_ == 0)
{
v___y_2971_ = v___x_2991_;
v___y_2972_ = v___y_2990_;
v___y_2973_ = v___y_2984_;
v___y_2974_ = v___y_2985_;
v___y_2975_ = v___y_2986_;
v___y_2976_ = v___y_2987_;
v___y_2977_ = v___y_2988_;
v___y_2978_ = v___y_2989_;
v___y_2979_ = v___x_2992_;
goto v___jp_2970_;
}
else
{
v___y_2971_ = v___x_2991_;
v___y_2972_ = v___y_2990_;
v___y_2973_ = v___y_2984_;
v___y_2974_ = v___y_2985_;
v___y_2975_ = v___y_2986_;
v___y_2976_ = v___y_2987_;
v___y_2977_ = v___y_2988_;
v___y_2978_ = v___y_2989_;
v___y_2979_ = v___y_2984_;
goto v___jp_2970_;
}
}
v___jp_2994_:
{
uint64_t v___x_3004_; uint8_t v___x_3005_; 
v___x_3004_ = lean_uint64_shift_right(v___y_2996_, v___y_2995_);
v___x_3005_ = lean_uint64_dec_eq(v___x_3004_, v___y_3001_);
if (v___x_3005_ == 0)
{
uint64_t v___x_3006_; 
v___x_3006_ = lean_uint64_add(v___y_2997_, v___y_2995_);
v___y_2984_ = v___y_3003_;
v___y_2985_ = v___y_2998_;
v___y_2986_ = v___y_2999_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___y_3002_;
v___y_2990_ = v___x_3006_;
goto v___jp_2983_;
}
else
{
v___y_2984_ = v___y_3003_;
v___y_2985_ = v___y_2998_;
v___y_2986_ = v___y_2999_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___y_3002_;
v___y_2990_ = v___y_2997_;
goto v___jp_2983_;
}
}
v___jp_3007_:
{
uint64_t v___x_3015_; uint64_t v___x_3016_; uint8_t v___x_3017_; 
v___x_3015_ = 16ULL;
v___x_3016_ = lean_uint64_shift_right(v___y_3008_, v___x_3015_);
v___x_3017_ = lean_uint64_dec_eq(v___x_3016_, v___y_3012_);
if (v___x_3017_ == 0)
{
v___y_2995_ = v___x_3015_;
v___y_2996_ = v___y_3008_;
v___y_2997_ = v___y_3014_;
v___y_2998_ = v___y_3009_;
v___y_2999_ = v___y_3010_;
v___y_3000_ = v___y_3011_;
v___y_3001_ = v___y_3012_;
v___y_3002_ = v___y_3013_;
v___y_3003_ = v___x_3016_;
goto v___jp_2994_;
}
else
{
v___y_2995_ = v___x_3015_;
v___y_2996_ = v___y_3008_;
v___y_2997_ = v___y_3014_;
v___y_2998_ = v___y_3009_;
v___y_2999_ = v___y_3010_;
v___y_3000_ = v___y_3011_;
v___y_3001_ = v___y_3012_;
v___y_3002_ = v___y_3013_;
v___y_3003_ = v___y_3008_;
goto v___jp_2994_;
}
}
v___jp_3018_:
{
uint64_t v___x_3026_; uint8_t v___x_3027_; 
v___x_3026_ = lean_uint64_shift_right(v___y_3021_, v___y_3019_);
v___x_3027_ = lean_uint64_dec_eq(v___x_3026_, v___y_3023_);
if (v___x_3027_ == 0)
{
v___y_3008_ = v___y_3025_;
v___y_3009_ = v___y_3020_;
v___y_3010_ = v___y_3021_;
v___y_3011_ = v___y_3022_;
v___y_3012_ = v___y_3023_;
v___y_3013_ = v___y_3024_;
v___y_3014_ = v___y_3019_;
goto v___jp_3007_;
}
else
{
v___y_3008_ = v___y_3025_;
v___y_3009_ = v___y_3020_;
v___y_3010_ = v___y_3021_;
v___y_3011_ = v___y_3022_;
v___y_3012_ = v___y_3023_;
v___y_3013_ = v___y_3024_;
v___y_3014_ = v___y_3023_;
goto v___jp_3007_;
}
}
v___jp_3028_:
{
uint64_t v___x_3033_; uint8_t v___x_3034_; 
v___x_3033_ = 0ULL;
v___x_3034_ = lean_uint64_dec_eq(v___y_3030_, v___x_3033_);
if (v___x_3034_ == 0)
{
uint64_t v___x_3035_; uint64_t v___x_3036_; uint8_t v___x_3037_; 
v___x_3035_ = 32ULL;
v___x_3036_ = lean_uint64_shift_right(v___y_3030_, v___x_3035_);
v___x_3037_ = lean_uint64_dec_eq(v___x_3036_, v___x_3033_);
if (v___x_3037_ == 0)
{
v___y_3019_ = v___x_3035_;
v___y_3020_ = v___y_3029_;
v___y_3021_ = v___y_3030_;
v___y_3022_ = v___y_3031_;
v___y_3023_ = v___x_3033_;
v___y_3024_ = v___y_3032_;
v___y_3025_ = v___x_3036_;
goto v___jp_3018_;
}
else
{
v___y_3019_ = v___x_3035_;
v___y_3020_ = v___y_3029_;
v___y_3021_ = v___y_3030_;
v___y_3022_ = v___y_3031_;
v___y_3023_ = v___x_3033_;
v___y_3024_ = v___y_3032_;
v___y_3025_ = v___y_3030_;
goto v___jp_3018_;
}
}
else
{
if (v___y_3032_ == 0)
{
uint32_t v___x_3038_; 
v___x_3038_ = 0;
return v___x_3038_;
}
else
{
uint32_t v___x_3039_; 
v___x_3039_ = 2147483648;
return v___x_3039_;
}
}
}
v___jp_3040_:
{
uint64_t v___x_3047_; uint64_t v___x_3048_; uint64_t v___x_3049_; uint8_t v___x_3050_; 
v___x_3047_ = lean_uint64_mul(v___y_3044_, v___y_3041_);
v___x_3048_ = lean_uint64_add(v___y_3042_, v___y_3046_);
v___x_3049_ = 281474976710656ULL;
v___x_3050_ = lean_uint64_dec_lt(v___x_3047_, v___x_3049_);
if (v___x_3050_ == 0)
{
v___y_3029_ = v___y_3043_;
v___y_3030_ = v___x_3047_;
v___y_3031_ = v___x_3048_;
v___y_3032_ = v___y_3045_;
goto v___jp_3028_;
}
else
{
uint64_t v___x_3051_; uint8_t v___x_3052_; 
v___x_3051_ = 123ULL;
v___x_3052_ = lean_uint64_dec_le(v___x_3048_, v___x_3051_);
if (v___x_3052_ == 0)
{
v___y_3029_ = v___y_3043_;
v___y_3030_ = v___x_3047_;
v___y_3031_ = v___x_3048_;
v___y_3032_ = v___y_3045_;
goto v___jp_3028_;
}
else
{
uint64_t v___x_3053_; uint8_t v___x_3054_; 
v___x_3053_ = 0ULL;
v___x_3054_ = lean_uint64_dec_eq(v___x_3047_, v___x_3053_);
if (v___x_3054_ == 0)
{
uint64_t v___x_3055_; uint64_t v___x_3056_; uint8_t v___x_3057_; 
v___x_3055_ = 149ULL;
v___x_3056_ = lean_uint64_sub(v___x_3055_, v___x_3048_);
v___x_3057_ = lean_uint64_dec_eq(v___x_3056_, v___x_3053_);
if (v___x_3057_ == 0)
{
uint64_t v___x_3058_; uint8_t v___x_3059_; 
v___x_3058_ = 64ULL;
v___x_3059_ = lean_uint64_dec_lt(v___x_3056_, v___x_3058_);
if (v___x_3059_ == 0)
{
uint8_t v___x_3060_; 
v___x_3060_ = lean_uint64_dec_eq(v___x_3056_, v___x_3058_);
if (v___x_3060_ == 0)
{
v___y_2082_ = v___y_3043_;
v___y_2083_ = v___y_3045_;
v___y_2084_ = v___x_3053_;
v___y_2085_ = v___x_3053_;
goto v___jp_2081_;
}
else
{
uint64_t v___x_3061_; uint8_t v___x_3062_; 
v___x_3061_ = 9223372036854775808ULL;
v___x_3062_ = lean_uint64_dec_lt(v___x_3061_, v___x_3047_);
if (v___x_3062_ == 0)
{
v___y_2082_ = v___y_3043_;
v___y_2083_ = v___y_3045_;
v___y_2084_ = v___x_3053_;
v___y_2085_ = v___x_3053_;
goto v___jp_2081_;
}
else
{
uint64_t v___x_3063_; 
v___x_3063_ = 1ULL;
v___y_2082_ = v___y_3043_;
v___y_2083_ = v___y_3045_;
v___y_2084_ = v___x_3053_;
v___y_2085_ = v___x_3063_;
goto v___jp_2081_;
}
}
}
else
{
uint64_t v_quotient_3064_; uint64_t v___x_3065_; uint64_t v___x_3066_; uint64_t v___x_3067_; uint64_t v_remainder_3068_; uint64_t v___x_3069_; uint64_t v_half_3070_; uint8_t v___x_3071_; 
v_quotient_3064_ = lean_uint64_shift_right(v___x_3047_, v___x_3056_);
v___x_3065_ = 1ULL;
v___x_3066_ = lean_uint64_shift_left(v___x_3065_, v___x_3056_);
v___x_3067_ = lean_uint64_sub(v___x_3066_, v___x_3065_);
v_remainder_3068_ = lean_uint64_land(v___x_3047_, v___x_3067_);
v___x_3069_ = lean_uint64_sub(v___x_3056_, v___x_3065_);
v_half_3070_ = lean_uint64_shift_left(v___x_3065_, v___x_3069_);
v___x_3071_ = lean_uint64_dec_lt(v_remainder_3068_, v_half_3070_);
if (v___x_3071_ == 0)
{
uint8_t v___x_3072_; 
v___x_3072_ = lean_uint64_dec_lt(v_half_3070_, v_remainder_3068_);
if (v___x_3072_ == 0)
{
uint64_t v___x_3073_; uint8_t v___x_3074_; 
v___x_3073_ = lean_uint64_land(v_quotient_3064_, v___x_3065_);
v___x_3074_ = lean_uint64_dec_eq(v___x_3073_, v___x_3053_);
if (v___x_3074_ == 0)
{
uint64_t v___x_3075_; 
v___x_3075_ = lean_uint64_add(v_quotient_3064_, v___x_3065_);
v___y_2082_ = v___y_3043_;
v___y_2083_ = v___y_3045_;
v___y_2084_ = v___x_3053_;
v___y_2085_ = v___x_3075_;
goto v___jp_2081_;
}
else
{
v___y_2082_ = v___y_3043_;
v___y_2083_ = v___y_3045_;
v___y_2084_ = v___x_3053_;
v___y_2085_ = v_quotient_3064_;
goto v___jp_2081_;
}
}
else
{
uint64_t v___x_3076_; 
v___x_3076_ = lean_uint64_add(v_quotient_3064_, v___x_3065_);
v___y_2082_ = v___y_3043_;
v___y_2083_ = v___y_3045_;
v___y_2084_ = v___x_3053_;
v___y_2085_ = v___x_3076_;
goto v___jp_2081_;
}
}
else
{
v___y_2082_ = v___y_3043_;
v___y_2083_ = v___y_3045_;
v___y_2084_ = v___x_3053_;
v___y_2085_ = v_quotient_3064_;
goto v___jp_2081_;
}
}
}
else
{
v___y_2082_ = v___y_3043_;
v___y_2083_ = v___y_3045_;
v___y_2084_ = v___x_3053_;
v___y_2085_ = v___x_3047_;
goto v___jp_2081_;
}
}
else
{
if (v___y_3045_ == 0)
{
uint32_t v___x_3077_; 
v___x_3077_ = 0;
return v___x_3077_;
}
else
{
uint32_t v___x_3078_; 
v___x_3078_ = 2147483648;
return v___x_3078_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_3372_, lean_object* v___y_3373_){
_start:
{
uint32_t v___y_14241__boxed_3374_; uint32_t v___y_14242__boxed_3375_; uint32_t v_res_3376_; lean_object* v_r_3377_; 
v___y_14241__boxed_3374_ = lean_unbox_uint32(v___y_3372_);
lean_dec(v___y_3372_);
v___y_14242__boxed_3375_ = lean_unbox_uint32(v___y_3373_);
lean_dec(v___y_3373_);
v_res_3376_ = lp_competition_main___lam__3(v___y_14241__boxed_3374_, v___y_14242__boxed_3375_);
v_r_3377_ = lean_box_uint32(v_res_3376_);
return v_r_3377_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_3385_; lean_object* v___x_3386_; 
v___x_3385_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_3386_ = lean_io_getenv(v___x_3385_);
if (lean_obj_tag(v___x_3386_) == 0)
{
lean_object* v___f_3387_; lean_object* v___f_3388_; lean_object* v___f_3389_; lean_object* v___f_3390_; lean_object* v___x_3391_; 
v___f_3387_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_3388_ = ((lean_object*)(lp_competition_main___closed__2));
v___f_3389_ = ((lean_object*)(lp_competition_main___closed__3));
v___f_3390_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_3391_ = lp_competition_Bench_runFull(v___f_3387_, v___f_3388_, v___f_3389_, v___f_3390_);
return v___x_3391_;
}
else
{
lean_object* v___f_3392_; lean_object* v___f_3393_; lean_object* v___f_3394_; lean_object* v___f_3395_; lean_object* v___x_3396_; 
lean_dec_ref_known(v___x_3386_, 1);
v___f_3392_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_3393_ = ((lean_object*)(lp_competition_main___closed__5));
v___f_3394_ = ((lean_object*)(lp_competition_main___closed__3));
v___f_3395_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_3396_ = lp_competition_Bench_Suite_run(v___f_3392_, v___f_3393_, v___f_3394_, v___f_3395_);
return v___x_3396_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_3397_){
_start:
{
lean_object* v_res_3398_; 
v_res_3398_ = _lean_main();
return v_res_3398_;
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
