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
uint32_t v___y_418__boxed_69_; uint32_t v___y_419__boxed_70_; uint32_t v_res_71_; lean_object* v_r_72_; 
v___y_418__boxed_69_ = lean_unbox_uint32(v___y_67_);
lean_dec(v___y_67_);
v___y_419__boxed_70_ = lean_unbox_uint32(v___y_68_);
lean_dec(v___y_68_);
v_res_71_ = lp_competition_main___lam__0(v___y_418__boxed_69_, v___y_419__boxed_70_);
v_r_72_ = lean_box_uint32(v_res_71_);
return v_r_72_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_73_, uint32_t v___y_74_){
_start:
{
float v___y_76_; float v___y_77_; float v___y_81_; uint8_t v___y_82_; float v___y_97_; uint8_t v___y_107_; uint32_t v___x_121_; uint32_t v___x_122_; uint32_t v___x_123_; uint32_t v___x_124_; uint8_t v___x_125_; 
v___x_121_ = 23;
v___x_122_ = lean_uint32_shift_right(v___y_73_, v___x_121_);
v___x_123_ = 255;
v___x_124_ = lean_uint32_land(v___x_122_, v___x_123_);
v___x_125_ = lean_uint32_dec_eq(v___x_124_, v___x_123_);
if (v___x_125_ == 0)
{
uint32_t v___x_126_; uint32_t v___x_127_; uint8_t v___x_128_; 
v___x_126_ = lean_uint32_shift_right(v___y_74_, v___x_121_);
v___x_127_ = lean_uint32_land(v___x_126_, v___x_123_);
v___x_128_ = lean_uint32_dec_eq(v___x_127_, v___x_123_);
if (v___x_128_ == 0)
{
uint32_t v___x_129_; uint32_t v_a_130_; uint32_t v___x_131_; uint32_t v___x_132_; uint32_t v___x_133_; uint8_t v___x_134_; 
v___x_129_ = 2147483647;
v_a_130_ = lean_uint32_land(v___y_73_, v___x_129_);
v___x_131_ = 201326591;
v___x_132_ = 1;
v___x_133_ = lean_uint32_sub(v_a_130_, v___x_132_);
v___x_134_ = lean_uint32_dec_le(v___x_131_, v___x_133_);
if (v___x_134_ == 0)
{
v___y_107_ = v___x_134_;
goto v___jp_106_;
}
else
{
uint32_t v___x_135_; uint8_t v___x_136_; 
v___x_135_ = 2139095040;
v___x_136_ = lean_uint32_dec_lt(v_a_130_, v___x_135_);
v___y_107_ = v___x_136_;
goto v___jp_106_;
}
}
else
{
uint32_t v___x_137_; 
v___x_137_ = lp_competition_Submission_FastMul_mul(v___y_73_, v___y_74_);
return v___x_137_;
}
}
else
{
uint32_t v___x_138_; 
v___x_138_ = lp_competition_Submission_FastMul_mul(v___y_73_, v___y_74_);
return v___x_138_;
}
v___jp_75_:
{
float v___x_78_; uint32_t v___x_79_; 
v___x_78_ = lean_float32_mul(v___y_76_, v___y_77_);
v___x_79_ = lean_float32_to_bits(v___x_78_);
return v___x_79_;
}
v___jp_80_:
{
if (v___y_82_ == 0)
{
float v___x_83_; 
v___x_83_ = lean_float32_of_bits(v___y_74_);
v___y_76_ = v___y_81_;
v___y_77_ = v___x_83_;
goto v___jp_75_;
}
else
{
uint32_t v___x_84_; uint32_t v___x_85_; uint32_t v___x_86_; uint32_t v___x_87_; float v___x_88_; lean_object* v___x_89_; uint32_t v___x_90_; uint32_t v___x_91_; lean_object* v___x_92_; lean_object* v___x_93_; float v___x_94_; float v___x_95_; 
v___x_84_ = 8388607;
v___x_85_ = lean_uint32_land(v___y_74_, v___x_84_);
v___x_86_ = 8388608;
v___x_87_ = lean_uint32_lor(v___x_85_, v___x_86_);
v___x_88_ = lean_uint32_to_float32(v___x_87_);
v___x_89_ = lp_competition_R2W01b_scaleTable;
v___x_90_ = 23;
v___x_91_ = lean_uint32_shift_right(v___y_74_, v___x_90_);
v___x_92_ = lean_uint32_to_nat(v___x_91_);
v___x_93_ = lean_array_fget_borrowed(v___x_89_, v___x_92_);
lean_dec(v___x_92_);
v___x_94_ = lean_unbox_float32(v___x_93_);
v___x_95_ = lean_float32_mul(v___x_88_, v___x_94_);
v___y_76_ = v___y_81_;
v___y_77_ = v___x_95_;
goto v___jp_75_;
}
}
v___jp_96_:
{
uint32_t v___x_98_; uint32_t v_a_99_; uint32_t v___x_100_; uint32_t v___x_101_; uint32_t v___x_102_; uint8_t v___x_103_; 
v___x_98_ = 2147483647;
v_a_99_ = lean_uint32_land(v___y_74_, v___x_98_);
v___x_100_ = 201326591;
v___x_101_ = 1;
v___x_102_ = lean_uint32_sub(v_a_99_, v___x_101_);
v___x_103_ = lean_uint32_dec_le(v___x_100_, v___x_102_);
if (v___x_103_ == 0)
{
v___y_81_ = v___y_97_;
v___y_82_ = v___x_103_;
goto v___jp_80_;
}
else
{
uint32_t v___x_104_; uint8_t v___x_105_; 
v___x_104_ = 2139095040;
v___x_105_ = lean_uint32_dec_lt(v_a_99_, v___x_104_);
v___y_81_ = v___y_97_;
v___y_82_ = v___x_105_;
goto v___jp_80_;
}
}
v___jp_106_:
{
if (v___y_107_ == 0)
{
float v___x_108_; 
v___x_108_ = lean_float32_of_bits(v___y_73_);
v___y_97_ = v___x_108_;
goto v___jp_96_;
}
else
{
uint32_t v___x_109_; uint32_t v___x_110_; uint32_t v___x_111_; uint32_t v___x_112_; float v___x_113_; lean_object* v___x_114_; uint32_t v___x_115_; uint32_t v___x_116_; lean_object* v___x_117_; lean_object* v___x_118_; float v___x_119_; float v___x_120_; 
v___x_109_ = 8388607;
v___x_110_ = lean_uint32_land(v___y_73_, v___x_109_);
v___x_111_ = 8388608;
v___x_112_ = lean_uint32_lor(v___x_110_, v___x_111_);
v___x_113_ = lean_uint32_to_float32(v___x_112_);
v___x_114_ = lp_competition_R2W01b_scaleTable;
v___x_115_ = 23;
v___x_116_ = lean_uint32_shift_right(v___y_73_, v___x_115_);
v___x_117_ = lean_uint32_to_nat(v___x_116_);
v___x_118_ = lean_array_fget_borrowed(v___x_114_, v___x_117_);
lean_dec(v___x_117_);
v___x_119_ = lean_unbox_float32(v___x_118_);
v___x_120_ = lean_float32_mul(v___x_113_, v___x_119_);
v___y_97_ = v___x_120_;
goto v___jp_96_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_139_, lean_object* v___y_140_){
_start:
{
uint32_t v___y_548__boxed_141_; uint32_t v___y_549__boxed_142_; uint32_t v_res_143_; lean_object* v_r_144_; 
v___y_548__boxed_141_ = lean_unbox_uint32(v___y_139_);
lean_dec(v___y_139_);
v___y_549__boxed_142_ = lean_unbox_uint32(v___y_140_);
lean_dec(v___y_140_);
v_res_143_ = lp_competition_main___lam__1(v___y_548__boxed_141_, v___y_549__boxed_142_);
v_r_144_ = lean_box_uint32(v_res_143_);
return v_r_144_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___f_150_; lean_object* v___f_151_; lean_object* v___x_152_; lean_object* v___x_153_; lean_object* v___x_154_; 
v___f_150_ = ((lean_object*)(lp_competition_main___closed__0));
v___f_151_ = ((lean_object*)(lp_competition_main___closed__1));
v___x_152_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_153_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_154_ = lp_competition_Bench_runFull(v___f_150_, v___f_151_, v___x_152_, v___x_153_);
return v___x_154_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_155_){
_start:
{
lean_object* v_res_156_; 
v_res_156_ = _lean_main();
return v_res_156_;
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
