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
float lean_float32_add(float, float);
uint8_t lean_float32_beq(float, float);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_float32_to_bits(float);
float lean_float32_of_bits(uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
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
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_runFull(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_main___lam__0(uint32_t, uint32_t);
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
LEAN_EXPORT lean_object* lp_competition_main___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
float v___y_4_; float v___y_5_; float v___y_16_; uint8_t v___y_17_; float v___y_32_; uint8_t v___y_42_; uint32_t v___x_56_; uint32_t v_a_57_; uint32_t v___x_58_; uint32_t v___x_59_; uint32_t v___x_60_; uint8_t v___x_61_; 
v___x_56_ = 2147483647;
v_a_57_ = lean_uint32_land(v___y_1_, v___x_56_);
v___x_58_ = 201326591;
v___x_59_ = 1;
v___x_60_ = lean_uint32_sub(v_a_57_, v___x_59_);
v___x_61_ = lean_uint32_dec_le(v___x_58_, v___x_60_);
if (v___x_61_ == 0)
{
v___y_42_ = v___x_61_;
goto v___jp_41_;
}
else
{
uint32_t v___x_62_; uint8_t v___x_63_; 
v___x_62_ = 2139095040;
v___x_63_ = lean_uint32_dec_lt(v_a_57_, v___x_62_);
v___y_42_ = v___x_63_;
goto v___jp_41_;
}
v___jp_3_:
{
float v_result_6_; uint8_t v___x_7_; 
v_result_6_ = lean_float32_add(v___y_4_, v___y_5_);
v___x_7_ = lean_float32_beq(v_result_6_, v_result_6_);
if (v___x_7_ == 0)
{
lean_object* v___x_8_; lean_object* v___x_9_; lean_object* v___x_10_; uint32_t v___x_11_; lean_object* v___x_12_; 
v___x_8_ = lean_uint32_to_nat(v___y_1_);
v___x_9_ = lean_uint32_to_nat(v___y_2_);
v___x_10_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_8_, v___x_9_);
v___x_11_ = lean_uint32_of_nat(v___x_10_);
lean_dec(v___x_10_);
v___x_12_ = lean_box_uint32(v___x_11_);
return v___x_12_;
}
else
{
uint32_t v___x_13_; lean_object* v___x_14_; 
v___x_13_ = lean_float32_to_bits(v_result_6_);
v___x_14_ = lean_box_uint32(v___x_13_);
return v___x_14_;
}
}
v___jp_15_:
{
if (v___y_17_ == 0)
{
float v___x_18_; 
v___x_18_ = lean_float32_of_bits(v___y_2_);
v___y_4_ = v___y_16_;
v___y_5_ = v___x_18_;
goto v___jp_3_;
}
else
{
uint32_t v___x_19_; uint32_t v___x_20_; uint32_t v___x_21_; uint32_t v___x_22_; float v___x_23_; lean_object* v___x_24_; uint32_t v___x_25_; uint32_t v___x_26_; lean_object* v___x_27_; lean_object* v___x_28_; float v___x_29_; float v___x_30_; 
v___x_19_ = 8388607;
v___x_20_ = lean_uint32_land(v___y_2_, v___x_19_);
v___x_21_ = 8388608;
v___x_22_ = lean_uint32_lor(v___x_20_, v___x_21_);
v___x_23_ = lean_uint32_to_float32(v___x_22_);
v___x_24_ = lp_competition_R2W01b_scaleTable;
v___x_25_ = 23;
v___x_26_ = lean_uint32_shift_right(v___y_2_, v___x_25_);
v___x_27_ = lean_uint32_to_nat(v___x_26_);
v___x_28_ = lean_array_fget_borrowed(v___x_24_, v___x_27_);
lean_dec(v___x_27_);
v___x_29_ = lean_unbox_float32(v___x_28_);
v___x_30_ = lean_float32_mul(v___x_23_, v___x_29_);
v___y_4_ = v___y_16_;
v___y_5_ = v___x_30_;
goto v___jp_3_;
}
}
v___jp_31_:
{
uint32_t v___x_33_; uint32_t v_a_34_; uint32_t v___x_35_; uint32_t v___x_36_; uint32_t v___x_37_; uint8_t v___x_38_; 
v___x_33_ = 2147483647;
v_a_34_ = lean_uint32_land(v___y_2_, v___x_33_);
v___x_35_ = 201326591;
v___x_36_ = 1;
v___x_37_ = lean_uint32_sub(v_a_34_, v___x_36_);
v___x_38_ = lean_uint32_dec_le(v___x_35_, v___x_37_);
if (v___x_38_ == 0)
{
v___y_16_ = v___y_32_;
v___y_17_ = v___x_38_;
goto v___jp_15_;
}
else
{
uint32_t v___x_39_; uint8_t v___x_40_; 
v___x_39_ = 2139095040;
v___x_40_ = lean_uint32_dec_lt(v_a_34_, v___x_39_);
v___y_16_ = v___y_32_;
v___y_17_ = v___x_40_;
goto v___jp_15_;
}
}
v___jp_41_:
{
if (v___y_42_ == 0)
{
float v___x_43_; 
v___x_43_ = lean_float32_of_bits(v___y_1_);
v___y_32_ = v___x_43_;
goto v___jp_31_;
}
else
{
uint32_t v___x_44_; uint32_t v___x_45_; uint32_t v___x_46_; uint32_t v___x_47_; float v___x_48_; lean_object* v___x_49_; uint32_t v___x_50_; uint32_t v___x_51_; lean_object* v___x_52_; lean_object* v___x_53_; float v___x_54_; float v___x_55_; 
v___x_44_ = 8388607;
v___x_45_ = lean_uint32_land(v___y_1_, v___x_44_);
v___x_46_ = 8388608;
v___x_47_ = lean_uint32_lor(v___x_45_, v___x_46_);
v___x_48_ = lean_uint32_to_float32(v___x_47_);
v___x_49_ = lp_competition_R2W01b_scaleTable;
v___x_50_ = 23;
v___x_51_ = lean_uint32_shift_right(v___y_1_, v___x_50_);
v___x_52_ = lean_uint32_to_nat(v___x_51_);
v___x_53_ = lean_array_fget_borrowed(v___x_49_, v___x_52_);
lean_dec(v___x_52_);
v___x_54_ = lean_unbox_float32(v___x_53_);
v___x_55_ = lean_float32_mul(v___x_48_, v___x_54_);
v___y_32_ = v___x_55_;
goto v___jp_31_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_64_, lean_object* v___y_65_){
_start:
{
uint32_t v___y_3737__boxed_66_; uint32_t v___y_3738__boxed_67_; lean_object* v_res_68_; 
v___y_3737__boxed_66_ = lean_unbox_uint32(v___y_64_);
lean_dec(v___y_64_);
v___y_3738__boxed_67_ = lean_unbox_uint32(v___y_65_);
lean_dec(v___y_65_);
v_res_68_ = lp_competition_main___lam__0(v___y_3737__boxed_66_, v___y_3738__boxed_67_);
return v_res_68_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_69_, uint32_t v___y_70_){
_start:
{
uint32_t v___y_72_; uint32_t v___y_76_; uint32_t v___y_80_; uint32_t v___y_81_; uint32_t v___y_82_; uint32_t v___y_86_; uint8_t v___y_87_; uint64_t v___y_88_; uint64_t v___y_89_; uint32_t v___y_101_; uint32_t v___y_102_; uint32_t v___y_103_; uint32_t v___y_107_; uint64_t v___y_108_; uint8_t v___y_109_; uint64_t v___y_110_; uint32_t v___x_121_; uint32_t v___x_122_; uint32_t v___x_123_; uint32_t v___y_125_; uint32_t v___y_126_; uint32_t v___y_127_; uint32_t v___y_128_; uint32_t v___y_135_; uint32_t v___y_136_; uint8_t v___y_137_; uint32_t v___y_138_; uint32_t v___y_142_; uint64_t v___y_143_; uint64_t v___y_144_; uint8_t v___y_145_; uint64_t v___y_146_; uint8_t v___y_156_; uint32_t v___y_157_; uint8_t v___y_158_; uint64_t v___y_159_; uint64_t v___y_160_; uint64_t v___y_161_; uint32_t v___y_168_; uint64_t v___y_169_; uint8_t v___y_170_; uint64_t v___y_171_; uint64_t v___y_172_; uint32_t v___y_178_; uint64_t v___y_179_; uint64_t v___y_180_; uint8_t v___y_181_; uint64_t v___y_182_; uint64_t v___y_183_; uint32_t v___y_238_; uint64_t v___y_239_; uint64_t v___y_240_; uint8_t v___y_241_; uint64_t v___y_242_; uint64_t v___y_243_; uint64_t v___y_244_; uint32_t v___y_250_; uint64_t v___y_251_; uint64_t v___y_252_; uint64_t v___y_253_; uint64_t v___y_254_; uint8_t v___y_255_; uint64_t v___y_256_; uint64_t v___y_257_; uint64_t v___y_258_; uint32_t v___y_263_; uint64_t v___y_264_; uint64_t v___y_265_; uint8_t v___y_266_; uint64_t v___y_267_; uint64_t v___y_268_; uint64_t v___y_269_; uint32_t v___y_274_; uint64_t v___y_275_; uint64_t v___y_276_; uint64_t v___y_277_; uint64_t v___y_278_; uint8_t v___y_279_; uint64_t v___y_280_; uint64_t v___y_281_; uint64_t v___y_282_; uint32_t v___y_287_; uint64_t v___y_288_; uint64_t v___y_289_; uint64_t v___y_290_; uint8_t v___y_291_; uint64_t v___y_292_; uint64_t v___y_293_; uint32_t v___y_298_; uint64_t v___y_299_; uint64_t v___y_300_; uint64_t v___y_301_; uint64_t v___y_302_; uint64_t v___y_303_; uint8_t v___y_304_; uint64_t v___y_305_; uint64_t v___y_306_; uint32_t v___y_311_; uint64_t v___y_312_; uint64_t v___y_313_; uint8_t v___y_314_; uint64_t v___y_315_; uint64_t v___y_316_; uint64_t v___y_317_; uint32_t v___y_322_; uint64_t v___y_323_; uint64_t v___y_324_; uint64_t v___y_325_; uint64_t v___y_326_; uint8_t v___y_327_; uint64_t v___y_328_; uint64_t v___y_329_; uint64_t v___y_330_; uint32_t v___y_335_; uint64_t v___y_336_; uint64_t v___y_337_; uint8_t v___y_338_; uint64_t v___y_339_; uint64_t v___y_340_; uint64_t v___y_341_; uint32_t v___y_346_; uint64_t v___y_347_; uint64_t v___y_348_; uint64_t v___y_349_; uint8_t v___y_350_; uint64_t v___y_351_; uint64_t v___y_352_; uint32_t v___y_356_; uint64_t v___y_357_; uint64_t v___y_358_; uint8_t v___y_359_; uint32_t v___y_368_; uint64_t v___y_369_; uint64_t v___y_370_; uint8_t v___y_371_; uint64_t v___y_372_; uint64_t v___y_373_; uint32_t v_ex_406_; uint32_t v___x_407_; uint32_t v_ey_408_; uint32_t v___y_410_; uint64_t v___y_411_; uint8_t v___y_412_; uint64_t v___y_413_; uint64_t v___y_414_; uint32_t v___y_421_; uint64_t v___y_422_; uint8_t v___y_423_; uint64_t v___y_424_; uint32_t v___y_431_; uint8_t v___y_432_; uint32_t v___y_433_; uint64_t v___y_434_; uint8_t v___y_442_; uint32_t v___x_452_; uint32_t v___x_453_; uint8_t v___x_454_; uint8_t v___y_456_; uint8_t v___y_457_; uint8_t v___y_459_; uint8_t v___y_460_; uint8_t v___y_461_; uint8_t v___y_463_; uint8_t v___y_464_; uint8_t v___y_470_; 
v___x_121_ = 23;
v___x_122_ = lean_uint32_shift_right(v___y_69_, v___x_121_);
v___x_123_ = 255;
v_ex_406_ = lean_uint32_land(v___x_122_, v___x_123_);
v___x_407_ = lean_uint32_shift_right(v___y_70_, v___x_121_);
v_ey_408_ = lean_uint32_land(v___x_407_, v___x_123_);
v___x_452_ = lean_uint32_add(v_ex_406_, v_ey_408_);
v___x_453_ = 128;
v___x_454_ = lean_uint32_dec_lt(v___x_452_, v___x_453_);
if (v___x_454_ == 0)
{
float v___x_479_; float v___x_480_; float v_result_481_; uint8_t v___x_482_; 
v___x_479_ = lean_float32_of_bits(v___y_69_);
v___x_480_ = lean_float32_of_bits(v___y_70_);
v_result_481_ = lean_float32_mul(v___x_479_, v___x_480_);
v___x_482_ = lean_float32_beq(v_result_481_, v_result_481_);
if (v___x_482_ == 0)
{
uint32_t v___x_483_; 
v___x_483_ = lp_competition_Submission_FastMul_mul(v___y_69_, v___y_70_);
return v___x_483_;
}
else
{
uint32_t v___x_484_; 
v___x_484_ = lean_float32_to_bits(v_result_481_);
return v___x_484_;
}
}
else
{
uint32_t v___x_485_; uint32_t v___x_486_; uint32_t v___x_487_; uint8_t v___x_488_; 
v___x_485_ = 4278190080;
v___x_486_ = 1;
v___x_487_ = lean_uint32_shift_left(v___y_69_, v___x_486_);
v___x_488_ = lean_uint32_dec_le(v___x_485_, v___x_487_);
if (v___x_488_ == 0)
{
uint32_t v___x_489_; uint8_t v___x_490_; 
v___x_489_ = lean_uint32_shift_left(v___y_70_, v___x_486_);
v___x_490_ = lean_uint32_dec_le(v___x_485_, v___x_489_);
v___y_470_ = v___x_490_;
goto v___jp_469_;
}
else
{
v___y_470_ = v___x_488_;
goto v___jp_469_;
}
}
v___jp_71_:
{
uint32_t v___x_73_; uint32_t v___x_74_; 
v___x_73_ = 8388608;
v___x_74_ = lean_uint32_lor(v___y_72_, v___x_73_);
return v___x_74_;
}
v___jp_75_:
{
uint32_t v___x_77_; uint32_t v___x_78_; 
v___x_77_ = 8388608;
v___x_78_ = lean_uint32_lor(v___y_76_, v___x_77_);
return v___x_78_;
}
v___jp_79_:
{
uint32_t v___x_83_; uint32_t v___x_84_; 
v___x_83_ = lean_uint32_land(v___y_81_, v___y_80_);
v___x_84_ = lean_uint32_lor(v___y_82_, v___x_83_);
return v___x_84_;
}
v___jp_85_:
{
uint8_t v___x_90_; 
v___x_90_ = lean_uint64_dec_eq(v___y_89_, v___y_88_);
if (v___x_90_ == 0)
{
uint64_t v___x_91_; uint8_t v___x_92_; 
v___x_91_ = 8388608ULL;
v___x_92_ = lean_uint64_dec_eq(v___y_89_, v___x_91_);
if (v___x_92_ == 0)
{
uint32_t v___x_93_; 
v___x_93_ = lean_uint64_to_uint32(v___y_89_);
if (v___y_87_ == 0)
{
uint32_t v___x_94_; 
v___x_94_ = 0;
v___y_80_ = v___y_86_;
v___y_81_ = v___x_93_;
v___y_82_ = v___x_94_;
goto v___jp_79_;
}
else
{
uint32_t v___x_95_; 
v___x_95_ = 2147483648;
v___y_80_ = v___y_86_;
v___y_81_ = v___x_93_;
v___y_82_ = v___x_95_;
goto v___jp_79_;
}
}
else
{
if (v___y_87_ == 0)
{
uint32_t v___x_96_; 
v___x_96_ = 0;
v___y_76_ = v___x_96_;
goto v___jp_75_;
}
else
{
uint32_t v___x_97_; 
v___x_97_ = 2147483648;
v___y_76_ = v___x_97_;
goto v___jp_75_;
}
}
}
else
{
if (v___y_87_ == 0)
{
uint32_t v___x_98_; 
v___x_98_ = 0;
return v___x_98_;
}
else
{
uint32_t v___x_99_; 
v___x_99_ = 2147483648;
return v___x_99_;
}
}
}
v___jp_100_:
{
uint32_t v___x_104_; uint32_t v___x_105_; 
v___x_104_ = lean_uint32_land(v___y_102_, v___y_101_);
v___x_105_ = lean_uint32_lor(v___y_103_, v___x_104_);
return v___x_105_;
}
v___jp_106_:
{
uint8_t v___x_111_; 
v___x_111_ = lean_uint64_dec_eq(v___y_110_, v___y_108_);
if (v___x_111_ == 0)
{
uint64_t v___x_112_; uint8_t v___x_113_; 
v___x_112_ = 8388608ULL;
v___x_113_ = lean_uint64_dec_eq(v___y_110_, v___x_112_);
if (v___x_113_ == 0)
{
uint32_t v___x_114_; 
v___x_114_ = lean_uint64_to_uint32(v___y_110_);
if (v___y_109_ == 0)
{
uint32_t v___x_115_; 
v___x_115_ = 0;
v___y_101_ = v___y_107_;
v___y_102_ = v___x_114_;
v___y_103_ = v___x_115_;
goto v___jp_100_;
}
else
{
uint32_t v___x_116_; 
v___x_116_ = 2147483648;
v___y_101_ = v___y_107_;
v___y_102_ = v___x_114_;
v___y_103_ = v___x_116_;
goto v___jp_100_;
}
}
else
{
if (v___y_109_ == 0)
{
uint32_t v___x_117_; 
v___x_117_ = 0;
v___y_72_ = v___x_117_;
goto v___jp_71_;
}
else
{
uint32_t v___x_118_; 
v___x_118_ = 2147483648;
v___y_72_ = v___x_118_;
goto v___jp_71_;
}
}
}
else
{
if (v___y_109_ == 0)
{
uint32_t v___x_119_; 
v___x_119_ = 0;
return v___x_119_;
}
else
{
uint32_t v___x_120_; 
v___x_120_ = 2147483648;
return v___x_120_;
}
}
}
v___jp_124_:
{
uint32_t v___x_129_; uint32_t v___x_130_; uint32_t v___x_131_; uint32_t v___x_132_; uint32_t v___x_133_; 
v___x_129_ = lean_uint32_land(v___y_126_, v___x_123_);
v___x_130_ = lean_uint32_shift_left(v___x_129_, v___x_121_);
v___x_131_ = lean_uint32_lor(v___y_128_, v___x_130_);
v___x_132_ = lean_uint32_land(v___y_127_, v___y_125_);
v___x_133_ = lean_uint32_lor(v___x_131_, v___x_132_);
return v___x_133_;
}
v___jp_134_:
{
if (v___y_137_ == 0)
{
uint32_t v___x_139_; 
v___x_139_ = 0;
v___y_125_ = v___y_135_;
v___y_126_ = v___y_136_;
v___y_127_ = v___y_138_;
v___y_128_ = v___x_139_;
goto v___jp_124_;
}
else
{
uint32_t v___x_140_; 
v___x_140_ = 2147483648;
v___y_125_ = v___y_135_;
v___y_126_ = v___y_136_;
v___y_127_ = v___y_138_;
v___y_128_ = v___x_140_;
goto v___jp_124_;
}
}
v___jp_141_:
{
uint64_t v___x_147_; uint64_t v_encodedExponent_148_; uint32_t v___x_149_; uint64_t v___x_150_; uint8_t v___x_151_; 
v___x_147_ = 171ULL;
v_encodedExponent_148_ = lean_uint64_sub(v___y_143_, v___x_147_);
v___x_149_ = lean_uint64_to_uint32(v_encodedExponent_148_);
v___x_150_ = 8388608ULL;
v___x_151_ = lean_uint64_dec_lt(v___y_146_, v___x_150_);
if (v___x_151_ == 0)
{
uint64_t v___x_152_; uint32_t v___x_153_; 
v___x_152_ = lean_uint64_sub(v___y_146_, v___x_150_);
v___x_153_ = lean_uint64_to_uint32(v___x_152_);
v___y_135_ = v___y_142_;
v___y_136_ = v___x_149_;
v___y_137_ = v___y_145_;
v___y_138_ = v___x_153_;
goto v___jp_134_;
}
else
{
uint32_t v___x_154_; 
v___x_154_ = lean_uint64_to_uint32(v___y_144_);
v___y_135_ = v___y_142_;
v___y_136_ = v___x_149_;
v___y_137_ = v___y_145_;
v___y_138_ = v___x_154_;
goto v___jp_134_;
}
}
v___jp_155_:
{
uint64_t v___x_162_; uint8_t v___x_163_; 
v___x_162_ = 425ULL;
v___x_163_ = lean_uint64_dec_lt(v___x_162_, v___y_161_);
if (v___x_163_ == 0)
{
if (v___y_156_ == 0)
{
v___y_142_ = v___y_157_;
v___y_143_ = v___y_161_;
v___y_144_ = v___y_159_;
v___y_145_ = v___y_158_;
v___y_146_ = v___y_160_;
goto v___jp_141_;
}
else
{
uint64_t v___x_164_; 
v___x_164_ = 8388608ULL;
v___y_142_ = v___y_157_;
v___y_143_ = v___y_161_;
v___y_144_ = v___y_159_;
v___y_145_ = v___y_158_;
v___y_146_ = v___x_164_;
goto v___jp_141_;
}
}
else
{
if (v___y_158_ == 0)
{
uint32_t v___x_165_; 
v___x_165_ = 2139095040;
return v___x_165_;
}
else
{
uint32_t v___x_166_; 
v___x_166_ = 4286578688;
return v___x_166_;
}
}
}
v___jp_167_:
{
uint64_t v___x_173_; uint8_t v_carry_174_; 
v___x_173_ = 16777216ULL;
v_carry_174_ = lean_uint64_dec_eq(v___y_172_, v___x_173_);
if (v_carry_174_ == 0)
{
v___y_156_ = v_carry_174_;
v___y_157_ = v___y_168_;
v___y_158_ = v___y_170_;
v___y_159_ = v___y_169_;
v___y_160_ = v___y_172_;
v___y_161_ = v___y_171_;
goto v___jp_155_;
}
else
{
uint64_t v___x_175_; uint64_t v___x_176_; 
v___x_175_ = 1ULL;
v___x_176_ = lean_uint64_add(v___y_171_, v___x_175_);
v___y_156_ = v_carry_174_;
v___y_157_ = v___y_168_;
v___y_158_ = v___y_170_;
v___y_159_ = v___y_169_;
v___y_160_ = v___y_172_;
v___y_161_ = v___x_176_;
goto v___jp_155_;
}
}
v___jp_177_:
{
uint64_t v_position_184_; uint64_t v___x_185_; uint8_t v___x_186_; 
v_position_184_ = lean_uint64_add(v___y_183_, v___y_180_);
v___x_185_ = 172ULL;
v___x_186_ = lean_uint64_dec_lt(v_position_184_, v___x_185_);
if (v___x_186_ == 0)
{
uint64_t v___x_187_; uint8_t v___x_188_; 
v___x_187_ = 23ULL;
v___x_188_ = lean_uint64_dec_lt(v___y_183_, v___x_187_);
if (v___x_188_ == 0)
{
uint64_t v___x_189_; uint8_t v___x_190_; 
v___x_189_ = lean_uint64_sub(v___y_183_, v___x_187_);
v___x_190_ = lean_uint64_dec_eq(v___x_189_, v___y_182_);
if (v___x_190_ == 0)
{
uint64_t v___x_191_; uint8_t v___x_192_; 
v___x_191_ = 64ULL;
v___x_192_ = lean_uint64_dec_lt(v___x_189_, v___x_191_);
if (v___x_192_ == 0)
{
uint8_t v___x_193_; 
v___x_193_ = lean_uint64_dec_eq(v___x_189_, v___x_191_);
if (v___x_193_ == 0)
{
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v___y_182_;
goto v___jp_167_;
}
else
{
uint64_t v___x_194_; uint8_t v___x_195_; 
v___x_194_ = 9223372036854775808ULL;
v___x_195_ = lean_uint64_dec_lt(v___x_194_, v___y_179_);
if (v___x_195_ == 0)
{
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v___y_182_;
goto v___jp_167_;
}
else
{
uint64_t v___x_196_; 
v___x_196_ = 1ULL;
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v___x_196_;
goto v___jp_167_;
}
}
}
else
{
uint64_t v_quotient_197_; uint64_t v___x_198_; uint64_t v___x_199_; uint64_t v___x_200_; uint64_t v_remainder_201_; uint64_t v___x_202_; uint64_t v_half_203_; uint8_t v___x_204_; 
v_quotient_197_ = lean_uint64_shift_right(v___y_179_, v___x_189_);
v___x_198_ = 1ULL;
v___x_199_ = lean_uint64_shift_left(v___x_198_, v___x_189_);
v___x_200_ = lean_uint64_sub(v___x_199_, v___x_198_);
v_remainder_201_ = lean_uint64_land(v___y_179_, v___x_200_);
v___x_202_ = lean_uint64_sub(v___x_189_, v___x_198_);
v_half_203_ = lean_uint64_shift_left(v___x_198_, v___x_202_);
v___x_204_ = lean_uint64_dec_lt(v_remainder_201_, v_half_203_);
if (v___x_204_ == 0)
{
uint8_t v___x_205_; 
v___x_205_ = lean_uint64_dec_lt(v_half_203_, v_remainder_201_);
if (v___x_205_ == 0)
{
uint64_t v___x_206_; uint8_t v___x_207_; 
v___x_206_ = lean_uint64_land(v_quotient_197_, v___x_198_);
v___x_207_ = lean_uint64_dec_eq(v___x_206_, v___y_182_);
if (v___x_207_ == 0)
{
uint64_t v___x_208_; 
v___x_208_ = lean_uint64_add(v_quotient_197_, v___x_198_);
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v___x_208_;
goto v___jp_167_;
}
else
{
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v_quotient_197_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_209_; 
v___x_209_ = lean_uint64_add(v_quotient_197_, v___x_198_);
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v___x_209_;
goto v___jp_167_;
}
}
else
{
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v_quotient_197_;
goto v___jp_167_;
}
}
}
else
{
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v___y_179_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_210_; uint64_t v___x_211_; 
v___x_210_ = lean_uint64_sub(v___x_187_, v___y_183_);
v___x_211_ = lean_uint64_shift_left(v___y_179_, v___x_210_);
v___y_168_ = v___y_178_;
v___y_169_ = v___y_182_;
v___y_170_ = v___y_181_;
v___y_171_ = v_position_184_;
v___y_172_ = v___x_211_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_212_; uint8_t v___x_213_; 
v___x_212_ = 149ULL;
v___x_213_ = lean_uint64_dec_lt(v___y_180_, v___x_212_);
if (v___x_213_ == 0)
{
uint64_t v___x_214_; uint64_t v___x_215_; 
v___x_214_ = lean_uint64_sub(v___y_180_, v___x_212_);
v___x_215_ = lean_uint64_shift_left(v___y_179_, v___x_214_);
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v___x_215_;
goto v___jp_85_;
}
else
{
uint64_t v___x_216_; uint8_t v___x_217_; 
v___x_216_ = lean_uint64_sub(v___x_212_, v___y_180_);
v___x_217_ = lean_uint64_dec_eq(v___x_216_, v___y_182_);
if (v___x_217_ == 0)
{
uint64_t v___x_218_; uint8_t v___x_219_; 
v___x_218_ = 64ULL;
v___x_219_ = lean_uint64_dec_lt(v___x_216_, v___x_218_);
if (v___x_219_ == 0)
{
uint8_t v___x_220_; 
v___x_220_ = lean_uint64_dec_eq(v___x_216_, v___x_218_);
if (v___x_220_ == 0)
{
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v___y_182_;
goto v___jp_85_;
}
else
{
uint64_t v___x_221_; uint8_t v___x_222_; 
v___x_221_ = 9223372036854775808ULL;
v___x_222_ = lean_uint64_dec_lt(v___x_221_, v___y_179_);
if (v___x_222_ == 0)
{
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v___y_182_;
goto v___jp_85_;
}
else
{
uint64_t v___x_223_; 
v___x_223_ = 1ULL;
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v___x_223_;
goto v___jp_85_;
}
}
}
else
{
uint64_t v_quotient_224_; uint64_t v___x_225_; uint64_t v___x_226_; uint64_t v___x_227_; uint64_t v_remainder_228_; uint64_t v___x_229_; uint64_t v_half_230_; uint8_t v___x_231_; 
v_quotient_224_ = lean_uint64_shift_right(v___y_179_, v___x_216_);
v___x_225_ = 1ULL;
v___x_226_ = lean_uint64_shift_left(v___x_225_, v___x_216_);
v___x_227_ = lean_uint64_sub(v___x_226_, v___x_225_);
v_remainder_228_ = lean_uint64_land(v___y_179_, v___x_227_);
v___x_229_ = lean_uint64_sub(v___x_216_, v___x_225_);
v_half_230_ = lean_uint64_shift_left(v___x_225_, v___x_229_);
v___x_231_ = lean_uint64_dec_lt(v_remainder_228_, v_half_230_);
if (v___x_231_ == 0)
{
uint8_t v___x_232_; 
v___x_232_ = lean_uint64_dec_lt(v_half_230_, v_remainder_228_);
if (v___x_232_ == 0)
{
uint64_t v___x_233_; uint8_t v___x_234_; 
v___x_233_ = lean_uint64_land(v_quotient_224_, v___x_225_);
v___x_234_ = lean_uint64_dec_eq(v___x_233_, v___y_182_);
if (v___x_234_ == 0)
{
uint64_t v___x_235_; 
v___x_235_ = lean_uint64_add(v_quotient_224_, v___x_225_);
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v___x_235_;
goto v___jp_85_;
}
else
{
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v_quotient_224_;
goto v___jp_85_;
}
}
else
{
uint64_t v___x_236_; 
v___x_236_ = lean_uint64_add(v_quotient_224_, v___x_225_);
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v___x_236_;
goto v___jp_85_;
}
}
else
{
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v_quotient_224_;
goto v___jp_85_;
}
}
}
else
{
v___y_86_ = v___y_178_;
v___y_87_ = v___y_181_;
v___y_88_ = v___y_182_;
v___y_89_ = v___y_179_;
goto v___jp_85_;
}
}
}
}
v___jp_237_:
{
uint64_t v___x_245_; uint64_t v___x_246_; uint8_t v___x_247_; 
v___x_245_ = 1ULL;
v___x_246_ = lean_uint64_shift_right(v___y_243_, v___x_245_);
v___x_247_ = lean_uint64_dec_eq(v___x_246_, v___y_242_);
if (v___x_247_ == 0)
{
uint64_t v___x_248_; 
v___x_248_ = lean_uint64_add(v___y_244_, v___x_245_);
v___y_178_ = v___y_238_;
v___y_179_ = v___y_239_;
v___y_180_ = v___y_240_;
v___y_181_ = v___y_241_;
v___y_182_ = v___y_242_;
v___y_183_ = v___x_248_;
goto v___jp_177_;
}
else
{
v___y_178_ = v___y_238_;
v___y_179_ = v___y_239_;
v___y_180_ = v___y_240_;
v___y_181_ = v___y_241_;
v___y_182_ = v___y_242_;
v___y_183_ = v___y_244_;
goto v___jp_177_;
}
}
v___jp_249_:
{
uint64_t v___x_259_; uint8_t v___x_260_; 
v___x_259_ = lean_uint64_shift_right(v___y_256_, v___y_257_);
v___x_260_ = lean_uint64_dec_eq(v___x_259_, v___y_254_);
if (v___x_260_ == 0)
{
uint64_t v___x_261_; 
v___x_261_ = lean_uint64_add(v___y_252_, v___y_257_);
v___y_238_ = v___y_250_;
v___y_239_ = v___y_251_;
v___y_240_ = v___y_253_;
v___y_241_ = v___y_255_;
v___y_242_ = v___y_254_;
v___y_243_ = v___y_258_;
v___y_244_ = v___x_261_;
goto v___jp_237_;
}
else
{
v___y_238_ = v___y_250_;
v___y_239_ = v___y_251_;
v___y_240_ = v___y_253_;
v___y_241_ = v___y_255_;
v___y_242_ = v___y_254_;
v___y_243_ = v___y_258_;
v___y_244_ = v___y_252_;
goto v___jp_237_;
}
}
v___jp_262_:
{
uint64_t v___x_270_; uint64_t v___x_271_; uint8_t v___x_272_; 
v___x_270_ = 2ULL;
v___x_271_ = lean_uint64_shift_right(v___y_268_, v___x_270_);
v___x_272_ = lean_uint64_dec_eq(v___x_271_, v___y_267_);
if (v___x_272_ == 0)
{
v___y_250_ = v___y_263_;
v___y_251_ = v___y_264_;
v___y_252_ = v___y_269_;
v___y_253_ = v___y_265_;
v___y_254_ = v___y_267_;
v___y_255_ = v___y_266_;
v___y_256_ = v___y_268_;
v___y_257_ = v___x_270_;
v___y_258_ = v___x_271_;
goto v___jp_249_;
}
else
{
v___y_250_ = v___y_263_;
v___y_251_ = v___y_264_;
v___y_252_ = v___y_269_;
v___y_253_ = v___y_265_;
v___y_254_ = v___y_267_;
v___y_255_ = v___y_266_;
v___y_256_ = v___y_268_;
v___y_257_ = v___x_270_;
v___y_258_ = v___y_268_;
goto v___jp_249_;
}
}
v___jp_273_:
{
uint64_t v___x_283_; uint8_t v___x_284_; 
v___x_283_ = lean_uint64_shift_right(v___y_276_, v___y_280_);
v___x_284_ = lean_uint64_dec_eq(v___x_283_, v___y_278_);
if (v___x_284_ == 0)
{
uint64_t v___x_285_; 
v___x_285_ = lean_uint64_add(v___y_281_, v___y_280_);
v___y_263_ = v___y_274_;
v___y_264_ = v___y_275_;
v___y_265_ = v___y_277_;
v___y_266_ = v___y_279_;
v___y_267_ = v___y_278_;
v___y_268_ = v___y_282_;
v___y_269_ = v___x_285_;
goto v___jp_262_;
}
else
{
v___y_263_ = v___y_274_;
v___y_264_ = v___y_275_;
v___y_265_ = v___y_277_;
v___y_266_ = v___y_279_;
v___y_267_ = v___y_278_;
v___y_268_ = v___y_282_;
v___y_269_ = v___y_281_;
goto v___jp_262_;
}
}
v___jp_286_:
{
uint64_t v___x_294_; uint64_t v___x_295_; uint8_t v___x_296_; 
v___x_294_ = 4ULL;
v___x_295_ = lean_uint64_shift_right(v___y_289_, v___x_294_);
v___x_296_ = lean_uint64_dec_eq(v___x_295_, v___y_292_);
if (v___x_296_ == 0)
{
v___y_274_ = v___y_287_;
v___y_275_ = v___y_288_;
v___y_276_ = v___y_289_;
v___y_277_ = v___y_290_;
v___y_278_ = v___y_292_;
v___y_279_ = v___y_291_;
v___y_280_ = v___x_294_;
v___y_281_ = v___y_293_;
v___y_282_ = v___x_295_;
goto v___jp_273_;
}
else
{
v___y_274_ = v___y_287_;
v___y_275_ = v___y_288_;
v___y_276_ = v___y_289_;
v___y_277_ = v___y_290_;
v___y_278_ = v___y_292_;
v___y_279_ = v___y_291_;
v___y_280_ = v___x_294_;
v___y_281_ = v___y_293_;
v___y_282_ = v___y_289_;
goto v___jp_273_;
}
}
v___jp_297_:
{
uint64_t v___x_307_; uint8_t v___x_308_; 
v___x_307_ = lean_uint64_shift_right(v___y_305_, v___y_301_);
v___x_308_ = lean_uint64_dec_eq(v___x_307_, v___y_303_);
if (v___x_308_ == 0)
{
uint64_t v___x_309_; 
v___x_309_ = lean_uint64_add(v___y_299_, v___y_301_);
v___y_287_ = v___y_298_;
v___y_288_ = v___y_300_;
v___y_289_ = v___y_306_;
v___y_290_ = v___y_302_;
v___y_291_ = v___y_304_;
v___y_292_ = v___y_303_;
v___y_293_ = v___x_309_;
goto v___jp_286_;
}
else
{
v___y_287_ = v___y_298_;
v___y_288_ = v___y_300_;
v___y_289_ = v___y_306_;
v___y_290_ = v___y_302_;
v___y_291_ = v___y_304_;
v___y_292_ = v___y_303_;
v___y_293_ = v___y_299_;
goto v___jp_286_;
}
}
v___jp_310_:
{
uint64_t v___x_318_; uint64_t v___x_319_; uint8_t v___x_320_; 
v___x_318_ = 8ULL;
v___x_319_ = lean_uint64_shift_right(v___y_316_, v___x_318_);
v___x_320_ = lean_uint64_dec_eq(v___x_319_, v___y_315_);
if (v___x_320_ == 0)
{
v___y_298_ = v___y_311_;
v___y_299_ = v___y_317_;
v___y_300_ = v___y_312_;
v___y_301_ = v___x_318_;
v___y_302_ = v___y_313_;
v___y_303_ = v___y_315_;
v___y_304_ = v___y_314_;
v___y_305_ = v___y_316_;
v___y_306_ = v___x_319_;
goto v___jp_297_;
}
else
{
v___y_298_ = v___y_311_;
v___y_299_ = v___y_317_;
v___y_300_ = v___y_312_;
v___y_301_ = v___x_318_;
v___y_302_ = v___y_313_;
v___y_303_ = v___y_315_;
v___y_304_ = v___y_314_;
v___y_305_ = v___y_316_;
v___y_306_ = v___y_316_;
goto v___jp_297_;
}
}
v___jp_321_:
{
uint64_t v___x_331_; uint8_t v___x_332_; 
v___x_331_ = lean_uint64_shift_right(v___y_328_, v___y_329_);
v___x_332_ = lean_uint64_dec_eq(v___x_331_, v___y_326_);
if (v___x_332_ == 0)
{
uint64_t v___x_333_; 
v___x_333_ = lean_uint64_add(v___y_324_, v___y_329_);
v___y_311_ = v___y_322_;
v___y_312_ = v___y_323_;
v___y_313_ = v___y_325_;
v___y_314_ = v___y_327_;
v___y_315_ = v___y_326_;
v___y_316_ = v___y_330_;
v___y_317_ = v___x_333_;
goto v___jp_310_;
}
else
{
v___y_311_ = v___y_322_;
v___y_312_ = v___y_323_;
v___y_313_ = v___y_325_;
v___y_314_ = v___y_327_;
v___y_315_ = v___y_326_;
v___y_316_ = v___y_330_;
v___y_317_ = v___y_324_;
goto v___jp_310_;
}
}
v___jp_334_:
{
uint64_t v___x_342_; uint64_t v___x_343_; uint8_t v___x_344_; 
v___x_342_ = 16ULL;
v___x_343_ = lean_uint64_shift_right(v___y_340_, v___x_342_);
v___x_344_ = lean_uint64_dec_eq(v___x_343_, v___y_339_);
if (v___x_344_ == 0)
{
v___y_322_ = v___y_335_;
v___y_323_ = v___y_336_;
v___y_324_ = v___y_341_;
v___y_325_ = v___y_337_;
v___y_326_ = v___y_339_;
v___y_327_ = v___y_338_;
v___y_328_ = v___y_340_;
v___y_329_ = v___x_342_;
v___y_330_ = v___x_343_;
goto v___jp_321_;
}
else
{
v___y_322_ = v___y_335_;
v___y_323_ = v___y_336_;
v___y_324_ = v___y_341_;
v___y_325_ = v___y_337_;
v___y_326_ = v___y_339_;
v___y_327_ = v___y_338_;
v___y_328_ = v___y_340_;
v___y_329_ = v___x_342_;
v___y_330_ = v___y_340_;
goto v___jp_321_;
}
}
v___jp_345_:
{
uint64_t v___x_353_; uint8_t v___x_354_; 
v___x_353_ = lean_uint64_shift_right(v___y_347_, v___y_351_);
v___x_354_ = lean_uint64_dec_eq(v___x_353_, v___y_349_);
if (v___x_354_ == 0)
{
v___y_335_ = v___y_346_;
v___y_336_ = v___y_347_;
v___y_337_ = v___y_348_;
v___y_338_ = v___y_350_;
v___y_339_ = v___y_349_;
v___y_340_ = v___y_352_;
v___y_341_ = v___y_351_;
goto v___jp_334_;
}
else
{
v___y_335_ = v___y_346_;
v___y_336_ = v___y_347_;
v___y_337_ = v___y_348_;
v___y_338_ = v___y_350_;
v___y_339_ = v___y_349_;
v___y_340_ = v___y_352_;
v___y_341_ = v___y_349_;
goto v___jp_334_;
}
}
v___jp_355_:
{
uint64_t v___x_360_; uint8_t v___x_361_; 
v___x_360_ = 0ULL;
v___x_361_ = lean_uint64_dec_eq(v___y_357_, v___x_360_);
if (v___x_361_ == 0)
{
uint64_t v___x_362_; uint64_t v___x_363_; uint8_t v___x_364_; 
v___x_362_ = 32ULL;
v___x_363_ = lean_uint64_shift_right(v___y_357_, v___x_362_);
v___x_364_ = lean_uint64_dec_eq(v___x_363_, v___x_360_);
if (v___x_364_ == 0)
{
v___y_346_ = v___y_356_;
v___y_347_ = v___y_357_;
v___y_348_ = v___y_358_;
v___y_349_ = v___x_360_;
v___y_350_ = v___y_359_;
v___y_351_ = v___x_362_;
v___y_352_ = v___x_363_;
goto v___jp_345_;
}
else
{
v___y_346_ = v___y_356_;
v___y_347_ = v___y_357_;
v___y_348_ = v___y_358_;
v___y_349_ = v___x_360_;
v___y_350_ = v___y_359_;
v___y_351_ = v___x_362_;
v___y_352_ = v___y_357_;
goto v___jp_345_;
}
}
else
{
if (v___y_359_ == 0)
{
uint32_t v___x_365_; 
v___x_365_ = 0;
return v___x_365_;
}
else
{
uint32_t v___x_366_; 
v___x_366_ = 2147483648;
return v___x_366_;
}
}
}
v___jp_367_:
{
uint64_t v___x_374_; uint64_t v___x_375_; uint64_t v___x_376_; uint8_t v___x_377_; 
v___x_374_ = lean_uint64_mul(v___y_370_, v___y_372_);
v___x_375_ = lean_uint64_add(v___y_369_, v___y_373_);
v___x_376_ = 281474976710656ULL;
v___x_377_ = lean_uint64_dec_lt(v___x_374_, v___x_376_);
if (v___x_377_ == 0)
{
v___y_356_ = v___y_368_;
v___y_357_ = v___x_374_;
v___y_358_ = v___x_375_;
v___y_359_ = v___y_371_;
goto v___jp_355_;
}
else
{
uint64_t v___x_378_; uint8_t v___x_379_; 
v___x_378_ = 123ULL;
v___x_379_ = lean_uint64_dec_le(v___x_375_, v___x_378_);
if (v___x_379_ == 0)
{
v___y_356_ = v___y_368_;
v___y_357_ = v___x_374_;
v___y_358_ = v___x_375_;
v___y_359_ = v___y_371_;
goto v___jp_355_;
}
else
{
uint64_t v___x_380_; uint8_t v___x_381_; 
v___x_380_ = 0ULL;
v___x_381_ = lean_uint64_dec_eq(v___x_374_, v___x_380_);
if (v___x_381_ == 0)
{
uint64_t v___x_382_; uint64_t v___x_383_; uint8_t v___x_384_; 
v___x_382_ = 149ULL;
v___x_383_ = lean_uint64_sub(v___x_382_, v___x_375_);
v___x_384_ = lean_uint64_dec_eq(v___x_383_, v___x_380_);
if (v___x_384_ == 0)
{
uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_385_ = 64ULL;
v___x_386_ = lean_uint64_dec_lt(v___x_383_, v___x_385_);
if (v___x_386_ == 0)
{
uint8_t v___x_387_; 
v___x_387_ = lean_uint64_dec_eq(v___x_383_, v___x_385_);
if (v___x_387_ == 0)
{
v___y_107_ = v___y_368_;
v___y_108_ = v___x_380_;
v___y_109_ = v___y_371_;
v___y_110_ = v___x_380_;
goto v___jp_106_;
}
else
{
uint64_t v___x_388_; uint8_t v___x_389_; 
v___x_388_ = 9223372036854775808ULL;
v___x_389_ = lean_uint64_dec_lt(v___x_388_, v___x_374_);
if (v___x_389_ == 0)
{
v___y_107_ = v___y_368_;
v___y_108_ = v___x_380_;
v___y_109_ = v___y_371_;
v___y_110_ = v___x_380_;
goto v___jp_106_;
}
else
{
uint64_t v___x_390_; 
v___x_390_ = 1ULL;
v___y_107_ = v___y_368_;
v___y_108_ = v___x_380_;
v___y_109_ = v___y_371_;
v___y_110_ = v___x_390_;
goto v___jp_106_;
}
}
}
else
{
uint64_t v_quotient_391_; uint64_t v___x_392_; uint64_t v___x_393_; uint64_t v___x_394_; uint64_t v_remainder_395_; uint64_t v___x_396_; uint64_t v_half_397_; uint8_t v___x_398_; 
v_quotient_391_ = lean_uint64_shift_right(v___x_374_, v___x_383_);
v___x_392_ = 1ULL;
v___x_393_ = lean_uint64_shift_left(v___x_392_, v___x_383_);
v___x_394_ = lean_uint64_sub(v___x_393_, v___x_392_);
v_remainder_395_ = lean_uint64_land(v___x_374_, v___x_394_);
v___x_396_ = lean_uint64_sub(v___x_383_, v___x_392_);
v_half_397_ = lean_uint64_shift_left(v___x_392_, v___x_396_);
v___x_398_ = lean_uint64_dec_lt(v_remainder_395_, v_half_397_);
if (v___x_398_ == 0)
{
uint8_t v___x_399_; 
v___x_399_ = lean_uint64_dec_lt(v_half_397_, v_remainder_395_);
if (v___x_399_ == 0)
{
uint64_t v___x_400_; uint8_t v___x_401_; 
v___x_400_ = lean_uint64_land(v_quotient_391_, v___x_392_);
v___x_401_ = lean_uint64_dec_eq(v___x_400_, v___x_380_);
if (v___x_401_ == 0)
{
uint64_t v___x_402_; 
v___x_402_ = lean_uint64_add(v_quotient_391_, v___x_392_);
v___y_107_ = v___y_368_;
v___y_108_ = v___x_380_;
v___y_109_ = v___y_371_;
v___y_110_ = v___x_402_;
goto v___jp_106_;
}
else
{
v___y_107_ = v___y_368_;
v___y_108_ = v___x_380_;
v___y_109_ = v___y_371_;
v___y_110_ = v_quotient_391_;
goto v___jp_106_;
}
}
else
{
uint64_t v___x_403_; 
v___x_403_ = lean_uint64_add(v_quotient_391_, v___x_392_);
v___y_107_ = v___y_368_;
v___y_108_ = v___x_380_;
v___y_109_ = v___y_371_;
v___y_110_ = v___x_403_;
goto v___jp_106_;
}
}
else
{
v___y_107_ = v___y_368_;
v___y_108_ = v___x_380_;
v___y_109_ = v___y_371_;
v___y_110_ = v_quotient_391_;
goto v___jp_106_;
}
}
}
else
{
v___y_107_ = v___y_368_;
v___y_108_ = v___x_380_;
v___y_109_ = v___y_371_;
v___y_110_ = v___x_374_;
goto v___jp_106_;
}
}
else
{
if (v___y_371_ == 0)
{
uint32_t v___x_404_; 
v___x_404_ = 0;
return v___x_404_;
}
else
{
uint32_t v___x_405_; 
v___x_405_ = 2147483648;
return v___x_405_;
}
}
}
}
}
v___jp_409_:
{
uint64_t v___x_415_; uint64_t v___x_416_; uint8_t v___x_417_; 
v___x_415_ = lean_uint32_to_uint64(v_ey_408_);
v___x_416_ = 0ULL;
v___x_417_ = lean_uint64_dec_eq(v___x_415_, v___x_416_);
if (v___x_417_ == 0)
{
uint64_t v___x_418_; uint64_t v___x_419_; 
v___x_418_ = 1ULL;
v___x_419_ = lean_uint64_sub(v___x_415_, v___x_418_);
v___y_368_ = v___y_410_;
v___y_369_ = v___y_414_;
v___y_370_ = v___y_411_;
v___y_371_ = v___y_412_;
v___y_372_ = v___y_413_;
v___y_373_ = v___x_419_;
goto v___jp_367_;
}
else
{
v___y_368_ = v___y_410_;
v___y_369_ = v___y_414_;
v___y_370_ = v___y_411_;
v___y_371_ = v___y_412_;
v___y_372_ = v___y_413_;
v___y_373_ = v___x_416_;
goto v___jp_367_;
}
}
v___jp_420_:
{
uint64_t v___x_425_; uint64_t v___x_426_; uint8_t v___x_427_; 
v___x_425_ = lean_uint32_to_uint64(v_ex_406_);
v___x_426_ = 0ULL;
v___x_427_ = lean_uint64_dec_eq(v___x_425_, v___x_426_);
if (v___x_427_ == 0)
{
uint64_t v___x_428_; uint64_t v___x_429_; 
v___x_428_ = 1ULL;
v___x_429_ = lean_uint64_sub(v___x_425_, v___x_428_);
v___y_410_ = v___y_421_;
v___y_411_ = v___y_422_;
v___y_412_ = v___y_423_;
v___y_413_ = v___y_424_;
v___y_414_ = v___x_429_;
goto v___jp_409_;
}
else
{
v___y_410_ = v___y_421_;
v___y_411_ = v___y_422_;
v___y_412_ = v___y_423_;
v___y_413_ = v___y_424_;
v___y_414_ = v___x_426_;
goto v___jp_409_;
}
}
v___jp_430_:
{
uint32_t v___x_435_; uint8_t v___x_436_; 
v___x_435_ = 0;
v___x_436_ = lean_uint32_dec_eq(v_ey_408_, v___x_435_);
if (v___x_436_ == 0)
{
uint64_t v___x_437_; uint64_t v___x_438_; uint64_t v___x_439_; 
v___x_437_ = lean_uint32_to_uint64(v___y_433_);
v___x_438_ = 8388608ULL;
v___x_439_ = lean_uint64_lor(v___x_437_, v___x_438_);
v___y_421_ = v___y_431_;
v___y_422_ = v___y_434_;
v___y_423_ = v___y_432_;
v___y_424_ = v___x_439_;
goto v___jp_420_;
}
else
{
uint64_t v___x_440_; 
v___x_440_ = lean_uint32_to_uint64(v___y_433_);
v___y_421_ = v___y_431_;
v___y_422_ = v___y_434_;
v___y_423_ = v___y_432_;
v___y_424_ = v___x_440_;
goto v___jp_420_;
}
}
v___jp_441_:
{
uint32_t v___x_443_; uint32_t v_xFraction_444_; uint32_t v_yFraction_445_; uint32_t v___x_446_; uint8_t v___x_447_; 
v___x_443_ = 8388607;
v_xFraction_444_ = lean_uint32_land(v___y_69_, v___x_443_);
v_yFraction_445_ = lean_uint32_land(v___y_70_, v___x_443_);
v___x_446_ = 0;
v___x_447_ = lean_uint32_dec_eq(v_ex_406_, v___x_446_);
if (v___x_447_ == 0)
{
uint64_t v___x_448_; uint64_t v___x_449_; uint64_t v___x_450_; 
v___x_448_ = lean_uint32_to_uint64(v_xFraction_444_);
v___x_449_ = 8388608ULL;
v___x_450_ = lean_uint64_lor(v___x_448_, v___x_449_);
v___y_431_ = v___x_443_;
v___y_432_ = v___y_442_;
v___y_433_ = v_yFraction_445_;
v___y_434_ = v___x_450_;
goto v___jp_430_;
}
else
{
uint64_t v___x_451_; 
v___x_451_ = lean_uint32_to_uint64(v_xFraction_444_);
v___y_431_ = v___x_443_;
v___y_432_ = v___y_442_;
v___y_433_ = v_yFraction_445_;
v___y_434_ = v___x_451_;
goto v___jp_430_;
}
}
v___jp_455_:
{
if (v___y_457_ == 0)
{
v___y_442_ = v___x_454_;
goto v___jp_441_;
}
else
{
v___y_442_ = v___y_456_;
goto v___jp_441_;
}
}
v___jp_458_:
{
if (v___y_460_ == 0)
{
if (v___y_461_ == 0)
{
v___y_456_ = v___y_459_;
v___y_457_ = v___x_454_;
goto v___jp_455_;
}
else
{
v___y_442_ = v___x_454_;
goto v___jp_441_;
}
}
else
{
v___y_456_ = v___y_459_;
v___y_457_ = v___y_461_;
goto v___jp_455_;
}
}
v___jp_462_:
{
uint32_t v___x_465_; uint32_t v___x_466_; uint32_t v___x_467_; uint8_t v___x_468_; 
v___x_465_ = 2147483648;
v___x_466_ = lean_uint32_land(v___y_70_, v___x_465_);
v___x_467_ = 0;
v___x_468_ = lean_uint32_dec_eq(v___x_466_, v___x_467_);
if (v___x_468_ == 0)
{
v___y_459_ = v___y_463_;
v___y_460_ = v___y_464_;
v___y_461_ = v___x_454_;
goto v___jp_458_;
}
else
{
v___y_459_ = v___y_463_;
v___y_460_ = v___y_464_;
v___y_461_ = v___y_463_;
goto v___jp_458_;
}
}
v___jp_469_:
{
if (v___y_470_ == 0)
{
uint32_t v___x_471_; uint32_t v___x_472_; uint32_t v___x_473_; uint8_t v___x_474_; 
v___x_471_ = 2147483648;
v___x_472_ = lean_uint32_land(v___y_69_, v___x_471_);
v___x_473_ = 0;
v___x_474_ = lean_uint32_dec_eq(v___x_472_, v___x_473_);
if (v___x_474_ == 0)
{
v___y_463_ = v___y_470_;
v___y_464_ = v___x_454_;
goto v___jp_462_;
}
else
{
v___y_463_ = v___y_470_;
v___y_464_ = v___y_470_;
goto v___jp_462_;
}
}
else
{
lean_object* v___x_475_; lean_object* v___x_476_; lean_object* v___x_477_; uint32_t v___x_478_; 
v___x_475_ = lean_uint32_to_nat(v___y_69_);
v___x_476_ = lean_uint32_to_nat(v___y_70_);
v___x_477_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_475_, v___x_476_);
v___x_478_ = lean_uint32_of_nat(v___x_477_);
lean_dec(v___x_477_);
return v___x_478_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_491_, lean_object* v___y_492_){
_start:
{
uint32_t v___y_3859__boxed_493_; uint32_t v___y_3860__boxed_494_; uint32_t v_res_495_; lean_object* v_r_496_; 
v___y_3859__boxed_493_ = lean_unbox_uint32(v___y_491_);
lean_dec(v___y_491_);
v___y_3860__boxed_494_ = lean_unbox_uint32(v___y_492_);
lean_dec(v___y_492_);
v_res_495_ = lp_competition_main___lam__1(v___y_3859__boxed_493_, v___y_3860__boxed_494_);
v_r_496_ = lean_box_uint32(v_res_495_);
return v_r_496_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_497_, uint32_t v___y_498_){
_start:
{
uint32_t v___y_500_; uint32_t v___y_504_; uint32_t v___y_508_; uint32_t v___y_509_; uint32_t v___y_510_; uint8_t v___y_514_; uint32_t v___y_515_; uint64_t v___y_516_; uint64_t v___y_517_; uint32_t v___y_529_; uint32_t v___y_530_; uint32_t v___y_531_; uint8_t v___y_535_; uint32_t v___y_536_; uint64_t v___y_537_; uint64_t v___y_538_; uint32_t v___x_549_; uint32_t v___x_550_; uint32_t v___x_551_; uint32_t v___y_553_; uint32_t v___y_554_; uint32_t v___y_555_; uint32_t v___y_556_; uint8_t v___y_563_; uint32_t v___y_564_; uint32_t v___y_565_; uint32_t v___y_566_; uint8_t v___y_570_; uint32_t v___y_571_; uint64_t v___y_572_; uint64_t v___y_573_; uint64_t v___y_574_; uint8_t v___y_584_; uint32_t v___y_585_; uint8_t v___y_586_; uint64_t v___y_587_; uint64_t v___y_588_; uint64_t v___y_589_; uint8_t v___y_596_; uint64_t v___y_597_; uint32_t v___y_598_; uint64_t v___y_599_; uint64_t v___y_600_; uint8_t v___y_606_; uint32_t v___y_607_; uint64_t v___y_608_; uint64_t v___y_609_; uint64_t v___y_610_; uint64_t v___y_611_; uint8_t v___y_666_; uint32_t v___y_667_; uint64_t v___y_668_; uint64_t v___y_669_; uint64_t v___y_670_; uint64_t v___y_671_; uint64_t v___y_672_; uint8_t v___y_678_; uint64_t v___y_679_; uint32_t v___y_680_; uint64_t v___y_681_; uint64_t v___y_682_; uint64_t v___y_683_; uint64_t v___y_684_; uint64_t v___y_685_; uint64_t v___y_686_; uint8_t v___y_691_; uint32_t v___y_692_; uint64_t v___y_693_; uint64_t v___y_694_; uint64_t v___y_695_; uint64_t v___y_696_; uint64_t v___y_697_; uint64_t v___y_702_; uint8_t v___y_703_; uint32_t v___y_704_; uint64_t v___y_705_; uint64_t v___y_706_; uint64_t v___y_707_; uint64_t v___y_708_; uint64_t v___y_709_; uint64_t v___y_710_; uint8_t v___y_715_; uint32_t v___y_716_; uint64_t v___y_717_; uint64_t v___y_718_; uint64_t v___y_719_; uint64_t v___y_720_; uint64_t v___y_721_; uint8_t v___y_726_; uint64_t v___y_727_; uint32_t v___y_728_; uint64_t v___y_729_; uint64_t v___y_730_; uint64_t v___y_731_; uint64_t v___y_732_; uint64_t v___y_733_; uint64_t v___y_734_; uint8_t v___y_739_; uint32_t v___y_740_; uint64_t v___y_741_; uint64_t v___y_742_; uint64_t v___y_743_; uint64_t v___y_744_; uint64_t v___y_745_; uint8_t v___y_750_; uint64_t v___y_751_; uint32_t v___y_752_; uint64_t v___y_753_; uint64_t v___y_754_; uint64_t v___y_755_; uint64_t v___y_756_; uint64_t v___y_757_; uint64_t v___y_758_; uint8_t v___y_763_; uint32_t v___y_764_; uint64_t v___y_765_; uint64_t v___y_766_; uint64_t v___y_767_; uint64_t v___y_768_; uint64_t v___y_769_; uint8_t v___y_774_; uint32_t v___y_775_; uint64_t v___y_776_; uint64_t v___y_777_; uint64_t v___y_778_; uint64_t v___y_779_; uint64_t v___y_780_; uint8_t v___y_784_; uint32_t v___y_785_; uint64_t v___y_786_; uint64_t v___y_787_; uint8_t v___y_796_; uint64_t v___y_797_; uint32_t v___y_798_; uint64_t v___y_799_; uint64_t v___y_800_; uint64_t v___y_801_; uint32_t v_ex_834_; uint32_t v___x_835_; uint32_t v_ey_836_; uint64_t v___y_838_; uint8_t v___y_839_; uint32_t v___y_840_; uint64_t v___y_841_; uint64_t v___y_842_; uint8_t v___y_849_; uint64_t v___y_850_; uint32_t v___y_851_; uint64_t v___y_852_; uint8_t v___y_859_; uint32_t v___y_860_; uint32_t v___y_861_; uint64_t v___y_862_; uint8_t v___y_870_; uint32_t v___x_880_; uint32_t v___x_881_; uint8_t v___x_882_; uint8_t v___y_884_; uint8_t v___y_885_; uint8_t v___y_887_; uint8_t v___y_888_; uint8_t v___y_889_; uint8_t v___y_891_; uint8_t v___y_892_; uint8_t v___y_898_; 
v___x_549_ = 23;
v___x_550_ = lean_uint32_shift_right(v___y_497_, v___x_549_);
v___x_551_ = 255;
v_ex_834_ = lean_uint32_land(v___x_550_, v___x_551_);
v___x_835_ = lean_uint32_shift_right(v___y_498_, v___x_549_);
v_ey_836_ = lean_uint32_land(v___x_835_, v___x_551_);
v___x_880_ = lean_uint32_add(v_ex_834_, v_ey_836_);
v___x_881_ = 128;
v___x_882_ = lean_uint32_dec_lt(v___x_880_, v___x_881_);
if (v___x_882_ == 0)
{
float v___x_907_; float v___x_908_; float v_result_909_; uint8_t v___x_910_; 
v___x_907_ = lean_float32_of_bits(v___y_497_);
v___x_908_ = lean_float32_of_bits(v___y_498_);
v_result_909_ = lean_float32_mul(v___x_907_, v___x_908_);
v___x_910_ = lean_float32_beq(v_result_909_, v_result_909_);
if (v___x_910_ == 0)
{
uint32_t v___x_911_; 
v___x_911_ = lp_competition_Submission_FastMul_mul(v___y_497_, v___y_498_);
return v___x_911_;
}
else
{
uint32_t v___x_912_; 
v___x_912_ = lean_float32_to_bits(v_result_909_);
return v___x_912_;
}
}
else
{
uint32_t v___x_913_; uint32_t v___x_914_; uint32_t v___x_915_; uint8_t v___x_916_; 
v___x_913_ = 4278190080;
v___x_914_ = 1;
v___x_915_ = lean_uint32_shift_left(v___y_497_, v___x_914_);
v___x_916_ = lean_uint32_dec_le(v___x_913_, v___x_915_);
if (v___x_916_ == 0)
{
uint32_t v___x_917_; uint8_t v___x_918_; 
v___x_917_ = lean_uint32_shift_left(v___y_498_, v___x_914_);
v___x_918_ = lean_uint32_dec_le(v___x_913_, v___x_917_);
v___y_898_ = v___x_918_;
goto v___jp_897_;
}
else
{
v___y_898_ = v___x_916_;
goto v___jp_897_;
}
}
v___jp_499_:
{
uint32_t v___x_501_; uint32_t v___x_502_; 
v___x_501_ = 8388608;
v___x_502_ = lean_uint32_lor(v___y_500_, v___x_501_);
return v___x_502_;
}
v___jp_503_:
{
uint32_t v___x_505_; uint32_t v___x_506_; 
v___x_505_ = 8388608;
v___x_506_ = lean_uint32_lor(v___y_504_, v___x_505_);
return v___x_506_;
}
v___jp_507_:
{
uint32_t v___x_511_; uint32_t v___x_512_; 
v___x_511_ = lean_uint32_land(v___y_509_, v___y_508_);
v___x_512_ = lean_uint32_lor(v___y_510_, v___x_511_);
return v___x_512_;
}
v___jp_513_:
{
uint8_t v___x_518_; 
v___x_518_ = lean_uint64_dec_eq(v___y_517_, v___y_516_);
if (v___x_518_ == 0)
{
uint64_t v___x_519_; uint8_t v___x_520_; 
v___x_519_ = 8388608ULL;
v___x_520_ = lean_uint64_dec_eq(v___y_517_, v___x_519_);
if (v___x_520_ == 0)
{
uint32_t v___x_521_; 
v___x_521_ = lean_uint64_to_uint32(v___y_517_);
if (v___y_514_ == 0)
{
uint32_t v___x_522_; 
v___x_522_ = 0;
v___y_508_ = v___y_515_;
v___y_509_ = v___x_521_;
v___y_510_ = v___x_522_;
goto v___jp_507_;
}
else
{
uint32_t v___x_523_; 
v___x_523_ = 2147483648;
v___y_508_ = v___y_515_;
v___y_509_ = v___x_521_;
v___y_510_ = v___x_523_;
goto v___jp_507_;
}
}
else
{
if (v___y_514_ == 0)
{
uint32_t v___x_524_; 
v___x_524_ = 0;
v___y_504_ = v___x_524_;
goto v___jp_503_;
}
else
{
uint32_t v___x_525_; 
v___x_525_ = 2147483648;
v___y_504_ = v___x_525_;
goto v___jp_503_;
}
}
}
else
{
if (v___y_514_ == 0)
{
uint32_t v___x_526_; 
v___x_526_ = 0;
return v___x_526_;
}
else
{
uint32_t v___x_527_; 
v___x_527_ = 2147483648;
return v___x_527_;
}
}
}
v___jp_528_:
{
uint32_t v___x_532_; uint32_t v___x_533_; 
v___x_532_ = lean_uint32_land(v___y_530_, v___y_529_);
v___x_533_ = lean_uint32_lor(v___y_531_, v___x_532_);
return v___x_533_;
}
v___jp_534_:
{
uint8_t v___x_539_; 
v___x_539_ = lean_uint64_dec_eq(v___y_538_, v___y_537_);
if (v___x_539_ == 0)
{
uint64_t v___x_540_; uint8_t v___x_541_; 
v___x_540_ = 8388608ULL;
v___x_541_ = lean_uint64_dec_eq(v___y_538_, v___x_540_);
if (v___x_541_ == 0)
{
uint32_t v___x_542_; 
v___x_542_ = lean_uint64_to_uint32(v___y_538_);
if (v___y_535_ == 0)
{
uint32_t v___x_543_; 
v___x_543_ = 0;
v___y_529_ = v___y_536_;
v___y_530_ = v___x_542_;
v___y_531_ = v___x_543_;
goto v___jp_528_;
}
else
{
uint32_t v___x_544_; 
v___x_544_ = 2147483648;
v___y_529_ = v___y_536_;
v___y_530_ = v___x_542_;
v___y_531_ = v___x_544_;
goto v___jp_528_;
}
}
else
{
if (v___y_535_ == 0)
{
uint32_t v___x_545_; 
v___x_545_ = 0;
v___y_500_ = v___x_545_;
goto v___jp_499_;
}
else
{
uint32_t v___x_546_; 
v___x_546_ = 2147483648;
v___y_500_ = v___x_546_;
goto v___jp_499_;
}
}
}
else
{
if (v___y_535_ == 0)
{
uint32_t v___x_547_; 
v___x_547_ = 0;
return v___x_547_;
}
else
{
uint32_t v___x_548_; 
v___x_548_ = 2147483648;
return v___x_548_;
}
}
}
v___jp_552_:
{
uint32_t v___x_557_; uint32_t v___x_558_; uint32_t v___x_559_; uint32_t v___x_560_; uint32_t v___x_561_; 
v___x_557_ = lean_uint32_land(v___y_554_, v___x_551_);
v___x_558_ = lean_uint32_shift_left(v___x_557_, v___x_549_);
v___x_559_ = lean_uint32_lor(v___y_556_, v___x_558_);
v___x_560_ = lean_uint32_land(v___y_555_, v___y_553_);
v___x_561_ = lean_uint32_lor(v___x_559_, v___x_560_);
return v___x_561_;
}
v___jp_562_:
{
if (v___y_563_ == 0)
{
uint32_t v___x_567_; 
v___x_567_ = 0;
v___y_553_ = v___y_564_;
v___y_554_ = v___y_565_;
v___y_555_ = v___y_566_;
v___y_556_ = v___x_567_;
goto v___jp_552_;
}
else
{
uint32_t v___x_568_; 
v___x_568_ = 2147483648;
v___y_553_ = v___y_564_;
v___y_554_ = v___y_565_;
v___y_555_ = v___y_566_;
v___y_556_ = v___x_568_;
goto v___jp_552_;
}
}
v___jp_569_:
{
uint64_t v___x_575_; uint64_t v_encodedExponent_576_; uint32_t v___x_577_; uint64_t v___x_578_; uint8_t v___x_579_; 
v___x_575_ = 171ULL;
v_encodedExponent_576_ = lean_uint64_sub(v___y_573_, v___x_575_);
v___x_577_ = lean_uint64_to_uint32(v_encodedExponent_576_);
v___x_578_ = 8388608ULL;
v___x_579_ = lean_uint64_dec_lt(v___y_574_, v___x_578_);
if (v___x_579_ == 0)
{
uint64_t v___x_580_; uint32_t v___x_581_; 
v___x_580_ = lean_uint64_sub(v___y_574_, v___x_578_);
v___x_581_ = lean_uint64_to_uint32(v___x_580_);
v___y_563_ = v___y_570_;
v___y_564_ = v___y_571_;
v___y_565_ = v___x_577_;
v___y_566_ = v___x_581_;
goto v___jp_562_;
}
else
{
uint32_t v___x_582_; 
v___x_582_ = lean_uint64_to_uint32(v___y_572_);
v___y_563_ = v___y_570_;
v___y_564_ = v___y_571_;
v___y_565_ = v___x_577_;
v___y_566_ = v___x_582_;
goto v___jp_562_;
}
}
v___jp_583_:
{
uint64_t v___x_590_; uint8_t v___x_591_; 
v___x_590_ = 425ULL;
v___x_591_ = lean_uint64_dec_lt(v___x_590_, v___y_589_);
if (v___x_591_ == 0)
{
if (v___y_586_ == 0)
{
v___y_570_ = v___y_584_;
v___y_571_ = v___y_585_;
v___y_572_ = v___y_588_;
v___y_573_ = v___y_589_;
v___y_574_ = v___y_587_;
goto v___jp_569_;
}
else
{
uint64_t v___x_592_; 
v___x_592_ = 8388608ULL;
v___y_570_ = v___y_584_;
v___y_571_ = v___y_585_;
v___y_572_ = v___y_588_;
v___y_573_ = v___y_589_;
v___y_574_ = v___x_592_;
goto v___jp_569_;
}
}
else
{
if (v___y_584_ == 0)
{
uint32_t v___x_593_; 
v___x_593_ = 2139095040;
return v___x_593_;
}
else
{
uint32_t v___x_594_; 
v___x_594_ = 4286578688;
return v___x_594_;
}
}
}
v___jp_595_:
{
uint64_t v___x_601_; uint8_t v_carry_602_; 
v___x_601_ = 16777216ULL;
v_carry_602_ = lean_uint64_dec_eq(v___y_600_, v___x_601_);
if (v_carry_602_ == 0)
{
v___y_584_ = v___y_596_;
v___y_585_ = v___y_598_;
v___y_586_ = v_carry_602_;
v___y_587_ = v___y_600_;
v___y_588_ = v___y_599_;
v___y_589_ = v___y_597_;
goto v___jp_583_;
}
else
{
uint64_t v___x_603_; uint64_t v___x_604_; 
v___x_603_ = 1ULL;
v___x_604_ = lean_uint64_add(v___y_597_, v___x_603_);
v___y_584_ = v___y_596_;
v___y_585_ = v___y_598_;
v___y_586_ = v_carry_602_;
v___y_587_ = v___y_600_;
v___y_588_ = v___y_599_;
v___y_589_ = v___x_604_;
goto v___jp_583_;
}
}
v___jp_605_:
{
uint64_t v_position_612_; uint64_t v___x_613_; uint8_t v___x_614_; 
v_position_612_ = lean_uint64_add(v___y_611_, v___y_608_);
v___x_613_ = 172ULL;
v___x_614_ = lean_uint64_dec_lt(v_position_612_, v___x_613_);
if (v___x_614_ == 0)
{
uint64_t v___x_615_; uint8_t v___x_616_; 
v___x_615_ = 23ULL;
v___x_616_ = lean_uint64_dec_lt(v___y_611_, v___x_615_);
if (v___x_616_ == 0)
{
uint64_t v___x_617_; uint8_t v___x_618_; 
v___x_617_ = lean_uint64_sub(v___y_611_, v___x_615_);
v___x_618_ = lean_uint64_dec_eq(v___x_617_, v___y_609_);
if (v___x_618_ == 0)
{
uint64_t v___x_619_; uint8_t v___x_620_; 
v___x_619_ = 64ULL;
v___x_620_ = lean_uint64_dec_lt(v___x_617_, v___x_619_);
if (v___x_620_ == 0)
{
uint8_t v___x_621_; 
v___x_621_ = lean_uint64_dec_eq(v___x_617_, v___x_619_);
if (v___x_621_ == 0)
{
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v___y_609_;
goto v___jp_595_;
}
else
{
uint64_t v___x_622_; uint8_t v___x_623_; 
v___x_622_ = 9223372036854775808ULL;
v___x_623_ = lean_uint64_dec_lt(v___x_622_, v___y_610_);
if (v___x_623_ == 0)
{
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v___y_609_;
goto v___jp_595_;
}
else
{
uint64_t v___x_624_; 
v___x_624_ = 1ULL;
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v___x_624_;
goto v___jp_595_;
}
}
}
else
{
uint64_t v_quotient_625_; uint64_t v___x_626_; uint64_t v___x_627_; uint64_t v___x_628_; uint64_t v_remainder_629_; uint64_t v___x_630_; uint64_t v_half_631_; uint8_t v___x_632_; 
v_quotient_625_ = lean_uint64_shift_right(v___y_610_, v___x_617_);
v___x_626_ = 1ULL;
v___x_627_ = lean_uint64_shift_left(v___x_626_, v___x_617_);
v___x_628_ = lean_uint64_sub(v___x_627_, v___x_626_);
v_remainder_629_ = lean_uint64_land(v___y_610_, v___x_628_);
v___x_630_ = lean_uint64_sub(v___x_617_, v___x_626_);
v_half_631_ = lean_uint64_shift_left(v___x_626_, v___x_630_);
v___x_632_ = lean_uint64_dec_lt(v_remainder_629_, v_half_631_);
if (v___x_632_ == 0)
{
uint8_t v___x_633_; 
v___x_633_ = lean_uint64_dec_lt(v_half_631_, v_remainder_629_);
if (v___x_633_ == 0)
{
uint64_t v___x_634_; uint8_t v___x_635_; 
v___x_634_ = lean_uint64_land(v_quotient_625_, v___x_626_);
v___x_635_ = lean_uint64_dec_eq(v___x_634_, v___y_609_);
if (v___x_635_ == 0)
{
uint64_t v___x_636_; 
v___x_636_ = lean_uint64_add(v_quotient_625_, v___x_626_);
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v___x_636_;
goto v___jp_595_;
}
else
{
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v_quotient_625_;
goto v___jp_595_;
}
}
else
{
uint64_t v___x_637_; 
v___x_637_ = lean_uint64_add(v_quotient_625_, v___x_626_);
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v___x_637_;
goto v___jp_595_;
}
}
else
{
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v_quotient_625_;
goto v___jp_595_;
}
}
}
else
{
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v___y_610_;
goto v___jp_595_;
}
}
else
{
uint64_t v___x_638_; uint64_t v___x_639_; 
v___x_638_ = lean_uint64_sub(v___x_615_, v___y_611_);
v___x_639_ = lean_uint64_shift_left(v___y_610_, v___x_638_);
v___y_596_ = v___y_606_;
v___y_597_ = v_position_612_;
v___y_598_ = v___y_607_;
v___y_599_ = v___y_609_;
v___y_600_ = v___x_639_;
goto v___jp_595_;
}
}
else
{
uint64_t v___x_640_; uint8_t v___x_641_; 
v___x_640_ = 149ULL;
v___x_641_ = lean_uint64_dec_lt(v___y_608_, v___x_640_);
if (v___x_641_ == 0)
{
uint64_t v___x_642_; uint64_t v___x_643_; 
v___x_642_ = lean_uint64_sub(v___y_608_, v___x_640_);
v___x_643_ = lean_uint64_shift_left(v___y_610_, v___x_642_);
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v___x_643_;
goto v___jp_513_;
}
else
{
uint64_t v___x_644_; uint8_t v___x_645_; 
v___x_644_ = lean_uint64_sub(v___x_640_, v___y_608_);
v___x_645_ = lean_uint64_dec_eq(v___x_644_, v___y_609_);
if (v___x_645_ == 0)
{
uint64_t v___x_646_; uint8_t v___x_647_; 
v___x_646_ = 64ULL;
v___x_647_ = lean_uint64_dec_lt(v___x_644_, v___x_646_);
if (v___x_647_ == 0)
{
uint8_t v___x_648_; 
v___x_648_ = lean_uint64_dec_eq(v___x_644_, v___x_646_);
if (v___x_648_ == 0)
{
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v___y_609_;
goto v___jp_513_;
}
else
{
uint64_t v___x_649_; uint8_t v___x_650_; 
v___x_649_ = 9223372036854775808ULL;
v___x_650_ = lean_uint64_dec_lt(v___x_649_, v___y_610_);
if (v___x_650_ == 0)
{
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v___y_609_;
goto v___jp_513_;
}
else
{
uint64_t v___x_651_; 
v___x_651_ = 1ULL;
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v___x_651_;
goto v___jp_513_;
}
}
}
else
{
uint64_t v_quotient_652_; uint64_t v___x_653_; uint64_t v___x_654_; uint64_t v___x_655_; uint64_t v_remainder_656_; uint64_t v___x_657_; uint64_t v_half_658_; uint8_t v___x_659_; 
v_quotient_652_ = lean_uint64_shift_right(v___y_610_, v___x_644_);
v___x_653_ = 1ULL;
v___x_654_ = lean_uint64_shift_left(v___x_653_, v___x_644_);
v___x_655_ = lean_uint64_sub(v___x_654_, v___x_653_);
v_remainder_656_ = lean_uint64_land(v___y_610_, v___x_655_);
v___x_657_ = lean_uint64_sub(v___x_644_, v___x_653_);
v_half_658_ = lean_uint64_shift_left(v___x_653_, v___x_657_);
v___x_659_ = lean_uint64_dec_lt(v_remainder_656_, v_half_658_);
if (v___x_659_ == 0)
{
uint8_t v___x_660_; 
v___x_660_ = lean_uint64_dec_lt(v_half_658_, v_remainder_656_);
if (v___x_660_ == 0)
{
uint64_t v___x_661_; uint8_t v___x_662_; 
v___x_661_ = lean_uint64_land(v_quotient_652_, v___x_653_);
v___x_662_ = lean_uint64_dec_eq(v___x_661_, v___y_609_);
if (v___x_662_ == 0)
{
uint64_t v___x_663_; 
v___x_663_ = lean_uint64_add(v_quotient_652_, v___x_653_);
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v___x_663_;
goto v___jp_513_;
}
else
{
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v_quotient_652_;
goto v___jp_513_;
}
}
else
{
uint64_t v___x_664_; 
v___x_664_ = lean_uint64_add(v_quotient_652_, v___x_653_);
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v___x_664_;
goto v___jp_513_;
}
}
else
{
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v_quotient_652_;
goto v___jp_513_;
}
}
}
else
{
v___y_514_ = v___y_606_;
v___y_515_ = v___y_607_;
v___y_516_ = v___y_609_;
v___y_517_ = v___y_610_;
goto v___jp_513_;
}
}
}
}
v___jp_665_:
{
uint64_t v___x_673_; uint64_t v___x_674_; uint8_t v___x_675_; 
v___x_673_ = 1ULL;
v___x_674_ = lean_uint64_shift_right(v___y_670_, v___x_673_);
v___x_675_ = lean_uint64_dec_eq(v___x_674_, v___y_669_);
if (v___x_675_ == 0)
{
uint64_t v___x_676_; 
v___x_676_ = lean_uint64_add(v___y_672_, v___x_673_);
v___y_606_ = v___y_666_;
v___y_607_ = v___y_667_;
v___y_608_ = v___y_668_;
v___y_609_ = v___y_669_;
v___y_610_ = v___y_671_;
v___y_611_ = v___x_676_;
goto v___jp_605_;
}
else
{
v___y_606_ = v___y_666_;
v___y_607_ = v___y_667_;
v___y_608_ = v___y_668_;
v___y_609_ = v___y_669_;
v___y_610_ = v___y_671_;
v___y_611_ = v___y_672_;
goto v___jp_605_;
}
}
v___jp_677_:
{
uint64_t v___x_687_; uint8_t v___x_688_; 
v___x_687_ = lean_uint64_shift_right(v___y_684_, v___y_679_);
v___x_688_ = lean_uint64_dec_eq(v___x_687_, v___y_683_);
if (v___x_688_ == 0)
{
uint64_t v___x_689_; 
v___x_689_ = lean_uint64_add(v___y_681_, v___y_679_);
v___y_666_ = v___y_678_;
v___y_667_ = v___y_680_;
v___y_668_ = v___y_682_;
v___y_669_ = v___y_683_;
v___y_670_ = v___y_686_;
v___y_671_ = v___y_685_;
v___y_672_ = v___x_689_;
goto v___jp_665_;
}
else
{
v___y_666_ = v___y_678_;
v___y_667_ = v___y_680_;
v___y_668_ = v___y_682_;
v___y_669_ = v___y_683_;
v___y_670_ = v___y_686_;
v___y_671_ = v___y_685_;
v___y_672_ = v___y_681_;
goto v___jp_665_;
}
}
v___jp_690_:
{
uint64_t v___x_698_; uint64_t v___x_699_; uint8_t v___x_700_; 
v___x_698_ = 2ULL;
v___x_699_ = lean_uint64_shift_right(v___y_695_, v___x_698_);
v___x_700_ = lean_uint64_dec_eq(v___x_699_, v___y_694_);
if (v___x_700_ == 0)
{
v___y_678_ = v___y_691_;
v___y_679_ = v___x_698_;
v___y_680_ = v___y_692_;
v___y_681_ = v___y_697_;
v___y_682_ = v___y_693_;
v___y_683_ = v___y_694_;
v___y_684_ = v___y_695_;
v___y_685_ = v___y_696_;
v___y_686_ = v___x_699_;
goto v___jp_677_;
}
else
{
v___y_678_ = v___y_691_;
v___y_679_ = v___x_698_;
v___y_680_ = v___y_692_;
v___y_681_ = v___y_697_;
v___y_682_ = v___y_693_;
v___y_683_ = v___y_694_;
v___y_684_ = v___y_695_;
v___y_685_ = v___y_696_;
v___y_686_ = v___y_695_;
goto v___jp_677_;
}
}
v___jp_701_:
{
uint64_t v___x_711_; uint8_t v___x_712_; 
v___x_711_ = lean_uint64_shift_right(v___y_708_, v___y_707_);
v___x_712_ = lean_uint64_dec_eq(v___x_711_, v___y_706_);
if (v___x_712_ == 0)
{
uint64_t v___x_713_; 
v___x_713_ = lean_uint64_add(v___y_702_, v___y_707_);
v___y_691_ = v___y_703_;
v___y_692_ = v___y_704_;
v___y_693_ = v___y_705_;
v___y_694_ = v___y_706_;
v___y_695_ = v___y_710_;
v___y_696_ = v___y_709_;
v___y_697_ = v___x_713_;
goto v___jp_690_;
}
else
{
v___y_691_ = v___y_703_;
v___y_692_ = v___y_704_;
v___y_693_ = v___y_705_;
v___y_694_ = v___y_706_;
v___y_695_ = v___y_710_;
v___y_696_ = v___y_709_;
v___y_697_ = v___y_702_;
goto v___jp_690_;
}
}
v___jp_714_:
{
uint64_t v___x_722_; uint64_t v___x_723_; uint8_t v___x_724_; 
v___x_722_ = 4ULL;
v___x_723_ = lean_uint64_shift_right(v___y_720_, v___x_722_);
v___x_724_ = lean_uint64_dec_eq(v___x_723_, v___y_718_);
if (v___x_724_ == 0)
{
v___y_702_ = v___y_721_;
v___y_703_ = v___y_715_;
v___y_704_ = v___y_716_;
v___y_705_ = v___y_717_;
v___y_706_ = v___y_718_;
v___y_707_ = v___x_722_;
v___y_708_ = v___y_720_;
v___y_709_ = v___y_719_;
v___y_710_ = v___x_723_;
goto v___jp_701_;
}
else
{
v___y_702_ = v___y_721_;
v___y_703_ = v___y_715_;
v___y_704_ = v___y_716_;
v___y_705_ = v___y_717_;
v___y_706_ = v___y_718_;
v___y_707_ = v___x_722_;
v___y_708_ = v___y_720_;
v___y_709_ = v___y_719_;
v___y_710_ = v___y_720_;
goto v___jp_701_;
}
}
v___jp_725_:
{
uint64_t v___x_735_; uint8_t v___x_736_; 
v___x_735_ = lean_uint64_shift_right(v___y_732_, v___y_727_);
v___x_736_ = lean_uint64_dec_eq(v___x_735_, v___y_730_);
if (v___x_736_ == 0)
{
uint64_t v___x_737_; 
v___x_737_ = lean_uint64_add(v___y_731_, v___y_727_);
v___y_715_ = v___y_726_;
v___y_716_ = v___y_728_;
v___y_717_ = v___y_729_;
v___y_718_ = v___y_730_;
v___y_719_ = v___y_733_;
v___y_720_ = v___y_734_;
v___y_721_ = v___x_737_;
goto v___jp_714_;
}
else
{
v___y_715_ = v___y_726_;
v___y_716_ = v___y_728_;
v___y_717_ = v___y_729_;
v___y_718_ = v___y_730_;
v___y_719_ = v___y_733_;
v___y_720_ = v___y_734_;
v___y_721_ = v___y_731_;
goto v___jp_714_;
}
}
v___jp_738_:
{
uint64_t v___x_746_; uint64_t v___x_747_; uint8_t v___x_748_; 
v___x_746_ = 8ULL;
v___x_747_ = lean_uint64_shift_right(v___y_744_, v___x_746_);
v___x_748_ = lean_uint64_dec_eq(v___x_747_, v___y_742_);
if (v___x_748_ == 0)
{
v___y_726_ = v___y_739_;
v___y_727_ = v___x_746_;
v___y_728_ = v___y_740_;
v___y_729_ = v___y_741_;
v___y_730_ = v___y_742_;
v___y_731_ = v___y_745_;
v___y_732_ = v___y_744_;
v___y_733_ = v___y_743_;
v___y_734_ = v___x_747_;
goto v___jp_725_;
}
else
{
v___y_726_ = v___y_739_;
v___y_727_ = v___x_746_;
v___y_728_ = v___y_740_;
v___y_729_ = v___y_741_;
v___y_730_ = v___y_742_;
v___y_731_ = v___y_745_;
v___y_732_ = v___y_744_;
v___y_733_ = v___y_743_;
v___y_734_ = v___y_744_;
goto v___jp_725_;
}
}
v___jp_749_:
{
uint64_t v___x_759_; uint8_t v___x_760_; 
v___x_759_ = lean_uint64_shift_right(v___y_755_, v___y_751_);
v___x_760_ = lean_uint64_dec_eq(v___x_759_, v___y_754_);
if (v___x_760_ == 0)
{
uint64_t v___x_761_; 
v___x_761_ = lean_uint64_add(v___y_756_, v___y_751_);
v___y_739_ = v___y_750_;
v___y_740_ = v___y_752_;
v___y_741_ = v___y_753_;
v___y_742_ = v___y_754_;
v___y_743_ = v___y_757_;
v___y_744_ = v___y_758_;
v___y_745_ = v___x_761_;
goto v___jp_738_;
}
else
{
v___y_739_ = v___y_750_;
v___y_740_ = v___y_752_;
v___y_741_ = v___y_753_;
v___y_742_ = v___y_754_;
v___y_743_ = v___y_757_;
v___y_744_ = v___y_758_;
v___y_745_ = v___y_756_;
goto v___jp_738_;
}
}
v___jp_762_:
{
uint64_t v___x_770_; uint64_t v___x_771_; uint8_t v___x_772_; 
v___x_770_ = 16ULL;
v___x_771_ = lean_uint64_shift_right(v___y_767_, v___x_770_);
v___x_772_ = lean_uint64_dec_eq(v___x_771_, v___y_766_);
if (v___x_772_ == 0)
{
v___y_750_ = v___y_763_;
v___y_751_ = v___x_770_;
v___y_752_ = v___y_764_;
v___y_753_ = v___y_765_;
v___y_754_ = v___y_766_;
v___y_755_ = v___y_767_;
v___y_756_ = v___y_769_;
v___y_757_ = v___y_768_;
v___y_758_ = v___x_771_;
goto v___jp_749_;
}
else
{
v___y_750_ = v___y_763_;
v___y_751_ = v___x_770_;
v___y_752_ = v___y_764_;
v___y_753_ = v___y_765_;
v___y_754_ = v___y_766_;
v___y_755_ = v___y_767_;
v___y_756_ = v___y_769_;
v___y_757_ = v___y_768_;
v___y_758_ = v___y_767_;
goto v___jp_749_;
}
}
v___jp_773_:
{
uint64_t v___x_781_; uint8_t v___x_782_; 
v___x_781_ = lean_uint64_shift_right(v___y_779_, v___y_778_);
v___x_782_ = lean_uint64_dec_eq(v___x_781_, v___y_777_);
if (v___x_782_ == 0)
{
v___y_763_ = v___y_774_;
v___y_764_ = v___y_775_;
v___y_765_ = v___y_776_;
v___y_766_ = v___y_777_;
v___y_767_ = v___y_780_;
v___y_768_ = v___y_779_;
v___y_769_ = v___y_778_;
goto v___jp_762_;
}
else
{
v___y_763_ = v___y_774_;
v___y_764_ = v___y_775_;
v___y_765_ = v___y_776_;
v___y_766_ = v___y_777_;
v___y_767_ = v___y_780_;
v___y_768_ = v___y_779_;
v___y_769_ = v___y_777_;
goto v___jp_762_;
}
}
v___jp_783_:
{
uint64_t v___x_788_; uint8_t v___x_789_; 
v___x_788_ = 0ULL;
v___x_789_ = lean_uint64_dec_eq(v___y_787_, v___x_788_);
if (v___x_789_ == 0)
{
uint64_t v___x_790_; uint64_t v___x_791_; uint8_t v___x_792_; 
v___x_790_ = 32ULL;
v___x_791_ = lean_uint64_shift_right(v___y_787_, v___x_790_);
v___x_792_ = lean_uint64_dec_eq(v___x_791_, v___x_788_);
if (v___x_792_ == 0)
{
v___y_774_ = v___y_784_;
v___y_775_ = v___y_785_;
v___y_776_ = v___y_786_;
v___y_777_ = v___x_788_;
v___y_778_ = v___x_790_;
v___y_779_ = v___y_787_;
v___y_780_ = v___x_791_;
goto v___jp_773_;
}
else
{
v___y_774_ = v___y_784_;
v___y_775_ = v___y_785_;
v___y_776_ = v___y_786_;
v___y_777_ = v___x_788_;
v___y_778_ = v___x_790_;
v___y_779_ = v___y_787_;
v___y_780_ = v___y_787_;
goto v___jp_773_;
}
}
else
{
if (v___y_784_ == 0)
{
uint32_t v___x_793_; 
v___x_793_ = 0;
return v___x_793_;
}
else
{
uint32_t v___x_794_; 
v___x_794_ = 2147483648;
return v___x_794_;
}
}
}
v___jp_795_:
{
uint64_t v___x_802_; uint64_t v___x_803_; uint64_t v___x_804_; uint8_t v___x_805_; 
v___x_802_ = lean_uint64_mul(v___y_797_, v___y_800_);
v___x_803_ = lean_uint64_add(v___y_799_, v___y_801_);
v___x_804_ = 281474976710656ULL;
v___x_805_ = lean_uint64_dec_lt(v___x_802_, v___x_804_);
if (v___x_805_ == 0)
{
v___y_784_ = v___y_796_;
v___y_785_ = v___y_798_;
v___y_786_ = v___x_803_;
v___y_787_ = v___x_802_;
goto v___jp_783_;
}
else
{
uint64_t v___x_806_; uint8_t v___x_807_; 
v___x_806_ = 123ULL;
v___x_807_ = lean_uint64_dec_le(v___x_803_, v___x_806_);
if (v___x_807_ == 0)
{
v___y_784_ = v___y_796_;
v___y_785_ = v___y_798_;
v___y_786_ = v___x_803_;
v___y_787_ = v___x_802_;
goto v___jp_783_;
}
else
{
uint64_t v___x_808_; uint8_t v___x_809_; 
v___x_808_ = 0ULL;
v___x_809_ = lean_uint64_dec_eq(v___x_802_, v___x_808_);
if (v___x_809_ == 0)
{
uint64_t v___x_810_; uint64_t v___x_811_; uint8_t v___x_812_; 
v___x_810_ = 149ULL;
v___x_811_ = lean_uint64_sub(v___x_810_, v___x_803_);
v___x_812_ = lean_uint64_dec_eq(v___x_811_, v___x_808_);
if (v___x_812_ == 0)
{
uint64_t v___x_813_; uint8_t v___x_814_; 
v___x_813_ = 64ULL;
v___x_814_ = lean_uint64_dec_lt(v___x_811_, v___x_813_);
if (v___x_814_ == 0)
{
uint8_t v___x_815_; 
v___x_815_ = lean_uint64_dec_eq(v___x_811_, v___x_813_);
if (v___x_815_ == 0)
{
v___y_535_ = v___y_796_;
v___y_536_ = v___y_798_;
v___y_537_ = v___x_808_;
v___y_538_ = v___x_808_;
goto v___jp_534_;
}
else
{
uint64_t v___x_816_; uint8_t v___x_817_; 
v___x_816_ = 9223372036854775808ULL;
v___x_817_ = lean_uint64_dec_lt(v___x_816_, v___x_802_);
if (v___x_817_ == 0)
{
v___y_535_ = v___y_796_;
v___y_536_ = v___y_798_;
v___y_537_ = v___x_808_;
v___y_538_ = v___x_808_;
goto v___jp_534_;
}
else
{
uint64_t v___x_818_; 
v___x_818_ = 1ULL;
v___y_535_ = v___y_796_;
v___y_536_ = v___y_798_;
v___y_537_ = v___x_808_;
v___y_538_ = v___x_818_;
goto v___jp_534_;
}
}
}
else
{
uint64_t v_quotient_819_; uint64_t v___x_820_; uint64_t v___x_821_; uint64_t v___x_822_; uint64_t v_remainder_823_; uint64_t v___x_824_; uint64_t v_half_825_; uint8_t v___x_826_; 
v_quotient_819_ = lean_uint64_shift_right(v___x_802_, v___x_811_);
v___x_820_ = 1ULL;
v___x_821_ = lean_uint64_shift_left(v___x_820_, v___x_811_);
v___x_822_ = lean_uint64_sub(v___x_821_, v___x_820_);
v_remainder_823_ = lean_uint64_land(v___x_802_, v___x_822_);
v___x_824_ = lean_uint64_sub(v___x_811_, v___x_820_);
v_half_825_ = lean_uint64_shift_left(v___x_820_, v___x_824_);
v___x_826_ = lean_uint64_dec_lt(v_remainder_823_, v_half_825_);
if (v___x_826_ == 0)
{
uint8_t v___x_827_; 
v___x_827_ = lean_uint64_dec_lt(v_half_825_, v_remainder_823_);
if (v___x_827_ == 0)
{
uint64_t v___x_828_; uint8_t v___x_829_; 
v___x_828_ = lean_uint64_land(v_quotient_819_, v___x_820_);
v___x_829_ = lean_uint64_dec_eq(v___x_828_, v___x_808_);
if (v___x_829_ == 0)
{
uint64_t v___x_830_; 
v___x_830_ = lean_uint64_add(v_quotient_819_, v___x_820_);
v___y_535_ = v___y_796_;
v___y_536_ = v___y_798_;
v___y_537_ = v___x_808_;
v___y_538_ = v___x_830_;
goto v___jp_534_;
}
else
{
v___y_535_ = v___y_796_;
v___y_536_ = v___y_798_;
v___y_537_ = v___x_808_;
v___y_538_ = v_quotient_819_;
goto v___jp_534_;
}
}
else
{
uint64_t v___x_831_; 
v___x_831_ = lean_uint64_add(v_quotient_819_, v___x_820_);
v___y_535_ = v___y_796_;
v___y_536_ = v___y_798_;
v___y_537_ = v___x_808_;
v___y_538_ = v___x_831_;
goto v___jp_534_;
}
}
else
{
v___y_535_ = v___y_796_;
v___y_536_ = v___y_798_;
v___y_537_ = v___x_808_;
v___y_538_ = v_quotient_819_;
goto v___jp_534_;
}
}
}
else
{
v___y_535_ = v___y_796_;
v___y_536_ = v___y_798_;
v___y_537_ = v___x_808_;
v___y_538_ = v___x_802_;
goto v___jp_534_;
}
}
else
{
if (v___y_796_ == 0)
{
uint32_t v___x_832_; 
v___x_832_ = 0;
return v___x_832_;
}
else
{
uint32_t v___x_833_; 
v___x_833_ = 2147483648;
return v___x_833_;
}
}
}
}
}
v___jp_837_:
{
uint64_t v___x_843_; uint64_t v___x_844_; uint8_t v___x_845_; 
v___x_843_ = lean_uint32_to_uint64(v_ey_836_);
v___x_844_ = 0ULL;
v___x_845_ = lean_uint64_dec_eq(v___x_843_, v___x_844_);
if (v___x_845_ == 0)
{
uint64_t v___x_846_; uint64_t v___x_847_; 
v___x_846_ = 1ULL;
v___x_847_ = lean_uint64_sub(v___x_843_, v___x_846_);
v___y_796_ = v___y_839_;
v___y_797_ = v___y_838_;
v___y_798_ = v___y_840_;
v___y_799_ = v___y_842_;
v___y_800_ = v___y_841_;
v___y_801_ = v___x_847_;
goto v___jp_795_;
}
else
{
v___y_796_ = v___y_839_;
v___y_797_ = v___y_838_;
v___y_798_ = v___y_840_;
v___y_799_ = v___y_842_;
v___y_800_ = v___y_841_;
v___y_801_ = v___x_844_;
goto v___jp_795_;
}
}
v___jp_848_:
{
uint64_t v___x_853_; uint64_t v___x_854_; uint8_t v___x_855_; 
v___x_853_ = lean_uint32_to_uint64(v_ex_834_);
v___x_854_ = 0ULL;
v___x_855_ = lean_uint64_dec_eq(v___x_853_, v___x_854_);
if (v___x_855_ == 0)
{
uint64_t v___x_856_; uint64_t v___x_857_; 
v___x_856_ = 1ULL;
v___x_857_ = lean_uint64_sub(v___x_853_, v___x_856_);
v___y_838_ = v___y_850_;
v___y_839_ = v___y_849_;
v___y_840_ = v___y_851_;
v___y_841_ = v___y_852_;
v___y_842_ = v___x_857_;
goto v___jp_837_;
}
else
{
v___y_838_ = v___y_850_;
v___y_839_ = v___y_849_;
v___y_840_ = v___y_851_;
v___y_841_ = v___y_852_;
v___y_842_ = v___x_854_;
goto v___jp_837_;
}
}
v___jp_858_:
{
uint32_t v___x_863_; uint8_t v___x_864_; 
v___x_863_ = 0;
v___x_864_ = lean_uint32_dec_eq(v_ey_836_, v___x_863_);
if (v___x_864_ == 0)
{
uint64_t v___x_865_; uint64_t v___x_866_; uint64_t v___x_867_; 
v___x_865_ = lean_uint32_to_uint64(v___y_861_);
v___x_866_ = 8388608ULL;
v___x_867_ = lean_uint64_lor(v___x_865_, v___x_866_);
v___y_849_ = v___y_859_;
v___y_850_ = v___y_862_;
v___y_851_ = v___y_860_;
v___y_852_ = v___x_867_;
goto v___jp_848_;
}
else
{
uint64_t v___x_868_; 
v___x_868_ = lean_uint32_to_uint64(v___y_861_);
v___y_849_ = v___y_859_;
v___y_850_ = v___y_862_;
v___y_851_ = v___y_860_;
v___y_852_ = v___x_868_;
goto v___jp_848_;
}
}
v___jp_869_:
{
uint32_t v___x_871_; uint32_t v_xFraction_872_; uint32_t v_yFraction_873_; uint32_t v___x_874_; uint8_t v___x_875_; 
v___x_871_ = 8388607;
v_xFraction_872_ = lean_uint32_land(v___y_497_, v___x_871_);
v_yFraction_873_ = lean_uint32_land(v___y_498_, v___x_871_);
v___x_874_ = 0;
v___x_875_ = lean_uint32_dec_eq(v_ex_834_, v___x_874_);
if (v___x_875_ == 0)
{
uint64_t v___x_876_; uint64_t v___x_877_; uint64_t v___x_878_; 
v___x_876_ = lean_uint32_to_uint64(v_xFraction_872_);
v___x_877_ = 8388608ULL;
v___x_878_ = lean_uint64_lor(v___x_876_, v___x_877_);
v___y_859_ = v___y_870_;
v___y_860_ = v___x_871_;
v___y_861_ = v_yFraction_873_;
v___y_862_ = v___x_878_;
goto v___jp_858_;
}
else
{
uint64_t v___x_879_; 
v___x_879_ = lean_uint32_to_uint64(v_xFraction_872_);
v___y_859_ = v___y_870_;
v___y_860_ = v___x_871_;
v___y_861_ = v_yFraction_873_;
v___y_862_ = v___x_879_;
goto v___jp_858_;
}
}
v___jp_883_:
{
if (v___y_885_ == 0)
{
v___y_870_ = v___x_882_;
goto v___jp_869_;
}
else
{
v___y_870_ = v___y_884_;
goto v___jp_869_;
}
}
v___jp_886_:
{
if (v___y_888_ == 0)
{
if (v___y_889_ == 0)
{
v___y_884_ = v___y_887_;
v___y_885_ = v___x_882_;
goto v___jp_883_;
}
else
{
v___y_870_ = v___x_882_;
goto v___jp_869_;
}
}
else
{
v___y_884_ = v___y_887_;
v___y_885_ = v___y_889_;
goto v___jp_883_;
}
}
v___jp_890_:
{
uint32_t v___x_893_; uint32_t v___x_894_; uint32_t v___x_895_; uint8_t v___x_896_; 
v___x_893_ = 2147483648;
v___x_894_ = lean_uint32_land(v___y_498_, v___x_893_);
v___x_895_ = 0;
v___x_896_ = lean_uint32_dec_eq(v___x_894_, v___x_895_);
if (v___x_896_ == 0)
{
v___y_887_ = v___y_891_;
v___y_888_ = v___y_892_;
v___y_889_ = v___x_882_;
goto v___jp_886_;
}
else
{
v___y_887_ = v___y_891_;
v___y_888_ = v___y_892_;
v___y_889_ = v___y_891_;
goto v___jp_886_;
}
}
v___jp_897_:
{
if (v___y_898_ == 0)
{
uint32_t v___x_899_; uint32_t v___x_900_; uint32_t v___x_901_; uint8_t v___x_902_; 
v___x_899_ = 2147483648;
v___x_900_ = lean_uint32_land(v___y_497_, v___x_899_);
v___x_901_ = 0;
v___x_902_ = lean_uint32_dec_eq(v___x_900_, v___x_901_);
if (v___x_902_ == 0)
{
v___y_891_ = v___y_898_;
v___y_892_ = v___x_882_;
goto v___jp_890_;
}
else
{
v___y_891_ = v___y_898_;
v___y_892_ = v___y_898_;
goto v___jp_890_;
}
}
else
{
lean_object* v___x_903_; lean_object* v___x_904_; lean_object* v___x_905_; uint32_t v___x_906_; 
v___x_903_ = lean_uint32_to_nat(v___y_497_);
v___x_904_ = lean_uint32_to_nat(v___y_498_);
v___x_905_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_903_, v___x_904_);
v___x_906_ = lean_uint32_of_nat(v___x_905_);
lean_dec(v___x_905_);
return v___x_906_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_919_, lean_object* v___y_920_){
_start:
{
uint32_t v___y_4671__boxed_921_; uint32_t v___y_4672__boxed_922_; uint32_t v_res_923_; lean_object* v_r_924_; 
v___y_4671__boxed_921_ = lean_unbox_uint32(v___y_919_);
lean_dec(v___y_919_);
v___y_4672__boxed_922_ = lean_unbox_uint32(v___y_920_);
lean_dec(v___y_920_);
v_res_923_ = lp_competition_main___lam__3(v___y_4671__boxed_921_, v___y_4672__boxed_922_);
v_r_924_ = lean_box_uint32(v_res_923_);
return v_r_924_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_932_; lean_object* v___x_933_; 
v___x_932_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_933_ = lean_io_getenv(v___x_932_);
if (lean_obj_tag(v___x_933_) == 0)
{
lean_object* v___f_934_; lean_object* v___f_935_; lean_object* v___x_936_; lean_object* v___x_937_; lean_object* v___x_938_; 
v___f_934_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_935_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_936_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_937_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_938_ = lp_competition_Bench_runFull(v___f_934_, v___f_935_, v___x_936_, v___x_937_);
return v___x_938_;
}
else
{
lean_object* v___f_939_; lean_object* v___f_940_; lean_object* v___x_941_; lean_object* v___x_942_; lean_object* v___x_943_; 
lean_dec_ref_known(v___x_933_, 1);
v___f_939_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_940_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_941_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_942_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_943_ = lp_competition_Bench_Suite_run(v___f_939_, v___f_940_, v___x_941_, v___x_942_);
return v___x_943_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_944_){
_start:
{
lean_object* v_res_945_; 
v_res_945_ = _lean_main();
return v_res_945_;
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
