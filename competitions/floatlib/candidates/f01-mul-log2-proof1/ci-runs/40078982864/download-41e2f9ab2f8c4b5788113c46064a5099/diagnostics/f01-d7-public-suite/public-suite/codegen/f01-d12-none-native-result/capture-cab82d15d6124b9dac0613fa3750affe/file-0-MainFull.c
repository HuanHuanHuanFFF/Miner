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
uint32_t lean_float32_to_bits(float);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
float lean_float32_add(float, float);
uint8_t lean_float32_beq(float, float);
float lean_float32_of_bits(uint32_t);
float lean_uint32_to_float32(uint32_t);
extern lean_object* lp_competition_R2W01b_scaleTable;
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
float v___y_4_; uint8_t v___y_5_; float v___y_10_; float v___y_22_; uint8_t v___y_23_; float v___y_27_; float v___y_38_; uint8_t v___y_39_; float v___y_46_; float v___y_57_; uint8_t v___y_58_; float v___y_65_; float v___y_66_; float v___y_80_; uint8_t v___y_81_; float v___y_96_; uint8_t v___y_106_; uint32_t v___x_120_; uint32_t v_a_121_; uint32_t v___x_122_; uint32_t v___x_123_; uint32_t v___x_124_; uint8_t v___x_125_; 
v___x_120_ = 2147483647;
v_a_121_ = lean_uint32_land(v___y_1_, v___x_120_);
v___x_122_ = 201326591;
v___x_123_ = 1;
v___x_124_ = lean_uint32_sub(v_a_121_, v___x_123_);
v___x_125_ = lean_uint32_dec_le(v___x_122_, v___x_124_);
if (v___x_125_ == 0)
{
v___y_106_ = v___x_125_;
goto v___jp_105_;
}
else
{
uint32_t v___x_126_; uint8_t v___x_127_; 
v___x_126_ = 2139095040;
v___x_127_ = lean_uint32_dec_lt(v_a_121_, v___x_126_);
v___y_106_ = v___x_127_;
goto v___jp_105_;
}
v___jp_3_:
{
if (v___y_5_ == 0)
{
uint32_t v___x_6_; 
v___x_6_ = lean_float32_to_bits(v___y_4_);
return v___x_6_;
}
else
{
uint32_t v___x_7_; uint32_t v___x_8_; 
v___x_7_ = 4194304;
v___x_8_ = lean_uint32_lor(v___y_2_, v___x_7_);
return v___x_8_;
}
}
v___jp_9_:
{
uint32_t v___x_11_; uint32_t v___x_12_; uint32_t v___x_13_; uint32_t v___x_14_; uint8_t v___x_15_; 
v___x_11_ = 23;
v___x_12_ = lean_uint32_shift_right(v___y_2_, v___x_11_);
v___x_13_ = 255;
v___x_14_ = lean_uint32_land(v___x_12_, v___x_13_);
v___x_15_ = lean_uint32_dec_eq(v___x_14_, v___x_13_);
if (v___x_15_ == 0)
{
v___y_4_ = v___y_10_;
v___y_5_ = v___x_15_;
goto v___jp_3_;
}
else
{
uint32_t v___x_16_; uint32_t v___x_17_; uint32_t v___x_18_; uint8_t v___x_19_; 
v___x_16_ = 8388607;
v___x_17_ = lean_uint32_land(v___y_2_, v___x_16_);
v___x_18_ = 0;
v___x_19_ = lean_uint32_dec_eq(v___x_17_, v___x_18_);
if (v___x_19_ == 0)
{
v___y_4_ = v___y_10_;
v___y_5_ = v___x_15_;
goto v___jp_3_;
}
else
{
uint32_t v___x_20_; 
v___x_20_ = lean_float32_to_bits(v___y_10_);
return v___x_20_;
}
}
}
v___jp_21_:
{
if (v___y_23_ == 0)
{
v___y_10_ = v___y_22_;
goto v___jp_9_;
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
uint32_t v___x_28_; uint32_t v___x_29_; uint32_t v___x_30_; uint32_t v___x_31_; uint8_t v___x_32_; 
v___x_28_ = 23;
v___x_29_ = lean_uint32_shift_right(v___y_1_, v___x_28_);
v___x_30_ = 255;
v___x_31_ = lean_uint32_land(v___x_29_, v___x_30_);
v___x_32_ = lean_uint32_dec_eq(v___x_31_, v___x_30_);
if (v___x_32_ == 0)
{
v___y_22_ = v___y_27_;
v___y_23_ = v___x_32_;
goto v___jp_21_;
}
else
{
uint32_t v___x_33_; uint32_t v___x_34_; uint32_t v___x_35_; uint8_t v___x_36_; 
v___x_33_ = 8388607;
v___x_34_ = lean_uint32_land(v___y_1_, v___x_33_);
v___x_35_ = 0;
v___x_36_ = lean_uint32_dec_eq(v___x_34_, v___x_35_);
if (v___x_36_ == 0)
{
v___y_22_ = v___y_27_;
v___y_23_ = v___x_32_;
goto v___jp_21_;
}
else
{
v___y_10_ = v___y_27_;
goto v___jp_9_;
}
}
}
v___jp_37_:
{
if (v___y_39_ == 0)
{
v___y_27_ = v___y_38_;
goto v___jp_26_;
}
else
{
uint32_t v___x_40_; uint32_t v___x_41_; uint32_t v___x_42_; uint8_t v___x_43_; 
v___x_40_ = 4194304;
v___x_41_ = lean_uint32_land(v___y_2_, v___x_40_);
v___x_42_ = 0;
v___x_43_ = lean_uint32_dec_eq(v___x_41_, v___x_42_);
if (v___x_43_ == 0)
{
v___y_27_ = v___y_38_;
goto v___jp_26_;
}
else
{
uint32_t v___x_44_; 
v___x_44_ = lean_uint32_lor(v___y_2_, v___x_40_);
return v___x_44_;
}
}
}
v___jp_45_:
{
uint32_t v___x_47_; uint32_t v___x_48_; uint32_t v___x_49_; uint32_t v___x_50_; uint8_t v___x_51_; 
v___x_47_ = 23;
v___x_48_ = lean_uint32_shift_right(v___y_2_, v___x_47_);
v___x_49_ = 255;
v___x_50_ = lean_uint32_land(v___x_48_, v___x_49_);
v___x_51_ = lean_uint32_dec_eq(v___x_50_, v___x_49_);
if (v___x_51_ == 0)
{
v___y_38_ = v___y_46_;
v___y_39_ = v___x_51_;
goto v___jp_37_;
}
else
{
uint32_t v___x_52_; uint32_t v___x_53_; uint32_t v___x_54_; uint8_t v___x_55_; 
v___x_52_ = 8388607;
v___x_53_ = lean_uint32_land(v___y_2_, v___x_52_);
v___x_54_ = 0;
v___x_55_ = lean_uint32_dec_eq(v___x_53_, v___x_54_);
if (v___x_55_ == 0)
{
v___y_38_ = v___y_46_;
v___y_39_ = v___x_51_;
goto v___jp_37_;
}
else
{
v___y_27_ = v___y_46_;
goto v___jp_26_;
}
}
}
v___jp_56_:
{
if (v___y_58_ == 0)
{
v___y_46_ = v___y_57_;
goto v___jp_45_;
}
else
{
uint32_t v___x_59_; uint32_t v___x_60_; uint32_t v___x_61_; uint8_t v___x_62_; 
v___x_59_ = 4194304;
v___x_60_ = lean_uint32_land(v___y_1_, v___x_59_);
v___x_61_ = 0;
v___x_62_ = lean_uint32_dec_eq(v___x_60_, v___x_61_);
if (v___x_62_ == 0)
{
v___y_46_ = v___y_57_;
goto v___jp_45_;
}
else
{
uint32_t v___x_63_; 
v___x_63_ = lean_uint32_lor(v___y_1_, v___x_59_);
return v___x_63_;
}
}
}
v___jp_64_:
{
float v_result_67_; uint8_t v___x_68_; 
v_result_67_ = lean_float32_add(v___y_65_, v___y_66_);
v___x_68_ = lean_float32_beq(v_result_67_, v_result_67_);
if (v___x_68_ == 0)
{
uint32_t v___x_69_; uint32_t v___x_70_; uint32_t v___x_71_; uint32_t v___x_72_; uint8_t v___x_73_; 
v___x_69_ = 23;
v___x_70_ = lean_uint32_shift_right(v___y_1_, v___x_69_);
v___x_71_ = 255;
v___x_72_ = lean_uint32_land(v___x_70_, v___x_71_);
v___x_73_ = lean_uint32_dec_eq(v___x_72_, v___x_71_);
if (v___x_73_ == 0)
{
v___y_57_ = v_result_67_;
v___y_58_ = v___x_73_;
goto v___jp_56_;
}
else
{
uint32_t v___x_74_; uint32_t v___x_75_; uint32_t v___x_76_; uint8_t v___x_77_; 
v___x_74_ = 8388607;
v___x_75_ = lean_uint32_land(v___y_1_, v___x_74_);
v___x_76_ = 0;
v___x_77_ = lean_uint32_dec_eq(v___x_75_, v___x_76_);
if (v___x_77_ == 0)
{
v___y_57_ = v_result_67_;
v___y_58_ = v___x_73_;
goto v___jp_56_;
}
else
{
v___y_46_ = v_result_67_;
goto v___jp_45_;
}
}
}
else
{
uint32_t v___x_78_; 
v___x_78_ = lean_float32_to_bits(v_result_67_);
return v___x_78_;
}
}
v___jp_79_:
{
if (v___y_81_ == 0)
{
float v___x_82_; 
v___x_82_ = lean_float32_of_bits(v___y_2_);
v___y_65_ = v___y_80_;
v___y_66_ = v___x_82_;
goto v___jp_64_;
}
else
{
uint32_t v___x_83_; uint32_t v___x_84_; uint32_t v___x_85_; uint32_t v___x_86_; float v___x_87_; lean_object* v___x_88_; uint32_t v___x_89_; uint32_t v___x_90_; lean_object* v___x_91_; lean_object* v___x_92_; float v___x_93_; float v___x_94_; 
v___x_83_ = 8388607;
v___x_84_ = lean_uint32_land(v___y_2_, v___x_83_);
v___x_85_ = 8388608;
v___x_86_ = lean_uint32_lor(v___x_84_, v___x_85_);
v___x_87_ = lean_uint32_to_float32(v___x_86_);
v___x_88_ = lp_competition_R2W01b_scaleTable;
v___x_89_ = 23;
v___x_90_ = lean_uint32_shift_right(v___y_2_, v___x_89_);
v___x_91_ = lean_uint32_to_nat(v___x_90_);
v___x_92_ = lean_array_fget_borrowed(v___x_88_, v___x_91_);
lean_dec(v___x_91_);
v___x_93_ = lean_unbox_float32(v___x_92_);
v___x_94_ = lean_float32_mul(v___x_87_, v___x_93_);
v___y_65_ = v___y_80_;
v___y_66_ = v___x_94_;
goto v___jp_64_;
}
}
v___jp_95_:
{
uint32_t v___x_97_; uint32_t v_a_98_; uint32_t v___x_99_; uint32_t v___x_100_; uint32_t v___x_101_; uint8_t v___x_102_; 
v___x_97_ = 2147483647;
v_a_98_ = lean_uint32_land(v___y_2_, v___x_97_);
v___x_99_ = 201326591;
v___x_100_ = 1;
v___x_101_ = lean_uint32_sub(v_a_98_, v___x_100_);
v___x_102_ = lean_uint32_dec_le(v___x_99_, v___x_101_);
if (v___x_102_ == 0)
{
v___y_80_ = v___y_96_;
v___y_81_ = v___x_102_;
goto v___jp_79_;
}
else
{
uint32_t v___x_103_; uint8_t v___x_104_; 
v___x_103_ = 2139095040;
v___x_104_ = lean_uint32_dec_lt(v_a_98_, v___x_103_);
v___y_80_ = v___y_96_;
v___y_81_ = v___x_104_;
goto v___jp_79_;
}
}
v___jp_105_:
{
if (v___y_106_ == 0)
{
float v___x_107_; 
v___x_107_ = lean_float32_of_bits(v___y_1_);
v___y_96_ = v___x_107_;
goto v___jp_95_;
}
else
{
uint32_t v___x_108_; uint32_t v___x_109_; uint32_t v___x_110_; uint32_t v___x_111_; float v___x_112_; lean_object* v___x_113_; uint32_t v___x_114_; uint32_t v___x_115_; lean_object* v___x_116_; lean_object* v___x_117_; float v___x_118_; float v___x_119_; 
v___x_108_ = 8388607;
v___x_109_ = lean_uint32_land(v___y_1_, v___x_108_);
v___x_110_ = 8388608;
v___x_111_ = lean_uint32_lor(v___x_109_, v___x_110_);
v___x_112_ = lean_uint32_to_float32(v___x_111_);
v___x_113_ = lp_competition_R2W01b_scaleTable;
v___x_114_ = 23;
v___x_115_ = lean_uint32_shift_right(v___y_1_, v___x_114_);
v___x_116_ = lean_uint32_to_nat(v___x_115_);
v___x_117_ = lean_array_fget_borrowed(v___x_113_, v___x_116_);
lean_dec(v___x_116_);
v___x_118_ = lean_unbox_float32(v___x_117_);
v___x_119_ = lean_float32_mul(v___x_112_, v___x_118_);
v___y_96_ = v___x_119_;
goto v___jp_95_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_128_, lean_object* v___y_129_){
_start:
{
uint32_t v___y_3905__boxed_130_; uint32_t v___y_3906__boxed_131_; uint32_t v_res_132_; lean_object* v_r_133_; 
v___y_3905__boxed_130_ = lean_unbox_uint32(v___y_128_);
lean_dec(v___y_128_);
v___y_3906__boxed_131_ = lean_unbox_uint32(v___y_129_);
lean_dec(v___y_129_);
v_res_132_ = lp_competition_main___lam__0(v___y_3905__boxed_130_, v___y_3906__boxed_131_);
v_r_133_ = lean_box_uint32(v_res_132_);
return v_r_133_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_134_, uint32_t v___y_135_){
_start:
{
uint32_t v___y_137_; uint32_t v___y_138_; uint32_t v___y_139_; uint32_t v___y_143_; uint32_t v___y_144_; uint32_t v___y_145_; uint32_t v___y_149_; uint64_t v___y_153_; uint32_t v___y_154_; uint8_t v___y_155_; uint64_t v___y_156_; uint32_t v___y_168_; uint32_t v___y_172_; uint64_t v___y_173_; uint8_t v___y_174_; uint64_t v___y_175_; float v___y_187_; uint8_t v___y_188_; float v___y_193_; float v___y_205_; uint8_t v___y_206_; float v___y_210_; float v___y_221_; uint8_t v___y_222_; float v___y_229_; float v___y_240_; uint8_t v___y_241_; float v___y_248_; float v___y_249_; float v___y_263_; uint8_t v___y_264_; float v___y_279_; uint32_t v___x_288_; uint32_t v___x_289_; uint8_t v___y_291_; uint32_t v___x_303_; uint32_t v___y_305_; uint32_t v___y_306_; uint32_t v___y_307_; uint32_t v___y_308_; uint32_t v___y_315_; uint32_t v___y_316_; uint8_t v___y_317_; uint32_t v___y_318_; uint64_t v___y_322_; uint32_t v___y_323_; uint64_t v___y_324_; uint8_t v___y_325_; uint64_t v___y_326_; uint64_t v___y_336_; uint8_t v___y_337_; uint32_t v___y_338_; uint8_t v___y_339_; uint64_t v___y_340_; uint64_t v___y_341_; uint64_t v___y_348_; uint32_t v___y_349_; uint64_t v___y_350_; uint8_t v___y_351_; uint64_t v___y_352_; uint64_t v___y_358_; uint32_t v___y_359_; uint64_t v___y_360_; uint64_t v___y_361_; uint8_t v___y_362_; uint64_t v___y_363_; uint64_t v___y_418_; uint64_t v___y_419_; uint32_t v___y_420_; uint64_t v___y_421_; uint64_t v___y_422_; uint8_t v___y_423_; uint64_t v___y_424_; uint64_t v___y_430_; uint64_t v___y_431_; uint64_t v___y_432_; uint32_t v___y_433_; uint64_t v___y_434_; uint64_t v___y_435_; uint8_t v___y_436_; uint64_t v___y_437_; uint64_t v___y_438_; uint64_t v___y_443_; uint64_t v___y_444_; uint32_t v___y_445_; uint64_t v___y_446_; uint64_t v___y_447_; uint8_t v___y_448_; uint64_t v___y_449_; uint64_t v___y_454_; uint64_t v___y_455_; uint32_t v___y_456_; uint64_t v___y_457_; uint64_t v___y_458_; uint64_t v___y_459_; uint64_t v___y_460_; uint8_t v___y_461_; uint64_t v___y_462_; uint64_t v___y_467_; uint32_t v___y_468_; uint64_t v___y_469_; uint64_t v___y_470_; uint64_t v___y_471_; uint8_t v___y_472_; uint64_t v___y_473_; uint64_t v___y_478_; uint64_t v___y_479_; uint64_t v___y_480_; uint32_t v___y_481_; uint64_t v___y_482_; uint64_t v___y_483_; uint64_t v___y_484_; uint8_t v___y_485_; uint64_t v___y_486_; uint64_t v___y_491_; uint64_t v___y_492_; uint32_t v___y_493_; uint64_t v___y_494_; uint64_t v___y_495_; uint8_t v___y_496_; uint64_t v___y_497_; uint64_t v___y_502_; uint32_t v___y_503_; uint64_t v___y_504_; uint64_t v___y_505_; uint64_t v___y_506_; uint64_t v___y_507_; uint64_t v___y_508_; uint8_t v___y_509_; uint64_t v___y_510_; uint64_t v___y_515_; uint32_t v___y_516_; uint64_t v___y_517_; uint64_t v___y_518_; uint64_t v___y_519_; uint8_t v___y_520_; uint64_t v___y_521_; uint64_t v___y_526_; uint64_t v___y_527_; uint32_t v___y_528_; uint64_t v___y_529_; uint64_t v___y_530_; uint8_t v___y_531_; uint64_t v___y_532_; uint32_t v___y_536_; uint64_t v___y_537_; uint64_t v___y_538_; uint8_t v___y_539_; uint64_t v___y_548_; uint32_t v___y_549_; uint64_t v___y_550_; uint64_t v___y_551_; uint8_t v___y_552_; uint64_t v___y_553_; uint32_t v_ex_586_; uint32_t v___x_587_; uint32_t v_ey_588_; uint64_t v___y_590_; uint32_t v___y_591_; uint64_t v___y_592_; uint8_t v___y_593_; uint64_t v___y_594_; uint32_t v___y_601_; uint64_t v___y_602_; uint8_t v___y_603_; uint64_t v___y_604_; uint32_t v___y_611_; uint32_t v___y_612_; uint8_t v___y_613_; uint64_t v___y_614_; uint8_t v___y_622_; uint32_t v___x_632_; uint32_t v___x_633_; uint8_t v___x_634_; uint8_t v___y_636_; uint8_t v___y_637_; uint8_t v___y_639_; uint8_t v___y_640_; uint8_t v___y_641_; uint8_t v___y_643_; uint8_t v___y_644_; uint8_t v___y_650_; 
v___x_288_ = 23;
v___x_289_ = lean_uint32_shift_right(v___y_134_, v___x_288_);
v___x_303_ = 255;
v_ex_586_ = lean_uint32_land(v___x_289_, v___x_303_);
v___x_587_ = lean_uint32_shift_right(v___y_135_, v___x_288_);
v_ey_588_ = lean_uint32_land(v___x_587_, v___x_303_);
v___x_632_ = lean_uint32_add(v_ex_586_, v_ey_588_);
v___x_633_ = 128;
v___x_634_ = lean_uint32_dec_lt(v___x_632_, v___x_633_);
if (v___x_634_ == 0)
{
uint32_t v___x_659_; uint32_t v_a_660_; uint32_t v___x_661_; uint32_t v___x_662_; uint32_t v___x_663_; uint8_t v___x_664_; 
v___x_659_ = 2147483647;
v_a_660_ = lean_uint32_land(v___y_134_, v___x_659_);
v___x_661_ = 201326591;
v___x_662_ = 1;
v___x_663_ = lean_uint32_sub(v_a_660_, v___x_662_);
v___x_664_ = lean_uint32_dec_le(v___x_661_, v___x_663_);
if (v___x_664_ == 0)
{
v___y_291_ = v___x_664_;
goto v___jp_290_;
}
else
{
uint32_t v___x_665_; uint8_t v___x_666_; 
v___x_665_ = 2139095040;
v___x_666_ = lean_uint32_dec_lt(v_a_660_, v___x_665_);
v___y_291_ = v___x_666_;
goto v___jp_290_;
}
}
else
{
uint32_t v___x_667_; uint32_t v___x_668_; uint32_t v___x_669_; uint8_t v___x_670_; 
v___x_667_ = 4278190080;
v___x_668_ = 1;
v___x_669_ = lean_uint32_shift_left(v___y_134_, v___x_668_);
v___x_670_ = lean_uint32_dec_le(v___x_667_, v___x_669_);
if (v___x_670_ == 0)
{
uint32_t v___x_671_; uint8_t v___x_672_; 
v___x_671_ = lean_uint32_shift_left(v___y_135_, v___x_668_);
v___x_672_ = lean_uint32_dec_le(v___x_667_, v___x_671_);
v___y_650_ = v___x_672_;
goto v___jp_649_;
}
else
{
v___y_650_ = v___x_670_;
goto v___jp_649_;
}
}
v___jp_136_:
{
uint32_t v___x_140_; uint32_t v___x_141_; 
v___x_140_ = lean_uint32_land(v___y_138_, v___y_137_);
v___x_141_ = lean_uint32_lor(v___y_139_, v___x_140_);
return v___x_141_;
}
v___jp_142_:
{
uint32_t v___x_146_; uint32_t v___x_147_; 
v___x_146_ = lean_uint32_land(v___y_143_, v___y_144_);
v___x_147_ = lean_uint32_lor(v___y_145_, v___x_146_);
return v___x_147_;
}
v___jp_148_:
{
uint32_t v___x_150_; uint32_t v___x_151_; 
v___x_150_ = 8388608;
v___x_151_ = lean_uint32_lor(v___y_149_, v___x_150_);
return v___x_151_;
}
v___jp_152_:
{
uint8_t v___x_157_; 
v___x_157_ = lean_uint64_dec_eq(v___y_156_, v___y_153_);
if (v___x_157_ == 0)
{
uint64_t v___x_158_; uint8_t v___x_159_; 
v___x_158_ = 8388608ULL;
v___x_159_ = lean_uint64_dec_eq(v___y_156_, v___x_158_);
if (v___x_159_ == 0)
{
uint32_t v___x_160_; 
v___x_160_ = lean_uint64_to_uint32(v___y_156_);
if (v___y_155_ == 0)
{
uint32_t v___x_161_; 
v___x_161_ = 0;
v___y_143_ = v___x_160_;
v___y_144_ = v___y_154_;
v___y_145_ = v___x_161_;
goto v___jp_142_;
}
else
{
uint32_t v___x_162_; 
v___x_162_ = 2147483648;
v___y_143_ = v___x_160_;
v___y_144_ = v___y_154_;
v___y_145_ = v___x_162_;
goto v___jp_142_;
}
}
else
{
if (v___y_155_ == 0)
{
uint32_t v___x_163_; 
v___x_163_ = 0;
v___y_149_ = v___x_163_;
goto v___jp_148_;
}
else
{
uint32_t v___x_164_; 
v___x_164_ = 2147483648;
v___y_149_ = v___x_164_;
goto v___jp_148_;
}
}
}
else
{
if (v___y_155_ == 0)
{
uint32_t v___x_165_; 
v___x_165_ = 0;
return v___x_165_;
}
else
{
uint32_t v___x_166_; 
v___x_166_ = 2147483648;
return v___x_166_;
}
}
}
v___jp_167_:
{
uint32_t v___x_169_; uint32_t v___x_170_; 
v___x_169_ = 8388608;
v___x_170_ = lean_uint32_lor(v___y_168_, v___x_169_);
return v___x_170_;
}
v___jp_171_:
{
uint8_t v___x_176_; 
v___x_176_ = lean_uint64_dec_eq(v___y_175_, v___y_173_);
if (v___x_176_ == 0)
{
uint64_t v___x_177_; uint8_t v___x_178_; 
v___x_177_ = 8388608ULL;
v___x_178_ = lean_uint64_dec_eq(v___y_175_, v___x_177_);
if (v___x_178_ == 0)
{
uint32_t v___x_179_; 
v___x_179_ = lean_uint64_to_uint32(v___y_175_);
if (v___y_174_ == 0)
{
uint32_t v___x_180_; 
v___x_180_ = 0;
v___y_137_ = v___y_172_;
v___y_138_ = v___x_179_;
v___y_139_ = v___x_180_;
goto v___jp_136_;
}
else
{
uint32_t v___x_181_; 
v___x_181_ = 2147483648;
v___y_137_ = v___y_172_;
v___y_138_ = v___x_179_;
v___y_139_ = v___x_181_;
goto v___jp_136_;
}
}
else
{
if (v___y_174_ == 0)
{
uint32_t v___x_182_; 
v___x_182_ = 0;
v___y_168_ = v___x_182_;
goto v___jp_167_;
}
else
{
uint32_t v___x_183_; 
v___x_183_ = 2147483648;
v___y_168_ = v___x_183_;
goto v___jp_167_;
}
}
}
else
{
if (v___y_174_ == 0)
{
uint32_t v___x_184_; 
v___x_184_ = 0;
return v___x_184_;
}
else
{
uint32_t v___x_185_; 
v___x_185_ = 2147483648;
return v___x_185_;
}
}
}
v___jp_186_:
{
if (v___y_188_ == 0)
{
uint32_t v___x_189_; 
v___x_189_ = lean_float32_to_bits(v___y_187_);
return v___x_189_;
}
else
{
uint32_t v___x_190_; uint32_t v___x_191_; 
v___x_190_ = 4194304;
v___x_191_ = lean_uint32_lor(v___y_135_, v___x_190_);
return v___x_191_;
}
}
v___jp_192_:
{
uint32_t v___x_194_; uint32_t v___x_195_; uint32_t v___x_196_; uint32_t v___x_197_; uint8_t v___x_198_; 
v___x_194_ = 23;
v___x_195_ = lean_uint32_shift_right(v___y_135_, v___x_194_);
v___x_196_ = 255;
v___x_197_ = lean_uint32_land(v___x_195_, v___x_196_);
v___x_198_ = lean_uint32_dec_eq(v___x_197_, v___x_196_);
if (v___x_198_ == 0)
{
v___y_187_ = v___y_193_;
v___y_188_ = v___x_198_;
goto v___jp_186_;
}
else
{
uint32_t v___x_199_; uint32_t v___x_200_; uint32_t v___x_201_; uint8_t v___x_202_; 
v___x_199_ = 8388607;
v___x_200_ = lean_uint32_land(v___y_135_, v___x_199_);
v___x_201_ = 0;
v___x_202_ = lean_uint32_dec_eq(v___x_200_, v___x_201_);
if (v___x_202_ == 0)
{
v___y_187_ = v___y_193_;
v___y_188_ = v___x_198_;
goto v___jp_186_;
}
else
{
uint32_t v___x_203_; 
v___x_203_ = lean_float32_to_bits(v___y_193_);
return v___x_203_;
}
}
}
v___jp_204_:
{
if (v___y_206_ == 0)
{
v___y_193_ = v___y_205_;
goto v___jp_192_;
}
else
{
uint32_t v___x_207_; uint32_t v___x_208_; 
v___x_207_ = 4194304;
v___x_208_ = lean_uint32_lor(v___y_134_, v___x_207_);
return v___x_208_;
}
}
v___jp_209_:
{
uint32_t v___x_211_; uint32_t v___x_212_; uint32_t v___x_213_; uint32_t v___x_214_; uint8_t v___x_215_; 
v___x_211_ = 23;
v___x_212_ = lean_uint32_shift_right(v___y_134_, v___x_211_);
v___x_213_ = 255;
v___x_214_ = lean_uint32_land(v___x_212_, v___x_213_);
v___x_215_ = lean_uint32_dec_eq(v___x_214_, v___x_213_);
if (v___x_215_ == 0)
{
v___y_205_ = v___y_210_;
v___y_206_ = v___x_215_;
goto v___jp_204_;
}
else
{
uint32_t v___x_216_; uint32_t v___x_217_; uint32_t v___x_218_; uint8_t v___x_219_; 
v___x_216_ = 8388607;
v___x_217_ = lean_uint32_land(v___y_134_, v___x_216_);
v___x_218_ = 0;
v___x_219_ = lean_uint32_dec_eq(v___x_217_, v___x_218_);
if (v___x_219_ == 0)
{
v___y_205_ = v___y_210_;
v___y_206_ = v___x_215_;
goto v___jp_204_;
}
else
{
v___y_193_ = v___y_210_;
goto v___jp_192_;
}
}
}
v___jp_220_:
{
if (v___y_222_ == 0)
{
v___y_210_ = v___y_221_;
goto v___jp_209_;
}
else
{
uint32_t v___x_223_; uint32_t v___x_224_; uint32_t v___x_225_; uint8_t v___x_226_; 
v___x_223_ = 4194304;
v___x_224_ = lean_uint32_land(v___y_135_, v___x_223_);
v___x_225_ = 0;
v___x_226_ = lean_uint32_dec_eq(v___x_224_, v___x_225_);
if (v___x_226_ == 0)
{
v___y_210_ = v___y_221_;
goto v___jp_209_;
}
else
{
uint32_t v___x_227_; 
v___x_227_ = lean_uint32_lor(v___y_135_, v___x_223_);
return v___x_227_;
}
}
}
v___jp_228_:
{
uint32_t v___x_230_; uint32_t v___x_231_; uint32_t v___x_232_; uint32_t v___x_233_; uint8_t v___x_234_; 
v___x_230_ = 23;
v___x_231_ = lean_uint32_shift_right(v___y_135_, v___x_230_);
v___x_232_ = 255;
v___x_233_ = lean_uint32_land(v___x_231_, v___x_232_);
v___x_234_ = lean_uint32_dec_eq(v___x_233_, v___x_232_);
if (v___x_234_ == 0)
{
v___y_221_ = v___y_229_;
v___y_222_ = v___x_234_;
goto v___jp_220_;
}
else
{
uint32_t v___x_235_; uint32_t v___x_236_; uint32_t v___x_237_; uint8_t v___x_238_; 
v___x_235_ = 8388607;
v___x_236_ = lean_uint32_land(v___y_135_, v___x_235_);
v___x_237_ = 0;
v___x_238_ = lean_uint32_dec_eq(v___x_236_, v___x_237_);
if (v___x_238_ == 0)
{
v___y_221_ = v___y_229_;
v___y_222_ = v___x_234_;
goto v___jp_220_;
}
else
{
v___y_210_ = v___y_229_;
goto v___jp_209_;
}
}
}
v___jp_239_:
{
if (v___y_241_ == 0)
{
v___y_229_ = v___y_240_;
goto v___jp_228_;
}
else
{
uint32_t v___x_242_; uint32_t v___x_243_; uint32_t v___x_244_; uint8_t v___x_245_; 
v___x_242_ = 4194304;
v___x_243_ = lean_uint32_land(v___y_134_, v___x_242_);
v___x_244_ = 0;
v___x_245_ = lean_uint32_dec_eq(v___x_243_, v___x_244_);
if (v___x_245_ == 0)
{
v___y_229_ = v___y_240_;
goto v___jp_228_;
}
else
{
uint32_t v___x_246_; 
v___x_246_ = lean_uint32_lor(v___y_134_, v___x_242_);
return v___x_246_;
}
}
}
v___jp_247_:
{
float v_result_250_; uint8_t v___x_251_; 
v_result_250_ = lean_float32_mul(v___y_248_, v___y_249_);
v___x_251_ = lean_float32_beq(v_result_250_, v_result_250_);
if (v___x_251_ == 0)
{
uint32_t v___x_252_; uint32_t v___x_253_; uint32_t v___x_254_; uint32_t v___x_255_; uint8_t v___x_256_; 
v___x_252_ = 23;
v___x_253_ = lean_uint32_shift_right(v___y_134_, v___x_252_);
v___x_254_ = 255;
v___x_255_ = lean_uint32_land(v___x_253_, v___x_254_);
v___x_256_ = lean_uint32_dec_eq(v___x_255_, v___x_254_);
if (v___x_256_ == 0)
{
v___y_240_ = v_result_250_;
v___y_241_ = v___x_256_;
goto v___jp_239_;
}
else
{
uint32_t v___x_257_; uint32_t v___x_258_; uint32_t v___x_259_; uint8_t v___x_260_; 
v___x_257_ = 8388607;
v___x_258_ = lean_uint32_land(v___y_134_, v___x_257_);
v___x_259_ = 0;
v___x_260_ = lean_uint32_dec_eq(v___x_258_, v___x_259_);
if (v___x_260_ == 0)
{
v___y_240_ = v_result_250_;
v___y_241_ = v___x_256_;
goto v___jp_239_;
}
else
{
v___y_229_ = v_result_250_;
goto v___jp_228_;
}
}
}
else
{
uint32_t v___x_261_; 
v___x_261_ = lean_float32_to_bits(v_result_250_);
return v___x_261_;
}
}
v___jp_262_:
{
if (v___y_264_ == 0)
{
float v___x_265_; 
v___x_265_ = lean_float32_of_bits(v___y_135_);
v___y_248_ = v___y_263_;
v___y_249_ = v___x_265_;
goto v___jp_247_;
}
else
{
uint32_t v___x_266_; uint32_t v___x_267_; uint32_t v___x_268_; uint32_t v___x_269_; float v___x_270_; lean_object* v___x_271_; uint32_t v___x_272_; uint32_t v___x_273_; lean_object* v___x_274_; lean_object* v___x_275_; float v___x_276_; float v___x_277_; 
v___x_266_ = 8388607;
v___x_267_ = lean_uint32_land(v___y_135_, v___x_266_);
v___x_268_ = 8388608;
v___x_269_ = lean_uint32_lor(v___x_267_, v___x_268_);
v___x_270_ = lean_uint32_to_float32(v___x_269_);
v___x_271_ = lp_competition_R2W01b_scaleTable;
v___x_272_ = 23;
v___x_273_ = lean_uint32_shift_right(v___y_135_, v___x_272_);
v___x_274_ = lean_uint32_to_nat(v___x_273_);
v___x_275_ = lean_array_fget_borrowed(v___x_271_, v___x_274_);
lean_dec(v___x_274_);
v___x_276_ = lean_unbox_float32(v___x_275_);
v___x_277_ = lean_float32_mul(v___x_270_, v___x_276_);
v___y_248_ = v___y_263_;
v___y_249_ = v___x_277_;
goto v___jp_247_;
}
}
v___jp_278_:
{
uint32_t v___x_280_; uint32_t v_a_281_; uint32_t v___x_282_; uint32_t v___x_283_; uint32_t v___x_284_; uint8_t v___x_285_; 
v___x_280_ = 2147483647;
v_a_281_ = lean_uint32_land(v___y_135_, v___x_280_);
v___x_282_ = 201326591;
v___x_283_ = 1;
v___x_284_ = lean_uint32_sub(v_a_281_, v___x_283_);
v___x_285_ = lean_uint32_dec_le(v___x_282_, v___x_284_);
if (v___x_285_ == 0)
{
v___y_263_ = v___y_279_;
v___y_264_ = v___x_285_;
goto v___jp_262_;
}
else
{
uint32_t v___x_286_; uint8_t v___x_287_; 
v___x_286_ = 2139095040;
v___x_287_ = lean_uint32_dec_lt(v_a_281_, v___x_286_);
v___y_263_ = v___y_279_;
v___y_264_ = v___x_287_;
goto v___jp_262_;
}
}
v___jp_290_:
{
if (v___y_291_ == 0)
{
float v___x_292_; 
v___x_292_ = lean_float32_of_bits(v___y_134_);
v___y_279_ = v___x_292_;
goto v___jp_278_;
}
else
{
uint32_t v___x_293_; uint32_t v___x_294_; uint32_t v___x_295_; uint32_t v___x_296_; float v___x_297_; lean_object* v___x_298_; lean_object* v___x_299_; lean_object* v___x_300_; float v___x_301_; float v___x_302_; 
v___x_293_ = 8388607;
v___x_294_ = lean_uint32_land(v___y_134_, v___x_293_);
v___x_295_ = 8388608;
v___x_296_ = lean_uint32_lor(v___x_294_, v___x_295_);
v___x_297_ = lean_uint32_to_float32(v___x_296_);
v___x_298_ = lp_competition_R2W01b_scaleTable;
v___x_299_ = lean_uint32_to_nat(v___x_289_);
v___x_300_ = lean_array_fget_borrowed(v___x_298_, v___x_299_);
lean_dec(v___x_299_);
v___x_301_ = lean_unbox_float32(v___x_300_);
v___x_302_ = lean_float32_mul(v___x_297_, v___x_301_);
v___y_279_ = v___x_302_;
goto v___jp_278_;
}
}
v___jp_304_:
{
uint32_t v___x_309_; uint32_t v___x_310_; uint32_t v___x_311_; uint32_t v___x_312_; uint32_t v___x_313_; 
v___x_309_ = lean_uint32_land(v___y_305_, v___x_303_);
v___x_310_ = lean_uint32_shift_left(v___x_309_, v___x_288_);
v___x_311_ = lean_uint32_lor(v___y_308_, v___x_310_);
v___x_312_ = lean_uint32_land(v___y_307_, v___y_306_);
v___x_313_ = lean_uint32_lor(v___x_311_, v___x_312_);
return v___x_313_;
}
v___jp_314_:
{
if (v___y_317_ == 0)
{
uint32_t v___x_319_; 
v___x_319_ = 0;
v___y_305_ = v___y_315_;
v___y_306_ = v___y_316_;
v___y_307_ = v___y_318_;
v___y_308_ = v___x_319_;
goto v___jp_304_;
}
else
{
uint32_t v___x_320_; 
v___x_320_ = 2147483648;
v___y_305_ = v___y_315_;
v___y_306_ = v___y_316_;
v___y_307_ = v___y_318_;
v___y_308_ = v___x_320_;
goto v___jp_304_;
}
}
v___jp_321_:
{
uint64_t v___x_327_; uint64_t v_encodedExponent_328_; uint32_t v___x_329_; uint64_t v___x_330_; uint8_t v___x_331_; 
v___x_327_ = 171ULL;
v_encodedExponent_328_ = lean_uint64_sub(v___y_324_, v___x_327_);
v___x_329_ = lean_uint64_to_uint32(v_encodedExponent_328_);
v___x_330_ = 8388608ULL;
v___x_331_ = lean_uint64_dec_lt(v___y_326_, v___x_330_);
if (v___x_331_ == 0)
{
uint64_t v___x_332_; uint32_t v___x_333_; 
v___x_332_ = lean_uint64_sub(v___y_326_, v___x_330_);
v___x_333_ = lean_uint64_to_uint32(v___x_332_);
v___y_315_ = v___x_329_;
v___y_316_ = v___y_323_;
v___y_317_ = v___y_325_;
v___y_318_ = v___x_333_;
goto v___jp_314_;
}
else
{
uint32_t v___x_334_; 
v___x_334_ = lean_uint64_to_uint32(v___y_322_);
v___y_315_ = v___x_329_;
v___y_316_ = v___y_323_;
v___y_317_ = v___y_325_;
v___y_318_ = v___x_334_;
goto v___jp_314_;
}
}
v___jp_335_:
{
uint64_t v___x_342_; uint8_t v___x_343_; 
v___x_342_ = 425ULL;
v___x_343_ = lean_uint64_dec_lt(v___x_342_, v___y_341_);
if (v___x_343_ == 0)
{
if (v___y_337_ == 0)
{
v___y_322_ = v___y_336_;
v___y_323_ = v___y_338_;
v___y_324_ = v___y_341_;
v___y_325_ = v___y_339_;
v___y_326_ = v___y_340_;
goto v___jp_321_;
}
else
{
uint64_t v___x_344_; 
v___x_344_ = 8388608ULL;
v___y_322_ = v___y_336_;
v___y_323_ = v___y_338_;
v___y_324_ = v___y_341_;
v___y_325_ = v___y_339_;
v___y_326_ = v___x_344_;
goto v___jp_321_;
}
}
else
{
if (v___y_339_ == 0)
{
uint32_t v___x_345_; 
v___x_345_ = 2139095040;
return v___x_345_;
}
else
{
uint32_t v___x_346_; 
v___x_346_ = 4286578688;
return v___x_346_;
}
}
}
v___jp_347_:
{
uint64_t v___x_353_; uint8_t v_carry_354_; 
v___x_353_ = 16777216ULL;
v_carry_354_ = lean_uint64_dec_eq(v___y_352_, v___x_353_);
if (v_carry_354_ == 0)
{
v___y_336_ = v___y_348_;
v___y_337_ = v_carry_354_;
v___y_338_ = v___y_349_;
v___y_339_ = v___y_351_;
v___y_340_ = v___y_352_;
v___y_341_ = v___y_350_;
goto v___jp_335_;
}
else
{
uint64_t v___x_355_; uint64_t v___x_356_; 
v___x_355_ = 1ULL;
v___x_356_ = lean_uint64_add(v___y_350_, v___x_355_);
v___y_336_ = v___y_348_;
v___y_337_ = v_carry_354_;
v___y_338_ = v___y_349_;
v___y_339_ = v___y_351_;
v___y_340_ = v___y_352_;
v___y_341_ = v___x_356_;
goto v___jp_335_;
}
}
v___jp_357_:
{
uint64_t v_position_364_; uint64_t v___x_365_; uint8_t v___x_366_; 
v_position_364_ = lean_uint64_add(v___y_363_, v___y_360_);
v___x_365_ = 172ULL;
v___x_366_ = lean_uint64_dec_lt(v_position_364_, v___x_365_);
if (v___x_366_ == 0)
{
uint64_t v___x_367_; uint8_t v___x_368_; 
v___x_367_ = 23ULL;
v___x_368_ = lean_uint64_dec_lt(v___y_363_, v___x_367_);
if (v___x_368_ == 0)
{
uint64_t v___x_369_; uint8_t v___x_370_; 
v___x_369_ = lean_uint64_sub(v___y_363_, v___x_367_);
v___x_370_ = lean_uint64_dec_eq(v___x_369_, v___y_358_);
if (v___x_370_ == 0)
{
uint64_t v___x_371_; uint8_t v___x_372_; 
v___x_371_ = 64ULL;
v___x_372_ = lean_uint64_dec_lt(v___x_369_, v___x_371_);
if (v___x_372_ == 0)
{
uint8_t v___x_373_; 
v___x_373_ = lean_uint64_dec_eq(v___x_369_, v___x_371_);
if (v___x_373_ == 0)
{
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v___y_358_;
goto v___jp_347_;
}
else
{
uint64_t v___x_374_; uint8_t v___x_375_; 
v___x_374_ = 9223372036854775808ULL;
v___x_375_ = lean_uint64_dec_lt(v___x_374_, v___y_361_);
if (v___x_375_ == 0)
{
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v___y_358_;
goto v___jp_347_;
}
else
{
uint64_t v___x_376_; 
v___x_376_ = 1ULL;
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v___x_376_;
goto v___jp_347_;
}
}
}
else
{
uint64_t v_quotient_377_; uint64_t v___x_378_; uint64_t v___x_379_; uint64_t v___x_380_; uint64_t v_remainder_381_; uint64_t v___x_382_; uint64_t v_half_383_; uint8_t v___x_384_; 
v_quotient_377_ = lean_uint64_shift_right(v___y_361_, v___x_369_);
v___x_378_ = 1ULL;
v___x_379_ = lean_uint64_shift_left(v___x_378_, v___x_369_);
v___x_380_ = lean_uint64_sub(v___x_379_, v___x_378_);
v_remainder_381_ = lean_uint64_land(v___y_361_, v___x_380_);
v___x_382_ = lean_uint64_sub(v___x_369_, v___x_378_);
v_half_383_ = lean_uint64_shift_left(v___x_378_, v___x_382_);
v___x_384_ = lean_uint64_dec_lt(v_remainder_381_, v_half_383_);
if (v___x_384_ == 0)
{
uint8_t v___x_385_; 
v___x_385_ = lean_uint64_dec_lt(v_half_383_, v_remainder_381_);
if (v___x_385_ == 0)
{
uint64_t v___x_386_; uint8_t v___x_387_; 
v___x_386_ = lean_uint64_land(v_quotient_377_, v___x_378_);
v___x_387_ = lean_uint64_dec_eq(v___x_386_, v___y_358_);
if (v___x_387_ == 0)
{
uint64_t v___x_388_; 
v___x_388_ = lean_uint64_add(v_quotient_377_, v___x_378_);
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v___x_388_;
goto v___jp_347_;
}
else
{
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v_quotient_377_;
goto v___jp_347_;
}
}
else
{
uint64_t v___x_389_; 
v___x_389_ = lean_uint64_add(v_quotient_377_, v___x_378_);
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v___x_389_;
goto v___jp_347_;
}
}
else
{
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v_quotient_377_;
goto v___jp_347_;
}
}
}
else
{
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v___y_361_;
goto v___jp_347_;
}
}
else
{
uint64_t v___x_390_; uint64_t v___x_391_; 
v___x_390_ = lean_uint64_sub(v___x_367_, v___y_363_);
v___x_391_ = lean_uint64_shift_left(v___y_361_, v___x_390_);
v___y_348_ = v___y_358_;
v___y_349_ = v___y_359_;
v___y_350_ = v_position_364_;
v___y_351_ = v___y_362_;
v___y_352_ = v___x_391_;
goto v___jp_347_;
}
}
else
{
uint64_t v___x_392_; uint8_t v___x_393_; 
v___x_392_ = 149ULL;
v___x_393_ = lean_uint64_dec_lt(v___y_360_, v___x_392_);
if (v___x_393_ == 0)
{
uint64_t v___x_394_; uint64_t v___x_395_; 
v___x_394_ = lean_uint64_sub(v___y_360_, v___x_392_);
v___x_395_ = lean_uint64_shift_left(v___y_361_, v___x_394_);
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v___x_395_;
goto v___jp_152_;
}
else
{
uint64_t v___x_396_; uint8_t v___x_397_; 
v___x_396_ = lean_uint64_sub(v___x_392_, v___y_360_);
v___x_397_ = lean_uint64_dec_eq(v___x_396_, v___y_358_);
if (v___x_397_ == 0)
{
uint64_t v___x_398_; uint8_t v___x_399_; 
v___x_398_ = 64ULL;
v___x_399_ = lean_uint64_dec_lt(v___x_396_, v___x_398_);
if (v___x_399_ == 0)
{
uint8_t v___x_400_; 
v___x_400_ = lean_uint64_dec_eq(v___x_396_, v___x_398_);
if (v___x_400_ == 0)
{
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v___y_358_;
goto v___jp_152_;
}
else
{
uint64_t v___x_401_; uint8_t v___x_402_; 
v___x_401_ = 9223372036854775808ULL;
v___x_402_ = lean_uint64_dec_lt(v___x_401_, v___y_361_);
if (v___x_402_ == 0)
{
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v___y_358_;
goto v___jp_152_;
}
else
{
uint64_t v___x_403_; 
v___x_403_ = 1ULL;
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v___x_403_;
goto v___jp_152_;
}
}
}
else
{
uint64_t v_quotient_404_; uint64_t v___x_405_; uint64_t v___x_406_; uint64_t v___x_407_; uint64_t v_remainder_408_; uint64_t v___x_409_; uint64_t v_half_410_; uint8_t v___x_411_; 
v_quotient_404_ = lean_uint64_shift_right(v___y_361_, v___x_396_);
v___x_405_ = 1ULL;
v___x_406_ = lean_uint64_shift_left(v___x_405_, v___x_396_);
v___x_407_ = lean_uint64_sub(v___x_406_, v___x_405_);
v_remainder_408_ = lean_uint64_land(v___y_361_, v___x_407_);
v___x_409_ = lean_uint64_sub(v___x_396_, v___x_405_);
v_half_410_ = lean_uint64_shift_left(v___x_405_, v___x_409_);
v___x_411_ = lean_uint64_dec_lt(v_remainder_408_, v_half_410_);
if (v___x_411_ == 0)
{
uint8_t v___x_412_; 
v___x_412_ = lean_uint64_dec_lt(v_half_410_, v_remainder_408_);
if (v___x_412_ == 0)
{
uint64_t v___x_413_; uint8_t v___x_414_; 
v___x_413_ = lean_uint64_land(v_quotient_404_, v___x_405_);
v___x_414_ = lean_uint64_dec_eq(v___x_413_, v___y_358_);
if (v___x_414_ == 0)
{
uint64_t v___x_415_; 
v___x_415_ = lean_uint64_add(v_quotient_404_, v___x_405_);
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v___x_415_;
goto v___jp_152_;
}
else
{
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v_quotient_404_;
goto v___jp_152_;
}
}
else
{
uint64_t v___x_416_; 
v___x_416_ = lean_uint64_add(v_quotient_404_, v___x_405_);
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v___x_416_;
goto v___jp_152_;
}
}
else
{
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v_quotient_404_;
goto v___jp_152_;
}
}
}
else
{
v___y_153_ = v___y_358_;
v___y_154_ = v___y_359_;
v___y_155_ = v___y_362_;
v___y_156_ = v___y_361_;
goto v___jp_152_;
}
}
}
}
v___jp_417_:
{
uint64_t v___x_425_; uint64_t v___x_426_; uint8_t v___x_427_; 
v___x_425_ = 1ULL;
v___x_426_ = lean_uint64_shift_right(v___y_418_, v___x_425_);
v___x_427_ = lean_uint64_dec_eq(v___x_426_, v___y_419_);
if (v___x_427_ == 0)
{
uint64_t v___x_428_; 
v___x_428_ = lean_uint64_add(v___y_424_, v___x_425_);
v___y_358_ = v___y_419_;
v___y_359_ = v___y_420_;
v___y_360_ = v___y_421_;
v___y_361_ = v___y_422_;
v___y_362_ = v___y_423_;
v___y_363_ = v___x_428_;
goto v___jp_357_;
}
else
{
v___y_358_ = v___y_419_;
v___y_359_ = v___y_420_;
v___y_360_ = v___y_421_;
v___y_361_ = v___y_422_;
v___y_362_ = v___y_423_;
v___y_363_ = v___y_424_;
goto v___jp_357_;
}
}
v___jp_429_:
{
uint64_t v___x_439_; uint8_t v___x_440_; 
v___x_439_ = lean_uint64_shift_right(v___y_431_, v___y_432_);
v___x_440_ = lean_uint64_dec_eq(v___x_439_, v___y_430_);
if (v___x_440_ == 0)
{
uint64_t v___x_441_; 
v___x_441_ = lean_uint64_add(v___y_437_, v___y_432_);
v___y_418_ = v___y_438_;
v___y_419_ = v___y_430_;
v___y_420_ = v___y_433_;
v___y_421_ = v___y_434_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_436_;
v___y_424_ = v___x_441_;
goto v___jp_417_;
}
else
{
v___y_418_ = v___y_438_;
v___y_419_ = v___y_430_;
v___y_420_ = v___y_433_;
v___y_421_ = v___y_434_;
v___y_422_ = v___y_435_;
v___y_423_ = v___y_436_;
v___y_424_ = v___y_437_;
goto v___jp_417_;
}
}
v___jp_442_:
{
uint64_t v___x_450_; uint64_t v___x_451_; uint8_t v___x_452_; 
v___x_450_ = 2ULL;
v___x_451_ = lean_uint64_shift_right(v___y_444_, v___x_450_);
v___x_452_ = lean_uint64_dec_eq(v___x_451_, v___y_443_);
if (v___x_452_ == 0)
{
v___y_430_ = v___y_443_;
v___y_431_ = v___y_444_;
v___y_432_ = v___x_450_;
v___y_433_ = v___y_445_;
v___y_434_ = v___y_446_;
v___y_435_ = v___y_447_;
v___y_436_ = v___y_448_;
v___y_437_ = v___y_449_;
v___y_438_ = v___x_451_;
goto v___jp_429_;
}
else
{
v___y_430_ = v___y_443_;
v___y_431_ = v___y_444_;
v___y_432_ = v___x_450_;
v___y_433_ = v___y_445_;
v___y_434_ = v___y_446_;
v___y_435_ = v___y_447_;
v___y_436_ = v___y_448_;
v___y_437_ = v___y_449_;
v___y_438_ = v___y_444_;
goto v___jp_429_;
}
}
v___jp_453_:
{
uint64_t v___x_463_; uint8_t v___x_464_; 
v___x_463_ = lean_uint64_shift_right(v___y_458_, v___y_459_);
v___x_464_ = lean_uint64_dec_eq(v___x_463_, v___y_454_);
if (v___x_464_ == 0)
{
uint64_t v___x_465_; 
v___x_465_ = lean_uint64_add(v___y_455_, v___y_459_);
v___y_443_ = v___y_454_;
v___y_444_ = v___y_462_;
v___y_445_ = v___y_456_;
v___y_446_ = v___y_457_;
v___y_447_ = v___y_460_;
v___y_448_ = v___y_461_;
v___y_449_ = v___x_465_;
goto v___jp_442_;
}
else
{
v___y_443_ = v___y_454_;
v___y_444_ = v___y_462_;
v___y_445_ = v___y_456_;
v___y_446_ = v___y_457_;
v___y_447_ = v___y_460_;
v___y_448_ = v___y_461_;
v___y_449_ = v___y_455_;
goto v___jp_442_;
}
}
v___jp_466_:
{
uint64_t v___x_474_; uint64_t v___x_475_; uint8_t v___x_476_; 
v___x_474_ = 4ULL;
v___x_475_ = lean_uint64_shift_right(v___y_470_, v___x_474_);
v___x_476_ = lean_uint64_dec_eq(v___x_475_, v___y_467_);
if (v___x_476_ == 0)
{
v___y_454_ = v___y_467_;
v___y_455_ = v___y_473_;
v___y_456_ = v___y_468_;
v___y_457_ = v___y_469_;
v___y_458_ = v___y_470_;
v___y_459_ = v___x_474_;
v___y_460_ = v___y_471_;
v___y_461_ = v___y_472_;
v___y_462_ = v___x_475_;
goto v___jp_453_;
}
else
{
v___y_454_ = v___y_467_;
v___y_455_ = v___y_473_;
v___y_456_ = v___y_468_;
v___y_457_ = v___y_469_;
v___y_458_ = v___y_470_;
v___y_459_ = v___x_474_;
v___y_460_ = v___y_471_;
v___y_461_ = v___y_472_;
v___y_462_ = v___y_470_;
goto v___jp_453_;
}
}
v___jp_477_:
{
uint64_t v___x_487_; uint8_t v___x_488_; 
v___x_487_ = lean_uint64_shift_right(v___y_478_, v___y_480_);
v___x_488_ = lean_uint64_dec_eq(v___x_487_, v___y_479_);
if (v___x_488_ == 0)
{
uint64_t v___x_489_; 
v___x_489_ = lean_uint64_add(v___y_483_, v___y_480_);
v___y_467_ = v___y_479_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_482_;
v___y_470_ = v___y_486_;
v___y_471_ = v___y_484_;
v___y_472_ = v___y_485_;
v___y_473_ = v___x_489_;
goto v___jp_466_;
}
else
{
v___y_467_ = v___y_479_;
v___y_468_ = v___y_481_;
v___y_469_ = v___y_482_;
v___y_470_ = v___y_486_;
v___y_471_ = v___y_484_;
v___y_472_ = v___y_485_;
v___y_473_ = v___y_483_;
goto v___jp_466_;
}
}
v___jp_490_:
{
uint64_t v___x_498_; uint64_t v___x_499_; uint8_t v___x_500_; 
v___x_498_ = 8ULL;
v___x_499_ = lean_uint64_shift_right(v___y_491_, v___x_498_);
v___x_500_ = lean_uint64_dec_eq(v___x_499_, v___y_492_);
if (v___x_500_ == 0)
{
v___y_478_ = v___y_491_;
v___y_479_ = v___y_492_;
v___y_480_ = v___x_498_;
v___y_481_ = v___y_493_;
v___y_482_ = v___y_494_;
v___y_483_ = v___y_497_;
v___y_484_ = v___y_495_;
v___y_485_ = v___y_496_;
v___y_486_ = v___x_499_;
goto v___jp_477_;
}
else
{
v___y_478_ = v___y_491_;
v___y_479_ = v___y_492_;
v___y_480_ = v___x_498_;
v___y_481_ = v___y_493_;
v___y_482_ = v___y_494_;
v___y_483_ = v___y_497_;
v___y_484_ = v___y_495_;
v___y_485_ = v___y_496_;
v___y_486_ = v___y_491_;
goto v___jp_477_;
}
}
v___jp_501_:
{
uint64_t v___x_511_; uint8_t v___x_512_; 
v___x_511_ = lean_uint64_shift_right(v___y_505_, v___y_506_);
v___x_512_ = lean_uint64_dec_eq(v___x_511_, v___y_502_);
if (v___x_512_ == 0)
{
uint64_t v___x_513_; 
v___x_513_ = lean_uint64_add(v___y_508_, v___y_506_);
v___y_491_ = v___y_510_;
v___y_492_ = v___y_502_;
v___y_493_ = v___y_503_;
v___y_494_ = v___y_504_;
v___y_495_ = v___y_507_;
v___y_496_ = v___y_509_;
v___y_497_ = v___x_513_;
goto v___jp_490_;
}
else
{
v___y_491_ = v___y_510_;
v___y_492_ = v___y_502_;
v___y_493_ = v___y_503_;
v___y_494_ = v___y_504_;
v___y_495_ = v___y_507_;
v___y_496_ = v___y_509_;
v___y_497_ = v___y_508_;
goto v___jp_490_;
}
}
v___jp_514_:
{
uint64_t v___x_522_; uint64_t v___x_523_; uint8_t v___x_524_; 
v___x_522_ = 16ULL;
v___x_523_ = lean_uint64_shift_right(v___y_518_, v___x_522_);
v___x_524_ = lean_uint64_dec_eq(v___x_523_, v___y_515_);
if (v___x_524_ == 0)
{
v___y_502_ = v___y_515_;
v___y_503_ = v___y_516_;
v___y_504_ = v___y_517_;
v___y_505_ = v___y_518_;
v___y_506_ = v___x_522_;
v___y_507_ = v___y_519_;
v___y_508_ = v___y_521_;
v___y_509_ = v___y_520_;
v___y_510_ = v___x_523_;
goto v___jp_501_;
}
else
{
v___y_502_ = v___y_515_;
v___y_503_ = v___y_516_;
v___y_504_ = v___y_517_;
v___y_505_ = v___y_518_;
v___y_506_ = v___x_522_;
v___y_507_ = v___y_519_;
v___y_508_ = v___y_521_;
v___y_509_ = v___y_520_;
v___y_510_ = v___y_518_;
goto v___jp_501_;
}
}
v___jp_525_:
{
uint64_t v___x_533_; uint8_t v___x_534_; 
v___x_533_ = lean_uint64_shift_right(v___y_530_, v___y_526_);
v___x_534_ = lean_uint64_dec_eq(v___x_533_, v___y_527_);
if (v___x_534_ == 0)
{
v___y_515_ = v___y_527_;
v___y_516_ = v___y_528_;
v___y_517_ = v___y_529_;
v___y_518_ = v___y_532_;
v___y_519_ = v___y_530_;
v___y_520_ = v___y_531_;
v___y_521_ = v___y_526_;
goto v___jp_514_;
}
else
{
v___y_515_ = v___y_527_;
v___y_516_ = v___y_528_;
v___y_517_ = v___y_529_;
v___y_518_ = v___y_532_;
v___y_519_ = v___y_530_;
v___y_520_ = v___y_531_;
v___y_521_ = v___y_527_;
goto v___jp_514_;
}
}
v___jp_535_:
{
uint64_t v___x_540_; uint8_t v___x_541_; 
v___x_540_ = 0ULL;
v___x_541_ = lean_uint64_dec_eq(v___y_538_, v___x_540_);
if (v___x_541_ == 0)
{
uint64_t v___x_542_; uint64_t v___x_543_; uint8_t v___x_544_; 
v___x_542_ = 32ULL;
v___x_543_ = lean_uint64_shift_right(v___y_538_, v___x_542_);
v___x_544_ = lean_uint64_dec_eq(v___x_543_, v___x_540_);
if (v___x_544_ == 0)
{
v___y_526_ = v___x_542_;
v___y_527_ = v___x_540_;
v___y_528_ = v___y_536_;
v___y_529_ = v___y_537_;
v___y_530_ = v___y_538_;
v___y_531_ = v___y_539_;
v___y_532_ = v___x_543_;
goto v___jp_525_;
}
else
{
v___y_526_ = v___x_542_;
v___y_527_ = v___x_540_;
v___y_528_ = v___y_536_;
v___y_529_ = v___y_537_;
v___y_530_ = v___y_538_;
v___y_531_ = v___y_539_;
v___y_532_ = v___y_538_;
goto v___jp_525_;
}
}
else
{
if (v___y_539_ == 0)
{
uint32_t v___x_545_; 
v___x_545_ = 0;
return v___x_545_;
}
else
{
uint32_t v___x_546_; 
v___x_546_ = 2147483648;
return v___x_546_;
}
}
}
v___jp_547_:
{
uint64_t v___x_554_; uint64_t v___x_555_; uint64_t v___x_556_; uint8_t v___x_557_; 
v___x_554_ = lean_uint64_mul(v___y_551_, v___y_548_);
v___x_555_ = lean_uint64_add(v___y_550_, v___y_553_);
v___x_556_ = 281474976710656ULL;
v___x_557_ = lean_uint64_dec_lt(v___x_554_, v___x_556_);
if (v___x_557_ == 0)
{
v___y_536_ = v___y_549_;
v___y_537_ = v___x_555_;
v___y_538_ = v___x_554_;
v___y_539_ = v___y_552_;
goto v___jp_535_;
}
else
{
uint64_t v___x_558_; uint8_t v___x_559_; 
v___x_558_ = 123ULL;
v___x_559_ = lean_uint64_dec_le(v___x_555_, v___x_558_);
if (v___x_559_ == 0)
{
v___y_536_ = v___y_549_;
v___y_537_ = v___x_555_;
v___y_538_ = v___x_554_;
v___y_539_ = v___y_552_;
goto v___jp_535_;
}
else
{
uint64_t v___x_560_; uint8_t v___x_561_; 
v___x_560_ = 0ULL;
v___x_561_ = lean_uint64_dec_eq(v___x_554_, v___x_560_);
if (v___x_561_ == 0)
{
uint64_t v___x_562_; uint64_t v___x_563_; uint8_t v___x_564_; 
v___x_562_ = 149ULL;
v___x_563_ = lean_uint64_sub(v___x_562_, v___x_555_);
v___x_564_ = lean_uint64_dec_eq(v___x_563_, v___x_560_);
if (v___x_564_ == 0)
{
uint64_t v___x_565_; uint8_t v___x_566_; 
v___x_565_ = 64ULL;
v___x_566_ = lean_uint64_dec_lt(v___x_563_, v___x_565_);
if (v___x_566_ == 0)
{
uint8_t v___x_567_; 
v___x_567_ = lean_uint64_dec_eq(v___x_563_, v___x_565_);
if (v___x_567_ == 0)
{
v___y_172_ = v___y_549_;
v___y_173_ = v___x_560_;
v___y_174_ = v___y_552_;
v___y_175_ = v___x_560_;
goto v___jp_171_;
}
else
{
uint64_t v___x_568_; uint8_t v___x_569_; 
v___x_568_ = 9223372036854775808ULL;
v___x_569_ = lean_uint64_dec_lt(v___x_568_, v___x_554_);
if (v___x_569_ == 0)
{
v___y_172_ = v___y_549_;
v___y_173_ = v___x_560_;
v___y_174_ = v___y_552_;
v___y_175_ = v___x_560_;
goto v___jp_171_;
}
else
{
uint64_t v___x_570_; 
v___x_570_ = 1ULL;
v___y_172_ = v___y_549_;
v___y_173_ = v___x_560_;
v___y_174_ = v___y_552_;
v___y_175_ = v___x_570_;
goto v___jp_171_;
}
}
}
else
{
uint64_t v_quotient_571_; uint64_t v___x_572_; uint64_t v___x_573_; uint64_t v___x_574_; uint64_t v_remainder_575_; uint64_t v___x_576_; uint64_t v_half_577_; uint8_t v___x_578_; 
v_quotient_571_ = lean_uint64_shift_right(v___x_554_, v___x_563_);
v___x_572_ = 1ULL;
v___x_573_ = lean_uint64_shift_left(v___x_572_, v___x_563_);
v___x_574_ = lean_uint64_sub(v___x_573_, v___x_572_);
v_remainder_575_ = lean_uint64_land(v___x_554_, v___x_574_);
v___x_576_ = lean_uint64_sub(v___x_563_, v___x_572_);
v_half_577_ = lean_uint64_shift_left(v___x_572_, v___x_576_);
v___x_578_ = lean_uint64_dec_lt(v_remainder_575_, v_half_577_);
if (v___x_578_ == 0)
{
uint8_t v___x_579_; 
v___x_579_ = lean_uint64_dec_lt(v_half_577_, v_remainder_575_);
if (v___x_579_ == 0)
{
uint64_t v___x_580_; uint8_t v___x_581_; 
v___x_580_ = lean_uint64_land(v_quotient_571_, v___x_572_);
v___x_581_ = lean_uint64_dec_eq(v___x_580_, v___x_560_);
if (v___x_581_ == 0)
{
uint64_t v___x_582_; 
v___x_582_ = lean_uint64_add(v_quotient_571_, v___x_572_);
v___y_172_ = v___y_549_;
v___y_173_ = v___x_560_;
v___y_174_ = v___y_552_;
v___y_175_ = v___x_582_;
goto v___jp_171_;
}
else
{
v___y_172_ = v___y_549_;
v___y_173_ = v___x_560_;
v___y_174_ = v___y_552_;
v___y_175_ = v_quotient_571_;
goto v___jp_171_;
}
}
else
{
uint64_t v___x_583_; 
v___x_583_ = lean_uint64_add(v_quotient_571_, v___x_572_);
v___y_172_ = v___y_549_;
v___y_173_ = v___x_560_;
v___y_174_ = v___y_552_;
v___y_175_ = v___x_583_;
goto v___jp_171_;
}
}
else
{
v___y_172_ = v___y_549_;
v___y_173_ = v___x_560_;
v___y_174_ = v___y_552_;
v___y_175_ = v_quotient_571_;
goto v___jp_171_;
}
}
}
else
{
v___y_172_ = v___y_549_;
v___y_173_ = v___x_560_;
v___y_174_ = v___y_552_;
v___y_175_ = v___x_554_;
goto v___jp_171_;
}
}
else
{
if (v___y_552_ == 0)
{
uint32_t v___x_584_; 
v___x_584_ = 0;
return v___x_584_;
}
else
{
uint32_t v___x_585_; 
v___x_585_ = 2147483648;
return v___x_585_;
}
}
}
}
}
v___jp_589_:
{
uint64_t v___x_595_; uint64_t v___x_596_; uint8_t v___x_597_; 
v___x_595_ = lean_uint32_to_uint64(v_ey_588_);
v___x_596_ = 0ULL;
v___x_597_ = lean_uint64_dec_eq(v___x_595_, v___x_596_);
if (v___x_597_ == 0)
{
uint64_t v___x_598_; uint64_t v___x_599_; 
v___x_598_ = 1ULL;
v___x_599_ = lean_uint64_sub(v___x_595_, v___x_598_);
v___y_548_ = v___y_590_;
v___y_549_ = v___y_591_;
v___y_550_ = v___y_594_;
v___y_551_ = v___y_592_;
v___y_552_ = v___y_593_;
v___y_553_ = v___x_599_;
goto v___jp_547_;
}
else
{
v___y_548_ = v___y_590_;
v___y_549_ = v___y_591_;
v___y_550_ = v___y_594_;
v___y_551_ = v___y_592_;
v___y_552_ = v___y_593_;
v___y_553_ = v___x_596_;
goto v___jp_547_;
}
}
v___jp_600_:
{
uint64_t v___x_605_; uint64_t v___x_606_; uint8_t v___x_607_; 
v___x_605_ = lean_uint32_to_uint64(v_ex_586_);
v___x_606_ = 0ULL;
v___x_607_ = lean_uint64_dec_eq(v___x_605_, v___x_606_);
if (v___x_607_ == 0)
{
uint64_t v___x_608_; uint64_t v___x_609_; 
v___x_608_ = 1ULL;
v___x_609_ = lean_uint64_sub(v___x_605_, v___x_608_);
v___y_590_ = v___y_604_;
v___y_591_ = v___y_601_;
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v___x_609_;
goto v___jp_589_;
}
else
{
v___y_590_ = v___y_604_;
v___y_591_ = v___y_601_;
v___y_592_ = v___y_602_;
v___y_593_ = v___y_603_;
v___y_594_ = v___x_606_;
goto v___jp_589_;
}
}
v___jp_610_:
{
uint32_t v___x_615_; uint8_t v___x_616_; 
v___x_615_ = 0;
v___x_616_ = lean_uint32_dec_eq(v_ey_588_, v___x_615_);
if (v___x_616_ == 0)
{
uint64_t v___x_617_; uint64_t v___x_618_; uint64_t v___x_619_; 
v___x_617_ = lean_uint32_to_uint64(v___y_612_);
v___x_618_ = 8388608ULL;
v___x_619_ = lean_uint64_lor(v___x_617_, v___x_618_);
v___y_601_ = v___y_611_;
v___y_602_ = v___y_614_;
v___y_603_ = v___y_613_;
v___y_604_ = v___x_619_;
goto v___jp_600_;
}
else
{
uint64_t v___x_620_; 
v___x_620_ = lean_uint32_to_uint64(v___y_612_);
v___y_601_ = v___y_611_;
v___y_602_ = v___y_614_;
v___y_603_ = v___y_613_;
v___y_604_ = v___x_620_;
goto v___jp_600_;
}
}
v___jp_621_:
{
uint32_t v___x_623_; uint32_t v_xFraction_624_; uint32_t v_yFraction_625_; uint32_t v___x_626_; uint8_t v___x_627_; 
v___x_623_ = 8388607;
v_xFraction_624_ = lean_uint32_land(v___y_134_, v___x_623_);
v_yFraction_625_ = lean_uint32_land(v___y_135_, v___x_623_);
v___x_626_ = 0;
v___x_627_ = lean_uint32_dec_eq(v_ex_586_, v___x_626_);
if (v___x_627_ == 0)
{
uint64_t v___x_628_; uint64_t v___x_629_; uint64_t v___x_630_; 
v___x_628_ = lean_uint32_to_uint64(v_xFraction_624_);
v___x_629_ = 8388608ULL;
v___x_630_ = lean_uint64_lor(v___x_628_, v___x_629_);
v___y_611_ = v___x_623_;
v___y_612_ = v_yFraction_625_;
v___y_613_ = v___y_622_;
v___y_614_ = v___x_630_;
goto v___jp_610_;
}
else
{
uint64_t v___x_631_; 
v___x_631_ = lean_uint32_to_uint64(v_xFraction_624_);
v___y_611_ = v___x_623_;
v___y_612_ = v_yFraction_625_;
v___y_613_ = v___y_622_;
v___y_614_ = v___x_631_;
goto v___jp_610_;
}
}
v___jp_635_:
{
if (v___y_637_ == 0)
{
v___y_622_ = v___x_634_;
goto v___jp_621_;
}
else
{
v___y_622_ = v___y_636_;
goto v___jp_621_;
}
}
v___jp_638_:
{
if (v___y_640_ == 0)
{
if (v___y_641_ == 0)
{
v___y_636_ = v___y_639_;
v___y_637_ = v___x_634_;
goto v___jp_635_;
}
else
{
v___y_622_ = v___x_634_;
goto v___jp_621_;
}
}
else
{
v___y_636_ = v___y_639_;
v___y_637_ = v___y_641_;
goto v___jp_635_;
}
}
v___jp_642_:
{
uint32_t v___x_645_; uint32_t v___x_646_; uint32_t v___x_647_; uint8_t v___x_648_; 
v___x_645_ = 2147483648;
v___x_646_ = lean_uint32_land(v___y_135_, v___x_645_);
v___x_647_ = 0;
v___x_648_ = lean_uint32_dec_eq(v___x_646_, v___x_647_);
if (v___x_648_ == 0)
{
v___y_639_ = v___y_643_;
v___y_640_ = v___y_644_;
v___y_641_ = v___x_634_;
goto v___jp_638_;
}
else
{
v___y_639_ = v___y_643_;
v___y_640_ = v___y_644_;
v___y_641_ = v___y_643_;
goto v___jp_638_;
}
}
v___jp_649_:
{
if (v___y_650_ == 0)
{
uint32_t v___x_651_; uint32_t v___x_652_; uint32_t v___x_653_; uint8_t v___x_654_; 
v___x_651_ = 2147483648;
v___x_652_ = lean_uint32_land(v___y_134_, v___x_651_);
v___x_653_ = 0;
v___x_654_ = lean_uint32_dec_eq(v___x_652_, v___x_653_);
if (v___x_654_ == 0)
{
v___y_643_ = v___y_650_;
v___y_644_ = v___x_634_;
goto v___jp_642_;
}
else
{
v___y_643_ = v___y_650_;
v___y_644_ = v___y_650_;
goto v___jp_642_;
}
}
else
{
lean_object* v___x_655_; lean_object* v___x_656_; lean_object* v___x_657_; uint32_t v___x_658_; 
v___x_655_ = lean_uint32_to_nat(v___y_134_);
v___x_656_ = lean_uint32_to_nat(v___y_135_);
v___x_657_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_655_, v___x_656_);
v___x_658_ = lean_uint32_of_nat(v___x_657_);
lean_dec(v___x_657_);
return v___x_658_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_673_, lean_object* v___y_674_){
_start:
{
uint32_t v___y_4155__boxed_675_; uint32_t v___y_4156__boxed_676_; uint32_t v_res_677_; lean_object* v_r_678_; 
v___y_4155__boxed_675_ = lean_unbox_uint32(v___y_673_);
lean_dec(v___y_673_);
v___y_4156__boxed_676_ = lean_unbox_uint32(v___y_674_);
lean_dec(v___y_674_);
v_res_677_ = lp_competition_main___lam__1(v___y_4155__boxed_675_, v___y_4156__boxed_676_);
v_r_678_ = lean_box_uint32(v_res_677_);
return v_r_678_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__3(uint32_t v___y_679_, uint32_t v___y_680_){
_start:
{
uint32_t v___y_682_; uint32_t v___y_683_; uint32_t v___y_684_; uint32_t v___y_688_; uint32_t v___y_689_; uint32_t v___y_690_; uint32_t v___y_694_; uint64_t v___y_698_; uint32_t v___y_699_; uint8_t v___y_700_; uint64_t v___y_701_; uint32_t v___y_713_; uint64_t v___y_717_; uint32_t v___y_718_; uint8_t v___y_719_; uint64_t v___y_720_; float v___y_732_; uint8_t v___y_733_; float v___y_738_; float v___y_750_; uint8_t v___y_751_; float v___y_755_; float v___y_766_; uint8_t v___y_767_; float v___y_774_; float v___y_785_; uint8_t v___y_786_; float v___y_793_; float v___y_794_; float v___y_808_; uint8_t v___y_809_; float v___y_824_; uint32_t v___x_833_; uint32_t v___x_834_; uint8_t v___y_836_; uint32_t v___x_848_; uint32_t v___y_850_; uint32_t v___y_851_; uint32_t v___y_852_; uint32_t v___y_853_; uint32_t v___y_860_; uint32_t v___y_861_; uint8_t v___y_862_; uint32_t v___y_863_; uint64_t v___y_867_; uint32_t v___y_868_; uint64_t v___y_869_; uint8_t v___y_870_; uint64_t v___y_871_; uint64_t v___y_881_; uint8_t v___y_882_; uint64_t v___y_883_; uint32_t v___y_884_; uint8_t v___y_885_; uint64_t v___y_886_; uint64_t v___y_893_; uint64_t v___y_894_; uint32_t v___y_895_; uint8_t v___y_896_; uint64_t v___y_897_; uint64_t v___y_903_; uint64_t v___y_904_; uint32_t v___y_905_; uint64_t v___y_906_; uint8_t v___y_907_; uint64_t v___y_908_; uint64_t v___y_963_; uint64_t v___y_964_; uint64_t v___y_965_; uint32_t v___y_966_; uint64_t v___y_967_; uint8_t v___y_968_; uint64_t v___y_969_; uint64_t v___y_975_; uint64_t v___y_976_; uint64_t v___y_977_; uint64_t v___y_978_; uint64_t v___y_979_; uint32_t v___y_980_; uint64_t v___y_981_; uint8_t v___y_982_; uint64_t v___y_983_; uint64_t v___y_988_; uint64_t v___y_989_; uint64_t v___y_990_; uint32_t v___y_991_; uint64_t v___y_992_; uint8_t v___y_993_; uint64_t v___y_994_; uint64_t v___y_999_; uint64_t v___y_1000_; uint64_t v___y_1001_; uint32_t v___y_1002_; uint64_t v___y_1003_; uint64_t v___y_1004_; uint64_t v___y_1005_; uint8_t v___y_1006_; uint64_t v___y_1007_; uint64_t v___y_1012_; uint64_t v___y_1013_; uint32_t v___y_1014_; uint64_t v___y_1015_; uint64_t v___y_1016_; uint8_t v___y_1017_; uint64_t v___y_1018_; uint64_t v___y_1023_; uint64_t v___y_1024_; uint64_t v___y_1025_; uint64_t v___y_1026_; uint32_t v___y_1027_; uint64_t v___y_1028_; uint64_t v___y_1029_; uint8_t v___y_1030_; uint64_t v___y_1031_; uint64_t v___y_1036_; uint64_t v___y_1037_; uint64_t v___y_1038_; uint32_t v___y_1039_; uint64_t v___y_1040_; uint8_t v___y_1041_; uint64_t v___y_1042_; uint64_t v___y_1047_; uint64_t v___y_1048_; uint64_t v___y_1049_; uint64_t v___y_1050_; uint32_t v___y_1051_; uint64_t v___y_1052_; uint64_t v___y_1053_; uint8_t v___y_1054_; uint64_t v___y_1055_; uint64_t v___y_1060_; uint64_t v___y_1061_; uint64_t v___y_1062_; uint32_t v___y_1063_; uint64_t v___y_1064_; uint8_t v___y_1065_; uint64_t v___y_1066_; uint64_t v___y_1071_; uint64_t v___y_1072_; uint64_t v___y_1073_; uint32_t v___y_1074_; uint64_t v___y_1075_; uint8_t v___y_1076_; uint64_t v___y_1077_; uint64_t v___y_1081_; uint32_t v___y_1082_; uint64_t v___y_1083_; uint8_t v___y_1084_; uint64_t v___y_1093_; uint64_t v___y_1094_; uint32_t v___y_1095_; uint8_t v___y_1096_; uint64_t v___y_1097_; uint64_t v___y_1098_; uint32_t v_ex_1131_; uint32_t v___x_1132_; uint32_t v_ey_1133_; uint64_t v___y_1135_; uint32_t v___y_1136_; uint64_t v___y_1137_; uint8_t v___y_1138_; uint64_t v___y_1139_; uint32_t v___y_1146_; uint8_t v___y_1147_; uint64_t v___y_1148_; uint64_t v___y_1149_; uint32_t v___y_1156_; uint32_t v___y_1157_; uint8_t v___y_1158_; uint64_t v___y_1159_; uint8_t v___y_1167_; uint32_t v___x_1177_; uint32_t v___x_1178_; uint8_t v___x_1179_; uint8_t v___y_1181_; uint8_t v___y_1182_; uint8_t v___y_1184_; uint8_t v___y_1185_; uint8_t v___y_1186_; uint8_t v___y_1188_; uint8_t v___y_1189_; uint8_t v___y_1195_; 
v___x_833_ = 23;
v___x_834_ = lean_uint32_shift_right(v___y_679_, v___x_833_);
v___x_848_ = 255;
v_ex_1131_ = lean_uint32_land(v___x_834_, v___x_848_);
v___x_1132_ = lean_uint32_shift_right(v___y_680_, v___x_833_);
v_ey_1133_ = lean_uint32_land(v___x_1132_, v___x_848_);
v___x_1177_ = lean_uint32_add(v_ex_1131_, v_ey_1133_);
v___x_1178_ = 128;
v___x_1179_ = lean_uint32_dec_lt(v___x_1177_, v___x_1178_);
if (v___x_1179_ == 0)
{
uint32_t v___x_1204_; uint32_t v_a_1205_; uint32_t v___x_1206_; uint32_t v___x_1207_; uint32_t v___x_1208_; uint8_t v___x_1209_; 
v___x_1204_ = 2147483647;
v_a_1205_ = lean_uint32_land(v___y_679_, v___x_1204_);
v___x_1206_ = 201326591;
v___x_1207_ = 1;
v___x_1208_ = lean_uint32_sub(v_a_1205_, v___x_1207_);
v___x_1209_ = lean_uint32_dec_le(v___x_1206_, v___x_1208_);
if (v___x_1209_ == 0)
{
v___y_836_ = v___x_1209_;
goto v___jp_835_;
}
else
{
uint32_t v___x_1210_; uint8_t v___x_1211_; 
v___x_1210_ = 2139095040;
v___x_1211_ = lean_uint32_dec_lt(v_a_1205_, v___x_1210_);
v___y_836_ = v___x_1211_;
goto v___jp_835_;
}
}
else
{
uint32_t v___x_1212_; uint32_t v___x_1213_; uint32_t v___x_1214_; uint8_t v___x_1215_; 
v___x_1212_ = 4278190080;
v___x_1213_ = 1;
v___x_1214_ = lean_uint32_shift_left(v___y_679_, v___x_1213_);
v___x_1215_ = lean_uint32_dec_le(v___x_1212_, v___x_1214_);
if (v___x_1215_ == 0)
{
uint32_t v___x_1216_; uint8_t v___x_1217_; 
v___x_1216_ = lean_uint32_shift_left(v___y_680_, v___x_1213_);
v___x_1217_ = lean_uint32_dec_le(v___x_1212_, v___x_1216_);
v___y_1195_ = v___x_1217_;
goto v___jp_1194_;
}
else
{
v___y_1195_ = v___x_1215_;
goto v___jp_1194_;
}
}
v___jp_681_:
{
uint32_t v___x_685_; uint32_t v___x_686_; 
v___x_685_ = lean_uint32_land(v___y_682_, v___y_683_);
v___x_686_ = lean_uint32_lor(v___y_684_, v___x_685_);
return v___x_686_;
}
v___jp_687_:
{
uint32_t v___x_691_; uint32_t v___x_692_; 
v___x_691_ = lean_uint32_land(v___y_688_, v___y_689_);
v___x_692_ = lean_uint32_lor(v___y_690_, v___x_691_);
return v___x_692_;
}
v___jp_693_:
{
uint32_t v___x_695_; uint32_t v___x_696_; 
v___x_695_ = 8388608;
v___x_696_ = lean_uint32_lor(v___y_694_, v___x_695_);
return v___x_696_;
}
v___jp_697_:
{
uint8_t v___x_702_; 
v___x_702_ = lean_uint64_dec_eq(v___y_701_, v___y_698_);
if (v___x_702_ == 0)
{
uint64_t v___x_703_; uint8_t v___x_704_; 
v___x_703_ = 8388608ULL;
v___x_704_ = lean_uint64_dec_eq(v___y_701_, v___x_703_);
if (v___x_704_ == 0)
{
uint32_t v___x_705_; 
v___x_705_ = lean_uint64_to_uint32(v___y_701_);
if (v___y_700_ == 0)
{
uint32_t v___x_706_; 
v___x_706_ = 0;
v___y_688_ = v___x_705_;
v___y_689_ = v___y_699_;
v___y_690_ = v___x_706_;
goto v___jp_687_;
}
else
{
uint32_t v___x_707_; 
v___x_707_ = 2147483648;
v___y_688_ = v___x_705_;
v___y_689_ = v___y_699_;
v___y_690_ = v___x_707_;
goto v___jp_687_;
}
}
else
{
if (v___y_700_ == 0)
{
uint32_t v___x_708_; 
v___x_708_ = 0;
v___y_694_ = v___x_708_;
goto v___jp_693_;
}
else
{
uint32_t v___x_709_; 
v___x_709_ = 2147483648;
v___y_694_ = v___x_709_;
goto v___jp_693_;
}
}
}
else
{
if (v___y_700_ == 0)
{
uint32_t v___x_710_; 
v___x_710_ = 0;
return v___x_710_;
}
else
{
uint32_t v___x_711_; 
v___x_711_ = 2147483648;
return v___x_711_;
}
}
}
v___jp_712_:
{
uint32_t v___x_714_; uint32_t v___x_715_; 
v___x_714_ = 8388608;
v___x_715_ = lean_uint32_lor(v___y_713_, v___x_714_);
return v___x_715_;
}
v___jp_716_:
{
uint8_t v___x_721_; 
v___x_721_ = lean_uint64_dec_eq(v___y_720_, v___y_717_);
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
v___y_682_ = v___x_724_;
v___y_683_ = v___y_718_;
v___y_684_ = v___x_725_;
goto v___jp_681_;
}
else
{
uint32_t v___x_726_; 
v___x_726_ = 2147483648;
v___y_682_ = v___x_724_;
v___y_683_ = v___y_718_;
v___y_684_ = v___x_726_;
goto v___jp_681_;
}
}
else
{
if (v___y_719_ == 0)
{
uint32_t v___x_727_; 
v___x_727_ = 0;
v___y_713_ = v___x_727_;
goto v___jp_712_;
}
else
{
uint32_t v___x_728_; 
v___x_728_ = 2147483648;
v___y_713_ = v___x_728_;
goto v___jp_712_;
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
if (v___y_733_ == 0)
{
uint32_t v___x_734_; 
v___x_734_ = lean_float32_to_bits(v___y_732_);
return v___x_734_;
}
else
{
uint32_t v___x_735_; uint32_t v___x_736_; 
v___x_735_ = 4194304;
v___x_736_ = lean_uint32_lor(v___y_680_, v___x_735_);
return v___x_736_;
}
}
v___jp_737_:
{
uint32_t v___x_739_; uint32_t v___x_740_; uint32_t v___x_741_; uint32_t v___x_742_; uint8_t v___x_743_; 
v___x_739_ = 23;
v___x_740_ = lean_uint32_shift_right(v___y_680_, v___x_739_);
v___x_741_ = 255;
v___x_742_ = lean_uint32_land(v___x_740_, v___x_741_);
v___x_743_ = lean_uint32_dec_eq(v___x_742_, v___x_741_);
if (v___x_743_ == 0)
{
v___y_732_ = v___y_738_;
v___y_733_ = v___x_743_;
goto v___jp_731_;
}
else
{
uint32_t v___x_744_; uint32_t v___x_745_; uint32_t v___x_746_; uint8_t v___x_747_; 
v___x_744_ = 8388607;
v___x_745_ = lean_uint32_land(v___y_680_, v___x_744_);
v___x_746_ = 0;
v___x_747_ = lean_uint32_dec_eq(v___x_745_, v___x_746_);
if (v___x_747_ == 0)
{
v___y_732_ = v___y_738_;
v___y_733_ = v___x_743_;
goto v___jp_731_;
}
else
{
uint32_t v___x_748_; 
v___x_748_ = lean_float32_to_bits(v___y_738_);
return v___x_748_;
}
}
}
v___jp_749_:
{
if (v___y_751_ == 0)
{
v___y_738_ = v___y_750_;
goto v___jp_737_;
}
else
{
uint32_t v___x_752_; uint32_t v___x_753_; 
v___x_752_ = 4194304;
v___x_753_ = lean_uint32_lor(v___y_679_, v___x_752_);
return v___x_753_;
}
}
v___jp_754_:
{
uint32_t v___x_756_; uint32_t v___x_757_; uint32_t v___x_758_; uint32_t v___x_759_; uint8_t v___x_760_; 
v___x_756_ = 23;
v___x_757_ = lean_uint32_shift_right(v___y_679_, v___x_756_);
v___x_758_ = 255;
v___x_759_ = lean_uint32_land(v___x_757_, v___x_758_);
v___x_760_ = lean_uint32_dec_eq(v___x_759_, v___x_758_);
if (v___x_760_ == 0)
{
v___y_750_ = v___y_755_;
v___y_751_ = v___x_760_;
goto v___jp_749_;
}
else
{
uint32_t v___x_761_; uint32_t v___x_762_; uint32_t v___x_763_; uint8_t v___x_764_; 
v___x_761_ = 8388607;
v___x_762_ = lean_uint32_land(v___y_679_, v___x_761_);
v___x_763_ = 0;
v___x_764_ = lean_uint32_dec_eq(v___x_762_, v___x_763_);
if (v___x_764_ == 0)
{
v___y_750_ = v___y_755_;
v___y_751_ = v___x_760_;
goto v___jp_749_;
}
else
{
v___y_738_ = v___y_755_;
goto v___jp_737_;
}
}
}
v___jp_765_:
{
if (v___y_767_ == 0)
{
v___y_755_ = v___y_766_;
goto v___jp_754_;
}
else
{
uint32_t v___x_768_; uint32_t v___x_769_; uint32_t v___x_770_; uint8_t v___x_771_; 
v___x_768_ = 4194304;
v___x_769_ = lean_uint32_land(v___y_680_, v___x_768_);
v___x_770_ = 0;
v___x_771_ = lean_uint32_dec_eq(v___x_769_, v___x_770_);
if (v___x_771_ == 0)
{
v___y_755_ = v___y_766_;
goto v___jp_754_;
}
else
{
uint32_t v___x_772_; 
v___x_772_ = lean_uint32_lor(v___y_680_, v___x_768_);
return v___x_772_;
}
}
}
v___jp_773_:
{
uint32_t v___x_775_; uint32_t v___x_776_; uint32_t v___x_777_; uint32_t v___x_778_; uint8_t v___x_779_; 
v___x_775_ = 23;
v___x_776_ = lean_uint32_shift_right(v___y_680_, v___x_775_);
v___x_777_ = 255;
v___x_778_ = lean_uint32_land(v___x_776_, v___x_777_);
v___x_779_ = lean_uint32_dec_eq(v___x_778_, v___x_777_);
if (v___x_779_ == 0)
{
v___y_766_ = v___y_774_;
v___y_767_ = v___x_779_;
goto v___jp_765_;
}
else
{
uint32_t v___x_780_; uint32_t v___x_781_; uint32_t v___x_782_; uint8_t v___x_783_; 
v___x_780_ = 8388607;
v___x_781_ = lean_uint32_land(v___y_680_, v___x_780_);
v___x_782_ = 0;
v___x_783_ = lean_uint32_dec_eq(v___x_781_, v___x_782_);
if (v___x_783_ == 0)
{
v___y_766_ = v___y_774_;
v___y_767_ = v___x_779_;
goto v___jp_765_;
}
else
{
v___y_755_ = v___y_774_;
goto v___jp_754_;
}
}
}
v___jp_784_:
{
if (v___y_786_ == 0)
{
v___y_774_ = v___y_785_;
goto v___jp_773_;
}
else
{
uint32_t v___x_787_; uint32_t v___x_788_; uint32_t v___x_789_; uint8_t v___x_790_; 
v___x_787_ = 4194304;
v___x_788_ = lean_uint32_land(v___y_679_, v___x_787_);
v___x_789_ = 0;
v___x_790_ = lean_uint32_dec_eq(v___x_788_, v___x_789_);
if (v___x_790_ == 0)
{
v___y_774_ = v___y_785_;
goto v___jp_773_;
}
else
{
uint32_t v___x_791_; 
v___x_791_ = lean_uint32_lor(v___y_679_, v___x_787_);
return v___x_791_;
}
}
}
v___jp_792_:
{
float v_result_795_; uint8_t v___x_796_; 
v_result_795_ = lean_float32_mul(v___y_793_, v___y_794_);
v___x_796_ = lean_float32_beq(v_result_795_, v_result_795_);
if (v___x_796_ == 0)
{
uint32_t v___x_797_; uint32_t v___x_798_; uint32_t v___x_799_; uint32_t v___x_800_; uint8_t v___x_801_; 
v___x_797_ = 23;
v___x_798_ = lean_uint32_shift_right(v___y_679_, v___x_797_);
v___x_799_ = 255;
v___x_800_ = lean_uint32_land(v___x_798_, v___x_799_);
v___x_801_ = lean_uint32_dec_eq(v___x_800_, v___x_799_);
if (v___x_801_ == 0)
{
v___y_785_ = v_result_795_;
v___y_786_ = v___x_801_;
goto v___jp_784_;
}
else
{
uint32_t v___x_802_; uint32_t v___x_803_; uint32_t v___x_804_; uint8_t v___x_805_; 
v___x_802_ = 8388607;
v___x_803_ = lean_uint32_land(v___y_679_, v___x_802_);
v___x_804_ = 0;
v___x_805_ = lean_uint32_dec_eq(v___x_803_, v___x_804_);
if (v___x_805_ == 0)
{
v___y_785_ = v_result_795_;
v___y_786_ = v___x_801_;
goto v___jp_784_;
}
else
{
v___y_774_ = v_result_795_;
goto v___jp_773_;
}
}
}
else
{
uint32_t v___x_806_; 
v___x_806_ = lean_float32_to_bits(v_result_795_);
return v___x_806_;
}
}
v___jp_807_:
{
if (v___y_809_ == 0)
{
float v___x_810_; 
v___x_810_ = lean_float32_of_bits(v___y_680_);
v___y_793_ = v___y_808_;
v___y_794_ = v___x_810_;
goto v___jp_792_;
}
else
{
uint32_t v___x_811_; uint32_t v___x_812_; uint32_t v___x_813_; uint32_t v___x_814_; float v___x_815_; lean_object* v___x_816_; uint32_t v___x_817_; uint32_t v___x_818_; lean_object* v___x_819_; lean_object* v___x_820_; float v___x_821_; float v___x_822_; 
v___x_811_ = 8388607;
v___x_812_ = lean_uint32_land(v___y_680_, v___x_811_);
v___x_813_ = 8388608;
v___x_814_ = lean_uint32_lor(v___x_812_, v___x_813_);
v___x_815_ = lean_uint32_to_float32(v___x_814_);
v___x_816_ = lp_competition_R2W01b_scaleTable;
v___x_817_ = 23;
v___x_818_ = lean_uint32_shift_right(v___y_680_, v___x_817_);
v___x_819_ = lean_uint32_to_nat(v___x_818_);
v___x_820_ = lean_array_fget_borrowed(v___x_816_, v___x_819_);
lean_dec(v___x_819_);
v___x_821_ = lean_unbox_float32(v___x_820_);
v___x_822_ = lean_float32_mul(v___x_815_, v___x_821_);
v___y_793_ = v___y_808_;
v___y_794_ = v___x_822_;
goto v___jp_792_;
}
}
v___jp_823_:
{
uint32_t v___x_825_; uint32_t v_a_826_; uint32_t v___x_827_; uint32_t v___x_828_; uint32_t v___x_829_; uint8_t v___x_830_; 
v___x_825_ = 2147483647;
v_a_826_ = lean_uint32_land(v___y_680_, v___x_825_);
v___x_827_ = 201326591;
v___x_828_ = 1;
v___x_829_ = lean_uint32_sub(v_a_826_, v___x_828_);
v___x_830_ = lean_uint32_dec_le(v___x_827_, v___x_829_);
if (v___x_830_ == 0)
{
v___y_808_ = v___y_824_;
v___y_809_ = v___x_830_;
goto v___jp_807_;
}
else
{
uint32_t v___x_831_; uint8_t v___x_832_; 
v___x_831_ = 2139095040;
v___x_832_ = lean_uint32_dec_lt(v_a_826_, v___x_831_);
v___y_808_ = v___y_824_;
v___y_809_ = v___x_832_;
goto v___jp_807_;
}
}
v___jp_835_:
{
if (v___y_836_ == 0)
{
float v___x_837_; 
v___x_837_ = lean_float32_of_bits(v___y_679_);
v___y_824_ = v___x_837_;
goto v___jp_823_;
}
else
{
uint32_t v___x_838_; uint32_t v___x_839_; uint32_t v___x_840_; uint32_t v___x_841_; float v___x_842_; lean_object* v___x_843_; lean_object* v___x_844_; lean_object* v___x_845_; float v___x_846_; float v___x_847_; 
v___x_838_ = 8388607;
v___x_839_ = lean_uint32_land(v___y_679_, v___x_838_);
v___x_840_ = 8388608;
v___x_841_ = lean_uint32_lor(v___x_839_, v___x_840_);
v___x_842_ = lean_uint32_to_float32(v___x_841_);
v___x_843_ = lp_competition_R2W01b_scaleTable;
v___x_844_ = lean_uint32_to_nat(v___x_834_);
v___x_845_ = lean_array_fget_borrowed(v___x_843_, v___x_844_);
lean_dec(v___x_844_);
v___x_846_ = lean_unbox_float32(v___x_845_);
v___x_847_ = lean_float32_mul(v___x_842_, v___x_846_);
v___y_824_ = v___x_847_;
goto v___jp_823_;
}
}
v___jp_849_:
{
uint32_t v___x_854_; uint32_t v___x_855_; uint32_t v___x_856_; uint32_t v___x_857_; uint32_t v___x_858_; 
v___x_854_ = lean_uint32_land(v___y_851_, v___x_848_);
v___x_855_ = lean_uint32_shift_left(v___x_854_, v___x_833_);
v___x_856_ = lean_uint32_lor(v___y_853_, v___x_855_);
v___x_857_ = lean_uint32_land(v___y_852_, v___y_850_);
v___x_858_ = lean_uint32_lor(v___x_856_, v___x_857_);
return v___x_858_;
}
v___jp_859_:
{
if (v___y_862_ == 0)
{
uint32_t v___x_864_; 
v___x_864_ = 0;
v___y_850_ = v___y_861_;
v___y_851_ = v___y_860_;
v___y_852_ = v___y_863_;
v___y_853_ = v___x_864_;
goto v___jp_849_;
}
else
{
uint32_t v___x_865_; 
v___x_865_ = 2147483648;
v___y_850_ = v___y_861_;
v___y_851_ = v___y_860_;
v___y_852_ = v___y_863_;
v___y_853_ = v___x_865_;
goto v___jp_849_;
}
}
v___jp_866_:
{
uint64_t v___x_872_; uint64_t v_encodedExponent_873_; uint32_t v___x_874_; uint64_t v___x_875_; uint8_t v___x_876_; 
v___x_872_ = 171ULL;
v_encodedExponent_873_ = lean_uint64_sub(v___y_869_, v___x_872_);
v___x_874_ = lean_uint64_to_uint32(v_encodedExponent_873_);
v___x_875_ = 8388608ULL;
v___x_876_ = lean_uint64_dec_lt(v___y_871_, v___x_875_);
if (v___x_876_ == 0)
{
uint64_t v___x_877_; uint32_t v___x_878_; 
v___x_877_ = lean_uint64_sub(v___y_871_, v___x_875_);
v___x_878_ = lean_uint64_to_uint32(v___x_877_);
v___y_860_ = v___x_874_;
v___y_861_ = v___y_868_;
v___y_862_ = v___y_870_;
v___y_863_ = v___x_878_;
goto v___jp_859_;
}
else
{
uint32_t v___x_879_; 
v___x_879_ = lean_uint64_to_uint32(v___y_867_);
v___y_860_ = v___x_874_;
v___y_861_ = v___y_868_;
v___y_862_ = v___y_870_;
v___y_863_ = v___x_879_;
goto v___jp_859_;
}
}
v___jp_880_:
{
uint64_t v___x_887_; uint8_t v___x_888_; 
v___x_887_ = 425ULL;
v___x_888_ = lean_uint64_dec_lt(v___x_887_, v___y_886_);
if (v___x_888_ == 0)
{
if (v___y_882_ == 0)
{
v___y_867_ = v___y_883_;
v___y_868_ = v___y_884_;
v___y_869_ = v___y_886_;
v___y_870_ = v___y_885_;
v___y_871_ = v___y_881_;
goto v___jp_866_;
}
else
{
uint64_t v___x_889_; 
v___x_889_ = 8388608ULL;
v___y_867_ = v___y_883_;
v___y_868_ = v___y_884_;
v___y_869_ = v___y_886_;
v___y_870_ = v___y_885_;
v___y_871_ = v___x_889_;
goto v___jp_866_;
}
}
else
{
if (v___y_885_ == 0)
{
uint32_t v___x_890_; 
v___x_890_ = 2139095040;
return v___x_890_;
}
else
{
uint32_t v___x_891_; 
v___x_891_ = 4286578688;
return v___x_891_;
}
}
}
v___jp_892_:
{
uint64_t v___x_898_; uint8_t v_carry_899_; 
v___x_898_ = 16777216ULL;
v_carry_899_ = lean_uint64_dec_eq(v___y_897_, v___x_898_);
if (v_carry_899_ == 0)
{
v___y_881_ = v___y_897_;
v___y_882_ = v_carry_899_;
v___y_883_ = v___y_894_;
v___y_884_ = v___y_895_;
v___y_885_ = v___y_896_;
v___y_886_ = v___y_893_;
goto v___jp_880_;
}
else
{
uint64_t v___x_900_; uint64_t v___x_901_; 
v___x_900_ = 1ULL;
v___x_901_ = lean_uint64_add(v___y_893_, v___x_900_);
v___y_881_ = v___y_897_;
v___y_882_ = v_carry_899_;
v___y_883_ = v___y_894_;
v___y_884_ = v___y_895_;
v___y_885_ = v___y_896_;
v___y_886_ = v___x_901_;
goto v___jp_880_;
}
}
v___jp_902_:
{
uint64_t v_position_909_; uint64_t v___x_910_; uint8_t v___x_911_; 
v_position_909_ = lean_uint64_add(v___y_908_, v___y_903_);
v___x_910_ = 172ULL;
v___x_911_ = lean_uint64_dec_lt(v_position_909_, v___x_910_);
if (v___x_911_ == 0)
{
uint64_t v___x_912_; uint8_t v___x_913_; 
v___x_912_ = 23ULL;
v___x_913_ = lean_uint64_dec_lt(v___y_908_, v___x_912_);
if (v___x_913_ == 0)
{
uint64_t v___x_914_; uint8_t v___x_915_; 
v___x_914_ = lean_uint64_sub(v___y_908_, v___x_912_);
v___x_915_ = lean_uint64_dec_eq(v___x_914_, v___y_904_);
if (v___x_915_ == 0)
{
uint64_t v___x_916_; uint8_t v___x_917_; 
v___x_916_ = 64ULL;
v___x_917_ = lean_uint64_dec_lt(v___x_914_, v___x_916_);
if (v___x_917_ == 0)
{
uint8_t v___x_918_; 
v___x_918_ = lean_uint64_dec_eq(v___x_914_, v___x_916_);
if (v___x_918_ == 0)
{
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v___y_904_;
goto v___jp_892_;
}
else
{
uint64_t v___x_919_; uint8_t v___x_920_; 
v___x_919_ = 9223372036854775808ULL;
v___x_920_ = lean_uint64_dec_lt(v___x_919_, v___y_906_);
if (v___x_920_ == 0)
{
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v___y_904_;
goto v___jp_892_;
}
else
{
uint64_t v___x_921_; 
v___x_921_ = 1ULL;
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v___x_921_;
goto v___jp_892_;
}
}
}
else
{
uint64_t v_quotient_922_; uint64_t v___x_923_; uint64_t v___x_924_; uint64_t v___x_925_; uint64_t v_remainder_926_; uint64_t v___x_927_; uint64_t v_half_928_; uint8_t v___x_929_; 
v_quotient_922_ = lean_uint64_shift_right(v___y_906_, v___x_914_);
v___x_923_ = 1ULL;
v___x_924_ = lean_uint64_shift_left(v___x_923_, v___x_914_);
v___x_925_ = lean_uint64_sub(v___x_924_, v___x_923_);
v_remainder_926_ = lean_uint64_land(v___y_906_, v___x_925_);
v___x_927_ = lean_uint64_sub(v___x_914_, v___x_923_);
v_half_928_ = lean_uint64_shift_left(v___x_923_, v___x_927_);
v___x_929_ = lean_uint64_dec_lt(v_remainder_926_, v_half_928_);
if (v___x_929_ == 0)
{
uint8_t v___x_930_; 
v___x_930_ = lean_uint64_dec_lt(v_half_928_, v_remainder_926_);
if (v___x_930_ == 0)
{
uint64_t v___x_931_; uint8_t v___x_932_; 
v___x_931_ = lean_uint64_land(v_quotient_922_, v___x_923_);
v___x_932_ = lean_uint64_dec_eq(v___x_931_, v___y_904_);
if (v___x_932_ == 0)
{
uint64_t v___x_933_; 
v___x_933_ = lean_uint64_add(v_quotient_922_, v___x_923_);
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v___x_933_;
goto v___jp_892_;
}
else
{
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v_quotient_922_;
goto v___jp_892_;
}
}
else
{
uint64_t v___x_934_; 
v___x_934_ = lean_uint64_add(v_quotient_922_, v___x_923_);
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v___x_934_;
goto v___jp_892_;
}
}
else
{
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v_quotient_922_;
goto v___jp_892_;
}
}
}
else
{
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v___y_906_;
goto v___jp_892_;
}
}
else
{
uint64_t v___x_935_; uint64_t v___x_936_; 
v___x_935_ = lean_uint64_sub(v___x_912_, v___y_908_);
v___x_936_ = lean_uint64_shift_left(v___y_906_, v___x_935_);
v___y_893_ = v_position_909_;
v___y_894_ = v___y_904_;
v___y_895_ = v___y_905_;
v___y_896_ = v___y_907_;
v___y_897_ = v___x_936_;
goto v___jp_892_;
}
}
else
{
uint64_t v___x_937_; uint8_t v___x_938_; 
v___x_937_ = 149ULL;
v___x_938_ = lean_uint64_dec_lt(v___y_903_, v___x_937_);
if (v___x_938_ == 0)
{
uint64_t v___x_939_; uint64_t v___x_940_; 
v___x_939_ = lean_uint64_sub(v___y_903_, v___x_937_);
v___x_940_ = lean_uint64_shift_left(v___y_906_, v___x_939_);
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v___x_940_;
goto v___jp_697_;
}
else
{
uint64_t v___x_941_; uint8_t v___x_942_; 
v___x_941_ = lean_uint64_sub(v___x_937_, v___y_903_);
v___x_942_ = lean_uint64_dec_eq(v___x_941_, v___y_904_);
if (v___x_942_ == 0)
{
uint64_t v___x_943_; uint8_t v___x_944_; 
v___x_943_ = 64ULL;
v___x_944_ = lean_uint64_dec_lt(v___x_941_, v___x_943_);
if (v___x_944_ == 0)
{
uint8_t v___x_945_; 
v___x_945_ = lean_uint64_dec_eq(v___x_941_, v___x_943_);
if (v___x_945_ == 0)
{
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v___y_904_;
goto v___jp_697_;
}
else
{
uint64_t v___x_946_; uint8_t v___x_947_; 
v___x_946_ = 9223372036854775808ULL;
v___x_947_ = lean_uint64_dec_lt(v___x_946_, v___y_906_);
if (v___x_947_ == 0)
{
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v___y_904_;
goto v___jp_697_;
}
else
{
uint64_t v___x_948_; 
v___x_948_ = 1ULL;
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v___x_948_;
goto v___jp_697_;
}
}
}
else
{
uint64_t v_quotient_949_; uint64_t v___x_950_; uint64_t v___x_951_; uint64_t v___x_952_; uint64_t v_remainder_953_; uint64_t v___x_954_; uint64_t v_half_955_; uint8_t v___x_956_; 
v_quotient_949_ = lean_uint64_shift_right(v___y_906_, v___x_941_);
v___x_950_ = 1ULL;
v___x_951_ = lean_uint64_shift_left(v___x_950_, v___x_941_);
v___x_952_ = lean_uint64_sub(v___x_951_, v___x_950_);
v_remainder_953_ = lean_uint64_land(v___y_906_, v___x_952_);
v___x_954_ = lean_uint64_sub(v___x_941_, v___x_950_);
v_half_955_ = lean_uint64_shift_left(v___x_950_, v___x_954_);
v___x_956_ = lean_uint64_dec_lt(v_remainder_953_, v_half_955_);
if (v___x_956_ == 0)
{
uint8_t v___x_957_; 
v___x_957_ = lean_uint64_dec_lt(v_half_955_, v_remainder_953_);
if (v___x_957_ == 0)
{
uint64_t v___x_958_; uint8_t v___x_959_; 
v___x_958_ = lean_uint64_land(v_quotient_949_, v___x_950_);
v___x_959_ = lean_uint64_dec_eq(v___x_958_, v___y_904_);
if (v___x_959_ == 0)
{
uint64_t v___x_960_; 
v___x_960_ = lean_uint64_add(v_quotient_949_, v___x_950_);
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v___x_960_;
goto v___jp_697_;
}
else
{
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v_quotient_949_;
goto v___jp_697_;
}
}
else
{
uint64_t v___x_961_; 
v___x_961_ = lean_uint64_add(v_quotient_949_, v___x_950_);
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v___x_961_;
goto v___jp_697_;
}
}
else
{
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v_quotient_949_;
goto v___jp_697_;
}
}
}
else
{
v___y_698_ = v___y_904_;
v___y_699_ = v___y_905_;
v___y_700_ = v___y_907_;
v___y_701_ = v___y_906_;
goto v___jp_697_;
}
}
}
}
v___jp_962_:
{
uint64_t v___x_970_; uint64_t v___x_971_; uint8_t v___x_972_; 
v___x_970_ = 1ULL;
v___x_971_ = lean_uint64_shift_right(v___y_964_, v___x_970_);
v___x_972_ = lean_uint64_dec_eq(v___x_971_, v___y_965_);
if (v___x_972_ == 0)
{
uint64_t v___x_973_; 
v___x_973_ = lean_uint64_add(v___y_969_, v___x_970_);
v___y_903_ = v___y_963_;
v___y_904_ = v___y_965_;
v___y_905_ = v___y_966_;
v___y_906_ = v___y_967_;
v___y_907_ = v___y_968_;
v___y_908_ = v___x_973_;
goto v___jp_902_;
}
else
{
v___y_903_ = v___y_963_;
v___y_904_ = v___y_965_;
v___y_905_ = v___y_966_;
v___y_906_ = v___y_967_;
v___y_907_ = v___y_968_;
v___y_908_ = v___y_969_;
goto v___jp_902_;
}
}
v___jp_974_:
{
uint64_t v___x_984_; uint8_t v___x_985_; 
v___x_984_ = lean_uint64_shift_right(v___y_976_, v___y_978_);
v___x_985_ = lean_uint64_dec_eq(v___x_984_, v___y_979_);
if (v___x_985_ == 0)
{
uint64_t v___x_986_; 
v___x_986_ = lean_uint64_add(v___y_975_, v___y_978_);
v___y_963_ = v___y_977_;
v___y_964_ = v___y_983_;
v___y_965_ = v___y_979_;
v___y_966_ = v___y_980_;
v___y_967_ = v___y_981_;
v___y_968_ = v___y_982_;
v___y_969_ = v___x_986_;
goto v___jp_962_;
}
else
{
v___y_963_ = v___y_977_;
v___y_964_ = v___y_983_;
v___y_965_ = v___y_979_;
v___y_966_ = v___y_980_;
v___y_967_ = v___y_981_;
v___y_968_ = v___y_982_;
v___y_969_ = v___y_975_;
goto v___jp_962_;
}
}
v___jp_987_:
{
uint64_t v___x_995_; uint64_t v___x_996_; uint8_t v___x_997_; 
v___x_995_ = 2ULL;
v___x_996_ = lean_uint64_shift_right(v___y_988_, v___x_995_);
v___x_997_ = lean_uint64_dec_eq(v___x_996_, v___y_990_);
if (v___x_997_ == 0)
{
v___y_975_ = v___y_994_;
v___y_976_ = v___y_988_;
v___y_977_ = v___y_989_;
v___y_978_ = v___x_995_;
v___y_979_ = v___y_990_;
v___y_980_ = v___y_991_;
v___y_981_ = v___y_992_;
v___y_982_ = v___y_993_;
v___y_983_ = v___x_996_;
goto v___jp_974_;
}
else
{
v___y_975_ = v___y_994_;
v___y_976_ = v___y_988_;
v___y_977_ = v___y_989_;
v___y_978_ = v___x_995_;
v___y_979_ = v___y_990_;
v___y_980_ = v___y_991_;
v___y_981_ = v___y_992_;
v___y_982_ = v___y_993_;
v___y_983_ = v___y_988_;
goto v___jp_974_;
}
}
v___jp_998_:
{
uint64_t v___x_1008_; uint8_t v___x_1009_; 
v___x_1008_ = lean_uint64_shift_right(v___y_1005_, v___y_1001_);
v___x_1009_ = lean_uint64_dec_eq(v___x_1008_, v___y_1000_);
if (v___x_1009_ == 0)
{
uint64_t v___x_1010_; 
v___x_1010_ = lean_uint64_add(v___y_1004_, v___y_1001_);
v___y_988_ = v___y_1007_;
v___y_989_ = v___y_999_;
v___y_990_ = v___y_1000_;
v___y_991_ = v___y_1002_;
v___y_992_ = v___y_1003_;
v___y_993_ = v___y_1006_;
v___y_994_ = v___x_1010_;
goto v___jp_987_;
}
else
{
v___y_988_ = v___y_1007_;
v___y_989_ = v___y_999_;
v___y_990_ = v___y_1000_;
v___y_991_ = v___y_1002_;
v___y_992_ = v___y_1003_;
v___y_993_ = v___y_1006_;
v___y_994_ = v___y_1004_;
goto v___jp_987_;
}
}
v___jp_1011_:
{
uint64_t v___x_1019_; uint64_t v___x_1020_; uint8_t v___x_1021_; 
v___x_1019_ = 4ULL;
v___x_1020_ = lean_uint64_shift_right(v___y_1016_, v___x_1019_);
v___x_1021_ = lean_uint64_dec_eq(v___x_1020_, v___y_1013_);
if (v___x_1021_ == 0)
{
v___y_999_ = v___y_1012_;
v___y_1000_ = v___y_1013_;
v___y_1001_ = v___x_1019_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v___y_1015_;
v___y_1004_ = v___y_1018_;
v___y_1005_ = v___y_1016_;
v___y_1006_ = v___y_1017_;
v___y_1007_ = v___x_1020_;
goto v___jp_998_;
}
else
{
v___y_999_ = v___y_1012_;
v___y_1000_ = v___y_1013_;
v___y_1001_ = v___x_1019_;
v___y_1002_ = v___y_1014_;
v___y_1003_ = v___y_1015_;
v___y_1004_ = v___y_1018_;
v___y_1005_ = v___y_1016_;
v___y_1006_ = v___y_1017_;
v___y_1007_ = v___y_1016_;
goto v___jp_998_;
}
}
v___jp_1022_:
{
uint64_t v___x_1032_; uint8_t v___x_1033_; 
v___x_1032_ = lean_uint64_shift_right(v___y_1025_, v___y_1023_);
v___x_1033_ = lean_uint64_dec_eq(v___x_1032_, v___y_1026_);
if (v___x_1033_ == 0)
{
uint64_t v___x_1034_; 
v___x_1034_ = lean_uint64_add(v___y_1029_, v___y_1023_);
v___y_1012_ = v___y_1024_;
v___y_1013_ = v___y_1026_;
v___y_1014_ = v___y_1027_;
v___y_1015_ = v___y_1028_;
v___y_1016_ = v___y_1031_;
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___x_1034_;
goto v___jp_1011_;
}
else
{
v___y_1012_ = v___y_1024_;
v___y_1013_ = v___y_1026_;
v___y_1014_ = v___y_1027_;
v___y_1015_ = v___y_1028_;
v___y_1016_ = v___y_1031_;
v___y_1017_ = v___y_1030_;
v___y_1018_ = v___y_1029_;
goto v___jp_1011_;
}
}
v___jp_1035_:
{
uint64_t v___x_1043_; uint64_t v___x_1044_; uint8_t v___x_1045_; 
v___x_1043_ = 8ULL;
v___x_1044_ = lean_uint64_shift_right(v___y_1037_, v___x_1043_);
v___x_1045_ = lean_uint64_dec_eq(v___x_1044_, v___y_1038_);
if (v___x_1045_ == 0)
{
v___y_1023_ = v___x_1043_;
v___y_1024_ = v___y_1036_;
v___y_1025_ = v___y_1037_;
v___y_1026_ = v___y_1038_;
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1040_;
v___y_1029_ = v___y_1042_;
v___y_1030_ = v___y_1041_;
v___y_1031_ = v___x_1044_;
goto v___jp_1022_;
}
else
{
v___y_1023_ = v___x_1043_;
v___y_1024_ = v___y_1036_;
v___y_1025_ = v___y_1037_;
v___y_1026_ = v___y_1038_;
v___y_1027_ = v___y_1039_;
v___y_1028_ = v___y_1040_;
v___y_1029_ = v___y_1042_;
v___y_1030_ = v___y_1041_;
v___y_1031_ = v___y_1037_;
goto v___jp_1022_;
}
}
v___jp_1046_:
{
uint64_t v___x_1056_; uint8_t v___x_1057_; 
v___x_1056_ = lean_uint64_shift_right(v___y_1047_, v___y_1050_);
v___x_1057_ = lean_uint64_dec_eq(v___x_1056_, v___y_1049_);
if (v___x_1057_ == 0)
{
uint64_t v___x_1058_; 
v___x_1058_ = lean_uint64_add(v___y_1053_, v___y_1050_);
v___y_1036_ = v___y_1048_;
v___y_1037_ = v___y_1055_;
v___y_1038_ = v___y_1049_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___y_1054_;
v___y_1042_ = v___x_1058_;
goto v___jp_1035_;
}
else
{
v___y_1036_ = v___y_1048_;
v___y_1037_ = v___y_1055_;
v___y_1038_ = v___y_1049_;
v___y_1039_ = v___y_1051_;
v___y_1040_ = v___y_1052_;
v___y_1041_ = v___y_1054_;
v___y_1042_ = v___y_1053_;
goto v___jp_1035_;
}
}
v___jp_1059_:
{
uint64_t v___x_1067_; uint64_t v___x_1068_; uint8_t v___x_1069_; 
v___x_1067_ = 16ULL;
v___x_1068_ = lean_uint64_shift_right(v___y_1060_, v___x_1067_);
v___x_1069_ = lean_uint64_dec_eq(v___x_1068_, v___y_1062_);
if (v___x_1069_ == 0)
{
v___y_1047_ = v___y_1060_;
v___y_1048_ = v___y_1061_;
v___y_1049_ = v___y_1062_;
v___y_1050_ = v___x_1067_;
v___y_1051_ = v___y_1063_;
v___y_1052_ = v___y_1064_;
v___y_1053_ = v___y_1066_;
v___y_1054_ = v___y_1065_;
v___y_1055_ = v___x_1068_;
goto v___jp_1046_;
}
else
{
v___y_1047_ = v___y_1060_;
v___y_1048_ = v___y_1061_;
v___y_1049_ = v___y_1062_;
v___y_1050_ = v___x_1067_;
v___y_1051_ = v___y_1063_;
v___y_1052_ = v___y_1064_;
v___y_1053_ = v___y_1066_;
v___y_1054_ = v___y_1065_;
v___y_1055_ = v___y_1060_;
goto v___jp_1046_;
}
}
v___jp_1070_:
{
uint64_t v___x_1078_; uint8_t v___x_1079_; 
v___x_1078_ = lean_uint64_shift_right(v___y_1075_, v___y_1071_);
v___x_1079_ = lean_uint64_dec_eq(v___x_1078_, v___y_1073_);
if (v___x_1079_ == 0)
{
v___y_1060_ = v___y_1077_;
v___y_1061_ = v___y_1072_;
v___y_1062_ = v___y_1073_;
v___y_1063_ = v___y_1074_;
v___y_1064_ = v___y_1075_;
v___y_1065_ = v___y_1076_;
v___y_1066_ = v___y_1071_;
goto v___jp_1059_;
}
else
{
v___y_1060_ = v___y_1077_;
v___y_1061_ = v___y_1072_;
v___y_1062_ = v___y_1073_;
v___y_1063_ = v___y_1074_;
v___y_1064_ = v___y_1075_;
v___y_1065_ = v___y_1076_;
v___y_1066_ = v___y_1073_;
goto v___jp_1059_;
}
}
v___jp_1080_:
{
uint64_t v___x_1085_; uint8_t v___x_1086_; 
v___x_1085_ = 0ULL;
v___x_1086_ = lean_uint64_dec_eq(v___y_1083_, v___x_1085_);
if (v___x_1086_ == 0)
{
uint64_t v___x_1087_; uint64_t v___x_1088_; uint8_t v___x_1089_; 
v___x_1087_ = 32ULL;
v___x_1088_ = lean_uint64_shift_right(v___y_1083_, v___x_1087_);
v___x_1089_ = lean_uint64_dec_eq(v___x_1088_, v___x_1085_);
if (v___x_1089_ == 0)
{
v___y_1071_ = v___x_1087_;
v___y_1072_ = v___y_1081_;
v___y_1073_ = v___x_1085_;
v___y_1074_ = v___y_1082_;
v___y_1075_ = v___y_1083_;
v___y_1076_ = v___y_1084_;
v___y_1077_ = v___x_1088_;
goto v___jp_1070_;
}
else
{
v___y_1071_ = v___x_1087_;
v___y_1072_ = v___y_1081_;
v___y_1073_ = v___x_1085_;
v___y_1074_ = v___y_1082_;
v___y_1075_ = v___y_1083_;
v___y_1076_ = v___y_1084_;
v___y_1077_ = v___y_1083_;
goto v___jp_1070_;
}
}
else
{
if (v___y_1084_ == 0)
{
uint32_t v___x_1090_; 
v___x_1090_ = 0;
return v___x_1090_;
}
else
{
uint32_t v___x_1091_; 
v___x_1091_ = 2147483648;
return v___x_1091_;
}
}
}
v___jp_1092_:
{
uint64_t v___x_1099_; uint64_t v___x_1100_; uint64_t v___x_1101_; uint8_t v___x_1102_; 
v___x_1099_ = lean_uint64_mul(v___y_1097_, v___y_1094_);
v___x_1100_ = lean_uint64_add(v___y_1093_, v___y_1098_);
v___x_1101_ = 281474976710656ULL;
v___x_1102_ = lean_uint64_dec_lt(v___x_1099_, v___x_1101_);
if (v___x_1102_ == 0)
{
v___y_1081_ = v___x_1100_;
v___y_1082_ = v___y_1095_;
v___y_1083_ = v___x_1099_;
v___y_1084_ = v___y_1096_;
goto v___jp_1080_;
}
else
{
uint64_t v___x_1103_; uint8_t v___x_1104_; 
v___x_1103_ = 123ULL;
v___x_1104_ = lean_uint64_dec_le(v___x_1100_, v___x_1103_);
if (v___x_1104_ == 0)
{
v___y_1081_ = v___x_1100_;
v___y_1082_ = v___y_1095_;
v___y_1083_ = v___x_1099_;
v___y_1084_ = v___y_1096_;
goto v___jp_1080_;
}
else
{
uint64_t v___x_1105_; uint8_t v___x_1106_; 
v___x_1105_ = 0ULL;
v___x_1106_ = lean_uint64_dec_eq(v___x_1099_, v___x_1105_);
if (v___x_1106_ == 0)
{
uint64_t v___x_1107_; uint64_t v___x_1108_; uint8_t v___x_1109_; 
v___x_1107_ = 149ULL;
v___x_1108_ = lean_uint64_sub(v___x_1107_, v___x_1100_);
v___x_1109_ = lean_uint64_dec_eq(v___x_1108_, v___x_1105_);
if (v___x_1109_ == 0)
{
uint64_t v___x_1110_; uint8_t v___x_1111_; 
v___x_1110_ = 64ULL;
v___x_1111_ = lean_uint64_dec_lt(v___x_1108_, v___x_1110_);
if (v___x_1111_ == 0)
{
uint8_t v___x_1112_; 
v___x_1112_ = lean_uint64_dec_eq(v___x_1108_, v___x_1110_);
if (v___x_1112_ == 0)
{
v___y_717_ = v___x_1105_;
v___y_718_ = v___y_1095_;
v___y_719_ = v___y_1096_;
v___y_720_ = v___x_1105_;
goto v___jp_716_;
}
else
{
uint64_t v___x_1113_; uint8_t v___x_1114_; 
v___x_1113_ = 9223372036854775808ULL;
v___x_1114_ = lean_uint64_dec_lt(v___x_1113_, v___x_1099_);
if (v___x_1114_ == 0)
{
v___y_717_ = v___x_1105_;
v___y_718_ = v___y_1095_;
v___y_719_ = v___y_1096_;
v___y_720_ = v___x_1105_;
goto v___jp_716_;
}
else
{
uint64_t v___x_1115_; 
v___x_1115_ = 1ULL;
v___y_717_ = v___x_1105_;
v___y_718_ = v___y_1095_;
v___y_719_ = v___y_1096_;
v___y_720_ = v___x_1115_;
goto v___jp_716_;
}
}
}
else
{
uint64_t v_quotient_1116_; uint64_t v___x_1117_; uint64_t v___x_1118_; uint64_t v___x_1119_; uint64_t v_remainder_1120_; uint64_t v___x_1121_; uint64_t v_half_1122_; uint8_t v___x_1123_; 
v_quotient_1116_ = lean_uint64_shift_right(v___x_1099_, v___x_1108_);
v___x_1117_ = 1ULL;
v___x_1118_ = lean_uint64_shift_left(v___x_1117_, v___x_1108_);
v___x_1119_ = lean_uint64_sub(v___x_1118_, v___x_1117_);
v_remainder_1120_ = lean_uint64_land(v___x_1099_, v___x_1119_);
v___x_1121_ = lean_uint64_sub(v___x_1108_, v___x_1117_);
v_half_1122_ = lean_uint64_shift_left(v___x_1117_, v___x_1121_);
v___x_1123_ = lean_uint64_dec_lt(v_remainder_1120_, v_half_1122_);
if (v___x_1123_ == 0)
{
uint8_t v___x_1124_; 
v___x_1124_ = lean_uint64_dec_lt(v_half_1122_, v_remainder_1120_);
if (v___x_1124_ == 0)
{
uint64_t v___x_1125_; uint8_t v___x_1126_; 
v___x_1125_ = lean_uint64_land(v_quotient_1116_, v___x_1117_);
v___x_1126_ = lean_uint64_dec_eq(v___x_1125_, v___x_1105_);
if (v___x_1126_ == 0)
{
uint64_t v___x_1127_; 
v___x_1127_ = lean_uint64_add(v_quotient_1116_, v___x_1117_);
v___y_717_ = v___x_1105_;
v___y_718_ = v___y_1095_;
v___y_719_ = v___y_1096_;
v___y_720_ = v___x_1127_;
goto v___jp_716_;
}
else
{
v___y_717_ = v___x_1105_;
v___y_718_ = v___y_1095_;
v___y_719_ = v___y_1096_;
v___y_720_ = v_quotient_1116_;
goto v___jp_716_;
}
}
else
{
uint64_t v___x_1128_; 
v___x_1128_ = lean_uint64_add(v_quotient_1116_, v___x_1117_);
v___y_717_ = v___x_1105_;
v___y_718_ = v___y_1095_;
v___y_719_ = v___y_1096_;
v___y_720_ = v___x_1128_;
goto v___jp_716_;
}
}
else
{
v___y_717_ = v___x_1105_;
v___y_718_ = v___y_1095_;
v___y_719_ = v___y_1096_;
v___y_720_ = v_quotient_1116_;
goto v___jp_716_;
}
}
}
else
{
v___y_717_ = v___x_1105_;
v___y_718_ = v___y_1095_;
v___y_719_ = v___y_1096_;
v___y_720_ = v___x_1099_;
goto v___jp_716_;
}
}
else
{
if (v___y_1096_ == 0)
{
uint32_t v___x_1129_; 
v___x_1129_ = 0;
return v___x_1129_;
}
else
{
uint32_t v___x_1130_; 
v___x_1130_ = 2147483648;
return v___x_1130_;
}
}
}
}
}
v___jp_1134_:
{
uint64_t v___x_1140_; uint64_t v___x_1141_; uint8_t v___x_1142_; 
v___x_1140_ = lean_uint32_to_uint64(v_ey_1133_);
v___x_1141_ = 0ULL;
v___x_1142_ = lean_uint64_dec_eq(v___x_1140_, v___x_1141_);
if (v___x_1142_ == 0)
{
uint64_t v___x_1143_; uint64_t v___x_1144_; 
v___x_1143_ = 1ULL;
v___x_1144_ = lean_uint64_sub(v___x_1140_, v___x_1143_);
v___y_1093_ = v___y_1139_;
v___y_1094_ = v___y_1135_;
v___y_1095_ = v___y_1136_;
v___y_1096_ = v___y_1138_;
v___y_1097_ = v___y_1137_;
v___y_1098_ = v___x_1144_;
goto v___jp_1092_;
}
else
{
v___y_1093_ = v___y_1139_;
v___y_1094_ = v___y_1135_;
v___y_1095_ = v___y_1136_;
v___y_1096_ = v___y_1138_;
v___y_1097_ = v___y_1137_;
v___y_1098_ = v___x_1141_;
goto v___jp_1092_;
}
}
v___jp_1145_:
{
uint64_t v___x_1150_; uint64_t v___x_1151_; uint8_t v___x_1152_; 
v___x_1150_ = lean_uint32_to_uint64(v_ex_1131_);
v___x_1151_ = 0ULL;
v___x_1152_ = lean_uint64_dec_eq(v___x_1150_, v___x_1151_);
if (v___x_1152_ == 0)
{
uint64_t v___x_1153_; uint64_t v___x_1154_; 
v___x_1153_ = 1ULL;
v___x_1154_ = lean_uint64_sub(v___x_1150_, v___x_1153_);
v___y_1135_ = v___y_1149_;
v___y_1136_ = v___y_1146_;
v___y_1137_ = v___y_1148_;
v___y_1138_ = v___y_1147_;
v___y_1139_ = v___x_1154_;
goto v___jp_1134_;
}
else
{
v___y_1135_ = v___y_1149_;
v___y_1136_ = v___y_1146_;
v___y_1137_ = v___y_1148_;
v___y_1138_ = v___y_1147_;
v___y_1139_ = v___x_1151_;
goto v___jp_1134_;
}
}
v___jp_1155_:
{
uint32_t v___x_1160_; uint8_t v___x_1161_; 
v___x_1160_ = 0;
v___x_1161_ = lean_uint32_dec_eq(v_ey_1133_, v___x_1160_);
if (v___x_1161_ == 0)
{
uint64_t v___x_1162_; uint64_t v___x_1163_; uint64_t v___x_1164_; 
v___x_1162_ = lean_uint32_to_uint64(v___y_1156_);
v___x_1163_ = 8388608ULL;
v___x_1164_ = lean_uint64_lor(v___x_1162_, v___x_1163_);
v___y_1146_ = v___y_1157_;
v___y_1147_ = v___y_1158_;
v___y_1148_ = v___y_1159_;
v___y_1149_ = v___x_1164_;
goto v___jp_1145_;
}
else
{
uint64_t v___x_1165_; 
v___x_1165_ = lean_uint32_to_uint64(v___y_1156_);
v___y_1146_ = v___y_1157_;
v___y_1147_ = v___y_1158_;
v___y_1148_ = v___y_1159_;
v___y_1149_ = v___x_1165_;
goto v___jp_1145_;
}
}
v___jp_1166_:
{
uint32_t v___x_1168_; uint32_t v_xFraction_1169_; uint32_t v_yFraction_1170_; uint32_t v___x_1171_; uint8_t v___x_1172_; 
v___x_1168_ = 8388607;
v_xFraction_1169_ = lean_uint32_land(v___y_679_, v___x_1168_);
v_yFraction_1170_ = lean_uint32_land(v___y_680_, v___x_1168_);
v___x_1171_ = 0;
v___x_1172_ = lean_uint32_dec_eq(v_ex_1131_, v___x_1171_);
if (v___x_1172_ == 0)
{
uint64_t v___x_1173_; uint64_t v___x_1174_; uint64_t v___x_1175_; 
v___x_1173_ = lean_uint32_to_uint64(v_xFraction_1169_);
v___x_1174_ = 8388608ULL;
v___x_1175_ = lean_uint64_lor(v___x_1173_, v___x_1174_);
v___y_1156_ = v_yFraction_1170_;
v___y_1157_ = v___x_1168_;
v___y_1158_ = v___y_1167_;
v___y_1159_ = v___x_1175_;
goto v___jp_1155_;
}
else
{
uint64_t v___x_1176_; 
v___x_1176_ = lean_uint32_to_uint64(v_xFraction_1169_);
v___y_1156_ = v_yFraction_1170_;
v___y_1157_ = v___x_1168_;
v___y_1158_ = v___y_1167_;
v___y_1159_ = v___x_1176_;
goto v___jp_1155_;
}
}
v___jp_1180_:
{
if (v___y_1182_ == 0)
{
v___y_1167_ = v___x_1179_;
goto v___jp_1166_;
}
else
{
v___y_1167_ = v___y_1181_;
goto v___jp_1166_;
}
}
v___jp_1183_:
{
if (v___y_1185_ == 0)
{
if (v___y_1186_ == 0)
{
v___y_1181_ = v___y_1184_;
v___y_1182_ = v___x_1179_;
goto v___jp_1180_;
}
else
{
v___y_1167_ = v___x_1179_;
goto v___jp_1166_;
}
}
else
{
v___y_1181_ = v___y_1184_;
v___y_1182_ = v___y_1186_;
goto v___jp_1180_;
}
}
v___jp_1187_:
{
uint32_t v___x_1190_; uint32_t v___x_1191_; uint32_t v___x_1192_; uint8_t v___x_1193_; 
v___x_1190_ = 2147483648;
v___x_1191_ = lean_uint32_land(v___y_680_, v___x_1190_);
v___x_1192_ = 0;
v___x_1193_ = lean_uint32_dec_eq(v___x_1191_, v___x_1192_);
if (v___x_1193_ == 0)
{
v___y_1184_ = v___y_1188_;
v___y_1185_ = v___y_1189_;
v___y_1186_ = v___x_1179_;
goto v___jp_1183_;
}
else
{
v___y_1184_ = v___y_1188_;
v___y_1185_ = v___y_1189_;
v___y_1186_ = v___y_1188_;
goto v___jp_1183_;
}
}
v___jp_1194_:
{
if (v___y_1195_ == 0)
{
uint32_t v___x_1196_; uint32_t v___x_1197_; uint32_t v___x_1198_; uint8_t v___x_1199_; 
v___x_1196_ = 2147483648;
v___x_1197_ = lean_uint32_land(v___y_679_, v___x_1196_);
v___x_1198_ = 0;
v___x_1199_ = lean_uint32_dec_eq(v___x_1197_, v___x_1198_);
if (v___x_1199_ == 0)
{
v___y_1188_ = v___y_1195_;
v___y_1189_ = v___x_1179_;
goto v___jp_1187_;
}
else
{
v___y_1188_ = v___y_1195_;
v___y_1189_ = v___y_1195_;
goto v___jp_1187_;
}
}
else
{
lean_object* v___x_1200_; lean_object* v___x_1201_; lean_object* v___x_1202_; uint32_t v___x_1203_; 
v___x_1200_ = lean_uint32_to_nat(v___y_679_);
v___x_1201_ = lean_uint32_to_nat(v___y_680_);
v___x_1202_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_1200_, v___x_1201_);
v___x_1203_ = lean_uint32_of_nat(v___x_1202_);
lean_dec(v___x_1202_);
return v___x_1203_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__3___boxed(lean_object* v___y_1218_, lean_object* v___y_1219_){
_start:
{
uint32_t v___y_5197__boxed_1220_; uint32_t v___y_5198__boxed_1221_; uint32_t v_res_1222_; lean_object* v_r_1223_; 
v___y_5197__boxed_1220_ = lean_unbox_uint32(v___y_1218_);
lean_dec(v___y_1218_);
v___y_5198__boxed_1221_ = lean_unbox_uint32(v___y_1219_);
lean_dec(v___y_1219_);
v_res_1222_ = lp_competition_main___lam__3(v___y_5197__boxed_1220_, v___y_5198__boxed_1221_);
v_r_1223_ = lean_box_uint32(v_res_1222_);
return v_r_1223_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_1231_; lean_object* v___x_1232_; 
v___x_1231_ = ((lean_object*)(lp_competition_main___closed__0));
v___x_1232_ = lean_io_getenv(v___x_1231_);
if (lean_obj_tag(v___x_1232_) == 0)
{
lean_object* v___f_1233_; lean_object* v___f_1234_; lean_object* v___x_1235_; lean_object* v___x_1236_; lean_object* v___x_1237_; 
v___f_1233_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1234_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_1235_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1236_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1237_ = lp_competition_Bench_runFull(v___f_1233_, v___f_1234_, v___x_1235_, v___x_1236_);
return v___x_1237_;
}
else
{
lean_object* v___f_1238_; lean_object* v___f_1239_; lean_object* v___x_1240_; lean_object* v___x_1241_; lean_object* v___x_1242_; 
lean_dec_ref_known(v___x_1232_, 1);
v___f_1238_ = ((lean_object*)(lp_competition_main___closed__1));
v___f_1239_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_1240_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_1241_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_1242_ = lp_competition_Bench_Suite_run(v___f_1238_, v___f_1239_, v___x_1240_, v___x_1241_);
return v___x_1242_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_1243_){
_start:
{
lean_object* v_res_1244_; 
v_res_1244_ = _lean_main();
return v_res_1244_;
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
