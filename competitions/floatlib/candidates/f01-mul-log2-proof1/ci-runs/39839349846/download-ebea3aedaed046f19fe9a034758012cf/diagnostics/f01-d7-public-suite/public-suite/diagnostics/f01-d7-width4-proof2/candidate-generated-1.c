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
uint32_t v___y_3295__boxed_69_; uint32_t v___y_3296__boxed_70_; uint32_t v_res_71_; lean_object* v_r_72_; 
v___y_3295__boxed_69_ = lean_unbox_uint32(v___y_67_);
lean_dec(v___y_67_);
v___y_3296__boxed_70_ = lean_unbox_uint32(v___y_68_);
lean_dec(v___y_68_);
v_res_71_ = lp_competition_main___lam__0(v___y_3295__boxed_69_, v___y_3296__boxed_70_);
v_r_72_ = lean_box_uint32(v_res_71_);
return v_r_72_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_73_, uint32_t v___y_74_){
_start:
{
uint32_t v___y_81_; uint32_t v___y_82_; uint32_t v___y_83_; uint32_t v___y_87_; uint32_t v___y_88_; uint32_t v___y_89_; uint32_t v___y_93_; uint64_t v___y_97_; uint32_t v___y_98_; uint8_t v___y_99_; uint64_t v___y_100_; uint32_t v___y_112_; uint64_t v___y_116_; uint32_t v___y_117_; uint8_t v___y_118_; uint64_t v___y_119_; uint32_t v___x_130_; uint32_t v___x_131_; uint32_t v___x_132_; uint32_t v___y_134_; uint32_t v___y_135_; uint32_t v___y_136_; uint32_t v___y_137_; uint32_t v___y_144_; uint32_t v___y_145_; uint8_t v___y_146_; uint32_t v___y_147_; uint64_t v___y_151_; uint32_t v___y_152_; uint64_t v___y_153_; uint8_t v___y_154_; uint64_t v___y_155_; uint64_t v___y_165_; uint8_t v___y_166_; uint32_t v___y_167_; uint64_t v___y_168_; uint8_t v___y_169_; uint64_t v___y_170_; uint64_t v___y_177_; uint64_t v___y_178_; uint32_t v___y_179_; uint8_t v___y_180_; uint64_t v___y_181_; uint64_t v___y_187_; uint64_t v___y_188_; uint64_t v___y_189_; uint32_t v___y_190_; uint8_t v___y_191_; uint64_t v___y_192_; uint64_t v___y_247_; uint64_t v___y_248_; uint64_t v___y_249_; uint64_t v___y_250_; uint32_t v___y_251_; uint8_t v___y_252_; uint64_t v___y_253_; uint64_t v___y_259_; uint64_t v___y_260_; uint64_t v___y_261_; uint64_t v___y_262_; uint64_t v___y_263_; uint64_t v___y_264_; uint32_t v___y_265_; uint8_t v___y_266_; uint64_t v___y_267_; uint64_t v___y_272_; uint64_t v___y_273_; uint64_t v___y_274_; uint64_t v___y_275_; uint32_t v___y_276_; uint8_t v___y_277_; uint64_t v___y_278_; uint64_t v___y_283_; uint64_t v___y_284_; uint64_t v___y_285_; uint64_t v___y_286_; uint64_t v___y_287_; uint32_t v___y_288_; uint64_t v___y_289_; uint8_t v___y_290_; uint64_t v___y_291_; uint64_t v___y_296_; uint64_t v___y_297_; uint64_t v___y_298_; uint64_t v___y_299_; uint32_t v___y_300_; uint8_t v___y_301_; uint64_t v___y_302_; uint64_t v___y_307_; uint64_t v___y_308_; uint64_t v___y_309_; uint64_t v___y_310_; uint64_t v___y_311_; uint32_t v___y_312_; uint64_t v___y_313_; uint8_t v___y_314_; uint64_t v___y_315_; uint64_t v___y_320_; uint64_t v___y_321_; uint64_t v___y_322_; uint32_t v___y_323_; uint64_t v___y_324_; uint8_t v___y_325_; uint64_t v___y_326_; uint64_t v___y_331_; uint64_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint64_t v___y_335_; uint32_t v___y_336_; uint64_t v___y_337_; uint8_t v___y_338_; uint64_t v___y_339_; uint64_t v___y_344_; uint64_t v___y_345_; uint64_t v___y_346_; uint64_t v___y_347_; uint32_t v___y_348_; uint8_t v___y_349_; uint64_t v___y_350_; uint64_t v___y_355_; uint64_t v___y_356_; uint64_t v___y_357_; uint32_t v___y_358_; uint64_t v___y_359_; uint8_t v___y_360_; uint64_t v___y_361_; uint64_t v___y_365_; uint64_t v___y_366_; uint32_t v___y_367_; uint8_t v___y_368_; uint64_t v___y_377_; uint64_t v___y_378_; uint64_t v___y_379_; uint32_t v___y_380_; uint8_t v___y_381_; uint64_t v___y_382_; uint32_t v_ex_415_; uint32_t v___x_416_; uint32_t v_ey_417_; uint64_t v___y_419_; uint64_t v___y_420_; uint32_t v___y_421_; uint8_t v___y_422_; uint64_t v___y_423_; uint64_t v___y_430_; uint32_t v___y_431_; uint8_t v___y_432_; uint64_t v___y_433_; uint32_t v___y_440_; uint32_t v___y_441_; uint8_t v___y_442_; uint64_t v___y_443_; uint8_t v___y_451_; uint32_t v___x_461_; uint32_t v___x_462_; uint8_t v___x_463_; uint8_t v___y_465_; uint8_t v___y_466_; uint8_t v___y_468_; uint8_t v___y_469_; uint8_t v___y_470_; uint8_t v___y_472_; uint8_t v___y_473_; uint8_t v___y_479_; 
v___x_130_ = 23;
v___x_131_ = lean_uint32_shift_right(v___y_73_, v___x_130_);
v___x_132_ = 255;
v_ex_415_ = lean_uint32_land(v___x_131_, v___x_132_);
v___x_416_ = lean_uint32_shift_right(v___y_74_, v___x_130_);
v_ey_417_ = lean_uint32_land(v___x_416_, v___x_132_);
v___x_461_ = lean_uint32_add(v_ex_415_, v_ey_417_);
v___x_462_ = 128;
v___x_463_ = lean_uint32_dec_lt(v___x_461_, v___x_462_);
if (v___x_463_ == 0)
{
uint8_t v___x_491_; 
v___x_491_ = lean_uint32_dec_eq(v_ex_415_, v___x_132_);
if (v___x_491_ == 0)
{
goto v___jp_488_;
}
else
{
if (v___x_463_ == 0)
{
uint32_t v___x_492_; 
v___x_492_ = lp_competition_Submission_FastMul_mul(v___y_73_, v___y_74_);
return v___x_492_;
}
else
{
goto v___jp_488_;
}
}
}
else
{
uint32_t v___x_493_; uint32_t v___x_494_; uint32_t v___x_495_; uint8_t v___x_496_; 
v___x_493_ = 4278190080;
v___x_494_ = 1;
v___x_495_ = lean_uint32_shift_left(v___y_73_, v___x_494_);
v___x_496_ = lean_uint32_dec_le(v___x_493_, v___x_495_);
if (v___x_496_ == 0)
{
uint32_t v___x_497_; uint8_t v___x_498_; 
v___x_497_ = lean_uint32_shift_left(v___y_74_, v___x_494_);
v___x_498_ = lean_uint32_dec_le(v___x_493_, v___x_497_);
v___y_479_ = v___x_498_;
goto v___jp_478_;
}
else
{
v___y_479_ = v___x_496_;
goto v___jp_478_;
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
uint32_t v___x_84_; uint32_t v___x_85_; 
v___x_84_ = lean_uint32_land(v___y_81_, v___y_82_);
v___x_85_ = lean_uint32_lor(v___y_83_, v___x_84_);
return v___x_85_;
}
v___jp_86_:
{
uint32_t v___x_90_; uint32_t v___x_91_; 
v___x_90_ = lean_uint32_land(v___y_87_, v___y_88_);
v___x_91_ = lean_uint32_lor(v___y_89_, v___x_90_);
return v___x_91_;
}
v___jp_92_:
{
uint32_t v___x_94_; uint32_t v___x_95_; 
v___x_94_ = 8388608;
v___x_95_ = lean_uint32_lor(v___y_93_, v___x_94_);
return v___x_95_;
}
v___jp_96_:
{
uint8_t v___x_101_; 
v___x_101_ = lean_uint64_dec_eq(v___y_100_, v___y_97_);
if (v___x_101_ == 0)
{
uint64_t v___x_102_; uint8_t v___x_103_; 
v___x_102_ = 8388608ULL;
v___x_103_ = lean_uint64_dec_eq(v___y_100_, v___x_102_);
if (v___x_103_ == 0)
{
uint32_t v___x_104_; 
v___x_104_ = lean_uint64_to_uint32(v___y_100_);
if (v___y_99_ == 0)
{
uint32_t v___x_105_; 
v___x_105_ = 0;
v___y_87_ = v___x_104_;
v___y_88_ = v___y_98_;
v___y_89_ = v___x_105_;
goto v___jp_86_;
}
else
{
uint32_t v___x_106_; 
v___x_106_ = 2147483648;
v___y_87_ = v___x_104_;
v___y_88_ = v___y_98_;
v___y_89_ = v___x_106_;
goto v___jp_86_;
}
}
else
{
if (v___y_99_ == 0)
{
uint32_t v___x_107_; 
v___x_107_ = 0;
v___y_93_ = v___x_107_;
goto v___jp_92_;
}
else
{
uint32_t v___x_108_; 
v___x_108_ = 2147483648;
v___y_93_ = v___x_108_;
goto v___jp_92_;
}
}
}
else
{
if (v___y_99_ == 0)
{
uint32_t v___x_109_; 
v___x_109_ = 0;
return v___x_109_;
}
else
{
uint32_t v___x_110_; 
v___x_110_ = 2147483648;
return v___x_110_;
}
}
}
v___jp_111_:
{
uint32_t v___x_113_; uint32_t v___x_114_; 
v___x_113_ = 8388608;
v___x_114_ = lean_uint32_lor(v___y_112_, v___x_113_);
return v___x_114_;
}
v___jp_115_:
{
uint8_t v___x_120_; 
v___x_120_ = lean_uint64_dec_eq(v___y_119_, v___y_116_);
if (v___x_120_ == 0)
{
uint64_t v___x_121_; uint8_t v___x_122_; 
v___x_121_ = 8388608ULL;
v___x_122_ = lean_uint64_dec_eq(v___y_119_, v___x_121_);
if (v___x_122_ == 0)
{
uint32_t v___x_123_; 
v___x_123_ = lean_uint64_to_uint32(v___y_119_);
if (v___y_118_ == 0)
{
uint32_t v___x_124_; 
v___x_124_ = 0;
v___y_81_ = v___x_123_;
v___y_82_ = v___y_117_;
v___y_83_ = v___x_124_;
goto v___jp_80_;
}
else
{
uint32_t v___x_125_; 
v___x_125_ = 2147483648;
v___y_81_ = v___x_123_;
v___y_82_ = v___y_117_;
v___y_83_ = v___x_125_;
goto v___jp_80_;
}
}
else
{
if (v___y_118_ == 0)
{
uint32_t v___x_126_; 
v___x_126_ = 0;
v___y_112_ = v___x_126_;
goto v___jp_111_;
}
else
{
uint32_t v___x_127_; 
v___x_127_ = 2147483648;
v___y_112_ = v___x_127_;
goto v___jp_111_;
}
}
}
else
{
if (v___y_118_ == 0)
{
uint32_t v___x_128_; 
v___x_128_ = 0;
return v___x_128_;
}
else
{
uint32_t v___x_129_; 
v___x_129_ = 2147483648;
return v___x_129_;
}
}
}
v___jp_133_:
{
uint32_t v___x_138_; uint32_t v___x_139_; uint32_t v___x_140_; uint32_t v___x_141_; uint32_t v___x_142_; 
v___x_138_ = lean_uint32_land(v___y_136_, v___x_132_);
v___x_139_ = lean_uint32_shift_left(v___x_138_, v___x_130_);
v___x_140_ = lean_uint32_lor(v___y_137_, v___x_139_);
v___x_141_ = lean_uint32_land(v___y_135_, v___y_134_);
v___x_142_ = lean_uint32_lor(v___x_140_, v___x_141_);
return v___x_142_;
}
v___jp_143_:
{
if (v___y_146_ == 0)
{
uint32_t v___x_148_; 
v___x_148_ = 0;
v___y_134_ = v___y_144_;
v___y_135_ = v___y_147_;
v___y_136_ = v___y_145_;
v___y_137_ = v___x_148_;
goto v___jp_133_;
}
else
{
uint32_t v___x_149_; 
v___x_149_ = 2147483648;
v___y_134_ = v___y_144_;
v___y_135_ = v___y_147_;
v___y_136_ = v___y_145_;
v___y_137_ = v___x_149_;
goto v___jp_133_;
}
}
v___jp_150_:
{
uint64_t v___x_156_; uint64_t v_encodedExponent_157_; uint32_t v___x_158_; uint64_t v___x_159_; uint8_t v___x_160_; 
v___x_156_ = 171ULL;
v_encodedExponent_157_ = lean_uint64_sub(v___y_153_, v___x_156_);
v___x_158_ = lean_uint64_to_uint32(v_encodedExponent_157_);
v___x_159_ = 8388608ULL;
v___x_160_ = lean_uint64_dec_lt(v___y_155_, v___x_159_);
if (v___x_160_ == 0)
{
uint64_t v___x_161_; uint32_t v___x_162_; 
v___x_161_ = lean_uint64_sub(v___y_155_, v___x_159_);
v___x_162_ = lean_uint64_to_uint32(v___x_161_);
v___y_144_ = v___y_152_;
v___y_145_ = v___x_158_;
v___y_146_ = v___y_154_;
v___y_147_ = v___x_162_;
goto v___jp_143_;
}
else
{
uint32_t v___x_163_; 
v___x_163_ = lean_uint64_to_uint32(v___y_151_);
v___y_144_ = v___y_152_;
v___y_145_ = v___x_158_;
v___y_146_ = v___y_154_;
v___y_147_ = v___x_163_;
goto v___jp_143_;
}
}
v___jp_164_:
{
uint64_t v___x_171_; uint8_t v___x_172_; 
v___x_171_ = 425ULL;
v___x_172_ = lean_uint64_dec_lt(v___x_171_, v___y_170_);
if (v___x_172_ == 0)
{
if (v___y_166_ == 0)
{
v___y_151_ = v___y_165_;
v___y_152_ = v___y_167_;
v___y_153_ = v___y_170_;
v___y_154_ = v___y_169_;
v___y_155_ = v___y_168_;
goto v___jp_150_;
}
else
{
uint64_t v___x_173_; 
v___x_173_ = 8388608ULL;
v___y_151_ = v___y_165_;
v___y_152_ = v___y_167_;
v___y_153_ = v___y_170_;
v___y_154_ = v___y_169_;
v___y_155_ = v___x_173_;
goto v___jp_150_;
}
}
else
{
if (v___y_169_ == 0)
{
uint32_t v___x_174_; 
v___x_174_ = 2139095040;
return v___x_174_;
}
else
{
uint32_t v___x_175_; 
v___x_175_ = 4286578688;
return v___x_175_;
}
}
}
v___jp_176_:
{
uint64_t v___x_182_; uint8_t v_carry_183_; 
v___x_182_ = 16777216ULL;
v_carry_183_ = lean_uint64_dec_eq(v___y_181_, v___x_182_);
if (v_carry_183_ == 0)
{
v___y_165_ = v___y_177_;
v___y_166_ = v_carry_183_;
v___y_167_ = v___y_179_;
v___y_168_ = v___y_181_;
v___y_169_ = v___y_180_;
v___y_170_ = v___y_178_;
goto v___jp_164_;
}
else
{
uint64_t v___x_184_; uint64_t v___x_185_; 
v___x_184_ = 1ULL;
v___x_185_ = lean_uint64_add(v___y_178_, v___x_184_);
v___y_165_ = v___y_177_;
v___y_166_ = v_carry_183_;
v___y_167_ = v___y_179_;
v___y_168_ = v___y_181_;
v___y_169_ = v___y_180_;
v___y_170_ = v___x_185_;
goto v___jp_164_;
}
}
v___jp_186_:
{
uint64_t v_position_193_; uint64_t v___x_194_; uint8_t v___x_195_; 
v_position_193_ = lean_uint64_add(v___y_192_, v___y_188_);
v___x_194_ = 172ULL;
v___x_195_ = lean_uint64_dec_lt(v_position_193_, v___x_194_);
if (v___x_195_ == 0)
{
uint64_t v___x_196_; uint8_t v___x_197_; 
v___x_196_ = 23ULL;
v___x_197_ = lean_uint64_dec_lt(v___y_192_, v___x_196_);
if (v___x_197_ == 0)
{
uint64_t v___x_198_; uint8_t v___x_199_; 
v___x_198_ = lean_uint64_sub(v___y_192_, v___x_196_);
v___x_199_ = lean_uint64_dec_eq(v___x_198_, v___y_189_);
if (v___x_199_ == 0)
{
uint64_t v___x_200_; uint8_t v___x_201_; 
v___x_200_ = 64ULL;
v___x_201_ = lean_uint64_dec_lt(v___x_198_, v___x_200_);
if (v___x_201_ == 0)
{
uint8_t v___x_202_; 
v___x_202_ = lean_uint64_dec_eq(v___x_198_, v___x_200_);
if (v___x_202_ == 0)
{
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___y_189_;
goto v___jp_176_;
}
else
{
uint64_t v___x_203_; uint8_t v___x_204_; 
v___x_203_ = 9223372036854775808ULL;
v___x_204_ = lean_uint64_dec_lt(v___x_203_, v___y_187_);
if (v___x_204_ == 0)
{
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___y_189_;
goto v___jp_176_;
}
else
{
uint64_t v___x_205_; 
v___x_205_ = 1ULL;
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___x_205_;
goto v___jp_176_;
}
}
}
else
{
uint64_t v_quotient_206_; uint64_t v___x_207_; uint64_t v___x_208_; uint64_t v___x_209_; uint64_t v_remainder_210_; uint64_t v___x_211_; uint64_t v_half_212_; uint8_t v___x_213_; 
v_quotient_206_ = lean_uint64_shift_right(v___y_187_, v___x_198_);
v___x_207_ = 1ULL;
v___x_208_ = lean_uint64_shift_left(v___x_207_, v___x_198_);
v___x_209_ = lean_uint64_sub(v___x_208_, v___x_207_);
v_remainder_210_ = lean_uint64_land(v___y_187_, v___x_209_);
v___x_211_ = lean_uint64_sub(v___x_198_, v___x_207_);
v_half_212_ = lean_uint64_shift_left(v___x_207_, v___x_211_);
v___x_213_ = lean_uint64_dec_lt(v_remainder_210_, v_half_212_);
if (v___x_213_ == 0)
{
uint8_t v___x_214_; 
v___x_214_ = lean_uint64_dec_lt(v_half_212_, v_remainder_210_);
if (v___x_214_ == 0)
{
uint64_t v___x_215_; uint8_t v___x_216_; 
v___x_215_ = lean_uint64_land(v_quotient_206_, v___x_207_);
v___x_216_ = lean_uint64_dec_eq(v___x_215_, v___y_189_);
if (v___x_216_ == 0)
{
uint64_t v___x_217_; 
v___x_217_ = lean_uint64_add(v_quotient_206_, v___x_207_);
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___x_217_;
goto v___jp_176_;
}
else
{
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v_quotient_206_;
goto v___jp_176_;
}
}
else
{
uint64_t v___x_218_; 
v___x_218_ = lean_uint64_add(v_quotient_206_, v___x_207_);
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___x_218_;
goto v___jp_176_;
}
}
else
{
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v_quotient_206_;
goto v___jp_176_;
}
}
}
else
{
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___y_187_;
goto v___jp_176_;
}
}
else
{
uint64_t v___x_219_; uint64_t v___x_220_; 
v___x_219_ = lean_uint64_sub(v___x_196_, v___y_192_);
v___x_220_ = lean_uint64_shift_left(v___y_187_, v___x_219_);
v___y_177_ = v___y_189_;
v___y_178_ = v_position_193_;
v___y_179_ = v___y_190_;
v___y_180_ = v___y_191_;
v___y_181_ = v___x_220_;
goto v___jp_176_;
}
}
else
{
uint64_t v___x_221_; uint8_t v___x_222_; 
v___x_221_ = 149ULL;
v___x_222_ = lean_uint64_dec_lt(v___y_188_, v___x_221_);
if (v___x_222_ == 0)
{
uint64_t v___x_223_; uint64_t v___x_224_; 
v___x_223_ = lean_uint64_sub(v___y_188_, v___x_221_);
v___x_224_ = lean_uint64_shift_left(v___y_187_, v___x_223_);
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v___x_224_;
goto v___jp_96_;
}
else
{
uint64_t v___x_225_; uint8_t v___x_226_; 
v___x_225_ = lean_uint64_sub(v___x_221_, v___y_188_);
v___x_226_ = lean_uint64_dec_eq(v___x_225_, v___y_189_);
if (v___x_226_ == 0)
{
uint64_t v___x_227_; uint8_t v___x_228_; 
v___x_227_ = 64ULL;
v___x_228_ = lean_uint64_dec_lt(v___x_225_, v___x_227_);
if (v___x_228_ == 0)
{
uint8_t v___x_229_; 
v___x_229_ = lean_uint64_dec_eq(v___x_225_, v___x_227_);
if (v___x_229_ == 0)
{
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v___y_189_;
goto v___jp_96_;
}
else
{
uint64_t v___x_230_; uint8_t v___x_231_; 
v___x_230_ = 9223372036854775808ULL;
v___x_231_ = lean_uint64_dec_lt(v___x_230_, v___y_187_);
if (v___x_231_ == 0)
{
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v___y_189_;
goto v___jp_96_;
}
else
{
uint64_t v___x_232_; 
v___x_232_ = 1ULL;
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v___x_232_;
goto v___jp_96_;
}
}
}
else
{
uint64_t v_quotient_233_; uint64_t v___x_234_; uint64_t v___x_235_; uint64_t v___x_236_; uint64_t v_remainder_237_; uint64_t v___x_238_; uint64_t v_half_239_; uint8_t v___x_240_; 
v_quotient_233_ = lean_uint64_shift_right(v___y_187_, v___x_225_);
v___x_234_ = 1ULL;
v___x_235_ = lean_uint64_shift_left(v___x_234_, v___x_225_);
v___x_236_ = lean_uint64_sub(v___x_235_, v___x_234_);
v_remainder_237_ = lean_uint64_land(v___y_187_, v___x_236_);
v___x_238_ = lean_uint64_sub(v___x_225_, v___x_234_);
v_half_239_ = lean_uint64_shift_left(v___x_234_, v___x_238_);
v___x_240_ = lean_uint64_dec_lt(v_remainder_237_, v_half_239_);
if (v___x_240_ == 0)
{
uint8_t v___x_241_; 
v___x_241_ = lean_uint64_dec_lt(v_half_239_, v_remainder_237_);
if (v___x_241_ == 0)
{
uint64_t v___x_242_; uint8_t v___x_243_; 
v___x_242_ = lean_uint64_land(v_quotient_233_, v___x_234_);
v___x_243_ = lean_uint64_dec_eq(v___x_242_, v___y_189_);
if (v___x_243_ == 0)
{
uint64_t v___x_244_; 
v___x_244_ = lean_uint64_add(v_quotient_233_, v___x_234_);
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v___x_244_;
goto v___jp_96_;
}
else
{
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v_quotient_233_;
goto v___jp_96_;
}
}
else
{
uint64_t v___x_245_; 
v___x_245_ = lean_uint64_add(v_quotient_233_, v___x_234_);
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v___x_245_;
goto v___jp_96_;
}
}
else
{
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v_quotient_233_;
goto v___jp_96_;
}
}
}
else
{
v___y_97_ = v___y_189_;
v___y_98_ = v___y_190_;
v___y_99_ = v___y_191_;
v___y_100_ = v___y_187_;
goto v___jp_96_;
}
}
}
}
v___jp_246_:
{
uint64_t v___x_254_; uint64_t v___x_255_; uint8_t v___x_256_; 
v___x_254_ = 1ULL;
v___x_255_ = lean_uint64_shift_right(v___y_250_, v___x_254_);
v___x_256_ = lean_uint64_dec_eq(v___x_255_, v___y_249_);
if (v___x_256_ == 0)
{
uint64_t v___x_257_; 
v___x_257_ = lean_uint64_add(v___y_253_, v___x_254_);
v___y_187_ = v___y_247_;
v___y_188_ = v___y_248_;
v___y_189_ = v___y_249_;
v___y_190_ = v___y_251_;
v___y_191_ = v___y_252_;
v___y_192_ = v___x_257_;
goto v___jp_186_;
}
else
{
v___y_187_ = v___y_247_;
v___y_188_ = v___y_248_;
v___y_189_ = v___y_249_;
v___y_190_ = v___y_251_;
v___y_191_ = v___y_252_;
v___y_192_ = v___y_253_;
goto v___jp_186_;
}
}
v___jp_258_:
{
uint64_t v___x_268_; uint8_t v___x_269_; 
v___x_268_ = lean_uint64_shift_right(v___y_264_, v___y_262_);
v___x_269_ = lean_uint64_dec_eq(v___x_268_, v___y_261_);
if (v___x_269_ == 0)
{
uint64_t v___x_270_; 
v___x_270_ = lean_uint64_add(v___y_263_, v___y_262_);
v___y_247_ = v___y_259_;
v___y_248_ = v___y_260_;
v___y_249_ = v___y_261_;
v___y_250_ = v___y_267_;
v___y_251_ = v___y_265_;
v___y_252_ = v___y_266_;
v___y_253_ = v___x_270_;
goto v___jp_246_;
}
else
{
v___y_247_ = v___y_259_;
v___y_248_ = v___y_260_;
v___y_249_ = v___y_261_;
v___y_250_ = v___y_267_;
v___y_251_ = v___y_265_;
v___y_252_ = v___y_266_;
v___y_253_ = v___y_263_;
goto v___jp_246_;
}
}
v___jp_271_:
{
uint64_t v___x_279_; uint64_t v___x_280_; uint8_t v___x_281_; 
v___x_279_ = 2ULL;
v___x_280_ = lean_uint64_shift_right(v___y_275_, v___x_279_);
v___x_281_ = lean_uint64_dec_eq(v___x_280_, v___y_274_);
if (v___x_281_ == 0)
{
v___y_259_ = v___y_272_;
v___y_260_ = v___y_273_;
v___y_261_ = v___y_274_;
v___y_262_ = v___x_279_;
v___y_263_ = v___y_278_;
v___y_264_ = v___y_275_;
v___y_265_ = v___y_276_;
v___y_266_ = v___y_277_;
v___y_267_ = v___x_280_;
goto v___jp_258_;
}
else
{
v___y_259_ = v___y_272_;
v___y_260_ = v___y_273_;
v___y_261_ = v___y_274_;
v___y_262_ = v___x_279_;
v___y_263_ = v___y_278_;
v___y_264_ = v___y_275_;
v___y_265_ = v___y_276_;
v___y_266_ = v___y_277_;
v___y_267_ = v___y_275_;
goto v___jp_258_;
}
}
v___jp_282_:
{
uint64_t v___x_292_; uint8_t v___x_293_; 
v___x_292_ = lean_uint64_shift_right(v___y_285_, v___y_289_);
v___x_293_ = lean_uint64_dec_eq(v___x_292_, v___y_286_);
if (v___x_293_ == 0)
{
uint64_t v___x_294_; 
v___x_294_ = lean_uint64_add(v___y_287_, v___y_289_);
v___y_272_ = v___y_283_;
v___y_273_ = v___y_284_;
v___y_274_ = v___y_286_;
v___y_275_ = v___y_291_;
v___y_276_ = v___y_288_;
v___y_277_ = v___y_290_;
v___y_278_ = v___x_294_;
goto v___jp_271_;
}
else
{
v___y_272_ = v___y_283_;
v___y_273_ = v___y_284_;
v___y_274_ = v___y_286_;
v___y_275_ = v___y_291_;
v___y_276_ = v___y_288_;
v___y_277_ = v___y_290_;
v___y_278_ = v___y_287_;
goto v___jp_271_;
}
}
v___jp_295_:
{
uint64_t v___x_303_; uint64_t v___x_304_; uint8_t v___x_305_; 
v___x_303_ = 4ULL;
v___x_304_ = lean_uint64_shift_right(v___y_298_, v___x_303_);
v___x_305_ = lean_uint64_dec_eq(v___x_304_, v___y_299_);
if (v___x_305_ == 0)
{
v___y_283_ = v___y_296_;
v___y_284_ = v___y_297_;
v___y_285_ = v___y_298_;
v___y_286_ = v___y_299_;
v___y_287_ = v___y_302_;
v___y_288_ = v___y_300_;
v___y_289_ = v___x_303_;
v___y_290_ = v___y_301_;
v___y_291_ = v___x_304_;
goto v___jp_282_;
}
else
{
v___y_283_ = v___y_296_;
v___y_284_ = v___y_297_;
v___y_285_ = v___y_298_;
v___y_286_ = v___y_299_;
v___y_287_ = v___y_302_;
v___y_288_ = v___y_300_;
v___y_289_ = v___x_303_;
v___y_290_ = v___y_301_;
v___y_291_ = v___y_298_;
goto v___jp_282_;
}
}
v___jp_306_:
{
uint64_t v___x_316_; uint8_t v___x_317_; 
v___x_316_ = lean_uint64_shift_right(v___y_311_, v___y_310_);
v___x_317_ = lean_uint64_dec_eq(v___x_316_, v___y_309_);
if (v___x_317_ == 0)
{
uint64_t v___x_318_; 
v___x_318_ = lean_uint64_add(v___y_313_, v___y_310_);
v___y_296_ = v___y_307_;
v___y_297_ = v___y_308_;
v___y_298_ = v___y_315_;
v___y_299_ = v___y_309_;
v___y_300_ = v___y_312_;
v___y_301_ = v___y_314_;
v___y_302_ = v___x_318_;
goto v___jp_295_;
}
else
{
v___y_296_ = v___y_307_;
v___y_297_ = v___y_308_;
v___y_298_ = v___y_315_;
v___y_299_ = v___y_309_;
v___y_300_ = v___y_312_;
v___y_301_ = v___y_314_;
v___y_302_ = v___y_313_;
goto v___jp_295_;
}
}
v___jp_319_:
{
uint64_t v___x_327_; uint64_t v___x_328_; uint8_t v___x_329_; 
v___x_327_ = 8ULL;
v___x_328_ = lean_uint64_shift_right(v___y_324_, v___x_327_);
v___x_329_ = lean_uint64_dec_eq(v___x_328_, v___y_322_);
if (v___x_329_ == 0)
{
v___y_307_ = v___y_320_;
v___y_308_ = v___y_321_;
v___y_309_ = v___y_322_;
v___y_310_ = v___x_327_;
v___y_311_ = v___y_324_;
v___y_312_ = v___y_323_;
v___y_313_ = v___y_326_;
v___y_314_ = v___y_325_;
v___y_315_ = v___x_328_;
goto v___jp_306_;
}
else
{
v___y_307_ = v___y_320_;
v___y_308_ = v___y_321_;
v___y_309_ = v___y_322_;
v___y_310_ = v___x_327_;
v___y_311_ = v___y_324_;
v___y_312_ = v___y_323_;
v___y_313_ = v___y_326_;
v___y_314_ = v___y_325_;
v___y_315_ = v___y_324_;
goto v___jp_306_;
}
}
v___jp_330_:
{
uint64_t v___x_340_; uint8_t v___x_341_; 
v___x_340_ = lean_uint64_shift_right(v___y_332_, v___y_335_);
v___x_341_ = lean_uint64_dec_eq(v___x_340_, v___y_334_);
if (v___x_341_ == 0)
{
uint64_t v___x_342_; 
v___x_342_ = lean_uint64_add(v___y_337_, v___y_335_);
v___y_320_ = v___y_331_;
v___y_321_ = v___y_333_;
v___y_322_ = v___y_334_;
v___y_323_ = v___y_336_;
v___y_324_ = v___y_339_;
v___y_325_ = v___y_338_;
v___y_326_ = v___x_342_;
goto v___jp_319_;
}
else
{
v___y_320_ = v___y_331_;
v___y_321_ = v___y_333_;
v___y_322_ = v___y_334_;
v___y_323_ = v___y_336_;
v___y_324_ = v___y_339_;
v___y_325_ = v___y_338_;
v___y_326_ = v___y_337_;
goto v___jp_319_;
}
}
v___jp_343_:
{
uint64_t v___x_351_; uint64_t v___x_352_; uint8_t v___x_353_; 
v___x_351_ = 16ULL;
v___x_352_ = lean_uint64_shift_right(v___y_346_, v___x_351_);
v___x_353_ = lean_uint64_dec_eq(v___x_352_, v___y_347_);
if (v___x_353_ == 0)
{
v___y_331_ = v___y_344_;
v___y_332_ = v___y_346_;
v___y_333_ = v___y_345_;
v___y_334_ = v___y_347_;
v___y_335_ = v___x_351_;
v___y_336_ = v___y_348_;
v___y_337_ = v___y_350_;
v___y_338_ = v___y_349_;
v___y_339_ = v___x_352_;
goto v___jp_330_;
}
else
{
v___y_331_ = v___y_344_;
v___y_332_ = v___y_346_;
v___y_333_ = v___y_345_;
v___y_334_ = v___y_347_;
v___y_335_ = v___x_351_;
v___y_336_ = v___y_348_;
v___y_337_ = v___y_350_;
v___y_338_ = v___y_349_;
v___y_339_ = v___y_346_;
goto v___jp_330_;
}
}
v___jp_354_:
{
uint64_t v___x_362_; uint8_t v___x_363_; 
v___x_362_ = lean_uint64_shift_right(v___y_355_, v___y_359_);
v___x_363_ = lean_uint64_dec_eq(v___x_362_, v___y_357_);
if (v___x_363_ == 0)
{
v___y_344_ = v___y_355_;
v___y_345_ = v___y_356_;
v___y_346_ = v___y_361_;
v___y_347_ = v___y_357_;
v___y_348_ = v___y_358_;
v___y_349_ = v___y_360_;
v___y_350_ = v___y_359_;
goto v___jp_343_;
}
else
{
v___y_344_ = v___y_355_;
v___y_345_ = v___y_356_;
v___y_346_ = v___y_361_;
v___y_347_ = v___y_357_;
v___y_348_ = v___y_358_;
v___y_349_ = v___y_360_;
v___y_350_ = v___y_357_;
goto v___jp_343_;
}
}
v___jp_364_:
{
uint64_t v___x_369_; uint8_t v___x_370_; 
v___x_369_ = 0ULL;
v___x_370_ = lean_uint64_dec_eq(v___y_365_, v___x_369_);
if (v___x_370_ == 0)
{
uint64_t v___x_371_; uint64_t v___x_372_; uint8_t v___x_373_; 
v___x_371_ = 32ULL;
v___x_372_ = lean_uint64_shift_right(v___y_365_, v___x_371_);
v___x_373_ = lean_uint64_dec_eq(v___x_372_, v___x_369_);
if (v___x_373_ == 0)
{
v___y_355_ = v___y_365_;
v___y_356_ = v___y_366_;
v___y_357_ = v___x_369_;
v___y_358_ = v___y_367_;
v___y_359_ = v___x_371_;
v___y_360_ = v___y_368_;
v___y_361_ = v___x_372_;
goto v___jp_354_;
}
else
{
v___y_355_ = v___y_365_;
v___y_356_ = v___y_366_;
v___y_357_ = v___x_369_;
v___y_358_ = v___y_367_;
v___y_359_ = v___x_371_;
v___y_360_ = v___y_368_;
v___y_361_ = v___y_365_;
goto v___jp_354_;
}
}
else
{
if (v___y_368_ == 0)
{
uint32_t v___x_374_; 
v___x_374_ = 0;
return v___x_374_;
}
else
{
uint32_t v___x_375_; 
v___x_375_ = 2147483648;
return v___x_375_;
}
}
}
v___jp_376_:
{
uint64_t v___x_383_; uint64_t v___x_384_; uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_383_ = lean_uint64_mul(v___y_377_, v___y_378_);
v___x_384_ = lean_uint64_add(v___y_379_, v___y_382_);
v___x_385_ = 281474976710656ULL;
v___x_386_ = lean_uint64_dec_lt(v___x_383_, v___x_385_);
if (v___x_386_ == 0)
{
v___y_365_ = v___x_383_;
v___y_366_ = v___x_384_;
v___y_367_ = v___y_380_;
v___y_368_ = v___y_381_;
goto v___jp_364_;
}
else
{
uint64_t v___x_387_; uint8_t v___x_388_; 
v___x_387_ = 123ULL;
v___x_388_ = lean_uint64_dec_le(v___x_384_, v___x_387_);
if (v___x_388_ == 0)
{
v___y_365_ = v___x_383_;
v___y_366_ = v___x_384_;
v___y_367_ = v___y_380_;
v___y_368_ = v___y_381_;
goto v___jp_364_;
}
else
{
uint64_t v___x_389_; uint8_t v___x_390_; 
v___x_389_ = 0ULL;
v___x_390_ = lean_uint64_dec_eq(v___x_383_, v___x_389_);
if (v___x_390_ == 0)
{
uint64_t v___x_391_; uint64_t v___x_392_; uint8_t v___x_393_; 
v___x_391_ = 149ULL;
v___x_392_ = lean_uint64_sub(v___x_391_, v___x_384_);
v___x_393_ = lean_uint64_dec_eq(v___x_392_, v___x_389_);
if (v___x_393_ == 0)
{
uint64_t v___x_394_; uint8_t v___x_395_; 
v___x_394_ = 64ULL;
v___x_395_ = lean_uint64_dec_lt(v___x_392_, v___x_394_);
if (v___x_395_ == 0)
{
uint8_t v___x_396_; 
v___x_396_ = lean_uint64_dec_eq(v___x_392_, v___x_394_);
if (v___x_396_ == 0)
{
v___y_116_ = v___x_389_;
v___y_117_ = v___y_380_;
v___y_118_ = v___y_381_;
v___y_119_ = v___x_389_;
goto v___jp_115_;
}
else
{
uint64_t v___x_397_; uint8_t v___x_398_; 
v___x_397_ = 9223372036854775808ULL;
v___x_398_ = lean_uint64_dec_lt(v___x_397_, v___x_383_);
if (v___x_398_ == 0)
{
v___y_116_ = v___x_389_;
v___y_117_ = v___y_380_;
v___y_118_ = v___y_381_;
v___y_119_ = v___x_389_;
goto v___jp_115_;
}
else
{
uint64_t v___x_399_; 
v___x_399_ = 1ULL;
v___y_116_ = v___x_389_;
v___y_117_ = v___y_380_;
v___y_118_ = v___y_381_;
v___y_119_ = v___x_399_;
goto v___jp_115_;
}
}
}
else
{
uint64_t v_quotient_400_; uint64_t v___x_401_; uint64_t v___x_402_; uint64_t v___x_403_; uint64_t v_remainder_404_; uint64_t v___x_405_; uint64_t v_half_406_; uint8_t v___x_407_; 
v_quotient_400_ = lean_uint64_shift_right(v___x_383_, v___x_392_);
v___x_401_ = 1ULL;
v___x_402_ = lean_uint64_shift_left(v___x_401_, v___x_392_);
v___x_403_ = lean_uint64_sub(v___x_402_, v___x_401_);
v_remainder_404_ = lean_uint64_land(v___x_383_, v___x_403_);
v___x_405_ = lean_uint64_sub(v___x_392_, v___x_401_);
v_half_406_ = lean_uint64_shift_left(v___x_401_, v___x_405_);
v___x_407_ = lean_uint64_dec_lt(v_remainder_404_, v_half_406_);
if (v___x_407_ == 0)
{
uint8_t v___x_408_; 
v___x_408_ = lean_uint64_dec_lt(v_half_406_, v_remainder_404_);
if (v___x_408_ == 0)
{
uint64_t v___x_409_; uint8_t v___x_410_; 
v___x_409_ = lean_uint64_land(v_quotient_400_, v___x_401_);
v___x_410_ = lean_uint64_dec_eq(v___x_409_, v___x_389_);
if (v___x_410_ == 0)
{
uint64_t v___x_411_; 
v___x_411_ = lean_uint64_add(v_quotient_400_, v___x_401_);
v___y_116_ = v___x_389_;
v___y_117_ = v___y_380_;
v___y_118_ = v___y_381_;
v___y_119_ = v___x_411_;
goto v___jp_115_;
}
else
{
v___y_116_ = v___x_389_;
v___y_117_ = v___y_380_;
v___y_118_ = v___y_381_;
v___y_119_ = v_quotient_400_;
goto v___jp_115_;
}
}
else
{
uint64_t v___x_412_; 
v___x_412_ = lean_uint64_add(v_quotient_400_, v___x_401_);
v___y_116_ = v___x_389_;
v___y_117_ = v___y_380_;
v___y_118_ = v___y_381_;
v___y_119_ = v___x_412_;
goto v___jp_115_;
}
}
else
{
v___y_116_ = v___x_389_;
v___y_117_ = v___y_380_;
v___y_118_ = v___y_381_;
v___y_119_ = v_quotient_400_;
goto v___jp_115_;
}
}
}
else
{
v___y_116_ = v___x_389_;
v___y_117_ = v___y_380_;
v___y_118_ = v___y_381_;
v___y_119_ = v___x_383_;
goto v___jp_115_;
}
}
else
{
if (v___y_381_ == 0)
{
uint32_t v___x_413_; 
v___x_413_ = 0;
return v___x_413_;
}
else
{
uint32_t v___x_414_; 
v___x_414_ = 2147483648;
return v___x_414_;
}
}
}
}
}
v___jp_418_:
{
uint64_t v___x_424_; uint64_t v___x_425_; uint8_t v___x_426_; 
v___x_424_ = lean_uint32_to_uint64(v_ey_417_);
v___x_425_ = 0ULL;
v___x_426_ = lean_uint64_dec_eq(v___x_424_, v___x_425_);
if (v___x_426_ == 0)
{
uint64_t v___x_427_; uint64_t v___x_428_; 
v___x_427_ = 1ULL;
v___x_428_ = lean_uint64_sub(v___x_424_, v___x_427_);
v___y_377_ = v___y_419_;
v___y_378_ = v___y_420_;
v___y_379_ = v___y_423_;
v___y_380_ = v___y_421_;
v___y_381_ = v___y_422_;
v___y_382_ = v___x_428_;
goto v___jp_376_;
}
else
{
v___y_377_ = v___y_419_;
v___y_378_ = v___y_420_;
v___y_379_ = v___y_423_;
v___y_380_ = v___y_421_;
v___y_381_ = v___y_422_;
v___y_382_ = v___x_425_;
goto v___jp_376_;
}
}
v___jp_429_:
{
uint64_t v___x_434_; uint64_t v___x_435_; uint8_t v___x_436_; 
v___x_434_ = lean_uint32_to_uint64(v_ex_415_);
v___x_435_ = 0ULL;
v___x_436_ = lean_uint64_dec_eq(v___x_434_, v___x_435_);
if (v___x_436_ == 0)
{
uint64_t v___x_437_; uint64_t v___x_438_; 
v___x_437_ = 1ULL;
v___x_438_ = lean_uint64_sub(v___x_434_, v___x_437_);
v___y_419_ = v___y_430_;
v___y_420_ = v___y_433_;
v___y_421_ = v___y_431_;
v___y_422_ = v___y_432_;
v___y_423_ = v___x_438_;
goto v___jp_418_;
}
else
{
v___y_419_ = v___y_430_;
v___y_420_ = v___y_433_;
v___y_421_ = v___y_431_;
v___y_422_ = v___y_432_;
v___y_423_ = v___x_435_;
goto v___jp_418_;
}
}
v___jp_439_:
{
uint32_t v___x_444_; uint8_t v___x_445_; 
v___x_444_ = 0;
v___x_445_ = lean_uint32_dec_eq(v_ey_417_, v___x_444_);
if (v___x_445_ == 0)
{
uint64_t v___x_446_; uint64_t v___x_447_; uint64_t v___x_448_; 
v___x_446_ = lean_uint32_to_uint64(v___y_440_);
v___x_447_ = 8388608ULL;
v___x_448_ = lean_uint64_lor(v___x_446_, v___x_447_);
v___y_430_ = v___y_443_;
v___y_431_ = v___y_441_;
v___y_432_ = v___y_442_;
v___y_433_ = v___x_448_;
goto v___jp_429_;
}
else
{
uint64_t v___x_449_; 
v___x_449_ = lean_uint32_to_uint64(v___y_440_);
v___y_430_ = v___y_443_;
v___y_431_ = v___y_441_;
v___y_432_ = v___y_442_;
v___y_433_ = v___x_449_;
goto v___jp_429_;
}
}
v___jp_450_:
{
uint32_t v___x_452_; uint32_t v_xFraction_453_; uint32_t v_yFraction_454_; uint32_t v___x_455_; uint8_t v___x_456_; 
v___x_452_ = 8388607;
v_xFraction_453_ = lean_uint32_land(v___y_73_, v___x_452_);
v_yFraction_454_ = lean_uint32_land(v___y_74_, v___x_452_);
v___x_455_ = 0;
v___x_456_ = lean_uint32_dec_eq(v_ex_415_, v___x_455_);
if (v___x_456_ == 0)
{
uint64_t v___x_457_; uint64_t v___x_458_; uint64_t v___x_459_; 
v___x_457_ = lean_uint32_to_uint64(v_xFraction_453_);
v___x_458_ = 8388608ULL;
v___x_459_ = lean_uint64_lor(v___x_457_, v___x_458_);
v___y_440_ = v_yFraction_454_;
v___y_441_ = v___x_452_;
v___y_442_ = v___y_451_;
v___y_443_ = v___x_459_;
goto v___jp_439_;
}
else
{
uint64_t v___x_460_; 
v___x_460_ = lean_uint32_to_uint64(v_xFraction_453_);
v___y_440_ = v_yFraction_454_;
v___y_441_ = v___x_452_;
v___y_442_ = v___y_451_;
v___y_443_ = v___x_460_;
goto v___jp_439_;
}
}
v___jp_464_:
{
if (v___y_466_ == 0)
{
v___y_451_ = v___x_463_;
goto v___jp_450_;
}
else
{
v___y_451_ = v___y_465_;
goto v___jp_450_;
}
}
v___jp_467_:
{
if (v___y_468_ == 0)
{
if (v___y_470_ == 0)
{
v___y_465_ = v___y_469_;
v___y_466_ = v___x_463_;
goto v___jp_464_;
}
else
{
v___y_451_ = v___x_463_;
goto v___jp_450_;
}
}
else
{
v___y_465_ = v___y_469_;
v___y_466_ = v___y_470_;
goto v___jp_464_;
}
}
v___jp_471_:
{
uint32_t v___x_474_; uint32_t v___x_475_; uint32_t v___x_476_; uint8_t v___x_477_; 
v___x_474_ = 2147483648;
v___x_475_ = lean_uint32_land(v___y_74_, v___x_474_);
v___x_476_ = 0;
v___x_477_ = lean_uint32_dec_eq(v___x_475_, v___x_476_);
if (v___x_477_ == 0)
{
v___y_468_ = v___y_473_;
v___y_469_ = v___y_472_;
v___y_470_ = v___x_463_;
goto v___jp_467_;
}
else
{
v___y_468_ = v___y_473_;
v___y_469_ = v___y_472_;
v___y_470_ = v___y_472_;
goto v___jp_467_;
}
}
v___jp_478_:
{
if (v___y_479_ == 0)
{
uint32_t v___x_480_; uint32_t v___x_481_; uint32_t v___x_482_; uint8_t v___x_483_; 
v___x_480_ = 2147483648;
v___x_481_ = lean_uint32_land(v___y_73_, v___x_480_);
v___x_482_ = 0;
v___x_483_ = lean_uint32_dec_eq(v___x_481_, v___x_482_);
if (v___x_483_ == 0)
{
v___y_472_ = v___y_479_;
v___y_473_ = v___x_463_;
goto v___jp_471_;
}
else
{
v___y_472_ = v___y_479_;
v___y_473_ = v___y_479_;
goto v___jp_471_;
}
}
else
{
lean_object* v___x_484_; lean_object* v___x_485_; lean_object* v___x_486_; uint32_t v___x_487_; 
v___x_484_ = lean_uint32_to_nat(v___y_73_);
v___x_485_ = lean_uint32_to_nat(v___y_74_);
v___x_486_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_484_, v___x_485_);
v___x_487_ = lean_uint32_of_nat(v___x_486_);
lean_dec(v___x_486_);
return v___x_487_;
}
}
v___jp_488_:
{
uint8_t v___x_489_; 
v___x_489_ = lean_uint32_dec_eq(v_ey_417_, v___x_132_);
if (v___x_489_ == 0)
{
goto v___jp_75_;
}
else
{
if (v___x_463_ == 0)
{
uint32_t v___x_490_; 
v___x_490_ = lp_competition_Submission_FastMul_mul(v___y_73_, v___y_74_);
return v___x_490_;
}
else
{
goto v___jp_75_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_499_, lean_object* v___y_500_){
_start:
{
uint32_t v___y_3425__boxed_501_; uint32_t v___y_3426__boxed_502_; uint32_t v_res_503_; lean_object* v_r_504_; 
v___y_3425__boxed_501_ = lean_unbox_uint32(v___y_499_);
lean_dec(v___y_499_);
v___y_3426__boxed_502_ = lean_unbox_uint32(v___y_500_);
lean_dec(v___y_500_);
v_res_503_ = lp_competition_main___lam__1(v___y_3425__boxed_501_, v___y_3426__boxed_502_);
v_r_504_ = lean_box_uint32(v_res_503_);
return v_r_504_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_505_, uint32_t v___y_506_){
_start:
{
uint32_t v___y_513_; uint32_t v___y_514_; uint32_t v___y_515_; uint32_t v___y_519_; uint32_t v___y_520_; uint32_t v___y_521_; uint32_t v___y_525_; uint64_t v___y_529_; uint32_t v___y_530_; uint8_t v___y_531_; uint64_t v___y_532_; uint32_t v___y_544_; uint32_t v___y_548_; uint8_t v___y_549_; uint64_t v___y_550_; uint64_t v___y_551_; uint32_t v___x_562_; uint32_t v___x_563_; uint32_t v___x_564_; uint32_t v___y_566_; uint32_t v___y_567_; uint32_t v___y_568_; uint32_t v___y_569_; uint32_t v___y_576_; uint32_t v___y_577_; uint8_t v___y_578_; uint32_t v___y_579_; uint64_t v___y_583_; uint64_t v___y_584_; uint32_t v___y_585_; uint8_t v___y_586_; uint64_t v___y_587_; uint8_t v___y_597_; uint64_t v___y_598_; uint64_t v___y_599_; uint32_t v___y_600_; uint8_t v___y_601_; uint64_t v___y_602_; uint64_t v___y_609_; uint32_t v___y_610_; uint64_t v___y_611_; uint8_t v___y_612_; uint64_t v___y_613_; uint64_t v___y_619_; uint64_t v___y_620_; uint32_t v___y_621_; uint64_t v___y_622_; uint8_t v___y_623_; uint64_t v___y_624_; uint64_t v___y_679_; uint64_t v___y_680_; uint32_t v___y_681_; uint64_t v___y_682_; uint64_t v___y_683_; uint8_t v___y_684_; uint64_t v___y_685_; uint64_t v___y_691_; uint64_t v___y_692_; uint64_t v___y_693_; uint64_t v___y_694_; uint64_t v___y_695_; uint32_t v___y_696_; uint64_t v___y_697_; uint8_t v___y_698_; uint64_t v___y_699_; uint64_t v___y_704_; uint64_t v___y_705_; uint64_t v___y_706_; uint32_t v___y_707_; uint64_t v___y_708_; uint8_t v___y_709_; uint64_t v___y_710_; uint64_t v___y_715_; uint64_t v___y_716_; uint64_t v___y_717_; uint64_t v___y_718_; uint32_t v___y_719_; uint64_t v___y_720_; uint64_t v___y_721_; uint8_t v___y_722_; uint64_t v___y_723_; uint64_t v___y_728_; uint64_t v___y_729_; uint32_t v___y_730_; uint64_t v___y_731_; uint8_t v___y_732_; uint64_t v___y_733_; uint64_t v___y_734_; uint64_t v___y_739_; uint64_t v___y_740_; uint64_t v___y_741_; uint64_t v___y_742_; uint32_t v___y_743_; uint64_t v___y_744_; uint64_t v___y_745_; uint8_t v___y_746_; uint64_t v___y_747_; uint64_t v___y_752_; uint64_t v___y_753_; uint32_t v___y_754_; uint64_t v___y_755_; uint64_t v___y_756_; uint8_t v___y_757_; uint64_t v___y_758_; uint64_t v___y_763_; uint64_t v___y_764_; uint64_t v___y_765_; uint64_t v___y_766_; uint32_t v___y_767_; uint64_t v___y_768_; uint64_t v___y_769_; uint8_t v___y_770_; uint64_t v___y_771_; uint64_t v___y_776_; uint64_t v___y_777_; uint64_t v___y_778_; uint32_t v___y_779_; uint64_t v___y_780_; uint8_t v___y_781_; uint64_t v___y_782_; uint64_t v___y_787_; uint64_t v___y_788_; uint64_t v___y_789_; uint32_t v___y_790_; uint64_t v___y_791_; uint8_t v___y_792_; uint64_t v___y_793_; uint64_t v___y_797_; uint32_t v___y_798_; uint64_t v___y_799_; uint8_t v___y_800_; uint32_t v___y_809_; uint64_t v___y_810_; uint8_t v___y_811_; uint64_t v___y_812_; uint64_t v___y_813_; uint64_t v___y_814_; uint32_t v_ex_847_; uint32_t v___x_848_; uint32_t v_ey_849_; uint64_t v___y_851_; uint32_t v___y_852_; uint64_t v___y_853_; uint8_t v___y_854_; uint64_t v___y_855_; uint32_t v___y_862_; uint64_t v___y_863_; uint8_t v___y_864_; uint64_t v___y_865_; uint32_t v___y_872_; uint32_t v___y_873_; uint8_t v___y_874_; uint64_t v___y_875_; uint8_t v___y_883_; uint32_t v___x_893_; uint32_t v___x_894_; uint8_t v___x_895_; uint8_t v___y_897_; uint8_t v___y_898_; uint8_t v___y_900_; uint8_t v___y_901_; uint8_t v___y_902_; uint8_t v___y_904_; uint8_t v___y_905_; uint8_t v___y_911_; 
v___x_562_ = 23;
v___x_563_ = lean_uint32_shift_right(v___y_505_, v___x_562_);
v___x_564_ = 255;
v_ex_847_ = lean_uint32_land(v___x_563_, v___x_564_);
v___x_848_ = lean_uint32_shift_right(v___y_506_, v___x_562_);
v_ey_849_ = lean_uint32_land(v___x_848_, v___x_564_);
v___x_893_ = lean_uint32_add(v_ex_847_, v_ey_849_);
v___x_894_ = 128;
v___x_895_ = lean_uint32_dec_lt(v___x_893_, v___x_894_);
if (v___x_895_ == 0)
{
uint8_t v___x_923_; 
v___x_923_ = lean_uint32_dec_eq(v_ex_847_, v___x_564_);
if (v___x_923_ == 0)
{
goto v___jp_920_;
}
else
{
if (v___x_895_ == 0)
{
uint32_t v___x_924_; 
v___x_924_ = lp_competition_Submission_FastMul_mul(v___y_505_, v___y_506_);
return v___x_924_;
}
else
{
goto v___jp_920_;
}
}
}
else
{
uint32_t v___x_925_; uint32_t v___x_926_; uint32_t v___x_927_; uint8_t v___x_928_; 
v___x_925_ = 4278190080;
v___x_926_ = 1;
v___x_927_ = lean_uint32_shift_left(v___y_505_, v___x_926_);
v___x_928_ = lean_uint32_dec_le(v___x_925_, v___x_927_);
if (v___x_928_ == 0)
{
uint32_t v___x_929_; uint8_t v___x_930_; 
v___x_929_ = lean_uint32_shift_left(v___y_506_, v___x_926_);
v___x_930_ = lean_uint32_dec_le(v___x_925_, v___x_929_);
v___y_911_ = v___x_930_;
goto v___jp_910_;
}
else
{
v___y_911_ = v___x_928_;
goto v___jp_910_;
}
}
v___jp_507_:
{
float v___x_508_; float v___x_509_; float v___x_510_; uint32_t v___x_511_; 
v___x_508_ = lean_float32_of_bits(v___y_505_);
v___x_509_ = lean_float32_of_bits(v___y_506_);
v___x_510_ = lean_float32_mul(v___x_508_, v___x_509_);
v___x_511_ = lean_float32_to_bits(v___x_510_);
return v___x_511_;
}
v___jp_512_:
{
uint32_t v___x_516_; uint32_t v___x_517_; 
v___x_516_ = lean_uint32_land(v___y_513_, v___y_514_);
v___x_517_ = lean_uint32_lor(v___y_515_, v___x_516_);
return v___x_517_;
}
v___jp_518_:
{
uint32_t v___x_522_; uint32_t v___x_523_; 
v___x_522_ = lean_uint32_land(v___y_519_, v___y_520_);
v___x_523_ = lean_uint32_lor(v___y_521_, v___x_522_);
return v___x_523_;
}
v___jp_524_:
{
uint32_t v___x_526_; uint32_t v___x_527_; 
v___x_526_ = 8388608;
v___x_527_ = lean_uint32_lor(v___y_525_, v___x_526_);
return v___x_527_;
}
v___jp_528_:
{
uint8_t v___x_533_; 
v___x_533_ = lean_uint64_dec_eq(v___y_532_, v___y_529_);
if (v___x_533_ == 0)
{
uint64_t v___x_534_; uint8_t v___x_535_; 
v___x_534_ = 8388608ULL;
v___x_535_ = lean_uint64_dec_eq(v___y_532_, v___x_534_);
if (v___x_535_ == 0)
{
uint32_t v___x_536_; 
v___x_536_ = lean_uint64_to_uint32(v___y_532_);
if (v___y_531_ == 0)
{
uint32_t v___x_537_; 
v___x_537_ = 0;
v___y_519_ = v___x_536_;
v___y_520_ = v___y_530_;
v___y_521_ = v___x_537_;
goto v___jp_518_;
}
else
{
uint32_t v___x_538_; 
v___x_538_ = 2147483648;
v___y_519_ = v___x_536_;
v___y_520_ = v___y_530_;
v___y_521_ = v___x_538_;
goto v___jp_518_;
}
}
else
{
if (v___y_531_ == 0)
{
uint32_t v___x_539_; 
v___x_539_ = 0;
v___y_525_ = v___x_539_;
goto v___jp_524_;
}
else
{
uint32_t v___x_540_; 
v___x_540_ = 2147483648;
v___y_525_ = v___x_540_;
goto v___jp_524_;
}
}
}
else
{
if (v___y_531_ == 0)
{
uint32_t v___x_541_; 
v___x_541_ = 0;
return v___x_541_;
}
else
{
uint32_t v___x_542_; 
v___x_542_ = 2147483648;
return v___x_542_;
}
}
}
v___jp_543_:
{
uint32_t v___x_545_; uint32_t v___x_546_; 
v___x_545_ = 8388608;
v___x_546_ = lean_uint32_lor(v___y_544_, v___x_545_);
return v___x_546_;
}
v___jp_547_:
{
uint8_t v___x_552_; 
v___x_552_ = lean_uint64_dec_eq(v___y_551_, v___y_550_);
if (v___x_552_ == 0)
{
uint64_t v___x_553_; uint8_t v___x_554_; 
v___x_553_ = 8388608ULL;
v___x_554_ = lean_uint64_dec_eq(v___y_551_, v___x_553_);
if (v___x_554_ == 0)
{
uint32_t v___x_555_; 
v___x_555_ = lean_uint64_to_uint32(v___y_551_);
if (v___y_549_ == 0)
{
uint32_t v___x_556_; 
v___x_556_ = 0;
v___y_513_ = v___x_555_;
v___y_514_ = v___y_548_;
v___y_515_ = v___x_556_;
goto v___jp_512_;
}
else
{
uint32_t v___x_557_; 
v___x_557_ = 2147483648;
v___y_513_ = v___x_555_;
v___y_514_ = v___y_548_;
v___y_515_ = v___x_557_;
goto v___jp_512_;
}
}
else
{
if (v___y_549_ == 0)
{
uint32_t v___x_558_; 
v___x_558_ = 0;
v___y_544_ = v___x_558_;
goto v___jp_543_;
}
else
{
uint32_t v___x_559_; 
v___x_559_ = 2147483648;
v___y_544_ = v___x_559_;
goto v___jp_543_;
}
}
}
else
{
if (v___y_549_ == 0)
{
uint32_t v___x_560_; 
v___x_560_ = 0;
return v___x_560_;
}
else
{
uint32_t v___x_561_; 
v___x_561_ = 2147483648;
return v___x_561_;
}
}
}
v___jp_565_:
{
uint32_t v___x_570_; uint32_t v___x_571_; uint32_t v___x_572_; uint32_t v___x_573_; uint32_t v___x_574_; 
v___x_570_ = lean_uint32_land(v___y_566_, v___x_564_);
v___x_571_ = lean_uint32_shift_left(v___x_570_, v___x_562_);
v___x_572_ = lean_uint32_lor(v___y_569_, v___x_571_);
v___x_573_ = lean_uint32_land(v___y_567_, v___y_568_);
v___x_574_ = lean_uint32_lor(v___x_572_, v___x_573_);
return v___x_574_;
}
v___jp_575_:
{
if (v___y_578_ == 0)
{
uint32_t v___x_580_; 
v___x_580_ = 0;
v___y_566_ = v___y_576_;
v___y_567_ = v___y_579_;
v___y_568_ = v___y_577_;
v___y_569_ = v___x_580_;
goto v___jp_565_;
}
else
{
uint32_t v___x_581_; 
v___x_581_ = 2147483648;
v___y_566_ = v___y_576_;
v___y_567_ = v___y_579_;
v___y_568_ = v___y_577_;
v___y_569_ = v___x_581_;
goto v___jp_565_;
}
}
v___jp_582_:
{
uint64_t v___x_588_; uint64_t v_encodedExponent_589_; uint32_t v___x_590_; uint64_t v___x_591_; uint8_t v___x_592_; 
v___x_588_ = 171ULL;
v_encodedExponent_589_ = lean_uint64_sub(v___y_584_, v___x_588_);
v___x_590_ = lean_uint64_to_uint32(v_encodedExponent_589_);
v___x_591_ = 8388608ULL;
v___x_592_ = lean_uint64_dec_lt(v___y_587_, v___x_591_);
if (v___x_592_ == 0)
{
uint64_t v___x_593_; uint32_t v___x_594_; 
v___x_593_ = lean_uint64_sub(v___y_587_, v___x_591_);
v___x_594_ = lean_uint64_to_uint32(v___x_593_);
v___y_576_ = v___x_590_;
v___y_577_ = v___y_585_;
v___y_578_ = v___y_586_;
v___y_579_ = v___x_594_;
goto v___jp_575_;
}
else
{
uint32_t v___x_595_; 
v___x_595_ = lean_uint64_to_uint32(v___y_583_);
v___y_576_ = v___x_590_;
v___y_577_ = v___y_585_;
v___y_578_ = v___y_586_;
v___y_579_ = v___x_595_;
goto v___jp_575_;
}
}
v___jp_596_:
{
uint64_t v___x_603_; uint8_t v___x_604_; 
v___x_603_ = 425ULL;
v___x_604_ = lean_uint64_dec_lt(v___x_603_, v___y_602_);
if (v___x_604_ == 0)
{
if (v___y_597_ == 0)
{
v___y_583_ = v___y_598_;
v___y_584_ = v___y_602_;
v___y_585_ = v___y_600_;
v___y_586_ = v___y_601_;
v___y_587_ = v___y_599_;
goto v___jp_582_;
}
else
{
uint64_t v___x_605_; 
v___x_605_ = 8388608ULL;
v___y_583_ = v___y_598_;
v___y_584_ = v___y_602_;
v___y_585_ = v___y_600_;
v___y_586_ = v___y_601_;
v___y_587_ = v___x_605_;
goto v___jp_582_;
}
}
else
{
if (v___y_601_ == 0)
{
uint32_t v___x_606_; 
v___x_606_ = 2139095040;
return v___x_606_;
}
else
{
uint32_t v___x_607_; 
v___x_607_ = 4286578688;
return v___x_607_;
}
}
}
v___jp_608_:
{
uint64_t v___x_614_; uint8_t v_carry_615_; 
v___x_614_ = 16777216ULL;
v_carry_615_ = lean_uint64_dec_eq(v___y_613_, v___x_614_);
if (v_carry_615_ == 0)
{
v___y_597_ = v_carry_615_;
v___y_598_ = v___y_609_;
v___y_599_ = v___y_613_;
v___y_600_ = v___y_610_;
v___y_601_ = v___y_612_;
v___y_602_ = v___y_611_;
goto v___jp_596_;
}
else
{
uint64_t v___x_616_; uint64_t v___x_617_; 
v___x_616_ = 1ULL;
v___x_617_ = lean_uint64_add(v___y_611_, v___x_616_);
v___y_597_ = v_carry_615_;
v___y_598_ = v___y_609_;
v___y_599_ = v___y_613_;
v___y_600_ = v___y_610_;
v___y_601_ = v___y_612_;
v___y_602_ = v___x_617_;
goto v___jp_596_;
}
}
v___jp_618_:
{
uint64_t v_position_625_; uint64_t v___x_626_; uint8_t v___x_627_; 
v_position_625_ = lean_uint64_add(v___y_624_, v___y_620_);
v___x_626_ = 172ULL;
v___x_627_ = lean_uint64_dec_lt(v_position_625_, v___x_626_);
if (v___x_627_ == 0)
{
uint64_t v___x_628_; uint8_t v___x_629_; 
v___x_628_ = 23ULL;
v___x_629_ = lean_uint64_dec_lt(v___y_624_, v___x_628_);
if (v___x_629_ == 0)
{
uint64_t v___x_630_; uint8_t v___x_631_; 
v___x_630_ = lean_uint64_sub(v___y_624_, v___x_628_);
v___x_631_ = lean_uint64_dec_eq(v___x_630_, v___y_619_);
if (v___x_631_ == 0)
{
uint64_t v___x_632_; uint8_t v___x_633_; 
v___x_632_ = 64ULL;
v___x_633_ = lean_uint64_dec_lt(v___x_630_, v___x_632_);
if (v___x_633_ == 0)
{
uint8_t v___x_634_; 
v___x_634_ = lean_uint64_dec_eq(v___x_630_, v___x_632_);
if (v___x_634_ == 0)
{
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v___y_619_;
goto v___jp_608_;
}
else
{
uint64_t v___x_635_; uint8_t v___x_636_; 
v___x_635_ = 9223372036854775808ULL;
v___x_636_ = lean_uint64_dec_lt(v___x_635_, v___y_622_);
if (v___x_636_ == 0)
{
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v___y_619_;
goto v___jp_608_;
}
else
{
uint64_t v___x_637_; 
v___x_637_ = 1ULL;
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v___x_637_;
goto v___jp_608_;
}
}
}
else
{
uint64_t v_quotient_638_; uint64_t v___x_639_; uint64_t v___x_640_; uint64_t v___x_641_; uint64_t v_remainder_642_; uint64_t v___x_643_; uint64_t v_half_644_; uint8_t v___x_645_; 
v_quotient_638_ = lean_uint64_shift_right(v___y_622_, v___x_630_);
v___x_639_ = 1ULL;
v___x_640_ = lean_uint64_shift_left(v___x_639_, v___x_630_);
v___x_641_ = lean_uint64_sub(v___x_640_, v___x_639_);
v_remainder_642_ = lean_uint64_land(v___y_622_, v___x_641_);
v___x_643_ = lean_uint64_sub(v___x_630_, v___x_639_);
v_half_644_ = lean_uint64_shift_left(v___x_639_, v___x_643_);
v___x_645_ = lean_uint64_dec_lt(v_remainder_642_, v_half_644_);
if (v___x_645_ == 0)
{
uint8_t v___x_646_; 
v___x_646_ = lean_uint64_dec_lt(v_half_644_, v_remainder_642_);
if (v___x_646_ == 0)
{
uint64_t v___x_647_; uint8_t v___x_648_; 
v___x_647_ = lean_uint64_land(v_quotient_638_, v___x_639_);
v___x_648_ = lean_uint64_dec_eq(v___x_647_, v___y_619_);
if (v___x_648_ == 0)
{
uint64_t v___x_649_; 
v___x_649_ = lean_uint64_add(v_quotient_638_, v___x_639_);
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v___x_649_;
goto v___jp_608_;
}
else
{
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v_quotient_638_;
goto v___jp_608_;
}
}
else
{
uint64_t v___x_650_; 
v___x_650_ = lean_uint64_add(v_quotient_638_, v___x_639_);
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v___x_650_;
goto v___jp_608_;
}
}
else
{
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v_quotient_638_;
goto v___jp_608_;
}
}
}
else
{
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v___y_622_;
goto v___jp_608_;
}
}
else
{
uint64_t v___x_651_; uint64_t v___x_652_; 
v___x_651_ = lean_uint64_sub(v___x_628_, v___y_624_);
v___x_652_ = lean_uint64_shift_left(v___y_622_, v___x_651_);
v___y_609_ = v___y_619_;
v___y_610_ = v___y_621_;
v___y_611_ = v_position_625_;
v___y_612_ = v___y_623_;
v___y_613_ = v___x_652_;
goto v___jp_608_;
}
}
else
{
uint64_t v___x_653_; uint8_t v___x_654_; 
v___x_653_ = 149ULL;
v___x_654_ = lean_uint64_dec_lt(v___y_620_, v___x_653_);
if (v___x_654_ == 0)
{
uint64_t v___x_655_; uint64_t v___x_656_; 
v___x_655_ = lean_uint64_sub(v___y_620_, v___x_653_);
v___x_656_ = lean_uint64_shift_left(v___y_622_, v___x_655_);
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v___x_656_;
goto v___jp_528_;
}
else
{
uint64_t v___x_657_; uint8_t v___x_658_; 
v___x_657_ = lean_uint64_sub(v___x_653_, v___y_620_);
v___x_658_ = lean_uint64_dec_eq(v___x_657_, v___y_619_);
if (v___x_658_ == 0)
{
uint64_t v___x_659_; uint8_t v___x_660_; 
v___x_659_ = 64ULL;
v___x_660_ = lean_uint64_dec_lt(v___x_657_, v___x_659_);
if (v___x_660_ == 0)
{
uint8_t v___x_661_; 
v___x_661_ = lean_uint64_dec_eq(v___x_657_, v___x_659_);
if (v___x_661_ == 0)
{
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v___y_619_;
goto v___jp_528_;
}
else
{
uint64_t v___x_662_; uint8_t v___x_663_; 
v___x_662_ = 9223372036854775808ULL;
v___x_663_ = lean_uint64_dec_lt(v___x_662_, v___y_622_);
if (v___x_663_ == 0)
{
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v___y_619_;
goto v___jp_528_;
}
else
{
uint64_t v___x_664_; 
v___x_664_ = 1ULL;
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v___x_664_;
goto v___jp_528_;
}
}
}
else
{
uint64_t v_quotient_665_; uint64_t v___x_666_; uint64_t v___x_667_; uint64_t v___x_668_; uint64_t v_remainder_669_; uint64_t v___x_670_; uint64_t v_half_671_; uint8_t v___x_672_; 
v_quotient_665_ = lean_uint64_shift_right(v___y_622_, v___x_657_);
v___x_666_ = 1ULL;
v___x_667_ = lean_uint64_shift_left(v___x_666_, v___x_657_);
v___x_668_ = lean_uint64_sub(v___x_667_, v___x_666_);
v_remainder_669_ = lean_uint64_land(v___y_622_, v___x_668_);
v___x_670_ = lean_uint64_sub(v___x_657_, v___x_666_);
v_half_671_ = lean_uint64_shift_left(v___x_666_, v___x_670_);
v___x_672_ = lean_uint64_dec_lt(v_remainder_669_, v_half_671_);
if (v___x_672_ == 0)
{
uint8_t v___x_673_; 
v___x_673_ = lean_uint64_dec_lt(v_half_671_, v_remainder_669_);
if (v___x_673_ == 0)
{
uint64_t v___x_674_; uint8_t v___x_675_; 
v___x_674_ = lean_uint64_land(v_quotient_665_, v___x_666_);
v___x_675_ = lean_uint64_dec_eq(v___x_674_, v___y_619_);
if (v___x_675_ == 0)
{
uint64_t v___x_676_; 
v___x_676_ = lean_uint64_add(v_quotient_665_, v___x_666_);
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v___x_676_;
goto v___jp_528_;
}
else
{
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v_quotient_665_;
goto v___jp_528_;
}
}
else
{
uint64_t v___x_677_; 
v___x_677_ = lean_uint64_add(v_quotient_665_, v___x_666_);
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v___x_677_;
goto v___jp_528_;
}
}
else
{
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v_quotient_665_;
goto v___jp_528_;
}
}
}
else
{
v___y_529_ = v___y_619_;
v___y_530_ = v___y_621_;
v___y_531_ = v___y_623_;
v___y_532_ = v___y_622_;
goto v___jp_528_;
}
}
}
}
v___jp_678_:
{
uint64_t v___x_686_; uint64_t v___x_687_; uint8_t v___x_688_; 
v___x_686_ = 1ULL;
v___x_687_ = lean_uint64_shift_right(v___y_682_, v___x_686_);
v___x_688_ = lean_uint64_dec_eq(v___x_687_, v___y_679_);
if (v___x_688_ == 0)
{
uint64_t v___x_689_; 
v___x_689_ = lean_uint64_add(v___y_685_, v___x_686_);
v___y_619_ = v___y_679_;
v___y_620_ = v___y_680_;
v___y_621_ = v___y_681_;
v___y_622_ = v___y_683_;
v___y_623_ = v___y_684_;
v___y_624_ = v___x_689_;
goto v___jp_618_;
}
else
{
v___y_619_ = v___y_679_;
v___y_620_ = v___y_680_;
v___y_621_ = v___y_681_;
v___y_622_ = v___y_683_;
v___y_623_ = v___y_684_;
v___y_624_ = v___y_685_;
goto v___jp_618_;
}
}
v___jp_690_:
{
uint64_t v___x_700_; uint8_t v___x_701_; 
v___x_700_ = lean_uint64_shift_right(v___y_692_, v___y_695_);
v___x_701_ = lean_uint64_dec_eq(v___x_700_, v___y_693_);
if (v___x_701_ == 0)
{
uint64_t v___x_702_; 
v___x_702_ = lean_uint64_add(v___y_691_, v___y_695_);
v___y_679_ = v___y_693_;
v___y_680_ = v___y_694_;
v___y_681_ = v___y_696_;
v___y_682_ = v___y_699_;
v___y_683_ = v___y_697_;
v___y_684_ = v___y_698_;
v___y_685_ = v___x_702_;
goto v___jp_678_;
}
else
{
v___y_679_ = v___y_693_;
v___y_680_ = v___y_694_;
v___y_681_ = v___y_696_;
v___y_682_ = v___y_699_;
v___y_683_ = v___y_697_;
v___y_684_ = v___y_698_;
v___y_685_ = v___y_691_;
goto v___jp_678_;
}
}
v___jp_703_:
{
uint64_t v___x_711_; uint64_t v___x_712_; uint8_t v___x_713_; 
v___x_711_ = 2ULL;
v___x_712_ = lean_uint64_shift_right(v___y_705_, v___x_711_);
v___x_713_ = lean_uint64_dec_eq(v___x_712_, v___y_704_);
if (v___x_713_ == 0)
{
v___y_691_ = v___y_710_;
v___y_692_ = v___y_705_;
v___y_693_ = v___y_704_;
v___y_694_ = v___y_706_;
v___y_695_ = v___x_711_;
v___y_696_ = v___y_707_;
v___y_697_ = v___y_708_;
v___y_698_ = v___y_709_;
v___y_699_ = v___x_712_;
goto v___jp_690_;
}
else
{
v___y_691_ = v___y_710_;
v___y_692_ = v___y_705_;
v___y_693_ = v___y_704_;
v___y_694_ = v___y_706_;
v___y_695_ = v___x_711_;
v___y_696_ = v___y_707_;
v___y_697_ = v___y_708_;
v___y_698_ = v___y_709_;
v___y_699_ = v___y_705_;
goto v___jp_690_;
}
}
v___jp_714_:
{
uint64_t v___x_724_; uint8_t v___x_725_; 
v___x_724_ = lean_uint64_shift_right(v___y_721_, v___y_715_);
v___x_725_ = lean_uint64_dec_eq(v___x_724_, v___y_717_);
if (v___x_725_ == 0)
{
uint64_t v___x_726_; 
v___x_726_ = lean_uint64_add(v___y_716_, v___y_715_);
v___y_704_ = v___y_717_;
v___y_705_ = v___y_723_;
v___y_706_ = v___y_718_;
v___y_707_ = v___y_719_;
v___y_708_ = v___y_720_;
v___y_709_ = v___y_722_;
v___y_710_ = v___x_726_;
goto v___jp_703_;
}
else
{
v___y_704_ = v___y_717_;
v___y_705_ = v___y_723_;
v___y_706_ = v___y_718_;
v___y_707_ = v___y_719_;
v___y_708_ = v___y_720_;
v___y_709_ = v___y_722_;
v___y_710_ = v___y_716_;
goto v___jp_703_;
}
}
v___jp_727_:
{
uint64_t v___x_735_; uint64_t v___x_736_; uint8_t v___x_737_; 
v___x_735_ = 4ULL;
v___x_736_ = lean_uint64_shift_right(v___y_733_, v___x_735_);
v___x_737_ = lean_uint64_dec_eq(v___x_736_, v___y_728_);
if (v___x_737_ == 0)
{
v___y_715_ = v___x_735_;
v___y_716_ = v___y_734_;
v___y_717_ = v___y_728_;
v___y_718_ = v___y_729_;
v___y_719_ = v___y_730_;
v___y_720_ = v___y_731_;
v___y_721_ = v___y_733_;
v___y_722_ = v___y_732_;
v___y_723_ = v___x_736_;
goto v___jp_714_;
}
else
{
v___y_715_ = v___x_735_;
v___y_716_ = v___y_734_;
v___y_717_ = v___y_728_;
v___y_718_ = v___y_729_;
v___y_719_ = v___y_730_;
v___y_720_ = v___y_731_;
v___y_721_ = v___y_733_;
v___y_722_ = v___y_732_;
v___y_723_ = v___y_733_;
goto v___jp_714_;
}
}
v___jp_738_:
{
uint64_t v___x_748_; uint8_t v___x_749_; 
v___x_748_ = lean_uint64_shift_right(v___y_744_, v___y_741_);
v___x_749_ = lean_uint64_dec_eq(v___x_748_, v___y_739_);
if (v___x_749_ == 0)
{
uint64_t v___x_750_; 
v___x_750_ = lean_uint64_add(v___y_740_, v___y_741_);
v___y_728_ = v___y_739_;
v___y_729_ = v___y_742_;
v___y_730_ = v___y_743_;
v___y_731_ = v___y_745_;
v___y_732_ = v___y_746_;
v___y_733_ = v___y_747_;
v___y_734_ = v___x_750_;
goto v___jp_727_;
}
else
{
v___y_728_ = v___y_739_;
v___y_729_ = v___y_742_;
v___y_730_ = v___y_743_;
v___y_731_ = v___y_745_;
v___y_732_ = v___y_746_;
v___y_733_ = v___y_747_;
v___y_734_ = v___y_740_;
goto v___jp_727_;
}
}
v___jp_751_:
{
uint64_t v___x_759_; uint64_t v___x_760_; uint8_t v___x_761_; 
v___x_759_ = 8ULL;
v___x_760_ = lean_uint64_shift_right(v___y_756_, v___x_759_);
v___x_761_ = lean_uint64_dec_eq(v___x_760_, v___y_752_);
if (v___x_761_ == 0)
{
v___y_739_ = v___y_752_;
v___y_740_ = v___y_758_;
v___y_741_ = v___x_759_;
v___y_742_ = v___y_753_;
v___y_743_ = v___y_754_;
v___y_744_ = v___y_756_;
v___y_745_ = v___y_755_;
v___y_746_ = v___y_757_;
v___y_747_ = v___x_760_;
goto v___jp_738_;
}
else
{
v___y_739_ = v___y_752_;
v___y_740_ = v___y_758_;
v___y_741_ = v___x_759_;
v___y_742_ = v___y_753_;
v___y_743_ = v___y_754_;
v___y_744_ = v___y_756_;
v___y_745_ = v___y_755_;
v___y_746_ = v___y_757_;
v___y_747_ = v___y_756_;
goto v___jp_738_;
}
}
v___jp_762_:
{
uint64_t v___x_772_; uint8_t v___x_773_; 
v___x_772_ = lean_uint64_shift_right(v___y_766_, v___y_764_);
v___x_773_ = lean_uint64_dec_eq(v___x_772_, v___y_763_);
if (v___x_773_ == 0)
{
uint64_t v___x_774_; 
v___x_774_ = lean_uint64_add(v___y_768_, v___y_764_);
v___y_752_ = v___y_763_;
v___y_753_ = v___y_765_;
v___y_754_ = v___y_767_;
v___y_755_ = v___y_769_;
v___y_756_ = v___y_771_;
v___y_757_ = v___y_770_;
v___y_758_ = v___x_774_;
goto v___jp_751_;
}
else
{
v___y_752_ = v___y_763_;
v___y_753_ = v___y_765_;
v___y_754_ = v___y_767_;
v___y_755_ = v___y_769_;
v___y_756_ = v___y_771_;
v___y_757_ = v___y_770_;
v___y_758_ = v___y_768_;
goto v___jp_751_;
}
}
v___jp_775_:
{
uint64_t v___x_783_; uint64_t v___x_784_; uint8_t v___x_785_; 
v___x_783_ = 16ULL;
v___x_784_ = lean_uint64_shift_right(v___y_778_, v___x_783_);
v___x_785_ = lean_uint64_dec_eq(v___x_784_, v___y_776_);
if (v___x_785_ == 0)
{
v___y_763_ = v___y_776_;
v___y_764_ = v___x_783_;
v___y_765_ = v___y_777_;
v___y_766_ = v___y_778_;
v___y_767_ = v___y_779_;
v___y_768_ = v___y_782_;
v___y_769_ = v___y_780_;
v___y_770_ = v___y_781_;
v___y_771_ = v___x_784_;
goto v___jp_762_;
}
else
{
v___y_763_ = v___y_776_;
v___y_764_ = v___x_783_;
v___y_765_ = v___y_777_;
v___y_766_ = v___y_778_;
v___y_767_ = v___y_779_;
v___y_768_ = v___y_782_;
v___y_769_ = v___y_780_;
v___y_770_ = v___y_781_;
v___y_771_ = v___y_778_;
goto v___jp_762_;
}
}
v___jp_786_:
{
uint64_t v___x_794_; uint8_t v___x_795_; 
v___x_794_ = lean_uint64_shift_right(v___y_791_, v___y_789_);
v___x_795_ = lean_uint64_dec_eq(v___x_794_, v___y_787_);
if (v___x_795_ == 0)
{
v___y_776_ = v___y_787_;
v___y_777_ = v___y_788_;
v___y_778_ = v___y_793_;
v___y_779_ = v___y_790_;
v___y_780_ = v___y_791_;
v___y_781_ = v___y_792_;
v___y_782_ = v___y_789_;
goto v___jp_775_;
}
else
{
v___y_776_ = v___y_787_;
v___y_777_ = v___y_788_;
v___y_778_ = v___y_793_;
v___y_779_ = v___y_790_;
v___y_780_ = v___y_791_;
v___y_781_ = v___y_792_;
v___y_782_ = v___y_787_;
goto v___jp_775_;
}
}
v___jp_796_:
{
uint64_t v___x_801_; uint8_t v___x_802_; 
v___x_801_ = 0ULL;
v___x_802_ = lean_uint64_dec_eq(v___y_799_, v___x_801_);
if (v___x_802_ == 0)
{
uint64_t v___x_803_; uint64_t v___x_804_; uint8_t v___x_805_; 
v___x_803_ = 32ULL;
v___x_804_ = lean_uint64_shift_right(v___y_799_, v___x_803_);
v___x_805_ = lean_uint64_dec_eq(v___x_804_, v___x_801_);
if (v___x_805_ == 0)
{
v___y_787_ = v___x_801_;
v___y_788_ = v___y_797_;
v___y_789_ = v___x_803_;
v___y_790_ = v___y_798_;
v___y_791_ = v___y_799_;
v___y_792_ = v___y_800_;
v___y_793_ = v___x_804_;
goto v___jp_786_;
}
else
{
v___y_787_ = v___x_801_;
v___y_788_ = v___y_797_;
v___y_789_ = v___x_803_;
v___y_790_ = v___y_798_;
v___y_791_ = v___y_799_;
v___y_792_ = v___y_800_;
v___y_793_ = v___y_799_;
goto v___jp_786_;
}
}
else
{
if (v___y_800_ == 0)
{
uint32_t v___x_806_; 
v___x_806_ = 0;
return v___x_806_;
}
else
{
uint32_t v___x_807_; 
v___x_807_ = 2147483648;
return v___x_807_;
}
}
}
v___jp_808_:
{
uint64_t v___x_815_; uint64_t v___x_816_; uint64_t v___x_817_; uint8_t v___x_818_; 
v___x_815_ = lean_uint64_mul(v___y_810_, v___y_813_);
v___x_816_ = lean_uint64_add(v___y_812_, v___y_814_);
v___x_817_ = 281474976710656ULL;
v___x_818_ = lean_uint64_dec_lt(v___x_815_, v___x_817_);
if (v___x_818_ == 0)
{
v___y_797_ = v___x_816_;
v___y_798_ = v___y_809_;
v___y_799_ = v___x_815_;
v___y_800_ = v___y_811_;
goto v___jp_796_;
}
else
{
uint64_t v___x_819_; uint8_t v___x_820_; 
v___x_819_ = 123ULL;
v___x_820_ = lean_uint64_dec_le(v___x_816_, v___x_819_);
if (v___x_820_ == 0)
{
v___y_797_ = v___x_816_;
v___y_798_ = v___y_809_;
v___y_799_ = v___x_815_;
v___y_800_ = v___y_811_;
goto v___jp_796_;
}
else
{
uint64_t v___x_821_; uint8_t v___x_822_; 
v___x_821_ = 0ULL;
v___x_822_ = lean_uint64_dec_eq(v___x_815_, v___x_821_);
if (v___x_822_ == 0)
{
uint64_t v___x_823_; uint64_t v___x_824_; uint8_t v___x_825_; 
v___x_823_ = 149ULL;
v___x_824_ = lean_uint64_sub(v___x_823_, v___x_816_);
v___x_825_ = lean_uint64_dec_eq(v___x_824_, v___x_821_);
if (v___x_825_ == 0)
{
uint64_t v___x_826_; uint8_t v___x_827_; 
v___x_826_ = 64ULL;
v___x_827_ = lean_uint64_dec_lt(v___x_824_, v___x_826_);
if (v___x_827_ == 0)
{
uint8_t v___x_828_; 
v___x_828_ = lean_uint64_dec_eq(v___x_824_, v___x_826_);
if (v___x_828_ == 0)
{
v___y_548_ = v___y_809_;
v___y_549_ = v___y_811_;
v___y_550_ = v___x_821_;
v___y_551_ = v___x_821_;
goto v___jp_547_;
}
else
{
uint64_t v___x_829_; uint8_t v___x_830_; 
v___x_829_ = 9223372036854775808ULL;
v___x_830_ = lean_uint64_dec_lt(v___x_829_, v___x_815_);
if (v___x_830_ == 0)
{
v___y_548_ = v___y_809_;
v___y_549_ = v___y_811_;
v___y_550_ = v___x_821_;
v___y_551_ = v___x_821_;
goto v___jp_547_;
}
else
{
uint64_t v___x_831_; 
v___x_831_ = 1ULL;
v___y_548_ = v___y_809_;
v___y_549_ = v___y_811_;
v___y_550_ = v___x_821_;
v___y_551_ = v___x_831_;
goto v___jp_547_;
}
}
}
else
{
uint64_t v_quotient_832_; uint64_t v___x_833_; uint64_t v___x_834_; uint64_t v___x_835_; uint64_t v_remainder_836_; uint64_t v___x_837_; uint64_t v_half_838_; uint8_t v___x_839_; 
v_quotient_832_ = lean_uint64_shift_right(v___x_815_, v___x_824_);
v___x_833_ = 1ULL;
v___x_834_ = lean_uint64_shift_left(v___x_833_, v___x_824_);
v___x_835_ = lean_uint64_sub(v___x_834_, v___x_833_);
v_remainder_836_ = lean_uint64_land(v___x_815_, v___x_835_);
v___x_837_ = lean_uint64_sub(v___x_824_, v___x_833_);
v_half_838_ = lean_uint64_shift_left(v___x_833_, v___x_837_);
v___x_839_ = lean_uint64_dec_lt(v_remainder_836_, v_half_838_);
if (v___x_839_ == 0)
{
uint8_t v___x_840_; 
v___x_840_ = lean_uint64_dec_lt(v_half_838_, v_remainder_836_);
if (v___x_840_ == 0)
{
uint64_t v___x_841_; uint8_t v___x_842_; 
v___x_841_ = lean_uint64_land(v_quotient_832_, v___x_833_);
v___x_842_ = lean_uint64_dec_eq(v___x_841_, v___x_821_);
if (v___x_842_ == 0)
{
uint64_t v___x_843_; 
v___x_843_ = lean_uint64_add(v_quotient_832_, v___x_833_);
v___y_548_ = v___y_809_;
v___y_549_ = v___y_811_;
v___y_550_ = v___x_821_;
v___y_551_ = v___x_843_;
goto v___jp_547_;
}
else
{
v___y_548_ = v___y_809_;
v___y_549_ = v___y_811_;
v___y_550_ = v___x_821_;
v___y_551_ = v_quotient_832_;
goto v___jp_547_;
}
}
else
{
uint64_t v___x_844_; 
v___x_844_ = lean_uint64_add(v_quotient_832_, v___x_833_);
v___y_548_ = v___y_809_;
v___y_549_ = v___y_811_;
v___y_550_ = v___x_821_;
v___y_551_ = v___x_844_;
goto v___jp_547_;
}
}
else
{
v___y_548_ = v___y_809_;
v___y_549_ = v___y_811_;
v___y_550_ = v___x_821_;
v___y_551_ = v_quotient_832_;
goto v___jp_547_;
}
}
}
else
{
v___y_548_ = v___y_809_;
v___y_549_ = v___y_811_;
v___y_550_ = v___x_821_;
v___y_551_ = v___x_815_;
goto v___jp_547_;
}
}
else
{
if (v___y_811_ == 0)
{
uint32_t v___x_845_; 
v___x_845_ = 0;
return v___x_845_;
}
else
{
uint32_t v___x_846_; 
v___x_846_ = 2147483648;
return v___x_846_;
}
}
}
}
}
v___jp_850_:
{
uint64_t v___x_856_; uint64_t v___x_857_; uint8_t v___x_858_; 
v___x_856_ = lean_uint32_to_uint64(v_ey_849_);
v___x_857_ = 0ULL;
v___x_858_ = lean_uint64_dec_eq(v___x_856_, v___x_857_);
if (v___x_858_ == 0)
{
uint64_t v___x_859_; uint64_t v___x_860_; 
v___x_859_ = 1ULL;
v___x_860_ = lean_uint64_sub(v___x_856_, v___x_859_);
v___y_809_ = v___y_852_;
v___y_810_ = v___y_851_;
v___y_811_ = v___y_854_;
v___y_812_ = v___y_855_;
v___y_813_ = v___y_853_;
v___y_814_ = v___x_860_;
goto v___jp_808_;
}
else
{
v___y_809_ = v___y_852_;
v___y_810_ = v___y_851_;
v___y_811_ = v___y_854_;
v___y_812_ = v___y_855_;
v___y_813_ = v___y_853_;
v___y_814_ = v___x_857_;
goto v___jp_808_;
}
}
v___jp_861_:
{
uint64_t v___x_866_; uint64_t v___x_867_; uint8_t v___x_868_; 
v___x_866_ = lean_uint32_to_uint64(v_ex_847_);
v___x_867_ = 0ULL;
v___x_868_ = lean_uint64_dec_eq(v___x_866_, v___x_867_);
if (v___x_868_ == 0)
{
uint64_t v___x_869_; uint64_t v___x_870_; 
v___x_869_ = 1ULL;
v___x_870_ = lean_uint64_sub(v___x_866_, v___x_869_);
v___y_851_ = v___y_863_;
v___y_852_ = v___y_862_;
v___y_853_ = v___y_865_;
v___y_854_ = v___y_864_;
v___y_855_ = v___x_870_;
goto v___jp_850_;
}
else
{
v___y_851_ = v___y_863_;
v___y_852_ = v___y_862_;
v___y_853_ = v___y_865_;
v___y_854_ = v___y_864_;
v___y_855_ = v___x_867_;
goto v___jp_850_;
}
}
v___jp_871_:
{
uint32_t v___x_876_; uint8_t v___x_877_; 
v___x_876_ = 0;
v___x_877_ = lean_uint32_dec_eq(v_ey_849_, v___x_876_);
if (v___x_877_ == 0)
{
uint64_t v___x_878_; uint64_t v___x_879_; uint64_t v___x_880_; 
v___x_878_ = lean_uint32_to_uint64(v___y_872_);
v___x_879_ = 8388608ULL;
v___x_880_ = lean_uint64_lor(v___x_878_, v___x_879_);
v___y_862_ = v___y_873_;
v___y_863_ = v___y_875_;
v___y_864_ = v___y_874_;
v___y_865_ = v___x_880_;
goto v___jp_861_;
}
else
{
uint64_t v___x_881_; 
v___x_881_ = lean_uint32_to_uint64(v___y_872_);
v___y_862_ = v___y_873_;
v___y_863_ = v___y_875_;
v___y_864_ = v___y_874_;
v___y_865_ = v___x_881_;
goto v___jp_861_;
}
}
v___jp_882_:
{
uint32_t v___x_884_; uint32_t v_xFraction_885_; uint32_t v_yFraction_886_; uint32_t v___x_887_; uint8_t v___x_888_; 
v___x_884_ = 8388607;
v_xFraction_885_ = lean_uint32_land(v___y_505_, v___x_884_);
v_yFraction_886_ = lean_uint32_land(v___y_506_, v___x_884_);
v___x_887_ = 0;
v___x_888_ = lean_uint32_dec_eq(v_ex_847_, v___x_887_);
if (v___x_888_ == 0)
{
uint64_t v___x_889_; uint64_t v___x_890_; uint64_t v___x_891_; 
v___x_889_ = lean_uint32_to_uint64(v_xFraction_885_);
v___x_890_ = 8388608ULL;
v___x_891_ = lean_uint64_lor(v___x_889_, v___x_890_);
v___y_872_ = v_yFraction_886_;
v___y_873_ = v___x_884_;
v___y_874_ = v___y_883_;
v___y_875_ = v___x_891_;
goto v___jp_871_;
}
else
{
uint64_t v___x_892_; 
v___x_892_ = lean_uint32_to_uint64(v_xFraction_885_);
v___y_872_ = v_yFraction_886_;
v___y_873_ = v___x_884_;
v___y_874_ = v___y_883_;
v___y_875_ = v___x_892_;
goto v___jp_871_;
}
}
v___jp_896_:
{
if (v___y_898_ == 0)
{
v___y_883_ = v___x_895_;
goto v___jp_882_;
}
else
{
v___y_883_ = v___y_897_;
goto v___jp_882_;
}
}
v___jp_899_:
{
if (v___y_900_ == 0)
{
if (v___y_902_ == 0)
{
v___y_897_ = v___y_901_;
v___y_898_ = v___x_895_;
goto v___jp_896_;
}
else
{
v___y_883_ = v___x_895_;
goto v___jp_882_;
}
}
else
{
v___y_897_ = v___y_901_;
v___y_898_ = v___y_902_;
goto v___jp_896_;
}
}
v___jp_903_:
{
uint32_t v___x_906_; uint32_t v___x_907_; uint32_t v___x_908_; uint8_t v___x_909_; 
v___x_906_ = 2147483648;
v___x_907_ = lean_uint32_land(v___y_506_, v___x_906_);
v___x_908_ = 0;
v___x_909_ = lean_uint32_dec_eq(v___x_907_, v___x_908_);
if (v___x_909_ == 0)
{
v___y_900_ = v___y_905_;
v___y_901_ = v___y_904_;
v___y_902_ = v___x_895_;
goto v___jp_899_;
}
else
{
v___y_900_ = v___y_905_;
v___y_901_ = v___y_904_;
v___y_902_ = v___y_904_;
goto v___jp_899_;
}
}
v___jp_910_:
{
if (v___y_911_ == 0)
{
uint32_t v___x_912_; uint32_t v___x_913_; uint32_t v___x_914_; uint8_t v___x_915_; 
v___x_912_ = 2147483648;
v___x_913_ = lean_uint32_land(v___y_505_, v___x_912_);
v___x_914_ = 0;
v___x_915_ = lean_uint32_dec_eq(v___x_913_, v___x_914_);
if (v___x_915_ == 0)
{
v___y_904_ = v___y_911_;
v___y_905_ = v___x_895_;
goto v___jp_903_;
}
else
{
v___y_904_ = v___y_911_;
v___y_905_ = v___y_911_;
goto v___jp_903_;
}
}
else
{
lean_object* v___x_916_; lean_object* v___x_917_; lean_object* v___x_918_; uint32_t v___x_919_; 
v___x_916_ = lean_uint32_to_nat(v___y_505_);
v___x_917_ = lean_uint32_to_nat(v___y_506_);
v___x_918_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_916_, v___x_917_);
v___x_919_ = lean_uint32_of_nat(v___x_918_);
lean_dec(v___x_918_);
return v___x_919_;
}
}
v___jp_920_:
{
uint8_t v___x_921_; 
v___x_921_ = lean_uint32_dec_eq(v_ey_849_, v___x_564_);
if (v___x_921_ == 0)
{
goto v___jp_507_;
}
else
{
if (v___x_895_ == 0)
{
uint32_t v___x_922_; 
v___x_922_ = lp_competition_Submission_FastMul_mul(v___y_505_, v___y_506_);
return v___x_922_;
}
else
{
goto v___jp_507_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_931_, lean_object* v___y_932_){
_start:
{
uint32_t v___y_4247__boxed_933_; uint32_t v___y_4248__boxed_934_; uint32_t v_res_935_; lean_object* v_r_936_; 
v___y_4247__boxed_933_ = lean_unbox_uint32(v___y_931_);
lean_dec(v___y_931_);
v___y_4248__boxed_934_ = lean_unbox_uint32(v___y_932_);
lean_dec(v___y_932_);
v_res_935_ = lp_competition_main___lam__3(v___y_4247__boxed_933_, v___y_4248__boxed_934_);
v_r_936_ = lean_box_uint32(v_res_935_);
return v_r_936_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_944_; lean_object* v___x_945_; 
v___x_944_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_945_ = lean_io_getenv(v___x_944_);
if (lean_obj_tag(v___x_945_) == 0)
{
lean_object* v___f_946_; lean_object* v___f_947_; lean_object* v___x_948_; lean_object* v___x_949_; lean_object* v___x_950_; 
v___f_946_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_947_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_948_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_949_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_950_ = lp_competition_Bench_runFull(v___f_946_, v___f_947_, v___x_948_, v___x_949_);
return v___x_950_;
}
else
{
lean_object* v___f_951_; lean_object* v___f_952_; lean_object* v___x_953_; lean_object* v___x_954_; lean_object* v___x_955_; 
lean_dec_ref_known(v___x_945_, 1);
v___f_951_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_952_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_953_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_954_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_955_ = lp_competition_Bench_Suite_run(v___f_951_, v___f_952_, v___x_953_, v___x_954_);
return v___x_955_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_956_){
_start:
{
lean_object* v_res_957_; 
v_res_957_ = _lean_main();
return v_res_957_;
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
