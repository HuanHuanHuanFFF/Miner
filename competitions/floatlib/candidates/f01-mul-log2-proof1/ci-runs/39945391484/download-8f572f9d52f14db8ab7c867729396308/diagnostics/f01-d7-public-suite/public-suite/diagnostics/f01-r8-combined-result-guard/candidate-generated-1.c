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
uint32_t v___y_3037__boxed_61_; uint32_t v___y_3038__boxed_62_; uint32_t v_res_63_; lean_object* v_r_64_; 
v___y_3037__boxed_61_ = lean_unbox_uint32(v___y_59_);
lean_dec(v___y_59_);
v___y_3038__boxed_62_ = lean_unbox_uint32(v___y_60_);
lean_dec(v___y_60_);
v_res_63_ = lp_competition_main___lam__0(v___y_3037__boxed_61_, v___y_3038__boxed_62_);
v_r_64_ = lean_box_uint32(v_res_63_);
return v_r_64_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_65_, uint32_t v___y_66_){
_start:
{
uint32_t v___y_68_; uint32_t v___y_72_; uint32_t v___y_76_; uint32_t v___y_77_; uint32_t v___y_78_; uint32_t v___y_82_; uint8_t v___y_83_; uint64_t v___y_84_; uint64_t v___y_85_; uint32_t v___y_97_; uint32_t v___y_98_; uint32_t v___y_99_; uint32_t v___y_103_; uint64_t v___y_104_; uint8_t v___y_105_; uint64_t v___y_106_; uint32_t v___x_117_; uint32_t v___x_118_; uint32_t v___x_119_; uint32_t v___y_121_; uint32_t v___y_122_; uint32_t v___y_123_; uint32_t v___y_124_; uint32_t v___y_131_; uint32_t v___y_132_; uint8_t v___y_133_; uint32_t v___y_134_; uint32_t v___y_138_; uint64_t v___y_139_; uint64_t v___y_140_; uint8_t v___y_141_; uint64_t v___y_142_; uint8_t v___y_152_; uint32_t v___y_153_; uint64_t v___y_154_; uint8_t v___y_155_; uint64_t v___y_156_; uint64_t v___y_157_; uint32_t v___y_164_; uint64_t v___y_165_; uint64_t v___y_166_; uint8_t v___y_167_; uint64_t v___y_168_; uint64_t v___y_174_; uint32_t v___y_175_; uint64_t v___y_176_; uint8_t v___y_177_; uint64_t v___y_178_; uint64_t v___y_179_; uint64_t v___y_234_; uint64_t v___y_235_; uint32_t v___y_236_; uint64_t v___y_237_; uint8_t v___y_238_; uint64_t v___y_239_; uint64_t v___y_240_; uint64_t v___y_246_; uint64_t v___y_247_; uint32_t v___y_248_; uint64_t v___y_249_; uint64_t v___y_250_; uint64_t v___y_251_; uint8_t v___y_252_; uint64_t v___y_253_; uint64_t v___y_254_; uint64_t v___y_259_; uint32_t v___y_260_; uint64_t v___y_261_; uint8_t v___y_262_; uint64_t v___y_263_; uint64_t v___y_264_; uint64_t v___y_265_; uint64_t v___y_270_; uint64_t v___y_271_; uint32_t v___y_272_; uint64_t v___y_273_; uint64_t v___y_274_; uint64_t v___y_275_; uint64_t v___y_276_; uint8_t v___y_277_; uint64_t v___y_278_; uint64_t v___y_283_; uint32_t v___y_284_; uint64_t v___y_285_; uint64_t v___y_286_; uint8_t v___y_287_; uint64_t v___y_288_; uint64_t v___y_289_; uint64_t v___y_294_; uint64_t v___y_295_; uint64_t v___y_296_; uint64_t v___y_297_; uint32_t v___y_298_; uint64_t v___y_299_; uint64_t v___y_300_; uint8_t v___y_301_; uint64_t v___y_302_; uint64_t v___y_307_; uint64_t v___y_308_; uint32_t v___y_309_; uint64_t v___y_310_; uint8_t v___y_311_; uint64_t v___y_312_; uint64_t v___y_313_; uint64_t v___y_318_; uint64_t v___y_319_; uint32_t v___y_320_; uint64_t v___y_321_; uint64_t v___y_322_; uint64_t v___y_323_; uint64_t v___y_324_; uint8_t v___y_325_; uint64_t v___y_326_; uint64_t v___y_331_; uint32_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint8_t v___y_335_; uint64_t v___y_336_; uint64_t v___y_337_; uint64_t v___y_342_; uint32_t v___y_343_; uint64_t v___y_344_; uint64_t v___y_345_; uint64_t v___y_346_; uint8_t v___y_347_; uint64_t v___y_348_; uint64_t v___y_352_; uint32_t v___y_353_; uint64_t v___y_354_; uint8_t v___y_355_; uint64_t v___y_364_; uint32_t v___y_365_; uint64_t v___y_366_; uint64_t v___y_367_; uint8_t v___y_368_; uint64_t v___y_369_; uint32_t v_ex_402_; uint32_t v___x_403_; uint32_t v_ey_404_; uint64_t v___y_406_; uint64_t v___y_407_; uint32_t v___y_408_; uint8_t v___y_409_; uint64_t v___y_410_; uint64_t v___y_417_; uint32_t v___y_418_; uint8_t v___y_419_; uint64_t v___y_420_; uint32_t v___y_427_; uint32_t v___y_428_; uint8_t v___y_429_; uint64_t v___y_430_; uint8_t v___y_438_; uint32_t v___x_448_; uint32_t v___x_449_; uint8_t v___x_450_; uint8_t v___y_452_; uint8_t v___y_453_; uint8_t v___y_455_; uint8_t v___y_456_; uint8_t v___y_457_; uint8_t v___y_459_; uint8_t v___y_460_; uint8_t v___y_466_; 
v___x_117_ = 23;
v___x_118_ = lean_uint32_shift_right(v___y_65_, v___x_117_);
v___x_119_ = 255;
v_ex_402_ = lean_uint32_land(v___x_118_, v___x_119_);
v___x_403_ = lean_uint32_shift_right(v___y_66_, v___x_117_);
v_ey_404_ = lean_uint32_land(v___x_403_, v___x_119_);
v___x_448_ = lean_uint32_add(v_ex_402_, v_ey_404_);
v___x_449_ = 128;
v___x_450_ = lean_uint32_dec_lt(v___x_448_, v___x_449_);
if (v___x_450_ == 0)
{
float v___x_475_; float v___x_476_; float v_result_477_; uint8_t v___x_478_; 
v___x_475_ = lean_float32_of_bits(v___y_65_);
v___x_476_ = lean_float32_of_bits(v___y_66_);
v_result_477_ = lean_float32_mul(v___x_475_, v___x_476_);
v___x_478_ = lean_float32_beq(v_result_477_, v_result_477_);
if (v___x_478_ == 0)
{
uint32_t v___x_479_; 
v___x_479_ = lp_competition_Submission_FastMul_mul(v___y_65_, v___y_66_);
return v___x_479_;
}
else
{
uint32_t v___x_480_; 
v___x_480_ = lean_float32_to_bits(v_result_477_);
return v___x_480_;
}
}
else
{
uint32_t v___x_481_; uint32_t v___x_482_; uint32_t v___x_483_; uint8_t v___x_484_; 
v___x_481_ = 4278190080;
v___x_482_ = 1;
v___x_483_ = lean_uint32_shift_left(v___y_65_, v___x_482_);
v___x_484_ = lean_uint32_dec_le(v___x_481_, v___x_483_);
if (v___x_484_ == 0)
{
uint32_t v___x_485_; uint8_t v___x_486_; 
v___x_485_ = lean_uint32_shift_left(v___y_66_, v___x_482_);
v___x_486_ = lean_uint32_dec_le(v___x_481_, v___x_485_);
v___y_466_ = v___x_486_;
goto v___jp_465_;
}
else
{
v___y_466_ = v___x_484_;
goto v___jp_465_;
}
}
v___jp_67_:
{
uint32_t v___x_69_; uint32_t v___x_70_; 
v___x_69_ = 8388608;
v___x_70_ = lean_uint32_lor(v___y_68_, v___x_69_);
return v___x_70_;
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
uint32_t v___x_79_; uint32_t v___x_80_; 
v___x_79_ = lean_uint32_land(v___y_77_, v___y_76_);
v___x_80_ = lean_uint32_lor(v___y_78_, v___x_79_);
return v___x_80_;
}
v___jp_81_:
{
uint8_t v___x_86_; 
v___x_86_ = lean_uint64_dec_eq(v___y_85_, v___y_84_);
if (v___x_86_ == 0)
{
uint64_t v___x_87_; uint8_t v___x_88_; 
v___x_87_ = 8388608ULL;
v___x_88_ = lean_uint64_dec_eq(v___y_85_, v___x_87_);
if (v___x_88_ == 0)
{
uint32_t v___x_89_; 
v___x_89_ = lean_uint64_to_uint32(v___y_85_);
if (v___y_83_ == 0)
{
uint32_t v___x_90_; 
v___x_90_ = 0;
v___y_76_ = v___y_82_;
v___y_77_ = v___x_89_;
v___y_78_ = v___x_90_;
goto v___jp_75_;
}
else
{
uint32_t v___x_91_; 
v___x_91_ = 2147483648;
v___y_76_ = v___y_82_;
v___y_77_ = v___x_89_;
v___y_78_ = v___x_91_;
goto v___jp_75_;
}
}
else
{
if (v___y_83_ == 0)
{
uint32_t v___x_92_; 
v___x_92_ = 0;
v___y_72_ = v___x_92_;
goto v___jp_71_;
}
else
{
uint32_t v___x_93_; 
v___x_93_ = 2147483648;
v___y_72_ = v___x_93_;
goto v___jp_71_;
}
}
}
else
{
if (v___y_83_ == 0)
{
uint32_t v___x_94_; 
v___x_94_ = 0;
return v___x_94_;
}
else
{
uint32_t v___x_95_; 
v___x_95_ = 2147483648;
return v___x_95_;
}
}
}
v___jp_96_:
{
uint32_t v___x_100_; uint32_t v___x_101_; 
v___x_100_ = lean_uint32_land(v___y_97_, v___y_98_);
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
if (v___y_105_ == 0)
{
uint32_t v___x_111_; 
v___x_111_ = 0;
v___y_97_ = v___x_110_;
v___y_98_ = v___y_103_;
v___y_99_ = v___x_111_;
goto v___jp_96_;
}
else
{
uint32_t v___x_112_; 
v___x_112_ = 2147483648;
v___y_97_ = v___x_110_;
v___y_98_ = v___y_103_;
v___y_99_ = v___x_112_;
goto v___jp_96_;
}
}
else
{
if (v___y_105_ == 0)
{
uint32_t v___x_113_; 
v___x_113_ = 0;
v___y_68_ = v___x_113_;
goto v___jp_67_;
}
else
{
uint32_t v___x_114_; 
v___x_114_ = 2147483648;
v___y_68_ = v___x_114_;
goto v___jp_67_;
}
}
}
else
{
if (v___y_105_ == 0)
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
v___jp_120_:
{
uint32_t v___x_125_; uint32_t v___x_126_; uint32_t v___x_127_; uint32_t v___x_128_; uint32_t v___x_129_; 
v___x_125_ = lean_uint32_land(v___y_122_, v___x_119_);
v___x_126_ = lean_uint32_shift_left(v___x_125_, v___x_117_);
v___x_127_ = lean_uint32_lor(v___y_124_, v___x_126_);
v___x_128_ = lean_uint32_land(v___y_123_, v___y_121_);
v___x_129_ = lean_uint32_lor(v___x_127_, v___x_128_);
return v___x_129_;
}
v___jp_130_:
{
if (v___y_133_ == 0)
{
uint32_t v___x_135_; 
v___x_135_ = 0;
v___y_121_ = v___y_131_;
v___y_122_ = v___y_132_;
v___y_123_ = v___y_134_;
v___y_124_ = v___x_135_;
goto v___jp_120_;
}
else
{
uint32_t v___x_136_; 
v___x_136_ = 2147483648;
v___y_121_ = v___y_131_;
v___y_122_ = v___y_132_;
v___y_123_ = v___y_134_;
v___y_124_ = v___x_136_;
goto v___jp_120_;
}
}
v___jp_137_:
{
uint64_t v___x_143_; uint64_t v_encodedExponent_144_; uint32_t v___x_145_; uint64_t v___x_146_; uint8_t v___x_147_; 
v___x_143_ = 171ULL;
v_encodedExponent_144_ = lean_uint64_sub(v___y_139_, v___x_143_);
v___x_145_ = lean_uint64_to_uint32(v_encodedExponent_144_);
v___x_146_ = 8388608ULL;
v___x_147_ = lean_uint64_dec_lt(v___y_142_, v___x_146_);
if (v___x_147_ == 0)
{
uint64_t v___x_148_; uint32_t v___x_149_; 
v___x_148_ = lean_uint64_sub(v___y_142_, v___x_146_);
v___x_149_ = lean_uint64_to_uint32(v___x_148_);
v___y_131_ = v___y_138_;
v___y_132_ = v___x_145_;
v___y_133_ = v___y_141_;
v___y_134_ = v___x_149_;
goto v___jp_130_;
}
else
{
uint32_t v___x_150_; 
v___x_150_ = lean_uint64_to_uint32(v___y_140_);
v___y_131_ = v___y_138_;
v___y_132_ = v___x_145_;
v___y_133_ = v___y_141_;
v___y_134_ = v___x_150_;
goto v___jp_130_;
}
}
v___jp_151_:
{
uint64_t v___x_158_; uint8_t v___x_159_; 
v___x_158_ = 425ULL;
v___x_159_ = lean_uint64_dec_lt(v___x_158_, v___y_157_);
if (v___x_159_ == 0)
{
if (v___y_152_ == 0)
{
v___y_138_ = v___y_153_;
v___y_139_ = v___y_157_;
v___y_140_ = v___y_156_;
v___y_141_ = v___y_155_;
v___y_142_ = v___y_154_;
goto v___jp_137_;
}
else
{
uint64_t v___x_160_; 
v___x_160_ = 8388608ULL;
v___y_138_ = v___y_153_;
v___y_139_ = v___y_157_;
v___y_140_ = v___y_156_;
v___y_141_ = v___y_155_;
v___y_142_ = v___x_160_;
goto v___jp_137_;
}
}
else
{
if (v___y_155_ == 0)
{
uint32_t v___x_161_; 
v___x_161_ = 2139095040;
return v___x_161_;
}
else
{
uint32_t v___x_162_; 
v___x_162_ = 4286578688;
return v___x_162_;
}
}
}
v___jp_163_:
{
uint64_t v___x_169_; uint8_t v_carry_170_; 
v___x_169_ = 16777216ULL;
v_carry_170_ = lean_uint64_dec_eq(v___y_168_, v___x_169_);
if (v_carry_170_ == 0)
{
v___y_152_ = v_carry_170_;
v___y_153_ = v___y_164_;
v___y_154_ = v___y_168_;
v___y_155_ = v___y_167_;
v___y_156_ = v___y_166_;
v___y_157_ = v___y_165_;
goto v___jp_151_;
}
else
{
uint64_t v___x_171_; uint64_t v___x_172_; 
v___x_171_ = 1ULL;
v___x_172_ = lean_uint64_add(v___y_165_, v___x_171_);
v___y_152_ = v_carry_170_;
v___y_153_ = v___y_164_;
v___y_154_ = v___y_168_;
v___y_155_ = v___y_167_;
v___y_156_ = v___y_166_;
v___y_157_ = v___x_172_;
goto v___jp_151_;
}
}
v___jp_173_:
{
uint64_t v_position_180_; uint64_t v___x_181_; uint8_t v___x_182_; 
v_position_180_ = lean_uint64_add(v___y_179_, v___y_176_);
v___x_181_ = 172ULL;
v___x_182_ = lean_uint64_dec_lt(v_position_180_, v___x_181_);
if (v___x_182_ == 0)
{
uint64_t v___x_183_; uint8_t v___x_184_; 
v___x_183_ = 23ULL;
v___x_184_ = lean_uint64_dec_lt(v___y_179_, v___x_183_);
if (v___x_184_ == 0)
{
uint64_t v___x_185_; uint8_t v___x_186_; 
v___x_185_ = lean_uint64_sub(v___y_179_, v___x_183_);
v___x_186_ = lean_uint64_dec_eq(v___x_185_, v___y_178_);
if (v___x_186_ == 0)
{
uint64_t v___x_187_; uint8_t v___x_188_; 
v___x_187_ = 64ULL;
v___x_188_ = lean_uint64_dec_lt(v___x_185_, v___x_187_);
if (v___x_188_ == 0)
{
uint8_t v___x_189_; 
v___x_189_ = lean_uint64_dec_eq(v___x_185_, v___x_187_);
if (v___x_189_ == 0)
{
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v___y_178_;
goto v___jp_163_;
}
else
{
uint64_t v___x_190_; uint8_t v___x_191_; 
v___x_190_ = 9223372036854775808ULL;
v___x_191_ = lean_uint64_dec_lt(v___x_190_, v___y_174_);
if (v___x_191_ == 0)
{
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v___y_178_;
goto v___jp_163_;
}
else
{
uint64_t v___x_192_; 
v___x_192_ = 1ULL;
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v___x_192_;
goto v___jp_163_;
}
}
}
else
{
uint64_t v_quotient_193_; uint64_t v___x_194_; uint64_t v___x_195_; uint64_t v___x_196_; uint64_t v_remainder_197_; uint64_t v___x_198_; uint64_t v_half_199_; uint8_t v___x_200_; 
v_quotient_193_ = lean_uint64_shift_right(v___y_174_, v___x_185_);
v___x_194_ = 1ULL;
v___x_195_ = lean_uint64_shift_left(v___x_194_, v___x_185_);
v___x_196_ = lean_uint64_sub(v___x_195_, v___x_194_);
v_remainder_197_ = lean_uint64_land(v___y_174_, v___x_196_);
v___x_198_ = lean_uint64_sub(v___x_185_, v___x_194_);
v_half_199_ = lean_uint64_shift_left(v___x_194_, v___x_198_);
v___x_200_ = lean_uint64_dec_lt(v_remainder_197_, v_half_199_);
if (v___x_200_ == 0)
{
uint8_t v___x_201_; 
v___x_201_ = lean_uint64_dec_lt(v_half_199_, v_remainder_197_);
if (v___x_201_ == 0)
{
uint64_t v___x_202_; uint8_t v___x_203_; 
v___x_202_ = lean_uint64_land(v_quotient_193_, v___x_194_);
v___x_203_ = lean_uint64_dec_eq(v___x_202_, v___y_178_);
if (v___x_203_ == 0)
{
uint64_t v___x_204_; 
v___x_204_ = lean_uint64_add(v_quotient_193_, v___x_194_);
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v___x_204_;
goto v___jp_163_;
}
else
{
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v_quotient_193_;
goto v___jp_163_;
}
}
else
{
uint64_t v___x_205_; 
v___x_205_ = lean_uint64_add(v_quotient_193_, v___x_194_);
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v___x_205_;
goto v___jp_163_;
}
}
else
{
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v_quotient_193_;
goto v___jp_163_;
}
}
}
else
{
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v___y_174_;
goto v___jp_163_;
}
}
else
{
uint64_t v___x_206_; uint64_t v___x_207_; 
v___x_206_ = lean_uint64_sub(v___x_183_, v___y_179_);
v___x_207_ = lean_uint64_shift_left(v___y_174_, v___x_206_);
v___y_164_ = v___y_175_;
v___y_165_ = v_position_180_;
v___y_166_ = v___y_178_;
v___y_167_ = v___y_177_;
v___y_168_ = v___x_207_;
goto v___jp_163_;
}
}
else
{
uint64_t v___x_208_; uint8_t v___x_209_; 
v___x_208_ = 149ULL;
v___x_209_ = lean_uint64_dec_lt(v___y_176_, v___x_208_);
if (v___x_209_ == 0)
{
uint64_t v___x_210_; uint64_t v___x_211_; 
v___x_210_ = lean_uint64_sub(v___y_176_, v___x_208_);
v___x_211_ = lean_uint64_shift_left(v___y_174_, v___x_210_);
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v___x_211_;
goto v___jp_81_;
}
else
{
uint64_t v___x_212_; uint8_t v___x_213_; 
v___x_212_ = lean_uint64_sub(v___x_208_, v___y_176_);
v___x_213_ = lean_uint64_dec_eq(v___x_212_, v___y_178_);
if (v___x_213_ == 0)
{
uint64_t v___x_214_; uint8_t v___x_215_; 
v___x_214_ = 64ULL;
v___x_215_ = lean_uint64_dec_lt(v___x_212_, v___x_214_);
if (v___x_215_ == 0)
{
uint8_t v___x_216_; 
v___x_216_ = lean_uint64_dec_eq(v___x_212_, v___x_214_);
if (v___x_216_ == 0)
{
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v___y_178_;
goto v___jp_81_;
}
else
{
uint64_t v___x_217_; uint8_t v___x_218_; 
v___x_217_ = 9223372036854775808ULL;
v___x_218_ = lean_uint64_dec_lt(v___x_217_, v___y_174_);
if (v___x_218_ == 0)
{
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v___y_178_;
goto v___jp_81_;
}
else
{
uint64_t v___x_219_; 
v___x_219_ = 1ULL;
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v___x_219_;
goto v___jp_81_;
}
}
}
else
{
uint64_t v_quotient_220_; uint64_t v___x_221_; uint64_t v___x_222_; uint64_t v___x_223_; uint64_t v_remainder_224_; uint64_t v___x_225_; uint64_t v_half_226_; uint8_t v___x_227_; 
v_quotient_220_ = lean_uint64_shift_right(v___y_174_, v___x_212_);
v___x_221_ = 1ULL;
v___x_222_ = lean_uint64_shift_left(v___x_221_, v___x_212_);
v___x_223_ = lean_uint64_sub(v___x_222_, v___x_221_);
v_remainder_224_ = lean_uint64_land(v___y_174_, v___x_223_);
v___x_225_ = lean_uint64_sub(v___x_212_, v___x_221_);
v_half_226_ = lean_uint64_shift_left(v___x_221_, v___x_225_);
v___x_227_ = lean_uint64_dec_lt(v_remainder_224_, v_half_226_);
if (v___x_227_ == 0)
{
uint8_t v___x_228_; 
v___x_228_ = lean_uint64_dec_lt(v_half_226_, v_remainder_224_);
if (v___x_228_ == 0)
{
uint64_t v___x_229_; uint8_t v___x_230_; 
v___x_229_ = lean_uint64_land(v_quotient_220_, v___x_221_);
v___x_230_ = lean_uint64_dec_eq(v___x_229_, v___y_178_);
if (v___x_230_ == 0)
{
uint64_t v___x_231_; 
v___x_231_ = lean_uint64_add(v_quotient_220_, v___x_221_);
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v___x_231_;
goto v___jp_81_;
}
else
{
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v_quotient_220_;
goto v___jp_81_;
}
}
else
{
uint64_t v___x_232_; 
v___x_232_ = lean_uint64_add(v_quotient_220_, v___x_221_);
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v___x_232_;
goto v___jp_81_;
}
}
else
{
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v_quotient_220_;
goto v___jp_81_;
}
}
}
else
{
v___y_82_ = v___y_175_;
v___y_83_ = v___y_177_;
v___y_84_ = v___y_178_;
v___y_85_ = v___y_174_;
goto v___jp_81_;
}
}
}
}
v___jp_233_:
{
uint64_t v___x_241_; uint64_t v___x_242_; uint8_t v___x_243_; 
v___x_241_ = 1ULL;
v___x_242_ = lean_uint64_shift_right(v___y_234_, v___x_241_);
v___x_243_ = lean_uint64_dec_eq(v___x_242_, v___y_239_);
if (v___x_243_ == 0)
{
uint64_t v___x_244_; 
v___x_244_ = lean_uint64_add(v___y_240_, v___x_241_);
v___y_174_ = v___y_235_;
v___y_175_ = v___y_236_;
v___y_176_ = v___y_237_;
v___y_177_ = v___y_238_;
v___y_178_ = v___y_239_;
v___y_179_ = v___x_244_;
goto v___jp_173_;
}
else
{
v___y_174_ = v___y_235_;
v___y_175_ = v___y_236_;
v___y_176_ = v___y_237_;
v___y_177_ = v___y_238_;
v___y_178_ = v___y_239_;
v___y_179_ = v___y_240_;
goto v___jp_173_;
}
}
v___jp_245_:
{
uint64_t v___x_255_; uint8_t v___x_256_; 
v___x_255_ = lean_uint64_shift_right(v___y_253_, v___y_246_);
v___x_256_ = lean_uint64_dec_eq(v___x_255_, v___y_251_);
if (v___x_256_ == 0)
{
uint64_t v___x_257_; 
v___x_257_ = lean_uint64_add(v___y_249_, v___y_246_);
v___y_234_ = v___y_254_;
v___y_235_ = v___y_247_;
v___y_236_ = v___y_248_;
v___y_237_ = v___y_250_;
v___y_238_ = v___y_252_;
v___y_239_ = v___y_251_;
v___y_240_ = v___x_257_;
goto v___jp_233_;
}
else
{
v___y_234_ = v___y_254_;
v___y_235_ = v___y_247_;
v___y_236_ = v___y_248_;
v___y_237_ = v___y_250_;
v___y_238_ = v___y_252_;
v___y_239_ = v___y_251_;
v___y_240_ = v___y_249_;
goto v___jp_233_;
}
}
v___jp_258_:
{
uint64_t v___x_266_; uint64_t v___x_267_; uint8_t v___x_268_; 
v___x_266_ = 2ULL;
v___x_267_ = lean_uint64_shift_right(v___y_264_, v___x_266_);
v___x_268_ = lean_uint64_dec_eq(v___x_267_, v___y_263_);
if (v___x_268_ == 0)
{
v___y_246_ = v___x_266_;
v___y_247_ = v___y_259_;
v___y_248_ = v___y_260_;
v___y_249_ = v___y_265_;
v___y_250_ = v___y_261_;
v___y_251_ = v___y_263_;
v___y_252_ = v___y_262_;
v___y_253_ = v___y_264_;
v___y_254_ = v___x_267_;
goto v___jp_245_;
}
else
{
v___y_246_ = v___x_266_;
v___y_247_ = v___y_259_;
v___y_248_ = v___y_260_;
v___y_249_ = v___y_265_;
v___y_250_ = v___y_261_;
v___y_251_ = v___y_263_;
v___y_252_ = v___y_262_;
v___y_253_ = v___y_264_;
v___y_254_ = v___y_264_;
goto v___jp_245_;
}
}
v___jp_269_:
{
uint64_t v___x_279_; uint8_t v___x_280_; 
v___x_279_ = lean_uint64_shift_right(v___y_274_, v___y_271_);
v___x_280_ = lean_uint64_dec_eq(v___x_279_, v___y_276_);
if (v___x_280_ == 0)
{
uint64_t v___x_281_; 
v___x_281_ = lean_uint64_add(v___y_273_, v___y_271_);
v___y_259_ = v___y_270_;
v___y_260_ = v___y_272_;
v___y_261_ = v___y_275_;
v___y_262_ = v___y_277_;
v___y_263_ = v___y_276_;
v___y_264_ = v___y_278_;
v___y_265_ = v___x_281_;
goto v___jp_258_;
}
else
{
v___y_259_ = v___y_270_;
v___y_260_ = v___y_272_;
v___y_261_ = v___y_275_;
v___y_262_ = v___y_277_;
v___y_263_ = v___y_276_;
v___y_264_ = v___y_278_;
v___y_265_ = v___y_273_;
goto v___jp_258_;
}
}
v___jp_282_:
{
uint64_t v___x_290_; uint64_t v___x_291_; uint8_t v___x_292_; 
v___x_290_ = 4ULL;
v___x_291_ = lean_uint64_shift_right(v___y_285_, v___x_290_);
v___x_292_ = lean_uint64_dec_eq(v___x_291_, v___y_288_);
if (v___x_292_ == 0)
{
v___y_270_ = v___y_283_;
v___y_271_ = v___x_290_;
v___y_272_ = v___y_284_;
v___y_273_ = v___y_289_;
v___y_274_ = v___y_285_;
v___y_275_ = v___y_286_;
v___y_276_ = v___y_288_;
v___y_277_ = v___y_287_;
v___y_278_ = v___x_291_;
goto v___jp_269_;
}
else
{
v___y_270_ = v___y_283_;
v___y_271_ = v___x_290_;
v___y_272_ = v___y_284_;
v___y_273_ = v___y_289_;
v___y_274_ = v___y_285_;
v___y_275_ = v___y_286_;
v___y_276_ = v___y_288_;
v___y_277_ = v___y_287_;
v___y_278_ = v___y_285_;
goto v___jp_269_;
}
}
v___jp_293_:
{
uint64_t v___x_303_; uint8_t v___x_304_; 
v___x_303_ = lean_uint64_shift_right(v___y_296_, v___y_295_);
v___x_304_ = lean_uint64_dec_eq(v___x_303_, v___y_300_);
if (v___x_304_ == 0)
{
uint64_t v___x_305_; 
v___x_305_ = lean_uint64_add(v___y_294_, v___y_295_);
v___y_283_ = v___y_297_;
v___y_284_ = v___y_298_;
v___y_285_ = v___y_302_;
v___y_286_ = v___y_299_;
v___y_287_ = v___y_301_;
v___y_288_ = v___y_300_;
v___y_289_ = v___x_305_;
goto v___jp_282_;
}
else
{
v___y_283_ = v___y_297_;
v___y_284_ = v___y_298_;
v___y_285_ = v___y_302_;
v___y_286_ = v___y_299_;
v___y_287_ = v___y_301_;
v___y_288_ = v___y_300_;
v___y_289_ = v___y_294_;
goto v___jp_282_;
}
}
v___jp_306_:
{
uint64_t v___x_314_; uint64_t v___x_315_; uint8_t v___x_316_; 
v___x_314_ = 8ULL;
v___x_315_ = lean_uint64_shift_right(v___y_308_, v___x_314_);
v___x_316_ = lean_uint64_dec_eq(v___x_315_, v___y_312_);
if (v___x_316_ == 0)
{
v___y_294_ = v___y_313_;
v___y_295_ = v___x_314_;
v___y_296_ = v___y_308_;
v___y_297_ = v___y_307_;
v___y_298_ = v___y_309_;
v___y_299_ = v___y_310_;
v___y_300_ = v___y_312_;
v___y_301_ = v___y_311_;
v___y_302_ = v___x_315_;
goto v___jp_293_;
}
else
{
v___y_294_ = v___y_313_;
v___y_295_ = v___x_314_;
v___y_296_ = v___y_308_;
v___y_297_ = v___y_307_;
v___y_298_ = v___y_309_;
v___y_299_ = v___y_310_;
v___y_300_ = v___y_312_;
v___y_301_ = v___y_311_;
v___y_302_ = v___y_308_;
goto v___jp_293_;
}
}
v___jp_317_:
{
uint64_t v___x_327_; uint8_t v___x_328_; 
v___x_327_ = lean_uint64_shift_right(v___y_321_, v___y_322_);
v___x_328_ = lean_uint64_dec_eq(v___x_327_, v___y_324_);
if (v___x_328_ == 0)
{
uint64_t v___x_329_; 
v___x_329_ = lean_uint64_add(v___y_318_, v___y_322_);
v___y_307_ = v___y_319_;
v___y_308_ = v___y_326_;
v___y_309_ = v___y_320_;
v___y_310_ = v___y_323_;
v___y_311_ = v___y_325_;
v___y_312_ = v___y_324_;
v___y_313_ = v___x_329_;
goto v___jp_306_;
}
else
{
v___y_307_ = v___y_319_;
v___y_308_ = v___y_326_;
v___y_309_ = v___y_320_;
v___y_310_ = v___y_323_;
v___y_311_ = v___y_325_;
v___y_312_ = v___y_324_;
v___y_313_ = v___y_318_;
goto v___jp_306_;
}
}
v___jp_330_:
{
uint64_t v___x_338_; uint64_t v___x_339_; uint8_t v___x_340_; 
v___x_338_ = 16ULL;
v___x_339_ = lean_uint64_shift_right(v___y_333_, v___x_338_);
v___x_340_ = lean_uint64_dec_eq(v___x_339_, v___y_336_);
if (v___x_340_ == 0)
{
v___y_318_ = v___y_337_;
v___y_319_ = v___y_331_;
v___y_320_ = v___y_332_;
v___y_321_ = v___y_333_;
v___y_322_ = v___x_338_;
v___y_323_ = v___y_334_;
v___y_324_ = v___y_336_;
v___y_325_ = v___y_335_;
v___y_326_ = v___x_339_;
goto v___jp_317_;
}
else
{
v___y_318_ = v___y_337_;
v___y_319_ = v___y_331_;
v___y_320_ = v___y_332_;
v___y_321_ = v___y_333_;
v___y_322_ = v___x_338_;
v___y_323_ = v___y_334_;
v___y_324_ = v___y_336_;
v___y_325_ = v___y_335_;
v___y_326_ = v___y_333_;
goto v___jp_317_;
}
}
v___jp_341_:
{
uint64_t v___x_349_; uint8_t v___x_350_; 
v___x_349_ = lean_uint64_shift_right(v___y_342_, v___y_344_);
v___x_350_ = lean_uint64_dec_eq(v___x_349_, v___y_346_);
if (v___x_350_ == 0)
{
v___y_331_ = v___y_342_;
v___y_332_ = v___y_343_;
v___y_333_ = v___y_348_;
v___y_334_ = v___y_345_;
v___y_335_ = v___y_347_;
v___y_336_ = v___y_346_;
v___y_337_ = v___y_344_;
goto v___jp_330_;
}
else
{
v___y_331_ = v___y_342_;
v___y_332_ = v___y_343_;
v___y_333_ = v___y_348_;
v___y_334_ = v___y_345_;
v___y_335_ = v___y_347_;
v___y_336_ = v___y_346_;
v___y_337_ = v___y_346_;
goto v___jp_330_;
}
}
v___jp_351_:
{
uint64_t v___x_356_; uint8_t v___x_357_; 
v___x_356_ = 0ULL;
v___x_357_ = lean_uint64_dec_eq(v___y_352_, v___x_356_);
if (v___x_357_ == 0)
{
uint64_t v___x_358_; uint64_t v___x_359_; uint8_t v___x_360_; 
v___x_358_ = 32ULL;
v___x_359_ = lean_uint64_shift_right(v___y_352_, v___x_358_);
v___x_360_ = lean_uint64_dec_eq(v___x_359_, v___x_356_);
if (v___x_360_ == 0)
{
v___y_342_ = v___y_352_;
v___y_343_ = v___y_353_;
v___y_344_ = v___x_358_;
v___y_345_ = v___y_354_;
v___y_346_ = v___x_356_;
v___y_347_ = v___y_355_;
v___y_348_ = v___x_359_;
goto v___jp_341_;
}
else
{
v___y_342_ = v___y_352_;
v___y_343_ = v___y_353_;
v___y_344_ = v___x_358_;
v___y_345_ = v___y_354_;
v___y_346_ = v___x_356_;
v___y_347_ = v___y_355_;
v___y_348_ = v___y_352_;
goto v___jp_341_;
}
}
else
{
if (v___y_355_ == 0)
{
uint32_t v___x_361_; 
v___x_361_ = 0;
return v___x_361_;
}
else
{
uint32_t v___x_362_; 
v___x_362_ = 2147483648;
return v___x_362_;
}
}
}
v___jp_363_:
{
uint64_t v___x_370_; uint64_t v___x_371_; uint64_t v___x_372_; uint8_t v___x_373_; 
v___x_370_ = lean_uint64_mul(v___y_364_, v___y_366_);
v___x_371_ = lean_uint64_add(v___y_367_, v___y_369_);
v___x_372_ = 281474976710656ULL;
v___x_373_ = lean_uint64_dec_lt(v___x_370_, v___x_372_);
if (v___x_373_ == 0)
{
v___y_352_ = v___x_370_;
v___y_353_ = v___y_365_;
v___y_354_ = v___x_371_;
v___y_355_ = v___y_368_;
goto v___jp_351_;
}
else
{
uint64_t v___x_374_; uint8_t v___x_375_; 
v___x_374_ = 123ULL;
v___x_375_ = lean_uint64_dec_le(v___x_371_, v___x_374_);
if (v___x_375_ == 0)
{
v___y_352_ = v___x_370_;
v___y_353_ = v___y_365_;
v___y_354_ = v___x_371_;
v___y_355_ = v___y_368_;
goto v___jp_351_;
}
else
{
uint64_t v___x_376_; uint8_t v___x_377_; 
v___x_376_ = 0ULL;
v___x_377_ = lean_uint64_dec_eq(v___x_370_, v___x_376_);
if (v___x_377_ == 0)
{
uint64_t v___x_378_; uint64_t v___x_379_; uint8_t v___x_380_; 
v___x_378_ = 149ULL;
v___x_379_ = lean_uint64_sub(v___x_378_, v___x_371_);
v___x_380_ = lean_uint64_dec_eq(v___x_379_, v___x_376_);
if (v___x_380_ == 0)
{
uint64_t v___x_381_; uint8_t v___x_382_; 
v___x_381_ = 64ULL;
v___x_382_ = lean_uint64_dec_lt(v___x_379_, v___x_381_);
if (v___x_382_ == 0)
{
uint8_t v___x_383_; 
v___x_383_ = lean_uint64_dec_eq(v___x_379_, v___x_381_);
if (v___x_383_ == 0)
{
v___y_103_ = v___y_365_;
v___y_104_ = v___x_376_;
v___y_105_ = v___y_368_;
v___y_106_ = v___x_376_;
goto v___jp_102_;
}
else
{
uint64_t v___x_384_; uint8_t v___x_385_; 
v___x_384_ = 9223372036854775808ULL;
v___x_385_ = lean_uint64_dec_lt(v___x_384_, v___x_370_);
if (v___x_385_ == 0)
{
v___y_103_ = v___y_365_;
v___y_104_ = v___x_376_;
v___y_105_ = v___y_368_;
v___y_106_ = v___x_376_;
goto v___jp_102_;
}
else
{
uint64_t v___x_386_; 
v___x_386_ = 1ULL;
v___y_103_ = v___y_365_;
v___y_104_ = v___x_376_;
v___y_105_ = v___y_368_;
v___y_106_ = v___x_386_;
goto v___jp_102_;
}
}
}
else
{
uint64_t v_quotient_387_; uint64_t v___x_388_; uint64_t v___x_389_; uint64_t v___x_390_; uint64_t v_remainder_391_; uint64_t v___x_392_; uint64_t v_half_393_; uint8_t v___x_394_; 
v_quotient_387_ = lean_uint64_shift_right(v___x_370_, v___x_379_);
v___x_388_ = 1ULL;
v___x_389_ = lean_uint64_shift_left(v___x_388_, v___x_379_);
v___x_390_ = lean_uint64_sub(v___x_389_, v___x_388_);
v_remainder_391_ = lean_uint64_land(v___x_370_, v___x_390_);
v___x_392_ = lean_uint64_sub(v___x_379_, v___x_388_);
v_half_393_ = lean_uint64_shift_left(v___x_388_, v___x_392_);
v___x_394_ = lean_uint64_dec_lt(v_remainder_391_, v_half_393_);
if (v___x_394_ == 0)
{
uint8_t v___x_395_; 
v___x_395_ = lean_uint64_dec_lt(v_half_393_, v_remainder_391_);
if (v___x_395_ == 0)
{
uint64_t v___x_396_; uint8_t v___x_397_; 
v___x_396_ = lean_uint64_land(v_quotient_387_, v___x_388_);
v___x_397_ = lean_uint64_dec_eq(v___x_396_, v___x_376_);
if (v___x_397_ == 0)
{
uint64_t v___x_398_; 
v___x_398_ = lean_uint64_add(v_quotient_387_, v___x_388_);
v___y_103_ = v___y_365_;
v___y_104_ = v___x_376_;
v___y_105_ = v___y_368_;
v___y_106_ = v___x_398_;
goto v___jp_102_;
}
else
{
v___y_103_ = v___y_365_;
v___y_104_ = v___x_376_;
v___y_105_ = v___y_368_;
v___y_106_ = v_quotient_387_;
goto v___jp_102_;
}
}
else
{
uint64_t v___x_399_; 
v___x_399_ = lean_uint64_add(v_quotient_387_, v___x_388_);
v___y_103_ = v___y_365_;
v___y_104_ = v___x_376_;
v___y_105_ = v___y_368_;
v___y_106_ = v___x_399_;
goto v___jp_102_;
}
}
else
{
v___y_103_ = v___y_365_;
v___y_104_ = v___x_376_;
v___y_105_ = v___y_368_;
v___y_106_ = v_quotient_387_;
goto v___jp_102_;
}
}
}
else
{
v___y_103_ = v___y_365_;
v___y_104_ = v___x_376_;
v___y_105_ = v___y_368_;
v___y_106_ = v___x_370_;
goto v___jp_102_;
}
}
else
{
if (v___y_368_ == 0)
{
uint32_t v___x_400_; 
v___x_400_ = 0;
return v___x_400_;
}
else
{
uint32_t v___x_401_; 
v___x_401_ = 2147483648;
return v___x_401_;
}
}
}
}
}
v___jp_405_:
{
uint64_t v___x_411_; uint64_t v___x_412_; uint8_t v___x_413_; 
v___x_411_ = lean_uint32_to_uint64(v_ey_404_);
v___x_412_ = 0ULL;
v___x_413_ = lean_uint64_dec_eq(v___x_411_, v___x_412_);
if (v___x_413_ == 0)
{
uint64_t v___x_414_; uint64_t v___x_415_; 
v___x_414_ = 1ULL;
v___x_415_ = lean_uint64_sub(v___x_411_, v___x_414_);
v___y_364_ = v___y_406_;
v___y_365_ = v___y_408_;
v___y_366_ = v___y_407_;
v___y_367_ = v___y_410_;
v___y_368_ = v___y_409_;
v___y_369_ = v___x_415_;
goto v___jp_363_;
}
else
{
v___y_364_ = v___y_406_;
v___y_365_ = v___y_408_;
v___y_366_ = v___y_407_;
v___y_367_ = v___y_410_;
v___y_368_ = v___y_409_;
v___y_369_ = v___x_412_;
goto v___jp_363_;
}
}
v___jp_416_:
{
uint64_t v___x_421_; uint64_t v___x_422_; uint8_t v___x_423_; 
v___x_421_ = lean_uint32_to_uint64(v_ex_402_);
v___x_422_ = 0ULL;
v___x_423_ = lean_uint64_dec_eq(v___x_421_, v___x_422_);
if (v___x_423_ == 0)
{
uint64_t v___x_424_; uint64_t v___x_425_; 
v___x_424_ = 1ULL;
v___x_425_ = lean_uint64_sub(v___x_421_, v___x_424_);
v___y_406_ = v___y_417_;
v___y_407_ = v___y_420_;
v___y_408_ = v___y_418_;
v___y_409_ = v___y_419_;
v___y_410_ = v___x_425_;
goto v___jp_405_;
}
else
{
v___y_406_ = v___y_417_;
v___y_407_ = v___y_420_;
v___y_408_ = v___y_418_;
v___y_409_ = v___y_419_;
v___y_410_ = v___x_422_;
goto v___jp_405_;
}
}
v___jp_426_:
{
uint32_t v___x_431_; uint8_t v___x_432_; 
v___x_431_ = 0;
v___x_432_ = lean_uint32_dec_eq(v_ey_404_, v___x_431_);
if (v___x_432_ == 0)
{
uint64_t v___x_433_; uint64_t v___x_434_; uint64_t v___x_435_; 
v___x_433_ = lean_uint32_to_uint64(v___y_428_);
v___x_434_ = 8388608ULL;
v___x_435_ = lean_uint64_lor(v___x_433_, v___x_434_);
v___y_417_ = v___y_430_;
v___y_418_ = v___y_427_;
v___y_419_ = v___y_429_;
v___y_420_ = v___x_435_;
goto v___jp_416_;
}
else
{
uint64_t v___x_436_; 
v___x_436_ = lean_uint32_to_uint64(v___y_428_);
v___y_417_ = v___y_430_;
v___y_418_ = v___y_427_;
v___y_419_ = v___y_429_;
v___y_420_ = v___x_436_;
goto v___jp_416_;
}
}
v___jp_437_:
{
uint32_t v___x_439_; uint32_t v_xFraction_440_; uint32_t v_yFraction_441_; uint32_t v___x_442_; uint8_t v___x_443_; 
v___x_439_ = 8388607;
v_xFraction_440_ = lean_uint32_land(v___y_65_, v___x_439_);
v_yFraction_441_ = lean_uint32_land(v___y_66_, v___x_439_);
v___x_442_ = 0;
v___x_443_ = lean_uint32_dec_eq(v_ex_402_, v___x_442_);
if (v___x_443_ == 0)
{
uint64_t v___x_444_; uint64_t v___x_445_; uint64_t v___x_446_; 
v___x_444_ = lean_uint32_to_uint64(v_xFraction_440_);
v___x_445_ = 8388608ULL;
v___x_446_ = lean_uint64_lor(v___x_444_, v___x_445_);
v___y_427_ = v___x_439_;
v___y_428_ = v_yFraction_441_;
v___y_429_ = v___y_438_;
v___y_430_ = v___x_446_;
goto v___jp_426_;
}
else
{
uint64_t v___x_447_; 
v___x_447_ = lean_uint32_to_uint64(v_xFraction_440_);
v___y_427_ = v___x_439_;
v___y_428_ = v_yFraction_441_;
v___y_429_ = v___y_438_;
v___y_430_ = v___x_447_;
goto v___jp_426_;
}
}
v___jp_451_:
{
if (v___y_453_ == 0)
{
v___y_438_ = v___x_450_;
goto v___jp_437_;
}
else
{
v___y_438_ = v___y_452_;
goto v___jp_437_;
}
}
v___jp_454_:
{
if (v___y_455_ == 0)
{
if (v___y_457_ == 0)
{
v___y_452_ = v___y_456_;
v___y_453_ = v___x_450_;
goto v___jp_451_;
}
else
{
v___y_438_ = v___x_450_;
goto v___jp_437_;
}
}
else
{
v___y_452_ = v___y_456_;
v___y_453_ = v___y_457_;
goto v___jp_451_;
}
}
v___jp_458_:
{
uint32_t v___x_461_; uint32_t v___x_462_; uint32_t v___x_463_; uint8_t v___x_464_; 
v___x_461_ = 2147483648;
v___x_462_ = lean_uint32_land(v___y_66_, v___x_461_);
v___x_463_ = 0;
v___x_464_ = lean_uint32_dec_eq(v___x_462_, v___x_463_);
if (v___x_464_ == 0)
{
v___y_455_ = v___y_460_;
v___y_456_ = v___y_459_;
v___y_457_ = v___x_450_;
goto v___jp_454_;
}
else
{
v___y_455_ = v___y_460_;
v___y_456_ = v___y_459_;
v___y_457_ = v___y_459_;
goto v___jp_454_;
}
}
v___jp_465_:
{
if (v___y_466_ == 0)
{
uint32_t v___x_467_; uint32_t v___x_468_; uint32_t v___x_469_; uint8_t v___x_470_; 
v___x_467_ = 2147483648;
v___x_468_ = lean_uint32_land(v___y_65_, v___x_467_);
v___x_469_ = 0;
v___x_470_ = lean_uint32_dec_eq(v___x_468_, v___x_469_);
if (v___x_470_ == 0)
{
v___y_459_ = v___y_466_;
v___y_460_ = v___x_450_;
goto v___jp_458_;
}
else
{
v___y_459_ = v___y_466_;
v___y_460_ = v___y_466_;
goto v___jp_458_;
}
}
else
{
lean_object* v___x_471_; lean_object* v___x_472_; lean_object* v___x_473_; uint32_t v___x_474_; 
v___x_471_ = lean_uint32_to_nat(v___y_65_);
v___x_472_ = lean_uint32_to_nat(v___y_66_);
v___x_473_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_471_, v___x_472_);
v___x_474_ = lean_uint32_of_nat(v___x_473_);
lean_dec(v___x_473_);
return v___x_474_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_487_, lean_object* v___y_488_){
_start:
{
uint32_t v___y_3149__boxed_489_; uint32_t v___y_3150__boxed_490_; uint32_t v_res_491_; lean_object* v_r_492_; 
v___y_3149__boxed_489_ = lean_unbox_uint32(v___y_487_);
lean_dec(v___y_487_);
v___y_3150__boxed_490_ = lean_unbox_uint32(v___y_488_);
lean_dec(v___y_488_);
v_res_491_ = lp_competition_main___lam__1(v___y_3149__boxed_489_, v___y_3150__boxed_490_);
v_r_492_ = lean_box_uint32(v_res_491_);
return v_r_492_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_493_, uint32_t v___y_494_){
_start:
{
uint32_t v___y_496_; uint32_t v___y_500_; uint32_t v___y_504_; uint32_t v___y_505_; uint32_t v___y_506_; uint8_t v___y_510_; uint64_t v___y_511_; uint32_t v___y_512_; uint64_t v___y_513_; uint32_t v___y_525_; uint32_t v___y_526_; uint32_t v___y_527_; uint8_t v___y_531_; uint64_t v___y_532_; uint32_t v___y_533_; uint64_t v___y_534_; uint32_t v___x_545_; uint32_t v___x_546_; uint32_t v___x_547_; uint32_t v___y_549_; uint32_t v___y_550_; uint32_t v___y_551_; uint32_t v___y_552_; uint8_t v___y_559_; uint32_t v___y_560_; uint32_t v___y_561_; uint32_t v___y_562_; uint8_t v___y_566_; uint64_t v___y_567_; uint64_t v___y_568_; uint32_t v___y_569_; uint64_t v___y_570_; uint8_t v___y_580_; uint64_t v___y_581_; uint64_t v___y_582_; uint32_t v___y_583_; uint8_t v___y_584_; uint64_t v___y_585_; uint8_t v___y_592_; uint64_t v___y_593_; uint64_t v___y_594_; uint32_t v___y_595_; uint64_t v___y_596_; uint8_t v___y_602_; uint64_t v___y_603_; uint32_t v___y_604_; uint64_t v___y_605_; uint64_t v___y_606_; uint64_t v___y_607_; uint8_t v___y_662_; uint64_t v___y_663_; uint64_t v___y_664_; uint32_t v___y_665_; uint64_t v___y_666_; uint64_t v___y_667_; uint64_t v___y_668_; uint64_t v___y_674_; uint64_t v___y_675_; uint8_t v___y_676_; uint64_t v___y_677_; uint64_t v___y_678_; uint32_t v___y_679_; uint64_t v___y_680_; uint64_t v___y_681_; uint64_t v___y_682_; uint8_t v___y_687_; uint64_t v___y_688_; uint64_t v___y_689_; uint32_t v___y_690_; uint64_t v___y_691_; uint64_t v___y_692_; uint64_t v___y_693_; uint8_t v___y_698_; uint64_t v___y_699_; uint64_t v___y_700_; uint64_t v___y_701_; uint64_t v___y_702_; uint32_t v___y_703_; uint64_t v___y_704_; uint64_t v___y_705_; uint64_t v___y_706_; uint8_t v___y_711_; uint64_t v___y_712_; uint32_t v___y_713_; uint64_t v___y_714_; uint64_t v___y_715_; uint64_t v___y_716_; uint64_t v___y_717_; uint64_t v___y_722_; uint8_t v___y_723_; uint64_t v___y_724_; uint32_t v___y_725_; uint64_t v___y_726_; uint64_t v___y_727_; uint64_t v___y_728_; uint64_t v___y_729_; uint64_t v___y_730_; uint8_t v___y_735_; uint64_t v___y_736_; uint32_t v___y_737_; uint64_t v___y_738_; uint64_t v___y_739_; uint64_t v___y_740_; uint64_t v___y_741_; uint64_t v___y_746_; uint8_t v___y_747_; uint64_t v___y_748_; uint32_t v___y_749_; uint64_t v___y_750_; uint64_t v___y_751_; uint64_t v___y_752_; uint64_t v___y_753_; uint64_t v___y_754_; uint8_t v___y_759_; uint64_t v___y_760_; uint32_t v___y_761_; uint64_t v___y_762_; uint64_t v___y_763_; uint64_t v___y_764_; uint64_t v___y_765_; uint8_t v___y_770_; uint64_t v___y_771_; uint32_t v___y_772_; uint64_t v___y_773_; uint64_t v___y_774_; uint64_t v___y_775_; uint64_t v___y_776_; uint8_t v___y_780_; uint32_t v___y_781_; uint64_t v___y_782_; uint64_t v___y_783_; uint64_t v___y_792_; uint8_t v___y_793_; uint32_t v___y_794_; uint64_t v___y_795_; uint64_t v___y_796_; uint64_t v___y_797_; uint32_t v_ex_830_; uint32_t v___x_831_; uint32_t v_ey_832_; uint64_t v___y_834_; uint8_t v___y_835_; uint32_t v___y_836_; uint64_t v___y_837_; uint64_t v___y_838_; uint8_t v___y_845_; uint32_t v___y_846_; uint64_t v___y_847_; uint64_t v___y_848_; uint8_t v___y_855_; uint32_t v___y_856_; uint32_t v___y_857_; uint64_t v___y_858_; uint8_t v___y_866_; uint32_t v___x_876_; uint32_t v___x_877_; uint8_t v___x_878_; uint8_t v___y_880_; uint8_t v___y_881_; uint8_t v___y_883_; uint8_t v___y_884_; uint8_t v___y_885_; uint8_t v___y_887_; uint8_t v___y_888_; uint8_t v___y_894_; 
v___x_545_ = 23;
v___x_546_ = lean_uint32_shift_right(v___y_493_, v___x_545_);
v___x_547_ = 255;
v_ex_830_ = lean_uint32_land(v___x_546_, v___x_547_);
v___x_831_ = lean_uint32_shift_right(v___y_494_, v___x_545_);
v_ey_832_ = lean_uint32_land(v___x_831_, v___x_547_);
v___x_876_ = lean_uint32_add(v_ex_830_, v_ey_832_);
v___x_877_ = 128;
v___x_878_ = lean_uint32_dec_lt(v___x_876_, v___x_877_);
if (v___x_878_ == 0)
{
float v___x_903_; float v___x_904_; float v_result_905_; uint8_t v___x_906_; 
v___x_903_ = lean_float32_of_bits(v___y_493_);
v___x_904_ = lean_float32_of_bits(v___y_494_);
v_result_905_ = lean_float32_mul(v___x_903_, v___x_904_);
v___x_906_ = lean_float32_beq(v_result_905_, v_result_905_);
if (v___x_906_ == 0)
{
uint32_t v___x_907_; 
v___x_907_ = lp_competition_Submission_FastMul_mul(v___y_493_, v___y_494_);
return v___x_907_;
}
else
{
uint32_t v___x_908_; 
v___x_908_ = lean_float32_to_bits(v_result_905_);
return v___x_908_;
}
}
else
{
uint32_t v___x_909_; uint32_t v___x_910_; uint32_t v___x_911_; uint8_t v___x_912_; 
v___x_909_ = 4278190080;
v___x_910_ = 1;
v___x_911_ = lean_uint32_shift_left(v___y_493_, v___x_910_);
v___x_912_ = lean_uint32_dec_le(v___x_909_, v___x_911_);
if (v___x_912_ == 0)
{
uint32_t v___x_913_; uint8_t v___x_914_; 
v___x_913_ = lean_uint32_shift_left(v___y_494_, v___x_910_);
v___x_914_ = lean_uint32_dec_le(v___x_909_, v___x_913_);
v___y_894_ = v___x_914_;
goto v___jp_893_;
}
else
{
v___y_894_ = v___x_912_;
goto v___jp_893_;
}
}
v___jp_495_:
{
uint32_t v___x_497_; uint32_t v___x_498_; 
v___x_497_ = 8388608;
v___x_498_ = lean_uint32_lor(v___y_496_, v___x_497_);
return v___x_498_;
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
uint32_t v___x_507_; uint32_t v___x_508_; 
v___x_507_ = lean_uint32_land(v___y_504_, v___y_505_);
v___x_508_ = lean_uint32_lor(v___y_506_, v___x_507_);
return v___x_508_;
}
v___jp_509_:
{
uint8_t v___x_514_; 
v___x_514_ = lean_uint64_dec_eq(v___y_513_, v___y_511_);
if (v___x_514_ == 0)
{
uint64_t v___x_515_; uint8_t v___x_516_; 
v___x_515_ = 8388608ULL;
v___x_516_ = lean_uint64_dec_eq(v___y_513_, v___x_515_);
if (v___x_516_ == 0)
{
uint32_t v___x_517_; 
v___x_517_ = lean_uint64_to_uint32(v___y_513_);
if (v___y_510_ == 0)
{
uint32_t v___x_518_; 
v___x_518_ = 0;
v___y_504_ = v___x_517_;
v___y_505_ = v___y_512_;
v___y_506_ = v___x_518_;
goto v___jp_503_;
}
else
{
uint32_t v___x_519_; 
v___x_519_ = 2147483648;
v___y_504_ = v___x_517_;
v___y_505_ = v___y_512_;
v___y_506_ = v___x_519_;
goto v___jp_503_;
}
}
else
{
if (v___y_510_ == 0)
{
uint32_t v___x_520_; 
v___x_520_ = 0;
v___y_500_ = v___x_520_;
goto v___jp_499_;
}
else
{
uint32_t v___x_521_; 
v___x_521_ = 2147483648;
v___y_500_ = v___x_521_;
goto v___jp_499_;
}
}
}
else
{
if (v___y_510_ == 0)
{
uint32_t v___x_522_; 
v___x_522_ = 0;
return v___x_522_;
}
else
{
uint32_t v___x_523_; 
v___x_523_ = 2147483648;
return v___x_523_;
}
}
}
v___jp_524_:
{
uint32_t v___x_528_; uint32_t v___x_529_; 
v___x_528_ = lean_uint32_land(v___y_526_, v___y_525_);
v___x_529_ = lean_uint32_lor(v___y_527_, v___x_528_);
return v___x_529_;
}
v___jp_530_:
{
uint8_t v___x_535_; 
v___x_535_ = lean_uint64_dec_eq(v___y_534_, v___y_532_);
if (v___x_535_ == 0)
{
uint64_t v___x_536_; uint8_t v___x_537_; 
v___x_536_ = 8388608ULL;
v___x_537_ = lean_uint64_dec_eq(v___y_534_, v___x_536_);
if (v___x_537_ == 0)
{
uint32_t v___x_538_; 
v___x_538_ = lean_uint64_to_uint32(v___y_534_);
if (v___y_531_ == 0)
{
uint32_t v___x_539_; 
v___x_539_ = 0;
v___y_525_ = v___y_533_;
v___y_526_ = v___x_538_;
v___y_527_ = v___x_539_;
goto v___jp_524_;
}
else
{
uint32_t v___x_540_; 
v___x_540_ = 2147483648;
v___y_525_ = v___y_533_;
v___y_526_ = v___x_538_;
v___y_527_ = v___x_540_;
goto v___jp_524_;
}
}
else
{
if (v___y_531_ == 0)
{
uint32_t v___x_541_; 
v___x_541_ = 0;
v___y_496_ = v___x_541_;
goto v___jp_495_;
}
else
{
uint32_t v___x_542_; 
v___x_542_ = 2147483648;
v___y_496_ = v___x_542_;
goto v___jp_495_;
}
}
}
else
{
if (v___y_531_ == 0)
{
uint32_t v___x_543_; 
v___x_543_ = 0;
return v___x_543_;
}
else
{
uint32_t v___x_544_; 
v___x_544_ = 2147483648;
return v___x_544_;
}
}
}
v___jp_548_:
{
uint32_t v___x_553_; uint32_t v___x_554_; uint32_t v___x_555_; uint32_t v___x_556_; uint32_t v___x_557_; 
v___x_553_ = lean_uint32_land(v___y_551_, v___x_547_);
v___x_554_ = lean_uint32_shift_left(v___x_553_, v___x_545_);
v___x_555_ = lean_uint32_lor(v___y_552_, v___x_554_);
v___x_556_ = lean_uint32_land(v___y_550_, v___y_549_);
v___x_557_ = lean_uint32_lor(v___x_555_, v___x_556_);
return v___x_557_;
}
v___jp_558_:
{
if (v___y_559_ == 0)
{
uint32_t v___x_563_; 
v___x_563_ = 0;
v___y_549_ = v___y_560_;
v___y_550_ = v___y_562_;
v___y_551_ = v___y_561_;
v___y_552_ = v___x_563_;
goto v___jp_548_;
}
else
{
uint32_t v___x_564_; 
v___x_564_ = 2147483648;
v___y_549_ = v___y_560_;
v___y_550_ = v___y_562_;
v___y_551_ = v___y_561_;
v___y_552_ = v___x_564_;
goto v___jp_548_;
}
}
v___jp_565_:
{
uint64_t v___x_571_; uint64_t v_encodedExponent_572_; uint32_t v___x_573_; uint64_t v___x_574_; uint8_t v___x_575_; 
v___x_571_ = 171ULL;
v_encodedExponent_572_ = lean_uint64_sub(v___y_568_, v___x_571_);
v___x_573_ = lean_uint64_to_uint32(v_encodedExponent_572_);
v___x_574_ = 8388608ULL;
v___x_575_ = lean_uint64_dec_lt(v___y_570_, v___x_574_);
if (v___x_575_ == 0)
{
uint64_t v___x_576_; uint32_t v___x_577_; 
v___x_576_ = lean_uint64_sub(v___y_570_, v___x_574_);
v___x_577_ = lean_uint64_to_uint32(v___x_576_);
v___y_559_ = v___y_566_;
v___y_560_ = v___y_569_;
v___y_561_ = v___x_573_;
v___y_562_ = v___x_577_;
goto v___jp_558_;
}
else
{
uint32_t v___x_578_; 
v___x_578_ = lean_uint64_to_uint32(v___y_567_);
v___y_559_ = v___y_566_;
v___y_560_ = v___y_569_;
v___y_561_ = v___x_573_;
v___y_562_ = v___x_578_;
goto v___jp_558_;
}
}
v___jp_579_:
{
uint64_t v___x_586_; uint8_t v___x_587_; 
v___x_586_ = 425ULL;
v___x_587_ = lean_uint64_dec_lt(v___x_586_, v___y_585_);
if (v___x_587_ == 0)
{
if (v___y_584_ == 0)
{
v___y_566_ = v___y_580_;
v___y_567_ = v___y_581_;
v___y_568_ = v___y_585_;
v___y_569_ = v___y_583_;
v___y_570_ = v___y_582_;
goto v___jp_565_;
}
else
{
uint64_t v___x_588_; 
v___x_588_ = 8388608ULL;
v___y_566_ = v___y_580_;
v___y_567_ = v___y_581_;
v___y_568_ = v___y_585_;
v___y_569_ = v___y_583_;
v___y_570_ = v___x_588_;
goto v___jp_565_;
}
}
else
{
if (v___y_580_ == 0)
{
uint32_t v___x_589_; 
v___x_589_ = 2139095040;
return v___x_589_;
}
else
{
uint32_t v___x_590_; 
v___x_590_ = 4286578688;
return v___x_590_;
}
}
}
v___jp_591_:
{
uint64_t v___x_597_; uint8_t v_carry_598_; 
v___x_597_ = 16777216ULL;
v_carry_598_ = lean_uint64_dec_eq(v___y_596_, v___x_597_);
if (v_carry_598_ == 0)
{
v___y_580_ = v___y_592_;
v___y_581_ = v___y_593_;
v___y_582_ = v___y_596_;
v___y_583_ = v___y_595_;
v___y_584_ = v_carry_598_;
v___y_585_ = v___y_594_;
goto v___jp_579_;
}
else
{
uint64_t v___x_599_; uint64_t v___x_600_; 
v___x_599_ = 1ULL;
v___x_600_ = lean_uint64_add(v___y_594_, v___x_599_);
v___y_580_ = v___y_592_;
v___y_581_ = v___y_593_;
v___y_582_ = v___y_596_;
v___y_583_ = v___y_595_;
v___y_584_ = v_carry_598_;
v___y_585_ = v___x_600_;
goto v___jp_579_;
}
}
v___jp_601_:
{
uint64_t v_position_608_; uint64_t v___x_609_; uint8_t v___x_610_; 
v_position_608_ = lean_uint64_add(v___y_607_, v___y_605_);
v___x_609_ = 172ULL;
v___x_610_ = lean_uint64_dec_lt(v_position_608_, v___x_609_);
if (v___x_610_ == 0)
{
uint64_t v___x_611_; uint8_t v___x_612_; 
v___x_611_ = 23ULL;
v___x_612_ = lean_uint64_dec_lt(v___y_607_, v___x_611_);
if (v___x_612_ == 0)
{
uint64_t v___x_613_; uint8_t v___x_614_; 
v___x_613_ = lean_uint64_sub(v___y_607_, v___x_611_);
v___x_614_ = lean_uint64_dec_eq(v___x_613_, v___y_603_);
if (v___x_614_ == 0)
{
uint64_t v___x_615_; uint8_t v___x_616_; 
v___x_615_ = 64ULL;
v___x_616_ = lean_uint64_dec_lt(v___x_613_, v___x_615_);
if (v___x_616_ == 0)
{
uint8_t v___x_617_; 
v___x_617_ = lean_uint64_dec_eq(v___x_613_, v___x_615_);
if (v___x_617_ == 0)
{
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v___y_603_;
goto v___jp_591_;
}
else
{
uint64_t v___x_618_; uint8_t v___x_619_; 
v___x_618_ = 9223372036854775808ULL;
v___x_619_ = lean_uint64_dec_lt(v___x_618_, v___y_606_);
if (v___x_619_ == 0)
{
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v___y_603_;
goto v___jp_591_;
}
else
{
uint64_t v___x_620_; 
v___x_620_ = 1ULL;
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v___x_620_;
goto v___jp_591_;
}
}
}
else
{
uint64_t v_quotient_621_; uint64_t v___x_622_; uint64_t v___x_623_; uint64_t v___x_624_; uint64_t v_remainder_625_; uint64_t v___x_626_; uint64_t v_half_627_; uint8_t v___x_628_; 
v_quotient_621_ = lean_uint64_shift_right(v___y_606_, v___x_613_);
v___x_622_ = 1ULL;
v___x_623_ = lean_uint64_shift_left(v___x_622_, v___x_613_);
v___x_624_ = lean_uint64_sub(v___x_623_, v___x_622_);
v_remainder_625_ = lean_uint64_land(v___y_606_, v___x_624_);
v___x_626_ = lean_uint64_sub(v___x_613_, v___x_622_);
v_half_627_ = lean_uint64_shift_left(v___x_622_, v___x_626_);
v___x_628_ = lean_uint64_dec_lt(v_remainder_625_, v_half_627_);
if (v___x_628_ == 0)
{
uint8_t v___x_629_; 
v___x_629_ = lean_uint64_dec_lt(v_half_627_, v_remainder_625_);
if (v___x_629_ == 0)
{
uint64_t v___x_630_; uint8_t v___x_631_; 
v___x_630_ = lean_uint64_land(v_quotient_621_, v___x_622_);
v___x_631_ = lean_uint64_dec_eq(v___x_630_, v___y_603_);
if (v___x_631_ == 0)
{
uint64_t v___x_632_; 
v___x_632_ = lean_uint64_add(v_quotient_621_, v___x_622_);
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v___x_632_;
goto v___jp_591_;
}
else
{
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v_quotient_621_;
goto v___jp_591_;
}
}
else
{
uint64_t v___x_633_; 
v___x_633_ = lean_uint64_add(v_quotient_621_, v___x_622_);
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v___x_633_;
goto v___jp_591_;
}
}
else
{
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v_quotient_621_;
goto v___jp_591_;
}
}
}
else
{
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v___y_606_;
goto v___jp_591_;
}
}
else
{
uint64_t v___x_634_; uint64_t v___x_635_; 
v___x_634_ = lean_uint64_sub(v___x_611_, v___y_607_);
v___x_635_ = lean_uint64_shift_left(v___y_606_, v___x_634_);
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v_position_608_;
v___y_595_ = v___y_604_;
v___y_596_ = v___x_635_;
goto v___jp_591_;
}
}
else
{
uint64_t v___x_636_; uint8_t v___x_637_; 
v___x_636_ = 149ULL;
v___x_637_ = lean_uint64_dec_lt(v___y_605_, v___x_636_);
if (v___x_637_ == 0)
{
uint64_t v___x_638_; uint64_t v___x_639_; 
v___x_638_ = lean_uint64_sub(v___y_605_, v___x_636_);
v___x_639_ = lean_uint64_shift_left(v___y_606_, v___x_638_);
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v___x_639_;
goto v___jp_509_;
}
else
{
uint64_t v___x_640_; uint8_t v___x_641_; 
v___x_640_ = lean_uint64_sub(v___x_636_, v___y_605_);
v___x_641_ = lean_uint64_dec_eq(v___x_640_, v___y_603_);
if (v___x_641_ == 0)
{
uint64_t v___x_642_; uint8_t v___x_643_; 
v___x_642_ = 64ULL;
v___x_643_ = lean_uint64_dec_lt(v___x_640_, v___x_642_);
if (v___x_643_ == 0)
{
uint8_t v___x_644_; 
v___x_644_ = lean_uint64_dec_eq(v___x_640_, v___x_642_);
if (v___x_644_ == 0)
{
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v___y_603_;
goto v___jp_509_;
}
else
{
uint64_t v___x_645_; uint8_t v___x_646_; 
v___x_645_ = 9223372036854775808ULL;
v___x_646_ = lean_uint64_dec_lt(v___x_645_, v___y_606_);
if (v___x_646_ == 0)
{
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v___y_603_;
goto v___jp_509_;
}
else
{
uint64_t v___x_647_; 
v___x_647_ = 1ULL;
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v___x_647_;
goto v___jp_509_;
}
}
}
else
{
uint64_t v_quotient_648_; uint64_t v___x_649_; uint64_t v___x_650_; uint64_t v___x_651_; uint64_t v_remainder_652_; uint64_t v___x_653_; uint64_t v_half_654_; uint8_t v___x_655_; 
v_quotient_648_ = lean_uint64_shift_right(v___y_606_, v___x_640_);
v___x_649_ = 1ULL;
v___x_650_ = lean_uint64_shift_left(v___x_649_, v___x_640_);
v___x_651_ = lean_uint64_sub(v___x_650_, v___x_649_);
v_remainder_652_ = lean_uint64_land(v___y_606_, v___x_651_);
v___x_653_ = lean_uint64_sub(v___x_640_, v___x_649_);
v_half_654_ = lean_uint64_shift_left(v___x_649_, v___x_653_);
v___x_655_ = lean_uint64_dec_lt(v_remainder_652_, v_half_654_);
if (v___x_655_ == 0)
{
uint8_t v___x_656_; 
v___x_656_ = lean_uint64_dec_lt(v_half_654_, v_remainder_652_);
if (v___x_656_ == 0)
{
uint64_t v___x_657_; uint8_t v___x_658_; 
v___x_657_ = lean_uint64_land(v_quotient_648_, v___x_649_);
v___x_658_ = lean_uint64_dec_eq(v___x_657_, v___y_603_);
if (v___x_658_ == 0)
{
uint64_t v___x_659_; 
v___x_659_ = lean_uint64_add(v_quotient_648_, v___x_649_);
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v___x_659_;
goto v___jp_509_;
}
else
{
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v_quotient_648_;
goto v___jp_509_;
}
}
else
{
uint64_t v___x_660_; 
v___x_660_ = lean_uint64_add(v_quotient_648_, v___x_649_);
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v___x_660_;
goto v___jp_509_;
}
}
else
{
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v_quotient_648_;
goto v___jp_509_;
}
}
}
else
{
v___y_510_ = v___y_602_;
v___y_511_ = v___y_603_;
v___y_512_ = v___y_604_;
v___y_513_ = v___y_606_;
goto v___jp_509_;
}
}
}
}
v___jp_661_:
{
uint64_t v___x_669_; uint64_t v___x_670_; uint8_t v___x_671_; 
v___x_669_ = 1ULL;
v___x_670_ = lean_uint64_shift_right(v___y_664_, v___x_669_);
v___x_671_ = lean_uint64_dec_eq(v___x_670_, v___y_663_);
if (v___x_671_ == 0)
{
uint64_t v___x_672_; 
v___x_672_ = lean_uint64_add(v___y_668_, v___x_669_);
v___y_602_ = v___y_662_;
v___y_603_ = v___y_663_;
v___y_604_ = v___y_665_;
v___y_605_ = v___y_666_;
v___y_606_ = v___y_667_;
v___y_607_ = v___x_672_;
goto v___jp_601_;
}
else
{
v___y_602_ = v___y_662_;
v___y_603_ = v___y_663_;
v___y_604_ = v___y_665_;
v___y_605_ = v___y_666_;
v___y_606_ = v___y_667_;
v___y_607_ = v___y_668_;
goto v___jp_601_;
}
}
v___jp_673_:
{
uint64_t v___x_683_; uint8_t v___x_684_; 
v___x_683_ = lean_uint64_shift_right(v___y_675_, v___y_678_);
v___x_684_ = lean_uint64_dec_eq(v___x_683_, v___y_677_);
if (v___x_684_ == 0)
{
uint64_t v___x_685_; 
v___x_685_ = lean_uint64_add(v___y_674_, v___y_678_);
v___y_662_ = v___y_676_;
v___y_663_ = v___y_677_;
v___y_664_ = v___y_682_;
v___y_665_ = v___y_679_;
v___y_666_ = v___y_680_;
v___y_667_ = v___y_681_;
v___y_668_ = v___x_685_;
goto v___jp_661_;
}
else
{
v___y_662_ = v___y_676_;
v___y_663_ = v___y_677_;
v___y_664_ = v___y_682_;
v___y_665_ = v___y_679_;
v___y_666_ = v___y_680_;
v___y_667_ = v___y_681_;
v___y_668_ = v___y_674_;
goto v___jp_661_;
}
}
v___jp_686_:
{
uint64_t v___x_694_; uint64_t v___x_695_; uint8_t v___x_696_; 
v___x_694_ = 2ULL;
v___x_695_ = lean_uint64_shift_right(v___y_688_, v___x_694_);
v___x_696_ = lean_uint64_dec_eq(v___x_695_, v___y_689_);
if (v___x_696_ == 0)
{
v___y_674_ = v___y_693_;
v___y_675_ = v___y_688_;
v___y_676_ = v___y_687_;
v___y_677_ = v___y_689_;
v___y_678_ = v___x_694_;
v___y_679_ = v___y_690_;
v___y_680_ = v___y_691_;
v___y_681_ = v___y_692_;
v___y_682_ = v___x_695_;
goto v___jp_673_;
}
else
{
v___y_674_ = v___y_693_;
v___y_675_ = v___y_688_;
v___y_676_ = v___y_687_;
v___y_677_ = v___y_689_;
v___y_678_ = v___x_694_;
v___y_679_ = v___y_690_;
v___y_680_ = v___y_691_;
v___y_681_ = v___y_692_;
v___y_682_ = v___y_688_;
goto v___jp_673_;
}
}
v___jp_697_:
{
uint64_t v___x_707_; uint8_t v___x_708_; 
v___x_707_ = lean_uint64_shift_right(v___y_702_, v___y_701_);
v___x_708_ = lean_uint64_dec_eq(v___x_707_, v___y_699_);
if (v___x_708_ == 0)
{
uint64_t v___x_709_; 
v___x_709_ = lean_uint64_add(v___y_700_, v___y_701_);
v___y_687_ = v___y_698_;
v___y_688_ = v___y_706_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_703_;
v___y_691_ = v___y_704_;
v___y_692_ = v___y_705_;
v___y_693_ = v___x_709_;
goto v___jp_686_;
}
else
{
v___y_687_ = v___y_698_;
v___y_688_ = v___y_706_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_703_;
v___y_691_ = v___y_704_;
v___y_692_ = v___y_705_;
v___y_693_ = v___y_700_;
goto v___jp_686_;
}
}
v___jp_710_:
{
uint64_t v___x_718_; uint64_t v___x_719_; uint8_t v___x_720_; 
v___x_718_ = 4ULL;
v___x_719_ = lean_uint64_shift_right(v___y_714_, v___x_718_);
v___x_720_ = lean_uint64_dec_eq(v___x_719_, v___y_712_);
if (v___x_720_ == 0)
{
v___y_698_ = v___y_711_;
v___y_699_ = v___y_712_;
v___y_700_ = v___y_717_;
v___y_701_ = v___x_718_;
v___y_702_ = v___y_714_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_715_;
v___y_705_ = v___y_716_;
v___y_706_ = v___x_719_;
goto v___jp_697_;
}
else
{
v___y_698_ = v___y_711_;
v___y_699_ = v___y_712_;
v___y_700_ = v___y_717_;
v___y_701_ = v___x_718_;
v___y_702_ = v___y_714_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_715_;
v___y_705_ = v___y_716_;
v___y_706_ = v___y_714_;
goto v___jp_697_;
}
}
v___jp_721_:
{
uint64_t v___x_731_; uint8_t v___x_732_; 
v___x_731_ = lean_uint64_shift_right(v___y_729_, v___y_722_);
v___x_732_ = lean_uint64_dec_eq(v___x_731_, v___y_724_);
if (v___x_732_ == 0)
{
uint64_t v___x_733_; 
v___x_733_ = lean_uint64_add(v___y_726_, v___y_722_);
v___y_711_ = v___y_723_;
v___y_712_ = v___y_724_;
v___y_713_ = v___y_725_;
v___y_714_ = v___y_730_;
v___y_715_ = v___y_727_;
v___y_716_ = v___y_728_;
v___y_717_ = v___x_733_;
goto v___jp_710_;
}
else
{
v___y_711_ = v___y_723_;
v___y_712_ = v___y_724_;
v___y_713_ = v___y_725_;
v___y_714_ = v___y_730_;
v___y_715_ = v___y_727_;
v___y_716_ = v___y_728_;
v___y_717_ = v___y_726_;
goto v___jp_710_;
}
}
v___jp_734_:
{
uint64_t v___x_742_; uint64_t v___x_743_; uint8_t v___x_744_; 
v___x_742_ = 8ULL;
v___x_743_ = lean_uint64_shift_right(v___y_740_, v___x_742_);
v___x_744_ = lean_uint64_dec_eq(v___x_743_, v___y_736_);
if (v___x_744_ == 0)
{
v___y_722_ = v___x_742_;
v___y_723_ = v___y_735_;
v___y_724_ = v___y_736_;
v___y_725_ = v___y_737_;
v___y_726_ = v___y_741_;
v___y_727_ = v___y_738_;
v___y_728_ = v___y_739_;
v___y_729_ = v___y_740_;
v___y_730_ = v___x_743_;
goto v___jp_721_;
}
else
{
v___y_722_ = v___x_742_;
v___y_723_ = v___y_735_;
v___y_724_ = v___y_736_;
v___y_725_ = v___y_737_;
v___y_726_ = v___y_741_;
v___y_727_ = v___y_738_;
v___y_728_ = v___y_739_;
v___y_729_ = v___y_740_;
v___y_730_ = v___y_740_;
goto v___jp_721_;
}
}
v___jp_745_:
{
uint64_t v___x_755_; uint8_t v___x_756_; 
v___x_755_ = lean_uint64_shift_right(v___y_752_, v___y_746_);
v___x_756_ = lean_uint64_dec_eq(v___x_755_, v___y_748_);
if (v___x_756_ == 0)
{
uint64_t v___x_757_; 
v___x_757_ = lean_uint64_add(v___y_750_, v___y_746_);
v___y_735_ = v___y_747_;
v___y_736_ = v___y_748_;
v___y_737_ = v___y_749_;
v___y_738_ = v___y_751_;
v___y_739_ = v___y_753_;
v___y_740_ = v___y_754_;
v___y_741_ = v___x_757_;
goto v___jp_734_;
}
else
{
v___y_735_ = v___y_747_;
v___y_736_ = v___y_748_;
v___y_737_ = v___y_749_;
v___y_738_ = v___y_751_;
v___y_739_ = v___y_753_;
v___y_740_ = v___y_754_;
v___y_741_ = v___y_750_;
goto v___jp_734_;
}
}
v___jp_758_:
{
uint64_t v___x_766_; uint64_t v___x_767_; uint8_t v___x_768_; 
v___x_766_ = 16ULL;
v___x_767_ = lean_uint64_shift_right(v___y_763_, v___x_766_);
v___x_768_ = lean_uint64_dec_eq(v___x_767_, v___y_760_);
if (v___x_768_ == 0)
{
v___y_746_ = v___x_766_;
v___y_747_ = v___y_759_;
v___y_748_ = v___y_760_;
v___y_749_ = v___y_761_;
v___y_750_ = v___y_765_;
v___y_751_ = v___y_762_;
v___y_752_ = v___y_763_;
v___y_753_ = v___y_764_;
v___y_754_ = v___x_767_;
goto v___jp_745_;
}
else
{
v___y_746_ = v___x_766_;
v___y_747_ = v___y_759_;
v___y_748_ = v___y_760_;
v___y_749_ = v___y_761_;
v___y_750_ = v___y_765_;
v___y_751_ = v___y_762_;
v___y_752_ = v___y_763_;
v___y_753_ = v___y_764_;
v___y_754_ = v___y_763_;
goto v___jp_745_;
}
}
v___jp_769_:
{
uint64_t v___x_777_; uint8_t v___x_778_; 
v___x_777_ = lean_uint64_shift_right(v___y_774_, v___y_775_);
v___x_778_ = lean_uint64_dec_eq(v___x_777_, v___y_771_);
if (v___x_778_ == 0)
{
v___y_759_ = v___y_770_;
v___y_760_ = v___y_771_;
v___y_761_ = v___y_772_;
v___y_762_ = v___y_773_;
v___y_763_ = v___y_776_;
v___y_764_ = v___y_774_;
v___y_765_ = v___y_775_;
goto v___jp_758_;
}
else
{
v___y_759_ = v___y_770_;
v___y_760_ = v___y_771_;
v___y_761_ = v___y_772_;
v___y_762_ = v___y_773_;
v___y_763_ = v___y_776_;
v___y_764_ = v___y_774_;
v___y_765_ = v___y_771_;
goto v___jp_758_;
}
}
v___jp_779_:
{
uint64_t v___x_784_; uint8_t v___x_785_; 
v___x_784_ = 0ULL;
v___x_785_ = lean_uint64_dec_eq(v___y_783_, v___x_784_);
if (v___x_785_ == 0)
{
uint64_t v___x_786_; uint64_t v___x_787_; uint8_t v___x_788_; 
v___x_786_ = 32ULL;
v___x_787_ = lean_uint64_shift_right(v___y_783_, v___x_786_);
v___x_788_ = lean_uint64_dec_eq(v___x_787_, v___x_784_);
if (v___x_788_ == 0)
{
v___y_770_ = v___y_780_;
v___y_771_ = v___x_784_;
v___y_772_ = v___y_781_;
v___y_773_ = v___y_782_;
v___y_774_ = v___y_783_;
v___y_775_ = v___x_786_;
v___y_776_ = v___x_787_;
goto v___jp_769_;
}
else
{
v___y_770_ = v___y_780_;
v___y_771_ = v___x_784_;
v___y_772_ = v___y_781_;
v___y_773_ = v___y_782_;
v___y_774_ = v___y_783_;
v___y_775_ = v___x_786_;
v___y_776_ = v___y_783_;
goto v___jp_769_;
}
}
else
{
if (v___y_780_ == 0)
{
uint32_t v___x_789_; 
v___x_789_ = 0;
return v___x_789_;
}
else
{
uint32_t v___x_790_; 
v___x_790_ = 2147483648;
return v___x_790_;
}
}
}
v___jp_791_:
{
uint64_t v___x_798_; uint64_t v___x_799_; uint64_t v___x_800_; uint8_t v___x_801_; 
v___x_798_ = lean_uint64_mul(v___y_796_, v___y_792_);
v___x_799_ = lean_uint64_add(v___y_795_, v___y_797_);
v___x_800_ = 281474976710656ULL;
v___x_801_ = lean_uint64_dec_lt(v___x_798_, v___x_800_);
if (v___x_801_ == 0)
{
v___y_780_ = v___y_793_;
v___y_781_ = v___y_794_;
v___y_782_ = v___x_799_;
v___y_783_ = v___x_798_;
goto v___jp_779_;
}
else
{
uint64_t v___x_802_; uint8_t v___x_803_; 
v___x_802_ = 123ULL;
v___x_803_ = lean_uint64_dec_le(v___x_799_, v___x_802_);
if (v___x_803_ == 0)
{
v___y_780_ = v___y_793_;
v___y_781_ = v___y_794_;
v___y_782_ = v___x_799_;
v___y_783_ = v___x_798_;
goto v___jp_779_;
}
else
{
uint64_t v___x_804_; uint8_t v___x_805_; 
v___x_804_ = 0ULL;
v___x_805_ = lean_uint64_dec_eq(v___x_798_, v___x_804_);
if (v___x_805_ == 0)
{
uint64_t v___x_806_; uint64_t v___x_807_; uint8_t v___x_808_; 
v___x_806_ = 149ULL;
v___x_807_ = lean_uint64_sub(v___x_806_, v___x_799_);
v___x_808_ = lean_uint64_dec_eq(v___x_807_, v___x_804_);
if (v___x_808_ == 0)
{
uint64_t v___x_809_; uint8_t v___x_810_; 
v___x_809_ = 64ULL;
v___x_810_ = lean_uint64_dec_lt(v___x_807_, v___x_809_);
if (v___x_810_ == 0)
{
uint8_t v___x_811_; 
v___x_811_ = lean_uint64_dec_eq(v___x_807_, v___x_809_);
if (v___x_811_ == 0)
{
v___y_531_ = v___y_793_;
v___y_532_ = v___x_804_;
v___y_533_ = v___y_794_;
v___y_534_ = v___x_804_;
goto v___jp_530_;
}
else
{
uint64_t v___x_812_; uint8_t v___x_813_; 
v___x_812_ = 9223372036854775808ULL;
v___x_813_ = lean_uint64_dec_lt(v___x_812_, v___x_798_);
if (v___x_813_ == 0)
{
v___y_531_ = v___y_793_;
v___y_532_ = v___x_804_;
v___y_533_ = v___y_794_;
v___y_534_ = v___x_804_;
goto v___jp_530_;
}
else
{
uint64_t v___x_814_; 
v___x_814_ = 1ULL;
v___y_531_ = v___y_793_;
v___y_532_ = v___x_804_;
v___y_533_ = v___y_794_;
v___y_534_ = v___x_814_;
goto v___jp_530_;
}
}
}
else
{
uint64_t v_quotient_815_; uint64_t v___x_816_; uint64_t v___x_817_; uint64_t v___x_818_; uint64_t v_remainder_819_; uint64_t v___x_820_; uint64_t v_half_821_; uint8_t v___x_822_; 
v_quotient_815_ = lean_uint64_shift_right(v___x_798_, v___x_807_);
v___x_816_ = 1ULL;
v___x_817_ = lean_uint64_shift_left(v___x_816_, v___x_807_);
v___x_818_ = lean_uint64_sub(v___x_817_, v___x_816_);
v_remainder_819_ = lean_uint64_land(v___x_798_, v___x_818_);
v___x_820_ = lean_uint64_sub(v___x_807_, v___x_816_);
v_half_821_ = lean_uint64_shift_left(v___x_816_, v___x_820_);
v___x_822_ = lean_uint64_dec_lt(v_remainder_819_, v_half_821_);
if (v___x_822_ == 0)
{
uint8_t v___x_823_; 
v___x_823_ = lean_uint64_dec_lt(v_half_821_, v_remainder_819_);
if (v___x_823_ == 0)
{
uint64_t v___x_824_; uint8_t v___x_825_; 
v___x_824_ = lean_uint64_land(v_quotient_815_, v___x_816_);
v___x_825_ = lean_uint64_dec_eq(v___x_824_, v___x_804_);
if (v___x_825_ == 0)
{
uint64_t v___x_826_; 
v___x_826_ = lean_uint64_add(v_quotient_815_, v___x_816_);
v___y_531_ = v___y_793_;
v___y_532_ = v___x_804_;
v___y_533_ = v___y_794_;
v___y_534_ = v___x_826_;
goto v___jp_530_;
}
else
{
v___y_531_ = v___y_793_;
v___y_532_ = v___x_804_;
v___y_533_ = v___y_794_;
v___y_534_ = v_quotient_815_;
goto v___jp_530_;
}
}
else
{
uint64_t v___x_827_; 
v___x_827_ = lean_uint64_add(v_quotient_815_, v___x_816_);
v___y_531_ = v___y_793_;
v___y_532_ = v___x_804_;
v___y_533_ = v___y_794_;
v___y_534_ = v___x_827_;
goto v___jp_530_;
}
}
else
{
v___y_531_ = v___y_793_;
v___y_532_ = v___x_804_;
v___y_533_ = v___y_794_;
v___y_534_ = v_quotient_815_;
goto v___jp_530_;
}
}
}
else
{
v___y_531_ = v___y_793_;
v___y_532_ = v___x_804_;
v___y_533_ = v___y_794_;
v___y_534_ = v___x_798_;
goto v___jp_530_;
}
}
else
{
if (v___y_793_ == 0)
{
uint32_t v___x_828_; 
v___x_828_ = 0;
return v___x_828_;
}
else
{
uint32_t v___x_829_; 
v___x_829_ = 2147483648;
return v___x_829_;
}
}
}
}
}
v___jp_833_:
{
uint64_t v___x_839_; uint64_t v___x_840_; uint8_t v___x_841_; 
v___x_839_ = lean_uint32_to_uint64(v_ey_832_);
v___x_840_ = 0ULL;
v___x_841_ = lean_uint64_dec_eq(v___x_839_, v___x_840_);
if (v___x_841_ == 0)
{
uint64_t v___x_842_; uint64_t v___x_843_; 
v___x_842_ = 1ULL;
v___x_843_ = lean_uint64_sub(v___x_839_, v___x_842_);
v___y_792_ = v___y_834_;
v___y_793_ = v___y_835_;
v___y_794_ = v___y_836_;
v___y_795_ = v___y_838_;
v___y_796_ = v___y_837_;
v___y_797_ = v___x_843_;
goto v___jp_791_;
}
else
{
v___y_792_ = v___y_834_;
v___y_793_ = v___y_835_;
v___y_794_ = v___y_836_;
v___y_795_ = v___y_838_;
v___y_796_ = v___y_837_;
v___y_797_ = v___x_840_;
goto v___jp_791_;
}
}
v___jp_844_:
{
uint64_t v___x_849_; uint64_t v___x_850_; uint8_t v___x_851_; 
v___x_849_ = lean_uint32_to_uint64(v_ex_830_);
v___x_850_ = 0ULL;
v___x_851_ = lean_uint64_dec_eq(v___x_849_, v___x_850_);
if (v___x_851_ == 0)
{
uint64_t v___x_852_; uint64_t v___x_853_; 
v___x_852_ = 1ULL;
v___x_853_ = lean_uint64_sub(v___x_849_, v___x_852_);
v___y_834_ = v___y_848_;
v___y_835_ = v___y_845_;
v___y_836_ = v___y_846_;
v___y_837_ = v___y_847_;
v___y_838_ = v___x_853_;
goto v___jp_833_;
}
else
{
v___y_834_ = v___y_848_;
v___y_835_ = v___y_845_;
v___y_836_ = v___y_846_;
v___y_837_ = v___y_847_;
v___y_838_ = v___x_850_;
goto v___jp_833_;
}
}
v___jp_854_:
{
uint32_t v___x_859_; uint8_t v___x_860_; 
v___x_859_ = 0;
v___x_860_ = lean_uint32_dec_eq(v_ey_832_, v___x_859_);
if (v___x_860_ == 0)
{
uint64_t v___x_861_; uint64_t v___x_862_; uint64_t v___x_863_; 
v___x_861_ = lean_uint32_to_uint64(v___y_857_);
v___x_862_ = 8388608ULL;
v___x_863_ = lean_uint64_lor(v___x_861_, v___x_862_);
v___y_845_ = v___y_855_;
v___y_846_ = v___y_856_;
v___y_847_ = v___y_858_;
v___y_848_ = v___x_863_;
goto v___jp_844_;
}
else
{
uint64_t v___x_864_; 
v___x_864_ = lean_uint32_to_uint64(v___y_857_);
v___y_845_ = v___y_855_;
v___y_846_ = v___y_856_;
v___y_847_ = v___y_858_;
v___y_848_ = v___x_864_;
goto v___jp_844_;
}
}
v___jp_865_:
{
uint32_t v___x_867_; uint32_t v_xFraction_868_; uint32_t v_yFraction_869_; uint32_t v___x_870_; uint8_t v___x_871_; 
v___x_867_ = 8388607;
v_xFraction_868_ = lean_uint32_land(v___y_493_, v___x_867_);
v_yFraction_869_ = lean_uint32_land(v___y_494_, v___x_867_);
v___x_870_ = 0;
v___x_871_ = lean_uint32_dec_eq(v_ex_830_, v___x_870_);
if (v___x_871_ == 0)
{
uint64_t v___x_872_; uint64_t v___x_873_; uint64_t v___x_874_; 
v___x_872_ = lean_uint32_to_uint64(v_xFraction_868_);
v___x_873_ = 8388608ULL;
v___x_874_ = lean_uint64_lor(v___x_872_, v___x_873_);
v___y_855_ = v___y_866_;
v___y_856_ = v___x_867_;
v___y_857_ = v_yFraction_869_;
v___y_858_ = v___x_874_;
goto v___jp_854_;
}
else
{
uint64_t v___x_875_; 
v___x_875_ = lean_uint32_to_uint64(v_xFraction_868_);
v___y_855_ = v___y_866_;
v___y_856_ = v___x_867_;
v___y_857_ = v_yFraction_869_;
v___y_858_ = v___x_875_;
goto v___jp_854_;
}
}
v___jp_879_:
{
if (v___y_881_ == 0)
{
v___y_866_ = v___x_878_;
goto v___jp_865_;
}
else
{
v___y_866_ = v___y_880_;
goto v___jp_865_;
}
}
v___jp_882_:
{
if (v___y_883_ == 0)
{
if (v___y_885_ == 0)
{
v___y_880_ = v___y_884_;
v___y_881_ = v___x_878_;
goto v___jp_879_;
}
else
{
v___y_866_ = v___x_878_;
goto v___jp_865_;
}
}
else
{
v___y_880_ = v___y_884_;
v___y_881_ = v___y_885_;
goto v___jp_879_;
}
}
v___jp_886_:
{
uint32_t v___x_889_; uint32_t v___x_890_; uint32_t v___x_891_; uint8_t v___x_892_; 
v___x_889_ = 2147483648;
v___x_890_ = lean_uint32_land(v___y_494_, v___x_889_);
v___x_891_ = 0;
v___x_892_ = lean_uint32_dec_eq(v___x_890_, v___x_891_);
if (v___x_892_ == 0)
{
v___y_883_ = v___y_888_;
v___y_884_ = v___y_887_;
v___y_885_ = v___x_878_;
goto v___jp_882_;
}
else
{
v___y_883_ = v___y_888_;
v___y_884_ = v___y_887_;
v___y_885_ = v___y_887_;
goto v___jp_882_;
}
}
v___jp_893_:
{
if (v___y_894_ == 0)
{
uint32_t v___x_895_; uint32_t v___x_896_; uint32_t v___x_897_; uint8_t v___x_898_; 
v___x_895_ = 2147483648;
v___x_896_ = lean_uint32_land(v___y_493_, v___x_895_);
v___x_897_ = 0;
v___x_898_ = lean_uint32_dec_eq(v___x_896_, v___x_897_);
if (v___x_898_ == 0)
{
v___y_887_ = v___y_894_;
v___y_888_ = v___x_878_;
goto v___jp_886_;
}
else
{
v___y_887_ = v___y_894_;
v___y_888_ = v___y_894_;
goto v___jp_886_;
}
}
else
{
lean_object* v___x_899_; lean_object* v___x_900_; lean_object* v___x_901_; uint32_t v___x_902_; 
v___x_899_ = lean_uint32_to_nat(v___y_493_);
v___x_900_ = lean_uint32_to_nat(v___y_494_);
v___x_901_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_899_, v___x_900_);
v___x_902_ = lean_uint32_of_nat(v___x_901_);
lean_dec(v___x_901_);
return v___x_902_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_915_, lean_object* v___y_916_){
_start:
{
uint32_t v___y_3961__boxed_917_; uint32_t v___y_3962__boxed_918_; uint32_t v_res_919_; lean_object* v_r_920_; 
v___y_3961__boxed_917_ = lean_unbox_uint32(v___y_915_);
lean_dec(v___y_915_);
v___y_3962__boxed_918_ = lean_unbox_uint32(v___y_916_);
lean_dec(v___y_916_);
v_res_919_ = lp_competition_main___lam__3(v___y_3961__boxed_917_, v___y_3962__boxed_918_);
v_r_920_ = lean_box_uint32(v_res_919_);
return v_r_920_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_928_; lean_object* v___x_929_; 
v___x_928_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_929_ = lean_io_getenv(v___x_928_);
if (lean_obj_tag(v___x_929_) == 0)
{
lean_object* v___f_930_; lean_object* v___f_931_; lean_object* v___x_932_; lean_object* v___x_933_; lean_object* v___x_934_; 
v___f_930_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_931_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_932_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_933_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_934_ = lp_competition_Bench_runFull(v___f_930_, v___f_931_, v___x_932_, v___x_933_);
return v___x_934_;
}
else
{
lean_object* v___f_935_; lean_object* v___f_936_; lean_object* v___x_937_; lean_object* v___x_938_; lean_object* v___x_939_; 
lean_dec_ref_known(v___x_929_, 1);
v___f_935_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_936_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_937_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_938_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_939_ = lp_competition_Bench_Suite_run(v___f_935_, v___f_936_, v___x_937_, v___x_938_);
return v___x_939_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_940_){
_start:
{
lean_object* v_res_941_; 
v_res_941_ = _lean_main();
return v_res_941_;
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
