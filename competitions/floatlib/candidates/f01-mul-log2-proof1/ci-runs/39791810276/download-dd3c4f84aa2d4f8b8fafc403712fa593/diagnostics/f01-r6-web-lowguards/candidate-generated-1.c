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
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
uint64_t lean_uint32_to_uint64(uint32_t);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
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
uint32_t v___y_1144__boxed_69_; uint32_t v___y_1145__boxed_70_; uint32_t v_res_71_; lean_object* v_r_72_; 
v___y_1144__boxed_69_ = lean_unbox_uint32(v___y_67_);
lean_dec(v___y_67_);
v___y_1145__boxed_70_ = lean_unbox_uint32(v___y_68_);
lean_dec(v___y_68_);
v_res_71_ = lp_competition_main___lam__0(v___y_1144__boxed_69_, v___y_1145__boxed_70_);
v_r_72_ = lean_box_uint32(v_res_71_);
return v_r_72_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_73_, uint32_t v___y_74_){
_start:
{
uint32_t v___y_81_; uint32_t v___y_82_; uint32_t v___y_87_; uint32_t v___y_88_; uint32_t v___y_93_; uint64_t v___y_97_; uint8_t v___y_98_; uint64_t v___y_99_; uint32_t v___y_111_; uint64_t v___y_115_; uint8_t v___y_116_; uint64_t v___y_117_; uint32_t v___x_128_; uint32_t v___x_129_; uint32_t v___x_130_; uint32_t v___y_132_; uint32_t v___y_133_; uint32_t v___y_134_; uint32_t v___y_142_; uint8_t v___y_143_; uint32_t v___y_144_; uint64_t v___y_148_; uint8_t v___y_149_; uint64_t v___y_150_; uint64_t v___y_151_; uint64_t v___y_161_; uint8_t v___y_162_; uint64_t v___y_163_; uint8_t v___y_164_; uint64_t v___y_165_; uint64_t v___y_172_; uint64_t v___y_173_; uint8_t v___y_174_; uint64_t v___y_175_; uint64_t v___y_181_; uint8_t v___y_182_; uint64_t v___y_183_; uint64_t v___y_184_; uint64_t v___y_185_; uint64_t v___y_240_; uint64_t v___y_241_; uint8_t v___y_242_; uint64_t v___y_243_; uint64_t v___y_244_; uint64_t v___y_245_; uint64_t v___y_251_; uint8_t v___y_252_; uint64_t v___y_253_; uint64_t v___y_254_; uint64_t v___y_255_; uint64_t v___y_256_; uint64_t v___y_257_; uint64_t v___y_258_; uint64_t v___y_263_; uint8_t v___y_264_; uint64_t v___y_265_; uint64_t v___y_266_; uint64_t v___y_267_; uint64_t v___y_268_; uint64_t v___y_273_; uint64_t v___y_274_; uint8_t v___y_275_; uint64_t v___y_276_; uint64_t v___y_277_; uint64_t v___y_278_; uint64_t v___y_279_; uint64_t v___y_280_; uint64_t v___y_285_; uint8_t v___y_286_; uint64_t v___y_287_; uint64_t v___y_288_; uint64_t v___y_289_; uint64_t v___y_290_; uint64_t v___y_295_; uint8_t v___y_296_; uint64_t v___y_297_; uint64_t v___y_298_; uint64_t v___y_299_; uint64_t v___y_300_; uint64_t v___y_301_; uint64_t v___y_302_; uint64_t v___y_307_; uint8_t v___y_308_; uint64_t v___y_309_; uint64_t v___y_310_; uint64_t v___y_311_; uint64_t v___y_312_; uint64_t v___y_317_; uint64_t v___y_318_; uint64_t v___y_319_; uint8_t v___y_320_; uint64_t v___y_321_; uint64_t v___y_322_; uint64_t v___y_323_; uint64_t v___y_324_; uint64_t v___y_329_; uint8_t v___y_330_; uint64_t v___y_331_; uint64_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint64_t v___y_339_; uint64_t v___y_340_; uint8_t v___y_341_; uint64_t v___y_342_; uint64_t v___y_343_; uint64_t v___y_344_; uint8_t v___y_348_; uint64_t v___y_349_; uint64_t v___y_350_; uint64_t v___y_351_; uint32_t v_ex_388_; uint32_t v___x_389_; uint32_t v_ey_390_; uint8_t v___y_392_; uint64_t v___y_393_; uint64_t v___y_394_; uint8_t v___y_401_; uint64_t v___y_402_; uint64_t v___y_403_; uint8_t v___y_411_; uint64_t v___y_412_; uint8_t v___y_422_; uint32_t v___x_433_; uint32_t v___x_434_; uint8_t v___x_435_; uint8_t v___y_437_; uint8_t v___y_438_; uint8_t v___y_440_; 
v___x_128_ = 23;
v___x_129_ = lean_uint32_shift_right(v___y_73_, v___x_128_);
v___x_130_ = 255;
v_ex_388_ = lean_uint32_land(v___x_129_, v___x_130_);
v___x_389_ = lean_uint32_shift_right(v___y_74_, v___x_128_);
v_ey_390_ = lean_uint32_land(v___x_389_, v___x_130_);
v___x_433_ = lean_uint32_add(v_ex_388_, v_ey_390_);
v___x_434_ = 128;
v___x_435_ = lean_uint32_dec_lt(v___x_433_, v___x_434_);
if (v___x_435_ == 0)
{
uint8_t v___x_449_; 
v___x_449_ = lean_uint32_dec_eq(v_ex_388_, v___x_130_);
if (v___x_449_ == 0)
{
goto v___jp_446_;
}
else
{
if (v___x_435_ == 0)
{
uint32_t v___x_450_; 
v___x_450_ = lp_competition_Submission_FastMul_mul(v___y_73_, v___y_74_);
return v___x_450_;
}
else
{
goto v___jp_446_;
}
}
}
else
{
uint32_t v___x_451_; uint32_t v___x_452_; uint32_t v___x_453_; uint8_t v___x_454_; 
v___x_451_ = 2147483648;
v___x_452_ = lean_uint32_land(v___y_73_, v___x_451_);
v___x_453_ = 0;
v___x_454_ = lean_uint32_dec_eq(v___x_452_, v___x_453_);
if (v___x_454_ == 0)
{
v___y_440_ = v___x_435_;
goto v___jp_439_;
}
else
{
uint8_t v___x_455_; 
v___x_455_ = 0;
v___y_440_ = v___x_455_;
goto v___jp_439_;
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
uint32_t v___x_83_; uint32_t v___x_84_; uint32_t v___x_85_; 
v___x_83_ = 8388607;
v___x_84_ = lean_uint32_land(v___y_81_, v___x_83_);
v___x_85_ = lean_uint32_lor(v___y_82_, v___x_84_);
return v___x_85_;
}
v___jp_86_:
{
uint32_t v___x_89_; uint32_t v___x_90_; uint32_t v___x_91_; 
v___x_89_ = 8388607;
v___x_90_ = lean_uint32_land(v___y_87_, v___x_89_);
v___x_91_ = lean_uint32_lor(v___y_88_, v___x_90_);
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
uint8_t v___x_100_; 
v___x_100_ = lean_uint64_dec_eq(v___y_99_, v___y_97_);
if (v___x_100_ == 0)
{
uint64_t v___x_101_; uint8_t v___x_102_; 
v___x_101_ = 8388608ULL;
v___x_102_ = lean_uint64_dec_eq(v___y_99_, v___x_101_);
if (v___x_102_ == 0)
{
uint32_t v___x_103_; 
v___x_103_ = lean_uint64_to_uint32(v___y_99_);
if (v___y_98_ == 0)
{
uint32_t v___x_104_; 
v___x_104_ = 0;
v___y_87_ = v___x_103_;
v___y_88_ = v___x_104_;
goto v___jp_86_;
}
else
{
uint32_t v___x_105_; 
v___x_105_ = 2147483648;
v___y_87_ = v___x_103_;
v___y_88_ = v___x_105_;
goto v___jp_86_;
}
}
else
{
if (v___y_98_ == 0)
{
uint32_t v___x_106_; 
v___x_106_ = 0;
v___y_93_ = v___x_106_;
goto v___jp_92_;
}
else
{
uint32_t v___x_107_; 
v___x_107_ = 2147483648;
v___y_93_ = v___x_107_;
goto v___jp_92_;
}
}
}
else
{
if (v___y_98_ == 0)
{
uint32_t v___x_108_; 
v___x_108_ = 0;
return v___x_108_;
}
else
{
uint32_t v___x_109_; 
v___x_109_ = 2147483648;
return v___x_109_;
}
}
}
v___jp_110_:
{
uint32_t v___x_112_; uint32_t v___x_113_; 
v___x_112_ = 8388608;
v___x_113_ = lean_uint32_lor(v___y_111_, v___x_112_);
return v___x_113_;
}
v___jp_114_:
{
uint8_t v___x_118_; 
v___x_118_ = lean_uint64_dec_eq(v___y_117_, v___y_115_);
if (v___x_118_ == 0)
{
uint64_t v___x_119_; uint8_t v___x_120_; 
v___x_119_ = 8388608ULL;
v___x_120_ = lean_uint64_dec_eq(v___y_117_, v___x_119_);
if (v___x_120_ == 0)
{
uint32_t v___x_121_; 
v___x_121_ = lean_uint64_to_uint32(v___y_117_);
if (v___y_116_ == 0)
{
uint32_t v___x_122_; 
v___x_122_ = 0;
v___y_81_ = v___x_121_;
v___y_82_ = v___x_122_;
goto v___jp_80_;
}
else
{
uint32_t v___x_123_; 
v___x_123_ = 2147483648;
v___y_81_ = v___x_121_;
v___y_82_ = v___x_123_;
goto v___jp_80_;
}
}
else
{
if (v___y_116_ == 0)
{
uint32_t v___x_124_; 
v___x_124_ = 0;
v___y_111_ = v___x_124_;
goto v___jp_110_;
}
else
{
uint32_t v___x_125_; 
v___x_125_ = 2147483648;
v___y_111_ = v___x_125_;
goto v___jp_110_;
}
}
}
else
{
if (v___y_116_ == 0)
{
uint32_t v___x_126_; 
v___x_126_ = 0;
return v___x_126_;
}
else
{
uint32_t v___x_127_; 
v___x_127_ = 2147483648;
return v___x_127_;
}
}
}
v___jp_131_:
{
uint32_t v___x_135_; uint32_t v___x_136_; uint32_t v___x_137_; uint32_t v___x_138_; uint32_t v___x_139_; uint32_t v___x_140_; 
v___x_135_ = lean_uint32_land(v___y_132_, v___x_130_);
v___x_136_ = lean_uint32_shift_left(v___x_135_, v___x_128_);
v___x_137_ = lean_uint32_lor(v___y_134_, v___x_136_);
v___x_138_ = 8388607;
v___x_139_ = lean_uint32_land(v___y_133_, v___x_138_);
v___x_140_ = lean_uint32_lor(v___x_137_, v___x_139_);
return v___x_140_;
}
v___jp_141_:
{
if (v___y_143_ == 0)
{
uint32_t v___x_145_; 
v___x_145_ = 0;
v___y_132_ = v___y_142_;
v___y_133_ = v___y_144_;
v___y_134_ = v___x_145_;
goto v___jp_131_;
}
else
{
uint32_t v___x_146_; 
v___x_146_ = 2147483648;
v___y_132_ = v___y_142_;
v___y_133_ = v___y_144_;
v___y_134_ = v___x_146_;
goto v___jp_131_;
}
}
v___jp_147_:
{
uint64_t v___x_152_; uint64_t v_encodedExponent_153_; uint32_t v___x_154_; uint64_t v___x_155_; uint8_t v___x_156_; 
v___x_152_ = 171ULL;
v_encodedExponent_153_ = lean_uint64_sub(v___y_150_, v___x_152_);
v___x_154_ = lean_uint64_to_uint32(v_encodedExponent_153_);
v___x_155_ = 8388608ULL;
v___x_156_ = lean_uint64_dec_lt(v___y_151_, v___x_155_);
if (v___x_156_ == 0)
{
uint64_t v___x_157_; uint32_t v___x_158_; 
v___x_157_ = lean_uint64_sub(v___y_151_, v___x_155_);
v___x_158_ = lean_uint64_to_uint32(v___x_157_);
v___y_142_ = v___x_154_;
v___y_143_ = v___y_149_;
v___y_144_ = v___x_158_;
goto v___jp_141_;
}
else
{
uint32_t v___x_159_; 
v___x_159_ = lean_uint64_to_uint32(v___y_148_);
v___y_142_ = v___x_154_;
v___y_143_ = v___y_149_;
v___y_144_ = v___x_159_;
goto v___jp_141_;
}
}
v___jp_160_:
{
uint64_t v___x_166_; uint8_t v___x_167_; 
v___x_166_ = 425ULL;
v___x_167_ = lean_uint64_dec_lt(v___x_166_, v___y_165_);
if (v___x_167_ == 0)
{
if (v___y_164_ == 0)
{
v___y_148_ = v___y_161_;
v___y_149_ = v___y_162_;
v___y_150_ = v___y_165_;
v___y_151_ = v___y_163_;
goto v___jp_147_;
}
else
{
uint64_t v___x_168_; 
v___x_168_ = 8388608ULL;
v___y_148_ = v___y_161_;
v___y_149_ = v___y_162_;
v___y_150_ = v___y_165_;
v___y_151_ = v___x_168_;
goto v___jp_147_;
}
}
else
{
if (v___y_162_ == 0)
{
uint32_t v___x_169_; 
v___x_169_ = 2139095040;
return v___x_169_;
}
else
{
uint32_t v___x_170_; 
v___x_170_ = 4286578688;
return v___x_170_;
}
}
}
v___jp_171_:
{
uint64_t v___x_176_; uint8_t v_carry_177_; 
v___x_176_ = 16777216ULL;
v_carry_177_ = lean_uint64_dec_eq(v___y_175_, v___x_176_);
if (v_carry_177_ == 0)
{
v___y_161_ = v___y_172_;
v___y_162_ = v___y_174_;
v___y_163_ = v___y_175_;
v___y_164_ = v_carry_177_;
v___y_165_ = v___y_173_;
goto v___jp_160_;
}
else
{
uint64_t v___x_178_; uint64_t v___x_179_; 
v___x_178_ = 1ULL;
v___x_179_ = lean_uint64_add(v___y_173_, v___x_178_);
v___y_161_ = v___y_172_;
v___y_162_ = v___y_174_;
v___y_163_ = v___y_175_;
v___y_164_ = v_carry_177_;
v___y_165_ = v___x_179_;
goto v___jp_160_;
}
}
v___jp_180_:
{
uint64_t v_position_186_; uint64_t v___x_187_; uint8_t v___x_188_; 
v_position_186_ = lean_uint64_add(v___y_185_, v___y_184_);
v___x_187_ = 172ULL;
v___x_188_ = lean_uint64_dec_lt(v_position_186_, v___x_187_);
if (v___x_188_ == 0)
{
uint64_t v___x_189_; uint8_t v___x_190_; 
v___x_189_ = 23ULL;
v___x_190_ = lean_uint64_dec_lt(v___y_185_, v___x_189_);
if (v___x_190_ == 0)
{
uint64_t v___x_191_; uint8_t v___x_192_; 
v___x_191_ = lean_uint64_sub(v___y_185_, v___x_189_);
v___x_192_ = lean_uint64_dec_eq(v___x_191_, v___y_181_);
if (v___x_192_ == 0)
{
uint64_t v___x_193_; uint8_t v___x_194_; 
v___x_193_ = 64ULL;
v___x_194_ = lean_uint64_dec_lt(v___x_191_, v___x_193_);
if (v___x_194_ == 0)
{
uint8_t v___x_195_; 
v___x_195_ = lean_uint64_dec_eq(v___x_191_, v___x_193_);
if (v___x_195_ == 0)
{
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v___y_181_;
goto v___jp_171_;
}
else
{
uint64_t v___x_196_; uint8_t v___x_197_; 
v___x_196_ = 9223372036854775808ULL;
v___x_197_ = lean_uint64_dec_lt(v___x_196_, v___y_183_);
if (v___x_197_ == 0)
{
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v___y_181_;
goto v___jp_171_;
}
else
{
uint64_t v___x_198_; 
v___x_198_ = 1ULL;
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v___x_198_;
goto v___jp_171_;
}
}
}
else
{
uint64_t v_quotient_199_; uint64_t v___x_200_; uint64_t v___x_201_; uint64_t v___x_202_; uint64_t v_remainder_203_; uint64_t v___x_204_; uint64_t v_half_205_; uint8_t v___x_206_; 
v_quotient_199_ = lean_uint64_shift_right(v___y_183_, v___x_191_);
v___x_200_ = 1ULL;
v___x_201_ = lean_uint64_shift_left(v___x_200_, v___x_191_);
v___x_202_ = lean_uint64_sub(v___x_201_, v___x_200_);
v_remainder_203_ = lean_uint64_land(v___y_183_, v___x_202_);
v___x_204_ = lean_uint64_sub(v___x_191_, v___x_200_);
v_half_205_ = lean_uint64_shift_left(v___x_200_, v___x_204_);
v___x_206_ = lean_uint64_dec_lt(v_remainder_203_, v_half_205_);
if (v___x_206_ == 0)
{
uint8_t v___x_207_; 
v___x_207_ = lean_uint64_dec_lt(v_half_205_, v_remainder_203_);
if (v___x_207_ == 0)
{
uint64_t v___x_208_; uint8_t v___x_209_; 
v___x_208_ = lean_uint64_land(v_quotient_199_, v___x_200_);
v___x_209_ = lean_uint64_dec_eq(v___x_208_, v___y_181_);
if (v___x_209_ == 0)
{
uint64_t v___x_210_; 
v___x_210_ = lean_uint64_add(v_quotient_199_, v___x_200_);
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v___x_210_;
goto v___jp_171_;
}
else
{
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v_quotient_199_;
goto v___jp_171_;
}
}
else
{
uint64_t v___x_211_; 
v___x_211_ = lean_uint64_add(v_quotient_199_, v___x_200_);
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v___x_211_;
goto v___jp_171_;
}
}
else
{
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v_quotient_199_;
goto v___jp_171_;
}
}
}
else
{
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v___y_183_;
goto v___jp_171_;
}
}
else
{
uint64_t v___x_212_; uint64_t v___x_213_; 
v___x_212_ = lean_uint64_sub(v___x_189_, v___y_185_);
v___x_213_ = lean_uint64_shift_left(v___y_183_, v___x_212_);
v___y_172_ = v___y_181_;
v___y_173_ = v_position_186_;
v___y_174_ = v___y_182_;
v___y_175_ = v___x_213_;
goto v___jp_171_;
}
}
else
{
uint64_t v___x_214_; uint8_t v___x_215_; 
v___x_214_ = 149ULL;
v___x_215_ = lean_uint64_dec_lt(v___y_184_, v___x_214_);
if (v___x_215_ == 0)
{
uint64_t v___x_216_; uint64_t v___x_217_; 
v___x_216_ = lean_uint64_sub(v___y_184_, v___x_214_);
v___x_217_ = lean_uint64_shift_left(v___y_183_, v___x_216_);
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v___x_217_;
goto v___jp_96_;
}
else
{
uint64_t v___x_218_; uint8_t v___x_219_; 
v___x_218_ = lean_uint64_sub(v___x_214_, v___y_184_);
v___x_219_ = lean_uint64_dec_eq(v___x_218_, v___y_181_);
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
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v___y_181_;
goto v___jp_96_;
}
else
{
uint64_t v___x_223_; uint8_t v___x_224_; 
v___x_223_ = 9223372036854775808ULL;
v___x_224_ = lean_uint64_dec_lt(v___x_223_, v___y_183_);
if (v___x_224_ == 0)
{
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v___y_181_;
goto v___jp_96_;
}
else
{
uint64_t v___x_225_; 
v___x_225_ = 1ULL;
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v___x_225_;
goto v___jp_96_;
}
}
}
else
{
uint64_t v_quotient_226_; uint64_t v___x_227_; uint64_t v___x_228_; uint64_t v___x_229_; uint64_t v_remainder_230_; uint64_t v___x_231_; uint64_t v_half_232_; uint8_t v___x_233_; 
v_quotient_226_ = lean_uint64_shift_right(v___y_183_, v___x_218_);
v___x_227_ = 1ULL;
v___x_228_ = lean_uint64_shift_left(v___x_227_, v___x_218_);
v___x_229_ = lean_uint64_sub(v___x_228_, v___x_227_);
v_remainder_230_ = lean_uint64_land(v___y_183_, v___x_229_);
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
v___x_236_ = lean_uint64_dec_eq(v___x_235_, v___y_181_);
if (v___x_236_ == 0)
{
uint64_t v___x_237_; 
v___x_237_ = lean_uint64_add(v_quotient_226_, v___x_227_);
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v___x_237_;
goto v___jp_96_;
}
else
{
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v_quotient_226_;
goto v___jp_96_;
}
}
else
{
uint64_t v___x_238_; 
v___x_238_ = lean_uint64_add(v_quotient_226_, v___x_227_);
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v___x_238_;
goto v___jp_96_;
}
}
else
{
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v_quotient_226_;
goto v___jp_96_;
}
}
}
else
{
v___y_97_ = v___y_181_;
v___y_98_ = v___y_182_;
v___y_99_ = v___y_183_;
goto v___jp_96_;
}
}
}
}
v___jp_239_:
{
uint64_t v___x_246_; uint64_t v___x_247_; uint8_t v___x_248_; 
v___x_246_ = 1ULL;
v___x_247_ = lean_uint64_shift_right(v___y_241_, v___x_246_);
v___x_248_ = lean_uint64_dec_eq(v___x_247_, v___y_240_);
if (v___x_248_ == 0)
{
uint64_t v___x_249_; 
v___x_249_ = lean_uint64_add(v___y_245_, v___x_246_);
v___y_181_ = v___y_240_;
v___y_182_ = v___y_242_;
v___y_183_ = v___y_243_;
v___y_184_ = v___y_244_;
v___y_185_ = v___x_249_;
goto v___jp_180_;
}
else
{
v___y_181_ = v___y_240_;
v___y_182_ = v___y_242_;
v___y_183_ = v___y_243_;
v___y_184_ = v___y_244_;
v___y_185_ = v___y_245_;
goto v___jp_180_;
}
}
v___jp_250_:
{
uint64_t v___x_259_; uint8_t v___x_260_; 
v___x_259_ = lean_uint64_shift_right(v___y_254_, v___y_256_);
v___x_260_ = lean_uint64_dec_eq(v___x_259_, v___y_251_);
if (v___x_260_ == 0)
{
uint64_t v___x_261_; 
v___x_261_ = lean_uint64_add(v___y_255_, v___y_256_);
v___y_240_ = v___y_251_;
v___y_241_ = v___y_258_;
v___y_242_ = v___y_252_;
v___y_243_ = v___y_253_;
v___y_244_ = v___y_257_;
v___y_245_ = v___x_261_;
goto v___jp_239_;
}
else
{
v___y_240_ = v___y_251_;
v___y_241_ = v___y_258_;
v___y_242_ = v___y_252_;
v___y_243_ = v___y_253_;
v___y_244_ = v___y_257_;
v___y_245_ = v___y_255_;
goto v___jp_239_;
}
}
v___jp_262_:
{
uint64_t v___x_269_; uint64_t v___x_270_; uint8_t v___x_271_; 
v___x_269_ = 2ULL;
v___x_270_ = lean_uint64_shift_right(v___y_266_, v___x_269_);
v___x_271_ = lean_uint64_dec_eq(v___x_270_, v___y_263_);
if (v___x_271_ == 0)
{
v___y_251_ = v___y_263_;
v___y_252_ = v___y_264_;
v___y_253_ = v___y_265_;
v___y_254_ = v___y_266_;
v___y_255_ = v___y_268_;
v___y_256_ = v___x_269_;
v___y_257_ = v___y_267_;
v___y_258_ = v___x_270_;
goto v___jp_250_;
}
else
{
v___y_251_ = v___y_263_;
v___y_252_ = v___y_264_;
v___y_253_ = v___y_265_;
v___y_254_ = v___y_266_;
v___y_255_ = v___y_268_;
v___y_256_ = v___x_269_;
v___y_257_ = v___y_267_;
v___y_258_ = v___y_266_;
goto v___jp_250_;
}
}
v___jp_272_:
{
uint64_t v___x_281_; uint8_t v___x_282_; 
v___x_281_ = lean_uint64_shift_right(v___y_277_, v___y_278_);
v___x_282_ = lean_uint64_dec_eq(v___x_281_, v___y_273_);
if (v___x_282_ == 0)
{
uint64_t v___x_283_; 
v___x_283_ = lean_uint64_add(v___y_274_, v___y_278_);
v___y_263_ = v___y_273_;
v___y_264_ = v___y_275_;
v___y_265_ = v___y_276_;
v___y_266_ = v___y_280_;
v___y_267_ = v___y_279_;
v___y_268_ = v___x_283_;
goto v___jp_262_;
}
else
{
v___y_263_ = v___y_273_;
v___y_264_ = v___y_275_;
v___y_265_ = v___y_276_;
v___y_266_ = v___y_280_;
v___y_267_ = v___y_279_;
v___y_268_ = v___y_274_;
goto v___jp_262_;
}
}
v___jp_284_:
{
uint64_t v___x_291_; uint64_t v___x_292_; uint8_t v___x_293_; 
v___x_291_ = 4ULL;
v___x_292_ = lean_uint64_shift_right(v___y_288_, v___x_291_);
v___x_293_ = lean_uint64_dec_eq(v___x_292_, v___y_285_);
if (v___x_293_ == 0)
{
v___y_273_ = v___y_285_;
v___y_274_ = v___y_290_;
v___y_275_ = v___y_286_;
v___y_276_ = v___y_287_;
v___y_277_ = v___y_288_;
v___y_278_ = v___x_291_;
v___y_279_ = v___y_289_;
v___y_280_ = v___x_292_;
goto v___jp_272_;
}
else
{
v___y_273_ = v___y_285_;
v___y_274_ = v___y_290_;
v___y_275_ = v___y_286_;
v___y_276_ = v___y_287_;
v___y_277_ = v___y_288_;
v___y_278_ = v___x_291_;
v___y_279_ = v___y_289_;
v___y_280_ = v___y_288_;
goto v___jp_272_;
}
}
v___jp_294_:
{
uint64_t v___x_303_; uint8_t v___x_304_; 
v___x_303_ = lean_uint64_shift_right(v___y_297_, v___y_300_);
v___x_304_ = lean_uint64_dec_eq(v___x_303_, v___y_295_);
if (v___x_304_ == 0)
{
uint64_t v___x_305_; 
v___x_305_ = lean_uint64_add(v___y_301_, v___y_300_);
v___y_285_ = v___y_295_;
v___y_286_ = v___y_296_;
v___y_287_ = v___y_298_;
v___y_288_ = v___y_302_;
v___y_289_ = v___y_299_;
v___y_290_ = v___x_305_;
goto v___jp_284_;
}
else
{
v___y_285_ = v___y_295_;
v___y_286_ = v___y_296_;
v___y_287_ = v___y_298_;
v___y_288_ = v___y_302_;
v___y_289_ = v___y_299_;
v___y_290_ = v___y_301_;
goto v___jp_284_;
}
}
v___jp_306_:
{
uint64_t v___x_313_; uint64_t v___x_314_; uint8_t v___x_315_; 
v___x_313_ = 8ULL;
v___x_314_ = lean_uint64_shift_right(v___y_310_, v___x_313_);
v___x_315_ = lean_uint64_dec_eq(v___x_314_, v___y_307_);
if (v___x_315_ == 0)
{
v___y_295_ = v___y_307_;
v___y_296_ = v___y_308_;
v___y_297_ = v___y_310_;
v___y_298_ = v___y_309_;
v___y_299_ = v___y_311_;
v___y_300_ = v___x_313_;
v___y_301_ = v___y_312_;
v___y_302_ = v___x_314_;
goto v___jp_294_;
}
else
{
v___y_295_ = v___y_307_;
v___y_296_ = v___y_308_;
v___y_297_ = v___y_310_;
v___y_298_ = v___y_309_;
v___y_299_ = v___y_311_;
v___y_300_ = v___x_313_;
v___y_301_ = v___y_312_;
v___y_302_ = v___y_310_;
goto v___jp_294_;
}
}
v___jp_316_:
{
uint64_t v___x_325_; uint8_t v___x_326_; 
v___x_325_ = lean_uint64_shift_right(v___y_322_, v___y_318_);
v___x_326_ = lean_uint64_dec_eq(v___x_325_, v___y_317_);
if (v___x_326_ == 0)
{
uint64_t v___x_327_; 
v___x_327_ = lean_uint64_add(v___y_319_, v___y_318_);
v___y_307_ = v___y_317_;
v___y_308_ = v___y_320_;
v___y_309_ = v___y_321_;
v___y_310_ = v___y_324_;
v___y_311_ = v___y_323_;
v___y_312_ = v___x_327_;
goto v___jp_306_;
}
else
{
v___y_307_ = v___y_317_;
v___y_308_ = v___y_320_;
v___y_309_ = v___y_321_;
v___y_310_ = v___y_324_;
v___y_311_ = v___y_323_;
v___y_312_ = v___y_319_;
goto v___jp_306_;
}
}
v___jp_328_:
{
uint64_t v___x_335_; uint64_t v___x_336_; uint8_t v___x_337_; 
v___x_335_ = 16ULL;
v___x_336_ = lean_uint64_shift_right(v___y_332_, v___x_335_);
v___x_337_ = lean_uint64_dec_eq(v___x_336_, v___y_329_);
if (v___x_337_ == 0)
{
v___y_317_ = v___y_329_;
v___y_318_ = v___x_335_;
v___y_319_ = v___y_334_;
v___y_320_ = v___y_330_;
v___y_321_ = v___y_331_;
v___y_322_ = v___y_332_;
v___y_323_ = v___y_333_;
v___y_324_ = v___x_336_;
goto v___jp_316_;
}
else
{
v___y_317_ = v___y_329_;
v___y_318_ = v___x_335_;
v___y_319_ = v___y_334_;
v___y_320_ = v___y_330_;
v___y_321_ = v___y_331_;
v___y_322_ = v___y_332_;
v___y_323_ = v___y_333_;
v___y_324_ = v___y_332_;
goto v___jp_316_;
}
}
v___jp_338_:
{
uint64_t v___x_345_; uint8_t v___x_346_; 
v___x_345_ = lean_uint64_shift_right(v___y_342_, v___y_340_);
v___x_346_ = lean_uint64_dec_eq(v___x_345_, v___y_339_);
if (v___x_346_ == 0)
{
v___y_329_ = v___y_339_;
v___y_330_ = v___y_341_;
v___y_331_ = v___y_342_;
v___y_332_ = v___y_344_;
v___y_333_ = v___y_343_;
v___y_334_ = v___y_340_;
goto v___jp_328_;
}
else
{
v___y_329_ = v___y_339_;
v___y_330_ = v___y_341_;
v___y_331_ = v___y_342_;
v___y_332_ = v___y_344_;
v___y_333_ = v___y_343_;
v___y_334_ = v___y_339_;
goto v___jp_328_;
}
}
v___jp_347_:
{
uint64_t v_s_352_; uint64_t v___x_353_; uint8_t v___x_354_; 
v_s_352_ = lean_uint64_add(v___y_349_, v___y_351_);
v___x_353_ = 123ULL;
v___x_354_ = lean_uint64_dec_le(v_s_352_, v___x_353_);
if (v___x_354_ == 0)
{
uint64_t v___x_355_; uint8_t v___x_356_; 
v___x_355_ = 0ULL;
v___x_356_ = lean_uint64_dec_eq(v___y_350_, v___x_355_);
if (v___x_356_ == 0)
{
uint64_t v___x_357_; uint64_t v___x_358_; uint8_t v___x_359_; 
v___x_357_ = 32ULL;
v___x_358_ = lean_uint64_shift_right(v___y_350_, v___x_357_);
v___x_359_ = lean_uint64_dec_eq(v___x_358_, v___x_355_);
if (v___x_359_ == 0)
{
v___y_339_ = v___x_355_;
v___y_340_ = v___x_357_;
v___y_341_ = v___y_348_;
v___y_342_ = v___y_350_;
v___y_343_ = v_s_352_;
v___y_344_ = v___x_358_;
goto v___jp_338_;
}
else
{
v___y_339_ = v___x_355_;
v___y_340_ = v___x_357_;
v___y_341_ = v___y_348_;
v___y_342_ = v___y_350_;
v___y_343_ = v_s_352_;
v___y_344_ = v___y_350_;
goto v___jp_338_;
}
}
else
{
if (v___y_348_ == 0)
{
uint32_t v___x_360_; 
v___x_360_ = 0;
return v___x_360_;
}
else
{
uint32_t v___x_361_; 
v___x_361_ = 2147483648;
return v___x_361_;
}
}
}
else
{
uint64_t v___x_362_; uint8_t v___x_363_; 
v___x_362_ = 0ULL;
v___x_363_ = lean_uint64_dec_eq(v___y_350_, v___x_362_);
if (v___x_363_ == 0)
{
uint64_t v___x_364_; uint64_t v___x_365_; uint8_t v___x_366_; 
v___x_364_ = 149ULL;
v___x_365_ = lean_uint64_sub(v___x_364_, v_s_352_);
v___x_366_ = lean_uint64_dec_eq(v___x_365_, v___x_362_);
if (v___x_366_ == 0)
{
uint64_t v___x_367_; uint8_t v___x_368_; 
v___x_367_ = 64ULL;
v___x_368_ = lean_uint64_dec_lt(v___x_365_, v___x_367_);
if (v___x_368_ == 0)
{
uint8_t v___x_369_; 
v___x_369_ = lean_uint64_dec_eq(v___x_365_, v___x_367_);
if (v___x_369_ == 0)
{
v___y_115_ = v___x_362_;
v___y_116_ = v___y_348_;
v___y_117_ = v___x_362_;
goto v___jp_114_;
}
else
{
uint64_t v___x_370_; uint8_t v___x_371_; 
v___x_370_ = 9223372036854775808ULL;
v___x_371_ = lean_uint64_dec_lt(v___x_370_, v___y_350_);
if (v___x_371_ == 0)
{
v___y_115_ = v___x_362_;
v___y_116_ = v___y_348_;
v___y_117_ = v___x_362_;
goto v___jp_114_;
}
else
{
uint64_t v___x_372_; 
v___x_372_ = 1ULL;
v___y_115_ = v___x_362_;
v___y_116_ = v___y_348_;
v___y_117_ = v___x_372_;
goto v___jp_114_;
}
}
}
else
{
uint64_t v_quotient_373_; uint64_t v___x_374_; uint64_t v___x_375_; uint64_t v___x_376_; uint64_t v_remainder_377_; uint64_t v___x_378_; uint64_t v_half_379_; uint8_t v___x_380_; 
v_quotient_373_ = lean_uint64_shift_right(v___y_350_, v___x_365_);
v___x_374_ = 1ULL;
v___x_375_ = lean_uint64_shift_left(v___x_374_, v___x_365_);
v___x_376_ = lean_uint64_sub(v___x_375_, v___x_374_);
v_remainder_377_ = lean_uint64_land(v___y_350_, v___x_376_);
v___x_378_ = lean_uint64_sub(v___x_365_, v___x_374_);
v_half_379_ = lean_uint64_shift_left(v___x_374_, v___x_378_);
v___x_380_ = lean_uint64_dec_lt(v_remainder_377_, v_half_379_);
if (v___x_380_ == 0)
{
uint8_t v___x_381_; 
v___x_381_ = lean_uint64_dec_lt(v_half_379_, v_remainder_377_);
if (v___x_381_ == 0)
{
uint64_t v___x_382_; uint8_t v___x_383_; 
v___x_382_ = lean_uint64_land(v_quotient_373_, v___x_374_);
v___x_383_ = lean_uint64_dec_eq(v___x_382_, v___x_362_);
if (v___x_383_ == 0)
{
uint64_t v___x_384_; 
v___x_384_ = lean_uint64_add(v_quotient_373_, v___x_374_);
v___y_115_ = v___x_362_;
v___y_116_ = v___y_348_;
v___y_117_ = v___x_384_;
goto v___jp_114_;
}
else
{
v___y_115_ = v___x_362_;
v___y_116_ = v___y_348_;
v___y_117_ = v_quotient_373_;
goto v___jp_114_;
}
}
else
{
uint64_t v___x_385_; 
v___x_385_ = lean_uint64_add(v_quotient_373_, v___x_374_);
v___y_115_ = v___x_362_;
v___y_116_ = v___y_348_;
v___y_117_ = v___x_385_;
goto v___jp_114_;
}
}
else
{
v___y_115_ = v___x_362_;
v___y_116_ = v___y_348_;
v___y_117_ = v_quotient_373_;
goto v___jp_114_;
}
}
}
else
{
v___y_115_ = v___x_362_;
v___y_116_ = v___y_348_;
v___y_117_ = v___y_350_;
goto v___jp_114_;
}
}
else
{
if (v___y_348_ == 0)
{
uint32_t v___x_386_; 
v___x_386_ = 0;
return v___x_386_;
}
else
{
uint32_t v___x_387_; 
v___x_387_ = 2147483648;
return v___x_387_;
}
}
}
}
v___jp_391_:
{
uint64_t v___x_395_; uint64_t v___x_396_; uint8_t v___x_397_; 
v___x_395_ = lean_uint32_to_uint64(v_ey_390_);
v___x_396_ = 0ULL;
v___x_397_ = lean_uint64_dec_eq(v___x_395_, v___x_396_);
if (v___x_397_ == 0)
{
uint64_t v___x_398_; uint64_t v___x_399_; 
v___x_398_ = 1ULL;
v___x_399_ = lean_uint64_sub(v___x_395_, v___x_398_);
v___y_348_ = v___y_392_;
v___y_349_ = v___y_394_;
v___y_350_ = v___y_393_;
v___y_351_ = v___x_399_;
goto v___jp_347_;
}
else
{
v___y_348_ = v___y_392_;
v___y_349_ = v___y_394_;
v___y_350_ = v___y_393_;
v___y_351_ = v___x_396_;
goto v___jp_347_;
}
}
v___jp_400_:
{
uint64_t v_p_404_; uint64_t v___x_405_; uint64_t v___x_406_; uint8_t v___x_407_; 
v_p_404_ = lean_uint64_mul(v___y_402_, v___y_403_);
v___x_405_ = lean_uint32_to_uint64(v_ex_388_);
v___x_406_ = 0ULL;
v___x_407_ = lean_uint64_dec_eq(v___x_405_, v___x_406_);
if (v___x_407_ == 0)
{
uint64_t v___x_408_; uint64_t v___x_409_; 
v___x_408_ = 1ULL;
v___x_409_ = lean_uint64_sub(v___x_405_, v___x_408_);
v___y_392_ = v___y_401_;
v___y_393_ = v_p_404_;
v___y_394_ = v___x_409_;
goto v___jp_391_;
}
else
{
v___y_392_ = v___y_401_;
v___y_393_ = v_p_404_;
v___y_394_ = v___x_406_;
goto v___jp_391_;
}
}
v___jp_410_:
{
uint32_t v___x_413_; uint32_t v___x_414_; uint32_t v___x_415_; uint8_t v___x_416_; 
v___x_413_ = 8388607;
v___x_414_ = lean_uint32_land(v___y_74_, v___x_413_);
v___x_415_ = 0;
v___x_416_ = lean_uint32_dec_eq(v_ey_390_, v___x_415_);
if (v___x_416_ == 0)
{
uint64_t v___x_417_; uint64_t v___x_418_; uint64_t v___x_419_; 
v___x_417_ = lean_uint32_to_uint64(v___x_414_);
v___x_418_ = 8388608ULL;
v___x_419_ = lean_uint64_lor(v___x_417_, v___x_418_);
v___y_401_ = v___y_411_;
v___y_402_ = v___y_412_;
v___y_403_ = v___x_419_;
goto v___jp_400_;
}
else
{
uint64_t v___x_420_; 
v___x_420_ = lean_uint32_to_uint64(v___x_414_);
v___y_401_ = v___y_411_;
v___y_402_ = v___y_412_;
v___y_403_ = v___x_420_;
goto v___jp_400_;
}
}
v___jp_421_:
{
uint32_t v___x_423_; uint32_t v___x_424_; uint32_t v___x_425_; uint8_t v___x_426_; 
v___x_423_ = 8388607;
v___x_424_ = lean_uint32_land(v___y_73_, v___x_423_);
v___x_425_ = 0;
v___x_426_ = lean_uint32_dec_eq(v_ex_388_, v___x_425_);
if (v___x_426_ == 0)
{
uint64_t v___x_427_; uint64_t v___x_428_; uint64_t v___x_429_; 
v___x_427_ = lean_uint32_to_uint64(v___x_424_);
v___x_428_ = 8388608ULL;
v___x_429_ = lean_uint64_lor(v___x_427_, v___x_428_);
v___y_411_ = v___y_422_;
v___y_412_ = v___x_429_;
goto v___jp_410_;
}
else
{
uint64_t v___x_430_; 
v___x_430_ = lean_uint32_to_uint64(v___x_424_);
v___y_411_ = v___y_422_;
v___y_412_ = v___x_430_;
goto v___jp_410_;
}
}
v___jp_431_:
{
uint8_t v___x_432_; 
v___x_432_ = 0;
v___y_422_ = v___x_432_;
goto v___jp_421_;
}
v___jp_436_:
{
if (v___y_437_ == 0)
{
if (v___y_438_ == 0)
{
goto v___jp_431_;
}
else
{
v___y_422_ = v___x_435_;
goto v___jp_421_;
}
}
else
{
if (v___y_438_ == 0)
{
v___y_422_ = v___x_435_;
goto v___jp_421_;
}
else
{
goto v___jp_431_;
}
}
}
v___jp_439_:
{
uint32_t v___x_441_; uint32_t v___x_442_; uint32_t v___x_443_; uint8_t v___x_444_; 
v___x_441_ = 2147483648;
v___x_442_ = lean_uint32_land(v___y_74_, v___x_441_);
v___x_443_ = 0;
v___x_444_ = lean_uint32_dec_eq(v___x_442_, v___x_443_);
if (v___x_444_ == 0)
{
v___y_437_ = v___y_440_;
v___y_438_ = v___x_435_;
goto v___jp_436_;
}
else
{
uint8_t v___x_445_; 
v___x_445_ = 0;
v___y_437_ = v___y_440_;
v___y_438_ = v___x_445_;
goto v___jp_436_;
}
}
v___jp_446_:
{
uint8_t v___x_447_; 
v___x_447_ = lean_uint32_dec_eq(v_ey_390_, v___x_130_);
if (v___x_447_ == 0)
{
goto v___jp_75_;
}
else
{
if (v___x_435_ == 0)
{
uint32_t v___x_448_; 
v___x_448_ = lp_competition_Submission_FastMul_mul(v___y_73_, v___y_74_);
return v___x_448_;
}
else
{
goto v___jp_75_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_456_, lean_object* v___y_457_){
_start:
{
uint32_t v___y_1274__boxed_458_; uint32_t v___y_1275__boxed_459_; uint32_t v_res_460_; lean_object* v_r_461_; 
v___y_1274__boxed_458_ = lean_unbox_uint32(v___y_456_);
lean_dec(v___y_456_);
v___y_1275__boxed_459_ = lean_unbox_uint32(v___y_457_);
lean_dec(v___y_457_);
v_res_460_ = lp_competition_main___lam__1(v___y_1274__boxed_458_, v___y_1275__boxed_459_);
v_r_461_ = lean_box_uint32(v_res_460_);
return v_r_461_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___f_467_; lean_object* v___f_468_; lean_object* v___x_469_; lean_object* v___x_470_; lean_object* v___x_471_; 
v___f_467_ = ((lean_object*)(lp_competition_main___closed__0));
v___f_468_ = ((lean_object*)(lp_competition_main___closed__1));
v___x_469_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_470_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_471_ = lp_competition_Bench_runFull(v___f_467_, v___f_468_, v___x_469_, v___x_470_);
return v___x_471_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_472_){
_start:
{
lean_object* v_res_473_; 
v_res_473_ = _lean_main();
return v_res_473_;
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
