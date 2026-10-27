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
uint64_t lean_uint64_lor(uint64_t, uint64_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
lean_object* lp_competition_Submission_R22StreamingCost_guarded(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Bench_runFull(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__0___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_closure_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__1___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_closure_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_R22StreamingCost_guarded, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_closure_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sum___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
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
uint32_t v___y_2198__boxed_126_; uint32_t v___y_2199__boxed_127_; uint32_t v_res_128_; lean_object* v_r_129_; 
v___y_2198__boxed_126_ = lean_unbox_uint32(v___y_124_);
lean_dec(v___y_124_);
v___y_2199__boxed_127_ = lean_unbox_uint32(v___y_125_);
lean_dec(v___y_125_);
v_res_128_ = lp_competition_main___lam__0(v___y_2198__boxed_126_, v___y_2199__boxed_127_);
v_r_129_ = lean_box_uint32(v_res_128_);
return v_r_129_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_130_, uint32_t v___y_131_){
_start:
{
uint32_t v___y_133_; uint32_t v___y_137_; uint32_t v___y_141_; uint32_t v___y_142_; uint32_t v___y_143_; uint8_t v___y_147_; uint32_t v___y_148_; uint64_t v___y_149_; uint64_t v___y_150_; uint32_t v___y_162_; uint32_t v___y_163_; uint32_t v___y_164_; uint8_t v___y_168_; uint32_t v___y_169_; uint64_t v___y_170_; uint64_t v___y_171_; uint8_t v___y_183_; uint8_t v___y_199_; uint8_t v___y_213_; uint8_t v___y_230_; float v___y_237_; float v___y_238_; float v___y_252_; uint8_t v___y_253_; float v___y_268_; uint32_t v___x_277_; uint32_t v___x_278_; uint8_t v___y_280_; uint32_t v___x_292_; uint32_t v___y_294_; uint32_t v___y_295_; uint32_t v___y_296_; uint32_t v___y_297_; uint32_t v___y_304_; uint8_t v___y_305_; uint32_t v___y_306_; uint32_t v___y_307_; uint8_t v___y_311_; uint64_t v___y_312_; uint32_t v___y_313_; uint64_t v___y_314_; uint64_t v___y_315_; uint8_t v___y_325_; uint8_t v___y_326_; uint32_t v___y_327_; uint64_t v___y_328_; uint64_t v___y_329_; uint64_t v___y_330_; uint8_t v___y_337_; uint64_t v___y_338_; uint64_t v___y_339_; uint32_t v___y_340_; uint64_t v___y_341_; uint8_t v___y_347_; uint64_t v___y_348_; uint32_t v___y_349_; uint64_t v___y_350_; uint64_t v___y_351_; uint64_t v___y_352_; uint64_t v___y_407_; uint8_t v___y_408_; uint32_t v___y_409_; uint64_t v___y_410_; uint64_t v___y_411_; uint64_t v___y_412_; uint64_t v___y_413_; uint64_t v___y_419_; uint8_t v___y_420_; uint64_t v___y_421_; uint64_t v___y_422_; uint64_t v___y_423_; uint32_t v___y_424_; uint64_t v___y_425_; uint64_t v___y_426_; uint64_t v___y_427_; uint8_t v___y_432_; uint32_t v___y_433_; uint64_t v___y_434_; uint64_t v___y_435_; uint64_t v___y_436_; uint64_t v___y_437_; uint64_t v___y_438_; uint8_t v___y_443_; uint64_t v___y_444_; uint64_t v___y_445_; uint64_t v___y_446_; uint64_t v___y_447_; uint32_t v___y_448_; uint64_t v___y_449_; uint64_t v___y_450_; uint64_t v___y_451_; uint8_t v___y_456_; uint32_t v___y_457_; uint64_t v___y_458_; uint64_t v___y_459_; uint64_t v___y_460_; uint64_t v___y_461_; uint64_t v___y_462_; uint64_t v___y_467_; uint8_t v___y_468_; uint64_t v___y_469_; uint64_t v___y_470_; uint32_t v___y_471_; uint64_t v___y_472_; uint64_t v___y_473_; uint64_t v___y_474_; uint64_t v___y_475_; uint64_t v___y_480_; uint8_t v___y_481_; uint32_t v___y_482_; uint64_t v___y_483_; uint64_t v___y_484_; uint64_t v___y_485_; uint64_t v___y_486_; uint8_t v___y_491_; uint64_t v___y_492_; uint64_t v___y_493_; uint64_t v___y_494_; uint32_t v___y_495_; uint64_t v___y_496_; uint64_t v___y_497_; uint64_t v___y_498_; uint64_t v___y_499_; uint8_t v___y_504_; uint64_t v___y_505_; uint32_t v___y_506_; uint64_t v___y_507_; uint64_t v___y_508_; uint64_t v___y_509_; uint64_t v___y_510_; uint8_t v___y_515_; uint64_t v___y_516_; uint64_t v___y_517_; uint64_t v___y_518_; uint32_t v___y_519_; uint64_t v___y_520_; uint64_t v___y_521_; uint8_t v___y_525_; uint64_t v___y_526_; uint32_t v___y_527_; uint64_t v___y_528_; uint8_t v___y_537_; uint64_t v___y_538_; uint32_t v___y_539_; uint64_t v___y_540_; uint64_t v___y_541_; uint64_t v___y_542_; uint32_t v_ex_575_; uint32_t v___x_576_; uint32_t v_ey_577_; uint8_t v___y_579_; uint32_t v___y_580_; uint64_t v___y_581_; uint64_t v___y_582_; uint64_t v___y_583_; uint8_t v___y_590_; uint32_t v___y_591_; uint64_t v___y_592_; uint64_t v___y_593_; uint32_t v___y_600_; uint8_t v___y_601_; uint32_t v___y_602_; uint64_t v___y_603_; uint8_t v___y_611_; uint32_t v___x_621_; uint32_t v___x_622_; uint8_t v___x_623_; uint8_t v___y_625_; uint8_t v___y_626_; uint8_t v___y_628_; uint8_t v___y_629_; uint8_t v___y_630_; uint8_t v___y_632_; uint8_t v___y_633_; uint8_t v___y_639_; 
v___x_277_ = 23;
v___x_278_ = lean_uint32_shift_right(v___y_130_, v___x_277_);
v___x_292_ = 255;
v_ex_575_ = lean_uint32_land(v___x_278_, v___x_292_);
v___x_576_ = lean_uint32_shift_right(v___y_131_, v___x_277_);
v_ey_577_ = lean_uint32_land(v___x_576_, v___x_292_);
v___x_621_ = lean_uint32_add(v_ex_575_, v_ey_577_);
v___x_622_ = 128;
v___x_623_ = lean_uint32_dec_lt(v___x_621_, v___x_622_);
if (v___x_623_ == 0)
{
uint32_t v___x_648_; uint32_t v_a_649_; uint32_t v___x_650_; uint32_t v___x_651_; uint32_t v___x_652_; uint8_t v___x_653_; 
v___x_648_ = 2147483647;
v_a_649_ = lean_uint32_land(v___y_130_, v___x_648_);
v___x_650_ = 201326591;
v___x_651_ = 1;
v___x_652_ = lean_uint32_sub(v_a_649_, v___x_651_);
v___x_653_ = lean_uint32_dec_le(v___x_650_, v___x_652_);
if (v___x_653_ == 0)
{
v___y_280_ = v___x_653_;
goto v___jp_279_;
}
else
{
uint32_t v___x_654_; uint8_t v___x_655_; 
v___x_654_ = 2139095040;
v___x_655_ = lean_uint32_dec_lt(v_a_649_, v___x_654_);
v___y_280_ = v___x_655_;
goto v___jp_279_;
}
}
else
{
uint32_t v___x_656_; uint32_t v___x_657_; uint32_t v___x_658_; uint8_t v___x_659_; 
v___x_656_ = 4278190080;
v___x_657_ = 1;
v___x_658_ = lean_uint32_shift_left(v___y_130_, v___x_657_);
v___x_659_ = lean_uint32_dec_le(v___x_656_, v___x_658_);
if (v___x_659_ == 0)
{
uint32_t v___x_660_; uint8_t v___x_661_; 
v___x_660_ = lean_uint32_shift_left(v___y_131_, v___x_657_);
v___x_661_ = lean_uint32_dec_le(v___x_656_, v___x_660_);
v___y_639_ = v___x_661_;
goto v___jp_638_;
}
else
{
v___y_639_ = v___x_659_;
goto v___jp_638_;
}
}
v___jp_132_:
{
uint32_t v___x_134_; uint32_t v___x_135_; 
v___x_134_ = 8388608;
v___x_135_ = lean_uint32_lor(v___y_133_, v___x_134_);
return v___x_135_;
}
v___jp_136_:
{
uint32_t v___x_138_; uint32_t v___x_139_; 
v___x_138_ = 8388608;
v___x_139_ = lean_uint32_lor(v___y_137_, v___x_138_);
return v___x_139_;
}
v___jp_140_:
{
uint32_t v___x_144_; uint32_t v___x_145_; 
v___x_144_ = lean_uint32_land(v___y_141_, v___y_142_);
v___x_145_ = lean_uint32_lor(v___y_143_, v___x_144_);
return v___x_145_;
}
v___jp_146_:
{
uint8_t v___x_151_; 
v___x_151_ = lean_uint64_dec_eq(v___y_150_, v___y_149_);
if (v___x_151_ == 0)
{
uint64_t v___x_152_; uint8_t v___x_153_; 
v___x_152_ = 8388608ULL;
v___x_153_ = lean_uint64_dec_eq(v___y_150_, v___x_152_);
if (v___x_153_ == 0)
{
uint32_t v___x_154_; 
v___x_154_ = lean_uint64_to_uint32(v___y_150_);
if (v___y_147_ == 0)
{
uint32_t v___x_155_; 
v___x_155_ = 0;
v___y_141_ = v___x_154_;
v___y_142_ = v___y_148_;
v___y_143_ = v___x_155_;
goto v___jp_140_;
}
else
{
uint32_t v___x_156_; 
v___x_156_ = 2147483648;
v___y_141_ = v___x_154_;
v___y_142_ = v___y_148_;
v___y_143_ = v___x_156_;
goto v___jp_140_;
}
}
else
{
if (v___y_147_ == 0)
{
uint32_t v___x_157_; 
v___x_157_ = 0;
v___y_137_ = v___x_157_;
goto v___jp_136_;
}
else
{
uint32_t v___x_158_; 
v___x_158_ = 2147483648;
v___y_137_ = v___x_158_;
goto v___jp_136_;
}
}
}
else
{
if (v___y_147_ == 0)
{
uint32_t v___x_159_; 
v___x_159_ = 0;
return v___x_159_;
}
else
{
uint32_t v___x_160_; 
v___x_160_ = 2147483648;
return v___x_160_;
}
}
}
v___jp_161_:
{
uint32_t v___x_165_; uint32_t v___x_166_; 
v___x_165_ = lean_uint32_land(v___y_162_, v___y_163_);
v___x_166_ = lean_uint32_lor(v___y_164_, v___x_165_);
return v___x_166_;
}
v___jp_167_:
{
uint8_t v___x_172_; 
v___x_172_ = lean_uint64_dec_eq(v___y_171_, v___y_170_);
if (v___x_172_ == 0)
{
uint64_t v___x_173_; uint8_t v___x_174_; 
v___x_173_ = 8388608ULL;
v___x_174_ = lean_uint64_dec_eq(v___y_171_, v___x_173_);
if (v___x_174_ == 0)
{
uint32_t v___x_175_; 
v___x_175_ = lean_uint64_to_uint32(v___y_171_);
if (v___y_168_ == 0)
{
uint32_t v___x_176_; 
v___x_176_ = 0;
v___y_162_ = v___x_175_;
v___y_163_ = v___y_169_;
v___y_164_ = v___x_176_;
goto v___jp_161_;
}
else
{
uint32_t v___x_177_; 
v___x_177_ = 2147483648;
v___y_162_ = v___x_175_;
v___y_163_ = v___y_169_;
v___y_164_ = v___x_177_;
goto v___jp_161_;
}
}
else
{
if (v___y_168_ == 0)
{
uint32_t v___x_178_; 
v___x_178_ = 0;
v___y_133_ = v___x_178_;
goto v___jp_132_;
}
else
{
uint32_t v___x_179_; 
v___x_179_ = 2147483648;
v___y_133_ = v___x_179_;
goto v___jp_132_;
}
}
}
else
{
if (v___y_168_ == 0)
{
uint32_t v___x_180_; 
v___x_180_ = 0;
return v___x_180_;
}
else
{
uint32_t v___x_181_; 
v___x_181_ = 2147483648;
return v___x_181_;
}
}
}
v___jp_182_:
{
if (v___y_183_ == 0)
{
uint32_t v___x_184_; 
v___x_184_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_184_;
}
else
{
uint32_t v___x_185_; uint32_t v___x_186_; 
v___x_185_ = 4194304;
v___x_186_ = lean_uint32_lor(v___y_131_, v___x_185_);
return v___x_186_;
}
}
v___jp_187_:
{
uint32_t v___x_188_; uint32_t v___x_189_; uint32_t v___x_190_; uint32_t v___x_191_; uint8_t v___x_192_; 
v___x_188_ = 23;
v___x_189_ = lean_uint32_shift_right(v___y_131_, v___x_188_);
v___x_190_ = 255;
v___x_191_ = lean_uint32_land(v___x_189_, v___x_190_);
v___x_192_ = lean_uint32_dec_eq(v___x_191_, v___x_190_);
if (v___x_192_ == 0)
{
v___y_183_ = v___x_192_;
goto v___jp_182_;
}
else
{
uint32_t v___x_193_; uint32_t v___x_194_; uint32_t v___x_195_; uint8_t v___x_196_; 
v___x_193_ = 8388607;
v___x_194_ = lean_uint32_land(v___y_131_, v___x_193_);
v___x_195_ = 0;
v___x_196_ = lean_uint32_dec_eq(v___x_194_, v___x_195_);
if (v___x_196_ == 0)
{
v___y_183_ = v___x_192_;
goto v___jp_182_;
}
else
{
uint32_t v___x_197_; 
v___x_197_ = lp_competition_Submission_FastMul_mul(v___y_130_, v___y_131_);
return v___x_197_;
}
}
}
v___jp_198_:
{
if (v___y_199_ == 0)
{
goto v___jp_187_;
}
else
{
uint32_t v___x_200_; uint32_t v___x_201_; 
v___x_200_ = 4194304;
v___x_201_ = lean_uint32_lor(v___y_130_, v___x_200_);
return v___x_201_;
}
}
v___jp_202_:
{
uint32_t v___x_203_; uint32_t v___x_204_; uint32_t v___x_205_; uint32_t v___x_206_; uint8_t v___x_207_; 
v___x_203_ = 23;
v___x_204_ = lean_uint32_shift_right(v___y_130_, v___x_203_);
v___x_205_ = 255;
v___x_206_ = lean_uint32_land(v___x_204_, v___x_205_);
v___x_207_ = lean_uint32_dec_eq(v___x_206_, v___x_205_);
if (v___x_207_ == 0)
{
v___y_199_ = v___x_207_;
goto v___jp_198_;
}
else
{
uint32_t v___x_208_; uint32_t v___x_209_; uint32_t v___x_210_; uint8_t v___x_211_; 
v___x_208_ = 8388607;
v___x_209_ = lean_uint32_land(v___y_130_, v___x_208_);
v___x_210_ = 0;
v___x_211_ = lean_uint32_dec_eq(v___x_209_, v___x_210_);
if (v___x_211_ == 0)
{
v___y_199_ = v___x_207_;
goto v___jp_198_;
}
else
{
goto v___jp_187_;
}
}
}
v___jp_212_:
{
if (v___y_213_ == 0)
{
goto v___jp_202_;
}
else
{
uint32_t v___x_214_; uint32_t v___x_215_; uint32_t v___x_216_; uint8_t v___x_217_; 
v___x_214_ = 4194304;
v___x_215_ = lean_uint32_land(v___y_131_, v___x_214_);
v___x_216_ = 0;
v___x_217_ = lean_uint32_dec_eq(v___x_215_, v___x_216_);
if (v___x_217_ == 0)
{
goto v___jp_202_;
}
else
{
uint32_t v___x_218_; 
v___x_218_ = lean_uint32_lor(v___y_131_, v___x_214_);
return v___x_218_;
}
}
}
v___jp_219_:
{
uint32_t v___x_220_; uint32_t v___x_221_; uint32_t v___x_222_; uint32_t v___x_223_; uint8_t v___x_224_; 
v___x_220_ = 23;
v___x_221_ = lean_uint32_shift_right(v___y_131_, v___x_220_);
v___x_222_ = 255;
v___x_223_ = lean_uint32_land(v___x_221_, v___x_222_);
v___x_224_ = lean_uint32_dec_eq(v___x_223_, v___x_222_);
if (v___x_224_ == 0)
{
v___y_213_ = v___x_224_;
goto v___jp_212_;
}
else
{
uint32_t v___x_225_; uint32_t v___x_226_; uint32_t v___x_227_; uint8_t v___x_228_; 
v___x_225_ = 8388607;
v___x_226_ = lean_uint32_land(v___y_131_, v___x_225_);
v___x_227_ = 0;
v___x_228_ = lean_uint32_dec_eq(v___x_226_, v___x_227_);
if (v___x_228_ == 0)
{
v___y_213_ = v___x_224_;
goto v___jp_212_;
}
else
{
goto v___jp_202_;
}
}
}
v___jp_229_:
{
if (v___y_230_ == 0)
{
goto v___jp_219_;
}
else
{
uint32_t v___x_231_; uint32_t v___x_232_; uint32_t v___x_233_; uint8_t v___x_234_; 
v___x_231_ = 4194304;
v___x_232_ = lean_uint32_land(v___y_130_, v___x_231_);
v___x_233_ = 0;
v___x_234_ = lean_uint32_dec_eq(v___x_232_, v___x_233_);
if (v___x_234_ == 0)
{
goto v___jp_219_;
}
else
{
uint32_t v___x_235_; 
v___x_235_ = lean_uint32_lor(v___y_130_, v___x_231_);
return v___x_235_;
}
}
}
v___jp_236_:
{
float v_result_239_; uint8_t v___x_240_; 
v_result_239_ = lean_float32_mul(v___y_237_, v___y_238_);
v___x_240_ = lean_float32_beq(v_result_239_, v_result_239_);
if (v___x_240_ == 0)
{
uint32_t v___x_241_; uint32_t v___x_242_; uint32_t v___x_243_; uint32_t v___x_244_; uint8_t v___x_245_; 
v___x_241_ = 23;
v___x_242_ = lean_uint32_shift_right(v___y_130_, v___x_241_);
v___x_243_ = 255;
v___x_244_ = lean_uint32_land(v___x_242_, v___x_243_);
v___x_245_ = lean_uint32_dec_eq(v___x_244_, v___x_243_);
if (v___x_245_ == 0)
{
v___y_230_ = v___x_245_;
goto v___jp_229_;
}
else
{
uint32_t v___x_246_; uint32_t v___x_247_; uint32_t v___x_248_; uint8_t v___x_249_; 
v___x_246_ = 8388607;
v___x_247_ = lean_uint32_land(v___y_130_, v___x_246_);
v___x_248_ = 0;
v___x_249_ = lean_uint32_dec_eq(v___x_247_, v___x_248_);
if (v___x_249_ == 0)
{
v___y_230_ = v___x_245_;
goto v___jp_229_;
}
else
{
goto v___jp_219_;
}
}
}
else
{
uint32_t v___x_250_; 
v___x_250_ = lean_float32_to_bits(v_result_239_);
return v___x_250_;
}
}
v___jp_251_:
{
if (v___y_253_ == 0)
{
float v___x_254_; 
v___x_254_ = lean_float32_of_bits(v___y_131_);
v___y_237_ = v___y_252_;
v___y_238_ = v___x_254_;
goto v___jp_236_;
}
else
{
uint32_t v___x_255_; uint32_t v___x_256_; uint32_t v___x_257_; uint32_t v___x_258_; float v___x_259_; lean_object* v___x_260_; uint32_t v___x_261_; uint32_t v___x_262_; lean_object* v___x_263_; lean_object* v___x_264_; float v___x_265_; float v___x_266_; 
v___x_255_ = 8388607;
v___x_256_ = lean_uint32_land(v___y_131_, v___x_255_);
v___x_257_ = 8388608;
v___x_258_ = lean_uint32_lor(v___x_256_, v___x_257_);
v___x_259_ = lean_uint32_to_float32(v___x_258_);
v___x_260_ = lp_competition_R2W01b_scaleTable;
v___x_261_ = 23;
v___x_262_ = lean_uint32_shift_right(v___y_131_, v___x_261_);
v___x_263_ = lean_uint32_to_nat(v___x_262_);
v___x_264_ = lean_array_fget_borrowed(v___x_260_, v___x_263_);
lean_dec(v___x_263_);
v___x_265_ = lean_unbox_float32(v___x_264_);
v___x_266_ = lean_float32_mul(v___x_259_, v___x_265_);
v___y_237_ = v___y_252_;
v___y_238_ = v___x_266_;
goto v___jp_236_;
}
}
v___jp_267_:
{
uint32_t v___x_269_; uint32_t v_a_270_; uint32_t v___x_271_; uint32_t v___x_272_; uint32_t v___x_273_; uint8_t v___x_274_; 
v___x_269_ = 2147483647;
v_a_270_ = lean_uint32_land(v___y_131_, v___x_269_);
v___x_271_ = 201326591;
v___x_272_ = 1;
v___x_273_ = lean_uint32_sub(v_a_270_, v___x_272_);
v___x_274_ = lean_uint32_dec_le(v___x_271_, v___x_273_);
if (v___x_274_ == 0)
{
v___y_252_ = v___y_268_;
v___y_253_ = v___x_274_;
goto v___jp_251_;
}
else
{
uint32_t v___x_275_; uint8_t v___x_276_; 
v___x_275_ = 2139095040;
v___x_276_ = lean_uint32_dec_lt(v_a_270_, v___x_275_);
v___y_252_ = v___y_268_;
v___y_253_ = v___x_276_;
goto v___jp_251_;
}
}
v___jp_279_:
{
if (v___y_280_ == 0)
{
float v___x_281_; 
v___x_281_ = lean_float32_of_bits(v___y_130_);
v___y_268_ = v___x_281_;
goto v___jp_267_;
}
else
{
uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint32_t v___x_285_; float v___x_286_; lean_object* v___x_287_; lean_object* v___x_288_; lean_object* v___x_289_; float v___x_290_; float v___x_291_; 
v___x_282_ = 8388607;
v___x_283_ = lean_uint32_land(v___y_130_, v___x_282_);
v___x_284_ = 8388608;
v___x_285_ = lean_uint32_lor(v___x_283_, v___x_284_);
v___x_286_ = lean_uint32_to_float32(v___x_285_);
v___x_287_ = lp_competition_R2W01b_scaleTable;
v___x_288_ = lean_uint32_to_nat(v___x_278_);
v___x_289_ = lean_array_fget_borrowed(v___x_287_, v___x_288_);
lean_dec(v___x_288_);
v___x_290_ = lean_unbox_float32(v___x_289_);
v___x_291_ = lean_float32_mul(v___x_286_, v___x_290_);
v___y_268_ = v___x_291_;
goto v___jp_267_;
}
}
v___jp_293_:
{
uint32_t v___x_298_; uint32_t v___x_299_; uint32_t v___x_300_; uint32_t v___x_301_; uint32_t v___x_302_; 
v___x_298_ = lean_uint32_land(v___y_295_, v___x_292_);
v___x_299_ = lean_uint32_shift_left(v___x_298_, v___x_277_);
v___x_300_ = lean_uint32_lor(v___y_297_, v___x_299_);
v___x_301_ = lean_uint32_land(v___y_294_, v___y_296_);
v___x_302_ = lean_uint32_lor(v___x_300_, v___x_301_);
return v___x_302_;
}
v___jp_303_:
{
if (v___y_305_ == 0)
{
uint32_t v___x_308_; 
v___x_308_ = 0;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_304_;
v___y_296_ = v___y_306_;
v___y_297_ = v___x_308_;
goto v___jp_293_;
}
else
{
uint32_t v___x_309_; 
v___x_309_ = 2147483648;
v___y_294_ = v___y_307_;
v___y_295_ = v___y_304_;
v___y_296_ = v___y_306_;
v___y_297_ = v___x_309_;
goto v___jp_293_;
}
}
v___jp_310_:
{
uint64_t v___x_316_; uint64_t v_encodedExponent_317_; uint32_t v___x_318_; uint64_t v___x_319_; uint8_t v___x_320_; 
v___x_316_ = 171ULL;
v_encodedExponent_317_ = lean_uint64_sub(v___y_314_, v___x_316_);
v___x_318_ = lean_uint64_to_uint32(v_encodedExponent_317_);
v___x_319_ = 8388608ULL;
v___x_320_ = lean_uint64_dec_lt(v___y_315_, v___x_319_);
if (v___x_320_ == 0)
{
uint64_t v___x_321_; uint32_t v___x_322_; 
v___x_321_ = lean_uint64_sub(v___y_315_, v___x_319_);
v___x_322_ = lean_uint64_to_uint32(v___x_321_);
v___y_304_ = v___x_318_;
v___y_305_ = v___y_311_;
v___y_306_ = v___y_313_;
v___y_307_ = v___x_322_;
goto v___jp_303_;
}
else
{
uint32_t v___x_323_; 
v___x_323_ = lean_uint64_to_uint32(v___y_312_);
v___y_304_ = v___x_318_;
v___y_305_ = v___y_311_;
v___y_306_ = v___y_313_;
v___y_307_ = v___x_323_;
goto v___jp_303_;
}
}
v___jp_324_:
{
uint64_t v___x_331_; uint8_t v___x_332_; 
v___x_331_ = 425ULL;
v___x_332_ = lean_uint64_dec_lt(v___x_331_, v___y_330_);
if (v___x_332_ == 0)
{
if (v___y_326_ == 0)
{
v___y_311_ = v___y_325_;
v___y_312_ = v___y_328_;
v___y_313_ = v___y_327_;
v___y_314_ = v___y_330_;
v___y_315_ = v___y_329_;
goto v___jp_310_;
}
else
{
uint64_t v___x_333_; 
v___x_333_ = 8388608ULL;
v___y_311_ = v___y_325_;
v___y_312_ = v___y_328_;
v___y_313_ = v___y_327_;
v___y_314_ = v___y_330_;
v___y_315_ = v___x_333_;
goto v___jp_310_;
}
}
else
{
if (v___y_325_ == 0)
{
uint32_t v___x_334_; 
v___x_334_ = 2139095040;
return v___x_334_;
}
else
{
uint32_t v___x_335_; 
v___x_335_ = 4286578688;
return v___x_335_;
}
}
}
v___jp_336_:
{
uint64_t v___x_342_; uint8_t v_carry_343_; 
v___x_342_ = 16777216ULL;
v_carry_343_ = lean_uint64_dec_eq(v___y_341_, v___x_342_);
if (v_carry_343_ == 0)
{
v___y_325_ = v___y_337_;
v___y_326_ = v_carry_343_;
v___y_327_ = v___y_340_;
v___y_328_ = v___y_339_;
v___y_329_ = v___y_341_;
v___y_330_ = v___y_338_;
goto v___jp_324_;
}
else
{
uint64_t v___x_344_; uint64_t v___x_345_; 
v___x_344_ = 1ULL;
v___x_345_ = lean_uint64_add(v___y_338_, v___x_344_);
v___y_325_ = v___y_337_;
v___y_326_ = v_carry_343_;
v___y_327_ = v___y_340_;
v___y_328_ = v___y_339_;
v___y_329_ = v___y_341_;
v___y_330_ = v___x_345_;
goto v___jp_324_;
}
}
v___jp_346_:
{
uint64_t v_position_353_; uint64_t v___x_354_; uint8_t v___x_355_; 
v_position_353_ = lean_uint64_add(v___y_352_, v___y_351_);
v___x_354_ = 172ULL;
v___x_355_ = lean_uint64_dec_lt(v_position_353_, v___x_354_);
if (v___x_355_ == 0)
{
uint64_t v___x_356_; uint8_t v___x_357_; 
v___x_356_ = 23ULL;
v___x_357_ = lean_uint64_dec_lt(v___y_352_, v___x_356_);
if (v___x_357_ == 0)
{
uint64_t v___x_358_; uint8_t v___x_359_; 
v___x_358_ = lean_uint64_sub(v___y_352_, v___x_356_);
v___x_359_ = lean_uint64_dec_eq(v___x_358_, v___y_350_);
if (v___x_359_ == 0)
{
uint64_t v___x_360_; uint8_t v___x_361_; 
v___x_360_ = 64ULL;
v___x_361_ = lean_uint64_dec_lt(v___x_358_, v___x_360_);
if (v___x_361_ == 0)
{
uint8_t v___x_362_; 
v___x_362_ = lean_uint64_dec_eq(v___x_358_, v___x_360_);
if (v___x_362_ == 0)
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_350_;
goto v___jp_336_;
}
else
{
uint64_t v___x_363_; uint8_t v___x_364_; 
v___x_363_ = 9223372036854775808ULL;
v___x_364_ = lean_uint64_dec_lt(v___x_363_, v___y_348_);
if (v___x_364_ == 0)
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_350_;
goto v___jp_336_;
}
else
{
uint64_t v___x_365_; 
v___x_365_ = 1ULL;
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_365_;
goto v___jp_336_;
}
}
}
else
{
uint64_t v_quotient_366_; uint64_t v___x_367_; uint64_t v___x_368_; uint64_t v___x_369_; uint64_t v_remainder_370_; uint64_t v___x_371_; uint64_t v_half_372_; uint8_t v___x_373_; 
v_quotient_366_ = lean_uint64_shift_right(v___y_348_, v___x_358_);
v___x_367_ = 1ULL;
v___x_368_ = lean_uint64_shift_left(v___x_367_, v___x_358_);
v___x_369_ = lean_uint64_sub(v___x_368_, v___x_367_);
v_remainder_370_ = lean_uint64_land(v___y_348_, v___x_369_);
v___x_371_ = lean_uint64_sub(v___x_358_, v___x_367_);
v_half_372_ = lean_uint64_shift_left(v___x_367_, v___x_371_);
v___x_373_ = lean_uint64_dec_lt(v_remainder_370_, v_half_372_);
if (v___x_373_ == 0)
{
uint8_t v___x_374_; 
v___x_374_ = lean_uint64_dec_lt(v_half_372_, v_remainder_370_);
if (v___x_374_ == 0)
{
uint64_t v___x_375_; uint8_t v___x_376_; 
v___x_375_ = lean_uint64_land(v_quotient_366_, v___x_367_);
v___x_376_ = lean_uint64_dec_eq(v___x_375_, v___y_350_);
if (v___x_376_ == 0)
{
uint64_t v___x_377_; 
v___x_377_ = lean_uint64_add(v_quotient_366_, v___x_367_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_377_;
goto v___jp_336_;
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v_quotient_366_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_378_; 
v___x_378_ = lean_uint64_add(v_quotient_366_, v___x_367_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_378_;
goto v___jp_336_;
}
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v_quotient_366_;
goto v___jp_336_;
}
}
}
else
{
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___y_348_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_379_; uint64_t v___x_380_; 
v___x_379_ = lean_uint64_sub(v___x_356_, v___y_352_);
v___x_380_ = lean_uint64_shift_left(v___y_348_, v___x_379_);
v___y_337_ = v___y_347_;
v___y_338_ = v_position_353_;
v___y_339_ = v___y_350_;
v___y_340_ = v___y_349_;
v___y_341_ = v___x_380_;
goto v___jp_336_;
}
}
else
{
uint64_t v___x_381_; uint8_t v___x_382_; 
v___x_381_ = 149ULL;
v___x_382_ = lean_uint64_dec_lt(v___y_351_, v___x_381_);
if (v___x_382_ == 0)
{
uint64_t v___x_383_; uint64_t v___x_384_; 
v___x_383_ = lean_uint64_sub(v___y_351_, v___x_381_);
v___x_384_ = lean_uint64_shift_left(v___y_348_, v___x_383_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_384_;
goto v___jp_146_;
}
else
{
uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_385_ = lean_uint64_sub(v___x_381_, v___y_351_);
v___x_386_ = lean_uint64_dec_eq(v___x_385_, v___y_350_);
if (v___x_386_ == 0)
{
uint64_t v___x_387_; uint8_t v___x_388_; 
v___x_387_ = 64ULL;
v___x_388_ = lean_uint64_dec_lt(v___x_385_, v___x_387_);
if (v___x_388_ == 0)
{
uint8_t v___x_389_; 
v___x_389_ = lean_uint64_dec_eq(v___x_385_, v___x_387_);
if (v___x_389_ == 0)
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_350_;
goto v___jp_146_;
}
else
{
uint64_t v___x_390_; uint8_t v___x_391_; 
v___x_390_ = 9223372036854775808ULL;
v___x_391_ = lean_uint64_dec_lt(v___x_390_, v___y_348_);
if (v___x_391_ == 0)
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_350_;
goto v___jp_146_;
}
else
{
uint64_t v___x_392_; 
v___x_392_ = 1ULL;
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_392_;
goto v___jp_146_;
}
}
}
else
{
uint64_t v_quotient_393_; uint64_t v___x_394_; uint64_t v___x_395_; uint64_t v___x_396_; uint64_t v_remainder_397_; uint64_t v___x_398_; uint64_t v_half_399_; uint8_t v___x_400_; 
v_quotient_393_ = lean_uint64_shift_right(v___y_348_, v___x_385_);
v___x_394_ = 1ULL;
v___x_395_ = lean_uint64_shift_left(v___x_394_, v___x_385_);
v___x_396_ = lean_uint64_sub(v___x_395_, v___x_394_);
v_remainder_397_ = lean_uint64_land(v___y_348_, v___x_396_);
v___x_398_ = lean_uint64_sub(v___x_385_, v___x_394_);
v_half_399_ = lean_uint64_shift_left(v___x_394_, v___x_398_);
v___x_400_ = lean_uint64_dec_lt(v_remainder_397_, v_half_399_);
if (v___x_400_ == 0)
{
uint8_t v___x_401_; 
v___x_401_ = lean_uint64_dec_lt(v_half_399_, v_remainder_397_);
if (v___x_401_ == 0)
{
uint64_t v___x_402_; uint8_t v___x_403_; 
v___x_402_ = lean_uint64_land(v_quotient_393_, v___x_394_);
v___x_403_ = lean_uint64_dec_eq(v___x_402_, v___y_350_);
if (v___x_403_ == 0)
{
uint64_t v___x_404_; 
v___x_404_ = lean_uint64_add(v_quotient_393_, v___x_394_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_404_;
goto v___jp_146_;
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v_quotient_393_;
goto v___jp_146_;
}
}
else
{
uint64_t v___x_405_; 
v___x_405_ = lean_uint64_add(v_quotient_393_, v___x_394_);
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___x_405_;
goto v___jp_146_;
}
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v_quotient_393_;
goto v___jp_146_;
}
}
}
else
{
v___y_147_ = v___y_347_;
v___y_148_ = v___y_349_;
v___y_149_ = v___y_350_;
v___y_150_ = v___y_348_;
goto v___jp_146_;
}
}
}
}
v___jp_406_:
{
uint64_t v___x_414_; uint64_t v___x_415_; uint8_t v___x_416_; 
v___x_414_ = 1ULL;
v___x_415_ = lean_uint64_shift_right(v___y_407_, v___x_414_);
v___x_416_ = lean_uint64_dec_eq(v___x_415_, v___y_411_);
if (v___x_416_ == 0)
{
uint64_t v___x_417_; 
v___x_417_ = lean_uint64_add(v___y_413_, v___x_414_);
v___y_347_ = v___y_408_;
v___y_348_ = v___y_410_;
v___y_349_ = v___y_409_;
v___y_350_ = v___y_411_;
v___y_351_ = v___y_412_;
v___y_352_ = v___x_417_;
goto v___jp_346_;
}
else
{
v___y_347_ = v___y_408_;
v___y_348_ = v___y_410_;
v___y_349_ = v___y_409_;
v___y_350_ = v___y_411_;
v___y_351_ = v___y_412_;
v___y_352_ = v___y_413_;
goto v___jp_346_;
}
}
v___jp_418_:
{
uint64_t v___x_428_; uint8_t v___x_429_; 
v___x_428_ = lean_uint64_shift_right(v___y_425_, v___y_419_);
v___x_429_ = lean_uint64_dec_eq(v___x_428_, v___y_422_);
if (v___x_429_ == 0)
{
uint64_t v___x_430_; 
v___x_430_ = lean_uint64_add(v___y_421_, v___y_419_);
v___y_407_ = v___y_427_;
v___y_408_ = v___y_420_;
v___y_409_ = v___y_424_;
v___y_410_ = v___y_423_;
v___y_411_ = v___y_422_;
v___y_412_ = v___y_426_;
v___y_413_ = v___x_430_;
goto v___jp_406_;
}
else
{
v___y_407_ = v___y_427_;
v___y_408_ = v___y_420_;
v___y_409_ = v___y_424_;
v___y_410_ = v___y_423_;
v___y_411_ = v___y_422_;
v___y_412_ = v___y_426_;
v___y_413_ = v___y_421_;
goto v___jp_406_;
}
}
v___jp_431_:
{
uint64_t v___x_439_; uint64_t v___x_440_; uint8_t v___x_441_; 
v___x_439_ = 2ULL;
v___x_440_ = lean_uint64_shift_right(v___y_436_, v___x_439_);
v___x_441_ = lean_uint64_dec_eq(v___x_440_, v___y_435_);
if (v___x_441_ == 0)
{
v___y_419_ = v___x_439_;
v___y_420_ = v___y_432_;
v___y_421_ = v___y_438_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_434_;
v___y_424_ = v___y_433_;
v___y_425_ = v___y_436_;
v___y_426_ = v___y_437_;
v___y_427_ = v___x_440_;
goto v___jp_418_;
}
else
{
v___y_419_ = v___x_439_;
v___y_420_ = v___y_432_;
v___y_421_ = v___y_438_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_434_;
v___y_424_ = v___y_433_;
v___y_425_ = v___y_436_;
v___y_426_ = v___y_437_;
v___y_427_ = v___y_436_;
goto v___jp_418_;
}
}
v___jp_442_:
{
uint64_t v___x_452_; uint8_t v___x_453_; 
v___x_452_ = lean_uint64_shift_right(v___y_449_, v___y_444_);
v___x_453_ = lean_uint64_dec_eq(v___x_452_, v___y_446_);
if (v___x_453_ == 0)
{
uint64_t v___x_454_; 
v___x_454_ = lean_uint64_add(v___y_445_, v___y_444_);
v___y_432_ = v___y_443_;
v___y_433_ = v___y_448_;
v___y_434_ = v___y_447_;
v___y_435_ = v___y_446_;
v___y_436_ = v___y_451_;
v___y_437_ = v___y_450_;
v___y_438_ = v___x_454_;
goto v___jp_431_;
}
else
{
v___y_432_ = v___y_443_;
v___y_433_ = v___y_448_;
v___y_434_ = v___y_447_;
v___y_435_ = v___y_446_;
v___y_436_ = v___y_451_;
v___y_437_ = v___y_450_;
v___y_438_ = v___y_445_;
goto v___jp_431_;
}
}
v___jp_455_:
{
uint64_t v___x_463_; uint64_t v___x_464_; uint8_t v___x_465_; 
v___x_463_ = 4ULL;
v___x_464_ = lean_uint64_shift_right(v___y_460_, v___x_463_);
v___x_465_ = lean_uint64_dec_eq(v___x_464_, v___y_459_);
if (v___x_465_ == 0)
{
v___y_443_ = v___y_456_;
v___y_444_ = v___x_463_;
v___y_445_ = v___y_462_;
v___y_446_ = v___y_459_;
v___y_447_ = v___y_458_;
v___y_448_ = v___y_457_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___x_464_;
goto v___jp_442_;
}
else
{
v___y_443_ = v___y_456_;
v___y_444_ = v___x_463_;
v___y_445_ = v___y_462_;
v___y_446_ = v___y_459_;
v___y_447_ = v___y_458_;
v___y_448_ = v___y_457_;
v___y_449_ = v___y_460_;
v___y_450_ = v___y_461_;
v___y_451_ = v___y_460_;
goto v___jp_442_;
}
}
v___jp_466_:
{
uint64_t v___x_476_; uint8_t v___x_477_; 
v___x_476_ = lean_uint64_shift_right(v___y_467_, v___y_474_);
v___x_477_ = lean_uint64_dec_eq(v___x_476_, v___y_469_);
if (v___x_477_ == 0)
{
uint64_t v___x_478_; 
v___x_478_ = lean_uint64_add(v___y_472_, v___y_474_);
v___y_456_ = v___y_468_;
v___y_457_ = v___y_471_;
v___y_458_ = v___y_470_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_475_;
v___y_461_ = v___y_473_;
v___y_462_ = v___x_478_;
goto v___jp_455_;
}
else
{
v___y_456_ = v___y_468_;
v___y_457_ = v___y_471_;
v___y_458_ = v___y_470_;
v___y_459_ = v___y_469_;
v___y_460_ = v___y_475_;
v___y_461_ = v___y_473_;
v___y_462_ = v___y_472_;
goto v___jp_455_;
}
}
v___jp_479_:
{
uint64_t v___x_487_; uint64_t v___x_488_; uint8_t v___x_489_; 
v___x_487_ = 8ULL;
v___x_488_ = lean_uint64_shift_right(v___y_480_, v___x_487_);
v___x_489_ = lean_uint64_dec_eq(v___x_488_, v___y_484_);
if (v___x_489_ == 0)
{
v___y_467_ = v___y_480_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_484_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_486_;
v___y_473_ = v___y_485_;
v___y_474_ = v___x_487_;
v___y_475_ = v___x_488_;
goto v___jp_466_;
}
else
{
v___y_467_ = v___y_480_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_484_;
v___y_470_ = v___y_483_;
v___y_471_ = v___y_482_;
v___y_472_ = v___y_486_;
v___y_473_ = v___y_485_;
v___y_474_ = v___x_487_;
v___y_475_ = v___y_480_;
goto v___jp_466_;
}
}
v___jp_490_:
{
uint64_t v___x_500_; uint8_t v___x_501_; 
v___x_500_ = lean_uint64_shift_right(v___y_492_, v___y_497_);
v___x_501_ = lean_uint64_dec_eq(v___x_500_, v___y_493_);
if (v___x_501_ == 0)
{
uint64_t v___x_502_; 
v___x_502_ = lean_uint64_add(v___y_498_, v___y_497_);
v___y_480_ = v___y_499_;
v___y_481_ = v___y_491_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_494_;
v___y_484_ = v___y_493_;
v___y_485_ = v___y_496_;
v___y_486_ = v___x_502_;
goto v___jp_479_;
}
else
{
v___y_480_ = v___y_499_;
v___y_481_ = v___y_491_;
v___y_482_ = v___y_495_;
v___y_483_ = v___y_494_;
v___y_484_ = v___y_493_;
v___y_485_ = v___y_496_;
v___y_486_ = v___y_498_;
goto v___jp_479_;
}
}
v___jp_503_:
{
uint64_t v___x_511_; uint64_t v___x_512_; uint8_t v___x_513_; 
v___x_511_ = 16ULL;
v___x_512_ = lean_uint64_shift_right(v___y_505_, v___x_511_);
v___x_513_ = lean_uint64_dec_eq(v___x_512_, v___y_508_);
if (v___x_513_ == 0)
{
v___y_491_ = v___y_504_;
v___y_492_ = v___y_505_;
v___y_493_ = v___y_508_;
v___y_494_ = v___y_507_;
v___y_495_ = v___y_506_;
v___y_496_ = v___y_509_;
v___y_497_ = v___x_511_;
v___y_498_ = v___y_510_;
v___y_499_ = v___x_512_;
goto v___jp_490_;
}
else
{
v___y_491_ = v___y_504_;
v___y_492_ = v___y_505_;
v___y_493_ = v___y_508_;
v___y_494_ = v___y_507_;
v___y_495_ = v___y_506_;
v___y_496_ = v___y_509_;
v___y_497_ = v___x_511_;
v___y_498_ = v___y_510_;
v___y_499_ = v___y_505_;
goto v___jp_490_;
}
}
v___jp_514_:
{
uint64_t v___x_522_; uint8_t v___x_523_; 
v___x_522_ = lean_uint64_shift_right(v___y_518_, v___y_516_);
v___x_523_ = lean_uint64_dec_eq(v___x_522_, v___y_517_);
if (v___x_523_ == 0)
{
v___y_504_ = v___y_515_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_519_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_517_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_516_;
goto v___jp_503_;
}
else
{
v___y_504_ = v___y_515_;
v___y_505_ = v___y_521_;
v___y_506_ = v___y_519_;
v___y_507_ = v___y_518_;
v___y_508_ = v___y_517_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_517_;
goto v___jp_503_;
}
}
v___jp_524_:
{
uint64_t v___x_529_; uint8_t v___x_530_; 
v___x_529_ = 0ULL;
v___x_530_ = lean_uint64_dec_eq(v___y_526_, v___x_529_);
if (v___x_530_ == 0)
{
uint64_t v___x_531_; uint64_t v___x_532_; uint8_t v___x_533_; 
v___x_531_ = 32ULL;
v___x_532_ = lean_uint64_shift_right(v___y_526_, v___x_531_);
v___x_533_ = lean_uint64_dec_eq(v___x_532_, v___x_529_);
if (v___x_533_ == 0)
{
v___y_515_ = v___y_525_;
v___y_516_ = v___x_531_;
v___y_517_ = v___x_529_;
v___y_518_ = v___y_526_;
v___y_519_ = v___y_527_;
v___y_520_ = v___y_528_;
v___y_521_ = v___x_532_;
goto v___jp_514_;
}
else
{
v___y_515_ = v___y_525_;
v___y_516_ = v___x_531_;
v___y_517_ = v___x_529_;
v___y_518_ = v___y_526_;
v___y_519_ = v___y_527_;
v___y_520_ = v___y_528_;
v___y_521_ = v___y_526_;
goto v___jp_514_;
}
}
else
{
if (v___y_525_ == 0)
{
uint32_t v___x_534_; 
v___x_534_ = 0;
return v___x_534_;
}
else
{
uint32_t v___x_535_; 
v___x_535_ = 2147483648;
return v___x_535_;
}
}
}
v___jp_536_:
{
uint64_t v___x_543_; uint64_t v___x_544_; uint64_t v___x_545_; uint8_t v___x_546_; 
v___x_543_ = lean_uint64_mul(v___y_541_, v___y_540_);
v___x_544_ = lean_uint64_add(v___y_538_, v___y_542_);
v___x_545_ = 281474976710656ULL;
v___x_546_ = lean_uint64_dec_lt(v___x_543_, v___x_545_);
if (v___x_546_ == 0)
{
v___y_525_ = v___y_537_;
v___y_526_ = v___x_543_;
v___y_527_ = v___y_539_;
v___y_528_ = v___x_544_;
goto v___jp_524_;
}
else
{
uint64_t v___x_547_; uint8_t v___x_548_; 
v___x_547_ = 123ULL;
v___x_548_ = lean_uint64_dec_le(v___x_544_, v___x_547_);
if (v___x_548_ == 0)
{
v___y_525_ = v___y_537_;
v___y_526_ = v___x_543_;
v___y_527_ = v___y_539_;
v___y_528_ = v___x_544_;
goto v___jp_524_;
}
else
{
uint64_t v___x_549_; uint8_t v___x_550_; 
v___x_549_ = 0ULL;
v___x_550_ = lean_uint64_dec_eq(v___x_543_, v___x_549_);
if (v___x_550_ == 0)
{
uint64_t v___x_551_; uint64_t v___x_552_; uint8_t v___x_553_; 
v___x_551_ = 149ULL;
v___x_552_ = lean_uint64_sub(v___x_551_, v___x_544_);
v___x_553_ = lean_uint64_dec_eq(v___x_552_, v___x_549_);
if (v___x_553_ == 0)
{
uint64_t v___x_554_; uint8_t v___x_555_; 
v___x_554_ = 64ULL;
v___x_555_ = lean_uint64_dec_lt(v___x_552_, v___x_554_);
if (v___x_555_ == 0)
{
uint8_t v___x_556_; 
v___x_556_ = lean_uint64_dec_eq(v___x_552_, v___x_554_);
if (v___x_556_ == 0)
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_549_;
goto v___jp_167_;
}
else
{
uint64_t v___x_557_; uint8_t v___x_558_; 
v___x_557_ = 9223372036854775808ULL;
v___x_558_ = lean_uint64_dec_lt(v___x_557_, v___x_543_);
if (v___x_558_ == 0)
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_549_;
goto v___jp_167_;
}
else
{
uint64_t v___x_559_; 
v___x_559_ = 1ULL;
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_559_;
goto v___jp_167_;
}
}
}
else
{
uint64_t v_quotient_560_; uint64_t v___x_561_; uint64_t v___x_562_; uint64_t v___x_563_; uint64_t v_remainder_564_; uint64_t v___x_565_; uint64_t v_half_566_; uint8_t v___x_567_; 
v_quotient_560_ = lean_uint64_shift_right(v___x_543_, v___x_552_);
v___x_561_ = 1ULL;
v___x_562_ = lean_uint64_shift_left(v___x_561_, v___x_552_);
v___x_563_ = lean_uint64_sub(v___x_562_, v___x_561_);
v_remainder_564_ = lean_uint64_land(v___x_543_, v___x_563_);
v___x_565_ = lean_uint64_sub(v___x_552_, v___x_561_);
v_half_566_ = lean_uint64_shift_left(v___x_561_, v___x_565_);
v___x_567_ = lean_uint64_dec_lt(v_remainder_564_, v_half_566_);
if (v___x_567_ == 0)
{
uint8_t v___x_568_; 
v___x_568_ = lean_uint64_dec_lt(v_half_566_, v_remainder_564_);
if (v___x_568_ == 0)
{
uint64_t v___x_569_; uint8_t v___x_570_; 
v___x_569_ = lean_uint64_land(v_quotient_560_, v___x_561_);
v___x_570_ = lean_uint64_dec_eq(v___x_569_, v___x_549_);
if (v___x_570_ == 0)
{
uint64_t v___x_571_; 
v___x_571_ = lean_uint64_add(v_quotient_560_, v___x_561_);
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_571_;
goto v___jp_167_;
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v_quotient_560_;
goto v___jp_167_;
}
}
else
{
uint64_t v___x_572_; 
v___x_572_ = lean_uint64_add(v_quotient_560_, v___x_561_);
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_572_;
goto v___jp_167_;
}
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v_quotient_560_;
goto v___jp_167_;
}
}
}
else
{
v___y_168_ = v___y_537_;
v___y_169_ = v___y_539_;
v___y_170_ = v___x_549_;
v___y_171_ = v___x_543_;
goto v___jp_167_;
}
}
else
{
if (v___y_537_ == 0)
{
uint32_t v___x_573_; 
v___x_573_ = 0;
return v___x_573_;
}
else
{
uint32_t v___x_574_; 
v___x_574_ = 2147483648;
return v___x_574_;
}
}
}
}
}
v___jp_578_:
{
uint64_t v___x_584_; uint64_t v___x_585_; uint8_t v___x_586_; 
v___x_584_ = lean_uint32_to_uint64(v_ey_577_);
v___x_585_ = 0ULL;
v___x_586_ = lean_uint64_dec_eq(v___x_584_, v___x_585_);
if (v___x_586_ == 0)
{
uint64_t v___x_587_; uint64_t v___x_588_; 
v___x_587_ = 1ULL;
v___x_588_ = lean_uint64_sub(v___x_584_, v___x_587_);
v___y_537_ = v___y_579_;
v___y_538_ = v___y_583_;
v___y_539_ = v___y_580_;
v___y_540_ = v___y_581_;
v___y_541_ = v___y_582_;
v___y_542_ = v___x_588_;
goto v___jp_536_;
}
else
{
v___y_537_ = v___y_579_;
v___y_538_ = v___y_583_;
v___y_539_ = v___y_580_;
v___y_540_ = v___y_581_;
v___y_541_ = v___y_582_;
v___y_542_ = v___x_585_;
goto v___jp_536_;
}
}
v___jp_589_:
{
uint64_t v___x_594_; uint64_t v___x_595_; uint8_t v___x_596_; 
v___x_594_ = lean_uint32_to_uint64(v_ex_575_);
v___x_595_ = 0ULL;
v___x_596_ = lean_uint64_dec_eq(v___x_594_, v___x_595_);
if (v___x_596_ == 0)
{
uint64_t v___x_597_; uint64_t v___x_598_; 
v___x_597_ = 1ULL;
v___x_598_ = lean_uint64_sub(v___x_594_, v___x_597_);
v___y_579_ = v___y_590_;
v___y_580_ = v___y_591_;
v___y_581_ = v___y_593_;
v___y_582_ = v___y_592_;
v___y_583_ = v___x_598_;
goto v___jp_578_;
}
else
{
v___y_579_ = v___y_590_;
v___y_580_ = v___y_591_;
v___y_581_ = v___y_593_;
v___y_582_ = v___y_592_;
v___y_583_ = v___x_595_;
goto v___jp_578_;
}
}
v___jp_599_:
{
uint32_t v___x_604_; uint8_t v___x_605_; 
v___x_604_ = 0;
v___x_605_ = lean_uint32_dec_eq(v_ey_577_, v___x_604_);
if (v___x_605_ == 0)
{
uint64_t v___x_606_; uint64_t v___x_607_; uint64_t v___x_608_; 
v___x_606_ = lean_uint32_to_uint64(v___y_600_);
v___x_607_ = 8388608ULL;
v___x_608_ = lean_uint64_lor(v___x_606_, v___x_607_);
v___y_590_ = v___y_601_;
v___y_591_ = v___y_602_;
v___y_592_ = v___y_603_;
v___y_593_ = v___x_608_;
goto v___jp_589_;
}
else
{
uint64_t v___x_609_; 
v___x_609_ = lean_uint32_to_uint64(v___y_600_);
v___y_590_ = v___y_601_;
v___y_591_ = v___y_602_;
v___y_592_ = v___y_603_;
v___y_593_ = v___x_609_;
goto v___jp_589_;
}
}
v___jp_610_:
{
uint32_t v___x_612_; uint32_t v_xFraction_613_; uint32_t v_yFraction_614_; uint32_t v___x_615_; uint8_t v___x_616_; 
v___x_612_ = 8388607;
v_xFraction_613_ = lean_uint32_land(v___y_130_, v___x_612_);
v_yFraction_614_ = lean_uint32_land(v___y_131_, v___x_612_);
v___x_615_ = 0;
v___x_616_ = lean_uint32_dec_eq(v_ex_575_, v___x_615_);
if (v___x_616_ == 0)
{
uint64_t v___x_617_; uint64_t v___x_618_; uint64_t v___x_619_; 
v___x_617_ = lean_uint32_to_uint64(v_xFraction_613_);
v___x_618_ = 8388608ULL;
v___x_619_ = lean_uint64_lor(v___x_617_, v___x_618_);
v___y_600_ = v_yFraction_614_;
v___y_601_ = v___y_611_;
v___y_602_ = v___x_612_;
v___y_603_ = v___x_619_;
goto v___jp_599_;
}
else
{
uint64_t v___x_620_; 
v___x_620_ = lean_uint32_to_uint64(v_xFraction_613_);
v___y_600_ = v_yFraction_614_;
v___y_601_ = v___y_611_;
v___y_602_ = v___x_612_;
v___y_603_ = v___x_620_;
goto v___jp_599_;
}
}
v___jp_624_:
{
if (v___y_626_ == 0)
{
v___y_611_ = v___x_623_;
goto v___jp_610_;
}
else
{
v___y_611_ = v___y_625_;
goto v___jp_610_;
}
}
v___jp_627_:
{
if (v___y_628_ == 0)
{
if (v___y_630_ == 0)
{
v___y_625_ = v___y_629_;
v___y_626_ = v___x_623_;
goto v___jp_624_;
}
else
{
v___y_611_ = v___x_623_;
goto v___jp_610_;
}
}
else
{
v___y_625_ = v___y_629_;
v___y_626_ = v___y_630_;
goto v___jp_624_;
}
}
v___jp_631_:
{
uint32_t v___x_634_; uint32_t v___x_635_; uint32_t v___x_636_; uint8_t v___x_637_; 
v___x_634_ = 2147483648;
v___x_635_ = lean_uint32_land(v___y_131_, v___x_634_);
v___x_636_ = 0;
v___x_637_ = lean_uint32_dec_eq(v___x_635_, v___x_636_);
if (v___x_637_ == 0)
{
v___y_628_ = v___y_633_;
v___y_629_ = v___y_632_;
v___y_630_ = v___x_623_;
goto v___jp_627_;
}
else
{
v___y_628_ = v___y_633_;
v___y_629_ = v___y_632_;
v___y_630_ = v___y_632_;
goto v___jp_627_;
}
}
v___jp_638_:
{
if (v___y_639_ == 0)
{
uint32_t v___x_640_; uint32_t v___x_641_; uint32_t v___x_642_; uint8_t v___x_643_; 
v___x_640_ = 2147483648;
v___x_641_ = lean_uint32_land(v___y_130_, v___x_640_);
v___x_642_ = 0;
v___x_643_ = lean_uint32_dec_eq(v___x_641_, v___x_642_);
if (v___x_643_ == 0)
{
v___y_632_ = v___y_639_;
v___y_633_ = v___x_623_;
goto v___jp_631_;
}
else
{
v___y_632_ = v___y_639_;
v___y_633_ = v___y_639_;
goto v___jp_631_;
}
}
else
{
lean_object* v___x_644_; lean_object* v___x_645_; lean_object* v___x_646_; uint32_t v___x_647_; 
v___x_644_ = lean_uint32_to_nat(v___y_130_);
v___x_645_ = lean_uint32_to_nat(v___y_131_);
v___x_646_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_644_, v___x_645_);
v___x_647_ = lean_uint32_of_nat(v___x_646_);
lean_dec(v___x_646_);
return v___x_647_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_662_, lean_object* v___y_663_){
_start:
{
uint32_t v___y_2440__boxed_664_; uint32_t v___y_2441__boxed_665_; uint32_t v_res_666_; lean_object* v_r_667_; 
v___y_2440__boxed_664_ = lean_unbox_uint32(v___y_662_);
lean_dec(v___y_662_);
v___y_2441__boxed_665_ = lean_unbox_uint32(v___y_663_);
lean_dec(v___y_663_);
v_res_666_ = lp_competition_main___lam__1(v___y_2440__boxed_664_, v___y_2441__boxed_665_);
v_r_667_ = lean_box_uint32(v_res_666_);
return v_r_667_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___f_673_; lean_object* v___f_674_; lean_object* v___f_675_; lean_object* v___x_676_; lean_object* v___x_677_; 
v___f_673_ = ((lean_object*)(lp_competition_main___closed__0));
v___f_674_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_675_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_676_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_677_ = lp_competition_Bench_runFull(v___f_673_, v___f_674_, v___x_676_, v___f_675_);
return v___x_677_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_678_){
_start:
{
lean_object* v_res_679_; 
v_res_679_ = _lean_main();
return v_res_679_;
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
