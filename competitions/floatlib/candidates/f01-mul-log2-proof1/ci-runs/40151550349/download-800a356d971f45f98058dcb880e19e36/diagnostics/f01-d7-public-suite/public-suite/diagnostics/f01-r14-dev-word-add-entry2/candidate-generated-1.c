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
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
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
uint32_t lean_uint32_add(uint32_t, uint32_t);
uint64_t lean_uint32_to_uint64(uint32_t);
uint64_t lean_uint64_sub(uint64_t, uint64_t);
uint64_t lean_uint64_shift_left(uint64_t, uint64_t);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint64_t lean_uint64_land(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
lean_object* lean_io_getenv(lean_object*);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
uint8_t lean_uint64_dec_lt(uint64_t, uint64_t);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_runFull(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__2(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_main___lam__2___boxed(lean_object*, lean_object*);
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
static const lean_closure_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__2___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_closure_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_main___lam__3___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
uint32_t v___y_4_; uint32_t v___y_5_; uint32_t v___y_6_; uint32_t v___y_7_; uint32_t v___y_8_; uint32_t v___y_9_; uint8_t v___y_21_; uint8_t v___y_35_; uint8_t v___y_49_; uint8_t v___y_66_; float v___y_73_; float v___y_74_; float v___y_88_; uint8_t v___y_89_; float v___y_104_; uint8_t v___y_114_; uint8_t v___y_134_; uint8_t v___y_148_; uint8_t v___y_162_; uint8_t v___y_179_; float v___y_186_; float v___y_187_; float v___y_201_; uint8_t v___y_202_; float v___y_217_; uint8_t v___y_227_; uint8_t v___y_247_; uint8_t v___y_261_; uint8_t v___y_275_; uint8_t v___y_292_; float v___y_299_; float v___y_300_; float v___y_314_; uint8_t v___y_315_; float v___y_330_; uint32_t v___y_340_; uint32_t v___y_341_; uint32_t v___y_342_; uint8_t v___y_343_; uint32_t v___y_355_; uint32_t v___y_356_; uint32_t v___y_357_; uint32_t v___y_358_; uint32_t v___y_359_; uint32_t v___y_360_; uint32_t v___y_361_; uint32_t v___y_362_; uint32_t v___y_363_; uint32_t v___y_403_; uint32_t v___y_404_; uint32_t v___y_405_; uint32_t v___y_406_; uint32_t v___y_407_; uint32_t v___y_408_; uint8_t v___y_409_; uint8_t v___y_421_; uint32_t v___y_422_; uint32_t v___y_423_; uint8_t v___y_435_; uint32_t v___y_436_; uint8_t v___y_445_; uint8_t v___y_454_; uint32_t v___y_464_; uint32_t v___y_465_; uint32_t v___y_466_; uint32_t v___y_467_; uint32_t v___y_468_; uint32_t v___y_474_; uint32_t v___y_475_; uint8_t v___y_486_; uint32_t v___y_496_; uint32_t v___y_497_; uint32_t v___y_498_; uint32_t v___y_499_; uint32_t v___y_509_; uint8_t v___y_520_; uint32_t v___x_536_; uint32_t v___x_537_; uint32_t v___x_538_; uint32_t v___x_539_; uint32_t v___x_540_; uint32_t v___x_541_; uint32_t v___x_542_; uint8_t v___x_543_; 
v___x_536_ = 23;
v___x_537_ = lean_uint32_shift_right(v___y_1_, v___x_536_);
v___x_538_ = 255;
v___x_539_ = lean_uint32_land(v___x_537_, v___x_538_);
v___x_540_ = 1;
v___x_541_ = lean_uint32_sub(v___x_539_, v___x_540_);
v___x_542_ = 253;
v___x_543_ = lean_uint32_dec_le(v___x_541_, v___x_542_);
if (v___x_543_ == 0)
{
v___y_520_ = v___x_543_;
goto v___jp_519_;
}
else
{
uint32_t v___x_544_; uint32_t v___x_545_; uint32_t v___x_546_; uint8_t v___x_547_; 
v___x_544_ = lean_uint32_shift_right(v___y_2_, v___x_536_);
v___x_545_ = lean_uint32_land(v___x_544_, v___x_538_);
v___x_546_ = lean_uint32_sub(v___x_545_, v___x_540_);
v___x_547_ = lean_uint32_dec_le(v___x_546_, v___x_542_);
v___y_520_ = v___x_547_;
goto v___jp_519_;
}
v___jp_3_:
{
uint32_t v___x_10_; uint32_t v___x_11_; uint32_t v___x_12_; uint32_t v___x_13_; uint32_t v___x_14_; 
v___x_10_ = lean_uint32_land(v___y_5_, v___y_8_);
v___x_11_ = lean_uint32_shift_left(v___x_10_, v___y_4_);
v___x_12_ = lean_uint32_lor(v___y_9_, v___x_11_);
v___x_13_ = lean_uint32_land(v___y_6_, v___y_7_);
v___x_14_ = lean_uint32_lor(v___x_12_, v___x_13_);
return v___x_14_;
}
v___jp_15_:
{
lean_object* v___x_16_; lean_object* v___x_17_; lean_object* v___x_18_; uint32_t v___x_19_; 
v___x_16_ = lean_uint32_to_nat(v___y_1_);
v___x_17_ = lean_uint32_to_nat(v___y_2_);
v___x_18_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_16_, v___x_17_);
v___x_19_ = lean_uint32_of_nat(v___x_18_);
lean_dec(v___x_18_);
return v___x_19_;
}
v___jp_20_:
{
if (v___y_21_ == 0)
{
goto v___jp_15_;
}
else
{
uint32_t v___x_22_; uint32_t v___x_23_; 
v___x_22_ = 4194304;
v___x_23_ = lean_uint32_lor(v___y_2_, v___x_22_);
return v___x_23_;
}
}
v___jp_24_:
{
uint32_t v___x_25_; uint32_t v___x_26_; uint32_t v___x_27_; uint32_t v___x_28_; uint8_t v___x_29_; 
v___x_25_ = 23;
v___x_26_ = lean_uint32_shift_right(v___y_2_, v___x_25_);
v___x_27_ = 255;
v___x_28_ = lean_uint32_land(v___x_26_, v___x_27_);
v___x_29_ = lean_uint32_dec_eq(v___x_28_, v___x_27_);
if (v___x_29_ == 0)
{
v___y_21_ = v___x_29_;
goto v___jp_20_;
}
else
{
uint32_t v___x_30_; uint32_t v___x_31_; uint32_t v___x_32_; uint8_t v___x_33_; 
v___x_30_ = 8388607;
v___x_31_ = lean_uint32_land(v___y_2_, v___x_30_);
v___x_32_ = 0;
v___x_33_ = lean_uint32_dec_eq(v___x_31_, v___x_32_);
if (v___x_33_ == 0)
{
v___y_21_ = v___x_29_;
goto v___jp_20_;
}
else
{
goto v___jp_15_;
}
}
}
v___jp_34_:
{
if (v___y_35_ == 0)
{
goto v___jp_24_;
}
else
{
uint32_t v___x_36_; uint32_t v___x_37_; 
v___x_36_ = 4194304;
v___x_37_ = lean_uint32_lor(v___y_1_, v___x_36_);
return v___x_37_;
}
}
v___jp_38_:
{
uint32_t v___x_39_; uint32_t v___x_40_; uint32_t v___x_41_; uint32_t v___x_42_; uint8_t v___x_43_; 
v___x_39_ = 23;
v___x_40_ = lean_uint32_shift_right(v___y_1_, v___x_39_);
v___x_41_ = 255;
v___x_42_ = lean_uint32_land(v___x_40_, v___x_41_);
v___x_43_ = lean_uint32_dec_eq(v___x_42_, v___x_41_);
if (v___x_43_ == 0)
{
v___y_35_ = v___x_43_;
goto v___jp_34_;
}
else
{
uint32_t v___x_44_; uint32_t v___x_45_; uint32_t v___x_46_; uint8_t v___x_47_; 
v___x_44_ = 8388607;
v___x_45_ = lean_uint32_land(v___y_1_, v___x_44_);
v___x_46_ = 0;
v___x_47_ = lean_uint32_dec_eq(v___x_45_, v___x_46_);
if (v___x_47_ == 0)
{
v___y_35_ = v___x_43_;
goto v___jp_34_;
}
else
{
goto v___jp_24_;
}
}
}
v___jp_48_:
{
if (v___y_49_ == 0)
{
goto v___jp_38_;
}
else
{
uint32_t v___x_50_; uint32_t v___x_51_; uint32_t v___x_52_; uint8_t v___x_53_; 
v___x_50_ = 4194304;
v___x_51_ = lean_uint32_land(v___y_2_, v___x_50_);
v___x_52_ = 0;
v___x_53_ = lean_uint32_dec_eq(v___x_51_, v___x_52_);
if (v___x_53_ == 0)
{
goto v___jp_38_;
}
else
{
uint32_t v___x_54_; 
v___x_54_ = lean_uint32_lor(v___y_2_, v___x_50_);
return v___x_54_;
}
}
}
v___jp_55_:
{
uint32_t v___x_56_; uint32_t v___x_57_; uint32_t v___x_58_; uint32_t v___x_59_; uint8_t v___x_60_; 
v___x_56_ = 23;
v___x_57_ = lean_uint32_shift_right(v___y_2_, v___x_56_);
v___x_58_ = 255;
v___x_59_ = lean_uint32_land(v___x_57_, v___x_58_);
v___x_60_ = lean_uint32_dec_eq(v___x_59_, v___x_58_);
if (v___x_60_ == 0)
{
v___y_49_ = v___x_60_;
goto v___jp_48_;
}
else
{
uint32_t v___x_61_; uint32_t v___x_62_; uint32_t v___x_63_; uint8_t v___x_64_; 
v___x_61_ = 8388607;
v___x_62_ = lean_uint32_land(v___y_2_, v___x_61_);
v___x_63_ = 0;
v___x_64_ = lean_uint32_dec_eq(v___x_62_, v___x_63_);
if (v___x_64_ == 0)
{
v___y_49_ = v___x_60_;
goto v___jp_48_;
}
else
{
goto v___jp_38_;
}
}
}
v___jp_65_:
{
if (v___y_66_ == 0)
{
goto v___jp_55_;
}
else
{
uint32_t v___x_67_; uint32_t v___x_68_; uint32_t v___x_69_; uint8_t v___x_70_; 
v___x_67_ = 4194304;
v___x_68_ = lean_uint32_land(v___y_1_, v___x_67_);
v___x_69_ = 0;
v___x_70_ = lean_uint32_dec_eq(v___x_68_, v___x_69_);
if (v___x_70_ == 0)
{
goto v___jp_55_;
}
else
{
uint32_t v___x_71_; 
v___x_71_ = lean_uint32_lor(v___y_1_, v___x_67_);
return v___x_71_;
}
}
}
v___jp_72_:
{
float v_result_75_; uint8_t v___x_76_; 
v_result_75_ = lean_float32_add(v___y_73_, v___y_74_);
v___x_76_ = lean_float32_beq(v_result_75_, v_result_75_);
if (v___x_76_ == 0)
{
uint32_t v___x_77_; uint32_t v___x_78_; uint32_t v___x_79_; uint32_t v___x_80_; uint8_t v___x_81_; 
v___x_77_ = 23;
v___x_78_ = lean_uint32_shift_right(v___y_1_, v___x_77_);
v___x_79_ = 255;
v___x_80_ = lean_uint32_land(v___x_78_, v___x_79_);
v___x_81_ = lean_uint32_dec_eq(v___x_80_, v___x_79_);
if (v___x_81_ == 0)
{
v___y_66_ = v___x_81_;
goto v___jp_65_;
}
else
{
uint32_t v___x_82_; uint32_t v___x_83_; uint32_t v___x_84_; uint8_t v___x_85_; 
v___x_82_ = 8388607;
v___x_83_ = lean_uint32_land(v___y_1_, v___x_82_);
v___x_84_ = 0;
v___x_85_ = lean_uint32_dec_eq(v___x_83_, v___x_84_);
if (v___x_85_ == 0)
{
v___y_66_ = v___x_81_;
goto v___jp_65_;
}
else
{
goto v___jp_55_;
}
}
}
else
{
uint32_t v___x_86_; 
v___x_86_ = lean_float32_to_bits(v_result_75_);
return v___x_86_;
}
}
v___jp_87_:
{
if (v___y_89_ == 0)
{
float v___x_90_; 
v___x_90_ = lean_float32_of_bits(v___y_2_);
v___y_73_ = v___y_88_;
v___y_74_ = v___x_90_;
goto v___jp_72_;
}
else
{
uint32_t v___x_91_; uint32_t v___x_92_; uint32_t v___x_93_; uint32_t v___x_94_; float v___x_95_; lean_object* v___x_96_; uint32_t v___x_97_; uint32_t v___x_98_; lean_object* v___x_99_; lean_object* v___x_100_; float v___x_101_; float v___x_102_; 
v___x_91_ = 8388607;
v___x_92_ = lean_uint32_land(v___y_2_, v___x_91_);
v___x_93_ = 8388608;
v___x_94_ = lean_uint32_lor(v___x_92_, v___x_93_);
v___x_95_ = lean_uint32_to_float32(v___x_94_);
v___x_96_ = lp_competition_R2W01b_scaleTable;
v___x_97_ = 23;
v___x_98_ = lean_uint32_shift_right(v___y_2_, v___x_97_);
v___x_99_ = lean_uint32_to_nat(v___x_98_);
v___x_100_ = lean_array_fget_borrowed(v___x_96_, v___x_99_);
lean_dec(v___x_99_);
v___x_101_ = lean_unbox_float32(v___x_100_);
v___x_102_ = lean_float32_mul(v___x_95_, v___x_101_);
v___y_73_ = v___y_88_;
v___y_74_ = v___x_102_;
goto v___jp_72_;
}
}
v___jp_103_:
{
uint32_t v___x_105_; uint32_t v_a_106_; uint32_t v___x_107_; uint32_t v___x_108_; uint32_t v___x_109_; uint8_t v___x_110_; 
v___x_105_ = 2147483647;
v_a_106_ = lean_uint32_land(v___y_2_, v___x_105_);
v___x_107_ = 201326591;
v___x_108_ = 1;
v___x_109_ = lean_uint32_sub(v_a_106_, v___x_108_);
v___x_110_ = lean_uint32_dec_le(v___x_107_, v___x_109_);
if (v___x_110_ == 0)
{
v___y_88_ = v___y_104_;
v___y_89_ = v___x_110_;
goto v___jp_87_;
}
else
{
uint32_t v___x_111_; uint8_t v___x_112_; 
v___x_111_ = 2139095040;
v___x_112_ = lean_uint32_dec_lt(v_a_106_, v___x_111_);
v___y_88_ = v___y_104_;
v___y_89_ = v___x_112_;
goto v___jp_87_;
}
}
v___jp_113_:
{
if (v___y_114_ == 0)
{
float v___x_115_; 
v___x_115_ = lean_float32_of_bits(v___y_1_);
v___y_104_ = v___x_115_;
goto v___jp_103_;
}
else
{
uint32_t v___x_116_; uint32_t v___x_117_; uint32_t v___x_118_; uint32_t v___x_119_; float v___x_120_; lean_object* v___x_121_; uint32_t v___x_122_; uint32_t v___x_123_; lean_object* v___x_124_; lean_object* v___x_125_; float v___x_126_; float v___x_127_; 
v___x_116_ = 8388607;
v___x_117_ = lean_uint32_land(v___y_1_, v___x_116_);
v___x_118_ = 8388608;
v___x_119_ = lean_uint32_lor(v___x_117_, v___x_118_);
v___x_120_ = lean_uint32_to_float32(v___x_119_);
v___x_121_ = lp_competition_R2W01b_scaleTable;
v___x_122_ = 23;
v___x_123_ = lean_uint32_shift_right(v___y_1_, v___x_122_);
v___x_124_ = lean_uint32_to_nat(v___x_123_);
v___x_125_ = lean_array_fget_borrowed(v___x_121_, v___x_124_);
lean_dec(v___x_124_);
v___x_126_ = lean_unbox_float32(v___x_125_);
v___x_127_ = lean_float32_mul(v___x_120_, v___x_126_);
v___y_104_ = v___x_127_;
goto v___jp_103_;
}
}
v___jp_128_:
{
lean_object* v___x_129_; lean_object* v___x_130_; lean_object* v___x_131_; uint32_t v___x_132_; 
v___x_129_ = lean_uint32_to_nat(v___y_1_);
v___x_130_ = lean_uint32_to_nat(v___y_2_);
v___x_131_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_129_, v___x_130_);
v___x_132_ = lean_uint32_of_nat(v___x_131_);
lean_dec(v___x_131_);
return v___x_132_;
}
v___jp_133_:
{
if (v___y_134_ == 0)
{
goto v___jp_128_;
}
else
{
uint32_t v___x_135_; uint32_t v___x_136_; 
v___x_135_ = 4194304;
v___x_136_ = lean_uint32_lor(v___y_2_, v___x_135_);
return v___x_136_;
}
}
v___jp_137_:
{
uint32_t v___x_138_; uint32_t v___x_139_; uint32_t v___x_140_; uint32_t v___x_141_; uint8_t v___x_142_; 
v___x_138_ = 23;
v___x_139_ = lean_uint32_shift_right(v___y_2_, v___x_138_);
v___x_140_ = 255;
v___x_141_ = lean_uint32_land(v___x_139_, v___x_140_);
v___x_142_ = lean_uint32_dec_eq(v___x_141_, v___x_140_);
if (v___x_142_ == 0)
{
v___y_134_ = v___x_142_;
goto v___jp_133_;
}
else
{
uint32_t v___x_143_; uint32_t v___x_144_; uint32_t v___x_145_; uint8_t v___x_146_; 
v___x_143_ = 8388607;
v___x_144_ = lean_uint32_land(v___y_2_, v___x_143_);
v___x_145_ = 0;
v___x_146_ = lean_uint32_dec_eq(v___x_144_, v___x_145_);
if (v___x_146_ == 0)
{
v___y_134_ = v___x_142_;
goto v___jp_133_;
}
else
{
goto v___jp_128_;
}
}
}
v___jp_147_:
{
if (v___y_148_ == 0)
{
goto v___jp_137_;
}
else
{
uint32_t v___x_149_; uint32_t v___x_150_; 
v___x_149_ = 4194304;
v___x_150_ = lean_uint32_lor(v___y_1_, v___x_149_);
return v___x_150_;
}
}
v___jp_151_:
{
uint32_t v___x_152_; uint32_t v___x_153_; uint32_t v___x_154_; uint32_t v___x_155_; uint8_t v___x_156_; 
v___x_152_ = 23;
v___x_153_ = lean_uint32_shift_right(v___y_1_, v___x_152_);
v___x_154_ = 255;
v___x_155_ = lean_uint32_land(v___x_153_, v___x_154_);
v___x_156_ = lean_uint32_dec_eq(v___x_155_, v___x_154_);
if (v___x_156_ == 0)
{
v___y_148_ = v___x_156_;
goto v___jp_147_;
}
else
{
uint32_t v___x_157_; uint32_t v___x_158_; uint32_t v___x_159_; uint8_t v___x_160_; 
v___x_157_ = 8388607;
v___x_158_ = lean_uint32_land(v___y_1_, v___x_157_);
v___x_159_ = 0;
v___x_160_ = lean_uint32_dec_eq(v___x_158_, v___x_159_);
if (v___x_160_ == 0)
{
v___y_148_ = v___x_156_;
goto v___jp_147_;
}
else
{
goto v___jp_137_;
}
}
}
v___jp_161_:
{
if (v___y_162_ == 0)
{
goto v___jp_151_;
}
else
{
uint32_t v___x_163_; uint32_t v___x_164_; uint32_t v___x_165_; uint8_t v___x_166_; 
v___x_163_ = 4194304;
v___x_164_ = lean_uint32_land(v___y_2_, v___x_163_);
v___x_165_ = 0;
v___x_166_ = lean_uint32_dec_eq(v___x_164_, v___x_165_);
if (v___x_166_ == 0)
{
goto v___jp_151_;
}
else
{
uint32_t v___x_167_; 
v___x_167_ = lean_uint32_lor(v___y_2_, v___x_163_);
return v___x_167_;
}
}
}
v___jp_168_:
{
uint32_t v___x_169_; uint32_t v___x_170_; uint32_t v___x_171_; uint32_t v___x_172_; uint8_t v___x_173_; 
v___x_169_ = 23;
v___x_170_ = lean_uint32_shift_right(v___y_2_, v___x_169_);
v___x_171_ = 255;
v___x_172_ = lean_uint32_land(v___x_170_, v___x_171_);
v___x_173_ = lean_uint32_dec_eq(v___x_172_, v___x_171_);
if (v___x_173_ == 0)
{
v___y_162_ = v___x_173_;
goto v___jp_161_;
}
else
{
uint32_t v___x_174_; uint32_t v___x_175_; uint32_t v___x_176_; uint8_t v___x_177_; 
v___x_174_ = 8388607;
v___x_175_ = lean_uint32_land(v___y_2_, v___x_174_);
v___x_176_ = 0;
v___x_177_ = lean_uint32_dec_eq(v___x_175_, v___x_176_);
if (v___x_177_ == 0)
{
v___y_162_ = v___x_173_;
goto v___jp_161_;
}
else
{
goto v___jp_151_;
}
}
}
v___jp_178_:
{
if (v___y_179_ == 0)
{
goto v___jp_168_;
}
else
{
uint32_t v___x_180_; uint32_t v___x_181_; uint32_t v___x_182_; uint8_t v___x_183_; 
v___x_180_ = 4194304;
v___x_181_ = lean_uint32_land(v___y_1_, v___x_180_);
v___x_182_ = 0;
v___x_183_ = lean_uint32_dec_eq(v___x_181_, v___x_182_);
if (v___x_183_ == 0)
{
goto v___jp_168_;
}
else
{
uint32_t v___x_184_; 
v___x_184_ = lean_uint32_lor(v___y_1_, v___x_180_);
return v___x_184_;
}
}
}
v___jp_185_:
{
float v_result_188_; uint8_t v___x_189_; 
v_result_188_ = lean_float32_add(v___y_186_, v___y_187_);
v___x_189_ = lean_float32_beq(v_result_188_, v_result_188_);
if (v___x_189_ == 0)
{
uint32_t v___x_190_; uint32_t v___x_191_; uint32_t v___x_192_; uint32_t v___x_193_; uint8_t v___x_194_; 
v___x_190_ = 23;
v___x_191_ = lean_uint32_shift_right(v___y_1_, v___x_190_);
v___x_192_ = 255;
v___x_193_ = lean_uint32_land(v___x_191_, v___x_192_);
v___x_194_ = lean_uint32_dec_eq(v___x_193_, v___x_192_);
if (v___x_194_ == 0)
{
v___y_179_ = v___x_194_;
goto v___jp_178_;
}
else
{
uint32_t v___x_195_; uint32_t v___x_196_; uint32_t v___x_197_; uint8_t v___x_198_; 
v___x_195_ = 8388607;
v___x_196_ = lean_uint32_land(v___y_1_, v___x_195_);
v___x_197_ = 0;
v___x_198_ = lean_uint32_dec_eq(v___x_196_, v___x_197_);
if (v___x_198_ == 0)
{
v___y_179_ = v___x_194_;
goto v___jp_178_;
}
else
{
goto v___jp_168_;
}
}
}
else
{
uint32_t v___x_199_; 
v___x_199_ = lean_float32_to_bits(v_result_188_);
return v___x_199_;
}
}
v___jp_200_:
{
if (v___y_202_ == 0)
{
float v___x_203_; 
v___x_203_ = lean_float32_of_bits(v___y_2_);
v___y_186_ = v___y_201_;
v___y_187_ = v___x_203_;
goto v___jp_185_;
}
else
{
uint32_t v___x_204_; uint32_t v___x_205_; uint32_t v___x_206_; uint32_t v___x_207_; float v___x_208_; lean_object* v___x_209_; uint32_t v___x_210_; uint32_t v___x_211_; lean_object* v___x_212_; lean_object* v___x_213_; float v___x_214_; float v___x_215_; 
v___x_204_ = 8388607;
v___x_205_ = lean_uint32_land(v___y_2_, v___x_204_);
v___x_206_ = 8388608;
v___x_207_ = lean_uint32_lor(v___x_205_, v___x_206_);
v___x_208_ = lean_uint32_to_float32(v___x_207_);
v___x_209_ = lp_competition_R2W01b_scaleTable;
v___x_210_ = 23;
v___x_211_ = lean_uint32_shift_right(v___y_2_, v___x_210_);
v___x_212_ = lean_uint32_to_nat(v___x_211_);
v___x_213_ = lean_array_fget_borrowed(v___x_209_, v___x_212_);
lean_dec(v___x_212_);
v___x_214_ = lean_unbox_float32(v___x_213_);
v___x_215_ = lean_float32_mul(v___x_208_, v___x_214_);
v___y_186_ = v___y_201_;
v___y_187_ = v___x_215_;
goto v___jp_185_;
}
}
v___jp_216_:
{
uint32_t v___x_218_; uint32_t v_a_219_; uint32_t v___x_220_; uint32_t v___x_221_; uint32_t v___x_222_; uint8_t v___x_223_; 
v___x_218_ = 2147483647;
v_a_219_ = lean_uint32_land(v___y_2_, v___x_218_);
v___x_220_ = 201326591;
v___x_221_ = 1;
v___x_222_ = lean_uint32_sub(v_a_219_, v___x_221_);
v___x_223_ = lean_uint32_dec_le(v___x_220_, v___x_222_);
if (v___x_223_ == 0)
{
v___y_201_ = v___y_217_;
v___y_202_ = v___x_223_;
goto v___jp_200_;
}
else
{
uint32_t v___x_224_; uint8_t v___x_225_; 
v___x_224_ = 2139095040;
v___x_225_ = lean_uint32_dec_lt(v_a_219_, v___x_224_);
v___y_201_ = v___y_217_;
v___y_202_ = v___x_225_;
goto v___jp_200_;
}
}
v___jp_226_:
{
if (v___y_227_ == 0)
{
float v___x_228_; 
v___x_228_ = lean_float32_of_bits(v___y_1_);
v___y_217_ = v___x_228_;
goto v___jp_216_;
}
else
{
uint32_t v___x_229_; uint32_t v___x_230_; uint32_t v___x_231_; uint32_t v___x_232_; float v___x_233_; lean_object* v___x_234_; uint32_t v___x_235_; uint32_t v___x_236_; lean_object* v___x_237_; lean_object* v___x_238_; float v___x_239_; float v___x_240_; 
v___x_229_ = 8388607;
v___x_230_ = lean_uint32_land(v___y_1_, v___x_229_);
v___x_231_ = 8388608;
v___x_232_ = lean_uint32_lor(v___x_230_, v___x_231_);
v___x_233_ = lean_uint32_to_float32(v___x_232_);
v___x_234_ = lp_competition_R2W01b_scaleTable;
v___x_235_ = 23;
v___x_236_ = lean_uint32_shift_right(v___y_1_, v___x_235_);
v___x_237_ = lean_uint32_to_nat(v___x_236_);
v___x_238_ = lean_array_fget_borrowed(v___x_234_, v___x_237_);
lean_dec(v___x_237_);
v___x_239_ = lean_unbox_float32(v___x_238_);
v___x_240_ = lean_float32_mul(v___x_233_, v___x_239_);
v___y_217_ = v___x_240_;
goto v___jp_216_;
}
}
v___jp_241_:
{
lean_object* v___x_242_; lean_object* v___x_243_; lean_object* v___x_244_; uint32_t v___x_245_; 
v___x_242_ = lean_uint32_to_nat(v___y_1_);
v___x_243_ = lean_uint32_to_nat(v___y_2_);
v___x_244_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_242_, v___x_243_);
v___x_245_ = lean_uint32_of_nat(v___x_244_);
lean_dec(v___x_244_);
return v___x_245_;
}
v___jp_246_:
{
if (v___y_247_ == 0)
{
goto v___jp_241_;
}
else
{
uint32_t v___x_248_; uint32_t v___x_249_; 
v___x_248_ = 4194304;
v___x_249_ = lean_uint32_lor(v___y_2_, v___x_248_);
return v___x_249_;
}
}
v___jp_250_:
{
uint32_t v___x_251_; uint32_t v___x_252_; uint32_t v___x_253_; uint32_t v___x_254_; uint8_t v___x_255_; 
v___x_251_ = 23;
v___x_252_ = lean_uint32_shift_right(v___y_2_, v___x_251_);
v___x_253_ = 255;
v___x_254_ = lean_uint32_land(v___x_252_, v___x_253_);
v___x_255_ = lean_uint32_dec_eq(v___x_254_, v___x_253_);
if (v___x_255_ == 0)
{
v___y_247_ = v___x_255_;
goto v___jp_246_;
}
else
{
uint32_t v___x_256_; uint32_t v___x_257_; uint32_t v___x_258_; uint8_t v___x_259_; 
v___x_256_ = 8388607;
v___x_257_ = lean_uint32_land(v___y_2_, v___x_256_);
v___x_258_ = 0;
v___x_259_ = lean_uint32_dec_eq(v___x_257_, v___x_258_);
if (v___x_259_ == 0)
{
v___y_247_ = v___x_255_;
goto v___jp_246_;
}
else
{
goto v___jp_241_;
}
}
}
v___jp_260_:
{
if (v___y_261_ == 0)
{
goto v___jp_250_;
}
else
{
uint32_t v___x_262_; uint32_t v___x_263_; 
v___x_262_ = 4194304;
v___x_263_ = lean_uint32_lor(v___y_1_, v___x_262_);
return v___x_263_;
}
}
v___jp_264_:
{
uint32_t v___x_265_; uint32_t v___x_266_; uint32_t v___x_267_; uint32_t v___x_268_; uint8_t v___x_269_; 
v___x_265_ = 23;
v___x_266_ = lean_uint32_shift_right(v___y_1_, v___x_265_);
v___x_267_ = 255;
v___x_268_ = lean_uint32_land(v___x_266_, v___x_267_);
v___x_269_ = lean_uint32_dec_eq(v___x_268_, v___x_267_);
if (v___x_269_ == 0)
{
v___y_261_ = v___x_269_;
goto v___jp_260_;
}
else
{
uint32_t v___x_270_; uint32_t v___x_271_; uint32_t v___x_272_; uint8_t v___x_273_; 
v___x_270_ = 8388607;
v___x_271_ = lean_uint32_land(v___y_1_, v___x_270_);
v___x_272_ = 0;
v___x_273_ = lean_uint32_dec_eq(v___x_271_, v___x_272_);
if (v___x_273_ == 0)
{
v___y_261_ = v___x_269_;
goto v___jp_260_;
}
else
{
goto v___jp_250_;
}
}
}
v___jp_274_:
{
if (v___y_275_ == 0)
{
goto v___jp_264_;
}
else
{
uint32_t v___x_276_; uint32_t v___x_277_; uint32_t v___x_278_; uint8_t v___x_279_; 
v___x_276_ = 4194304;
v___x_277_ = lean_uint32_land(v___y_2_, v___x_276_);
v___x_278_ = 0;
v___x_279_ = lean_uint32_dec_eq(v___x_277_, v___x_278_);
if (v___x_279_ == 0)
{
goto v___jp_264_;
}
else
{
uint32_t v___x_280_; 
v___x_280_ = lean_uint32_lor(v___y_2_, v___x_276_);
return v___x_280_;
}
}
}
v___jp_281_:
{
uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint32_t v___x_285_; uint8_t v___x_286_; 
v___x_282_ = 23;
v___x_283_ = lean_uint32_shift_right(v___y_2_, v___x_282_);
v___x_284_ = 255;
v___x_285_ = lean_uint32_land(v___x_283_, v___x_284_);
v___x_286_ = lean_uint32_dec_eq(v___x_285_, v___x_284_);
if (v___x_286_ == 0)
{
v___y_275_ = v___x_286_;
goto v___jp_274_;
}
else
{
uint32_t v___x_287_; uint32_t v___x_288_; uint32_t v___x_289_; uint8_t v___x_290_; 
v___x_287_ = 8388607;
v___x_288_ = lean_uint32_land(v___y_2_, v___x_287_);
v___x_289_ = 0;
v___x_290_ = lean_uint32_dec_eq(v___x_288_, v___x_289_);
if (v___x_290_ == 0)
{
v___y_275_ = v___x_286_;
goto v___jp_274_;
}
else
{
goto v___jp_264_;
}
}
}
v___jp_291_:
{
if (v___y_292_ == 0)
{
goto v___jp_281_;
}
else
{
uint32_t v___x_293_; uint32_t v___x_294_; uint32_t v___x_295_; uint8_t v___x_296_; 
v___x_293_ = 4194304;
v___x_294_ = lean_uint32_land(v___y_1_, v___x_293_);
v___x_295_ = 0;
v___x_296_ = lean_uint32_dec_eq(v___x_294_, v___x_295_);
if (v___x_296_ == 0)
{
goto v___jp_281_;
}
else
{
uint32_t v___x_297_; 
v___x_297_ = lean_uint32_lor(v___y_1_, v___x_293_);
return v___x_297_;
}
}
}
v___jp_298_:
{
float v_result_301_; uint8_t v___x_302_; 
v_result_301_ = lean_float32_add(v___y_299_, v___y_300_);
v___x_302_ = lean_float32_beq(v_result_301_, v_result_301_);
if (v___x_302_ == 0)
{
uint32_t v___x_303_; uint32_t v___x_304_; uint32_t v___x_305_; uint32_t v___x_306_; uint8_t v___x_307_; 
v___x_303_ = 23;
v___x_304_ = lean_uint32_shift_right(v___y_1_, v___x_303_);
v___x_305_ = 255;
v___x_306_ = lean_uint32_land(v___x_304_, v___x_305_);
v___x_307_ = lean_uint32_dec_eq(v___x_306_, v___x_305_);
if (v___x_307_ == 0)
{
v___y_292_ = v___x_307_;
goto v___jp_291_;
}
else
{
uint32_t v___x_308_; uint32_t v___x_309_; uint32_t v___x_310_; uint8_t v___x_311_; 
v___x_308_ = 8388607;
v___x_309_ = lean_uint32_land(v___y_1_, v___x_308_);
v___x_310_ = 0;
v___x_311_ = lean_uint32_dec_eq(v___x_309_, v___x_310_);
if (v___x_311_ == 0)
{
v___y_292_ = v___x_307_;
goto v___jp_291_;
}
else
{
goto v___jp_281_;
}
}
}
else
{
uint32_t v___x_312_; 
v___x_312_ = lean_float32_to_bits(v_result_301_);
return v___x_312_;
}
}
v___jp_313_:
{
if (v___y_315_ == 0)
{
float v___x_316_; 
v___x_316_ = lean_float32_of_bits(v___y_2_);
v___y_299_ = v___y_314_;
v___y_300_ = v___x_316_;
goto v___jp_298_;
}
else
{
uint32_t v___x_317_; uint32_t v___x_318_; uint32_t v___x_319_; uint32_t v___x_320_; float v___x_321_; lean_object* v___x_322_; uint32_t v___x_323_; uint32_t v___x_324_; lean_object* v___x_325_; lean_object* v___x_326_; float v___x_327_; float v___x_328_; 
v___x_317_ = 8388607;
v___x_318_ = lean_uint32_land(v___y_2_, v___x_317_);
v___x_319_ = 8388608;
v___x_320_ = lean_uint32_lor(v___x_318_, v___x_319_);
v___x_321_ = lean_uint32_to_float32(v___x_320_);
v___x_322_ = lp_competition_R2W01b_scaleTable;
v___x_323_ = 23;
v___x_324_ = lean_uint32_shift_right(v___y_2_, v___x_323_);
v___x_325_ = lean_uint32_to_nat(v___x_324_);
v___x_326_ = lean_array_fget_borrowed(v___x_322_, v___x_325_);
lean_dec(v___x_325_);
v___x_327_ = lean_unbox_float32(v___x_326_);
v___x_328_ = lean_float32_mul(v___x_321_, v___x_327_);
v___y_299_ = v___y_314_;
v___y_300_ = v___x_328_;
goto v___jp_298_;
}
}
v___jp_329_:
{
uint32_t v___x_331_; uint32_t v_a_332_; uint32_t v___x_333_; uint32_t v___x_334_; uint32_t v___x_335_; uint8_t v___x_336_; 
v___x_331_ = 2147483647;
v_a_332_ = lean_uint32_land(v___y_2_, v___x_331_);
v___x_333_ = 201326591;
v___x_334_ = 1;
v___x_335_ = lean_uint32_sub(v_a_332_, v___x_334_);
v___x_336_ = lean_uint32_dec_le(v___x_333_, v___x_335_);
if (v___x_336_ == 0)
{
v___y_314_ = v___y_330_;
v___y_315_ = v___x_336_;
goto v___jp_313_;
}
else
{
uint32_t v___x_337_; uint8_t v___x_338_; 
v___x_337_ = 2139095040;
v___x_338_ = lean_uint32_dec_lt(v_a_332_, v___x_337_);
v___y_314_ = v___y_330_;
v___y_315_ = v___x_338_;
goto v___jp_313_;
}
}
v___jp_339_:
{
if (v___y_343_ == 0)
{
float v___x_344_; 
v___x_344_ = lean_float32_of_bits(v___y_1_);
v___y_330_ = v___x_344_;
goto v___jp_329_;
}
else
{
uint32_t v___x_345_; uint32_t v___x_346_; float v___x_347_; lean_object* v___x_348_; uint32_t v___x_349_; lean_object* v___x_350_; lean_object* v___x_351_; float v___x_352_; float v___x_353_; 
v___x_345_ = lean_uint32_land(v___y_1_, v___y_342_);
v___x_346_ = lean_uint32_lor(v___x_345_, v___y_341_);
v___x_347_ = lean_uint32_to_float32(v___x_346_);
v___x_348_ = lp_competition_R2W01b_scaleTable;
v___x_349_ = lean_uint32_shift_right(v___y_1_, v___y_340_);
v___x_350_ = lean_uint32_to_nat(v___x_349_);
v___x_351_ = lean_array_fget_borrowed(v___x_348_, v___x_350_);
lean_dec(v___x_350_);
v___x_352_ = lean_unbox_float32(v___x_351_);
v___x_353_ = lean_float32_mul(v___x_347_, v___x_352_);
v___y_330_ = v___x_353_;
goto v___jp_329_;
}
}
v___jp_354_:
{
uint32_t v_base_364_; uint32_t v___x_365_; uint32_t v___x_366_; uint32_t v___x_367_; uint32_t v_h_368_; uint64_t v___x_369_; uint32_t v___x_370_; uint64_t v___x_371_; uint64_t v___x_372_; uint64_t v___x_373_; uint64_t v___x_374_; uint64_t v___x_375_; uint64_t v___x_376_; uint64_t v___x_377_; uint64_t v___x_378_; uint64_t v___x_379_; uint64_t v_q_380_; uint32_t v___x_381_; uint32_t v___x_382_; uint64_t v___x_383_; uint64_t v___x_384_; uint32_t v___x_385_; uint32_t v_e_386_; uint32_t v___x_387_; uint32_t v___x_388_; uint8_t v___x_389_; 
v_base_364_ = lean_uint32_add(v___y_363_, v___y_357_);
v___x_365_ = 1;
v___x_366_ = lean_uint32_add(v_base_364_, v___x_365_);
v___x_367_ = lean_uint32_shift_right(v___y_359_, v___x_366_);
v_h_368_ = lean_uint32_add(v_base_364_, v___x_367_);
v___x_369_ = lean_uint32_to_uint64(v___y_359_);
v___x_370_ = lean_uint32_sub(v_h_368_, v___y_356_);
v___x_371_ = lean_uint32_to_uint64(v___x_370_);
v___x_372_ = 1ULL;
v___x_373_ = lean_uint64_sub(v___x_371_, v___x_372_);
v___x_374_ = lean_uint64_shift_left(v___x_372_, v___x_373_);
v___x_375_ = lean_uint64_add(v___x_369_, v___x_374_);
v___x_376_ = lean_uint64_sub(v___x_375_, v___x_372_);
v___x_377_ = lean_uint64_shift_right(v___x_369_, v___x_371_);
v___x_378_ = lean_uint64_land(v___x_377_, v___x_372_);
v___x_379_ = lean_uint64_add(v___x_376_, v___x_378_);
v_q_380_ = lean_uint64_shift_right(v___x_379_, v___x_371_);
v___x_381_ = lean_uint32_add(v_h_368_, v___y_358_);
v___x_382_ = lean_uint32_sub(v___x_381_, v___y_356_);
v___x_383_ = 24ULL;
v___x_384_ = lean_uint64_shift_right(v_q_380_, v___x_383_);
v___x_385_ = lean_uint64_to_uint32(v___x_384_);
v_e_386_ = lean_uint32_add(v___x_382_, v___x_385_);
v___x_387_ = lean_uint32_sub(v_e_386_, v___x_365_);
v___x_388_ = 253;
v___x_389_ = lean_uint32_dec_le(v___x_387_, v___x_388_);
if (v___x_389_ == 0)
{
uint32_t v___x_390_; uint32_t v_a_391_; uint32_t v___x_392_; uint32_t v___x_393_; uint8_t v___x_394_; 
v___x_390_ = 2147483647;
v_a_391_ = lean_uint32_land(v___y_1_, v___x_390_);
v___x_392_ = 201326591;
v___x_393_ = lean_uint32_sub(v_a_391_, v___x_365_);
v___x_394_ = lean_uint32_dec_le(v___x_392_, v___x_393_);
if (v___x_394_ == 0)
{
v___y_340_ = v___y_356_;
v___y_341_ = v___y_355_;
v___y_342_ = v___y_361_;
v___y_343_ = v___x_394_;
goto v___jp_339_;
}
else
{
uint32_t v___x_395_; uint8_t v___x_396_; 
v___x_395_ = 2139095040;
v___x_396_ = lean_uint32_dec_lt(v_a_391_, v___x_395_);
v___y_340_ = v___y_356_;
v___y_341_ = v___y_355_;
v___y_342_ = v___y_361_;
v___y_343_ = v___x_396_;
goto v___jp_339_;
}
}
else
{
uint32_t v___x_397_; uint8_t v___x_398_; uint32_t v___x_399_; uint32_t v___x_400_; 
v___x_397_ = 2147483648;
v___x_398_ = lean_uint32_dec_le(v___x_397_, v___y_360_);
v___x_399_ = lean_uint64_to_uint32(v_q_380_);
v___x_400_ = lean_uint32_land(v___x_399_, v___y_361_);
if (v___x_398_ == 0)
{
uint32_t v___x_401_; 
v___x_401_ = 0;
v___y_4_ = v___y_356_;
v___y_5_ = v_e_386_;
v___y_6_ = v___x_400_;
v___y_7_ = v___y_361_;
v___y_8_ = v___y_362_;
v___y_9_ = v___x_401_;
goto v___jp_3_;
}
else
{
v___y_4_ = v___y_356_;
v___y_5_ = v_e_386_;
v___y_6_ = v___x_400_;
v___y_7_ = v___y_361_;
v___y_8_ = v___y_362_;
v___y_9_ = v___x_397_;
goto v___jp_3_;
}
}
}
v___jp_402_:
{
uint32_t v___x_410_; uint32_t v___x_411_; uint32_t v___x_412_; uint32_t v___x_413_; uint32_t v_left_414_; uint32_t v___x_415_; uint32_t v_right_416_; 
v___x_410_ = 8388607;
v___x_411_ = lean_uint32_land(v___y_407_, v___x_410_);
v___x_412_ = 8388608;
v___x_413_ = lean_uint32_lor(v___x_411_, v___x_412_);
v_left_414_ = lean_uint32_shift_left(v___x_413_, v___y_405_);
v___x_415_ = lean_uint32_land(v___y_404_, v___x_410_);
v_right_416_ = lean_uint32_lor(v___x_415_, v___x_412_);
if (v___y_409_ == 0)
{
uint32_t v___x_417_; uint32_t v___x_418_; 
v___x_417_ = lean_uint32_sub(v_left_414_, v_right_416_);
v___x_418_ = 22;
v___y_355_ = v___x_412_;
v___y_356_ = v___y_403_;
v___y_357_ = v___y_405_;
v___y_358_ = v___y_406_;
v___y_359_ = v___x_417_;
v___y_360_ = v___y_407_;
v___y_361_ = v___x_410_;
v___y_362_ = v___y_408_;
v___y_363_ = v___x_418_;
goto v___jp_354_;
}
else
{
uint32_t v___x_419_; 
v___x_419_ = lean_uint32_add(v_left_414_, v_right_416_);
v___y_355_ = v___x_412_;
v___y_356_ = v___y_403_;
v___y_357_ = v___y_405_;
v___y_358_ = v___y_406_;
v___y_359_ = v___x_419_;
v___y_360_ = v___y_407_;
v___y_361_ = v___x_410_;
v___y_362_ = v___y_408_;
v___y_363_ = v___y_403_;
goto v___jp_354_;
}
}
v___jp_420_:
{
uint32_t v___x_424_; uint32_t v___x_425_; uint32_t v___x_426_; uint32_t v___x_427_; uint32_t v___x_428_; uint32_t v___x_429_; uint32_t v_d_430_; uint32_t v___x_431_; uint8_t v___x_432_; uint8_t v___x_433_; 
v___x_424_ = 23;
v___x_425_ = lean_uint32_shift_right(v___y_422_, v___x_424_);
v___x_426_ = 255;
v___x_427_ = lean_uint32_land(v___x_425_, v___x_426_);
v___x_428_ = lean_uint32_shift_right(v___y_423_, v___x_424_);
v___x_429_ = lean_uint32_land(v___x_428_, v___x_426_);
v_d_430_ = lean_uint32_sub(v___x_427_, v___x_429_);
v___x_431_ = 2147483648;
v___x_432_ = lean_uint32_dec_le(v___x_431_, v___y_1_);
v___x_433_ = lean_uint32_dec_le(v___x_431_, v___y_2_);
if (v___x_432_ == 0)
{
if (v___x_433_ == 0)
{
v___y_403_ = v___x_424_;
v___y_404_ = v___y_423_;
v___y_405_ = v_d_430_;
v___y_406_ = v___x_429_;
v___y_407_ = v___y_422_;
v___y_408_ = v___x_426_;
v___y_409_ = v___y_421_;
goto v___jp_402_;
}
else
{
v___y_403_ = v___x_424_;
v___y_404_ = v___y_423_;
v___y_405_ = v_d_430_;
v___y_406_ = v___x_429_;
v___y_407_ = v___y_422_;
v___y_408_ = v___x_426_;
v___y_409_ = v___x_432_;
goto v___jp_402_;
}
}
else
{
v___y_403_ = v___x_424_;
v___y_404_ = v___y_423_;
v___y_405_ = v_d_430_;
v___y_406_ = v___x_429_;
v___y_407_ = v___y_422_;
v___y_408_ = v___x_426_;
v___y_409_ = v___x_433_;
goto v___jp_402_;
}
}
v___jp_434_:
{
uint32_t v___x_437_; uint32_t v___x_438_; uint32_t v___x_439_; uint32_t v___x_440_; uint32_t v___x_441_; uint32_t v___x_442_; uint8_t v___x_443_; 
v___x_437_ = 23;
v___x_438_ = lean_uint32_shift_right(v___y_1_, v___x_437_);
v___x_439_ = 255;
v___x_440_ = lean_uint32_land(v___x_438_, v___x_439_);
v___x_441_ = lean_uint32_shift_right(v___y_2_, v___x_437_);
v___x_442_ = lean_uint32_land(v___x_441_, v___x_439_);
v___x_443_ = lean_uint32_dec_lt(v___x_440_, v___x_442_);
if (v___x_443_ == 0)
{
v___y_421_ = v___y_435_;
v___y_422_ = v___y_436_;
v___y_423_ = v___y_2_;
goto v___jp_420_;
}
else
{
v___y_421_ = v___y_435_;
v___y_422_ = v___y_436_;
v___y_423_ = v___y_1_;
goto v___jp_420_;
}
}
v___jp_444_:
{
uint32_t v___x_446_; uint32_t v___x_447_; uint32_t v___x_448_; uint32_t v___x_449_; uint32_t v___x_450_; uint32_t v___x_451_; uint8_t v___x_452_; 
v___x_446_ = 23;
v___x_447_ = lean_uint32_shift_right(v___y_1_, v___x_446_);
v___x_448_ = 255;
v___x_449_ = lean_uint32_land(v___x_447_, v___x_448_);
v___x_450_ = lean_uint32_shift_right(v___y_2_, v___x_446_);
v___x_451_ = lean_uint32_land(v___x_450_, v___x_448_);
v___x_452_ = lean_uint32_dec_lt(v___x_449_, v___x_451_);
if (v___x_452_ == 0)
{
v___y_435_ = v___y_445_;
v___y_436_ = v___y_1_;
goto v___jp_434_;
}
else
{
v___y_435_ = v___y_445_;
v___y_436_ = v___y_2_;
goto v___jp_434_;
}
}
v___jp_453_:
{
if (v___y_454_ == 0)
{
uint32_t v___x_455_; uint32_t v_a_456_; uint32_t v___x_457_; uint32_t v___x_458_; uint32_t v___x_459_; uint8_t v___x_460_; 
v___x_455_ = 2147483647;
v_a_456_ = lean_uint32_land(v___y_1_, v___x_455_);
v___x_457_ = 201326591;
v___x_458_ = 1;
v___x_459_ = lean_uint32_sub(v_a_456_, v___x_458_);
v___x_460_ = lean_uint32_dec_le(v___x_457_, v___x_459_);
if (v___x_460_ == 0)
{
v___y_227_ = v___x_460_;
goto v___jp_226_;
}
else
{
uint32_t v___x_461_; uint8_t v___x_462_; 
v___x_461_ = 2139095040;
v___x_462_ = lean_uint32_dec_lt(v_a_456_, v___x_461_);
v___y_227_ = v___x_462_;
goto v___jp_226_;
}
}
else
{
v___y_445_ = v___y_454_;
goto v___jp_444_;
}
}
v___jp_463_:
{
uint32_t v___x_469_; uint32_t v___x_470_; uint32_t v___x_471_; uint8_t v___x_472_; 
v___x_469_ = lean_uint32_shift_right(v___y_468_, v___y_467_);
v___x_470_ = lean_uint32_land(v___x_469_, v___y_466_);
v___x_471_ = lean_uint32_sub(v___y_465_, v___x_470_);
v___x_472_ = lean_uint32_dec_le(v___y_464_, v___x_471_);
v___y_454_ = v___x_472_;
goto v___jp_453_;
}
v___jp_473_:
{
uint32_t v___x_476_; uint32_t v___x_477_; uint32_t v___x_478_; uint32_t v___x_479_; uint32_t v___x_480_; uint32_t v___x_481_; uint32_t v___x_482_; uint32_t v___x_483_; uint8_t v___x_484_; 
v___x_476_ = 23;
v___x_477_ = lean_uint32_shift_right(v___y_475_, v___x_476_);
v___x_478_ = 255;
v___x_479_ = lean_uint32_land(v___x_477_, v___x_478_);
v___x_480_ = lean_uint32_shift_right(v___y_1_, v___x_476_);
v___x_481_ = lean_uint32_land(v___x_480_, v___x_478_);
v___x_482_ = lean_uint32_shift_right(v___y_2_, v___x_476_);
v___x_483_ = lean_uint32_land(v___x_482_, v___x_478_);
v___x_484_ = lean_uint32_dec_lt(v___x_481_, v___x_483_);
if (v___x_484_ == 0)
{
v___y_464_ = v___y_474_;
v___y_465_ = v___x_479_;
v___y_466_ = v___x_478_;
v___y_467_ = v___x_476_;
v___y_468_ = v___y_2_;
goto v___jp_463_;
}
else
{
v___y_464_ = v___y_474_;
v___y_465_ = v___x_479_;
v___y_466_ = v___x_478_;
v___y_467_ = v___x_476_;
v___y_468_ = v___y_1_;
goto v___jp_463_;
}
}
v___jp_485_:
{
if (v___y_486_ == 0)
{
uint32_t v___x_487_; uint32_t v___x_488_; uint32_t v___x_489_; uint32_t v___x_490_; uint32_t v___x_491_; uint32_t v___x_492_; uint32_t v___x_493_; uint8_t v___x_494_; 
v___x_487_ = 2;
v___x_488_ = 23;
v___x_489_ = lean_uint32_shift_right(v___y_1_, v___x_488_);
v___x_490_ = 255;
v___x_491_ = lean_uint32_land(v___x_489_, v___x_490_);
v___x_492_ = lean_uint32_shift_right(v___y_2_, v___x_488_);
v___x_493_ = lean_uint32_land(v___x_492_, v___x_490_);
v___x_494_ = lean_uint32_dec_lt(v___x_491_, v___x_493_);
if (v___x_494_ == 0)
{
v___y_474_ = v___x_487_;
v___y_475_ = v___y_1_;
goto v___jp_473_;
}
else
{
v___y_474_ = v___x_487_;
v___y_475_ = v___y_2_;
goto v___jp_473_;
}
}
else
{
v___y_445_ = v___y_486_;
goto v___jp_444_;
}
}
v___jp_495_:
{
uint32_t v___x_500_; uint32_t v___x_501_; uint32_t v___x_502_; uint32_t v___x_503_; uint8_t v___x_504_; 
v___x_500_ = lean_uint32_shift_right(v___y_499_, v___y_496_);
v___x_501_ = lean_uint32_land(v___x_500_, v___y_497_);
v___x_502_ = lean_uint32_sub(v___y_498_, v___x_501_);
v___x_503_ = 7;
v___x_504_ = lean_uint32_dec_le(v___x_502_, v___x_503_);
if (v___x_504_ == 0)
{
v___y_454_ = v___x_504_;
goto v___jp_453_;
}
else
{
uint32_t v___x_505_; uint8_t v___x_506_; uint8_t v___x_507_; 
v___x_505_ = 2147483648;
v___x_506_ = lean_uint32_dec_le(v___x_505_, v___y_1_);
v___x_507_ = lean_uint32_dec_le(v___x_505_, v___y_2_);
if (v___x_506_ == 0)
{
if (v___x_507_ == 0)
{
v___y_454_ = v___x_504_;
goto v___jp_453_;
}
else
{
v___y_486_ = v___x_506_;
goto v___jp_485_;
}
}
else
{
v___y_486_ = v___x_507_;
goto v___jp_485_;
}
}
}
v___jp_508_:
{
uint32_t v___x_510_; uint32_t v___x_511_; uint32_t v___x_512_; uint32_t v___x_513_; uint32_t v___x_514_; uint32_t v___x_515_; uint32_t v___x_516_; uint32_t v___x_517_; uint8_t v___x_518_; 
v___x_510_ = 23;
v___x_511_ = lean_uint32_shift_right(v___y_509_, v___x_510_);
v___x_512_ = 255;
v___x_513_ = lean_uint32_land(v___x_511_, v___x_512_);
v___x_514_ = lean_uint32_shift_right(v___y_1_, v___x_510_);
v___x_515_ = lean_uint32_land(v___x_514_, v___x_512_);
v___x_516_ = lean_uint32_shift_right(v___y_2_, v___x_510_);
v___x_517_ = lean_uint32_land(v___x_516_, v___x_512_);
v___x_518_ = lean_uint32_dec_lt(v___x_515_, v___x_517_);
if (v___x_518_ == 0)
{
v___y_496_ = v___x_510_;
v___y_497_ = v___x_512_;
v___y_498_ = v___x_513_;
v___y_499_ = v___y_2_;
goto v___jp_495_;
}
else
{
v___y_496_ = v___x_510_;
v___y_497_ = v___x_512_;
v___y_498_ = v___x_513_;
v___y_499_ = v___y_1_;
goto v___jp_495_;
}
}
v___jp_519_:
{
if (v___y_520_ == 0)
{
uint32_t v___x_521_; uint32_t v_a_522_; uint32_t v___x_523_; uint32_t v___x_524_; uint32_t v___x_525_; uint8_t v___x_526_; 
v___x_521_ = 2147483647;
v_a_522_ = lean_uint32_land(v___y_1_, v___x_521_);
v___x_523_ = 201326591;
v___x_524_ = 1;
v___x_525_ = lean_uint32_sub(v_a_522_, v___x_524_);
v___x_526_ = lean_uint32_dec_le(v___x_523_, v___x_525_);
if (v___x_526_ == 0)
{
v___y_114_ = v___x_526_;
goto v___jp_113_;
}
else
{
uint32_t v___x_527_; uint8_t v___x_528_; 
v___x_527_ = 2139095040;
v___x_528_ = lean_uint32_dec_lt(v_a_522_, v___x_527_);
v___y_114_ = v___x_528_;
goto v___jp_113_;
}
}
else
{
uint32_t v___x_529_; uint32_t v___x_530_; uint32_t v___x_531_; uint32_t v___x_532_; uint32_t v___x_533_; uint32_t v___x_534_; uint8_t v___x_535_; 
v___x_529_ = 23;
v___x_530_ = lean_uint32_shift_right(v___y_1_, v___x_529_);
v___x_531_ = 255;
v___x_532_ = lean_uint32_land(v___x_530_, v___x_531_);
v___x_533_ = lean_uint32_shift_right(v___y_2_, v___x_529_);
v___x_534_ = lean_uint32_land(v___x_533_, v___x_531_);
v___x_535_ = lean_uint32_dec_lt(v___x_532_, v___x_534_);
if (v___x_535_ == 0)
{
v___y_509_ = v___y_1_;
goto v___jp_508_;
}
else
{
v___y_509_ = v___y_2_;
goto v___jp_508_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_548_, lean_object* v___y_549_){
_start:
{
uint32_t v___y_7923__boxed_550_; uint32_t v___y_7924__boxed_551_; uint32_t v_res_552_; lean_object* v_r_553_; 
v___y_7923__boxed_550_ = lean_unbox_uint32(v___y_548_);
lean_dec(v___y_548_);
v___y_7924__boxed_551_ = lean_unbox_uint32(v___y_549_);
lean_dec(v___y_549_);
v_res_552_ = lp_competition_main___lam__0(v___y_7923__boxed_550_, v___y_7924__boxed_551_);
v_r_553_ = lean_box_uint32(v_res_552_);
return v_r_553_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_554_, uint32_t v___y_555_){
_start:
{
uint32_t v___y_557_; uint32_t v___y_561_; uint32_t v___y_565_; uint32_t v___y_566_; uint32_t v___y_567_; uint8_t v___y_571_; uint64_t v___y_572_; uint32_t v___y_573_; uint64_t v___y_574_; uint32_t v___y_586_; uint32_t v___y_587_; uint32_t v___y_588_; uint64_t v___y_592_; uint8_t v___y_593_; uint32_t v___y_594_; uint64_t v___y_595_; uint8_t v___y_607_; uint8_t v___y_623_; uint8_t v___y_637_; uint8_t v___y_654_; float v___y_661_; float v___y_662_; float v___y_676_; uint8_t v___y_677_; float v___y_692_; uint32_t v___x_701_; uint32_t v___x_702_; uint8_t v___y_704_; uint32_t v___x_716_; uint32_t v___y_718_; uint32_t v___y_719_; uint32_t v___y_720_; uint32_t v___y_721_; uint8_t v___y_728_; uint32_t v___y_729_; uint32_t v___y_730_; uint32_t v___y_731_; uint8_t v___y_735_; uint64_t v___y_736_; uint32_t v___y_737_; uint64_t v___y_738_; uint64_t v___y_739_; uint8_t v___y_749_; uint8_t v___y_750_; uint64_t v___y_751_; uint64_t v___y_752_; uint32_t v___y_753_; uint64_t v___y_754_; uint8_t v___y_761_; uint64_t v___y_762_; uint32_t v___y_763_; uint64_t v___y_764_; uint64_t v___y_765_; uint64_t v___y_771_; uint64_t v___y_772_; uint8_t v___y_773_; uint64_t v___y_774_; uint32_t v___y_775_; uint64_t v___y_776_; uint64_t v___y_831_; uint8_t v___y_832_; uint64_t v___y_833_; uint64_t v___y_834_; uint32_t v___y_835_; uint64_t v___y_836_; uint64_t v___y_837_; uint64_t v___y_843_; uint64_t v___y_844_; uint64_t v___y_845_; uint64_t v___y_846_; uint8_t v___y_847_; uint64_t v___y_848_; uint32_t v___y_849_; uint64_t v___y_850_; uint64_t v___y_851_; uint64_t v___y_856_; uint64_t v___y_857_; uint8_t v___y_858_; uint64_t v___y_859_; uint64_t v___y_860_; uint32_t v___y_861_; uint64_t v___y_862_; uint64_t v___y_867_; uint64_t v___y_868_; uint64_t v___y_869_; uint8_t v___y_870_; uint64_t v___y_871_; uint32_t v___y_872_; uint64_t v___y_873_; uint64_t v___y_874_; uint64_t v___y_875_; uint64_t v___y_880_; uint8_t v___y_881_; uint64_t v___y_882_; uint64_t v___y_883_; uint32_t v___y_884_; uint64_t v___y_885_; uint64_t v___y_886_; uint64_t v___y_891_; uint64_t v___y_892_; uint64_t v___y_893_; uint8_t v___y_894_; uint64_t v___y_895_; uint32_t v___y_896_; uint64_t v___y_897_; uint64_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_904_; uint64_t v___y_905_; uint8_t v___y_906_; uint64_t v___y_907_; uint64_t v___y_908_; uint32_t v___y_909_; uint64_t v___y_910_; uint64_t v___y_915_; uint64_t v___y_916_; uint64_t v___y_917_; uint8_t v___y_918_; uint64_t v___y_919_; uint64_t v___y_920_; uint32_t v___y_921_; uint64_t v___y_922_; uint64_t v___y_923_; uint64_t v___y_928_; uint64_t v___y_929_; uint8_t v___y_930_; uint64_t v___y_931_; uint64_t v___y_932_; uint32_t v___y_933_; uint64_t v___y_934_; uint64_t v___y_939_; uint64_t v___y_940_; uint8_t v___y_941_; uint64_t v___y_942_; uint32_t v___y_943_; uint64_t v___y_944_; uint64_t v___y_945_; uint64_t v___y_949_; uint64_t v___y_950_; uint8_t v___y_951_; uint32_t v___y_952_; uint64_t v___y_961_; uint8_t v___y_962_; uint64_t v___y_963_; uint32_t v___y_964_; uint64_t v___y_965_; uint64_t v___y_966_; uint32_t v_ex_999_; uint32_t v___x_1000_; uint32_t v_ey_1001_; uint64_t v___y_1003_; uint8_t v___y_1004_; uint64_t v___y_1005_; uint32_t v___y_1006_; uint64_t v___y_1007_; uint8_t v___y_1014_; uint64_t v___y_1015_; uint32_t v___y_1016_; uint64_t v___y_1017_; uint8_t v___y_1024_; uint32_t v___y_1025_; uint32_t v___y_1026_; uint64_t v___y_1027_; uint8_t v___y_1035_; uint32_t v___x_1045_; uint32_t v___x_1046_; uint8_t v___x_1047_; uint8_t v___y_1049_; uint8_t v___y_1050_; uint8_t v___y_1052_; uint8_t v___y_1053_; uint8_t v___y_1054_; uint8_t v___y_1056_; uint8_t v___y_1057_; uint8_t v___y_1063_; 
v___x_701_ = 23;
v___x_702_ = lean_uint32_shift_right(v___y_554_, v___x_701_);
v___x_716_ = 255;
v_ex_999_ = lean_uint32_land(v___x_702_, v___x_716_);
v___x_1000_ = lean_uint32_shift_right(v___y_555_, v___x_701_);
v_ey_1001_ = lean_uint32_land(v___x_1000_, v___x_716_);
v___x_1045_ = lean_uint32_add(v_ex_999_, v_ey_1001_);
v___x_1046_ = 128;
v___x_1047_ = lean_uint32_dec_lt(v___x_1045_, v___x_1046_);
if (v___x_1047_ == 0)
{
uint32_t v___x_1072_; uint32_t v_a_1073_; uint32_t v___x_1074_; uint32_t v___x_1075_; uint32_t v___x_1076_; uint8_t v___x_1077_; 
v___x_1072_ = 2147483647;
v_a_1073_ = lean_uint32_land(v___y_554_, v___x_1072_);
v___x_1074_ = 201326591;
v___x_1075_ = 1;
v___x_1076_ = lean_uint32_sub(v_a_1073_, v___x_1075_);
v___x_1077_ = lean_uint32_dec_le(v___x_1074_, v___x_1076_);
if (v___x_1077_ == 0)
{
v___y_704_ = v___x_1077_;
goto v___jp_703_;
}
else
{
uint32_t v___x_1078_; uint8_t v___x_1079_; 
v___x_1078_ = 2139095040;
v___x_1079_ = lean_uint32_dec_lt(v_a_1073_, v___x_1078_);
v___y_704_ = v___x_1079_;
goto v___jp_703_;
}
}
else
{
uint32_t v___x_1080_; uint32_t v___x_1081_; uint32_t v___x_1082_; uint8_t v___x_1083_; 
v___x_1080_ = 4278190080;
v___x_1081_ = 1;
v___x_1082_ = lean_uint32_shift_left(v___y_554_, v___x_1081_);
v___x_1083_ = lean_uint32_dec_le(v___x_1080_, v___x_1082_);
if (v___x_1083_ == 0)
{
uint32_t v___x_1084_; uint8_t v___x_1085_; 
v___x_1084_ = lean_uint32_shift_left(v___y_555_, v___x_1081_);
v___x_1085_ = lean_uint32_dec_le(v___x_1080_, v___x_1084_);
v___y_1063_ = v___x_1085_;
goto v___jp_1062_;
}
else
{
v___y_1063_ = v___x_1083_;
goto v___jp_1062_;
}
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
uint32_t v___x_562_; uint32_t v___x_563_; 
v___x_562_ = 8388608;
v___x_563_ = lean_uint32_lor(v___y_561_, v___x_562_);
return v___x_563_;
}
v___jp_564_:
{
uint32_t v___x_568_; uint32_t v___x_569_; 
v___x_568_ = lean_uint32_land(v___y_566_, v___y_565_);
v___x_569_ = lean_uint32_lor(v___y_567_, v___x_568_);
return v___x_569_;
}
v___jp_570_:
{
uint8_t v___x_575_; 
v___x_575_ = lean_uint64_dec_eq(v___y_574_, v___y_572_);
if (v___x_575_ == 0)
{
uint64_t v___x_576_; uint8_t v___x_577_; 
v___x_576_ = 8388608ULL;
v___x_577_ = lean_uint64_dec_eq(v___y_574_, v___x_576_);
if (v___x_577_ == 0)
{
uint32_t v___x_578_; 
v___x_578_ = lean_uint64_to_uint32(v___y_574_);
if (v___y_571_ == 0)
{
uint32_t v___x_579_; 
v___x_579_ = 0;
v___y_565_ = v___y_573_;
v___y_566_ = v___x_578_;
v___y_567_ = v___x_579_;
goto v___jp_564_;
}
else
{
uint32_t v___x_580_; 
v___x_580_ = 2147483648;
v___y_565_ = v___y_573_;
v___y_566_ = v___x_578_;
v___y_567_ = v___x_580_;
goto v___jp_564_;
}
}
else
{
if (v___y_571_ == 0)
{
uint32_t v___x_581_; 
v___x_581_ = 0;
v___y_561_ = v___x_581_;
goto v___jp_560_;
}
else
{
uint32_t v___x_582_; 
v___x_582_ = 2147483648;
v___y_561_ = v___x_582_;
goto v___jp_560_;
}
}
}
else
{
if (v___y_571_ == 0)
{
uint32_t v___x_583_; 
v___x_583_ = 0;
return v___x_583_;
}
else
{
uint32_t v___x_584_; 
v___x_584_ = 2147483648;
return v___x_584_;
}
}
}
v___jp_585_:
{
uint32_t v___x_589_; uint32_t v___x_590_; 
v___x_589_ = lean_uint32_land(v___y_587_, v___y_586_);
v___x_590_ = lean_uint32_lor(v___y_588_, v___x_589_);
return v___x_590_;
}
v___jp_591_:
{
uint8_t v___x_596_; 
v___x_596_ = lean_uint64_dec_eq(v___y_595_, v___y_592_);
if (v___x_596_ == 0)
{
uint64_t v___x_597_; uint8_t v___x_598_; 
v___x_597_ = 8388608ULL;
v___x_598_ = lean_uint64_dec_eq(v___y_595_, v___x_597_);
if (v___x_598_ == 0)
{
uint32_t v___x_599_; 
v___x_599_ = lean_uint64_to_uint32(v___y_595_);
if (v___y_593_ == 0)
{
uint32_t v___x_600_; 
v___x_600_ = 0;
v___y_586_ = v___y_594_;
v___y_587_ = v___x_599_;
v___y_588_ = v___x_600_;
goto v___jp_585_;
}
else
{
uint32_t v___x_601_; 
v___x_601_ = 2147483648;
v___y_586_ = v___y_594_;
v___y_587_ = v___x_599_;
v___y_588_ = v___x_601_;
goto v___jp_585_;
}
}
else
{
if (v___y_593_ == 0)
{
uint32_t v___x_602_; 
v___x_602_ = 0;
v___y_557_ = v___x_602_;
goto v___jp_556_;
}
else
{
uint32_t v___x_603_; 
v___x_603_ = 2147483648;
v___y_557_ = v___x_603_;
goto v___jp_556_;
}
}
}
else
{
if (v___y_593_ == 0)
{
uint32_t v___x_604_; 
v___x_604_ = 0;
return v___x_604_;
}
else
{
uint32_t v___x_605_; 
v___x_605_ = 2147483648;
return v___x_605_;
}
}
}
v___jp_606_:
{
if (v___y_607_ == 0)
{
uint32_t v___x_608_; 
v___x_608_ = lp_competition_Submission_FastMul_mul(v___y_554_, v___y_555_);
return v___x_608_;
}
else
{
uint32_t v___x_609_; uint32_t v___x_610_; 
v___x_609_ = 4194304;
v___x_610_ = lean_uint32_lor(v___y_555_, v___x_609_);
return v___x_610_;
}
}
v___jp_611_:
{
uint32_t v___x_612_; uint32_t v___x_613_; uint32_t v___x_614_; uint32_t v___x_615_; uint8_t v___x_616_; 
v___x_612_ = 23;
v___x_613_ = lean_uint32_shift_right(v___y_555_, v___x_612_);
v___x_614_ = 255;
v___x_615_ = lean_uint32_land(v___x_613_, v___x_614_);
v___x_616_ = lean_uint32_dec_eq(v___x_615_, v___x_614_);
if (v___x_616_ == 0)
{
v___y_607_ = v___x_616_;
goto v___jp_606_;
}
else
{
uint32_t v___x_617_; uint32_t v___x_618_; uint32_t v___x_619_; uint8_t v___x_620_; 
v___x_617_ = 8388607;
v___x_618_ = lean_uint32_land(v___y_555_, v___x_617_);
v___x_619_ = 0;
v___x_620_ = lean_uint32_dec_eq(v___x_618_, v___x_619_);
if (v___x_620_ == 0)
{
v___y_607_ = v___x_616_;
goto v___jp_606_;
}
else
{
uint32_t v___x_621_; 
v___x_621_ = lp_competition_Submission_FastMul_mul(v___y_554_, v___y_555_);
return v___x_621_;
}
}
}
v___jp_622_:
{
if (v___y_623_ == 0)
{
goto v___jp_611_;
}
else
{
uint32_t v___x_624_; uint32_t v___x_625_; 
v___x_624_ = 4194304;
v___x_625_ = lean_uint32_lor(v___y_554_, v___x_624_);
return v___x_625_;
}
}
v___jp_626_:
{
uint32_t v___x_627_; uint32_t v___x_628_; uint32_t v___x_629_; uint32_t v___x_630_; uint8_t v___x_631_; 
v___x_627_ = 23;
v___x_628_ = lean_uint32_shift_right(v___y_554_, v___x_627_);
v___x_629_ = 255;
v___x_630_ = lean_uint32_land(v___x_628_, v___x_629_);
v___x_631_ = lean_uint32_dec_eq(v___x_630_, v___x_629_);
if (v___x_631_ == 0)
{
v___y_623_ = v___x_631_;
goto v___jp_622_;
}
else
{
uint32_t v___x_632_; uint32_t v___x_633_; uint32_t v___x_634_; uint8_t v___x_635_; 
v___x_632_ = 8388607;
v___x_633_ = lean_uint32_land(v___y_554_, v___x_632_);
v___x_634_ = 0;
v___x_635_ = lean_uint32_dec_eq(v___x_633_, v___x_634_);
if (v___x_635_ == 0)
{
v___y_623_ = v___x_631_;
goto v___jp_622_;
}
else
{
goto v___jp_611_;
}
}
}
v___jp_636_:
{
if (v___y_637_ == 0)
{
goto v___jp_626_;
}
else
{
uint32_t v___x_638_; uint32_t v___x_639_; uint32_t v___x_640_; uint8_t v___x_641_; 
v___x_638_ = 4194304;
v___x_639_ = lean_uint32_land(v___y_555_, v___x_638_);
v___x_640_ = 0;
v___x_641_ = lean_uint32_dec_eq(v___x_639_, v___x_640_);
if (v___x_641_ == 0)
{
goto v___jp_626_;
}
else
{
uint32_t v___x_642_; 
v___x_642_ = lean_uint32_lor(v___y_555_, v___x_638_);
return v___x_642_;
}
}
}
v___jp_643_:
{
uint32_t v___x_644_; uint32_t v___x_645_; uint32_t v___x_646_; uint32_t v___x_647_; uint8_t v___x_648_; 
v___x_644_ = 23;
v___x_645_ = lean_uint32_shift_right(v___y_555_, v___x_644_);
v___x_646_ = 255;
v___x_647_ = lean_uint32_land(v___x_645_, v___x_646_);
v___x_648_ = lean_uint32_dec_eq(v___x_647_, v___x_646_);
if (v___x_648_ == 0)
{
v___y_637_ = v___x_648_;
goto v___jp_636_;
}
else
{
uint32_t v___x_649_; uint32_t v___x_650_; uint32_t v___x_651_; uint8_t v___x_652_; 
v___x_649_ = 8388607;
v___x_650_ = lean_uint32_land(v___y_555_, v___x_649_);
v___x_651_ = 0;
v___x_652_ = lean_uint32_dec_eq(v___x_650_, v___x_651_);
if (v___x_652_ == 0)
{
v___y_637_ = v___x_648_;
goto v___jp_636_;
}
else
{
goto v___jp_626_;
}
}
}
v___jp_653_:
{
if (v___y_654_ == 0)
{
goto v___jp_643_;
}
else
{
uint32_t v___x_655_; uint32_t v___x_656_; uint32_t v___x_657_; uint8_t v___x_658_; 
v___x_655_ = 4194304;
v___x_656_ = lean_uint32_land(v___y_554_, v___x_655_);
v___x_657_ = 0;
v___x_658_ = lean_uint32_dec_eq(v___x_656_, v___x_657_);
if (v___x_658_ == 0)
{
goto v___jp_643_;
}
else
{
uint32_t v___x_659_; 
v___x_659_ = lean_uint32_lor(v___y_554_, v___x_655_);
return v___x_659_;
}
}
}
v___jp_660_:
{
float v_result_663_; uint8_t v___x_664_; 
v_result_663_ = lean_float32_mul(v___y_661_, v___y_662_);
v___x_664_ = lean_float32_beq(v_result_663_, v_result_663_);
if (v___x_664_ == 0)
{
uint32_t v___x_665_; uint32_t v___x_666_; uint32_t v___x_667_; uint32_t v___x_668_; uint8_t v___x_669_; 
v___x_665_ = 23;
v___x_666_ = lean_uint32_shift_right(v___y_554_, v___x_665_);
v___x_667_ = 255;
v___x_668_ = lean_uint32_land(v___x_666_, v___x_667_);
v___x_669_ = lean_uint32_dec_eq(v___x_668_, v___x_667_);
if (v___x_669_ == 0)
{
v___y_654_ = v___x_669_;
goto v___jp_653_;
}
else
{
uint32_t v___x_670_; uint32_t v___x_671_; uint32_t v___x_672_; uint8_t v___x_673_; 
v___x_670_ = 8388607;
v___x_671_ = lean_uint32_land(v___y_554_, v___x_670_);
v___x_672_ = 0;
v___x_673_ = lean_uint32_dec_eq(v___x_671_, v___x_672_);
if (v___x_673_ == 0)
{
v___y_654_ = v___x_669_;
goto v___jp_653_;
}
else
{
goto v___jp_643_;
}
}
}
else
{
uint32_t v___x_674_; 
v___x_674_ = lean_float32_to_bits(v_result_663_);
return v___x_674_;
}
}
v___jp_675_:
{
if (v___y_677_ == 0)
{
float v___x_678_; 
v___x_678_ = lean_float32_of_bits(v___y_555_);
v___y_661_ = v___y_676_;
v___y_662_ = v___x_678_;
goto v___jp_660_;
}
else
{
uint32_t v___x_679_; uint32_t v___x_680_; uint32_t v___x_681_; uint32_t v___x_682_; float v___x_683_; lean_object* v___x_684_; uint32_t v___x_685_; uint32_t v___x_686_; lean_object* v___x_687_; lean_object* v___x_688_; float v___x_689_; float v___x_690_; 
v___x_679_ = 8388607;
v___x_680_ = lean_uint32_land(v___y_555_, v___x_679_);
v___x_681_ = 8388608;
v___x_682_ = lean_uint32_lor(v___x_680_, v___x_681_);
v___x_683_ = lean_uint32_to_float32(v___x_682_);
v___x_684_ = lp_competition_R2W01b_scaleTable;
v___x_685_ = 23;
v___x_686_ = lean_uint32_shift_right(v___y_555_, v___x_685_);
v___x_687_ = lean_uint32_to_nat(v___x_686_);
v___x_688_ = lean_array_fget_borrowed(v___x_684_, v___x_687_);
lean_dec(v___x_687_);
v___x_689_ = lean_unbox_float32(v___x_688_);
v___x_690_ = lean_float32_mul(v___x_683_, v___x_689_);
v___y_661_ = v___y_676_;
v___y_662_ = v___x_690_;
goto v___jp_660_;
}
}
v___jp_691_:
{
uint32_t v___x_693_; uint32_t v_a_694_; uint32_t v___x_695_; uint32_t v___x_696_; uint32_t v___x_697_; uint8_t v___x_698_; 
v___x_693_ = 2147483647;
v_a_694_ = lean_uint32_land(v___y_555_, v___x_693_);
v___x_695_ = 201326591;
v___x_696_ = 1;
v___x_697_ = lean_uint32_sub(v_a_694_, v___x_696_);
v___x_698_ = lean_uint32_dec_le(v___x_695_, v___x_697_);
if (v___x_698_ == 0)
{
v___y_676_ = v___y_692_;
v___y_677_ = v___x_698_;
goto v___jp_675_;
}
else
{
uint32_t v___x_699_; uint8_t v___x_700_; 
v___x_699_ = 2139095040;
v___x_700_ = lean_uint32_dec_lt(v_a_694_, v___x_699_);
v___y_676_ = v___y_692_;
v___y_677_ = v___x_700_;
goto v___jp_675_;
}
}
v___jp_703_:
{
if (v___y_704_ == 0)
{
float v___x_705_; 
v___x_705_ = lean_float32_of_bits(v___y_554_);
v___y_692_ = v___x_705_;
goto v___jp_691_;
}
else
{
uint32_t v___x_706_; uint32_t v___x_707_; uint32_t v___x_708_; uint32_t v___x_709_; float v___x_710_; lean_object* v___x_711_; lean_object* v___x_712_; lean_object* v___x_713_; float v___x_714_; float v___x_715_; 
v___x_706_ = 8388607;
v___x_707_ = lean_uint32_land(v___y_554_, v___x_706_);
v___x_708_ = 8388608;
v___x_709_ = lean_uint32_lor(v___x_707_, v___x_708_);
v___x_710_ = lean_uint32_to_float32(v___x_709_);
v___x_711_ = lp_competition_R2W01b_scaleTable;
v___x_712_ = lean_uint32_to_nat(v___x_702_);
v___x_713_ = lean_array_fget_borrowed(v___x_711_, v___x_712_);
lean_dec(v___x_712_);
v___x_714_ = lean_unbox_float32(v___x_713_);
v___x_715_ = lean_float32_mul(v___x_710_, v___x_714_);
v___y_692_ = v___x_715_;
goto v___jp_691_;
}
}
v___jp_717_:
{
uint32_t v___x_722_; uint32_t v___x_723_; uint32_t v___x_724_; uint32_t v___x_725_; uint32_t v___x_726_; 
v___x_722_ = lean_uint32_land(v___y_718_, v___x_716_);
v___x_723_ = lean_uint32_shift_left(v___x_722_, v___x_701_);
v___x_724_ = lean_uint32_lor(v___y_721_, v___x_723_);
v___x_725_ = lean_uint32_land(v___y_720_, v___y_719_);
v___x_726_ = lean_uint32_lor(v___x_724_, v___x_725_);
return v___x_726_;
}
v___jp_727_:
{
if (v___y_728_ == 0)
{
uint32_t v___x_732_; 
v___x_732_ = 0;
v___y_718_ = v___y_729_;
v___y_719_ = v___y_730_;
v___y_720_ = v___y_731_;
v___y_721_ = v___x_732_;
goto v___jp_717_;
}
else
{
uint32_t v___x_733_; 
v___x_733_ = 2147483648;
v___y_718_ = v___y_729_;
v___y_719_ = v___y_730_;
v___y_720_ = v___y_731_;
v___y_721_ = v___x_733_;
goto v___jp_717_;
}
}
v___jp_734_:
{
uint64_t v___x_740_; uint64_t v_encodedExponent_741_; uint32_t v___x_742_; uint64_t v___x_743_; uint8_t v___x_744_; 
v___x_740_ = 171ULL;
v_encodedExponent_741_ = lean_uint64_sub(v___y_738_, v___x_740_);
v___x_742_ = lean_uint64_to_uint32(v_encodedExponent_741_);
v___x_743_ = 8388608ULL;
v___x_744_ = lean_uint64_dec_lt(v___y_739_, v___x_743_);
if (v___x_744_ == 0)
{
uint64_t v___x_745_; uint32_t v___x_746_; 
v___x_745_ = lean_uint64_sub(v___y_739_, v___x_743_);
v___x_746_ = lean_uint64_to_uint32(v___x_745_);
v___y_728_ = v___y_735_;
v___y_729_ = v___x_742_;
v___y_730_ = v___y_737_;
v___y_731_ = v___x_746_;
goto v___jp_727_;
}
else
{
uint32_t v___x_747_; 
v___x_747_ = lean_uint64_to_uint32(v___y_736_);
v___y_728_ = v___y_735_;
v___y_729_ = v___x_742_;
v___y_730_ = v___y_737_;
v___y_731_ = v___x_747_;
goto v___jp_727_;
}
}
v___jp_748_:
{
uint64_t v___x_755_; uint8_t v___x_756_; 
v___x_755_ = 425ULL;
v___x_756_ = lean_uint64_dec_lt(v___x_755_, v___y_754_);
if (v___x_756_ == 0)
{
if (v___y_750_ == 0)
{
v___y_735_ = v___y_749_;
v___y_736_ = v___y_752_;
v___y_737_ = v___y_753_;
v___y_738_ = v___y_754_;
v___y_739_ = v___y_751_;
goto v___jp_734_;
}
else
{
uint64_t v___x_757_; 
v___x_757_ = 8388608ULL;
v___y_735_ = v___y_749_;
v___y_736_ = v___y_752_;
v___y_737_ = v___y_753_;
v___y_738_ = v___y_754_;
v___y_739_ = v___x_757_;
goto v___jp_734_;
}
}
else
{
if (v___y_749_ == 0)
{
uint32_t v___x_758_; 
v___x_758_ = 2139095040;
return v___x_758_;
}
else
{
uint32_t v___x_759_; 
v___x_759_ = 4286578688;
return v___x_759_;
}
}
}
v___jp_760_:
{
uint64_t v___x_766_; uint8_t v_carry_767_; 
v___x_766_ = 16777216ULL;
v_carry_767_ = lean_uint64_dec_eq(v___y_765_, v___x_766_);
if (v_carry_767_ == 0)
{
v___y_749_ = v___y_761_;
v___y_750_ = v_carry_767_;
v___y_751_ = v___y_765_;
v___y_752_ = v___y_762_;
v___y_753_ = v___y_763_;
v___y_754_ = v___y_764_;
goto v___jp_748_;
}
else
{
uint64_t v___x_768_; uint64_t v___x_769_; 
v___x_768_ = 1ULL;
v___x_769_ = lean_uint64_add(v___y_764_, v___x_768_);
v___y_749_ = v___y_761_;
v___y_750_ = v_carry_767_;
v___y_751_ = v___y_765_;
v___y_752_ = v___y_762_;
v___y_753_ = v___y_763_;
v___y_754_ = v___x_769_;
goto v___jp_748_;
}
}
v___jp_770_:
{
uint64_t v_position_777_; uint64_t v___x_778_; uint8_t v___x_779_; 
v_position_777_ = lean_uint64_add(v___y_776_, v___y_771_);
v___x_778_ = 172ULL;
v___x_779_ = lean_uint64_dec_lt(v_position_777_, v___x_778_);
if (v___x_779_ == 0)
{
uint64_t v___x_780_; uint8_t v___x_781_; 
v___x_780_ = 23ULL;
v___x_781_ = lean_uint64_dec_lt(v___y_776_, v___x_780_);
if (v___x_781_ == 0)
{
uint64_t v___x_782_; uint8_t v___x_783_; 
v___x_782_ = lean_uint64_sub(v___y_776_, v___x_780_);
v___x_783_ = lean_uint64_dec_eq(v___x_782_, v___y_774_);
if (v___x_783_ == 0)
{
uint64_t v___x_784_; uint8_t v___x_785_; 
v___x_784_ = 64ULL;
v___x_785_ = lean_uint64_dec_lt(v___x_782_, v___x_784_);
if (v___x_785_ == 0)
{
uint8_t v___x_786_; 
v___x_786_ = lean_uint64_dec_eq(v___x_782_, v___x_784_);
if (v___x_786_ == 0)
{
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v___y_774_;
goto v___jp_760_;
}
else
{
uint64_t v___x_787_; uint8_t v___x_788_; 
v___x_787_ = 9223372036854775808ULL;
v___x_788_ = lean_uint64_dec_lt(v___x_787_, v___y_772_);
if (v___x_788_ == 0)
{
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v___y_774_;
goto v___jp_760_;
}
else
{
uint64_t v___x_789_; 
v___x_789_ = 1ULL;
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v___x_789_;
goto v___jp_760_;
}
}
}
else
{
uint64_t v_quotient_790_; uint64_t v___x_791_; uint64_t v___x_792_; uint64_t v___x_793_; uint64_t v_remainder_794_; uint64_t v___x_795_; uint64_t v_half_796_; uint8_t v___x_797_; 
v_quotient_790_ = lean_uint64_shift_right(v___y_772_, v___x_782_);
v___x_791_ = 1ULL;
v___x_792_ = lean_uint64_shift_left(v___x_791_, v___x_782_);
v___x_793_ = lean_uint64_sub(v___x_792_, v___x_791_);
v_remainder_794_ = lean_uint64_land(v___y_772_, v___x_793_);
v___x_795_ = lean_uint64_sub(v___x_782_, v___x_791_);
v_half_796_ = lean_uint64_shift_left(v___x_791_, v___x_795_);
v___x_797_ = lean_uint64_dec_lt(v_remainder_794_, v_half_796_);
if (v___x_797_ == 0)
{
uint8_t v___x_798_; 
v___x_798_ = lean_uint64_dec_lt(v_half_796_, v_remainder_794_);
if (v___x_798_ == 0)
{
uint64_t v___x_799_; uint8_t v___x_800_; 
v___x_799_ = lean_uint64_land(v_quotient_790_, v___x_791_);
v___x_800_ = lean_uint64_dec_eq(v___x_799_, v___y_774_);
if (v___x_800_ == 0)
{
uint64_t v___x_801_; 
v___x_801_ = lean_uint64_add(v_quotient_790_, v___x_791_);
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v___x_801_;
goto v___jp_760_;
}
else
{
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v_quotient_790_;
goto v___jp_760_;
}
}
else
{
uint64_t v___x_802_; 
v___x_802_ = lean_uint64_add(v_quotient_790_, v___x_791_);
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v___x_802_;
goto v___jp_760_;
}
}
else
{
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v_quotient_790_;
goto v___jp_760_;
}
}
}
else
{
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v___y_772_;
goto v___jp_760_;
}
}
else
{
uint64_t v___x_803_; uint64_t v___x_804_; 
v___x_803_ = lean_uint64_sub(v___x_780_, v___y_776_);
v___x_804_ = lean_uint64_shift_left(v___y_772_, v___x_803_);
v___y_761_ = v___y_773_;
v___y_762_ = v___y_774_;
v___y_763_ = v___y_775_;
v___y_764_ = v_position_777_;
v___y_765_ = v___x_804_;
goto v___jp_760_;
}
}
else
{
uint64_t v___x_805_; uint8_t v___x_806_; 
v___x_805_ = 149ULL;
v___x_806_ = lean_uint64_dec_lt(v___y_771_, v___x_805_);
if (v___x_806_ == 0)
{
uint64_t v___x_807_; uint64_t v___x_808_; 
v___x_807_ = lean_uint64_sub(v___y_771_, v___x_805_);
v___x_808_ = lean_uint64_shift_left(v___y_772_, v___x_807_);
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v___x_808_;
goto v___jp_570_;
}
else
{
uint64_t v___x_809_; uint8_t v___x_810_; 
v___x_809_ = lean_uint64_sub(v___x_805_, v___y_771_);
v___x_810_ = lean_uint64_dec_eq(v___x_809_, v___y_774_);
if (v___x_810_ == 0)
{
uint64_t v___x_811_; uint8_t v___x_812_; 
v___x_811_ = 64ULL;
v___x_812_ = lean_uint64_dec_lt(v___x_809_, v___x_811_);
if (v___x_812_ == 0)
{
uint8_t v___x_813_; 
v___x_813_ = lean_uint64_dec_eq(v___x_809_, v___x_811_);
if (v___x_813_ == 0)
{
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v___y_774_;
goto v___jp_570_;
}
else
{
uint64_t v___x_814_; uint8_t v___x_815_; 
v___x_814_ = 9223372036854775808ULL;
v___x_815_ = lean_uint64_dec_lt(v___x_814_, v___y_772_);
if (v___x_815_ == 0)
{
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v___y_774_;
goto v___jp_570_;
}
else
{
uint64_t v___x_816_; 
v___x_816_ = 1ULL;
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v___x_816_;
goto v___jp_570_;
}
}
}
else
{
uint64_t v_quotient_817_; uint64_t v___x_818_; uint64_t v___x_819_; uint64_t v___x_820_; uint64_t v_remainder_821_; uint64_t v___x_822_; uint64_t v_half_823_; uint8_t v___x_824_; 
v_quotient_817_ = lean_uint64_shift_right(v___y_772_, v___x_809_);
v___x_818_ = 1ULL;
v___x_819_ = lean_uint64_shift_left(v___x_818_, v___x_809_);
v___x_820_ = lean_uint64_sub(v___x_819_, v___x_818_);
v_remainder_821_ = lean_uint64_land(v___y_772_, v___x_820_);
v___x_822_ = lean_uint64_sub(v___x_809_, v___x_818_);
v_half_823_ = lean_uint64_shift_left(v___x_818_, v___x_822_);
v___x_824_ = lean_uint64_dec_lt(v_remainder_821_, v_half_823_);
if (v___x_824_ == 0)
{
uint8_t v___x_825_; 
v___x_825_ = lean_uint64_dec_lt(v_half_823_, v_remainder_821_);
if (v___x_825_ == 0)
{
uint64_t v___x_826_; uint8_t v___x_827_; 
v___x_826_ = lean_uint64_land(v_quotient_817_, v___x_818_);
v___x_827_ = lean_uint64_dec_eq(v___x_826_, v___y_774_);
if (v___x_827_ == 0)
{
uint64_t v___x_828_; 
v___x_828_ = lean_uint64_add(v_quotient_817_, v___x_818_);
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v___x_828_;
goto v___jp_570_;
}
else
{
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v_quotient_817_;
goto v___jp_570_;
}
}
else
{
uint64_t v___x_829_; 
v___x_829_ = lean_uint64_add(v_quotient_817_, v___x_818_);
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v___x_829_;
goto v___jp_570_;
}
}
else
{
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v_quotient_817_;
goto v___jp_570_;
}
}
}
else
{
v___y_571_ = v___y_773_;
v___y_572_ = v___y_774_;
v___y_573_ = v___y_775_;
v___y_574_ = v___y_772_;
goto v___jp_570_;
}
}
}
}
v___jp_830_:
{
uint64_t v___x_838_; uint64_t v___x_839_; uint8_t v___x_840_; 
v___x_838_ = 1ULL;
v___x_839_ = lean_uint64_shift_right(v___y_836_, v___x_838_);
v___x_840_ = lean_uint64_dec_eq(v___x_839_, v___y_834_);
if (v___x_840_ == 0)
{
uint64_t v___x_841_; 
v___x_841_ = lean_uint64_add(v___y_837_, v___x_838_);
v___y_771_ = v___y_831_;
v___y_772_ = v___y_833_;
v___y_773_ = v___y_832_;
v___y_774_ = v___y_834_;
v___y_775_ = v___y_835_;
v___y_776_ = v___x_841_;
goto v___jp_770_;
}
else
{
v___y_771_ = v___y_831_;
v___y_772_ = v___y_833_;
v___y_773_ = v___y_832_;
v___y_774_ = v___y_834_;
v___y_775_ = v___y_835_;
v___y_776_ = v___y_837_;
goto v___jp_770_;
}
}
v___jp_842_:
{
uint64_t v___x_852_; uint8_t v___x_853_; 
v___x_852_ = lean_uint64_shift_right(v___y_844_, v___y_845_);
v___x_853_ = lean_uint64_dec_eq(v___x_852_, v___y_848_);
if (v___x_853_ == 0)
{
uint64_t v___x_854_; 
v___x_854_ = lean_uint64_add(v___y_850_, v___y_845_);
v___y_831_ = v___y_843_;
v___y_832_ = v___y_847_;
v___y_833_ = v___y_846_;
v___y_834_ = v___y_848_;
v___y_835_ = v___y_849_;
v___y_836_ = v___y_851_;
v___y_837_ = v___x_854_;
goto v___jp_830_;
}
else
{
v___y_831_ = v___y_843_;
v___y_832_ = v___y_847_;
v___y_833_ = v___y_846_;
v___y_834_ = v___y_848_;
v___y_835_ = v___y_849_;
v___y_836_ = v___y_851_;
v___y_837_ = v___y_850_;
goto v___jp_830_;
}
}
v___jp_855_:
{
uint64_t v___x_863_; uint64_t v___x_864_; uint8_t v___x_865_; 
v___x_863_ = 2ULL;
v___x_864_ = lean_uint64_shift_right(v___y_857_, v___x_863_);
v___x_865_ = lean_uint64_dec_eq(v___x_864_, v___y_860_);
if (v___x_865_ == 0)
{
v___y_843_ = v___y_856_;
v___y_844_ = v___y_857_;
v___y_845_ = v___x_863_;
v___y_846_ = v___y_859_;
v___y_847_ = v___y_858_;
v___y_848_ = v___y_860_;
v___y_849_ = v___y_861_;
v___y_850_ = v___y_862_;
v___y_851_ = v___x_864_;
goto v___jp_842_;
}
else
{
v___y_843_ = v___y_856_;
v___y_844_ = v___y_857_;
v___y_845_ = v___x_863_;
v___y_846_ = v___y_859_;
v___y_847_ = v___y_858_;
v___y_848_ = v___y_860_;
v___y_849_ = v___y_861_;
v___y_850_ = v___y_862_;
v___y_851_ = v___y_857_;
goto v___jp_842_;
}
}
v___jp_866_:
{
uint64_t v___x_876_; uint8_t v___x_877_; 
v___x_876_ = lean_uint64_shift_right(v___y_874_, v___y_868_);
v___x_877_ = lean_uint64_dec_eq(v___x_876_, v___y_871_);
if (v___x_877_ == 0)
{
uint64_t v___x_878_; 
v___x_878_ = lean_uint64_add(v___y_873_, v___y_868_);
v___y_856_ = v___y_867_;
v___y_857_ = v___y_875_;
v___y_858_ = v___y_870_;
v___y_859_ = v___y_869_;
v___y_860_ = v___y_871_;
v___y_861_ = v___y_872_;
v___y_862_ = v___x_878_;
goto v___jp_855_;
}
else
{
v___y_856_ = v___y_867_;
v___y_857_ = v___y_875_;
v___y_858_ = v___y_870_;
v___y_859_ = v___y_869_;
v___y_860_ = v___y_871_;
v___y_861_ = v___y_872_;
v___y_862_ = v___y_873_;
goto v___jp_855_;
}
}
v___jp_879_:
{
uint64_t v___x_887_; uint64_t v___x_888_; uint8_t v___x_889_; 
v___x_887_ = 4ULL;
v___x_888_ = lean_uint64_shift_right(v___y_885_, v___x_887_);
v___x_889_ = lean_uint64_dec_eq(v___x_888_, v___y_883_);
if (v___x_889_ == 0)
{
v___y_867_ = v___y_880_;
v___y_868_ = v___x_887_;
v___y_869_ = v___y_882_;
v___y_870_ = v___y_881_;
v___y_871_ = v___y_883_;
v___y_872_ = v___y_884_;
v___y_873_ = v___y_886_;
v___y_874_ = v___y_885_;
v___y_875_ = v___x_888_;
goto v___jp_866_;
}
else
{
v___y_867_ = v___y_880_;
v___y_868_ = v___x_887_;
v___y_869_ = v___y_882_;
v___y_870_ = v___y_881_;
v___y_871_ = v___y_883_;
v___y_872_ = v___y_884_;
v___y_873_ = v___y_886_;
v___y_874_ = v___y_885_;
v___y_875_ = v___y_885_;
goto v___jp_866_;
}
}
v___jp_890_:
{
uint64_t v___x_900_; uint8_t v___x_901_; 
v___x_900_ = lean_uint64_shift_right(v___y_892_, v___y_898_);
v___x_901_ = lean_uint64_dec_eq(v___x_900_, v___y_895_);
if (v___x_901_ == 0)
{
uint64_t v___x_902_; 
v___x_902_ = lean_uint64_add(v___y_897_, v___y_898_);
v___y_880_ = v___y_891_;
v___y_881_ = v___y_894_;
v___y_882_ = v___y_893_;
v___y_883_ = v___y_895_;
v___y_884_ = v___y_896_;
v___y_885_ = v___y_899_;
v___y_886_ = v___x_902_;
goto v___jp_879_;
}
else
{
v___y_880_ = v___y_891_;
v___y_881_ = v___y_894_;
v___y_882_ = v___y_893_;
v___y_883_ = v___y_895_;
v___y_884_ = v___y_896_;
v___y_885_ = v___y_899_;
v___y_886_ = v___y_897_;
goto v___jp_879_;
}
}
v___jp_903_:
{
uint64_t v___x_911_; uint64_t v___x_912_; uint8_t v___x_913_; 
v___x_911_ = 8ULL;
v___x_912_ = lean_uint64_shift_right(v___y_905_, v___x_911_);
v___x_913_ = lean_uint64_dec_eq(v___x_912_, v___y_908_);
if (v___x_913_ == 0)
{
v___y_891_ = v___y_904_;
v___y_892_ = v___y_905_;
v___y_893_ = v___y_907_;
v___y_894_ = v___y_906_;
v___y_895_ = v___y_908_;
v___y_896_ = v___y_909_;
v___y_897_ = v___y_910_;
v___y_898_ = v___x_911_;
v___y_899_ = v___x_912_;
goto v___jp_890_;
}
else
{
v___y_891_ = v___y_904_;
v___y_892_ = v___y_905_;
v___y_893_ = v___y_907_;
v___y_894_ = v___y_906_;
v___y_895_ = v___y_908_;
v___y_896_ = v___y_909_;
v___y_897_ = v___y_910_;
v___y_898_ = v___x_911_;
v___y_899_ = v___y_905_;
goto v___jp_890_;
}
}
v___jp_914_:
{
uint64_t v___x_924_; uint8_t v___x_925_; 
v___x_924_ = lean_uint64_shift_right(v___y_915_, v___y_920_);
v___x_925_ = lean_uint64_dec_eq(v___x_924_, v___y_919_);
if (v___x_925_ == 0)
{
uint64_t v___x_926_; 
v___x_926_ = lean_uint64_add(v___y_922_, v___y_920_);
v___y_904_ = v___y_916_;
v___y_905_ = v___y_923_;
v___y_906_ = v___y_918_;
v___y_907_ = v___y_917_;
v___y_908_ = v___y_919_;
v___y_909_ = v___y_921_;
v___y_910_ = v___x_926_;
goto v___jp_903_;
}
else
{
v___y_904_ = v___y_916_;
v___y_905_ = v___y_923_;
v___y_906_ = v___y_918_;
v___y_907_ = v___y_917_;
v___y_908_ = v___y_919_;
v___y_909_ = v___y_921_;
v___y_910_ = v___y_922_;
goto v___jp_903_;
}
}
v___jp_927_:
{
uint64_t v___x_935_; uint64_t v___x_936_; uint8_t v___x_937_; 
v___x_935_ = 16ULL;
v___x_936_ = lean_uint64_shift_right(v___y_929_, v___x_935_);
v___x_937_ = lean_uint64_dec_eq(v___x_936_, v___y_932_);
if (v___x_937_ == 0)
{
v___y_915_ = v___y_929_;
v___y_916_ = v___y_928_;
v___y_917_ = v___y_931_;
v___y_918_ = v___y_930_;
v___y_919_ = v___y_932_;
v___y_920_ = v___x_935_;
v___y_921_ = v___y_933_;
v___y_922_ = v___y_934_;
v___y_923_ = v___x_936_;
goto v___jp_914_;
}
else
{
v___y_915_ = v___y_929_;
v___y_916_ = v___y_928_;
v___y_917_ = v___y_931_;
v___y_918_ = v___y_930_;
v___y_919_ = v___y_932_;
v___y_920_ = v___x_935_;
v___y_921_ = v___y_933_;
v___y_922_ = v___y_934_;
v___y_923_ = v___y_929_;
goto v___jp_914_;
}
}
v___jp_938_:
{
uint64_t v___x_946_; uint8_t v___x_947_; 
v___x_946_ = lean_uint64_shift_right(v___y_940_, v___y_944_);
v___x_947_ = lean_uint64_dec_eq(v___x_946_, v___y_942_);
if (v___x_947_ == 0)
{
v___y_928_ = v___y_939_;
v___y_929_ = v___y_945_;
v___y_930_ = v___y_941_;
v___y_931_ = v___y_940_;
v___y_932_ = v___y_942_;
v___y_933_ = v___y_943_;
v___y_934_ = v___y_944_;
goto v___jp_927_;
}
else
{
v___y_928_ = v___y_939_;
v___y_929_ = v___y_945_;
v___y_930_ = v___y_941_;
v___y_931_ = v___y_940_;
v___y_932_ = v___y_942_;
v___y_933_ = v___y_943_;
v___y_934_ = v___y_942_;
goto v___jp_927_;
}
}
v___jp_948_:
{
uint64_t v___x_953_; uint8_t v___x_954_; 
v___x_953_ = 0ULL;
v___x_954_ = lean_uint64_dec_eq(v___y_950_, v___x_953_);
if (v___x_954_ == 0)
{
uint64_t v___x_955_; uint64_t v___x_956_; uint8_t v___x_957_; 
v___x_955_ = 32ULL;
v___x_956_ = lean_uint64_shift_right(v___y_950_, v___x_955_);
v___x_957_ = lean_uint64_dec_eq(v___x_956_, v___x_953_);
if (v___x_957_ == 0)
{
v___y_939_ = v___y_949_;
v___y_940_ = v___y_950_;
v___y_941_ = v___y_951_;
v___y_942_ = v___x_953_;
v___y_943_ = v___y_952_;
v___y_944_ = v___x_955_;
v___y_945_ = v___x_956_;
goto v___jp_938_;
}
else
{
v___y_939_ = v___y_949_;
v___y_940_ = v___y_950_;
v___y_941_ = v___y_951_;
v___y_942_ = v___x_953_;
v___y_943_ = v___y_952_;
v___y_944_ = v___x_955_;
v___y_945_ = v___y_950_;
goto v___jp_938_;
}
}
else
{
if (v___y_951_ == 0)
{
uint32_t v___x_958_; 
v___x_958_ = 0;
return v___x_958_;
}
else
{
uint32_t v___x_959_; 
v___x_959_ = 2147483648;
return v___x_959_;
}
}
}
v___jp_960_:
{
uint64_t v___x_967_; uint64_t v___x_968_; uint64_t v___x_969_; uint8_t v___x_970_; 
v___x_967_ = lean_uint64_mul(v___y_963_, v___y_961_);
v___x_968_ = lean_uint64_add(v___y_965_, v___y_966_);
v___x_969_ = 281474976710656ULL;
v___x_970_ = lean_uint64_dec_lt(v___x_967_, v___x_969_);
if (v___x_970_ == 0)
{
v___y_949_ = v___x_968_;
v___y_950_ = v___x_967_;
v___y_951_ = v___y_962_;
v___y_952_ = v___y_964_;
goto v___jp_948_;
}
else
{
uint64_t v___x_971_; uint8_t v___x_972_; 
v___x_971_ = 123ULL;
v___x_972_ = lean_uint64_dec_le(v___x_968_, v___x_971_);
if (v___x_972_ == 0)
{
v___y_949_ = v___x_968_;
v___y_950_ = v___x_967_;
v___y_951_ = v___y_962_;
v___y_952_ = v___y_964_;
goto v___jp_948_;
}
else
{
uint64_t v___x_973_; uint8_t v___x_974_; 
v___x_973_ = 0ULL;
v___x_974_ = lean_uint64_dec_eq(v___x_967_, v___x_973_);
if (v___x_974_ == 0)
{
uint64_t v___x_975_; uint64_t v___x_976_; uint8_t v___x_977_; 
v___x_975_ = 149ULL;
v___x_976_ = lean_uint64_sub(v___x_975_, v___x_968_);
v___x_977_ = lean_uint64_dec_eq(v___x_976_, v___x_973_);
if (v___x_977_ == 0)
{
uint64_t v___x_978_; uint8_t v___x_979_; 
v___x_978_ = 64ULL;
v___x_979_ = lean_uint64_dec_lt(v___x_976_, v___x_978_);
if (v___x_979_ == 0)
{
uint8_t v___x_980_; 
v___x_980_ = lean_uint64_dec_eq(v___x_976_, v___x_978_);
if (v___x_980_ == 0)
{
v___y_592_ = v___x_973_;
v___y_593_ = v___y_962_;
v___y_594_ = v___y_964_;
v___y_595_ = v___x_973_;
goto v___jp_591_;
}
else
{
uint64_t v___x_981_; uint8_t v___x_982_; 
v___x_981_ = 9223372036854775808ULL;
v___x_982_ = lean_uint64_dec_lt(v___x_981_, v___x_967_);
if (v___x_982_ == 0)
{
v___y_592_ = v___x_973_;
v___y_593_ = v___y_962_;
v___y_594_ = v___y_964_;
v___y_595_ = v___x_973_;
goto v___jp_591_;
}
else
{
uint64_t v___x_983_; 
v___x_983_ = 1ULL;
v___y_592_ = v___x_973_;
v___y_593_ = v___y_962_;
v___y_594_ = v___y_964_;
v___y_595_ = v___x_983_;
goto v___jp_591_;
}
}
}
else
{
uint64_t v_quotient_984_; uint64_t v___x_985_; uint64_t v___x_986_; uint64_t v___x_987_; uint64_t v_remainder_988_; uint64_t v___x_989_; uint64_t v_half_990_; uint8_t v___x_991_; 
v_quotient_984_ = lean_uint64_shift_right(v___x_967_, v___x_976_);
v___x_985_ = 1ULL;
v___x_986_ = lean_uint64_shift_left(v___x_985_, v___x_976_);
v___x_987_ = lean_uint64_sub(v___x_986_, v___x_985_);
v_remainder_988_ = lean_uint64_land(v___x_967_, v___x_987_);
v___x_989_ = lean_uint64_sub(v___x_976_, v___x_985_);
v_half_990_ = lean_uint64_shift_left(v___x_985_, v___x_989_);
v___x_991_ = lean_uint64_dec_lt(v_remainder_988_, v_half_990_);
if (v___x_991_ == 0)
{
uint8_t v___x_992_; 
v___x_992_ = lean_uint64_dec_lt(v_half_990_, v_remainder_988_);
if (v___x_992_ == 0)
{
uint64_t v___x_993_; uint8_t v___x_994_; 
v___x_993_ = lean_uint64_land(v_quotient_984_, v___x_985_);
v___x_994_ = lean_uint64_dec_eq(v___x_993_, v___x_973_);
if (v___x_994_ == 0)
{
uint64_t v___x_995_; 
v___x_995_ = lean_uint64_add(v_quotient_984_, v___x_985_);
v___y_592_ = v___x_973_;
v___y_593_ = v___y_962_;
v___y_594_ = v___y_964_;
v___y_595_ = v___x_995_;
goto v___jp_591_;
}
else
{
v___y_592_ = v___x_973_;
v___y_593_ = v___y_962_;
v___y_594_ = v___y_964_;
v___y_595_ = v_quotient_984_;
goto v___jp_591_;
}
}
else
{
uint64_t v___x_996_; 
v___x_996_ = lean_uint64_add(v_quotient_984_, v___x_985_);
v___y_592_ = v___x_973_;
v___y_593_ = v___y_962_;
v___y_594_ = v___y_964_;
v___y_595_ = v___x_996_;
goto v___jp_591_;
}
}
else
{
v___y_592_ = v___x_973_;
v___y_593_ = v___y_962_;
v___y_594_ = v___y_964_;
v___y_595_ = v_quotient_984_;
goto v___jp_591_;
}
}
}
else
{
v___y_592_ = v___x_973_;
v___y_593_ = v___y_962_;
v___y_594_ = v___y_964_;
v___y_595_ = v___x_967_;
goto v___jp_591_;
}
}
else
{
if (v___y_962_ == 0)
{
uint32_t v___x_997_; 
v___x_997_ = 0;
return v___x_997_;
}
else
{
uint32_t v___x_998_; 
v___x_998_ = 2147483648;
return v___x_998_;
}
}
}
}
}
v___jp_1002_:
{
uint64_t v___x_1008_; uint64_t v___x_1009_; uint8_t v___x_1010_; 
v___x_1008_ = lean_uint32_to_uint64(v_ey_1001_);
v___x_1009_ = 0ULL;
v___x_1010_ = lean_uint64_dec_eq(v___x_1008_, v___x_1009_);
if (v___x_1010_ == 0)
{
uint64_t v___x_1011_; uint64_t v___x_1012_; 
v___x_1011_ = 1ULL;
v___x_1012_ = lean_uint64_sub(v___x_1008_, v___x_1011_);
v___y_961_ = v___y_1003_;
v___y_962_ = v___y_1004_;
v___y_963_ = v___y_1005_;
v___y_964_ = v___y_1006_;
v___y_965_ = v___y_1007_;
v___y_966_ = v___x_1012_;
goto v___jp_960_;
}
else
{
v___y_961_ = v___y_1003_;
v___y_962_ = v___y_1004_;
v___y_963_ = v___y_1005_;
v___y_964_ = v___y_1006_;
v___y_965_ = v___y_1007_;
v___y_966_ = v___x_1009_;
goto v___jp_960_;
}
}
v___jp_1013_:
{
uint64_t v___x_1018_; uint64_t v___x_1019_; uint8_t v___x_1020_; 
v___x_1018_ = lean_uint32_to_uint64(v_ex_999_);
v___x_1019_ = 0ULL;
v___x_1020_ = lean_uint64_dec_eq(v___x_1018_, v___x_1019_);
if (v___x_1020_ == 0)
{
uint64_t v___x_1021_; uint64_t v___x_1022_; 
v___x_1021_ = 1ULL;
v___x_1022_ = lean_uint64_sub(v___x_1018_, v___x_1021_);
v___y_1003_ = v___y_1017_;
v___y_1004_ = v___y_1014_;
v___y_1005_ = v___y_1015_;
v___y_1006_ = v___y_1016_;
v___y_1007_ = v___x_1022_;
goto v___jp_1002_;
}
else
{
v___y_1003_ = v___y_1017_;
v___y_1004_ = v___y_1014_;
v___y_1005_ = v___y_1015_;
v___y_1006_ = v___y_1016_;
v___y_1007_ = v___x_1019_;
goto v___jp_1002_;
}
}
v___jp_1023_:
{
uint32_t v___x_1028_; uint8_t v___x_1029_; 
v___x_1028_ = 0;
v___x_1029_ = lean_uint32_dec_eq(v_ey_1001_, v___x_1028_);
if (v___x_1029_ == 0)
{
uint64_t v___x_1030_; uint64_t v___x_1031_; uint64_t v___x_1032_; 
v___x_1030_ = lean_uint32_to_uint64(v___y_1026_);
v___x_1031_ = 8388608ULL;
v___x_1032_ = lean_uint64_lor(v___x_1030_, v___x_1031_);
v___y_1014_ = v___y_1024_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1025_;
v___y_1017_ = v___x_1032_;
goto v___jp_1013_;
}
else
{
uint64_t v___x_1033_; 
v___x_1033_ = lean_uint32_to_uint64(v___y_1026_);
v___y_1014_ = v___y_1024_;
v___y_1015_ = v___y_1027_;
v___y_1016_ = v___y_1025_;
v___y_1017_ = v___x_1033_;
goto v___jp_1013_;
}
}
v___jp_1034_:
{
uint32_t v___x_1036_; uint32_t v_xFraction_1037_; uint32_t v_yFraction_1038_; uint32_t v___x_1039_; uint8_t v___x_1040_; 
v___x_1036_ = 8388607;
v_xFraction_1037_ = lean_uint32_land(v___y_554_, v___x_1036_);
v_yFraction_1038_ = lean_uint32_land(v___y_555_, v___x_1036_);
v___x_1039_ = 0;
v___x_1040_ = lean_uint32_dec_eq(v_ex_999_, v___x_1039_);
if (v___x_1040_ == 0)
{
uint64_t v___x_1041_; uint64_t v___x_1042_; uint64_t v___x_1043_; 
v___x_1041_ = lean_uint32_to_uint64(v_xFraction_1037_);
v___x_1042_ = 8388608ULL;
v___x_1043_ = lean_uint64_lor(v___x_1041_, v___x_1042_);
v___y_1024_ = v___y_1035_;
v___y_1025_ = v___x_1036_;
v___y_1026_ = v_yFraction_1038_;
v___y_1027_ = v___x_1043_;
goto v___jp_1023_;
}
else
{
uint64_t v___x_1044_; 
v___x_1044_ = lean_uint32_to_uint64(v_xFraction_1037_);
v___y_1024_ = v___y_1035_;
v___y_1025_ = v___x_1036_;
v___y_1026_ = v_yFraction_1038_;
v___y_1027_ = v___x_1044_;
goto v___jp_1023_;
}
}
v___jp_1048_:
{
if (v___y_1050_ == 0)
{
v___y_1035_ = v___x_1047_;
goto v___jp_1034_;
}
else
{
v___y_1035_ = v___y_1049_;
goto v___jp_1034_;
}
}
v___jp_1051_:
{
if (v___y_1052_ == 0)
{
if (v___y_1054_ == 0)
{
v___y_1049_ = v___y_1053_;
v___y_1050_ = v___x_1047_;
goto v___jp_1048_;
}
else
{
v___y_1035_ = v___x_1047_;
goto v___jp_1034_;
}
}
else
{
v___y_1049_ = v___y_1053_;
v___y_1050_ = v___y_1054_;
goto v___jp_1048_;
}
}
v___jp_1055_:
{
uint32_t v___x_1058_; uint32_t v___x_1059_; uint32_t v___x_1060_; uint8_t v___x_1061_; 
v___x_1058_ = 2147483648;
v___x_1059_ = lean_uint32_land(v___y_555_, v___x_1058_);
v___x_1060_ = 0;
v___x_1061_ = lean_uint32_dec_eq(v___x_1059_, v___x_1060_);
if (v___x_1061_ == 0)
{
v___y_1052_ = v___y_1057_;
v___y_1053_ = v___y_1056_;
v___y_1054_ = v___x_1047_;
goto v___jp_1051_;
}
else
{
v___y_1052_ = v___y_1057_;
v___y_1053_ = v___y_1056_;
v___y_1054_ = v___y_1056_;
goto v___jp_1051_;
}
}
v___jp_1062_:
{
if (v___y_1063_ == 0)
{
uint32_t v___x_1064_; uint32_t v___x_1065_; uint32_t v___x_1066_; uint8_t v___x_1067_; 
v___x_1064_ = 2147483648;
v___x_1065_ = lean_uint32_land(v___y_554_, v___x_1064_);
v___x_1066_ = 0;
v___x_1067_ = lean_uint32_dec_eq(v___x_1065_, v___x_1066_);
if (v___x_1067_ == 0)
{
v___y_1056_ = v___y_1063_;
v___y_1057_ = v___x_1047_;
goto v___jp_1055_;
}
else
{
v___y_1056_ = v___y_1063_;
v___y_1057_ = v___y_1063_;
goto v___jp_1055_;
}
}
else
{
lean_object* v___x_1068_; lean_object* v___x_1069_; lean_object* v___x_1070_; uint32_t v___x_1071_; 
v___x_1068_ = lean_uint32_to_nat(v___y_554_);
v___x_1069_ = lean_uint32_to_nat(v___y_555_);
v___x_1070_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1068_, v___x_1069_);
v___x_1071_ = lean_uint32_of_nat(v___x_1070_);
lean_dec(v___x_1070_);
return v___x_1071_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_1086_, lean_object* v___y_1087_){
_start:
{
uint32_t v___y_8987__boxed_1088_; uint32_t v___y_8988__boxed_1089_; uint32_t v_res_1090_; lean_object* v_r_1091_; 
v___y_8987__boxed_1088_ = lean_unbox_uint32(v___y_1086_);
lean_dec(v___y_1086_);
v___y_8988__boxed_1089_ = lean_unbox_uint32(v___y_1087_);
lean_dec(v___y_1087_);
v_res_1090_ = lp_competition_main___lam__1(v___y_8987__boxed_1088_, v___y_8988__boxed_1089_);
v_r_1091_ = lean_box_uint32(v_res_1090_);
return v_r_1091_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__2(uint32_t v___y_1092_, uint32_t v___y_1093_){
_start:
{
uint32_t v___y_1095_; uint32_t v___y_1096_; uint32_t v___y_1097_; uint32_t v___y_1098_; uint32_t v___y_1099_; uint32_t v___y_1100_; uint8_t v___y_1112_; uint8_t v___y_1126_; uint8_t v___y_1140_; uint8_t v___y_1157_; float v___y_1164_; float v___y_1165_; float v___y_1179_; uint8_t v___y_1180_; float v___y_1195_; uint8_t v___y_1205_; uint8_t v___y_1225_; uint8_t v___y_1239_; uint8_t v___y_1253_; uint8_t v___y_1270_; float v___y_1277_; float v___y_1278_; float v___y_1292_; uint8_t v___y_1293_; float v___y_1308_; uint8_t v___y_1318_; uint8_t v___y_1338_; uint8_t v___y_1352_; uint8_t v___y_1366_; uint8_t v___y_1383_; float v___y_1390_; float v___y_1391_; float v___y_1405_; uint8_t v___y_1406_; float v___y_1421_; uint32_t v___y_1431_; uint32_t v___y_1432_; uint32_t v___y_1433_; uint8_t v___y_1434_; uint32_t v___y_1446_; uint32_t v___y_1447_; uint32_t v___y_1448_; uint32_t v___y_1449_; uint32_t v___y_1450_; uint32_t v___y_1451_; uint32_t v___y_1452_; uint32_t v___y_1453_; uint32_t v___y_1454_; uint32_t v___y_1494_; uint32_t v___y_1495_; uint32_t v___y_1496_; uint32_t v___y_1497_; uint32_t v___y_1498_; uint32_t v___y_1499_; uint8_t v___y_1500_; uint32_t v___y_1512_; uint8_t v___y_1513_; uint32_t v___y_1514_; uint8_t v___y_1526_; uint32_t v___y_1527_; uint8_t v___y_1536_; uint8_t v___y_1545_; uint32_t v___y_1555_; uint32_t v___y_1556_; uint32_t v___y_1557_; uint32_t v___y_1558_; uint32_t v___y_1559_; uint32_t v___y_1565_; uint32_t v___y_1566_; uint8_t v___y_1577_; uint32_t v___y_1587_; uint32_t v___y_1588_; uint32_t v___y_1589_; uint32_t v___y_1590_; uint32_t v___y_1600_; uint8_t v___y_1611_; uint32_t v___x_1627_; uint32_t v___x_1628_; uint32_t v___x_1629_; uint32_t v___x_1630_; uint32_t v___x_1631_; uint32_t v___x_1632_; uint32_t v___x_1633_; uint8_t v___x_1634_; 
v___x_1627_ = 23;
v___x_1628_ = lean_uint32_shift_right(v___y_1092_, v___x_1627_);
v___x_1629_ = 255;
v___x_1630_ = lean_uint32_land(v___x_1628_, v___x_1629_);
v___x_1631_ = 1;
v___x_1632_ = lean_uint32_sub(v___x_1630_, v___x_1631_);
v___x_1633_ = 253;
v___x_1634_ = lean_uint32_dec_le(v___x_1632_, v___x_1633_);
if (v___x_1634_ == 0)
{
v___y_1611_ = v___x_1634_;
goto v___jp_1610_;
}
else
{
uint32_t v___x_1635_; uint32_t v___x_1636_; uint32_t v___x_1637_; uint8_t v___x_1638_; 
v___x_1635_ = lean_uint32_shift_right(v___y_1093_, v___x_1627_);
v___x_1636_ = lean_uint32_land(v___x_1635_, v___x_1629_);
v___x_1637_ = lean_uint32_sub(v___x_1636_, v___x_1631_);
v___x_1638_ = lean_uint32_dec_le(v___x_1637_, v___x_1633_);
v___y_1611_ = v___x_1638_;
goto v___jp_1610_;
}
v___jp_1094_:
{
uint32_t v___x_1101_; uint32_t v___x_1102_; uint32_t v___x_1103_; uint32_t v___x_1104_; uint32_t v___x_1105_; 
v___x_1101_ = lean_uint32_land(v___y_1097_, v___y_1098_);
v___x_1102_ = lean_uint32_shift_left(v___x_1101_, v___y_1095_);
v___x_1103_ = lean_uint32_lor(v___y_1100_, v___x_1102_);
v___x_1104_ = lean_uint32_land(v___y_1096_, v___y_1099_);
v___x_1105_ = lean_uint32_lor(v___x_1103_, v___x_1104_);
return v___x_1105_;
}
v___jp_1106_:
{
lean_object* v___x_1107_; lean_object* v___x_1108_; lean_object* v___x_1109_; uint32_t v___x_1110_; 
v___x_1107_ = lean_uint32_to_nat(v___y_1092_);
v___x_1108_ = lean_uint32_to_nat(v___y_1093_);
v___x_1109_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1107_, v___x_1108_);
v___x_1110_ = lean_uint32_of_nat(v___x_1109_);
lean_dec(v___x_1109_);
return v___x_1110_;
}
v___jp_1111_:
{
if (v___y_1112_ == 0)
{
goto v___jp_1106_;
}
else
{
uint32_t v___x_1113_; uint32_t v___x_1114_; 
v___x_1113_ = 4194304;
v___x_1114_ = lean_uint32_lor(v___y_1093_, v___x_1113_);
return v___x_1114_;
}
}
v___jp_1115_:
{
uint32_t v___x_1116_; uint32_t v___x_1117_; uint32_t v___x_1118_; uint32_t v___x_1119_; uint8_t v___x_1120_; 
v___x_1116_ = 23;
v___x_1117_ = lean_uint32_shift_right(v___y_1093_, v___x_1116_);
v___x_1118_ = 255;
v___x_1119_ = lean_uint32_land(v___x_1117_, v___x_1118_);
v___x_1120_ = lean_uint32_dec_eq(v___x_1119_, v___x_1118_);
if (v___x_1120_ == 0)
{
v___y_1112_ = v___x_1120_;
goto v___jp_1111_;
}
else
{
uint32_t v___x_1121_; uint32_t v___x_1122_; uint32_t v___x_1123_; uint8_t v___x_1124_; 
v___x_1121_ = 8388607;
v___x_1122_ = lean_uint32_land(v___y_1093_, v___x_1121_);
v___x_1123_ = 0;
v___x_1124_ = lean_uint32_dec_eq(v___x_1122_, v___x_1123_);
if (v___x_1124_ == 0)
{
v___y_1112_ = v___x_1120_;
goto v___jp_1111_;
}
else
{
goto v___jp_1106_;
}
}
}
v___jp_1125_:
{
if (v___y_1126_ == 0)
{
goto v___jp_1115_;
}
else
{
uint32_t v___x_1127_; uint32_t v___x_1128_; 
v___x_1127_ = 4194304;
v___x_1128_ = lean_uint32_lor(v___y_1092_, v___x_1127_);
return v___x_1128_;
}
}
v___jp_1129_:
{
uint32_t v___x_1130_; uint32_t v___x_1131_; uint32_t v___x_1132_; uint32_t v___x_1133_; uint8_t v___x_1134_; 
v___x_1130_ = 23;
v___x_1131_ = lean_uint32_shift_right(v___y_1092_, v___x_1130_);
v___x_1132_ = 255;
v___x_1133_ = lean_uint32_land(v___x_1131_, v___x_1132_);
v___x_1134_ = lean_uint32_dec_eq(v___x_1133_, v___x_1132_);
if (v___x_1134_ == 0)
{
v___y_1126_ = v___x_1134_;
goto v___jp_1125_;
}
else
{
uint32_t v___x_1135_; uint32_t v___x_1136_; uint32_t v___x_1137_; uint8_t v___x_1138_; 
v___x_1135_ = 8388607;
v___x_1136_ = lean_uint32_land(v___y_1092_, v___x_1135_);
v___x_1137_ = 0;
v___x_1138_ = lean_uint32_dec_eq(v___x_1136_, v___x_1137_);
if (v___x_1138_ == 0)
{
v___y_1126_ = v___x_1134_;
goto v___jp_1125_;
}
else
{
goto v___jp_1115_;
}
}
}
v___jp_1139_:
{
if (v___y_1140_ == 0)
{
goto v___jp_1129_;
}
else
{
uint32_t v___x_1141_; uint32_t v___x_1142_; uint32_t v___x_1143_; uint8_t v___x_1144_; 
v___x_1141_ = 4194304;
v___x_1142_ = lean_uint32_land(v___y_1093_, v___x_1141_);
v___x_1143_ = 0;
v___x_1144_ = lean_uint32_dec_eq(v___x_1142_, v___x_1143_);
if (v___x_1144_ == 0)
{
goto v___jp_1129_;
}
else
{
uint32_t v___x_1145_; 
v___x_1145_ = lean_uint32_lor(v___y_1093_, v___x_1141_);
return v___x_1145_;
}
}
}
v___jp_1146_:
{
uint32_t v___x_1147_; uint32_t v___x_1148_; uint32_t v___x_1149_; uint32_t v___x_1150_; uint8_t v___x_1151_; 
v___x_1147_ = 23;
v___x_1148_ = lean_uint32_shift_right(v___y_1093_, v___x_1147_);
v___x_1149_ = 255;
v___x_1150_ = lean_uint32_land(v___x_1148_, v___x_1149_);
v___x_1151_ = lean_uint32_dec_eq(v___x_1150_, v___x_1149_);
if (v___x_1151_ == 0)
{
v___y_1140_ = v___x_1151_;
goto v___jp_1139_;
}
else
{
uint32_t v___x_1152_; uint32_t v___x_1153_; uint32_t v___x_1154_; uint8_t v___x_1155_; 
v___x_1152_ = 8388607;
v___x_1153_ = lean_uint32_land(v___y_1093_, v___x_1152_);
v___x_1154_ = 0;
v___x_1155_ = lean_uint32_dec_eq(v___x_1153_, v___x_1154_);
if (v___x_1155_ == 0)
{
v___y_1140_ = v___x_1151_;
goto v___jp_1139_;
}
else
{
goto v___jp_1129_;
}
}
}
v___jp_1156_:
{
if (v___y_1157_ == 0)
{
goto v___jp_1146_;
}
else
{
uint32_t v___x_1158_; uint32_t v___x_1159_; uint32_t v___x_1160_; uint8_t v___x_1161_; 
v___x_1158_ = 4194304;
v___x_1159_ = lean_uint32_land(v___y_1092_, v___x_1158_);
v___x_1160_ = 0;
v___x_1161_ = lean_uint32_dec_eq(v___x_1159_, v___x_1160_);
if (v___x_1161_ == 0)
{
goto v___jp_1146_;
}
else
{
uint32_t v___x_1162_; 
v___x_1162_ = lean_uint32_lor(v___y_1092_, v___x_1158_);
return v___x_1162_;
}
}
}
v___jp_1163_:
{
float v_result_1166_; uint8_t v___x_1167_; 
v_result_1166_ = lean_float32_add(v___y_1164_, v___y_1165_);
v___x_1167_ = lean_float32_beq(v_result_1166_, v_result_1166_);
if (v___x_1167_ == 0)
{
uint32_t v___x_1168_; uint32_t v___x_1169_; uint32_t v___x_1170_; uint32_t v___x_1171_; uint8_t v___x_1172_; 
v___x_1168_ = 23;
v___x_1169_ = lean_uint32_shift_right(v___y_1092_, v___x_1168_);
v___x_1170_ = 255;
v___x_1171_ = lean_uint32_land(v___x_1169_, v___x_1170_);
v___x_1172_ = lean_uint32_dec_eq(v___x_1171_, v___x_1170_);
if (v___x_1172_ == 0)
{
v___y_1157_ = v___x_1172_;
goto v___jp_1156_;
}
else
{
uint32_t v___x_1173_; uint32_t v___x_1174_; uint32_t v___x_1175_; uint8_t v___x_1176_; 
v___x_1173_ = 8388607;
v___x_1174_ = lean_uint32_land(v___y_1092_, v___x_1173_);
v___x_1175_ = 0;
v___x_1176_ = lean_uint32_dec_eq(v___x_1174_, v___x_1175_);
if (v___x_1176_ == 0)
{
v___y_1157_ = v___x_1172_;
goto v___jp_1156_;
}
else
{
goto v___jp_1146_;
}
}
}
else
{
uint32_t v___x_1177_; 
v___x_1177_ = lean_float32_to_bits(v_result_1166_);
return v___x_1177_;
}
}
v___jp_1178_:
{
if (v___y_1180_ == 0)
{
float v___x_1181_; 
v___x_1181_ = lean_float32_of_bits(v___y_1093_);
v___y_1164_ = v___y_1179_;
v___y_1165_ = v___x_1181_;
goto v___jp_1163_;
}
else
{
uint32_t v___x_1182_; uint32_t v___x_1183_; uint32_t v___x_1184_; uint32_t v___x_1185_; float v___x_1186_; lean_object* v___x_1187_; uint32_t v___x_1188_; uint32_t v___x_1189_; lean_object* v___x_1190_; lean_object* v___x_1191_; float v___x_1192_; float v___x_1193_; 
v___x_1182_ = 8388607;
v___x_1183_ = lean_uint32_land(v___y_1093_, v___x_1182_);
v___x_1184_ = 8388608;
v___x_1185_ = lean_uint32_lor(v___x_1183_, v___x_1184_);
v___x_1186_ = lean_uint32_to_float32(v___x_1185_);
v___x_1187_ = lp_competition_R2W01b_scaleTable;
v___x_1188_ = 23;
v___x_1189_ = lean_uint32_shift_right(v___y_1093_, v___x_1188_);
v___x_1190_ = lean_uint32_to_nat(v___x_1189_);
v___x_1191_ = lean_array_fget_borrowed(v___x_1187_, v___x_1190_);
lean_dec(v___x_1190_);
v___x_1192_ = lean_unbox_float32(v___x_1191_);
v___x_1193_ = lean_float32_mul(v___x_1186_, v___x_1192_);
v___y_1164_ = v___y_1179_;
v___y_1165_ = v___x_1193_;
goto v___jp_1163_;
}
}
v___jp_1194_:
{
uint32_t v___x_1196_; uint32_t v_a_1197_; uint32_t v___x_1198_; uint32_t v___x_1199_; uint32_t v___x_1200_; uint8_t v___x_1201_; 
v___x_1196_ = 2147483647;
v_a_1197_ = lean_uint32_land(v___y_1093_, v___x_1196_);
v___x_1198_ = 201326591;
v___x_1199_ = 1;
v___x_1200_ = lean_uint32_sub(v_a_1197_, v___x_1199_);
v___x_1201_ = lean_uint32_dec_le(v___x_1198_, v___x_1200_);
if (v___x_1201_ == 0)
{
v___y_1179_ = v___y_1195_;
v___y_1180_ = v___x_1201_;
goto v___jp_1178_;
}
else
{
uint32_t v___x_1202_; uint8_t v___x_1203_; 
v___x_1202_ = 2139095040;
v___x_1203_ = lean_uint32_dec_lt(v_a_1197_, v___x_1202_);
v___y_1179_ = v___y_1195_;
v___y_1180_ = v___x_1203_;
goto v___jp_1178_;
}
}
v___jp_1204_:
{
if (v___y_1205_ == 0)
{
float v___x_1206_; 
v___x_1206_ = lean_float32_of_bits(v___y_1092_);
v___y_1195_ = v___x_1206_;
goto v___jp_1194_;
}
else
{
uint32_t v___x_1207_; uint32_t v___x_1208_; uint32_t v___x_1209_; uint32_t v___x_1210_; float v___x_1211_; lean_object* v___x_1212_; uint32_t v___x_1213_; uint32_t v___x_1214_; lean_object* v___x_1215_; lean_object* v___x_1216_; float v___x_1217_; float v___x_1218_; 
v___x_1207_ = 8388607;
v___x_1208_ = lean_uint32_land(v___y_1092_, v___x_1207_);
v___x_1209_ = 8388608;
v___x_1210_ = lean_uint32_lor(v___x_1208_, v___x_1209_);
v___x_1211_ = lean_uint32_to_float32(v___x_1210_);
v___x_1212_ = lp_competition_R2W01b_scaleTable;
v___x_1213_ = 23;
v___x_1214_ = lean_uint32_shift_right(v___y_1092_, v___x_1213_);
v___x_1215_ = lean_uint32_to_nat(v___x_1214_);
v___x_1216_ = lean_array_fget_borrowed(v___x_1212_, v___x_1215_);
lean_dec(v___x_1215_);
v___x_1217_ = lean_unbox_float32(v___x_1216_);
v___x_1218_ = lean_float32_mul(v___x_1211_, v___x_1217_);
v___y_1195_ = v___x_1218_;
goto v___jp_1194_;
}
}
v___jp_1219_:
{
lean_object* v___x_1220_; lean_object* v___x_1221_; lean_object* v___x_1222_; uint32_t v___x_1223_; 
v___x_1220_ = lean_uint32_to_nat(v___y_1092_);
v___x_1221_ = lean_uint32_to_nat(v___y_1093_);
v___x_1222_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1220_, v___x_1221_);
v___x_1223_ = lean_uint32_of_nat(v___x_1222_);
lean_dec(v___x_1222_);
return v___x_1223_;
}
v___jp_1224_:
{
if (v___y_1225_ == 0)
{
goto v___jp_1219_;
}
else
{
uint32_t v___x_1226_; uint32_t v___x_1227_; 
v___x_1226_ = 4194304;
v___x_1227_ = lean_uint32_lor(v___y_1093_, v___x_1226_);
return v___x_1227_;
}
}
v___jp_1228_:
{
uint32_t v___x_1229_; uint32_t v___x_1230_; uint32_t v___x_1231_; uint32_t v___x_1232_; uint8_t v___x_1233_; 
v___x_1229_ = 23;
v___x_1230_ = lean_uint32_shift_right(v___y_1093_, v___x_1229_);
v___x_1231_ = 255;
v___x_1232_ = lean_uint32_land(v___x_1230_, v___x_1231_);
v___x_1233_ = lean_uint32_dec_eq(v___x_1232_, v___x_1231_);
if (v___x_1233_ == 0)
{
v___y_1225_ = v___x_1233_;
goto v___jp_1224_;
}
else
{
uint32_t v___x_1234_; uint32_t v___x_1235_; uint32_t v___x_1236_; uint8_t v___x_1237_; 
v___x_1234_ = 8388607;
v___x_1235_ = lean_uint32_land(v___y_1093_, v___x_1234_);
v___x_1236_ = 0;
v___x_1237_ = lean_uint32_dec_eq(v___x_1235_, v___x_1236_);
if (v___x_1237_ == 0)
{
v___y_1225_ = v___x_1233_;
goto v___jp_1224_;
}
else
{
goto v___jp_1219_;
}
}
}
v___jp_1238_:
{
if (v___y_1239_ == 0)
{
goto v___jp_1228_;
}
else
{
uint32_t v___x_1240_; uint32_t v___x_1241_; 
v___x_1240_ = 4194304;
v___x_1241_ = lean_uint32_lor(v___y_1092_, v___x_1240_);
return v___x_1241_;
}
}
v___jp_1242_:
{
uint32_t v___x_1243_; uint32_t v___x_1244_; uint32_t v___x_1245_; uint32_t v___x_1246_; uint8_t v___x_1247_; 
v___x_1243_ = 23;
v___x_1244_ = lean_uint32_shift_right(v___y_1092_, v___x_1243_);
v___x_1245_ = 255;
v___x_1246_ = lean_uint32_land(v___x_1244_, v___x_1245_);
v___x_1247_ = lean_uint32_dec_eq(v___x_1246_, v___x_1245_);
if (v___x_1247_ == 0)
{
v___y_1239_ = v___x_1247_;
goto v___jp_1238_;
}
else
{
uint32_t v___x_1248_; uint32_t v___x_1249_; uint32_t v___x_1250_; uint8_t v___x_1251_; 
v___x_1248_ = 8388607;
v___x_1249_ = lean_uint32_land(v___y_1092_, v___x_1248_);
v___x_1250_ = 0;
v___x_1251_ = lean_uint32_dec_eq(v___x_1249_, v___x_1250_);
if (v___x_1251_ == 0)
{
v___y_1239_ = v___x_1247_;
goto v___jp_1238_;
}
else
{
goto v___jp_1228_;
}
}
}
v___jp_1252_:
{
if (v___y_1253_ == 0)
{
goto v___jp_1242_;
}
else
{
uint32_t v___x_1254_; uint32_t v___x_1255_; uint32_t v___x_1256_; uint8_t v___x_1257_; 
v___x_1254_ = 4194304;
v___x_1255_ = lean_uint32_land(v___y_1093_, v___x_1254_);
v___x_1256_ = 0;
v___x_1257_ = lean_uint32_dec_eq(v___x_1255_, v___x_1256_);
if (v___x_1257_ == 0)
{
goto v___jp_1242_;
}
else
{
uint32_t v___x_1258_; 
v___x_1258_ = lean_uint32_lor(v___y_1093_, v___x_1254_);
return v___x_1258_;
}
}
}
v___jp_1259_:
{
uint32_t v___x_1260_; uint32_t v___x_1261_; uint32_t v___x_1262_; uint32_t v___x_1263_; uint8_t v___x_1264_; 
v___x_1260_ = 23;
v___x_1261_ = lean_uint32_shift_right(v___y_1093_, v___x_1260_);
v___x_1262_ = 255;
v___x_1263_ = lean_uint32_land(v___x_1261_, v___x_1262_);
v___x_1264_ = lean_uint32_dec_eq(v___x_1263_, v___x_1262_);
if (v___x_1264_ == 0)
{
v___y_1253_ = v___x_1264_;
goto v___jp_1252_;
}
else
{
uint32_t v___x_1265_; uint32_t v___x_1266_; uint32_t v___x_1267_; uint8_t v___x_1268_; 
v___x_1265_ = 8388607;
v___x_1266_ = lean_uint32_land(v___y_1093_, v___x_1265_);
v___x_1267_ = 0;
v___x_1268_ = lean_uint32_dec_eq(v___x_1266_, v___x_1267_);
if (v___x_1268_ == 0)
{
v___y_1253_ = v___x_1264_;
goto v___jp_1252_;
}
else
{
goto v___jp_1242_;
}
}
}
v___jp_1269_:
{
if (v___y_1270_ == 0)
{
goto v___jp_1259_;
}
else
{
uint32_t v___x_1271_; uint32_t v___x_1272_; uint32_t v___x_1273_; uint8_t v___x_1274_; 
v___x_1271_ = 4194304;
v___x_1272_ = lean_uint32_land(v___y_1092_, v___x_1271_);
v___x_1273_ = 0;
v___x_1274_ = lean_uint32_dec_eq(v___x_1272_, v___x_1273_);
if (v___x_1274_ == 0)
{
goto v___jp_1259_;
}
else
{
uint32_t v___x_1275_; 
v___x_1275_ = lean_uint32_lor(v___y_1092_, v___x_1271_);
return v___x_1275_;
}
}
}
v___jp_1276_:
{
float v_result_1279_; uint8_t v___x_1280_; 
v_result_1279_ = lean_float32_add(v___y_1277_, v___y_1278_);
v___x_1280_ = lean_float32_beq(v_result_1279_, v_result_1279_);
if (v___x_1280_ == 0)
{
uint32_t v___x_1281_; uint32_t v___x_1282_; uint32_t v___x_1283_; uint32_t v___x_1284_; uint8_t v___x_1285_; 
v___x_1281_ = 23;
v___x_1282_ = lean_uint32_shift_right(v___y_1092_, v___x_1281_);
v___x_1283_ = 255;
v___x_1284_ = lean_uint32_land(v___x_1282_, v___x_1283_);
v___x_1285_ = lean_uint32_dec_eq(v___x_1284_, v___x_1283_);
if (v___x_1285_ == 0)
{
v___y_1270_ = v___x_1285_;
goto v___jp_1269_;
}
else
{
uint32_t v___x_1286_; uint32_t v___x_1287_; uint32_t v___x_1288_; uint8_t v___x_1289_; 
v___x_1286_ = 8388607;
v___x_1287_ = lean_uint32_land(v___y_1092_, v___x_1286_);
v___x_1288_ = 0;
v___x_1289_ = lean_uint32_dec_eq(v___x_1287_, v___x_1288_);
if (v___x_1289_ == 0)
{
v___y_1270_ = v___x_1285_;
goto v___jp_1269_;
}
else
{
goto v___jp_1259_;
}
}
}
else
{
uint32_t v___x_1290_; 
v___x_1290_ = lean_float32_to_bits(v_result_1279_);
return v___x_1290_;
}
}
v___jp_1291_:
{
if (v___y_1293_ == 0)
{
float v___x_1294_; 
v___x_1294_ = lean_float32_of_bits(v___y_1093_);
v___y_1277_ = v___y_1292_;
v___y_1278_ = v___x_1294_;
goto v___jp_1276_;
}
else
{
uint32_t v___x_1295_; uint32_t v___x_1296_; uint32_t v___x_1297_; uint32_t v___x_1298_; float v___x_1299_; lean_object* v___x_1300_; uint32_t v___x_1301_; uint32_t v___x_1302_; lean_object* v___x_1303_; lean_object* v___x_1304_; float v___x_1305_; float v___x_1306_; 
v___x_1295_ = 8388607;
v___x_1296_ = lean_uint32_land(v___y_1093_, v___x_1295_);
v___x_1297_ = 8388608;
v___x_1298_ = lean_uint32_lor(v___x_1296_, v___x_1297_);
v___x_1299_ = lean_uint32_to_float32(v___x_1298_);
v___x_1300_ = lp_competition_R2W01b_scaleTable;
v___x_1301_ = 23;
v___x_1302_ = lean_uint32_shift_right(v___y_1093_, v___x_1301_);
v___x_1303_ = lean_uint32_to_nat(v___x_1302_);
v___x_1304_ = lean_array_fget_borrowed(v___x_1300_, v___x_1303_);
lean_dec(v___x_1303_);
v___x_1305_ = lean_unbox_float32(v___x_1304_);
v___x_1306_ = lean_float32_mul(v___x_1299_, v___x_1305_);
v___y_1277_ = v___y_1292_;
v___y_1278_ = v___x_1306_;
goto v___jp_1276_;
}
}
v___jp_1307_:
{
uint32_t v___x_1309_; uint32_t v_a_1310_; uint32_t v___x_1311_; uint32_t v___x_1312_; uint32_t v___x_1313_; uint8_t v___x_1314_; 
v___x_1309_ = 2147483647;
v_a_1310_ = lean_uint32_land(v___y_1093_, v___x_1309_);
v___x_1311_ = 201326591;
v___x_1312_ = 1;
v___x_1313_ = lean_uint32_sub(v_a_1310_, v___x_1312_);
v___x_1314_ = lean_uint32_dec_le(v___x_1311_, v___x_1313_);
if (v___x_1314_ == 0)
{
v___y_1292_ = v___y_1308_;
v___y_1293_ = v___x_1314_;
goto v___jp_1291_;
}
else
{
uint32_t v___x_1315_; uint8_t v___x_1316_; 
v___x_1315_ = 2139095040;
v___x_1316_ = lean_uint32_dec_lt(v_a_1310_, v___x_1315_);
v___y_1292_ = v___y_1308_;
v___y_1293_ = v___x_1316_;
goto v___jp_1291_;
}
}
v___jp_1317_:
{
if (v___y_1318_ == 0)
{
float v___x_1319_; 
v___x_1319_ = lean_float32_of_bits(v___y_1092_);
v___y_1308_ = v___x_1319_;
goto v___jp_1307_;
}
else
{
uint32_t v___x_1320_; uint32_t v___x_1321_; uint32_t v___x_1322_; uint32_t v___x_1323_; float v___x_1324_; lean_object* v___x_1325_; uint32_t v___x_1326_; uint32_t v___x_1327_; lean_object* v___x_1328_; lean_object* v___x_1329_; float v___x_1330_; float v___x_1331_; 
v___x_1320_ = 8388607;
v___x_1321_ = lean_uint32_land(v___y_1092_, v___x_1320_);
v___x_1322_ = 8388608;
v___x_1323_ = lean_uint32_lor(v___x_1321_, v___x_1322_);
v___x_1324_ = lean_uint32_to_float32(v___x_1323_);
v___x_1325_ = lp_competition_R2W01b_scaleTable;
v___x_1326_ = 23;
v___x_1327_ = lean_uint32_shift_right(v___y_1092_, v___x_1326_);
v___x_1328_ = lean_uint32_to_nat(v___x_1327_);
v___x_1329_ = lean_array_fget_borrowed(v___x_1325_, v___x_1328_);
lean_dec(v___x_1328_);
v___x_1330_ = lean_unbox_float32(v___x_1329_);
v___x_1331_ = lean_float32_mul(v___x_1324_, v___x_1330_);
v___y_1308_ = v___x_1331_;
goto v___jp_1307_;
}
}
v___jp_1332_:
{
lean_object* v___x_1333_; lean_object* v___x_1334_; lean_object* v___x_1335_; uint32_t v___x_1336_; 
v___x_1333_ = lean_uint32_to_nat(v___y_1092_);
v___x_1334_ = lean_uint32_to_nat(v___y_1093_);
v___x_1335_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1333_, v___x_1334_);
v___x_1336_ = lean_uint32_of_nat(v___x_1335_);
lean_dec(v___x_1335_);
return v___x_1336_;
}
v___jp_1337_:
{
if (v___y_1338_ == 0)
{
goto v___jp_1332_;
}
else
{
uint32_t v___x_1339_; uint32_t v___x_1340_; 
v___x_1339_ = 4194304;
v___x_1340_ = lean_uint32_lor(v___y_1093_, v___x_1339_);
return v___x_1340_;
}
}
v___jp_1341_:
{
uint32_t v___x_1342_; uint32_t v___x_1343_; uint32_t v___x_1344_; uint32_t v___x_1345_; uint8_t v___x_1346_; 
v___x_1342_ = 23;
v___x_1343_ = lean_uint32_shift_right(v___y_1093_, v___x_1342_);
v___x_1344_ = 255;
v___x_1345_ = lean_uint32_land(v___x_1343_, v___x_1344_);
v___x_1346_ = lean_uint32_dec_eq(v___x_1345_, v___x_1344_);
if (v___x_1346_ == 0)
{
v___y_1338_ = v___x_1346_;
goto v___jp_1337_;
}
else
{
uint32_t v___x_1347_; uint32_t v___x_1348_; uint32_t v___x_1349_; uint8_t v___x_1350_; 
v___x_1347_ = 8388607;
v___x_1348_ = lean_uint32_land(v___y_1093_, v___x_1347_);
v___x_1349_ = 0;
v___x_1350_ = lean_uint32_dec_eq(v___x_1348_, v___x_1349_);
if (v___x_1350_ == 0)
{
v___y_1338_ = v___x_1346_;
goto v___jp_1337_;
}
else
{
goto v___jp_1332_;
}
}
}
v___jp_1351_:
{
if (v___y_1352_ == 0)
{
goto v___jp_1341_;
}
else
{
uint32_t v___x_1353_; uint32_t v___x_1354_; 
v___x_1353_ = 4194304;
v___x_1354_ = lean_uint32_lor(v___y_1092_, v___x_1353_);
return v___x_1354_;
}
}
v___jp_1355_:
{
uint32_t v___x_1356_; uint32_t v___x_1357_; uint32_t v___x_1358_; uint32_t v___x_1359_; uint8_t v___x_1360_; 
v___x_1356_ = 23;
v___x_1357_ = lean_uint32_shift_right(v___y_1092_, v___x_1356_);
v___x_1358_ = 255;
v___x_1359_ = lean_uint32_land(v___x_1357_, v___x_1358_);
v___x_1360_ = lean_uint32_dec_eq(v___x_1359_, v___x_1358_);
if (v___x_1360_ == 0)
{
v___y_1352_ = v___x_1360_;
goto v___jp_1351_;
}
else
{
uint32_t v___x_1361_; uint32_t v___x_1362_; uint32_t v___x_1363_; uint8_t v___x_1364_; 
v___x_1361_ = 8388607;
v___x_1362_ = lean_uint32_land(v___y_1092_, v___x_1361_);
v___x_1363_ = 0;
v___x_1364_ = lean_uint32_dec_eq(v___x_1362_, v___x_1363_);
if (v___x_1364_ == 0)
{
v___y_1352_ = v___x_1360_;
goto v___jp_1351_;
}
else
{
goto v___jp_1341_;
}
}
}
v___jp_1365_:
{
if (v___y_1366_ == 0)
{
goto v___jp_1355_;
}
else
{
uint32_t v___x_1367_; uint32_t v___x_1368_; uint32_t v___x_1369_; uint8_t v___x_1370_; 
v___x_1367_ = 4194304;
v___x_1368_ = lean_uint32_land(v___y_1093_, v___x_1367_);
v___x_1369_ = 0;
v___x_1370_ = lean_uint32_dec_eq(v___x_1368_, v___x_1369_);
if (v___x_1370_ == 0)
{
goto v___jp_1355_;
}
else
{
uint32_t v___x_1371_; 
v___x_1371_ = lean_uint32_lor(v___y_1093_, v___x_1367_);
return v___x_1371_;
}
}
}
v___jp_1372_:
{
uint32_t v___x_1373_; uint32_t v___x_1374_; uint32_t v___x_1375_; uint32_t v___x_1376_; uint8_t v___x_1377_; 
v___x_1373_ = 23;
v___x_1374_ = lean_uint32_shift_right(v___y_1093_, v___x_1373_);
v___x_1375_ = 255;
v___x_1376_ = lean_uint32_land(v___x_1374_, v___x_1375_);
v___x_1377_ = lean_uint32_dec_eq(v___x_1376_, v___x_1375_);
if (v___x_1377_ == 0)
{
v___y_1366_ = v___x_1377_;
goto v___jp_1365_;
}
else
{
uint32_t v___x_1378_; uint32_t v___x_1379_; uint32_t v___x_1380_; uint8_t v___x_1381_; 
v___x_1378_ = 8388607;
v___x_1379_ = lean_uint32_land(v___y_1093_, v___x_1378_);
v___x_1380_ = 0;
v___x_1381_ = lean_uint32_dec_eq(v___x_1379_, v___x_1380_);
if (v___x_1381_ == 0)
{
v___y_1366_ = v___x_1377_;
goto v___jp_1365_;
}
else
{
goto v___jp_1355_;
}
}
}
v___jp_1382_:
{
if (v___y_1383_ == 0)
{
goto v___jp_1372_;
}
else
{
uint32_t v___x_1384_; uint32_t v___x_1385_; uint32_t v___x_1386_; uint8_t v___x_1387_; 
v___x_1384_ = 4194304;
v___x_1385_ = lean_uint32_land(v___y_1092_, v___x_1384_);
v___x_1386_ = 0;
v___x_1387_ = lean_uint32_dec_eq(v___x_1385_, v___x_1386_);
if (v___x_1387_ == 0)
{
goto v___jp_1372_;
}
else
{
uint32_t v___x_1388_; 
v___x_1388_ = lean_uint32_lor(v___y_1092_, v___x_1384_);
return v___x_1388_;
}
}
}
v___jp_1389_:
{
float v_result_1392_; uint8_t v___x_1393_; 
v_result_1392_ = lean_float32_add(v___y_1390_, v___y_1391_);
v___x_1393_ = lean_float32_beq(v_result_1392_, v_result_1392_);
if (v___x_1393_ == 0)
{
uint32_t v___x_1394_; uint32_t v___x_1395_; uint32_t v___x_1396_; uint32_t v___x_1397_; uint8_t v___x_1398_; 
v___x_1394_ = 23;
v___x_1395_ = lean_uint32_shift_right(v___y_1092_, v___x_1394_);
v___x_1396_ = 255;
v___x_1397_ = lean_uint32_land(v___x_1395_, v___x_1396_);
v___x_1398_ = lean_uint32_dec_eq(v___x_1397_, v___x_1396_);
if (v___x_1398_ == 0)
{
v___y_1383_ = v___x_1398_;
goto v___jp_1382_;
}
else
{
uint32_t v___x_1399_; uint32_t v___x_1400_; uint32_t v___x_1401_; uint8_t v___x_1402_; 
v___x_1399_ = 8388607;
v___x_1400_ = lean_uint32_land(v___y_1092_, v___x_1399_);
v___x_1401_ = 0;
v___x_1402_ = lean_uint32_dec_eq(v___x_1400_, v___x_1401_);
if (v___x_1402_ == 0)
{
v___y_1383_ = v___x_1398_;
goto v___jp_1382_;
}
else
{
goto v___jp_1372_;
}
}
}
else
{
uint32_t v___x_1403_; 
v___x_1403_ = lean_float32_to_bits(v_result_1392_);
return v___x_1403_;
}
}
v___jp_1404_:
{
if (v___y_1406_ == 0)
{
float v___x_1407_; 
v___x_1407_ = lean_float32_of_bits(v___y_1093_);
v___y_1390_ = v___y_1405_;
v___y_1391_ = v___x_1407_;
goto v___jp_1389_;
}
else
{
uint32_t v___x_1408_; uint32_t v___x_1409_; uint32_t v___x_1410_; uint32_t v___x_1411_; float v___x_1412_; lean_object* v___x_1413_; uint32_t v___x_1414_; uint32_t v___x_1415_; lean_object* v___x_1416_; lean_object* v___x_1417_; float v___x_1418_; float v___x_1419_; 
v___x_1408_ = 8388607;
v___x_1409_ = lean_uint32_land(v___y_1093_, v___x_1408_);
v___x_1410_ = 8388608;
v___x_1411_ = lean_uint32_lor(v___x_1409_, v___x_1410_);
v___x_1412_ = lean_uint32_to_float32(v___x_1411_);
v___x_1413_ = lp_competition_R2W01b_scaleTable;
v___x_1414_ = 23;
v___x_1415_ = lean_uint32_shift_right(v___y_1093_, v___x_1414_);
v___x_1416_ = lean_uint32_to_nat(v___x_1415_);
v___x_1417_ = lean_array_fget_borrowed(v___x_1413_, v___x_1416_);
lean_dec(v___x_1416_);
v___x_1418_ = lean_unbox_float32(v___x_1417_);
v___x_1419_ = lean_float32_mul(v___x_1412_, v___x_1418_);
v___y_1390_ = v___y_1405_;
v___y_1391_ = v___x_1419_;
goto v___jp_1389_;
}
}
v___jp_1420_:
{
uint32_t v___x_1422_; uint32_t v_a_1423_; uint32_t v___x_1424_; uint32_t v___x_1425_; uint32_t v___x_1426_; uint8_t v___x_1427_; 
v___x_1422_ = 2147483647;
v_a_1423_ = lean_uint32_land(v___y_1093_, v___x_1422_);
v___x_1424_ = 201326591;
v___x_1425_ = 1;
v___x_1426_ = lean_uint32_sub(v_a_1423_, v___x_1425_);
v___x_1427_ = lean_uint32_dec_le(v___x_1424_, v___x_1426_);
if (v___x_1427_ == 0)
{
v___y_1405_ = v___y_1421_;
v___y_1406_ = v___x_1427_;
goto v___jp_1404_;
}
else
{
uint32_t v___x_1428_; uint8_t v___x_1429_; 
v___x_1428_ = 2139095040;
v___x_1429_ = lean_uint32_dec_lt(v_a_1423_, v___x_1428_);
v___y_1405_ = v___y_1421_;
v___y_1406_ = v___x_1429_;
goto v___jp_1404_;
}
}
v___jp_1430_:
{
if (v___y_1434_ == 0)
{
float v___x_1435_; 
v___x_1435_ = lean_float32_of_bits(v___y_1092_);
v___y_1421_ = v___x_1435_;
goto v___jp_1420_;
}
else
{
uint32_t v___x_1436_; uint32_t v___x_1437_; float v___x_1438_; lean_object* v___x_1439_; uint32_t v___x_1440_; lean_object* v___x_1441_; lean_object* v___x_1442_; float v___x_1443_; float v___x_1444_; 
v___x_1436_ = lean_uint32_land(v___y_1092_, v___y_1433_);
v___x_1437_ = lean_uint32_lor(v___x_1436_, v___y_1432_);
v___x_1438_ = lean_uint32_to_float32(v___x_1437_);
v___x_1439_ = lp_competition_R2W01b_scaleTable;
v___x_1440_ = lean_uint32_shift_right(v___y_1092_, v___y_1431_);
v___x_1441_ = lean_uint32_to_nat(v___x_1440_);
v___x_1442_ = lean_array_fget_borrowed(v___x_1439_, v___x_1441_);
lean_dec(v___x_1441_);
v___x_1443_ = lean_unbox_float32(v___x_1442_);
v___x_1444_ = lean_float32_mul(v___x_1438_, v___x_1443_);
v___y_1421_ = v___x_1444_;
goto v___jp_1420_;
}
}
v___jp_1445_:
{
uint32_t v_base_1455_; uint32_t v___x_1456_; uint32_t v___x_1457_; uint32_t v___x_1458_; uint32_t v_h_1459_; uint64_t v___x_1460_; uint32_t v___x_1461_; uint64_t v___x_1462_; uint64_t v___x_1463_; uint64_t v___x_1464_; uint64_t v___x_1465_; uint64_t v___x_1466_; uint64_t v___x_1467_; uint64_t v___x_1468_; uint64_t v___x_1469_; uint64_t v___x_1470_; uint64_t v_q_1471_; uint32_t v___x_1472_; uint32_t v___x_1473_; uint64_t v___x_1474_; uint64_t v___x_1475_; uint32_t v___x_1476_; uint32_t v_e_1477_; uint32_t v___x_1478_; uint32_t v___x_1479_; uint8_t v___x_1480_; 
v_base_1455_ = lean_uint32_add(v___y_1454_, v___y_1453_);
v___x_1456_ = 1;
v___x_1457_ = lean_uint32_add(v_base_1455_, v___x_1456_);
v___x_1458_ = lean_uint32_shift_right(v___y_1447_, v___x_1457_);
v_h_1459_ = lean_uint32_add(v_base_1455_, v___x_1458_);
v___x_1460_ = lean_uint32_to_uint64(v___y_1447_);
v___x_1461_ = lean_uint32_sub(v_h_1459_, v___y_1446_);
v___x_1462_ = lean_uint32_to_uint64(v___x_1461_);
v___x_1463_ = 1ULL;
v___x_1464_ = lean_uint64_sub(v___x_1462_, v___x_1463_);
v___x_1465_ = lean_uint64_shift_left(v___x_1463_, v___x_1464_);
v___x_1466_ = lean_uint64_add(v___x_1460_, v___x_1465_);
v___x_1467_ = lean_uint64_sub(v___x_1466_, v___x_1463_);
v___x_1468_ = lean_uint64_shift_right(v___x_1460_, v___x_1462_);
v___x_1469_ = lean_uint64_land(v___x_1468_, v___x_1463_);
v___x_1470_ = lean_uint64_add(v___x_1467_, v___x_1469_);
v_q_1471_ = lean_uint64_shift_right(v___x_1470_, v___x_1462_);
v___x_1472_ = lean_uint32_add(v_h_1459_, v___y_1449_);
v___x_1473_ = lean_uint32_sub(v___x_1472_, v___y_1446_);
v___x_1474_ = 24ULL;
v___x_1475_ = lean_uint64_shift_right(v_q_1471_, v___x_1474_);
v___x_1476_ = lean_uint64_to_uint32(v___x_1475_);
v_e_1477_ = lean_uint32_add(v___x_1473_, v___x_1476_);
v___x_1478_ = lean_uint32_sub(v_e_1477_, v___x_1456_);
v___x_1479_ = 253;
v___x_1480_ = lean_uint32_dec_le(v___x_1478_, v___x_1479_);
if (v___x_1480_ == 0)
{
uint32_t v___x_1481_; uint32_t v_a_1482_; uint32_t v___x_1483_; uint32_t v___x_1484_; uint8_t v___x_1485_; 
v___x_1481_ = 2147483647;
v_a_1482_ = lean_uint32_land(v___y_1092_, v___x_1481_);
v___x_1483_ = 201326591;
v___x_1484_ = lean_uint32_sub(v_a_1482_, v___x_1456_);
v___x_1485_ = lean_uint32_dec_le(v___x_1483_, v___x_1484_);
if (v___x_1485_ == 0)
{
v___y_1431_ = v___y_1446_;
v___y_1432_ = v___y_1450_;
v___y_1433_ = v___y_1452_;
v___y_1434_ = v___x_1485_;
goto v___jp_1430_;
}
else
{
uint32_t v___x_1486_; uint8_t v___x_1487_; 
v___x_1486_ = 2139095040;
v___x_1487_ = lean_uint32_dec_lt(v_a_1482_, v___x_1486_);
v___y_1431_ = v___y_1446_;
v___y_1432_ = v___y_1450_;
v___y_1433_ = v___y_1452_;
v___y_1434_ = v___x_1487_;
goto v___jp_1430_;
}
}
else
{
uint32_t v___x_1488_; uint8_t v___x_1489_; uint32_t v___x_1490_; uint32_t v___x_1491_; 
v___x_1488_ = 2147483648;
v___x_1489_ = lean_uint32_dec_le(v___x_1488_, v___y_1448_);
v___x_1490_ = lean_uint64_to_uint32(v_q_1471_);
v___x_1491_ = lean_uint32_land(v___x_1490_, v___y_1452_);
if (v___x_1489_ == 0)
{
uint32_t v___x_1492_; 
v___x_1492_ = 0;
v___y_1095_ = v___y_1446_;
v___y_1096_ = v___x_1491_;
v___y_1097_ = v_e_1477_;
v___y_1098_ = v___y_1451_;
v___y_1099_ = v___y_1452_;
v___y_1100_ = v___x_1492_;
goto v___jp_1094_;
}
else
{
v___y_1095_ = v___y_1446_;
v___y_1096_ = v___x_1491_;
v___y_1097_ = v_e_1477_;
v___y_1098_ = v___y_1451_;
v___y_1099_ = v___y_1452_;
v___y_1100_ = v___x_1488_;
goto v___jp_1094_;
}
}
}
v___jp_1493_:
{
uint32_t v___x_1501_; uint32_t v___x_1502_; uint32_t v___x_1503_; uint32_t v___x_1504_; uint32_t v_left_1505_; uint32_t v___x_1506_; uint32_t v_right_1507_; 
v___x_1501_ = 8388607;
v___x_1502_ = lean_uint32_land(v___y_1497_, v___x_1501_);
v___x_1503_ = 8388608;
v___x_1504_ = lean_uint32_lor(v___x_1502_, v___x_1503_);
v_left_1505_ = lean_uint32_shift_left(v___x_1504_, v___y_1499_);
v___x_1506_ = lean_uint32_land(v___y_1495_, v___x_1501_);
v_right_1507_ = lean_uint32_lor(v___x_1506_, v___x_1503_);
if (v___y_1500_ == 0)
{
uint32_t v___x_1508_; uint32_t v___x_1509_; 
v___x_1508_ = lean_uint32_sub(v_left_1505_, v_right_1507_);
v___x_1509_ = 22;
v___y_1446_ = v___y_1494_;
v___y_1447_ = v___x_1508_;
v___y_1448_ = v___y_1497_;
v___y_1449_ = v___y_1496_;
v___y_1450_ = v___x_1503_;
v___y_1451_ = v___y_1498_;
v___y_1452_ = v___x_1501_;
v___y_1453_ = v___y_1499_;
v___y_1454_ = v___x_1509_;
goto v___jp_1445_;
}
else
{
uint32_t v___x_1510_; 
v___x_1510_ = lean_uint32_add(v_left_1505_, v_right_1507_);
v___y_1446_ = v___y_1494_;
v___y_1447_ = v___x_1510_;
v___y_1448_ = v___y_1497_;
v___y_1449_ = v___y_1496_;
v___y_1450_ = v___x_1503_;
v___y_1451_ = v___y_1498_;
v___y_1452_ = v___x_1501_;
v___y_1453_ = v___y_1499_;
v___y_1454_ = v___y_1494_;
goto v___jp_1445_;
}
}
v___jp_1511_:
{
uint32_t v___x_1515_; uint32_t v___x_1516_; uint32_t v___x_1517_; uint32_t v___x_1518_; uint32_t v___x_1519_; uint32_t v___x_1520_; uint32_t v_d_1521_; uint32_t v___x_1522_; uint8_t v___x_1523_; uint8_t v___x_1524_; 
v___x_1515_ = 23;
v___x_1516_ = lean_uint32_shift_right(v___y_1512_, v___x_1515_);
v___x_1517_ = 255;
v___x_1518_ = lean_uint32_land(v___x_1516_, v___x_1517_);
v___x_1519_ = lean_uint32_shift_right(v___y_1514_, v___x_1515_);
v___x_1520_ = lean_uint32_land(v___x_1519_, v___x_1517_);
v_d_1521_ = lean_uint32_sub(v___x_1518_, v___x_1520_);
v___x_1522_ = 2147483648;
v___x_1523_ = lean_uint32_dec_le(v___x_1522_, v___y_1092_);
v___x_1524_ = lean_uint32_dec_le(v___x_1522_, v___y_1093_);
if (v___x_1523_ == 0)
{
if (v___x_1524_ == 0)
{
v___y_1494_ = v___x_1515_;
v___y_1495_ = v___y_1514_;
v___y_1496_ = v___x_1520_;
v___y_1497_ = v___y_1512_;
v___y_1498_ = v___x_1517_;
v___y_1499_ = v_d_1521_;
v___y_1500_ = v___y_1513_;
goto v___jp_1493_;
}
else
{
v___y_1494_ = v___x_1515_;
v___y_1495_ = v___y_1514_;
v___y_1496_ = v___x_1520_;
v___y_1497_ = v___y_1512_;
v___y_1498_ = v___x_1517_;
v___y_1499_ = v_d_1521_;
v___y_1500_ = v___x_1523_;
goto v___jp_1493_;
}
}
else
{
v___y_1494_ = v___x_1515_;
v___y_1495_ = v___y_1514_;
v___y_1496_ = v___x_1520_;
v___y_1497_ = v___y_1512_;
v___y_1498_ = v___x_1517_;
v___y_1499_ = v_d_1521_;
v___y_1500_ = v___x_1524_;
goto v___jp_1493_;
}
}
v___jp_1525_:
{
uint32_t v___x_1528_; uint32_t v___x_1529_; uint32_t v___x_1530_; uint32_t v___x_1531_; uint32_t v___x_1532_; uint32_t v___x_1533_; uint8_t v___x_1534_; 
v___x_1528_ = 23;
v___x_1529_ = lean_uint32_shift_right(v___y_1092_, v___x_1528_);
v___x_1530_ = 255;
v___x_1531_ = lean_uint32_land(v___x_1529_, v___x_1530_);
v___x_1532_ = lean_uint32_shift_right(v___y_1093_, v___x_1528_);
v___x_1533_ = lean_uint32_land(v___x_1532_, v___x_1530_);
v___x_1534_ = lean_uint32_dec_lt(v___x_1531_, v___x_1533_);
if (v___x_1534_ == 0)
{
v___y_1512_ = v___y_1527_;
v___y_1513_ = v___y_1526_;
v___y_1514_ = v___y_1093_;
goto v___jp_1511_;
}
else
{
v___y_1512_ = v___y_1527_;
v___y_1513_ = v___y_1526_;
v___y_1514_ = v___y_1092_;
goto v___jp_1511_;
}
}
v___jp_1535_:
{
uint32_t v___x_1537_; uint32_t v___x_1538_; uint32_t v___x_1539_; uint32_t v___x_1540_; uint32_t v___x_1541_; uint32_t v___x_1542_; uint8_t v___x_1543_; 
v___x_1537_ = 23;
v___x_1538_ = lean_uint32_shift_right(v___y_1092_, v___x_1537_);
v___x_1539_ = 255;
v___x_1540_ = lean_uint32_land(v___x_1538_, v___x_1539_);
v___x_1541_ = lean_uint32_shift_right(v___y_1093_, v___x_1537_);
v___x_1542_ = lean_uint32_land(v___x_1541_, v___x_1539_);
v___x_1543_ = lean_uint32_dec_lt(v___x_1540_, v___x_1542_);
if (v___x_1543_ == 0)
{
v___y_1526_ = v___y_1536_;
v___y_1527_ = v___y_1092_;
goto v___jp_1525_;
}
else
{
v___y_1526_ = v___y_1536_;
v___y_1527_ = v___y_1093_;
goto v___jp_1525_;
}
}
v___jp_1544_:
{
if (v___y_1545_ == 0)
{
uint32_t v___x_1546_; uint32_t v_a_1547_; uint32_t v___x_1548_; uint32_t v___x_1549_; uint32_t v___x_1550_; uint8_t v___x_1551_; 
v___x_1546_ = 2147483647;
v_a_1547_ = lean_uint32_land(v___y_1092_, v___x_1546_);
v___x_1548_ = 201326591;
v___x_1549_ = 1;
v___x_1550_ = lean_uint32_sub(v_a_1547_, v___x_1549_);
v___x_1551_ = lean_uint32_dec_le(v___x_1548_, v___x_1550_);
if (v___x_1551_ == 0)
{
v___y_1318_ = v___x_1551_;
goto v___jp_1317_;
}
else
{
uint32_t v___x_1552_; uint8_t v___x_1553_; 
v___x_1552_ = 2139095040;
v___x_1553_ = lean_uint32_dec_lt(v_a_1547_, v___x_1552_);
v___y_1318_ = v___x_1553_;
goto v___jp_1317_;
}
}
else
{
v___y_1536_ = v___y_1545_;
goto v___jp_1535_;
}
}
v___jp_1554_:
{
uint32_t v___x_1560_; uint32_t v___x_1561_; uint32_t v___x_1562_; uint8_t v___x_1563_; 
v___x_1560_ = lean_uint32_shift_right(v___y_1559_, v___y_1555_);
v___x_1561_ = lean_uint32_land(v___x_1560_, v___y_1558_);
v___x_1562_ = lean_uint32_sub(v___y_1557_, v___x_1561_);
v___x_1563_ = lean_uint32_dec_le(v___y_1556_, v___x_1562_);
v___y_1545_ = v___x_1563_;
goto v___jp_1544_;
}
v___jp_1564_:
{
uint32_t v___x_1567_; uint32_t v___x_1568_; uint32_t v___x_1569_; uint32_t v___x_1570_; uint32_t v___x_1571_; uint32_t v___x_1572_; uint32_t v___x_1573_; uint32_t v___x_1574_; uint8_t v___x_1575_; 
v___x_1567_ = 23;
v___x_1568_ = lean_uint32_shift_right(v___y_1566_, v___x_1567_);
v___x_1569_ = 255;
v___x_1570_ = lean_uint32_land(v___x_1568_, v___x_1569_);
v___x_1571_ = lean_uint32_shift_right(v___y_1092_, v___x_1567_);
v___x_1572_ = lean_uint32_land(v___x_1571_, v___x_1569_);
v___x_1573_ = lean_uint32_shift_right(v___y_1093_, v___x_1567_);
v___x_1574_ = lean_uint32_land(v___x_1573_, v___x_1569_);
v___x_1575_ = lean_uint32_dec_lt(v___x_1572_, v___x_1574_);
if (v___x_1575_ == 0)
{
v___y_1555_ = v___x_1567_;
v___y_1556_ = v___y_1565_;
v___y_1557_ = v___x_1570_;
v___y_1558_ = v___x_1569_;
v___y_1559_ = v___y_1093_;
goto v___jp_1554_;
}
else
{
v___y_1555_ = v___x_1567_;
v___y_1556_ = v___y_1565_;
v___y_1557_ = v___x_1570_;
v___y_1558_ = v___x_1569_;
v___y_1559_ = v___y_1092_;
goto v___jp_1554_;
}
}
v___jp_1576_:
{
if (v___y_1577_ == 0)
{
uint32_t v___x_1578_; uint32_t v___x_1579_; uint32_t v___x_1580_; uint32_t v___x_1581_; uint32_t v___x_1582_; uint32_t v___x_1583_; uint32_t v___x_1584_; uint8_t v___x_1585_; 
v___x_1578_ = 2;
v___x_1579_ = 23;
v___x_1580_ = lean_uint32_shift_right(v___y_1092_, v___x_1579_);
v___x_1581_ = 255;
v___x_1582_ = lean_uint32_land(v___x_1580_, v___x_1581_);
v___x_1583_ = lean_uint32_shift_right(v___y_1093_, v___x_1579_);
v___x_1584_ = lean_uint32_land(v___x_1583_, v___x_1581_);
v___x_1585_ = lean_uint32_dec_lt(v___x_1582_, v___x_1584_);
if (v___x_1585_ == 0)
{
v___y_1565_ = v___x_1578_;
v___y_1566_ = v___y_1092_;
goto v___jp_1564_;
}
else
{
v___y_1565_ = v___x_1578_;
v___y_1566_ = v___y_1093_;
goto v___jp_1564_;
}
}
else
{
v___y_1536_ = v___y_1577_;
goto v___jp_1535_;
}
}
v___jp_1586_:
{
uint32_t v___x_1591_; uint32_t v___x_1592_; uint32_t v___x_1593_; uint32_t v___x_1594_; uint8_t v___x_1595_; 
v___x_1591_ = lean_uint32_shift_right(v___y_1590_, v___y_1589_);
v___x_1592_ = lean_uint32_land(v___x_1591_, v___y_1587_);
v___x_1593_ = lean_uint32_sub(v___y_1588_, v___x_1592_);
v___x_1594_ = 7;
v___x_1595_ = lean_uint32_dec_le(v___x_1593_, v___x_1594_);
if (v___x_1595_ == 0)
{
v___y_1545_ = v___x_1595_;
goto v___jp_1544_;
}
else
{
uint32_t v___x_1596_; uint8_t v___x_1597_; uint8_t v___x_1598_; 
v___x_1596_ = 2147483648;
v___x_1597_ = lean_uint32_dec_le(v___x_1596_, v___y_1092_);
v___x_1598_ = lean_uint32_dec_le(v___x_1596_, v___y_1093_);
if (v___x_1597_ == 0)
{
if (v___x_1598_ == 0)
{
v___y_1545_ = v___x_1595_;
goto v___jp_1544_;
}
else
{
v___y_1577_ = v___x_1597_;
goto v___jp_1576_;
}
}
else
{
v___y_1577_ = v___x_1598_;
goto v___jp_1576_;
}
}
}
v___jp_1599_:
{
uint32_t v___x_1601_; uint32_t v___x_1602_; uint32_t v___x_1603_; uint32_t v___x_1604_; uint32_t v___x_1605_; uint32_t v___x_1606_; uint32_t v___x_1607_; uint32_t v___x_1608_; uint8_t v___x_1609_; 
v___x_1601_ = 23;
v___x_1602_ = lean_uint32_shift_right(v___y_1600_, v___x_1601_);
v___x_1603_ = 255;
v___x_1604_ = lean_uint32_land(v___x_1602_, v___x_1603_);
v___x_1605_ = lean_uint32_shift_right(v___y_1092_, v___x_1601_);
v___x_1606_ = lean_uint32_land(v___x_1605_, v___x_1603_);
v___x_1607_ = lean_uint32_shift_right(v___y_1093_, v___x_1601_);
v___x_1608_ = lean_uint32_land(v___x_1607_, v___x_1603_);
v___x_1609_ = lean_uint32_dec_lt(v___x_1606_, v___x_1608_);
if (v___x_1609_ == 0)
{
v___y_1587_ = v___x_1603_;
v___y_1588_ = v___x_1604_;
v___y_1589_ = v___x_1601_;
v___y_1590_ = v___y_1093_;
goto v___jp_1586_;
}
else
{
v___y_1587_ = v___x_1603_;
v___y_1588_ = v___x_1604_;
v___y_1589_ = v___x_1601_;
v___y_1590_ = v___y_1092_;
goto v___jp_1586_;
}
}
v___jp_1610_:
{
if (v___y_1611_ == 0)
{
uint32_t v___x_1612_; uint32_t v_a_1613_; uint32_t v___x_1614_; uint32_t v___x_1615_; uint32_t v___x_1616_; uint8_t v___x_1617_; 
v___x_1612_ = 2147483647;
v_a_1613_ = lean_uint32_land(v___y_1092_, v___x_1612_);
v___x_1614_ = 201326591;
v___x_1615_ = 1;
v___x_1616_ = lean_uint32_sub(v_a_1613_, v___x_1615_);
v___x_1617_ = lean_uint32_dec_le(v___x_1614_, v___x_1616_);
if (v___x_1617_ == 0)
{
v___y_1205_ = v___x_1617_;
goto v___jp_1204_;
}
else
{
uint32_t v___x_1618_; uint8_t v___x_1619_; 
v___x_1618_ = 2139095040;
v___x_1619_ = lean_uint32_dec_lt(v_a_1613_, v___x_1618_);
v___y_1205_ = v___x_1619_;
goto v___jp_1204_;
}
}
else
{
uint32_t v___x_1620_; uint32_t v___x_1621_; uint32_t v___x_1622_; uint32_t v___x_1623_; uint32_t v___x_1624_; uint32_t v___x_1625_; uint8_t v___x_1626_; 
v___x_1620_ = 23;
v___x_1621_ = lean_uint32_shift_right(v___y_1092_, v___x_1620_);
v___x_1622_ = 255;
v___x_1623_ = lean_uint32_land(v___x_1621_, v___x_1622_);
v___x_1624_ = lean_uint32_shift_right(v___y_1093_, v___x_1620_);
v___x_1625_ = lean_uint32_land(v___x_1624_, v___x_1622_);
v___x_1626_ = lean_uint32_dec_lt(v___x_1623_, v___x_1625_);
if (v___x_1626_ == 0)
{
v___y_1600_ = v___y_1092_;
goto v___jp_1599_;
}
else
{
v___y_1600_ = v___y_1093_;
goto v___jp_1599_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__2___boxed(lean_object* v___y_1639_, lean_object* v___y_1640_){
_start:
{
uint32_t v___y_10015__boxed_1641_; uint32_t v___y_10016__boxed_1642_; uint32_t v_res_1643_; lean_object* v_r_1644_; 
v___y_10015__boxed_1641_ = lean_unbox_uint32(v___y_1639_);
lean_dec(v___y_1639_);
v___y_10016__boxed_1642_ = lean_unbox_uint32(v___y_1640_);
lean_dec(v___y_1640_);
v_res_1643_ = lp_competition_main___lam__2(v___y_10015__boxed_1641_, v___y_10016__boxed_1642_);
v_r_1644_ = lean_box_uint32(v_res_1643_);
return v_r_1644_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_1645_, uint32_t v___y_1646_){
_start:
{
uint32_t v___y_1648_; uint32_t v___y_1652_; uint32_t v___y_1656_; uint32_t v___y_1657_; uint32_t v___y_1658_; uint32_t v___y_1662_; uint8_t v___y_1663_; uint64_t v___y_1664_; uint64_t v___y_1665_; uint32_t v___y_1677_; uint32_t v___y_1678_; uint32_t v___y_1679_; uint32_t v___y_1683_; uint64_t v___y_1684_; uint8_t v___y_1685_; uint64_t v___y_1686_; uint8_t v___y_1698_; uint8_t v___y_1714_; uint8_t v___y_1728_; uint8_t v___y_1745_; float v___y_1752_; float v___y_1753_; float v___y_1767_; uint8_t v___y_1768_; float v___y_1783_; uint32_t v___x_1792_; uint32_t v___x_1793_; uint8_t v___y_1795_; uint32_t v___x_1807_; uint32_t v___y_1809_; uint32_t v___y_1810_; uint32_t v___y_1811_; uint32_t v___y_1812_; uint32_t v___y_1819_; uint8_t v___y_1820_; uint32_t v___y_1821_; uint32_t v___y_1822_; uint32_t v___y_1826_; uint8_t v___y_1827_; uint64_t v___y_1828_; uint64_t v___y_1829_; uint64_t v___y_1830_; uint32_t v___y_1840_; uint8_t v___y_1841_; uint8_t v___y_1842_; uint64_t v___y_1843_; uint64_t v___y_1844_; uint64_t v___y_1845_; uint32_t v___y_1852_; uint8_t v___y_1853_; uint64_t v___y_1854_; uint64_t v___y_1855_; uint64_t v___y_1856_; uint64_t v___y_1862_; uint32_t v___y_1863_; uint8_t v___y_1864_; uint64_t v___y_1865_; uint64_t v___y_1866_; uint64_t v___y_1867_; uint32_t v___y_1922_; uint64_t v___y_1923_; uint64_t v___y_1924_; uint64_t v___y_1925_; uint8_t v___y_1926_; uint64_t v___y_1927_; uint64_t v___y_1928_; uint64_t v___y_1934_; uint32_t v___y_1935_; uint64_t v___y_1936_; uint8_t v___y_1937_; uint64_t v___y_1938_; uint64_t v___y_1939_; uint64_t v___y_1940_; uint64_t v___y_1941_; uint64_t v___y_1942_; uint32_t v___y_1947_; uint64_t v___y_1948_; uint64_t v___y_1949_; uint64_t v___y_1950_; uint8_t v___y_1951_; uint64_t v___y_1952_; uint64_t v___y_1953_; uint64_t v___y_1958_; uint32_t v___y_1959_; uint64_t v___y_1960_; uint8_t v___y_1961_; uint64_t v___y_1962_; uint64_t v___y_1963_; uint64_t v___y_1964_; uint64_t v___y_1965_; uint64_t v___y_1966_; uint32_t v___y_1971_; uint64_t v___y_1972_; uint64_t v___y_1973_; uint8_t v___y_1974_; uint64_t v___y_1975_; uint64_t v___y_1976_; uint64_t v___y_1977_; uint64_t v___y_1982_; uint64_t v___y_1983_; uint64_t v___y_1984_; uint32_t v___y_1985_; uint8_t v___y_1986_; uint64_t v___y_1987_; uint64_t v___y_1988_; uint64_t v___y_1989_; uint64_t v___y_1990_; uint32_t v___y_1995_; uint64_t v___y_1996_; uint64_t v___y_1997_; uint8_t v___y_1998_; uint64_t v___y_1999_; uint64_t v___y_2000_; uint64_t v___y_2001_; uint64_t v___y_2006_; uint32_t v___y_2007_; uint8_t v___y_2008_; uint64_t v___y_2009_; uint64_t v___y_2010_; uint64_t v___y_2011_; uint64_t v___y_2012_; uint64_t v___y_2013_; uint64_t v___y_2014_; uint32_t v___y_2019_; uint64_t v___y_2020_; uint64_t v___y_2021_; uint8_t v___y_2022_; uint64_t v___y_2023_; uint64_t v___y_2024_; uint64_t v___y_2025_; uint64_t v___y_2030_; uint32_t v___y_2031_; uint64_t v___y_2032_; uint8_t v___y_2033_; uint64_t v___y_2034_; uint64_t v___y_2035_; uint64_t v___y_2036_; uint64_t v___y_2040_; uint32_t v___y_2041_; uint64_t v___y_2042_; uint8_t v___y_2043_; uint32_t v___y_2052_; uint8_t v___y_2053_; uint64_t v___y_2054_; uint64_t v___y_2055_; uint64_t v___y_2056_; uint64_t v___y_2057_; uint32_t v_ex_2090_; uint32_t v___x_2091_; uint32_t v_ey_2092_; uint32_t v___y_2094_; uint8_t v___y_2095_; uint64_t v___y_2096_; uint64_t v___y_2097_; uint64_t v___y_2098_; uint32_t v___y_2105_; uint8_t v___y_2106_; uint64_t v___y_2107_; uint64_t v___y_2108_; uint32_t v___y_2115_; uint8_t v___y_2116_; uint32_t v___y_2117_; uint64_t v___y_2118_; uint8_t v___y_2126_; uint32_t v___x_2136_; uint32_t v___x_2137_; uint8_t v___x_2138_; uint8_t v___y_2140_; uint8_t v___y_2141_; uint8_t v___y_2143_; uint8_t v___y_2144_; uint8_t v___y_2145_; uint8_t v___y_2147_; uint8_t v___y_2148_; uint8_t v___y_2154_; 
v___x_1792_ = 23;
v___x_1793_ = lean_uint32_shift_right(v___y_1645_, v___x_1792_);
v___x_1807_ = 255;
v_ex_2090_ = lean_uint32_land(v___x_1793_, v___x_1807_);
v___x_2091_ = lean_uint32_shift_right(v___y_1646_, v___x_1792_);
v_ey_2092_ = lean_uint32_land(v___x_2091_, v___x_1807_);
v___x_2136_ = lean_uint32_add(v_ex_2090_, v_ey_2092_);
v___x_2137_ = 128;
v___x_2138_ = lean_uint32_dec_lt(v___x_2136_, v___x_2137_);
if (v___x_2138_ == 0)
{
uint32_t v___x_2163_; uint32_t v_a_2164_; uint32_t v___x_2165_; uint32_t v___x_2166_; uint32_t v___x_2167_; uint8_t v___x_2168_; 
v___x_2163_ = 2147483647;
v_a_2164_ = lean_uint32_land(v___y_1645_, v___x_2163_);
v___x_2165_ = 201326591;
v___x_2166_ = 1;
v___x_2167_ = lean_uint32_sub(v_a_2164_, v___x_2166_);
v___x_2168_ = lean_uint32_dec_le(v___x_2165_, v___x_2167_);
if (v___x_2168_ == 0)
{
v___y_1795_ = v___x_2168_;
goto v___jp_1794_;
}
else
{
uint32_t v___x_2169_; uint8_t v___x_2170_; 
v___x_2169_ = 2139095040;
v___x_2170_ = lean_uint32_dec_lt(v_a_2164_, v___x_2169_);
v___y_1795_ = v___x_2170_;
goto v___jp_1794_;
}
}
else
{
uint32_t v___x_2171_; uint32_t v___x_2172_; uint32_t v___x_2173_; uint8_t v___x_2174_; 
v___x_2171_ = 4278190080;
v___x_2172_ = 1;
v___x_2173_ = lean_uint32_shift_left(v___y_1645_, v___x_2172_);
v___x_2174_ = lean_uint32_dec_le(v___x_2171_, v___x_2173_);
if (v___x_2174_ == 0)
{
uint32_t v___x_2175_; uint8_t v___x_2176_; 
v___x_2175_ = lean_uint32_shift_left(v___y_1646_, v___x_2172_);
v___x_2176_ = lean_uint32_dec_le(v___x_2171_, v___x_2175_);
v___y_2154_ = v___x_2176_;
goto v___jp_2153_;
}
else
{
v___y_2154_ = v___x_2174_;
goto v___jp_2153_;
}
}
v___jp_1647_:
{
uint32_t v___x_1649_; uint32_t v___x_1650_; 
v___x_1649_ = 8388608;
v___x_1650_ = lean_uint32_lor(v___y_1648_, v___x_1649_);
return v___x_1650_;
}
v___jp_1651_:
{
uint32_t v___x_1653_; uint32_t v___x_1654_; 
v___x_1653_ = 8388608;
v___x_1654_ = lean_uint32_lor(v___y_1652_, v___x_1653_);
return v___x_1654_;
}
v___jp_1655_:
{
uint32_t v___x_1659_; uint32_t v___x_1660_; 
v___x_1659_ = lean_uint32_land(v___y_1656_, v___y_1657_);
v___x_1660_ = lean_uint32_lor(v___y_1658_, v___x_1659_);
return v___x_1660_;
}
v___jp_1661_:
{
uint8_t v___x_1666_; 
v___x_1666_ = lean_uint64_dec_eq(v___y_1665_, v___y_1664_);
if (v___x_1666_ == 0)
{
uint64_t v___x_1667_; uint8_t v___x_1668_; 
v___x_1667_ = 8388608ULL;
v___x_1668_ = lean_uint64_dec_eq(v___y_1665_, v___x_1667_);
if (v___x_1668_ == 0)
{
uint32_t v___x_1669_; 
v___x_1669_ = lean_uint64_to_uint32(v___y_1665_);
if (v___y_1663_ == 0)
{
uint32_t v___x_1670_; 
v___x_1670_ = 0;
v___y_1656_ = v___x_1669_;
v___y_1657_ = v___y_1662_;
v___y_1658_ = v___x_1670_;
goto v___jp_1655_;
}
else
{
uint32_t v___x_1671_; 
v___x_1671_ = 2147483648;
v___y_1656_ = v___x_1669_;
v___y_1657_ = v___y_1662_;
v___y_1658_ = v___x_1671_;
goto v___jp_1655_;
}
}
else
{
if (v___y_1663_ == 0)
{
uint32_t v___x_1672_; 
v___x_1672_ = 0;
v___y_1652_ = v___x_1672_;
goto v___jp_1651_;
}
else
{
uint32_t v___x_1673_; 
v___x_1673_ = 2147483648;
v___y_1652_ = v___x_1673_;
goto v___jp_1651_;
}
}
}
else
{
if (v___y_1663_ == 0)
{
uint32_t v___x_1674_; 
v___x_1674_ = 0;
return v___x_1674_;
}
else
{
uint32_t v___x_1675_; 
v___x_1675_ = 2147483648;
return v___x_1675_;
}
}
}
v___jp_1676_:
{
uint32_t v___x_1680_; uint32_t v___x_1681_; 
v___x_1680_ = lean_uint32_land(v___y_1678_, v___y_1677_);
v___x_1681_ = lean_uint32_lor(v___y_1679_, v___x_1680_);
return v___x_1681_;
}
v___jp_1682_:
{
uint8_t v___x_1687_; 
v___x_1687_ = lean_uint64_dec_eq(v___y_1686_, v___y_1684_);
if (v___x_1687_ == 0)
{
uint64_t v___x_1688_; uint8_t v___x_1689_; 
v___x_1688_ = 8388608ULL;
v___x_1689_ = lean_uint64_dec_eq(v___y_1686_, v___x_1688_);
if (v___x_1689_ == 0)
{
uint32_t v___x_1690_; 
v___x_1690_ = lean_uint64_to_uint32(v___y_1686_);
if (v___y_1685_ == 0)
{
uint32_t v___x_1691_; 
v___x_1691_ = 0;
v___y_1677_ = v___y_1683_;
v___y_1678_ = v___x_1690_;
v___y_1679_ = v___x_1691_;
goto v___jp_1676_;
}
else
{
uint32_t v___x_1692_; 
v___x_1692_ = 2147483648;
v___y_1677_ = v___y_1683_;
v___y_1678_ = v___x_1690_;
v___y_1679_ = v___x_1692_;
goto v___jp_1676_;
}
}
else
{
if (v___y_1685_ == 0)
{
uint32_t v___x_1693_; 
v___x_1693_ = 0;
v___y_1648_ = v___x_1693_;
goto v___jp_1647_;
}
else
{
uint32_t v___x_1694_; 
v___x_1694_ = 2147483648;
v___y_1648_ = v___x_1694_;
goto v___jp_1647_;
}
}
}
else
{
if (v___y_1685_ == 0)
{
uint32_t v___x_1695_; 
v___x_1695_ = 0;
return v___x_1695_;
}
else
{
uint32_t v___x_1696_; 
v___x_1696_ = 2147483648;
return v___x_1696_;
}
}
}
v___jp_1697_:
{
if (v___y_1698_ == 0)
{
uint32_t v___x_1699_; 
v___x_1699_ = lp_competition_Submission_FastMul_mul(v___y_1645_, v___y_1646_);
return v___x_1699_;
}
else
{
uint32_t v___x_1700_; uint32_t v___x_1701_; 
v___x_1700_ = 4194304;
v___x_1701_ = lean_uint32_lor(v___y_1646_, v___x_1700_);
return v___x_1701_;
}
}
v___jp_1702_:
{
uint32_t v___x_1703_; uint32_t v___x_1704_; uint32_t v___x_1705_; uint32_t v___x_1706_; uint8_t v___x_1707_; 
v___x_1703_ = 23;
v___x_1704_ = lean_uint32_shift_right(v___y_1646_, v___x_1703_);
v___x_1705_ = 255;
v___x_1706_ = lean_uint32_land(v___x_1704_, v___x_1705_);
v___x_1707_ = lean_uint32_dec_eq(v___x_1706_, v___x_1705_);
if (v___x_1707_ == 0)
{
v___y_1698_ = v___x_1707_;
goto v___jp_1697_;
}
else
{
uint32_t v___x_1708_; uint32_t v___x_1709_; uint32_t v___x_1710_; uint8_t v___x_1711_; 
v___x_1708_ = 8388607;
v___x_1709_ = lean_uint32_land(v___y_1646_, v___x_1708_);
v___x_1710_ = 0;
v___x_1711_ = lean_uint32_dec_eq(v___x_1709_, v___x_1710_);
if (v___x_1711_ == 0)
{
v___y_1698_ = v___x_1707_;
goto v___jp_1697_;
}
else
{
uint32_t v___x_1712_; 
v___x_1712_ = lp_competition_Submission_FastMul_mul(v___y_1645_, v___y_1646_);
return v___x_1712_;
}
}
}
v___jp_1713_:
{
if (v___y_1714_ == 0)
{
goto v___jp_1702_;
}
else
{
uint32_t v___x_1715_; uint32_t v___x_1716_; 
v___x_1715_ = 4194304;
v___x_1716_ = lean_uint32_lor(v___y_1645_, v___x_1715_);
return v___x_1716_;
}
}
v___jp_1717_:
{
uint32_t v___x_1718_; uint32_t v___x_1719_; uint32_t v___x_1720_; uint32_t v___x_1721_; uint8_t v___x_1722_; 
v___x_1718_ = 23;
v___x_1719_ = lean_uint32_shift_right(v___y_1645_, v___x_1718_);
v___x_1720_ = 255;
v___x_1721_ = lean_uint32_land(v___x_1719_, v___x_1720_);
v___x_1722_ = lean_uint32_dec_eq(v___x_1721_, v___x_1720_);
if (v___x_1722_ == 0)
{
v___y_1714_ = v___x_1722_;
goto v___jp_1713_;
}
else
{
uint32_t v___x_1723_; uint32_t v___x_1724_; uint32_t v___x_1725_; uint8_t v___x_1726_; 
v___x_1723_ = 8388607;
v___x_1724_ = lean_uint32_land(v___y_1645_, v___x_1723_);
v___x_1725_ = 0;
v___x_1726_ = lean_uint32_dec_eq(v___x_1724_, v___x_1725_);
if (v___x_1726_ == 0)
{
v___y_1714_ = v___x_1722_;
goto v___jp_1713_;
}
else
{
goto v___jp_1702_;
}
}
}
v___jp_1727_:
{
if (v___y_1728_ == 0)
{
goto v___jp_1717_;
}
else
{
uint32_t v___x_1729_; uint32_t v___x_1730_; uint32_t v___x_1731_; uint8_t v___x_1732_; 
v___x_1729_ = 4194304;
v___x_1730_ = lean_uint32_land(v___y_1646_, v___x_1729_);
v___x_1731_ = 0;
v___x_1732_ = lean_uint32_dec_eq(v___x_1730_, v___x_1731_);
if (v___x_1732_ == 0)
{
goto v___jp_1717_;
}
else
{
uint32_t v___x_1733_; 
v___x_1733_ = lean_uint32_lor(v___y_1646_, v___x_1729_);
return v___x_1733_;
}
}
}
v___jp_1734_:
{
uint32_t v___x_1735_; uint32_t v___x_1736_; uint32_t v___x_1737_; uint32_t v___x_1738_; uint8_t v___x_1739_; 
v___x_1735_ = 23;
v___x_1736_ = lean_uint32_shift_right(v___y_1646_, v___x_1735_);
v___x_1737_ = 255;
v___x_1738_ = lean_uint32_land(v___x_1736_, v___x_1737_);
v___x_1739_ = lean_uint32_dec_eq(v___x_1738_, v___x_1737_);
if (v___x_1739_ == 0)
{
v___y_1728_ = v___x_1739_;
goto v___jp_1727_;
}
else
{
uint32_t v___x_1740_; uint32_t v___x_1741_; uint32_t v___x_1742_; uint8_t v___x_1743_; 
v___x_1740_ = 8388607;
v___x_1741_ = lean_uint32_land(v___y_1646_, v___x_1740_);
v___x_1742_ = 0;
v___x_1743_ = lean_uint32_dec_eq(v___x_1741_, v___x_1742_);
if (v___x_1743_ == 0)
{
v___y_1728_ = v___x_1739_;
goto v___jp_1727_;
}
else
{
goto v___jp_1717_;
}
}
}
v___jp_1744_:
{
if (v___y_1745_ == 0)
{
goto v___jp_1734_;
}
else
{
uint32_t v___x_1746_; uint32_t v___x_1747_; uint32_t v___x_1748_; uint8_t v___x_1749_; 
v___x_1746_ = 4194304;
v___x_1747_ = lean_uint32_land(v___y_1645_, v___x_1746_);
v___x_1748_ = 0;
v___x_1749_ = lean_uint32_dec_eq(v___x_1747_, v___x_1748_);
if (v___x_1749_ == 0)
{
goto v___jp_1734_;
}
else
{
uint32_t v___x_1750_; 
v___x_1750_ = lean_uint32_lor(v___y_1645_, v___x_1746_);
return v___x_1750_;
}
}
}
v___jp_1751_:
{
float v_result_1754_; uint8_t v___x_1755_; 
v_result_1754_ = lean_float32_mul(v___y_1752_, v___y_1753_);
v___x_1755_ = lean_float32_beq(v_result_1754_, v_result_1754_);
if (v___x_1755_ == 0)
{
uint32_t v___x_1756_; uint32_t v___x_1757_; uint32_t v___x_1758_; uint32_t v___x_1759_; uint8_t v___x_1760_; 
v___x_1756_ = 23;
v___x_1757_ = lean_uint32_shift_right(v___y_1645_, v___x_1756_);
v___x_1758_ = 255;
v___x_1759_ = lean_uint32_land(v___x_1757_, v___x_1758_);
v___x_1760_ = lean_uint32_dec_eq(v___x_1759_, v___x_1758_);
if (v___x_1760_ == 0)
{
v___y_1745_ = v___x_1760_;
goto v___jp_1744_;
}
else
{
uint32_t v___x_1761_; uint32_t v___x_1762_; uint32_t v___x_1763_; uint8_t v___x_1764_; 
v___x_1761_ = 8388607;
v___x_1762_ = lean_uint32_land(v___y_1645_, v___x_1761_);
v___x_1763_ = 0;
v___x_1764_ = lean_uint32_dec_eq(v___x_1762_, v___x_1763_);
if (v___x_1764_ == 0)
{
v___y_1745_ = v___x_1760_;
goto v___jp_1744_;
}
else
{
goto v___jp_1734_;
}
}
}
else
{
uint32_t v___x_1765_; 
v___x_1765_ = lean_float32_to_bits(v_result_1754_);
return v___x_1765_;
}
}
v___jp_1766_:
{
if (v___y_1768_ == 0)
{
float v___x_1769_; 
v___x_1769_ = lean_float32_of_bits(v___y_1646_);
v___y_1752_ = v___y_1767_;
v___y_1753_ = v___x_1769_;
goto v___jp_1751_;
}
else
{
uint32_t v___x_1770_; uint32_t v___x_1771_; uint32_t v___x_1772_; uint32_t v___x_1773_; float v___x_1774_; lean_object* v___x_1775_; uint32_t v___x_1776_; uint32_t v___x_1777_; lean_object* v___x_1778_; lean_object* v___x_1779_; float v___x_1780_; float v___x_1781_; 
v___x_1770_ = 8388607;
v___x_1771_ = lean_uint32_land(v___y_1646_, v___x_1770_);
v___x_1772_ = 8388608;
v___x_1773_ = lean_uint32_lor(v___x_1771_, v___x_1772_);
v___x_1774_ = lean_uint32_to_float32(v___x_1773_);
v___x_1775_ = lp_competition_R2W01b_scaleTable;
v___x_1776_ = 23;
v___x_1777_ = lean_uint32_shift_right(v___y_1646_, v___x_1776_);
v___x_1778_ = lean_uint32_to_nat(v___x_1777_);
v___x_1779_ = lean_array_fget_borrowed(v___x_1775_, v___x_1778_);
lean_dec(v___x_1778_);
v___x_1780_ = lean_unbox_float32(v___x_1779_);
v___x_1781_ = lean_float32_mul(v___x_1774_, v___x_1780_);
v___y_1752_ = v___y_1767_;
v___y_1753_ = v___x_1781_;
goto v___jp_1751_;
}
}
v___jp_1782_:
{
uint32_t v___x_1784_; uint32_t v_a_1785_; uint32_t v___x_1786_; uint32_t v___x_1787_; uint32_t v___x_1788_; uint8_t v___x_1789_; 
v___x_1784_ = 2147483647;
v_a_1785_ = lean_uint32_land(v___y_1646_, v___x_1784_);
v___x_1786_ = 201326591;
v___x_1787_ = 1;
v___x_1788_ = lean_uint32_sub(v_a_1785_, v___x_1787_);
v___x_1789_ = lean_uint32_dec_le(v___x_1786_, v___x_1788_);
if (v___x_1789_ == 0)
{
v___y_1767_ = v___y_1783_;
v___y_1768_ = v___x_1789_;
goto v___jp_1766_;
}
else
{
uint32_t v___x_1790_; uint8_t v___x_1791_; 
v___x_1790_ = 2139095040;
v___x_1791_ = lean_uint32_dec_lt(v_a_1785_, v___x_1790_);
v___y_1767_ = v___y_1783_;
v___y_1768_ = v___x_1791_;
goto v___jp_1766_;
}
}
v___jp_1794_:
{
if (v___y_1795_ == 0)
{
float v___x_1796_; 
v___x_1796_ = lean_float32_of_bits(v___y_1645_);
v___y_1783_ = v___x_1796_;
goto v___jp_1782_;
}
else
{
uint32_t v___x_1797_; uint32_t v___x_1798_; uint32_t v___x_1799_; uint32_t v___x_1800_; float v___x_1801_; lean_object* v___x_1802_; lean_object* v___x_1803_; lean_object* v___x_1804_; float v___x_1805_; float v___x_1806_; 
v___x_1797_ = 8388607;
v___x_1798_ = lean_uint32_land(v___y_1645_, v___x_1797_);
v___x_1799_ = 8388608;
v___x_1800_ = lean_uint32_lor(v___x_1798_, v___x_1799_);
v___x_1801_ = lean_uint32_to_float32(v___x_1800_);
v___x_1802_ = lp_competition_R2W01b_scaleTable;
v___x_1803_ = lean_uint32_to_nat(v___x_1793_);
v___x_1804_ = lean_array_fget_borrowed(v___x_1802_, v___x_1803_);
lean_dec(v___x_1803_);
v___x_1805_ = lean_unbox_float32(v___x_1804_);
v___x_1806_ = lean_float32_mul(v___x_1801_, v___x_1805_);
v___y_1783_ = v___x_1806_;
goto v___jp_1782_;
}
}
v___jp_1808_:
{
uint32_t v___x_1813_; uint32_t v___x_1814_; uint32_t v___x_1815_; uint32_t v___x_1816_; uint32_t v___x_1817_; 
v___x_1813_ = lean_uint32_land(v___y_1811_, v___x_1807_);
v___x_1814_ = lean_uint32_shift_left(v___x_1813_, v___x_1792_);
v___x_1815_ = lean_uint32_lor(v___y_1812_, v___x_1814_);
v___x_1816_ = lean_uint32_land(v___y_1810_, v___y_1809_);
v___x_1817_ = lean_uint32_lor(v___x_1815_, v___x_1816_);
return v___x_1817_;
}
v___jp_1818_:
{
if (v___y_1820_ == 0)
{
uint32_t v___x_1823_; 
v___x_1823_ = 0;
v___y_1809_ = v___y_1819_;
v___y_1810_ = v___y_1822_;
v___y_1811_ = v___y_1821_;
v___y_1812_ = v___x_1823_;
goto v___jp_1808_;
}
else
{
uint32_t v___x_1824_; 
v___x_1824_ = 2147483648;
v___y_1809_ = v___y_1819_;
v___y_1810_ = v___y_1822_;
v___y_1811_ = v___y_1821_;
v___y_1812_ = v___x_1824_;
goto v___jp_1808_;
}
}
v___jp_1825_:
{
uint64_t v___x_1831_; uint64_t v_encodedExponent_1832_; uint32_t v___x_1833_; uint64_t v___x_1834_; uint8_t v___x_1835_; 
v___x_1831_ = 171ULL;
v_encodedExponent_1832_ = lean_uint64_sub(v___y_1828_, v___x_1831_);
v___x_1833_ = lean_uint64_to_uint32(v_encodedExponent_1832_);
v___x_1834_ = 8388608ULL;
v___x_1835_ = lean_uint64_dec_lt(v___y_1830_, v___x_1834_);
if (v___x_1835_ == 0)
{
uint64_t v___x_1836_; uint32_t v___x_1837_; 
v___x_1836_ = lean_uint64_sub(v___y_1830_, v___x_1834_);
v___x_1837_ = lean_uint64_to_uint32(v___x_1836_);
v___y_1819_ = v___y_1826_;
v___y_1820_ = v___y_1827_;
v___y_1821_ = v___x_1833_;
v___y_1822_ = v___x_1837_;
goto v___jp_1818_;
}
else
{
uint32_t v___x_1838_; 
v___x_1838_ = lean_uint64_to_uint32(v___y_1829_);
v___y_1819_ = v___y_1826_;
v___y_1820_ = v___y_1827_;
v___y_1821_ = v___x_1833_;
v___y_1822_ = v___x_1838_;
goto v___jp_1818_;
}
}
v___jp_1839_:
{
uint64_t v___x_1846_; uint8_t v___x_1847_; 
v___x_1846_ = 425ULL;
v___x_1847_ = lean_uint64_dec_lt(v___x_1846_, v___y_1845_);
if (v___x_1847_ == 0)
{
if (v___y_1842_ == 0)
{
v___y_1826_ = v___y_1840_;
v___y_1827_ = v___y_1841_;
v___y_1828_ = v___y_1845_;
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___y_1843_;
goto v___jp_1825_;
}
else
{
uint64_t v___x_1848_; 
v___x_1848_ = 8388608ULL;
v___y_1826_ = v___y_1840_;
v___y_1827_ = v___y_1841_;
v___y_1828_ = v___y_1845_;
v___y_1829_ = v___y_1844_;
v___y_1830_ = v___x_1848_;
goto v___jp_1825_;
}
}
else
{
if (v___y_1841_ == 0)
{
uint32_t v___x_1849_; 
v___x_1849_ = 2139095040;
return v___x_1849_;
}
else
{
uint32_t v___x_1850_; 
v___x_1850_ = 4286578688;
return v___x_1850_;
}
}
}
v___jp_1851_:
{
uint64_t v___x_1857_; uint8_t v_carry_1858_; 
v___x_1857_ = 16777216ULL;
v_carry_1858_ = lean_uint64_dec_eq(v___y_1856_, v___x_1857_);
if (v_carry_1858_ == 0)
{
v___y_1840_ = v___y_1852_;
v___y_1841_ = v___y_1853_;
v___y_1842_ = v_carry_1858_;
v___y_1843_ = v___y_1856_;
v___y_1844_ = v___y_1855_;
v___y_1845_ = v___y_1854_;
goto v___jp_1839_;
}
else
{
uint64_t v___x_1859_; uint64_t v___x_1860_; 
v___x_1859_ = 1ULL;
v___x_1860_ = lean_uint64_add(v___y_1854_, v___x_1859_);
v___y_1840_ = v___y_1852_;
v___y_1841_ = v___y_1853_;
v___y_1842_ = v_carry_1858_;
v___y_1843_ = v___y_1856_;
v___y_1844_ = v___y_1855_;
v___y_1845_ = v___x_1860_;
goto v___jp_1839_;
}
}
v___jp_1861_:
{
uint64_t v_position_1868_; uint64_t v___x_1869_; uint8_t v___x_1870_; 
v_position_1868_ = lean_uint64_add(v___y_1867_, v___y_1865_);
v___x_1869_ = 172ULL;
v___x_1870_ = lean_uint64_dec_lt(v_position_1868_, v___x_1869_);
if (v___x_1870_ == 0)
{
uint64_t v___x_1871_; uint8_t v___x_1872_; 
v___x_1871_ = 23ULL;
v___x_1872_ = lean_uint64_dec_lt(v___y_1867_, v___x_1871_);
if (v___x_1872_ == 0)
{
uint64_t v___x_1873_; uint8_t v___x_1874_; 
v___x_1873_ = lean_uint64_sub(v___y_1867_, v___x_1871_);
v___x_1874_ = lean_uint64_dec_eq(v___x_1873_, v___y_1866_);
if (v___x_1874_ == 0)
{
uint64_t v___x_1875_; uint8_t v___x_1876_; 
v___x_1875_ = 64ULL;
v___x_1876_ = lean_uint64_dec_lt(v___x_1873_, v___x_1875_);
if (v___x_1876_ == 0)
{
uint8_t v___x_1877_; 
v___x_1877_ = lean_uint64_dec_eq(v___x_1873_, v___x_1875_);
if (v___x_1877_ == 0)
{
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v___y_1866_;
goto v___jp_1851_;
}
else
{
uint64_t v___x_1878_; uint8_t v___x_1879_; 
v___x_1878_ = 9223372036854775808ULL;
v___x_1879_ = lean_uint64_dec_lt(v___x_1878_, v___y_1862_);
if (v___x_1879_ == 0)
{
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v___y_1866_;
goto v___jp_1851_;
}
else
{
uint64_t v___x_1880_; 
v___x_1880_ = 1ULL;
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v___x_1880_;
goto v___jp_1851_;
}
}
}
else
{
uint64_t v_quotient_1881_; uint64_t v___x_1882_; uint64_t v___x_1883_; uint64_t v___x_1884_; uint64_t v_remainder_1885_; uint64_t v___x_1886_; uint64_t v_half_1887_; uint8_t v___x_1888_; 
v_quotient_1881_ = lean_uint64_shift_right(v___y_1862_, v___x_1873_);
v___x_1882_ = 1ULL;
v___x_1883_ = lean_uint64_shift_left(v___x_1882_, v___x_1873_);
v___x_1884_ = lean_uint64_sub(v___x_1883_, v___x_1882_);
v_remainder_1885_ = lean_uint64_land(v___y_1862_, v___x_1884_);
v___x_1886_ = lean_uint64_sub(v___x_1873_, v___x_1882_);
v_half_1887_ = lean_uint64_shift_left(v___x_1882_, v___x_1886_);
v___x_1888_ = lean_uint64_dec_lt(v_remainder_1885_, v_half_1887_);
if (v___x_1888_ == 0)
{
uint8_t v___x_1889_; 
v___x_1889_ = lean_uint64_dec_lt(v_half_1887_, v_remainder_1885_);
if (v___x_1889_ == 0)
{
uint64_t v___x_1890_; uint8_t v___x_1891_; 
v___x_1890_ = lean_uint64_land(v_quotient_1881_, v___x_1882_);
v___x_1891_ = lean_uint64_dec_eq(v___x_1890_, v___y_1866_);
if (v___x_1891_ == 0)
{
uint64_t v___x_1892_; 
v___x_1892_ = lean_uint64_add(v_quotient_1881_, v___x_1882_);
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v___x_1892_;
goto v___jp_1851_;
}
else
{
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v_quotient_1881_;
goto v___jp_1851_;
}
}
else
{
uint64_t v___x_1893_; 
v___x_1893_ = lean_uint64_add(v_quotient_1881_, v___x_1882_);
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v___x_1893_;
goto v___jp_1851_;
}
}
else
{
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v_quotient_1881_;
goto v___jp_1851_;
}
}
}
else
{
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v___y_1862_;
goto v___jp_1851_;
}
}
else
{
uint64_t v___x_1894_; uint64_t v___x_1895_; 
v___x_1894_ = lean_uint64_sub(v___x_1871_, v___y_1867_);
v___x_1895_ = lean_uint64_shift_left(v___y_1862_, v___x_1894_);
v___y_1852_ = v___y_1863_;
v___y_1853_ = v___y_1864_;
v___y_1854_ = v_position_1868_;
v___y_1855_ = v___y_1866_;
v___y_1856_ = v___x_1895_;
goto v___jp_1851_;
}
}
else
{
uint64_t v___x_1896_; uint8_t v___x_1897_; 
v___x_1896_ = 149ULL;
v___x_1897_ = lean_uint64_dec_lt(v___y_1865_, v___x_1896_);
if (v___x_1897_ == 0)
{
uint64_t v___x_1898_; uint64_t v___x_1899_; 
v___x_1898_ = lean_uint64_sub(v___y_1865_, v___x_1896_);
v___x_1899_ = lean_uint64_shift_left(v___y_1862_, v___x_1898_);
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v___x_1899_;
goto v___jp_1661_;
}
else
{
uint64_t v___x_1900_; uint8_t v___x_1901_; 
v___x_1900_ = lean_uint64_sub(v___x_1896_, v___y_1865_);
v___x_1901_ = lean_uint64_dec_eq(v___x_1900_, v___y_1866_);
if (v___x_1901_ == 0)
{
uint64_t v___x_1902_; uint8_t v___x_1903_; 
v___x_1902_ = 64ULL;
v___x_1903_ = lean_uint64_dec_lt(v___x_1900_, v___x_1902_);
if (v___x_1903_ == 0)
{
uint8_t v___x_1904_; 
v___x_1904_ = lean_uint64_dec_eq(v___x_1900_, v___x_1902_);
if (v___x_1904_ == 0)
{
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v___y_1866_;
goto v___jp_1661_;
}
else
{
uint64_t v___x_1905_; uint8_t v___x_1906_; 
v___x_1905_ = 9223372036854775808ULL;
v___x_1906_ = lean_uint64_dec_lt(v___x_1905_, v___y_1862_);
if (v___x_1906_ == 0)
{
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v___y_1866_;
goto v___jp_1661_;
}
else
{
uint64_t v___x_1907_; 
v___x_1907_ = 1ULL;
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v___x_1907_;
goto v___jp_1661_;
}
}
}
else
{
uint64_t v_quotient_1908_; uint64_t v___x_1909_; uint64_t v___x_1910_; uint64_t v___x_1911_; uint64_t v_remainder_1912_; uint64_t v___x_1913_; uint64_t v_half_1914_; uint8_t v___x_1915_; 
v_quotient_1908_ = lean_uint64_shift_right(v___y_1862_, v___x_1900_);
v___x_1909_ = 1ULL;
v___x_1910_ = lean_uint64_shift_left(v___x_1909_, v___x_1900_);
v___x_1911_ = lean_uint64_sub(v___x_1910_, v___x_1909_);
v_remainder_1912_ = lean_uint64_land(v___y_1862_, v___x_1911_);
v___x_1913_ = lean_uint64_sub(v___x_1900_, v___x_1909_);
v_half_1914_ = lean_uint64_shift_left(v___x_1909_, v___x_1913_);
v___x_1915_ = lean_uint64_dec_lt(v_remainder_1912_, v_half_1914_);
if (v___x_1915_ == 0)
{
uint8_t v___x_1916_; 
v___x_1916_ = lean_uint64_dec_lt(v_half_1914_, v_remainder_1912_);
if (v___x_1916_ == 0)
{
uint64_t v___x_1917_; uint8_t v___x_1918_; 
v___x_1917_ = lean_uint64_land(v_quotient_1908_, v___x_1909_);
v___x_1918_ = lean_uint64_dec_eq(v___x_1917_, v___y_1866_);
if (v___x_1918_ == 0)
{
uint64_t v___x_1919_; 
v___x_1919_ = lean_uint64_add(v_quotient_1908_, v___x_1909_);
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v___x_1919_;
goto v___jp_1661_;
}
else
{
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v_quotient_1908_;
goto v___jp_1661_;
}
}
else
{
uint64_t v___x_1920_; 
v___x_1920_ = lean_uint64_add(v_quotient_1908_, v___x_1909_);
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v___x_1920_;
goto v___jp_1661_;
}
}
else
{
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v_quotient_1908_;
goto v___jp_1661_;
}
}
}
else
{
v___y_1662_ = v___y_1863_;
v___y_1663_ = v___y_1864_;
v___y_1664_ = v___y_1866_;
v___y_1665_ = v___y_1862_;
goto v___jp_1661_;
}
}
}
}
v___jp_1921_:
{
uint64_t v___x_1929_; uint64_t v___x_1930_; uint8_t v___x_1931_; 
v___x_1929_ = 1ULL;
v___x_1930_ = lean_uint64_shift_right(v___y_1924_, v___x_1929_);
v___x_1931_ = lean_uint64_dec_eq(v___x_1930_, v___y_1927_);
if (v___x_1931_ == 0)
{
uint64_t v___x_1932_; 
v___x_1932_ = lean_uint64_add(v___y_1928_, v___x_1929_);
v___y_1862_ = v___y_1923_;
v___y_1863_ = v___y_1922_;
v___y_1864_ = v___y_1926_;
v___y_1865_ = v___y_1925_;
v___y_1866_ = v___y_1927_;
v___y_1867_ = v___x_1932_;
goto v___jp_1861_;
}
else
{
v___y_1862_ = v___y_1923_;
v___y_1863_ = v___y_1922_;
v___y_1864_ = v___y_1926_;
v___y_1865_ = v___y_1925_;
v___y_1866_ = v___y_1927_;
v___y_1867_ = v___y_1928_;
goto v___jp_1861_;
}
}
v___jp_1933_:
{
uint64_t v___x_1943_; uint8_t v___x_1944_; 
v___x_1943_ = lean_uint64_shift_right(v___y_1936_, v___y_1940_);
v___x_1944_ = lean_uint64_dec_eq(v___x_1943_, v___y_1941_);
if (v___x_1944_ == 0)
{
uint64_t v___x_1945_; 
v___x_1945_ = lean_uint64_add(v___y_1939_, v___y_1940_);
v___y_1922_ = v___y_1935_;
v___y_1923_ = v___y_1934_;
v___y_1924_ = v___y_1942_;
v___y_1925_ = v___y_1938_;
v___y_1926_ = v___y_1937_;
v___y_1927_ = v___y_1941_;
v___y_1928_ = v___x_1945_;
goto v___jp_1921_;
}
else
{
v___y_1922_ = v___y_1935_;
v___y_1923_ = v___y_1934_;
v___y_1924_ = v___y_1942_;
v___y_1925_ = v___y_1938_;
v___y_1926_ = v___y_1937_;
v___y_1927_ = v___y_1941_;
v___y_1928_ = v___y_1939_;
goto v___jp_1921_;
}
}
v___jp_1946_:
{
uint64_t v___x_1954_; uint64_t v___x_1955_; uint8_t v___x_1956_; 
v___x_1954_ = 2ULL;
v___x_1955_ = lean_uint64_shift_right(v___y_1949_, v___x_1954_);
v___x_1956_ = lean_uint64_dec_eq(v___x_1955_, v___y_1952_);
if (v___x_1956_ == 0)
{
v___y_1934_ = v___y_1948_;
v___y_1935_ = v___y_1947_;
v___y_1936_ = v___y_1949_;
v___y_1937_ = v___y_1951_;
v___y_1938_ = v___y_1950_;
v___y_1939_ = v___y_1953_;
v___y_1940_ = v___x_1954_;
v___y_1941_ = v___y_1952_;
v___y_1942_ = v___x_1955_;
goto v___jp_1933_;
}
else
{
v___y_1934_ = v___y_1948_;
v___y_1935_ = v___y_1947_;
v___y_1936_ = v___y_1949_;
v___y_1937_ = v___y_1951_;
v___y_1938_ = v___y_1950_;
v___y_1939_ = v___y_1953_;
v___y_1940_ = v___x_1954_;
v___y_1941_ = v___y_1952_;
v___y_1942_ = v___y_1949_;
goto v___jp_1933_;
}
}
v___jp_1957_:
{
uint64_t v___x_1967_; uint8_t v___x_1968_; 
v___x_1967_ = lean_uint64_shift_right(v___y_1960_, v___y_1964_);
v___x_1968_ = lean_uint64_dec_eq(v___x_1967_, v___y_1965_);
if (v___x_1968_ == 0)
{
uint64_t v___x_1969_; 
v___x_1969_ = lean_uint64_add(v___y_1963_, v___y_1964_);
v___y_1947_ = v___y_1959_;
v___y_1948_ = v___y_1958_;
v___y_1949_ = v___y_1966_;
v___y_1950_ = v___y_1962_;
v___y_1951_ = v___y_1961_;
v___y_1952_ = v___y_1965_;
v___y_1953_ = v___x_1969_;
goto v___jp_1946_;
}
else
{
v___y_1947_ = v___y_1959_;
v___y_1948_ = v___y_1958_;
v___y_1949_ = v___y_1966_;
v___y_1950_ = v___y_1962_;
v___y_1951_ = v___y_1961_;
v___y_1952_ = v___y_1965_;
v___y_1953_ = v___y_1963_;
goto v___jp_1946_;
}
}
v___jp_1970_:
{
uint64_t v___x_1978_; uint64_t v___x_1979_; uint8_t v___x_1980_; 
v___x_1978_ = 4ULL;
v___x_1979_ = lean_uint64_shift_right(v___y_1975_, v___x_1978_);
v___x_1980_ = lean_uint64_dec_eq(v___x_1979_, v___y_1976_);
if (v___x_1980_ == 0)
{
v___y_1958_ = v___y_1972_;
v___y_1959_ = v___y_1971_;
v___y_1960_ = v___y_1975_;
v___y_1961_ = v___y_1974_;
v___y_1962_ = v___y_1973_;
v___y_1963_ = v___y_1977_;
v___y_1964_ = v___x_1978_;
v___y_1965_ = v___y_1976_;
v___y_1966_ = v___x_1979_;
goto v___jp_1957_;
}
else
{
v___y_1958_ = v___y_1972_;
v___y_1959_ = v___y_1971_;
v___y_1960_ = v___y_1975_;
v___y_1961_ = v___y_1974_;
v___y_1962_ = v___y_1973_;
v___y_1963_ = v___y_1977_;
v___y_1964_ = v___x_1978_;
v___y_1965_ = v___y_1976_;
v___y_1966_ = v___y_1975_;
goto v___jp_1957_;
}
}
v___jp_1981_:
{
uint64_t v___x_1991_; uint8_t v___x_1992_; 
v___x_1991_ = lean_uint64_shift_right(v___y_1988_, v___y_1982_);
v___x_1992_ = lean_uint64_dec_eq(v___x_1991_, v___y_1989_);
if (v___x_1992_ == 0)
{
uint64_t v___x_1993_; 
v___x_1993_ = lean_uint64_add(v___y_1983_, v___y_1982_);
v___y_1971_ = v___y_1985_;
v___y_1972_ = v___y_1984_;
v___y_1973_ = v___y_1987_;
v___y_1974_ = v___y_1986_;
v___y_1975_ = v___y_1990_;
v___y_1976_ = v___y_1989_;
v___y_1977_ = v___x_1993_;
goto v___jp_1970_;
}
else
{
v___y_1971_ = v___y_1985_;
v___y_1972_ = v___y_1984_;
v___y_1973_ = v___y_1987_;
v___y_1974_ = v___y_1986_;
v___y_1975_ = v___y_1990_;
v___y_1976_ = v___y_1989_;
v___y_1977_ = v___y_1983_;
goto v___jp_1970_;
}
}
v___jp_1994_:
{
uint64_t v___x_2002_; uint64_t v___x_2003_; uint8_t v___x_2004_; 
v___x_2002_ = 8ULL;
v___x_2003_ = lean_uint64_shift_right(v___y_1999_, v___x_2002_);
v___x_2004_ = lean_uint64_dec_eq(v___x_2003_, v___y_2000_);
if (v___x_2004_ == 0)
{
v___y_1982_ = v___x_2002_;
v___y_1983_ = v___y_2001_;
v___y_1984_ = v___y_1996_;
v___y_1985_ = v___y_1995_;
v___y_1986_ = v___y_1998_;
v___y_1987_ = v___y_1997_;
v___y_1988_ = v___y_1999_;
v___y_1989_ = v___y_2000_;
v___y_1990_ = v___x_2003_;
goto v___jp_1981_;
}
else
{
v___y_1982_ = v___x_2002_;
v___y_1983_ = v___y_2001_;
v___y_1984_ = v___y_1996_;
v___y_1985_ = v___y_1995_;
v___y_1986_ = v___y_1998_;
v___y_1987_ = v___y_1997_;
v___y_1988_ = v___y_1999_;
v___y_1989_ = v___y_2000_;
v___y_1990_ = v___y_1999_;
goto v___jp_1981_;
}
}
v___jp_2005_:
{
uint64_t v___x_2015_; uint8_t v___x_2016_; 
v___x_2015_ = lean_uint64_shift_right(v___y_2012_, v___y_2011_);
v___x_2016_ = lean_uint64_dec_eq(v___x_2015_, v___y_2013_);
if (v___x_2016_ == 0)
{
uint64_t v___x_2017_; 
v___x_2017_ = lean_uint64_add(v___y_2010_, v___y_2011_);
v___y_1995_ = v___y_2007_;
v___y_1996_ = v___y_2006_;
v___y_1997_ = v___y_2009_;
v___y_1998_ = v___y_2008_;
v___y_1999_ = v___y_2014_;
v___y_2000_ = v___y_2013_;
v___y_2001_ = v___x_2017_;
goto v___jp_1994_;
}
else
{
v___y_1995_ = v___y_2007_;
v___y_1996_ = v___y_2006_;
v___y_1997_ = v___y_2009_;
v___y_1998_ = v___y_2008_;
v___y_1999_ = v___y_2014_;
v___y_2000_ = v___y_2013_;
v___y_2001_ = v___y_2010_;
goto v___jp_1994_;
}
}
v___jp_2018_:
{
uint64_t v___x_2026_; uint64_t v___x_2027_; uint8_t v___x_2028_; 
v___x_2026_ = 16ULL;
v___x_2027_ = lean_uint64_shift_right(v___y_2023_, v___x_2026_);
v___x_2028_ = lean_uint64_dec_eq(v___x_2027_, v___y_2024_);
if (v___x_2028_ == 0)
{
v___y_2006_ = v___y_2020_;
v___y_2007_ = v___y_2019_;
v___y_2008_ = v___y_2022_;
v___y_2009_ = v___y_2021_;
v___y_2010_ = v___y_2025_;
v___y_2011_ = v___x_2026_;
v___y_2012_ = v___y_2023_;
v___y_2013_ = v___y_2024_;
v___y_2014_ = v___x_2027_;
goto v___jp_2005_;
}
else
{
v___y_2006_ = v___y_2020_;
v___y_2007_ = v___y_2019_;
v___y_2008_ = v___y_2022_;
v___y_2009_ = v___y_2021_;
v___y_2010_ = v___y_2025_;
v___y_2011_ = v___x_2026_;
v___y_2012_ = v___y_2023_;
v___y_2013_ = v___y_2024_;
v___y_2014_ = v___y_2023_;
goto v___jp_2005_;
}
}
v___jp_2029_:
{
uint64_t v___x_2037_; uint8_t v___x_2038_; 
v___x_2037_ = lean_uint64_shift_right(v___y_2030_, v___y_2032_);
v___x_2038_ = lean_uint64_dec_eq(v___x_2037_, v___y_2035_);
if (v___x_2038_ == 0)
{
v___y_2019_ = v___y_2031_;
v___y_2020_ = v___y_2030_;
v___y_2021_ = v___y_2034_;
v___y_2022_ = v___y_2033_;
v___y_2023_ = v___y_2036_;
v___y_2024_ = v___y_2035_;
v___y_2025_ = v___y_2032_;
goto v___jp_2018_;
}
else
{
v___y_2019_ = v___y_2031_;
v___y_2020_ = v___y_2030_;
v___y_2021_ = v___y_2034_;
v___y_2022_ = v___y_2033_;
v___y_2023_ = v___y_2036_;
v___y_2024_ = v___y_2035_;
v___y_2025_ = v___y_2035_;
goto v___jp_2018_;
}
}
v___jp_2039_:
{
uint64_t v___x_2044_; uint8_t v___x_2045_; 
v___x_2044_ = 0ULL;
v___x_2045_ = lean_uint64_dec_eq(v___y_2040_, v___x_2044_);
if (v___x_2045_ == 0)
{
uint64_t v___x_2046_; uint64_t v___x_2047_; uint8_t v___x_2048_; 
v___x_2046_ = 32ULL;
v___x_2047_ = lean_uint64_shift_right(v___y_2040_, v___x_2046_);
v___x_2048_ = lean_uint64_dec_eq(v___x_2047_, v___x_2044_);
if (v___x_2048_ == 0)
{
v___y_2030_ = v___y_2040_;
v___y_2031_ = v___y_2041_;
v___y_2032_ = v___x_2046_;
v___y_2033_ = v___y_2043_;
v___y_2034_ = v___y_2042_;
v___y_2035_ = v___x_2044_;
v___y_2036_ = v___x_2047_;
goto v___jp_2029_;
}
else
{
v___y_2030_ = v___y_2040_;
v___y_2031_ = v___y_2041_;
v___y_2032_ = v___x_2046_;
v___y_2033_ = v___y_2043_;
v___y_2034_ = v___y_2042_;
v___y_2035_ = v___x_2044_;
v___y_2036_ = v___y_2040_;
goto v___jp_2029_;
}
}
else
{
if (v___y_2043_ == 0)
{
uint32_t v___x_2049_; 
v___x_2049_ = 0;
return v___x_2049_;
}
else
{
uint32_t v___x_2050_; 
v___x_2050_ = 2147483648;
return v___x_2050_;
}
}
}
v___jp_2051_:
{
uint64_t v___x_2058_; uint64_t v___x_2059_; uint64_t v___x_2060_; uint8_t v___x_2061_; 
v___x_2058_ = lean_uint64_mul(v___y_2055_, v___y_2056_);
v___x_2059_ = lean_uint64_add(v___y_2054_, v___y_2057_);
v___x_2060_ = 281474976710656ULL;
v___x_2061_ = lean_uint64_dec_lt(v___x_2058_, v___x_2060_);
if (v___x_2061_ == 0)
{
v___y_2040_ = v___x_2058_;
v___y_2041_ = v___y_2052_;
v___y_2042_ = v___x_2059_;
v___y_2043_ = v___y_2053_;
goto v___jp_2039_;
}
else
{
uint64_t v___x_2062_; uint8_t v___x_2063_; 
v___x_2062_ = 123ULL;
v___x_2063_ = lean_uint64_dec_le(v___x_2059_, v___x_2062_);
if (v___x_2063_ == 0)
{
v___y_2040_ = v___x_2058_;
v___y_2041_ = v___y_2052_;
v___y_2042_ = v___x_2059_;
v___y_2043_ = v___y_2053_;
goto v___jp_2039_;
}
else
{
uint64_t v___x_2064_; uint8_t v___x_2065_; 
v___x_2064_ = 0ULL;
v___x_2065_ = lean_uint64_dec_eq(v___x_2058_, v___x_2064_);
if (v___x_2065_ == 0)
{
uint64_t v___x_2066_; uint64_t v___x_2067_; uint8_t v___x_2068_; 
v___x_2066_ = 149ULL;
v___x_2067_ = lean_uint64_sub(v___x_2066_, v___x_2059_);
v___x_2068_ = lean_uint64_dec_eq(v___x_2067_, v___x_2064_);
if (v___x_2068_ == 0)
{
uint64_t v___x_2069_; uint8_t v___x_2070_; 
v___x_2069_ = 64ULL;
v___x_2070_ = lean_uint64_dec_lt(v___x_2067_, v___x_2069_);
if (v___x_2070_ == 0)
{
uint8_t v___x_2071_; 
v___x_2071_ = lean_uint64_dec_eq(v___x_2067_, v___x_2069_);
if (v___x_2071_ == 0)
{
v___y_1683_ = v___y_2052_;
v___y_1684_ = v___x_2064_;
v___y_1685_ = v___y_2053_;
v___y_1686_ = v___x_2064_;
goto v___jp_1682_;
}
else
{
uint64_t v___x_2072_; uint8_t v___x_2073_; 
v___x_2072_ = 9223372036854775808ULL;
v___x_2073_ = lean_uint64_dec_lt(v___x_2072_, v___x_2058_);
if (v___x_2073_ == 0)
{
v___y_1683_ = v___y_2052_;
v___y_1684_ = v___x_2064_;
v___y_1685_ = v___y_2053_;
v___y_1686_ = v___x_2064_;
goto v___jp_1682_;
}
else
{
uint64_t v___x_2074_; 
v___x_2074_ = 1ULL;
v___y_1683_ = v___y_2052_;
v___y_1684_ = v___x_2064_;
v___y_1685_ = v___y_2053_;
v___y_1686_ = v___x_2074_;
goto v___jp_1682_;
}
}
}
else
{
uint64_t v_quotient_2075_; uint64_t v___x_2076_; uint64_t v___x_2077_; uint64_t v___x_2078_; uint64_t v_remainder_2079_; uint64_t v___x_2080_; uint64_t v_half_2081_; uint8_t v___x_2082_; 
v_quotient_2075_ = lean_uint64_shift_right(v___x_2058_, v___x_2067_);
v___x_2076_ = 1ULL;
v___x_2077_ = lean_uint64_shift_left(v___x_2076_, v___x_2067_);
v___x_2078_ = lean_uint64_sub(v___x_2077_, v___x_2076_);
v_remainder_2079_ = lean_uint64_land(v___x_2058_, v___x_2078_);
v___x_2080_ = lean_uint64_sub(v___x_2067_, v___x_2076_);
v_half_2081_ = lean_uint64_shift_left(v___x_2076_, v___x_2080_);
v___x_2082_ = lean_uint64_dec_lt(v_remainder_2079_, v_half_2081_);
if (v___x_2082_ == 0)
{
uint8_t v___x_2083_; 
v___x_2083_ = lean_uint64_dec_lt(v_half_2081_, v_remainder_2079_);
if (v___x_2083_ == 0)
{
uint64_t v___x_2084_; uint8_t v___x_2085_; 
v___x_2084_ = lean_uint64_land(v_quotient_2075_, v___x_2076_);
v___x_2085_ = lean_uint64_dec_eq(v___x_2084_, v___x_2064_);
if (v___x_2085_ == 0)
{
uint64_t v___x_2086_; 
v___x_2086_ = lean_uint64_add(v_quotient_2075_, v___x_2076_);
v___y_1683_ = v___y_2052_;
v___y_1684_ = v___x_2064_;
v___y_1685_ = v___y_2053_;
v___y_1686_ = v___x_2086_;
goto v___jp_1682_;
}
else
{
v___y_1683_ = v___y_2052_;
v___y_1684_ = v___x_2064_;
v___y_1685_ = v___y_2053_;
v___y_1686_ = v_quotient_2075_;
goto v___jp_1682_;
}
}
else
{
uint64_t v___x_2087_; 
v___x_2087_ = lean_uint64_add(v_quotient_2075_, v___x_2076_);
v___y_1683_ = v___y_2052_;
v___y_1684_ = v___x_2064_;
v___y_1685_ = v___y_2053_;
v___y_1686_ = v___x_2087_;
goto v___jp_1682_;
}
}
else
{
v___y_1683_ = v___y_2052_;
v___y_1684_ = v___x_2064_;
v___y_1685_ = v___y_2053_;
v___y_1686_ = v_quotient_2075_;
goto v___jp_1682_;
}
}
}
else
{
v___y_1683_ = v___y_2052_;
v___y_1684_ = v___x_2064_;
v___y_1685_ = v___y_2053_;
v___y_1686_ = v___x_2058_;
goto v___jp_1682_;
}
}
else
{
if (v___y_2053_ == 0)
{
uint32_t v___x_2088_; 
v___x_2088_ = 0;
return v___x_2088_;
}
else
{
uint32_t v___x_2089_; 
v___x_2089_ = 2147483648;
return v___x_2089_;
}
}
}
}
}
v___jp_2093_:
{
uint64_t v___x_2099_; uint64_t v___x_2100_; uint8_t v___x_2101_; 
v___x_2099_ = lean_uint32_to_uint64(v_ey_2092_);
v___x_2100_ = 0ULL;
v___x_2101_ = lean_uint64_dec_eq(v___x_2099_, v___x_2100_);
if (v___x_2101_ == 0)
{
uint64_t v___x_2102_; uint64_t v___x_2103_; 
v___x_2102_ = 1ULL;
v___x_2103_ = lean_uint64_sub(v___x_2099_, v___x_2102_);
v___y_2052_ = v___y_2094_;
v___y_2053_ = v___y_2095_;
v___y_2054_ = v___y_2098_;
v___y_2055_ = v___y_2096_;
v___y_2056_ = v___y_2097_;
v___y_2057_ = v___x_2103_;
goto v___jp_2051_;
}
else
{
v___y_2052_ = v___y_2094_;
v___y_2053_ = v___y_2095_;
v___y_2054_ = v___y_2098_;
v___y_2055_ = v___y_2096_;
v___y_2056_ = v___y_2097_;
v___y_2057_ = v___x_2100_;
goto v___jp_2051_;
}
}
v___jp_2104_:
{
uint64_t v___x_2109_; uint64_t v___x_2110_; uint8_t v___x_2111_; 
v___x_2109_ = lean_uint32_to_uint64(v_ex_2090_);
v___x_2110_ = 0ULL;
v___x_2111_ = lean_uint64_dec_eq(v___x_2109_, v___x_2110_);
if (v___x_2111_ == 0)
{
uint64_t v___x_2112_; uint64_t v___x_2113_; 
v___x_2112_ = 1ULL;
v___x_2113_ = lean_uint64_sub(v___x_2109_, v___x_2112_);
v___y_2094_ = v___y_2105_;
v___y_2095_ = v___y_2106_;
v___y_2096_ = v___y_2107_;
v___y_2097_ = v___y_2108_;
v___y_2098_ = v___x_2113_;
goto v___jp_2093_;
}
else
{
v___y_2094_ = v___y_2105_;
v___y_2095_ = v___y_2106_;
v___y_2096_ = v___y_2107_;
v___y_2097_ = v___y_2108_;
v___y_2098_ = v___x_2110_;
goto v___jp_2093_;
}
}
v___jp_2114_:
{
uint32_t v___x_2119_; uint8_t v___x_2120_; 
v___x_2119_ = 0;
v___x_2120_ = lean_uint32_dec_eq(v_ey_2092_, v___x_2119_);
if (v___x_2120_ == 0)
{
uint64_t v___x_2121_; uint64_t v___x_2122_; uint64_t v___x_2123_; 
v___x_2121_ = lean_uint32_to_uint64(v___y_2117_);
v___x_2122_ = 8388608ULL;
v___x_2123_ = lean_uint64_lor(v___x_2121_, v___x_2122_);
v___y_2105_ = v___y_2115_;
v___y_2106_ = v___y_2116_;
v___y_2107_ = v___y_2118_;
v___y_2108_ = v___x_2123_;
goto v___jp_2104_;
}
else
{
uint64_t v___x_2124_; 
v___x_2124_ = lean_uint32_to_uint64(v___y_2117_);
v___y_2105_ = v___y_2115_;
v___y_2106_ = v___y_2116_;
v___y_2107_ = v___y_2118_;
v___y_2108_ = v___x_2124_;
goto v___jp_2104_;
}
}
v___jp_2125_:
{
uint32_t v___x_2127_; uint32_t v_xFraction_2128_; uint32_t v_yFraction_2129_; uint32_t v___x_2130_; uint8_t v___x_2131_; 
v___x_2127_ = 8388607;
v_xFraction_2128_ = lean_uint32_land(v___y_1645_, v___x_2127_);
v_yFraction_2129_ = lean_uint32_land(v___y_1646_, v___x_2127_);
v___x_2130_ = 0;
v___x_2131_ = lean_uint32_dec_eq(v_ex_2090_, v___x_2130_);
if (v___x_2131_ == 0)
{
uint64_t v___x_2132_; uint64_t v___x_2133_; uint64_t v___x_2134_; 
v___x_2132_ = lean_uint32_to_uint64(v_xFraction_2128_);
v___x_2133_ = 8388608ULL;
v___x_2134_ = lean_uint64_lor(v___x_2132_, v___x_2133_);
v___y_2115_ = v___x_2127_;
v___y_2116_ = v___y_2126_;
v___y_2117_ = v_yFraction_2129_;
v___y_2118_ = v___x_2134_;
goto v___jp_2114_;
}
else
{
uint64_t v___x_2135_; 
v___x_2135_ = lean_uint32_to_uint64(v_xFraction_2128_);
v___y_2115_ = v___x_2127_;
v___y_2116_ = v___y_2126_;
v___y_2117_ = v_yFraction_2129_;
v___y_2118_ = v___x_2135_;
goto v___jp_2114_;
}
}
v___jp_2139_:
{
if (v___y_2141_ == 0)
{
v___y_2126_ = v___x_2138_;
goto v___jp_2125_;
}
else
{
v___y_2126_ = v___y_2140_;
goto v___jp_2125_;
}
}
v___jp_2142_:
{
if (v___y_2144_ == 0)
{
if (v___y_2145_ == 0)
{
v___y_2140_ = v___y_2143_;
v___y_2141_ = v___x_2138_;
goto v___jp_2139_;
}
else
{
v___y_2126_ = v___x_2138_;
goto v___jp_2125_;
}
}
else
{
v___y_2140_ = v___y_2143_;
v___y_2141_ = v___y_2145_;
goto v___jp_2139_;
}
}
v___jp_2146_:
{
uint32_t v___x_2149_; uint32_t v___x_2150_; uint32_t v___x_2151_; uint8_t v___x_2152_; 
v___x_2149_ = 2147483648;
v___x_2150_ = lean_uint32_land(v___y_1646_, v___x_2149_);
v___x_2151_ = 0;
v___x_2152_ = lean_uint32_dec_eq(v___x_2150_, v___x_2151_);
if (v___x_2152_ == 0)
{
v___y_2143_ = v___y_2147_;
v___y_2144_ = v___y_2148_;
v___y_2145_ = v___x_2138_;
goto v___jp_2142_;
}
else
{
v___y_2143_ = v___y_2147_;
v___y_2144_ = v___y_2148_;
v___y_2145_ = v___y_2147_;
goto v___jp_2142_;
}
}
v___jp_2153_:
{
if (v___y_2154_ == 0)
{
uint32_t v___x_2155_; uint32_t v___x_2156_; uint32_t v___x_2157_; uint8_t v___x_2158_; 
v___x_2155_ = 2147483648;
v___x_2156_ = lean_uint32_land(v___y_1645_, v___x_2155_);
v___x_2157_ = 0;
v___x_2158_ = lean_uint32_dec_eq(v___x_2156_, v___x_2157_);
if (v___x_2158_ == 0)
{
v___y_2147_ = v___y_2154_;
v___y_2148_ = v___x_2138_;
goto v___jp_2146_;
}
else
{
v___y_2147_ = v___y_2154_;
v___y_2148_ = v___y_2154_;
goto v___jp_2146_;
}
}
else
{
lean_object* v___x_2159_; lean_object* v___x_2160_; lean_object* v___x_2161_; uint32_t v___x_2162_; 
v___x_2159_ = lean_uint32_to_nat(v___y_1645_);
v___x_2160_ = lean_uint32_to_nat(v___y_1646_);
v___x_2161_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2159_, v___x_2160_);
v___x_2162_ = lean_uint32_of_nat(v___x_2161_);
lean_dec(v___x_2161_);
return v___x_2162_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_2177_, lean_object* v___y_2178_){
_start:
{
uint32_t v___y_11079__boxed_2179_; uint32_t v___y_11080__boxed_2180_; uint32_t v_res_2181_; lean_object* v_r_2182_; 
v___y_11079__boxed_2179_ = lean_unbox_uint32(v___y_2177_);
lean_dec(v___y_2177_);
v___y_11080__boxed_2180_ = lean_unbox_uint32(v___y_2178_);
lean_dec(v___y_2178_);
v_res_2181_ = lp_competition_main___lam__3(v___y_11079__boxed_2179_, v___y_11080__boxed_2180_);
v_r_2182_ = lean_box_uint32(v_res_2181_);
return v_r_2182_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2191_; lean_object* v___x_2192_; 
v___x_2191_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_2192_ = lean_io_getenv(v___x_2191_);
if (lean_obj_tag(v___x_2192_) == 0)
{
lean_object* v___f_2193_; lean_object* v___f_2194_; lean_object* v___x_2195_; lean_object* v___x_2196_; lean_object* v___x_2197_; 
v___f_2193_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2194_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_2195_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2196_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2197_ = lp_competition_Bench_runFull(v___f_2193_, v___f_2194_, v___x_2195_, v___x_2196_);
return v___x_2197_;
}
else
{
lean_object* v___f_2198_; lean_object* v___f_2199_; lean_object* v___x_2200_; lean_object* v___x_2201_; lean_object* v___x_2202_; 
lean_dec_ref_known(v___x_2192_, 1);
v___f_2198_ = ((lean_object*)(lp_competition_main___closed__5));
v___f_2199_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_2200_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2201_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2202_ = lp_competition_Bench_Suite_run(v___f_2198_, v___f_2199_, v___x_2200_, v___x_2201_);
return v___x_2202_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_2203_){
_start:
{
lean_object* v_res_2204_; 
v_res_2204_ = _lean_main();
return v_res_2204_;
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
