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
float lean_float32_of_bits(uint32_t);
uint8_t lean_float32_isfinite(float);
uint32_t lp_competition_Submission_TunedAdd_add(uint32_t, uint32_t);
float lean_float32_add(float, float);
uint32_t lean_float32_to_bits(float);
uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
float lean_float32_mul(float, float);
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
float v_fx_3_; uint8_t v___x_4_; 
v_fx_3_ = lean_float32_of_bits(v___y_1_);
v___x_4_ = lean_float32_isfinite(v_fx_3_);
if (v___x_4_ == 0)
{
uint32_t v___x_5_; 
v___x_5_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_5_;
}
else
{
float v_fy_6_; uint8_t v___x_7_; 
v_fy_6_ = lean_float32_of_bits(v___y_2_);
v___x_7_ = lean_float32_isfinite(v_fy_6_);
if (v___x_7_ == 0)
{
uint32_t v___x_8_; 
v___x_8_ = lp_competition_Submission_TunedAdd_add(v___y_1_, v___y_2_);
return v___x_8_;
}
else
{
float v___x_9_; uint32_t v___x_10_; 
v___x_9_ = lean_float32_add(v_fx_3_, v_fy_6_);
v___x_10_ = lean_float32_to_bits(v___x_9_);
return v___x_10_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__0___boxed(lean_object* v___y_11_, lean_object* v___y_12_){
_start:
{
uint32_t v___y_54__boxed_13_; uint32_t v___y_55__boxed_14_; uint32_t v_res_15_; lean_object* v_r_16_; 
v___y_54__boxed_13_ = lean_unbox_uint32(v___y_11_);
lean_dec(v___y_11_);
v___y_55__boxed_14_ = lean_unbox_uint32(v___y_12_);
lean_dec(v___y_12_);
v_res_15_ = lp_competition_main___lam__0(v___y_54__boxed_13_, v___y_55__boxed_14_);
v_r_16_ = lean_box_uint32(v_res_15_);
return v_r_16_;
}
}
LEAN_EXPORT uint32_t lp_competition_main___lam__1(uint32_t v___y_17_, uint32_t v___y_18_){
_start:
{
float v_fx_19_; uint8_t v___x_20_; 
v_fx_19_ = lean_float32_of_bits(v___y_17_);
v___x_20_ = lean_float32_isfinite(v_fx_19_);
if (v___x_20_ == 0)
{
uint32_t v___x_21_; 
v___x_21_ = lp_competition_Submission_FastMul_mul(v___y_17_, v___y_18_);
return v___x_21_;
}
else
{
float v_fy_22_; uint8_t v___x_23_; 
v_fy_22_ = lean_float32_of_bits(v___y_18_);
v___x_23_ = lean_float32_isfinite(v_fy_22_);
if (v___x_23_ == 0)
{
uint32_t v___x_24_; 
v___x_24_ = lp_competition_Submission_FastMul_mul(v___y_17_, v___y_18_);
return v___x_24_;
}
else
{
float v___x_25_; uint32_t v___x_26_; 
v___x_25_ = lean_float32_mul(v_fx_19_, v_fy_22_);
v___x_26_ = lean_float32_to_bits(v___x_25_);
return v___x_26_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___lam__1___boxed(lean_object* v___y_27_, lean_object* v___y_28_){
_start:
{
uint32_t v___y_72__boxed_29_; uint32_t v___y_73__boxed_30_; uint32_t v_res_31_; lean_object* v_r_32_; 
v___y_72__boxed_29_ = lean_unbox_uint32(v___y_27_);
lean_dec(v___y_27_);
v___y_73__boxed_30_ = lean_unbox_uint32(v___y_28_);
lean_dec(v___y_28_);
v_res_31_ = lp_competition_main___lam__1(v___y_72__boxed_29_, v___y_73__boxed_30_);
v_r_32_ = lean_box_uint32(v_res_31_);
return v_r_32_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___f_38_; lean_object* v___f_39_; lean_object* v___x_40_; lean_object* v___x_41_; lean_object* v___x_42_; 
v___f_38_ = ((lean_object*)(lp_competition_main___closed__0));
v___f_39_ = ((lean_object*)(lp_competition_main___closed__1));
v___x_40_ = ((lean_object*)(lp_competition_main___closed__2));
v___x_41_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_42_ = lp_competition_Bench_runFull(v___f_38_, v___f_39_, v___x_40_, v___x_41_);
return v___x_42_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_43_){
_start:
{
lean_object* v_res_44_; 
v_res_44_ = _lean_main();
return v_res_44_;
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
