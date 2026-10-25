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
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
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
uint32_t v___y_8953__boxed_126_; uint32_t v___y_8954__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_8953__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_8954__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_main___lam__0(v___y_8953__boxed_126_, v___y_8954__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_130_, uint32_t v___y_131_){
_start:
{
uint32_t v___y_133_; uint32_t v___y_137_; uint32_t v___y_141_; uint32_t v___y_145_; uint32_t v___y_149_; uint32_t v___y_150_; uint32_t v___y_151_; uint32_t v___y_155_; uint64_t v___y_156_; uint8_t v___y_157_; uint64_t v___y_158_; uint32_t v___y_170_; uint32_t v___y_171_; uint32_t v___y_172_; uint32_t v___y_173_; uint32_t v___y_174_; uint32_t v___y_175_; uint32_t v___y_182_; uint32_t v___y_183_; uint32_t v___y_184_; uint32_t v___y_185_; uint8_t v___y_186_; uint32_t v___y_187_; uint32_t v___y_191_; uint32_t v___y_192_; uint64_t v___y_193_; uint64_t v___y_194_; uint32_t v___y_195_; uint8_t v___y_196_; uint64_t v___y_197_; uint64_t v___y_207_; uint32_t v___y_208_; uint32_t v___y_209_; uint8_t v___y_210_; uint32_t v___y_211_; uint64_t v___y_212_; uint8_t v___y_213_; uint64_t v___y_214_; uint32_t v___y_221_; uint32_t v___y_222_; uint64_t v___y_223_; uint64_t v___y_224_; uint32_t v___y_225_; uint8_t v___y_226_; uint64_t v___y_227_; uint32_t v___y_233_; uint64_t v___y_234_; uint32_t v___y_235_; uint64_t v___y_236_; uint32_t v___y_237_; uint64_t v___y_238_; uint8_t v___y_239_; uint64_t v___y_240_; uint32_t v___y_295_; uint64_t v___y_296_; uint64_t v___y_297_; uint32_t v___y_298_; uint32_t v___y_299_; uint64_t v___y_300_; uint64_t v___y_301_; uint8_t v___y_302_; uint64_t v___y_303_; uint64_t v___y_309_; uint32_t v___y_310_; uint64_t v___y_311_; uint32_t v___y_312_; uint64_t v___y_313_; uint64_t v___y_314_; uint32_t v___y_315_; uint64_t v___y_316_; uint8_t v___y_317_; uint64_t v___y_318_; uint64_t v___y_319_; uint32_t v___y_324_; uint64_t v___y_325_; uint64_t v___y_326_; uint32_t v___y_327_; uint32_t v___y_328_; uint64_t v___y_329_; uint64_t v___y_330_; uint8_t v___y_331_; uint64_t v___y_332_; uint64_t v___y_337_; uint32_t v___y_338_; uint64_t v___y_339_; uint32_t v___y_340_; uint64_t v___y_341_; uint64_t v___y_342_; uint64_t v___y_343_; uint64_t v___y_344_; uint32_t v___y_345_; uint8_t v___y_346_; uint64_t v___y_347_; uint32_t v___y_352_; uint64_t v___y_353_; uint64_t v___y_354_; uint32_t v___y_355_; uint64_t v___y_356_; uint32_t v___y_357_; uint64_t v___y_358_; uint8_t v___y_359_; uint64_t v___y_360_; uint32_t v___y_365_; uint64_t v___y_366_; uint64_t v___y_367_; uint64_t v___y_368_; uint32_t v___y_369_; uint64_t v___y_370_; uint64_t v___y_371_; uint32_t v___y_372_; uint8_t v___y_373_; uint64_t v___y_374_; uint64_t v___y_375_; uint32_t v___y_380_; uint64_t v___y_381_; uint64_t v___y_382_; uint32_t v___y_383_; uint32_t v___y_384_; uint64_t v___y_385_; uint8_t v___y_386_; uint64_t v___y_387_; uint64_t v___y_388_; uint64_t v___y_393_; uint64_t v___y_394_; uint32_t v___y_395_; uint64_t v___y_396_; uint32_t v___y_397_; uint64_t v___y_398_; uint64_t v___y_399_; uint32_t v___y_400_; uint64_t v___y_401_; uint8_t v___y_402_; uint64_t v___y_403_; uint64_t v___y_408_; uint32_t v___y_409_; uint64_t v___y_410_; uint64_t v___y_411_; uint32_t v___y_412_; uint32_t v___y_413_; uint64_t v___y_414_; uint8_t v___y_415_; uint64_t v___y_416_; uint32_t v___y_421_; uint64_t v___y_422_; uint32_t v___y_423_; uint64_t v___y_424_; uint64_t v___y_425_; uint64_t v___y_426_; uint32_t v___y_427_; uint8_t v___y_428_; uint64_t v___y_429_; uint32_t v___y_433_; uint64_t v___y_434_; uint64_t v___y_435_; uint32_t v___y_436_; uint32_t v___y_437_; uint8_t v___y_438_; uint32_t v___y_447_; uint32_t v___y_448_; uint32_t v___y_449_; uint32_t v___y_453_; uint64_t v___y_454_; uint8_t v___y_455_; uint64_t v___y_456_; uint32_t v___y_468_; uint64_t v___y_469_; uint32_t v___y_470_; uint32_t v___y_471_; uint8_t v___y_472_; uint64_t v___y_473_; uint64_t v___y_474_; uint64_t v___y_475_; uint32_t v___y_509_; uint32_t v___y_510_; uint32_t v___y_511_; uint32_t v___y_512_; uint8_t v___y_513_; uint64_t v___y_514_; uint64_t v___y_515_; uint64_t v___y_516_; uint32_t v___y_523_; uint32_t v___y_524_; uint32_t v___y_525_; uint32_t v___y_526_; uint8_t v___y_527_; uint32_t v___y_528_; uint64_t v___y_529_; uint64_t v___y_530_; uint32_t v___y_537_; uint32_t v___y_538_; uint32_t v___y_539_; uint32_t v___y_540_; uint32_t v___y_541_; uint8_t v___y_542_; uint32_t v___y_543_; uint64_t v___y_544_; uint32_t v___y_552_; uint32_t v___y_553_; uint32_t v___y_554_; uint32_t v___y_555_; uint32_t v___y_556_; uint32_t v___y_557_; uint32_t v___y_564_; uint32_t v___y_565_; uint64_t v___y_566_; uint64_t v___y_567_; uint64_t v___y_568_; uint32_t v___y_569_; uint32_t v___y_570_; uint8_t v___y_571_; uint32_t v___y_583_; uint32_t v___y_584_; uint64_t v___y_585_; uint64_t v___y_586_; uint64_t v___y_587_; uint32_t v___y_588_; uint32_t v___y_589_; uint32_t v___y_592_; uint32_t v___y_593_; uint64_t v___y_594_; uint64_t v___y_595_; uint64_t v___y_596_; uint32_t v___y_597_; uint8_t v___y_598_; uint32_t v___y_599_; uint8_t v___y_600_; uint32_t v___y_602_; uint32_t v___y_603_; uint32_t v___y_604_; uint8_t v___y_608_; uint64_t v___y_609_; uint32_t v___y_610_; uint64_t v___y_611_; uint32_t v___y_623_; uint32_t v___y_624_; uint32_t v___y_625_; uint32_t v___y_626_; uint32_t v___y_627_; uint32_t v___y_628_; uint32_t v___y_635_; uint8_t v___y_636_; uint32_t v___y_637_; uint32_t v___y_638_; uint32_t v___y_639_; uint32_t v___y_640_; uint32_t v___y_644_; uint8_t v___y_645_; uint64_t v___y_646_; uint32_t v___y_647_; uint32_t v___y_648_; uint64_t v___y_649_; uint64_t v___y_650_; uint64_t v___y_660_; uint8_t v___y_661_; uint32_t v___y_662_; uint8_t v___y_663_; uint64_t v___y_664_; uint32_t v___y_665_; uint32_t v___y_666_; uint64_t v___y_667_; uint32_t v___y_674_; uint8_t v___y_675_; uint64_t v___y_676_; uint32_t v___y_677_; uint32_t v___y_678_; uint64_t v___y_679_; uint64_t v___y_680_; uint64_t v___y_686_; uint64_t v___y_687_; uint32_t v___y_688_; uint8_t v___y_689_; uint64_t v___y_690_; uint32_t v___y_691_; uint32_t v___y_692_; uint64_t v___y_693_; uint64_t v___y_748_; uint64_t v___y_749_; uint64_t v___y_750_; uint32_t v___y_751_; uint8_t v___y_752_; uint64_t v___y_753_; uint32_t v___y_754_; uint32_t v___y_755_; uint64_t v___y_756_; uint64_t v___y_762_; uint64_t v___y_763_; uint64_t v___y_764_; uint32_t v___y_765_; uint8_t v___y_766_; uint64_t v___y_767_; uint64_t v___y_768_; uint64_t v___y_769_; uint32_t v___y_770_; uint32_t v___y_771_; uint64_t v___y_772_; uint64_t v___y_777_; uint64_t v___y_778_; uint32_t v___y_779_; uint8_t v___y_780_; uint64_t v___y_781_; uint64_t v___y_782_; uint32_t v___y_783_; uint32_t v___y_784_; uint64_t v___y_785_; uint64_t v___y_790_; uint64_t v___y_791_; uint32_t v___y_792_; uint8_t v___y_793_; uint64_t v___y_794_; uint32_t v___y_795_; uint64_t v___y_796_; uint32_t v___y_797_; uint64_t v___y_798_; uint64_t v___y_799_; uint64_t v___y_800_; uint64_t v___y_805_; uint64_t v___y_806_; uint32_t v___y_807_; uint8_t v___y_808_; uint64_t v___y_809_; uint32_t v___y_810_; uint32_t v___y_811_; uint64_t v___y_812_; uint64_t v___y_813_; uint64_t v___y_818_; uint64_t v___y_819_; uint64_t v___y_820_; uint64_t v___y_821_; uint32_t v___y_822_; uint8_t v___y_823_; uint64_t v___y_824_; uint64_t v___y_825_; uint32_t v___y_826_; uint32_t v___y_827_; uint64_t v___y_828_; uint64_t v___y_833_; uint64_t v___y_834_; uint64_t v___y_835_; uint32_t v___y_836_; uint8_t v___y_837_; uint64_t v___y_838_; uint32_t v___y_839_; uint32_t v___y_840_; uint64_t v___y_841_; uint64_t v___y_846_; uint64_t v___y_847_; uint32_t v___y_848_; uint8_t v___y_849_; uint64_t v___y_850_; uint32_t v___y_851_; uint64_t v___y_852_; uint32_t v___y_853_; uint64_t v___y_854_; uint64_t v___y_855_; uint64_t v___y_856_; uint64_t v___y_861_; uint64_t v___y_862_; uint32_t v___y_863_; uint8_t v___y_864_; uint64_t v___y_865_; uint32_t v___y_866_; uint32_t v___y_867_; uint64_t v___y_868_; uint64_t v___y_869_; uint64_t v___y_874_; uint64_t v___y_875_; uint32_t v___y_876_; uint8_t v___y_877_; uint64_t v___y_878_; uint64_t v___y_879_; uint32_t v___y_880_; uint32_t v___y_881_; uint64_t v___y_882_; uint64_t v___y_886_; uint64_t v___y_887_; uint32_t v___y_888_; uint8_t v___y_889_; uint32_t v___y_890_; uint32_t v___y_891_; uint32_t v___y_900_; uint32_t v___y_901_; uint32_t v___y_902_; uint8_t v___y_906_; uint64_t v___y_907_; uint32_t v___y_908_; uint64_t v___y_909_; uint64_t v___y_921_; uint64_t v___y_922_; uint32_t v___y_923_; uint8_t v___y_924_; uint32_t v___y_925_; uint32_t v___y_926_; uint64_t v___y_927_; uint64_t v___y_928_; uint64_t v___y_962_; uint64_t v___y_963_; uint32_t v___y_964_; uint8_t v___y_965_; uint32_t v___y_966_; uint32_t v___y_967_; uint32_t v___y_968_; uint64_t v___y_969_; uint64_t v___y_976_; uint32_t v___y_977_; uint8_t v___y_978_; uint32_t v___y_979_; uint32_t v___y_980_; uint32_t v___y_981_; uint32_t v___y_982_; uint64_t v___y_983_; uint32_t v___y_990_; uint8_t v___y_991_; uint32_t v___y_992_; uint32_t v___y_993_; uint32_t v___y_994_; uint32_t v___y_995_; uint32_t v___y_996_; uint64_t v___y_997_; uint32_t v___y_1005_; uint32_t v___y_1006_; uint32_t v___y_1007_; uint32_t v___y_1008_; uint8_t v___y_1009_; uint8_t v___y_1020_; uint8_t v___y_1021_; uint32_t v___y_1022_; uint32_t v___y_1023_; uint32_t v___y_1024_; uint32_t v___y_1025_; uint8_t v___y_1026_; uint8_t v___y_1027_; uint8_t v___y_1029_; uint8_t v___y_1030_; uint32_t v___y_1031_; uint32_t v___y_1032_; uint32_t v___y_1033_; uint32_t v___y_1034_; uint8_t v___y_1035_; uint8_t v___y_1041_; uint32_t v___y_1042_; uint32_t v___y_1043_; uint32_t v___y_1044_; uint32_t v___y_1045_; uint8_t v___y_1046_; uint32_t v___y_1056_; uint8_t v___y_1057_; uint32_t v___y_1058_; uint32_t v___y_1059_; uint64_t v___y_1060_; uint64_t v___y_1078_; uint32_t v___y_1079_; uint64_t v___y_1080_; uint32_t v___y_1081_; uint8_t v___y_1082_; uint64_t v___y_1083_; uint32_t v___y_1084_; uint64_t v___y_1085_; uint32_t v___y_1090_; uint64_t v___y_1091_; uint64_t v___y_1092_; uint8_t v___y_1093_; uint32_t v___y_1094_; uint64_t v___y_1095_; uint32_t v___y_1096_; uint64_t v___y_1097_; uint8_t v___y_1102_; uint32_t v___y_1103_; uint64_t v___y_1104_; uint32_t v___y_1105_; uint8_t v___y_1106_; uint64_t v___y_1107_; uint32_t v___y_1108_; uint64_t v___y_1109_; uint64_t v___y_1112_; uint32_t v___y_1113_; uint32_t v___y_1114_; uint8_t v___y_1115_; uint64_t v___y_1116_; uint64_t v___y_1117_; uint32_t v___y_1118_; uint64_t v___y_1119_; uint64_t v___y_1124_; uint32_t v___y_1125_; uint8_t v___y_1126_; uint32_t v___y_1127_; uint64_t v___y_1128_; uint64_t v___y_1129_; uint32_t v___y_1130_; uint64_t v___y_1131_; uint8_t v___y_1136_; uint64_t v___y_1137_; uint32_t v___y_1138_; uint32_t v___y_1139_; uint8_t v___y_1140_; uint64_t v___y_1141_; uint32_t v___y_1142_; uint64_t v___y_1143_; uint32_t v___y_1146_; uint32_t v___y_1147_; uint32_t v___y_1148_; uint32_t v___y_1149_; uint8_t v___y_1150_; uint32_t v___y_1161_; uint32_t v___y_1162_; uint32_t v___y_1163_; uint32_t v___y_1164_; uint32_t v___y_1167_; uint32_t v___y_1168_; uint32_t v___y_1169_; uint8_t v___y_1170_; uint8_t v___y_1171_; uint32_t v___y_1172_; uint8_t v___y_1173_; uint32_t v___y_1175_; uint32_t v___y_1176_; uint32_t v___y_1177_; uint8_t v___y_1178_; uint32_t v___y_1179_; uint8_t v___y_1180_; uint32_t v___y_1187_; uint32_t v___y_1188_; uint32_t v___y_1189_; uint32_t v___y_1190_; uint8_t v___y_1191_; uint8_t v___y_1202_; uint8_t v___y_1218_; uint8_t v___y_1232_; uint8_t v___y_1249_; float v___y_1256_; float v___y_1257_; float v___y_1271_; uint8_t v___y_1272_; float v___y_1287_; uint32_t v___y_1297_; uint8_t v___y_1298_; uint8_t v___y_1311_; uint8_t v___y_1327_; uint8_t v___y_1341_; uint8_t v___y_1358_; float v___y_1365_; float v___y_1366_; float v___y_1380_; uint8_t v___y_1381_; float v___y_1396_; uint32_t v___y_1406_; uint8_t v___y_1407_; uint8_t v___y_1420_; uint32_t v___x_1501_; uint32_t v___x_1502_; uint32_t v___x_1503_; uint32_t v___x_1504_; uint32_t v___x_1505_; uint32_t v___x_1506_; uint32_t v___x_1507_; uint8_t v___x_1508_; 
v___x_1501_ = 23;
v___x_1502_ = lean_uint32_shift_right(v___y_130_, v___x_1501_);
v___x_1503_ = 255;
v___x_1504_ = lean_uint32_land(v___x_1502_, v___x_1503_);
v___x_1505_ = 1;
v___x_1506_ = lean_uint32_sub(v___x_1504_, v___x_1505_);
v___x_1507_ = 253;
v___x_1508_ = lean_uint32_dec_le(v___x_1506_, v___x_1507_);
if (v___x_1508_ == 0)
{
v___y_1420_ = v___x_1508_;
goto v___jp_1419_;
}
else
{
uint32_t v___x_1509_; uint32_t v___x_1510_; uint32_t v___x_1511_; uint8_t v___x_1512_; 
v___x_1509_ = lean_uint32_shift_right(v___y_131_, v___x_1501_);
v___x_1510_ = lean_uint32_land(v___x_1509_, v___x_1503_);
v___x_1511_ = lean_uint32_sub(v___x_1510_, v___x_1505_);
v___x_1512_ = lean_uint32_dec_le(v___x_1511_, v___x_1507_);
v___y_1420_ = v___x_1512_;
goto v___jp_1419_;
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
uint32_t v___x_142_; uint32_t v___x_143_; 
v___x_142_ = 8388608;
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
uint32_t v___x_152_; uint32_t v___x_153_; 
v___x_152_ = lean_uint32_land(v___y_150_, v___y_149_);
v___x_153_ = lean_uint32_lor(v___y_151_, v___x_152_);
return v___x_153_;
}
v___jp_154_:
{
uint8_t v___x_159_; 
v___x_159_ = lean_uint64_dec_eq(v___y_158_, v___y_156_);
if (v___x_159_ == 0)
{
uint64_t v___x_160_; uint8_t v___x_161_; 
v___x_160_ = 8388608ULL;
v___x_161_ = lean_uint64_dec_eq(v___y_158_, v___x_160_);
if (v___x_161_ == 0)
{
uint32_t v___x_162_; 
v___x_162_ = lean_uint64_to_uint32(v___y_158_);
if (v___y_157_ == 0)
{
uint32_t v___x_163_; 
v___x_163_ = 0;
v___y_149_ = v___y_155_;
v___y_150_ = v___x_162_;
v___y_151_ = v___x_163_;
goto v___jp_148_;
}
else
{
uint32_t v___x_164_; 
v___x_164_ = 2147483648;
v___y_149_ = v___y_155_;
v___y_150_ = v___x_162_;
v___y_151_ = v___x_164_;
goto v___jp_148_;
}
}
else
{
if (v___y_157_ == 0)
{
uint32_t v___x_165_; 
v___x_165_ = 0;
v___y_145_ = v___x_165_;
goto v___jp_144_;
}
else
{
uint32_t v___x_166_; 
v___x_166_ = 2147483648;
v___y_145_ = v___x_166_;
goto v___jp_144_;
}
}
}
else
{
if (v___y_157_ == 0)
{
uint32_t v___x_167_; 
v___x_167_ = 0;
return v___x_167_;
}
else
{
uint32_t v___x_168_; 
v___x_168_ = 2147483648;
return v___x_168_;
}
}
}
v___jp_169_:
{
uint32_t v___x_176_; uint32_t v___x_177_; uint32_t v___x_178_; uint32_t v___x_179_; uint32_t v___x_180_; 
v___x_176_ = lean_uint32_land(v___y_174_, v___y_172_);
v___x_177_ = lean_uint32_shift_left(v___x_176_, v___y_170_);
v___x_178_ = lean_uint32_lor(v___y_175_, v___x_177_);
v___x_179_ = lean_uint32_land(v___y_171_, v___y_173_);
v___x_180_ = lean_uint32_lor(v___x_178_, v___x_179_);
return v___x_180_;
}
v___jp_181_:
{
if (v___y_186_ == 0)
{
uint32_t v___x_188_; 
v___x_188_ = 0;
v___y_170_ = v___y_182_;
v___y_171_ = v___y_187_;
v___y_172_ = v___y_183_;
v___y_173_ = v___y_184_;
v___y_174_ = v___y_185_;
v___y_175_ = v___x_188_;
goto v___jp_169_;
}
else
{
uint32_t v___x_189_; 
v___x_189_ = 2147483648;
v___y_170_ = v___y_182_;
v___y_171_ = v___y_187_;
v___y_172_ = v___y_183_;
v___y_173_ = v___y_184_;
v___y_174_ = v___y_185_;
v___y_175_ = v___x_189_;
goto v___jp_169_;
}
}
v___jp_190_:
{
uint64_t v___x_198_; uint64_t v_encodedExponent_199_; uint32_t v___x_200_; uint64_t v___x_201_; uint8_t v___x_202_; 
v___x_198_ = 171ULL;
v_encodedExponent_199_ = lean_uint64_sub(v___y_193_, v___x_198_);
v___x_200_ = lean_uint64_to_uint32(v_encodedExponent_199_);
v___x_201_ = 8388608ULL;
v___x_202_ = lean_uint64_dec_lt(v___y_197_, v___x_201_);
if (v___x_202_ == 0)
{
uint64_t v___x_203_; uint32_t v___x_204_; 
v___x_203_ = lean_uint64_sub(v___y_197_, v___x_201_);
v___x_204_ = lean_uint64_to_uint32(v___x_203_);
v___y_182_ = v___y_191_;
v___y_183_ = v___y_192_;
v___y_184_ = v___y_195_;
v___y_185_ = v___x_200_;
v___y_186_ = v___y_196_;
v___y_187_ = v___x_204_;
goto v___jp_181_;
}
else
{
uint32_t v___x_205_; 
v___x_205_ = lean_uint64_to_uint32(v___y_194_);
v___y_182_ = v___y_191_;
v___y_183_ = v___y_192_;
v___y_184_ = v___y_195_;
v___y_185_ = v___x_200_;
v___y_186_ = v___y_196_;
v___y_187_ = v___x_205_;
goto v___jp_181_;
}
}
v___jp_206_:
{
uint64_t v___x_215_; uint8_t v___x_216_; 
v___x_215_ = 425ULL;
v___x_216_ = lean_uint64_dec_lt(v___x_215_, v___y_214_);
if (v___x_216_ == 0)
{
if (v___y_210_ == 0)
{
v___y_191_ = v___y_208_;
v___y_192_ = v___y_209_;
v___y_193_ = v___y_214_;
v___y_194_ = v___y_212_;
v___y_195_ = v___y_211_;
v___y_196_ = v___y_213_;
v___y_197_ = v___y_207_;
goto v___jp_190_;
}
else
{
uint64_t v___x_217_; 
v___x_217_ = 8388608ULL;
v___y_191_ = v___y_208_;
v___y_192_ = v___y_209_;
v___y_193_ = v___y_214_;
v___y_194_ = v___y_212_;
v___y_195_ = v___y_211_;
v___y_196_ = v___y_213_;
v___y_197_ = v___x_217_;
goto v___jp_190_;
}
}
else
{
if (v___y_213_ == 0)
{
uint32_t v___x_218_; 
v___x_218_ = 2139095040;
return v___x_218_;
}
else
{
uint32_t v___x_219_; 
v___x_219_ = 4286578688;
return v___x_219_;
}
}
}
v___jp_220_:
{
uint64_t v___x_228_; uint8_t v_carry_229_; 
v___x_228_ = 16777216ULL;
v_carry_229_ = lean_uint64_dec_eq(v___y_227_, v___x_228_);
if (v_carry_229_ == 0)
{
v___y_207_ = v___y_227_;
v___y_208_ = v___y_221_;
v___y_209_ = v___y_222_;
v___y_210_ = v_carry_229_;
v___y_211_ = v___y_225_;
v___y_212_ = v___y_224_;
v___y_213_ = v___y_226_;
v___y_214_ = v___y_223_;
goto v___jp_206_;
}
else
{
uint64_t v___x_230_; uint64_t v___x_231_; 
v___x_230_ = 1ULL;
v___x_231_ = lean_uint64_add(v___y_223_, v___x_230_);
v___y_207_ = v___y_227_;
v___y_208_ = v___y_221_;
v___y_209_ = v___y_222_;
v___y_210_ = v_carry_229_;
v___y_211_ = v___y_225_;
v___y_212_ = v___y_224_;
v___y_213_ = v___y_226_;
v___y_214_ = v___x_231_;
goto v___jp_206_;
}
}
v___jp_232_:
{
uint64_t v_position_241_; uint64_t v___x_242_; uint8_t v___x_243_; 
v_position_241_ = lean_uint64_add(v___y_240_, v___y_236_);
v___x_242_ = 172ULL;
v___x_243_ = lean_uint64_dec_lt(v_position_241_, v___x_242_);
if (v___x_243_ == 0)
{
uint64_t v___x_244_; uint8_t v___x_245_; 
v___x_244_ = 23ULL;
v___x_245_ = lean_uint64_dec_lt(v___y_240_, v___x_244_);
if (v___x_245_ == 0)
{
uint64_t v___x_246_; uint8_t v___x_247_; 
v___x_246_ = lean_uint64_sub(v___y_240_, v___x_244_);
v___x_247_ = lean_uint64_dec_eq(v___x_246_, v___y_238_);
if (v___x_247_ == 0)
{
uint64_t v___x_248_; uint8_t v___x_249_; 
v___x_248_ = 64ULL;
v___x_249_ = lean_uint64_dec_lt(v___x_246_, v___x_248_);
if (v___x_249_ == 0)
{
uint8_t v___x_250_; 
v___x_250_ = lean_uint64_dec_eq(v___x_246_, v___x_248_);
if (v___x_250_ == 0)
{
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v___y_238_;
goto v___jp_220_;
}
else
{
uint64_t v___x_251_; uint8_t v___x_252_; 
v___x_251_ = 9223372036854775808ULL;
v___x_252_ = lean_uint64_dec_lt(v___x_251_, v___y_234_);
if (v___x_252_ == 0)
{
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v___y_238_;
goto v___jp_220_;
}
else
{
uint64_t v___x_253_; 
v___x_253_ = 1ULL;
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v___x_253_;
goto v___jp_220_;
}
}
}
else
{
uint64_t v_quotient_254_; uint64_t v___x_255_; uint64_t v___x_256_; uint64_t v___x_257_; uint64_t v_remainder_258_; uint64_t v___x_259_; uint64_t v_half_260_; uint8_t v___x_261_; 
v_quotient_254_ = lean_uint64_shift_right(v___y_234_, v___x_246_);
v___x_255_ = 1ULL;
v___x_256_ = lean_uint64_shift_left(v___x_255_, v___x_246_);
v___x_257_ = lean_uint64_sub(v___x_256_, v___x_255_);
v_remainder_258_ = lean_uint64_land(v___y_234_, v___x_257_);
v___x_259_ = lean_uint64_sub(v___x_246_, v___x_255_);
v_half_260_ = lean_uint64_shift_left(v___x_255_, v___x_259_);
v___x_261_ = lean_uint64_dec_lt(v_remainder_258_, v_half_260_);
if (v___x_261_ == 0)
{
uint8_t v___x_262_; 
v___x_262_ = lean_uint64_dec_lt(v_half_260_, v_remainder_258_);
if (v___x_262_ == 0)
{
uint64_t v___x_263_; uint8_t v___x_264_; 
v___x_263_ = lean_uint64_land(v_quotient_254_, v___x_255_);
v___x_264_ = lean_uint64_dec_eq(v___x_263_, v___y_238_);
if (v___x_264_ == 0)
{
uint64_t v___x_265_; 
v___x_265_ = lean_uint64_add(v_quotient_254_, v___x_255_);
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v___x_265_;
goto v___jp_220_;
}
else
{
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v_quotient_254_;
goto v___jp_220_;
}
}
else
{
uint64_t v___x_266_; 
v___x_266_ = lean_uint64_add(v_quotient_254_, v___x_255_);
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v___x_266_;
goto v___jp_220_;
}
}
else
{
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v_quotient_254_;
goto v___jp_220_;
}
}
}
else
{
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v___y_234_;
goto v___jp_220_;
}
}
else
{
uint64_t v___x_267_; uint64_t v___x_268_; 
v___x_267_ = lean_uint64_sub(v___x_244_, v___y_240_);
v___x_268_ = lean_uint64_shift_left(v___y_234_, v___x_267_);
v___y_221_ = v___y_233_;
v___y_222_ = v___y_235_;
v___y_223_ = v_position_241_;
v___y_224_ = v___y_238_;
v___y_225_ = v___y_237_;
v___y_226_ = v___y_239_;
v___y_227_ = v___x_268_;
goto v___jp_220_;
}
}
else
{
uint64_t v___x_269_; uint8_t v___x_270_; 
v___x_269_ = 149ULL;
v___x_270_ = lean_uint64_dec_lt(v___y_236_, v___x_269_);
if (v___x_270_ == 0)
{
uint64_t v___x_271_; uint64_t v___x_272_; 
v___x_271_ = lean_uint64_sub(v___y_236_, v___x_269_);
v___x_272_ = lean_uint64_shift_left(v___y_234_, v___x_271_);
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v___x_272_;
goto v___jp_154_;
}
else
{
uint64_t v___x_273_; uint8_t v___x_274_; 
v___x_273_ = lean_uint64_sub(v___x_269_, v___y_236_);
v___x_274_ = lean_uint64_dec_eq(v___x_273_, v___y_238_);
if (v___x_274_ == 0)
{
uint64_t v___x_275_; uint8_t v___x_276_; 
v___x_275_ = 64ULL;
v___x_276_ = lean_uint64_dec_lt(v___x_273_, v___x_275_);
if (v___x_276_ == 0)
{
uint8_t v___x_277_; 
v___x_277_ = lean_uint64_dec_eq(v___x_273_, v___x_275_);
if (v___x_277_ == 0)
{
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v___y_238_;
goto v___jp_154_;
}
else
{
uint64_t v___x_278_; uint8_t v___x_279_; 
v___x_278_ = 9223372036854775808ULL;
v___x_279_ = lean_uint64_dec_lt(v___x_278_, v___y_234_);
if (v___x_279_ == 0)
{
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v___y_238_;
goto v___jp_154_;
}
else
{
uint64_t v___x_280_; 
v___x_280_ = 1ULL;
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v___x_280_;
goto v___jp_154_;
}
}
}
else
{
uint64_t v_quotient_281_; uint64_t v___x_282_; uint64_t v___x_283_; uint64_t v___x_284_; uint64_t v_remainder_285_; uint64_t v___x_286_; uint64_t v_half_287_; uint8_t v___x_288_; 
v_quotient_281_ = lean_uint64_shift_right(v___y_234_, v___x_273_);
v___x_282_ = 1ULL;
v___x_283_ = lean_uint64_shift_left(v___x_282_, v___x_273_);
v___x_284_ = lean_uint64_sub(v___x_283_, v___x_282_);
v_remainder_285_ = lean_uint64_land(v___y_234_, v___x_284_);
v___x_286_ = lean_uint64_sub(v___x_273_, v___x_282_);
v_half_287_ = lean_uint64_shift_left(v___x_282_, v___x_286_);
v___x_288_ = lean_uint64_dec_lt(v_remainder_285_, v_half_287_);
if (v___x_288_ == 0)
{
uint8_t v___x_289_; 
v___x_289_ = lean_uint64_dec_lt(v_half_287_, v_remainder_285_);
if (v___x_289_ == 0)
{
uint64_t v___x_290_; uint8_t v___x_291_; 
v___x_290_ = lean_uint64_land(v_quotient_281_, v___x_282_);
v___x_291_ = lean_uint64_dec_eq(v___x_290_, v___y_238_);
if (v___x_291_ == 0)
{
uint64_t v___x_292_; 
v___x_292_ = lean_uint64_add(v_quotient_281_, v___x_282_);
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v___x_292_;
goto v___jp_154_;
}
else
{
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v_quotient_281_;
goto v___jp_154_;
}
}
else
{
uint64_t v___x_293_; 
v___x_293_ = lean_uint64_add(v_quotient_281_, v___x_282_);
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v___x_293_;
goto v___jp_154_;
}
}
else
{
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v_quotient_281_;
goto v___jp_154_;
}
}
}
else
{
v___y_155_ = v___y_237_;
v___y_156_ = v___y_238_;
v___y_157_ = v___y_239_;
v___y_158_ = v___y_234_;
goto v___jp_154_;
}
}
}
}
v___jp_294_:
{
uint64_t v___x_304_; uint64_t v___x_305_; uint8_t v___x_306_; 
v___x_304_ = 1ULL;
v___x_305_ = lean_uint64_shift_right(v___y_301_, v___x_304_);
v___x_306_ = lean_uint64_dec_eq(v___x_305_, v___y_300_);
if (v___x_306_ == 0)
{
uint64_t v___x_307_; 
v___x_307_ = lean_uint64_add(v___y_303_, v___x_304_);
v___y_233_ = v___y_295_;
v___y_234_ = v___y_296_;
v___y_235_ = v___y_298_;
v___y_236_ = v___y_297_;
v___y_237_ = v___y_299_;
v___y_238_ = v___y_300_;
v___y_239_ = v___y_302_;
v___y_240_ = v___x_307_;
goto v___jp_232_;
}
else
{
v___y_233_ = v___y_295_;
v___y_234_ = v___y_296_;
v___y_235_ = v___y_298_;
v___y_236_ = v___y_297_;
v___y_237_ = v___y_299_;
v___y_238_ = v___y_300_;
v___y_239_ = v___y_302_;
v___y_240_ = v___y_303_;
goto v___jp_232_;
}
}
v___jp_308_:
{
uint64_t v___x_320_; uint8_t v___x_321_; 
v___x_320_ = lean_uint64_shift_right(v___y_316_, v___y_318_);
v___x_321_ = lean_uint64_dec_eq(v___x_320_, v___y_314_);
if (v___x_321_ == 0)
{
uint64_t v___x_322_; 
v___x_322_ = lean_uint64_add(v___y_309_, v___y_318_);
v___y_295_ = v___y_310_;
v___y_296_ = v___y_311_;
v___y_297_ = v___y_313_;
v___y_298_ = v___y_312_;
v___y_299_ = v___y_315_;
v___y_300_ = v___y_314_;
v___y_301_ = v___y_319_;
v___y_302_ = v___y_317_;
v___y_303_ = v___x_322_;
goto v___jp_294_;
}
else
{
v___y_295_ = v___y_310_;
v___y_296_ = v___y_311_;
v___y_297_ = v___y_313_;
v___y_298_ = v___y_312_;
v___y_299_ = v___y_315_;
v___y_300_ = v___y_314_;
v___y_301_ = v___y_319_;
v___y_302_ = v___y_317_;
v___y_303_ = v___y_309_;
goto v___jp_294_;
}
}
v___jp_323_:
{
uint64_t v___x_333_; uint64_t v___x_334_; uint8_t v___x_335_; 
v___x_333_ = 2ULL;
v___x_334_ = lean_uint64_shift_right(v___y_330_, v___x_333_);
v___x_335_ = lean_uint64_dec_eq(v___x_334_, v___y_329_);
if (v___x_335_ == 0)
{
v___y_309_ = v___y_332_;
v___y_310_ = v___y_324_;
v___y_311_ = v___y_325_;
v___y_312_ = v___y_327_;
v___y_313_ = v___y_326_;
v___y_314_ = v___y_329_;
v___y_315_ = v___y_328_;
v___y_316_ = v___y_330_;
v___y_317_ = v___y_331_;
v___y_318_ = v___x_333_;
v___y_319_ = v___x_334_;
goto v___jp_308_;
}
else
{
v___y_309_ = v___y_332_;
v___y_310_ = v___y_324_;
v___y_311_ = v___y_325_;
v___y_312_ = v___y_327_;
v___y_313_ = v___y_326_;
v___y_314_ = v___y_329_;
v___y_315_ = v___y_328_;
v___y_316_ = v___y_330_;
v___y_317_ = v___y_331_;
v___y_318_ = v___x_333_;
v___y_319_ = v___y_330_;
goto v___jp_308_;
}
}
v___jp_336_:
{
uint64_t v___x_348_; uint8_t v___x_349_; 
v___x_348_ = lean_uint64_shift_right(v___y_343_, v___y_337_);
v___x_349_ = lean_uint64_dec_eq(v___x_348_, v___y_344_);
if (v___x_349_ == 0)
{
uint64_t v___x_350_; 
v___x_350_ = lean_uint64_add(v___y_342_, v___y_337_);
v___y_324_ = v___y_338_;
v___y_325_ = v___y_339_;
v___y_326_ = v___y_341_;
v___y_327_ = v___y_340_;
v___y_328_ = v___y_345_;
v___y_329_ = v___y_344_;
v___y_330_ = v___y_347_;
v___y_331_ = v___y_346_;
v___y_332_ = v___x_350_;
goto v___jp_323_;
}
else
{
v___y_324_ = v___y_338_;
v___y_325_ = v___y_339_;
v___y_326_ = v___y_341_;
v___y_327_ = v___y_340_;
v___y_328_ = v___y_345_;
v___y_329_ = v___y_344_;
v___y_330_ = v___y_347_;
v___y_331_ = v___y_346_;
v___y_332_ = v___y_342_;
goto v___jp_323_;
}
}
v___jp_351_:
{
uint64_t v___x_361_; uint64_t v___x_362_; uint8_t v___x_363_; 
v___x_361_ = 4ULL;
v___x_362_ = lean_uint64_shift_right(v___y_356_, v___x_361_);
v___x_363_ = lean_uint64_dec_eq(v___x_362_, v___y_358_);
if (v___x_363_ == 0)
{
v___y_337_ = v___x_361_;
v___y_338_ = v___y_352_;
v___y_339_ = v___y_353_;
v___y_340_ = v___y_355_;
v___y_341_ = v___y_354_;
v___y_342_ = v___y_360_;
v___y_343_ = v___y_356_;
v___y_344_ = v___y_358_;
v___y_345_ = v___y_357_;
v___y_346_ = v___y_359_;
v___y_347_ = v___x_362_;
goto v___jp_336_;
}
else
{
v___y_337_ = v___x_361_;
v___y_338_ = v___y_352_;
v___y_339_ = v___y_353_;
v___y_340_ = v___y_355_;
v___y_341_ = v___y_354_;
v___y_342_ = v___y_360_;
v___y_343_ = v___y_356_;
v___y_344_ = v___y_358_;
v___y_345_ = v___y_357_;
v___y_346_ = v___y_359_;
v___y_347_ = v___y_356_;
goto v___jp_336_;
}
}
v___jp_364_:
{
uint64_t v___x_376_; uint8_t v___x_377_; 
v___x_376_ = lean_uint64_shift_right(v___y_374_, v___y_368_);
v___x_377_ = lean_uint64_dec_eq(v___x_376_, v___y_371_);
if (v___x_377_ == 0)
{
uint64_t v___x_378_; 
v___x_378_ = lean_uint64_add(v___y_367_, v___y_368_);
v___y_352_ = v___y_365_;
v___y_353_ = v___y_366_;
v___y_354_ = v___y_370_;
v___y_355_ = v___y_369_;
v___y_356_ = v___y_375_;
v___y_357_ = v___y_372_;
v___y_358_ = v___y_371_;
v___y_359_ = v___y_373_;
v___y_360_ = v___x_378_;
goto v___jp_351_;
}
else
{
v___y_352_ = v___y_365_;
v___y_353_ = v___y_366_;
v___y_354_ = v___y_370_;
v___y_355_ = v___y_369_;
v___y_356_ = v___y_375_;
v___y_357_ = v___y_372_;
v___y_358_ = v___y_371_;
v___y_359_ = v___y_373_;
v___y_360_ = v___y_367_;
goto v___jp_351_;
}
}
v___jp_379_:
{
uint64_t v___x_389_; uint64_t v___x_390_; uint8_t v___x_391_; 
v___x_389_ = 8ULL;
v___x_390_ = lean_uint64_shift_right(v___y_387_, v___x_389_);
v___x_391_ = lean_uint64_dec_eq(v___x_390_, v___y_385_);
if (v___x_391_ == 0)
{
v___y_365_ = v___y_380_;
v___y_366_ = v___y_381_;
v___y_367_ = v___y_388_;
v___y_368_ = v___x_389_;
v___y_369_ = v___y_383_;
v___y_370_ = v___y_382_;
v___y_371_ = v___y_385_;
v___y_372_ = v___y_384_;
v___y_373_ = v___y_386_;
v___y_374_ = v___y_387_;
v___y_375_ = v___x_390_;
goto v___jp_364_;
}
else
{
v___y_365_ = v___y_380_;
v___y_366_ = v___y_381_;
v___y_367_ = v___y_388_;
v___y_368_ = v___x_389_;
v___y_369_ = v___y_383_;
v___y_370_ = v___y_382_;
v___y_371_ = v___y_385_;
v___y_372_ = v___y_384_;
v___y_373_ = v___y_386_;
v___y_374_ = v___y_387_;
v___y_375_ = v___y_387_;
goto v___jp_364_;
}
}
v___jp_392_:
{
uint64_t v___x_404_; uint8_t v___x_405_; 
v___x_404_ = lean_uint64_shift_right(v___y_393_, v___y_401_);
v___x_405_ = lean_uint64_dec_eq(v___x_404_, v___y_399_);
if (v___x_405_ == 0)
{
uint64_t v___x_406_; 
v___x_406_ = lean_uint64_add(v___y_394_, v___y_401_);
v___y_380_ = v___y_395_;
v___y_381_ = v___y_396_;
v___y_382_ = v___y_398_;
v___y_383_ = v___y_397_;
v___y_384_ = v___y_400_;
v___y_385_ = v___y_399_;
v___y_386_ = v___y_402_;
v___y_387_ = v___y_403_;
v___y_388_ = v___x_406_;
goto v___jp_379_;
}
else
{
v___y_380_ = v___y_395_;
v___y_381_ = v___y_396_;
v___y_382_ = v___y_398_;
v___y_383_ = v___y_397_;
v___y_384_ = v___y_400_;
v___y_385_ = v___y_399_;
v___y_386_ = v___y_402_;
v___y_387_ = v___y_403_;
v___y_388_ = v___y_394_;
goto v___jp_379_;
}
}
v___jp_407_:
{
uint64_t v___x_417_; uint64_t v___x_418_; uint8_t v___x_419_; 
v___x_417_ = 16ULL;
v___x_418_ = lean_uint64_shift_right(v___y_408_, v___x_417_);
v___x_419_ = lean_uint64_dec_eq(v___x_418_, v___y_414_);
if (v___x_419_ == 0)
{
v___y_393_ = v___y_408_;
v___y_394_ = v___y_416_;
v___y_395_ = v___y_409_;
v___y_396_ = v___y_410_;
v___y_397_ = v___y_412_;
v___y_398_ = v___y_411_;
v___y_399_ = v___y_414_;
v___y_400_ = v___y_413_;
v___y_401_ = v___x_417_;
v___y_402_ = v___y_415_;
v___y_403_ = v___x_418_;
goto v___jp_392_;
}
else
{
v___y_393_ = v___y_408_;
v___y_394_ = v___y_416_;
v___y_395_ = v___y_409_;
v___y_396_ = v___y_410_;
v___y_397_ = v___y_412_;
v___y_398_ = v___y_411_;
v___y_399_ = v___y_414_;
v___y_400_ = v___y_413_;
v___y_401_ = v___x_417_;
v___y_402_ = v___y_415_;
v___y_403_ = v___y_408_;
goto v___jp_392_;
}
}
v___jp_420_:
{
uint64_t v___x_430_; uint8_t v___x_431_; 
v___x_430_ = lean_uint64_shift_right(v___y_422_, v___y_425_);
v___x_431_ = lean_uint64_dec_eq(v___x_430_, v___y_426_);
if (v___x_431_ == 0)
{
v___y_408_ = v___y_429_;
v___y_409_ = v___y_421_;
v___y_410_ = v___y_422_;
v___y_411_ = v___y_424_;
v___y_412_ = v___y_423_;
v___y_413_ = v___y_427_;
v___y_414_ = v___y_426_;
v___y_415_ = v___y_428_;
v___y_416_ = v___y_425_;
goto v___jp_407_;
}
else
{
v___y_408_ = v___y_429_;
v___y_409_ = v___y_421_;
v___y_410_ = v___y_422_;
v___y_411_ = v___y_424_;
v___y_412_ = v___y_423_;
v___y_413_ = v___y_427_;
v___y_414_ = v___y_426_;
v___y_415_ = v___y_428_;
v___y_416_ = v___y_426_;
goto v___jp_407_;
}
}
v___jp_432_:
{
uint64_t v___x_439_; uint8_t v___x_440_; 
v___x_439_ = 0ULL;
v___x_440_ = lean_uint64_dec_eq(v___y_434_, v___x_439_);
if (v___x_440_ == 0)
{
uint64_t v___x_441_; uint64_t v___x_442_; uint8_t v___x_443_; 
v___x_441_ = 32ULL;
v___x_442_ = lean_uint64_shift_right(v___y_434_, v___x_441_);
v___x_443_ = lean_uint64_dec_eq(v___x_442_, v___x_439_);
if (v___x_443_ == 0)
{
v___y_421_ = v___y_433_;
v___y_422_ = v___y_434_;
v___y_423_ = v___y_436_;
v___y_424_ = v___y_435_;
v___y_425_ = v___x_441_;
v___y_426_ = v___x_439_;
v___y_427_ = v___y_437_;
v___y_428_ = v___y_438_;
v___y_429_ = v___x_442_;
goto v___jp_420_;
}
else
{
v___y_421_ = v___y_433_;
v___y_422_ = v___y_434_;
v___y_423_ = v___y_436_;
v___y_424_ = v___y_435_;
v___y_425_ = v___x_441_;
v___y_426_ = v___x_439_;
v___y_427_ = v___y_437_;
v___y_428_ = v___y_438_;
v___y_429_ = v___y_434_;
goto v___jp_420_;
}
}
else
{
if (v___y_438_ == 0)
{
uint32_t v___x_444_; 
v___x_444_ = 0;
return v___x_444_;
}
else
{
uint32_t v___x_445_; 
v___x_445_ = 2147483648;
return v___x_445_;
}
}
}
v___jp_446_:
{
uint32_t v___x_450_; uint32_t v___x_451_; 
v___x_450_ = lean_uint32_land(v___y_448_, v___y_447_);
v___x_451_ = lean_uint32_lor(v___y_449_, v___x_450_);
return v___x_451_;
}
v___jp_452_:
{
uint8_t v___x_457_; 
v___x_457_ = lean_uint64_dec_eq(v___y_456_, v___y_454_);
if (v___x_457_ == 0)
{
uint64_t v___x_458_; uint8_t v___x_459_; 
v___x_458_ = 8388608ULL;
v___x_459_ = lean_uint64_dec_eq(v___y_456_, v___x_458_);
if (v___x_459_ == 0)
{
uint32_t v___x_460_; 
v___x_460_ = lean_uint64_to_uint32(v___y_456_);
if (v___y_455_ == 0)
{
uint32_t v___x_461_; 
v___x_461_ = 0;
v___y_447_ = v___y_453_;
v___y_448_ = v___x_460_;
v___y_449_ = v___x_461_;
goto v___jp_446_;
}
else
{
uint32_t v___x_462_; 
v___x_462_ = 2147483648;
v___y_447_ = v___y_453_;
v___y_448_ = v___x_460_;
v___y_449_ = v___x_462_;
goto v___jp_446_;
}
}
else
{
if (v___y_455_ == 0)
{
uint32_t v___x_463_; 
v___x_463_ = 0;
v___y_141_ = v___x_463_;
goto v___jp_140_;
}
else
{
uint32_t v___x_464_; 
v___x_464_ = 2147483648;
v___y_141_ = v___x_464_;
goto v___jp_140_;
}
}
}
else
{
if (v___y_455_ == 0)
{
uint32_t v___x_465_; 
v___x_465_ = 0;
return v___x_465_;
}
else
{
uint32_t v___x_466_; 
v___x_466_ = 2147483648;
return v___x_466_;
}
}
}
v___jp_467_:
{
uint64_t v___x_476_; uint64_t v___x_477_; uint64_t v___x_478_; uint8_t v___x_479_; 
v___x_476_ = lean_uint64_mul(v___y_474_, v___y_473_);
v___x_477_ = lean_uint64_add(v___y_469_, v___y_475_);
v___x_478_ = 281474976710656ULL;
v___x_479_ = lean_uint64_dec_lt(v___x_476_, v___x_478_);
if (v___x_479_ == 0)
{
v___y_433_ = v___y_468_;
v___y_434_ = v___x_476_;
v___y_435_ = v___x_477_;
v___y_436_ = v___y_470_;
v___y_437_ = v___y_471_;
v___y_438_ = v___y_472_;
goto v___jp_432_;
}
else
{
uint64_t v___x_480_; uint8_t v___x_481_; 
v___x_480_ = 123ULL;
v___x_481_ = lean_uint64_dec_le(v___x_477_, v___x_480_);
if (v___x_481_ == 0)
{
v___y_433_ = v___y_468_;
v___y_434_ = v___x_476_;
v___y_435_ = v___x_477_;
v___y_436_ = v___y_470_;
v___y_437_ = v___y_471_;
v___y_438_ = v___y_472_;
goto v___jp_432_;
}
else
{
uint64_t v___x_482_; uint8_t v___x_483_; 
v___x_482_ = 0ULL;
v___x_483_ = lean_uint64_dec_eq(v___x_476_, v___x_482_);
if (v___x_483_ == 0)
{
uint64_t v___x_484_; uint64_t v___x_485_; uint8_t v___x_486_; 
v___x_484_ = 149ULL;
v___x_485_ = lean_uint64_sub(v___x_484_, v___x_477_);
v___x_486_ = lean_uint64_dec_eq(v___x_485_, v___x_482_);
if (v___x_486_ == 0)
{
uint64_t v___x_487_; uint8_t v___x_488_; 
v___x_487_ = 64ULL;
v___x_488_ = lean_uint64_dec_lt(v___x_485_, v___x_487_);
if (v___x_488_ == 0)
{
uint8_t v___x_489_; 
v___x_489_ = lean_uint64_dec_eq(v___x_485_, v___x_487_);
if (v___x_489_ == 0)
{
v___y_453_ = v___y_471_;
v___y_454_ = v___x_482_;
v___y_455_ = v___y_472_;
v___y_456_ = v___x_482_;
goto v___jp_452_;
}
else
{
uint64_t v___x_490_; uint8_t v___x_491_; 
v___x_490_ = 9223372036854775808ULL;
v___x_491_ = lean_uint64_dec_lt(v___x_490_, v___x_476_);
if (v___x_491_ == 0)
{
v___y_453_ = v___y_471_;
v___y_454_ = v___x_482_;
v___y_455_ = v___y_472_;
v___y_456_ = v___x_482_;
goto v___jp_452_;
}
else
{
uint64_t v___x_492_; 
v___x_492_ = 1ULL;
v___y_453_ = v___y_471_;
v___y_454_ = v___x_482_;
v___y_455_ = v___y_472_;
v___y_456_ = v___x_492_;
goto v___jp_452_;
}
}
}
else
{
uint64_t v_quotient_493_; uint64_t v___x_494_; uint64_t v___x_495_; uint64_t v___x_496_; uint64_t v_remainder_497_; uint64_t v___x_498_; uint64_t v_half_499_; uint8_t v___x_500_; 
v_quotient_493_ = lean_uint64_shift_right(v___x_476_, v___x_485_);
v___x_494_ = 1ULL;
v___x_495_ = lean_uint64_shift_left(v___x_494_, v___x_485_);
v___x_496_ = lean_uint64_sub(v___x_495_, v___x_494_);
v_remainder_497_ = lean_uint64_land(v___x_476_, v___x_496_);
v___x_498_ = lean_uint64_sub(v___x_485_, v___x_494_);
v_half_499_ = lean_uint64_shift_left(v___x_494_, v___x_498_);
v___x_500_ = lean_uint64_dec_lt(v_remainder_497_, v_half_499_);
if (v___x_500_ == 0)
{
uint8_t v___x_501_; 
v___x_501_ = lean_uint64_dec_lt(v_half_499_, v_remainder_497_);
if (v___x_501_ == 0)
{
uint64_t v___x_502_; uint8_t v___x_503_; 
v___x_502_ = lean_uint64_land(v_quotient_493_, v___x_494_);
v___x_503_ = lean_uint64_dec_eq(v___x_502_, v___x_482_);
if (v___x_503_ == 0)
{
uint64_t v___x_504_; 
v___x_504_ = lean_uint64_add(v_quotient_493_, v___x_494_);
v___y_453_ = v___y_471_;
v___y_454_ = v___x_482_;
v___y_455_ = v___y_472_;
v___y_456_ = v___x_504_;
goto v___jp_452_;
}
else
{
v___y_453_ = v___y_471_;
v___y_454_ = v___x_482_;
v___y_455_ = v___y_472_;
v___y_456_ = v_quotient_493_;
goto v___jp_452_;
}
}
else
{
uint64_t v___x_505_; 
v___x_505_ = lean_uint64_add(v_quotient_493_, v___x_494_);
v___y_453_ = v___y_471_;
v___y_454_ = v___x_482_;
v___y_455_ = v___y_472_;
v___y_456_ = v___x_505_;
goto v___jp_452_;
}
}
else
{
v___y_453_ = v___y_471_;
v___y_454_ = v___x_482_;
v___y_455_ = v___y_472_;
v___y_456_ = v_quotient_493_;
goto v___jp_452_;
}
}
}
else
{
v___y_453_ = v___y_471_;
v___y_454_ = v___x_482_;
v___y_455_ = v___y_472_;
v___y_456_ = v___x_476_;
goto v___jp_452_;
}
}
else
{
if (v___y_472_ == 0)
{
uint32_t v___x_506_; 
v___x_506_ = 0;
return v___x_506_;
}
else
{
uint32_t v___x_507_; 
v___x_507_ = 2147483648;
return v___x_507_;
}
}
}
}
}
v___jp_508_:
{
uint64_t v___x_517_; uint64_t v___x_518_; uint8_t v___x_519_; 
v___x_517_ = lean_uint32_to_uint64(v___y_512_);
v___x_518_ = 0ULL;
v___x_519_ = lean_uint64_dec_eq(v___x_517_, v___x_518_);
if (v___x_519_ == 0)
{
uint64_t v___x_520_; uint64_t v___x_521_; 
v___x_520_ = 1ULL;
v___x_521_ = lean_uint64_sub(v___x_517_, v___x_520_);
v___y_468_ = v___y_509_;
v___y_469_ = v___y_516_;
v___y_470_ = v___y_510_;
v___y_471_ = v___y_511_;
v___y_472_ = v___y_513_;
v___y_473_ = v___y_515_;
v___y_474_ = v___y_514_;
v___y_475_ = v___x_521_;
goto v___jp_467_;
}
else
{
v___y_468_ = v___y_509_;
v___y_469_ = v___y_516_;
v___y_470_ = v___y_510_;
v___y_471_ = v___y_511_;
v___y_472_ = v___y_513_;
v___y_473_ = v___y_515_;
v___y_474_ = v___y_514_;
v___y_475_ = v___x_518_;
goto v___jp_467_;
}
}
v___jp_522_:
{
uint64_t v___x_531_; uint64_t v___x_532_; uint8_t v___x_533_; 
v___x_531_ = lean_uint32_to_uint64(v___y_524_);
v___x_532_ = 0ULL;
v___x_533_ = lean_uint64_dec_eq(v___x_531_, v___x_532_);
if (v___x_533_ == 0)
{
uint64_t v___x_534_; uint64_t v___x_535_; 
v___x_534_ = 1ULL;
v___x_535_ = lean_uint64_sub(v___x_531_, v___x_534_);
v___y_509_ = v___y_523_;
v___y_510_ = v___y_525_;
v___y_511_ = v___y_526_;
v___y_512_ = v___y_528_;
v___y_513_ = v___y_527_;
v___y_514_ = v___y_529_;
v___y_515_ = v___y_530_;
v___y_516_ = v___x_535_;
goto v___jp_508_;
}
else
{
v___y_509_ = v___y_523_;
v___y_510_ = v___y_525_;
v___y_511_ = v___y_526_;
v___y_512_ = v___y_528_;
v___y_513_ = v___y_527_;
v___y_514_ = v___y_529_;
v___y_515_ = v___y_530_;
v___y_516_ = v___x_532_;
goto v___jp_508_;
}
}
v___jp_536_:
{
uint32_t v___x_545_; uint8_t v___x_546_; 
v___x_545_ = 0;
v___x_546_ = lean_uint32_dec_eq(v___y_541_, v___x_545_);
if (v___x_546_ == 0)
{
uint64_t v___x_547_; uint64_t v___x_548_; uint64_t v___x_549_; 
v___x_547_ = lean_uint32_to_uint64(v___y_543_);
v___x_548_ = 8388608ULL;
v___x_549_ = lean_uint64_lor(v___x_547_, v___x_548_);
v___y_523_ = v___y_537_;
v___y_524_ = v___y_539_;
v___y_525_ = v___y_538_;
v___y_526_ = v___y_540_;
v___y_527_ = v___y_542_;
v___y_528_ = v___y_541_;
v___y_529_ = v___y_544_;
v___y_530_ = v___x_549_;
goto v___jp_522_;
}
else
{
uint64_t v___x_550_; 
v___x_550_ = lean_uint32_to_uint64(v___y_543_);
v___y_523_ = v___y_537_;
v___y_524_ = v___y_539_;
v___y_525_ = v___y_538_;
v___y_526_ = v___y_540_;
v___y_527_ = v___y_542_;
v___y_528_ = v___y_541_;
v___y_529_ = v___y_544_;
v___y_530_ = v___x_550_;
goto v___jp_522_;
}
}
v___jp_551_:
{
uint32_t v___x_558_; uint32_t v___x_559_; uint32_t v___x_560_; uint32_t v___x_561_; uint32_t v___x_562_; 
v___x_558_ = lean_uint32_land(v___y_555_, v___y_554_);
v___x_559_ = lean_uint32_shift_left(v___x_558_, v___y_553_);
v___x_560_ = lean_uint32_lor(v___y_557_, v___x_559_);
v___x_561_ = lean_uint32_land(v___y_556_, v___y_552_);
v___x_562_ = lean_uint32_lor(v___x_560_, v___x_561_);
return v___x_562_;
}
v___jp_563_:
{
uint32_t v___x_572_; uint32_t v___x_573_; uint32_t v___x_574_; uint32_t v___x_575_; uint32_t v___x_576_; uint32_t v___x_577_; uint32_t v___x_578_; uint32_t v___x_579_; 
v___x_572_ = 127;
v___x_573_ = lean_uint32_sub(v___y_570_, v___x_572_);
v___x_574_ = lean_uint64_to_uint32(v___y_567_);
v___x_575_ = lean_uint32_add(v___x_573_, v___x_574_);
v___x_576_ = lean_uint64_to_uint32(v___y_568_);
v___x_577_ = lean_uint32_add(v___x_575_, v___x_576_);
v___x_578_ = lean_uint64_to_uint32(v___y_566_);
v___x_579_ = lean_uint32_land(v___x_578_, v___y_565_);
if (v___y_571_ == 0)
{
uint32_t v___x_580_; 
v___x_580_ = 0;
v___y_552_ = v___y_565_;
v___y_553_ = v___y_564_;
v___y_554_ = v___y_569_;
v___y_555_ = v___x_577_;
v___y_556_ = v___x_579_;
v___y_557_ = v___x_580_;
goto v___jp_551_;
}
else
{
uint32_t v___x_581_; 
v___x_581_ = 2147483648;
v___y_552_ = v___y_565_;
v___y_553_ = v___y_564_;
v___y_554_ = v___y_569_;
v___y_555_ = v___x_577_;
v___y_556_ = v___x_579_;
v___y_557_ = v___x_581_;
goto v___jp_551_;
}
}
v___jp_582_:
{
uint8_t v___x_590_; 
v___x_590_ = 0;
v___y_564_ = v___y_584_;
v___y_565_ = v___y_583_;
v___y_566_ = v___y_585_;
v___y_567_ = v___y_586_;
v___y_568_ = v___y_587_;
v___y_569_ = v___y_588_;
v___y_570_ = v___y_589_;
v___y_571_ = v___x_590_;
goto v___jp_563_;
}
v___jp_591_:
{
if (v___y_600_ == 0)
{
v___y_564_ = v___y_593_;
v___y_565_ = v___y_592_;
v___y_566_ = v___y_594_;
v___y_567_ = v___y_595_;
v___y_568_ = v___y_596_;
v___y_569_ = v___y_597_;
v___y_570_ = v___y_599_;
v___y_571_ = v___y_598_;
goto v___jp_563_;
}
else
{
v___y_583_ = v___y_592_;
v___y_584_ = v___y_593_;
v___y_585_ = v___y_594_;
v___y_586_ = v___y_595_;
v___y_587_ = v___y_596_;
v___y_588_ = v___y_597_;
v___y_589_ = v___y_599_;
goto v___jp_582_;
}
}
v___jp_601_:
{
uint32_t v___x_605_; uint32_t v___x_606_; 
v___x_605_ = lean_uint32_land(v___y_602_, v___y_603_);
v___x_606_ = lean_uint32_lor(v___y_604_, v___x_605_);
return v___x_606_;
}
v___jp_607_:
{
uint8_t v___x_612_; 
v___x_612_ = lean_uint64_dec_eq(v___y_611_, v___y_609_);
if (v___x_612_ == 0)
{
uint64_t v___x_613_; uint8_t v___x_614_; 
v___x_613_ = 8388608ULL;
v___x_614_ = lean_uint64_dec_eq(v___y_611_, v___x_613_);
if (v___x_614_ == 0)
{
uint32_t v___x_615_; 
v___x_615_ = lean_uint64_to_uint32(v___y_611_);
if (v___y_608_ == 0)
{
uint32_t v___x_616_; 
v___x_616_ = 0;
v___y_602_ = v___x_615_;
v___y_603_ = v___y_610_;
v___y_604_ = v___x_616_;
goto v___jp_601_;
}
else
{
uint32_t v___x_617_; 
v___x_617_ = 2147483648;
v___y_602_ = v___x_615_;
v___y_603_ = v___y_610_;
v___y_604_ = v___x_617_;
goto v___jp_601_;
}
}
else
{
if (v___y_608_ == 0)
{
uint32_t v___x_618_; 
v___x_618_ = 0;
v___y_133_ = v___x_618_;
goto v___jp_132_;
}
else
{
uint32_t v___x_619_; 
v___x_619_ = 2147483648;
v___y_133_ = v___x_619_;
goto v___jp_132_;
}
}
}
else
{
if (v___y_608_ == 0)
{
uint32_t v___x_620_; 
v___x_620_ = 0;
return v___x_620_;
}
else
{
uint32_t v___x_621_; 
v___x_621_ = 2147483648;
return v___x_621_;
}
}
}
v___jp_622_:
{
uint32_t v___x_629_; uint32_t v___x_630_; uint32_t v___x_631_; uint32_t v___x_632_; uint32_t v___x_633_; 
v___x_629_ = lean_uint32_land(v___y_627_, v___y_625_);
v___x_630_ = lean_uint32_shift_left(v___x_629_, v___y_623_);
v___x_631_ = lean_uint32_lor(v___y_628_, v___x_630_);
v___x_632_ = lean_uint32_land(v___y_626_, v___y_624_);
v___x_633_ = lean_uint32_lor(v___x_631_, v___x_632_);
return v___x_633_;
}
v___jp_634_:
{
if (v___y_636_ == 0)
{
uint32_t v___x_641_; 
v___x_641_ = 0;
v___y_623_ = v___y_635_;
v___y_624_ = v___y_637_;
v___y_625_ = v___y_638_;
v___y_626_ = v___y_640_;
v___y_627_ = v___y_639_;
v___y_628_ = v___x_641_;
goto v___jp_622_;
}
else
{
uint32_t v___x_642_; 
v___x_642_ = 2147483648;
v___y_623_ = v___y_635_;
v___y_624_ = v___y_637_;
v___y_625_ = v___y_638_;
v___y_626_ = v___y_640_;
v___y_627_ = v___y_639_;
v___y_628_ = v___x_642_;
goto v___jp_622_;
}
}
v___jp_643_:
{
uint64_t v___x_651_; uint64_t v_encodedExponent_652_; uint32_t v___x_653_; uint64_t v___x_654_; uint8_t v___x_655_; 
v___x_651_ = 171ULL;
v_encodedExponent_652_ = lean_uint64_sub(v___y_649_, v___x_651_);
v___x_653_ = lean_uint64_to_uint32(v_encodedExponent_652_);
v___x_654_ = 8388608ULL;
v___x_655_ = lean_uint64_dec_lt(v___y_650_, v___x_654_);
if (v___x_655_ == 0)
{
uint64_t v___x_656_; uint32_t v___x_657_; 
v___x_656_ = lean_uint64_sub(v___y_650_, v___x_654_);
v___x_657_ = lean_uint64_to_uint32(v___x_656_);
v___y_635_ = v___y_644_;
v___y_636_ = v___y_645_;
v___y_637_ = v___y_647_;
v___y_638_ = v___y_648_;
v___y_639_ = v___x_653_;
v___y_640_ = v___x_657_;
goto v___jp_634_;
}
else
{
uint32_t v___x_658_; 
v___x_658_ = lean_uint64_to_uint32(v___y_646_);
v___y_635_ = v___y_644_;
v___y_636_ = v___y_645_;
v___y_637_ = v___y_647_;
v___y_638_ = v___y_648_;
v___y_639_ = v___x_653_;
v___y_640_ = v___x_658_;
goto v___jp_634_;
}
}
v___jp_659_:
{
uint64_t v___x_668_; uint8_t v___x_669_; 
v___x_668_ = 425ULL;
v___x_669_ = lean_uint64_dec_lt(v___x_668_, v___y_667_);
if (v___x_669_ == 0)
{
if (v___y_661_ == 0)
{
v___y_644_ = v___y_662_;
v___y_645_ = v___y_663_;
v___y_646_ = v___y_664_;
v___y_647_ = v___y_665_;
v___y_648_ = v___y_666_;
v___y_649_ = v___y_667_;
v___y_650_ = v___y_660_;
goto v___jp_643_;
}
else
{
uint64_t v___x_670_; 
v___x_670_ = 8388608ULL;
v___y_644_ = v___y_662_;
v___y_645_ = v___y_663_;
v___y_646_ = v___y_664_;
v___y_647_ = v___y_665_;
v___y_648_ = v___y_666_;
v___y_649_ = v___y_667_;
v___y_650_ = v___x_670_;
goto v___jp_643_;
}
}
else
{
if (v___y_663_ == 0)
{
uint32_t v___x_671_; 
v___x_671_ = 2139095040;
return v___x_671_;
}
else
{
uint32_t v___x_672_; 
v___x_672_ = 4286578688;
return v___x_672_;
}
}
}
v___jp_673_:
{
uint64_t v___x_681_; uint8_t v_carry_682_; 
v___x_681_ = 16777216ULL;
v_carry_682_ = lean_uint64_dec_eq(v___y_680_, v___x_681_);
if (v_carry_682_ == 0)
{
v___y_660_ = v___y_680_;
v___y_661_ = v_carry_682_;
v___y_662_ = v___y_674_;
v___y_663_ = v___y_675_;
v___y_664_ = v___y_676_;
v___y_665_ = v___y_677_;
v___y_666_ = v___y_678_;
v___y_667_ = v___y_679_;
goto v___jp_659_;
}
else
{
uint64_t v___x_683_; uint64_t v___x_684_; 
v___x_683_ = 1ULL;
v___x_684_ = lean_uint64_add(v___y_679_, v___x_683_);
v___y_660_ = v___y_680_;
v___y_661_ = v_carry_682_;
v___y_662_ = v___y_674_;
v___y_663_ = v___y_675_;
v___y_664_ = v___y_676_;
v___y_665_ = v___y_677_;
v___y_666_ = v___y_678_;
v___y_667_ = v___x_684_;
goto v___jp_659_;
}
}
v___jp_685_:
{
uint64_t v_position_694_; uint64_t v___x_695_; uint8_t v___x_696_; 
v_position_694_ = lean_uint64_add(v___y_693_, v___y_686_);
v___x_695_ = 172ULL;
v___x_696_ = lean_uint64_dec_lt(v_position_694_, v___x_695_);
if (v___x_696_ == 0)
{
uint64_t v___x_697_; uint8_t v___x_698_; 
v___x_697_ = 23ULL;
v___x_698_ = lean_uint64_dec_lt(v___y_693_, v___x_697_);
if (v___x_698_ == 0)
{
uint64_t v___x_699_; uint8_t v___x_700_; 
v___x_699_ = lean_uint64_sub(v___y_693_, v___x_697_);
v___x_700_ = lean_uint64_dec_eq(v___x_699_, v___y_690_);
if (v___x_700_ == 0)
{
uint64_t v___x_701_; uint8_t v___x_702_; 
v___x_701_ = 64ULL;
v___x_702_ = lean_uint64_dec_lt(v___x_699_, v___x_701_);
if (v___x_702_ == 0)
{
uint8_t v___x_703_; 
v___x_703_ = lean_uint64_dec_eq(v___x_699_, v___x_701_);
if (v___x_703_ == 0)
{
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v___y_690_;
goto v___jp_673_;
}
else
{
uint64_t v___x_704_; uint8_t v___x_705_; 
v___x_704_ = 9223372036854775808ULL;
v___x_705_ = lean_uint64_dec_lt(v___x_704_, v___y_687_);
if (v___x_705_ == 0)
{
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v___y_690_;
goto v___jp_673_;
}
else
{
uint64_t v___x_706_; 
v___x_706_ = 1ULL;
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v___x_706_;
goto v___jp_673_;
}
}
}
else
{
uint64_t v_quotient_707_; uint64_t v___x_708_; uint64_t v___x_709_; uint64_t v___x_710_; uint64_t v_remainder_711_; uint64_t v___x_712_; uint64_t v_half_713_; uint8_t v___x_714_; 
v_quotient_707_ = lean_uint64_shift_right(v___y_687_, v___x_699_);
v___x_708_ = 1ULL;
v___x_709_ = lean_uint64_shift_left(v___x_708_, v___x_699_);
v___x_710_ = lean_uint64_sub(v___x_709_, v___x_708_);
v_remainder_711_ = lean_uint64_land(v___y_687_, v___x_710_);
v___x_712_ = lean_uint64_sub(v___x_699_, v___x_708_);
v_half_713_ = lean_uint64_shift_left(v___x_708_, v___x_712_);
v___x_714_ = lean_uint64_dec_lt(v_remainder_711_, v_half_713_);
if (v___x_714_ == 0)
{
uint8_t v___x_715_; 
v___x_715_ = lean_uint64_dec_lt(v_half_713_, v_remainder_711_);
if (v___x_715_ == 0)
{
uint64_t v___x_716_; uint8_t v___x_717_; 
v___x_716_ = lean_uint64_land(v_quotient_707_, v___x_708_);
v___x_717_ = lean_uint64_dec_eq(v___x_716_, v___y_690_);
if (v___x_717_ == 0)
{
uint64_t v___x_718_; 
v___x_718_ = lean_uint64_add(v_quotient_707_, v___x_708_);
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v___x_718_;
goto v___jp_673_;
}
else
{
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v_quotient_707_;
goto v___jp_673_;
}
}
else
{
uint64_t v___x_719_; 
v___x_719_ = lean_uint64_add(v_quotient_707_, v___x_708_);
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v___x_719_;
goto v___jp_673_;
}
}
else
{
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v_quotient_707_;
goto v___jp_673_;
}
}
}
else
{
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v___y_687_;
goto v___jp_673_;
}
}
else
{
uint64_t v___x_720_; uint64_t v___x_721_; 
v___x_720_ = lean_uint64_sub(v___x_697_, v___y_693_);
v___x_721_ = lean_uint64_shift_left(v___y_687_, v___x_720_);
v___y_674_ = v___y_688_;
v___y_675_ = v___y_689_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_691_;
v___y_678_ = v___y_692_;
v___y_679_ = v_position_694_;
v___y_680_ = v___x_721_;
goto v___jp_673_;
}
}
else
{
uint64_t v___x_722_; uint8_t v___x_723_; 
v___x_722_ = 149ULL;
v___x_723_ = lean_uint64_dec_lt(v___y_686_, v___x_722_);
if (v___x_723_ == 0)
{
uint64_t v___x_724_; uint64_t v___x_725_; 
v___x_724_ = lean_uint64_sub(v___y_686_, v___x_722_);
v___x_725_ = lean_uint64_shift_left(v___y_687_, v___x_724_);
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v___x_725_;
goto v___jp_607_;
}
else
{
uint64_t v___x_726_; uint8_t v___x_727_; 
v___x_726_ = lean_uint64_sub(v___x_722_, v___y_686_);
v___x_727_ = lean_uint64_dec_eq(v___x_726_, v___y_690_);
if (v___x_727_ == 0)
{
uint64_t v___x_728_; uint8_t v___x_729_; 
v___x_728_ = 64ULL;
v___x_729_ = lean_uint64_dec_lt(v___x_726_, v___x_728_);
if (v___x_729_ == 0)
{
uint8_t v___x_730_; 
v___x_730_ = lean_uint64_dec_eq(v___x_726_, v___x_728_);
if (v___x_730_ == 0)
{
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v___y_690_;
goto v___jp_607_;
}
else
{
uint64_t v___x_731_; uint8_t v___x_732_; 
v___x_731_ = 9223372036854775808ULL;
v___x_732_ = lean_uint64_dec_lt(v___x_731_, v___y_687_);
if (v___x_732_ == 0)
{
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v___y_690_;
goto v___jp_607_;
}
else
{
uint64_t v___x_733_; 
v___x_733_ = 1ULL;
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v___x_733_;
goto v___jp_607_;
}
}
}
else
{
uint64_t v_quotient_734_; uint64_t v___x_735_; uint64_t v___x_736_; uint64_t v___x_737_; uint64_t v_remainder_738_; uint64_t v___x_739_; uint64_t v_half_740_; uint8_t v___x_741_; 
v_quotient_734_ = lean_uint64_shift_right(v___y_687_, v___x_726_);
v___x_735_ = 1ULL;
v___x_736_ = lean_uint64_shift_left(v___x_735_, v___x_726_);
v___x_737_ = lean_uint64_sub(v___x_736_, v___x_735_);
v_remainder_738_ = lean_uint64_land(v___y_687_, v___x_737_);
v___x_739_ = lean_uint64_sub(v___x_726_, v___x_735_);
v_half_740_ = lean_uint64_shift_left(v___x_735_, v___x_739_);
v___x_741_ = lean_uint64_dec_lt(v_remainder_738_, v_half_740_);
if (v___x_741_ == 0)
{
uint8_t v___x_742_; 
v___x_742_ = lean_uint64_dec_lt(v_half_740_, v_remainder_738_);
if (v___x_742_ == 0)
{
uint64_t v___x_743_; uint8_t v___x_744_; 
v___x_743_ = lean_uint64_land(v_quotient_734_, v___x_735_);
v___x_744_ = lean_uint64_dec_eq(v___x_743_, v___y_690_);
if (v___x_744_ == 0)
{
uint64_t v___x_745_; 
v___x_745_ = lean_uint64_add(v_quotient_734_, v___x_735_);
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v___x_745_;
goto v___jp_607_;
}
else
{
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v_quotient_734_;
goto v___jp_607_;
}
}
else
{
uint64_t v___x_746_; 
v___x_746_ = lean_uint64_add(v_quotient_734_, v___x_735_);
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v___x_746_;
goto v___jp_607_;
}
}
else
{
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v_quotient_734_;
goto v___jp_607_;
}
}
}
else
{
v___y_608_ = v___y_689_;
v___y_609_ = v___y_690_;
v___y_610_ = v___y_691_;
v___y_611_ = v___y_687_;
goto v___jp_607_;
}
}
}
}
v___jp_747_:
{
uint64_t v___x_757_; uint64_t v___x_758_; uint8_t v___x_759_; 
v___x_757_ = 1ULL;
v___x_758_ = lean_uint64_shift_right(v___y_750_, v___x_757_);
v___x_759_ = lean_uint64_dec_eq(v___x_758_, v___y_753_);
if (v___x_759_ == 0)
{
uint64_t v___x_760_; 
v___x_760_ = lean_uint64_add(v___y_756_, v___x_757_);
v___y_686_ = v___y_748_;
v___y_687_ = v___y_749_;
v___y_688_ = v___y_751_;
v___y_689_ = v___y_752_;
v___y_690_ = v___y_753_;
v___y_691_ = v___y_754_;
v___y_692_ = v___y_755_;
v___y_693_ = v___x_760_;
goto v___jp_685_;
}
else
{
v___y_686_ = v___y_748_;
v___y_687_ = v___y_749_;
v___y_688_ = v___y_751_;
v___y_689_ = v___y_752_;
v___y_690_ = v___y_753_;
v___y_691_ = v___y_754_;
v___y_692_ = v___y_755_;
v___y_693_ = v___y_756_;
goto v___jp_685_;
}
}
v___jp_761_:
{
uint64_t v___x_773_; uint8_t v___x_774_; 
v___x_773_ = lean_uint64_shift_right(v___y_768_, v___y_764_);
v___x_774_ = lean_uint64_dec_eq(v___x_773_, v___y_767_);
if (v___x_774_ == 0)
{
uint64_t v___x_775_; 
v___x_775_ = lean_uint64_add(v___y_769_, v___y_764_);
v___y_748_ = v___y_762_;
v___y_749_ = v___y_763_;
v___y_750_ = v___y_772_;
v___y_751_ = v___y_765_;
v___y_752_ = v___y_766_;
v___y_753_ = v___y_767_;
v___y_754_ = v___y_770_;
v___y_755_ = v___y_771_;
v___y_756_ = v___x_775_;
goto v___jp_747_;
}
else
{
v___y_748_ = v___y_762_;
v___y_749_ = v___y_763_;
v___y_750_ = v___y_772_;
v___y_751_ = v___y_765_;
v___y_752_ = v___y_766_;
v___y_753_ = v___y_767_;
v___y_754_ = v___y_770_;
v___y_755_ = v___y_771_;
v___y_756_ = v___y_769_;
goto v___jp_747_;
}
}
v___jp_776_:
{
uint64_t v___x_786_; uint64_t v___x_787_; uint8_t v___x_788_; 
v___x_786_ = 2ULL;
v___x_787_ = lean_uint64_shift_right(v___y_782_, v___x_786_);
v___x_788_ = lean_uint64_dec_eq(v___x_787_, v___y_781_);
if (v___x_788_ == 0)
{
v___y_762_ = v___y_777_;
v___y_763_ = v___y_778_;
v___y_764_ = v___x_786_;
v___y_765_ = v___y_779_;
v___y_766_ = v___y_780_;
v___y_767_ = v___y_781_;
v___y_768_ = v___y_782_;
v___y_769_ = v___y_785_;
v___y_770_ = v___y_783_;
v___y_771_ = v___y_784_;
v___y_772_ = v___x_787_;
goto v___jp_761_;
}
else
{
v___y_762_ = v___y_777_;
v___y_763_ = v___y_778_;
v___y_764_ = v___x_786_;
v___y_765_ = v___y_779_;
v___y_766_ = v___y_780_;
v___y_767_ = v___y_781_;
v___y_768_ = v___y_782_;
v___y_769_ = v___y_785_;
v___y_770_ = v___y_783_;
v___y_771_ = v___y_784_;
v___y_772_ = v___y_782_;
goto v___jp_761_;
}
}
v___jp_789_:
{
uint64_t v___x_801_; uint8_t v___x_802_; 
v___x_801_ = lean_uint64_shift_right(v___y_799_, v___y_798_);
v___x_802_ = lean_uint64_dec_eq(v___x_801_, v___y_794_);
if (v___x_802_ == 0)
{
uint64_t v___x_803_; 
v___x_803_ = lean_uint64_add(v___y_796_, v___y_798_);
v___y_777_ = v___y_790_;
v___y_778_ = v___y_791_;
v___y_779_ = v___y_792_;
v___y_780_ = v___y_793_;
v___y_781_ = v___y_794_;
v___y_782_ = v___y_800_;
v___y_783_ = v___y_795_;
v___y_784_ = v___y_797_;
v___y_785_ = v___x_803_;
goto v___jp_776_;
}
else
{
v___y_777_ = v___y_790_;
v___y_778_ = v___y_791_;
v___y_779_ = v___y_792_;
v___y_780_ = v___y_793_;
v___y_781_ = v___y_794_;
v___y_782_ = v___y_800_;
v___y_783_ = v___y_795_;
v___y_784_ = v___y_797_;
v___y_785_ = v___y_796_;
goto v___jp_776_;
}
}
v___jp_804_:
{
uint64_t v___x_814_; uint64_t v___x_815_; uint8_t v___x_816_; 
v___x_814_ = 4ULL;
v___x_815_ = lean_uint64_shift_right(v___y_812_, v___x_814_);
v___x_816_ = lean_uint64_dec_eq(v___x_815_, v___y_809_);
if (v___x_816_ == 0)
{
v___y_790_ = v___y_805_;
v___y_791_ = v___y_806_;
v___y_792_ = v___y_807_;
v___y_793_ = v___y_808_;
v___y_794_ = v___y_809_;
v___y_795_ = v___y_810_;
v___y_796_ = v___y_813_;
v___y_797_ = v___y_811_;
v___y_798_ = v___x_814_;
v___y_799_ = v___y_812_;
v___y_800_ = v___x_815_;
goto v___jp_789_;
}
else
{
v___y_790_ = v___y_805_;
v___y_791_ = v___y_806_;
v___y_792_ = v___y_807_;
v___y_793_ = v___y_808_;
v___y_794_ = v___y_809_;
v___y_795_ = v___y_810_;
v___y_796_ = v___y_813_;
v___y_797_ = v___y_811_;
v___y_798_ = v___x_814_;
v___y_799_ = v___y_812_;
v___y_800_ = v___y_812_;
goto v___jp_789_;
}
}
v___jp_817_:
{
uint64_t v___x_829_; uint8_t v___x_830_; 
v___x_829_ = lean_uint64_shift_right(v___y_820_, v___y_818_);
v___x_830_ = lean_uint64_dec_eq(v___x_829_, v___y_825_);
if (v___x_830_ == 0)
{
uint64_t v___x_831_; 
v___x_831_ = lean_uint64_add(v___y_824_, v___y_818_);
v___y_805_ = v___y_819_;
v___y_806_ = v___y_821_;
v___y_807_ = v___y_822_;
v___y_808_ = v___y_823_;
v___y_809_ = v___y_825_;
v___y_810_ = v___y_826_;
v___y_811_ = v___y_827_;
v___y_812_ = v___y_828_;
v___y_813_ = v___x_831_;
goto v___jp_804_;
}
else
{
v___y_805_ = v___y_819_;
v___y_806_ = v___y_821_;
v___y_807_ = v___y_822_;
v___y_808_ = v___y_823_;
v___y_809_ = v___y_825_;
v___y_810_ = v___y_826_;
v___y_811_ = v___y_827_;
v___y_812_ = v___y_828_;
v___y_813_ = v___y_824_;
goto v___jp_804_;
}
}
v___jp_832_:
{
uint64_t v___x_842_; uint64_t v___x_843_; uint8_t v___x_844_; 
v___x_842_ = 8ULL;
v___x_843_ = lean_uint64_shift_right(v___y_835_, v___x_842_);
v___x_844_ = lean_uint64_dec_eq(v___x_843_, v___y_838_);
if (v___x_844_ == 0)
{
v___y_818_ = v___x_842_;
v___y_819_ = v___y_833_;
v___y_820_ = v___y_835_;
v___y_821_ = v___y_834_;
v___y_822_ = v___y_836_;
v___y_823_ = v___y_837_;
v___y_824_ = v___y_841_;
v___y_825_ = v___y_838_;
v___y_826_ = v___y_839_;
v___y_827_ = v___y_840_;
v___y_828_ = v___x_843_;
goto v___jp_817_;
}
else
{
v___y_818_ = v___x_842_;
v___y_819_ = v___y_833_;
v___y_820_ = v___y_835_;
v___y_821_ = v___y_834_;
v___y_822_ = v___y_836_;
v___y_823_ = v___y_837_;
v___y_824_ = v___y_841_;
v___y_825_ = v___y_838_;
v___y_826_ = v___y_839_;
v___y_827_ = v___y_840_;
v___y_828_ = v___y_835_;
goto v___jp_817_;
}
}
v___jp_845_:
{
uint64_t v___x_857_; uint8_t v___x_858_; 
v___x_857_ = lean_uint64_shift_right(v___y_855_, v___y_852_);
v___x_858_ = lean_uint64_dec_eq(v___x_857_, v___y_850_);
if (v___x_858_ == 0)
{
uint64_t v___x_859_; 
v___x_859_ = lean_uint64_add(v___y_854_, v___y_852_);
v___y_833_ = v___y_846_;
v___y_834_ = v___y_847_;
v___y_835_ = v___y_856_;
v___y_836_ = v___y_848_;
v___y_837_ = v___y_849_;
v___y_838_ = v___y_850_;
v___y_839_ = v___y_851_;
v___y_840_ = v___y_853_;
v___y_841_ = v___x_859_;
goto v___jp_832_;
}
else
{
v___y_833_ = v___y_846_;
v___y_834_ = v___y_847_;
v___y_835_ = v___y_856_;
v___y_836_ = v___y_848_;
v___y_837_ = v___y_849_;
v___y_838_ = v___y_850_;
v___y_839_ = v___y_851_;
v___y_840_ = v___y_853_;
v___y_841_ = v___y_854_;
goto v___jp_832_;
}
}
v___jp_860_:
{
uint64_t v___x_870_; uint64_t v___x_871_; uint8_t v___x_872_; 
v___x_870_ = 16ULL;
v___x_871_ = lean_uint64_shift_right(v___y_868_, v___x_870_);
v___x_872_ = lean_uint64_dec_eq(v___x_871_, v___y_865_);
if (v___x_872_ == 0)
{
v___y_846_ = v___y_861_;
v___y_847_ = v___y_862_;
v___y_848_ = v___y_863_;
v___y_849_ = v___y_864_;
v___y_850_ = v___y_865_;
v___y_851_ = v___y_866_;
v___y_852_ = v___x_870_;
v___y_853_ = v___y_867_;
v___y_854_ = v___y_869_;
v___y_855_ = v___y_868_;
v___y_856_ = v___x_871_;
goto v___jp_845_;
}
else
{
v___y_846_ = v___y_861_;
v___y_847_ = v___y_862_;
v___y_848_ = v___y_863_;
v___y_849_ = v___y_864_;
v___y_850_ = v___y_865_;
v___y_851_ = v___y_866_;
v___y_852_ = v___x_870_;
v___y_853_ = v___y_867_;
v___y_854_ = v___y_869_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_868_;
goto v___jp_845_;
}
}
v___jp_873_:
{
uint64_t v___x_883_; uint8_t v___x_884_; 
v___x_883_ = lean_uint64_shift_right(v___y_875_, v___y_878_);
v___x_884_ = lean_uint64_dec_eq(v___x_883_, v___y_879_);
if (v___x_884_ == 0)
{
v___y_861_ = v___y_874_;
v___y_862_ = v___y_875_;
v___y_863_ = v___y_876_;
v___y_864_ = v___y_877_;
v___y_865_ = v___y_879_;
v___y_866_ = v___y_880_;
v___y_867_ = v___y_881_;
v___y_868_ = v___y_882_;
v___y_869_ = v___y_878_;
goto v___jp_860_;
}
else
{
v___y_861_ = v___y_874_;
v___y_862_ = v___y_875_;
v___y_863_ = v___y_876_;
v___y_864_ = v___y_877_;
v___y_865_ = v___y_879_;
v___y_866_ = v___y_880_;
v___y_867_ = v___y_881_;
v___y_868_ = v___y_882_;
v___y_869_ = v___y_879_;
goto v___jp_860_;
}
}
v___jp_885_:
{
uint64_t v___x_892_; uint8_t v___x_893_; 
v___x_892_ = 0ULL;
v___x_893_ = lean_uint64_dec_eq(v___y_887_, v___x_892_);
if (v___x_893_ == 0)
{
uint64_t v___x_894_; uint64_t v___x_895_; uint8_t v___x_896_; 
v___x_894_ = 32ULL;
v___x_895_ = lean_uint64_shift_right(v___y_887_, v___x_894_);
v___x_896_ = lean_uint64_dec_eq(v___x_895_, v___x_892_);
if (v___x_896_ == 0)
{
v___y_874_ = v___y_886_;
v___y_875_ = v___y_887_;
v___y_876_ = v___y_888_;
v___y_877_ = v___y_889_;
v___y_878_ = v___x_894_;
v___y_879_ = v___x_892_;
v___y_880_ = v___y_890_;
v___y_881_ = v___y_891_;
v___y_882_ = v___x_895_;
goto v___jp_873_;
}
else
{
v___y_874_ = v___y_886_;
v___y_875_ = v___y_887_;
v___y_876_ = v___y_888_;
v___y_877_ = v___y_889_;
v___y_878_ = v___x_894_;
v___y_879_ = v___x_892_;
v___y_880_ = v___y_890_;
v___y_881_ = v___y_891_;
v___y_882_ = v___y_887_;
goto v___jp_873_;
}
}
else
{
if (v___y_889_ == 0)
{
uint32_t v___x_897_; 
v___x_897_ = 0;
return v___x_897_;
}
else
{
uint32_t v___x_898_; 
v___x_898_ = 2147483648;
return v___x_898_;
}
}
}
v___jp_899_:
{
uint32_t v___x_903_; uint32_t v___x_904_; 
v___x_903_ = lean_uint32_land(v___y_900_, v___y_901_);
v___x_904_ = lean_uint32_lor(v___y_902_, v___x_903_);
return v___x_904_;
}
v___jp_905_:
{
uint8_t v___x_910_; 
v___x_910_ = lean_uint64_dec_eq(v___y_909_, v___y_907_);
if (v___x_910_ == 0)
{
uint64_t v___x_911_; uint8_t v___x_912_; 
v___x_911_ = 8388608ULL;
v___x_912_ = lean_uint64_dec_eq(v___y_909_, v___x_911_);
if (v___x_912_ == 0)
{
uint32_t v___x_913_; 
v___x_913_ = lean_uint64_to_uint32(v___y_909_);
if (v___y_906_ == 0)
{
uint32_t v___x_914_; 
v___x_914_ = 0;
v___y_900_ = v___x_913_;
v___y_901_ = v___y_908_;
v___y_902_ = v___x_914_;
goto v___jp_899_;
}
else
{
uint32_t v___x_915_; 
v___x_915_ = 2147483648;
v___y_900_ = v___x_913_;
v___y_901_ = v___y_908_;
v___y_902_ = v___x_915_;
goto v___jp_899_;
}
}
else
{
if (v___y_906_ == 0)
{
uint32_t v___x_916_; 
v___x_916_ = 0;
v___y_137_ = v___x_916_;
goto v___jp_136_;
}
else
{
uint32_t v___x_917_; 
v___x_917_ = 2147483648;
v___y_137_ = v___x_917_;
goto v___jp_136_;
}
}
}
else
{
if (v___y_906_ == 0)
{
uint32_t v___x_918_; 
v___x_918_ = 0;
return v___x_918_;
}
else
{
uint32_t v___x_919_; 
v___x_919_ = 2147483648;
return v___x_919_;
}
}
}
v___jp_920_:
{
uint64_t v___x_929_; uint64_t v___x_930_; uint64_t v___x_931_; uint8_t v___x_932_; 
v___x_929_ = lean_uint64_mul(v___y_921_, v___y_922_);
v___x_930_ = lean_uint64_add(v___y_927_, v___y_928_);
v___x_931_ = 281474976710656ULL;
v___x_932_ = lean_uint64_dec_lt(v___x_929_, v___x_931_);
if (v___x_932_ == 0)
{
v___y_886_ = v___x_930_;
v___y_887_ = v___x_929_;
v___y_888_ = v___y_923_;
v___y_889_ = v___y_924_;
v___y_890_ = v___y_925_;
v___y_891_ = v___y_926_;
goto v___jp_885_;
}
else
{
uint64_t v___x_933_; uint8_t v___x_934_; 
v___x_933_ = 123ULL;
v___x_934_ = lean_uint64_dec_le(v___x_930_, v___x_933_);
if (v___x_934_ == 0)
{
v___y_886_ = v___x_930_;
v___y_887_ = v___x_929_;
v___y_888_ = v___y_923_;
v___y_889_ = v___y_924_;
v___y_890_ = v___y_925_;
v___y_891_ = v___y_926_;
goto v___jp_885_;
}
else
{
uint64_t v___x_935_; uint8_t v___x_936_; 
v___x_935_ = 0ULL;
v___x_936_ = lean_uint64_dec_eq(v___x_929_, v___x_935_);
if (v___x_936_ == 0)
{
uint64_t v___x_937_; uint64_t v___x_938_; uint8_t v___x_939_; 
v___x_937_ = 149ULL;
v___x_938_ = lean_uint64_sub(v___x_937_, v___x_930_);
v___x_939_ = lean_uint64_dec_eq(v___x_938_, v___x_935_);
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
v___y_906_ = v___y_924_;
v___y_907_ = v___x_935_;
v___y_908_ = v___y_925_;
v___y_909_ = v___x_935_;
goto v___jp_905_;
}
else
{
uint64_t v___x_943_; uint8_t v___x_944_; 
v___x_943_ = 9223372036854775808ULL;
v___x_944_ = lean_uint64_dec_lt(v___x_943_, v___x_929_);
if (v___x_944_ == 0)
{
v___y_906_ = v___y_924_;
v___y_907_ = v___x_935_;
v___y_908_ = v___y_925_;
v___y_909_ = v___x_935_;
goto v___jp_905_;
}
else
{
uint64_t v___x_945_; 
v___x_945_ = 1ULL;
v___y_906_ = v___y_924_;
v___y_907_ = v___x_935_;
v___y_908_ = v___y_925_;
v___y_909_ = v___x_945_;
goto v___jp_905_;
}
}
}
else
{
uint64_t v_quotient_946_; uint64_t v___x_947_; uint64_t v___x_948_; uint64_t v___x_949_; uint64_t v_remainder_950_; uint64_t v___x_951_; uint64_t v_half_952_; uint8_t v___x_953_; 
v_quotient_946_ = lean_uint64_shift_right(v___x_929_, v___x_938_);
v___x_947_ = 1ULL;
v___x_948_ = lean_uint64_shift_left(v___x_947_, v___x_938_);
v___x_949_ = lean_uint64_sub(v___x_948_, v___x_947_);
v_remainder_950_ = lean_uint64_land(v___x_929_, v___x_949_);
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
v___x_956_ = lean_uint64_dec_eq(v___x_955_, v___x_935_);
if (v___x_956_ == 0)
{
uint64_t v___x_957_; 
v___x_957_ = lean_uint64_add(v_quotient_946_, v___x_947_);
v___y_906_ = v___y_924_;
v___y_907_ = v___x_935_;
v___y_908_ = v___y_925_;
v___y_909_ = v___x_957_;
goto v___jp_905_;
}
else
{
v___y_906_ = v___y_924_;
v___y_907_ = v___x_935_;
v___y_908_ = v___y_925_;
v___y_909_ = v_quotient_946_;
goto v___jp_905_;
}
}
else
{
uint64_t v___x_958_; 
v___x_958_ = lean_uint64_add(v_quotient_946_, v___x_947_);
v___y_906_ = v___y_924_;
v___y_907_ = v___x_935_;
v___y_908_ = v___y_925_;
v___y_909_ = v___x_958_;
goto v___jp_905_;
}
}
else
{
v___y_906_ = v___y_924_;
v___y_907_ = v___x_935_;
v___y_908_ = v___y_925_;
v___y_909_ = v_quotient_946_;
goto v___jp_905_;
}
}
}
else
{
v___y_906_ = v___y_924_;
v___y_907_ = v___x_935_;
v___y_908_ = v___y_925_;
v___y_909_ = v___x_929_;
goto v___jp_905_;
}
}
else
{
if (v___y_924_ == 0)
{
uint32_t v___x_959_; 
v___x_959_ = 0;
return v___x_959_;
}
else
{
uint32_t v___x_960_; 
v___x_960_ = 2147483648;
return v___x_960_;
}
}
}
}
}
v___jp_961_:
{
uint64_t v___x_970_; uint64_t v___x_971_; uint8_t v___x_972_; 
v___x_970_ = lean_uint32_to_uint64(v___y_968_);
v___x_971_ = 0ULL;
v___x_972_ = lean_uint64_dec_eq(v___x_970_, v___x_971_);
if (v___x_972_ == 0)
{
uint64_t v___x_973_; uint64_t v___x_974_; 
v___x_973_ = 1ULL;
v___x_974_ = lean_uint64_sub(v___x_970_, v___x_973_);
v___y_921_ = v___y_962_;
v___y_922_ = v___y_963_;
v___y_923_ = v___y_964_;
v___y_924_ = v___y_965_;
v___y_925_ = v___y_966_;
v___y_926_ = v___y_967_;
v___y_927_ = v___y_969_;
v___y_928_ = v___x_974_;
goto v___jp_920_;
}
else
{
v___y_921_ = v___y_962_;
v___y_922_ = v___y_963_;
v___y_923_ = v___y_964_;
v___y_924_ = v___y_965_;
v___y_925_ = v___y_966_;
v___y_926_ = v___y_967_;
v___y_927_ = v___y_969_;
v___y_928_ = v___x_971_;
goto v___jp_920_;
}
}
v___jp_975_:
{
uint64_t v___x_984_; uint64_t v___x_985_; uint8_t v___x_986_; 
v___x_984_ = lean_uint32_to_uint64(v___y_979_);
v___x_985_ = 0ULL;
v___x_986_ = lean_uint64_dec_eq(v___x_984_, v___x_985_);
if (v___x_986_ == 0)
{
uint64_t v___x_987_; uint64_t v___x_988_; 
v___x_987_ = 1ULL;
v___x_988_ = lean_uint64_sub(v___x_984_, v___x_987_);
v___y_962_ = v___y_976_;
v___y_963_ = v___y_983_;
v___y_964_ = v___y_977_;
v___y_965_ = v___y_978_;
v___y_966_ = v___y_980_;
v___y_967_ = v___y_981_;
v___y_968_ = v___y_982_;
v___y_969_ = v___x_988_;
goto v___jp_961_;
}
else
{
v___y_962_ = v___y_976_;
v___y_963_ = v___y_983_;
v___y_964_ = v___y_977_;
v___y_965_ = v___y_978_;
v___y_966_ = v___y_980_;
v___y_967_ = v___y_981_;
v___y_968_ = v___y_982_;
v___y_969_ = v___x_985_;
goto v___jp_961_;
}
}
v___jp_989_:
{
uint32_t v___x_998_; uint8_t v___x_999_; 
v___x_998_ = 0;
v___x_999_ = lean_uint32_dec_eq(v___y_996_, v___x_998_);
if (v___x_999_ == 0)
{
uint64_t v___x_1000_; uint64_t v___x_1001_; uint64_t v___x_1002_; 
v___x_1000_ = lean_uint32_to_uint64(v___y_995_);
v___x_1001_ = 8388608ULL;
v___x_1002_ = lean_uint64_lor(v___x_1000_, v___x_1001_);
v___y_976_ = v___y_997_;
v___y_977_ = v___y_990_;
v___y_978_ = v___y_991_;
v___y_979_ = v___y_992_;
v___y_980_ = v___y_993_;
v___y_981_ = v___y_994_;
v___y_982_ = v___y_996_;
v___y_983_ = v___x_1002_;
goto v___jp_975_;
}
else
{
uint64_t v___x_1003_; 
v___x_1003_ = lean_uint32_to_uint64(v___y_995_);
v___y_976_ = v___y_997_;
v___y_977_ = v___y_990_;
v___y_978_ = v___y_991_;
v___y_979_ = v___y_992_;
v___y_980_ = v___y_993_;
v___y_981_ = v___y_994_;
v___y_982_ = v___y_996_;
v___y_983_ = v___x_1003_;
goto v___jp_975_;
}
}
v___jp_1004_:
{
uint32_t v___x_1010_; uint32_t v_xFraction_1011_; uint32_t v_yFraction_1012_; uint32_t v___x_1013_; uint8_t v___x_1014_; 
v___x_1010_ = 8388607;
v_xFraction_1011_ = lean_uint32_land(v___y_130_, v___x_1010_);
v_yFraction_1012_ = lean_uint32_land(v___y_131_, v___x_1010_);
v___x_1013_ = 0;
v___x_1014_ = lean_uint32_dec_eq(v___y_1006_, v___x_1013_);
if (v___x_1014_ == 0)
{
uint64_t v___x_1015_; uint64_t v___x_1016_; uint64_t v___x_1017_; 
v___x_1015_ = lean_uint32_to_uint64(v_xFraction_1011_);
v___x_1016_ = 8388608ULL;
v___x_1017_ = lean_uint64_lor(v___x_1015_, v___x_1016_);
v___y_990_ = v___y_1005_;
v___y_991_ = v___y_1009_;
v___y_992_ = v___y_1006_;
v___y_993_ = v___x_1010_;
v___y_994_ = v___y_1007_;
v___y_995_ = v_yFraction_1012_;
v___y_996_ = v___y_1008_;
v___y_997_ = v___x_1017_;
goto v___jp_989_;
}
else
{
uint64_t v___x_1018_; 
v___x_1018_ = lean_uint32_to_uint64(v_xFraction_1011_);
v___y_990_ = v___y_1005_;
v___y_991_ = v___y_1009_;
v___y_992_ = v___y_1006_;
v___y_993_ = v___x_1010_;
v___y_994_ = v___y_1007_;
v___y_995_ = v_yFraction_1012_;
v___y_996_ = v___y_1008_;
v___y_997_ = v___x_1018_;
goto v___jp_989_;
}
}
v___jp_1019_:
{
if (v___y_1026_ == 0)
{
if (v___y_1027_ == 0)
{
v___y_1005_ = v___y_1022_;
v___y_1006_ = v___y_1023_;
v___y_1007_ = v___y_1024_;
v___y_1008_ = v___y_1025_;
v___y_1009_ = v___y_1021_;
goto v___jp_1004_;
}
else
{
v___y_1005_ = v___y_1022_;
v___y_1006_ = v___y_1023_;
v___y_1007_ = v___y_1024_;
v___y_1008_ = v___y_1025_;
v___y_1009_ = v___y_1020_;
goto v___jp_1004_;
}
}
else
{
if (v___y_1027_ == 0)
{
v___y_1005_ = v___y_1022_;
v___y_1006_ = v___y_1023_;
v___y_1007_ = v___y_1024_;
v___y_1008_ = v___y_1025_;
v___y_1009_ = v___y_1020_;
goto v___jp_1004_;
}
else
{
v___y_1005_ = v___y_1022_;
v___y_1006_ = v___y_1023_;
v___y_1007_ = v___y_1024_;
v___y_1008_ = v___y_1025_;
v___y_1009_ = v___y_1021_;
goto v___jp_1004_;
}
}
}
v___jp_1028_:
{
uint32_t v___x_1036_; uint32_t v___x_1037_; uint32_t v___x_1038_; uint8_t v___x_1039_; 
v___x_1036_ = 2147483648;
v___x_1037_ = lean_uint32_land(v___y_131_, v___x_1036_);
v___x_1038_ = 0;
v___x_1039_ = lean_uint32_dec_eq(v___x_1037_, v___x_1038_);
if (v___x_1039_ == 0)
{
v___y_1020_ = v___y_1029_;
v___y_1021_ = v___y_1030_;
v___y_1022_ = v___y_1031_;
v___y_1023_ = v___y_1032_;
v___y_1024_ = v___y_1033_;
v___y_1025_ = v___y_1034_;
v___y_1026_ = v___y_1035_;
v___y_1027_ = v___y_1029_;
goto v___jp_1019_;
}
else
{
v___y_1020_ = v___y_1029_;
v___y_1021_ = v___y_1030_;
v___y_1022_ = v___y_1031_;
v___y_1023_ = v___y_1032_;
v___y_1024_ = v___y_1033_;
v___y_1025_ = v___y_1034_;
v___y_1026_ = v___y_1035_;
v___y_1027_ = v___y_1030_;
goto v___jp_1019_;
}
}
v___jp_1040_:
{
if (v___y_1046_ == 0)
{
uint32_t v___x_1047_; uint32_t v___x_1048_; uint32_t v___x_1049_; uint8_t v___x_1050_; 
v___x_1047_ = 2147483648;
v___x_1048_ = lean_uint32_land(v___y_130_, v___x_1047_);
v___x_1049_ = 0;
v___x_1050_ = lean_uint32_dec_eq(v___x_1048_, v___x_1049_);
if (v___x_1050_ == 0)
{
v___y_1029_ = v___y_1041_;
v___y_1030_ = v___y_1046_;
v___y_1031_ = v___y_1042_;
v___y_1032_ = v___y_1043_;
v___y_1033_ = v___y_1044_;
v___y_1034_ = v___y_1045_;
v___y_1035_ = v___y_1041_;
goto v___jp_1028_;
}
else
{
v___y_1029_ = v___y_1041_;
v___y_1030_ = v___y_1046_;
v___y_1031_ = v___y_1042_;
v___y_1032_ = v___y_1043_;
v___y_1033_ = v___y_1044_;
v___y_1034_ = v___y_1045_;
v___y_1035_ = v___y_1046_;
goto v___jp_1028_;
}
}
else
{
lean_object* v___x_1051_; lean_object* v___x_1052_; lean_object* v___x_1053_; uint32_t v___x_1054_; 
v___x_1051_ = lean_uint32_to_nat(v___y_130_);
v___x_1052_ = lean_uint32_to_nat(v___y_131_);
v___x_1053_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1051_, v___x_1052_);
v___x_1054_ = lean_uint32_of_nat(v___x_1053_);
lean_dec(v___x_1053_);
return v___x_1054_;
}
}
v___jp_1055_:
{
uint32_t v___x_1061_; uint32_t v___x_1062_; uint32_t v___x_1063_; uint32_t v___x_1064_; uint64_t v___x_1065_; uint32_t v___x_1066_; uint32_t v___x_1067_; uint64_t v___x_1068_; uint64_t v___x_1069_; uint64_t v___x_1070_; uint64_t v_high_1071_; uint64_t v___x_1072_; uint64_t v_carry_1073_; uint32_t v___x_1074_; uint8_t v___x_1075_; uint8_t v___x_1076_; 
v___x_1061_ = 8388607;
v___x_1062_ = lean_uint32_land(v___y_130_, v___x_1061_);
v___x_1063_ = 8388608;
v___x_1064_ = lean_uint32_lor(v___x_1062_, v___x_1063_);
v___x_1065_ = lean_uint32_to_uint64(v___x_1064_);
v___x_1066_ = lean_uint32_land(v___y_131_, v___x_1061_);
v___x_1067_ = lean_uint32_lor(v___x_1066_, v___x_1063_);
v___x_1068_ = lean_uint32_to_uint64(v___x_1067_);
v___x_1069_ = lean_uint64_mul(v___x_1065_, v___x_1068_);
v___x_1070_ = 47ULL;
v_high_1071_ = lean_uint64_shift_right(v___x_1069_, v___x_1070_);
v___x_1072_ = 24ULL;
v_carry_1073_ = lean_uint64_shift_right(v___y_1060_, v___x_1072_);
v___x_1074_ = 2147483648;
v___x_1075_ = lean_uint32_dec_le(v___x_1074_, v___y_130_);
v___x_1076_ = lean_uint32_dec_le(v___x_1074_, v___y_131_);
if (v___x_1075_ == 0)
{
if (v___x_1076_ == 0)
{
v___y_583_ = v___x_1061_;
v___y_584_ = v___y_1056_;
v___y_585_ = v___y_1060_;
v___y_586_ = v_high_1071_;
v___y_587_ = v_carry_1073_;
v___y_588_ = v___y_1058_;
v___y_589_ = v___y_1059_;
goto v___jp_582_;
}
else
{
v___y_592_ = v___x_1061_;
v___y_593_ = v___y_1056_;
v___y_594_ = v___y_1060_;
v___y_595_ = v_high_1071_;
v___y_596_ = v_carry_1073_;
v___y_597_ = v___y_1058_;
v___y_598_ = v___y_1057_;
v___y_599_ = v___y_1059_;
v___y_600_ = v___x_1075_;
goto v___jp_591_;
}
}
else
{
v___y_592_ = v___x_1061_;
v___y_593_ = v___y_1056_;
v___y_594_ = v___y_1060_;
v___y_595_ = v_high_1071_;
v___y_596_ = v_carry_1073_;
v___y_597_ = v___y_1058_;
v___y_598_ = v___y_1057_;
v___y_599_ = v___y_1059_;
v___y_600_ = v___x_1076_;
goto v___jp_591_;
}
}
v___jp_1077_:
{
uint64_t v___x_1086_; uint64_t v___x_1087_; uint64_t v___x_1088_; 
v___x_1086_ = lean_uint64_lor(v___y_1078_, v___y_1085_);
v___x_1087_ = lean_uint64_land(v___y_1083_, v___x_1086_);
v___x_1088_ = lean_uint64_add(v___y_1080_, v___x_1087_);
v___y_1056_ = v___y_1079_;
v___y_1057_ = v___y_1082_;
v___y_1058_ = v___y_1081_;
v___y_1059_ = v___y_1084_;
v___y_1060_ = v___x_1088_;
goto v___jp_1055_;
}
v___jp_1089_:
{
uint64_t v___x_1098_; uint64_t v___x_1099_; uint8_t v___x_1100_; 
v___x_1098_ = lean_uint64_land(v___y_1091_, v___y_1092_);
v___x_1099_ = 0ULL;
v___x_1100_ = lean_uint64_dec_eq(v___x_1098_, v___x_1099_);
if (v___x_1100_ == 0)
{
v___y_1078_ = v___y_1097_;
v___y_1079_ = v___y_1090_;
v___y_1080_ = v___y_1091_;
v___y_1081_ = v___y_1094_;
v___y_1082_ = v___y_1093_;
v___y_1083_ = v___y_1095_;
v___y_1084_ = v___y_1096_;
v___y_1085_ = v___y_1092_;
goto v___jp_1077_;
}
else
{
v___y_1078_ = v___y_1097_;
v___y_1079_ = v___y_1090_;
v___y_1080_ = v___y_1091_;
v___y_1081_ = v___y_1094_;
v___y_1082_ = v___y_1093_;
v___y_1083_ = v___y_1095_;
v___y_1084_ = v___y_1096_;
v___y_1085_ = v___x_1099_;
goto v___jp_1077_;
}
}
v___jp_1101_:
{
if (v___y_1102_ == 0)
{
uint64_t v___x_1110_; 
v___x_1110_ = 0ULL;
v___y_1090_ = v___y_1103_;
v___y_1091_ = v___y_1104_;
v___y_1092_ = v___y_1107_;
v___y_1093_ = v___y_1106_;
v___y_1094_ = v___y_1105_;
v___y_1095_ = v___y_1109_;
v___y_1096_ = v___y_1108_;
v___y_1097_ = v___x_1110_;
goto v___jp_1089_;
}
else
{
v___y_1090_ = v___y_1103_;
v___y_1091_ = v___y_1104_;
v___y_1092_ = v___y_1107_;
v___y_1093_ = v___y_1106_;
v___y_1094_ = v___y_1105_;
v___y_1095_ = v___y_1109_;
v___y_1096_ = v___y_1108_;
v___y_1097_ = v___y_1107_;
goto v___jp_1089_;
}
}
v___jp_1111_:
{
uint64_t v___x_1120_; uint64_t v___x_1121_; uint64_t v___x_1122_; 
v___x_1120_ = lean_uint64_lor(v___y_1117_, v___y_1119_);
v___x_1121_ = lean_uint64_land(v___y_1116_, v___x_1120_);
v___x_1122_ = lean_uint64_add(v___y_1112_, v___x_1121_);
v___y_1056_ = v___y_1113_;
v___y_1057_ = v___y_1115_;
v___y_1058_ = v___y_1114_;
v___y_1059_ = v___y_1118_;
v___y_1060_ = v___x_1122_;
goto v___jp_1055_;
}
v___jp_1123_:
{
uint64_t v___x_1132_; uint64_t v___x_1133_; uint8_t v___x_1134_; 
v___x_1132_ = lean_uint64_land(v___y_1124_, v___y_1128_);
v___x_1133_ = 0ULL;
v___x_1134_ = lean_uint64_dec_eq(v___x_1132_, v___x_1133_);
if (v___x_1134_ == 0)
{
v___y_1112_ = v___y_1124_;
v___y_1113_ = v___y_1125_;
v___y_1114_ = v___y_1127_;
v___y_1115_ = v___y_1126_;
v___y_1116_ = v___y_1129_;
v___y_1117_ = v___y_1131_;
v___y_1118_ = v___y_1130_;
v___y_1119_ = v___y_1128_;
goto v___jp_1111_;
}
else
{
v___y_1112_ = v___y_1124_;
v___y_1113_ = v___y_1125_;
v___y_1114_ = v___y_1127_;
v___y_1115_ = v___y_1126_;
v___y_1116_ = v___y_1129_;
v___y_1117_ = v___y_1131_;
v___y_1118_ = v___y_1130_;
v___y_1119_ = v___x_1133_;
goto v___jp_1111_;
}
}
v___jp_1135_:
{
if (v___y_1136_ == 0)
{
uint64_t v___x_1144_; 
v___x_1144_ = 0ULL;
v___y_1124_ = v___y_1137_;
v___y_1125_ = v___y_1138_;
v___y_1126_ = v___y_1140_;
v___y_1127_ = v___y_1139_;
v___y_1128_ = v___y_1141_;
v___y_1129_ = v___y_1143_;
v___y_1130_ = v___y_1142_;
v___y_1131_ = v___x_1144_;
goto v___jp_1123_;
}
else
{
v___y_1124_ = v___y_1137_;
v___y_1125_ = v___y_1138_;
v___y_1126_ = v___y_1140_;
v___y_1127_ = v___y_1139_;
v___y_1128_ = v___y_1141_;
v___y_1129_ = v___y_1143_;
v___y_1130_ = v___y_1142_;
v___y_1131_ = v___y_1141_;
goto v___jp_1123_;
}
}
v___jp_1145_:
{
uint32_t v___x_1151_; uint32_t v_xFraction_1152_; uint32_t v_yFraction_1153_; uint32_t v___x_1154_; uint8_t v___x_1155_; 
v___x_1151_ = 8388607;
v_xFraction_1152_ = lean_uint32_land(v___y_130_, v___x_1151_);
v_yFraction_1153_ = lean_uint32_land(v___y_131_, v___x_1151_);
v___x_1154_ = 0;
v___x_1155_ = lean_uint32_dec_eq(v___y_1147_, v___x_1154_);
if (v___x_1155_ == 0)
{
uint64_t v___x_1156_; uint64_t v___x_1157_; uint64_t v___x_1158_; 
v___x_1156_ = lean_uint32_to_uint64(v_xFraction_1152_);
v___x_1157_ = 8388608ULL;
v___x_1158_ = lean_uint64_lor(v___x_1156_, v___x_1157_);
v___y_537_ = v___y_1146_;
v___y_538_ = v___y_1148_;
v___y_539_ = v___y_1147_;
v___y_540_ = v___x_1151_;
v___y_541_ = v___y_1149_;
v___y_542_ = v___y_1150_;
v___y_543_ = v_yFraction_1153_;
v___y_544_ = v___x_1158_;
goto v___jp_536_;
}
else
{
uint64_t v___x_1159_; 
v___x_1159_ = lean_uint32_to_uint64(v_xFraction_1152_);
v___y_537_ = v___y_1146_;
v___y_538_ = v___y_1148_;
v___y_539_ = v___y_1147_;
v___y_540_ = v___x_1151_;
v___y_541_ = v___y_1149_;
v___y_542_ = v___y_1150_;
v___y_543_ = v_yFraction_1153_;
v___y_544_ = v___x_1159_;
goto v___jp_536_;
}
}
v___jp_1160_:
{
uint8_t v___x_1165_; 
v___x_1165_ = 1;
v___y_1146_ = v___y_1161_;
v___y_1147_ = v___y_1163_;
v___y_1148_ = v___y_1162_;
v___y_1149_ = v___y_1164_;
v___y_1150_ = v___x_1165_;
goto v___jp_1145_;
}
v___jp_1166_:
{
if (v___y_1171_ == 0)
{
if (v___y_1173_ == 0)
{
v___y_1146_ = v___y_1167_;
v___y_1147_ = v___y_1169_;
v___y_1148_ = v___y_1168_;
v___y_1149_ = v___y_1172_;
v___y_1150_ = v___y_1170_;
goto v___jp_1145_;
}
else
{
v___y_1161_ = v___y_1167_;
v___y_1162_ = v___y_1168_;
v___y_1163_ = v___y_1169_;
v___y_1164_ = v___y_1172_;
goto v___jp_1160_;
}
}
else
{
if (v___y_1173_ == 0)
{
v___y_1161_ = v___y_1167_;
v___y_1162_ = v___y_1168_;
v___y_1163_ = v___y_1169_;
v___y_1164_ = v___y_1172_;
goto v___jp_1160_;
}
else
{
v___y_1146_ = v___y_1167_;
v___y_1147_ = v___y_1169_;
v___y_1148_ = v___y_1168_;
v___y_1149_ = v___y_1172_;
v___y_1150_ = v___y_1170_;
goto v___jp_1145_;
}
}
}
v___jp_1174_:
{
uint32_t v___x_1181_; uint32_t v___x_1182_; uint32_t v___x_1183_; uint8_t v___x_1184_; 
v___x_1181_ = 2147483648;
v___x_1182_ = lean_uint32_land(v___y_131_, v___x_1181_);
v___x_1183_ = 0;
v___x_1184_ = lean_uint32_dec_eq(v___x_1182_, v___x_1183_);
if (v___x_1184_ == 0)
{
uint8_t v___x_1185_; 
v___x_1185_ = 1;
v___y_1167_ = v___y_1175_;
v___y_1168_ = v___y_1177_;
v___y_1169_ = v___y_1176_;
v___y_1170_ = v___y_1178_;
v___y_1171_ = v___y_1180_;
v___y_1172_ = v___y_1179_;
v___y_1173_ = v___x_1185_;
goto v___jp_1166_;
}
else
{
v___y_1167_ = v___y_1175_;
v___y_1168_ = v___y_1177_;
v___y_1169_ = v___y_1176_;
v___y_1170_ = v___y_1178_;
v___y_1171_ = v___y_1180_;
v___y_1172_ = v___y_1179_;
v___y_1173_ = v___y_1178_;
goto v___jp_1166_;
}
}
v___jp_1186_:
{
if (v___y_1191_ == 0)
{
uint32_t v___x_1192_; uint32_t v___x_1193_; uint32_t v___x_1194_; uint8_t v___x_1195_; 
v___x_1192_ = 2147483648;
v___x_1193_ = lean_uint32_land(v___y_130_, v___x_1192_);
v___x_1194_ = 0;
v___x_1195_ = lean_uint32_dec_eq(v___x_1193_, v___x_1194_);
if (v___x_1195_ == 0)
{
uint8_t v___x_1196_; 
v___x_1196_ = 1;
v___y_1175_ = v___y_1187_;
v___y_1176_ = v___y_1188_;
v___y_1177_ = v___y_1189_;
v___y_1178_ = v___y_1191_;
v___y_1179_ = v___y_1190_;
v___y_1180_ = v___x_1196_;
goto v___jp_1174_;
}
else
{
v___y_1175_ = v___y_1187_;
v___y_1176_ = v___y_1188_;
v___y_1177_ = v___y_1189_;
v___y_1178_ = v___y_1191_;
v___y_1179_ = v___y_1190_;
v___y_1180_ = v___y_1191_;
goto v___jp_1174_;
}
}
else
{
lean_object* v___x_1197_; lean_object* v___x_1198_; lean_object* v___x_1199_; uint32_t v___x_1200_; 
v___x_1197_ = lean_uint32_to_nat(v___y_130_);
v___x_1198_ = lean_uint32_to_nat(v___y_131_);
v___x_1199_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1197_, v___x_1198_);
v___x_1200_ = lean_uint32_of_nat(v___x_1199_);
lean_dec(v___x_1199_);
return v___x_1200_;
}
}
v___jp_1201_:
{
if (v___y_1202_ == 0)
{
uint32_t v___x_1203_; 
v___x_1203_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_1203_;
}
else
{
uint32_t v___x_1204_; uint32_t v___x_1205_; 
v___x_1204_ = 4194304;
v___x_1205_ = lean_uint32_lor(v___y_131_, v___x_1204_);
return v___x_1205_;
}
}
v___jp_1206_:
{
uint32_t v___x_1207_; uint32_t v___x_1208_; uint32_t v___x_1209_; uint32_t v___x_1210_; uint8_t v___x_1211_; 
v___x_1207_ = 23;
v___x_1208_ = lean_uint32_shift_right(v___y_131_, v___x_1207_);
v___x_1209_ = 255;
v___x_1210_ = lean_uint32_land(v___x_1208_, v___x_1209_);
v___x_1211_ = lean_uint32_dec_eq(v___x_1210_, v___x_1209_);
if (v___x_1211_ == 0)
{
v___y_1202_ = v___x_1211_;
goto v___jp_1201_;
}
else
{
uint32_t v___x_1212_; uint32_t v___x_1213_; uint32_t v___x_1214_; uint8_t v___x_1215_; 
v___x_1212_ = 8388607;
v___x_1213_ = lean_uint32_land(v___y_131_, v___x_1212_);
v___x_1214_ = 0;
v___x_1215_ = lean_uint32_dec_eq(v___x_1213_, v___x_1214_);
if (v___x_1215_ == 0)
{
v___y_1202_ = v___x_1211_;
goto v___jp_1201_;
}
else
{
uint32_t v___x_1216_; 
v___x_1216_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_1216_;
}
}
}
v___jp_1217_:
{
if (v___y_1218_ == 0)
{
goto v___jp_1206_;
}
else
{
uint32_t v___x_1219_; uint32_t v___x_1220_; 
v___x_1219_ = 4194304;
v___x_1220_ = lean_uint32_lor(v___y_130_, v___x_1219_);
return v___x_1220_;
}
}
v___jp_1221_:
{
uint32_t v___x_1222_; uint32_t v___x_1223_; uint32_t v___x_1224_; uint32_t v___x_1225_; uint8_t v___x_1226_; 
v___x_1222_ = 23;
v___x_1223_ = lean_uint32_shift_right(v___y_130_, v___x_1222_);
v___x_1224_ = 255;
v___x_1225_ = lean_uint32_land(v___x_1223_, v___x_1224_);
v___x_1226_ = lean_uint32_dec_eq(v___x_1225_, v___x_1224_);
if (v___x_1226_ == 0)
{
v___y_1218_ = v___x_1226_;
goto v___jp_1217_;
}
else
{
uint32_t v___x_1227_; uint32_t v___x_1228_; uint32_t v___x_1229_; uint8_t v___x_1230_; 
v___x_1227_ = 8388607;
v___x_1228_ = lean_uint32_land(v___y_130_, v___x_1227_);
v___x_1229_ = 0;
v___x_1230_ = lean_uint32_dec_eq(v___x_1228_, v___x_1229_);
if (v___x_1230_ == 0)
{
v___y_1218_ = v___x_1226_;
goto v___jp_1217_;
}
else
{
goto v___jp_1206_;
}
}
}
v___jp_1231_:
{
if (v___y_1232_ == 0)
{
goto v___jp_1221_;
}
else
{
uint32_t v___x_1233_; uint32_t v___x_1234_; uint32_t v___x_1235_; uint8_t v___x_1236_; 
v___x_1233_ = 4194304;
v___x_1234_ = lean_uint32_land(v___y_131_, v___x_1233_);
v___x_1235_ = 0;
v___x_1236_ = lean_uint32_dec_eq(v___x_1234_, v___x_1235_);
if (v___x_1236_ == 0)
{
goto v___jp_1221_;
}
else
{
uint32_t v___x_1237_; 
v___x_1237_ = lean_uint32_lor(v___y_131_, v___x_1233_);
return v___x_1237_;
}
}
}
v___jp_1238_:
{
uint32_t v___x_1239_; uint32_t v___x_1240_; uint32_t v___x_1241_; uint32_t v___x_1242_; uint8_t v___x_1243_; 
v___x_1239_ = 23;
v___x_1240_ = lean_uint32_shift_right(v___y_131_, v___x_1239_);
v___x_1241_ = 255;
v___x_1242_ = lean_uint32_land(v___x_1240_, v___x_1241_);
v___x_1243_ = lean_uint32_dec_eq(v___x_1242_, v___x_1241_);
if (v___x_1243_ == 0)
{
v___y_1232_ = v___x_1243_;
goto v___jp_1231_;
}
else
{
uint32_t v___x_1244_; uint32_t v___x_1245_; uint32_t v___x_1246_; uint8_t v___x_1247_; 
v___x_1244_ = 8388607;
v___x_1245_ = lean_uint32_land(v___y_131_, v___x_1244_);
v___x_1246_ = 0;
v___x_1247_ = lean_uint32_dec_eq(v___x_1245_, v___x_1246_);
if (v___x_1247_ == 0)
{
v___y_1232_ = v___x_1243_;
goto v___jp_1231_;
}
else
{
goto v___jp_1221_;
}
}
}
v___jp_1248_:
{
if (v___y_1249_ == 0)
{
goto v___jp_1238_;
}
else
{
uint32_t v___x_1250_; uint32_t v___x_1251_; uint32_t v___x_1252_; uint8_t v___x_1253_; 
v___x_1250_ = 4194304;
v___x_1251_ = lean_uint32_land(v___y_130_, v___x_1250_);
v___x_1252_ = 0;
v___x_1253_ = lean_uint32_dec_eq(v___x_1251_, v___x_1252_);
if (v___x_1253_ == 0)
{
goto v___jp_1238_;
}
else
{
uint32_t v___x_1254_; 
v___x_1254_ = lean_uint32_lor(v___y_130_, v___x_1250_);
return v___x_1254_;
}
}
}
v___jp_1255_:
{
float v_result_1258_; uint8_t v___x_1259_; 
v_result_1258_ = lean_float32_mul(v___y_1256_, v___y_1257_);
v___x_1259_ = lean_float32_beq(v_result_1258_, v_result_1258_);
if (v___x_1259_ == 0)
{
uint32_t v___x_1260_; uint32_t v___x_1261_; uint32_t v___x_1262_; uint32_t v___x_1263_; uint8_t v___x_1264_; 
v___x_1260_ = 23;
v___x_1261_ = lean_uint32_shift_right(v___y_130_, v___x_1260_);
v___x_1262_ = 255;
v___x_1263_ = lean_uint32_land(v___x_1261_, v___x_1262_);
v___x_1264_ = lean_uint32_dec_eq(v___x_1263_, v___x_1262_);
if (v___x_1264_ == 0)
{
v___y_1249_ = v___x_1264_;
goto v___jp_1248_;
}
else
{
uint32_t v___x_1265_; uint32_t v___x_1266_; uint32_t v___x_1267_; uint8_t v___x_1268_; 
v___x_1265_ = 8388607;
v___x_1266_ = lean_uint32_land(v___y_130_, v___x_1265_);
v___x_1267_ = 0;
v___x_1268_ = lean_uint32_dec_eq(v___x_1266_, v___x_1267_);
if (v___x_1268_ == 0)
{
v___y_1249_ = v___x_1264_;
goto v___jp_1248_;
}
else
{
goto v___jp_1238_;
}
}
}
else
{
uint32_t v___x_1269_; 
v___x_1269_ = lean_float32_to_bits(v_result_1258_);
return v___x_1269_;
}
}
v___jp_1270_:
{
if (v___y_1272_ == 0)
{
float v___x_1273_; 
v___x_1273_ = lean_float32_of_bits(v___y_131_);
v___y_1256_ = v___y_1271_;
v___y_1257_ = v___x_1273_;
goto v___jp_1255_;
}
else
{
uint32_t v___x_1274_; uint32_t v___x_1275_; uint32_t v___x_1276_; uint32_t v___x_1277_; float v___x_1278_; lean_object* v___x_1279_; uint32_t v___x_1280_; uint32_t v___x_1281_; lean_object* v___x_1282_; lean_object* v___x_1283_; float v___x_1284_; float v___x_1285_; 
v___x_1274_ = 8388607;
v___x_1275_ = lean_uint32_land(v___y_131_, v___x_1274_);
v___x_1276_ = 8388608;
v___x_1277_ = lean_uint32_lor(v___x_1275_, v___x_1276_);
v___x_1278_ = lean_uint32_to_float32(v___x_1277_);
v___x_1279_ = lp_competition_R2W01b_scaleTable;
v___x_1280_ = 23;
v___x_1281_ = lean_uint32_shift_right(v___y_131_, v___x_1280_);
v___x_1282_ = lean_uint32_to_nat(v___x_1281_);
v___x_1283_ = lean_array_fget_borrowed(v___x_1279_, v___x_1282_);
lean_dec(v___x_1282_);
v___x_1284_ = lean_unbox_float32(v___x_1283_);
v___x_1285_ = lean_float32_mul(v___x_1278_, v___x_1284_);
v___y_1256_ = v___y_1271_;
v___y_1257_ = v___x_1285_;
goto v___jp_1255_;
}
}
v___jp_1286_:
{
uint32_t v___x_1288_; uint32_t v_a_1289_; uint32_t v___x_1290_; uint32_t v___x_1291_; uint32_t v___x_1292_; uint8_t v___x_1293_; 
v___x_1288_ = 2147483647;
v_a_1289_ = lean_uint32_land(v___y_131_, v___x_1288_);
v___x_1290_ = 201326591;
v___x_1291_ = 1;
v___x_1292_ = lean_uint32_sub(v_a_1289_, v___x_1291_);
v___x_1293_ = lean_uint32_dec_le(v___x_1290_, v___x_1292_);
if (v___x_1293_ == 0)
{
v___y_1271_ = v___y_1287_;
v___y_1272_ = v___x_1293_;
goto v___jp_1270_;
}
else
{
uint32_t v___x_1294_; uint8_t v___x_1295_; 
v___x_1294_ = 2139095040;
v___x_1295_ = lean_uint32_dec_lt(v_a_1289_, v___x_1294_);
v___y_1271_ = v___y_1287_;
v___y_1272_ = v___x_1295_;
goto v___jp_1270_;
}
}
v___jp_1296_:
{
if (v___y_1298_ == 0)
{
float v___x_1299_; 
v___x_1299_ = lean_float32_of_bits(v___y_130_);
v___y_1287_ = v___x_1299_;
goto v___jp_1286_;
}
else
{
uint32_t v___x_1300_; uint32_t v___x_1301_; uint32_t v___x_1302_; uint32_t v___x_1303_; float v___x_1304_; lean_object* v___x_1305_; lean_object* v___x_1306_; lean_object* v___x_1307_; float v___x_1308_; float v___x_1309_; 
v___x_1300_ = 8388607;
v___x_1301_ = lean_uint32_land(v___y_130_, v___x_1300_);
v___x_1302_ = 8388608;
v___x_1303_ = lean_uint32_lor(v___x_1301_, v___x_1302_);
v___x_1304_ = lean_uint32_to_float32(v___x_1303_);
v___x_1305_ = lp_competition_R2W01b_scaleTable;
v___x_1306_ = lean_uint32_to_nat(v___y_1297_);
v___x_1307_ = lean_array_fget_borrowed(v___x_1305_, v___x_1306_);
lean_dec(v___x_1306_);
v___x_1308_ = lean_unbox_float32(v___x_1307_);
v___x_1309_ = lean_float32_mul(v___x_1304_, v___x_1308_);
v___y_1287_ = v___x_1309_;
goto v___jp_1286_;
}
}
v___jp_1310_:
{
if (v___y_1311_ == 0)
{
uint32_t v___x_1312_; 
v___x_1312_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_1312_;
}
else
{
uint32_t v___x_1313_; uint32_t v___x_1314_; 
v___x_1313_ = 4194304;
v___x_1314_ = lean_uint32_lor(v___y_131_, v___x_1313_);
return v___x_1314_;
}
}
v___jp_1315_:
{
uint32_t v___x_1316_; uint32_t v___x_1317_; uint32_t v___x_1318_; uint32_t v___x_1319_; uint8_t v___x_1320_; 
v___x_1316_ = 23;
v___x_1317_ = lean_uint32_shift_right(v___y_131_, v___x_1316_);
v___x_1318_ = 255;
v___x_1319_ = lean_uint32_land(v___x_1317_, v___x_1318_);
v___x_1320_ = lean_uint32_dec_eq(v___x_1319_, v___x_1318_);
if (v___x_1320_ == 0)
{
v___y_1311_ = v___x_1320_;
goto v___jp_1310_;
}
else
{
uint32_t v___x_1321_; uint32_t v___x_1322_; uint32_t v___x_1323_; uint8_t v___x_1324_; 
v___x_1321_ = 8388607;
v___x_1322_ = lean_uint32_land(v___y_131_, v___x_1321_);
v___x_1323_ = 0;
v___x_1324_ = lean_uint32_dec_eq(v___x_1322_, v___x_1323_);
if (v___x_1324_ == 0)
{
v___y_1311_ = v___x_1320_;
goto v___jp_1310_;
}
else
{
uint32_t v___x_1325_; 
v___x_1325_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_1325_;
}
}
}
v___jp_1326_:
{
if (v___y_1327_ == 0)
{
goto v___jp_1315_;
}
else
{
uint32_t v___x_1328_; uint32_t v___x_1329_; 
v___x_1328_ = 4194304;
v___x_1329_ = lean_uint32_lor(v___y_130_, v___x_1328_);
return v___x_1329_;
}
}
v___jp_1330_:
{
uint32_t v___x_1331_; uint32_t v___x_1332_; uint32_t v___x_1333_; uint32_t v___x_1334_; uint8_t v___x_1335_; 
v___x_1331_ = 23;
v___x_1332_ = lean_uint32_shift_right(v___y_130_, v___x_1331_);
v___x_1333_ = 255;
v___x_1334_ = lean_uint32_land(v___x_1332_, v___x_1333_);
v___x_1335_ = lean_uint32_dec_eq(v___x_1334_, v___x_1333_);
if (v___x_1335_ == 0)
{
v___y_1327_ = v___x_1335_;
goto v___jp_1326_;
}
else
{
uint32_t v___x_1336_; uint32_t v___x_1337_; uint32_t v___x_1338_; uint8_t v___x_1339_; 
v___x_1336_ = 8388607;
v___x_1337_ = lean_uint32_land(v___y_130_, v___x_1336_);
v___x_1338_ = 0;
v___x_1339_ = lean_uint32_dec_eq(v___x_1337_, v___x_1338_);
if (v___x_1339_ == 0)
{
v___y_1327_ = v___x_1335_;
goto v___jp_1326_;
}
else
{
goto v___jp_1315_;
}
}
}
v___jp_1340_:
{
if (v___y_1341_ == 0)
{
goto v___jp_1330_;
}
else
{
uint32_t v___x_1342_; uint32_t v___x_1343_; uint32_t v___x_1344_; uint8_t v___x_1345_; 
v___x_1342_ = 4194304;
v___x_1343_ = lean_uint32_land(v___y_131_, v___x_1342_);
v___x_1344_ = 0;
v___x_1345_ = lean_uint32_dec_eq(v___x_1343_, v___x_1344_);
if (v___x_1345_ == 0)
{
goto v___jp_1330_;
}
else
{
uint32_t v___x_1346_; 
v___x_1346_ = lean_uint32_lor(v___y_131_, v___x_1342_);
return v___x_1346_;
}
}
}
v___jp_1347_:
{
uint32_t v___x_1348_; uint32_t v___x_1349_; uint32_t v___x_1350_; uint32_t v___x_1351_; uint8_t v___x_1352_; 
v___x_1348_ = 23;
v___x_1349_ = lean_uint32_shift_right(v___y_131_, v___x_1348_);
v___x_1350_ = 255;
v___x_1351_ = lean_uint32_land(v___x_1349_, v___x_1350_);
v___x_1352_ = lean_uint32_dec_eq(v___x_1351_, v___x_1350_);
if (v___x_1352_ == 0)
{
v___y_1341_ = v___x_1352_;
goto v___jp_1340_;
}
else
{
uint32_t v___x_1353_; uint32_t v___x_1354_; uint32_t v___x_1355_; uint8_t v___x_1356_; 
v___x_1353_ = 8388607;
v___x_1354_ = lean_uint32_land(v___y_131_, v___x_1353_);
v___x_1355_ = 0;
v___x_1356_ = lean_uint32_dec_eq(v___x_1354_, v___x_1355_);
if (v___x_1356_ == 0)
{
v___y_1341_ = v___x_1352_;
goto v___jp_1340_;
}
else
{
goto v___jp_1330_;
}
}
}
v___jp_1357_:
{
if (v___y_1358_ == 0)
{
goto v___jp_1347_;
}
else
{
uint32_t v___x_1359_; uint32_t v___x_1360_; uint32_t v___x_1361_; uint8_t v___x_1362_; 
v___x_1359_ = 4194304;
v___x_1360_ = lean_uint32_land(v___y_130_, v___x_1359_);
v___x_1361_ = 0;
v___x_1362_ = lean_uint32_dec_eq(v___x_1360_, v___x_1361_);
if (v___x_1362_ == 0)
{
goto v___jp_1347_;
}
else
{
uint32_t v___x_1363_; 
v___x_1363_ = lean_uint32_lor(v___y_130_, v___x_1359_);
return v___x_1363_;
}
}
}
v___jp_1364_:
{
float v_result_1367_; uint8_t v___x_1368_; 
v_result_1367_ = lean_float32_mul(v___y_1365_, v___y_1366_);
v___x_1368_ = lean_float32_beq(v_result_1367_, v_result_1367_);
if (v___x_1368_ == 0)
{
uint32_t v___x_1369_; uint32_t v___x_1370_; uint32_t v___x_1371_; uint32_t v___x_1372_; uint8_t v___x_1373_; 
v___x_1369_ = 23;
v___x_1370_ = lean_uint32_shift_right(v___y_130_, v___x_1369_);
v___x_1371_ = 255;
v___x_1372_ = lean_uint32_land(v___x_1370_, v___x_1371_);
v___x_1373_ = lean_uint32_dec_eq(v___x_1372_, v___x_1371_);
if (v___x_1373_ == 0)
{
v___y_1358_ = v___x_1373_;
goto v___jp_1357_;
}
else
{
uint32_t v___x_1374_; uint32_t v___x_1375_; uint32_t v___x_1376_; uint8_t v___x_1377_; 
v___x_1374_ = 8388607;
v___x_1375_ = lean_uint32_land(v___y_130_, v___x_1374_);
v___x_1376_ = 0;
v___x_1377_ = lean_uint32_dec_eq(v___x_1375_, v___x_1376_);
if (v___x_1377_ == 0)
{
v___y_1358_ = v___x_1373_;
goto v___jp_1357_;
}
else
{
goto v___jp_1347_;
}
}
}
else
{
uint32_t v___x_1378_; 
v___x_1378_ = lean_float32_to_bits(v_result_1367_);
return v___x_1378_;
}
}
v___jp_1379_:
{
if (v___y_1381_ == 0)
{
float v___x_1382_; 
v___x_1382_ = lean_float32_of_bits(v___y_131_);
v___y_1365_ = v___y_1380_;
v___y_1366_ = v___x_1382_;
goto v___jp_1364_;
}
else
{
uint32_t v___x_1383_; uint32_t v___x_1384_; uint32_t v___x_1385_; uint32_t v___x_1386_; float v___x_1387_; lean_object* v___x_1388_; uint32_t v___x_1389_; uint32_t v___x_1390_; lean_object* v___x_1391_; lean_object* v___x_1392_; float v___x_1393_; float v___x_1394_; 
v___x_1383_ = 8388607;
v___x_1384_ = lean_uint32_land(v___y_131_, v___x_1383_);
v___x_1385_ = 8388608;
v___x_1386_ = lean_uint32_lor(v___x_1384_, v___x_1385_);
v___x_1387_ = lean_uint32_to_float32(v___x_1386_);
v___x_1388_ = lp_competition_R2W01b_scaleTable;
v___x_1389_ = 23;
v___x_1390_ = lean_uint32_shift_right(v___y_131_, v___x_1389_);
v___x_1391_ = lean_uint32_to_nat(v___x_1390_);
v___x_1392_ = lean_array_fget_borrowed(v___x_1388_, v___x_1391_);
lean_dec(v___x_1391_);
v___x_1393_ = lean_unbox_float32(v___x_1392_);
v___x_1394_ = lean_float32_mul(v___x_1387_, v___x_1393_);
v___y_1365_ = v___y_1380_;
v___y_1366_ = v___x_1394_;
goto v___jp_1364_;
}
}
v___jp_1395_:
{
uint32_t v___x_1397_; uint32_t v_a_1398_; uint32_t v___x_1399_; uint32_t v___x_1400_; uint32_t v___x_1401_; uint8_t v___x_1402_; 
v___x_1397_ = 2147483647;
v_a_1398_ = lean_uint32_land(v___y_131_, v___x_1397_);
v___x_1399_ = 201326591;
v___x_1400_ = 1;
v___x_1401_ = lean_uint32_sub(v_a_1398_, v___x_1400_);
v___x_1402_ = lean_uint32_dec_le(v___x_1399_, v___x_1401_);
if (v___x_1402_ == 0)
{
v___y_1380_ = v___y_1396_;
v___y_1381_ = v___x_1402_;
goto v___jp_1379_;
}
else
{
uint32_t v___x_1403_; uint8_t v___x_1404_; 
v___x_1403_ = 2139095040;
v___x_1404_ = lean_uint32_dec_lt(v_a_1398_, v___x_1403_);
v___y_1380_ = v___y_1396_;
v___y_1381_ = v___x_1404_;
goto v___jp_1379_;
}
}
v___jp_1405_:
{
if (v___y_1407_ == 0)
{
float v___x_1408_; 
v___x_1408_ = lean_float32_of_bits(v___y_130_);
v___y_1396_ = v___x_1408_;
goto v___jp_1395_;
}
else
{
uint32_t v___x_1409_; uint32_t v___x_1410_; uint32_t v___x_1411_; uint32_t v___x_1412_; float v___x_1413_; lean_object* v___x_1414_; lean_object* v___x_1415_; lean_object* v___x_1416_; float v___x_1417_; float v___x_1418_; 
v___x_1409_ = 8388607;
v___x_1410_ = lean_uint32_land(v___y_130_, v___x_1409_);
v___x_1411_ = 8388608;
v___x_1412_ = lean_uint32_lor(v___x_1410_, v___x_1411_);
v___x_1413_ = lean_uint32_to_float32(v___x_1412_);
v___x_1414_ = lp_competition_R2W01b_scaleTable;
v___x_1415_ = lean_uint32_to_nat(v___y_1406_);
v___x_1416_ = lean_array_fget_borrowed(v___x_1414_, v___x_1415_);
lean_dec(v___x_1415_);
v___x_1417_ = lean_unbox_float32(v___x_1416_);
v___x_1418_ = lean_float32_mul(v___x_1413_, v___x_1417_);
v___y_1396_ = v___x_1418_;
goto v___jp_1395_;
}
}
v___jp_1419_:
{
if (v___y_1420_ == 0)
{
uint32_t v___x_1421_; uint32_t v___x_1422_; uint32_t v___x_1423_; uint32_t v_ex_1424_; uint32_t v___x_1425_; uint32_t v_ey_1426_; uint32_t v___x_1427_; uint32_t v___x_1428_; uint8_t v___x_1429_; 
v___x_1421_ = 23;
v___x_1422_ = lean_uint32_shift_right(v___y_130_, v___x_1421_);
v___x_1423_ = 255;
v_ex_1424_ = lean_uint32_land(v___x_1422_, v___x_1423_);
v___x_1425_ = lean_uint32_shift_right(v___y_131_, v___x_1421_);
v_ey_1426_ = lean_uint32_land(v___x_1425_, v___x_1423_);
v___x_1427_ = lean_uint32_add(v_ex_1424_, v_ey_1426_);
v___x_1428_ = 128;
v___x_1429_ = lean_uint32_dec_lt(v___x_1427_, v___x_1428_);
if (v___x_1429_ == 0)
{
uint32_t v___x_1430_; uint32_t v_a_1431_; uint32_t v___x_1432_; uint32_t v___x_1433_; uint32_t v___x_1434_; uint8_t v___x_1435_; 
v___x_1430_ = 2147483647;
v_a_1431_ = lean_uint32_land(v___y_130_, v___x_1430_);
v___x_1432_ = 201326591;
v___x_1433_ = 1;
v___x_1434_ = lean_uint32_sub(v_a_1431_, v___x_1433_);
v___x_1435_ = lean_uint32_dec_le(v___x_1432_, v___x_1434_);
if (v___x_1435_ == 0)
{
v___y_1297_ = v___x_1422_;
v___y_1298_ = v___x_1435_;
goto v___jp_1296_;
}
else
{
uint32_t v___x_1436_; uint8_t v___x_1437_; 
v___x_1436_ = 2139095040;
v___x_1437_ = lean_uint32_dec_lt(v_a_1431_, v___x_1436_);
v___y_1297_ = v___x_1422_;
v___y_1298_ = v___x_1437_;
goto v___jp_1296_;
}
}
else
{
uint32_t v___x_1438_; uint32_t v___x_1439_; uint32_t v___x_1440_; uint8_t v___x_1441_; 
v___x_1438_ = 4278190080;
v___x_1439_ = 1;
v___x_1440_ = lean_uint32_shift_left(v___y_130_, v___x_1439_);
v___x_1441_ = lean_uint32_dec_le(v___x_1438_, v___x_1440_);
if (v___x_1441_ == 0)
{
uint32_t v___x_1442_; uint8_t v___x_1443_; 
v___x_1442_ = lean_uint32_shift_left(v___y_131_, v___x_1439_);
v___x_1443_ = lean_uint32_dec_le(v___x_1438_, v___x_1442_);
v___y_1187_ = v___x_1421_;
v___y_1188_ = v_ex_1424_;
v___y_1189_ = v___x_1423_;
v___y_1190_ = v_ey_1426_;
v___y_1191_ = v___x_1443_;
goto v___jp_1186_;
}
else
{
v___y_1187_ = v___x_1421_;
v___y_1188_ = v_ex_1424_;
v___y_1189_ = v___x_1423_;
v___y_1190_ = v_ey_1426_;
v___y_1191_ = v___x_1441_;
goto v___jp_1186_;
}
}
}
else
{
uint32_t v___x_1444_; uint32_t v___x_1445_; uint32_t v___x_1446_; uint32_t v___x_1447_; uint32_t v___x_1448_; uint32_t v___x_1449_; uint32_t v___x_1450_; uint32_t v___x_1451_; uint32_t v___x_1452_; uint32_t v___x_1453_; uint8_t v___x_1454_; 
v___x_1444_ = 23;
v___x_1445_ = lean_uint32_shift_right(v___y_130_, v___x_1444_);
v___x_1446_ = 255;
v___x_1447_ = lean_uint32_land(v___x_1445_, v___x_1446_);
v___x_1448_ = lean_uint32_shift_right(v___y_131_, v___x_1444_);
v___x_1449_ = lean_uint32_land(v___x_1448_, v___x_1446_);
v___x_1450_ = lean_uint32_add(v___x_1447_, v___x_1449_);
v___x_1451_ = 128;
v___x_1452_ = lean_uint32_sub(v___x_1450_, v___x_1451_);
v___x_1453_ = 252;
v___x_1454_ = lean_uint32_dec_le(v___x_1452_, v___x_1453_);
if (v___x_1454_ == 0)
{
uint8_t v___x_1455_; 
v___x_1455_ = lean_uint32_dec_lt(v___x_1450_, v___x_1451_);
if (v___x_1455_ == 0)
{
uint32_t v___x_1456_; uint32_t v_a_1457_; uint32_t v___x_1458_; uint32_t v___x_1459_; uint32_t v___x_1460_; uint8_t v___x_1461_; 
v___x_1456_ = 2147483647;
v_a_1457_ = lean_uint32_land(v___y_130_, v___x_1456_);
v___x_1458_ = 201326591;
v___x_1459_ = 1;
v___x_1460_ = lean_uint32_sub(v_a_1457_, v___x_1459_);
v___x_1461_ = lean_uint32_dec_le(v___x_1458_, v___x_1460_);
if (v___x_1461_ == 0)
{
v___y_1406_ = v___x_1445_;
v___y_1407_ = v___x_1461_;
goto v___jp_1405_;
}
else
{
uint32_t v___x_1462_; uint8_t v___x_1463_; 
v___x_1462_ = 2139095040;
v___x_1463_ = lean_uint32_dec_lt(v_a_1457_, v___x_1462_);
v___y_1406_ = v___x_1445_;
v___y_1407_ = v___x_1463_;
goto v___jp_1405_;
}
}
else
{
uint32_t v___x_1464_; uint32_t v___x_1465_; uint32_t v___x_1466_; uint8_t v___x_1467_; 
v___x_1464_ = 4278190080;
v___x_1465_ = 1;
v___x_1466_ = lean_uint32_shift_left(v___y_130_, v___x_1465_);
v___x_1467_ = lean_uint32_dec_le(v___x_1464_, v___x_1466_);
if (v___x_1467_ == 0)
{
uint32_t v___x_1468_; uint8_t v___x_1469_; 
v___x_1468_ = lean_uint32_shift_left(v___y_131_, v___x_1465_);
v___x_1469_ = lean_uint32_dec_le(v___x_1464_, v___x_1468_);
v___y_1041_ = v___y_1420_;
v___y_1042_ = v___x_1444_;
v___y_1043_ = v___x_1447_;
v___y_1044_ = v___x_1446_;
v___y_1045_ = v___x_1449_;
v___y_1046_ = v___x_1469_;
goto v___jp_1040_;
}
else
{
v___y_1041_ = v___y_1420_;
v___y_1042_ = v___x_1444_;
v___y_1043_ = v___x_1447_;
v___y_1044_ = v___x_1446_;
v___y_1045_ = v___x_1449_;
v___y_1046_ = v___x_1467_;
goto v___jp_1040_;
}
}
}
else
{
uint32_t v___x_1470_; uint32_t v___x_1471_; uint32_t v___x_1472_; uint32_t v___x_1473_; uint64_t v___x_1474_; uint32_t v___x_1475_; uint32_t v___x_1476_; uint64_t v___x_1477_; uint64_t v_product_1478_; uint64_t v___x_1479_; uint64_t v___x_1480_; uint64_t v___x_1481_; uint64_t v___x_1482_; uint8_t v___x_1483_; 
v___x_1470_ = 8388607;
v___x_1471_ = lean_uint32_land(v___y_130_, v___x_1470_);
v___x_1472_ = 8388608;
v___x_1473_ = lean_uint32_lor(v___x_1471_, v___x_1472_);
v___x_1474_ = lean_uint32_to_uint64(v___x_1473_);
v___x_1475_ = lean_uint32_land(v___y_131_, v___x_1470_);
v___x_1476_ = lean_uint32_lor(v___x_1475_, v___x_1472_);
v___x_1477_ = lean_uint32_to_uint64(v___x_1476_);
v_product_1478_ = lean_uint64_mul(v___x_1474_, v___x_1477_);
v___x_1479_ = 23ULL;
v___x_1480_ = 47ULL;
v___x_1481_ = lean_uint64_shift_right(v_product_1478_, v___x_1480_);
v___x_1482_ = lean_uint64_add(v___x_1479_, v___x_1481_);
v___x_1483_ = lean_uint64_dec_eq(v___x_1482_, v___x_1479_);
if (v___x_1483_ == 0)
{
uint64_t v___x_1484_; uint64_t v_q_1485_; uint64_t v___x_1486_; uint64_t v___x_1487_; uint64_t v_r_1488_; uint64_t v_half_1489_; uint8_t v___x_1490_; uint8_t v___x_1491_; 
v___x_1484_ = 24ULL;
v_q_1485_ = lean_uint64_shift_right(v_product_1478_, v___x_1484_);
v___x_1486_ = 1ULL;
v___x_1487_ = 16777215ULL;
v_r_1488_ = lean_uint64_land(v_product_1478_, v___x_1487_);
v_half_1489_ = 8388608ULL;
v___x_1490_ = lean_uint64_dec_lt(v_r_1488_, v_half_1489_);
v___x_1491_ = lean_uint64_dec_lt(v_half_1489_, v_r_1488_);
if (v___x_1490_ == 0)
{
v___y_1102_ = v___x_1491_;
v___y_1103_ = v___x_1444_;
v___y_1104_ = v_q_1485_;
v___y_1105_ = v___x_1446_;
v___y_1106_ = v___x_1454_;
v___y_1107_ = v___x_1486_;
v___y_1108_ = v___x_1450_;
v___y_1109_ = v___x_1486_;
goto v___jp_1101_;
}
else
{
uint64_t v___x_1492_; 
v___x_1492_ = 0ULL;
v___y_1102_ = v___x_1491_;
v___y_1103_ = v___x_1444_;
v___y_1104_ = v_q_1485_;
v___y_1105_ = v___x_1446_;
v___y_1106_ = v___x_1454_;
v___y_1107_ = v___x_1486_;
v___y_1108_ = v___x_1450_;
v___y_1109_ = v___x_1492_;
goto v___jp_1101_;
}
}
else
{
uint64_t v_q_1493_; uint64_t v___x_1494_; uint64_t v___x_1495_; uint64_t v_r_1496_; uint64_t v_half_1497_; uint8_t v___x_1498_; uint8_t v___x_1499_; 
v_q_1493_ = lean_uint64_shift_right(v_product_1478_, v___x_1479_);
v___x_1494_ = 1ULL;
v___x_1495_ = 8388607ULL;
v_r_1496_ = lean_uint64_land(v_product_1478_, v___x_1495_);
v_half_1497_ = 4194304ULL;
v___x_1498_ = lean_uint64_dec_lt(v_r_1496_, v_half_1497_);
v___x_1499_ = lean_uint64_dec_lt(v_half_1497_, v_r_1496_);
if (v___x_1498_ == 0)
{
v___y_1136_ = v___x_1499_;
v___y_1137_ = v_q_1493_;
v___y_1138_ = v___x_1444_;
v___y_1139_ = v___x_1446_;
v___y_1140_ = v___x_1454_;
v___y_1141_ = v___x_1494_;
v___y_1142_ = v___x_1450_;
v___y_1143_ = v___x_1494_;
goto v___jp_1135_;
}
else
{
uint64_t v___x_1500_; 
v___x_1500_ = 0ULL;
v___y_1136_ = v___x_1499_;
v___y_1137_ = v_q_1493_;
v___y_1138_ = v___x_1444_;
v___y_1139_ = v___x_1446_;
v___y_1140_ = v___x_1454_;
v___y_1141_ = v___x_1494_;
v___y_1142_ = v___x_1450_;
v___y_1143_ = v___x_1500_;
goto v___jp_1135_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_1513_, lean_object* v___y_1514_){
_start:
{
uint32_t v___y_9195__boxed_1515_; uint32_t v___y_9196__boxed_1516_; uint32_t v_res_1517_; lean_object* v_r_1518_; 
v___y_9195__boxed_1515_ = lean_unbox_uint32(v___y_1513_);
lean_dec(v___y_1513_);
v___y_9196__boxed_1516_ = lean_unbox_uint32(v___y_1514_);
lean_dec(v___y_1514_);
v_res_1517_ = lp_competition_main___lam__1(v___y_9195__boxed_1515_, v___y_9196__boxed_1516_);
v_r_1518_ = lean_box_uint32(v_res_1517_);
return v_r_1518_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_1519_, uint32_t v___y_1520_){
_start:
{
uint32_t v___y_1522_; uint32_t v___y_1526_; uint32_t v___y_1530_; uint32_t v___y_1534_; uint32_t v___y_1538_; uint32_t v___y_1539_; uint32_t v___y_1540_; uint64_t v___y_1544_; uint32_t v___y_1545_; uint8_t v___y_1546_; uint64_t v___y_1547_; uint32_t v___y_1559_; uint32_t v___y_1560_; uint32_t v___y_1561_; uint32_t v___y_1562_; uint32_t v___y_1563_; uint32_t v___y_1564_; uint32_t v___y_1571_; uint32_t v___y_1572_; uint32_t v___y_1573_; uint32_t v___y_1574_; uint8_t v___y_1575_; uint32_t v___y_1576_; uint32_t v___y_1580_; uint32_t v___y_1581_; uint64_t v___y_1582_; uint32_t v___y_1583_; uint64_t v___y_1584_; uint8_t v___y_1585_; uint64_t v___y_1586_; uint32_t v___y_1596_; uint32_t v___y_1597_; uint64_t v___y_1598_; uint32_t v___y_1599_; uint8_t v___y_1600_; uint8_t v___y_1601_; uint64_t v___y_1602_; uint64_t v___y_1603_; uint32_t v___y_1610_; uint32_t v___y_1611_; uint64_t v___y_1612_; uint32_t v___y_1613_; uint8_t v___y_1614_; uint64_t v___y_1615_; uint64_t v___y_1616_; uint32_t v___y_1622_; uint64_t v___y_1623_; uint32_t v___y_1624_; uint64_t v___y_1625_; uint32_t v___y_1626_; uint8_t v___y_1627_; uint64_t v___y_1628_; uint64_t v___y_1629_; uint64_t v___y_1684_; uint32_t v___y_1685_; uint32_t v___y_1686_; uint64_t v___y_1687_; uint32_t v___y_1688_; uint8_t v___y_1689_; uint64_t v___y_1690_; uint64_t v___y_1691_; uint64_t v___y_1692_; uint32_t v___y_1698_; uint64_t v___y_1699_; uint64_t v___y_1700_; uint32_t v___y_1701_; uint64_t v___y_1702_; uint64_t v___y_1703_; uint64_t v___y_1704_; uint32_t v___y_1705_; uint8_t v___y_1706_; uint64_t v___y_1707_; uint64_t v___y_1708_; uint64_t v___y_1713_; uint32_t v___y_1714_; uint32_t v___y_1715_; uint64_t v___y_1716_; uint64_t v___y_1717_; uint32_t v___y_1718_; uint8_t v___y_1719_; uint64_t v___y_1720_; uint64_t v___y_1721_; uint32_t v___y_1726_; uint64_t v___y_1727_; uint64_t v___y_1728_; uint32_t v___y_1729_; uint64_t v___y_1730_; uint32_t v___y_1731_; uint64_t v___y_1732_; uint8_t v___y_1733_; uint64_t v___y_1734_; uint64_t v___y_1735_; uint64_t v___y_1736_; uint64_t v___y_1741_; uint32_t v___y_1742_; uint64_t v___y_1743_; uint32_t v___y_1744_; uint64_t v___y_1745_; uint32_t v___y_1746_; uint8_t v___y_1747_; uint64_t v___y_1748_; uint64_t v___y_1749_; uint64_t v___y_1754_; uint32_t v___y_1755_; uint64_t v___y_1756_; uint32_t v___y_1757_; uint64_t v___y_1758_; uint64_t v___y_1759_; uint32_t v___y_1760_; uint8_t v___y_1761_; uint64_t v___y_1762_; uint64_t v___y_1763_; uint64_t v___y_1764_; uint64_t v___y_1769_; uint32_t v___y_1770_; uint64_t v___y_1771_; uint32_t v___y_1772_; uint64_t v___y_1773_; uint32_t v___y_1774_; uint8_t v___y_1775_; uint64_t v___y_1776_; uint64_t v___y_1777_; uint32_t v___y_1782_; uint64_t v___y_1783_; uint32_t v___y_1784_; uint64_t v___y_1785_; uint64_t v___y_1786_; uint64_t v___y_1787_; uint32_t v___y_1788_; uint8_t v___y_1789_; uint64_t v___y_1790_; uint64_t v___y_1791_; uint64_t v___y_1792_; uint64_t v___y_1797_; uint32_t v___y_1798_; uint32_t v___y_1799_; uint64_t v___y_1800_; uint64_t v___y_1801_; uint32_t v___y_1802_; uint8_t v___y_1803_; uint64_t v___y_1804_; uint64_t v___y_1805_; uint32_t v___y_1810_; uint64_t v___y_1811_; uint32_t v___y_1812_; uint64_t v___y_1813_; uint64_t v___y_1814_; uint32_t v___y_1815_; uint8_t v___y_1816_; uint64_t v___y_1817_; uint64_t v___y_1818_; uint64_t v___y_1822_; uint32_t v___y_1823_; uint32_t v___y_1824_; uint32_t v___y_1825_; uint8_t v___y_1826_; uint64_t v___y_1827_; uint32_t v___y_1836_; uint32_t v___y_1837_; uint32_t v___y_1838_; uint32_t v___y_1842_; uint64_t v___y_1843_; uint8_t v___y_1844_; uint64_t v___y_1845_; uint32_t v___y_1857_; uint64_t v___y_1858_; uint32_t v___y_1859_; uint32_t v___y_1860_; uint64_t v___y_1861_; uint8_t v___y_1862_; uint64_t v___y_1863_; uint64_t v___y_1864_; uint32_t v___y_1898_; uint64_t v___y_1899_; uint32_t v___y_1900_; uint32_t v___y_1901_; uint64_t v___y_1902_; uint8_t v___y_1903_; uint32_t v___y_1904_; uint64_t v___y_1905_; uint32_t v___y_1912_; uint32_t v___y_1913_; uint32_t v___y_1914_; uint32_t v___y_1915_; uint64_t v___y_1916_; uint8_t v___y_1917_; uint32_t v___y_1918_; uint64_t v___y_1919_; uint32_t v___y_1926_; uint32_t v___y_1927_; uint32_t v___y_1928_; uint32_t v___y_1929_; uint32_t v___y_1930_; uint8_t v___y_1931_; uint32_t v___y_1932_; uint64_t v___y_1933_; uint32_t v___y_1941_; uint32_t v___y_1942_; uint32_t v___y_1943_; uint32_t v___y_1944_; uint32_t v___y_1945_; uint32_t v___y_1946_; uint32_t v___y_1953_; uint32_t v___y_1954_; uint64_t v___y_1955_; uint64_t v___y_1956_; uint64_t v___y_1957_; uint32_t v___y_1958_; uint32_t v___y_1959_; uint8_t v___y_1960_; uint32_t v___y_1972_; uint32_t v___y_1973_; uint64_t v___y_1974_; uint64_t v___y_1975_; uint64_t v___y_1976_; uint32_t v___y_1977_; uint32_t v___y_1978_; uint32_t v___y_1981_; uint32_t v___y_1982_; uint64_t v___y_1983_; uint64_t v___y_1984_; uint64_t v___y_1985_; uint32_t v___y_1986_; uint32_t v___y_1987_; uint8_t v___y_1988_; uint8_t v___y_1989_; uint32_t v___y_1991_; uint32_t v___y_1992_; uint32_t v___y_1993_; uint32_t v___y_1997_; uint8_t v___y_1998_; uint64_t v___y_1999_; uint64_t v___y_2000_; uint32_t v___y_2012_; uint32_t v___y_2013_; uint32_t v___y_2014_; uint32_t v___y_2015_; uint32_t v___y_2016_; uint32_t v___y_2017_; uint32_t v___y_2024_; uint32_t v___y_2025_; uint8_t v___y_2026_; uint32_t v___y_2027_; uint32_t v___y_2028_; uint32_t v___y_2029_; uint32_t v___y_2033_; uint32_t v___y_2034_; uint8_t v___y_2035_; uint64_t v___y_2036_; uint64_t v___y_2037_; uint32_t v___y_2038_; uint64_t v___y_2039_; uint8_t v___y_2049_; uint32_t v___y_2050_; uint32_t v___y_2051_; uint8_t v___y_2052_; uint64_t v___y_2053_; uint64_t v___y_2054_; uint32_t v___y_2055_; uint64_t v___y_2056_; uint64_t v___y_2063_; uint32_t v___y_2064_; uint32_t v___y_2065_; uint8_t v___y_2066_; uint64_t v___y_2067_; uint32_t v___y_2068_; uint64_t v___y_2069_; uint32_t v___y_2075_; uint64_t v___y_2076_; uint32_t v___y_2077_; uint8_t v___y_2078_; uint64_t v___y_2079_; uint64_t v___y_2080_; uint32_t v___y_2081_; uint64_t v___y_2082_; uint32_t v___y_2137_; uint32_t v___y_2138_; uint64_t v___y_2139_; uint8_t v___y_2140_; uint64_t v___y_2141_; uint64_t v___y_2142_; uint64_t v___y_2143_; uint32_t v___y_2144_; uint64_t v___y_2145_; uint64_t v___y_2151_; uint64_t v___y_2152_; uint32_t v___y_2153_; uint64_t v___y_2154_; uint32_t v___y_2155_; uint64_t v___y_2156_; uint8_t v___y_2157_; uint64_t v___y_2158_; uint64_t v___y_2159_; uint32_t v___y_2160_; uint64_t v___y_2161_; uint32_t v___y_2166_; uint64_t v___y_2167_; uint32_t v___y_2168_; uint64_t v___y_2169_; uint8_t v___y_2170_; uint64_t v___y_2171_; uint64_t v___y_2172_; uint32_t v___y_2173_; uint64_t v___y_2174_; uint64_t v___y_2179_; uint32_t v___y_2180_; uint64_t v___y_2181_; uint32_t v___y_2182_; uint8_t v___y_2183_; uint64_t v___y_2184_; uint64_t v___y_2185_; uint64_t v___y_2186_; uint64_t v___y_2187_; uint32_t v___y_2188_; uint64_t v___y_2189_; uint32_t v___y_2194_; uint32_t v___y_2195_; uint64_t v___y_2196_; uint8_t v___y_2197_; uint64_t v___y_2198_; uint64_t v___y_2199_; uint64_t v___y_2200_; uint32_t v___y_2201_; uint64_t v___y_2202_; uint64_t v___y_2207_; uint64_t v___y_2208_; uint32_t v___y_2209_; uint64_t v___y_2210_; uint32_t v___y_2211_; uint8_t v___y_2212_; uint64_t v___y_2213_; uint64_t v___y_2214_; uint32_t v___y_2215_; uint64_t v___y_2216_; uint64_t v___y_2217_; uint32_t v___y_2222_; uint64_t v___y_2223_; uint32_t v___y_2224_; uint64_t v___y_2225_; uint8_t v___y_2226_; uint64_t v___y_2227_; uint64_t v___y_2228_; uint32_t v___y_2229_; uint64_t v___y_2230_; uint64_t v___y_2235_; uint64_t v___y_2236_; uint64_t v___y_2237_; uint32_t v___y_2238_; uint64_t v___y_2239_; uint32_t v___y_2240_; uint8_t v___y_2241_; uint64_t v___y_2242_; uint64_t v___y_2243_; uint32_t v___y_2244_; uint64_t v___y_2245_; uint32_t v___y_2250_; uint64_t v___y_2251_; uint32_t v___y_2252_; uint64_t v___y_2253_; uint8_t v___y_2254_; uint64_t v___y_2255_; uint64_t v___y_2256_; uint32_t v___y_2257_; uint64_t v___y_2258_; uint32_t v___y_2263_; uint64_t v___y_2264_; uint32_t v___y_2265_; uint8_t v___y_2266_; uint64_t v___y_2267_; uint64_t v___y_2268_; uint64_t v___y_2269_; uint32_t v___y_2270_; uint64_t v___y_2271_; uint32_t v___y_2275_; uint64_t v___y_2276_; uint32_t v___y_2277_; uint8_t v___y_2278_; uint64_t v___y_2279_; uint32_t v___y_2280_; uint32_t v___y_2289_; uint32_t v___y_2290_; uint32_t v___y_2291_; uint32_t v___y_2295_; uint8_t v___y_2296_; uint64_t v___y_2297_; uint64_t v___y_2298_; uint64_t v___y_2310_; uint32_t v___y_2311_; uint32_t v___y_2312_; uint8_t v___y_2313_; uint64_t v___y_2314_; uint32_t v___y_2315_; uint64_t v___y_2316_; uint64_t v___y_2317_; uint64_t v___y_2351_; uint32_t v___y_2352_; uint32_t v___y_2353_; uint8_t v___y_2354_; uint64_t v___y_2355_; uint32_t v___y_2356_; uint32_t v___y_2357_; uint64_t v___y_2358_; uint64_t v___y_2365_; uint32_t v___y_2366_; uint32_t v___y_2367_; uint8_t v___y_2368_; uint32_t v___y_2369_; uint32_t v___y_2370_; uint32_t v___y_2371_; uint64_t v___y_2372_; uint32_t v___y_2379_; uint32_t v___y_2380_; uint32_t v___y_2381_; uint8_t v___y_2382_; uint32_t v___y_2383_; uint32_t v___y_2384_; uint32_t v___y_2385_; uint64_t v___y_2386_; uint32_t v___y_2394_; uint32_t v___y_2395_; uint32_t v___y_2396_; uint32_t v___y_2397_; uint8_t v___y_2398_; uint8_t v___y_2409_; uint32_t v___y_2410_; uint8_t v___y_2411_; uint32_t v___y_2412_; uint8_t v___y_2413_; uint32_t v___y_2414_; uint32_t v___y_2415_; uint8_t v___y_2416_; uint8_t v___y_2418_; uint32_t v___y_2419_; uint8_t v___y_2420_; uint32_t v___y_2421_; uint32_t v___y_2422_; uint32_t v___y_2423_; uint8_t v___y_2424_; uint8_t v___y_2430_; uint32_t v___y_2431_; uint32_t v___y_2432_; uint32_t v___y_2433_; uint32_t v___y_2434_; uint8_t v___y_2435_; uint32_t v___y_2445_; uint32_t v___y_2446_; uint32_t v___y_2447_; uint8_t v___y_2448_; uint64_t v___y_2449_; uint32_t v___y_2467_; uint32_t v___y_2468_; uint64_t v___y_2469_; uint64_t v___y_2470_; uint32_t v___y_2471_; uint64_t v___y_2472_; uint8_t v___y_2473_; uint64_t v___y_2474_; uint32_t v___y_2479_; uint32_t v___y_2480_; uint64_t v___y_2481_; uint64_t v___y_2482_; uint64_t v___y_2483_; uint32_t v___y_2484_; uint8_t v___y_2485_; uint64_t v___y_2486_; uint8_t v___y_2491_; uint32_t v___y_2492_; uint32_t v___y_2493_; uint64_t v___y_2494_; uint32_t v___y_2495_; uint64_t v___y_2496_; uint8_t v___y_2497_; uint64_t v___y_2498_; uint64_t v___y_2501_; uint64_t v___y_2502_; uint32_t v___y_2503_; uint32_t v___y_2504_; uint64_t v___y_2505_; uint32_t v___y_2506_; uint8_t v___y_2507_; uint64_t v___y_2508_; uint64_t v___y_2513_; uint64_t v___y_2514_; uint32_t v___y_2515_; uint32_t v___y_2516_; uint64_t v___y_2517_; uint32_t v___y_2518_; uint8_t v___y_2519_; uint64_t v___y_2520_; uint64_t v___y_2525_; uint8_t v___y_2526_; uint32_t v___y_2527_; uint32_t v___y_2528_; uint64_t v___y_2529_; uint32_t v___y_2530_; uint8_t v___y_2531_; uint64_t v___y_2532_; uint32_t v___y_2535_; uint32_t v___y_2536_; uint32_t v___y_2537_; uint32_t v___y_2538_; uint8_t v___y_2539_; uint32_t v___y_2550_; uint32_t v___y_2551_; uint32_t v___y_2552_; uint32_t v___y_2553_; uint32_t v___y_2556_; uint32_t v___y_2557_; uint8_t v___y_2558_; uint32_t v___y_2559_; uint8_t v___y_2560_; uint32_t v___y_2561_; uint8_t v___y_2562_; uint32_t v___y_2564_; uint8_t v___y_2565_; uint32_t v___y_2566_; uint32_t v___y_2567_; uint32_t v___y_2568_; uint8_t v___y_2569_; uint32_t v___y_2576_; uint32_t v___y_2577_; uint32_t v___y_2578_; uint32_t v___y_2579_; uint8_t v___y_2580_; uint8_t v___y_2591_; uint8_t v___y_2607_; uint8_t v___y_2621_; uint8_t v___y_2638_; float v___y_2645_; float v___y_2646_; float v___y_2660_; uint8_t v___y_2661_; float v___y_2676_; uint32_t v___y_2686_; uint8_t v___y_2687_; uint8_t v___y_2700_; uint8_t v___y_2716_; uint8_t v___y_2730_; uint8_t v___y_2747_; float v___y_2754_; float v___y_2755_; float v___y_2769_; uint8_t v___y_2770_; float v___y_2785_; uint32_t v___y_2795_; uint8_t v___y_2796_; uint8_t v___y_2809_; uint32_t v___x_2890_; uint32_t v___x_2891_; uint32_t v___x_2892_; uint32_t v___x_2893_; uint32_t v___x_2894_; uint32_t v___x_2895_; uint32_t v___x_2896_; uint8_t v___x_2897_; 
v___x_2890_ = 23;
v___x_2891_ = lean_uint32_shift_right(v___y_1519_, v___x_2890_);
v___x_2892_ = 255;
v___x_2893_ = lean_uint32_land(v___x_2891_, v___x_2892_);
v___x_2894_ = 1;
v___x_2895_ = lean_uint32_sub(v___x_2893_, v___x_2894_);
v___x_2896_ = 253;
v___x_2897_ = lean_uint32_dec_le(v___x_2895_, v___x_2896_);
if (v___x_2897_ == 0)
{
v___y_2809_ = v___x_2897_;
goto v___jp_2808_;
}
else
{
uint32_t v___x_2898_; uint32_t v___x_2899_; uint32_t v___x_2900_; uint8_t v___x_2901_; 
v___x_2898_ = lean_uint32_shift_right(v___y_1520_, v___x_2890_);
v___x_2899_ = lean_uint32_land(v___x_2898_, v___x_2892_);
v___x_2900_ = lean_uint32_sub(v___x_2899_, v___x_2894_);
v___x_2901_ = lean_uint32_dec_le(v___x_2900_, v___x_2896_);
v___y_2809_ = v___x_2901_;
goto v___jp_2808_;
}
v___jp_1521_:
{
uint32_t v___x_1523_; uint32_t v___x_1524_; 
v___x_1523_ = 8388608;
v___x_1524_ = lean_uint32_lor(v___y_1522_, v___x_1523_);
return v___x_1524_;
}
v___jp_1525_:
{
uint32_t v___x_1527_; uint32_t v___x_1528_; 
v___x_1527_ = 8388608;
v___x_1528_ = lean_uint32_lor(v___y_1526_, v___x_1527_);
return v___x_1528_;
}
v___jp_1529_:
{
uint32_t v___x_1531_; uint32_t v___x_1532_; 
v___x_1531_ = 8388608;
v___x_1532_ = lean_uint32_lor(v___y_1530_, v___x_1531_);
return v___x_1532_;
}
v___jp_1533_:
{
uint32_t v___x_1535_; uint32_t v___x_1536_; 
v___x_1535_ = 8388608;
v___x_1536_ = lean_uint32_lor(v___y_1534_, v___x_1535_);
return v___x_1536_;
}
v___jp_1537_:
{
uint32_t v___x_1541_; uint32_t v___x_1542_; 
v___x_1541_ = lean_uint32_land(v___y_1539_, v___y_1538_);
v___x_1542_ = lean_uint32_lor(v___y_1540_, v___x_1541_);
return v___x_1542_;
}
v___jp_1543_:
{
uint8_t v___x_1548_; 
v___x_1548_ = lean_uint64_dec_eq(v___y_1547_, v___y_1544_);
if (v___x_1548_ == 0)
{
uint64_t v___x_1549_; uint8_t v___x_1550_; 
v___x_1549_ = 8388608ULL;
v___x_1550_ = lean_uint64_dec_eq(v___y_1547_, v___x_1549_);
if (v___x_1550_ == 0)
{
uint32_t v___x_1551_; 
v___x_1551_ = lean_uint64_to_uint32(v___y_1547_);
if (v___y_1546_ == 0)
{
uint32_t v___x_1552_; 
v___x_1552_ = 0;
v___y_1538_ = v___y_1545_;
v___y_1539_ = v___x_1551_;
v___y_1540_ = v___x_1552_;
goto v___jp_1537_;
}
else
{
uint32_t v___x_1553_; 
v___x_1553_ = 2147483648;
v___y_1538_ = v___y_1545_;
v___y_1539_ = v___x_1551_;
v___y_1540_ = v___x_1553_;
goto v___jp_1537_;
}
}
else
{
if (v___y_1546_ == 0)
{
uint32_t v___x_1554_; 
v___x_1554_ = 0;
v___y_1534_ = v___x_1554_;
goto v___jp_1533_;
}
else
{
uint32_t v___x_1555_; 
v___x_1555_ = 2147483648;
v___y_1534_ = v___x_1555_;
goto v___jp_1533_;
}
}
}
else
{
if (v___y_1546_ == 0)
{
uint32_t v___x_1556_; 
v___x_1556_ = 0;
return v___x_1556_;
}
else
{
uint32_t v___x_1557_; 
v___x_1557_ = 2147483648;
return v___x_1557_;
}
}
}
v___jp_1558_:
{
uint32_t v___x_1565_; uint32_t v___x_1566_; uint32_t v___x_1567_; uint32_t v___x_1568_; uint32_t v___x_1569_; 
v___x_1565_ = lean_uint32_land(v___y_1561_, v___y_1560_);
v___x_1566_ = lean_uint32_shift_left(v___x_1565_, v___y_1559_);
v___x_1567_ = lean_uint32_lor(v___y_1564_, v___x_1566_);
v___x_1568_ = lean_uint32_land(v___y_1563_, v___y_1562_);
v___x_1569_ = lean_uint32_lor(v___x_1567_, v___x_1568_);
return v___x_1569_;
}
v___jp_1570_:
{
if (v___y_1575_ == 0)
{
uint32_t v___x_1577_; 
v___x_1577_ = 0;
v___y_1559_ = v___y_1571_;
v___y_1560_ = v___y_1572_;
v___y_1561_ = v___y_1573_;
v___y_1562_ = v___y_1574_;
v___y_1563_ = v___y_1576_;
v___y_1564_ = v___x_1577_;
goto v___jp_1558_;
}
else
{
uint32_t v___x_1578_; 
v___x_1578_ = 2147483648;
v___y_1559_ = v___y_1571_;
v___y_1560_ = v___y_1572_;
v___y_1561_ = v___y_1573_;
v___y_1562_ = v___y_1574_;
v___y_1563_ = v___y_1576_;
v___y_1564_ = v___x_1578_;
goto v___jp_1558_;
}
}
v___jp_1579_:
{
uint64_t v___x_1587_; uint64_t v_encodedExponent_1588_; uint32_t v___x_1589_; uint64_t v___x_1590_; uint8_t v___x_1591_; 
v___x_1587_ = 171ULL;
v_encodedExponent_1588_ = lean_uint64_sub(v___y_1584_, v___x_1587_);
v___x_1589_ = lean_uint64_to_uint32(v_encodedExponent_1588_);
v___x_1590_ = 8388608ULL;
v___x_1591_ = lean_uint64_dec_lt(v___y_1586_, v___x_1590_);
if (v___x_1591_ == 0)
{
uint64_t v___x_1592_; uint32_t v___x_1593_; 
v___x_1592_ = lean_uint64_sub(v___y_1586_, v___x_1590_);
v___x_1593_ = lean_uint64_to_uint32(v___x_1592_);
v___y_1571_ = v___y_1580_;
v___y_1572_ = v___y_1581_;
v___y_1573_ = v___x_1589_;
v___y_1574_ = v___y_1583_;
v___y_1575_ = v___y_1585_;
v___y_1576_ = v___x_1593_;
goto v___jp_1570_;
}
else
{
uint32_t v___x_1594_; 
v___x_1594_ = lean_uint64_to_uint32(v___y_1582_);
v___y_1571_ = v___y_1580_;
v___y_1572_ = v___y_1581_;
v___y_1573_ = v___x_1589_;
v___y_1574_ = v___y_1583_;
v___y_1575_ = v___y_1585_;
v___y_1576_ = v___x_1594_;
goto v___jp_1570_;
}
}
v___jp_1595_:
{
uint64_t v___x_1604_; uint8_t v___x_1605_; 
v___x_1604_ = 425ULL;
v___x_1605_ = lean_uint64_dec_lt(v___x_1604_, v___y_1603_);
if (v___x_1605_ == 0)
{
if (v___y_1601_ == 0)
{
v___y_1580_ = v___y_1596_;
v___y_1581_ = v___y_1597_;
v___y_1582_ = v___y_1598_;
v___y_1583_ = v___y_1599_;
v___y_1584_ = v___y_1603_;
v___y_1585_ = v___y_1600_;
v___y_1586_ = v___y_1602_;
goto v___jp_1579_;
}
else
{
uint64_t v___x_1606_; 
v___x_1606_ = 8388608ULL;
v___y_1580_ = v___y_1596_;
v___y_1581_ = v___y_1597_;
v___y_1582_ = v___y_1598_;
v___y_1583_ = v___y_1599_;
v___y_1584_ = v___y_1603_;
v___y_1585_ = v___y_1600_;
v___y_1586_ = v___x_1606_;
goto v___jp_1579_;
}
}
else
{
if (v___y_1600_ == 0)
{
uint32_t v___x_1607_; 
v___x_1607_ = 2139095040;
return v___x_1607_;
}
else
{
uint32_t v___x_1608_; 
v___x_1608_ = 4286578688;
return v___x_1608_;
}
}
}
v___jp_1609_:
{
uint64_t v___x_1617_; uint8_t v_carry_1618_; 
v___x_1617_ = 16777216ULL;
v_carry_1618_ = lean_uint64_dec_eq(v___y_1616_, v___x_1617_);
if (v_carry_1618_ == 0)
{
v___y_1596_ = v___y_1610_;
v___y_1597_ = v___y_1611_;
v___y_1598_ = v___y_1612_;
v___y_1599_ = v___y_1613_;
v___y_1600_ = v___y_1614_;
v___y_1601_ = v_carry_1618_;
v___y_1602_ = v___y_1616_;
v___y_1603_ = v___y_1615_;
goto v___jp_1595_;
}
else
{
uint64_t v___x_1619_; uint64_t v___x_1620_; 
v___x_1619_ = 1ULL;
v___x_1620_ = lean_uint64_add(v___y_1615_, v___x_1619_);
v___y_1596_ = v___y_1610_;
v___y_1597_ = v___y_1611_;
v___y_1598_ = v___y_1612_;
v___y_1599_ = v___y_1613_;
v___y_1600_ = v___y_1614_;
v___y_1601_ = v_carry_1618_;
v___y_1602_ = v___y_1616_;
v___y_1603_ = v___x_1620_;
goto v___jp_1595_;
}
}
v___jp_1621_:
{
uint64_t v_position_1630_; uint64_t v___x_1631_; uint8_t v___x_1632_; 
v_position_1630_ = lean_uint64_add(v___y_1629_, v___y_1623_);
v___x_1631_ = 172ULL;
v___x_1632_ = lean_uint64_dec_lt(v_position_1630_, v___x_1631_);
if (v___x_1632_ == 0)
{
uint64_t v___x_1633_; uint8_t v___x_1634_; 
v___x_1633_ = 23ULL;
v___x_1634_ = lean_uint64_dec_lt(v___y_1629_, v___x_1633_);
if (v___x_1634_ == 0)
{
uint64_t v___x_1635_; uint8_t v___x_1636_; 
v___x_1635_ = lean_uint64_sub(v___y_1629_, v___x_1633_);
v___x_1636_ = lean_uint64_dec_eq(v___x_1635_, v___y_1625_);
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
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v___y_1625_;
goto v___jp_1609_;
}
else
{
uint64_t v___x_1640_; uint8_t v___x_1641_; 
v___x_1640_ = 9223372036854775808ULL;
v___x_1641_ = lean_uint64_dec_lt(v___x_1640_, v___y_1628_);
if (v___x_1641_ == 0)
{
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v___y_1625_;
goto v___jp_1609_;
}
else
{
uint64_t v___x_1642_; 
v___x_1642_ = 1ULL;
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v___x_1642_;
goto v___jp_1609_;
}
}
}
else
{
uint64_t v_quotient_1643_; uint64_t v___x_1644_; uint64_t v___x_1645_; uint64_t v___x_1646_; uint64_t v_remainder_1647_; uint64_t v___x_1648_; uint64_t v_half_1649_; uint8_t v___x_1650_; 
v_quotient_1643_ = lean_uint64_shift_right(v___y_1628_, v___x_1635_);
v___x_1644_ = 1ULL;
v___x_1645_ = lean_uint64_shift_left(v___x_1644_, v___x_1635_);
v___x_1646_ = lean_uint64_sub(v___x_1645_, v___x_1644_);
v_remainder_1647_ = lean_uint64_land(v___y_1628_, v___x_1646_);
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
v___x_1653_ = lean_uint64_dec_eq(v___x_1652_, v___y_1625_);
if (v___x_1653_ == 0)
{
uint64_t v___x_1654_; 
v___x_1654_ = lean_uint64_add(v_quotient_1643_, v___x_1644_);
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v___x_1654_;
goto v___jp_1609_;
}
else
{
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v_quotient_1643_;
goto v___jp_1609_;
}
}
else
{
uint64_t v___x_1655_; 
v___x_1655_ = lean_uint64_add(v_quotient_1643_, v___x_1644_);
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v___x_1655_;
goto v___jp_1609_;
}
}
else
{
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v_quotient_1643_;
goto v___jp_1609_;
}
}
}
else
{
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v___y_1628_;
goto v___jp_1609_;
}
}
else
{
uint64_t v___x_1656_; uint64_t v___x_1657_; 
v___x_1656_ = lean_uint64_sub(v___x_1633_, v___y_1629_);
v___x_1657_ = lean_uint64_shift_left(v___y_1628_, v___x_1656_);
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1626_;
v___y_1614_ = v___y_1627_;
v___y_1615_ = v_position_1630_;
v___y_1616_ = v___x_1657_;
goto v___jp_1609_;
}
}
else
{
uint64_t v___x_1658_; uint8_t v___x_1659_; 
v___x_1658_ = 149ULL;
v___x_1659_ = lean_uint64_dec_lt(v___y_1623_, v___x_1658_);
if (v___x_1659_ == 0)
{
uint64_t v___x_1660_; uint64_t v___x_1661_; 
v___x_1660_ = lean_uint64_sub(v___y_1623_, v___x_1658_);
v___x_1661_ = lean_uint64_shift_left(v___y_1628_, v___x_1660_);
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v___x_1661_;
goto v___jp_1543_;
}
else
{
uint64_t v___x_1662_; uint8_t v___x_1663_; 
v___x_1662_ = lean_uint64_sub(v___x_1658_, v___y_1623_);
v___x_1663_ = lean_uint64_dec_eq(v___x_1662_, v___y_1625_);
if (v___x_1663_ == 0)
{
uint64_t v___x_1664_; uint8_t v___x_1665_; 
v___x_1664_ = 64ULL;
v___x_1665_ = lean_uint64_dec_lt(v___x_1662_, v___x_1664_);
if (v___x_1665_ == 0)
{
uint8_t v___x_1666_; 
v___x_1666_ = lean_uint64_dec_eq(v___x_1662_, v___x_1664_);
if (v___x_1666_ == 0)
{
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v___y_1625_;
goto v___jp_1543_;
}
else
{
uint64_t v___x_1667_; uint8_t v___x_1668_; 
v___x_1667_ = 9223372036854775808ULL;
v___x_1668_ = lean_uint64_dec_lt(v___x_1667_, v___y_1628_);
if (v___x_1668_ == 0)
{
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v___y_1625_;
goto v___jp_1543_;
}
else
{
uint64_t v___x_1669_; 
v___x_1669_ = 1ULL;
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v___x_1669_;
goto v___jp_1543_;
}
}
}
else
{
uint64_t v_quotient_1670_; uint64_t v___x_1671_; uint64_t v___x_1672_; uint64_t v___x_1673_; uint64_t v_remainder_1674_; uint64_t v___x_1675_; uint64_t v_half_1676_; uint8_t v___x_1677_; 
v_quotient_1670_ = lean_uint64_shift_right(v___y_1628_, v___x_1662_);
v___x_1671_ = 1ULL;
v___x_1672_ = lean_uint64_shift_left(v___x_1671_, v___x_1662_);
v___x_1673_ = lean_uint64_sub(v___x_1672_, v___x_1671_);
v_remainder_1674_ = lean_uint64_land(v___y_1628_, v___x_1673_);
v___x_1675_ = lean_uint64_sub(v___x_1662_, v___x_1671_);
v_half_1676_ = lean_uint64_shift_left(v___x_1671_, v___x_1675_);
v___x_1677_ = lean_uint64_dec_lt(v_remainder_1674_, v_half_1676_);
if (v___x_1677_ == 0)
{
uint8_t v___x_1678_; 
v___x_1678_ = lean_uint64_dec_lt(v_half_1676_, v_remainder_1674_);
if (v___x_1678_ == 0)
{
uint64_t v___x_1679_; uint8_t v___x_1680_; 
v___x_1679_ = lean_uint64_land(v_quotient_1670_, v___x_1671_);
v___x_1680_ = lean_uint64_dec_eq(v___x_1679_, v___y_1625_);
if (v___x_1680_ == 0)
{
uint64_t v___x_1681_; 
v___x_1681_ = lean_uint64_add(v_quotient_1670_, v___x_1671_);
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v___x_1681_;
goto v___jp_1543_;
}
else
{
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v_quotient_1670_;
goto v___jp_1543_;
}
}
else
{
uint64_t v___x_1682_; 
v___x_1682_ = lean_uint64_add(v_quotient_1670_, v___x_1671_);
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v___x_1682_;
goto v___jp_1543_;
}
}
else
{
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v_quotient_1670_;
goto v___jp_1543_;
}
}
}
else
{
v___y_1544_ = v___y_1625_;
v___y_1545_ = v___y_1626_;
v___y_1546_ = v___y_1627_;
v___y_1547_ = v___y_1628_;
goto v___jp_1543_;
}
}
}
}
v___jp_1683_:
{
uint64_t v___x_1693_; uint64_t v___x_1694_; uint8_t v___x_1695_; 
v___x_1693_ = 1ULL;
v___x_1694_ = lean_uint64_shift_right(v___y_1690_, v___x_1693_);
v___x_1695_ = lean_uint64_dec_eq(v___x_1694_, v___y_1687_);
if (v___x_1695_ == 0)
{
uint64_t v___x_1696_; 
v___x_1696_ = lean_uint64_add(v___y_1692_, v___x_1693_);
v___y_1622_ = v___y_1685_;
v___y_1623_ = v___y_1684_;
v___y_1624_ = v___y_1686_;
v___y_1625_ = v___y_1687_;
v___y_1626_ = v___y_1688_;
v___y_1627_ = v___y_1689_;
v___y_1628_ = v___y_1691_;
v___y_1629_ = v___x_1696_;
goto v___jp_1621_;
}
else
{
v___y_1622_ = v___y_1685_;
v___y_1623_ = v___y_1684_;
v___y_1624_ = v___y_1686_;
v___y_1625_ = v___y_1687_;
v___y_1626_ = v___y_1688_;
v___y_1627_ = v___y_1689_;
v___y_1628_ = v___y_1691_;
v___y_1629_ = v___y_1692_;
goto v___jp_1621_;
}
}
v___jp_1697_:
{
uint64_t v___x_1709_; uint8_t v___x_1710_; 
v___x_1709_ = lean_uint64_shift_right(v___y_1703_, v___y_1702_);
v___x_1710_ = lean_uint64_dec_eq(v___x_1709_, v___y_1704_);
if (v___x_1710_ == 0)
{
uint64_t v___x_1711_; 
v___x_1711_ = lean_uint64_add(v___y_1700_, v___y_1702_);
v___y_1684_ = v___y_1699_;
v___y_1685_ = v___y_1698_;
v___y_1686_ = v___y_1701_;
v___y_1687_ = v___y_1704_;
v___y_1688_ = v___y_1705_;
v___y_1689_ = v___y_1706_;
v___y_1690_ = v___y_1708_;
v___y_1691_ = v___y_1707_;
v___y_1692_ = v___x_1711_;
goto v___jp_1683_;
}
else
{
v___y_1684_ = v___y_1699_;
v___y_1685_ = v___y_1698_;
v___y_1686_ = v___y_1701_;
v___y_1687_ = v___y_1704_;
v___y_1688_ = v___y_1705_;
v___y_1689_ = v___y_1706_;
v___y_1690_ = v___y_1708_;
v___y_1691_ = v___y_1707_;
v___y_1692_ = v___y_1700_;
goto v___jp_1683_;
}
}
v___jp_1712_:
{
uint64_t v___x_1722_; uint64_t v___x_1723_; uint8_t v___x_1724_; 
v___x_1722_ = 2ULL;
v___x_1723_ = lean_uint64_shift_right(v___y_1716_, v___x_1722_);
v___x_1724_ = lean_uint64_dec_eq(v___x_1723_, v___y_1717_);
if (v___x_1724_ == 0)
{
v___y_1698_ = v___y_1714_;
v___y_1699_ = v___y_1713_;
v___y_1700_ = v___y_1721_;
v___y_1701_ = v___y_1715_;
v___y_1702_ = v___x_1722_;
v___y_1703_ = v___y_1716_;
v___y_1704_ = v___y_1717_;
v___y_1705_ = v___y_1718_;
v___y_1706_ = v___y_1719_;
v___y_1707_ = v___y_1720_;
v___y_1708_ = v___x_1723_;
goto v___jp_1697_;
}
else
{
v___y_1698_ = v___y_1714_;
v___y_1699_ = v___y_1713_;
v___y_1700_ = v___y_1721_;
v___y_1701_ = v___y_1715_;
v___y_1702_ = v___x_1722_;
v___y_1703_ = v___y_1716_;
v___y_1704_ = v___y_1717_;
v___y_1705_ = v___y_1718_;
v___y_1706_ = v___y_1719_;
v___y_1707_ = v___y_1720_;
v___y_1708_ = v___y_1716_;
goto v___jp_1697_;
}
}
v___jp_1725_:
{
uint64_t v___x_1737_; uint8_t v___x_1738_; 
v___x_1737_ = lean_uint64_shift_right(v___y_1728_, v___y_1734_);
v___x_1738_ = lean_uint64_dec_eq(v___x_1737_, v___y_1730_);
if (v___x_1738_ == 0)
{
uint64_t v___x_1739_; 
v___x_1739_ = lean_uint64_add(v___y_1732_, v___y_1734_);
v___y_1713_ = v___y_1727_;
v___y_1714_ = v___y_1726_;
v___y_1715_ = v___y_1729_;
v___y_1716_ = v___y_1736_;
v___y_1717_ = v___y_1730_;
v___y_1718_ = v___y_1731_;
v___y_1719_ = v___y_1733_;
v___y_1720_ = v___y_1735_;
v___y_1721_ = v___x_1739_;
goto v___jp_1712_;
}
else
{
v___y_1713_ = v___y_1727_;
v___y_1714_ = v___y_1726_;
v___y_1715_ = v___y_1729_;
v___y_1716_ = v___y_1736_;
v___y_1717_ = v___y_1730_;
v___y_1718_ = v___y_1731_;
v___y_1719_ = v___y_1733_;
v___y_1720_ = v___y_1735_;
v___y_1721_ = v___y_1732_;
goto v___jp_1712_;
}
}
v___jp_1740_:
{
uint64_t v___x_1750_; uint64_t v___x_1751_; uint8_t v___x_1752_; 
v___x_1750_ = 4ULL;
v___x_1751_ = lean_uint64_shift_right(v___y_1743_, v___x_1750_);
v___x_1752_ = lean_uint64_dec_eq(v___x_1751_, v___y_1745_);
if (v___x_1752_ == 0)
{
v___y_1726_ = v___y_1742_;
v___y_1727_ = v___y_1741_;
v___y_1728_ = v___y_1743_;
v___y_1729_ = v___y_1744_;
v___y_1730_ = v___y_1745_;
v___y_1731_ = v___y_1746_;
v___y_1732_ = v___y_1749_;
v___y_1733_ = v___y_1747_;
v___y_1734_ = v___x_1750_;
v___y_1735_ = v___y_1748_;
v___y_1736_ = v___x_1751_;
goto v___jp_1725_;
}
else
{
v___y_1726_ = v___y_1742_;
v___y_1727_ = v___y_1741_;
v___y_1728_ = v___y_1743_;
v___y_1729_ = v___y_1744_;
v___y_1730_ = v___y_1745_;
v___y_1731_ = v___y_1746_;
v___y_1732_ = v___y_1749_;
v___y_1733_ = v___y_1747_;
v___y_1734_ = v___x_1750_;
v___y_1735_ = v___y_1748_;
v___y_1736_ = v___y_1743_;
goto v___jp_1725_;
}
}
v___jp_1753_:
{
uint64_t v___x_1765_; uint8_t v___x_1766_; 
v___x_1765_ = lean_uint64_shift_right(v___y_1754_, v___y_1762_);
v___x_1766_ = lean_uint64_dec_eq(v___x_1765_, v___y_1759_);
if (v___x_1766_ == 0)
{
uint64_t v___x_1767_; 
v___x_1767_ = lean_uint64_add(v___y_1758_, v___y_1762_);
v___y_1741_ = v___y_1756_;
v___y_1742_ = v___y_1755_;
v___y_1743_ = v___y_1764_;
v___y_1744_ = v___y_1757_;
v___y_1745_ = v___y_1759_;
v___y_1746_ = v___y_1760_;
v___y_1747_ = v___y_1761_;
v___y_1748_ = v___y_1763_;
v___y_1749_ = v___x_1767_;
goto v___jp_1740_;
}
else
{
v___y_1741_ = v___y_1756_;
v___y_1742_ = v___y_1755_;
v___y_1743_ = v___y_1764_;
v___y_1744_ = v___y_1757_;
v___y_1745_ = v___y_1759_;
v___y_1746_ = v___y_1760_;
v___y_1747_ = v___y_1761_;
v___y_1748_ = v___y_1763_;
v___y_1749_ = v___y_1758_;
goto v___jp_1740_;
}
}
v___jp_1768_:
{
uint64_t v___x_1778_; uint64_t v___x_1779_; uint8_t v___x_1780_; 
v___x_1778_ = 8ULL;
v___x_1779_ = lean_uint64_shift_right(v___y_1771_, v___x_1778_);
v___x_1780_ = lean_uint64_dec_eq(v___x_1779_, v___y_1773_);
if (v___x_1780_ == 0)
{
v___y_1754_ = v___y_1771_;
v___y_1755_ = v___y_1770_;
v___y_1756_ = v___y_1769_;
v___y_1757_ = v___y_1772_;
v___y_1758_ = v___y_1777_;
v___y_1759_ = v___y_1773_;
v___y_1760_ = v___y_1774_;
v___y_1761_ = v___y_1775_;
v___y_1762_ = v___x_1778_;
v___y_1763_ = v___y_1776_;
v___y_1764_ = v___x_1779_;
goto v___jp_1753_;
}
else
{
v___y_1754_ = v___y_1771_;
v___y_1755_ = v___y_1770_;
v___y_1756_ = v___y_1769_;
v___y_1757_ = v___y_1772_;
v___y_1758_ = v___y_1777_;
v___y_1759_ = v___y_1773_;
v___y_1760_ = v___y_1774_;
v___y_1761_ = v___y_1775_;
v___y_1762_ = v___x_1778_;
v___y_1763_ = v___y_1776_;
v___y_1764_ = v___y_1771_;
goto v___jp_1753_;
}
}
v___jp_1781_:
{
uint64_t v___x_1793_; uint8_t v___x_1794_; 
v___x_1793_ = lean_uint64_shift_right(v___y_1786_, v___y_1785_);
v___x_1794_ = lean_uint64_dec_eq(v___x_1793_, v___y_1787_);
if (v___x_1794_ == 0)
{
uint64_t v___x_1795_; 
v___x_1795_ = lean_uint64_add(v___y_1790_, v___y_1785_);
v___y_1769_ = v___y_1783_;
v___y_1770_ = v___y_1782_;
v___y_1771_ = v___y_1792_;
v___y_1772_ = v___y_1784_;
v___y_1773_ = v___y_1787_;
v___y_1774_ = v___y_1788_;
v___y_1775_ = v___y_1789_;
v___y_1776_ = v___y_1791_;
v___y_1777_ = v___x_1795_;
goto v___jp_1768_;
}
else
{
v___y_1769_ = v___y_1783_;
v___y_1770_ = v___y_1782_;
v___y_1771_ = v___y_1792_;
v___y_1772_ = v___y_1784_;
v___y_1773_ = v___y_1787_;
v___y_1774_ = v___y_1788_;
v___y_1775_ = v___y_1789_;
v___y_1776_ = v___y_1791_;
v___y_1777_ = v___y_1790_;
goto v___jp_1768_;
}
}
v___jp_1796_:
{
uint64_t v___x_1806_; uint64_t v___x_1807_; uint8_t v___x_1808_; 
v___x_1806_ = 16ULL;
v___x_1807_ = lean_uint64_shift_right(v___y_1801_, v___x_1806_);
v___x_1808_ = lean_uint64_dec_eq(v___x_1807_, v___y_1800_);
if (v___x_1808_ == 0)
{
v___y_1782_ = v___y_1798_;
v___y_1783_ = v___y_1797_;
v___y_1784_ = v___y_1799_;
v___y_1785_ = v___x_1806_;
v___y_1786_ = v___y_1801_;
v___y_1787_ = v___y_1800_;
v___y_1788_ = v___y_1802_;
v___y_1789_ = v___y_1803_;
v___y_1790_ = v___y_1805_;
v___y_1791_ = v___y_1804_;
v___y_1792_ = v___x_1807_;
goto v___jp_1781_;
}
else
{
v___y_1782_ = v___y_1798_;
v___y_1783_ = v___y_1797_;
v___y_1784_ = v___y_1799_;
v___y_1785_ = v___x_1806_;
v___y_1786_ = v___y_1801_;
v___y_1787_ = v___y_1800_;
v___y_1788_ = v___y_1802_;
v___y_1789_ = v___y_1803_;
v___y_1790_ = v___y_1805_;
v___y_1791_ = v___y_1804_;
v___y_1792_ = v___y_1801_;
goto v___jp_1781_;
}
}
v___jp_1809_:
{
uint64_t v___x_1819_; uint8_t v___x_1820_; 
v___x_1819_ = lean_uint64_shift_right(v___y_1817_, v___y_1814_);
v___x_1820_ = lean_uint64_dec_eq(v___x_1819_, v___y_1813_);
if (v___x_1820_ == 0)
{
v___y_1797_ = v___y_1811_;
v___y_1798_ = v___y_1810_;
v___y_1799_ = v___y_1812_;
v___y_1800_ = v___y_1813_;
v___y_1801_ = v___y_1818_;
v___y_1802_ = v___y_1815_;
v___y_1803_ = v___y_1816_;
v___y_1804_ = v___y_1817_;
v___y_1805_ = v___y_1814_;
goto v___jp_1796_;
}
else
{
v___y_1797_ = v___y_1811_;
v___y_1798_ = v___y_1810_;
v___y_1799_ = v___y_1812_;
v___y_1800_ = v___y_1813_;
v___y_1801_ = v___y_1818_;
v___y_1802_ = v___y_1815_;
v___y_1803_ = v___y_1816_;
v___y_1804_ = v___y_1817_;
v___y_1805_ = v___y_1813_;
goto v___jp_1796_;
}
}
v___jp_1821_:
{
uint64_t v___x_1828_; uint8_t v___x_1829_; 
v___x_1828_ = 0ULL;
v___x_1829_ = lean_uint64_dec_eq(v___y_1827_, v___x_1828_);
if (v___x_1829_ == 0)
{
uint64_t v___x_1830_; uint64_t v___x_1831_; uint8_t v___x_1832_; 
v___x_1830_ = 32ULL;
v___x_1831_ = lean_uint64_shift_right(v___y_1827_, v___x_1830_);
v___x_1832_ = lean_uint64_dec_eq(v___x_1831_, v___x_1828_);
if (v___x_1832_ == 0)
{
v___y_1810_ = v___y_1823_;
v___y_1811_ = v___y_1822_;
v___y_1812_ = v___y_1824_;
v___y_1813_ = v___x_1828_;
v___y_1814_ = v___x_1830_;
v___y_1815_ = v___y_1825_;
v___y_1816_ = v___y_1826_;
v___y_1817_ = v___y_1827_;
v___y_1818_ = v___x_1831_;
goto v___jp_1809_;
}
else
{
v___y_1810_ = v___y_1823_;
v___y_1811_ = v___y_1822_;
v___y_1812_ = v___y_1824_;
v___y_1813_ = v___x_1828_;
v___y_1814_ = v___x_1830_;
v___y_1815_ = v___y_1825_;
v___y_1816_ = v___y_1826_;
v___y_1817_ = v___y_1827_;
v___y_1818_ = v___y_1827_;
goto v___jp_1809_;
}
}
else
{
if (v___y_1826_ == 0)
{
uint32_t v___x_1833_; 
v___x_1833_ = 0;
return v___x_1833_;
}
else
{
uint32_t v___x_1834_; 
v___x_1834_ = 2147483648;
return v___x_1834_;
}
}
}
v___jp_1835_:
{
uint32_t v___x_1839_; uint32_t v___x_1840_; 
v___x_1839_ = lean_uint32_land(v___y_1836_, v___y_1837_);
v___x_1840_ = lean_uint32_lor(v___y_1838_, v___x_1839_);
return v___x_1840_;
}
v___jp_1841_:
{
uint8_t v___x_1846_; 
v___x_1846_ = lean_uint64_dec_eq(v___y_1845_, v___y_1843_);
if (v___x_1846_ == 0)
{
uint64_t v___x_1847_; uint8_t v___x_1848_; 
v___x_1847_ = 8388608ULL;
v___x_1848_ = lean_uint64_dec_eq(v___y_1845_, v___x_1847_);
if (v___x_1848_ == 0)
{
uint32_t v___x_1849_; 
v___x_1849_ = lean_uint64_to_uint32(v___y_1845_);
if (v___y_1844_ == 0)
{
uint32_t v___x_1850_; 
v___x_1850_ = 0;
v___y_1836_ = v___x_1849_;
v___y_1837_ = v___y_1842_;
v___y_1838_ = v___x_1850_;
goto v___jp_1835_;
}
else
{
uint32_t v___x_1851_; 
v___x_1851_ = 2147483648;
v___y_1836_ = v___x_1849_;
v___y_1837_ = v___y_1842_;
v___y_1838_ = v___x_1851_;
goto v___jp_1835_;
}
}
else
{
if (v___y_1844_ == 0)
{
uint32_t v___x_1852_; 
v___x_1852_ = 0;
v___y_1530_ = v___x_1852_;
goto v___jp_1529_;
}
else
{
uint32_t v___x_1853_; 
v___x_1853_ = 2147483648;
v___y_1530_ = v___x_1853_;
goto v___jp_1529_;
}
}
}
else
{
if (v___y_1844_ == 0)
{
uint32_t v___x_1854_; 
v___x_1854_ = 0;
return v___x_1854_;
}
else
{
uint32_t v___x_1855_; 
v___x_1855_ = 2147483648;
return v___x_1855_;
}
}
}
v___jp_1856_:
{
uint64_t v___x_1865_; uint64_t v___x_1866_; uint64_t v___x_1867_; uint8_t v___x_1868_; 
v___x_1865_ = lean_uint64_mul(v___y_1861_, v___y_1858_);
v___x_1866_ = lean_uint64_add(v___y_1863_, v___y_1864_);
v___x_1867_ = 281474976710656ULL;
v___x_1868_ = lean_uint64_dec_lt(v___x_1865_, v___x_1867_);
if (v___x_1868_ == 0)
{
v___y_1822_ = v___x_1866_;
v___y_1823_ = v___y_1857_;
v___y_1824_ = v___y_1859_;
v___y_1825_ = v___y_1860_;
v___y_1826_ = v___y_1862_;
v___y_1827_ = v___x_1865_;
goto v___jp_1821_;
}
else
{
uint64_t v___x_1869_; uint8_t v___x_1870_; 
v___x_1869_ = 123ULL;
v___x_1870_ = lean_uint64_dec_le(v___x_1866_, v___x_1869_);
if (v___x_1870_ == 0)
{
v___y_1822_ = v___x_1866_;
v___y_1823_ = v___y_1857_;
v___y_1824_ = v___y_1859_;
v___y_1825_ = v___y_1860_;
v___y_1826_ = v___y_1862_;
v___y_1827_ = v___x_1865_;
goto v___jp_1821_;
}
else
{
uint64_t v___x_1871_; uint8_t v___x_1872_; 
v___x_1871_ = 0ULL;
v___x_1872_ = lean_uint64_dec_eq(v___x_1865_, v___x_1871_);
if (v___x_1872_ == 0)
{
uint64_t v___x_1873_; uint64_t v___x_1874_; uint8_t v___x_1875_; 
v___x_1873_ = 149ULL;
v___x_1874_ = lean_uint64_sub(v___x_1873_, v___x_1866_);
v___x_1875_ = lean_uint64_dec_eq(v___x_1874_, v___x_1871_);
if (v___x_1875_ == 0)
{
uint64_t v___x_1876_; uint8_t v___x_1877_; 
v___x_1876_ = 64ULL;
v___x_1877_ = lean_uint64_dec_lt(v___x_1874_, v___x_1876_);
if (v___x_1877_ == 0)
{
uint8_t v___x_1878_; 
v___x_1878_ = lean_uint64_dec_eq(v___x_1874_, v___x_1876_);
if (v___x_1878_ == 0)
{
v___y_1842_ = v___y_1860_;
v___y_1843_ = v___x_1871_;
v___y_1844_ = v___y_1862_;
v___y_1845_ = v___x_1871_;
goto v___jp_1841_;
}
else
{
uint64_t v___x_1879_; uint8_t v___x_1880_; 
v___x_1879_ = 9223372036854775808ULL;
v___x_1880_ = lean_uint64_dec_lt(v___x_1879_, v___x_1865_);
if (v___x_1880_ == 0)
{
v___y_1842_ = v___y_1860_;
v___y_1843_ = v___x_1871_;
v___y_1844_ = v___y_1862_;
v___y_1845_ = v___x_1871_;
goto v___jp_1841_;
}
else
{
uint64_t v___x_1881_; 
v___x_1881_ = 1ULL;
v___y_1842_ = v___y_1860_;
v___y_1843_ = v___x_1871_;
v___y_1844_ = v___y_1862_;
v___y_1845_ = v___x_1881_;
goto v___jp_1841_;
}
}
}
else
{
uint64_t v_quotient_1882_; uint64_t v___x_1883_; uint64_t v___x_1884_; uint64_t v___x_1885_; uint64_t v_remainder_1886_; uint64_t v___x_1887_; uint64_t v_half_1888_; uint8_t v___x_1889_; 
v_quotient_1882_ = lean_uint64_shift_right(v___x_1865_, v___x_1874_);
v___x_1883_ = 1ULL;
v___x_1884_ = lean_uint64_shift_left(v___x_1883_, v___x_1874_);
v___x_1885_ = lean_uint64_sub(v___x_1884_, v___x_1883_);
v_remainder_1886_ = lean_uint64_land(v___x_1865_, v___x_1885_);
v___x_1887_ = lean_uint64_sub(v___x_1874_, v___x_1883_);
v_half_1888_ = lean_uint64_shift_left(v___x_1883_, v___x_1887_);
v___x_1889_ = lean_uint64_dec_lt(v_remainder_1886_, v_half_1888_);
if (v___x_1889_ == 0)
{
uint8_t v___x_1890_; 
v___x_1890_ = lean_uint64_dec_lt(v_half_1888_, v_remainder_1886_);
if (v___x_1890_ == 0)
{
uint64_t v___x_1891_; uint8_t v___x_1892_; 
v___x_1891_ = lean_uint64_land(v_quotient_1882_, v___x_1883_);
v___x_1892_ = lean_uint64_dec_eq(v___x_1891_, v___x_1871_);
if (v___x_1892_ == 0)
{
uint64_t v___x_1893_; 
v___x_1893_ = lean_uint64_add(v_quotient_1882_, v___x_1883_);
v___y_1842_ = v___y_1860_;
v___y_1843_ = v___x_1871_;
v___y_1844_ = v___y_1862_;
v___y_1845_ = v___x_1893_;
goto v___jp_1841_;
}
else
{
v___y_1842_ = v___y_1860_;
v___y_1843_ = v___x_1871_;
v___y_1844_ = v___y_1862_;
v___y_1845_ = v_quotient_1882_;
goto v___jp_1841_;
}
}
else
{
uint64_t v___x_1894_; 
v___x_1894_ = lean_uint64_add(v_quotient_1882_, v___x_1883_);
v___y_1842_ = v___y_1860_;
v___y_1843_ = v___x_1871_;
v___y_1844_ = v___y_1862_;
v___y_1845_ = v___x_1894_;
goto v___jp_1841_;
}
}
else
{
v___y_1842_ = v___y_1860_;
v___y_1843_ = v___x_1871_;
v___y_1844_ = v___y_1862_;
v___y_1845_ = v_quotient_1882_;
goto v___jp_1841_;
}
}
}
else
{
v___y_1842_ = v___y_1860_;
v___y_1843_ = v___x_1871_;
v___y_1844_ = v___y_1862_;
v___y_1845_ = v___x_1865_;
goto v___jp_1841_;
}
}
else
{
if (v___y_1862_ == 0)
{
uint32_t v___x_1895_; 
v___x_1895_ = 0;
return v___x_1895_;
}
else
{
uint32_t v___x_1896_; 
v___x_1896_ = 2147483648;
return v___x_1896_;
}
}
}
}
}
v___jp_1897_:
{
uint64_t v___x_1906_; uint64_t v___x_1907_; uint8_t v___x_1908_; 
v___x_1906_ = lean_uint32_to_uint64(v___y_1904_);
v___x_1907_ = 0ULL;
v___x_1908_ = lean_uint64_dec_eq(v___x_1906_, v___x_1907_);
if (v___x_1908_ == 0)
{
uint64_t v___x_1909_; uint64_t v___x_1910_; 
v___x_1909_ = 1ULL;
v___x_1910_ = lean_uint64_sub(v___x_1906_, v___x_1909_);
v___y_1857_ = v___y_1898_;
v___y_1858_ = v___y_1899_;
v___y_1859_ = v___y_1900_;
v___y_1860_ = v___y_1901_;
v___y_1861_ = v___y_1902_;
v___y_1862_ = v___y_1903_;
v___y_1863_ = v___y_1905_;
v___y_1864_ = v___x_1910_;
goto v___jp_1856_;
}
else
{
v___y_1857_ = v___y_1898_;
v___y_1858_ = v___y_1899_;
v___y_1859_ = v___y_1900_;
v___y_1860_ = v___y_1901_;
v___y_1861_ = v___y_1902_;
v___y_1862_ = v___y_1903_;
v___y_1863_ = v___y_1905_;
v___y_1864_ = v___x_1907_;
goto v___jp_1856_;
}
}
v___jp_1911_:
{
uint64_t v___x_1920_; uint64_t v___x_1921_; uint8_t v___x_1922_; 
v___x_1920_ = lean_uint32_to_uint64(v___y_1915_);
v___x_1921_ = 0ULL;
v___x_1922_ = lean_uint64_dec_eq(v___x_1920_, v___x_1921_);
if (v___x_1922_ == 0)
{
uint64_t v___x_1923_; uint64_t v___x_1924_; 
v___x_1923_ = 1ULL;
v___x_1924_ = lean_uint64_sub(v___x_1920_, v___x_1923_);
v___y_1898_ = v___y_1912_;
v___y_1899_ = v___y_1919_;
v___y_1900_ = v___y_1913_;
v___y_1901_ = v___y_1914_;
v___y_1902_ = v___y_1916_;
v___y_1903_ = v___y_1917_;
v___y_1904_ = v___y_1918_;
v___y_1905_ = v___x_1924_;
goto v___jp_1897_;
}
else
{
v___y_1898_ = v___y_1912_;
v___y_1899_ = v___y_1919_;
v___y_1900_ = v___y_1913_;
v___y_1901_ = v___y_1914_;
v___y_1902_ = v___y_1916_;
v___y_1903_ = v___y_1917_;
v___y_1904_ = v___y_1918_;
v___y_1905_ = v___x_1921_;
goto v___jp_1897_;
}
}
v___jp_1925_:
{
uint32_t v___x_1934_; uint8_t v___x_1935_; 
v___x_1934_ = 0;
v___x_1935_ = lean_uint32_dec_eq(v___y_1932_, v___x_1934_);
if (v___x_1935_ == 0)
{
uint64_t v___x_1936_; uint64_t v___x_1937_; uint64_t v___x_1938_; 
v___x_1936_ = lean_uint32_to_uint64(v___y_1930_);
v___x_1937_ = 8388608ULL;
v___x_1938_ = lean_uint64_lor(v___x_1936_, v___x_1937_);
v___y_1912_ = v___y_1926_;
v___y_1913_ = v___y_1927_;
v___y_1914_ = v___y_1928_;
v___y_1915_ = v___y_1929_;
v___y_1916_ = v___y_1933_;
v___y_1917_ = v___y_1931_;
v___y_1918_ = v___y_1932_;
v___y_1919_ = v___x_1938_;
goto v___jp_1911_;
}
else
{
uint64_t v___x_1939_; 
v___x_1939_ = lean_uint32_to_uint64(v___y_1930_);
v___y_1912_ = v___y_1926_;
v___y_1913_ = v___y_1927_;
v___y_1914_ = v___y_1928_;
v___y_1915_ = v___y_1929_;
v___y_1916_ = v___y_1933_;
v___y_1917_ = v___y_1931_;
v___y_1918_ = v___y_1932_;
v___y_1919_ = v___x_1939_;
goto v___jp_1911_;
}
}
v___jp_1940_:
{
uint32_t v___x_1947_; uint32_t v___x_1948_; uint32_t v___x_1949_; uint32_t v___x_1950_; uint32_t v___x_1951_; 
v___x_1947_ = lean_uint32_land(v___y_1942_, v___y_1945_);
v___x_1948_ = lean_uint32_shift_left(v___x_1947_, v___y_1941_);
v___x_1949_ = lean_uint32_lor(v___y_1946_, v___x_1948_);
v___x_1950_ = lean_uint32_land(v___y_1943_, v___y_1944_);
v___x_1951_ = lean_uint32_lor(v___x_1949_, v___x_1950_);
return v___x_1951_;
}
v___jp_1952_:
{
uint32_t v___x_1961_; uint32_t v___x_1962_; uint32_t v___x_1963_; uint32_t v___x_1964_; uint32_t v___x_1965_; uint32_t v___x_1966_; uint32_t v___x_1967_; uint32_t v___x_1968_; 
v___x_1961_ = 127;
v___x_1962_ = lean_uint32_sub(v___y_1954_, v___x_1961_);
v___x_1963_ = lean_uint64_to_uint32(v___y_1956_);
v___x_1964_ = lean_uint32_add(v___x_1962_, v___x_1963_);
v___x_1965_ = lean_uint64_to_uint32(v___y_1955_);
v___x_1966_ = lean_uint32_add(v___x_1964_, v___x_1965_);
v___x_1967_ = lean_uint64_to_uint32(v___y_1957_);
v___x_1968_ = lean_uint32_land(v___x_1967_, v___y_1959_);
if (v___y_1960_ == 0)
{
uint32_t v___x_1969_; 
v___x_1969_ = 0;
v___y_1941_ = v___y_1953_;
v___y_1942_ = v___x_1966_;
v___y_1943_ = v___x_1968_;
v___y_1944_ = v___y_1959_;
v___y_1945_ = v___y_1958_;
v___y_1946_ = v___x_1969_;
goto v___jp_1940_;
}
else
{
uint32_t v___x_1970_; 
v___x_1970_ = 2147483648;
v___y_1941_ = v___y_1953_;
v___y_1942_ = v___x_1966_;
v___y_1943_ = v___x_1968_;
v___y_1944_ = v___y_1959_;
v___y_1945_ = v___y_1958_;
v___y_1946_ = v___x_1970_;
goto v___jp_1940_;
}
}
v___jp_1971_:
{
uint8_t v___x_1979_; 
v___x_1979_ = 0;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v___y_1973_;
v___y_1955_ = v___y_1974_;
v___y_1956_ = v___y_1975_;
v___y_1957_ = v___y_1976_;
v___y_1958_ = v___y_1978_;
v___y_1959_ = v___y_1977_;
v___y_1960_ = v___x_1979_;
goto v___jp_1952_;
}
v___jp_1980_:
{
if (v___y_1989_ == 0)
{
v___y_1953_ = v___y_1981_;
v___y_1954_ = v___y_1982_;
v___y_1955_ = v___y_1983_;
v___y_1956_ = v___y_1984_;
v___y_1957_ = v___y_1985_;
v___y_1958_ = v___y_1987_;
v___y_1959_ = v___y_1986_;
v___y_1960_ = v___y_1988_;
goto v___jp_1952_;
}
else
{
v___y_1972_ = v___y_1981_;
v___y_1973_ = v___y_1982_;
v___y_1974_ = v___y_1983_;
v___y_1975_ = v___y_1984_;
v___y_1976_ = v___y_1985_;
v___y_1977_ = v___y_1986_;
v___y_1978_ = v___y_1987_;
goto v___jp_1971_;
}
}
v___jp_1990_:
{
uint32_t v___x_1994_; uint32_t v___x_1995_; 
v___x_1994_ = lean_uint32_land(v___y_1992_, v___y_1991_);
v___x_1995_ = lean_uint32_lor(v___y_1993_, v___x_1994_);
return v___x_1995_;
}
v___jp_1996_:
{
uint8_t v___x_2001_; 
v___x_2001_ = lean_uint64_dec_eq(v___y_2000_, v___y_1999_);
if (v___x_2001_ == 0)
{
uint64_t v___x_2002_; uint8_t v___x_2003_; 
v___x_2002_ = 8388608ULL;
v___x_2003_ = lean_uint64_dec_eq(v___y_2000_, v___x_2002_);
if (v___x_2003_ == 0)
{
uint32_t v___x_2004_; 
v___x_2004_ = lean_uint64_to_uint32(v___y_2000_);
if (v___y_1998_ == 0)
{
uint32_t v___x_2005_; 
v___x_2005_ = 0;
v___y_1991_ = v___y_1997_;
v___y_1992_ = v___x_2004_;
v___y_1993_ = v___x_2005_;
goto v___jp_1990_;
}
else
{
uint32_t v___x_2006_; 
v___x_2006_ = 2147483648;
v___y_1991_ = v___y_1997_;
v___y_1992_ = v___x_2004_;
v___y_1993_ = v___x_2006_;
goto v___jp_1990_;
}
}
else
{
if (v___y_1998_ == 0)
{
uint32_t v___x_2007_; 
v___x_2007_ = 0;
v___y_1522_ = v___x_2007_;
goto v___jp_1521_;
}
else
{
uint32_t v___x_2008_; 
v___x_2008_ = 2147483648;
v___y_1522_ = v___x_2008_;
goto v___jp_1521_;
}
}
}
else
{
if (v___y_1998_ == 0)
{
uint32_t v___x_2009_; 
v___x_2009_ = 0;
return v___x_2009_;
}
else
{
uint32_t v___x_2010_; 
v___x_2010_ = 2147483648;
return v___x_2010_;
}
}
}
v___jp_2011_:
{
uint32_t v___x_2018_; uint32_t v___x_2019_; uint32_t v___x_2020_; uint32_t v___x_2021_; uint32_t v___x_2022_; 
v___x_2018_ = lean_uint32_land(v___y_2015_, v___y_2016_);
v___x_2019_ = lean_uint32_shift_left(v___x_2018_, v___y_2013_);
v___x_2020_ = lean_uint32_lor(v___y_2017_, v___x_2019_);
v___x_2021_ = lean_uint32_land(v___y_2012_, v___y_2014_);
v___x_2022_ = lean_uint32_lor(v___x_2020_, v___x_2021_);
return v___x_2022_;
}
v___jp_2023_:
{
if (v___y_2026_ == 0)
{
uint32_t v___x_2030_; 
v___x_2030_ = 0;
v___y_2012_ = v___y_2029_;
v___y_2013_ = v___y_2024_;
v___y_2014_ = v___y_2025_;
v___y_2015_ = v___y_2027_;
v___y_2016_ = v___y_2028_;
v___y_2017_ = v___x_2030_;
goto v___jp_2011_;
}
else
{
uint32_t v___x_2031_; 
v___x_2031_ = 2147483648;
v___y_2012_ = v___y_2029_;
v___y_2013_ = v___y_2024_;
v___y_2014_ = v___y_2025_;
v___y_2015_ = v___y_2027_;
v___y_2016_ = v___y_2028_;
v___y_2017_ = v___x_2031_;
goto v___jp_2011_;
}
}
v___jp_2032_:
{
uint64_t v___x_2040_; uint64_t v_encodedExponent_2041_; uint32_t v___x_2042_; uint64_t v___x_2043_; uint8_t v___x_2044_; 
v___x_2040_ = 171ULL;
v_encodedExponent_2041_ = lean_uint64_sub(v___y_2036_, v___x_2040_);
v___x_2042_ = lean_uint64_to_uint32(v_encodedExponent_2041_);
v___x_2043_ = 8388608ULL;
v___x_2044_ = lean_uint64_dec_lt(v___y_2039_, v___x_2043_);
if (v___x_2044_ == 0)
{
uint64_t v___x_2045_; uint32_t v___x_2046_; 
v___x_2045_ = lean_uint64_sub(v___y_2039_, v___x_2043_);
v___x_2046_ = lean_uint64_to_uint32(v___x_2045_);
v___y_2024_ = v___y_2033_;
v___y_2025_ = v___y_2034_;
v___y_2026_ = v___y_2035_;
v___y_2027_ = v___x_2042_;
v___y_2028_ = v___y_2038_;
v___y_2029_ = v___x_2046_;
goto v___jp_2023_;
}
else
{
uint32_t v___x_2047_; 
v___x_2047_ = lean_uint64_to_uint32(v___y_2037_);
v___y_2024_ = v___y_2033_;
v___y_2025_ = v___y_2034_;
v___y_2026_ = v___y_2035_;
v___y_2027_ = v___x_2042_;
v___y_2028_ = v___y_2038_;
v___y_2029_ = v___x_2047_;
goto v___jp_2023_;
}
}
v___jp_2048_:
{
uint64_t v___x_2057_; uint8_t v___x_2058_; 
v___x_2057_ = 425ULL;
v___x_2058_ = lean_uint64_dec_lt(v___x_2057_, v___y_2056_);
if (v___x_2058_ == 0)
{
if (v___y_2049_ == 0)
{
v___y_2033_ = v___y_2050_;
v___y_2034_ = v___y_2051_;
v___y_2035_ = v___y_2052_;
v___y_2036_ = v___y_2056_;
v___y_2037_ = v___y_2054_;
v___y_2038_ = v___y_2055_;
v___y_2039_ = v___y_2053_;
goto v___jp_2032_;
}
else
{
uint64_t v___x_2059_; 
v___x_2059_ = 8388608ULL;
v___y_2033_ = v___y_2050_;
v___y_2034_ = v___y_2051_;
v___y_2035_ = v___y_2052_;
v___y_2036_ = v___y_2056_;
v___y_2037_ = v___y_2054_;
v___y_2038_ = v___y_2055_;
v___y_2039_ = v___x_2059_;
goto v___jp_2032_;
}
}
else
{
if (v___y_2052_ == 0)
{
uint32_t v___x_2060_; 
v___x_2060_ = 2139095040;
return v___x_2060_;
}
else
{
uint32_t v___x_2061_; 
v___x_2061_ = 4286578688;
return v___x_2061_;
}
}
}
v___jp_2062_:
{
uint64_t v___x_2070_; uint8_t v_carry_2071_; 
v___x_2070_ = 16777216ULL;
v_carry_2071_ = lean_uint64_dec_eq(v___y_2069_, v___x_2070_);
if (v_carry_2071_ == 0)
{
v___y_2049_ = v_carry_2071_;
v___y_2050_ = v___y_2064_;
v___y_2051_ = v___y_2065_;
v___y_2052_ = v___y_2066_;
v___y_2053_ = v___y_2069_;
v___y_2054_ = v___y_2067_;
v___y_2055_ = v___y_2068_;
v___y_2056_ = v___y_2063_;
goto v___jp_2048_;
}
else
{
uint64_t v___x_2072_; uint64_t v___x_2073_; 
v___x_2072_ = 1ULL;
v___x_2073_ = lean_uint64_add(v___y_2063_, v___x_2072_);
v___y_2049_ = v_carry_2071_;
v___y_2050_ = v___y_2064_;
v___y_2051_ = v___y_2065_;
v___y_2052_ = v___y_2066_;
v___y_2053_ = v___y_2069_;
v___y_2054_ = v___y_2067_;
v___y_2055_ = v___y_2068_;
v___y_2056_ = v___x_2073_;
goto v___jp_2048_;
}
}
v___jp_2074_:
{
uint64_t v_position_2083_; uint64_t v___x_2084_; uint8_t v___x_2085_; 
v_position_2083_ = lean_uint64_add(v___y_2082_, v___y_2079_);
v___x_2084_ = 172ULL;
v___x_2085_ = lean_uint64_dec_lt(v_position_2083_, v___x_2084_);
if (v___x_2085_ == 0)
{
uint64_t v___x_2086_; uint8_t v___x_2087_; 
v___x_2086_ = 23ULL;
v___x_2087_ = lean_uint64_dec_lt(v___y_2082_, v___x_2086_);
if (v___x_2087_ == 0)
{
uint64_t v___x_2088_; uint8_t v___x_2089_; 
v___x_2088_ = lean_uint64_sub(v___y_2082_, v___x_2086_);
v___x_2089_ = lean_uint64_dec_eq(v___x_2088_, v___y_2080_);
if (v___x_2089_ == 0)
{
uint64_t v___x_2090_; uint8_t v___x_2091_; 
v___x_2090_ = 64ULL;
v___x_2091_ = lean_uint64_dec_lt(v___x_2088_, v___x_2090_);
if (v___x_2091_ == 0)
{
uint8_t v___x_2092_; 
v___x_2092_ = lean_uint64_dec_eq(v___x_2088_, v___x_2090_);
if (v___x_2092_ == 0)
{
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v___y_2080_;
goto v___jp_2062_;
}
else
{
uint64_t v___x_2093_; uint8_t v___x_2094_; 
v___x_2093_ = 9223372036854775808ULL;
v___x_2094_ = lean_uint64_dec_lt(v___x_2093_, v___y_2076_);
if (v___x_2094_ == 0)
{
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v___y_2080_;
goto v___jp_2062_;
}
else
{
uint64_t v___x_2095_; 
v___x_2095_ = 1ULL;
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v___x_2095_;
goto v___jp_2062_;
}
}
}
else
{
uint64_t v_quotient_2096_; uint64_t v___x_2097_; uint64_t v___x_2098_; uint64_t v___x_2099_; uint64_t v_remainder_2100_; uint64_t v___x_2101_; uint64_t v_half_2102_; uint8_t v___x_2103_; 
v_quotient_2096_ = lean_uint64_shift_right(v___y_2076_, v___x_2088_);
v___x_2097_ = 1ULL;
v___x_2098_ = lean_uint64_shift_left(v___x_2097_, v___x_2088_);
v___x_2099_ = lean_uint64_sub(v___x_2098_, v___x_2097_);
v_remainder_2100_ = lean_uint64_land(v___y_2076_, v___x_2099_);
v___x_2101_ = lean_uint64_sub(v___x_2088_, v___x_2097_);
v_half_2102_ = lean_uint64_shift_left(v___x_2097_, v___x_2101_);
v___x_2103_ = lean_uint64_dec_lt(v_remainder_2100_, v_half_2102_);
if (v___x_2103_ == 0)
{
uint8_t v___x_2104_; 
v___x_2104_ = lean_uint64_dec_lt(v_half_2102_, v_remainder_2100_);
if (v___x_2104_ == 0)
{
uint64_t v___x_2105_; uint8_t v___x_2106_; 
v___x_2105_ = lean_uint64_land(v_quotient_2096_, v___x_2097_);
v___x_2106_ = lean_uint64_dec_eq(v___x_2105_, v___y_2080_);
if (v___x_2106_ == 0)
{
uint64_t v___x_2107_; 
v___x_2107_ = lean_uint64_add(v_quotient_2096_, v___x_2097_);
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v___x_2107_;
goto v___jp_2062_;
}
else
{
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v_quotient_2096_;
goto v___jp_2062_;
}
}
else
{
uint64_t v___x_2108_; 
v___x_2108_ = lean_uint64_add(v_quotient_2096_, v___x_2097_);
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v___x_2108_;
goto v___jp_2062_;
}
}
else
{
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v_quotient_2096_;
goto v___jp_2062_;
}
}
}
else
{
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v___y_2076_;
goto v___jp_2062_;
}
}
else
{
uint64_t v___x_2109_; uint64_t v___x_2110_; 
v___x_2109_ = lean_uint64_sub(v___x_2086_, v___y_2082_);
v___x_2110_ = lean_uint64_shift_left(v___y_2076_, v___x_2109_);
v___y_2063_ = v_position_2083_;
v___y_2064_ = v___y_2075_;
v___y_2065_ = v___y_2077_;
v___y_2066_ = v___y_2078_;
v___y_2067_ = v___y_2080_;
v___y_2068_ = v___y_2081_;
v___y_2069_ = v___x_2110_;
goto v___jp_2062_;
}
}
else
{
uint64_t v___x_2111_; uint8_t v___x_2112_; 
v___x_2111_ = 149ULL;
v___x_2112_ = lean_uint64_dec_lt(v___y_2079_, v___x_2111_);
if (v___x_2112_ == 0)
{
uint64_t v___x_2113_; uint64_t v___x_2114_; 
v___x_2113_ = lean_uint64_sub(v___y_2079_, v___x_2111_);
v___x_2114_ = lean_uint64_shift_left(v___y_2076_, v___x_2113_);
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v___x_2114_;
goto v___jp_1996_;
}
else
{
uint64_t v___x_2115_; uint8_t v___x_2116_; 
v___x_2115_ = lean_uint64_sub(v___x_2111_, v___y_2079_);
v___x_2116_ = lean_uint64_dec_eq(v___x_2115_, v___y_2080_);
if (v___x_2116_ == 0)
{
uint64_t v___x_2117_; uint8_t v___x_2118_; 
v___x_2117_ = 64ULL;
v___x_2118_ = lean_uint64_dec_lt(v___x_2115_, v___x_2117_);
if (v___x_2118_ == 0)
{
uint8_t v___x_2119_; 
v___x_2119_ = lean_uint64_dec_eq(v___x_2115_, v___x_2117_);
if (v___x_2119_ == 0)
{
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v___y_2080_;
goto v___jp_1996_;
}
else
{
uint64_t v___x_2120_; uint8_t v___x_2121_; 
v___x_2120_ = 9223372036854775808ULL;
v___x_2121_ = lean_uint64_dec_lt(v___x_2120_, v___y_2076_);
if (v___x_2121_ == 0)
{
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v___y_2080_;
goto v___jp_1996_;
}
else
{
uint64_t v___x_2122_; 
v___x_2122_ = 1ULL;
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v___x_2122_;
goto v___jp_1996_;
}
}
}
else
{
uint64_t v_quotient_2123_; uint64_t v___x_2124_; uint64_t v___x_2125_; uint64_t v___x_2126_; uint64_t v_remainder_2127_; uint64_t v___x_2128_; uint64_t v_half_2129_; uint8_t v___x_2130_; 
v_quotient_2123_ = lean_uint64_shift_right(v___y_2076_, v___x_2115_);
v___x_2124_ = 1ULL;
v___x_2125_ = lean_uint64_shift_left(v___x_2124_, v___x_2115_);
v___x_2126_ = lean_uint64_sub(v___x_2125_, v___x_2124_);
v_remainder_2127_ = lean_uint64_land(v___y_2076_, v___x_2126_);
v___x_2128_ = lean_uint64_sub(v___x_2115_, v___x_2124_);
v_half_2129_ = lean_uint64_shift_left(v___x_2124_, v___x_2128_);
v___x_2130_ = lean_uint64_dec_lt(v_remainder_2127_, v_half_2129_);
if (v___x_2130_ == 0)
{
uint8_t v___x_2131_; 
v___x_2131_ = lean_uint64_dec_lt(v_half_2129_, v_remainder_2127_);
if (v___x_2131_ == 0)
{
uint64_t v___x_2132_; uint8_t v___x_2133_; 
v___x_2132_ = lean_uint64_land(v_quotient_2123_, v___x_2124_);
v___x_2133_ = lean_uint64_dec_eq(v___x_2132_, v___y_2080_);
if (v___x_2133_ == 0)
{
uint64_t v___x_2134_; 
v___x_2134_ = lean_uint64_add(v_quotient_2123_, v___x_2124_);
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v___x_2134_;
goto v___jp_1996_;
}
else
{
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v_quotient_2123_;
goto v___jp_1996_;
}
}
else
{
uint64_t v___x_2135_; 
v___x_2135_ = lean_uint64_add(v_quotient_2123_, v___x_2124_);
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v___x_2135_;
goto v___jp_1996_;
}
}
else
{
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v_quotient_2123_;
goto v___jp_1996_;
}
}
}
else
{
v___y_1997_ = v___y_2077_;
v___y_1998_ = v___y_2078_;
v___y_1999_ = v___y_2080_;
v___y_2000_ = v___y_2076_;
goto v___jp_1996_;
}
}
}
}
v___jp_2136_:
{
uint64_t v___x_2146_; uint64_t v___x_2147_; uint8_t v___x_2148_; 
v___x_2146_ = 1ULL;
v___x_2147_ = lean_uint64_shift_right(v___y_2142_, v___x_2146_);
v___x_2148_ = lean_uint64_dec_eq(v___x_2147_, v___y_2143_);
if (v___x_2148_ == 0)
{
uint64_t v___x_2149_; 
v___x_2149_ = lean_uint64_add(v___y_2145_, v___x_2146_);
v___y_2075_ = v___y_2137_;
v___y_2076_ = v___y_2139_;
v___y_2077_ = v___y_2138_;
v___y_2078_ = v___y_2140_;
v___y_2079_ = v___y_2141_;
v___y_2080_ = v___y_2143_;
v___y_2081_ = v___y_2144_;
v___y_2082_ = v___x_2149_;
goto v___jp_2074_;
}
else
{
v___y_2075_ = v___y_2137_;
v___y_2076_ = v___y_2139_;
v___y_2077_ = v___y_2138_;
v___y_2078_ = v___y_2140_;
v___y_2079_ = v___y_2141_;
v___y_2080_ = v___y_2143_;
v___y_2081_ = v___y_2144_;
v___y_2082_ = v___y_2145_;
goto v___jp_2074_;
}
}
v___jp_2150_:
{
uint64_t v___x_2162_; uint8_t v___x_2163_; 
v___x_2162_ = lean_uint64_shift_right(v___y_2152_, v___y_2151_);
v___x_2163_ = lean_uint64_dec_eq(v___x_2162_, v___y_2159_);
if (v___x_2163_ == 0)
{
uint64_t v___x_2164_; 
v___x_2164_ = lean_uint64_add(v___y_2156_, v___y_2151_);
v___y_2137_ = v___y_2153_;
v___y_2138_ = v___y_2155_;
v___y_2139_ = v___y_2154_;
v___y_2140_ = v___y_2157_;
v___y_2141_ = v___y_2158_;
v___y_2142_ = v___y_2161_;
v___y_2143_ = v___y_2159_;
v___y_2144_ = v___y_2160_;
v___y_2145_ = v___x_2164_;
goto v___jp_2136_;
}
else
{
v___y_2137_ = v___y_2153_;
v___y_2138_ = v___y_2155_;
v___y_2139_ = v___y_2154_;
v___y_2140_ = v___y_2157_;
v___y_2141_ = v___y_2158_;
v___y_2142_ = v___y_2161_;
v___y_2143_ = v___y_2159_;
v___y_2144_ = v___y_2160_;
v___y_2145_ = v___y_2156_;
goto v___jp_2136_;
}
}
v___jp_2165_:
{
uint64_t v___x_2175_; uint64_t v___x_2176_; uint8_t v___x_2177_; 
v___x_2175_ = 2ULL;
v___x_2176_ = lean_uint64_shift_right(v___y_2167_, v___x_2175_);
v___x_2177_ = lean_uint64_dec_eq(v___x_2176_, v___y_2172_);
if (v___x_2177_ == 0)
{
v___y_2151_ = v___x_2175_;
v___y_2152_ = v___y_2167_;
v___y_2153_ = v___y_2166_;
v___y_2154_ = v___y_2169_;
v___y_2155_ = v___y_2168_;
v___y_2156_ = v___y_2174_;
v___y_2157_ = v___y_2170_;
v___y_2158_ = v___y_2171_;
v___y_2159_ = v___y_2172_;
v___y_2160_ = v___y_2173_;
v___y_2161_ = v___x_2176_;
goto v___jp_2150_;
}
else
{
v___y_2151_ = v___x_2175_;
v___y_2152_ = v___y_2167_;
v___y_2153_ = v___y_2166_;
v___y_2154_ = v___y_2169_;
v___y_2155_ = v___y_2168_;
v___y_2156_ = v___y_2174_;
v___y_2157_ = v___y_2170_;
v___y_2158_ = v___y_2171_;
v___y_2159_ = v___y_2172_;
v___y_2160_ = v___y_2173_;
v___y_2161_ = v___y_2167_;
goto v___jp_2150_;
}
}
v___jp_2178_:
{
uint64_t v___x_2190_; uint8_t v___x_2191_; 
v___x_2190_ = lean_uint64_shift_right(v___y_2184_, v___y_2179_);
v___x_2191_ = lean_uint64_dec_eq(v___x_2190_, v___y_2187_);
if (v___x_2191_ == 0)
{
uint64_t v___x_2192_; 
v___x_2192_ = lean_uint64_add(v___y_2186_, v___y_2179_);
v___y_2166_ = v___y_2180_;
v___y_2167_ = v___y_2189_;
v___y_2168_ = v___y_2182_;
v___y_2169_ = v___y_2181_;
v___y_2170_ = v___y_2183_;
v___y_2171_ = v___y_2185_;
v___y_2172_ = v___y_2187_;
v___y_2173_ = v___y_2188_;
v___y_2174_ = v___x_2192_;
goto v___jp_2165_;
}
else
{
v___y_2166_ = v___y_2180_;
v___y_2167_ = v___y_2189_;
v___y_2168_ = v___y_2182_;
v___y_2169_ = v___y_2181_;
v___y_2170_ = v___y_2183_;
v___y_2171_ = v___y_2185_;
v___y_2172_ = v___y_2187_;
v___y_2173_ = v___y_2188_;
v___y_2174_ = v___y_2186_;
goto v___jp_2165_;
}
}
v___jp_2193_:
{
uint64_t v___x_2203_; uint64_t v___x_2204_; uint8_t v___x_2205_; 
v___x_2203_ = 4ULL;
v___x_2204_ = lean_uint64_shift_right(v___y_2199_, v___x_2203_);
v___x_2205_ = lean_uint64_dec_eq(v___x_2204_, v___y_2200_);
if (v___x_2205_ == 0)
{
v___y_2179_ = v___x_2203_;
v___y_2180_ = v___y_2194_;
v___y_2181_ = v___y_2196_;
v___y_2182_ = v___y_2195_;
v___y_2183_ = v___y_2197_;
v___y_2184_ = v___y_2199_;
v___y_2185_ = v___y_2198_;
v___y_2186_ = v___y_2202_;
v___y_2187_ = v___y_2200_;
v___y_2188_ = v___y_2201_;
v___y_2189_ = v___x_2204_;
goto v___jp_2178_;
}
else
{
v___y_2179_ = v___x_2203_;
v___y_2180_ = v___y_2194_;
v___y_2181_ = v___y_2196_;
v___y_2182_ = v___y_2195_;
v___y_2183_ = v___y_2197_;
v___y_2184_ = v___y_2199_;
v___y_2185_ = v___y_2198_;
v___y_2186_ = v___y_2202_;
v___y_2187_ = v___y_2200_;
v___y_2188_ = v___y_2201_;
v___y_2189_ = v___y_2199_;
goto v___jp_2178_;
}
}
v___jp_2206_:
{
uint64_t v___x_2218_; uint8_t v___x_2219_; 
v___x_2218_ = lean_uint64_shift_right(v___y_2208_, v___y_2216_);
v___x_2219_ = lean_uint64_dec_eq(v___x_2218_, v___y_2214_);
if (v___x_2219_ == 0)
{
uint64_t v___x_2220_; 
v___x_2220_ = lean_uint64_add(v___y_2207_, v___y_2216_);
v___y_2194_ = v___y_2209_;
v___y_2195_ = v___y_2211_;
v___y_2196_ = v___y_2210_;
v___y_2197_ = v___y_2212_;
v___y_2198_ = v___y_2213_;
v___y_2199_ = v___y_2217_;
v___y_2200_ = v___y_2214_;
v___y_2201_ = v___y_2215_;
v___y_2202_ = v___x_2220_;
goto v___jp_2193_;
}
else
{
v___y_2194_ = v___y_2209_;
v___y_2195_ = v___y_2211_;
v___y_2196_ = v___y_2210_;
v___y_2197_ = v___y_2212_;
v___y_2198_ = v___y_2213_;
v___y_2199_ = v___y_2217_;
v___y_2200_ = v___y_2214_;
v___y_2201_ = v___y_2215_;
v___y_2202_ = v___y_2207_;
goto v___jp_2193_;
}
}
v___jp_2221_:
{
uint64_t v___x_2231_; uint64_t v___x_2232_; uint8_t v___x_2233_; 
v___x_2231_ = 8ULL;
v___x_2232_ = lean_uint64_shift_right(v___y_2223_, v___x_2231_);
v___x_2233_ = lean_uint64_dec_eq(v___x_2232_, v___y_2228_);
if (v___x_2233_ == 0)
{
v___y_2207_ = v___y_2230_;
v___y_2208_ = v___y_2223_;
v___y_2209_ = v___y_2222_;
v___y_2210_ = v___y_2225_;
v___y_2211_ = v___y_2224_;
v___y_2212_ = v___y_2226_;
v___y_2213_ = v___y_2227_;
v___y_2214_ = v___y_2228_;
v___y_2215_ = v___y_2229_;
v___y_2216_ = v___x_2231_;
v___y_2217_ = v___x_2232_;
goto v___jp_2206_;
}
else
{
v___y_2207_ = v___y_2230_;
v___y_2208_ = v___y_2223_;
v___y_2209_ = v___y_2222_;
v___y_2210_ = v___y_2225_;
v___y_2211_ = v___y_2224_;
v___y_2212_ = v___y_2226_;
v___y_2213_ = v___y_2227_;
v___y_2214_ = v___y_2228_;
v___y_2215_ = v___y_2229_;
v___y_2216_ = v___x_2231_;
v___y_2217_ = v___y_2223_;
goto v___jp_2206_;
}
}
v___jp_2234_:
{
uint64_t v___x_2246_; uint8_t v___x_2247_; 
v___x_2246_ = lean_uint64_shift_right(v___y_2237_, v___y_2235_);
v___x_2247_ = lean_uint64_dec_eq(v___x_2246_, v___y_2243_);
if (v___x_2247_ == 0)
{
uint64_t v___x_2248_; 
v___x_2248_ = lean_uint64_add(v___y_2236_, v___y_2235_);
v___y_2222_ = v___y_2238_;
v___y_2223_ = v___y_2245_;
v___y_2224_ = v___y_2240_;
v___y_2225_ = v___y_2239_;
v___y_2226_ = v___y_2241_;
v___y_2227_ = v___y_2242_;
v___y_2228_ = v___y_2243_;
v___y_2229_ = v___y_2244_;
v___y_2230_ = v___x_2248_;
goto v___jp_2221_;
}
else
{
v___y_2222_ = v___y_2238_;
v___y_2223_ = v___y_2245_;
v___y_2224_ = v___y_2240_;
v___y_2225_ = v___y_2239_;
v___y_2226_ = v___y_2241_;
v___y_2227_ = v___y_2242_;
v___y_2228_ = v___y_2243_;
v___y_2229_ = v___y_2244_;
v___y_2230_ = v___y_2236_;
goto v___jp_2221_;
}
}
v___jp_2249_:
{
uint64_t v___x_2259_; uint64_t v___x_2260_; uint8_t v___x_2261_; 
v___x_2259_ = 16ULL;
v___x_2260_ = lean_uint64_shift_right(v___y_2251_, v___x_2259_);
v___x_2261_ = lean_uint64_dec_eq(v___x_2260_, v___y_2256_);
if (v___x_2261_ == 0)
{
v___y_2235_ = v___x_2259_;
v___y_2236_ = v___y_2258_;
v___y_2237_ = v___y_2251_;
v___y_2238_ = v___y_2250_;
v___y_2239_ = v___y_2253_;
v___y_2240_ = v___y_2252_;
v___y_2241_ = v___y_2254_;
v___y_2242_ = v___y_2255_;
v___y_2243_ = v___y_2256_;
v___y_2244_ = v___y_2257_;
v___y_2245_ = v___x_2260_;
goto v___jp_2234_;
}
else
{
v___y_2235_ = v___x_2259_;
v___y_2236_ = v___y_2258_;
v___y_2237_ = v___y_2251_;
v___y_2238_ = v___y_2250_;
v___y_2239_ = v___y_2253_;
v___y_2240_ = v___y_2252_;
v___y_2241_ = v___y_2254_;
v___y_2242_ = v___y_2255_;
v___y_2243_ = v___y_2256_;
v___y_2244_ = v___y_2257_;
v___y_2245_ = v___y_2251_;
goto v___jp_2234_;
}
}
v___jp_2262_:
{
uint64_t v___x_2272_; uint8_t v___x_2273_; 
v___x_2272_ = lean_uint64_shift_right(v___y_2264_, v___y_2269_);
v___x_2273_ = lean_uint64_dec_eq(v___x_2272_, v___y_2268_);
if (v___x_2273_ == 0)
{
v___y_2250_ = v___y_2263_;
v___y_2251_ = v___y_2271_;
v___y_2252_ = v___y_2265_;
v___y_2253_ = v___y_2264_;
v___y_2254_ = v___y_2266_;
v___y_2255_ = v___y_2267_;
v___y_2256_ = v___y_2268_;
v___y_2257_ = v___y_2270_;
v___y_2258_ = v___y_2269_;
goto v___jp_2249_;
}
else
{
v___y_2250_ = v___y_2263_;
v___y_2251_ = v___y_2271_;
v___y_2252_ = v___y_2265_;
v___y_2253_ = v___y_2264_;
v___y_2254_ = v___y_2266_;
v___y_2255_ = v___y_2267_;
v___y_2256_ = v___y_2268_;
v___y_2257_ = v___y_2270_;
v___y_2258_ = v___y_2268_;
goto v___jp_2249_;
}
}
v___jp_2274_:
{
uint64_t v___x_2281_; uint8_t v___x_2282_; 
v___x_2281_ = 0ULL;
v___x_2282_ = lean_uint64_dec_eq(v___y_2276_, v___x_2281_);
if (v___x_2282_ == 0)
{
uint64_t v___x_2283_; uint64_t v___x_2284_; uint8_t v___x_2285_; 
v___x_2283_ = 32ULL;
v___x_2284_ = lean_uint64_shift_right(v___y_2276_, v___x_2283_);
v___x_2285_ = lean_uint64_dec_eq(v___x_2284_, v___x_2281_);
if (v___x_2285_ == 0)
{
v___y_2263_ = v___y_2275_;
v___y_2264_ = v___y_2276_;
v___y_2265_ = v___y_2277_;
v___y_2266_ = v___y_2278_;
v___y_2267_ = v___y_2279_;
v___y_2268_ = v___x_2281_;
v___y_2269_ = v___x_2283_;
v___y_2270_ = v___y_2280_;
v___y_2271_ = v___x_2284_;
goto v___jp_2262_;
}
else
{
v___y_2263_ = v___y_2275_;
v___y_2264_ = v___y_2276_;
v___y_2265_ = v___y_2277_;
v___y_2266_ = v___y_2278_;
v___y_2267_ = v___y_2279_;
v___y_2268_ = v___x_2281_;
v___y_2269_ = v___x_2283_;
v___y_2270_ = v___y_2280_;
v___y_2271_ = v___y_2276_;
goto v___jp_2262_;
}
}
else
{
if (v___y_2278_ == 0)
{
uint32_t v___x_2286_; 
v___x_2286_ = 0;
return v___x_2286_;
}
else
{
uint32_t v___x_2287_; 
v___x_2287_ = 2147483648;
return v___x_2287_;
}
}
}
v___jp_2288_:
{
uint32_t v___x_2292_; uint32_t v___x_2293_; 
v___x_2292_ = lean_uint32_land(v___y_2290_, v___y_2289_);
v___x_2293_ = lean_uint32_lor(v___y_2291_, v___x_2292_);
return v___x_2293_;
}
v___jp_2294_:
{
uint8_t v___x_2299_; 
v___x_2299_ = lean_uint64_dec_eq(v___y_2298_, v___y_2297_);
if (v___x_2299_ == 0)
{
uint64_t v___x_2300_; uint8_t v___x_2301_; 
v___x_2300_ = 8388608ULL;
v___x_2301_ = lean_uint64_dec_eq(v___y_2298_, v___x_2300_);
if (v___x_2301_ == 0)
{
uint32_t v___x_2302_; 
v___x_2302_ = lean_uint64_to_uint32(v___y_2298_);
if (v___y_2296_ == 0)
{
uint32_t v___x_2303_; 
v___x_2303_ = 0;
v___y_2289_ = v___y_2295_;
v___y_2290_ = v___x_2302_;
v___y_2291_ = v___x_2303_;
goto v___jp_2288_;
}
else
{
uint32_t v___x_2304_; 
v___x_2304_ = 2147483648;
v___y_2289_ = v___y_2295_;
v___y_2290_ = v___x_2302_;
v___y_2291_ = v___x_2304_;
goto v___jp_2288_;
}
}
else
{
if (v___y_2296_ == 0)
{
uint32_t v___x_2305_; 
v___x_2305_ = 0;
v___y_1526_ = v___x_2305_;
goto v___jp_1525_;
}
else
{
uint32_t v___x_2306_; 
v___x_2306_ = 2147483648;
v___y_1526_ = v___x_2306_;
goto v___jp_1525_;
}
}
}
else
{
if (v___y_2296_ == 0)
{
uint32_t v___x_2307_; 
v___x_2307_ = 0;
return v___x_2307_;
}
else
{
uint32_t v___x_2308_; 
v___x_2308_ = 2147483648;
return v___x_2308_;
}
}
}
v___jp_2309_:
{
uint64_t v___x_2318_; uint64_t v___x_2319_; uint64_t v___x_2320_; uint8_t v___x_2321_; 
v___x_2318_ = lean_uint64_mul(v___y_2310_, v___y_2314_);
v___x_2319_ = lean_uint64_add(v___y_2316_, v___y_2317_);
v___x_2320_ = 281474976710656ULL;
v___x_2321_ = lean_uint64_dec_lt(v___x_2318_, v___x_2320_);
if (v___x_2321_ == 0)
{
v___y_2275_ = v___y_2311_;
v___y_2276_ = v___x_2318_;
v___y_2277_ = v___y_2312_;
v___y_2278_ = v___y_2313_;
v___y_2279_ = v___x_2319_;
v___y_2280_ = v___y_2315_;
goto v___jp_2274_;
}
else
{
uint64_t v___x_2322_; uint8_t v___x_2323_; 
v___x_2322_ = 123ULL;
v___x_2323_ = lean_uint64_dec_le(v___x_2319_, v___x_2322_);
if (v___x_2323_ == 0)
{
v___y_2275_ = v___y_2311_;
v___y_2276_ = v___x_2318_;
v___y_2277_ = v___y_2312_;
v___y_2278_ = v___y_2313_;
v___y_2279_ = v___x_2319_;
v___y_2280_ = v___y_2315_;
goto v___jp_2274_;
}
else
{
uint64_t v___x_2324_; uint8_t v___x_2325_; 
v___x_2324_ = 0ULL;
v___x_2325_ = lean_uint64_dec_eq(v___x_2318_, v___x_2324_);
if (v___x_2325_ == 0)
{
uint64_t v___x_2326_; uint64_t v___x_2327_; uint8_t v___x_2328_; 
v___x_2326_ = 149ULL;
v___x_2327_ = lean_uint64_sub(v___x_2326_, v___x_2319_);
v___x_2328_ = lean_uint64_dec_eq(v___x_2327_, v___x_2324_);
if (v___x_2328_ == 0)
{
uint64_t v___x_2329_; uint8_t v___x_2330_; 
v___x_2329_ = 64ULL;
v___x_2330_ = lean_uint64_dec_lt(v___x_2327_, v___x_2329_);
if (v___x_2330_ == 0)
{
uint8_t v___x_2331_; 
v___x_2331_ = lean_uint64_dec_eq(v___x_2327_, v___x_2329_);
if (v___x_2331_ == 0)
{
v___y_2295_ = v___y_2312_;
v___y_2296_ = v___y_2313_;
v___y_2297_ = v___x_2324_;
v___y_2298_ = v___x_2324_;
goto v___jp_2294_;
}
else
{
uint64_t v___x_2332_; uint8_t v___x_2333_; 
v___x_2332_ = 9223372036854775808ULL;
v___x_2333_ = lean_uint64_dec_lt(v___x_2332_, v___x_2318_);
if (v___x_2333_ == 0)
{
v___y_2295_ = v___y_2312_;
v___y_2296_ = v___y_2313_;
v___y_2297_ = v___x_2324_;
v___y_2298_ = v___x_2324_;
goto v___jp_2294_;
}
else
{
uint64_t v___x_2334_; 
v___x_2334_ = 1ULL;
v___y_2295_ = v___y_2312_;
v___y_2296_ = v___y_2313_;
v___y_2297_ = v___x_2324_;
v___y_2298_ = v___x_2334_;
goto v___jp_2294_;
}
}
}
else
{
uint64_t v_quotient_2335_; uint64_t v___x_2336_; uint64_t v___x_2337_; uint64_t v___x_2338_; uint64_t v_remainder_2339_; uint64_t v___x_2340_; uint64_t v_half_2341_; uint8_t v___x_2342_; 
v_quotient_2335_ = lean_uint64_shift_right(v___x_2318_, v___x_2327_);
v___x_2336_ = 1ULL;
v___x_2337_ = lean_uint64_shift_left(v___x_2336_, v___x_2327_);
v___x_2338_ = lean_uint64_sub(v___x_2337_, v___x_2336_);
v_remainder_2339_ = lean_uint64_land(v___x_2318_, v___x_2338_);
v___x_2340_ = lean_uint64_sub(v___x_2327_, v___x_2336_);
v_half_2341_ = lean_uint64_shift_left(v___x_2336_, v___x_2340_);
v___x_2342_ = lean_uint64_dec_lt(v_remainder_2339_, v_half_2341_);
if (v___x_2342_ == 0)
{
uint8_t v___x_2343_; 
v___x_2343_ = lean_uint64_dec_lt(v_half_2341_, v_remainder_2339_);
if (v___x_2343_ == 0)
{
uint64_t v___x_2344_; uint8_t v___x_2345_; 
v___x_2344_ = lean_uint64_land(v_quotient_2335_, v___x_2336_);
v___x_2345_ = lean_uint64_dec_eq(v___x_2344_, v___x_2324_);
if (v___x_2345_ == 0)
{
uint64_t v___x_2346_; 
v___x_2346_ = lean_uint64_add(v_quotient_2335_, v___x_2336_);
v___y_2295_ = v___y_2312_;
v___y_2296_ = v___y_2313_;
v___y_2297_ = v___x_2324_;
v___y_2298_ = v___x_2346_;
goto v___jp_2294_;
}
else
{
v___y_2295_ = v___y_2312_;
v___y_2296_ = v___y_2313_;
v___y_2297_ = v___x_2324_;
v___y_2298_ = v_quotient_2335_;
goto v___jp_2294_;
}
}
else
{
uint64_t v___x_2347_; 
v___x_2347_ = lean_uint64_add(v_quotient_2335_, v___x_2336_);
v___y_2295_ = v___y_2312_;
v___y_2296_ = v___y_2313_;
v___y_2297_ = v___x_2324_;
v___y_2298_ = v___x_2347_;
goto v___jp_2294_;
}
}
else
{
v___y_2295_ = v___y_2312_;
v___y_2296_ = v___y_2313_;
v___y_2297_ = v___x_2324_;
v___y_2298_ = v_quotient_2335_;
goto v___jp_2294_;
}
}
}
else
{
v___y_2295_ = v___y_2312_;
v___y_2296_ = v___y_2313_;
v___y_2297_ = v___x_2324_;
v___y_2298_ = v___x_2318_;
goto v___jp_2294_;
}
}
else
{
if (v___y_2313_ == 0)
{
uint32_t v___x_2348_; 
v___x_2348_ = 0;
return v___x_2348_;
}
else
{
uint32_t v___x_2349_; 
v___x_2349_ = 2147483648;
return v___x_2349_;
}
}
}
}
}
v___jp_2350_:
{
uint64_t v___x_2359_; uint64_t v___x_2360_; uint8_t v___x_2361_; 
v___x_2359_ = lean_uint32_to_uint64(v___y_2357_);
v___x_2360_ = 0ULL;
v___x_2361_ = lean_uint64_dec_eq(v___x_2359_, v___x_2360_);
if (v___x_2361_ == 0)
{
uint64_t v___x_2362_; uint64_t v___x_2363_; 
v___x_2362_ = 1ULL;
v___x_2363_ = lean_uint64_sub(v___x_2359_, v___x_2362_);
v___y_2310_ = v___y_2351_;
v___y_2311_ = v___y_2352_;
v___y_2312_ = v___y_2353_;
v___y_2313_ = v___y_2354_;
v___y_2314_ = v___y_2355_;
v___y_2315_ = v___y_2356_;
v___y_2316_ = v___y_2358_;
v___y_2317_ = v___x_2363_;
goto v___jp_2309_;
}
else
{
v___y_2310_ = v___y_2351_;
v___y_2311_ = v___y_2352_;
v___y_2312_ = v___y_2353_;
v___y_2313_ = v___y_2354_;
v___y_2314_ = v___y_2355_;
v___y_2315_ = v___y_2356_;
v___y_2316_ = v___y_2358_;
v___y_2317_ = v___x_2360_;
goto v___jp_2309_;
}
}
v___jp_2364_:
{
uint64_t v___x_2373_; uint64_t v___x_2374_; uint8_t v___x_2375_; 
v___x_2373_ = lean_uint32_to_uint64(v___y_2370_);
v___x_2374_ = 0ULL;
v___x_2375_ = lean_uint64_dec_eq(v___x_2373_, v___x_2374_);
if (v___x_2375_ == 0)
{
uint64_t v___x_2376_; uint64_t v___x_2377_; 
v___x_2376_ = 1ULL;
v___x_2377_ = lean_uint64_sub(v___x_2373_, v___x_2376_);
v___y_2351_ = v___y_2365_;
v___y_2352_ = v___y_2366_;
v___y_2353_ = v___y_2367_;
v___y_2354_ = v___y_2368_;
v___y_2355_ = v___y_2372_;
v___y_2356_ = v___y_2369_;
v___y_2357_ = v___y_2371_;
v___y_2358_ = v___x_2377_;
goto v___jp_2350_;
}
else
{
v___y_2351_ = v___y_2365_;
v___y_2352_ = v___y_2366_;
v___y_2353_ = v___y_2367_;
v___y_2354_ = v___y_2368_;
v___y_2355_ = v___y_2372_;
v___y_2356_ = v___y_2369_;
v___y_2357_ = v___y_2371_;
v___y_2358_ = v___x_2374_;
goto v___jp_2350_;
}
}
v___jp_2378_:
{
uint32_t v___x_2387_; uint8_t v___x_2388_; 
v___x_2387_ = 0;
v___x_2388_ = lean_uint32_dec_eq(v___y_2384_, v___x_2387_);
if (v___x_2388_ == 0)
{
uint64_t v___x_2389_; uint64_t v___x_2390_; uint64_t v___x_2391_; 
v___x_2389_ = lean_uint32_to_uint64(v___y_2379_);
v___x_2390_ = 8388608ULL;
v___x_2391_ = lean_uint64_lor(v___x_2389_, v___x_2390_);
v___y_2365_ = v___y_2386_;
v___y_2366_ = v___y_2380_;
v___y_2367_ = v___y_2381_;
v___y_2368_ = v___y_2382_;
v___y_2369_ = v___y_2383_;
v___y_2370_ = v___y_2385_;
v___y_2371_ = v___y_2384_;
v___y_2372_ = v___x_2391_;
goto v___jp_2364_;
}
else
{
uint64_t v___x_2392_; 
v___x_2392_ = lean_uint32_to_uint64(v___y_2379_);
v___y_2365_ = v___y_2386_;
v___y_2366_ = v___y_2380_;
v___y_2367_ = v___y_2381_;
v___y_2368_ = v___y_2382_;
v___y_2369_ = v___y_2383_;
v___y_2370_ = v___y_2385_;
v___y_2371_ = v___y_2384_;
v___y_2372_ = v___x_2392_;
goto v___jp_2364_;
}
}
v___jp_2393_:
{
uint32_t v___x_2399_; uint32_t v_xFraction_2400_; uint32_t v_yFraction_2401_; uint32_t v___x_2402_; uint8_t v___x_2403_; 
v___x_2399_ = 8388607;
v_xFraction_2400_ = lean_uint32_land(v___y_1519_, v___x_2399_);
v_yFraction_2401_ = lean_uint32_land(v___y_1520_, v___x_2399_);
v___x_2402_ = 0;
v___x_2403_ = lean_uint32_dec_eq(v___y_2396_, v___x_2402_);
if (v___x_2403_ == 0)
{
uint64_t v___x_2404_; uint64_t v___x_2405_; uint64_t v___x_2406_; 
v___x_2404_ = lean_uint32_to_uint64(v_xFraction_2400_);
v___x_2405_ = 8388608ULL;
v___x_2406_ = lean_uint64_lor(v___x_2404_, v___x_2405_);
v___y_2379_ = v_yFraction_2401_;
v___y_2380_ = v___y_2394_;
v___y_2381_ = v___x_2399_;
v___y_2382_ = v___y_2398_;
v___y_2383_ = v___y_2395_;
v___y_2384_ = v___y_2397_;
v___y_2385_ = v___y_2396_;
v___y_2386_ = v___x_2406_;
goto v___jp_2378_;
}
else
{
uint64_t v___x_2407_; 
v___x_2407_ = lean_uint32_to_uint64(v_xFraction_2400_);
v___y_2379_ = v_yFraction_2401_;
v___y_2380_ = v___y_2394_;
v___y_2381_ = v___x_2399_;
v___y_2382_ = v___y_2398_;
v___y_2383_ = v___y_2395_;
v___y_2384_ = v___y_2397_;
v___y_2385_ = v___y_2396_;
v___y_2386_ = v___x_2407_;
goto v___jp_2378_;
}
}
v___jp_2408_:
{
if (v___y_2411_ == 0)
{
if (v___y_2416_ == 0)
{
v___y_2394_ = v___y_2410_;
v___y_2395_ = v___y_2412_;
v___y_2396_ = v___y_2415_;
v___y_2397_ = v___y_2414_;
v___y_2398_ = v___y_2413_;
goto v___jp_2393_;
}
else
{
v___y_2394_ = v___y_2410_;
v___y_2395_ = v___y_2412_;
v___y_2396_ = v___y_2415_;
v___y_2397_ = v___y_2414_;
v___y_2398_ = v___y_2409_;
goto v___jp_2393_;
}
}
else
{
if (v___y_2416_ == 0)
{
v___y_2394_ = v___y_2410_;
v___y_2395_ = v___y_2412_;
v___y_2396_ = v___y_2415_;
v___y_2397_ = v___y_2414_;
v___y_2398_ = v___y_2409_;
goto v___jp_2393_;
}
else
{
v___y_2394_ = v___y_2410_;
v___y_2395_ = v___y_2412_;
v___y_2396_ = v___y_2415_;
v___y_2397_ = v___y_2414_;
v___y_2398_ = v___y_2413_;
goto v___jp_2393_;
}
}
}
v___jp_2417_:
{
uint32_t v___x_2425_; uint32_t v___x_2426_; uint32_t v___x_2427_; uint8_t v___x_2428_; 
v___x_2425_ = 2147483648;
v___x_2426_ = lean_uint32_land(v___y_1520_, v___x_2425_);
v___x_2427_ = 0;
v___x_2428_ = lean_uint32_dec_eq(v___x_2426_, v___x_2427_);
if (v___x_2428_ == 0)
{
v___y_2409_ = v___y_2418_;
v___y_2410_ = v___y_2419_;
v___y_2411_ = v___y_2424_;
v___y_2412_ = v___y_2421_;
v___y_2413_ = v___y_2420_;
v___y_2414_ = v___y_2423_;
v___y_2415_ = v___y_2422_;
v___y_2416_ = v___y_2418_;
goto v___jp_2408_;
}
else
{
v___y_2409_ = v___y_2418_;
v___y_2410_ = v___y_2419_;
v___y_2411_ = v___y_2424_;
v___y_2412_ = v___y_2421_;
v___y_2413_ = v___y_2420_;
v___y_2414_ = v___y_2423_;
v___y_2415_ = v___y_2422_;
v___y_2416_ = v___y_2420_;
goto v___jp_2408_;
}
}
v___jp_2429_:
{
if (v___y_2435_ == 0)
{
uint32_t v___x_2436_; uint32_t v___x_2437_; uint32_t v___x_2438_; uint8_t v___x_2439_; 
v___x_2436_ = 2147483648;
v___x_2437_ = lean_uint32_land(v___y_1519_, v___x_2436_);
v___x_2438_ = 0;
v___x_2439_ = lean_uint32_dec_eq(v___x_2437_, v___x_2438_);
if (v___x_2439_ == 0)
{
v___y_2418_ = v___y_2430_;
v___y_2419_ = v___y_2431_;
v___y_2420_ = v___y_2435_;
v___y_2421_ = v___y_2432_;
v___y_2422_ = v___y_2434_;
v___y_2423_ = v___y_2433_;
v___y_2424_ = v___y_2430_;
goto v___jp_2417_;
}
else
{
v___y_2418_ = v___y_2430_;
v___y_2419_ = v___y_2431_;
v___y_2420_ = v___y_2435_;
v___y_2421_ = v___y_2432_;
v___y_2422_ = v___y_2434_;
v___y_2423_ = v___y_2433_;
v___y_2424_ = v___y_2435_;
goto v___jp_2417_;
}
}
else
{
lean_object* v___x_2440_; lean_object* v___x_2441_; lean_object* v___x_2442_; uint32_t v___x_2443_; 
v___x_2440_ = lean_uint32_to_nat(v___y_1519_);
v___x_2441_ = lean_uint32_to_nat(v___y_1520_);
v___x_2442_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2440_, v___x_2441_);
v___x_2443_ = lean_uint32_of_nat(v___x_2442_);
lean_dec(v___x_2442_);
return v___x_2443_;
}
}
v___jp_2444_:
{
uint32_t v___x_2450_; uint32_t v___x_2451_; uint32_t v___x_2452_; uint32_t v___x_2453_; uint64_t v___x_2454_; uint32_t v___x_2455_; uint32_t v___x_2456_; uint64_t v___x_2457_; uint64_t v___x_2458_; uint64_t v___x_2459_; uint64_t v_high_2460_; uint64_t v___x_2461_; uint64_t v_carry_2462_; uint32_t v___x_2463_; uint8_t v___x_2464_; uint8_t v___x_2465_; 
v___x_2450_ = 8388607;
v___x_2451_ = lean_uint32_land(v___y_1519_, v___x_2450_);
v___x_2452_ = 8388608;
v___x_2453_ = lean_uint32_lor(v___x_2451_, v___x_2452_);
v___x_2454_ = lean_uint32_to_uint64(v___x_2453_);
v___x_2455_ = lean_uint32_land(v___y_1520_, v___x_2450_);
v___x_2456_ = lean_uint32_lor(v___x_2455_, v___x_2452_);
v___x_2457_ = lean_uint32_to_uint64(v___x_2456_);
v___x_2458_ = lean_uint64_mul(v___x_2454_, v___x_2457_);
v___x_2459_ = 47ULL;
v_high_2460_ = lean_uint64_shift_right(v___x_2458_, v___x_2459_);
v___x_2461_ = 24ULL;
v_carry_2462_ = lean_uint64_shift_right(v___y_2449_, v___x_2461_);
v___x_2463_ = 2147483648;
v___x_2464_ = lean_uint32_dec_le(v___x_2463_, v___y_1519_);
v___x_2465_ = lean_uint32_dec_le(v___x_2463_, v___y_1520_);
if (v___x_2464_ == 0)
{
if (v___x_2465_ == 0)
{
v___y_1972_ = v___y_2445_;
v___y_1973_ = v___y_2446_;
v___y_1974_ = v_carry_2462_;
v___y_1975_ = v_high_2460_;
v___y_1976_ = v___y_2449_;
v___y_1977_ = v___x_2450_;
v___y_1978_ = v___y_2447_;
goto v___jp_1971_;
}
else
{
v___y_1981_ = v___y_2445_;
v___y_1982_ = v___y_2446_;
v___y_1983_ = v_carry_2462_;
v___y_1984_ = v_high_2460_;
v___y_1985_ = v___y_2449_;
v___y_1986_ = v___x_2450_;
v___y_1987_ = v___y_2447_;
v___y_1988_ = v___y_2448_;
v___y_1989_ = v___x_2464_;
goto v___jp_1980_;
}
}
else
{
v___y_1981_ = v___y_2445_;
v___y_1982_ = v___y_2446_;
v___y_1983_ = v_carry_2462_;
v___y_1984_ = v_high_2460_;
v___y_1985_ = v___y_2449_;
v___y_1986_ = v___x_2450_;
v___y_1987_ = v___y_2447_;
v___y_1988_ = v___y_2448_;
v___y_1989_ = v___x_2465_;
goto v___jp_1980_;
}
}
v___jp_2466_:
{
uint64_t v___x_2475_; uint64_t v___x_2476_; uint64_t v___x_2477_; 
v___x_2475_ = lean_uint64_lor(v___y_2470_, v___y_2474_);
v___x_2476_ = lean_uint64_land(v___y_2469_, v___x_2475_);
v___x_2477_ = lean_uint64_add(v___y_2472_, v___x_2476_);
v___y_2445_ = v___y_2467_;
v___y_2446_ = v___y_2468_;
v___y_2447_ = v___y_2471_;
v___y_2448_ = v___y_2473_;
v___y_2449_ = v___x_2477_;
goto v___jp_2444_;
}
v___jp_2478_:
{
uint64_t v___x_2487_; uint64_t v___x_2488_; uint8_t v___x_2489_; 
v___x_2487_ = lean_uint64_land(v___y_2483_, v___y_2482_);
v___x_2488_ = 0ULL;
v___x_2489_ = lean_uint64_dec_eq(v___x_2487_, v___x_2488_);
if (v___x_2489_ == 0)
{
v___y_2467_ = v___y_2479_;
v___y_2468_ = v___y_2480_;
v___y_2469_ = v___y_2481_;
v___y_2470_ = v___y_2486_;
v___y_2471_ = v___y_2484_;
v___y_2472_ = v___y_2483_;
v___y_2473_ = v___y_2485_;
v___y_2474_ = v___y_2482_;
goto v___jp_2466_;
}
else
{
v___y_2467_ = v___y_2479_;
v___y_2468_ = v___y_2480_;
v___y_2469_ = v___y_2481_;
v___y_2470_ = v___y_2486_;
v___y_2471_ = v___y_2484_;
v___y_2472_ = v___y_2483_;
v___y_2473_ = v___y_2485_;
v___y_2474_ = v___x_2488_;
goto v___jp_2466_;
}
}
v___jp_2490_:
{
if (v___y_2491_ == 0)
{
uint64_t v___x_2499_; 
v___x_2499_ = 0ULL;
v___y_2479_ = v___y_2492_;
v___y_2480_ = v___y_2493_;
v___y_2481_ = v___y_2498_;
v___y_2482_ = v___y_2494_;
v___y_2483_ = v___y_2496_;
v___y_2484_ = v___y_2495_;
v___y_2485_ = v___y_2497_;
v___y_2486_ = v___x_2499_;
goto v___jp_2478_;
}
else
{
v___y_2479_ = v___y_2492_;
v___y_2480_ = v___y_2493_;
v___y_2481_ = v___y_2498_;
v___y_2482_ = v___y_2494_;
v___y_2483_ = v___y_2496_;
v___y_2484_ = v___y_2495_;
v___y_2485_ = v___y_2497_;
v___y_2486_ = v___y_2494_;
goto v___jp_2478_;
}
}
v___jp_2500_:
{
uint64_t v___x_2509_; uint64_t v___x_2510_; uint64_t v___x_2511_; 
v___x_2509_ = lean_uint64_lor(v___y_2502_, v___y_2508_);
v___x_2510_ = lean_uint64_land(v___y_2501_, v___x_2509_);
v___x_2511_ = lean_uint64_add(v___y_2505_, v___x_2510_);
v___y_2445_ = v___y_2503_;
v___y_2446_ = v___y_2504_;
v___y_2447_ = v___y_2506_;
v___y_2448_ = v___y_2507_;
v___y_2449_ = v___x_2511_;
goto v___jp_2444_;
}
v___jp_2512_:
{
uint64_t v___x_2521_; uint64_t v___x_2522_; uint8_t v___x_2523_; 
v___x_2521_ = lean_uint64_land(v___y_2517_, v___y_2513_);
v___x_2522_ = 0ULL;
v___x_2523_ = lean_uint64_dec_eq(v___x_2521_, v___x_2522_);
if (v___x_2523_ == 0)
{
v___y_2501_ = v___y_2514_;
v___y_2502_ = v___y_2520_;
v___y_2503_ = v___y_2515_;
v___y_2504_ = v___y_2516_;
v___y_2505_ = v___y_2517_;
v___y_2506_ = v___y_2518_;
v___y_2507_ = v___y_2519_;
v___y_2508_ = v___y_2513_;
goto v___jp_2500_;
}
else
{
v___y_2501_ = v___y_2514_;
v___y_2502_ = v___y_2520_;
v___y_2503_ = v___y_2515_;
v___y_2504_ = v___y_2516_;
v___y_2505_ = v___y_2517_;
v___y_2506_ = v___y_2518_;
v___y_2507_ = v___y_2519_;
v___y_2508_ = v___x_2522_;
goto v___jp_2500_;
}
}
v___jp_2524_:
{
if (v___y_2526_ == 0)
{
uint64_t v___x_2533_; 
v___x_2533_ = 0ULL;
v___y_2513_ = v___y_2525_;
v___y_2514_ = v___y_2532_;
v___y_2515_ = v___y_2527_;
v___y_2516_ = v___y_2528_;
v___y_2517_ = v___y_2529_;
v___y_2518_ = v___y_2530_;
v___y_2519_ = v___y_2531_;
v___y_2520_ = v___x_2533_;
goto v___jp_2512_;
}
else
{
v___y_2513_ = v___y_2525_;
v___y_2514_ = v___y_2532_;
v___y_2515_ = v___y_2527_;
v___y_2516_ = v___y_2528_;
v___y_2517_ = v___y_2529_;
v___y_2518_ = v___y_2530_;
v___y_2519_ = v___y_2531_;
v___y_2520_ = v___y_2525_;
goto v___jp_2512_;
}
}
v___jp_2534_:
{
uint32_t v___x_2540_; uint32_t v_xFraction_2541_; uint32_t v_yFraction_2542_; uint32_t v___x_2543_; uint8_t v___x_2544_; 
v___x_2540_ = 8388607;
v_xFraction_2541_ = lean_uint32_land(v___y_1519_, v___x_2540_);
v_yFraction_2542_ = lean_uint32_land(v___y_1520_, v___x_2540_);
v___x_2543_ = 0;
v___x_2544_ = lean_uint32_dec_eq(v___y_2537_, v___x_2543_);
if (v___x_2544_ == 0)
{
uint64_t v___x_2545_; uint64_t v___x_2546_; uint64_t v___x_2547_; 
v___x_2545_ = lean_uint32_to_uint64(v_xFraction_2541_);
v___x_2546_ = 8388608ULL;
v___x_2547_ = lean_uint64_lor(v___x_2545_, v___x_2546_);
v___y_1926_ = v___y_2535_;
v___y_1927_ = v___y_2536_;
v___y_1928_ = v___x_2540_;
v___y_1929_ = v___y_2537_;
v___y_1930_ = v_yFraction_2542_;
v___y_1931_ = v___y_2539_;
v___y_1932_ = v___y_2538_;
v___y_1933_ = v___x_2547_;
goto v___jp_1925_;
}
else
{
uint64_t v___x_2548_; 
v___x_2548_ = lean_uint32_to_uint64(v_xFraction_2541_);
v___y_1926_ = v___y_2535_;
v___y_1927_ = v___y_2536_;
v___y_1928_ = v___x_2540_;
v___y_1929_ = v___y_2537_;
v___y_1930_ = v_yFraction_2542_;
v___y_1931_ = v___y_2539_;
v___y_1932_ = v___y_2538_;
v___y_1933_ = v___x_2548_;
goto v___jp_1925_;
}
}
v___jp_2549_:
{
uint8_t v___x_2554_; 
v___x_2554_ = 1;
v___y_2535_ = v___y_2550_;
v___y_2536_ = v___y_2551_;
v___y_2537_ = v___y_2552_;
v___y_2538_ = v___y_2553_;
v___y_2539_ = v___x_2554_;
goto v___jp_2534_;
}
v___jp_2555_:
{
if (v___y_2560_ == 0)
{
if (v___y_2562_ == 0)
{
v___y_2535_ = v___y_2556_;
v___y_2536_ = v___y_2557_;
v___y_2537_ = v___y_2559_;
v___y_2538_ = v___y_2561_;
v___y_2539_ = v___y_2558_;
goto v___jp_2534_;
}
else
{
v___y_2550_ = v___y_2556_;
v___y_2551_ = v___y_2557_;
v___y_2552_ = v___y_2559_;
v___y_2553_ = v___y_2561_;
goto v___jp_2549_;
}
}
else
{
if (v___y_2562_ == 0)
{
v___y_2550_ = v___y_2556_;
v___y_2551_ = v___y_2557_;
v___y_2552_ = v___y_2559_;
v___y_2553_ = v___y_2561_;
goto v___jp_2549_;
}
else
{
v___y_2535_ = v___y_2556_;
v___y_2536_ = v___y_2557_;
v___y_2537_ = v___y_2559_;
v___y_2538_ = v___y_2561_;
v___y_2539_ = v___y_2558_;
goto v___jp_2534_;
}
}
}
v___jp_2563_:
{
uint32_t v___x_2570_; uint32_t v___x_2571_; uint32_t v___x_2572_; uint8_t v___x_2573_; 
v___x_2570_ = 2147483648;
v___x_2571_ = lean_uint32_land(v___y_1520_, v___x_2570_);
v___x_2572_ = 0;
v___x_2573_ = lean_uint32_dec_eq(v___x_2571_, v___x_2572_);
if (v___x_2573_ == 0)
{
uint8_t v___x_2574_; 
v___x_2574_ = 1;
v___y_2556_ = v___y_2564_;
v___y_2557_ = v___y_2566_;
v___y_2558_ = v___y_2565_;
v___y_2559_ = v___y_2567_;
v___y_2560_ = v___y_2569_;
v___y_2561_ = v___y_2568_;
v___y_2562_ = v___x_2574_;
goto v___jp_2555_;
}
else
{
v___y_2556_ = v___y_2564_;
v___y_2557_ = v___y_2566_;
v___y_2558_ = v___y_2565_;
v___y_2559_ = v___y_2567_;
v___y_2560_ = v___y_2569_;
v___y_2561_ = v___y_2568_;
v___y_2562_ = v___y_2565_;
goto v___jp_2555_;
}
}
v___jp_2575_:
{
if (v___y_2580_ == 0)
{
uint32_t v___x_2581_; uint32_t v___x_2582_; uint32_t v___x_2583_; uint8_t v___x_2584_; 
v___x_2581_ = 2147483648;
v___x_2582_ = lean_uint32_land(v___y_1519_, v___x_2581_);
v___x_2583_ = 0;
v___x_2584_ = lean_uint32_dec_eq(v___x_2582_, v___x_2583_);
if (v___x_2584_ == 0)
{
uint8_t v___x_2585_; 
v___x_2585_ = 1;
v___y_2564_ = v___y_2576_;
v___y_2565_ = v___y_2580_;
v___y_2566_ = v___y_2577_;
v___y_2567_ = v___y_2578_;
v___y_2568_ = v___y_2579_;
v___y_2569_ = v___x_2585_;
goto v___jp_2563_;
}
else
{
v___y_2564_ = v___y_2576_;
v___y_2565_ = v___y_2580_;
v___y_2566_ = v___y_2577_;
v___y_2567_ = v___y_2578_;
v___y_2568_ = v___y_2579_;
v___y_2569_ = v___y_2580_;
goto v___jp_2563_;
}
}
else
{
lean_object* v___x_2586_; lean_object* v___x_2587_; lean_object* v___x_2588_; uint32_t v___x_2589_; 
v___x_2586_ = lean_uint32_to_nat(v___y_1519_);
v___x_2587_ = lean_uint32_to_nat(v___y_1520_);
v___x_2588_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2586_, v___x_2587_);
v___x_2589_ = lean_uint32_of_nat(v___x_2588_);
lean_dec(v___x_2588_);
return v___x_2589_;
}
}
v___jp_2590_:
{
if (v___y_2591_ == 0)
{
uint32_t v___x_2592_; 
v___x_2592_ = lp_competition_Submission_FastMul_mul(v___y_1519_, v___y_1520_);
return v___x_2592_;
}
else
{
uint32_t v___x_2593_; uint32_t v___x_2594_; 
v___x_2593_ = 4194304;
v___x_2594_ = lean_uint32_lor(v___y_1520_, v___x_2593_);
return v___x_2594_;
}
}
v___jp_2595_:
{
uint32_t v___x_2596_; uint32_t v___x_2597_; uint32_t v___x_2598_; uint32_t v___x_2599_; uint8_t v___x_2600_; 
v___x_2596_ = 23;
v___x_2597_ = lean_uint32_shift_right(v___y_1520_, v___x_2596_);
v___x_2598_ = 255;
v___x_2599_ = lean_uint32_land(v___x_2597_, v___x_2598_);
v___x_2600_ = lean_uint32_dec_eq(v___x_2599_, v___x_2598_);
if (v___x_2600_ == 0)
{
v___y_2591_ = v___x_2600_;
goto v___jp_2590_;
}
else
{
uint32_t v___x_2601_; uint32_t v___x_2602_; uint32_t v___x_2603_; uint8_t v___x_2604_; 
v___x_2601_ = 8388607;
v___x_2602_ = lean_uint32_land(v___y_1520_, v___x_2601_);
v___x_2603_ = 0;
v___x_2604_ = lean_uint32_dec_eq(v___x_2602_, v___x_2603_);
if (v___x_2604_ == 0)
{
v___y_2591_ = v___x_2600_;
goto v___jp_2590_;
}
else
{
uint32_t v___x_2605_; 
v___x_2605_ = lp_competition_Submission_FastMul_mul(v___y_1519_, v___y_1520_);
return v___x_2605_;
}
}
}
v___jp_2606_:
{
if (v___y_2607_ == 0)
{
goto v___jp_2595_;
}
else
{
uint32_t v___x_2608_; uint32_t v___x_2609_; 
v___x_2608_ = 4194304;
v___x_2609_ = lean_uint32_lor(v___y_1519_, v___x_2608_);
return v___x_2609_;
}
}
v___jp_2610_:
{
uint32_t v___x_2611_; uint32_t v___x_2612_; uint32_t v___x_2613_; uint32_t v___x_2614_; uint8_t v___x_2615_; 
v___x_2611_ = 23;
v___x_2612_ = lean_uint32_shift_right(v___y_1519_, v___x_2611_);
v___x_2613_ = 255;
v___x_2614_ = lean_uint32_land(v___x_2612_, v___x_2613_);
v___x_2615_ = lean_uint32_dec_eq(v___x_2614_, v___x_2613_);
if (v___x_2615_ == 0)
{
v___y_2607_ = v___x_2615_;
goto v___jp_2606_;
}
else
{
uint32_t v___x_2616_; uint32_t v___x_2617_; uint32_t v___x_2618_; uint8_t v___x_2619_; 
v___x_2616_ = 8388607;
v___x_2617_ = lean_uint32_land(v___y_1519_, v___x_2616_);
v___x_2618_ = 0;
v___x_2619_ = lean_uint32_dec_eq(v___x_2617_, v___x_2618_);
if (v___x_2619_ == 0)
{
v___y_2607_ = v___x_2615_;
goto v___jp_2606_;
}
else
{
goto v___jp_2595_;
}
}
}
v___jp_2620_:
{
if (v___y_2621_ == 0)
{
goto v___jp_2610_;
}
else
{
uint32_t v___x_2622_; uint32_t v___x_2623_; uint32_t v___x_2624_; uint8_t v___x_2625_; 
v___x_2622_ = 4194304;
v___x_2623_ = lean_uint32_land(v___y_1520_, v___x_2622_);
v___x_2624_ = 0;
v___x_2625_ = lean_uint32_dec_eq(v___x_2623_, v___x_2624_);
if (v___x_2625_ == 0)
{
goto v___jp_2610_;
}
else
{
uint32_t v___x_2626_; 
v___x_2626_ = lean_uint32_lor(v___y_1520_, v___x_2622_);
return v___x_2626_;
}
}
}
v___jp_2627_:
{
uint32_t v___x_2628_; uint32_t v___x_2629_; uint32_t v___x_2630_; uint32_t v___x_2631_; uint8_t v___x_2632_; 
v___x_2628_ = 23;
v___x_2629_ = lean_uint32_shift_right(v___y_1520_, v___x_2628_);
v___x_2630_ = 255;
v___x_2631_ = lean_uint32_land(v___x_2629_, v___x_2630_);
v___x_2632_ = lean_uint32_dec_eq(v___x_2631_, v___x_2630_);
if (v___x_2632_ == 0)
{
v___y_2621_ = v___x_2632_;
goto v___jp_2620_;
}
else
{
uint32_t v___x_2633_; uint32_t v___x_2634_; uint32_t v___x_2635_; uint8_t v___x_2636_; 
v___x_2633_ = 8388607;
v___x_2634_ = lean_uint32_land(v___y_1520_, v___x_2633_);
v___x_2635_ = 0;
v___x_2636_ = lean_uint32_dec_eq(v___x_2634_, v___x_2635_);
if (v___x_2636_ == 0)
{
v___y_2621_ = v___x_2632_;
goto v___jp_2620_;
}
else
{
goto v___jp_2610_;
}
}
}
v___jp_2637_:
{
if (v___y_2638_ == 0)
{
goto v___jp_2627_;
}
else
{
uint32_t v___x_2639_; uint32_t v___x_2640_; uint32_t v___x_2641_; uint8_t v___x_2642_; 
v___x_2639_ = 4194304;
v___x_2640_ = lean_uint32_land(v___y_1519_, v___x_2639_);
v___x_2641_ = 0;
v___x_2642_ = lean_uint32_dec_eq(v___x_2640_, v___x_2641_);
if (v___x_2642_ == 0)
{
goto v___jp_2627_;
}
else
{
uint32_t v___x_2643_; 
v___x_2643_ = lean_uint32_lor(v___y_1519_, v___x_2639_);
return v___x_2643_;
}
}
}
v___jp_2644_:
{
float v_result_2647_; uint8_t v___x_2648_; 
v_result_2647_ = lean_float32_mul(v___y_2645_, v___y_2646_);
v___x_2648_ = lean_float32_beq(v_result_2647_, v_result_2647_);
if (v___x_2648_ == 0)
{
uint32_t v___x_2649_; uint32_t v___x_2650_; uint32_t v___x_2651_; uint32_t v___x_2652_; uint8_t v___x_2653_; 
v___x_2649_ = 23;
v___x_2650_ = lean_uint32_shift_right(v___y_1519_, v___x_2649_);
v___x_2651_ = 255;
v___x_2652_ = lean_uint32_land(v___x_2650_, v___x_2651_);
v___x_2653_ = lean_uint32_dec_eq(v___x_2652_, v___x_2651_);
if (v___x_2653_ == 0)
{
v___y_2638_ = v___x_2653_;
goto v___jp_2637_;
}
else
{
uint32_t v___x_2654_; uint32_t v___x_2655_; uint32_t v___x_2656_; uint8_t v___x_2657_; 
v___x_2654_ = 8388607;
v___x_2655_ = lean_uint32_land(v___y_1519_, v___x_2654_);
v___x_2656_ = 0;
v___x_2657_ = lean_uint32_dec_eq(v___x_2655_, v___x_2656_);
if (v___x_2657_ == 0)
{
v___y_2638_ = v___x_2653_;
goto v___jp_2637_;
}
else
{
goto v___jp_2627_;
}
}
}
else
{
uint32_t v___x_2658_; 
v___x_2658_ = lean_float32_to_bits(v_result_2647_);
return v___x_2658_;
}
}
v___jp_2659_:
{
if (v___y_2661_ == 0)
{
float v___x_2662_; 
v___x_2662_ = lean_float32_of_bits(v___y_1520_);
v___y_2645_ = v___y_2660_;
v___y_2646_ = v___x_2662_;
goto v___jp_2644_;
}
else
{
uint32_t v___x_2663_; uint32_t v___x_2664_; uint32_t v___x_2665_; uint32_t v___x_2666_; float v___x_2667_; lean_object* v___x_2668_; uint32_t v___x_2669_; uint32_t v___x_2670_; lean_object* v___x_2671_; lean_object* v___x_2672_; float v___x_2673_; float v___x_2674_; 
v___x_2663_ = 8388607;
v___x_2664_ = lean_uint32_land(v___y_1520_, v___x_2663_);
v___x_2665_ = 8388608;
v___x_2666_ = lean_uint32_lor(v___x_2664_, v___x_2665_);
v___x_2667_ = lean_uint32_to_float32(v___x_2666_);
v___x_2668_ = lp_competition_R2W01b_scaleTable;
v___x_2669_ = 23;
v___x_2670_ = lean_uint32_shift_right(v___y_1520_, v___x_2669_);
v___x_2671_ = lean_uint32_to_nat(v___x_2670_);
v___x_2672_ = lean_array_fget_borrowed(v___x_2668_, v___x_2671_);
lean_dec(v___x_2671_);
v___x_2673_ = lean_unbox_float32(v___x_2672_);
v___x_2674_ = lean_float32_mul(v___x_2667_, v___x_2673_);
v___y_2645_ = v___y_2660_;
v___y_2646_ = v___x_2674_;
goto v___jp_2644_;
}
}
v___jp_2675_:
{
uint32_t v___x_2677_; uint32_t v_a_2678_; uint32_t v___x_2679_; uint32_t v___x_2680_; uint32_t v___x_2681_; uint8_t v___x_2682_; 
v___x_2677_ = 2147483647;
v_a_2678_ = lean_uint32_land(v___y_1520_, v___x_2677_);
v___x_2679_ = 201326591;
v___x_2680_ = 1;
v___x_2681_ = lean_uint32_sub(v_a_2678_, v___x_2680_);
v___x_2682_ = lean_uint32_dec_le(v___x_2679_, v___x_2681_);
if (v___x_2682_ == 0)
{
v___y_2660_ = v___y_2676_;
v___y_2661_ = v___x_2682_;
goto v___jp_2659_;
}
else
{
uint32_t v___x_2683_; uint8_t v___x_2684_; 
v___x_2683_ = 2139095040;
v___x_2684_ = lean_uint32_dec_lt(v_a_2678_, v___x_2683_);
v___y_2660_ = v___y_2676_;
v___y_2661_ = v___x_2684_;
goto v___jp_2659_;
}
}
v___jp_2685_:
{
if (v___y_2687_ == 0)
{
float v___x_2688_; 
v___x_2688_ = lean_float32_of_bits(v___y_1519_);
v___y_2676_ = v___x_2688_;
goto v___jp_2675_;
}
else
{
uint32_t v___x_2689_; uint32_t v___x_2690_; uint32_t v___x_2691_; uint32_t v___x_2692_; float v___x_2693_; lean_object* v___x_2694_; lean_object* v___x_2695_; lean_object* v___x_2696_; float v___x_2697_; float v___x_2698_; 
v___x_2689_ = 8388607;
v___x_2690_ = lean_uint32_land(v___y_1519_, v___x_2689_);
v___x_2691_ = 8388608;
v___x_2692_ = lean_uint32_lor(v___x_2690_, v___x_2691_);
v___x_2693_ = lean_uint32_to_float32(v___x_2692_);
v___x_2694_ = lp_competition_R2W01b_scaleTable;
v___x_2695_ = lean_uint32_to_nat(v___y_2686_);
v___x_2696_ = lean_array_fget_borrowed(v___x_2694_, v___x_2695_);
lean_dec(v___x_2695_);
v___x_2697_ = lean_unbox_float32(v___x_2696_);
v___x_2698_ = lean_float32_mul(v___x_2693_, v___x_2697_);
v___y_2676_ = v___x_2698_;
goto v___jp_2675_;
}
}
v___jp_2699_:
{
if (v___y_2700_ == 0)
{
uint32_t v___x_2701_; 
v___x_2701_ = lp_competition_Submission_FastMul_mul(v___y_1519_, v___y_1520_);
return v___x_2701_;
}
else
{
uint32_t v___x_2702_; uint32_t v___x_2703_; 
v___x_2702_ = 4194304;
v___x_2703_ = lean_uint32_lor(v___y_1520_, v___x_2702_);
return v___x_2703_;
}
}
v___jp_2704_:
{
uint32_t v___x_2705_; uint32_t v___x_2706_; uint32_t v___x_2707_; uint32_t v___x_2708_; uint8_t v___x_2709_; 
v___x_2705_ = 23;
v___x_2706_ = lean_uint32_shift_right(v___y_1520_, v___x_2705_);
v___x_2707_ = 255;
v___x_2708_ = lean_uint32_land(v___x_2706_, v___x_2707_);
v___x_2709_ = lean_uint32_dec_eq(v___x_2708_, v___x_2707_);
if (v___x_2709_ == 0)
{
v___y_2700_ = v___x_2709_;
goto v___jp_2699_;
}
else
{
uint32_t v___x_2710_; uint32_t v___x_2711_; uint32_t v___x_2712_; uint8_t v___x_2713_; 
v___x_2710_ = 8388607;
v___x_2711_ = lean_uint32_land(v___y_1520_, v___x_2710_);
v___x_2712_ = 0;
v___x_2713_ = lean_uint32_dec_eq(v___x_2711_, v___x_2712_);
if (v___x_2713_ == 0)
{
v___y_2700_ = v___x_2709_;
goto v___jp_2699_;
}
else
{
uint32_t v___x_2714_; 
v___x_2714_ = lp_competition_Submission_FastMul_mul(v___y_1519_, v___y_1520_);
return v___x_2714_;
}
}
}
v___jp_2715_:
{
if (v___y_2716_ == 0)
{
goto v___jp_2704_;
}
else
{
uint32_t v___x_2717_; uint32_t v___x_2718_; 
v___x_2717_ = 4194304;
v___x_2718_ = lean_uint32_lor(v___y_1519_, v___x_2717_);
return v___x_2718_;
}
}
v___jp_2719_:
{
uint32_t v___x_2720_; uint32_t v___x_2721_; uint32_t v___x_2722_; uint32_t v___x_2723_; uint8_t v___x_2724_; 
v___x_2720_ = 23;
v___x_2721_ = lean_uint32_shift_right(v___y_1519_, v___x_2720_);
v___x_2722_ = 255;
v___x_2723_ = lean_uint32_land(v___x_2721_, v___x_2722_);
v___x_2724_ = lean_uint32_dec_eq(v___x_2723_, v___x_2722_);
if (v___x_2724_ == 0)
{
v___y_2716_ = v___x_2724_;
goto v___jp_2715_;
}
else
{
uint32_t v___x_2725_; uint32_t v___x_2726_; uint32_t v___x_2727_; uint8_t v___x_2728_; 
v___x_2725_ = 8388607;
v___x_2726_ = lean_uint32_land(v___y_1519_, v___x_2725_);
v___x_2727_ = 0;
v___x_2728_ = lean_uint32_dec_eq(v___x_2726_, v___x_2727_);
if (v___x_2728_ == 0)
{
v___y_2716_ = v___x_2724_;
goto v___jp_2715_;
}
else
{
goto v___jp_2704_;
}
}
}
v___jp_2729_:
{
if (v___y_2730_ == 0)
{
goto v___jp_2719_;
}
else
{
uint32_t v___x_2731_; uint32_t v___x_2732_; uint32_t v___x_2733_; uint8_t v___x_2734_; 
v___x_2731_ = 4194304;
v___x_2732_ = lean_uint32_land(v___y_1520_, v___x_2731_);
v___x_2733_ = 0;
v___x_2734_ = lean_uint32_dec_eq(v___x_2732_, v___x_2733_);
if (v___x_2734_ == 0)
{
goto v___jp_2719_;
}
else
{
uint32_t v___x_2735_; 
v___x_2735_ = lean_uint32_lor(v___y_1520_, v___x_2731_);
return v___x_2735_;
}
}
}
v___jp_2736_:
{
uint32_t v___x_2737_; uint32_t v___x_2738_; uint32_t v___x_2739_; uint32_t v___x_2740_; uint8_t v___x_2741_; 
v___x_2737_ = 23;
v___x_2738_ = lean_uint32_shift_right(v___y_1520_, v___x_2737_);
v___x_2739_ = 255;
v___x_2740_ = lean_uint32_land(v___x_2738_, v___x_2739_);
v___x_2741_ = lean_uint32_dec_eq(v___x_2740_, v___x_2739_);
if (v___x_2741_ == 0)
{
v___y_2730_ = v___x_2741_;
goto v___jp_2729_;
}
else
{
uint32_t v___x_2742_; uint32_t v___x_2743_; uint32_t v___x_2744_; uint8_t v___x_2745_; 
v___x_2742_ = 8388607;
v___x_2743_ = lean_uint32_land(v___y_1520_, v___x_2742_);
v___x_2744_ = 0;
v___x_2745_ = lean_uint32_dec_eq(v___x_2743_, v___x_2744_);
if (v___x_2745_ == 0)
{
v___y_2730_ = v___x_2741_;
goto v___jp_2729_;
}
else
{
goto v___jp_2719_;
}
}
}
v___jp_2746_:
{
if (v___y_2747_ == 0)
{
goto v___jp_2736_;
}
else
{
uint32_t v___x_2748_; uint32_t v___x_2749_; uint32_t v___x_2750_; uint8_t v___x_2751_; 
v___x_2748_ = 4194304;
v___x_2749_ = lean_uint32_land(v___y_1519_, v___x_2748_);
v___x_2750_ = 0;
v___x_2751_ = lean_uint32_dec_eq(v___x_2749_, v___x_2750_);
if (v___x_2751_ == 0)
{
goto v___jp_2736_;
}
else
{
uint32_t v___x_2752_; 
v___x_2752_ = lean_uint32_lor(v___y_1519_, v___x_2748_);
return v___x_2752_;
}
}
}
v___jp_2753_:
{
float v_result_2756_; uint8_t v___x_2757_; 
v_result_2756_ = lean_float32_mul(v___y_2754_, v___y_2755_);
v___x_2757_ = lean_float32_beq(v_result_2756_, v_result_2756_);
if (v___x_2757_ == 0)
{
uint32_t v___x_2758_; uint32_t v___x_2759_; uint32_t v___x_2760_; uint32_t v___x_2761_; uint8_t v___x_2762_; 
v___x_2758_ = 23;
v___x_2759_ = lean_uint32_shift_right(v___y_1519_, v___x_2758_);
v___x_2760_ = 255;
v___x_2761_ = lean_uint32_land(v___x_2759_, v___x_2760_);
v___x_2762_ = lean_uint32_dec_eq(v___x_2761_, v___x_2760_);
if (v___x_2762_ == 0)
{
v___y_2747_ = v___x_2762_;
goto v___jp_2746_;
}
else
{
uint32_t v___x_2763_; uint32_t v___x_2764_; uint32_t v___x_2765_; uint8_t v___x_2766_; 
v___x_2763_ = 8388607;
v___x_2764_ = lean_uint32_land(v___y_1519_, v___x_2763_);
v___x_2765_ = 0;
v___x_2766_ = lean_uint32_dec_eq(v___x_2764_, v___x_2765_);
if (v___x_2766_ == 0)
{
v___y_2747_ = v___x_2762_;
goto v___jp_2746_;
}
else
{
goto v___jp_2736_;
}
}
}
else
{
uint32_t v___x_2767_; 
v___x_2767_ = lean_float32_to_bits(v_result_2756_);
return v___x_2767_;
}
}
v___jp_2768_:
{
if (v___y_2770_ == 0)
{
float v___x_2771_; 
v___x_2771_ = lean_float32_of_bits(v___y_1520_);
v___y_2754_ = v___y_2769_;
v___y_2755_ = v___x_2771_;
goto v___jp_2753_;
}
else
{
uint32_t v___x_2772_; uint32_t v___x_2773_; uint32_t v___x_2774_; uint32_t v___x_2775_; float v___x_2776_; lean_object* v___x_2777_; uint32_t v___x_2778_; uint32_t v___x_2779_; lean_object* v___x_2780_; lean_object* v___x_2781_; float v___x_2782_; float v___x_2783_; 
v___x_2772_ = 8388607;
v___x_2773_ = lean_uint32_land(v___y_1520_, v___x_2772_);
v___x_2774_ = 8388608;
v___x_2775_ = lean_uint32_lor(v___x_2773_, v___x_2774_);
v___x_2776_ = lean_uint32_to_float32(v___x_2775_);
v___x_2777_ = lp_competition_R2W01b_scaleTable;
v___x_2778_ = 23;
v___x_2779_ = lean_uint32_shift_right(v___y_1520_, v___x_2778_);
v___x_2780_ = lean_uint32_to_nat(v___x_2779_);
v___x_2781_ = lean_array_fget_borrowed(v___x_2777_, v___x_2780_);
lean_dec(v___x_2780_);
v___x_2782_ = lean_unbox_float32(v___x_2781_);
v___x_2783_ = lean_float32_mul(v___x_2776_, v___x_2782_);
v___y_2754_ = v___y_2769_;
v___y_2755_ = v___x_2783_;
goto v___jp_2753_;
}
}
v___jp_2784_:
{
uint32_t v___x_2786_; uint32_t v_a_2787_; uint32_t v___x_2788_; uint32_t v___x_2789_; uint32_t v___x_2790_; uint8_t v___x_2791_; 
v___x_2786_ = 2147483647;
v_a_2787_ = lean_uint32_land(v___y_1520_, v___x_2786_);
v___x_2788_ = 201326591;
v___x_2789_ = 1;
v___x_2790_ = lean_uint32_sub(v_a_2787_, v___x_2789_);
v___x_2791_ = lean_uint32_dec_le(v___x_2788_, v___x_2790_);
if (v___x_2791_ == 0)
{
v___y_2769_ = v___y_2785_;
v___y_2770_ = v___x_2791_;
goto v___jp_2768_;
}
else
{
uint32_t v___x_2792_; uint8_t v___x_2793_; 
v___x_2792_ = 2139095040;
v___x_2793_ = lean_uint32_dec_lt(v_a_2787_, v___x_2792_);
v___y_2769_ = v___y_2785_;
v___y_2770_ = v___x_2793_;
goto v___jp_2768_;
}
}
v___jp_2794_:
{
if (v___y_2796_ == 0)
{
float v___x_2797_; 
v___x_2797_ = lean_float32_of_bits(v___y_1519_);
v___y_2785_ = v___x_2797_;
goto v___jp_2784_;
}
else
{
uint32_t v___x_2798_; uint32_t v___x_2799_; uint32_t v___x_2800_; uint32_t v___x_2801_; float v___x_2802_; lean_object* v___x_2803_; lean_object* v___x_2804_; lean_object* v___x_2805_; float v___x_2806_; float v___x_2807_; 
v___x_2798_ = 8388607;
v___x_2799_ = lean_uint32_land(v___y_1519_, v___x_2798_);
v___x_2800_ = 8388608;
v___x_2801_ = lean_uint32_lor(v___x_2799_, v___x_2800_);
v___x_2802_ = lean_uint32_to_float32(v___x_2801_);
v___x_2803_ = lp_competition_R2W01b_scaleTable;
v___x_2804_ = lean_uint32_to_nat(v___y_2795_);
v___x_2805_ = lean_array_fget_borrowed(v___x_2803_, v___x_2804_);
lean_dec(v___x_2804_);
v___x_2806_ = lean_unbox_float32(v___x_2805_);
v___x_2807_ = lean_float32_mul(v___x_2802_, v___x_2806_);
v___y_2785_ = v___x_2807_;
goto v___jp_2784_;
}
}
v___jp_2808_:
{
if (v___y_2809_ == 0)
{
uint32_t v___x_2810_; uint32_t v___x_2811_; uint32_t v___x_2812_; uint32_t v_ex_2813_; uint32_t v___x_2814_; uint32_t v_ey_2815_; uint32_t v___x_2816_; uint32_t v___x_2817_; uint8_t v___x_2818_; 
v___x_2810_ = 23;
v___x_2811_ = lean_uint32_shift_right(v___y_1519_, v___x_2810_);
v___x_2812_ = 255;
v_ex_2813_ = lean_uint32_land(v___x_2811_, v___x_2812_);
v___x_2814_ = lean_uint32_shift_right(v___y_1520_, v___x_2810_);
v_ey_2815_ = lean_uint32_land(v___x_2814_, v___x_2812_);
v___x_2816_ = lean_uint32_add(v_ex_2813_, v_ey_2815_);
v___x_2817_ = 128;
v___x_2818_ = lean_uint32_dec_lt(v___x_2816_, v___x_2817_);
if (v___x_2818_ == 0)
{
uint32_t v___x_2819_; uint32_t v_a_2820_; uint32_t v___x_2821_; uint32_t v___x_2822_; uint32_t v___x_2823_; uint8_t v___x_2824_; 
v___x_2819_ = 2147483647;
v_a_2820_ = lean_uint32_land(v___y_1519_, v___x_2819_);
v___x_2821_ = 201326591;
v___x_2822_ = 1;
v___x_2823_ = lean_uint32_sub(v_a_2820_, v___x_2822_);
v___x_2824_ = lean_uint32_dec_le(v___x_2821_, v___x_2823_);
if (v___x_2824_ == 0)
{
v___y_2686_ = v___x_2811_;
v___y_2687_ = v___x_2824_;
goto v___jp_2685_;
}
else
{
uint32_t v___x_2825_; uint8_t v___x_2826_; 
v___x_2825_ = 2139095040;
v___x_2826_ = lean_uint32_dec_lt(v_a_2820_, v___x_2825_);
v___y_2686_ = v___x_2811_;
v___y_2687_ = v___x_2826_;
goto v___jp_2685_;
}
}
else
{
uint32_t v___x_2827_; uint32_t v___x_2828_; uint32_t v___x_2829_; uint8_t v___x_2830_; 
v___x_2827_ = 4278190080;
v___x_2828_ = 1;
v___x_2829_ = lean_uint32_shift_left(v___y_1519_, v___x_2828_);
v___x_2830_ = lean_uint32_dec_le(v___x_2827_, v___x_2829_);
if (v___x_2830_ == 0)
{
uint32_t v___x_2831_; uint8_t v___x_2832_; 
v___x_2831_ = lean_uint32_shift_left(v___y_1520_, v___x_2828_);
v___x_2832_ = lean_uint32_dec_le(v___x_2827_, v___x_2831_);
v___y_2576_ = v___x_2810_;
v___y_2577_ = v___x_2812_;
v___y_2578_ = v_ex_2813_;
v___y_2579_ = v_ey_2815_;
v___y_2580_ = v___x_2832_;
goto v___jp_2575_;
}
else
{
v___y_2576_ = v___x_2810_;
v___y_2577_ = v___x_2812_;
v___y_2578_ = v_ex_2813_;
v___y_2579_ = v_ey_2815_;
v___y_2580_ = v___x_2830_;
goto v___jp_2575_;
}
}
}
else
{
uint32_t v___x_2833_; uint32_t v___x_2834_; uint32_t v___x_2835_; uint32_t v___x_2836_; uint32_t v___x_2837_; uint32_t v___x_2838_; uint32_t v___x_2839_; uint32_t v___x_2840_; uint32_t v___x_2841_; uint32_t v___x_2842_; uint8_t v___x_2843_; 
v___x_2833_ = 23;
v___x_2834_ = lean_uint32_shift_right(v___y_1519_, v___x_2833_);
v___x_2835_ = 255;
v___x_2836_ = lean_uint32_land(v___x_2834_, v___x_2835_);
v___x_2837_ = lean_uint32_shift_right(v___y_1520_, v___x_2833_);
v___x_2838_ = lean_uint32_land(v___x_2837_, v___x_2835_);
v___x_2839_ = lean_uint32_add(v___x_2836_, v___x_2838_);
v___x_2840_ = 128;
v___x_2841_ = lean_uint32_sub(v___x_2839_, v___x_2840_);
v___x_2842_ = 252;
v___x_2843_ = lean_uint32_dec_le(v___x_2841_, v___x_2842_);
if (v___x_2843_ == 0)
{
uint8_t v___x_2844_; 
v___x_2844_ = lean_uint32_dec_lt(v___x_2839_, v___x_2840_);
if (v___x_2844_ == 0)
{
uint32_t v___x_2845_; uint32_t v_a_2846_; uint32_t v___x_2847_; uint32_t v___x_2848_; uint32_t v___x_2849_; uint8_t v___x_2850_; 
v___x_2845_ = 2147483647;
v_a_2846_ = lean_uint32_land(v___y_1519_, v___x_2845_);
v___x_2847_ = 201326591;
v___x_2848_ = 1;
v___x_2849_ = lean_uint32_sub(v_a_2846_, v___x_2848_);
v___x_2850_ = lean_uint32_dec_le(v___x_2847_, v___x_2849_);
if (v___x_2850_ == 0)
{
v___y_2795_ = v___x_2834_;
v___y_2796_ = v___x_2850_;
goto v___jp_2794_;
}
else
{
uint32_t v___x_2851_; uint8_t v___x_2852_; 
v___x_2851_ = 2139095040;
v___x_2852_ = lean_uint32_dec_lt(v_a_2846_, v___x_2851_);
v___y_2795_ = v___x_2834_;
v___y_2796_ = v___x_2852_;
goto v___jp_2794_;
}
}
else
{
uint32_t v___x_2853_; uint32_t v___x_2854_; uint32_t v___x_2855_; uint8_t v___x_2856_; 
v___x_2853_ = 4278190080;
v___x_2854_ = 1;
v___x_2855_ = lean_uint32_shift_left(v___y_1519_, v___x_2854_);
v___x_2856_ = lean_uint32_dec_le(v___x_2853_, v___x_2855_);
if (v___x_2856_ == 0)
{
uint32_t v___x_2857_; uint8_t v___x_2858_; 
v___x_2857_ = lean_uint32_shift_left(v___y_1520_, v___x_2854_);
v___x_2858_ = lean_uint32_dec_le(v___x_2853_, v___x_2857_);
v___y_2430_ = v___y_2809_;
v___y_2431_ = v___x_2833_;
v___y_2432_ = v___x_2835_;
v___y_2433_ = v___x_2838_;
v___y_2434_ = v___x_2836_;
v___y_2435_ = v___x_2858_;
goto v___jp_2429_;
}
else
{
v___y_2430_ = v___y_2809_;
v___y_2431_ = v___x_2833_;
v___y_2432_ = v___x_2835_;
v___y_2433_ = v___x_2838_;
v___y_2434_ = v___x_2836_;
v___y_2435_ = v___x_2856_;
goto v___jp_2429_;
}
}
}
else
{
uint32_t v___x_2859_; uint32_t v___x_2860_; uint32_t v___x_2861_; uint32_t v___x_2862_; uint64_t v___x_2863_; uint32_t v___x_2864_; uint32_t v___x_2865_; uint64_t v___x_2866_; uint64_t v_product_2867_; uint64_t v___x_2868_; uint64_t v___x_2869_; uint64_t v___x_2870_; uint64_t v___x_2871_; uint8_t v___x_2872_; 
v___x_2859_ = 8388607;
v___x_2860_ = lean_uint32_land(v___y_1519_, v___x_2859_);
v___x_2861_ = 8388608;
v___x_2862_ = lean_uint32_lor(v___x_2860_, v___x_2861_);
v___x_2863_ = lean_uint32_to_uint64(v___x_2862_);
v___x_2864_ = lean_uint32_land(v___y_1520_, v___x_2859_);
v___x_2865_ = lean_uint32_lor(v___x_2864_, v___x_2861_);
v___x_2866_ = lean_uint32_to_uint64(v___x_2865_);
v_product_2867_ = lean_uint64_mul(v___x_2863_, v___x_2866_);
v___x_2868_ = 23ULL;
v___x_2869_ = 47ULL;
v___x_2870_ = lean_uint64_shift_right(v_product_2867_, v___x_2869_);
v___x_2871_ = lean_uint64_add(v___x_2868_, v___x_2870_);
v___x_2872_ = lean_uint64_dec_eq(v___x_2871_, v___x_2868_);
if (v___x_2872_ == 0)
{
uint64_t v___x_2873_; uint64_t v_q_2874_; uint64_t v___x_2875_; uint64_t v___x_2876_; uint64_t v_r_2877_; uint64_t v_half_2878_; uint8_t v___x_2879_; uint8_t v___x_2880_; 
v___x_2873_ = 24ULL;
v_q_2874_ = lean_uint64_shift_right(v_product_2867_, v___x_2873_);
v___x_2875_ = 1ULL;
v___x_2876_ = 16777215ULL;
v_r_2877_ = lean_uint64_land(v_product_2867_, v___x_2876_);
v_half_2878_ = 8388608ULL;
v___x_2879_ = lean_uint64_dec_lt(v_r_2877_, v_half_2878_);
v___x_2880_ = lean_uint64_dec_lt(v_half_2878_, v_r_2877_);
if (v___x_2879_ == 0)
{
v___y_2491_ = v___x_2880_;
v___y_2492_ = v___x_2833_;
v___y_2493_ = v___x_2839_;
v___y_2494_ = v___x_2875_;
v___y_2495_ = v___x_2835_;
v___y_2496_ = v_q_2874_;
v___y_2497_ = v___x_2843_;
v___y_2498_ = v___x_2875_;
goto v___jp_2490_;
}
else
{
uint64_t v___x_2881_; 
v___x_2881_ = 0ULL;
v___y_2491_ = v___x_2880_;
v___y_2492_ = v___x_2833_;
v___y_2493_ = v___x_2839_;
v___y_2494_ = v___x_2875_;
v___y_2495_ = v___x_2835_;
v___y_2496_ = v_q_2874_;
v___y_2497_ = v___x_2843_;
v___y_2498_ = v___x_2881_;
goto v___jp_2490_;
}
}
else
{
uint64_t v_q_2882_; uint64_t v___x_2883_; uint64_t v___x_2884_; uint64_t v_r_2885_; uint64_t v_half_2886_; uint8_t v___x_2887_; uint8_t v___x_2888_; 
v_q_2882_ = lean_uint64_shift_right(v_product_2867_, v___x_2868_);
v___x_2883_ = 1ULL;
v___x_2884_ = 8388607ULL;
v_r_2885_ = lean_uint64_land(v_product_2867_, v___x_2884_);
v_half_2886_ = 4194304ULL;
v___x_2887_ = lean_uint64_dec_lt(v_r_2885_, v_half_2886_);
v___x_2888_ = lean_uint64_dec_lt(v_half_2886_, v_r_2885_);
if (v___x_2887_ == 0)
{
v___y_2525_ = v___x_2883_;
v___y_2526_ = v___x_2888_;
v___y_2527_ = v___x_2833_;
v___y_2528_ = v___x_2839_;
v___y_2529_ = v_q_2882_;
v___y_2530_ = v___x_2835_;
v___y_2531_ = v___x_2843_;
v___y_2532_ = v___x_2883_;
goto v___jp_2524_;
}
else
{
uint64_t v___x_2889_; 
v___x_2889_ = 0ULL;
v___y_2525_ = v___x_2883_;
v___y_2526_ = v___x_2888_;
v___y_2527_ = v___x_2833_;
v___y_2528_ = v___x_2839_;
v___y_2529_ = v_q_2882_;
v___y_2530_ = v___x_2835_;
v___y_2531_ = v___x_2843_;
v___y_2532_ = v___x_2889_;
goto v___jp_2524_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_2902_, lean_object* v___y_2903_){
_start:
{
uint32_t v___y_11873__boxed_2904_; uint32_t v___y_11874__boxed_2905_; uint32_t v_res_2906_; lean_object* v_r_2907_; 
v___y_11873__boxed_2904_ = lean_unbox_uint32(v___y_2902_);
lean_dec(v___y_2902_);
v___y_11874__boxed_2905_ = lean_unbox_uint32(v___y_2903_);
lean_dec(v___y_2903_);
v_res_2906_ = lp_competition_main___lam__3(v___y_11873__boxed_2904_, v___y_11874__boxed_2905_);
v_r_2907_ = lean_box_uint32(v_res_2906_);
return v_r_2907_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2915_; lean_object* v___x_2916_; 
v___x_2915_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_2916_ = lean_io_getenv(v___x_2915_);
if (lean_obj_tag(v___x_2916_) == 0)
{
lean_object* v___f_2917_; lean_object* v___f_2918_; lean_object* v___x_2919_; lean_object* v___x_2920_; lean_object* v___x_2921_; 
v___f_2917_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2918_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_2919_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2920_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2921_ = lp_competition_Bench_runFull(v___f_2917_, v___f_2918_, v___x_2919_, v___x_2920_);
return v___x_2921_;
}
else
{
lean_object* v___f_2922_; lean_object* v___f_2923_; lean_object* v___x_2924_; lean_object* v___x_2925_; lean_object* v___x_2926_; 
lean_dec_ref_known(v___x_2916_, 1);
v___f_2922_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2923_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_2924_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2925_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2926_ = lp_competition_Bench_Suite_run(v___f_2922_, v___f_2923_, v___x_2924_, v___x_2925_);
return v___x_2926_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_2927_){
_start:
{
lean_object* v_res_2928_; 
v_res_2928_ = _lean_main();
return v_res_2928_;
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
