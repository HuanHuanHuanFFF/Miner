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
float v___y_4_; float v___y_5_; float v___y_11_; uint8_t v___y_12_; float v___y_27_; uint8_t v___y_37_; uint32_t v___x_51_; uint32_t v___x_52_; uint32_t v___x_53_; uint32_t v___x_54_; uint32_t v___x_55_; uint32_t v___x_56_; uint32_t v___x_57_; uint32_t v___x_58_; uint8_t v___x_59_; 
v___x_51_ = 2147483647;
v___x_52_ = lean_uint32_land(v___y_1_, v___x_51_);
v___x_53_ = 536870912;
v___x_54_ = lean_uint32_sub(v___x_52_, v___x_53_);
v___x_55_ = lean_uint32_land(v___y_2_, v___x_51_);
v___x_56_ = lean_uint32_sub(v___x_55_, v___x_53_);
v___x_57_ = lean_uint32_lor(v___x_54_, v___x_56_);
v___x_58_ = 1073741824;
v___x_59_ = lean_uint32_dec_lt(v___x_57_, v___x_58_);
if (v___x_59_ == 0)
{
uint32_t v___x_60_; uint32_t v___x_61_; uint32_t v___x_62_; uint8_t v___x_63_; 
v___x_60_ = 201326591;
v___x_61_ = 1;
v___x_62_ = lean_uint32_sub(v___x_52_, v___x_61_);
v___x_63_ = lean_uint32_dec_le(v___x_60_, v___x_62_);
if (v___x_63_ == 0)
{
v___y_37_ = v___x_63_;
goto v___jp_36_;
}
else
{
uint32_t v___x_64_; uint8_t v___x_65_; 
v___x_64_ = 2139095040;
v___x_65_ = lean_uint32_dec_lt(v___x_52_, v___x_64_);
v___y_37_ = v___x_65_;
goto v___jp_36_;
}
}
else
{
uint32_t v___x_66_; uint32_t v___x_67_; uint32_t v___x_68_; uint32_t v___x_69_; float v___x_70_; lean_object* v___x_71_; uint32_t v___x_72_; uint32_t v___x_73_; lean_object* v___x_74_; lean_object* v___x_75_; float v___x_76_; float v___x_77_; uint32_t v___x_78_; uint32_t v___x_79_; float v___x_80_; uint32_t v___x_81_; lean_object* v___x_82_; lean_object* v___x_83_; float v___x_84_; float v___x_85_; float v___x_86_; uint32_t v___x_87_; 
v___x_66_ = 8388607;
v___x_67_ = lean_uint32_land(v___y_1_, v___x_66_);
v___x_68_ = 8388608;
v___x_69_ = lean_uint32_lor(v___x_67_, v___x_68_);
v___x_70_ = lean_uint32_to_float32(v___x_69_);
v___x_71_ = lp_competition_R2W01b_scaleTable;
v___x_72_ = 23;
v___x_73_ = lean_uint32_shift_right(v___y_1_, v___x_72_);
v___x_74_ = lean_uint32_to_nat(v___x_73_);
v___x_75_ = lean_array_fget_borrowed(v___x_71_, v___x_74_);
lean_dec(v___x_74_);
v___x_76_ = lean_unbox_float32(v___x_75_);
v___x_77_ = lean_float32_mul(v___x_70_, v___x_76_);
v___x_78_ = lean_uint32_land(v___y_2_, v___x_66_);
v___x_79_ = lean_uint32_lor(v___x_78_, v___x_68_);
v___x_80_ = lean_uint32_to_float32(v___x_79_);
v___x_81_ = lean_uint32_shift_right(v___y_2_, v___x_72_);
v___x_82_ = lean_uint32_to_nat(v___x_81_);
v___x_83_ = lean_array_fget_borrowed(v___x_71_, v___x_82_);
lean_dec(v___x_82_);
v___x_84_ = lean_unbox_float32(v___x_83_);
v___x_85_ = lean_float32_mul(v___x_80_, v___x_84_);
v___x_86_ = lean_float32_add(v___x_77_, v___x_85_);
v___x_87_ = lean_float32_to_bits(v___x_86_);
return v___x_87_;
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
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_88_, lean_object* v___y_89_){
_start:
{
uint32_t v___y_3277__boxed_90_; uint32_t v___y_3278__boxed_91_; uint32_t v_res_92_; lean_object* v_r_93_; 
v___y_3277__boxed_90_ = lean_unbox_uint32(v___y_88_);
lean_dec(v___y_88_);
v___y_3278__boxed_91_ = lean_unbox_uint32(v___y_89_);
lean_dec(v___y_89_);
v_res_92_ = lp_competition_main___lam__0(v___y_3277__boxed_90_, v___y_3278__boxed_91_);
v_r_93_ = lean_box_uint32(v_res_92_);
return v_r_93_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_94_, uint32_t v___y_95_){
_start:
{
uint32_t v___y_97_; uint32_t v___y_101_; uint32_t v___y_105_; uint32_t v___y_106_; uint32_t v___y_107_; uint8_t v___y_111_; uint32_t v___y_112_; uint64_t v___y_113_; uint64_t v___y_114_; uint32_t v___y_126_; uint32_t v___y_127_; uint32_t v___y_128_; uint8_t v___y_132_; uint32_t v___y_133_; uint64_t v___y_134_; uint64_t v___y_135_; uint32_t v___x_146_; uint32_t v___x_147_; uint32_t v___x_148_; uint32_t v___x_149_; uint32_t v___x_150_; uint32_t v___x_151_; uint32_t v___x_152_; uint32_t v___x_153_; uint8_t v___x_154_; 
v___x_146_ = 2147483647;
v___x_147_ = lean_uint32_land(v___y_94_, v___x_146_);
v___x_148_ = 536870912;
v___x_149_ = lean_uint32_sub(v___x_147_, v___x_148_);
v___x_150_ = lean_uint32_land(v___y_95_, v___x_146_);
v___x_151_ = lean_uint32_sub(v___x_150_, v___x_148_);
v___x_152_ = lean_uint32_lor(v___x_149_, v___x_151_);
v___x_153_ = 1073741824;
v___x_154_ = lean_uint32_dec_lt(v___x_152_, v___x_153_);
if (v___x_154_ == 0)
{
uint32_t v___x_155_; uint32_t v___x_156_; uint32_t v___x_157_; uint32_t v___y_159_; uint32_t v___y_160_; uint32_t v___y_161_; uint32_t v___y_162_; uint8_t v___y_169_; uint32_t v___y_170_; uint32_t v___y_171_; uint32_t v___y_172_; uint8_t v___y_176_; uint32_t v___y_177_; uint64_t v___y_178_; uint64_t v___y_179_; uint64_t v___y_180_; uint64_t v___y_190_; uint8_t v___y_191_; uint8_t v___y_192_; uint32_t v___y_193_; uint64_t v___y_194_; uint64_t v___y_195_; uint8_t v___y_202_; uint64_t v___y_203_; uint32_t v___y_204_; uint64_t v___y_205_; uint64_t v___y_206_; uint8_t v___y_212_; uint32_t v___y_213_; uint64_t v___y_214_; uint64_t v___y_215_; uint64_t v___y_216_; uint64_t v___y_217_; uint8_t v___y_272_; uint32_t v___y_273_; uint64_t v___y_274_; uint64_t v___y_275_; uint64_t v___y_276_; uint64_t v___y_277_; uint64_t v___y_278_; uint8_t v___y_284_; uint64_t v___y_285_; uint32_t v___y_286_; uint64_t v___y_287_; uint64_t v___y_288_; uint64_t v___y_289_; uint64_t v___y_290_; uint64_t v___y_291_; uint64_t v___y_292_; uint8_t v___y_297_; uint32_t v___y_298_; uint64_t v___y_299_; uint64_t v___y_300_; uint64_t v___y_301_; uint64_t v___y_302_; uint64_t v___y_303_; uint8_t v___y_308_; uint32_t v___y_309_; uint64_t v___y_310_; uint64_t v___y_311_; uint64_t v___y_312_; uint64_t v___y_313_; uint64_t v___y_314_; uint64_t v___y_315_; uint64_t v___y_316_; uint8_t v___y_321_; uint32_t v___y_322_; uint64_t v___y_323_; uint64_t v___y_324_; uint64_t v___y_325_; uint64_t v___y_326_; uint64_t v___y_327_; uint8_t v___y_332_; uint32_t v___y_333_; uint64_t v___y_334_; uint64_t v___y_335_; uint64_t v___y_336_; uint64_t v___y_337_; uint64_t v___y_338_; uint64_t v___y_339_; uint64_t v___y_340_; uint8_t v___y_345_; uint32_t v___y_346_; uint64_t v___y_347_; uint64_t v___y_348_; uint64_t v___y_349_; uint64_t v___y_350_; uint64_t v___y_351_; uint8_t v___y_356_; uint64_t v___y_357_; uint32_t v___y_358_; uint64_t v___y_359_; uint64_t v___y_360_; uint64_t v___y_361_; uint64_t v___y_362_; uint64_t v___y_363_; uint64_t v___y_364_; uint8_t v___y_369_; uint32_t v___y_370_; uint64_t v___y_371_; uint64_t v___y_372_; uint64_t v___y_373_; uint64_t v___y_374_; uint64_t v___y_375_; uint8_t v___y_380_; uint32_t v___y_381_; uint64_t v___y_382_; uint64_t v___y_383_; uint64_t v___y_384_; uint64_t v___y_385_; uint64_t v___y_386_; uint8_t v___y_390_; uint32_t v___y_391_; uint64_t v___y_392_; uint64_t v___y_393_; uint8_t v___y_402_; uint64_t v___y_403_; uint64_t v___y_404_; uint32_t v___y_405_; uint64_t v___y_406_; uint64_t v___y_407_; uint32_t v_ex_440_; uint32_t v___x_441_; uint32_t v_ey_442_; uint64_t v___y_444_; uint8_t v___y_445_; uint64_t v___y_446_; uint32_t v___y_447_; uint64_t v___y_448_; uint8_t v___y_455_; uint64_t v___y_456_; uint32_t v___y_457_; uint64_t v___y_458_; uint8_t v___y_465_; uint32_t v___y_466_; uint32_t v___y_467_; uint64_t v___y_468_; uint8_t v___y_476_; uint32_t v___x_486_; uint32_t v___x_487_; uint8_t v___x_488_; uint8_t v___y_490_; uint8_t v___y_491_; uint8_t v___y_492_; uint8_t v___y_494_; uint8_t v___y_495_; uint8_t v___y_501_; 
v___x_155_ = 23;
v___x_156_ = lean_uint32_shift_right(v___y_94_, v___x_155_);
v___x_157_ = 255;
v_ex_440_ = lean_uint32_land(v___x_156_, v___x_157_);
v___x_441_ = lean_uint32_shift_right(v___y_95_, v___x_155_);
v_ey_442_ = lean_uint32_land(v___x_441_, v___x_157_);
v___x_486_ = lean_uint32_add(v_ex_440_, v_ey_442_);
v___x_487_ = 128;
v___x_488_ = lean_uint32_dec_lt(v___x_486_, v___x_487_);
if (v___x_488_ == 0)
{
float v___x_510_; float v___x_511_; float v_result_512_; uint8_t v___x_513_; 
v___x_510_ = lean_float32_of_bits(v___y_94_);
v___x_511_ = lean_float32_of_bits(v___y_95_);
v_result_512_ = lean_float32_mul(v___x_510_, v___x_511_);
v___x_513_ = lean_float32_beq(v_result_512_, v_result_512_);
if (v___x_513_ == 0)
{
uint32_t v___x_514_; 
v___x_514_ = lp_competition_Submission_FastMul_mul(v___y_94_, v___y_95_);
return v___x_514_;
}
else
{
uint32_t v___x_515_; 
v___x_515_ = lean_float32_to_bits(v_result_512_);
return v___x_515_;
}
}
else
{
uint32_t v___x_516_; uint32_t v___x_517_; uint32_t v___x_518_; uint8_t v___x_519_; 
v___x_516_ = 4278190080;
v___x_517_ = 1;
v___x_518_ = lean_uint32_shift_left(v___y_94_, v___x_517_);
v___x_519_ = lean_uint32_dec_le(v___x_516_, v___x_518_);
if (v___x_519_ == 0)
{
uint32_t v___x_520_; uint8_t v___x_521_; 
v___x_520_ = lean_uint32_shift_left(v___y_95_, v___x_517_);
v___x_521_ = lean_uint32_dec_le(v___x_516_, v___x_520_);
v___y_501_ = v___x_521_;
goto v___jp_500_;
}
else
{
v___y_501_ = v___x_519_;
goto v___jp_500_;
}
}
v___jp_158_:
{
uint32_t v___x_163_; uint32_t v___x_164_; uint32_t v___x_165_; uint32_t v___x_166_; uint32_t v___x_167_; 
v___x_163_ = lean_uint32_land(v___y_159_, v___x_157_);
v___x_164_ = lean_uint32_shift_left(v___x_163_, v___x_155_);
v___x_165_ = lean_uint32_lor(v___y_162_, v___x_164_);
v___x_166_ = lean_uint32_land(v___y_161_, v___y_160_);
v___x_167_ = lean_uint32_lor(v___x_165_, v___x_166_);
return v___x_167_;
}
v___jp_168_:
{
if (v___y_169_ == 0)
{
uint32_t v___x_173_; 
v___x_173_ = 0;
v___y_159_ = v___y_170_;
v___y_160_ = v___y_171_;
v___y_161_ = v___y_172_;
v___y_162_ = v___x_173_;
goto v___jp_158_;
}
else
{
uint32_t v___x_174_; 
v___x_174_ = 2147483648;
v___y_159_ = v___y_170_;
v___y_160_ = v___y_171_;
v___y_161_ = v___y_172_;
v___y_162_ = v___x_174_;
goto v___jp_158_;
}
}
v___jp_175_:
{
uint64_t v___x_181_; uint64_t v_encodedExponent_182_; uint32_t v___x_183_; uint64_t v___x_184_; uint8_t v___x_185_; 
v___x_181_ = 171ULL;
v_encodedExponent_182_ = lean_uint64_sub(v___y_179_, v___x_181_);
v___x_183_ = lean_uint64_to_uint32(v_encodedExponent_182_);
v___x_184_ = 8388608ULL;
v___x_185_ = lean_uint64_dec_lt(v___y_180_, v___x_184_);
if (v___x_185_ == 0)
{
uint64_t v___x_186_; uint32_t v___x_187_; 
v___x_186_ = lean_uint64_sub(v___y_180_, v___x_184_);
v___x_187_ = lean_uint64_to_uint32(v___x_186_);
v___y_169_ = v___y_176_;
v___y_170_ = v___x_183_;
v___y_171_ = v___y_177_;
v___y_172_ = v___x_187_;
goto v___jp_168_;
}
else
{
uint32_t v___x_188_; 
v___x_188_ = lean_uint64_to_uint32(v___y_178_);
v___y_169_ = v___y_176_;
v___y_170_ = v___x_183_;
v___y_171_ = v___y_177_;
v___y_172_ = v___x_188_;
goto v___jp_168_;
}
}
v___jp_189_:
{
uint64_t v___x_196_; uint8_t v___x_197_; 
v___x_196_ = 425ULL;
v___x_197_ = lean_uint64_dec_lt(v___x_196_, v___y_195_);
if (v___x_197_ == 0)
{
if (v___y_191_ == 0)
{
v___y_176_ = v___y_192_;
v___y_177_ = v___y_193_;
v___y_178_ = v___y_194_;
v___y_179_ = v___y_195_;
v___y_180_ = v___y_190_;
goto v___jp_175_;
}
else
{
uint64_t v___x_198_; 
v___x_198_ = 8388608ULL;
v___y_176_ = v___y_192_;
v___y_177_ = v___y_193_;
v___y_178_ = v___y_194_;
v___y_179_ = v___y_195_;
v___y_180_ = v___x_198_;
goto v___jp_175_;
}
}
else
{
if (v___y_192_ == 0)
{
uint32_t v___x_199_; 
v___x_199_ = 2139095040;
return v___x_199_;
}
else
{
uint32_t v___x_200_; 
v___x_200_ = 4286578688;
return v___x_200_;
}
}
}
v___jp_201_:
{
uint64_t v___x_207_; uint8_t v_carry_208_; 
v___x_207_ = 16777216ULL;
v_carry_208_ = lean_uint64_dec_eq(v___y_206_, v___x_207_);
if (v_carry_208_ == 0)
{
v___y_190_ = v___y_206_;
v___y_191_ = v_carry_208_;
v___y_192_ = v___y_202_;
v___y_193_ = v___y_204_;
v___y_194_ = v___y_205_;
v___y_195_ = v___y_203_;
goto v___jp_189_;
}
else
{
uint64_t v___x_209_; uint64_t v___x_210_; 
v___x_209_ = 1ULL;
v___x_210_ = lean_uint64_add(v___y_203_, v___x_209_);
v___y_190_ = v___y_206_;
v___y_191_ = v_carry_208_;
v___y_192_ = v___y_202_;
v___y_193_ = v___y_204_;
v___y_194_ = v___y_205_;
v___y_195_ = v___x_210_;
goto v___jp_189_;
}
}
v___jp_211_:
{
uint64_t v_position_218_; uint64_t v___x_219_; uint8_t v___x_220_; 
v_position_218_ = lean_uint64_add(v___y_217_, v___y_216_);
v___x_219_ = 172ULL;
v___x_220_ = lean_uint64_dec_lt(v_position_218_, v___x_219_);
if (v___x_220_ == 0)
{
uint64_t v___x_221_; uint8_t v___x_222_; 
v___x_221_ = 23ULL;
v___x_222_ = lean_uint64_dec_lt(v___y_217_, v___x_221_);
if (v___x_222_ == 0)
{
uint64_t v___x_223_; uint8_t v___x_224_; 
v___x_223_ = lean_uint64_sub(v___y_217_, v___x_221_);
v___x_224_ = lean_uint64_dec_eq(v___x_223_, v___y_214_);
if (v___x_224_ == 0)
{
uint64_t v___x_225_; uint8_t v___x_226_; 
v___x_225_ = 64ULL;
v___x_226_ = lean_uint64_dec_lt(v___x_223_, v___x_225_);
if (v___x_226_ == 0)
{
uint8_t v___x_227_; 
v___x_227_ = lean_uint64_dec_eq(v___x_223_, v___x_225_);
if (v___x_227_ == 0)
{
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v___y_214_;
goto v___jp_201_;
}
else
{
uint64_t v___x_228_; uint8_t v___x_229_; 
v___x_228_ = 9223372036854775808ULL;
v___x_229_ = lean_uint64_dec_lt(v___x_228_, v___y_215_);
if (v___x_229_ == 0)
{
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v___y_214_;
goto v___jp_201_;
}
else
{
uint64_t v___x_230_; 
v___x_230_ = 1ULL;
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v___x_230_;
goto v___jp_201_;
}
}
}
else
{
uint64_t v_quotient_231_; uint64_t v___x_232_; uint64_t v___x_233_; uint64_t v___x_234_; uint64_t v_remainder_235_; uint64_t v___x_236_; uint64_t v_half_237_; uint8_t v___x_238_; 
v_quotient_231_ = lean_uint64_shift_right(v___y_215_, v___x_223_);
v___x_232_ = 1ULL;
v___x_233_ = lean_uint64_shift_left(v___x_232_, v___x_223_);
v___x_234_ = lean_uint64_sub(v___x_233_, v___x_232_);
v_remainder_235_ = lean_uint64_land(v___y_215_, v___x_234_);
v___x_236_ = lean_uint64_sub(v___x_223_, v___x_232_);
v_half_237_ = lean_uint64_shift_left(v___x_232_, v___x_236_);
v___x_238_ = lean_uint64_dec_lt(v_remainder_235_, v_half_237_);
if (v___x_238_ == 0)
{
uint8_t v___x_239_; 
v___x_239_ = lean_uint64_dec_lt(v_half_237_, v_remainder_235_);
if (v___x_239_ == 0)
{
uint64_t v___x_240_; uint8_t v___x_241_; 
v___x_240_ = lean_uint64_land(v_quotient_231_, v___x_232_);
v___x_241_ = lean_uint64_dec_eq(v___x_240_, v___y_214_);
if (v___x_241_ == 0)
{
uint64_t v___x_242_; 
v___x_242_ = lean_uint64_add(v_quotient_231_, v___x_232_);
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v___x_242_;
goto v___jp_201_;
}
else
{
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v_quotient_231_;
goto v___jp_201_;
}
}
else
{
uint64_t v___x_243_; 
v___x_243_ = lean_uint64_add(v_quotient_231_, v___x_232_);
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v___x_243_;
goto v___jp_201_;
}
}
else
{
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v_quotient_231_;
goto v___jp_201_;
}
}
}
else
{
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v___y_215_;
goto v___jp_201_;
}
}
else
{
uint64_t v___x_244_; uint64_t v___x_245_; 
v___x_244_ = lean_uint64_sub(v___x_221_, v___y_217_);
v___x_245_ = lean_uint64_shift_left(v___y_215_, v___x_244_);
v___y_202_ = v___y_212_;
v___y_203_ = v_position_218_;
v___y_204_ = v___y_213_;
v___y_205_ = v___y_214_;
v___y_206_ = v___x_245_;
goto v___jp_201_;
}
}
else
{
uint64_t v___x_246_; uint8_t v___x_247_; 
v___x_246_ = 149ULL;
v___x_247_ = lean_uint64_dec_lt(v___y_216_, v___x_246_);
if (v___x_247_ == 0)
{
uint64_t v___x_248_; uint64_t v___x_249_; 
v___x_248_ = lean_uint64_sub(v___y_216_, v___x_246_);
v___x_249_ = lean_uint64_shift_left(v___y_215_, v___x_248_);
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v___x_249_;
goto v___jp_110_;
}
else
{
uint64_t v___x_250_; uint8_t v___x_251_; 
v___x_250_ = lean_uint64_sub(v___x_246_, v___y_216_);
v___x_251_ = lean_uint64_dec_eq(v___x_250_, v___y_214_);
if (v___x_251_ == 0)
{
uint64_t v___x_252_; uint8_t v___x_253_; 
v___x_252_ = 64ULL;
v___x_253_ = lean_uint64_dec_lt(v___x_250_, v___x_252_);
if (v___x_253_ == 0)
{
uint8_t v___x_254_; 
v___x_254_ = lean_uint64_dec_eq(v___x_250_, v___x_252_);
if (v___x_254_ == 0)
{
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v___y_214_;
goto v___jp_110_;
}
else
{
uint64_t v___x_255_; uint8_t v___x_256_; 
v___x_255_ = 9223372036854775808ULL;
v___x_256_ = lean_uint64_dec_lt(v___x_255_, v___y_215_);
if (v___x_256_ == 0)
{
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v___y_214_;
goto v___jp_110_;
}
else
{
uint64_t v___x_257_; 
v___x_257_ = 1ULL;
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v___x_257_;
goto v___jp_110_;
}
}
}
else
{
uint64_t v_quotient_258_; uint64_t v___x_259_; uint64_t v___x_260_; uint64_t v___x_261_; uint64_t v_remainder_262_; uint64_t v___x_263_; uint64_t v_half_264_; uint8_t v___x_265_; 
v_quotient_258_ = lean_uint64_shift_right(v___y_215_, v___x_250_);
v___x_259_ = 1ULL;
v___x_260_ = lean_uint64_shift_left(v___x_259_, v___x_250_);
v___x_261_ = lean_uint64_sub(v___x_260_, v___x_259_);
v_remainder_262_ = lean_uint64_land(v___y_215_, v___x_261_);
v___x_263_ = lean_uint64_sub(v___x_250_, v___x_259_);
v_half_264_ = lean_uint64_shift_left(v___x_259_, v___x_263_);
v___x_265_ = lean_uint64_dec_lt(v_remainder_262_, v_half_264_);
if (v___x_265_ == 0)
{
uint8_t v___x_266_; 
v___x_266_ = lean_uint64_dec_lt(v_half_264_, v_remainder_262_);
if (v___x_266_ == 0)
{
uint64_t v___x_267_; uint8_t v___x_268_; 
v___x_267_ = lean_uint64_land(v_quotient_258_, v___x_259_);
v___x_268_ = lean_uint64_dec_eq(v___x_267_, v___y_214_);
if (v___x_268_ == 0)
{
uint64_t v___x_269_; 
v___x_269_ = lean_uint64_add(v_quotient_258_, v___x_259_);
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v___x_269_;
goto v___jp_110_;
}
else
{
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v_quotient_258_;
goto v___jp_110_;
}
}
else
{
uint64_t v___x_270_; 
v___x_270_ = lean_uint64_add(v_quotient_258_, v___x_259_);
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v___x_270_;
goto v___jp_110_;
}
}
else
{
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v_quotient_258_;
goto v___jp_110_;
}
}
}
else
{
v___y_111_ = v___y_212_;
v___y_112_ = v___y_213_;
v___y_113_ = v___y_214_;
v___y_114_ = v___y_215_;
goto v___jp_110_;
}
}
}
}
v___jp_271_:
{
uint64_t v___x_279_; uint64_t v___x_280_; uint8_t v___x_281_; 
v___x_279_ = 1ULL;
v___x_280_ = lean_uint64_shift_right(v___y_277_, v___x_279_);
v___x_281_ = lean_uint64_dec_eq(v___x_280_, v___y_274_);
if (v___x_281_ == 0)
{
uint64_t v___x_282_; 
v___x_282_ = lean_uint64_add(v___y_278_, v___x_279_);
v___y_212_ = v___y_272_;
v___y_213_ = v___y_273_;
v___y_214_ = v___y_274_;
v___y_215_ = v___y_276_;
v___y_216_ = v___y_275_;
v___y_217_ = v___x_282_;
goto v___jp_211_;
}
else
{
v___y_212_ = v___y_272_;
v___y_213_ = v___y_273_;
v___y_214_ = v___y_274_;
v___y_215_ = v___y_276_;
v___y_216_ = v___y_275_;
v___y_217_ = v___y_278_;
goto v___jp_211_;
}
}
v___jp_283_:
{
uint64_t v___x_293_; uint8_t v___x_294_; 
v___x_293_ = lean_uint64_shift_right(v___y_288_, v___y_285_);
v___x_294_ = lean_uint64_dec_eq(v___x_293_, v___y_287_);
if (v___x_294_ == 0)
{
uint64_t v___x_295_; 
v___x_295_ = lean_uint64_add(v___y_291_, v___y_285_);
v___y_272_ = v___y_284_;
v___y_273_ = v___y_286_;
v___y_274_ = v___y_287_;
v___y_275_ = v___y_290_;
v___y_276_ = v___y_289_;
v___y_277_ = v___y_292_;
v___y_278_ = v___x_295_;
goto v___jp_271_;
}
else
{
v___y_272_ = v___y_284_;
v___y_273_ = v___y_286_;
v___y_274_ = v___y_287_;
v___y_275_ = v___y_290_;
v___y_276_ = v___y_289_;
v___y_277_ = v___y_292_;
v___y_278_ = v___y_291_;
goto v___jp_271_;
}
}
v___jp_296_:
{
uint64_t v___x_304_; uint64_t v___x_305_; uint8_t v___x_306_; 
v___x_304_ = 2ULL;
v___x_305_ = lean_uint64_shift_right(v___y_300_, v___x_304_);
v___x_306_ = lean_uint64_dec_eq(v___x_305_, v___y_299_);
if (v___x_306_ == 0)
{
v___y_284_ = v___y_297_;
v___y_285_ = v___x_304_;
v___y_286_ = v___y_298_;
v___y_287_ = v___y_299_;
v___y_288_ = v___y_300_;
v___y_289_ = v___y_302_;
v___y_290_ = v___y_301_;
v___y_291_ = v___y_303_;
v___y_292_ = v___x_305_;
goto v___jp_283_;
}
else
{
v___y_284_ = v___y_297_;
v___y_285_ = v___x_304_;
v___y_286_ = v___y_298_;
v___y_287_ = v___y_299_;
v___y_288_ = v___y_300_;
v___y_289_ = v___y_302_;
v___y_290_ = v___y_301_;
v___y_291_ = v___y_303_;
v___y_292_ = v___y_300_;
goto v___jp_283_;
}
}
v___jp_307_:
{
uint64_t v___x_317_; uint8_t v___x_318_; 
v___x_317_ = lean_uint64_shift_right(v___y_313_, v___y_310_);
v___x_318_ = lean_uint64_dec_eq(v___x_317_, v___y_311_);
if (v___x_318_ == 0)
{
uint64_t v___x_319_; 
v___x_319_ = lean_uint64_add(v___y_312_, v___y_310_);
v___y_297_ = v___y_308_;
v___y_298_ = v___y_309_;
v___y_299_ = v___y_311_;
v___y_300_ = v___y_316_;
v___y_301_ = v___y_315_;
v___y_302_ = v___y_314_;
v___y_303_ = v___x_319_;
goto v___jp_296_;
}
else
{
v___y_297_ = v___y_308_;
v___y_298_ = v___y_309_;
v___y_299_ = v___y_311_;
v___y_300_ = v___y_316_;
v___y_301_ = v___y_315_;
v___y_302_ = v___y_314_;
v___y_303_ = v___y_312_;
goto v___jp_296_;
}
}
v___jp_320_:
{
uint64_t v___x_328_; uint64_t v___x_329_; uint8_t v___x_330_; 
v___x_328_ = 4ULL;
v___x_329_ = lean_uint64_shift_right(v___y_324_, v___x_328_);
v___x_330_ = lean_uint64_dec_eq(v___x_329_, v___y_323_);
if (v___x_330_ == 0)
{
v___y_308_ = v___y_321_;
v___y_309_ = v___y_322_;
v___y_310_ = v___x_328_;
v___y_311_ = v___y_323_;
v___y_312_ = v___y_327_;
v___y_313_ = v___y_324_;
v___y_314_ = v___y_326_;
v___y_315_ = v___y_325_;
v___y_316_ = v___x_329_;
goto v___jp_307_;
}
else
{
v___y_308_ = v___y_321_;
v___y_309_ = v___y_322_;
v___y_310_ = v___x_328_;
v___y_311_ = v___y_323_;
v___y_312_ = v___y_327_;
v___y_313_ = v___y_324_;
v___y_314_ = v___y_326_;
v___y_315_ = v___y_325_;
v___y_316_ = v___y_324_;
goto v___jp_307_;
}
}
v___jp_331_:
{
uint64_t v___x_341_; uint8_t v___x_342_; 
v___x_341_ = lean_uint64_shift_right(v___y_335_, v___y_336_);
v___x_342_ = lean_uint64_dec_eq(v___x_341_, v___y_334_);
if (v___x_342_ == 0)
{
uint64_t v___x_343_; 
v___x_343_ = lean_uint64_add(v___y_339_, v___y_336_);
v___y_321_ = v___y_332_;
v___y_322_ = v___y_333_;
v___y_323_ = v___y_334_;
v___y_324_ = v___y_340_;
v___y_325_ = v___y_338_;
v___y_326_ = v___y_337_;
v___y_327_ = v___x_343_;
goto v___jp_320_;
}
else
{
v___y_321_ = v___y_332_;
v___y_322_ = v___y_333_;
v___y_323_ = v___y_334_;
v___y_324_ = v___y_340_;
v___y_325_ = v___y_338_;
v___y_326_ = v___y_337_;
v___y_327_ = v___y_339_;
goto v___jp_320_;
}
}
v___jp_344_:
{
uint64_t v___x_352_; uint64_t v___x_353_; uint8_t v___x_354_; 
v___x_352_ = 8ULL;
v___x_353_ = lean_uint64_shift_right(v___y_348_, v___x_352_);
v___x_354_ = lean_uint64_dec_eq(v___x_353_, v___y_347_);
if (v___x_354_ == 0)
{
v___y_332_ = v___y_345_;
v___y_333_ = v___y_346_;
v___y_334_ = v___y_347_;
v___y_335_ = v___y_348_;
v___y_336_ = v___x_352_;
v___y_337_ = v___y_350_;
v___y_338_ = v___y_349_;
v___y_339_ = v___y_351_;
v___y_340_ = v___x_353_;
goto v___jp_331_;
}
else
{
v___y_332_ = v___y_345_;
v___y_333_ = v___y_346_;
v___y_334_ = v___y_347_;
v___y_335_ = v___y_348_;
v___y_336_ = v___x_352_;
v___y_337_ = v___y_350_;
v___y_338_ = v___y_349_;
v___y_339_ = v___y_351_;
v___y_340_ = v___y_348_;
goto v___jp_331_;
}
}
v___jp_355_:
{
uint64_t v___x_365_; uint8_t v___x_366_; 
v___x_365_ = lean_uint64_shift_right(v___y_363_, v___y_357_);
v___x_366_ = lean_uint64_dec_eq(v___x_365_, v___y_359_);
if (v___x_366_ == 0)
{
uint64_t v___x_367_; 
v___x_367_ = lean_uint64_add(v___y_360_, v___y_357_);
v___y_345_ = v___y_356_;
v___y_346_ = v___y_358_;
v___y_347_ = v___y_359_;
v___y_348_ = v___y_364_;
v___y_349_ = v___y_362_;
v___y_350_ = v___y_361_;
v___y_351_ = v___x_367_;
goto v___jp_344_;
}
else
{
v___y_345_ = v___y_356_;
v___y_346_ = v___y_358_;
v___y_347_ = v___y_359_;
v___y_348_ = v___y_364_;
v___y_349_ = v___y_362_;
v___y_350_ = v___y_361_;
v___y_351_ = v___y_360_;
goto v___jp_344_;
}
}
v___jp_368_:
{
uint64_t v___x_376_; uint64_t v___x_377_; uint8_t v___x_378_; 
v___x_376_ = 16ULL;
v___x_377_ = lean_uint64_shift_right(v___y_374_, v___x_376_);
v___x_378_ = lean_uint64_dec_eq(v___x_377_, v___y_371_);
if (v___x_378_ == 0)
{
v___y_356_ = v___y_369_;
v___y_357_ = v___x_376_;
v___y_358_ = v___y_370_;
v___y_359_ = v___y_371_;
v___y_360_ = v___y_375_;
v___y_361_ = v___y_373_;
v___y_362_ = v___y_372_;
v___y_363_ = v___y_374_;
v___y_364_ = v___x_377_;
goto v___jp_355_;
}
else
{
v___y_356_ = v___y_369_;
v___y_357_ = v___x_376_;
v___y_358_ = v___y_370_;
v___y_359_ = v___y_371_;
v___y_360_ = v___y_375_;
v___y_361_ = v___y_373_;
v___y_362_ = v___y_372_;
v___y_363_ = v___y_374_;
v___y_364_ = v___y_374_;
goto v___jp_355_;
}
}
v___jp_379_:
{
uint64_t v___x_387_; uint8_t v___x_388_; 
v___x_387_ = lean_uint64_shift_right(v___y_384_, v___y_383_);
v___x_388_ = lean_uint64_dec_eq(v___x_387_, v___y_382_);
if (v___x_388_ == 0)
{
v___y_369_ = v___y_380_;
v___y_370_ = v___y_381_;
v___y_371_ = v___y_382_;
v___y_372_ = v___y_385_;
v___y_373_ = v___y_384_;
v___y_374_ = v___y_386_;
v___y_375_ = v___y_383_;
goto v___jp_368_;
}
else
{
v___y_369_ = v___y_380_;
v___y_370_ = v___y_381_;
v___y_371_ = v___y_382_;
v___y_372_ = v___y_385_;
v___y_373_ = v___y_384_;
v___y_374_ = v___y_386_;
v___y_375_ = v___y_382_;
goto v___jp_368_;
}
}
v___jp_389_:
{
uint64_t v___x_394_; uint8_t v___x_395_; 
v___x_394_ = 0ULL;
v___x_395_ = lean_uint64_dec_eq(v___y_393_, v___x_394_);
if (v___x_395_ == 0)
{
uint64_t v___x_396_; uint64_t v___x_397_; uint8_t v___x_398_; 
v___x_396_ = 32ULL;
v___x_397_ = lean_uint64_shift_right(v___y_393_, v___x_396_);
v___x_398_ = lean_uint64_dec_eq(v___x_397_, v___x_394_);
if (v___x_398_ == 0)
{
v___y_380_ = v___y_390_;
v___y_381_ = v___y_391_;
v___y_382_ = v___x_394_;
v___y_383_ = v___x_396_;
v___y_384_ = v___y_393_;
v___y_385_ = v___y_392_;
v___y_386_ = v___x_397_;
goto v___jp_379_;
}
else
{
v___y_380_ = v___y_390_;
v___y_381_ = v___y_391_;
v___y_382_ = v___x_394_;
v___y_383_ = v___x_396_;
v___y_384_ = v___y_393_;
v___y_385_ = v___y_392_;
v___y_386_ = v___y_393_;
goto v___jp_379_;
}
}
else
{
if (v___y_390_ == 0)
{
uint32_t v___x_399_; 
v___x_399_ = 0;
return v___x_399_;
}
else
{
uint32_t v___x_400_; 
v___x_400_ = 2147483648;
return v___x_400_;
}
}
}
v___jp_401_:
{
uint64_t v___x_408_; uint64_t v___x_409_; uint64_t v___x_410_; uint8_t v___x_411_; 
v___x_408_ = lean_uint64_mul(v___y_403_, v___y_404_);
v___x_409_ = lean_uint64_add(v___y_406_, v___y_407_);
v___x_410_ = 281474976710656ULL;
v___x_411_ = lean_uint64_dec_lt(v___x_408_, v___x_410_);
if (v___x_411_ == 0)
{
v___y_390_ = v___y_402_;
v___y_391_ = v___y_405_;
v___y_392_ = v___x_409_;
v___y_393_ = v___x_408_;
goto v___jp_389_;
}
else
{
uint64_t v___x_412_; uint8_t v___x_413_; 
v___x_412_ = 123ULL;
v___x_413_ = lean_uint64_dec_le(v___x_409_, v___x_412_);
if (v___x_413_ == 0)
{
v___y_390_ = v___y_402_;
v___y_391_ = v___y_405_;
v___y_392_ = v___x_409_;
v___y_393_ = v___x_408_;
goto v___jp_389_;
}
else
{
uint64_t v___x_414_; uint8_t v___x_415_; 
v___x_414_ = 0ULL;
v___x_415_ = lean_uint64_dec_eq(v___x_408_, v___x_414_);
if (v___x_415_ == 0)
{
uint64_t v___x_416_; uint64_t v___x_417_; uint8_t v___x_418_; 
v___x_416_ = 149ULL;
v___x_417_ = lean_uint64_sub(v___x_416_, v___x_409_);
v___x_418_ = lean_uint64_dec_eq(v___x_417_, v___x_414_);
if (v___x_418_ == 0)
{
uint64_t v___x_419_; uint8_t v___x_420_; 
v___x_419_ = 64ULL;
v___x_420_ = lean_uint64_dec_lt(v___x_417_, v___x_419_);
if (v___x_420_ == 0)
{
uint8_t v___x_421_; 
v___x_421_ = lean_uint64_dec_eq(v___x_417_, v___x_419_);
if (v___x_421_ == 0)
{
v___y_132_ = v___y_402_;
v___y_133_ = v___y_405_;
v___y_134_ = v___x_414_;
v___y_135_ = v___x_414_;
goto v___jp_131_;
}
else
{
uint64_t v___x_422_; uint8_t v___x_423_; 
v___x_422_ = 9223372036854775808ULL;
v___x_423_ = lean_uint64_dec_lt(v___x_422_, v___x_408_);
if (v___x_423_ == 0)
{
v___y_132_ = v___y_402_;
v___y_133_ = v___y_405_;
v___y_134_ = v___x_414_;
v___y_135_ = v___x_414_;
goto v___jp_131_;
}
else
{
uint64_t v___x_424_; 
v___x_424_ = 1ULL;
v___y_132_ = v___y_402_;
v___y_133_ = v___y_405_;
v___y_134_ = v___x_414_;
v___y_135_ = v___x_424_;
goto v___jp_131_;
}
}
}
else
{
uint64_t v_quotient_425_; uint64_t v___x_426_; uint64_t v___x_427_; uint64_t v___x_428_; uint64_t v_remainder_429_; uint64_t v___x_430_; uint64_t v_half_431_; uint8_t v___x_432_; 
v_quotient_425_ = lean_uint64_shift_right(v___x_408_, v___x_417_);
v___x_426_ = 1ULL;
v___x_427_ = lean_uint64_shift_left(v___x_426_, v___x_417_);
v___x_428_ = lean_uint64_sub(v___x_427_, v___x_426_);
v_remainder_429_ = lean_uint64_land(v___x_408_, v___x_428_);
v___x_430_ = lean_uint64_sub(v___x_417_, v___x_426_);
v_half_431_ = lean_uint64_shift_left(v___x_426_, v___x_430_);
v___x_432_ = lean_uint64_dec_lt(v_remainder_429_, v_half_431_);
if (v___x_432_ == 0)
{
uint8_t v___x_433_; 
v___x_433_ = lean_uint64_dec_lt(v_half_431_, v_remainder_429_);
if (v___x_433_ == 0)
{
uint64_t v___x_434_; uint8_t v___x_435_; 
v___x_434_ = lean_uint64_land(v_quotient_425_, v___x_426_);
v___x_435_ = lean_uint64_dec_eq(v___x_434_, v___x_414_);
if (v___x_435_ == 0)
{
uint64_t v___x_436_; 
v___x_436_ = lean_uint64_add(v_quotient_425_, v___x_426_);
v___y_132_ = v___y_402_;
v___y_133_ = v___y_405_;
v___y_134_ = v___x_414_;
v___y_135_ = v___x_436_;
goto v___jp_131_;
}
else
{
v___y_132_ = v___y_402_;
v___y_133_ = v___y_405_;
v___y_134_ = v___x_414_;
v___y_135_ = v_quotient_425_;
goto v___jp_131_;
}
}
else
{
uint64_t v___x_437_; 
v___x_437_ = lean_uint64_add(v_quotient_425_, v___x_426_);
v___y_132_ = v___y_402_;
v___y_133_ = v___y_405_;
v___y_134_ = v___x_414_;
v___y_135_ = v___x_437_;
goto v___jp_131_;
}
}
else
{
v___y_132_ = v___y_402_;
v___y_133_ = v___y_405_;
v___y_134_ = v___x_414_;
v___y_135_ = v_quotient_425_;
goto v___jp_131_;
}
}
}
else
{
v___y_132_ = v___y_402_;
v___y_133_ = v___y_405_;
v___y_134_ = v___x_414_;
v___y_135_ = v___x_408_;
goto v___jp_131_;
}
}
else
{
if (v___y_402_ == 0)
{
uint32_t v___x_438_; 
v___x_438_ = 0;
return v___x_438_;
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
v___jp_443_:
{
uint64_t v___x_449_; uint64_t v___x_450_; uint8_t v___x_451_; 
v___x_449_ = lean_uint32_to_uint64(v_ey_442_);
v___x_450_ = 0ULL;
v___x_451_ = lean_uint64_dec_eq(v___x_449_, v___x_450_);
if (v___x_451_ == 0)
{
uint64_t v___x_452_; uint64_t v___x_453_; 
v___x_452_ = 1ULL;
v___x_453_ = lean_uint64_sub(v___x_449_, v___x_452_);
v___y_402_ = v___y_445_;
v___y_403_ = v___y_444_;
v___y_404_ = v___y_446_;
v___y_405_ = v___y_447_;
v___y_406_ = v___y_448_;
v___y_407_ = v___x_453_;
goto v___jp_401_;
}
else
{
v___y_402_ = v___y_445_;
v___y_403_ = v___y_444_;
v___y_404_ = v___y_446_;
v___y_405_ = v___y_447_;
v___y_406_ = v___y_448_;
v___y_407_ = v___x_450_;
goto v___jp_401_;
}
}
v___jp_454_:
{
uint64_t v___x_459_; uint64_t v___x_460_; uint8_t v___x_461_; 
v___x_459_ = lean_uint32_to_uint64(v_ex_440_);
v___x_460_ = 0ULL;
v___x_461_ = lean_uint64_dec_eq(v___x_459_, v___x_460_);
if (v___x_461_ == 0)
{
uint64_t v___x_462_; uint64_t v___x_463_; 
v___x_462_ = 1ULL;
v___x_463_ = lean_uint64_sub(v___x_459_, v___x_462_);
v___y_444_ = v___y_456_;
v___y_445_ = v___y_455_;
v___y_446_ = v___y_458_;
v___y_447_ = v___y_457_;
v___y_448_ = v___x_463_;
goto v___jp_443_;
}
else
{
v___y_444_ = v___y_456_;
v___y_445_ = v___y_455_;
v___y_446_ = v___y_458_;
v___y_447_ = v___y_457_;
v___y_448_ = v___x_460_;
goto v___jp_443_;
}
}
v___jp_464_:
{
uint32_t v___x_469_; uint8_t v___x_470_; 
v___x_469_ = 0;
v___x_470_ = lean_uint32_dec_eq(v_ey_442_, v___x_469_);
if (v___x_470_ == 0)
{
uint64_t v___x_471_; uint64_t v___x_472_; uint64_t v___x_473_; 
v___x_471_ = lean_uint32_to_uint64(v___y_467_);
v___x_472_ = 8388608ULL;
v___x_473_ = lean_uint64_lor(v___x_471_, v___x_472_);
v___y_455_ = v___y_465_;
v___y_456_ = v___y_468_;
v___y_457_ = v___y_466_;
v___y_458_ = v___x_473_;
goto v___jp_454_;
}
else
{
uint64_t v___x_474_; 
v___x_474_ = lean_uint32_to_uint64(v___y_467_);
v___y_455_ = v___y_465_;
v___y_456_ = v___y_468_;
v___y_457_ = v___y_466_;
v___y_458_ = v___x_474_;
goto v___jp_454_;
}
}
v___jp_475_:
{
uint32_t v___x_477_; uint32_t v_xFraction_478_; uint32_t v_yFraction_479_; uint32_t v___x_480_; uint8_t v___x_481_; 
v___x_477_ = 8388607;
v_xFraction_478_ = lean_uint32_land(v___y_94_, v___x_477_);
v_yFraction_479_ = lean_uint32_land(v___y_95_, v___x_477_);
v___x_480_ = 0;
v___x_481_ = lean_uint32_dec_eq(v_ex_440_, v___x_480_);
if (v___x_481_ == 0)
{
uint64_t v___x_482_; uint64_t v___x_483_; uint64_t v___x_484_; 
v___x_482_ = lean_uint32_to_uint64(v_xFraction_478_);
v___x_483_ = 8388608ULL;
v___x_484_ = lean_uint64_lor(v___x_482_, v___x_483_);
v___y_465_ = v___y_476_;
v___y_466_ = v___x_477_;
v___y_467_ = v_yFraction_479_;
v___y_468_ = v___x_484_;
goto v___jp_464_;
}
else
{
uint64_t v___x_485_; 
v___x_485_ = lean_uint32_to_uint64(v_xFraction_478_);
v___y_465_ = v___y_476_;
v___y_466_ = v___x_477_;
v___y_467_ = v_yFraction_479_;
v___y_468_ = v___x_485_;
goto v___jp_464_;
}
}
v___jp_489_:
{
if (v___y_491_ == 0)
{
if (v___y_492_ == 0)
{
v___y_476_ = v___y_490_;
goto v___jp_475_;
}
else
{
v___y_476_ = v___x_488_;
goto v___jp_475_;
}
}
else
{
if (v___y_492_ == 0)
{
v___y_476_ = v___x_488_;
goto v___jp_475_;
}
else
{
v___y_476_ = v___y_490_;
goto v___jp_475_;
}
}
}
v___jp_493_:
{
uint32_t v___x_496_; uint32_t v___x_497_; uint32_t v___x_498_; uint8_t v___x_499_; 
v___x_496_ = 2147483648;
v___x_497_ = lean_uint32_land(v___y_95_, v___x_496_);
v___x_498_ = 0;
v___x_499_ = lean_uint32_dec_eq(v___x_497_, v___x_498_);
if (v___x_499_ == 0)
{
v___y_490_ = v___y_494_;
v___y_491_ = v___y_495_;
v___y_492_ = v___x_488_;
goto v___jp_489_;
}
else
{
v___y_490_ = v___y_494_;
v___y_491_ = v___y_495_;
v___y_492_ = v___y_494_;
goto v___jp_489_;
}
}
v___jp_500_:
{
if (v___y_501_ == 0)
{
uint32_t v___x_502_; uint32_t v___x_503_; uint32_t v___x_504_; uint8_t v___x_505_; 
v___x_502_ = 2147483648;
v___x_503_ = lean_uint32_land(v___y_94_, v___x_502_);
v___x_504_ = 0;
v___x_505_ = lean_uint32_dec_eq(v___x_503_, v___x_504_);
if (v___x_505_ == 0)
{
v___y_494_ = v___y_501_;
v___y_495_ = v___x_488_;
goto v___jp_493_;
}
else
{
v___y_494_ = v___y_501_;
v___y_495_ = v___y_501_;
goto v___jp_493_;
}
}
else
{
lean_object* v___x_506_; lean_object* v___x_507_; lean_object* v___x_508_; uint32_t v___x_509_; 
v___x_506_ = lean_uint32_to_nat(v___y_94_);
v___x_507_ = lean_uint32_to_nat(v___y_95_);
v___x_508_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_506_, v___x_507_);
v___x_509_ = lean_uint32_of_nat(v___x_508_);
lean_dec(v___x_508_);
return v___x_509_;
}
}
}
else
{
uint32_t v___x_522_; uint32_t v___x_523_; uint32_t v___x_524_; uint32_t v___x_525_; float v___x_526_; lean_object* v___x_527_; uint32_t v___x_528_; uint32_t v___x_529_; lean_object* v___x_530_; lean_object* v___x_531_; float v___x_532_; float v___x_533_; uint32_t v___x_534_; uint32_t v___x_535_; float v___x_536_; uint32_t v___x_537_; lean_object* v___x_538_; lean_object* v___x_539_; float v___x_540_; float v___x_541_; float v___x_542_; uint32_t v___x_543_; 
v___x_522_ = 8388607;
v___x_523_ = lean_uint32_land(v___y_94_, v___x_522_);
v___x_524_ = 8388608;
v___x_525_ = lean_uint32_lor(v___x_523_, v___x_524_);
v___x_526_ = lean_uint32_to_float32(v___x_525_);
v___x_527_ = lp_competition_R2W01b_scaleTable;
v___x_528_ = 23;
v___x_529_ = lean_uint32_shift_right(v___y_94_, v___x_528_);
v___x_530_ = lean_uint32_to_nat(v___x_529_);
v___x_531_ = lean_array_fget_borrowed(v___x_527_, v___x_530_);
lean_dec(v___x_530_);
v___x_532_ = lean_unbox_float32(v___x_531_);
v___x_533_ = lean_float32_mul(v___x_526_, v___x_532_);
v___x_534_ = lean_uint32_land(v___y_95_, v___x_522_);
v___x_535_ = lean_uint32_lor(v___x_534_, v___x_524_);
v___x_536_ = lean_uint32_to_float32(v___x_535_);
v___x_537_ = lean_uint32_shift_right(v___y_95_, v___x_528_);
v___x_538_ = lean_uint32_to_nat(v___x_537_);
v___x_539_ = lean_array_fget_borrowed(v___x_527_, v___x_538_);
lean_dec(v___x_538_);
v___x_540_ = lean_unbox_float32(v___x_539_);
v___x_541_ = lean_float32_mul(v___x_536_, v___x_540_);
v___x_542_ = lean_float32_mul(v___x_533_, v___x_541_);
v___x_543_ = lean_float32_to_bits(v___x_542_);
return v___x_543_;
}
v___jp_96_:
{
uint32_t v___x_98_; uint32_t v___x_99_; 
v___x_98_ = 8388608;
v___x_99_ = lean_uint32_lor(v___y_97_, v___x_98_);
return v___x_99_;
}
v___jp_100_:
{
uint32_t v___x_102_; uint32_t v___x_103_; 
v___x_102_ = 8388608;
v___x_103_ = lean_uint32_lor(v___y_101_, v___x_102_);
return v___x_103_;
}
v___jp_104_:
{
uint32_t v___x_108_; uint32_t v___x_109_; 
v___x_108_ = lean_uint32_land(v___y_106_, v___y_105_);
v___x_109_ = lean_uint32_lor(v___y_107_, v___x_108_);
return v___x_109_;
}
v___jp_110_:
{
uint8_t v___x_115_; 
v___x_115_ = lean_uint64_dec_eq(v___y_114_, v___y_113_);
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
v___y_105_ = v___y_112_;
v___y_106_ = v___x_118_;
v___y_107_ = v___x_119_;
goto v___jp_104_;
}
else
{
uint32_t v___x_120_; 
v___x_120_ = 2147483648;
v___y_105_ = v___y_112_;
v___y_106_ = v___x_118_;
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
v___y_101_ = v___x_121_;
goto v___jp_100_;
}
else
{
uint32_t v___x_122_; 
v___x_122_ = 2147483648;
v___y_101_ = v___x_122_;
goto v___jp_100_;
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
uint32_t v___x_129_; uint32_t v___x_130_; 
v___x_129_ = lean_uint32_land(v___y_127_, v___y_126_);
v___x_130_ = lean_uint32_lor(v___y_128_, v___x_129_);
return v___x_130_;
}
v___jp_131_:
{
uint8_t v___x_136_; 
v___x_136_ = lean_uint64_dec_eq(v___y_135_, v___y_134_);
if (v___x_136_ == 0)
{
uint64_t v___x_137_; uint8_t v___x_138_; 
v___x_137_ = 8388608ULL;
v___x_138_ = lean_uint64_dec_eq(v___y_135_, v___x_137_);
if (v___x_138_ == 0)
{
uint32_t v___x_139_; 
v___x_139_ = lean_uint64_to_uint32(v___y_135_);
if (v___y_132_ == 0)
{
uint32_t v___x_140_; 
v___x_140_ = 0;
v___y_126_ = v___y_133_;
v___y_127_ = v___x_139_;
v___y_128_ = v___x_140_;
goto v___jp_125_;
}
else
{
uint32_t v___x_141_; 
v___x_141_ = 2147483648;
v___y_126_ = v___y_133_;
v___y_127_ = v___x_139_;
v___y_128_ = v___x_141_;
goto v___jp_125_;
}
}
else
{
if (v___y_132_ == 0)
{
uint32_t v___x_142_; 
v___x_142_ = 0;
v___y_97_ = v___x_142_;
goto v___jp_96_;
}
else
{
uint32_t v___x_143_; 
v___x_143_ = 2147483648;
v___y_97_ = v___x_143_;
goto v___jp_96_;
}
}
}
else
{
if (v___y_132_ == 0)
{
uint32_t v___x_144_; 
v___x_144_ = 0;
return v___x_144_;
}
else
{
uint32_t v___x_145_; 
v___x_145_ = 2147483648;
return v___x_145_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_544_, lean_object* v___y_545_){
_start:
{
uint32_t v___y_3449__boxed_546_; uint32_t v___y_3450__boxed_547_; uint32_t v_res_548_; lean_object* v_r_549_; 
v___y_3449__boxed_546_ = lean_unbox_uint32(v___y_544_);
lean_dec(v___y_544_);
v___y_3450__boxed_547_ = lean_unbox_uint32(v___y_545_);
lean_dec(v___y_545_);
v_res_548_ = lp_competition_main___lam__1(v___y_3449__boxed_546_, v___y_3450__boxed_547_);
v_r_549_ = lean_box_uint32(v_res_548_);
return v_r_549_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_550_, uint32_t v___y_551_){
_start:
{
uint32_t v___y_553_; uint32_t v___y_557_; uint32_t v___y_561_; uint32_t v___y_562_; uint32_t v___y_563_; uint32_t v___y_567_; uint64_t v___y_568_; uint8_t v___y_569_; uint64_t v___y_570_; uint32_t v___y_582_; uint32_t v___y_583_; uint32_t v___y_584_; uint64_t v___y_588_; uint32_t v___y_589_; uint8_t v___y_590_; uint64_t v___y_591_; uint32_t v___x_602_; uint32_t v___x_603_; uint32_t v___x_604_; uint32_t v___x_605_; uint32_t v___x_606_; uint32_t v___x_607_; uint32_t v___x_608_; uint32_t v___x_609_; uint8_t v___x_610_; 
v___x_602_ = 2147483647;
v___x_603_ = lean_uint32_land(v___y_550_, v___x_602_);
v___x_604_ = 536870912;
v___x_605_ = lean_uint32_sub(v___x_603_, v___x_604_);
v___x_606_ = lean_uint32_land(v___y_551_, v___x_602_);
v___x_607_ = lean_uint32_sub(v___x_606_, v___x_604_);
v___x_608_ = lean_uint32_lor(v___x_605_, v___x_607_);
v___x_609_ = 1073741824;
v___x_610_ = lean_uint32_dec_lt(v___x_608_, v___x_609_);
if (v___x_610_ == 0)
{
uint32_t v___x_611_; uint32_t v___x_612_; uint32_t v___x_613_; uint32_t v___y_615_; uint32_t v___y_616_; uint32_t v___y_617_; uint32_t v___y_618_; uint32_t v___y_625_; uint32_t v___y_626_; uint8_t v___y_627_; uint32_t v___y_628_; uint32_t v___y_632_; uint64_t v___y_633_; uint8_t v___y_634_; uint64_t v___y_635_; uint64_t v___y_636_; uint8_t v___y_646_; uint32_t v___y_647_; uint64_t v___y_648_; uint8_t v___y_649_; uint64_t v___y_650_; uint64_t v___y_651_; uint64_t v___y_658_; uint32_t v___y_659_; uint64_t v___y_660_; uint8_t v___y_661_; uint64_t v___y_662_; uint32_t v___y_668_; uint64_t v___y_669_; uint8_t v___y_670_; uint64_t v___y_671_; uint64_t v___y_672_; uint64_t v___y_673_; uint32_t v___y_728_; uint64_t v___y_729_; uint64_t v___y_730_; uint8_t v___y_731_; uint64_t v___y_732_; uint64_t v___y_733_; uint64_t v___y_734_; uint64_t v___y_740_; uint64_t v___y_741_; uint32_t v___y_742_; uint64_t v___y_743_; uint8_t v___y_744_; uint64_t v___y_745_; uint64_t v___y_746_; uint64_t v___y_747_; uint64_t v___y_748_; uint64_t v___y_753_; uint32_t v___y_754_; uint64_t v___y_755_; uint8_t v___y_756_; uint64_t v___y_757_; uint64_t v___y_758_; uint64_t v___y_759_; uint64_t v___y_764_; uint32_t v___y_765_; uint64_t v___y_766_; uint64_t v___y_767_; uint64_t v___y_768_; uint8_t v___y_769_; uint64_t v___y_770_; uint64_t v___y_771_; uint64_t v___y_772_; uint32_t v___y_777_; uint64_t v___y_778_; uint8_t v___y_779_; uint64_t v___y_780_; uint64_t v___y_781_; uint64_t v___y_782_; uint64_t v___y_783_; uint64_t v___y_788_; uint64_t v___y_789_; uint32_t v___y_790_; uint64_t v___y_791_; uint8_t v___y_792_; uint64_t v___y_793_; uint64_t v___y_794_; uint64_t v___y_795_; uint64_t v___y_796_; uint32_t v___y_801_; uint64_t v___y_802_; uint64_t v___y_803_; uint8_t v___y_804_; uint64_t v___y_805_; uint64_t v___y_806_; uint64_t v___y_807_; uint32_t v___y_812_; uint64_t v___y_813_; uint8_t v___y_814_; uint64_t v___y_815_; uint64_t v___y_816_; uint64_t v___y_817_; uint64_t v___y_818_; uint64_t v___y_819_; uint64_t v___y_820_; uint32_t v___y_825_; uint64_t v___y_826_; uint8_t v___y_827_; uint64_t v___y_828_; uint64_t v___y_829_; uint64_t v___y_830_; uint64_t v___y_831_; uint32_t v___y_836_; uint64_t v___y_837_; uint64_t v___y_838_; uint8_t v___y_839_; uint64_t v___y_840_; uint64_t v___y_841_; uint64_t v___y_842_; uint32_t v___y_846_; uint8_t v___y_847_; uint64_t v___y_848_; uint64_t v___y_849_; uint32_t v___y_858_; uint64_t v___y_859_; uint8_t v___y_860_; uint64_t v___y_861_; uint64_t v___y_862_; uint64_t v___y_863_; uint32_t v_ex_896_; uint32_t v___x_897_; uint32_t v_ey_898_; uint32_t v___y_900_; uint64_t v___y_901_; uint8_t v___y_902_; uint64_t v___y_903_; uint64_t v___y_904_; uint32_t v___y_911_; uint64_t v___y_912_; uint8_t v___y_913_; uint64_t v___y_914_; uint32_t v___y_921_; uint32_t v___y_922_; uint8_t v___y_923_; uint64_t v___y_924_; uint8_t v___y_932_; uint32_t v___x_942_; uint32_t v___x_943_; uint8_t v___x_944_; uint8_t v___y_946_; uint8_t v___y_947_; uint8_t v___y_948_; uint8_t v___y_950_; uint8_t v___y_951_; uint8_t v___y_957_; 
v___x_611_ = 23;
v___x_612_ = lean_uint32_shift_right(v___y_550_, v___x_611_);
v___x_613_ = 255;
v_ex_896_ = lean_uint32_land(v___x_612_, v___x_613_);
v___x_897_ = lean_uint32_shift_right(v___y_551_, v___x_611_);
v_ey_898_ = lean_uint32_land(v___x_897_, v___x_613_);
v___x_942_ = lean_uint32_add(v_ex_896_, v_ey_898_);
v___x_943_ = 128;
v___x_944_ = lean_uint32_dec_lt(v___x_942_, v___x_943_);
if (v___x_944_ == 0)
{
float v___x_966_; float v___x_967_; float v_result_968_; uint8_t v___x_969_; 
v___x_966_ = lean_float32_of_bits(v___y_550_);
v___x_967_ = lean_float32_of_bits(v___y_551_);
v_result_968_ = lean_float32_mul(v___x_966_, v___x_967_);
v___x_969_ = lean_float32_beq(v_result_968_, v_result_968_);
if (v___x_969_ == 0)
{
uint32_t v___x_970_; 
v___x_970_ = lp_competition_Submission_FastMul_mul(v___y_550_, v___y_551_);
return v___x_970_;
}
else
{
uint32_t v___x_971_; 
v___x_971_ = lean_float32_to_bits(v_result_968_);
return v___x_971_;
}
}
else
{
uint32_t v___x_972_; uint32_t v___x_973_; uint32_t v___x_974_; uint8_t v___x_975_; 
v___x_972_ = 4278190080;
v___x_973_ = 1;
v___x_974_ = lean_uint32_shift_left(v___y_550_, v___x_973_);
v___x_975_ = lean_uint32_dec_le(v___x_972_, v___x_974_);
if (v___x_975_ == 0)
{
uint32_t v___x_976_; uint8_t v___x_977_; 
v___x_976_ = lean_uint32_shift_left(v___y_551_, v___x_973_);
v___x_977_ = lean_uint32_dec_le(v___x_972_, v___x_976_);
v___y_957_ = v___x_977_;
goto v___jp_956_;
}
else
{
v___y_957_ = v___x_975_;
goto v___jp_956_;
}
}
v___jp_614_:
{
uint32_t v___x_619_; uint32_t v___x_620_; uint32_t v___x_621_; uint32_t v___x_622_; uint32_t v___x_623_; 
v___x_619_ = lean_uint32_land(v___y_616_, v___x_613_);
v___x_620_ = lean_uint32_shift_left(v___x_619_, v___x_611_);
v___x_621_ = lean_uint32_lor(v___y_618_, v___x_620_);
v___x_622_ = lean_uint32_land(v___y_617_, v___y_615_);
v___x_623_ = lean_uint32_lor(v___x_621_, v___x_622_);
return v___x_623_;
}
v___jp_624_:
{
if (v___y_627_ == 0)
{
uint32_t v___x_629_; 
v___x_629_ = 0;
v___y_615_ = v___y_625_;
v___y_616_ = v___y_626_;
v___y_617_ = v___y_628_;
v___y_618_ = v___x_629_;
goto v___jp_614_;
}
else
{
uint32_t v___x_630_; 
v___x_630_ = 2147483648;
v___y_615_ = v___y_625_;
v___y_616_ = v___y_626_;
v___y_617_ = v___y_628_;
v___y_618_ = v___x_630_;
goto v___jp_614_;
}
}
v___jp_631_:
{
uint64_t v___x_637_; uint64_t v_encodedExponent_638_; uint32_t v___x_639_; uint64_t v___x_640_; uint8_t v___x_641_; 
v___x_637_ = 171ULL;
v_encodedExponent_638_ = lean_uint64_sub(v___y_635_, v___x_637_);
v___x_639_ = lean_uint64_to_uint32(v_encodedExponent_638_);
v___x_640_ = 8388608ULL;
v___x_641_ = lean_uint64_dec_lt(v___y_636_, v___x_640_);
if (v___x_641_ == 0)
{
uint64_t v___x_642_; uint32_t v___x_643_; 
v___x_642_ = lean_uint64_sub(v___y_636_, v___x_640_);
v___x_643_ = lean_uint64_to_uint32(v___x_642_);
v___y_625_ = v___y_632_;
v___y_626_ = v___x_639_;
v___y_627_ = v___y_634_;
v___y_628_ = v___x_643_;
goto v___jp_624_;
}
else
{
uint32_t v___x_644_; 
v___x_644_ = lean_uint64_to_uint32(v___y_633_);
v___y_625_ = v___y_632_;
v___y_626_ = v___x_639_;
v___y_627_ = v___y_634_;
v___y_628_ = v___x_644_;
goto v___jp_624_;
}
}
v___jp_645_:
{
uint64_t v___x_652_; uint8_t v___x_653_; 
v___x_652_ = 425ULL;
v___x_653_ = lean_uint64_dec_lt(v___x_652_, v___y_651_);
if (v___x_653_ == 0)
{
if (v___y_646_ == 0)
{
v___y_632_ = v___y_647_;
v___y_633_ = v___y_648_;
v___y_634_ = v___y_649_;
v___y_635_ = v___y_651_;
v___y_636_ = v___y_650_;
goto v___jp_631_;
}
else
{
uint64_t v___x_654_; 
v___x_654_ = 8388608ULL;
v___y_632_ = v___y_647_;
v___y_633_ = v___y_648_;
v___y_634_ = v___y_649_;
v___y_635_ = v___y_651_;
v___y_636_ = v___x_654_;
goto v___jp_631_;
}
}
else
{
if (v___y_649_ == 0)
{
uint32_t v___x_655_; 
v___x_655_ = 2139095040;
return v___x_655_;
}
else
{
uint32_t v___x_656_; 
v___x_656_ = 4286578688;
return v___x_656_;
}
}
}
v___jp_657_:
{
uint64_t v___x_663_; uint8_t v_carry_664_; 
v___x_663_ = 16777216ULL;
v_carry_664_ = lean_uint64_dec_eq(v___y_662_, v___x_663_);
if (v_carry_664_ == 0)
{
v___y_646_ = v_carry_664_;
v___y_647_ = v___y_659_;
v___y_648_ = v___y_660_;
v___y_649_ = v___y_661_;
v___y_650_ = v___y_662_;
v___y_651_ = v___y_658_;
goto v___jp_645_;
}
else
{
uint64_t v___x_665_; uint64_t v___x_666_; 
v___x_665_ = 1ULL;
v___x_666_ = lean_uint64_add(v___y_658_, v___x_665_);
v___y_646_ = v_carry_664_;
v___y_647_ = v___y_659_;
v___y_648_ = v___y_660_;
v___y_649_ = v___y_661_;
v___y_650_ = v___y_662_;
v___y_651_ = v___x_666_;
goto v___jp_645_;
}
}
v___jp_667_:
{
uint64_t v_position_674_; uint64_t v___x_675_; uint8_t v___x_676_; 
v_position_674_ = lean_uint64_add(v___y_673_, v___y_672_);
v___x_675_ = 172ULL;
v___x_676_ = lean_uint64_dec_lt(v_position_674_, v___x_675_);
if (v___x_676_ == 0)
{
uint64_t v___x_677_; uint8_t v___x_678_; 
v___x_677_ = 23ULL;
v___x_678_ = lean_uint64_dec_lt(v___y_673_, v___x_677_);
if (v___x_678_ == 0)
{
uint64_t v___x_679_; uint8_t v___x_680_; 
v___x_679_ = lean_uint64_sub(v___y_673_, v___x_677_);
v___x_680_ = lean_uint64_dec_eq(v___x_679_, v___y_669_);
if (v___x_680_ == 0)
{
uint64_t v___x_681_; uint8_t v___x_682_; 
v___x_681_ = 64ULL;
v___x_682_ = lean_uint64_dec_lt(v___x_679_, v___x_681_);
if (v___x_682_ == 0)
{
uint8_t v___x_683_; 
v___x_683_ = lean_uint64_dec_eq(v___x_679_, v___x_681_);
if (v___x_683_ == 0)
{
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v___y_669_;
goto v___jp_657_;
}
else
{
uint64_t v___x_684_; uint8_t v___x_685_; 
v___x_684_ = 9223372036854775808ULL;
v___x_685_ = lean_uint64_dec_lt(v___x_684_, v___y_671_);
if (v___x_685_ == 0)
{
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v___y_669_;
goto v___jp_657_;
}
else
{
uint64_t v___x_686_; 
v___x_686_ = 1ULL;
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v___x_686_;
goto v___jp_657_;
}
}
}
else
{
uint64_t v_quotient_687_; uint64_t v___x_688_; uint64_t v___x_689_; uint64_t v___x_690_; uint64_t v_remainder_691_; uint64_t v___x_692_; uint64_t v_half_693_; uint8_t v___x_694_; 
v_quotient_687_ = lean_uint64_shift_right(v___y_671_, v___x_679_);
v___x_688_ = 1ULL;
v___x_689_ = lean_uint64_shift_left(v___x_688_, v___x_679_);
v___x_690_ = lean_uint64_sub(v___x_689_, v___x_688_);
v_remainder_691_ = lean_uint64_land(v___y_671_, v___x_690_);
v___x_692_ = lean_uint64_sub(v___x_679_, v___x_688_);
v_half_693_ = lean_uint64_shift_left(v___x_688_, v___x_692_);
v___x_694_ = lean_uint64_dec_lt(v_remainder_691_, v_half_693_);
if (v___x_694_ == 0)
{
uint8_t v___x_695_; 
v___x_695_ = lean_uint64_dec_lt(v_half_693_, v_remainder_691_);
if (v___x_695_ == 0)
{
uint64_t v___x_696_; uint8_t v___x_697_; 
v___x_696_ = lean_uint64_land(v_quotient_687_, v___x_688_);
v___x_697_ = lean_uint64_dec_eq(v___x_696_, v___y_669_);
if (v___x_697_ == 0)
{
uint64_t v___x_698_; 
v___x_698_ = lean_uint64_add(v_quotient_687_, v___x_688_);
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v___x_698_;
goto v___jp_657_;
}
else
{
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v_quotient_687_;
goto v___jp_657_;
}
}
else
{
uint64_t v___x_699_; 
v___x_699_ = lean_uint64_add(v_quotient_687_, v___x_688_);
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v___x_699_;
goto v___jp_657_;
}
}
else
{
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v_quotient_687_;
goto v___jp_657_;
}
}
}
else
{
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v___y_671_;
goto v___jp_657_;
}
}
else
{
uint64_t v___x_700_; uint64_t v___x_701_; 
v___x_700_ = lean_uint64_sub(v___x_677_, v___y_673_);
v___x_701_ = lean_uint64_shift_left(v___y_671_, v___x_700_);
v___y_658_ = v_position_674_;
v___y_659_ = v___y_668_;
v___y_660_ = v___y_669_;
v___y_661_ = v___y_670_;
v___y_662_ = v___x_701_;
goto v___jp_657_;
}
}
else
{
uint64_t v___x_702_; uint8_t v___x_703_; 
v___x_702_ = 149ULL;
v___x_703_ = lean_uint64_dec_lt(v___y_672_, v___x_702_);
if (v___x_703_ == 0)
{
uint64_t v___x_704_; uint64_t v___x_705_; 
v___x_704_ = lean_uint64_sub(v___y_672_, v___x_702_);
v___x_705_ = lean_uint64_shift_left(v___y_671_, v___x_704_);
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v___x_705_;
goto v___jp_566_;
}
else
{
uint64_t v___x_706_; uint8_t v___x_707_; 
v___x_706_ = lean_uint64_sub(v___x_702_, v___y_672_);
v___x_707_ = lean_uint64_dec_eq(v___x_706_, v___y_669_);
if (v___x_707_ == 0)
{
uint64_t v___x_708_; uint8_t v___x_709_; 
v___x_708_ = 64ULL;
v___x_709_ = lean_uint64_dec_lt(v___x_706_, v___x_708_);
if (v___x_709_ == 0)
{
uint8_t v___x_710_; 
v___x_710_ = lean_uint64_dec_eq(v___x_706_, v___x_708_);
if (v___x_710_ == 0)
{
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v___y_669_;
goto v___jp_566_;
}
else
{
uint64_t v___x_711_; uint8_t v___x_712_; 
v___x_711_ = 9223372036854775808ULL;
v___x_712_ = lean_uint64_dec_lt(v___x_711_, v___y_671_);
if (v___x_712_ == 0)
{
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v___y_669_;
goto v___jp_566_;
}
else
{
uint64_t v___x_713_; 
v___x_713_ = 1ULL;
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v___x_713_;
goto v___jp_566_;
}
}
}
else
{
uint64_t v_quotient_714_; uint64_t v___x_715_; uint64_t v___x_716_; uint64_t v___x_717_; uint64_t v_remainder_718_; uint64_t v___x_719_; uint64_t v_half_720_; uint8_t v___x_721_; 
v_quotient_714_ = lean_uint64_shift_right(v___y_671_, v___x_706_);
v___x_715_ = 1ULL;
v___x_716_ = lean_uint64_shift_left(v___x_715_, v___x_706_);
v___x_717_ = lean_uint64_sub(v___x_716_, v___x_715_);
v_remainder_718_ = lean_uint64_land(v___y_671_, v___x_717_);
v___x_719_ = lean_uint64_sub(v___x_706_, v___x_715_);
v_half_720_ = lean_uint64_shift_left(v___x_715_, v___x_719_);
v___x_721_ = lean_uint64_dec_lt(v_remainder_718_, v_half_720_);
if (v___x_721_ == 0)
{
uint8_t v___x_722_; 
v___x_722_ = lean_uint64_dec_lt(v_half_720_, v_remainder_718_);
if (v___x_722_ == 0)
{
uint64_t v___x_723_; uint8_t v___x_724_; 
v___x_723_ = lean_uint64_land(v_quotient_714_, v___x_715_);
v___x_724_ = lean_uint64_dec_eq(v___x_723_, v___y_669_);
if (v___x_724_ == 0)
{
uint64_t v___x_725_; 
v___x_725_ = lean_uint64_add(v_quotient_714_, v___x_715_);
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v___x_725_;
goto v___jp_566_;
}
else
{
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v_quotient_714_;
goto v___jp_566_;
}
}
else
{
uint64_t v___x_726_; 
v___x_726_ = lean_uint64_add(v_quotient_714_, v___x_715_);
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v___x_726_;
goto v___jp_566_;
}
}
else
{
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v_quotient_714_;
goto v___jp_566_;
}
}
}
else
{
v___y_567_ = v___y_668_;
v___y_568_ = v___y_669_;
v___y_569_ = v___y_670_;
v___y_570_ = v___y_671_;
goto v___jp_566_;
}
}
}
}
v___jp_727_:
{
uint64_t v___x_735_; uint64_t v___x_736_; uint8_t v___x_737_; 
v___x_735_ = 1ULL;
v___x_736_ = lean_uint64_shift_right(v___y_730_, v___x_735_);
v___x_737_ = lean_uint64_dec_eq(v___x_736_, v___y_729_);
if (v___x_737_ == 0)
{
uint64_t v___x_738_; 
v___x_738_ = lean_uint64_add(v___y_734_, v___x_735_);
v___y_668_ = v___y_728_;
v___y_669_ = v___y_729_;
v___y_670_ = v___y_731_;
v___y_671_ = v___y_732_;
v___y_672_ = v___y_733_;
v___y_673_ = v___x_738_;
goto v___jp_667_;
}
else
{
v___y_668_ = v___y_728_;
v___y_669_ = v___y_729_;
v___y_670_ = v___y_731_;
v___y_671_ = v___y_732_;
v___y_672_ = v___y_733_;
v___y_673_ = v___y_734_;
goto v___jp_667_;
}
}
v___jp_739_:
{
uint64_t v___x_749_; uint8_t v___x_750_; 
v___x_749_ = lean_uint64_shift_right(v___y_740_, v___y_747_);
v___x_750_ = lean_uint64_dec_eq(v___x_749_, v___y_743_);
if (v___x_750_ == 0)
{
uint64_t v___x_751_; 
v___x_751_ = lean_uint64_add(v___y_741_, v___y_747_);
v___y_728_ = v___y_742_;
v___y_729_ = v___y_743_;
v___y_730_ = v___y_748_;
v___y_731_ = v___y_744_;
v___y_732_ = v___y_745_;
v___y_733_ = v___y_746_;
v___y_734_ = v___x_751_;
goto v___jp_727_;
}
else
{
v___y_728_ = v___y_742_;
v___y_729_ = v___y_743_;
v___y_730_ = v___y_748_;
v___y_731_ = v___y_744_;
v___y_732_ = v___y_745_;
v___y_733_ = v___y_746_;
v___y_734_ = v___y_741_;
goto v___jp_727_;
}
}
v___jp_752_:
{
uint64_t v___x_760_; uint64_t v___x_761_; uint8_t v___x_762_; 
v___x_760_ = 2ULL;
v___x_761_ = lean_uint64_shift_right(v___y_753_, v___x_760_);
v___x_762_ = lean_uint64_dec_eq(v___x_761_, v___y_755_);
if (v___x_762_ == 0)
{
v___y_740_ = v___y_753_;
v___y_741_ = v___y_759_;
v___y_742_ = v___y_754_;
v___y_743_ = v___y_755_;
v___y_744_ = v___y_756_;
v___y_745_ = v___y_757_;
v___y_746_ = v___y_758_;
v___y_747_ = v___x_760_;
v___y_748_ = v___x_761_;
goto v___jp_739_;
}
else
{
v___y_740_ = v___y_753_;
v___y_741_ = v___y_759_;
v___y_742_ = v___y_754_;
v___y_743_ = v___y_755_;
v___y_744_ = v___y_756_;
v___y_745_ = v___y_757_;
v___y_746_ = v___y_758_;
v___y_747_ = v___x_760_;
v___y_748_ = v___y_753_;
goto v___jp_739_;
}
}
v___jp_763_:
{
uint64_t v___x_773_; uint8_t v___x_774_; 
v___x_773_ = lean_uint64_shift_right(v___y_768_, v___y_764_);
v___x_774_ = lean_uint64_dec_eq(v___x_773_, v___y_766_);
if (v___x_774_ == 0)
{
uint64_t v___x_775_; 
v___x_775_ = lean_uint64_add(v___y_767_, v___y_764_);
v___y_753_ = v___y_772_;
v___y_754_ = v___y_765_;
v___y_755_ = v___y_766_;
v___y_756_ = v___y_769_;
v___y_757_ = v___y_770_;
v___y_758_ = v___y_771_;
v___y_759_ = v___x_775_;
goto v___jp_752_;
}
else
{
v___y_753_ = v___y_772_;
v___y_754_ = v___y_765_;
v___y_755_ = v___y_766_;
v___y_756_ = v___y_769_;
v___y_757_ = v___y_770_;
v___y_758_ = v___y_771_;
v___y_759_ = v___y_767_;
goto v___jp_752_;
}
}
v___jp_776_:
{
uint64_t v___x_784_; uint64_t v___x_785_; uint8_t v___x_786_; 
v___x_784_ = 4ULL;
v___x_785_ = lean_uint64_shift_right(v___y_780_, v___x_784_);
v___x_786_ = lean_uint64_dec_eq(v___x_785_, v___y_778_);
if (v___x_786_ == 0)
{
v___y_764_ = v___x_784_;
v___y_765_ = v___y_777_;
v___y_766_ = v___y_778_;
v___y_767_ = v___y_783_;
v___y_768_ = v___y_780_;
v___y_769_ = v___y_779_;
v___y_770_ = v___y_781_;
v___y_771_ = v___y_782_;
v___y_772_ = v___x_785_;
goto v___jp_763_;
}
else
{
v___y_764_ = v___x_784_;
v___y_765_ = v___y_777_;
v___y_766_ = v___y_778_;
v___y_767_ = v___y_783_;
v___y_768_ = v___y_780_;
v___y_769_ = v___y_779_;
v___y_770_ = v___y_781_;
v___y_771_ = v___y_782_;
v___y_772_ = v___y_780_;
goto v___jp_763_;
}
}
v___jp_787_:
{
uint64_t v___x_797_; uint8_t v___x_798_; 
v___x_797_ = lean_uint64_shift_right(v___y_789_, v___y_795_);
v___x_798_ = lean_uint64_dec_eq(v___x_797_, v___y_791_);
if (v___x_798_ == 0)
{
uint64_t v___x_799_; 
v___x_799_ = lean_uint64_add(v___y_788_, v___y_795_);
v___y_777_ = v___y_790_;
v___y_778_ = v___y_791_;
v___y_779_ = v___y_792_;
v___y_780_ = v___y_796_;
v___y_781_ = v___y_793_;
v___y_782_ = v___y_794_;
v___y_783_ = v___x_799_;
goto v___jp_776_;
}
else
{
v___y_777_ = v___y_790_;
v___y_778_ = v___y_791_;
v___y_779_ = v___y_792_;
v___y_780_ = v___y_796_;
v___y_781_ = v___y_793_;
v___y_782_ = v___y_794_;
v___y_783_ = v___y_788_;
goto v___jp_776_;
}
}
v___jp_800_:
{
uint64_t v___x_808_; uint64_t v___x_809_; uint8_t v___x_810_; 
v___x_808_ = 8ULL;
v___x_809_ = lean_uint64_shift_right(v___y_802_, v___x_808_);
v___x_810_ = lean_uint64_dec_eq(v___x_809_, v___y_803_);
if (v___x_810_ == 0)
{
v___y_788_ = v___y_807_;
v___y_789_ = v___y_802_;
v___y_790_ = v___y_801_;
v___y_791_ = v___y_803_;
v___y_792_ = v___y_804_;
v___y_793_ = v___y_805_;
v___y_794_ = v___y_806_;
v___y_795_ = v___x_808_;
v___y_796_ = v___x_809_;
goto v___jp_787_;
}
else
{
v___y_788_ = v___y_807_;
v___y_789_ = v___y_802_;
v___y_790_ = v___y_801_;
v___y_791_ = v___y_803_;
v___y_792_ = v___y_804_;
v___y_793_ = v___y_805_;
v___y_794_ = v___y_806_;
v___y_795_ = v___x_808_;
v___y_796_ = v___y_802_;
goto v___jp_787_;
}
}
v___jp_811_:
{
uint64_t v___x_821_; uint8_t v___x_822_; 
v___x_821_ = lean_uint64_shift_right(v___y_818_, v___y_817_);
v___x_822_ = lean_uint64_dec_eq(v___x_821_, v___y_813_);
if (v___x_822_ == 0)
{
uint64_t v___x_823_; 
v___x_823_ = lean_uint64_add(v___y_819_, v___y_817_);
v___y_801_ = v___y_812_;
v___y_802_ = v___y_820_;
v___y_803_ = v___y_813_;
v___y_804_ = v___y_814_;
v___y_805_ = v___y_815_;
v___y_806_ = v___y_816_;
v___y_807_ = v___x_823_;
goto v___jp_800_;
}
else
{
v___y_801_ = v___y_812_;
v___y_802_ = v___y_820_;
v___y_803_ = v___y_813_;
v___y_804_ = v___y_814_;
v___y_805_ = v___y_815_;
v___y_806_ = v___y_816_;
v___y_807_ = v___y_819_;
goto v___jp_800_;
}
}
v___jp_824_:
{
uint64_t v___x_832_; uint64_t v___x_833_; uint8_t v___x_834_; 
v___x_832_ = 16ULL;
v___x_833_ = lean_uint64_shift_right(v___y_830_, v___x_832_);
v___x_834_ = lean_uint64_dec_eq(v___x_833_, v___y_826_);
if (v___x_834_ == 0)
{
v___y_812_ = v___y_825_;
v___y_813_ = v___y_826_;
v___y_814_ = v___y_827_;
v___y_815_ = v___y_828_;
v___y_816_ = v___y_829_;
v___y_817_ = v___x_832_;
v___y_818_ = v___y_830_;
v___y_819_ = v___y_831_;
v___y_820_ = v___x_833_;
goto v___jp_811_;
}
else
{
v___y_812_ = v___y_825_;
v___y_813_ = v___y_826_;
v___y_814_ = v___y_827_;
v___y_815_ = v___y_828_;
v___y_816_ = v___y_829_;
v___y_817_ = v___x_832_;
v___y_818_ = v___y_830_;
v___y_819_ = v___y_831_;
v___y_820_ = v___y_830_;
goto v___jp_811_;
}
}
v___jp_835_:
{
uint64_t v___x_843_; uint8_t v___x_844_; 
v___x_843_ = lean_uint64_shift_right(v___y_840_, v___y_837_);
v___x_844_ = lean_uint64_dec_eq(v___x_843_, v___y_838_);
if (v___x_844_ == 0)
{
v___y_825_ = v___y_836_;
v___y_826_ = v___y_838_;
v___y_827_ = v___y_839_;
v___y_828_ = v___y_840_;
v___y_829_ = v___y_841_;
v___y_830_ = v___y_842_;
v___y_831_ = v___y_837_;
goto v___jp_824_;
}
else
{
v___y_825_ = v___y_836_;
v___y_826_ = v___y_838_;
v___y_827_ = v___y_839_;
v___y_828_ = v___y_840_;
v___y_829_ = v___y_841_;
v___y_830_ = v___y_842_;
v___y_831_ = v___y_838_;
goto v___jp_824_;
}
}
v___jp_845_:
{
uint64_t v___x_850_; uint8_t v___x_851_; 
v___x_850_ = 0ULL;
v___x_851_ = lean_uint64_dec_eq(v___y_848_, v___x_850_);
if (v___x_851_ == 0)
{
uint64_t v___x_852_; uint64_t v___x_853_; uint8_t v___x_854_; 
v___x_852_ = 32ULL;
v___x_853_ = lean_uint64_shift_right(v___y_848_, v___x_852_);
v___x_854_ = lean_uint64_dec_eq(v___x_853_, v___x_850_);
if (v___x_854_ == 0)
{
v___y_836_ = v___y_846_;
v___y_837_ = v___x_852_;
v___y_838_ = v___x_850_;
v___y_839_ = v___y_847_;
v___y_840_ = v___y_848_;
v___y_841_ = v___y_849_;
v___y_842_ = v___x_853_;
goto v___jp_835_;
}
else
{
v___y_836_ = v___y_846_;
v___y_837_ = v___x_852_;
v___y_838_ = v___x_850_;
v___y_839_ = v___y_847_;
v___y_840_ = v___y_848_;
v___y_841_ = v___y_849_;
v___y_842_ = v___y_848_;
goto v___jp_835_;
}
}
else
{
if (v___y_847_ == 0)
{
uint32_t v___x_855_; 
v___x_855_ = 0;
return v___x_855_;
}
else
{
uint32_t v___x_856_; 
v___x_856_ = 2147483648;
return v___x_856_;
}
}
}
v___jp_857_:
{
uint64_t v___x_864_; uint64_t v___x_865_; uint64_t v___x_866_; uint8_t v___x_867_; 
v___x_864_ = lean_uint64_mul(v___y_859_, v___y_862_);
v___x_865_ = lean_uint64_add(v___y_861_, v___y_863_);
v___x_866_ = 281474976710656ULL;
v___x_867_ = lean_uint64_dec_lt(v___x_864_, v___x_866_);
if (v___x_867_ == 0)
{
v___y_846_ = v___y_858_;
v___y_847_ = v___y_860_;
v___y_848_ = v___x_864_;
v___y_849_ = v___x_865_;
goto v___jp_845_;
}
else
{
uint64_t v___x_868_; uint8_t v___x_869_; 
v___x_868_ = 123ULL;
v___x_869_ = lean_uint64_dec_le(v___x_865_, v___x_868_);
if (v___x_869_ == 0)
{
v___y_846_ = v___y_858_;
v___y_847_ = v___y_860_;
v___y_848_ = v___x_864_;
v___y_849_ = v___x_865_;
goto v___jp_845_;
}
else
{
uint64_t v___x_870_; uint8_t v___x_871_; 
v___x_870_ = 0ULL;
v___x_871_ = lean_uint64_dec_eq(v___x_864_, v___x_870_);
if (v___x_871_ == 0)
{
uint64_t v___x_872_; uint64_t v___x_873_; uint8_t v___x_874_; 
v___x_872_ = 149ULL;
v___x_873_ = lean_uint64_sub(v___x_872_, v___x_865_);
v___x_874_ = lean_uint64_dec_eq(v___x_873_, v___x_870_);
if (v___x_874_ == 0)
{
uint64_t v___x_875_; uint8_t v___x_876_; 
v___x_875_ = 64ULL;
v___x_876_ = lean_uint64_dec_lt(v___x_873_, v___x_875_);
if (v___x_876_ == 0)
{
uint8_t v___x_877_; 
v___x_877_ = lean_uint64_dec_eq(v___x_873_, v___x_875_);
if (v___x_877_ == 0)
{
v___y_588_ = v___x_870_;
v___y_589_ = v___y_858_;
v___y_590_ = v___y_860_;
v___y_591_ = v___x_870_;
goto v___jp_587_;
}
else
{
uint64_t v___x_878_; uint8_t v___x_879_; 
v___x_878_ = 9223372036854775808ULL;
v___x_879_ = lean_uint64_dec_lt(v___x_878_, v___x_864_);
if (v___x_879_ == 0)
{
v___y_588_ = v___x_870_;
v___y_589_ = v___y_858_;
v___y_590_ = v___y_860_;
v___y_591_ = v___x_870_;
goto v___jp_587_;
}
else
{
uint64_t v___x_880_; 
v___x_880_ = 1ULL;
v___y_588_ = v___x_870_;
v___y_589_ = v___y_858_;
v___y_590_ = v___y_860_;
v___y_591_ = v___x_880_;
goto v___jp_587_;
}
}
}
else
{
uint64_t v_quotient_881_; uint64_t v___x_882_; uint64_t v___x_883_; uint64_t v___x_884_; uint64_t v_remainder_885_; uint64_t v___x_886_; uint64_t v_half_887_; uint8_t v___x_888_; 
v_quotient_881_ = lean_uint64_shift_right(v___x_864_, v___x_873_);
v___x_882_ = 1ULL;
v___x_883_ = lean_uint64_shift_left(v___x_882_, v___x_873_);
v___x_884_ = lean_uint64_sub(v___x_883_, v___x_882_);
v_remainder_885_ = lean_uint64_land(v___x_864_, v___x_884_);
v___x_886_ = lean_uint64_sub(v___x_873_, v___x_882_);
v_half_887_ = lean_uint64_shift_left(v___x_882_, v___x_886_);
v___x_888_ = lean_uint64_dec_lt(v_remainder_885_, v_half_887_);
if (v___x_888_ == 0)
{
uint8_t v___x_889_; 
v___x_889_ = lean_uint64_dec_lt(v_half_887_, v_remainder_885_);
if (v___x_889_ == 0)
{
uint64_t v___x_890_; uint8_t v___x_891_; 
v___x_890_ = lean_uint64_land(v_quotient_881_, v___x_882_);
v___x_891_ = lean_uint64_dec_eq(v___x_890_, v___x_870_);
if (v___x_891_ == 0)
{
uint64_t v___x_892_; 
v___x_892_ = lean_uint64_add(v_quotient_881_, v___x_882_);
v___y_588_ = v___x_870_;
v___y_589_ = v___y_858_;
v___y_590_ = v___y_860_;
v___y_591_ = v___x_892_;
goto v___jp_587_;
}
else
{
v___y_588_ = v___x_870_;
v___y_589_ = v___y_858_;
v___y_590_ = v___y_860_;
v___y_591_ = v_quotient_881_;
goto v___jp_587_;
}
}
else
{
uint64_t v___x_893_; 
v___x_893_ = lean_uint64_add(v_quotient_881_, v___x_882_);
v___y_588_ = v___x_870_;
v___y_589_ = v___y_858_;
v___y_590_ = v___y_860_;
v___y_591_ = v___x_893_;
goto v___jp_587_;
}
}
else
{
v___y_588_ = v___x_870_;
v___y_589_ = v___y_858_;
v___y_590_ = v___y_860_;
v___y_591_ = v_quotient_881_;
goto v___jp_587_;
}
}
}
else
{
v___y_588_ = v___x_870_;
v___y_589_ = v___y_858_;
v___y_590_ = v___y_860_;
v___y_591_ = v___x_864_;
goto v___jp_587_;
}
}
else
{
if (v___y_860_ == 0)
{
uint32_t v___x_894_; 
v___x_894_ = 0;
return v___x_894_;
}
else
{
uint32_t v___x_895_; 
v___x_895_ = 2147483648;
return v___x_895_;
}
}
}
}
}
v___jp_899_:
{
uint64_t v___x_905_; uint64_t v___x_906_; uint8_t v___x_907_; 
v___x_905_ = lean_uint32_to_uint64(v_ey_898_);
v___x_906_ = 0ULL;
v___x_907_ = lean_uint64_dec_eq(v___x_905_, v___x_906_);
if (v___x_907_ == 0)
{
uint64_t v___x_908_; uint64_t v___x_909_; 
v___x_908_ = 1ULL;
v___x_909_ = lean_uint64_sub(v___x_905_, v___x_908_);
v___y_858_ = v___y_900_;
v___y_859_ = v___y_901_;
v___y_860_ = v___y_902_;
v___y_861_ = v___y_904_;
v___y_862_ = v___y_903_;
v___y_863_ = v___x_909_;
goto v___jp_857_;
}
else
{
v___y_858_ = v___y_900_;
v___y_859_ = v___y_901_;
v___y_860_ = v___y_902_;
v___y_861_ = v___y_904_;
v___y_862_ = v___y_903_;
v___y_863_ = v___x_906_;
goto v___jp_857_;
}
}
v___jp_910_:
{
uint64_t v___x_915_; uint64_t v___x_916_; uint8_t v___x_917_; 
v___x_915_ = lean_uint32_to_uint64(v_ex_896_);
v___x_916_ = 0ULL;
v___x_917_ = lean_uint64_dec_eq(v___x_915_, v___x_916_);
if (v___x_917_ == 0)
{
uint64_t v___x_918_; uint64_t v___x_919_; 
v___x_918_ = 1ULL;
v___x_919_ = lean_uint64_sub(v___x_915_, v___x_918_);
v___y_900_ = v___y_911_;
v___y_901_ = v___y_912_;
v___y_902_ = v___y_913_;
v___y_903_ = v___y_914_;
v___y_904_ = v___x_919_;
goto v___jp_899_;
}
else
{
v___y_900_ = v___y_911_;
v___y_901_ = v___y_912_;
v___y_902_ = v___y_913_;
v___y_903_ = v___y_914_;
v___y_904_ = v___x_916_;
goto v___jp_899_;
}
}
v___jp_920_:
{
uint32_t v___x_925_; uint8_t v___x_926_; 
v___x_925_ = 0;
v___x_926_ = lean_uint32_dec_eq(v_ey_898_, v___x_925_);
if (v___x_926_ == 0)
{
uint64_t v___x_927_; uint64_t v___x_928_; uint64_t v___x_929_; 
v___x_927_ = lean_uint32_to_uint64(v___y_921_);
v___x_928_ = 8388608ULL;
v___x_929_ = lean_uint64_lor(v___x_927_, v___x_928_);
v___y_911_ = v___y_922_;
v___y_912_ = v___y_924_;
v___y_913_ = v___y_923_;
v___y_914_ = v___x_929_;
goto v___jp_910_;
}
else
{
uint64_t v___x_930_; 
v___x_930_ = lean_uint32_to_uint64(v___y_921_);
v___y_911_ = v___y_922_;
v___y_912_ = v___y_924_;
v___y_913_ = v___y_923_;
v___y_914_ = v___x_930_;
goto v___jp_910_;
}
}
v___jp_931_:
{
uint32_t v___x_933_; uint32_t v_xFraction_934_; uint32_t v_yFraction_935_; uint32_t v___x_936_; uint8_t v___x_937_; 
v___x_933_ = 8388607;
v_xFraction_934_ = lean_uint32_land(v___y_550_, v___x_933_);
v_yFraction_935_ = lean_uint32_land(v___y_551_, v___x_933_);
v___x_936_ = 0;
v___x_937_ = lean_uint32_dec_eq(v_ex_896_, v___x_936_);
if (v___x_937_ == 0)
{
uint64_t v___x_938_; uint64_t v___x_939_; uint64_t v___x_940_; 
v___x_938_ = lean_uint32_to_uint64(v_xFraction_934_);
v___x_939_ = 8388608ULL;
v___x_940_ = lean_uint64_lor(v___x_938_, v___x_939_);
v___y_921_ = v_yFraction_935_;
v___y_922_ = v___x_933_;
v___y_923_ = v___y_932_;
v___y_924_ = v___x_940_;
goto v___jp_920_;
}
else
{
uint64_t v___x_941_; 
v___x_941_ = lean_uint32_to_uint64(v_xFraction_934_);
v___y_921_ = v_yFraction_935_;
v___y_922_ = v___x_933_;
v___y_923_ = v___y_932_;
v___y_924_ = v___x_941_;
goto v___jp_920_;
}
}
v___jp_945_:
{
if (v___y_947_ == 0)
{
if (v___y_948_ == 0)
{
v___y_932_ = v___y_946_;
goto v___jp_931_;
}
else
{
v___y_932_ = v___x_944_;
goto v___jp_931_;
}
}
else
{
if (v___y_948_ == 0)
{
v___y_932_ = v___x_944_;
goto v___jp_931_;
}
else
{
v___y_932_ = v___y_946_;
goto v___jp_931_;
}
}
}
v___jp_949_:
{
uint32_t v___x_952_; uint32_t v___x_953_; uint32_t v___x_954_; uint8_t v___x_955_; 
v___x_952_ = 2147483648;
v___x_953_ = lean_uint32_land(v___y_551_, v___x_952_);
v___x_954_ = 0;
v___x_955_ = lean_uint32_dec_eq(v___x_953_, v___x_954_);
if (v___x_955_ == 0)
{
v___y_946_ = v___y_950_;
v___y_947_ = v___y_951_;
v___y_948_ = v___x_944_;
goto v___jp_945_;
}
else
{
v___y_946_ = v___y_950_;
v___y_947_ = v___y_951_;
v___y_948_ = v___y_950_;
goto v___jp_945_;
}
}
v___jp_956_:
{
if (v___y_957_ == 0)
{
uint32_t v___x_958_; uint32_t v___x_959_; uint32_t v___x_960_; uint8_t v___x_961_; 
v___x_958_ = 2147483648;
v___x_959_ = lean_uint32_land(v___y_550_, v___x_958_);
v___x_960_ = 0;
v___x_961_ = lean_uint32_dec_eq(v___x_959_, v___x_960_);
if (v___x_961_ == 0)
{
v___y_950_ = v___y_957_;
v___y_951_ = v___x_944_;
goto v___jp_949_;
}
else
{
v___y_950_ = v___y_957_;
v___y_951_ = v___y_957_;
goto v___jp_949_;
}
}
else
{
lean_object* v___x_962_; lean_object* v___x_963_; lean_object* v___x_964_; uint32_t v___x_965_; 
v___x_962_ = lean_uint32_to_nat(v___y_550_);
v___x_963_ = lean_uint32_to_nat(v___y_551_);
v___x_964_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_962_, v___x_963_);
v___x_965_ = lean_uint32_of_nat(v___x_964_);
lean_dec(v___x_964_);
return v___x_965_;
}
}
}
else
{
uint32_t v___x_978_; uint32_t v___x_979_; uint32_t v___x_980_; uint32_t v___x_981_; float v___x_982_; lean_object* v___x_983_; uint32_t v___x_984_; uint32_t v___x_985_; lean_object* v___x_986_; lean_object* v___x_987_; float v___x_988_; float v___x_989_; uint32_t v___x_990_; uint32_t v___x_991_; float v___x_992_; uint32_t v___x_993_; lean_object* v___x_994_; lean_object* v___x_995_; float v___x_996_; float v___x_997_; float v___x_998_; uint32_t v___x_999_; 
v___x_978_ = 8388607;
v___x_979_ = lean_uint32_land(v___y_550_, v___x_978_);
v___x_980_ = 8388608;
v___x_981_ = lean_uint32_lor(v___x_979_, v___x_980_);
v___x_982_ = lean_uint32_to_float32(v___x_981_);
v___x_983_ = lp_competition_R2W01b_scaleTable;
v___x_984_ = 23;
v___x_985_ = lean_uint32_shift_right(v___y_550_, v___x_984_);
v___x_986_ = lean_uint32_to_nat(v___x_985_);
v___x_987_ = lean_array_fget_borrowed(v___x_983_, v___x_986_);
lean_dec(v___x_986_);
v___x_988_ = lean_unbox_float32(v___x_987_);
v___x_989_ = lean_float32_mul(v___x_982_, v___x_988_);
v___x_990_ = lean_uint32_land(v___y_551_, v___x_978_);
v___x_991_ = lean_uint32_lor(v___x_990_, v___x_980_);
v___x_992_ = lean_uint32_to_float32(v___x_991_);
v___x_993_ = lean_uint32_shift_right(v___y_551_, v___x_984_);
v___x_994_ = lean_uint32_to_nat(v___x_993_);
v___x_995_ = lean_array_fget_borrowed(v___x_983_, v___x_994_);
lean_dec(v___x_994_);
v___x_996_ = lean_unbox_float32(v___x_995_);
v___x_997_ = lean_float32_mul(v___x_992_, v___x_996_);
v___x_998_ = lean_float32_mul(v___x_989_, v___x_997_);
v___x_999_ = lean_float32_to_bits(v___x_998_);
return v___x_999_;
}
v___jp_552_:
{
uint32_t v___x_554_; uint32_t v___x_555_; 
v___x_554_ = 8388608;
v___x_555_ = lean_uint32_lor(v___y_553_, v___x_554_);
return v___x_555_;
}
v___jp_556_:
{
uint32_t v___x_558_; uint32_t v___x_559_; 
v___x_558_ = 8388608;
v___x_559_ = lean_uint32_lor(v___y_557_, v___x_558_);
return v___x_559_;
}
v___jp_560_:
{
uint32_t v___x_564_; uint32_t v___x_565_; 
v___x_564_ = lean_uint32_land(v___y_562_, v___y_561_);
v___x_565_ = lean_uint32_lor(v___y_563_, v___x_564_);
return v___x_565_;
}
v___jp_566_:
{
uint8_t v___x_571_; 
v___x_571_ = lean_uint64_dec_eq(v___y_570_, v___y_568_);
if (v___x_571_ == 0)
{
uint64_t v___x_572_; uint8_t v___x_573_; 
v___x_572_ = 8388608ULL;
v___x_573_ = lean_uint64_dec_eq(v___y_570_, v___x_572_);
if (v___x_573_ == 0)
{
uint32_t v___x_574_; 
v___x_574_ = lean_uint64_to_uint32(v___y_570_);
if (v___y_569_ == 0)
{
uint32_t v___x_575_; 
v___x_575_ = 0;
v___y_561_ = v___y_567_;
v___y_562_ = v___x_574_;
v___y_563_ = v___x_575_;
goto v___jp_560_;
}
else
{
uint32_t v___x_576_; 
v___x_576_ = 2147483648;
v___y_561_ = v___y_567_;
v___y_562_ = v___x_574_;
v___y_563_ = v___x_576_;
goto v___jp_560_;
}
}
else
{
if (v___y_569_ == 0)
{
uint32_t v___x_577_; 
v___x_577_ = 0;
v___y_557_ = v___x_577_;
goto v___jp_556_;
}
else
{
uint32_t v___x_578_; 
v___x_578_ = 2147483648;
v___y_557_ = v___x_578_;
goto v___jp_556_;
}
}
}
else
{
if (v___y_569_ == 0)
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
v___jp_581_:
{
uint32_t v___x_585_; uint32_t v___x_586_; 
v___x_585_ = lean_uint32_land(v___y_582_, v___y_583_);
v___x_586_ = lean_uint32_lor(v___y_584_, v___x_585_);
return v___x_586_;
}
v___jp_587_:
{
uint8_t v___x_592_; 
v___x_592_ = lean_uint64_dec_eq(v___y_591_, v___y_588_);
if (v___x_592_ == 0)
{
uint64_t v___x_593_; uint8_t v___x_594_; 
v___x_593_ = 8388608ULL;
v___x_594_ = lean_uint64_dec_eq(v___y_591_, v___x_593_);
if (v___x_594_ == 0)
{
uint32_t v___x_595_; 
v___x_595_ = lean_uint64_to_uint32(v___y_591_);
if (v___y_590_ == 0)
{
uint32_t v___x_596_; 
v___x_596_ = 0;
v___y_582_ = v___x_595_;
v___y_583_ = v___y_589_;
v___y_584_ = v___x_596_;
goto v___jp_581_;
}
else
{
uint32_t v___x_597_; 
v___x_597_ = 2147483648;
v___y_582_ = v___x_595_;
v___y_583_ = v___y_589_;
v___y_584_ = v___x_597_;
goto v___jp_581_;
}
}
else
{
if (v___y_590_ == 0)
{
uint32_t v___x_598_; 
v___x_598_ = 0;
v___y_553_ = v___x_598_;
goto v___jp_552_;
}
else
{
uint32_t v___x_599_; 
v___x_599_ = 2147483648;
v___y_553_ = v___x_599_;
goto v___jp_552_;
}
}
}
else
{
if (v___y_590_ == 0)
{
uint32_t v___x_600_; 
v___x_600_ = 0;
return v___x_600_;
}
else
{
uint32_t v___x_601_; 
v___x_601_ = 2147483648;
return v___x_601_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_1000_, lean_object* v___y_1001_){
_start:
{
uint32_t v___y_4317__boxed_1002_; uint32_t v___y_4318__boxed_1003_; uint32_t v_res_1004_; lean_object* v_r_1005_; 
v___y_4317__boxed_1002_ = lean_unbox_uint32(v___y_1000_);
lean_dec(v___y_1000_);
v___y_4318__boxed_1003_ = lean_unbox_uint32(v___y_1001_);
lean_dec(v___y_1001_);
v_res_1004_ = lp_competition_main___lam__3(v___y_4317__boxed_1002_, v___y_4318__boxed_1003_);
v_r_1005_ = lean_box_uint32(v_res_1004_);
return v_r_1005_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1013_; lean_object* v___x_1014_; 
v___x_1013_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1014_ = lean_io_getenv(v___x_1013_);
if (lean_obj_tag(v___x_1014_) == 0)
{
lean_object* v___f_1015_; lean_object* v___f_1016_; lean_object* v___x_1017_; lean_object* v___x_1018_; lean_object* v___x_1019_; 
v___f_1015_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1016_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1017_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1018_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1019_ = lp_competition_Bench_runFull(v___f_1015_, v___f_1016_, v___x_1017_, v___x_1018_);
return v___x_1019_;
}
else
{
lean_object* v___f_1020_; lean_object* v___f_1021_; lean_object* v___x_1022_; lean_object* v___x_1023_; lean_object* v___x_1024_; 
lean_dec_ref_known(v___x_1014_, 1);
v___f_1020_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1021_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1022_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1023_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1024_ = lp_competition_Bench_Suite_run(v___f_1020_, v___f_1021_, v___x_1022_, v___x_1023_);
return v___x_1024_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1025_){
_start:
{
lean_object* v_res_1026_; 
v_res_1026_ = _lean_main();
return v_res_1026_;
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
