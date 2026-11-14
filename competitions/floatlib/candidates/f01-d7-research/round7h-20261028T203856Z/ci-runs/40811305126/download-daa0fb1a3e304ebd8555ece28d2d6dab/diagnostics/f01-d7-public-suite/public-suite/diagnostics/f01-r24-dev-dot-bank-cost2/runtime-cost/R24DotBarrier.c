// Lean compiler output
// Module: R24DotBarrier
// Imports: public import Init public meta import Init public import Submission
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
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchBank(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchBank___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchBank(lean_object* v_i_1_, lean_object* v_p_2_){
_start:
{
lean_object* v___x_3_; uint8_t v___x_4_; 
v___x_3_ = lean_unsigned_to_nat(1000000007u);
v___x_4_ = lean_nat_dec_eq(v_i_1_, v___x_3_);
if (v___x_4_ == 0)
{
return v_p_2_;
}
else
{
lean_object* v_fst_5_; lean_object* v___x_7_; uint8_t v_isShared_8_; uint8_t v_isSharedCheck_12_; 
v_fst_5_ = lean_ctor_get(v_p_2_, 0);
v_isSharedCheck_12_ = !lean_is_exclusive(v_p_2_);
if (v_isSharedCheck_12_ == 0)
{
lean_object* v_unused_13_; 
v_unused_13_ = lean_ctor_get(v_p_2_, 1);
lean_dec(v_unused_13_);
v___x_7_ = v_p_2_;
v_isShared_8_ = v_isSharedCheck_12_;
goto v_resetjp_6_;
}
else
{
lean_inc(v_fst_5_);
lean_dec(v_p_2_);
v___x_7_ = lean_box(0);
v_isShared_8_ = v_isSharedCheck_12_;
goto v_resetjp_6_;
}
v_resetjp_6_:
{
lean_object* v___x_10_; 
lean_inc(v_fst_5_);
if (v_isShared_8_ == 0)
{
lean_ctor_set(v___x_7_, 1, v_fst_5_);
v___x_10_ = v___x_7_;
goto v_reusejp_9_;
}
else
{
lean_object* v_reuseFailAlloc_11_; 
v_reuseFailAlloc_11_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_11_, 0, v_fst_5_);
lean_ctor_set(v_reuseFailAlloc_11_, 1, v_fst_5_);
v___x_10_ = v_reuseFailAlloc_11_;
goto v_reusejp_9_;
}
v_reusejp_9_:
{
return v___x_10_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchBank___boxed(lean_object* v_i_14_, lean_object* v_p_15_){
_start:
{
lean_object* v_res_16_; 
v_res_16_ = lp_competition_R24DotBarrier_touchBank(v_i_14_, v_p_15_);
lean_dec(v_i_14_);
return v_res_16_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R24DotBarrier(uint8_t builtin) {
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
res = initialize_competition_Submission(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
