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
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_uint32_add(uint32_t, uint32_t);
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
float v___y_4_; float v___y_5_; float v___y_9_; uint8_t v___y_10_; float v___y_25_; uint8_t v___y_35_; uint32_t v___x_49_; uint32_t v___x_50_; uint32_t v___x_51_; uint32_t v___x_52_; uint8_t v___x_53_; 
v___x_49_ = 23;
v___x_50_ = lean_uint32_shift_right(v___y_1_, v___x_49_);
v___x_51_ = 255;
v___x_52_ = lean_uint32_land(v___x_50_, v___x_51_);
v___x_53_ = lean_uint32_dec_eq(v___x_52_, v___x_51_);
if (v___x_53_ == 0)
{
uint32_t v___x_54_; uint32_t v___x_55_; uint8_t v___x_56_; 
v___x_54_ = lean_uint32_shift_right(v___y_2_, v___x_49_);
v___x_55_ = lean_uint32_land(v___x_54_, v___x_51_);
v___x_56_ = lean_uint32_dec_eq(v___x_55_, v___x_51_);
if (v___x_56_ == 0)
{
uint32_t v___x_57_; uint32_t v_a_58_; uint32_t v___x_59_; uint32_t v___x_60_; uint32_t v___x_61_; uint8_t v___x_62_; 
v___x_57_ = 2147483647;
v_a_58_ = lean_uint32_land(v___y_1_, v___x_57_);
v___x_59_ = 201326591;
v___x_60_ = 1;
v___x_61_ = lean_uint32_sub(v_a_58_, v___x_60_);
v___x_62_ = lean_uint32_dec_le(v___x_59_, v___x_61_);
if (v___x_62_ == 0)
{
v___y_35_ = v___x_62_;
goto v___jp_34_;
}
else
{
uint32_t v___x_63_; uint8_t v___x_64_; 
v___x_63_ = 2139095040;
v___x_64_ = lean_uint32_dec_lt(v_a_58_, v___x_63_);
v___y_35_ = v___x_64_;
goto v___jp_34_;
}
}
else
{
uint32_t v___x_65_; 
v___x_65_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_65_;
}
}
else
{
uint32_t v___x_66_; 
v___x_66_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_66_;
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
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_67_, lean_object* v___y_68_){
_start:
{
uint32_t v___y_2696__boxed_69_; uint32_t v___y_2697__boxed_70_; uint32_t v_res_71_; lean_object* v_r_72_; 
v___y_2696__boxed_69_ = lean_unbox_uint32(v___y_67_);
lean_dec(v___y_67_);
v___y_2697__boxed_70_ = lean_unbox_uint32(v___y_68_);
lean_dec(v___y_68_);
v_res_71_ = lp_competition_main___lam__0(v___y_2696__boxed_69_, v___y_2697__boxed_70_);
v_r_72_ = lean_box_uint32(v_res_71_);
return v_r_72_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_73_, uint32_t v___y_74_){
_start:
{
uint32_t v___y_76_; uint32_t v___y_80_; uint32_t v___y_84_; uint32_t v___y_85_; uint32_t v___y_86_; uint8_t v___y_90_; uint64_t v___y_91_; uint32_t v___y_92_; uint64_t v___y_93_; uint32_t v___y_105_; uint32_t v___y_106_; uint32_t v___y_107_; uint8_t v___y_111_; uint64_t v___y_112_; uint32_t v___y_113_; uint64_t v___y_114_; uint32_t v___y_126_; uint32_t v___y_130_; uint32_t v___y_131_; uint32_t v___y_132_; uint32_t v___y_136_; uint64_t v___y_137_; uint8_t v___y_138_; uint64_t v___y_139_; uint32_t v___x_150_; uint32_t v___x_151_; uint32_t v___x_152_; uint32_t v___y_154_; uint32_t v___y_155_; uint32_t v___y_156_; uint32_t v___y_157_; uint32_t v___y_164_; uint32_t v___y_165_; uint8_t v___y_166_; uint32_t v___y_167_; uint32_t v___y_171_; uint64_t v___y_172_; uint8_t v___y_173_; uint64_t v___y_174_; uint64_t v___y_175_; uint64_t v___y_185_; uint32_t v___y_186_; uint64_t v___y_187_; uint8_t v___y_188_; uint8_t v___y_189_; uint64_t v___y_190_; uint64_t v___y_197_; uint32_t v___y_198_; uint64_t v___y_199_; uint8_t v___y_200_; uint64_t v___y_201_; uint32_t v___y_207_; uint64_t v___y_208_; uint64_t v___y_209_; uint64_t v___y_210_; uint8_t v___y_211_; uint64_t v___y_212_; uint32_t v___y_267_; uint64_t v___y_268_; uint64_t v___y_269_; uint64_t v___y_270_; uint64_t v___y_271_; uint8_t v___y_272_; uint64_t v___y_273_; uint32_t v___y_279_; uint64_t v___y_280_; uint64_t v___y_281_; uint64_t v___y_282_; uint64_t v___y_283_; uint8_t v___y_284_; uint64_t v___y_285_; uint64_t v___y_286_; uint64_t v___y_287_; uint32_t v___y_292_; uint64_t v___y_293_; uint64_t v___y_294_; uint64_t v___y_295_; uint8_t v___y_296_; uint64_t v___y_297_; uint64_t v___y_298_; uint32_t v___y_303_; uint64_t v___y_304_; uint64_t v___y_305_; uint64_t v___y_306_; uint64_t v___y_307_; uint8_t v___y_308_; uint64_t v___y_309_; uint64_t v___y_310_; uint64_t v___y_311_; uint32_t v___y_316_; uint64_t v___y_317_; uint64_t v___y_318_; uint64_t v___y_319_; uint64_t v___y_320_; uint8_t v___y_321_; uint64_t v___y_322_; uint32_t v___y_327_; uint64_t v___y_328_; uint64_t v___y_329_; uint64_t v___y_330_; uint64_t v___y_331_; uint8_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint64_t v___y_335_; uint32_t v___y_340_; uint64_t v___y_341_; uint64_t v___y_342_; uint64_t v___y_343_; uint8_t v___y_344_; uint64_t v___y_345_; uint64_t v___y_346_; uint64_t v___y_351_; uint32_t v___y_352_; uint64_t v___y_353_; uint64_t v___y_354_; uint64_t v___y_355_; uint64_t v___y_356_; uint8_t v___y_357_; uint64_t v___y_358_; uint64_t v___y_359_; uint32_t v___y_364_; uint64_t v___y_365_; uint64_t v___y_366_; uint64_t v___y_367_; uint8_t v___y_368_; uint64_t v___y_369_; uint64_t v___y_370_; uint32_t v___y_375_; uint64_t v___y_376_; uint64_t v___y_377_; uint64_t v___y_378_; uint64_t v___y_379_; uint8_t v___y_380_; uint64_t v___y_381_; uint32_t v___y_385_; uint64_t v___y_386_; uint64_t v___y_387_; uint64_t v___y_388_; uint8_t v___y_389_; uint32_t v___y_394_; uint64_t v___y_395_; uint64_t v___y_396_; uint64_t v___y_397_; uint8_t v___y_398_; uint64_t v___y_399_; uint32_t v___y_415_; uint32_t v___y_416_; uint32_t v___y_417_; uint32_t v___y_418_; uint8_t v___y_425_; uint32_t v___y_426_; uint32_t v___y_427_; uint32_t v___y_428_; uint64_t v___y_432_; uint8_t v___y_433_; uint64_t v___y_434_; uint32_t v___y_435_; uint64_t v___y_436_; uint8_t v___y_446_; uint8_t v___y_447_; uint64_t v___y_448_; uint64_t v___y_449_; uint32_t v___y_450_; uint64_t v___y_451_; uint64_t v___y_458_; uint8_t v___y_459_; uint64_t v___y_460_; uint32_t v___y_461_; uint64_t v___y_462_; uint64_t v___y_468_; uint8_t v___y_469_; uint64_t v___y_470_; uint32_t v___y_471_; uint64_t v___y_472_; uint64_t v___y_473_; uint64_t v___y_528_; uint8_t v___y_529_; uint64_t v___y_530_; uint64_t v___y_531_; uint32_t v___y_532_; uint64_t v___y_533_; uint64_t v___y_534_; uint64_t v___y_540_; uint64_t v___y_541_; uint8_t v___y_542_; uint64_t v___y_543_; uint64_t v___y_544_; uint64_t v___y_545_; uint32_t v___y_546_; uint64_t v___y_547_; uint64_t v___y_548_; uint64_t v___y_553_; uint8_t v___y_554_; uint64_t v___y_555_; uint64_t v___y_556_; uint64_t v___y_557_; uint32_t v___y_558_; uint64_t v___y_559_; uint64_t v___y_564_; uint64_t v___y_565_; uint8_t v___y_566_; uint64_t v___y_567_; uint64_t v___y_568_; uint64_t v___y_569_; uint32_t v___y_570_; uint64_t v___y_571_; uint64_t v___y_572_; uint64_t v___y_577_; uint8_t v___y_578_; uint64_t v___y_579_; uint64_t v___y_580_; uint64_t v___y_581_; uint32_t v___y_582_; uint64_t v___y_583_; uint64_t v___y_588_; uint8_t v___y_589_; uint64_t v___y_590_; uint64_t v___y_591_; uint64_t v___y_592_; uint32_t v___y_593_; uint64_t v___y_594_; uint64_t v___y_595_; uint64_t v___y_596_; uint64_t v___y_601_; uint8_t v___y_602_; uint64_t v___y_603_; uint64_t v___y_604_; uint64_t v___y_605_; uint32_t v___y_606_; uint64_t v___y_607_; uint64_t v___y_612_; uint64_t v___y_613_; uint64_t v___y_614_; uint8_t v___y_615_; uint64_t v___y_616_; uint32_t v___y_617_; uint64_t v___y_618_; uint64_t v___y_619_; uint64_t v___y_620_; uint64_t v___y_625_; uint8_t v___y_626_; uint64_t v___y_627_; uint64_t v___y_628_; uint32_t v___y_629_; uint64_t v___y_630_; uint64_t v___y_631_; uint64_t v___y_636_; uint8_t v___y_637_; uint64_t v___y_638_; uint32_t v___y_639_; uint64_t v___y_640_; uint64_t v___y_641_; uint64_t v___y_642_; uint64_t v___y_646_; uint8_t v___y_647_; uint64_t v___y_648_; uint32_t v___y_649_; uint64_t v___y_658_; uint8_t v___y_659_; uint64_t v___y_660_; uint64_t v___y_661_; uint32_t v___y_662_; uint64_t v___y_663_; uint32_t v_ex_696_; uint32_t v___x_697_; uint32_t v_ey_698_; uint64_t v___y_700_; uint64_t v___y_701_; uint32_t v___y_702_; uint8_t v___y_703_; uint64_t v___y_704_; uint32_t v___y_711_; uint64_t v___y_712_; uint8_t v___y_713_; uint64_t v___y_714_; uint32_t v___y_721_; uint32_t v___y_722_; uint8_t v___y_723_; uint64_t v___y_724_; uint8_t v___y_732_; uint8_t v___y_745_; uint8_t v___y_746_; uint8_t v___y_747_; uint8_t v___y_749_; uint8_t v___y_750_; uint8_t v___y_757_; uint64_t v___y_768_; uint8_t v___y_769_; uint64_t v___y_770_; uint32_t v___y_771_; uint64_t v___y_772_; uint8_t v___y_779_; uint64_t v___y_780_; uint32_t v___y_781_; uint64_t v___y_782_; uint32_t v___y_789_; uint8_t v___y_790_; uint32_t v___y_791_; uint64_t v___y_792_; uint8_t v___y_800_; uint32_t v___x_810_; uint32_t v___x_811_; uint8_t v___x_812_; uint8_t v___y_814_; uint8_t v___y_815_; uint8_t v___y_817_; uint8_t v___y_818_; uint8_t v___y_819_; uint8_t v___y_821_; uint8_t v___y_822_; uint8_t v___y_828_; 
v___x_150_ = 23;
v___x_151_ = lean_uint32_shift_right(v___y_73_, v___x_150_);
v___x_152_ = 255;
v_ex_696_ = lean_uint32_land(v___x_151_, v___x_152_);
v___x_697_ = lean_uint32_shift_right(v___y_74_, v___x_150_);
v_ey_698_ = lean_uint32_land(v___x_697_, v___x_152_);
v___x_810_ = lean_uint32_add(v_ex_696_, v_ey_698_);
v___x_811_ = 128;
v___x_812_ = lean_uint32_dec_lt(v___x_810_, v___x_811_);
if (v___x_812_ == 0)
{
uint32_t v___x_837_; uint32_t v___x_838_; uint32_t v___x_839_; uint8_t v___x_840_; 
v___x_837_ = 4278190080;
v___x_838_ = 1;
v___x_839_ = lean_uint32_shift_left(v___y_73_, v___x_838_);
v___x_840_ = lean_uint32_dec_le(v___x_837_, v___x_839_);
if (v___x_840_ == 0)
{
uint32_t v___x_841_; uint8_t v___x_842_; 
v___x_841_ = lean_uint32_shift_left(v___y_74_, v___x_838_);
v___x_842_ = lean_uint32_dec_le(v___x_837_, v___x_841_);
v___y_757_ = v___x_842_;
goto v___jp_756_;
}
else
{
v___y_757_ = v___x_840_;
goto v___jp_756_;
}
}
else
{
uint32_t v___x_843_; uint32_t v___x_844_; uint32_t v___x_845_; uint8_t v___x_846_; 
v___x_843_ = 4278190080;
v___x_844_ = 1;
v___x_845_ = lean_uint32_shift_left(v___y_73_, v___x_844_);
v___x_846_ = lean_uint32_dec_le(v___x_843_, v___x_845_);
if (v___x_846_ == 0)
{
uint32_t v___x_847_; uint8_t v___x_848_; 
v___x_847_ = lean_uint32_shift_left(v___y_74_, v___x_844_);
v___x_848_ = lean_uint32_dec_le(v___x_843_, v___x_847_);
v___y_828_ = v___x_848_;
goto v___jp_827_;
}
else
{
v___y_828_ = v___x_846_;
goto v___jp_827_;
}
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
uint32_t v___x_81_; uint32_t v___x_82_; 
v___x_81_ = 8388608;
v___x_82_ = lean_uint32_lor(v___y_80_, v___x_81_);
return v___x_82_;
}
v___jp_83_:
{
uint32_t v___x_87_; uint32_t v___x_88_; 
v___x_87_ = lean_uint32_land(v___y_84_, v___y_85_);
v___x_88_ = lean_uint32_lor(v___y_86_, v___x_87_);
return v___x_88_;
}
v___jp_89_:
{
uint8_t v___x_94_; 
v___x_94_ = lean_uint64_dec_eq(v___y_93_, v___y_91_);
if (v___x_94_ == 0)
{
uint64_t v___x_95_; uint8_t v___x_96_; 
v___x_95_ = 8388608ULL;
v___x_96_ = lean_uint64_dec_eq(v___y_93_, v___x_95_);
if (v___x_96_ == 0)
{
uint32_t v___x_97_; 
v___x_97_ = lean_uint64_to_uint32(v___y_93_);
if (v___y_90_ == 0)
{
uint32_t v___x_98_; 
v___x_98_ = 0;
v___y_84_ = v___x_97_;
v___y_85_ = v___y_92_;
v___y_86_ = v___x_98_;
goto v___jp_83_;
}
else
{
uint32_t v___x_99_; 
v___x_99_ = 2147483648;
v___y_84_ = v___x_97_;
v___y_85_ = v___y_92_;
v___y_86_ = v___x_99_;
goto v___jp_83_;
}
}
else
{
if (v___y_90_ == 0)
{
uint32_t v___x_100_; 
v___x_100_ = 0;
v___y_80_ = v___x_100_;
goto v___jp_79_;
}
else
{
uint32_t v___x_101_; 
v___x_101_ = 2147483648;
v___y_80_ = v___x_101_;
goto v___jp_79_;
}
}
}
else
{
if (v___y_90_ == 0)
{
uint32_t v___x_102_; 
v___x_102_ = 0;
return v___x_102_;
}
else
{
uint32_t v___x_103_; 
v___x_103_ = 2147483648;
return v___x_103_;
}
}
}
v___jp_104_:
{
uint32_t v___x_108_; uint32_t v___x_109_; 
v___x_108_ = lean_uint32_land(v___y_105_, v___y_106_);
v___x_109_ = lean_uint32_lor(v___y_107_, v___x_108_);
return v___x_109_;
}
v___jp_110_:
{
uint8_t v___x_115_; 
v___x_115_ = lean_uint64_dec_eq(v___y_114_, v___y_112_);
if (v___x_115_ == 0)
{
uint64_t v___x_116_; uint8_t v___x_117_; 
v___x_116_ = 8388608ULL;
v___x_117_ = lean_uint64_dec_eq(v___y_114_, v___x_116_);
if (v___x_117_ == 0)
{
uint32_t v___x_118_; 
v___x_118_ = lean_uint64_to_uint32(v___y_114_);
if (v___y_111_ == 0)
{
uint32_t v___x_119_; 
v___x_119_ = 0;
v___y_105_ = v___x_118_;
v___y_106_ = v___y_113_;
v___y_107_ = v___x_119_;
goto v___jp_104_;
}
else
{
uint32_t v___x_120_; 
v___x_120_ = 2147483648;
v___y_105_ = v___x_118_;
v___y_106_ = v___y_113_;
v___y_107_ = v___x_120_;
goto v___jp_104_;
}
}
else
{
if (v___y_111_ == 0)
{
uint32_t v___x_121_; 
v___x_121_ = 0;
v___y_76_ = v___x_121_;
goto v___jp_75_;
}
else
{
uint32_t v___x_122_; 
v___x_122_ = 2147483648;
v___y_76_ = v___x_122_;
goto v___jp_75_;
}
}
}
else
{
if (v___y_111_ == 0)
{
uint32_t v___x_123_; 
v___x_123_ = 0;
return v___x_123_;
}
else
{
uint32_t v___x_124_; 
v___x_124_ = 2147483648;
return v___x_124_;
}
}
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
uint32_t v___x_133_; uint32_t v___x_134_; 
v___x_133_ = lean_uint32_land(v___y_131_, v___y_130_);
v___x_134_ = lean_uint32_lor(v___y_132_, v___x_133_);
return v___x_134_;
}
v___jp_135_:
{
uint8_t v___x_140_; 
v___x_140_ = lean_uint64_dec_eq(v___y_139_, v___y_137_);
if (v___x_140_ == 0)
{
uint64_t v___x_141_; uint8_t v___x_142_; 
v___x_141_ = 8388608ULL;
v___x_142_ = lean_uint64_dec_eq(v___y_139_, v___x_141_);
if (v___x_142_ == 0)
{
uint32_t v___x_143_; 
v___x_143_ = lean_uint64_to_uint32(v___y_139_);
if (v___y_138_ == 0)
{
uint32_t v___x_144_; 
v___x_144_ = 0;
v___y_130_ = v___y_136_;
v___y_131_ = v___x_143_;
v___y_132_ = v___x_144_;
goto v___jp_129_;
}
else
{
uint32_t v___x_145_; 
v___x_145_ = 2147483648;
v___y_130_ = v___y_136_;
v___y_131_ = v___x_143_;
v___y_132_ = v___x_145_;
goto v___jp_129_;
}
}
else
{
if (v___y_138_ == 0)
{
uint32_t v___x_146_; 
v___x_146_ = 0;
v___y_126_ = v___x_146_;
goto v___jp_125_;
}
else
{
uint32_t v___x_147_; 
v___x_147_ = 2147483648;
v___y_126_ = v___x_147_;
goto v___jp_125_;
}
}
}
else
{
if (v___y_138_ == 0)
{
uint32_t v___x_148_; 
v___x_148_ = 0;
return v___x_148_;
}
else
{
uint32_t v___x_149_; 
v___x_149_ = 2147483648;
return v___x_149_;
}
}
}
v___jp_153_:
{
uint32_t v___x_158_; uint32_t v___x_159_; uint32_t v___x_160_; uint32_t v___x_161_; uint32_t v___x_162_; 
v___x_158_ = lean_uint32_land(v___y_155_, v___x_152_);
v___x_159_ = lean_uint32_shift_left(v___x_158_, v___x_150_);
v___x_160_ = lean_uint32_lor(v___y_157_, v___x_159_);
v___x_161_ = lean_uint32_land(v___y_156_, v___y_154_);
v___x_162_ = lean_uint32_lor(v___x_160_, v___x_161_);
return v___x_162_;
}
v___jp_163_:
{
if (v___y_166_ == 0)
{
uint32_t v___x_168_; 
v___x_168_ = 0;
v___y_154_ = v___y_164_;
v___y_155_ = v___y_165_;
v___y_156_ = v___y_167_;
v___y_157_ = v___x_168_;
goto v___jp_153_;
}
else
{
uint32_t v___x_169_; 
v___x_169_ = 2147483648;
v___y_154_ = v___y_164_;
v___y_155_ = v___y_165_;
v___y_156_ = v___y_167_;
v___y_157_ = v___x_169_;
goto v___jp_153_;
}
}
v___jp_170_:
{
uint64_t v___x_176_; uint64_t v_encodedExponent_177_; uint32_t v___x_178_; uint64_t v___x_179_; uint8_t v___x_180_; 
v___x_176_ = 171ULL;
v_encodedExponent_177_ = lean_uint64_sub(v___y_174_, v___x_176_);
v___x_178_ = lean_uint64_to_uint32(v_encodedExponent_177_);
v___x_179_ = 8388608ULL;
v___x_180_ = lean_uint64_dec_lt(v___y_175_, v___x_179_);
if (v___x_180_ == 0)
{
uint64_t v___x_181_; uint32_t v___x_182_; 
v___x_181_ = lean_uint64_sub(v___y_175_, v___x_179_);
v___x_182_ = lean_uint64_to_uint32(v___x_181_);
v___y_164_ = v___y_171_;
v___y_165_ = v___x_178_;
v___y_166_ = v___y_173_;
v___y_167_ = v___x_182_;
goto v___jp_163_;
}
else
{
uint32_t v___x_183_; 
v___x_183_ = lean_uint64_to_uint32(v___y_172_);
v___y_164_ = v___y_171_;
v___y_165_ = v___x_178_;
v___y_166_ = v___y_173_;
v___y_167_ = v___x_183_;
goto v___jp_163_;
}
}
v___jp_184_:
{
uint64_t v___x_191_; uint8_t v___x_192_; 
v___x_191_ = 425ULL;
v___x_192_ = lean_uint64_dec_lt(v___x_191_, v___y_190_);
if (v___x_192_ == 0)
{
if (v___y_188_ == 0)
{
v___y_171_ = v___y_186_;
v___y_172_ = v___y_187_;
v___y_173_ = v___y_189_;
v___y_174_ = v___y_190_;
v___y_175_ = v___y_185_;
goto v___jp_170_;
}
else
{
uint64_t v___x_193_; 
v___x_193_ = 8388608ULL;
v___y_171_ = v___y_186_;
v___y_172_ = v___y_187_;
v___y_173_ = v___y_189_;
v___y_174_ = v___y_190_;
v___y_175_ = v___x_193_;
goto v___jp_170_;
}
}
else
{
if (v___y_189_ == 0)
{
uint32_t v___x_194_; 
v___x_194_ = 2139095040;
return v___x_194_;
}
else
{
uint32_t v___x_195_; 
v___x_195_ = 4286578688;
return v___x_195_;
}
}
}
v___jp_196_:
{
uint64_t v___x_202_; uint8_t v_carry_203_; 
v___x_202_ = 16777216ULL;
v_carry_203_ = lean_uint64_dec_eq(v___y_201_, v___x_202_);
if (v_carry_203_ == 0)
{
v___y_185_ = v___y_201_;
v___y_186_ = v___y_198_;
v___y_187_ = v___y_199_;
v___y_188_ = v_carry_203_;
v___y_189_ = v___y_200_;
v___y_190_ = v___y_197_;
goto v___jp_184_;
}
else
{
uint64_t v___x_204_; uint64_t v___x_205_; 
v___x_204_ = 1ULL;
v___x_205_ = lean_uint64_add(v___y_197_, v___x_204_);
v___y_185_ = v___y_201_;
v___y_186_ = v___y_198_;
v___y_187_ = v___y_199_;
v___y_188_ = v_carry_203_;
v___y_189_ = v___y_200_;
v___y_190_ = v___x_205_;
goto v___jp_184_;
}
}
v___jp_206_:
{
uint64_t v_position_213_; uint64_t v___x_214_; uint8_t v___x_215_; 
v_position_213_ = lean_uint64_add(v___y_212_, v___y_210_);
v___x_214_ = 172ULL;
v___x_215_ = lean_uint64_dec_lt(v_position_213_, v___x_214_);
if (v___x_215_ == 0)
{
uint64_t v___x_216_; uint8_t v___x_217_; 
v___x_216_ = 23ULL;
v___x_217_ = lean_uint64_dec_lt(v___y_212_, v___x_216_);
if (v___x_217_ == 0)
{
uint64_t v___x_218_; uint8_t v___x_219_; 
v___x_218_ = lean_uint64_sub(v___y_212_, v___x_216_);
v___x_219_ = lean_uint64_dec_eq(v___x_218_, v___y_209_);
if (v___x_219_ == 0)
{
uint64_t v___x_220_; uint8_t v___x_221_; 
v___x_220_ = 64ULL;
v___x_221_ = lean_uint64_dec_lt(v___x_218_, v___x_220_);
if (v___x_221_ == 0)
{
uint8_t v___x_222_; 
v___x_222_ = lean_uint64_dec_eq(v___x_218_, v___x_220_);
if (v___x_222_ == 0)
{
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v___y_209_;
goto v___jp_196_;
}
else
{
uint64_t v___x_223_; uint8_t v___x_224_; 
v___x_223_ = 9223372036854775808ULL;
v___x_224_ = lean_uint64_dec_lt(v___x_223_, v___y_208_);
if (v___x_224_ == 0)
{
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v___y_209_;
goto v___jp_196_;
}
else
{
uint64_t v___x_225_; 
v___x_225_ = 1ULL;
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v___x_225_;
goto v___jp_196_;
}
}
}
else
{
uint64_t v_quotient_226_; uint64_t v___x_227_; uint64_t v___x_228_; uint64_t v___x_229_; uint64_t v_remainder_230_; uint64_t v___x_231_; uint64_t v_half_232_; uint8_t v___x_233_; 
v_quotient_226_ = lean_uint64_shift_right(v___y_208_, v___x_218_);
v___x_227_ = 1ULL;
v___x_228_ = lean_uint64_shift_left(v___x_227_, v___x_218_);
v___x_229_ = lean_uint64_sub(v___x_228_, v___x_227_);
v_remainder_230_ = lean_uint64_land(v___y_208_, v___x_229_);
v___x_231_ = lean_uint64_sub(v___x_218_, v___x_227_);
v_half_232_ = lean_uint64_shift_left(v___x_227_, v___x_231_);
v___x_233_ = lean_uint64_dec_lt(v_remainder_230_, v_half_232_);
if (v___x_233_ == 0)
{
uint8_t v___x_234_; 
v___x_234_ = lean_uint64_dec_lt(v_half_232_, v_remainder_230_);
if (v___x_234_ == 0)
{
uint64_t v___x_235_; uint8_t v___x_236_; 
v___x_235_ = lean_uint64_land(v_quotient_226_, v___x_227_);
v___x_236_ = lean_uint64_dec_eq(v___x_235_, v___y_209_);
if (v___x_236_ == 0)
{
uint64_t v___x_237_; 
v___x_237_ = lean_uint64_add(v_quotient_226_, v___x_227_);
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v___x_237_;
goto v___jp_196_;
}
else
{
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v_quotient_226_;
goto v___jp_196_;
}
}
else
{
uint64_t v___x_238_; 
v___x_238_ = lean_uint64_add(v_quotient_226_, v___x_227_);
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v___x_238_;
goto v___jp_196_;
}
}
else
{
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v_quotient_226_;
goto v___jp_196_;
}
}
}
else
{
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v___y_208_;
goto v___jp_196_;
}
}
else
{
uint64_t v___x_239_; uint64_t v___x_240_; 
v___x_239_ = lean_uint64_sub(v___x_216_, v___y_212_);
v___x_240_ = lean_uint64_shift_left(v___y_208_, v___x_239_);
v___y_197_ = v_position_213_;
v___y_198_ = v___y_207_;
v___y_199_ = v___y_209_;
v___y_200_ = v___y_211_;
v___y_201_ = v___x_240_;
goto v___jp_196_;
}
}
else
{
uint64_t v___x_241_; uint8_t v___x_242_; 
v___x_241_ = 149ULL;
v___x_242_ = lean_uint64_dec_lt(v___y_210_, v___x_241_);
if (v___x_242_ == 0)
{
uint64_t v___x_243_; uint64_t v___x_244_; 
v___x_243_ = lean_uint64_sub(v___y_210_, v___x_241_);
v___x_244_ = lean_uint64_shift_left(v___y_208_, v___x_243_);
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v___x_244_;
goto v___jp_135_;
}
else
{
uint64_t v___x_245_; uint8_t v___x_246_; 
v___x_245_ = lean_uint64_sub(v___x_241_, v___y_210_);
v___x_246_ = lean_uint64_dec_eq(v___x_245_, v___y_209_);
if (v___x_246_ == 0)
{
uint64_t v___x_247_; uint8_t v___x_248_; 
v___x_247_ = 64ULL;
v___x_248_ = lean_uint64_dec_lt(v___x_245_, v___x_247_);
if (v___x_248_ == 0)
{
uint8_t v___x_249_; 
v___x_249_ = lean_uint64_dec_eq(v___x_245_, v___x_247_);
if (v___x_249_ == 0)
{
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v___y_209_;
goto v___jp_135_;
}
else
{
uint64_t v___x_250_; uint8_t v___x_251_; 
v___x_250_ = 9223372036854775808ULL;
v___x_251_ = lean_uint64_dec_lt(v___x_250_, v___y_208_);
if (v___x_251_ == 0)
{
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v___y_209_;
goto v___jp_135_;
}
else
{
uint64_t v___x_252_; 
v___x_252_ = 1ULL;
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v___x_252_;
goto v___jp_135_;
}
}
}
else
{
uint64_t v_quotient_253_; uint64_t v___x_254_; uint64_t v___x_255_; uint64_t v___x_256_; uint64_t v_remainder_257_; uint64_t v___x_258_; uint64_t v_half_259_; uint8_t v___x_260_; 
v_quotient_253_ = lean_uint64_shift_right(v___y_208_, v___x_245_);
v___x_254_ = 1ULL;
v___x_255_ = lean_uint64_shift_left(v___x_254_, v___x_245_);
v___x_256_ = lean_uint64_sub(v___x_255_, v___x_254_);
v_remainder_257_ = lean_uint64_land(v___y_208_, v___x_256_);
v___x_258_ = lean_uint64_sub(v___x_245_, v___x_254_);
v_half_259_ = lean_uint64_shift_left(v___x_254_, v___x_258_);
v___x_260_ = lean_uint64_dec_lt(v_remainder_257_, v_half_259_);
if (v___x_260_ == 0)
{
uint8_t v___x_261_; 
v___x_261_ = lean_uint64_dec_lt(v_half_259_, v_remainder_257_);
if (v___x_261_ == 0)
{
uint64_t v___x_262_; uint8_t v___x_263_; 
v___x_262_ = lean_uint64_land(v_quotient_253_, v___x_254_);
v___x_263_ = lean_uint64_dec_eq(v___x_262_, v___y_209_);
if (v___x_263_ == 0)
{
uint64_t v___x_264_; 
v___x_264_ = lean_uint64_add(v_quotient_253_, v___x_254_);
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v___x_264_;
goto v___jp_135_;
}
else
{
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v_quotient_253_;
goto v___jp_135_;
}
}
else
{
uint64_t v___x_265_; 
v___x_265_ = lean_uint64_add(v_quotient_253_, v___x_254_);
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v___x_265_;
goto v___jp_135_;
}
}
else
{
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v_quotient_253_;
goto v___jp_135_;
}
}
}
else
{
v___y_136_ = v___y_207_;
v___y_137_ = v___y_209_;
v___y_138_ = v___y_211_;
v___y_139_ = v___y_208_;
goto v___jp_135_;
}
}
}
}
v___jp_266_:
{
uint64_t v___x_274_; uint64_t v___x_275_; uint8_t v___x_276_; 
v___x_274_ = 1ULL;
v___x_275_ = lean_uint64_shift_right(v___y_268_, v___x_274_);
v___x_276_ = lean_uint64_dec_eq(v___x_275_, v___y_271_);
if (v___x_276_ == 0)
{
uint64_t v___x_277_; 
v___x_277_ = lean_uint64_add(v___y_273_, v___x_274_);
v___y_207_ = v___y_267_;
v___y_208_ = v___y_269_;
v___y_209_ = v___y_271_;
v___y_210_ = v___y_270_;
v___y_211_ = v___y_272_;
v___y_212_ = v___x_277_;
goto v___jp_206_;
}
else
{
v___y_207_ = v___y_267_;
v___y_208_ = v___y_269_;
v___y_209_ = v___y_271_;
v___y_210_ = v___y_270_;
v___y_211_ = v___y_272_;
v___y_212_ = v___y_273_;
goto v___jp_206_;
}
}
v___jp_278_:
{
uint64_t v___x_288_; uint8_t v___x_289_; 
v___x_288_ = lean_uint64_shift_right(v___y_286_, v___y_285_);
v___x_289_ = lean_uint64_dec_eq(v___x_288_, v___y_282_);
if (v___x_289_ == 0)
{
uint64_t v___x_290_; 
v___x_290_ = lean_uint64_add(v___y_280_, v___y_285_);
v___y_267_ = v___y_279_;
v___y_268_ = v___y_287_;
v___y_269_ = v___y_281_;
v___y_270_ = v___y_283_;
v___y_271_ = v___y_282_;
v___y_272_ = v___y_284_;
v___y_273_ = v___x_290_;
goto v___jp_266_;
}
else
{
v___y_267_ = v___y_279_;
v___y_268_ = v___y_287_;
v___y_269_ = v___y_281_;
v___y_270_ = v___y_283_;
v___y_271_ = v___y_282_;
v___y_272_ = v___y_284_;
v___y_273_ = v___y_280_;
goto v___jp_266_;
}
}
v___jp_291_:
{
uint64_t v___x_299_; uint64_t v___x_300_; uint8_t v___x_301_; 
v___x_299_ = 2ULL;
v___x_300_ = lean_uint64_shift_right(v___y_297_, v___x_299_);
v___x_301_ = lean_uint64_dec_eq(v___x_300_, v___y_295_);
if (v___x_301_ == 0)
{
v___y_279_ = v___y_292_;
v___y_280_ = v___y_298_;
v___y_281_ = v___y_293_;
v___y_282_ = v___y_295_;
v___y_283_ = v___y_294_;
v___y_284_ = v___y_296_;
v___y_285_ = v___x_299_;
v___y_286_ = v___y_297_;
v___y_287_ = v___x_300_;
goto v___jp_278_;
}
else
{
v___y_279_ = v___y_292_;
v___y_280_ = v___y_298_;
v___y_281_ = v___y_293_;
v___y_282_ = v___y_295_;
v___y_283_ = v___y_294_;
v___y_284_ = v___y_296_;
v___y_285_ = v___x_299_;
v___y_286_ = v___y_297_;
v___y_287_ = v___y_297_;
goto v___jp_278_;
}
}
v___jp_302_:
{
uint64_t v___x_312_; uint8_t v___x_313_; 
v___x_312_ = lean_uint64_shift_right(v___y_305_, v___y_309_);
v___x_313_ = lean_uint64_dec_eq(v___x_312_, v___y_306_);
if (v___x_313_ == 0)
{
uint64_t v___x_314_; 
v___x_314_ = lean_uint64_add(v___y_310_, v___y_309_);
v___y_292_ = v___y_303_;
v___y_293_ = v___y_304_;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_306_;
v___y_296_ = v___y_308_;
v___y_297_ = v___y_311_;
v___y_298_ = v___x_314_;
goto v___jp_291_;
}
else
{
v___y_292_ = v___y_303_;
v___y_293_ = v___y_304_;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_306_;
v___y_296_ = v___y_308_;
v___y_297_ = v___y_311_;
v___y_298_ = v___y_310_;
goto v___jp_291_;
}
}
v___jp_315_:
{
uint64_t v___x_323_; uint64_t v___x_324_; uint8_t v___x_325_; 
v___x_323_ = 4ULL;
v___x_324_ = lean_uint64_shift_right(v___y_318_, v___x_323_);
v___x_325_ = lean_uint64_dec_eq(v___x_324_, v___y_320_);
if (v___x_325_ == 0)
{
v___y_303_ = v___y_316_;
v___y_304_ = v___y_317_;
v___y_305_ = v___y_318_;
v___y_306_ = v___y_320_;
v___y_307_ = v___y_319_;
v___y_308_ = v___y_321_;
v___y_309_ = v___x_323_;
v___y_310_ = v___y_322_;
v___y_311_ = v___x_324_;
goto v___jp_302_;
}
else
{
v___y_303_ = v___y_316_;
v___y_304_ = v___y_317_;
v___y_305_ = v___y_318_;
v___y_306_ = v___y_320_;
v___y_307_ = v___y_319_;
v___y_308_ = v___y_321_;
v___y_309_ = v___x_323_;
v___y_310_ = v___y_322_;
v___y_311_ = v___y_318_;
goto v___jp_302_;
}
}
v___jp_326_:
{
uint64_t v___x_336_; uint8_t v___x_337_; 
v___x_336_ = lean_uint64_shift_right(v___y_333_, v___y_334_);
v___x_337_ = lean_uint64_dec_eq(v___x_336_, v___y_329_);
if (v___x_337_ == 0)
{
uint64_t v___x_338_; 
v___x_338_ = lean_uint64_add(v___y_331_, v___y_334_);
v___y_316_ = v___y_327_;
v___y_317_ = v___y_328_;
v___y_318_ = v___y_335_;
v___y_319_ = v___y_330_;
v___y_320_ = v___y_329_;
v___y_321_ = v___y_332_;
v___y_322_ = v___x_338_;
goto v___jp_315_;
}
else
{
v___y_316_ = v___y_327_;
v___y_317_ = v___y_328_;
v___y_318_ = v___y_335_;
v___y_319_ = v___y_330_;
v___y_320_ = v___y_329_;
v___y_321_ = v___y_332_;
v___y_322_ = v___y_331_;
goto v___jp_315_;
}
}
v___jp_339_:
{
uint64_t v___x_347_; uint64_t v___x_348_; uint8_t v___x_349_; 
v___x_347_ = 8ULL;
v___x_348_ = lean_uint64_shift_right(v___y_345_, v___x_347_);
v___x_349_ = lean_uint64_dec_eq(v___x_348_, v___y_343_);
if (v___x_349_ == 0)
{
v___y_327_ = v___y_340_;
v___y_328_ = v___y_341_;
v___y_329_ = v___y_343_;
v___y_330_ = v___y_342_;
v___y_331_ = v___y_346_;
v___y_332_ = v___y_344_;
v___y_333_ = v___y_345_;
v___y_334_ = v___x_347_;
v___y_335_ = v___x_348_;
goto v___jp_326_;
}
else
{
v___y_327_ = v___y_340_;
v___y_328_ = v___y_341_;
v___y_329_ = v___y_343_;
v___y_330_ = v___y_342_;
v___y_331_ = v___y_346_;
v___y_332_ = v___y_344_;
v___y_333_ = v___y_345_;
v___y_334_ = v___x_347_;
v___y_335_ = v___y_345_;
goto v___jp_326_;
}
}
v___jp_350_:
{
uint64_t v___x_360_; uint8_t v___x_361_; 
v___x_360_ = lean_uint64_shift_right(v___y_358_, v___y_351_);
v___x_361_ = lean_uint64_dec_eq(v___x_360_, v___y_355_);
if (v___x_361_ == 0)
{
uint64_t v___x_362_; 
v___x_362_ = lean_uint64_add(v___y_353_, v___y_351_);
v___y_340_ = v___y_352_;
v___y_341_ = v___y_354_;
v___y_342_ = v___y_356_;
v___y_343_ = v___y_355_;
v___y_344_ = v___y_357_;
v___y_345_ = v___y_359_;
v___y_346_ = v___x_362_;
goto v___jp_339_;
}
else
{
v___y_340_ = v___y_352_;
v___y_341_ = v___y_354_;
v___y_342_ = v___y_356_;
v___y_343_ = v___y_355_;
v___y_344_ = v___y_357_;
v___y_345_ = v___y_359_;
v___y_346_ = v___y_353_;
goto v___jp_339_;
}
}
v___jp_363_:
{
uint64_t v___x_371_; uint64_t v___x_372_; uint8_t v___x_373_; 
v___x_371_ = 16ULL;
v___x_372_ = lean_uint64_shift_right(v___y_369_, v___x_371_);
v___x_373_ = lean_uint64_dec_eq(v___x_372_, v___y_367_);
if (v___x_373_ == 0)
{
v___y_351_ = v___x_371_;
v___y_352_ = v___y_364_;
v___y_353_ = v___y_370_;
v___y_354_ = v___y_365_;
v___y_355_ = v___y_367_;
v___y_356_ = v___y_366_;
v___y_357_ = v___y_368_;
v___y_358_ = v___y_369_;
v___y_359_ = v___x_372_;
goto v___jp_350_;
}
else
{
v___y_351_ = v___x_371_;
v___y_352_ = v___y_364_;
v___y_353_ = v___y_370_;
v___y_354_ = v___y_365_;
v___y_355_ = v___y_367_;
v___y_356_ = v___y_366_;
v___y_357_ = v___y_368_;
v___y_358_ = v___y_369_;
v___y_359_ = v___y_369_;
goto v___jp_350_;
}
}
v___jp_374_:
{
uint64_t v___x_382_; uint8_t v___x_383_; 
v___x_382_ = lean_uint64_shift_right(v___y_376_, v___y_379_);
v___x_383_ = lean_uint64_dec_eq(v___x_382_, v___y_377_);
if (v___x_383_ == 0)
{
v___y_364_ = v___y_375_;
v___y_365_ = v___y_376_;
v___y_366_ = v___y_378_;
v___y_367_ = v___y_377_;
v___y_368_ = v___y_380_;
v___y_369_ = v___y_381_;
v___y_370_ = v___y_379_;
goto v___jp_363_;
}
else
{
v___y_364_ = v___y_375_;
v___y_365_ = v___y_376_;
v___y_366_ = v___y_378_;
v___y_367_ = v___y_377_;
v___y_368_ = v___y_380_;
v___y_369_ = v___y_381_;
v___y_370_ = v___y_377_;
goto v___jp_363_;
}
}
v___jp_384_:
{
uint64_t v___x_390_; uint64_t v___x_391_; uint8_t v___x_392_; 
v___x_390_ = 32ULL;
v___x_391_ = lean_uint64_shift_right(v___y_386_, v___x_390_);
v___x_392_ = lean_uint64_dec_eq(v___x_391_, v___y_388_);
if (v___x_392_ == 0)
{
v___y_375_ = v___y_385_;
v___y_376_ = v___y_386_;
v___y_377_ = v___y_388_;
v___y_378_ = v___y_387_;
v___y_379_ = v___x_390_;
v___y_380_ = v___y_389_;
v___y_381_ = v___x_391_;
goto v___jp_374_;
}
else
{
v___y_375_ = v___y_385_;
v___y_376_ = v___y_386_;
v___y_377_ = v___y_388_;
v___y_378_ = v___y_387_;
v___y_379_ = v___x_390_;
v___y_380_ = v___y_389_;
v___y_381_ = v___y_386_;
goto v___jp_374_;
}
}
v___jp_393_:
{
uint64_t v___x_400_; uint64_t v___x_401_; uint8_t v___x_402_; 
v___x_400_ = lean_uint64_mul(v___y_396_, v___y_395_);
v___x_401_ = 0ULL;
v___x_402_ = lean_uint64_dec_eq(v___x_400_, v___x_401_);
if (v___x_402_ == 0)
{
uint64_t v___x_403_; uint64_t v___x_404_; uint8_t v___x_405_; 
v___x_403_ = lean_uint64_add(v___y_397_, v___y_399_);
v___x_404_ = 70368744177664ULL;
v___x_405_ = lean_uint64_dec_le(v___x_404_, v___x_400_);
if (v___x_405_ == 0)
{
v___y_385_ = v___y_394_;
v___y_386_ = v___x_400_;
v___y_387_ = v___x_403_;
v___y_388_ = v___x_401_;
v___y_389_ = v___y_398_;
goto v___jp_384_;
}
else
{
uint64_t v___x_406_; uint8_t v___x_407_; 
v___x_406_ = 281474976710656ULL;
v___x_407_ = lean_uint64_dec_lt(v___x_400_, v___x_406_);
if (v___x_407_ == 0)
{
v___y_385_ = v___y_394_;
v___y_386_ = v___x_400_;
v___y_387_ = v___x_403_;
v___y_388_ = v___x_401_;
v___y_389_ = v___y_398_;
goto v___jp_384_;
}
else
{
uint64_t v___x_408_; uint8_t v___x_409_; 
v___x_408_ = 140737488355328ULL;
v___x_409_ = lean_uint64_dec_lt(v___x_400_, v___x_408_);
if (v___x_409_ == 0)
{
uint64_t v___x_410_; 
v___x_410_ = 47ULL;
v___y_207_ = v___y_394_;
v___y_208_ = v___x_400_;
v___y_209_ = v___x_401_;
v___y_210_ = v___x_403_;
v___y_211_ = v___y_398_;
v___y_212_ = v___x_410_;
goto v___jp_206_;
}
else
{
uint64_t v___x_411_; 
v___x_411_ = 46ULL;
v___y_207_ = v___y_394_;
v___y_208_ = v___x_400_;
v___y_209_ = v___x_401_;
v___y_210_ = v___x_403_;
v___y_211_ = v___y_398_;
v___y_212_ = v___x_411_;
goto v___jp_206_;
}
}
}
}
else
{
if (v___y_398_ == 0)
{
uint32_t v___x_412_; 
v___x_412_ = 0;
return v___x_412_;
}
else
{
uint32_t v___x_413_; 
v___x_413_ = 2147483648;
return v___x_413_;
}
}
}
v___jp_414_:
{
uint32_t v___x_419_; uint32_t v___x_420_; uint32_t v___x_421_; uint32_t v___x_422_; uint32_t v___x_423_; 
v___x_419_ = lean_uint32_land(v___y_417_, v___x_152_);
v___x_420_ = lean_uint32_shift_left(v___x_419_, v___x_150_);
v___x_421_ = lean_uint32_lor(v___y_418_, v___x_420_);
v___x_422_ = lean_uint32_land(v___y_415_, v___y_416_);
v___x_423_ = lean_uint32_lor(v___x_421_, v___x_422_);
return v___x_423_;
}
v___jp_424_:
{
if (v___y_425_ == 0)
{
uint32_t v___x_429_; 
v___x_429_ = 0;
v___y_415_ = v___y_428_;
v___y_416_ = v___y_426_;
v___y_417_ = v___y_427_;
v___y_418_ = v___x_429_;
goto v___jp_414_;
}
else
{
uint32_t v___x_430_; 
v___x_430_ = 2147483648;
v___y_415_ = v___y_428_;
v___y_416_ = v___y_426_;
v___y_417_ = v___y_427_;
v___y_418_ = v___x_430_;
goto v___jp_414_;
}
}
v___jp_431_:
{
uint64_t v___x_437_; uint64_t v_encodedExponent_438_; uint32_t v___x_439_; uint64_t v___x_440_; uint8_t v___x_441_; 
v___x_437_ = 171ULL;
v_encodedExponent_438_ = lean_uint64_sub(v___y_432_, v___x_437_);
v___x_439_ = lean_uint64_to_uint32(v_encodedExponent_438_);
v___x_440_ = 8388608ULL;
v___x_441_ = lean_uint64_dec_lt(v___y_436_, v___x_440_);
if (v___x_441_ == 0)
{
uint64_t v___x_442_; uint32_t v___x_443_; 
v___x_442_ = lean_uint64_sub(v___y_436_, v___x_440_);
v___x_443_ = lean_uint64_to_uint32(v___x_442_);
v___y_425_ = v___y_433_;
v___y_426_ = v___y_435_;
v___y_427_ = v___x_439_;
v___y_428_ = v___x_443_;
goto v___jp_424_;
}
else
{
uint32_t v___x_444_; 
v___x_444_ = lean_uint64_to_uint32(v___y_434_);
v___y_425_ = v___y_433_;
v___y_426_ = v___y_435_;
v___y_427_ = v___x_439_;
v___y_428_ = v___x_444_;
goto v___jp_424_;
}
}
v___jp_445_:
{
uint64_t v___x_452_; uint8_t v___x_453_; 
v___x_452_ = 425ULL;
v___x_453_ = lean_uint64_dec_lt(v___x_452_, v___y_451_);
if (v___x_453_ == 0)
{
if (v___y_446_ == 0)
{
v___y_432_ = v___y_451_;
v___y_433_ = v___y_447_;
v___y_434_ = v___y_449_;
v___y_435_ = v___y_450_;
v___y_436_ = v___y_448_;
goto v___jp_431_;
}
else
{
uint64_t v___x_454_; 
v___x_454_ = 8388608ULL;
v___y_432_ = v___y_451_;
v___y_433_ = v___y_447_;
v___y_434_ = v___y_449_;
v___y_435_ = v___y_450_;
v___y_436_ = v___x_454_;
goto v___jp_431_;
}
}
else
{
if (v___y_447_ == 0)
{
uint32_t v___x_455_; 
v___x_455_ = 2139095040;
return v___x_455_;
}
else
{
uint32_t v___x_456_; 
v___x_456_ = 4286578688;
return v___x_456_;
}
}
}
v___jp_457_:
{
uint64_t v___x_463_; uint8_t v_carry_464_; 
v___x_463_ = 16777216ULL;
v_carry_464_ = lean_uint64_dec_eq(v___y_462_, v___x_463_);
if (v_carry_464_ == 0)
{
v___y_446_ = v_carry_464_;
v___y_447_ = v___y_459_;
v___y_448_ = v___y_462_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___y_458_;
goto v___jp_445_;
}
else
{
uint64_t v___x_465_; uint64_t v___x_466_; 
v___x_465_ = 1ULL;
v___x_466_ = lean_uint64_add(v___y_458_, v___x_465_);
v___y_446_ = v_carry_464_;
v___y_447_ = v___y_459_;
v___y_448_ = v___y_462_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___x_466_;
goto v___jp_445_;
}
}
v___jp_467_:
{
uint64_t v_position_474_; uint64_t v___x_475_; uint8_t v___x_476_; 
v_position_474_ = lean_uint64_add(v___y_473_, v___y_472_);
v___x_475_ = 172ULL;
v___x_476_ = lean_uint64_dec_lt(v_position_474_, v___x_475_);
if (v___x_476_ == 0)
{
uint64_t v___x_477_; uint8_t v___x_478_; 
v___x_477_ = 23ULL;
v___x_478_ = lean_uint64_dec_lt(v___y_473_, v___x_477_);
if (v___x_478_ == 0)
{
uint64_t v___x_479_; uint8_t v___x_480_; 
v___x_479_ = lean_uint64_sub(v___y_473_, v___x_477_);
v___x_480_ = lean_uint64_dec_eq(v___x_479_, v___y_470_);
if (v___x_480_ == 0)
{
uint64_t v___x_481_; uint8_t v___x_482_; 
v___x_481_ = 64ULL;
v___x_482_ = lean_uint64_dec_lt(v___x_479_, v___x_481_);
if (v___x_482_ == 0)
{
uint8_t v___x_483_; 
v___x_483_ = lean_uint64_dec_eq(v___x_479_, v___x_481_);
if (v___x_483_ == 0)
{
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v___y_470_;
goto v___jp_457_;
}
else
{
uint64_t v___x_484_; uint8_t v___x_485_; 
v___x_484_ = 9223372036854775808ULL;
v___x_485_ = lean_uint64_dec_lt(v___x_484_, v___y_468_);
if (v___x_485_ == 0)
{
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v___y_470_;
goto v___jp_457_;
}
else
{
uint64_t v___x_486_; 
v___x_486_ = 1ULL;
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v___x_486_;
goto v___jp_457_;
}
}
}
else
{
uint64_t v_quotient_487_; uint64_t v___x_488_; uint64_t v___x_489_; uint64_t v___x_490_; uint64_t v_remainder_491_; uint64_t v___x_492_; uint64_t v_half_493_; uint8_t v___x_494_; 
v_quotient_487_ = lean_uint64_shift_right(v___y_468_, v___x_479_);
v___x_488_ = 1ULL;
v___x_489_ = lean_uint64_shift_left(v___x_488_, v___x_479_);
v___x_490_ = lean_uint64_sub(v___x_489_, v___x_488_);
v_remainder_491_ = lean_uint64_land(v___y_468_, v___x_490_);
v___x_492_ = lean_uint64_sub(v___x_479_, v___x_488_);
v_half_493_ = lean_uint64_shift_left(v___x_488_, v___x_492_);
v___x_494_ = lean_uint64_dec_lt(v_remainder_491_, v_half_493_);
if (v___x_494_ == 0)
{
uint8_t v___x_495_; 
v___x_495_ = lean_uint64_dec_lt(v_half_493_, v_remainder_491_);
if (v___x_495_ == 0)
{
uint64_t v___x_496_; uint8_t v___x_497_; 
v___x_496_ = lean_uint64_land(v_quotient_487_, v___x_488_);
v___x_497_ = lean_uint64_dec_eq(v___x_496_, v___y_470_);
if (v___x_497_ == 0)
{
uint64_t v___x_498_; 
v___x_498_ = lean_uint64_add(v_quotient_487_, v___x_488_);
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v___x_498_;
goto v___jp_457_;
}
else
{
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v_quotient_487_;
goto v___jp_457_;
}
}
else
{
uint64_t v___x_499_; 
v___x_499_ = lean_uint64_add(v_quotient_487_, v___x_488_);
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v___x_499_;
goto v___jp_457_;
}
}
else
{
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v_quotient_487_;
goto v___jp_457_;
}
}
}
else
{
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v___y_468_;
goto v___jp_457_;
}
}
else
{
uint64_t v___x_500_; uint64_t v___x_501_; 
v___x_500_ = lean_uint64_sub(v___x_477_, v___y_473_);
v___x_501_ = lean_uint64_shift_left(v___y_468_, v___x_500_);
v___y_458_ = v_position_474_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_470_;
v___y_461_ = v___y_471_;
v___y_462_ = v___x_501_;
goto v___jp_457_;
}
}
else
{
uint64_t v___x_502_; uint8_t v___x_503_; 
v___x_502_ = 149ULL;
v___x_503_ = lean_uint64_dec_lt(v___y_472_, v___x_502_);
if (v___x_503_ == 0)
{
uint64_t v___x_504_; uint64_t v___x_505_; 
v___x_504_ = lean_uint64_sub(v___y_472_, v___x_502_);
v___x_505_ = lean_uint64_shift_left(v___y_468_, v___x_504_);
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v___x_505_;
goto v___jp_89_;
}
else
{
uint64_t v___x_506_; uint8_t v___x_507_; 
v___x_506_ = lean_uint64_sub(v___x_502_, v___y_472_);
v___x_507_ = lean_uint64_dec_eq(v___x_506_, v___y_470_);
if (v___x_507_ == 0)
{
uint64_t v___x_508_; uint8_t v___x_509_; 
v___x_508_ = 64ULL;
v___x_509_ = lean_uint64_dec_lt(v___x_506_, v___x_508_);
if (v___x_509_ == 0)
{
uint8_t v___x_510_; 
v___x_510_ = lean_uint64_dec_eq(v___x_506_, v___x_508_);
if (v___x_510_ == 0)
{
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v___y_470_;
goto v___jp_89_;
}
else
{
uint64_t v___x_511_; uint8_t v___x_512_; 
v___x_511_ = 9223372036854775808ULL;
v___x_512_ = lean_uint64_dec_lt(v___x_511_, v___y_468_);
if (v___x_512_ == 0)
{
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v___y_470_;
goto v___jp_89_;
}
else
{
uint64_t v___x_513_; 
v___x_513_ = 1ULL;
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v___x_513_;
goto v___jp_89_;
}
}
}
else
{
uint64_t v_quotient_514_; uint64_t v___x_515_; uint64_t v___x_516_; uint64_t v___x_517_; uint64_t v_remainder_518_; uint64_t v___x_519_; uint64_t v_half_520_; uint8_t v___x_521_; 
v_quotient_514_ = lean_uint64_shift_right(v___y_468_, v___x_506_);
v___x_515_ = 1ULL;
v___x_516_ = lean_uint64_shift_left(v___x_515_, v___x_506_);
v___x_517_ = lean_uint64_sub(v___x_516_, v___x_515_);
v_remainder_518_ = lean_uint64_land(v___y_468_, v___x_517_);
v___x_519_ = lean_uint64_sub(v___x_506_, v___x_515_);
v_half_520_ = lean_uint64_shift_left(v___x_515_, v___x_519_);
v___x_521_ = lean_uint64_dec_lt(v_remainder_518_, v_half_520_);
if (v___x_521_ == 0)
{
uint8_t v___x_522_; 
v___x_522_ = lean_uint64_dec_lt(v_half_520_, v_remainder_518_);
if (v___x_522_ == 0)
{
uint64_t v___x_523_; uint8_t v___x_524_; 
v___x_523_ = lean_uint64_land(v_quotient_514_, v___x_515_);
v___x_524_ = lean_uint64_dec_eq(v___x_523_, v___y_470_);
if (v___x_524_ == 0)
{
uint64_t v___x_525_; 
v___x_525_ = lean_uint64_add(v_quotient_514_, v___x_515_);
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v___x_525_;
goto v___jp_89_;
}
else
{
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v_quotient_514_;
goto v___jp_89_;
}
}
else
{
uint64_t v___x_526_; 
v___x_526_ = lean_uint64_add(v_quotient_514_, v___x_515_);
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v___x_526_;
goto v___jp_89_;
}
}
else
{
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v_quotient_514_;
goto v___jp_89_;
}
}
}
else
{
v___y_90_ = v___y_469_;
v___y_91_ = v___y_470_;
v___y_92_ = v___y_471_;
v___y_93_ = v___y_468_;
goto v___jp_89_;
}
}
}
}
v___jp_527_:
{
uint64_t v___x_535_; uint64_t v___x_536_; uint8_t v___x_537_; 
v___x_535_ = 1ULL;
v___x_536_ = lean_uint64_shift_right(v___y_533_, v___x_535_);
v___x_537_ = lean_uint64_dec_eq(v___x_536_, v___y_530_);
if (v___x_537_ == 0)
{
uint64_t v___x_538_; 
v___x_538_ = lean_uint64_add(v___y_534_, v___x_535_);
v___y_468_ = v___y_528_;
v___y_469_ = v___y_529_;
v___y_470_ = v___y_530_;
v___y_471_ = v___y_532_;
v___y_472_ = v___y_531_;
v___y_473_ = v___x_538_;
goto v___jp_467_;
}
else
{
v___y_468_ = v___y_528_;
v___y_469_ = v___y_529_;
v___y_470_ = v___y_530_;
v___y_471_ = v___y_532_;
v___y_472_ = v___y_531_;
v___y_473_ = v___y_534_;
goto v___jp_467_;
}
}
v___jp_539_:
{
uint64_t v___x_549_; uint8_t v___x_550_; 
v___x_549_ = lean_uint64_shift_right(v___y_545_, v___y_540_);
v___x_550_ = lean_uint64_dec_eq(v___x_549_, v___y_543_);
if (v___x_550_ == 0)
{
uint64_t v___x_551_; 
v___x_551_ = lean_uint64_add(v___y_544_, v___y_540_);
v___y_528_ = v___y_541_;
v___y_529_ = v___y_542_;
v___y_530_ = v___y_543_;
v___y_531_ = v___y_547_;
v___y_532_ = v___y_546_;
v___y_533_ = v___y_548_;
v___y_534_ = v___x_551_;
goto v___jp_527_;
}
else
{
v___y_528_ = v___y_541_;
v___y_529_ = v___y_542_;
v___y_530_ = v___y_543_;
v___y_531_ = v___y_547_;
v___y_532_ = v___y_546_;
v___y_533_ = v___y_548_;
v___y_534_ = v___y_544_;
goto v___jp_527_;
}
}
v___jp_552_:
{
uint64_t v___x_560_; uint64_t v___x_561_; uint8_t v___x_562_; 
v___x_560_ = 2ULL;
v___x_561_ = lean_uint64_shift_right(v___y_556_, v___x_560_);
v___x_562_ = lean_uint64_dec_eq(v___x_561_, v___y_555_);
if (v___x_562_ == 0)
{
v___y_540_ = v___x_560_;
v___y_541_ = v___y_553_;
v___y_542_ = v___y_554_;
v___y_543_ = v___y_555_;
v___y_544_ = v___y_559_;
v___y_545_ = v___y_556_;
v___y_546_ = v___y_558_;
v___y_547_ = v___y_557_;
v___y_548_ = v___x_561_;
goto v___jp_539_;
}
else
{
v___y_540_ = v___x_560_;
v___y_541_ = v___y_553_;
v___y_542_ = v___y_554_;
v___y_543_ = v___y_555_;
v___y_544_ = v___y_559_;
v___y_545_ = v___y_556_;
v___y_546_ = v___y_558_;
v___y_547_ = v___y_557_;
v___y_548_ = v___y_556_;
goto v___jp_539_;
}
}
v___jp_563_:
{
uint64_t v___x_573_; uint8_t v___x_574_; 
v___x_573_ = lean_uint64_shift_right(v___y_567_, v___y_569_);
v___x_574_ = lean_uint64_dec_eq(v___x_573_, v___y_568_);
if (v___x_574_ == 0)
{
uint64_t v___x_575_; 
v___x_575_ = lean_uint64_add(v___y_564_, v___y_569_);
v___y_553_ = v___y_565_;
v___y_554_ = v___y_566_;
v___y_555_ = v___y_568_;
v___y_556_ = v___y_572_;
v___y_557_ = v___y_571_;
v___y_558_ = v___y_570_;
v___y_559_ = v___x_575_;
goto v___jp_552_;
}
else
{
v___y_553_ = v___y_565_;
v___y_554_ = v___y_566_;
v___y_555_ = v___y_568_;
v___y_556_ = v___y_572_;
v___y_557_ = v___y_571_;
v___y_558_ = v___y_570_;
v___y_559_ = v___y_564_;
goto v___jp_552_;
}
}
v___jp_576_:
{
uint64_t v___x_584_; uint64_t v___x_585_; uint8_t v___x_586_; 
v___x_584_ = 4ULL;
v___x_585_ = lean_uint64_shift_right(v___y_580_, v___x_584_);
v___x_586_ = lean_uint64_dec_eq(v___x_585_, v___y_579_);
if (v___x_586_ == 0)
{
v___y_564_ = v___y_583_;
v___y_565_ = v___y_577_;
v___y_566_ = v___y_578_;
v___y_567_ = v___y_580_;
v___y_568_ = v___y_579_;
v___y_569_ = v___x_584_;
v___y_570_ = v___y_582_;
v___y_571_ = v___y_581_;
v___y_572_ = v___x_585_;
goto v___jp_563_;
}
else
{
v___y_564_ = v___y_583_;
v___y_565_ = v___y_577_;
v___y_566_ = v___y_578_;
v___y_567_ = v___y_580_;
v___y_568_ = v___y_579_;
v___y_569_ = v___x_584_;
v___y_570_ = v___y_582_;
v___y_571_ = v___y_581_;
v___y_572_ = v___y_580_;
goto v___jp_563_;
}
}
v___jp_587_:
{
uint64_t v___x_597_; uint8_t v___x_598_; 
v___x_597_ = lean_uint64_shift_right(v___y_592_, v___y_590_);
v___x_598_ = lean_uint64_dec_eq(v___x_597_, v___y_591_);
if (v___x_598_ == 0)
{
uint64_t v___x_599_; 
v___x_599_ = lean_uint64_add(v___y_595_, v___y_590_);
v___y_577_ = v___y_588_;
v___y_578_ = v___y_589_;
v___y_579_ = v___y_591_;
v___y_580_ = v___y_596_;
v___y_581_ = v___y_594_;
v___y_582_ = v___y_593_;
v___y_583_ = v___x_599_;
goto v___jp_576_;
}
else
{
v___y_577_ = v___y_588_;
v___y_578_ = v___y_589_;
v___y_579_ = v___y_591_;
v___y_580_ = v___y_596_;
v___y_581_ = v___y_594_;
v___y_582_ = v___y_593_;
v___y_583_ = v___y_595_;
goto v___jp_576_;
}
}
v___jp_600_:
{
uint64_t v___x_608_; uint64_t v___x_609_; uint8_t v___x_610_; 
v___x_608_ = 8ULL;
v___x_609_ = lean_uint64_shift_right(v___y_604_, v___x_608_);
v___x_610_ = lean_uint64_dec_eq(v___x_609_, v___y_603_);
if (v___x_610_ == 0)
{
v___y_588_ = v___y_601_;
v___y_589_ = v___y_602_;
v___y_590_ = v___x_608_;
v___y_591_ = v___y_603_;
v___y_592_ = v___y_604_;
v___y_593_ = v___y_606_;
v___y_594_ = v___y_605_;
v___y_595_ = v___y_607_;
v___y_596_ = v___x_609_;
goto v___jp_587_;
}
else
{
v___y_588_ = v___y_601_;
v___y_589_ = v___y_602_;
v___y_590_ = v___x_608_;
v___y_591_ = v___y_603_;
v___y_592_ = v___y_604_;
v___y_593_ = v___y_606_;
v___y_594_ = v___y_605_;
v___y_595_ = v___y_607_;
v___y_596_ = v___y_604_;
goto v___jp_587_;
}
}
v___jp_611_:
{
uint64_t v___x_621_; uint8_t v___x_622_; 
v___x_621_ = lean_uint64_shift_right(v___y_619_, v___y_612_);
v___x_622_ = lean_uint64_dec_eq(v___x_621_, v___y_616_);
if (v___x_622_ == 0)
{
uint64_t v___x_623_; 
v___x_623_ = lean_uint64_add(v___y_613_, v___y_612_);
v___y_601_ = v___y_614_;
v___y_602_ = v___y_615_;
v___y_603_ = v___y_616_;
v___y_604_ = v___y_620_;
v___y_605_ = v___y_618_;
v___y_606_ = v___y_617_;
v___y_607_ = v___x_623_;
goto v___jp_600_;
}
else
{
v___y_601_ = v___y_614_;
v___y_602_ = v___y_615_;
v___y_603_ = v___y_616_;
v___y_604_ = v___y_620_;
v___y_605_ = v___y_618_;
v___y_606_ = v___y_617_;
v___y_607_ = v___y_613_;
goto v___jp_600_;
}
}
v___jp_624_:
{
uint64_t v___x_632_; uint64_t v___x_633_; uint8_t v___x_634_; 
v___x_632_ = 16ULL;
v___x_633_ = lean_uint64_shift_right(v___y_630_, v___x_632_);
v___x_634_ = lean_uint64_dec_eq(v___x_633_, v___y_627_);
if (v___x_634_ == 0)
{
v___y_612_ = v___x_632_;
v___y_613_ = v___y_631_;
v___y_614_ = v___y_625_;
v___y_615_ = v___y_626_;
v___y_616_ = v___y_627_;
v___y_617_ = v___y_629_;
v___y_618_ = v___y_628_;
v___y_619_ = v___y_630_;
v___y_620_ = v___x_633_;
goto v___jp_611_;
}
else
{
v___y_612_ = v___x_632_;
v___y_613_ = v___y_631_;
v___y_614_ = v___y_625_;
v___y_615_ = v___y_626_;
v___y_616_ = v___y_627_;
v___y_617_ = v___y_629_;
v___y_618_ = v___y_628_;
v___y_619_ = v___y_630_;
v___y_620_ = v___y_630_;
goto v___jp_611_;
}
}
v___jp_635_:
{
uint64_t v___x_643_; uint8_t v___x_644_; 
v___x_643_ = lean_uint64_shift_right(v___y_636_, v___y_641_);
v___x_644_ = lean_uint64_dec_eq(v___x_643_, v___y_638_);
if (v___x_644_ == 0)
{
v___y_625_ = v___y_636_;
v___y_626_ = v___y_637_;
v___y_627_ = v___y_638_;
v___y_628_ = v___y_640_;
v___y_629_ = v___y_639_;
v___y_630_ = v___y_642_;
v___y_631_ = v___y_641_;
goto v___jp_624_;
}
else
{
v___y_625_ = v___y_636_;
v___y_626_ = v___y_637_;
v___y_627_ = v___y_638_;
v___y_628_ = v___y_640_;
v___y_629_ = v___y_639_;
v___y_630_ = v___y_642_;
v___y_631_ = v___y_638_;
goto v___jp_624_;
}
}
v___jp_645_:
{
uint64_t v___x_650_; uint8_t v___x_651_; 
v___x_650_ = 0ULL;
v___x_651_ = lean_uint64_dec_eq(v___y_646_, v___x_650_);
if (v___x_651_ == 0)
{
uint64_t v___x_652_; uint64_t v___x_653_; uint8_t v___x_654_; 
v___x_652_ = 32ULL;
v___x_653_ = lean_uint64_shift_right(v___y_646_, v___x_652_);
v___x_654_ = lean_uint64_dec_eq(v___x_653_, v___x_650_);
if (v___x_654_ == 0)
{
v___y_636_ = v___y_646_;
v___y_637_ = v___y_647_;
v___y_638_ = v___x_650_;
v___y_639_ = v___y_649_;
v___y_640_ = v___y_648_;
v___y_641_ = v___x_652_;
v___y_642_ = v___x_653_;
goto v___jp_635_;
}
else
{
v___y_636_ = v___y_646_;
v___y_637_ = v___y_647_;
v___y_638_ = v___x_650_;
v___y_639_ = v___y_649_;
v___y_640_ = v___y_648_;
v___y_641_ = v___x_652_;
v___y_642_ = v___y_646_;
goto v___jp_635_;
}
}
else
{
if (v___y_647_ == 0)
{
uint32_t v___x_655_; 
v___x_655_ = 0;
return v___x_655_;
}
else
{
uint32_t v___x_656_; 
v___x_656_ = 2147483648;
return v___x_656_;
}
}
}
v___jp_657_:
{
uint64_t v___x_664_; uint64_t v___x_665_; uint64_t v___x_666_; uint8_t v___x_667_; 
v___x_664_ = lean_uint64_mul(v___y_660_, v___y_658_);
v___x_665_ = lean_uint64_add(v___y_661_, v___y_663_);
v___x_666_ = 281474976710656ULL;
v___x_667_ = lean_uint64_dec_lt(v___x_664_, v___x_666_);
if (v___x_667_ == 0)
{
v___y_646_ = v___x_664_;
v___y_647_ = v___y_659_;
v___y_648_ = v___x_665_;
v___y_649_ = v___y_662_;
goto v___jp_645_;
}
else
{
uint64_t v___x_668_; uint8_t v___x_669_; 
v___x_668_ = 123ULL;
v___x_669_ = lean_uint64_dec_le(v___x_665_, v___x_668_);
if (v___x_669_ == 0)
{
v___y_646_ = v___x_664_;
v___y_647_ = v___y_659_;
v___y_648_ = v___x_665_;
v___y_649_ = v___y_662_;
goto v___jp_645_;
}
else
{
uint64_t v___x_670_; uint8_t v___x_671_; 
v___x_670_ = 0ULL;
v___x_671_ = lean_uint64_dec_eq(v___x_664_, v___x_670_);
if (v___x_671_ == 0)
{
uint64_t v___x_672_; uint64_t v___x_673_; uint8_t v___x_674_; 
v___x_672_ = 149ULL;
v___x_673_ = lean_uint64_sub(v___x_672_, v___x_665_);
v___x_674_ = lean_uint64_dec_eq(v___x_673_, v___x_670_);
if (v___x_674_ == 0)
{
uint64_t v___x_675_; uint8_t v___x_676_; 
v___x_675_ = 64ULL;
v___x_676_ = lean_uint64_dec_lt(v___x_673_, v___x_675_);
if (v___x_676_ == 0)
{
uint8_t v___x_677_; 
v___x_677_ = lean_uint64_dec_eq(v___x_673_, v___x_675_);
if (v___x_677_ == 0)
{
v___y_111_ = v___y_659_;
v___y_112_ = v___x_670_;
v___y_113_ = v___y_662_;
v___y_114_ = v___x_670_;
goto v___jp_110_;
}
else
{
uint64_t v___x_678_; uint8_t v___x_679_; 
v___x_678_ = 9223372036854775808ULL;
v___x_679_ = lean_uint64_dec_lt(v___x_678_, v___x_664_);
if (v___x_679_ == 0)
{
v___y_111_ = v___y_659_;
v___y_112_ = v___x_670_;
v___y_113_ = v___y_662_;
v___y_114_ = v___x_670_;
goto v___jp_110_;
}
else
{
uint64_t v___x_680_; 
v___x_680_ = 1ULL;
v___y_111_ = v___y_659_;
v___y_112_ = v___x_670_;
v___y_113_ = v___y_662_;
v___y_114_ = v___x_680_;
goto v___jp_110_;
}
}
}
else
{
uint64_t v_quotient_681_; uint64_t v___x_682_; uint64_t v___x_683_; uint64_t v___x_684_; uint64_t v_remainder_685_; uint64_t v___x_686_; uint64_t v_half_687_; uint8_t v___x_688_; 
v_quotient_681_ = lean_uint64_shift_right(v___x_664_, v___x_673_);
v___x_682_ = 1ULL;
v___x_683_ = lean_uint64_shift_left(v___x_682_, v___x_673_);
v___x_684_ = lean_uint64_sub(v___x_683_, v___x_682_);
v_remainder_685_ = lean_uint64_land(v___x_664_, v___x_684_);
v___x_686_ = lean_uint64_sub(v___x_673_, v___x_682_);
v_half_687_ = lean_uint64_shift_left(v___x_682_, v___x_686_);
v___x_688_ = lean_uint64_dec_lt(v_remainder_685_, v_half_687_);
if (v___x_688_ == 0)
{
uint8_t v___x_689_; 
v___x_689_ = lean_uint64_dec_lt(v_half_687_, v_remainder_685_);
if (v___x_689_ == 0)
{
uint64_t v___x_690_; uint8_t v___x_691_; 
v___x_690_ = lean_uint64_land(v_quotient_681_, v___x_682_);
v___x_691_ = lean_uint64_dec_eq(v___x_690_, v___x_670_);
if (v___x_691_ == 0)
{
uint64_t v___x_692_; 
v___x_692_ = lean_uint64_add(v_quotient_681_, v___x_682_);
v___y_111_ = v___y_659_;
v___y_112_ = v___x_670_;
v___y_113_ = v___y_662_;
v___y_114_ = v___x_692_;
goto v___jp_110_;
}
else
{
v___y_111_ = v___y_659_;
v___y_112_ = v___x_670_;
v___y_113_ = v___y_662_;
v___y_114_ = v_quotient_681_;
goto v___jp_110_;
}
}
else
{
uint64_t v___x_693_; 
v___x_693_ = lean_uint64_add(v_quotient_681_, v___x_682_);
v___y_111_ = v___y_659_;
v___y_112_ = v___x_670_;
v___y_113_ = v___y_662_;
v___y_114_ = v___x_693_;
goto v___jp_110_;
}
}
else
{
v___y_111_ = v___y_659_;
v___y_112_ = v___x_670_;
v___y_113_ = v___y_662_;
v___y_114_ = v_quotient_681_;
goto v___jp_110_;
}
}
}
else
{
v___y_111_ = v___y_659_;
v___y_112_ = v___x_670_;
v___y_113_ = v___y_662_;
v___y_114_ = v___x_664_;
goto v___jp_110_;
}
}
else
{
if (v___y_659_ == 0)
{
uint32_t v___x_694_; 
v___x_694_ = 0;
return v___x_694_;
}
else
{
uint32_t v___x_695_; 
v___x_695_ = 2147483648;
return v___x_695_;
}
}
}
}
}
v___jp_699_:
{
uint64_t v___x_705_; uint64_t v___x_706_; uint8_t v___x_707_; 
v___x_705_ = lean_uint32_to_uint64(v_ey_698_);
v___x_706_ = 0ULL;
v___x_707_ = lean_uint64_dec_eq(v___x_705_, v___x_706_);
if (v___x_707_ == 0)
{
uint64_t v___x_708_; uint64_t v___x_709_; 
v___x_708_ = 1ULL;
v___x_709_ = lean_uint64_sub(v___x_705_, v___x_708_);
v___y_394_ = v___y_702_;
v___y_395_ = v___y_701_;
v___y_396_ = v___y_700_;
v___y_397_ = v___y_704_;
v___y_398_ = v___y_703_;
v___y_399_ = v___x_709_;
goto v___jp_393_;
}
else
{
v___y_394_ = v___y_702_;
v___y_395_ = v___y_701_;
v___y_396_ = v___y_700_;
v___y_397_ = v___y_704_;
v___y_398_ = v___y_703_;
v___y_399_ = v___x_706_;
goto v___jp_393_;
}
}
v___jp_710_:
{
uint64_t v___x_715_; uint64_t v___x_716_; uint8_t v___x_717_; 
v___x_715_ = lean_uint32_to_uint64(v_ex_696_);
v___x_716_ = 0ULL;
v___x_717_ = lean_uint64_dec_eq(v___x_715_, v___x_716_);
if (v___x_717_ == 0)
{
uint64_t v___x_718_; uint64_t v___x_719_; 
v___x_718_ = 1ULL;
v___x_719_ = lean_uint64_sub(v___x_715_, v___x_718_);
v___y_700_ = v___y_712_;
v___y_701_ = v___y_714_;
v___y_702_ = v___y_711_;
v___y_703_ = v___y_713_;
v___y_704_ = v___x_719_;
goto v___jp_699_;
}
else
{
v___y_700_ = v___y_712_;
v___y_701_ = v___y_714_;
v___y_702_ = v___y_711_;
v___y_703_ = v___y_713_;
v___y_704_ = v___x_716_;
goto v___jp_699_;
}
}
v___jp_720_:
{
uint32_t v___x_725_; uint8_t v___x_726_; 
v___x_725_ = 0;
v___x_726_ = lean_uint32_dec_eq(v_ey_698_, v___x_725_);
if (v___x_726_ == 0)
{
uint64_t v___x_727_; uint64_t v___x_728_; uint64_t v___x_729_; 
v___x_727_ = lean_uint32_to_uint64(v___y_721_);
v___x_728_ = 8388608ULL;
v___x_729_ = lean_uint64_lor(v___x_727_, v___x_728_);
v___y_711_ = v___y_722_;
v___y_712_ = v___y_724_;
v___y_713_ = v___y_723_;
v___y_714_ = v___x_729_;
goto v___jp_710_;
}
else
{
uint64_t v___x_730_; 
v___x_730_ = lean_uint32_to_uint64(v___y_721_);
v___y_711_ = v___y_722_;
v___y_712_ = v___y_724_;
v___y_713_ = v___y_723_;
v___y_714_ = v___x_730_;
goto v___jp_710_;
}
}
v___jp_731_:
{
uint32_t v___x_733_; uint32_t v_xFraction_734_; uint32_t v_yFraction_735_; uint32_t v___x_736_; uint8_t v___x_737_; 
v___x_733_ = 8388607;
v_xFraction_734_ = lean_uint32_land(v___y_73_, v___x_733_);
v_yFraction_735_ = lean_uint32_land(v___y_74_, v___x_733_);
v___x_736_ = 0;
v___x_737_ = lean_uint32_dec_eq(v_ex_696_, v___x_736_);
if (v___x_737_ == 0)
{
uint64_t v___x_738_; uint64_t v___x_739_; uint64_t v___x_740_; 
v___x_738_ = lean_uint32_to_uint64(v_xFraction_734_);
v___x_739_ = 8388608ULL;
v___x_740_ = lean_uint64_lor(v___x_738_, v___x_739_);
v___y_721_ = v_yFraction_735_;
v___y_722_ = v___x_733_;
v___y_723_ = v___y_732_;
v___y_724_ = v___x_740_;
goto v___jp_720_;
}
else
{
uint64_t v___x_741_; 
v___x_741_ = lean_uint32_to_uint64(v_xFraction_734_);
v___y_721_ = v_yFraction_735_;
v___y_722_ = v___x_733_;
v___y_723_ = v___y_732_;
v___y_724_ = v___x_741_;
goto v___jp_720_;
}
}
v___jp_742_:
{
uint8_t v___x_743_; 
v___x_743_ = 1;
v___y_732_ = v___x_743_;
goto v___jp_731_;
}
v___jp_744_:
{
if (v___y_746_ == 0)
{
if (v___y_747_ == 0)
{
v___y_732_ = v___y_745_;
goto v___jp_731_;
}
else
{
goto v___jp_742_;
}
}
else
{
if (v___y_747_ == 0)
{
goto v___jp_742_;
}
else
{
v___y_732_ = v___y_745_;
goto v___jp_731_;
}
}
}
v___jp_748_:
{
uint32_t v___x_751_; uint32_t v___x_752_; uint32_t v___x_753_; uint8_t v___x_754_; 
v___x_751_ = 2147483648;
v___x_752_ = lean_uint32_land(v___y_74_, v___x_751_);
v___x_753_ = 0;
v___x_754_ = lean_uint32_dec_eq(v___x_752_, v___x_753_);
if (v___x_754_ == 0)
{
uint8_t v___x_755_; 
v___x_755_ = 1;
v___y_745_ = v___y_749_;
v___y_746_ = v___y_750_;
v___y_747_ = v___x_755_;
goto v___jp_744_;
}
else
{
v___y_745_ = v___y_749_;
v___y_746_ = v___y_750_;
v___y_747_ = v___y_749_;
goto v___jp_744_;
}
}
v___jp_756_:
{
if (v___y_757_ == 0)
{
uint32_t v___x_758_; uint32_t v___x_759_; uint32_t v___x_760_; uint8_t v___x_761_; 
v___x_758_ = 2147483648;
v___x_759_ = lean_uint32_land(v___y_73_, v___x_758_);
v___x_760_ = 0;
v___x_761_ = lean_uint32_dec_eq(v___x_759_, v___x_760_);
if (v___x_761_ == 0)
{
uint8_t v___x_762_; 
v___x_762_ = 1;
v___y_749_ = v___y_757_;
v___y_750_ = v___x_762_;
goto v___jp_748_;
}
else
{
v___y_749_ = v___y_757_;
v___y_750_ = v___y_757_;
goto v___jp_748_;
}
}
else
{
lean_object* v___x_763_; lean_object* v___x_764_; lean_object* v___x_765_; uint32_t v___x_766_; 
v___x_763_ = lean_uint32_to_nat(v___y_73_);
v___x_764_ = lean_uint32_to_nat(v___y_74_);
v___x_765_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_763_, v___x_764_);
v___x_766_ = lean_uint32_of_nat(v___x_765_);
lean_dec(v___x_765_);
return v___x_766_;
}
}
v___jp_767_:
{
uint64_t v___x_773_; uint64_t v___x_774_; uint8_t v___x_775_; 
v___x_773_ = lean_uint32_to_uint64(v_ey_698_);
v___x_774_ = 0ULL;
v___x_775_ = lean_uint64_dec_eq(v___x_773_, v___x_774_);
if (v___x_775_ == 0)
{
uint64_t v___x_776_; uint64_t v___x_777_; 
v___x_776_ = 1ULL;
v___x_777_ = lean_uint64_sub(v___x_773_, v___x_776_);
v___y_658_ = v___y_768_;
v___y_659_ = v___y_769_;
v___y_660_ = v___y_770_;
v___y_661_ = v___y_772_;
v___y_662_ = v___y_771_;
v___y_663_ = v___x_777_;
goto v___jp_657_;
}
else
{
v___y_658_ = v___y_768_;
v___y_659_ = v___y_769_;
v___y_660_ = v___y_770_;
v___y_661_ = v___y_772_;
v___y_662_ = v___y_771_;
v___y_663_ = v___x_774_;
goto v___jp_657_;
}
}
v___jp_778_:
{
uint64_t v___x_783_; uint64_t v___x_784_; uint8_t v___x_785_; 
v___x_783_ = lean_uint32_to_uint64(v_ex_696_);
v___x_784_ = 0ULL;
v___x_785_ = lean_uint64_dec_eq(v___x_783_, v___x_784_);
if (v___x_785_ == 0)
{
uint64_t v___x_786_; uint64_t v___x_787_; 
v___x_786_ = 1ULL;
v___x_787_ = lean_uint64_sub(v___x_783_, v___x_786_);
v___y_768_ = v___y_782_;
v___y_769_ = v___y_779_;
v___y_770_ = v___y_780_;
v___y_771_ = v___y_781_;
v___y_772_ = v___x_787_;
goto v___jp_767_;
}
else
{
v___y_768_ = v___y_782_;
v___y_769_ = v___y_779_;
v___y_770_ = v___y_780_;
v___y_771_ = v___y_781_;
v___y_772_ = v___x_784_;
goto v___jp_767_;
}
}
v___jp_788_:
{
uint32_t v___x_793_; uint8_t v___x_794_; 
v___x_793_ = 0;
v___x_794_ = lean_uint32_dec_eq(v_ey_698_, v___x_793_);
if (v___x_794_ == 0)
{
uint64_t v___x_795_; uint64_t v___x_796_; uint64_t v___x_797_; 
v___x_795_ = lean_uint32_to_uint64(v___y_789_);
v___x_796_ = 8388608ULL;
v___x_797_ = lean_uint64_lor(v___x_795_, v___x_796_);
v___y_779_ = v___y_790_;
v___y_780_ = v___y_792_;
v___y_781_ = v___y_791_;
v___y_782_ = v___x_797_;
goto v___jp_778_;
}
else
{
uint64_t v___x_798_; 
v___x_798_ = lean_uint32_to_uint64(v___y_789_);
v___y_779_ = v___y_790_;
v___y_780_ = v___y_792_;
v___y_781_ = v___y_791_;
v___y_782_ = v___x_798_;
goto v___jp_778_;
}
}
v___jp_799_:
{
uint32_t v___x_801_; uint32_t v_xFraction_802_; uint32_t v_yFraction_803_; uint32_t v___x_804_; uint8_t v___x_805_; 
v___x_801_ = 8388607;
v_xFraction_802_ = lean_uint32_land(v___y_73_, v___x_801_);
v_yFraction_803_ = lean_uint32_land(v___y_74_, v___x_801_);
v___x_804_ = 0;
v___x_805_ = lean_uint32_dec_eq(v_ex_696_, v___x_804_);
if (v___x_805_ == 0)
{
uint64_t v___x_806_; uint64_t v___x_807_; uint64_t v___x_808_; 
v___x_806_ = lean_uint32_to_uint64(v_xFraction_802_);
v___x_807_ = 8388608ULL;
v___x_808_ = lean_uint64_lor(v___x_806_, v___x_807_);
v___y_789_ = v_yFraction_803_;
v___y_790_ = v___y_800_;
v___y_791_ = v___x_801_;
v___y_792_ = v___x_808_;
goto v___jp_788_;
}
else
{
uint64_t v___x_809_; 
v___x_809_ = lean_uint32_to_uint64(v_xFraction_802_);
v___y_789_ = v_yFraction_803_;
v___y_790_ = v___y_800_;
v___y_791_ = v___x_801_;
v___y_792_ = v___x_809_;
goto v___jp_788_;
}
}
v___jp_813_:
{
if (v___y_815_ == 0)
{
v___y_800_ = v___x_812_;
goto v___jp_799_;
}
else
{
v___y_800_ = v___y_814_;
goto v___jp_799_;
}
}
v___jp_816_:
{
if (v___y_818_ == 0)
{
if (v___y_819_ == 0)
{
v___y_814_ = v___y_817_;
v___y_815_ = v___x_812_;
goto v___jp_813_;
}
else
{
v___y_800_ = v___x_812_;
goto v___jp_799_;
}
}
else
{
v___y_814_ = v___y_817_;
v___y_815_ = v___y_819_;
goto v___jp_813_;
}
}
v___jp_820_:
{
uint32_t v___x_823_; uint32_t v___x_824_; uint32_t v___x_825_; uint8_t v___x_826_; 
v___x_823_ = 2147483648;
v___x_824_ = lean_uint32_land(v___y_74_, v___x_823_);
v___x_825_ = 0;
v___x_826_ = lean_uint32_dec_eq(v___x_824_, v___x_825_);
if (v___x_826_ == 0)
{
v___y_817_ = v___y_821_;
v___y_818_ = v___y_822_;
v___y_819_ = v___x_812_;
goto v___jp_816_;
}
else
{
v___y_817_ = v___y_821_;
v___y_818_ = v___y_822_;
v___y_819_ = v___y_821_;
goto v___jp_816_;
}
}
v___jp_827_:
{
if (v___y_828_ == 0)
{
uint32_t v___x_829_; uint32_t v___x_830_; uint32_t v___x_831_; uint8_t v___x_832_; 
v___x_829_ = 2147483648;
v___x_830_ = lean_uint32_land(v___y_73_, v___x_829_);
v___x_831_ = 0;
v___x_832_ = lean_uint32_dec_eq(v___x_830_, v___x_831_);
if (v___x_832_ == 0)
{
v___y_821_ = v___y_828_;
v___y_822_ = v___x_812_;
goto v___jp_820_;
}
else
{
v___y_821_ = v___y_828_;
v___y_822_ = v___y_828_;
goto v___jp_820_;
}
}
else
{
lean_object* v___x_833_; lean_object* v___x_834_; lean_object* v___x_835_; uint32_t v___x_836_; 
v___x_833_ = lean_uint32_to_nat(v___y_73_);
v___x_834_ = lean_uint32_to_nat(v___y_74_);
v___x_835_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_833_, v___x_834_);
v___x_836_ = lean_uint32_of_nat(v___x_835_);
lean_dec(v___x_835_);
return v___x_836_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_849_, lean_object* v___y_850_){
_start:
{
uint32_t v___y_2826__boxed_851_; uint32_t v___y_2827__boxed_852_; uint32_t v_res_853_; lean_object* v_r_854_; 
v___y_2826__boxed_851_ = lean_unbox_uint32(v___y_849_);
lean_dec(v___y_849_);
v___y_2827__boxed_852_ = lean_unbox_uint32(v___y_850_);
lean_dec(v___y_850_);
v_res_853_ = lp_competition_main___lam__1(v___y_2826__boxed_851_, v___y_2827__boxed_852_);
v_r_854_ = lean_box_uint32(v_res_853_);
return v_r_854_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___f_860_; lean_object* v___f_861_; lean_object* v___x_862_; lean_object* v___x_863_; lean_object* v___x_864_; 
v___f_860_ = ((lean_object*)(lp_competition_main___closed__0));
v___f_861_ = ((lean_object*)(lp_competition_main___closed__1));
v___x_862_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_863_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_864_ = lp_competition_Bench_runFull(v___f_860_, v___f_861_, v___x_862_, v___x_863_);
return v___x_864_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_865_){
_start:
{
lean_object* v_res_866_; 
v_res_866_ = _lean_main();
return v_res_866_;
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
