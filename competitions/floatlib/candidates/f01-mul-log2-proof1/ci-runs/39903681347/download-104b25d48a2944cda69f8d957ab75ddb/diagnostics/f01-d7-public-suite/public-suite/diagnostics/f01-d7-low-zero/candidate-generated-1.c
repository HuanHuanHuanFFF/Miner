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
lean_object* lean_io_getenv(lean_object*);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
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
uint32_t v___y_3403__boxed_69_; uint32_t v___y_3404__boxed_70_; uint32_t v_res_71_; lean_object* v_r_72_; 
v___y_3403__boxed_69_ = lean_unbox_uint32(v___y_67_);
lean_dec(v___y_67_);
v___y_3404__boxed_70_ = lean_unbox_uint32(v___y_68_);
lean_dec(v___y_68_);
v_res_71_ = lp_competition_main___lam__0(v___y_3403__boxed_69_, v___y_3404__boxed_70_);
v_r_72_ = lean_box_uint32(v_res_71_);
return v_r_72_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_73_, uint32_t v___y_74_){
_start:
{
uint8_t v___y_81_; uint8_t v___y_82_; uint32_t v___y_88_; uint32_t v___y_92_; uint32_t v___y_96_; uint32_t v___y_97_; uint32_t v___y_98_; uint32_t v___y_102_; uint32_t v___y_103_; uint32_t v___y_104_; uint32_t v___x_107_; uint32_t v___x_108_; uint32_t v___x_109_; uint32_t v___y_111_; uint32_t v___y_112_; uint32_t v___y_113_; uint32_t v___y_114_; uint32_t v_ex_120_; uint32_t v___x_121_; uint32_t v_ey_122_; uint32_t v___x_123_; uint32_t v___x_124_; uint8_t v___x_125_; uint8_t v___y_127_; 
v___x_107_ = 23;
v___x_108_ = lean_uint32_shift_right(v___y_73_, v___x_107_);
v___x_109_ = 255;
v_ex_120_ = lean_uint32_land(v___x_108_, v___x_109_);
v___x_121_ = lean_uint32_shift_right(v___y_74_, v___x_107_);
v_ey_122_ = lean_uint32_land(v___x_121_, v___x_109_);
v___x_123_ = lean_uint32_add(v_ex_120_, v_ey_122_);
v___x_124_ = 128;
v___x_125_ = lean_uint32_dec_lt(v___x_123_, v___x_124_);
if (v___x_125_ == 0)
{
uint8_t v___x_142_; 
v___x_142_ = lean_uint32_dec_eq(v_ex_120_, v___x_109_);
if (v___x_142_ == 0)
{
goto v___jp_139_;
}
else
{
if (v___x_125_ == 0)
{
uint32_t v___x_143_; 
v___x_143_ = lp_competition_Submission_FastMul_mul(v___y_73_, v___y_74_);
return v___x_143_;
}
else
{
goto v___jp_139_;
}
}
}
else
{
uint32_t v___x_144_; uint32_t v___x_145_; uint32_t v___x_146_; uint64_t v___y_148_; uint8_t v___y_149_; uint32_t v___y_150_; uint64_t v___y_151_; uint8_t v___y_160_; uint32_t v___y_161_; uint32_t v___y_162_; uint32_t v___y_163_; uint64_t v___y_166_; uint8_t v___y_167_; uint64_t v___y_168_; uint32_t v___y_169_; uint64_t v___y_170_; uint64_t v___y_180_; uint8_t v___y_181_; uint64_t v___y_182_; uint8_t v___y_183_; uint32_t v___y_184_; uint64_t v___y_185_; uint64_t v___y_192_; uint8_t v___y_193_; uint64_t v___y_194_; uint32_t v___y_195_; uint64_t v___y_196_; uint64_t v___y_202_; uint8_t v___y_203_; uint64_t v___y_204_; uint32_t v___y_205_; uint64_t v___y_206_; uint64_t v___y_207_; uint64_t v___y_262_; uint8_t v___y_263_; uint64_t v___y_264_; uint32_t v___y_265_; uint64_t v___y_266_; uint64_t v___y_267_; uint64_t v___y_268_; uint64_t v___y_274_; uint8_t v___y_275_; uint64_t v___y_276_; uint64_t v___y_277_; uint32_t v___y_278_; uint64_t v___y_279_; uint64_t v___y_280_; uint64_t v___y_281_; uint64_t v___y_282_; uint64_t v___y_287_; uint8_t v___y_288_; uint64_t v___y_289_; uint64_t v___y_290_; uint32_t v___y_291_; uint64_t v___y_292_; uint64_t v___y_293_; uint64_t v___y_298_; uint64_t v___y_299_; uint8_t v___y_300_; uint64_t v___y_301_; uint32_t v___y_302_; uint64_t v___y_303_; uint64_t v___y_304_; uint64_t v___y_305_; uint64_t v___y_306_; uint64_t v___y_311_; uint64_t v___y_312_; uint8_t v___y_313_; uint64_t v___y_314_; uint32_t v___y_315_; uint64_t v___y_316_; uint64_t v___y_317_; uint64_t v___y_322_; uint8_t v___y_323_; uint64_t v___y_324_; uint64_t v___y_325_; uint64_t v___y_326_; uint64_t v___y_327_; uint32_t v___y_328_; uint64_t v___y_329_; uint64_t v___y_330_; uint64_t v___y_335_; uint8_t v___y_336_; uint64_t v___y_337_; uint64_t v___y_338_; uint32_t v___y_339_; uint64_t v___y_340_; uint64_t v___y_341_; uint64_t v___y_346_; uint64_t v___y_347_; uint8_t v___y_348_; uint64_t v___y_349_; uint64_t v___y_350_; uint32_t v___y_351_; uint64_t v___y_352_; uint64_t v___y_353_; uint64_t v___y_354_; uint64_t v___y_359_; uint8_t v___y_360_; uint64_t v___y_361_; uint32_t v___y_362_; uint64_t v___y_363_; uint64_t v___y_364_; uint64_t v___y_365_; uint64_t v___y_370_; uint8_t v___y_371_; uint64_t v___y_372_; uint32_t v___y_373_; uint64_t v___y_374_; uint64_t v___y_375_; uint64_t v___y_376_; uint8_t v___y_380_; uint64_t v___y_381_; uint32_t v___y_382_; uint64_t v___y_383_; uint8_t v___y_391_; uint32_t v___y_392_; uint64_t v___y_393_; uint64_t v___y_394_; uint8_t v___y_403_; uint64_t v___y_404_; uint64_t v___y_405_; uint32_t v___y_406_; uint64_t v___y_407_; uint64_t v___y_408_; uint8_t v___y_441_; uint64_t v___y_442_; uint32_t v___y_443_; uint64_t v___y_444_; uint64_t v___y_445_; uint8_t v___y_452_; uint64_t v___y_453_; uint32_t v___y_454_; uint64_t v___y_455_; uint32_t v___y_462_; uint8_t v___y_463_; uint32_t v___y_464_; uint64_t v___y_465_; uint8_t v___y_472_; uint8_t v___y_482_; uint8_t v___y_483_; uint8_t v___y_485_; uint8_t v___y_486_; uint8_t v___y_487_; uint8_t v___y_489_; uint8_t v___y_490_; uint8_t v___y_495_; uint8_t v___x_503_; 
v___x_144_ = 2147483647;
v___x_145_ = lean_uint32_land(v___y_73_, v___x_144_);
v___x_146_ = 0;
v___x_503_ = lean_uint32_dec_eq(v___x_145_, v___x_146_);
if (v___x_503_ == 0)
{
uint32_t v___x_504_; uint8_t v___x_505_; 
v___x_504_ = lean_uint32_land(v___y_74_, v___x_144_);
v___x_505_ = lean_uint32_dec_eq(v___x_504_, v___x_146_);
if (v___x_505_ == 0)
{
uint32_t v___x_506_; uint32_t v___x_507_; uint32_t v___x_508_; uint8_t v___x_509_; 
v___x_506_ = 4278190080;
v___x_507_ = 1;
v___x_508_ = lean_uint32_shift_left(v___y_73_, v___x_507_);
v___x_509_ = lean_uint32_dec_le(v___x_506_, v___x_508_);
if (v___x_509_ == 0)
{
uint32_t v___x_510_; uint8_t v___x_511_; 
v___x_510_ = lean_uint32_shift_left(v___y_74_, v___x_507_);
v___x_511_ = lean_uint32_dec_le(v___x_506_, v___x_510_);
v___y_495_ = v___x_511_;
goto v___jp_494_;
}
else
{
v___y_495_ = v___x_509_;
goto v___jp_494_;
}
}
else
{
goto v___jp_133_;
}
}
else
{
goto v___jp_133_;
}
v___jp_147_:
{
uint8_t v___x_152_; 
v___x_152_ = lean_uint64_dec_eq(v___y_151_, v___y_148_);
if (v___x_152_ == 0)
{
uint64_t v___x_153_; uint8_t v___x_154_; 
v___x_153_ = 8388608ULL;
v___x_154_ = lean_uint64_dec_eq(v___y_151_, v___x_153_);
if (v___x_154_ == 0)
{
uint32_t v___x_155_; 
v___x_155_ = lean_uint64_to_uint32(v___y_151_);
if (v___y_149_ == 0)
{
v___y_96_ = v___y_150_;
v___y_97_ = v___x_155_;
v___y_98_ = v___x_146_;
goto v___jp_95_;
}
else
{
uint32_t v___x_156_; 
v___x_156_ = 2147483648;
v___y_96_ = v___y_150_;
v___y_97_ = v___x_155_;
v___y_98_ = v___x_156_;
goto v___jp_95_;
}
}
else
{
if (v___y_149_ == 0)
{
v___y_92_ = v___x_146_;
goto v___jp_91_;
}
else
{
uint32_t v___x_157_; 
v___x_157_ = 2147483648;
v___y_92_ = v___x_157_;
goto v___jp_91_;
}
}
}
else
{
if (v___y_149_ == 0)
{
return v___x_146_;
}
else
{
uint32_t v___x_158_; 
v___x_158_ = 2147483648;
return v___x_158_;
}
}
}
v___jp_159_:
{
if (v___y_160_ == 0)
{
v___y_111_ = v___y_161_;
v___y_112_ = v___y_163_;
v___y_113_ = v___y_162_;
v___y_114_ = v___x_146_;
goto v___jp_110_;
}
else
{
uint32_t v___x_164_; 
v___x_164_ = 2147483648;
v___y_111_ = v___y_161_;
v___y_112_ = v___y_163_;
v___y_113_ = v___y_162_;
v___y_114_ = v___x_164_;
goto v___jp_110_;
}
}
v___jp_165_:
{
uint64_t v___x_171_; uint64_t v_encodedExponent_172_; uint32_t v___x_173_; uint64_t v___x_174_; uint8_t v___x_175_; 
v___x_171_ = 171ULL;
v_encodedExponent_172_ = lean_uint64_sub(v___y_168_, v___x_171_);
v___x_173_ = lean_uint64_to_uint32(v_encodedExponent_172_);
v___x_174_ = 8388608ULL;
v___x_175_ = lean_uint64_dec_lt(v___y_170_, v___x_174_);
if (v___x_175_ == 0)
{
uint64_t v___x_176_; uint32_t v___x_177_; 
v___x_176_ = lean_uint64_sub(v___y_170_, v___x_174_);
v___x_177_ = lean_uint64_to_uint32(v___x_176_);
v___y_160_ = v___y_167_;
v___y_161_ = v___y_169_;
v___y_162_ = v___x_173_;
v___y_163_ = v___x_177_;
goto v___jp_159_;
}
else
{
uint32_t v___x_178_; 
v___x_178_ = lean_uint64_to_uint32(v___y_166_);
v___y_160_ = v___y_167_;
v___y_161_ = v___y_169_;
v___y_162_ = v___x_173_;
v___y_163_ = v___x_178_;
goto v___jp_159_;
}
}
v___jp_179_:
{
uint64_t v___x_186_; uint8_t v___x_187_; 
v___x_186_ = 425ULL;
v___x_187_ = lean_uint64_dec_lt(v___x_186_, v___y_185_);
if (v___x_187_ == 0)
{
if (v___y_183_ == 0)
{
v___y_166_ = v___y_180_;
v___y_167_ = v___y_181_;
v___y_168_ = v___y_185_;
v___y_169_ = v___y_184_;
v___y_170_ = v___y_182_;
goto v___jp_165_;
}
else
{
uint64_t v___x_188_; 
v___x_188_ = 8388608ULL;
v___y_166_ = v___y_180_;
v___y_167_ = v___y_181_;
v___y_168_ = v___y_185_;
v___y_169_ = v___y_184_;
v___y_170_ = v___x_188_;
goto v___jp_165_;
}
}
else
{
if (v___y_181_ == 0)
{
uint32_t v___x_189_; 
v___x_189_ = 2139095040;
return v___x_189_;
}
else
{
uint32_t v___x_190_; 
v___x_190_ = 4286578688;
return v___x_190_;
}
}
}
v___jp_191_:
{
uint64_t v___x_197_; uint8_t v_carry_198_; 
v___x_197_ = 16777216ULL;
v_carry_198_ = lean_uint64_dec_eq(v___y_196_, v___x_197_);
if (v_carry_198_ == 0)
{
v___y_180_ = v___y_192_;
v___y_181_ = v___y_193_;
v___y_182_ = v___y_196_;
v___y_183_ = v_carry_198_;
v___y_184_ = v___y_195_;
v___y_185_ = v___y_194_;
goto v___jp_179_;
}
else
{
uint64_t v___x_199_; uint64_t v___x_200_; 
v___x_199_ = 1ULL;
v___x_200_ = lean_uint64_add(v___y_194_, v___x_199_);
v___y_180_ = v___y_192_;
v___y_181_ = v___y_193_;
v___y_182_ = v___y_196_;
v___y_183_ = v_carry_198_;
v___y_184_ = v___y_195_;
v___y_185_ = v___x_200_;
goto v___jp_179_;
}
}
v___jp_201_:
{
uint64_t v_position_208_; uint64_t v___x_209_; uint8_t v___x_210_; 
v_position_208_ = lean_uint64_add(v___y_207_, v___y_206_);
v___x_209_ = 172ULL;
v___x_210_ = lean_uint64_dec_lt(v_position_208_, v___x_209_);
if (v___x_210_ == 0)
{
uint64_t v___x_211_; uint8_t v___x_212_; 
v___x_211_ = 23ULL;
v___x_212_ = lean_uint64_dec_lt(v___y_207_, v___x_211_);
if (v___x_212_ == 0)
{
uint64_t v___x_213_; uint8_t v___x_214_; 
v___x_213_ = lean_uint64_sub(v___y_207_, v___x_211_);
v___x_214_ = lean_uint64_dec_eq(v___x_213_, v___y_202_);
if (v___x_214_ == 0)
{
uint64_t v___x_215_; uint8_t v___x_216_; 
v___x_215_ = 64ULL;
v___x_216_ = lean_uint64_dec_lt(v___x_213_, v___x_215_);
if (v___x_216_ == 0)
{
uint8_t v___x_217_; 
v___x_217_ = lean_uint64_dec_eq(v___x_213_, v___x_215_);
if (v___x_217_ == 0)
{
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v___y_202_;
goto v___jp_191_;
}
else
{
uint64_t v___x_218_; uint8_t v___x_219_; 
v___x_218_ = 9223372036854775808ULL;
v___x_219_ = lean_uint64_dec_lt(v___x_218_, v___y_204_);
if (v___x_219_ == 0)
{
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v___y_202_;
goto v___jp_191_;
}
else
{
uint64_t v___x_220_; 
v___x_220_ = 1ULL;
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v___x_220_;
goto v___jp_191_;
}
}
}
else
{
uint64_t v_quotient_221_; uint64_t v___x_222_; uint64_t v___x_223_; uint64_t v___x_224_; uint64_t v_remainder_225_; uint64_t v___x_226_; uint64_t v_half_227_; uint8_t v___x_228_; 
v_quotient_221_ = lean_uint64_shift_right(v___y_204_, v___x_213_);
v___x_222_ = 1ULL;
v___x_223_ = lean_uint64_shift_left(v___x_222_, v___x_213_);
v___x_224_ = lean_uint64_sub(v___x_223_, v___x_222_);
v_remainder_225_ = lean_uint64_land(v___y_204_, v___x_224_);
v___x_226_ = lean_uint64_sub(v___x_213_, v___x_222_);
v_half_227_ = lean_uint64_shift_left(v___x_222_, v___x_226_);
v___x_228_ = lean_uint64_dec_lt(v_remainder_225_, v_half_227_);
if (v___x_228_ == 0)
{
uint8_t v___x_229_; 
v___x_229_ = lean_uint64_dec_lt(v_half_227_, v_remainder_225_);
if (v___x_229_ == 0)
{
uint64_t v___x_230_; uint8_t v___x_231_; 
v___x_230_ = lean_uint64_land(v_quotient_221_, v___x_222_);
v___x_231_ = lean_uint64_dec_eq(v___x_230_, v___y_202_);
if (v___x_231_ == 0)
{
uint64_t v___x_232_; 
v___x_232_ = lean_uint64_add(v_quotient_221_, v___x_222_);
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v___x_232_;
goto v___jp_191_;
}
else
{
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v_quotient_221_;
goto v___jp_191_;
}
}
else
{
uint64_t v___x_233_; 
v___x_233_ = lean_uint64_add(v_quotient_221_, v___x_222_);
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v___x_233_;
goto v___jp_191_;
}
}
else
{
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v_quotient_221_;
goto v___jp_191_;
}
}
}
else
{
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v___y_204_;
goto v___jp_191_;
}
}
else
{
uint64_t v___x_234_; uint64_t v___x_235_; 
v___x_234_ = lean_uint64_sub(v___x_211_, v___y_207_);
v___x_235_ = lean_uint64_shift_left(v___y_204_, v___x_234_);
v___y_192_ = v___y_202_;
v___y_193_ = v___y_203_;
v___y_194_ = v_position_208_;
v___y_195_ = v___y_205_;
v___y_196_ = v___x_235_;
goto v___jp_191_;
}
}
else
{
uint64_t v___x_236_; uint8_t v___x_237_; 
v___x_236_ = 149ULL;
v___x_237_ = lean_uint64_dec_lt(v___y_206_, v___x_236_);
if (v___x_237_ == 0)
{
uint64_t v___x_238_; uint64_t v___x_239_; 
v___x_238_ = lean_uint64_sub(v___y_206_, v___x_236_);
v___x_239_ = lean_uint64_shift_left(v___y_204_, v___x_238_);
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v___x_239_;
goto v___jp_147_;
}
else
{
uint64_t v___x_240_; uint8_t v___x_241_; 
v___x_240_ = lean_uint64_sub(v___x_236_, v___y_206_);
v___x_241_ = lean_uint64_dec_eq(v___x_240_, v___y_202_);
if (v___x_241_ == 0)
{
uint64_t v___x_242_; uint8_t v___x_243_; 
v___x_242_ = 64ULL;
v___x_243_ = lean_uint64_dec_lt(v___x_240_, v___x_242_);
if (v___x_243_ == 0)
{
uint8_t v___x_244_; 
v___x_244_ = lean_uint64_dec_eq(v___x_240_, v___x_242_);
if (v___x_244_ == 0)
{
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v___y_202_;
goto v___jp_147_;
}
else
{
uint64_t v___x_245_; uint8_t v___x_246_; 
v___x_245_ = 9223372036854775808ULL;
v___x_246_ = lean_uint64_dec_lt(v___x_245_, v___y_204_);
if (v___x_246_ == 0)
{
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v___y_202_;
goto v___jp_147_;
}
else
{
uint64_t v___x_247_; 
v___x_247_ = 1ULL;
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v___x_247_;
goto v___jp_147_;
}
}
}
else
{
uint64_t v_quotient_248_; uint64_t v___x_249_; uint64_t v___x_250_; uint64_t v___x_251_; uint64_t v_remainder_252_; uint64_t v___x_253_; uint64_t v_half_254_; uint8_t v___x_255_; 
v_quotient_248_ = lean_uint64_shift_right(v___y_204_, v___x_240_);
v___x_249_ = 1ULL;
v___x_250_ = lean_uint64_shift_left(v___x_249_, v___x_240_);
v___x_251_ = lean_uint64_sub(v___x_250_, v___x_249_);
v_remainder_252_ = lean_uint64_land(v___y_204_, v___x_251_);
v___x_253_ = lean_uint64_sub(v___x_240_, v___x_249_);
v_half_254_ = lean_uint64_shift_left(v___x_249_, v___x_253_);
v___x_255_ = lean_uint64_dec_lt(v_remainder_252_, v_half_254_);
if (v___x_255_ == 0)
{
uint8_t v___x_256_; 
v___x_256_ = lean_uint64_dec_lt(v_half_254_, v_remainder_252_);
if (v___x_256_ == 0)
{
uint64_t v___x_257_; uint8_t v___x_258_; 
v___x_257_ = lean_uint64_land(v_quotient_248_, v___x_249_);
v___x_258_ = lean_uint64_dec_eq(v___x_257_, v___y_202_);
if (v___x_258_ == 0)
{
uint64_t v___x_259_; 
v___x_259_ = lean_uint64_add(v_quotient_248_, v___x_249_);
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v___x_259_;
goto v___jp_147_;
}
else
{
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v_quotient_248_;
goto v___jp_147_;
}
}
else
{
uint64_t v___x_260_; 
v___x_260_ = lean_uint64_add(v_quotient_248_, v___x_249_);
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v___x_260_;
goto v___jp_147_;
}
}
else
{
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v_quotient_248_;
goto v___jp_147_;
}
}
}
else
{
v___y_148_ = v___y_202_;
v___y_149_ = v___y_203_;
v___y_150_ = v___y_205_;
v___y_151_ = v___y_204_;
goto v___jp_147_;
}
}
}
}
v___jp_261_:
{
uint64_t v___x_269_; uint64_t v___x_270_; uint8_t v___x_271_; 
v___x_269_ = 1ULL;
v___x_270_ = lean_uint64_shift_right(v___y_267_, v___x_269_);
v___x_271_ = lean_uint64_dec_eq(v___x_270_, v___y_262_);
if (v___x_271_ == 0)
{
uint64_t v___x_272_; 
v___x_272_ = lean_uint64_add(v___y_268_, v___x_269_);
v___y_202_ = v___y_262_;
v___y_203_ = v___y_263_;
v___y_204_ = v___y_264_;
v___y_205_ = v___y_265_;
v___y_206_ = v___y_266_;
v___y_207_ = v___x_272_;
goto v___jp_201_;
}
else
{
v___y_202_ = v___y_262_;
v___y_203_ = v___y_263_;
v___y_204_ = v___y_264_;
v___y_205_ = v___y_265_;
v___y_206_ = v___y_266_;
v___y_207_ = v___y_268_;
goto v___jp_201_;
}
}
v___jp_273_:
{
uint64_t v___x_283_; uint8_t v___x_284_; 
v___x_283_ = lean_uint64_shift_right(v___y_277_, v___y_280_);
v___x_284_ = lean_uint64_dec_eq(v___x_283_, v___y_274_);
if (v___x_284_ == 0)
{
uint64_t v___x_285_; 
v___x_285_ = lean_uint64_add(v___y_281_, v___y_280_);
v___y_262_ = v___y_274_;
v___y_263_ = v___y_275_;
v___y_264_ = v___y_276_;
v___y_265_ = v___y_278_;
v___y_266_ = v___y_279_;
v___y_267_ = v___y_282_;
v___y_268_ = v___x_285_;
goto v___jp_261_;
}
else
{
v___y_262_ = v___y_274_;
v___y_263_ = v___y_275_;
v___y_264_ = v___y_276_;
v___y_265_ = v___y_278_;
v___y_266_ = v___y_279_;
v___y_267_ = v___y_282_;
v___y_268_ = v___y_281_;
goto v___jp_261_;
}
}
v___jp_286_:
{
uint64_t v___x_294_; uint64_t v___x_295_; uint8_t v___x_296_; 
v___x_294_ = 2ULL;
v___x_295_ = lean_uint64_shift_right(v___y_290_, v___x_294_);
v___x_296_ = lean_uint64_dec_eq(v___x_295_, v___y_287_);
if (v___x_296_ == 0)
{
v___y_274_ = v___y_287_;
v___y_275_ = v___y_288_;
v___y_276_ = v___y_289_;
v___y_277_ = v___y_290_;
v___y_278_ = v___y_291_;
v___y_279_ = v___y_292_;
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
v___y_278_ = v___y_291_;
v___y_279_ = v___y_292_;
v___y_280_ = v___x_294_;
v___y_281_ = v___y_293_;
v___y_282_ = v___y_290_;
goto v___jp_273_;
}
}
v___jp_297_:
{
uint64_t v___x_307_; uint8_t v___x_308_; 
v___x_307_ = lean_uint64_shift_right(v___y_298_, v___y_304_);
v___x_308_ = lean_uint64_dec_eq(v___x_307_, v___y_299_);
if (v___x_308_ == 0)
{
uint64_t v___x_309_; 
v___x_309_ = lean_uint64_add(v___y_303_, v___y_304_);
v___y_287_ = v___y_299_;
v___y_288_ = v___y_300_;
v___y_289_ = v___y_301_;
v___y_290_ = v___y_306_;
v___y_291_ = v___y_302_;
v___y_292_ = v___y_305_;
v___y_293_ = v___x_309_;
goto v___jp_286_;
}
else
{
v___y_287_ = v___y_299_;
v___y_288_ = v___y_300_;
v___y_289_ = v___y_301_;
v___y_290_ = v___y_306_;
v___y_291_ = v___y_302_;
v___y_292_ = v___y_305_;
v___y_293_ = v___y_303_;
goto v___jp_286_;
}
}
v___jp_310_:
{
uint64_t v___x_318_; uint64_t v___x_319_; uint8_t v___x_320_; 
v___x_318_ = 4ULL;
v___x_319_ = lean_uint64_shift_right(v___y_312_, v___x_318_);
v___x_320_ = lean_uint64_dec_eq(v___x_319_, v___y_311_);
if (v___x_320_ == 0)
{
v___y_298_ = v___y_312_;
v___y_299_ = v___y_311_;
v___y_300_ = v___y_313_;
v___y_301_ = v___y_314_;
v___y_302_ = v___y_315_;
v___y_303_ = v___y_317_;
v___y_304_ = v___x_318_;
v___y_305_ = v___y_316_;
v___y_306_ = v___x_319_;
goto v___jp_297_;
}
else
{
v___y_298_ = v___y_312_;
v___y_299_ = v___y_311_;
v___y_300_ = v___y_313_;
v___y_301_ = v___y_314_;
v___y_302_ = v___y_315_;
v___y_303_ = v___y_317_;
v___y_304_ = v___x_318_;
v___y_305_ = v___y_316_;
v___y_306_ = v___y_312_;
goto v___jp_297_;
}
}
v___jp_321_:
{
uint64_t v___x_331_; uint8_t v___x_332_; 
v___x_331_ = lean_uint64_shift_right(v___y_327_, v___y_325_);
v___x_332_ = lean_uint64_dec_eq(v___x_331_, v___y_322_);
if (v___x_332_ == 0)
{
uint64_t v___x_333_; 
v___x_333_ = lean_uint64_add(v___y_326_, v___y_325_);
v___y_311_ = v___y_322_;
v___y_312_ = v___y_330_;
v___y_313_ = v___y_323_;
v___y_314_ = v___y_324_;
v___y_315_ = v___y_328_;
v___y_316_ = v___y_329_;
v___y_317_ = v___x_333_;
goto v___jp_310_;
}
else
{
v___y_311_ = v___y_322_;
v___y_312_ = v___y_330_;
v___y_313_ = v___y_323_;
v___y_314_ = v___y_324_;
v___y_315_ = v___y_328_;
v___y_316_ = v___y_329_;
v___y_317_ = v___y_326_;
goto v___jp_310_;
}
}
v___jp_334_:
{
uint64_t v___x_342_; uint64_t v___x_343_; uint8_t v___x_344_; 
v___x_342_ = 8ULL;
v___x_343_ = lean_uint64_shift_right(v___y_338_, v___x_342_);
v___x_344_ = lean_uint64_dec_eq(v___x_343_, v___y_335_);
if (v___x_344_ == 0)
{
v___y_322_ = v___y_335_;
v___y_323_ = v___y_336_;
v___y_324_ = v___y_337_;
v___y_325_ = v___x_342_;
v___y_326_ = v___y_341_;
v___y_327_ = v___y_338_;
v___y_328_ = v___y_339_;
v___y_329_ = v___y_340_;
v___y_330_ = v___x_343_;
goto v___jp_321_;
}
else
{
v___y_322_ = v___y_335_;
v___y_323_ = v___y_336_;
v___y_324_ = v___y_337_;
v___y_325_ = v___x_342_;
v___y_326_ = v___y_341_;
v___y_327_ = v___y_338_;
v___y_328_ = v___y_339_;
v___y_329_ = v___y_340_;
v___y_330_ = v___y_338_;
goto v___jp_321_;
}
}
v___jp_345_:
{
uint64_t v___x_355_; uint8_t v___x_356_; 
v___x_355_ = lean_uint64_shift_right(v___y_352_, v___y_347_);
v___x_356_ = lean_uint64_dec_eq(v___x_355_, v___y_346_);
if (v___x_356_ == 0)
{
uint64_t v___x_357_; 
v___x_357_ = lean_uint64_add(v___y_350_, v___y_347_);
v___y_335_ = v___y_346_;
v___y_336_ = v___y_348_;
v___y_337_ = v___y_349_;
v___y_338_ = v___y_354_;
v___y_339_ = v___y_351_;
v___y_340_ = v___y_353_;
v___y_341_ = v___x_357_;
goto v___jp_334_;
}
else
{
v___y_335_ = v___y_346_;
v___y_336_ = v___y_348_;
v___y_337_ = v___y_349_;
v___y_338_ = v___y_354_;
v___y_339_ = v___y_351_;
v___y_340_ = v___y_353_;
v___y_341_ = v___y_350_;
goto v___jp_334_;
}
}
v___jp_358_:
{
uint64_t v___x_366_; uint64_t v___x_367_; uint8_t v___x_368_; 
v___x_366_ = 16ULL;
v___x_367_ = lean_uint64_shift_right(v___y_364_, v___x_366_);
v___x_368_ = lean_uint64_dec_eq(v___x_367_, v___y_359_);
if (v___x_368_ == 0)
{
v___y_346_ = v___y_359_;
v___y_347_ = v___x_366_;
v___y_348_ = v___y_360_;
v___y_349_ = v___y_361_;
v___y_350_ = v___y_365_;
v___y_351_ = v___y_362_;
v___y_352_ = v___y_364_;
v___y_353_ = v___y_363_;
v___y_354_ = v___x_367_;
goto v___jp_345_;
}
else
{
v___y_346_ = v___y_359_;
v___y_347_ = v___x_366_;
v___y_348_ = v___y_360_;
v___y_349_ = v___y_361_;
v___y_350_ = v___y_365_;
v___y_351_ = v___y_362_;
v___y_352_ = v___y_364_;
v___y_353_ = v___y_363_;
v___y_354_ = v___y_364_;
goto v___jp_345_;
}
}
v___jp_369_:
{
uint64_t v___x_377_; uint8_t v___x_378_; 
v___x_377_ = lean_uint64_shift_right(v___y_372_, v___y_374_);
v___x_378_ = lean_uint64_dec_eq(v___x_377_, v___y_370_);
if (v___x_378_ == 0)
{
v___y_359_ = v___y_370_;
v___y_360_ = v___y_371_;
v___y_361_ = v___y_372_;
v___y_362_ = v___y_373_;
v___y_363_ = v___y_375_;
v___y_364_ = v___y_376_;
v___y_365_ = v___y_374_;
goto v___jp_358_;
}
else
{
v___y_359_ = v___y_370_;
v___y_360_ = v___y_371_;
v___y_361_ = v___y_372_;
v___y_362_ = v___y_373_;
v___y_363_ = v___y_375_;
v___y_364_ = v___y_376_;
v___y_365_ = v___y_370_;
goto v___jp_358_;
}
}
v___jp_379_:
{
uint64_t v___x_384_; uint8_t v___x_385_; 
v___x_384_ = 0ULL;
v___x_385_ = lean_uint64_dec_eq(v___y_381_, v___x_384_);
if (v___x_385_ == 0)
{
uint64_t v___x_386_; uint64_t v___x_387_; uint8_t v___x_388_; 
v___x_386_ = 32ULL;
v___x_387_ = lean_uint64_shift_right(v___y_381_, v___x_386_);
v___x_388_ = lean_uint64_dec_eq(v___x_387_, v___x_384_);
if (v___x_388_ == 0)
{
v___y_370_ = v___x_384_;
v___y_371_ = v___y_380_;
v___y_372_ = v___y_381_;
v___y_373_ = v___y_382_;
v___y_374_ = v___x_386_;
v___y_375_ = v___y_383_;
v___y_376_ = v___x_387_;
goto v___jp_369_;
}
else
{
v___y_370_ = v___x_384_;
v___y_371_ = v___y_380_;
v___y_372_ = v___y_381_;
v___y_373_ = v___y_382_;
v___y_374_ = v___x_386_;
v___y_375_ = v___y_383_;
v___y_376_ = v___y_381_;
goto v___jp_369_;
}
}
else
{
if (v___y_380_ == 0)
{
return v___x_146_;
}
else
{
uint32_t v___x_389_; 
v___x_389_ = 2147483648;
return v___x_389_;
}
}
}
v___jp_390_:
{
uint8_t v___x_395_; 
v___x_395_ = lean_uint64_dec_eq(v___y_394_, v___y_393_);
if (v___x_395_ == 0)
{
uint64_t v___x_396_; uint8_t v___x_397_; 
v___x_396_ = 8388608ULL;
v___x_397_ = lean_uint64_dec_eq(v___y_394_, v___x_396_);
if (v___x_397_ == 0)
{
uint32_t v___x_398_; 
v___x_398_ = lean_uint64_to_uint32(v___y_394_);
if (v___y_391_ == 0)
{
v___y_102_ = v___y_392_;
v___y_103_ = v___x_398_;
v___y_104_ = v___x_146_;
goto v___jp_101_;
}
else
{
uint32_t v___x_399_; 
v___x_399_ = 2147483648;
v___y_102_ = v___y_392_;
v___y_103_ = v___x_398_;
v___y_104_ = v___x_399_;
goto v___jp_101_;
}
}
else
{
if (v___y_391_ == 0)
{
v___y_88_ = v___x_146_;
goto v___jp_87_;
}
else
{
uint32_t v___x_400_; 
v___x_400_ = 2147483648;
v___y_88_ = v___x_400_;
goto v___jp_87_;
}
}
}
else
{
if (v___y_391_ == 0)
{
return v___x_146_;
}
else
{
uint32_t v___x_401_; 
v___x_401_ = 2147483648;
return v___x_401_;
}
}
}
v___jp_402_:
{
uint64_t v___x_409_; uint64_t v___x_410_; uint64_t v___x_411_; uint8_t v___x_412_; 
v___x_409_ = lean_uint64_mul(v___y_405_, v___y_407_);
v___x_410_ = lean_uint64_add(v___y_404_, v___y_408_);
v___x_411_ = 281474976710656ULL;
v___x_412_ = lean_uint64_dec_lt(v___x_409_, v___x_411_);
if (v___x_412_ == 0)
{
v___y_380_ = v___y_403_;
v___y_381_ = v___x_409_;
v___y_382_ = v___y_406_;
v___y_383_ = v___x_410_;
goto v___jp_379_;
}
else
{
uint64_t v___x_413_; uint8_t v___x_414_; 
v___x_413_ = 123ULL;
v___x_414_ = lean_uint64_dec_le(v___x_410_, v___x_413_);
if (v___x_414_ == 0)
{
v___y_380_ = v___y_403_;
v___y_381_ = v___x_409_;
v___y_382_ = v___y_406_;
v___y_383_ = v___x_410_;
goto v___jp_379_;
}
else
{
uint64_t v___x_415_; uint8_t v___x_416_; 
v___x_415_ = 0ULL;
v___x_416_ = lean_uint64_dec_eq(v___x_409_, v___x_415_);
if (v___x_416_ == 0)
{
uint64_t v___x_417_; uint64_t v___x_418_; uint8_t v___x_419_; 
v___x_417_ = 149ULL;
v___x_418_ = lean_uint64_sub(v___x_417_, v___x_410_);
v___x_419_ = lean_uint64_dec_eq(v___x_418_, v___x_415_);
if (v___x_419_ == 0)
{
uint64_t v___x_420_; uint8_t v___x_421_; 
v___x_420_ = 64ULL;
v___x_421_ = lean_uint64_dec_lt(v___x_418_, v___x_420_);
if (v___x_421_ == 0)
{
uint8_t v___x_422_; 
v___x_422_ = lean_uint64_dec_eq(v___x_418_, v___x_420_);
if (v___x_422_ == 0)
{
v___y_391_ = v___y_403_;
v___y_392_ = v___y_406_;
v___y_393_ = v___x_415_;
v___y_394_ = v___x_415_;
goto v___jp_390_;
}
else
{
uint64_t v___x_423_; uint8_t v___x_424_; 
v___x_423_ = 9223372036854775808ULL;
v___x_424_ = lean_uint64_dec_lt(v___x_423_, v___x_409_);
if (v___x_424_ == 0)
{
v___y_391_ = v___y_403_;
v___y_392_ = v___y_406_;
v___y_393_ = v___x_415_;
v___y_394_ = v___x_415_;
goto v___jp_390_;
}
else
{
uint64_t v___x_425_; 
v___x_425_ = 1ULL;
v___y_391_ = v___y_403_;
v___y_392_ = v___y_406_;
v___y_393_ = v___x_415_;
v___y_394_ = v___x_425_;
goto v___jp_390_;
}
}
}
else
{
uint64_t v_quotient_426_; uint64_t v___x_427_; uint64_t v___x_428_; uint64_t v___x_429_; uint64_t v_remainder_430_; uint64_t v___x_431_; uint64_t v_half_432_; uint8_t v___x_433_; 
v_quotient_426_ = lean_uint64_shift_right(v___x_409_, v___x_418_);
v___x_427_ = 1ULL;
v___x_428_ = lean_uint64_shift_left(v___x_427_, v___x_418_);
v___x_429_ = lean_uint64_sub(v___x_428_, v___x_427_);
v_remainder_430_ = lean_uint64_land(v___x_409_, v___x_429_);
v___x_431_ = lean_uint64_sub(v___x_418_, v___x_427_);
v_half_432_ = lean_uint64_shift_left(v___x_427_, v___x_431_);
v___x_433_ = lean_uint64_dec_lt(v_remainder_430_, v_half_432_);
if (v___x_433_ == 0)
{
uint8_t v___x_434_; 
v___x_434_ = lean_uint64_dec_lt(v_half_432_, v_remainder_430_);
if (v___x_434_ == 0)
{
uint64_t v___x_435_; uint8_t v___x_436_; 
v___x_435_ = lean_uint64_land(v_quotient_426_, v___x_427_);
v___x_436_ = lean_uint64_dec_eq(v___x_435_, v___x_415_);
if (v___x_436_ == 0)
{
uint64_t v___x_437_; 
v___x_437_ = lean_uint64_add(v_quotient_426_, v___x_427_);
v___y_391_ = v___y_403_;
v___y_392_ = v___y_406_;
v___y_393_ = v___x_415_;
v___y_394_ = v___x_437_;
goto v___jp_390_;
}
else
{
v___y_391_ = v___y_403_;
v___y_392_ = v___y_406_;
v___y_393_ = v___x_415_;
v___y_394_ = v_quotient_426_;
goto v___jp_390_;
}
}
else
{
uint64_t v___x_438_; 
v___x_438_ = lean_uint64_add(v_quotient_426_, v___x_427_);
v___y_391_ = v___y_403_;
v___y_392_ = v___y_406_;
v___y_393_ = v___x_415_;
v___y_394_ = v___x_438_;
goto v___jp_390_;
}
}
else
{
v___y_391_ = v___y_403_;
v___y_392_ = v___y_406_;
v___y_393_ = v___x_415_;
v___y_394_ = v_quotient_426_;
goto v___jp_390_;
}
}
}
else
{
v___y_391_ = v___y_403_;
v___y_392_ = v___y_406_;
v___y_393_ = v___x_415_;
v___y_394_ = v___x_409_;
goto v___jp_390_;
}
}
else
{
if (v___y_403_ == 0)
{
return v___x_146_;
}
else
{
uint32_t v___x_439_; 
v___x_439_ = 2147483648;
return v___x_439_;
}
}
}
}
}
v___jp_440_:
{
uint64_t v___x_446_; uint64_t v___x_447_; uint8_t v___x_448_; 
v___x_446_ = lean_uint32_to_uint64(v_ey_122_);
v___x_447_ = 0ULL;
v___x_448_ = lean_uint64_dec_eq(v___x_446_, v___x_447_);
if (v___x_448_ == 0)
{
uint64_t v___x_449_; uint64_t v___x_450_; 
v___x_449_ = 1ULL;
v___x_450_ = lean_uint64_sub(v___x_446_, v___x_449_);
v___y_403_ = v___y_441_;
v___y_404_ = v___y_445_;
v___y_405_ = v___y_442_;
v___y_406_ = v___y_443_;
v___y_407_ = v___y_444_;
v___y_408_ = v___x_450_;
goto v___jp_402_;
}
else
{
v___y_403_ = v___y_441_;
v___y_404_ = v___y_445_;
v___y_405_ = v___y_442_;
v___y_406_ = v___y_443_;
v___y_407_ = v___y_444_;
v___y_408_ = v___x_447_;
goto v___jp_402_;
}
}
v___jp_451_:
{
uint64_t v___x_456_; uint64_t v___x_457_; uint8_t v___x_458_; 
v___x_456_ = lean_uint32_to_uint64(v_ex_120_);
v___x_457_ = 0ULL;
v___x_458_ = lean_uint64_dec_eq(v___x_456_, v___x_457_);
if (v___x_458_ == 0)
{
uint64_t v___x_459_; uint64_t v___x_460_; 
v___x_459_ = 1ULL;
v___x_460_ = lean_uint64_sub(v___x_456_, v___x_459_);
v___y_441_ = v___y_452_;
v___y_442_ = v___y_453_;
v___y_443_ = v___y_454_;
v___y_444_ = v___y_455_;
v___y_445_ = v___x_460_;
goto v___jp_440_;
}
else
{
v___y_441_ = v___y_452_;
v___y_442_ = v___y_453_;
v___y_443_ = v___y_454_;
v___y_444_ = v___y_455_;
v___y_445_ = v___x_457_;
goto v___jp_440_;
}
}
v___jp_461_:
{
uint8_t v___x_466_; 
v___x_466_ = lean_uint32_dec_eq(v_ey_122_, v___x_146_);
if (v___x_466_ == 0)
{
uint64_t v___x_467_; uint64_t v___x_468_; uint64_t v___x_469_; 
v___x_467_ = lean_uint32_to_uint64(v___y_462_);
v___x_468_ = 8388608ULL;
v___x_469_ = lean_uint64_lor(v___x_467_, v___x_468_);
v___y_452_ = v___y_463_;
v___y_453_ = v___y_465_;
v___y_454_ = v___y_464_;
v___y_455_ = v___x_469_;
goto v___jp_451_;
}
else
{
uint64_t v___x_470_; 
v___x_470_ = lean_uint32_to_uint64(v___y_462_);
v___y_452_ = v___y_463_;
v___y_453_ = v___y_465_;
v___y_454_ = v___y_464_;
v___y_455_ = v___x_470_;
goto v___jp_451_;
}
}
v___jp_471_:
{
uint32_t v___x_473_; uint32_t v_xFraction_474_; uint32_t v_yFraction_475_; uint8_t v___x_476_; 
v___x_473_ = 8388607;
v_xFraction_474_ = lean_uint32_land(v___y_73_, v___x_473_);
v_yFraction_475_ = lean_uint32_land(v___y_74_, v___x_473_);
v___x_476_ = lean_uint32_dec_eq(v_ex_120_, v___x_146_);
if (v___x_476_ == 0)
{
uint64_t v___x_477_; uint64_t v___x_478_; uint64_t v___x_479_; 
v___x_477_ = lean_uint32_to_uint64(v_xFraction_474_);
v___x_478_ = 8388608ULL;
v___x_479_ = lean_uint64_lor(v___x_477_, v___x_478_);
v___y_462_ = v_yFraction_475_;
v___y_463_ = v___y_472_;
v___y_464_ = v___x_473_;
v___y_465_ = v___x_479_;
goto v___jp_461_;
}
else
{
uint64_t v___x_480_; 
v___x_480_ = lean_uint32_to_uint64(v_xFraction_474_);
v___y_462_ = v_yFraction_475_;
v___y_463_ = v___y_472_;
v___y_464_ = v___x_473_;
v___y_465_ = v___x_480_;
goto v___jp_461_;
}
}
v___jp_481_:
{
if (v___y_483_ == 0)
{
v___y_472_ = v___x_125_;
goto v___jp_471_;
}
else
{
v___y_472_ = v___y_482_;
goto v___jp_471_;
}
}
v___jp_484_:
{
if (v___y_486_ == 0)
{
if (v___y_487_ == 0)
{
v___y_482_ = v___y_485_;
v___y_483_ = v___x_125_;
goto v___jp_481_;
}
else
{
v___y_472_ = v___x_125_;
goto v___jp_471_;
}
}
else
{
v___y_482_ = v___y_485_;
v___y_483_ = v___y_487_;
goto v___jp_481_;
}
}
v___jp_488_:
{
uint32_t v___x_491_; uint32_t v___x_492_; uint8_t v___x_493_; 
v___x_491_ = 2147483648;
v___x_492_ = lean_uint32_land(v___y_74_, v___x_491_);
v___x_493_ = lean_uint32_dec_eq(v___x_492_, v___x_146_);
if (v___x_493_ == 0)
{
v___y_485_ = v___y_489_;
v___y_486_ = v___y_490_;
v___y_487_ = v___x_125_;
goto v___jp_484_;
}
else
{
v___y_485_ = v___y_489_;
v___y_486_ = v___y_490_;
v___y_487_ = v___y_489_;
goto v___jp_484_;
}
}
v___jp_494_:
{
if (v___y_495_ == 0)
{
uint32_t v___x_496_; uint32_t v___x_497_; uint8_t v___x_498_; 
v___x_496_ = 2147483648;
v___x_497_ = lean_uint32_land(v___y_73_, v___x_496_);
v___x_498_ = lean_uint32_dec_eq(v___x_497_, v___x_146_);
if (v___x_498_ == 0)
{
v___y_489_ = v___y_495_;
v___y_490_ = v___x_125_;
goto v___jp_488_;
}
else
{
v___y_489_ = v___y_495_;
v___y_490_ = v___y_495_;
goto v___jp_488_;
}
}
else
{
lean_object* v___x_499_; lean_object* v___x_500_; lean_object* v___x_501_; uint32_t v___x_502_; 
v___x_499_ = lean_uint32_to_nat(v___y_73_);
v___x_500_ = lean_uint32_to_nat(v___y_74_);
v___x_501_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_499_, v___x_500_);
v___x_502_ = lean_uint32_of_nat(v___x_501_);
lean_dec(v___x_501_);
return v___x_502_;
}
}
}
v___jp_75_:
{
float v___x_76_; float v___x_77_; float v___x_78_; uint32_t v___x_79_; 
v___x_76_ = lean_float32_of_bits(v___y_73_);
v___x_77_ = lean_float32_of_bits(v___y_74_);
v___x_78_ = lean_float32_mul(v___x_76_, v___x_77_);
v___x_79_ = lean_float32_to_bits(v___x_78_);
return v___x_79_;
}
v___jp_80_:
{
if (v___y_81_ == 0)
{
if (v___y_82_ == 0)
{
uint32_t v___x_83_; 
v___x_83_ = 0;
return v___x_83_;
}
else
{
uint32_t v___x_84_; 
v___x_84_ = 2147483648;
return v___x_84_;
}
}
else
{
if (v___y_82_ == 0)
{
uint32_t v___x_85_; 
v___x_85_ = 2147483648;
return v___x_85_;
}
else
{
uint32_t v___x_86_; 
v___x_86_ = 0;
return v___x_86_;
}
}
}
v___jp_87_:
{
uint32_t v___x_89_; uint32_t v___x_90_; 
v___x_89_ = 8388608;
v___x_90_ = lean_uint32_lor(v___y_88_, v___x_89_);
return v___x_90_;
}
v___jp_91_:
{
uint32_t v___x_93_; uint32_t v___x_94_; 
v___x_93_ = 8388608;
v___x_94_ = lean_uint32_lor(v___y_92_, v___x_93_);
return v___x_94_;
}
v___jp_95_:
{
uint32_t v___x_99_; uint32_t v___x_100_; 
v___x_99_ = lean_uint32_land(v___y_97_, v___y_96_);
v___x_100_ = lean_uint32_lor(v___y_98_, v___x_99_);
return v___x_100_;
}
v___jp_101_:
{
uint32_t v___x_105_; uint32_t v___x_106_; 
v___x_105_ = lean_uint32_land(v___y_103_, v___y_102_);
v___x_106_ = lean_uint32_lor(v___y_104_, v___x_105_);
return v___x_106_;
}
v___jp_110_:
{
uint32_t v___x_115_; uint32_t v___x_116_; uint32_t v___x_117_; uint32_t v___x_118_; uint32_t v___x_119_; 
v___x_115_ = lean_uint32_land(v___y_113_, v___x_109_);
v___x_116_ = lean_uint32_shift_left(v___x_115_, v___x_107_);
v___x_117_ = lean_uint32_lor(v___y_114_, v___x_116_);
v___x_118_ = lean_uint32_land(v___y_112_, v___y_111_);
v___x_119_ = lean_uint32_lor(v___x_117_, v___x_118_);
return v___x_119_;
}
v___jp_126_:
{
uint32_t v___x_128_; uint32_t v___x_129_; uint32_t v___x_130_; uint8_t v___x_131_; 
v___x_128_ = 2147483648;
v___x_129_ = lean_uint32_land(v___y_74_, v___x_128_);
v___x_130_ = 0;
v___x_131_ = lean_uint32_dec_eq(v___x_129_, v___x_130_);
if (v___x_131_ == 0)
{
v___y_81_ = v___y_127_;
v___y_82_ = v___x_125_;
goto v___jp_80_;
}
else
{
uint8_t v___x_132_; 
v___x_132_ = 0;
v___y_81_ = v___y_127_;
v___y_82_ = v___x_132_;
goto v___jp_80_;
}
}
v___jp_133_:
{
uint32_t v___x_134_; uint32_t v___x_135_; uint32_t v___x_136_; uint8_t v___x_137_; 
v___x_134_ = 2147483648;
v___x_135_ = lean_uint32_land(v___y_73_, v___x_134_);
v___x_136_ = 0;
v___x_137_ = lean_uint32_dec_eq(v___x_135_, v___x_136_);
if (v___x_137_ == 0)
{
v___y_127_ = v___x_125_;
goto v___jp_126_;
}
else
{
uint8_t v___x_138_; 
v___x_138_ = 0;
v___y_127_ = v___x_138_;
goto v___jp_126_;
}
}
v___jp_139_:
{
uint8_t v___x_140_; 
v___x_140_ = lean_uint32_dec_eq(v_ey_122_, v___x_109_);
if (v___x_140_ == 0)
{
goto v___jp_75_;
}
else
{
if (v___x_125_ == 0)
{
uint32_t v___x_141_; 
v___x_141_ = lp_competition_Submission_FastMul_mul(v___y_73_, v___y_74_);
return v___x_141_;
}
else
{
goto v___jp_75_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_512_, lean_object* v___y_513_){
_start:
{
uint32_t v___y_3533__boxed_514_; uint32_t v___y_3534__boxed_515_; uint32_t v_res_516_; lean_object* v_r_517_; 
v___y_3533__boxed_514_ = lean_unbox_uint32(v___y_512_);
lean_dec(v___y_512_);
v___y_3534__boxed_515_ = lean_unbox_uint32(v___y_513_);
lean_dec(v___y_513_);
v_res_516_ = lp_competition_main___lam__1(v___y_3533__boxed_514_, v___y_3534__boxed_515_);
v_r_517_ = lean_box_uint32(v_res_516_);
return v_r_517_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_518_, uint32_t v___y_519_){
_start:
{
uint8_t v___y_526_; uint8_t v___y_527_; uint32_t v___y_533_; uint32_t v___y_537_; uint32_t v___y_541_; uint32_t v___y_542_; uint32_t v___y_543_; uint32_t v___y_547_; uint32_t v___y_548_; uint32_t v___y_549_; uint32_t v___x_552_; uint32_t v___x_553_; uint32_t v___x_554_; uint32_t v___y_556_; uint32_t v___y_557_; uint32_t v___y_558_; uint32_t v___y_559_; uint32_t v_ex_565_; uint32_t v___x_566_; uint32_t v_ey_567_; uint32_t v___x_568_; uint32_t v___x_569_; uint8_t v___x_570_; uint8_t v___y_572_; 
v___x_552_ = 23;
v___x_553_ = lean_uint32_shift_right(v___y_518_, v___x_552_);
v___x_554_ = 255;
v_ex_565_ = lean_uint32_land(v___x_553_, v___x_554_);
v___x_566_ = lean_uint32_shift_right(v___y_519_, v___x_552_);
v_ey_567_ = lean_uint32_land(v___x_566_, v___x_554_);
v___x_568_ = lean_uint32_add(v_ex_565_, v_ey_567_);
v___x_569_ = 128;
v___x_570_ = lean_uint32_dec_lt(v___x_568_, v___x_569_);
if (v___x_570_ == 0)
{
uint8_t v___x_587_; 
v___x_587_ = lean_uint32_dec_eq(v_ex_565_, v___x_554_);
if (v___x_587_ == 0)
{
goto v___jp_584_;
}
else
{
if (v___x_570_ == 0)
{
uint32_t v___x_588_; 
v___x_588_ = lp_competition_Submission_FastMul_mul(v___y_518_, v___y_519_);
return v___x_588_;
}
else
{
goto v___jp_584_;
}
}
}
else
{
uint32_t v___x_589_; uint32_t v___x_590_; uint32_t v___x_591_; uint8_t v___y_593_; uint64_t v___y_594_; uint32_t v___y_595_; uint64_t v___y_596_; uint32_t v___y_605_; uint8_t v___y_606_; uint32_t v___y_607_; uint32_t v___y_608_; uint64_t v___y_611_; uint8_t v___y_612_; uint32_t v___y_613_; uint64_t v___y_614_; uint64_t v___y_615_; uint8_t v___y_625_; uint8_t v___y_626_; uint64_t v___y_627_; uint32_t v___y_628_; uint64_t v___y_629_; uint64_t v___y_630_; uint64_t v___y_637_; uint8_t v___y_638_; uint64_t v___y_639_; uint32_t v___y_640_; uint64_t v___y_641_; uint64_t v___y_647_; uint64_t v___y_648_; uint8_t v___y_649_; uint64_t v___y_650_; uint32_t v___y_651_; uint64_t v___y_652_; uint64_t v___y_707_; uint64_t v___y_708_; uint8_t v___y_709_; uint64_t v___y_710_; uint32_t v___y_711_; uint64_t v___y_712_; uint64_t v___y_713_; uint64_t v___y_719_; uint64_t v___y_720_; uint64_t v___y_721_; uint64_t v___y_722_; uint8_t v___y_723_; uint64_t v___y_724_; uint32_t v___y_725_; uint64_t v___y_726_; uint64_t v___y_727_; uint64_t v___y_732_; uint64_t v___y_733_; uint8_t v___y_734_; uint64_t v___y_735_; uint32_t v___y_736_; uint64_t v___y_737_; uint64_t v___y_738_; uint64_t v___y_743_; uint64_t v___y_744_; uint64_t v___y_745_; uint64_t v___y_746_; uint64_t v___y_747_; uint8_t v___y_748_; uint32_t v___y_749_; uint64_t v___y_750_; uint64_t v___y_751_; uint64_t v___y_756_; uint64_t v___y_757_; uint64_t v___y_758_; uint8_t v___y_759_; uint64_t v___y_760_; uint32_t v___y_761_; uint64_t v___y_762_; uint64_t v___y_767_; uint64_t v___y_768_; uint64_t v___y_769_; uint64_t v___y_770_; uint8_t v___y_771_; uint64_t v___y_772_; uint32_t v___y_773_; uint64_t v___y_774_; uint64_t v___y_775_; uint64_t v___y_780_; uint64_t v___y_781_; uint8_t v___y_782_; uint64_t v___y_783_; uint32_t v___y_784_; uint64_t v___y_785_; uint64_t v___y_786_; uint64_t v___y_791_; uint64_t v___y_792_; uint64_t v___y_793_; uint64_t v___y_794_; uint8_t v___y_795_; uint32_t v___y_796_; uint64_t v___y_797_; uint64_t v___y_798_; uint64_t v___y_799_; uint64_t v___y_804_; uint64_t v___y_805_; uint8_t v___y_806_; uint64_t v___y_807_; uint32_t v___y_808_; uint64_t v___y_809_; uint64_t v___y_810_; uint64_t v___y_815_; uint64_t v___y_816_; uint64_t v___y_817_; uint8_t v___y_818_; uint32_t v___y_819_; uint64_t v___y_820_; uint64_t v___y_821_; uint64_t v___y_825_; uint64_t v___y_826_; uint8_t v___y_827_; uint32_t v___y_828_; uint8_t v___y_836_; uint64_t v___y_837_; uint32_t v___y_838_; uint64_t v___y_839_; uint8_t v___y_848_; uint64_t v___y_849_; uint32_t v___y_850_; uint64_t v___y_851_; uint64_t v___y_852_; uint64_t v___y_853_; uint8_t v___y_886_; uint64_t v___y_887_; uint64_t v___y_888_; uint32_t v___y_889_; uint64_t v___y_890_; uint8_t v___y_897_; uint32_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_900_; uint8_t v___y_907_; uint32_t v___y_908_; uint32_t v___y_909_; uint64_t v___y_910_; uint8_t v___y_917_; uint8_t v___y_927_; uint8_t v___y_928_; uint8_t v___y_930_; uint8_t v___y_931_; uint8_t v___y_932_; uint8_t v___y_934_; uint8_t v___y_935_; uint8_t v___y_940_; uint8_t v___x_948_; 
v___x_589_ = 2147483647;
v___x_590_ = lean_uint32_land(v___y_518_, v___x_589_);
v___x_591_ = 0;
v___x_948_ = lean_uint32_dec_eq(v___x_590_, v___x_591_);
if (v___x_948_ == 0)
{
uint32_t v___x_949_; uint8_t v___x_950_; 
v___x_949_ = lean_uint32_land(v___y_519_, v___x_589_);
v___x_950_ = lean_uint32_dec_eq(v___x_949_, v___x_591_);
if (v___x_950_ == 0)
{
uint32_t v___x_951_; uint32_t v___x_952_; uint32_t v___x_953_; uint8_t v___x_954_; 
v___x_951_ = 4278190080;
v___x_952_ = 1;
v___x_953_ = lean_uint32_shift_left(v___y_518_, v___x_952_);
v___x_954_ = lean_uint32_dec_le(v___x_951_, v___x_953_);
if (v___x_954_ == 0)
{
uint32_t v___x_955_; uint8_t v___x_956_; 
v___x_955_ = lean_uint32_shift_left(v___y_519_, v___x_952_);
v___x_956_ = lean_uint32_dec_le(v___x_951_, v___x_955_);
v___y_940_ = v___x_956_;
goto v___jp_939_;
}
else
{
v___y_940_ = v___x_954_;
goto v___jp_939_;
}
}
else
{
goto v___jp_578_;
}
}
else
{
goto v___jp_578_;
}
v___jp_592_:
{
uint8_t v___x_597_; 
v___x_597_ = lean_uint64_dec_eq(v___y_596_, v___y_594_);
if (v___x_597_ == 0)
{
uint64_t v___x_598_; uint8_t v___x_599_; 
v___x_598_ = 8388608ULL;
v___x_599_ = lean_uint64_dec_eq(v___y_596_, v___x_598_);
if (v___x_599_ == 0)
{
uint32_t v___x_600_; 
v___x_600_ = lean_uint64_to_uint32(v___y_596_);
if (v___y_593_ == 0)
{
v___y_541_ = v___x_600_;
v___y_542_ = v___y_595_;
v___y_543_ = v___x_591_;
goto v___jp_540_;
}
else
{
uint32_t v___x_601_; 
v___x_601_ = 2147483648;
v___y_541_ = v___x_600_;
v___y_542_ = v___y_595_;
v___y_543_ = v___x_601_;
goto v___jp_540_;
}
}
else
{
if (v___y_593_ == 0)
{
v___y_537_ = v___x_591_;
goto v___jp_536_;
}
else
{
uint32_t v___x_602_; 
v___x_602_ = 2147483648;
v___y_537_ = v___x_602_;
goto v___jp_536_;
}
}
}
else
{
if (v___y_593_ == 0)
{
return v___x_591_;
}
else
{
uint32_t v___x_603_; 
v___x_603_ = 2147483648;
return v___x_603_;
}
}
}
v___jp_604_:
{
if (v___y_606_ == 0)
{
v___y_556_ = v___y_608_;
v___y_557_ = v___y_605_;
v___y_558_ = v___y_607_;
v___y_559_ = v___x_591_;
goto v___jp_555_;
}
else
{
uint32_t v___x_609_; 
v___x_609_ = 2147483648;
v___y_556_ = v___y_608_;
v___y_557_ = v___y_605_;
v___y_558_ = v___y_607_;
v___y_559_ = v___x_609_;
goto v___jp_555_;
}
}
v___jp_610_:
{
uint64_t v___x_616_; uint64_t v_encodedExponent_617_; uint32_t v___x_618_; uint64_t v___x_619_; uint8_t v___x_620_; 
v___x_616_ = 171ULL;
v_encodedExponent_617_ = lean_uint64_sub(v___y_614_, v___x_616_);
v___x_618_ = lean_uint64_to_uint32(v_encodedExponent_617_);
v___x_619_ = 8388608ULL;
v___x_620_ = lean_uint64_dec_lt(v___y_615_, v___x_619_);
if (v___x_620_ == 0)
{
uint64_t v___x_621_; uint32_t v___x_622_; 
v___x_621_ = lean_uint64_sub(v___y_615_, v___x_619_);
v___x_622_ = lean_uint64_to_uint32(v___x_621_);
v___y_605_ = v___x_618_;
v___y_606_ = v___y_612_;
v___y_607_ = v___y_613_;
v___y_608_ = v___x_622_;
goto v___jp_604_;
}
else
{
uint32_t v___x_623_; 
v___x_623_ = lean_uint64_to_uint32(v___y_611_);
v___y_605_ = v___x_618_;
v___y_606_ = v___y_612_;
v___y_607_ = v___y_613_;
v___y_608_ = v___x_623_;
goto v___jp_604_;
}
}
v___jp_624_:
{
uint64_t v___x_631_; uint8_t v___x_632_; 
v___x_631_ = 425ULL;
v___x_632_ = lean_uint64_dec_lt(v___x_631_, v___y_630_);
if (v___x_632_ == 0)
{
if (v___y_625_ == 0)
{
v___y_611_ = v___y_627_;
v___y_612_ = v___y_626_;
v___y_613_ = v___y_628_;
v___y_614_ = v___y_630_;
v___y_615_ = v___y_629_;
goto v___jp_610_;
}
else
{
uint64_t v___x_633_; 
v___x_633_ = 8388608ULL;
v___y_611_ = v___y_627_;
v___y_612_ = v___y_626_;
v___y_613_ = v___y_628_;
v___y_614_ = v___y_630_;
v___y_615_ = v___x_633_;
goto v___jp_610_;
}
}
else
{
if (v___y_626_ == 0)
{
uint32_t v___x_634_; 
v___x_634_ = 2139095040;
return v___x_634_;
}
else
{
uint32_t v___x_635_; 
v___x_635_ = 4286578688;
return v___x_635_;
}
}
}
v___jp_636_:
{
uint64_t v___x_642_; uint8_t v_carry_643_; 
v___x_642_ = 16777216ULL;
v_carry_643_ = lean_uint64_dec_eq(v___y_641_, v___x_642_);
if (v_carry_643_ == 0)
{
v___y_625_ = v_carry_643_;
v___y_626_ = v___y_638_;
v___y_627_ = v___y_637_;
v___y_628_ = v___y_640_;
v___y_629_ = v___y_641_;
v___y_630_ = v___y_639_;
goto v___jp_624_;
}
else
{
uint64_t v___x_644_; uint64_t v___x_645_; 
v___x_644_ = 1ULL;
v___x_645_ = lean_uint64_add(v___y_639_, v___x_644_);
v___y_625_ = v_carry_643_;
v___y_626_ = v___y_638_;
v___y_627_ = v___y_637_;
v___y_628_ = v___y_640_;
v___y_629_ = v___y_641_;
v___y_630_ = v___x_645_;
goto v___jp_624_;
}
}
v___jp_646_:
{
uint64_t v_position_653_; uint64_t v___x_654_; uint8_t v___x_655_; 
v_position_653_ = lean_uint64_add(v___y_652_, v___y_648_);
v___x_654_ = 172ULL;
v___x_655_ = lean_uint64_dec_lt(v_position_653_, v___x_654_);
if (v___x_655_ == 0)
{
uint64_t v___x_656_; uint8_t v___x_657_; 
v___x_656_ = 23ULL;
v___x_657_ = lean_uint64_dec_lt(v___y_652_, v___x_656_);
if (v___x_657_ == 0)
{
uint64_t v___x_658_; uint8_t v___x_659_; 
v___x_658_ = lean_uint64_sub(v___y_652_, v___x_656_);
v___x_659_ = lean_uint64_dec_eq(v___x_658_, v___y_650_);
if (v___x_659_ == 0)
{
uint64_t v___x_660_; uint8_t v___x_661_; 
v___x_660_ = 64ULL;
v___x_661_ = lean_uint64_dec_lt(v___x_658_, v___x_660_);
if (v___x_661_ == 0)
{
uint8_t v___x_662_; 
v___x_662_ = lean_uint64_dec_eq(v___x_658_, v___x_660_);
if (v___x_662_ == 0)
{
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v___y_650_;
goto v___jp_636_;
}
else
{
uint64_t v___x_663_; uint8_t v___x_664_; 
v___x_663_ = 9223372036854775808ULL;
v___x_664_ = lean_uint64_dec_lt(v___x_663_, v___y_647_);
if (v___x_664_ == 0)
{
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v___y_650_;
goto v___jp_636_;
}
else
{
uint64_t v___x_665_; 
v___x_665_ = 1ULL;
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v___x_665_;
goto v___jp_636_;
}
}
}
else
{
uint64_t v_quotient_666_; uint64_t v___x_667_; uint64_t v___x_668_; uint64_t v___x_669_; uint64_t v_remainder_670_; uint64_t v___x_671_; uint64_t v_half_672_; uint8_t v___x_673_; 
v_quotient_666_ = lean_uint64_shift_right(v___y_647_, v___x_658_);
v___x_667_ = 1ULL;
v___x_668_ = lean_uint64_shift_left(v___x_667_, v___x_658_);
v___x_669_ = lean_uint64_sub(v___x_668_, v___x_667_);
v_remainder_670_ = lean_uint64_land(v___y_647_, v___x_669_);
v___x_671_ = lean_uint64_sub(v___x_658_, v___x_667_);
v_half_672_ = lean_uint64_shift_left(v___x_667_, v___x_671_);
v___x_673_ = lean_uint64_dec_lt(v_remainder_670_, v_half_672_);
if (v___x_673_ == 0)
{
uint8_t v___x_674_; 
v___x_674_ = lean_uint64_dec_lt(v_half_672_, v_remainder_670_);
if (v___x_674_ == 0)
{
uint64_t v___x_675_; uint8_t v___x_676_; 
v___x_675_ = lean_uint64_land(v_quotient_666_, v___x_667_);
v___x_676_ = lean_uint64_dec_eq(v___x_675_, v___y_650_);
if (v___x_676_ == 0)
{
uint64_t v___x_677_; 
v___x_677_ = lean_uint64_add(v_quotient_666_, v___x_667_);
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v___x_677_;
goto v___jp_636_;
}
else
{
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v_quotient_666_;
goto v___jp_636_;
}
}
else
{
uint64_t v___x_678_; 
v___x_678_ = lean_uint64_add(v_quotient_666_, v___x_667_);
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v___x_678_;
goto v___jp_636_;
}
}
else
{
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v_quotient_666_;
goto v___jp_636_;
}
}
}
else
{
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v___y_647_;
goto v___jp_636_;
}
}
else
{
uint64_t v___x_679_; uint64_t v___x_680_; 
v___x_679_ = lean_uint64_sub(v___x_656_, v___y_652_);
v___x_680_ = lean_uint64_shift_left(v___y_647_, v___x_679_);
v___y_637_ = v___y_650_;
v___y_638_ = v___y_649_;
v___y_639_ = v_position_653_;
v___y_640_ = v___y_651_;
v___y_641_ = v___x_680_;
goto v___jp_636_;
}
}
else
{
uint64_t v___x_681_; uint8_t v___x_682_; 
v___x_681_ = 149ULL;
v___x_682_ = lean_uint64_dec_lt(v___y_648_, v___x_681_);
if (v___x_682_ == 0)
{
uint64_t v___x_683_; uint64_t v___x_684_; 
v___x_683_ = lean_uint64_sub(v___y_648_, v___x_681_);
v___x_684_ = lean_uint64_shift_left(v___y_647_, v___x_683_);
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v___x_684_;
goto v___jp_592_;
}
else
{
uint64_t v___x_685_; uint8_t v___x_686_; 
v___x_685_ = lean_uint64_sub(v___x_681_, v___y_648_);
v___x_686_ = lean_uint64_dec_eq(v___x_685_, v___y_650_);
if (v___x_686_ == 0)
{
uint64_t v___x_687_; uint8_t v___x_688_; 
v___x_687_ = 64ULL;
v___x_688_ = lean_uint64_dec_lt(v___x_685_, v___x_687_);
if (v___x_688_ == 0)
{
uint8_t v___x_689_; 
v___x_689_ = lean_uint64_dec_eq(v___x_685_, v___x_687_);
if (v___x_689_ == 0)
{
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v___y_650_;
goto v___jp_592_;
}
else
{
uint64_t v___x_690_; uint8_t v___x_691_; 
v___x_690_ = 9223372036854775808ULL;
v___x_691_ = lean_uint64_dec_lt(v___x_690_, v___y_647_);
if (v___x_691_ == 0)
{
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v___y_650_;
goto v___jp_592_;
}
else
{
uint64_t v___x_692_; 
v___x_692_ = 1ULL;
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v___x_692_;
goto v___jp_592_;
}
}
}
else
{
uint64_t v_quotient_693_; uint64_t v___x_694_; uint64_t v___x_695_; uint64_t v___x_696_; uint64_t v_remainder_697_; uint64_t v___x_698_; uint64_t v_half_699_; uint8_t v___x_700_; 
v_quotient_693_ = lean_uint64_shift_right(v___y_647_, v___x_685_);
v___x_694_ = 1ULL;
v___x_695_ = lean_uint64_shift_left(v___x_694_, v___x_685_);
v___x_696_ = lean_uint64_sub(v___x_695_, v___x_694_);
v_remainder_697_ = lean_uint64_land(v___y_647_, v___x_696_);
v___x_698_ = lean_uint64_sub(v___x_685_, v___x_694_);
v_half_699_ = lean_uint64_shift_left(v___x_694_, v___x_698_);
v___x_700_ = lean_uint64_dec_lt(v_remainder_697_, v_half_699_);
if (v___x_700_ == 0)
{
uint8_t v___x_701_; 
v___x_701_ = lean_uint64_dec_lt(v_half_699_, v_remainder_697_);
if (v___x_701_ == 0)
{
uint64_t v___x_702_; uint8_t v___x_703_; 
v___x_702_ = lean_uint64_land(v_quotient_693_, v___x_694_);
v___x_703_ = lean_uint64_dec_eq(v___x_702_, v___y_650_);
if (v___x_703_ == 0)
{
uint64_t v___x_704_; 
v___x_704_ = lean_uint64_add(v_quotient_693_, v___x_694_);
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v___x_704_;
goto v___jp_592_;
}
else
{
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v_quotient_693_;
goto v___jp_592_;
}
}
else
{
uint64_t v___x_705_; 
v___x_705_ = lean_uint64_add(v_quotient_693_, v___x_694_);
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v___x_705_;
goto v___jp_592_;
}
}
else
{
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v_quotient_693_;
goto v___jp_592_;
}
}
}
else
{
v___y_593_ = v___y_649_;
v___y_594_ = v___y_650_;
v___y_595_ = v___y_651_;
v___y_596_ = v___y_647_;
goto v___jp_592_;
}
}
}
}
v___jp_706_:
{
uint64_t v___x_714_; uint64_t v___x_715_; uint8_t v___x_716_; 
v___x_714_ = 1ULL;
v___x_715_ = lean_uint64_shift_right(v___y_712_, v___x_714_);
v___x_716_ = lean_uint64_dec_eq(v___x_715_, v___y_710_);
if (v___x_716_ == 0)
{
uint64_t v___x_717_; 
v___x_717_ = lean_uint64_add(v___y_713_, v___x_714_);
v___y_647_ = v___y_707_;
v___y_648_ = v___y_708_;
v___y_649_ = v___y_709_;
v___y_650_ = v___y_710_;
v___y_651_ = v___y_711_;
v___y_652_ = v___x_717_;
goto v___jp_646_;
}
else
{
v___y_647_ = v___y_707_;
v___y_648_ = v___y_708_;
v___y_649_ = v___y_709_;
v___y_650_ = v___y_710_;
v___y_651_ = v___y_711_;
v___y_652_ = v___y_713_;
goto v___jp_646_;
}
}
v___jp_718_:
{
uint64_t v___x_728_; uint8_t v___x_729_; 
v___x_728_ = lean_uint64_shift_right(v___y_726_, v___y_724_);
v___x_729_ = lean_uint64_dec_eq(v___x_728_, v___y_722_);
if (v___x_729_ == 0)
{
uint64_t v___x_730_; 
v___x_730_ = lean_uint64_add(v___y_720_, v___y_724_);
v___y_707_ = v___y_719_;
v___y_708_ = v___y_721_;
v___y_709_ = v___y_723_;
v___y_710_ = v___y_722_;
v___y_711_ = v___y_725_;
v___y_712_ = v___y_727_;
v___y_713_ = v___x_730_;
goto v___jp_706_;
}
else
{
v___y_707_ = v___y_719_;
v___y_708_ = v___y_721_;
v___y_709_ = v___y_723_;
v___y_710_ = v___y_722_;
v___y_711_ = v___y_725_;
v___y_712_ = v___y_727_;
v___y_713_ = v___y_720_;
goto v___jp_706_;
}
}
v___jp_731_:
{
uint64_t v___x_739_; uint64_t v___x_740_; uint8_t v___x_741_; 
v___x_739_ = 2ULL;
v___x_740_ = lean_uint64_shift_right(v___y_737_, v___x_739_);
v___x_741_ = lean_uint64_dec_eq(v___x_740_, v___y_735_);
if (v___x_741_ == 0)
{
v___y_719_ = v___y_732_;
v___y_720_ = v___y_738_;
v___y_721_ = v___y_733_;
v___y_722_ = v___y_735_;
v___y_723_ = v___y_734_;
v___y_724_ = v___x_739_;
v___y_725_ = v___y_736_;
v___y_726_ = v___y_737_;
v___y_727_ = v___x_740_;
goto v___jp_718_;
}
else
{
v___y_719_ = v___y_732_;
v___y_720_ = v___y_738_;
v___y_721_ = v___y_733_;
v___y_722_ = v___y_735_;
v___y_723_ = v___y_734_;
v___y_724_ = v___x_739_;
v___y_725_ = v___y_736_;
v___y_726_ = v___y_737_;
v___y_727_ = v___y_737_;
goto v___jp_718_;
}
}
v___jp_742_:
{
uint64_t v___x_752_; uint8_t v___x_753_; 
v___x_752_ = lean_uint64_shift_right(v___y_743_, v___y_746_);
v___x_753_ = lean_uint64_dec_eq(v___x_752_, v___y_747_);
if (v___x_753_ == 0)
{
uint64_t v___x_754_; 
v___x_754_ = lean_uint64_add(v___y_750_, v___y_746_);
v___y_732_ = v___y_744_;
v___y_733_ = v___y_745_;
v___y_734_ = v___y_748_;
v___y_735_ = v___y_747_;
v___y_736_ = v___y_749_;
v___y_737_ = v___y_751_;
v___y_738_ = v___x_754_;
goto v___jp_731_;
}
else
{
v___y_732_ = v___y_744_;
v___y_733_ = v___y_745_;
v___y_734_ = v___y_748_;
v___y_735_ = v___y_747_;
v___y_736_ = v___y_749_;
v___y_737_ = v___y_751_;
v___y_738_ = v___y_750_;
goto v___jp_731_;
}
}
v___jp_755_:
{
uint64_t v___x_763_; uint64_t v___x_764_; uint8_t v___x_765_; 
v___x_763_ = 4ULL;
v___x_764_ = lean_uint64_shift_right(v___y_757_, v___x_763_);
v___x_765_ = lean_uint64_dec_eq(v___x_764_, v___y_760_);
if (v___x_765_ == 0)
{
v___y_743_ = v___y_757_;
v___y_744_ = v___y_756_;
v___y_745_ = v___y_758_;
v___y_746_ = v___x_763_;
v___y_747_ = v___y_760_;
v___y_748_ = v___y_759_;
v___y_749_ = v___y_761_;
v___y_750_ = v___y_762_;
v___y_751_ = v___x_764_;
goto v___jp_742_;
}
else
{
v___y_743_ = v___y_757_;
v___y_744_ = v___y_756_;
v___y_745_ = v___y_758_;
v___y_746_ = v___x_763_;
v___y_747_ = v___y_760_;
v___y_748_ = v___y_759_;
v___y_749_ = v___y_761_;
v___y_750_ = v___y_762_;
v___y_751_ = v___y_757_;
goto v___jp_742_;
}
}
v___jp_766_:
{
uint64_t v___x_776_; uint8_t v___x_777_; 
v___x_776_ = lean_uint64_shift_right(v___y_774_, v___y_768_);
v___x_777_ = lean_uint64_dec_eq(v___x_776_, v___y_770_);
if (v___x_777_ == 0)
{
uint64_t v___x_778_; 
v___x_778_ = lean_uint64_add(v___y_772_, v___y_768_);
v___y_756_ = v___y_767_;
v___y_757_ = v___y_775_;
v___y_758_ = v___y_769_;
v___y_759_ = v___y_771_;
v___y_760_ = v___y_770_;
v___y_761_ = v___y_773_;
v___y_762_ = v___x_778_;
goto v___jp_755_;
}
else
{
v___y_756_ = v___y_767_;
v___y_757_ = v___y_775_;
v___y_758_ = v___y_769_;
v___y_759_ = v___y_771_;
v___y_760_ = v___y_770_;
v___y_761_ = v___y_773_;
v___y_762_ = v___y_772_;
goto v___jp_755_;
}
}
v___jp_779_:
{
uint64_t v___x_787_; uint64_t v___x_788_; uint8_t v___x_789_; 
v___x_787_ = 8ULL;
v___x_788_ = lean_uint64_shift_right(v___y_785_, v___x_787_);
v___x_789_ = lean_uint64_dec_eq(v___x_788_, v___y_783_);
if (v___x_789_ == 0)
{
v___y_767_ = v___y_780_;
v___y_768_ = v___x_787_;
v___y_769_ = v___y_781_;
v___y_770_ = v___y_783_;
v___y_771_ = v___y_782_;
v___y_772_ = v___y_786_;
v___y_773_ = v___y_784_;
v___y_774_ = v___y_785_;
v___y_775_ = v___x_788_;
goto v___jp_766_;
}
else
{
v___y_767_ = v___y_780_;
v___y_768_ = v___x_787_;
v___y_769_ = v___y_781_;
v___y_770_ = v___y_783_;
v___y_771_ = v___y_782_;
v___y_772_ = v___y_786_;
v___y_773_ = v___y_784_;
v___y_774_ = v___y_785_;
v___y_775_ = v___y_785_;
goto v___jp_766_;
}
}
v___jp_790_:
{
uint64_t v___x_800_; uint8_t v___x_801_; 
v___x_800_ = lean_uint64_shift_right(v___y_797_, v___y_791_);
v___x_801_ = lean_uint64_dec_eq(v___x_800_, v___y_794_);
if (v___x_801_ == 0)
{
uint64_t v___x_802_; 
v___x_802_ = lean_uint64_add(v___y_798_, v___y_791_);
v___y_780_ = v___y_792_;
v___y_781_ = v___y_793_;
v___y_782_ = v___y_795_;
v___y_783_ = v___y_794_;
v___y_784_ = v___y_796_;
v___y_785_ = v___y_799_;
v___y_786_ = v___x_802_;
goto v___jp_779_;
}
else
{
v___y_780_ = v___y_792_;
v___y_781_ = v___y_793_;
v___y_782_ = v___y_795_;
v___y_783_ = v___y_794_;
v___y_784_ = v___y_796_;
v___y_785_ = v___y_799_;
v___y_786_ = v___y_798_;
goto v___jp_779_;
}
}
v___jp_803_:
{
uint64_t v___x_811_; uint64_t v___x_812_; uint8_t v___x_813_; 
v___x_811_ = 16ULL;
v___x_812_ = lean_uint64_shift_right(v___y_809_, v___x_811_);
v___x_813_ = lean_uint64_dec_eq(v___x_812_, v___y_807_);
if (v___x_813_ == 0)
{
v___y_791_ = v___x_811_;
v___y_792_ = v___y_804_;
v___y_793_ = v___y_805_;
v___y_794_ = v___y_807_;
v___y_795_ = v___y_806_;
v___y_796_ = v___y_808_;
v___y_797_ = v___y_809_;
v___y_798_ = v___y_810_;
v___y_799_ = v___x_812_;
goto v___jp_790_;
}
else
{
v___y_791_ = v___x_811_;
v___y_792_ = v___y_804_;
v___y_793_ = v___y_805_;
v___y_794_ = v___y_807_;
v___y_795_ = v___y_806_;
v___y_796_ = v___y_808_;
v___y_797_ = v___y_809_;
v___y_798_ = v___y_810_;
v___y_799_ = v___y_809_;
goto v___jp_790_;
}
}
v___jp_814_:
{
uint64_t v___x_822_; uint8_t v___x_823_; 
v___x_822_ = lean_uint64_shift_right(v___y_815_, v___y_820_);
v___x_823_ = lean_uint64_dec_eq(v___x_822_, v___y_817_);
if (v___x_823_ == 0)
{
v___y_804_ = v___y_815_;
v___y_805_ = v___y_816_;
v___y_806_ = v___y_818_;
v___y_807_ = v___y_817_;
v___y_808_ = v___y_819_;
v___y_809_ = v___y_821_;
v___y_810_ = v___y_820_;
goto v___jp_803_;
}
else
{
v___y_804_ = v___y_815_;
v___y_805_ = v___y_816_;
v___y_806_ = v___y_818_;
v___y_807_ = v___y_817_;
v___y_808_ = v___y_819_;
v___y_809_ = v___y_821_;
v___y_810_ = v___y_817_;
goto v___jp_803_;
}
}
v___jp_824_:
{
uint64_t v___x_829_; uint8_t v___x_830_; 
v___x_829_ = 0ULL;
v___x_830_ = lean_uint64_dec_eq(v___y_825_, v___x_829_);
if (v___x_830_ == 0)
{
uint64_t v___x_831_; uint64_t v___x_832_; uint8_t v___x_833_; 
v___x_831_ = 32ULL;
v___x_832_ = lean_uint64_shift_right(v___y_825_, v___x_831_);
v___x_833_ = lean_uint64_dec_eq(v___x_832_, v___x_829_);
if (v___x_833_ == 0)
{
v___y_815_ = v___y_825_;
v___y_816_ = v___y_826_;
v___y_817_ = v___x_829_;
v___y_818_ = v___y_827_;
v___y_819_ = v___y_828_;
v___y_820_ = v___x_831_;
v___y_821_ = v___x_832_;
goto v___jp_814_;
}
else
{
v___y_815_ = v___y_825_;
v___y_816_ = v___y_826_;
v___y_817_ = v___x_829_;
v___y_818_ = v___y_827_;
v___y_819_ = v___y_828_;
v___y_820_ = v___x_831_;
v___y_821_ = v___y_825_;
goto v___jp_814_;
}
}
else
{
if (v___y_827_ == 0)
{
return v___x_591_;
}
else
{
uint32_t v___x_834_; 
v___x_834_ = 2147483648;
return v___x_834_;
}
}
}
v___jp_835_:
{
uint8_t v___x_840_; 
v___x_840_ = lean_uint64_dec_eq(v___y_839_, v___y_837_);
if (v___x_840_ == 0)
{
uint64_t v___x_841_; uint8_t v___x_842_; 
v___x_841_ = 8388608ULL;
v___x_842_ = lean_uint64_dec_eq(v___y_839_, v___x_841_);
if (v___x_842_ == 0)
{
uint32_t v___x_843_; 
v___x_843_ = lean_uint64_to_uint32(v___y_839_);
if (v___y_836_ == 0)
{
v___y_547_ = v___y_838_;
v___y_548_ = v___x_843_;
v___y_549_ = v___x_591_;
goto v___jp_546_;
}
else
{
uint32_t v___x_844_; 
v___x_844_ = 2147483648;
v___y_547_ = v___y_838_;
v___y_548_ = v___x_843_;
v___y_549_ = v___x_844_;
goto v___jp_546_;
}
}
else
{
if (v___y_836_ == 0)
{
v___y_533_ = v___x_591_;
goto v___jp_532_;
}
else
{
uint32_t v___x_845_; 
v___x_845_ = 2147483648;
v___y_533_ = v___x_845_;
goto v___jp_532_;
}
}
}
else
{
if (v___y_836_ == 0)
{
return v___x_591_;
}
else
{
uint32_t v___x_846_; 
v___x_846_ = 2147483648;
return v___x_846_;
}
}
}
v___jp_847_:
{
uint64_t v___x_854_; uint64_t v___x_855_; uint64_t v___x_856_; uint8_t v___x_857_; 
v___x_854_ = lean_uint64_mul(v___y_851_, v___y_849_);
v___x_855_ = lean_uint64_add(v___y_852_, v___y_853_);
v___x_856_ = 281474976710656ULL;
v___x_857_ = lean_uint64_dec_lt(v___x_854_, v___x_856_);
if (v___x_857_ == 0)
{
v___y_825_ = v___x_854_;
v___y_826_ = v___x_855_;
v___y_827_ = v___y_848_;
v___y_828_ = v___y_850_;
goto v___jp_824_;
}
else
{
uint64_t v___x_858_; uint8_t v___x_859_; 
v___x_858_ = 123ULL;
v___x_859_ = lean_uint64_dec_le(v___x_855_, v___x_858_);
if (v___x_859_ == 0)
{
v___y_825_ = v___x_854_;
v___y_826_ = v___x_855_;
v___y_827_ = v___y_848_;
v___y_828_ = v___y_850_;
goto v___jp_824_;
}
else
{
uint64_t v___x_860_; uint8_t v___x_861_; 
v___x_860_ = 0ULL;
v___x_861_ = lean_uint64_dec_eq(v___x_854_, v___x_860_);
if (v___x_861_ == 0)
{
uint64_t v___x_862_; uint64_t v___x_863_; uint8_t v___x_864_; 
v___x_862_ = 149ULL;
v___x_863_ = lean_uint64_sub(v___x_862_, v___x_855_);
v___x_864_ = lean_uint64_dec_eq(v___x_863_, v___x_860_);
if (v___x_864_ == 0)
{
uint64_t v___x_865_; uint8_t v___x_866_; 
v___x_865_ = 64ULL;
v___x_866_ = lean_uint64_dec_lt(v___x_863_, v___x_865_);
if (v___x_866_ == 0)
{
uint8_t v___x_867_; 
v___x_867_ = lean_uint64_dec_eq(v___x_863_, v___x_865_);
if (v___x_867_ == 0)
{
v___y_836_ = v___y_848_;
v___y_837_ = v___x_860_;
v___y_838_ = v___y_850_;
v___y_839_ = v___x_860_;
goto v___jp_835_;
}
else
{
uint64_t v___x_868_; uint8_t v___x_869_; 
v___x_868_ = 9223372036854775808ULL;
v___x_869_ = lean_uint64_dec_lt(v___x_868_, v___x_854_);
if (v___x_869_ == 0)
{
v___y_836_ = v___y_848_;
v___y_837_ = v___x_860_;
v___y_838_ = v___y_850_;
v___y_839_ = v___x_860_;
goto v___jp_835_;
}
else
{
uint64_t v___x_870_; 
v___x_870_ = 1ULL;
v___y_836_ = v___y_848_;
v___y_837_ = v___x_860_;
v___y_838_ = v___y_850_;
v___y_839_ = v___x_870_;
goto v___jp_835_;
}
}
}
else
{
uint64_t v_quotient_871_; uint64_t v___x_872_; uint64_t v___x_873_; uint64_t v___x_874_; uint64_t v_remainder_875_; uint64_t v___x_876_; uint64_t v_half_877_; uint8_t v___x_878_; 
v_quotient_871_ = lean_uint64_shift_right(v___x_854_, v___x_863_);
v___x_872_ = 1ULL;
v___x_873_ = lean_uint64_shift_left(v___x_872_, v___x_863_);
v___x_874_ = lean_uint64_sub(v___x_873_, v___x_872_);
v_remainder_875_ = lean_uint64_land(v___x_854_, v___x_874_);
v___x_876_ = lean_uint64_sub(v___x_863_, v___x_872_);
v_half_877_ = lean_uint64_shift_left(v___x_872_, v___x_876_);
v___x_878_ = lean_uint64_dec_lt(v_remainder_875_, v_half_877_);
if (v___x_878_ == 0)
{
uint8_t v___x_879_; 
v___x_879_ = lean_uint64_dec_lt(v_half_877_, v_remainder_875_);
if (v___x_879_ == 0)
{
uint64_t v___x_880_; uint8_t v___x_881_; 
v___x_880_ = lean_uint64_land(v_quotient_871_, v___x_872_);
v___x_881_ = lean_uint64_dec_eq(v___x_880_, v___x_860_);
if (v___x_881_ == 0)
{
uint64_t v___x_882_; 
v___x_882_ = lean_uint64_add(v_quotient_871_, v___x_872_);
v___y_836_ = v___y_848_;
v___y_837_ = v___x_860_;
v___y_838_ = v___y_850_;
v___y_839_ = v___x_882_;
goto v___jp_835_;
}
else
{
v___y_836_ = v___y_848_;
v___y_837_ = v___x_860_;
v___y_838_ = v___y_850_;
v___y_839_ = v_quotient_871_;
goto v___jp_835_;
}
}
else
{
uint64_t v___x_883_; 
v___x_883_ = lean_uint64_add(v_quotient_871_, v___x_872_);
v___y_836_ = v___y_848_;
v___y_837_ = v___x_860_;
v___y_838_ = v___y_850_;
v___y_839_ = v___x_883_;
goto v___jp_835_;
}
}
else
{
v___y_836_ = v___y_848_;
v___y_837_ = v___x_860_;
v___y_838_ = v___y_850_;
v___y_839_ = v_quotient_871_;
goto v___jp_835_;
}
}
}
else
{
v___y_836_ = v___y_848_;
v___y_837_ = v___x_860_;
v___y_838_ = v___y_850_;
v___y_839_ = v___x_854_;
goto v___jp_835_;
}
}
else
{
if (v___y_848_ == 0)
{
return v___x_591_;
}
else
{
uint32_t v___x_884_; 
v___x_884_ = 2147483648;
return v___x_884_;
}
}
}
}
}
v___jp_885_:
{
uint64_t v___x_891_; uint64_t v___x_892_; uint8_t v___x_893_; 
v___x_891_ = lean_uint32_to_uint64(v_ey_567_);
v___x_892_ = 0ULL;
v___x_893_ = lean_uint64_dec_eq(v___x_891_, v___x_892_);
if (v___x_893_ == 0)
{
uint64_t v___x_894_; uint64_t v___x_895_; 
v___x_894_ = 1ULL;
v___x_895_ = lean_uint64_sub(v___x_891_, v___x_894_);
v___y_848_ = v___y_886_;
v___y_849_ = v___y_887_;
v___y_850_ = v___y_889_;
v___y_851_ = v___y_888_;
v___y_852_ = v___y_890_;
v___y_853_ = v___x_895_;
goto v___jp_847_;
}
else
{
v___y_848_ = v___y_886_;
v___y_849_ = v___y_887_;
v___y_850_ = v___y_889_;
v___y_851_ = v___y_888_;
v___y_852_ = v___y_890_;
v___y_853_ = v___x_892_;
goto v___jp_847_;
}
}
v___jp_896_:
{
uint64_t v___x_901_; uint64_t v___x_902_; uint8_t v___x_903_; 
v___x_901_ = lean_uint32_to_uint64(v_ex_565_);
v___x_902_ = 0ULL;
v___x_903_ = lean_uint64_dec_eq(v___x_901_, v___x_902_);
if (v___x_903_ == 0)
{
uint64_t v___x_904_; uint64_t v___x_905_; 
v___x_904_ = 1ULL;
v___x_905_ = lean_uint64_sub(v___x_901_, v___x_904_);
v___y_886_ = v___y_897_;
v___y_887_ = v___y_900_;
v___y_888_ = v___y_899_;
v___y_889_ = v___y_898_;
v___y_890_ = v___x_905_;
goto v___jp_885_;
}
else
{
v___y_886_ = v___y_897_;
v___y_887_ = v___y_900_;
v___y_888_ = v___y_899_;
v___y_889_ = v___y_898_;
v___y_890_ = v___x_902_;
goto v___jp_885_;
}
}
v___jp_906_:
{
uint8_t v___x_911_; 
v___x_911_ = lean_uint32_dec_eq(v_ey_567_, v___x_591_);
if (v___x_911_ == 0)
{
uint64_t v___x_912_; uint64_t v___x_913_; uint64_t v___x_914_; 
v___x_912_ = lean_uint32_to_uint64(v___y_909_);
v___x_913_ = 8388608ULL;
v___x_914_ = lean_uint64_lor(v___x_912_, v___x_913_);
v___y_897_ = v___y_907_;
v___y_898_ = v___y_908_;
v___y_899_ = v___y_910_;
v___y_900_ = v___x_914_;
goto v___jp_896_;
}
else
{
uint64_t v___x_915_; 
v___x_915_ = lean_uint32_to_uint64(v___y_909_);
v___y_897_ = v___y_907_;
v___y_898_ = v___y_908_;
v___y_899_ = v___y_910_;
v___y_900_ = v___x_915_;
goto v___jp_896_;
}
}
v___jp_916_:
{
uint32_t v___x_918_; uint32_t v_xFraction_919_; uint32_t v_yFraction_920_; uint8_t v___x_921_; 
v___x_918_ = 8388607;
v_xFraction_919_ = lean_uint32_land(v___y_518_, v___x_918_);
v_yFraction_920_ = lean_uint32_land(v___y_519_, v___x_918_);
v___x_921_ = lean_uint32_dec_eq(v_ex_565_, v___x_591_);
if (v___x_921_ == 0)
{
uint64_t v___x_922_; uint64_t v___x_923_; uint64_t v___x_924_; 
v___x_922_ = lean_uint32_to_uint64(v_xFraction_919_);
v___x_923_ = 8388608ULL;
v___x_924_ = lean_uint64_lor(v___x_922_, v___x_923_);
v___y_907_ = v___y_917_;
v___y_908_ = v___x_918_;
v___y_909_ = v_yFraction_920_;
v___y_910_ = v___x_924_;
goto v___jp_906_;
}
else
{
uint64_t v___x_925_; 
v___x_925_ = lean_uint32_to_uint64(v_xFraction_919_);
v___y_907_ = v___y_917_;
v___y_908_ = v___x_918_;
v___y_909_ = v_yFraction_920_;
v___y_910_ = v___x_925_;
goto v___jp_906_;
}
}
v___jp_926_:
{
if (v___y_928_ == 0)
{
v___y_917_ = v___x_570_;
goto v___jp_916_;
}
else
{
v___y_917_ = v___y_927_;
goto v___jp_916_;
}
}
v___jp_929_:
{
if (v___y_930_ == 0)
{
if (v___y_932_ == 0)
{
v___y_927_ = v___y_931_;
v___y_928_ = v___x_570_;
goto v___jp_926_;
}
else
{
v___y_917_ = v___x_570_;
goto v___jp_916_;
}
}
else
{
v___y_927_ = v___y_931_;
v___y_928_ = v___y_932_;
goto v___jp_926_;
}
}
v___jp_933_:
{
uint32_t v___x_936_; uint32_t v___x_937_; uint8_t v___x_938_; 
v___x_936_ = 2147483648;
v___x_937_ = lean_uint32_land(v___y_519_, v___x_936_);
v___x_938_ = lean_uint32_dec_eq(v___x_937_, v___x_591_);
if (v___x_938_ == 0)
{
v___y_930_ = v___y_935_;
v___y_931_ = v___y_934_;
v___y_932_ = v___x_570_;
goto v___jp_929_;
}
else
{
v___y_930_ = v___y_935_;
v___y_931_ = v___y_934_;
v___y_932_ = v___y_934_;
goto v___jp_929_;
}
}
v___jp_939_:
{
if (v___y_940_ == 0)
{
uint32_t v___x_941_; uint32_t v___x_942_; uint8_t v___x_943_; 
v___x_941_ = 2147483648;
v___x_942_ = lean_uint32_land(v___y_518_, v___x_941_);
v___x_943_ = lean_uint32_dec_eq(v___x_942_, v___x_591_);
if (v___x_943_ == 0)
{
v___y_934_ = v___y_940_;
v___y_935_ = v___x_570_;
goto v___jp_933_;
}
else
{
v___y_934_ = v___y_940_;
v___y_935_ = v___y_940_;
goto v___jp_933_;
}
}
else
{
lean_object* v___x_944_; lean_object* v___x_945_; lean_object* v___x_946_; uint32_t v___x_947_; 
v___x_944_ = lean_uint32_to_nat(v___y_518_);
v___x_945_ = lean_uint32_to_nat(v___y_519_);
v___x_946_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_944_, v___x_945_);
v___x_947_ = lean_uint32_of_nat(v___x_946_);
lean_dec(v___x_946_);
return v___x_947_;
}
}
}
v___jp_520_:
{
float v___x_521_; float v___x_522_; float v___x_523_; uint32_t v___x_524_; 
v___x_521_ = lean_float32_of_bits(v___y_518_);
v___x_522_ = lean_float32_of_bits(v___y_519_);
v___x_523_ = lean_float32_mul(v___x_521_, v___x_522_);
v___x_524_ = lean_float32_to_bits(v___x_523_);
return v___x_524_;
}
v___jp_525_:
{
if (v___y_526_ == 0)
{
if (v___y_527_ == 0)
{
uint32_t v___x_528_; 
v___x_528_ = 0;
return v___x_528_;
}
else
{
uint32_t v___x_529_; 
v___x_529_ = 2147483648;
return v___x_529_;
}
}
else
{
if (v___y_527_ == 0)
{
uint32_t v___x_530_; 
v___x_530_ = 2147483648;
return v___x_530_;
}
else
{
uint32_t v___x_531_; 
v___x_531_ = 0;
return v___x_531_;
}
}
}
v___jp_532_:
{
uint32_t v___x_534_; uint32_t v___x_535_; 
v___x_534_ = 8388608;
v___x_535_ = lean_uint32_lor(v___y_533_, v___x_534_);
return v___x_535_;
}
v___jp_536_:
{
uint32_t v___x_538_; uint32_t v___x_539_; 
v___x_538_ = 8388608;
v___x_539_ = lean_uint32_lor(v___y_537_, v___x_538_);
return v___x_539_;
}
v___jp_540_:
{
uint32_t v___x_544_; uint32_t v___x_545_; 
v___x_544_ = lean_uint32_land(v___y_541_, v___y_542_);
v___x_545_ = lean_uint32_lor(v___y_543_, v___x_544_);
return v___x_545_;
}
v___jp_546_:
{
uint32_t v___x_550_; uint32_t v___x_551_; 
v___x_550_ = lean_uint32_land(v___y_548_, v___y_547_);
v___x_551_ = lean_uint32_lor(v___y_549_, v___x_550_);
return v___x_551_;
}
v___jp_555_:
{
uint32_t v___x_560_; uint32_t v___x_561_; uint32_t v___x_562_; uint32_t v___x_563_; uint32_t v___x_564_; 
v___x_560_ = lean_uint32_land(v___y_557_, v___x_554_);
v___x_561_ = lean_uint32_shift_left(v___x_560_, v___x_552_);
v___x_562_ = lean_uint32_lor(v___y_559_, v___x_561_);
v___x_563_ = lean_uint32_land(v___y_556_, v___y_558_);
v___x_564_ = lean_uint32_lor(v___x_562_, v___x_563_);
return v___x_564_;
}
v___jp_571_:
{
uint32_t v___x_573_; uint32_t v___x_574_; uint32_t v___x_575_; uint8_t v___x_576_; 
v___x_573_ = 2147483648;
v___x_574_ = lean_uint32_land(v___y_519_, v___x_573_);
v___x_575_ = 0;
v___x_576_ = lean_uint32_dec_eq(v___x_574_, v___x_575_);
if (v___x_576_ == 0)
{
v___y_526_ = v___y_572_;
v___y_527_ = v___x_570_;
goto v___jp_525_;
}
else
{
uint8_t v___x_577_; 
v___x_577_ = 0;
v___y_526_ = v___y_572_;
v___y_527_ = v___x_577_;
goto v___jp_525_;
}
}
v___jp_578_:
{
uint32_t v___x_579_; uint32_t v___x_580_; uint32_t v___x_581_; uint8_t v___x_582_; 
v___x_579_ = 2147483648;
v___x_580_ = lean_uint32_land(v___y_518_, v___x_579_);
v___x_581_ = 0;
v___x_582_ = lean_uint32_dec_eq(v___x_580_, v___x_581_);
if (v___x_582_ == 0)
{
v___y_572_ = v___x_570_;
goto v___jp_571_;
}
else
{
uint8_t v___x_583_; 
v___x_583_ = 0;
v___y_572_ = v___x_583_;
goto v___jp_571_;
}
}
v___jp_584_:
{
uint8_t v___x_585_; 
v___x_585_ = lean_uint32_dec_eq(v_ey_567_, v___x_554_);
if (v___x_585_ == 0)
{
goto v___jp_520_;
}
else
{
if (v___x_570_ == 0)
{
uint32_t v___x_586_; 
v___x_586_ = lp_competition_Submission_FastMul_mul(v___y_518_, v___y_519_);
return v___x_586_;
}
else
{
goto v___jp_520_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_957_, lean_object* v___y_958_){
_start:
{
uint32_t v___y_4381__boxed_959_; uint32_t v___y_4382__boxed_960_; uint32_t v_res_961_; lean_object* v_r_962_; 
v___y_4381__boxed_959_ = lean_unbox_uint32(v___y_957_);
lean_dec(v___y_957_);
v___y_4382__boxed_960_ = lean_unbox_uint32(v___y_958_);
lean_dec(v___y_958_);
v_res_961_ = lp_competition_main___lam__3(v___y_4381__boxed_959_, v___y_4382__boxed_960_);
v_r_962_ = lean_box_uint32(v_res_961_);
return v_r_962_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_970_; lean_object* v___x_971_; 
v___x_970_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_971_ = lean_io_getenv(v___x_970_);
if (lean_obj_tag(v___x_971_) == 0)
{
lean_object* v___f_972_; lean_object* v___f_973_; lean_object* v___x_974_; lean_object* v___x_975_; lean_object* v___x_976_; 
v___f_972_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_973_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_974_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_975_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_976_ = lp_competition_Bench_runFull(v___f_972_, v___f_973_, v___x_974_, v___x_975_);
return v___x_976_;
}
else
{
lean_object* v___f_977_; lean_object* v___f_978_; lean_object* v___x_979_; lean_object* v___x_980_; lean_object* v___x_981_; 
lean_dec_ref_known(v___x_971_, 1);
v___f_977_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_978_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_979_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_980_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_981_ = lp_competition_Bench_Suite_run(v___f_977_, v___f_978_, v___x_979_, v___x_980_);
return v___x_981_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_982_){
_start:
{
lean_object* v_res_983_; 
v_res_983_ = _lean_main();
return v_res_983_;
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
