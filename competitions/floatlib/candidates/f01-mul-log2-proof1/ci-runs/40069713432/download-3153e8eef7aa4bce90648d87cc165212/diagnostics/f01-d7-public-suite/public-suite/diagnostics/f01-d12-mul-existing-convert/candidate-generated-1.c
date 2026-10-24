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
uint32_t lp_competition_Submission_TunedAdd_add(uint32_t, uint32_t);
uint32_t lean_float32_to_bits(float);
float lean_float32_of_bits(uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
lean_object* lean_uint32_to_nat(uint32_t);
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
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
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
float v___y_4_; float v___y_5_; float v___y_11_; uint8_t v___y_12_; float v___y_27_; uint8_t v___y_37_; uint32_t v___x_51_; uint32_t v_a_52_; uint32_t v___x_53_; uint32_t v___x_54_; uint32_t v___x_55_; uint8_t v___x_56_; 
v___x_51_ = 2147483647;
v_a_52_ = lean_uint32_land(v___y_1_, v___x_51_);
v___x_53_ = 201326591;
v___x_54_ = 1;
v___x_55_ = lean_uint32_sub(v_a_52_, v___x_54_);
v___x_56_ = lean_uint32_dec_le(v___x_53_, v___x_55_);
if (v___x_56_ == 0)
{
v___y_37_ = v___x_56_;
goto v___jp_36_;
}
else
{
uint32_t v___x_57_; uint8_t v___x_58_; 
v___x_57_ = 2139095040;
v___x_58_ = lean_uint32_dec_lt(v_a_52_, v___x_57_);
v___y_37_ = v___x_58_;
goto v___jp_36_;
}
v___jp_3_:
{
float v_result_6_; uint8_t v___x_7_; 
v_result_6_ = lean_float32_add(v___y_4_, v___y_5_);
v___x_7_ = lean_float32_beq(v_result_6_, v_result_6_);
if (v___x_7_ == 0)
{
uint32_t v___x_8_; 
v___x_8_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_8_;
}
else
{
uint32_t v___x_9_; 
v___x_9_ = lean_float32_to_bits(v_result_6_);
return v___x_9_;
}
}
v___jp_10_:
{
if (v___y_12_ == 0)
{
float v___x_13_; 
v___x_13_ = lean_float32_of_bits(v___y_2_);
v___y_4_ = v___y_11_;
v___y_5_ = v___x_13_;
goto v___jp_3_;
}
else
{
uint32_t v___x_14_; uint32_t v___x_15_; uint32_t v___x_16_; uint32_t v___x_17_; float v___x_18_; lean_object* v___x_19_; uint32_t v___x_20_; uint32_t v___x_21_; lean_object* v___x_22_; lean_object* v___x_23_; float v___x_24_; float v___x_25_; 
v___x_14_ = 8388607;
v___x_15_ = lean_uint32_land(v___y_2_, v___x_14_);
v___x_16_ = 8388608;
v___x_17_ = lean_uint32_lor(v___x_15_, v___x_16_);
v___x_18_ = lean_uint32_to_float32(v___x_17_);
v___x_19_ = lp_competition_R2W01b_scaleTable;
v___x_20_ = 23;
v___x_21_ = lean_uint32_shift_right(v___y_2_, v___x_20_);
v___x_22_ = lean_uint32_to_nat(v___x_21_);
v___x_23_ = lean_array_fget_borrowed(v___x_19_, v___x_22_);
lean_dec(v___x_22_);
v___x_24_ = lean_unbox_float32(v___x_23_);
v___x_25_ = lean_float32_mul(v___x_18_, v___x_24_);
v___y_4_ = v___y_11_;
v___y_5_ = v___x_25_;
goto v___jp_3_;
}
}
v___jp_26_:
{
uint32_t v___x_28_; uint32_t v_a_29_; uint32_t v___x_30_; uint32_t v___x_31_; uint32_t v___x_32_; uint8_t v___x_33_; 
v___x_28_ = 2147483647;
v_a_29_ = lean_uint32_land(v___y_2_, v___x_28_);
v___x_30_ = 201326591;
v___x_31_ = 1;
v___x_32_ = lean_uint32_sub(v_a_29_, v___x_31_);
v___x_33_ = lean_uint32_dec_le(v___x_30_, v___x_32_);
if (v___x_33_ == 0)
{
v___y_11_ = v___y_27_;
v___y_12_ = v___x_33_;
goto v___jp_10_;
}
else
{
uint32_t v___x_34_; uint8_t v___x_35_; 
v___x_34_ = 2139095040;
v___x_35_ = lean_uint32_dec_lt(v_a_29_, v___x_34_);
v___y_11_ = v___y_27_;
v___y_12_ = v___x_35_;
goto v___jp_10_;
}
}
v___jp_36_:
{
if (v___y_37_ == 0)
{
float v___x_38_; 
v___x_38_ = lean_float32_of_bits(v___y_1_);
v___y_27_ = v___x_38_;
goto v___jp_26_;
}
else
{
uint32_t v___x_39_; uint32_t v___x_40_; uint32_t v___x_41_; uint32_t v___x_42_; float v___x_43_; lean_object* v___x_44_; uint32_t v___x_45_; uint32_t v___x_46_; lean_object* v___x_47_; lean_object* v___x_48_; float v___x_49_; float v___x_50_; 
v___x_39_ = 8388607;
v___x_40_ = lean_uint32_land(v___y_1_, v___x_39_);
v___x_41_ = 8388608;
v___x_42_ = lean_uint32_lor(v___x_40_, v___x_41_);
v___x_43_ = lean_uint32_to_float32(v___x_42_);
v___x_44_ = lp_competition_R2W01b_scaleTable;
v___x_45_ = 23;
v___x_46_ = lean_uint32_shift_right(v___y_1_, v___x_45_);
v___x_47_ = lean_uint32_to_nat(v___x_46_);
v___x_48_ = lean_array_fget_borrowed(v___x_44_, v___x_47_);
lean_dec(v___x_47_);
v___x_49_ = lean_unbox_float32(v___x_48_);
v___x_50_ = lean_float32_mul(v___x_43_, v___x_49_);
v___y_27_ = v___x_50_;
goto v___jp_26_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_59_, lean_object* v___y_60_){
_start:
{
uint32_t v___y_3225__boxed_61_; uint32_t v___y_3226__boxed_62_; uint32_t v_res_63_; lean_object* v_r_64_; 
v___y_3225__boxed_61_ = lean_unbox_uint32(v___y_59_);
lean_dec(v___y_59_);
v___y_3226__boxed_62_ = lean_unbox_uint32(v___y_60_);
lean_dec(v___y_60_);
v_res_63_ = lp_competition_main___lam__0(v___y_3225__boxed_61_, v___y_3226__boxed_62_);
v_r_64_ = lean_box_uint32(v_res_63_);
return v_r_64_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_65_, uint32_t v___y_66_){
_start:
{
uint32_t v___y_68_; uint32_t v___y_69_; uint32_t v___y_70_; uint32_t v___y_74_; uint32_t v___y_75_; uint32_t v___y_76_; uint32_t v___y_80_; uint8_t v___y_84_; uint64_t v___y_85_; uint32_t v___y_86_; uint64_t v___y_87_; uint32_t v___y_99_; uint8_t v___y_103_; uint64_t v___y_104_; uint32_t v___y_105_; uint64_t v___y_106_; float v___y_118_; float v___y_119_; float v___y_125_; uint8_t v___y_126_; float v___y_141_; uint32_t v___x_150_; uint32_t v___x_151_; uint8_t v___y_153_; uint32_t v___x_165_; uint32_t v___y_167_; uint32_t v___y_168_; uint32_t v___y_169_; uint32_t v___y_170_; uint32_t v___y_177_; uint8_t v___y_178_; uint32_t v___y_179_; uint32_t v___y_180_; uint8_t v___y_184_; uint64_t v___y_185_; uint32_t v___y_186_; uint64_t v___y_187_; uint64_t v___y_188_; uint8_t v___y_198_; uint8_t v___y_199_; uint64_t v___y_200_; uint32_t v___y_201_; uint64_t v___y_202_; uint64_t v___y_203_; uint8_t v___y_210_; uint64_t v___y_211_; uint32_t v___y_212_; uint64_t v___y_213_; uint64_t v___y_214_; uint64_t v___y_220_; uint64_t v___y_221_; uint8_t v___y_222_; uint64_t v___y_223_; uint32_t v___y_224_; uint64_t v___y_225_; uint64_t v___y_280_; uint64_t v___y_281_; uint64_t v___y_282_; uint8_t v___y_283_; uint64_t v___y_284_; uint32_t v___y_285_; uint64_t v___y_286_; uint64_t v___y_292_; uint64_t v___y_293_; uint8_t v___y_294_; uint64_t v___y_295_; uint64_t v___y_296_; uint64_t v___y_297_; uint64_t v___y_298_; uint32_t v___y_299_; uint64_t v___y_300_; uint64_t v___y_305_; uint64_t v___y_306_; uint8_t v___y_307_; uint64_t v___y_308_; uint64_t v___y_309_; uint32_t v___y_310_; uint64_t v___y_311_; uint64_t v___y_316_; uint64_t v___y_317_; uint64_t v___y_318_; uint8_t v___y_319_; uint64_t v___y_320_; uint64_t v___y_321_; uint64_t v___y_322_; uint32_t v___y_323_; uint64_t v___y_324_; uint64_t v___y_329_; uint64_t v___y_330_; uint8_t v___y_331_; uint64_t v___y_332_; uint64_t v___y_333_; uint32_t v___y_334_; uint64_t v___y_335_; uint64_t v___y_340_; uint64_t v___y_341_; uint64_t v___y_342_; uint8_t v___y_343_; uint64_t v___y_344_; uint64_t v___y_345_; uint64_t v___y_346_; uint32_t v___y_347_; uint64_t v___y_348_; uint64_t v___y_353_; uint64_t v___y_354_; uint8_t v___y_355_; uint64_t v___y_356_; uint64_t v___y_357_; uint32_t v___y_358_; uint64_t v___y_359_; uint64_t v___y_364_; uint64_t v___y_365_; uint8_t v___y_366_; uint64_t v___y_367_; uint64_t v___y_368_; uint32_t v___y_369_; uint64_t v___y_370_; uint64_t v___y_371_; uint64_t v___y_372_; uint64_t v___y_377_; uint64_t v___y_378_; uint8_t v___y_379_; uint64_t v___y_380_; uint32_t v___y_381_; uint64_t v___y_382_; uint64_t v___y_383_; uint64_t v___y_388_; uint64_t v___y_389_; uint8_t v___y_390_; uint64_t v___y_391_; uint64_t v___y_392_; uint32_t v___y_393_; uint64_t v___y_394_; uint64_t v___y_398_; uint64_t v___y_399_; uint8_t v___y_400_; uint32_t v___y_401_; uint8_t v___y_410_; uint64_t v___y_411_; uint64_t v___y_412_; uint32_t v___y_413_; uint64_t v___y_414_; uint64_t v___y_415_; uint32_t v_ex_448_; uint32_t v___x_449_; uint32_t v_ey_450_; uint8_t v___y_452_; uint64_t v___y_453_; uint32_t v___y_454_; uint64_t v___y_455_; uint64_t v___y_456_; uint8_t v___y_463_; uint64_t v___y_464_; uint32_t v___y_465_; uint64_t v___y_466_; uint32_t v___y_473_; uint8_t v___y_474_; uint32_t v___y_475_; uint64_t v___y_476_; uint8_t v___y_484_; uint32_t v___x_494_; uint32_t v___x_495_; uint8_t v___x_496_; uint8_t v___y_498_; uint8_t v___y_499_; uint8_t v___y_501_; uint8_t v___y_502_; uint8_t v___y_503_; uint8_t v___y_505_; uint8_t v___y_506_; uint8_t v___y_512_; 
v___x_150_ = 23;
v___x_151_ = lean_uint32_shift_right(v___y_65_, v___x_150_);
v___x_165_ = 255;
v_ex_448_ = lean_uint32_land(v___x_151_, v___x_165_);
v___x_449_ = lean_uint32_shift_right(v___y_66_, v___x_150_);
v_ey_450_ = lean_uint32_land(v___x_449_, v___x_165_);
v___x_494_ = lean_uint32_add(v_ex_448_, v_ey_450_);
v___x_495_ = 128;
v___x_496_ = lean_uint32_dec_lt(v___x_494_, v___x_495_);
if (v___x_496_ == 0)
{
uint32_t v___x_521_; uint32_t v_a_522_; uint32_t v___x_523_; uint32_t v___x_524_; uint32_t v___x_525_; uint8_t v___x_526_; 
v___x_521_ = 2147483647;
v_a_522_ = lean_uint32_land(v___y_65_, v___x_521_);
v___x_523_ = 201326591;
v___x_524_ = 1;
v___x_525_ = lean_uint32_sub(v_a_522_, v___x_524_);
v___x_526_ = lean_uint32_dec_le(v___x_523_, v___x_525_);
if (v___x_526_ == 0)
{
v___y_153_ = v___x_526_;
goto v___jp_152_;
}
else
{
uint32_t v___x_527_; uint8_t v___x_528_; 
v___x_527_ = 2139095040;
v___x_528_ = lean_uint32_dec_lt(v_a_522_, v___x_527_);
v___y_153_ = v___x_528_;
goto v___jp_152_;
}
}
else
{
uint32_t v___x_529_; uint32_t v___x_530_; uint32_t v___x_531_; uint8_t v___x_532_; 
v___x_529_ = 4278190080;
v___x_530_ = 1;
v___x_531_ = lean_uint32_shift_left(v___y_65_, v___x_530_);
v___x_532_ = lean_uint32_dec_le(v___x_529_, v___x_531_);
if (v___x_532_ == 0)
{
uint32_t v___x_533_; uint8_t v___x_534_; 
v___x_533_ = lean_uint32_shift_left(v___y_66_, v___x_530_);
v___x_534_ = lean_uint32_dec_le(v___x_529_, v___x_533_);
v___y_512_ = v___x_534_;
goto v___jp_511_;
}
else
{
v___y_512_ = v___x_532_;
goto v___jp_511_;
}
}
v___jp_67_:
{
uint32_t v___x_71_; uint32_t v___x_72_; 
v___x_71_ = lean_uint32_land(v___y_68_, v___y_69_);
v___x_72_ = lean_uint32_lor(v___y_70_, v___x_71_);
return v___x_72_;
}
v___jp_73_:
{
uint32_t v___x_77_; uint32_t v___x_78_; 
v___x_77_ = lean_uint32_land(v___y_74_, v___y_75_);
v___x_78_ = lean_uint32_lor(v___y_76_, v___x_77_);
return v___x_78_;
}
v___jp_79_:
{
uint32_t v___x_81_; uint32_t v___x_82_; 
v___x_81_ = 8388608;
v___x_82_ = lean_uint32_lor(v___y_80_, v___x_81_);
return v___x_82_;
}
v___jp_83_:
{
uint8_t v___x_88_; 
v___x_88_ = lean_uint64_dec_eq(v___y_87_, v___y_85_);
if (v___x_88_ == 0)
{
uint64_t v___x_89_; uint8_t v___x_90_; 
v___x_89_ = 8388608ULL;
v___x_90_ = lean_uint64_dec_eq(v___y_87_, v___x_89_);
if (v___x_90_ == 0)
{
uint32_t v___x_91_; 
v___x_91_ = lean_uint64_to_uint32(v___y_87_);
if (v___y_84_ == 0)
{
uint32_t v___x_92_; 
v___x_92_ = 0;
v___y_74_ = v___x_91_;
v___y_75_ = v___y_86_;
v___y_76_ = v___x_92_;
goto v___jp_73_;
}
else
{
uint32_t v___x_93_; 
v___x_93_ = 2147483648;
v___y_74_ = v___x_91_;
v___y_75_ = v___y_86_;
v___y_76_ = v___x_93_;
goto v___jp_73_;
}
}
else
{
if (v___y_84_ == 0)
{
uint32_t v___x_94_; 
v___x_94_ = 0;
v___y_80_ = v___x_94_;
goto v___jp_79_;
}
else
{
uint32_t v___x_95_; 
v___x_95_ = 2147483648;
v___y_80_ = v___x_95_;
goto v___jp_79_;
}
}
}
else
{
if (v___y_84_ == 0)
{
uint32_t v___x_96_; 
v___x_96_ = 0;
return v___x_96_;
}
else
{
uint32_t v___x_97_; 
v___x_97_ = 2147483648;
return v___x_97_;
}
}
}
v___jp_98_:
{
uint32_t v___x_100_; uint32_t v___x_101_; 
v___x_100_ = 8388608;
v___x_101_ = lean_uint32_lor(v___y_99_, v___x_100_);
return v___x_101_;
}
v___jp_102_:
{
uint8_t v___x_107_; 
v___x_107_ = lean_uint64_dec_eq(v___y_106_, v___y_104_);
if (v___x_107_ == 0)
{
uint64_t v___x_108_; uint8_t v___x_109_; 
v___x_108_ = 8388608ULL;
v___x_109_ = lean_uint64_dec_eq(v___y_106_, v___x_108_);
if (v___x_109_ == 0)
{
uint32_t v___x_110_; 
v___x_110_ = lean_uint64_to_uint32(v___y_106_);
if (v___y_103_ == 0)
{
uint32_t v___x_111_; 
v___x_111_ = 0;
v___y_68_ = v___x_110_;
v___y_69_ = v___y_105_;
v___y_70_ = v___x_111_;
goto v___jp_67_;
}
else
{
uint32_t v___x_112_; 
v___x_112_ = 2147483648;
v___y_68_ = v___x_110_;
v___y_69_ = v___y_105_;
v___y_70_ = v___x_112_;
goto v___jp_67_;
}
}
else
{
if (v___y_103_ == 0)
{
uint32_t v___x_113_; 
v___x_113_ = 0;
v___y_99_ = v___x_113_;
goto v___jp_98_;
}
else
{
uint32_t v___x_114_; 
v___x_114_ = 2147483648;
v___y_99_ = v___x_114_;
goto v___jp_98_;
}
}
}
else
{
if (v___y_103_ == 0)
{
uint32_t v___x_115_; 
v___x_115_ = 0;
return v___x_115_;
}
else
{
uint32_t v___x_116_; 
v___x_116_ = 2147483648;
return v___x_116_;
}
}
}
v___jp_117_:
{
float v_result_120_; uint8_t v___x_121_; 
v_result_120_ = lean_float32_mul(v___y_118_, v___y_119_);
v___x_121_ = lean_float32_beq(v_result_120_, v_result_120_);
if (v___x_121_ == 0)
{
uint32_t v___x_122_; 
v___x_122_ = lp_competition_Submission_FastMul_mul(v___y_65_, v___y_66_);
return v___x_122_;
}
else
{
uint32_t v___x_123_; 
v___x_123_ = lean_float32_to_bits(v_result_120_);
return v___x_123_;
}
}
v___jp_124_:
{
if (v___y_126_ == 0)
{
float v___x_127_; 
v___x_127_ = lean_float32_of_bits(v___y_66_);
v___y_118_ = v___y_125_;
v___y_119_ = v___x_127_;
goto v___jp_117_;
}
else
{
uint32_t v___x_128_; uint32_t v___x_129_; uint32_t v___x_130_; uint32_t v___x_131_; float v___x_132_; lean_object* v___x_133_; uint32_t v___x_134_; uint32_t v___x_135_; lean_object* v___x_136_; lean_object* v___x_137_; float v___x_138_; float v___x_139_; 
v___x_128_ = 8388607;
v___x_129_ = lean_uint32_land(v___y_66_, v___x_128_);
v___x_130_ = 8388608;
v___x_131_ = lean_uint32_lor(v___x_129_, v___x_130_);
v___x_132_ = lean_uint32_to_float32(v___x_131_);
v___x_133_ = lp_competition_R2W01b_scaleTable;
v___x_134_ = 23;
v___x_135_ = lean_uint32_shift_right(v___y_66_, v___x_134_);
v___x_136_ = lean_uint32_to_nat(v___x_135_);
v___x_137_ = lean_array_fget_borrowed(v___x_133_, v___x_136_);
lean_dec(v___x_136_);
v___x_138_ = lean_unbox_float32(v___x_137_);
v___x_139_ = lean_float32_mul(v___x_132_, v___x_138_);
v___y_118_ = v___y_125_;
v___y_119_ = v___x_139_;
goto v___jp_117_;
}
}
v___jp_140_:
{
uint32_t v___x_142_; uint32_t v_a_143_; uint32_t v___x_144_; uint32_t v___x_145_; uint32_t v___x_146_; uint8_t v___x_147_; 
v___x_142_ = 2147483647;
v_a_143_ = lean_uint32_land(v___y_66_, v___x_142_);
v___x_144_ = 201326591;
v___x_145_ = 1;
v___x_146_ = lean_uint32_sub(v_a_143_, v___x_145_);
v___x_147_ = lean_uint32_dec_le(v___x_144_, v___x_146_);
if (v___x_147_ == 0)
{
v___y_125_ = v___y_141_;
v___y_126_ = v___x_147_;
goto v___jp_124_;
}
else
{
uint32_t v___x_148_; uint8_t v___x_149_; 
v___x_148_ = 2139095040;
v___x_149_ = lean_uint32_dec_lt(v_a_143_, v___x_148_);
v___y_125_ = v___y_141_;
v___y_126_ = v___x_149_;
goto v___jp_124_;
}
}
v___jp_152_:
{
if (v___y_153_ == 0)
{
float v___x_154_; 
v___x_154_ = lean_float32_of_bits(v___y_65_);
v___y_141_ = v___x_154_;
goto v___jp_140_;
}
else
{
uint32_t v___x_155_; uint32_t v___x_156_; uint32_t v___x_157_; uint32_t v___x_158_; float v___x_159_; lean_object* v___x_160_; lean_object* v___x_161_; lean_object* v___x_162_; float v___x_163_; float v___x_164_; 
v___x_155_ = 8388607;
v___x_156_ = lean_uint32_land(v___y_65_, v___x_155_);
v___x_157_ = 8388608;
v___x_158_ = lean_uint32_lor(v___x_156_, v___x_157_);
v___x_159_ = lean_uint32_to_float32(v___x_158_);
v___x_160_ = lp_competition_R2W01b_scaleTable;
v___x_161_ = lean_uint32_to_nat(v___x_151_);
v___x_162_ = lean_array_fget_borrowed(v___x_160_, v___x_161_);
lean_dec(v___x_161_);
v___x_163_ = lean_unbox_float32(v___x_162_);
v___x_164_ = lean_float32_mul(v___x_159_, v___x_163_);
v___y_141_ = v___x_164_;
goto v___jp_140_;
}
}
v___jp_166_:
{
uint32_t v___x_171_; uint32_t v___x_172_; uint32_t v___x_173_; uint32_t v___x_174_; uint32_t v___x_175_; 
v___x_171_ = lean_uint32_land(v___y_168_, v___x_165_);
v___x_172_ = lean_uint32_shift_left(v___x_171_, v___x_150_);
v___x_173_ = lean_uint32_lor(v___y_170_, v___x_172_);
v___x_174_ = lean_uint32_land(v___y_167_, v___y_169_);
v___x_175_ = lean_uint32_lor(v___x_173_, v___x_174_);
return v___x_175_;
}
v___jp_176_:
{
if (v___y_178_ == 0)
{
uint32_t v___x_181_; 
v___x_181_ = 0;
v___y_167_ = v___y_180_;
v___y_168_ = v___y_177_;
v___y_169_ = v___y_179_;
v___y_170_ = v___x_181_;
goto v___jp_166_;
}
else
{
uint32_t v___x_182_; 
v___x_182_ = 2147483648;
v___y_167_ = v___y_180_;
v___y_168_ = v___y_177_;
v___y_169_ = v___y_179_;
v___y_170_ = v___x_182_;
goto v___jp_166_;
}
}
v___jp_183_:
{
uint64_t v___x_189_; uint64_t v_encodedExponent_190_; uint32_t v___x_191_; uint64_t v___x_192_; uint8_t v___x_193_; 
v___x_189_ = 171ULL;
v_encodedExponent_190_ = lean_uint64_sub(v___y_187_, v___x_189_);
v___x_191_ = lean_uint64_to_uint32(v_encodedExponent_190_);
v___x_192_ = 8388608ULL;
v___x_193_ = lean_uint64_dec_lt(v___y_188_, v___x_192_);
if (v___x_193_ == 0)
{
uint64_t v___x_194_; uint32_t v___x_195_; 
v___x_194_ = lean_uint64_sub(v___y_188_, v___x_192_);
v___x_195_ = lean_uint64_to_uint32(v___x_194_);
v___y_177_ = v___x_191_;
v___y_178_ = v___y_184_;
v___y_179_ = v___y_186_;
v___y_180_ = v___x_195_;
goto v___jp_176_;
}
else
{
uint32_t v___x_196_; 
v___x_196_ = lean_uint64_to_uint32(v___y_185_);
v___y_177_ = v___x_191_;
v___y_178_ = v___y_184_;
v___y_179_ = v___y_186_;
v___y_180_ = v___x_196_;
goto v___jp_176_;
}
}
v___jp_197_:
{
uint64_t v___x_204_; uint8_t v___x_205_; 
v___x_204_ = 425ULL;
v___x_205_ = lean_uint64_dec_lt(v___x_204_, v___y_203_);
if (v___x_205_ == 0)
{
if (v___y_198_ == 0)
{
v___y_184_ = v___y_199_;
v___y_185_ = v___y_200_;
v___y_186_ = v___y_201_;
v___y_187_ = v___y_203_;
v___y_188_ = v___y_202_;
goto v___jp_183_;
}
else
{
uint64_t v___x_206_; 
v___x_206_ = 8388608ULL;
v___y_184_ = v___y_199_;
v___y_185_ = v___y_200_;
v___y_186_ = v___y_201_;
v___y_187_ = v___y_203_;
v___y_188_ = v___x_206_;
goto v___jp_183_;
}
}
else
{
if (v___y_199_ == 0)
{
uint32_t v___x_207_; 
v___x_207_ = 2139095040;
return v___x_207_;
}
else
{
uint32_t v___x_208_; 
v___x_208_ = 4286578688;
return v___x_208_;
}
}
}
v___jp_209_:
{
uint64_t v___x_215_; uint8_t v_carry_216_; 
v___x_215_ = 16777216ULL;
v_carry_216_ = lean_uint64_dec_eq(v___y_214_, v___x_215_);
if (v_carry_216_ == 0)
{
v___y_198_ = v_carry_216_;
v___y_199_ = v___y_210_;
v___y_200_ = v___y_211_;
v___y_201_ = v___y_212_;
v___y_202_ = v___y_214_;
v___y_203_ = v___y_213_;
goto v___jp_197_;
}
else
{
uint64_t v___x_217_; uint64_t v___x_218_; 
v___x_217_ = 1ULL;
v___x_218_ = lean_uint64_add(v___y_213_, v___x_217_);
v___y_198_ = v_carry_216_;
v___y_199_ = v___y_210_;
v___y_200_ = v___y_211_;
v___y_201_ = v___y_212_;
v___y_202_ = v___y_214_;
v___y_203_ = v___x_218_;
goto v___jp_197_;
}
}
v___jp_219_:
{
uint64_t v_position_226_; uint64_t v___x_227_; uint8_t v___x_228_; 
v_position_226_ = lean_uint64_add(v___y_225_, v___y_220_);
v___x_227_ = 172ULL;
v___x_228_ = lean_uint64_dec_lt(v_position_226_, v___x_227_);
if (v___x_228_ == 0)
{
uint64_t v___x_229_; uint8_t v___x_230_; 
v___x_229_ = 23ULL;
v___x_230_ = lean_uint64_dec_lt(v___y_225_, v___x_229_);
if (v___x_230_ == 0)
{
uint64_t v___x_231_; uint8_t v___x_232_; 
v___x_231_ = lean_uint64_sub(v___y_225_, v___x_229_);
v___x_232_ = lean_uint64_dec_eq(v___x_231_, v___y_223_);
if (v___x_232_ == 0)
{
uint64_t v___x_233_; uint8_t v___x_234_; 
v___x_233_ = 64ULL;
v___x_234_ = lean_uint64_dec_lt(v___x_231_, v___x_233_);
if (v___x_234_ == 0)
{
uint8_t v___x_235_; 
v___x_235_ = lean_uint64_dec_eq(v___x_231_, v___x_233_);
if (v___x_235_ == 0)
{
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v___y_223_;
goto v___jp_209_;
}
else
{
uint64_t v___x_236_; uint8_t v___x_237_; 
v___x_236_ = 9223372036854775808ULL;
v___x_237_ = lean_uint64_dec_lt(v___x_236_, v___y_221_);
if (v___x_237_ == 0)
{
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v___y_223_;
goto v___jp_209_;
}
else
{
uint64_t v___x_238_; 
v___x_238_ = 1ULL;
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v___x_238_;
goto v___jp_209_;
}
}
}
else
{
uint64_t v_quotient_239_; uint64_t v___x_240_; uint64_t v___x_241_; uint64_t v___x_242_; uint64_t v_remainder_243_; uint64_t v___x_244_; uint64_t v_half_245_; uint8_t v___x_246_; 
v_quotient_239_ = lean_uint64_shift_right(v___y_221_, v___x_231_);
v___x_240_ = 1ULL;
v___x_241_ = lean_uint64_shift_left(v___x_240_, v___x_231_);
v___x_242_ = lean_uint64_sub(v___x_241_, v___x_240_);
v_remainder_243_ = lean_uint64_land(v___y_221_, v___x_242_);
v___x_244_ = lean_uint64_sub(v___x_231_, v___x_240_);
v_half_245_ = lean_uint64_shift_left(v___x_240_, v___x_244_);
v___x_246_ = lean_uint64_dec_lt(v_remainder_243_, v_half_245_);
if (v___x_246_ == 0)
{
uint8_t v___x_247_; 
v___x_247_ = lean_uint64_dec_lt(v_half_245_, v_remainder_243_);
if (v___x_247_ == 0)
{
uint64_t v___x_248_; uint8_t v___x_249_; 
v___x_248_ = lean_uint64_land(v_quotient_239_, v___x_240_);
v___x_249_ = lean_uint64_dec_eq(v___x_248_, v___y_223_);
if (v___x_249_ == 0)
{
uint64_t v___x_250_; 
v___x_250_ = lean_uint64_add(v_quotient_239_, v___x_240_);
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v___x_250_;
goto v___jp_209_;
}
else
{
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v_quotient_239_;
goto v___jp_209_;
}
}
else
{
uint64_t v___x_251_; 
v___x_251_ = lean_uint64_add(v_quotient_239_, v___x_240_);
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v___x_251_;
goto v___jp_209_;
}
}
else
{
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v_quotient_239_;
goto v___jp_209_;
}
}
}
else
{
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v___y_221_;
goto v___jp_209_;
}
}
else
{
uint64_t v___x_252_; uint64_t v___x_253_; 
v___x_252_ = lean_uint64_sub(v___x_229_, v___y_225_);
v___x_253_ = lean_uint64_shift_left(v___y_221_, v___x_252_);
v___y_210_ = v___y_222_;
v___y_211_ = v___y_223_;
v___y_212_ = v___y_224_;
v___y_213_ = v_position_226_;
v___y_214_ = v___x_253_;
goto v___jp_209_;
}
}
else
{
uint64_t v___x_254_; uint8_t v___x_255_; 
v___x_254_ = 149ULL;
v___x_255_ = lean_uint64_dec_lt(v___y_220_, v___x_254_);
if (v___x_255_ == 0)
{
uint64_t v___x_256_; uint64_t v___x_257_; 
v___x_256_ = lean_uint64_sub(v___y_220_, v___x_254_);
v___x_257_ = lean_uint64_shift_left(v___y_221_, v___x_256_);
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v___x_257_;
goto v___jp_83_;
}
else
{
uint64_t v___x_258_; uint8_t v___x_259_; 
v___x_258_ = lean_uint64_sub(v___x_254_, v___y_220_);
v___x_259_ = lean_uint64_dec_eq(v___x_258_, v___y_223_);
if (v___x_259_ == 0)
{
uint64_t v___x_260_; uint8_t v___x_261_; 
v___x_260_ = 64ULL;
v___x_261_ = lean_uint64_dec_lt(v___x_258_, v___x_260_);
if (v___x_261_ == 0)
{
uint8_t v___x_262_; 
v___x_262_ = lean_uint64_dec_eq(v___x_258_, v___x_260_);
if (v___x_262_ == 0)
{
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v___y_223_;
goto v___jp_83_;
}
else
{
uint64_t v___x_263_; uint8_t v___x_264_; 
v___x_263_ = 9223372036854775808ULL;
v___x_264_ = lean_uint64_dec_lt(v___x_263_, v___y_221_);
if (v___x_264_ == 0)
{
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v___y_223_;
goto v___jp_83_;
}
else
{
uint64_t v___x_265_; 
v___x_265_ = 1ULL;
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v___x_265_;
goto v___jp_83_;
}
}
}
else
{
uint64_t v_quotient_266_; uint64_t v___x_267_; uint64_t v___x_268_; uint64_t v___x_269_; uint64_t v_remainder_270_; uint64_t v___x_271_; uint64_t v_half_272_; uint8_t v___x_273_; 
v_quotient_266_ = lean_uint64_shift_right(v___y_221_, v___x_258_);
v___x_267_ = 1ULL;
v___x_268_ = lean_uint64_shift_left(v___x_267_, v___x_258_);
v___x_269_ = lean_uint64_sub(v___x_268_, v___x_267_);
v_remainder_270_ = lean_uint64_land(v___y_221_, v___x_269_);
v___x_271_ = lean_uint64_sub(v___x_258_, v___x_267_);
v_half_272_ = lean_uint64_shift_left(v___x_267_, v___x_271_);
v___x_273_ = lean_uint64_dec_lt(v_remainder_270_, v_half_272_);
if (v___x_273_ == 0)
{
uint8_t v___x_274_; 
v___x_274_ = lean_uint64_dec_lt(v_half_272_, v_remainder_270_);
if (v___x_274_ == 0)
{
uint64_t v___x_275_; uint8_t v___x_276_; 
v___x_275_ = lean_uint64_land(v_quotient_266_, v___x_267_);
v___x_276_ = lean_uint64_dec_eq(v___x_275_, v___y_223_);
if (v___x_276_ == 0)
{
uint64_t v___x_277_; 
v___x_277_ = lean_uint64_add(v_quotient_266_, v___x_267_);
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v___x_277_;
goto v___jp_83_;
}
else
{
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v_quotient_266_;
goto v___jp_83_;
}
}
else
{
uint64_t v___x_278_; 
v___x_278_ = lean_uint64_add(v_quotient_266_, v___x_267_);
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v___x_278_;
goto v___jp_83_;
}
}
else
{
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v_quotient_266_;
goto v___jp_83_;
}
}
}
else
{
v___y_84_ = v___y_222_;
v___y_85_ = v___y_223_;
v___y_86_ = v___y_224_;
v___y_87_ = v___y_221_;
goto v___jp_83_;
}
}
}
}
v___jp_279_:
{
uint64_t v___x_287_; uint64_t v___x_288_; uint8_t v___x_289_; 
v___x_287_ = 1ULL;
v___x_288_ = lean_uint64_shift_right(v___y_282_, v___x_287_);
v___x_289_ = lean_uint64_dec_eq(v___x_288_, v___y_284_);
if (v___x_289_ == 0)
{
uint64_t v___x_290_; 
v___x_290_ = lean_uint64_add(v___y_286_, v___x_287_);
v___y_220_ = v___y_280_;
v___y_221_ = v___y_281_;
v___y_222_ = v___y_283_;
v___y_223_ = v___y_284_;
v___y_224_ = v___y_285_;
v___y_225_ = v___x_290_;
goto v___jp_219_;
}
else
{
v___y_220_ = v___y_280_;
v___y_221_ = v___y_281_;
v___y_222_ = v___y_283_;
v___y_223_ = v___y_284_;
v___y_224_ = v___y_285_;
v___y_225_ = v___y_286_;
goto v___jp_219_;
}
}
v___jp_291_:
{
uint64_t v___x_301_; uint8_t v___x_302_; 
v___x_301_ = lean_uint64_shift_right(v___y_296_, v___y_295_);
v___x_302_ = lean_uint64_dec_eq(v___x_301_, v___y_297_);
if (v___x_302_ == 0)
{
uint64_t v___x_303_; 
v___x_303_ = lean_uint64_add(v___y_298_, v___y_295_);
v___y_280_ = v___y_292_;
v___y_281_ = v___y_293_;
v___y_282_ = v___y_300_;
v___y_283_ = v___y_294_;
v___y_284_ = v___y_297_;
v___y_285_ = v___y_299_;
v___y_286_ = v___x_303_;
goto v___jp_279_;
}
else
{
v___y_280_ = v___y_292_;
v___y_281_ = v___y_293_;
v___y_282_ = v___y_300_;
v___y_283_ = v___y_294_;
v___y_284_ = v___y_297_;
v___y_285_ = v___y_299_;
v___y_286_ = v___y_298_;
goto v___jp_279_;
}
}
v___jp_304_:
{
uint64_t v___x_312_; uint64_t v___x_313_; uint8_t v___x_314_; 
v___x_312_ = 2ULL;
v___x_313_ = lean_uint64_shift_right(v___y_308_, v___x_312_);
v___x_314_ = lean_uint64_dec_eq(v___x_313_, v___y_309_);
if (v___x_314_ == 0)
{
v___y_292_ = v___y_305_;
v___y_293_ = v___y_306_;
v___y_294_ = v___y_307_;
v___y_295_ = v___x_312_;
v___y_296_ = v___y_308_;
v___y_297_ = v___y_309_;
v___y_298_ = v___y_311_;
v___y_299_ = v___y_310_;
v___y_300_ = v___x_313_;
goto v___jp_291_;
}
else
{
v___y_292_ = v___y_305_;
v___y_293_ = v___y_306_;
v___y_294_ = v___y_307_;
v___y_295_ = v___x_312_;
v___y_296_ = v___y_308_;
v___y_297_ = v___y_309_;
v___y_298_ = v___y_311_;
v___y_299_ = v___y_310_;
v___y_300_ = v___y_308_;
goto v___jp_291_;
}
}
v___jp_315_:
{
uint64_t v___x_325_; uint8_t v___x_326_; 
v___x_325_ = lean_uint64_shift_right(v___y_321_, v___y_320_);
v___x_326_ = lean_uint64_dec_eq(v___x_325_, v___y_322_);
if (v___x_326_ == 0)
{
uint64_t v___x_327_; 
v___x_327_ = lean_uint64_add(v___y_317_, v___y_320_);
v___y_305_ = v___y_316_;
v___y_306_ = v___y_318_;
v___y_307_ = v___y_319_;
v___y_308_ = v___y_324_;
v___y_309_ = v___y_322_;
v___y_310_ = v___y_323_;
v___y_311_ = v___x_327_;
goto v___jp_304_;
}
else
{
v___y_305_ = v___y_316_;
v___y_306_ = v___y_318_;
v___y_307_ = v___y_319_;
v___y_308_ = v___y_324_;
v___y_309_ = v___y_322_;
v___y_310_ = v___y_323_;
v___y_311_ = v___y_317_;
goto v___jp_304_;
}
}
v___jp_328_:
{
uint64_t v___x_336_; uint64_t v___x_337_; uint8_t v___x_338_; 
v___x_336_ = 4ULL;
v___x_337_ = lean_uint64_shift_right(v___y_332_, v___x_336_);
v___x_338_ = lean_uint64_dec_eq(v___x_337_, v___y_333_);
if (v___x_338_ == 0)
{
v___y_316_ = v___y_329_;
v___y_317_ = v___y_335_;
v___y_318_ = v___y_330_;
v___y_319_ = v___y_331_;
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
v___y_317_ = v___y_335_;
v___y_318_ = v___y_330_;
v___y_319_ = v___y_331_;
v___y_320_ = v___x_336_;
v___y_321_ = v___y_332_;
v___y_322_ = v___y_333_;
v___y_323_ = v___y_334_;
v___y_324_ = v___y_332_;
goto v___jp_315_;
}
}
v___jp_339_:
{
uint64_t v___x_349_; uint8_t v___x_350_; 
v___x_349_ = lean_uint64_shift_right(v___y_342_, v___y_344_);
v___x_350_ = lean_uint64_dec_eq(v___x_349_, v___y_346_);
if (v___x_350_ == 0)
{
uint64_t v___x_351_; 
v___x_351_ = lean_uint64_add(v___y_345_, v___y_344_);
v___y_329_ = v___y_340_;
v___y_330_ = v___y_341_;
v___y_331_ = v___y_343_;
v___y_332_ = v___y_348_;
v___y_333_ = v___y_346_;
v___y_334_ = v___y_347_;
v___y_335_ = v___x_351_;
goto v___jp_328_;
}
else
{
v___y_329_ = v___y_340_;
v___y_330_ = v___y_341_;
v___y_331_ = v___y_343_;
v___y_332_ = v___y_348_;
v___y_333_ = v___y_346_;
v___y_334_ = v___y_347_;
v___y_335_ = v___y_345_;
goto v___jp_328_;
}
}
v___jp_352_:
{
uint64_t v___x_360_; uint64_t v___x_361_; uint8_t v___x_362_; 
v___x_360_ = 8ULL;
v___x_361_ = lean_uint64_shift_right(v___y_356_, v___x_360_);
v___x_362_ = lean_uint64_dec_eq(v___x_361_, v___y_357_);
if (v___x_362_ == 0)
{
v___y_340_ = v___y_353_;
v___y_341_ = v___y_354_;
v___y_342_ = v___y_356_;
v___y_343_ = v___y_355_;
v___y_344_ = v___x_360_;
v___y_345_ = v___y_359_;
v___y_346_ = v___y_357_;
v___y_347_ = v___y_358_;
v___y_348_ = v___x_361_;
goto v___jp_339_;
}
else
{
v___y_340_ = v___y_353_;
v___y_341_ = v___y_354_;
v___y_342_ = v___y_356_;
v___y_343_ = v___y_355_;
v___y_344_ = v___x_360_;
v___y_345_ = v___y_359_;
v___y_346_ = v___y_357_;
v___y_347_ = v___y_358_;
v___y_348_ = v___y_356_;
goto v___jp_339_;
}
}
v___jp_363_:
{
uint64_t v___x_373_; uint8_t v___x_374_; 
v___x_373_ = lean_uint64_shift_right(v___y_371_, v___y_370_);
v___x_374_ = lean_uint64_dec_eq(v___x_373_, v___y_368_);
if (v___x_374_ == 0)
{
uint64_t v___x_375_; 
v___x_375_ = lean_uint64_add(v___y_367_, v___y_370_);
v___y_353_ = v___y_364_;
v___y_354_ = v___y_365_;
v___y_355_ = v___y_366_;
v___y_356_ = v___y_372_;
v___y_357_ = v___y_368_;
v___y_358_ = v___y_369_;
v___y_359_ = v___x_375_;
goto v___jp_352_;
}
else
{
v___y_353_ = v___y_364_;
v___y_354_ = v___y_365_;
v___y_355_ = v___y_366_;
v___y_356_ = v___y_372_;
v___y_357_ = v___y_368_;
v___y_358_ = v___y_369_;
v___y_359_ = v___y_367_;
goto v___jp_352_;
}
}
v___jp_376_:
{
uint64_t v___x_384_; uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_384_ = 16ULL;
v___x_385_ = lean_uint64_shift_right(v___y_382_, v___x_384_);
v___x_386_ = lean_uint64_dec_eq(v___x_385_, v___y_380_);
if (v___x_386_ == 0)
{
v___y_364_ = v___y_377_;
v___y_365_ = v___y_378_;
v___y_366_ = v___y_379_;
v___y_367_ = v___y_383_;
v___y_368_ = v___y_380_;
v___y_369_ = v___y_381_;
v___y_370_ = v___x_384_;
v___y_371_ = v___y_382_;
v___y_372_ = v___x_385_;
goto v___jp_363_;
}
else
{
v___y_364_ = v___y_377_;
v___y_365_ = v___y_378_;
v___y_366_ = v___y_379_;
v___y_367_ = v___y_383_;
v___y_368_ = v___y_380_;
v___y_369_ = v___y_381_;
v___y_370_ = v___x_384_;
v___y_371_ = v___y_382_;
v___y_372_ = v___y_382_;
goto v___jp_363_;
}
}
v___jp_387_:
{
uint64_t v___x_395_; uint8_t v___x_396_; 
v___x_395_ = lean_uint64_shift_right(v___y_389_, v___y_391_);
v___x_396_ = lean_uint64_dec_eq(v___x_395_, v___y_392_);
if (v___x_396_ == 0)
{
v___y_377_ = v___y_388_;
v___y_378_ = v___y_389_;
v___y_379_ = v___y_390_;
v___y_380_ = v___y_392_;
v___y_381_ = v___y_393_;
v___y_382_ = v___y_394_;
v___y_383_ = v___y_391_;
goto v___jp_376_;
}
else
{
v___y_377_ = v___y_388_;
v___y_378_ = v___y_389_;
v___y_379_ = v___y_390_;
v___y_380_ = v___y_392_;
v___y_381_ = v___y_393_;
v___y_382_ = v___y_394_;
v___y_383_ = v___y_392_;
goto v___jp_376_;
}
}
v___jp_397_:
{
uint64_t v___x_402_; uint8_t v___x_403_; 
v___x_402_ = 0ULL;
v___x_403_ = lean_uint64_dec_eq(v___y_399_, v___x_402_);
if (v___x_403_ == 0)
{
uint64_t v___x_404_; uint64_t v___x_405_; uint8_t v___x_406_; 
v___x_404_ = 32ULL;
v___x_405_ = lean_uint64_shift_right(v___y_399_, v___x_404_);
v___x_406_ = lean_uint64_dec_eq(v___x_405_, v___x_402_);
if (v___x_406_ == 0)
{
v___y_388_ = v___y_398_;
v___y_389_ = v___y_399_;
v___y_390_ = v___y_400_;
v___y_391_ = v___x_404_;
v___y_392_ = v___x_402_;
v___y_393_ = v___y_401_;
v___y_394_ = v___x_405_;
goto v___jp_387_;
}
else
{
v___y_388_ = v___y_398_;
v___y_389_ = v___y_399_;
v___y_390_ = v___y_400_;
v___y_391_ = v___x_404_;
v___y_392_ = v___x_402_;
v___y_393_ = v___y_401_;
v___y_394_ = v___y_399_;
goto v___jp_387_;
}
}
else
{
if (v___y_400_ == 0)
{
uint32_t v___x_407_; 
v___x_407_ = 0;
return v___x_407_;
}
else
{
uint32_t v___x_408_; 
v___x_408_ = 2147483648;
return v___x_408_;
}
}
}
v___jp_409_:
{
uint64_t v___x_416_; uint64_t v___x_417_; uint64_t v___x_418_; uint8_t v___x_419_; 
v___x_416_ = lean_uint64_mul(v___y_412_, v___y_414_);
v___x_417_ = lean_uint64_add(v___y_411_, v___y_415_);
v___x_418_ = 281474976710656ULL;
v___x_419_ = lean_uint64_dec_lt(v___x_416_, v___x_418_);
if (v___x_419_ == 0)
{
v___y_398_ = v___x_417_;
v___y_399_ = v___x_416_;
v___y_400_ = v___y_410_;
v___y_401_ = v___y_413_;
goto v___jp_397_;
}
else
{
uint64_t v___x_420_; uint8_t v___x_421_; 
v___x_420_ = 123ULL;
v___x_421_ = lean_uint64_dec_le(v___x_417_, v___x_420_);
if (v___x_421_ == 0)
{
v___y_398_ = v___x_417_;
v___y_399_ = v___x_416_;
v___y_400_ = v___y_410_;
v___y_401_ = v___y_413_;
goto v___jp_397_;
}
else
{
uint64_t v___x_422_; uint8_t v___x_423_; 
v___x_422_ = 0ULL;
v___x_423_ = lean_uint64_dec_eq(v___x_416_, v___x_422_);
if (v___x_423_ == 0)
{
uint64_t v___x_424_; uint64_t v___x_425_; uint8_t v___x_426_; 
v___x_424_ = 149ULL;
v___x_425_ = lean_uint64_sub(v___x_424_, v___x_417_);
v___x_426_ = lean_uint64_dec_eq(v___x_425_, v___x_422_);
if (v___x_426_ == 0)
{
uint64_t v___x_427_; uint8_t v___x_428_; 
v___x_427_ = 64ULL;
v___x_428_ = lean_uint64_dec_lt(v___x_425_, v___x_427_);
if (v___x_428_ == 0)
{
uint8_t v___x_429_; 
v___x_429_ = lean_uint64_dec_eq(v___x_425_, v___x_427_);
if (v___x_429_ == 0)
{
v___y_103_ = v___y_410_;
v___y_104_ = v___x_422_;
v___y_105_ = v___y_413_;
v___y_106_ = v___x_422_;
goto v___jp_102_;
}
else
{
uint64_t v___x_430_; uint8_t v___x_431_; 
v___x_430_ = 9223372036854775808ULL;
v___x_431_ = lean_uint64_dec_lt(v___x_430_, v___x_416_);
if (v___x_431_ == 0)
{
v___y_103_ = v___y_410_;
v___y_104_ = v___x_422_;
v___y_105_ = v___y_413_;
v___y_106_ = v___x_422_;
goto v___jp_102_;
}
else
{
uint64_t v___x_432_; 
v___x_432_ = 1ULL;
v___y_103_ = v___y_410_;
v___y_104_ = v___x_422_;
v___y_105_ = v___y_413_;
v___y_106_ = v___x_432_;
goto v___jp_102_;
}
}
}
else
{
uint64_t v_quotient_433_; uint64_t v___x_434_; uint64_t v___x_435_; uint64_t v___x_436_; uint64_t v_remainder_437_; uint64_t v___x_438_; uint64_t v_half_439_; uint8_t v___x_440_; 
v_quotient_433_ = lean_uint64_shift_right(v___x_416_, v___x_425_);
v___x_434_ = 1ULL;
v___x_435_ = lean_uint64_shift_left(v___x_434_, v___x_425_);
v___x_436_ = lean_uint64_sub(v___x_435_, v___x_434_);
v_remainder_437_ = lean_uint64_land(v___x_416_, v___x_436_);
v___x_438_ = lean_uint64_sub(v___x_425_, v___x_434_);
v_half_439_ = lean_uint64_shift_left(v___x_434_, v___x_438_);
v___x_440_ = lean_uint64_dec_lt(v_remainder_437_, v_half_439_);
if (v___x_440_ == 0)
{
uint8_t v___x_441_; 
v___x_441_ = lean_uint64_dec_lt(v_half_439_, v_remainder_437_);
if (v___x_441_ == 0)
{
uint64_t v___x_442_; uint8_t v___x_443_; 
v___x_442_ = lean_uint64_land(v_quotient_433_, v___x_434_);
v___x_443_ = lean_uint64_dec_eq(v___x_442_, v___x_422_);
if (v___x_443_ == 0)
{
uint64_t v___x_444_; 
v___x_444_ = lean_uint64_add(v_quotient_433_, v___x_434_);
v___y_103_ = v___y_410_;
v___y_104_ = v___x_422_;
v___y_105_ = v___y_413_;
v___y_106_ = v___x_444_;
goto v___jp_102_;
}
else
{
v___y_103_ = v___y_410_;
v___y_104_ = v___x_422_;
v___y_105_ = v___y_413_;
v___y_106_ = v_quotient_433_;
goto v___jp_102_;
}
}
else
{
uint64_t v___x_445_; 
v___x_445_ = lean_uint64_add(v_quotient_433_, v___x_434_);
v___y_103_ = v___y_410_;
v___y_104_ = v___x_422_;
v___y_105_ = v___y_413_;
v___y_106_ = v___x_445_;
goto v___jp_102_;
}
}
else
{
v___y_103_ = v___y_410_;
v___y_104_ = v___x_422_;
v___y_105_ = v___y_413_;
v___y_106_ = v_quotient_433_;
goto v___jp_102_;
}
}
}
else
{
v___y_103_ = v___y_410_;
v___y_104_ = v___x_422_;
v___y_105_ = v___y_413_;
v___y_106_ = v___x_416_;
goto v___jp_102_;
}
}
else
{
if (v___y_410_ == 0)
{
uint32_t v___x_446_; 
v___x_446_ = 0;
return v___x_446_;
}
else
{
uint32_t v___x_447_; 
v___x_447_ = 2147483648;
return v___x_447_;
}
}
}
}
}
v___jp_451_:
{
uint64_t v___x_457_; uint64_t v___x_458_; uint8_t v___x_459_; 
v___x_457_ = lean_uint32_to_uint64(v_ey_450_);
v___x_458_ = 0ULL;
v___x_459_ = lean_uint64_dec_eq(v___x_457_, v___x_458_);
if (v___x_459_ == 0)
{
uint64_t v___x_460_; uint64_t v___x_461_; 
v___x_460_ = 1ULL;
v___x_461_ = lean_uint64_sub(v___x_457_, v___x_460_);
v___y_410_ = v___y_452_;
v___y_411_ = v___y_456_;
v___y_412_ = v___y_453_;
v___y_413_ = v___y_454_;
v___y_414_ = v___y_455_;
v___y_415_ = v___x_461_;
goto v___jp_409_;
}
else
{
v___y_410_ = v___y_452_;
v___y_411_ = v___y_456_;
v___y_412_ = v___y_453_;
v___y_413_ = v___y_454_;
v___y_414_ = v___y_455_;
v___y_415_ = v___x_458_;
goto v___jp_409_;
}
}
v___jp_462_:
{
uint64_t v___x_467_; uint64_t v___x_468_; uint8_t v___x_469_; 
v___x_467_ = lean_uint32_to_uint64(v_ex_448_);
v___x_468_ = 0ULL;
v___x_469_ = lean_uint64_dec_eq(v___x_467_, v___x_468_);
if (v___x_469_ == 0)
{
uint64_t v___x_470_; uint64_t v___x_471_; 
v___x_470_ = 1ULL;
v___x_471_ = lean_uint64_sub(v___x_467_, v___x_470_);
v___y_452_ = v___y_463_;
v___y_453_ = v___y_464_;
v___y_454_ = v___y_465_;
v___y_455_ = v___y_466_;
v___y_456_ = v___x_471_;
goto v___jp_451_;
}
else
{
v___y_452_ = v___y_463_;
v___y_453_ = v___y_464_;
v___y_454_ = v___y_465_;
v___y_455_ = v___y_466_;
v___y_456_ = v___x_468_;
goto v___jp_451_;
}
}
v___jp_472_:
{
uint32_t v___x_477_; uint8_t v___x_478_; 
v___x_477_ = 0;
v___x_478_ = lean_uint32_dec_eq(v_ey_450_, v___x_477_);
if (v___x_478_ == 0)
{
uint64_t v___x_479_; uint64_t v___x_480_; uint64_t v___x_481_; 
v___x_479_ = lean_uint32_to_uint64(v___y_473_);
v___x_480_ = 8388608ULL;
v___x_481_ = lean_uint64_lor(v___x_479_, v___x_480_);
v___y_463_ = v___y_474_;
v___y_464_ = v___y_476_;
v___y_465_ = v___y_475_;
v___y_466_ = v___x_481_;
goto v___jp_462_;
}
else
{
uint64_t v___x_482_; 
v___x_482_ = lean_uint32_to_uint64(v___y_473_);
v___y_463_ = v___y_474_;
v___y_464_ = v___y_476_;
v___y_465_ = v___y_475_;
v___y_466_ = v___x_482_;
goto v___jp_462_;
}
}
v___jp_483_:
{
uint32_t v___x_485_; uint32_t v_xFraction_486_; uint32_t v_yFraction_487_; uint32_t v___x_488_; uint8_t v___x_489_; 
v___x_485_ = 8388607;
v_xFraction_486_ = lean_uint32_land(v___y_65_, v___x_485_);
v_yFraction_487_ = lean_uint32_land(v___y_66_, v___x_485_);
v___x_488_ = 0;
v___x_489_ = lean_uint32_dec_eq(v_ex_448_, v___x_488_);
if (v___x_489_ == 0)
{
uint64_t v___x_490_; uint64_t v___x_491_; uint64_t v___x_492_; 
v___x_490_ = lean_uint32_to_uint64(v_xFraction_486_);
v___x_491_ = 8388608ULL;
v___x_492_ = lean_uint64_lor(v___x_490_, v___x_491_);
v___y_473_ = v_yFraction_487_;
v___y_474_ = v___y_484_;
v___y_475_ = v___x_485_;
v___y_476_ = v___x_492_;
goto v___jp_472_;
}
else
{
uint64_t v___x_493_; 
v___x_493_ = lean_uint32_to_uint64(v_xFraction_486_);
v___y_473_ = v_yFraction_487_;
v___y_474_ = v___y_484_;
v___y_475_ = v___x_485_;
v___y_476_ = v___x_493_;
goto v___jp_472_;
}
}
v___jp_497_:
{
if (v___y_499_ == 0)
{
v___y_484_ = v___x_496_;
goto v___jp_483_;
}
else
{
v___y_484_ = v___y_498_;
goto v___jp_483_;
}
}
v___jp_500_:
{
if (v___y_502_ == 0)
{
if (v___y_503_ == 0)
{
v___y_498_ = v___y_501_;
v___y_499_ = v___x_496_;
goto v___jp_497_;
}
else
{
v___y_484_ = v___x_496_;
goto v___jp_483_;
}
}
else
{
v___y_498_ = v___y_501_;
v___y_499_ = v___y_503_;
goto v___jp_497_;
}
}
v___jp_504_:
{
uint32_t v___x_507_; uint32_t v___x_508_; uint32_t v___x_509_; uint8_t v___x_510_; 
v___x_507_ = 2147483648;
v___x_508_ = lean_uint32_land(v___y_66_, v___x_507_);
v___x_509_ = 0;
v___x_510_ = lean_uint32_dec_eq(v___x_508_, v___x_509_);
if (v___x_510_ == 0)
{
v___y_501_ = v___y_505_;
v___y_502_ = v___y_506_;
v___y_503_ = v___x_496_;
goto v___jp_500_;
}
else
{
v___y_501_ = v___y_505_;
v___y_502_ = v___y_506_;
v___y_503_ = v___y_505_;
goto v___jp_500_;
}
}
v___jp_511_:
{
if (v___y_512_ == 0)
{
uint32_t v___x_513_; uint32_t v___x_514_; uint32_t v___x_515_; uint8_t v___x_516_; 
v___x_513_ = 2147483648;
v___x_514_ = lean_uint32_land(v___y_65_, v___x_513_);
v___x_515_ = 0;
v___x_516_ = lean_uint32_dec_eq(v___x_514_, v___x_515_);
if (v___x_516_ == 0)
{
v___y_505_ = v___y_512_;
v___y_506_ = v___x_496_;
goto v___jp_504_;
}
else
{
v___y_505_ = v___y_512_;
v___y_506_ = v___y_512_;
goto v___jp_504_;
}
}
else
{
lean_object* v___x_517_; lean_object* v___x_518_; lean_object* v___x_519_; uint32_t v___x_520_; 
v___x_517_ = lean_uint32_to_nat(v___y_65_);
v___x_518_ = lean_uint32_to_nat(v___y_66_);
v___x_519_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_517_, v___x_518_);
v___x_520_ = lean_uint32_of_nat(v___x_519_);
lean_dec(v___x_519_);
return v___x_520_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_535_, lean_object* v___y_536_){
_start:
{
uint32_t v___y_3337__boxed_537_; uint32_t v___y_3338__boxed_538_; uint32_t v_res_539_; lean_object* v_r_540_; 
v___y_3337__boxed_537_ = lean_unbox_uint32(v___y_535_);
lean_dec(v___y_535_);
v___y_3338__boxed_538_ = lean_unbox_uint32(v___y_536_);
lean_dec(v___y_536_);
v_res_539_ = lp_competition_main___lam__1(v___y_3337__boxed_537_, v___y_3338__boxed_538_);
v_r_540_ = lean_box_uint32(v_res_539_);
return v_r_540_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_541_, uint32_t v___y_542_){
_start:
{
uint32_t v___y_544_; uint32_t v___y_545_; uint32_t v___y_546_; uint32_t v___y_550_; uint32_t v___y_551_; uint32_t v___y_552_; uint32_t v___y_556_; uint8_t v___y_560_; uint32_t v___y_561_; uint64_t v___y_562_; uint64_t v___y_563_; uint32_t v___y_575_; uint64_t v___y_579_; uint8_t v___y_580_; uint32_t v___y_581_; uint64_t v___y_582_; float v___y_594_; float v___y_595_; float v___y_601_; uint8_t v___y_602_; float v___y_617_; uint32_t v___x_626_; uint32_t v___x_627_; uint8_t v___y_629_; uint32_t v___x_641_; uint32_t v___y_643_; uint32_t v___y_644_; uint32_t v___y_645_; uint32_t v___y_646_; uint32_t v___y_653_; uint8_t v___y_654_; uint32_t v___y_655_; uint32_t v___y_656_; uint64_t v___y_660_; uint8_t v___y_661_; uint32_t v___y_662_; uint64_t v___y_663_; uint64_t v___y_664_; uint8_t v___y_674_; uint8_t v___y_675_; uint64_t v___y_676_; uint32_t v___y_677_; uint64_t v___y_678_; uint64_t v___y_679_; uint64_t v___y_686_; uint8_t v___y_687_; uint32_t v___y_688_; uint64_t v___y_689_; uint64_t v___y_690_; uint64_t v___y_696_; uint8_t v___y_697_; uint32_t v___y_698_; uint64_t v___y_699_; uint64_t v___y_700_; uint64_t v___y_701_; uint64_t v___y_756_; uint8_t v___y_757_; uint32_t v___y_758_; uint64_t v___y_759_; uint64_t v___y_760_; uint64_t v___y_761_; uint64_t v___y_762_; uint64_t v___y_768_; uint64_t v___y_769_; uint64_t v___y_770_; uint64_t v___y_771_; uint8_t v___y_772_; uint32_t v___y_773_; uint64_t v___y_774_; uint64_t v___y_775_; uint64_t v___y_776_; uint64_t v___y_781_; uint64_t v___y_782_; uint8_t v___y_783_; uint32_t v___y_784_; uint64_t v___y_785_; uint64_t v___y_786_; uint64_t v___y_787_; uint64_t v___y_792_; uint64_t v___y_793_; uint64_t v___y_794_; uint8_t v___y_795_; uint32_t v___y_796_; uint64_t v___y_797_; uint64_t v___y_798_; uint64_t v___y_799_; uint64_t v___y_800_; uint64_t v___y_805_; uint64_t v___y_806_; uint8_t v___y_807_; uint32_t v___y_808_; uint64_t v___y_809_; uint64_t v___y_810_; uint64_t v___y_811_; uint64_t v___y_816_; uint64_t v___y_817_; uint64_t v___y_818_; uint8_t v___y_819_; uint32_t v___y_820_; uint64_t v___y_821_; uint64_t v___y_822_; uint64_t v___y_823_; uint64_t v___y_824_; uint64_t v___y_829_; uint8_t v___y_830_; uint32_t v___y_831_; uint64_t v___y_832_; uint64_t v___y_833_; uint64_t v___y_834_; uint64_t v___y_835_; uint64_t v___y_840_; uint64_t v___y_841_; uint64_t v___y_842_; uint64_t v___y_843_; uint8_t v___y_844_; uint32_t v___y_845_; uint64_t v___y_846_; uint64_t v___y_847_; uint64_t v___y_848_; uint64_t v___y_853_; uint64_t v___y_854_; uint8_t v___y_855_; uint32_t v___y_856_; uint64_t v___y_857_; uint64_t v___y_858_; uint64_t v___y_859_; uint64_t v___y_864_; uint64_t v___y_865_; uint8_t v___y_866_; uint32_t v___y_867_; uint64_t v___y_868_; uint64_t v___y_869_; uint64_t v___y_870_; uint64_t v___y_874_; uint8_t v___y_875_; uint32_t v___y_876_; uint64_t v___y_877_; uint64_t v___y_886_; uint64_t v___y_887_; uint8_t v___y_888_; uint64_t v___y_889_; uint32_t v___y_890_; uint64_t v___y_891_; uint32_t v_ex_924_; uint32_t v___x_925_; uint32_t v_ey_926_; uint64_t v___y_928_; uint64_t v___y_929_; uint8_t v___y_930_; uint32_t v___y_931_; uint64_t v___y_932_; uint64_t v___y_939_; uint8_t v___y_940_; uint32_t v___y_941_; uint64_t v___y_942_; uint8_t v___y_949_; uint32_t v___y_950_; uint32_t v___y_951_; uint64_t v___y_952_; uint8_t v___y_960_; uint32_t v___x_970_; uint32_t v___x_971_; uint8_t v___x_972_; uint8_t v___y_974_; uint8_t v___y_975_; uint8_t v___y_977_; uint8_t v___y_978_; uint8_t v___y_979_; uint8_t v___y_981_; uint8_t v___y_982_; uint8_t v___y_988_; 
v___x_626_ = 23;
v___x_627_ = lean_uint32_shift_right(v___y_541_, v___x_626_);
v___x_641_ = 255;
v_ex_924_ = lean_uint32_land(v___x_627_, v___x_641_);
v___x_925_ = lean_uint32_shift_right(v___y_542_, v___x_626_);
v_ey_926_ = lean_uint32_land(v___x_925_, v___x_641_);
v___x_970_ = lean_uint32_add(v_ex_924_, v_ey_926_);
v___x_971_ = 128;
v___x_972_ = lean_uint32_dec_lt(v___x_970_, v___x_971_);
if (v___x_972_ == 0)
{
uint32_t v___x_997_; uint32_t v_a_998_; uint32_t v___x_999_; uint32_t v___x_1000_; uint32_t v___x_1001_; uint8_t v___x_1002_; 
v___x_997_ = 2147483647;
v_a_998_ = lean_uint32_land(v___y_541_, v___x_997_);
v___x_999_ = 201326591;
v___x_1000_ = 1;
v___x_1001_ = lean_uint32_sub(v_a_998_, v___x_1000_);
v___x_1002_ = lean_uint32_dec_le(v___x_999_, v___x_1001_);
if (v___x_1002_ == 0)
{
v___y_629_ = v___x_1002_;
goto v___jp_628_;
}
else
{
uint32_t v___x_1003_; uint8_t v___x_1004_; 
v___x_1003_ = 2139095040;
v___x_1004_ = lean_uint32_dec_lt(v_a_998_, v___x_1003_);
v___y_629_ = v___x_1004_;
goto v___jp_628_;
}
}
else
{
uint32_t v___x_1005_; uint32_t v___x_1006_; uint32_t v___x_1007_; uint8_t v___x_1008_; 
v___x_1005_ = 4278190080;
v___x_1006_ = 1;
v___x_1007_ = lean_uint32_shift_left(v___y_541_, v___x_1006_);
v___x_1008_ = lean_uint32_dec_le(v___x_1005_, v___x_1007_);
if (v___x_1008_ == 0)
{
uint32_t v___x_1009_; uint8_t v___x_1010_; 
v___x_1009_ = lean_uint32_shift_left(v___y_542_, v___x_1006_);
v___x_1010_ = lean_uint32_dec_le(v___x_1005_, v___x_1009_);
v___y_988_ = v___x_1010_;
goto v___jp_987_;
}
else
{
v___y_988_ = v___x_1008_;
goto v___jp_987_;
}
}
v___jp_543_:
{
uint32_t v___x_547_; uint32_t v___x_548_; 
v___x_547_ = lean_uint32_land(v___y_544_, v___y_545_);
v___x_548_ = lean_uint32_lor(v___y_546_, v___x_547_);
return v___x_548_;
}
v___jp_549_:
{
uint32_t v___x_553_; uint32_t v___x_554_; 
v___x_553_ = lean_uint32_land(v___y_550_, v___y_551_);
v___x_554_ = lean_uint32_lor(v___y_552_, v___x_553_);
return v___x_554_;
}
v___jp_555_:
{
uint32_t v___x_557_; uint32_t v___x_558_; 
v___x_557_ = 8388608;
v___x_558_ = lean_uint32_lor(v___y_556_, v___x_557_);
return v___x_558_;
}
v___jp_559_:
{
uint8_t v___x_564_; 
v___x_564_ = lean_uint64_dec_eq(v___y_563_, v___y_562_);
if (v___x_564_ == 0)
{
uint64_t v___x_565_; uint8_t v___x_566_; 
v___x_565_ = 8388608ULL;
v___x_566_ = lean_uint64_dec_eq(v___y_563_, v___x_565_);
if (v___x_566_ == 0)
{
uint32_t v___x_567_; 
v___x_567_ = lean_uint64_to_uint32(v___y_563_);
if (v___y_560_ == 0)
{
uint32_t v___x_568_; 
v___x_568_ = 0;
v___y_550_ = v___x_567_;
v___y_551_ = v___y_561_;
v___y_552_ = v___x_568_;
goto v___jp_549_;
}
else
{
uint32_t v___x_569_; 
v___x_569_ = 2147483648;
v___y_550_ = v___x_567_;
v___y_551_ = v___y_561_;
v___y_552_ = v___x_569_;
goto v___jp_549_;
}
}
else
{
if (v___y_560_ == 0)
{
uint32_t v___x_570_; 
v___x_570_ = 0;
v___y_556_ = v___x_570_;
goto v___jp_555_;
}
else
{
uint32_t v___x_571_; 
v___x_571_ = 2147483648;
v___y_556_ = v___x_571_;
goto v___jp_555_;
}
}
}
else
{
if (v___y_560_ == 0)
{
uint32_t v___x_572_; 
v___x_572_ = 0;
return v___x_572_;
}
else
{
uint32_t v___x_573_; 
v___x_573_ = 2147483648;
return v___x_573_;
}
}
}
v___jp_574_:
{
uint32_t v___x_576_; uint32_t v___x_577_; 
v___x_576_ = 8388608;
v___x_577_ = lean_uint32_lor(v___y_575_, v___x_576_);
return v___x_577_;
}
v___jp_578_:
{
uint8_t v___x_583_; 
v___x_583_ = lean_uint64_dec_eq(v___y_582_, v___y_579_);
if (v___x_583_ == 0)
{
uint64_t v___x_584_; uint8_t v___x_585_; 
v___x_584_ = 8388608ULL;
v___x_585_ = lean_uint64_dec_eq(v___y_582_, v___x_584_);
if (v___x_585_ == 0)
{
uint32_t v___x_586_; 
v___x_586_ = lean_uint64_to_uint32(v___y_582_);
if (v___y_580_ == 0)
{
uint32_t v___x_587_; 
v___x_587_ = 0;
v___y_544_ = v___x_586_;
v___y_545_ = v___y_581_;
v___y_546_ = v___x_587_;
goto v___jp_543_;
}
else
{
uint32_t v___x_588_; 
v___x_588_ = 2147483648;
v___y_544_ = v___x_586_;
v___y_545_ = v___y_581_;
v___y_546_ = v___x_588_;
goto v___jp_543_;
}
}
else
{
if (v___y_580_ == 0)
{
uint32_t v___x_589_; 
v___x_589_ = 0;
v___y_575_ = v___x_589_;
goto v___jp_574_;
}
else
{
uint32_t v___x_590_; 
v___x_590_ = 2147483648;
v___y_575_ = v___x_590_;
goto v___jp_574_;
}
}
}
else
{
if (v___y_580_ == 0)
{
uint32_t v___x_591_; 
v___x_591_ = 0;
return v___x_591_;
}
else
{
uint32_t v___x_592_; 
v___x_592_ = 2147483648;
return v___x_592_;
}
}
}
v___jp_593_:
{
float v_result_596_; uint8_t v___x_597_; 
v_result_596_ = lean_float32_mul(v___y_594_, v___y_595_);
v___x_597_ = lean_float32_beq(v_result_596_, v_result_596_);
if (v___x_597_ == 0)
{
uint32_t v___x_598_; 
v___x_598_ = lp_competition_Submission_FastMul_mul(v___y_541_, v___y_542_);
return v___x_598_;
}
else
{
uint32_t v___x_599_; 
v___x_599_ = lean_float32_to_bits(v_result_596_);
return v___x_599_;
}
}
v___jp_600_:
{
if (v___y_602_ == 0)
{
float v___x_603_; 
v___x_603_ = lean_float32_of_bits(v___y_542_);
v___y_594_ = v___y_601_;
v___y_595_ = v___x_603_;
goto v___jp_593_;
}
else
{
uint32_t v___x_604_; uint32_t v___x_605_; uint32_t v___x_606_; uint32_t v___x_607_; float v___x_608_; lean_object* v___x_609_; uint32_t v___x_610_; uint32_t v___x_611_; lean_object* v___x_612_; lean_object* v___x_613_; float v___x_614_; float v___x_615_; 
v___x_604_ = 8388607;
v___x_605_ = lean_uint32_land(v___y_542_, v___x_604_);
v___x_606_ = 8388608;
v___x_607_ = lean_uint32_lor(v___x_605_, v___x_606_);
v___x_608_ = lean_uint32_to_float32(v___x_607_);
v___x_609_ = lp_competition_R2W01b_scaleTable;
v___x_610_ = 23;
v___x_611_ = lean_uint32_shift_right(v___y_542_, v___x_610_);
v___x_612_ = lean_uint32_to_nat(v___x_611_);
v___x_613_ = lean_array_fget_borrowed(v___x_609_, v___x_612_);
lean_dec(v___x_612_);
v___x_614_ = lean_unbox_float32(v___x_613_);
v___x_615_ = lean_float32_mul(v___x_608_, v___x_614_);
v___y_594_ = v___y_601_;
v___y_595_ = v___x_615_;
goto v___jp_593_;
}
}
v___jp_616_:
{
uint32_t v___x_618_; uint32_t v_a_619_; uint32_t v___x_620_; uint32_t v___x_621_; uint32_t v___x_622_; uint8_t v___x_623_; 
v___x_618_ = 2147483647;
v_a_619_ = lean_uint32_land(v___y_542_, v___x_618_);
v___x_620_ = 201326591;
v___x_621_ = 1;
v___x_622_ = lean_uint32_sub(v_a_619_, v___x_621_);
v___x_623_ = lean_uint32_dec_le(v___x_620_, v___x_622_);
if (v___x_623_ == 0)
{
v___y_601_ = v___y_617_;
v___y_602_ = v___x_623_;
goto v___jp_600_;
}
else
{
uint32_t v___x_624_; uint8_t v___x_625_; 
v___x_624_ = 2139095040;
v___x_625_ = lean_uint32_dec_lt(v_a_619_, v___x_624_);
v___y_601_ = v___y_617_;
v___y_602_ = v___x_625_;
goto v___jp_600_;
}
}
v___jp_628_:
{
if (v___y_629_ == 0)
{
float v___x_630_; 
v___x_630_ = lean_float32_of_bits(v___y_541_);
v___y_617_ = v___x_630_;
goto v___jp_616_;
}
else
{
uint32_t v___x_631_; uint32_t v___x_632_; uint32_t v___x_633_; uint32_t v___x_634_; float v___x_635_; lean_object* v___x_636_; lean_object* v___x_637_; lean_object* v___x_638_; float v___x_639_; float v___x_640_; 
v___x_631_ = 8388607;
v___x_632_ = lean_uint32_land(v___y_541_, v___x_631_);
v___x_633_ = 8388608;
v___x_634_ = lean_uint32_lor(v___x_632_, v___x_633_);
v___x_635_ = lean_uint32_to_float32(v___x_634_);
v___x_636_ = lp_competition_R2W01b_scaleTable;
v___x_637_ = lean_uint32_to_nat(v___x_627_);
v___x_638_ = lean_array_fget_borrowed(v___x_636_, v___x_637_);
lean_dec(v___x_637_);
v___x_639_ = lean_unbox_float32(v___x_638_);
v___x_640_ = lean_float32_mul(v___x_635_, v___x_639_);
v___y_617_ = v___x_640_;
goto v___jp_616_;
}
}
v___jp_642_:
{
uint32_t v___x_647_; uint32_t v___x_648_; uint32_t v___x_649_; uint32_t v___x_650_; uint32_t v___x_651_; 
v___x_647_ = lean_uint32_land(v___y_644_, v___x_641_);
v___x_648_ = lean_uint32_shift_left(v___x_647_, v___x_626_);
v___x_649_ = lean_uint32_lor(v___y_646_, v___x_648_);
v___x_650_ = lean_uint32_land(v___y_643_, v___y_645_);
v___x_651_ = lean_uint32_lor(v___x_649_, v___x_650_);
return v___x_651_;
}
v___jp_652_:
{
if (v___y_654_ == 0)
{
uint32_t v___x_657_; 
v___x_657_ = 0;
v___y_643_ = v___y_656_;
v___y_644_ = v___y_653_;
v___y_645_ = v___y_655_;
v___y_646_ = v___x_657_;
goto v___jp_642_;
}
else
{
uint32_t v___x_658_; 
v___x_658_ = 2147483648;
v___y_643_ = v___y_656_;
v___y_644_ = v___y_653_;
v___y_645_ = v___y_655_;
v___y_646_ = v___x_658_;
goto v___jp_642_;
}
}
v___jp_659_:
{
uint64_t v___x_665_; uint64_t v_encodedExponent_666_; uint32_t v___x_667_; uint64_t v___x_668_; uint8_t v___x_669_; 
v___x_665_ = 171ULL;
v_encodedExponent_666_ = lean_uint64_sub(v___y_660_, v___x_665_);
v___x_667_ = lean_uint64_to_uint32(v_encodedExponent_666_);
v___x_668_ = 8388608ULL;
v___x_669_ = lean_uint64_dec_lt(v___y_664_, v___x_668_);
if (v___x_669_ == 0)
{
uint64_t v___x_670_; uint32_t v___x_671_; 
v___x_670_ = lean_uint64_sub(v___y_664_, v___x_668_);
v___x_671_ = lean_uint64_to_uint32(v___x_670_);
v___y_653_ = v___x_667_;
v___y_654_ = v___y_661_;
v___y_655_ = v___y_662_;
v___y_656_ = v___x_671_;
goto v___jp_652_;
}
else
{
uint32_t v___x_672_; 
v___x_672_ = lean_uint64_to_uint32(v___y_663_);
v___y_653_ = v___x_667_;
v___y_654_ = v___y_661_;
v___y_655_ = v___y_662_;
v___y_656_ = v___x_672_;
goto v___jp_652_;
}
}
v___jp_673_:
{
uint64_t v___x_680_; uint8_t v___x_681_; 
v___x_680_ = 425ULL;
v___x_681_ = lean_uint64_dec_lt(v___x_680_, v___y_679_);
if (v___x_681_ == 0)
{
if (v___y_674_ == 0)
{
v___y_660_ = v___y_679_;
v___y_661_ = v___y_675_;
v___y_662_ = v___y_677_;
v___y_663_ = v___y_678_;
v___y_664_ = v___y_676_;
goto v___jp_659_;
}
else
{
uint64_t v___x_682_; 
v___x_682_ = 8388608ULL;
v___y_660_ = v___y_679_;
v___y_661_ = v___y_675_;
v___y_662_ = v___y_677_;
v___y_663_ = v___y_678_;
v___y_664_ = v___x_682_;
goto v___jp_659_;
}
}
else
{
if (v___y_675_ == 0)
{
uint32_t v___x_683_; 
v___x_683_ = 2139095040;
return v___x_683_;
}
else
{
uint32_t v___x_684_; 
v___x_684_ = 4286578688;
return v___x_684_;
}
}
}
v___jp_685_:
{
uint64_t v___x_691_; uint8_t v_carry_692_; 
v___x_691_ = 16777216ULL;
v_carry_692_ = lean_uint64_dec_eq(v___y_690_, v___x_691_);
if (v_carry_692_ == 0)
{
v___y_674_ = v_carry_692_;
v___y_675_ = v___y_687_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_688_;
v___y_678_ = v___y_689_;
v___y_679_ = v___y_686_;
goto v___jp_673_;
}
else
{
uint64_t v___x_693_; uint64_t v___x_694_; 
v___x_693_ = 1ULL;
v___x_694_ = lean_uint64_add(v___y_686_, v___x_693_);
v___y_674_ = v_carry_692_;
v___y_675_ = v___y_687_;
v___y_676_ = v___y_690_;
v___y_677_ = v___y_688_;
v___y_678_ = v___y_689_;
v___y_679_ = v___x_694_;
goto v___jp_673_;
}
}
v___jp_695_:
{
uint64_t v_position_702_; uint64_t v___x_703_; uint8_t v___x_704_; 
v_position_702_ = lean_uint64_add(v___y_701_, v___y_700_);
v___x_703_ = 172ULL;
v___x_704_ = lean_uint64_dec_lt(v_position_702_, v___x_703_);
if (v___x_704_ == 0)
{
uint64_t v___x_705_; uint8_t v___x_706_; 
v___x_705_ = 23ULL;
v___x_706_ = lean_uint64_dec_lt(v___y_701_, v___x_705_);
if (v___x_706_ == 0)
{
uint64_t v___x_707_; uint8_t v___x_708_; 
v___x_707_ = lean_uint64_sub(v___y_701_, v___x_705_);
v___x_708_ = lean_uint64_dec_eq(v___x_707_, v___y_699_);
if (v___x_708_ == 0)
{
uint64_t v___x_709_; uint8_t v___x_710_; 
v___x_709_ = 64ULL;
v___x_710_ = lean_uint64_dec_lt(v___x_707_, v___x_709_);
if (v___x_710_ == 0)
{
uint8_t v___x_711_; 
v___x_711_ = lean_uint64_dec_eq(v___x_707_, v___x_709_);
if (v___x_711_ == 0)
{
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_699_;
goto v___jp_685_;
}
else
{
uint64_t v___x_712_; uint8_t v___x_713_; 
v___x_712_ = 9223372036854775808ULL;
v___x_713_ = lean_uint64_dec_lt(v___x_712_, v___y_696_);
if (v___x_713_ == 0)
{
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_699_;
goto v___jp_685_;
}
else
{
uint64_t v___x_714_; 
v___x_714_ = 1ULL;
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v___x_714_;
goto v___jp_685_;
}
}
}
else
{
uint64_t v_quotient_715_; uint64_t v___x_716_; uint64_t v___x_717_; uint64_t v___x_718_; uint64_t v_remainder_719_; uint64_t v___x_720_; uint64_t v_half_721_; uint8_t v___x_722_; 
v_quotient_715_ = lean_uint64_shift_right(v___y_696_, v___x_707_);
v___x_716_ = 1ULL;
v___x_717_ = lean_uint64_shift_left(v___x_716_, v___x_707_);
v___x_718_ = lean_uint64_sub(v___x_717_, v___x_716_);
v_remainder_719_ = lean_uint64_land(v___y_696_, v___x_718_);
v___x_720_ = lean_uint64_sub(v___x_707_, v___x_716_);
v_half_721_ = lean_uint64_shift_left(v___x_716_, v___x_720_);
v___x_722_ = lean_uint64_dec_lt(v_remainder_719_, v_half_721_);
if (v___x_722_ == 0)
{
uint8_t v___x_723_; 
v___x_723_ = lean_uint64_dec_lt(v_half_721_, v_remainder_719_);
if (v___x_723_ == 0)
{
uint64_t v___x_724_; uint8_t v___x_725_; 
v___x_724_ = lean_uint64_land(v_quotient_715_, v___x_716_);
v___x_725_ = lean_uint64_dec_eq(v___x_724_, v___y_699_);
if (v___x_725_ == 0)
{
uint64_t v___x_726_; 
v___x_726_ = lean_uint64_add(v_quotient_715_, v___x_716_);
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v___x_726_;
goto v___jp_685_;
}
else
{
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v_quotient_715_;
goto v___jp_685_;
}
}
else
{
uint64_t v___x_727_; 
v___x_727_ = lean_uint64_add(v_quotient_715_, v___x_716_);
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v___x_727_;
goto v___jp_685_;
}
}
else
{
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v_quotient_715_;
goto v___jp_685_;
}
}
}
else
{
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_696_;
goto v___jp_685_;
}
}
else
{
uint64_t v___x_728_; uint64_t v___x_729_; 
v___x_728_ = lean_uint64_sub(v___x_705_, v___y_701_);
v___x_729_ = lean_uint64_shift_left(v___y_696_, v___x_728_);
v___y_686_ = v_position_702_;
v___y_687_ = v___y_697_;
v___y_688_ = v___y_698_;
v___y_689_ = v___y_699_;
v___y_690_ = v___x_729_;
goto v___jp_685_;
}
}
else
{
uint64_t v___x_730_; uint8_t v___x_731_; 
v___x_730_ = 149ULL;
v___x_731_ = lean_uint64_dec_lt(v___y_700_, v___x_730_);
if (v___x_731_ == 0)
{
uint64_t v___x_732_; uint64_t v___x_733_; 
v___x_732_ = lean_uint64_sub(v___y_700_, v___x_730_);
v___x_733_ = lean_uint64_shift_left(v___y_696_, v___x_732_);
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v___x_733_;
goto v___jp_559_;
}
else
{
uint64_t v___x_734_; uint8_t v___x_735_; 
v___x_734_ = lean_uint64_sub(v___x_730_, v___y_700_);
v___x_735_ = lean_uint64_dec_eq(v___x_734_, v___y_699_);
if (v___x_735_ == 0)
{
uint64_t v___x_736_; uint8_t v___x_737_; 
v___x_736_ = 64ULL;
v___x_737_ = lean_uint64_dec_lt(v___x_734_, v___x_736_);
if (v___x_737_ == 0)
{
uint8_t v___x_738_; 
v___x_738_ = lean_uint64_dec_eq(v___x_734_, v___x_736_);
if (v___x_738_ == 0)
{
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v___y_699_;
goto v___jp_559_;
}
else
{
uint64_t v___x_739_; uint8_t v___x_740_; 
v___x_739_ = 9223372036854775808ULL;
v___x_740_ = lean_uint64_dec_lt(v___x_739_, v___y_696_);
if (v___x_740_ == 0)
{
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v___y_699_;
goto v___jp_559_;
}
else
{
uint64_t v___x_741_; 
v___x_741_ = 1ULL;
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v___x_741_;
goto v___jp_559_;
}
}
}
else
{
uint64_t v_quotient_742_; uint64_t v___x_743_; uint64_t v___x_744_; uint64_t v___x_745_; uint64_t v_remainder_746_; uint64_t v___x_747_; uint64_t v_half_748_; uint8_t v___x_749_; 
v_quotient_742_ = lean_uint64_shift_right(v___y_696_, v___x_734_);
v___x_743_ = 1ULL;
v___x_744_ = lean_uint64_shift_left(v___x_743_, v___x_734_);
v___x_745_ = lean_uint64_sub(v___x_744_, v___x_743_);
v_remainder_746_ = lean_uint64_land(v___y_696_, v___x_745_);
v___x_747_ = lean_uint64_sub(v___x_734_, v___x_743_);
v_half_748_ = lean_uint64_shift_left(v___x_743_, v___x_747_);
v___x_749_ = lean_uint64_dec_lt(v_remainder_746_, v_half_748_);
if (v___x_749_ == 0)
{
uint8_t v___x_750_; 
v___x_750_ = lean_uint64_dec_lt(v_half_748_, v_remainder_746_);
if (v___x_750_ == 0)
{
uint64_t v___x_751_; uint8_t v___x_752_; 
v___x_751_ = lean_uint64_land(v_quotient_742_, v___x_743_);
v___x_752_ = lean_uint64_dec_eq(v___x_751_, v___y_699_);
if (v___x_752_ == 0)
{
uint64_t v___x_753_; 
v___x_753_ = lean_uint64_add(v_quotient_742_, v___x_743_);
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v___x_753_;
goto v___jp_559_;
}
else
{
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v_quotient_742_;
goto v___jp_559_;
}
}
else
{
uint64_t v___x_754_; 
v___x_754_ = lean_uint64_add(v_quotient_742_, v___x_743_);
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v___x_754_;
goto v___jp_559_;
}
}
else
{
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v_quotient_742_;
goto v___jp_559_;
}
}
}
else
{
v___y_560_ = v___y_697_;
v___y_561_ = v___y_698_;
v___y_562_ = v___y_699_;
v___y_563_ = v___y_696_;
goto v___jp_559_;
}
}
}
}
v___jp_755_:
{
uint64_t v___x_763_; uint64_t v___x_764_; uint8_t v___x_765_; 
v___x_763_ = 1ULL;
v___x_764_ = lean_uint64_shift_right(v___y_760_, v___x_763_);
v___x_765_ = lean_uint64_dec_eq(v___x_764_, v___y_759_);
if (v___x_765_ == 0)
{
uint64_t v___x_766_; 
v___x_766_ = lean_uint64_add(v___y_762_, v___x_763_);
v___y_696_ = v___y_756_;
v___y_697_ = v___y_757_;
v___y_698_ = v___y_758_;
v___y_699_ = v___y_759_;
v___y_700_ = v___y_761_;
v___y_701_ = v___x_766_;
goto v___jp_695_;
}
else
{
v___y_696_ = v___y_756_;
v___y_697_ = v___y_757_;
v___y_698_ = v___y_758_;
v___y_699_ = v___y_759_;
v___y_700_ = v___y_761_;
v___y_701_ = v___y_762_;
goto v___jp_695_;
}
}
v___jp_767_:
{
uint64_t v___x_777_; uint8_t v___x_778_; 
v___x_777_ = lean_uint64_shift_right(v___y_769_, v___y_771_);
v___x_778_ = lean_uint64_dec_eq(v___x_777_, v___y_774_);
if (v___x_778_ == 0)
{
uint64_t v___x_779_; 
v___x_779_ = lean_uint64_add(v___y_768_, v___y_771_);
v___y_756_ = v___y_770_;
v___y_757_ = v___y_772_;
v___y_758_ = v___y_773_;
v___y_759_ = v___y_774_;
v___y_760_ = v___y_776_;
v___y_761_ = v___y_775_;
v___y_762_ = v___x_779_;
goto v___jp_755_;
}
else
{
v___y_756_ = v___y_770_;
v___y_757_ = v___y_772_;
v___y_758_ = v___y_773_;
v___y_759_ = v___y_774_;
v___y_760_ = v___y_776_;
v___y_761_ = v___y_775_;
v___y_762_ = v___y_768_;
goto v___jp_755_;
}
}
v___jp_780_:
{
uint64_t v___x_788_; uint64_t v___x_789_; uint8_t v___x_790_; 
v___x_788_ = 2ULL;
v___x_789_ = lean_uint64_shift_right(v___y_781_, v___x_788_);
v___x_790_ = lean_uint64_dec_eq(v___x_789_, v___y_785_);
if (v___x_790_ == 0)
{
v___y_768_ = v___y_787_;
v___y_769_ = v___y_781_;
v___y_770_ = v___y_782_;
v___y_771_ = v___x_788_;
v___y_772_ = v___y_783_;
v___y_773_ = v___y_784_;
v___y_774_ = v___y_785_;
v___y_775_ = v___y_786_;
v___y_776_ = v___x_789_;
goto v___jp_767_;
}
else
{
v___y_768_ = v___y_787_;
v___y_769_ = v___y_781_;
v___y_770_ = v___y_782_;
v___y_771_ = v___x_788_;
v___y_772_ = v___y_783_;
v___y_773_ = v___y_784_;
v___y_774_ = v___y_785_;
v___y_775_ = v___y_786_;
v___y_776_ = v___y_781_;
goto v___jp_767_;
}
}
v___jp_791_:
{
uint64_t v___x_801_; uint8_t v___x_802_; 
v___x_801_ = lean_uint64_shift_right(v___y_793_, v___y_798_);
v___x_802_ = lean_uint64_dec_eq(v___x_801_, v___y_797_);
if (v___x_802_ == 0)
{
uint64_t v___x_803_; 
v___x_803_ = lean_uint64_add(v___y_792_, v___y_798_);
v___y_781_ = v___y_800_;
v___y_782_ = v___y_794_;
v___y_783_ = v___y_795_;
v___y_784_ = v___y_796_;
v___y_785_ = v___y_797_;
v___y_786_ = v___y_799_;
v___y_787_ = v___x_803_;
goto v___jp_780_;
}
else
{
v___y_781_ = v___y_800_;
v___y_782_ = v___y_794_;
v___y_783_ = v___y_795_;
v___y_784_ = v___y_796_;
v___y_785_ = v___y_797_;
v___y_786_ = v___y_799_;
v___y_787_ = v___y_792_;
goto v___jp_780_;
}
}
v___jp_804_:
{
uint64_t v___x_812_; uint64_t v___x_813_; uint8_t v___x_814_; 
v___x_812_ = 4ULL;
v___x_813_ = lean_uint64_shift_right(v___y_806_, v___x_812_);
v___x_814_ = lean_uint64_dec_eq(v___x_813_, v___y_809_);
if (v___x_814_ == 0)
{
v___y_792_ = v___y_811_;
v___y_793_ = v___y_806_;
v___y_794_ = v___y_805_;
v___y_795_ = v___y_807_;
v___y_796_ = v___y_808_;
v___y_797_ = v___y_809_;
v___y_798_ = v___x_812_;
v___y_799_ = v___y_810_;
v___y_800_ = v___x_813_;
goto v___jp_791_;
}
else
{
v___y_792_ = v___y_811_;
v___y_793_ = v___y_806_;
v___y_794_ = v___y_805_;
v___y_795_ = v___y_807_;
v___y_796_ = v___y_808_;
v___y_797_ = v___y_809_;
v___y_798_ = v___x_812_;
v___y_799_ = v___y_810_;
v___y_800_ = v___y_806_;
goto v___jp_791_;
}
}
v___jp_815_:
{
uint64_t v___x_825_; uint8_t v___x_826_; 
v___x_825_ = lean_uint64_shift_right(v___y_821_, v___y_818_);
v___x_826_ = lean_uint64_dec_eq(v___x_825_, v___y_822_);
if (v___x_826_ == 0)
{
uint64_t v___x_827_; 
v___x_827_ = lean_uint64_add(v___y_817_, v___y_818_);
v___y_805_ = v___y_816_;
v___y_806_ = v___y_824_;
v___y_807_ = v___y_819_;
v___y_808_ = v___y_820_;
v___y_809_ = v___y_822_;
v___y_810_ = v___y_823_;
v___y_811_ = v___x_827_;
goto v___jp_804_;
}
else
{
v___y_805_ = v___y_816_;
v___y_806_ = v___y_824_;
v___y_807_ = v___y_819_;
v___y_808_ = v___y_820_;
v___y_809_ = v___y_822_;
v___y_810_ = v___y_823_;
v___y_811_ = v___y_817_;
goto v___jp_804_;
}
}
v___jp_828_:
{
uint64_t v___x_836_; uint64_t v___x_837_; uint8_t v___x_838_; 
v___x_836_ = 8ULL;
v___x_837_ = lean_uint64_shift_right(v___y_833_, v___x_836_);
v___x_838_ = lean_uint64_dec_eq(v___x_837_, v___y_832_);
if (v___x_838_ == 0)
{
v___y_816_ = v___y_829_;
v___y_817_ = v___y_835_;
v___y_818_ = v___x_836_;
v___y_819_ = v___y_830_;
v___y_820_ = v___y_831_;
v___y_821_ = v___y_833_;
v___y_822_ = v___y_832_;
v___y_823_ = v___y_834_;
v___y_824_ = v___x_837_;
goto v___jp_815_;
}
else
{
v___y_816_ = v___y_829_;
v___y_817_ = v___y_835_;
v___y_818_ = v___x_836_;
v___y_819_ = v___y_830_;
v___y_820_ = v___y_831_;
v___y_821_ = v___y_833_;
v___y_822_ = v___y_832_;
v___y_823_ = v___y_834_;
v___y_824_ = v___y_833_;
goto v___jp_815_;
}
}
v___jp_839_:
{
uint64_t v___x_849_; uint8_t v___x_850_; 
v___x_849_ = lean_uint64_shift_right(v___y_842_, v___y_841_);
v___x_850_ = lean_uint64_dec_eq(v___x_849_, v___y_846_);
if (v___x_850_ == 0)
{
uint64_t v___x_851_; 
v___x_851_ = lean_uint64_add(v___y_840_, v___y_841_);
v___y_829_ = v___y_843_;
v___y_830_ = v___y_844_;
v___y_831_ = v___y_845_;
v___y_832_ = v___y_846_;
v___y_833_ = v___y_848_;
v___y_834_ = v___y_847_;
v___y_835_ = v___x_851_;
goto v___jp_828_;
}
else
{
v___y_829_ = v___y_843_;
v___y_830_ = v___y_844_;
v___y_831_ = v___y_845_;
v___y_832_ = v___y_846_;
v___y_833_ = v___y_848_;
v___y_834_ = v___y_847_;
v___y_835_ = v___y_840_;
goto v___jp_828_;
}
}
v___jp_852_:
{
uint64_t v___x_860_; uint64_t v___x_861_; uint8_t v___x_862_; 
v___x_860_ = 16ULL;
v___x_861_ = lean_uint64_shift_right(v___y_853_, v___x_860_);
v___x_862_ = lean_uint64_dec_eq(v___x_861_, v___y_857_);
if (v___x_862_ == 0)
{
v___y_840_ = v___y_859_;
v___y_841_ = v___x_860_;
v___y_842_ = v___y_853_;
v___y_843_ = v___y_854_;
v___y_844_ = v___y_855_;
v___y_845_ = v___y_856_;
v___y_846_ = v___y_857_;
v___y_847_ = v___y_858_;
v___y_848_ = v___x_861_;
goto v___jp_839_;
}
else
{
v___y_840_ = v___y_859_;
v___y_841_ = v___x_860_;
v___y_842_ = v___y_853_;
v___y_843_ = v___y_854_;
v___y_844_ = v___y_855_;
v___y_845_ = v___y_856_;
v___y_846_ = v___y_857_;
v___y_847_ = v___y_858_;
v___y_848_ = v___y_853_;
goto v___jp_839_;
}
}
v___jp_863_:
{
uint64_t v___x_871_; uint8_t v___x_872_; 
v___x_871_ = lean_uint64_shift_right(v___y_864_, v___y_865_);
v___x_872_ = lean_uint64_dec_eq(v___x_871_, v___y_868_);
if (v___x_872_ == 0)
{
v___y_853_ = v___y_870_;
v___y_854_ = v___y_864_;
v___y_855_ = v___y_866_;
v___y_856_ = v___y_867_;
v___y_857_ = v___y_868_;
v___y_858_ = v___y_869_;
v___y_859_ = v___y_865_;
goto v___jp_852_;
}
else
{
v___y_853_ = v___y_870_;
v___y_854_ = v___y_864_;
v___y_855_ = v___y_866_;
v___y_856_ = v___y_867_;
v___y_857_ = v___y_868_;
v___y_858_ = v___y_869_;
v___y_859_ = v___y_868_;
goto v___jp_852_;
}
}
v___jp_873_:
{
uint64_t v___x_878_; uint8_t v___x_879_; 
v___x_878_ = 0ULL;
v___x_879_ = lean_uint64_dec_eq(v___y_874_, v___x_878_);
if (v___x_879_ == 0)
{
uint64_t v___x_880_; uint64_t v___x_881_; uint8_t v___x_882_; 
v___x_880_ = 32ULL;
v___x_881_ = lean_uint64_shift_right(v___y_874_, v___x_880_);
v___x_882_ = lean_uint64_dec_eq(v___x_881_, v___x_878_);
if (v___x_882_ == 0)
{
v___y_864_ = v___y_874_;
v___y_865_ = v___x_880_;
v___y_866_ = v___y_875_;
v___y_867_ = v___y_876_;
v___y_868_ = v___x_878_;
v___y_869_ = v___y_877_;
v___y_870_ = v___x_881_;
goto v___jp_863_;
}
else
{
v___y_864_ = v___y_874_;
v___y_865_ = v___x_880_;
v___y_866_ = v___y_875_;
v___y_867_ = v___y_876_;
v___y_868_ = v___x_878_;
v___y_869_ = v___y_877_;
v___y_870_ = v___y_874_;
goto v___jp_863_;
}
}
else
{
if (v___y_875_ == 0)
{
uint32_t v___x_883_; 
v___x_883_ = 0;
return v___x_883_;
}
else
{
uint32_t v___x_884_; 
v___x_884_ = 2147483648;
return v___x_884_;
}
}
}
v___jp_885_:
{
uint64_t v___x_892_; uint64_t v___x_893_; uint64_t v___x_894_; uint8_t v___x_895_; 
v___x_892_ = lean_uint64_mul(v___y_887_, v___y_886_);
v___x_893_ = lean_uint64_add(v___y_889_, v___y_891_);
v___x_894_ = 281474976710656ULL;
v___x_895_ = lean_uint64_dec_lt(v___x_892_, v___x_894_);
if (v___x_895_ == 0)
{
v___y_874_ = v___x_892_;
v___y_875_ = v___y_888_;
v___y_876_ = v___y_890_;
v___y_877_ = v___x_893_;
goto v___jp_873_;
}
else
{
uint64_t v___x_896_; uint8_t v___x_897_; 
v___x_896_ = 123ULL;
v___x_897_ = lean_uint64_dec_le(v___x_893_, v___x_896_);
if (v___x_897_ == 0)
{
v___y_874_ = v___x_892_;
v___y_875_ = v___y_888_;
v___y_876_ = v___y_890_;
v___y_877_ = v___x_893_;
goto v___jp_873_;
}
else
{
uint64_t v___x_898_; uint8_t v___x_899_; 
v___x_898_ = 0ULL;
v___x_899_ = lean_uint64_dec_eq(v___x_892_, v___x_898_);
if (v___x_899_ == 0)
{
uint64_t v___x_900_; uint64_t v___x_901_; uint8_t v___x_902_; 
v___x_900_ = 149ULL;
v___x_901_ = lean_uint64_sub(v___x_900_, v___x_893_);
v___x_902_ = lean_uint64_dec_eq(v___x_901_, v___x_898_);
if (v___x_902_ == 0)
{
uint64_t v___x_903_; uint8_t v___x_904_; 
v___x_903_ = 64ULL;
v___x_904_ = lean_uint64_dec_lt(v___x_901_, v___x_903_);
if (v___x_904_ == 0)
{
uint8_t v___x_905_; 
v___x_905_ = lean_uint64_dec_eq(v___x_901_, v___x_903_);
if (v___x_905_ == 0)
{
v___y_579_ = v___x_898_;
v___y_580_ = v___y_888_;
v___y_581_ = v___y_890_;
v___y_582_ = v___x_898_;
goto v___jp_578_;
}
else
{
uint64_t v___x_906_; uint8_t v___x_907_; 
v___x_906_ = 9223372036854775808ULL;
v___x_907_ = lean_uint64_dec_lt(v___x_906_, v___x_892_);
if (v___x_907_ == 0)
{
v___y_579_ = v___x_898_;
v___y_580_ = v___y_888_;
v___y_581_ = v___y_890_;
v___y_582_ = v___x_898_;
goto v___jp_578_;
}
else
{
uint64_t v___x_908_; 
v___x_908_ = 1ULL;
v___y_579_ = v___x_898_;
v___y_580_ = v___y_888_;
v___y_581_ = v___y_890_;
v___y_582_ = v___x_908_;
goto v___jp_578_;
}
}
}
else
{
uint64_t v_quotient_909_; uint64_t v___x_910_; uint64_t v___x_911_; uint64_t v___x_912_; uint64_t v_remainder_913_; uint64_t v___x_914_; uint64_t v_half_915_; uint8_t v___x_916_; 
v_quotient_909_ = lean_uint64_shift_right(v___x_892_, v___x_901_);
v___x_910_ = 1ULL;
v___x_911_ = lean_uint64_shift_left(v___x_910_, v___x_901_);
v___x_912_ = lean_uint64_sub(v___x_911_, v___x_910_);
v_remainder_913_ = lean_uint64_land(v___x_892_, v___x_912_);
v___x_914_ = lean_uint64_sub(v___x_901_, v___x_910_);
v_half_915_ = lean_uint64_shift_left(v___x_910_, v___x_914_);
v___x_916_ = lean_uint64_dec_lt(v_remainder_913_, v_half_915_);
if (v___x_916_ == 0)
{
uint8_t v___x_917_; 
v___x_917_ = lean_uint64_dec_lt(v_half_915_, v_remainder_913_);
if (v___x_917_ == 0)
{
uint64_t v___x_918_; uint8_t v___x_919_; 
v___x_918_ = lean_uint64_land(v_quotient_909_, v___x_910_);
v___x_919_ = lean_uint64_dec_eq(v___x_918_, v___x_898_);
if (v___x_919_ == 0)
{
uint64_t v___x_920_; 
v___x_920_ = lean_uint64_add(v_quotient_909_, v___x_910_);
v___y_579_ = v___x_898_;
v___y_580_ = v___y_888_;
v___y_581_ = v___y_890_;
v___y_582_ = v___x_920_;
goto v___jp_578_;
}
else
{
v___y_579_ = v___x_898_;
v___y_580_ = v___y_888_;
v___y_581_ = v___y_890_;
v___y_582_ = v_quotient_909_;
goto v___jp_578_;
}
}
else
{
uint64_t v___x_921_; 
v___x_921_ = lean_uint64_add(v_quotient_909_, v___x_910_);
v___y_579_ = v___x_898_;
v___y_580_ = v___y_888_;
v___y_581_ = v___y_890_;
v___y_582_ = v___x_921_;
goto v___jp_578_;
}
}
else
{
v___y_579_ = v___x_898_;
v___y_580_ = v___y_888_;
v___y_581_ = v___y_890_;
v___y_582_ = v_quotient_909_;
goto v___jp_578_;
}
}
}
else
{
v___y_579_ = v___x_898_;
v___y_580_ = v___y_888_;
v___y_581_ = v___y_890_;
v___y_582_ = v___x_892_;
goto v___jp_578_;
}
}
else
{
if (v___y_888_ == 0)
{
uint32_t v___x_922_; 
v___x_922_ = 0;
return v___x_922_;
}
else
{
uint32_t v___x_923_; 
v___x_923_ = 2147483648;
return v___x_923_;
}
}
}
}
}
v___jp_927_:
{
uint64_t v___x_933_; uint64_t v___x_934_; uint8_t v___x_935_; 
v___x_933_ = lean_uint32_to_uint64(v_ey_926_);
v___x_934_ = 0ULL;
v___x_935_ = lean_uint64_dec_eq(v___x_933_, v___x_934_);
if (v___x_935_ == 0)
{
uint64_t v___x_936_; uint64_t v___x_937_; 
v___x_936_ = 1ULL;
v___x_937_ = lean_uint64_sub(v___x_933_, v___x_936_);
v___y_886_ = v___y_928_;
v___y_887_ = v___y_929_;
v___y_888_ = v___y_930_;
v___y_889_ = v___y_932_;
v___y_890_ = v___y_931_;
v___y_891_ = v___x_937_;
goto v___jp_885_;
}
else
{
v___y_886_ = v___y_928_;
v___y_887_ = v___y_929_;
v___y_888_ = v___y_930_;
v___y_889_ = v___y_932_;
v___y_890_ = v___y_931_;
v___y_891_ = v___x_934_;
goto v___jp_885_;
}
}
v___jp_938_:
{
uint64_t v___x_943_; uint64_t v___x_944_; uint8_t v___x_945_; 
v___x_943_ = lean_uint32_to_uint64(v_ex_924_);
v___x_944_ = 0ULL;
v___x_945_ = lean_uint64_dec_eq(v___x_943_, v___x_944_);
if (v___x_945_ == 0)
{
uint64_t v___x_946_; uint64_t v___x_947_; 
v___x_946_ = 1ULL;
v___x_947_ = lean_uint64_sub(v___x_943_, v___x_946_);
v___y_928_ = v___y_942_;
v___y_929_ = v___y_939_;
v___y_930_ = v___y_940_;
v___y_931_ = v___y_941_;
v___y_932_ = v___x_947_;
goto v___jp_927_;
}
else
{
v___y_928_ = v___y_942_;
v___y_929_ = v___y_939_;
v___y_930_ = v___y_940_;
v___y_931_ = v___y_941_;
v___y_932_ = v___x_944_;
goto v___jp_927_;
}
}
v___jp_948_:
{
uint32_t v___x_953_; uint8_t v___x_954_; 
v___x_953_ = 0;
v___x_954_ = lean_uint32_dec_eq(v_ey_926_, v___x_953_);
if (v___x_954_ == 0)
{
uint64_t v___x_955_; uint64_t v___x_956_; uint64_t v___x_957_; 
v___x_955_ = lean_uint32_to_uint64(v___y_951_);
v___x_956_ = 8388608ULL;
v___x_957_ = lean_uint64_lor(v___x_955_, v___x_956_);
v___y_939_ = v___y_952_;
v___y_940_ = v___y_949_;
v___y_941_ = v___y_950_;
v___y_942_ = v___x_957_;
goto v___jp_938_;
}
else
{
uint64_t v___x_958_; 
v___x_958_ = lean_uint32_to_uint64(v___y_951_);
v___y_939_ = v___y_952_;
v___y_940_ = v___y_949_;
v___y_941_ = v___y_950_;
v___y_942_ = v___x_958_;
goto v___jp_938_;
}
}
v___jp_959_:
{
uint32_t v___x_961_; uint32_t v_xFraction_962_; uint32_t v_yFraction_963_; uint32_t v___x_964_; uint8_t v___x_965_; 
v___x_961_ = 8388607;
v_xFraction_962_ = lean_uint32_land(v___y_541_, v___x_961_);
v_yFraction_963_ = lean_uint32_land(v___y_542_, v___x_961_);
v___x_964_ = 0;
v___x_965_ = lean_uint32_dec_eq(v_ex_924_, v___x_964_);
if (v___x_965_ == 0)
{
uint64_t v___x_966_; uint64_t v___x_967_; uint64_t v___x_968_; 
v___x_966_ = lean_uint32_to_uint64(v_xFraction_962_);
v___x_967_ = 8388608ULL;
v___x_968_ = lean_uint64_lor(v___x_966_, v___x_967_);
v___y_949_ = v___y_960_;
v___y_950_ = v___x_961_;
v___y_951_ = v_yFraction_963_;
v___y_952_ = v___x_968_;
goto v___jp_948_;
}
else
{
uint64_t v___x_969_; 
v___x_969_ = lean_uint32_to_uint64(v_xFraction_962_);
v___y_949_ = v___y_960_;
v___y_950_ = v___x_961_;
v___y_951_ = v_yFraction_963_;
v___y_952_ = v___x_969_;
goto v___jp_948_;
}
}
v___jp_973_:
{
if (v___y_975_ == 0)
{
v___y_960_ = v___x_972_;
goto v___jp_959_;
}
else
{
v___y_960_ = v___y_974_;
goto v___jp_959_;
}
}
v___jp_976_:
{
if (v___y_977_ == 0)
{
if (v___y_979_ == 0)
{
v___y_974_ = v___y_978_;
v___y_975_ = v___x_972_;
goto v___jp_973_;
}
else
{
v___y_960_ = v___x_972_;
goto v___jp_959_;
}
}
else
{
v___y_974_ = v___y_978_;
v___y_975_ = v___y_979_;
goto v___jp_973_;
}
}
v___jp_980_:
{
uint32_t v___x_983_; uint32_t v___x_984_; uint32_t v___x_985_; uint8_t v___x_986_; 
v___x_983_ = 2147483648;
v___x_984_ = lean_uint32_land(v___y_542_, v___x_983_);
v___x_985_ = 0;
v___x_986_ = lean_uint32_dec_eq(v___x_984_, v___x_985_);
if (v___x_986_ == 0)
{
v___y_977_ = v___y_982_;
v___y_978_ = v___y_981_;
v___y_979_ = v___x_972_;
goto v___jp_976_;
}
else
{
v___y_977_ = v___y_982_;
v___y_978_ = v___y_981_;
v___y_979_ = v___y_981_;
goto v___jp_976_;
}
}
v___jp_987_:
{
if (v___y_988_ == 0)
{
uint32_t v___x_989_; uint32_t v___x_990_; uint32_t v___x_991_; uint8_t v___x_992_; 
v___x_989_ = 2147483648;
v___x_990_ = lean_uint32_land(v___y_541_, v___x_989_);
v___x_991_ = 0;
v___x_992_ = lean_uint32_dec_eq(v___x_990_, v___x_991_);
if (v___x_992_ == 0)
{
v___y_981_ = v___y_988_;
v___y_982_ = v___x_972_;
goto v___jp_980_;
}
else
{
v___y_981_ = v___y_988_;
v___y_982_ = v___y_988_;
goto v___jp_980_;
}
}
else
{
lean_object* v___x_993_; lean_object* v___x_994_; lean_object* v___x_995_; uint32_t v___x_996_; 
v___x_993_ = lean_uint32_to_nat(v___y_541_);
v___x_994_ = lean_uint32_to_nat(v___y_542_);
v___x_995_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_993_, v___x_994_);
v___x_996_ = lean_uint32_of_nat(v___x_995_);
lean_dec(v___x_995_);
return v___x_996_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_1011_, lean_object* v___y_1012_){
_start:
{
uint32_t v___y_4241__boxed_1013_; uint32_t v___y_4242__boxed_1014_; uint32_t v_res_1015_; lean_object* v_r_1016_; 
v___y_4241__boxed_1013_ = lean_unbox_uint32(v___y_1011_);
lean_dec(v___y_1011_);
v___y_4242__boxed_1014_ = lean_unbox_uint32(v___y_1012_);
lean_dec(v___y_1012_);
v_res_1015_ = lp_competition_main___lam__3(v___y_4241__boxed_1013_, v___y_4242__boxed_1014_);
v_r_1016_ = lean_box_uint32(v_res_1015_);
return v_r_1016_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1024_; lean_object* v___x_1025_; 
v___x_1024_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1025_ = lean_io_getenv(v___x_1024_);
if (lean_obj_tag(v___x_1025_) == 0)
{
lean_object* v___f_1026_; lean_object* v___f_1027_; lean_object* v___x_1028_; lean_object* v___x_1029_; lean_object* v___x_1030_; 
v___f_1026_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1027_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1028_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1029_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1030_ = lp_competition_Bench_runFull(v___f_1026_, v___f_1027_, v___x_1028_, v___x_1029_);
return v___x_1030_;
}
else
{
lean_object* v___f_1031_; lean_object* v___f_1032_; lean_object* v___x_1033_; lean_object* v___x_1034_; lean_object* v___x_1035_; 
lean_dec_ref_known(v___x_1025_, 1);
v___f_1031_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1032_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1033_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1034_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1035_ = lp_competition_Bench_Suite_run(v___f_1031_, v___f_1032_, v___x_1033_, v___x_1034_);
return v___x_1035_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1036_){
_start:
{
lean_object* v_res_1037_; 
v_res_1037_ = _lean_main();
return v_res_1037_;
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
