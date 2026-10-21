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
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
float lean_float32_of_bits(uint32_t);
float lean_float32_add(float, float);
uint32_t lean_float32_to_bits(float);
uint32_t lp_competition_Submission_TunedAdd_add(uint32_t, uint32_t);
float lean_float32_mul(float, float);
uint32_t lean_uint32_add(uint32_t, uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
uint32_t lp_competition_Submission_RebuiltMul_mul(uint32_t, uint32_t);
lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
lean_object* lp_competition_Submission_bmm___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
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
static const lean_closure_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_bmm___boxed, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1_, uint32_t v___y_2_){
_start:
{
uint32_t v___x_3_; uint32_t v___x_4_; uint32_t v___x_5_; uint32_t v___x_6_; uint8_t v___x_7_; 
v___x_3_ = 23;
v___x_4_ = lean_uint32_shift_right(v___y_1_, v___x_3_);
v___x_5_ = 255;
v___x_6_ = lean_uint32_land(v___x_4_, v___x_5_);
v___x_7_ = lean_uint32_dec_eq(v___x_6_, v___x_5_);
if (v___x_7_ == 0)
{
uint32_t v___x_8_; uint32_t v___x_9_; uint8_t v___x_10_; 
v___x_8_ = lean_uint32_shift_right(v___y_2_, v___x_3_);
v___x_9_ = lean_uint32_land(v___x_8_, v___x_5_);
v___x_10_ = lean_uint32_dec_eq(v___x_9_, v___x_5_);
if (v___x_10_ == 0)
{
float v___x_11_; float v___x_12_; float v___x_13_; uint32_t v___x_14_; 
v___x_11_ = lean_float32_of_bits(v___y_1_);
v___x_12_ = lean_float32_of_bits(v___y_2_);
v___x_13_ = lean_float32_add(v___x_11_, v___x_12_);
v___x_14_ = lean_float32_to_bits(v___x_13_);
return v___x_14_;
}
else
{
uint32_t v___x_15_; 
v___x_15_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_15_;
}
}
else
{
uint32_t v___x_16_; 
v___x_16_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_16_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_17_, lean_object* v___y_18_){
_start:
{
uint32_t v___y_183__boxed_19_; uint32_t v___y_184__boxed_20_; uint32_t v_res_21_; lean_object* v_r_22_; 
v___y_183__boxed_19_ = lean_unbox_uint32(v___y_17_);
lean_dec(v___y_17_);
v___y_184__boxed_20_ = lean_unbox_uint32(v___y_18_);
lean_dec(v___y_18_);
v_res_21_ = lp_competition_main___lam__0(v___y_183__boxed_19_, v___y_184__boxed_20_);
v_r_22_ = lean_box_uint32(v_res_21_);
return v_r_22_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_23_, uint32_t v___y_24_){
_start:
{
uint32_t v___x_30_; uint32_t v___x_31_; uint32_t v___x_32_; uint32_t v_ex_33_; uint32_t v___x_34_; uint32_t v_ey_35_; uint32_t v___x_36_; uint32_t v___x_37_; uint8_t v___x_38_; 
v___x_30_ = 23;
v___x_31_ = lean_uint32_shift_right(v___y_23_, v___x_30_);
v___x_32_ = 255;
v_ex_33_ = lean_uint32_land(v___x_31_, v___x_32_);
v___x_34_ = lean_uint32_shift_right(v___y_24_, v___x_30_);
v_ey_35_ = lean_uint32_land(v___x_34_, v___x_32_);
v___x_36_ = lean_uint32_add(v_ex_33_, v_ey_35_);
v___x_37_ = 128;
v___x_38_ = lean_uint32_dec_lt(v___x_36_, v___x_37_);
if (v___x_38_ == 0)
{
uint8_t v___x_42_; 
v___x_42_ = lean_uint32_dec_eq(v_ex_33_, v___x_32_);
if (v___x_42_ == 0)
{
goto v___jp_39_;
}
else
{
if (v___x_38_ == 0)
{
uint32_t v___x_43_; 
v___x_43_ = lp_competition_Submission_FastMul_mul(v___y_23_, v___y_24_);
return v___x_43_;
}
else
{
goto v___jp_39_;
}
}
}
else
{
uint32_t v___x_44_; 
v___x_44_ = lp_competition_Submission_RebuiltMul_mul(v___y_23_, v___y_24_);
return v___x_44_;
}
v___jp_25_:
{
float v___x_26_; float v___x_27_; float v___x_28_; uint32_t v___x_29_; 
v___x_26_ = lean_float32_of_bits(v___y_23_);
v___x_27_ = lean_float32_of_bits(v___y_24_);
v___x_28_ = lean_float32_mul(v___x_26_, v___x_27_);
v___x_29_ = lean_float32_to_bits(v___x_28_);
return v___x_29_;
}
v___jp_39_:
{
uint8_t v___x_40_; 
v___x_40_ = lean_uint32_dec_eq(v_ey_35_, v___x_32_);
if (v___x_40_ == 0)
{
goto v___jp_25_;
}
else
{
if (v___x_38_ == 0)
{
uint32_t v___x_41_; 
v___x_41_ = lp_competition_Submission_FastMul_mul(v___y_23_, v___y_24_);
return v___x_41_;
}
else
{
goto v___jp_25_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_45_, lean_object* v___y_46_){
_start:
{
uint32_t v___y_217__boxed_47_; uint32_t v___y_218__boxed_48_; uint32_t v_res_49_; lean_object* v_r_50_; 
v___y_217__boxed_47_ = lean_unbox_uint32(v___y_45_);
lean_dec(v___y_45_);
v___y_218__boxed_48_ = lean_unbox_uint32(v___y_46_);
lean_dec(v___y_46_);
v_res_49_ = lp_competition_main___lam__1(v___y_217__boxed_47_, v___y_218__boxed_48_);
v_r_50_ = lean_box_uint32(v_res_49_);
return v_r_50_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___f_56_; lean_object* v___f_57_; lean_object* v___x_58_; lean_object* v___x_59_; lean_object* v___x_60_; 
v___f_56_ = ((lean_object*)(lp_competition_main___closed__0));
v___f_57_ = ((lean_object*)(lp_competition_main___closed__1));
v___x_58_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_59_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_60_ = lp_competition_Bench_runFull(v___f_56_, v___f_57_, v___x_58_, v___x_59_);
return v___x_60_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_61_){
_start:
{
lean_object* v_res_62_; 
v_res_62_ = _lean_main();
return v_res_62_;
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
