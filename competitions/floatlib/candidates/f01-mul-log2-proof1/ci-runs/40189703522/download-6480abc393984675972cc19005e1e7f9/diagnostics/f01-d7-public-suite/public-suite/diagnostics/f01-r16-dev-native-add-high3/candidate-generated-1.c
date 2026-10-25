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
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
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
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lean_io_getenv(lean_object*);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
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
uint32_t v___y_4_; uint32_t v___y_5_; uint32_t v___y_6_; uint32_t v___y_7_; uint32_t v___y_8_; uint32_t v___y_9_; uint32_t v___y_16_; uint32_t v___y_17_; uint32_t v___y_18_; uint32_t v___y_19_; uint32_t v___y_20_; uint32_t v___y_21_; uint8_t v___y_32_; uint8_t v___y_46_; uint8_t v___y_60_; uint8_t v___y_77_; float v___y_84_; float v___y_85_; float v___y_99_; uint8_t v___y_100_; float v___y_115_; uint8_t v___y_125_; uint8_t v___y_145_; uint8_t v___y_159_; uint8_t v___y_173_; uint8_t v___y_190_; float v___y_197_; float v___y_198_; float v___y_212_; uint8_t v___y_213_; float v___y_228_; uint8_t v___y_238_; uint8_t v___y_258_; uint8_t v___y_272_; uint8_t v___y_286_; uint8_t v___y_303_; float v___y_310_; float v___y_311_; float v___y_325_; uint8_t v___y_326_; float v___y_341_; uint32_t v___y_351_; uint8_t v___y_352_; uint8_t v___y_371_; uint8_t v___y_385_; uint8_t v___y_399_; uint8_t v___y_416_; float v___y_423_; float v___y_424_; float v___y_438_; uint8_t v___y_439_; float v___y_454_; uint32_t v___y_464_; uint32_t v___y_465_; uint8_t v___y_466_; uint32_t v___y_479_; uint32_t v___y_480_; uint32_t v___y_481_; uint32_t v___y_482_; uint32_t v___y_483_; uint32_t v___y_484_; uint32_t v___y_508_; uint32_t v___y_531_; uint32_t v___y_532_; uint8_t v___y_533_; uint32_t v___y_537_; uint32_t v___y_538_; uint32_t v___y_539_; uint32_t v___y_540_; uint32_t v___y_548_; uint32_t v___y_549_; uint32_t v___y_550_; uint32_t v___y_551_; uint32_t v___y_552_; uint32_t v___y_553_; uint32_t v___y_554_; uint32_t v___y_565_; uint32_t v___y_566_; uint32_t v___y_567_; uint32_t v___y_568_; uint32_t v___y_579_; uint8_t v___y_600_; uint32_t v___y_610_; uint32_t v___y_611_; uint32_t v___y_612_; uint32_t v___y_613_; uint32_t v___y_614_; uint32_t v___y_620_; uint32_t v___y_621_; uint8_t v___y_632_; uint32_t v___y_642_; uint32_t v___y_643_; uint32_t v___y_644_; uint32_t v___y_645_; uint32_t v___y_655_; uint8_t v___y_666_; uint32_t v___x_682_; uint32_t v___x_683_; uint32_t v___x_684_; uint32_t v___x_685_; uint32_t v___x_686_; uint32_t v___x_687_; uint32_t v___x_688_; uint8_t v___x_689_; 
v___x_682_ = 23;
v___x_683_ = lean_uint32_shift_right(v___y_1_, v___x_682_);
v___x_684_ = 255;
v___x_685_ = lean_uint32_land(v___x_683_, v___x_684_);
v___x_686_ = 1;
v___x_687_ = lean_uint32_sub(v___x_685_, v___x_686_);
v___x_688_ = 253;
v___x_689_ = lean_uint32_dec_le(v___x_687_, v___x_688_);
if (v___x_689_ == 0)
{
v___y_666_ = v___x_689_;
goto v___jp_665_;
}
else
{
uint32_t v___x_690_; uint32_t v___x_691_; uint32_t v___x_692_; uint8_t v___x_693_; 
v___x_690_ = lean_uint32_shift_right(v___y_2_, v___x_682_);
v___x_691_ = lean_uint32_land(v___x_690_, v___x_684_);
v___x_692_ = lean_uint32_sub(v___x_691_, v___x_686_);
v___x_693_ = lean_uint32_dec_le(v___x_692_, v___x_688_);
v___y_666_ = v___x_693_;
goto v___jp_665_;
}
v___jp_3_:
{
uint32_t v___x_10_; uint32_t v___x_11_; uint32_t v___x_12_; uint32_t v___x_13_; uint32_t v___x_14_; 
v___x_10_ = lean_uint32_land(v___y_6_, v___y_4_);
v___x_11_ = lean_uint32_shift_left(v___x_10_, v___y_8_);
v___x_12_ = lean_uint32_lor(v___y_9_, v___x_11_);
v___x_13_ = lean_uint32_land(v___y_7_, v___y_5_);
v___x_14_ = lean_uint32_lor(v___x_12_, v___x_13_);
return v___x_14_;
}
v___jp_15_:
{
uint8_t v___x_22_; uint32_t v___x_23_; uint32_t v___x_24_; 
v___x_22_ = lean_uint32_dec_le(v___y_19_, v___y_21_);
v___x_23_ = 8388607;
v___x_24_ = lean_uint32_land(v___y_17_, v___x_23_);
if (v___x_22_ == 0)
{
uint32_t v___x_25_; 
v___x_25_ = 0;
v___y_4_ = v___y_16_;
v___y_5_ = v___x_23_;
v___y_6_ = v___y_18_;
v___y_7_ = v___x_24_;
v___y_8_ = v___y_20_;
v___y_9_ = v___x_25_;
goto v___jp_3_;
}
else
{
v___y_4_ = v___y_16_;
v___y_5_ = v___x_23_;
v___y_6_ = v___y_18_;
v___y_7_ = v___x_24_;
v___y_8_ = v___y_20_;
v___y_9_ = v___y_19_;
goto v___jp_3_;
}
}
v___jp_26_:
{
lean_object* v___x_27_; lean_object* v___x_28_; lean_object* v___x_29_; uint32_t v___x_30_; 
v___x_27_ = lean_uint32_to_nat(v___y_1_);
v___x_28_ = lean_uint32_to_nat(v___y_2_);
v___x_29_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_27_, v___x_28_);
v___x_30_ = lean_uint32_of_nat(v___x_29_);
lean_dec(v___x_29_);
return v___x_30_;
}
v___jp_31_:
{
if (v___y_32_ == 0)
{
goto v___jp_26_;
}
else
{
uint32_t v___x_33_; uint32_t v___x_34_; 
v___x_33_ = 4194304;
v___x_34_ = lean_uint32_lor(v___y_2_, v___x_33_);
return v___x_34_;
}
}
v___jp_35_:
{
uint32_t v___x_36_; uint32_t v___x_37_; uint32_t v___x_38_; uint32_t v___x_39_; uint8_t v___x_40_; 
v___x_36_ = 23;
v___x_37_ = lean_uint32_shift_right(v___y_2_, v___x_36_);
v___x_38_ = 255;
v___x_39_ = lean_uint32_land(v___x_37_, v___x_38_);
v___x_40_ = lean_uint32_dec_eq(v___x_39_, v___x_38_);
if (v___x_40_ == 0)
{
v___y_32_ = v___x_40_;
goto v___jp_31_;
}
else
{
uint32_t v___x_41_; uint32_t v___x_42_; uint32_t v___x_43_; uint8_t v___x_44_; 
v___x_41_ = 8388607;
v___x_42_ = lean_uint32_land(v___y_2_, v___x_41_);
v___x_43_ = 0;
v___x_44_ = lean_uint32_dec_eq(v___x_42_, v___x_43_);
if (v___x_44_ == 0)
{
v___y_32_ = v___x_40_;
goto v___jp_31_;
}
else
{
goto v___jp_26_;
}
}
}
v___jp_45_:
{
if (v___y_46_ == 0)
{
goto v___jp_35_;
}
else
{
uint32_t v___x_47_; uint32_t v___x_48_; 
v___x_47_ = 4194304;
v___x_48_ = lean_uint32_lor(v___y_1_, v___x_47_);
return v___x_48_;
}
}
v___jp_49_:
{
uint32_t v___x_50_; uint32_t v___x_51_; uint32_t v___x_52_; uint32_t v___x_53_; uint8_t v___x_54_; 
v___x_50_ = 23;
v___x_51_ = lean_uint32_shift_right(v___y_1_, v___x_50_);
v___x_52_ = 255;
v___x_53_ = lean_uint32_land(v___x_51_, v___x_52_);
v___x_54_ = lean_uint32_dec_eq(v___x_53_, v___x_52_);
if (v___x_54_ == 0)
{
v___y_46_ = v___x_54_;
goto v___jp_45_;
}
else
{
uint32_t v___x_55_; uint32_t v___x_56_; uint32_t v___x_57_; uint8_t v___x_58_; 
v___x_55_ = 8388607;
v___x_56_ = lean_uint32_land(v___y_1_, v___x_55_);
v___x_57_ = 0;
v___x_58_ = lean_uint32_dec_eq(v___x_56_, v___x_57_);
if (v___x_58_ == 0)
{
v___y_46_ = v___x_54_;
goto v___jp_45_;
}
else
{
goto v___jp_35_;
}
}
}
v___jp_59_:
{
if (v___y_60_ == 0)
{
goto v___jp_49_;
}
else
{
uint32_t v___x_61_; uint32_t v___x_62_; uint32_t v___x_63_; uint8_t v___x_64_; 
v___x_61_ = 4194304;
v___x_62_ = lean_uint32_land(v___y_2_, v___x_61_);
v___x_63_ = 0;
v___x_64_ = lean_uint32_dec_eq(v___x_62_, v___x_63_);
if (v___x_64_ == 0)
{
goto v___jp_49_;
}
else
{
uint32_t v___x_65_; 
v___x_65_ = lean_uint32_lor(v___y_2_, v___x_61_);
return v___x_65_;
}
}
}
v___jp_66_:
{
uint32_t v___x_67_; uint32_t v___x_68_; uint32_t v___x_69_; uint32_t v___x_70_; uint8_t v___x_71_; 
v___x_67_ = 23;
v___x_68_ = lean_uint32_shift_right(v___y_2_, v___x_67_);
v___x_69_ = 255;
v___x_70_ = lean_uint32_land(v___x_68_, v___x_69_);
v___x_71_ = lean_uint32_dec_eq(v___x_70_, v___x_69_);
if (v___x_71_ == 0)
{
v___y_60_ = v___x_71_;
goto v___jp_59_;
}
else
{
uint32_t v___x_72_; uint32_t v___x_73_; uint32_t v___x_74_; uint8_t v___x_75_; 
v___x_72_ = 8388607;
v___x_73_ = lean_uint32_land(v___y_2_, v___x_72_);
v___x_74_ = 0;
v___x_75_ = lean_uint32_dec_eq(v___x_73_, v___x_74_);
if (v___x_75_ == 0)
{
v___y_60_ = v___x_71_;
goto v___jp_59_;
}
else
{
goto v___jp_49_;
}
}
}
v___jp_76_:
{
if (v___y_77_ == 0)
{
goto v___jp_66_;
}
else
{
uint32_t v___x_78_; uint32_t v___x_79_; uint32_t v___x_80_; uint8_t v___x_81_; 
v___x_78_ = 4194304;
v___x_79_ = lean_uint32_land(v___y_1_, v___x_78_);
v___x_80_ = 0;
v___x_81_ = lean_uint32_dec_eq(v___x_79_, v___x_80_);
if (v___x_81_ == 0)
{
goto v___jp_66_;
}
else
{
uint32_t v___x_82_; 
v___x_82_ = lean_uint32_lor(v___y_1_, v___x_78_);
return v___x_82_;
}
}
}
v___jp_83_:
{
float v_result_86_; uint8_t v___x_87_; 
v_result_86_ = lean_float32_add(v___y_84_, v___y_85_);
v___x_87_ = lean_float32_beq(v_result_86_, v_result_86_);
if (v___x_87_ == 0)
{
uint32_t v___x_88_; uint32_t v___x_89_; uint32_t v___x_90_; uint32_t v___x_91_; uint8_t v___x_92_; 
v___x_88_ = 23;
v___x_89_ = lean_uint32_shift_right(v___y_1_, v___x_88_);
v___x_90_ = 255;
v___x_91_ = lean_uint32_land(v___x_89_, v___x_90_);
v___x_92_ = lean_uint32_dec_eq(v___x_91_, v___x_90_);
if (v___x_92_ == 0)
{
v___y_77_ = v___x_92_;
goto v___jp_76_;
}
else
{
uint32_t v___x_93_; uint32_t v___x_94_; uint32_t v___x_95_; uint8_t v___x_96_; 
v___x_93_ = 8388607;
v___x_94_ = lean_uint32_land(v___y_1_, v___x_93_);
v___x_95_ = 0;
v___x_96_ = lean_uint32_dec_eq(v___x_94_, v___x_95_);
if (v___x_96_ == 0)
{
v___y_77_ = v___x_92_;
goto v___jp_76_;
}
else
{
goto v___jp_66_;
}
}
}
else
{
uint32_t v___x_97_; 
v___x_97_ = lean_float32_to_bits(v_result_86_);
return v___x_97_;
}
}
v___jp_98_:
{
if (v___y_100_ == 0)
{
float v___x_101_; 
v___x_101_ = lean_float32_of_bits(v___y_2_);
v___y_84_ = v___y_99_;
v___y_85_ = v___x_101_;
goto v___jp_83_;
}
else
{
uint32_t v___x_102_; uint32_t v___x_103_; uint32_t v___x_104_; uint32_t v___x_105_; float v___x_106_; lean_object* v___x_107_; uint32_t v___x_108_; uint32_t v___x_109_; lean_object* v___x_110_; lean_object* v___x_111_; float v___x_112_; float v___x_113_; 
v___x_102_ = 8388607;
v___x_103_ = lean_uint32_land(v___y_2_, v___x_102_);
v___x_104_ = 8388608;
v___x_105_ = lean_uint32_lor(v___x_103_, v___x_104_);
v___x_106_ = lean_uint32_to_float32(v___x_105_);
v___x_107_ = lp_competition_R2W01b_scaleTable;
v___x_108_ = 23;
v___x_109_ = lean_uint32_shift_right(v___y_2_, v___x_108_);
v___x_110_ = lean_uint32_to_nat(v___x_109_);
v___x_111_ = lean_array_fget_borrowed(v___x_107_, v___x_110_);
lean_dec(v___x_110_);
v___x_112_ = lean_unbox_float32(v___x_111_);
v___x_113_ = lean_float32_mul(v___x_106_, v___x_112_);
v___y_84_ = v___y_99_;
v___y_85_ = v___x_113_;
goto v___jp_83_;
}
}
v___jp_114_:
{
uint32_t v___x_116_; uint32_t v_a_117_; uint32_t v___x_118_; uint32_t v___x_119_; uint32_t v___x_120_; uint8_t v___x_121_; 
v___x_116_ = 2147483647;
v_a_117_ = lean_uint32_land(v___y_2_, v___x_116_);
v___x_118_ = 201326591;
v___x_119_ = 1;
v___x_120_ = lean_uint32_sub(v_a_117_, v___x_119_);
v___x_121_ = lean_uint32_dec_le(v___x_118_, v___x_120_);
if (v___x_121_ == 0)
{
v___y_99_ = v___y_115_;
v___y_100_ = v___x_121_;
goto v___jp_98_;
}
else
{
uint32_t v___x_122_; uint8_t v___x_123_; 
v___x_122_ = 2139095040;
v___x_123_ = lean_uint32_dec_lt(v_a_117_, v___x_122_);
v___y_99_ = v___y_115_;
v___y_100_ = v___x_123_;
goto v___jp_98_;
}
}
v___jp_124_:
{
if (v___y_125_ == 0)
{
float v___x_126_; 
v___x_126_ = lean_float32_of_bits(v___y_1_);
v___y_115_ = v___x_126_;
goto v___jp_114_;
}
else
{
uint32_t v___x_127_; uint32_t v___x_128_; uint32_t v___x_129_; uint32_t v___x_130_; float v___x_131_; lean_object* v___x_132_; uint32_t v___x_133_; uint32_t v___x_134_; lean_object* v___x_135_; lean_object* v___x_136_; float v___x_137_; float v___x_138_; 
v___x_127_ = 8388607;
v___x_128_ = lean_uint32_land(v___y_1_, v___x_127_);
v___x_129_ = 8388608;
v___x_130_ = lean_uint32_lor(v___x_128_, v___x_129_);
v___x_131_ = lean_uint32_to_float32(v___x_130_);
v___x_132_ = lp_competition_R2W01b_scaleTable;
v___x_133_ = 23;
v___x_134_ = lean_uint32_shift_right(v___y_1_, v___x_133_);
v___x_135_ = lean_uint32_to_nat(v___x_134_);
v___x_136_ = lean_array_fget_borrowed(v___x_132_, v___x_135_);
lean_dec(v___x_135_);
v___x_137_ = lean_unbox_float32(v___x_136_);
v___x_138_ = lean_float32_mul(v___x_131_, v___x_137_);
v___y_115_ = v___x_138_;
goto v___jp_114_;
}
}
v___jp_139_:
{
lean_object* v___x_140_; lean_object* v___x_141_; lean_object* v___x_142_; uint32_t v___x_143_; 
v___x_140_ = lean_uint32_to_nat(v___y_1_);
v___x_141_ = lean_uint32_to_nat(v___y_2_);
v___x_142_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_140_, v___x_141_);
v___x_143_ = lean_uint32_of_nat(v___x_142_);
lean_dec(v___x_142_);
return v___x_143_;
}
v___jp_144_:
{
if (v___y_145_ == 0)
{
goto v___jp_139_;
}
else
{
uint32_t v___x_146_; uint32_t v___x_147_; 
v___x_146_ = 4194304;
v___x_147_ = lean_uint32_lor(v___y_2_, v___x_146_);
return v___x_147_;
}
}
v___jp_148_:
{
uint32_t v___x_149_; uint32_t v___x_150_; uint32_t v___x_151_; uint32_t v___x_152_; uint8_t v___x_153_; 
v___x_149_ = 23;
v___x_150_ = lean_uint32_shift_right(v___y_2_, v___x_149_);
v___x_151_ = 255;
v___x_152_ = lean_uint32_land(v___x_150_, v___x_151_);
v___x_153_ = lean_uint32_dec_eq(v___x_152_, v___x_151_);
if (v___x_153_ == 0)
{
v___y_145_ = v___x_153_;
goto v___jp_144_;
}
else
{
uint32_t v___x_154_; uint32_t v___x_155_; uint32_t v___x_156_; uint8_t v___x_157_; 
v___x_154_ = 8388607;
v___x_155_ = lean_uint32_land(v___y_2_, v___x_154_);
v___x_156_ = 0;
v___x_157_ = lean_uint32_dec_eq(v___x_155_, v___x_156_);
if (v___x_157_ == 0)
{
v___y_145_ = v___x_153_;
goto v___jp_144_;
}
else
{
goto v___jp_139_;
}
}
}
v___jp_158_:
{
if (v___y_159_ == 0)
{
goto v___jp_148_;
}
else
{
uint32_t v___x_160_; uint32_t v___x_161_; 
v___x_160_ = 4194304;
v___x_161_ = lean_uint32_lor(v___y_1_, v___x_160_);
return v___x_161_;
}
}
v___jp_162_:
{
uint32_t v___x_163_; uint32_t v___x_164_; uint32_t v___x_165_; uint32_t v___x_166_; uint8_t v___x_167_; 
v___x_163_ = 23;
v___x_164_ = lean_uint32_shift_right(v___y_1_, v___x_163_);
v___x_165_ = 255;
v___x_166_ = lean_uint32_land(v___x_164_, v___x_165_);
v___x_167_ = lean_uint32_dec_eq(v___x_166_, v___x_165_);
if (v___x_167_ == 0)
{
v___y_159_ = v___x_167_;
goto v___jp_158_;
}
else
{
uint32_t v___x_168_; uint32_t v___x_169_; uint32_t v___x_170_; uint8_t v___x_171_; 
v___x_168_ = 8388607;
v___x_169_ = lean_uint32_land(v___y_1_, v___x_168_);
v___x_170_ = 0;
v___x_171_ = lean_uint32_dec_eq(v___x_169_, v___x_170_);
if (v___x_171_ == 0)
{
v___y_159_ = v___x_167_;
goto v___jp_158_;
}
else
{
goto v___jp_148_;
}
}
}
v___jp_172_:
{
if (v___y_173_ == 0)
{
goto v___jp_162_;
}
else
{
uint32_t v___x_174_; uint32_t v___x_175_; uint32_t v___x_176_; uint8_t v___x_177_; 
v___x_174_ = 4194304;
v___x_175_ = lean_uint32_land(v___y_2_, v___x_174_);
v___x_176_ = 0;
v___x_177_ = lean_uint32_dec_eq(v___x_175_, v___x_176_);
if (v___x_177_ == 0)
{
goto v___jp_162_;
}
else
{
uint32_t v___x_178_; 
v___x_178_ = lean_uint32_lor(v___y_2_, v___x_174_);
return v___x_178_;
}
}
}
v___jp_179_:
{
uint32_t v___x_180_; uint32_t v___x_181_; uint32_t v___x_182_; uint32_t v___x_183_; uint8_t v___x_184_; 
v___x_180_ = 23;
v___x_181_ = lean_uint32_shift_right(v___y_2_, v___x_180_);
v___x_182_ = 255;
v___x_183_ = lean_uint32_land(v___x_181_, v___x_182_);
v___x_184_ = lean_uint32_dec_eq(v___x_183_, v___x_182_);
if (v___x_184_ == 0)
{
v___y_173_ = v___x_184_;
goto v___jp_172_;
}
else
{
uint32_t v___x_185_; uint32_t v___x_186_; uint32_t v___x_187_; uint8_t v___x_188_; 
v___x_185_ = 8388607;
v___x_186_ = lean_uint32_land(v___y_2_, v___x_185_);
v___x_187_ = 0;
v___x_188_ = lean_uint32_dec_eq(v___x_186_, v___x_187_);
if (v___x_188_ == 0)
{
v___y_173_ = v___x_184_;
goto v___jp_172_;
}
else
{
goto v___jp_162_;
}
}
}
v___jp_189_:
{
if (v___y_190_ == 0)
{
goto v___jp_179_;
}
else
{
uint32_t v___x_191_; uint32_t v___x_192_; uint32_t v___x_193_; uint8_t v___x_194_; 
v___x_191_ = 4194304;
v___x_192_ = lean_uint32_land(v___y_1_, v___x_191_);
v___x_193_ = 0;
v___x_194_ = lean_uint32_dec_eq(v___x_192_, v___x_193_);
if (v___x_194_ == 0)
{
goto v___jp_179_;
}
else
{
uint32_t v___x_195_; 
v___x_195_ = lean_uint32_lor(v___y_1_, v___x_191_);
return v___x_195_;
}
}
}
v___jp_196_:
{
float v_result_199_; uint8_t v___x_200_; 
v_result_199_ = lean_float32_add(v___y_197_, v___y_198_);
v___x_200_ = lean_float32_beq(v_result_199_, v_result_199_);
if (v___x_200_ == 0)
{
uint32_t v___x_201_; uint32_t v___x_202_; uint32_t v___x_203_; uint32_t v___x_204_; uint8_t v___x_205_; 
v___x_201_ = 23;
v___x_202_ = lean_uint32_shift_right(v___y_1_, v___x_201_);
v___x_203_ = 255;
v___x_204_ = lean_uint32_land(v___x_202_, v___x_203_);
v___x_205_ = lean_uint32_dec_eq(v___x_204_, v___x_203_);
if (v___x_205_ == 0)
{
v___y_190_ = v___x_205_;
goto v___jp_189_;
}
else
{
uint32_t v___x_206_; uint32_t v___x_207_; uint32_t v___x_208_; uint8_t v___x_209_; 
v___x_206_ = 8388607;
v___x_207_ = lean_uint32_land(v___y_1_, v___x_206_);
v___x_208_ = 0;
v___x_209_ = lean_uint32_dec_eq(v___x_207_, v___x_208_);
if (v___x_209_ == 0)
{
v___y_190_ = v___x_205_;
goto v___jp_189_;
}
else
{
goto v___jp_179_;
}
}
}
else
{
uint32_t v___x_210_; 
v___x_210_ = lean_float32_to_bits(v_result_199_);
return v___x_210_;
}
}
v___jp_211_:
{
if (v___y_213_ == 0)
{
float v___x_214_; 
v___x_214_ = lean_float32_of_bits(v___y_2_);
v___y_197_ = v___y_212_;
v___y_198_ = v___x_214_;
goto v___jp_196_;
}
else
{
uint32_t v___x_215_; uint32_t v___x_216_; uint32_t v___x_217_; uint32_t v___x_218_; float v___x_219_; lean_object* v___x_220_; uint32_t v___x_221_; uint32_t v___x_222_; lean_object* v___x_223_; lean_object* v___x_224_; float v___x_225_; float v___x_226_; 
v___x_215_ = 8388607;
v___x_216_ = lean_uint32_land(v___y_2_, v___x_215_);
v___x_217_ = 8388608;
v___x_218_ = lean_uint32_lor(v___x_216_, v___x_217_);
v___x_219_ = lean_uint32_to_float32(v___x_218_);
v___x_220_ = lp_competition_R2W01b_scaleTable;
v___x_221_ = 23;
v___x_222_ = lean_uint32_shift_right(v___y_2_, v___x_221_);
v___x_223_ = lean_uint32_to_nat(v___x_222_);
v___x_224_ = lean_array_fget_borrowed(v___x_220_, v___x_223_);
lean_dec(v___x_223_);
v___x_225_ = lean_unbox_float32(v___x_224_);
v___x_226_ = lean_float32_mul(v___x_219_, v___x_225_);
v___y_197_ = v___y_212_;
v___y_198_ = v___x_226_;
goto v___jp_196_;
}
}
v___jp_227_:
{
uint32_t v___x_229_; uint32_t v_a_230_; uint32_t v___x_231_; uint32_t v___x_232_; uint32_t v___x_233_; uint8_t v___x_234_; 
v___x_229_ = 2147483647;
v_a_230_ = lean_uint32_land(v___y_2_, v___x_229_);
v___x_231_ = 201326591;
v___x_232_ = 1;
v___x_233_ = lean_uint32_sub(v_a_230_, v___x_232_);
v___x_234_ = lean_uint32_dec_le(v___x_231_, v___x_233_);
if (v___x_234_ == 0)
{
v___y_212_ = v___y_228_;
v___y_213_ = v___x_234_;
goto v___jp_211_;
}
else
{
uint32_t v___x_235_; uint8_t v___x_236_; 
v___x_235_ = 2139095040;
v___x_236_ = lean_uint32_dec_lt(v_a_230_, v___x_235_);
v___y_212_ = v___y_228_;
v___y_213_ = v___x_236_;
goto v___jp_211_;
}
}
v___jp_237_:
{
if (v___y_238_ == 0)
{
float v___x_239_; 
v___x_239_ = lean_float32_of_bits(v___y_1_);
v___y_228_ = v___x_239_;
goto v___jp_227_;
}
else
{
uint32_t v___x_240_; uint32_t v___x_241_; uint32_t v___x_242_; uint32_t v___x_243_; float v___x_244_; lean_object* v___x_245_; uint32_t v___x_246_; uint32_t v___x_247_; lean_object* v___x_248_; lean_object* v___x_249_; float v___x_250_; float v___x_251_; 
v___x_240_ = 8388607;
v___x_241_ = lean_uint32_land(v___y_1_, v___x_240_);
v___x_242_ = 8388608;
v___x_243_ = lean_uint32_lor(v___x_241_, v___x_242_);
v___x_244_ = lean_uint32_to_float32(v___x_243_);
v___x_245_ = lp_competition_R2W01b_scaleTable;
v___x_246_ = 23;
v___x_247_ = lean_uint32_shift_right(v___y_1_, v___x_246_);
v___x_248_ = lean_uint32_to_nat(v___x_247_);
v___x_249_ = lean_array_fget_borrowed(v___x_245_, v___x_248_);
lean_dec(v___x_248_);
v___x_250_ = lean_unbox_float32(v___x_249_);
v___x_251_ = lean_float32_mul(v___x_244_, v___x_250_);
v___y_228_ = v___x_251_;
goto v___jp_227_;
}
}
v___jp_252_:
{
lean_object* v___x_253_; lean_object* v___x_254_; lean_object* v___x_255_; uint32_t v___x_256_; 
v___x_253_ = lean_uint32_to_nat(v___y_1_);
v___x_254_ = lean_uint32_to_nat(v___y_2_);
v___x_255_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_253_, v___x_254_);
v___x_256_ = lean_uint32_of_nat(v___x_255_);
lean_dec(v___x_255_);
return v___x_256_;
}
v___jp_257_:
{
if (v___y_258_ == 0)
{
goto v___jp_252_;
}
else
{
uint32_t v___x_259_; uint32_t v___x_260_; 
v___x_259_ = 4194304;
v___x_260_ = lean_uint32_lor(v___y_2_, v___x_259_);
return v___x_260_;
}
}
v___jp_261_:
{
uint32_t v___x_262_; uint32_t v___x_263_; uint32_t v___x_264_; uint32_t v___x_265_; uint8_t v___x_266_; 
v___x_262_ = 23;
v___x_263_ = lean_uint32_shift_right(v___y_2_, v___x_262_);
v___x_264_ = 255;
v___x_265_ = lean_uint32_land(v___x_263_, v___x_264_);
v___x_266_ = lean_uint32_dec_eq(v___x_265_, v___x_264_);
if (v___x_266_ == 0)
{
v___y_258_ = v___x_266_;
goto v___jp_257_;
}
else
{
uint32_t v___x_267_; uint32_t v___x_268_; uint32_t v___x_269_; uint8_t v___x_270_; 
v___x_267_ = 8388607;
v___x_268_ = lean_uint32_land(v___y_2_, v___x_267_);
v___x_269_ = 0;
v___x_270_ = lean_uint32_dec_eq(v___x_268_, v___x_269_);
if (v___x_270_ == 0)
{
v___y_258_ = v___x_266_;
goto v___jp_257_;
}
else
{
goto v___jp_252_;
}
}
}
v___jp_271_:
{
if (v___y_272_ == 0)
{
goto v___jp_261_;
}
else
{
uint32_t v___x_273_; uint32_t v___x_274_; 
v___x_273_ = 4194304;
v___x_274_ = lean_uint32_lor(v___y_1_, v___x_273_);
return v___x_274_;
}
}
v___jp_275_:
{
uint32_t v___x_276_; uint32_t v___x_277_; uint32_t v___x_278_; uint32_t v___x_279_; uint8_t v___x_280_; 
v___x_276_ = 23;
v___x_277_ = lean_uint32_shift_right(v___y_1_, v___x_276_);
v___x_278_ = 255;
v___x_279_ = lean_uint32_land(v___x_277_, v___x_278_);
v___x_280_ = lean_uint32_dec_eq(v___x_279_, v___x_278_);
if (v___x_280_ == 0)
{
v___y_272_ = v___x_280_;
goto v___jp_271_;
}
else
{
uint32_t v___x_281_; uint32_t v___x_282_; uint32_t v___x_283_; uint8_t v___x_284_; 
v___x_281_ = 8388607;
v___x_282_ = lean_uint32_land(v___y_1_, v___x_281_);
v___x_283_ = 0;
v___x_284_ = lean_uint32_dec_eq(v___x_282_, v___x_283_);
if (v___x_284_ == 0)
{
v___y_272_ = v___x_280_;
goto v___jp_271_;
}
else
{
goto v___jp_261_;
}
}
}
v___jp_285_:
{
if (v___y_286_ == 0)
{
goto v___jp_275_;
}
else
{
uint32_t v___x_287_; uint32_t v___x_288_; uint32_t v___x_289_; uint8_t v___x_290_; 
v___x_287_ = 4194304;
v___x_288_ = lean_uint32_land(v___y_2_, v___x_287_);
v___x_289_ = 0;
v___x_290_ = lean_uint32_dec_eq(v___x_288_, v___x_289_);
if (v___x_290_ == 0)
{
goto v___jp_275_;
}
else
{
uint32_t v___x_291_; 
v___x_291_ = lean_uint32_lor(v___y_2_, v___x_287_);
return v___x_291_;
}
}
}
v___jp_292_:
{
uint32_t v___x_293_; uint32_t v___x_294_; uint32_t v___x_295_; uint32_t v___x_296_; uint8_t v___x_297_; 
v___x_293_ = 23;
v___x_294_ = lean_uint32_shift_right(v___y_2_, v___x_293_);
v___x_295_ = 255;
v___x_296_ = lean_uint32_land(v___x_294_, v___x_295_);
v___x_297_ = lean_uint32_dec_eq(v___x_296_, v___x_295_);
if (v___x_297_ == 0)
{
v___y_286_ = v___x_297_;
goto v___jp_285_;
}
else
{
uint32_t v___x_298_; uint32_t v___x_299_; uint32_t v___x_300_; uint8_t v___x_301_; 
v___x_298_ = 8388607;
v___x_299_ = lean_uint32_land(v___y_2_, v___x_298_);
v___x_300_ = 0;
v___x_301_ = lean_uint32_dec_eq(v___x_299_, v___x_300_);
if (v___x_301_ == 0)
{
v___y_286_ = v___x_297_;
goto v___jp_285_;
}
else
{
goto v___jp_275_;
}
}
}
v___jp_302_:
{
if (v___y_303_ == 0)
{
goto v___jp_292_;
}
else
{
uint32_t v___x_304_; uint32_t v___x_305_; uint32_t v___x_306_; uint8_t v___x_307_; 
v___x_304_ = 4194304;
v___x_305_ = lean_uint32_land(v___y_1_, v___x_304_);
v___x_306_ = 0;
v___x_307_ = lean_uint32_dec_eq(v___x_305_, v___x_306_);
if (v___x_307_ == 0)
{
goto v___jp_292_;
}
else
{
uint32_t v___x_308_; 
v___x_308_ = lean_uint32_lor(v___y_1_, v___x_304_);
return v___x_308_;
}
}
}
v___jp_309_:
{
float v_result_312_; uint8_t v___x_313_; 
v_result_312_ = lean_float32_add(v___y_310_, v___y_311_);
v___x_313_ = lean_float32_beq(v_result_312_, v_result_312_);
if (v___x_313_ == 0)
{
uint32_t v___x_314_; uint32_t v___x_315_; uint32_t v___x_316_; uint32_t v___x_317_; uint8_t v___x_318_; 
v___x_314_ = 23;
v___x_315_ = lean_uint32_shift_right(v___y_1_, v___x_314_);
v___x_316_ = 255;
v___x_317_ = lean_uint32_land(v___x_315_, v___x_316_);
v___x_318_ = lean_uint32_dec_eq(v___x_317_, v___x_316_);
if (v___x_318_ == 0)
{
v___y_303_ = v___x_318_;
goto v___jp_302_;
}
else
{
uint32_t v___x_319_; uint32_t v___x_320_; uint32_t v___x_321_; uint8_t v___x_322_; 
v___x_319_ = 8388607;
v___x_320_ = lean_uint32_land(v___y_1_, v___x_319_);
v___x_321_ = 0;
v___x_322_ = lean_uint32_dec_eq(v___x_320_, v___x_321_);
if (v___x_322_ == 0)
{
v___y_303_ = v___x_318_;
goto v___jp_302_;
}
else
{
goto v___jp_292_;
}
}
}
else
{
uint32_t v___x_323_; 
v___x_323_ = lean_float32_to_bits(v_result_312_);
return v___x_323_;
}
}
v___jp_324_:
{
if (v___y_326_ == 0)
{
float v___x_327_; 
v___x_327_ = lean_float32_of_bits(v___y_2_);
v___y_310_ = v___y_325_;
v___y_311_ = v___x_327_;
goto v___jp_309_;
}
else
{
uint32_t v___x_328_; uint32_t v___x_329_; uint32_t v___x_330_; uint32_t v___x_331_; float v___x_332_; lean_object* v___x_333_; uint32_t v___x_334_; uint32_t v___x_335_; lean_object* v___x_336_; lean_object* v___x_337_; float v___x_338_; float v___x_339_; 
v___x_328_ = 8388607;
v___x_329_ = lean_uint32_land(v___y_2_, v___x_328_);
v___x_330_ = 8388608;
v___x_331_ = lean_uint32_lor(v___x_329_, v___x_330_);
v___x_332_ = lean_uint32_to_float32(v___x_331_);
v___x_333_ = lp_competition_R2W01b_scaleTable;
v___x_334_ = 23;
v___x_335_ = lean_uint32_shift_right(v___y_2_, v___x_334_);
v___x_336_ = lean_uint32_to_nat(v___x_335_);
v___x_337_ = lean_array_fget_borrowed(v___x_333_, v___x_336_);
lean_dec(v___x_336_);
v___x_338_ = lean_unbox_float32(v___x_337_);
v___x_339_ = lean_float32_mul(v___x_332_, v___x_338_);
v___y_310_ = v___y_325_;
v___y_311_ = v___x_339_;
goto v___jp_309_;
}
}
v___jp_340_:
{
uint32_t v___x_342_; uint32_t v_a_343_; uint32_t v___x_344_; uint32_t v___x_345_; uint32_t v___x_346_; uint8_t v___x_347_; 
v___x_342_ = 2147483647;
v_a_343_ = lean_uint32_land(v___y_2_, v___x_342_);
v___x_344_ = 201326591;
v___x_345_ = 1;
v___x_346_ = lean_uint32_sub(v_a_343_, v___x_345_);
v___x_347_ = lean_uint32_dec_le(v___x_344_, v___x_346_);
if (v___x_347_ == 0)
{
v___y_325_ = v___y_341_;
v___y_326_ = v___x_347_;
goto v___jp_324_;
}
else
{
uint32_t v___x_348_; uint8_t v___x_349_; 
v___x_348_ = 2139095040;
v___x_349_ = lean_uint32_dec_lt(v_a_343_, v___x_348_);
v___y_325_ = v___y_341_;
v___y_326_ = v___x_349_;
goto v___jp_324_;
}
}
v___jp_350_:
{
if (v___y_352_ == 0)
{
float v___x_353_; 
v___x_353_ = lean_float32_of_bits(v___y_1_);
v___y_341_ = v___x_353_;
goto v___jp_340_;
}
else
{
uint32_t v___x_354_; uint32_t v___x_355_; uint32_t v___x_356_; float v___x_357_; lean_object* v___x_358_; uint32_t v___x_359_; uint32_t v___x_360_; lean_object* v___x_361_; lean_object* v___x_362_; float v___x_363_; float v___x_364_; 
v___x_354_ = 8388607;
v___x_355_ = lean_uint32_land(v___y_1_, v___x_354_);
v___x_356_ = lean_uint32_lor(v___x_355_, v___y_351_);
v___x_357_ = lean_uint32_to_float32(v___x_356_);
v___x_358_ = lp_competition_R2W01b_scaleTable;
v___x_359_ = 23;
v___x_360_ = lean_uint32_shift_right(v___y_1_, v___x_359_);
v___x_361_ = lean_uint32_to_nat(v___x_360_);
v___x_362_ = lean_array_fget_borrowed(v___x_358_, v___x_361_);
lean_dec(v___x_361_);
v___x_363_ = lean_unbox_float32(v___x_362_);
v___x_364_ = lean_float32_mul(v___x_357_, v___x_363_);
v___y_341_ = v___x_364_;
goto v___jp_340_;
}
}
v___jp_365_:
{
lean_object* v___x_366_; lean_object* v___x_367_; lean_object* v___x_368_; uint32_t v___x_369_; 
v___x_366_ = lean_uint32_to_nat(v___y_1_);
v___x_367_ = lean_uint32_to_nat(v___y_2_);
v___x_368_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_366_, v___x_367_);
v___x_369_ = lean_uint32_of_nat(v___x_368_);
lean_dec(v___x_368_);
return v___x_369_;
}
v___jp_370_:
{
if (v___y_371_ == 0)
{
goto v___jp_365_;
}
else
{
uint32_t v___x_372_; uint32_t v___x_373_; 
v___x_372_ = 4194304;
v___x_373_ = lean_uint32_lor(v___y_2_, v___x_372_);
return v___x_373_;
}
}
v___jp_374_:
{
uint32_t v___x_375_; uint32_t v___x_376_; uint32_t v___x_377_; uint32_t v___x_378_; uint8_t v___x_379_; 
v___x_375_ = 23;
v___x_376_ = lean_uint32_shift_right(v___y_2_, v___x_375_);
v___x_377_ = 255;
v___x_378_ = lean_uint32_land(v___x_376_, v___x_377_);
v___x_379_ = lean_uint32_dec_eq(v___x_378_, v___x_377_);
if (v___x_379_ == 0)
{
v___y_371_ = v___x_379_;
goto v___jp_370_;
}
else
{
uint32_t v___x_380_; uint32_t v___x_381_; uint32_t v___x_382_; uint8_t v___x_383_; 
v___x_380_ = 8388607;
v___x_381_ = lean_uint32_land(v___y_2_, v___x_380_);
v___x_382_ = 0;
v___x_383_ = lean_uint32_dec_eq(v___x_381_, v___x_382_);
if (v___x_383_ == 0)
{
v___y_371_ = v___x_379_;
goto v___jp_370_;
}
else
{
goto v___jp_365_;
}
}
}
v___jp_384_:
{
if (v___y_385_ == 0)
{
goto v___jp_374_;
}
else
{
uint32_t v___x_386_; uint32_t v___x_387_; 
v___x_386_ = 4194304;
v___x_387_ = lean_uint32_lor(v___y_1_, v___x_386_);
return v___x_387_;
}
}
v___jp_388_:
{
uint32_t v___x_389_; uint32_t v___x_390_; uint32_t v___x_391_; uint32_t v___x_392_; uint8_t v___x_393_; 
v___x_389_ = 23;
v___x_390_ = lean_uint32_shift_right(v___y_1_, v___x_389_);
v___x_391_ = 255;
v___x_392_ = lean_uint32_land(v___x_390_, v___x_391_);
v___x_393_ = lean_uint32_dec_eq(v___x_392_, v___x_391_);
if (v___x_393_ == 0)
{
v___y_385_ = v___x_393_;
goto v___jp_384_;
}
else
{
uint32_t v___x_394_; uint32_t v___x_395_; uint32_t v___x_396_; uint8_t v___x_397_; 
v___x_394_ = 8388607;
v___x_395_ = lean_uint32_land(v___y_1_, v___x_394_);
v___x_396_ = 0;
v___x_397_ = lean_uint32_dec_eq(v___x_395_, v___x_396_);
if (v___x_397_ == 0)
{
v___y_385_ = v___x_393_;
goto v___jp_384_;
}
else
{
goto v___jp_374_;
}
}
}
v___jp_398_:
{
if (v___y_399_ == 0)
{
goto v___jp_388_;
}
else
{
uint32_t v___x_400_; uint32_t v___x_401_; uint32_t v___x_402_; uint8_t v___x_403_; 
v___x_400_ = 4194304;
v___x_401_ = lean_uint32_land(v___y_2_, v___x_400_);
v___x_402_ = 0;
v___x_403_ = lean_uint32_dec_eq(v___x_401_, v___x_402_);
if (v___x_403_ == 0)
{
goto v___jp_388_;
}
else
{
uint32_t v___x_404_; 
v___x_404_ = lean_uint32_lor(v___y_2_, v___x_400_);
return v___x_404_;
}
}
}
v___jp_405_:
{
uint32_t v___x_406_; uint32_t v___x_407_; uint32_t v___x_408_; uint32_t v___x_409_; uint8_t v___x_410_; 
v___x_406_ = 23;
v___x_407_ = lean_uint32_shift_right(v___y_2_, v___x_406_);
v___x_408_ = 255;
v___x_409_ = lean_uint32_land(v___x_407_, v___x_408_);
v___x_410_ = lean_uint32_dec_eq(v___x_409_, v___x_408_);
if (v___x_410_ == 0)
{
v___y_399_ = v___x_410_;
goto v___jp_398_;
}
else
{
uint32_t v___x_411_; uint32_t v___x_412_; uint32_t v___x_413_; uint8_t v___x_414_; 
v___x_411_ = 8388607;
v___x_412_ = lean_uint32_land(v___y_2_, v___x_411_);
v___x_413_ = 0;
v___x_414_ = lean_uint32_dec_eq(v___x_412_, v___x_413_);
if (v___x_414_ == 0)
{
v___y_399_ = v___x_410_;
goto v___jp_398_;
}
else
{
goto v___jp_388_;
}
}
}
v___jp_415_:
{
if (v___y_416_ == 0)
{
goto v___jp_405_;
}
else
{
uint32_t v___x_417_; uint32_t v___x_418_; uint32_t v___x_419_; uint8_t v___x_420_; 
v___x_417_ = 4194304;
v___x_418_ = lean_uint32_land(v___y_1_, v___x_417_);
v___x_419_ = 0;
v___x_420_ = lean_uint32_dec_eq(v___x_418_, v___x_419_);
if (v___x_420_ == 0)
{
goto v___jp_405_;
}
else
{
uint32_t v___x_421_; 
v___x_421_ = lean_uint32_lor(v___y_1_, v___x_417_);
return v___x_421_;
}
}
}
v___jp_422_:
{
float v_result_425_; uint8_t v___x_426_; 
v_result_425_ = lean_float32_add(v___y_423_, v___y_424_);
v___x_426_ = lean_float32_beq(v_result_425_, v_result_425_);
if (v___x_426_ == 0)
{
uint32_t v___x_427_; uint32_t v___x_428_; uint32_t v___x_429_; uint32_t v___x_430_; uint8_t v___x_431_; 
v___x_427_ = 23;
v___x_428_ = lean_uint32_shift_right(v___y_1_, v___x_427_);
v___x_429_ = 255;
v___x_430_ = lean_uint32_land(v___x_428_, v___x_429_);
v___x_431_ = lean_uint32_dec_eq(v___x_430_, v___x_429_);
if (v___x_431_ == 0)
{
v___y_416_ = v___x_431_;
goto v___jp_415_;
}
else
{
uint32_t v___x_432_; uint32_t v___x_433_; uint32_t v___x_434_; uint8_t v___x_435_; 
v___x_432_ = 8388607;
v___x_433_ = lean_uint32_land(v___y_1_, v___x_432_);
v___x_434_ = 0;
v___x_435_ = lean_uint32_dec_eq(v___x_433_, v___x_434_);
if (v___x_435_ == 0)
{
v___y_416_ = v___x_431_;
goto v___jp_415_;
}
else
{
goto v___jp_405_;
}
}
}
else
{
uint32_t v___x_436_; 
v___x_436_ = lean_float32_to_bits(v_result_425_);
return v___x_436_;
}
}
v___jp_437_:
{
if (v___y_439_ == 0)
{
float v___x_440_; 
v___x_440_ = lean_float32_of_bits(v___y_2_);
v___y_423_ = v___y_438_;
v___y_424_ = v___x_440_;
goto v___jp_422_;
}
else
{
uint32_t v___x_441_; uint32_t v___x_442_; uint32_t v___x_443_; uint32_t v___x_444_; float v___x_445_; lean_object* v___x_446_; uint32_t v___x_447_; uint32_t v___x_448_; lean_object* v___x_449_; lean_object* v___x_450_; float v___x_451_; float v___x_452_; 
v___x_441_ = 8388607;
v___x_442_ = lean_uint32_land(v___y_2_, v___x_441_);
v___x_443_ = 8388608;
v___x_444_ = lean_uint32_lor(v___x_442_, v___x_443_);
v___x_445_ = lean_uint32_to_float32(v___x_444_);
v___x_446_ = lp_competition_R2W01b_scaleTable;
v___x_447_ = 23;
v___x_448_ = lean_uint32_shift_right(v___y_2_, v___x_447_);
v___x_449_ = lean_uint32_to_nat(v___x_448_);
v___x_450_ = lean_array_fget_borrowed(v___x_446_, v___x_449_);
lean_dec(v___x_449_);
v___x_451_ = lean_unbox_float32(v___x_450_);
v___x_452_ = lean_float32_mul(v___x_445_, v___x_451_);
v___y_423_ = v___y_438_;
v___y_424_ = v___x_452_;
goto v___jp_422_;
}
}
v___jp_453_:
{
uint32_t v___x_455_; uint32_t v_a_456_; uint32_t v___x_457_; uint32_t v___x_458_; uint32_t v___x_459_; uint8_t v___x_460_; 
v___x_455_ = 2147483647;
v_a_456_ = lean_uint32_land(v___y_2_, v___x_455_);
v___x_457_ = 201326591;
v___x_458_ = 1;
v___x_459_ = lean_uint32_sub(v_a_456_, v___x_458_);
v___x_460_ = lean_uint32_dec_le(v___x_457_, v___x_459_);
if (v___x_460_ == 0)
{
v___y_438_ = v___y_454_;
v___y_439_ = v___x_460_;
goto v___jp_437_;
}
else
{
uint32_t v___x_461_; uint8_t v___x_462_; 
v___x_461_ = 2139095040;
v___x_462_ = lean_uint32_dec_lt(v_a_456_, v___x_461_);
v___y_438_ = v___y_454_;
v___y_439_ = v___x_462_;
goto v___jp_437_;
}
}
v___jp_463_:
{
if (v___y_466_ == 0)
{
float v___x_467_; 
v___x_467_ = lean_float32_of_bits(v___y_1_);
v___y_454_ = v___x_467_;
goto v___jp_453_;
}
else
{
uint32_t v___x_468_; uint32_t v___x_469_; uint32_t v___x_470_; float v___x_471_; lean_object* v___x_472_; uint32_t v___x_473_; lean_object* v___x_474_; lean_object* v___x_475_; float v___x_476_; float v___x_477_; 
v___x_468_ = 8388607;
v___x_469_ = lean_uint32_land(v___y_1_, v___x_468_);
v___x_470_ = lean_uint32_lor(v___x_469_, v___y_464_);
v___x_471_ = lean_uint32_to_float32(v___x_470_);
v___x_472_ = lp_competition_R2W01b_scaleTable;
v___x_473_ = lean_uint32_shift_right(v___y_1_, v___y_465_);
v___x_474_ = lean_uint32_to_nat(v___x_473_);
v___x_475_ = lean_array_fget_borrowed(v___x_472_, v___x_474_);
lean_dec(v___x_474_);
v___x_476_ = lean_unbox_float32(v___x_475_);
v___x_477_ = lean_float32_mul(v___x_471_, v___x_476_);
v___y_454_ = v___x_477_;
goto v___jp_453_;
}
}
v___jp_478_:
{
uint32_t v___x_485_; uint32_t v___x_486_; uint32_t v___x_487_; uint32_t v___x_488_; uint32_t v_e_489_; uint32_t v___x_490_; uint32_t v___x_491_; uint32_t v___x_492_; uint8_t v___x_493_; 
v___x_485_ = lean_uint32_shift_right(v___y_484_, v___y_483_);
v___x_486_ = lean_uint32_land(v___x_485_, v___y_479_);
v___x_487_ = lean_uint32_add(v___y_482_, v___x_486_);
v___x_488_ = 150;
v_e_489_ = lean_uint32_sub(v___x_487_, v___x_488_);
v___x_490_ = 1;
v___x_491_ = lean_uint32_sub(v_e_489_, v___x_490_);
v___x_492_ = 253;
v___x_493_ = lean_uint32_dec_le(v___x_491_, v___x_492_);
if (v___x_493_ == 0)
{
uint32_t v___x_494_; uint32_t v_a_495_; uint32_t v___x_496_; uint32_t v___x_497_; uint8_t v___x_498_; 
v___x_494_ = 2147483647;
v_a_495_ = lean_uint32_land(v___y_1_, v___x_494_);
v___x_496_ = 201326591;
v___x_497_ = lean_uint32_sub(v_a_495_, v___x_490_);
v___x_498_ = lean_uint32_dec_le(v___x_496_, v___x_497_);
if (v___x_498_ == 0)
{
v___y_464_ = v___y_481_;
v___y_465_ = v___y_483_;
v___y_466_ = v___x_498_;
goto v___jp_463_;
}
else
{
uint32_t v___x_499_; uint8_t v___x_500_; 
v___x_499_ = 2139095040;
v___x_500_ = lean_uint32_dec_lt(v_a_495_, v___x_499_);
v___y_464_ = v___y_481_;
v___y_465_ = v___y_483_;
v___y_466_ = v___x_500_;
goto v___jp_463_;
}
}
else
{
uint32_t v___x_501_; uint32_t v___x_502_; uint32_t v___x_503_; uint32_t v___x_504_; uint32_t v___x_505_; uint8_t v___x_506_; 
v___x_501_ = 2147483648;
v___x_502_ = lean_uint32_shift_right(v___y_1_, v___y_483_);
v___x_503_ = lean_uint32_land(v___x_502_, v___y_479_);
v___x_504_ = lean_uint32_shift_right(v___y_2_, v___y_483_);
v___x_505_ = lean_uint32_land(v___x_504_, v___y_479_);
v___x_506_ = lean_uint32_dec_lt(v___x_503_, v___x_505_);
if (v___x_506_ == 0)
{
v___y_16_ = v___y_479_;
v___y_17_ = v___y_480_;
v___y_18_ = v_e_489_;
v___y_19_ = v___x_501_;
v___y_20_ = v___y_483_;
v___y_21_ = v___y_1_;
goto v___jp_15_;
}
else
{
v___y_16_ = v___y_479_;
v___y_17_ = v___y_480_;
v___y_18_ = v_e_489_;
v___y_19_ = v___x_501_;
v___y_20_ = v___y_483_;
v___y_21_ = v___y_2_;
goto v___jp_15_;
}
}
}
v___jp_507_:
{
uint32_t v___x_509_; uint8_t v___x_510_; 
v___x_509_ = 8388608;
v___x_510_ = lean_uint32_dec_le(v___x_509_, v___y_508_);
if (v___x_510_ == 0)
{
uint32_t v___x_511_; uint32_t v_a_512_; uint32_t v___x_513_; uint32_t v___x_514_; uint32_t v___x_515_; uint8_t v___x_516_; 
v___x_511_ = 2147483647;
v_a_512_ = lean_uint32_land(v___y_1_, v___x_511_);
v___x_513_ = 201326591;
v___x_514_ = 1;
v___x_515_ = lean_uint32_sub(v_a_512_, v___x_514_);
v___x_516_ = lean_uint32_dec_le(v___x_513_, v___x_515_);
if (v___x_516_ == 0)
{
v___y_351_ = v___x_509_;
v___y_352_ = v___x_516_;
goto v___jp_350_;
}
else
{
uint32_t v___x_517_; uint8_t v___x_518_; 
v___x_517_ = 2139095040;
v___x_518_ = lean_uint32_dec_lt(v_a_512_, v___x_517_);
v___y_351_ = v___x_509_;
v___y_352_ = v___x_518_;
goto v___jp_350_;
}
}
else
{
float v___x_519_; uint32_t v_mid_520_; uint32_t v___x_521_; uint32_t v___x_522_; uint32_t v___x_523_; uint32_t v___x_524_; uint32_t v___x_525_; uint32_t v___x_526_; uint32_t v___x_527_; uint32_t v___x_528_; uint8_t v___x_529_; 
v___x_519_ = lean_uint32_to_float32(v___y_508_);
v_mid_520_ = lean_float32_to_bits(v___x_519_);
v___x_521_ = 23;
v___x_522_ = lean_uint32_shift_right(v_mid_520_, v___x_521_);
v___x_523_ = 255;
v___x_524_ = lean_uint32_land(v___x_522_, v___x_523_);
v___x_525_ = lean_uint32_shift_right(v___y_1_, v___x_521_);
v___x_526_ = lean_uint32_land(v___x_525_, v___x_523_);
v___x_527_ = lean_uint32_shift_right(v___y_2_, v___x_521_);
v___x_528_ = lean_uint32_land(v___x_527_, v___x_523_);
v___x_529_ = lean_uint32_dec_lt(v___x_526_, v___x_528_);
if (v___x_529_ == 0)
{
v___y_479_ = v___x_523_;
v___y_480_ = v_mid_520_;
v___y_481_ = v___x_509_;
v___y_482_ = v___x_524_;
v___y_483_ = v___x_521_;
v___y_484_ = v___y_2_;
goto v___jp_478_;
}
else
{
v___y_479_ = v___x_523_;
v___y_480_ = v_mid_520_;
v___y_481_ = v___x_509_;
v___y_482_ = v___x_524_;
v___y_483_ = v___x_521_;
v___y_484_ = v___y_1_;
goto v___jp_478_;
}
}
}
v___jp_530_:
{
if (v___y_533_ == 0)
{
uint32_t v___x_534_; 
v___x_534_ = lean_uint32_sub(v___y_532_, v___y_531_);
v___y_508_ = v___x_534_;
goto v___jp_507_;
}
else
{
uint32_t v___x_535_; 
v___x_535_ = lean_uint32_add(v___y_532_, v___y_531_);
v___y_508_ = v___x_535_;
goto v___jp_507_;
}
}
v___jp_536_:
{
uint32_t v___x_541_; uint32_t v_right_542_; uint32_t v___x_543_; uint8_t v___x_544_; uint8_t v___x_545_; 
v___x_541_ = lean_uint32_land(v___y_540_, v___y_539_);
v_right_542_ = lean_uint32_lor(v___x_541_, v___y_538_);
v___x_543_ = 2147483648;
v___x_544_ = lean_uint32_dec_le(v___x_543_, v___y_1_);
v___x_545_ = lean_uint32_dec_le(v___x_543_, v___y_2_);
if (v___x_544_ == 0)
{
if (v___x_545_ == 0)
{
uint32_t v___x_546_; 
v___x_546_ = lean_uint32_add(v___y_537_, v_right_542_);
v___y_508_ = v___x_546_;
goto v___jp_507_;
}
else
{
v___y_531_ = v_right_542_;
v___y_532_ = v___y_537_;
v___y_533_ = v___x_544_;
goto v___jp_530_;
}
}
else
{
v___y_531_ = v_right_542_;
v___y_532_ = v___y_537_;
v___y_533_ = v___x_545_;
goto v___jp_530_;
}
}
v___jp_547_:
{
uint32_t v___x_555_; uint32_t v___x_556_; uint32_t v___x_557_; uint32_t v_left_558_; uint32_t v___x_559_; uint32_t v___x_560_; uint32_t v___x_561_; uint32_t v___x_562_; uint8_t v___x_563_; 
v___x_555_ = lean_uint32_shift_right(v___y_554_, v___y_551_);
v___x_556_ = lean_uint32_land(v___x_555_, v___y_552_);
v___x_557_ = lean_uint32_sub(v___y_549_, v___x_556_);
v_left_558_ = lean_uint32_shift_left(v___y_548_, v___x_557_);
v___x_559_ = lean_uint32_shift_right(v___y_1_, v___y_551_);
v___x_560_ = lean_uint32_land(v___x_559_, v___y_552_);
v___x_561_ = lean_uint32_shift_right(v___y_2_, v___y_551_);
v___x_562_ = lean_uint32_land(v___x_561_, v___y_552_);
v___x_563_ = lean_uint32_dec_lt(v___x_560_, v___x_562_);
if (v___x_563_ == 0)
{
v___y_537_ = v_left_558_;
v___y_538_ = v___y_550_;
v___y_539_ = v___y_553_;
v___y_540_ = v___y_2_;
goto v___jp_536_;
}
else
{
v___y_537_ = v_left_558_;
v___y_538_ = v___y_550_;
v___y_539_ = v___y_553_;
v___y_540_ = v___y_1_;
goto v___jp_536_;
}
}
v___jp_564_:
{
uint32_t v___x_569_; uint32_t v___x_570_; uint32_t v___x_571_; uint32_t v___x_572_; uint32_t v___x_573_; uint32_t v___x_574_; uint32_t v___x_575_; uint32_t v___x_576_; uint8_t v___x_577_; 
v___x_569_ = 23;
v___x_570_ = lean_uint32_shift_right(v___y_568_, v___x_569_);
v___x_571_ = 255;
v___x_572_ = lean_uint32_land(v___x_570_, v___x_571_);
v___x_573_ = lean_uint32_shift_right(v___y_1_, v___x_569_);
v___x_574_ = lean_uint32_land(v___x_573_, v___x_571_);
v___x_575_ = lean_uint32_shift_right(v___y_2_, v___x_569_);
v___x_576_ = lean_uint32_land(v___x_575_, v___x_571_);
v___x_577_ = lean_uint32_dec_lt(v___x_574_, v___x_576_);
if (v___x_577_ == 0)
{
v___y_548_ = v___y_565_;
v___y_549_ = v___x_572_;
v___y_550_ = v___y_566_;
v___y_551_ = v___x_569_;
v___y_552_ = v___x_571_;
v___y_553_ = v___y_567_;
v___y_554_ = v___y_2_;
goto v___jp_547_;
}
else
{
v___y_548_ = v___y_565_;
v___y_549_ = v___x_572_;
v___y_550_ = v___y_566_;
v___y_551_ = v___x_569_;
v___y_552_ = v___x_571_;
v___y_553_ = v___y_567_;
v___y_554_ = v___y_1_;
goto v___jp_547_;
}
}
v___jp_578_:
{
uint32_t v___x_580_; uint32_t v___x_581_; uint32_t v___x_582_; uint32_t v___x_583_; uint32_t v___x_584_; uint32_t v___x_585_; uint32_t v___x_586_; uint32_t v___x_587_; uint32_t v___x_588_; uint32_t v___x_589_; uint8_t v___x_590_; 
v___x_580_ = 8388607;
v___x_581_ = lean_uint32_land(v___y_579_, v___x_580_);
v___x_582_ = 8388608;
v___x_583_ = lean_uint32_lor(v___x_581_, v___x_582_);
v___x_584_ = 23;
v___x_585_ = lean_uint32_shift_right(v___y_1_, v___x_584_);
v___x_586_ = 255;
v___x_587_ = lean_uint32_land(v___x_585_, v___x_586_);
v___x_588_ = lean_uint32_shift_right(v___y_2_, v___x_584_);
v___x_589_ = lean_uint32_land(v___x_588_, v___x_586_);
v___x_590_ = lean_uint32_dec_lt(v___x_587_, v___x_589_);
if (v___x_590_ == 0)
{
v___y_565_ = v___x_583_;
v___y_566_ = v___x_582_;
v___y_567_ = v___x_580_;
v___y_568_ = v___y_1_;
goto v___jp_564_;
}
else
{
v___y_565_ = v___x_583_;
v___y_566_ = v___x_582_;
v___y_567_ = v___x_580_;
v___y_568_ = v___y_2_;
goto v___jp_564_;
}
}
v___jp_591_:
{
uint32_t v___x_592_; uint32_t v___x_593_; uint32_t v___x_594_; uint32_t v___x_595_; uint32_t v___x_596_; uint32_t v___x_597_; uint8_t v___x_598_; 
v___x_592_ = 23;
v___x_593_ = lean_uint32_shift_right(v___y_1_, v___x_592_);
v___x_594_ = 255;
v___x_595_ = lean_uint32_land(v___x_593_, v___x_594_);
v___x_596_ = lean_uint32_shift_right(v___y_2_, v___x_592_);
v___x_597_ = lean_uint32_land(v___x_596_, v___x_594_);
v___x_598_ = lean_uint32_dec_lt(v___x_595_, v___x_597_);
if (v___x_598_ == 0)
{
v___y_579_ = v___y_1_;
goto v___jp_578_;
}
else
{
v___y_579_ = v___y_2_;
goto v___jp_578_;
}
}
v___jp_599_:
{
if (v___y_600_ == 0)
{
uint32_t v___x_601_; uint32_t v_a_602_; uint32_t v___x_603_; uint32_t v___x_604_; uint32_t v___x_605_; uint8_t v___x_606_; 
v___x_601_ = 2147483647;
v_a_602_ = lean_uint32_land(v___y_1_, v___x_601_);
v___x_603_ = 201326591;
v___x_604_ = 1;
v___x_605_ = lean_uint32_sub(v_a_602_, v___x_604_);
v___x_606_ = lean_uint32_dec_le(v___x_603_, v___x_605_);
if (v___x_606_ == 0)
{
v___y_238_ = v___x_606_;
goto v___jp_237_;
}
else
{
uint32_t v___x_607_; uint8_t v___x_608_; 
v___x_607_ = 2139095040;
v___x_608_ = lean_uint32_dec_lt(v_a_602_, v___x_607_);
v___y_238_ = v___x_608_;
goto v___jp_237_;
}
}
else
{
goto v___jp_591_;
}
}
v___jp_609_:
{
uint32_t v___x_615_; uint32_t v___x_616_; uint32_t v___x_617_; uint8_t v___x_618_; 
v___x_615_ = lean_uint32_shift_right(v___y_614_, v___y_612_);
v___x_616_ = lean_uint32_land(v___x_615_, v___y_613_);
v___x_617_ = lean_uint32_sub(v___y_611_, v___x_616_);
v___x_618_ = lean_uint32_dec_le(v___y_610_, v___x_617_);
v___y_600_ = v___x_618_;
goto v___jp_599_;
}
v___jp_619_:
{
uint32_t v___x_622_; uint32_t v___x_623_; uint32_t v___x_624_; uint32_t v___x_625_; uint32_t v___x_626_; uint32_t v___x_627_; uint32_t v___x_628_; uint32_t v___x_629_; uint8_t v___x_630_; 
v___x_622_ = 23;
v___x_623_ = lean_uint32_shift_right(v___y_621_, v___x_622_);
v___x_624_ = 255;
v___x_625_ = lean_uint32_land(v___x_623_, v___x_624_);
v___x_626_ = lean_uint32_shift_right(v___y_1_, v___x_622_);
v___x_627_ = lean_uint32_land(v___x_626_, v___x_624_);
v___x_628_ = lean_uint32_shift_right(v___y_2_, v___x_622_);
v___x_629_ = lean_uint32_land(v___x_628_, v___x_624_);
v___x_630_ = lean_uint32_dec_lt(v___x_627_, v___x_629_);
if (v___x_630_ == 0)
{
v___y_610_ = v___y_620_;
v___y_611_ = v___x_625_;
v___y_612_ = v___x_622_;
v___y_613_ = v___x_624_;
v___y_614_ = v___y_2_;
goto v___jp_609_;
}
else
{
v___y_610_ = v___y_620_;
v___y_611_ = v___x_625_;
v___y_612_ = v___x_622_;
v___y_613_ = v___x_624_;
v___y_614_ = v___y_1_;
goto v___jp_609_;
}
}
v___jp_631_:
{
if (v___y_632_ == 0)
{
uint32_t v___x_633_; uint32_t v___x_634_; uint32_t v___x_635_; uint32_t v___x_636_; uint32_t v___x_637_; uint32_t v___x_638_; uint32_t v___x_639_; uint8_t v___x_640_; 
v___x_633_ = 1;
v___x_634_ = 23;
v___x_635_ = lean_uint32_shift_right(v___y_1_, v___x_634_);
v___x_636_ = 255;
v___x_637_ = lean_uint32_land(v___x_635_, v___x_636_);
v___x_638_ = lean_uint32_shift_right(v___y_2_, v___x_634_);
v___x_639_ = lean_uint32_land(v___x_638_, v___x_636_);
v___x_640_ = lean_uint32_dec_lt(v___x_637_, v___x_639_);
if (v___x_640_ == 0)
{
v___y_620_ = v___x_633_;
v___y_621_ = v___y_1_;
goto v___jp_619_;
}
else
{
v___y_620_ = v___x_633_;
v___y_621_ = v___y_2_;
goto v___jp_619_;
}
}
else
{
goto v___jp_591_;
}
}
v___jp_641_:
{
uint32_t v___x_646_; uint32_t v___x_647_; uint32_t v___x_648_; uint32_t v___x_649_; uint8_t v___x_650_; 
v___x_646_ = lean_uint32_shift_right(v___y_645_, v___y_643_);
v___x_647_ = lean_uint32_land(v___x_646_, v___y_644_);
v___x_648_ = lean_uint32_sub(v___y_642_, v___x_647_);
v___x_649_ = 7;
v___x_650_ = lean_uint32_dec_le(v___x_648_, v___x_649_);
if (v___x_650_ == 0)
{
v___y_600_ = v___x_650_;
goto v___jp_599_;
}
else
{
uint32_t v___x_651_; uint8_t v___x_652_; uint8_t v___x_653_; 
v___x_651_ = 2147483648;
v___x_652_ = lean_uint32_dec_le(v___x_651_, v___y_1_);
v___x_653_ = lean_uint32_dec_le(v___x_651_, v___y_2_);
if (v___x_652_ == 0)
{
if (v___x_653_ == 0)
{
v___y_600_ = v___x_650_;
goto v___jp_599_;
}
else
{
v___y_632_ = v___x_652_;
goto v___jp_631_;
}
}
else
{
v___y_632_ = v___x_653_;
goto v___jp_631_;
}
}
}
v___jp_654_:
{
uint32_t v___x_656_; uint32_t v___x_657_; uint32_t v___x_658_; uint32_t v___x_659_; uint32_t v___x_660_; uint32_t v___x_661_; uint32_t v___x_662_; uint32_t v___x_663_; uint8_t v___x_664_; 
v___x_656_ = 23;
v___x_657_ = lean_uint32_shift_right(v___y_655_, v___x_656_);
v___x_658_ = 255;
v___x_659_ = lean_uint32_land(v___x_657_, v___x_658_);
v___x_660_ = lean_uint32_shift_right(v___y_1_, v___x_656_);
v___x_661_ = lean_uint32_land(v___x_660_, v___x_658_);
v___x_662_ = lean_uint32_shift_right(v___y_2_, v___x_656_);
v___x_663_ = lean_uint32_land(v___x_662_, v___x_658_);
v___x_664_ = lean_uint32_dec_lt(v___x_661_, v___x_663_);
if (v___x_664_ == 0)
{
v___y_642_ = v___x_659_;
v___y_643_ = v___x_656_;
v___y_644_ = v___x_658_;
v___y_645_ = v___y_2_;
goto v___jp_641_;
}
else
{
v___y_642_ = v___x_659_;
v___y_643_ = v___x_656_;
v___y_644_ = v___x_658_;
v___y_645_ = v___y_1_;
goto v___jp_641_;
}
}
v___jp_665_:
{
if (v___y_666_ == 0)
{
uint32_t v___x_667_; uint32_t v_a_668_; uint32_t v___x_669_; uint32_t v___x_670_; uint32_t v___x_671_; uint8_t v___x_672_; 
v___x_667_ = 2147483647;
v_a_668_ = lean_uint32_land(v___y_1_, v___x_667_);
v___x_669_ = 201326591;
v___x_670_ = 1;
v___x_671_ = lean_uint32_sub(v_a_668_, v___x_670_);
v___x_672_ = lean_uint32_dec_le(v___x_669_, v___x_671_);
if (v___x_672_ == 0)
{
v___y_125_ = v___x_672_;
goto v___jp_124_;
}
else
{
uint32_t v___x_673_; uint8_t v___x_674_; 
v___x_673_ = 2139095040;
v___x_674_ = lean_uint32_dec_lt(v_a_668_, v___x_673_);
v___y_125_ = v___x_674_;
goto v___jp_124_;
}
}
else
{
uint32_t v___x_675_; uint32_t v___x_676_; uint32_t v___x_677_; uint32_t v___x_678_; uint32_t v___x_679_; uint32_t v___x_680_; uint8_t v___x_681_; 
v___x_675_ = 23;
v___x_676_ = lean_uint32_shift_right(v___y_1_, v___x_675_);
v___x_677_ = 255;
v___x_678_ = lean_uint32_land(v___x_676_, v___x_677_);
v___x_679_ = lean_uint32_shift_right(v___y_2_, v___x_675_);
v___x_680_ = lean_uint32_land(v___x_679_, v___x_677_);
v___x_681_ = lean_uint32_dec_lt(v___x_678_, v___x_680_);
if (v___x_681_ == 0)
{
v___y_655_ = v___y_1_;
goto v___jp_654_;
}
else
{
v___y_655_ = v___y_2_;
goto v___jp_654_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_694_, lean_object* v___y_695_){
_start:
{
uint32_t v___y_9087__boxed_696_; uint32_t v___y_9088__boxed_697_; uint32_t v_res_698_; lean_object* v_r_699_; 
v___y_9087__boxed_696_ = lean_unbox_uint32(v___y_694_);
lean_dec(v___y_694_);
v___y_9088__boxed_697_ = lean_unbox_uint32(v___y_695_);
lean_dec(v___y_695_);
v_res_698_ = lp_competition_main___lam__0(v___y_9087__boxed_696_, v___y_9088__boxed_697_);
v_r_699_ = lean_box_uint32(v_res_698_);
return v_r_699_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_700_, uint32_t v___y_701_){
_start:
{
uint32_t v___y_703_; uint32_t v___y_707_; uint32_t v___y_711_; uint32_t v___y_712_; uint32_t v___y_713_; uint32_t v___y_717_; uint64_t v___y_718_; uint8_t v___y_719_; uint64_t v___y_720_; uint32_t v___y_732_; uint32_t v___y_733_; uint32_t v___y_734_; uint32_t v___y_738_; uint64_t v___y_739_; uint8_t v___y_740_; uint64_t v___y_741_; uint8_t v___y_753_; uint8_t v___y_769_; uint8_t v___y_783_; uint8_t v___y_800_; float v___y_807_; float v___y_808_; float v___y_822_; uint8_t v___y_823_; float v___y_838_; uint32_t v___x_847_; uint32_t v___x_848_; uint8_t v___y_850_; uint32_t v___x_862_; uint32_t v___y_864_; uint32_t v___y_865_; uint32_t v___y_866_; uint32_t v___y_867_; uint32_t v___y_874_; uint32_t v___y_875_; uint8_t v___y_876_; uint32_t v___y_877_; uint32_t v___y_881_; uint64_t v___y_882_; uint64_t v___y_883_; uint8_t v___y_884_; uint64_t v___y_885_; uint32_t v___y_895_; uint64_t v___y_896_; uint8_t v___y_897_; uint8_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_900_; uint32_t v___y_907_; uint64_t v___y_908_; uint64_t v___y_909_; uint8_t v___y_910_; uint64_t v___y_911_; uint64_t v___y_917_; uint32_t v___y_918_; uint64_t v___y_919_; uint64_t v___y_920_; uint8_t v___y_921_; uint64_t v___y_922_; uint64_t v___y_977_; uint32_t v___y_978_; uint64_t v___y_979_; uint64_t v___y_980_; uint8_t v___y_981_; uint64_t v___y_982_; uint64_t v___y_983_; uint64_t v___y_989_; uint32_t v___y_990_; uint64_t v___y_991_; uint64_t v___y_992_; uint64_t v___y_993_; uint64_t v___y_994_; uint64_t v___y_995_; uint8_t v___y_996_; uint64_t v___y_997_; uint64_t v___y_1002_; uint32_t v___y_1003_; uint64_t v___y_1004_; uint64_t v___y_1005_; uint64_t v___y_1006_; uint8_t v___y_1007_; uint64_t v___y_1008_; uint64_t v___y_1013_; uint32_t v___y_1014_; uint64_t v___y_1015_; uint64_t v___y_1016_; uint64_t v___y_1017_; uint64_t v___y_1018_; uint8_t v___y_1019_; uint64_t v___y_1020_; uint64_t v___y_1021_; uint64_t v___y_1026_; uint32_t v___y_1027_; uint64_t v___y_1028_; uint64_t v___y_1029_; uint64_t v___y_1030_; uint8_t v___y_1031_; uint64_t v___y_1032_; uint64_t v___y_1037_; uint64_t v___y_1038_; uint32_t v___y_1039_; uint64_t v___y_1040_; uint64_t v___y_1041_; uint64_t v___y_1042_; uint64_t v___y_1043_; uint8_t v___y_1044_; uint64_t v___y_1045_; uint64_t v___y_1050_; uint32_t v___y_1051_; uint64_t v___y_1052_; uint64_t v___y_1053_; uint64_t v___y_1054_; uint8_t v___y_1055_; uint64_t v___y_1056_; uint64_t v___y_1061_; uint64_t v___y_1062_; uint32_t v___y_1063_; uint64_t v___y_1064_; uint64_t v___y_1065_; uint64_t v___y_1066_; uint64_t v___y_1067_; uint8_t v___y_1068_; uint64_t v___y_1069_; uint64_t v___y_1074_; uint64_t v___y_1075_; uint32_t v___y_1076_; uint64_t v___y_1077_; uint64_t v___y_1078_; uint8_t v___y_1079_; uint64_t v___y_1080_; uint64_t v___y_1085_; uint32_t v___y_1086_; uint64_t v___y_1087_; uint64_t v___y_1088_; uint64_t v___y_1089_; uint8_t v___y_1090_; uint64_t v___y_1091_; uint64_t v___y_1095_; uint32_t v___y_1096_; uint64_t v___y_1097_; uint8_t v___y_1098_; uint32_t v___y_1107_; uint64_t v___y_1108_; uint64_t v___y_1109_; uint64_t v___y_1110_; uint8_t v___y_1111_; uint64_t v___y_1112_; uint32_t v_ex_1145_; uint32_t v___x_1146_; uint32_t v_ey_1147_; uint32_t v___y_1149_; uint64_t v___y_1150_; uint64_t v___y_1151_; uint8_t v___y_1152_; uint64_t v___y_1153_; uint32_t v___y_1160_; uint64_t v___y_1161_; uint8_t v___y_1162_; uint64_t v___y_1163_; uint32_t v___y_1170_; uint32_t v___y_1171_; uint8_t v___y_1172_; uint64_t v___y_1173_; uint8_t v___y_1181_; uint32_t v___x_1191_; uint32_t v___x_1192_; uint8_t v___x_1193_; uint8_t v___y_1195_; uint8_t v___y_1196_; uint8_t v___y_1198_; uint8_t v___y_1199_; uint8_t v___y_1200_; uint8_t v___y_1202_; uint8_t v___y_1203_; uint8_t v___y_1209_; 
v___x_847_ = 23;
v___x_848_ = lean_uint32_shift_right(v___y_700_, v___x_847_);
v___x_862_ = 255;
v_ex_1145_ = lean_uint32_land(v___x_848_, v___x_862_);
v___x_1146_ = lean_uint32_shift_right(v___y_701_, v___x_847_);
v_ey_1147_ = lean_uint32_land(v___x_1146_, v___x_862_);
v___x_1191_ = lean_uint32_add(v_ex_1145_, v_ey_1147_);
v___x_1192_ = 128;
v___x_1193_ = lean_uint32_dec_lt(v___x_1191_, v___x_1192_);
if (v___x_1193_ == 0)
{
uint32_t v___x_1218_; uint32_t v_a_1219_; uint32_t v___x_1220_; uint32_t v___x_1221_; uint32_t v___x_1222_; uint8_t v___x_1223_; 
v___x_1218_ = 2147483647;
v_a_1219_ = lean_uint32_land(v___y_700_, v___x_1218_);
v___x_1220_ = 201326591;
v___x_1221_ = 1;
v___x_1222_ = lean_uint32_sub(v_a_1219_, v___x_1221_);
v___x_1223_ = lean_uint32_dec_le(v___x_1220_, v___x_1222_);
if (v___x_1223_ == 0)
{
v___y_850_ = v___x_1223_;
goto v___jp_849_;
}
else
{
uint32_t v___x_1224_; uint8_t v___x_1225_; 
v___x_1224_ = 2139095040;
v___x_1225_ = lean_uint32_dec_lt(v_a_1219_, v___x_1224_);
v___y_850_ = v___x_1225_;
goto v___jp_849_;
}
}
else
{
uint32_t v___x_1226_; uint32_t v___x_1227_; uint32_t v___x_1228_; uint8_t v___x_1229_; 
v___x_1226_ = 4278190080;
v___x_1227_ = 1;
v___x_1228_ = lean_uint32_shift_left(v___y_700_, v___x_1227_);
v___x_1229_ = lean_uint32_dec_le(v___x_1226_, v___x_1228_);
if (v___x_1229_ == 0)
{
uint32_t v___x_1230_; uint8_t v___x_1231_; 
v___x_1230_ = lean_uint32_shift_left(v___y_701_, v___x_1227_);
v___x_1231_ = lean_uint32_dec_le(v___x_1226_, v___x_1230_);
v___y_1209_ = v___x_1231_;
goto v___jp_1208_;
}
else
{
v___y_1209_ = v___x_1229_;
goto v___jp_1208_;
}
}
v___jp_702_:
{
uint32_t v___x_704_; uint32_t v___x_705_; 
v___x_704_ = 8388608;
v___x_705_ = lean_uint32_lor(v___y_703_, v___x_704_);
return v___x_705_;
}
v___jp_706_:
{
uint32_t v___x_708_; uint32_t v___x_709_; 
v___x_708_ = 8388608;
v___x_709_ = lean_uint32_lor(v___y_707_, v___x_708_);
return v___x_709_;
}
v___jp_710_:
{
uint32_t v___x_714_; uint32_t v___x_715_; 
v___x_714_ = lean_uint32_land(v___y_712_, v___y_711_);
v___x_715_ = lean_uint32_lor(v___y_713_, v___x_714_);
return v___x_715_;
}
v___jp_716_:
{
uint8_t v___x_721_; 
v___x_721_ = lean_uint64_dec_eq(v___y_720_, v___y_718_);
if (v___x_721_ == 0)
{
uint64_t v___x_722_; uint8_t v___x_723_; 
v___x_722_ = 8388608ULL;
v___x_723_ = lean_uint64_dec_eq(v___y_720_, v___x_722_);
if (v___x_723_ == 0)
{
uint32_t v___x_724_; 
v___x_724_ = lean_uint64_to_uint32(v___y_720_);
if (v___y_719_ == 0)
{
uint32_t v___x_725_; 
v___x_725_ = 0;
v___y_711_ = v___y_717_;
v___y_712_ = v___x_724_;
v___y_713_ = v___x_725_;
goto v___jp_710_;
}
else
{
uint32_t v___x_726_; 
v___x_726_ = 2147483648;
v___y_711_ = v___y_717_;
v___y_712_ = v___x_724_;
v___y_713_ = v___x_726_;
goto v___jp_710_;
}
}
else
{
if (v___y_719_ == 0)
{
uint32_t v___x_727_; 
v___x_727_ = 0;
v___y_707_ = v___x_727_;
goto v___jp_706_;
}
else
{
uint32_t v___x_728_; 
v___x_728_ = 2147483648;
v___y_707_ = v___x_728_;
goto v___jp_706_;
}
}
}
else
{
if (v___y_719_ == 0)
{
uint32_t v___x_729_; 
v___x_729_ = 0;
return v___x_729_;
}
else
{
uint32_t v___x_730_; 
v___x_730_ = 2147483648;
return v___x_730_;
}
}
}
v___jp_731_:
{
uint32_t v___x_735_; uint32_t v___x_736_; 
v___x_735_ = lean_uint32_land(v___y_733_, v___y_732_);
v___x_736_ = lean_uint32_lor(v___y_734_, v___x_735_);
return v___x_736_;
}
v___jp_737_:
{
uint8_t v___x_742_; 
v___x_742_ = lean_uint64_dec_eq(v___y_741_, v___y_739_);
if (v___x_742_ == 0)
{
uint64_t v___x_743_; uint8_t v___x_744_; 
v___x_743_ = 8388608ULL;
v___x_744_ = lean_uint64_dec_eq(v___y_741_, v___x_743_);
if (v___x_744_ == 0)
{
uint32_t v___x_745_; 
v___x_745_ = lean_uint64_to_uint32(v___y_741_);
if (v___y_740_ == 0)
{
uint32_t v___x_746_; 
v___x_746_ = 0;
v___y_732_ = v___y_738_;
v___y_733_ = v___x_745_;
v___y_734_ = v___x_746_;
goto v___jp_731_;
}
else
{
uint32_t v___x_747_; 
v___x_747_ = 2147483648;
v___y_732_ = v___y_738_;
v___y_733_ = v___x_745_;
v___y_734_ = v___x_747_;
goto v___jp_731_;
}
}
else
{
if (v___y_740_ == 0)
{
uint32_t v___x_748_; 
v___x_748_ = 0;
v___y_703_ = v___x_748_;
goto v___jp_702_;
}
else
{
uint32_t v___x_749_; 
v___x_749_ = 2147483648;
v___y_703_ = v___x_749_;
goto v___jp_702_;
}
}
}
else
{
if (v___y_740_ == 0)
{
uint32_t v___x_750_; 
v___x_750_ = 0;
return v___x_750_;
}
else
{
uint32_t v___x_751_; 
v___x_751_ = 2147483648;
return v___x_751_;
}
}
}
v___jp_752_:
{
if (v___y_753_ == 0)
{
uint32_t v___x_754_; 
v___x_754_ = lp_competition_Submission_FastMul_mul(v___y_700_, v___y_701_);
return v___x_754_;
}
else
{
uint32_t v___x_755_; uint32_t v___x_756_; 
v___x_755_ = 4194304;
v___x_756_ = lean_uint32_lor(v___y_701_, v___x_755_);
return v___x_756_;
}
}
v___jp_757_:
{
uint32_t v___x_758_; uint32_t v___x_759_; uint32_t v___x_760_; uint32_t v___x_761_; uint8_t v___x_762_; 
v___x_758_ = 23;
v___x_759_ = lean_uint32_shift_right(v___y_701_, v___x_758_);
v___x_760_ = 255;
v___x_761_ = lean_uint32_land(v___x_759_, v___x_760_);
v___x_762_ = lean_uint32_dec_eq(v___x_761_, v___x_760_);
if (v___x_762_ == 0)
{
v___y_753_ = v___x_762_;
goto v___jp_752_;
}
else
{
uint32_t v___x_763_; uint32_t v___x_764_; uint32_t v___x_765_; uint8_t v___x_766_; 
v___x_763_ = 8388607;
v___x_764_ = lean_uint32_land(v___y_701_, v___x_763_);
v___x_765_ = 0;
v___x_766_ = lean_uint32_dec_eq(v___x_764_, v___x_765_);
if (v___x_766_ == 0)
{
v___y_753_ = v___x_762_;
goto v___jp_752_;
}
else
{
uint32_t v___x_767_; 
v___x_767_ = lp_competition_Submission_FastMul_mul(v___y_700_, v___y_701_);
return v___x_767_;
}
}
}
v___jp_768_:
{
if (v___y_769_ == 0)
{
goto v___jp_757_;
}
else
{
uint32_t v___x_770_; uint32_t v___x_771_; 
v___x_770_ = 4194304;
v___x_771_ = lean_uint32_lor(v___y_700_, v___x_770_);
return v___x_771_;
}
}
v___jp_772_:
{
uint32_t v___x_773_; uint32_t v___x_774_; uint32_t v___x_775_; uint32_t v___x_776_; uint8_t v___x_777_; 
v___x_773_ = 23;
v___x_774_ = lean_uint32_shift_right(v___y_700_, v___x_773_);
v___x_775_ = 255;
v___x_776_ = lean_uint32_land(v___x_774_, v___x_775_);
v___x_777_ = lean_uint32_dec_eq(v___x_776_, v___x_775_);
if (v___x_777_ == 0)
{
v___y_769_ = v___x_777_;
goto v___jp_768_;
}
else
{
uint32_t v___x_778_; uint32_t v___x_779_; uint32_t v___x_780_; uint8_t v___x_781_; 
v___x_778_ = 8388607;
v___x_779_ = lean_uint32_land(v___y_700_, v___x_778_);
v___x_780_ = 0;
v___x_781_ = lean_uint32_dec_eq(v___x_779_, v___x_780_);
if (v___x_781_ == 0)
{
v___y_769_ = v___x_777_;
goto v___jp_768_;
}
else
{
goto v___jp_757_;
}
}
}
v___jp_782_:
{
if (v___y_783_ == 0)
{
goto v___jp_772_;
}
else
{
uint32_t v___x_784_; uint32_t v___x_785_; uint32_t v___x_786_; uint8_t v___x_787_; 
v___x_784_ = 4194304;
v___x_785_ = lean_uint32_land(v___y_701_, v___x_784_);
v___x_786_ = 0;
v___x_787_ = lean_uint32_dec_eq(v___x_785_, v___x_786_);
if (v___x_787_ == 0)
{
goto v___jp_772_;
}
else
{
uint32_t v___x_788_; 
v___x_788_ = lean_uint32_lor(v___y_701_, v___x_784_);
return v___x_788_;
}
}
}
v___jp_789_:
{
uint32_t v___x_790_; uint32_t v___x_791_; uint32_t v___x_792_; uint32_t v___x_793_; uint8_t v___x_794_; 
v___x_790_ = 23;
v___x_791_ = lean_uint32_shift_right(v___y_701_, v___x_790_);
v___x_792_ = 255;
v___x_793_ = lean_uint32_land(v___x_791_, v___x_792_);
v___x_794_ = lean_uint32_dec_eq(v___x_793_, v___x_792_);
if (v___x_794_ == 0)
{
v___y_783_ = v___x_794_;
goto v___jp_782_;
}
else
{
uint32_t v___x_795_; uint32_t v___x_796_; uint32_t v___x_797_; uint8_t v___x_798_; 
v___x_795_ = 8388607;
v___x_796_ = lean_uint32_land(v___y_701_, v___x_795_);
v___x_797_ = 0;
v___x_798_ = lean_uint32_dec_eq(v___x_796_, v___x_797_);
if (v___x_798_ == 0)
{
v___y_783_ = v___x_794_;
goto v___jp_782_;
}
else
{
goto v___jp_772_;
}
}
}
v___jp_799_:
{
if (v___y_800_ == 0)
{
goto v___jp_789_;
}
else
{
uint32_t v___x_801_; uint32_t v___x_802_; uint32_t v___x_803_; uint8_t v___x_804_; 
v___x_801_ = 4194304;
v___x_802_ = lean_uint32_land(v___y_700_, v___x_801_);
v___x_803_ = 0;
v___x_804_ = lean_uint32_dec_eq(v___x_802_, v___x_803_);
if (v___x_804_ == 0)
{
goto v___jp_789_;
}
else
{
uint32_t v___x_805_; 
v___x_805_ = lean_uint32_lor(v___y_700_, v___x_801_);
return v___x_805_;
}
}
}
v___jp_806_:
{
float v_result_809_; uint8_t v___x_810_; 
v_result_809_ = lean_float32_mul(v___y_807_, v___y_808_);
v___x_810_ = lean_float32_beq(v_result_809_, v_result_809_);
if (v___x_810_ == 0)
{
uint32_t v___x_811_; uint32_t v___x_812_; uint32_t v___x_813_; uint32_t v___x_814_; uint8_t v___x_815_; 
v___x_811_ = 23;
v___x_812_ = lean_uint32_shift_right(v___y_700_, v___x_811_);
v___x_813_ = 255;
v___x_814_ = lean_uint32_land(v___x_812_, v___x_813_);
v___x_815_ = lean_uint32_dec_eq(v___x_814_, v___x_813_);
if (v___x_815_ == 0)
{
v___y_800_ = v___x_815_;
goto v___jp_799_;
}
else
{
uint32_t v___x_816_; uint32_t v___x_817_; uint32_t v___x_818_; uint8_t v___x_819_; 
v___x_816_ = 8388607;
v___x_817_ = lean_uint32_land(v___y_700_, v___x_816_);
v___x_818_ = 0;
v___x_819_ = lean_uint32_dec_eq(v___x_817_, v___x_818_);
if (v___x_819_ == 0)
{
v___y_800_ = v___x_815_;
goto v___jp_799_;
}
else
{
goto v___jp_789_;
}
}
}
else
{
uint32_t v___x_820_; 
v___x_820_ = lean_float32_to_bits(v_result_809_);
return v___x_820_;
}
}
v___jp_821_:
{
if (v___y_823_ == 0)
{
float v___x_824_; 
v___x_824_ = lean_float32_of_bits(v___y_701_);
v___y_807_ = v___y_822_;
v___y_808_ = v___x_824_;
goto v___jp_806_;
}
else
{
uint32_t v___x_825_; uint32_t v___x_826_; uint32_t v___x_827_; uint32_t v___x_828_; float v___x_829_; lean_object* v___x_830_; uint32_t v___x_831_; uint32_t v___x_832_; lean_object* v___x_833_; lean_object* v___x_834_; float v___x_835_; float v___x_836_; 
v___x_825_ = 8388607;
v___x_826_ = lean_uint32_land(v___y_701_, v___x_825_);
v___x_827_ = 8388608;
v___x_828_ = lean_uint32_lor(v___x_826_, v___x_827_);
v___x_829_ = lean_uint32_to_float32(v___x_828_);
v___x_830_ = lp_competition_R2W01b_scaleTable;
v___x_831_ = 23;
v___x_832_ = lean_uint32_shift_right(v___y_701_, v___x_831_);
v___x_833_ = lean_uint32_to_nat(v___x_832_);
v___x_834_ = lean_array_fget_borrowed(v___x_830_, v___x_833_);
lean_dec(v___x_833_);
v___x_835_ = lean_unbox_float32(v___x_834_);
v___x_836_ = lean_float32_mul(v___x_829_, v___x_835_);
v___y_807_ = v___y_822_;
v___y_808_ = v___x_836_;
goto v___jp_806_;
}
}
v___jp_837_:
{
uint32_t v___x_839_; uint32_t v_a_840_; uint32_t v___x_841_; uint32_t v___x_842_; uint32_t v___x_843_; uint8_t v___x_844_; 
v___x_839_ = 2147483647;
v_a_840_ = lean_uint32_land(v___y_701_, v___x_839_);
v___x_841_ = 201326591;
v___x_842_ = 1;
v___x_843_ = lean_uint32_sub(v_a_840_, v___x_842_);
v___x_844_ = lean_uint32_dec_le(v___x_841_, v___x_843_);
if (v___x_844_ == 0)
{
v___y_822_ = v___y_838_;
v___y_823_ = v___x_844_;
goto v___jp_821_;
}
else
{
uint32_t v___x_845_; uint8_t v___x_846_; 
v___x_845_ = 2139095040;
v___x_846_ = lean_uint32_dec_lt(v_a_840_, v___x_845_);
v___y_822_ = v___y_838_;
v___y_823_ = v___x_846_;
goto v___jp_821_;
}
}
v___jp_849_:
{
if (v___y_850_ == 0)
{
float v___x_851_; 
v___x_851_ = lean_float32_of_bits(v___y_700_);
v___y_838_ = v___x_851_;
goto v___jp_837_;
}
else
{
uint32_t v___x_852_; uint32_t v___x_853_; uint32_t v___x_854_; uint32_t v___x_855_; float v___x_856_; lean_object* v___x_857_; lean_object* v___x_858_; lean_object* v___x_859_; float v___x_860_; float v___x_861_; 
v___x_852_ = 8388607;
v___x_853_ = lean_uint32_land(v___y_700_, v___x_852_);
v___x_854_ = 8388608;
v___x_855_ = lean_uint32_lor(v___x_853_, v___x_854_);
v___x_856_ = lean_uint32_to_float32(v___x_855_);
v___x_857_ = lp_competition_R2W01b_scaleTable;
v___x_858_ = lean_uint32_to_nat(v___x_848_);
v___x_859_ = lean_array_fget_borrowed(v___x_857_, v___x_858_);
lean_dec(v___x_858_);
v___x_860_ = lean_unbox_float32(v___x_859_);
v___x_861_ = lean_float32_mul(v___x_856_, v___x_860_);
v___y_838_ = v___x_861_;
goto v___jp_837_;
}
}
v___jp_863_:
{
uint32_t v___x_868_; uint32_t v___x_869_; uint32_t v___x_870_; uint32_t v___x_871_; uint32_t v___x_872_; 
v___x_868_ = lean_uint32_land(v___y_866_, v___x_862_);
v___x_869_ = lean_uint32_shift_left(v___x_868_, v___x_847_);
v___x_870_ = lean_uint32_lor(v___y_867_, v___x_869_);
v___x_871_ = lean_uint32_land(v___y_865_, v___y_864_);
v___x_872_ = lean_uint32_lor(v___x_870_, v___x_871_);
return v___x_872_;
}
v___jp_873_:
{
if (v___y_876_ == 0)
{
uint32_t v___x_878_; 
v___x_878_ = 0;
v___y_864_ = v___y_874_;
v___y_865_ = v___y_877_;
v___y_866_ = v___y_875_;
v___y_867_ = v___x_878_;
goto v___jp_863_;
}
else
{
uint32_t v___x_879_; 
v___x_879_ = 2147483648;
v___y_864_ = v___y_874_;
v___y_865_ = v___y_877_;
v___y_866_ = v___y_875_;
v___y_867_ = v___x_879_;
goto v___jp_863_;
}
}
v___jp_880_:
{
uint64_t v___x_886_; uint64_t v_encodedExponent_887_; uint32_t v___x_888_; uint64_t v___x_889_; uint8_t v___x_890_; 
v___x_886_ = 171ULL;
v_encodedExponent_887_ = lean_uint64_sub(v___y_883_, v___x_886_);
v___x_888_ = lean_uint64_to_uint32(v_encodedExponent_887_);
v___x_889_ = 8388608ULL;
v___x_890_ = lean_uint64_dec_lt(v___y_885_, v___x_889_);
if (v___x_890_ == 0)
{
uint64_t v___x_891_; uint32_t v___x_892_; 
v___x_891_ = lean_uint64_sub(v___y_885_, v___x_889_);
v___x_892_ = lean_uint64_to_uint32(v___x_891_);
v___y_874_ = v___y_881_;
v___y_875_ = v___x_888_;
v___y_876_ = v___y_884_;
v___y_877_ = v___x_892_;
goto v___jp_873_;
}
else
{
uint32_t v___x_893_; 
v___x_893_ = lean_uint64_to_uint32(v___y_882_);
v___y_874_ = v___y_881_;
v___y_875_ = v___x_888_;
v___y_876_ = v___y_884_;
v___y_877_ = v___x_893_;
goto v___jp_873_;
}
}
v___jp_894_:
{
uint64_t v___x_901_; uint8_t v___x_902_; 
v___x_901_ = 425ULL;
v___x_902_ = lean_uint64_dec_lt(v___x_901_, v___y_900_);
if (v___x_902_ == 0)
{
if (v___y_897_ == 0)
{
v___y_881_ = v___y_895_;
v___y_882_ = v___y_896_;
v___y_883_ = v___y_900_;
v___y_884_ = v___y_898_;
v___y_885_ = v___y_899_;
goto v___jp_880_;
}
else
{
uint64_t v___x_903_; 
v___x_903_ = 8388608ULL;
v___y_881_ = v___y_895_;
v___y_882_ = v___y_896_;
v___y_883_ = v___y_900_;
v___y_884_ = v___y_898_;
v___y_885_ = v___x_903_;
goto v___jp_880_;
}
}
else
{
if (v___y_898_ == 0)
{
uint32_t v___x_904_; 
v___x_904_ = 2139095040;
return v___x_904_;
}
else
{
uint32_t v___x_905_; 
v___x_905_ = 4286578688;
return v___x_905_;
}
}
}
v___jp_906_:
{
uint64_t v___x_912_; uint8_t v_carry_913_; 
v___x_912_ = 16777216ULL;
v_carry_913_ = lean_uint64_dec_eq(v___y_911_, v___x_912_);
if (v_carry_913_ == 0)
{
v___y_895_ = v___y_907_;
v___y_896_ = v___y_909_;
v___y_897_ = v_carry_913_;
v___y_898_ = v___y_910_;
v___y_899_ = v___y_911_;
v___y_900_ = v___y_908_;
goto v___jp_894_;
}
else
{
uint64_t v___x_914_; uint64_t v___x_915_; 
v___x_914_ = 1ULL;
v___x_915_ = lean_uint64_add(v___y_908_, v___x_914_);
v___y_895_ = v___y_907_;
v___y_896_ = v___y_909_;
v___y_897_ = v_carry_913_;
v___y_898_ = v___y_910_;
v___y_899_ = v___y_911_;
v___y_900_ = v___x_915_;
goto v___jp_894_;
}
}
v___jp_916_:
{
uint64_t v_position_923_; uint64_t v___x_924_; uint8_t v___x_925_; 
v_position_923_ = lean_uint64_add(v___y_922_, v___y_917_);
v___x_924_ = 172ULL;
v___x_925_ = lean_uint64_dec_lt(v_position_923_, v___x_924_);
if (v___x_925_ == 0)
{
uint64_t v___x_926_; uint8_t v___x_927_; 
v___x_926_ = 23ULL;
v___x_927_ = lean_uint64_dec_lt(v___y_922_, v___x_926_);
if (v___x_927_ == 0)
{
uint64_t v___x_928_; uint8_t v___x_929_; 
v___x_928_ = lean_uint64_sub(v___y_922_, v___x_926_);
v___x_929_ = lean_uint64_dec_eq(v___x_928_, v___y_920_);
if (v___x_929_ == 0)
{
uint64_t v___x_930_; uint8_t v___x_931_; 
v___x_930_ = 64ULL;
v___x_931_ = lean_uint64_dec_lt(v___x_928_, v___x_930_);
if (v___x_931_ == 0)
{
uint8_t v___x_932_; 
v___x_932_ = lean_uint64_dec_eq(v___x_928_, v___x_930_);
if (v___x_932_ == 0)
{
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v___y_920_;
goto v___jp_906_;
}
else
{
uint64_t v___x_933_; uint8_t v___x_934_; 
v___x_933_ = 9223372036854775808ULL;
v___x_934_ = lean_uint64_dec_lt(v___x_933_, v___y_919_);
if (v___x_934_ == 0)
{
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v___y_920_;
goto v___jp_906_;
}
else
{
uint64_t v___x_935_; 
v___x_935_ = 1ULL;
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v___x_935_;
goto v___jp_906_;
}
}
}
else
{
uint64_t v_quotient_936_; uint64_t v___x_937_; uint64_t v___x_938_; uint64_t v___x_939_; uint64_t v_remainder_940_; uint64_t v___x_941_; uint64_t v_half_942_; uint8_t v___x_943_; 
v_quotient_936_ = lean_uint64_shift_right(v___y_919_, v___x_928_);
v___x_937_ = 1ULL;
v___x_938_ = lean_uint64_shift_left(v___x_937_, v___x_928_);
v___x_939_ = lean_uint64_sub(v___x_938_, v___x_937_);
v_remainder_940_ = lean_uint64_land(v___y_919_, v___x_939_);
v___x_941_ = lean_uint64_sub(v___x_928_, v___x_937_);
v_half_942_ = lean_uint64_shift_left(v___x_937_, v___x_941_);
v___x_943_ = lean_uint64_dec_lt(v_remainder_940_, v_half_942_);
if (v___x_943_ == 0)
{
uint8_t v___x_944_; 
v___x_944_ = lean_uint64_dec_lt(v_half_942_, v_remainder_940_);
if (v___x_944_ == 0)
{
uint64_t v___x_945_; uint8_t v___x_946_; 
v___x_945_ = lean_uint64_land(v_quotient_936_, v___x_937_);
v___x_946_ = lean_uint64_dec_eq(v___x_945_, v___y_920_);
if (v___x_946_ == 0)
{
uint64_t v___x_947_; 
v___x_947_ = lean_uint64_add(v_quotient_936_, v___x_937_);
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v___x_947_;
goto v___jp_906_;
}
else
{
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v_quotient_936_;
goto v___jp_906_;
}
}
else
{
uint64_t v___x_948_; 
v___x_948_ = lean_uint64_add(v_quotient_936_, v___x_937_);
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v___x_948_;
goto v___jp_906_;
}
}
else
{
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v_quotient_936_;
goto v___jp_906_;
}
}
}
else
{
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v___y_919_;
goto v___jp_906_;
}
}
else
{
uint64_t v___x_949_; uint64_t v___x_950_; 
v___x_949_ = lean_uint64_sub(v___x_926_, v___y_922_);
v___x_950_ = lean_uint64_shift_left(v___y_919_, v___x_949_);
v___y_907_ = v___y_918_;
v___y_908_ = v_position_923_;
v___y_909_ = v___y_920_;
v___y_910_ = v___y_921_;
v___y_911_ = v___x_950_;
goto v___jp_906_;
}
}
else
{
uint64_t v___x_951_; uint8_t v___x_952_; 
v___x_951_ = 149ULL;
v___x_952_ = lean_uint64_dec_lt(v___y_917_, v___x_951_);
if (v___x_952_ == 0)
{
uint64_t v___x_953_; uint64_t v___x_954_; 
v___x_953_ = lean_uint64_sub(v___y_917_, v___x_951_);
v___x_954_ = lean_uint64_shift_left(v___y_919_, v___x_953_);
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v___x_954_;
goto v___jp_716_;
}
else
{
uint64_t v___x_955_; uint8_t v___x_956_; 
v___x_955_ = lean_uint64_sub(v___x_951_, v___y_917_);
v___x_956_ = lean_uint64_dec_eq(v___x_955_, v___y_920_);
if (v___x_956_ == 0)
{
uint64_t v___x_957_; uint8_t v___x_958_; 
v___x_957_ = 64ULL;
v___x_958_ = lean_uint64_dec_lt(v___x_955_, v___x_957_);
if (v___x_958_ == 0)
{
uint8_t v___x_959_; 
v___x_959_ = lean_uint64_dec_eq(v___x_955_, v___x_957_);
if (v___x_959_ == 0)
{
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v___y_920_;
goto v___jp_716_;
}
else
{
uint64_t v___x_960_; uint8_t v___x_961_; 
v___x_960_ = 9223372036854775808ULL;
v___x_961_ = lean_uint64_dec_lt(v___x_960_, v___y_919_);
if (v___x_961_ == 0)
{
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v___y_920_;
goto v___jp_716_;
}
else
{
uint64_t v___x_962_; 
v___x_962_ = 1ULL;
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v___x_962_;
goto v___jp_716_;
}
}
}
else
{
uint64_t v_quotient_963_; uint64_t v___x_964_; uint64_t v___x_965_; uint64_t v___x_966_; uint64_t v_remainder_967_; uint64_t v___x_968_; uint64_t v_half_969_; uint8_t v___x_970_; 
v_quotient_963_ = lean_uint64_shift_right(v___y_919_, v___x_955_);
v___x_964_ = 1ULL;
v___x_965_ = lean_uint64_shift_left(v___x_964_, v___x_955_);
v___x_966_ = lean_uint64_sub(v___x_965_, v___x_964_);
v_remainder_967_ = lean_uint64_land(v___y_919_, v___x_966_);
v___x_968_ = lean_uint64_sub(v___x_955_, v___x_964_);
v_half_969_ = lean_uint64_shift_left(v___x_964_, v___x_968_);
v___x_970_ = lean_uint64_dec_lt(v_remainder_967_, v_half_969_);
if (v___x_970_ == 0)
{
uint8_t v___x_971_; 
v___x_971_ = lean_uint64_dec_lt(v_half_969_, v_remainder_967_);
if (v___x_971_ == 0)
{
uint64_t v___x_972_; uint8_t v___x_973_; 
v___x_972_ = lean_uint64_land(v_quotient_963_, v___x_964_);
v___x_973_ = lean_uint64_dec_eq(v___x_972_, v___y_920_);
if (v___x_973_ == 0)
{
uint64_t v___x_974_; 
v___x_974_ = lean_uint64_add(v_quotient_963_, v___x_964_);
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v___x_974_;
goto v___jp_716_;
}
else
{
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v_quotient_963_;
goto v___jp_716_;
}
}
else
{
uint64_t v___x_975_; 
v___x_975_ = lean_uint64_add(v_quotient_963_, v___x_964_);
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v___x_975_;
goto v___jp_716_;
}
}
else
{
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v_quotient_963_;
goto v___jp_716_;
}
}
}
else
{
v___y_717_ = v___y_918_;
v___y_718_ = v___y_920_;
v___y_719_ = v___y_921_;
v___y_720_ = v___y_919_;
goto v___jp_716_;
}
}
}
}
v___jp_976_:
{
uint64_t v___x_984_; uint64_t v___x_985_; uint8_t v___x_986_; 
v___x_984_ = 1ULL;
v___x_985_ = lean_uint64_shift_right(v___y_982_, v___x_984_);
v___x_986_ = lean_uint64_dec_eq(v___x_985_, v___y_980_);
if (v___x_986_ == 0)
{
uint64_t v___x_987_; 
v___x_987_ = lean_uint64_add(v___y_983_, v___x_984_);
v___y_917_ = v___y_977_;
v___y_918_ = v___y_978_;
v___y_919_ = v___y_979_;
v___y_920_ = v___y_980_;
v___y_921_ = v___y_981_;
v___y_922_ = v___x_987_;
goto v___jp_916_;
}
else
{
v___y_917_ = v___y_977_;
v___y_918_ = v___y_978_;
v___y_919_ = v___y_979_;
v___y_920_ = v___y_980_;
v___y_921_ = v___y_981_;
v___y_922_ = v___y_983_;
goto v___jp_916_;
}
}
v___jp_988_:
{
uint64_t v___x_998_; uint8_t v___x_999_; 
v___x_998_ = lean_uint64_shift_right(v___y_995_, v___y_993_);
v___x_999_ = lean_uint64_dec_eq(v___x_998_, v___y_994_);
if (v___x_999_ == 0)
{
uint64_t v___x_1000_; 
v___x_1000_ = lean_uint64_add(v___y_991_, v___y_993_);
v___y_977_ = v___y_989_;
v___y_978_ = v___y_990_;
v___y_979_ = v___y_992_;
v___y_980_ = v___y_994_;
v___y_981_ = v___y_996_;
v___y_982_ = v___y_997_;
v___y_983_ = v___x_1000_;
goto v___jp_976_;
}
else
{
v___y_977_ = v___y_989_;
v___y_978_ = v___y_990_;
v___y_979_ = v___y_992_;
v___y_980_ = v___y_994_;
v___y_981_ = v___y_996_;
v___y_982_ = v___y_997_;
v___y_983_ = v___y_991_;
goto v___jp_976_;
}
}
v___jp_1001_:
{
uint64_t v___x_1009_; uint64_t v___x_1010_; uint8_t v___x_1011_; 
v___x_1009_ = 2ULL;
v___x_1010_ = lean_uint64_shift_right(v___y_1006_, v___x_1009_);
v___x_1011_ = lean_uint64_dec_eq(v___x_1010_, v___y_1005_);
if (v___x_1011_ == 0)
{
v___y_989_ = v___y_1002_;
v___y_990_ = v___y_1003_;
v___y_991_ = v___y_1008_;
v___y_992_ = v___y_1004_;
v___y_993_ = v___x_1009_;
v___y_994_ = v___y_1005_;
v___y_995_ = v___y_1006_;
v___y_996_ = v___y_1007_;
v___y_997_ = v___x_1010_;
goto v___jp_988_;
}
else
{
v___y_989_ = v___y_1002_;
v___y_990_ = v___y_1003_;
v___y_991_ = v___y_1008_;
v___y_992_ = v___y_1004_;
v___y_993_ = v___x_1009_;
v___y_994_ = v___y_1005_;
v___y_995_ = v___y_1006_;
v___y_996_ = v___y_1007_;
v___y_997_ = v___y_1006_;
goto v___jp_988_;
}
}
v___jp_1012_:
{
uint64_t v___x_1022_; uint8_t v___x_1023_; 
v___x_1022_ = lean_uint64_shift_right(v___y_1015_, v___y_1020_);
v___x_1023_ = lean_uint64_dec_eq(v___x_1022_, v___y_1017_);
if (v___x_1023_ == 0)
{
uint64_t v___x_1024_; 
v___x_1024_ = lean_uint64_add(v___y_1018_, v___y_1020_);
v___y_1002_ = v___y_1013_;
v___y_1003_ = v___y_1014_;
v___y_1004_ = v___y_1016_;
v___y_1005_ = v___y_1017_;
v___y_1006_ = v___y_1021_;
v___y_1007_ = v___y_1019_;
v___y_1008_ = v___x_1024_;
goto v___jp_1001_;
}
else
{
v___y_1002_ = v___y_1013_;
v___y_1003_ = v___y_1014_;
v___y_1004_ = v___y_1016_;
v___y_1005_ = v___y_1017_;
v___y_1006_ = v___y_1021_;
v___y_1007_ = v___y_1019_;
v___y_1008_ = v___y_1018_;
goto v___jp_1001_;
}
}
v___jp_1025_:
{
uint64_t v___x_1033_; uint64_t v___x_1034_; uint8_t v___x_1035_; 
v___x_1033_ = 4ULL;
v___x_1034_ = lean_uint64_shift_right(v___y_1029_, v___x_1033_);
v___x_1035_ = lean_uint64_dec_eq(v___x_1034_, v___y_1030_);
if (v___x_1035_ == 0)
{
v___y_1013_ = v___y_1026_;
v___y_1014_ = v___y_1027_;
v___y_1015_ = v___y_1029_;
v___y_1016_ = v___y_1028_;
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___y_1032_;
v___y_1019_ = v___y_1031_;
v___y_1020_ = v___x_1033_;
v___y_1021_ = v___x_1034_;
goto v___jp_1012_;
}
else
{
v___y_1013_ = v___y_1026_;
v___y_1014_ = v___y_1027_;
v___y_1015_ = v___y_1029_;
v___y_1016_ = v___y_1028_;
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___y_1032_;
v___y_1019_ = v___y_1031_;
v___y_1020_ = v___x_1033_;
v___y_1021_ = v___y_1029_;
goto v___jp_1012_;
}
}
v___jp_1036_:
{
uint64_t v___x_1046_; uint8_t v___x_1047_; 
v___x_1046_ = lean_uint64_shift_right(v___y_1042_, v___y_1038_);
v___x_1047_ = lean_uint64_dec_eq(v___x_1046_, v___y_1043_);
if (v___x_1047_ == 0)
{
uint64_t v___x_1048_; 
v___x_1048_ = lean_uint64_add(v___y_1040_, v___y_1038_);
v___y_1026_ = v___y_1037_;
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1041_;
v___y_1029_ = v___y_1045_;
v___y_1030_ = v___y_1043_;
v___y_1031_ = v___y_1044_;
v___y_1032_ = v___x_1048_;
goto v___jp_1025_;
}
else
{
v___y_1026_ = v___y_1037_;
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1041_;
v___y_1029_ = v___y_1045_;
v___y_1030_ = v___y_1043_;
v___y_1031_ = v___y_1044_;
v___y_1032_ = v___y_1040_;
goto v___jp_1025_;
}
}
v___jp_1049_:
{
uint64_t v___x_1057_; uint64_t v___x_1058_; uint8_t v___x_1059_; 
v___x_1057_ = 8ULL;
v___x_1058_ = lean_uint64_shift_right(v___y_1054_, v___x_1057_);
v___x_1059_ = lean_uint64_dec_eq(v___x_1058_, v___y_1053_);
if (v___x_1059_ == 0)
{
v___y_1037_ = v___y_1050_;
v___y_1038_ = v___x_1057_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1056_;
v___y_1041_ = v___y_1052_;
v___y_1042_ = v___y_1054_;
v___y_1043_ = v___y_1053_;
v___y_1044_ = v___y_1055_;
v___y_1045_ = v___x_1058_;
goto v___jp_1036_;
}
else
{
v___y_1037_ = v___y_1050_;
v___y_1038_ = v___x_1057_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1056_;
v___y_1041_ = v___y_1052_;
v___y_1042_ = v___y_1054_;
v___y_1043_ = v___y_1053_;
v___y_1044_ = v___y_1055_;
v___y_1045_ = v___y_1054_;
goto v___jp_1036_;
}
}
v___jp_1060_:
{
uint64_t v___x_1070_; uint8_t v___x_1071_; 
v___x_1070_ = lean_uint64_shift_right(v___y_1061_, v___y_1064_);
v___x_1071_ = lean_uint64_dec_eq(v___x_1070_, v___y_1066_);
if (v___x_1071_ == 0)
{
uint64_t v___x_1072_; 
v___x_1072_ = lean_uint64_add(v___y_1067_, v___y_1064_);
v___y_1050_ = v___y_1062_;
v___y_1051_ = v___y_1063_;
v___y_1052_ = v___y_1065_;
v___y_1053_ = v___y_1066_;
v___y_1054_ = v___y_1069_;
v___y_1055_ = v___y_1068_;
v___y_1056_ = v___x_1072_;
goto v___jp_1049_;
}
else
{
v___y_1050_ = v___y_1062_;
v___y_1051_ = v___y_1063_;
v___y_1052_ = v___y_1065_;
v___y_1053_ = v___y_1066_;
v___y_1054_ = v___y_1069_;
v___y_1055_ = v___y_1068_;
v___y_1056_ = v___y_1067_;
goto v___jp_1049_;
}
}
v___jp_1073_:
{
uint64_t v___x_1081_; uint64_t v___x_1082_; uint8_t v___x_1083_; 
v___x_1081_ = 16ULL;
v___x_1082_ = lean_uint64_shift_right(v___y_1075_, v___x_1081_);
v___x_1083_ = lean_uint64_dec_eq(v___x_1082_, v___y_1078_);
if (v___x_1083_ == 0)
{
v___y_1061_ = v___y_1075_;
v___y_1062_ = v___y_1074_;
v___y_1063_ = v___y_1076_;
v___y_1064_ = v___x_1081_;
v___y_1065_ = v___y_1077_;
v___y_1066_ = v___y_1078_;
v___y_1067_ = v___y_1080_;
v___y_1068_ = v___y_1079_;
v___y_1069_ = v___x_1082_;
goto v___jp_1060_;
}
else
{
v___y_1061_ = v___y_1075_;
v___y_1062_ = v___y_1074_;
v___y_1063_ = v___y_1076_;
v___y_1064_ = v___x_1081_;
v___y_1065_ = v___y_1077_;
v___y_1066_ = v___y_1078_;
v___y_1067_ = v___y_1080_;
v___y_1068_ = v___y_1079_;
v___y_1069_ = v___y_1075_;
goto v___jp_1060_;
}
}
v___jp_1084_:
{
uint64_t v___x_1092_; uint8_t v___x_1093_; 
v___x_1092_ = lean_uint64_shift_right(v___y_1087_, v___y_1089_);
v___x_1093_ = lean_uint64_dec_eq(v___x_1092_, v___y_1088_);
if (v___x_1093_ == 0)
{
v___y_1074_ = v___y_1085_;
v___y_1075_ = v___y_1091_;
v___y_1076_ = v___y_1086_;
v___y_1077_ = v___y_1087_;
v___y_1078_ = v___y_1088_;
v___y_1079_ = v___y_1090_;
v___y_1080_ = v___y_1089_;
goto v___jp_1073_;
}
else
{
v___y_1074_ = v___y_1085_;
v___y_1075_ = v___y_1091_;
v___y_1076_ = v___y_1086_;
v___y_1077_ = v___y_1087_;
v___y_1078_ = v___y_1088_;
v___y_1079_ = v___y_1090_;
v___y_1080_ = v___y_1088_;
goto v___jp_1073_;
}
}
v___jp_1094_:
{
uint64_t v___x_1099_; uint8_t v___x_1100_; 
v___x_1099_ = 0ULL;
v___x_1100_ = lean_uint64_dec_eq(v___y_1097_, v___x_1099_);
if (v___x_1100_ == 0)
{
uint64_t v___x_1101_; uint64_t v___x_1102_; uint8_t v___x_1103_; 
v___x_1101_ = 32ULL;
v___x_1102_ = lean_uint64_shift_right(v___y_1097_, v___x_1101_);
v___x_1103_ = lean_uint64_dec_eq(v___x_1102_, v___x_1099_);
if (v___x_1103_ == 0)
{
v___y_1085_ = v___y_1095_;
v___y_1086_ = v___y_1096_;
v___y_1087_ = v___y_1097_;
v___y_1088_ = v___x_1099_;
v___y_1089_ = v___x_1101_;
v___y_1090_ = v___y_1098_;
v___y_1091_ = v___x_1102_;
goto v___jp_1084_;
}
else
{
v___y_1085_ = v___y_1095_;
v___y_1086_ = v___y_1096_;
v___y_1087_ = v___y_1097_;
v___y_1088_ = v___x_1099_;
v___y_1089_ = v___x_1101_;
v___y_1090_ = v___y_1098_;
v___y_1091_ = v___y_1097_;
goto v___jp_1084_;
}
}
else
{
if (v___y_1098_ == 0)
{
uint32_t v___x_1104_; 
v___x_1104_ = 0;
return v___x_1104_;
}
else
{
uint32_t v___x_1105_; 
v___x_1105_ = 2147483648;
return v___x_1105_;
}
}
}
v___jp_1106_:
{
uint64_t v___x_1113_; uint64_t v___x_1114_; uint64_t v___x_1115_; uint8_t v___x_1116_; 
v___x_1113_ = lean_uint64_mul(v___y_1110_, v___y_1109_);
v___x_1114_ = lean_uint64_add(v___y_1108_, v___y_1112_);
v___x_1115_ = 281474976710656ULL;
v___x_1116_ = lean_uint64_dec_lt(v___x_1113_, v___x_1115_);
if (v___x_1116_ == 0)
{
v___y_1095_ = v___x_1114_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___x_1113_;
v___y_1098_ = v___y_1111_;
goto v___jp_1094_;
}
else
{
uint64_t v___x_1117_; uint8_t v___x_1118_; 
v___x_1117_ = 123ULL;
v___x_1118_ = lean_uint64_dec_le(v___x_1114_, v___x_1117_);
if (v___x_1118_ == 0)
{
v___y_1095_ = v___x_1114_;
v___y_1096_ = v___y_1107_;
v___y_1097_ = v___x_1113_;
v___y_1098_ = v___y_1111_;
goto v___jp_1094_;
}
else
{
uint64_t v___x_1119_; uint8_t v___x_1120_; 
v___x_1119_ = 0ULL;
v___x_1120_ = lean_uint64_dec_eq(v___x_1113_, v___x_1119_);
if (v___x_1120_ == 0)
{
uint64_t v___x_1121_; uint64_t v___x_1122_; uint8_t v___x_1123_; 
v___x_1121_ = 149ULL;
v___x_1122_ = lean_uint64_sub(v___x_1121_, v___x_1114_);
v___x_1123_ = lean_uint64_dec_eq(v___x_1122_, v___x_1119_);
if (v___x_1123_ == 0)
{
uint64_t v___x_1124_; uint8_t v___x_1125_; 
v___x_1124_ = 64ULL;
v___x_1125_ = lean_uint64_dec_lt(v___x_1122_, v___x_1124_);
if (v___x_1125_ == 0)
{
uint8_t v___x_1126_; 
v___x_1126_ = lean_uint64_dec_eq(v___x_1122_, v___x_1124_);
if (v___x_1126_ == 0)
{
v___y_738_ = v___y_1107_;
v___y_739_ = v___x_1119_;
v___y_740_ = v___y_1111_;
v___y_741_ = v___x_1119_;
goto v___jp_737_;
}
else
{
uint64_t v___x_1127_; uint8_t v___x_1128_; 
v___x_1127_ = 9223372036854775808ULL;
v___x_1128_ = lean_uint64_dec_lt(v___x_1127_, v___x_1113_);
if (v___x_1128_ == 0)
{
v___y_738_ = v___y_1107_;
v___y_739_ = v___x_1119_;
v___y_740_ = v___y_1111_;
v___y_741_ = v___x_1119_;
goto v___jp_737_;
}
else
{
uint64_t v___x_1129_; 
v___x_1129_ = 1ULL;
v___y_738_ = v___y_1107_;
v___y_739_ = v___x_1119_;
v___y_740_ = v___y_1111_;
v___y_741_ = v___x_1129_;
goto v___jp_737_;
}
}
}
else
{
uint64_t v_quotient_1130_; uint64_t v___x_1131_; uint64_t v___x_1132_; uint64_t v___x_1133_; uint64_t v_remainder_1134_; uint64_t v___x_1135_; uint64_t v_half_1136_; uint8_t v___x_1137_; 
v_quotient_1130_ = lean_uint64_shift_right(v___x_1113_, v___x_1122_);
v___x_1131_ = 1ULL;
v___x_1132_ = lean_uint64_shift_left(v___x_1131_, v___x_1122_);
v___x_1133_ = lean_uint64_sub(v___x_1132_, v___x_1131_);
v_remainder_1134_ = lean_uint64_land(v___x_1113_, v___x_1133_);
v___x_1135_ = lean_uint64_sub(v___x_1122_, v___x_1131_);
v_half_1136_ = lean_uint64_shift_left(v___x_1131_, v___x_1135_);
v___x_1137_ = lean_uint64_dec_lt(v_remainder_1134_, v_half_1136_);
if (v___x_1137_ == 0)
{
uint8_t v___x_1138_; 
v___x_1138_ = lean_uint64_dec_lt(v_half_1136_, v_remainder_1134_);
if (v___x_1138_ == 0)
{
uint64_t v___x_1139_; uint8_t v___x_1140_; 
v___x_1139_ = lean_uint64_land(v_quotient_1130_, v___x_1131_);
v___x_1140_ = lean_uint64_dec_eq(v___x_1139_, v___x_1119_);
if (v___x_1140_ == 0)
{
uint64_t v___x_1141_; 
v___x_1141_ = lean_uint64_add(v_quotient_1130_, v___x_1131_);
v___y_738_ = v___y_1107_;
v___y_739_ = v___x_1119_;
v___y_740_ = v___y_1111_;
v___y_741_ = v___x_1141_;
goto v___jp_737_;
}
else
{
v___y_738_ = v___y_1107_;
v___y_739_ = v___x_1119_;
v___y_740_ = v___y_1111_;
v___y_741_ = v_quotient_1130_;
goto v___jp_737_;
}
}
else
{
uint64_t v___x_1142_; 
v___x_1142_ = lean_uint64_add(v_quotient_1130_, v___x_1131_);
v___y_738_ = v___y_1107_;
v___y_739_ = v___x_1119_;
v___y_740_ = v___y_1111_;
v___y_741_ = v___x_1142_;
goto v___jp_737_;
}
}
else
{
v___y_738_ = v___y_1107_;
v___y_739_ = v___x_1119_;
v___y_740_ = v___y_1111_;
v___y_741_ = v_quotient_1130_;
goto v___jp_737_;
}
}
}
else
{
v___y_738_ = v___y_1107_;
v___y_739_ = v___x_1119_;
v___y_740_ = v___y_1111_;
v___y_741_ = v___x_1113_;
goto v___jp_737_;
}
}
else
{
if (v___y_1111_ == 0)
{
uint32_t v___x_1143_; 
v___x_1143_ = 0;
return v___x_1143_;
}
else
{
uint32_t v___x_1144_; 
v___x_1144_ = 2147483648;
return v___x_1144_;
}
}
}
}
}
v___jp_1148_:
{
uint64_t v___x_1154_; uint64_t v___x_1155_; uint8_t v___x_1156_; 
v___x_1154_ = lean_uint32_to_uint64(v_ey_1147_);
v___x_1155_ = 0ULL;
v___x_1156_ = lean_uint64_dec_eq(v___x_1154_, v___x_1155_);
if (v___x_1156_ == 0)
{
uint64_t v___x_1157_; uint64_t v___x_1158_; 
v___x_1157_ = 1ULL;
v___x_1158_ = lean_uint64_sub(v___x_1154_, v___x_1157_);
v___y_1107_ = v___y_1149_;
v___y_1108_ = v___y_1153_;
v___y_1109_ = v___y_1150_;
v___y_1110_ = v___y_1151_;
v___y_1111_ = v___y_1152_;
v___y_1112_ = v___x_1158_;
goto v___jp_1106_;
}
else
{
v___y_1107_ = v___y_1149_;
v___y_1108_ = v___y_1153_;
v___y_1109_ = v___y_1150_;
v___y_1110_ = v___y_1151_;
v___y_1111_ = v___y_1152_;
v___y_1112_ = v___x_1155_;
goto v___jp_1106_;
}
}
v___jp_1159_:
{
uint64_t v___x_1164_; uint64_t v___x_1165_; uint8_t v___x_1166_; 
v___x_1164_ = lean_uint32_to_uint64(v_ex_1145_);
v___x_1165_ = 0ULL;
v___x_1166_ = lean_uint64_dec_eq(v___x_1164_, v___x_1165_);
if (v___x_1166_ == 0)
{
uint64_t v___x_1167_; uint64_t v___x_1168_; 
v___x_1167_ = 1ULL;
v___x_1168_ = lean_uint64_sub(v___x_1164_, v___x_1167_);
v___y_1149_ = v___y_1160_;
v___y_1150_ = v___y_1163_;
v___y_1151_ = v___y_1161_;
v___y_1152_ = v___y_1162_;
v___y_1153_ = v___x_1168_;
goto v___jp_1148_;
}
else
{
v___y_1149_ = v___y_1160_;
v___y_1150_ = v___y_1163_;
v___y_1151_ = v___y_1161_;
v___y_1152_ = v___y_1162_;
v___y_1153_ = v___x_1165_;
goto v___jp_1148_;
}
}
v___jp_1169_:
{
uint32_t v___x_1174_; uint8_t v___x_1175_; 
v___x_1174_ = 0;
v___x_1175_ = lean_uint32_dec_eq(v_ey_1147_, v___x_1174_);
if (v___x_1175_ == 0)
{
uint64_t v___x_1176_; uint64_t v___x_1177_; uint64_t v___x_1178_; 
v___x_1176_ = lean_uint32_to_uint64(v___y_1171_);
v___x_1177_ = 8388608ULL;
v___x_1178_ = lean_uint64_lor(v___x_1176_, v___x_1177_);
v___y_1160_ = v___y_1170_;
v___y_1161_ = v___y_1173_;
v___y_1162_ = v___y_1172_;
v___y_1163_ = v___x_1178_;
goto v___jp_1159_;
}
else
{
uint64_t v___x_1179_; 
v___x_1179_ = lean_uint32_to_uint64(v___y_1171_);
v___y_1160_ = v___y_1170_;
v___y_1161_ = v___y_1173_;
v___y_1162_ = v___y_1172_;
v___y_1163_ = v___x_1179_;
goto v___jp_1159_;
}
}
v___jp_1180_:
{
uint32_t v___x_1182_; uint32_t v_xFraction_1183_; uint32_t v_yFraction_1184_; uint32_t v___x_1185_; uint8_t v___x_1186_; 
v___x_1182_ = 8388607;
v_xFraction_1183_ = lean_uint32_land(v___y_700_, v___x_1182_);
v_yFraction_1184_ = lean_uint32_land(v___y_701_, v___x_1182_);
v___x_1185_ = 0;
v___x_1186_ = lean_uint32_dec_eq(v_ex_1145_, v___x_1185_);
if (v___x_1186_ == 0)
{
uint64_t v___x_1187_; uint64_t v___x_1188_; uint64_t v___x_1189_; 
v___x_1187_ = lean_uint32_to_uint64(v_xFraction_1183_);
v___x_1188_ = 8388608ULL;
v___x_1189_ = lean_uint64_lor(v___x_1187_, v___x_1188_);
v___y_1170_ = v___x_1182_;
v___y_1171_ = v_yFraction_1184_;
v___y_1172_ = v___y_1181_;
v___y_1173_ = v___x_1189_;
goto v___jp_1169_;
}
else
{
uint64_t v___x_1190_; 
v___x_1190_ = lean_uint32_to_uint64(v_xFraction_1183_);
v___y_1170_ = v___x_1182_;
v___y_1171_ = v_yFraction_1184_;
v___y_1172_ = v___y_1181_;
v___y_1173_ = v___x_1190_;
goto v___jp_1169_;
}
}
v___jp_1194_:
{
if (v___y_1196_ == 0)
{
v___y_1181_ = v___x_1193_;
goto v___jp_1180_;
}
else
{
v___y_1181_ = v___y_1195_;
goto v___jp_1180_;
}
}
v___jp_1197_:
{
if (v___y_1198_ == 0)
{
if (v___y_1200_ == 0)
{
v___y_1195_ = v___y_1199_;
v___y_1196_ = v___x_1193_;
goto v___jp_1194_;
}
else
{
v___y_1181_ = v___x_1193_;
goto v___jp_1180_;
}
}
else
{
v___y_1195_ = v___y_1199_;
v___y_1196_ = v___y_1200_;
goto v___jp_1194_;
}
}
v___jp_1201_:
{
uint32_t v___x_1204_; uint32_t v___x_1205_; uint32_t v___x_1206_; uint8_t v___x_1207_; 
v___x_1204_ = 2147483648;
v___x_1205_ = lean_uint32_land(v___y_701_, v___x_1204_);
v___x_1206_ = 0;
v___x_1207_ = lean_uint32_dec_eq(v___x_1205_, v___x_1206_);
if (v___x_1207_ == 0)
{
v___y_1198_ = v___y_1203_;
v___y_1199_ = v___y_1202_;
v___y_1200_ = v___x_1193_;
goto v___jp_1197_;
}
else
{
v___y_1198_ = v___y_1203_;
v___y_1199_ = v___y_1202_;
v___y_1200_ = v___y_1202_;
goto v___jp_1197_;
}
}
v___jp_1208_:
{
if (v___y_1209_ == 0)
{
uint32_t v___x_1210_; uint32_t v___x_1211_; uint32_t v___x_1212_; uint8_t v___x_1213_; 
v___x_1210_ = 2147483648;
v___x_1211_ = lean_uint32_land(v___y_700_, v___x_1210_);
v___x_1212_ = 0;
v___x_1213_ = lean_uint32_dec_eq(v___x_1211_, v___x_1212_);
if (v___x_1213_ == 0)
{
v___y_1202_ = v___y_1209_;
v___y_1203_ = v___x_1193_;
goto v___jp_1201_;
}
else
{
v___y_1202_ = v___y_1209_;
v___y_1203_ = v___y_1209_;
goto v___jp_1201_;
}
}
else
{
lean_object* v___x_1214_; lean_object* v___x_1215_; lean_object* v___x_1216_; uint32_t v___x_1217_; 
v___x_1214_ = lean_uint32_to_nat(v___y_700_);
v___x_1215_ = lean_uint32_to_nat(v___y_701_);
v___x_1216_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1214_, v___x_1215_);
v___x_1217_ = lean_uint32_of_nat(v___x_1216_);
lean_dec(v___x_1216_);
return v___x_1217_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_1232_, lean_object* v___y_1233_){
_start:
{
uint32_t v___y_10443__boxed_1234_; uint32_t v___y_10444__boxed_1235_; uint32_t v_res_1236_; lean_object* v_r_1237_; 
v___y_10443__boxed_1234_ = lean_unbox_uint32(v___y_1232_);
lean_dec(v___y_1232_);
v___y_10444__boxed_1235_ = lean_unbox_uint32(v___y_1233_);
lean_dec(v___y_1233_);
v_res_1236_ = lp_competition_main___lam__1(v___y_10443__boxed_1234_, v___y_10444__boxed_1235_);
v_r_1237_ = lean_box_uint32(v_res_1236_);
return v_r_1237_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__2(uint32_t v___y_1238_, uint32_t v___y_1239_){
_start:
{
uint32_t v___y_1241_; uint32_t v___y_1242_; uint32_t v___y_1243_; uint32_t v___y_1244_; uint32_t v___y_1245_; uint32_t v___y_1246_; uint32_t v___y_1253_; uint32_t v___y_1254_; uint32_t v___y_1255_; uint32_t v___y_1256_; uint32_t v___y_1257_; uint32_t v___y_1258_; uint8_t v___y_1269_; uint8_t v___y_1283_; uint8_t v___y_1297_; uint8_t v___y_1314_; float v___y_1321_; float v___y_1322_; float v___y_1336_; uint8_t v___y_1337_; float v___y_1352_; uint8_t v___y_1362_; uint8_t v___y_1382_; uint8_t v___y_1396_; uint8_t v___y_1410_; uint8_t v___y_1427_; float v___y_1434_; float v___y_1435_; float v___y_1449_; uint8_t v___y_1450_; float v___y_1465_; uint8_t v___y_1475_; uint8_t v___y_1495_; uint8_t v___y_1509_; uint8_t v___y_1523_; uint8_t v___y_1540_; float v___y_1547_; float v___y_1548_; float v___y_1562_; uint8_t v___y_1563_; float v___y_1578_; uint32_t v___y_1588_; uint8_t v___y_1589_; uint8_t v___y_1608_; uint8_t v___y_1622_; uint8_t v___y_1636_; uint8_t v___y_1653_; float v___y_1660_; float v___y_1661_; float v___y_1675_; uint8_t v___y_1676_; float v___y_1691_; uint32_t v___y_1701_; uint32_t v___y_1702_; uint8_t v___y_1703_; uint32_t v___y_1716_; uint32_t v___y_1717_; uint32_t v___y_1718_; uint32_t v___y_1719_; uint32_t v___y_1720_; uint32_t v___y_1721_; uint32_t v___y_1745_; uint32_t v___y_1768_; uint32_t v___y_1769_; uint8_t v___y_1770_; uint32_t v___y_1774_; uint32_t v___y_1775_; uint32_t v___y_1776_; uint32_t v___y_1777_; uint32_t v___y_1785_; uint32_t v___y_1786_; uint32_t v___y_1787_; uint32_t v___y_1788_; uint32_t v___y_1789_; uint32_t v___y_1790_; uint32_t v___y_1791_; uint32_t v___y_1802_; uint32_t v___y_1803_; uint32_t v___y_1804_; uint32_t v___y_1805_; uint32_t v___y_1816_; uint8_t v___y_1837_; uint32_t v___y_1847_; uint32_t v___y_1848_; uint32_t v___y_1849_; uint32_t v___y_1850_; uint32_t v___y_1851_; uint32_t v___y_1857_; uint32_t v___y_1858_; uint8_t v___y_1869_; uint32_t v___y_1879_; uint32_t v___y_1880_; uint32_t v___y_1881_; uint32_t v___y_1882_; uint32_t v___y_1892_; uint8_t v___y_1903_; uint32_t v___x_1919_; uint32_t v___x_1920_; uint32_t v___x_1921_; uint32_t v___x_1922_; uint32_t v___x_1923_; uint32_t v___x_1924_; uint32_t v___x_1925_; uint8_t v___x_1926_; 
v___x_1919_ = 23;
v___x_1920_ = lean_uint32_shift_right(v___y_1238_, v___x_1919_);
v___x_1921_ = 255;
v___x_1922_ = lean_uint32_land(v___x_1920_, v___x_1921_);
v___x_1923_ = 1;
v___x_1924_ = lean_uint32_sub(v___x_1922_, v___x_1923_);
v___x_1925_ = 253;
v___x_1926_ = lean_uint32_dec_le(v___x_1924_, v___x_1925_);
if (v___x_1926_ == 0)
{
v___y_1903_ = v___x_1926_;
goto v___jp_1902_;
}
else
{
uint32_t v___x_1927_; uint32_t v___x_1928_; uint32_t v___x_1929_; uint8_t v___x_1930_; 
v___x_1927_ = lean_uint32_shift_right(v___y_1239_, v___x_1919_);
v___x_1928_ = lean_uint32_land(v___x_1927_, v___x_1921_);
v___x_1929_ = lean_uint32_sub(v___x_1928_, v___x_1923_);
v___x_1930_ = lean_uint32_dec_le(v___x_1929_, v___x_1925_);
v___y_1903_ = v___x_1930_;
goto v___jp_1902_;
}
v___jp_1240_:
{
uint32_t v___x_1247_; uint32_t v___x_1248_; uint32_t v___x_1249_; uint32_t v___x_1250_; uint32_t v___x_1251_; 
v___x_1247_ = lean_uint32_land(v___y_1242_, v___y_1245_);
v___x_1248_ = lean_uint32_shift_left(v___x_1247_, v___y_1244_);
v___x_1249_ = lean_uint32_lor(v___y_1246_, v___x_1248_);
v___x_1250_ = lean_uint32_land(v___y_1243_, v___y_1241_);
v___x_1251_ = lean_uint32_lor(v___x_1249_, v___x_1250_);
return v___x_1251_;
}
v___jp_1252_:
{
uint8_t v___x_1259_; uint32_t v___x_1260_; uint32_t v___x_1261_; 
v___x_1259_ = lean_uint32_dec_le(v___y_1254_, v___y_1258_);
v___x_1260_ = 8388607;
v___x_1261_ = lean_uint32_land(v___y_1256_, v___x_1260_);
if (v___x_1259_ == 0)
{
uint32_t v___x_1262_; 
v___x_1262_ = 0;
v___y_1241_ = v___x_1260_;
v___y_1242_ = v___y_1253_;
v___y_1243_ = v___x_1261_;
v___y_1244_ = v___y_1255_;
v___y_1245_ = v___y_1257_;
v___y_1246_ = v___x_1262_;
goto v___jp_1240_;
}
else
{
v___y_1241_ = v___x_1260_;
v___y_1242_ = v___y_1253_;
v___y_1243_ = v___x_1261_;
v___y_1244_ = v___y_1255_;
v___y_1245_ = v___y_1257_;
v___y_1246_ = v___y_1254_;
goto v___jp_1240_;
}
}
v___jp_1263_:
{
lean_object* v___x_1264_; lean_object* v___x_1265_; lean_object* v___x_1266_; uint32_t v___x_1267_; 
v___x_1264_ = lean_uint32_to_nat(v___y_1238_);
v___x_1265_ = lean_uint32_to_nat(v___y_1239_);
v___x_1266_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1264_, v___x_1265_);
v___x_1267_ = lean_uint32_of_nat(v___x_1266_);
lean_dec(v___x_1266_);
return v___x_1267_;
}
v___jp_1268_:
{
if (v___y_1269_ == 0)
{
goto v___jp_1263_;
}
else
{
uint32_t v___x_1270_; uint32_t v___x_1271_; 
v___x_1270_ = 4194304;
v___x_1271_ = lean_uint32_lor(v___y_1239_, v___x_1270_);
return v___x_1271_;
}
}
v___jp_1272_:
{
uint32_t v___x_1273_; uint32_t v___x_1274_; uint32_t v___x_1275_; uint32_t v___x_1276_; uint8_t v___x_1277_; 
v___x_1273_ = 23;
v___x_1274_ = lean_uint32_shift_right(v___y_1239_, v___x_1273_);
v___x_1275_ = 255;
v___x_1276_ = lean_uint32_land(v___x_1274_, v___x_1275_);
v___x_1277_ = lean_uint32_dec_eq(v___x_1276_, v___x_1275_);
if (v___x_1277_ == 0)
{
v___y_1269_ = v___x_1277_;
goto v___jp_1268_;
}
else
{
uint32_t v___x_1278_; uint32_t v___x_1279_; uint32_t v___x_1280_; uint8_t v___x_1281_; 
v___x_1278_ = 8388607;
v___x_1279_ = lean_uint32_land(v___y_1239_, v___x_1278_);
v___x_1280_ = 0;
v___x_1281_ = lean_uint32_dec_eq(v___x_1279_, v___x_1280_);
if (v___x_1281_ == 0)
{
v___y_1269_ = v___x_1277_;
goto v___jp_1268_;
}
else
{
goto v___jp_1263_;
}
}
}
v___jp_1282_:
{
if (v___y_1283_ == 0)
{
goto v___jp_1272_;
}
else
{
uint32_t v___x_1284_; uint32_t v___x_1285_; 
v___x_1284_ = 4194304;
v___x_1285_ = lean_uint32_lor(v___y_1238_, v___x_1284_);
return v___x_1285_;
}
}
v___jp_1286_:
{
uint32_t v___x_1287_; uint32_t v___x_1288_; uint32_t v___x_1289_; uint32_t v___x_1290_; uint8_t v___x_1291_; 
v___x_1287_ = 23;
v___x_1288_ = lean_uint32_shift_right(v___y_1238_, v___x_1287_);
v___x_1289_ = 255;
v___x_1290_ = lean_uint32_land(v___x_1288_, v___x_1289_);
v___x_1291_ = lean_uint32_dec_eq(v___x_1290_, v___x_1289_);
if (v___x_1291_ == 0)
{
v___y_1283_ = v___x_1291_;
goto v___jp_1282_;
}
else
{
uint32_t v___x_1292_; uint32_t v___x_1293_; uint32_t v___x_1294_; uint8_t v___x_1295_; 
v___x_1292_ = 8388607;
v___x_1293_ = lean_uint32_land(v___y_1238_, v___x_1292_);
v___x_1294_ = 0;
v___x_1295_ = lean_uint32_dec_eq(v___x_1293_, v___x_1294_);
if (v___x_1295_ == 0)
{
v___y_1283_ = v___x_1291_;
goto v___jp_1282_;
}
else
{
goto v___jp_1272_;
}
}
}
v___jp_1296_:
{
if (v___y_1297_ == 0)
{
goto v___jp_1286_;
}
else
{
uint32_t v___x_1298_; uint32_t v___x_1299_; uint32_t v___x_1300_; uint8_t v___x_1301_; 
v___x_1298_ = 4194304;
v___x_1299_ = lean_uint32_land(v___y_1239_, v___x_1298_);
v___x_1300_ = 0;
v___x_1301_ = lean_uint32_dec_eq(v___x_1299_, v___x_1300_);
if (v___x_1301_ == 0)
{
goto v___jp_1286_;
}
else
{
uint32_t v___x_1302_; 
v___x_1302_ = lean_uint32_lor(v___y_1239_, v___x_1298_);
return v___x_1302_;
}
}
}
v___jp_1303_:
{
uint32_t v___x_1304_; uint32_t v___x_1305_; uint32_t v___x_1306_; uint32_t v___x_1307_; uint8_t v___x_1308_; 
v___x_1304_ = 23;
v___x_1305_ = lean_uint32_shift_right(v___y_1239_, v___x_1304_);
v___x_1306_ = 255;
v___x_1307_ = lean_uint32_land(v___x_1305_, v___x_1306_);
v___x_1308_ = lean_uint32_dec_eq(v___x_1307_, v___x_1306_);
if (v___x_1308_ == 0)
{
v___y_1297_ = v___x_1308_;
goto v___jp_1296_;
}
else
{
uint32_t v___x_1309_; uint32_t v___x_1310_; uint32_t v___x_1311_; uint8_t v___x_1312_; 
v___x_1309_ = 8388607;
v___x_1310_ = lean_uint32_land(v___y_1239_, v___x_1309_);
v___x_1311_ = 0;
v___x_1312_ = lean_uint32_dec_eq(v___x_1310_, v___x_1311_);
if (v___x_1312_ == 0)
{
v___y_1297_ = v___x_1308_;
goto v___jp_1296_;
}
else
{
goto v___jp_1286_;
}
}
}
v___jp_1313_:
{
if (v___y_1314_ == 0)
{
goto v___jp_1303_;
}
else
{
uint32_t v___x_1315_; uint32_t v___x_1316_; uint32_t v___x_1317_; uint8_t v___x_1318_; 
v___x_1315_ = 4194304;
v___x_1316_ = lean_uint32_land(v___y_1238_, v___x_1315_);
v___x_1317_ = 0;
v___x_1318_ = lean_uint32_dec_eq(v___x_1316_, v___x_1317_);
if (v___x_1318_ == 0)
{
goto v___jp_1303_;
}
else
{
uint32_t v___x_1319_; 
v___x_1319_ = lean_uint32_lor(v___y_1238_, v___x_1315_);
return v___x_1319_;
}
}
}
v___jp_1320_:
{
float v_result_1323_; uint8_t v___x_1324_; 
v_result_1323_ = lean_float32_add(v___y_1321_, v___y_1322_);
v___x_1324_ = lean_float32_beq(v_result_1323_, v_result_1323_);
if (v___x_1324_ == 0)
{
uint32_t v___x_1325_; uint32_t v___x_1326_; uint32_t v___x_1327_; uint32_t v___x_1328_; uint8_t v___x_1329_; 
v___x_1325_ = 23;
v___x_1326_ = lean_uint32_shift_right(v___y_1238_, v___x_1325_);
v___x_1327_ = 255;
v___x_1328_ = lean_uint32_land(v___x_1326_, v___x_1327_);
v___x_1329_ = lean_uint32_dec_eq(v___x_1328_, v___x_1327_);
if (v___x_1329_ == 0)
{
v___y_1314_ = v___x_1329_;
goto v___jp_1313_;
}
else
{
uint32_t v___x_1330_; uint32_t v___x_1331_; uint32_t v___x_1332_; uint8_t v___x_1333_; 
v___x_1330_ = 8388607;
v___x_1331_ = lean_uint32_land(v___y_1238_, v___x_1330_);
v___x_1332_ = 0;
v___x_1333_ = lean_uint32_dec_eq(v___x_1331_, v___x_1332_);
if (v___x_1333_ == 0)
{
v___y_1314_ = v___x_1329_;
goto v___jp_1313_;
}
else
{
goto v___jp_1303_;
}
}
}
else
{
uint32_t v___x_1334_; 
v___x_1334_ = lean_float32_to_bits(v_result_1323_);
return v___x_1334_;
}
}
v___jp_1335_:
{
if (v___y_1337_ == 0)
{
float v___x_1338_; 
v___x_1338_ = lean_float32_of_bits(v___y_1239_);
v___y_1321_ = v___y_1336_;
v___y_1322_ = v___x_1338_;
goto v___jp_1320_;
}
else
{
uint32_t v___x_1339_; uint32_t v___x_1340_; uint32_t v___x_1341_; uint32_t v___x_1342_; float v___x_1343_; lean_object* v___x_1344_; uint32_t v___x_1345_; uint32_t v___x_1346_; lean_object* v___x_1347_; lean_object* v___x_1348_; float v___x_1349_; float v___x_1350_; 
v___x_1339_ = 8388607;
v___x_1340_ = lean_uint32_land(v___y_1239_, v___x_1339_);
v___x_1341_ = 8388608;
v___x_1342_ = lean_uint32_lor(v___x_1340_, v___x_1341_);
v___x_1343_ = lean_uint32_to_float32(v___x_1342_);
v___x_1344_ = lp_competition_R2W01b_scaleTable;
v___x_1345_ = 23;
v___x_1346_ = lean_uint32_shift_right(v___y_1239_, v___x_1345_);
v___x_1347_ = lean_uint32_to_nat(v___x_1346_);
v___x_1348_ = lean_array_fget_borrowed(v___x_1344_, v___x_1347_);
lean_dec(v___x_1347_);
v___x_1349_ = lean_unbox_float32(v___x_1348_);
v___x_1350_ = lean_float32_mul(v___x_1343_, v___x_1349_);
v___y_1321_ = v___y_1336_;
v___y_1322_ = v___x_1350_;
goto v___jp_1320_;
}
}
v___jp_1351_:
{
uint32_t v___x_1353_; uint32_t v_a_1354_; uint32_t v___x_1355_; uint32_t v___x_1356_; uint32_t v___x_1357_; uint8_t v___x_1358_; 
v___x_1353_ = 2147483647;
v_a_1354_ = lean_uint32_land(v___y_1239_, v___x_1353_);
v___x_1355_ = 201326591;
v___x_1356_ = 1;
v___x_1357_ = lean_uint32_sub(v_a_1354_, v___x_1356_);
v___x_1358_ = lean_uint32_dec_le(v___x_1355_, v___x_1357_);
if (v___x_1358_ == 0)
{
v___y_1336_ = v___y_1352_;
v___y_1337_ = v___x_1358_;
goto v___jp_1335_;
}
else
{
uint32_t v___x_1359_; uint8_t v___x_1360_; 
v___x_1359_ = 2139095040;
v___x_1360_ = lean_uint32_dec_lt(v_a_1354_, v___x_1359_);
v___y_1336_ = v___y_1352_;
v___y_1337_ = v___x_1360_;
goto v___jp_1335_;
}
}
v___jp_1361_:
{
if (v___y_1362_ == 0)
{
float v___x_1363_; 
v___x_1363_ = lean_float32_of_bits(v___y_1238_);
v___y_1352_ = v___x_1363_;
goto v___jp_1351_;
}
else
{
uint32_t v___x_1364_; uint32_t v___x_1365_; uint32_t v___x_1366_; uint32_t v___x_1367_; float v___x_1368_; lean_object* v___x_1369_; uint32_t v___x_1370_; uint32_t v___x_1371_; lean_object* v___x_1372_; lean_object* v___x_1373_; float v___x_1374_; float v___x_1375_; 
v___x_1364_ = 8388607;
v___x_1365_ = lean_uint32_land(v___y_1238_, v___x_1364_);
v___x_1366_ = 8388608;
v___x_1367_ = lean_uint32_lor(v___x_1365_, v___x_1366_);
v___x_1368_ = lean_uint32_to_float32(v___x_1367_);
v___x_1369_ = lp_competition_R2W01b_scaleTable;
v___x_1370_ = 23;
v___x_1371_ = lean_uint32_shift_right(v___y_1238_, v___x_1370_);
v___x_1372_ = lean_uint32_to_nat(v___x_1371_);
v___x_1373_ = lean_array_fget_borrowed(v___x_1369_, v___x_1372_);
lean_dec(v___x_1372_);
v___x_1374_ = lean_unbox_float32(v___x_1373_);
v___x_1375_ = lean_float32_mul(v___x_1368_, v___x_1374_);
v___y_1352_ = v___x_1375_;
goto v___jp_1351_;
}
}
v___jp_1376_:
{
lean_object* v___x_1377_; lean_object* v___x_1378_; lean_object* v___x_1379_; uint32_t v___x_1380_; 
v___x_1377_ = lean_uint32_to_nat(v___y_1238_);
v___x_1378_ = lean_uint32_to_nat(v___y_1239_);
v___x_1379_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1377_, v___x_1378_);
v___x_1380_ = lean_uint32_of_nat(v___x_1379_);
lean_dec(v___x_1379_);
return v___x_1380_;
}
v___jp_1381_:
{
if (v___y_1382_ == 0)
{
goto v___jp_1376_;
}
else
{
uint32_t v___x_1383_; uint32_t v___x_1384_; 
v___x_1383_ = 4194304;
v___x_1384_ = lean_uint32_lor(v___y_1239_, v___x_1383_);
return v___x_1384_;
}
}
v___jp_1385_:
{
uint32_t v___x_1386_; uint32_t v___x_1387_; uint32_t v___x_1388_; uint32_t v___x_1389_; uint8_t v___x_1390_; 
v___x_1386_ = 23;
v___x_1387_ = lean_uint32_shift_right(v___y_1239_, v___x_1386_);
v___x_1388_ = 255;
v___x_1389_ = lean_uint32_land(v___x_1387_, v___x_1388_);
v___x_1390_ = lean_uint32_dec_eq(v___x_1389_, v___x_1388_);
if (v___x_1390_ == 0)
{
v___y_1382_ = v___x_1390_;
goto v___jp_1381_;
}
else
{
uint32_t v___x_1391_; uint32_t v___x_1392_; uint32_t v___x_1393_; uint8_t v___x_1394_; 
v___x_1391_ = 8388607;
v___x_1392_ = lean_uint32_land(v___y_1239_, v___x_1391_);
v___x_1393_ = 0;
v___x_1394_ = lean_uint32_dec_eq(v___x_1392_, v___x_1393_);
if (v___x_1394_ == 0)
{
v___y_1382_ = v___x_1390_;
goto v___jp_1381_;
}
else
{
goto v___jp_1376_;
}
}
}
v___jp_1395_:
{
if (v___y_1396_ == 0)
{
goto v___jp_1385_;
}
else
{
uint32_t v___x_1397_; uint32_t v___x_1398_; 
v___x_1397_ = 4194304;
v___x_1398_ = lean_uint32_lor(v___y_1238_, v___x_1397_);
return v___x_1398_;
}
}
v___jp_1399_:
{
uint32_t v___x_1400_; uint32_t v___x_1401_; uint32_t v___x_1402_; uint32_t v___x_1403_; uint8_t v___x_1404_; 
v___x_1400_ = 23;
v___x_1401_ = lean_uint32_shift_right(v___y_1238_, v___x_1400_);
v___x_1402_ = 255;
v___x_1403_ = lean_uint32_land(v___x_1401_, v___x_1402_);
v___x_1404_ = lean_uint32_dec_eq(v___x_1403_, v___x_1402_);
if (v___x_1404_ == 0)
{
v___y_1396_ = v___x_1404_;
goto v___jp_1395_;
}
else
{
uint32_t v___x_1405_; uint32_t v___x_1406_; uint32_t v___x_1407_; uint8_t v___x_1408_; 
v___x_1405_ = 8388607;
v___x_1406_ = lean_uint32_land(v___y_1238_, v___x_1405_);
v___x_1407_ = 0;
v___x_1408_ = lean_uint32_dec_eq(v___x_1406_, v___x_1407_);
if (v___x_1408_ == 0)
{
v___y_1396_ = v___x_1404_;
goto v___jp_1395_;
}
else
{
goto v___jp_1385_;
}
}
}
v___jp_1409_:
{
if (v___y_1410_ == 0)
{
goto v___jp_1399_;
}
else
{
uint32_t v___x_1411_; uint32_t v___x_1412_; uint32_t v___x_1413_; uint8_t v___x_1414_; 
v___x_1411_ = 4194304;
v___x_1412_ = lean_uint32_land(v___y_1239_, v___x_1411_);
v___x_1413_ = 0;
v___x_1414_ = lean_uint32_dec_eq(v___x_1412_, v___x_1413_);
if (v___x_1414_ == 0)
{
goto v___jp_1399_;
}
else
{
uint32_t v___x_1415_; 
v___x_1415_ = lean_uint32_lor(v___y_1239_, v___x_1411_);
return v___x_1415_;
}
}
}
v___jp_1416_:
{
uint32_t v___x_1417_; uint32_t v___x_1418_; uint32_t v___x_1419_; uint32_t v___x_1420_; uint8_t v___x_1421_; 
v___x_1417_ = 23;
v___x_1418_ = lean_uint32_shift_right(v___y_1239_, v___x_1417_);
v___x_1419_ = 255;
v___x_1420_ = lean_uint32_land(v___x_1418_, v___x_1419_);
v___x_1421_ = lean_uint32_dec_eq(v___x_1420_, v___x_1419_);
if (v___x_1421_ == 0)
{
v___y_1410_ = v___x_1421_;
goto v___jp_1409_;
}
else
{
uint32_t v___x_1422_; uint32_t v___x_1423_; uint32_t v___x_1424_; uint8_t v___x_1425_; 
v___x_1422_ = 8388607;
v___x_1423_ = lean_uint32_land(v___y_1239_, v___x_1422_);
v___x_1424_ = 0;
v___x_1425_ = lean_uint32_dec_eq(v___x_1423_, v___x_1424_);
if (v___x_1425_ == 0)
{
v___y_1410_ = v___x_1421_;
goto v___jp_1409_;
}
else
{
goto v___jp_1399_;
}
}
}
v___jp_1426_:
{
if (v___y_1427_ == 0)
{
goto v___jp_1416_;
}
else
{
uint32_t v___x_1428_; uint32_t v___x_1429_; uint32_t v___x_1430_; uint8_t v___x_1431_; 
v___x_1428_ = 4194304;
v___x_1429_ = lean_uint32_land(v___y_1238_, v___x_1428_);
v___x_1430_ = 0;
v___x_1431_ = lean_uint32_dec_eq(v___x_1429_, v___x_1430_);
if (v___x_1431_ == 0)
{
goto v___jp_1416_;
}
else
{
uint32_t v___x_1432_; 
v___x_1432_ = lean_uint32_lor(v___y_1238_, v___x_1428_);
return v___x_1432_;
}
}
}
v___jp_1433_:
{
float v_result_1436_; uint8_t v___x_1437_; 
v_result_1436_ = lean_float32_add(v___y_1434_, v___y_1435_);
v___x_1437_ = lean_float32_beq(v_result_1436_, v_result_1436_);
if (v___x_1437_ == 0)
{
uint32_t v___x_1438_; uint32_t v___x_1439_; uint32_t v___x_1440_; uint32_t v___x_1441_; uint8_t v___x_1442_; 
v___x_1438_ = 23;
v___x_1439_ = lean_uint32_shift_right(v___y_1238_, v___x_1438_);
v___x_1440_ = 255;
v___x_1441_ = lean_uint32_land(v___x_1439_, v___x_1440_);
v___x_1442_ = lean_uint32_dec_eq(v___x_1441_, v___x_1440_);
if (v___x_1442_ == 0)
{
v___y_1427_ = v___x_1442_;
goto v___jp_1426_;
}
else
{
uint32_t v___x_1443_; uint32_t v___x_1444_; uint32_t v___x_1445_; uint8_t v___x_1446_; 
v___x_1443_ = 8388607;
v___x_1444_ = lean_uint32_land(v___y_1238_, v___x_1443_);
v___x_1445_ = 0;
v___x_1446_ = lean_uint32_dec_eq(v___x_1444_, v___x_1445_);
if (v___x_1446_ == 0)
{
v___y_1427_ = v___x_1442_;
goto v___jp_1426_;
}
else
{
goto v___jp_1416_;
}
}
}
else
{
uint32_t v___x_1447_; 
v___x_1447_ = lean_float32_to_bits(v_result_1436_);
return v___x_1447_;
}
}
v___jp_1448_:
{
if (v___y_1450_ == 0)
{
float v___x_1451_; 
v___x_1451_ = lean_float32_of_bits(v___y_1239_);
v___y_1434_ = v___y_1449_;
v___y_1435_ = v___x_1451_;
goto v___jp_1433_;
}
else
{
uint32_t v___x_1452_; uint32_t v___x_1453_; uint32_t v___x_1454_; uint32_t v___x_1455_; float v___x_1456_; lean_object* v___x_1457_; uint32_t v___x_1458_; uint32_t v___x_1459_; lean_object* v___x_1460_; lean_object* v___x_1461_; float v___x_1462_; float v___x_1463_; 
v___x_1452_ = 8388607;
v___x_1453_ = lean_uint32_land(v___y_1239_, v___x_1452_);
v___x_1454_ = 8388608;
v___x_1455_ = lean_uint32_lor(v___x_1453_, v___x_1454_);
v___x_1456_ = lean_uint32_to_float32(v___x_1455_);
v___x_1457_ = lp_competition_R2W01b_scaleTable;
v___x_1458_ = 23;
v___x_1459_ = lean_uint32_shift_right(v___y_1239_, v___x_1458_);
v___x_1460_ = lean_uint32_to_nat(v___x_1459_);
v___x_1461_ = lean_array_fget_borrowed(v___x_1457_, v___x_1460_);
lean_dec(v___x_1460_);
v___x_1462_ = lean_unbox_float32(v___x_1461_);
v___x_1463_ = lean_float32_mul(v___x_1456_, v___x_1462_);
v___y_1434_ = v___y_1449_;
v___y_1435_ = v___x_1463_;
goto v___jp_1433_;
}
}
v___jp_1464_:
{
uint32_t v___x_1466_; uint32_t v_a_1467_; uint32_t v___x_1468_; uint32_t v___x_1469_; uint32_t v___x_1470_; uint8_t v___x_1471_; 
v___x_1466_ = 2147483647;
v_a_1467_ = lean_uint32_land(v___y_1239_, v___x_1466_);
v___x_1468_ = 201326591;
v___x_1469_ = 1;
v___x_1470_ = lean_uint32_sub(v_a_1467_, v___x_1469_);
v___x_1471_ = lean_uint32_dec_le(v___x_1468_, v___x_1470_);
if (v___x_1471_ == 0)
{
v___y_1449_ = v___y_1465_;
v___y_1450_ = v___x_1471_;
goto v___jp_1448_;
}
else
{
uint32_t v___x_1472_; uint8_t v___x_1473_; 
v___x_1472_ = 2139095040;
v___x_1473_ = lean_uint32_dec_lt(v_a_1467_, v___x_1472_);
v___y_1449_ = v___y_1465_;
v___y_1450_ = v___x_1473_;
goto v___jp_1448_;
}
}
v___jp_1474_:
{
if (v___y_1475_ == 0)
{
float v___x_1476_; 
v___x_1476_ = lean_float32_of_bits(v___y_1238_);
v___y_1465_ = v___x_1476_;
goto v___jp_1464_;
}
else
{
uint32_t v___x_1477_; uint32_t v___x_1478_; uint32_t v___x_1479_; uint32_t v___x_1480_; float v___x_1481_; lean_object* v___x_1482_; uint32_t v___x_1483_; uint32_t v___x_1484_; lean_object* v___x_1485_; lean_object* v___x_1486_; float v___x_1487_; float v___x_1488_; 
v___x_1477_ = 8388607;
v___x_1478_ = lean_uint32_land(v___y_1238_, v___x_1477_);
v___x_1479_ = 8388608;
v___x_1480_ = lean_uint32_lor(v___x_1478_, v___x_1479_);
v___x_1481_ = lean_uint32_to_float32(v___x_1480_);
v___x_1482_ = lp_competition_R2W01b_scaleTable;
v___x_1483_ = 23;
v___x_1484_ = lean_uint32_shift_right(v___y_1238_, v___x_1483_);
v___x_1485_ = lean_uint32_to_nat(v___x_1484_);
v___x_1486_ = lean_array_fget_borrowed(v___x_1482_, v___x_1485_);
lean_dec(v___x_1485_);
v___x_1487_ = lean_unbox_float32(v___x_1486_);
v___x_1488_ = lean_float32_mul(v___x_1481_, v___x_1487_);
v___y_1465_ = v___x_1488_;
goto v___jp_1464_;
}
}
v___jp_1489_:
{
lean_object* v___x_1490_; lean_object* v___x_1491_; lean_object* v___x_1492_; uint32_t v___x_1493_; 
v___x_1490_ = lean_uint32_to_nat(v___y_1238_);
v___x_1491_ = lean_uint32_to_nat(v___y_1239_);
v___x_1492_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1490_, v___x_1491_);
v___x_1493_ = lean_uint32_of_nat(v___x_1492_);
lean_dec(v___x_1492_);
return v___x_1493_;
}
v___jp_1494_:
{
if (v___y_1495_ == 0)
{
goto v___jp_1489_;
}
else
{
uint32_t v___x_1496_; uint32_t v___x_1497_; 
v___x_1496_ = 4194304;
v___x_1497_ = lean_uint32_lor(v___y_1239_, v___x_1496_);
return v___x_1497_;
}
}
v___jp_1498_:
{
uint32_t v___x_1499_; uint32_t v___x_1500_; uint32_t v___x_1501_; uint32_t v___x_1502_; uint8_t v___x_1503_; 
v___x_1499_ = 23;
v___x_1500_ = lean_uint32_shift_right(v___y_1239_, v___x_1499_);
v___x_1501_ = 255;
v___x_1502_ = lean_uint32_land(v___x_1500_, v___x_1501_);
v___x_1503_ = lean_uint32_dec_eq(v___x_1502_, v___x_1501_);
if (v___x_1503_ == 0)
{
v___y_1495_ = v___x_1503_;
goto v___jp_1494_;
}
else
{
uint32_t v___x_1504_; uint32_t v___x_1505_; uint32_t v___x_1506_; uint8_t v___x_1507_; 
v___x_1504_ = 8388607;
v___x_1505_ = lean_uint32_land(v___y_1239_, v___x_1504_);
v___x_1506_ = 0;
v___x_1507_ = lean_uint32_dec_eq(v___x_1505_, v___x_1506_);
if (v___x_1507_ == 0)
{
v___y_1495_ = v___x_1503_;
goto v___jp_1494_;
}
else
{
goto v___jp_1489_;
}
}
}
v___jp_1508_:
{
if (v___y_1509_ == 0)
{
goto v___jp_1498_;
}
else
{
uint32_t v___x_1510_; uint32_t v___x_1511_; 
v___x_1510_ = 4194304;
v___x_1511_ = lean_uint32_lor(v___y_1238_, v___x_1510_);
return v___x_1511_;
}
}
v___jp_1512_:
{
uint32_t v___x_1513_; uint32_t v___x_1514_; uint32_t v___x_1515_; uint32_t v___x_1516_; uint8_t v___x_1517_; 
v___x_1513_ = 23;
v___x_1514_ = lean_uint32_shift_right(v___y_1238_, v___x_1513_);
v___x_1515_ = 255;
v___x_1516_ = lean_uint32_land(v___x_1514_, v___x_1515_);
v___x_1517_ = lean_uint32_dec_eq(v___x_1516_, v___x_1515_);
if (v___x_1517_ == 0)
{
v___y_1509_ = v___x_1517_;
goto v___jp_1508_;
}
else
{
uint32_t v___x_1518_; uint32_t v___x_1519_; uint32_t v___x_1520_; uint8_t v___x_1521_; 
v___x_1518_ = 8388607;
v___x_1519_ = lean_uint32_land(v___y_1238_, v___x_1518_);
v___x_1520_ = 0;
v___x_1521_ = lean_uint32_dec_eq(v___x_1519_, v___x_1520_);
if (v___x_1521_ == 0)
{
v___y_1509_ = v___x_1517_;
goto v___jp_1508_;
}
else
{
goto v___jp_1498_;
}
}
}
v___jp_1522_:
{
if (v___y_1523_ == 0)
{
goto v___jp_1512_;
}
else
{
uint32_t v___x_1524_; uint32_t v___x_1525_; uint32_t v___x_1526_; uint8_t v___x_1527_; 
v___x_1524_ = 4194304;
v___x_1525_ = lean_uint32_land(v___y_1239_, v___x_1524_);
v___x_1526_ = 0;
v___x_1527_ = lean_uint32_dec_eq(v___x_1525_, v___x_1526_);
if (v___x_1527_ == 0)
{
goto v___jp_1512_;
}
else
{
uint32_t v___x_1528_; 
v___x_1528_ = lean_uint32_lor(v___y_1239_, v___x_1524_);
return v___x_1528_;
}
}
}
v___jp_1529_:
{
uint32_t v___x_1530_; uint32_t v___x_1531_; uint32_t v___x_1532_; uint32_t v___x_1533_; uint8_t v___x_1534_; 
v___x_1530_ = 23;
v___x_1531_ = lean_uint32_shift_right(v___y_1239_, v___x_1530_);
v___x_1532_ = 255;
v___x_1533_ = lean_uint32_land(v___x_1531_, v___x_1532_);
v___x_1534_ = lean_uint32_dec_eq(v___x_1533_, v___x_1532_);
if (v___x_1534_ == 0)
{
v___y_1523_ = v___x_1534_;
goto v___jp_1522_;
}
else
{
uint32_t v___x_1535_; uint32_t v___x_1536_; uint32_t v___x_1537_; uint8_t v___x_1538_; 
v___x_1535_ = 8388607;
v___x_1536_ = lean_uint32_land(v___y_1239_, v___x_1535_);
v___x_1537_ = 0;
v___x_1538_ = lean_uint32_dec_eq(v___x_1536_, v___x_1537_);
if (v___x_1538_ == 0)
{
v___y_1523_ = v___x_1534_;
goto v___jp_1522_;
}
else
{
goto v___jp_1512_;
}
}
}
v___jp_1539_:
{
if (v___y_1540_ == 0)
{
goto v___jp_1529_;
}
else
{
uint32_t v___x_1541_; uint32_t v___x_1542_; uint32_t v___x_1543_; uint8_t v___x_1544_; 
v___x_1541_ = 4194304;
v___x_1542_ = lean_uint32_land(v___y_1238_, v___x_1541_);
v___x_1543_ = 0;
v___x_1544_ = lean_uint32_dec_eq(v___x_1542_, v___x_1543_);
if (v___x_1544_ == 0)
{
goto v___jp_1529_;
}
else
{
uint32_t v___x_1545_; 
v___x_1545_ = lean_uint32_lor(v___y_1238_, v___x_1541_);
return v___x_1545_;
}
}
}
v___jp_1546_:
{
float v_result_1549_; uint8_t v___x_1550_; 
v_result_1549_ = lean_float32_add(v___y_1547_, v___y_1548_);
v___x_1550_ = lean_float32_beq(v_result_1549_, v_result_1549_);
if (v___x_1550_ == 0)
{
uint32_t v___x_1551_; uint32_t v___x_1552_; uint32_t v___x_1553_; uint32_t v___x_1554_; uint8_t v___x_1555_; 
v___x_1551_ = 23;
v___x_1552_ = lean_uint32_shift_right(v___y_1238_, v___x_1551_);
v___x_1553_ = 255;
v___x_1554_ = lean_uint32_land(v___x_1552_, v___x_1553_);
v___x_1555_ = lean_uint32_dec_eq(v___x_1554_, v___x_1553_);
if (v___x_1555_ == 0)
{
v___y_1540_ = v___x_1555_;
goto v___jp_1539_;
}
else
{
uint32_t v___x_1556_; uint32_t v___x_1557_; uint32_t v___x_1558_; uint8_t v___x_1559_; 
v___x_1556_ = 8388607;
v___x_1557_ = lean_uint32_land(v___y_1238_, v___x_1556_);
v___x_1558_ = 0;
v___x_1559_ = lean_uint32_dec_eq(v___x_1557_, v___x_1558_);
if (v___x_1559_ == 0)
{
v___y_1540_ = v___x_1555_;
goto v___jp_1539_;
}
else
{
goto v___jp_1529_;
}
}
}
else
{
uint32_t v___x_1560_; 
v___x_1560_ = lean_float32_to_bits(v_result_1549_);
return v___x_1560_;
}
}
v___jp_1561_:
{
if (v___y_1563_ == 0)
{
float v___x_1564_; 
v___x_1564_ = lean_float32_of_bits(v___y_1239_);
v___y_1547_ = v___y_1562_;
v___y_1548_ = v___x_1564_;
goto v___jp_1546_;
}
else
{
uint32_t v___x_1565_; uint32_t v___x_1566_; uint32_t v___x_1567_; uint32_t v___x_1568_; float v___x_1569_; lean_object* v___x_1570_; uint32_t v___x_1571_; uint32_t v___x_1572_; lean_object* v___x_1573_; lean_object* v___x_1574_; float v___x_1575_; float v___x_1576_; 
v___x_1565_ = 8388607;
v___x_1566_ = lean_uint32_land(v___y_1239_, v___x_1565_);
v___x_1567_ = 8388608;
v___x_1568_ = lean_uint32_lor(v___x_1566_, v___x_1567_);
v___x_1569_ = lean_uint32_to_float32(v___x_1568_);
v___x_1570_ = lp_competition_R2W01b_scaleTable;
v___x_1571_ = 23;
v___x_1572_ = lean_uint32_shift_right(v___y_1239_, v___x_1571_);
v___x_1573_ = lean_uint32_to_nat(v___x_1572_);
v___x_1574_ = lean_array_fget_borrowed(v___x_1570_, v___x_1573_);
lean_dec(v___x_1573_);
v___x_1575_ = lean_unbox_float32(v___x_1574_);
v___x_1576_ = lean_float32_mul(v___x_1569_, v___x_1575_);
v___y_1547_ = v___y_1562_;
v___y_1548_ = v___x_1576_;
goto v___jp_1546_;
}
}
v___jp_1577_:
{
uint32_t v___x_1579_; uint32_t v_a_1580_; uint32_t v___x_1581_; uint32_t v___x_1582_; uint32_t v___x_1583_; uint8_t v___x_1584_; 
v___x_1579_ = 2147483647;
v_a_1580_ = lean_uint32_land(v___y_1239_, v___x_1579_);
v___x_1581_ = 201326591;
v___x_1582_ = 1;
v___x_1583_ = lean_uint32_sub(v_a_1580_, v___x_1582_);
v___x_1584_ = lean_uint32_dec_le(v___x_1581_, v___x_1583_);
if (v___x_1584_ == 0)
{
v___y_1562_ = v___y_1578_;
v___y_1563_ = v___x_1584_;
goto v___jp_1561_;
}
else
{
uint32_t v___x_1585_; uint8_t v___x_1586_; 
v___x_1585_ = 2139095040;
v___x_1586_ = lean_uint32_dec_lt(v_a_1580_, v___x_1585_);
v___y_1562_ = v___y_1578_;
v___y_1563_ = v___x_1586_;
goto v___jp_1561_;
}
}
v___jp_1587_:
{
if (v___y_1589_ == 0)
{
float v___x_1590_; 
v___x_1590_ = lean_float32_of_bits(v___y_1238_);
v___y_1578_ = v___x_1590_;
goto v___jp_1577_;
}
else
{
uint32_t v___x_1591_; uint32_t v___x_1592_; uint32_t v___x_1593_; float v___x_1594_; lean_object* v___x_1595_; uint32_t v___x_1596_; uint32_t v___x_1597_; lean_object* v___x_1598_; lean_object* v___x_1599_; float v___x_1600_; float v___x_1601_; 
v___x_1591_ = 8388607;
v___x_1592_ = lean_uint32_land(v___y_1238_, v___x_1591_);
v___x_1593_ = lean_uint32_lor(v___x_1592_, v___y_1588_);
v___x_1594_ = lean_uint32_to_float32(v___x_1593_);
v___x_1595_ = lp_competition_R2W01b_scaleTable;
v___x_1596_ = 23;
v___x_1597_ = lean_uint32_shift_right(v___y_1238_, v___x_1596_);
v___x_1598_ = lean_uint32_to_nat(v___x_1597_);
v___x_1599_ = lean_array_fget_borrowed(v___x_1595_, v___x_1598_);
lean_dec(v___x_1598_);
v___x_1600_ = lean_unbox_float32(v___x_1599_);
v___x_1601_ = lean_float32_mul(v___x_1594_, v___x_1600_);
v___y_1578_ = v___x_1601_;
goto v___jp_1577_;
}
}
v___jp_1602_:
{
lean_object* v___x_1603_; lean_object* v___x_1604_; lean_object* v___x_1605_; uint32_t v___x_1606_; 
v___x_1603_ = lean_uint32_to_nat(v___y_1238_);
v___x_1604_ = lean_uint32_to_nat(v___y_1239_);
v___x_1605_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1603_, v___x_1604_);
v___x_1606_ = lean_uint32_of_nat(v___x_1605_);
lean_dec(v___x_1605_);
return v___x_1606_;
}
v___jp_1607_:
{
if (v___y_1608_ == 0)
{
goto v___jp_1602_;
}
else
{
uint32_t v___x_1609_; uint32_t v___x_1610_; 
v___x_1609_ = 4194304;
v___x_1610_ = lean_uint32_lor(v___y_1239_, v___x_1609_);
return v___x_1610_;
}
}
v___jp_1611_:
{
uint32_t v___x_1612_; uint32_t v___x_1613_; uint32_t v___x_1614_; uint32_t v___x_1615_; uint8_t v___x_1616_; 
v___x_1612_ = 23;
v___x_1613_ = lean_uint32_shift_right(v___y_1239_, v___x_1612_);
v___x_1614_ = 255;
v___x_1615_ = lean_uint32_land(v___x_1613_, v___x_1614_);
v___x_1616_ = lean_uint32_dec_eq(v___x_1615_, v___x_1614_);
if (v___x_1616_ == 0)
{
v___y_1608_ = v___x_1616_;
goto v___jp_1607_;
}
else
{
uint32_t v___x_1617_; uint32_t v___x_1618_; uint32_t v___x_1619_; uint8_t v___x_1620_; 
v___x_1617_ = 8388607;
v___x_1618_ = lean_uint32_land(v___y_1239_, v___x_1617_);
v___x_1619_ = 0;
v___x_1620_ = lean_uint32_dec_eq(v___x_1618_, v___x_1619_);
if (v___x_1620_ == 0)
{
v___y_1608_ = v___x_1616_;
goto v___jp_1607_;
}
else
{
goto v___jp_1602_;
}
}
}
v___jp_1621_:
{
if (v___y_1622_ == 0)
{
goto v___jp_1611_;
}
else
{
uint32_t v___x_1623_; uint32_t v___x_1624_; 
v___x_1623_ = 4194304;
v___x_1624_ = lean_uint32_lor(v___y_1238_, v___x_1623_);
return v___x_1624_;
}
}
v___jp_1625_:
{
uint32_t v___x_1626_; uint32_t v___x_1627_; uint32_t v___x_1628_; uint32_t v___x_1629_; uint8_t v___x_1630_; 
v___x_1626_ = 23;
v___x_1627_ = lean_uint32_shift_right(v___y_1238_, v___x_1626_);
v___x_1628_ = 255;
v___x_1629_ = lean_uint32_land(v___x_1627_, v___x_1628_);
v___x_1630_ = lean_uint32_dec_eq(v___x_1629_, v___x_1628_);
if (v___x_1630_ == 0)
{
v___y_1622_ = v___x_1630_;
goto v___jp_1621_;
}
else
{
uint32_t v___x_1631_; uint32_t v___x_1632_; uint32_t v___x_1633_; uint8_t v___x_1634_; 
v___x_1631_ = 8388607;
v___x_1632_ = lean_uint32_land(v___y_1238_, v___x_1631_);
v___x_1633_ = 0;
v___x_1634_ = lean_uint32_dec_eq(v___x_1632_, v___x_1633_);
if (v___x_1634_ == 0)
{
v___y_1622_ = v___x_1630_;
goto v___jp_1621_;
}
else
{
goto v___jp_1611_;
}
}
}
v___jp_1635_:
{
if (v___y_1636_ == 0)
{
goto v___jp_1625_;
}
else
{
uint32_t v___x_1637_; uint32_t v___x_1638_; uint32_t v___x_1639_; uint8_t v___x_1640_; 
v___x_1637_ = 4194304;
v___x_1638_ = lean_uint32_land(v___y_1239_, v___x_1637_);
v___x_1639_ = 0;
v___x_1640_ = lean_uint32_dec_eq(v___x_1638_, v___x_1639_);
if (v___x_1640_ == 0)
{
goto v___jp_1625_;
}
else
{
uint32_t v___x_1641_; 
v___x_1641_ = lean_uint32_lor(v___y_1239_, v___x_1637_);
return v___x_1641_;
}
}
}
v___jp_1642_:
{
uint32_t v___x_1643_; uint32_t v___x_1644_; uint32_t v___x_1645_; uint32_t v___x_1646_; uint8_t v___x_1647_; 
v___x_1643_ = 23;
v___x_1644_ = lean_uint32_shift_right(v___y_1239_, v___x_1643_);
v___x_1645_ = 255;
v___x_1646_ = lean_uint32_land(v___x_1644_, v___x_1645_);
v___x_1647_ = lean_uint32_dec_eq(v___x_1646_, v___x_1645_);
if (v___x_1647_ == 0)
{
v___y_1636_ = v___x_1647_;
goto v___jp_1635_;
}
else
{
uint32_t v___x_1648_; uint32_t v___x_1649_; uint32_t v___x_1650_; uint8_t v___x_1651_; 
v___x_1648_ = 8388607;
v___x_1649_ = lean_uint32_land(v___y_1239_, v___x_1648_);
v___x_1650_ = 0;
v___x_1651_ = lean_uint32_dec_eq(v___x_1649_, v___x_1650_);
if (v___x_1651_ == 0)
{
v___y_1636_ = v___x_1647_;
goto v___jp_1635_;
}
else
{
goto v___jp_1625_;
}
}
}
v___jp_1652_:
{
if (v___y_1653_ == 0)
{
goto v___jp_1642_;
}
else
{
uint32_t v___x_1654_; uint32_t v___x_1655_; uint32_t v___x_1656_; uint8_t v___x_1657_; 
v___x_1654_ = 4194304;
v___x_1655_ = lean_uint32_land(v___y_1238_, v___x_1654_);
v___x_1656_ = 0;
v___x_1657_ = lean_uint32_dec_eq(v___x_1655_, v___x_1656_);
if (v___x_1657_ == 0)
{
goto v___jp_1642_;
}
else
{
uint32_t v___x_1658_; 
v___x_1658_ = lean_uint32_lor(v___y_1238_, v___x_1654_);
return v___x_1658_;
}
}
}
v___jp_1659_:
{
float v_result_1662_; uint8_t v___x_1663_; 
v_result_1662_ = lean_float32_add(v___y_1660_, v___y_1661_);
v___x_1663_ = lean_float32_beq(v_result_1662_, v_result_1662_);
if (v___x_1663_ == 0)
{
uint32_t v___x_1664_; uint32_t v___x_1665_; uint32_t v___x_1666_; uint32_t v___x_1667_; uint8_t v___x_1668_; 
v___x_1664_ = 23;
v___x_1665_ = lean_uint32_shift_right(v___y_1238_, v___x_1664_);
v___x_1666_ = 255;
v___x_1667_ = lean_uint32_land(v___x_1665_, v___x_1666_);
v___x_1668_ = lean_uint32_dec_eq(v___x_1667_, v___x_1666_);
if (v___x_1668_ == 0)
{
v___y_1653_ = v___x_1668_;
goto v___jp_1652_;
}
else
{
uint32_t v___x_1669_; uint32_t v___x_1670_; uint32_t v___x_1671_; uint8_t v___x_1672_; 
v___x_1669_ = 8388607;
v___x_1670_ = lean_uint32_land(v___y_1238_, v___x_1669_);
v___x_1671_ = 0;
v___x_1672_ = lean_uint32_dec_eq(v___x_1670_, v___x_1671_);
if (v___x_1672_ == 0)
{
v___y_1653_ = v___x_1668_;
goto v___jp_1652_;
}
else
{
goto v___jp_1642_;
}
}
}
else
{
uint32_t v___x_1673_; 
v___x_1673_ = lean_float32_to_bits(v_result_1662_);
return v___x_1673_;
}
}
v___jp_1674_:
{
if (v___y_1676_ == 0)
{
float v___x_1677_; 
v___x_1677_ = lean_float32_of_bits(v___y_1239_);
v___y_1660_ = v___y_1675_;
v___y_1661_ = v___x_1677_;
goto v___jp_1659_;
}
else
{
uint32_t v___x_1678_; uint32_t v___x_1679_; uint32_t v___x_1680_; uint32_t v___x_1681_; float v___x_1682_; lean_object* v___x_1683_; uint32_t v___x_1684_; uint32_t v___x_1685_; lean_object* v___x_1686_; lean_object* v___x_1687_; float v___x_1688_; float v___x_1689_; 
v___x_1678_ = 8388607;
v___x_1679_ = lean_uint32_land(v___y_1239_, v___x_1678_);
v___x_1680_ = 8388608;
v___x_1681_ = lean_uint32_lor(v___x_1679_, v___x_1680_);
v___x_1682_ = lean_uint32_to_float32(v___x_1681_);
v___x_1683_ = lp_competition_R2W01b_scaleTable;
v___x_1684_ = 23;
v___x_1685_ = lean_uint32_shift_right(v___y_1239_, v___x_1684_);
v___x_1686_ = lean_uint32_to_nat(v___x_1685_);
v___x_1687_ = lean_array_fget_borrowed(v___x_1683_, v___x_1686_);
lean_dec(v___x_1686_);
v___x_1688_ = lean_unbox_float32(v___x_1687_);
v___x_1689_ = lean_float32_mul(v___x_1682_, v___x_1688_);
v___y_1660_ = v___y_1675_;
v___y_1661_ = v___x_1689_;
goto v___jp_1659_;
}
}
v___jp_1690_:
{
uint32_t v___x_1692_; uint32_t v_a_1693_; uint32_t v___x_1694_; uint32_t v___x_1695_; uint32_t v___x_1696_; uint8_t v___x_1697_; 
v___x_1692_ = 2147483647;
v_a_1693_ = lean_uint32_land(v___y_1239_, v___x_1692_);
v___x_1694_ = 201326591;
v___x_1695_ = 1;
v___x_1696_ = lean_uint32_sub(v_a_1693_, v___x_1695_);
v___x_1697_ = lean_uint32_dec_le(v___x_1694_, v___x_1696_);
if (v___x_1697_ == 0)
{
v___y_1675_ = v___y_1691_;
v___y_1676_ = v___x_1697_;
goto v___jp_1674_;
}
else
{
uint32_t v___x_1698_; uint8_t v___x_1699_; 
v___x_1698_ = 2139095040;
v___x_1699_ = lean_uint32_dec_lt(v_a_1693_, v___x_1698_);
v___y_1675_ = v___y_1691_;
v___y_1676_ = v___x_1699_;
goto v___jp_1674_;
}
}
v___jp_1700_:
{
if (v___y_1703_ == 0)
{
float v___x_1704_; 
v___x_1704_ = lean_float32_of_bits(v___y_1238_);
v___y_1691_ = v___x_1704_;
goto v___jp_1690_;
}
else
{
uint32_t v___x_1705_; uint32_t v___x_1706_; uint32_t v___x_1707_; float v___x_1708_; lean_object* v___x_1709_; uint32_t v___x_1710_; lean_object* v___x_1711_; lean_object* v___x_1712_; float v___x_1713_; float v___x_1714_; 
v___x_1705_ = 8388607;
v___x_1706_ = lean_uint32_land(v___y_1238_, v___x_1705_);
v___x_1707_ = lean_uint32_lor(v___x_1706_, v___y_1702_);
v___x_1708_ = lean_uint32_to_float32(v___x_1707_);
v___x_1709_ = lp_competition_R2W01b_scaleTable;
v___x_1710_ = lean_uint32_shift_right(v___y_1238_, v___y_1701_);
v___x_1711_ = lean_uint32_to_nat(v___x_1710_);
v___x_1712_ = lean_array_fget_borrowed(v___x_1709_, v___x_1711_);
lean_dec(v___x_1711_);
v___x_1713_ = lean_unbox_float32(v___x_1712_);
v___x_1714_ = lean_float32_mul(v___x_1708_, v___x_1713_);
v___y_1691_ = v___x_1714_;
goto v___jp_1690_;
}
}
v___jp_1715_:
{
uint32_t v___x_1722_; uint32_t v___x_1723_; uint32_t v___x_1724_; uint32_t v___x_1725_; uint32_t v_e_1726_; uint32_t v___x_1727_; uint32_t v___x_1728_; uint32_t v___x_1729_; uint8_t v___x_1730_; 
v___x_1722_ = lean_uint32_shift_right(v___y_1721_, v___y_1718_);
v___x_1723_ = lean_uint32_land(v___x_1722_, v___y_1720_);
v___x_1724_ = lean_uint32_add(v___y_1716_, v___x_1723_);
v___x_1725_ = 150;
v_e_1726_ = lean_uint32_sub(v___x_1724_, v___x_1725_);
v___x_1727_ = 1;
v___x_1728_ = lean_uint32_sub(v_e_1726_, v___x_1727_);
v___x_1729_ = 253;
v___x_1730_ = lean_uint32_dec_le(v___x_1728_, v___x_1729_);
if (v___x_1730_ == 0)
{
uint32_t v___x_1731_; uint32_t v_a_1732_; uint32_t v___x_1733_; uint32_t v___x_1734_; uint8_t v___x_1735_; 
v___x_1731_ = 2147483647;
v_a_1732_ = lean_uint32_land(v___y_1238_, v___x_1731_);
v___x_1733_ = 201326591;
v___x_1734_ = lean_uint32_sub(v_a_1732_, v___x_1727_);
v___x_1735_ = lean_uint32_dec_le(v___x_1733_, v___x_1734_);
if (v___x_1735_ == 0)
{
v___y_1701_ = v___y_1718_;
v___y_1702_ = v___y_1719_;
v___y_1703_ = v___x_1735_;
goto v___jp_1700_;
}
else
{
uint32_t v___x_1736_; uint8_t v___x_1737_; 
v___x_1736_ = 2139095040;
v___x_1737_ = lean_uint32_dec_lt(v_a_1732_, v___x_1736_);
v___y_1701_ = v___y_1718_;
v___y_1702_ = v___y_1719_;
v___y_1703_ = v___x_1737_;
goto v___jp_1700_;
}
}
else
{
uint32_t v___x_1738_; uint32_t v___x_1739_; uint32_t v___x_1740_; uint32_t v___x_1741_; uint32_t v___x_1742_; uint8_t v___x_1743_; 
v___x_1738_ = 2147483648;
v___x_1739_ = lean_uint32_shift_right(v___y_1238_, v___y_1718_);
v___x_1740_ = lean_uint32_land(v___x_1739_, v___y_1720_);
v___x_1741_ = lean_uint32_shift_right(v___y_1239_, v___y_1718_);
v___x_1742_ = lean_uint32_land(v___x_1741_, v___y_1720_);
v___x_1743_ = lean_uint32_dec_lt(v___x_1740_, v___x_1742_);
if (v___x_1743_ == 0)
{
v___y_1253_ = v_e_1726_;
v___y_1254_ = v___x_1738_;
v___y_1255_ = v___y_1718_;
v___y_1256_ = v___y_1717_;
v___y_1257_ = v___y_1720_;
v___y_1258_ = v___y_1238_;
goto v___jp_1252_;
}
else
{
v___y_1253_ = v_e_1726_;
v___y_1254_ = v___x_1738_;
v___y_1255_ = v___y_1718_;
v___y_1256_ = v___y_1717_;
v___y_1257_ = v___y_1720_;
v___y_1258_ = v___y_1239_;
goto v___jp_1252_;
}
}
}
v___jp_1744_:
{
uint32_t v___x_1746_; uint8_t v___x_1747_; 
v___x_1746_ = 8388608;
v___x_1747_ = lean_uint32_dec_le(v___x_1746_, v___y_1745_);
if (v___x_1747_ == 0)
{
uint32_t v___x_1748_; uint32_t v_a_1749_; uint32_t v___x_1750_; uint32_t v___x_1751_; uint32_t v___x_1752_; uint8_t v___x_1753_; 
v___x_1748_ = 2147483647;
v_a_1749_ = lean_uint32_land(v___y_1238_, v___x_1748_);
v___x_1750_ = 201326591;
v___x_1751_ = 1;
v___x_1752_ = lean_uint32_sub(v_a_1749_, v___x_1751_);
v___x_1753_ = lean_uint32_dec_le(v___x_1750_, v___x_1752_);
if (v___x_1753_ == 0)
{
v___y_1588_ = v___x_1746_;
v___y_1589_ = v___x_1753_;
goto v___jp_1587_;
}
else
{
uint32_t v___x_1754_; uint8_t v___x_1755_; 
v___x_1754_ = 2139095040;
v___x_1755_ = lean_uint32_dec_lt(v_a_1749_, v___x_1754_);
v___y_1588_ = v___x_1746_;
v___y_1589_ = v___x_1755_;
goto v___jp_1587_;
}
}
else
{
float v___x_1756_; uint32_t v_mid_1757_; uint32_t v___x_1758_; uint32_t v___x_1759_; uint32_t v___x_1760_; uint32_t v___x_1761_; uint32_t v___x_1762_; uint32_t v___x_1763_; uint32_t v___x_1764_; uint32_t v___x_1765_; uint8_t v___x_1766_; 
v___x_1756_ = lean_uint32_to_float32(v___y_1745_);
v_mid_1757_ = lean_float32_to_bits(v___x_1756_);
v___x_1758_ = 23;
v___x_1759_ = lean_uint32_shift_right(v_mid_1757_, v___x_1758_);
v___x_1760_ = 255;
v___x_1761_ = lean_uint32_land(v___x_1759_, v___x_1760_);
v___x_1762_ = lean_uint32_shift_right(v___y_1238_, v___x_1758_);
v___x_1763_ = lean_uint32_land(v___x_1762_, v___x_1760_);
v___x_1764_ = lean_uint32_shift_right(v___y_1239_, v___x_1758_);
v___x_1765_ = lean_uint32_land(v___x_1764_, v___x_1760_);
v___x_1766_ = lean_uint32_dec_lt(v___x_1763_, v___x_1765_);
if (v___x_1766_ == 0)
{
v___y_1716_ = v___x_1761_;
v___y_1717_ = v_mid_1757_;
v___y_1718_ = v___x_1758_;
v___y_1719_ = v___x_1746_;
v___y_1720_ = v___x_1760_;
v___y_1721_ = v___y_1239_;
goto v___jp_1715_;
}
else
{
v___y_1716_ = v___x_1761_;
v___y_1717_ = v_mid_1757_;
v___y_1718_ = v___x_1758_;
v___y_1719_ = v___x_1746_;
v___y_1720_ = v___x_1760_;
v___y_1721_ = v___y_1238_;
goto v___jp_1715_;
}
}
}
v___jp_1767_:
{
if (v___y_1770_ == 0)
{
uint32_t v___x_1771_; 
v___x_1771_ = lean_uint32_sub(v___y_1769_, v___y_1768_);
v___y_1745_ = v___x_1771_;
goto v___jp_1744_;
}
else
{
uint32_t v___x_1772_; 
v___x_1772_ = lean_uint32_add(v___y_1769_, v___y_1768_);
v___y_1745_ = v___x_1772_;
goto v___jp_1744_;
}
}
v___jp_1773_:
{
uint32_t v___x_1778_; uint32_t v_right_1779_; uint32_t v___x_1780_; uint8_t v___x_1781_; uint8_t v___x_1782_; 
v___x_1778_ = lean_uint32_land(v___y_1777_, v___y_1776_);
v_right_1779_ = lean_uint32_lor(v___x_1778_, v___y_1774_);
v___x_1780_ = 2147483648;
v___x_1781_ = lean_uint32_dec_le(v___x_1780_, v___y_1238_);
v___x_1782_ = lean_uint32_dec_le(v___x_1780_, v___y_1239_);
if (v___x_1781_ == 0)
{
if (v___x_1782_ == 0)
{
uint32_t v___x_1783_; 
v___x_1783_ = lean_uint32_add(v___y_1775_, v_right_1779_);
v___y_1745_ = v___x_1783_;
goto v___jp_1744_;
}
else
{
v___y_1768_ = v_right_1779_;
v___y_1769_ = v___y_1775_;
v___y_1770_ = v___x_1781_;
goto v___jp_1767_;
}
}
else
{
v___y_1768_ = v_right_1779_;
v___y_1769_ = v___y_1775_;
v___y_1770_ = v___x_1782_;
goto v___jp_1767_;
}
}
v___jp_1784_:
{
uint32_t v___x_1792_; uint32_t v___x_1793_; uint32_t v___x_1794_; uint32_t v_left_1795_; uint32_t v___x_1796_; uint32_t v___x_1797_; uint32_t v___x_1798_; uint32_t v___x_1799_; uint8_t v___x_1800_; 
v___x_1792_ = lean_uint32_shift_right(v___y_1791_, v___y_1787_);
v___x_1793_ = lean_uint32_land(v___x_1792_, v___y_1789_);
v___x_1794_ = lean_uint32_sub(v___y_1790_, v___x_1793_);
v_left_1795_ = lean_uint32_shift_left(v___y_1786_, v___x_1794_);
v___x_1796_ = lean_uint32_shift_right(v___y_1238_, v___y_1787_);
v___x_1797_ = lean_uint32_land(v___x_1796_, v___y_1789_);
v___x_1798_ = lean_uint32_shift_right(v___y_1239_, v___y_1787_);
v___x_1799_ = lean_uint32_land(v___x_1798_, v___y_1789_);
v___x_1800_ = lean_uint32_dec_lt(v___x_1797_, v___x_1799_);
if (v___x_1800_ == 0)
{
v___y_1774_ = v___y_1785_;
v___y_1775_ = v_left_1795_;
v___y_1776_ = v___y_1788_;
v___y_1777_ = v___y_1239_;
goto v___jp_1773_;
}
else
{
v___y_1774_ = v___y_1785_;
v___y_1775_ = v_left_1795_;
v___y_1776_ = v___y_1788_;
v___y_1777_ = v___y_1238_;
goto v___jp_1773_;
}
}
v___jp_1801_:
{
uint32_t v___x_1806_; uint32_t v___x_1807_; uint32_t v___x_1808_; uint32_t v___x_1809_; uint32_t v___x_1810_; uint32_t v___x_1811_; uint32_t v___x_1812_; uint32_t v___x_1813_; uint8_t v___x_1814_; 
v___x_1806_ = 23;
v___x_1807_ = lean_uint32_shift_right(v___y_1805_, v___x_1806_);
v___x_1808_ = 255;
v___x_1809_ = lean_uint32_land(v___x_1807_, v___x_1808_);
v___x_1810_ = lean_uint32_shift_right(v___y_1238_, v___x_1806_);
v___x_1811_ = lean_uint32_land(v___x_1810_, v___x_1808_);
v___x_1812_ = lean_uint32_shift_right(v___y_1239_, v___x_1806_);
v___x_1813_ = lean_uint32_land(v___x_1812_, v___x_1808_);
v___x_1814_ = lean_uint32_dec_lt(v___x_1811_, v___x_1813_);
if (v___x_1814_ == 0)
{
v___y_1785_ = v___y_1802_;
v___y_1786_ = v___y_1803_;
v___y_1787_ = v___x_1806_;
v___y_1788_ = v___y_1804_;
v___y_1789_ = v___x_1808_;
v___y_1790_ = v___x_1809_;
v___y_1791_ = v___y_1239_;
goto v___jp_1784_;
}
else
{
v___y_1785_ = v___y_1802_;
v___y_1786_ = v___y_1803_;
v___y_1787_ = v___x_1806_;
v___y_1788_ = v___y_1804_;
v___y_1789_ = v___x_1808_;
v___y_1790_ = v___x_1809_;
v___y_1791_ = v___y_1238_;
goto v___jp_1784_;
}
}
v___jp_1815_:
{
uint32_t v___x_1817_; uint32_t v___x_1818_; uint32_t v___x_1819_; uint32_t v___x_1820_; uint32_t v___x_1821_; uint32_t v___x_1822_; uint32_t v___x_1823_; uint32_t v___x_1824_; uint32_t v___x_1825_; uint32_t v___x_1826_; uint8_t v___x_1827_; 
v___x_1817_ = 8388607;
v___x_1818_ = lean_uint32_land(v___y_1816_, v___x_1817_);
v___x_1819_ = 8388608;
v___x_1820_ = lean_uint32_lor(v___x_1818_, v___x_1819_);
v___x_1821_ = 23;
v___x_1822_ = lean_uint32_shift_right(v___y_1238_, v___x_1821_);
v___x_1823_ = 255;
v___x_1824_ = lean_uint32_land(v___x_1822_, v___x_1823_);
v___x_1825_ = lean_uint32_shift_right(v___y_1239_, v___x_1821_);
v___x_1826_ = lean_uint32_land(v___x_1825_, v___x_1823_);
v___x_1827_ = lean_uint32_dec_lt(v___x_1824_, v___x_1826_);
if (v___x_1827_ == 0)
{
v___y_1802_ = v___x_1819_;
v___y_1803_ = v___x_1820_;
v___y_1804_ = v___x_1817_;
v___y_1805_ = v___y_1238_;
goto v___jp_1801_;
}
else
{
v___y_1802_ = v___x_1819_;
v___y_1803_ = v___x_1820_;
v___y_1804_ = v___x_1817_;
v___y_1805_ = v___y_1239_;
goto v___jp_1801_;
}
}
v___jp_1828_:
{
uint32_t v___x_1829_; uint32_t v___x_1830_; uint32_t v___x_1831_; uint32_t v___x_1832_; uint32_t v___x_1833_; uint32_t v___x_1834_; uint8_t v___x_1835_; 
v___x_1829_ = 23;
v___x_1830_ = lean_uint32_shift_right(v___y_1238_, v___x_1829_);
v___x_1831_ = 255;
v___x_1832_ = lean_uint32_land(v___x_1830_, v___x_1831_);
v___x_1833_ = lean_uint32_shift_right(v___y_1239_, v___x_1829_);
v___x_1834_ = lean_uint32_land(v___x_1833_, v___x_1831_);
v___x_1835_ = lean_uint32_dec_lt(v___x_1832_, v___x_1834_);
if (v___x_1835_ == 0)
{
v___y_1816_ = v___y_1238_;
goto v___jp_1815_;
}
else
{
v___y_1816_ = v___y_1239_;
goto v___jp_1815_;
}
}
v___jp_1836_:
{
if (v___y_1837_ == 0)
{
uint32_t v___x_1838_; uint32_t v_a_1839_; uint32_t v___x_1840_; uint32_t v___x_1841_; uint32_t v___x_1842_; uint8_t v___x_1843_; 
v___x_1838_ = 2147483647;
v_a_1839_ = lean_uint32_land(v___y_1238_, v___x_1838_);
v___x_1840_ = 201326591;
v___x_1841_ = 1;
v___x_1842_ = lean_uint32_sub(v_a_1839_, v___x_1841_);
v___x_1843_ = lean_uint32_dec_le(v___x_1840_, v___x_1842_);
if (v___x_1843_ == 0)
{
v___y_1475_ = v___x_1843_;
goto v___jp_1474_;
}
else
{
uint32_t v___x_1844_; uint8_t v___x_1845_; 
v___x_1844_ = 2139095040;
v___x_1845_ = lean_uint32_dec_lt(v_a_1839_, v___x_1844_);
v___y_1475_ = v___x_1845_;
goto v___jp_1474_;
}
}
else
{
goto v___jp_1828_;
}
}
v___jp_1846_:
{
uint32_t v___x_1852_; uint32_t v___x_1853_; uint32_t v___x_1854_; uint8_t v___x_1855_; 
v___x_1852_ = lean_uint32_shift_right(v___y_1851_, v___y_1850_);
v___x_1853_ = lean_uint32_land(v___x_1852_, v___y_1849_);
v___x_1854_ = lean_uint32_sub(v___y_1848_, v___x_1853_);
v___x_1855_ = lean_uint32_dec_le(v___y_1847_, v___x_1854_);
v___y_1837_ = v___x_1855_;
goto v___jp_1836_;
}
v___jp_1856_:
{
uint32_t v___x_1859_; uint32_t v___x_1860_; uint32_t v___x_1861_; uint32_t v___x_1862_; uint32_t v___x_1863_; uint32_t v___x_1864_; uint32_t v___x_1865_; uint32_t v___x_1866_; uint8_t v___x_1867_; 
v___x_1859_ = 23;
v___x_1860_ = lean_uint32_shift_right(v___y_1858_, v___x_1859_);
v___x_1861_ = 255;
v___x_1862_ = lean_uint32_land(v___x_1860_, v___x_1861_);
v___x_1863_ = lean_uint32_shift_right(v___y_1238_, v___x_1859_);
v___x_1864_ = lean_uint32_land(v___x_1863_, v___x_1861_);
v___x_1865_ = lean_uint32_shift_right(v___y_1239_, v___x_1859_);
v___x_1866_ = lean_uint32_land(v___x_1865_, v___x_1861_);
v___x_1867_ = lean_uint32_dec_lt(v___x_1864_, v___x_1866_);
if (v___x_1867_ == 0)
{
v___y_1847_ = v___y_1857_;
v___y_1848_ = v___x_1862_;
v___y_1849_ = v___x_1861_;
v___y_1850_ = v___x_1859_;
v___y_1851_ = v___y_1239_;
goto v___jp_1846_;
}
else
{
v___y_1847_ = v___y_1857_;
v___y_1848_ = v___x_1862_;
v___y_1849_ = v___x_1861_;
v___y_1850_ = v___x_1859_;
v___y_1851_ = v___y_1238_;
goto v___jp_1846_;
}
}
v___jp_1868_:
{
if (v___y_1869_ == 0)
{
uint32_t v___x_1870_; uint32_t v___x_1871_; uint32_t v___x_1872_; uint32_t v___x_1873_; uint32_t v___x_1874_; uint32_t v___x_1875_; uint32_t v___x_1876_; uint8_t v___x_1877_; 
v___x_1870_ = 1;
v___x_1871_ = 23;
v___x_1872_ = lean_uint32_shift_right(v___y_1238_, v___x_1871_);
v___x_1873_ = 255;
v___x_1874_ = lean_uint32_land(v___x_1872_, v___x_1873_);
v___x_1875_ = lean_uint32_shift_right(v___y_1239_, v___x_1871_);
v___x_1876_ = lean_uint32_land(v___x_1875_, v___x_1873_);
v___x_1877_ = lean_uint32_dec_lt(v___x_1874_, v___x_1876_);
if (v___x_1877_ == 0)
{
v___y_1857_ = v___x_1870_;
v___y_1858_ = v___y_1238_;
goto v___jp_1856_;
}
else
{
v___y_1857_ = v___x_1870_;
v___y_1858_ = v___y_1239_;
goto v___jp_1856_;
}
}
else
{
goto v___jp_1828_;
}
}
v___jp_1878_:
{
uint32_t v___x_1883_; uint32_t v___x_1884_; uint32_t v___x_1885_; uint32_t v___x_1886_; uint8_t v___x_1887_; 
v___x_1883_ = lean_uint32_shift_right(v___y_1882_, v___y_1879_);
v___x_1884_ = lean_uint32_land(v___x_1883_, v___y_1880_);
v___x_1885_ = lean_uint32_sub(v___y_1881_, v___x_1884_);
v___x_1886_ = 7;
v___x_1887_ = lean_uint32_dec_le(v___x_1885_, v___x_1886_);
if (v___x_1887_ == 0)
{
v___y_1837_ = v___x_1887_;
goto v___jp_1836_;
}
else
{
uint32_t v___x_1888_; uint8_t v___x_1889_; uint8_t v___x_1890_; 
v___x_1888_ = 2147483648;
v___x_1889_ = lean_uint32_dec_le(v___x_1888_, v___y_1238_);
v___x_1890_ = lean_uint32_dec_le(v___x_1888_, v___y_1239_);
if (v___x_1889_ == 0)
{
if (v___x_1890_ == 0)
{
v___y_1837_ = v___x_1887_;
goto v___jp_1836_;
}
else
{
v___y_1869_ = v___x_1889_;
goto v___jp_1868_;
}
}
else
{
v___y_1869_ = v___x_1890_;
goto v___jp_1868_;
}
}
}
v___jp_1891_:
{
uint32_t v___x_1893_; uint32_t v___x_1894_; uint32_t v___x_1895_; uint32_t v___x_1896_; uint32_t v___x_1897_; uint32_t v___x_1898_; uint32_t v___x_1899_; uint32_t v___x_1900_; uint8_t v___x_1901_; 
v___x_1893_ = 23;
v___x_1894_ = lean_uint32_shift_right(v___y_1892_, v___x_1893_);
v___x_1895_ = 255;
v___x_1896_ = lean_uint32_land(v___x_1894_, v___x_1895_);
v___x_1897_ = lean_uint32_shift_right(v___y_1238_, v___x_1893_);
v___x_1898_ = lean_uint32_land(v___x_1897_, v___x_1895_);
v___x_1899_ = lean_uint32_shift_right(v___y_1239_, v___x_1893_);
v___x_1900_ = lean_uint32_land(v___x_1899_, v___x_1895_);
v___x_1901_ = lean_uint32_dec_lt(v___x_1898_, v___x_1900_);
if (v___x_1901_ == 0)
{
v___y_1879_ = v___x_1893_;
v___y_1880_ = v___x_1895_;
v___y_1881_ = v___x_1896_;
v___y_1882_ = v___y_1239_;
goto v___jp_1878_;
}
else
{
v___y_1879_ = v___x_1893_;
v___y_1880_ = v___x_1895_;
v___y_1881_ = v___x_1896_;
v___y_1882_ = v___y_1238_;
goto v___jp_1878_;
}
}
v___jp_1902_:
{
if (v___y_1903_ == 0)
{
uint32_t v___x_1904_; uint32_t v_a_1905_; uint32_t v___x_1906_; uint32_t v___x_1907_; uint32_t v___x_1908_; uint8_t v___x_1909_; 
v___x_1904_ = 2147483647;
v_a_1905_ = lean_uint32_land(v___y_1238_, v___x_1904_);
v___x_1906_ = 201326591;
v___x_1907_ = 1;
v___x_1908_ = lean_uint32_sub(v_a_1905_, v___x_1907_);
v___x_1909_ = lean_uint32_dec_le(v___x_1906_, v___x_1908_);
if (v___x_1909_ == 0)
{
v___y_1362_ = v___x_1909_;
goto v___jp_1361_;
}
else
{
uint32_t v___x_1910_; uint8_t v___x_1911_; 
v___x_1910_ = 2139095040;
v___x_1911_ = lean_uint32_dec_lt(v_a_1905_, v___x_1910_);
v___y_1362_ = v___x_1911_;
goto v___jp_1361_;
}
}
else
{
uint32_t v___x_1912_; uint32_t v___x_1913_; uint32_t v___x_1914_; uint32_t v___x_1915_; uint32_t v___x_1916_; uint32_t v___x_1917_; uint8_t v___x_1918_; 
v___x_1912_ = 23;
v___x_1913_ = lean_uint32_shift_right(v___y_1238_, v___x_1912_);
v___x_1914_ = 255;
v___x_1915_ = lean_uint32_land(v___x_1913_, v___x_1914_);
v___x_1916_ = lean_uint32_shift_right(v___y_1239_, v___x_1912_);
v___x_1917_ = lean_uint32_land(v___x_1916_, v___x_1914_);
v___x_1918_ = lean_uint32_dec_lt(v___x_1915_, v___x_1917_);
if (v___x_1918_ == 0)
{
v___y_1892_ = v___y_1238_;
goto v___jp_1891_;
}
else
{
v___y_1892_ = v___y_1239_;
goto v___jp_1891_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__2___boxed(lean_object* v___y_1931_, lean_object* v___y_1932_){
_start:
{
uint32_t v___y_11471__boxed_1933_; uint32_t v___y_11472__boxed_1934_; uint32_t v_res_1935_; lean_object* v_r_1936_; 
v___y_11471__boxed_1933_ = lean_unbox_uint32(v___y_1931_);
lean_dec(v___y_1931_);
v___y_11472__boxed_1934_ = lean_unbox_uint32(v___y_1932_);
lean_dec(v___y_1932_);
v_res_1935_ = lp_competition_main___lam__2(v___y_11471__boxed_1933_, v___y_11472__boxed_1934_);
v_r_1936_ = lean_box_uint32(v_res_1935_);
return v_r_1936_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_1937_, uint32_t v___y_1938_){
_start:
{
uint32_t v___y_1940_; uint32_t v___y_1944_; uint32_t v___y_1948_; uint32_t v___y_1949_; uint32_t v___y_1950_; uint8_t v___y_1954_; uint32_t v___y_1955_; uint64_t v___y_1956_; uint64_t v___y_1957_; uint32_t v___y_1969_; uint32_t v___y_1970_; uint32_t v___y_1971_; uint8_t v___y_1975_; uint32_t v___y_1976_; uint64_t v___y_1977_; uint64_t v___y_1978_; uint8_t v___y_1990_; uint8_t v___y_2006_; uint8_t v___y_2020_; uint8_t v___y_2037_; float v___y_2044_; float v___y_2045_; float v___y_2059_; uint8_t v___y_2060_; float v___y_2075_; uint32_t v___x_2084_; uint32_t v___x_2085_; uint8_t v___y_2087_; uint32_t v___x_2099_; uint32_t v___y_2101_; uint32_t v___y_2102_; uint32_t v___y_2103_; uint32_t v___y_2104_; uint8_t v___y_2111_; uint32_t v___y_2112_; uint32_t v___y_2113_; uint32_t v___y_2114_; uint8_t v___y_2118_; uint32_t v___y_2119_; uint64_t v___y_2120_; uint64_t v___y_2121_; uint64_t v___y_2122_; uint64_t v___y_2132_; uint8_t v___y_2133_; uint32_t v___y_2134_; uint8_t v___y_2135_; uint64_t v___y_2136_; uint64_t v___y_2137_; uint8_t v___y_2144_; uint32_t v___y_2145_; uint64_t v___y_2146_; uint64_t v___y_2147_; uint64_t v___y_2148_; uint8_t v___y_2154_; uint32_t v___y_2155_; uint64_t v___y_2156_; uint64_t v___y_2157_; uint64_t v___y_2158_; uint64_t v___y_2159_; uint8_t v___y_2214_; uint32_t v___y_2215_; uint64_t v___y_2216_; uint64_t v___y_2217_; uint64_t v___y_2218_; uint64_t v___y_2219_; uint64_t v___y_2220_; uint64_t v___y_2226_; uint8_t v___y_2227_; uint32_t v___y_2228_; uint64_t v___y_2229_; uint64_t v___y_2230_; uint64_t v___y_2231_; uint64_t v___y_2232_; uint64_t v___y_2233_; uint64_t v___y_2234_; uint8_t v___y_2239_; uint32_t v___y_2240_; uint64_t v___y_2241_; uint64_t v___y_2242_; uint64_t v___y_2243_; uint64_t v___y_2244_; uint64_t v___y_2245_; uint8_t v___y_2250_; uint32_t v___y_2251_; uint64_t v___y_2252_; uint64_t v___y_2253_; uint64_t v___y_2254_; uint64_t v___y_2255_; uint64_t v___y_2256_; uint64_t v___y_2257_; uint64_t v___y_2258_; uint8_t v___y_2263_; uint32_t v___y_2264_; uint64_t v___y_2265_; uint64_t v___y_2266_; uint64_t v___y_2267_; uint64_t v___y_2268_; uint64_t v___y_2269_; uint64_t v___y_2274_; uint64_t v___y_2275_; uint8_t v___y_2276_; uint32_t v___y_2277_; uint64_t v___y_2278_; uint64_t v___y_2279_; uint64_t v___y_2280_; uint64_t v___y_2281_; uint64_t v___y_2282_; uint8_t v___y_2287_; uint64_t v___y_2288_; uint32_t v___y_2289_; uint64_t v___y_2290_; uint64_t v___y_2291_; uint64_t v___y_2292_; uint64_t v___y_2293_; uint8_t v___y_2298_; uint32_t v___y_2299_; uint64_t v___y_2300_; uint64_t v___y_2301_; uint64_t v___y_2302_; uint64_t v___y_2303_; uint64_t v___y_2304_; uint64_t v___y_2305_; uint64_t v___y_2306_; uint8_t v___y_2311_; uint32_t v___y_2312_; uint64_t v___y_2313_; uint64_t v___y_2314_; uint64_t v___y_2315_; uint64_t v___y_2316_; uint64_t v___y_2317_; uint8_t v___y_2322_; uint64_t v___y_2323_; uint32_t v___y_2324_; uint64_t v___y_2325_; uint64_t v___y_2326_; uint64_t v___y_2327_; uint64_t v___y_2328_; uint8_t v___y_2332_; uint32_t v___y_2333_; uint64_t v___y_2334_; uint64_t v___y_2335_; uint8_t v___y_2344_; uint64_t v___y_2345_; uint32_t v___y_2346_; uint64_t v___y_2347_; uint64_t v___y_2348_; uint64_t v___y_2349_; uint32_t v_ex_2382_; uint32_t v___x_2383_; uint32_t v_ey_2384_; uint64_t v___y_2386_; uint8_t v___y_2387_; uint32_t v___y_2388_; uint64_t v___y_2389_; uint64_t v___y_2390_; uint8_t v___y_2397_; uint32_t v___y_2398_; uint64_t v___y_2399_; uint64_t v___y_2400_; uint8_t v___y_2407_; uint32_t v___y_2408_; uint32_t v___y_2409_; uint64_t v___y_2410_; uint8_t v___y_2418_; uint32_t v___x_2428_; uint32_t v___x_2429_; uint8_t v___x_2430_; uint8_t v___y_2432_; uint8_t v___y_2433_; uint8_t v___y_2435_; uint8_t v___y_2436_; uint8_t v___y_2437_; uint8_t v___y_2439_; uint8_t v___y_2440_; uint8_t v___y_2446_; 
v___x_2084_ = 23;
v___x_2085_ = lean_uint32_shift_right(v___y_1937_, v___x_2084_);
v___x_2099_ = 255;
v_ex_2382_ = lean_uint32_land(v___x_2085_, v___x_2099_);
v___x_2383_ = lean_uint32_shift_right(v___y_1938_, v___x_2084_);
v_ey_2384_ = lean_uint32_land(v___x_2383_, v___x_2099_);
v___x_2428_ = lean_uint32_add(v_ex_2382_, v_ey_2384_);
v___x_2429_ = 128;
v___x_2430_ = lean_uint32_dec_lt(v___x_2428_, v___x_2429_);
if (v___x_2430_ == 0)
{
uint32_t v___x_2455_; uint32_t v_a_2456_; uint32_t v___x_2457_; uint32_t v___x_2458_; uint32_t v___x_2459_; uint8_t v___x_2460_; 
v___x_2455_ = 2147483647;
v_a_2456_ = lean_uint32_land(v___y_1937_, v___x_2455_);
v___x_2457_ = 201326591;
v___x_2458_ = 1;
v___x_2459_ = lean_uint32_sub(v_a_2456_, v___x_2458_);
v___x_2460_ = lean_uint32_dec_le(v___x_2457_, v___x_2459_);
if (v___x_2460_ == 0)
{
v___y_2087_ = v___x_2460_;
goto v___jp_2086_;
}
else
{
uint32_t v___x_2461_; uint8_t v___x_2462_; 
v___x_2461_ = 2139095040;
v___x_2462_ = lean_uint32_dec_lt(v_a_2456_, v___x_2461_);
v___y_2087_ = v___x_2462_;
goto v___jp_2086_;
}
}
else
{
uint32_t v___x_2463_; uint32_t v___x_2464_; uint32_t v___x_2465_; uint8_t v___x_2466_; 
v___x_2463_ = 4278190080;
v___x_2464_ = 1;
v___x_2465_ = lean_uint32_shift_left(v___y_1937_, v___x_2464_);
v___x_2466_ = lean_uint32_dec_le(v___x_2463_, v___x_2465_);
if (v___x_2466_ == 0)
{
uint32_t v___x_2467_; uint8_t v___x_2468_; 
v___x_2467_ = lean_uint32_shift_left(v___y_1938_, v___x_2464_);
v___x_2468_ = lean_uint32_dec_le(v___x_2463_, v___x_2467_);
v___y_2446_ = v___x_2468_;
goto v___jp_2445_;
}
else
{
v___y_2446_ = v___x_2466_;
goto v___jp_2445_;
}
}
v___jp_1939_:
{
uint32_t v___x_1941_; uint32_t v___x_1942_; 
v___x_1941_ = 8388608;
v___x_1942_ = lean_uint32_lor(v___y_1940_, v___x_1941_);
return v___x_1942_;
}
v___jp_1943_:
{
uint32_t v___x_1945_; uint32_t v___x_1946_; 
v___x_1945_ = 8388608;
v___x_1946_ = lean_uint32_lor(v___y_1944_, v___x_1945_);
return v___x_1946_;
}
v___jp_1947_:
{
uint32_t v___x_1951_; uint32_t v___x_1952_; 
v___x_1951_ = lean_uint32_land(v___y_1949_, v___y_1948_);
v___x_1952_ = lean_uint32_lor(v___y_1950_, v___x_1951_);
return v___x_1952_;
}
v___jp_1953_:
{
uint8_t v___x_1958_; 
v___x_1958_ = lean_uint64_dec_eq(v___y_1957_, v___y_1956_);
if (v___x_1958_ == 0)
{
uint64_t v___x_1959_; uint8_t v___x_1960_; 
v___x_1959_ = 8388608ULL;
v___x_1960_ = lean_uint64_dec_eq(v___y_1957_, v___x_1959_);
if (v___x_1960_ == 0)
{
uint32_t v___x_1961_; 
v___x_1961_ = lean_uint64_to_uint32(v___y_1957_);
if (v___y_1954_ == 0)
{
uint32_t v___x_1962_; 
v___x_1962_ = 0;
v___y_1948_ = v___y_1955_;
v___y_1949_ = v___x_1961_;
v___y_1950_ = v___x_1962_;
goto v___jp_1947_;
}
else
{
uint32_t v___x_1963_; 
v___x_1963_ = 2147483648;
v___y_1948_ = v___y_1955_;
v___y_1949_ = v___x_1961_;
v___y_1950_ = v___x_1963_;
goto v___jp_1947_;
}
}
else
{
if (v___y_1954_ == 0)
{
uint32_t v___x_1964_; 
v___x_1964_ = 0;
v___y_1944_ = v___x_1964_;
goto v___jp_1943_;
}
else
{
uint32_t v___x_1965_; 
v___x_1965_ = 2147483648;
v___y_1944_ = v___x_1965_;
goto v___jp_1943_;
}
}
}
else
{
if (v___y_1954_ == 0)
{
uint32_t v___x_1966_; 
v___x_1966_ = 0;
return v___x_1966_;
}
else
{
uint32_t v___x_1967_; 
v___x_1967_ = 2147483648;
return v___x_1967_;
}
}
}
v___jp_1968_:
{
uint32_t v___x_1972_; uint32_t v___x_1973_; 
v___x_1972_ = lean_uint32_land(v___y_1970_, v___y_1969_);
v___x_1973_ = lean_uint32_lor(v___y_1971_, v___x_1972_);
return v___x_1973_;
}
v___jp_1974_:
{
uint8_t v___x_1979_; 
v___x_1979_ = lean_uint64_dec_eq(v___y_1978_, v___y_1977_);
if (v___x_1979_ == 0)
{
uint64_t v___x_1980_; uint8_t v___x_1981_; 
v___x_1980_ = 8388608ULL;
v___x_1981_ = lean_uint64_dec_eq(v___y_1978_, v___x_1980_);
if (v___x_1981_ == 0)
{
uint32_t v___x_1982_; 
v___x_1982_ = lean_uint64_to_uint32(v___y_1978_);
if (v___y_1975_ == 0)
{
uint32_t v___x_1983_; 
v___x_1983_ = 0;
v___y_1969_ = v___y_1976_;
v___y_1970_ = v___x_1982_;
v___y_1971_ = v___x_1983_;
goto v___jp_1968_;
}
else
{
uint32_t v___x_1984_; 
v___x_1984_ = 2147483648;
v___y_1969_ = v___y_1976_;
v___y_1970_ = v___x_1982_;
v___y_1971_ = v___x_1984_;
goto v___jp_1968_;
}
}
else
{
if (v___y_1975_ == 0)
{
uint32_t v___x_1985_; 
v___x_1985_ = 0;
v___y_1940_ = v___x_1985_;
goto v___jp_1939_;
}
else
{
uint32_t v___x_1986_; 
v___x_1986_ = 2147483648;
v___y_1940_ = v___x_1986_;
goto v___jp_1939_;
}
}
}
else
{
if (v___y_1975_ == 0)
{
uint32_t v___x_1987_; 
v___x_1987_ = 0;
return v___x_1987_;
}
else
{
uint32_t v___x_1988_; 
v___x_1988_ = 2147483648;
return v___x_1988_;
}
}
}
v___jp_1989_:
{
if (v___y_1990_ == 0)
{
uint32_t v___x_1991_; 
v___x_1991_ = lp_competition_Submission_FastMul_mul(v___y_1937_, v___y_1938_);
return v___x_1991_;
}
else
{
uint32_t v___x_1992_; uint32_t v___x_1993_; 
v___x_1992_ = 4194304;
v___x_1993_ = lean_uint32_lor(v___y_1938_, v___x_1992_);
return v___x_1993_;
}
}
v___jp_1994_:
{
uint32_t v___x_1995_; uint32_t v___x_1996_; uint32_t v___x_1997_; uint32_t v___x_1998_; uint8_t v___x_1999_; 
v___x_1995_ = 23;
v___x_1996_ = lean_uint32_shift_right(v___y_1938_, v___x_1995_);
v___x_1997_ = 255;
v___x_1998_ = lean_uint32_land(v___x_1996_, v___x_1997_);
v___x_1999_ = lean_uint32_dec_eq(v___x_1998_, v___x_1997_);
if (v___x_1999_ == 0)
{
v___y_1990_ = v___x_1999_;
goto v___jp_1989_;
}
else
{
uint32_t v___x_2000_; uint32_t v___x_2001_; uint32_t v___x_2002_; uint8_t v___x_2003_; 
v___x_2000_ = 8388607;
v___x_2001_ = lean_uint32_land(v___y_1938_, v___x_2000_);
v___x_2002_ = 0;
v___x_2003_ = lean_uint32_dec_eq(v___x_2001_, v___x_2002_);
if (v___x_2003_ == 0)
{
v___y_1990_ = v___x_1999_;
goto v___jp_1989_;
}
else
{
uint32_t v___x_2004_; 
v___x_2004_ = lp_competition_Submission_FastMul_mul(v___y_1937_, v___y_1938_);
return v___x_2004_;
}
}
}
v___jp_2005_:
{
if (v___y_2006_ == 0)
{
goto v___jp_1994_;
}
else
{
uint32_t v___x_2007_; uint32_t v___x_2008_; 
v___x_2007_ = 4194304;
v___x_2008_ = lean_uint32_lor(v___y_1937_, v___x_2007_);
return v___x_2008_;
}
}
v___jp_2009_:
{
uint32_t v___x_2010_; uint32_t v___x_2011_; uint32_t v___x_2012_; uint32_t v___x_2013_; uint8_t v___x_2014_; 
v___x_2010_ = 23;
v___x_2011_ = lean_uint32_shift_right(v___y_1937_, v___x_2010_);
v___x_2012_ = 255;
v___x_2013_ = lean_uint32_land(v___x_2011_, v___x_2012_);
v___x_2014_ = lean_uint32_dec_eq(v___x_2013_, v___x_2012_);
if (v___x_2014_ == 0)
{
v___y_2006_ = v___x_2014_;
goto v___jp_2005_;
}
else
{
uint32_t v___x_2015_; uint32_t v___x_2016_; uint32_t v___x_2017_; uint8_t v___x_2018_; 
v___x_2015_ = 8388607;
v___x_2016_ = lean_uint32_land(v___y_1937_, v___x_2015_);
v___x_2017_ = 0;
v___x_2018_ = lean_uint32_dec_eq(v___x_2016_, v___x_2017_);
if (v___x_2018_ == 0)
{
v___y_2006_ = v___x_2014_;
goto v___jp_2005_;
}
else
{
goto v___jp_1994_;
}
}
}
v___jp_2019_:
{
if (v___y_2020_ == 0)
{
goto v___jp_2009_;
}
else
{
uint32_t v___x_2021_; uint32_t v___x_2022_; uint32_t v___x_2023_; uint8_t v___x_2024_; 
v___x_2021_ = 4194304;
v___x_2022_ = lean_uint32_land(v___y_1938_, v___x_2021_);
v___x_2023_ = 0;
v___x_2024_ = lean_uint32_dec_eq(v___x_2022_, v___x_2023_);
if (v___x_2024_ == 0)
{
goto v___jp_2009_;
}
else
{
uint32_t v___x_2025_; 
v___x_2025_ = lean_uint32_lor(v___y_1938_, v___x_2021_);
return v___x_2025_;
}
}
}
v___jp_2026_:
{
uint32_t v___x_2027_; uint32_t v___x_2028_; uint32_t v___x_2029_; uint32_t v___x_2030_; uint8_t v___x_2031_; 
v___x_2027_ = 23;
v___x_2028_ = lean_uint32_shift_right(v___y_1938_, v___x_2027_);
v___x_2029_ = 255;
v___x_2030_ = lean_uint32_land(v___x_2028_, v___x_2029_);
v___x_2031_ = lean_uint32_dec_eq(v___x_2030_, v___x_2029_);
if (v___x_2031_ == 0)
{
v___y_2020_ = v___x_2031_;
goto v___jp_2019_;
}
else
{
uint32_t v___x_2032_; uint32_t v___x_2033_; uint32_t v___x_2034_; uint8_t v___x_2035_; 
v___x_2032_ = 8388607;
v___x_2033_ = lean_uint32_land(v___y_1938_, v___x_2032_);
v___x_2034_ = 0;
v___x_2035_ = lean_uint32_dec_eq(v___x_2033_, v___x_2034_);
if (v___x_2035_ == 0)
{
v___y_2020_ = v___x_2031_;
goto v___jp_2019_;
}
else
{
goto v___jp_2009_;
}
}
}
v___jp_2036_:
{
if (v___y_2037_ == 0)
{
goto v___jp_2026_;
}
else
{
uint32_t v___x_2038_; uint32_t v___x_2039_; uint32_t v___x_2040_; uint8_t v___x_2041_; 
v___x_2038_ = 4194304;
v___x_2039_ = lean_uint32_land(v___y_1937_, v___x_2038_);
v___x_2040_ = 0;
v___x_2041_ = lean_uint32_dec_eq(v___x_2039_, v___x_2040_);
if (v___x_2041_ == 0)
{
goto v___jp_2026_;
}
else
{
uint32_t v___x_2042_; 
v___x_2042_ = lean_uint32_lor(v___y_1937_, v___x_2038_);
return v___x_2042_;
}
}
}
v___jp_2043_:
{
float v_result_2046_; uint8_t v___x_2047_; 
v_result_2046_ = lean_float32_mul(v___y_2044_, v___y_2045_);
v___x_2047_ = lean_float32_beq(v_result_2046_, v_result_2046_);
if (v___x_2047_ == 0)
{
uint32_t v___x_2048_; uint32_t v___x_2049_; uint32_t v___x_2050_; uint32_t v___x_2051_; uint8_t v___x_2052_; 
v___x_2048_ = 23;
v___x_2049_ = lean_uint32_shift_right(v___y_1937_, v___x_2048_);
v___x_2050_ = 255;
v___x_2051_ = lean_uint32_land(v___x_2049_, v___x_2050_);
v___x_2052_ = lean_uint32_dec_eq(v___x_2051_, v___x_2050_);
if (v___x_2052_ == 0)
{
v___y_2037_ = v___x_2052_;
goto v___jp_2036_;
}
else
{
uint32_t v___x_2053_; uint32_t v___x_2054_; uint32_t v___x_2055_; uint8_t v___x_2056_; 
v___x_2053_ = 8388607;
v___x_2054_ = lean_uint32_land(v___y_1937_, v___x_2053_);
v___x_2055_ = 0;
v___x_2056_ = lean_uint32_dec_eq(v___x_2054_, v___x_2055_);
if (v___x_2056_ == 0)
{
v___y_2037_ = v___x_2052_;
goto v___jp_2036_;
}
else
{
goto v___jp_2026_;
}
}
}
else
{
uint32_t v___x_2057_; 
v___x_2057_ = lean_float32_to_bits(v_result_2046_);
return v___x_2057_;
}
}
v___jp_2058_:
{
if (v___y_2060_ == 0)
{
float v___x_2061_; 
v___x_2061_ = lean_float32_of_bits(v___y_1938_);
v___y_2044_ = v___y_2059_;
v___y_2045_ = v___x_2061_;
goto v___jp_2043_;
}
else
{
uint32_t v___x_2062_; uint32_t v___x_2063_; uint32_t v___x_2064_; uint32_t v___x_2065_; float v___x_2066_; lean_object* v___x_2067_; uint32_t v___x_2068_; uint32_t v___x_2069_; lean_object* v___x_2070_; lean_object* v___x_2071_; float v___x_2072_; float v___x_2073_; 
v___x_2062_ = 8388607;
v___x_2063_ = lean_uint32_land(v___y_1938_, v___x_2062_);
v___x_2064_ = 8388608;
v___x_2065_ = lean_uint32_lor(v___x_2063_, v___x_2064_);
v___x_2066_ = lean_uint32_to_float32(v___x_2065_);
v___x_2067_ = lp_competition_R2W01b_scaleTable;
v___x_2068_ = 23;
v___x_2069_ = lean_uint32_shift_right(v___y_1938_, v___x_2068_);
v___x_2070_ = lean_uint32_to_nat(v___x_2069_);
v___x_2071_ = lean_array_fget_borrowed(v___x_2067_, v___x_2070_);
lean_dec(v___x_2070_);
v___x_2072_ = lean_unbox_float32(v___x_2071_);
v___x_2073_ = lean_float32_mul(v___x_2066_, v___x_2072_);
v___y_2044_ = v___y_2059_;
v___y_2045_ = v___x_2073_;
goto v___jp_2043_;
}
}
v___jp_2074_:
{
uint32_t v___x_2076_; uint32_t v_a_2077_; uint32_t v___x_2078_; uint32_t v___x_2079_; uint32_t v___x_2080_; uint8_t v___x_2081_; 
v___x_2076_ = 2147483647;
v_a_2077_ = lean_uint32_land(v___y_1938_, v___x_2076_);
v___x_2078_ = 201326591;
v___x_2079_ = 1;
v___x_2080_ = lean_uint32_sub(v_a_2077_, v___x_2079_);
v___x_2081_ = lean_uint32_dec_le(v___x_2078_, v___x_2080_);
if (v___x_2081_ == 0)
{
v___y_2059_ = v___y_2075_;
v___y_2060_ = v___x_2081_;
goto v___jp_2058_;
}
else
{
uint32_t v___x_2082_; uint8_t v___x_2083_; 
v___x_2082_ = 2139095040;
v___x_2083_ = lean_uint32_dec_lt(v_a_2077_, v___x_2082_);
v___y_2059_ = v___y_2075_;
v___y_2060_ = v___x_2083_;
goto v___jp_2058_;
}
}
v___jp_2086_:
{
if (v___y_2087_ == 0)
{
float v___x_2088_; 
v___x_2088_ = lean_float32_of_bits(v___y_1937_);
v___y_2075_ = v___x_2088_;
goto v___jp_2074_;
}
else
{
uint32_t v___x_2089_; uint32_t v___x_2090_; uint32_t v___x_2091_; uint32_t v___x_2092_; float v___x_2093_; lean_object* v___x_2094_; lean_object* v___x_2095_; lean_object* v___x_2096_; float v___x_2097_; float v___x_2098_; 
v___x_2089_ = 8388607;
v___x_2090_ = lean_uint32_land(v___y_1937_, v___x_2089_);
v___x_2091_ = 8388608;
v___x_2092_ = lean_uint32_lor(v___x_2090_, v___x_2091_);
v___x_2093_ = lean_uint32_to_float32(v___x_2092_);
v___x_2094_ = lp_competition_R2W01b_scaleTable;
v___x_2095_ = lean_uint32_to_nat(v___x_2085_);
v___x_2096_ = lean_array_fget_borrowed(v___x_2094_, v___x_2095_);
lean_dec(v___x_2095_);
v___x_2097_ = lean_unbox_float32(v___x_2096_);
v___x_2098_ = lean_float32_mul(v___x_2093_, v___x_2097_);
v___y_2075_ = v___x_2098_;
goto v___jp_2074_;
}
}
v___jp_2100_:
{
uint32_t v___x_2105_; uint32_t v___x_2106_; uint32_t v___x_2107_; uint32_t v___x_2108_; uint32_t v___x_2109_; 
v___x_2105_ = lean_uint32_land(v___y_2102_, v___x_2099_);
v___x_2106_ = lean_uint32_shift_left(v___x_2105_, v___x_2084_);
v___x_2107_ = lean_uint32_lor(v___y_2104_, v___x_2106_);
v___x_2108_ = lean_uint32_land(v___y_2103_, v___y_2101_);
v___x_2109_ = lean_uint32_lor(v___x_2107_, v___x_2108_);
return v___x_2109_;
}
v___jp_2110_:
{
if (v___y_2111_ == 0)
{
uint32_t v___x_2115_; 
v___x_2115_ = 0;
v___y_2101_ = v___y_2112_;
v___y_2102_ = v___y_2113_;
v___y_2103_ = v___y_2114_;
v___y_2104_ = v___x_2115_;
goto v___jp_2100_;
}
else
{
uint32_t v___x_2116_; 
v___x_2116_ = 2147483648;
v___y_2101_ = v___y_2112_;
v___y_2102_ = v___y_2113_;
v___y_2103_ = v___y_2114_;
v___y_2104_ = v___x_2116_;
goto v___jp_2100_;
}
}
v___jp_2117_:
{
uint64_t v___x_2123_; uint64_t v_encodedExponent_2124_; uint32_t v___x_2125_; uint64_t v___x_2126_; uint8_t v___x_2127_; 
v___x_2123_ = 171ULL;
v_encodedExponent_2124_ = lean_uint64_sub(v___y_2120_, v___x_2123_);
v___x_2125_ = lean_uint64_to_uint32(v_encodedExponent_2124_);
v___x_2126_ = 8388608ULL;
v___x_2127_ = lean_uint64_dec_lt(v___y_2122_, v___x_2126_);
if (v___x_2127_ == 0)
{
uint64_t v___x_2128_; uint32_t v___x_2129_; 
v___x_2128_ = lean_uint64_sub(v___y_2122_, v___x_2126_);
v___x_2129_ = lean_uint64_to_uint32(v___x_2128_);
v___y_2111_ = v___y_2118_;
v___y_2112_ = v___y_2119_;
v___y_2113_ = v___x_2125_;
v___y_2114_ = v___x_2129_;
goto v___jp_2110_;
}
else
{
uint32_t v___x_2130_; 
v___x_2130_ = lean_uint64_to_uint32(v___y_2121_);
v___y_2111_ = v___y_2118_;
v___y_2112_ = v___y_2119_;
v___y_2113_ = v___x_2125_;
v___y_2114_ = v___x_2130_;
goto v___jp_2110_;
}
}
v___jp_2131_:
{
uint64_t v___x_2138_; uint8_t v___x_2139_; 
v___x_2138_ = 425ULL;
v___x_2139_ = lean_uint64_dec_lt(v___x_2138_, v___y_2137_);
if (v___x_2139_ == 0)
{
if (v___y_2135_ == 0)
{
v___y_2118_ = v___y_2133_;
v___y_2119_ = v___y_2134_;
v___y_2120_ = v___y_2137_;
v___y_2121_ = v___y_2136_;
v___y_2122_ = v___y_2132_;
goto v___jp_2117_;
}
else
{
uint64_t v___x_2140_; 
v___x_2140_ = 8388608ULL;
v___y_2118_ = v___y_2133_;
v___y_2119_ = v___y_2134_;
v___y_2120_ = v___y_2137_;
v___y_2121_ = v___y_2136_;
v___y_2122_ = v___x_2140_;
goto v___jp_2117_;
}
}
else
{
if (v___y_2133_ == 0)
{
uint32_t v___x_2141_; 
v___x_2141_ = 2139095040;
return v___x_2141_;
}
else
{
uint32_t v___x_2142_; 
v___x_2142_ = 4286578688;
return v___x_2142_;
}
}
}
v___jp_2143_:
{
uint64_t v___x_2149_; uint8_t v_carry_2150_; 
v___x_2149_ = 16777216ULL;
v_carry_2150_ = lean_uint64_dec_eq(v___y_2148_, v___x_2149_);
if (v_carry_2150_ == 0)
{
v___y_2132_ = v___y_2148_;
v___y_2133_ = v___y_2144_;
v___y_2134_ = v___y_2145_;
v___y_2135_ = v_carry_2150_;
v___y_2136_ = v___y_2147_;
v___y_2137_ = v___y_2146_;
goto v___jp_2131_;
}
else
{
uint64_t v___x_2151_; uint64_t v___x_2152_; 
v___x_2151_ = 1ULL;
v___x_2152_ = lean_uint64_add(v___y_2146_, v___x_2151_);
v___y_2132_ = v___y_2148_;
v___y_2133_ = v___y_2144_;
v___y_2134_ = v___y_2145_;
v___y_2135_ = v_carry_2150_;
v___y_2136_ = v___y_2147_;
v___y_2137_ = v___x_2152_;
goto v___jp_2131_;
}
}
v___jp_2153_:
{
uint64_t v_position_2160_; uint64_t v___x_2161_; uint8_t v___x_2162_; 
v_position_2160_ = lean_uint64_add(v___y_2159_, v___y_2156_);
v___x_2161_ = 172ULL;
v___x_2162_ = lean_uint64_dec_lt(v_position_2160_, v___x_2161_);
if (v___x_2162_ == 0)
{
uint64_t v___x_2163_; uint8_t v___x_2164_; 
v___x_2163_ = 23ULL;
v___x_2164_ = lean_uint64_dec_lt(v___y_2159_, v___x_2163_);
if (v___x_2164_ == 0)
{
uint64_t v___x_2165_; uint8_t v___x_2166_; 
v___x_2165_ = lean_uint64_sub(v___y_2159_, v___x_2163_);
v___x_2166_ = lean_uint64_dec_eq(v___x_2165_, v___y_2157_);
if (v___x_2166_ == 0)
{
uint64_t v___x_2167_; uint8_t v___x_2168_; 
v___x_2167_ = 64ULL;
v___x_2168_ = lean_uint64_dec_lt(v___x_2165_, v___x_2167_);
if (v___x_2168_ == 0)
{
uint8_t v___x_2169_; 
v___x_2169_ = lean_uint64_dec_eq(v___x_2165_, v___x_2167_);
if (v___x_2169_ == 0)
{
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v___y_2157_;
goto v___jp_2143_;
}
else
{
uint64_t v___x_2170_; uint8_t v___x_2171_; 
v___x_2170_ = 9223372036854775808ULL;
v___x_2171_ = lean_uint64_dec_lt(v___x_2170_, v___y_2158_);
if (v___x_2171_ == 0)
{
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v___y_2157_;
goto v___jp_2143_;
}
else
{
uint64_t v___x_2172_; 
v___x_2172_ = 1ULL;
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v___x_2172_;
goto v___jp_2143_;
}
}
}
else
{
uint64_t v_quotient_2173_; uint64_t v___x_2174_; uint64_t v___x_2175_; uint64_t v___x_2176_; uint64_t v_remainder_2177_; uint64_t v___x_2178_; uint64_t v_half_2179_; uint8_t v___x_2180_; 
v_quotient_2173_ = lean_uint64_shift_right(v___y_2158_, v___x_2165_);
v___x_2174_ = 1ULL;
v___x_2175_ = lean_uint64_shift_left(v___x_2174_, v___x_2165_);
v___x_2176_ = lean_uint64_sub(v___x_2175_, v___x_2174_);
v_remainder_2177_ = lean_uint64_land(v___y_2158_, v___x_2176_);
v___x_2178_ = lean_uint64_sub(v___x_2165_, v___x_2174_);
v_half_2179_ = lean_uint64_shift_left(v___x_2174_, v___x_2178_);
v___x_2180_ = lean_uint64_dec_lt(v_remainder_2177_, v_half_2179_);
if (v___x_2180_ == 0)
{
uint8_t v___x_2181_; 
v___x_2181_ = lean_uint64_dec_lt(v_half_2179_, v_remainder_2177_);
if (v___x_2181_ == 0)
{
uint64_t v___x_2182_; uint8_t v___x_2183_; 
v___x_2182_ = lean_uint64_land(v_quotient_2173_, v___x_2174_);
v___x_2183_ = lean_uint64_dec_eq(v___x_2182_, v___y_2157_);
if (v___x_2183_ == 0)
{
uint64_t v___x_2184_; 
v___x_2184_ = lean_uint64_add(v_quotient_2173_, v___x_2174_);
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v___x_2184_;
goto v___jp_2143_;
}
else
{
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v_quotient_2173_;
goto v___jp_2143_;
}
}
else
{
uint64_t v___x_2185_; 
v___x_2185_ = lean_uint64_add(v_quotient_2173_, v___x_2174_);
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v___x_2185_;
goto v___jp_2143_;
}
}
else
{
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v_quotient_2173_;
goto v___jp_2143_;
}
}
}
else
{
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v___y_2158_;
goto v___jp_2143_;
}
}
else
{
uint64_t v___x_2186_; uint64_t v___x_2187_; 
v___x_2186_ = lean_uint64_sub(v___x_2163_, v___y_2159_);
v___x_2187_ = lean_uint64_shift_left(v___y_2158_, v___x_2186_);
v___y_2144_ = v___y_2154_;
v___y_2145_ = v___y_2155_;
v___y_2146_ = v_position_2160_;
v___y_2147_ = v___y_2157_;
v___y_2148_ = v___x_2187_;
goto v___jp_2143_;
}
}
else
{
uint64_t v___x_2188_; uint8_t v___x_2189_; 
v___x_2188_ = 149ULL;
v___x_2189_ = lean_uint64_dec_lt(v___y_2156_, v___x_2188_);
if (v___x_2189_ == 0)
{
uint64_t v___x_2190_; uint64_t v___x_2191_; 
v___x_2190_ = lean_uint64_sub(v___y_2156_, v___x_2188_);
v___x_2191_ = lean_uint64_shift_left(v___y_2158_, v___x_2190_);
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v___x_2191_;
goto v___jp_1953_;
}
else
{
uint64_t v___x_2192_; uint8_t v___x_2193_; 
v___x_2192_ = lean_uint64_sub(v___x_2188_, v___y_2156_);
v___x_2193_ = lean_uint64_dec_eq(v___x_2192_, v___y_2157_);
if (v___x_2193_ == 0)
{
uint64_t v___x_2194_; uint8_t v___x_2195_; 
v___x_2194_ = 64ULL;
v___x_2195_ = lean_uint64_dec_lt(v___x_2192_, v___x_2194_);
if (v___x_2195_ == 0)
{
uint8_t v___x_2196_; 
v___x_2196_ = lean_uint64_dec_eq(v___x_2192_, v___x_2194_);
if (v___x_2196_ == 0)
{
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v___y_2157_;
goto v___jp_1953_;
}
else
{
uint64_t v___x_2197_; uint8_t v___x_2198_; 
v___x_2197_ = 9223372036854775808ULL;
v___x_2198_ = lean_uint64_dec_lt(v___x_2197_, v___y_2158_);
if (v___x_2198_ == 0)
{
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v___y_2157_;
goto v___jp_1953_;
}
else
{
uint64_t v___x_2199_; 
v___x_2199_ = 1ULL;
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v___x_2199_;
goto v___jp_1953_;
}
}
}
else
{
uint64_t v_quotient_2200_; uint64_t v___x_2201_; uint64_t v___x_2202_; uint64_t v___x_2203_; uint64_t v_remainder_2204_; uint64_t v___x_2205_; uint64_t v_half_2206_; uint8_t v___x_2207_; 
v_quotient_2200_ = lean_uint64_shift_right(v___y_2158_, v___x_2192_);
v___x_2201_ = 1ULL;
v___x_2202_ = lean_uint64_shift_left(v___x_2201_, v___x_2192_);
v___x_2203_ = lean_uint64_sub(v___x_2202_, v___x_2201_);
v_remainder_2204_ = lean_uint64_land(v___y_2158_, v___x_2203_);
v___x_2205_ = lean_uint64_sub(v___x_2192_, v___x_2201_);
v_half_2206_ = lean_uint64_shift_left(v___x_2201_, v___x_2205_);
v___x_2207_ = lean_uint64_dec_lt(v_remainder_2204_, v_half_2206_);
if (v___x_2207_ == 0)
{
uint8_t v___x_2208_; 
v___x_2208_ = lean_uint64_dec_lt(v_half_2206_, v_remainder_2204_);
if (v___x_2208_ == 0)
{
uint64_t v___x_2209_; uint8_t v___x_2210_; 
v___x_2209_ = lean_uint64_land(v_quotient_2200_, v___x_2201_);
v___x_2210_ = lean_uint64_dec_eq(v___x_2209_, v___y_2157_);
if (v___x_2210_ == 0)
{
uint64_t v___x_2211_; 
v___x_2211_ = lean_uint64_add(v_quotient_2200_, v___x_2201_);
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v___x_2211_;
goto v___jp_1953_;
}
else
{
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v_quotient_2200_;
goto v___jp_1953_;
}
}
else
{
uint64_t v___x_2212_; 
v___x_2212_ = lean_uint64_add(v_quotient_2200_, v___x_2201_);
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v___x_2212_;
goto v___jp_1953_;
}
}
else
{
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v_quotient_2200_;
goto v___jp_1953_;
}
}
}
else
{
v___y_1954_ = v___y_2154_;
v___y_1955_ = v___y_2155_;
v___y_1956_ = v___y_2157_;
v___y_1957_ = v___y_2158_;
goto v___jp_1953_;
}
}
}
}
v___jp_2213_:
{
uint64_t v___x_2221_; uint64_t v___x_2222_; uint8_t v___x_2223_; 
v___x_2221_ = 1ULL;
v___x_2222_ = lean_uint64_shift_right(v___y_2217_, v___x_2221_);
v___x_2223_ = lean_uint64_dec_eq(v___x_2222_, v___y_2218_);
if (v___x_2223_ == 0)
{
uint64_t v___x_2224_; 
v___x_2224_ = lean_uint64_add(v___y_2220_, v___x_2221_);
v___y_2154_ = v___y_2214_;
v___y_2155_ = v___y_2215_;
v___y_2156_ = v___y_2216_;
v___y_2157_ = v___y_2218_;
v___y_2158_ = v___y_2219_;
v___y_2159_ = v___x_2224_;
goto v___jp_2153_;
}
else
{
v___y_2154_ = v___y_2214_;
v___y_2155_ = v___y_2215_;
v___y_2156_ = v___y_2216_;
v___y_2157_ = v___y_2218_;
v___y_2158_ = v___y_2219_;
v___y_2159_ = v___y_2220_;
goto v___jp_2153_;
}
}
v___jp_2225_:
{
uint64_t v___x_2235_; uint8_t v___x_2236_; 
v___x_2235_ = lean_uint64_shift_right(v___y_2229_, v___y_2233_);
v___x_2236_ = lean_uint64_dec_eq(v___x_2235_, v___y_2231_);
if (v___x_2236_ == 0)
{
uint64_t v___x_2237_; 
v___x_2237_ = lean_uint64_add(v___y_2226_, v___y_2233_);
v___y_2214_ = v___y_2227_;
v___y_2215_ = v___y_2228_;
v___y_2216_ = v___y_2230_;
v___y_2217_ = v___y_2234_;
v___y_2218_ = v___y_2231_;
v___y_2219_ = v___y_2232_;
v___y_2220_ = v___x_2237_;
goto v___jp_2213_;
}
else
{
v___y_2214_ = v___y_2227_;
v___y_2215_ = v___y_2228_;
v___y_2216_ = v___y_2230_;
v___y_2217_ = v___y_2234_;
v___y_2218_ = v___y_2231_;
v___y_2219_ = v___y_2232_;
v___y_2220_ = v___y_2226_;
goto v___jp_2213_;
}
}
v___jp_2238_:
{
uint64_t v___x_2246_; uint64_t v___x_2247_; uint8_t v___x_2248_; 
v___x_2246_ = 2ULL;
v___x_2247_ = lean_uint64_shift_right(v___y_2241_, v___x_2246_);
v___x_2248_ = lean_uint64_dec_eq(v___x_2247_, v___y_2243_);
if (v___x_2248_ == 0)
{
v___y_2226_ = v___y_2245_;
v___y_2227_ = v___y_2239_;
v___y_2228_ = v___y_2240_;
v___y_2229_ = v___y_2241_;
v___y_2230_ = v___y_2242_;
v___y_2231_ = v___y_2243_;
v___y_2232_ = v___y_2244_;
v___y_2233_ = v___x_2246_;
v___y_2234_ = v___x_2247_;
goto v___jp_2225_;
}
else
{
v___y_2226_ = v___y_2245_;
v___y_2227_ = v___y_2239_;
v___y_2228_ = v___y_2240_;
v___y_2229_ = v___y_2241_;
v___y_2230_ = v___y_2242_;
v___y_2231_ = v___y_2243_;
v___y_2232_ = v___y_2244_;
v___y_2233_ = v___x_2246_;
v___y_2234_ = v___y_2241_;
goto v___jp_2225_;
}
}
v___jp_2249_:
{
uint64_t v___x_2259_; uint8_t v___x_2260_; 
v___x_2259_ = lean_uint64_shift_right(v___y_2257_, v___y_2252_);
v___x_2260_ = lean_uint64_dec_eq(v___x_2259_, v___y_2254_);
if (v___x_2260_ == 0)
{
uint64_t v___x_2261_; 
v___x_2261_ = lean_uint64_add(v___y_2256_, v___y_2252_);
v___y_2239_ = v___y_2250_;
v___y_2240_ = v___y_2251_;
v___y_2241_ = v___y_2258_;
v___y_2242_ = v___y_2253_;
v___y_2243_ = v___y_2254_;
v___y_2244_ = v___y_2255_;
v___y_2245_ = v___x_2261_;
goto v___jp_2238_;
}
else
{
v___y_2239_ = v___y_2250_;
v___y_2240_ = v___y_2251_;
v___y_2241_ = v___y_2258_;
v___y_2242_ = v___y_2253_;
v___y_2243_ = v___y_2254_;
v___y_2244_ = v___y_2255_;
v___y_2245_ = v___y_2256_;
goto v___jp_2238_;
}
}
v___jp_2262_:
{
uint64_t v___x_2270_; uint64_t v___x_2271_; uint8_t v___x_2272_; 
v___x_2270_ = 4ULL;
v___x_2271_ = lean_uint64_shift_right(v___y_2268_, v___x_2270_);
v___x_2272_ = lean_uint64_dec_eq(v___x_2271_, v___y_2266_);
if (v___x_2272_ == 0)
{
v___y_2250_ = v___y_2263_;
v___y_2251_ = v___y_2264_;
v___y_2252_ = v___x_2270_;
v___y_2253_ = v___y_2265_;
v___y_2254_ = v___y_2266_;
v___y_2255_ = v___y_2267_;
v___y_2256_ = v___y_2269_;
v___y_2257_ = v___y_2268_;
v___y_2258_ = v___x_2271_;
goto v___jp_2249_;
}
else
{
v___y_2250_ = v___y_2263_;
v___y_2251_ = v___y_2264_;
v___y_2252_ = v___x_2270_;
v___y_2253_ = v___y_2265_;
v___y_2254_ = v___y_2266_;
v___y_2255_ = v___y_2267_;
v___y_2256_ = v___y_2269_;
v___y_2257_ = v___y_2268_;
v___y_2258_ = v___y_2268_;
goto v___jp_2249_;
}
}
v___jp_2273_:
{
uint64_t v___x_2283_; uint8_t v___x_2284_; 
v___x_2283_ = lean_uint64_shift_right(v___y_2275_, v___y_2274_);
v___x_2284_ = lean_uint64_dec_eq(v___x_2283_, v___y_2279_);
if (v___x_2284_ == 0)
{
uint64_t v___x_2285_; 
v___x_2285_ = lean_uint64_add(v___y_2281_, v___y_2274_);
v___y_2263_ = v___y_2276_;
v___y_2264_ = v___y_2277_;
v___y_2265_ = v___y_2278_;
v___y_2266_ = v___y_2279_;
v___y_2267_ = v___y_2280_;
v___y_2268_ = v___y_2282_;
v___y_2269_ = v___x_2285_;
goto v___jp_2262_;
}
else
{
v___y_2263_ = v___y_2276_;
v___y_2264_ = v___y_2277_;
v___y_2265_ = v___y_2278_;
v___y_2266_ = v___y_2279_;
v___y_2267_ = v___y_2280_;
v___y_2268_ = v___y_2282_;
v___y_2269_ = v___y_2281_;
goto v___jp_2262_;
}
}
v___jp_2286_:
{
uint64_t v___x_2294_; uint64_t v___x_2295_; uint8_t v___x_2296_; 
v___x_2294_ = 8ULL;
v___x_2295_ = lean_uint64_shift_right(v___y_2288_, v___x_2294_);
v___x_2296_ = lean_uint64_dec_eq(v___x_2295_, v___y_2291_);
if (v___x_2296_ == 0)
{
v___y_2274_ = v___x_2294_;
v___y_2275_ = v___y_2288_;
v___y_2276_ = v___y_2287_;
v___y_2277_ = v___y_2289_;
v___y_2278_ = v___y_2290_;
v___y_2279_ = v___y_2291_;
v___y_2280_ = v___y_2292_;
v___y_2281_ = v___y_2293_;
v___y_2282_ = v___x_2295_;
goto v___jp_2273_;
}
else
{
v___y_2274_ = v___x_2294_;
v___y_2275_ = v___y_2288_;
v___y_2276_ = v___y_2287_;
v___y_2277_ = v___y_2289_;
v___y_2278_ = v___y_2290_;
v___y_2279_ = v___y_2291_;
v___y_2280_ = v___y_2292_;
v___y_2281_ = v___y_2293_;
v___y_2282_ = v___y_2288_;
goto v___jp_2273_;
}
}
v___jp_2297_:
{
uint64_t v___x_2307_; uint8_t v___x_2308_; 
v___x_2307_ = lean_uint64_shift_right(v___y_2305_, v___y_2302_);
v___x_2308_ = lean_uint64_dec_eq(v___x_2307_, v___y_2303_);
if (v___x_2308_ == 0)
{
uint64_t v___x_2309_; 
v___x_2309_ = lean_uint64_add(v___y_2300_, v___y_2302_);
v___y_2287_ = v___y_2298_;
v___y_2288_ = v___y_2306_;
v___y_2289_ = v___y_2299_;
v___y_2290_ = v___y_2301_;
v___y_2291_ = v___y_2303_;
v___y_2292_ = v___y_2304_;
v___y_2293_ = v___x_2309_;
goto v___jp_2286_;
}
else
{
v___y_2287_ = v___y_2298_;
v___y_2288_ = v___y_2306_;
v___y_2289_ = v___y_2299_;
v___y_2290_ = v___y_2301_;
v___y_2291_ = v___y_2303_;
v___y_2292_ = v___y_2304_;
v___y_2293_ = v___y_2300_;
goto v___jp_2286_;
}
}
v___jp_2310_:
{
uint64_t v___x_2318_; uint64_t v___x_2319_; uint8_t v___x_2320_; 
v___x_2318_ = 16ULL;
v___x_2319_ = lean_uint64_shift_right(v___y_2316_, v___x_2318_);
v___x_2320_ = lean_uint64_dec_eq(v___x_2319_, v___y_2314_);
if (v___x_2320_ == 0)
{
v___y_2298_ = v___y_2311_;
v___y_2299_ = v___y_2312_;
v___y_2300_ = v___y_2317_;
v___y_2301_ = v___y_2313_;
v___y_2302_ = v___x_2318_;
v___y_2303_ = v___y_2314_;
v___y_2304_ = v___y_2315_;
v___y_2305_ = v___y_2316_;
v___y_2306_ = v___x_2319_;
goto v___jp_2297_;
}
else
{
v___y_2298_ = v___y_2311_;
v___y_2299_ = v___y_2312_;
v___y_2300_ = v___y_2317_;
v___y_2301_ = v___y_2313_;
v___y_2302_ = v___x_2318_;
v___y_2303_ = v___y_2314_;
v___y_2304_ = v___y_2315_;
v___y_2305_ = v___y_2316_;
v___y_2306_ = v___y_2316_;
goto v___jp_2297_;
}
}
v___jp_2321_:
{
uint64_t v___x_2329_; uint8_t v___x_2330_; 
v___x_2329_ = lean_uint64_shift_right(v___y_2327_, v___y_2323_);
v___x_2330_ = lean_uint64_dec_eq(v___x_2329_, v___y_2326_);
if (v___x_2330_ == 0)
{
v___y_2311_ = v___y_2322_;
v___y_2312_ = v___y_2324_;
v___y_2313_ = v___y_2325_;
v___y_2314_ = v___y_2326_;
v___y_2315_ = v___y_2327_;
v___y_2316_ = v___y_2328_;
v___y_2317_ = v___y_2323_;
goto v___jp_2310_;
}
else
{
v___y_2311_ = v___y_2322_;
v___y_2312_ = v___y_2324_;
v___y_2313_ = v___y_2325_;
v___y_2314_ = v___y_2326_;
v___y_2315_ = v___y_2327_;
v___y_2316_ = v___y_2328_;
v___y_2317_ = v___y_2326_;
goto v___jp_2310_;
}
}
v___jp_2331_:
{
uint64_t v___x_2336_; uint8_t v___x_2337_; 
v___x_2336_ = 0ULL;
v___x_2337_ = lean_uint64_dec_eq(v___y_2335_, v___x_2336_);
if (v___x_2337_ == 0)
{
uint64_t v___x_2338_; uint64_t v___x_2339_; uint8_t v___x_2340_; 
v___x_2338_ = 32ULL;
v___x_2339_ = lean_uint64_shift_right(v___y_2335_, v___x_2338_);
v___x_2340_ = lean_uint64_dec_eq(v___x_2339_, v___x_2336_);
if (v___x_2340_ == 0)
{
v___y_2322_ = v___y_2332_;
v___y_2323_ = v___x_2338_;
v___y_2324_ = v___y_2333_;
v___y_2325_ = v___y_2334_;
v___y_2326_ = v___x_2336_;
v___y_2327_ = v___y_2335_;
v___y_2328_ = v___x_2339_;
goto v___jp_2321_;
}
else
{
v___y_2322_ = v___y_2332_;
v___y_2323_ = v___x_2338_;
v___y_2324_ = v___y_2333_;
v___y_2325_ = v___y_2334_;
v___y_2326_ = v___x_2336_;
v___y_2327_ = v___y_2335_;
v___y_2328_ = v___y_2335_;
goto v___jp_2321_;
}
}
else
{
if (v___y_2332_ == 0)
{
uint32_t v___x_2341_; 
v___x_2341_ = 0;
return v___x_2341_;
}
else
{
uint32_t v___x_2342_; 
v___x_2342_ = 2147483648;
return v___x_2342_;
}
}
}
v___jp_2343_:
{
uint64_t v___x_2350_; uint64_t v___x_2351_; uint64_t v___x_2352_; uint8_t v___x_2353_; 
v___x_2350_ = lean_uint64_mul(v___y_2347_, v___y_2345_);
v___x_2351_ = lean_uint64_add(v___y_2348_, v___y_2349_);
v___x_2352_ = 281474976710656ULL;
v___x_2353_ = lean_uint64_dec_lt(v___x_2350_, v___x_2352_);
if (v___x_2353_ == 0)
{
v___y_2332_ = v___y_2344_;
v___y_2333_ = v___y_2346_;
v___y_2334_ = v___x_2351_;
v___y_2335_ = v___x_2350_;
goto v___jp_2331_;
}
else
{
uint64_t v___x_2354_; uint8_t v___x_2355_; 
v___x_2354_ = 123ULL;
v___x_2355_ = lean_uint64_dec_le(v___x_2351_, v___x_2354_);
if (v___x_2355_ == 0)
{
v___y_2332_ = v___y_2344_;
v___y_2333_ = v___y_2346_;
v___y_2334_ = v___x_2351_;
v___y_2335_ = v___x_2350_;
goto v___jp_2331_;
}
else
{
uint64_t v___x_2356_; uint8_t v___x_2357_; 
v___x_2356_ = 0ULL;
v___x_2357_ = lean_uint64_dec_eq(v___x_2350_, v___x_2356_);
if (v___x_2357_ == 0)
{
uint64_t v___x_2358_; uint64_t v___x_2359_; uint8_t v___x_2360_; 
v___x_2358_ = 149ULL;
v___x_2359_ = lean_uint64_sub(v___x_2358_, v___x_2351_);
v___x_2360_ = lean_uint64_dec_eq(v___x_2359_, v___x_2356_);
if (v___x_2360_ == 0)
{
uint64_t v___x_2361_; uint8_t v___x_2362_; 
v___x_2361_ = 64ULL;
v___x_2362_ = lean_uint64_dec_lt(v___x_2359_, v___x_2361_);
if (v___x_2362_ == 0)
{
uint8_t v___x_2363_; 
v___x_2363_ = lean_uint64_dec_eq(v___x_2359_, v___x_2361_);
if (v___x_2363_ == 0)
{
v___y_1975_ = v___y_2344_;
v___y_1976_ = v___y_2346_;
v___y_1977_ = v___x_2356_;
v___y_1978_ = v___x_2356_;
goto v___jp_1974_;
}
else
{
uint64_t v___x_2364_; uint8_t v___x_2365_; 
v___x_2364_ = 9223372036854775808ULL;
v___x_2365_ = lean_uint64_dec_lt(v___x_2364_, v___x_2350_);
if (v___x_2365_ == 0)
{
v___y_1975_ = v___y_2344_;
v___y_1976_ = v___y_2346_;
v___y_1977_ = v___x_2356_;
v___y_1978_ = v___x_2356_;
goto v___jp_1974_;
}
else
{
uint64_t v___x_2366_; 
v___x_2366_ = 1ULL;
v___y_1975_ = v___y_2344_;
v___y_1976_ = v___y_2346_;
v___y_1977_ = v___x_2356_;
v___y_1978_ = v___x_2366_;
goto v___jp_1974_;
}
}
}
else
{
uint64_t v_quotient_2367_; uint64_t v___x_2368_; uint64_t v___x_2369_; uint64_t v___x_2370_; uint64_t v_remainder_2371_; uint64_t v___x_2372_; uint64_t v_half_2373_; uint8_t v___x_2374_; 
v_quotient_2367_ = lean_uint64_shift_right(v___x_2350_, v___x_2359_);
v___x_2368_ = 1ULL;
v___x_2369_ = lean_uint64_shift_left(v___x_2368_, v___x_2359_);
v___x_2370_ = lean_uint64_sub(v___x_2369_, v___x_2368_);
v_remainder_2371_ = lean_uint64_land(v___x_2350_, v___x_2370_);
v___x_2372_ = lean_uint64_sub(v___x_2359_, v___x_2368_);
v_half_2373_ = lean_uint64_shift_left(v___x_2368_, v___x_2372_);
v___x_2374_ = lean_uint64_dec_lt(v_remainder_2371_, v_half_2373_);
if (v___x_2374_ == 0)
{
uint8_t v___x_2375_; 
v___x_2375_ = lean_uint64_dec_lt(v_half_2373_, v_remainder_2371_);
if (v___x_2375_ == 0)
{
uint64_t v___x_2376_; uint8_t v___x_2377_; 
v___x_2376_ = lean_uint64_land(v_quotient_2367_, v___x_2368_);
v___x_2377_ = lean_uint64_dec_eq(v___x_2376_, v___x_2356_);
if (v___x_2377_ == 0)
{
uint64_t v___x_2378_; 
v___x_2378_ = lean_uint64_add(v_quotient_2367_, v___x_2368_);
v___y_1975_ = v___y_2344_;
v___y_1976_ = v___y_2346_;
v___y_1977_ = v___x_2356_;
v___y_1978_ = v___x_2378_;
goto v___jp_1974_;
}
else
{
v___y_1975_ = v___y_2344_;
v___y_1976_ = v___y_2346_;
v___y_1977_ = v___x_2356_;
v___y_1978_ = v_quotient_2367_;
goto v___jp_1974_;
}
}
else
{
uint64_t v___x_2379_; 
v___x_2379_ = lean_uint64_add(v_quotient_2367_, v___x_2368_);
v___y_1975_ = v___y_2344_;
v___y_1976_ = v___y_2346_;
v___y_1977_ = v___x_2356_;
v___y_1978_ = v___x_2379_;
goto v___jp_1974_;
}
}
else
{
v___y_1975_ = v___y_2344_;
v___y_1976_ = v___y_2346_;
v___y_1977_ = v___x_2356_;
v___y_1978_ = v_quotient_2367_;
goto v___jp_1974_;
}
}
}
else
{
v___y_1975_ = v___y_2344_;
v___y_1976_ = v___y_2346_;
v___y_1977_ = v___x_2356_;
v___y_1978_ = v___x_2350_;
goto v___jp_1974_;
}
}
else
{
if (v___y_2344_ == 0)
{
uint32_t v___x_2380_; 
v___x_2380_ = 0;
return v___x_2380_;
}
else
{
uint32_t v___x_2381_; 
v___x_2381_ = 2147483648;
return v___x_2381_;
}
}
}
}
}
v___jp_2385_:
{
uint64_t v___x_2391_; uint64_t v___x_2392_; uint8_t v___x_2393_; 
v___x_2391_ = lean_uint32_to_uint64(v_ey_2384_);
v___x_2392_ = 0ULL;
v___x_2393_ = lean_uint64_dec_eq(v___x_2391_, v___x_2392_);
if (v___x_2393_ == 0)
{
uint64_t v___x_2394_; uint64_t v___x_2395_; 
v___x_2394_ = 1ULL;
v___x_2395_ = lean_uint64_sub(v___x_2391_, v___x_2394_);
v___y_2344_ = v___y_2387_;
v___y_2345_ = v___y_2386_;
v___y_2346_ = v___y_2388_;
v___y_2347_ = v___y_2389_;
v___y_2348_ = v___y_2390_;
v___y_2349_ = v___x_2395_;
goto v___jp_2343_;
}
else
{
v___y_2344_ = v___y_2387_;
v___y_2345_ = v___y_2386_;
v___y_2346_ = v___y_2388_;
v___y_2347_ = v___y_2389_;
v___y_2348_ = v___y_2390_;
v___y_2349_ = v___x_2392_;
goto v___jp_2343_;
}
}
v___jp_2396_:
{
uint64_t v___x_2401_; uint64_t v___x_2402_; uint8_t v___x_2403_; 
v___x_2401_ = lean_uint32_to_uint64(v_ex_2382_);
v___x_2402_ = 0ULL;
v___x_2403_ = lean_uint64_dec_eq(v___x_2401_, v___x_2402_);
if (v___x_2403_ == 0)
{
uint64_t v___x_2404_; uint64_t v___x_2405_; 
v___x_2404_ = 1ULL;
v___x_2405_ = lean_uint64_sub(v___x_2401_, v___x_2404_);
v___y_2386_ = v___y_2400_;
v___y_2387_ = v___y_2397_;
v___y_2388_ = v___y_2398_;
v___y_2389_ = v___y_2399_;
v___y_2390_ = v___x_2405_;
goto v___jp_2385_;
}
else
{
v___y_2386_ = v___y_2400_;
v___y_2387_ = v___y_2397_;
v___y_2388_ = v___y_2398_;
v___y_2389_ = v___y_2399_;
v___y_2390_ = v___x_2402_;
goto v___jp_2385_;
}
}
v___jp_2406_:
{
uint32_t v___x_2411_; uint8_t v___x_2412_; 
v___x_2411_ = 0;
v___x_2412_ = lean_uint32_dec_eq(v_ey_2384_, v___x_2411_);
if (v___x_2412_ == 0)
{
uint64_t v___x_2413_; uint64_t v___x_2414_; uint64_t v___x_2415_; 
v___x_2413_ = lean_uint32_to_uint64(v___y_2409_);
v___x_2414_ = 8388608ULL;
v___x_2415_ = lean_uint64_lor(v___x_2413_, v___x_2414_);
v___y_2397_ = v___y_2407_;
v___y_2398_ = v___y_2408_;
v___y_2399_ = v___y_2410_;
v___y_2400_ = v___x_2415_;
goto v___jp_2396_;
}
else
{
uint64_t v___x_2416_; 
v___x_2416_ = lean_uint32_to_uint64(v___y_2409_);
v___y_2397_ = v___y_2407_;
v___y_2398_ = v___y_2408_;
v___y_2399_ = v___y_2410_;
v___y_2400_ = v___x_2416_;
goto v___jp_2396_;
}
}
v___jp_2417_:
{
uint32_t v___x_2419_; uint32_t v_xFraction_2420_; uint32_t v_yFraction_2421_; uint32_t v___x_2422_; uint8_t v___x_2423_; 
v___x_2419_ = 8388607;
v_xFraction_2420_ = lean_uint32_land(v___y_1937_, v___x_2419_);
v_yFraction_2421_ = lean_uint32_land(v___y_1938_, v___x_2419_);
v___x_2422_ = 0;
v___x_2423_ = lean_uint32_dec_eq(v_ex_2382_, v___x_2422_);
if (v___x_2423_ == 0)
{
uint64_t v___x_2424_; uint64_t v___x_2425_; uint64_t v___x_2426_; 
v___x_2424_ = lean_uint32_to_uint64(v_xFraction_2420_);
v___x_2425_ = 8388608ULL;
v___x_2426_ = lean_uint64_lor(v___x_2424_, v___x_2425_);
v___y_2407_ = v___y_2418_;
v___y_2408_ = v___x_2419_;
v___y_2409_ = v_yFraction_2421_;
v___y_2410_ = v___x_2426_;
goto v___jp_2406_;
}
else
{
uint64_t v___x_2427_; 
v___x_2427_ = lean_uint32_to_uint64(v_xFraction_2420_);
v___y_2407_ = v___y_2418_;
v___y_2408_ = v___x_2419_;
v___y_2409_ = v_yFraction_2421_;
v___y_2410_ = v___x_2427_;
goto v___jp_2406_;
}
}
v___jp_2431_:
{
if (v___y_2433_ == 0)
{
v___y_2418_ = v___x_2430_;
goto v___jp_2417_;
}
else
{
v___y_2418_ = v___y_2432_;
goto v___jp_2417_;
}
}
v___jp_2434_:
{
if (v___y_2436_ == 0)
{
if (v___y_2437_ == 0)
{
v___y_2432_ = v___y_2435_;
v___y_2433_ = v___x_2430_;
goto v___jp_2431_;
}
else
{
v___y_2418_ = v___x_2430_;
goto v___jp_2417_;
}
}
else
{
v___y_2432_ = v___y_2435_;
v___y_2433_ = v___y_2437_;
goto v___jp_2431_;
}
}
v___jp_2438_:
{
uint32_t v___x_2441_; uint32_t v___x_2442_; uint32_t v___x_2443_; uint8_t v___x_2444_; 
v___x_2441_ = 2147483648;
v___x_2442_ = lean_uint32_land(v___y_1938_, v___x_2441_);
v___x_2443_ = 0;
v___x_2444_ = lean_uint32_dec_eq(v___x_2442_, v___x_2443_);
if (v___x_2444_ == 0)
{
v___y_2435_ = v___y_2439_;
v___y_2436_ = v___y_2440_;
v___y_2437_ = v___x_2430_;
goto v___jp_2434_;
}
else
{
v___y_2435_ = v___y_2439_;
v___y_2436_ = v___y_2440_;
v___y_2437_ = v___y_2439_;
goto v___jp_2434_;
}
}
v___jp_2445_:
{
if (v___y_2446_ == 0)
{
uint32_t v___x_2447_; uint32_t v___x_2448_; uint32_t v___x_2449_; uint8_t v___x_2450_; 
v___x_2447_ = 2147483648;
v___x_2448_ = lean_uint32_land(v___y_1937_, v___x_2447_);
v___x_2449_ = 0;
v___x_2450_ = lean_uint32_dec_eq(v___x_2448_, v___x_2449_);
if (v___x_2450_ == 0)
{
v___y_2439_ = v___y_2446_;
v___y_2440_ = v___x_2430_;
goto v___jp_2438_;
}
else
{
v___y_2439_ = v___y_2446_;
v___y_2440_ = v___y_2446_;
goto v___jp_2438_;
}
}
else
{
lean_object* v___x_2451_; lean_object* v___x_2452_; lean_object* v___x_2453_; uint32_t v___x_2454_; 
v___x_2451_ = lean_uint32_to_nat(v___y_1937_);
v___x_2452_ = lean_uint32_to_nat(v___y_1938_);
v___x_2453_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_2451_, v___x_2452_);
v___x_2454_ = lean_uint32_of_nat(v___x_2453_);
lean_dec(v___x_2453_);
return v___x_2454_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_2469_, lean_object* v___y_2470_){
_start:
{
uint32_t v___y_12827__boxed_2471_; uint32_t v___y_12828__boxed_2472_; uint32_t v_res_2473_; lean_object* v_r_2474_; 
v___y_12827__boxed_2471_ = lean_unbox_uint32(v___y_2469_);
lean_dec(v___y_2469_);
v___y_12828__boxed_2472_ = lean_unbox_uint32(v___y_2470_);
lean_dec(v___y_2470_);
v_res_2473_ = lp_competition_main___lam__3(v___y_12827__boxed_2471_, v___y_12828__boxed_2472_);
v_r_2474_ = lean_box_uint32(v_res_2473_);
return v_r_2474_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2483_; lean_object* v___x_2484_; 
v___x_2483_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_2484_ = lean_io_getenv(v___x_2483_);
if (lean_obj_tag(v___x_2484_) == 0)
{
lean_object* v___f_2485_; lean_object* v___f_2486_; lean_object* v___x_2487_; lean_object* v___x_2488_; lean_object* v___x_2489_; 
v___f_2485_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_2486_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_2487_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2488_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2489_ = lp_competition_Bench_runFull(v___f_2485_, v___f_2486_, v___x_2487_, v___x_2488_);
return v___x_2489_;
}
else
{
lean_object* v___f_2490_; lean_object* v___f_2491_; lean_object* v___x_2492_; lean_object* v___x_2493_; lean_object* v___x_2494_; 
lean_dec_ref_known(v___x_2484_, 1);
v___f_2490_ = ((lean_object*)(lp_competition_main___closed__5));
v___f_2491_ = ((lean_object*)(lp_competition_main___closed__6));
v___x_2492_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_2493_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_2494_ = lp_competition_Bench_Suite_run(v___f_2490_, v___f_2491_, v___x_2492_, v___x_2493_);
return v___x_2494_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_2495_){
_start:
{
lean_object* v_res_2496_; 
v_res_2496_ = _lean_main();
return v_res_2496_;
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
