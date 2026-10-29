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
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchRaw(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchRaw___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchExact(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchExact___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchLazy(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchLazy___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchEager(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchEager___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchRaw(lean_object* v_i_1_, lean_object* v_p_2_){
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
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchRaw___boxed(lean_object* v_i_14_, lean_object* v_p_15_){
_start:
{
lean_object* v_res_16_; 
v_res_16_ = lp_competition_R24DotBarrier_touchRaw(v_i_14_, v_p_15_);
lean_dec(v_i_14_);
return v_res_16_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchExact(lean_object* v_i_17_, lean_object* v_p_18_){
_start:
{
lean_object* v___x_19_; uint8_t v___x_20_; 
v___x_19_ = lean_unsigned_to_nat(1000000007u);
v___x_20_ = lean_nat_dec_eq(v_i_17_, v___x_19_);
if (v___x_20_ == 0)
{
return v_p_18_;
}
else
{
lean_object* v_fst_21_; lean_object* v___x_23_; uint8_t v_isShared_24_; uint8_t v_isSharedCheck_28_; 
v_fst_21_ = lean_ctor_get(v_p_18_, 0);
v_isSharedCheck_28_ = !lean_is_exclusive(v_p_18_);
if (v_isSharedCheck_28_ == 0)
{
lean_object* v_unused_29_; 
v_unused_29_ = lean_ctor_get(v_p_18_, 1);
lean_dec(v_unused_29_);
v___x_23_ = v_p_18_;
v_isShared_24_ = v_isSharedCheck_28_;
goto v_resetjp_22_;
}
else
{
lean_inc(v_fst_21_);
lean_dec(v_p_18_);
v___x_23_ = lean_box(0);
v_isShared_24_ = v_isSharedCheck_28_;
goto v_resetjp_22_;
}
v_resetjp_22_:
{
lean_object* v___x_26_; 
lean_inc(v_fst_21_);
if (v_isShared_24_ == 0)
{
lean_ctor_set(v___x_23_, 1, v_fst_21_);
v___x_26_ = v___x_23_;
goto v_reusejp_25_;
}
else
{
lean_object* v_reuseFailAlloc_27_; 
v_reuseFailAlloc_27_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_27_, 0, v_fst_21_);
lean_ctor_set(v_reuseFailAlloc_27_, 1, v_fst_21_);
v___x_26_ = v_reuseFailAlloc_27_;
goto v_reusejp_25_;
}
v_reusejp_25_:
{
return v___x_26_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchExact___boxed(lean_object* v_i_30_, lean_object* v_p_31_){
_start:
{
lean_object* v_res_32_; 
v_res_32_ = lp_competition_R24DotBarrier_touchExact(v_i_30_, v_p_31_);
lean_dec(v_i_30_);
return v_res_32_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchLazy(lean_object* v_i_33_, lean_object* v_p_34_){
_start:
{
lean_object* v___x_35_; uint8_t v___x_36_; 
v___x_35_ = lean_unsigned_to_nat(1000000007u);
v___x_36_ = lean_nat_dec_eq(v_i_33_, v___x_35_);
if (v___x_36_ == 0)
{
return v_p_34_;
}
else
{
lean_object* v_fst_37_; lean_object* v___x_39_; uint8_t v_isShared_40_; uint8_t v_isSharedCheck_44_; 
v_fst_37_ = lean_ctor_get(v_p_34_, 0);
v_isSharedCheck_44_ = !lean_is_exclusive(v_p_34_);
if (v_isSharedCheck_44_ == 0)
{
lean_object* v_unused_45_; 
v_unused_45_ = lean_ctor_get(v_p_34_, 1);
lean_dec(v_unused_45_);
v___x_39_ = v_p_34_;
v_isShared_40_ = v_isSharedCheck_44_;
goto v_resetjp_38_;
}
else
{
lean_inc(v_fst_37_);
lean_dec(v_p_34_);
v___x_39_ = lean_box(0);
v_isShared_40_ = v_isSharedCheck_44_;
goto v_resetjp_38_;
}
v_resetjp_38_:
{
lean_object* v___x_42_; 
lean_inc(v_fst_37_);
if (v_isShared_40_ == 0)
{
lean_ctor_set(v___x_39_, 1, v_fst_37_);
v___x_42_ = v___x_39_;
goto v_reusejp_41_;
}
else
{
lean_object* v_reuseFailAlloc_43_; 
v_reuseFailAlloc_43_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_43_, 0, v_fst_37_);
lean_ctor_set(v_reuseFailAlloc_43_, 1, v_fst_37_);
v___x_42_ = v_reuseFailAlloc_43_;
goto v_reusejp_41_;
}
v_reusejp_41_:
{
return v___x_42_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchLazy___boxed(lean_object* v_i_46_, lean_object* v_p_47_){
_start:
{
lean_object* v_res_48_; 
v_res_48_ = lp_competition_R24DotBarrier_touchLazy(v_i_46_, v_p_47_);
lean_dec(v_i_46_);
return v_res_48_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchEager(lean_object* v_i_49_, lean_object* v_p_50_){
_start:
{
lean_object* v___x_51_; uint8_t v___x_52_; 
v___x_51_ = lean_unsigned_to_nat(1000000007u);
v___x_52_ = lean_nat_dec_eq(v_i_49_, v___x_51_);
if (v___x_52_ == 0)
{
return v_p_50_;
}
else
{
lean_object* v_fst_53_; lean_object* v___x_55_; uint8_t v_isShared_56_; uint8_t v_isSharedCheck_60_; 
v_fst_53_ = lean_ctor_get(v_p_50_, 0);
v_isSharedCheck_60_ = !lean_is_exclusive(v_p_50_);
if (v_isSharedCheck_60_ == 0)
{
lean_object* v_unused_61_; 
v_unused_61_ = lean_ctor_get(v_p_50_, 1);
lean_dec(v_unused_61_);
v___x_55_ = v_p_50_;
v_isShared_56_ = v_isSharedCheck_60_;
goto v_resetjp_54_;
}
else
{
lean_inc(v_fst_53_);
lean_dec(v_p_50_);
v___x_55_ = lean_box(0);
v_isShared_56_ = v_isSharedCheck_60_;
goto v_resetjp_54_;
}
v_resetjp_54_:
{
lean_object* v___x_58_; 
lean_inc(v_fst_53_);
if (v_isShared_56_ == 0)
{
lean_ctor_set(v___x_55_, 1, v_fst_53_);
v___x_58_ = v___x_55_;
goto v_reusejp_57_;
}
else
{
lean_object* v_reuseFailAlloc_59_; 
v_reuseFailAlloc_59_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_59_, 0, v_fst_53_);
lean_ctor_set(v_reuseFailAlloc_59_, 1, v_fst_53_);
v___x_58_ = v_reuseFailAlloc_59_;
goto v_reusejp_57_;
}
v_reusejp_57_:
{
return v___x_58_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBarrier_touchEager___boxed(lean_object* v_i_62_, lean_object* v_p_63_){
_start:
{
lean_object* v_res_64_; 
v_res_64_ = lp_competition_R24DotBarrier_touchEager(v_i_62_, v_p_63_);
lean_dec(v_i_62_);
return v_res_64_;
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
