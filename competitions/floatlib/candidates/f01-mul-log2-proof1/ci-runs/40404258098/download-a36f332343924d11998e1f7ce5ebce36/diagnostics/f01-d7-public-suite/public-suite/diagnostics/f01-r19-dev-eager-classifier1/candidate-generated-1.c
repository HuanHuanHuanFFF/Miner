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
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
float lean_float32_mul(float, float);
float lean_float32_of_bits(uint32_t);
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
uint8_t v___y_9_; uint8_t v___y_23_; uint8_t v___y_37_; uint8_t v___y_54_; float v___y_61_; float v___y_62_; float v___y_76_; float v___y_90_; uint8_t v___y_91_; float v___y_94_; uint8_t v___y_117_; uint32_t v___x_119_; uint32_t v_a_120_; uint32_t v___x_121_; uint32_t v___x_122_; uint32_t v___x_123_; uint8_t v___x_124_; uint32_t v___x_125_; uint8_t v___x_126_; 
v___x_119_ = 2147483647;
v_a_120_ = lean_uint32_land(v___y_1_, v___x_119_);
v___x_121_ = 201326591;
v___x_122_ = 1;
v___x_123_ = lean_uint32_sub(v_a_120_, v___x_122_);
v___x_124_ = lean_uint32_dec_le(v___x_121_, v___x_123_);
v___x_125_ = 2139095040;
v___x_126_ = lean_uint32_dec_lt(v_a_120_, v___x_125_);
if (v___x_124_ == 0)
{
if (v___x_126_ == 0)
{
goto v___jp_103_;
}
else
{
v___y_117_ = v___x_124_;
goto v___jp_116_;
}
}
else
{
v___y_117_ = v___x_126_;
goto v___jp_116_;
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
uint32_t v___x_77_; uint32_t v___x_78_; uint32_t v___x_79_; uint32_t v___x_80_; float v___x_81_; lean_object* v___x_82_; uint32_t v___x_83_; uint32_t v___x_84_; lean_object* v___x_85_; lean_object* v___x_86_; float v___x_87_; float v___x_88_; 
v___x_77_ = 8388607;
v___x_78_ = lean_uint32_land(v___y_2_, v___x_77_);
v___x_79_ = 8388608;
v___x_80_ = lean_uint32_lor(v___x_78_, v___x_79_);
v___x_81_ = lean_uint32_to_float32(v___x_80_);
v___x_82_ = lp_competition_R2W01b_scaleTable;
v___x_83_ = 23;
v___x_84_ = lean_uint32_shift_right(v___y_2_, v___x_83_);
v___x_85_ = lean_uint32_to_nat(v___x_84_);
v___x_86_ = lean_array_fget_borrowed(v___x_82_, v___x_85_);
lean_dec(v___x_85_);
v___x_87_ = lean_unbox_float32(v___x_86_);
v___x_88_ = lean_float32_mul(v___x_81_, v___x_87_);
v___y_61_ = v___y_76_;
v___y_62_ = v___x_88_;
goto v___jp_60_;
}
v___jp_89_:
{
if (v___y_91_ == 0)
{
float v___x_92_; 
v___x_92_ = lean_float32_of_bits(v___y_2_);
v___y_61_ = v___y_90_;
v___y_62_ = v___x_92_;
goto v___jp_60_;
}
else
{
v___y_76_ = v___y_90_;
goto v___jp_75_;
}
}
v___jp_93_:
{
uint32_t v___x_95_; uint32_t v_a_96_; uint32_t v___x_97_; uint32_t v___x_98_; uint32_t v___x_99_; uint8_t v___x_100_; uint32_t v___x_101_; uint8_t v___x_102_; 
v___x_95_ = 2147483647;
v_a_96_ = lean_uint32_land(v___y_2_, v___x_95_);
v___x_97_ = 201326591;
v___x_98_ = 1;
v___x_99_ = lean_uint32_sub(v_a_96_, v___x_98_);
v___x_100_ = lean_uint32_dec_le(v___x_97_, v___x_99_);
v___x_101_ = 2139095040;
v___x_102_ = lean_uint32_dec_lt(v_a_96_, v___x_101_);
if (v___x_100_ == 0)
{
if (v___x_102_ == 0)
{
v___y_76_ = v___y_94_;
goto v___jp_75_;
}
else
{
v___y_90_ = v___y_94_;
v___y_91_ = v___x_100_;
goto v___jp_89_;
}
}
else
{
v___y_90_ = v___y_94_;
v___y_91_ = v___x_102_;
goto v___jp_89_;
}
}
v___jp_103_:
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
v___y_94_ = v___x_115_;
goto v___jp_93_;
}
v___jp_116_:
{
if (v___y_117_ == 0)
{
float v___x_118_; 
v___x_118_ = lean_float32_of_bits(v___y_1_);
v___y_94_ = v___x_118_;
goto v___jp_93_;
}
else
{
goto v___jp_103_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_127_, lean_object* v___y_128_){
_start:
{
uint32_t v___y_4557__boxed_129_; uint32_t v___y_4558__boxed_130_; uint32_t v_res_131_; lean_object* v_r_132_; 
v___y_4557__boxed_129_ = lean_unbox_uint32(v___y_127_);
lean_dec(v___y_127_);
v___y_4558__boxed_130_ = lean_unbox_uint32(v___y_128_);
lean_dec(v___y_128_);
v_res_131_ = lp_competition_main___lam__0(v___y_4557__boxed_129_, v___y_4558__boxed_130_);
v_r_132_ = lean_box_uint32(v_res_131_);
return v_r_132_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_133_, uint32_t v___y_134_){
_start:
{
uint8_t v___y_136_; uint8_t v___y_152_; uint8_t v___y_166_; uint8_t v___y_183_; float v___y_190_; float v___y_191_; float v___y_205_; float v___y_219_; uint8_t v___y_220_; float v___y_223_; uint32_t v___y_233_; uint32_t v___y_237_; uint32_t v___y_241_; uint32_t v___y_242_; uint32_t v___y_243_; uint32_t v___y_247_; uint8_t v___y_248_; uint64_t v___y_249_; uint64_t v___y_250_; uint32_t v___y_262_; uint32_t v___y_263_; uint32_t v___y_264_; uint32_t v___y_268_; uint8_t v___y_269_; uint64_t v___y_270_; uint64_t v___y_271_; uint32_t v___x_282_; uint32_t v___x_283_; uint8_t v___y_296_; uint32_t v___x_298_; uint32_t v___y_300_; uint32_t v___y_301_; uint32_t v___y_302_; uint32_t v___y_303_; uint32_t v___y_310_; uint32_t v___y_311_; uint8_t v___y_312_; uint32_t v___y_313_; uint32_t v___y_317_; uint64_t v___y_318_; uint8_t v___y_319_; uint64_t v___y_320_; uint64_t v___y_321_; uint32_t v___y_331_; uint8_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint8_t v___y_335_; uint64_t v___y_336_; uint32_t v___y_343_; uint64_t v___y_344_; uint8_t v___y_345_; uint64_t v___y_346_; uint64_t v___y_347_; uint64_t v___y_353_; uint32_t v___y_354_; uint8_t v___y_355_; uint64_t v___y_356_; uint64_t v___y_357_; uint64_t v___y_358_; uint64_t v___y_413_; uint32_t v___y_414_; uint8_t v___y_415_; uint64_t v___y_416_; uint64_t v___y_417_; uint64_t v___y_418_; uint64_t v___y_419_; uint64_t v___y_425_; uint32_t v___y_426_; uint64_t v___y_427_; uint8_t v___y_428_; uint64_t v___y_429_; uint64_t v___y_430_; uint64_t v___y_431_; uint64_t v___y_432_; uint64_t v___y_433_; uint64_t v___y_438_; uint32_t v___y_439_; uint8_t v___y_440_; uint64_t v___y_441_; uint64_t v___y_442_; uint64_t v___y_443_; uint64_t v___y_444_; uint64_t v___y_449_; uint32_t v___y_450_; uint64_t v___y_451_; uint8_t v___y_452_; uint64_t v___y_453_; uint64_t v___y_454_; uint64_t v___y_455_; uint64_t v___y_456_; uint64_t v___y_457_; uint64_t v___y_462_; uint32_t v___y_463_; uint8_t v___y_464_; uint64_t v___y_465_; uint64_t v___y_466_; uint64_t v___y_467_; uint64_t v___y_468_; uint64_t v___y_473_; uint64_t v___y_474_; uint32_t v___y_475_; uint64_t v___y_476_; uint8_t v___y_477_; uint64_t v___y_478_; uint64_t v___y_479_; uint64_t v___y_480_; uint64_t v___y_481_; uint64_t v___y_486_; uint32_t v___y_487_; uint8_t v___y_488_; uint64_t v___y_489_; uint64_t v___y_490_; uint64_t v___y_491_; uint64_t v___y_492_; uint64_t v___y_497_; uint32_t v___y_498_; uint64_t v___y_499_; uint8_t v___y_500_; uint64_t v___y_501_; uint64_t v___y_502_; uint64_t v___y_503_; uint64_t v___y_504_; uint64_t v___y_505_; uint64_t v___y_510_; uint32_t v___y_511_; uint8_t v___y_512_; uint64_t v___y_513_; uint64_t v___y_514_; uint64_t v___y_515_; uint64_t v___y_516_; uint64_t v___y_521_; uint64_t v___y_522_; uint32_t v___y_523_; uint64_t v___y_524_; uint8_t v___y_525_; uint64_t v___y_526_; uint64_t v___y_527_; uint64_t v___y_531_; uint32_t v___y_532_; uint8_t v___y_533_; uint64_t v___y_534_; uint32_t v___y_543_; uint8_t v___y_544_; uint64_t v___y_545_; uint64_t v___y_546_; uint64_t v___y_547_; uint64_t v___y_548_; uint32_t v_ex_581_; uint32_t v___x_582_; uint32_t v_ey_583_; uint32_t v___y_585_; uint8_t v___y_586_; uint64_t v___y_587_; uint64_t v___y_588_; uint64_t v___y_589_; uint32_t v___y_596_; uint8_t v___y_597_; uint64_t v___y_598_; uint64_t v___y_599_; uint32_t v___y_606_; uint8_t v___y_607_; uint32_t v___y_608_; uint64_t v___y_609_; uint8_t v___y_617_; uint32_t v___x_627_; uint32_t v___x_628_; uint8_t v___x_629_; uint8_t v___y_631_; uint8_t v___y_632_; uint8_t v___y_634_; uint8_t v___y_635_; uint8_t v___y_636_; uint8_t v___y_638_; uint8_t v___y_639_; uint8_t v___y_645_; 
v___x_282_ = 23;
v___x_283_ = lean_uint32_shift_right(v___y_133_, v___x_282_);
v___x_298_ = 255;
v_ex_581_ = lean_uint32_land(v___x_283_, v___x_298_);
v___x_582_ = lean_uint32_shift_right(v___y_134_, v___x_282_);
v_ey_583_ = lean_uint32_land(v___x_582_, v___x_298_);
v___x_627_ = lean_uint32_add(v_ex_581_, v_ey_583_);
v___x_628_ = 128;
v___x_629_ = lean_uint32_dec_lt(v___x_627_, v___x_628_);
if (v___x_629_ == 0)
{
uint32_t v___x_654_; uint32_t v_a_655_; uint32_t v___x_656_; uint32_t v___x_657_; uint32_t v___x_658_; uint8_t v___x_659_; uint32_t v___x_660_; uint8_t v___x_661_; 
v___x_654_ = 2147483647;
v_a_655_ = lean_uint32_land(v___y_133_, v___x_654_);
v___x_656_ = 201326591;
v___x_657_ = 1;
v___x_658_ = lean_uint32_sub(v_a_655_, v___x_657_);
v___x_659_ = lean_uint32_dec_le(v___x_656_, v___x_658_);
v___x_660_ = 2139095040;
v___x_661_ = lean_uint32_dec_lt(v_a_655_, v___x_660_);
if (v___x_659_ == 0)
{
if (v___x_661_ == 0)
{
goto v___jp_284_;
}
else
{
v___y_296_ = v___x_659_;
goto v___jp_295_;
}
}
else
{
v___y_296_ = v___x_661_;
goto v___jp_295_;
}
}
else
{
uint32_t v___x_662_; uint32_t v___x_663_; uint32_t v___x_664_; uint8_t v___x_665_; 
v___x_662_ = 4278190080;
v___x_663_ = 1;
v___x_664_ = lean_uint32_shift_left(v___y_133_, v___x_663_);
v___x_665_ = lean_uint32_dec_le(v___x_662_, v___x_664_);
if (v___x_665_ == 0)
{
uint32_t v___x_666_; uint8_t v___x_667_; 
v___x_666_ = lean_uint32_shift_left(v___y_134_, v___x_663_);
v___x_667_ = lean_uint32_dec_le(v___x_662_, v___x_666_);
v___y_645_ = v___x_667_;
goto v___jp_644_;
}
else
{
v___y_645_ = v___x_665_;
goto v___jp_644_;
}
}
v___jp_135_:
{
if (v___y_136_ == 0)
{
uint32_t v___x_137_; 
v___x_137_ = lp_competition_Submission_FastMul_mul(v___y_133_, v___y_134_);
return v___x_137_;
}
else
{
uint32_t v___x_138_; uint32_t v___x_139_; 
v___x_138_ = 4194304;
v___x_139_ = lean_uint32_lor(v___y_134_, v___x_138_);
return v___x_139_;
}
}
v___jp_140_:
{
uint32_t v___x_141_; uint32_t v___x_142_; uint32_t v___x_143_; uint32_t v___x_144_; uint8_t v___x_145_; 
v___x_141_ = 23;
v___x_142_ = lean_uint32_shift_right(v___y_134_, v___x_141_);
v___x_143_ = 255;
v___x_144_ = lean_uint32_land(v___x_142_, v___x_143_);
v___x_145_ = lean_uint32_dec_eq(v___x_144_, v___x_143_);
if (v___x_145_ == 0)
{
v___y_136_ = v___x_145_;
goto v___jp_135_;
}
else
{
uint32_t v___x_146_; uint32_t v___x_147_; uint32_t v___x_148_; uint8_t v___x_149_; 
v___x_146_ = 8388607;
v___x_147_ = lean_uint32_land(v___y_134_, v___x_146_);
v___x_148_ = 0;
v___x_149_ = lean_uint32_dec_eq(v___x_147_, v___x_148_);
if (v___x_149_ == 0)
{
v___y_136_ = v___x_145_;
goto v___jp_135_;
}
else
{
uint32_t v___x_150_; 
v___x_150_ = lp_competition_Submission_FastMul_mul(v___y_133_, v___y_134_);
return v___x_150_;
}
}
}
v___jp_151_:
{
if (v___y_152_ == 0)
{
goto v___jp_140_;
}
else
{
uint32_t v___x_153_; uint32_t v___x_154_; 
v___x_153_ = 4194304;
v___x_154_ = lean_uint32_lor(v___y_133_, v___x_153_);
return v___x_154_;
}
}
v___jp_155_:
{
uint32_t v___x_156_; uint32_t v___x_157_; uint32_t v___x_158_; uint32_t v___x_159_; uint8_t v___x_160_; 
v___x_156_ = 23;
v___x_157_ = lean_uint32_shift_right(v___y_133_, v___x_156_);
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
v___x_162_ = lean_uint32_land(v___y_133_, v___x_161_);
v___x_163_ = 0;
v___x_164_ = lean_uint32_dec_eq(v___x_162_, v___x_163_);
if (v___x_164_ == 0)
{
v___y_152_ = v___x_160_;
goto v___jp_151_;
}
else
{
goto v___jp_140_;
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
v___x_168_ = lean_uint32_land(v___y_134_, v___x_167_);
v___x_169_ = 0;
v___x_170_ = lean_uint32_dec_eq(v___x_168_, v___x_169_);
if (v___x_170_ == 0)
{
goto v___jp_155_;
}
else
{
uint32_t v___x_171_; 
v___x_171_ = lean_uint32_lor(v___y_134_, v___x_167_);
return v___x_171_;
}
}
}
v___jp_172_:
{
uint32_t v___x_173_; uint32_t v___x_174_; uint32_t v___x_175_; uint32_t v___x_176_; uint8_t v___x_177_; 
v___x_173_ = 23;
v___x_174_ = lean_uint32_shift_right(v___y_134_, v___x_173_);
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
v___x_179_ = lean_uint32_land(v___y_134_, v___x_178_);
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
v___x_185_ = lean_uint32_land(v___y_133_, v___x_184_);
v___x_186_ = 0;
v___x_187_ = lean_uint32_dec_eq(v___x_185_, v___x_186_);
if (v___x_187_ == 0)
{
goto v___jp_172_;
}
else
{
uint32_t v___x_188_; 
v___x_188_ = lean_uint32_lor(v___y_133_, v___x_184_);
return v___x_188_;
}
}
}
v___jp_189_:
{
float v_result_192_; uint8_t v___x_193_; 
v_result_192_ = lean_float32_mul(v___y_190_, v___y_191_);
v___x_193_ = lean_float32_beq(v_result_192_, v_result_192_);
if (v___x_193_ == 0)
{
uint32_t v___x_194_; uint32_t v___x_195_; uint32_t v___x_196_; uint32_t v___x_197_; uint8_t v___x_198_; 
v___x_194_ = 23;
v___x_195_ = lean_uint32_shift_right(v___y_133_, v___x_194_);
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
v___x_200_ = lean_uint32_land(v___y_133_, v___x_199_);
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
uint32_t v___x_206_; uint32_t v___x_207_; uint32_t v___x_208_; uint32_t v___x_209_; float v___x_210_; lean_object* v___x_211_; uint32_t v___x_212_; uint32_t v___x_213_; lean_object* v___x_214_; lean_object* v___x_215_; float v___x_216_; float v___x_217_; 
v___x_206_ = 8388607;
v___x_207_ = lean_uint32_land(v___y_134_, v___x_206_);
v___x_208_ = 8388608;
v___x_209_ = lean_uint32_lor(v___x_207_, v___x_208_);
v___x_210_ = lean_uint32_to_float32(v___x_209_);
v___x_211_ = lp_competition_R2W01b_scaleTable;
v___x_212_ = 23;
v___x_213_ = lean_uint32_shift_right(v___y_134_, v___x_212_);
v___x_214_ = lean_uint32_to_nat(v___x_213_);
v___x_215_ = lean_array_fget_borrowed(v___x_211_, v___x_214_);
lean_dec(v___x_214_);
v___x_216_ = lean_unbox_float32(v___x_215_);
v___x_217_ = lean_float32_mul(v___x_210_, v___x_216_);
v___y_190_ = v___y_205_;
v___y_191_ = v___x_217_;
goto v___jp_189_;
}
v___jp_218_:
{
if (v___y_220_ == 0)
{
float v___x_221_; 
v___x_221_ = lean_float32_of_bits(v___y_134_);
v___y_190_ = v___y_219_;
v___y_191_ = v___x_221_;
goto v___jp_189_;
}
else
{
v___y_205_ = v___y_219_;
goto v___jp_204_;
}
}
v___jp_222_:
{
uint32_t v___x_224_; uint32_t v_a_225_; uint32_t v___x_226_; uint32_t v___x_227_; uint32_t v___x_228_; uint8_t v___x_229_; uint32_t v___x_230_; uint8_t v___x_231_; 
v___x_224_ = 2147483647;
v_a_225_ = lean_uint32_land(v___y_134_, v___x_224_);
v___x_226_ = 201326591;
v___x_227_ = 1;
v___x_228_ = lean_uint32_sub(v_a_225_, v___x_227_);
v___x_229_ = lean_uint32_dec_le(v___x_226_, v___x_228_);
v___x_230_ = 2139095040;
v___x_231_ = lean_uint32_dec_lt(v_a_225_, v___x_230_);
if (v___x_229_ == 0)
{
if (v___x_231_ == 0)
{
v___y_205_ = v___y_223_;
goto v___jp_204_;
}
else
{
v___y_219_ = v___y_223_;
v___y_220_ = v___x_229_;
goto v___jp_218_;
}
}
else
{
v___y_219_ = v___y_223_;
v___y_220_ = v___x_231_;
goto v___jp_218_;
}
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
uint32_t v___x_238_; uint32_t v___x_239_; 
v___x_238_ = 8388608;
v___x_239_ = lean_uint32_lor(v___y_237_, v___x_238_);
return v___x_239_;
}
v___jp_240_:
{
uint32_t v___x_244_; uint32_t v___x_245_; 
v___x_244_ = lean_uint32_land(v___y_241_, v___y_242_);
v___x_245_ = lean_uint32_lor(v___y_243_, v___x_244_);
return v___x_245_;
}
v___jp_246_:
{
uint8_t v___x_251_; 
v___x_251_ = lean_uint64_dec_eq(v___y_250_, v___y_249_);
if (v___x_251_ == 0)
{
uint64_t v___x_252_; uint8_t v___x_253_; 
v___x_252_ = 8388608ULL;
v___x_253_ = lean_uint64_dec_eq(v___y_250_, v___x_252_);
if (v___x_253_ == 0)
{
uint32_t v___x_254_; 
v___x_254_ = lean_uint64_to_uint32(v___y_250_);
if (v___y_248_ == 0)
{
uint32_t v___x_255_; 
v___x_255_ = 0;
v___y_241_ = v___x_254_;
v___y_242_ = v___y_247_;
v___y_243_ = v___x_255_;
goto v___jp_240_;
}
else
{
uint32_t v___x_256_; 
v___x_256_ = 2147483648;
v___y_241_ = v___x_254_;
v___y_242_ = v___y_247_;
v___y_243_ = v___x_256_;
goto v___jp_240_;
}
}
else
{
if (v___y_248_ == 0)
{
uint32_t v___x_257_; 
v___x_257_ = 0;
v___y_237_ = v___x_257_;
goto v___jp_236_;
}
else
{
uint32_t v___x_258_; 
v___x_258_ = 2147483648;
v___y_237_ = v___x_258_;
goto v___jp_236_;
}
}
}
else
{
if (v___y_248_ == 0)
{
uint32_t v___x_259_; 
v___x_259_ = 0;
return v___x_259_;
}
else
{
uint32_t v___x_260_; 
v___x_260_ = 2147483648;
return v___x_260_;
}
}
}
v___jp_261_:
{
uint32_t v___x_265_; uint32_t v___x_266_; 
v___x_265_ = lean_uint32_land(v___y_263_, v___y_262_);
v___x_266_ = lean_uint32_lor(v___y_264_, v___x_265_);
return v___x_266_;
}
v___jp_267_:
{
uint8_t v___x_272_; 
v___x_272_ = lean_uint64_dec_eq(v___y_271_, v___y_270_);
if (v___x_272_ == 0)
{
uint64_t v___x_273_; uint8_t v___x_274_; 
v___x_273_ = 8388608ULL;
v___x_274_ = lean_uint64_dec_eq(v___y_271_, v___x_273_);
if (v___x_274_ == 0)
{
uint32_t v___x_275_; 
v___x_275_ = lean_uint64_to_uint32(v___y_271_);
if (v___y_269_ == 0)
{
uint32_t v___x_276_; 
v___x_276_ = 0;
v___y_262_ = v___y_268_;
v___y_263_ = v___x_275_;
v___y_264_ = v___x_276_;
goto v___jp_261_;
}
else
{
uint32_t v___x_277_; 
v___x_277_ = 2147483648;
v___y_262_ = v___y_268_;
v___y_263_ = v___x_275_;
v___y_264_ = v___x_277_;
goto v___jp_261_;
}
}
else
{
if (v___y_269_ == 0)
{
uint32_t v___x_278_; 
v___x_278_ = 0;
v___y_233_ = v___x_278_;
goto v___jp_232_;
}
else
{
uint32_t v___x_279_; 
v___x_279_ = 2147483648;
v___y_233_ = v___x_279_;
goto v___jp_232_;
}
}
}
else
{
if (v___y_269_ == 0)
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
}
v___jp_284_:
{
uint32_t v___x_285_; uint32_t v___x_286_; uint32_t v___x_287_; uint32_t v___x_288_; float v___x_289_; lean_object* v___x_290_; lean_object* v___x_291_; lean_object* v___x_292_; float v___x_293_; float v___x_294_; 
v___x_285_ = 8388607;
v___x_286_ = lean_uint32_land(v___y_133_, v___x_285_);
v___x_287_ = 8388608;
v___x_288_ = lean_uint32_lor(v___x_286_, v___x_287_);
v___x_289_ = lean_uint32_to_float32(v___x_288_);
v___x_290_ = lp_competition_R2W01b_scaleTable;
v___x_291_ = lean_uint32_to_nat(v___x_283_);
v___x_292_ = lean_array_fget_borrowed(v___x_290_, v___x_291_);
lean_dec(v___x_291_);
v___x_293_ = lean_unbox_float32(v___x_292_);
v___x_294_ = lean_float32_mul(v___x_289_, v___x_293_);
v___y_223_ = v___x_294_;
goto v___jp_222_;
}
v___jp_295_:
{
if (v___y_296_ == 0)
{
float v___x_297_; 
v___x_297_ = lean_float32_of_bits(v___y_133_);
v___y_223_ = v___x_297_;
goto v___jp_222_;
}
else
{
goto v___jp_284_;
}
}
v___jp_299_:
{
uint32_t v___x_304_; uint32_t v___x_305_; uint32_t v___x_306_; uint32_t v___x_307_; uint32_t v___x_308_; 
v___x_304_ = lean_uint32_land(v___y_300_, v___x_298_);
v___x_305_ = lean_uint32_shift_left(v___x_304_, v___x_282_);
v___x_306_ = lean_uint32_lor(v___y_303_, v___x_305_);
v___x_307_ = lean_uint32_land(v___y_302_, v___y_301_);
v___x_308_ = lean_uint32_lor(v___x_306_, v___x_307_);
return v___x_308_;
}
v___jp_309_:
{
if (v___y_312_ == 0)
{
uint32_t v___x_314_; 
v___x_314_ = 0;
v___y_300_ = v___y_310_;
v___y_301_ = v___y_311_;
v___y_302_ = v___y_313_;
v___y_303_ = v___x_314_;
goto v___jp_299_;
}
else
{
uint32_t v___x_315_; 
v___x_315_ = 2147483648;
v___y_300_ = v___y_310_;
v___y_301_ = v___y_311_;
v___y_302_ = v___y_313_;
v___y_303_ = v___x_315_;
goto v___jp_299_;
}
}
v___jp_316_:
{
uint64_t v___x_322_; uint64_t v_encodedExponent_323_; uint32_t v___x_324_; uint64_t v___x_325_; uint8_t v___x_326_; 
v___x_322_ = 171ULL;
v_encodedExponent_323_ = lean_uint64_sub(v___y_320_, v___x_322_);
v___x_324_ = lean_uint64_to_uint32(v_encodedExponent_323_);
v___x_325_ = 8388608ULL;
v___x_326_ = lean_uint64_dec_lt(v___y_321_, v___x_325_);
if (v___x_326_ == 0)
{
uint64_t v___x_327_; uint32_t v___x_328_; 
v___x_327_ = lean_uint64_sub(v___y_321_, v___x_325_);
v___x_328_ = lean_uint64_to_uint32(v___x_327_);
v___y_310_ = v___x_324_;
v___y_311_ = v___y_317_;
v___y_312_ = v___y_319_;
v___y_313_ = v___x_328_;
goto v___jp_309_;
}
else
{
uint32_t v___x_329_; 
v___x_329_ = lean_uint64_to_uint32(v___y_318_);
v___y_310_ = v___x_324_;
v___y_311_ = v___y_317_;
v___y_312_ = v___y_319_;
v___y_313_ = v___x_329_;
goto v___jp_309_;
}
}
v___jp_330_:
{
uint64_t v___x_337_; uint8_t v___x_338_; 
v___x_337_ = 425ULL;
v___x_338_ = lean_uint64_dec_lt(v___x_337_, v___y_336_);
if (v___x_338_ == 0)
{
if (v___y_335_ == 0)
{
v___y_317_ = v___y_331_;
v___y_318_ = v___y_333_;
v___y_319_ = v___y_332_;
v___y_320_ = v___y_336_;
v___y_321_ = v___y_334_;
goto v___jp_316_;
}
else
{
uint64_t v___x_339_; 
v___x_339_ = 8388608ULL;
v___y_317_ = v___y_331_;
v___y_318_ = v___y_333_;
v___y_319_ = v___y_332_;
v___y_320_ = v___y_336_;
v___y_321_ = v___x_339_;
goto v___jp_316_;
}
}
else
{
if (v___y_332_ == 0)
{
uint32_t v___x_340_; 
v___x_340_ = 2139095040;
return v___x_340_;
}
else
{
uint32_t v___x_341_; 
v___x_341_ = 4286578688;
return v___x_341_;
}
}
}
v___jp_342_:
{
uint64_t v___x_348_; uint8_t v_carry_349_; 
v___x_348_ = 16777216ULL;
v_carry_349_ = lean_uint64_dec_eq(v___y_347_, v___x_348_);
if (v_carry_349_ == 0)
{
v___y_331_ = v___y_343_;
v___y_332_ = v___y_345_;
v___y_333_ = v___y_344_;
v___y_334_ = v___y_347_;
v___y_335_ = v_carry_349_;
v___y_336_ = v___y_346_;
goto v___jp_330_;
}
else
{
uint64_t v___x_350_; uint64_t v___x_351_; 
v___x_350_ = 1ULL;
v___x_351_ = lean_uint64_add(v___y_346_, v___x_350_);
v___y_331_ = v___y_343_;
v___y_332_ = v___y_345_;
v___y_333_ = v___y_344_;
v___y_334_ = v___y_347_;
v___y_335_ = v_carry_349_;
v___y_336_ = v___x_351_;
goto v___jp_330_;
}
}
v___jp_352_:
{
uint64_t v_position_359_; uint64_t v___x_360_; uint8_t v___x_361_; 
v_position_359_ = lean_uint64_add(v___y_358_, v___y_357_);
v___x_360_ = 172ULL;
v___x_361_ = lean_uint64_dec_lt(v_position_359_, v___x_360_);
if (v___x_361_ == 0)
{
uint64_t v___x_362_; uint8_t v___x_363_; 
v___x_362_ = 23ULL;
v___x_363_ = lean_uint64_dec_lt(v___y_358_, v___x_362_);
if (v___x_363_ == 0)
{
uint64_t v___x_364_; uint8_t v___x_365_; 
v___x_364_ = lean_uint64_sub(v___y_358_, v___x_362_);
v___x_365_ = lean_uint64_dec_eq(v___x_364_, v___y_356_);
if (v___x_365_ == 0)
{
uint64_t v___x_366_; uint8_t v___x_367_; 
v___x_366_ = 64ULL;
v___x_367_ = lean_uint64_dec_lt(v___x_364_, v___x_366_);
if (v___x_367_ == 0)
{
uint8_t v___x_368_; 
v___x_368_ = lean_uint64_dec_eq(v___x_364_, v___x_366_);
if (v___x_368_ == 0)
{
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v___y_356_;
goto v___jp_342_;
}
else
{
uint64_t v___x_369_; uint8_t v___x_370_; 
v___x_369_ = 9223372036854775808ULL;
v___x_370_ = lean_uint64_dec_lt(v___x_369_, v___y_353_);
if (v___x_370_ == 0)
{
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v___y_356_;
goto v___jp_342_;
}
else
{
uint64_t v___x_371_; 
v___x_371_ = 1ULL;
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v___x_371_;
goto v___jp_342_;
}
}
}
else
{
uint64_t v_quotient_372_; uint64_t v___x_373_; uint64_t v___x_374_; uint64_t v___x_375_; uint64_t v_remainder_376_; uint64_t v___x_377_; uint64_t v_half_378_; uint8_t v___x_379_; 
v_quotient_372_ = lean_uint64_shift_right(v___y_353_, v___x_364_);
v___x_373_ = 1ULL;
v___x_374_ = lean_uint64_shift_left(v___x_373_, v___x_364_);
v___x_375_ = lean_uint64_sub(v___x_374_, v___x_373_);
v_remainder_376_ = lean_uint64_land(v___y_353_, v___x_375_);
v___x_377_ = lean_uint64_sub(v___x_364_, v___x_373_);
v_half_378_ = lean_uint64_shift_left(v___x_373_, v___x_377_);
v___x_379_ = lean_uint64_dec_lt(v_remainder_376_, v_half_378_);
if (v___x_379_ == 0)
{
uint8_t v___x_380_; 
v___x_380_ = lean_uint64_dec_lt(v_half_378_, v_remainder_376_);
if (v___x_380_ == 0)
{
uint64_t v___x_381_; uint8_t v___x_382_; 
v___x_381_ = lean_uint64_land(v_quotient_372_, v___x_373_);
v___x_382_ = lean_uint64_dec_eq(v___x_381_, v___y_356_);
if (v___x_382_ == 0)
{
uint64_t v___x_383_; 
v___x_383_ = lean_uint64_add(v_quotient_372_, v___x_373_);
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v___x_383_;
goto v___jp_342_;
}
else
{
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v_quotient_372_;
goto v___jp_342_;
}
}
else
{
uint64_t v___x_384_; 
v___x_384_ = lean_uint64_add(v_quotient_372_, v___x_373_);
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v___x_384_;
goto v___jp_342_;
}
}
else
{
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v_quotient_372_;
goto v___jp_342_;
}
}
}
else
{
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v___y_353_;
goto v___jp_342_;
}
}
else
{
uint64_t v___x_385_; uint64_t v___x_386_; 
v___x_385_ = lean_uint64_sub(v___x_362_, v___y_358_);
v___x_386_ = lean_uint64_shift_left(v___y_353_, v___x_385_);
v___y_343_ = v___y_354_;
v___y_344_ = v___y_356_;
v___y_345_ = v___y_355_;
v___y_346_ = v_position_359_;
v___y_347_ = v___x_386_;
goto v___jp_342_;
}
}
else
{
uint64_t v___x_387_; uint8_t v___x_388_; 
v___x_387_ = 149ULL;
v___x_388_ = lean_uint64_dec_lt(v___y_357_, v___x_387_);
if (v___x_388_ == 0)
{
uint64_t v___x_389_; uint64_t v___x_390_; 
v___x_389_ = lean_uint64_sub(v___y_357_, v___x_387_);
v___x_390_ = lean_uint64_shift_left(v___y_353_, v___x_389_);
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v___x_390_;
goto v___jp_246_;
}
else
{
uint64_t v___x_391_; uint8_t v___x_392_; 
v___x_391_ = lean_uint64_sub(v___x_387_, v___y_357_);
v___x_392_ = lean_uint64_dec_eq(v___x_391_, v___y_356_);
if (v___x_392_ == 0)
{
uint64_t v___x_393_; uint8_t v___x_394_; 
v___x_393_ = 64ULL;
v___x_394_ = lean_uint64_dec_lt(v___x_391_, v___x_393_);
if (v___x_394_ == 0)
{
uint8_t v___x_395_; 
v___x_395_ = lean_uint64_dec_eq(v___x_391_, v___x_393_);
if (v___x_395_ == 0)
{
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v___y_356_;
goto v___jp_246_;
}
else
{
uint64_t v___x_396_; uint8_t v___x_397_; 
v___x_396_ = 9223372036854775808ULL;
v___x_397_ = lean_uint64_dec_lt(v___x_396_, v___y_353_);
if (v___x_397_ == 0)
{
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v___y_356_;
goto v___jp_246_;
}
else
{
uint64_t v___x_398_; 
v___x_398_ = 1ULL;
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v___x_398_;
goto v___jp_246_;
}
}
}
else
{
uint64_t v_quotient_399_; uint64_t v___x_400_; uint64_t v___x_401_; uint64_t v___x_402_; uint64_t v_remainder_403_; uint64_t v___x_404_; uint64_t v_half_405_; uint8_t v___x_406_; 
v_quotient_399_ = lean_uint64_shift_right(v___y_353_, v___x_391_);
v___x_400_ = 1ULL;
v___x_401_ = lean_uint64_shift_left(v___x_400_, v___x_391_);
v___x_402_ = lean_uint64_sub(v___x_401_, v___x_400_);
v_remainder_403_ = lean_uint64_land(v___y_353_, v___x_402_);
v___x_404_ = lean_uint64_sub(v___x_391_, v___x_400_);
v_half_405_ = lean_uint64_shift_left(v___x_400_, v___x_404_);
v___x_406_ = lean_uint64_dec_lt(v_remainder_403_, v_half_405_);
if (v___x_406_ == 0)
{
uint8_t v___x_407_; 
v___x_407_ = lean_uint64_dec_lt(v_half_405_, v_remainder_403_);
if (v___x_407_ == 0)
{
uint64_t v___x_408_; uint8_t v___x_409_; 
v___x_408_ = lean_uint64_land(v_quotient_399_, v___x_400_);
v___x_409_ = lean_uint64_dec_eq(v___x_408_, v___y_356_);
if (v___x_409_ == 0)
{
uint64_t v___x_410_; 
v___x_410_ = lean_uint64_add(v_quotient_399_, v___x_400_);
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v___x_410_;
goto v___jp_246_;
}
else
{
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v_quotient_399_;
goto v___jp_246_;
}
}
else
{
uint64_t v___x_411_; 
v___x_411_ = lean_uint64_add(v_quotient_399_, v___x_400_);
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v___x_411_;
goto v___jp_246_;
}
}
else
{
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v_quotient_399_;
goto v___jp_246_;
}
}
}
else
{
v___y_247_ = v___y_354_;
v___y_248_ = v___y_355_;
v___y_249_ = v___y_356_;
v___y_250_ = v___y_353_;
goto v___jp_246_;
}
}
}
}
v___jp_412_:
{
uint64_t v___x_420_; uint64_t v___x_421_; uint8_t v___x_422_; 
v___x_420_ = 1ULL;
v___x_421_ = lean_uint64_shift_right(v___y_417_, v___x_420_);
v___x_422_ = lean_uint64_dec_eq(v___x_421_, v___y_416_);
if (v___x_422_ == 0)
{
uint64_t v___x_423_; 
v___x_423_ = lean_uint64_add(v___y_419_, v___x_420_);
v___y_353_ = v___y_413_;
v___y_354_ = v___y_414_;
v___y_355_ = v___y_415_;
v___y_356_ = v___y_416_;
v___y_357_ = v___y_418_;
v___y_358_ = v___x_423_;
goto v___jp_352_;
}
else
{
v___y_353_ = v___y_413_;
v___y_354_ = v___y_414_;
v___y_355_ = v___y_415_;
v___y_356_ = v___y_416_;
v___y_357_ = v___y_418_;
v___y_358_ = v___y_419_;
goto v___jp_352_;
}
}
v___jp_424_:
{
uint64_t v___x_434_; uint8_t v___x_435_; 
v___x_434_ = lean_uint64_shift_right(v___y_429_, v___y_431_);
v___x_435_ = lean_uint64_dec_eq(v___x_434_, v___y_427_);
if (v___x_435_ == 0)
{
uint64_t v___x_436_; 
v___x_436_ = lean_uint64_add(v___y_430_, v___y_431_);
v___y_413_ = v___y_425_;
v___y_414_ = v___y_426_;
v___y_415_ = v___y_428_;
v___y_416_ = v___y_427_;
v___y_417_ = v___y_433_;
v___y_418_ = v___y_432_;
v___y_419_ = v___x_436_;
goto v___jp_412_;
}
else
{
v___y_413_ = v___y_425_;
v___y_414_ = v___y_426_;
v___y_415_ = v___y_428_;
v___y_416_ = v___y_427_;
v___y_417_ = v___y_433_;
v___y_418_ = v___y_432_;
v___y_419_ = v___y_430_;
goto v___jp_412_;
}
}
v___jp_437_:
{
uint64_t v___x_445_; uint64_t v___x_446_; uint8_t v___x_447_; 
v___x_445_ = 2ULL;
v___x_446_ = lean_uint64_shift_right(v___y_442_, v___x_445_);
v___x_447_ = lean_uint64_dec_eq(v___x_446_, v___y_441_);
if (v___x_447_ == 0)
{
v___y_425_ = v___y_438_;
v___y_426_ = v___y_439_;
v___y_427_ = v___y_441_;
v___y_428_ = v___y_440_;
v___y_429_ = v___y_442_;
v___y_430_ = v___y_444_;
v___y_431_ = v___x_445_;
v___y_432_ = v___y_443_;
v___y_433_ = v___x_446_;
goto v___jp_424_;
}
else
{
v___y_425_ = v___y_438_;
v___y_426_ = v___y_439_;
v___y_427_ = v___y_441_;
v___y_428_ = v___y_440_;
v___y_429_ = v___y_442_;
v___y_430_ = v___y_444_;
v___y_431_ = v___x_445_;
v___y_432_ = v___y_443_;
v___y_433_ = v___y_442_;
goto v___jp_424_;
}
}
v___jp_448_:
{
uint64_t v___x_458_; uint8_t v___x_459_; 
v___x_458_ = lean_uint64_shift_right(v___y_453_, v___y_456_);
v___x_459_ = lean_uint64_dec_eq(v___x_458_, v___y_451_);
if (v___x_459_ == 0)
{
uint64_t v___x_460_; 
v___x_460_ = lean_uint64_add(v___y_455_, v___y_456_);
v___y_438_ = v___y_449_;
v___y_439_ = v___y_450_;
v___y_440_ = v___y_452_;
v___y_441_ = v___y_451_;
v___y_442_ = v___y_457_;
v___y_443_ = v___y_454_;
v___y_444_ = v___x_460_;
goto v___jp_437_;
}
else
{
v___y_438_ = v___y_449_;
v___y_439_ = v___y_450_;
v___y_440_ = v___y_452_;
v___y_441_ = v___y_451_;
v___y_442_ = v___y_457_;
v___y_443_ = v___y_454_;
v___y_444_ = v___y_455_;
goto v___jp_437_;
}
}
v___jp_461_:
{
uint64_t v___x_469_; uint64_t v___x_470_; uint8_t v___x_471_; 
v___x_469_ = 4ULL;
v___x_470_ = lean_uint64_shift_right(v___y_466_, v___x_469_);
v___x_471_ = lean_uint64_dec_eq(v___x_470_, v___y_465_);
if (v___x_471_ == 0)
{
v___y_449_ = v___y_462_;
v___y_450_ = v___y_463_;
v___y_451_ = v___y_465_;
v___y_452_ = v___y_464_;
v___y_453_ = v___y_466_;
v___y_454_ = v___y_467_;
v___y_455_ = v___y_468_;
v___y_456_ = v___x_469_;
v___y_457_ = v___x_470_;
goto v___jp_448_;
}
else
{
v___y_449_ = v___y_462_;
v___y_450_ = v___y_463_;
v___y_451_ = v___y_465_;
v___y_452_ = v___y_464_;
v___y_453_ = v___y_466_;
v___y_454_ = v___y_467_;
v___y_455_ = v___y_468_;
v___y_456_ = v___x_469_;
v___y_457_ = v___y_466_;
goto v___jp_448_;
}
}
v___jp_472_:
{
uint64_t v___x_482_; uint8_t v___x_483_; 
v___x_482_ = lean_uint64_shift_right(v___y_478_, v___y_473_);
v___x_483_ = lean_uint64_dec_eq(v___x_482_, v___y_476_);
if (v___x_483_ == 0)
{
uint64_t v___x_484_; 
v___x_484_ = lean_uint64_add(v___y_479_, v___y_473_);
v___y_462_ = v___y_474_;
v___y_463_ = v___y_475_;
v___y_464_ = v___y_477_;
v___y_465_ = v___y_476_;
v___y_466_ = v___y_481_;
v___y_467_ = v___y_480_;
v___y_468_ = v___x_484_;
goto v___jp_461_;
}
else
{
v___y_462_ = v___y_474_;
v___y_463_ = v___y_475_;
v___y_464_ = v___y_477_;
v___y_465_ = v___y_476_;
v___y_466_ = v___y_481_;
v___y_467_ = v___y_480_;
v___y_468_ = v___y_479_;
goto v___jp_461_;
}
}
v___jp_485_:
{
uint64_t v___x_493_; uint64_t v___x_494_; uint8_t v___x_495_; 
v___x_493_ = 8ULL;
v___x_494_ = lean_uint64_shift_right(v___y_490_, v___x_493_);
v___x_495_ = lean_uint64_dec_eq(v___x_494_, v___y_489_);
if (v___x_495_ == 0)
{
v___y_473_ = v___x_493_;
v___y_474_ = v___y_486_;
v___y_475_ = v___y_487_;
v___y_476_ = v___y_489_;
v___y_477_ = v___y_488_;
v___y_478_ = v___y_490_;
v___y_479_ = v___y_492_;
v___y_480_ = v___y_491_;
v___y_481_ = v___x_494_;
goto v___jp_472_;
}
else
{
v___y_473_ = v___x_493_;
v___y_474_ = v___y_486_;
v___y_475_ = v___y_487_;
v___y_476_ = v___y_489_;
v___y_477_ = v___y_488_;
v___y_478_ = v___y_490_;
v___y_479_ = v___y_492_;
v___y_480_ = v___y_491_;
v___y_481_ = v___y_490_;
goto v___jp_472_;
}
}
v___jp_496_:
{
uint64_t v___x_506_; uint8_t v___x_507_; 
v___x_506_ = lean_uint64_shift_right(v___y_504_, v___y_501_);
v___x_507_ = lean_uint64_dec_eq(v___x_506_, v___y_499_);
if (v___x_507_ == 0)
{
uint64_t v___x_508_; 
v___x_508_ = lean_uint64_add(v___y_502_, v___y_501_);
v___y_486_ = v___y_497_;
v___y_487_ = v___y_498_;
v___y_488_ = v___y_500_;
v___y_489_ = v___y_499_;
v___y_490_ = v___y_505_;
v___y_491_ = v___y_503_;
v___y_492_ = v___x_508_;
goto v___jp_485_;
}
else
{
v___y_486_ = v___y_497_;
v___y_487_ = v___y_498_;
v___y_488_ = v___y_500_;
v___y_489_ = v___y_499_;
v___y_490_ = v___y_505_;
v___y_491_ = v___y_503_;
v___y_492_ = v___y_502_;
goto v___jp_485_;
}
}
v___jp_509_:
{
uint64_t v___x_517_; uint64_t v___x_518_; uint8_t v___x_519_; 
v___x_517_ = 16ULL;
v___x_518_ = lean_uint64_shift_right(v___y_515_, v___x_517_);
v___x_519_ = lean_uint64_dec_eq(v___x_518_, v___y_513_);
if (v___x_519_ == 0)
{
v___y_497_ = v___y_510_;
v___y_498_ = v___y_511_;
v___y_499_ = v___y_513_;
v___y_500_ = v___y_512_;
v___y_501_ = v___x_517_;
v___y_502_ = v___y_516_;
v___y_503_ = v___y_514_;
v___y_504_ = v___y_515_;
v___y_505_ = v___x_518_;
goto v___jp_496_;
}
else
{
v___y_497_ = v___y_510_;
v___y_498_ = v___y_511_;
v___y_499_ = v___y_513_;
v___y_500_ = v___y_512_;
v___y_501_ = v___x_517_;
v___y_502_ = v___y_516_;
v___y_503_ = v___y_514_;
v___y_504_ = v___y_515_;
v___y_505_ = v___y_515_;
goto v___jp_496_;
}
}
v___jp_520_:
{
uint64_t v___x_528_; uint8_t v___x_529_; 
v___x_528_ = lean_uint64_shift_right(v___y_522_, v___y_521_);
v___x_529_ = lean_uint64_dec_eq(v___x_528_, v___y_524_);
if (v___x_529_ == 0)
{
v___y_510_ = v___y_522_;
v___y_511_ = v___y_523_;
v___y_512_ = v___y_525_;
v___y_513_ = v___y_524_;
v___y_514_ = v___y_526_;
v___y_515_ = v___y_527_;
v___y_516_ = v___y_521_;
goto v___jp_509_;
}
else
{
v___y_510_ = v___y_522_;
v___y_511_ = v___y_523_;
v___y_512_ = v___y_525_;
v___y_513_ = v___y_524_;
v___y_514_ = v___y_526_;
v___y_515_ = v___y_527_;
v___y_516_ = v___y_524_;
goto v___jp_509_;
}
}
v___jp_530_:
{
uint64_t v___x_535_; uint8_t v___x_536_; 
v___x_535_ = 0ULL;
v___x_536_ = lean_uint64_dec_eq(v___y_531_, v___x_535_);
if (v___x_536_ == 0)
{
uint64_t v___x_537_; uint64_t v___x_538_; uint8_t v___x_539_; 
v___x_537_ = 32ULL;
v___x_538_ = lean_uint64_shift_right(v___y_531_, v___x_537_);
v___x_539_ = lean_uint64_dec_eq(v___x_538_, v___x_535_);
if (v___x_539_ == 0)
{
v___y_521_ = v___x_537_;
v___y_522_ = v___y_531_;
v___y_523_ = v___y_532_;
v___y_524_ = v___x_535_;
v___y_525_ = v___y_533_;
v___y_526_ = v___y_534_;
v___y_527_ = v___x_538_;
goto v___jp_520_;
}
else
{
v___y_521_ = v___x_537_;
v___y_522_ = v___y_531_;
v___y_523_ = v___y_532_;
v___y_524_ = v___x_535_;
v___y_525_ = v___y_533_;
v___y_526_ = v___y_534_;
v___y_527_ = v___y_531_;
goto v___jp_520_;
}
}
else
{
if (v___y_533_ == 0)
{
uint32_t v___x_540_; 
v___x_540_ = 0;
return v___x_540_;
}
else
{
uint32_t v___x_541_; 
v___x_541_ = 2147483648;
return v___x_541_;
}
}
}
v___jp_542_:
{
uint64_t v___x_549_; uint64_t v___x_550_; uint64_t v___x_551_; uint8_t v___x_552_; 
v___x_549_ = lean_uint64_mul(v___y_547_, v___y_545_);
v___x_550_ = lean_uint64_add(v___y_546_, v___y_548_);
v___x_551_ = 281474976710656ULL;
v___x_552_ = lean_uint64_dec_lt(v___x_549_, v___x_551_);
if (v___x_552_ == 0)
{
v___y_531_ = v___x_549_;
v___y_532_ = v___y_543_;
v___y_533_ = v___y_544_;
v___y_534_ = v___x_550_;
goto v___jp_530_;
}
else
{
uint64_t v___x_553_; uint8_t v___x_554_; 
v___x_553_ = 123ULL;
v___x_554_ = lean_uint64_dec_le(v___x_550_, v___x_553_);
if (v___x_554_ == 0)
{
v___y_531_ = v___x_549_;
v___y_532_ = v___y_543_;
v___y_533_ = v___y_544_;
v___y_534_ = v___x_550_;
goto v___jp_530_;
}
else
{
uint64_t v___x_555_; uint8_t v___x_556_; 
v___x_555_ = 0ULL;
v___x_556_ = lean_uint64_dec_eq(v___x_549_, v___x_555_);
if (v___x_556_ == 0)
{
uint64_t v___x_557_; uint64_t v___x_558_; uint8_t v___x_559_; 
v___x_557_ = 149ULL;
v___x_558_ = lean_uint64_sub(v___x_557_, v___x_550_);
v___x_559_ = lean_uint64_dec_eq(v___x_558_, v___x_555_);
if (v___x_559_ == 0)
{
uint64_t v___x_560_; uint8_t v___x_561_; 
v___x_560_ = 64ULL;
v___x_561_ = lean_uint64_dec_lt(v___x_558_, v___x_560_);
if (v___x_561_ == 0)
{
uint8_t v___x_562_; 
v___x_562_ = lean_uint64_dec_eq(v___x_558_, v___x_560_);
if (v___x_562_ == 0)
{
v___y_268_ = v___y_543_;
v___y_269_ = v___y_544_;
v___y_270_ = v___x_555_;
v___y_271_ = v___x_555_;
goto v___jp_267_;
}
else
{
uint64_t v___x_563_; uint8_t v___x_564_; 
v___x_563_ = 9223372036854775808ULL;
v___x_564_ = lean_uint64_dec_lt(v___x_563_, v___x_549_);
if (v___x_564_ == 0)
{
v___y_268_ = v___y_543_;
v___y_269_ = v___y_544_;
v___y_270_ = v___x_555_;
v___y_271_ = v___x_555_;
goto v___jp_267_;
}
else
{
uint64_t v___x_565_; 
v___x_565_ = 1ULL;
v___y_268_ = v___y_543_;
v___y_269_ = v___y_544_;
v___y_270_ = v___x_555_;
v___y_271_ = v___x_565_;
goto v___jp_267_;
}
}
}
else
{
uint64_t v_quotient_566_; uint64_t v___x_567_; uint64_t v___x_568_; uint64_t v___x_569_; uint64_t v_remainder_570_; uint64_t v___x_571_; uint64_t v_half_572_; uint8_t v___x_573_; 
v_quotient_566_ = lean_uint64_shift_right(v___x_549_, v___x_558_);
v___x_567_ = 1ULL;
v___x_568_ = lean_uint64_shift_left(v___x_567_, v___x_558_);
v___x_569_ = lean_uint64_sub(v___x_568_, v___x_567_);
v_remainder_570_ = lean_uint64_land(v___x_549_, v___x_569_);
v___x_571_ = lean_uint64_sub(v___x_558_, v___x_567_);
v_half_572_ = lean_uint64_shift_left(v___x_567_, v___x_571_);
v___x_573_ = lean_uint64_dec_lt(v_remainder_570_, v_half_572_);
if (v___x_573_ == 0)
{
uint8_t v___x_574_; 
v___x_574_ = lean_uint64_dec_lt(v_half_572_, v_remainder_570_);
if (v___x_574_ == 0)
{
uint64_t v___x_575_; uint8_t v___x_576_; 
v___x_575_ = lean_uint64_land(v_quotient_566_, v___x_567_);
v___x_576_ = lean_uint64_dec_eq(v___x_575_, v___x_555_);
if (v___x_576_ == 0)
{
uint64_t v___x_577_; 
v___x_577_ = lean_uint64_add(v_quotient_566_, v___x_567_);
v___y_268_ = v___y_543_;
v___y_269_ = v___y_544_;
v___y_270_ = v___x_555_;
v___y_271_ = v___x_577_;
goto v___jp_267_;
}
else
{
v___y_268_ = v___y_543_;
v___y_269_ = v___y_544_;
v___y_270_ = v___x_555_;
v___y_271_ = v_quotient_566_;
goto v___jp_267_;
}
}
else
{
uint64_t v___x_578_; 
v___x_578_ = lean_uint64_add(v_quotient_566_, v___x_567_);
v___y_268_ = v___y_543_;
v___y_269_ = v___y_544_;
v___y_270_ = v___x_555_;
v___y_271_ = v___x_578_;
goto v___jp_267_;
}
}
else
{
v___y_268_ = v___y_543_;
v___y_269_ = v___y_544_;
v___y_270_ = v___x_555_;
v___y_271_ = v_quotient_566_;
goto v___jp_267_;
}
}
}
else
{
v___y_268_ = v___y_543_;
v___y_269_ = v___y_544_;
v___y_270_ = v___x_555_;
v___y_271_ = v___x_549_;
goto v___jp_267_;
}
}
else
{
if (v___y_544_ == 0)
{
uint32_t v___x_579_; 
v___x_579_ = 0;
return v___x_579_;
}
else
{
uint32_t v___x_580_; 
v___x_580_ = 2147483648;
return v___x_580_;
}
}
}
}
}
v___jp_584_:
{
uint64_t v___x_590_; uint64_t v___x_591_; uint8_t v___x_592_; 
v___x_590_ = lean_uint32_to_uint64(v_ey_583_);
v___x_591_ = 0ULL;
v___x_592_ = lean_uint64_dec_eq(v___x_590_, v___x_591_);
if (v___x_592_ == 0)
{
uint64_t v___x_593_; uint64_t v___x_594_; 
v___x_593_ = 1ULL;
v___x_594_ = lean_uint64_sub(v___x_590_, v___x_593_);
v___y_543_ = v___y_585_;
v___y_544_ = v___y_586_;
v___y_545_ = v___y_587_;
v___y_546_ = v___y_589_;
v___y_547_ = v___y_588_;
v___y_548_ = v___x_594_;
goto v___jp_542_;
}
else
{
v___y_543_ = v___y_585_;
v___y_544_ = v___y_586_;
v___y_545_ = v___y_587_;
v___y_546_ = v___y_589_;
v___y_547_ = v___y_588_;
v___y_548_ = v___x_591_;
goto v___jp_542_;
}
}
v___jp_595_:
{
uint64_t v___x_600_; uint64_t v___x_601_; uint8_t v___x_602_; 
v___x_600_ = lean_uint32_to_uint64(v_ex_581_);
v___x_601_ = 0ULL;
v___x_602_ = lean_uint64_dec_eq(v___x_600_, v___x_601_);
if (v___x_602_ == 0)
{
uint64_t v___x_603_; uint64_t v___x_604_; 
v___x_603_ = 1ULL;
v___x_604_ = lean_uint64_sub(v___x_600_, v___x_603_);
v___y_585_ = v___y_596_;
v___y_586_ = v___y_597_;
v___y_587_ = v___y_599_;
v___y_588_ = v___y_598_;
v___y_589_ = v___x_604_;
goto v___jp_584_;
}
else
{
v___y_585_ = v___y_596_;
v___y_586_ = v___y_597_;
v___y_587_ = v___y_599_;
v___y_588_ = v___y_598_;
v___y_589_ = v___x_601_;
goto v___jp_584_;
}
}
v___jp_605_:
{
uint32_t v___x_610_; uint8_t v___x_611_; 
v___x_610_ = 0;
v___x_611_ = lean_uint32_dec_eq(v_ey_583_, v___x_610_);
if (v___x_611_ == 0)
{
uint64_t v___x_612_; uint64_t v___x_613_; uint64_t v___x_614_; 
v___x_612_ = lean_uint32_to_uint64(v___y_608_);
v___x_613_ = 8388608ULL;
v___x_614_ = lean_uint64_lor(v___x_612_, v___x_613_);
v___y_596_ = v___y_606_;
v___y_597_ = v___y_607_;
v___y_598_ = v___y_609_;
v___y_599_ = v___x_614_;
goto v___jp_595_;
}
else
{
uint64_t v___x_615_; 
v___x_615_ = lean_uint32_to_uint64(v___y_608_);
v___y_596_ = v___y_606_;
v___y_597_ = v___y_607_;
v___y_598_ = v___y_609_;
v___y_599_ = v___x_615_;
goto v___jp_595_;
}
}
v___jp_616_:
{
uint32_t v___x_618_; uint32_t v_xFraction_619_; uint32_t v_yFraction_620_; uint32_t v___x_621_; uint8_t v___x_622_; 
v___x_618_ = 8388607;
v_xFraction_619_ = lean_uint32_land(v___y_133_, v___x_618_);
v_yFraction_620_ = lean_uint32_land(v___y_134_, v___x_618_);
v___x_621_ = 0;
v___x_622_ = lean_uint32_dec_eq(v_ex_581_, v___x_621_);
if (v___x_622_ == 0)
{
uint64_t v___x_623_; uint64_t v___x_624_; uint64_t v___x_625_; 
v___x_623_ = lean_uint32_to_uint64(v_xFraction_619_);
v___x_624_ = 8388608ULL;
v___x_625_ = lean_uint64_lor(v___x_623_, v___x_624_);
v___y_606_ = v___x_618_;
v___y_607_ = v___y_617_;
v___y_608_ = v_yFraction_620_;
v___y_609_ = v___x_625_;
goto v___jp_605_;
}
else
{
uint64_t v___x_626_; 
v___x_626_ = lean_uint32_to_uint64(v_xFraction_619_);
v___y_606_ = v___x_618_;
v___y_607_ = v___y_617_;
v___y_608_ = v_yFraction_620_;
v___y_609_ = v___x_626_;
goto v___jp_605_;
}
}
v___jp_630_:
{
if (v___y_632_ == 0)
{
v___y_617_ = v___x_629_;
goto v___jp_616_;
}
else
{
v___y_617_ = v___y_631_;
goto v___jp_616_;
}
}
v___jp_633_:
{
if (v___y_635_ == 0)
{
if (v___y_636_ == 0)
{
v___y_631_ = v___y_634_;
v___y_632_ = v___x_629_;
goto v___jp_630_;
}
else
{
v___y_617_ = v___x_629_;
goto v___jp_616_;
}
}
else
{
v___y_631_ = v___y_634_;
v___y_632_ = v___y_636_;
goto v___jp_630_;
}
}
v___jp_637_:
{
uint32_t v___x_640_; uint32_t v___x_641_; uint32_t v___x_642_; uint8_t v___x_643_; 
v___x_640_ = 2147483648;
v___x_641_ = lean_uint32_land(v___y_134_, v___x_640_);
v___x_642_ = 0;
v___x_643_ = lean_uint32_dec_eq(v___x_641_, v___x_642_);
if (v___x_643_ == 0)
{
v___y_634_ = v___y_638_;
v___y_635_ = v___y_639_;
v___y_636_ = v___x_629_;
goto v___jp_633_;
}
else
{
v___y_634_ = v___y_638_;
v___y_635_ = v___y_639_;
v___y_636_ = v___y_638_;
goto v___jp_633_;
}
}
v___jp_644_:
{
if (v___y_645_ == 0)
{
uint32_t v___x_646_; uint32_t v___x_647_; uint32_t v___x_648_; uint8_t v___x_649_; 
v___x_646_ = 2147483648;
v___x_647_ = lean_uint32_land(v___y_133_, v___x_646_);
v___x_648_ = 0;
v___x_649_ = lean_uint32_dec_eq(v___x_647_, v___x_648_);
if (v___x_649_ == 0)
{
v___y_638_ = v___y_645_;
v___y_639_ = v___x_629_;
goto v___jp_637_;
}
else
{
v___y_638_ = v___y_645_;
v___y_639_ = v___y_645_;
goto v___jp_637_;
}
}
else
{
lean_object* v___x_650_; lean_object* v___x_651_; lean_object* v___x_652_; uint32_t v___x_653_; 
v___x_650_ = lean_uint32_to_nat(v___y_133_);
v___x_651_ = lean_uint32_to_nat(v___y_134_);
v___x_652_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_650_, v___x_651_);
v___x_653_ = lean_uint32_of_nat(v___x_652_);
lean_dec(v___x_652_);
return v___x_653_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_668_, lean_object* v___y_669_){
_start:
{
uint32_t v___y_4805__boxed_670_; uint32_t v___y_4806__boxed_671_; uint32_t v_res_672_; lean_object* v_r_673_; 
v___y_4805__boxed_670_ = lean_unbox_uint32(v___y_668_);
lean_dec(v___y_668_);
v___y_4806__boxed_671_ = lean_unbox_uint32(v___y_669_);
lean_dec(v___y_669_);
v_res_672_ = lp_competition_main___lam__1(v___y_4805__boxed_670_, v___y_4806__boxed_671_);
v_r_673_ = lean_box_uint32(v_res_672_);
return v_r_673_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_674_, uint32_t v___y_675_){
_start:
{
uint8_t v___y_677_; uint8_t v___y_693_; uint8_t v___y_707_; uint8_t v___y_724_; float v___y_731_; float v___y_732_; float v___y_746_; float v___y_760_; uint8_t v___y_761_; float v___y_764_; uint32_t v___y_774_; uint32_t v___y_778_; uint32_t v___y_782_; uint32_t v___y_783_; uint32_t v___y_784_; uint64_t v___y_788_; uint32_t v___y_789_; uint8_t v___y_790_; uint64_t v___y_791_; uint32_t v___y_803_; uint32_t v___y_804_; uint32_t v___y_805_; uint32_t v___y_809_; uint8_t v___y_810_; uint64_t v___y_811_; uint64_t v___y_812_; uint32_t v___x_823_; uint32_t v___x_824_; uint8_t v___y_837_; uint32_t v___x_839_; uint32_t v___y_841_; uint32_t v___y_842_; uint32_t v___y_843_; uint32_t v___y_844_; uint32_t v___y_851_; uint32_t v___y_852_; uint8_t v___y_853_; uint32_t v___y_854_; uint64_t v___y_858_; uint32_t v___y_859_; uint8_t v___y_860_; uint64_t v___y_861_; uint64_t v___y_862_; uint64_t v___y_872_; uint32_t v___y_873_; uint8_t v___y_874_; uint8_t v___y_875_; uint64_t v___y_876_; uint64_t v___y_877_; uint64_t v___y_884_; uint32_t v___y_885_; uint64_t v___y_886_; uint8_t v___y_887_; uint64_t v___y_888_; uint64_t v___y_894_; uint64_t v___y_895_; uint32_t v___y_896_; uint64_t v___y_897_; uint8_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_954_; uint64_t v___y_955_; uint32_t v___y_956_; uint64_t v___y_957_; uint8_t v___y_958_; uint64_t v___y_959_; uint64_t v___y_960_; uint64_t v___y_966_; uint64_t v___y_967_; uint64_t v___y_968_; uint64_t v___y_969_; uint32_t v___y_970_; uint64_t v___y_971_; uint64_t v___y_972_; uint8_t v___y_973_; uint64_t v___y_974_; uint64_t v___y_979_; uint64_t v___y_980_; uint64_t v___y_981_; uint32_t v___y_982_; uint64_t v___y_983_; uint8_t v___y_984_; uint64_t v___y_985_; uint64_t v___y_990_; uint64_t v___y_991_; uint64_t v___y_992_; uint32_t v___y_993_; uint64_t v___y_994_; uint64_t v___y_995_; uint8_t v___y_996_; uint64_t v___y_997_; uint64_t v___y_998_; uint64_t v___y_1003_; uint64_t v___y_1004_; uint32_t v___y_1005_; uint64_t v___y_1006_; uint8_t v___y_1007_; uint64_t v___y_1008_; uint64_t v___y_1009_; uint64_t v___y_1014_; uint64_t v___y_1015_; uint32_t v___y_1016_; uint64_t v___y_1017_; uint64_t v___y_1018_; uint8_t v___y_1019_; uint64_t v___y_1020_; uint64_t v___y_1021_; uint64_t v___y_1022_; uint64_t v___y_1027_; uint64_t v___y_1028_; uint32_t v___y_1029_; uint64_t v___y_1030_; uint64_t v___y_1031_; uint8_t v___y_1032_; uint64_t v___y_1033_; uint64_t v___y_1038_; uint64_t v___y_1039_; uint64_t v___y_1040_; uint32_t v___y_1041_; uint64_t v___y_1042_; uint64_t v___y_1043_; uint8_t v___y_1044_; uint64_t v___y_1045_; uint64_t v___y_1046_; uint64_t v___y_1051_; uint64_t v___y_1052_; uint64_t v___y_1053_; uint32_t v___y_1054_; uint64_t v___y_1055_; uint8_t v___y_1056_; uint64_t v___y_1057_; uint64_t v___y_1062_; uint64_t v___y_1063_; uint64_t v___y_1064_; uint32_t v___y_1065_; uint64_t v___y_1066_; uint8_t v___y_1067_; uint64_t v___y_1068_; uint64_t v___y_1072_; uint32_t v___y_1073_; uint64_t v___y_1074_; uint8_t v___y_1075_; uint64_t v___y_1084_; uint32_t v___y_1085_; uint64_t v___y_1086_; uint8_t v___y_1087_; uint64_t v___y_1088_; uint64_t v___y_1089_; uint32_t v_ex_1122_; uint32_t v___x_1123_; uint32_t v_ey_1124_; uint64_t v___y_1126_; uint64_t v___y_1127_; uint32_t v___y_1128_; uint8_t v___y_1129_; uint64_t v___y_1130_; uint64_t v___y_1137_; uint32_t v___y_1138_; uint8_t v___y_1139_; uint64_t v___y_1140_; uint32_t v___y_1147_; uint32_t v___y_1148_; uint8_t v___y_1149_; uint64_t v___y_1150_; uint8_t v___y_1158_; uint32_t v___x_1168_; uint32_t v___x_1169_; uint8_t v___x_1170_; uint8_t v___y_1172_; uint8_t v___y_1173_; uint8_t v___y_1175_; uint8_t v___y_1176_; uint8_t v___y_1177_; uint8_t v___y_1179_; uint8_t v___y_1180_; uint8_t v___y_1186_; 
v___x_823_ = 23;
v___x_824_ = lean_uint32_shift_right(v___y_674_, v___x_823_);
v___x_839_ = 255;
v_ex_1122_ = lean_uint32_land(v___x_824_, v___x_839_);
v___x_1123_ = lean_uint32_shift_right(v___y_675_, v___x_823_);
v_ey_1124_ = lean_uint32_land(v___x_1123_, v___x_839_);
v___x_1168_ = lean_uint32_add(v_ex_1122_, v_ey_1124_);
v___x_1169_ = 128;
v___x_1170_ = lean_uint32_dec_lt(v___x_1168_, v___x_1169_);
if (v___x_1170_ == 0)
{
uint32_t v___x_1195_; uint32_t v_a_1196_; uint32_t v___x_1197_; uint32_t v___x_1198_; uint32_t v___x_1199_; uint8_t v___x_1200_; uint32_t v___x_1201_; uint8_t v___x_1202_; 
v___x_1195_ = 2147483647;
v_a_1196_ = lean_uint32_land(v___y_674_, v___x_1195_);
v___x_1197_ = 201326591;
v___x_1198_ = 1;
v___x_1199_ = lean_uint32_sub(v_a_1196_, v___x_1198_);
v___x_1200_ = lean_uint32_dec_le(v___x_1197_, v___x_1199_);
v___x_1201_ = 2139095040;
v___x_1202_ = lean_uint32_dec_lt(v_a_1196_, v___x_1201_);
if (v___x_1200_ == 0)
{
if (v___x_1202_ == 0)
{
goto v___jp_825_;
}
else
{
v___y_837_ = v___x_1200_;
goto v___jp_836_;
}
}
else
{
v___y_837_ = v___x_1202_;
goto v___jp_836_;
}
}
else
{
uint32_t v___x_1203_; uint32_t v___x_1204_; uint32_t v___x_1205_; uint8_t v___x_1206_; 
v___x_1203_ = 4278190080;
v___x_1204_ = 1;
v___x_1205_ = lean_uint32_shift_left(v___y_674_, v___x_1204_);
v___x_1206_ = lean_uint32_dec_le(v___x_1203_, v___x_1205_);
if (v___x_1206_ == 0)
{
uint32_t v___x_1207_; uint8_t v___x_1208_; 
v___x_1207_ = lean_uint32_shift_left(v___y_675_, v___x_1204_);
v___x_1208_ = lean_uint32_dec_le(v___x_1203_, v___x_1207_);
v___y_1186_ = v___x_1208_;
goto v___jp_1185_;
}
else
{
v___y_1186_ = v___x_1206_;
goto v___jp_1185_;
}
}
v___jp_676_:
{
if (v___y_677_ == 0)
{
uint32_t v___x_678_; 
v___x_678_ = lp_competition_Submission_FastMul_mul(v___y_674_, v___y_675_);
return v___x_678_;
}
else
{
uint32_t v___x_679_; uint32_t v___x_680_; 
v___x_679_ = 4194304;
v___x_680_ = lean_uint32_lor(v___y_675_, v___x_679_);
return v___x_680_;
}
}
v___jp_681_:
{
uint32_t v___x_682_; uint32_t v___x_683_; uint32_t v___x_684_; uint32_t v___x_685_; uint8_t v___x_686_; 
v___x_682_ = 23;
v___x_683_ = lean_uint32_shift_right(v___y_675_, v___x_682_);
v___x_684_ = 255;
v___x_685_ = lean_uint32_land(v___x_683_, v___x_684_);
v___x_686_ = lean_uint32_dec_eq(v___x_685_, v___x_684_);
if (v___x_686_ == 0)
{
v___y_677_ = v___x_686_;
goto v___jp_676_;
}
else
{
uint32_t v___x_687_; uint32_t v___x_688_; uint32_t v___x_689_; uint8_t v___x_690_; 
v___x_687_ = 8388607;
v___x_688_ = lean_uint32_land(v___y_675_, v___x_687_);
v___x_689_ = 0;
v___x_690_ = lean_uint32_dec_eq(v___x_688_, v___x_689_);
if (v___x_690_ == 0)
{
v___y_677_ = v___x_686_;
goto v___jp_676_;
}
else
{
uint32_t v___x_691_; 
v___x_691_ = lp_competition_Submission_FastMul_mul(v___y_674_, v___y_675_);
return v___x_691_;
}
}
}
v___jp_692_:
{
if (v___y_693_ == 0)
{
goto v___jp_681_;
}
else
{
uint32_t v___x_694_; uint32_t v___x_695_; 
v___x_694_ = 4194304;
v___x_695_ = lean_uint32_lor(v___y_674_, v___x_694_);
return v___x_695_;
}
}
v___jp_696_:
{
uint32_t v___x_697_; uint32_t v___x_698_; uint32_t v___x_699_; uint32_t v___x_700_; uint8_t v___x_701_; 
v___x_697_ = 23;
v___x_698_ = lean_uint32_shift_right(v___y_674_, v___x_697_);
v___x_699_ = 255;
v___x_700_ = lean_uint32_land(v___x_698_, v___x_699_);
v___x_701_ = lean_uint32_dec_eq(v___x_700_, v___x_699_);
if (v___x_701_ == 0)
{
v___y_693_ = v___x_701_;
goto v___jp_692_;
}
else
{
uint32_t v___x_702_; uint32_t v___x_703_; uint32_t v___x_704_; uint8_t v___x_705_; 
v___x_702_ = 8388607;
v___x_703_ = lean_uint32_land(v___y_674_, v___x_702_);
v___x_704_ = 0;
v___x_705_ = lean_uint32_dec_eq(v___x_703_, v___x_704_);
if (v___x_705_ == 0)
{
v___y_693_ = v___x_701_;
goto v___jp_692_;
}
else
{
goto v___jp_681_;
}
}
}
v___jp_706_:
{
if (v___y_707_ == 0)
{
goto v___jp_696_;
}
else
{
uint32_t v___x_708_; uint32_t v___x_709_; uint32_t v___x_710_; uint8_t v___x_711_; 
v___x_708_ = 4194304;
v___x_709_ = lean_uint32_land(v___y_675_, v___x_708_);
v___x_710_ = 0;
v___x_711_ = lean_uint32_dec_eq(v___x_709_, v___x_710_);
if (v___x_711_ == 0)
{
goto v___jp_696_;
}
else
{
uint32_t v___x_712_; 
v___x_712_ = lean_uint32_lor(v___y_675_, v___x_708_);
return v___x_712_;
}
}
}
v___jp_713_:
{
uint32_t v___x_714_; uint32_t v___x_715_; uint32_t v___x_716_; uint32_t v___x_717_; uint8_t v___x_718_; 
v___x_714_ = 23;
v___x_715_ = lean_uint32_shift_right(v___y_675_, v___x_714_);
v___x_716_ = 255;
v___x_717_ = lean_uint32_land(v___x_715_, v___x_716_);
v___x_718_ = lean_uint32_dec_eq(v___x_717_, v___x_716_);
if (v___x_718_ == 0)
{
v___y_707_ = v___x_718_;
goto v___jp_706_;
}
else
{
uint32_t v___x_719_; uint32_t v___x_720_; uint32_t v___x_721_; uint8_t v___x_722_; 
v___x_719_ = 8388607;
v___x_720_ = lean_uint32_land(v___y_675_, v___x_719_);
v___x_721_ = 0;
v___x_722_ = lean_uint32_dec_eq(v___x_720_, v___x_721_);
if (v___x_722_ == 0)
{
v___y_707_ = v___x_718_;
goto v___jp_706_;
}
else
{
goto v___jp_696_;
}
}
}
v___jp_723_:
{
if (v___y_724_ == 0)
{
goto v___jp_713_;
}
else
{
uint32_t v___x_725_; uint32_t v___x_726_; uint32_t v___x_727_; uint8_t v___x_728_; 
v___x_725_ = 4194304;
v___x_726_ = lean_uint32_land(v___y_674_, v___x_725_);
v___x_727_ = 0;
v___x_728_ = lean_uint32_dec_eq(v___x_726_, v___x_727_);
if (v___x_728_ == 0)
{
goto v___jp_713_;
}
else
{
uint32_t v___x_729_; 
v___x_729_ = lean_uint32_lor(v___y_674_, v___x_725_);
return v___x_729_;
}
}
}
v___jp_730_:
{
float v_result_733_; uint8_t v___x_734_; 
v_result_733_ = lean_float32_mul(v___y_731_, v___y_732_);
v___x_734_ = lean_float32_beq(v_result_733_, v_result_733_);
if (v___x_734_ == 0)
{
uint32_t v___x_735_; uint32_t v___x_736_; uint32_t v___x_737_; uint32_t v___x_738_; uint8_t v___x_739_; 
v___x_735_ = 23;
v___x_736_ = lean_uint32_shift_right(v___y_674_, v___x_735_);
v___x_737_ = 255;
v___x_738_ = lean_uint32_land(v___x_736_, v___x_737_);
v___x_739_ = lean_uint32_dec_eq(v___x_738_, v___x_737_);
if (v___x_739_ == 0)
{
v___y_724_ = v___x_739_;
goto v___jp_723_;
}
else
{
uint32_t v___x_740_; uint32_t v___x_741_; uint32_t v___x_742_; uint8_t v___x_743_; 
v___x_740_ = 8388607;
v___x_741_ = lean_uint32_land(v___y_674_, v___x_740_);
v___x_742_ = 0;
v___x_743_ = lean_uint32_dec_eq(v___x_741_, v___x_742_);
if (v___x_743_ == 0)
{
v___y_724_ = v___x_739_;
goto v___jp_723_;
}
else
{
goto v___jp_713_;
}
}
}
else
{
uint32_t v___x_744_; 
v___x_744_ = lean_float32_to_bits(v_result_733_);
return v___x_744_;
}
}
v___jp_745_:
{
uint32_t v___x_747_; uint32_t v___x_748_; uint32_t v___x_749_; uint32_t v___x_750_; float v___x_751_; lean_object* v___x_752_; uint32_t v___x_753_; uint32_t v___x_754_; lean_object* v___x_755_; lean_object* v___x_756_; float v___x_757_; float v___x_758_; 
v___x_747_ = 8388607;
v___x_748_ = lean_uint32_land(v___y_675_, v___x_747_);
v___x_749_ = 8388608;
v___x_750_ = lean_uint32_lor(v___x_748_, v___x_749_);
v___x_751_ = lean_uint32_to_float32(v___x_750_);
v___x_752_ = lp_competition_R2W01b_scaleTable;
v___x_753_ = 23;
v___x_754_ = lean_uint32_shift_right(v___y_675_, v___x_753_);
v___x_755_ = lean_uint32_to_nat(v___x_754_);
v___x_756_ = lean_array_fget_borrowed(v___x_752_, v___x_755_);
lean_dec(v___x_755_);
v___x_757_ = lean_unbox_float32(v___x_756_);
v___x_758_ = lean_float32_mul(v___x_751_, v___x_757_);
v___y_731_ = v___y_746_;
v___y_732_ = v___x_758_;
goto v___jp_730_;
}
v___jp_759_:
{
if (v___y_761_ == 0)
{
float v___x_762_; 
v___x_762_ = lean_float32_of_bits(v___y_675_);
v___y_731_ = v___y_760_;
v___y_732_ = v___x_762_;
goto v___jp_730_;
}
else
{
v___y_746_ = v___y_760_;
goto v___jp_745_;
}
}
v___jp_763_:
{
uint32_t v___x_765_; uint32_t v_a_766_; uint32_t v___x_767_; uint32_t v___x_768_; uint32_t v___x_769_; uint8_t v___x_770_; uint32_t v___x_771_; uint8_t v___x_772_; 
v___x_765_ = 2147483647;
v_a_766_ = lean_uint32_land(v___y_675_, v___x_765_);
v___x_767_ = 201326591;
v___x_768_ = 1;
v___x_769_ = lean_uint32_sub(v_a_766_, v___x_768_);
v___x_770_ = lean_uint32_dec_le(v___x_767_, v___x_769_);
v___x_771_ = 2139095040;
v___x_772_ = lean_uint32_dec_lt(v_a_766_, v___x_771_);
if (v___x_770_ == 0)
{
if (v___x_772_ == 0)
{
v___y_746_ = v___y_764_;
goto v___jp_745_;
}
else
{
v___y_760_ = v___y_764_;
v___y_761_ = v___x_770_;
goto v___jp_759_;
}
}
else
{
v___y_760_ = v___y_764_;
v___y_761_ = v___x_772_;
goto v___jp_759_;
}
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
uint32_t v___x_779_; uint32_t v___x_780_; 
v___x_779_ = 8388608;
v___x_780_ = lean_uint32_lor(v___y_778_, v___x_779_);
return v___x_780_;
}
v___jp_781_:
{
uint32_t v___x_785_; uint32_t v___x_786_; 
v___x_785_ = lean_uint32_land(v___y_783_, v___y_782_);
v___x_786_ = lean_uint32_lor(v___y_784_, v___x_785_);
return v___x_786_;
}
v___jp_787_:
{
uint8_t v___x_792_; 
v___x_792_ = lean_uint64_dec_eq(v___y_791_, v___y_788_);
if (v___x_792_ == 0)
{
uint64_t v___x_793_; uint8_t v___x_794_; 
v___x_793_ = 8388608ULL;
v___x_794_ = lean_uint64_dec_eq(v___y_791_, v___x_793_);
if (v___x_794_ == 0)
{
uint32_t v___x_795_; 
v___x_795_ = lean_uint64_to_uint32(v___y_791_);
if (v___y_790_ == 0)
{
uint32_t v___x_796_; 
v___x_796_ = 0;
v___y_782_ = v___y_789_;
v___y_783_ = v___x_795_;
v___y_784_ = v___x_796_;
goto v___jp_781_;
}
else
{
uint32_t v___x_797_; 
v___x_797_ = 2147483648;
v___y_782_ = v___y_789_;
v___y_783_ = v___x_795_;
v___y_784_ = v___x_797_;
goto v___jp_781_;
}
}
else
{
if (v___y_790_ == 0)
{
uint32_t v___x_798_; 
v___x_798_ = 0;
v___y_778_ = v___x_798_;
goto v___jp_777_;
}
else
{
uint32_t v___x_799_; 
v___x_799_ = 2147483648;
v___y_778_ = v___x_799_;
goto v___jp_777_;
}
}
}
else
{
if (v___y_790_ == 0)
{
uint32_t v___x_800_; 
v___x_800_ = 0;
return v___x_800_;
}
else
{
uint32_t v___x_801_; 
v___x_801_ = 2147483648;
return v___x_801_;
}
}
}
v___jp_802_:
{
uint32_t v___x_806_; uint32_t v___x_807_; 
v___x_806_ = lean_uint32_land(v___y_804_, v___y_803_);
v___x_807_ = lean_uint32_lor(v___y_805_, v___x_806_);
return v___x_807_;
}
v___jp_808_:
{
uint8_t v___x_813_; 
v___x_813_ = lean_uint64_dec_eq(v___y_812_, v___y_811_);
if (v___x_813_ == 0)
{
uint64_t v___x_814_; uint8_t v___x_815_; 
v___x_814_ = 8388608ULL;
v___x_815_ = lean_uint64_dec_eq(v___y_812_, v___x_814_);
if (v___x_815_ == 0)
{
uint32_t v___x_816_; 
v___x_816_ = lean_uint64_to_uint32(v___y_812_);
if (v___y_810_ == 0)
{
uint32_t v___x_817_; 
v___x_817_ = 0;
v___y_803_ = v___y_809_;
v___y_804_ = v___x_816_;
v___y_805_ = v___x_817_;
goto v___jp_802_;
}
else
{
uint32_t v___x_818_; 
v___x_818_ = 2147483648;
v___y_803_ = v___y_809_;
v___y_804_ = v___x_816_;
v___y_805_ = v___x_818_;
goto v___jp_802_;
}
}
else
{
if (v___y_810_ == 0)
{
uint32_t v___x_819_; 
v___x_819_ = 0;
v___y_774_ = v___x_819_;
goto v___jp_773_;
}
else
{
uint32_t v___x_820_; 
v___x_820_ = 2147483648;
v___y_774_ = v___x_820_;
goto v___jp_773_;
}
}
}
else
{
if (v___y_810_ == 0)
{
uint32_t v___x_821_; 
v___x_821_ = 0;
return v___x_821_;
}
else
{
uint32_t v___x_822_; 
v___x_822_ = 2147483648;
return v___x_822_;
}
}
}
v___jp_825_:
{
uint32_t v___x_826_; uint32_t v___x_827_; uint32_t v___x_828_; uint32_t v___x_829_; float v___x_830_; lean_object* v___x_831_; lean_object* v___x_832_; lean_object* v___x_833_; float v___x_834_; float v___x_835_; 
v___x_826_ = 8388607;
v___x_827_ = lean_uint32_land(v___y_674_, v___x_826_);
v___x_828_ = 8388608;
v___x_829_ = lean_uint32_lor(v___x_827_, v___x_828_);
v___x_830_ = lean_uint32_to_float32(v___x_829_);
v___x_831_ = lp_competition_R2W01b_scaleTable;
v___x_832_ = lean_uint32_to_nat(v___x_824_);
v___x_833_ = lean_array_fget_borrowed(v___x_831_, v___x_832_);
lean_dec(v___x_832_);
v___x_834_ = lean_unbox_float32(v___x_833_);
v___x_835_ = lean_float32_mul(v___x_830_, v___x_834_);
v___y_764_ = v___x_835_;
goto v___jp_763_;
}
v___jp_836_:
{
if (v___y_837_ == 0)
{
float v___x_838_; 
v___x_838_ = lean_float32_of_bits(v___y_674_);
v___y_764_ = v___x_838_;
goto v___jp_763_;
}
else
{
goto v___jp_825_;
}
}
v___jp_840_:
{
uint32_t v___x_845_; uint32_t v___x_846_; uint32_t v___x_847_; uint32_t v___x_848_; uint32_t v___x_849_; 
v___x_845_ = lean_uint32_land(v___y_843_, v___x_839_);
v___x_846_ = lean_uint32_shift_left(v___x_845_, v___x_823_);
v___x_847_ = lean_uint32_lor(v___y_844_, v___x_846_);
v___x_848_ = lean_uint32_land(v___y_841_, v___y_842_);
v___x_849_ = lean_uint32_lor(v___x_847_, v___x_848_);
return v___x_849_;
}
v___jp_850_:
{
if (v___y_853_ == 0)
{
uint32_t v___x_855_; 
v___x_855_ = 0;
v___y_841_ = v___y_854_;
v___y_842_ = v___y_851_;
v___y_843_ = v___y_852_;
v___y_844_ = v___x_855_;
goto v___jp_840_;
}
else
{
uint32_t v___x_856_; 
v___x_856_ = 2147483648;
v___y_841_ = v___y_854_;
v___y_842_ = v___y_851_;
v___y_843_ = v___y_852_;
v___y_844_ = v___x_856_;
goto v___jp_840_;
}
}
v___jp_857_:
{
uint64_t v___x_863_; uint64_t v_encodedExponent_864_; uint32_t v___x_865_; uint64_t v___x_866_; uint8_t v___x_867_; 
v___x_863_ = 171ULL;
v_encodedExponent_864_ = lean_uint64_sub(v___y_861_, v___x_863_);
v___x_865_ = lean_uint64_to_uint32(v_encodedExponent_864_);
v___x_866_ = 8388608ULL;
v___x_867_ = lean_uint64_dec_lt(v___y_862_, v___x_866_);
if (v___x_867_ == 0)
{
uint64_t v___x_868_; uint32_t v___x_869_; 
v___x_868_ = lean_uint64_sub(v___y_862_, v___x_866_);
v___x_869_ = lean_uint64_to_uint32(v___x_868_);
v___y_851_ = v___y_859_;
v___y_852_ = v___x_865_;
v___y_853_ = v___y_860_;
v___y_854_ = v___x_869_;
goto v___jp_850_;
}
else
{
uint32_t v___x_870_; 
v___x_870_ = lean_uint64_to_uint32(v___y_858_);
v___y_851_ = v___y_859_;
v___y_852_ = v___x_865_;
v___y_853_ = v___y_860_;
v___y_854_ = v___x_870_;
goto v___jp_850_;
}
}
v___jp_871_:
{
uint64_t v___x_878_; uint8_t v___x_879_; 
v___x_878_ = 425ULL;
v___x_879_ = lean_uint64_dec_lt(v___x_878_, v___y_877_);
if (v___x_879_ == 0)
{
if (v___y_874_ == 0)
{
v___y_858_ = v___y_872_;
v___y_859_ = v___y_873_;
v___y_860_ = v___y_875_;
v___y_861_ = v___y_877_;
v___y_862_ = v___y_876_;
goto v___jp_857_;
}
else
{
uint64_t v___x_880_; 
v___x_880_ = 8388608ULL;
v___y_858_ = v___y_872_;
v___y_859_ = v___y_873_;
v___y_860_ = v___y_875_;
v___y_861_ = v___y_877_;
v___y_862_ = v___x_880_;
goto v___jp_857_;
}
}
else
{
if (v___y_875_ == 0)
{
uint32_t v___x_881_; 
v___x_881_ = 2139095040;
return v___x_881_;
}
else
{
uint32_t v___x_882_; 
v___x_882_ = 4286578688;
return v___x_882_;
}
}
}
v___jp_883_:
{
uint64_t v___x_889_; uint8_t v_carry_890_; 
v___x_889_ = 16777216ULL;
v_carry_890_ = lean_uint64_dec_eq(v___y_888_, v___x_889_);
if (v_carry_890_ == 0)
{
v___y_872_ = v___y_884_;
v___y_873_ = v___y_885_;
v___y_874_ = v_carry_890_;
v___y_875_ = v___y_887_;
v___y_876_ = v___y_888_;
v___y_877_ = v___y_886_;
goto v___jp_871_;
}
else
{
uint64_t v___x_891_; uint64_t v___x_892_; 
v___x_891_ = 1ULL;
v___x_892_ = lean_uint64_add(v___y_886_, v___x_891_);
v___y_872_ = v___y_884_;
v___y_873_ = v___y_885_;
v___y_874_ = v_carry_890_;
v___y_875_ = v___y_887_;
v___y_876_ = v___y_888_;
v___y_877_ = v___x_892_;
goto v___jp_871_;
}
}
v___jp_893_:
{
uint64_t v_position_900_; uint64_t v___x_901_; uint8_t v___x_902_; 
v_position_900_ = lean_uint64_add(v___y_899_, v___y_895_);
v___x_901_ = 172ULL;
v___x_902_ = lean_uint64_dec_lt(v_position_900_, v___x_901_);
if (v___x_902_ == 0)
{
uint64_t v___x_903_; uint8_t v___x_904_; 
v___x_903_ = 23ULL;
v___x_904_ = lean_uint64_dec_lt(v___y_899_, v___x_903_);
if (v___x_904_ == 0)
{
uint64_t v___x_905_; uint8_t v___x_906_; 
v___x_905_ = lean_uint64_sub(v___y_899_, v___x_903_);
v___x_906_ = lean_uint64_dec_eq(v___x_905_, v___y_894_);
if (v___x_906_ == 0)
{
uint64_t v___x_907_; uint8_t v___x_908_; 
v___x_907_ = 64ULL;
v___x_908_ = lean_uint64_dec_lt(v___x_905_, v___x_907_);
if (v___x_908_ == 0)
{
uint8_t v___x_909_; 
v___x_909_ = lean_uint64_dec_eq(v___x_905_, v___x_907_);
if (v___x_909_ == 0)
{
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v___y_894_;
goto v___jp_883_;
}
else
{
uint64_t v___x_910_; uint8_t v___x_911_; 
v___x_910_ = 9223372036854775808ULL;
v___x_911_ = lean_uint64_dec_lt(v___x_910_, v___y_897_);
if (v___x_911_ == 0)
{
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v___y_894_;
goto v___jp_883_;
}
else
{
uint64_t v___x_912_; 
v___x_912_ = 1ULL;
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v___x_912_;
goto v___jp_883_;
}
}
}
else
{
uint64_t v_quotient_913_; uint64_t v___x_914_; uint64_t v___x_915_; uint64_t v___x_916_; uint64_t v_remainder_917_; uint64_t v___x_918_; uint64_t v_half_919_; uint8_t v___x_920_; 
v_quotient_913_ = lean_uint64_shift_right(v___y_897_, v___x_905_);
v___x_914_ = 1ULL;
v___x_915_ = lean_uint64_shift_left(v___x_914_, v___x_905_);
v___x_916_ = lean_uint64_sub(v___x_915_, v___x_914_);
v_remainder_917_ = lean_uint64_land(v___y_897_, v___x_916_);
v___x_918_ = lean_uint64_sub(v___x_905_, v___x_914_);
v_half_919_ = lean_uint64_shift_left(v___x_914_, v___x_918_);
v___x_920_ = lean_uint64_dec_lt(v_remainder_917_, v_half_919_);
if (v___x_920_ == 0)
{
uint8_t v___x_921_; 
v___x_921_ = lean_uint64_dec_lt(v_half_919_, v_remainder_917_);
if (v___x_921_ == 0)
{
uint64_t v___x_922_; uint8_t v___x_923_; 
v___x_922_ = lean_uint64_land(v_quotient_913_, v___x_914_);
v___x_923_ = lean_uint64_dec_eq(v___x_922_, v___y_894_);
if (v___x_923_ == 0)
{
uint64_t v___x_924_; 
v___x_924_ = lean_uint64_add(v_quotient_913_, v___x_914_);
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v___x_924_;
goto v___jp_883_;
}
else
{
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v_quotient_913_;
goto v___jp_883_;
}
}
else
{
uint64_t v___x_925_; 
v___x_925_ = lean_uint64_add(v_quotient_913_, v___x_914_);
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v___x_925_;
goto v___jp_883_;
}
}
else
{
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v_quotient_913_;
goto v___jp_883_;
}
}
}
else
{
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v___y_897_;
goto v___jp_883_;
}
}
else
{
uint64_t v___x_926_; uint64_t v___x_927_; 
v___x_926_ = lean_uint64_sub(v___x_903_, v___y_899_);
v___x_927_ = lean_uint64_shift_left(v___y_897_, v___x_926_);
v___y_884_ = v___y_894_;
v___y_885_ = v___y_896_;
v___y_886_ = v_position_900_;
v___y_887_ = v___y_898_;
v___y_888_ = v___x_927_;
goto v___jp_883_;
}
}
else
{
uint64_t v___x_928_; uint8_t v___x_929_; 
v___x_928_ = 149ULL;
v___x_929_ = lean_uint64_dec_lt(v___y_895_, v___x_928_);
if (v___x_929_ == 0)
{
uint64_t v___x_930_; uint64_t v___x_931_; 
v___x_930_ = lean_uint64_sub(v___y_895_, v___x_928_);
v___x_931_ = lean_uint64_shift_left(v___y_897_, v___x_930_);
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v___x_931_;
goto v___jp_787_;
}
else
{
uint64_t v___x_932_; uint8_t v___x_933_; 
v___x_932_ = lean_uint64_sub(v___x_928_, v___y_895_);
v___x_933_ = lean_uint64_dec_eq(v___x_932_, v___y_894_);
if (v___x_933_ == 0)
{
uint64_t v___x_934_; uint8_t v___x_935_; 
v___x_934_ = 64ULL;
v___x_935_ = lean_uint64_dec_lt(v___x_932_, v___x_934_);
if (v___x_935_ == 0)
{
uint8_t v___x_936_; 
v___x_936_ = lean_uint64_dec_eq(v___x_932_, v___x_934_);
if (v___x_936_ == 0)
{
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v___y_894_;
goto v___jp_787_;
}
else
{
uint64_t v___x_937_; uint8_t v___x_938_; 
v___x_937_ = 9223372036854775808ULL;
v___x_938_ = lean_uint64_dec_lt(v___x_937_, v___y_897_);
if (v___x_938_ == 0)
{
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v___y_894_;
goto v___jp_787_;
}
else
{
uint64_t v___x_939_; 
v___x_939_ = 1ULL;
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v___x_939_;
goto v___jp_787_;
}
}
}
else
{
uint64_t v_quotient_940_; uint64_t v___x_941_; uint64_t v___x_942_; uint64_t v___x_943_; uint64_t v_remainder_944_; uint64_t v___x_945_; uint64_t v_half_946_; uint8_t v___x_947_; 
v_quotient_940_ = lean_uint64_shift_right(v___y_897_, v___x_932_);
v___x_941_ = 1ULL;
v___x_942_ = lean_uint64_shift_left(v___x_941_, v___x_932_);
v___x_943_ = lean_uint64_sub(v___x_942_, v___x_941_);
v_remainder_944_ = lean_uint64_land(v___y_897_, v___x_943_);
v___x_945_ = lean_uint64_sub(v___x_932_, v___x_941_);
v_half_946_ = lean_uint64_shift_left(v___x_941_, v___x_945_);
v___x_947_ = lean_uint64_dec_lt(v_remainder_944_, v_half_946_);
if (v___x_947_ == 0)
{
uint8_t v___x_948_; 
v___x_948_ = lean_uint64_dec_lt(v_half_946_, v_remainder_944_);
if (v___x_948_ == 0)
{
uint64_t v___x_949_; uint8_t v___x_950_; 
v___x_949_ = lean_uint64_land(v_quotient_940_, v___x_941_);
v___x_950_ = lean_uint64_dec_eq(v___x_949_, v___y_894_);
if (v___x_950_ == 0)
{
uint64_t v___x_951_; 
v___x_951_ = lean_uint64_add(v_quotient_940_, v___x_941_);
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v___x_951_;
goto v___jp_787_;
}
else
{
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v_quotient_940_;
goto v___jp_787_;
}
}
else
{
uint64_t v___x_952_; 
v___x_952_ = lean_uint64_add(v_quotient_940_, v___x_941_);
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v___x_952_;
goto v___jp_787_;
}
}
else
{
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v_quotient_940_;
goto v___jp_787_;
}
}
}
else
{
v___y_788_ = v___y_894_;
v___y_789_ = v___y_896_;
v___y_790_ = v___y_898_;
v___y_791_ = v___y_897_;
goto v___jp_787_;
}
}
}
}
v___jp_953_:
{
uint64_t v___x_961_; uint64_t v___x_962_; uint8_t v___x_963_; 
v___x_961_ = 1ULL;
v___x_962_ = lean_uint64_shift_right(v___y_959_, v___x_961_);
v___x_963_ = lean_uint64_dec_eq(v___x_962_, v___y_955_);
if (v___x_963_ == 0)
{
uint64_t v___x_964_; 
v___x_964_ = lean_uint64_add(v___y_960_, v___x_961_);
v___y_894_ = v___y_955_;
v___y_895_ = v___y_954_;
v___y_896_ = v___y_956_;
v___y_897_ = v___y_957_;
v___y_898_ = v___y_958_;
v___y_899_ = v___x_964_;
goto v___jp_893_;
}
else
{
v___y_894_ = v___y_955_;
v___y_895_ = v___y_954_;
v___y_896_ = v___y_956_;
v___y_897_ = v___y_957_;
v___y_898_ = v___y_958_;
v___y_899_ = v___y_960_;
goto v___jp_893_;
}
}
v___jp_965_:
{
uint64_t v___x_975_; uint8_t v___x_976_; 
v___x_975_ = lean_uint64_shift_right(v___y_966_, v___y_967_);
v___x_976_ = lean_uint64_dec_eq(v___x_975_, v___y_968_);
if (v___x_976_ == 0)
{
uint64_t v___x_977_; 
v___x_977_ = lean_uint64_add(v___y_972_, v___y_967_);
v___y_954_ = v___y_969_;
v___y_955_ = v___y_968_;
v___y_956_ = v___y_970_;
v___y_957_ = v___y_971_;
v___y_958_ = v___y_973_;
v___y_959_ = v___y_974_;
v___y_960_ = v___x_977_;
goto v___jp_953_;
}
else
{
v___y_954_ = v___y_969_;
v___y_955_ = v___y_968_;
v___y_956_ = v___y_970_;
v___y_957_ = v___y_971_;
v___y_958_ = v___y_973_;
v___y_959_ = v___y_974_;
v___y_960_ = v___y_972_;
goto v___jp_953_;
}
}
v___jp_978_:
{
uint64_t v___x_986_; uint64_t v___x_987_; uint8_t v___x_988_; 
v___x_986_ = 2ULL;
v___x_987_ = lean_uint64_shift_right(v___y_979_, v___x_986_);
v___x_988_ = lean_uint64_dec_eq(v___x_987_, v___y_981_);
if (v___x_988_ == 0)
{
v___y_966_ = v___y_979_;
v___y_967_ = v___x_986_;
v___y_968_ = v___y_981_;
v___y_969_ = v___y_980_;
v___y_970_ = v___y_982_;
v___y_971_ = v___y_983_;
v___y_972_ = v___y_985_;
v___y_973_ = v___y_984_;
v___y_974_ = v___x_987_;
goto v___jp_965_;
}
else
{
v___y_966_ = v___y_979_;
v___y_967_ = v___x_986_;
v___y_968_ = v___y_981_;
v___y_969_ = v___y_980_;
v___y_970_ = v___y_982_;
v___y_971_ = v___y_983_;
v___y_972_ = v___y_985_;
v___y_973_ = v___y_984_;
v___y_974_ = v___y_979_;
goto v___jp_965_;
}
}
v___jp_989_:
{
uint64_t v___x_999_; uint8_t v___x_1000_; 
v___x_999_ = lean_uint64_shift_right(v___y_997_, v___y_990_);
v___x_1000_ = lean_uint64_dec_eq(v___x_999_, v___y_991_);
if (v___x_1000_ == 0)
{
uint64_t v___x_1001_; 
v___x_1001_ = lean_uint64_add(v___y_995_, v___y_990_);
v___y_979_ = v___y_998_;
v___y_980_ = v___y_992_;
v___y_981_ = v___y_991_;
v___y_982_ = v___y_993_;
v___y_983_ = v___y_994_;
v___y_984_ = v___y_996_;
v___y_985_ = v___x_1001_;
goto v___jp_978_;
}
else
{
v___y_979_ = v___y_998_;
v___y_980_ = v___y_992_;
v___y_981_ = v___y_991_;
v___y_982_ = v___y_993_;
v___y_983_ = v___y_994_;
v___y_984_ = v___y_996_;
v___y_985_ = v___y_995_;
goto v___jp_978_;
}
}
v___jp_1002_:
{
uint64_t v___x_1010_; uint64_t v___x_1011_; uint8_t v___x_1012_; 
v___x_1010_ = 4ULL;
v___x_1011_ = lean_uint64_shift_right(v___y_1008_, v___x_1010_);
v___x_1012_ = lean_uint64_dec_eq(v___x_1011_, v___y_1004_);
if (v___x_1012_ == 0)
{
v___y_990_ = v___x_1010_;
v___y_991_ = v___y_1004_;
v___y_992_ = v___y_1003_;
v___y_993_ = v___y_1005_;
v___y_994_ = v___y_1006_;
v___y_995_ = v___y_1009_;
v___y_996_ = v___y_1007_;
v___y_997_ = v___y_1008_;
v___y_998_ = v___x_1011_;
goto v___jp_989_;
}
else
{
v___y_990_ = v___x_1010_;
v___y_991_ = v___y_1004_;
v___y_992_ = v___y_1003_;
v___y_993_ = v___y_1005_;
v___y_994_ = v___y_1006_;
v___y_995_ = v___y_1009_;
v___y_996_ = v___y_1007_;
v___y_997_ = v___y_1008_;
v___y_998_ = v___y_1008_;
goto v___jp_989_;
}
}
v___jp_1013_:
{
uint64_t v___x_1023_; uint8_t v___x_1024_; 
v___x_1023_ = lean_uint64_shift_right(v___y_1018_, v___y_1021_);
v___x_1024_ = lean_uint64_dec_eq(v___x_1023_, v___y_1014_);
if (v___x_1024_ == 0)
{
uint64_t v___x_1025_; 
v___x_1025_ = lean_uint64_add(v___y_1020_, v___y_1021_);
v___y_1003_ = v___y_1015_;
v___y_1004_ = v___y_1014_;
v___y_1005_ = v___y_1016_;
v___y_1006_ = v___y_1017_;
v___y_1007_ = v___y_1019_;
v___y_1008_ = v___y_1022_;
v___y_1009_ = v___x_1025_;
goto v___jp_1002_;
}
else
{
v___y_1003_ = v___y_1015_;
v___y_1004_ = v___y_1014_;
v___y_1005_ = v___y_1016_;
v___y_1006_ = v___y_1017_;
v___y_1007_ = v___y_1019_;
v___y_1008_ = v___y_1022_;
v___y_1009_ = v___y_1020_;
goto v___jp_1002_;
}
}
v___jp_1026_:
{
uint64_t v___x_1034_; uint64_t v___x_1035_; uint8_t v___x_1036_; 
v___x_1034_ = 8ULL;
v___x_1035_ = lean_uint64_shift_right(v___y_1031_, v___x_1034_);
v___x_1036_ = lean_uint64_dec_eq(v___x_1035_, v___y_1028_);
if (v___x_1036_ == 0)
{
v___y_1014_ = v___y_1028_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1029_;
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___y_1031_;
v___y_1019_ = v___y_1032_;
v___y_1020_ = v___y_1033_;
v___y_1021_ = v___x_1034_;
v___y_1022_ = v___x_1035_;
goto v___jp_1013_;
}
else
{
v___y_1014_ = v___y_1028_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1029_;
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___y_1031_;
v___y_1019_ = v___y_1032_;
v___y_1020_ = v___y_1033_;
v___y_1021_ = v___x_1034_;
v___y_1022_ = v___y_1031_;
goto v___jp_1013_;
}
}
v___jp_1037_:
{
uint64_t v___x_1047_; uint8_t v___x_1048_; 
v___x_1047_ = lean_uint64_shift_right(v___y_1038_, v___y_1043_);
v___x_1048_ = lean_uint64_dec_eq(v___x_1047_, v___y_1039_);
if (v___x_1048_ == 0)
{
uint64_t v___x_1049_; 
v___x_1049_ = lean_uint64_add(v___y_1045_, v___y_1043_);
v___y_1027_ = v___y_1040_;
v___y_1028_ = v___y_1039_;
v___y_1029_ = v___y_1041_;
v___y_1030_ = v___y_1042_;
v___y_1031_ = v___y_1046_;
v___y_1032_ = v___y_1044_;
v___y_1033_ = v___x_1049_;
goto v___jp_1026_;
}
else
{
v___y_1027_ = v___y_1040_;
v___y_1028_ = v___y_1039_;
v___y_1029_ = v___y_1041_;
v___y_1030_ = v___y_1042_;
v___y_1031_ = v___y_1046_;
v___y_1032_ = v___y_1044_;
v___y_1033_ = v___y_1045_;
goto v___jp_1026_;
}
}
v___jp_1050_:
{
uint64_t v___x_1058_; uint64_t v___x_1059_; uint8_t v___x_1060_; 
v___x_1058_ = 16ULL;
v___x_1059_ = lean_uint64_shift_right(v___y_1051_, v___x_1058_);
v___x_1060_ = lean_uint64_dec_eq(v___x_1059_, v___y_1053_);
if (v___x_1060_ == 0)
{
v___y_1038_ = v___y_1051_;
v___y_1039_ = v___y_1053_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___y_1054_;
v___y_1042_ = v___y_1055_;
v___y_1043_ = v___x_1058_;
v___y_1044_ = v___y_1056_;
v___y_1045_ = v___y_1057_;
v___y_1046_ = v___x_1059_;
goto v___jp_1037_;
}
else
{
v___y_1038_ = v___y_1051_;
v___y_1039_ = v___y_1053_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___y_1054_;
v___y_1042_ = v___y_1055_;
v___y_1043_ = v___x_1058_;
v___y_1044_ = v___y_1056_;
v___y_1045_ = v___y_1057_;
v___y_1046_ = v___y_1051_;
goto v___jp_1037_;
}
}
v___jp_1061_:
{
uint64_t v___x_1069_; uint8_t v___x_1070_; 
v___x_1069_ = lean_uint64_shift_right(v___y_1066_, v___y_1062_);
v___x_1070_ = lean_uint64_dec_eq(v___x_1069_, v___y_1063_);
if (v___x_1070_ == 0)
{
v___y_1051_ = v___y_1068_;
v___y_1052_ = v___y_1064_;
v___y_1053_ = v___y_1063_;
v___y_1054_ = v___y_1065_;
v___y_1055_ = v___y_1066_;
v___y_1056_ = v___y_1067_;
v___y_1057_ = v___y_1062_;
goto v___jp_1050_;
}
else
{
v___y_1051_ = v___y_1068_;
v___y_1052_ = v___y_1064_;
v___y_1053_ = v___y_1063_;
v___y_1054_ = v___y_1065_;
v___y_1055_ = v___y_1066_;
v___y_1056_ = v___y_1067_;
v___y_1057_ = v___y_1063_;
goto v___jp_1050_;
}
}
v___jp_1071_:
{
uint64_t v___x_1076_; uint8_t v___x_1077_; 
v___x_1076_ = 0ULL;
v___x_1077_ = lean_uint64_dec_eq(v___y_1074_, v___x_1076_);
if (v___x_1077_ == 0)
{
uint64_t v___x_1078_; uint64_t v___x_1079_; uint8_t v___x_1080_; 
v___x_1078_ = 32ULL;
v___x_1079_ = lean_uint64_shift_right(v___y_1074_, v___x_1078_);
v___x_1080_ = lean_uint64_dec_eq(v___x_1079_, v___x_1076_);
if (v___x_1080_ == 0)
{
v___y_1062_ = v___x_1078_;
v___y_1063_ = v___x_1076_;
v___y_1064_ = v___y_1072_;
v___y_1065_ = v___y_1073_;
v___y_1066_ = v___y_1074_;
v___y_1067_ = v___y_1075_;
v___y_1068_ = v___x_1079_;
goto v___jp_1061_;
}
else
{
v___y_1062_ = v___x_1078_;
v___y_1063_ = v___x_1076_;
v___y_1064_ = v___y_1072_;
v___y_1065_ = v___y_1073_;
v___y_1066_ = v___y_1074_;
v___y_1067_ = v___y_1075_;
v___y_1068_ = v___y_1074_;
goto v___jp_1061_;
}
}
else
{
if (v___y_1075_ == 0)
{
uint32_t v___x_1081_; 
v___x_1081_ = 0;
return v___x_1081_;
}
else
{
uint32_t v___x_1082_; 
v___x_1082_ = 2147483648;
return v___x_1082_;
}
}
}
v___jp_1083_:
{
uint64_t v___x_1090_; uint64_t v___x_1091_; uint64_t v___x_1092_; uint8_t v___x_1093_; 
v___x_1090_ = lean_uint64_mul(v___y_1084_, v___y_1086_);
v___x_1091_ = lean_uint64_add(v___y_1088_, v___y_1089_);
v___x_1092_ = 281474976710656ULL;
v___x_1093_ = lean_uint64_dec_lt(v___x_1090_, v___x_1092_);
if (v___x_1093_ == 0)
{
v___y_1072_ = v___x_1091_;
v___y_1073_ = v___y_1085_;
v___y_1074_ = v___x_1090_;
v___y_1075_ = v___y_1087_;
goto v___jp_1071_;
}
else
{
uint64_t v___x_1094_; uint8_t v___x_1095_; 
v___x_1094_ = 123ULL;
v___x_1095_ = lean_uint64_dec_le(v___x_1091_, v___x_1094_);
if (v___x_1095_ == 0)
{
v___y_1072_ = v___x_1091_;
v___y_1073_ = v___y_1085_;
v___y_1074_ = v___x_1090_;
v___y_1075_ = v___y_1087_;
goto v___jp_1071_;
}
else
{
uint64_t v___x_1096_; uint8_t v___x_1097_; 
v___x_1096_ = 0ULL;
v___x_1097_ = lean_uint64_dec_eq(v___x_1090_, v___x_1096_);
if (v___x_1097_ == 0)
{
uint64_t v___x_1098_; uint64_t v___x_1099_; uint8_t v___x_1100_; 
v___x_1098_ = 149ULL;
v___x_1099_ = lean_uint64_sub(v___x_1098_, v___x_1091_);
v___x_1100_ = lean_uint64_dec_eq(v___x_1099_, v___x_1096_);
if (v___x_1100_ == 0)
{
uint64_t v___x_1101_; uint8_t v___x_1102_; 
v___x_1101_ = 64ULL;
v___x_1102_ = lean_uint64_dec_lt(v___x_1099_, v___x_1101_);
if (v___x_1102_ == 0)
{
uint8_t v___x_1103_; 
v___x_1103_ = lean_uint64_dec_eq(v___x_1099_, v___x_1101_);
if (v___x_1103_ == 0)
{
v___y_809_ = v___y_1085_;
v___y_810_ = v___y_1087_;
v___y_811_ = v___x_1096_;
v___y_812_ = v___x_1096_;
goto v___jp_808_;
}
else
{
uint64_t v___x_1104_; uint8_t v___x_1105_; 
v___x_1104_ = 9223372036854775808ULL;
v___x_1105_ = lean_uint64_dec_lt(v___x_1104_, v___x_1090_);
if (v___x_1105_ == 0)
{
v___y_809_ = v___y_1085_;
v___y_810_ = v___y_1087_;
v___y_811_ = v___x_1096_;
v___y_812_ = v___x_1096_;
goto v___jp_808_;
}
else
{
uint64_t v___x_1106_; 
v___x_1106_ = 1ULL;
v___y_809_ = v___y_1085_;
v___y_810_ = v___y_1087_;
v___y_811_ = v___x_1096_;
v___y_812_ = v___x_1106_;
goto v___jp_808_;
}
}
}
else
{
uint64_t v_quotient_1107_; uint64_t v___x_1108_; uint64_t v___x_1109_; uint64_t v___x_1110_; uint64_t v_remainder_1111_; uint64_t v___x_1112_; uint64_t v_half_1113_; uint8_t v___x_1114_; 
v_quotient_1107_ = lean_uint64_shift_right(v___x_1090_, v___x_1099_);
v___x_1108_ = 1ULL;
v___x_1109_ = lean_uint64_shift_left(v___x_1108_, v___x_1099_);
v___x_1110_ = lean_uint64_sub(v___x_1109_, v___x_1108_);
v_remainder_1111_ = lean_uint64_land(v___x_1090_, v___x_1110_);
v___x_1112_ = lean_uint64_sub(v___x_1099_, v___x_1108_);
v_half_1113_ = lean_uint64_shift_left(v___x_1108_, v___x_1112_);
v___x_1114_ = lean_uint64_dec_lt(v_remainder_1111_, v_half_1113_);
if (v___x_1114_ == 0)
{
uint8_t v___x_1115_; 
v___x_1115_ = lean_uint64_dec_lt(v_half_1113_, v_remainder_1111_);
if (v___x_1115_ == 0)
{
uint64_t v___x_1116_; uint8_t v___x_1117_; 
v___x_1116_ = lean_uint64_land(v_quotient_1107_, v___x_1108_);
v___x_1117_ = lean_uint64_dec_eq(v___x_1116_, v___x_1096_);
if (v___x_1117_ == 0)
{
uint64_t v___x_1118_; 
v___x_1118_ = lean_uint64_add(v_quotient_1107_, v___x_1108_);
v___y_809_ = v___y_1085_;
v___y_810_ = v___y_1087_;
v___y_811_ = v___x_1096_;
v___y_812_ = v___x_1118_;
goto v___jp_808_;
}
else
{
v___y_809_ = v___y_1085_;
v___y_810_ = v___y_1087_;
v___y_811_ = v___x_1096_;
v___y_812_ = v_quotient_1107_;
goto v___jp_808_;
}
}
else
{
uint64_t v___x_1119_; 
v___x_1119_ = lean_uint64_add(v_quotient_1107_, v___x_1108_);
v___y_809_ = v___y_1085_;
v___y_810_ = v___y_1087_;
v___y_811_ = v___x_1096_;
v___y_812_ = v___x_1119_;
goto v___jp_808_;
}
}
else
{
v___y_809_ = v___y_1085_;
v___y_810_ = v___y_1087_;
v___y_811_ = v___x_1096_;
v___y_812_ = v_quotient_1107_;
goto v___jp_808_;
}
}
}
else
{
v___y_809_ = v___y_1085_;
v___y_810_ = v___y_1087_;
v___y_811_ = v___x_1096_;
v___y_812_ = v___x_1090_;
goto v___jp_808_;
}
}
else
{
if (v___y_1087_ == 0)
{
uint32_t v___x_1120_; 
v___x_1120_ = 0;
return v___x_1120_;
}
else
{
uint32_t v___x_1121_; 
v___x_1121_ = 2147483648;
return v___x_1121_;
}
}
}
}
}
v___jp_1125_:
{
uint64_t v___x_1131_; uint64_t v___x_1132_; uint8_t v___x_1133_; 
v___x_1131_ = lean_uint32_to_uint64(v_ey_1124_);
v___x_1132_ = 0ULL;
v___x_1133_ = lean_uint64_dec_eq(v___x_1131_, v___x_1132_);
if (v___x_1133_ == 0)
{
uint64_t v___x_1134_; uint64_t v___x_1135_; 
v___x_1134_ = 1ULL;
v___x_1135_ = lean_uint64_sub(v___x_1131_, v___x_1134_);
v___y_1084_ = v___y_1126_;
v___y_1085_ = v___y_1128_;
v___y_1086_ = v___y_1127_;
v___y_1087_ = v___y_1129_;
v___y_1088_ = v___y_1130_;
v___y_1089_ = v___x_1135_;
goto v___jp_1083_;
}
else
{
v___y_1084_ = v___y_1126_;
v___y_1085_ = v___y_1128_;
v___y_1086_ = v___y_1127_;
v___y_1087_ = v___y_1129_;
v___y_1088_ = v___y_1130_;
v___y_1089_ = v___x_1132_;
goto v___jp_1083_;
}
}
v___jp_1136_:
{
uint64_t v___x_1141_; uint64_t v___x_1142_; uint8_t v___x_1143_; 
v___x_1141_ = lean_uint32_to_uint64(v_ex_1122_);
v___x_1142_ = 0ULL;
v___x_1143_ = lean_uint64_dec_eq(v___x_1141_, v___x_1142_);
if (v___x_1143_ == 0)
{
uint64_t v___x_1144_; uint64_t v___x_1145_; 
v___x_1144_ = 1ULL;
v___x_1145_ = lean_uint64_sub(v___x_1141_, v___x_1144_);
v___y_1126_ = v___y_1137_;
v___y_1127_ = v___y_1140_;
v___y_1128_ = v___y_1138_;
v___y_1129_ = v___y_1139_;
v___y_1130_ = v___x_1145_;
goto v___jp_1125_;
}
else
{
v___y_1126_ = v___y_1137_;
v___y_1127_ = v___y_1140_;
v___y_1128_ = v___y_1138_;
v___y_1129_ = v___y_1139_;
v___y_1130_ = v___x_1142_;
goto v___jp_1125_;
}
}
v___jp_1146_:
{
uint32_t v___x_1151_; uint8_t v___x_1152_; 
v___x_1151_ = 0;
v___x_1152_ = lean_uint32_dec_eq(v_ey_1124_, v___x_1151_);
if (v___x_1152_ == 0)
{
uint64_t v___x_1153_; uint64_t v___x_1154_; uint64_t v___x_1155_; 
v___x_1153_ = lean_uint32_to_uint64(v___y_1148_);
v___x_1154_ = 8388608ULL;
v___x_1155_ = lean_uint64_lor(v___x_1153_, v___x_1154_);
v___y_1137_ = v___y_1150_;
v___y_1138_ = v___y_1147_;
v___y_1139_ = v___y_1149_;
v___y_1140_ = v___x_1155_;
goto v___jp_1136_;
}
else
{
uint64_t v___x_1156_; 
v___x_1156_ = lean_uint32_to_uint64(v___y_1148_);
v___y_1137_ = v___y_1150_;
v___y_1138_ = v___y_1147_;
v___y_1139_ = v___y_1149_;
v___y_1140_ = v___x_1156_;
goto v___jp_1136_;
}
}
v___jp_1157_:
{
uint32_t v___x_1159_; uint32_t v_xFraction_1160_; uint32_t v_yFraction_1161_; uint32_t v___x_1162_; uint8_t v___x_1163_; 
v___x_1159_ = 8388607;
v_xFraction_1160_ = lean_uint32_land(v___y_674_, v___x_1159_);
v_yFraction_1161_ = lean_uint32_land(v___y_675_, v___x_1159_);
v___x_1162_ = 0;
v___x_1163_ = lean_uint32_dec_eq(v_ex_1122_, v___x_1162_);
if (v___x_1163_ == 0)
{
uint64_t v___x_1164_; uint64_t v___x_1165_; uint64_t v___x_1166_; 
v___x_1164_ = lean_uint32_to_uint64(v_xFraction_1160_);
v___x_1165_ = 8388608ULL;
v___x_1166_ = lean_uint64_lor(v___x_1164_, v___x_1165_);
v___y_1147_ = v___x_1159_;
v___y_1148_ = v_yFraction_1161_;
v___y_1149_ = v___y_1158_;
v___y_1150_ = v___x_1166_;
goto v___jp_1146_;
}
else
{
uint64_t v___x_1167_; 
v___x_1167_ = lean_uint32_to_uint64(v_xFraction_1160_);
v___y_1147_ = v___x_1159_;
v___y_1148_ = v_yFraction_1161_;
v___y_1149_ = v___y_1158_;
v___y_1150_ = v___x_1167_;
goto v___jp_1146_;
}
}
v___jp_1171_:
{
if (v___y_1173_ == 0)
{
v___y_1158_ = v___x_1170_;
goto v___jp_1157_;
}
else
{
v___y_1158_ = v___y_1172_;
goto v___jp_1157_;
}
}
v___jp_1174_:
{
if (v___y_1175_ == 0)
{
if (v___y_1177_ == 0)
{
v___y_1172_ = v___y_1176_;
v___y_1173_ = v___x_1170_;
goto v___jp_1171_;
}
else
{
v___y_1158_ = v___x_1170_;
goto v___jp_1157_;
}
}
else
{
v___y_1172_ = v___y_1176_;
v___y_1173_ = v___y_1177_;
goto v___jp_1171_;
}
}
v___jp_1178_:
{
uint32_t v___x_1181_; uint32_t v___x_1182_; uint32_t v___x_1183_; uint8_t v___x_1184_; 
v___x_1181_ = 2147483648;
v___x_1182_ = lean_uint32_land(v___y_675_, v___x_1181_);
v___x_1183_ = 0;
v___x_1184_ = lean_uint32_dec_eq(v___x_1182_, v___x_1183_);
if (v___x_1184_ == 0)
{
v___y_1175_ = v___y_1180_;
v___y_1176_ = v___y_1179_;
v___y_1177_ = v___x_1170_;
goto v___jp_1174_;
}
else
{
v___y_1175_ = v___y_1180_;
v___y_1176_ = v___y_1179_;
v___y_1177_ = v___y_1179_;
goto v___jp_1174_;
}
}
v___jp_1185_:
{
if (v___y_1186_ == 0)
{
uint32_t v___x_1187_; uint32_t v___x_1188_; uint32_t v___x_1189_; uint8_t v___x_1190_; 
v___x_1187_ = 2147483648;
v___x_1188_ = lean_uint32_land(v___y_674_, v___x_1187_);
v___x_1189_ = 0;
v___x_1190_ = lean_uint32_dec_eq(v___x_1188_, v___x_1189_);
if (v___x_1190_ == 0)
{
v___y_1179_ = v___y_1186_;
v___y_1180_ = v___x_1170_;
goto v___jp_1178_;
}
else
{
v___y_1179_ = v___y_1186_;
v___y_1180_ = v___y_1186_;
goto v___jp_1178_;
}
}
else
{
lean_object* v___x_1191_; lean_object* v___x_1192_; lean_object* v___x_1193_; uint32_t v___x_1194_; 
v___x_1191_ = lean_uint32_to_nat(v___y_674_);
v___x_1192_ = lean_uint32_to_nat(v___y_675_);
v___x_1193_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1191_, v___x_1192_);
v___x_1194_ = lean_uint32_of_nat(v___x_1193_);
lean_dec(v___x_1193_);
return v___x_1194_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_1209_, lean_object* v___y_1210_){
_start:
{
uint32_t v___y_5839__boxed_1211_; uint32_t v___y_5840__boxed_1212_; uint32_t v_res_1213_; lean_object* v_r_1214_; 
v___y_5839__boxed_1211_ = lean_unbox_uint32(v___y_1209_);
lean_dec(v___y_1209_);
v___y_5840__boxed_1212_ = lean_unbox_uint32(v___y_1210_);
lean_dec(v___y_1210_);
v_res_1213_ = lp_competition_main___lam__3(v___y_5839__boxed_1211_, v___y_5840__boxed_1212_);
v_r_1214_ = lean_box_uint32(v_res_1213_);
return v_r_1214_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1222_; lean_object* v___x_1223_; 
v___x_1222_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1223_ = lean_io_getenv(v___x_1222_);
if (lean_obj_tag(v___x_1223_) == 0)
{
lean_object* v___f_1224_; lean_object* v___f_1225_; lean_object* v___x_1226_; lean_object* v___x_1227_; lean_object* v___x_1228_; 
v___f_1224_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1225_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1226_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1227_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1228_ = lp_competition_Bench_runFull(v___f_1224_, v___f_1225_, v___x_1226_, v___x_1227_);
return v___x_1228_;
}
else
{
lean_object* v___f_1229_; lean_object* v___f_1230_; lean_object* v___x_1231_; lean_object* v___x_1232_; lean_object* v___x_1233_; 
lean_dec_ref_known(v___x_1223_, 1);
v___f_1229_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1230_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1231_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1232_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1233_ = lp_competition_Bench_Suite_run(v___f_1229_, v___f_1230_, v___x_1231_, v___x_1232_);
return v___x_1233_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1234_){
_start:
{
lean_object* v_res_1235_; 
v_res_1235_ = _lean_main();
return v_res_1235_;
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
