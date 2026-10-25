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
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
uint64_t lean_uint64_sub(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
uint8_t lean_uint64_dec_lt(uint64_t, uint64_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint64_t lean_uint64_shift_left(uint64_t, uint64_t);
uint64_t lean_uint64_land(uint64_t, uint64_t);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
uint64_t lean_uint32_to_uint64(uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
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
uint32_t v___y_8477__boxed_126_; uint32_t v___y_8478__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_8477__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_8478__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_main___lam__0(v___y_8477__boxed_126_, v___y_8478__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_130_, uint32_t v___y_131_){
_start:
{
uint32_t v___y_133_; uint32_t v___y_134_; uint32_t v___y_135_; uint32_t v___y_136_; uint32_t v___y_137_; uint32_t v___y_138_; uint32_t v___y_145_; uint32_t v___y_146_; uint32_t v___y_147_; uint32_t v___y_148_; uint32_t v___y_149_; uint32_t v___y_150_; uint8_t v___y_151_; uint32_t v___y_162_; uint32_t v___y_163_; uint32_t v___y_164_; uint32_t v___y_165_; uint32_t v___y_166_; uint8_t v___y_167_; uint32_t v___y_168_; uint8_t v___y_169_; uint32_t v___y_172_; uint32_t v___y_173_; uint32_t v___y_174_; uint32_t v___y_178_; uint32_t v___y_179_; uint32_t v___y_180_; uint32_t v___y_181_; uint32_t v___y_182_; uint32_t v___y_183_; uint32_t v___y_190_; uint32_t v___y_191_; uint32_t v___y_192_; uint8_t v___y_193_; uint32_t v___y_194_; uint32_t v___y_195_; uint32_t v___y_199_; uint64_t v___y_200_; uint32_t v___y_201_; uint32_t v___y_202_; uint8_t v___y_203_; uint64_t v___y_204_; uint64_t v___y_205_; uint32_t v___y_215_; uint32_t v___y_216_; uint32_t v___y_217_; uint64_t v___y_218_; uint8_t v___y_219_; uint8_t v___y_220_; uint64_t v___y_221_; uint64_t v___y_222_; uint32_t v___y_229_; uint32_t v___y_230_; uint32_t v___y_231_; uint8_t v___y_232_; uint64_t v___y_233_; uint64_t v___y_234_; uint64_t v___y_235_; uint32_t v___y_241_; uint32_t v___y_242_; uint32_t v___y_243_; uint32_t v___y_247_; uint32_t v___y_248_; uint32_t v___y_249_; uint32_t v___y_253_; uint32_t v___y_254_; uint32_t v___y_255_; uint32_t v___y_256_; uint32_t v___y_257_; uint32_t v___y_258_; uint32_t v___y_265_; uint32_t v___y_266_; uint32_t v___y_267_; uint32_t v___y_268_; uint8_t v___y_269_; uint32_t v___y_270_; uint32_t v___y_274_; uint32_t v___y_275_; uint64_t v___y_276_; uint64_t v___y_277_; uint32_t v___y_278_; uint8_t v___y_279_; uint64_t v___y_280_; uint64_t v___y_290_; uint32_t v___y_291_; uint8_t v___y_292_; uint32_t v___y_293_; uint32_t v___y_294_; uint64_t v___y_295_; uint8_t v___y_296_; uint64_t v___y_297_; uint32_t v___y_304_; uint32_t v___y_305_; uint64_t v___y_306_; uint64_t v___y_307_; uint32_t v___y_308_; uint8_t v___y_309_; uint64_t v___y_310_; uint32_t v___y_316_; uint32_t v___y_317_; uint32_t v___y_318_; uint32_t v___y_322_; uint32_t v___y_326_; uint8_t v___y_327_; uint64_t v___y_328_; uint64_t v___y_329_; uint64_t v___y_341_; uint32_t v___y_342_; uint32_t v___y_343_; uint32_t v___y_344_; uint64_t v___y_345_; uint8_t v___y_346_; uint64_t v___y_347_; uint64_t v___y_348_; uint64_t v___y_403_; uint32_t v___y_404_; uint32_t v___y_405_; uint32_t v___y_406_; uint64_t v___y_407_; uint8_t v___y_408_; uint64_t v___y_409_; uint64_t v___y_410_; uint64_t v___y_411_; uint64_t v___y_417_; uint64_t v___y_418_; uint64_t v___y_419_; uint32_t v___y_420_; uint64_t v___y_421_; uint32_t v___y_422_; uint32_t v___y_423_; uint64_t v___y_424_; uint8_t v___y_425_; uint64_t v___y_426_; uint64_t v___y_427_; uint64_t v___y_432_; uint64_t v___y_433_; uint32_t v___y_434_; uint32_t v___y_435_; uint32_t v___y_436_; uint64_t v___y_437_; uint8_t v___y_438_; uint64_t v___y_439_; uint64_t v___y_440_; uint64_t v___y_445_; uint32_t v___y_446_; uint64_t v___y_447_; uint32_t v___y_448_; uint32_t v___y_449_; uint64_t v___y_450_; uint64_t v___y_451_; uint64_t v___y_452_; uint8_t v___y_453_; uint64_t v___y_454_; uint64_t v___y_455_; uint64_t v___y_460_; uint32_t v___y_461_; uint32_t v___y_462_; uint32_t v___y_463_; uint64_t v___y_464_; uint64_t v___y_465_; uint8_t v___y_466_; uint64_t v___y_467_; uint64_t v___y_468_; uint64_t v___y_473_; uint64_t v___y_474_; uint32_t v___y_475_; uint64_t v___y_476_; uint32_t v___y_477_; uint32_t v___y_478_; uint64_t v___y_479_; uint8_t v___y_480_; uint64_t v___y_481_; uint64_t v___y_482_; uint64_t v___y_483_; uint64_t v___y_488_; uint64_t v___y_489_; uint32_t v___y_490_; uint32_t v___y_491_; uint32_t v___y_492_; uint64_t v___y_493_; uint8_t v___y_494_; uint64_t v___y_495_; uint64_t v___y_496_; uint64_t v___y_501_; uint64_t v___y_502_; uint32_t v___y_503_; uint64_t v___y_504_; uint32_t v___y_505_; uint64_t v___y_506_; uint32_t v___y_507_; uint64_t v___y_508_; uint8_t v___y_509_; uint64_t v___y_510_; uint64_t v___y_511_; uint64_t v___y_516_; uint32_t v___y_517_; uint32_t v___y_518_; uint32_t v___y_519_; uint64_t v___y_520_; uint64_t v___y_521_; uint8_t v___y_522_; uint64_t v___y_523_; uint64_t v___y_524_; uint64_t v___y_529_; uint32_t v___y_530_; uint32_t v___y_531_; uint32_t v___y_532_; uint64_t v___y_533_; uint64_t v___y_534_; uint8_t v___y_535_; uint64_t v___y_536_; uint64_t v___y_537_; uint64_t v___y_541_; uint32_t v___y_542_; uint32_t v___y_543_; uint32_t v___y_544_; uint64_t v___y_545_; uint8_t v___y_546_; uint32_t v___y_555_; uint64_t v___y_559_; uint32_t v___y_560_; uint8_t v___y_561_; uint64_t v___y_562_; uint64_t v___y_574_; uint32_t v___y_575_; uint64_t v___y_576_; uint64_t v___y_577_; uint32_t v___y_578_; uint32_t v___y_579_; uint8_t v___y_580_; uint64_t v___y_581_; uint32_t v___y_615_; uint64_t v___y_616_; uint64_t v___y_617_; uint32_t v___y_618_; uint32_t v___y_619_; uint8_t v___y_620_; uint32_t v___y_621_; uint64_t v___y_622_; uint32_t v___y_629_; uint32_t v___y_630_; uint64_t v___y_631_; uint32_t v___y_632_; uint32_t v___y_633_; uint8_t v___y_634_; uint32_t v___y_635_; uint64_t v___y_636_; uint32_t v___y_643_; uint32_t v___y_644_; uint32_t v___y_645_; uint32_t v___y_646_; uint32_t v___y_647_; uint8_t v___y_648_; uint32_t v___y_649_; uint64_t v___y_650_; uint32_t v___y_658_; uint32_t v___y_662_; uint64_t v___y_663_; uint8_t v___y_664_; uint64_t v___y_665_; uint32_t v___y_677_; uint32_t v___y_681_; uint64_t v___y_682_; uint8_t v___y_683_; uint64_t v___y_684_; uint32_t v___y_696_; uint64_t v___y_697_; uint32_t v___y_698_; uint64_t v___y_699_; uint32_t v___y_700_; uint64_t v___y_701_; uint8_t v___y_702_; uint64_t v___y_703_; uint32_t v___y_758_; uint64_t v___y_759_; uint64_t v___y_760_; uint32_t v___y_761_; uint32_t v___y_762_; uint64_t v___y_763_; uint64_t v___y_764_; uint8_t v___y_765_; uint64_t v___y_766_; uint64_t v___y_772_; uint32_t v___y_773_; uint64_t v___y_774_; uint32_t v___y_775_; uint64_t v___y_776_; uint64_t v___y_777_; uint32_t v___y_778_; uint64_t v___y_779_; uint8_t v___y_780_; uint64_t v___y_781_; uint64_t v___y_782_; uint32_t v___y_787_; uint64_t v___y_788_; uint64_t v___y_789_; uint32_t v___y_790_; uint32_t v___y_791_; uint64_t v___y_792_; uint64_t v___y_793_; uint8_t v___y_794_; uint64_t v___y_795_; uint64_t v___y_800_; uint32_t v___y_801_; uint64_t v___y_802_; uint32_t v___y_803_; uint64_t v___y_804_; uint64_t v___y_805_; uint64_t v___y_806_; uint64_t v___y_807_; uint32_t v___y_808_; uint8_t v___y_809_; uint64_t v___y_810_; uint32_t v___y_815_; uint64_t v___y_816_; uint64_t v___y_817_; uint32_t v___y_818_; uint64_t v___y_819_; uint32_t v___y_820_; uint64_t v___y_821_; uint8_t v___y_822_; uint64_t v___y_823_; uint32_t v___y_828_; uint64_t v___y_829_; uint64_t v___y_830_; uint64_t v___y_831_; uint32_t v___y_832_; uint64_t v___y_833_; uint64_t v___y_834_; uint32_t v___y_835_; uint8_t v___y_836_; uint64_t v___y_837_; uint64_t v___y_838_; uint32_t v___y_843_; uint64_t v___y_844_; uint64_t v___y_845_; uint32_t v___y_846_; uint32_t v___y_847_; uint64_t v___y_848_; uint8_t v___y_849_; uint64_t v___y_850_; uint64_t v___y_851_; uint64_t v___y_856_; uint64_t v___y_857_; uint32_t v___y_858_; uint64_t v___y_859_; uint32_t v___y_860_; uint64_t v___y_861_; uint64_t v___y_862_; uint32_t v___y_863_; uint64_t v___y_864_; uint8_t v___y_865_; uint64_t v___y_866_; uint64_t v___y_871_; uint32_t v___y_872_; uint64_t v___y_873_; uint64_t v___y_874_; uint32_t v___y_875_; uint32_t v___y_876_; uint64_t v___y_877_; uint8_t v___y_878_; uint64_t v___y_879_; uint32_t v___y_884_; uint64_t v___y_885_; uint32_t v___y_886_; uint64_t v___y_887_; uint64_t v___y_888_; uint64_t v___y_889_; uint32_t v___y_890_; uint8_t v___y_891_; uint64_t v___y_892_; uint32_t v___y_896_; uint64_t v___y_897_; uint64_t v___y_898_; uint32_t v___y_899_; uint32_t v___y_900_; uint8_t v___y_901_; uint32_t v___y_910_; uint64_t v___y_911_; uint32_t v___y_912_; uint32_t v___y_913_; uint8_t v___y_914_; uint64_t v___y_915_; uint64_t v___y_916_; uint64_t v___y_917_; uint32_t v___y_951_; uint32_t v___y_952_; uint32_t v___y_953_; uint32_t v___y_954_; uint8_t v___y_955_; uint64_t v___y_956_; uint64_t v___y_957_; uint64_t v___y_958_; uint32_t v___y_965_; uint32_t v___y_966_; uint32_t v___y_967_; uint32_t v___y_968_; uint8_t v___y_969_; uint32_t v___y_970_; uint64_t v___y_971_; uint64_t v___y_972_; uint32_t v___y_979_; uint32_t v___y_980_; uint32_t v___y_981_; uint32_t v___y_982_; uint32_t v___y_983_; uint8_t v___y_984_; uint32_t v___y_985_; uint64_t v___y_986_; uint32_t v___y_994_; uint32_t v___y_995_; uint32_t v___y_996_; uint32_t v___y_997_; uint8_t v___y_998_; uint8_t v___y_1009_; uint32_t v___y_1010_; uint32_t v___y_1011_; uint8_t v___y_1012_; uint32_t v___y_1013_; uint8_t v___y_1014_; uint32_t v___y_1015_; uint8_t v___y_1016_; uint8_t v___y_1018_; uint32_t v___y_1019_; uint32_t v___y_1020_; uint32_t v___y_1021_; uint8_t v___y_1022_; uint32_t v___y_1023_; uint8_t v___y_1024_; uint8_t v___y_1030_; uint32_t v___y_1031_; uint32_t v___y_1032_; uint32_t v___y_1033_; uint32_t v___y_1034_; uint8_t v___y_1035_; uint32_t v___y_1045_; uint32_t v___y_1046_; uint32_t v___y_1047_; uint32_t v___y_1048_; uint8_t v___y_1049_; uint32_t v___y_1060_; uint32_t v___y_1061_; uint32_t v___y_1062_; uint32_t v___y_1063_; uint32_t v___y_1066_; uint32_t v___y_1067_; uint32_t v___y_1068_; uint8_t v___y_1069_; uint8_t v___y_1070_; uint32_t v___y_1071_; uint8_t v___y_1072_; uint32_t v___y_1074_; uint32_t v___y_1075_; uint32_t v___y_1076_; uint8_t v___y_1077_; uint32_t v___y_1078_; uint8_t v___y_1079_; uint32_t v___y_1086_; uint32_t v___y_1087_; uint32_t v___y_1088_; uint32_t v___y_1089_; uint8_t v___y_1090_; uint8_t v___y_1101_; uint8_t v___y_1117_; uint8_t v___y_1131_; uint8_t v___y_1148_; float v___y_1155_; float v___y_1156_; float v___y_1170_; uint8_t v___y_1171_; float v___y_1186_; uint32_t v___y_1196_; uint8_t v___y_1197_; uint8_t v___y_1210_; uint8_t v___y_1226_; uint8_t v___y_1240_; uint8_t v___y_1257_; float v___y_1264_; float v___y_1265_; float v___y_1279_; uint8_t v___y_1280_; float v___y_1295_; uint32_t v___y_1305_; uint8_t v___y_1306_; uint8_t v___y_1319_; uint32_t v___x_1382_; uint32_t v___x_1383_; uint32_t v___x_1384_; uint32_t v___x_1385_; uint32_t v___x_1386_; uint32_t v___x_1387_; uint32_t v___x_1388_; uint8_t v___x_1389_; 
v___x_1382_ = 23;
v___x_1383_ = lean_uint32_shift_right(v___y_130_, v___x_1382_);
v___x_1384_ = 255;
v___x_1385_ = lean_uint32_land(v___x_1383_, v___x_1384_);
v___x_1386_ = 1;
v___x_1387_ = lean_uint32_sub(v___x_1385_, v___x_1386_);
v___x_1388_ = 253;
v___x_1389_ = lean_uint32_dec_le(v___x_1387_, v___x_1388_);
if (v___x_1389_ == 0)
{
v___y_1319_ = v___x_1389_;
goto v___jp_1318_;
}
else
{
uint32_t v___x_1390_; uint32_t v___x_1391_; uint32_t v___x_1392_; uint8_t v___x_1393_; 
v___x_1390_ = lean_uint32_shift_right(v___y_131_, v___x_1382_);
v___x_1391_ = lean_uint32_land(v___x_1390_, v___x_1384_);
v___x_1392_ = lean_uint32_sub(v___x_1391_, v___x_1386_);
v___x_1393_ = lean_uint32_dec_le(v___x_1392_, v___x_1388_);
v___y_1319_ = v___x_1393_;
goto v___jp_1318_;
}
v___jp_132_:
{
uint32_t v___x_139_; uint32_t v___x_140_; uint32_t v___x_141_; uint32_t v___x_142_; uint32_t v___x_143_; 
v___x_139_ = lean_uint32_land(v___y_136_, v___y_137_);
v___x_140_ = lean_uint32_shift_left(v___x_139_, v___y_134_);
v___x_141_ = lean_uint32_lor(v___y_138_, v___x_140_);
v___x_142_ = lean_uint32_land(v___y_133_, v___y_135_);
v___x_143_ = lean_uint32_lor(v___x_141_, v___x_142_);
return v___x_143_;
}
v___jp_144_:
{
uint32_t v___x_152_; uint32_t v___x_153_; uint32_t v___x_154_; uint32_t v___x_155_; uint32_t v___x_156_; uint32_t v___x_157_; uint32_t v___x_158_; 
v___x_152_ = lean_uint32_shift_right(v___y_145_, v___y_146_);
v___x_153_ = lean_uint32_land(v___x_152_, v___y_149_);
v___x_154_ = lean_uint32_add(v___x_153_, v___y_148_);
v___x_155_ = lean_uint32_add(v___x_154_, v___y_150_);
v___x_156_ = 300;
v___x_157_ = lean_uint32_sub(v___x_155_, v___x_156_);
v___x_158_ = lean_uint32_land(v___y_145_, v___y_147_);
if (v___y_151_ == 0)
{
uint32_t v___x_159_; 
v___x_159_ = 0;
v___y_133_ = v___x_158_;
v___y_134_ = v___y_146_;
v___y_135_ = v___y_147_;
v___y_136_ = v___x_157_;
v___y_137_ = v___y_149_;
v___y_138_ = v___x_159_;
goto v___jp_132_;
}
else
{
uint32_t v___x_160_; 
v___x_160_ = 2147483648;
v___y_133_ = v___x_158_;
v___y_134_ = v___y_146_;
v___y_135_ = v___y_147_;
v___y_136_ = v___x_157_;
v___y_137_ = v___y_149_;
v___y_138_ = v___x_160_;
goto v___jp_132_;
}
}
v___jp_161_:
{
if (v___y_169_ == 0)
{
v___y_145_ = v___y_162_;
v___y_146_ = v___y_163_;
v___y_147_ = v___y_164_;
v___y_148_ = v___y_165_;
v___y_149_ = v___y_166_;
v___y_150_ = v___y_168_;
v___y_151_ = v___y_167_;
goto v___jp_144_;
}
else
{
uint8_t v___x_170_; 
v___x_170_ = 0;
v___y_145_ = v___y_162_;
v___y_146_ = v___y_163_;
v___y_147_ = v___y_164_;
v___y_148_ = v___y_165_;
v___y_149_ = v___y_166_;
v___y_150_ = v___y_168_;
v___y_151_ = v___x_170_;
goto v___jp_144_;
}
}
v___jp_171_:
{
uint32_t v___x_175_; uint32_t v___x_176_; 
v___x_175_ = lean_uint32_land(v___y_172_, v___y_173_);
v___x_176_ = lean_uint32_lor(v___y_174_, v___x_175_);
return v___x_176_;
}
v___jp_177_:
{
uint32_t v___x_184_; uint32_t v___x_185_; uint32_t v___x_186_; uint32_t v___x_187_; uint32_t v___x_188_; 
v___x_184_ = lean_uint32_land(v___y_182_, v___y_181_);
v___x_185_ = lean_uint32_shift_left(v___x_184_, v___y_179_);
v___x_186_ = lean_uint32_lor(v___y_183_, v___x_185_);
v___x_187_ = lean_uint32_land(v___y_178_, v___y_180_);
v___x_188_ = lean_uint32_lor(v___x_186_, v___x_187_);
return v___x_188_;
}
v___jp_189_:
{
if (v___y_193_ == 0)
{
uint32_t v___x_196_; 
v___x_196_ = 0;
v___y_178_ = v___y_195_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___y_192_;
v___y_182_ = v___y_194_;
v___y_183_ = v___x_196_;
goto v___jp_177_;
}
else
{
uint32_t v___x_197_; 
v___x_197_ = 2147483648;
v___y_178_ = v___y_195_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___y_192_;
v___y_182_ = v___y_194_;
v___y_183_ = v___x_197_;
goto v___jp_177_;
}
}
v___jp_198_:
{
uint64_t v___x_206_; uint64_t v_encodedExponent_207_; uint32_t v___x_208_; uint64_t v___x_209_; uint8_t v___x_210_; 
v___x_206_ = 171ULL;
v_encodedExponent_207_ = lean_uint64_sub(v___y_200_, v___x_206_);
v___x_208_ = lean_uint64_to_uint32(v_encodedExponent_207_);
v___x_209_ = 8388608ULL;
v___x_210_ = lean_uint64_dec_lt(v___y_205_, v___x_209_);
if (v___x_210_ == 0)
{
uint64_t v___x_211_; uint32_t v___x_212_; 
v___x_211_ = lean_uint64_sub(v___y_205_, v___x_209_);
v___x_212_ = lean_uint64_to_uint32(v___x_211_);
v___y_190_ = v___y_199_;
v___y_191_ = v___y_201_;
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v___x_208_;
v___y_195_ = v___x_212_;
goto v___jp_189_;
}
else
{
uint32_t v___x_213_; 
v___x_213_ = lean_uint64_to_uint32(v___y_204_);
v___y_190_ = v___y_199_;
v___y_191_ = v___y_201_;
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v___x_208_;
v___y_195_ = v___x_213_;
goto v___jp_189_;
}
}
v___jp_214_:
{
uint64_t v___x_223_; uint8_t v___x_224_; 
v___x_223_ = 425ULL;
v___x_224_ = lean_uint64_dec_lt(v___x_223_, v___y_222_);
if (v___x_224_ == 0)
{
if (v___y_220_ == 0)
{
v___y_199_ = v___y_215_;
v___y_200_ = v___y_222_;
v___y_201_ = v___y_216_;
v___y_202_ = v___y_217_;
v___y_203_ = v___y_219_;
v___y_204_ = v___y_221_;
v___y_205_ = v___y_218_;
goto v___jp_198_;
}
else
{
uint64_t v___x_225_; 
v___x_225_ = 8388608ULL;
v___y_199_ = v___y_215_;
v___y_200_ = v___y_222_;
v___y_201_ = v___y_216_;
v___y_202_ = v___y_217_;
v___y_203_ = v___y_219_;
v___y_204_ = v___y_221_;
v___y_205_ = v___x_225_;
goto v___jp_198_;
}
}
else
{
if (v___y_219_ == 0)
{
uint32_t v___x_226_; 
v___x_226_ = 2139095040;
return v___x_226_;
}
else
{
uint32_t v___x_227_; 
v___x_227_ = 4286578688;
return v___x_227_;
}
}
}
v___jp_228_:
{
uint64_t v___x_236_; uint8_t v_carry_237_; 
v___x_236_ = 16777216ULL;
v_carry_237_ = lean_uint64_dec_eq(v___y_235_, v___x_236_);
if (v_carry_237_ == 0)
{
v___y_215_ = v___y_229_;
v___y_216_ = v___y_230_;
v___y_217_ = v___y_231_;
v___y_218_ = v___y_235_;
v___y_219_ = v___y_232_;
v___y_220_ = v_carry_237_;
v___y_221_ = v___y_234_;
v___y_222_ = v___y_233_;
goto v___jp_214_;
}
else
{
uint64_t v___x_238_; uint64_t v___x_239_; 
v___x_238_ = 1ULL;
v___x_239_ = lean_uint64_add(v___y_233_, v___x_238_);
v___y_215_ = v___y_229_;
v___y_216_ = v___y_230_;
v___y_217_ = v___y_231_;
v___y_218_ = v___y_235_;
v___y_219_ = v___y_232_;
v___y_220_ = v_carry_237_;
v___y_221_ = v___y_234_;
v___y_222_ = v___x_239_;
goto v___jp_214_;
}
}
v___jp_240_:
{
uint32_t v___x_244_; uint32_t v___x_245_; 
v___x_244_ = lean_uint32_land(v___y_242_, v___y_241_);
v___x_245_ = lean_uint32_lor(v___y_243_, v___x_244_);
return v___x_245_;
}
v___jp_246_:
{
uint32_t v___x_250_; uint32_t v___x_251_; 
v___x_250_ = lean_uint32_land(v___y_248_, v___y_247_);
v___x_251_ = lean_uint32_lor(v___y_249_, v___x_250_);
return v___x_251_;
}
v___jp_252_:
{
uint32_t v___x_259_; uint32_t v___x_260_; uint32_t v___x_261_; uint32_t v___x_262_; uint32_t v___x_263_; 
v___x_259_ = lean_uint32_land(v___y_254_, v___y_256_);
v___x_260_ = lean_uint32_shift_left(v___x_259_, v___y_253_);
v___x_261_ = lean_uint32_lor(v___y_258_, v___x_260_);
v___x_262_ = lean_uint32_land(v___y_255_, v___y_257_);
v___x_263_ = lean_uint32_lor(v___x_261_, v___x_262_);
return v___x_263_;
}
v___jp_264_:
{
if (v___y_269_ == 0)
{
uint32_t v___x_271_; 
v___x_271_ = 0;
v___y_253_ = v___y_265_;
v___y_254_ = v___y_266_;
v___y_255_ = v___y_270_;
v___y_256_ = v___y_267_;
v___y_257_ = v___y_268_;
v___y_258_ = v___x_271_;
goto v___jp_252_;
}
else
{
uint32_t v___x_272_; 
v___x_272_ = 2147483648;
v___y_253_ = v___y_265_;
v___y_254_ = v___y_266_;
v___y_255_ = v___y_270_;
v___y_256_ = v___y_267_;
v___y_257_ = v___y_268_;
v___y_258_ = v___x_272_;
goto v___jp_252_;
}
}
v___jp_273_:
{
uint64_t v___x_281_; uint64_t v_encodedExponent_282_; uint32_t v___x_283_; uint64_t v___x_284_; uint8_t v___x_285_; 
v___x_281_ = 171ULL;
v_encodedExponent_282_ = lean_uint64_sub(v___y_276_, v___x_281_);
v___x_283_ = lean_uint64_to_uint32(v_encodedExponent_282_);
v___x_284_ = 8388608ULL;
v___x_285_ = lean_uint64_dec_lt(v___y_280_, v___x_284_);
if (v___x_285_ == 0)
{
uint64_t v___x_286_; uint32_t v___x_287_; 
v___x_286_ = lean_uint64_sub(v___y_280_, v___x_284_);
v___x_287_ = lean_uint64_to_uint32(v___x_286_);
v___y_265_ = v___y_274_;
v___y_266_ = v___x_283_;
v___y_267_ = v___y_275_;
v___y_268_ = v___y_278_;
v___y_269_ = v___y_279_;
v___y_270_ = v___x_287_;
goto v___jp_264_;
}
else
{
uint32_t v___x_288_; 
v___x_288_ = lean_uint64_to_uint32(v___y_277_);
v___y_265_ = v___y_274_;
v___y_266_ = v___x_283_;
v___y_267_ = v___y_275_;
v___y_268_ = v___y_278_;
v___y_269_ = v___y_279_;
v___y_270_ = v___x_288_;
goto v___jp_264_;
}
}
v___jp_289_:
{
uint64_t v___x_298_; uint8_t v___x_299_; 
v___x_298_ = 425ULL;
v___x_299_ = lean_uint64_dec_lt(v___x_298_, v___y_297_);
if (v___x_299_ == 0)
{
if (v___y_292_ == 0)
{
v___y_274_ = v___y_291_;
v___y_275_ = v___y_293_;
v___y_276_ = v___y_297_;
v___y_277_ = v___y_295_;
v___y_278_ = v___y_294_;
v___y_279_ = v___y_296_;
v___y_280_ = v___y_290_;
goto v___jp_273_;
}
else
{
uint64_t v___x_300_; 
v___x_300_ = 8388608ULL;
v___y_274_ = v___y_291_;
v___y_275_ = v___y_293_;
v___y_276_ = v___y_297_;
v___y_277_ = v___y_295_;
v___y_278_ = v___y_294_;
v___y_279_ = v___y_296_;
v___y_280_ = v___x_300_;
goto v___jp_273_;
}
}
else
{
if (v___y_296_ == 0)
{
uint32_t v___x_301_; 
v___x_301_ = 2139095040;
return v___x_301_;
}
else
{
uint32_t v___x_302_; 
v___x_302_ = 4286578688;
return v___x_302_;
}
}
}
v___jp_303_:
{
uint64_t v___x_311_; uint8_t v_carry_312_; 
v___x_311_ = 16777216ULL;
v_carry_312_ = lean_uint64_dec_eq(v___y_310_, v___x_311_);
if (v_carry_312_ == 0)
{
v___y_290_ = v___y_310_;
v___y_291_ = v___y_304_;
v___y_292_ = v_carry_312_;
v___y_293_ = v___y_305_;
v___y_294_ = v___y_308_;
v___y_295_ = v___y_307_;
v___y_296_ = v___y_309_;
v___y_297_ = v___y_306_;
goto v___jp_289_;
}
else
{
uint64_t v___x_313_; uint64_t v___x_314_; 
v___x_313_ = 1ULL;
v___x_314_ = lean_uint64_add(v___y_306_, v___x_313_);
v___y_290_ = v___y_310_;
v___y_291_ = v___y_304_;
v___y_292_ = v_carry_312_;
v___y_293_ = v___y_305_;
v___y_294_ = v___y_308_;
v___y_295_ = v___y_307_;
v___y_296_ = v___y_309_;
v___y_297_ = v___x_314_;
goto v___jp_289_;
}
}
v___jp_315_:
{
uint32_t v___x_319_; uint32_t v___x_320_; 
v___x_319_ = lean_uint32_land(v___y_317_, v___y_316_);
v___x_320_ = lean_uint32_lor(v___y_318_, v___x_319_);
return v___x_320_;
}
v___jp_321_:
{
uint32_t v___x_323_; uint32_t v___x_324_; 
v___x_323_ = 8388608;
v___x_324_ = lean_uint32_lor(v___y_322_, v___x_323_);
return v___x_324_;
}
v___jp_325_:
{
uint8_t v___x_330_; 
v___x_330_ = lean_uint64_dec_eq(v___y_329_, v___y_328_);
if (v___x_330_ == 0)
{
uint64_t v___x_331_; uint8_t v___x_332_; 
v___x_331_ = 8388608ULL;
v___x_332_ = lean_uint64_dec_eq(v___y_329_, v___x_331_);
if (v___x_332_ == 0)
{
uint32_t v___x_333_; 
v___x_333_ = lean_uint64_to_uint32(v___y_329_);
if (v___y_327_ == 0)
{
uint32_t v___x_334_; 
v___x_334_ = 0;
v___y_241_ = v___y_326_;
v___y_242_ = v___x_333_;
v___y_243_ = v___x_334_;
goto v___jp_240_;
}
else
{
uint32_t v___x_335_; 
v___x_335_ = 2147483648;
v___y_241_ = v___y_326_;
v___y_242_ = v___x_333_;
v___y_243_ = v___x_335_;
goto v___jp_240_;
}
}
else
{
if (v___y_327_ == 0)
{
uint32_t v___x_336_; 
v___x_336_ = 0;
v___y_322_ = v___x_336_;
goto v___jp_321_;
}
else
{
uint32_t v___x_337_; 
v___x_337_ = 2147483648;
v___y_322_ = v___x_337_;
goto v___jp_321_;
}
}
}
else
{
if (v___y_327_ == 0)
{
uint32_t v___x_338_; 
v___x_338_ = 0;
return v___x_338_;
}
else
{
uint32_t v___x_339_; 
v___x_339_ = 2147483648;
return v___x_339_;
}
}
}
v___jp_340_:
{
uint64_t v_position_349_; uint64_t v___x_350_; uint8_t v___x_351_; 
v_position_349_ = lean_uint64_add(v___y_348_, v___y_341_);
v___x_350_ = 172ULL;
v___x_351_ = lean_uint64_dec_lt(v_position_349_, v___x_350_);
if (v___x_351_ == 0)
{
uint64_t v___x_352_; uint8_t v___x_353_; 
v___x_352_ = 23ULL;
v___x_353_ = lean_uint64_dec_lt(v___y_348_, v___x_352_);
if (v___x_353_ == 0)
{
uint64_t v___x_354_; uint8_t v___x_355_; 
v___x_354_ = lean_uint64_sub(v___y_348_, v___x_352_);
v___x_355_ = lean_uint64_dec_eq(v___x_354_, v___y_347_);
if (v___x_355_ == 0)
{
uint64_t v___x_356_; uint8_t v___x_357_; 
v___x_356_ = 64ULL;
v___x_357_ = lean_uint64_dec_lt(v___x_354_, v___x_356_);
if (v___x_357_ == 0)
{
uint8_t v___x_358_; 
v___x_358_ = lean_uint64_dec_eq(v___x_354_, v___x_356_);
if (v___x_358_ == 0)
{
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v___y_347_;
goto v___jp_228_;
}
else
{
uint64_t v___x_359_; uint8_t v___x_360_; 
v___x_359_ = 9223372036854775808ULL;
v___x_360_ = lean_uint64_dec_lt(v___x_359_, v___y_345_);
if (v___x_360_ == 0)
{
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v___y_347_;
goto v___jp_228_;
}
else
{
uint64_t v___x_361_; 
v___x_361_ = 1ULL;
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v___x_361_;
goto v___jp_228_;
}
}
}
else
{
uint64_t v_quotient_362_; uint64_t v___x_363_; uint64_t v___x_364_; uint64_t v___x_365_; uint64_t v_remainder_366_; uint64_t v___x_367_; uint64_t v_half_368_; uint8_t v___x_369_; 
v_quotient_362_ = lean_uint64_shift_right(v___y_345_, v___x_354_);
v___x_363_ = 1ULL;
v___x_364_ = lean_uint64_shift_left(v___x_363_, v___x_354_);
v___x_365_ = lean_uint64_sub(v___x_364_, v___x_363_);
v_remainder_366_ = lean_uint64_land(v___y_345_, v___x_365_);
v___x_367_ = lean_uint64_sub(v___x_354_, v___x_363_);
v_half_368_ = lean_uint64_shift_left(v___x_363_, v___x_367_);
v___x_369_ = lean_uint64_dec_lt(v_remainder_366_, v_half_368_);
if (v___x_369_ == 0)
{
uint8_t v___x_370_; 
v___x_370_ = lean_uint64_dec_lt(v_half_368_, v_remainder_366_);
if (v___x_370_ == 0)
{
uint64_t v___x_371_; uint8_t v___x_372_; 
v___x_371_ = lean_uint64_land(v_quotient_362_, v___x_363_);
v___x_372_ = lean_uint64_dec_eq(v___x_371_, v___y_347_);
if (v___x_372_ == 0)
{
uint64_t v___x_373_; 
v___x_373_ = lean_uint64_add(v_quotient_362_, v___x_363_);
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v___x_373_;
goto v___jp_228_;
}
else
{
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v_quotient_362_;
goto v___jp_228_;
}
}
else
{
uint64_t v___x_374_; 
v___x_374_ = lean_uint64_add(v_quotient_362_, v___x_363_);
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v___x_374_;
goto v___jp_228_;
}
}
else
{
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v_quotient_362_;
goto v___jp_228_;
}
}
}
else
{
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v___y_345_;
goto v___jp_228_;
}
}
else
{
uint64_t v___x_375_; uint64_t v___x_376_; 
v___x_375_ = lean_uint64_sub(v___x_352_, v___y_348_);
v___x_376_ = lean_uint64_shift_left(v___y_345_, v___x_375_);
v___y_229_ = v___y_342_;
v___y_230_ = v___y_343_;
v___y_231_ = v___y_344_;
v___y_232_ = v___y_346_;
v___y_233_ = v_position_349_;
v___y_234_ = v___y_347_;
v___y_235_ = v___x_376_;
goto v___jp_228_;
}
}
else
{
uint64_t v___x_377_; uint8_t v___x_378_; 
v___x_377_ = 149ULL;
v___x_378_ = lean_uint64_dec_lt(v___y_341_, v___x_377_);
if (v___x_378_ == 0)
{
uint64_t v___x_379_; uint64_t v___x_380_; 
v___x_379_ = lean_uint64_sub(v___y_341_, v___x_377_);
v___x_380_ = lean_uint64_shift_left(v___y_345_, v___x_379_);
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v___x_380_;
goto v___jp_325_;
}
else
{
uint64_t v___x_381_; uint8_t v___x_382_; 
v___x_381_ = lean_uint64_sub(v___x_377_, v___y_341_);
v___x_382_ = lean_uint64_dec_eq(v___x_381_, v___y_347_);
if (v___x_382_ == 0)
{
uint64_t v___x_383_; uint8_t v___x_384_; 
v___x_383_ = 64ULL;
v___x_384_ = lean_uint64_dec_lt(v___x_381_, v___x_383_);
if (v___x_384_ == 0)
{
uint8_t v___x_385_; 
v___x_385_ = lean_uint64_dec_eq(v___x_381_, v___x_383_);
if (v___x_385_ == 0)
{
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v___y_347_;
goto v___jp_325_;
}
else
{
uint64_t v___x_386_; uint8_t v___x_387_; 
v___x_386_ = 9223372036854775808ULL;
v___x_387_ = lean_uint64_dec_lt(v___x_386_, v___y_345_);
if (v___x_387_ == 0)
{
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v___y_347_;
goto v___jp_325_;
}
else
{
uint64_t v___x_388_; 
v___x_388_ = 1ULL;
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v___x_388_;
goto v___jp_325_;
}
}
}
else
{
uint64_t v_quotient_389_; uint64_t v___x_390_; uint64_t v___x_391_; uint64_t v___x_392_; uint64_t v_remainder_393_; uint64_t v___x_394_; uint64_t v_half_395_; uint8_t v___x_396_; 
v_quotient_389_ = lean_uint64_shift_right(v___y_345_, v___x_381_);
v___x_390_ = 1ULL;
v___x_391_ = lean_uint64_shift_left(v___x_390_, v___x_381_);
v___x_392_ = lean_uint64_sub(v___x_391_, v___x_390_);
v_remainder_393_ = lean_uint64_land(v___y_345_, v___x_392_);
v___x_394_ = lean_uint64_sub(v___x_381_, v___x_390_);
v_half_395_ = lean_uint64_shift_left(v___x_390_, v___x_394_);
v___x_396_ = lean_uint64_dec_lt(v_remainder_393_, v_half_395_);
if (v___x_396_ == 0)
{
uint8_t v___x_397_; 
v___x_397_ = lean_uint64_dec_lt(v_half_395_, v_remainder_393_);
if (v___x_397_ == 0)
{
uint64_t v___x_398_; uint8_t v___x_399_; 
v___x_398_ = lean_uint64_land(v_quotient_389_, v___x_390_);
v___x_399_ = lean_uint64_dec_eq(v___x_398_, v___y_347_);
if (v___x_399_ == 0)
{
uint64_t v___x_400_; 
v___x_400_ = lean_uint64_add(v_quotient_389_, v___x_390_);
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v___x_400_;
goto v___jp_325_;
}
else
{
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v_quotient_389_;
goto v___jp_325_;
}
}
else
{
uint64_t v___x_401_; 
v___x_401_ = lean_uint64_add(v_quotient_389_, v___x_390_);
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v___x_401_;
goto v___jp_325_;
}
}
else
{
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v_quotient_389_;
goto v___jp_325_;
}
}
}
else
{
v___y_326_ = v___y_343_;
v___y_327_ = v___y_346_;
v___y_328_ = v___y_347_;
v___y_329_ = v___y_345_;
goto v___jp_325_;
}
}
}
}
v___jp_402_:
{
uint64_t v___x_412_; uint64_t v___x_413_; uint8_t v___x_414_; 
v___x_412_ = 1ULL;
v___x_413_ = lean_uint64_shift_right(v___y_409_, v___x_412_);
v___x_414_ = lean_uint64_dec_eq(v___x_413_, v___y_410_);
if (v___x_414_ == 0)
{
uint64_t v___x_415_; 
v___x_415_ = lean_uint64_add(v___y_411_, v___x_412_);
v___y_341_ = v___y_403_;
v___y_342_ = v___y_404_;
v___y_343_ = v___y_405_;
v___y_344_ = v___y_406_;
v___y_345_ = v___y_407_;
v___y_346_ = v___y_408_;
v___y_347_ = v___y_410_;
v___y_348_ = v___x_415_;
goto v___jp_340_;
}
else
{
v___y_341_ = v___y_403_;
v___y_342_ = v___y_404_;
v___y_343_ = v___y_405_;
v___y_344_ = v___y_406_;
v___y_345_ = v___y_407_;
v___y_346_ = v___y_408_;
v___y_347_ = v___y_410_;
v___y_348_ = v___y_411_;
goto v___jp_340_;
}
}
v___jp_416_:
{
uint64_t v___x_428_; uint8_t v___x_429_; 
v___x_428_ = lean_uint64_shift_right(v___y_417_, v___y_421_);
v___x_429_ = lean_uint64_dec_eq(v___x_428_, v___y_426_);
if (v___x_429_ == 0)
{
uint64_t v___x_430_; 
v___x_430_ = lean_uint64_add(v___y_419_, v___y_421_);
v___y_403_ = v___y_418_;
v___y_404_ = v___y_420_;
v___y_405_ = v___y_422_;
v___y_406_ = v___y_423_;
v___y_407_ = v___y_424_;
v___y_408_ = v___y_425_;
v___y_409_ = v___y_427_;
v___y_410_ = v___y_426_;
v___y_411_ = v___x_430_;
goto v___jp_402_;
}
else
{
v___y_403_ = v___y_418_;
v___y_404_ = v___y_420_;
v___y_405_ = v___y_422_;
v___y_406_ = v___y_423_;
v___y_407_ = v___y_424_;
v___y_408_ = v___y_425_;
v___y_409_ = v___y_427_;
v___y_410_ = v___y_426_;
v___y_411_ = v___y_419_;
goto v___jp_402_;
}
}
v___jp_431_:
{
uint64_t v___x_441_; uint64_t v___x_442_; uint8_t v___x_443_; 
v___x_441_ = 2ULL;
v___x_442_ = lean_uint64_shift_right(v___y_433_, v___x_441_);
v___x_443_ = lean_uint64_dec_eq(v___x_442_, v___y_439_);
if (v___x_443_ == 0)
{
v___y_417_ = v___y_433_;
v___y_418_ = v___y_432_;
v___y_419_ = v___y_440_;
v___y_420_ = v___y_434_;
v___y_421_ = v___x_441_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_436_;
v___y_424_ = v___y_437_;
v___y_425_ = v___y_438_;
v___y_426_ = v___y_439_;
v___y_427_ = v___x_442_;
goto v___jp_416_;
}
else
{
v___y_417_ = v___y_433_;
v___y_418_ = v___y_432_;
v___y_419_ = v___y_440_;
v___y_420_ = v___y_434_;
v___y_421_ = v___x_441_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_436_;
v___y_424_ = v___y_437_;
v___y_425_ = v___y_438_;
v___y_426_ = v___y_439_;
v___y_427_ = v___y_433_;
goto v___jp_416_;
}
}
v___jp_444_:
{
uint64_t v___x_456_; uint8_t v___x_457_; 
v___x_456_ = lean_uint64_shift_right(v___y_452_, v___y_451_);
v___x_457_ = lean_uint64_dec_eq(v___x_456_, v___y_454_);
if (v___x_457_ == 0)
{
uint64_t v___x_458_; 
v___x_458_ = lean_uint64_add(v___y_447_, v___y_451_);
v___y_432_ = v___y_445_;
v___y_433_ = v___y_455_;
v___y_434_ = v___y_446_;
v___y_435_ = v___y_448_;
v___y_436_ = v___y_449_;
v___y_437_ = v___y_450_;
v___y_438_ = v___y_453_;
v___y_439_ = v___y_454_;
v___y_440_ = v___x_458_;
goto v___jp_431_;
}
else
{
v___y_432_ = v___y_445_;
v___y_433_ = v___y_455_;
v___y_434_ = v___y_446_;
v___y_435_ = v___y_448_;
v___y_436_ = v___y_449_;
v___y_437_ = v___y_450_;
v___y_438_ = v___y_453_;
v___y_439_ = v___y_454_;
v___y_440_ = v___y_447_;
goto v___jp_431_;
}
}
v___jp_459_:
{
uint64_t v___x_469_; uint64_t v___x_470_; uint8_t v___x_471_; 
v___x_469_ = 4ULL;
v___x_470_ = lean_uint64_shift_right(v___y_465_, v___x_469_);
v___x_471_ = lean_uint64_dec_eq(v___x_470_, v___y_467_);
if (v___x_471_ == 0)
{
v___y_445_ = v___y_460_;
v___y_446_ = v___y_461_;
v___y_447_ = v___y_468_;
v___y_448_ = v___y_462_;
v___y_449_ = v___y_463_;
v___y_450_ = v___y_464_;
v___y_451_ = v___x_469_;
v___y_452_ = v___y_465_;
v___y_453_ = v___y_466_;
v___y_454_ = v___y_467_;
v___y_455_ = v___x_470_;
goto v___jp_444_;
}
else
{
v___y_445_ = v___y_460_;
v___y_446_ = v___y_461_;
v___y_447_ = v___y_468_;
v___y_448_ = v___y_462_;
v___y_449_ = v___y_463_;
v___y_450_ = v___y_464_;
v___y_451_ = v___x_469_;
v___y_452_ = v___y_465_;
v___y_453_ = v___y_466_;
v___y_454_ = v___y_467_;
v___y_455_ = v___y_465_;
goto v___jp_444_;
}
}
v___jp_472_:
{
uint64_t v___x_484_; uint8_t v___x_485_; 
v___x_484_ = lean_uint64_shift_right(v___y_473_, v___y_476_);
v___x_485_ = lean_uint64_dec_eq(v___x_484_, v___y_482_);
if (v___x_485_ == 0)
{
uint64_t v___x_486_; 
v___x_486_ = lean_uint64_add(v___y_481_, v___y_476_);
v___y_460_ = v___y_474_;
v___y_461_ = v___y_475_;
v___y_462_ = v___y_477_;
v___y_463_ = v___y_478_;
v___y_464_ = v___y_479_;
v___y_465_ = v___y_483_;
v___y_466_ = v___y_480_;
v___y_467_ = v___y_482_;
v___y_468_ = v___x_486_;
goto v___jp_459_;
}
else
{
v___y_460_ = v___y_474_;
v___y_461_ = v___y_475_;
v___y_462_ = v___y_477_;
v___y_463_ = v___y_478_;
v___y_464_ = v___y_479_;
v___y_465_ = v___y_483_;
v___y_466_ = v___y_480_;
v___y_467_ = v___y_482_;
v___y_468_ = v___y_481_;
goto v___jp_459_;
}
}
v___jp_487_:
{
uint64_t v___x_497_; uint64_t v___x_498_; uint8_t v___x_499_; 
v___x_497_ = 8ULL;
v___x_498_ = lean_uint64_shift_right(v___y_488_, v___x_497_);
v___x_499_ = lean_uint64_dec_eq(v___x_498_, v___y_495_);
if (v___x_499_ == 0)
{
v___y_473_ = v___y_488_;
v___y_474_ = v___y_489_;
v___y_475_ = v___y_490_;
v___y_476_ = v___x_497_;
v___y_477_ = v___y_491_;
v___y_478_ = v___y_492_;
v___y_479_ = v___y_493_;
v___y_480_ = v___y_494_;
v___y_481_ = v___y_496_;
v___y_482_ = v___y_495_;
v___y_483_ = v___x_498_;
goto v___jp_472_;
}
else
{
v___y_473_ = v___y_488_;
v___y_474_ = v___y_489_;
v___y_475_ = v___y_490_;
v___y_476_ = v___x_497_;
v___y_477_ = v___y_491_;
v___y_478_ = v___y_492_;
v___y_479_ = v___y_493_;
v___y_480_ = v___y_494_;
v___y_481_ = v___y_496_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_488_;
goto v___jp_472_;
}
}
v___jp_500_:
{
uint64_t v___x_512_; uint8_t v___x_513_; 
v___x_512_ = lean_uint64_shift_right(v___y_506_, v___y_504_);
v___x_513_ = lean_uint64_dec_eq(v___x_512_, v___y_510_);
if (v___x_513_ == 0)
{
uint64_t v___x_514_; 
v___x_514_ = lean_uint64_add(v___y_502_, v___y_504_);
v___y_488_ = v___y_511_;
v___y_489_ = v___y_501_;
v___y_490_ = v___y_503_;
v___y_491_ = v___y_505_;
v___y_492_ = v___y_507_;
v___y_493_ = v___y_508_;
v___y_494_ = v___y_509_;
v___y_495_ = v___y_510_;
v___y_496_ = v___x_514_;
goto v___jp_487_;
}
else
{
v___y_488_ = v___y_511_;
v___y_489_ = v___y_501_;
v___y_490_ = v___y_503_;
v___y_491_ = v___y_505_;
v___y_492_ = v___y_507_;
v___y_493_ = v___y_508_;
v___y_494_ = v___y_509_;
v___y_495_ = v___y_510_;
v___y_496_ = v___y_502_;
goto v___jp_487_;
}
}
v___jp_515_:
{
uint64_t v___x_525_; uint64_t v___x_526_; uint8_t v___x_527_; 
v___x_525_ = 16ULL;
v___x_526_ = lean_uint64_shift_right(v___y_520_, v___x_525_);
v___x_527_ = lean_uint64_dec_eq(v___x_526_, v___y_523_);
if (v___x_527_ == 0)
{
v___y_501_ = v___y_516_;
v___y_502_ = v___y_524_;
v___y_503_ = v___y_517_;
v___y_504_ = v___x_525_;
v___y_505_ = v___y_518_;
v___y_506_ = v___y_520_;
v___y_507_ = v___y_519_;
v___y_508_ = v___y_521_;
v___y_509_ = v___y_522_;
v___y_510_ = v___y_523_;
v___y_511_ = v___x_526_;
goto v___jp_500_;
}
else
{
v___y_501_ = v___y_516_;
v___y_502_ = v___y_524_;
v___y_503_ = v___y_517_;
v___y_504_ = v___x_525_;
v___y_505_ = v___y_518_;
v___y_506_ = v___y_520_;
v___y_507_ = v___y_519_;
v___y_508_ = v___y_521_;
v___y_509_ = v___y_522_;
v___y_510_ = v___y_523_;
v___y_511_ = v___y_520_;
goto v___jp_500_;
}
}
v___jp_528_:
{
uint64_t v___x_538_; uint8_t v___x_539_; 
v___x_538_ = lean_uint64_shift_right(v___y_533_, v___y_534_);
v___x_539_ = lean_uint64_dec_eq(v___x_538_, v___y_536_);
if (v___x_539_ == 0)
{
v___y_516_ = v___y_529_;
v___y_517_ = v___y_530_;
v___y_518_ = v___y_531_;
v___y_519_ = v___y_532_;
v___y_520_ = v___y_537_;
v___y_521_ = v___y_533_;
v___y_522_ = v___y_535_;
v___y_523_ = v___y_536_;
v___y_524_ = v___y_534_;
goto v___jp_515_;
}
else
{
v___y_516_ = v___y_529_;
v___y_517_ = v___y_530_;
v___y_518_ = v___y_531_;
v___y_519_ = v___y_532_;
v___y_520_ = v___y_537_;
v___y_521_ = v___y_533_;
v___y_522_ = v___y_535_;
v___y_523_ = v___y_536_;
v___y_524_ = v___y_536_;
goto v___jp_515_;
}
}
v___jp_540_:
{
uint64_t v___x_547_; uint8_t v___x_548_; 
v___x_547_ = 0ULL;
v___x_548_ = lean_uint64_dec_eq(v___y_545_, v___x_547_);
if (v___x_548_ == 0)
{
uint64_t v___x_549_; uint64_t v___x_550_; uint8_t v___x_551_; 
v___x_549_ = 32ULL;
v___x_550_ = lean_uint64_shift_right(v___y_545_, v___x_549_);
v___x_551_ = lean_uint64_dec_eq(v___x_550_, v___x_547_);
if (v___x_551_ == 0)
{
v___y_529_ = v___y_541_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_544_;
v___y_533_ = v___y_545_;
v___y_534_ = v___x_549_;
v___y_535_ = v___y_546_;
v___y_536_ = v___x_547_;
v___y_537_ = v___x_550_;
goto v___jp_528_;
}
else
{
v___y_529_ = v___y_541_;
v___y_530_ = v___y_542_;
v___y_531_ = v___y_543_;
v___y_532_ = v___y_544_;
v___y_533_ = v___y_545_;
v___y_534_ = v___x_549_;
v___y_535_ = v___y_546_;
v___y_536_ = v___x_547_;
v___y_537_ = v___y_545_;
goto v___jp_528_;
}
}
else
{
if (v___y_546_ == 0)
{
uint32_t v___x_552_; 
v___x_552_ = 0;
return v___x_552_;
}
else
{
uint32_t v___x_553_; 
v___x_553_ = 2147483648;
return v___x_553_;
}
}
}
v___jp_554_:
{
uint32_t v___x_556_; uint32_t v___x_557_; 
v___x_556_ = 8388608;
v___x_557_ = lean_uint32_lor(v___y_555_, v___x_556_);
return v___x_557_;
}
v___jp_558_:
{
uint8_t v___x_563_; 
v___x_563_ = lean_uint64_dec_eq(v___y_562_, v___y_559_);
if (v___x_563_ == 0)
{
uint64_t v___x_564_; uint8_t v___x_565_; 
v___x_564_ = 8388608ULL;
v___x_565_ = lean_uint64_dec_eq(v___y_562_, v___x_564_);
if (v___x_565_ == 0)
{
uint32_t v___x_566_; 
v___x_566_ = lean_uint64_to_uint32(v___y_562_);
if (v___y_561_ == 0)
{
uint32_t v___x_567_; 
v___x_567_ = 0;
v___y_172_ = v___x_566_;
v___y_173_ = v___y_560_;
v___y_174_ = v___x_567_;
goto v___jp_171_;
}
else
{
uint32_t v___x_568_; 
v___x_568_ = 2147483648;
v___y_172_ = v___x_566_;
v___y_173_ = v___y_560_;
v___y_174_ = v___x_568_;
goto v___jp_171_;
}
}
else
{
if (v___y_561_ == 0)
{
uint32_t v___x_569_; 
v___x_569_ = 0;
v___y_555_ = v___x_569_;
goto v___jp_554_;
}
else
{
uint32_t v___x_570_; 
v___x_570_ = 2147483648;
v___y_555_ = v___x_570_;
goto v___jp_554_;
}
}
}
else
{
if (v___y_561_ == 0)
{
uint32_t v___x_571_; 
v___x_571_ = 0;
return v___x_571_;
}
else
{
uint32_t v___x_572_; 
v___x_572_ = 2147483648;
return v___x_572_;
}
}
}
v___jp_573_:
{
uint64_t v___x_582_; uint64_t v___x_583_; uint64_t v___x_584_; uint8_t v___x_585_; 
v___x_582_ = lean_uint64_mul(v___y_577_, v___y_576_);
v___x_583_ = lean_uint64_add(v___y_574_, v___y_581_);
v___x_584_ = 281474976710656ULL;
v___x_585_ = lean_uint64_dec_lt(v___x_582_, v___x_584_);
if (v___x_585_ == 0)
{
v___y_541_ = v___x_583_;
v___y_542_ = v___y_575_;
v___y_543_ = v___y_578_;
v___y_544_ = v___y_579_;
v___y_545_ = v___x_582_;
v___y_546_ = v___y_580_;
goto v___jp_540_;
}
else
{
uint64_t v___x_586_; uint8_t v___x_587_; 
v___x_586_ = 123ULL;
v___x_587_ = lean_uint64_dec_le(v___x_583_, v___x_586_);
if (v___x_587_ == 0)
{
v___y_541_ = v___x_583_;
v___y_542_ = v___y_575_;
v___y_543_ = v___y_578_;
v___y_544_ = v___y_579_;
v___y_545_ = v___x_582_;
v___y_546_ = v___y_580_;
goto v___jp_540_;
}
else
{
uint64_t v___x_588_; uint8_t v___x_589_; 
v___x_588_ = 0ULL;
v___x_589_ = lean_uint64_dec_eq(v___x_582_, v___x_588_);
if (v___x_589_ == 0)
{
uint64_t v___x_590_; uint64_t v___x_591_; uint8_t v___x_592_; 
v___x_590_ = 149ULL;
v___x_591_ = lean_uint64_sub(v___x_590_, v___x_583_);
v___x_592_ = lean_uint64_dec_eq(v___x_591_, v___x_588_);
if (v___x_592_ == 0)
{
uint64_t v___x_593_; uint8_t v___x_594_; 
v___x_593_ = 64ULL;
v___x_594_ = lean_uint64_dec_lt(v___x_591_, v___x_593_);
if (v___x_594_ == 0)
{
uint8_t v___x_595_; 
v___x_595_ = lean_uint64_dec_eq(v___x_591_, v___x_593_);
if (v___x_595_ == 0)
{
v___y_559_ = v___x_588_;
v___y_560_ = v___y_578_;
v___y_561_ = v___y_580_;
v___y_562_ = v___x_588_;
goto v___jp_558_;
}
else
{
uint64_t v___x_596_; uint8_t v___x_597_; 
v___x_596_ = 9223372036854775808ULL;
v___x_597_ = lean_uint64_dec_lt(v___x_596_, v___x_582_);
if (v___x_597_ == 0)
{
v___y_559_ = v___x_588_;
v___y_560_ = v___y_578_;
v___y_561_ = v___y_580_;
v___y_562_ = v___x_588_;
goto v___jp_558_;
}
else
{
uint64_t v___x_598_; 
v___x_598_ = 1ULL;
v___y_559_ = v___x_588_;
v___y_560_ = v___y_578_;
v___y_561_ = v___y_580_;
v___y_562_ = v___x_598_;
goto v___jp_558_;
}
}
}
else
{
uint64_t v_quotient_599_; uint64_t v___x_600_; uint64_t v___x_601_; uint64_t v___x_602_; uint64_t v_remainder_603_; uint64_t v___x_604_; uint64_t v_half_605_; uint8_t v___x_606_; 
v_quotient_599_ = lean_uint64_shift_right(v___x_582_, v___x_591_);
v___x_600_ = 1ULL;
v___x_601_ = lean_uint64_shift_left(v___x_600_, v___x_591_);
v___x_602_ = lean_uint64_sub(v___x_601_, v___x_600_);
v_remainder_603_ = lean_uint64_land(v___x_582_, v___x_602_);
v___x_604_ = lean_uint64_sub(v___x_591_, v___x_600_);
v_half_605_ = lean_uint64_shift_left(v___x_600_, v___x_604_);
v___x_606_ = lean_uint64_dec_lt(v_remainder_603_, v_half_605_);
if (v___x_606_ == 0)
{
uint8_t v___x_607_; 
v___x_607_ = lean_uint64_dec_lt(v_half_605_, v_remainder_603_);
if (v___x_607_ == 0)
{
uint64_t v___x_608_; uint8_t v___x_609_; 
v___x_608_ = lean_uint64_land(v_quotient_599_, v___x_600_);
v___x_609_ = lean_uint64_dec_eq(v___x_608_, v___x_588_);
if (v___x_609_ == 0)
{
uint64_t v___x_610_; 
v___x_610_ = lean_uint64_add(v_quotient_599_, v___x_600_);
v___y_559_ = v___x_588_;
v___y_560_ = v___y_578_;
v___y_561_ = v___y_580_;
v___y_562_ = v___x_610_;
goto v___jp_558_;
}
else
{
v___y_559_ = v___x_588_;
v___y_560_ = v___y_578_;
v___y_561_ = v___y_580_;
v___y_562_ = v_quotient_599_;
goto v___jp_558_;
}
}
else
{
uint64_t v___x_611_; 
v___x_611_ = lean_uint64_add(v_quotient_599_, v___x_600_);
v___y_559_ = v___x_588_;
v___y_560_ = v___y_578_;
v___y_561_ = v___y_580_;
v___y_562_ = v___x_611_;
goto v___jp_558_;
}
}
else
{
v___y_559_ = v___x_588_;
v___y_560_ = v___y_578_;
v___y_561_ = v___y_580_;
v___y_562_ = v_quotient_599_;
goto v___jp_558_;
}
}
}
else
{
v___y_559_ = v___x_588_;
v___y_560_ = v___y_578_;
v___y_561_ = v___y_580_;
v___y_562_ = v___x_582_;
goto v___jp_558_;
}
}
else
{
if (v___y_580_ == 0)
{
uint32_t v___x_612_; 
v___x_612_ = 0;
return v___x_612_;
}
else
{
uint32_t v___x_613_; 
v___x_613_ = 2147483648;
return v___x_613_;
}
}
}
}
}
v___jp_614_:
{
uint64_t v___x_623_; uint64_t v___x_624_; uint8_t v___x_625_; 
v___x_623_ = lean_uint32_to_uint64(v___y_621_);
v___x_624_ = 0ULL;
v___x_625_ = lean_uint64_dec_eq(v___x_623_, v___x_624_);
if (v___x_625_ == 0)
{
uint64_t v___x_626_; uint64_t v___x_627_; 
v___x_626_ = 1ULL;
v___x_627_ = lean_uint64_sub(v___x_623_, v___x_626_);
v___y_574_ = v___y_622_;
v___y_575_ = v___y_615_;
v___y_576_ = v___y_616_;
v___y_577_ = v___y_617_;
v___y_578_ = v___y_618_;
v___y_579_ = v___y_619_;
v___y_580_ = v___y_620_;
v___y_581_ = v___x_627_;
goto v___jp_573_;
}
else
{
v___y_574_ = v___y_622_;
v___y_575_ = v___y_615_;
v___y_576_ = v___y_616_;
v___y_577_ = v___y_617_;
v___y_578_ = v___y_618_;
v___y_579_ = v___y_619_;
v___y_580_ = v___y_620_;
v___y_581_ = v___x_624_;
goto v___jp_573_;
}
}
v___jp_628_:
{
uint64_t v___x_637_; uint64_t v___x_638_; uint8_t v___x_639_; 
v___x_637_ = lean_uint32_to_uint64(v___y_630_);
v___x_638_ = 0ULL;
v___x_639_ = lean_uint64_dec_eq(v___x_637_, v___x_638_);
if (v___x_639_ == 0)
{
uint64_t v___x_640_; uint64_t v___x_641_; 
v___x_640_ = 1ULL;
v___x_641_ = lean_uint64_sub(v___x_637_, v___x_640_);
v___y_615_ = v___y_629_;
v___y_616_ = v___y_636_;
v___y_617_ = v___y_631_;
v___y_618_ = v___y_632_;
v___y_619_ = v___y_633_;
v___y_620_ = v___y_634_;
v___y_621_ = v___y_635_;
v___y_622_ = v___x_641_;
goto v___jp_614_;
}
else
{
v___y_615_ = v___y_629_;
v___y_616_ = v___y_636_;
v___y_617_ = v___y_631_;
v___y_618_ = v___y_632_;
v___y_619_ = v___y_633_;
v___y_620_ = v___y_634_;
v___y_621_ = v___y_635_;
v___y_622_ = v___x_638_;
goto v___jp_614_;
}
}
v___jp_642_:
{
uint32_t v___x_651_; uint8_t v___x_652_; 
v___x_651_ = 0;
v___x_652_ = lean_uint32_dec_eq(v___y_649_, v___x_651_);
if (v___x_652_ == 0)
{
uint64_t v___x_653_; uint64_t v___x_654_; uint64_t v___x_655_; 
v___x_653_ = lean_uint32_to_uint64(v___y_643_);
v___x_654_ = 8388608ULL;
v___x_655_ = lean_uint64_lor(v___x_653_, v___x_654_);
v___y_629_ = v___y_644_;
v___y_630_ = v___y_645_;
v___y_631_ = v___y_650_;
v___y_632_ = v___y_646_;
v___y_633_ = v___y_647_;
v___y_634_ = v___y_648_;
v___y_635_ = v___y_649_;
v___y_636_ = v___x_655_;
goto v___jp_628_;
}
else
{
uint64_t v___x_656_; 
v___x_656_ = lean_uint32_to_uint64(v___y_643_);
v___y_629_ = v___y_644_;
v___y_630_ = v___y_645_;
v___y_631_ = v___y_650_;
v___y_632_ = v___y_646_;
v___y_633_ = v___y_647_;
v___y_634_ = v___y_648_;
v___y_635_ = v___y_649_;
v___y_636_ = v___x_656_;
goto v___jp_628_;
}
}
v___jp_657_:
{
uint32_t v___x_659_; uint32_t v___x_660_; 
v___x_659_ = 8388608;
v___x_660_ = lean_uint32_lor(v___y_658_, v___x_659_);
return v___x_660_;
}
v___jp_661_:
{
uint8_t v___x_666_; 
v___x_666_ = lean_uint64_dec_eq(v___y_665_, v___y_663_);
if (v___x_666_ == 0)
{
uint64_t v___x_667_; uint8_t v___x_668_; 
v___x_667_ = 8388608ULL;
v___x_668_ = lean_uint64_dec_eq(v___y_665_, v___x_667_);
if (v___x_668_ == 0)
{
uint32_t v___x_669_; 
v___x_669_ = lean_uint64_to_uint32(v___y_665_);
if (v___y_664_ == 0)
{
uint32_t v___x_670_; 
v___x_670_ = 0;
v___y_247_ = v___y_662_;
v___y_248_ = v___x_669_;
v___y_249_ = v___x_670_;
goto v___jp_246_;
}
else
{
uint32_t v___x_671_; 
v___x_671_ = 2147483648;
v___y_247_ = v___y_662_;
v___y_248_ = v___x_669_;
v___y_249_ = v___x_671_;
goto v___jp_246_;
}
}
else
{
if (v___y_664_ == 0)
{
uint32_t v___x_672_; 
v___x_672_ = 0;
v___y_658_ = v___x_672_;
goto v___jp_657_;
}
else
{
uint32_t v___x_673_; 
v___x_673_ = 2147483648;
v___y_658_ = v___x_673_;
goto v___jp_657_;
}
}
}
else
{
if (v___y_664_ == 0)
{
uint32_t v___x_674_; 
v___x_674_ = 0;
return v___x_674_;
}
else
{
uint32_t v___x_675_; 
v___x_675_ = 2147483648;
return v___x_675_;
}
}
}
v___jp_676_:
{
uint32_t v___x_678_; uint32_t v___x_679_; 
v___x_678_ = 8388608;
v___x_679_ = lean_uint32_lor(v___y_677_, v___x_678_);
return v___x_679_;
}
v___jp_680_:
{
uint8_t v___x_685_; 
v___x_685_ = lean_uint64_dec_eq(v___y_684_, v___y_682_);
if (v___x_685_ == 0)
{
uint64_t v___x_686_; uint8_t v___x_687_; 
v___x_686_ = 8388608ULL;
v___x_687_ = lean_uint64_dec_eq(v___y_684_, v___x_686_);
if (v___x_687_ == 0)
{
uint32_t v___x_688_; 
v___x_688_ = lean_uint64_to_uint32(v___y_684_);
if (v___y_683_ == 0)
{
uint32_t v___x_689_; 
v___x_689_ = 0;
v___y_316_ = v___y_681_;
v___y_317_ = v___x_688_;
v___y_318_ = v___x_689_;
goto v___jp_315_;
}
else
{
uint32_t v___x_690_; 
v___x_690_ = 2147483648;
v___y_316_ = v___y_681_;
v___y_317_ = v___x_688_;
v___y_318_ = v___x_690_;
goto v___jp_315_;
}
}
else
{
if (v___y_683_ == 0)
{
uint32_t v___x_691_; 
v___x_691_ = 0;
v___y_677_ = v___x_691_;
goto v___jp_676_;
}
else
{
uint32_t v___x_692_; 
v___x_692_ = 2147483648;
v___y_677_ = v___x_692_;
goto v___jp_676_;
}
}
}
else
{
if (v___y_683_ == 0)
{
uint32_t v___x_693_; 
v___x_693_ = 0;
return v___x_693_;
}
else
{
uint32_t v___x_694_; 
v___x_694_ = 2147483648;
return v___x_694_;
}
}
}
v___jp_695_:
{
uint64_t v_position_704_; uint64_t v___x_705_; uint8_t v___x_706_; 
v_position_704_ = lean_uint64_add(v___y_703_, v___y_699_);
v___x_705_ = 172ULL;
v___x_706_ = lean_uint64_dec_lt(v_position_704_, v___x_705_);
if (v___x_706_ == 0)
{
uint64_t v___x_707_; uint8_t v___x_708_; 
v___x_707_ = 23ULL;
v___x_708_ = lean_uint64_dec_lt(v___y_703_, v___x_707_);
if (v___x_708_ == 0)
{
uint64_t v___x_709_; uint8_t v___x_710_; 
v___x_709_ = lean_uint64_sub(v___y_703_, v___x_707_);
v___x_710_ = lean_uint64_dec_eq(v___x_709_, v___y_701_);
if (v___x_710_ == 0)
{
uint64_t v___x_711_; uint8_t v___x_712_; 
v___x_711_ = 64ULL;
v___x_712_ = lean_uint64_dec_lt(v___x_709_, v___x_711_);
if (v___x_712_ == 0)
{
uint8_t v___x_713_; 
v___x_713_ = lean_uint64_dec_eq(v___x_709_, v___x_711_);
if (v___x_713_ == 0)
{
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v___y_701_;
goto v___jp_303_;
}
else
{
uint64_t v___x_714_; uint8_t v___x_715_; 
v___x_714_ = 9223372036854775808ULL;
v___x_715_ = lean_uint64_dec_lt(v___x_714_, v___y_697_);
if (v___x_715_ == 0)
{
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v___y_701_;
goto v___jp_303_;
}
else
{
uint64_t v___x_716_; 
v___x_716_ = 1ULL;
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v___x_716_;
goto v___jp_303_;
}
}
}
else
{
uint64_t v_quotient_717_; uint64_t v___x_718_; uint64_t v___x_719_; uint64_t v___x_720_; uint64_t v_remainder_721_; uint64_t v___x_722_; uint64_t v_half_723_; uint8_t v___x_724_; 
v_quotient_717_ = lean_uint64_shift_right(v___y_697_, v___x_709_);
v___x_718_ = 1ULL;
v___x_719_ = lean_uint64_shift_left(v___x_718_, v___x_709_);
v___x_720_ = lean_uint64_sub(v___x_719_, v___x_718_);
v_remainder_721_ = lean_uint64_land(v___y_697_, v___x_720_);
v___x_722_ = lean_uint64_sub(v___x_709_, v___x_718_);
v_half_723_ = lean_uint64_shift_left(v___x_718_, v___x_722_);
v___x_724_ = lean_uint64_dec_lt(v_remainder_721_, v_half_723_);
if (v___x_724_ == 0)
{
uint8_t v___x_725_; 
v___x_725_ = lean_uint64_dec_lt(v_half_723_, v_remainder_721_);
if (v___x_725_ == 0)
{
uint64_t v___x_726_; uint8_t v___x_727_; 
v___x_726_ = lean_uint64_land(v_quotient_717_, v___x_718_);
v___x_727_ = lean_uint64_dec_eq(v___x_726_, v___y_701_);
if (v___x_727_ == 0)
{
uint64_t v___x_728_; 
v___x_728_ = lean_uint64_add(v_quotient_717_, v___x_718_);
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v___x_728_;
goto v___jp_303_;
}
else
{
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v_quotient_717_;
goto v___jp_303_;
}
}
else
{
uint64_t v___x_729_; 
v___x_729_ = lean_uint64_add(v_quotient_717_, v___x_718_);
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v___x_729_;
goto v___jp_303_;
}
}
else
{
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v_quotient_717_;
goto v___jp_303_;
}
}
}
else
{
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v___y_697_;
goto v___jp_303_;
}
}
else
{
uint64_t v___x_730_; uint64_t v___x_731_; 
v___x_730_ = lean_uint64_sub(v___x_707_, v___y_703_);
v___x_731_ = lean_uint64_shift_left(v___y_697_, v___x_730_);
v___y_304_ = v___y_696_;
v___y_305_ = v___y_698_;
v___y_306_ = v_position_704_;
v___y_307_ = v___y_701_;
v___y_308_ = v___y_700_;
v___y_309_ = v___y_702_;
v___y_310_ = v___x_731_;
goto v___jp_303_;
}
}
else
{
uint64_t v___x_732_; uint8_t v___x_733_; 
v___x_732_ = 149ULL;
v___x_733_ = lean_uint64_dec_lt(v___y_699_, v___x_732_);
if (v___x_733_ == 0)
{
uint64_t v___x_734_; uint64_t v___x_735_; 
v___x_734_ = lean_uint64_sub(v___y_699_, v___x_732_);
v___x_735_ = lean_uint64_shift_left(v___y_697_, v___x_734_);
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v___x_735_;
goto v___jp_680_;
}
else
{
uint64_t v___x_736_; uint8_t v___x_737_; 
v___x_736_ = lean_uint64_sub(v___x_732_, v___y_699_);
v___x_737_ = lean_uint64_dec_eq(v___x_736_, v___y_701_);
if (v___x_737_ == 0)
{
uint64_t v___x_738_; uint8_t v___x_739_; 
v___x_738_ = 64ULL;
v___x_739_ = lean_uint64_dec_lt(v___x_736_, v___x_738_);
if (v___x_739_ == 0)
{
uint8_t v___x_740_; 
v___x_740_ = lean_uint64_dec_eq(v___x_736_, v___x_738_);
if (v___x_740_ == 0)
{
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v___y_701_;
goto v___jp_680_;
}
else
{
uint64_t v___x_741_; uint8_t v___x_742_; 
v___x_741_ = 9223372036854775808ULL;
v___x_742_ = lean_uint64_dec_lt(v___x_741_, v___y_697_);
if (v___x_742_ == 0)
{
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v___y_701_;
goto v___jp_680_;
}
else
{
uint64_t v___x_743_; 
v___x_743_ = 1ULL;
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v___x_743_;
goto v___jp_680_;
}
}
}
else
{
uint64_t v_quotient_744_; uint64_t v___x_745_; uint64_t v___x_746_; uint64_t v___x_747_; uint64_t v_remainder_748_; uint64_t v___x_749_; uint64_t v_half_750_; uint8_t v___x_751_; 
v_quotient_744_ = lean_uint64_shift_right(v___y_697_, v___x_736_);
v___x_745_ = 1ULL;
v___x_746_ = lean_uint64_shift_left(v___x_745_, v___x_736_);
v___x_747_ = lean_uint64_sub(v___x_746_, v___x_745_);
v_remainder_748_ = lean_uint64_land(v___y_697_, v___x_747_);
v___x_749_ = lean_uint64_sub(v___x_736_, v___x_745_);
v_half_750_ = lean_uint64_shift_left(v___x_745_, v___x_749_);
v___x_751_ = lean_uint64_dec_lt(v_remainder_748_, v_half_750_);
if (v___x_751_ == 0)
{
uint8_t v___x_752_; 
v___x_752_ = lean_uint64_dec_lt(v_half_750_, v_remainder_748_);
if (v___x_752_ == 0)
{
uint64_t v___x_753_; uint8_t v___x_754_; 
v___x_753_ = lean_uint64_land(v_quotient_744_, v___x_745_);
v___x_754_ = lean_uint64_dec_eq(v___x_753_, v___y_701_);
if (v___x_754_ == 0)
{
uint64_t v___x_755_; 
v___x_755_ = lean_uint64_add(v_quotient_744_, v___x_745_);
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v___x_755_;
goto v___jp_680_;
}
else
{
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v_quotient_744_;
goto v___jp_680_;
}
}
else
{
uint64_t v___x_756_; 
v___x_756_ = lean_uint64_add(v_quotient_744_, v___x_745_);
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v___x_756_;
goto v___jp_680_;
}
}
else
{
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v_quotient_744_;
goto v___jp_680_;
}
}
}
else
{
v___y_681_ = v___y_700_;
v___y_682_ = v___y_701_;
v___y_683_ = v___y_702_;
v___y_684_ = v___y_697_;
goto v___jp_680_;
}
}
}
}
v___jp_757_:
{
uint64_t v___x_767_; uint64_t v___x_768_; uint8_t v___x_769_; 
v___x_767_ = 1ULL;
v___x_768_ = lean_uint64_shift_right(v___y_764_, v___x_767_);
v___x_769_ = lean_uint64_dec_eq(v___x_768_, v___y_763_);
if (v___x_769_ == 0)
{
uint64_t v___x_770_; 
v___x_770_ = lean_uint64_add(v___y_766_, v___x_767_);
v___y_696_ = v___y_758_;
v___y_697_ = v___y_759_;
v___y_698_ = v___y_761_;
v___y_699_ = v___y_760_;
v___y_700_ = v___y_762_;
v___y_701_ = v___y_763_;
v___y_702_ = v___y_765_;
v___y_703_ = v___x_770_;
goto v___jp_695_;
}
else
{
v___y_696_ = v___y_758_;
v___y_697_ = v___y_759_;
v___y_698_ = v___y_761_;
v___y_699_ = v___y_760_;
v___y_700_ = v___y_762_;
v___y_701_ = v___y_763_;
v___y_702_ = v___y_765_;
v___y_703_ = v___y_766_;
goto v___jp_695_;
}
}
v___jp_771_:
{
uint64_t v___x_783_; uint8_t v___x_784_; 
v___x_783_ = lean_uint64_shift_right(v___y_779_, v___y_781_);
v___x_784_ = lean_uint64_dec_eq(v___x_783_, v___y_777_);
if (v___x_784_ == 0)
{
uint64_t v___x_785_; 
v___x_785_ = lean_uint64_add(v___y_772_, v___y_781_);
v___y_758_ = v___y_773_;
v___y_759_ = v___y_774_;
v___y_760_ = v___y_776_;
v___y_761_ = v___y_775_;
v___y_762_ = v___y_778_;
v___y_763_ = v___y_777_;
v___y_764_ = v___y_782_;
v___y_765_ = v___y_780_;
v___y_766_ = v___x_785_;
goto v___jp_757_;
}
else
{
v___y_758_ = v___y_773_;
v___y_759_ = v___y_774_;
v___y_760_ = v___y_776_;
v___y_761_ = v___y_775_;
v___y_762_ = v___y_778_;
v___y_763_ = v___y_777_;
v___y_764_ = v___y_782_;
v___y_765_ = v___y_780_;
v___y_766_ = v___y_772_;
goto v___jp_757_;
}
}
v___jp_786_:
{
uint64_t v___x_796_; uint64_t v___x_797_; uint8_t v___x_798_; 
v___x_796_ = 2ULL;
v___x_797_ = lean_uint64_shift_right(v___y_793_, v___x_796_);
v___x_798_ = lean_uint64_dec_eq(v___x_797_, v___y_792_);
if (v___x_798_ == 0)
{
v___y_772_ = v___y_795_;
v___y_773_ = v___y_787_;
v___y_774_ = v___y_788_;
v___y_775_ = v___y_790_;
v___y_776_ = v___y_789_;
v___y_777_ = v___y_792_;
v___y_778_ = v___y_791_;
v___y_779_ = v___y_793_;
v___y_780_ = v___y_794_;
v___y_781_ = v___x_796_;
v___y_782_ = v___x_797_;
goto v___jp_771_;
}
else
{
v___y_772_ = v___y_795_;
v___y_773_ = v___y_787_;
v___y_774_ = v___y_788_;
v___y_775_ = v___y_790_;
v___y_776_ = v___y_789_;
v___y_777_ = v___y_792_;
v___y_778_ = v___y_791_;
v___y_779_ = v___y_793_;
v___y_780_ = v___y_794_;
v___y_781_ = v___x_796_;
v___y_782_ = v___y_793_;
goto v___jp_771_;
}
}
v___jp_799_:
{
uint64_t v___x_811_; uint8_t v___x_812_; 
v___x_811_ = lean_uint64_shift_right(v___y_806_, v___y_800_);
v___x_812_ = lean_uint64_dec_eq(v___x_811_, v___y_807_);
if (v___x_812_ == 0)
{
uint64_t v___x_813_; 
v___x_813_ = lean_uint64_add(v___y_805_, v___y_800_);
v___y_787_ = v___y_801_;
v___y_788_ = v___y_802_;
v___y_789_ = v___y_804_;
v___y_790_ = v___y_803_;
v___y_791_ = v___y_808_;
v___y_792_ = v___y_807_;
v___y_793_ = v___y_810_;
v___y_794_ = v___y_809_;
v___y_795_ = v___x_813_;
goto v___jp_786_;
}
else
{
v___y_787_ = v___y_801_;
v___y_788_ = v___y_802_;
v___y_789_ = v___y_804_;
v___y_790_ = v___y_803_;
v___y_791_ = v___y_808_;
v___y_792_ = v___y_807_;
v___y_793_ = v___y_810_;
v___y_794_ = v___y_809_;
v___y_795_ = v___y_805_;
goto v___jp_786_;
}
}
v___jp_814_:
{
uint64_t v___x_824_; uint64_t v___x_825_; uint8_t v___x_826_; 
v___x_824_ = 4ULL;
v___x_825_ = lean_uint64_shift_right(v___y_819_, v___x_824_);
v___x_826_ = lean_uint64_dec_eq(v___x_825_, v___y_821_);
if (v___x_826_ == 0)
{
v___y_800_ = v___x_824_;
v___y_801_ = v___y_815_;
v___y_802_ = v___y_816_;
v___y_803_ = v___y_818_;
v___y_804_ = v___y_817_;
v___y_805_ = v___y_823_;
v___y_806_ = v___y_819_;
v___y_807_ = v___y_821_;
v___y_808_ = v___y_820_;
v___y_809_ = v___y_822_;
v___y_810_ = v___x_825_;
goto v___jp_799_;
}
else
{
v___y_800_ = v___x_824_;
v___y_801_ = v___y_815_;
v___y_802_ = v___y_816_;
v___y_803_ = v___y_818_;
v___y_804_ = v___y_817_;
v___y_805_ = v___y_823_;
v___y_806_ = v___y_819_;
v___y_807_ = v___y_821_;
v___y_808_ = v___y_820_;
v___y_809_ = v___y_822_;
v___y_810_ = v___y_819_;
goto v___jp_799_;
}
}
v___jp_827_:
{
uint64_t v___x_839_; uint8_t v___x_840_; 
v___x_839_ = lean_uint64_shift_right(v___y_837_, v___y_831_);
v___x_840_ = lean_uint64_dec_eq(v___x_839_, v___y_834_);
if (v___x_840_ == 0)
{
uint64_t v___x_841_; 
v___x_841_ = lean_uint64_add(v___y_830_, v___y_831_);
v___y_815_ = v___y_828_;
v___y_816_ = v___y_829_;
v___y_817_ = v___y_833_;
v___y_818_ = v___y_832_;
v___y_819_ = v___y_838_;
v___y_820_ = v___y_835_;
v___y_821_ = v___y_834_;
v___y_822_ = v___y_836_;
v___y_823_ = v___x_841_;
goto v___jp_814_;
}
else
{
v___y_815_ = v___y_828_;
v___y_816_ = v___y_829_;
v___y_817_ = v___y_833_;
v___y_818_ = v___y_832_;
v___y_819_ = v___y_838_;
v___y_820_ = v___y_835_;
v___y_821_ = v___y_834_;
v___y_822_ = v___y_836_;
v___y_823_ = v___y_830_;
goto v___jp_814_;
}
}
v___jp_842_:
{
uint64_t v___x_852_; uint64_t v___x_853_; uint8_t v___x_854_; 
v___x_852_ = 8ULL;
v___x_853_ = lean_uint64_shift_right(v___y_850_, v___x_852_);
v___x_854_ = lean_uint64_dec_eq(v___x_853_, v___y_848_);
if (v___x_854_ == 0)
{
v___y_828_ = v___y_843_;
v___y_829_ = v___y_844_;
v___y_830_ = v___y_851_;
v___y_831_ = v___x_852_;
v___y_832_ = v___y_846_;
v___y_833_ = v___y_845_;
v___y_834_ = v___y_848_;
v___y_835_ = v___y_847_;
v___y_836_ = v___y_849_;
v___y_837_ = v___y_850_;
v___y_838_ = v___x_853_;
goto v___jp_827_;
}
else
{
v___y_828_ = v___y_843_;
v___y_829_ = v___y_844_;
v___y_830_ = v___y_851_;
v___y_831_ = v___x_852_;
v___y_832_ = v___y_846_;
v___y_833_ = v___y_845_;
v___y_834_ = v___y_848_;
v___y_835_ = v___y_847_;
v___y_836_ = v___y_849_;
v___y_837_ = v___y_850_;
v___y_838_ = v___y_850_;
goto v___jp_827_;
}
}
v___jp_855_:
{
uint64_t v___x_867_; uint8_t v___x_868_; 
v___x_867_ = lean_uint64_shift_right(v___y_856_, v___y_864_);
v___x_868_ = lean_uint64_dec_eq(v___x_867_, v___y_862_);
if (v___x_868_ == 0)
{
uint64_t v___x_869_; 
v___x_869_ = lean_uint64_add(v___y_857_, v___y_864_);
v___y_843_ = v___y_858_;
v___y_844_ = v___y_859_;
v___y_845_ = v___y_861_;
v___y_846_ = v___y_860_;
v___y_847_ = v___y_863_;
v___y_848_ = v___y_862_;
v___y_849_ = v___y_865_;
v___y_850_ = v___y_866_;
v___y_851_ = v___x_869_;
goto v___jp_842_;
}
else
{
v___y_843_ = v___y_858_;
v___y_844_ = v___y_859_;
v___y_845_ = v___y_861_;
v___y_846_ = v___y_860_;
v___y_847_ = v___y_863_;
v___y_848_ = v___y_862_;
v___y_849_ = v___y_865_;
v___y_850_ = v___y_866_;
v___y_851_ = v___y_857_;
goto v___jp_842_;
}
}
v___jp_870_:
{
uint64_t v___x_880_; uint64_t v___x_881_; uint8_t v___x_882_; 
v___x_880_ = 16ULL;
v___x_881_ = lean_uint64_shift_right(v___y_871_, v___x_880_);
v___x_882_ = lean_uint64_dec_eq(v___x_881_, v___y_877_);
if (v___x_882_ == 0)
{
v___y_856_ = v___y_871_;
v___y_857_ = v___y_879_;
v___y_858_ = v___y_872_;
v___y_859_ = v___y_873_;
v___y_860_ = v___y_875_;
v___y_861_ = v___y_874_;
v___y_862_ = v___y_877_;
v___y_863_ = v___y_876_;
v___y_864_ = v___x_880_;
v___y_865_ = v___y_878_;
v___y_866_ = v___x_881_;
goto v___jp_855_;
}
else
{
v___y_856_ = v___y_871_;
v___y_857_ = v___y_879_;
v___y_858_ = v___y_872_;
v___y_859_ = v___y_873_;
v___y_860_ = v___y_875_;
v___y_861_ = v___y_874_;
v___y_862_ = v___y_877_;
v___y_863_ = v___y_876_;
v___y_864_ = v___x_880_;
v___y_865_ = v___y_878_;
v___y_866_ = v___y_871_;
goto v___jp_855_;
}
}
v___jp_883_:
{
uint64_t v___x_893_; uint8_t v___x_894_; 
v___x_893_ = lean_uint64_shift_right(v___y_885_, v___y_888_);
v___x_894_ = lean_uint64_dec_eq(v___x_893_, v___y_889_);
if (v___x_894_ == 0)
{
v___y_871_ = v___y_892_;
v___y_872_ = v___y_884_;
v___y_873_ = v___y_885_;
v___y_874_ = v___y_887_;
v___y_875_ = v___y_886_;
v___y_876_ = v___y_890_;
v___y_877_ = v___y_889_;
v___y_878_ = v___y_891_;
v___y_879_ = v___y_888_;
goto v___jp_870_;
}
else
{
v___y_871_ = v___y_892_;
v___y_872_ = v___y_884_;
v___y_873_ = v___y_885_;
v___y_874_ = v___y_887_;
v___y_875_ = v___y_886_;
v___y_876_ = v___y_890_;
v___y_877_ = v___y_889_;
v___y_878_ = v___y_891_;
v___y_879_ = v___y_889_;
goto v___jp_870_;
}
}
v___jp_895_:
{
uint64_t v___x_902_; uint8_t v___x_903_; 
v___x_902_ = 0ULL;
v___x_903_ = lean_uint64_dec_eq(v___y_897_, v___x_902_);
if (v___x_903_ == 0)
{
uint64_t v___x_904_; uint64_t v___x_905_; uint8_t v___x_906_; 
v___x_904_ = 32ULL;
v___x_905_ = lean_uint64_shift_right(v___y_897_, v___x_904_);
v___x_906_ = lean_uint64_dec_eq(v___x_905_, v___x_902_);
if (v___x_906_ == 0)
{
v___y_884_ = v___y_896_;
v___y_885_ = v___y_897_;
v___y_886_ = v___y_899_;
v___y_887_ = v___y_898_;
v___y_888_ = v___x_904_;
v___y_889_ = v___x_902_;
v___y_890_ = v___y_900_;
v___y_891_ = v___y_901_;
v___y_892_ = v___x_905_;
goto v___jp_883_;
}
else
{
v___y_884_ = v___y_896_;
v___y_885_ = v___y_897_;
v___y_886_ = v___y_899_;
v___y_887_ = v___y_898_;
v___y_888_ = v___x_904_;
v___y_889_ = v___x_902_;
v___y_890_ = v___y_900_;
v___y_891_ = v___y_901_;
v___y_892_ = v___y_897_;
goto v___jp_883_;
}
}
else
{
if (v___y_901_ == 0)
{
uint32_t v___x_907_; 
v___x_907_ = 0;
return v___x_907_;
}
else
{
uint32_t v___x_908_; 
v___x_908_ = 2147483648;
return v___x_908_;
}
}
}
v___jp_909_:
{
uint64_t v___x_918_; uint64_t v___x_919_; uint64_t v___x_920_; uint8_t v___x_921_; 
v___x_918_ = lean_uint64_mul(v___y_916_, v___y_915_);
v___x_919_ = lean_uint64_add(v___y_911_, v___y_917_);
v___x_920_ = 281474976710656ULL;
v___x_921_ = lean_uint64_dec_lt(v___x_918_, v___x_920_);
if (v___x_921_ == 0)
{
v___y_896_ = v___y_910_;
v___y_897_ = v___x_918_;
v___y_898_ = v___x_919_;
v___y_899_ = v___y_912_;
v___y_900_ = v___y_913_;
v___y_901_ = v___y_914_;
goto v___jp_895_;
}
else
{
uint64_t v___x_922_; uint8_t v___x_923_; 
v___x_922_ = 123ULL;
v___x_923_ = lean_uint64_dec_le(v___x_919_, v___x_922_);
if (v___x_923_ == 0)
{
v___y_896_ = v___y_910_;
v___y_897_ = v___x_918_;
v___y_898_ = v___x_919_;
v___y_899_ = v___y_912_;
v___y_900_ = v___y_913_;
v___y_901_ = v___y_914_;
goto v___jp_895_;
}
else
{
uint64_t v___x_924_; uint8_t v___x_925_; 
v___x_924_ = 0ULL;
v___x_925_ = lean_uint64_dec_eq(v___x_918_, v___x_924_);
if (v___x_925_ == 0)
{
uint64_t v___x_926_; uint64_t v___x_927_; uint8_t v___x_928_; 
v___x_926_ = 149ULL;
v___x_927_ = lean_uint64_sub(v___x_926_, v___x_919_);
v___x_928_ = lean_uint64_dec_eq(v___x_927_, v___x_924_);
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
v___y_662_ = v___y_913_;
v___y_663_ = v___x_924_;
v___y_664_ = v___y_914_;
v___y_665_ = v___x_924_;
goto v___jp_661_;
}
else
{
uint64_t v___x_932_; uint8_t v___x_933_; 
v___x_932_ = 9223372036854775808ULL;
v___x_933_ = lean_uint64_dec_lt(v___x_932_, v___x_918_);
if (v___x_933_ == 0)
{
v___y_662_ = v___y_913_;
v___y_663_ = v___x_924_;
v___y_664_ = v___y_914_;
v___y_665_ = v___x_924_;
goto v___jp_661_;
}
else
{
uint64_t v___x_934_; 
v___x_934_ = 1ULL;
v___y_662_ = v___y_913_;
v___y_663_ = v___x_924_;
v___y_664_ = v___y_914_;
v___y_665_ = v___x_934_;
goto v___jp_661_;
}
}
}
else
{
uint64_t v_quotient_935_; uint64_t v___x_936_; uint64_t v___x_937_; uint64_t v___x_938_; uint64_t v_remainder_939_; uint64_t v___x_940_; uint64_t v_half_941_; uint8_t v___x_942_; 
v_quotient_935_ = lean_uint64_shift_right(v___x_918_, v___x_927_);
v___x_936_ = 1ULL;
v___x_937_ = lean_uint64_shift_left(v___x_936_, v___x_927_);
v___x_938_ = lean_uint64_sub(v___x_937_, v___x_936_);
v_remainder_939_ = lean_uint64_land(v___x_918_, v___x_938_);
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
v___x_945_ = lean_uint64_dec_eq(v___x_944_, v___x_924_);
if (v___x_945_ == 0)
{
uint64_t v___x_946_; 
v___x_946_ = lean_uint64_add(v_quotient_935_, v___x_936_);
v___y_662_ = v___y_913_;
v___y_663_ = v___x_924_;
v___y_664_ = v___y_914_;
v___y_665_ = v___x_946_;
goto v___jp_661_;
}
else
{
v___y_662_ = v___y_913_;
v___y_663_ = v___x_924_;
v___y_664_ = v___y_914_;
v___y_665_ = v_quotient_935_;
goto v___jp_661_;
}
}
else
{
uint64_t v___x_947_; 
v___x_947_ = lean_uint64_add(v_quotient_935_, v___x_936_);
v___y_662_ = v___y_913_;
v___y_663_ = v___x_924_;
v___y_664_ = v___y_914_;
v___y_665_ = v___x_947_;
goto v___jp_661_;
}
}
else
{
v___y_662_ = v___y_913_;
v___y_663_ = v___x_924_;
v___y_664_ = v___y_914_;
v___y_665_ = v_quotient_935_;
goto v___jp_661_;
}
}
}
else
{
v___y_662_ = v___y_913_;
v___y_663_ = v___x_924_;
v___y_664_ = v___y_914_;
v___y_665_ = v___x_918_;
goto v___jp_661_;
}
}
else
{
if (v___y_914_ == 0)
{
uint32_t v___x_948_; 
v___x_948_ = 0;
return v___x_948_;
}
else
{
uint32_t v___x_949_; 
v___x_949_ = 2147483648;
return v___x_949_;
}
}
}
}
}
v___jp_950_:
{
uint64_t v___x_959_; uint64_t v___x_960_; uint8_t v___x_961_; 
v___x_959_ = lean_uint32_to_uint64(v___y_954_);
v___x_960_ = 0ULL;
v___x_961_ = lean_uint64_dec_eq(v___x_959_, v___x_960_);
if (v___x_961_ == 0)
{
uint64_t v___x_962_; uint64_t v___x_963_; 
v___x_962_ = 1ULL;
v___x_963_ = lean_uint64_sub(v___x_959_, v___x_962_);
v___y_910_ = v___y_951_;
v___y_911_ = v___y_958_;
v___y_912_ = v___y_952_;
v___y_913_ = v___y_953_;
v___y_914_ = v___y_955_;
v___y_915_ = v___y_957_;
v___y_916_ = v___y_956_;
v___y_917_ = v___x_963_;
goto v___jp_909_;
}
else
{
v___y_910_ = v___y_951_;
v___y_911_ = v___y_958_;
v___y_912_ = v___y_952_;
v___y_913_ = v___y_953_;
v___y_914_ = v___y_955_;
v___y_915_ = v___y_957_;
v___y_916_ = v___y_956_;
v___y_917_ = v___x_960_;
goto v___jp_909_;
}
}
v___jp_964_:
{
uint64_t v___x_973_; uint64_t v___x_974_; uint8_t v___x_975_; 
v___x_973_ = lean_uint32_to_uint64(v___y_966_);
v___x_974_ = 0ULL;
v___x_975_ = lean_uint64_dec_eq(v___x_973_, v___x_974_);
if (v___x_975_ == 0)
{
uint64_t v___x_976_; uint64_t v___x_977_; 
v___x_976_ = 1ULL;
v___x_977_ = lean_uint64_sub(v___x_973_, v___x_976_);
v___y_951_ = v___y_965_;
v___y_952_ = v___y_967_;
v___y_953_ = v___y_968_;
v___y_954_ = v___y_970_;
v___y_955_ = v___y_969_;
v___y_956_ = v___y_971_;
v___y_957_ = v___y_972_;
v___y_958_ = v___x_977_;
goto v___jp_950_;
}
else
{
v___y_951_ = v___y_965_;
v___y_952_ = v___y_967_;
v___y_953_ = v___y_968_;
v___y_954_ = v___y_970_;
v___y_955_ = v___y_969_;
v___y_956_ = v___y_971_;
v___y_957_ = v___y_972_;
v___y_958_ = v___x_974_;
goto v___jp_950_;
}
}
v___jp_978_:
{
uint32_t v___x_987_; uint8_t v___x_988_; 
v___x_987_ = 0;
v___x_988_ = lean_uint32_dec_eq(v___y_983_, v___x_987_);
if (v___x_988_ == 0)
{
uint64_t v___x_989_; uint64_t v___x_990_; uint64_t v___x_991_; 
v___x_989_ = lean_uint32_to_uint64(v___y_985_);
v___x_990_ = 8388608ULL;
v___x_991_ = lean_uint64_lor(v___x_989_, v___x_990_);
v___y_965_ = v___y_979_;
v___y_966_ = v___y_981_;
v___y_967_ = v___y_980_;
v___y_968_ = v___y_982_;
v___y_969_ = v___y_984_;
v___y_970_ = v___y_983_;
v___y_971_ = v___y_986_;
v___y_972_ = v___x_991_;
goto v___jp_964_;
}
else
{
uint64_t v___x_992_; 
v___x_992_ = lean_uint32_to_uint64(v___y_985_);
v___y_965_ = v___y_979_;
v___y_966_ = v___y_981_;
v___y_967_ = v___y_980_;
v___y_968_ = v___y_982_;
v___y_969_ = v___y_984_;
v___y_970_ = v___y_983_;
v___y_971_ = v___y_986_;
v___y_972_ = v___x_992_;
goto v___jp_964_;
}
}
v___jp_993_:
{
uint32_t v___x_999_; uint32_t v_xFraction_1000_; uint32_t v_yFraction_1001_; uint32_t v___x_1002_; uint8_t v___x_1003_; 
v___x_999_ = 8388607;
v_xFraction_1000_ = lean_uint32_land(v___y_130_, v___x_999_);
v_yFraction_1001_ = lean_uint32_land(v___y_131_, v___x_999_);
v___x_1002_ = 0;
v___x_1003_ = lean_uint32_dec_eq(v___y_995_, v___x_1002_);
if (v___x_1003_ == 0)
{
uint64_t v___x_1004_; uint64_t v___x_1005_; uint64_t v___x_1006_; 
v___x_1004_ = lean_uint32_to_uint64(v_xFraction_1000_);
v___x_1005_ = 8388608ULL;
v___x_1006_ = lean_uint64_lor(v___x_1004_, v___x_1005_);
v___y_643_ = v_yFraction_1001_;
v___y_644_ = v___y_994_;
v___y_645_ = v___y_995_;
v___y_646_ = v___x_999_;
v___y_647_ = v___y_996_;
v___y_648_ = v___y_998_;
v___y_649_ = v___y_997_;
v___y_650_ = v___x_1006_;
goto v___jp_642_;
}
else
{
uint64_t v___x_1007_; 
v___x_1007_ = lean_uint32_to_uint64(v_xFraction_1000_);
v___y_643_ = v_yFraction_1001_;
v___y_644_ = v___y_994_;
v___y_645_ = v___y_995_;
v___y_646_ = v___x_999_;
v___y_647_ = v___y_996_;
v___y_648_ = v___y_998_;
v___y_649_ = v___y_997_;
v___y_650_ = v___x_1007_;
goto v___jp_642_;
}
}
v___jp_1008_:
{
if (v___y_1012_ == 0)
{
if (v___y_1016_ == 0)
{
v___y_994_ = v___y_1010_;
v___y_995_ = v___y_1011_;
v___y_996_ = v___y_1013_;
v___y_997_ = v___y_1015_;
v___y_998_ = v___y_1014_;
goto v___jp_993_;
}
else
{
v___y_994_ = v___y_1010_;
v___y_995_ = v___y_1011_;
v___y_996_ = v___y_1013_;
v___y_997_ = v___y_1015_;
v___y_998_ = v___y_1009_;
goto v___jp_993_;
}
}
else
{
if (v___y_1016_ == 0)
{
v___y_994_ = v___y_1010_;
v___y_995_ = v___y_1011_;
v___y_996_ = v___y_1013_;
v___y_997_ = v___y_1015_;
v___y_998_ = v___y_1009_;
goto v___jp_993_;
}
else
{
v___y_994_ = v___y_1010_;
v___y_995_ = v___y_1011_;
v___y_996_ = v___y_1013_;
v___y_997_ = v___y_1015_;
v___y_998_ = v___y_1014_;
goto v___jp_993_;
}
}
}
v___jp_1017_:
{
uint32_t v___x_1025_; uint32_t v___x_1026_; uint32_t v___x_1027_; uint8_t v___x_1028_; 
v___x_1025_ = 2147483648;
v___x_1026_ = lean_uint32_land(v___y_131_, v___x_1025_);
v___x_1027_ = 0;
v___x_1028_ = lean_uint32_dec_eq(v___x_1026_, v___x_1027_);
if (v___x_1028_ == 0)
{
v___y_1009_ = v___y_1018_;
v___y_1010_ = v___y_1019_;
v___y_1011_ = v___y_1020_;
v___y_1012_ = v___y_1024_;
v___y_1013_ = v___y_1021_;
v___y_1014_ = v___y_1022_;
v___y_1015_ = v___y_1023_;
v___y_1016_ = v___y_1018_;
goto v___jp_1008_;
}
else
{
v___y_1009_ = v___y_1018_;
v___y_1010_ = v___y_1019_;
v___y_1011_ = v___y_1020_;
v___y_1012_ = v___y_1024_;
v___y_1013_ = v___y_1021_;
v___y_1014_ = v___y_1022_;
v___y_1015_ = v___y_1023_;
v___y_1016_ = v___y_1022_;
goto v___jp_1008_;
}
}
v___jp_1029_:
{
if (v___y_1035_ == 0)
{
uint32_t v___x_1036_; uint32_t v___x_1037_; uint32_t v___x_1038_; uint8_t v___x_1039_; 
v___x_1036_ = 2147483648;
v___x_1037_ = lean_uint32_land(v___y_130_, v___x_1036_);
v___x_1038_ = 0;
v___x_1039_ = lean_uint32_dec_eq(v___x_1037_, v___x_1038_);
if (v___x_1039_ == 0)
{
v___y_1018_ = v___y_1030_;
v___y_1019_ = v___y_1031_;
v___y_1020_ = v___y_1032_;
v___y_1021_ = v___y_1033_;
v___y_1022_ = v___y_1035_;
v___y_1023_ = v___y_1034_;
v___y_1024_ = v___y_1030_;
goto v___jp_1017_;
}
else
{
v___y_1018_ = v___y_1030_;
v___y_1019_ = v___y_1031_;
v___y_1020_ = v___y_1032_;
v___y_1021_ = v___y_1033_;
v___y_1022_ = v___y_1035_;
v___y_1023_ = v___y_1034_;
v___y_1024_ = v___y_1035_;
goto v___jp_1017_;
}
}
else
{
lean_object* v___x_1040_; lean_object* v___x_1041_; lean_object* v___x_1042_; uint32_t v___x_1043_; 
v___x_1040_ = lean_uint32_to_nat(v___y_130_);
v___x_1041_ = lean_uint32_to_nat(v___y_131_);
v___x_1042_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1040_, v___x_1041_);
v___x_1043_ = lean_uint32_of_nat(v___x_1042_);
lean_dec(v___x_1042_);
return v___x_1043_;
}
}
v___jp_1044_:
{
uint32_t v___x_1050_; uint32_t v_xFraction_1051_; uint32_t v_yFraction_1052_; uint32_t v___x_1053_; uint8_t v___x_1054_; 
v___x_1050_ = 8388607;
v_xFraction_1051_ = lean_uint32_land(v___y_130_, v___x_1050_);
v_yFraction_1052_ = lean_uint32_land(v___y_131_, v___x_1050_);
v___x_1053_ = 0;
v___x_1054_ = lean_uint32_dec_eq(v___y_1046_, v___x_1053_);
if (v___x_1054_ == 0)
{
uint64_t v___x_1055_; uint64_t v___x_1056_; uint64_t v___x_1057_; 
v___x_1055_ = lean_uint32_to_uint64(v_xFraction_1051_);
v___x_1056_ = 8388608ULL;
v___x_1057_ = lean_uint64_lor(v___x_1055_, v___x_1056_);
v___y_979_ = v___y_1045_;
v___y_980_ = v___y_1047_;
v___y_981_ = v___y_1046_;
v___y_982_ = v___x_1050_;
v___y_983_ = v___y_1048_;
v___y_984_ = v___y_1049_;
v___y_985_ = v_yFraction_1052_;
v___y_986_ = v___x_1057_;
goto v___jp_978_;
}
else
{
uint64_t v___x_1058_; 
v___x_1058_ = lean_uint32_to_uint64(v_xFraction_1051_);
v___y_979_ = v___y_1045_;
v___y_980_ = v___y_1047_;
v___y_981_ = v___y_1046_;
v___y_982_ = v___x_1050_;
v___y_983_ = v___y_1048_;
v___y_984_ = v___y_1049_;
v___y_985_ = v_yFraction_1052_;
v___y_986_ = v___x_1058_;
goto v___jp_978_;
}
}
v___jp_1059_:
{
uint8_t v___x_1064_; 
v___x_1064_ = 1;
v___y_1045_ = v___y_1060_;
v___y_1046_ = v___y_1062_;
v___y_1047_ = v___y_1061_;
v___y_1048_ = v___y_1063_;
v___y_1049_ = v___x_1064_;
goto v___jp_1044_;
}
v___jp_1065_:
{
if (v___y_1070_ == 0)
{
if (v___y_1072_ == 0)
{
v___y_1045_ = v___y_1066_;
v___y_1046_ = v___y_1068_;
v___y_1047_ = v___y_1067_;
v___y_1048_ = v___y_1071_;
v___y_1049_ = v___y_1069_;
goto v___jp_1044_;
}
else
{
v___y_1060_ = v___y_1066_;
v___y_1061_ = v___y_1067_;
v___y_1062_ = v___y_1068_;
v___y_1063_ = v___y_1071_;
goto v___jp_1059_;
}
}
else
{
if (v___y_1072_ == 0)
{
v___y_1060_ = v___y_1066_;
v___y_1061_ = v___y_1067_;
v___y_1062_ = v___y_1068_;
v___y_1063_ = v___y_1071_;
goto v___jp_1059_;
}
else
{
v___y_1045_ = v___y_1066_;
v___y_1046_ = v___y_1068_;
v___y_1047_ = v___y_1067_;
v___y_1048_ = v___y_1071_;
v___y_1049_ = v___y_1069_;
goto v___jp_1044_;
}
}
}
v___jp_1073_:
{
uint32_t v___x_1080_; uint32_t v___x_1081_; uint32_t v___x_1082_; uint8_t v___x_1083_; 
v___x_1080_ = 2147483648;
v___x_1081_ = lean_uint32_land(v___y_131_, v___x_1080_);
v___x_1082_ = 0;
v___x_1083_ = lean_uint32_dec_eq(v___x_1081_, v___x_1082_);
if (v___x_1083_ == 0)
{
uint8_t v___x_1084_; 
v___x_1084_ = 1;
v___y_1066_ = v___y_1074_;
v___y_1067_ = v___y_1076_;
v___y_1068_ = v___y_1075_;
v___y_1069_ = v___y_1077_;
v___y_1070_ = v___y_1079_;
v___y_1071_ = v___y_1078_;
v___y_1072_ = v___x_1084_;
goto v___jp_1065_;
}
else
{
v___y_1066_ = v___y_1074_;
v___y_1067_ = v___y_1076_;
v___y_1068_ = v___y_1075_;
v___y_1069_ = v___y_1077_;
v___y_1070_ = v___y_1079_;
v___y_1071_ = v___y_1078_;
v___y_1072_ = v___y_1077_;
goto v___jp_1065_;
}
}
v___jp_1085_:
{
if (v___y_1090_ == 0)
{
uint32_t v___x_1091_; uint32_t v___x_1092_; uint32_t v___x_1093_; uint8_t v___x_1094_; 
v___x_1091_ = 2147483648;
v___x_1092_ = lean_uint32_land(v___y_130_, v___x_1091_);
v___x_1093_ = 0;
v___x_1094_ = lean_uint32_dec_eq(v___x_1092_, v___x_1093_);
if (v___x_1094_ == 0)
{
uint8_t v___x_1095_; 
v___x_1095_ = 1;
v___y_1074_ = v___y_1086_;
v___y_1075_ = v___y_1087_;
v___y_1076_ = v___y_1088_;
v___y_1077_ = v___y_1090_;
v___y_1078_ = v___y_1089_;
v___y_1079_ = v___x_1095_;
goto v___jp_1073_;
}
else
{
v___y_1074_ = v___y_1086_;
v___y_1075_ = v___y_1087_;
v___y_1076_ = v___y_1088_;
v___y_1077_ = v___y_1090_;
v___y_1078_ = v___y_1089_;
v___y_1079_ = v___y_1090_;
goto v___jp_1073_;
}
}
else
{
lean_object* v___x_1096_; lean_object* v___x_1097_; lean_object* v___x_1098_; uint32_t v___x_1099_; 
v___x_1096_ = lean_uint32_to_nat(v___y_130_);
v___x_1097_ = lean_uint32_to_nat(v___y_131_);
v___x_1098_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1096_, v___x_1097_);
v___x_1099_ = lean_uint32_of_nat(v___x_1098_);
lean_dec(v___x_1098_);
return v___x_1099_;
}
}
v___jp_1100_:
{
if (v___y_1101_ == 0)
{
uint32_t v___x_1102_; 
v___x_1102_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_1102_;
}
else
{
uint32_t v___x_1103_; uint32_t v___x_1104_; 
v___x_1103_ = 4194304;
v___x_1104_ = lean_uint32_lor(v___y_131_, v___x_1103_);
return v___x_1104_;
}
}
v___jp_1105_:
{
uint32_t v___x_1106_; uint32_t v___x_1107_; uint32_t v___x_1108_; uint32_t v___x_1109_; uint8_t v___x_1110_; 
v___x_1106_ = 23;
v___x_1107_ = lean_uint32_shift_right(v___y_131_, v___x_1106_);
v___x_1108_ = 255;
v___x_1109_ = lean_uint32_land(v___x_1107_, v___x_1108_);
v___x_1110_ = lean_uint32_dec_eq(v___x_1109_, v___x_1108_);
if (v___x_1110_ == 0)
{
v___y_1101_ = v___x_1110_;
goto v___jp_1100_;
}
else
{
uint32_t v___x_1111_; uint32_t v___x_1112_; uint32_t v___x_1113_; uint8_t v___x_1114_; 
v___x_1111_ = 8388607;
v___x_1112_ = lean_uint32_land(v___y_131_, v___x_1111_);
v___x_1113_ = 0;
v___x_1114_ = lean_uint32_dec_eq(v___x_1112_, v___x_1113_);
if (v___x_1114_ == 0)
{
v___y_1101_ = v___x_1110_;
goto v___jp_1100_;
}
else
{
uint32_t v___x_1115_; 
v___x_1115_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_1115_;
}
}
}
v___jp_1116_:
{
if (v___y_1117_ == 0)
{
goto v___jp_1105_;
}
else
{
uint32_t v___x_1118_; uint32_t v___x_1119_; 
v___x_1118_ = 4194304;
v___x_1119_ = lean_uint32_lor(v___y_130_, v___x_1118_);
return v___x_1119_;
}
}
v___jp_1120_:
{
uint32_t v___x_1121_; uint32_t v___x_1122_; uint32_t v___x_1123_; uint32_t v___x_1124_; uint8_t v___x_1125_; 
v___x_1121_ = 23;
v___x_1122_ = lean_uint32_shift_right(v___y_130_, v___x_1121_);
v___x_1123_ = 255;
v___x_1124_ = lean_uint32_land(v___x_1122_, v___x_1123_);
v___x_1125_ = lean_uint32_dec_eq(v___x_1124_, v___x_1123_);
if (v___x_1125_ == 0)
{
v___y_1117_ = v___x_1125_;
goto v___jp_1116_;
}
else
{
uint32_t v___x_1126_; uint32_t v___x_1127_; uint32_t v___x_1128_; uint8_t v___x_1129_; 
v___x_1126_ = 8388607;
v___x_1127_ = lean_uint32_land(v___y_130_, v___x_1126_);
v___x_1128_ = 0;
v___x_1129_ = lean_uint32_dec_eq(v___x_1127_, v___x_1128_);
if (v___x_1129_ == 0)
{
v___y_1117_ = v___x_1125_;
goto v___jp_1116_;
}
else
{
goto v___jp_1105_;
}
}
}
v___jp_1130_:
{
if (v___y_1131_ == 0)
{
goto v___jp_1120_;
}
else
{
uint32_t v___x_1132_; uint32_t v___x_1133_; uint32_t v___x_1134_; uint8_t v___x_1135_; 
v___x_1132_ = 4194304;
v___x_1133_ = lean_uint32_land(v___y_131_, v___x_1132_);
v___x_1134_ = 0;
v___x_1135_ = lean_uint32_dec_eq(v___x_1133_, v___x_1134_);
if (v___x_1135_ == 0)
{
goto v___jp_1120_;
}
else
{
uint32_t v___x_1136_; 
v___x_1136_ = lean_uint32_lor(v___y_131_, v___x_1132_);
return v___x_1136_;
}
}
}
v___jp_1137_:
{
uint32_t v___x_1138_; uint32_t v___x_1139_; uint32_t v___x_1140_; uint32_t v___x_1141_; uint8_t v___x_1142_; 
v___x_1138_ = 23;
v___x_1139_ = lean_uint32_shift_right(v___y_131_, v___x_1138_);
v___x_1140_ = 255;
v___x_1141_ = lean_uint32_land(v___x_1139_, v___x_1140_);
v___x_1142_ = lean_uint32_dec_eq(v___x_1141_, v___x_1140_);
if (v___x_1142_ == 0)
{
v___y_1131_ = v___x_1142_;
goto v___jp_1130_;
}
else
{
uint32_t v___x_1143_; uint32_t v___x_1144_; uint32_t v___x_1145_; uint8_t v___x_1146_; 
v___x_1143_ = 8388607;
v___x_1144_ = lean_uint32_land(v___y_131_, v___x_1143_);
v___x_1145_ = 0;
v___x_1146_ = lean_uint32_dec_eq(v___x_1144_, v___x_1145_);
if (v___x_1146_ == 0)
{
v___y_1131_ = v___x_1142_;
goto v___jp_1130_;
}
else
{
goto v___jp_1120_;
}
}
}
v___jp_1147_:
{
if (v___y_1148_ == 0)
{
goto v___jp_1137_;
}
else
{
uint32_t v___x_1149_; uint32_t v___x_1150_; uint32_t v___x_1151_; uint8_t v___x_1152_; 
v___x_1149_ = 4194304;
v___x_1150_ = lean_uint32_land(v___y_130_, v___x_1149_);
v___x_1151_ = 0;
v___x_1152_ = lean_uint32_dec_eq(v___x_1150_, v___x_1151_);
if (v___x_1152_ == 0)
{
goto v___jp_1137_;
}
else
{
uint32_t v___x_1153_; 
v___x_1153_ = lean_uint32_lor(v___y_130_, v___x_1149_);
return v___x_1153_;
}
}
}
v___jp_1154_:
{
float v_result_1157_; uint8_t v___x_1158_; 
v_result_1157_ = lean_float32_mul(v___y_1155_, v___y_1156_);
v___x_1158_ = lean_float32_beq(v_result_1157_, v_result_1157_);
if (v___x_1158_ == 0)
{
uint32_t v___x_1159_; uint32_t v___x_1160_; uint32_t v___x_1161_; uint32_t v___x_1162_; uint8_t v___x_1163_; 
v___x_1159_ = 23;
v___x_1160_ = lean_uint32_shift_right(v___y_130_, v___x_1159_);
v___x_1161_ = 255;
v___x_1162_ = lean_uint32_land(v___x_1160_, v___x_1161_);
v___x_1163_ = lean_uint32_dec_eq(v___x_1162_, v___x_1161_);
if (v___x_1163_ == 0)
{
v___y_1148_ = v___x_1163_;
goto v___jp_1147_;
}
else
{
uint32_t v___x_1164_; uint32_t v___x_1165_; uint32_t v___x_1166_; uint8_t v___x_1167_; 
v___x_1164_ = 8388607;
v___x_1165_ = lean_uint32_land(v___y_130_, v___x_1164_);
v___x_1166_ = 0;
v___x_1167_ = lean_uint32_dec_eq(v___x_1165_, v___x_1166_);
if (v___x_1167_ == 0)
{
v___y_1148_ = v___x_1163_;
goto v___jp_1147_;
}
else
{
goto v___jp_1137_;
}
}
}
else
{
uint32_t v___x_1168_; 
v___x_1168_ = lean_float32_to_bits(v_result_1157_);
return v___x_1168_;
}
}
v___jp_1169_:
{
if (v___y_1171_ == 0)
{
float v___x_1172_; 
v___x_1172_ = lean_float32_of_bits(v___y_131_);
v___y_1155_ = v___y_1170_;
v___y_1156_ = v___x_1172_;
goto v___jp_1154_;
}
else
{
uint32_t v___x_1173_; uint32_t v___x_1174_; uint32_t v___x_1175_; uint32_t v___x_1176_; float v___x_1177_; lean_object* v___x_1178_; uint32_t v___x_1179_; uint32_t v___x_1180_; lean_object* v___x_1181_; lean_object* v___x_1182_; float v___x_1183_; float v___x_1184_; 
v___x_1173_ = 8388607;
v___x_1174_ = lean_uint32_land(v___y_131_, v___x_1173_);
v___x_1175_ = 8388608;
v___x_1176_ = lean_uint32_lor(v___x_1174_, v___x_1175_);
v___x_1177_ = lean_uint32_to_float32(v___x_1176_);
v___x_1178_ = lp_competition_R2W01b_scaleTable;
v___x_1179_ = 23;
v___x_1180_ = lean_uint32_shift_right(v___y_131_, v___x_1179_);
v___x_1181_ = lean_uint32_to_nat(v___x_1180_);
v___x_1182_ = lean_array_fget_borrowed(v___x_1178_, v___x_1181_);
lean_dec(v___x_1181_);
v___x_1183_ = lean_unbox_float32(v___x_1182_);
v___x_1184_ = lean_float32_mul(v___x_1177_, v___x_1183_);
v___y_1155_ = v___y_1170_;
v___y_1156_ = v___x_1184_;
goto v___jp_1154_;
}
}
v___jp_1185_:
{
uint32_t v___x_1187_; uint32_t v_a_1188_; uint32_t v___x_1189_; uint32_t v___x_1190_; uint32_t v___x_1191_; uint8_t v___x_1192_; 
v___x_1187_ = 2147483647;
v_a_1188_ = lean_uint32_land(v___y_131_, v___x_1187_);
v___x_1189_ = 201326591;
v___x_1190_ = 1;
v___x_1191_ = lean_uint32_sub(v_a_1188_, v___x_1190_);
v___x_1192_ = lean_uint32_dec_le(v___x_1189_, v___x_1191_);
if (v___x_1192_ == 0)
{
v___y_1170_ = v___y_1186_;
v___y_1171_ = v___x_1192_;
goto v___jp_1169_;
}
else
{
uint32_t v___x_1193_; uint8_t v___x_1194_; 
v___x_1193_ = 2139095040;
v___x_1194_ = lean_uint32_dec_lt(v_a_1188_, v___x_1193_);
v___y_1170_ = v___y_1186_;
v___y_1171_ = v___x_1194_;
goto v___jp_1169_;
}
}
v___jp_1195_:
{
if (v___y_1197_ == 0)
{
float v___x_1198_; 
v___x_1198_ = lean_float32_of_bits(v___y_130_);
v___y_1186_ = v___x_1198_;
goto v___jp_1185_;
}
else
{
uint32_t v___x_1199_; uint32_t v___x_1200_; uint32_t v___x_1201_; uint32_t v___x_1202_; float v___x_1203_; lean_object* v___x_1204_; lean_object* v___x_1205_; lean_object* v___x_1206_; float v___x_1207_; float v___x_1208_; 
v___x_1199_ = 8388607;
v___x_1200_ = lean_uint32_land(v___y_130_, v___x_1199_);
v___x_1201_ = 8388608;
v___x_1202_ = lean_uint32_lor(v___x_1200_, v___x_1201_);
v___x_1203_ = lean_uint32_to_float32(v___x_1202_);
v___x_1204_ = lp_competition_R2W01b_scaleTable;
v___x_1205_ = lean_uint32_to_nat(v___y_1196_);
v___x_1206_ = lean_array_fget_borrowed(v___x_1204_, v___x_1205_);
lean_dec(v___x_1205_);
v___x_1207_ = lean_unbox_float32(v___x_1206_);
v___x_1208_ = lean_float32_mul(v___x_1203_, v___x_1207_);
v___y_1186_ = v___x_1208_;
goto v___jp_1185_;
}
}
v___jp_1209_:
{
if (v___y_1210_ == 0)
{
uint32_t v___x_1211_; 
v___x_1211_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_1211_;
}
else
{
uint32_t v___x_1212_; uint32_t v___x_1213_; 
v___x_1212_ = 4194304;
v___x_1213_ = lean_uint32_lor(v___y_131_, v___x_1212_);
return v___x_1213_;
}
}
v___jp_1214_:
{
uint32_t v___x_1215_; uint32_t v___x_1216_; uint32_t v___x_1217_; uint32_t v___x_1218_; uint8_t v___x_1219_; 
v___x_1215_ = 23;
v___x_1216_ = lean_uint32_shift_right(v___y_131_, v___x_1215_);
v___x_1217_ = 255;
v___x_1218_ = lean_uint32_land(v___x_1216_, v___x_1217_);
v___x_1219_ = lean_uint32_dec_eq(v___x_1218_, v___x_1217_);
if (v___x_1219_ == 0)
{
v___y_1210_ = v___x_1219_;
goto v___jp_1209_;
}
else
{
uint32_t v___x_1220_; uint32_t v___x_1221_; uint32_t v___x_1222_; uint8_t v___x_1223_; 
v___x_1220_ = 8388607;
v___x_1221_ = lean_uint32_land(v___y_131_, v___x_1220_);
v___x_1222_ = 0;
v___x_1223_ = lean_uint32_dec_eq(v___x_1221_, v___x_1222_);
if (v___x_1223_ == 0)
{
v___y_1210_ = v___x_1219_;
goto v___jp_1209_;
}
else
{
uint32_t v___x_1224_; 
v___x_1224_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_1224_;
}
}
}
v___jp_1225_:
{
if (v___y_1226_ == 0)
{
goto v___jp_1214_;
}
else
{
uint32_t v___x_1227_; uint32_t v___x_1228_; 
v___x_1227_ = 4194304;
v___x_1228_ = lean_uint32_lor(v___y_130_, v___x_1227_);
return v___x_1228_;
}
}
v___jp_1229_:
{
uint32_t v___x_1230_; uint32_t v___x_1231_; uint32_t v___x_1232_; uint32_t v___x_1233_; uint8_t v___x_1234_; 
v___x_1230_ = 23;
v___x_1231_ = lean_uint32_shift_right(v___y_130_, v___x_1230_);
v___x_1232_ = 255;
v___x_1233_ = lean_uint32_land(v___x_1231_, v___x_1232_);
v___x_1234_ = lean_uint32_dec_eq(v___x_1233_, v___x_1232_);
if (v___x_1234_ == 0)
{
v___y_1226_ = v___x_1234_;
goto v___jp_1225_;
}
else
{
uint32_t v___x_1235_; uint32_t v___x_1236_; uint32_t v___x_1237_; uint8_t v___x_1238_; 
v___x_1235_ = 8388607;
v___x_1236_ = lean_uint32_land(v___y_130_, v___x_1235_);
v___x_1237_ = 0;
v___x_1238_ = lean_uint32_dec_eq(v___x_1236_, v___x_1237_);
if (v___x_1238_ == 0)
{
v___y_1226_ = v___x_1234_;
goto v___jp_1225_;
}
else
{
goto v___jp_1214_;
}
}
}
v___jp_1239_:
{
if (v___y_1240_ == 0)
{
goto v___jp_1229_;
}
else
{
uint32_t v___x_1241_; uint32_t v___x_1242_; uint32_t v___x_1243_; uint8_t v___x_1244_; 
v___x_1241_ = 4194304;
v___x_1242_ = lean_uint32_land(v___y_131_, v___x_1241_);
v___x_1243_ = 0;
v___x_1244_ = lean_uint32_dec_eq(v___x_1242_, v___x_1243_);
if (v___x_1244_ == 0)
{
goto v___jp_1229_;
}
else
{
uint32_t v___x_1245_; 
v___x_1245_ = lean_uint32_lor(v___y_131_, v___x_1241_);
return v___x_1245_;
}
}
}
v___jp_1246_:
{
uint32_t v___x_1247_; uint32_t v___x_1248_; uint32_t v___x_1249_; uint32_t v___x_1250_; uint8_t v___x_1251_; 
v___x_1247_ = 23;
v___x_1248_ = lean_uint32_shift_right(v___y_131_, v___x_1247_);
v___x_1249_ = 255;
v___x_1250_ = lean_uint32_land(v___x_1248_, v___x_1249_);
v___x_1251_ = lean_uint32_dec_eq(v___x_1250_, v___x_1249_);
if (v___x_1251_ == 0)
{
v___y_1240_ = v___x_1251_;
goto v___jp_1239_;
}
else
{
uint32_t v___x_1252_; uint32_t v___x_1253_; uint32_t v___x_1254_; uint8_t v___x_1255_; 
v___x_1252_ = 8388607;
v___x_1253_ = lean_uint32_land(v___y_131_, v___x_1252_);
v___x_1254_ = 0;
v___x_1255_ = lean_uint32_dec_eq(v___x_1253_, v___x_1254_);
if (v___x_1255_ == 0)
{
v___y_1240_ = v___x_1251_;
goto v___jp_1239_;
}
else
{
goto v___jp_1229_;
}
}
}
v___jp_1256_:
{
if (v___y_1257_ == 0)
{
goto v___jp_1246_;
}
else
{
uint32_t v___x_1258_; uint32_t v___x_1259_; uint32_t v___x_1260_; uint8_t v___x_1261_; 
v___x_1258_ = 4194304;
v___x_1259_ = lean_uint32_land(v___y_130_, v___x_1258_);
v___x_1260_ = 0;
v___x_1261_ = lean_uint32_dec_eq(v___x_1259_, v___x_1260_);
if (v___x_1261_ == 0)
{
goto v___jp_1246_;
}
else
{
uint32_t v___x_1262_; 
v___x_1262_ = lean_uint32_lor(v___y_130_, v___x_1258_);
return v___x_1262_;
}
}
}
v___jp_1263_:
{
float v_result_1266_; uint8_t v___x_1267_; 
v_result_1266_ = lean_float32_mul(v___y_1264_, v___y_1265_);
v___x_1267_ = lean_float32_beq(v_result_1266_, v_result_1266_);
if (v___x_1267_ == 0)
{
uint32_t v___x_1268_; uint32_t v___x_1269_; uint32_t v___x_1270_; uint32_t v___x_1271_; uint8_t v___x_1272_; 
v___x_1268_ = 23;
v___x_1269_ = lean_uint32_shift_right(v___y_130_, v___x_1268_);
v___x_1270_ = 255;
v___x_1271_ = lean_uint32_land(v___x_1269_, v___x_1270_);
v___x_1272_ = lean_uint32_dec_eq(v___x_1271_, v___x_1270_);
if (v___x_1272_ == 0)
{
v___y_1257_ = v___x_1272_;
goto v___jp_1256_;
}
else
{
uint32_t v___x_1273_; uint32_t v___x_1274_; uint32_t v___x_1275_; uint8_t v___x_1276_; 
v___x_1273_ = 8388607;
v___x_1274_ = lean_uint32_land(v___y_130_, v___x_1273_);
v___x_1275_ = 0;
v___x_1276_ = lean_uint32_dec_eq(v___x_1274_, v___x_1275_);
if (v___x_1276_ == 0)
{
v___y_1257_ = v___x_1272_;
goto v___jp_1256_;
}
else
{
goto v___jp_1246_;
}
}
}
else
{
uint32_t v___x_1277_; 
v___x_1277_ = lean_float32_to_bits(v_result_1266_);
return v___x_1277_;
}
}
v___jp_1278_:
{
if (v___y_1280_ == 0)
{
float v___x_1281_; 
v___x_1281_ = lean_float32_of_bits(v___y_131_);
v___y_1264_ = v___y_1279_;
v___y_1265_ = v___x_1281_;
goto v___jp_1263_;
}
else
{
uint32_t v___x_1282_; uint32_t v___x_1283_; uint32_t v___x_1284_; uint32_t v___x_1285_; float v___x_1286_; lean_object* v___x_1287_; uint32_t v___x_1288_; uint32_t v___x_1289_; lean_object* v___x_1290_; lean_object* v___x_1291_; float v___x_1292_; float v___x_1293_; 
v___x_1282_ = 8388607;
v___x_1283_ = lean_uint32_land(v___y_131_, v___x_1282_);
v___x_1284_ = 8388608;
v___x_1285_ = lean_uint32_lor(v___x_1283_, v___x_1284_);
v___x_1286_ = lean_uint32_to_float32(v___x_1285_);
v___x_1287_ = lp_competition_R2W01b_scaleTable;
v___x_1288_ = 23;
v___x_1289_ = lean_uint32_shift_right(v___y_131_, v___x_1288_);
v___x_1290_ = lean_uint32_to_nat(v___x_1289_);
v___x_1291_ = lean_array_fget_borrowed(v___x_1287_, v___x_1290_);
lean_dec(v___x_1290_);
v___x_1292_ = lean_unbox_float32(v___x_1291_);
v___x_1293_ = lean_float32_mul(v___x_1286_, v___x_1292_);
v___y_1264_ = v___y_1279_;
v___y_1265_ = v___x_1293_;
goto v___jp_1263_;
}
}
v___jp_1294_:
{
uint32_t v___x_1296_; uint32_t v_a_1297_; uint32_t v___x_1298_; uint32_t v___x_1299_; uint32_t v___x_1300_; uint8_t v___x_1301_; 
v___x_1296_ = 2147483647;
v_a_1297_ = lean_uint32_land(v___y_131_, v___x_1296_);
v___x_1298_ = 201326591;
v___x_1299_ = 1;
v___x_1300_ = lean_uint32_sub(v_a_1297_, v___x_1299_);
v___x_1301_ = lean_uint32_dec_le(v___x_1298_, v___x_1300_);
if (v___x_1301_ == 0)
{
v___y_1279_ = v___y_1295_;
v___y_1280_ = v___x_1301_;
goto v___jp_1278_;
}
else
{
uint32_t v___x_1302_; uint8_t v___x_1303_; 
v___x_1302_ = 2139095040;
v___x_1303_ = lean_uint32_dec_lt(v_a_1297_, v___x_1302_);
v___y_1279_ = v___y_1295_;
v___y_1280_ = v___x_1303_;
goto v___jp_1278_;
}
}
v___jp_1304_:
{
if (v___y_1306_ == 0)
{
float v___x_1307_; 
v___x_1307_ = lean_float32_of_bits(v___y_130_);
v___y_1295_ = v___x_1307_;
goto v___jp_1294_;
}
else
{
uint32_t v___x_1308_; uint32_t v___x_1309_; uint32_t v___x_1310_; uint32_t v___x_1311_; float v___x_1312_; lean_object* v___x_1313_; lean_object* v___x_1314_; lean_object* v___x_1315_; float v___x_1316_; float v___x_1317_; 
v___x_1308_ = 8388607;
v___x_1309_ = lean_uint32_land(v___y_130_, v___x_1308_);
v___x_1310_ = 8388608;
v___x_1311_ = lean_uint32_lor(v___x_1309_, v___x_1310_);
v___x_1312_ = lean_uint32_to_float32(v___x_1311_);
v___x_1313_ = lp_competition_R2W01b_scaleTable;
v___x_1314_ = lean_uint32_to_nat(v___y_1305_);
v___x_1315_ = lean_array_fget_borrowed(v___x_1313_, v___x_1314_);
lean_dec(v___x_1314_);
v___x_1316_ = lean_unbox_float32(v___x_1315_);
v___x_1317_ = lean_float32_mul(v___x_1312_, v___x_1316_);
v___y_1295_ = v___x_1317_;
goto v___jp_1294_;
}
}
v___jp_1318_:
{
if (v___y_1319_ == 0)
{
uint32_t v___x_1320_; uint32_t v___x_1321_; uint32_t v___x_1322_; uint32_t v_ex_1323_; uint32_t v___x_1324_; uint32_t v_ey_1325_; uint32_t v___x_1326_; uint32_t v___x_1327_; uint8_t v___x_1328_; 
v___x_1320_ = 23;
v___x_1321_ = lean_uint32_shift_right(v___y_130_, v___x_1320_);
v___x_1322_ = 255;
v_ex_1323_ = lean_uint32_land(v___x_1321_, v___x_1322_);
v___x_1324_ = lean_uint32_shift_right(v___y_131_, v___x_1320_);
v_ey_1325_ = lean_uint32_land(v___x_1324_, v___x_1322_);
v___x_1326_ = lean_uint32_add(v_ex_1323_, v_ey_1325_);
v___x_1327_ = 128;
v___x_1328_ = lean_uint32_dec_lt(v___x_1326_, v___x_1327_);
if (v___x_1328_ == 0)
{
uint32_t v___x_1329_; uint32_t v_a_1330_; uint32_t v___x_1331_; uint32_t v___x_1332_; uint32_t v___x_1333_; uint8_t v___x_1334_; 
v___x_1329_ = 2147483647;
v_a_1330_ = lean_uint32_land(v___y_130_, v___x_1329_);
v___x_1331_ = 201326591;
v___x_1332_ = 1;
v___x_1333_ = lean_uint32_sub(v_a_1330_, v___x_1332_);
v___x_1334_ = lean_uint32_dec_le(v___x_1331_, v___x_1333_);
if (v___x_1334_ == 0)
{
v___y_1305_ = v___x_1321_;
v___y_1306_ = v___x_1334_;
goto v___jp_1304_;
}
else
{
uint32_t v___x_1335_; uint8_t v___x_1336_; 
v___x_1335_ = 2139095040;
v___x_1336_ = lean_uint32_dec_lt(v_a_1330_, v___x_1335_);
v___y_1305_ = v___x_1321_;
v___y_1306_ = v___x_1336_;
goto v___jp_1304_;
}
}
else
{
uint32_t v___x_1337_; uint32_t v___x_1338_; uint32_t v___x_1339_; uint8_t v___x_1340_; 
v___x_1337_ = 4278190080;
v___x_1338_ = 1;
v___x_1339_ = lean_uint32_shift_left(v___y_130_, v___x_1338_);
v___x_1340_ = lean_uint32_dec_le(v___x_1337_, v___x_1339_);
if (v___x_1340_ == 0)
{
uint32_t v___x_1341_; uint8_t v___x_1342_; 
v___x_1341_ = lean_uint32_shift_left(v___y_131_, v___x_1338_);
v___x_1342_ = lean_uint32_dec_le(v___x_1337_, v___x_1341_);
v___y_1086_ = v___x_1320_;
v___y_1087_ = v_ex_1323_;
v___y_1088_ = v___x_1322_;
v___y_1089_ = v_ey_1325_;
v___y_1090_ = v___x_1342_;
goto v___jp_1085_;
}
else
{
v___y_1086_ = v___x_1320_;
v___y_1087_ = v_ex_1323_;
v___y_1088_ = v___x_1322_;
v___y_1089_ = v_ey_1325_;
v___y_1090_ = v___x_1340_;
goto v___jp_1085_;
}
}
}
else
{
uint32_t v___x_1343_; uint32_t v___x_1344_; uint32_t v___x_1345_; uint32_t v___x_1346_; uint32_t v___x_1347_; uint32_t v___x_1348_; uint32_t v___x_1349_; uint32_t v___x_1350_; uint32_t v___x_1351_; uint32_t v___x_1352_; uint8_t v___x_1353_; 
v___x_1343_ = 23;
v___x_1344_ = lean_uint32_shift_right(v___y_130_, v___x_1343_);
v___x_1345_ = 255;
v___x_1346_ = lean_uint32_land(v___x_1344_, v___x_1345_);
v___x_1347_ = lean_uint32_shift_right(v___y_131_, v___x_1343_);
v___x_1348_ = lean_uint32_land(v___x_1347_, v___x_1345_);
v___x_1349_ = lean_uint32_add(v___x_1346_, v___x_1348_);
v___x_1350_ = 128;
v___x_1351_ = lean_uint32_sub(v___x_1349_, v___x_1350_);
v___x_1352_ = 252;
v___x_1353_ = lean_uint32_dec_le(v___x_1351_, v___x_1352_);
if (v___x_1353_ == 0)
{
uint8_t v___x_1354_; 
v___x_1354_ = lean_uint32_dec_lt(v___x_1349_, v___x_1350_);
if (v___x_1354_ == 0)
{
uint32_t v___x_1355_; uint32_t v_a_1356_; uint32_t v___x_1357_; uint32_t v___x_1358_; uint32_t v___x_1359_; uint8_t v___x_1360_; 
v___x_1355_ = 2147483647;
v_a_1356_ = lean_uint32_land(v___y_130_, v___x_1355_);
v___x_1357_ = 201326591;
v___x_1358_ = 1;
v___x_1359_ = lean_uint32_sub(v_a_1356_, v___x_1358_);
v___x_1360_ = lean_uint32_dec_le(v___x_1357_, v___x_1359_);
if (v___x_1360_ == 0)
{
v___y_1196_ = v___x_1344_;
v___y_1197_ = v___x_1360_;
goto v___jp_1195_;
}
else
{
uint32_t v___x_1361_; uint8_t v___x_1362_; 
v___x_1361_ = 2139095040;
v___x_1362_ = lean_uint32_dec_lt(v_a_1356_, v___x_1361_);
v___y_1196_ = v___x_1344_;
v___y_1197_ = v___x_1362_;
goto v___jp_1195_;
}
}
else
{
uint32_t v___x_1363_; uint32_t v___x_1364_; uint32_t v___x_1365_; uint8_t v___x_1366_; 
v___x_1363_ = 4278190080;
v___x_1364_ = 1;
v___x_1365_ = lean_uint32_shift_left(v___y_130_, v___x_1364_);
v___x_1366_ = lean_uint32_dec_le(v___x_1363_, v___x_1365_);
if (v___x_1366_ == 0)
{
uint32_t v___x_1367_; uint8_t v___x_1368_; 
v___x_1367_ = lean_uint32_shift_left(v___y_131_, v___x_1364_);
v___x_1368_ = lean_uint32_dec_le(v___x_1363_, v___x_1367_);
v___y_1030_ = v___y_1319_;
v___y_1031_ = v___x_1343_;
v___y_1032_ = v___x_1346_;
v___y_1033_ = v___x_1345_;
v___y_1034_ = v___x_1348_;
v___y_1035_ = v___x_1368_;
goto v___jp_1029_;
}
else
{
v___y_1030_ = v___y_1319_;
v___y_1031_ = v___x_1343_;
v___y_1032_ = v___x_1346_;
v___y_1033_ = v___x_1345_;
v___y_1034_ = v___x_1348_;
v___y_1035_ = v___x_1366_;
goto v___jp_1029_;
}
}
}
else
{
uint32_t v___x_1369_; uint32_t v___x_1370_; uint32_t v___x_1371_; uint32_t v___x_1372_; float v___x_1373_; uint32_t v___x_1374_; uint32_t v___x_1375_; float v___x_1376_; float v___x_1377_; uint32_t v_mid_1378_; uint32_t v___x_1379_; uint8_t v___x_1380_; uint8_t v___x_1381_; 
v___x_1369_ = 8388607;
v___x_1370_ = lean_uint32_land(v___y_130_, v___x_1369_);
v___x_1371_ = 8388608;
v___x_1372_ = lean_uint32_lor(v___x_1370_, v___x_1371_);
v___x_1373_ = lean_uint32_to_float32(v___x_1372_);
v___x_1374_ = lean_uint32_land(v___y_131_, v___x_1369_);
v___x_1375_ = lean_uint32_lor(v___x_1374_, v___x_1371_);
v___x_1376_ = lean_uint32_to_float32(v___x_1375_);
v___x_1377_ = lean_float32_mul(v___x_1373_, v___x_1376_);
v_mid_1378_ = lean_float32_to_bits(v___x_1377_);
v___x_1379_ = 2147483648;
v___x_1380_ = lean_uint32_dec_le(v___x_1379_, v___y_130_);
v___x_1381_ = lean_uint32_dec_le(v___x_1379_, v___y_131_);
if (v___x_1380_ == 0)
{
if (v___x_1381_ == 0)
{
v___y_162_ = v_mid_1378_;
v___y_163_ = v___x_1343_;
v___y_164_ = v___x_1369_;
v___y_165_ = v___x_1346_;
v___y_166_ = v___x_1345_;
v___y_167_ = v___x_1353_;
v___y_168_ = v___x_1348_;
v___y_169_ = v___x_1353_;
goto v___jp_161_;
}
else
{
v___y_162_ = v_mid_1378_;
v___y_163_ = v___x_1343_;
v___y_164_ = v___x_1369_;
v___y_165_ = v___x_1346_;
v___y_166_ = v___x_1345_;
v___y_167_ = v___x_1353_;
v___y_168_ = v___x_1348_;
v___y_169_ = v___x_1380_;
goto v___jp_161_;
}
}
else
{
v___y_162_ = v_mid_1378_;
v___y_163_ = v___x_1343_;
v___y_164_ = v___x_1369_;
v___y_165_ = v___x_1346_;
v___y_166_ = v___x_1345_;
v___y_167_ = v___x_1353_;
v___y_168_ = v___x_1348_;
v___y_169_ = v___x_1381_;
goto v___jp_161_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_1394_, lean_object* v___y_1395_){
_start:
{
uint32_t v___y_8719__boxed_1396_; uint32_t v___y_8720__boxed_1397_; uint32_t v_res_1398_; lean_object* v_r_1399_; 
v___y_8719__boxed_1396_ = lean_unbox_uint32(v___y_1394_);
lean_dec(v___y_1394_);
v___y_8720__boxed_1397_ = lean_unbox_uint32(v___y_1395_);
lean_dec(v___y_1395_);
v_res_1398_ = lp_competition_main___lam__1(v___y_8719__boxed_1396_, v___y_8720__boxed_1397_);
v_r_1399_ = lean_box_uint32(v_res_1398_);
return v_r_1399_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_1400_, uint32_t v___y_1401_){
_start:
{
uint32_t v___y_1403_; uint32_t v___y_1404_; uint32_t v___y_1405_; uint32_t v___y_1406_; uint32_t v___y_1407_; uint32_t v___y_1408_; uint32_t v___y_1415_; uint32_t v___y_1416_; uint32_t v___y_1417_; uint32_t v___y_1418_; uint32_t v___y_1419_; uint32_t v___y_1420_; uint8_t v___y_1421_; uint32_t v___y_1432_; uint8_t v___y_1433_; uint32_t v___y_1434_; uint32_t v___y_1435_; uint32_t v___y_1436_; uint32_t v___y_1437_; uint32_t v___y_1438_; uint8_t v___y_1439_; uint32_t v___y_1442_; uint32_t v___y_1443_; uint32_t v___y_1444_; uint32_t v___y_1448_; uint32_t v___y_1449_; uint32_t v___y_1450_; uint32_t v___y_1451_; uint32_t v___y_1452_; uint32_t v___y_1453_; uint8_t v___y_1460_; uint32_t v___y_1461_; uint32_t v___y_1462_; uint32_t v___y_1463_; uint32_t v___y_1464_; uint32_t v___y_1465_; uint32_t v___y_1469_; uint8_t v___y_1470_; uint64_t v___y_1471_; uint32_t v___y_1472_; uint64_t v___y_1473_; uint32_t v___y_1474_; uint64_t v___y_1475_; uint8_t v___y_1485_; uint32_t v___y_1486_; uint64_t v___y_1487_; uint64_t v___y_1488_; uint32_t v___y_1489_; uint32_t v___y_1490_; uint8_t v___y_1491_; uint64_t v___y_1492_; uint32_t v___y_1499_; uint8_t v___y_1500_; uint64_t v___y_1501_; uint32_t v___y_1502_; uint32_t v___y_1503_; uint64_t v___y_1504_; uint64_t v___y_1505_; uint32_t v___y_1511_; uint32_t v___y_1512_; uint32_t v___y_1513_; uint32_t v___y_1517_; uint32_t v___y_1518_; uint32_t v___y_1519_; uint32_t v___y_1523_; uint32_t v___y_1524_; uint32_t v___y_1525_; uint32_t v___y_1526_; uint32_t v___y_1527_; uint32_t v___y_1528_; uint32_t v___y_1535_; uint32_t v___y_1536_; uint32_t v___y_1537_; uint8_t v___y_1538_; uint32_t v___y_1539_; uint32_t v___y_1540_; uint32_t v___y_1544_; uint32_t v___y_1545_; uint64_t v___y_1546_; uint32_t v___y_1547_; uint64_t v___y_1548_; uint8_t v___y_1549_; uint64_t v___y_1550_; uint32_t v___y_1560_; uint32_t v___y_1561_; uint32_t v___y_1562_; uint64_t v___y_1563_; uint64_t v___y_1564_; uint8_t v___y_1565_; uint8_t v___y_1566_; uint64_t v___y_1567_; uint32_t v___y_1574_; uint32_t v___y_1575_; uint32_t v___y_1576_; uint64_t v___y_1577_; uint64_t v___y_1578_; uint8_t v___y_1579_; uint64_t v___y_1580_; uint32_t v___y_1586_; uint32_t v___y_1587_; uint32_t v___y_1588_; uint32_t v___y_1592_; uint8_t v___y_1596_; uint32_t v___y_1597_; uint64_t v___y_1598_; uint64_t v___y_1599_; uint8_t v___y_1611_; uint32_t v___y_1612_; uint64_t v___y_1613_; uint32_t v___y_1614_; uint32_t v___y_1615_; uint64_t v___y_1616_; uint64_t v___y_1617_; uint64_t v___y_1618_; uint32_t v___y_1673_; uint8_t v___y_1674_; uint64_t v___y_1675_; uint64_t v___y_1676_; uint32_t v___y_1677_; uint64_t v___y_1678_; uint32_t v___y_1679_; uint64_t v___y_1680_; uint64_t v___y_1681_; uint8_t v___y_1687_; uint32_t v___y_1688_; uint64_t v___y_1689_; uint64_t v___y_1690_; uint64_t v___y_1691_; uint32_t v___y_1692_; uint64_t v___y_1693_; uint32_t v___y_1694_; uint64_t v___y_1695_; uint64_t v___y_1696_; uint64_t v___y_1697_; uint32_t v___y_1702_; uint8_t v___y_1703_; uint64_t v___y_1704_; uint64_t v___y_1705_; uint32_t v___y_1706_; uint64_t v___y_1707_; uint32_t v___y_1708_; uint64_t v___y_1709_; uint64_t v___y_1710_; uint64_t v___y_1715_; uint64_t v___y_1716_; uint8_t v___y_1717_; uint32_t v___y_1718_; uint64_t v___y_1719_; uint64_t v___y_1720_; uint32_t v___y_1721_; uint32_t v___y_1722_; uint64_t v___y_1723_; uint64_t v___y_1724_; uint64_t v___y_1725_; uint32_t v___y_1730_; uint8_t v___y_1731_; uint64_t v___y_1732_; uint64_t v___y_1733_; uint32_t v___y_1734_; uint64_t v___y_1735_; uint32_t v___y_1736_; uint64_t v___y_1737_; uint64_t v___y_1738_; uint8_t v___y_1743_; uint32_t v___y_1744_; uint64_t v___y_1745_; uint64_t v___y_1746_; uint64_t v___y_1747_; uint32_t v___y_1748_; uint64_t v___y_1749_; uint32_t v___y_1750_; uint64_t v___y_1751_; uint64_t v___y_1752_; uint64_t v___y_1753_; uint32_t v___y_1758_; uint8_t v___y_1759_; uint64_t v___y_1760_; uint64_t v___y_1761_; uint32_t v___y_1762_; uint64_t v___y_1763_; uint32_t v___y_1764_; uint64_t v___y_1765_; uint64_t v___y_1766_; uint64_t v___y_1771_; uint8_t v___y_1772_; uint32_t v___y_1773_; uint64_t v___y_1774_; uint32_t v___y_1775_; uint32_t v___y_1776_; uint64_t v___y_1777_; uint64_t v___y_1778_; uint64_t v___y_1779_; uint64_t v___y_1780_; uint64_t v___y_1781_; uint64_t v___y_1786_; uint32_t v___y_1787_; uint8_t v___y_1788_; uint64_t v___y_1789_; uint32_t v___y_1790_; uint64_t v___y_1791_; uint32_t v___y_1792_; uint64_t v___y_1793_; uint64_t v___y_1794_; uint8_t v___y_1799_; uint32_t v___y_1800_; uint64_t v___y_1801_; uint64_t v___y_1802_; uint32_t v___y_1803_; uint32_t v___y_1804_; uint64_t v___y_1805_; uint64_t v___y_1806_; uint64_t v___y_1807_; uint32_t v___y_1811_; uint8_t v___y_1812_; uint32_t v___y_1813_; uint64_t v___y_1814_; uint32_t v___y_1815_; uint64_t v___y_1816_; uint32_t v___y_1825_; uint8_t v___y_1829_; uint32_t v___y_1830_; uint64_t v___y_1831_; uint64_t v___y_1832_; uint8_t v___y_1844_; uint32_t v___y_1845_; uint64_t v___y_1846_; uint64_t v___y_1847_; uint64_t v___y_1848_; uint32_t v___y_1849_; uint32_t v___y_1850_; uint64_t v___y_1851_; uint64_t v___y_1885_; uint32_t v___y_1886_; uint8_t v___y_1887_; uint32_t v___y_1888_; uint64_t v___y_1889_; uint32_t v___y_1890_; uint32_t v___y_1891_; uint64_t v___y_1892_; uint8_t v___y_1899_; uint32_t v___y_1900_; uint64_t v___y_1901_; uint32_t v___y_1902_; uint32_t v___y_1903_; uint32_t v___y_1904_; uint32_t v___y_1905_; uint64_t v___y_1906_; uint32_t v___y_1913_; uint8_t v___y_1914_; uint32_t v___y_1915_; uint32_t v___y_1916_; uint32_t v___y_1917_; uint32_t v___y_1918_; uint32_t v___y_1919_; uint64_t v___y_1920_; uint32_t v___y_1928_; uint32_t v___y_1932_; uint64_t v___y_1933_; uint8_t v___y_1934_; uint64_t v___y_1935_; uint32_t v___y_1947_; uint32_t v___y_1951_; uint64_t v___y_1952_; uint8_t v___y_1953_; uint64_t v___y_1954_; uint32_t v___y_1966_; uint32_t v___y_1967_; uint32_t v___y_1968_; uint64_t v___y_1969_; uint64_t v___y_1970_; uint64_t v___y_1971_; uint8_t v___y_1972_; uint64_t v___y_1973_; uint32_t v___y_2028_; uint32_t v___y_2029_; uint32_t v___y_2030_; uint64_t v___y_2031_; uint64_t v___y_2032_; uint64_t v___y_2033_; uint8_t v___y_2034_; uint64_t v___y_2035_; uint64_t v___y_2036_; uint32_t v___y_2042_; uint32_t v___y_2043_; uint64_t v___y_2044_; uint32_t v___y_2045_; uint64_t v___y_2046_; uint64_t v___y_2047_; uint64_t v___y_2048_; uint64_t v___y_2049_; uint8_t v___y_2050_; uint64_t v___y_2051_; uint64_t v___y_2052_; uint32_t v___y_2057_; uint32_t v___y_2058_; uint64_t v___y_2059_; uint32_t v___y_2060_; uint64_t v___y_2061_; uint64_t v___y_2062_; uint64_t v___y_2063_; uint8_t v___y_2064_; uint64_t v___y_2065_; uint32_t v___y_2070_; uint32_t v___y_2071_; uint64_t v___y_2072_; uint32_t v___y_2073_; uint64_t v___y_2074_; uint64_t v___y_2075_; uint64_t v___y_2076_; uint64_t v___y_2077_; uint8_t v___y_2078_; uint64_t v___y_2079_; uint64_t v___y_2080_; uint32_t v___y_2085_; uint32_t v___y_2086_; uint32_t v___y_2087_; uint64_t v___y_2088_; uint64_t v___y_2089_; uint64_t v___y_2090_; uint8_t v___y_2091_; uint64_t v___y_2092_; uint64_t v___y_2093_; uint32_t v___y_2098_; uint32_t v___y_2099_; uint64_t v___y_2100_; uint64_t v___y_2101_; uint64_t v___y_2102_; uint32_t v___y_2103_; uint64_t v___y_2104_; uint64_t v___y_2105_; uint64_t v___y_2106_; uint8_t v___y_2107_; uint64_t v___y_2108_; uint32_t v___y_2113_; uint32_t v___y_2114_; uint64_t v___y_2115_; uint32_t v___y_2116_; uint64_t v___y_2117_; uint64_t v___y_2118_; uint64_t v___y_2119_; uint8_t v___y_2120_; uint64_t v___y_2121_; uint64_t v___y_2126_; uint32_t v___y_2127_; uint32_t v___y_2128_; uint32_t v___y_2129_; uint64_t v___y_2130_; uint64_t v___y_2131_; uint64_t v___y_2132_; uint64_t v___y_2133_; uint8_t v___y_2134_; uint64_t v___y_2135_; uint64_t v___y_2136_; uint32_t v___y_2141_; uint32_t v___y_2142_; uint32_t v___y_2143_; uint64_t v___y_2144_; uint64_t v___y_2145_; uint64_t v___y_2146_; uint8_t v___y_2147_; uint64_t v___y_2148_; uint64_t v___y_2149_; uint32_t v___y_2154_; uint32_t v___y_2155_; uint64_t v___y_2156_; uint32_t v___y_2157_; uint64_t v___y_2158_; uint64_t v___y_2159_; uint64_t v___y_2160_; uint8_t v___y_2161_; uint64_t v___y_2162_; uint32_t v___y_2166_; uint32_t v___y_2167_; uint32_t v___y_2168_; uint64_t v___y_2169_; uint64_t v___y_2170_; uint8_t v___y_2171_; uint32_t v___y_2180_; uint32_t v___y_2181_; uint32_t v___y_2182_; uint64_t v___y_2183_; uint64_t v___y_2184_; uint64_t v___y_2185_; uint8_t v___y_2186_; uint64_t v___y_2187_; uint32_t v___y_2221_; uint32_t v___y_2222_; uint32_t v___y_2223_; uint32_t v___y_2224_; uint64_t v___y_2225_; uint64_t v___y_2226_; uint8_t v___y_2227_; uint64_t v___y_2228_; uint32_t v___y_2235_; uint32_t v___y_2236_; uint32_t v___y_2237_; uint32_t v___y_2238_; uint64_t v___y_2239_; uint8_t v___y_2240_; uint32_t v___y_2241_; uint64_t v___y_2242_; uint32_t v___y_2249_; uint32_t v___y_2250_; uint32_t v___y_2251_; uint32_t v___y_2252_; uint32_t v___y_2253_; uint8_t v___y_2254_; uint32_t v___y_2255_; uint64_t v___y_2256_; uint32_t v___y_2264_; uint32_t v___y_2265_; uint32_t v___y_2266_; uint32_t v___y_2267_; uint8_t v___y_2268_; uint8_t v___y_2279_; uint32_t v___y_2280_; uint8_t v___y_2281_; uint32_t v___y_2282_; uint8_t v___y_2283_; uint32_t v___y_2284_; uint32_t v___y_2285_; uint8_t v___y_2286_; uint8_t v___y_2288_; uint32_t v___y_2289_; uint8_t v___y_2290_; uint32_t v___y_2291_; uint32_t v___y_2292_; uint32_t v___y_2293_; uint8_t v___y_2294_; uint32_t v___y_2300_; uint8_t v___y_2301_; uint32_t v___y_2302_; uint32_t v___y_2303_; uint32_t v___y_2304_; uint8_t v___y_2305_; uint32_t v___y_2315_; uint32_t v___y_2316_; uint32_t v___y_2317_; uint32_t v___y_2318_; uint8_t v___y_2319_; uint32_t v___y_2330_; uint32_t v___y_2331_; uint32_t v___y_2332_; uint32_t v___y_2333_; uint32_t v___y_2336_; uint32_t v___y_2337_; uint32_t v___y_2338_; uint8_t v___y_2339_; uint8_t v___y_2340_; uint32_t v___y_2341_; uint8_t v___y_2342_; uint32_t v___y_2344_; uint32_t v___y_2345_; uint32_t v___y_2346_; uint8_t v___y_2347_; uint32_t v___y_2348_; uint8_t v___y_2349_; uint32_t v___y_2356_; uint32_t v___y_2357_; uint32_t v___y_2358_; uint32_t v___y_2359_; uint8_t v___y_2360_; uint8_t v___y_2371_; uint8_t v___y_2387_; uint8_t v___y_2401_; uint8_t v___y_2418_; float v___y_2425_; float v___y_2426_; float v___y_2440_; uint8_t v___y_2441_; float v___y_2456_; uint32_t v___y_2466_; uint8_t v___y_2467_; uint8_t v___y_2480_; uint8_t v___y_2496_; uint8_t v___y_2510_; uint8_t v___y_2527_; float v___y_2534_; float v___y_2535_; float v___y_2549_; uint8_t v___y_2550_; float v___y_2565_; uint32_t v___y_2575_; uint8_t v___y_2576_; uint8_t v___y_2589_; uint32_t v___x_2652_; uint32_t v___x_2653_; uint32_t v___x_2654_; uint32_t v___x_2655_; uint32_t v___x_2656_; uint32_t v___x_2657_; uint32_t v___x_2658_; uint8_t v___x_2659_; 
v___x_2652_ = 23;
v___x_2653_ = lean_uint32_shift_right(v___y_1400_, v___x_2652_);
v___x_2654_ = 255;
v___x_2655_ = lean_uint32_land(v___x_2653_, v___x_2654_);
v___x_2656_ = 1;
v___x_2657_ = lean_uint32_sub(v___x_2655_, v___x_2656_);
v___x_2658_ = 253;
v___x_2659_ = lean_uint32_dec_le(v___x_2657_, v___x_2658_);
if (v___x_2659_ == 0)
{
v___y_2589_ = v___x_2659_;
goto v___jp_2588_;
}
else
{
uint32_t v___x_2660_; uint32_t v___x_2661_; uint32_t v___x_2662_; uint8_t v___x_2663_; 
v___x_2660_ = lean_uint32_shift_right(v___y_1401_, v___x_2652_);
v___x_2661_ = lean_uint32_land(v___x_2660_, v___x_2654_);
v___x_2662_ = lean_uint32_sub(v___x_2661_, v___x_2656_);
v___x_2663_ = lean_uint32_dec_le(v___x_2662_, v___x_2658_);
v___y_2589_ = v___x_2663_;
goto v___jp_2588_;
}
v___jp_1402_:
{
uint32_t v___x_1409_; uint32_t v___x_1410_; uint32_t v___x_1411_; uint32_t v___x_1412_; uint32_t v___x_1413_; 
v___x_1409_ = lean_uint32_land(v___y_1404_, v___y_1405_);
v___x_1410_ = lean_uint32_shift_left(v___x_1409_, v___y_1403_);
v___x_1411_ = lean_uint32_lor(v___y_1408_, v___x_1410_);
v___x_1412_ = lean_uint32_land(v___y_1406_, v___y_1407_);
v___x_1413_ = lean_uint32_lor(v___x_1411_, v___x_1412_);
return v___x_1413_;
}
v___jp_1414_:
{
uint32_t v___x_1422_; uint32_t v___x_1423_; uint32_t v___x_1424_; uint32_t v___x_1425_; uint32_t v___x_1426_; uint32_t v___x_1427_; uint32_t v___x_1428_; 
v___x_1422_ = lean_uint32_shift_right(v___y_1419_, v___y_1416_);
v___x_1423_ = lean_uint32_land(v___x_1422_, v___y_1418_);
v___x_1424_ = lean_uint32_add(v___x_1423_, v___y_1417_);
v___x_1425_ = lean_uint32_add(v___x_1424_, v___y_1415_);
v___x_1426_ = 300;
v___x_1427_ = lean_uint32_sub(v___x_1425_, v___x_1426_);
v___x_1428_ = lean_uint32_land(v___y_1419_, v___y_1420_);
if (v___y_1421_ == 0)
{
uint32_t v___x_1429_; 
v___x_1429_ = 0;
v___y_1403_ = v___y_1416_;
v___y_1404_ = v___x_1427_;
v___y_1405_ = v___y_1418_;
v___y_1406_ = v___x_1428_;
v___y_1407_ = v___y_1420_;
v___y_1408_ = v___x_1429_;
goto v___jp_1402_;
}
else
{
uint32_t v___x_1430_; 
v___x_1430_ = 2147483648;
v___y_1403_ = v___y_1416_;
v___y_1404_ = v___x_1427_;
v___y_1405_ = v___y_1418_;
v___y_1406_ = v___x_1428_;
v___y_1407_ = v___y_1420_;
v___y_1408_ = v___x_1430_;
goto v___jp_1402_;
}
}
v___jp_1431_:
{
if (v___y_1439_ == 0)
{
v___y_1415_ = v___y_1432_;
v___y_1416_ = v___y_1434_;
v___y_1417_ = v___y_1435_;
v___y_1418_ = v___y_1436_;
v___y_1419_ = v___y_1437_;
v___y_1420_ = v___y_1438_;
v___y_1421_ = v___y_1433_;
goto v___jp_1414_;
}
else
{
uint8_t v___x_1440_; 
v___x_1440_ = 0;
v___y_1415_ = v___y_1432_;
v___y_1416_ = v___y_1434_;
v___y_1417_ = v___y_1435_;
v___y_1418_ = v___y_1436_;
v___y_1419_ = v___y_1437_;
v___y_1420_ = v___y_1438_;
v___y_1421_ = v___x_1440_;
goto v___jp_1414_;
}
}
v___jp_1441_:
{
uint32_t v___x_1445_; uint32_t v___x_1446_; 
v___x_1445_ = lean_uint32_land(v___y_1443_, v___y_1442_);
v___x_1446_ = lean_uint32_lor(v___y_1444_, v___x_1445_);
return v___x_1446_;
}
v___jp_1447_:
{
uint32_t v___x_1454_; uint32_t v___x_1455_; uint32_t v___x_1456_; uint32_t v___x_1457_; uint32_t v___x_1458_; 
v___x_1454_ = lean_uint32_land(v___y_1449_, v___y_1451_);
v___x_1455_ = lean_uint32_shift_left(v___x_1454_, v___y_1450_);
v___x_1456_ = lean_uint32_lor(v___y_1453_, v___x_1455_);
v___x_1457_ = lean_uint32_land(v___y_1452_, v___y_1448_);
v___x_1458_ = lean_uint32_lor(v___x_1456_, v___x_1457_);
return v___x_1458_;
}
v___jp_1459_:
{
if (v___y_1460_ == 0)
{
uint32_t v___x_1466_; 
v___x_1466_ = 0;
v___y_1448_ = v___y_1461_;
v___y_1449_ = v___y_1462_;
v___y_1450_ = v___y_1463_;
v___y_1451_ = v___y_1464_;
v___y_1452_ = v___y_1465_;
v___y_1453_ = v___x_1466_;
goto v___jp_1447_;
}
else
{
uint32_t v___x_1467_; 
v___x_1467_ = 2147483648;
v___y_1448_ = v___y_1461_;
v___y_1449_ = v___y_1462_;
v___y_1450_ = v___y_1463_;
v___y_1451_ = v___y_1464_;
v___y_1452_ = v___y_1465_;
v___y_1453_ = v___x_1467_;
goto v___jp_1447_;
}
}
v___jp_1468_:
{
uint64_t v___x_1476_; uint64_t v_encodedExponent_1477_; uint32_t v___x_1478_; uint64_t v___x_1479_; uint8_t v___x_1480_; 
v___x_1476_ = 171ULL;
v_encodedExponent_1477_ = lean_uint64_sub(v___y_1473_, v___x_1476_);
v___x_1478_ = lean_uint64_to_uint32(v_encodedExponent_1477_);
v___x_1479_ = 8388608ULL;
v___x_1480_ = lean_uint64_dec_lt(v___y_1475_, v___x_1479_);
if (v___x_1480_ == 0)
{
uint64_t v___x_1481_; uint32_t v___x_1482_; 
v___x_1481_ = lean_uint64_sub(v___y_1475_, v___x_1479_);
v___x_1482_ = lean_uint64_to_uint32(v___x_1481_);
v___y_1460_ = v___y_1470_;
v___y_1461_ = v___y_1469_;
v___y_1462_ = v___x_1478_;
v___y_1463_ = v___y_1472_;
v___y_1464_ = v___y_1474_;
v___y_1465_ = v___x_1482_;
goto v___jp_1459_;
}
else
{
uint32_t v___x_1483_; 
v___x_1483_ = lean_uint64_to_uint32(v___y_1471_);
v___y_1460_ = v___y_1470_;
v___y_1461_ = v___y_1469_;
v___y_1462_ = v___x_1478_;
v___y_1463_ = v___y_1472_;
v___y_1464_ = v___y_1474_;
v___y_1465_ = v___x_1483_;
goto v___jp_1459_;
}
}
v___jp_1484_:
{
uint64_t v___x_1493_; uint8_t v___x_1494_; 
v___x_1493_ = 425ULL;
v___x_1494_ = lean_uint64_dec_lt(v___x_1493_, v___y_1492_);
if (v___x_1494_ == 0)
{
if (v___y_1491_ == 0)
{
v___y_1469_ = v___y_1486_;
v___y_1470_ = v___y_1485_;
v___y_1471_ = v___y_1488_;
v___y_1472_ = v___y_1489_;
v___y_1473_ = v___y_1492_;
v___y_1474_ = v___y_1490_;
v___y_1475_ = v___y_1487_;
goto v___jp_1468_;
}
else
{
uint64_t v___x_1495_; 
v___x_1495_ = 8388608ULL;
v___y_1469_ = v___y_1486_;
v___y_1470_ = v___y_1485_;
v___y_1471_ = v___y_1488_;
v___y_1472_ = v___y_1489_;
v___y_1473_ = v___y_1492_;
v___y_1474_ = v___y_1490_;
v___y_1475_ = v___x_1495_;
goto v___jp_1468_;
}
}
else
{
if (v___y_1485_ == 0)
{
uint32_t v___x_1496_; 
v___x_1496_ = 2139095040;
return v___x_1496_;
}
else
{
uint32_t v___x_1497_; 
v___x_1497_ = 4286578688;
return v___x_1497_;
}
}
}
v___jp_1498_:
{
uint64_t v___x_1506_; uint8_t v_carry_1507_; 
v___x_1506_ = 16777216ULL;
v_carry_1507_ = lean_uint64_dec_eq(v___y_1505_, v___x_1506_);
if (v_carry_1507_ == 0)
{
v___y_1485_ = v___y_1500_;
v___y_1486_ = v___y_1499_;
v___y_1487_ = v___y_1505_;
v___y_1488_ = v___y_1501_;
v___y_1489_ = v___y_1502_;
v___y_1490_ = v___y_1503_;
v___y_1491_ = v_carry_1507_;
v___y_1492_ = v___y_1504_;
goto v___jp_1484_;
}
else
{
uint64_t v___x_1508_; uint64_t v___x_1509_; 
v___x_1508_ = 1ULL;
v___x_1509_ = lean_uint64_add(v___y_1504_, v___x_1508_);
v___y_1485_ = v___y_1500_;
v___y_1486_ = v___y_1499_;
v___y_1487_ = v___y_1505_;
v___y_1488_ = v___y_1501_;
v___y_1489_ = v___y_1502_;
v___y_1490_ = v___y_1503_;
v___y_1491_ = v_carry_1507_;
v___y_1492_ = v___x_1509_;
goto v___jp_1484_;
}
}
v___jp_1510_:
{
uint32_t v___x_1514_; uint32_t v___x_1515_; 
v___x_1514_ = lean_uint32_land(v___y_1511_, v___y_1512_);
v___x_1515_ = lean_uint32_lor(v___y_1513_, v___x_1514_);
return v___x_1515_;
}
v___jp_1516_:
{
uint32_t v___x_1520_; uint32_t v___x_1521_; 
v___x_1520_ = lean_uint32_land(v___y_1517_, v___y_1518_);
v___x_1521_ = lean_uint32_lor(v___y_1519_, v___x_1520_);
return v___x_1521_;
}
v___jp_1522_:
{
uint32_t v___x_1529_; uint32_t v___x_1530_; uint32_t v___x_1531_; uint32_t v___x_1532_; uint32_t v___x_1533_; 
v___x_1529_ = lean_uint32_land(v___y_1527_, v___y_1525_);
v___x_1530_ = lean_uint32_shift_left(v___x_1529_, v___y_1524_);
v___x_1531_ = lean_uint32_lor(v___y_1528_, v___x_1530_);
v___x_1532_ = lean_uint32_land(v___y_1523_, v___y_1526_);
v___x_1533_ = lean_uint32_lor(v___x_1531_, v___x_1532_);
return v___x_1533_;
}
v___jp_1534_:
{
if (v___y_1538_ == 0)
{
uint32_t v___x_1541_; 
v___x_1541_ = 0;
v___y_1523_ = v___y_1540_;
v___y_1524_ = v___y_1536_;
v___y_1525_ = v___y_1535_;
v___y_1526_ = v___y_1537_;
v___y_1527_ = v___y_1539_;
v___y_1528_ = v___x_1541_;
goto v___jp_1522_;
}
else
{
uint32_t v___x_1542_; 
v___x_1542_ = 2147483648;
v___y_1523_ = v___y_1540_;
v___y_1524_ = v___y_1536_;
v___y_1525_ = v___y_1535_;
v___y_1526_ = v___y_1537_;
v___y_1527_ = v___y_1539_;
v___y_1528_ = v___x_1542_;
goto v___jp_1522_;
}
}
v___jp_1543_:
{
uint64_t v___x_1551_; uint64_t v_encodedExponent_1552_; uint32_t v___x_1553_; uint64_t v___x_1554_; uint8_t v___x_1555_; 
v___x_1551_ = 171ULL;
v_encodedExponent_1552_ = lean_uint64_sub(v___y_1546_, v___x_1551_);
v___x_1553_ = lean_uint64_to_uint32(v_encodedExponent_1552_);
v___x_1554_ = 8388608ULL;
v___x_1555_ = lean_uint64_dec_lt(v___y_1550_, v___x_1554_);
if (v___x_1555_ == 0)
{
uint64_t v___x_1556_; uint32_t v___x_1557_; 
v___x_1556_ = lean_uint64_sub(v___y_1550_, v___x_1554_);
v___x_1557_ = lean_uint64_to_uint32(v___x_1556_);
v___y_1535_ = v___y_1545_;
v___y_1536_ = v___y_1544_;
v___y_1537_ = v___y_1547_;
v___y_1538_ = v___y_1549_;
v___y_1539_ = v___x_1553_;
v___y_1540_ = v___x_1557_;
goto v___jp_1534_;
}
else
{
uint32_t v___x_1558_; 
v___x_1558_ = lean_uint64_to_uint32(v___y_1548_);
v___y_1535_ = v___y_1545_;
v___y_1536_ = v___y_1544_;
v___y_1537_ = v___y_1547_;
v___y_1538_ = v___y_1549_;
v___y_1539_ = v___x_1553_;
v___y_1540_ = v___x_1558_;
goto v___jp_1534_;
}
}
v___jp_1559_:
{
uint64_t v___x_1568_; uint8_t v___x_1569_; 
v___x_1568_ = 425ULL;
v___x_1569_ = lean_uint64_dec_lt(v___x_1568_, v___y_1567_);
if (v___x_1569_ == 0)
{
if (v___y_1566_ == 0)
{
v___y_1544_ = v___y_1561_;
v___y_1545_ = v___y_1560_;
v___y_1546_ = v___y_1567_;
v___y_1547_ = v___y_1562_;
v___y_1548_ = v___y_1564_;
v___y_1549_ = v___y_1565_;
v___y_1550_ = v___y_1563_;
goto v___jp_1543_;
}
else
{
uint64_t v___x_1570_; 
v___x_1570_ = 8388608ULL;
v___y_1544_ = v___y_1561_;
v___y_1545_ = v___y_1560_;
v___y_1546_ = v___y_1567_;
v___y_1547_ = v___y_1562_;
v___y_1548_ = v___y_1564_;
v___y_1549_ = v___y_1565_;
v___y_1550_ = v___x_1570_;
goto v___jp_1543_;
}
}
else
{
if (v___y_1565_ == 0)
{
uint32_t v___x_1571_; 
v___x_1571_ = 2139095040;
return v___x_1571_;
}
else
{
uint32_t v___x_1572_; 
v___x_1572_ = 4286578688;
return v___x_1572_;
}
}
}
v___jp_1573_:
{
uint64_t v___x_1581_; uint8_t v_carry_1582_; 
v___x_1581_ = 16777216ULL;
v_carry_1582_ = lean_uint64_dec_eq(v___y_1580_, v___x_1581_);
if (v_carry_1582_ == 0)
{
v___y_1560_ = v___y_1575_;
v___y_1561_ = v___y_1574_;
v___y_1562_ = v___y_1576_;
v___y_1563_ = v___y_1580_;
v___y_1564_ = v___y_1577_;
v___y_1565_ = v___y_1579_;
v___y_1566_ = v_carry_1582_;
v___y_1567_ = v___y_1578_;
goto v___jp_1559_;
}
else
{
uint64_t v___x_1583_; uint64_t v___x_1584_; 
v___x_1583_ = 1ULL;
v___x_1584_ = lean_uint64_add(v___y_1578_, v___x_1583_);
v___y_1560_ = v___y_1575_;
v___y_1561_ = v___y_1574_;
v___y_1562_ = v___y_1576_;
v___y_1563_ = v___y_1580_;
v___y_1564_ = v___y_1577_;
v___y_1565_ = v___y_1579_;
v___y_1566_ = v_carry_1582_;
v___y_1567_ = v___x_1584_;
goto v___jp_1559_;
}
}
v___jp_1585_:
{
uint32_t v___x_1589_; uint32_t v___x_1590_; 
v___x_1589_ = lean_uint32_land(v___y_1587_, v___y_1586_);
v___x_1590_ = lean_uint32_lor(v___y_1588_, v___x_1589_);
return v___x_1590_;
}
v___jp_1591_:
{
uint32_t v___x_1593_; uint32_t v___x_1594_; 
v___x_1593_ = 8388608;
v___x_1594_ = lean_uint32_lor(v___y_1592_, v___x_1593_);
return v___x_1594_;
}
v___jp_1595_:
{
uint8_t v___x_1600_; 
v___x_1600_ = lean_uint64_dec_eq(v___y_1599_, v___y_1598_);
if (v___x_1600_ == 0)
{
uint64_t v___x_1601_; uint8_t v___x_1602_; 
v___x_1601_ = 8388608ULL;
v___x_1602_ = lean_uint64_dec_eq(v___y_1599_, v___x_1601_);
if (v___x_1602_ == 0)
{
uint32_t v___x_1603_; 
v___x_1603_ = lean_uint64_to_uint32(v___y_1599_);
if (v___y_1596_ == 0)
{
uint32_t v___x_1604_; 
v___x_1604_ = 0;
v___y_1511_ = v___x_1603_;
v___y_1512_ = v___y_1597_;
v___y_1513_ = v___x_1604_;
goto v___jp_1510_;
}
else
{
uint32_t v___x_1605_; 
v___x_1605_ = 2147483648;
v___y_1511_ = v___x_1603_;
v___y_1512_ = v___y_1597_;
v___y_1513_ = v___x_1605_;
goto v___jp_1510_;
}
}
else
{
if (v___y_1596_ == 0)
{
uint32_t v___x_1606_; 
v___x_1606_ = 0;
v___y_1592_ = v___x_1606_;
goto v___jp_1591_;
}
else
{
uint32_t v___x_1607_; 
v___x_1607_ = 2147483648;
v___y_1592_ = v___x_1607_;
goto v___jp_1591_;
}
}
}
else
{
if (v___y_1596_ == 0)
{
uint32_t v___x_1608_; 
v___x_1608_ = 0;
return v___x_1608_;
}
else
{
uint32_t v___x_1609_; 
v___x_1609_ = 2147483648;
return v___x_1609_;
}
}
}
v___jp_1610_:
{
uint64_t v_position_1619_; uint64_t v___x_1620_; uint8_t v___x_1621_; 
v_position_1619_ = lean_uint64_add(v___y_1618_, v___y_1616_);
v___x_1620_ = 172ULL;
v___x_1621_ = lean_uint64_dec_lt(v_position_1619_, v___x_1620_);
if (v___x_1621_ == 0)
{
uint64_t v___x_1622_; uint8_t v___x_1623_; 
v___x_1622_ = 23ULL;
v___x_1623_ = lean_uint64_dec_lt(v___y_1618_, v___x_1622_);
if (v___x_1623_ == 0)
{
uint64_t v___x_1624_; uint8_t v___x_1625_; 
v___x_1624_ = lean_uint64_sub(v___y_1618_, v___x_1622_);
v___x_1625_ = lean_uint64_dec_eq(v___x_1624_, v___y_1613_);
if (v___x_1625_ == 0)
{
uint64_t v___x_1626_; uint8_t v___x_1627_; 
v___x_1626_ = 64ULL;
v___x_1627_ = lean_uint64_dec_lt(v___x_1624_, v___x_1626_);
if (v___x_1627_ == 0)
{
uint8_t v___x_1628_; 
v___x_1628_ = lean_uint64_dec_eq(v___x_1624_, v___x_1626_);
if (v___x_1628_ == 0)
{
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v___y_1613_;
goto v___jp_1498_;
}
else
{
uint64_t v___x_1629_; uint8_t v___x_1630_; 
v___x_1629_ = 9223372036854775808ULL;
v___x_1630_ = lean_uint64_dec_lt(v___x_1629_, v___y_1617_);
if (v___x_1630_ == 0)
{
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v___y_1613_;
goto v___jp_1498_;
}
else
{
uint64_t v___x_1631_; 
v___x_1631_ = 1ULL;
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v___x_1631_;
goto v___jp_1498_;
}
}
}
else
{
uint64_t v_quotient_1632_; uint64_t v___x_1633_; uint64_t v___x_1634_; uint64_t v___x_1635_; uint64_t v_remainder_1636_; uint64_t v___x_1637_; uint64_t v_half_1638_; uint8_t v___x_1639_; 
v_quotient_1632_ = lean_uint64_shift_right(v___y_1617_, v___x_1624_);
v___x_1633_ = 1ULL;
v___x_1634_ = lean_uint64_shift_left(v___x_1633_, v___x_1624_);
v___x_1635_ = lean_uint64_sub(v___x_1634_, v___x_1633_);
v_remainder_1636_ = lean_uint64_land(v___y_1617_, v___x_1635_);
v___x_1637_ = lean_uint64_sub(v___x_1624_, v___x_1633_);
v_half_1638_ = lean_uint64_shift_left(v___x_1633_, v___x_1637_);
v___x_1639_ = lean_uint64_dec_lt(v_remainder_1636_, v_half_1638_);
if (v___x_1639_ == 0)
{
uint8_t v___x_1640_; 
v___x_1640_ = lean_uint64_dec_lt(v_half_1638_, v_remainder_1636_);
if (v___x_1640_ == 0)
{
uint64_t v___x_1641_; uint8_t v___x_1642_; 
v___x_1641_ = lean_uint64_land(v_quotient_1632_, v___x_1633_);
v___x_1642_ = lean_uint64_dec_eq(v___x_1641_, v___y_1613_);
if (v___x_1642_ == 0)
{
uint64_t v___x_1643_; 
v___x_1643_ = lean_uint64_add(v_quotient_1632_, v___x_1633_);
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v___x_1643_;
goto v___jp_1498_;
}
else
{
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v_quotient_1632_;
goto v___jp_1498_;
}
}
else
{
uint64_t v___x_1644_; 
v___x_1644_ = lean_uint64_add(v_quotient_1632_, v___x_1633_);
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v___x_1644_;
goto v___jp_1498_;
}
}
else
{
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v_quotient_1632_;
goto v___jp_1498_;
}
}
}
else
{
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v___y_1617_;
goto v___jp_1498_;
}
}
else
{
uint64_t v___x_1645_; uint64_t v___x_1646_; 
v___x_1645_ = lean_uint64_sub(v___x_1622_, v___y_1618_);
v___x_1646_ = lean_uint64_shift_left(v___y_1617_, v___x_1645_);
v___y_1499_ = v___y_1612_;
v___y_1500_ = v___y_1611_;
v___y_1501_ = v___y_1613_;
v___y_1502_ = v___y_1614_;
v___y_1503_ = v___y_1615_;
v___y_1504_ = v_position_1619_;
v___y_1505_ = v___x_1646_;
goto v___jp_1498_;
}
}
else
{
uint64_t v___x_1647_; uint8_t v___x_1648_; 
v___x_1647_ = 149ULL;
v___x_1648_ = lean_uint64_dec_lt(v___y_1616_, v___x_1647_);
if (v___x_1648_ == 0)
{
uint64_t v___x_1649_; uint64_t v___x_1650_; 
v___x_1649_ = lean_uint64_sub(v___y_1616_, v___x_1647_);
v___x_1650_ = lean_uint64_shift_left(v___y_1617_, v___x_1649_);
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v___x_1650_;
goto v___jp_1595_;
}
else
{
uint64_t v___x_1651_; uint8_t v___x_1652_; 
v___x_1651_ = lean_uint64_sub(v___x_1647_, v___y_1616_);
v___x_1652_ = lean_uint64_dec_eq(v___x_1651_, v___y_1613_);
if (v___x_1652_ == 0)
{
uint64_t v___x_1653_; uint8_t v___x_1654_; 
v___x_1653_ = 64ULL;
v___x_1654_ = lean_uint64_dec_lt(v___x_1651_, v___x_1653_);
if (v___x_1654_ == 0)
{
uint8_t v___x_1655_; 
v___x_1655_ = lean_uint64_dec_eq(v___x_1651_, v___x_1653_);
if (v___x_1655_ == 0)
{
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v___y_1613_;
goto v___jp_1595_;
}
else
{
uint64_t v___x_1656_; uint8_t v___x_1657_; 
v___x_1656_ = 9223372036854775808ULL;
v___x_1657_ = lean_uint64_dec_lt(v___x_1656_, v___y_1617_);
if (v___x_1657_ == 0)
{
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v___y_1613_;
goto v___jp_1595_;
}
else
{
uint64_t v___x_1658_; 
v___x_1658_ = 1ULL;
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v___x_1658_;
goto v___jp_1595_;
}
}
}
else
{
uint64_t v_quotient_1659_; uint64_t v___x_1660_; uint64_t v___x_1661_; uint64_t v___x_1662_; uint64_t v_remainder_1663_; uint64_t v___x_1664_; uint64_t v_half_1665_; uint8_t v___x_1666_; 
v_quotient_1659_ = lean_uint64_shift_right(v___y_1617_, v___x_1651_);
v___x_1660_ = 1ULL;
v___x_1661_ = lean_uint64_shift_left(v___x_1660_, v___x_1651_);
v___x_1662_ = lean_uint64_sub(v___x_1661_, v___x_1660_);
v_remainder_1663_ = lean_uint64_land(v___y_1617_, v___x_1662_);
v___x_1664_ = lean_uint64_sub(v___x_1651_, v___x_1660_);
v_half_1665_ = lean_uint64_shift_left(v___x_1660_, v___x_1664_);
v___x_1666_ = lean_uint64_dec_lt(v_remainder_1663_, v_half_1665_);
if (v___x_1666_ == 0)
{
uint8_t v___x_1667_; 
v___x_1667_ = lean_uint64_dec_lt(v_half_1665_, v_remainder_1663_);
if (v___x_1667_ == 0)
{
uint64_t v___x_1668_; uint8_t v___x_1669_; 
v___x_1668_ = lean_uint64_land(v_quotient_1659_, v___x_1660_);
v___x_1669_ = lean_uint64_dec_eq(v___x_1668_, v___y_1613_);
if (v___x_1669_ == 0)
{
uint64_t v___x_1670_; 
v___x_1670_ = lean_uint64_add(v_quotient_1659_, v___x_1660_);
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v___x_1670_;
goto v___jp_1595_;
}
else
{
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v_quotient_1659_;
goto v___jp_1595_;
}
}
else
{
uint64_t v___x_1671_; 
v___x_1671_ = lean_uint64_add(v_quotient_1659_, v___x_1660_);
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v___x_1671_;
goto v___jp_1595_;
}
}
else
{
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v_quotient_1659_;
goto v___jp_1595_;
}
}
}
else
{
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1613_;
v___y_1599_ = v___y_1617_;
goto v___jp_1595_;
}
}
}
}
v___jp_1672_:
{
uint64_t v___x_1682_; uint64_t v___x_1683_; uint8_t v___x_1684_; 
v___x_1682_ = 1ULL;
v___x_1683_ = lean_uint64_shift_right(v___y_1675_, v___x_1682_);
v___x_1684_ = lean_uint64_dec_eq(v___x_1683_, v___y_1676_);
if (v___x_1684_ == 0)
{
uint64_t v___x_1685_; 
v___x_1685_ = lean_uint64_add(v___y_1681_, v___x_1682_);
v___y_1611_ = v___y_1674_;
v___y_1612_ = v___y_1673_;
v___y_1613_ = v___y_1676_;
v___y_1614_ = v___y_1677_;
v___y_1615_ = v___y_1679_;
v___y_1616_ = v___y_1678_;
v___y_1617_ = v___y_1680_;
v___y_1618_ = v___x_1685_;
goto v___jp_1610_;
}
else
{
v___y_1611_ = v___y_1674_;
v___y_1612_ = v___y_1673_;
v___y_1613_ = v___y_1676_;
v___y_1614_ = v___y_1677_;
v___y_1615_ = v___y_1679_;
v___y_1616_ = v___y_1678_;
v___y_1617_ = v___y_1680_;
v___y_1618_ = v___y_1681_;
goto v___jp_1610_;
}
}
v___jp_1686_:
{
uint64_t v___x_1698_; uint8_t v___x_1699_; 
v___x_1698_ = lean_uint64_shift_right(v___y_1691_, v___y_1690_);
v___x_1699_ = lean_uint64_dec_eq(v___x_1698_, v___y_1689_);
if (v___x_1699_ == 0)
{
uint64_t v___x_1700_; 
v___x_1700_ = lean_uint64_add(v___y_1693_, v___y_1690_);
v___y_1673_ = v___y_1688_;
v___y_1674_ = v___y_1687_;
v___y_1675_ = v___y_1697_;
v___y_1676_ = v___y_1689_;
v___y_1677_ = v___y_1692_;
v___y_1678_ = v___y_1695_;
v___y_1679_ = v___y_1694_;
v___y_1680_ = v___y_1696_;
v___y_1681_ = v___x_1700_;
goto v___jp_1672_;
}
else
{
v___y_1673_ = v___y_1688_;
v___y_1674_ = v___y_1687_;
v___y_1675_ = v___y_1697_;
v___y_1676_ = v___y_1689_;
v___y_1677_ = v___y_1692_;
v___y_1678_ = v___y_1695_;
v___y_1679_ = v___y_1694_;
v___y_1680_ = v___y_1696_;
v___y_1681_ = v___y_1693_;
goto v___jp_1672_;
}
}
v___jp_1701_:
{
uint64_t v___x_1711_; uint64_t v___x_1712_; uint8_t v___x_1713_; 
v___x_1711_ = 2ULL;
v___x_1712_ = lean_uint64_shift_right(v___y_1705_, v___x_1711_);
v___x_1713_ = lean_uint64_dec_eq(v___x_1712_, v___y_1704_);
if (v___x_1713_ == 0)
{
v___y_1687_ = v___y_1703_;
v___y_1688_ = v___y_1702_;
v___y_1689_ = v___y_1704_;
v___y_1690_ = v___x_1711_;
v___y_1691_ = v___y_1705_;
v___y_1692_ = v___y_1706_;
v___y_1693_ = v___y_1710_;
v___y_1694_ = v___y_1708_;
v___y_1695_ = v___y_1707_;
v___y_1696_ = v___y_1709_;
v___y_1697_ = v___x_1712_;
goto v___jp_1686_;
}
else
{
v___y_1687_ = v___y_1703_;
v___y_1688_ = v___y_1702_;
v___y_1689_ = v___y_1704_;
v___y_1690_ = v___x_1711_;
v___y_1691_ = v___y_1705_;
v___y_1692_ = v___y_1706_;
v___y_1693_ = v___y_1710_;
v___y_1694_ = v___y_1708_;
v___y_1695_ = v___y_1707_;
v___y_1696_ = v___y_1709_;
v___y_1697_ = v___y_1705_;
goto v___jp_1686_;
}
}
v___jp_1714_:
{
uint64_t v___x_1726_; uint8_t v___x_1727_; 
v___x_1726_ = lean_uint64_shift_right(v___y_1720_, v___y_1716_);
v___x_1727_ = lean_uint64_dec_eq(v___x_1726_, v___y_1719_);
if (v___x_1727_ == 0)
{
uint64_t v___x_1728_; 
v___x_1728_ = lean_uint64_add(v___y_1715_, v___y_1716_);
v___y_1702_ = v___y_1718_;
v___y_1703_ = v___y_1717_;
v___y_1704_ = v___y_1719_;
v___y_1705_ = v___y_1725_;
v___y_1706_ = v___y_1721_;
v___y_1707_ = v___y_1723_;
v___y_1708_ = v___y_1722_;
v___y_1709_ = v___y_1724_;
v___y_1710_ = v___x_1728_;
goto v___jp_1701_;
}
else
{
v___y_1702_ = v___y_1718_;
v___y_1703_ = v___y_1717_;
v___y_1704_ = v___y_1719_;
v___y_1705_ = v___y_1725_;
v___y_1706_ = v___y_1721_;
v___y_1707_ = v___y_1723_;
v___y_1708_ = v___y_1722_;
v___y_1709_ = v___y_1724_;
v___y_1710_ = v___y_1715_;
goto v___jp_1701_;
}
}
v___jp_1729_:
{
uint64_t v___x_1739_; uint64_t v___x_1740_; uint8_t v___x_1741_; 
v___x_1739_ = 4ULL;
v___x_1740_ = lean_uint64_shift_right(v___y_1733_, v___x_1739_);
v___x_1741_ = lean_uint64_dec_eq(v___x_1740_, v___y_1732_);
if (v___x_1741_ == 0)
{
v___y_1715_ = v___y_1738_;
v___y_1716_ = v___x_1739_;
v___y_1717_ = v___y_1731_;
v___y_1718_ = v___y_1730_;
v___y_1719_ = v___y_1732_;
v___y_1720_ = v___y_1733_;
v___y_1721_ = v___y_1734_;
v___y_1722_ = v___y_1736_;
v___y_1723_ = v___y_1735_;
v___y_1724_ = v___y_1737_;
v___y_1725_ = v___x_1740_;
goto v___jp_1714_;
}
else
{
v___y_1715_ = v___y_1738_;
v___y_1716_ = v___x_1739_;
v___y_1717_ = v___y_1731_;
v___y_1718_ = v___y_1730_;
v___y_1719_ = v___y_1732_;
v___y_1720_ = v___y_1733_;
v___y_1721_ = v___y_1734_;
v___y_1722_ = v___y_1736_;
v___y_1723_ = v___y_1735_;
v___y_1724_ = v___y_1737_;
v___y_1725_ = v___y_1733_;
goto v___jp_1714_;
}
}
v___jp_1742_:
{
uint64_t v___x_1754_; uint8_t v___x_1755_; 
v___x_1754_ = lean_uint64_shift_right(v___y_1745_, v___y_1749_);
v___x_1755_ = lean_uint64_dec_eq(v___x_1754_, v___y_1746_);
if (v___x_1755_ == 0)
{
uint64_t v___x_1756_; 
v___x_1756_ = lean_uint64_add(v___y_1747_, v___y_1749_);
v___y_1730_ = v___y_1744_;
v___y_1731_ = v___y_1743_;
v___y_1732_ = v___y_1746_;
v___y_1733_ = v___y_1753_;
v___y_1734_ = v___y_1748_;
v___y_1735_ = v___y_1751_;
v___y_1736_ = v___y_1750_;
v___y_1737_ = v___y_1752_;
v___y_1738_ = v___x_1756_;
goto v___jp_1729_;
}
else
{
v___y_1730_ = v___y_1744_;
v___y_1731_ = v___y_1743_;
v___y_1732_ = v___y_1746_;
v___y_1733_ = v___y_1753_;
v___y_1734_ = v___y_1748_;
v___y_1735_ = v___y_1751_;
v___y_1736_ = v___y_1750_;
v___y_1737_ = v___y_1752_;
v___y_1738_ = v___y_1747_;
goto v___jp_1729_;
}
}
v___jp_1757_:
{
uint64_t v___x_1767_; uint64_t v___x_1768_; uint8_t v___x_1769_; 
v___x_1767_ = 8ULL;
v___x_1768_ = lean_uint64_shift_right(v___y_1760_, v___x_1767_);
v___x_1769_ = lean_uint64_dec_eq(v___x_1768_, v___y_1761_);
if (v___x_1769_ == 0)
{
v___y_1743_ = v___y_1759_;
v___y_1744_ = v___y_1758_;
v___y_1745_ = v___y_1760_;
v___y_1746_ = v___y_1761_;
v___y_1747_ = v___y_1766_;
v___y_1748_ = v___y_1762_;
v___y_1749_ = v___x_1767_;
v___y_1750_ = v___y_1764_;
v___y_1751_ = v___y_1763_;
v___y_1752_ = v___y_1765_;
v___y_1753_ = v___x_1768_;
goto v___jp_1742_;
}
else
{
v___y_1743_ = v___y_1759_;
v___y_1744_ = v___y_1758_;
v___y_1745_ = v___y_1760_;
v___y_1746_ = v___y_1761_;
v___y_1747_ = v___y_1766_;
v___y_1748_ = v___y_1762_;
v___y_1749_ = v___x_1767_;
v___y_1750_ = v___y_1764_;
v___y_1751_ = v___y_1763_;
v___y_1752_ = v___y_1765_;
v___y_1753_ = v___y_1760_;
goto v___jp_1742_;
}
}
v___jp_1770_:
{
uint64_t v___x_1782_; uint8_t v___x_1783_; 
v___x_1782_ = lean_uint64_shift_right(v___y_1771_, v___y_1779_);
v___x_1783_ = lean_uint64_dec_eq(v___x_1782_, v___y_1774_);
if (v___x_1783_ == 0)
{
uint64_t v___x_1784_; 
v___x_1784_ = lean_uint64_add(v___y_1778_, v___y_1779_);
v___y_1758_ = v___y_1773_;
v___y_1759_ = v___y_1772_;
v___y_1760_ = v___y_1781_;
v___y_1761_ = v___y_1774_;
v___y_1762_ = v___y_1775_;
v___y_1763_ = v___y_1777_;
v___y_1764_ = v___y_1776_;
v___y_1765_ = v___y_1780_;
v___y_1766_ = v___x_1784_;
goto v___jp_1757_;
}
else
{
v___y_1758_ = v___y_1773_;
v___y_1759_ = v___y_1772_;
v___y_1760_ = v___y_1781_;
v___y_1761_ = v___y_1774_;
v___y_1762_ = v___y_1775_;
v___y_1763_ = v___y_1777_;
v___y_1764_ = v___y_1776_;
v___y_1765_ = v___y_1780_;
v___y_1766_ = v___y_1778_;
goto v___jp_1757_;
}
}
v___jp_1785_:
{
uint64_t v___x_1795_; uint64_t v___x_1796_; uint8_t v___x_1797_; 
v___x_1795_ = 16ULL;
v___x_1796_ = lean_uint64_shift_right(v___y_1786_, v___x_1795_);
v___x_1797_ = lean_uint64_dec_eq(v___x_1796_, v___y_1789_);
if (v___x_1797_ == 0)
{
v___y_1771_ = v___y_1786_;
v___y_1772_ = v___y_1788_;
v___y_1773_ = v___y_1787_;
v___y_1774_ = v___y_1789_;
v___y_1775_ = v___y_1790_;
v___y_1776_ = v___y_1792_;
v___y_1777_ = v___y_1791_;
v___y_1778_ = v___y_1794_;
v___y_1779_ = v___x_1795_;
v___y_1780_ = v___y_1793_;
v___y_1781_ = v___x_1796_;
goto v___jp_1770_;
}
else
{
v___y_1771_ = v___y_1786_;
v___y_1772_ = v___y_1788_;
v___y_1773_ = v___y_1787_;
v___y_1774_ = v___y_1789_;
v___y_1775_ = v___y_1790_;
v___y_1776_ = v___y_1792_;
v___y_1777_ = v___y_1791_;
v___y_1778_ = v___y_1794_;
v___y_1779_ = v___x_1795_;
v___y_1780_ = v___y_1793_;
v___y_1781_ = v___y_1786_;
goto v___jp_1770_;
}
}
v___jp_1798_:
{
uint64_t v___x_1808_; uint8_t v___x_1809_; 
v___x_1808_ = lean_uint64_shift_right(v___y_1806_, v___y_1802_);
v___x_1809_ = lean_uint64_dec_eq(v___x_1808_, v___y_1801_);
if (v___x_1809_ == 0)
{
v___y_1786_ = v___y_1807_;
v___y_1787_ = v___y_1800_;
v___y_1788_ = v___y_1799_;
v___y_1789_ = v___y_1801_;
v___y_1790_ = v___y_1803_;
v___y_1791_ = v___y_1805_;
v___y_1792_ = v___y_1804_;
v___y_1793_ = v___y_1806_;
v___y_1794_ = v___y_1802_;
goto v___jp_1785_;
}
else
{
v___y_1786_ = v___y_1807_;
v___y_1787_ = v___y_1800_;
v___y_1788_ = v___y_1799_;
v___y_1789_ = v___y_1801_;
v___y_1790_ = v___y_1803_;
v___y_1791_ = v___y_1805_;
v___y_1792_ = v___y_1804_;
v___y_1793_ = v___y_1806_;
v___y_1794_ = v___y_1801_;
goto v___jp_1785_;
}
}
v___jp_1810_:
{
uint64_t v___x_1817_; uint8_t v___x_1818_; 
v___x_1817_ = 0ULL;
v___x_1818_ = lean_uint64_dec_eq(v___y_1816_, v___x_1817_);
if (v___x_1818_ == 0)
{
uint64_t v___x_1819_; uint64_t v___x_1820_; uint8_t v___x_1821_; 
v___x_1819_ = 32ULL;
v___x_1820_ = lean_uint64_shift_right(v___y_1816_, v___x_1819_);
v___x_1821_ = lean_uint64_dec_eq(v___x_1820_, v___x_1817_);
if (v___x_1821_ == 0)
{
v___y_1799_ = v___y_1812_;
v___y_1800_ = v___y_1811_;
v___y_1801_ = v___x_1817_;
v___y_1802_ = v___x_1819_;
v___y_1803_ = v___y_1813_;
v___y_1804_ = v___y_1815_;
v___y_1805_ = v___y_1814_;
v___y_1806_ = v___y_1816_;
v___y_1807_ = v___x_1820_;
goto v___jp_1798_;
}
else
{
v___y_1799_ = v___y_1812_;
v___y_1800_ = v___y_1811_;
v___y_1801_ = v___x_1817_;
v___y_1802_ = v___x_1819_;
v___y_1803_ = v___y_1813_;
v___y_1804_ = v___y_1815_;
v___y_1805_ = v___y_1814_;
v___y_1806_ = v___y_1816_;
v___y_1807_ = v___y_1816_;
goto v___jp_1798_;
}
}
else
{
if (v___y_1812_ == 0)
{
uint32_t v___x_1822_; 
v___x_1822_ = 0;
return v___x_1822_;
}
else
{
uint32_t v___x_1823_; 
v___x_1823_ = 2147483648;
return v___x_1823_;
}
}
}
v___jp_1824_:
{
uint32_t v___x_1826_; uint32_t v___x_1827_; 
v___x_1826_ = 8388608;
v___x_1827_ = lean_uint32_lor(v___y_1825_, v___x_1826_);
return v___x_1827_;
}
v___jp_1828_:
{
uint8_t v___x_1833_; 
v___x_1833_ = lean_uint64_dec_eq(v___y_1832_, v___y_1831_);
if (v___x_1833_ == 0)
{
uint64_t v___x_1834_; uint8_t v___x_1835_; 
v___x_1834_ = 8388608ULL;
v___x_1835_ = lean_uint64_dec_eq(v___y_1832_, v___x_1834_);
if (v___x_1835_ == 0)
{
uint32_t v___x_1836_; 
v___x_1836_ = lean_uint64_to_uint32(v___y_1832_);
if (v___y_1829_ == 0)
{
uint32_t v___x_1837_; 
v___x_1837_ = 0;
v___y_1442_ = v___y_1830_;
v___y_1443_ = v___x_1836_;
v___y_1444_ = v___x_1837_;
goto v___jp_1441_;
}
else
{
uint32_t v___x_1838_; 
v___x_1838_ = 2147483648;
v___y_1442_ = v___y_1830_;
v___y_1443_ = v___x_1836_;
v___y_1444_ = v___x_1838_;
goto v___jp_1441_;
}
}
else
{
if (v___y_1829_ == 0)
{
uint32_t v___x_1839_; 
v___x_1839_ = 0;
v___y_1825_ = v___x_1839_;
goto v___jp_1824_;
}
else
{
uint32_t v___x_1840_; 
v___x_1840_ = 2147483648;
v___y_1825_ = v___x_1840_;
goto v___jp_1824_;
}
}
}
else
{
if (v___y_1829_ == 0)
{
uint32_t v___x_1841_; 
v___x_1841_ = 0;
return v___x_1841_;
}
else
{
uint32_t v___x_1842_; 
v___x_1842_ = 2147483648;
return v___x_1842_;
}
}
}
v___jp_1843_:
{
uint64_t v___x_1852_; uint64_t v___x_1853_; uint64_t v___x_1854_; uint8_t v___x_1855_; 
v___x_1852_ = lean_uint64_mul(v___y_1846_, v___y_1848_);
v___x_1853_ = lean_uint64_add(v___y_1847_, v___y_1851_);
v___x_1854_ = 281474976710656ULL;
v___x_1855_ = lean_uint64_dec_lt(v___x_1852_, v___x_1854_);
if (v___x_1855_ == 0)
{
v___y_1811_ = v___y_1845_;
v___y_1812_ = v___y_1844_;
v___y_1813_ = v___y_1849_;
v___y_1814_ = v___x_1853_;
v___y_1815_ = v___y_1850_;
v___y_1816_ = v___x_1852_;
goto v___jp_1810_;
}
else
{
uint64_t v___x_1856_; uint8_t v___x_1857_; 
v___x_1856_ = 123ULL;
v___x_1857_ = lean_uint64_dec_le(v___x_1853_, v___x_1856_);
if (v___x_1857_ == 0)
{
v___y_1811_ = v___y_1845_;
v___y_1812_ = v___y_1844_;
v___y_1813_ = v___y_1849_;
v___y_1814_ = v___x_1853_;
v___y_1815_ = v___y_1850_;
v___y_1816_ = v___x_1852_;
goto v___jp_1810_;
}
else
{
uint64_t v___x_1858_; uint8_t v___x_1859_; 
v___x_1858_ = 0ULL;
v___x_1859_ = lean_uint64_dec_eq(v___x_1852_, v___x_1858_);
if (v___x_1859_ == 0)
{
uint64_t v___x_1860_; uint64_t v___x_1861_; uint8_t v___x_1862_; 
v___x_1860_ = 149ULL;
v___x_1861_ = lean_uint64_sub(v___x_1860_, v___x_1853_);
v___x_1862_ = lean_uint64_dec_eq(v___x_1861_, v___x_1858_);
if (v___x_1862_ == 0)
{
uint64_t v___x_1863_; uint8_t v___x_1864_; 
v___x_1863_ = 64ULL;
v___x_1864_ = lean_uint64_dec_lt(v___x_1861_, v___x_1863_);
if (v___x_1864_ == 0)
{
uint8_t v___x_1865_; 
v___x_1865_ = lean_uint64_dec_eq(v___x_1861_, v___x_1863_);
if (v___x_1865_ == 0)
{
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1845_;
v___y_1831_ = v___x_1858_;
v___y_1832_ = v___x_1858_;
goto v___jp_1828_;
}
else
{
uint64_t v___x_1866_; uint8_t v___x_1867_; 
v___x_1866_ = 9223372036854775808ULL;
v___x_1867_ = lean_uint64_dec_lt(v___x_1866_, v___x_1852_);
if (v___x_1867_ == 0)
{
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1845_;
v___y_1831_ = v___x_1858_;
v___y_1832_ = v___x_1858_;
goto v___jp_1828_;
}
else
{
uint64_t v___x_1868_; 
v___x_1868_ = 1ULL;
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1845_;
v___y_1831_ = v___x_1858_;
v___y_1832_ = v___x_1868_;
goto v___jp_1828_;
}
}
}
else
{
uint64_t v_quotient_1869_; uint64_t v___x_1870_; uint64_t v___x_1871_; uint64_t v___x_1872_; uint64_t v_remainder_1873_; uint64_t v___x_1874_; uint64_t v_half_1875_; uint8_t v___x_1876_; 
v_quotient_1869_ = lean_uint64_shift_right(v___x_1852_, v___x_1861_);
v___x_1870_ = 1ULL;
v___x_1871_ = lean_uint64_shift_left(v___x_1870_, v___x_1861_);
v___x_1872_ = lean_uint64_sub(v___x_1871_, v___x_1870_);
v_remainder_1873_ = lean_uint64_land(v___x_1852_, v___x_1872_);
v___x_1874_ = lean_uint64_sub(v___x_1861_, v___x_1870_);
v_half_1875_ = lean_uint64_shift_left(v___x_1870_, v___x_1874_);
v___x_1876_ = lean_uint64_dec_lt(v_remainder_1873_, v_half_1875_);
if (v___x_1876_ == 0)
{
uint8_t v___x_1877_; 
v___x_1877_ = lean_uint64_dec_lt(v_half_1875_, v_remainder_1873_);
if (v___x_1877_ == 0)
{
uint64_t v___x_1878_; uint8_t v___x_1879_; 
v___x_1878_ = lean_uint64_land(v_quotient_1869_, v___x_1870_);
v___x_1879_ = lean_uint64_dec_eq(v___x_1878_, v___x_1858_);
if (v___x_1879_ == 0)
{
uint64_t v___x_1880_; 
v___x_1880_ = lean_uint64_add(v_quotient_1869_, v___x_1870_);
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1845_;
v___y_1831_ = v___x_1858_;
v___y_1832_ = v___x_1880_;
goto v___jp_1828_;
}
else
{
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1845_;
v___y_1831_ = v___x_1858_;
v___y_1832_ = v_quotient_1869_;
goto v___jp_1828_;
}
}
else
{
uint64_t v___x_1881_; 
v___x_1881_ = lean_uint64_add(v_quotient_1869_, v___x_1870_);
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1845_;
v___y_1831_ = v___x_1858_;
v___y_1832_ = v___x_1881_;
goto v___jp_1828_;
}
}
else
{
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1845_;
v___y_1831_ = v___x_1858_;
v___y_1832_ = v_quotient_1869_;
goto v___jp_1828_;
}
}
}
else
{
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1845_;
v___y_1831_ = v___x_1858_;
v___y_1832_ = v___x_1852_;
goto v___jp_1828_;
}
}
else
{
if (v___y_1844_ == 0)
{
uint32_t v___x_1882_; 
v___x_1882_ = 0;
return v___x_1882_;
}
else
{
uint32_t v___x_1883_; 
v___x_1883_ = 2147483648;
return v___x_1883_;
}
}
}
}
}
v___jp_1884_:
{
uint64_t v___x_1893_; uint64_t v___x_1894_; uint8_t v___x_1895_; 
v___x_1893_ = lean_uint32_to_uint64(v___y_1888_);
v___x_1894_ = 0ULL;
v___x_1895_ = lean_uint64_dec_eq(v___x_1893_, v___x_1894_);
if (v___x_1895_ == 0)
{
uint64_t v___x_1896_; uint64_t v___x_1897_; 
v___x_1896_ = 1ULL;
v___x_1897_ = lean_uint64_sub(v___x_1893_, v___x_1896_);
v___y_1844_ = v___y_1887_;
v___y_1845_ = v___y_1886_;
v___y_1846_ = v___y_1885_;
v___y_1847_ = v___y_1892_;
v___y_1848_ = v___y_1889_;
v___y_1849_ = v___y_1890_;
v___y_1850_ = v___y_1891_;
v___y_1851_ = v___x_1897_;
goto v___jp_1843_;
}
else
{
v___y_1844_ = v___y_1887_;
v___y_1845_ = v___y_1886_;
v___y_1846_ = v___y_1885_;
v___y_1847_ = v___y_1892_;
v___y_1848_ = v___y_1889_;
v___y_1849_ = v___y_1890_;
v___y_1850_ = v___y_1891_;
v___y_1851_ = v___x_1894_;
goto v___jp_1843_;
}
}
v___jp_1898_:
{
uint64_t v___x_1907_; uint64_t v___x_1908_; uint8_t v___x_1909_; 
v___x_1907_ = lean_uint32_to_uint64(v___y_1904_);
v___x_1908_ = 0ULL;
v___x_1909_ = lean_uint64_dec_eq(v___x_1907_, v___x_1908_);
if (v___x_1909_ == 0)
{
uint64_t v___x_1910_; uint64_t v___x_1911_; 
v___x_1910_ = 1ULL;
v___x_1911_ = lean_uint64_sub(v___x_1907_, v___x_1910_);
v___y_1885_ = v___y_1901_;
v___y_1886_ = v___y_1900_;
v___y_1887_ = v___y_1899_;
v___y_1888_ = v___y_1902_;
v___y_1889_ = v___y_1906_;
v___y_1890_ = v___y_1903_;
v___y_1891_ = v___y_1905_;
v___y_1892_ = v___x_1911_;
goto v___jp_1884_;
}
else
{
v___y_1885_ = v___y_1901_;
v___y_1886_ = v___y_1900_;
v___y_1887_ = v___y_1899_;
v___y_1888_ = v___y_1902_;
v___y_1889_ = v___y_1906_;
v___y_1890_ = v___y_1903_;
v___y_1891_ = v___y_1905_;
v___y_1892_ = v___x_1908_;
goto v___jp_1884_;
}
}
v___jp_1912_:
{
uint32_t v___x_1921_; uint8_t v___x_1922_; 
v___x_1921_ = 0;
v___x_1922_ = lean_uint32_dec_eq(v___y_1915_, v___x_1921_);
if (v___x_1922_ == 0)
{
uint64_t v___x_1923_; uint64_t v___x_1924_; uint64_t v___x_1925_; 
v___x_1923_ = lean_uint32_to_uint64(v___y_1916_);
v___x_1924_ = 8388608ULL;
v___x_1925_ = lean_uint64_lor(v___x_1923_, v___x_1924_);
v___y_1899_ = v___y_1914_;
v___y_1900_ = v___y_1913_;
v___y_1901_ = v___y_1920_;
v___y_1902_ = v___y_1915_;
v___y_1903_ = v___y_1917_;
v___y_1904_ = v___y_1918_;
v___y_1905_ = v___y_1919_;
v___y_1906_ = v___x_1925_;
goto v___jp_1898_;
}
else
{
uint64_t v___x_1926_; 
v___x_1926_ = lean_uint32_to_uint64(v___y_1916_);
v___y_1899_ = v___y_1914_;
v___y_1900_ = v___y_1913_;
v___y_1901_ = v___y_1920_;
v___y_1902_ = v___y_1915_;
v___y_1903_ = v___y_1917_;
v___y_1904_ = v___y_1918_;
v___y_1905_ = v___y_1919_;
v___y_1906_ = v___x_1926_;
goto v___jp_1898_;
}
}
v___jp_1927_:
{
uint32_t v___x_1929_; uint32_t v___x_1930_; 
v___x_1929_ = 8388608;
v___x_1930_ = lean_uint32_lor(v___y_1928_, v___x_1929_);
return v___x_1930_;
}
v___jp_1931_:
{
uint8_t v___x_1936_; 
v___x_1936_ = lean_uint64_dec_eq(v___y_1935_, v___y_1933_);
if (v___x_1936_ == 0)
{
uint64_t v___x_1937_; uint8_t v___x_1938_; 
v___x_1937_ = 8388608ULL;
v___x_1938_ = lean_uint64_dec_eq(v___y_1935_, v___x_1937_);
if (v___x_1938_ == 0)
{
uint32_t v___x_1939_; 
v___x_1939_ = lean_uint64_to_uint32(v___y_1935_);
if (v___y_1934_ == 0)
{
uint32_t v___x_1940_; 
v___x_1940_ = 0;
v___y_1517_ = v___x_1939_;
v___y_1518_ = v___y_1932_;
v___y_1519_ = v___x_1940_;
goto v___jp_1516_;
}
else
{
uint32_t v___x_1941_; 
v___x_1941_ = 2147483648;
v___y_1517_ = v___x_1939_;
v___y_1518_ = v___y_1932_;
v___y_1519_ = v___x_1941_;
goto v___jp_1516_;
}
}
else
{
if (v___y_1934_ == 0)
{
uint32_t v___x_1942_; 
v___x_1942_ = 0;
v___y_1928_ = v___x_1942_;
goto v___jp_1927_;
}
else
{
uint32_t v___x_1943_; 
v___x_1943_ = 2147483648;
v___y_1928_ = v___x_1943_;
goto v___jp_1927_;
}
}
}
else
{
if (v___y_1934_ == 0)
{
uint32_t v___x_1944_; 
v___x_1944_ = 0;
return v___x_1944_;
}
else
{
uint32_t v___x_1945_; 
v___x_1945_ = 2147483648;
return v___x_1945_;
}
}
}
v___jp_1946_:
{
uint32_t v___x_1948_; uint32_t v___x_1949_; 
v___x_1948_ = 8388608;
v___x_1949_ = lean_uint32_lor(v___y_1947_, v___x_1948_);
return v___x_1949_;
}
v___jp_1950_:
{
uint8_t v___x_1955_; 
v___x_1955_ = lean_uint64_dec_eq(v___y_1954_, v___y_1952_);
if (v___x_1955_ == 0)
{
uint64_t v___x_1956_; uint8_t v___x_1957_; 
v___x_1956_ = 8388608ULL;
v___x_1957_ = lean_uint64_dec_eq(v___y_1954_, v___x_1956_);
if (v___x_1957_ == 0)
{
uint32_t v___x_1958_; 
v___x_1958_ = lean_uint64_to_uint32(v___y_1954_);
if (v___y_1953_ == 0)
{
uint32_t v___x_1959_; 
v___x_1959_ = 0;
v___y_1586_ = v___y_1951_;
v___y_1587_ = v___x_1958_;
v___y_1588_ = v___x_1959_;
goto v___jp_1585_;
}
else
{
uint32_t v___x_1960_; 
v___x_1960_ = 2147483648;
v___y_1586_ = v___y_1951_;
v___y_1587_ = v___x_1958_;
v___y_1588_ = v___x_1960_;
goto v___jp_1585_;
}
}
else
{
if (v___y_1953_ == 0)
{
uint32_t v___x_1961_; 
v___x_1961_ = 0;
v___y_1947_ = v___x_1961_;
goto v___jp_1946_;
}
else
{
uint32_t v___x_1962_; 
v___x_1962_ = 2147483648;
v___y_1947_ = v___x_1962_;
goto v___jp_1946_;
}
}
}
else
{
if (v___y_1953_ == 0)
{
uint32_t v___x_1963_; 
v___x_1963_ = 0;
return v___x_1963_;
}
else
{
uint32_t v___x_1964_; 
v___x_1964_ = 2147483648;
return v___x_1964_;
}
}
}
v___jp_1965_:
{
uint64_t v_position_1974_; uint64_t v___x_1975_; uint8_t v___x_1976_; 
v_position_1974_ = lean_uint64_add(v___y_1973_, v___y_1969_);
v___x_1975_ = 172ULL;
v___x_1976_ = lean_uint64_dec_lt(v_position_1974_, v___x_1975_);
if (v___x_1976_ == 0)
{
uint64_t v___x_1977_; uint8_t v___x_1978_; 
v___x_1977_ = 23ULL;
v___x_1978_ = lean_uint64_dec_lt(v___y_1973_, v___x_1977_);
if (v___x_1978_ == 0)
{
uint64_t v___x_1979_; uint8_t v___x_1980_; 
v___x_1979_ = lean_uint64_sub(v___y_1973_, v___x_1977_);
v___x_1980_ = lean_uint64_dec_eq(v___x_1979_, v___y_1970_);
if (v___x_1980_ == 0)
{
uint64_t v___x_1981_; uint8_t v___x_1982_; 
v___x_1981_ = 64ULL;
v___x_1982_ = lean_uint64_dec_lt(v___x_1979_, v___x_1981_);
if (v___x_1982_ == 0)
{
uint8_t v___x_1983_; 
v___x_1983_ = lean_uint64_dec_eq(v___x_1979_, v___x_1981_);
if (v___x_1983_ == 0)
{
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v___y_1970_;
goto v___jp_1573_;
}
else
{
uint64_t v___x_1984_; uint8_t v___x_1985_; 
v___x_1984_ = 9223372036854775808ULL;
v___x_1985_ = lean_uint64_dec_lt(v___x_1984_, v___y_1971_);
if (v___x_1985_ == 0)
{
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v___y_1970_;
goto v___jp_1573_;
}
else
{
uint64_t v___x_1986_; 
v___x_1986_ = 1ULL;
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v___x_1986_;
goto v___jp_1573_;
}
}
}
else
{
uint64_t v_quotient_1987_; uint64_t v___x_1988_; uint64_t v___x_1989_; uint64_t v___x_1990_; uint64_t v_remainder_1991_; uint64_t v___x_1992_; uint64_t v_half_1993_; uint8_t v___x_1994_; 
v_quotient_1987_ = lean_uint64_shift_right(v___y_1971_, v___x_1979_);
v___x_1988_ = 1ULL;
v___x_1989_ = lean_uint64_shift_left(v___x_1988_, v___x_1979_);
v___x_1990_ = lean_uint64_sub(v___x_1989_, v___x_1988_);
v_remainder_1991_ = lean_uint64_land(v___y_1971_, v___x_1990_);
v___x_1992_ = lean_uint64_sub(v___x_1979_, v___x_1988_);
v_half_1993_ = lean_uint64_shift_left(v___x_1988_, v___x_1992_);
v___x_1994_ = lean_uint64_dec_lt(v_remainder_1991_, v_half_1993_);
if (v___x_1994_ == 0)
{
uint8_t v___x_1995_; 
v___x_1995_ = lean_uint64_dec_lt(v_half_1993_, v_remainder_1991_);
if (v___x_1995_ == 0)
{
uint64_t v___x_1996_; uint8_t v___x_1997_; 
v___x_1996_ = lean_uint64_land(v_quotient_1987_, v___x_1988_);
v___x_1997_ = lean_uint64_dec_eq(v___x_1996_, v___y_1970_);
if (v___x_1997_ == 0)
{
uint64_t v___x_1998_; 
v___x_1998_ = lean_uint64_add(v_quotient_1987_, v___x_1988_);
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v___x_1998_;
goto v___jp_1573_;
}
else
{
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v_quotient_1987_;
goto v___jp_1573_;
}
}
else
{
uint64_t v___x_1999_; 
v___x_1999_ = lean_uint64_add(v_quotient_1987_, v___x_1988_);
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v___x_1999_;
goto v___jp_1573_;
}
}
else
{
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v_quotient_1987_;
goto v___jp_1573_;
}
}
}
else
{
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v___y_1971_;
goto v___jp_1573_;
}
}
else
{
uint64_t v___x_2000_; uint64_t v___x_2001_; 
v___x_2000_ = lean_uint64_sub(v___x_1977_, v___y_1973_);
v___x_2001_ = lean_uint64_shift_left(v___y_1971_, v___x_2000_);
v___y_1574_ = v___y_1967_;
v___y_1575_ = v___y_1966_;
v___y_1576_ = v___y_1968_;
v___y_1577_ = v___y_1970_;
v___y_1578_ = v_position_1974_;
v___y_1579_ = v___y_1972_;
v___y_1580_ = v___x_2001_;
goto v___jp_1573_;
}
}
else
{
uint64_t v___x_2002_; uint8_t v___x_2003_; 
v___x_2002_ = 149ULL;
v___x_2003_ = lean_uint64_dec_lt(v___y_1969_, v___x_2002_);
if (v___x_2003_ == 0)
{
uint64_t v___x_2004_; uint64_t v___x_2005_; 
v___x_2004_ = lean_uint64_sub(v___y_1969_, v___x_2002_);
v___x_2005_ = lean_uint64_shift_left(v___y_1971_, v___x_2004_);
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v___x_2005_;
goto v___jp_1950_;
}
else
{
uint64_t v___x_2006_; uint8_t v___x_2007_; 
v___x_2006_ = lean_uint64_sub(v___x_2002_, v___y_1969_);
v___x_2007_ = lean_uint64_dec_eq(v___x_2006_, v___y_1970_);
if (v___x_2007_ == 0)
{
uint64_t v___x_2008_; uint8_t v___x_2009_; 
v___x_2008_ = 64ULL;
v___x_2009_ = lean_uint64_dec_lt(v___x_2006_, v___x_2008_);
if (v___x_2009_ == 0)
{
uint8_t v___x_2010_; 
v___x_2010_ = lean_uint64_dec_eq(v___x_2006_, v___x_2008_);
if (v___x_2010_ == 0)
{
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v___y_1970_;
goto v___jp_1950_;
}
else
{
uint64_t v___x_2011_; uint8_t v___x_2012_; 
v___x_2011_ = 9223372036854775808ULL;
v___x_2012_ = lean_uint64_dec_lt(v___x_2011_, v___y_1971_);
if (v___x_2012_ == 0)
{
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v___y_1970_;
goto v___jp_1950_;
}
else
{
uint64_t v___x_2013_; 
v___x_2013_ = 1ULL;
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v___x_2013_;
goto v___jp_1950_;
}
}
}
else
{
uint64_t v_quotient_2014_; uint64_t v___x_2015_; uint64_t v___x_2016_; uint64_t v___x_2017_; uint64_t v_remainder_2018_; uint64_t v___x_2019_; uint64_t v_half_2020_; uint8_t v___x_2021_; 
v_quotient_2014_ = lean_uint64_shift_right(v___y_1971_, v___x_2006_);
v___x_2015_ = 1ULL;
v___x_2016_ = lean_uint64_shift_left(v___x_2015_, v___x_2006_);
v___x_2017_ = lean_uint64_sub(v___x_2016_, v___x_2015_);
v_remainder_2018_ = lean_uint64_land(v___y_1971_, v___x_2017_);
v___x_2019_ = lean_uint64_sub(v___x_2006_, v___x_2015_);
v_half_2020_ = lean_uint64_shift_left(v___x_2015_, v___x_2019_);
v___x_2021_ = lean_uint64_dec_lt(v_remainder_2018_, v_half_2020_);
if (v___x_2021_ == 0)
{
uint8_t v___x_2022_; 
v___x_2022_ = lean_uint64_dec_lt(v_half_2020_, v_remainder_2018_);
if (v___x_2022_ == 0)
{
uint64_t v___x_2023_; uint8_t v___x_2024_; 
v___x_2023_ = lean_uint64_land(v_quotient_2014_, v___x_2015_);
v___x_2024_ = lean_uint64_dec_eq(v___x_2023_, v___y_1970_);
if (v___x_2024_ == 0)
{
uint64_t v___x_2025_; 
v___x_2025_ = lean_uint64_add(v_quotient_2014_, v___x_2015_);
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v___x_2025_;
goto v___jp_1950_;
}
else
{
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v_quotient_2014_;
goto v___jp_1950_;
}
}
else
{
uint64_t v___x_2026_; 
v___x_2026_ = lean_uint64_add(v_quotient_2014_, v___x_2015_);
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v___x_2026_;
goto v___jp_1950_;
}
}
else
{
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v_quotient_2014_;
goto v___jp_1950_;
}
}
}
else
{
v___y_1951_ = v___y_1968_;
v___y_1952_ = v___y_1970_;
v___y_1953_ = v___y_1972_;
v___y_1954_ = v___y_1971_;
goto v___jp_1950_;
}
}
}
}
v___jp_2027_:
{
uint64_t v___x_2037_; uint64_t v___x_2038_; uint8_t v___x_2039_; 
v___x_2037_ = 1ULL;
v___x_2038_ = lean_uint64_shift_right(v___y_2035_, v___x_2037_);
v___x_2039_ = lean_uint64_dec_eq(v___x_2038_, v___y_2032_);
if (v___x_2039_ == 0)
{
uint64_t v___x_2040_; 
v___x_2040_ = lean_uint64_add(v___y_2036_, v___x_2037_);
v___y_1966_ = v___y_2029_;
v___y_1967_ = v___y_2028_;
v___y_1968_ = v___y_2030_;
v___y_1969_ = v___y_2031_;
v___y_1970_ = v___y_2032_;
v___y_1971_ = v___y_2033_;
v___y_1972_ = v___y_2034_;
v___y_1973_ = v___x_2040_;
goto v___jp_1965_;
}
else
{
v___y_1966_ = v___y_2029_;
v___y_1967_ = v___y_2028_;
v___y_1968_ = v___y_2030_;
v___y_1969_ = v___y_2031_;
v___y_1970_ = v___y_2032_;
v___y_1971_ = v___y_2033_;
v___y_1972_ = v___y_2034_;
v___y_1973_ = v___y_2036_;
goto v___jp_1965_;
}
}
v___jp_2041_:
{
uint64_t v___x_2053_; uint8_t v___x_2054_; 
v___x_2053_ = lean_uint64_shift_right(v___y_2044_, v___y_2046_);
v___x_2054_ = lean_uint64_dec_eq(v___x_2053_, v___y_2048_);
if (v___x_2054_ == 0)
{
uint64_t v___x_2055_; 
v___x_2055_ = lean_uint64_add(v___y_2051_, v___y_2046_);
v___y_2028_ = v___y_2043_;
v___y_2029_ = v___y_2042_;
v___y_2030_ = v___y_2045_;
v___y_2031_ = v___y_2047_;
v___y_2032_ = v___y_2048_;
v___y_2033_ = v___y_2049_;
v___y_2034_ = v___y_2050_;
v___y_2035_ = v___y_2052_;
v___y_2036_ = v___x_2055_;
goto v___jp_2027_;
}
else
{
v___y_2028_ = v___y_2043_;
v___y_2029_ = v___y_2042_;
v___y_2030_ = v___y_2045_;
v___y_2031_ = v___y_2047_;
v___y_2032_ = v___y_2048_;
v___y_2033_ = v___y_2049_;
v___y_2034_ = v___y_2050_;
v___y_2035_ = v___y_2052_;
v___y_2036_ = v___y_2051_;
goto v___jp_2027_;
}
}
v___jp_2056_:
{
uint64_t v___x_2066_; uint64_t v___x_2067_; uint8_t v___x_2068_; 
v___x_2066_ = 2ULL;
v___x_2067_ = lean_uint64_shift_right(v___y_2059_, v___x_2066_);
v___x_2068_ = lean_uint64_dec_eq(v___x_2067_, v___y_2062_);
if (v___x_2068_ == 0)
{
v___y_2042_ = v___y_2058_;
v___y_2043_ = v___y_2057_;
v___y_2044_ = v___y_2059_;
v___y_2045_ = v___y_2060_;
v___y_2046_ = v___x_2066_;
v___y_2047_ = v___y_2061_;
v___y_2048_ = v___y_2062_;
v___y_2049_ = v___y_2063_;
v___y_2050_ = v___y_2064_;
v___y_2051_ = v___y_2065_;
v___y_2052_ = v___x_2067_;
goto v___jp_2041_;
}
else
{
v___y_2042_ = v___y_2058_;
v___y_2043_ = v___y_2057_;
v___y_2044_ = v___y_2059_;
v___y_2045_ = v___y_2060_;
v___y_2046_ = v___x_2066_;
v___y_2047_ = v___y_2061_;
v___y_2048_ = v___y_2062_;
v___y_2049_ = v___y_2063_;
v___y_2050_ = v___y_2064_;
v___y_2051_ = v___y_2065_;
v___y_2052_ = v___y_2059_;
goto v___jp_2041_;
}
}
v___jp_2069_:
{
uint64_t v___x_2081_; uint8_t v___x_2082_; 
v___x_2081_ = lean_uint64_shift_right(v___y_2079_, v___y_2076_);
v___x_2082_ = lean_uint64_dec_eq(v___x_2081_, v___y_2075_);
if (v___x_2082_ == 0)
{
uint64_t v___x_2083_; 
v___x_2083_ = lean_uint64_add(v___y_2072_, v___y_2076_);
v___y_2057_ = v___y_2071_;
v___y_2058_ = v___y_2070_;
v___y_2059_ = v___y_2080_;
v___y_2060_ = v___y_2073_;
v___y_2061_ = v___y_2074_;
v___y_2062_ = v___y_2075_;
v___y_2063_ = v___y_2077_;
v___y_2064_ = v___y_2078_;
v___y_2065_ = v___x_2083_;
goto v___jp_2056_;
}
else
{
v___y_2057_ = v___y_2071_;
v___y_2058_ = v___y_2070_;
v___y_2059_ = v___y_2080_;
v___y_2060_ = v___y_2073_;
v___y_2061_ = v___y_2074_;
v___y_2062_ = v___y_2075_;
v___y_2063_ = v___y_2077_;
v___y_2064_ = v___y_2078_;
v___y_2065_ = v___y_2072_;
goto v___jp_2056_;
}
}
v___jp_2084_:
{
uint64_t v___x_2094_; uint64_t v___x_2095_; uint8_t v___x_2096_; 
v___x_2094_ = 4ULL;
v___x_2095_ = lean_uint64_shift_right(v___y_2092_, v___x_2094_);
v___x_2096_ = lean_uint64_dec_eq(v___x_2095_, v___y_2089_);
if (v___x_2096_ == 0)
{
v___y_2070_ = v___y_2086_;
v___y_2071_ = v___y_2085_;
v___y_2072_ = v___y_2093_;
v___y_2073_ = v___y_2087_;
v___y_2074_ = v___y_2088_;
v___y_2075_ = v___y_2089_;
v___y_2076_ = v___x_2094_;
v___y_2077_ = v___y_2090_;
v___y_2078_ = v___y_2091_;
v___y_2079_ = v___y_2092_;
v___y_2080_ = v___x_2095_;
goto v___jp_2069_;
}
else
{
v___y_2070_ = v___y_2086_;
v___y_2071_ = v___y_2085_;
v___y_2072_ = v___y_2093_;
v___y_2073_ = v___y_2087_;
v___y_2074_ = v___y_2088_;
v___y_2075_ = v___y_2089_;
v___y_2076_ = v___x_2094_;
v___y_2077_ = v___y_2090_;
v___y_2078_ = v___y_2091_;
v___y_2079_ = v___y_2092_;
v___y_2080_ = v___y_2092_;
goto v___jp_2069_;
}
}
v___jp_2097_:
{
uint64_t v___x_2109_; uint8_t v___x_2110_; 
v___x_2109_ = lean_uint64_shift_right(v___y_2102_, v___y_2101_);
v___x_2110_ = lean_uint64_dec_eq(v___x_2109_, v___y_2105_);
if (v___x_2110_ == 0)
{
uint64_t v___x_2111_; 
v___x_2111_ = lean_uint64_add(v___y_2100_, v___y_2101_);
v___y_2085_ = v___y_2099_;
v___y_2086_ = v___y_2098_;
v___y_2087_ = v___y_2103_;
v___y_2088_ = v___y_2104_;
v___y_2089_ = v___y_2105_;
v___y_2090_ = v___y_2106_;
v___y_2091_ = v___y_2107_;
v___y_2092_ = v___y_2108_;
v___y_2093_ = v___x_2111_;
goto v___jp_2084_;
}
else
{
v___y_2085_ = v___y_2099_;
v___y_2086_ = v___y_2098_;
v___y_2087_ = v___y_2103_;
v___y_2088_ = v___y_2104_;
v___y_2089_ = v___y_2105_;
v___y_2090_ = v___y_2106_;
v___y_2091_ = v___y_2107_;
v___y_2092_ = v___y_2108_;
v___y_2093_ = v___y_2100_;
goto v___jp_2084_;
}
}
v___jp_2112_:
{
uint64_t v___x_2122_; uint64_t v___x_2123_; uint8_t v___x_2124_; 
v___x_2122_ = 8ULL;
v___x_2123_ = lean_uint64_shift_right(v___y_2115_, v___x_2122_);
v___x_2124_ = lean_uint64_dec_eq(v___x_2123_, v___y_2118_);
if (v___x_2124_ == 0)
{
v___y_2098_ = v___y_2114_;
v___y_2099_ = v___y_2113_;
v___y_2100_ = v___y_2121_;
v___y_2101_ = v___x_2122_;
v___y_2102_ = v___y_2115_;
v___y_2103_ = v___y_2116_;
v___y_2104_ = v___y_2117_;
v___y_2105_ = v___y_2118_;
v___y_2106_ = v___y_2119_;
v___y_2107_ = v___y_2120_;
v___y_2108_ = v___x_2123_;
goto v___jp_2097_;
}
else
{
v___y_2098_ = v___y_2114_;
v___y_2099_ = v___y_2113_;
v___y_2100_ = v___y_2121_;
v___y_2101_ = v___x_2122_;
v___y_2102_ = v___y_2115_;
v___y_2103_ = v___y_2116_;
v___y_2104_ = v___y_2117_;
v___y_2105_ = v___y_2118_;
v___y_2106_ = v___y_2119_;
v___y_2107_ = v___y_2120_;
v___y_2108_ = v___y_2115_;
goto v___jp_2097_;
}
}
v___jp_2125_:
{
uint64_t v___x_2137_; uint8_t v___x_2138_; 
v___x_2137_ = lean_uint64_shift_right(v___y_2135_, v___y_2131_);
v___x_2138_ = lean_uint64_dec_eq(v___x_2137_, v___y_2132_);
if (v___x_2138_ == 0)
{
uint64_t v___x_2139_; 
v___x_2139_ = lean_uint64_add(v___y_2126_, v___y_2131_);
v___y_2113_ = v___y_2128_;
v___y_2114_ = v___y_2127_;
v___y_2115_ = v___y_2136_;
v___y_2116_ = v___y_2129_;
v___y_2117_ = v___y_2130_;
v___y_2118_ = v___y_2132_;
v___y_2119_ = v___y_2133_;
v___y_2120_ = v___y_2134_;
v___y_2121_ = v___x_2139_;
goto v___jp_2112_;
}
else
{
v___y_2113_ = v___y_2128_;
v___y_2114_ = v___y_2127_;
v___y_2115_ = v___y_2136_;
v___y_2116_ = v___y_2129_;
v___y_2117_ = v___y_2130_;
v___y_2118_ = v___y_2132_;
v___y_2119_ = v___y_2133_;
v___y_2120_ = v___y_2134_;
v___y_2121_ = v___y_2126_;
goto v___jp_2112_;
}
}
v___jp_2140_:
{
uint64_t v___x_2150_; uint64_t v___x_2151_; uint8_t v___x_2152_; 
v___x_2150_ = 16ULL;
v___x_2151_ = lean_uint64_shift_right(v___y_2148_, v___x_2150_);
v___x_2152_ = lean_uint64_dec_eq(v___x_2151_, v___y_2145_);
if (v___x_2152_ == 0)
{
v___y_2126_ = v___y_2149_;
v___y_2127_ = v___y_2142_;
v___y_2128_ = v___y_2141_;
v___y_2129_ = v___y_2143_;
v___y_2130_ = v___y_2144_;
v___y_2131_ = v___x_2150_;
v___y_2132_ = v___y_2145_;
v___y_2133_ = v___y_2146_;
v___y_2134_ = v___y_2147_;
v___y_2135_ = v___y_2148_;
v___y_2136_ = v___x_2151_;
goto v___jp_2125_;
}
else
{
v___y_2126_ = v___y_2149_;
v___y_2127_ = v___y_2142_;
v___y_2128_ = v___y_2141_;
v___y_2129_ = v___y_2143_;
v___y_2130_ = v___y_2144_;
v___y_2131_ = v___x_2150_;
v___y_2132_ = v___y_2145_;
v___y_2133_ = v___y_2146_;
v___y_2134_ = v___y_2147_;
v___y_2135_ = v___y_2148_;
v___y_2136_ = v___y_2148_;
goto v___jp_2125_;
}
}
v___jp_2153_:
{
uint64_t v___x_2163_; uint8_t v___x_2164_; 
v___x_2163_ = lean_uint64_shift_right(v___y_2160_, v___y_2156_);
v___x_2164_ = lean_uint64_dec_eq(v___x_2163_, v___y_2159_);
if (v___x_2164_ == 0)
{
v___y_2141_ = v___y_2155_;
v___y_2142_ = v___y_2154_;
v___y_2143_ = v___y_2157_;
v___y_2144_ = v___y_2158_;
v___y_2145_ = v___y_2159_;
v___y_2146_ = v___y_2160_;
v___y_2147_ = v___y_2161_;
v___y_2148_ = v___y_2162_;
v___y_2149_ = v___y_2156_;
goto v___jp_2140_;
}
else
{
v___y_2141_ = v___y_2155_;
v___y_2142_ = v___y_2154_;
v___y_2143_ = v___y_2157_;
v___y_2144_ = v___y_2158_;
v___y_2145_ = v___y_2159_;
v___y_2146_ = v___y_2160_;
v___y_2147_ = v___y_2161_;
v___y_2148_ = v___y_2162_;
v___y_2149_ = v___y_2159_;
goto v___jp_2140_;
}
}
v___jp_2165_:
{
uint64_t v___x_2172_; uint8_t v___x_2173_; 
v___x_2172_ = 0ULL;
v___x_2173_ = lean_uint64_dec_eq(v___y_2170_, v___x_2172_);
if (v___x_2173_ == 0)
{
uint64_t v___x_2174_; uint64_t v___x_2175_; uint8_t v___x_2176_; 
v___x_2174_ = 32ULL;
v___x_2175_ = lean_uint64_shift_right(v___y_2170_, v___x_2174_);
v___x_2176_ = lean_uint64_dec_eq(v___x_2175_, v___x_2172_);
if (v___x_2176_ == 0)
{
v___y_2154_ = v___y_2167_;
v___y_2155_ = v___y_2166_;
v___y_2156_ = v___x_2174_;
v___y_2157_ = v___y_2168_;
v___y_2158_ = v___y_2169_;
v___y_2159_ = v___x_2172_;
v___y_2160_ = v___y_2170_;
v___y_2161_ = v___y_2171_;
v___y_2162_ = v___x_2175_;
goto v___jp_2153_;
}
else
{
v___y_2154_ = v___y_2167_;
v___y_2155_ = v___y_2166_;
v___y_2156_ = v___x_2174_;
v___y_2157_ = v___y_2168_;
v___y_2158_ = v___y_2169_;
v___y_2159_ = v___x_2172_;
v___y_2160_ = v___y_2170_;
v___y_2161_ = v___y_2171_;
v___y_2162_ = v___y_2170_;
goto v___jp_2153_;
}
}
else
{
if (v___y_2171_ == 0)
{
uint32_t v___x_2177_; 
v___x_2177_ = 0;
return v___x_2177_;
}
else
{
uint32_t v___x_2178_; 
v___x_2178_ = 2147483648;
return v___x_2178_;
}
}
}
v___jp_2179_:
{
uint64_t v___x_2188_; uint64_t v___x_2189_; uint64_t v___x_2190_; uint8_t v___x_2191_; 
v___x_2188_ = lean_uint64_mul(v___y_2183_, v___y_2185_);
v___x_2189_ = lean_uint64_add(v___y_2184_, v___y_2187_);
v___x_2190_ = 281474976710656ULL;
v___x_2191_ = lean_uint64_dec_lt(v___x_2188_, v___x_2190_);
if (v___x_2191_ == 0)
{
v___y_2166_ = v___y_2181_;
v___y_2167_ = v___y_2180_;
v___y_2168_ = v___y_2182_;
v___y_2169_ = v___x_2189_;
v___y_2170_ = v___x_2188_;
v___y_2171_ = v___y_2186_;
goto v___jp_2165_;
}
else
{
uint64_t v___x_2192_; uint8_t v___x_2193_; 
v___x_2192_ = 123ULL;
v___x_2193_ = lean_uint64_dec_le(v___x_2189_, v___x_2192_);
if (v___x_2193_ == 0)
{
v___y_2166_ = v___y_2181_;
v___y_2167_ = v___y_2180_;
v___y_2168_ = v___y_2182_;
v___y_2169_ = v___x_2189_;
v___y_2170_ = v___x_2188_;
v___y_2171_ = v___y_2186_;
goto v___jp_2165_;
}
else
{
uint64_t v___x_2194_; uint8_t v___x_2195_; 
v___x_2194_ = 0ULL;
v___x_2195_ = lean_uint64_dec_eq(v___x_2188_, v___x_2194_);
if (v___x_2195_ == 0)
{
uint64_t v___x_2196_; uint64_t v___x_2197_; uint8_t v___x_2198_; 
v___x_2196_ = 149ULL;
v___x_2197_ = lean_uint64_sub(v___x_2196_, v___x_2189_);
v___x_2198_ = lean_uint64_dec_eq(v___x_2197_, v___x_2194_);
if (v___x_2198_ == 0)
{
uint64_t v___x_2199_; uint8_t v___x_2200_; 
v___x_2199_ = 64ULL;
v___x_2200_ = lean_uint64_dec_lt(v___x_2197_, v___x_2199_);
if (v___x_2200_ == 0)
{
uint8_t v___x_2201_; 
v___x_2201_ = lean_uint64_dec_eq(v___x_2197_, v___x_2199_);
if (v___x_2201_ == 0)
{
v___y_1932_ = v___y_2182_;
v___y_1933_ = v___x_2194_;
v___y_1934_ = v___y_2186_;
v___y_1935_ = v___x_2194_;
goto v___jp_1931_;
}
else
{
uint64_t v___x_2202_; uint8_t v___x_2203_; 
v___x_2202_ = 9223372036854775808ULL;
v___x_2203_ = lean_uint64_dec_lt(v___x_2202_, v___x_2188_);
if (v___x_2203_ == 0)
{
v___y_1932_ = v___y_2182_;
v___y_1933_ = v___x_2194_;
v___y_1934_ = v___y_2186_;
v___y_1935_ = v___x_2194_;
goto v___jp_1931_;
}
else
{
uint64_t v___x_2204_; 
v___x_2204_ = 1ULL;
v___y_1932_ = v___y_2182_;
v___y_1933_ = v___x_2194_;
v___y_1934_ = v___y_2186_;
v___y_1935_ = v___x_2204_;
goto v___jp_1931_;
}
}
}
else
{
uint64_t v_quotient_2205_; uint64_t v___x_2206_; uint64_t v___x_2207_; uint64_t v___x_2208_; uint64_t v_remainder_2209_; uint64_t v___x_2210_; uint64_t v_half_2211_; uint8_t v___x_2212_; 
v_quotient_2205_ = lean_uint64_shift_right(v___x_2188_, v___x_2197_);
v___x_2206_ = 1ULL;
v___x_2207_ = lean_uint64_shift_left(v___x_2206_, v___x_2197_);
v___x_2208_ = lean_uint64_sub(v___x_2207_, v___x_2206_);
v_remainder_2209_ = lean_uint64_land(v___x_2188_, v___x_2208_);
v___x_2210_ = lean_uint64_sub(v___x_2197_, v___x_2206_);
v_half_2211_ = lean_uint64_shift_left(v___x_2206_, v___x_2210_);
v___x_2212_ = lean_uint64_dec_lt(v_remainder_2209_, v_half_2211_);
if (v___x_2212_ == 0)
{
uint8_t v___x_2213_; 
v___x_2213_ = lean_uint64_dec_lt(v_half_2211_, v_remainder_2209_);
if (v___x_2213_ == 0)
{
uint64_t v___x_2214_; uint8_t v___x_2215_; 
v___x_2214_ = lean_uint64_land(v_quotient_2205_, v___x_2206_);
v___x_2215_ = lean_uint64_dec_eq(v___x_2214_, v___x_2194_);
if (v___x_2215_ == 0)
{
uint64_t v___x_2216_; 
v___x_2216_ = lean_uint64_add(v_quotient_2205_, v___x_2206_);
v___y_1932_ = v___y_2182_;
v___y_1933_ = v___x_2194_;
v___y_1934_ = v___y_2186_;
v___y_1935_ = v___x_2216_;
goto v___jp_1931_;
}
else
{
v___y_1932_ = v___y_2182_;
v___y_1933_ = v___x_2194_;
v___y_1934_ = v___y_2186_;
v___y_1935_ = v_quotient_2205_;
goto v___jp_1931_;
}
}
else
{
uint64_t v___x_2217_; 
v___x_2217_ = lean_uint64_add(v_quotient_2205_, v___x_2206_);
v___y_1932_ = v___y_2182_;
v___y_1933_ = v___x_2194_;
v___y_1934_ = v___y_2186_;
v___y_1935_ = v___x_2217_;
goto v___jp_1931_;
}
}
else
{
v___y_1932_ = v___y_2182_;
v___y_1933_ = v___x_2194_;
v___y_1934_ = v___y_2186_;
v___y_1935_ = v_quotient_2205_;
goto v___jp_1931_;
}
}
}
else
{
v___y_1932_ = v___y_2182_;
v___y_1933_ = v___x_2194_;
v___y_1934_ = v___y_2186_;
v___y_1935_ = v___x_2188_;
goto v___jp_1931_;
}
}
else
{
if (v___y_2186_ == 0)
{
uint32_t v___x_2218_; 
v___x_2218_ = 0;
return v___x_2218_;
}
else
{
uint32_t v___x_2219_; 
v___x_2219_ = 2147483648;
return v___x_2219_;
}
}
}
}
}
v___jp_2220_:
{
uint64_t v___x_2229_; uint64_t v___x_2230_; uint8_t v___x_2231_; 
v___x_2229_ = lean_uint32_to_uint64(v___y_2221_);
v___x_2230_ = 0ULL;
v___x_2231_ = lean_uint64_dec_eq(v___x_2229_, v___x_2230_);
if (v___x_2231_ == 0)
{
uint64_t v___x_2232_; uint64_t v___x_2233_; 
v___x_2232_ = 1ULL;
v___x_2233_ = lean_uint64_sub(v___x_2229_, v___x_2232_);
v___y_2180_ = v___y_2223_;
v___y_2181_ = v___y_2222_;
v___y_2182_ = v___y_2224_;
v___y_2183_ = v___y_2225_;
v___y_2184_ = v___y_2228_;
v___y_2185_ = v___y_2226_;
v___y_2186_ = v___y_2227_;
v___y_2187_ = v___x_2233_;
goto v___jp_2179_;
}
else
{
v___y_2180_ = v___y_2223_;
v___y_2181_ = v___y_2222_;
v___y_2182_ = v___y_2224_;
v___y_2183_ = v___y_2225_;
v___y_2184_ = v___y_2228_;
v___y_2185_ = v___y_2226_;
v___y_2186_ = v___y_2227_;
v___y_2187_ = v___x_2230_;
goto v___jp_2179_;
}
}
v___jp_2234_:
{
uint64_t v___x_2243_; uint64_t v___x_2244_; uint8_t v___x_2245_; 
v___x_2243_ = lean_uint32_to_uint64(v___y_2241_);
v___x_2244_ = 0ULL;
v___x_2245_ = lean_uint64_dec_eq(v___x_2243_, v___x_2244_);
if (v___x_2245_ == 0)
{
uint64_t v___x_2246_; uint64_t v___x_2247_; 
v___x_2246_ = 1ULL;
v___x_2247_ = lean_uint64_sub(v___x_2243_, v___x_2246_);
v___y_2221_ = v___y_2237_;
v___y_2222_ = v___y_2236_;
v___y_2223_ = v___y_2235_;
v___y_2224_ = v___y_2238_;
v___y_2225_ = v___y_2239_;
v___y_2226_ = v___y_2242_;
v___y_2227_ = v___y_2240_;
v___y_2228_ = v___x_2247_;
goto v___jp_2220_;
}
else
{
v___y_2221_ = v___y_2237_;
v___y_2222_ = v___y_2236_;
v___y_2223_ = v___y_2235_;
v___y_2224_ = v___y_2238_;
v___y_2225_ = v___y_2239_;
v___y_2226_ = v___y_2242_;
v___y_2227_ = v___y_2240_;
v___y_2228_ = v___x_2244_;
goto v___jp_2220_;
}
}
v___jp_2248_:
{
uint32_t v___x_2257_; uint8_t v___x_2258_; 
v___x_2257_ = 0;
v___x_2258_ = lean_uint32_dec_eq(v___y_2250_, v___x_2257_);
if (v___x_2258_ == 0)
{
uint64_t v___x_2259_; uint64_t v___x_2260_; uint64_t v___x_2261_; 
v___x_2259_ = lean_uint32_to_uint64(v___y_2249_);
v___x_2260_ = 8388608ULL;
v___x_2261_ = lean_uint64_lor(v___x_2259_, v___x_2260_);
v___y_2235_ = v___y_2252_;
v___y_2236_ = v___y_2251_;
v___y_2237_ = v___y_2250_;
v___y_2238_ = v___y_2253_;
v___y_2239_ = v___y_2256_;
v___y_2240_ = v___y_2254_;
v___y_2241_ = v___y_2255_;
v___y_2242_ = v___x_2261_;
goto v___jp_2234_;
}
else
{
uint64_t v___x_2262_; 
v___x_2262_ = lean_uint32_to_uint64(v___y_2249_);
v___y_2235_ = v___y_2252_;
v___y_2236_ = v___y_2251_;
v___y_2237_ = v___y_2250_;
v___y_2238_ = v___y_2253_;
v___y_2239_ = v___y_2256_;
v___y_2240_ = v___y_2254_;
v___y_2241_ = v___y_2255_;
v___y_2242_ = v___x_2262_;
goto v___jp_2234_;
}
}
v___jp_2263_:
{
uint32_t v___x_2269_; uint32_t v_xFraction_2270_; uint32_t v_yFraction_2271_; uint32_t v___x_2272_; uint8_t v___x_2273_; 
v___x_2269_ = 8388607;
v_xFraction_2270_ = lean_uint32_land(v___y_1400_, v___x_2269_);
v_yFraction_2271_ = lean_uint32_land(v___y_1401_, v___x_2269_);
v___x_2272_ = 0;
v___x_2273_ = lean_uint32_dec_eq(v___y_2266_, v___x_2272_);
if (v___x_2273_ == 0)
{
uint64_t v___x_2274_; uint64_t v___x_2275_; uint64_t v___x_2276_; 
v___x_2274_ = lean_uint32_to_uint64(v_xFraction_2270_);
v___x_2275_ = 8388608ULL;
v___x_2276_ = lean_uint64_lor(v___x_2274_, v___x_2275_);
v___y_1913_ = v___x_2269_;
v___y_1914_ = v___y_2268_;
v___y_1915_ = v___y_2264_;
v___y_1916_ = v_yFraction_2271_;
v___y_1917_ = v___y_2265_;
v___y_1918_ = v___y_2266_;
v___y_1919_ = v___y_2267_;
v___y_1920_ = v___x_2276_;
goto v___jp_1912_;
}
else
{
uint64_t v___x_2277_; 
v___x_2277_ = lean_uint32_to_uint64(v_xFraction_2270_);
v___y_1913_ = v___x_2269_;
v___y_1914_ = v___y_2268_;
v___y_1915_ = v___y_2264_;
v___y_1916_ = v_yFraction_2271_;
v___y_1917_ = v___y_2265_;
v___y_1918_ = v___y_2266_;
v___y_1919_ = v___y_2267_;
v___y_1920_ = v___x_2277_;
goto v___jp_1912_;
}
}
v___jp_2278_:
{
if (v___y_2283_ == 0)
{
if (v___y_2286_ == 0)
{
v___y_2264_ = v___y_2280_;
v___y_2265_ = v___y_2282_;
v___y_2266_ = v___y_2284_;
v___y_2267_ = v___y_2285_;
v___y_2268_ = v___y_2279_;
goto v___jp_2263_;
}
else
{
v___y_2264_ = v___y_2280_;
v___y_2265_ = v___y_2282_;
v___y_2266_ = v___y_2284_;
v___y_2267_ = v___y_2285_;
v___y_2268_ = v___y_2281_;
goto v___jp_2263_;
}
}
else
{
if (v___y_2286_ == 0)
{
v___y_2264_ = v___y_2280_;
v___y_2265_ = v___y_2282_;
v___y_2266_ = v___y_2284_;
v___y_2267_ = v___y_2285_;
v___y_2268_ = v___y_2281_;
goto v___jp_2263_;
}
else
{
v___y_2264_ = v___y_2280_;
v___y_2265_ = v___y_2282_;
v___y_2266_ = v___y_2284_;
v___y_2267_ = v___y_2285_;
v___y_2268_ = v___y_2279_;
goto v___jp_2263_;
}
}
}
v___jp_2287_:
{
uint32_t v___x_2295_; uint32_t v___x_2296_; uint32_t v___x_2297_; uint8_t v___x_2298_; 
v___x_2295_ = 2147483648;
v___x_2296_ = lean_uint32_land(v___y_1401_, v___x_2295_);
v___x_2297_ = 0;
v___x_2298_ = lean_uint32_dec_eq(v___x_2296_, v___x_2297_);
if (v___x_2298_ == 0)
{
v___y_2279_ = v___y_2288_;
v___y_2280_ = v___y_2289_;
v___y_2281_ = v___y_2290_;
v___y_2282_ = v___y_2291_;
v___y_2283_ = v___y_2294_;
v___y_2284_ = v___y_2292_;
v___y_2285_ = v___y_2293_;
v___y_2286_ = v___y_2290_;
goto v___jp_2278_;
}
else
{
v___y_2279_ = v___y_2288_;
v___y_2280_ = v___y_2289_;
v___y_2281_ = v___y_2290_;
v___y_2282_ = v___y_2291_;
v___y_2283_ = v___y_2294_;
v___y_2284_ = v___y_2292_;
v___y_2285_ = v___y_2293_;
v___y_2286_ = v___y_2288_;
goto v___jp_2278_;
}
}
v___jp_2299_:
{
if (v___y_2305_ == 0)
{
uint32_t v___x_2306_; uint32_t v___x_2307_; uint32_t v___x_2308_; uint8_t v___x_2309_; 
v___x_2306_ = 2147483648;
v___x_2307_ = lean_uint32_land(v___y_1400_, v___x_2306_);
v___x_2308_ = 0;
v___x_2309_ = lean_uint32_dec_eq(v___x_2307_, v___x_2308_);
if (v___x_2309_ == 0)
{
v___y_2288_ = v___y_2305_;
v___y_2289_ = v___y_2300_;
v___y_2290_ = v___y_2301_;
v___y_2291_ = v___y_2302_;
v___y_2292_ = v___y_2303_;
v___y_2293_ = v___y_2304_;
v___y_2294_ = v___y_2301_;
goto v___jp_2287_;
}
else
{
v___y_2288_ = v___y_2305_;
v___y_2289_ = v___y_2300_;
v___y_2290_ = v___y_2301_;
v___y_2291_ = v___y_2302_;
v___y_2292_ = v___y_2303_;
v___y_2293_ = v___y_2304_;
v___y_2294_ = v___y_2305_;
goto v___jp_2287_;
}
}
else
{
lean_object* v___x_2310_; lean_object* v___x_2311_; lean_object* v___x_2312_; uint32_t v___x_2313_; 
v___x_2310_ = lean_uint32_to_nat(v___y_1400_);
v___x_2311_ = lean_uint32_to_nat(v___y_1401_);
v___x_2312_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2310_, v___x_2311_);
v___x_2313_ = lean_uint32_of_nat(v___x_2312_);
lean_dec(v___x_2312_);
return v___x_2313_;
}
}
v___jp_2314_:
{
uint32_t v___x_2320_; uint32_t v_xFraction_2321_; uint32_t v_yFraction_2322_; uint32_t v___x_2323_; uint8_t v___x_2324_; 
v___x_2320_ = 8388607;
v_xFraction_2321_ = lean_uint32_land(v___y_1400_, v___x_2320_);
v_yFraction_2322_ = lean_uint32_land(v___y_1401_, v___x_2320_);
v___x_2323_ = 0;
v___x_2324_ = lean_uint32_dec_eq(v___y_2318_, v___x_2323_);
if (v___x_2324_ == 0)
{
uint64_t v___x_2325_; uint64_t v___x_2326_; uint64_t v___x_2327_; 
v___x_2325_ = lean_uint32_to_uint64(v_xFraction_2321_);
v___x_2326_ = 8388608ULL;
v___x_2327_ = lean_uint64_lor(v___x_2325_, v___x_2326_);
v___y_2249_ = v_yFraction_2322_;
v___y_2250_ = v___y_2317_;
v___y_2251_ = v___y_2316_;
v___y_2252_ = v___y_2315_;
v___y_2253_ = v___x_2320_;
v___y_2254_ = v___y_2319_;
v___y_2255_ = v___y_2318_;
v___y_2256_ = v___x_2327_;
goto v___jp_2248_;
}
else
{
uint64_t v___x_2328_; 
v___x_2328_ = lean_uint32_to_uint64(v_xFraction_2321_);
v___y_2249_ = v_yFraction_2322_;
v___y_2250_ = v___y_2317_;
v___y_2251_ = v___y_2316_;
v___y_2252_ = v___y_2315_;
v___y_2253_ = v___x_2320_;
v___y_2254_ = v___y_2319_;
v___y_2255_ = v___y_2318_;
v___y_2256_ = v___x_2328_;
goto v___jp_2248_;
}
}
v___jp_2329_:
{
uint8_t v___x_2334_; 
v___x_2334_ = 1;
v___y_2315_ = v___y_2332_;
v___y_2316_ = v___y_2331_;
v___y_2317_ = v___y_2330_;
v___y_2318_ = v___y_2333_;
v___y_2319_ = v___x_2334_;
goto v___jp_2314_;
}
v___jp_2335_:
{
if (v___y_2340_ == 0)
{
if (v___y_2342_ == 0)
{
v___y_2315_ = v___y_2338_;
v___y_2316_ = v___y_2337_;
v___y_2317_ = v___y_2336_;
v___y_2318_ = v___y_2341_;
v___y_2319_ = v___y_2339_;
goto v___jp_2314_;
}
else
{
v___y_2330_ = v___y_2336_;
v___y_2331_ = v___y_2337_;
v___y_2332_ = v___y_2338_;
v___y_2333_ = v___y_2341_;
goto v___jp_2329_;
}
}
else
{
if (v___y_2342_ == 0)
{
v___y_2330_ = v___y_2336_;
v___y_2331_ = v___y_2337_;
v___y_2332_ = v___y_2338_;
v___y_2333_ = v___y_2341_;
goto v___jp_2329_;
}
else
{
v___y_2315_ = v___y_2338_;
v___y_2316_ = v___y_2337_;
v___y_2317_ = v___y_2336_;
v___y_2318_ = v___y_2341_;
v___y_2319_ = v___y_2339_;
goto v___jp_2314_;
}
}
}
v___jp_2343_:
{
uint32_t v___x_2350_; uint32_t v___x_2351_; uint32_t v___x_2352_; uint8_t v___x_2353_; 
v___x_2350_ = 2147483648;
v___x_2351_ = lean_uint32_land(v___y_1401_, v___x_2350_);
v___x_2352_ = 0;
v___x_2353_ = lean_uint32_dec_eq(v___x_2351_, v___x_2352_);
if (v___x_2353_ == 0)
{
uint8_t v___x_2354_; 
v___x_2354_ = 1;
v___y_2336_ = v___y_2346_;
v___y_2337_ = v___y_2345_;
v___y_2338_ = v___y_2344_;
v___y_2339_ = v___y_2347_;
v___y_2340_ = v___y_2349_;
v___y_2341_ = v___y_2348_;
v___y_2342_ = v___x_2354_;
goto v___jp_2335_;
}
else
{
v___y_2336_ = v___y_2346_;
v___y_2337_ = v___y_2345_;
v___y_2338_ = v___y_2344_;
v___y_2339_ = v___y_2347_;
v___y_2340_ = v___y_2349_;
v___y_2341_ = v___y_2348_;
v___y_2342_ = v___y_2347_;
goto v___jp_2335_;
}
}
v___jp_2355_:
{
if (v___y_2360_ == 0)
{
uint32_t v___x_2361_; uint32_t v___x_2362_; uint32_t v___x_2363_; uint8_t v___x_2364_; 
v___x_2361_ = 2147483648;
v___x_2362_ = lean_uint32_land(v___y_1400_, v___x_2361_);
v___x_2363_ = 0;
v___x_2364_ = lean_uint32_dec_eq(v___x_2362_, v___x_2363_);
if (v___x_2364_ == 0)
{
uint8_t v___x_2365_; 
v___x_2365_ = 1;
v___y_2344_ = v___y_2356_;
v___y_2345_ = v___y_2357_;
v___y_2346_ = v___y_2358_;
v___y_2347_ = v___y_2360_;
v___y_2348_ = v___y_2359_;
v___y_2349_ = v___x_2365_;
goto v___jp_2343_;
}
else
{
v___y_2344_ = v___y_2356_;
v___y_2345_ = v___y_2357_;
v___y_2346_ = v___y_2358_;
v___y_2347_ = v___y_2360_;
v___y_2348_ = v___y_2359_;
v___y_2349_ = v___y_2360_;
goto v___jp_2343_;
}
}
else
{
lean_object* v___x_2366_; lean_object* v___x_2367_; lean_object* v___x_2368_; uint32_t v___x_2369_; 
v___x_2366_ = lean_uint32_to_nat(v___y_1400_);
v___x_2367_ = lean_uint32_to_nat(v___y_1401_);
v___x_2368_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2366_, v___x_2367_);
v___x_2369_ = lean_uint32_of_nat(v___x_2368_);
lean_dec(v___x_2368_);
return v___x_2369_;
}
}
v___jp_2370_:
{
if (v___y_2371_ == 0)
{
uint32_t v___x_2372_; 
v___x_2372_ = lp_competition_Submission_FastMul_mul(v___y_1400_, v___y_1401_);
return v___x_2372_;
}
else
{
uint32_t v___x_2373_; uint32_t v___x_2374_; 
v___x_2373_ = 4194304;
v___x_2374_ = lean_uint32_lor(v___y_1401_, v___x_2373_);
return v___x_2374_;
}
}
v___jp_2375_:
{
uint32_t v___x_2376_; uint32_t v___x_2377_; uint32_t v___x_2378_; uint32_t v___x_2379_; uint8_t v___x_2380_; 
v___x_2376_ = 23;
v___x_2377_ = lean_uint32_shift_right(v___y_1401_, v___x_2376_);
v___x_2378_ = 255;
v___x_2379_ = lean_uint32_land(v___x_2377_, v___x_2378_);
v___x_2380_ = lean_uint32_dec_eq(v___x_2379_, v___x_2378_);
if (v___x_2380_ == 0)
{
v___y_2371_ = v___x_2380_;
goto v___jp_2370_;
}
else
{
uint32_t v___x_2381_; uint32_t v___x_2382_; uint32_t v___x_2383_; uint8_t v___x_2384_; 
v___x_2381_ = 8388607;
v___x_2382_ = lean_uint32_land(v___y_1401_, v___x_2381_);
v___x_2383_ = 0;
v___x_2384_ = lean_uint32_dec_eq(v___x_2382_, v___x_2383_);
if (v___x_2384_ == 0)
{
v___y_2371_ = v___x_2380_;
goto v___jp_2370_;
}
else
{
uint32_t v___x_2385_; 
v___x_2385_ = lp_competition_Submission_FastMul_mul(v___y_1400_, v___y_1401_);
return v___x_2385_;
}
}
}
v___jp_2386_:
{
if (v___y_2387_ == 0)
{
goto v___jp_2375_;
}
else
{
uint32_t v___x_2388_; uint32_t v___x_2389_; 
v___x_2388_ = 4194304;
v___x_2389_ = lean_uint32_lor(v___y_1400_, v___x_2388_);
return v___x_2389_;
}
}
v___jp_2390_:
{
uint32_t v___x_2391_; uint32_t v___x_2392_; uint32_t v___x_2393_; uint32_t v___x_2394_; uint8_t v___x_2395_; 
v___x_2391_ = 23;
v___x_2392_ = lean_uint32_shift_right(v___y_1400_, v___x_2391_);
v___x_2393_ = 255;
v___x_2394_ = lean_uint32_land(v___x_2392_, v___x_2393_);
v___x_2395_ = lean_uint32_dec_eq(v___x_2394_, v___x_2393_);
if (v___x_2395_ == 0)
{
v___y_2387_ = v___x_2395_;
goto v___jp_2386_;
}
else
{
uint32_t v___x_2396_; uint32_t v___x_2397_; uint32_t v___x_2398_; uint8_t v___x_2399_; 
v___x_2396_ = 8388607;
v___x_2397_ = lean_uint32_land(v___y_1400_, v___x_2396_);
v___x_2398_ = 0;
v___x_2399_ = lean_uint32_dec_eq(v___x_2397_, v___x_2398_);
if (v___x_2399_ == 0)
{
v___y_2387_ = v___x_2395_;
goto v___jp_2386_;
}
else
{
goto v___jp_2375_;
}
}
}
v___jp_2400_:
{
if (v___y_2401_ == 0)
{
goto v___jp_2390_;
}
else
{
uint32_t v___x_2402_; uint32_t v___x_2403_; uint32_t v___x_2404_; uint8_t v___x_2405_; 
v___x_2402_ = 4194304;
v___x_2403_ = lean_uint32_land(v___y_1401_, v___x_2402_);
v___x_2404_ = 0;
v___x_2405_ = lean_uint32_dec_eq(v___x_2403_, v___x_2404_);
if (v___x_2405_ == 0)
{
goto v___jp_2390_;
}
else
{
uint32_t v___x_2406_; 
v___x_2406_ = lean_uint32_lor(v___y_1401_, v___x_2402_);
return v___x_2406_;
}
}
}
v___jp_2407_:
{
uint32_t v___x_2408_; uint32_t v___x_2409_; uint32_t v___x_2410_; uint32_t v___x_2411_; uint8_t v___x_2412_; 
v___x_2408_ = 23;
v___x_2409_ = lean_uint32_shift_right(v___y_1401_, v___x_2408_);
v___x_2410_ = 255;
v___x_2411_ = lean_uint32_land(v___x_2409_, v___x_2410_);
v___x_2412_ = lean_uint32_dec_eq(v___x_2411_, v___x_2410_);
if (v___x_2412_ == 0)
{
v___y_2401_ = v___x_2412_;
goto v___jp_2400_;
}
else
{
uint32_t v___x_2413_; uint32_t v___x_2414_; uint32_t v___x_2415_; uint8_t v___x_2416_; 
v___x_2413_ = 8388607;
v___x_2414_ = lean_uint32_land(v___y_1401_, v___x_2413_);
v___x_2415_ = 0;
v___x_2416_ = lean_uint32_dec_eq(v___x_2414_, v___x_2415_);
if (v___x_2416_ == 0)
{
v___y_2401_ = v___x_2412_;
goto v___jp_2400_;
}
else
{
goto v___jp_2390_;
}
}
}
v___jp_2417_:
{
if (v___y_2418_ == 0)
{
goto v___jp_2407_;
}
else
{
uint32_t v___x_2419_; uint32_t v___x_2420_; uint32_t v___x_2421_; uint8_t v___x_2422_; 
v___x_2419_ = 4194304;
v___x_2420_ = lean_uint32_land(v___y_1400_, v___x_2419_);
v___x_2421_ = 0;
v___x_2422_ = lean_uint32_dec_eq(v___x_2420_, v___x_2421_);
if (v___x_2422_ == 0)
{
goto v___jp_2407_;
}
else
{
uint32_t v___x_2423_; 
v___x_2423_ = lean_uint32_lor(v___y_1400_, v___x_2419_);
return v___x_2423_;
}
}
}
v___jp_2424_:
{
float v_result_2427_; uint8_t v___x_2428_; 
v_result_2427_ = lean_float32_mul(v___y_2425_, v___y_2426_);
v___x_2428_ = lean_float32_beq(v_result_2427_, v_result_2427_);
if (v___x_2428_ == 0)
{
uint32_t v___x_2429_; uint32_t v___x_2430_; uint32_t v___x_2431_; uint32_t v___x_2432_; uint8_t v___x_2433_; 
v___x_2429_ = 23;
v___x_2430_ = lean_uint32_shift_right(v___y_1400_, v___x_2429_);
v___x_2431_ = 255;
v___x_2432_ = lean_uint32_land(v___x_2430_, v___x_2431_);
v___x_2433_ = lean_uint32_dec_eq(v___x_2432_, v___x_2431_);
if (v___x_2433_ == 0)
{
v___y_2418_ = v___x_2433_;
goto v___jp_2417_;
}
else
{
uint32_t v___x_2434_; uint32_t v___x_2435_; uint32_t v___x_2436_; uint8_t v___x_2437_; 
v___x_2434_ = 8388607;
v___x_2435_ = lean_uint32_land(v___y_1400_, v___x_2434_);
v___x_2436_ = 0;
v___x_2437_ = lean_uint32_dec_eq(v___x_2435_, v___x_2436_);
if (v___x_2437_ == 0)
{
v___y_2418_ = v___x_2433_;
goto v___jp_2417_;
}
else
{
goto v___jp_2407_;
}
}
}
else
{
uint32_t v___x_2438_; 
v___x_2438_ = lean_float32_to_bits(v_result_2427_);
return v___x_2438_;
}
}
v___jp_2439_:
{
if (v___y_2441_ == 0)
{
float v___x_2442_; 
v___x_2442_ = lean_float32_of_bits(v___y_1401_);
v___y_2425_ = v___y_2440_;
v___y_2426_ = v___x_2442_;
goto v___jp_2424_;
}
else
{
uint32_t v___x_2443_; uint32_t v___x_2444_; uint32_t v___x_2445_; uint32_t v___x_2446_; float v___x_2447_; lean_object* v___x_2448_; uint32_t v___x_2449_; uint32_t v___x_2450_; lean_object* v___x_2451_; lean_object* v___x_2452_; float v___x_2453_; float v___x_2454_; 
v___x_2443_ = 8388607;
v___x_2444_ = lean_uint32_land(v___y_1401_, v___x_2443_);
v___x_2445_ = 8388608;
v___x_2446_ = lean_uint32_lor(v___x_2444_, v___x_2445_);
v___x_2447_ = lean_uint32_to_float32(v___x_2446_);
v___x_2448_ = lp_competition_R2W01b_scaleTable;
v___x_2449_ = 23;
v___x_2450_ = lean_uint32_shift_right(v___y_1401_, v___x_2449_);
v___x_2451_ = lean_uint32_to_nat(v___x_2450_);
v___x_2452_ = lean_array_fget_borrowed(v___x_2448_, v___x_2451_);
lean_dec(v___x_2451_);
v___x_2453_ = lean_unbox_float32(v___x_2452_);
v___x_2454_ = lean_float32_mul(v___x_2447_, v___x_2453_);
v___y_2425_ = v___y_2440_;
v___y_2426_ = v___x_2454_;
goto v___jp_2424_;
}
}
v___jp_2455_:
{
uint32_t v___x_2457_; uint32_t v_a_2458_; uint32_t v___x_2459_; uint32_t v___x_2460_; uint32_t v___x_2461_; uint8_t v___x_2462_; 
v___x_2457_ = 2147483647;
v_a_2458_ = lean_uint32_land(v___y_1401_, v___x_2457_);
v___x_2459_ = 201326591;
v___x_2460_ = 1;
v___x_2461_ = lean_uint32_sub(v_a_2458_, v___x_2460_);
v___x_2462_ = lean_uint32_dec_le(v___x_2459_, v___x_2461_);
if (v___x_2462_ == 0)
{
v___y_2440_ = v___y_2456_;
v___y_2441_ = v___x_2462_;
goto v___jp_2439_;
}
else
{
uint32_t v___x_2463_; uint8_t v___x_2464_; 
v___x_2463_ = 2139095040;
v___x_2464_ = lean_uint32_dec_lt(v_a_2458_, v___x_2463_);
v___y_2440_ = v___y_2456_;
v___y_2441_ = v___x_2464_;
goto v___jp_2439_;
}
}
v___jp_2465_:
{
if (v___y_2467_ == 0)
{
float v___x_2468_; 
v___x_2468_ = lean_float32_of_bits(v___y_1400_);
v___y_2456_ = v___x_2468_;
goto v___jp_2455_;
}
else
{
uint32_t v___x_2469_; uint32_t v___x_2470_; uint32_t v___x_2471_; uint32_t v___x_2472_; float v___x_2473_; lean_object* v___x_2474_; lean_object* v___x_2475_; lean_object* v___x_2476_; float v___x_2477_; float v___x_2478_; 
v___x_2469_ = 8388607;
v___x_2470_ = lean_uint32_land(v___y_1400_, v___x_2469_);
v___x_2471_ = 8388608;
v___x_2472_ = lean_uint32_lor(v___x_2470_, v___x_2471_);
v___x_2473_ = lean_uint32_to_float32(v___x_2472_);
v___x_2474_ = lp_competition_R2W01b_scaleTable;
v___x_2475_ = lean_uint32_to_nat(v___y_2466_);
v___x_2476_ = lean_array_fget_borrowed(v___x_2474_, v___x_2475_);
lean_dec(v___x_2475_);
v___x_2477_ = lean_unbox_float32(v___x_2476_);
v___x_2478_ = lean_float32_mul(v___x_2473_, v___x_2477_);
v___y_2456_ = v___x_2478_;
goto v___jp_2455_;
}
}
v___jp_2479_:
{
if (v___y_2480_ == 0)
{
uint32_t v___x_2481_; 
v___x_2481_ = lp_competition_Submission_FastMul_mul(v___y_1400_, v___y_1401_);
return v___x_2481_;
}
else
{
uint32_t v___x_2482_; uint32_t v___x_2483_; 
v___x_2482_ = 4194304;
v___x_2483_ = lean_uint32_lor(v___y_1401_, v___x_2482_);
return v___x_2483_;
}
}
v___jp_2484_:
{
uint32_t v___x_2485_; uint32_t v___x_2486_; uint32_t v___x_2487_; uint32_t v___x_2488_; uint8_t v___x_2489_; 
v___x_2485_ = 23;
v___x_2486_ = lean_uint32_shift_right(v___y_1401_, v___x_2485_);
v___x_2487_ = 255;
v___x_2488_ = lean_uint32_land(v___x_2486_, v___x_2487_);
v___x_2489_ = lean_uint32_dec_eq(v___x_2488_, v___x_2487_);
if (v___x_2489_ == 0)
{
v___y_2480_ = v___x_2489_;
goto v___jp_2479_;
}
else
{
uint32_t v___x_2490_; uint32_t v___x_2491_; uint32_t v___x_2492_; uint8_t v___x_2493_; 
v___x_2490_ = 8388607;
v___x_2491_ = lean_uint32_land(v___y_1401_, v___x_2490_);
v___x_2492_ = 0;
v___x_2493_ = lean_uint32_dec_eq(v___x_2491_, v___x_2492_);
if (v___x_2493_ == 0)
{
v___y_2480_ = v___x_2489_;
goto v___jp_2479_;
}
else
{
uint32_t v___x_2494_; 
v___x_2494_ = lp_competition_Submission_FastMul_mul(v___y_1400_, v___y_1401_);
return v___x_2494_;
}
}
}
v___jp_2495_:
{
if (v___y_2496_ == 0)
{
goto v___jp_2484_;
}
else
{
uint32_t v___x_2497_; uint32_t v___x_2498_; 
v___x_2497_ = 4194304;
v___x_2498_ = lean_uint32_lor(v___y_1400_, v___x_2497_);
return v___x_2498_;
}
}
v___jp_2499_:
{
uint32_t v___x_2500_; uint32_t v___x_2501_; uint32_t v___x_2502_; uint32_t v___x_2503_; uint8_t v___x_2504_; 
v___x_2500_ = 23;
v___x_2501_ = lean_uint32_shift_right(v___y_1400_, v___x_2500_);
v___x_2502_ = 255;
v___x_2503_ = lean_uint32_land(v___x_2501_, v___x_2502_);
v___x_2504_ = lean_uint32_dec_eq(v___x_2503_, v___x_2502_);
if (v___x_2504_ == 0)
{
v___y_2496_ = v___x_2504_;
goto v___jp_2495_;
}
else
{
uint32_t v___x_2505_; uint32_t v___x_2506_; uint32_t v___x_2507_; uint8_t v___x_2508_; 
v___x_2505_ = 8388607;
v___x_2506_ = lean_uint32_land(v___y_1400_, v___x_2505_);
v___x_2507_ = 0;
v___x_2508_ = lean_uint32_dec_eq(v___x_2506_, v___x_2507_);
if (v___x_2508_ == 0)
{
v___y_2496_ = v___x_2504_;
goto v___jp_2495_;
}
else
{
goto v___jp_2484_;
}
}
}
v___jp_2509_:
{
if (v___y_2510_ == 0)
{
goto v___jp_2499_;
}
else
{
uint32_t v___x_2511_; uint32_t v___x_2512_; uint32_t v___x_2513_; uint8_t v___x_2514_; 
v___x_2511_ = 4194304;
v___x_2512_ = lean_uint32_land(v___y_1401_, v___x_2511_);
v___x_2513_ = 0;
v___x_2514_ = lean_uint32_dec_eq(v___x_2512_, v___x_2513_);
if (v___x_2514_ == 0)
{
goto v___jp_2499_;
}
else
{
uint32_t v___x_2515_; 
v___x_2515_ = lean_uint32_lor(v___y_1401_, v___x_2511_);
return v___x_2515_;
}
}
}
v___jp_2516_:
{
uint32_t v___x_2517_; uint32_t v___x_2518_; uint32_t v___x_2519_; uint32_t v___x_2520_; uint8_t v___x_2521_; 
v___x_2517_ = 23;
v___x_2518_ = lean_uint32_shift_right(v___y_1401_, v___x_2517_);
v___x_2519_ = 255;
v___x_2520_ = lean_uint32_land(v___x_2518_, v___x_2519_);
v___x_2521_ = lean_uint32_dec_eq(v___x_2520_, v___x_2519_);
if (v___x_2521_ == 0)
{
v___y_2510_ = v___x_2521_;
goto v___jp_2509_;
}
else
{
uint32_t v___x_2522_; uint32_t v___x_2523_; uint32_t v___x_2524_; uint8_t v___x_2525_; 
v___x_2522_ = 8388607;
v___x_2523_ = lean_uint32_land(v___y_1401_, v___x_2522_);
v___x_2524_ = 0;
v___x_2525_ = lean_uint32_dec_eq(v___x_2523_, v___x_2524_);
if (v___x_2525_ == 0)
{
v___y_2510_ = v___x_2521_;
goto v___jp_2509_;
}
else
{
goto v___jp_2499_;
}
}
}
v___jp_2526_:
{
if (v___y_2527_ == 0)
{
goto v___jp_2516_;
}
else
{
uint32_t v___x_2528_; uint32_t v___x_2529_; uint32_t v___x_2530_; uint8_t v___x_2531_; 
v___x_2528_ = 4194304;
v___x_2529_ = lean_uint32_land(v___y_1400_, v___x_2528_);
v___x_2530_ = 0;
v___x_2531_ = lean_uint32_dec_eq(v___x_2529_, v___x_2530_);
if (v___x_2531_ == 0)
{
goto v___jp_2516_;
}
else
{
uint32_t v___x_2532_; 
v___x_2532_ = lean_uint32_lor(v___y_1400_, v___x_2528_);
return v___x_2532_;
}
}
}
v___jp_2533_:
{
float v_result_2536_; uint8_t v___x_2537_; 
v_result_2536_ = lean_float32_mul(v___y_2534_, v___y_2535_);
v___x_2537_ = lean_float32_beq(v_result_2536_, v_result_2536_);
if (v___x_2537_ == 0)
{
uint32_t v___x_2538_; uint32_t v___x_2539_; uint32_t v___x_2540_; uint32_t v___x_2541_; uint8_t v___x_2542_; 
v___x_2538_ = 23;
v___x_2539_ = lean_uint32_shift_right(v___y_1400_, v___x_2538_);
v___x_2540_ = 255;
v___x_2541_ = lean_uint32_land(v___x_2539_, v___x_2540_);
v___x_2542_ = lean_uint32_dec_eq(v___x_2541_, v___x_2540_);
if (v___x_2542_ == 0)
{
v___y_2527_ = v___x_2542_;
goto v___jp_2526_;
}
else
{
uint32_t v___x_2543_; uint32_t v___x_2544_; uint32_t v___x_2545_; uint8_t v___x_2546_; 
v___x_2543_ = 8388607;
v___x_2544_ = lean_uint32_land(v___y_1400_, v___x_2543_);
v___x_2545_ = 0;
v___x_2546_ = lean_uint32_dec_eq(v___x_2544_, v___x_2545_);
if (v___x_2546_ == 0)
{
v___y_2527_ = v___x_2542_;
goto v___jp_2526_;
}
else
{
goto v___jp_2516_;
}
}
}
else
{
uint32_t v___x_2547_; 
v___x_2547_ = lean_float32_to_bits(v_result_2536_);
return v___x_2547_;
}
}
v___jp_2548_:
{
if (v___y_2550_ == 0)
{
float v___x_2551_; 
v___x_2551_ = lean_float32_of_bits(v___y_1401_);
v___y_2534_ = v___y_2549_;
v___y_2535_ = v___x_2551_;
goto v___jp_2533_;
}
else
{
uint32_t v___x_2552_; uint32_t v___x_2553_; uint32_t v___x_2554_; uint32_t v___x_2555_; float v___x_2556_; lean_object* v___x_2557_; uint32_t v___x_2558_; uint32_t v___x_2559_; lean_object* v___x_2560_; lean_object* v___x_2561_; float v___x_2562_; float v___x_2563_; 
v___x_2552_ = 8388607;
v___x_2553_ = lean_uint32_land(v___y_1401_, v___x_2552_);
v___x_2554_ = 8388608;
v___x_2555_ = lean_uint32_lor(v___x_2553_, v___x_2554_);
v___x_2556_ = lean_uint32_to_float32(v___x_2555_);
v___x_2557_ = lp_competition_R2W01b_scaleTable;
v___x_2558_ = 23;
v___x_2559_ = lean_uint32_shift_right(v___y_1401_, v___x_2558_);
v___x_2560_ = lean_uint32_to_nat(v___x_2559_);
v___x_2561_ = lean_array_fget_borrowed(v___x_2557_, v___x_2560_);
lean_dec(v___x_2560_);
v___x_2562_ = lean_unbox_float32(v___x_2561_);
v___x_2563_ = lean_float32_mul(v___x_2556_, v___x_2562_);
v___y_2534_ = v___y_2549_;
v___y_2535_ = v___x_2563_;
goto v___jp_2533_;
}
}
v___jp_2564_:
{
uint32_t v___x_2566_; uint32_t v_a_2567_; uint32_t v___x_2568_; uint32_t v___x_2569_; uint32_t v___x_2570_; uint8_t v___x_2571_; 
v___x_2566_ = 2147483647;
v_a_2567_ = lean_uint32_land(v___y_1401_, v___x_2566_);
v___x_2568_ = 201326591;
v___x_2569_ = 1;
v___x_2570_ = lean_uint32_sub(v_a_2567_, v___x_2569_);
v___x_2571_ = lean_uint32_dec_le(v___x_2568_, v___x_2570_);
if (v___x_2571_ == 0)
{
v___y_2549_ = v___y_2565_;
v___y_2550_ = v___x_2571_;
goto v___jp_2548_;
}
else
{
uint32_t v___x_2572_; uint8_t v___x_2573_; 
v___x_2572_ = 2139095040;
v___x_2573_ = lean_uint32_dec_lt(v_a_2567_, v___x_2572_);
v___y_2549_ = v___y_2565_;
v___y_2550_ = v___x_2573_;
goto v___jp_2548_;
}
}
v___jp_2574_:
{
if (v___y_2576_ == 0)
{
float v___x_2577_; 
v___x_2577_ = lean_float32_of_bits(v___y_1400_);
v___y_2565_ = v___x_2577_;
goto v___jp_2564_;
}
else
{
uint32_t v___x_2578_; uint32_t v___x_2579_; uint32_t v___x_2580_; uint32_t v___x_2581_; float v___x_2582_; lean_object* v___x_2583_; lean_object* v___x_2584_; lean_object* v___x_2585_; float v___x_2586_; float v___x_2587_; 
v___x_2578_ = 8388607;
v___x_2579_ = lean_uint32_land(v___y_1400_, v___x_2578_);
v___x_2580_ = 8388608;
v___x_2581_ = lean_uint32_lor(v___x_2579_, v___x_2580_);
v___x_2582_ = lean_uint32_to_float32(v___x_2581_);
v___x_2583_ = lp_competition_R2W01b_scaleTable;
v___x_2584_ = lean_uint32_to_nat(v___y_2575_);
v___x_2585_ = lean_array_fget_borrowed(v___x_2583_, v___x_2584_);
lean_dec(v___x_2584_);
v___x_2586_ = lean_unbox_float32(v___x_2585_);
v___x_2587_ = lean_float32_mul(v___x_2582_, v___x_2586_);
v___y_2565_ = v___x_2587_;
goto v___jp_2564_;
}
}
v___jp_2588_:
{
if (v___y_2589_ == 0)
{
uint32_t v___x_2590_; uint32_t v___x_2591_; uint32_t v___x_2592_; uint32_t v_ex_2593_; uint32_t v___x_2594_; uint32_t v_ey_2595_; uint32_t v___x_2596_; uint32_t v___x_2597_; uint8_t v___x_2598_; 
v___x_2590_ = 23;
v___x_2591_ = lean_uint32_shift_right(v___y_1400_, v___x_2590_);
v___x_2592_ = 255;
v_ex_2593_ = lean_uint32_land(v___x_2591_, v___x_2592_);
v___x_2594_ = lean_uint32_shift_right(v___y_1401_, v___x_2590_);
v_ey_2595_ = lean_uint32_land(v___x_2594_, v___x_2592_);
v___x_2596_ = lean_uint32_add(v_ex_2593_, v_ey_2595_);
v___x_2597_ = 128;
v___x_2598_ = lean_uint32_dec_lt(v___x_2596_, v___x_2597_);
if (v___x_2598_ == 0)
{
uint32_t v___x_2599_; uint32_t v_a_2600_; uint32_t v___x_2601_; uint32_t v___x_2602_; uint32_t v___x_2603_; uint8_t v___x_2604_; 
v___x_2599_ = 2147483647;
v_a_2600_ = lean_uint32_land(v___y_1400_, v___x_2599_);
v___x_2601_ = 201326591;
v___x_2602_ = 1;
v___x_2603_ = lean_uint32_sub(v_a_2600_, v___x_2602_);
v___x_2604_ = lean_uint32_dec_le(v___x_2601_, v___x_2603_);
if (v___x_2604_ == 0)
{
v___y_2575_ = v___x_2591_;
v___y_2576_ = v___x_2604_;
goto v___jp_2574_;
}
else
{
uint32_t v___x_2605_; uint8_t v___x_2606_; 
v___x_2605_ = 2139095040;
v___x_2606_ = lean_uint32_dec_lt(v_a_2600_, v___x_2605_);
v___y_2575_ = v___x_2591_;
v___y_2576_ = v___x_2606_;
goto v___jp_2574_;
}
}
else
{
uint32_t v___x_2607_; uint32_t v___x_2608_; uint32_t v___x_2609_; uint8_t v___x_2610_; 
v___x_2607_ = 4278190080;
v___x_2608_ = 1;
v___x_2609_ = lean_uint32_shift_left(v___y_1400_, v___x_2608_);
v___x_2610_ = lean_uint32_dec_le(v___x_2607_, v___x_2609_);
if (v___x_2610_ == 0)
{
uint32_t v___x_2611_; uint8_t v___x_2612_; 
v___x_2611_ = lean_uint32_shift_left(v___y_1401_, v___x_2608_);
v___x_2612_ = lean_uint32_dec_le(v___x_2607_, v___x_2611_);
v___y_2356_ = v___x_2592_;
v___y_2357_ = v___x_2590_;
v___y_2358_ = v_ey_2595_;
v___y_2359_ = v_ex_2593_;
v___y_2360_ = v___x_2612_;
goto v___jp_2355_;
}
else
{
v___y_2356_ = v___x_2592_;
v___y_2357_ = v___x_2590_;
v___y_2358_ = v_ey_2595_;
v___y_2359_ = v_ex_2593_;
v___y_2360_ = v___x_2610_;
goto v___jp_2355_;
}
}
}
else
{
uint32_t v___x_2613_; uint32_t v___x_2614_; uint32_t v___x_2615_; uint32_t v___x_2616_; uint32_t v___x_2617_; uint32_t v___x_2618_; uint32_t v___x_2619_; uint32_t v___x_2620_; uint32_t v___x_2621_; uint32_t v___x_2622_; uint8_t v___x_2623_; 
v___x_2613_ = 23;
v___x_2614_ = lean_uint32_shift_right(v___y_1400_, v___x_2613_);
v___x_2615_ = 255;
v___x_2616_ = lean_uint32_land(v___x_2614_, v___x_2615_);
v___x_2617_ = lean_uint32_shift_right(v___y_1401_, v___x_2613_);
v___x_2618_ = lean_uint32_land(v___x_2617_, v___x_2615_);
v___x_2619_ = lean_uint32_add(v___x_2616_, v___x_2618_);
v___x_2620_ = 128;
v___x_2621_ = lean_uint32_sub(v___x_2619_, v___x_2620_);
v___x_2622_ = 252;
v___x_2623_ = lean_uint32_dec_le(v___x_2621_, v___x_2622_);
if (v___x_2623_ == 0)
{
uint8_t v___x_2624_; 
v___x_2624_ = lean_uint32_dec_lt(v___x_2619_, v___x_2620_);
if (v___x_2624_ == 0)
{
uint32_t v___x_2625_; uint32_t v_a_2626_; uint32_t v___x_2627_; uint32_t v___x_2628_; uint32_t v___x_2629_; uint8_t v___x_2630_; 
v___x_2625_ = 2147483647;
v_a_2626_ = lean_uint32_land(v___y_1400_, v___x_2625_);
v___x_2627_ = 201326591;
v___x_2628_ = 1;
v___x_2629_ = lean_uint32_sub(v_a_2626_, v___x_2628_);
v___x_2630_ = lean_uint32_dec_le(v___x_2627_, v___x_2629_);
if (v___x_2630_ == 0)
{
v___y_2466_ = v___x_2614_;
v___y_2467_ = v___x_2630_;
goto v___jp_2465_;
}
else
{
uint32_t v___x_2631_; uint8_t v___x_2632_; 
v___x_2631_ = 2139095040;
v___x_2632_ = lean_uint32_dec_lt(v_a_2626_, v___x_2631_);
v___y_2466_ = v___x_2614_;
v___y_2467_ = v___x_2632_;
goto v___jp_2465_;
}
}
else
{
uint32_t v___x_2633_; uint32_t v___x_2634_; uint32_t v___x_2635_; uint8_t v___x_2636_; 
v___x_2633_ = 4278190080;
v___x_2634_ = 1;
v___x_2635_ = lean_uint32_shift_left(v___y_1400_, v___x_2634_);
v___x_2636_ = lean_uint32_dec_le(v___x_2633_, v___x_2635_);
if (v___x_2636_ == 0)
{
uint32_t v___x_2637_; uint8_t v___x_2638_; 
v___x_2637_ = lean_uint32_shift_left(v___y_1401_, v___x_2634_);
v___x_2638_ = lean_uint32_dec_le(v___x_2633_, v___x_2637_);
v___y_2300_ = v___x_2618_;
v___y_2301_ = v___y_2589_;
v___y_2302_ = v___x_2613_;
v___y_2303_ = v___x_2616_;
v___y_2304_ = v___x_2615_;
v___y_2305_ = v___x_2638_;
goto v___jp_2299_;
}
else
{
v___y_2300_ = v___x_2618_;
v___y_2301_ = v___y_2589_;
v___y_2302_ = v___x_2613_;
v___y_2303_ = v___x_2616_;
v___y_2304_ = v___x_2615_;
v___y_2305_ = v___x_2636_;
goto v___jp_2299_;
}
}
}
else
{
uint32_t v___x_2639_; uint32_t v___x_2640_; uint32_t v___x_2641_; uint32_t v___x_2642_; float v___x_2643_; uint32_t v___x_2644_; uint32_t v___x_2645_; float v___x_2646_; float v___x_2647_; uint32_t v_mid_2648_; uint32_t v___x_2649_; uint8_t v___x_2650_; uint8_t v___x_2651_; 
v___x_2639_ = 8388607;
v___x_2640_ = lean_uint32_land(v___y_1400_, v___x_2639_);
v___x_2641_ = 8388608;
v___x_2642_ = lean_uint32_lor(v___x_2640_, v___x_2641_);
v___x_2643_ = lean_uint32_to_float32(v___x_2642_);
v___x_2644_ = lean_uint32_land(v___y_1401_, v___x_2639_);
v___x_2645_ = lean_uint32_lor(v___x_2644_, v___x_2641_);
v___x_2646_ = lean_uint32_to_float32(v___x_2645_);
v___x_2647_ = lean_float32_mul(v___x_2643_, v___x_2646_);
v_mid_2648_ = lean_float32_to_bits(v___x_2647_);
v___x_2649_ = 2147483648;
v___x_2650_ = lean_uint32_dec_le(v___x_2649_, v___y_1400_);
v___x_2651_ = lean_uint32_dec_le(v___x_2649_, v___y_1401_);
if (v___x_2650_ == 0)
{
if (v___x_2651_ == 0)
{
v___y_1432_ = v___x_2618_;
v___y_1433_ = v___x_2623_;
v___y_1434_ = v___x_2613_;
v___y_1435_ = v___x_2616_;
v___y_1436_ = v___x_2615_;
v___y_1437_ = v_mid_2648_;
v___y_1438_ = v___x_2639_;
v___y_1439_ = v___x_2623_;
goto v___jp_1431_;
}
else
{
v___y_1432_ = v___x_2618_;
v___y_1433_ = v___x_2623_;
v___y_1434_ = v___x_2613_;
v___y_1435_ = v___x_2616_;
v___y_1436_ = v___x_2615_;
v___y_1437_ = v_mid_2648_;
v___y_1438_ = v___x_2639_;
v___y_1439_ = v___x_2650_;
goto v___jp_1431_;
}
}
else
{
v___y_1432_ = v___x_2618_;
v___y_1433_ = v___x_2623_;
v___y_1434_ = v___x_2613_;
v___y_1435_ = v___x_2616_;
v___y_1436_ = v___x_2615_;
v___y_1437_ = v_mid_2648_;
v___y_1438_ = v___x_2639_;
v___y_1439_ = v___x_2651_;
goto v___jp_1431_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_2664_, lean_object* v___y_2665_){
_start:
{
uint32_t v___y_11175__boxed_2666_; uint32_t v___y_11176__boxed_2667_; uint32_t v_res_2668_; lean_object* v_r_2669_; 
v___y_11175__boxed_2666_ = lean_unbox_uint32(v___y_2664_);
lean_dec(v___y_2664_);
v___y_11176__boxed_2667_ = lean_unbox_uint32(v___y_2665_);
lean_dec(v___y_2665_);
v_res_2668_ = lp_competition_main___lam__3(v___y_11175__boxed_2666_, v___y_11176__boxed_2667_);
v_r_2669_ = lean_box_uint32(v_res_2668_);
return v_r_2669_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2677_; lean_object* v___x_2678_; 
v___x_2677_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_2678_ = lean_io_getenv(v___x_2677_);
if (lean_obj_tag(v___x_2678_) == 0)
{
lean_object* v___f_2679_; lean_object* v___f_2680_; lean_object* v___x_2681_; lean_object* v___x_2682_; lean_object* v___x_2683_; 
v___f_2679_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2680_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_2681_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2682_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2683_ = lp_competition_Bench_runFull(v___f_2679_, v___f_2680_, v___x_2681_, v___x_2682_);
return v___x_2683_;
}
else
{
lean_object* v___f_2684_; lean_object* v___f_2685_; lean_object* v___x_2686_; lean_object* v___x_2687_; lean_object* v___x_2688_; 
lean_dec_ref_known(v___x_2678_, 1);
v___f_2684_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2685_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_2686_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2687_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2688_ = lp_competition_Bench_Suite_run(v___f_2684_, v___f_2685_, v___x_2686_, v___x_2687_);
return v___x_2688_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_2689_){
_start:
{
lean_object* v_res_2690_; 
v_res_2690_ = _lean_main();
return v_res_2690_;
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
