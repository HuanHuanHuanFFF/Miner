// Lean compiler output
// Module: MainFull
// Imports: public import Init public meta import Init public import BenchFull public import Submission
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
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
uint32_t lp_competition_Submission_TunedAdd_add(uint32_t, uint32_t);
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
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_runFull(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_closure_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_closure_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_closure_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
float v___y_4_; float v___y_5_; float v___y_9_; uint8_t v___y_10_; float v___y_25_; uint8_t v___y_35_; uint8_t v___y_50_; uint32_t v___x_91_; uint32_t v___x_92_; uint32_t v___x_93_; uint32_t v___x_94_; uint32_t v___x_95_; uint8_t v___x_96_; 
v___x_91_ = 2147483647;
v___x_92_ = lean_uint32_land(v___y_1_, v___x_91_);
v___x_93_ = 201326592;
v___x_94_ = lean_uint32_sub(v___x_92_, v___x_93_);
v___x_95_ = 1937768448;
v___x_96_ = lean_uint32_dec_lt(v___x_94_, v___x_95_);
if (v___x_96_ == 0)
{
v___y_50_ = v___x_96_;
goto v___jp_49_;
}
else
{
uint32_t v___x_97_; uint32_t v___x_98_; uint8_t v___x_99_; 
v___x_97_ = lean_uint32_land(v___y_2_, v___x_91_);
v___x_98_ = lean_uint32_sub(v___x_97_, v___x_93_);
v___x_99_ = lean_uint32_dec_lt(v___x_98_, v___x_95_);
v___y_50_ = v___x_99_;
goto v___jp_49_;
}
v___jp_3_:
{
float v___x_6_; uint32_t v___x_7_; 
v___x_6_ = lean_float32_add(v___y_4_, v___y_5_);
v___x_7_ = lean_float32_to_bits(v___x_6_);
return v___x_7_;
}
v___jp_8_:
{
if (v___y_10_ == 0)
{
float v___x_11_; 
v___x_11_ = lean_float32_of_bits(v___y_2_);
v___y_4_ = v___y_9_;
v___y_5_ = v___x_11_;
goto v___jp_3_;
}
else
{
uint32_t v___x_12_; uint32_t v___x_13_; uint32_t v___x_14_; uint32_t v___x_15_; float v___x_16_; lean_object* v___x_17_; uint32_t v___x_18_; uint32_t v___x_19_; lean_object* v___x_20_; lean_object* v___x_21_; float v___x_22_; float v___x_23_; 
v___x_12_ = 8388607;
v___x_13_ = lean_uint32_land(v___y_2_, v___x_12_);
v___x_14_ = 8388608;
v___x_15_ = lean_uint32_lor(v___x_13_, v___x_14_);
v___x_16_ = lean_uint32_to_float32(v___x_15_);
v___x_17_ = lp_competition_R2W01b_scaleTable;
v___x_18_ = 23;
v___x_19_ = lean_uint32_shift_right(v___y_2_, v___x_18_);
v___x_20_ = lean_uint32_to_nat(v___x_19_);
v___x_21_ = lean_array_fget_borrowed(v___x_17_, v___x_20_);
lean_dec(v___x_20_);
v___x_22_ = lean_unbox_float32(v___x_21_);
v___x_23_ = lean_float32_mul(v___x_16_, v___x_22_);
v___y_4_ = v___y_9_;
v___y_5_ = v___x_23_;
goto v___jp_3_;
}
}
v___jp_24_:
{
uint32_t v___x_26_; uint32_t v_a_27_; uint32_t v___x_28_; uint32_t v___x_29_; uint32_t v___x_30_; uint8_t v___x_31_; 
v___x_26_ = 2147483647;
v_a_27_ = lean_uint32_land(v___y_2_, v___x_26_);
v___x_28_ = 201326591;
v___x_29_ = 1;
v___x_30_ = lean_uint32_sub(v_a_27_, v___x_29_);
v___x_31_ = lean_uint32_dec_le(v___x_28_, v___x_30_);
if (v___x_31_ == 0)
{
v___y_9_ = v___y_25_;
v___y_10_ = v___x_31_;
goto v___jp_8_;
}
else
{
uint32_t v___x_32_; uint8_t v___x_33_; 
v___x_32_ = 2139095040;
v___x_33_ = lean_uint32_dec_lt(v_a_27_, v___x_32_);
v___y_9_ = v___y_25_;
v___y_10_ = v___x_33_;
goto v___jp_8_;
}
}
v___jp_34_:
{
if (v___y_35_ == 0)
{
float v___x_36_; 
v___x_36_ = lean_float32_of_bits(v___y_1_);
v___y_25_ = v___x_36_;
goto v___jp_24_;
}
else
{
uint32_t v___x_37_; uint32_t v___x_38_; uint32_t v___x_39_; uint32_t v___x_40_; float v___x_41_; lean_object* v___x_42_; uint32_t v___x_43_; uint32_t v___x_44_; lean_object* v___x_45_; lean_object* v___x_46_; float v___x_47_; float v___x_48_; 
v___x_37_ = 8388607;
v___x_38_ = lean_uint32_land(v___y_1_, v___x_37_);
v___x_39_ = 8388608;
v___x_40_ = lean_uint32_lor(v___x_38_, v___x_39_);
v___x_41_ = lean_uint32_to_float32(v___x_40_);
v___x_42_ = lp_competition_R2W01b_scaleTable;
v___x_43_ = 23;
v___x_44_ = lean_uint32_shift_right(v___y_1_, v___x_43_);
v___x_45_ = lean_uint32_to_nat(v___x_44_);
v___x_46_ = lean_array_fget_borrowed(v___x_42_, v___x_45_);
lean_dec(v___x_45_);
v___x_47_ = lean_unbox_float32(v___x_46_);
v___x_48_ = lean_float32_mul(v___x_41_, v___x_47_);
v___y_25_ = v___x_48_;
goto v___jp_24_;
}
}
v___jp_49_:
{
if (v___y_50_ == 0)
{
uint32_t v___x_51_; uint32_t v___x_52_; uint32_t v___x_53_; uint32_t v___x_54_; uint8_t v___x_55_; 
v___x_51_ = 23;
v___x_52_ = lean_uint32_shift_right(v___y_1_, v___x_51_);
v___x_53_ = 255;
v___x_54_ = lean_uint32_land(v___x_52_, v___x_53_);
v___x_55_ = lean_uint32_dec_eq(v___x_54_, v___x_53_);
if (v___x_55_ == 0)
{
uint32_t v___x_56_; uint32_t v___x_57_; uint8_t v___x_58_; 
v___x_56_ = lean_uint32_shift_right(v___y_2_, v___x_51_);
v___x_57_ = lean_uint32_land(v___x_56_, v___x_53_);
v___x_58_ = lean_uint32_dec_eq(v___x_57_, v___x_53_);
if (v___x_58_ == 0)
{
uint32_t v___x_59_; uint32_t v_a_60_; uint32_t v___x_61_; uint32_t v___x_62_; uint32_t v___x_63_; uint8_t v___x_64_; 
v___x_59_ = 2147483647;
v_a_60_ = lean_uint32_land(v___y_1_, v___x_59_);
v___x_61_ = 201326591;
v___x_62_ = 1;
v___x_63_ = lean_uint32_sub(v_a_60_, v___x_62_);
v___x_64_ = lean_uint32_dec_le(v___x_61_, v___x_63_);
if (v___x_64_ == 0)
{
v___y_35_ = v___x_64_;
goto v___jp_34_;
}
else
{
uint32_t v___x_65_; uint8_t v___x_66_; 
v___x_65_ = 2139095040;
v___x_66_ = lean_uint32_dec_lt(v_a_60_, v___x_65_);
v___y_35_ = v___x_66_;
goto v___jp_34_;
}
}
else
{
uint32_t v___x_67_; 
v___x_67_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_67_;
}
}
else
{
uint32_t v___x_68_; 
v___x_68_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_68_;
}
}
else
{
uint32_t v___x_69_; uint32_t v___x_70_; uint32_t v___x_71_; uint32_t v___x_72_; float v___x_73_; lean_object* v___x_74_; uint32_t v___x_75_; uint32_t v___x_76_; lean_object* v___x_77_; lean_object* v___x_78_; float v___x_79_; float v___x_80_; uint32_t v___x_81_; uint32_t v___x_82_; float v___x_83_; uint32_t v___x_84_; lean_object* v___x_85_; lean_object* v___x_86_; float v___x_87_; float v___x_88_; float v___x_89_; uint32_t v___x_90_; 
v___x_69_ = 8388607;
v___x_70_ = lean_uint32_land(v___y_1_, v___x_69_);
v___x_71_ = 8388608;
v___x_72_ = lean_uint32_lor(v___x_70_, v___x_71_);
v___x_73_ = lean_uint32_to_float32(v___x_72_);
v___x_74_ = lp_competition_R2W01b_scaleTable;
v___x_75_ = 23;
v___x_76_ = lean_uint32_shift_right(v___y_1_, v___x_75_);
v___x_77_ = lean_uint32_to_nat(v___x_76_);
v___x_78_ = lean_array_fget_borrowed(v___x_74_, v___x_77_);
lean_dec(v___x_77_);
v___x_79_ = lean_unbox_float32(v___x_78_);
v___x_80_ = lean_float32_mul(v___x_73_, v___x_79_);
v___x_81_ = lean_uint32_land(v___y_2_, v___x_69_);
v___x_82_ = lean_uint32_lor(v___x_81_, v___x_71_);
v___x_83_ = lean_uint32_to_float32(v___x_82_);
v___x_84_ = lean_uint32_shift_right(v___y_2_, v___x_75_);
v___x_85_ = lean_uint32_to_nat(v___x_84_);
v___x_86_ = lean_array_fget_borrowed(v___x_74_, v___x_85_);
lean_dec(v___x_85_);
v___x_87_ = lean_unbox_float32(v___x_86_);
v___x_88_ = lean_float32_mul(v___x_83_, v___x_87_);
v___x_89_ = lean_float32_add(v___x_80_, v___x_88_);
v___x_90_ = lean_float32_to_bits(v___x_89_);
return v___x_90_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_100_, lean_object* v___y_101_){
_start:
{
uint32_t v___y_1640__boxed_102_; uint32_t v___y_1641__boxed_103_; uint32_t v_res_104_; lean_object* v_r_105_; 
v___y_1640__boxed_102_ = lean_unbox_uint32(v___y_100_);
lean_dec(v___y_100_);
v___y_1641__boxed_103_ = lean_unbox_uint32(v___y_101_);
lean_dec(v___y_101_);
v_res_104_ = lp_competition_main___lam__0(v___y_1640__boxed_102_, v___y_1641__boxed_103_);
v_r_105_ = lean_box_uint32(v_res_104_);
return v_r_105_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_106_, uint32_t v___y_107_){
_start:
{
uint32_t v___y_114_; uint32_t v___y_115_; uint32_t v___y_116_; uint32_t v___y_120_; uint32_t v___y_121_; uint32_t v___y_122_; uint32_t v___y_126_; uint32_t v___y_130_; uint8_t v___y_131_; uint64_t v___y_132_; uint64_t v___y_133_; uint32_t v___y_145_; uint32_t v___y_149_; uint8_t v___y_150_; uint64_t v___y_151_; uint64_t v___y_152_; uint32_t v___x_163_; uint32_t v___x_164_; uint32_t v___x_165_; uint32_t v___y_167_; uint32_t v___y_168_; uint32_t v___y_169_; uint32_t v___y_170_; uint32_t v___y_177_; uint8_t v___y_178_; uint32_t v___y_179_; uint32_t v___y_180_; uint64_t v___y_184_; uint32_t v___y_185_; uint8_t v___y_186_; uint64_t v___y_187_; uint64_t v___y_188_; uint64_t v___y_198_; uint8_t v___y_199_; uint32_t v___y_200_; uint8_t v___y_201_; uint64_t v___y_202_; uint64_t v___y_203_; uint32_t v___y_210_; uint64_t v___y_211_; uint8_t v___y_212_; uint64_t v___y_213_; uint64_t v___y_214_; uint32_t v___y_220_; uint64_t v___y_221_; uint8_t v___y_222_; uint64_t v___y_223_; uint64_t v___y_224_; uint64_t v___y_225_; uint32_t v___y_280_; uint64_t v___y_281_; uint64_t v___y_282_; uint8_t v___y_283_; uint64_t v___y_284_; uint64_t v___y_285_; uint64_t v___y_286_; uint64_t v___y_292_; uint32_t v___y_293_; uint64_t v___y_294_; uint8_t v___y_295_; uint64_t v___y_296_; uint64_t v___y_297_; uint64_t v___y_298_; uint64_t v___y_299_; uint64_t v___y_300_; uint64_t v___y_305_; uint32_t v___y_306_; uint64_t v___y_307_; uint8_t v___y_308_; uint64_t v___y_309_; uint64_t v___y_310_; uint64_t v___y_311_; uint64_t v___y_316_; uint64_t v___y_317_; uint64_t v___y_318_; uint32_t v___y_319_; uint64_t v___y_320_; uint8_t v___y_321_; uint64_t v___y_322_; uint64_t v___y_323_; uint64_t v___y_324_; uint64_t v___y_329_; uint32_t v___y_330_; uint64_t v___y_331_; uint8_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint64_t v___y_335_; uint64_t v___y_340_; uint32_t v___y_341_; uint64_t v___y_342_; uint64_t v___y_343_; uint64_t v___y_344_; uint8_t v___y_345_; uint64_t v___y_346_; uint64_t v___y_347_; uint64_t v___y_348_; uint32_t v___y_353_; uint64_t v___y_354_; uint64_t v___y_355_; uint8_t v___y_356_; uint64_t v___y_357_; uint64_t v___y_358_; uint64_t v___y_359_; uint32_t v___y_364_; uint64_t v___y_365_; uint64_t v___y_366_; uint64_t v___y_367_; uint64_t v___y_368_; uint8_t v___y_369_; uint64_t v___y_370_; uint64_t v___y_371_; uint64_t v___y_372_; uint32_t v___y_377_; uint64_t v___y_378_; uint64_t v___y_379_; uint8_t v___y_380_; uint64_t v___y_381_; uint64_t v___y_382_; uint64_t v___y_383_; uint32_t v___y_388_; uint64_t v___y_389_; uint8_t v___y_390_; uint64_t v___y_391_; uint64_t v___y_392_; uint64_t v___y_393_; uint64_t v___y_394_; uint32_t v___y_398_; uint64_t v___y_399_; uint8_t v___y_400_; uint64_t v___y_401_; uint32_t v___y_410_; uint8_t v___y_411_; uint64_t v___y_412_; uint64_t v___y_413_; uint64_t v___y_414_; uint64_t v___y_415_; uint32_t v_ex_448_; uint32_t v___x_449_; uint32_t v_ey_450_; uint32_t v___y_452_; uint64_t v___y_453_; uint8_t v___y_454_; uint64_t v___y_455_; uint64_t v___y_456_; uint32_t v___y_463_; uint8_t v___y_464_; uint64_t v___y_465_; uint64_t v___y_466_; uint32_t v___y_473_; uint8_t v___y_474_; uint32_t v___y_475_; uint64_t v___y_476_; uint8_t v___y_484_; uint32_t v___x_494_; uint32_t v___x_495_; uint8_t v___x_496_; uint8_t v___y_498_; uint8_t v___y_499_; uint8_t v___y_501_; uint8_t v___y_502_; uint8_t v___y_503_; uint8_t v___y_505_; uint8_t v___y_506_; uint8_t v___y_512_; 
v___x_163_ = 23;
v___x_164_ = lean_uint32_shift_right(v___y_106_, v___x_163_);
v___x_165_ = 255;
v_ex_448_ = lean_uint32_land(v___x_164_, v___x_165_);
v___x_449_ = lean_uint32_shift_right(v___y_107_, v___x_163_);
v_ey_450_ = lean_uint32_land(v___x_449_, v___x_165_);
v___x_494_ = lean_uint32_add(v_ex_448_, v_ey_450_);
v___x_495_ = 128;
v___x_496_ = lean_uint32_dec_lt(v___x_494_, v___x_495_);
if (v___x_496_ == 0)
{
uint8_t v___x_524_; 
v___x_524_ = lean_uint32_dec_eq(v_ex_448_, v___x_165_);
if (v___x_524_ == 0)
{
goto v___jp_521_;
}
else
{
if (v___x_496_ == 0)
{
uint32_t v___x_525_; 
v___x_525_ = lp_competition_Submission_FastMul_mul(v___y_106_, v___y_107_);
return v___x_525_;
}
else
{
goto v___jp_521_;
}
}
}
else
{
uint32_t v___x_526_; uint32_t v___x_527_; uint32_t v___x_528_; uint8_t v___x_529_; 
v___x_526_ = 4278190080;
v___x_527_ = 1;
v___x_528_ = lean_uint32_shift_left(v___y_106_, v___x_527_);
v___x_529_ = lean_uint32_dec_le(v___x_526_, v___x_528_);
if (v___x_529_ == 0)
{
uint32_t v___x_530_; uint8_t v___x_531_; 
v___x_530_ = lean_uint32_shift_left(v___y_107_, v___x_527_);
v___x_531_ = lean_uint32_dec_le(v___x_526_, v___x_530_);
v___y_512_ = v___x_531_;
goto v___jp_511_;
}
else
{
v___y_512_ = v___x_529_;
goto v___jp_511_;
}
}
v___jp_108_:
{
float v___x_109_; float v___x_110_; float v___x_111_; uint32_t v___x_112_; 
v___x_109_ = lean_float32_of_bits(v___y_106_);
v___x_110_ = lean_float32_of_bits(v___y_107_);
v___x_111_ = lean_float32_mul(v___x_109_, v___x_110_);
v___x_112_ = lean_float32_to_bits(v___x_111_);
return v___x_112_;
}
v___jp_113_:
{
uint32_t v___x_117_; uint32_t v___x_118_; 
v___x_117_ = lean_uint32_land(v___y_114_, v___y_115_);
v___x_118_ = lean_uint32_lor(v___y_116_, v___x_117_);
return v___x_118_;
}
v___jp_119_:
{
uint32_t v___x_123_; uint32_t v___x_124_; 
v___x_123_ = lean_uint32_land(v___y_121_, v___y_120_);
v___x_124_ = lean_uint32_lor(v___y_122_, v___x_123_);
return v___x_124_;
}
v___jp_125_:
{
uint32_t v___x_127_; uint32_t v___x_128_; 
v___x_127_ = 8388608;
v___x_128_ = lean_uint32_lor(v___y_126_, v___x_127_);
return v___x_128_;
}
v___jp_129_:
{
uint8_t v___x_134_; 
v___x_134_ = lean_uint64_dec_eq(v___y_133_, v___y_132_);
if (v___x_134_ == 0)
{
uint64_t v___x_135_; uint8_t v___x_136_; 
v___x_135_ = 8388608ULL;
v___x_136_ = lean_uint64_dec_eq(v___y_133_, v___x_135_);
if (v___x_136_ == 0)
{
uint32_t v___x_137_; 
v___x_137_ = lean_uint64_to_uint32(v___y_133_);
if (v___y_131_ == 0)
{
uint32_t v___x_138_; 
v___x_138_ = 0;
v___y_120_ = v___y_130_;
v___y_121_ = v___x_137_;
v___y_122_ = v___x_138_;
goto v___jp_119_;
}
else
{
uint32_t v___x_139_; 
v___x_139_ = 2147483648;
v___y_120_ = v___y_130_;
v___y_121_ = v___x_137_;
v___y_122_ = v___x_139_;
goto v___jp_119_;
}
}
else
{
if (v___y_131_ == 0)
{
uint32_t v___x_140_; 
v___x_140_ = 0;
v___y_126_ = v___x_140_;
goto v___jp_125_;
}
else
{
uint32_t v___x_141_; 
v___x_141_ = 2147483648;
v___y_126_ = v___x_141_;
goto v___jp_125_;
}
}
}
else
{
if (v___y_131_ == 0)
{
uint32_t v___x_142_; 
v___x_142_ = 0;
return v___x_142_;
}
else
{
uint32_t v___x_143_; 
v___x_143_ = 2147483648;
return v___x_143_;
}
}
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
if (v___y_150_ == 0)
{
uint32_t v___x_157_; 
v___x_157_ = 0;
v___y_114_ = v___x_156_;
v___y_115_ = v___y_149_;
v___y_116_ = v___x_157_;
goto v___jp_113_;
}
else
{
uint32_t v___x_158_; 
v___x_158_ = 2147483648;
v___y_114_ = v___x_156_;
v___y_115_ = v___y_149_;
v___y_116_ = v___x_158_;
goto v___jp_113_;
}
}
else
{
if (v___y_150_ == 0)
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
if (v___y_150_ == 0)
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
v___jp_166_:
{
uint32_t v___x_171_; uint32_t v___x_172_; uint32_t v___x_173_; uint32_t v___x_174_; uint32_t v___x_175_; 
v___x_171_ = lean_uint32_land(v___y_169_, v___x_165_);
v___x_172_ = lean_uint32_shift_left(v___x_171_, v___x_163_);
v___x_173_ = lean_uint32_lor(v___y_170_, v___x_172_);
v___x_174_ = lean_uint32_land(v___y_168_, v___y_167_);
v___x_175_ = lean_uint32_lor(v___x_173_, v___x_174_);
return v___x_175_;
}
v___jp_176_:
{
if (v___y_178_ == 0)
{
uint32_t v___x_181_; 
v___x_181_ = 0;
v___y_167_ = v___y_177_;
v___y_168_ = v___y_180_;
v___y_169_ = v___y_179_;
v___y_170_ = v___x_181_;
goto v___jp_166_;
}
else
{
uint32_t v___x_182_; 
v___x_182_ = 2147483648;
v___y_167_ = v___y_177_;
v___y_168_ = v___y_180_;
v___y_169_ = v___y_179_;
v___y_170_ = v___x_182_;
goto v___jp_166_;
}
}
v___jp_183_:
{
uint64_t v___x_189_; uint64_t v_encodedExponent_190_; uint32_t v___x_191_; uint64_t v___x_192_; uint8_t v___x_193_; 
v___x_189_ = 171ULL;
v_encodedExponent_190_ = lean_uint64_sub(v___y_184_, v___x_189_);
v___x_191_ = lean_uint64_to_uint32(v_encodedExponent_190_);
v___x_192_ = 8388608ULL;
v___x_193_ = lean_uint64_dec_lt(v___y_188_, v___x_192_);
if (v___x_193_ == 0)
{
uint64_t v___x_194_; uint32_t v___x_195_; 
v___x_194_ = lean_uint64_sub(v___y_188_, v___x_192_);
v___x_195_ = lean_uint64_to_uint32(v___x_194_);
v___y_177_ = v___y_185_;
v___y_178_ = v___y_186_;
v___y_179_ = v___x_191_;
v___y_180_ = v___x_195_;
goto v___jp_176_;
}
else
{
uint32_t v___x_196_; 
v___x_196_ = lean_uint64_to_uint32(v___y_187_);
v___y_177_ = v___y_185_;
v___y_178_ = v___y_186_;
v___y_179_ = v___x_191_;
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
if (v___y_199_ == 0)
{
v___y_184_ = v___y_203_;
v___y_185_ = v___y_200_;
v___y_186_ = v___y_201_;
v___y_187_ = v___y_202_;
v___y_188_ = v___y_198_;
goto v___jp_183_;
}
else
{
uint64_t v___x_206_; 
v___x_206_ = 8388608ULL;
v___y_184_ = v___y_203_;
v___y_185_ = v___y_200_;
v___y_186_ = v___y_201_;
v___y_187_ = v___y_202_;
v___y_188_ = v___x_206_;
goto v___jp_183_;
}
}
else
{
if (v___y_201_ == 0)
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
v___y_198_ = v___y_214_;
v___y_199_ = v_carry_216_;
v___y_200_ = v___y_210_;
v___y_201_ = v___y_212_;
v___y_202_ = v___y_213_;
v___y_203_ = v___y_211_;
goto v___jp_197_;
}
else
{
uint64_t v___x_217_; uint64_t v___x_218_; 
v___x_217_ = 1ULL;
v___x_218_ = lean_uint64_add(v___y_211_, v___x_217_);
v___y_198_ = v___y_214_;
v___y_199_ = v_carry_216_;
v___y_200_ = v___y_210_;
v___y_201_ = v___y_212_;
v___y_202_ = v___y_213_;
v___y_203_ = v___x_218_;
goto v___jp_197_;
}
}
v___jp_219_:
{
uint64_t v_position_226_; uint64_t v___x_227_; uint8_t v___x_228_; 
v_position_226_ = lean_uint64_add(v___y_225_, v___y_224_);
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
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
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
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
v___y_214_ = v___y_223_;
goto v___jp_209_;
}
else
{
uint64_t v___x_238_; 
v___x_238_ = 1ULL;
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
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
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
v___y_214_ = v___x_250_;
goto v___jp_209_;
}
else
{
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
v___y_214_ = v_quotient_239_;
goto v___jp_209_;
}
}
else
{
uint64_t v___x_251_; 
v___x_251_ = lean_uint64_add(v_quotient_239_, v___x_240_);
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
v___y_214_ = v___x_251_;
goto v___jp_209_;
}
}
else
{
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
v___y_214_ = v_quotient_239_;
goto v___jp_209_;
}
}
}
else
{
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
v___y_214_ = v___y_221_;
goto v___jp_209_;
}
}
else
{
uint64_t v___x_252_; uint64_t v___x_253_; 
v___x_252_ = lean_uint64_sub(v___x_229_, v___y_225_);
v___x_253_ = lean_uint64_shift_left(v___y_221_, v___x_252_);
v___y_210_ = v___y_220_;
v___y_211_ = v_position_226_;
v___y_212_ = v___y_222_;
v___y_213_ = v___y_223_;
v___y_214_ = v___x_253_;
goto v___jp_209_;
}
}
else
{
uint64_t v___x_254_; uint8_t v___x_255_; 
v___x_254_ = 149ULL;
v___x_255_ = lean_uint64_dec_lt(v___y_224_, v___x_254_);
if (v___x_255_ == 0)
{
uint64_t v___x_256_; uint64_t v___x_257_; 
v___x_256_ = lean_uint64_sub(v___y_224_, v___x_254_);
v___x_257_ = lean_uint64_shift_left(v___y_221_, v___x_256_);
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v___x_257_;
goto v___jp_129_;
}
else
{
uint64_t v___x_258_; uint8_t v___x_259_; 
v___x_258_ = lean_uint64_sub(v___x_254_, v___y_224_);
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
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v___y_223_;
goto v___jp_129_;
}
else
{
uint64_t v___x_263_; uint8_t v___x_264_; 
v___x_263_ = 9223372036854775808ULL;
v___x_264_ = lean_uint64_dec_lt(v___x_263_, v___y_221_);
if (v___x_264_ == 0)
{
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v___y_223_;
goto v___jp_129_;
}
else
{
uint64_t v___x_265_; 
v___x_265_ = 1ULL;
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v___x_265_;
goto v___jp_129_;
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
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v___x_277_;
goto v___jp_129_;
}
else
{
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v_quotient_266_;
goto v___jp_129_;
}
}
else
{
uint64_t v___x_278_; 
v___x_278_ = lean_uint64_add(v_quotient_266_, v___x_267_);
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v___x_278_;
goto v___jp_129_;
}
}
else
{
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v_quotient_266_;
goto v___jp_129_;
}
}
}
else
{
v___y_130_ = v___y_220_;
v___y_131_ = v___y_222_;
v___y_132_ = v___y_223_;
v___y_133_ = v___y_221_;
goto v___jp_129_;
}
}
}
}
v___jp_279_:
{
uint64_t v___x_287_; uint64_t v___x_288_; uint8_t v___x_289_; 
v___x_287_ = 1ULL;
v___x_288_ = lean_uint64_shift_right(v___y_282_, v___x_287_);
v___x_289_ = lean_uint64_dec_eq(v___x_288_, v___y_285_);
if (v___x_289_ == 0)
{
uint64_t v___x_290_; 
v___x_290_ = lean_uint64_add(v___y_286_, v___x_287_);
v___y_220_ = v___y_280_;
v___y_221_ = v___y_281_;
v___y_222_ = v___y_283_;
v___y_223_ = v___y_285_;
v___y_224_ = v___y_284_;
v___y_225_ = v___x_290_;
goto v___jp_219_;
}
else
{
v___y_220_ = v___y_280_;
v___y_221_ = v___y_281_;
v___y_222_ = v___y_283_;
v___y_223_ = v___y_285_;
v___y_224_ = v___y_284_;
v___y_225_ = v___y_286_;
goto v___jp_219_;
}
}
v___jp_291_:
{
uint64_t v___x_301_; uint8_t v___x_302_; 
v___x_301_ = lean_uint64_shift_right(v___y_292_, v___y_297_);
v___x_302_ = lean_uint64_dec_eq(v___x_301_, v___y_298_);
if (v___x_302_ == 0)
{
uint64_t v___x_303_; 
v___x_303_ = lean_uint64_add(v___y_296_, v___y_297_);
v___y_280_ = v___y_293_;
v___y_281_ = v___y_294_;
v___y_282_ = v___y_300_;
v___y_283_ = v___y_295_;
v___y_284_ = v___y_299_;
v___y_285_ = v___y_298_;
v___y_286_ = v___x_303_;
goto v___jp_279_;
}
else
{
v___y_280_ = v___y_293_;
v___y_281_ = v___y_294_;
v___y_282_ = v___y_300_;
v___y_283_ = v___y_295_;
v___y_284_ = v___y_299_;
v___y_285_ = v___y_298_;
v___y_286_ = v___y_296_;
goto v___jp_279_;
}
}
v___jp_304_:
{
uint64_t v___x_312_; uint64_t v___x_313_; uint8_t v___x_314_; 
v___x_312_ = 2ULL;
v___x_313_ = lean_uint64_shift_right(v___y_305_, v___x_312_);
v___x_314_ = lean_uint64_dec_eq(v___x_313_, v___y_310_);
if (v___x_314_ == 0)
{
v___y_292_ = v___y_305_;
v___y_293_ = v___y_306_;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_308_;
v___y_296_ = v___y_311_;
v___y_297_ = v___x_312_;
v___y_298_ = v___y_310_;
v___y_299_ = v___y_309_;
v___y_300_ = v___x_313_;
goto v___jp_291_;
}
else
{
v___y_292_ = v___y_305_;
v___y_293_ = v___y_306_;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_308_;
v___y_296_ = v___y_311_;
v___y_297_ = v___x_312_;
v___y_298_ = v___y_310_;
v___y_299_ = v___y_309_;
v___y_300_ = v___y_305_;
goto v___jp_291_;
}
}
v___jp_315_:
{
uint64_t v___x_325_; uint8_t v___x_326_; 
v___x_325_ = lean_uint64_shift_right(v___y_316_, v___y_317_);
v___x_326_ = lean_uint64_dec_eq(v___x_325_, v___y_322_);
if (v___x_326_ == 0)
{
uint64_t v___x_327_; 
v___x_327_ = lean_uint64_add(v___y_318_, v___y_317_);
v___y_305_ = v___y_324_;
v___y_306_ = v___y_319_;
v___y_307_ = v___y_320_;
v___y_308_ = v___y_321_;
v___y_309_ = v___y_323_;
v___y_310_ = v___y_322_;
v___y_311_ = v___x_327_;
goto v___jp_304_;
}
else
{
v___y_305_ = v___y_324_;
v___y_306_ = v___y_319_;
v___y_307_ = v___y_320_;
v___y_308_ = v___y_321_;
v___y_309_ = v___y_323_;
v___y_310_ = v___y_322_;
v___y_311_ = v___y_318_;
goto v___jp_304_;
}
}
v___jp_328_:
{
uint64_t v___x_336_; uint64_t v___x_337_; uint8_t v___x_338_; 
v___x_336_ = 4ULL;
v___x_337_ = lean_uint64_shift_right(v___y_329_, v___x_336_);
v___x_338_ = lean_uint64_dec_eq(v___x_337_, v___y_334_);
if (v___x_338_ == 0)
{
v___y_316_ = v___y_329_;
v___y_317_ = v___x_336_;
v___y_318_ = v___y_335_;
v___y_319_ = v___y_330_;
v___y_320_ = v___y_331_;
v___y_321_ = v___y_332_;
v___y_322_ = v___y_334_;
v___y_323_ = v___y_333_;
v___y_324_ = v___x_337_;
goto v___jp_315_;
}
else
{
v___y_316_ = v___y_329_;
v___y_317_ = v___x_336_;
v___y_318_ = v___y_335_;
v___y_319_ = v___y_330_;
v___y_320_ = v___y_331_;
v___y_321_ = v___y_332_;
v___y_322_ = v___y_334_;
v___y_323_ = v___y_333_;
v___y_324_ = v___y_329_;
goto v___jp_315_;
}
}
v___jp_339_:
{
uint64_t v___x_349_; uint8_t v___x_350_; 
v___x_349_ = lean_uint64_shift_right(v___y_343_, v___y_342_);
v___x_350_ = lean_uint64_dec_eq(v___x_349_, v___y_346_);
if (v___x_350_ == 0)
{
uint64_t v___x_351_; 
v___x_351_ = lean_uint64_add(v___y_340_, v___y_342_);
v___y_329_ = v___y_348_;
v___y_330_ = v___y_341_;
v___y_331_ = v___y_344_;
v___y_332_ = v___y_345_;
v___y_333_ = v___y_347_;
v___y_334_ = v___y_346_;
v___y_335_ = v___x_351_;
goto v___jp_328_;
}
else
{
v___y_329_ = v___y_348_;
v___y_330_ = v___y_341_;
v___y_331_ = v___y_344_;
v___y_332_ = v___y_345_;
v___y_333_ = v___y_347_;
v___y_334_ = v___y_346_;
v___y_335_ = v___y_340_;
goto v___jp_328_;
}
}
v___jp_352_:
{
uint64_t v___x_360_; uint64_t v___x_361_; uint8_t v___x_362_; 
v___x_360_ = 8ULL;
v___x_361_ = lean_uint64_shift_right(v___y_355_, v___x_360_);
v___x_362_ = lean_uint64_dec_eq(v___x_361_, v___y_358_);
if (v___x_362_ == 0)
{
v___y_340_ = v___y_359_;
v___y_341_ = v___y_353_;
v___y_342_ = v___x_360_;
v___y_343_ = v___y_355_;
v___y_344_ = v___y_354_;
v___y_345_ = v___y_356_;
v___y_346_ = v___y_358_;
v___y_347_ = v___y_357_;
v___y_348_ = v___x_361_;
goto v___jp_339_;
}
else
{
v___y_340_ = v___y_359_;
v___y_341_ = v___y_353_;
v___y_342_ = v___x_360_;
v___y_343_ = v___y_355_;
v___y_344_ = v___y_354_;
v___y_345_ = v___y_356_;
v___y_346_ = v___y_358_;
v___y_347_ = v___y_357_;
v___y_348_ = v___y_355_;
goto v___jp_339_;
}
}
v___jp_363_:
{
uint64_t v___x_373_; uint8_t v___x_374_; 
v___x_373_ = lean_uint64_shift_right(v___y_367_, v___y_365_);
v___x_374_ = lean_uint64_dec_eq(v___x_373_, v___y_370_);
if (v___x_374_ == 0)
{
uint64_t v___x_375_; 
v___x_375_ = lean_uint64_add(v___y_366_, v___y_365_);
v___y_353_ = v___y_364_;
v___y_354_ = v___y_368_;
v___y_355_ = v___y_372_;
v___y_356_ = v___y_369_;
v___y_357_ = v___y_371_;
v___y_358_ = v___y_370_;
v___y_359_ = v___x_375_;
goto v___jp_352_;
}
else
{
v___y_353_ = v___y_364_;
v___y_354_ = v___y_368_;
v___y_355_ = v___y_372_;
v___y_356_ = v___y_369_;
v___y_357_ = v___y_371_;
v___y_358_ = v___y_370_;
v___y_359_ = v___y_366_;
goto v___jp_352_;
}
}
v___jp_376_:
{
uint64_t v___x_384_; uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_384_ = 16ULL;
v___x_385_ = lean_uint64_shift_right(v___y_378_, v___x_384_);
v___x_386_ = lean_uint64_dec_eq(v___x_385_, v___y_382_);
if (v___x_386_ == 0)
{
v___y_364_ = v___y_377_;
v___y_365_ = v___x_384_;
v___y_366_ = v___y_383_;
v___y_367_ = v___y_378_;
v___y_368_ = v___y_379_;
v___y_369_ = v___y_380_;
v___y_370_ = v___y_382_;
v___y_371_ = v___y_381_;
v___y_372_ = v___x_385_;
goto v___jp_363_;
}
else
{
v___y_364_ = v___y_377_;
v___y_365_ = v___x_384_;
v___y_366_ = v___y_383_;
v___y_367_ = v___y_378_;
v___y_368_ = v___y_379_;
v___y_369_ = v___y_380_;
v___y_370_ = v___y_382_;
v___y_371_ = v___y_381_;
v___y_372_ = v___y_378_;
goto v___jp_363_;
}
}
v___jp_387_:
{
uint64_t v___x_395_; uint8_t v___x_396_; 
v___x_395_ = lean_uint64_shift_right(v___y_389_, v___y_393_);
v___x_396_ = lean_uint64_dec_eq(v___x_395_, v___y_391_);
if (v___x_396_ == 0)
{
v___y_377_ = v___y_388_;
v___y_378_ = v___y_394_;
v___y_379_ = v___y_389_;
v___y_380_ = v___y_390_;
v___y_381_ = v___y_392_;
v___y_382_ = v___y_391_;
v___y_383_ = v___y_393_;
goto v___jp_376_;
}
else
{
v___y_377_ = v___y_388_;
v___y_378_ = v___y_394_;
v___y_379_ = v___y_389_;
v___y_380_ = v___y_390_;
v___y_381_ = v___y_392_;
v___y_382_ = v___y_391_;
v___y_383_ = v___y_391_;
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
v___y_391_ = v___x_402_;
v___y_392_ = v___y_401_;
v___y_393_ = v___x_404_;
v___y_394_ = v___x_405_;
goto v___jp_387_;
}
else
{
v___y_388_ = v___y_398_;
v___y_389_ = v___y_399_;
v___y_390_ = v___y_400_;
v___y_391_ = v___x_402_;
v___y_392_ = v___y_401_;
v___y_393_ = v___x_404_;
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
v___x_416_ = lean_uint64_mul(v___y_413_, v___y_412_);
v___x_417_ = lean_uint64_add(v___y_414_, v___y_415_);
v___x_418_ = 281474976710656ULL;
v___x_419_ = lean_uint64_dec_lt(v___x_416_, v___x_418_);
if (v___x_419_ == 0)
{
v___y_398_ = v___y_410_;
v___y_399_ = v___x_416_;
v___y_400_ = v___y_411_;
v___y_401_ = v___x_417_;
goto v___jp_397_;
}
else
{
uint64_t v___x_420_; uint8_t v___x_421_; 
v___x_420_ = 123ULL;
v___x_421_ = lean_uint64_dec_le(v___x_417_, v___x_420_);
if (v___x_421_ == 0)
{
v___y_398_ = v___y_410_;
v___y_399_ = v___x_416_;
v___y_400_ = v___y_411_;
v___y_401_ = v___x_417_;
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
v___y_149_ = v___y_410_;
v___y_150_ = v___y_411_;
v___y_151_ = v___x_422_;
v___y_152_ = v___x_422_;
goto v___jp_148_;
}
else
{
uint64_t v___x_430_; uint8_t v___x_431_; 
v___x_430_ = 9223372036854775808ULL;
v___x_431_ = lean_uint64_dec_lt(v___x_430_, v___x_416_);
if (v___x_431_ == 0)
{
v___y_149_ = v___y_410_;
v___y_150_ = v___y_411_;
v___y_151_ = v___x_422_;
v___y_152_ = v___x_422_;
goto v___jp_148_;
}
else
{
uint64_t v___x_432_; 
v___x_432_ = 1ULL;
v___y_149_ = v___y_410_;
v___y_150_ = v___y_411_;
v___y_151_ = v___x_422_;
v___y_152_ = v___x_432_;
goto v___jp_148_;
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
v___y_149_ = v___y_410_;
v___y_150_ = v___y_411_;
v___y_151_ = v___x_422_;
v___y_152_ = v___x_444_;
goto v___jp_148_;
}
else
{
v___y_149_ = v___y_410_;
v___y_150_ = v___y_411_;
v___y_151_ = v___x_422_;
v___y_152_ = v_quotient_433_;
goto v___jp_148_;
}
}
else
{
uint64_t v___x_445_; 
v___x_445_ = lean_uint64_add(v_quotient_433_, v___x_434_);
v___y_149_ = v___y_410_;
v___y_150_ = v___y_411_;
v___y_151_ = v___x_422_;
v___y_152_ = v___x_445_;
goto v___jp_148_;
}
}
else
{
v___y_149_ = v___y_410_;
v___y_150_ = v___y_411_;
v___y_151_ = v___x_422_;
v___y_152_ = v_quotient_433_;
goto v___jp_148_;
}
}
}
else
{
v___y_149_ = v___y_410_;
v___y_150_ = v___y_411_;
v___y_151_ = v___x_422_;
v___y_152_ = v___x_416_;
goto v___jp_148_;
}
}
else
{
if (v___y_411_ == 0)
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
v___y_411_ = v___y_454_;
v___y_412_ = v___y_453_;
v___y_413_ = v___y_455_;
v___y_414_ = v___y_456_;
v___y_415_ = v___x_461_;
goto v___jp_409_;
}
else
{
v___y_410_ = v___y_452_;
v___y_411_ = v___y_454_;
v___y_412_ = v___y_453_;
v___y_413_ = v___y_455_;
v___y_414_ = v___y_456_;
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
v___y_453_ = v___y_466_;
v___y_454_ = v___y_464_;
v___y_455_ = v___y_465_;
v___y_456_ = v___x_471_;
goto v___jp_451_;
}
else
{
v___y_452_ = v___y_463_;
v___y_453_ = v___y_466_;
v___y_454_ = v___y_464_;
v___y_455_ = v___y_465_;
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
v___x_479_ = lean_uint32_to_uint64(v___y_475_);
v___x_480_ = 8388608ULL;
v___x_481_ = lean_uint64_lor(v___x_479_, v___x_480_);
v___y_463_ = v___y_473_;
v___y_464_ = v___y_474_;
v___y_465_ = v___y_476_;
v___y_466_ = v___x_481_;
goto v___jp_462_;
}
else
{
uint64_t v___x_482_; 
v___x_482_ = lean_uint32_to_uint64(v___y_475_);
v___y_463_ = v___y_473_;
v___y_464_ = v___y_474_;
v___y_465_ = v___y_476_;
v___y_466_ = v___x_482_;
goto v___jp_462_;
}
}
v___jp_483_:
{
uint32_t v___x_485_; uint32_t v_xFraction_486_; uint32_t v_yFraction_487_; uint32_t v___x_488_; uint8_t v___x_489_; 
v___x_485_ = 8388607;
v_xFraction_486_ = lean_uint32_land(v___y_106_, v___x_485_);
v_yFraction_487_ = lean_uint32_land(v___y_107_, v___x_485_);
v___x_488_ = 0;
v___x_489_ = lean_uint32_dec_eq(v_ex_448_, v___x_488_);
if (v___x_489_ == 0)
{
uint64_t v___x_490_; uint64_t v___x_491_; uint64_t v___x_492_; 
v___x_490_ = lean_uint32_to_uint64(v_xFraction_486_);
v___x_491_ = 8388608ULL;
v___x_492_ = lean_uint64_lor(v___x_490_, v___x_491_);
v___y_473_ = v___x_485_;
v___y_474_ = v___y_484_;
v___y_475_ = v_yFraction_487_;
v___y_476_ = v___x_492_;
goto v___jp_472_;
}
else
{
uint64_t v___x_493_; 
v___x_493_ = lean_uint32_to_uint64(v_xFraction_486_);
v___y_473_ = v___x_485_;
v___y_474_ = v___y_484_;
v___y_475_ = v_yFraction_487_;
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
if (v___y_501_ == 0)
{
if (v___y_503_ == 0)
{
v___y_498_ = v___y_502_;
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
v___y_498_ = v___y_502_;
v___y_499_ = v___y_503_;
goto v___jp_497_;
}
}
v___jp_504_:
{
uint32_t v___x_507_; uint32_t v___x_508_; uint32_t v___x_509_; uint8_t v___x_510_; 
v___x_507_ = 2147483648;
v___x_508_ = lean_uint32_land(v___y_107_, v___x_507_);
v___x_509_ = 0;
v___x_510_ = lean_uint32_dec_eq(v___x_508_, v___x_509_);
if (v___x_510_ == 0)
{
v___y_501_ = v___y_506_;
v___y_502_ = v___y_505_;
v___y_503_ = v___x_496_;
goto v___jp_500_;
}
else
{
v___y_501_ = v___y_506_;
v___y_502_ = v___y_505_;
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
v___x_514_ = lean_uint32_land(v___y_106_, v___x_513_);
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
v___x_517_ = lean_uint32_to_nat(v___y_106_);
v___x_518_ = lean_uint32_to_nat(v___y_107_);
v___x_519_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_517_, v___x_518_);
v___x_520_ = lean_uint32_of_nat(v___x_519_);
lean_dec(v___x_519_);
return v___x_520_;
}
}
v___jp_521_:
{
uint8_t v___x_522_; 
v___x_522_ = lean_uint32_dec_eq(v_ey_450_, v___x_165_);
if (v___x_522_ == 0)
{
goto v___jp_108_;
}
else
{
if (v___x_496_ == 0)
{
uint32_t v___x_523_; 
v___x_523_ = lp_competition_Submission_FastMul_mul(v___y_106_, v___y_107_);
return v___x_523_;
}
else
{
goto v___jp_108_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_532_, lean_object* v___y_533_){
_start:
{
uint32_t v___y_1836__boxed_534_; uint32_t v___y_1837__boxed_535_; uint32_t v_res_536_; lean_object* v_r_537_; 
v___y_1836__boxed_534_ = lean_unbox_uint32(v___y_532_);
lean_dec(v___y_532_);
v___y_1837__boxed_535_ = lean_unbox_uint32(v___y_533_);
lean_dec(v___y_533_);
v_res_536_ = lp_competition_main___lam__1(v___y_1836__boxed_534_, v___y_1837__boxed_535_);
v_r_537_ = lean_box_uint32(v_res_536_);
return v_r_537_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___f_543_; lean_object* v___f_544_; lean_object* v___x_545_; lean_object* v___x_546_; lean_object* v___x_547_; 
v___f_543_ = ((lean_object*)(lp_competition_main___closed__0));
v___f_544_ = ((lean_object*)(lp_competition_main___closed__1));
v___x_545_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_546_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_547_ = lp_competition_Bench_runFull(v___f_543_, v___f_544_, v___x_545_, v___x_546_);
return v___x_547_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_548_){
_start:
{
lean_object* v_res_549_; 
v_res_549_ = _lean_main();
return v_res_549_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
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
