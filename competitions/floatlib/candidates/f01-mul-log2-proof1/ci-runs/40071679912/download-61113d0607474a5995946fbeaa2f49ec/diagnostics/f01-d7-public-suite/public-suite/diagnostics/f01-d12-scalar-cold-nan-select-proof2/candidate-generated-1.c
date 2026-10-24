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
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
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
uint32_t v___y_4273__boxed_126_; uint32_t v___y_4274__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_4273__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_4274__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_main___lam__0(v___y_4273__boxed_126_, v___y_4274__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_130_, uint32_t v___y_131_){
_start:
{
uint32_t v___y_133_; uint32_t v___y_134_; uint32_t v___y_135_; uint32_t v___y_139_; uint32_t v___y_140_; uint32_t v___y_141_; uint32_t v___y_145_; uint8_t v___y_149_; uint32_t v___y_150_; uint64_t v___y_151_; uint64_t v___y_152_; uint32_t v___y_164_; uint8_t v___y_168_; uint32_t v___y_169_; uint64_t v___y_170_; uint64_t v___y_171_; uint8_t v___y_183_; uint32_t v___x_187_; uint32_t v___x_188_; uint32_t v___x_189_; uint32_t v___y_191_; uint32_t v___y_192_; uint32_t v___y_193_; uint32_t v___y_194_; uint8_t v___y_201_; uint32_t v___y_202_; uint32_t v___y_203_; uint32_t v___y_204_; uint8_t v___y_208_; uint32_t v___y_209_; uint64_t v___y_210_; uint64_t v___y_211_; uint64_t v___y_212_; uint8_t v___y_222_; uint8_t v___y_223_; uint32_t v___y_224_; uint64_t v___y_225_; uint64_t v___y_226_; uint64_t v___y_227_; uint8_t v___y_234_; uint32_t v___y_235_; uint64_t v___y_236_; uint64_t v___y_237_; uint64_t v___y_238_; uint8_t v___y_244_; uint32_t v___y_245_; uint64_t v___y_246_; uint64_t v___y_247_; uint64_t v___y_248_; uint64_t v___y_249_; uint8_t v___y_304_; uint32_t v___y_305_; uint64_t v___y_306_; uint64_t v___y_307_; uint64_t v___y_308_; uint64_t v___y_309_; uint64_t v___y_310_; uint8_t v___y_316_; uint64_t v___y_317_; uint32_t v___y_318_; uint64_t v___y_319_; uint64_t v___y_320_; uint64_t v___y_321_; uint64_t v___y_322_; uint64_t v___y_323_; uint64_t v___y_324_; uint8_t v___y_329_; uint32_t v___y_330_; uint64_t v___y_331_; uint64_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint64_t v___y_335_; uint8_t v___y_340_; uint64_t v___y_341_; uint64_t v___y_342_; uint32_t v___y_343_; uint64_t v___y_344_; uint64_t v___y_345_; uint64_t v___y_346_; uint64_t v___y_347_; uint64_t v___y_348_; uint8_t v___y_353_; uint64_t v___y_354_; uint32_t v___y_355_; uint64_t v___y_356_; uint64_t v___y_357_; uint64_t v___y_358_; uint64_t v___y_359_; uint64_t v___y_364_; uint64_t v___y_365_; uint8_t v___y_366_; uint64_t v___y_367_; uint32_t v___y_368_; uint64_t v___y_369_; uint64_t v___y_370_; uint64_t v___y_371_; uint64_t v___y_372_; uint8_t v___y_377_; uint64_t v___y_378_; uint32_t v___y_379_; uint64_t v___y_380_; uint64_t v___y_381_; uint64_t v___y_382_; uint64_t v___y_383_; uint64_t v___y_388_; uint8_t v___y_389_; uint64_t v___y_390_; uint32_t v___y_391_; uint64_t v___y_392_; uint64_t v___y_393_; uint64_t v___y_394_; uint64_t v___y_395_; uint64_t v___y_396_; uint8_t v___y_401_; uint32_t v___y_402_; uint64_t v___y_403_; uint64_t v___y_404_; uint64_t v___y_405_; uint64_t v___y_406_; uint64_t v___y_407_; uint8_t v___y_412_; uint64_t v___y_413_; uint32_t v___y_414_; uint64_t v___y_415_; uint64_t v___y_416_; uint64_t v___y_417_; uint64_t v___y_418_; uint8_t v___y_422_; uint32_t v___y_423_; uint64_t v___y_424_; uint64_t v___y_425_; uint64_t v___y_434_; uint8_t v___y_435_; uint32_t v___y_436_; uint64_t v___y_437_; uint64_t v___y_438_; uint64_t v___y_439_; uint32_t v_ex_472_; uint32_t v___x_473_; uint32_t v_ey_474_; uint8_t v___y_483_; uint8_t v___y_493_; uint8_t v___y_506_; uint64_t v___y_513_; uint8_t v___y_514_; uint32_t v___y_515_; uint64_t v___y_516_; uint64_t v___y_517_; uint64_t v___y_524_; uint8_t v___y_525_; uint32_t v___y_526_; uint64_t v___y_527_; uint8_t v___y_534_; uint32_t v___y_535_; uint32_t v___y_536_; uint64_t v___y_537_; uint8_t v___y_545_; uint32_t v___x_555_; uint32_t v___x_556_; uint8_t v___x_557_; uint8_t v___y_559_; uint8_t v___y_560_; uint8_t v___y_562_; uint8_t v___y_563_; uint8_t v___y_564_; uint8_t v___y_566_; uint8_t v___y_567_; uint8_t v___y_573_; 
v___x_187_ = 23;
v___x_188_ = lean_uint32_shift_right(v___y_130_, v___x_187_);
v___x_189_ = 255;
v_ex_472_ = lean_uint32_land(v___x_188_, v___x_189_);
v___x_473_ = lean_uint32_shift_right(v___y_131_, v___x_187_);
v_ey_474_ = lean_uint32_land(v___x_473_, v___x_189_);
v___x_555_ = lean_uint32_add(v_ex_472_, v_ey_474_);
v___x_556_ = 128;
v___x_557_ = lean_uint32_dec_lt(v___x_555_, v___x_556_);
if (v___x_557_ == 0)
{
float v___x_582_; float v___x_583_; float v_result_584_; uint8_t v___x_585_; 
v___x_582_ = lean_float32_of_bits(v___y_130_);
v___x_583_ = lean_float32_of_bits(v___y_131_);
v_result_584_ = lean_float32_mul(v___x_582_, v___x_583_);
v___x_585_ = lean_float32_beq(v_result_584_, v_result_584_);
if (v___x_585_ == 0)
{
uint8_t v___x_586_; 
v___x_586_ = lean_uint32_dec_eq(v_ex_472_, v___x_189_);
if (v___x_586_ == 0)
{
v___y_506_ = v___x_586_;
goto v___jp_505_;
}
else
{
uint32_t v___x_587_; uint32_t v___x_588_; uint32_t v___x_589_; uint8_t v___x_590_; 
v___x_587_ = 8388607;
v___x_588_ = lean_uint32_land(v___y_130_, v___x_587_);
v___x_589_ = 0;
v___x_590_ = lean_uint32_dec_eq(v___x_588_, v___x_589_);
if (v___x_590_ == 0)
{
v___y_506_ = v___x_586_;
goto v___jp_505_;
}
else
{
goto v___jp_499_;
}
}
}
else
{
uint32_t v___x_591_; 
v___x_591_ = lean_float32_to_bits(v_result_584_);
return v___x_591_;
}
}
else
{
uint32_t v___x_592_; uint32_t v___x_593_; uint32_t v___x_594_; uint8_t v___x_595_; 
v___x_592_ = 4278190080;
v___x_593_ = 1;
v___x_594_ = lean_uint32_shift_left(v___y_130_, v___x_593_);
v___x_595_ = lean_uint32_dec_le(v___x_592_, v___x_594_);
if (v___x_595_ == 0)
{
uint32_t v___x_596_; uint8_t v___x_597_; 
v___x_596_ = lean_uint32_shift_left(v___y_131_, v___x_593_);
v___x_597_ = lean_uint32_dec_le(v___x_592_, v___x_596_);
v___y_573_ = v___x_597_;
goto v___jp_572_;
}
else
{
v___y_573_ = v___x_595_;
goto v___jp_572_;
}
}
v___jp_132_:
{
uint32_t v___x_136_; uint32_t v___x_137_; 
v___x_136_ = lean_uint32_land(v___y_134_, v___y_133_);
v___x_137_ = lean_uint32_lor(v___y_135_, v___x_136_);
return v___x_137_;
}
v___jp_138_:
{
uint32_t v___x_142_; uint32_t v___x_143_; 
v___x_142_ = lean_uint32_land(v___y_140_, v___y_139_);
v___x_143_ = lean_uint32_lor(v___y_141_, v___x_142_);
return v___x_143_;
}
v___jp_144_:
{
uint32_t v___x_146_; uint32_t v___x_147_; 
v___x_146_ = 8388608;
v___x_147_ = lean_uint32_lor(v___y_145_, v___x_146_);
return v___x_147_;
}
v___jp_148_:
{
uint8_t v___x_153_; 
v___x_153_ = lean_uint64_dec_eq(v___y_152_, v___y_151_);
if (v___x_153_ == 0)
{
uint64_t v___x_154_; uint8_t v___x_155_; 
v___x_154_ = 8388608ULL;
v___x_155_ = lean_uint64_dec_eq(v___y_152_, v___x_154_);
if (v___x_155_ == 0)
{
uint32_t v___x_156_; 
v___x_156_ = lean_uint64_to_uint32(v___y_152_);
if (v___y_149_ == 0)
{
uint32_t v___x_157_; 
v___x_157_ = 0;
v___y_139_ = v___y_150_;
v___y_140_ = v___x_156_;
v___y_141_ = v___x_157_;
goto v___jp_138_;
}
else
{
uint32_t v___x_158_; 
v___x_158_ = 2147483648;
v___y_139_ = v___y_150_;
v___y_140_ = v___x_156_;
v___y_141_ = v___x_158_;
goto v___jp_138_;
}
}
else
{
if (v___y_149_ == 0)
{
uint32_t v___x_159_; 
v___x_159_ = 0;
v___y_145_ = v___x_159_;
goto v___jp_144_;
}
else
{
uint32_t v___x_160_; 
v___x_160_ = 2147483648;
v___y_145_ = v___x_160_;
goto v___jp_144_;
}
}
}
else
{
if (v___y_149_ == 0)
{
uint32_t v___x_161_; 
v___x_161_ = 0;
return v___x_161_;
}
else
{
uint32_t v___x_162_; 
v___x_162_ = 2147483648;
return v___x_162_;
}
}
}
v___jp_163_:
{
uint32_t v___x_165_; uint32_t v___x_166_; 
v___x_165_ = 8388608;
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
v___y_133_ = v___y_169_;
v___y_134_ = v___x_175_;
v___y_135_ = v___x_176_;
goto v___jp_132_;
}
else
{
uint32_t v___x_177_; 
v___x_177_ = 2147483648;
v___y_133_ = v___y_169_;
v___y_134_ = v___x_175_;
v___y_135_ = v___x_177_;
goto v___jp_132_;
}
}
else
{
if (v___y_168_ == 0)
{
uint32_t v___x_178_; 
v___x_178_ = 0;
v___y_164_ = v___x_178_;
goto v___jp_163_;
}
else
{
uint32_t v___x_179_; 
v___x_179_ = 2147483648;
v___y_164_ = v___x_179_;
goto v___jp_163_;
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
v___jp_190_:
{
uint32_t v___x_195_; uint32_t v___x_196_; uint32_t v___x_197_; uint32_t v___x_198_; uint32_t v___x_199_; 
v___x_195_ = lean_uint32_land(v___y_192_, v___x_189_);
v___x_196_ = lean_uint32_shift_left(v___x_195_, v___x_187_);
v___x_197_ = lean_uint32_lor(v___y_194_, v___x_196_);
v___x_198_ = lean_uint32_land(v___y_191_, v___y_193_);
v___x_199_ = lean_uint32_lor(v___x_197_, v___x_198_);
return v___x_199_;
}
v___jp_200_:
{
if (v___y_201_ == 0)
{
uint32_t v___x_205_; 
v___x_205_ = 0;
v___y_191_ = v___y_204_;
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v___x_205_;
goto v___jp_190_;
}
else
{
uint32_t v___x_206_; 
v___x_206_ = 2147483648;
v___y_191_ = v___y_204_;
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v___x_206_;
goto v___jp_190_;
}
}
v___jp_207_:
{
uint64_t v___x_213_; uint64_t v_encodedExponent_214_; uint32_t v___x_215_; uint64_t v___x_216_; uint8_t v___x_217_; 
v___x_213_ = 171ULL;
v_encodedExponent_214_ = lean_uint64_sub(v___y_210_, v___x_213_);
v___x_215_ = lean_uint64_to_uint32(v_encodedExponent_214_);
v___x_216_ = 8388608ULL;
v___x_217_ = lean_uint64_dec_lt(v___y_212_, v___x_216_);
if (v___x_217_ == 0)
{
uint64_t v___x_218_; uint32_t v___x_219_; 
v___x_218_ = lean_uint64_sub(v___y_212_, v___x_216_);
v___x_219_ = lean_uint64_to_uint32(v___x_218_);
v___y_201_ = v___y_208_;
v___y_202_ = v___x_215_;
v___y_203_ = v___y_209_;
v___y_204_ = v___x_219_;
goto v___jp_200_;
}
else
{
uint32_t v___x_220_; 
v___x_220_ = lean_uint64_to_uint32(v___y_211_);
v___y_201_ = v___y_208_;
v___y_202_ = v___x_215_;
v___y_203_ = v___y_209_;
v___y_204_ = v___x_220_;
goto v___jp_200_;
}
}
v___jp_221_:
{
uint64_t v___x_228_; uint8_t v___x_229_; 
v___x_228_ = 425ULL;
v___x_229_ = lean_uint64_dec_lt(v___x_228_, v___y_227_);
if (v___x_229_ == 0)
{
if (v___y_223_ == 0)
{
v___y_208_ = v___y_222_;
v___y_209_ = v___y_224_;
v___y_210_ = v___y_227_;
v___y_211_ = v___y_226_;
v___y_212_ = v___y_225_;
goto v___jp_207_;
}
else
{
uint64_t v___x_230_; 
v___x_230_ = 8388608ULL;
v___y_208_ = v___y_222_;
v___y_209_ = v___y_224_;
v___y_210_ = v___y_227_;
v___y_211_ = v___y_226_;
v___y_212_ = v___x_230_;
goto v___jp_207_;
}
}
else
{
if (v___y_222_ == 0)
{
uint32_t v___x_231_; 
v___x_231_ = 2139095040;
return v___x_231_;
}
else
{
uint32_t v___x_232_; 
v___x_232_ = 4286578688;
return v___x_232_;
}
}
}
v___jp_233_:
{
uint64_t v___x_239_; uint8_t v_carry_240_; 
v___x_239_ = 16777216ULL;
v_carry_240_ = lean_uint64_dec_eq(v___y_238_, v___x_239_);
if (v_carry_240_ == 0)
{
v___y_222_ = v___y_234_;
v___y_223_ = v_carry_240_;
v___y_224_ = v___y_235_;
v___y_225_ = v___y_238_;
v___y_226_ = v___y_237_;
v___y_227_ = v___y_236_;
goto v___jp_221_;
}
else
{
uint64_t v___x_241_; uint64_t v___x_242_; 
v___x_241_ = 1ULL;
v___x_242_ = lean_uint64_add(v___y_236_, v___x_241_);
v___y_222_ = v___y_234_;
v___y_223_ = v_carry_240_;
v___y_224_ = v___y_235_;
v___y_225_ = v___y_238_;
v___y_226_ = v___y_237_;
v___y_227_ = v___x_242_;
goto v___jp_221_;
}
}
v___jp_243_:
{
uint64_t v_position_250_; uint64_t v___x_251_; uint8_t v___x_252_; 
v_position_250_ = lean_uint64_add(v___y_249_, v___y_247_);
v___x_251_ = 172ULL;
v___x_252_ = lean_uint64_dec_lt(v_position_250_, v___x_251_);
if (v___x_252_ == 0)
{
uint64_t v___x_253_; uint8_t v___x_254_; 
v___x_253_ = 23ULL;
v___x_254_ = lean_uint64_dec_lt(v___y_249_, v___x_253_);
if (v___x_254_ == 0)
{
uint64_t v___x_255_; uint8_t v___x_256_; 
v___x_255_ = lean_uint64_sub(v___y_249_, v___x_253_);
v___x_256_ = lean_uint64_dec_eq(v___x_255_, v___y_246_);
if (v___x_256_ == 0)
{
uint64_t v___x_257_; uint8_t v___x_258_; 
v___x_257_ = 64ULL;
v___x_258_ = lean_uint64_dec_lt(v___x_255_, v___x_257_);
if (v___x_258_ == 0)
{
uint8_t v___x_259_; 
v___x_259_ = lean_uint64_dec_eq(v___x_255_, v___x_257_);
if (v___x_259_ == 0)
{
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v___y_246_;
goto v___jp_233_;
}
else
{
uint64_t v___x_260_; uint8_t v___x_261_; 
v___x_260_ = 9223372036854775808ULL;
v___x_261_ = lean_uint64_dec_lt(v___x_260_, v___y_248_);
if (v___x_261_ == 0)
{
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v___y_246_;
goto v___jp_233_;
}
else
{
uint64_t v___x_262_; 
v___x_262_ = 1ULL;
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v___x_262_;
goto v___jp_233_;
}
}
}
else
{
uint64_t v_quotient_263_; uint64_t v___x_264_; uint64_t v___x_265_; uint64_t v___x_266_; uint64_t v_remainder_267_; uint64_t v___x_268_; uint64_t v_half_269_; uint8_t v___x_270_; 
v_quotient_263_ = lean_uint64_shift_right(v___y_248_, v___x_255_);
v___x_264_ = 1ULL;
v___x_265_ = lean_uint64_shift_left(v___x_264_, v___x_255_);
v___x_266_ = lean_uint64_sub(v___x_265_, v___x_264_);
v_remainder_267_ = lean_uint64_land(v___y_248_, v___x_266_);
v___x_268_ = lean_uint64_sub(v___x_255_, v___x_264_);
v_half_269_ = lean_uint64_shift_left(v___x_264_, v___x_268_);
v___x_270_ = lean_uint64_dec_lt(v_remainder_267_, v_half_269_);
if (v___x_270_ == 0)
{
uint8_t v___x_271_; 
v___x_271_ = lean_uint64_dec_lt(v_half_269_, v_remainder_267_);
if (v___x_271_ == 0)
{
uint64_t v___x_272_; uint8_t v___x_273_; 
v___x_272_ = lean_uint64_land(v_quotient_263_, v___x_264_);
v___x_273_ = lean_uint64_dec_eq(v___x_272_, v___y_246_);
if (v___x_273_ == 0)
{
uint64_t v___x_274_; 
v___x_274_ = lean_uint64_add(v_quotient_263_, v___x_264_);
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v___x_274_;
goto v___jp_233_;
}
else
{
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v_quotient_263_;
goto v___jp_233_;
}
}
else
{
uint64_t v___x_275_; 
v___x_275_ = lean_uint64_add(v_quotient_263_, v___x_264_);
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v___x_275_;
goto v___jp_233_;
}
}
else
{
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v_quotient_263_;
goto v___jp_233_;
}
}
}
else
{
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v___y_248_;
goto v___jp_233_;
}
}
else
{
uint64_t v___x_276_; uint64_t v___x_277_; 
v___x_276_ = lean_uint64_sub(v___x_253_, v___y_249_);
v___x_277_ = lean_uint64_shift_left(v___y_248_, v___x_276_);
v___y_234_ = v___y_244_;
v___y_235_ = v___y_245_;
v___y_236_ = v_position_250_;
v___y_237_ = v___y_246_;
v___y_238_ = v___x_277_;
goto v___jp_233_;
}
}
else
{
uint64_t v___x_278_; uint8_t v___x_279_; 
v___x_278_ = 149ULL;
v___x_279_ = lean_uint64_dec_lt(v___y_247_, v___x_278_);
if (v___x_279_ == 0)
{
uint64_t v___x_280_; uint64_t v___x_281_; 
v___x_280_ = lean_uint64_sub(v___y_247_, v___x_278_);
v___x_281_ = lean_uint64_shift_left(v___y_248_, v___x_280_);
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v___x_281_;
goto v___jp_148_;
}
else
{
uint64_t v___x_282_; uint8_t v___x_283_; 
v___x_282_ = lean_uint64_sub(v___x_278_, v___y_247_);
v___x_283_ = lean_uint64_dec_eq(v___x_282_, v___y_246_);
if (v___x_283_ == 0)
{
uint64_t v___x_284_; uint8_t v___x_285_; 
v___x_284_ = 64ULL;
v___x_285_ = lean_uint64_dec_lt(v___x_282_, v___x_284_);
if (v___x_285_ == 0)
{
uint8_t v___x_286_; 
v___x_286_ = lean_uint64_dec_eq(v___x_282_, v___x_284_);
if (v___x_286_ == 0)
{
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v___y_246_;
goto v___jp_148_;
}
else
{
uint64_t v___x_287_; uint8_t v___x_288_; 
v___x_287_ = 9223372036854775808ULL;
v___x_288_ = lean_uint64_dec_lt(v___x_287_, v___y_248_);
if (v___x_288_ == 0)
{
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v___y_246_;
goto v___jp_148_;
}
else
{
uint64_t v___x_289_; 
v___x_289_ = 1ULL;
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v___x_289_;
goto v___jp_148_;
}
}
}
else
{
uint64_t v_quotient_290_; uint64_t v___x_291_; uint64_t v___x_292_; uint64_t v___x_293_; uint64_t v_remainder_294_; uint64_t v___x_295_; uint64_t v_half_296_; uint8_t v___x_297_; 
v_quotient_290_ = lean_uint64_shift_right(v___y_248_, v___x_282_);
v___x_291_ = 1ULL;
v___x_292_ = lean_uint64_shift_left(v___x_291_, v___x_282_);
v___x_293_ = lean_uint64_sub(v___x_292_, v___x_291_);
v_remainder_294_ = lean_uint64_land(v___y_248_, v___x_293_);
v___x_295_ = lean_uint64_sub(v___x_282_, v___x_291_);
v_half_296_ = lean_uint64_shift_left(v___x_291_, v___x_295_);
v___x_297_ = lean_uint64_dec_lt(v_remainder_294_, v_half_296_);
if (v___x_297_ == 0)
{
uint8_t v___x_298_; 
v___x_298_ = lean_uint64_dec_lt(v_half_296_, v_remainder_294_);
if (v___x_298_ == 0)
{
uint64_t v___x_299_; uint8_t v___x_300_; 
v___x_299_ = lean_uint64_land(v_quotient_290_, v___x_291_);
v___x_300_ = lean_uint64_dec_eq(v___x_299_, v___y_246_);
if (v___x_300_ == 0)
{
uint64_t v___x_301_; 
v___x_301_ = lean_uint64_add(v_quotient_290_, v___x_291_);
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v___x_301_;
goto v___jp_148_;
}
else
{
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v_quotient_290_;
goto v___jp_148_;
}
}
else
{
uint64_t v___x_302_; 
v___x_302_ = lean_uint64_add(v_quotient_290_, v___x_291_);
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v___x_302_;
goto v___jp_148_;
}
}
else
{
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v_quotient_290_;
goto v___jp_148_;
}
}
}
else
{
v___y_149_ = v___y_244_;
v___y_150_ = v___y_245_;
v___y_151_ = v___y_246_;
v___y_152_ = v___y_248_;
goto v___jp_148_;
}
}
}
}
v___jp_303_:
{
uint64_t v___x_311_; uint64_t v___x_312_; uint8_t v___x_313_; 
v___x_311_ = 1ULL;
v___x_312_ = lean_uint64_shift_right(v___y_306_, v___x_311_);
v___x_313_ = lean_uint64_dec_eq(v___x_312_, v___y_307_);
if (v___x_313_ == 0)
{
uint64_t v___x_314_; 
v___x_314_ = lean_uint64_add(v___y_310_, v___x_311_);
v___y_244_ = v___y_304_;
v___y_245_ = v___y_305_;
v___y_246_ = v___y_307_;
v___y_247_ = v___y_308_;
v___y_248_ = v___y_309_;
v___y_249_ = v___x_314_;
goto v___jp_243_;
}
else
{
v___y_244_ = v___y_304_;
v___y_245_ = v___y_305_;
v___y_246_ = v___y_307_;
v___y_247_ = v___y_308_;
v___y_248_ = v___y_309_;
v___y_249_ = v___y_310_;
goto v___jp_243_;
}
}
v___jp_315_:
{
uint64_t v___x_325_; uint8_t v___x_326_; 
v___x_325_ = lean_uint64_shift_right(v___y_317_, v___y_320_);
v___x_326_ = lean_uint64_dec_eq(v___x_325_, v___y_321_);
if (v___x_326_ == 0)
{
uint64_t v___x_327_; 
v___x_327_ = lean_uint64_add(v___y_319_, v___y_320_);
v___y_304_ = v___y_316_;
v___y_305_ = v___y_318_;
v___y_306_ = v___y_324_;
v___y_307_ = v___y_321_;
v___y_308_ = v___y_322_;
v___y_309_ = v___y_323_;
v___y_310_ = v___x_327_;
goto v___jp_303_;
}
else
{
v___y_304_ = v___y_316_;
v___y_305_ = v___y_318_;
v___y_306_ = v___y_324_;
v___y_307_ = v___y_321_;
v___y_308_ = v___y_322_;
v___y_309_ = v___y_323_;
v___y_310_ = v___y_319_;
goto v___jp_303_;
}
}
v___jp_328_:
{
uint64_t v___x_336_; uint64_t v___x_337_; uint8_t v___x_338_; 
v___x_336_ = 2ULL;
v___x_337_ = lean_uint64_shift_right(v___y_331_, v___x_336_);
v___x_338_ = lean_uint64_dec_eq(v___x_337_, v___y_332_);
if (v___x_338_ == 0)
{
v___y_316_ = v___y_329_;
v___y_317_ = v___y_331_;
v___y_318_ = v___y_330_;
v___y_319_ = v___y_335_;
v___y_320_ = v___x_336_;
v___y_321_ = v___y_332_;
v___y_322_ = v___y_333_;
v___y_323_ = v___y_334_;
v___y_324_ = v___x_337_;
goto v___jp_315_;
}
else
{
v___y_316_ = v___y_329_;
v___y_317_ = v___y_331_;
v___y_318_ = v___y_330_;
v___y_319_ = v___y_335_;
v___y_320_ = v___x_336_;
v___y_321_ = v___y_332_;
v___y_322_ = v___y_333_;
v___y_323_ = v___y_334_;
v___y_324_ = v___y_331_;
goto v___jp_315_;
}
}
v___jp_339_:
{
uint64_t v___x_349_; uint8_t v___x_350_; 
v___x_349_ = lean_uint64_shift_right(v___y_342_, v___y_344_);
v___x_350_ = lean_uint64_dec_eq(v___x_349_, v___y_345_);
if (v___x_350_ == 0)
{
uint64_t v___x_351_; 
v___x_351_ = lean_uint64_add(v___y_341_, v___y_344_);
v___y_329_ = v___y_340_;
v___y_330_ = v___y_343_;
v___y_331_ = v___y_348_;
v___y_332_ = v___y_345_;
v___y_333_ = v___y_346_;
v___y_334_ = v___y_347_;
v___y_335_ = v___x_351_;
goto v___jp_328_;
}
else
{
v___y_329_ = v___y_340_;
v___y_330_ = v___y_343_;
v___y_331_ = v___y_348_;
v___y_332_ = v___y_345_;
v___y_333_ = v___y_346_;
v___y_334_ = v___y_347_;
v___y_335_ = v___y_341_;
goto v___jp_328_;
}
}
v___jp_352_:
{
uint64_t v___x_360_; uint64_t v___x_361_; uint8_t v___x_362_; 
v___x_360_ = 4ULL;
v___x_361_ = lean_uint64_shift_right(v___y_354_, v___x_360_);
v___x_362_ = lean_uint64_dec_eq(v___x_361_, v___y_356_);
if (v___x_362_ == 0)
{
v___y_340_ = v___y_353_;
v___y_341_ = v___y_359_;
v___y_342_ = v___y_354_;
v___y_343_ = v___y_355_;
v___y_344_ = v___x_360_;
v___y_345_ = v___y_356_;
v___y_346_ = v___y_357_;
v___y_347_ = v___y_358_;
v___y_348_ = v___x_361_;
goto v___jp_339_;
}
else
{
v___y_340_ = v___y_353_;
v___y_341_ = v___y_359_;
v___y_342_ = v___y_354_;
v___y_343_ = v___y_355_;
v___y_344_ = v___x_360_;
v___y_345_ = v___y_356_;
v___y_346_ = v___y_357_;
v___y_347_ = v___y_358_;
v___y_348_ = v___y_354_;
goto v___jp_339_;
}
}
v___jp_363_:
{
uint64_t v___x_373_; uint8_t v___x_374_; 
v___x_373_ = lean_uint64_shift_right(v___y_365_, v___y_367_);
v___x_374_ = lean_uint64_dec_eq(v___x_373_, v___y_369_);
if (v___x_374_ == 0)
{
uint64_t v___x_375_; 
v___x_375_ = lean_uint64_add(v___y_364_, v___y_367_);
v___y_353_ = v___y_366_;
v___y_354_ = v___y_372_;
v___y_355_ = v___y_368_;
v___y_356_ = v___y_369_;
v___y_357_ = v___y_370_;
v___y_358_ = v___y_371_;
v___y_359_ = v___x_375_;
goto v___jp_352_;
}
else
{
v___y_353_ = v___y_366_;
v___y_354_ = v___y_372_;
v___y_355_ = v___y_368_;
v___y_356_ = v___y_369_;
v___y_357_ = v___y_370_;
v___y_358_ = v___y_371_;
v___y_359_ = v___y_364_;
goto v___jp_352_;
}
}
v___jp_376_:
{
uint64_t v___x_384_; uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_384_ = 8ULL;
v___x_385_ = lean_uint64_shift_right(v___y_378_, v___x_384_);
v___x_386_ = lean_uint64_dec_eq(v___x_385_, v___y_380_);
if (v___x_386_ == 0)
{
v___y_364_ = v___y_383_;
v___y_365_ = v___y_378_;
v___y_366_ = v___y_377_;
v___y_367_ = v___x_384_;
v___y_368_ = v___y_379_;
v___y_369_ = v___y_380_;
v___y_370_ = v___y_381_;
v___y_371_ = v___y_382_;
v___y_372_ = v___x_385_;
goto v___jp_363_;
}
else
{
v___y_364_ = v___y_383_;
v___y_365_ = v___y_378_;
v___y_366_ = v___y_377_;
v___y_367_ = v___x_384_;
v___y_368_ = v___y_379_;
v___y_369_ = v___y_380_;
v___y_370_ = v___y_381_;
v___y_371_ = v___y_382_;
v___y_372_ = v___y_378_;
goto v___jp_363_;
}
}
v___jp_387_:
{
uint64_t v___x_397_; uint8_t v___x_398_; 
v___x_397_ = lean_uint64_shift_right(v___y_393_, v___y_388_);
v___x_398_ = lean_uint64_dec_eq(v___x_397_, v___y_392_);
if (v___x_398_ == 0)
{
uint64_t v___x_399_; 
v___x_399_ = lean_uint64_add(v___y_390_, v___y_388_);
v___y_377_ = v___y_389_;
v___y_378_ = v___y_396_;
v___y_379_ = v___y_391_;
v___y_380_ = v___y_392_;
v___y_381_ = v___y_394_;
v___y_382_ = v___y_395_;
v___y_383_ = v___x_399_;
goto v___jp_376_;
}
else
{
v___y_377_ = v___y_389_;
v___y_378_ = v___y_396_;
v___y_379_ = v___y_391_;
v___y_380_ = v___y_392_;
v___y_381_ = v___y_394_;
v___y_382_ = v___y_395_;
v___y_383_ = v___y_390_;
goto v___jp_376_;
}
}
v___jp_400_:
{
uint64_t v___x_408_; uint64_t v___x_409_; uint8_t v___x_410_; 
v___x_408_ = 16ULL;
v___x_409_ = lean_uint64_shift_right(v___y_405_, v___x_408_);
v___x_410_ = lean_uint64_dec_eq(v___x_409_, v___y_403_);
if (v___x_410_ == 0)
{
v___y_388_ = v___x_408_;
v___y_389_ = v___y_401_;
v___y_390_ = v___y_407_;
v___y_391_ = v___y_402_;
v___y_392_ = v___y_403_;
v___y_393_ = v___y_405_;
v___y_394_ = v___y_404_;
v___y_395_ = v___y_406_;
v___y_396_ = v___x_409_;
goto v___jp_387_;
}
else
{
v___y_388_ = v___x_408_;
v___y_389_ = v___y_401_;
v___y_390_ = v___y_407_;
v___y_391_ = v___y_402_;
v___y_392_ = v___y_403_;
v___y_393_ = v___y_405_;
v___y_394_ = v___y_404_;
v___y_395_ = v___y_406_;
v___y_396_ = v___y_405_;
goto v___jp_387_;
}
}
v___jp_411_:
{
uint64_t v___x_419_; uint8_t v___x_420_; 
v___x_419_ = lean_uint64_shift_right(v___y_417_, v___y_413_);
v___x_420_ = lean_uint64_dec_eq(v___x_419_, v___y_415_);
if (v___x_420_ == 0)
{
v___y_401_ = v___y_412_;
v___y_402_ = v___y_414_;
v___y_403_ = v___y_415_;
v___y_404_ = v___y_416_;
v___y_405_ = v___y_418_;
v___y_406_ = v___y_417_;
v___y_407_ = v___y_413_;
goto v___jp_400_;
}
else
{
v___y_401_ = v___y_412_;
v___y_402_ = v___y_414_;
v___y_403_ = v___y_415_;
v___y_404_ = v___y_416_;
v___y_405_ = v___y_418_;
v___y_406_ = v___y_417_;
v___y_407_ = v___y_415_;
goto v___jp_400_;
}
}
v___jp_421_:
{
uint64_t v___x_426_; uint8_t v___x_427_; 
v___x_426_ = 0ULL;
v___x_427_ = lean_uint64_dec_eq(v___y_425_, v___x_426_);
if (v___x_427_ == 0)
{
uint64_t v___x_428_; uint64_t v___x_429_; uint8_t v___x_430_; 
v___x_428_ = 32ULL;
v___x_429_ = lean_uint64_shift_right(v___y_425_, v___x_428_);
v___x_430_ = lean_uint64_dec_eq(v___x_429_, v___x_426_);
if (v___x_430_ == 0)
{
v___y_412_ = v___y_422_;
v___y_413_ = v___x_428_;
v___y_414_ = v___y_423_;
v___y_415_ = v___x_426_;
v___y_416_ = v___y_424_;
v___y_417_ = v___y_425_;
v___y_418_ = v___x_429_;
goto v___jp_411_;
}
else
{
v___y_412_ = v___y_422_;
v___y_413_ = v___x_428_;
v___y_414_ = v___y_423_;
v___y_415_ = v___x_426_;
v___y_416_ = v___y_424_;
v___y_417_ = v___y_425_;
v___y_418_ = v___y_425_;
goto v___jp_411_;
}
}
else
{
if (v___y_422_ == 0)
{
uint32_t v___x_431_; 
v___x_431_ = 0;
return v___x_431_;
}
else
{
uint32_t v___x_432_; 
v___x_432_ = 2147483648;
return v___x_432_;
}
}
}
v___jp_433_:
{
uint64_t v___x_440_; uint64_t v___x_441_; uint64_t v___x_442_; uint8_t v___x_443_; 
v___x_440_ = lean_uint64_mul(v___y_434_, v___y_438_);
v___x_441_ = lean_uint64_add(v___y_437_, v___y_439_);
v___x_442_ = 281474976710656ULL;
v___x_443_ = lean_uint64_dec_lt(v___x_440_, v___x_442_);
if (v___x_443_ == 0)
{
v___y_422_ = v___y_435_;
v___y_423_ = v___y_436_;
v___y_424_ = v___x_441_;
v___y_425_ = v___x_440_;
goto v___jp_421_;
}
else
{
uint64_t v___x_444_; uint8_t v___x_445_; 
v___x_444_ = 123ULL;
v___x_445_ = lean_uint64_dec_le(v___x_441_, v___x_444_);
if (v___x_445_ == 0)
{
v___y_422_ = v___y_435_;
v___y_423_ = v___y_436_;
v___y_424_ = v___x_441_;
v___y_425_ = v___x_440_;
goto v___jp_421_;
}
else
{
uint64_t v___x_446_; uint8_t v___x_447_; 
v___x_446_ = 0ULL;
v___x_447_ = lean_uint64_dec_eq(v___x_440_, v___x_446_);
if (v___x_447_ == 0)
{
uint64_t v___x_448_; uint64_t v___x_449_; uint8_t v___x_450_; 
v___x_448_ = 149ULL;
v___x_449_ = lean_uint64_sub(v___x_448_, v___x_441_);
v___x_450_ = lean_uint64_dec_eq(v___x_449_, v___x_446_);
if (v___x_450_ == 0)
{
uint64_t v___x_451_; uint8_t v___x_452_; 
v___x_451_ = 64ULL;
v___x_452_ = lean_uint64_dec_lt(v___x_449_, v___x_451_);
if (v___x_452_ == 0)
{
uint8_t v___x_453_; 
v___x_453_ = lean_uint64_dec_eq(v___x_449_, v___x_451_);
if (v___x_453_ == 0)
{
v___y_168_ = v___y_435_;
v___y_169_ = v___y_436_;
v___y_170_ = v___x_446_;
v___y_171_ = v___x_446_;
goto v___jp_167_;
}
else
{
uint64_t v___x_454_; uint8_t v___x_455_; 
v___x_454_ = 9223372036854775808ULL;
v___x_455_ = lean_uint64_dec_lt(v___x_454_, v___x_440_);
if (v___x_455_ == 0)
{
v___y_168_ = v___y_435_;
v___y_169_ = v___y_436_;
v___y_170_ = v___x_446_;
v___y_171_ = v___x_446_;
goto v___jp_167_;
}
else
{
uint64_t v___x_456_; 
v___x_456_ = 1ULL;
v___y_168_ = v___y_435_;
v___y_169_ = v___y_436_;
v___y_170_ = v___x_446_;
v___y_171_ = v___x_456_;
goto v___jp_167_;
}
}
}
else
{
uint64_t v_quotient_457_; uint64_t v___x_458_; uint64_t v___x_459_; uint64_t v___x_460_; uint64_t v_remainder_461_; uint64_t v___x_462_; uint64_t v_half_463_; uint8_t v___x_464_; 
v_quotient_457_ = lean_uint64_shift_right(v___x_440_, v___x_449_);
v___x_458_ = 1ULL;
v___x_459_ = lean_uint64_shift_left(v___x_458_, v___x_449_);
v___x_460_ = lean_uint64_sub(v___x_459_, v___x_458_);
v_remainder_461_ = lean_uint64_land(v___x_440_, v___x_460_);
v___x_462_ = lean_uint64_sub(v___x_449_, v___x_458_);
v_half_463_ = lean_uint64_shift_left(v___x_458_, v___x_462_);
v___x_464_ = lean_uint64_dec_lt(v_remainder_461_, v_half_463_);
if (v___x_464_ == 0)
{
uint8_t v___x_465_; 
v___x_465_ = lean_uint64_dec_lt(v_half_463_, v_remainder_461_);
if (v___x_465_ == 0)
{
uint64_t v___x_466_; uint8_t v___x_467_; 
v___x_466_ = lean_uint64_land(v_quotient_457_, v___x_458_);
v___x_467_ = lean_uint64_dec_eq(v___x_466_, v___x_446_);
if (v___x_467_ == 0)
{
uint64_t v___x_468_; 
v___x_468_ = lean_uint64_add(v_quotient_457_, v___x_458_);
v___y_168_ = v___y_435_;
v___y_169_ = v___y_436_;
v___y_170_ = v___x_446_;
v___y_171_ = v___x_468_;
goto v___jp_167_;
}
else
{
v___y_168_ = v___y_435_;
v___y_169_ = v___y_436_;
v___y_170_ = v___x_446_;
v___y_171_ = v_quotient_457_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_469_; 
v___x_469_ = lean_uint64_add(v_quotient_457_, v___x_458_);
v___y_168_ = v___y_435_;
v___y_169_ = v___y_436_;
v___y_170_ = v___x_446_;
v___y_171_ = v___x_469_;
goto v___jp_167_;
}
}
else
{
v___y_168_ = v___y_435_;
v___y_169_ = v___y_436_;
v___y_170_ = v___x_446_;
v___y_171_ = v_quotient_457_;
goto v___jp_167_;
}
}
}
else
{
v___y_168_ = v___y_435_;
v___y_169_ = v___y_436_;
v___y_170_ = v___x_446_;
v___y_171_ = v___x_440_;
goto v___jp_167_;
}
}
else
{
if (v___y_435_ == 0)
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
}
}
v___jp_475_:
{
uint8_t v___x_476_; 
v___x_476_ = lean_uint32_dec_eq(v_ey_474_, v___x_189_);
if (v___x_476_ == 0)
{
v___y_183_ = v___x_476_;
goto v___jp_182_;
}
else
{
uint32_t v___x_477_; uint32_t v___x_478_; uint32_t v___x_479_; uint8_t v___x_480_; 
v___x_477_ = 8388607;
v___x_478_ = lean_uint32_land(v___y_131_, v___x_477_);
v___x_479_ = 0;
v___x_480_ = lean_uint32_dec_eq(v___x_478_, v___x_479_);
if (v___x_480_ == 0)
{
v___y_183_ = v___x_476_;
goto v___jp_182_;
}
else
{
uint32_t v___x_481_; 
v___x_481_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_481_;
}
}
}
v___jp_482_:
{
if (v___y_483_ == 0)
{
goto v___jp_475_;
}
else
{
uint32_t v___x_484_; uint32_t v___x_485_; 
v___x_484_ = 4194304;
v___x_485_ = lean_uint32_lor(v___y_130_, v___x_484_);
return v___x_485_;
}
}
v___jp_486_:
{
uint8_t v___x_487_; 
v___x_487_ = lean_uint32_dec_eq(v_ex_472_, v___x_189_);
if (v___x_487_ == 0)
{
v___y_483_ = v___x_487_;
goto v___jp_482_;
}
else
{
uint32_t v___x_488_; uint32_t v___x_489_; uint32_t v___x_490_; uint8_t v___x_491_; 
v___x_488_ = 8388607;
v___x_489_ = lean_uint32_land(v___y_130_, v___x_488_);
v___x_490_ = 0;
v___x_491_ = lean_uint32_dec_eq(v___x_489_, v___x_490_);
if (v___x_491_ == 0)
{
v___y_483_ = v___x_487_;
goto v___jp_482_;
}
else
{
goto v___jp_475_;
}
}
}
v___jp_492_:
{
if (v___y_493_ == 0)
{
goto v___jp_486_;
}
else
{
uint32_t v___x_494_; uint32_t v___x_495_; uint32_t v___x_496_; uint8_t v___x_497_; 
v___x_494_ = 4194304;
v___x_495_ = lean_uint32_land(v___y_131_, v___x_494_);
v___x_496_ = 0;
v___x_497_ = lean_uint32_dec_eq(v___x_495_, v___x_496_);
if (v___x_497_ == 0)
{
goto v___jp_486_;
}
else
{
uint32_t v___x_498_; 
v___x_498_ = lean_uint32_lor(v___y_131_, v___x_494_);
return v___x_498_;
}
}
}
v___jp_499_:
{
uint8_t v___x_500_; 
v___x_500_ = lean_uint32_dec_eq(v_ey_474_, v___x_189_);
if (v___x_500_ == 0)
{
v___y_493_ = v___x_500_;
goto v___jp_492_;
}
else
{
uint32_t v___x_501_; uint32_t v___x_502_; uint32_t v___x_503_; uint8_t v___x_504_; 
v___x_501_ = 8388607;
v___x_502_ = lean_uint32_land(v___y_131_, v___x_501_);
v___x_503_ = 0;
v___x_504_ = lean_uint32_dec_eq(v___x_502_, v___x_503_);
if (v___x_504_ == 0)
{
v___y_493_ = v___x_500_;
goto v___jp_492_;
}
else
{
goto v___jp_486_;
}
}
}
v___jp_505_:
{
if (v___y_506_ == 0)
{
goto v___jp_499_;
}
else
{
uint32_t v___x_507_; uint32_t v___x_508_; uint32_t v___x_509_; uint8_t v___x_510_; 
v___x_507_ = 4194304;
v___x_508_ = lean_uint32_land(v___y_130_, v___x_507_);
v___x_509_ = 0;
v___x_510_ = lean_uint32_dec_eq(v___x_508_, v___x_509_);
if (v___x_510_ == 0)
{
goto v___jp_499_;
}
else
{
uint32_t v___x_511_; 
v___x_511_ = lean_uint32_lor(v___y_130_, v___x_507_);
return v___x_511_;
}
}
}
v___jp_512_:
{
uint64_t v___x_518_; uint64_t v___x_519_; uint8_t v___x_520_; 
v___x_518_ = lean_uint32_to_uint64(v_ey_474_);
v___x_519_ = 0ULL;
v___x_520_ = lean_uint64_dec_eq(v___x_518_, v___x_519_);
if (v___x_520_ == 0)
{
uint64_t v___x_521_; uint64_t v___x_522_; 
v___x_521_ = 1ULL;
v___x_522_ = lean_uint64_sub(v___x_518_, v___x_521_);
v___y_434_ = v___y_513_;
v___y_435_ = v___y_514_;
v___y_436_ = v___y_515_;
v___y_437_ = v___y_517_;
v___y_438_ = v___y_516_;
v___y_439_ = v___x_522_;
goto v___jp_433_;
}
else
{
v___y_434_ = v___y_513_;
v___y_435_ = v___y_514_;
v___y_436_ = v___y_515_;
v___y_437_ = v___y_517_;
v___y_438_ = v___y_516_;
v___y_439_ = v___x_519_;
goto v___jp_433_;
}
}
v___jp_523_:
{
uint64_t v___x_528_; uint64_t v___x_529_; uint8_t v___x_530_; 
v___x_528_ = lean_uint32_to_uint64(v_ex_472_);
v___x_529_ = 0ULL;
v___x_530_ = lean_uint64_dec_eq(v___x_528_, v___x_529_);
if (v___x_530_ == 0)
{
uint64_t v___x_531_; uint64_t v___x_532_; 
v___x_531_ = 1ULL;
v___x_532_ = lean_uint64_sub(v___x_528_, v___x_531_);
v___y_513_ = v___y_524_;
v___y_514_ = v___y_525_;
v___y_515_ = v___y_526_;
v___y_516_ = v___y_527_;
v___y_517_ = v___x_532_;
goto v___jp_512_;
}
else
{
v___y_513_ = v___y_524_;
v___y_514_ = v___y_525_;
v___y_515_ = v___y_526_;
v___y_516_ = v___y_527_;
v___y_517_ = v___x_529_;
goto v___jp_512_;
}
}
v___jp_533_:
{
uint32_t v___x_538_; uint8_t v___x_539_; 
v___x_538_ = 0;
v___x_539_ = lean_uint32_dec_eq(v_ey_474_, v___x_538_);
if (v___x_539_ == 0)
{
uint64_t v___x_540_; uint64_t v___x_541_; uint64_t v___x_542_; 
v___x_540_ = lean_uint32_to_uint64(v___y_535_);
v___x_541_ = 8388608ULL;
v___x_542_ = lean_uint64_lor(v___x_540_, v___x_541_);
v___y_524_ = v___y_537_;
v___y_525_ = v___y_534_;
v___y_526_ = v___y_536_;
v___y_527_ = v___x_542_;
goto v___jp_523_;
}
else
{
uint64_t v___x_543_; 
v___x_543_ = lean_uint32_to_uint64(v___y_535_);
v___y_524_ = v___y_537_;
v___y_525_ = v___y_534_;
v___y_526_ = v___y_536_;
v___y_527_ = v___x_543_;
goto v___jp_523_;
}
}
v___jp_544_:
{
uint32_t v___x_546_; uint32_t v_xFraction_547_; uint32_t v_yFraction_548_; uint32_t v___x_549_; uint8_t v___x_550_; 
v___x_546_ = 8388607;
v_xFraction_547_ = lean_uint32_land(v___y_130_, v___x_546_);
v_yFraction_548_ = lean_uint32_land(v___y_131_, v___x_546_);
v___x_549_ = 0;
v___x_550_ = lean_uint32_dec_eq(v_ex_472_, v___x_549_);
if (v___x_550_ == 0)
{
uint64_t v___x_551_; uint64_t v___x_552_; uint64_t v___x_553_; 
v___x_551_ = lean_uint32_to_uint64(v_xFraction_547_);
v___x_552_ = 8388608ULL;
v___x_553_ = lean_uint64_lor(v___x_551_, v___x_552_);
v___y_534_ = v___y_545_;
v___y_535_ = v_yFraction_548_;
v___y_536_ = v___x_546_;
v___y_537_ = v___x_553_;
goto v___jp_533_;
}
else
{
uint64_t v___x_554_; 
v___x_554_ = lean_uint32_to_uint64(v_xFraction_547_);
v___y_534_ = v___y_545_;
v___y_535_ = v_yFraction_548_;
v___y_536_ = v___x_546_;
v___y_537_ = v___x_554_;
goto v___jp_533_;
}
}
v___jp_558_:
{
if (v___y_560_ == 0)
{
v___y_545_ = v___x_557_;
goto v___jp_544_;
}
else
{
v___y_545_ = v___y_559_;
goto v___jp_544_;
}
}
v___jp_561_:
{
if (v___y_563_ == 0)
{
if (v___y_564_ == 0)
{
v___y_559_ = v___y_562_;
v___y_560_ = v___x_557_;
goto v___jp_558_;
}
else
{
v___y_545_ = v___x_557_;
goto v___jp_544_;
}
}
else
{
v___y_559_ = v___y_562_;
v___y_560_ = v___y_564_;
goto v___jp_558_;
}
}
v___jp_565_:
{
uint32_t v___x_568_; uint32_t v___x_569_; uint32_t v___x_570_; uint8_t v___x_571_; 
v___x_568_ = 2147483648;
v___x_569_ = lean_uint32_land(v___y_131_, v___x_568_);
v___x_570_ = 0;
v___x_571_ = lean_uint32_dec_eq(v___x_569_, v___x_570_);
if (v___x_571_ == 0)
{
v___y_562_ = v___y_566_;
v___y_563_ = v___y_567_;
v___y_564_ = v___x_557_;
goto v___jp_561_;
}
else
{
v___y_562_ = v___y_566_;
v___y_563_ = v___y_567_;
v___y_564_ = v___y_566_;
goto v___jp_561_;
}
}
v___jp_572_:
{
if (v___y_573_ == 0)
{
uint32_t v___x_574_; uint32_t v___x_575_; uint32_t v___x_576_; uint8_t v___x_577_; 
v___x_574_ = 2147483648;
v___x_575_ = lean_uint32_land(v___y_130_, v___x_574_);
v___x_576_ = 0;
v___x_577_ = lean_uint32_dec_eq(v___x_575_, v___x_576_);
if (v___x_577_ == 0)
{
v___y_566_ = v___y_573_;
v___y_567_ = v___x_557_;
goto v___jp_565_;
}
else
{
v___y_566_ = v___y_573_;
v___y_567_ = v___y_573_;
goto v___jp_565_;
}
}
else
{
lean_object* v___x_578_; lean_object* v___x_579_; lean_object* v___x_580_; uint32_t v___x_581_; 
v___x_578_ = lean_uint32_to_nat(v___y_130_);
v___x_579_ = lean_uint32_to_nat(v___y_131_);
v___x_580_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_578_, v___x_579_);
v___x_581_ = lean_uint32_of_nat(v___x_580_);
lean_dec(v___x_580_);
return v___x_581_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_598_, lean_object* v___y_599_){
_start:
{
uint32_t v___y_4515__boxed_600_; uint32_t v___y_4516__boxed_601_; uint32_t v_res_602_; lean_object* v_r_603_; 
v___y_4515__boxed_600_ = lean_unbox_uint32(v___y_598_);
lean_dec(v___y_598_);
v___y_4516__boxed_601_ = lean_unbox_uint32(v___y_599_);
lean_dec(v___y_599_);
v_res_602_ = lp_competition_main___lam__1(v___y_4515__boxed_600_, v___y_4516__boxed_601_);
v_r_603_ = lean_box_uint32(v_res_602_);
return v_r_603_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_604_, uint32_t v___y_605_){
_start:
{
uint32_t v___y_607_; uint32_t v___y_608_; uint32_t v___y_609_; uint32_t v___y_613_; uint32_t v___y_614_; uint32_t v___y_615_; uint32_t v___y_619_; uint32_t v___y_623_; uint8_t v___y_624_; uint64_t v___y_625_; uint64_t v___y_626_; uint32_t v___y_638_; uint64_t v___y_642_; uint32_t v___y_643_; uint8_t v___y_644_; uint64_t v___y_645_; uint8_t v___y_657_; uint32_t v___x_661_; uint32_t v___x_662_; uint32_t v___x_663_; uint32_t v___y_665_; uint32_t v___y_666_; uint32_t v___y_667_; uint32_t v___y_668_; uint32_t v___y_675_; uint32_t v___y_676_; uint8_t v___y_677_; uint32_t v___y_678_; uint32_t v___y_682_; uint8_t v___y_683_; uint64_t v___y_684_; uint64_t v___y_685_; uint64_t v___y_686_; uint32_t v___y_696_; uint8_t v___y_697_; uint8_t v___y_698_; uint64_t v___y_699_; uint64_t v___y_700_; uint64_t v___y_701_; uint32_t v___y_708_; uint8_t v___y_709_; uint64_t v___y_710_; uint64_t v___y_711_; uint64_t v___y_712_; uint64_t v___y_718_; uint32_t v___y_719_; uint8_t v___y_720_; uint64_t v___y_721_; uint64_t v___y_722_; uint64_t v___y_723_; uint64_t v___y_778_; uint64_t v___y_779_; uint32_t v___y_780_; uint8_t v___y_781_; uint64_t v___y_782_; uint64_t v___y_783_; uint64_t v___y_784_; uint64_t v___y_790_; uint64_t v___y_791_; uint64_t v___y_792_; uint32_t v___y_793_; uint8_t v___y_794_; uint64_t v___y_795_; uint64_t v___y_796_; uint64_t v___y_797_; uint64_t v___y_798_; uint64_t v___y_803_; uint32_t v___y_804_; uint8_t v___y_805_; uint64_t v___y_806_; uint64_t v___y_807_; uint64_t v___y_808_; uint64_t v___y_809_; uint64_t v___y_814_; uint64_t v___y_815_; uint32_t v___y_816_; uint8_t v___y_817_; uint64_t v___y_818_; uint64_t v___y_819_; uint64_t v___y_820_; uint64_t v___y_821_; uint64_t v___y_822_; uint64_t v___y_827_; uint32_t v___y_828_; uint8_t v___y_829_; uint64_t v___y_830_; uint64_t v___y_831_; uint64_t v___y_832_; uint64_t v___y_833_; uint64_t v___y_838_; uint64_t v___y_839_; uint64_t v___y_840_; uint32_t v___y_841_; uint8_t v___y_842_; uint64_t v___y_843_; uint64_t v___y_844_; uint64_t v___y_845_; uint64_t v___y_846_; uint64_t v___y_851_; uint32_t v___y_852_; uint8_t v___y_853_; uint64_t v___y_854_; uint64_t v___y_855_; uint64_t v___y_856_; uint64_t v___y_857_; uint64_t v___y_862_; uint64_t v___y_863_; uint64_t v___y_864_; uint32_t v___y_865_; uint8_t v___y_866_; uint64_t v___y_867_; uint64_t v___y_868_; uint64_t v___y_869_; uint64_t v___y_870_; uint64_t v___y_875_; uint32_t v___y_876_; uint8_t v___y_877_; uint64_t v___y_878_; uint64_t v___y_879_; uint64_t v___y_880_; uint64_t v___y_881_; uint64_t v___y_886_; uint32_t v___y_887_; uint8_t v___y_888_; uint64_t v___y_889_; uint64_t v___y_890_; uint64_t v___y_891_; uint64_t v___y_892_; uint64_t v___y_896_; uint32_t v___y_897_; uint8_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_908_; uint32_t v___y_909_; uint8_t v___y_910_; uint64_t v___y_911_; uint64_t v___y_912_; uint64_t v___y_913_; uint32_t v_ex_946_; uint32_t v___x_947_; uint32_t v_ey_948_; uint8_t v___y_957_; uint8_t v___y_967_; uint8_t v___y_980_; uint64_t v___y_987_; uint32_t v___y_988_; uint8_t v___y_989_; uint64_t v___y_990_; uint64_t v___y_991_; uint32_t v___y_998_; uint8_t v___y_999_; uint64_t v___y_1000_; uint64_t v___y_1001_; uint32_t v___y_1008_; uint32_t v___y_1009_; uint8_t v___y_1010_; uint64_t v___y_1011_; uint8_t v___y_1019_; uint32_t v___x_1029_; uint32_t v___x_1030_; uint8_t v___x_1031_; uint8_t v___y_1033_; uint8_t v___y_1034_; uint8_t v___y_1036_; uint8_t v___y_1037_; uint8_t v___y_1038_; uint8_t v___y_1040_; uint8_t v___y_1041_; uint8_t v___y_1047_; 
v___x_661_ = 23;
v___x_662_ = lean_uint32_shift_right(v___y_604_, v___x_661_);
v___x_663_ = 255;
v_ex_946_ = lean_uint32_land(v___x_662_, v___x_663_);
v___x_947_ = lean_uint32_shift_right(v___y_605_, v___x_661_);
v_ey_948_ = lean_uint32_land(v___x_947_, v___x_663_);
v___x_1029_ = lean_uint32_add(v_ex_946_, v_ey_948_);
v___x_1030_ = 128;
v___x_1031_ = lean_uint32_dec_lt(v___x_1029_, v___x_1030_);
if (v___x_1031_ == 0)
{
float v___x_1056_; float v___x_1057_; float v_result_1058_; uint8_t v___x_1059_; 
v___x_1056_ = lean_float32_of_bits(v___y_604_);
v___x_1057_ = lean_float32_of_bits(v___y_605_);
v_result_1058_ = lean_float32_mul(v___x_1056_, v___x_1057_);
v___x_1059_ = lean_float32_beq(v_result_1058_, v_result_1058_);
if (v___x_1059_ == 0)
{
uint8_t v___x_1060_; 
v___x_1060_ = lean_uint32_dec_eq(v_ex_946_, v___x_663_);
if (v___x_1060_ == 0)
{
v___y_980_ = v___x_1060_;
goto v___jp_979_;
}
else
{
uint32_t v___x_1061_; uint32_t v___x_1062_; uint32_t v___x_1063_; uint8_t v___x_1064_; 
v___x_1061_ = 8388607;
v___x_1062_ = lean_uint32_land(v___y_604_, v___x_1061_);
v___x_1063_ = 0;
v___x_1064_ = lean_uint32_dec_eq(v___x_1062_, v___x_1063_);
if (v___x_1064_ == 0)
{
v___y_980_ = v___x_1060_;
goto v___jp_979_;
}
else
{
goto v___jp_973_;
}
}
}
else
{
uint32_t v___x_1065_; 
v___x_1065_ = lean_float32_to_bits(v_result_1058_);
return v___x_1065_;
}
}
else
{
uint32_t v___x_1066_; uint32_t v___x_1067_; uint32_t v___x_1068_; uint8_t v___x_1069_; 
v___x_1066_ = 4278190080;
v___x_1067_ = 1;
v___x_1068_ = lean_uint32_shift_left(v___y_604_, v___x_1067_);
v___x_1069_ = lean_uint32_dec_le(v___x_1066_, v___x_1068_);
if (v___x_1069_ == 0)
{
uint32_t v___x_1070_; uint8_t v___x_1071_; 
v___x_1070_ = lean_uint32_shift_left(v___y_605_, v___x_1067_);
v___x_1071_ = lean_uint32_dec_le(v___x_1066_, v___x_1070_);
v___y_1047_ = v___x_1071_;
goto v___jp_1046_;
}
else
{
v___y_1047_ = v___x_1069_;
goto v___jp_1046_;
}
}
v___jp_606_:
{
uint32_t v___x_610_; uint32_t v___x_611_; 
v___x_610_ = lean_uint32_land(v___y_607_, v___y_608_);
v___x_611_ = lean_uint32_lor(v___y_609_, v___x_610_);
return v___x_611_;
}
v___jp_612_:
{
uint32_t v___x_616_; uint32_t v___x_617_; 
v___x_616_ = lean_uint32_land(v___y_614_, v___y_613_);
v___x_617_ = lean_uint32_lor(v___y_615_, v___x_616_);
return v___x_617_;
}
v___jp_618_:
{
uint32_t v___x_620_; uint32_t v___x_621_; 
v___x_620_ = 8388608;
v___x_621_ = lean_uint32_lor(v___y_619_, v___x_620_);
return v___x_621_;
}
v___jp_622_:
{
uint8_t v___x_627_; 
v___x_627_ = lean_uint64_dec_eq(v___y_626_, v___y_625_);
if (v___x_627_ == 0)
{
uint64_t v___x_628_; uint8_t v___x_629_; 
v___x_628_ = 8388608ULL;
v___x_629_ = lean_uint64_dec_eq(v___y_626_, v___x_628_);
if (v___x_629_ == 0)
{
uint32_t v___x_630_; 
v___x_630_ = lean_uint64_to_uint32(v___y_626_);
if (v___y_624_ == 0)
{
uint32_t v___x_631_; 
v___x_631_ = 0;
v___y_613_ = v___y_623_;
v___y_614_ = v___x_630_;
v___y_615_ = v___x_631_;
goto v___jp_612_;
}
else
{
uint32_t v___x_632_; 
v___x_632_ = 2147483648;
v___y_613_ = v___y_623_;
v___y_614_ = v___x_630_;
v___y_615_ = v___x_632_;
goto v___jp_612_;
}
}
else
{
if (v___y_624_ == 0)
{
uint32_t v___x_633_; 
v___x_633_ = 0;
v___y_619_ = v___x_633_;
goto v___jp_618_;
}
else
{
uint32_t v___x_634_; 
v___x_634_ = 2147483648;
v___y_619_ = v___x_634_;
goto v___jp_618_;
}
}
}
else
{
if (v___y_624_ == 0)
{
uint32_t v___x_635_; 
v___x_635_ = 0;
return v___x_635_;
}
else
{
uint32_t v___x_636_; 
v___x_636_ = 2147483648;
return v___x_636_;
}
}
}
v___jp_637_:
{
uint32_t v___x_639_; uint32_t v___x_640_; 
v___x_639_ = 8388608;
v___x_640_ = lean_uint32_lor(v___y_638_, v___x_639_);
return v___x_640_;
}
v___jp_641_:
{
uint8_t v___x_646_; 
v___x_646_ = lean_uint64_dec_eq(v___y_645_, v___y_642_);
if (v___x_646_ == 0)
{
uint64_t v___x_647_; uint8_t v___x_648_; 
v___x_647_ = 8388608ULL;
v___x_648_ = lean_uint64_dec_eq(v___y_645_, v___x_647_);
if (v___x_648_ == 0)
{
uint32_t v___x_649_; 
v___x_649_ = lean_uint64_to_uint32(v___y_645_);
if (v___y_644_ == 0)
{
uint32_t v___x_650_; 
v___x_650_ = 0;
v___y_607_ = v___x_649_;
v___y_608_ = v___y_643_;
v___y_609_ = v___x_650_;
goto v___jp_606_;
}
else
{
uint32_t v___x_651_; 
v___x_651_ = 2147483648;
v___y_607_ = v___x_649_;
v___y_608_ = v___y_643_;
v___y_609_ = v___x_651_;
goto v___jp_606_;
}
}
else
{
if (v___y_644_ == 0)
{
uint32_t v___x_652_; 
v___x_652_ = 0;
v___y_638_ = v___x_652_;
goto v___jp_637_;
}
else
{
uint32_t v___x_653_; 
v___x_653_ = 2147483648;
v___y_638_ = v___x_653_;
goto v___jp_637_;
}
}
}
else
{
if (v___y_644_ == 0)
{
uint32_t v___x_654_; 
v___x_654_ = 0;
return v___x_654_;
}
else
{
uint32_t v___x_655_; 
v___x_655_ = 2147483648;
return v___x_655_;
}
}
}
v___jp_656_:
{
if (v___y_657_ == 0)
{
uint32_t v___x_658_; 
v___x_658_ = lp_competition_Submission_FastMul_mul(v___y_604_, v___y_605_);
return v___x_658_;
}
else
{
uint32_t v___x_659_; uint32_t v___x_660_; 
v___x_659_ = 4194304;
v___x_660_ = lean_uint32_lor(v___y_605_, v___x_659_);
return v___x_660_;
}
}
v___jp_664_:
{
uint32_t v___x_669_; uint32_t v___x_670_; uint32_t v___x_671_; uint32_t v___x_672_; uint32_t v___x_673_; 
v___x_669_ = lean_uint32_land(v___y_665_, v___x_663_);
v___x_670_ = lean_uint32_shift_left(v___x_669_, v___x_661_);
v___x_671_ = lean_uint32_lor(v___y_668_, v___x_670_);
v___x_672_ = lean_uint32_land(v___y_667_, v___y_666_);
v___x_673_ = lean_uint32_lor(v___x_671_, v___x_672_);
return v___x_673_;
}
v___jp_674_:
{
if (v___y_677_ == 0)
{
uint32_t v___x_679_; 
v___x_679_ = 0;
v___y_665_ = v___y_675_;
v___y_666_ = v___y_676_;
v___y_667_ = v___y_678_;
v___y_668_ = v___x_679_;
goto v___jp_664_;
}
else
{
uint32_t v___x_680_; 
v___x_680_ = 2147483648;
v___y_665_ = v___y_675_;
v___y_666_ = v___y_676_;
v___y_667_ = v___y_678_;
v___y_668_ = v___x_680_;
goto v___jp_664_;
}
}
v___jp_681_:
{
uint64_t v___x_687_; uint64_t v_encodedExponent_688_; uint32_t v___x_689_; uint64_t v___x_690_; uint8_t v___x_691_; 
v___x_687_ = 171ULL;
v_encodedExponent_688_ = lean_uint64_sub(v___y_685_, v___x_687_);
v___x_689_ = lean_uint64_to_uint32(v_encodedExponent_688_);
v___x_690_ = 8388608ULL;
v___x_691_ = lean_uint64_dec_lt(v___y_686_, v___x_690_);
if (v___x_691_ == 0)
{
uint64_t v___x_692_; uint32_t v___x_693_; 
v___x_692_ = lean_uint64_sub(v___y_686_, v___x_690_);
v___x_693_ = lean_uint64_to_uint32(v___x_692_);
v___y_675_ = v___x_689_;
v___y_676_ = v___y_682_;
v___y_677_ = v___y_683_;
v___y_678_ = v___x_693_;
goto v___jp_674_;
}
else
{
uint32_t v___x_694_; 
v___x_694_ = lean_uint64_to_uint32(v___y_684_);
v___y_675_ = v___x_689_;
v___y_676_ = v___y_682_;
v___y_677_ = v___y_683_;
v___y_678_ = v___x_694_;
goto v___jp_674_;
}
}
v___jp_695_:
{
uint64_t v___x_702_; uint8_t v___x_703_; 
v___x_702_ = 425ULL;
v___x_703_ = lean_uint64_dec_lt(v___x_702_, v___y_701_);
if (v___x_703_ == 0)
{
if (v___y_697_ == 0)
{
v___y_682_ = v___y_696_;
v___y_683_ = v___y_698_;
v___y_684_ = v___y_699_;
v___y_685_ = v___y_701_;
v___y_686_ = v___y_700_;
goto v___jp_681_;
}
else
{
uint64_t v___x_704_; 
v___x_704_ = 8388608ULL;
v___y_682_ = v___y_696_;
v___y_683_ = v___y_698_;
v___y_684_ = v___y_699_;
v___y_685_ = v___y_701_;
v___y_686_ = v___x_704_;
goto v___jp_681_;
}
}
else
{
if (v___y_698_ == 0)
{
uint32_t v___x_705_; 
v___x_705_ = 2139095040;
return v___x_705_;
}
else
{
uint32_t v___x_706_; 
v___x_706_ = 4286578688;
return v___x_706_;
}
}
}
v___jp_707_:
{
uint64_t v___x_713_; uint8_t v_carry_714_; 
v___x_713_ = 16777216ULL;
v_carry_714_ = lean_uint64_dec_eq(v___y_712_, v___x_713_);
if (v_carry_714_ == 0)
{
v___y_696_ = v___y_708_;
v___y_697_ = v_carry_714_;
v___y_698_ = v___y_709_;
v___y_699_ = v___y_711_;
v___y_700_ = v___y_712_;
v___y_701_ = v___y_710_;
goto v___jp_695_;
}
else
{
uint64_t v___x_715_; uint64_t v___x_716_; 
v___x_715_ = 1ULL;
v___x_716_ = lean_uint64_add(v___y_710_, v___x_715_);
v___y_696_ = v___y_708_;
v___y_697_ = v_carry_714_;
v___y_698_ = v___y_709_;
v___y_699_ = v___y_711_;
v___y_700_ = v___y_712_;
v___y_701_ = v___x_716_;
goto v___jp_695_;
}
}
v___jp_717_:
{
uint64_t v_position_724_; uint64_t v___x_725_; uint8_t v___x_726_; 
v_position_724_ = lean_uint64_add(v___y_723_, v___y_722_);
v___x_725_ = 172ULL;
v___x_726_ = lean_uint64_dec_lt(v_position_724_, v___x_725_);
if (v___x_726_ == 0)
{
uint64_t v___x_727_; uint8_t v___x_728_; 
v___x_727_ = 23ULL;
v___x_728_ = lean_uint64_dec_lt(v___y_723_, v___x_727_);
if (v___x_728_ == 0)
{
uint64_t v___x_729_; uint8_t v___x_730_; 
v___x_729_ = lean_uint64_sub(v___y_723_, v___x_727_);
v___x_730_ = lean_uint64_dec_eq(v___x_729_, v___y_721_);
if (v___x_730_ == 0)
{
uint64_t v___x_731_; uint8_t v___x_732_; 
v___x_731_ = 64ULL;
v___x_732_ = lean_uint64_dec_lt(v___x_729_, v___x_731_);
if (v___x_732_ == 0)
{
uint8_t v___x_733_; 
v___x_733_ = lean_uint64_dec_eq(v___x_729_, v___x_731_);
if (v___x_733_ == 0)
{
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v___y_721_;
goto v___jp_707_;
}
else
{
uint64_t v___x_734_; uint8_t v___x_735_; 
v___x_734_ = 9223372036854775808ULL;
v___x_735_ = lean_uint64_dec_lt(v___x_734_, v___y_718_);
if (v___x_735_ == 0)
{
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v___y_721_;
goto v___jp_707_;
}
else
{
uint64_t v___x_736_; 
v___x_736_ = 1ULL;
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v___x_736_;
goto v___jp_707_;
}
}
}
else
{
uint64_t v_quotient_737_; uint64_t v___x_738_; uint64_t v___x_739_; uint64_t v___x_740_; uint64_t v_remainder_741_; uint64_t v___x_742_; uint64_t v_half_743_; uint8_t v___x_744_; 
v_quotient_737_ = lean_uint64_shift_right(v___y_718_, v___x_729_);
v___x_738_ = 1ULL;
v___x_739_ = lean_uint64_shift_left(v___x_738_, v___x_729_);
v___x_740_ = lean_uint64_sub(v___x_739_, v___x_738_);
v_remainder_741_ = lean_uint64_land(v___y_718_, v___x_740_);
v___x_742_ = lean_uint64_sub(v___x_729_, v___x_738_);
v_half_743_ = lean_uint64_shift_left(v___x_738_, v___x_742_);
v___x_744_ = lean_uint64_dec_lt(v_remainder_741_, v_half_743_);
if (v___x_744_ == 0)
{
uint8_t v___x_745_; 
v___x_745_ = lean_uint64_dec_lt(v_half_743_, v_remainder_741_);
if (v___x_745_ == 0)
{
uint64_t v___x_746_; uint8_t v___x_747_; 
v___x_746_ = lean_uint64_land(v_quotient_737_, v___x_738_);
v___x_747_ = lean_uint64_dec_eq(v___x_746_, v___y_721_);
if (v___x_747_ == 0)
{
uint64_t v___x_748_; 
v___x_748_ = lean_uint64_add(v_quotient_737_, v___x_738_);
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v___x_748_;
goto v___jp_707_;
}
else
{
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v_quotient_737_;
goto v___jp_707_;
}
}
else
{
uint64_t v___x_749_; 
v___x_749_ = lean_uint64_add(v_quotient_737_, v___x_738_);
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v___x_749_;
goto v___jp_707_;
}
}
else
{
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v_quotient_737_;
goto v___jp_707_;
}
}
}
else
{
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v___y_718_;
goto v___jp_707_;
}
}
else
{
uint64_t v___x_750_; uint64_t v___x_751_; 
v___x_750_ = lean_uint64_sub(v___x_727_, v___y_723_);
v___x_751_ = lean_uint64_shift_left(v___y_718_, v___x_750_);
v___y_708_ = v___y_719_;
v___y_709_ = v___y_720_;
v___y_710_ = v_position_724_;
v___y_711_ = v___y_721_;
v___y_712_ = v___x_751_;
goto v___jp_707_;
}
}
else
{
uint64_t v___x_752_; uint8_t v___x_753_; 
v___x_752_ = 149ULL;
v___x_753_ = lean_uint64_dec_lt(v___y_722_, v___x_752_);
if (v___x_753_ == 0)
{
uint64_t v___x_754_; uint64_t v___x_755_; 
v___x_754_ = lean_uint64_sub(v___y_722_, v___x_752_);
v___x_755_ = lean_uint64_shift_left(v___y_718_, v___x_754_);
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v___x_755_;
goto v___jp_622_;
}
else
{
uint64_t v___x_756_; uint8_t v___x_757_; 
v___x_756_ = lean_uint64_sub(v___x_752_, v___y_722_);
v___x_757_ = lean_uint64_dec_eq(v___x_756_, v___y_721_);
if (v___x_757_ == 0)
{
uint64_t v___x_758_; uint8_t v___x_759_; 
v___x_758_ = 64ULL;
v___x_759_ = lean_uint64_dec_lt(v___x_756_, v___x_758_);
if (v___x_759_ == 0)
{
uint8_t v___x_760_; 
v___x_760_ = lean_uint64_dec_eq(v___x_756_, v___x_758_);
if (v___x_760_ == 0)
{
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v___y_721_;
goto v___jp_622_;
}
else
{
uint64_t v___x_761_; uint8_t v___x_762_; 
v___x_761_ = 9223372036854775808ULL;
v___x_762_ = lean_uint64_dec_lt(v___x_761_, v___y_718_);
if (v___x_762_ == 0)
{
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v___y_721_;
goto v___jp_622_;
}
else
{
uint64_t v___x_763_; 
v___x_763_ = 1ULL;
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v___x_763_;
goto v___jp_622_;
}
}
}
else
{
uint64_t v_quotient_764_; uint64_t v___x_765_; uint64_t v___x_766_; uint64_t v___x_767_; uint64_t v_remainder_768_; uint64_t v___x_769_; uint64_t v_half_770_; uint8_t v___x_771_; 
v_quotient_764_ = lean_uint64_shift_right(v___y_718_, v___x_756_);
v___x_765_ = 1ULL;
v___x_766_ = lean_uint64_shift_left(v___x_765_, v___x_756_);
v___x_767_ = lean_uint64_sub(v___x_766_, v___x_765_);
v_remainder_768_ = lean_uint64_land(v___y_718_, v___x_767_);
v___x_769_ = lean_uint64_sub(v___x_756_, v___x_765_);
v_half_770_ = lean_uint64_shift_left(v___x_765_, v___x_769_);
v___x_771_ = lean_uint64_dec_lt(v_remainder_768_, v_half_770_);
if (v___x_771_ == 0)
{
uint8_t v___x_772_; 
v___x_772_ = lean_uint64_dec_lt(v_half_770_, v_remainder_768_);
if (v___x_772_ == 0)
{
uint64_t v___x_773_; uint8_t v___x_774_; 
v___x_773_ = lean_uint64_land(v_quotient_764_, v___x_765_);
v___x_774_ = lean_uint64_dec_eq(v___x_773_, v___y_721_);
if (v___x_774_ == 0)
{
uint64_t v___x_775_; 
v___x_775_ = lean_uint64_add(v_quotient_764_, v___x_765_);
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v___x_775_;
goto v___jp_622_;
}
else
{
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v_quotient_764_;
goto v___jp_622_;
}
}
else
{
uint64_t v___x_776_; 
v___x_776_ = lean_uint64_add(v_quotient_764_, v___x_765_);
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v___x_776_;
goto v___jp_622_;
}
}
else
{
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v_quotient_764_;
goto v___jp_622_;
}
}
}
else
{
v___y_623_ = v___y_719_;
v___y_624_ = v___y_720_;
v___y_625_ = v___y_721_;
v___y_626_ = v___y_718_;
goto v___jp_622_;
}
}
}
}
v___jp_777_:
{
uint64_t v___x_785_; uint64_t v___x_786_; uint8_t v___x_787_; 
v___x_785_ = 1ULL;
v___x_786_ = lean_uint64_shift_right(v___y_779_, v___x_785_);
v___x_787_ = lean_uint64_dec_eq(v___x_786_, v___y_782_);
if (v___x_787_ == 0)
{
uint64_t v___x_788_; 
v___x_788_ = lean_uint64_add(v___y_784_, v___x_785_);
v___y_718_ = v___y_778_;
v___y_719_ = v___y_780_;
v___y_720_ = v___y_781_;
v___y_721_ = v___y_782_;
v___y_722_ = v___y_783_;
v___y_723_ = v___x_788_;
goto v___jp_717_;
}
else
{
v___y_718_ = v___y_778_;
v___y_719_ = v___y_780_;
v___y_720_ = v___y_781_;
v___y_721_ = v___y_782_;
v___y_722_ = v___y_783_;
v___y_723_ = v___y_784_;
goto v___jp_717_;
}
}
v___jp_789_:
{
uint64_t v___x_799_; uint8_t v___x_800_; 
v___x_799_ = lean_uint64_shift_right(v___y_796_, v___y_791_);
v___x_800_ = lean_uint64_dec_eq(v___x_799_, v___y_795_);
if (v___x_800_ == 0)
{
uint64_t v___x_801_; 
v___x_801_ = lean_uint64_add(v___y_792_, v___y_791_);
v___y_778_ = v___y_790_;
v___y_779_ = v___y_798_;
v___y_780_ = v___y_793_;
v___y_781_ = v___y_794_;
v___y_782_ = v___y_795_;
v___y_783_ = v___y_797_;
v___y_784_ = v___x_801_;
goto v___jp_777_;
}
else
{
v___y_778_ = v___y_790_;
v___y_779_ = v___y_798_;
v___y_780_ = v___y_793_;
v___y_781_ = v___y_794_;
v___y_782_ = v___y_795_;
v___y_783_ = v___y_797_;
v___y_784_ = v___y_792_;
goto v___jp_777_;
}
}
v___jp_802_:
{
uint64_t v___x_810_; uint64_t v___x_811_; uint8_t v___x_812_; 
v___x_810_ = 2ULL;
v___x_811_ = lean_uint64_shift_right(v___y_807_, v___x_810_);
v___x_812_ = lean_uint64_dec_eq(v___x_811_, v___y_806_);
if (v___x_812_ == 0)
{
v___y_790_ = v___y_803_;
v___y_791_ = v___x_810_;
v___y_792_ = v___y_809_;
v___y_793_ = v___y_804_;
v___y_794_ = v___y_805_;
v___y_795_ = v___y_806_;
v___y_796_ = v___y_807_;
v___y_797_ = v___y_808_;
v___y_798_ = v___x_811_;
goto v___jp_789_;
}
else
{
v___y_790_ = v___y_803_;
v___y_791_ = v___x_810_;
v___y_792_ = v___y_809_;
v___y_793_ = v___y_804_;
v___y_794_ = v___y_805_;
v___y_795_ = v___y_806_;
v___y_796_ = v___y_807_;
v___y_797_ = v___y_808_;
v___y_798_ = v___y_807_;
goto v___jp_789_;
}
}
v___jp_813_:
{
uint64_t v___x_823_; uint8_t v___x_824_; 
v___x_823_ = lean_uint64_shift_right(v___y_820_, v___y_819_);
v___x_824_ = lean_uint64_dec_eq(v___x_823_, v___y_818_);
if (v___x_824_ == 0)
{
uint64_t v___x_825_; 
v___x_825_ = lean_uint64_add(v___y_815_, v___y_819_);
v___y_803_ = v___y_814_;
v___y_804_ = v___y_816_;
v___y_805_ = v___y_817_;
v___y_806_ = v___y_818_;
v___y_807_ = v___y_822_;
v___y_808_ = v___y_821_;
v___y_809_ = v___x_825_;
goto v___jp_802_;
}
else
{
v___y_803_ = v___y_814_;
v___y_804_ = v___y_816_;
v___y_805_ = v___y_817_;
v___y_806_ = v___y_818_;
v___y_807_ = v___y_822_;
v___y_808_ = v___y_821_;
v___y_809_ = v___y_815_;
goto v___jp_802_;
}
}
v___jp_826_:
{
uint64_t v___x_834_; uint64_t v___x_835_; uint8_t v___x_836_; 
v___x_834_ = 4ULL;
v___x_835_ = lean_uint64_shift_right(v___y_832_, v___x_834_);
v___x_836_ = lean_uint64_dec_eq(v___x_835_, v___y_830_);
if (v___x_836_ == 0)
{
v___y_814_ = v___y_827_;
v___y_815_ = v___y_833_;
v___y_816_ = v___y_828_;
v___y_817_ = v___y_829_;
v___y_818_ = v___y_830_;
v___y_819_ = v___x_834_;
v___y_820_ = v___y_832_;
v___y_821_ = v___y_831_;
v___y_822_ = v___x_835_;
goto v___jp_813_;
}
else
{
v___y_814_ = v___y_827_;
v___y_815_ = v___y_833_;
v___y_816_ = v___y_828_;
v___y_817_ = v___y_829_;
v___y_818_ = v___y_830_;
v___y_819_ = v___x_834_;
v___y_820_ = v___y_832_;
v___y_821_ = v___y_831_;
v___y_822_ = v___y_832_;
goto v___jp_813_;
}
}
v___jp_837_:
{
uint64_t v___x_847_; uint8_t v___x_848_; 
v___x_847_ = lean_uint64_shift_right(v___y_844_, v___y_839_);
v___x_848_ = lean_uint64_dec_eq(v___x_847_, v___y_843_);
if (v___x_848_ == 0)
{
uint64_t v___x_849_; 
v___x_849_ = lean_uint64_add(v___y_840_, v___y_839_);
v___y_827_ = v___y_838_;
v___y_828_ = v___y_841_;
v___y_829_ = v___y_842_;
v___y_830_ = v___y_843_;
v___y_831_ = v___y_845_;
v___y_832_ = v___y_846_;
v___y_833_ = v___x_849_;
goto v___jp_826_;
}
else
{
v___y_827_ = v___y_838_;
v___y_828_ = v___y_841_;
v___y_829_ = v___y_842_;
v___y_830_ = v___y_843_;
v___y_831_ = v___y_845_;
v___y_832_ = v___y_846_;
v___y_833_ = v___y_840_;
goto v___jp_826_;
}
}
v___jp_850_:
{
uint64_t v___x_858_; uint64_t v___x_859_; uint8_t v___x_860_; 
v___x_858_ = 8ULL;
v___x_859_ = lean_uint64_shift_right(v___y_856_, v___x_858_);
v___x_860_ = lean_uint64_dec_eq(v___x_859_, v___y_854_);
if (v___x_860_ == 0)
{
v___y_838_ = v___y_851_;
v___y_839_ = v___x_858_;
v___y_840_ = v___y_857_;
v___y_841_ = v___y_852_;
v___y_842_ = v___y_853_;
v___y_843_ = v___y_854_;
v___y_844_ = v___y_856_;
v___y_845_ = v___y_855_;
v___y_846_ = v___x_859_;
goto v___jp_837_;
}
else
{
v___y_838_ = v___y_851_;
v___y_839_ = v___x_858_;
v___y_840_ = v___y_857_;
v___y_841_ = v___y_852_;
v___y_842_ = v___y_853_;
v___y_843_ = v___y_854_;
v___y_844_ = v___y_856_;
v___y_845_ = v___y_855_;
v___y_846_ = v___y_856_;
goto v___jp_837_;
}
}
v___jp_861_:
{
uint64_t v___x_871_; uint8_t v___x_872_; 
v___x_871_ = lean_uint64_shift_right(v___y_869_, v___y_862_);
v___x_872_ = lean_uint64_dec_eq(v___x_871_, v___y_867_);
if (v___x_872_ == 0)
{
uint64_t v___x_873_; 
v___x_873_ = lean_uint64_add(v___y_864_, v___y_862_);
v___y_851_ = v___y_863_;
v___y_852_ = v___y_865_;
v___y_853_ = v___y_866_;
v___y_854_ = v___y_867_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_870_;
v___y_857_ = v___x_873_;
goto v___jp_850_;
}
else
{
v___y_851_ = v___y_863_;
v___y_852_ = v___y_865_;
v___y_853_ = v___y_866_;
v___y_854_ = v___y_867_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_870_;
v___y_857_ = v___y_864_;
goto v___jp_850_;
}
}
v___jp_874_:
{
uint64_t v___x_882_; uint64_t v___x_883_; uint8_t v___x_884_; 
v___x_882_ = 16ULL;
v___x_883_ = lean_uint64_shift_right(v___y_880_, v___x_882_);
v___x_884_ = lean_uint64_dec_eq(v___x_883_, v___y_878_);
if (v___x_884_ == 0)
{
v___y_862_ = v___x_882_;
v___y_863_ = v___y_875_;
v___y_864_ = v___y_881_;
v___y_865_ = v___y_876_;
v___y_866_ = v___y_877_;
v___y_867_ = v___y_878_;
v___y_868_ = v___y_879_;
v___y_869_ = v___y_880_;
v___y_870_ = v___x_883_;
goto v___jp_861_;
}
else
{
v___y_862_ = v___x_882_;
v___y_863_ = v___y_875_;
v___y_864_ = v___y_881_;
v___y_865_ = v___y_876_;
v___y_866_ = v___y_877_;
v___y_867_ = v___y_878_;
v___y_868_ = v___y_879_;
v___y_869_ = v___y_880_;
v___y_870_ = v___y_880_;
goto v___jp_861_;
}
}
v___jp_885_:
{
uint64_t v___x_893_; uint8_t v___x_894_; 
v___x_893_ = lean_uint64_shift_right(v___y_886_, v___y_891_);
v___x_894_ = lean_uint64_dec_eq(v___x_893_, v___y_889_);
if (v___x_894_ == 0)
{
v___y_875_ = v___y_886_;
v___y_876_ = v___y_887_;
v___y_877_ = v___y_888_;
v___y_878_ = v___y_889_;
v___y_879_ = v___y_890_;
v___y_880_ = v___y_892_;
v___y_881_ = v___y_891_;
goto v___jp_874_;
}
else
{
v___y_875_ = v___y_886_;
v___y_876_ = v___y_887_;
v___y_877_ = v___y_888_;
v___y_878_ = v___y_889_;
v___y_879_ = v___y_890_;
v___y_880_ = v___y_892_;
v___y_881_ = v___y_889_;
goto v___jp_874_;
}
}
v___jp_895_:
{
uint64_t v___x_900_; uint8_t v___x_901_; 
v___x_900_ = 0ULL;
v___x_901_ = lean_uint64_dec_eq(v___y_896_, v___x_900_);
if (v___x_901_ == 0)
{
uint64_t v___x_902_; uint64_t v___x_903_; uint8_t v___x_904_; 
v___x_902_ = 32ULL;
v___x_903_ = lean_uint64_shift_right(v___y_896_, v___x_902_);
v___x_904_ = lean_uint64_dec_eq(v___x_903_, v___x_900_);
if (v___x_904_ == 0)
{
v___y_886_ = v___y_896_;
v___y_887_ = v___y_897_;
v___y_888_ = v___y_898_;
v___y_889_ = v___x_900_;
v___y_890_ = v___y_899_;
v___y_891_ = v___x_902_;
v___y_892_ = v___x_903_;
goto v___jp_885_;
}
else
{
v___y_886_ = v___y_896_;
v___y_887_ = v___y_897_;
v___y_888_ = v___y_898_;
v___y_889_ = v___x_900_;
v___y_890_ = v___y_899_;
v___y_891_ = v___x_902_;
v___y_892_ = v___y_896_;
goto v___jp_885_;
}
}
else
{
if (v___y_898_ == 0)
{
uint32_t v___x_905_; 
v___x_905_ = 0;
return v___x_905_;
}
else
{
uint32_t v___x_906_; 
v___x_906_ = 2147483648;
return v___x_906_;
}
}
}
v___jp_907_:
{
uint64_t v___x_914_; uint64_t v___x_915_; uint64_t v___x_916_; uint8_t v___x_917_; 
v___x_914_ = lean_uint64_mul(v___y_911_, v___y_908_);
v___x_915_ = lean_uint64_add(v___y_912_, v___y_913_);
v___x_916_ = 281474976710656ULL;
v___x_917_ = lean_uint64_dec_lt(v___x_914_, v___x_916_);
if (v___x_917_ == 0)
{
v___y_896_ = v___x_914_;
v___y_897_ = v___y_909_;
v___y_898_ = v___y_910_;
v___y_899_ = v___x_915_;
goto v___jp_895_;
}
else
{
uint64_t v___x_918_; uint8_t v___x_919_; 
v___x_918_ = 123ULL;
v___x_919_ = lean_uint64_dec_le(v___x_915_, v___x_918_);
if (v___x_919_ == 0)
{
v___y_896_ = v___x_914_;
v___y_897_ = v___y_909_;
v___y_898_ = v___y_910_;
v___y_899_ = v___x_915_;
goto v___jp_895_;
}
else
{
uint64_t v___x_920_; uint8_t v___x_921_; 
v___x_920_ = 0ULL;
v___x_921_ = lean_uint64_dec_eq(v___x_914_, v___x_920_);
if (v___x_921_ == 0)
{
uint64_t v___x_922_; uint64_t v___x_923_; uint8_t v___x_924_; 
v___x_922_ = 149ULL;
v___x_923_ = lean_uint64_sub(v___x_922_, v___x_915_);
v___x_924_ = lean_uint64_dec_eq(v___x_923_, v___x_920_);
if (v___x_924_ == 0)
{
uint64_t v___x_925_; uint8_t v___x_926_; 
v___x_925_ = 64ULL;
v___x_926_ = lean_uint64_dec_lt(v___x_923_, v___x_925_);
if (v___x_926_ == 0)
{
uint8_t v___x_927_; 
v___x_927_ = lean_uint64_dec_eq(v___x_923_, v___x_925_);
if (v___x_927_ == 0)
{
v___y_642_ = v___x_920_;
v___y_643_ = v___y_909_;
v___y_644_ = v___y_910_;
v___y_645_ = v___x_920_;
goto v___jp_641_;
}
else
{
uint64_t v___x_928_; uint8_t v___x_929_; 
v___x_928_ = 9223372036854775808ULL;
v___x_929_ = lean_uint64_dec_lt(v___x_928_, v___x_914_);
if (v___x_929_ == 0)
{
v___y_642_ = v___x_920_;
v___y_643_ = v___y_909_;
v___y_644_ = v___y_910_;
v___y_645_ = v___x_920_;
goto v___jp_641_;
}
else
{
uint64_t v___x_930_; 
v___x_930_ = 1ULL;
v___y_642_ = v___x_920_;
v___y_643_ = v___y_909_;
v___y_644_ = v___y_910_;
v___y_645_ = v___x_930_;
goto v___jp_641_;
}
}
}
else
{
uint64_t v_quotient_931_; uint64_t v___x_932_; uint64_t v___x_933_; uint64_t v___x_934_; uint64_t v_remainder_935_; uint64_t v___x_936_; uint64_t v_half_937_; uint8_t v___x_938_; 
v_quotient_931_ = lean_uint64_shift_right(v___x_914_, v___x_923_);
v___x_932_ = 1ULL;
v___x_933_ = lean_uint64_shift_left(v___x_932_, v___x_923_);
v___x_934_ = lean_uint64_sub(v___x_933_, v___x_932_);
v_remainder_935_ = lean_uint64_land(v___x_914_, v___x_934_);
v___x_936_ = lean_uint64_sub(v___x_923_, v___x_932_);
v_half_937_ = lean_uint64_shift_left(v___x_932_, v___x_936_);
v___x_938_ = lean_uint64_dec_lt(v_remainder_935_, v_half_937_);
if (v___x_938_ == 0)
{
uint8_t v___x_939_; 
v___x_939_ = lean_uint64_dec_lt(v_half_937_, v_remainder_935_);
if (v___x_939_ == 0)
{
uint64_t v___x_940_; uint8_t v___x_941_; 
v___x_940_ = lean_uint64_land(v_quotient_931_, v___x_932_);
v___x_941_ = lean_uint64_dec_eq(v___x_940_, v___x_920_);
if (v___x_941_ == 0)
{
uint64_t v___x_942_; 
v___x_942_ = lean_uint64_add(v_quotient_931_, v___x_932_);
v___y_642_ = v___x_920_;
v___y_643_ = v___y_909_;
v___y_644_ = v___y_910_;
v___y_645_ = v___x_942_;
goto v___jp_641_;
}
else
{
v___y_642_ = v___x_920_;
v___y_643_ = v___y_909_;
v___y_644_ = v___y_910_;
v___y_645_ = v_quotient_931_;
goto v___jp_641_;
}
}
else
{
uint64_t v___x_943_; 
v___x_943_ = lean_uint64_add(v_quotient_931_, v___x_932_);
v___y_642_ = v___x_920_;
v___y_643_ = v___y_909_;
v___y_644_ = v___y_910_;
v___y_645_ = v___x_943_;
goto v___jp_641_;
}
}
else
{
v___y_642_ = v___x_920_;
v___y_643_ = v___y_909_;
v___y_644_ = v___y_910_;
v___y_645_ = v_quotient_931_;
goto v___jp_641_;
}
}
}
else
{
v___y_642_ = v___x_920_;
v___y_643_ = v___y_909_;
v___y_644_ = v___y_910_;
v___y_645_ = v___x_914_;
goto v___jp_641_;
}
}
else
{
if (v___y_910_ == 0)
{
uint32_t v___x_944_; 
v___x_944_ = 0;
return v___x_944_;
}
else
{
uint32_t v___x_945_; 
v___x_945_ = 2147483648;
return v___x_945_;
}
}
}
}
}
v___jp_949_:
{
uint8_t v___x_950_; 
v___x_950_ = lean_uint32_dec_eq(v_ey_948_, v___x_663_);
if (v___x_950_ == 0)
{
v___y_657_ = v___x_950_;
goto v___jp_656_;
}
else
{
uint32_t v___x_951_; uint32_t v___x_952_; uint32_t v___x_953_; uint8_t v___x_954_; 
v___x_951_ = 8388607;
v___x_952_ = lean_uint32_land(v___y_605_, v___x_951_);
v___x_953_ = 0;
v___x_954_ = lean_uint32_dec_eq(v___x_952_, v___x_953_);
if (v___x_954_ == 0)
{
v___y_657_ = v___x_950_;
goto v___jp_656_;
}
else
{
uint32_t v___x_955_; 
v___x_955_ = lp_competition_Submission_FastMul_mul(v___y_604_, v___y_605_);
return v___x_955_;
}
}
}
v___jp_956_:
{
if (v___y_957_ == 0)
{
goto v___jp_949_;
}
else
{
uint32_t v___x_958_; uint32_t v___x_959_; 
v___x_958_ = 4194304;
v___x_959_ = lean_uint32_lor(v___y_604_, v___x_958_);
return v___x_959_;
}
}
v___jp_960_:
{
uint8_t v___x_961_; 
v___x_961_ = lean_uint32_dec_eq(v_ex_946_, v___x_663_);
if (v___x_961_ == 0)
{
v___y_957_ = v___x_961_;
goto v___jp_956_;
}
else
{
uint32_t v___x_962_; uint32_t v___x_963_; uint32_t v___x_964_; uint8_t v___x_965_; 
v___x_962_ = 8388607;
v___x_963_ = lean_uint32_land(v___y_604_, v___x_962_);
v___x_964_ = 0;
v___x_965_ = lean_uint32_dec_eq(v___x_963_, v___x_964_);
if (v___x_965_ == 0)
{
v___y_957_ = v___x_961_;
goto v___jp_956_;
}
else
{
goto v___jp_949_;
}
}
}
v___jp_966_:
{
if (v___y_967_ == 0)
{
goto v___jp_960_;
}
else
{
uint32_t v___x_968_; uint32_t v___x_969_; uint32_t v___x_970_; uint8_t v___x_971_; 
v___x_968_ = 4194304;
v___x_969_ = lean_uint32_land(v___y_605_, v___x_968_);
v___x_970_ = 0;
v___x_971_ = lean_uint32_dec_eq(v___x_969_, v___x_970_);
if (v___x_971_ == 0)
{
goto v___jp_960_;
}
else
{
uint32_t v___x_972_; 
v___x_972_ = lean_uint32_lor(v___y_605_, v___x_968_);
return v___x_972_;
}
}
}
v___jp_973_:
{
uint8_t v___x_974_; 
v___x_974_ = lean_uint32_dec_eq(v_ey_948_, v___x_663_);
if (v___x_974_ == 0)
{
v___y_967_ = v___x_974_;
goto v___jp_966_;
}
else
{
uint32_t v___x_975_; uint32_t v___x_976_; uint32_t v___x_977_; uint8_t v___x_978_; 
v___x_975_ = 8388607;
v___x_976_ = lean_uint32_land(v___y_605_, v___x_975_);
v___x_977_ = 0;
v___x_978_ = lean_uint32_dec_eq(v___x_976_, v___x_977_);
if (v___x_978_ == 0)
{
v___y_967_ = v___x_974_;
goto v___jp_966_;
}
else
{
goto v___jp_960_;
}
}
}
v___jp_979_:
{
if (v___y_980_ == 0)
{
goto v___jp_973_;
}
else
{
uint32_t v___x_981_; uint32_t v___x_982_; uint32_t v___x_983_; uint8_t v___x_984_; 
v___x_981_ = 4194304;
v___x_982_ = lean_uint32_land(v___y_604_, v___x_981_);
v___x_983_ = 0;
v___x_984_ = lean_uint32_dec_eq(v___x_982_, v___x_983_);
if (v___x_984_ == 0)
{
goto v___jp_973_;
}
else
{
uint32_t v___x_985_; 
v___x_985_ = lean_uint32_lor(v___y_604_, v___x_981_);
return v___x_985_;
}
}
}
v___jp_986_:
{
uint64_t v___x_992_; uint64_t v___x_993_; uint8_t v___x_994_; 
v___x_992_ = lean_uint32_to_uint64(v_ey_948_);
v___x_993_ = 0ULL;
v___x_994_ = lean_uint64_dec_eq(v___x_992_, v___x_993_);
if (v___x_994_ == 0)
{
uint64_t v___x_995_; uint64_t v___x_996_; 
v___x_995_ = 1ULL;
v___x_996_ = lean_uint64_sub(v___x_992_, v___x_995_);
v___y_908_ = v___y_987_;
v___y_909_ = v___y_988_;
v___y_910_ = v___y_989_;
v___y_911_ = v___y_990_;
v___y_912_ = v___y_991_;
v___y_913_ = v___x_996_;
goto v___jp_907_;
}
else
{
v___y_908_ = v___y_987_;
v___y_909_ = v___y_988_;
v___y_910_ = v___y_989_;
v___y_911_ = v___y_990_;
v___y_912_ = v___y_991_;
v___y_913_ = v___x_993_;
goto v___jp_907_;
}
}
v___jp_997_:
{
uint64_t v___x_1002_; uint64_t v___x_1003_; uint8_t v___x_1004_; 
v___x_1002_ = lean_uint32_to_uint64(v_ex_946_);
v___x_1003_ = 0ULL;
v___x_1004_ = lean_uint64_dec_eq(v___x_1002_, v___x_1003_);
if (v___x_1004_ == 0)
{
uint64_t v___x_1005_; uint64_t v___x_1006_; 
v___x_1005_ = 1ULL;
v___x_1006_ = lean_uint64_sub(v___x_1002_, v___x_1005_);
v___y_987_ = v___y_1001_;
v___y_988_ = v___y_998_;
v___y_989_ = v___y_999_;
v___y_990_ = v___y_1000_;
v___y_991_ = v___x_1006_;
goto v___jp_986_;
}
else
{
v___y_987_ = v___y_1001_;
v___y_988_ = v___y_998_;
v___y_989_ = v___y_999_;
v___y_990_ = v___y_1000_;
v___y_991_ = v___x_1003_;
goto v___jp_986_;
}
}
v___jp_1007_:
{
uint32_t v___x_1012_; uint8_t v___x_1013_; 
v___x_1012_ = 0;
v___x_1013_ = lean_uint32_dec_eq(v_ey_948_, v___x_1012_);
if (v___x_1013_ == 0)
{
uint64_t v___x_1014_; uint64_t v___x_1015_; uint64_t v___x_1016_; 
v___x_1014_ = lean_uint32_to_uint64(v___y_1009_);
v___x_1015_ = 8388608ULL;
v___x_1016_ = lean_uint64_lor(v___x_1014_, v___x_1015_);
v___y_998_ = v___y_1008_;
v___y_999_ = v___y_1010_;
v___y_1000_ = v___y_1011_;
v___y_1001_ = v___x_1016_;
goto v___jp_997_;
}
else
{
uint64_t v___x_1017_; 
v___x_1017_ = lean_uint32_to_uint64(v___y_1009_);
v___y_998_ = v___y_1008_;
v___y_999_ = v___y_1010_;
v___y_1000_ = v___y_1011_;
v___y_1001_ = v___x_1017_;
goto v___jp_997_;
}
}
v___jp_1018_:
{
uint32_t v___x_1020_; uint32_t v_xFraction_1021_; uint32_t v_yFraction_1022_; uint32_t v___x_1023_; uint8_t v___x_1024_; 
v___x_1020_ = 8388607;
v_xFraction_1021_ = lean_uint32_land(v___y_604_, v___x_1020_);
v_yFraction_1022_ = lean_uint32_land(v___y_605_, v___x_1020_);
v___x_1023_ = 0;
v___x_1024_ = lean_uint32_dec_eq(v_ex_946_, v___x_1023_);
if (v___x_1024_ == 0)
{
uint64_t v___x_1025_; uint64_t v___x_1026_; uint64_t v___x_1027_; 
v___x_1025_ = lean_uint32_to_uint64(v_xFraction_1021_);
v___x_1026_ = 8388608ULL;
v___x_1027_ = lean_uint64_lor(v___x_1025_, v___x_1026_);
v___y_1008_ = v___x_1020_;
v___y_1009_ = v_yFraction_1022_;
v___y_1010_ = v___y_1019_;
v___y_1011_ = v___x_1027_;
goto v___jp_1007_;
}
else
{
uint64_t v___x_1028_; 
v___x_1028_ = lean_uint32_to_uint64(v_xFraction_1021_);
v___y_1008_ = v___x_1020_;
v___y_1009_ = v_yFraction_1022_;
v___y_1010_ = v___y_1019_;
v___y_1011_ = v___x_1028_;
goto v___jp_1007_;
}
}
v___jp_1032_:
{
if (v___y_1034_ == 0)
{
v___y_1019_ = v___x_1031_;
goto v___jp_1018_;
}
else
{
v___y_1019_ = v___y_1033_;
goto v___jp_1018_;
}
}
v___jp_1035_:
{
if (v___y_1036_ == 0)
{
if (v___y_1038_ == 0)
{
v___y_1033_ = v___y_1037_;
v___y_1034_ = v___x_1031_;
goto v___jp_1032_;
}
else
{
v___y_1019_ = v___x_1031_;
goto v___jp_1018_;
}
}
else
{
v___y_1033_ = v___y_1037_;
v___y_1034_ = v___y_1038_;
goto v___jp_1032_;
}
}
v___jp_1039_:
{
uint32_t v___x_1042_; uint32_t v___x_1043_; uint32_t v___x_1044_; uint8_t v___x_1045_; 
v___x_1042_ = 2147483648;
v___x_1043_ = lean_uint32_land(v___y_605_, v___x_1042_);
v___x_1044_ = 0;
v___x_1045_ = lean_uint32_dec_eq(v___x_1043_, v___x_1044_);
if (v___x_1045_ == 0)
{
v___y_1036_ = v___y_1041_;
v___y_1037_ = v___y_1040_;
v___y_1038_ = v___x_1031_;
goto v___jp_1035_;
}
else
{
v___y_1036_ = v___y_1041_;
v___y_1037_ = v___y_1040_;
v___y_1038_ = v___y_1040_;
goto v___jp_1035_;
}
}
v___jp_1046_:
{
if (v___y_1047_ == 0)
{
uint32_t v___x_1048_; uint32_t v___x_1049_; uint32_t v___x_1050_; uint8_t v___x_1051_; 
v___x_1048_ = 2147483648;
v___x_1049_ = lean_uint32_land(v___y_604_, v___x_1048_);
v___x_1050_ = 0;
v___x_1051_ = lean_uint32_dec_eq(v___x_1049_, v___x_1050_);
if (v___x_1051_ == 0)
{
v___y_1040_ = v___y_1047_;
v___y_1041_ = v___x_1031_;
goto v___jp_1039_;
}
else
{
v___y_1040_ = v___y_1047_;
v___y_1041_ = v___y_1047_;
goto v___jp_1039_;
}
}
else
{
lean_object* v___x_1052_; lean_object* v___x_1053_; lean_object* v___x_1054_; uint32_t v___x_1055_; 
v___x_1052_ = lean_uint32_to_nat(v___y_604_);
v___x_1053_ = lean_uint32_to_nat(v___y_605_);
v___x_1054_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1052_, v___x_1053_);
v___x_1055_ = lean_uint32_of_nat(v___x_1054_);
lean_dec(v___x_1054_);
return v___x_1055_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_1072_, lean_object* v___y_1073_){
_start:
{
uint32_t v___y_5419__boxed_1074_; uint32_t v___y_5420__boxed_1075_; uint32_t v_res_1076_; lean_object* v_r_1077_; 
v___y_5419__boxed_1074_ = lean_unbox_uint32(v___y_1072_);
lean_dec(v___y_1072_);
v___y_5420__boxed_1075_ = lean_unbox_uint32(v___y_1073_);
lean_dec(v___y_1073_);
v_res_1076_ = lp_competition_main___lam__3(v___y_5419__boxed_1074_, v___y_5420__boxed_1075_);
v_r_1077_ = lean_box_uint32(v_res_1076_);
return v_r_1077_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1085_; lean_object* v___x_1086_; 
v___x_1085_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1086_ = lean_io_getenv(v___x_1085_);
if (lean_obj_tag(v___x_1086_) == 0)
{
lean_object* v___f_1087_; lean_object* v___f_1088_; lean_object* v___x_1089_; lean_object* v___x_1090_; lean_object* v___x_1091_; 
v___f_1087_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1088_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1089_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1090_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1091_ = lp_competition_Bench_runFull(v___f_1087_, v___f_1088_, v___x_1089_, v___x_1090_);
return v___x_1091_;
}
else
{
lean_object* v___f_1092_; lean_object* v___f_1093_; lean_object* v___x_1094_; lean_object* v___x_1095_; lean_object* v___x_1096_; 
lean_dec_ref_known(v___x_1086_, 1);
v___f_1092_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1093_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1094_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1095_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1096_ = lp_competition_Bench_Suite_run(v___f_1092_, v___f_1093_, v___x_1094_, v___x_1095_);
return v___x_1096_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1097_){
_start:
{
lean_object* v_res_1098_; 
v_res_1098_ = _lean_main();
return v_res_1098_;
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
