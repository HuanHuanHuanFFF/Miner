// Lean compiler output
// Module: Submission
// Imports: public import Init public meta import Init public import ContractTensor
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
lean_object* l_BitVec_ofNat(lean_object*, lean_object*);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint64_t lean_uint64_sub(uint64_t, uint64_t);
uint8_t lean_uint64_dec_lt(uint64_t, uint64_t);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint64_t lean_uint64_shift_left(uint64_t, uint64_t);
uint64_t lean_uint64_land(uint64_t, uint64_t);
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
uint64_t lean_uint32_to_uint64(uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
lean_object* l_Id_instMonad___lam__2___boxed(lean_object*, lean_object*);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(lean_object*, lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
lean_object* lean_array_get_size(lean_object*);
lean_object* l_Id_instMonad___lam__6(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__5___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__4___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__3(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__0(lean_object*, lean_object*, lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(lean_object*, lean_object*, lean_object*);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
size_t lean_usize_of_nat(lean_object*);
lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___redArg(lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
lean_object* lean_nat_mul(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
lean_object* lp_competition_Competition_bmmDecodeC(lean_object*, lean_object*, lean_object*);
lean_object* l_Fin_foldl_loop___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Array_ofFn___redArg(lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_sx(uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sx___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_sr(uint64_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sr___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_fastLog2(uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_fastLog2___boxed(lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_rse(uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_rse___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_rseAny(uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_rseAny___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_mkW(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_mkW___boxed(lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_TunedAdd_fracW___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static uint32_t lp_competition_Submission_TunedAdd_fracW___closed__0;
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_fracW(uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_fracW___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_roundP(uint8_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_roundP___boxed(lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_Submission_TunedAdd_core___boxed__const__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*0 + 8, .m_other = 0, .m_tag = 0}, .m_objs = {LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
LEAN_EXPORT const lean_object* lp_competition_Submission_TunedAdd_core___boxed__const__1 = (const lean_object*)&lp_competition_Submission_TunedAdd_core___boxed__const__1_value;
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_core(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_core___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_sp1(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sp1___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_special(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_special___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_ofBits(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_ofBits___boxed(lean_object*);
static const lean_ctor_object lp_competition_Submission_TunedAdd_add___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 8, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(8) << 1) | 1)),((lean_object*)(((size_t)(23) << 1) | 1)),((lean_object*)(((size_t)(127) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
static const lean_object* lp_competition_Submission_TunedAdd_add___closed__0 = (const lean_object*)&lp_competition_Submission_TunedAdd_add___closed__0_value;
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_add(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_add___boxed(lean_object*, lean_object*);
LEAN_EXPORT const lean_object* lp_competition_Submission_TunedAdd_Fmt = (const lean_object*)&lp_competition_Submission_TunedAdd_add___closed__0_value;
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_Plan;
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec___boxed(lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sx(uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sx___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sr(uint64_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sr___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_fastLog2(uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fastLog2___boxed(lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rse(uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rse___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rseAny(uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rseAny___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mkW(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mkW___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_fracW(uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fracW___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_roundP(uint8_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_roundP___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_core(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_core___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_sm1(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sm1___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_special(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_special___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_ofBits(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_ofBits___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mul___boxed(lean_object*, lean_object*);
LEAN_EXPORT const lean_object* lp_competition_Submission_FastMul_Fmt = (const lean_object*)&lp_competition_Submission_TunedAdd_add___closed__0_value;
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_Plan;
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___lam__0___boxed__const__1;
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___lam__0___boxed__const__2;
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___lam__0(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___lam__0___boxed(lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_sum___redArg___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_sum___redArg___closed__0;
static lean_once_cell_t lp_competition_Submission_sum___redArg___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static uint32_t lp_competition_Submission_sum___redArg___closed__1;
static const lean_closure_object lp_competition_Submission_sum___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__0, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_sum___redArg___closed__2 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__2_value;
static const lean_closure_object lp_competition_Submission_sum___redArg___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__1___boxed, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_sum___redArg___closed__3 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__3_value;
static const lean_closure_object lp_competition_Submission_sum___redArg___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__2___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_sum___redArg___closed__4 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__4_value;
static const lean_closure_object lp_competition_Submission_sum___redArg___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__3, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_sum___redArg___closed__5 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__5_value;
static const lean_closure_object lp_competition_Submission_sum___redArg___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__4___boxed, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_sum___redArg___closed__6 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__6_value;
static const lean_closure_object lp_competition_Submission_sum___redArg___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__5___boxed, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_sum___redArg___closed__7 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__7_value;
static const lean_closure_object lp_competition_Submission_sum___redArg___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__6, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_sum___redArg___closed__8 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__8_value;
static const lean_ctor_object lp_competition_Submission_sum___redArg___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_sum___redArg___closed__2_value),((lean_object*)&lp_competition_Submission_sum___redArg___closed__3_value)}};
static const lean_object* lp_competition_Submission_sum___redArg___closed__9 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__9_value;
static const lean_ctor_object lp_competition_Submission_sum___redArg___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*5 + 0, .m_other = 5, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_sum___redArg___closed__9_value),((lean_object*)&lp_competition_Submission_sum___redArg___closed__4_value),((lean_object*)&lp_competition_Submission_sum___redArg___closed__5_value),((lean_object*)&lp_competition_Submission_sum___redArg___closed__6_value),((lean_object*)&lp_competition_Submission_sum___redArg___closed__7_value)}};
static const lean_object* lp_competition_Submission_sum___redArg___closed__10 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__10_value;
static const lean_ctor_object lp_competition_Submission_sum___redArg___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_sum___redArg___closed__10_value),((lean_object*)&lp_competition_Submission_sum___redArg___closed__8_value)}};
static const lean_object* lp_competition_Submission_sum___redArg___closed__11 = (const lean_object*)&lp_competition_Submission_sum___redArg___closed__11_value;
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___boxed__const__1;
LEAN_EXPORT uint32_t lp_competition_Submission_sum___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_bmm___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_sx(uint64_t v_k_1_, uint64_t v_x_2_){
_start:
{
uint64_t v___x_3_; uint64_t v___x_4_; uint8_t v___x_5_; 
v___x_3_ = lean_uint64_shift_right(v_x_2_, v_k_1_);
v___x_4_ = 0ULL;
v___x_5_ = lean_uint64_dec_eq(v___x_3_, v___x_4_);
if (v___x_5_ == 0)
{
return v___x_3_;
}
else
{
return v_x_2_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sx___boxed(lean_object* v_k_6_, lean_object* v_x_7_){
_start:
{
uint64_t v_k_boxed_8_; uint64_t v_x_boxed_9_; uint64_t v_res_10_; lean_object* v_r_11_; 
v_k_boxed_8_ = lean_unbox_uint64(v_k_6_);
lean_dec_ref(v_k_6_);
v_x_boxed_9_ = lean_unbox_uint64(v_x_7_);
lean_dec_ref(v_x_7_);
v_res_10_ = lp_competition_Submission_TunedAdd_sx(v_k_boxed_8_, v_x_boxed_9_);
v_r_11_ = lean_box_uint64(v_res_10_);
return v_r_11_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_sr(uint64_t v_k_12_, uint64_t v_x_13_, uint64_t v_r_14_){
_start:
{
uint64_t v___x_15_; uint64_t v___x_16_; uint8_t v___x_17_; 
v___x_15_ = lean_uint64_shift_right(v_x_13_, v_k_12_);
v___x_16_ = 0ULL;
v___x_17_ = lean_uint64_dec_eq(v___x_15_, v___x_16_);
if (v___x_17_ == 0)
{
uint64_t v___x_18_; 
v___x_18_ = lean_uint64_add(v_r_14_, v_k_12_);
return v___x_18_;
}
else
{
return v_r_14_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sr___boxed(lean_object* v_k_19_, lean_object* v_x_20_, lean_object* v_r_21_){
_start:
{
uint64_t v_k_boxed_22_; uint64_t v_x_boxed_23_; uint64_t v_r_boxed_24_; uint64_t v_res_25_; lean_object* v_r_26_; 
v_k_boxed_22_ = lean_unbox_uint64(v_k_19_);
lean_dec_ref(v_k_19_);
v_x_boxed_23_ = lean_unbox_uint64(v_x_20_);
lean_dec_ref(v_x_20_);
v_r_boxed_24_ = lean_unbox_uint64(v_r_21_);
lean_dec_ref(v_r_21_);
v_res_25_ = lp_competition_Submission_TunedAdd_sr(v_k_boxed_22_, v_x_boxed_23_, v_r_boxed_24_);
v_r_26_ = lean_box_uint64(v_res_25_);
return v_r_26_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_fastLog2(uint64_t v_x0_27_){
_start:
{
uint64_t v___y_29_; uint64_t v___y_30_; uint64_t v___y_37_; uint64_t v___y_38_; uint64_t v___y_39_; uint64_t v___y_40_; uint64_t v___y_46_; uint64_t v___y_47_; uint64_t v___y_53_; uint64_t v___y_54_; uint64_t v___y_55_; uint64_t v___y_56_; uint64_t v___y_62_; uint64_t v___y_63_; uint64_t v___y_69_; uint64_t v___y_70_; uint64_t v___y_71_; uint64_t v___y_72_; uint64_t v___y_78_; uint64_t v___y_79_; uint64_t v___y_85_; uint64_t v___y_86_; uint64_t v___y_87_; uint64_t v___y_88_; uint64_t v___y_94_; uint64_t v___y_95_; uint64_t v___x_100_; uint64_t v___y_102_; uint64_t v___x_106_; uint64_t v___x_107_; uint8_t v___x_108_; 
v___x_100_ = 32ULL;
v___x_106_ = lean_uint64_shift_right(v_x0_27_, v___x_100_);
v___x_107_ = 0ULL;
v___x_108_ = lean_uint64_dec_eq(v___x_106_, v___x_107_);
if (v___x_108_ == 0)
{
v___y_102_ = v___x_106_;
goto v___jp_101_;
}
else
{
v___y_102_ = v_x0_27_;
goto v___jp_101_;
}
v___jp_28_:
{
uint64_t v___x_31_; uint64_t v___x_32_; uint64_t v___x_33_; uint8_t v___x_34_; 
v___x_31_ = 1ULL;
v___x_32_ = lean_uint64_shift_right(v___y_29_, v___x_31_);
v___x_33_ = 0ULL;
v___x_34_ = lean_uint64_dec_eq(v___x_32_, v___x_33_);
if (v___x_34_ == 0)
{
uint64_t v___x_35_; 
v___x_35_ = lean_uint64_add(v___y_30_, v___x_31_);
return v___x_35_;
}
else
{
return v___y_30_;
}
}
v___jp_36_:
{
uint64_t v___x_41_; uint64_t v___x_42_; uint8_t v___x_43_; 
v___x_41_ = lean_uint64_shift_right(v___y_38_, v___y_39_);
v___x_42_ = 0ULL;
v___x_43_ = lean_uint64_dec_eq(v___x_41_, v___x_42_);
if (v___x_43_ == 0)
{
uint64_t v___x_44_; 
v___x_44_ = lean_uint64_add(v___y_37_, v___y_39_);
v___y_29_ = v___y_40_;
v___y_30_ = v___x_44_;
goto v___jp_28_;
}
else
{
v___y_29_ = v___y_40_;
v___y_30_ = v___y_37_;
goto v___jp_28_;
}
}
v___jp_45_:
{
uint64_t v___x_48_; uint64_t v___x_49_; uint64_t v___x_50_; uint8_t v___x_51_; 
v___x_48_ = 2ULL;
v___x_49_ = lean_uint64_shift_right(v___y_46_, v___x_48_);
v___x_50_ = 0ULL;
v___x_51_ = lean_uint64_dec_eq(v___x_49_, v___x_50_);
if (v___x_51_ == 0)
{
v___y_37_ = v___y_47_;
v___y_38_ = v___y_46_;
v___y_39_ = v___x_48_;
v___y_40_ = v___x_49_;
goto v___jp_36_;
}
else
{
v___y_37_ = v___y_47_;
v___y_38_ = v___y_46_;
v___y_39_ = v___x_48_;
v___y_40_ = v___y_46_;
goto v___jp_36_;
}
}
v___jp_52_:
{
uint64_t v___x_57_; uint64_t v___x_58_; uint8_t v___x_59_; 
v___x_57_ = lean_uint64_shift_right(v___y_53_, v___y_55_);
v___x_58_ = 0ULL;
v___x_59_ = lean_uint64_dec_eq(v___x_57_, v___x_58_);
if (v___x_59_ == 0)
{
uint64_t v___x_60_; 
v___x_60_ = lean_uint64_add(v___y_54_, v___y_55_);
v___y_46_ = v___y_56_;
v___y_47_ = v___x_60_;
goto v___jp_45_;
}
else
{
v___y_46_ = v___y_56_;
v___y_47_ = v___y_54_;
goto v___jp_45_;
}
}
v___jp_61_:
{
uint64_t v___x_64_; uint64_t v___x_65_; uint64_t v___x_66_; uint8_t v___x_67_; 
v___x_64_ = 4ULL;
v___x_65_ = lean_uint64_shift_right(v___y_62_, v___x_64_);
v___x_66_ = 0ULL;
v___x_67_ = lean_uint64_dec_eq(v___x_65_, v___x_66_);
if (v___x_67_ == 0)
{
v___y_53_ = v___y_62_;
v___y_54_ = v___y_63_;
v___y_55_ = v___x_64_;
v___y_56_ = v___x_65_;
goto v___jp_52_;
}
else
{
v___y_53_ = v___y_62_;
v___y_54_ = v___y_63_;
v___y_55_ = v___x_64_;
v___y_56_ = v___y_62_;
goto v___jp_52_;
}
}
v___jp_68_:
{
uint64_t v___x_73_; uint64_t v___x_74_; uint8_t v___x_75_; 
v___x_73_ = lean_uint64_shift_right(v___y_71_, v___y_69_);
v___x_74_ = 0ULL;
v___x_75_ = lean_uint64_dec_eq(v___x_73_, v___x_74_);
if (v___x_75_ == 0)
{
uint64_t v___x_76_; 
v___x_76_ = lean_uint64_add(v___y_70_, v___y_69_);
v___y_62_ = v___y_72_;
v___y_63_ = v___x_76_;
goto v___jp_61_;
}
else
{
v___y_62_ = v___y_72_;
v___y_63_ = v___y_70_;
goto v___jp_61_;
}
}
v___jp_77_:
{
uint64_t v___x_80_; uint64_t v___x_81_; uint64_t v___x_82_; uint8_t v___x_83_; 
v___x_80_ = 8ULL;
v___x_81_ = lean_uint64_shift_right(v___y_78_, v___x_80_);
v___x_82_ = 0ULL;
v___x_83_ = lean_uint64_dec_eq(v___x_81_, v___x_82_);
if (v___x_83_ == 0)
{
v___y_69_ = v___x_80_;
v___y_70_ = v___y_79_;
v___y_71_ = v___y_78_;
v___y_72_ = v___x_81_;
goto v___jp_68_;
}
else
{
v___y_69_ = v___x_80_;
v___y_70_ = v___y_79_;
v___y_71_ = v___y_78_;
v___y_72_ = v___y_78_;
goto v___jp_68_;
}
}
v___jp_84_:
{
uint64_t v___x_89_; uint64_t v___x_90_; uint8_t v___x_91_; 
v___x_89_ = lean_uint64_shift_right(v___y_86_, v___y_85_);
v___x_90_ = 0ULL;
v___x_91_ = lean_uint64_dec_eq(v___x_89_, v___x_90_);
if (v___x_91_ == 0)
{
uint64_t v___x_92_; 
v___x_92_ = lean_uint64_add(v___y_87_, v___y_85_);
v___y_78_ = v___y_88_;
v___y_79_ = v___x_92_;
goto v___jp_77_;
}
else
{
v___y_78_ = v___y_88_;
v___y_79_ = v___y_87_;
goto v___jp_77_;
}
}
v___jp_93_:
{
uint64_t v___x_96_; uint64_t v___x_97_; uint64_t v___x_98_; uint8_t v___x_99_; 
v___x_96_ = 16ULL;
v___x_97_ = lean_uint64_shift_right(v___y_94_, v___x_96_);
v___x_98_ = 0ULL;
v___x_99_ = lean_uint64_dec_eq(v___x_97_, v___x_98_);
if (v___x_99_ == 0)
{
v___y_85_ = v___x_96_;
v___y_86_ = v___y_94_;
v___y_87_ = v___y_95_;
v___y_88_ = v___x_97_;
goto v___jp_84_;
}
else
{
v___y_85_ = v___x_96_;
v___y_86_ = v___y_94_;
v___y_87_ = v___y_95_;
v___y_88_ = v___y_94_;
goto v___jp_84_;
}
}
v___jp_101_:
{
uint64_t v___x_103_; uint64_t v___x_104_; uint8_t v___x_105_; 
v___x_103_ = lean_uint64_shift_right(v_x0_27_, v___x_100_);
v___x_104_ = 0ULL;
v___x_105_ = lean_uint64_dec_eq(v___x_103_, v___x_104_);
if (v___x_105_ == 0)
{
v___y_94_ = v___y_102_;
v___y_95_ = v___x_100_;
goto v___jp_93_;
}
else
{
v___y_94_ = v___y_102_;
v___y_95_ = v___x_104_;
goto v___jp_93_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_fastLog2___boxed(lean_object* v_x0_109_){
_start:
{
uint64_t v_x0_boxed_110_; uint64_t v_res_111_; lean_object* v_r_112_; 
v_x0_boxed_110_ = lean_unbox_uint64(v_x0_109_);
lean_dec_ref(v_x0_109_);
v_res_111_ = lp_competition_Submission_TunedAdd_fastLog2(v_x0_boxed_110_);
v_r_112_ = lean_box_uint64(v_res_111_);
return v_r_112_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_rse(uint64_t v_value_113_, uint64_t v_shift_114_){
_start:
{
uint64_t v_quotient_115_; uint64_t v___x_116_; uint64_t v___x_117_; uint64_t v___x_118_; uint64_t v_remainder_119_; uint64_t v___x_120_; uint64_t v_half_121_; uint8_t v___x_122_; 
v_quotient_115_ = lean_uint64_shift_right(v_value_113_, v_shift_114_);
v___x_116_ = 1ULL;
v___x_117_ = lean_uint64_shift_left(v___x_116_, v_shift_114_);
v___x_118_ = lean_uint64_sub(v___x_117_, v___x_116_);
v_remainder_119_ = lean_uint64_land(v_value_113_, v___x_118_);
v___x_120_ = lean_uint64_sub(v_shift_114_, v___x_116_);
v_half_121_ = lean_uint64_shift_left(v___x_116_, v___x_120_);
v___x_122_ = lean_uint64_dec_lt(v_remainder_119_, v_half_121_);
if (v___x_122_ == 0)
{
uint8_t v___x_123_; 
v___x_123_ = lean_uint64_dec_lt(v_half_121_, v_remainder_119_);
if (v___x_123_ == 0)
{
uint64_t v___x_124_; uint64_t v___x_125_; uint8_t v___x_126_; 
v___x_124_ = lean_uint64_land(v_quotient_115_, v___x_116_);
v___x_125_ = 0ULL;
v___x_126_ = lean_uint64_dec_eq(v___x_124_, v___x_125_);
if (v___x_126_ == 0)
{
uint64_t v___x_127_; 
v___x_127_ = lean_uint64_add(v_quotient_115_, v___x_116_);
return v___x_127_;
}
else
{
return v_quotient_115_;
}
}
else
{
uint64_t v___x_128_; 
v___x_128_ = lean_uint64_add(v_quotient_115_, v___x_116_);
return v___x_128_;
}
}
else
{
return v_quotient_115_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_rse___boxed(lean_object* v_value_129_, lean_object* v_shift_130_){
_start:
{
uint64_t v_value_boxed_131_; uint64_t v_shift_boxed_132_; uint64_t v_res_133_; lean_object* v_r_134_; 
v_value_boxed_131_ = lean_unbox_uint64(v_value_129_);
lean_dec_ref(v_value_129_);
v_shift_boxed_132_ = lean_unbox_uint64(v_shift_130_);
lean_dec_ref(v_shift_130_);
v_res_133_ = lp_competition_Submission_TunedAdd_rse(v_value_boxed_131_, v_shift_boxed_132_);
v_r_134_ = lean_box_uint64(v_res_133_);
return v_r_134_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_rseAny(uint64_t v_value_135_, uint64_t v_shift_136_){
_start:
{
uint64_t v___x_137_; uint8_t v___x_138_; 
v___x_137_ = 0ULL;
v___x_138_ = lean_uint64_dec_eq(v_shift_136_, v___x_137_);
if (v___x_138_ == 0)
{
uint64_t v___x_139_; uint8_t v___x_140_; 
v___x_139_ = 64ULL;
v___x_140_ = lean_uint64_dec_lt(v_shift_136_, v___x_139_);
if (v___x_140_ == 0)
{
uint8_t v___x_141_; 
v___x_141_ = lean_uint64_dec_eq(v_shift_136_, v___x_139_);
if (v___x_141_ == 0)
{
return v___x_137_;
}
else
{
uint64_t v___x_142_; uint8_t v___x_143_; 
v___x_142_ = 9223372036854775808ULL;
v___x_143_ = lean_uint64_dec_lt(v___x_142_, v_value_135_);
if (v___x_143_ == 0)
{
return v___x_137_;
}
else
{
uint64_t v___x_144_; 
v___x_144_ = 1ULL;
return v___x_144_;
}
}
}
else
{
uint64_t v_quotient_145_; uint64_t v___x_146_; uint64_t v___x_147_; uint64_t v___x_148_; uint64_t v_remainder_149_; uint64_t v___x_150_; uint64_t v_half_151_; uint8_t v___x_152_; 
v_quotient_145_ = lean_uint64_shift_right(v_value_135_, v_shift_136_);
v___x_146_ = 1ULL;
v___x_147_ = lean_uint64_shift_left(v___x_146_, v_shift_136_);
v___x_148_ = lean_uint64_sub(v___x_147_, v___x_146_);
v_remainder_149_ = lean_uint64_land(v_value_135_, v___x_148_);
v___x_150_ = lean_uint64_sub(v_shift_136_, v___x_146_);
v_half_151_ = lean_uint64_shift_left(v___x_146_, v___x_150_);
v___x_152_ = lean_uint64_dec_lt(v_remainder_149_, v_half_151_);
if (v___x_152_ == 0)
{
uint8_t v___x_153_; 
v___x_153_ = lean_uint64_dec_lt(v_half_151_, v_remainder_149_);
if (v___x_153_ == 0)
{
uint64_t v___x_154_; uint8_t v___x_155_; 
v___x_154_ = lean_uint64_land(v_quotient_145_, v___x_146_);
v___x_155_ = lean_uint64_dec_eq(v___x_154_, v___x_137_);
if (v___x_155_ == 0)
{
uint64_t v___x_156_; 
v___x_156_ = lean_uint64_add(v_quotient_145_, v___x_146_);
return v___x_156_;
}
else
{
return v_quotient_145_;
}
}
else
{
uint64_t v___x_157_; 
v___x_157_ = lean_uint64_add(v_quotient_145_, v___x_146_);
return v___x_157_;
}
}
else
{
return v_quotient_145_;
}
}
}
else
{
return v_value_135_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_rseAny___boxed(lean_object* v_value_158_, lean_object* v_shift_159_){
_start:
{
uint64_t v_value_boxed_160_; uint64_t v_shift_boxed_161_; uint64_t v_res_162_; lean_object* v_r_163_; 
v_value_boxed_160_ = lean_unbox_uint64(v_value_158_);
lean_dec_ref(v_value_158_);
v_shift_boxed_161_ = lean_unbox_uint64(v_shift_159_);
lean_dec_ref(v_shift_159_);
v_res_162_ = lp_competition_Submission_TunedAdd_rseAny(v_value_boxed_160_, v_shift_boxed_161_);
v_r_163_ = lean_box_uint64(v_res_162_);
return v_r_163_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_mkW(uint8_t v_sign_164_, uint32_t v_e_165_, uint32_t v_f_166_){
_start:
{
uint32_t v___y_168_; 
if (v_sign_164_ == 0)
{
uint32_t v___x_177_; 
v___x_177_ = 0;
v___y_168_ = v___x_177_;
goto v___jp_167_;
}
else
{
uint32_t v___x_178_; 
v___x_178_ = 2147483648;
v___y_168_ = v___x_178_;
goto v___jp_167_;
}
v___jp_167_:
{
uint32_t v___x_169_; uint32_t v___x_170_; uint32_t v___x_171_; uint32_t v___x_172_; uint32_t v___x_173_; uint32_t v___x_174_; uint32_t v___x_175_; uint32_t v___x_176_; 
v___x_169_ = 255;
v___x_170_ = lean_uint32_land(v_e_165_, v___x_169_);
v___x_171_ = 23;
v___x_172_ = lean_uint32_shift_left(v___x_170_, v___x_171_);
v___x_173_ = lean_uint32_lor(v___y_168_, v___x_172_);
v___x_174_ = 8388607;
v___x_175_ = lean_uint32_land(v_f_166_, v___x_174_);
v___x_176_ = lean_uint32_lor(v___x_173_, v___x_175_);
return v___x_176_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_mkW___boxed(lean_object* v_sign_179_, lean_object* v_e_180_, lean_object* v_f_181_){
_start:
{
uint8_t v_sign_boxed_182_; uint32_t v_e_boxed_183_; uint32_t v_f_boxed_184_; uint32_t v_res_185_; lean_object* v_r_186_; 
v_sign_boxed_182_ = lean_unbox(v_sign_179_);
v_e_boxed_183_ = lean_unbox_uint32(v_e_180_);
lean_dec(v_e_180_);
v_f_boxed_184_ = lean_unbox_uint32(v_f_181_);
lean_dec(v_f_181_);
v_res_185_ = lp_competition_Submission_TunedAdd_mkW(v_sign_boxed_182_, v_e_boxed_183_, v_f_boxed_184_);
v_r_186_ = lean_box_uint32(v_res_185_);
return v_r_186_;
}
}
static uint32_t _init_lp_competition_Submission_TunedAdd_fracW___closed__0(void){
_start:
{
uint64_t v___x_187_; uint32_t v___x_188_; 
v___x_187_ = 0ULL;
v___x_188_ = lean_uint64_to_uint32(v___x_187_);
return v___x_188_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_fracW(uint64_t v_n_189_){
_start:
{
uint64_t v___x_190_; uint8_t v___x_191_; 
v___x_190_ = 8388608ULL;
v___x_191_ = lean_uint64_dec_lt(v_n_189_, v___x_190_);
if (v___x_191_ == 0)
{
uint64_t v___x_192_; uint32_t v___x_193_; 
v___x_192_ = lean_uint64_sub(v_n_189_, v___x_190_);
v___x_193_ = lean_uint64_to_uint32(v___x_192_);
return v___x_193_;
}
else
{
uint32_t v___x_194_; 
v___x_194_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
return v___x_194_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_fracW___boxed(lean_object* v_n_195_){
_start:
{
uint64_t v_n_boxed_196_; uint32_t v_res_197_; lean_object* v_r_198_; 
v_n_boxed_196_ = lean_unbox_uint64(v_n_195_);
lean_dec_ref(v_n_195_);
v_res_197_ = lp_competition_Submission_TunedAdd_fracW(v_n_boxed_196_);
v_r_198_ = lean_box_uint32(v_res_197_);
return v_r_198_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_roundP(uint8_t v_sign_199_, uint64_t v_product_200_, uint64_t v_scale_201_){
_start:
{
uint32_t v___y_203_; uint32_t v___y_207_; uint32_t v___y_208_; uint32_t v___y_213_; uint32_t v___y_214_; uint32_t v___y_215_; uint32_t v___y_225_; uint32_t v___y_226_; uint64_t v___x_229_; uint64_t v___y_231_; uint64_t v___y_243_; uint64_t v___y_244_; uint64_t v___y_254_; uint8_t v___y_255_; uint64_t v___y_256_; uint64_t v___y_263_; uint64_t v___y_264_; uint64_t v___y_270_; uint64_t v___y_325_; uint64_t v___y_326_; uint64_t v___y_332_; uint64_t v___y_333_; uint64_t v___y_334_; uint64_t v___y_335_; uint64_t v___y_340_; uint64_t v___y_341_; uint64_t v___y_346_; uint64_t v___y_347_; uint64_t v___y_348_; uint64_t v___y_349_; uint64_t v___y_354_; uint64_t v___y_355_; uint64_t v___y_360_; uint64_t v___y_361_; uint64_t v___y_362_; uint64_t v___y_363_; uint64_t v___y_368_; uint64_t v___y_369_; uint64_t v___y_374_; uint64_t v___y_375_; uint64_t v___y_376_; uint64_t v___y_377_; uint64_t v___y_382_; uint64_t v___y_383_; uint8_t v___x_387_; 
v___x_229_ = 0ULL;
v___x_387_ = lean_uint64_dec_eq(v_product_200_, v___x_229_);
if (v___x_387_ == 0)
{
uint64_t v___x_388_; uint64_t v___y_390_; uint64_t v___x_393_; uint8_t v___x_394_; 
v___x_388_ = 32ULL;
v___x_393_ = lean_uint64_shift_right(v_product_200_, v___x_388_);
v___x_394_ = lean_uint64_dec_eq(v___x_393_, v___x_229_);
if (v___x_394_ == 0)
{
v___y_390_ = v___x_393_;
goto v___jp_389_;
}
else
{
v___y_390_ = v_product_200_;
goto v___jp_389_;
}
v___jp_389_:
{
uint64_t v___x_391_; uint8_t v___x_392_; 
v___x_391_ = lean_uint64_shift_right(v_product_200_, v___x_388_);
v___x_392_ = lean_uint64_dec_eq(v___x_391_, v___x_229_);
if (v___x_392_ == 0)
{
v___y_382_ = v___y_390_;
v___y_383_ = v___x_388_;
goto v___jp_381_;
}
else
{
v___y_382_ = v___y_390_;
v___y_383_ = v___x_229_;
goto v___jp_381_;
}
}
}
else
{
if (v_sign_199_ == 0)
{
uint32_t v___x_395_; 
v___x_395_ = 0;
return v___x_395_;
}
else
{
uint32_t v___x_396_; 
v___x_396_ = 2147483648;
return v___x_396_;
}
}
v___jp_202_:
{
uint32_t v___x_204_; uint32_t v___x_205_; 
v___x_204_ = 8388608;
v___x_205_ = lean_uint32_lor(v___y_203_, v___x_204_);
return v___x_205_;
}
v___jp_206_:
{
uint32_t v___x_209_; uint32_t v___x_210_; uint32_t v___x_211_; 
v___x_209_ = 8388607;
v___x_210_ = lean_uint32_land(v___y_207_, v___x_209_);
v___x_211_ = lean_uint32_lor(v___y_208_, v___x_210_);
return v___x_211_;
}
v___jp_212_:
{
uint32_t v___x_216_; uint32_t v___x_217_; uint32_t v___x_218_; uint32_t v___x_219_; uint32_t v___x_220_; uint32_t v___x_221_; uint32_t v___x_222_; uint32_t v___x_223_; 
v___x_216_ = 255;
v___x_217_ = lean_uint32_land(v___y_213_, v___x_216_);
v___x_218_ = 23;
v___x_219_ = lean_uint32_shift_left(v___x_217_, v___x_218_);
v___x_220_ = lean_uint32_lor(v___y_215_, v___x_219_);
v___x_221_ = 8388607;
v___x_222_ = lean_uint32_land(v___y_214_, v___x_221_);
v___x_223_ = lean_uint32_lor(v___x_220_, v___x_222_);
return v___x_223_;
}
v___jp_224_:
{
if (v_sign_199_ == 0)
{
uint32_t v___x_227_; 
v___x_227_ = 0;
v___y_213_ = v___y_225_;
v___y_214_ = v___y_226_;
v___y_215_ = v___x_227_;
goto v___jp_212_;
}
else
{
uint32_t v___x_228_; 
v___x_228_ = 2147483648;
v___y_213_ = v___y_225_;
v___y_214_ = v___y_226_;
v___y_215_ = v___x_228_;
goto v___jp_212_;
}
}
v___jp_230_:
{
uint8_t v___x_232_; 
v___x_232_ = lean_uint64_dec_eq(v___y_231_, v___x_229_);
if (v___x_232_ == 0)
{
uint64_t v___x_233_; uint8_t v___x_234_; 
v___x_233_ = 8388608ULL;
v___x_234_ = lean_uint64_dec_eq(v___y_231_, v___x_233_);
if (v___x_234_ == 0)
{
uint32_t v___x_235_; 
v___x_235_ = lean_uint64_to_uint32(v___y_231_);
if (v_sign_199_ == 0)
{
uint32_t v___x_236_; 
v___x_236_ = 0;
v___y_207_ = v___x_235_;
v___y_208_ = v___x_236_;
goto v___jp_206_;
}
else
{
uint32_t v___x_237_; 
v___x_237_ = 2147483648;
v___y_207_ = v___x_235_;
v___y_208_ = v___x_237_;
goto v___jp_206_;
}
}
else
{
if (v_sign_199_ == 0)
{
uint32_t v___x_238_; 
v___x_238_ = 0;
v___y_203_ = v___x_238_;
goto v___jp_202_;
}
else
{
uint32_t v___x_239_; 
v___x_239_ = 2147483648;
v___y_203_ = v___x_239_;
goto v___jp_202_;
}
}
}
else
{
if (v_sign_199_ == 0)
{
uint32_t v___x_240_; 
v___x_240_ = 0;
return v___x_240_;
}
else
{
uint32_t v___x_241_; 
v___x_241_ = 2147483648;
return v___x_241_;
}
}
}
v___jp_242_:
{
uint64_t v___x_245_; uint64_t v_encodedExponent_246_; uint32_t v___x_247_; uint64_t v___x_248_; uint8_t v___x_249_; 
v___x_245_ = 171ULL;
v_encodedExponent_246_ = lean_uint64_sub(v___y_243_, v___x_245_);
v___x_247_ = lean_uint64_to_uint32(v_encodedExponent_246_);
v___x_248_ = 8388608ULL;
v___x_249_ = lean_uint64_dec_lt(v___y_244_, v___x_248_);
if (v___x_249_ == 0)
{
uint64_t v___x_250_; uint32_t v___x_251_; 
v___x_250_ = lean_uint64_sub(v___y_244_, v___x_248_);
v___x_251_ = lean_uint64_to_uint32(v___x_250_);
v___y_225_ = v___x_247_;
v___y_226_ = v___x_251_;
goto v___jp_224_;
}
else
{
uint32_t v___x_252_; 
v___x_252_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_225_ = v___x_247_;
v___y_226_ = v___x_252_;
goto v___jp_224_;
}
}
v___jp_253_:
{
uint64_t v___x_257_; uint8_t v___x_258_; 
v___x_257_ = 425ULL;
v___x_258_ = lean_uint64_dec_lt(v___x_257_, v___y_256_);
if (v___x_258_ == 0)
{
if (v___y_255_ == 0)
{
v___y_243_ = v___y_256_;
v___y_244_ = v___y_254_;
goto v___jp_242_;
}
else
{
uint64_t v___x_259_; 
v___x_259_ = 8388608ULL;
v___y_243_ = v___y_256_;
v___y_244_ = v___x_259_;
goto v___jp_242_;
}
}
else
{
if (v_sign_199_ == 0)
{
uint32_t v___x_260_; 
v___x_260_ = 2139095040;
return v___x_260_;
}
else
{
uint32_t v___x_261_; 
v___x_261_ = 4286578688;
return v___x_261_;
}
}
}
v___jp_262_:
{
uint64_t v___x_265_; uint8_t v_carry_266_; 
v___x_265_ = 16777216ULL;
v_carry_266_ = lean_uint64_dec_eq(v___y_264_, v___x_265_);
if (v_carry_266_ == 0)
{
v___y_254_ = v___y_264_;
v___y_255_ = v_carry_266_;
v___y_256_ = v___y_263_;
goto v___jp_253_;
}
else
{
uint64_t v___x_267_; uint64_t v___x_268_; 
v___x_267_ = 1ULL;
v___x_268_ = lean_uint64_add(v___y_263_, v___x_267_);
v___y_254_ = v___y_264_;
v___y_255_ = v_carry_266_;
v___y_256_ = v___x_268_;
goto v___jp_253_;
}
}
v___jp_269_:
{
uint64_t v_position_271_; uint64_t v___x_272_; uint8_t v___x_273_; 
v_position_271_ = lean_uint64_add(v___y_270_, v_scale_201_);
v___x_272_ = 172ULL;
v___x_273_ = lean_uint64_dec_lt(v_position_271_, v___x_272_);
if (v___x_273_ == 0)
{
uint64_t v___x_274_; uint8_t v___x_275_; 
v___x_274_ = 23ULL;
v___x_275_ = lean_uint64_dec_lt(v___y_270_, v___x_274_);
if (v___x_275_ == 0)
{
uint64_t v___x_276_; uint8_t v___x_277_; 
v___x_276_ = lean_uint64_sub(v___y_270_, v___x_274_);
v___x_277_ = lean_uint64_dec_eq(v___x_276_, v___x_229_);
if (v___x_277_ == 0)
{
uint64_t v___x_278_; uint8_t v___x_279_; 
v___x_278_ = 64ULL;
v___x_279_ = lean_uint64_dec_lt(v___x_276_, v___x_278_);
if (v___x_279_ == 0)
{
uint8_t v___x_280_; 
v___x_280_ = lean_uint64_dec_eq(v___x_276_, v___x_278_);
if (v___x_280_ == 0)
{
v___y_263_ = v_position_271_;
v___y_264_ = v___x_229_;
goto v___jp_262_;
}
else
{
uint64_t v___x_281_; uint8_t v___x_282_; 
v___x_281_ = 9223372036854775808ULL;
v___x_282_ = lean_uint64_dec_lt(v___x_281_, v_product_200_);
if (v___x_282_ == 0)
{
v___y_263_ = v_position_271_;
v___y_264_ = v___x_229_;
goto v___jp_262_;
}
else
{
uint64_t v___x_283_; 
v___x_283_ = 1ULL;
v___y_263_ = v_position_271_;
v___y_264_ = v___x_283_;
goto v___jp_262_;
}
}
}
else
{
uint64_t v_quotient_284_; uint64_t v___x_285_; uint64_t v___x_286_; uint64_t v___x_287_; uint64_t v_remainder_288_; uint64_t v___x_289_; uint64_t v_half_290_; uint8_t v___x_291_; 
v_quotient_284_ = lean_uint64_shift_right(v_product_200_, v___x_276_);
v___x_285_ = 1ULL;
v___x_286_ = lean_uint64_shift_left(v___x_285_, v___x_276_);
v___x_287_ = lean_uint64_sub(v___x_286_, v___x_285_);
v_remainder_288_ = lean_uint64_land(v_product_200_, v___x_287_);
v___x_289_ = lean_uint64_sub(v___x_276_, v___x_285_);
v_half_290_ = lean_uint64_shift_left(v___x_285_, v___x_289_);
v___x_291_ = lean_uint64_dec_lt(v_remainder_288_, v_half_290_);
if (v___x_291_ == 0)
{
uint8_t v___x_292_; 
v___x_292_ = lean_uint64_dec_lt(v_half_290_, v_remainder_288_);
if (v___x_292_ == 0)
{
uint64_t v___x_293_; uint8_t v___x_294_; 
v___x_293_ = lean_uint64_land(v_quotient_284_, v___x_285_);
v___x_294_ = lean_uint64_dec_eq(v___x_293_, v___x_229_);
if (v___x_294_ == 0)
{
uint64_t v___x_295_; 
v___x_295_ = lean_uint64_add(v_quotient_284_, v___x_285_);
v___y_263_ = v_position_271_;
v___y_264_ = v___x_295_;
goto v___jp_262_;
}
else
{
v___y_263_ = v_position_271_;
v___y_264_ = v_quotient_284_;
goto v___jp_262_;
}
}
else
{
uint64_t v___x_296_; 
v___x_296_ = lean_uint64_add(v_quotient_284_, v___x_285_);
v___y_263_ = v_position_271_;
v___y_264_ = v___x_296_;
goto v___jp_262_;
}
}
else
{
v___y_263_ = v_position_271_;
v___y_264_ = v_quotient_284_;
goto v___jp_262_;
}
}
}
else
{
v___y_263_ = v_position_271_;
v___y_264_ = v_product_200_;
goto v___jp_262_;
}
}
else
{
uint64_t v___x_297_; uint64_t v___x_298_; 
v___x_297_ = lean_uint64_sub(v___x_274_, v___y_270_);
v___x_298_ = lean_uint64_shift_left(v_product_200_, v___x_297_);
v___y_263_ = v_position_271_;
v___y_264_ = v___x_298_;
goto v___jp_262_;
}
}
else
{
uint64_t v___x_299_; uint8_t v___x_300_; 
v___x_299_ = 149ULL;
v___x_300_ = lean_uint64_dec_lt(v_scale_201_, v___x_299_);
if (v___x_300_ == 0)
{
uint64_t v___x_301_; uint64_t v___x_302_; 
v___x_301_ = lean_uint64_sub(v_scale_201_, v___x_299_);
v___x_302_ = lean_uint64_shift_left(v_product_200_, v___x_301_);
v___y_231_ = v___x_302_;
goto v___jp_230_;
}
else
{
uint64_t v___x_303_; uint8_t v___x_304_; 
v___x_303_ = lean_uint64_sub(v___x_299_, v_scale_201_);
v___x_304_ = lean_uint64_dec_eq(v___x_303_, v___x_229_);
if (v___x_304_ == 0)
{
uint64_t v___x_305_; uint8_t v___x_306_; 
v___x_305_ = 64ULL;
v___x_306_ = lean_uint64_dec_lt(v___x_303_, v___x_305_);
if (v___x_306_ == 0)
{
uint8_t v___x_307_; 
v___x_307_ = lean_uint64_dec_eq(v___x_303_, v___x_305_);
if (v___x_307_ == 0)
{
v___y_231_ = v___x_229_;
goto v___jp_230_;
}
else
{
uint64_t v___x_308_; uint8_t v___x_309_; 
v___x_308_ = 9223372036854775808ULL;
v___x_309_ = lean_uint64_dec_lt(v___x_308_, v_product_200_);
if (v___x_309_ == 0)
{
v___y_231_ = v___x_229_;
goto v___jp_230_;
}
else
{
uint64_t v___x_310_; 
v___x_310_ = 1ULL;
v___y_231_ = v___x_310_;
goto v___jp_230_;
}
}
}
else
{
uint64_t v_quotient_311_; uint64_t v___x_312_; uint64_t v___x_313_; uint64_t v___x_314_; uint64_t v_remainder_315_; uint64_t v___x_316_; uint64_t v_half_317_; uint8_t v___x_318_; 
v_quotient_311_ = lean_uint64_shift_right(v_product_200_, v___x_303_);
v___x_312_ = 1ULL;
v___x_313_ = lean_uint64_shift_left(v___x_312_, v___x_303_);
v___x_314_ = lean_uint64_sub(v___x_313_, v___x_312_);
v_remainder_315_ = lean_uint64_land(v_product_200_, v___x_314_);
v___x_316_ = lean_uint64_sub(v___x_303_, v___x_312_);
v_half_317_ = lean_uint64_shift_left(v___x_312_, v___x_316_);
v___x_318_ = lean_uint64_dec_lt(v_remainder_315_, v_half_317_);
if (v___x_318_ == 0)
{
uint8_t v___x_319_; 
v___x_319_ = lean_uint64_dec_lt(v_half_317_, v_remainder_315_);
if (v___x_319_ == 0)
{
uint64_t v___x_320_; uint8_t v___x_321_; 
v___x_320_ = lean_uint64_land(v_quotient_311_, v___x_312_);
v___x_321_ = lean_uint64_dec_eq(v___x_320_, v___x_229_);
if (v___x_321_ == 0)
{
uint64_t v___x_322_; 
v___x_322_ = lean_uint64_add(v_quotient_311_, v___x_312_);
v___y_231_ = v___x_322_;
goto v___jp_230_;
}
else
{
v___y_231_ = v_quotient_311_;
goto v___jp_230_;
}
}
else
{
uint64_t v___x_323_; 
v___x_323_ = lean_uint64_add(v_quotient_311_, v___x_312_);
v___y_231_ = v___x_323_;
goto v___jp_230_;
}
}
else
{
v___y_231_ = v_quotient_311_;
goto v___jp_230_;
}
}
}
else
{
v___y_231_ = v_product_200_;
goto v___jp_230_;
}
}
}
}
v___jp_324_:
{
uint64_t v___x_327_; uint64_t v___x_328_; uint8_t v___x_329_; 
v___x_327_ = 1ULL;
v___x_328_ = lean_uint64_shift_right(v___y_325_, v___x_327_);
v___x_329_ = lean_uint64_dec_eq(v___x_328_, v___x_229_);
if (v___x_329_ == 0)
{
uint64_t v___x_330_; 
v___x_330_ = lean_uint64_add(v___y_326_, v___x_327_);
v___y_270_ = v___x_330_;
goto v___jp_269_;
}
else
{
v___y_270_ = v___y_326_;
goto v___jp_269_;
}
}
v___jp_331_:
{
uint64_t v___x_336_; uint8_t v___x_337_; 
v___x_336_ = lean_uint64_shift_right(v___y_334_, v___y_333_);
v___x_337_ = lean_uint64_dec_eq(v___x_336_, v___x_229_);
if (v___x_337_ == 0)
{
uint64_t v___x_338_; 
v___x_338_ = lean_uint64_add(v___y_332_, v___y_333_);
v___y_325_ = v___y_335_;
v___y_326_ = v___x_338_;
goto v___jp_324_;
}
else
{
v___y_325_ = v___y_335_;
v___y_326_ = v___y_332_;
goto v___jp_324_;
}
}
v___jp_339_:
{
uint64_t v___x_342_; uint64_t v___x_343_; uint8_t v___x_344_; 
v___x_342_ = 2ULL;
v___x_343_ = lean_uint64_shift_right(v___y_340_, v___x_342_);
v___x_344_ = lean_uint64_dec_eq(v___x_343_, v___x_229_);
if (v___x_344_ == 0)
{
v___y_332_ = v___y_341_;
v___y_333_ = v___x_342_;
v___y_334_ = v___y_340_;
v___y_335_ = v___x_343_;
goto v___jp_331_;
}
else
{
v___y_332_ = v___y_341_;
v___y_333_ = v___x_342_;
v___y_334_ = v___y_340_;
v___y_335_ = v___y_340_;
goto v___jp_331_;
}
}
v___jp_345_:
{
uint64_t v___x_350_; uint8_t v___x_351_; 
v___x_350_ = lean_uint64_shift_right(v___y_348_, v___y_346_);
v___x_351_ = lean_uint64_dec_eq(v___x_350_, v___x_229_);
if (v___x_351_ == 0)
{
uint64_t v___x_352_; 
v___x_352_ = lean_uint64_add(v___y_347_, v___y_346_);
v___y_340_ = v___y_349_;
v___y_341_ = v___x_352_;
goto v___jp_339_;
}
else
{
v___y_340_ = v___y_349_;
v___y_341_ = v___y_347_;
goto v___jp_339_;
}
}
v___jp_353_:
{
uint64_t v___x_356_; uint64_t v___x_357_; uint8_t v___x_358_; 
v___x_356_ = 4ULL;
v___x_357_ = lean_uint64_shift_right(v___y_354_, v___x_356_);
v___x_358_ = lean_uint64_dec_eq(v___x_357_, v___x_229_);
if (v___x_358_ == 0)
{
v___y_346_ = v___x_356_;
v___y_347_ = v___y_355_;
v___y_348_ = v___y_354_;
v___y_349_ = v___x_357_;
goto v___jp_345_;
}
else
{
v___y_346_ = v___x_356_;
v___y_347_ = v___y_355_;
v___y_348_ = v___y_354_;
v___y_349_ = v___y_354_;
goto v___jp_345_;
}
}
v___jp_359_:
{
uint64_t v___x_364_; uint8_t v___x_365_; 
v___x_364_ = lean_uint64_shift_right(v___y_361_, v___y_362_);
v___x_365_ = lean_uint64_dec_eq(v___x_364_, v___x_229_);
if (v___x_365_ == 0)
{
uint64_t v___x_366_; 
v___x_366_ = lean_uint64_add(v___y_360_, v___y_362_);
v___y_354_ = v___y_363_;
v___y_355_ = v___x_366_;
goto v___jp_353_;
}
else
{
v___y_354_ = v___y_363_;
v___y_355_ = v___y_360_;
goto v___jp_353_;
}
}
v___jp_367_:
{
uint64_t v___x_370_; uint64_t v___x_371_; uint8_t v___x_372_; 
v___x_370_ = 8ULL;
v___x_371_ = lean_uint64_shift_right(v___y_368_, v___x_370_);
v___x_372_ = lean_uint64_dec_eq(v___x_371_, v___x_229_);
if (v___x_372_ == 0)
{
v___y_360_ = v___y_369_;
v___y_361_ = v___y_368_;
v___y_362_ = v___x_370_;
v___y_363_ = v___x_371_;
goto v___jp_359_;
}
else
{
v___y_360_ = v___y_369_;
v___y_361_ = v___y_368_;
v___y_362_ = v___x_370_;
v___y_363_ = v___y_368_;
goto v___jp_359_;
}
}
v___jp_373_:
{
uint64_t v___x_378_; uint8_t v___x_379_; 
v___x_378_ = lean_uint64_shift_right(v___y_375_, v___y_376_);
v___x_379_ = lean_uint64_dec_eq(v___x_378_, v___x_229_);
if (v___x_379_ == 0)
{
uint64_t v___x_380_; 
v___x_380_ = lean_uint64_add(v___y_374_, v___y_376_);
v___y_368_ = v___y_377_;
v___y_369_ = v___x_380_;
goto v___jp_367_;
}
else
{
v___y_368_ = v___y_377_;
v___y_369_ = v___y_374_;
goto v___jp_367_;
}
}
v___jp_381_:
{
uint64_t v___x_384_; uint64_t v___x_385_; uint8_t v___x_386_; 
v___x_384_ = 16ULL;
v___x_385_ = lean_uint64_shift_right(v___y_382_, v___x_384_);
v___x_386_ = lean_uint64_dec_eq(v___x_385_, v___x_229_);
if (v___x_386_ == 0)
{
v___y_374_ = v___y_383_;
v___y_375_ = v___y_382_;
v___y_376_ = v___x_384_;
v___y_377_ = v___x_385_;
goto v___jp_373_;
}
else
{
v___y_374_ = v___y_383_;
v___y_375_ = v___y_382_;
v___y_376_ = v___x_384_;
v___y_377_ = v___y_382_;
goto v___jp_373_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_roundP___boxed(lean_object* v_sign_397_, lean_object* v_product_398_, lean_object* v_scale_399_){
_start:
{
uint8_t v_sign_boxed_400_; uint64_t v_product_boxed_401_; uint64_t v_scale_boxed_402_; uint32_t v_res_403_; lean_object* v_r_404_; 
v_sign_boxed_400_ = lean_unbox(v_sign_397_);
v_product_boxed_401_ = lean_unbox_uint64(v_product_398_);
lean_dec_ref(v_product_398_);
v_scale_boxed_402_ = lean_unbox_uint64(v_scale_399_);
lean_dec_ref(v_scale_399_);
v_res_403_ = lp_competition_Submission_TunedAdd_roundP(v_sign_boxed_400_, v_product_boxed_401_, v_scale_boxed_402_);
v_r_404_ = lean_box_uint32(v_res_403_);
return v_r_404_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_core(uint32_t v_xBits_407_, uint32_t v_yBits_408_){
_start:
{
uint32_t v___y_410_; uint32_t v___y_414_; uint32_t v___y_418_; uint32_t v___y_419_; lean_object* v___y_424_; uint64_t v___y_425_; uint64_t v___y_426_; uint32_t v___y_441_; uint32_t v___y_442_; lean_object* v___y_447_; uint64_t v___y_448_; uint64_t v___y_449_; uint32_t v___x_463_; uint32_t v___x_464_; uint32_t v___x_465_; uint32_t v___y_467_; uint32_t v___y_468_; uint32_t v___y_469_; uint32_t v___y_477_; lean_object* v___y_478_; uint32_t v___y_479_; uint64_t v___y_484_; uint64_t v___y_485_; lean_object* v___y_486_; uint64_t v___y_487_; uint8_t v___y_497_; lean_object* v___y_498_; uint64_t v___y_499_; uint64_t v___y_500_; uint64_t v___y_501_; uint64_t v___y_509_; lean_object* v___y_510_; uint64_t v___y_511_; uint64_t v___y_512_; lean_object* v___y_518_; uint64_t v___y_519_; uint64_t v___y_520_; lean_object* v___y_521_; uint64_t v___y_522_; uint64_t v___y_523_; uint64_t v___y_587_; lean_object* v___y_588_; uint64_t v___y_589_; lean_object* v___y_590_; uint64_t v___y_591_; uint64_t v___y_592_; uint64_t v___y_593_; lean_object* v___y_599_; uint64_t v___y_600_; uint64_t v___y_601_; uint64_t v___y_602_; uint64_t v___y_603_; uint64_t v___y_604_; uint64_t v___y_605_; lean_object* v___y_606_; uint64_t v___y_607_; uint64_t v___y_612_; lean_object* v___y_613_; uint64_t v___y_614_; uint64_t v___y_615_; lean_object* v___y_616_; uint64_t v___y_617_; uint64_t v___y_618_; uint64_t v___y_623_; uint64_t v___y_624_; lean_object* v___y_625_; uint64_t v___y_626_; uint64_t v___y_627_; uint64_t v___y_628_; uint64_t v___y_629_; lean_object* v___y_630_; uint64_t v___y_631_; uint64_t v___y_636_; lean_object* v___y_637_; uint64_t v___y_638_; uint64_t v___y_639_; lean_object* v___y_640_; uint64_t v___y_641_; uint64_t v___y_642_; uint64_t v___y_647_; uint64_t v___y_648_; lean_object* v___y_649_; uint64_t v___y_650_; uint64_t v___y_651_; uint64_t v___y_652_; uint64_t v___y_653_; lean_object* v___y_654_; uint64_t v___y_655_; uint64_t v___y_660_; lean_object* v___y_661_; uint64_t v___y_662_; uint64_t v___y_663_; lean_object* v___y_664_; uint64_t v___y_665_; uint64_t v___y_666_; uint64_t v___y_671_; uint64_t v___y_672_; lean_object* v___y_673_; uint64_t v___y_674_; uint64_t v___y_675_; uint64_t v___y_676_; uint64_t v___y_677_; lean_object* v___y_678_; uint64_t v___y_679_; uint64_t v___y_684_; lean_object* v___y_685_; uint64_t v___y_686_; uint64_t v___y_687_; lean_object* v___y_688_; uint64_t v___y_689_; uint64_t v___y_690_; lean_object* v___y_695_; uint64_t v___y_696_; uint64_t v___y_697_; uint64_t v___y_698_; uint64_t v___y_699_; lean_object* v___y_700_; uint64_t v___y_701_; uint64_t v___y_706_; lean_object* v_fst_707_; lean_object* v_snd_708_; uint8_t v___y_723_; uint8_t v___y_724_; uint64_t v___y_725_; uint64_t v___y_726_; uint64_t v___y_727_; uint8_t v___y_728_; uint8_t v___y_740_; uint8_t v___y_741_; uint64_t v___y_742_; uint64_t v___y_743_; uint64_t v___y_744_; uint8_t v___y_745_; uint32_t v___y_750_; uint32_t v___y_751_; uint32_t v___y_752_; lean_object* v___y_760_; uint32_t v___y_761_; uint32_t v___y_762_; lean_object* v___y_767_; uint64_t v___y_768_; uint64_t v___y_769_; uint64_t v___y_770_; lean_object* v___y_780_; uint64_t v___y_781_; uint8_t v___y_782_; uint64_t v___y_783_; uint64_t v___y_784_; lean_object* v___y_792_; uint64_t v___y_793_; uint64_t v___y_794_; uint64_t v___y_795_; lean_object* v___y_801_; lean_object* v___y_802_; uint64_t v___y_803_; uint64_t v___y_804_; uint64_t v___y_805_; uint64_t v___y_806_; lean_object* v___y_870_; lean_object* v___y_871_; uint64_t v___y_872_; uint64_t v___y_873_; uint64_t v___y_874_; uint64_t v___y_875_; uint64_t v___y_876_; lean_object* v___y_882_; uint64_t v___y_883_; lean_object* v___y_884_; uint64_t v___y_885_; uint64_t v___y_886_; uint64_t v___y_887_; uint64_t v___y_888_; uint64_t v___y_889_; uint64_t v___y_890_; lean_object* v___y_895_; lean_object* v___y_896_; uint64_t v___y_897_; uint64_t v___y_898_; uint64_t v___y_899_; uint64_t v___y_900_; uint64_t v___y_901_; lean_object* v___y_906_; lean_object* v___y_907_; uint64_t v___y_908_; uint64_t v___y_909_; uint64_t v___y_910_; uint64_t v___y_911_; uint64_t v___y_912_; uint64_t v___y_913_; uint64_t v___y_914_; lean_object* v___y_919_; lean_object* v___y_920_; uint64_t v___y_921_; uint64_t v___y_922_; uint64_t v___y_923_; uint64_t v___y_924_; uint64_t v___y_925_; lean_object* v___y_930_; uint64_t v___y_931_; lean_object* v___y_932_; uint64_t v___y_933_; uint64_t v___y_934_; uint64_t v___y_935_; uint64_t v___y_936_; uint64_t v___y_937_; uint64_t v___y_938_; lean_object* v___y_943_; lean_object* v___y_944_; uint64_t v___y_945_; uint64_t v___y_946_; uint64_t v___y_947_; uint64_t v___y_948_; uint64_t v___y_949_; lean_object* v___y_954_; lean_object* v___y_955_; uint64_t v___y_956_; uint64_t v___y_957_; uint64_t v___y_958_; uint64_t v___y_959_; uint64_t v___y_960_; uint64_t v___y_961_; uint64_t v___y_962_; lean_object* v___y_967_; lean_object* v___y_968_; uint64_t v___y_969_; uint64_t v___y_970_; uint64_t v___y_971_; uint64_t v___y_972_; uint64_t v___y_973_; lean_object* v___y_978_; lean_object* v___y_979_; uint64_t v___y_980_; uint64_t v___y_981_; uint64_t v___y_982_; uint64_t v___y_983_; uint64_t v___y_984_; uint64_t v___y_989_; lean_object* v_fst_990_; lean_object* v_snd_991_; uint64_t v___y_1006_; uint8_t v___y_1007_; uint8_t v___y_1008_; uint64_t v___y_1009_; uint64_t v___y_1010_; uint8_t v___y_1011_; uint8_t v___y_1023_; uint64_t v___y_1024_; uint8_t v___y_1025_; uint64_t v___y_1026_; uint64_t v___y_1027_; uint8_t v___y_1028_; uint8_t v___y_1033_; uint8_t v___y_1034_; uint64_t v___y_1035_; uint64_t v___y_1036_; uint64_t v___y_1037_; uint64_t v___y_1038_; uint32_t v_xExponent_1048_; uint32_t v___x_1049_; uint32_t v_yExponent_1050_; uint8_t v___y_1052_; uint8_t v___y_1053_; uint64_t v___y_1054_; uint64_t v___y_1055_; uint64_t v___y_1056_; uint8_t v___y_1063_; uint8_t v___y_1064_; uint64_t v___y_1065_; uint64_t v___y_1066_; uint8_t v___y_1073_; uint8_t v___y_1074_; uint64_t v___y_1075_; uint8_t v___y_1085_; uint8_t v___y_1086_; uint8_t v___y_1096_; uint32_t v___x_1103_; uint32_t v___x_1104_; uint32_t v___x_1105_; uint8_t v___x_1106_; 
v___x_463_ = 23;
v___x_464_ = lean_uint32_shift_right(v_xBits_407_, v___x_463_);
v___x_465_ = 255;
v_xExponent_1048_ = lean_uint32_land(v___x_464_, v___x_465_);
v___x_1049_ = lean_uint32_shift_right(v_yBits_408_, v___x_463_);
v_yExponent_1050_ = lean_uint32_land(v___x_1049_, v___x_465_);
v___x_1103_ = 2147483648;
v___x_1104_ = lean_uint32_land(v_xBits_407_, v___x_1103_);
v___x_1105_ = 0;
v___x_1106_ = lean_uint32_dec_eq(v___x_1104_, v___x_1105_);
if (v___x_1106_ == 0)
{
uint8_t v___x_1107_; 
v___x_1107_ = 1;
v___y_1096_ = v___x_1107_;
goto v___jp_1095_;
}
else
{
uint8_t v___x_1108_; 
v___x_1108_ = 0;
v___y_1096_ = v___x_1108_;
goto v___jp_1095_;
}
v___jp_409_:
{
uint32_t v___x_411_; uint32_t v___x_412_; 
v___x_411_ = 8388608;
v___x_412_ = lean_uint32_lor(v___y_410_, v___x_411_);
return v___x_412_;
}
v___jp_413_:
{
uint32_t v___x_415_; uint32_t v___x_416_; 
v___x_415_ = 8388608;
v___x_416_ = lean_uint32_lor(v___y_414_, v___x_415_);
return v___x_416_;
}
v___jp_417_:
{
uint32_t v___x_420_; uint32_t v___x_421_; uint32_t v___x_422_; 
v___x_420_ = 8388607;
v___x_421_ = lean_uint32_land(v___y_418_, v___x_420_);
v___x_422_ = lean_uint32_lor(v___y_419_, v___x_421_);
return v___x_422_;
}
v___jp_423_:
{
uint8_t v___x_427_; 
v___x_427_ = lean_uint64_dec_eq(v___y_426_, v___y_425_);
if (v___x_427_ == 0)
{
uint64_t v___x_428_; uint8_t v___x_429_; 
v___x_428_ = 8388608ULL;
v___x_429_ = lean_uint64_dec_eq(v___y_426_, v___x_428_);
if (v___x_429_ == 0)
{
uint32_t v___x_430_; uint8_t v___x_431_; 
v___x_430_ = lean_uint64_to_uint32(v___y_426_);
v___x_431_ = lean_unbox(v___y_424_);
lean_dec(v___y_424_);
if (v___x_431_ == 0)
{
uint32_t v___x_432_; 
v___x_432_ = 0;
v___y_418_ = v___x_430_;
v___y_419_ = v___x_432_;
goto v___jp_417_;
}
else
{
uint32_t v___x_433_; 
v___x_433_ = 2147483648;
v___y_418_ = v___x_430_;
v___y_419_ = v___x_433_;
goto v___jp_417_;
}
}
else
{
uint8_t v___x_434_; 
v___x_434_ = lean_unbox(v___y_424_);
lean_dec(v___y_424_);
if (v___x_434_ == 0)
{
uint32_t v___x_435_; 
v___x_435_ = 0;
v___y_414_ = v___x_435_;
goto v___jp_413_;
}
else
{
uint32_t v___x_436_; 
v___x_436_ = 2147483648;
v___y_414_ = v___x_436_;
goto v___jp_413_;
}
}
}
else
{
uint8_t v___x_437_; 
v___x_437_ = lean_unbox(v___y_424_);
lean_dec(v___y_424_);
if (v___x_437_ == 0)
{
uint32_t v___x_438_; 
v___x_438_ = 0;
return v___x_438_;
}
else
{
uint32_t v___x_439_; 
v___x_439_ = 2147483648;
return v___x_439_;
}
}
}
v___jp_440_:
{
uint32_t v___x_443_; uint32_t v___x_444_; uint32_t v___x_445_; 
v___x_443_ = 8388607;
v___x_444_ = lean_uint32_land(v___y_441_, v___x_443_);
v___x_445_ = lean_uint32_lor(v___y_442_, v___x_444_);
return v___x_445_;
}
v___jp_446_:
{
uint8_t v___x_450_; 
v___x_450_ = lean_uint64_dec_eq(v___y_449_, v___y_448_);
if (v___x_450_ == 0)
{
uint64_t v___x_451_; uint8_t v___x_452_; 
v___x_451_ = 8388608ULL;
v___x_452_ = lean_uint64_dec_eq(v___y_449_, v___x_451_);
if (v___x_452_ == 0)
{
uint32_t v___x_453_; uint8_t v___x_454_; 
v___x_453_ = lean_uint64_to_uint32(v___y_449_);
v___x_454_ = lean_unbox(v___y_447_);
lean_dec(v___y_447_);
if (v___x_454_ == 0)
{
uint32_t v___x_455_; 
v___x_455_ = 0;
v___y_441_ = v___x_453_;
v___y_442_ = v___x_455_;
goto v___jp_440_;
}
else
{
uint32_t v___x_456_; 
v___x_456_ = 2147483648;
v___y_441_ = v___x_453_;
v___y_442_ = v___x_456_;
goto v___jp_440_;
}
}
else
{
uint8_t v___x_457_; 
v___x_457_ = lean_unbox(v___y_447_);
lean_dec(v___y_447_);
if (v___x_457_ == 0)
{
uint32_t v___x_458_; 
v___x_458_ = 0;
v___y_410_ = v___x_458_;
goto v___jp_409_;
}
else
{
uint32_t v___x_459_; 
v___x_459_ = 2147483648;
v___y_410_ = v___x_459_;
goto v___jp_409_;
}
}
}
else
{
uint8_t v___x_460_; 
v___x_460_ = lean_unbox(v___y_447_);
lean_dec(v___y_447_);
if (v___x_460_ == 0)
{
uint32_t v___x_461_; 
v___x_461_ = 0;
return v___x_461_;
}
else
{
uint32_t v___x_462_; 
v___x_462_ = 2147483648;
return v___x_462_;
}
}
}
v___jp_466_:
{
uint32_t v___x_470_; uint32_t v___x_471_; uint32_t v___x_472_; uint32_t v___x_473_; uint32_t v___x_474_; uint32_t v___x_475_; 
v___x_470_ = lean_uint32_land(v___y_468_, v___x_465_);
v___x_471_ = lean_uint32_shift_left(v___x_470_, v___x_463_);
v___x_472_ = lean_uint32_lor(v___y_469_, v___x_471_);
v___x_473_ = 8388607;
v___x_474_ = lean_uint32_land(v___y_467_, v___x_473_);
v___x_475_ = lean_uint32_lor(v___x_472_, v___x_474_);
return v___x_475_;
}
v___jp_476_:
{
uint8_t v___x_480_; 
v___x_480_ = lean_unbox(v___y_478_);
lean_dec(v___y_478_);
if (v___x_480_ == 0)
{
uint32_t v___x_481_; 
v___x_481_ = 0;
v___y_467_ = v___y_479_;
v___y_468_ = v___y_477_;
v___y_469_ = v___x_481_;
goto v___jp_466_;
}
else
{
uint32_t v___x_482_; 
v___x_482_ = 2147483648;
v___y_467_ = v___y_479_;
v___y_468_ = v___y_477_;
v___y_469_ = v___x_482_;
goto v___jp_466_;
}
}
v___jp_483_:
{
uint64_t v___x_488_; uint64_t v_encodedExponent_489_; uint32_t v___x_490_; uint64_t v___x_491_; uint8_t v___x_492_; 
v___x_488_ = 171ULL;
v_encodedExponent_489_ = lean_uint64_sub(v___y_484_, v___x_488_);
v___x_490_ = lean_uint64_to_uint32(v_encodedExponent_489_);
v___x_491_ = 8388608ULL;
v___x_492_ = lean_uint64_dec_lt(v___y_487_, v___x_491_);
if (v___x_492_ == 0)
{
uint64_t v___x_493_; uint32_t v___x_494_; 
v___x_493_ = lean_uint64_sub(v___y_487_, v___x_491_);
v___x_494_ = lean_uint64_to_uint32(v___x_493_);
v___y_477_ = v___x_490_;
v___y_478_ = v___y_486_;
v___y_479_ = v___x_494_;
goto v___jp_476_;
}
else
{
uint32_t v___x_495_; 
v___x_495_ = lean_uint64_to_uint32(v___y_485_);
v___y_477_ = v___x_490_;
v___y_478_ = v___y_486_;
v___y_479_ = v___x_495_;
goto v___jp_476_;
}
}
v___jp_496_:
{
uint64_t v___x_502_; uint8_t v___x_503_; 
v___x_502_ = 425ULL;
v___x_503_ = lean_uint64_dec_lt(v___x_502_, v___y_501_);
if (v___x_503_ == 0)
{
if (v___y_497_ == 0)
{
v___y_484_ = v___y_501_;
v___y_485_ = v___y_499_;
v___y_486_ = v___y_498_;
v___y_487_ = v___y_500_;
goto v___jp_483_;
}
else
{
uint64_t v___x_504_; 
v___x_504_ = 8388608ULL;
v___y_484_ = v___y_501_;
v___y_485_ = v___y_499_;
v___y_486_ = v___y_498_;
v___y_487_ = v___x_504_;
goto v___jp_483_;
}
}
else
{
uint8_t v___x_505_; 
v___x_505_ = lean_unbox(v___y_498_);
lean_dec(v___y_498_);
if (v___x_505_ == 0)
{
uint32_t v___x_506_; 
v___x_506_ = 2139095040;
return v___x_506_;
}
else
{
uint32_t v___x_507_; 
v___x_507_ = 4286578688;
return v___x_507_;
}
}
}
v___jp_508_:
{
uint64_t v___x_513_; uint8_t v_carry_514_; 
v___x_513_ = 16777216ULL;
v_carry_514_ = lean_uint64_dec_eq(v___y_512_, v___x_513_);
if (v_carry_514_ == 0)
{
v___y_497_ = v_carry_514_;
v___y_498_ = v___y_510_;
v___y_499_ = v___y_509_;
v___y_500_ = v___y_512_;
v___y_501_ = v___y_511_;
goto v___jp_496_;
}
else
{
uint64_t v___x_515_; uint64_t v___x_516_; 
v___x_515_ = 1ULL;
v___x_516_ = lean_uint64_add(v___y_511_, v___x_515_);
v___y_497_ = v_carry_514_;
v___y_498_ = v___y_510_;
v___y_499_ = v___y_509_;
v___y_500_ = v___y_512_;
v___y_501_ = v___x_516_;
goto v___jp_496_;
}
}
v___jp_517_:
{
uint64_t v_position_524_; uint64_t v___x_525_; uint8_t v___x_526_; 
v_position_524_ = lean_uint64_add(v___y_523_, v___y_519_);
v___x_525_ = 172ULL;
v___x_526_ = lean_uint64_dec_lt(v_position_524_, v___x_525_);
if (v___x_526_ == 0)
{
uint64_t v___x_527_; uint8_t v___x_528_; 
v___x_527_ = 23ULL;
v___x_528_ = lean_uint64_dec_lt(v___y_523_, v___x_527_);
if (v___x_528_ == 0)
{
uint64_t v___x_529_; uint8_t v___x_530_; 
v___x_529_ = lean_uint64_sub(v___y_523_, v___x_527_);
v___x_530_ = lean_uint64_dec_eq(v___x_529_, v___y_522_);
if (v___x_530_ == 0)
{
uint64_t v___x_531_; uint8_t v___x_532_; 
v___x_531_ = 64ULL;
v___x_532_ = lean_uint64_dec_lt(v___x_529_, v___x_531_);
if (v___x_532_ == 0)
{
uint8_t v___x_533_; 
v___x_533_ = lean_uint64_dec_eq(v___x_529_, v___x_531_);
if (v___x_533_ == 0)
{
lean_dec(v___y_518_);
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v___y_522_;
goto v___jp_508_;
}
else
{
uint64_t v___x_534_; uint64_t v___x_535_; uint8_t v___x_536_; 
v___x_534_ = 9223372036854775808ULL;
v___x_535_ = lean_unbox_uint64(v___y_518_);
lean_dec(v___y_518_);
v___x_536_ = lean_uint64_dec_lt(v___x_534_, v___x_535_);
if (v___x_536_ == 0)
{
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v___y_522_;
goto v___jp_508_;
}
else
{
uint64_t v___x_537_; 
v___x_537_ = 1ULL;
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v___x_537_;
goto v___jp_508_;
}
}
}
else
{
uint64_t v___x_538_; uint64_t v_quotient_539_; uint64_t v___x_540_; uint64_t v___x_541_; uint64_t v___x_542_; uint64_t v___x_543_; uint64_t v_remainder_544_; uint64_t v___x_545_; uint64_t v_half_546_; uint8_t v___x_547_; 
v___x_538_ = lean_unbox_uint64(v___y_518_);
v_quotient_539_ = lean_uint64_shift_right(v___x_538_, v___x_529_);
v___x_540_ = 1ULL;
v___x_541_ = lean_uint64_shift_left(v___x_540_, v___x_529_);
v___x_542_ = lean_uint64_sub(v___x_541_, v___x_540_);
v___x_543_ = lean_unbox_uint64(v___y_518_);
lean_dec(v___y_518_);
v_remainder_544_ = lean_uint64_land(v___x_543_, v___x_542_);
v___x_545_ = lean_uint64_sub(v___x_529_, v___x_540_);
v_half_546_ = lean_uint64_shift_left(v___x_540_, v___x_545_);
v___x_547_ = lean_uint64_dec_lt(v_remainder_544_, v_half_546_);
if (v___x_547_ == 0)
{
uint8_t v___x_548_; 
v___x_548_ = lean_uint64_dec_lt(v_half_546_, v_remainder_544_);
if (v___x_548_ == 0)
{
uint64_t v___x_549_; uint8_t v___x_550_; 
v___x_549_ = lean_uint64_land(v_quotient_539_, v___x_540_);
v___x_550_ = lean_uint64_dec_eq(v___x_549_, v___y_522_);
if (v___x_550_ == 0)
{
uint64_t v___x_551_; 
v___x_551_ = lean_uint64_add(v_quotient_539_, v___x_540_);
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v___x_551_;
goto v___jp_508_;
}
else
{
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v_quotient_539_;
goto v___jp_508_;
}
}
else
{
uint64_t v___x_552_; 
v___x_552_ = lean_uint64_add(v_quotient_539_, v___x_540_);
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v___x_552_;
goto v___jp_508_;
}
}
else
{
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v_quotient_539_;
goto v___jp_508_;
}
}
}
else
{
uint64_t v___x_553_; 
v___x_553_ = lean_unbox_uint64(v___y_518_);
lean_dec(v___y_518_);
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v___x_553_;
goto v___jp_508_;
}
}
else
{
uint64_t v___x_554_; uint64_t v___x_555_; uint64_t v___x_556_; 
v___x_554_ = lean_uint64_sub(v___x_527_, v___y_523_);
v___x_555_ = lean_unbox_uint64(v___y_518_);
lean_dec(v___y_518_);
v___x_556_ = lean_uint64_shift_left(v___x_555_, v___x_554_);
v___y_509_ = v___y_522_;
v___y_510_ = v___y_521_;
v___y_511_ = v_position_524_;
v___y_512_ = v___x_556_;
goto v___jp_508_;
}
}
else
{
uint8_t v___x_557_; 
v___x_557_ = lean_uint64_dec_lt(v___y_519_, v___y_520_);
if (v___x_557_ == 0)
{
uint64_t v___x_558_; uint64_t v___x_559_; uint64_t v___x_560_; 
v___x_558_ = lean_uint64_sub(v___y_519_, v___y_520_);
v___x_559_ = lean_unbox_uint64(v___y_518_);
lean_dec(v___y_518_);
v___x_560_ = lean_uint64_shift_left(v___x_559_, v___x_558_);
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v___x_560_;
goto v___jp_423_;
}
else
{
uint64_t v___x_561_; uint8_t v___x_562_; 
v___x_561_ = lean_uint64_sub(v___y_520_, v___y_519_);
v___x_562_ = lean_uint64_dec_eq(v___x_561_, v___y_522_);
if (v___x_562_ == 0)
{
uint64_t v___x_563_; uint8_t v___x_564_; 
v___x_563_ = 64ULL;
v___x_564_ = lean_uint64_dec_lt(v___x_561_, v___x_563_);
if (v___x_564_ == 0)
{
uint8_t v___x_565_; 
v___x_565_ = lean_uint64_dec_eq(v___x_561_, v___x_563_);
if (v___x_565_ == 0)
{
lean_dec(v___y_518_);
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v___y_522_;
goto v___jp_423_;
}
else
{
uint64_t v___x_566_; uint64_t v___x_567_; uint8_t v___x_568_; 
v___x_566_ = 9223372036854775808ULL;
v___x_567_ = lean_unbox_uint64(v___y_518_);
lean_dec(v___y_518_);
v___x_568_ = lean_uint64_dec_lt(v___x_566_, v___x_567_);
if (v___x_568_ == 0)
{
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v___y_522_;
goto v___jp_423_;
}
else
{
uint64_t v___x_569_; 
v___x_569_ = 1ULL;
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v___x_569_;
goto v___jp_423_;
}
}
}
else
{
uint64_t v___x_570_; uint64_t v_quotient_571_; uint64_t v___x_572_; uint64_t v___x_573_; uint64_t v___x_574_; uint64_t v___x_575_; uint64_t v_remainder_576_; uint64_t v___x_577_; uint64_t v_half_578_; uint8_t v___x_579_; 
v___x_570_ = lean_unbox_uint64(v___y_518_);
v_quotient_571_ = lean_uint64_shift_right(v___x_570_, v___x_561_);
v___x_572_ = 1ULL;
v___x_573_ = lean_uint64_shift_left(v___x_572_, v___x_561_);
v___x_574_ = lean_uint64_sub(v___x_573_, v___x_572_);
v___x_575_ = lean_unbox_uint64(v___y_518_);
lean_dec(v___y_518_);
v_remainder_576_ = lean_uint64_land(v___x_575_, v___x_574_);
v___x_577_ = lean_uint64_sub(v___x_561_, v___x_572_);
v_half_578_ = lean_uint64_shift_left(v___x_572_, v___x_577_);
v___x_579_ = lean_uint64_dec_lt(v_remainder_576_, v_half_578_);
if (v___x_579_ == 0)
{
uint8_t v___x_580_; 
v___x_580_ = lean_uint64_dec_lt(v_half_578_, v_remainder_576_);
if (v___x_580_ == 0)
{
uint64_t v___x_581_; uint8_t v___x_582_; 
v___x_581_ = lean_uint64_land(v_quotient_571_, v___x_572_);
v___x_582_ = lean_uint64_dec_eq(v___x_581_, v___y_522_);
if (v___x_582_ == 0)
{
uint64_t v___x_583_; 
v___x_583_ = lean_uint64_add(v_quotient_571_, v___x_572_);
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v___x_583_;
goto v___jp_423_;
}
else
{
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v_quotient_571_;
goto v___jp_423_;
}
}
else
{
uint64_t v___x_584_; 
v___x_584_ = lean_uint64_add(v_quotient_571_, v___x_572_);
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v___x_584_;
goto v___jp_423_;
}
}
else
{
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v_quotient_571_;
goto v___jp_423_;
}
}
}
else
{
uint64_t v___x_585_; 
v___x_585_ = lean_unbox_uint64(v___y_518_);
lean_dec(v___y_518_);
v___y_424_ = v___y_521_;
v___y_425_ = v___y_522_;
v___y_426_ = v___x_585_;
goto v___jp_423_;
}
}
}
}
v___jp_586_:
{
uint64_t v___x_594_; uint64_t v___x_595_; uint8_t v___x_596_; 
v___x_594_ = 1ULL;
v___x_595_ = lean_uint64_shift_right(v___y_592_, v___x_594_);
v___x_596_ = lean_uint64_dec_eq(v___x_595_, v___y_591_);
if (v___x_596_ == 0)
{
uint64_t v___x_597_; 
v___x_597_ = lean_uint64_add(v___y_593_, v___x_594_);
v___y_518_ = v___y_588_;
v___y_519_ = v___y_587_;
v___y_520_ = v___y_589_;
v___y_521_ = v___y_590_;
v___y_522_ = v___y_591_;
v___y_523_ = v___x_597_;
goto v___jp_517_;
}
else
{
v___y_518_ = v___y_588_;
v___y_519_ = v___y_587_;
v___y_520_ = v___y_589_;
v___y_521_ = v___y_590_;
v___y_522_ = v___y_591_;
v___y_523_ = v___y_593_;
goto v___jp_517_;
}
}
v___jp_598_:
{
uint64_t v___x_608_; uint8_t v___x_609_; 
v___x_608_ = lean_uint64_shift_right(v___y_602_, v___y_601_);
v___x_609_ = lean_uint64_dec_eq(v___x_608_, v___y_605_);
if (v___x_609_ == 0)
{
uint64_t v___x_610_; 
v___x_610_ = lean_uint64_add(v___y_603_, v___y_601_);
v___y_587_ = v___y_600_;
v___y_588_ = v___y_599_;
v___y_589_ = v___y_604_;
v___y_590_ = v___y_606_;
v___y_591_ = v___y_605_;
v___y_592_ = v___y_607_;
v___y_593_ = v___x_610_;
goto v___jp_586_;
}
else
{
v___y_587_ = v___y_600_;
v___y_588_ = v___y_599_;
v___y_589_ = v___y_604_;
v___y_590_ = v___y_606_;
v___y_591_ = v___y_605_;
v___y_592_ = v___y_607_;
v___y_593_ = v___y_603_;
goto v___jp_586_;
}
}
v___jp_611_:
{
uint64_t v___x_619_; uint64_t v___x_620_; uint8_t v___x_621_; 
v___x_619_ = 2ULL;
v___x_620_ = lean_uint64_shift_right(v___y_614_, v___x_619_);
v___x_621_ = lean_uint64_dec_eq(v___x_620_, v___y_617_);
if (v___x_621_ == 0)
{
v___y_599_ = v___y_613_;
v___y_600_ = v___y_612_;
v___y_601_ = v___x_619_;
v___y_602_ = v___y_614_;
v___y_603_ = v___y_618_;
v___y_604_ = v___y_615_;
v___y_605_ = v___y_617_;
v___y_606_ = v___y_616_;
v___y_607_ = v___x_620_;
goto v___jp_598_;
}
else
{
v___y_599_ = v___y_613_;
v___y_600_ = v___y_612_;
v___y_601_ = v___x_619_;
v___y_602_ = v___y_614_;
v___y_603_ = v___y_618_;
v___y_604_ = v___y_615_;
v___y_605_ = v___y_617_;
v___y_606_ = v___y_616_;
v___y_607_ = v___y_614_;
goto v___jp_598_;
}
}
v___jp_622_:
{
uint64_t v___x_632_; uint8_t v___x_633_; 
v___x_632_ = lean_uint64_shift_right(v___y_627_, v___y_624_);
v___x_633_ = lean_uint64_dec_eq(v___x_632_, v___y_629_);
if (v___x_633_ == 0)
{
uint64_t v___x_634_; 
v___x_634_ = lean_uint64_add(v___y_623_, v___y_624_);
v___y_612_ = v___y_626_;
v___y_613_ = v___y_625_;
v___y_614_ = v___y_631_;
v___y_615_ = v___y_628_;
v___y_616_ = v___y_630_;
v___y_617_ = v___y_629_;
v___y_618_ = v___x_634_;
goto v___jp_611_;
}
else
{
v___y_612_ = v___y_626_;
v___y_613_ = v___y_625_;
v___y_614_ = v___y_631_;
v___y_615_ = v___y_628_;
v___y_616_ = v___y_630_;
v___y_617_ = v___y_629_;
v___y_618_ = v___y_623_;
goto v___jp_611_;
}
}
v___jp_635_:
{
uint64_t v___x_643_; uint64_t v___x_644_; uint8_t v___x_645_; 
v___x_643_ = 4ULL;
v___x_644_ = lean_uint64_shift_right(v___y_638_, v___x_643_);
v___x_645_ = lean_uint64_dec_eq(v___x_644_, v___y_641_);
if (v___x_645_ == 0)
{
v___y_623_ = v___y_642_;
v___y_624_ = v___x_643_;
v___y_625_ = v___y_637_;
v___y_626_ = v___y_636_;
v___y_627_ = v___y_638_;
v___y_628_ = v___y_639_;
v___y_629_ = v___y_641_;
v___y_630_ = v___y_640_;
v___y_631_ = v___x_644_;
goto v___jp_622_;
}
else
{
v___y_623_ = v___y_642_;
v___y_624_ = v___x_643_;
v___y_625_ = v___y_637_;
v___y_626_ = v___y_636_;
v___y_627_ = v___y_638_;
v___y_628_ = v___y_639_;
v___y_629_ = v___y_641_;
v___y_630_ = v___y_640_;
v___y_631_ = v___y_638_;
goto v___jp_622_;
}
}
v___jp_646_:
{
uint64_t v___x_656_; uint8_t v___x_657_; 
v___x_656_ = lean_uint64_shift_right(v___y_651_, v___y_648_);
v___x_657_ = lean_uint64_dec_eq(v___x_656_, v___y_653_);
if (v___x_657_ == 0)
{
uint64_t v___x_658_; 
v___x_658_ = lean_uint64_add(v___y_647_, v___y_648_);
v___y_636_ = v___y_650_;
v___y_637_ = v___y_649_;
v___y_638_ = v___y_655_;
v___y_639_ = v___y_652_;
v___y_640_ = v___y_654_;
v___y_641_ = v___y_653_;
v___y_642_ = v___x_658_;
goto v___jp_635_;
}
else
{
v___y_636_ = v___y_650_;
v___y_637_ = v___y_649_;
v___y_638_ = v___y_655_;
v___y_639_ = v___y_652_;
v___y_640_ = v___y_654_;
v___y_641_ = v___y_653_;
v___y_642_ = v___y_647_;
goto v___jp_635_;
}
}
v___jp_659_:
{
uint64_t v___x_667_; uint64_t v___x_668_; uint8_t v___x_669_; 
v___x_667_ = 8ULL;
v___x_668_ = lean_uint64_shift_right(v___y_662_, v___x_667_);
v___x_669_ = lean_uint64_dec_eq(v___x_668_, v___y_665_);
if (v___x_669_ == 0)
{
v___y_647_ = v___y_666_;
v___y_648_ = v___x_667_;
v___y_649_ = v___y_661_;
v___y_650_ = v___y_660_;
v___y_651_ = v___y_662_;
v___y_652_ = v___y_663_;
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___x_668_;
goto v___jp_646_;
}
else
{
v___y_647_ = v___y_666_;
v___y_648_ = v___x_667_;
v___y_649_ = v___y_661_;
v___y_650_ = v___y_660_;
v___y_651_ = v___y_662_;
v___y_652_ = v___y_663_;
v___y_653_ = v___y_665_;
v___y_654_ = v___y_664_;
v___y_655_ = v___y_662_;
goto v___jp_646_;
}
}
v___jp_670_:
{
uint64_t v___x_680_; uint8_t v___x_681_; 
v___x_680_ = lean_uint64_shift_right(v___y_672_, v___y_675_);
v___x_681_ = lean_uint64_dec_eq(v___x_680_, v___y_677_);
if (v___x_681_ == 0)
{
uint64_t v___x_682_; 
v___x_682_ = lean_uint64_add(v___y_671_, v___y_675_);
v___y_660_ = v___y_674_;
v___y_661_ = v___y_673_;
v___y_662_ = v___y_679_;
v___y_663_ = v___y_676_;
v___y_664_ = v___y_678_;
v___y_665_ = v___y_677_;
v___y_666_ = v___x_682_;
goto v___jp_659_;
}
else
{
v___y_660_ = v___y_674_;
v___y_661_ = v___y_673_;
v___y_662_ = v___y_679_;
v___y_663_ = v___y_676_;
v___y_664_ = v___y_678_;
v___y_665_ = v___y_677_;
v___y_666_ = v___y_671_;
goto v___jp_659_;
}
}
v___jp_683_:
{
uint64_t v___x_691_; uint64_t v___x_692_; uint8_t v___x_693_; 
v___x_691_ = 16ULL;
v___x_692_ = lean_uint64_shift_right(v___y_686_, v___x_691_);
v___x_693_ = lean_uint64_dec_eq(v___x_692_, v___y_689_);
if (v___x_693_ == 0)
{
v___y_671_ = v___y_690_;
v___y_672_ = v___y_686_;
v___y_673_ = v___y_685_;
v___y_674_ = v___y_684_;
v___y_675_ = v___x_691_;
v___y_676_ = v___y_687_;
v___y_677_ = v___y_689_;
v___y_678_ = v___y_688_;
v___y_679_ = v___x_692_;
goto v___jp_670_;
}
else
{
v___y_671_ = v___y_690_;
v___y_672_ = v___y_686_;
v___y_673_ = v___y_685_;
v___y_674_ = v___y_684_;
v___y_675_ = v___x_691_;
v___y_676_ = v___y_687_;
v___y_677_ = v___y_689_;
v___y_678_ = v___y_688_;
v___y_679_ = v___y_686_;
goto v___jp_670_;
}
}
v___jp_694_:
{
uint64_t v___x_702_; uint64_t v___x_703_; uint8_t v___x_704_; 
v___x_702_ = lean_unbox_uint64(v___y_695_);
v___x_703_ = lean_uint64_shift_right(v___x_702_, v___y_697_);
v___x_704_ = lean_uint64_dec_eq(v___x_703_, v___y_699_);
if (v___x_704_ == 0)
{
v___y_684_ = v___y_696_;
v___y_685_ = v___y_695_;
v___y_686_ = v___y_701_;
v___y_687_ = v___y_698_;
v___y_688_ = v___y_700_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_697_;
goto v___jp_683_;
}
else
{
v___y_684_ = v___y_696_;
v___y_685_ = v___y_695_;
v___y_686_ = v___y_701_;
v___y_687_ = v___y_698_;
v___y_688_ = v___y_700_;
v___y_689_ = v___y_699_;
v___y_690_ = v___y_699_;
goto v___jp_683_;
}
}
v___jp_705_:
{
uint64_t v___x_709_; uint64_t v___x_710_; uint8_t v___x_711_; 
v___x_709_ = 0ULL;
v___x_710_ = lean_unbox_uint64(v_snd_708_);
v___x_711_ = lean_uint64_dec_eq(v___x_710_, v___x_709_);
if (v___x_711_ == 0)
{
uint64_t v___x_712_; uint64_t v___x_713_; uint64_t v___x_714_; uint64_t v___x_715_; uint64_t v___x_716_; uint8_t v___x_717_; 
v___x_712_ = 149ULL;
v___x_713_ = lean_uint64_add(v___y_706_, v___x_712_);
v___x_714_ = 32ULL;
v___x_715_ = lean_unbox_uint64(v_snd_708_);
v___x_716_ = lean_uint64_shift_right(v___x_715_, v___x_714_);
v___x_717_ = lean_uint64_dec_eq(v___x_716_, v___x_709_);
if (v___x_717_ == 0)
{
v___y_695_ = v_snd_708_;
v___y_696_ = v___x_713_;
v___y_697_ = v___x_714_;
v___y_698_ = v___x_712_;
v___y_699_ = v___x_709_;
v___y_700_ = v_fst_707_;
v___y_701_ = v___x_716_;
goto v___jp_694_;
}
else
{
uint64_t v___x_718_; 
v___x_718_ = lean_unbox_uint64(v_snd_708_);
v___y_695_ = v_snd_708_;
v___y_696_ = v___x_713_;
v___y_697_ = v___x_714_;
v___y_698_ = v___x_712_;
v___y_699_ = v___x_709_;
v___y_700_ = v_fst_707_;
v___y_701_ = v___x_718_;
goto v___jp_694_;
}
}
else
{
uint8_t v___x_719_; 
lean_dec(v_snd_708_);
v___x_719_ = lean_unbox(v_fst_707_);
lean_dec(v_fst_707_);
if (v___x_719_ == 0)
{
uint32_t v___x_720_; 
v___x_720_ = 0;
return v___x_720_;
}
else
{
uint32_t v___x_721_; 
v___x_721_ = 2147483648;
return v___x_721_;
}
}
}
v___jp_722_:
{
uint8_t v___x_729_; 
v___x_729_ = lean_uint64_dec_eq(v___y_727_, v___y_726_);
if (v___x_729_ == 0)
{
uint8_t v___x_730_; 
v___x_730_ = lean_uint64_dec_lt(v___y_727_, v___y_726_);
if (v___x_730_ == 0)
{
uint64_t v___x_731_; lean_object* v___x_732_; lean_object* v___x_733_; 
v___x_731_ = lean_uint64_sub(v___y_727_, v___y_726_);
v___x_732_ = lean_box(v___y_723_);
v___x_733_ = lean_box_uint64(v___x_731_);
v___y_706_ = v___y_725_;
v_fst_707_ = v___x_732_;
v_snd_708_ = v___x_733_;
goto v___jp_705_;
}
else
{
uint64_t v___x_734_; lean_object* v___x_735_; lean_object* v___x_736_; 
v___x_734_ = lean_uint64_sub(v___y_726_, v___y_727_);
v___x_735_ = lean_box(v___y_724_);
v___x_736_ = lean_box_uint64(v___x_734_);
v___y_706_ = v___y_725_;
v_fst_707_ = v___x_735_;
v_snd_708_ = v___x_736_;
goto v___jp_705_;
}
}
else
{
lean_object* v___x_737_; lean_object* v___x_738_; 
v___x_737_ = lean_box(v___y_728_);
v___x_738_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_706_ = v___y_725_;
v_fst_707_ = v___x_737_;
v_snd_708_ = v___x_738_;
goto v___jp_705_;
}
}
v___jp_739_:
{
if (v___y_745_ == 0)
{
v___y_723_ = v___y_740_;
v___y_724_ = v___y_741_;
v___y_725_ = v___y_742_;
v___y_726_ = v___y_743_;
v___y_727_ = v___y_744_;
v___y_728_ = v___y_745_;
goto v___jp_722_;
}
else
{
uint64_t v___x_746_; lean_object* v___x_747_; lean_object* v___x_748_; 
v___x_746_ = lean_uint64_add(v___y_744_, v___y_743_);
v___x_747_ = lean_box(v___y_740_);
v___x_748_ = lean_box_uint64(v___x_746_);
v___y_706_ = v___y_742_;
v_fst_707_ = v___x_747_;
v_snd_708_ = v___x_748_;
goto v___jp_705_;
}
}
v___jp_749_:
{
uint32_t v___x_753_; uint32_t v___x_754_; uint32_t v___x_755_; uint32_t v___x_756_; uint32_t v___x_757_; uint32_t v___x_758_; 
v___x_753_ = lean_uint32_land(v___y_751_, v___x_465_);
v___x_754_ = lean_uint32_shift_left(v___x_753_, v___x_463_);
v___x_755_ = lean_uint32_lor(v___y_752_, v___x_754_);
v___x_756_ = 8388607;
v___x_757_ = lean_uint32_land(v___y_750_, v___x_756_);
v___x_758_ = lean_uint32_lor(v___x_755_, v___x_757_);
return v___x_758_;
}
v___jp_759_:
{
uint8_t v___x_763_; 
v___x_763_ = lean_unbox(v___y_760_);
lean_dec(v___y_760_);
if (v___x_763_ == 0)
{
uint32_t v___x_764_; 
v___x_764_ = 0;
v___y_750_ = v___y_762_;
v___y_751_ = v___y_761_;
v___y_752_ = v___x_764_;
goto v___jp_749_;
}
else
{
uint32_t v___x_765_; 
v___x_765_ = 2147483648;
v___y_750_ = v___y_762_;
v___y_751_ = v___y_761_;
v___y_752_ = v___x_765_;
goto v___jp_749_;
}
}
v___jp_766_:
{
uint64_t v___x_771_; uint64_t v_encodedExponent_772_; uint32_t v___x_773_; uint64_t v___x_774_; uint8_t v___x_775_; 
v___x_771_ = 171ULL;
v_encodedExponent_772_ = lean_uint64_sub(v___y_768_, v___x_771_);
v___x_773_ = lean_uint64_to_uint32(v_encodedExponent_772_);
v___x_774_ = 8388608ULL;
v___x_775_ = lean_uint64_dec_lt(v___y_770_, v___x_774_);
if (v___x_775_ == 0)
{
uint64_t v___x_776_; uint32_t v___x_777_; 
v___x_776_ = lean_uint64_sub(v___y_770_, v___x_774_);
v___x_777_ = lean_uint64_to_uint32(v___x_776_);
v___y_760_ = v___y_767_;
v___y_761_ = v___x_773_;
v___y_762_ = v___x_777_;
goto v___jp_759_;
}
else
{
uint32_t v___x_778_; 
v___x_778_ = lean_uint64_to_uint32(v___y_769_);
v___y_760_ = v___y_767_;
v___y_761_ = v___x_773_;
v___y_762_ = v___x_778_;
goto v___jp_759_;
}
}
v___jp_779_:
{
uint64_t v___x_785_; uint8_t v___x_786_; 
v___x_785_ = 425ULL;
v___x_786_ = lean_uint64_dec_lt(v___x_785_, v___y_784_);
if (v___x_786_ == 0)
{
if (v___y_782_ == 0)
{
v___y_767_ = v___y_780_;
v___y_768_ = v___y_784_;
v___y_769_ = v___y_783_;
v___y_770_ = v___y_781_;
goto v___jp_766_;
}
else
{
uint64_t v___x_787_; 
v___x_787_ = 8388608ULL;
v___y_767_ = v___y_780_;
v___y_768_ = v___y_784_;
v___y_769_ = v___y_783_;
v___y_770_ = v___x_787_;
goto v___jp_766_;
}
}
else
{
uint8_t v___x_788_; 
v___x_788_ = lean_unbox(v___y_780_);
lean_dec(v___y_780_);
if (v___x_788_ == 0)
{
uint32_t v___x_789_; 
v___x_789_ = 2139095040;
return v___x_789_;
}
else
{
uint32_t v___x_790_; 
v___x_790_ = 4286578688;
return v___x_790_;
}
}
}
v___jp_791_:
{
uint64_t v___x_796_; uint8_t v_carry_797_; 
v___x_796_ = 16777216ULL;
v_carry_797_ = lean_uint64_dec_eq(v___y_795_, v___x_796_);
if (v_carry_797_ == 0)
{
v___y_780_ = v___y_792_;
v___y_781_ = v___y_795_;
v___y_782_ = v_carry_797_;
v___y_783_ = v___y_794_;
v___y_784_ = v___y_793_;
goto v___jp_779_;
}
else
{
uint64_t v___x_798_; uint64_t v___x_799_; 
v___x_798_ = 1ULL;
v___x_799_ = lean_uint64_add(v___y_793_, v___x_798_);
v___y_780_ = v___y_792_;
v___y_781_ = v___y_795_;
v___y_782_ = v_carry_797_;
v___y_783_ = v___y_794_;
v___y_784_ = v___x_799_;
goto v___jp_779_;
}
}
v___jp_800_:
{
uint64_t v_position_807_; uint64_t v___x_808_; uint8_t v___x_809_; 
v_position_807_ = lean_uint64_add(v___y_806_, v___y_804_);
v___x_808_ = 172ULL;
v___x_809_ = lean_uint64_dec_lt(v_position_807_, v___x_808_);
if (v___x_809_ == 0)
{
uint64_t v___x_810_; uint8_t v___x_811_; 
v___x_810_ = 23ULL;
v___x_811_ = lean_uint64_dec_lt(v___y_806_, v___x_810_);
if (v___x_811_ == 0)
{
uint64_t v___x_812_; uint8_t v___x_813_; 
v___x_812_ = lean_uint64_sub(v___y_806_, v___x_810_);
v___x_813_ = lean_uint64_dec_eq(v___x_812_, v___y_805_);
if (v___x_813_ == 0)
{
uint64_t v___x_814_; uint8_t v___x_815_; 
v___x_814_ = 64ULL;
v___x_815_ = lean_uint64_dec_lt(v___x_812_, v___x_814_);
if (v___x_815_ == 0)
{
uint8_t v___x_816_; 
v___x_816_ = lean_uint64_dec_eq(v___x_812_, v___x_814_);
if (v___x_816_ == 0)
{
lean_dec(v___y_802_);
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v___y_805_;
goto v___jp_791_;
}
else
{
uint64_t v___x_817_; uint64_t v___x_818_; uint8_t v___x_819_; 
v___x_817_ = 9223372036854775808ULL;
v___x_818_ = lean_unbox_uint64(v___y_802_);
lean_dec(v___y_802_);
v___x_819_ = lean_uint64_dec_lt(v___x_817_, v___x_818_);
if (v___x_819_ == 0)
{
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v___y_805_;
goto v___jp_791_;
}
else
{
uint64_t v___x_820_; 
v___x_820_ = 1ULL;
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v___x_820_;
goto v___jp_791_;
}
}
}
else
{
uint64_t v___x_821_; uint64_t v_quotient_822_; uint64_t v___x_823_; uint64_t v___x_824_; uint64_t v___x_825_; uint64_t v___x_826_; uint64_t v_remainder_827_; uint64_t v___x_828_; uint64_t v_half_829_; uint8_t v___x_830_; 
v___x_821_ = lean_unbox_uint64(v___y_802_);
v_quotient_822_ = lean_uint64_shift_right(v___x_821_, v___x_812_);
v___x_823_ = 1ULL;
v___x_824_ = lean_uint64_shift_left(v___x_823_, v___x_812_);
v___x_825_ = lean_uint64_sub(v___x_824_, v___x_823_);
v___x_826_ = lean_unbox_uint64(v___y_802_);
lean_dec(v___y_802_);
v_remainder_827_ = lean_uint64_land(v___x_826_, v___x_825_);
v___x_828_ = lean_uint64_sub(v___x_812_, v___x_823_);
v_half_829_ = lean_uint64_shift_left(v___x_823_, v___x_828_);
v___x_830_ = lean_uint64_dec_lt(v_remainder_827_, v_half_829_);
if (v___x_830_ == 0)
{
uint8_t v___x_831_; 
v___x_831_ = lean_uint64_dec_lt(v_half_829_, v_remainder_827_);
if (v___x_831_ == 0)
{
uint64_t v___x_832_; uint8_t v___x_833_; 
v___x_832_ = lean_uint64_land(v_quotient_822_, v___x_823_);
v___x_833_ = lean_uint64_dec_eq(v___x_832_, v___y_805_);
if (v___x_833_ == 0)
{
uint64_t v___x_834_; 
v___x_834_ = lean_uint64_add(v_quotient_822_, v___x_823_);
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v___x_834_;
goto v___jp_791_;
}
else
{
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v_quotient_822_;
goto v___jp_791_;
}
}
else
{
uint64_t v___x_835_; 
v___x_835_ = lean_uint64_add(v_quotient_822_, v___x_823_);
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v___x_835_;
goto v___jp_791_;
}
}
else
{
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v_quotient_822_;
goto v___jp_791_;
}
}
}
else
{
uint64_t v___x_836_; 
v___x_836_ = lean_unbox_uint64(v___y_802_);
lean_dec(v___y_802_);
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v___x_836_;
goto v___jp_791_;
}
}
else
{
uint64_t v___x_837_; uint64_t v___x_838_; uint64_t v___x_839_; 
v___x_837_ = lean_uint64_sub(v___x_810_, v___y_806_);
v___x_838_ = lean_unbox_uint64(v___y_802_);
lean_dec(v___y_802_);
v___x_839_ = lean_uint64_shift_left(v___x_838_, v___x_837_);
v___y_792_ = v___y_801_;
v___y_793_ = v_position_807_;
v___y_794_ = v___y_805_;
v___y_795_ = v___x_839_;
goto v___jp_791_;
}
}
else
{
uint8_t v___x_840_; 
v___x_840_ = lean_uint64_dec_lt(v___y_804_, v___y_803_);
if (v___x_840_ == 0)
{
uint64_t v___x_841_; uint64_t v___x_842_; uint64_t v___x_843_; 
v___x_841_ = lean_uint64_sub(v___y_804_, v___y_803_);
v___x_842_ = lean_unbox_uint64(v___y_802_);
lean_dec(v___y_802_);
v___x_843_ = lean_uint64_shift_left(v___x_842_, v___x_841_);
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v___x_843_;
goto v___jp_446_;
}
else
{
uint64_t v___x_844_; uint8_t v___x_845_; 
v___x_844_ = lean_uint64_sub(v___y_803_, v___y_804_);
v___x_845_ = lean_uint64_dec_eq(v___x_844_, v___y_805_);
if (v___x_845_ == 0)
{
uint64_t v___x_846_; uint8_t v___x_847_; 
v___x_846_ = 64ULL;
v___x_847_ = lean_uint64_dec_lt(v___x_844_, v___x_846_);
if (v___x_847_ == 0)
{
uint8_t v___x_848_; 
v___x_848_ = lean_uint64_dec_eq(v___x_844_, v___x_846_);
if (v___x_848_ == 0)
{
lean_dec(v___y_802_);
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v___y_805_;
goto v___jp_446_;
}
else
{
uint64_t v___x_849_; uint64_t v___x_850_; uint8_t v___x_851_; 
v___x_849_ = 9223372036854775808ULL;
v___x_850_ = lean_unbox_uint64(v___y_802_);
lean_dec(v___y_802_);
v___x_851_ = lean_uint64_dec_lt(v___x_849_, v___x_850_);
if (v___x_851_ == 0)
{
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v___y_805_;
goto v___jp_446_;
}
else
{
uint64_t v___x_852_; 
v___x_852_ = 1ULL;
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v___x_852_;
goto v___jp_446_;
}
}
}
else
{
uint64_t v___x_853_; uint64_t v_quotient_854_; uint64_t v___x_855_; uint64_t v___x_856_; uint64_t v___x_857_; uint64_t v___x_858_; uint64_t v_remainder_859_; uint64_t v___x_860_; uint64_t v_half_861_; uint8_t v___x_862_; 
v___x_853_ = lean_unbox_uint64(v___y_802_);
v_quotient_854_ = lean_uint64_shift_right(v___x_853_, v___x_844_);
v___x_855_ = 1ULL;
v___x_856_ = lean_uint64_shift_left(v___x_855_, v___x_844_);
v___x_857_ = lean_uint64_sub(v___x_856_, v___x_855_);
v___x_858_ = lean_unbox_uint64(v___y_802_);
lean_dec(v___y_802_);
v_remainder_859_ = lean_uint64_land(v___x_858_, v___x_857_);
v___x_860_ = lean_uint64_sub(v___x_844_, v___x_855_);
v_half_861_ = lean_uint64_shift_left(v___x_855_, v___x_860_);
v___x_862_ = lean_uint64_dec_lt(v_remainder_859_, v_half_861_);
if (v___x_862_ == 0)
{
uint8_t v___x_863_; 
v___x_863_ = lean_uint64_dec_lt(v_half_861_, v_remainder_859_);
if (v___x_863_ == 0)
{
uint64_t v___x_864_; uint8_t v___x_865_; 
v___x_864_ = lean_uint64_land(v_quotient_854_, v___x_855_);
v___x_865_ = lean_uint64_dec_eq(v___x_864_, v___y_805_);
if (v___x_865_ == 0)
{
uint64_t v___x_866_; 
v___x_866_ = lean_uint64_add(v_quotient_854_, v___x_855_);
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v___x_866_;
goto v___jp_446_;
}
else
{
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v_quotient_854_;
goto v___jp_446_;
}
}
else
{
uint64_t v___x_867_; 
v___x_867_ = lean_uint64_add(v_quotient_854_, v___x_855_);
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v___x_867_;
goto v___jp_446_;
}
}
else
{
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v_quotient_854_;
goto v___jp_446_;
}
}
}
else
{
uint64_t v___x_868_; 
v___x_868_ = lean_unbox_uint64(v___y_802_);
lean_dec(v___y_802_);
v___y_447_ = v___y_801_;
v___y_448_ = v___y_805_;
v___y_449_ = v___x_868_;
goto v___jp_446_;
}
}
}
}
v___jp_869_:
{
uint64_t v___x_877_; uint64_t v___x_878_; uint8_t v___x_879_; 
v___x_877_ = 1ULL;
v___x_878_ = lean_uint64_shift_right(v___y_873_, v___x_877_);
v___x_879_ = lean_uint64_dec_eq(v___x_878_, v___y_875_);
if (v___x_879_ == 0)
{
uint64_t v___x_880_; 
v___x_880_ = lean_uint64_add(v___y_876_, v___x_877_);
v___y_801_ = v___y_870_;
v___y_802_ = v___y_871_;
v___y_803_ = v___y_872_;
v___y_804_ = v___y_874_;
v___y_805_ = v___y_875_;
v___y_806_ = v___x_880_;
goto v___jp_800_;
}
else
{
v___y_801_ = v___y_870_;
v___y_802_ = v___y_871_;
v___y_803_ = v___y_872_;
v___y_804_ = v___y_874_;
v___y_805_ = v___y_875_;
v___y_806_ = v___y_876_;
goto v___jp_800_;
}
}
v___jp_881_:
{
uint64_t v___x_891_; uint8_t v___x_892_; 
v___x_891_ = lean_uint64_shift_right(v___y_888_, v___y_889_);
v___x_892_ = lean_uint64_dec_eq(v___x_891_, v___y_887_);
if (v___x_892_ == 0)
{
uint64_t v___x_893_; 
v___x_893_ = lean_uint64_add(v___y_883_, v___y_889_);
v___y_870_ = v___y_882_;
v___y_871_ = v___y_884_;
v___y_872_ = v___y_885_;
v___y_873_ = v___y_890_;
v___y_874_ = v___y_886_;
v___y_875_ = v___y_887_;
v___y_876_ = v___x_893_;
goto v___jp_869_;
}
else
{
v___y_870_ = v___y_882_;
v___y_871_ = v___y_884_;
v___y_872_ = v___y_885_;
v___y_873_ = v___y_890_;
v___y_874_ = v___y_886_;
v___y_875_ = v___y_887_;
v___y_876_ = v___y_883_;
goto v___jp_869_;
}
}
v___jp_894_:
{
uint64_t v___x_902_; uint64_t v___x_903_; uint8_t v___x_904_; 
v___x_902_ = 2ULL;
v___x_903_ = lean_uint64_shift_right(v___y_900_, v___x_902_);
v___x_904_ = lean_uint64_dec_eq(v___x_903_, v___y_899_);
if (v___x_904_ == 0)
{
v___y_882_ = v___y_895_;
v___y_883_ = v___y_901_;
v___y_884_ = v___y_896_;
v___y_885_ = v___y_897_;
v___y_886_ = v___y_898_;
v___y_887_ = v___y_899_;
v___y_888_ = v___y_900_;
v___y_889_ = v___x_902_;
v___y_890_ = v___x_903_;
goto v___jp_881_;
}
else
{
v___y_882_ = v___y_895_;
v___y_883_ = v___y_901_;
v___y_884_ = v___y_896_;
v___y_885_ = v___y_897_;
v___y_886_ = v___y_898_;
v___y_887_ = v___y_899_;
v___y_888_ = v___y_900_;
v___y_889_ = v___x_902_;
v___y_890_ = v___y_900_;
goto v___jp_881_;
}
}
v___jp_905_:
{
uint64_t v___x_915_; uint8_t v___x_916_; 
v___x_915_ = lean_uint64_shift_right(v___y_910_, v___y_911_);
v___x_916_ = lean_uint64_dec_eq(v___x_915_, v___y_913_);
if (v___x_916_ == 0)
{
uint64_t v___x_917_; 
v___x_917_ = lean_uint64_add(v___y_908_, v___y_911_);
v___y_895_ = v___y_906_;
v___y_896_ = v___y_907_;
v___y_897_ = v___y_909_;
v___y_898_ = v___y_912_;
v___y_899_ = v___y_913_;
v___y_900_ = v___y_914_;
v___y_901_ = v___x_917_;
goto v___jp_894_;
}
else
{
v___y_895_ = v___y_906_;
v___y_896_ = v___y_907_;
v___y_897_ = v___y_909_;
v___y_898_ = v___y_912_;
v___y_899_ = v___y_913_;
v___y_900_ = v___y_914_;
v___y_901_ = v___y_908_;
goto v___jp_894_;
}
}
v___jp_918_:
{
uint64_t v___x_926_; uint64_t v___x_927_; uint8_t v___x_928_; 
v___x_926_ = 4ULL;
v___x_927_ = lean_uint64_shift_right(v___y_922_, v___x_926_);
v___x_928_ = lean_uint64_dec_eq(v___x_927_, v___y_924_);
if (v___x_928_ == 0)
{
v___y_906_ = v___y_919_;
v___y_907_ = v___y_920_;
v___y_908_ = v___y_925_;
v___y_909_ = v___y_921_;
v___y_910_ = v___y_922_;
v___y_911_ = v___x_926_;
v___y_912_ = v___y_923_;
v___y_913_ = v___y_924_;
v___y_914_ = v___x_927_;
goto v___jp_905_;
}
else
{
v___y_906_ = v___y_919_;
v___y_907_ = v___y_920_;
v___y_908_ = v___y_925_;
v___y_909_ = v___y_921_;
v___y_910_ = v___y_922_;
v___y_911_ = v___x_926_;
v___y_912_ = v___y_923_;
v___y_913_ = v___y_924_;
v___y_914_ = v___y_922_;
goto v___jp_905_;
}
}
v___jp_929_:
{
uint64_t v___x_939_; uint8_t v___x_940_; 
v___x_939_ = lean_uint64_shift_right(v___y_931_, v___y_937_);
v___x_940_ = lean_uint64_dec_eq(v___x_939_, v___y_936_);
if (v___x_940_ == 0)
{
uint64_t v___x_941_; 
v___x_941_ = lean_uint64_add(v___y_933_, v___y_937_);
v___y_919_ = v___y_930_;
v___y_920_ = v___y_932_;
v___y_921_ = v___y_934_;
v___y_922_ = v___y_938_;
v___y_923_ = v___y_935_;
v___y_924_ = v___y_936_;
v___y_925_ = v___x_941_;
goto v___jp_918_;
}
else
{
v___y_919_ = v___y_930_;
v___y_920_ = v___y_932_;
v___y_921_ = v___y_934_;
v___y_922_ = v___y_938_;
v___y_923_ = v___y_935_;
v___y_924_ = v___y_936_;
v___y_925_ = v___y_933_;
goto v___jp_918_;
}
}
v___jp_942_:
{
uint64_t v___x_950_; uint64_t v___x_951_; uint8_t v___x_952_; 
v___x_950_ = 8ULL;
v___x_951_ = lean_uint64_shift_right(v___y_945_, v___x_950_);
v___x_952_ = lean_uint64_dec_eq(v___x_951_, v___y_948_);
if (v___x_952_ == 0)
{
v___y_930_ = v___y_943_;
v___y_931_ = v___y_945_;
v___y_932_ = v___y_944_;
v___y_933_ = v___y_949_;
v___y_934_ = v___y_946_;
v___y_935_ = v___y_947_;
v___y_936_ = v___y_948_;
v___y_937_ = v___x_950_;
v___y_938_ = v___x_951_;
goto v___jp_929_;
}
else
{
v___y_930_ = v___y_943_;
v___y_931_ = v___y_945_;
v___y_932_ = v___y_944_;
v___y_933_ = v___y_949_;
v___y_934_ = v___y_946_;
v___y_935_ = v___y_947_;
v___y_936_ = v___y_948_;
v___y_937_ = v___x_950_;
v___y_938_ = v___y_945_;
goto v___jp_929_;
}
}
v___jp_953_:
{
uint64_t v___x_963_; uint8_t v___x_964_; 
v___x_963_ = lean_uint64_shift_right(v___y_961_, v___y_959_);
v___x_964_ = lean_uint64_dec_eq(v___x_963_, v___y_960_);
if (v___x_964_ == 0)
{
uint64_t v___x_965_; 
v___x_965_ = lean_uint64_add(v___y_958_, v___y_959_);
v___y_943_ = v___y_954_;
v___y_944_ = v___y_955_;
v___y_945_ = v___y_962_;
v___y_946_ = v___y_956_;
v___y_947_ = v___y_957_;
v___y_948_ = v___y_960_;
v___y_949_ = v___x_965_;
goto v___jp_942_;
}
else
{
v___y_943_ = v___y_954_;
v___y_944_ = v___y_955_;
v___y_945_ = v___y_962_;
v___y_946_ = v___y_956_;
v___y_947_ = v___y_957_;
v___y_948_ = v___y_960_;
v___y_949_ = v___y_958_;
goto v___jp_942_;
}
}
v___jp_966_:
{
uint64_t v___x_974_; uint64_t v___x_975_; uint8_t v___x_976_; 
v___x_974_ = 16ULL;
v___x_975_ = lean_uint64_shift_right(v___y_972_, v___x_974_);
v___x_976_ = lean_uint64_dec_eq(v___x_975_, v___y_971_);
if (v___x_976_ == 0)
{
v___y_954_ = v___y_967_;
v___y_955_ = v___y_968_;
v___y_956_ = v___y_969_;
v___y_957_ = v___y_970_;
v___y_958_ = v___y_973_;
v___y_959_ = v___x_974_;
v___y_960_ = v___y_971_;
v___y_961_ = v___y_972_;
v___y_962_ = v___x_975_;
goto v___jp_953_;
}
else
{
v___y_954_ = v___y_967_;
v___y_955_ = v___y_968_;
v___y_956_ = v___y_969_;
v___y_957_ = v___y_970_;
v___y_958_ = v___y_973_;
v___y_959_ = v___x_974_;
v___y_960_ = v___y_971_;
v___y_961_ = v___y_972_;
v___y_962_ = v___y_972_;
goto v___jp_953_;
}
}
v___jp_977_:
{
uint64_t v___x_985_; uint64_t v___x_986_; uint8_t v___x_987_; 
v___x_985_ = lean_unbox_uint64(v___y_979_);
v___x_986_ = lean_uint64_shift_right(v___x_985_, v___y_982_);
v___x_987_ = lean_uint64_dec_eq(v___x_986_, v___y_983_);
if (v___x_987_ == 0)
{
v___y_967_ = v___y_978_;
v___y_968_ = v___y_979_;
v___y_969_ = v___y_980_;
v___y_970_ = v___y_981_;
v___y_971_ = v___y_983_;
v___y_972_ = v___y_984_;
v___y_973_ = v___y_982_;
goto v___jp_966_;
}
else
{
v___y_967_ = v___y_978_;
v___y_968_ = v___y_979_;
v___y_969_ = v___y_980_;
v___y_970_ = v___y_981_;
v___y_971_ = v___y_983_;
v___y_972_ = v___y_984_;
v___y_973_ = v___y_983_;
goto v___jp_966_;
}
}
v___jp_988_:
{
uint64_t v___x_992_; uint64_t v___x_993_; uint8_t v___x_994_; 
v___x_992_ = 0ULL;
v___x_993_ = lean_unbox_uint64(v_snd_991_);
v___x_994_ = lean_uint64_dec_eq(v___x_993_, v___x_992_);
if (v___x_994_ == 0)
{
uint64_t v___x_995_; uint64_t v___x_996_; uint64_t v___x_997_; uint64_t v___x_998_; uint64_t v___x_999_; uint8_t v___x_1000_; 
v___x_995_ = 149ULL;
v___x_996_ = lean_uint64_add(v___y_989_, v___x_995_);
v___x_997_ = 32ULL;
v___x_998_ = lean_unbox_uint64(v_snd_991_);
v___x_999_ = lean_uint64_shift_right(v___x_998_, v___x_997_);
v___x_1000_ = lean_uint64_dec_eq(v___x_999_, v___x_992_);
if (v___x_1000_ == 0)
{
v___y_978_ = v_fst_990_;
v___y_979_ = v_snd_991_;
v___y_980_ = v___x_995_;
v___y_981_ = v___x_996_;
v___y_982_ = v___x_997_;
v___y_983_ = v___x_992_;
v___y_984_ = v___x_999_;
goto v___jp_977_;
}
else
{
uint64_t v___x_1001_; 
v___x_1001_ = lean_unbox_uint64(v_snd_991_);
v___y_978_ = v_fst_990_;
v___y_979_ = v_snd_991_;
v___y_980_ = v___x_995_;
v___y_981_ = v___x_996_;
v___y_982_ = v___x_997_;
v___y_983_ = v___x_992_;
v___y_984_ = v___x_1001_;
goto v___jp_977_;
}
}
else
{
uint8_t v___x_1002_; 
lean_dec(v_snd_991_);
v___x_1002_ = lean_unbox(v_fst_990_);
lean_dec(v_fst_990_);
if (v___x_1002_ == 0)
{
uint32_t v___x_1003_; 
v___x_1003_ = 0;
return v___x_1003_;
}
else
{
uint32_t v___x_1004_; 
v___x_1004_ = 2147483648;
return v___x_1004_;
}
}
}
v___jp_1005_:
{
uint8_t v___x_1012_; 
v___x_1012_ = lean_uint64_dec_eq(v___y_1009_, v___y_1010_);
if (v___x_1012_ == 0)
{
uint8_t v___x_1013_; 
v___x_1013_ = lean_uint64_dec_lt(v___y_1009_, v___y_1010_);
if (v___x_1013_ == 0)
{
uint64_t v___x_1014_; lean_object* v___x_1015_; lean_object* v___x_1016_; 
v___x_1014_ = lean_uint64_sub(v___y_1009_, v___y_1010_);
v___x_1015_ = lean_box(v___y_1007_);
v___x_1016_ = lean_box_uint64(v___x_1014_);
v___y_989_ = v___y_1006_;
v_fst_990_ = v___x_1015_;
v_snd_991_ = v___x_1016_;
goto v___jp_988_;
}
else
{
uint64_t v___x_1017_; lean_object* v___x_1018_; lean_object* v___x_1019_; 
v___x_1017_ = lean_uint64_sub(v___y_1010_, v___y_1009_);
v___x_1018_ = lean_box(v___y_1008_);
v___x_1019_ = lean_box_uint64(v___x_1017_);
v___y_989_ = v___y_1006_;
v_fst_990_ = v___x_1018_;
v_snd_991_ = v___x_1019_;
goto v___jp_988_;
}
}
else
{
lean_object* v___x_1020_; lean_object* v___x_1021_; 
v___x_1020_ = lean_box(v___y_1011_);
v___x_1021_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_989_ = v___y_1006_;
v_fst_990_ = v___x_1020_;
v_snd_991_ = v___x_1021_;
goto v___jp_988_;
}
}
v___jp_1022_:
{
if (v___y_1028_ == 0)
{
v___y_1006_ = v___y_1024_;
v___y_1007_ = v___y_1023_;
v___y_1008_ = v___y_1025_;
v___y_1009_ = v___y_1026_;
v___y_1010_ = v___y_1027_;
v___y_1011_ = v___y_1028_;
goto v___jp_1005_;
}
else
{
uint64_t v___x_1029_; lean_object* v___x_1030_; lean_object* v___x_1031_; 
v___x_1029_ = lean_uint64_add(v___y_1026_, v___y_1027_);
v___x_1030_ = lean_box(v___y_1023_);
v___x_1031_ = lean_box_uint64(v___x_1029_);
v___y_989_ = v___y_1024_;
v_fst_990_ = v___x_1030_;
v_snd_991_ = v___x_1031_;
goto v___jp_988_;
}
}
v___jp_1032_:
{
uint8_t v___x_1039_; 
v___x_1039_ = lean_uint64_dec_le(v___y_1035_, v___y_1038_);
if (v___x_1039_ == 0)
{
uint64_t v_shift_1040_; uint64_t v___x_1041_; uint8_t v___x_1042_; 
v_shift_1040_ = lean_uint64_sub(v___y_1035_, v___y_1038_);
v___x_1041_ = 39ULL;
v___x_1042_ = lean_uint64_dec_le(v_shift_1040_, v___x_1041_);
if (v___x_1042_ == 0)
{
return v_xBits_407_;
}
else
{
uint64_t v___x_1043_; 
v___x_1043_ = lean_uint64_shift_left(v___y_1037_, v_shift_1040_);
if (v___y_1033_ == 0)
{
if (v___y_1034_ == 0)
{
v___y_1023_ = v___y_1033_;
v___y_1024_ = v___y_1038_;
v___y_1025_ = v___y_1034_;
v___y_1026_ = v___x_1043_;
v___y_1027_ = v___y_1036_;
v___y_1028_ = v___x_1042_;
goto v___jp_1022_;
}
else
{
v___y_1006_ = v___y_1038_;
v___y_1007_ = v___y_1033_;
v___y_1008_ = v___y_1034_;
v___y_1009_ = v___x_1043_;
v___y_1010_ = v___y_1036_;
v___y_1011_ = v___y_1033_;
goto v___jp_1005_;
}
}
else
{
v___y_1023_ = v___y_1033_;
v___y_1024_ = v___y_1038_;
v___y_1025_ = v___y_1034_;
v___y_1026_ = v___x_1043_;
v___y_1027_ = v___y_1036_;
v___y_1028_ = v___y_1034_;
goto v___jp_1022_;
}
}
}
else
{
uint64_t v_shift_1044_; uint64_t v___x_1045_; uint8_t v___x_1046_; 
v_shift_1044_ = lean_uint64_sub(v___y_1038_, v___y_1035_);
v___x_1045_ = 39ULL;
v___x_1046_ = lean_uint64_dec_le(v_shift_1044_, v___x_1045_);
if (v___x_1046_ == 0)
{
return v_yBits_408_;
}
else
{
uint64_t v___x_1047_; 
v___x_1047_ = lean_uint64_shift_left(v___y_1036_, v_shift_1044_);
if (v___y_1033_ == 0)
{
if (v___y_1034_ == 0)
{
v___y_740_ = v___y_1033_;
v___y_741_ = v___y_1034_;
v___y_742_ = v___y_1035_;
v___y_743_ = v___x_1047_;
v___y_744_ = v___y_1037_;
v___y_745_ = v___x_1046_;
goto v___jp_739_;
}
else
{
v___y_723_ = v___y_1033_;
v___y_724_ = v___y_1034_;
v___y_725_ = v___y_1035_;
v___y_726_ = v___x_1047_;
v___y_727_ = v___y_1037_;
v___y_728_ = v___y_1033_;
goto v___jp_722_;
}
}
else
{
v___y_740_ = v___y_1033_;
v___y_741_ = v___y_1034_;
v___y_742_ = v___y_1035_;
v___y_743_ = v___x_1047_;
v___y_744_ = v___y_1037_;
v___y_745_ = v___y_1034_;
goto v___jp_739_;
}
}
}
}
v___jp_1051_:
{
uint64_t v___x_1057_; uint64_t v___x_1058_; uint8_t v___x_1059_; 
v___x_1057_ = lean_uint32_to_uint64(v_yExponent_1050_);
v___x_1058_ = 0ULL;
v___x_1059_ = lean_uint64_dec_eq(v___x_1057_, v___x_1058_);
if (v___x_1059_ == 0)
{
uint64_t v___x_1060_; uint64_t v___x_1061_; 
v___x_1060_ = 1ULL;
v___x_1061_ = lean_uint64_sub(v___x_1057_, v___x_1060_);
v___y_1033_ = v___y_1052_;
v___y_1034_ = v___y_1053_;
v___y_1035_ = v___y_1056_;
v___y_1036_ = v___y_1054_;
v___y_1037_ = v___y_1055_;
v___y_1038_ = v___x_1061_;
goto v___jp_1032_;
}
else
{
v___y_1033_ = v___y_1052_;
v___y_1034_ = v___y_1053_;
v___y_1035_ = v___y_1056_;
v___y_1036_ = v___y_1054_;
v___y_1037_ = v___y_1055_;
v___y_1038_ = v___x_1058_;
goto v___jp_1032_;
}
}
v___jp_1062_:
{
uint64_t v___x_1067_; uint64_t v___x_1068_; uint8_t v___x_1069_; 
v___x_1067_ = lean_uint32_to_uint64(v_xExponent_1048_);
v___x_1068_ = 0ULL;
v___x_1069_ = lean_uint64_dec_eq(v___x_1067_, v___x_1068_);
if (v___x_1069_ == 0)
{
uint64_t v___x_1070_; uint64_t v___x_1071_; 
v___x_1070_ = 1ULL;
v___x_1071_ = lean_uint64_sub(v___x_1067_, v___x_1070_);
v___y_1052_ = v___y_1063_;
v___y_1053_ = v___y_1064_;
v___y_1054_ = v___y_1066_;
v___y_1055_ = v___y_1065_;
v___y_1056_ = v___x_1071_;
goto v___jp_1051_;
}
else
{
v___y_1052_ = v___y_1063_;
v___y_1053_ = v___y_1064_;
v___y_1054_ = v___y_1066_;
v___y_1055_ = v___y_1065_;
v___y_1056_ = v___x_1068_;
goto v___jp_1051_;
}
}
v___jp_1072_:
{
uint32_t v___x_1076_; uint32_t v___x_1077_; uint32_t v___x_1078_; uint8_t v___x_1079_; 
v___x_1076_ = 8388607;
v___x_1077_ = lean_uint32_land(v_yBits_408_, v___x_1076_);
v___x_1078_ = 0;
v___x_1079_ = lean_uint32_dec_eq(v_yExponent_1050_, v___x_1078_);
if (v___x_1079_ == 0)
{
uint64_t v___x_1080_; uint64_t v___x_1081_; uint64_t v___x_1082_; 
v___x_1080_ = lean_uint32_to_uint64(v___x_1077_);
v___x_1081_ = 8388608ULL;
v___x_1082_ = lean_uint64_lor(v___x_1080_, v___x_1081_);
v___y_1063_ = v___y_1073_;
v___y_1064_ = v___y_1074_;
v___y_1065_ = v___y_1075_;
v___y_1066_ = v___x_1082_;
goto v___jp_1062_;
}
else
{
uint64_t v___x_1083_; 
v___x_1083_ = lean_uint32_to_uint64(v___x_1077_);
v___y_1063_ = v___y_1073_;
v___y_1064_ = v___y_1074_;
v___y_1065_ = v___y_1075_;
v___y_1066_ = v___x_1083_;
goto v___jp_1062_;
}
}
v___jp_1084_:
{
uint32_t v___x_1087_; uint32_t v___x_1088_; uint32_t v___x_1089_; uint8_t v___x_1090_; 
v___x_1087_ = 8388607;
v___x_1088_ = lean_uint32_land(v_xBits_407_, v___x_1087_);
v___x_1089_ = 0;
v___x_1090_ = lean_uint32_dec_eq(v_xExponent_1048_, v___x_1089_);
if (v___x_1090_ == 0)
{
uint64_t v___x_1091_; uint64_t v___x_1092_; uint64_t v___x_1093_; 
v___x_1091_ = lean_uint32_to_uint64(v___x_1088_);
v___x_1092_ = 8388608ULL;
v___x_1093_ = lean_uint64_lor(v___x_1091_, v___x_1092_);
v___y_1073_ = v___y_1085_;
v___y_1074_ = v___y_1086_;
v___y_1075_ = v___x_1093_;
goto v___jp_1072_;
}
else
{
uint64_t v___x_1094_; 
v___x_1094_ = lean_uint32_to_uint64(v___x_1088_);
v___y_1073_ = v___y_1085_;
v___y_1074_ = v___y_1086_;
v___y_1075_ = v___x_1094_;
goto v___jp_1072_;
}
}
v___jp_1095_:
{
uint32_t v___x_1097_; uint32_t v___x_1098_; uint32_t v___x_1099_; uint8_t v___x_1100_; 
v___x_1097_ = 2147483648;
v___x_1098_ = lean_uint32_land(v_yBits_408_, v___x_1097_);
v___x_1099_ = 0;
v___x_1100_ = lean_uint32_dec_eq(v___x_1098_, v___x_1099_);
if (v___x_1100_ == 0)
{
uint8_t v___x_1101_; 
v___x_1101_ = 1;
v___y_1085_ = v___y_1096_;
v___y_1086_ = v___x_1101_;
goto v___jp_1084_;
}
else
{
uint8_t v___x_1102_; 
v___x_1102_ = 0;
v___y_1085_ = v___y_1096_;
v___y_1086_ = v___x_1102_;
goto v___jp_1084_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_core___boxed(lean_object* v_xBits_1109_, lean_object* v_yBits_1110_){
_start:
{
uint32_t v_xBits_boxed_1111_; uint32_t v_yBits_boxed_1112_; uint32_t v_res_1113_; lean_object* v_r_1114_; 
v_xBits_boxed_1111_ = lean_unbox_uint32(v_xBits_1109_);
lean_dec(v_xBits_1109_);
v_yBits_boxed_1112_ = lean_unbox_uint32(v_yBits_1110_);
lean_dec(v_yBits_1110_);
v_res_1113_ = lp_competition_Submission_TunedAdd_core(v_xBits_boxed_1111_, v_yBits_boxed_1112_);
v_r_1114_ = lean_box_uint32(v_res_1113_);
return v_r_1114_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_sp1(uint32_t v_a_1115_){
_start:
{
uint32_t v___x_1116_; uint32_t v___x_1117_; uint32_t v___x_1118_; uint32_t v___x_1119_; uint8_t v___x_1120_; 
v___x_1116_ = 4278190079;
v___x_1117_ = 1;
v___x_1118_ = lean_uint32_shift_left(v_a_1115_, v___x_1117_);
v___x_1119_ = lean_uint32_sub(v___x_1118_, v___x_1117_);
v___x_1120_ = lean_uint32_dec_le(v___x_1116_, v___x_1119_);
return v___x_1120_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sp1___boxed(lean_object* v_a_1121_){
_start:
{
uint32_t v_a_boxed_1122_; uint8_t v_res_1123_; lean_object* v_r_1124_; 
v_a_boxed_1122_ = lean_unbox_uint32(v_a_1121_);
lean_dec(v_a_1121_);
v_res_1123_ = lp_competition_Submission_TunedAdd_sp1(v_a_boxed_1122_);
v_r_1124_ = lean_box(v_res_1123_);
return v_r_1124_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_special(uint32_t v_a_1125_, uint32_t v_b_1126_){
_start:
{
uint32_t v___x_1127_; uint32_t v___x_1128_; uint32_t v___x_1129_; uint32_t v___x_1130_; uint8_t v___x_1131_; 
v___x_1127_ = 4278190079;
v___x_1128_ = 1;
v___x_1129_ = lean_uint32_shift_left(v_a_1125_, v___x_1128_);
v___x_1130_ = lean_uint32_sub(v___x_1129_, v___x_1128_);
v___x_1131_ = lean_uint32_dec_le(v___x_1127_, v___x_1130_);
if (v___x_1131_ == 0)
{
uint32_t v___x_1132_; uint32_t v___x_1133_; uint8_t v___x_1134_; 
v___x_1132_ = lean_uint32_shift_left(v_b_1126_, v___x_1128_);
v___x_1133_ = lean_uint32_sub(v___x_1132_, v___x_1128_);
v___x_1134_ = lean_uint32_dec_le(v___x_1127_, v___x_1133_);
return v___x_1134_;
}
else
{
return v___x_1131_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_special___boxed(lean_object* v_a_1135_, lean_object* v_b_1136_){
_start:
{
uint32_t v_a_boxed_1137_; uint32_t v_b_boxed_1138_; uint8_t v_res_1139_; lean_object* v_r_1140_; 
v_a_boxed_1137_ = lean_unbox_uint32(v_a_1135_);
lean_dec(v_a_1135_);
v_b_boxed_1138_ = lean_unbox_uint32(v_b_1136_);
lean_dec(v_b_1136_);
v_res_1139_ = lp_competition_Submission_TunedAdd_special(v_a_boxed_1137_, v_b_boxed_1138_);
v_r_1140_ = lean_box(v_res_1139_);
return v_r_1140_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_ofBits(uint32_t v_w_1141_){
_start:
{
return v_w_1141_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_ofBits___boxed(lean_object* v_w_1142_){
_start:
{
uint32_t v_w_boxed_1143_; uint32_t v_res_1144_; lean_object* v_r_1145_; 
v_w_boxed_1143_ = lean_unbox_uint32(v_w_1142_);
lean_dec(v_w_1142_);
v_res_1144_ = lp_competition_Submission_TunedAdd_ofBits(v_w_boxed_1143_);
v_r_1145_ = lean_box_uint32(v_res_1144_);
return v_r_1145_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_add(uint32_t v_x_1151_, uint32_t v_y_1152_){
_start:
{
uint32_t v___y_1154_; uint32_t v___y_1158_; uint32_t v___y_1162_; uint32_t v___y_1163_; uint64_t v___y_1168_; lean_object* v___y_1169_; uint64_t v___y_1170_; uint32_t v___y_1185_; uint32_t v___y_1186_; uint32_t v___y_1187_; uint32_t v___y_1188_; uint32_t v___y_1189_; uint32_t v___y_1197_; uint32_t v___y_1198_; uint32_t v___y_1199_; lean_object* v___y_1200_; uint32_t v___y_1201_; uint32_t v___y_1206_; uint64_t v___y_1207_; uint32_t v___y_1208_; uint64_t v___y_1209_; lean_object* v___y_1210_; uint64_t v___y_1211_; uint32_t v___y_1221_; uint8_t v___y_1222_; uint32_t v___y_1223_; uint64_t v___y_1224_; uint64_t v___y_1225_; lean_object* v___y_1226_; uint64_t v___y_1227_; uint32_t v___y_1235_; uint64_t v___y_1236_; uint32_t v___y_1237_; uint64_t v___y_1238_; lean_object* v___y_1239_; uint64_t v___y_1240_; uint64_t v___y_1246_; uint32_t v___y_1247_; lean_object* v___y_1248_; uint32_t v___y_1249_; uint64_t v___y_1250_; uint64_t v___y_1251_; lean_object* v___y_1252_; uint64_t v___y_1253_; uint64_t v___y_1317_; uint32_t v___y_1318_; lean_object* v___y_1319_; uint64_t v___y_1320_; uint32_t v___y_1321_; uint64_t v___y_1322_; uint64_t v___y_1323_; lean_object* v___y_1324_; uint64_t v___y_1325_; uint64_t v___y_1331_; uint32_t v___y_1332_; lean_object* v___y_1333_; uint64_t v___y_1334_; uint64_t v___y_1335_; uint32_t v___y_1336_; uint64_t v___y_1337_; uint64_t v___y_1338_; uint64_t v___y_1339_; lean_object* v___y_1340_; uint64_t v___y_1341_; uint64_t v___y_1346_; uint32_t v___y_1347_; lean_object* v___y_1348_; uint64_t v___y_1349_; uint32_t v___y_1350_; uint64_t v___y_1351_; uint64_t v___y_1352_; lean_object* v___y_1353_; uint64_t v___y_1354_; uint64_t v___y_1359_; uint64_t v___y_1360_; uint32_t v___y_1361_; lean_object* v___y_1362_; uint64_t v___y_1363_; uint64_t v___y_1364_; uint32_t v___y_1365_; uint64_t v___y_1366_; uint64_t v___y_1367_; lean_object* v___y_1368_; uint64_t v___y_1369_; uint64_t v___y_1374_; uint64_t v___y_1375_; uint32_t v___y_1376_; lean_object* v___y_1377_; uint32_t v___y_1378_; uint64_t v___y_1379_; uint64_t v___y_1380_; lean_object* v___y_1381_; uint64_t v___y_1382_; uint64_t v___y_1387_; uint32_t v___y_1388_; uint64_t v___y_1389_; lean_object* v___y_1390_; uint64_t v___y_1391_; uint32_t v___y_1392_; uint64_t v___y_1393_; uint64_t v___y_1394_; uint64_t v___y_1395_; lean_object* v___y_1396_; uint64_t v___y_1397_; uint64_t v___y_1402_; uint32_t v___y_1403_; lean_object* v___y_1404_; uint32_t v___y_1405_; uint64_t v___y_1406_; uint64_t v___y_1407_; lean_object* v___y_1408_; uint64_t v___y_1409_; uint64_t v___y_1410_; uint64_t v___y_1415_; uint32_t v___y_1416_; lean_object* v___y_1417_; uint64_t v___y_1418_; uint64_t v___y_1419_; uint32_t v___y_1420_; uint64_t v___y_1421_; uint64_t v___y_1422_; uint64_t v___y_1423_; lean_object* v___y_1424_; uint64_t v___y_1425_; uint64_t v___y_1430_; uint32_t v___y_1431_; lean_object* v___y_1432_; uint64_t v___y_1433_; uint32_t v___y_1434_; uint64_t v___y_1435_; uint64_t v___y_1436_; lean_object* v___y_1437_; uint64_t v___y_1438_; uint64_t v___y_1443_; uint32_t v___y_1444_; lean_object* v___y_1445_; uint32_t v___y_1446_; uint64_t v___y_1447_; uint64_t v___y_1448_; uint64_t v___y_1449_; lean_object* v___y_1450_; uint64_t v___y_1451_; uint64_t v___y_1456_; uint32_t v___y_1457_; uint32_t v___y_1458_; lean_object* v_fst_1459_; lean_object* v_snd_1460_; uint32_t v___y_1475_; uint32_t v___y_1476_; uint64_t v___y_1481_; lean_object* v___y_1482_; uint64_t v___y_1483_; uint32_t v___y_1498_; uint32_t v___y_1499_; uint32_t v___y_1500_; uint32_t v___y_1501_; uint32_t v___y_1502_; uint32_t v___y_1510_; uint32_t v___y_1511_; uint32_t v___y_1512_; lean_object* v___y_1513_; uint32_t v___y_1514_; uint32_t v___y_1519_; uint64_t v___y_1520_; uint64_t v___y_1521_; uint32_t v___y_1522_; lean_object* v___y_1523_; uint64_t v___y_1524_; uint64_t v___y_1534_; uint32_t v___y_1535_; uint64_t v___y_1536_; uint8_t v___y_1537_; uint32_t v___y_1538_; lean_object* v___y_1539_; uint64_t v___y_1540_; uint32_t v___y_1548_; uint64_t v___y_1549_; uint64_t v___y_1550_; uint32_t v___y_1551_; lean_object* v___y_1552_; uint64_t v___y_1553_; uint64_t v___y_1559_; uint32_t v___y_1560_; uint64_t v___y_1561_; uint32_t v___y_1562_; lean_object* v___y_1563_; lean_object* v___y_1564_; uint64_t v___y_1565_; uint64_t v___y_1566_; uint64_t v___y_1630_; uint32_t v___y_1631_; uint64_t v___y_1632_; uint64_t v___y_1633_; uint32_t v___y_1634_; lean_object* v___y_1635_; lean_object* v___y_1636_; uint64_t v___y_1637_; uint64_t v___y_1638_; uint64_t v___y_1644_; uint64_t v___y_1645_; uint32_t v___y_1646_; uint64_t v___y_1647_; uint64_t v___y_1648_; uint32_t v___y_1649_; lean_object* v___y_1650_; lean_object* v___y_1651_; uint64_t v___y_1652_; uint64_t v___y_1653_; uint64_t v___y_1654_; uint64_t v___y_1659_; uint32_t v___y_1660_; uint64_t v___y_1661_; uint32_t v___y_1662_; uint64_t v___y_1663_; lean_object* v___y_1664_; lean_object* v___y_1665_; uint64_t v___y_1666_; uint64_t v___y_1667_; uint64_t v___y_1672_; uint32_t v___y_1673_; uint64_t v___y_1674_; uint32_t v___y_1675_; lean_object* v___y_1676_; lean_object* v___y_1677_; uint64_t v___y_1678_; uint64_t v___y_1679_; uint64_t v___y_1680_; uint64_t v___y_1681_; uint64_t v___y_1682_; uint64_t v___y_1687_; uint32_t v___y_1688_; uint64_t v___y_1689_; uint32_t v___y_1690_; lean_object* v___y_1691_; lean_object* v___y_1692_; uint64_t v___y_1693_; uint64_t v___y_1694_; uint64_t v___y_1695_; uint64_t v___y_1700_; uint64_t v___y_1701_; uint32_t v___y_1702_; uint64_t v___y_1703_; uint32_t v___y_1704_; lean_object* v___y_1705_; lean_object* v___y_1706_; uint64_t v___y_1707_; uint64_t v___y_1708_; uint64_t v___y_1709_; uint64_t v___y_1710_; uint64_t v___y_1715_; uint32_t v___y_1716_; uint64_t v___y_1717_; uint64_t v___y_1718_; uint32_t v___y_1719_; lean_object* v___y_1720_; lean_object* v___y_1721_; uint64_t v___y_1722_; uint64_t v___y_1723_; uint64_t v___y_1728_; uint32_t v___y_1729_; uint64_t v___y_1730_; uint64_t v___y_1731_; uint64_t v___y_1732_; uint32_t v___y_1733_; lean_object* v___y_1734_; lean_object* v___y_1735_; uint64_t v___y_1736_; uint64_t v___y_1737_; uint64_t v___y_1738_; uint64_t v___y_1743_; uint32_t v___y_1744_; uint64_t v___y_1745_; uint32_t v___y_1746_; lean_object* v___y_1747_; lean_object* v___y_1748_; uint64_t v___y_1749_; uint64_t v___y_1750_; uint64_t v___y_1751_; uint64_t v___y_1756_; uint32_t v___y_1757_; uint64_t v___y_1758_; uint64_t v___y_1759_; uint32_t v___y_1760_; lean_object* v___y_1761_; lean_object* v___y_1762_; uint64_t v___y_1763_; uint64_t v___y_1764_; uint32_t v___y_1769_; uint64_t v___y_1770_; uint32_t v___y_1771_; lean_object* v_fst_1772_; lean_object* v_snd_1773_; uint32_t v___y_1788_; uint64_t v___y_1789_; uint64_t v___y_1790_; uint64_t v___y_1791_; uint32_t v___y_1792_; uint8_t v___y_1793_; uint8_t v___y_1794_; uint8_t v___y_1795_; uint64_t v___y_1807_; uint32_t v___y_1808_; uint64_t v___y_1809_; uint64_t v___y_1810_; uint32_t v___y_1811_; uint8_t v___y_1812_; uint8_t v___y_1813_; uint8_t v___y_1814_; uint64_t v___y_1819_; uint32_t v___y_1820_; uint64_t v___y_1821_; uint64_t v___y_1822_; uint32_t v___y_1823_; uint8_t v___y_1824_; uint8_t v___y_1825_; uint8_t v___y_1826_; uint64_t v___y_1838_; uint32_t v___y_1839_; uint64_t v___y_1840_; uint64_t v___y_1841_; uint32_t v___y_1842_; uint8_t v___y_1843_; uint8_t v___y_1844_; uint8_t v___y_1845_; uint64_t v___y_1850_; uint32_t v___y_1851_; uint64_t v___y_1852_; uint64_t v___y_1853_; uint32_t v___y_1854_; uint8_t v___y_1855_; uint8_t v___y_1856_; uint64_t v___y_1857_; uint32_t v___y_1868_; uint32_t v___y_1869_; uint64_t v___y_1870_; uint64_t v___y_1871_; uint32_t v___y_1872_; uint8_t v___y_1873_; uint8_t v___y_1874_; uint64_t v___y_1875_; uint32_t v___y_1882_; uint64_t v___y_1883_; uint32_t v___y_1884_; uint32_t v___y_1885_; uint8_t v___y_1886_; uint32_t v___y_1887_; uint8_t v___y_1888_; uint64_t v___y_1889_; uint32_t v___y_1896_; uint32_t v___y_1897_; uint32_t v___y_1898_; uint8_t v___y_1899_; uint8_t v___y_1900_; uint32_t v___y_1901_; uint64_t v___y_1902_; uint32_t v___y_1912_; uint32_t v___y_1913_; uint32_t v___y_1914_; uint8_t v___y_1915_; uint32_t v___y_1916_; uint8_t v___y_1917_; uint8_t v___y_1927_; uint32_t v___y_1928_; uint32_t v___y_1929_; uint32_t v___y_1930_; uint32_t v___y_1931_; uint8_t v___y_1932_; uint8_t v___y_1939_; uint32_t v___x_1956_; uint32_t v___x_1957_; uint32_t v___x_1958_; uint32_t v___x_1959_; uint8_t v___x_1960_; 
v___x_1956_ = 4278190079;
v___x_1957_ = 1;
v___x_1958_ = lean_uint32_shift_left(v_x_1151_, v___x_1957_);
v___x_1959_ = lean_uint32_sub(v___x_1958_, v___x_1957_);
v___x_1960_ = lean_uint32_dec_le(v___x_1956_, v___x_1959_);
if (v___x_1960_ == 0)
{
uint32_t v___x_1961_; uint32_t v___x_1962_; uint8_t v___x_1963_; 
v___x_1961_ = lean_uint32_shift_left(v_y_1152_, v___x_1957_);
v___x_1962_ = lean_uint32_sub(v___x_1961_, v___x_1957_);
v___x_1963_ = lean_uint32_dec_le(v___x_1956_, v___x_1962_);
v___y_1939_ = v___x_1963_;
goto v___jp_1938_;
}
else
{
v___y_1939_ = v___x_1960_;
goto v___jp_1938_;
}
v___jp_1153_:
{
uint32_t v___x_1155_; uint32_t v___x_1156_; 
v___x_1155_ = 8388608;
v___x_1156_ = lean_uint32_lor(v___y_1154_, v___x_1155_);
return v___x_1156_;
}
v___jp_1157_:
{
uint32_t v___x_1159_; uint32_t v___x_1160_; 
v___x_1159_ = 8388608;
v___x_1160_ = lean_uint32_lor(v___y_1158_, v___x_1159_);
return v___x_1160_;
}
v___jp_1161_:
{
uint32_t v___x_1164_; uint32_t v___x_1165_; uint32_t v___x_1166_; 
v___x_1164_ = 8388607;
v___x_1165_ = lean_uint32_land(v___y_1162_, v___x_1164_);
v___x_1166_ = lean_uint32_lor(v___y_1163_, v___x_1165_);
return v___x_1166_;
}
v___jp_1167_:
{
uint8_t v___x_1171_; 
v___x_1171_ = lean_uint64_dec_eq(v___y_1170_, v___y_1168_);
if (v___x_1171_ == 0)
{
uint64_t v___x_1172_; uint8_t v___x_1173_; 
v___x_1172_ = 8388608ULL;
v___x_1173_ = lean_uint64_dec_eq(v___y_1170_, v___x_1172_);
if (v___x_1173_ == 0)
{
uint32_t v___x_1174_; uint8_t v___x_1175_; 
v___x_1174_ = lean_uint64_to_uint32(v___y_1170_);
v___x_1175_ = lean_unbox(v___y_1169_);
lean_dec(v___y_1169_);
if (v___x_1175_ == 0)
{
uint32_t v___x_1176_; 
v___x_1176_ = 0;
v___y_1162_ = v___x_1174_;
v___y_1163_ = v___x_1176_;
goto v___jp_1161_;
}
else
{
uint32_t v___x_1177_; 
v___x_1177_ = 2147483648;
v___y_1162_ = v___x_1174_;
v___y_1163_ = v___x_1177_;
goto v___jp_1161_;
}
}
else
{
uint8_t v___x_1178_; 
v___x_1178_ = lean_unbox(v___y_1169_);
lean_dec(v___y_1169_);
if (v___x_1178_ == 0)
{
uint32_t v___x_1179_; 
v___x_1179_ = 0;
v___y_1158_ = v___x_1179_;
goto v___jp_1157_;
}
else
{
uint32_t v___x_1180_; 
v___x_1180_ = 2147483648;
v___y_1158_ = v___x_1180_;
goto v___jp_1157_;
}
}
}
else
{
uint8_t v___x_1181_; 
v___x_1181_ = lean_unbox(v___y_1169_);
lean_dec(v___y_1169_);
if (v___x_1181_ == 0)
{
uint32_t v___x_1182_; 
v___x_1182_ = 0;
return v___x_1182_;
}
else
{
uint32_t v___x_1183_; 
v___x_1183_ = 2147483648;
return v___x_1183_;
}
}
}
v___jp_1184_:
{
uint32_t v___x_1190_; uint32_t v___x_1191_; uint32_t v___x_1192_; uint32_t v___x_1193_; uint32_t v___x_1194_; uint32_t v___x_1195_; 
v___x_1190_ = lean_uint32_land(v___y_1186_, v___y_1188_);
v___x_1191_ = lean_uint32_shift_left(v___x_1190_, v___y_1185_);
v___x_1192_ = lean_uint32_lor(v___y_1189_, v___x_1191_);
v___x_1193_ = 8388607;
v___x_1194_ = lean_uint32_land(v___y_1187_, v___x_1193_);
v___x_1195_ = lean_uint32_lor(v___x_1192_, v___x_1194_);
return v___x_1195_;
}
v___jp_1196_:
{
uint8_t v___x_1202_; 
v___x_1202_ = lean_unbox(v___y_1200_);
lean_dec(v___y_1200_);
if (v___x_1202_ == 0)
{
uint32_t v___x_1203_; 
v___x_1203_ = 0;
v___y_1185_ = v___y_1198_;
v___y_1186_ = v___y_1197_;
v___y_1187_ = v___y_1201_;
v___y_1188_ = v___y_1199_;
v___y_1189_ = v___x_1203_;
goto v___jp_1184_;
}
else
{
uint32_t v___x_1204_; 
v___x_1204_ = 2147483648;
v___y_1185_ = v___y_1198_;
v___y_1186_ = v___y_1197_;
v___y_1187_ = v___y_1201_;
v___y_1188_ = v___y_1199_;
v___y_1189_ = v___x_1204_;
goto v___jp_1184_;
}
}
v___jp_1205_:
{
uint64_t v___x_1212_; uint64_t v_encodedExponent_1213_; uint32_t v___x_1214_; uint64_t v___x_1215_; uint8_t v___x_1216_; 
v___x_1212_ = 171ULL;
v_encodedExponent_1213_ = lean_uint64_sub(v___y_1207_, v___x_1212_);
v___x_1214_ = lean_uint64_to_uint32(v_encodedExponent_1213_);
v___x_1215_ = 8388608ULL;
v___x_1216_ = lean_uint64_dec_lt(v___y_1211_, v___x_1215_);
if (v___x_1216_ == 0)
{
uint64_t v___x_1217_; uint32_t v___x_1218_; 
v___x_1217_ = lean_uint64_sub(v___y_1211_, v___x_1215_);
v___x_1218_ = lean_uint64_to_uint32(v___x_1217_);
v___y_1197_ = v___x_1214_;
v___y_1198_ = v___y_1206_;
v___y_1199_ = v___y_1208_;
v___y_1200_ = v___y_1210_;
v___y_1201_ = v___x_1218_;
goto v___jp_1196_;
}
else
{
uint32_t v___x_1219_; 
v___x_1219_ = lean_uint64_to_uint32(v___y_1209_);
v___y_1197_ = v___x_1214_;
v___y_1198_ = v___y_1206_;
v___y_1199_ = v___y_1208_;
v___y_1200_ = v___y_1210_;
v___y_1201_ = v___x_1219_;
goto v___jp_1196_;
}
}
v___jp_1220_:
{
uint64_t v___x_1228_; uint8_t v___x_1229_; 
v___x_1228_ = 425ULL;
v___x_1229_ = lean_uint64_dec_lt(v___x_1228_, v___y_1227_);
if (v___x_1229_ == 0)
{
if (v___y_1222_ == 0)
{
v___y_1206_ = v___y_1221_;
v___y_1207_ = v___y_1227_;
v___y_1208_ = v___y_1223_;
v___y_1209_ = v___y_1225_;
v___y_1210_ = v___y_1226_;
v___y_1211_ = v___y_1224_;
goto v___jp_1205_;
}
else
{
uint64_t v___x_1230_; 
v___x_1230_ = 8388608ULL;
v___y_1206_ = v___y_1221_;
v___y_1207_ = v___y_1227_;
v___y_1208_ = v___y_1223_;
v___y_1209_ = v___y_1225_;
v___y_1210_ = v___y_1226_;
v___y_1211_ = v___x_1230_;
goto v___jp_1205_;
}
}
else
{
uint8_t v___x_1231_; 
v___x_1231_ = lean_unbox(v___y_1226_);
lean_dec(v___y_1226_);
if (v___x_1231_ == 0)
{
uint32_t v___x_1232_; 
v___x_1232_ = 2139095040;
return v___x_1232_;
}
else
{
uint32_t v___x_1233_; 
v___x_1233_ = 4286578688;
return v___x_1233_;
}
}
}
v___jp_1234_:
{
uint64_t v___x_1241_; uint8_t v_carry_1242_; 
v___x_1241_ = 16777216ULL;
v_carry_1242_ = lean_uint64_dec_eq(v___y_1240_, v___x_1241_);
if (v_carry_1242_ == 0)
{
v___y_1221_ = v___y_1235_;
v___y_1222_ = v_carry_1242_;
v___y_1223_ = v___y_1237_;
v___y_1224_ = v___y_1240_;
v___y_1225_ = v___y_1238_;
v___y_1226_ = v___y_1239_;
v___y_1227_ = v___y_1236_;
goto v___jp_1220_;
}
else
{
uint64_t v___x_1243_; uint64_t v___x_1244_; 
v___x_1243_ = 1ULL;
v___x_1244_ = lean_uint64_add(v___y_1236_, v___x_1243_);
v___y_1221_ = v___y_1235_;
v___y_1222_ = v_carry_1242_;
v___y_1223_ = v___y_1237_;
v___y_1224_ = v___y_1240_;
v___y_1225_ = v___y_1238_;
v___y_1226_ = v___y_1239_;
v___y_1227_ = v___x_1244_;
goto v___jp_1220_;
}
}
v___jp_1245_:
{
uint64_t v_position_1254_; uint64_t v___x_1255_; uint8_t v___x_1256_; 
v_position_1254_ = lean_uint64_add(v___y_1253_, v___y_1246_);
v___x_1255_ = 172ULL;
v___x_1256_ = lean_uint64_dec_lt(v_position_1254_, v___x_1255_);
if (v___x_1256_ == 0)
{
uint64_t v___x_1257_; uint8_t v___x_1258_; 
v___x_1257_ = 23ULL;
v___x_1258_ = lean_uint64_dec_lt(v___y_1253_, v___x_1257_);
if (v___x_1258_ == 0)
{
uint64_t v___x_1259_; uint8_t v___x_1260_; 
v___x_1259_ = lean_uint64_sub(v___y_1253_, v___x_1257_);
v___x_1260_ = lean_uint64_dec_eq(v___x_1259_, v___y_1251_);
if (v___x_1260_ == 0)
{
uint64_t v___x_1261_; uint8_t v___x_1262_; 
v___x_1261_ = 64ULL;
v___x_1262_ = lean_uint64_dec_lt(v___x_1259_, v___x_1261_);
if (v___x_1262_ == 0)
{
uint8_t v___x_1263_; 
v___x_1263_ = lean_uint64_dec_eq(v___x_1259_, v___x_1261_);
if (v___x_1263_ == 0)
{
lean_dec(v___y_1248_);
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v___y_1251_;
goto v___jp_1234_;
}
else
{
uint64_t v___x_1264_; uint64_t v___x_1265_; uint8_t v___x_1266_; 
v___x_1264_ = 9223372036854775808ULL;
v___x_1265_ = lean_unbox_uint64(v___y_1248_);
lean_dec(v___y_1248_);
v___x_1266_ = lean_uint64_dec_lt(v___x_1264_, v___x_1265_);
if (v___x_1266_ == 0)
{
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v___y_1251_;
goto v___jp_1234_;
}
else
{
uint64_t v___x_1267_; 
v___x_1267_ = 1ULL;
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v___x_1267_;
goto v___jp_1234_;
}
}
}
else
{
uint64_t v___x_1268_; uint64_t v_quotient_1269_; uint64_t v___x_1270_; uint64_t v___x_1271_; uint64_t v___x_1272_; uint64_t v___x_1273_; uint64_t v_remainder_1274_; uint64_t v___x_1275_; uint64_t v_half_1276_; uint8_t v___x_1277_; 
v___x_1268_ = lean_unbox_uint64(v___y_1248_);
v_quotient_1269_ = lean_uint64_shift_right(v___x_1268_, v___x_1259_);
v___x_1270_ = 1ULL;
v___x_1271_ = lean_uint64_shift_left(v___x_1270_, v___x_1259_);
v___x_1272_ = lean_uint64_sub(v___x_1271_, v___x_1270_);
v___x_1273_ = lean_unbox_uint64(v___y_1248_);
lean_dec(v___y_1248_);
v_remainder_1274_ = lean_uint64_land(v___x_1273_, v___x_1272_);
v___x_1275_ = lean_uint64_sub(v___x_1259_, v___x_1270_);
v_half_1276_ = lean_uint64_shift_left(v___x_1270_, v___x_1275_);
v___x_1277_ = lean_uint64_dec_lt(v_remainder_1274_, v_half_1276_);
if (v___x_1277_ == 0)
{
uint8_t v___x_1278_; 
v___x_1278_ = lean_uint64_dec_lt(v_half_1276_, v_remainder_1274_);
if (v___x_1278_ == 0)
{
uint64_t v___x_1279_; uint8_t v___x_1280_; 
v___x_1279_ = lean_uint64_land(v_quotient_1269_, v___x_1270_);
v___x_1280_ = lean_uint64_dec_eq(v___x_1279_, v___y_1251_);
if (v___x_1280_ == 0)
{
uint64_t v___x_1281_; 
v___x_1281_ = lean_uint64_add(v_quotient_1269_, v___x_1270_);
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v___x_1281_;
goto v___jp_1234_;
}
else
{
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v_quotient_1269_;
goto v___jp_1234_;
}
}
else
{
uint64_t v___x_1282_; 
v___x_1282_ = lean_uint64_add(v_quotient_1269_, v___x_1270_);
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v___x_1282_;
goto v___jp_1234_;
}
}
else
{
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v_quotient_1269_;
goto v___jp_1234_;
}
}
}
else
{
uint64_t v___x_1283_; 
v___x_1283_ = lean_unbox_uint64(v___y_1248_);
lean_dec(v___y_1248_);
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v___x_1283_;
goto v___jp_1234_;
}
}
else
{
uint64_t v___x_1284_; uint64_t v___x_1285_; uint64_t v___x_1286_; 
v___x_1284_ = lean_uint64_sub(v___x_1257_, v___y_1253_);
v___x_1285_ = lean_unbox_uint64(v___y_1248_);
lean_dec(v___y_1248_);
v___x_1286_ = lean_uint64_shift_left(v___x_1285_, v___x_1284_);
v___y_1235_ = v___y_1247_;
v___y_1236_ = v_position_1254_;
v___y_1237_ = v___y_1249_;
v___y_1238_ = v___y_1251_;
v___y_1239_ = v___y_1252_;
v___y_1240_ = v___x_1286_;
goto v___jp_1234_;
}
}
else
{
uint8_t v___x_1287_; 
v___x_1287_ = lean_uint64_dec_lt(v___y_1246_, v___y_1250_);
if (v___x_1287_ == 0)
{
uint64_t v___x_1288_; uint64_t v___x_1289_; uint64_t v___x_1290_; 
v___x_1288_ = lean_uint64_sub(v___y_1246_, v___y_1250_);
v___x_1289_ = lean_unbox_uint64(v___y_1248_);
lean_dec(v___y_1248_);
v___x_1290_ = lean_uint64_shift_left(v___x_1289_, v___x_1288_);
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v___x_1290_;
goto v___jp_1167_;
}
else
{
uint64_t v___x_1291_; uint8_t v___x_1292_; 
v___x_1291_ = lean_uint64_sub(v___y_1250_, v___y_1246_);
v___x_1292_ = lean_uint64_dec_eq(v___x_1291_, v___y_1251_);
if (v___x_1292_ == 0)
{
uint64_t v___x_1293_; uint8_t v___x_1294_; 
v___x_1293_ = 64ULL;
v___x_1294_ = lean_uint64_dec_lt(v___x_1291_, v___x_1293_);
if (v___x_1294_ == 0)
{
uint8_t v___x_1295_; 
v___x_1295_ = lean_uint64_dec_eq(v___x_1291_, v___x_1293_);
if (v___x_1295_ == 0)
{
lean_dec(v___y_1248_);
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v___y_1251_;
goto v___jp_1167_;
}
else
{
uint64_t v___x_1296_; uint64_t v___x_1297_; uint8_t v___x_1298_; 
v___x_1296_ = 9223372036854775808ULL;
v___x_1297_ = lean_unbox_uint64(v___y_1248_);
lean_dec(v___y_1248_);
v___x_1298_ = lean_uint64_dec_lt(v___x_1296_, v___x_1297_);
if (v___x_1298_ == 0)
{
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v___y_1251_;
goto v___jp_1167_;
}
else
{
uint64_t v___x_1299_; 
v___x_1299_ = 1ULL;
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v___x_1299_;
goto v___jp_1167_;
}
}
}
else
{
uint64_t v___x_1300_; uint64_t v_quotient_1301_; uint64_t v___x_1302_; uint64_t v___x_1303_; uint64_t v___x_1304_; uint64_t v___x_1305_; uint64_t v_remainder_1306_; uint64_t v___x_1307_; uint64_t v_half_1308_; uint8_t v___x_1309_; 
v___x_1300_ = lean_unbox_uint64(v___y_1248_);
v_quotient_1301_ = lean_uint64_shift_right(v___x_1300_, v___x_1291_);
v___x_1302_ = 1ULL;
v___x_1303_ = lean_uint64_shift_left(v___x_1302_, v___x_1291_);
v___x_1304_ = lean_uint64_sub(v___x_1303_, v___x_1302_);
v___x_1305_ = lean_unbox_uint64(v___y_1248_);
lean_dec(v___y_1248_);
v_remainder_1306_ = lean_uint64_land(v___x_1305_, v___x_1304_);
v___x_1307_ = lean_uint64_sub(v___x_1291_, v___x_1302_);
v_half_1308_ = lean_uint64_shift_left(v___x_1302_, v___x_1307_);
v___x_1309_ = lean_uint64_dec_lt(v_remainder_1306_, v_half_1308_);
if (v___x_1309_ == 0)
{
uint8_t v___x_1310_; 
v___x_1310_ = lean_uint64_dec_lt(v_half_1308_, v_remainder_1306_);
if (v___x_1310_ == 0)
{
uint64_t v___x_1311_; uint8_t v___x_1312_; 
v___x_1311_ = lean_uint64_land(v_quotient_1301_, v___x_1302_);
v___x_1312_ = lean_uint64_dec_eq(v___x_1311_, v___y_1251_);
if (v___x_1312_ == 0)
{
uint64_t v___x_1313_; 
v___x_1313_ = lean_uint64_add(v_quotient_1301_, v___x_1302_);
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v___x_1313_;
goto v___jp_1167_;
}
else
{
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v_quotient_1301_;
goto v___jp_1167_;
}
}
else
{
uint64_t v___x_1314_; 
v___x_1314_ = lean_uint64_add(v_quotient_1301_, v___x_1302_);
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v___x_1314_;
goto v___jp_1167_;
}
}
else
{
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v_quotient_1301_;
goto v___jp_1167_;
}
}
}
else
{
uint64_t v___x_1315_; 
v___x_1315_ = lean_unbox_uint64(v___y_1248_);
lean_dec(v___y_1248_);
v___y_1168_ = v___y_1251_;
v___y_1169_ = v___y_1252_;
v___y_1170_ = v___x_1315_;
goto v___jp_1167_;
}
}
}
}
v___jp_1316_:
{
uint64_t v___x_1326_; uint64_t v___x_1327_; uint8_t v___x_1328_; 
v___x_1326_ = 1ULL;
v___x_1327_ = lean_uint64_shift_right(v___y_1320_, v___x_1326_);
v___x_1328_ = lean_uint64_dec_eq(v___x_1327_, v___y_1323_);
if (v___x_1328_ == 0)
{
uint64_t v___x_1329_; 
v___x_1329_ = lean_uint64_add(v___y_1325_, v___x_1326_);
v___y_1246_ = v___y_1317_;
v___y_1247_ = v___y_1318_;
v___y_1248_ = v___y_1319_;
v___y_1249_ = v___y_1321_;
v___y_1250_ = v___y_1322_;
v___y_1251_ = v___y_1323_;
v___y_1252_ = v___y_1324_;
v___y_1253_ = v___x_1329_;
goto v___jp_1245_;
}
else
{
v___y_1246_ = v___y_1317_;
v___y_1247_ = v___y_1318_;
v___y_1248_ = v___y_1319_;
v___y_1249_ = v___y_1321_;
v___y_1250_ = v___y_1322_;
v___y_1251_ = v___y_1323_;
v___y_1252_ = v___y_1324_;
v___y_1253_ = v___y_1325_;
goto v___jp_1245_;
}
}
v___jp_1330_:
{
uint64_t v___x_1342_; uint8_t v___x_1343_; 
v___x_1342_ = lean_uint64_shift_right(v___y_1334_, v___y_1337_);
v___x_1343_ = lean_uint64_dec_eq(v___x_1342_, v___y_1339_);
if (v___x_1343_ == 0)
{
uint64_t v___x_1344_; 
v___x_1344_ = lean_uint64_add(v___y_1335_, v___y_1337_);
v___y_1317_ = v___y_1331_;
v___y_1318_ = v___y_1332_;
v___y_1319_ = v___y_1333_;
v___y_1320_ = v___y_1341_;
v___y_1321_ = v___y_1336_;
v___y_1322_ = v___y_1338_;
v___y_1323_ = v___y_1339_;
v___y_1324_ = v___y_1340_;
v___y_1325_ = v___x_1344_;
goto v___jp_1316_;
}
else
{
v___y_1317_ = v___y_1331_;
v___y_1318_ = v___y_1332_;
v___y_1319_ = v___y_1333_;
v___y_1320_ = v___y_1341_;
v___y_1321_ = v___y_1336_;
v___y_1322_ = v___y_1338_;
v___y_1323_ = v___y_1339_;
v___y_1324_ = v___y_1340_;
v___y_1325_ = v___y_1335_;
goto v___jp_1316_;
}
}
v___jp_1345_:
{
uint64_t v___x_1355_; uint64_t v___x_1356_; uint8_t v___x_1357_; 
v___x_1355_ = 2ULL;
v___x_1356_ = lean_uint64_shift_right(v___y_1349_, v___x_1355_);
v___x_1357_ = lean_uint64_dec_eq(v___x_1356_, v___y_1352_);
if (v___x_1357_ == 0)
{
v___y_1331_ = v___y_1346_;
v___y_1332_ = v___y_1347_;
v___y_1333_ = v___y_1348_;
v___y_1334_ = v___y_1349_;
v___y_1335_ = v___y_1354_;
v___y_1336_ = v___y_1350_;
v___y_1337_ = v___x_1355_;
v___y_1338_ = v___y_1351_;
v___y_1339_ = v___y_1352_;
v___y_1340_ = v___y_1353_;
v___y_1341_ = v___x_1356_;
goto v___jp_1330_;
}
else
{
v___y_1331_ = v___y_1346_;
v___y_1332_ = v___y_1347_;
v___y_1333_ = v___y_1348_;
v___y_1334_ = v___y_1349_;
v___y_1335_ = v___y_1354_;
v___y_1336_ = v___y_1350_;
v___y_1337_ = v___x_1355_;
v___y_1338_ = v___y_1351_;
v___y_1339_ = v___y_1352_;
v___y_1340_ = v___y_1353_;
v___y_1341_ = v___y_1349_;
goto v___jp_1330_;
}
}
v___jp_1358_:
{
uint64_t v___x_1370_; uint8_t v___x_1371_; 
v___x_1370_ = lean_uint64_shift_right(v___y_1360_, v___y_1364_);
v___x_1371_ = lean_uint64_dec_eq(v___x_1370_, v___y_1367_);
if (v___x_1371_ == 0)
{
uint64_t v___x_1372_; 
v___x_1372_ = lean_uint64_add(v___y_1363_, v___y_1364_);
v___y_1346_ = v___y_1359_;
v___y_1347_ = v___y_1361_;
v___y_1348_ = v___y_1362_;
v___y_1349_ = v___y_1369_;
v___y_1350_ = v___y_1365_;
v___y_1351_ = v___y_1366_;
v___y_1352_ = v___y_1367_;
v___y_1353_ = v___y_1368_;
v___y_1354_ = v___x_1372_;
goto v___jp_1345_;
}
else
{
v___y_1346_ = v___y_1359_;
v___y_1347_ = v___y_1361_;
v___y_1348_ = v___y_1362_;
v___y_1349_ = v___y_1369_;
v___y_1350_ = v___y_1365_;
v___y_1351_ = v___y_1366_;
v___y_1352_ = v___y_1367_;
v___y_1353_ = v___y_1368_;
v___y_1354_ = v___y_1363_;
goto v___jp_1345_;
}
}
v___jp_1373_:
{
uint64_t v___x_1383_; uint64_t v___x_1384_; uint8_t v___x_1385_; 
v___x_1383_ = 4ULL;
v___x_1384_ = lean_uint64_shift_right(v___y_1375_, v___x_1383_);
v___x_1385_ = lean_uint64_dec_eq(v___x_1384_, v___y_1380_);
if (v___x_1385_ == 0)
{
v___y_1359_ = v___y_1374_;
v___y_1360_ = v___y_1375_;
v___y_1361_ = v___y_1376_;
v___y_1362_ = v___y_1377_;
v___y_1363_ = v___y_1382_;
v___y_1364_ = v___x_1383_;
v___y_1365_ = v___y_1378_;
v___y_1366_ = v___y_1379_;
v___y_1367_ = v___y_1380_;
v___y_1368_ = v___y_1381_;
v___y_1369_ = v___x_1384_;
goto v___jp_1358_;
}
else
{
v___y_1359_ = v___y_1374_;
v___y_1360_ = v___y_1375_;
v___y_1361_ = v___y_1376_;
v___y_1362_ = v___y_1377_;
v___y_1363_ = v___y_1382_;
v___y_1364_ = v___x_1383_;
v___y_1365_ = v___y_1378_;
v___y_1366_ = v___y_1379_;
v___y_1367_ = v___y_1380_;
v___y_1368_ = v___y_1381_;
v___y_1369_ = v___y_1375_;
goto v___jp_1358_;
}
}
v___jp_1386_:
{
uint64_t v___x_1398_; uint8_t v___x_1399_; 
v___x_1398_ = lean_uint64_shift_right(v___y_1395_, v___y_1389_);
v___x_1399_ = lean_uint64_dec_eq(v___x_1398_, v___y_1394_);
if (v___x_1399_ == 0)
{
uint64_t v___x_1400_; 
v___x_1400_ = lean_uint64_add(v___y_1391_, v___y_1389_);
v___y_1374_ = v___y_1387_;
v___y_1375_ = v___y_1397_;
v___y_1376_ = v___y_1388_;
v___y_1377_ = v___y_1390_;
v___y_1378_ = v___y_1392_;
v___y_1379_ = v___y_1393_;
v___y_1380_ = v___y_1394_;
v___y_1381_ = v___y_1396_;
v___y_1382_ = v___x_1400_;
goto v___jp_1373_;
}
else
{
v___y_1374_ = v___y_1387_;
v___y_1375_ = v___y_1397_;
v___y_1376_ = v___y_1388_;
v___y_1377_ = v___y_1390_;
v___y_1378_ = v___y_1392_;
v___y_1379_ = v___y_1393_;
v___y_1380_ = v___y_1394_;
v___y_1381_ = v___y_1396_;
v___y_1382_ = v___y_1391_;
goto v___jp_1373_;
}
}
v___jp_1401_:
{
uint64_t v___x_1411_; uint64_t v___x_1412_; uint8_t v___x_1413_; 
v___x_1411_ = 8ULL;
v___x_1412_ = lean_uint64_shift_right(v___y_1409_, v___x_1411_);
v___x_1413_ = lean_uint64_dec_eq(v___x_1412_, v___y_1407_);
if (v___x_1413_ == 0)
{
v___y_1387_ = v___y_1402_;
v___y_1388_ = v___y_1403_;
v___y_1389_ = v___x_1411_;
v___y_1390_ = v___y_1404_;
v___y_1391_ = v___y_1410_;
v___y_1392_ = v___y_1405_;
v___y_1393_ = v___y_1406_;
v___y_1394_ = v___y_1407_;
v___y_1395_ = v___y_1409_;
v___y_1396_ = v___y_1408_;
v___y_1397_ = v___x_1412_;
goto v___jp_1386_;
}
else
{
v___y_1387_ = v___y_1402_;
v___y_1388_ = v___y_1403_;
v___y_1389_ = v___x_1411_;
v___y_1390_ = v___y_1404_;
v___y_1391_ = v___y_1410_;
v___y_1392_ = v___y_1405_;
v___y_1393_ = v___y_1406_;
v___y_1394_ = v___y_1407_;
v___y_1395_ = v___y_1409_;
v___y_1396_ = v___y_1408_;
v___y_1397_ = v___y_1409_;
goto v___jp_1386_;
}
}
v___jp_1414_:
{
uint64_t v___x_1426_; uint8_t v___x_1427_; 
v___x_1426_ = lean_uint64_shift_right(v___y_1419_, v___y_1422_);
v___x_1427_ = lean_uint64_dec_eq(v___x_1426_, v___y_1423_);
if (v___x_1427_ == 0)
{
uint64_t v___x_1428_; 
v___x_1428_ = lean_uint64_add(v___y_1418_, v___y_1422_);
v___y_1402_ = v___y_1415_;
v___y_1403_ = v___y_1416_;
v___y_1404_ = v___y_1417_;
v___y_1405_ = v___y_1420_;
v___y_1406_ = v___y_1421_;
v___y_1407_ = v___y_1423_;
v___y_1408_ = v___y_1424_;
v___y_1409_ = v___y_1425_;
v___y_1410_ = v___x_1428_;
goto v___jp_1401_;
}
else
{
v___y_1402_ = v___y_1415_;
v___y_1403_ = v___y_1416_;
v___y_1404_ = v___y_1417_;
v___y_1405_ = v___y_1420_;
v___y_1406_ = v___y_1421_;
v___y_1407_ = v___y_1423_;
v___y_1408_ = v___y_1424_;
v___y_1409_ = v___y_1425_;
v___y_1410_ = v___y_1418_;
goto v___jp_1401_;
}
}
v___jp_1429_:
{
uint64_t v___x_1439_; uint64_t v___x_1440_; uint8_t v___x_1441_; 
v___x_1439_ = 16ULL;
v___x_1440_ = lean_uint64_shift_right(v___y_1433_, v___x_1439_);
v___x_1441_ = lean_uint64_dec_eq(v___x_1440_, v___y_1436_);
if (v___x_1441_ == 0)
{
v___y_1415_ = v___y_1430_;
v___y_1416_ = v___y_1431_;
v___y_1417_ = v___y_1432_;
v___y_1418_ = v___y_1438_;
v___y_1419_ = v___y_1433_;
v___y_1420_ = v___y_1434_;
v___y_1421_ = v___y_1435_;
v___y_1422_ = v___x_1439_;
v___y_1423_ = v___y_1436_;
v___y_1424_ = v___y_1437_;
v___y_1425_ = v___x_1440_;
goto v___jp_1414_;
}
else
{
v___y_1415_ = v___y_1430_;
v___y_1416_ = v___y_1431_;
v___y_1417_ = v___y_1432_;
v___y_1418_ = v___y_1438_;
v___y_1419_ = v___y_1433_;
v___y_1420_ = v___y_1434_;
v___y_1421_ = v___y_1435_;
v___y_1422_ = v___x_1439_;
v___y_1423_ = v___y_1436_;
v___y_1424_ = v___y_1437_;
v___y_1425_ = v___y_1433_;
goto v___jp_1414_;
}
}
v___jp_1442_:
{
uint64_t v___x_1452_; uint64_t v___x_1453_; uint8_t v___x_1454_; 
v___x_1452_ = lean_unbox_uint64(v___y_1445_);
v___x_1453_ = lean_uint64_shift_right(v___x_1452_, v___y_1449_);
v___x_1454_ = lean_uint64_dec_eq(v___x_1453_, v___y_1448_);
if (v___x_1454_ == 0)
{
v___y_1430_ = v___y_1443_;
v___y_1431_ = v___y_1444_;
v___y_1432_ = v___y_1445_;
v___y_1433_ = v___y_1451_;
v___y_1434_ = v___y_1446_;
v___y_1435_ = v___y_1447_;
v___y_1436_ = v___y_1448_;
v___y_1437_ = v___y_1450_;
v___y_1438_ = v___y_1449_;
goto v___jp_1429_;
}
else
{
v___y_1430_ = v___y_1443_;
v___y_1431_ = v___y_1444_;
v___y_1432_ = v___y_1445_;
v___y_1433_ = v___y_1451_;
v___y_1434_ = v___y_1446_;
v___y_1435_ = v___y_1447_;
v___y_1436_ = v___y_1448_;
v___y_1437_ = v___y_1450_;
v___y_1438_ = v___y_1448_;
goto v___jp_1429_;
}
}
v___jp_1455_:
{
uint64_t v___x_1461_; uint64_t v___x_1462_; uint8_t v___x_1463_; 
v___x_1461_ = 0ULL;
v___x_1462_ = lean_unbox_uint64(v_snd_1460_);
v___x_1463_ = lean_uint64_dec_eq(v___x_1462_, v___x_1461_);
if (v___x_1463_ == 0)
{
uint64_t v___x_1464_; uint64_t v___x_1465_; uint64_t v___x_1466_; uint64_t v___x_1467_; uint64_t v___x_1468_; uint8_t v___x_1469_; 
v___x_1464_ = 149ULL;
v___x_1465_ = lean_uint64_add(v___y_1456_, v___x_1464_);
v___x_1466_ = 32ULL;
v___x_1467_ = lean_unbox_uint64(v_snd_1460_);
v___x_1468_ = lean_uint64_shift_right(v___x_1467_, v___x_1466_);
v___x_1469_ = lean_uint64_dec_eq(v___x_1468_, v___x_1461_);
if (v___x_1469_ == 0)
{
v___y_1443_ = v___x_1465_;
v___y_1444_ = v___y_1457_;
v___y_1445_ = v_snd_1460_;
v___y_1446_ = v___y_1458_;
v___y_1447_ = v___x_1464_;
v___y_1448_ = v___x_1461_;
v___y_1449_ = v___x_1466_;
v___y_1450_ = v_fst_1459_;
v___y_1451_ = v___x_1468_;
goto v___jp_1442_;
}
else
{
uint64_t v___x_1470_; 
v___x_1470_ = lean_unbox_uint64(v_snd_1460_);
v___y_1443_ = v___x_1465_;
v___y_1444_ = v___y_1457_;
v___y_1445_ = v_snd_1460_;
v___y_1446_ = v___y_1458_;
v___y_1447_ = v___x_1464_;
v___y_1448_ = v___x_1461_;
v___y_1449_ = v___x_1466_;
v___y_1450_ = v_fst_1459_;
v___y_1451_ = v___x_1470_;
goto v___jp_1442_;
}
}
else
{
uint8_t v___x_1471_; 
lean_dec(v_snd_1460_);
v___x_1471_ = lean_unbox(v_fst_1459_);
lean_dec(v_fst_1459_);
if (v___x_1471_ == 0)
{
uint32_t v___x_1472_; 
v___x_1472_ = 0;
return v___x_1472_;
}
else
{
uint32_t v___x_1473_; 
v___x_1473_ = 2147483648;
return v___x_1473_;
}
}
}
v___jp_1474_:
{
uint32_t v___x_1477_; uint32_t v___x_1478_; uint32_t v___x_1479_; 
v___x_1477_ = 8388607;
v___x_1478_ = lean_uint32_land(v___y_1475_, v___x_1477_);
v___x_1479_ = lean_uint32_lor(v___y_1476_, v___x_1478_);
return v___x_1479_;
}
v___jp_1480_:
{
uint8_t v___x_1484_; 
v___x_1484_ = lean_uint64_dec_eq(v___y_1483_, v___y_1481_);
if (v___x_1484_ == 0)
{
uint64_t v___x_1485_; uint8_t v___x_1486_; 
v___x_1485_ = 8388608ULL;
v___x_1486_ = lean_uint64_dec_eq(v___y_1483_, v___x_1485_);
if (v___x_1486_ == 0)
{
uint32_t v___x_1487_; uint8_t v___x_1488_; 
v___x_1487_ = lean_uint64_to_uint32(v___y_1483_);
v___x_1488_ = lean_unbox(v___y_1482_);
lean_dec(v___y_1482_);
if (v___x_1488_ == 0)
{
uint32_t v___x_1489_; 
v___x_1489_ = 0;
v___y_1475_ = v___x_1487_;
v___y_1476_ = v___x_1489_;
goto v___jp_1474_;
}
else
{
uint32_t v___x_1490_; 
v___x_1490_ = 2147483648;
v___y_1475_ = v___x_1487_;
v___y_1476_ = v___x_1490_;
goto v___jp_1474_;
}
}
else
{
uint8_t v___x_1491_; 
v___x_1491_ = lean_unbox(v___y_1482_);
lean_dec(v___y_1482_);
if (v___x_1491_ == 0)
{
uint32_t v___x_1492_; 
v___x_1492_ = 0;
v___y_1154_ = v___x_1492_;
goto v___jp_1153_;
}
else
{
uint32_t v___x_1493_; 
v___x_1493_ = 2147483648;
v___y_1154_ = v___x_1493_;
goto v___jp_1153_;
}
}
}
else
{
uint8_t v___x_1494_; 
v___x_1494_ = lean_unbox(v___y_1482_);
lean_dec(v___y_1482_);
if (v___x_1494_ == 0)
{
uint32_t v___x_1495_; 
v___x_1495_ = 0;
return v___x_1495_;
}
else
{
uint32_t v___x_1496_; 
v___x_1496_ = 2147483648;
return v___x_1496_;
}
}
}
v___jp_1497_:
{
uint32_t v___x_1503_; uint32_t v___x_1504_; uint32_t v___x_1505_; uint32_t v___x_1506_; uint32_t v___x_1507_; uint32_t v___x_1508_; 
v___x_1503_ = lean_uint32_land(v___y_1499_, v___y_1500_);
v___x_1504_ = lean_uint32_shift_left(v___x_1503_, v___y_1498_);
v___x_1505_ = lean_uint32_lor(v___y_1502_, v___x_1504_);
v___x_1506_ = 8388607;
v___x_1507_ = lean_uint32_land(v___y_1501_, v___x_1506_);
v___x_1508_ = lean_uint32_lor(v___x_1505_, v___x_1507_);
return v___x_1508_;
}
v___jp_1509_:
{
uint8_t v___x_1515_; 
v___x_1515_ = lean_unbox(v___y_1513_);
lean_dec(v___y_1513_);
if (v___x_1515_ == 0)
{
uint32_t v___x_1516_; 
v___x_1516_ = 0;
v___y_1498_ = v___y_1510_;
v___y_1499_ = v___y_1511_;
v___y_1500_ = v___y_1512_;
v___y_1501_ = v___y_1514_;
v___y_1502_ = v___x_1516_;
goto v___jp_1497_;
}
else
{
uint32_t v___x_1517_; 
v___x_1517_ = 2147483648;
v___y_1498_ = v___y_1510_;
v___y_1499_ = v___y_1511_;
v___y_1500_ = v___y_1512_;
v___y_1501_ = v___y_1514_;
v___y_1502_ = v___x_1517_;
goto v___jp_1497_;
}
}
v___jp_1518_:
{
uint64_t v___x_1525_; uint64_t v_encodedExponent_1526_; uint32_t v___x_1527_; uint64_t v___x_1528_; uint8_t v___x_1529_; 
v___x_1525_ = 171ULL;
v_encodedExponent_1526_ = lean_uint64_sub(v___y_1521_, v___x_1525_);
v___x_1527_ = lean_uint64_to_uint32(v_encodedExponent_1526_);
v___x_1528_ = 8388608ULL;
v___x_1529_ = lean_uint64_dec_lt(v___y_1524_, v___x_1528_);
if (v___x_1529_ == 0)
{
uint64_t v___x_1530_; uint32_t v___x_1531_; 
v___x_1530_ = lean_uint64_sub(v___y_1524_, v___x_1528_);
v___x_1531_ = lean_uint64_to_uint32(v___x_1530_);
v___y_1510_ = v___y_1519_;
v___y_1511_ = v___x_1527_;
v___y_1512_ = v___y_1522_;
v___y_1513_ = v___y_1523_;
v___y_1514_ = v___x_1531_;
goto v___jp_1509_;
}
else
{
uint32_t v___x_1532_; 
v___x_1532_ = lean_uint64_to_uint32(v___y_1520_);
v___y_1510_ = v___y_1519_;
v___y_1511_ = v___x_1527_;
v___y_1512_ = v___y_1522_;
v___y_1513_ = v___y_1523_;
v___y_1514_ = v___x_1532_;
goto v___jp_1509_;
}
}
v___jp_1533_:
{
uint64_t v___x_1541_; uint8_t v___x_1542_; 
v___x_1541_ = 425ULL;
v___x_1542_ = lean_uint64_dec_lt(v___x_1541_, v___y_1540_);
if (v___x_1542_ == 0)
{
if (v___y_1537_ == 0)
{
v___y_1519_ = v___y_1535_;
v___y_1520_ = v___y_1536_;
v___y_1521_ = v___y_1540_;
v___y_1522_ = v___y_1538_;
v___y_1523_ = v___y_1539_;
v___y_1524_ = v___y_1534_;
goto v___jp_1518_;
}
else
{
uint64_t v___x_1543_; 
v___x_1543_ = 8388608ULL;
v___y_1519_ = v___y_1535_;
v___y_1520_ = v___y_1536_;
v___y_1521_ = v___y_1540_;
v___y_1522_ = v___y_1538_;
v___y_1523_ = v___y_1539_;
v___y_1524_ = v___x_1543_;
goto v___jp_1518_;
}
}
else
{
uint8_t v___x_1544_; 
v___x_1544_ = lean_unbox(v___y_1539_);
lean_dec(v___y_1539_);
if (v___x_1544_ == 0)
{
uint32_t v___x_1545_; 
v___x_1545_ = 2139095040;
return v___x_1545_;
}
else
{
uint32_t v___x_1546_; 
v___x_1546_ = 4286578688;
return v___x_1546_;
}
}
}
v___jp_1547_:
{
uint64_t v___x_1554_; uint8_t v_carry_1555_; 
v___x_1554_ = 16777216ULL;
v_carry_1555_ = lean_uint64_dec_eq(v___y_1553_, v___x_1554_);
if (v_carry_1555_ == 0)
{
v___y_1534_ = v___y_1553_;
v___y_1535_ = v___y_1548_;
v___y_1536_ = v___y_1549_;
v___y_1537_ = v_carry_1555_;
v___y_1538_ = v___y_1551_;
v___y_1539_ = v___y_1552_;
v___y_1540_ = v___y_1550_;
goto v___jp_1533_;
}
else
{
uint64_t v___x_1556_; uint64_t v___x_1557_; 
v___x_1556_ = 1ULL;
v___x_1557_ = lean_uint64_add(v___y_1550_, v___x_1556_);
v___y_1534_ = v___y_1553_;
v___y_1535_ = v___y_1548_;
v___y_1536_ = v___y_1549_;
v___y_1537_ = v_carry_1555_;
v___y_1538_ = v___y_1551_;
v___y_1539_ = v___y_1552_;
v___y_1540_ = v___x_1557_;
goto v___jp_1533_;
}
}
v___jp_1558_:
{
uint64_t v_position_1567_; uint64_t v___x_1568_; uint8_t v___x_1569_; 
v_position_1567_ = lean_uint64_add(v___y_1566_, v___y_1565_);
v___x_1568_ = 172ULL;
v___x_1569_ = lean_uint64_dec_lt(v_position_1567_, v___x_1568_);
if (v___x_1569_ == 0)
{
uint64_t v___x_1570_; uint8_t v___x_1571_; 
v___x_1570_ = 23ULL;
v___x_1571_ = lean_uint64_dec_lt(v___y_1566_, v___x_1570_);
if (v___x_1571_ == 0)
{
uint64_t v___x_1572_; uint8_t v___x_1573_; 
v___x_1572_ = lean_uint64_sub(v___y_1566_, v___x_1570_);
v___x_1573_ = lean_uint64_dec_eq(v___x_1572_, v___y_1561_);
if (v___x_1573_ == 0)
{
uint64_t v___x_1574_; uint8_t v___x_1575_; 
v___x_1574_ = 64ULL;
v___x_1575_ = lean_uint64_dec_lt(v___x_1572_, v___x_1574_);
if (v___x_1575_ == 0)
{
uint8_t v___x_1576_; 
v___x_1576_ = lean_uint64_dec_eq(v___x_1572_, v___x_1574_);
if (v___x_1576_ == 0)
{
lean_dec(v___y_1563_);
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v___y_1561_;
goto v___jp_1547_;
}
else
{
uint64_t v___x_1577_; uint64_t v___x_1578_; uint8_t v___x_1579_; 
v___x_1577_ = 9223372036854775808ULL;
v___x_1578_ = lean_unbox_uint64(v___y_1563_);
lean_dec(v___y_1563_);
v___x_1579_ = lean_uint64_dec_lt(v___x_1577_, v___x_1578_);
if (v___x_1579_ == 0)
{
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v___y_1561_;
goto v___jp_1547_;
}
else
{
uint64_t v___x_1580_; 
v___x_1580_ = 1ULL;
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v___x_1580_;
goto v___jp_1547_;
}
}
}
else
{
uint64_t v___x_1581_; uint64_t v_quotient_1582_; uint64_t v___x_1583_; uint64_t v___x_1584_; uint64_t v___x_1585_; uint64_t v___x_1586_; uint64_t v_remainder_1587_; uint64_t v___x_1588_; uint64_t v_half_1589_; uint8_t v___x_1590_; 
v___x_1581_ = lean_unbox_uint64(v___y_1563_);
v_quotient_1582_ = lean_uint64_shift_right(v___x_1581_, v___x_1572_);
v___x_1583_ = 1ULL;
v___x_1584_ = lean_uint64_shift_left(v___x_1583_, v___x_1572_);
v___x_1585_ = lean_uint64_sub(v___x_1584_, v___x_1583_);
v___x_1586_ = lean_unbox_uint64(v___y_1563_);
lean_dec(v___y_1563_);
v_remainder_1587_ = lean_uint64_land(v___x_1586_, v___x_1585_);
v___x_1588_ = lean_uint64_sub(v___x_1572_, v___x_1583_);
v_half_1589_ = lean_uint64_shift_left(v___x_1583_, v___x_1588_);
v___x_1590_ = lean_uint64_dec_lt(v_remainder_1587_, v_half_1589_);
if (v___x_1590_ == 0)
{
uint8_t v___x_1591_; 
v___x_1591_ = lean_uint64_dec_lt(v_half_1589_, v_remainder_1587_);
if (v___x_1591_ == 0)
{
uint64_t v___x_1592_; uint8_t v___x_1593_; 
v___x_1592_ = lean_uint64_land(v_quotient_1582_, v___x_1583_);
v___x_1593_ = lean_uint64_dec_eq(v___x_1592_, v___y_1561_);
if (v___x_1593_ == 0)
{
uint64_t v___x_1594_; 
v___x_1594_ = lean_uint64_add(v_quotient_1582_, v___x_1583_);
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v___x_1594_;
goto v___jp_1547_;
}
else
{
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v_quotient_1582_;
goto v___jp_1547_;
}
}
else
{
uint64_t v___x_1595_; 
v___x_1595_ = lean_uint64_add(v_quotient_1582_, v___x_1583_);
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v___x_1595_;
goto v___jp_1547_;
}
}
else
{
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v_quotient_1582_;
goto v___jp_1547_;
}
}
}
else
{
uint64_t v___x_1596_; 
v___x_1596_ = lean_unbox_uint64(v___y_1563_);
lean_dec(v___y_1563_);
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v___x_1596_;
goto v___jp_1547_;
}
}
else
{
uint64_t v___x_1597_; uint64_t v___x_1598_; uint64_t v___x_1599_; 
v___x_1597_ = lean_uint64_sub(v___x_1570_, v___y_1566_);
v___x_1598_ = lean_unbox_uint64(v___y_1563_);
lean_dec(v___y_1563_);
v___x_1599_ = lean_uint64_shift_left(v___x_1598_, v___x_1597_);
v___y_1548_ = v___y_1560_;
v___y_1549_ = v___y_1561_;
v___y_1550_ = v_position_1567_;
v___y_1551_ = v___y_1562_;
v___y_1552_ = v___y_1564_;
v___y_1553_ = v___x_1599_;
goto v___jp_1547_;
}
}
else
{
uint8_t v___x_1600_; 
v___x_1600_ = lean_uint64_dec_lt(v___y_1565_, v___y_1559_);
if (v___x_1600_ == 0)
{
uint64_t v___x_1601_; uint64_t v___x_1602_; uint64_t v___x_1603_; 
v___x_1601_ = lean_uint64_sub(v___y_1565_, v___y_1559_);
v___x_1602_ = lean_unbox_uint64(v___y_1563_);
lean_dec(v___y_1563_);
v___x_1603_ = lean_uint64_shift_left(v___x_1602_, v___x_1601_);
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v___x_1603_;
goto v___jp_1480_;
}
else
{
uint64_t v___x_1604_; uint8_t v___x_1605_; 
v___x_1604_ = lean_uint64_sub(v___y_1559_, v___y_1565_);
v___x_1605_ = lean_uint64_dec_eq(v___x_1604_, v___y_1561_);
if (v___x_1605_ == 0)
{
uint64_t v___x_1606_; uint8_t v___x_1607_; 
v___x_1606_ = 64ULL;
v___x_1607_ = lean_uint64_dec_lt(v___x_1604_, v___x_1606_);
if (v___x_1607_ == 0)
{
uint8_t v___x_1608_; 
v___x_1608_ = lean_uint64_dec_eq(v___x_1604_, v___x_1606_);
if (v___x_1608_ == 0)
{
lean_dec(v___y_1563_);
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v___y_1561_;
goto v___jp_1480_;
}
else
{
uint64_t v___x_1609_; uint64_t v___x_1610_; uint8_t v___x_1611_; 
v___x_1609_ = 9223372036854775808ULL;
v___x_1610_ = lean_unbox_uint64(v___y_1563_);
lean_dec(v___y_1563_);
v___x_1611_ = lean_uint64_dec_lt(v___x_1609_, v___x_1610_);
if (v___x_1611_ == 0)
{
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v___y_1561_;
goto v___jp_1480_;
}
else
{
uint64_t v___x_1612_; 
v___x_1612_ = 1ULL;
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v___x_1612_;
goto v___jp_1480_;
}
}
}
else
{
uint64_t v___x_1613_; uint64_t v_quotient_1614_; uint64_t v___x_1615_; uint64_t v___x_1616_; uint64_t v___x_1617_; uint64_t v___x_1618_; uint64_t v_remainder_1619_; uint64_t v___x_1620_; uint64_t v_half_1621_; uint8_t v___x_1622_; 
v___x_1613_ = lean_unbox_uint64(v___y_1563_);
v_quotient_1614_ = lean_uint64_shift_right(v___x_1613_, v___x_1604_);
v___x_1615_ = 1ULL;
v___x_1616_ = lean_uint64_shift_left(v___x_1615_, v___x_1604_);
v___x_1617_ = lean_uint64_sub(v___x_1616_, v___x_1615_);
v___x_1618_ = lean_unbox_uint64(v___y_1563_);
lean_dec(v___y_1563_);
v_remainder_1619_ = lean_uint64_land(v___x_1618_, v___x_1617_);
v___x_1620_ = lean_uint64_sub(v___x_1604_, v___x_1615_);
v_half_1621_ = lean_uint64_shift_left(v___x_1615_, v___x_1620_);
v___x_1622_ = lean_uint64_dec_lt(v_remainder_1619_, v_half_1621_);
if (v___x_1622_ == 0)
{
uint8_t v___x_1623_; 
v___x_1623_ = lean_uint64_dec_lt(v_half_1621_, v_remainder_1619_);
if (v___x_1623_ == 0)
{
uint64_t v___x_1624_; uint8_t v___x_1625_; 
v___x_1624_ = lean_uint64_land(v_quotient_1614_, v___x_1615_);
v___x_1625_ = lean_uint64_dec_eq(v___x_1624_, v___y_1561_);
if (v___x_1625_ == 0)
{
uint64_t v___x_1626_; 
v___x_1626_ = lean_uint64_add(v_quotient_1614_, v___x_1615_);
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v___x_1626_;
goto v___jp_1480_;
}
else
{
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v_quotient_1614_;
goto v___jp_1480_;
}
}
else
{
uint64_t v___x_1627_; 
v___x_1627_ = lean_uint64_add(v_quotient_1614_, v___x_1615_);
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v___x_1627_;
goto v___jp_1480_;
}
}
else
{
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v_quotient_1614_;
goto v___jp_1480_;
}
}
}
else
{
uint64_t v___x_1628_; 
v___x_1628_ = lean_unbox_uint64(v___y_1563_);
lean_dec(v___y_1563_);
v___y_1481_ = v___y_1561_;
v___y_1482_ = v___y_1564_;
v___y_1483_ = v___x_1628_;
goto v___jp_1480_;
}
}
}
}
v___jp_1629_:
{
uint64_t v___x_1639_; uint64_t v___x_1640_; uint8_t v___x_1641_; 
v___x_1639_ = 1ULL;
v___x_1640_ = lean_uint64_shift_right(v___y_1632_, v___x_1639_);
v___x_1641_ = lean_uint64_dec_eq(v___x_1640_, v___y_1633_);
if (v___x_1641_ == 0)
{
uint64_t v___x_1642_; 
v___x_1642_ = lean_uint64_add(v___y_1638_, v___x_1639_);
v___y_1559_ = v___y_1630_;
v___y_1560_ = v___y_1631_;
v___y_1561_ = v___y_1633_;
v___y_1562_ = v___y_1634_;
v___y_1563_ = v___y_1636_;
v___y_1564_ = v___y_1635_;
v___y_1565_ = v___y_1637_;
v___y_1566_ = v___x_1642_;
goto v___jp_1558_;
}
else
{
v___y_1559_ = v___y_1630_;
v___y_1560_ = v___y_1631_;
v___y_1561_ = v___y_1633_;
v___y_1562_ = v___y_1634_;
v___y_1563_ = v___y_1636_;
v___y_1564_ = v___y_1635_;
v___y_1565_ = v___y_1637_;
v___y_1566_ = v___y_1638_;
goto v___jp_1558_;
}
}
v___jp_1643_:
{
uint64_t v___x_1655_; uint8_t v___x_1656_; 
v___x_1655_ = lean_uint64_shift_right(v___y_1648_, v___y_1653_);
v___x_1656_ = lean_uint64_dec_eq(v___x_1655_, v___y_1647_);
if (v___x_1656_ == 0)
{
uint64_t v___x_1657_; 
v___x_1657_ = lean_uint64_add(v___y_1644_, v___y_1653_);
v___y_1630_ = v___y_1645_;
v___y_1631_ = v___y_1646_;
v___y_1632_ = v___y_1654_;
v___y_1633_ = v___y_1647_;
v___y_1634_ = v___y_1649_;
v___y_1635_ = v___y_1651_;
v___y_1636_ = v___y_1650_;
v___y_1637_ = v___y_1652_;
v___y_1638_ = v___x_1657_;
goto v___jp_1629_;
}
else
{
v___y_1630_ = v___y_1645_;
v___y_1631_ = v___y_1646_;
v___y_1632_ = v___y_1654_;
v___y_1633_ = v___y_1647_;
v___y_1634_ = v___y_1649_;
v___y_1635_ = v___y_1651_;
v___y_1636_ = v___y_1650_;
v___y_1637_ = v___y_1652_;
v___y_1638_ = v___y_1644_;
goto v___jp_1629_;
}
}
v___jp_1658_:
{
uint64_t v___x_1668_; uint64_t v___x_1669_; uint8_t v___x_1670_; 
v___x_1668_ = 2ULL;
v___x_1669_ = lean_uint64_shift_right(v___y_1663_, v___x_1668_);
v___x_1670_ = lean_uint64_dec_eq(v___x_1669_, v___y_1661_);
if (v___x_1670_ == 0)
{
v___y_1644_ = v___y_1667_;
v___y_1645_ = v___y_1659_;
v___y_1646_ = v___y_1660_;
v___y_1647_ = v___y_1661_;
v___y_1648_ = v___y_1663_;
v___y_1649_ = v___y_1662_;
v___y_1650_ = v___y_1665_;
v___y_1651_ = v___y_1664_;
v___y_1652_ = v___y_1666_;
v___y_1653_ = v___x_1668_;
v___y_1654_ = v___x_1669_;
goto v___jp_1643_;
}
else
{
v___y_1644_ = v___y_1667_;
v___y_1645_ = v___y_1659_;
v___y_1646_ = v___y_1660_;
v___y_1647_ = v___y_1661_;
v___y_1648_ = v___y_1663_;
v___y_1649_ = v___y_1662_;
v___y_1650_ = v___y_1665_;
v___y_1651_ = v___y_1664_;
v___y_1652_ = v___y_1666_;
v___y_1653_ = v___x_1668_;
v___y_1654_ = v___y_1663_;
goto v___jp_1643_;
}
}
v___jp_1671_:
{
uint64_t v___x_1683_; uint8_t v___x_1684_; 
v___x_1683_ = lean_uint64_shift_right(v___y_1681_, v___y_1679_);
v___x_1684_ = lean_uint64_dec_eq(v___x_1683_, v___y_1674_);
if (v___x_1684_ == 0)
{
uint64_t v___x_1685_; 
v___x_1685_ = lean_uint64_add(v___y_1678_, v___y_1679_);
v___y_1659_ = v___y_1672_;
v___y_1660_ = v___y_1673_;
v___y_1661_ = v___y_1674_;
v___y_1662_ = v___y_1675_;
v___y_1663_ = v___y_1682_;
v___y_1664_ = v___y_1677_;
v___y_1665_ = v___y_1676_;
v___y_1666_ = v___y_1680_;
v___y_1667_ = v___x_1685_;
goto v___jp_1658_;
}
else
{
v___y_1659_ = v___y_1672_;
v___y_1660_ = v___y_1673_;
v___y_1661_ = v___y_1674_;
v___y_1662_ = v___y_1675_;
v___y_1663_ = v___y_1682_;
v___y_1664_ = v___y_1677_;
v___y_1665_ = v___y_1676_;
v___y_1666_ = v___y_1680_;
v___y_1667_ = v___y_1678_;
goto v___jp_1658_;
}
}
v___jp_1686_:
{
uint64_t v___x_1696_; uint64_t v___x_1697_; uint8_t v___x_1698_; 
v___x_1696_ = 4ULL;
v___x_1697_ = lean_uint64_shift_right(v___y_1694_, v___x_1696_);
v___x_1698_ = lean_uint64_dec_eq(v___x_1697_, v___y_1689_);
if (v___x_1698_ == 0)
{
v___y_1672_ = v___y_1687_;
v___y_1673_ = v___y_1688_;
v___y_1674_ = v___y_1689_;
v___y_1675_ = v___y_1690_;
v___y_1676_ = v___y_1692_;
v___y_1677_ = v___y_1691_;
v___y_1678_ = v___y_1695_;
v___y_1679_ = v___x_1696_;
v___y_1680_ = v___y_1693_;
v___y_1681_ = v___y_1694_;
v___y_1682_ = v___x_1697_;
goto v___jp_1671_;
}
else
{
v___y_1672_ = v___y_1687_;
v___y_1673_ = v___y_1688_;
v___y_1674_ = v___y_1689_;
v___y_1675_ = v___y_1690_;
v___y_1676_ = v___y_1692_;
v___y_1677_ = v___y_1691_;
v___y_1678_ = v___y_1695_;
v___y_1679_ = v___x_1696_;
v___y_1680_ = v___y_1693_;
v___y_1681_ = v___y_1694_;
v___y_1682_ = v___y_1694_;
goto v___jp_1671_;
}
}
v___jp_1699_:
{
uint64_t v___x_1711_; uint8_t v___x_1712_; 
v___x_1711_ = lean_uint64_shift_right(v___y_1701_, v___y_1709_);
v___x_1712_ = lean_uint64_dec_eq(v___x_1711_, v___y_1703_);
if (v___x_1712_ == 0)
{
uint64_t v___x_1713_; 
v___x_1713_ = lean_uint64_add(v___y_1707_, v___y_1709_);
v___y_1687_ = v___y_1700_;
v___y_1688_ = v___y_1702_;
v___y_1689_ = v___y_1703_;
v___y_1690_ = v___y_1704_;
v___y_1691_ = v___y_1706_;
v___y_1692_ = v___y_1705_;
v___y_1693_ = v___y_1708_;
v___y_1694_ = v___y_1710_;
v___y_1695_ = v___x_1713_;
goto v___jp_1686_;
}
else
{
v___y_1687_ = v___y_1700_;
v___y_1688_ = v___y_1702_;
v___y_1689_ = v___y_1703_;
v___y_1690_ = v___y_1704_;
v___y_1691_ = v___y_1706_;
v___y_1692_ = v___y_1705_;
v___y_1693_ = v___y_1708_;
v___y_1694_ = v___y_1710_;
v___y_1695_ = v___y_1707_;
goto v___jp_1686_;
}
}
v___jp_1714_:
{
uint64_t v___x_1724_; uint64_t v___x_1725_; uint8_t v___x_1726_; 
v___x_1724_ = 8ULL;
v___x_1725_ = lean_uint64_shift_right(v___y_1717_, v___x_1724_);
v___x_1726_ = lean_uint64_dec_eq(v___x_1725_, v___y_1718_);
if (v___x_1726_ == 0)
{
v___y_1700_ = v___y_1715_;
v___y_1701_ = v___y_1717_;
v___y_1702_ = v___y_1716_;
v___y_1703_ = v___y_1718_;
v___y_1704_ = v___y_1719_;
v___y_1705_ = v___y_1721_;
v___y_1706_ = v___y_1720_;
v___y_1707_ = v___y_1723_;
v___y_1708_ = v___y_1722_;
v___y_1709_ = v___x_1724_;
v___y_1710_ = v___x_1725_;
goto v___jp_1699_;
}
else
{
v___y_1700_ = v___y_1715_;
v___y_1701_ = v___y_1717_;
v___y_1702_ = v___y_1716_;
v___y_1703_ = v___y_1718_;
v___y_1704_ = v___y_1719_;
v___y_1705_ = v___y_1721_;
v___y_1706_ = v___y_1720_;
v___y_1707_ = v___y_1723_;
v___y_1708_ = v___y_1722_;
v___y_1709_ = v___x_1724_;
v___y_1710_ = v___y_1717_;
goto v___jp_1699_;
}
}
v___jp_1727_:
{
uint64_t v___x_1739_; uint8_t v___x_1740_; 
v___x_1739_ = lean_uint64_shift_right(v___y_1737_, v___y_1732_);
v___x_1740_ = lean_uint64_dec_eq(v___x_1739_, v___y_1730_);
if (v___x_1740_ == 0)
{
uint64_t v___x_1741_; 
v___x_1741_ = lean_uint64_add(v___y_1731_, v___y_1732_);
v___y_1715_ = v___y_1728_;
v___y_1716_ = v___y_1729_;
v___y_1717_ = v___y_1738_;
v___y_1718_ = v___y_1730_;
v___y_1719_ = v___y_1733_;
v___y_1720_ = v___y_1735_;
v___y_1721_ = v___y_1734_;
v___y_1722_ = v___y_1736_;
v___y_1723_ = v___x_1741_;
goto v___jp_1714_;
}
else
{
v___y_1715_ = v___y_1728_;
v___y_1716_ = v___y_1729_;
v___y_1717_ = v___y_1738_;
v___y_1718_ = v___y_1730_;
v___y_1719_ = v___y_1733_;
v___y_1720_ = v___y_1735_;
v___y_1721_ = v___y_1734_;
v___y_1722_ = v___y_1736_;
v___y_1723_ = v___y_1731_;
goto v___jp_1714_;
}
}
v___jp_1742_:
{
uint64_t v___x_1752_; uint64_t v___x_1753_; uint8_t v___x_1754_; 
v___x_1752_ = 16ULL;
v___x_1753_ = lean_uint64_shift_right(v___y_1750_, v___x_1752_);
v___x_1754_ = lean_uint64_dec_eq(v___x_1753_, v___y_1745_);
if (v___x_1754_ == 0)
{
v___y_1728_ = v___y_1743_;
v___y_1729_ = v___y_1744_;
v___y_1730_ = v___y_1745_;
v___y_1731_ = v___y_1751_;
v___y_1732_ = v___x_1752_;
v___y_1733_ = v___y_1746_;
v___y_1734_ = v___y_1748_;
v___y_1735_ = v___y_1747_;
v___y_1736_ = v___y_1749_;
v___y_1737_ = v___y_1750_;
v___y_1738_ = v___x_1753_;
goto v___jp_1727_;
}
else
{
v___y_1728_ = v___y_1743_;
v___y_1729_ = v___y_1744_;
v___y_1730_ = v___y_1745_;
v___y_1731_ = v___y_1751_;
v___y_1732_ = v___x_1752_;
v___y_1733_ = v___y_1746_;
v___y_1734_ = v___y_1748_;
v___y_1735_ = v___y_1747_;
v___y_1736_ = v___y_1749_;
v___y_1737_ = v___y_1750_;
v___y_1738_ = v___y_1750_;
goto v___jp_1727_;
}
}
v___jp_1755_:
{
uint64_t v___x_1765_; uint64_t v___x_1766_; uint8_t v___x_1767_; 
v___x_1765_ = lean_unbox_uint64(v___y_1761_);
v___x_1766_ = lean_uint64_shift_right(v___x_1765_, v___y_1758_);
v___x_1767_ = lean_uint64_dec_eq(v___x_1766_, v___y_1759_);
if (v___x_1767_ == 0)
{
v___y_1743_ = v___y_1756_;
v___y_1744_ = v___y_1757_;
v___y_1745_ = v___y_1759_;
v___y_1746_ = v___y_1760_;
v___y_1747_ = v___y_1762_;
v___y_1748_ = v___y_1761_;
v___y_1749_ = v___y_1763_;
v___y_1750_ = v___y_1764_;
v___y_1751_ = v___y_1758_;
goto v___jp_1742_;
}
else
{
v___y_1743_ = v___y_1756_;
v___y_1744_ = v___y_1757_;
v___y_1745_ = v___y_1759_;
v___y_1746_ = v___y_1760_;
v___y_1747_ = v___y_1762_;
v___y_1748_ = v___y_1761_;
v___y_1749_ = v___y_1763_;
v___y_1750_ = v___y_1764_;
v___y_1751_ = v___y_1759_;
goto v___jp_1742_;
}
}
v___jp_1768_:
{
uint64_t v___x_1774_; uint64_t v___x_1775_; uint8_t v___x_1776_; 
v___x_1774_ = 0ULL;
v___x_1775_ = lean_unbox_uint64(v_snd_1773_);
v___x_1776_ = lean_uint64_dec_eq(v___x_1775_, v___x_1774_);
if (v___x_1776_ == 0)
{
uint64_t v___x_1777_; uint64_t v___x_1778_; uint64_t v___x_1779_; uint64_t v___x_1780_; uint64_t v___x_1781_; uint8_t v___x_1782_; 
v___x_1777_ = 149ULL;
v___x_1778_ = lean_uint64_add(v___y_1770_, v___x_1777_);
v___x_1779_ = 32ULL;
v___x_1780_ = lean_unbox_uint64(v_snd_1773_);
v___x_1781_ = lean_uint64_shift_right(v___x_1780_, v___x_1779_);
v___x_1782_ = lean_uint64_dec_eq(v___x_1781_, v___x_1774_);
if (v___x_1782_ == 0)
{
v___y_1756_ = v___x_1777_;
v___y_1757_ = v___y_1769_;
v___y_1758_ = v___x_1779_;
v___y_1759_ = v___x_1774_;
v___y_1760_ = v___y_1771_;
v___y_1761_ = v_snd_1773_;
v___y_1762_ = v_fst_1772_;
v___y_1763_ = v___x_1778_;
v___y_1764_ = v___x_1781_;
goto v___jp_1755_;
}
else
{
uint64_t v___x_1783_; 
v___x_1783_ = lean_unbox_uint64(v_snd_1773_);
v___y_1756_ = v___x_1777_;
v___y_1757_ = v___y_1769_;
v___y_1758_ = v___x_1779_;
v___y_1759_ = v___x_1774_;
v___y_1760_ = v___y_1771_;
v___y_1761_ = v_snd_1773_;
v___y_1762_ = v_fst_1772_;
v___y_1763_ = v___x_1778_;
v___y_1764_ = v___x_1783_;
goto v___jp_1755_;
}
}
else
{
uint8_t v___x_1784_; 
lean_dec(v_snd_1773_);
v___x_1784_ = lean_unbox(v_fst_1772_);
lean_dec(v_fst_1772_);
if (v___x_1784_ == 0)
{
uint32_t v___x_1785_; 
v___x_1785_ = 0;
return v___x_1785_;
}
else
{
uint32_t v___x_1786_; 
v___x_1786_ = 2147483648;
return v___x_1786_;
}
}
}
v___jp_1787_:
{
uint8_t v___x_1796_; 
v___x_1796_ = lean_uint64_dec_eq(v___y_1789_, v___y_1791_);
if (v___x_1796_ == 0)
{
uint8_t v___x_1797_; 
v___x_1797_ = lean_uint64_dec_lt(v___y_1789_, v___y_1791_);
if (v___x_1797_ == 0)
{
uint64_t v___x_1798_; lean_object* v___x_1799_; lean_object* v___x_1800_; 
v___x_1798_ = lean_uint64_sub(v___y_1789_, v___y_1791_);
v___x_1799_ = lean_box(v___y_1793_);
v___x_1800_ = lean_box_uint64(v___x_1798_);
v___y_1769_ = v___y_1788_;
v___y_1770_ = v___y_1790_;
v___y_1771_ = v___y_1792_;
v_fst_1772_ = v___x_1799_;
v_snd_1773_ = v___x_1800_;
goto v___jp_1768_;
}
else
{
uint64_t v___x_1801_; lean_object* v___x_1802_; lean_object* v___x_1803_; 
v___x_1801_ = lean_uint64_sub(v___y_1791_, v___y_1789_);
v___x_1802_ = lean_box(v___y_1794_);
v___x_1803_ = lean_box_uint64(v___x_1801_);
v___y_1769_ = v___y_1788_;
v___y_1770_ = v___y_1790_;
v___y_1771_ = v___y_1792_;
v_fst_1772_ = v___x_1802_;
v_snd_1773_ = v___x_1803_;
goto v___jp_1768_;
}
}
else
{
lean_object* v___x_1804_; lean_object* v___x_1805_; 
v___x_1804_ = lean_box(v___y_1795_);
v___x_1805_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1769_ = v___y_1788_;
v___y_1770_ = v___y_1790_;
v___y_1771_ = v___y_1792_;
v_fst_1772_ = v___x_1804_;
v_snd_1773_ = v___x_1805_;
goto v___jp_1768_;
}
}
v___jp_1806_:
{
if (v___y_1814_ == 0)
{
v___y_1788_ = v___y_1808_;
v___y_1789_ = v___y_1807_;
v___y_1790_ = v___y_1809_;
v___y_1791_ = v___y_1810_;
v___y_1792_ = v___y_1811_;
v___y_1793_ = v___y_1812_;
v___y_1794_ = v___y_1813_;
v___y_1795_ = v___y_1814_;
goto v___jp_1787_;
}
else
{
uint64_t v___x_1815_; lean_object* v___x_1816_; lean_object* v___x_1817_; 
v___x_1815_ = lean_uint64_add(v___y_1807_, v___y_1810_);
v___x_1816_ = lean_box(v___y_1812_);
v___x_1817_ = lean_box_uint64(v___x_1815_);
v___y_1769_ = v___y_1808_;
v___y_1770_ = v___y_1809_;
v___y_1771_ = v___y_1811_;
v_fst_1772_ = v___x_1816_;
v_snd_1773_ = v___x_1817_;
goto v___jp_1768_;
}
}
v___jp_1818_:
{
uint8_t v___x_1827_; 
v___x_1827_ = lean_uint64_dec_eq(v___y_1822_, v___y_1821_);
if (v___x_1827_ == 0)
{
uint8_t v___x_1828_; 
v___x_1828_ = lean_uint64_dec_lt(v___y_1822_, v___y_1821_);
if (v___x_1828_ == 0)
{
uint64_t v___x_1829_; lean_object* v___x_1830_; lean_object* v___x_1831_; 
v___x_1829_ = lean_uint64_sub(v___y_1822_, v___y_1821_);
v___x_1830_ = lean_box(v___y_1824_);
v___x_1831_ = lean_box_uint64(v___x_1829_);
v___y_1456_ = v___y_1819_;
v___y_1457_ = v___y_1820_;
v___y_1458_ = v___y_1823_;
v_fst_1459_ = v___x_1830_;
v_snd_1460_ = v___x_1831_;
goto v___jp_1455_;
}
else
{
uint64_t v___x_1832_; lean_object* v___x_1833_; lean_object* v___x_1834_; 
v___x_1832_ = lean_uint64_sub(v___y_1821_, v___y_1822_);
v___x_1833_ = lean_box(v___y_1825_);
v___x_1834_ = lean_box_uint64(v___x_1832_);
v___y_1456_ = v___y_1819_;
v___y_1457_ = v___y_1820_;
v___y_1458_ = v___y_1823_;
v_fst_1459_ = v___x_1833_;
v_snd_1460_ = v___x_1834_;
goto v___jp_1455_;
}
}
else
{
lean_object* v___x_1835_; lean_object* v___x_1836_; 
v___x_1835_ = lean_box(v___y_1826_);
v___x_1836_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1456_ = v___y_1819_;
v___y_1457_ = v___y_1820_;
v___y_1458_ = v___y_1823_;
v_fst_1459_ = v___x_1835_;
v_snd_1460_ = v___x_1836_;
goto v___jp_1455_;
}
}
v___jp_1837_:
{
if (v___y_1845_ == 0)
{
v___y_1819_ = v___y_1838_;
v___y_1820_ = v___y_1839_;
v___y_1821_ = v___y_1841_;
v___y_1822_ = v___y_1840_;
v___y_1823_ = v___y_1842_;
v___y_1824_ = v___y_1843_;
v___y_1825_ = v___y_1844_;
v___y_1826_ = v___y_1845_;
goto v___jp_1818_;
}
else
{
uint64_t v___x_1846_; lean_object* v___x_1847_; lean_object* v___x_1848_; 
v___x_1846_ = lean_uint64_add(v___y_1840_, v___y_1841_);
v___x_1847_ = lean_box(v___y_1843_);
v___x_1848_ = lean_box_uint64(v___x_1846_);
v___y_1456_ = v___y_1838_;
v___y_1457_ = v___y_1839_;
v___y_1458_ = v___y_1842_;
v_fst_1459_ = v___x_1847_;
v_snd_1460_ = v___x_1848_;
goto v___jp_1455_;
}
}
v___jp_1849_:
{
uint8_t v___x_1858_; 
v___x_1858_ = lean_uint64_dec_le(v___y_1850_, v___y_1857_);
if (v___x_1858_ == 0)
{
uint64_t v_shift_1859_; uint64_t v___x_1860_; uint8_t v___x_1861_; 
v_shift_1859_ = lean_uint64_sub(v___y_1850_, v___y_1857_);
v___x_1860_ = 39ULL;
v___x_1861_ = lean_uint64_dec_le(v_shift_1859_, v___x_1860_);
if (v___x_1861_ == 0)
{
return v_x_1151_;
}
else
{
uint64_t v___x_1862_; 
v___x_1862_ = lean_uint64_shift_left(v___y_1852_, v_shift_1859_);
if (v___y_1855_ == 0)
{
if (v___y_1856_ == 0)
{
v___y_1807_ = v___x_1862_;
v___y_1808_ = v___y_1851_;
v___y_1809_ = v___y_1857_;
v___y_1810_ = v___y_1853_;
v___y_1811_ = v___y_1854_;
v___y_1812_ = v___y_1855_;
v___y_1813_ = v___y_1856_;
v___y_1814_ = v___x_1861_;
goto v___jp_1806_;
}
else
{
v___y_1788_ = v___y_1851_;
v___y_1789_ = v___x_1862_;
v___y_1790_ = v___y_1857_;
v___y_1791_ = v___y_1853_;
v___y_1792_ = v___y_1854_;
v___y_1793_ = v___y_1855_;
v___y_1794_ = v___y_1856_;
v___y_1795_ = v___y_1855_;
goto v___jp_1787_;
}
}
else
{
v___y_1807_ = v___x_1862_;
v___y_1808_ = v___y_1851_;
v___y_1809_ = v___y_1857_;
v___y_1810_ = v___y_1853_;
v___y_1811_ = v___y_1854_;
v___y_1812_ = v___y_1855_;
v___y_1813_ = v___y_1856_;
v___y_1814_ = v___y_1856_;
goto v___jp_1806_;
}
}
}
else
{
uint64_t v_shift_1863_; uint64_t v___x_1864_; uint8_t v___x_1865_; 
v_shift_1863_ = lean_uint64_sub(v___y_1857_, v___y_1850_);
v___x_1864_ = 39ULL;
v___x_1865_ = lean_uint64_dec_le(v_shift_1863_, v___x_1864_);
if (v___x_1865_ == 0)
{
return v_y_1152_;
}
else
{
uint64_t v___x_1866_; 
v___x_1866_ = lean_uint64_shift_left(v___y_1853_, v_shift_1863_);
if (v___y_1855_ == 0)
{
if (v___y_1856_ == 0)
{
v___y_1838_ = v___y_1850_;
v___y_1839_ = v___y_1851_;
v___y_1840_ = v___y_1852_;
v___y_1841_ = v___x_1866_;
v___y_1842_ = v___y_1854_;
v___y_1843_ = v___y_1855_;
v___y_1844_ = v___y_1856_;
v___y_1845_ = v___x_1865_;
goto v___jp_1837_;
}
else
{
v___y_1819_ = v___y_1850_;
v___y_1820_ = v___y_1851_;
v___y_1821_ = v___x_1866_;
v___y_1822_ = v___y_1852_;
v___y_1823_ = v___y_1854_;
v___y_1824_ = v___y_1855_;
v___y_1825_ = v___y_1856_;
v___y_1826_ = v___y_1855_;
goto v___jp_1818_;
}
}
else
{
v___y_1838_ = v___y_1850_;
v___y_1839_ = v___y_1851_;
v___y_1840_ = v___y_1852_;
v___y_1841_ = v___x_1866_;
v___y_1842_ = v___y_1854_;
v___y_1843_ = v___y_1855_;
v___y_1844_ = v___y_1856_;
v___y_1845_ = v___y_1856_;
goto v___jp_1837_;
}
}
}
}
v___jp_1867_:
{
uint64_t v___x_1876_; uint64_t v___x_1877_; uint8_t v___x_1878_; 
v___x_1876_ = lean_uint32_to_uint64(v___y_1869_);
v___x_1877_ = 0ULL;
v___x_1878_ = lean_uint64_dec_eq(v___x_1876_, v___x_1877_);
if (v___x_1878_ == 0)
{
uint64_t v___x_1879_; uint64_t v___x_1880_; 
v___x_1879_ = 1ULL;
v___x_1880_ = lean_uint64_sub(v___x_1876_, v___x_1879_);
v___y_1850_ = v___y_1875_;
v___y_1851_ = v___y_1868_;
v___y_1852_ = v___y_1870_;
v___y_1853_ = v___y_1871_;
v___y_1854_ = v___y_1872_;
v___y_1855_ = v___y_1873_;
v___y_1856_ = v___y_1874_;
v___y_1857_ = v___x_1880_;
goto v___jp_1849_;
}
else
{
v___y_1850_ = v___y_1875_;
v___y_1851_ = v___y_1868_;
v___y_1852_ = v___y_1870_;
v___y_1853_ = v___y_1871_;
v___y_1854_ = v___y_1872_;
v___y_1855_ = v___y_1873_;
v___y_1856_ = v___y_1874_;
v___y_1857_ = v___x_1877_;
goto v___jp_1849_;
}
}
v___jp_1881_:
{
uint64_t v___x_1890_; uint64_t v___x_1891_; uint8_t v___x_1892_; 
v___x_1890_ = lean_uint32_to_uint64(v___y_1887_);
v___x_1891_ = 0ULL;
v___x_1892_ = lean_uint64_dec_eq(v___x_1890_, v___x_1891_);
if (v___x_1892_ == 0)
{
uint64_t v___x_1893_; uint64_t v___x_1894_; 
v___x_1893_ = 1ULL;
v___x_1894_ = lean_uint64_sub(v___x_1890_, v___x_1893_);
v___y_1868_ = v___y_1882_;
v___y_1869_ = v___y_1884_;
v___y_1870_ = v___y_1883_;
v___y_1871_ = v___y_1889_;
v___y_1872_ = v___y_1885_;
v___y_1873_ = v___y_1886_;
v___y_1874_ = v___y_1888_;
v___y_1875_ = v___x_1894_;
goto v___jp_1867_;
}
else
{
v___y_1868_ = v___y_1882_;
v___y_1869_ = v___y_1884_;
v___y_1870_ = v___y_1883_;
v___y_1871_ = v___y_1889_;
v___y_1872_ = v___y_1885_;
v___y_1873_ = v___y_1886_;
v___y_1874_ = v___y_1888_;
v___y_1875_ = v___x_1891_;
goto v___jp_1867_;
}
}
v___jp_1895_:
{
uint32_t v___x_1903_; uint32_t v___x_1904_; uint32_t v___x_1905_; uint8_t v___x_1906_; 
v___x_1903_ = 8388607;
v___x_1904_ = lean_uint32_land(v_y_1152_, v___x_1903_);
v___x_1905_ = 0;
v___x_1906_ = lean_uint32_dec_eq(v___y_1897_, v___x_1905_);
if (v___x_1906_ == 0)
{
uint64_t v___x_1907_; uint64_t v___x_1908_; uint64_t v___x_1909_; 
v___x_1907_ = lean_uint32_to_uint64(v___x_1904_);
v___x_1908_ = 8388608ULL;
v___x_1909_ = lean_uint64_lor(v___x_1907_, v___x_1908_);
v___y_1882_ = v___y_1896_;
v___y_1883_ = v___y_1902_;
v___y_1884_ = v___y_1897_;
v___y_1885_ = v___y_1898_;
v___y_1886_ = v___y_1899_;
v___y_1887_ = v___y_1901_;
v___y_1888_ = v___y_1900_;
v___y_1889_ = v___x_1909_;
goto v___jp_1881_;
}
else
{
uint64_t v___x_1910_; 
v___x_1910_ = lean_uint32_to_uint64(v___x_1904_);
v___y_1882_ = v___y_1896_;
v___y_1883_ = v___y_1902_;
v___y_1884_ = v___y_1897_;
v___y_1885_ = v___y_1898_;
v___y_1886_ = v___y_1899_;
v___y_1887_ = v___y_1901_;
v___y_1888_ = v___y_1900_;
v___y_1889_ = v___x_1910_;
goto v___jp_1881_;
}
}
v___jp_1911_:
{
uint32_t v___x_1918_; uint32_t v___x_1919_; uint32_t v___x_1920_; uint8_t v___x_1921_; 
v___x_1918_ = 8388607;
v___x_1919_ = lean_uint32_land(v_x_1151_, v___x_1918_);
v___x_1920_ = 0;
v___x_1921_ = lean_uint32_dec_eq(v___y_1916_, v___x_1920_);
if (v___x_1921_ == 0)
{
uint64_t v___x_1922_; uint64_t v___x_1923_; uint64_t v___x_1924_; 
v___x_1922_ = lean_uint32_to_uint64(v___x_1919_);
v___x_1923_ = 8388608ULL;
v___x_1924_ = lean_uint64_lor(v___x_1922_, v___x_1923_);
v___y_1896_ = v___y_1912_;
v___y_1897_ = v___y_1913_;
v___y_1898_ = v___y_1914_;
v___y_1899_ = v___y_1915_;
v___y_1900_ = v___y_1917_;
v___y_1901_ = v___y_1916_;
v___y_1902_ = v___x_1924_;
goto v___jp_1895_;
}
else
{
uint64_t v___x_1925_; 
v___x_1925_ = lean_uint32_to_uint64(v___x_1919_);
v___y_1896_ = v___y_1912_;
v___y_1897_ = v___y_1913_;
v___y_1898_ = v___y_1914_;
v___y_1899_ = v___y_1915_;
v___y_1900_ = v___y_1917_;
v___y_1901_ = v___y_1916_;
v___y_1902_ = v___x_1925_;
goto v___jp_1895_;
}
}
v___jp_1926_:
{
uint32_t v___x_1933_; uint32_t v___x_1934_; uint32_t v___x_1935_; uint8_t v___x_1936_; 
v___x_1933_ = 2147483648;
v___x_1934_ = lean_uint32_land(v_y_1152_, v___x_1933_);
v___x_1935_ = 0;
v___x_1936_ = lean_uint32_dec_eq(v___x_1934_, v___x_1935_);
if (v___x_1936_ == 0)
{
uint8_t v___x_1937_; 
v___x_1937_ = 1;
v___y_1912_ = v___y_1928_;
v___y_1913_ = v___y_1929_;
v___y_1914_ = v___y_1930_;
v___y_1915_ = v___y_1932_;
v___y_1916_ = v___y_1931_;
v___y_1917_ = v___x_1937_;
goto v___jp_1911_;
}
else
{
v___y_1912_ = v___y_1928_;
v___y_1913_ = v___y_1929_;
v___y_1914_ = v___y_1930_;
v___y_1915_ = v___y_1932_;
v___y_1916_ = v___y_1931_;
v___y_1917_ = v___y_1927_;
goto v___jp_1911_;
}
}
v___jp_1938_:
{
if (v___y_1939_ == 0)
{
uint32_t v___x_1940_; uint32_t v___x_1941_; uint32_t v___x_1942_; uint32_t v_xExponent_1943_; uint32_t v___x_1944_; uint32_t v_yExponent_1945_; uint32_t v___x_1946_; uint32_t v___x_1947_; uint32_t v___x_1948_; uint8_t v___x_1949_; 
v___x_1940_ = 23;
v___x_1941_ = lean_uint32_shift_right(v_x_1151_, v___x_1940_);
v___x_1942_ = 255;
v_xExponent_1943_ = lean_uint32_land(v___x_1941_, v___x_1942_);
v___x_1944_ = lean_uint32_shift_right(v_y_1152_, v___x_1940_);
v_yExponent_1945_ = lean_uint32_land(v___x_1944_, v___x_1942_);
v___x_1946_ = 2147483648;
v___x_1947_ = lean_uint32_land(v_x_1151_, v___x_1946_);
v___x_1948_ = 0;
v___x_1949_ = lean_uint32_dec_eq(v___x_1947_, v___x_1948_);
if (v___x_1949_ == 0)
{
uint8_t v___x_1950_; 
v___x_1950_ = 1;
v___y_1927_ = v___y_1939_;
v___y_1928_ = v___x_1940_;
v___y_1929_ = v_yExponent_1945_;
v___y_1930_ = v___x_1942_;
v___y_1931_ = v_xExponent_1943_;
v___y_1932_ = v___x_1950_;
goto v___jp_1926_;
}
else
{
v___y_1927_ = v___y_1939_;
v___y_1928_ = v___x_1940_;
v___y_1929_ = v_yExponent_1945_;
v___y_1930_ = v___x_1942_;
v___y_1931_ = v_xExponent_1943_;
v___y_1932_ = v___y_1939_;
goto v___jp_1926_;
}
}
else
{
lean_object* v___x_1951_; lean_object* v___x_1952_; lean_object* v___x_1953_; lean_object* v___x_1954_; uint32_t v___x_1955_; 
v___x_1951_ = ((lean_object*)(lp_competition_Submission_TunedAdd_add___closed__0));
v___x_1952_ = lean_uint32_to_nat(v_x_1151_);
v___x_1953_ = lean_uint32_to_nat(v_y_1152_);
v___x_1954_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(v___x_1951_, v___x_1952_, v___x_1953_);
v___x_1955_ = lean_uint32_of_nat(v___x_1954_);
lean_dec(v___x_1954_);
return v___x_1955_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_add___boxed(lean_object* v_x_1964_, lean_object* v_y_1965_){
_start:
{
uint32_t v_x_boxed_1966_; uint32_t v_y_boxed_1967_; uint32_t v_res_1968_; lean_object* v_r_1969_; 
v_x_boxed_1966_ = lean_unbox_uint32(v_x_1964_);
lean_dec(v_x_1964_);
v_y_boxed_1967_ = lean_unbox_uint32(v_y_1965_);
lean_dec(v_y_1965_);
v_res_1968_ = lp_competition_Submission_TunedAdd_add(v_x_boxed_1966_, v_y_boxed_1967_);
v_r_1969_ = lean_box_uint32(v_res_1968_);
return v_r_1969_;
}
}
static uint8_t _init_lp_competition_Submission_TunedAdd_Plan(void){
_start:
{
uint8_t v___x_1971_; 
v___x_1971_ = 2;
return v___x_1971_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec(uint32_t v_z_1972_){
_start:
{
lean_object* v___x_1973_; 
v___x_1973_ = lean_uint32_to_nat(v_z_1972_);
return v___x_1973_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec___boxed(lean_object* v_z_1974_){
_start:
{
uint32_t v_z_boxed_1975_; lean_object* v_res_1976_; 
v_z_boxed_1975_ = lean_unbox_uint32(v_z_1974_);
lean_dec(v_z_1974_);
v_res_1976_ = lp_competition_Submission_TunedAdd_dec(v_z_boxed_1975_);
return v_res_1976_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sx(uint64_t v_k_1977_, uint64_t v_x_1978_){
_start:
{
uint64_t v___x_1979_; uint64_t v___x_1980_; uint8_t v___x_1981_; 
v___x_1979_ = lean_uint64_shift_right(v_x_1978_, v_k_1977_);
v___x_1980_ = 0ULL;
v___x_1981_ = lean_uint64_dec_eq(v___x_1979_, v___x_1980_);
if (v___x_1981_ == 0)
{
return v___x_1979_;
}
else
{
return v_x_1978_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sx___boxed(lean_object* v_k_1982_, lean_object* v_x_1983_){
_start:
{
uint64_t v_k_boxed_1984_; uint64_t v_x_boxed_1985_; uint64_t v_res_1986_; lean_object* v_r_1987_; 
v_k_boxed_1984_ = lean_unbox_uint64(v_k_1982_);
lean_dec_ref(v_k_1982_);
v_x_boxed_1985_ = lean_unbox_uint64(v_x_1983_);
lean_dec_ref(v_x_1983_);
v_res_1986_ = lp_competition_Submission_FastMul_sx(v_k_boxed_1984_, v_x_boxed_1985_);
v_r_1987_ = lean_box_uint64(v_res_1986_);
return v_r_1987_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sr(uint64_t v_k_1988_, uint64_t v_x_1989_, uint64_t v_r_1990_){
_start:
{
uint64_t v___x_1991_; uint64_t v___x_1992_; uint8_t v___x_1993_; 
v___x_1991_ = lean_uint64_shift_right(v_x_1989_, v_k_1988_);
v___x_1992_ = 0ULL;
v___x_1993_ = lean_uint64_dec_eq(v___x_1991_, v___x_1992_);
if (v___x_1993_ == 0)
{
uint64_t v___x_1994_; 
v___x_1994_ = lean_uint64_add(v_r_1990_, v_k_1988_);
return v___x_1994_;
}
else
{
return v_r_1990_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sr___boxed(lean_object* v_k_1995_, lean_object* v_x_1996_, lean_object* v_r_1997_){
_start:
{
uint64_t v_k_boxed_1998_; uint64_t v_x_boxed_1999_; uint64_t v_r_boxed_2000_; uint64_t v_res_2001_; lean_object* v_r_2002_; 
v_k_boxed_1998_ = lean_unbox_uint64(v_k_1995_);
lean_dec_ref(v_k_1995_);
v_x_boxed_1999_ = lean_unbox_uint64(v_x_1996_);
lean_dec_ref(v_x_1996_);
v_r_boxed_2000_ = lean_unbox_uint64(v_r_1997_);
lean_dec_ref(v_r_1997_);
v_res_2001_ = lp_competition_Submission_FastMul_sr(v_k_boxed_1998_, v_x_boxed_1999_, v_r_boxed_2000_);
v_r_2002_ = lean_box_uint64(v_res_2001_);
return v_r_2002_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_fastLog2(uint64_t v_x0_2003_){
_start:
{
uint64_t v___y_2005_; uint64_t v___y_2006_; uint64_t v___y_2013_; uint64_t v___y_2014_; uint64_t v___y_2015_; uint64_t v___y_2016_; uint64_t v___y_2022_; uint64_t v___y_2023_; uint64_t v___y_2029_; uint64_t v___y_2030_; uint64_t v___y_2031_; uint64_t v___y_2032_; uint64_t v___y_2038_; uint64_t v___y_2039_; uint64_t v___y_2045_; uint64_t v___y_2046_; uint64_t v___y_2047_; uint64_t v___y_2048_; uint64_t v___y_2054_; uint64_t v___y_2055_; uint64_t v___y_2061_; uint64_t v___y_2062_; uint64_t v___y_2063_; uint64_t v___y_2064_; uint64_t v___y_2070_; uint64_t v___y_2071_; uint64_t v___x_2076_; uint64_t v___y_2078_; uint64_t v___x_2082_; uint64_t v___x_2083_; uint8_t v___x_2084_; 
v___x_2076_ = 32ULL;
v___x_2082_ = lean_uint64_shift_right(v_x0_2003_, v___x_2076_);
v___x_2083_ = 0ULL;
v___x_2084_ = lean_uint64_dec_eq(v___x_2082_, v___x_2083_);
if (v___x_2084_ == 0)
{
v___y_2078_ = v___x_2082_;
goto v___jp_2077_;
}
else
{
v___y_2078_ = v_x0_2003_;
goto v___jp_2077_;
}
v___jp_2004_:
{
uint64_t v___x_2007_; uint64_t v___x_2008_; uint64_t v___x_2009_; uint8_t v___x_2010_; 
v___x_2007_ = 1ULL;
v___x_2008_ = lean_uint64_shift_right(v___y_2005_, v___x_2007_);
v___x_2009_ = 0ULL;
v___x_2010_ = lean_uint64_dec_eq(v___x_2008_, v___x_2009_);
if (v___x_2010_ == 0)
{
uint64_t v___x_2011_; 
v___x_2011_ = lean_uint64_add(v___y_2006_, v___x_2007_);
return v___x_2011_;
}
else
{
return v___y_2006_;
}
}
v___jp_2012_:
{
uint64_t v___x_2017_; uint64_t v___x_2018_; uint8_t v___x_2019_; 
v___x_2017_ = lean_uint64_shift_right(v___y_2013_, v___y_2014_);
v___x_2018_ = 0ULL;
v___x_2019_ = lean_uint64_dec_eq(v___x_2017_, v___x_2018_);
if (v___x_2019_ == 0)
{
uint64_t v___x_2020_; 
v___x_2020_ = lean_uint64_add(v___y_2015_, v___y_2014_);
v___y_2005_ = v___y_2016_;
v___y_2006_ = v___x_2020_;
goto v___jp_2004_;
}
else
{
v___y_2005_ = v___y_2016_;
v___y_2006_ = v___y_2015_;
goto v___jp_2004_;
}
}
v___jp_2021_:
{
uint64_t v___x_2024_; uint64_t v___x_2025_; uint64_t v___x_2026_; uint8_t v___x_2027_; 
v___x_2024_ = 2ULL;
v___x_2025_ = lean_uint64_shift_right(v___y_2022_, v___x_2024_);
v___x_2026_ = 0ULL;
v___x_2027_ = lean_uint64_dec_eq(v___x_2025_, v___x_2026_);
if (v___x_2027_ == 0)
{
v___y_2013_ = v___y_2022_;
v___y_2014_ = v___x_2024_;
v___y_2015_ = v___y_2023_;
v___y_2016_ = v___x_2025_;
goto v___jp_2012_;
}
else
{
v___y_2013_ = v___y_2022_;
v___y_2014_ = v___x_2024_;
v___y_2015_ = v___y_2023_;
v___y_2016_ = v___y_2022_;
goto v___jp_2012_;
}
}
v___jp_2028_:
{
uint64_t v___x_2033_; uint64_t v___x_2034_; uint8_t v___x_2035_; 
v___x_2033_ = lean_uint64_shift_right(v___y_2030_, v___y_2029_);
v___x_2034_ = 0ULL;
v___x_2035_ = lean_uint64_dec_eq(v___x_2033_, v___x_2034_);
if (v___x_2035_ == 0)
{
uint64_t v___x_2036_; 
v___x_2036_ = lean_uint64_add(v___y_2031_, v___y_2029_);
v___y_2022_ = v___y_2032_;
v___y_2023_ = v___x_2036_;
goto v___jp_2021_;
}
else
{
v___y_2022_ = v___y_2032_;
v___y_2023_ = v___y_2031_;
goto v___jp_2021_;
}
}
v___jp_2037_:
{
uint64_t v___x_2040_; uint64_t v___x_2041_; uint64_t v___x_2042_; uint8_t v___x_2043_; 
v___x_2040_ = 4ULL;
v___x_2041_ = lean_uint64_shift_right(v___y_2038_, v___x_2040_);
v___x_2042_ = 0ULL;
v___x_2043_ = lean_uint64_dec_eq(v___x_2041_, v___x_2042_);
if (v___x_2043_ == 0)
{
v___y_2029_ = v___x_2040_;
v___y_2030_ = v___y_2038_;
v___y_2031_ = v___y_2039_;
v___y_2032_ = v___x_2041_;
goto v___jp_2028_;
}
else
{
v___y_2029_ = v___x_2040_;
v___y_2030_ = v___y_2038_;
v___y_2031_ = v___y_2039_;
v___y_2032_ = v___y_2038_;
goto v___jp_2028_;
}
}
v___jp_2044_:
{
uint64_t v___x_2049_; uint64_t v___x_2050_; uint8_t v___x_2051_; 
v___x_2049_ = lean_uint64_shift_right(v___y_2045_, v___y_2047_);
v___x_2050_ = 0ULL;
v___x_2051_ = lean_uint64_dec_eq(v___x_2049_, v___x_2050_);
if (v___x_2051_ == 0)
{
uint64_t v___x_2052_; 
v___x_2052_ = lean_uint64_add(v___y_2046_, v___y_2047_);
v___y_2038_ = v___y_2048_;
v___y_2039_ = v___x_2052_;
goto v___jp_2037_;
}
else
{
v___y_2038_ = v___y_2048_;
v___y_2039_ = v___y_2046_;
goto v___jp_2037_;
}
}
v___jp_2053_:
{
uint64_t v___x_2056_; uint64_t v___x_2057_; uint64_t v___x_2058_; uint8_t v___x_2059_; 
v___x_2056_ = 8ULL;
v___x_2057_ = lean_uint64_shift_right(v___y_2054_, v___x_2056_);
v___x_2058_ = 0ULL;
v___x_2059_ = lean_uint64_dec_eq(v___x_2057_, v___x_2058_);
if (v___x_2059_ == 0)
{
v___y_2045_ = v___y_2054_;
v___y_2046_ = v___y_2055_;
v___y_2047_ = v___x_2056_;
v___y_2048_ = v___x_2057_;
goto v___jp_2044_;
}
else
{
v___y_2045_ = v___y_2054_;
v___y_2046_ = v___y_2055_;
v___y_2047_ = v___x_2056_;
v___y_2048_ = v___y_2054_;
goto v___jp_2044_;
}
}
v___jp_2060_:
{
uint64_t v___x_2065_; uint64_t v___x_2066_; uint8_t v___x_2067_; 
v___x_2065_ = lean_uint64_shift_right(v___y_2061_, v___y_2062_);
v___x_2066_ = 0ULL;
v___x_2067_ = lean_uint64_dec_eq(v___x_2065_, v___x_2066_);
if (v___x_2067_ == 0)
{
uint64_t v___x_2068_; 
v___x_2068_ = lean_uint64_add(v___y_2063_, v___y_2062_);
v___y_2054_ = v___y_2064_;
v___y_2055_ = v___x_2068_;
goto v___jp_2053_;
}
else
{
v___y_2054_ = v___y_2064_;
v___y_2055_ = v___y_2063_;
goto v___jp_2053_;
}
}
v___jp_2069_:
{
uint64_t v___x_2072_; uint64_t v___x_2073_; uint64_t v___x_2074_; uint8_t v___x_2075_; 
v___x_2072_ = 16ULL;
v___x_2073_ = lean_uint64_shift_right(v___y_2070_, v___x_2072_);
v___x_2074_ = 0ULL;
v___x_2075_ = lean_uint64_dec_eq(v___x_2073_, v___x_2074_);
if (v___x_2075_ == 0)
{
v___y_2061_ = v___y_2070_;
v___y_2062_ = v___x_2072_;
v___y_2063_ = v___y_2071_;
v___y_2064_ = v___x_2073_;
goto v___jp_2060_;
}
else
{
v___y_2061_ = v___y_2070_;
v___y_2062_ = v___x_2072_;
v___y_2063_ = v___y_2071_;
v___y_2064_ = v___y_2070_;
goto v___jp_2060_;
}
}
v___jp_2077_:
{
uint64_t v___x_2079_; uint64_t v___x_2080_; uint8_t v___x_2081_; 
v___x_2079_ = lean_uint64_shift_right(v_x0_2003_, v___x_2076_);
v___x_2080_ = 0ULL;
v___x_2081_ = lean_uint64_dec_eq(v___x_2079_, v___x_2080_);
if (v___x_2081_ == 0)
{
v___y_2070_ = v___y_2078_;
v___y_2071_ = v___x_2076_;
goto v___jp_2069_;
}
else
{
v___y_2070_ = v___y_2078_;
v___y_2071_ = v___x_2080_;
goto v___jp_2069_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fastLog2___boxed(lean_object* v_x0_2085_){
_start:
{
uint64_t v_x0_boxed_2086_; uint64_t v_res_2087_; lean_object* v_r_2088_; 
v_x0_boxed_2086_ = lean_unbox_uint64(v_x0_2085_);
lean_dec_ref(v_x0_2085_);
v_res_2087_ = lp_competition_Submission_FastMul_fastLog2(v_x0_boxed_2086_);
v_r_2088_ = lean_box_uint64(v_res_2087_);
return v_r_2088_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rse(uint64_t v_value_2089_, uint64_t v_shift_2090_){
_start:
{
uint64_t v_quotient_2091_; uint64_t v___x_2092_; uint64_t v___x_2093_; uint64_t v___x_2094_; uint64_t v_remainder_2095_; uint64_t v___x_2096_; uint64_t v_half_2097_; uint8_t v___x_2098_; 
v_quotient_2091_ = lean_uint64_shift_right(v_value_2089_, v_shift_2090_);
v___x_2092_ = 1ULL;
v___x_2093_ = lean_uint64_shift_left(v___x_2092_, v_shift_2090_);
v___x_2094_ = lean_uint64_sub(v___x_2093_, v___x_2092_);
v_remainder_2095_ = lean_uint64_land(v_value_2089_, v___x_2094_);
v___x_2096_ = lean_uint64_sub(v_shift_2090_, v___x_2092_);
v_half_2097_ = lean_uint64_shift_left(v___x_2092_, v___x_2096_);
v___x_2098_ = lean_uint64_dec_lt(v_remainder_2095_, v_half_2097_);
if (v___x_2098_ == 0)
{
uint8_t v___x_2099_; 
v___x_2099_ = lean_uint64_dec_lt(v_half_2097_, v_remainder_2095_);
if (v___x_2099_ == 0)
{
uint64_t v___x_2100_; uint64_t v___x_2101_; uint8_t v___x_2102_; 
v___x_2100_ = lean_uint64_land(v_quotient_2091_, v___x_2092_);
v___x_2101_ = 0ULL;
v___x_2102_ = lean_uint64_dec_eq(v___x_2100_, v___x_2101_);
if (v___x_2102_ == 0)
{
uint64_t v___x_2103_; 
v___x_2103_ = lean_uint64_add(v_quotient_2091_, v___x_2092_);
return v___x_2103_;
}
else
{
return v_quotient_2091_;
}
}
else
{
uint64_t v___x_2104_; 
v___x_2104_ = lean_uint64_add(v_quotient_2091_, v___x_2092_);
return v___x_2104_;
}
}
else
{
return v_quotient_2091_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rse___boxed(lean_object* v_value_2105_, lean_object* v_shift_2106_){
_start:
{
uint64_t v_value_boxed_2107_; uint64_t v_shift_boxed_2108_; uint64_t v_res_2109_; lean_object* v_r_2110_; 
v_value_boxed_2107_ = lean_unbox_uint64(v_value_2105_);
lean_dec_ref(v_value_2105_);
v_shift_boxed_2108_ = lean_unbox_uint64(v_shift_2106_);
lean_dec_ref(v_shift_2106_);
v_res_2109_ = lp_competition_Submission_FastMul_rse(v_value_boxed_2107_, v_shift_boxed_2108_);
v_r_2110_ = lean_box_uint64(v_res_2109_);
return v_r_2110_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rseAny(uint64_t v_value_2111_, uint64_t v_shift_2112_){
_start:
{
uint64_t v___x_2113_; uint8_t v___x_2114_; 
v___x_2113_ = 0ULL;
v___x_2114_ = lean_uint64_dec_eq(v_shift_2112_, v___x_2113_);
if (v___x_2114_ == 0)
{
uint64_t v___x_2115_; uint8_t v___x_2116_; 
v___x_2115_ = 64ULL;
v___x_2116_ = lean_uint64_dec_lt(v_shift_2112_, v___x_2115_);
if (v___x_2116_ == 0)
{
uint8_t v___x_2117_; 
v___x_2117_ = lean_uint64_dec_eq(v_shift_2112_, v___x_2115_);
if (v___x_2117_ == 0)
{
return v___x_2113_;
}
else
{
uint64_t v___x_2118_; uint8_t v___x_2119_; 
v___x_2118_ = 9223372036854775808ULL;
v___x_2119_ = lean_uint64_dec_lt(v___x_2118_, v_value_2111_);
if (v___x_2119_ == 0)
{
return v___x_2113_;
}
else
{
uint64_t v___x_2120_; 
v___x_2120_ = 1ULL;
return v___x_2120_;
}
}
}
else
{
uint64_t v_quotient_2121_; uint64_t v___x_2122_; uint64_t v___x_2123_; uint64_t v___x_2124_; uint64_t v_remainder_2125_; uint64_t v___x_2126_; uint64_t v_half_2127_; uint8_t v___x_2128_; 
v_quotient_2121_ = lean_uint64_shift_right(v_value_2111_, v_shift_2112_);
v___x_2122_ = 1ULL;
v___x_2123_ = lean_uint64_shift_left(v___x_2122_, v_shift_2112_);
v___x_2124_ = lean_uint64_sub(v___x_2123_, v___x_2122_);
v_remainder_2125_ = lean_uint64_land(v_value_2111_, v___x_2124_);
v___x_2126_ = lean_uint64_sub(v_shift_2112_, v___x_2122_);
v_half_2127_ = lean_uint64_shift_left(v___x_2122_, v___x_2126_);
v___x_2128_ = lean_uint64_dec_lt(v_remainder_2125_, v_half_2127_);
if (v___x_2128_ == 0)
{
uint8_t v___x_2129_; 
v___x_2129_ = lean_uint64_dec_lt(v_half_2127_, v_remainder_2125_);
if (v___x_2129_ == 0)
{
uint64_t v___x_2130_; uint8_t v___x_2131_; 
v___x_2130_ = lean_uint64_land(v_quotient_2121_, v___x_2122_);
v___x_2131_ = lean_uint64_dec_eq(v___x_2130_, v___x_2113_);
if (v___x_2131_ == 0)
{
uint64_t v___x_2132_; 
v___x_2132_ = lean_uint64_add(v_quotient_2121_, v___x_2122_);
return v___x_2132_;
}
else
{
return v_quotient_2121_;
}
}
else
{
uint64_t v___x_2133_; 
v___x_2133_ = lean_uint64_add(v_quotient_2121_, v___x_2122_);
return v___x_2133_;
}
}
else
{
return v_quotient_2121_;
}
}
}
else
{
return v_value_2111_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rseAny___boxed(lean_object* v_value_2134_, lean_object* v_shift_2135_){
_start:
{
uint64_t v_value_boxed_2136_; uint64_t v_shift_boxed_2137_; uint64_t v_res_2138_; lean_object* v_r_2139_; 
v_value_boxed_2136_ = lean_unbox_uint64(v_value_2134_);
lean_dec_ref(v_value_2134_);
v_shift_boxed_2137_ = lean_unbox_uint64(v_shift_2135_);
lean_dec_ref(v_shift_2135_);
v_res_2138_ = lp_competition_Submission_FastMul_rseAny(v_value_boxed_2136_, v_shift_boxed_2137_);
v_r_2139_ = lean_box_uint64(v_res_2138_);
return v_r_2139_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mkW(uint8_t v_sign_2140_, uint32_t v_e_2141_, uint32_t v_f_2142_){
_start:
{
uint32_t v___y_2144_; 
if (v_sign_2140_ == 0)
{
uint32_t v___x_2153_; 
v___x_2153_ = 0;
v___y_2144_ = v___x_2153_;
goto v___jp_2143_;
}
else
{
uint32_t v___x_2154_; 
v___x_2154_ = 2147483648;
v___y_2144_ = v___x_2154_;
goto v___jp_2143_;
}
v___jp_2143_:
{
uint32_t v___x_2145_; uint32_t v___x_2146_; uint32_t v___x_2147_; uint32_t v___x_2148_; uint32_t v___x_2149_; uint32_t v___x_2150_; uint32_t v___x_2151_; uint32_t v___x_2152_; 
v___x_2145_ = 255;
v___x_2146_ = lean_uint32_land(v_e_2141_, v___x_2145_);
v___x_2147_ = 23;
v___x_2148_ = lean_uint32_shift_left(v___x_2146_, v___x_2147_);
v___x_2149_ = lean_uint32_lor(v___y_2144_, v___x_2148_);
v___x_2150_ = 8388607;
v___x_2151_ = lean_uint32_land(v_f_2142_, v___x_2150_);
v___x_2152_ = lean_uint32_lor(v___x_2149_, v___x_2151_);
return v___x_2152_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mkW___boxed(lean_object* v_sign_2155_, lean_object* v_e_2156_, lean_object* v_f_2157_){
_start:
{
uint8_t v_sign_boxed_2158_; uint32_t v_e_boxed_2159_; uint32_t v_f_boxed_2160_; uint32_t v_res_2161_; lean_object* v_r_2162_; 
v_sign_boxed_2158_ = lean_unbox(v_sign_2155_);
v_e_boxed_2159_ = lean_unbox_uint32(v_e_2156_);
lean_dec(v_e_2156_);
v_f_boxed_2160_ = lean_unbox_uint32(v_f_2157_);
lean_dec(v_f_2157_);
v_res_2161_ = lp_competition_Submission_FastMul_mkW(v_sign_boxed_2158_, v_e_boxed_2159_, v_f_boxed_2160_);
v_r_2162_ = lean_box_uint32(v_res_2161_);
return v_r_2162_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_fracW(uint64_t v_n_2163_){
_start:
{
uint64_t v___x_2164_; uint8_t v___x_2165_; 
v___x_2164_ = 8388608ULL;
v___x_2165_ = lean_uint64_dec_lt(v_n_2163_, v___x_2164_);
if (v___x_2165_ == 0)
{
uint64_t v___x_2166_; uint32_t v___x_2167_; 
v___x_2166_ = lean_uint64_sub(v_n_2163_, v___x_2164_);
v___x_2167_ = lean_uint64_to_uint32(v___x_2166_);
return v___x_2167_;
}
else
{
uint32_t v___x_2168_; 
v___x_2168_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
return v___x_2168_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fracW___boxed(lean_object* v_n_2169_){
_start:
{
uint64_t v_n_boxed_2170_; uint32_t v_res_2171_; lean_object* v_r_2172_; 
v_n_boxed_2170_ = lean_unbox_uint64(v_n_2169_);
lean_dec_ref(v_n_2169_);
v_res_2171_ = lp_competition_Submission_FastMul_fracW(v_n_boxed_2170_);
v_r_2172_ = lean_box_uint32(v_res_2171_);
return v_r_2172_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_roundP(uint8_t v_sign_2173_, uint64_t v_product_2174_, uint64_t v_scale_2175_){
_start:
{
uint32_t v___y_2177_; uint32_t v___y_2181_; uint32_t v___y_2182_; uint32_t v___y_2187_; uint32_t v___y_2188_; uint32_t v___y_2189_; uint32_t v___y_2199_; uint32_t v___y_2200_; uint64_t v___x_2203_; uint64_t v___y_2205_; uint64_t v___y_2217_; uint64_t v___y_2218_; uint8_t v___y_2228_; uint64_t v___y_2229_; uint64_t v___y_2230_; uint64_t v___y_2237_; uint64_t v___y_2238_; uint64_t v___y_2244_; uint64_t v___y_2299_; uint64_t v___y_2300_; uint64_t v___y_2306_; uint64_t v___y_2307_; uint64_t v___y_2308_; uint64_t v___y_2309_; uint64_t v___y_2314_; uint64_t v___y_2315_; uint64_t v___y_2320_; uint64_t v___y_2321_; uint64_t v___y_2322_; uint64_t v___y_2323_; uint64_t v___y_2328_; uint64_t v___y_2329_; uint64_t v___y_2334_; uint64_t v___y_2335_; uint64_t v___y_2336_; uint64_t v___y_2337_; uint64_t v___y_2342_; uint64_t v___y_2343_; uint64_t v___y_2348_; uint64_t v___y_2349_; uint64_t v___y_2350_; uint64_t v___y_2351_; uint64_t v___y_2356_; uint64_t v___y_2357_; uint8_t v___x_2361_; 
v___x_2203_ = 0ULL;
v___x_2361_ = lean_uint64_dec_eq(v_product_2174_, v___x_2203_);
if (v___x_2361_ == 0)
{
uint64_t v___x_2362_; uint64_t v___y_2364_; uint64_t v___x_2367_; uint8_t v___x_2368_; 
v___x_2362_ = 32ULL;
v___x_2367_ = lean_uint64_shift_right(v_product_2174_, v___x_2362_);
v___x_2368_ = lean_uint64_dec_eq(v___x_2367_, v___x_2203_);
if (v___x_2368_ == 0)
{
v___y_2364_ = v___x_2367_;
goto v___jp_2363_;
}
else
{
v___y_2364_ = v_product_2174_;
goto v___jp_2363_;
}
v___jp_2363_:
{
uint64_t v___x_2365_; uint8_t v___x_2366_; 
v___x_2365_ = lean_uint64_shift_right(v_product_2174_, v___x_2362_);
v___x_2366_ = lean_uint64_dec_eq(v___x_2365_, v___x_2203_);
if (v___x_2366_ == 0)
{
v___y_2356_ = v___y_2364_;
v___y_2357_ = v___x_2362_;
goto v___jp_2355_;
}
else
{
v___y_2356_ = v___y_2364_;
v___y_2357_ = v___x_2203_;
goto v___jp_2355_;
}
}
}
else
{
if (v_sign_2173_ == 0)
{
uint32_t v___x_2369_; 
v___x_2369_ = 0;
return v___x_2369_;
}
else
{
uint32_t v___x_2370_; 
v___x_2370_ = 2147483648;
return v___x_2370_;
}
}
v___jp_2176_:
{
uint32_t v___x_2178_; uint32_t v___x_2179_; 
v___x_2178_ = 8388608;
v___x_2179_ = lean_uint32_lor(v___y_2177_, v___x_2178_);
return v___x_2179_;
}
v___jp_2180_:
{
uint32_t v___x_2183_; uint32_t v___x_2184_; uint32_t v___x_2185_; 
v___x_2183_ = 8388607;
v___x_2184_ = lean_uint32_land(v___y_2181_, v___x_2183_);
v___x_2185_ = lean_uint32_lor(v___y_2182_, v___x_2184_);
return v___x_2185_;
}
v___jp_2186_:
{
uint32_t v___x_2190_; uint32_t v___x_2191_; uint32_t v___x_2192_; uint32_t v___x_2193_; uint32_t v___x_2194_; uint32_t v___x_2195_; uint32_t v___x_2196_; uint32_t v___x_2197_; 
v___x_2190_ = 255;
v___x_2191_ = lean_uint32_land(v___y_2188_, v___x_2190_);
v___x_2192_ = 23;
v___x_2193_ = lean_uint32_shift_left(v___x_2191_, v___x_2192_);
v___x_2194_ = lean_uint32_lor(v___y_2189_, v___x_2193_);
v___x_2195_ = 8388607;
v___x_2196_ = lean_uint32_land(v___y_2187_, v___x_2195_);
v___x_2197_ = lean_uint32_lor(v___x_2194_, v___x_2196_);
return v___x_2197_;
}
v___jp_2198_:
{
if (v_sign_2173_ == 0)
{
uint32_t v___x_2201_; 
v___x_2201_ = 0;
v___y_2187_ = v___y_2200_;
v___y_2188_ = v___y_2199_;
v___y_2189_ = v___x_2201_;
goto v___jp_2186_;
}
else
{
uint32_t v___x_2202_; 
v___x_2202_ = 2147483648;
v___y_2187_ = v___y_2200_;
v___y_2188_ = v___y_2199_;
v___y_2189_ = v___x_2202_;
goto v___jp_2186_;
}
}
v___jp_2204_:
{
uint8_t v___x_2206_; 
v___x_2206_ = lean_uint64_dec_eq(v___y_2205_, v___x_2203_);
if (v___x_2206_ == 0)
{
uint64_t v___x_2207_; uint8_t v___x_2208_; 
v___x_2207_ = 8388608ULL;
v___x_2208_ = lean_uint64_dec_eq(v___y_2205_, v___x_2207_);
if (v___x_2208_ == 0)
{
uint32_t v___x_2209_; 
v___x_2209_ = lean_uint64_to_uint32(v___y_2205_);
if (v_sign_2173_ == 0)
{
uint32_t v___x_2210_; 
v___x_2210_ = 0;
v___y_2181_ = v___x_2209_;
v___y_2182_ = v___x_2210_;
goto v___jp_2180_;
}
else
{
uint32_t v___x_2211_; 
v___x_2211_ = 2147483648;
v___y_2181_ = v___x_2209_;
v___y_2182_ = v___x_2211_;
goto v___jp_2180_;
}
}
else
{
if (v_sign_2173_ == 0)
{
uint32_t v___x_2212_; 
v___x_2212_ = 0;
v___y_2177_ = v___x_2212_;
goto v___jp_2176_;
}
else
{
uint32_t v___x_2213_; 
v___x_2213_ = 2147483648;
v___y_2177_ = v___x_2213_;
goto v___jp_2176_;
}
}
}
else
{
if (v_sign_2173_ == 0)
{
uint32_t v___x_2214_; 
v___x_2214_ = 0;
return v___x_2214_;
}
else
{
uint32_t v___x_2215_; 
v___x_2215_ = 2147483648;
return v___x_2215_;
}
}
}
v___jp_2216_:
{
uint64_t v___x_2219_; uint64_t v_encodedExponent_2220_; uint32_t v___x_2221_; uint64_t v___x_2222_; uint8_t v___x_2223_; 
v___x_2219_ = 171ULL;
v_encodedExponent_2220_ = lean_uint64_sub(v___y_2217_, v___x_2219_);
v___x_2221_ = lean_uint64_to_uint32(v_encodedExponent_2220_);
v___x_2222_ = 8388608ULL;
v___x_2223_ = lean_uint64_dec_lt(v___y_2218_, v___x_2222_);
if (v___x_2223_ == 0)
{
uint64_t v___x_2224_; uint32_t v___x_2225_; 
v___x_2224_ = lean_uint64_sub(v___y_2218_, v___x_2222_);
v___x_2225_ = lean_uint64_to_uint32(v___x_2224_);
v___y_2199_ = v___x_2221_;
v___y_2200_ = v___x_2225_;
goto v___jp_2198_;
}
else
{
uint32_t v___x_2226_; 
v___x_2226_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_2199_ = v___x_2221_;
v___y_2200_ = v___x_2226_;
goto v___jp_2198_;
}
}
v___jp_2227_:
{
uint64_t v___x_2231_; uint8_t v___x_2232_; 
v___x_2231_ = 425ULL;
v___x_2232_ = lean_uint64_dec_lt(v___x_2231_, v___y_2230_);
if (v___x_2232_ == 0)
{
if (v___y_2228_ == 0)
{
v___y_2217_ = v___y_2230_;
v___y_2218_ = v___y_2229_;
goto v___jp_2216_;
}
else
{
uint64_t v___x_2233_; 
v___x_2233_ = 8388608ULL;
v___y_2217_ = v___y_2230_;
v___y_2218_ = v___x_2233_;
goto v___jp_2216_;
}
}
else
{
if (v_sign_2173_ == 0)
{
uint32_t v___x_2234_; 
v___x_2234_ = 2139095040;
return v___x_2234_;
}
else
{
uint32_t v___x_2235_; 
v___x_2235_ = 4286578688;
return v___x_2235_;
}
}
}
v___jp_2236_:
{
uint64_t v___x_2239_; uint8_t v_carry_2240_; 
v___x_2239_ = 16777216ULL;
v_carry_2240_ = lean_uint64_dec_eq(v___y_2238_, v___x_2239_);
if (v_carry_2240_ == 0)
{
v___y_2228_ = v_carry_2240_;
v___y_2229_ = v___y_2238_;
v___y_2230_ = v___y_2237_;
goto v___jp_2227_;
}
else
{
uint64_t v___x_2241_; uint64_t v___x_2242_; 
v___x_2241_ = 1ULL;
v___x_2242_ = lean_uint64_add(v___y_2237_, v___x_2241_);
v___y_2228_ = v_carry_2240_;
v___y_2229_ = v___y_2238_;
v___y_2230_ = v___x_2242_;
goto v___jp_2227_;
}
}
v___jp_2243_:
{
uint64_t v_position_2245_; uint64_t v___x_2246_; uint8_t v___x_2247_; 
v_position_2245_ = lean_uint64_add(v___y_2244_, v_scale_2175_);
v___x_2246_ = 172ULL;
v___x_2247_ = lean_uint64_dec_lt(v_position_2245_, v___x_2246_);
if (v___x_2247_ == 0)
{
uint64_t v___x_2248_; uint8_t v___x_2249_; 
v___x_2248_ = 23ULL;
v___x_2249_ = lean_uint64_dec_lt(v___y_2244_, v___x_2248_);
if (v___x_2249_ == 0)
{
uint64_t v___x_2250_; uint8_t v___x_2251_; 
v___x_2250_ = lean_uint64_sub(v___y_2244_, v___x_2248_);
v___x_2251_ = lean_uint64_dec_eq(v___x_2250_, v___x_2203_);
if (v___x_2251_ == 0)
{
uint64_t v___x_2252_; uint8_t v___x_2253_; 
v___x_2252_ = 64ULL;
v___x_2253_ = lean_uint64_dec_lt(v___x_2250_, v___x_2252_);
if (v___x_2253_ == 0)
{
uint8_t v___x_2254_; 
v___x_2254_ = lean_uint64_dec_eq(v___x_2250_, v___x_2252_);
if (v___x_2254_ == 0)
{
v___y_2237_ = v_position_2245_;
v___y_2238_ = v___x_2203_;
goto v___jp_2236_;
}
else
{
uint64_t v___x_2255_; uint8_t v___x_2256_; 
v___x_2255_ = 9223372036854775808ULL;
v___x_2256_ = lean_uint64_dec_lt(v___x_2255_, v_product_2174_);
if (v___x_2256_ == 0)
{
v___y_2237_ = v_position_2245_;
v___y_2238_ = v___x_2203_;
goto v___jp_2236_;
}
else
{
uint64_t v___x_2257_; 
v___x_2257_ = 1ULL;
v___y_2237_ = v_position_2245_;
v___y_2238_ = v___x_2257_;
goto v___jp_2236_;
}
}
}
else
{
uint64_t v_quotient_2258_; uint64_t v___x_2259_; uint64_t v___x_2260_; uint64_t v___x_2261_; uint64_t v_remainder_2262_; uint64_t v___x_2263_; uint64_t v_half_2264_; uint8_t v___x_2265_; 
v_quotient_2258_ = lean_uint64_shift_right(v_product_2174_, v___x_2250_);
v___x_2259_ = 1ULL;
v___x_2260_ = lean_uint64_shift_left(v___x_2259_, v___x_2250_);
v___x_2261_ = lean_uint64_sub(v___x_2260_, v___x_2259_);
v_remainder_2262_ = lean_uint64_land(v_product_2174_, v___x_2261_);
v___x_2263_ = lean_uint64_sub(v___x_2250_, v___x_2259_);
v_half_2264_ = lean_uint64_shift_left(v___x_2259_, v___x_2263_);
v___x_2265_ = lean_uint64_dec_lt(v_remainder_2262_, v_half_2264_);
if (v___x_2265_ == 0)
{
uint8_t v___x_2266_; 
v___x_2266_ = lean_uint64_dec_lt(v_half_2264_, v_remainder_2262_);
if (v___x_2266_ == 0)
{
uint64_t v___x_2267_; uint8_t v___x_2268_; 
v___x_2267_ = lean_uint64_land(v_quotient_2258_, v___x_2259_);
v___x_2268_ = lean_uint64_dec_eq(v___x_2267_, v___x_2203_);
if (v___x_2268_ == 0)
{
uint64_t v___x_2269_; 
v___x_2269_ = lean_uint64_add(v_quotient_2258_, v___x_2259_);
v___y_2237_ = v_position_2245_;
v___y_2238_ = v___x_2269_;
goto v___jp_2236_;
}
else
{
v___y_2237_ = v_position_2245_;
v___y_2238_ = v_quotient_2258_;
goto v___jp_2236_;
}
}
else
{
uint64_t v___x_2270_; 
v___x_2270_ = lean_uint64_add(v_quotient_2258_, v___x_2259_);
v___y_2237_ = v_position_2245_;
v___y_2238_ = v___x_2270_;
goto v___jp_2236_;
}
}
else
{
v___y_2237_ = v_position_2245_;
v___y_2238_ = v_quotient_2258_;
goto v___jp_2236_;
}
}
}
else
{
v___y_2237_ = v_position_2245_;
v___y_2238_ = v_product_2174_;
goto v___jp_2236_;
}
}
else
{
uint64_t v___x_2271_; uint64_t v___x_2272_; 
v___x_2271_ = lean_uint64_sub(v___x_2248_, v___y_2244_);
v___x_2272_ = lean_uint64_shift_left(v_product_2174_, v___x_2271_);
v___y_2237_ = v_position_2245_;
v___y_2238_ = v___x_2272_;
goto v___jp_2236_;
}
}
else
{
uint64_t v___x_2273_; uint8_t v___x_2274_; 
v___x_2273_ = 149ULL;
v___x_2274_ = lean_uint64_dec_lt(v_scale_2175_, v___x_2273_);
if (v___x_2274_ == 0)
{
uint64_t v___x_2275_; uint64_t v___x_2276_; 
v___x_2275_ = lean_uint64_sub(v_scale_2175_, v___x_2273_);
v___x_2276_ = lean_uint64_shift_left(v_product_2174_, v___x_2275_);
v___y_2205_ = v___x_2276_;
goto v___jp_2204_;
}
else
{
uint64_t v___x_2277_; uint8_t v___x_2278_; 
v___x_2277_ = lean_uint64_sub(v___x_2273_, v_scale_2175_);
v___x_2278_ = lean_uint64_dec_eq(v___x_2277_, v___x_2203_);
if (v___x_2278_ == 0)
{
uint64_t v___x_2279_; uint8_t v___x_2280_; 
v___x_2279_ = 64ULL;
v___x_2280_ = lean_uint64_dec_lt(v___x_2277_, v___x_2279_);
if (v___x_2280_ == 0)
{
uint8_t v___x_2281_; 
v___x_2281_ = lean_uint64_dec_eq(v___x_2277_, v___x_2279_);
if (v___x_2281_ == 0)
{
v___y_2205_ = v___x_2203_;
goto v___jp_2204_;
}
else
{
uint64_t v___x_2282_; uint8_t v___x_2283_; 
v___x_2282_ = 9223372036854775808ULL;
v___x_2283_ = lean_uint64_dec_lt(v___x_2282_, v_product_2174_);
if (v___x_2283_ == 0)
{
v___y_2205_ = v___x_2203_;
goto v___jp_2204_;
}
else
{
uint64_t v___x_2284_; 
v___x_2284_ = 1ULL;
v___y_2205_ = v___x_2284_;
goto v___jp_2204_;
}
}
}
else
{
uint64_t v_quotient_2285_; uint64_t v___x_2286_; uint64_t v___x_2287_; uint64_t v___x_2288_; uint64_t v_remainder_2289_; uint64_t v___x_2290_; uint64_t v_half_2291_; uint8_t v___x_2292_; 
v_quotient_2285_ = lean_uint64_shift_right(v_product_2174_, v___x_2277_);
v___x_2286_ = 1ULL;
v___x_2287_ = lean_uint64_shift_left(v___x_2286_, v___x_2277_);
v___x_2288_ = lean_uint64_sub(v___x_2287_, v___x_2286_);
v_remainder_2289_ = lean_uint64_land(v_product_2174_, v___x_2288_);
v___x_2290_ = lean_uint64_sub(v___x_2277_, v___x_2286_);
v_half_2291_ = lean_uint64_shift_left(v___x_2286_, v___x_2290_);
v___x_2292_ = lean_uint64_dec_lt(v_remainder_2289_, v_half_2291_);
if (v___x_2292_ == 0)
{
uint8_t v___x_2293_; 
v___x_2293_ = lean_uint64_dec_lt(v_half_2291_, v_remainder_2289_);
if (v___x_2293_ == 0)
{
uint64_t v___x_2294_; uint8_t v___x_2295_; 
v___x_2294_ = lean_uint64_land(v_quotient_2285_, v___x_2286_);
v___x_2295_ = lean_uint64_dec_eq(v___x_2294_, v___x_2203_);
if (v___x_2295_ == 0)
{
uint64_t v___x_2296_; 
v___x_2296_ = lean_uint64_add(v_quotient_2285_, v___x_2286_);
v___y_2205_ = v___x_2296_;
goto v___jp_2204_;
}
else
{
v___y_2205_ = v_quotient_2285_;
goto v___jp_2204_;
}
}
else
{
uint64_t v___x_2297_; 
v___x_2297_ = lean_uint64_add(v_quotient_2285_, v___x_2286_);
v___y_2205_ = v___x_2297_;
goto v___jp_2204_;
}
}
else
{
v___y_2205_ = v_quotient_2285_;
goto v___jp_2204_;
}
}
}
else
{
v___y_2205_ = v_product_2174_;
goto v___jp_2204_;
}
}
}
}
v___jp_2298_:
{
uint64_t v___x_2301_; uint64_t v___x_2302_; uint8_t v___x_2303_; 
v___x_2301_ = 1ULL;
v___x_2302_ = lean_uint64_shift_right(v___y_2299_, v___x_2301_);
v___x_2303_ = lean_uint64_dec_eq(v___x_2302_, v___x_2203_);
if (v___x_2303_ == 0)
{
uint64_t v___x_2304_; 
v___x_2304_ = lean_uint64_add(v___y_2300_, v___x_2301_);
v___y_2244_ = v___x_2304_;
goto v___jp_2243_;
}
else
{
v___y_2244_ = v___y_2300_;
goto v___jp_2243_;
}
}
v___jp_2305_:
{
uint64_t v___x_2310_; uint8_t v___x_2311_; 
v___x_2310_ = lean_uint64_shift_right(v___y_2307_, v___y_2308_);
v___x_2311_ = lean_uint64_dec_eq(v___x_2310_, v___x_2203_);
if (v___x_2311_ == 0)
{
uint64_t v___x_2312_; 
v___x_2312_ = lean_uint64_add(v___y_2306_, v___y_2308_);
v___y_2299_ = v___y_2309_;
v___y_2300_ = v___x_2312_;
goto v___jp_2298_;
}
else
{
v___y_2299_ = v___y_2309_;
v___y_2300_ = v___y_2306_;
goto v___jp_2298_;
}
}
v___jp_2313_:
{
uint64_t v___x_2316_; uint64_t v___x_2317_; uint8_t v___x_2318_; 
v___x_2316_ = 2ULL;
v___x_2317_ = lean_uint64_shift_right(v___y_2314_, v___x_2316_);
v___x_2318_ = lean_uint64_dec_eq(v___x_2317_, v___x_2203_);
if (v___x_2318_ == 0)
{
v___y_2306_ = v___y_2315_;
v___y_2307_ = v___y_2314_;
v___y_2308_ = v___x_2316_;
v___y_2309_ = v___x_2317_;
goto v___jp_2305_;
}
else
{
v___y_2306_ = v___y_2315_;
v___y_2307_ = v___y_2314_;
v___y_2308_ = v___x_2316_;
v___y_2309_ = v___y_2314_;
goto v___jp_2305_;
}
}
v___jp_2319_:
{
uint64_t v___x_2324_; uint8_t v___x_2325_; 
v___x_2324_ = lean_uint64_shift_right(v___y_2322_, v___y_2321_);
v___x_2325_ = lean_uint64_dec_eq(v___x_2324_, v___x_2203_);
if (v___x_2325_ == 0)
{
uint64_t v___x_2326_; 
v___x_2326_ = lean_uint64_add(v___y_2320_, v___y_2321_);
v___y_2314_ = v___y_2323_;
v___y_2315_ = v___x_2326_;
goto v___jp_2313_;
}
else
{
v___y_2314_ = v___y_2323_;
v___y_2315_ = v___y_2320_;
goto v___jp_2313_;
}
}
v___jp_2327_:
{
uint64_t v___x_2330_; uint64_t v___x_2331_; uint8_t v___x_2332_; 
v___x_2330_ = 4ULL;
v___x_2331_ = lean_uint64_shift_right(v___y_2328_, v___x_2330_);
v___x_2332_ = lean_uint64_dec_eq(v___x_2331_, v___x_2203_);
if (v___x_2332_ == 0)
{
v___y_2320_ = v___y_2329_;
v___y_2321_ = v___x_2330_;
v___y_2322_ = v___y_2328_;
v___y_2323_ = v___x_2331_;
goto v___jp_2319_;
}
else
{
v___y_2320_ = v___y_2329_;
v___y_2321_ = v___x_2330_;
v___y_2322_ = v___y_2328_;
v___y_2323_ = v___y_2328_;
goto v___jp_2319_;
}
}
v___jp_2333_:
{
uint64_t v___x_2338_; uint8_t v___x_2339_; 
v___x_2338_ = lean_uint64_shift_right(v___y_2336_, v___y_2334_);
v___x_2339_ = lean_uint64_dec_eq(v___x_2338_, v___x_2203_);
if (v___x_2339_ == 0)
{
uint64_t v___x_2340_; 
v___x_2340_ = lean_uint64_add(v___y_2335_, v___y_2334_);
v___y_2328_ = v___y_2337_;
v___y_2329_ = v___x_2340_;
goto v___jp_2327_;
}
else
{
v___y_2328_ = v___y_2337_;
v___y_2329_ = v___y_2335_;
goto v___jp_2327_;
}
}
v___jp_2341_:
{
uint64_t v___x_2344_; uint64_t v___x_2345_; uint8_t v___x_2346_; 
v___x_2344_ = 8ULL;
v___x_2345_ = lean_uint64_shift_right(v___y_2342_, v___x_2344_);
v___x_2346_ = lean_uint64_dec_eq(v___x_2345_, v___x_2203_);
if (v___x_2346_ == 0)
{
v___y_2334_ = v___x_2344_;
v___y_2335_ = v___y_2343_;
v___y_2336_ = v___y_2342_;
v___y_2337_ = v___x_2345_;
goto v___jp_2333_;
}
else
{
v___y_2334_ = v___x_2344_;
v___y_2335_ = v___y_2343_;
v___y_2336_ = v___y_2342_;
v___y_2337_ = v___y_2342_;
goto v___jp_2333_;
}
}
v___jp_2347_:
{
uint64_t v___x_2352_; uint8_t v___x_2353_; 
v___x_2352_ = lean_uint64_shift_right(v___y_2348_, v___y_2349_);
v___x_2353_ = lean_uint64_dec_eq(v___x_2352_, v___x_2203_);
if (v___x_2353_ == 0)
{
uint64_t v___x_2354_; 
v___x_2354_ = lean_uint64_add(v___y_2350_, v___y_2349_);
v___y_2342_ = v___y_2351_;
v___y_2343_ = v___x_2354_;
goto v___jp_2341_;
}
else
{
v___y_2342_ = v___y_2351_;
v___y_2343_ = v___y_2350_;
goto v___jp_2341_;
}
}
v___jp_2355_:
{
uint64_t v___x_2358_; uint64_t v___x_2359_; uint8_t v___x_2360_; 
v___x_2358_ = 16ULL;
v___x_2359_ = lean_uint64_shift_right(v___y_2356_, v___x_2358_);
v___x_2360_ = lean_uint64_dec_eq(v___x_2359_, v___x_2203_);
if (v___x_2360_ == 0)
{
v___y_2348_ = v___y_2356_;
v___y_2349_ = v___x_2358_;
v___y_2350_ = v___y_2357_;
v___y_2351_ = v___x_2359_;
goto v___jp_2347_;
}
else
{
v___y_2348_ = v___y_2356_;
v___y_2349_ = v___x_2358_;
v___y_2350_ = v___y_2357_;
v___y_2351_ = v___y_2356_;
goto v___jp_2347_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_roundP___boxed(lean_object* v_sign_2371_, lean_object* v_product_2372_, lean_object* v_scale_2373_){
_start:
{
uint8_t v_sign_boxed_2374_; uint64_t v_product_boxed_2375_; uint64_t v_scale_boxed_2376_; uint32_t v_res_2377_; lean_object* v_r_2378_; 
v_sign_boxed_2374_ = lean_unbox(v_sign_2371_);
v_product_boxed_2375_ = lean_unbox_uint64(v_product_2372_);
lean_dec_ref(v_product_2372_);
v_scale_boxed_2376_ = lean_unbox_uint64(v_scale_2373_);
lean_dec_ref(v_scale_2373_);
v_res_2377_ = lp_competition_Submission_FastMul_roundP(v_sign_boxed_2374_, v_product_boxed_2375_, v_scale_boxed_2376_);
v_r_2378_ = lean_box_uint32(v_res_2377_);
return v_r_2378_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_core(uint32_t v_xBits_2379_, uint32_t v_yBits_2380_){
_start:
{
uint32_t v___y_2382_; uint32_t v___y_2386_; uint32_t v___y_2387_; uint32_t v___y_2388_; uint64_t v___y_2392_; uint8_t v___y_2393_; uint32_t v___y_2394_; uint64_t v___y_2395_; uint32_t v___x_2406_; uint32_t v___x_2407_; uint32_t v___x_2408_; uint32_t v___y_2410_; uint32_t v___y_2411_; uint32_t v___y_2412_; uint32_t v___y_2413_; uint8_t v___y_2420_; uint32_t v___y_2421_; uint32_t v___y_2422_; uint32_t v___y_2423_; uint64_t v___y_2427_; uint64_t v___y_2428_; uint32_t v___y_2429_; uint8_t v___y_2430_; uint64_t v___y_2431_; uint64_t v___y_2441_; uint64_t v___y_2442_; uint8_t v___y_2443_; uint8_t v___y_2444_; uint32_t v___y_2445_; uint64_t v___y_2446_; uint64_t v___y_2453_; uint32_t v___y_2454_; uint8_t v___y_2455_; uint64_t v___y_2456_; uint64_t v___y_2457_; uint64_t v___y_2463_; uint64_t v___y_2464_; uint8_t v___y_2465_; uint32_t v___y_2466_; uint64_t v___y_2467_; uint64_t v___y_2468_; uint64_t v___y_2523_; uint64_t v___y_2524_; uint32_t v___y_2525_; uint8_t v___y_2526_; uint64_t v___y_2527_; uint64_t v___y_2528_; uint64_t v___y_2529_; uint64_t v___y_2535_; uint64_t v___y_2536_; uint64_t v___y_2537_; uint8_t v___y_2538_; uint32_t v___y_2539_; uint64_t v___y_2540_; uint64_t v___y_2541_; uint64_t v___y_2542_; uint64_t v___y_2543_; uint64_t v___y_2548_; uint64_t v___y_2549_; uint64_t v___y_2550_; uint32_t v___y_2551_; uint8_t v___y_2552_; uint64_t v___y_2553_; uint64_t v___y_2554_; uint64_t v___y_2559_; uint64_t v___y_2560_; uint64_t v___y_2561_; uint64_t v___y_2562_; uint8_t v___y_2563_; uint32_t v___y_2564_; uint64_t v___y_2565_; uint64_t v___y_2566_; uint64_t v___y_2567_; uint64_t v___y_2572_; uint64_t v___y_2573_; uint32_t v___y_2574_; uint8_t v___y_2575_; uint64_t v___y_2576_; uint64_t v___y_2577_; uint64_t v___y_2578_; uint64_t v___y_2583_; uint64_t v___y_2584_; uint64_t v___y_2585_; uint64_t v___y_2586_; uint64_t v___y_2587_; uint8_t v___y_2588_; uint32_t v___y_2589_; uint64_t v___y_2590_; uint64_t v___y_2591_; uint64_t v___y_2596_; uint64_t v___y_2597_; uint64_t v___y_2598_; uint32_t v___y_2599_; uint8_t v___y_2600_; uint64_t v___y_2601_; uint64_t v___y_2602_; uint64_t v___y_2607_; uint64_t v___y_2608_; uint64_t v___y_2609_; uint64_t v___y_2610_; uint8_t v___y_2611_; uint32_t v___y_2612_; uint64_t v___y_2613_; uint64_t v___y_2614_; uint64_t v___y_2615_; uint64_t v___y_2620_; uint64_t v___y_2621_; uint64_t v___y_2622_; uint32_t v___y_2623_; uint8_t v___y_2624_; uint64_t v___y_2625_; uint64_t v___y_2626_; uint64_t v___y_2631_; uint64_t v___y_2632_; uint64_t v___y_2633_; uint8_t v___y_2634_; uint32_t v___y_2635_; uint64_t v___y_2636_; uint64_t v___y_2637_; uint64_t v___y_2641_; uint32_t v___y_2642_; uint8_t v___y_2643_; uint64_t v___y_2644_; uint64_t v___y_2645_; uint64_t v___y_2646_; uint32_t v_xExponent_2656_; uint32_t v___x_2657_; uint32_t v_yExponent_2658_; uint64_t v___y_2660_; uint8_t v___y_2661_; uint32_t v___y_2662_; uint64_t v___y_2663_; uint64_t v___y_2664_; uint64_t v___y_2671_; uint32_t v___y_2672_; uint8_t v___y_2673_; uint64_t v___y_2674_; uint32_t v___y_2681_; uint8_t v___y_2682_; uint32_t v___y_2683_; uint64_t v___y_2684_; uint8_t v___y_2692_; uint8_t v___y_2707_; uint8_t v___y_2708_; uint8_t v___y_2710_; uint32_t v___x_2717_; uint32_t v___x_2718_; uint32_t v___x_2719_; uint8_t v___x_2720_; 
v___x_2406_ = 23;
v___x_2407_ = lean_uint32_shift_right(v_xBits_2379_, v___x_2406_);
v___x_2408_ = 255;
v_xExponent_2656_ = lean_uint32_land(v___x_2407_, v___x_2408_);
v___x_2657_ = lean_uint32_shift_right(v_yBits_2380_, v___x_2406_);
v_yExponent_2658_ = lean_uint32_land(v___x_2657_, v___x_2408_);
v___x_2717_ = 2147483648;
v___x_2718_ = lean_uint32_land(v_xBits_2379_, v___x_2717_);
v___x_2719_ = 0;
v___x_2720_ = lean_uint32_dec_eq(v___x_2718_, v___x_2719_);
if (v___x_2720_ == 0)
{
uint8_t v___x_2721_; 
v___x_2721_ = 1;
v___y_2710_ = v___x_2721_;
goto v___jp_2709_;
}
else
{
uint8_t v___x_2722_; 
v___x_2722_ = 0;
v___y_2710_ = v___x_2722_;
goto v___jp_2709_;
}
v___jp_2381_:
{
uint32_t v___x_2383_; uint32_t v___x_2384_; 
v___x_2383_ = 8388608;
v___x_2384_ = lean_uint32_lor(v___y_2382_, v___x_2383_);
return v___x_2384_;
}
v___jp_2385_:
{
uint32_t v___x_2389_; uint32_t v___x_2390_; 
v___x_2389_ = lean_uint32_land(v___y_2386_, v___y_2387_);
v___x_2390_ = lean_uint32_lor(v___y_2388_, v___x_2389_);
return v___x_2390_;
}
v___jp_2391_:
{
uint8_t v___x_2396_; 
v___x_2396_ = lean_uint64_dec_eq(v___y_2395_, v___y_2392_);
if (v___x_2396_ == 0)
{
uint64_t v___x_2397_; uint8_t v___x_2398_; 
v___x_2397_ = 8388608ULL;
v___x_2398_ = lean_uint64_dec_eq(v___y_2395_, v___x_2397_);
if (v___x_2398_ == 0)
{
uint32_t v___x_2399_; 
v___x_2399_ = lean_uint64_to_uint32(v___y_2395_);
if (v___y_2393_ == 0)
{
uint32_t v___x_2400_; 
v___x_2400_ = 0;
v___y_2386_ = v___x_2399_;
v___y_2387_ = v___y_2394_;
v___y_2388_ = v___x_2400_;
goto v___jp_2385_;
}
else
{
uint32_t v___x_2401_; 
v___x_2401_ = 2147483648;
v___y_2386_ = v___x_2399_;
v___y_2387_ = v___y_2394_;
v___y_2388_ = v___x_2401_;
goto v___jp_2385_;
}
}
else
{
if (v___y_2393_ == 0)
{
uint32_t v___x_2402_; 
v___x_2402_ = 0;
v___y_2382_ = v___x_2402_;
goto v___jp_2381_;
}
else
{
uint32_t v___x_2403_; 
v___x_2403_ = 2147483648;
v___y_2382_ = v___x_2403_;
goto v___jp_2381_;
}
}
}
else
{
if (v___y_2393_ == 0)
{
uint32_t v___x_2404_; 
v___x_2404_ = 0;
return v___x_2404_;
}
else
{
uint32_t v___x_2405_; 
v___x_2405_ = 2147483648;
return v___x_2405_;
}
}
}
v___jp_2409_:
{
uint32_t v___x_2414_; uint32_t v___x_2415_; uint32_t v___x_2416_; uint32_t v___x_2417_; uint32_t v___x_2418_; 
v___x_2414_ = lean_uint32_land(v___y_2411_, v___x_2408_);
v___x_2415_ = lean_uint32_shift_left(v___x_2414_, v___x_2406_);
v___x_2416_ = lean_uint32_lor(v___y_2413_, v___x_2415_);
v___x_2417_ = lean_uint32_land(v___y_2412_, v___y_2410_);
v___x_2418_ = lean_uint32_lor(v___x_2416_, v___x_2417_);
return v___x_2418_;
}
v___jp_2419_:
{
if (v___y_2420_ == 0)
{
uint32_t v___x_2424_; 
v___x_2424_ = 0;
v___y_2410_ = v___y_2422_;
v___y_2411_ = v___y_2421_;
v___y_2412_ = v___y_2423_;
v___y_2413_ = v___x_2424_;
goto v___jp_2409_;
}
else
{
uint32_t v___x_2425_; 
v___x_2425_ = 2147483648;
v___y_2410_ = v___y_2422_;
v___y_2411_ = v___y_2421_;
v___y_2412_ = v___y_2423_;
v___y_2413_ = v___x_2425_;
goto v___jp_2409_;
}
}
v___jp_2426_:
{
uint64_t v___x_2432_; uint64_t v_encodedExponent_2433_; uint32_t v___x_2434_; uint64_t v___x_2435_; uint8_t v___x_2436_; 
v___x_2432_ = 171ULL;
v_encodedExponent_2433_ = lean_uint64_sub(v___y_2428_, v___x_2432_);
v___x_2434_ = lean_uint64_to_uint32(v_encodedExponent_2433_);
v___x_2435_ = 8388608ULL;
v___x_2436_ = lean_uint64_dec_lt(v___y_2431_, v___x_2435_);
if (v___x_2436_ == 0)
{
uint64_t v___x_2437_; uint32_t v___x_2438_; 
v___x_2437_ = lean_uint64_sub(v___y_2431_, v___x_2435_);
v___x_2438_ = lean_uint64_to_uint32(v___x_2437_);
v___y_2420_ = v___y_2430_;
v___y_2421_ = v___x_2434_;
v___y_2422_ = v___y_2429_;
v___y_2423_ = v___x_2438_;
goto v___jp_2419_;
}
else
{
uint32_t v___x_2439_; 
v___x_2439_ = lean_uint64_to_uint32(v___y_2427_);
v___y_2420_ = v___y_2430_;
v___y_2421_ = v___x_2434_;
v___y_2422_ = v___y_2429_;
v___y_2423_ = v___x_2439_;
goto v___jp_2419_;
}
}
v___jp_2440_:
{
uint64_t v___x_2447_; uint8_t v___x_2448_; 
v___x_2447_ = 425ULL;
v___x_2448_ = lean_uint64_dec_lt(v___x_2447_, v___y_2446_);
if (v___x_2448_ == 0)
{
if (v___y_2443_ == 0)
{
v___y_2427_ = v___y_2442_;
v___y_2428_ = v___y_2446_;
v___y_2429_ = v___y_2445_;
v___y_2430_ = v___y_2444_;
v___y_2431_ = v___y_2441_;
goto v___jp_2426_;
}
else
{
uint64_t v___x_2449_; 
v___x_2449_ = 8388608ULL;
v___y_2427_ = v___y_2442_;
v___y_2428_ = v___y_2446_;
v___y_2429_ = v___y_2445_;
v___y_2430_ = v___y_2444_;
v___y_2431_ = v___x_2449_;
goto v___jp_2426_;
}
}
else
{
if (v___y_2444_ == 0)
{
uint32_t v___x_2450_; 
v___x_2450_ = 2139095040;
return v___x_2450_;
}
else
{
uint32_t v___x_2451_; 
v___x_2451_ = 4286578688;
return v___x_2451_;
}
}
}
v___jp_2452_:
{
uint64_t v___x_2458_; uint8_t v_carry_2459_; 
v___x_2458_ = 16777216ULL;
v_carry_2459_ = lean_uint64_dec_eq(v___y_2457_, v___x_2458_);
if (v_carry_2459_ == 0)
{
v___y_2441_ = v___y_2457_;
v___y_2442_ = v___y_2453_;
v___y_2443_ = v_carry_2459_;
v___y_2444_ = v___y_2455_;
v___y_2445_ = v___y_2454_;
v___y_2446_ = v___y_2456_;
goto v___jp_2440_;
}
else
{
uint64_t v___x_2460_; uint64_t v___x_2461_; 
v___x_2460_ = 1ULL;
v___x_2461_ = lean_uint64_add(v___y_2456_, v___x_2460_);
v___y_2441_ = v___y_2457_;
v___y_2442_ = v___y_2453_;
v___y_2443_ = v_carry_2459_;
v___y_2444_ = v___y_2455_;
v___y_2445_ = v___y_2454_;
v___y_2446_ = v___x_2461_;
goto v___jp_2440_;
}
}
v___jp_2462_:
{
uint64_t v_position_2469_; uint64_t v___x_2470_; uint8_t v___x_2471_; 
v_position_2469_ = lean_uint64_add(v___y_2468_, v___y_2467_);
v___x_2470_ = 172ULL;
v___x_2471_ = lean_uint64_dec_lt(v_position_2469_, v___x_2470_);
if (v___x_2471_ == 0)
{
uint64_t v___x_2472_; uint8_t v___x_2473_; 
v___x_2472_ = 23ULL;
v___x_2473_ = lean_uint64_dec_lt(v___y_2468_, v___x_2472_);
if (v___x_2473_ == 0)
{
uint64_t v___x_2474_; uint8_t v___x_2475_; 
v___x_2474_ = lean_uint64_sub(v___y_2468_, v___x_2472_);
v___x_2475_ = lean_uint64_dec_eq(v___x_2474_, v___y_2464_);
if (v___x_2475_ == 0)
{
uint64_t v___x_2476_; uint8_t v___x_2477_; 
v___x_2476_ = 64ULL;
v___x_2477_ = lean_uint64_dec_lt(v___x_2474_, v___x_2476_);
if (v___x_2477_ == 0)
{
uint8_t v___x_2478_; 
v___x_2478_ = lean_uint64_dec_eq(v___x_2474_, v___x_2476_);
if (v___x_2478_ == 0)
{
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v___y_2464_;
goto v___jp_2452_;
}
else
{
uint64_t v___x_2479_; uint8_t v___x_2480_; 
v___x_2479_ = 9223372036854775808ULL;
v___x_2480_ = lean_uint64_dec_lt(v___x_2479_, v___y_2463_);
if (v___x_2480_ == 0)
{
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v___y_2464_;
goto v___jp_2452_;
}
else
{
uint64_t v___x_2481_; 
v___x_2481_ = 1ULL;
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v___x_2481_;
goto v___jp_2452_;
}
}
}
else
{
uint64_t v_quotient_2482_; uint64_t v___x_2483_; uint64_t v___x_2484_; uint64_t v___x_2485_; uint64_t v_remainder_2486_; uint64_t v___x_2487_; uint64_t v_half_2488_; uint8_t v___x_2489_; 
v_quotient_2482_ = lean_uint64_shift_right(v___y_2463_, v___x_2474_);
v___x_2483_ = 1ULL;
v___x_2484_ = lean_uint64_shift_left(v___x_2483_, v___x_2474_);
v___x_2485_ = lean_uint64_sub(v___x_2484_, v___x_2483_);
v_remainder_2486_ = lean_uint64_land(v___y_2463_, v___x_2485_);
v___x_2487_ = lean_uint64_sub(v___x_2474_, v___x_2483_);
v_half_2488_ = lean_uint64_shift_left(v___x_2483_, v___x_2487_);
v___x_2489_ = lean_uint64_dec_lt(v_remainder_2486_, v_half_2488_);
if (v___x_2489_ == 0)
{
uint8_t v___x_2490_; 
v___x_2490_ = lean_uint64_dec_lt(v_half_2488_, v_remainder_2486_);
if (v___x_2490_ == 0)
{
uint64_t v___x_2491_; uint8_t v___x_2492_; 
v___x_2491_ = lean_uint64_land(v_quotient_2482_, v___x_2483_);
v___x_2492_ = lean_uint64_dec_eq(v___x_2491_, v___y_2464_);
if (v___x_2492_ == 0)
{
uint64_t v___x_2493_; 
v___x_2493_ = lean_uint64_add(v_quotient_2482_, v___x_2483_);
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v___x_2493_;
goto v___jp_2452_;
}
else
{
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v_quotient_2482_;
goto v___jp_2452_;
}
}
else
{
uint64_t v___x_2494_; 
v___x_2494_ = lean_uint64_add(v_quotient_2482_, v___x_2483_);
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v___x_2494_;
goto v___jp_2452_;
}
}
else
{
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v_quotient_2482_;
goto v___jp_2452_;
}
}
}
else
{
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v___y_2463_;
goto v___jp_2452_;
}
}
else
{
uint64_t v___x_2495_; uint64_t v___x_2496_; 
v___x_2495_ = lean_uint64_sub(v___x_2472_, v___y_2468_);
v___x_2496_ = lean_uint64_shift_left(v___y_2463_, v___x_2495_);
v___y_2453_ = v___y_2464_;
v___y_2454_ = v___y_2466_;
v___y_2455_ = v___y_2465_;
v___y_2456_ = v_position_2469_;
v___y_2457_ = v___x_2496_;
goto v___jp_2452_;
}
}
else
{
uint64_t v___x_2497_; uint8_t v___x_2498_; 
v___x_2497_ = 149ULL;
v___x_2498_ = lean_uint64_dec_lt(v___y_2467_, v___x_2497_);
if (v___x_2498_ == 0)
{
uint64_t v___x_2499_; uint64_t v___x_2500_; 
v___x_2499_ = lean_uint64_sub(v___y_2467_, v___x_2497_);
v___x_2500_ = lean_uint64_shift_left(v___y_2463_, v___x_2499_);
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v___x_2500_;
goto v___jp_2391_;
}
else
{
uint64_t v___x_2501_; uint8_t v___x_2502_; 
v___x_2501_ = lean_uint64_sub(v___x_2497_, v___y_2467_);
v___x_2502_ = lean_uint64_dec_eq(v___x_2501_, v___y_2464_);
if (v___x_2502_ == 0)
{
uint64_t v___x_2503_; uint8_t v___x_2504_; 
v___x_2503_ = 64ULL;
v___x_2504_ = lean_uint64_dec_lt(v___x_2501_, v___x_2503_);
if (v___x_2504_ == 0)
{
uint8_t v___x_2505_; 
v___x_2505_ = lean_uint64_dec_eq(v___x_2501_, v___x_2503_);
if (v___x_2505_ == 0)
{
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v___y_2464_;
goto v___jp_2391_;
}
else
{
uint64_t v___x_2506_; uint8_t v___x_2507_; 
v___x_2506_ = 9223372036854775808ULL;
v___x_2507_ = lean_uint64_dec_lt(v___x_2506_, v___y_2463_);
if (v___x_2507_ == 0)
{
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v___y_2464_;
goto v___jp_2391_;
}
else
{
uint64_t v___x_2508_; 
v___x_2508_ = 1ULL;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v___x_2508_;
goto v___jp_2391_;
}
}
}
else
{
uint64_t v_quotient_2509_; uint64_t v___x_2510_; uint64_t v___x_2511_; uint64_t v___x_2512_; uint64_t v_remainder_2513_; uint64_t v___x_2514_; uint64_t v_half_2515_; uint8_t v___x_2516_; 
v_quotient_2509_ = lean_uint64_shift_right(v___y_2463_, v___x_2501_);
v___x_2510_ = 1ULL;
v___x_2511_ = lean_uint64_shift_left(v___x_2510_, v___x_2501_);
v___x_2512_ = lean_uint64_sub(v___x_2511_, v___x_2510_);
v_remainder_2513_ = lean_uint64_land(v___y_2463_, v___x_2512_);
v___x_2514_ = lean_uint64_sub(v___x_2501_, v___x_2510_);
v_half_2515_ = lean_uint64_shift_left(v___x_2510_, v___x_2514_);
v___x_2516_ = lean_uint64_dec_lt(v_remainder_2513_, v_half_2515_);
if (v___x_2516_ == 0)
{
uint8_t v___x_2517_; 
v___x_2517_ = lean_uint64_dec_lt(v_half_2515_, v_remainder_2513_);
if (v___x_2517_ == 0)
{
uint64_t v___x_2518_; uint8_t v___x_2519_; 
v___x_2518_ = lean_uint64_land(v_quotient_2509_, v___x_2510_);
v___x_2519_ = lean_uint64_dec_eq(v___x_2518_, v___y_2464_);
if (v___x_2519_ == 0)
{
uint64_t v___x_2520_; 
v___x_2520_ = lean_uint64_add(v_quotient_2509_, v___x_2510_);
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v___x_2520_;
goto v___jp_2391_;
}
else
{
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v_quotient_2509_;
goto v___jp_2391_;
}
}
else
{
uint64_t v___x_2521_; 
v___x_2521_ = lean_uint64_add(v_quotient_2509_, v___x_2510_);
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v___x_2521_;
goto v___jp_2391_;
}
}
else
{
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v_quotient_2509_;
goto v___jp_2391_;
}
}
}
else
{
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2466_;
v___y_2395_ = v___y_2463_;
goto v___jp_2391_;
}
}
}
}
v___jp_2522_:
{
uint64_t v___x_2530_; uint64_t v___x_2531_; uint8_t v___x_2532_; 
v___x_2530_ = 1ULL;
v___x_2531_ = lean_uint64_shift_right(v___y_2528_, v___x_2530_);
v___x_2532_ = lean_uint64_dec_eq(v___x_2531_, v___y_2524_);
if (v___x_2532_ == 0)
{
uint64_t v___x_2533_; 
v___x_2533_ = lean_uint64_add(v___y_2529_, v___x_2530_);
v___y_2463_ = v___y_2523_;
v___y_2464_ = v___y_2524_;
v___y_2465_ = v___y_2526_;
v___y_2466_ = v___y_2525_;
v___y_2467_ = v___y_2527_;
v___y_2468_ = v___x_2533_;
goto v___jp_2462_;
}
else
{
v___y_2463_ = v___y_2523_;
v___y_2464_ = v___y_2524_;
v___y_2465_ = v___y_2526_;
v___y_2466_ = v___y_2525_;
v___y_2467_ = v___y_2527_;
v___y_2468_ = v___y_2529_;
goto v___jp_2462_;
}
}
v___jp_2534_:
{
uint64_t v___x_2544_; uint8_t v___x_2545_; 
v___x_2544_ = lean_uint64_shift_right(v___y_2535_, v___y_2540_);
v___x_2545_ = lean_uint64_dec_eq(v___x_2544_, v___y_2536_);
if (v___x_2545_ == 0)
{
uint64_t v___x_2546_; 
v___x_2546_ = lean_uint64_add(v___y_2542_, v___y_2540_);
v___y_2523_ = v___y_2537_;
v___y_2524_ = v___y_2536_;
v___y_2525_ = v___y_2539_;
v___y_2526_ = v___y_2538_;
v___y_2527_ = v___y_2541_;
v___y_2528_ = v___y_2543_;
v___y_2529_ = v___x_2546_;
goto v___jp_2522_;
}
else
{
v___y_2523_ = v___y_2537_;
v___y_2524_ = v___y_2536_;
v___y_2525_ = v___y_2539_;
v___y_2526_ = v___y_2538_;
v___y_2527_ = v___y_2541_;
v___y_2528_ = v___y_2543_;
v___y_2529_ = v___y_2542_;
goto v___jp_2522_;
}
}
v___jp_2547_:
{
uint64_t v___x_2555_; uint64_t v___x_2556_; uint8_t v___x_2557_; 
v___x_2555_ = 2ULL;
v___x_2556_ = lean_uint64_shift_right(v___y_2548_, v___x_2555_);
v___x_2557_ = lean_uint64_dec_eq(v___x_2556_, v___y_2550_);
if (v___x_2557_ == 0)
{
v___y_2535_ = v___y_2548_;
v___y_2536_ = v___y_2550_;
v___y_2537_ = v___y_2549_;
v___y_2538_ = v___y_2552_;
v___y_2539_ = v___y_2551_;
v___y_2540_ = v___x_2555_;
v___y_2541_ = v___y_2553_;
v___y_2542_ = v___y_2554_;
v___y_2543_ = v___x_2556_;
goto v___jp_2534_;
}
else
{
v___y_2535_ = v___y_2548_;
v___y_2536_ = v___y_2550_;
v___y_2537_ = v___y_2549_;
v___y_2538_ = v___y_2552_;
v___y_2539_ = v___y_2551_;
v___y_2540_ = v___x_2555_;
v___y_2541_ = v___y_2553_;
v___y_2542_ = v___y_2554_;
v___y_2543_ = v___y_2548_;
goto v___jp_2534_;
}
}
v___jp_2558_:
{
uint64_t v___x_2568_; uint8_t v___x_2569_; 
v___x_2568_ = lean_uint64_shift_right(v___y_2565_, v___y_2562_);
v___x_2569_ = lean_uint64_dec_eq(v___x_2568_, v___y_2559_);
if (v___x_2569_ == 0)
{
uint64_t v___x_2570_; 
v___x_2570_ = lean_uint64_add(v___y_2561_, v___y_2562_);
v___y_2548_ = v___y_2567_;
v___y_2549_ = v___y_2560_;
v___y_2550_ = v___y_2559_;
v___y_2551_ = v___y_2564_;
v___y_2552_ = v___y_2563_;
v___y_2553_ = v___y_2566_;
v___y_2554_ = v___x_2570_;
goto v___jp_2547_;
}
else
{
v___y_2548_ = v___y_2567_;
v___y_2549_ = v___y_2560_;
v___y_2550_ = v___y_2559_;
v___y_2551_ = v___y_2564_;
v___y_2552_ = v___y_2563_;
v___y_2553_ = v___y_2566_;
v___y_2554_ = v___y_2561_;
goto v___jp_2547_;
}
}
v___jp_2571_:
{
uint64_t v___x_2579_; uint64_t v___x_2580_; uint8_t v___x_2581_; 
v___x_2579_ = 4ULL;
v___x_2580_ = lean_uint64_shift_right(v___y_2576_, v___x_2579_);
v___x_2581_ = lean_uint64_dec_eq(v___x_2580_, v___y_2573_);
if (v___x_2581_ == 0)
{
v___y_2559_ = v___y_2573_;
v___y_2560_ = v___y_2572_;
v___y_2561_ = v___y_2578_;
v___y_2562_ = v___x_2579_;
v___y_2563_ = v___y_2575_;
v___y_2564_ = v___y_2574_;
v___y_2565_ = v___y_2576_;
v___y_2566_ = v___y_2577_;
v___y_2567_ = v___x_2580_;
goto v___jp_2558_;
}
else
{
v___y_2559_ = v___y_2573_;
v___y_2560_ = v___y_2572_;
v___y_2561_ = v___y_2578_;
v___y_2562_ = v___x_2579_;
v___y_2563_ = v___y_2575_;
v___y_2564_ = v___y_2574_;
v___y_2565_ = v___y_2576_;
v___y_2566_ = v___y_2577_;
v___y_2567_ = v___y_2576_;
goto v___jp_2558_;
}
}
v___jp_2582_:
{
uint64_t v___x_2592_; uint8_t v___x_2593_; 
v___x_2592_ = lean_uint64_shift_right(v___y_2583_, v___y_2584_);
v___x_2593_ = lean_uint64_dec_eq(v___x_2592_, v___y_2585_);
if (v___x_2593_ == 0)
{
uint64_t v___x_2594_; 
v___x_2594_ = lean_uint64_add(v___y_2587_, v___y_2584_);
v___y_2572_ = v___y_2586_;
v___y_2573_ = v___y_2585_;
v___y_2574_ = v___y_2589_;
v___y_2575_ = v___y_2588_;
v___y_2576_ = v___y_2591_;
v___y_2577_ = v___y_2590_;
v___y_2578_ = v___x_2594_;
goto v___jp_2571_;
}
else
{
v___y_2572_ = v___y_2586_;
v___y_2573_ = v___y_2585_;
v___y_2574_ = v___y_2589_;
v___y_2575_ = v___y_2588_;
v___y_2576_ = v___y_2591_;
v___y_2577_ = v___y_2590_;
v___y_2578_ = v___y_2587_;
goto v___jp_2571_;
}
}
v___jp_2595_:
{
uint64_t v___x_2603_; uint64_t v___x_2604_; uint8_t v___x_2605_; 
v___x_2603_ = 8ULL;
v___x_2604_ = lean_uint64_shift_right(v___y_2596_, v___x_2603_);
v___x_2605_ = lean_uint64_dec_eq(v___x_2604_, v___y_2598_);
if (v___x_2605_ == 0)
{
v___y_2583_ = v___y_2596_;
v___y_2584_ = v___x_2603_;
v___y_2585_ = v___y_2598_;
v___y_2586_ = v___y_2597_;
v___y_2587_ = v___y_2602_;
v___y_2588_ = v___y_2600_;
v___y_2589_ = v___y_2599_;
v___y_2590_ = v___y_2601_;
v___y_2591_ = v___x_2604_;
goto v___jp_2582_;
}
else
{
v___y_2583_ = v___y_2596_;
v___y_2584_ = v___x_2603_;
v___y_2585_ = v___y_2598_;
v___y_2586_ = v___y_2597_;
v___y_2587_ = v___y_2602_;
v___y_2588_ = v___y_2600_;
v___y_2589_ = v___y_2599_;
v___y_2590_ = v___y_2601_;
v___y_2591_ = v___y_2596_;
goto v___jp_2582_;
}
}
v___jp_2606_:
{
uint64_t v___x_2616_; uint8_t v___x_2617_; 
v___x_2616_ = lean_uint64_shift_right(v___y_2607_, v___y_2610_);
v___x_2617_ = lean_uint64_dec_eq(v___x_2616_, v___y_2608_);
if (v___x_2617_ == 0)
{
uint64_t v___x_2618_; 
v___x_2618_ = lean_uint64_add(v___y_2613_, v___y_2610_);
v___y_2596_ = v___y_2615_;
v___y_2597_ = v___y_2609_;
v___y_2598_ = v___y_2608_;
v___y_2599_ = v___y_2612_;
v___y_2600_ = v___y_2611_;
v___y_2601_ = v___y_2614_;
v___y_2602_ = v___x_2618_;
goto v___jp_2595_;
}
else
{
v___y_2596_ = v___y_2615_;
v___y_2597_ = v___y_2609_;
v___y_2598_ = v___y_2608_;
v___y_2599_ = v___y_2612_;
v___y_2600_ = v___y_2611_;
v___y_2601_ = v___y_2614_;
v___y_2602_ = v___y_2613_;
goto v___jp_2595_;
}
}
v___jp_2619_:
{
uint64_t v___x_2627_; uint64_t v___x_2628_; uint8_t v___x_2629_; 
v___x_2627_ = 16ULL;
v___x_2628_ = lean_uint64_shift_right(v___y_2620_, v___x_2627_);
v___x_2629_ = lean_uint64_dec_eq(v___x_2628_, v___y_2622_);
if (v___x_2629_ == 0)
{
v___y_2607_ = v___y_2620_;
v___y_2608_ = v___y_2622_;
v___y_2609_ = v___y_2621_;
v___y_2610_ = v___x_2627_;
v___y_2611_ = v___y_2624_;
v___y_2612_ = v___y_2623_;
v___y_2613_ = v___y_2626_;
v___y_2614_ = v___y_2625_;
v___y_2615_ = v___x_2628_;
goto v___jp_2606_;
}
else
{
v___y_2607_ = v___y_2620_;
v___y_2608_ = v___y_2622_;
v___y_2609_ = v___y_2621_;
v___y_2610_ = v___x_2627_;
v___y_2611_ = v___y_2624_;
v___y_2612_ = v___y_2623_;
v___y_2613_ = v___y_2626_;
v___y_2614_ = v___y_2625_;
v___y_2615_ = v___y_2620_;
goto v___jp_2606_;
}
}
v___jp_2630_:
{
uint64_t v___x_2638_; uint8_t v___x_2639_; 
v___x_2638_ = lean_uint64_shift_right(v___y_2633_, v___y_2631_);
v___x_2639_ = lean_uint64_dec_eq(v___x_2638_, v___y_2632_);
if (v___x_2639_ == 0)
{
v___y_2620_ = v___y_2637_;
v___y_2621_ = v___y_2633_;
v___y_2622_ = v___y_2632_;
v___y_2623_ = v___y_2635_;
v___y_2624_ = v___y_2634_;
v___y_2625_ = v___y_2636_;
v___y_2626_ = v___y_2631_;
goto v___jp_2619_;
}
else
{
v___y_2620_ = v___y_2637_;
v___y_2621_ = v___y_2633_;
v___y_2622_ = v___y_2632_;
v___y_2623_ = v___y_2635_;
v___y_2624_ = v___y_2634_;
v___y_2625_ = v___y_2636_;
v___y_2626_ = v___y_2632_;
goto v___jp_2619_;
}
}
v___jp_2640_:
{
uint64_t v___x_2647_; uint64_t v___x_2648_; uint8_t v___x_2649_; 
v___x_2647_ = lean_uint64_mul(v___y_2641_, v___y_2645_);
v___x_2648_ = 0ULL;
v___x_2649_ = lean_uint64_dec_eq(v___x_2647_, v___x_2648_);
if (v___x_2649_ == 0)
{
uint64_t v___x_2650_; uint64_t v___x_2651_; uint64_t v___x_2652_; uint8_t v___x_2653_; 
v___x_2650_ = lean_uint64_add(v___y_2644_, v___y_2646_);
v___x_2651_ = 32ULL;
v___x_2652_ = lean_uint64_shift_right(v___x_2647_, v___x_2651_);
v___x_2653_ = lean_uint64_dec_eq(v___x_2652_, v___x_2648_);
if (v___x_2653_ == 0)
{
v___y_2631_ = v___x_2651_;
v___y_2632_ = v___x_2648_;
v___y_2633_ = v___x_2647_;
v___y_2634_ = v___y_2643_;
v___y_2635_ = v___y_2642_;
v___y_2636_ = v___x_2650_;
v___y_2637_ = v___x_2652_;
goto v___jp_2630_;
}
else
{
v___y_2631_ = v___x_2651_;
v___y_2632_ = v___x_2648_;
v___y_2633_ = v___x_2647_;
v___y_2634_ = v___y_2643_;
v___y_2635_ = v___y_2642_;
v___y_2636_ = v___x_2650_;
v___y_2637_ = v___x_2647_;
goto v___jp_2630_;
}
}
else
{
if (v___y_2643_ == 0)
{
uint32_t v___x_2654_; 
v___x_2654_ = 0;
return v___x_2654_;
}
else
{
uint32_t v___x_2655_; 
v___x_2655_ = 2147483648;
return v___x_2655_;
}
}
}
v___jp_2659_:
{
uint64_t v___x_2665_; uint64_t v___x_2666_; uint8_t v___x_2667_; 
v___x_2665_ = lean_uint32_to_uint64(v_yExponent_2658_);
v___x_2666_ = 0ULL;
v___x_2667_ = lean_uint64_dec_eq(v___x_2665_, v___x_2666_);
if (v___x_2667_ == 0)
{
uint64_t v___x_2668_; uint64_t v___x_2669_; 
v___x_2668_ = 1ULL;
v___x_2669_ = lean_uint64_sub(v___x_2665_, v___x_2668_);
v___y_2641_ = v___y_2660_;
v___y_2642_ = v___y_2662_;
v___y_2643_ = v___y_2661_;
v___y_2644_ = v___y_2664_;
v___y_2645_ = v___y_2663_;
v___y_2646_ = v___x_2669_;
goto v___jp_2640_;
}
else
{
v___y_2641_ = v___y_2660_;
v___y_2642_ = v___y_2662_;
v___y_2643_ = v___y_2661_;
v___y_2644_ = v___y_2664_;
v___y_2645_ = v___y_2663_;
v___y_2646_ = v___x_2666_;
goto v___jp_2640_;
}
}
v___jp_2670_:
{
uint64_t v___x_2675_; uint64_t v___x_2676_; uint8_t v___x_2677_; 
v___x_2675_ = lean_uint32_to_uint64(v_xExponent_2656_);
v___x_2676_ = 0ULL;
v___x_2677_ = lean_uint64_dec_eq(v___x_2675_, v___x_2676_);
if (v___x_2677_ == 0)
{
uint64_t v___x_2678_; uint64_t v___x_2679_; 
v___x_2678_ = 1ULL;
v___x_2679_ = lean_uint64_sub(v___x_2675_, v___x_2678_);
v___y_2660_ = v___y_2671_;
v___y_2661_ = v___y_2673_;
v___y_2662_ = v___y_2672_;
v___y_2663_ = v___y_2674_;
v___y_2664_ = v___x_2679_;
goto v___jp_2659_;
}
else
{
v___y_2660_ = v___y_2671_;
v___y_2661_ = v___y_2673_;
v___y_2662_ = v___y_2672_;
v___y_2663_ = v___y_2674_;
v___y_2664_ = v___x_2676_;
goto v___jp_2659_;
}
}
v___jp_2680_:
{
uint32_t v___x_2685_; uint8_t v___x_2686_; 
v___x_2685_ = 0;
v___x_2686_ = lean_uint32_dec_eq(v_yExponent_2658_, v___x_2685_);
if (v___x_2686_ == 0)
{
uint64_t v___x_2687_; uint64_t v___x_2688_; uint64_t v___x_2689_; 
v___x_2687_ = lean_uint32_to_uint64(v___y_2681_);
v___x_2688_ = 8388608ULL;
v___x_2689_ = lean_uint64_lor(v___x_2687_, v___x_2688_);
v___y_2671_ = v___y_2684_;
v___y_2672_ = v___y_2683_;
v___y_2673_ = v___y_2682_;
v___y_2674_ = v___x_2689_;
goto v___jp_2670_;
}
else
{
uint64_t v___x_2690_; 
v___x_2690_ = lean_uint32_to_uint64(v___y_2681_);
v___y_2671_ = v___y_2684_;
v___y_2672_ = v___y_2683_;
v___y_2673_ = v___y_2682_;
v___y_2674_ = v___x_2690_;
goto v___jp_2670_;
}
}
v___jp_2691_:
{
uint32_t v___x_2693_; uint32_t v_xFraction_2694_; uint32_t v_yFraction_2695_; uint32_t v___x_2696_; uint8_t v___x_2697_; 
v___x_2693_ = 8388607;
v_xFraction_2694_ = lean_uint32_land(v_xBits_2379_, v___x_2693_);
v_yFraction_2695_ = lean_uint32_land(v_yBits_2380_, v___x_2693_);
v___x_2696_ = 0;
v___x_2697_ = lean_uint32_dec_eq(v_xExponent_2656_, v___x_2696_);
if (v___x_2697_ == 0)
{
uint64_t v___x_2698_; uint64_t v___x_2699_; uint64_t v___x_2700_; 
v___x_2698_ = lean_uint32_to_uint64(v_xFraction_2694_);
v___x_2699_ = 8388608ULL;
v___x_2700_ = lean_uint64_lor(v___x_2698_, v___x_2699_);
v___y_2681_ = v_yFraction_2695_;
v___y_2682_ = v___y_2692_;
v___y_2683_ = v___x_2693_;
v___y_2684_ = v___x_2700_;
goto v___jp_2680_;
}
else
{
uint64_t v___x_2701_; 
v___x_2701_ = lean_uint32_to_uint64(v_xFraction_2694_);
v___y_2681_ = v_yFraction_2695_;
v___y_2682_ = v___y_2692_;
v___y_2683_ = v___x_2693_;
v___y_2684_ = v___x_2701_;
goto v___jp_2680_;
}
}
v___jp_2702_:
{
uint8_t v___x_2703_; 
v___x_2703_ = 1;
v___y_2692_ = v___x_2703_;
goto v___jp_2691_;
}
v___jp_2704_:
{
uint8_t v___x_2705_; 
v___x_2705_ = 0;
v___y_2692_ = v___x_2705_;
goto v___jp_2691_;
}
v___jp_2706_:
{
if (v___y_2707_ == 0)
{
if (v___y_2708_ == 0)
{
goto v___jp_2704_;
}
else
{
goto v___jp_2702_;
}
}
else
{
if (v___y_2708_ == 0)
{
goto v___jp_2702_;
}
else
{
goto v___jp_2704_;
}
}
}
v___jp_2709_:
{
uint32_t v___x_2711_; uint32_t v___x_2712_; uint32_t v___x_2713_; uint8_t v___x_2714_; 
v___x_2711_ = 2147483648;
v___x_2712_ = lean_uint32_land(v_yBits_2380_, v___x_2711_);
v___x_2713_ = 0;
v___x_2714_ = lean_uint32_dec_eq(v___x_2712_, v___x_2713_);
if (v___x_2714_ == 0)
{
uint8_t v___x_2715_; 
v___x_2715_ = 1;
v___y_2707_ = v___y_2710_;
v___y_2708_ = v___x_2715_;
goto v___jp_2706_;
}
else
{
uint8_t v___x_2716_; 
v___x_2716_ = 0;
v___y_2707_ = v___y_2710_;
v___y_2708_ = v___x_2716_;
goto v___jp_2706_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_core___boxed(lean_object* v_xBits_2723_, lean_object* v_yBits_2724_){
_start:
{
uint32_t v_xBits_boxed_2725_; uint32_t v_yBits_boxed_2726_; uint32_t v_res_2727_; lean_object* v_r_2728_; 
v_xBits_boxed_2725_ = lean_unbox_uint32(v_xBits_2723_);
lean_dec(v_xBits_2723_);
v_yBits_boxed_2726_ = lean_unbox_uint32(v_yBits_2724_);
lean_dec(v_yBits_2724_);
v_res_2727_ = lp_competition_Submission_FastMul_core(v_xBits_boxed_2725_, v_yBits_boxed_2726_);
v_r_2728_ = lean_box_uint32(v_res_2727_);
return v_r_2728_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_sm1(uint32_t v_a_2729_){
_start:
{
uint32_t v___x_2730_; uint32_t v___x_2731_; uint32_t v___x_2732_; uint8_t v___x_2733_; 
v___x_2730_ = 4278190080;
v___x_2731_ = 1;
v___x_2732_ = lean_uint32_shift_left(v_a_2729_, v___x_2731_);
v___x_2733_ = lean_uint32_dec_le(v___x_2730_, v___x_2732_);
return v___x_2733_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sm1___boxed(lean_object* v_a_2734_){
_start:
{
uint32_t v_a_boxed_2735_; uint8_t v_res_2736_; lean_object* v_r_2737_; 
v_a_boxed_2735_ = lean_unbox_uint32(v_a_2734_);
lean_dec(v_a_2734_);
v_res_2736_ = lp_competition_Submission_FastMul_sm1(v_a_boxed_2735_);
v_r_2737_ = lean_box(v_res_2736_);
return v_r_2737_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_special(uint32_t v_a_2738_, uint32_t v_b_2739_){
_start:
{
uint32_t v___x_2740_; uint32_t v___x_2741_; uint32_t v___x_2742_; uint8_t v___x_2743_; 
v___x_2740_ = 4278190080;
v___x_2741_ = 1;
v___x_2742_ = lean_uint32_shift_left(v_a_2738_, v___x_2741_);
v___x_2743_ = lean_uint32_dec_le(v___x_2740_, v___x_2742_);
if (v___x_2743_ == 0)
{
uint32_t v___x_2744_; uint8_t v___x_2745_; 
v___x_2744_ = lean_uint32_shift_left(v_b_2739_, v___x_2741_);
v___x_2745_ = lean_uint32_dec_le(v___x_2740_, v___x_2744_);
return v___x_2745_;
}
else
{
return v___x_2743_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_special___boxed(lean_object* v_a_2746_, lean_object* v_b_2747_){
_start:
{
uint32_t v_a_boxed_2748_; uint32_t v_b_boxed_2749_; uint8_t v_res_2750_; lean_object* v_r_2751_; 
v_a_boxed_2748_ = lean_unbox_uint32(v_a_2746_);
lean_dec(v_a_2746_);
v_b_boxed_2749_ = lean_unbox_uint32(v_b_2747_);
lean_dec(v_b_2747_);
v_res_2750_ = lp_competition_Submission_FastMul_special(v_a_boxed_2748_, v_b_boxed_2749_);
v_r_2751_ = lean_box(v_res_2750_);
return v_r_2751_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_ofBits(uint32_t v_w_2752_){
_start:
{
return v_w_2752_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_ofBits___boxed(lean_object* v_w_2753_){
_start:
{
uint32_t v_w_boxed_2754_; uint32_t v_res_2755_; lean_object* v_r_2756_; 
v_w_boxed_2754_ = lean_unbox_uint32(v_w_2753_);
lean_dec(v_w_2753_);
v_res_2755_ = lp_competition_Submission_FastMul_ofBits(v_w_boxed_2754_);
v_r_2756_ = lean_box_uint32(v_res_2755_);
return v_r_2756_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mul(uint32_t v_x_2757_, uint32_t v_y_2758_){
_start:
{
uint32_t v___y_2760_; uint32_t v___y_2764_; uint32_t v___y_2765_; uint32_t v___y_2766_; uint32_t v___y_2770_; uint8_t v___y_2771_; uint64_t v___y_2772_; uint64_t v___y_2773_; uint32_t v___y_2785_; uint32_t v___y_2786_; uint32_t v___y_2787_; uint32_t v___y_2788_; uint32_t v___y_2789_; uint32_t v___y_2790_; uint32_t v___y_2797_; uint32_t v___y_2798_; uint32_t v___y_2799_; uint32_t v___y_2800_; uint8_t v___y_2801_; uint32_t v___y_2802_; uint32_t v___y_2806_; uint32_t v___y_2807_; uint64_t v___y_2808_; uint32_t v___y_2809_; uint8_t v___y_2810_; uint64_t v___y_2811_; uint64_t v___y_2812_; uint32_t v___y_2822_; uint64_t v___y_2823_; uint32_t v___y_2824_; uint8_t v___y_2825_; uint32_t v___y_2826_; uint8_t v___y_2827_; uint64_t v___y_2828_; uint64_t v___y_2829_; uint32_t v___y_2836_; uint32_t v___y_2837_; uint32_t v___y_2838_; uint8_t v___y_2839_; uint64_t v___y_2840_; uint64_t v___y_2841_; uint64_t v___y_2842_; uint32_t v___y_2848_; uint32_t v___y_2849_; uint64_t v___y_2850_; uint64_t v___y_2851_; uint32_t v___y_2852_; uint8_t v___y_2853_; uint64_t v___y_2854_; uint64_t v___y_2855_; uint32_t v___y_2910_; uint32_t v___y_2911_; uint64_t v___y_2912_; uint64_t v___y_2913_; uint32_t v___y_2914_; uint8_t v___y_2915_; uint64_t v___y_2916_; uint64_t v___y_2917_; uint64_t v___y_2918_; uint64_t v___y_2924_; uint32_t v___y_2925_; uint32_t v___y_2926_; uint64_t v___y_2927_; uint64_t v___y_2928_; uint64_t v___y_2929_; uint32_t v___y_2930_; uint8_t v___y_2931_; uint64_t v___y_2932_; uint64_t v___y_2933_; uint64_t v___y_2934_; uint32_t v___y_2939_; uint32_t v___y_2940_; uint64_t v___y_2941_; uint64_t v___y_2942_; uint64_t v___y_2943_; uint32_t v___y_2944_; uint8_t v___y_2945_; uint64_t v___y_2946_; uint64_t v___y_2947_; uint32_t v___y_2952_; uint32_t v___y_2953_; uint64_t v___y_2954_; uint64_t v___y_2955_; uint64_t v___y_2956_; uint64_t v___y_2957_; uint64_t v___y_2958_; uint32_t v___y_2959_; uint8_t v___y_2960_; uint64_t v___y_2961_; uint64_t v___y_2962_; uint32_t v___y_2967_; uint32_t v___y_2968_; uint64_t v___y_2969_; uint64_t v___y_2970_; uint64_t v___y_2971_; uint32_t v___y_2972_; uint8_t v___y_2973_; uint64_t v___y_2974_; uint64_t v___y_2975_; uint32_t v___y_2980_; uint64_t v___y_2981_; uint32_t v___y_2982_; uint64_t v___y_2983_; uint64_t v___y_2984_; uint64_t v___y_2985_; uint64_t v___y_2986_; uint32_t v___y_2987_; uint8_t v___y_2988_; uint64_t v___y_2989_; uint64_t v___y_2990_; uint32_t v___y_2995_; uint32_t v___y_2996_; uint64_t v___y_2997_; uint64_t v___y_2998_; uint64_t v___y_2999_; uint32_t v___y_3000_; uint8_t v___y_3001_; uint64_t v___y_3002_; uint64_t v___y_3003_; uint64_t v___y_3008_; uint32_t v___y_3009_; uint32_t v___y_3010_; uint64_t v___y_3011_; uint64_t v___y_3012_; uint64_t v___y_3013_; uint64_t v___y_3014_; uint32_t v___y_3015_; uint8_t v___y_3016_; uint64_t v___y_3017_; uint64_t v___y_3018_; uint32_t v___y_3023_; uint32_t v___y_3024_; uint64_t v___y_3025_; uint64_t v___y_3026_; uint64_t v___y_3027_; uint32_t v___y_3028_; uint8_t v___y_3029_; uint64_t v___y_3030_; uint64_t v___y_3031_; uint32_t v___y_3036_; uint32_t v___y_3037_; uint64_t v___y_3038_; uint64_t v___y_3039_; uint32_t v___y_3040_; uint8_t v___y_3041_; uint64_t v___y_3042_; uint64_t v___y_3043_; uint64_t v___y_3044_; uint32_t v___y_3048_; uint32_t v___y_3049_; uint64_t v___y_3050_; uint32_t v___y_3051_; uint64_t v___y_3052_; uint8_t v___y_3053_; uint64_t v___y_3054_; uint64_t v___y_3055_; uint32_t v___y_3066_; uint64_t v___y_3067_; uint32_t v___y_3068_; uint32_t v___y_3069_; uint32_t v___y_3070_; uint8_t v___y_3071_; uint64_t v___y_3072_; uint64_t v___y_3073_; uint32_t v___y_3080_; uint32_t v___y_3081_; uint64_t v___y_3082_; uint32_t v___y_3083_; uint32_t v___y_3084_; uint32_t v___y_3085_; uint8_t v___y_3086_; uint64_t v___y_3087_; uint32_t v___y_3094_; uint32_t v___y_3095_; uint32_t v___y_3096_; uint32_t v___y_3097_; uint32_t v___y_3098_; uint8_t v___y_3099_; uint32_t v___y_3100_; uint64_t v___y_3101_; uint32_t v___y_3109_; uint32_t v___y_3110_; uint32_t v___y_3111_; uint32_t v___y_3112_; uint8_t v___y_3113_; uint32_t v___y_3124_; uint32_t v___y_3125_; uint32_t v___y_3126_; uint32_t v___y_3127_; uint32_t v___y_3130_; uint8_t v___y_3131_; uint32_t v___y_3132_; uint32_t v___y_3133_; uint8_t v___y_3134_; uint32_t v___y_3135_; uint8_t v___y_3136_; uint32_t v___y_3138_; uint8_t v___y_3139_; uint32_t v___y_3140_; uint32_t v___y_3141_; uint32_t v___y_3142_; uint8_t v___y_3143_; uint8_t v___y_3150_; uint32_t v___x_3167_; uint32_t v___x_3168_; uint32_t v___x_3169_; uint8_t v___x_3170_; 
v___x_3167_ = 4278190080;
v___x_3168_ = 1;
v___x_3169_ = lean_uint32_shift_left(v_x_2757_, v___x_3168_);
v___x_3170_ = lean_uint32_dec_le(v___x_3167_, v___x_3169_);
if (v___x_3170_ == 0)
{
uint32_t v___x_3171_; uint8_t v___x_3172_; 
v___x_3171_ = lean_uint32_shift_left(v_y_2758_, v___x_3168_);
v___x_3172_ = lean_uint32_dec_le(v___x_3167_, v___x_3171_);
v___y_3150_ = v___x_3172_;
goto v___jp_3149_;
}
else
{
v___y_3150_ = v___x_3170_;
goto v___jp_3149_;
}
v___jp_2759_:
{
uint32_t v___x_2761_; uint32_t v___x_2762_; 
v___x_2761_ = 8388608;
v___x_2762_ = lean_uint32_lor(v___y_2760_, v___x_2761_);
return v___x_2762_;
}
v___jp_2763_:
{
uint32_t v___x_2767_; uint32_t v___x_2768_; 
v___x_2767_ = lean_uint32_land(v___y_2765_, v___y_2764_);
v___x_2768_ = lean_uint32_lor(v___y_2766_, v___x_2767_);
return v___x_2768_;
}
v___jp_2769_:
{
uint8_t v___x_2774_; 
v___x_2774_ = lean_uint64_dec_eq(v___y_2773_, v___y_2772_);
if (v___x_2774_ == 0)
{
uint64_t v___x_2775_; uint8_t v___x_2776_; 
v___x_2775_ = 8388608ULL;
v___x_2776_ = lean_uint64_dec_eq(v___y_2773_, v___x_2775_);
if (v___x_2776_ == 0)
{
uint32_t v___x_2777_; 
v___x_2777_ = lean_uint64_to_uint32(v___y_2773_);
if (v___y_2771_ == 0)
{
uint32_t v___x_2778_; 
v___x_2778_ = 0;
v___y_2764_ = v___y_2770_;
v___y_2765_ = v___x_2777_;
v___y_2766_ = v___x_2778_;
goto v___jp_2763_;
}
else
{
uint32_t v___x_2779_; 
v___x_2779_ = 2147483648;
v___y_2764_ = v___y_2770_;
v___y_2765_ = v___x_2777_;
v___y_2766_ = v___x_2779_;
goto v___jp_2763_;
}
}
else
{
if (v___y_2771_ == 0)
{
uint32_t v___x_2780_; 
v___x_2780_ = 0;
v___y_2760_ = v___x_2780_;
goto v___jp_2759_;
}
else
{
uint32_t v___x_2781_; 
v___x_2781_ = 2147483648;
v___y_2760_ = v___x_2781_;
goto v___jp_2759_;
}
}
}
else
{
if (v___y_2771_ == 0)
{
uint32_t v___x_2782_; 
v___x_2782_ = 0;
return v___x_2782_;
}
else
{
uint32_t v___x_2783_; 
v___x_2783_ = 2147483648;
return v___x_2783_;
}
}
}
v___jp_2784_:
{
uint32_t v___x_2791_; uint32_t v___x_2792_; uint32_t v___x_2793_; uint32_t v___x_2794_; uint32_t v___x_2795_; 
v___x_2791_ = lean_uint32_land(v___y_2789_, v___y_2785_);
v___x_2792_ = lean_uint32_shift_left(v___x_2791_, v___y_2788_);
v___x_2793_ = lean_uint32_lor(v___y_2790_, v___x_2792_);
v___x_2794_ = lean_uint32_land(v___y_2787_, v___y_2786_);
v___x_2795_ = lean_uint32_lor(v___x_2793_, v___x_2794_);
return v___x_2795_;
}
v___jp_2796_:
{
if (v___y_2801_ == 0)
{
uint32_t v___x_2803_; 
v___x_2803_ = 0;
v___y_2785_ = v___y_2797_;
v___y_2786_ = v___y_2798_;
v___y_2787_ = v___y_2802_;
v___y_2788_ = v___y_2800_;
v___y_2789_ = v___y_2799_;
v___y_2790_ = v___x_2803_;
goto v___jp_2784_;
}
else
{
uint32_t v___x_2804_; 
v___x_2804_ = 2147483648;
v___y_2785_ = v___y_2797_;
v___y_2786_ = v___y_2798_;
v___y_2787_ = v___y_2802_;
v___y_2788_ = v___y_2800_;
v___y_2789_ = v___y_2799_;
v___y_2790_ = v___x_2804_;
goto v___jp_2784_;
}
}
v___jp_2805_:
{
uint64_t v___x_2813_; uint64_t v_encodedExponent_2814_; uint32_t v___x_2815_; uint64_t v___x_2816_; uint8_t v___x_2817_; 
v___x_2813_ = 171ULL;
v_encodedExponent_2814_ = lean_uint64_sub(v___y_2808_, v___x_2813_);
v___x_2815_ = lean_uint64_to_uint32(v_encodedExponent_2814_);
v___x_2816_ = 8388608ULL;
v___x_2817_ = lean_uint64_dec_lt(v___y_2812_, v___x_2816_);
if (v___x_2817_ == 0)
{
uint64_t v___x_2818_; uint32_t v___x_2819_; 
v___x_2818_ = lean_uint64_sub(v___y_2812_, v___x_2816_);
v___x_2819_ = lean_uint64_to_uint32(v___x_2818_);
v___y_2797_ = v___y_2806_;
v___y_2798_ = v___y_2807_;
v___y_2799_ = v___x_2815_;
v___y_2800_ = v___y_2809_;
v___y_2801_ = v___y_2810_;
v___y_2802_ = v___x_2819_;
goto v___jp_2796_;
}
else
{
uint32_t v___x_2820_; 
v___x_2820_ = lean_uint64_to_uint32(v___y_2811_);
v___y_2797_ = v___y_2806_;
v___y_2798_ = v___y_2807_;
v___y_2799_ = v___x_2815_;
v___y_2800_ = v___y_2809_;
v___y_2801_ = v___y_2810_;
v___y_2802_ = v___x_2820_;
goto v___jp_2796_;
}
}
v___jp_2821_:
{
uint64_t v___x_2830_; uint8_t v___x_2831_; 
v___x_2830_ = 425ULL;
v___x_2831_ = lean_uint64_dec_lt(v___x_2830_, v___y_2829_);
if (v___x_2831_ == 0)
{
if (v___y_2825_ == 0)
{
v___y_2806_ = v___y_2822_;
v___y_2807_ = v___y_2824_;
v___y_2808_ = v___y_2829_;
v___y_2809_ = v___y_2826_;
v___y_2810_ = v___y_2827_;
v___y_2811_ = v___y_2828_;
v___y_2812_ = v___y_2823_;
goto v___jp_2805_;
}
else
{
uint64_t v___x_2832_; 
v___x_2832_ = 8388608ULL;
v___y_2806_ = v___y_2822_;
v___y_2807_ = v___y_2824_;
v___y_2808_ = v___y_2829_;
v___y_2809_ = v___y_2826_;
v___y_2810_ = v___y_2827_;
v___y_2811_ = v___y_2828_;
v___y_2812_ = v___x_2832_;
goto v___jp_2805_;
}
}
else
{
if (v___y_2827_ == 0)
{
uint32_t v___x_2833_; 
v___x_2833_ = 2139095040;
return v___x_2833_;
}
else
{
uint32_t v___x_2834_; 
v___x_2834_ = 4286578688;
return v___x_2834_;
}
}
}
v___jp_2835_:
{
uint64_t v___x_2843_; uint8_t v_carry_2844_; 
v___x_2843_ = 16777216ULL;
v_carry_2844_ = lean_uint64_dec_eq(v___y_2842_, v___x_2843_);
if (v_carry_2844_ == 0)
{
v___y_2822_ = v___y_2836_;
v___y_2823_ = v___y_2842_;
v___y_2824_ = v___y_2837_;
v___y_2825_ = v_carry_2844_;
v___y_2826_ = v___y_2838_;
v___y_2827_ = v___y_2839_;
v___y_2828_ = v___y_2841_;
v___y_2829_ = v___y_2840_;
goto v___jp_2821_;
}
else
{
uint64_t v___x_2845_; uint64_t v___x_2846_; 
v___x_2845_ = 1ULL;
v___x_2846_ = lean_uint64_add(v___y_2840_, v___x_2845_);
v___y_2822_ = v___y_2836_;
v___y_2823_ = v___y_2842_;
v___y_2824_ = v___y_2837_;
v___y_2825_ = v_carry_2844_;
v___y_2826_ = v___y_2838_;
v___y_2827_ = v___y_2839_;
v___y_2828_ = v___y_2841_;
v___y_2829_ = v___x_2846_;
goto v___jp_2821_;
}
}
v___jp_2847_:
{
uint64_t v_position_2856_; uint64_t v___x_2857_; uint8_t v___x_2858_; 
v_position_2856_ = lean_uint64_add(v___y_2855_, v___y_2851_);
v___x_2857_ = 172ULL;
v___x_2858_ = lean_uint64_dec_lt(v_position_2856_, v___x_2857_);
if (v___x_2858_ == 0)
{
uint64_t v___x_2859_; uint8_t v___x_2860_; 
v___x_2859_ = 23ULL;
v___x_2860_ = lean_uint64_dec_lt(v___y_2855_, v___x_2859_);
if (v___x_2860_ == 0)
{
uint64_t v___x_2861_; uint8_t v___x_2862_; 
v___x_2861_ = lean_uint64_sub(v___y_2855_, v___x_2859_);
v___x_2862_ = lean_uint64_dec_eq(v___x_2861_, v___y_2854_);
if (v___x_2862_ == 0)
{
uint64_t v___x_2863_; uint8_t v___x_2864_; 
v___x_2863_ = 64ULL;
v___x_2864_ = lean_uint64_dec_lt(v___x_2861_, v___x_2863_);
if (v___x_2864_ == 0)
{
uint8_t v___x_2865_; 
v___x_2865_ = lean_uint64_dec_eq(v___x_2861_, v___x_2863_);
if (v___x_2865_ == 0)
{
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v___y_2854_;
goto v___jp_2835_;
}
else
{
uint64_t v___x_2866_; uint8_t v___x_2867_; 
v___x_2866_ = 9223372036854775808ULL;
v___x_2867_ = lean_uint64_dec_lt(v___x_2866_, v___y_2850_);
if (v___x_2867_ == 0)
{
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v___y_2854_;
goto v___jp_2835_;
}
else
{
uint64_t v___x_2868_; 
v___x_2868_ = 1ULL;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v___x_2868_;
goto v___jp_2835_;
}
}
}
else
{
uint64_t v_quotient_2869_; uint64_t v___x_2870_; uint64_t v___x_2871_; uint64_t v___x_2872_; uint64_t v_remainder_2873_; uint64_t v___x_2874_; uint64_t v_half_2875_; uint8_t v___x_2876_; 
v_quotient_2869_ = lean_uint64_shift_right(v___y_2850_, v___x_2861_);
v___x_2870_ = 1ULL;
v___x_2871_ = lean_uint64_shift_left(v___x_2870_, v___x_2861_);
v___x_2872_ = lean_uint64_sub(v___x_2871_, v___x_2870_);
v_remainder_2873_ = lean_uint64_land(v___y_2850_, v___x_2872_);
v___x_2874_ = lean_uint64_sub(v___x_2861_, v___x_2870_);
v_half_2875_ = lean_uint64_shift_left(v___x_2870_, v___x_2874_);
v___x_2876_ = lean_uint64_dec_lt(v_remainder_2873_, v_half_2875_);
if (v___x_2876_ == 0)
{
uint8_t v___x_2877_; 
v___x_2877_ = lean_uint64_dec_lt(v_half_2875_, v_remainder_2873_);
if (v___x_2877_ == 0)
{
uint64_t v___x_2878_; uint8_t v___x_2879_; 
v___x_2878_ = lean_uint64_land(v_quotient_2869_, v___x_2870_);
v___x_2879_ = lean_uint64_dec_eq(v___x_2878_, v___y_2854_);
if (v___x_2879_ == 0)
{
uint64_t v___x_2880_; 
v___x_2880_ = lean_uint64_add(v_quotient_2869_, v___x_2870_);
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v___x_2880_;
goto v___jp_2835_;
}
else
{
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v_quotient_2869_;
goto v___jp_2835_;
}
}
else
{
uint64_t v___x_2881_; 
v___x_2881_ = lean_uint64_add(v_quotient_2869_, v___x_2870_);
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v___x_2881_;
goto v___jp_2835_;
}
}
else
{
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v_quotient_2869_;
goto v___jp_2835_;
}
}
}
else
{
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v___y_2850_;
goto v___jp_2835_;
}
}
else
{
uint64_t v___x_2882_; uint64_t v___x_2883_; 
v___x_2882_ = lean_uint64_sub(v___x_2859_, v___y_2855_);
v___x_2883_ = lean_uint64_shift_left(v___y_2850_, v___x_2882_);
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2849_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v___y_2853_;
v___y_2840_ = v_position_2856_;
v___y_2841_ = v___y_2854_;
v___y_2842_ = v___x_2883_;
goto v___jp_2835_;
}
}
else
{
uint64_t v___x_2884_; uint8_t v___x_2885_; 
v___x_2884_ = 149ULL;
v___x_2885_ = lean_uint64_dec_lt(v___y_2851_, v___x_2884_);
if (v___x_2885_ == 0)
{
uint64_t v___x_2886_; uint64_t v___x_2887_; 
v___x_2886_ = lean_uint64_sub(v___y_2851_, v___x_2884_);
v___x_2887_ = lean_uint64_shift_left(v___y_2850_, v___x_2886_);
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v___x_2887_;
goto v___jp_2769_;
}
else
{
uint64_t v___x_2888_; uint8_t v___x_2889_; 
v___x_2888_ = lean_uint64_sub(v___x_2884_, v___y_2851_);
v___x_2889_ = lean_uint64_dec_eq(v___x_2888_, v___y_2854_);
if (v___x_2889_ == 0)
{
uint64_t v___x_2890_; uint8_t v___x_2891_; 
v___x_2890_ = 64ULL;
v___x_2891_ = lean_uint64_dec_lt(v___x_2888_, v___x_2890_);
if (v___x_2891_ == 0)
{
uint8_t v___x_2892_; 
v___x_2892_ = lean_uint64_dec_eq(v___x_2888_, v___x_2890_);
if (v___x_2892_ == 0)
{
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v___y_2854_;
goto v___jp_2769_;
}
else
{
uint64_t v___x_2893_; uint8_t v___x_2894_; 
v___x_2893_ = 9223372036854775808ULL;
v___x_2894_ = lean_uint64_dec_lt(v___x_2893_, v___y_2850_);
if (v___x_2894_ == 0)
{
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v___y_2854_;
goto v___jp_2769_;
}
else
{
uint64_t v___x_2895_; 
v___x_2895_ = 1ULL;
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v___x_2895_;
goto v___jp_2769_;
}
}
}
else
{
uint64_t v_quotient_2896_; uint64_t v___x_2897_; uint64_t v___x_2898_; uint64_t v___x_2899_; uint64_t v_remainder_2900_; uint64_t v___x_2901_; uint64_t v_half_2902_; uint8_t v___x_2903_; 
v_quotient_2896_ = lean_uint64_shift_right(v___y_2850_, v___x_2888_);
v___x_2897_ = 1ULL;
v___x_2898_ = lean_uint64_shift_left(v___x_2897_, v___x_2888_);
v___x_2899_ = lean_uint64_sub(v___x_2898_, v___x_2897_);
v_remainder_2900_ = lean_uint64_land(v___y_2850_, v___x_2899_);
v___x_2901_ = lean_uint64_sub(v___x_2888_, v___x_2897_);
v_half_2902_ = lean_uint64_shift_left(v___x_2897_, v___x_2901_);
v___x_2903_ = lean_uint64_dec_lt(v_remainder_2900_, v_half_2902_);
if (v___x_2903_ == 0)
{
uint8_t v___x_2904_; 
v___x_2904_ = lean_uint64_dec_lt(v_half_2902_, v_remainder_2900_);
if (v___x_2904_ == 0)
{
uint64_t v___x_2905_; uint8_t v___x_2906_; 
v___x_2905_ = lean_uint64_land(v_quotient_2896_, v___x_2897_);
v___x_2906_ = lean_uint64_dec_eq(v___x_2905_, v___y_2854_);
if (v___x_2906_ == 0)
{
uint64_t v___x_2907_; 
v___x_2907_ = lean_uint64_add(v_quotient_2896_, v___x_2897_);
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v___x_2907_;
goto v___jp_2769_;
}
else
{
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v_quotient_2896_;
goto v___jp_2769_;
}
}
else
{
uint64_t v___x_2908_; 
v___x_2908_ = lean_uint64_add(v_quotient_2896_, v___x_2897_);
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v___x_2908_;
goto v___jp_2769_;
}
}
else
{
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v_quotient_2896_;
goto v___jp_2769_;
}
}
}
else
{
v___y_2770_ = v___y_2849_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2854_;
v___y_2773_ = v___y_2850_;
goto v___jp_2769_;
}
}
}
}
v___jp_2909_:
{
uint64_t v___x_2919_; uint64_t v___x_2920_; uint8_t v___x_2921_; 
v___x_2919_ = 1ULL;
v___x_2920_ = lean_uint64_shift_right(v___y_2916_, v___x_2919_);
v___x_2921_ = lean_uint64_dec_eq(v___x_2920_, v___y_2917_);
if (v___x_2921_ == 0)
{
uint64_t v___x_2922_; 
v___x_2922_ = lean_uint64_add(v___y_2918_, v___x_2919_);
v___y_2848_ = v___y_2910_;
v___y_2849_ = v___y_2911_;
v___y_2850_ = v___y_2912_;
v___y_2851_ = v___y_2913_;
v___y_2852_ = v___y_2914_;
v___y_2853_ = v___y_2915_;
v___y_2854_ = v___y_2917_;
v___y_2855_ = v___x_2922_;
goto v___jp_2847_;
}
else
{
v___y_2848_ = v___y_2910_;
v___y_2849_ = v___y_2911_;
v___y_2850_ = v___y_2912_;
v___y_2851_ = v___y_2913_;
v___y_2852_ = v___y_2914_;
v___y_2853_ = v___y_2915_;
v___y_2854_ = v___y_2917_;
v___y_2855_ = v___y_2918_;
goto v___jp_2847_;
}
}
v___jp_2923_:
{
uint64_t v___x_2935_; uint8_t v___x_2936_; 
v___x_2935_ = lean_uint64_shift_right(v___y_2928_, v___y_2924_);
v___x_2936_ = lean_uint64_dec_eq(v___x_2935_, v___y_2933_);
if (v___x_2936_ == 0)
{
uint64_t v___x_2937_; 
v___x_2937_ = lean_uint64_add(v___y_2932_, v___y_2924_);
v___y_2910_ = v___y_2925_;
v___y_2911_ = v___y_2926_;
v___y_2912_ = v___y_2927_;
v___y_2913_ = v___y_2929_;
v___y_2914_ = v___y_2930_;
v___y_2915_ = v___y_2931_;
v___y_2916_ = v___y_2934_;
v___y_2917_ = v___y_2933_;
v___y_2918_ = v___x_2937_;
goto v___jp_2909_;
}
else
{
v___y_2910_ = v___y_2925_;
v___y_2911_ = v___y_2926_;
v___y_2912_ = v___y_2927_;
v___y_2913_ = v___y_2929_;
v___y_2914_ = v___y_2930_;
v___y_2915_ = v___y_2931_;
v___y_2916_ = v___y_2934_;
v___y_2917_ = v___y_2933_;
v___y_2918_ = v___y_2932_;
goto v___jp_2909_;
}
}
v___jp_2938_:
{
uint64_t v___x_2948_; uint64_t v___x_2949_; uint8_t v___x_2950_; 
v___x_2948_ = 2ULL;
v___x_2949_ = lean_uint64_shift_right(v___y_2942_, v___x_2948_);
v___x_2950_ = lean_uint64_dec_eq(v___x_2949_, v___y_2946_);
if (v___x_2950_ == 0)
{
v___y_2924_ = v___x_2948_;
v___y_2925_ = v___y_2939_;
v___y_2926_ = v___y_2940_;
v___y_2927_ = v___y_2941_;
v___y_2928_ = v___y_2942_;
v___y_2929_ = v___y_2943_;
v___y_2930_ = v___y_2944_;
v___y_2931_ = v___y_2945_;
v___y_2932_ = v___y_2947_;
v___y_2933_ = v___y_2946_;
v___y_2934_ = v___x_2949_;
goto v___jp_2923_;
}
else
{
v___y_2924_ = v___x_2948_;
v___y_2925_ = v___y_2939_;
v___y_2926_ = v___y_2940_;
v___y_2927_ = v___y_2941_;
v___y_2928_ = v___y_2942_;
v___y_2929_ = v___y_2943_;
v___y_2930_ = v___y_2944_;
v___y_2931_ = v___y_2945_;
v___y_2932_ = v___y_2947_;
v___y_2933_ = v___y_2946_;
v___y_2934_ = v___y_2942_;
goto v___jp_2923_;
}
}
v___jp_2951_:
{
uint64_t v___x_2963_; uint8_t v___x_2964_; 
v___x_2963_ = lean_uint64_shift_right(v___y_2957_, v___y_2955_);
v___x_2964_ = lean_uint64_dec_eq(v___x_2963_, v___y_2961_);
if (v___x_2964_ == 0)
{
uint64_t v___x_2965_; 
v___x_2965_ = lean_uint64_add(v___y_2958_, v___y_2955_);
v___y_2939_ = v___y_2952_;
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___y_2954_;
v___y_2942_ = v___y_2962_;
v___y_2943_ = v___y_2956_;
v___y_2944_ = v___y_2959_;
v___y_2945_ = v___y_2960_;
v___y_2946_ = v___y_2961_;
v___y_2947_ = v___x_2965_;
goto v___jp_2938_;
}
else
{
v___y_2939_ = v___y_2952_;
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___y_2954_;
v___y_2942_ = v___y_2962_;
v___y_2943_ = v___y_2956_;
v___y_2944_ = v___y_2959_;
v___y_2945_ = v___y_2960_;
v___y_2946_ = v___y_2961_;
v___y_2947_ = v___y_2958_;
goto v___jp_2938_;
}
}
v___jp_2966_:
{
uint64_t v___x_2976_; uint64_t v___x_2977_; uint8_t v___x_2978_; 
v___x_2976_ = 4ULL;
v___x_2977_ = lean_uint64_shift_right(v___y_2971_, v___x_2976_);
v___x_2978_ = lean_uint64_dec_eq(v___x_2977_, v___y_2974_);
if (v___x_2978_ == 0)
{
v___y_2952_ = v___y_2967_;
v___y_2953_ = v___y_2968_;
v___y_2954_ = v___y_2969_;
v___y_2955_ = v___x_2976_;
v___y_2956_ = v___y_2970_;
v___y_2957_ = v___y_2971_;
v___y_2958_ = v___y_2975_;
v___y_2959_ = v___y_2972_;
v___y_2960_ = v___y_2973_;
v___y_2961_ = v___y_2974_;
v___y_2962_ = v___x_2977_;
goto v___jp_2951_;
}
else
{
v___y_2952_ = v___y_2967_;
v___y_2953_ = v___y_2968_;
v___y_2954_ = v___y_2969_;
v___y_2955_ = v___x_2976_;
v___y_2956_ = v___y_2970_;
v___y_2957_ = v___y_2971_;
v___y_2958_ = v___y_2975_;
v___y_2959_ = v___y_2972_;
v___y_2960_ = v___y_2973_;
v___y_2961_ = v___y_2974_;
v___y_2962_ = v___y_2971_;
goto v___jp_2951_;
}
}
v___jp_2979_:
{
uint64_t v___x_2991_; uint8_t v___x_2992_; 
v___x_2991_ = lean_uint64_shift_right(v___y_2981_, v___y_2985_);
v___x_2992_ = lean_uint64_dec_eq(v___x_2991_, v___y_2989_);
if (v___x_2992_ == 0)
{
uint64_t v___x_2993_; 
v___x_2993_ = lean_uint64_add(v___y_2983_, v___y_2985_);
v___y_2967_ = v___y_2980_;
v___y_2968_ = v___y_2982_;
v___y_2969_ = v___y_2984_;
v___y_2970_ = v___y_2986_;
v___y_2971_ = v___y_2990_;
v___y_2972_ = v___y_2987_;
v___y_2973_ = v___y_2988_;
v___y_2974_ = v___y_2989_;
v___y_2975_ = v___x_2993_;
goto v___jp_2966_;
}
else
{
v___y_2967_ = v___y_2980_;
v___y_2968_ = v___y_2982_;
v___y_2969_ = v___y_2984_;
v___y_2970_ = v___y_2986_;
v___y_2971_ = v___y_2990_;
v___y_2972_ = v___y_2987_;
v___y_2973_ = v___y_2988_;
v___y_2974_ = v___y_2989_;
v___y_2975_ = v___y_2983_;
goto v___jp_2966_;
}
}
v___jp_2994_:
{
uint64_t v___x_3004_; uint64_t v___x_3005_; uint8_t v___x_3006_; 
v___x_3004_ = 8ULL;
v___x_3005_ = lean_uint64_shift_right(v___y_2997_, v___x_3004_);
v___x_3006_ = lean_uint64_dec_eq(v___x_3005_, v___y_3002_);
if (v___x_3006_ == 0)
{
v___y_2980_ = v___y_2995_;
v___y_2981_ = v___y_2997_;
v___y_2982_ = v___y_2996_;
v___y_2983_ = v___y_3003_;
v___y_2984_ = v___y_2998_;
v___y_2985_ = v___x_3004_;
v___y_2986_ = v___y_2999_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___y_3002_;
v___y_2990_ = v___x_3005_;
goto v___jp_2979_;
}
else
{
v___y_2980_ = v___y_2995_;
v___y_2981_ = v___y_2997_;
v___y_2982_ = v___y_2996_;
v___y_2983_ = v___y_3003_;
v___y_2984_ = v___y_2998_;
v___y_2985_ = v___x_3004_;
v___y_2986_ = v___y_2999_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___y_3002_;
v___y_2990_ = v___y_2997_;
goto v___jp_2979_;
}
}
v___jp_3007_:
{
uint64_t v___x_3019_; uint8_t v___x_3020_; 
v___x_3019_ = lean_uint64_shift_right(v___y_3013_, v___y_3011_);
v___x_3020_ = lean_uint64_dec_eq(v___x_3019_, v___y_3017_);
if (v___x_3020_ == 0)
{
uint64_t v___x_3021_; 
v___x_3021_ = lean_uint64_add(v___y_3008_, v___y_3011_);
v___y_2995_ = v___y_3009_;
v___y_2996_ = v___y_3010_;
v___y_2997_ = v___y_3018_;
v___y_2998_ = v___y_3012_;
v___y_2999_ = v___y_3014_;
v___y_3000_ = v___y_3015_;
v___y_3001_ = v___y_3016_;
v___y_3002_ = v___y_3017_;
v___y_3003_ = v___x_3021_;
goto v___jp_2994_;
}
else
{
v___y_2995_ = v___y_3009_;
v___y_2996_ = v___y_3010_;
v___y_2997_ = v___y_3018_;
v___y_2998_ = v___y_3012_;
v___y_2999_ = v___y_3014_;
v___y_3000_ = v___y_3015_;
v___y_3001_ = v___y_3016_;
v___y_3002_ = v___y_3017_;
v___y_3003_ = v___y_3008_;
goto v___jp_2994_;
}
}
v___jp_3022_:
{
uint64_t v___x_3032_; uint64_t v___x_3033_; uint8_t v___x_3034_; 
v___x_3032_ = 16ULL;
v___x_3033_ = lean_uint64_shift_right(v___y_3027_, v___x_3032_);
v___x_3034_ = lean_uint64_dec_eq(v___x_3033_, v___y_3030_);
if (v___x_3034_ == 0)
{
v___y_3008_ = v___y_3031_;
v___y_3009_ = v___y_3023_;
v___y_3010_ = v___y_3024_;
v___y_3011_ = v___x_3032_;
v___y_3012_ = v___y_3025_;
v___y_3013_ = v___y_3027_;
v___y_3014_ = v___y_3026_;
v___y_3015_ = v___y_3028_;
v___y_3016_ = v___y_3029_;
v___y_3017_ = v___y_3030_;
v___y_3018_ = v___x_3033_;
goto v___jp_3007_;
}
else
{
v___y_3008_ = v___y_3031_;
v___y_3009_ = v___y_3023_;
v___y_3010_ = v___y_3024_;
v___y_3011_ = v___x_3032_;
v___y_3012_ = v___y_3025_;
v___y_3013_ = v___y_3027_;
v___y_3014_ = v___y_3026_;
v___y_3015_ = v___y_3028_;
v___y_3016_ = v___y_3029_;
v___y_3017_ = v___y_3030_;
v___y_3018_ = v___y_3027_;
goto v___jp_3007_;
}
}
v___jp_3035_:
{
uint64_t v___x_3045_; uint8_t v___x_3046_; 
v___x_3045_ = lean_uint64_shift_right(v___y_3038_, v___y_3042_);
v___x_3046_ = lean_uint64_dec_eq(v___x_3045_, v___y_3043_);
if (v___x_3046_ == 0)
{
v___y_3023_ = v___y_3036_;
v___y_3024_ = v___y_3037_;
v___y_3025_ = v___y_3038_;
v___y_3026_ = v___y_3039_;
v___y_3027_ = v___y_3044_;
v___y_3028_ = v___y_3040_;
v___y_3029_ = v___y_3041_;
v___y_3030_ = v___y_3043_;
v___y_3031_ = v___y_3042_;
goto v___jp_3022_;
}
else
{
v___y_3023_ = v___y_3036_;
v___y_3024_ = v___y_3037_;
v___y_3025_ = v___y_3038_;
v___y_3026_ = v___y_3039_;
v___y_3027_ = v___y_3044_;
v___y_3028_ = v___y_3040_;
v___y_3029_ = v___y_3041_;
v___y_3030_ = v___y_3043_;
v___y_3031_ = v___y_3043_;
goto v___jp_3022_;
}
}
v___jp_3047_:
{
uint64_t v___x_3056_; uint64_t v___x_3057_; uint8_t v___x_3058_; 
v___x_3056_ = lean_uint64_mul(v___y_3050_, v___y_3054_);
v___x_3057_ = 0ULL;
v___x_3058_ = lean_uint64_dec_eq(v___x_3056_, v___x_3057_);
if (v___x_3058_ == 0)
{
uint64_t v___x_3059_; uint64_t v___x_3060_; uint64_t v___x_3061_; uint8_t v___x_3062_; 
v___x_3059_ = lean_uint64_add(v___y_3052_, v___y_3055_);
v___x_3060_ = 32ULL;
v___x_3061_ = lean_uint64_shift_right(v___x_3056_, v___x_3060_);
v___x_3062_ = lean_uint64_dec_eq(v___x_3061_, v___x_3057_);
if (v___x_3062_ == 0)
{
v___y_3036_ = v___y_3048_;
v___y_3037_ = v___y_3049_;
v___y_3038_ = v___x_3056_;
v___y_3039_ = v___x_3059_;
v___y_3040_ = v___y_3051_;
v___y_3041_ = v___y_3053_;
v___y_3042_ = v___x_3060_;
v___y_3043_ = v___x_3057_;
v___y_3044_ = v___x_3061_;
goto v___jp_3035_;
}
else
{
v___y_3036_ = v___y_3048_;
v___y_3037_ = v___y_3049_;
v___y_3038_ = v___x_3056_;
v___y_3039_ = v___x_3059_;
v___y_3040_ = v___y_3051_;
v___y_3041_ = v___y_3053_;
v___y_3042_ = v___x_3060_;
v___y_3043_ = v___x_3057_;
v___y_3044_ = v___x_3056_;
goto v___jp_3035_;
}
}
else
{
if (v___y_3053_ == 0)
{
uint32_t v___x_3063_; 
v___x_3063_ = 0;
return v___x_3063_;
}
else
{
uint32_t v___x_3064_; 
v___x_3064_ = 2147483648;
return v___x_3064_;
}
}
}
v___jp_3065_:
{
uint64_t v___x_3074_; uint64_t v___x_3075_; uint8_t v___x_3076_; 
v___x_3074_ = lean_uint32_to_uint64(v___y_3069_);
v___x_3075_ = 0ULL;
v___x_3076_ = lean_uint64_dec_eq(v___x_3074_, v___x_3075_);
if (v___x_3076_ == 0)
{
uint64_t v___x_3077_; uint64_t v___x_3078_; 
v___x_3077_ = 1ULL;
v___x_3078_ = lean_uint64_sub(v___x_3074_, v___x_3077_);
v___y_3048_ = v___y_3066_;
v___y_3049_ = v___y_3068_;
v___y_3050_ = v___y_3067_;
v___y_3051_ = v___y_3070_;
v___y_3052_ = v___y_3073_;
v___y_3053_ = v___y_3071_;
v___y_3054_ = v___y_3072_;
v___y_3055_ = v___x_3078_;
goto v___jp_3047_;
}
else
{
v___y_3048_ = v___y_3066_;
v___y_3049_ = v___y_3068_;
v___y_3050_ = v___y_3067_;
v___y_3051_ = v___y_3070_;
v___y_3052_ = v___y_3073_;
v___y_3053_ = v___y_3071_;
v___y_3054_ = v___y_3072_;
v___y_3055_ = v___x_3075_;
goto v___jp_3047_;
}
}
v___jp_3079_:
{
uint64_t v___x_3088_; uint64_t v___x_3089_; uint8_t v___x_3090_; 
v___x_3088_ = lean_uint32_to_uint64(v___y_3083_);
v___x_3089_ = 0ULL;
v___x_3090_ = lean_uint64_dec_eq(v___x_3088_, v___x_3089_);
if (v___x_3090_ == 0)
{
uint64_t v___x_3091_; uint64_t v___x_3092_; 
v___x_3091_ = 1ULL;
v___x_3092_ = lean_uint64_sub(v___x_3088_, v___x_3091_);
v___y_3066_ = v___y_3080_;
v___y_3067_ = v___y_3082_;
v___y_3068_ = v___y_3081_;
v___y_3069_ = v___y_3084_;
v___y_3070_ = v___y_3085_;
v___y_3071_ = v___y_3086_;
v___y_3072_ = v___y_3087_;
v___y_3073_ = v___x_3092_;
goto v___jp_3065_;
}
else
{
v___y_3066_ = v___y_3080_;
v___y_3067_ = v___y_3082_;
v___y_3068_ = v___y_3081_;
v___y_3069_ = v___y_3084_;
v___y_3070_ = v___y_3085_;
v___y_3071_ = v___y_3086_;
v___y_3072_ = v___y_3087_;
v___y_3073_ = v___x_3089_;
goto v___jp_3065_;
}
}
v___jp_3093_:
{
uint32_t v___x_3102_; uint8_t v___x_3103_; 
v___x_3102_ = 0;
v___x_3103_ = lean_uint32_dec_eq(v___y_3097_, v___x_3102_);
if (v___x_3103_ == 0)
{
uint64_t v___x_3104_; uint64_t v___x_3105_; uint64_t v___x_3106_; 
v___x_3104_ = lean_uint32_to_uint64(v___y_3100_);
v___x_3105_ = 8388608ULL;
v___x_3106_ = lean_uint64_lor(v___x_3104_, v___x_3105_);
v___y_3080_ = v___y_3094_;
v___y_3081_ = v___y_3095_;
v___y_3082_ = v___y_3101_;
v___y_3083_ = v___y_3096_;
v___y_3084_ = v___y_3097_;
v___y_3085_ = v___y_3098_;
v___y_3086_ = v___y_3099_;
v___y_3087_ = v___x_3106_;
goto v___jp_3079_;
}
else
{
uint64_t v___x_3107_; 
v___x_3107_ = lean_uint32_to_uint64(v___y_3100_);
v___y_3080_ = v___y_3094_;
v___y_3081_ = v___y_3095_;
v___y_3082_ = v___y_3101_;
v___y_3083_ = v___y_3096_;
v___y_3084_ = v___y_3097_;
v___y_3085_ = v___y_3098_;
v___y_3086_ = v___y_3099_;
v___y_3087_ = v___x_3107_;
goto v___jp_3079_;
}
}
v___jp_3108_:
{
uint32_t v___x_3114_; uint32_t v_xFraction_3115_; uint32_t v_yFraction_3116_; uint32_t v___x_3117_; uint8_t v___x_3118_; 
v___x_3114_ = 8388607;
v_xFraction_3115_ = lean_uint32_land(v_x_2757_, v___x_3114_);
v_yFraction_3116_ = lean_uint32_land(v_y_2758_, v___x_3114_);
v___x_3117_ = 0;
v___x_3118_ = lean_uint32_dec_eq(v___y_3110_, v___x_3117_);
if (v___x_3118_ == 0)
{
uint64_t v___x_3119_; uint64_t v___x_3120_; uint64_t v___x_3121_; 
v___x_3119_ = lean_uint32_to_uint64(v_xFraction_3115_);
v___x_3120_ = 8388608ULL;
v___x_3121_ = lean_uint64_lor(v___x_3119_, v___x_3120_);
v___y_3094_ = v___y_3109_;
v___y_3095_ = v___x_3114_;
v___y_3096_ = v___y_3110_;
v___y_3097_ = v___y_3111_;
v___y_3098_ = v___y_3112_;
v___y_3099_ = v___y_3113_;
v___y_3100_ = v_yFraction_3116_;
v___y_3101_ = v___x_3121_;
goto v___jp_3093_;
}
else
{
uint64_t v___x_3122_; 
v___x_3122_ = lean_uint32_to_uint64(v_xFraction_3115_);
v___y_3094_ = v___y_3109_;
v___y_3095_ = v___x_3114_;
v___y_3096_ = v___y_3110_;
v___y_3097_ = v___y_3111_;
v___y_3098_ = v___y_3112_;
v___y_3099_ = v___y_3113_;
v___y_3100_ = v_yFraction_3116_;
v___y_3101_ = v___x_3122_;
goto v___jp_3093_;
}
}
v___jp_3123_:
{
uint8_t v___x_3128_; 
v___x_3128_ = 1;
v___y_3109_ = v___y_3124_;
v___y_3110_ = v___y_3125_;
v___y_3111_ = v___y_3126_;
v___y_3112_ = v___y_3127_;
v___y_3113_ = v___x_3128_;
goto v___jp_3108_;
}
v___jp_3129_:
{
if (v___y_3134_ == 0)
{
if (v___y_3136_ == 0)
{
v___y_3109_ = v___y_3130_;
v___y_3110_ = v___y_3132_;
v___y_3111_ = v___y_3133_;
v___y_3112_ = v___y_3135_;
v___y_3113_ = v___y_3131_;
goto v___jp_3108_;
}
else
{
v___y_3124_ = v___y_3130_;
v___y_3125_ = v___y_3132_;
v___y_3126_ = v___y_3133_;
v___y_3127_ = v___y_3135_;
goto v___jp_3123_;
}
}
else
{
if (v___y_3136_ == 0)
{
v___y_3124_ = v___y_3130_;
v___y_3125_ = v___y_3132_;
v___y_3126_ = v___y_3133_;
v___y_3127_ = v___y_3135_;
goto v___jp_3123_;
}
else
{
v___y_3109_ = v___y_3130_;
v___y_3110_ = v___y_3132_;
v___y_3111_ = v___y_3133_;
v___y_3112_ = v___y_3135_;
v___y_3113_ = v___y_3131_;
goto v___jp_3108_;
}
}
}
v___jp_3137_:
{
uint32_t v___x_3144_; uint32_t v___x_3145_; uint32_t v___x_3146_; uint8_t v___x_3147_; 
v___x_3144_ = 2147483648;
v___x_3145_ = lean_uint32_land(v_y_2758_, v___x_3144_);
v___x_3146_ = 0;
v___x_3147_ = lean_uint32_dec_eq(v___x_3145_, v___x_3146_);
if (v___x_3147_ == 0)
{
uint8_t v___x_3148_; 
v___x_3148_ = 1;
v___y_3130_ = v___y_3138_;
v___y_3131_ = v___y_3139_;
v___y_3132_ = v___y_3140_;
v___y_3133_ = v___y_3141_;
v___y_3134_ = v___y_3143_;
v___y_3135_ = v___y_3142_;
v___y_3136_ = v___x_3148_;
goto v___jp_3129_;
}
else
{
v___y_3130_ = v___y_3138_;
v___y_3131_ = v___y_3139_;
v___y_3132_ = v___y_3140_;
v___y_3133_ = v___y_3141_;
v___y_3134_ = v___y_3143_;
v___y_3135_ = v___y_3142_;
v___y_3136_ = v___y_3139_;
goto v___jp_3129_;
}
}
v___jp_3149_:
{
if (v___y_3150_ == 0)
{
uint32_t v___x_3151_; uint32_t v___x_3152_; uint32_t v___x_3153_; uint32_t v_xExponent_3154_; uint32_t v___x_3155_; uint32_t v_yExponent_3156_; uint32_t v___x_3157_; uint32_t v___x_3158_; uint32_t v___x_3159_; uint8_t v___x_3160_; 
v___x_3151_ = 23;
v___x_3152_ = lean_uint32_shift_right(v_x_2757_, v___x_3151_);
v___x_3153_ = 255;
v_xExponent_3154_ = lean_uint32_land(v___x_3152_, v___x_3153_);
v___x_3155_ = lean_uint32_shift_right(v_y_2758_, v___x_3151_);
v_yExponent_3156_ = lean_uint32_land(v___x_3155_, v___x_3153_);
v___x_3157_ = 2147483648;
v___x_3158_ = lean_uint32_land(v_x_2757_, v___x_3157_);
v___x_3159_ = 0;
v___x_3160_ = lean_uint32_dec_eq(v___x_3158_, v___x_3159_);
if (v___x_3160_ == 0)
{
uint8_t v___x_3161_; 
v___x_3161_ = 1;
v___y_3138_ = v___x_3153_;
v___y_3139_ = v___y_3150_;
v___y_3140_ = v_xExponent_3154_;
v___y_3141_ = v_yExponent_3156_;
v___y_3142_ = v___x_3151_;
v___y_3143_ = v___x_3161_;
goto v___jp_3137_;
}
else
{
v___y_3138_ = v___x_3153_;
v___y_3139_ = v___y_3150_;
v___y_3140_ = v_xExponent_3154_;
v___y_3141_ = v_yExponent_3156_;
v___y_3142_ = v___x_3151_;
v___y_3143_ = v___y_3150_;
goto v___jp_3137_;
}
}
else
{
lean_object* v___x_3162_; lean_object* v___x_3163_; lean_object* v___x_3164_; lean_object* v___x_3165_; uint32_t v___x_3166_; 
v___x_3162_ = ((lean_object*)(lp_competition_Submission_TunedAdd_add___closed__0));
v___x_3163_ = lean_uint32_to_nat(v_x_2757_);
v___x_3164_ = lean_uint32_to_nat(v_y_2758_);
v___x_3165_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_3162_, v___x_3163_, v___x_3164_);
v___x_3166_ = lean_uint32_of_nat(v___x_3165_);
lean_dec(v___x_3165_);
return v___x_3166_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mul___boxed(lean_object* v_x_3173_, lean_object* v_y_3174_){
_start:
{
uint32_t v_x_boxed_3175_; uint32_t v_y_boxed_3176_; uint32_t v_res_3177_; lean_object* v_r_3178_; 
v_x_boxed_3175_ = lean_unbox_uint32(v_x_3173_);
lean_dec(v_x_3173_);
v_y_boxed_3176_ = lean_unbox_uint32(v_y_3174_);
lean_dec(v_y_3174_);
v_res_3177_ = lp_competition_Submission_FastMul_mul(v_x_boxed_3175_, v_y_boxed_3176_);
v_r_3178_ = lean_box_uint32(v_res_3177_);
return v_r_3178_;
}
}
static uint8_t _init_lp_competition_Submission_FastMul_Plan(void){
_start:
{
uint8_t v___x_3180_; 
v___x_3180_ = 2;
return v___x_3180_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec(uint32_t v_z_3181_){
_start:
{
lean_object* v___x_3182_; 
v___x_3182_ = lean_uint32_to_nat(v_z_3181_);
return v___x_3182_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec___boxed(lean_object* v_z_3183_){
_start:
{
uint32_t v_z_boxed_3184_; lean_object* v_res_3185_; 
v_z_boxed_3184_ = lean_unbox_uint32(v_z_3183_);
lean_dec(v_z_3183_);
v_res_3185_ = lp_competition_Submission_FastMul_dec(v_z_boxed_3184_);
return v_res_3185_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t v_x_3186_, uint32_t v_y_3187_){
_start:
{
uint32_t v___y_3189_; uint32_t v___y_3193_; uint32_t v___y_3197_; uint32_t v___y_3198_; uint64_t v___y_3203_; lean_object* v___y_3204_; uint64_t v___y_3205_; uint32_t v___y_3220_; uint32_t v___y_3221_; uint32_t v___y_3222_; uint32_t v___y_3223_; uint32_t v___y_3224_; uint32_t v___y_3232_; uint32_t v___y_3233_; uint32_t v___y_3234_; lean_object* v___y_3235_; uint32_t v___y_3236_; uint64_t v___y_3241_; uint32_t v___y_3242_; uint32_t v___y_3243_; lean_object* v___y_3244_; uint64_t v___y_3245_; uint64_t v___y_3246_; uint32_t v___y_3256_; uint64_t v___y_3257_; uint32_t v___y_3258_; uint8_t v___y_3259_; uint64_t v___y_3260_; lean_object* v___y_3261_; uint64_t v___y_3262_; uint64_t v___y_3270_; uint32_t v___y_3271_; uint32_t v___y_3272_; uint64_t v___y_3273_; lean_object* v___y_3274_; uint64_t v___y_3275_; lean_object* v___y_3281_; uint32_t v___y_3282_; uint64_t v___y_3283_; uint64_t v___y_3284_; uint32_t v___y_3285_; uint64_t v___y_3286_; lean_object* v___y_3287_; uint64_t v___y_3288_; uint32_t v___y_3352_; lean_object* v___y_3353_; uint64_t v___y_3354_; uint64_t v___y_3355_; uint32_t v___y_3356_; uint64_t v___y_3357_; uint64_t v___y_3358_; lean_object* v___y_3359_; uint64_t v___y_3360_; uint64_t v___y_3366_; lean_object* v___y_3367_; uint32_t v___y_3368_; uint64_t v___y_3369_; uint32_t v___y_3370_; uint64_t v___y_3371_; uint64_t v___y_3372_; uint64_t v___y_3373_; uint64_t v___y_3374_; lean_object* v___y_3375_; uint64_t v___y_3376_; uint32_t v___y_3381_; lean_object* v___y_3382_; uint64_t v___y_3383_; uint64_t v___y_3384_; uint32_t v___y_3385_; uint64_t v___y_3386_; uint64_t v___y_3387_; lean_object* v___y_3388_; uint64_t v___y_3389_; uint64_t v___y_3394_; uint64_t v___y_3395_; lean_object* v___y_3396_; uint32_t v___y_3397_; uint64_t v___y_3398_; uint64_t v___y_3399_; uint32_t v___y_3400_; uint64_t v___y_3401_; uint64_t v___y_3402_; lean_object* v___y_3403_; uint64_t v___y_3404_; uint32_t v___y_3409_; lean_object* v___y_3410_; uint64_t v___y_3411_; uint64_t v___y_3412_; uint64_t v___y_3413_; uint32_t v___y_3414_; uint64_t v___y_3415_; lean_object* v___y_3416_; uint64_t v___y_3417_; uint64_t v___y_3422_; uint64_t v___y_3423_; lean_object* v___y_3424_; uint32_t v___y_3425_; uint64_t v___y_3426_; uint32_t v___y_3427_; uint64_t v___y_3428_; uint64_t v___y_3429_; uint64_t v___y_3430_; lean_object* v___y_3431_; uint64_t v___y_3432_; uint32_t v___y_3437_; lean_object* v___y_3438_; uint64_t v___y_3439_; uint64_t v___y_3440_; uint32_t v___y_3441_; uint64_t v___y_3442_; uint64_t v___y_3443_; lean_object* v___y_3444_; uint64_t v___y_3445_; uint64_t v___y_3450_; lean_object* v___y_3451_; uint32_t v___y_3452_; uint64_t v___y_3453_; uint32_t v___y_3454_; uint64_t v___y_3455_; uint64_t v___y_3456_; uint64_t v___y_3457_; uint64_t v___y_3458_; lean_object* v___y_3459_; uint64_t v___y_3460_; uint32_t v___y_3465_; lean_object* v___y_3466_; uint64_t v___y_3467_; uint64_t v___y_3468_; uint32_t v___y_3469_; uint64_t v___y_3470_; uint64_t v___y_3471_; lean_object* v___y_3472_; uint64_t v___y_3473_; uint64_t v___y_3478_; lean_object* v___y_3479_; uint32_t v___y_3480_; uint64_t v___y_3481_; uint32_t v___y_3482_; uint64_t v___y_3483_; uint64_t v___y_3484_; lean_object* v___y_3485_; uint64_t v___y_3486_; uint32_t v___y_3491_; uint32_t v___y_3492_; uint64_t v___y_3493_; lean_object* v_fst_3494_; lean_object* v_snd_3495_; uint32_t v___y_3510_; uint32_t v___y_3511_; lean_object* v___y_3516_; uint64_t v___y_3517_; uint64_t v___y_3518_; uint32_t v___y_3533_; uint32_t v___y_3534_; uint32_t v___y_3535_; uint32_t v___y_3536_; uint32_t v___y_3537_; uint32_t v___y_3545_; uint32_t v___y_3546_; uint32_t v___y_3547_; lean_object* v___y_3548_; uint32_t v___y_3549_; uint32_t v___y_3554_; uint32_t v___y_3555_; lean_object* v___y_3556_; uint64_t v___y_3557_; uint64_t v___y_3558_; uint64_t v___y_3559_; uint32_t v___y_3569_; uint32_t v___y_3570_; uint64_t v___y_3571_; lean_object* v___y_3572_; uint8_t v___y_3573_; uint64_t v___y_3574_; uint64_t v___y_3575_; uint64_t v___y_3583_; uint32_t v___y_3584_; uint32_t v___y_3585_; lean_object* v___y_3586_; uint64_t v___y_3587_; uint64_t v___y_3588_; uint64_t v___y_3594_; uint32_t v___y_3595_; uint32_t v___y_3596_; lean_object* v___y_3597_; uint64_t v___y_3598_; lean_object* v___y_3599_; uint64_t v___y_3600_; uint64_t v___y_3601_; uint64_t v___y_3665_; uint32_t v___y_3666_; uint32_t v___y_3667_; lean_object* v___y_3668_; lean_object* v___y_3669_; uint64_t v___y_3670_; uint64_t v___y_3671_; uint64_t v___y_3672_; uint64_t v___y_3673_; uint64_t v___y_3679_; uint32_t v___y_3680_; uint64_t v___y_3681_; uint64_t v___y_3682_; uint32_t v___y_3683_; lean_object* v___y_3684_; uint64_t v___y_3685_; uint64_t v___y_3686_; lean_object* v___y_3687_; uint64_t v___y_3688_; uint64_t v___y_3689_; uint64_t v___y_3694_; uint32_t v___y_3695_; uint32_t v___y_3696_; lean_object* v___y_3697_; uint64_t v___y_3698_; lean_object* v___y_3699_; uint64_t v___y_3700_; uint64_t v___y_3701_; uint64_t v___y_3702_; uint64_t v___y_3707_; uint64_t v___y_3708_; uint32_t v___y_3709_; uint64_t v___y_3710_; uint32_t v___y_3711_; uint64_t v___y_3712_; lean_object* v___y_3713_; uint64_t v___y_3714_; lean_object* v___y_3715_; uint64_t v___y_3716_; uint64_t v___y_3717_; uint64_t v___y_3722_; uint64_t v___y_3723_; uint32_t v___y_3724_; uint32_t v___y_3725_; lean_object* v___y_3726_; lean_object* v___y_3727_; uint64_t v___y_3728_; uint64_t v___y_3729_; uint64_t v___y_3730_; uint64_t v___y_3735_; uint64_t v___y_3736_; uint32_t v___y_3737_; uint64_t v___y_3738_; uint32_t v___y_3739_; lean_object* v___y_3740_; uint64_t v___y_3741_; lean_object* v___y_3742_; uint64_t v___y_3743_; uint64_t v___y_3744_; uint64_t v___y_3745_; uint64_t v___y_3750_; uint32_t v___y_3751_; uint32_t v___y_3752_; lean_object* v___y_3753_; lean_object* v___y_3754_; uint64_t v___y_3755_; uint64_t v___y_3756_; uint64_t v___y_3757_; uint64_t v___y_3758_; uint64_t v___y_3763_; uint32_t v___y_3764_; uint32_t v___y_3765_; uint64_t v___y_3766_; uint64_t v___y_3767_; uint64_t v___y_3768_; lean_object* v___y_3769_; uint64_t v___y_3770_; lean_object* v___y_3771_; uint64_t v___y_3772_; uint64_t v___y_3773_; uint64_t v___y_3778_; uint32_t v___y_3779_; uint32_t v___y_3780_; uint64_t v___y_3781_; lean_object* v___y_3782_; lean_object* v___y_3783_; uint64_t v___y_3784_; uint64_t v___y_3785_; uint64_t v___y_3786_; uint64_t v___y_3791_; uint32_t v___y_3792_; uint64_t v___y_3793_; uint32_t v___y_3794_; lean_object* v___y_3795_; uint64_t v___y_3796_; lean_object* v___y_3797_; uint64_t v___y_3798_; uint64_t v___y_3799_; uint64_t v___y_3804_; uint32_t v___y_3805_; uint32_t v___y_3806_; lean_object* v_fst_3807_; lean_object* v_snd_3808_; uint64_t v___y_3823_; uint64_t v___y_3824_; uint8_t v___y_3825_; uint32_t v___y_3826_; uint32_t v___y_3827_; uint8_t v___y_3828_; uint64_t v___y_3829_; uint8_t v___y_3830_; uint64_t v___y_3842_; uint64_t v___y_3843_; uint8_t v___y_3844_; uint32_t v___y_3845_; uint8_t v___y_3846_; uint32_t v___y_3847_; uint64_t v___y_3848_; uint8_t v___y_3849_; uint64_t v___y_3854_; uint8_t v___y_3855_; uint32_t v___y_3856_; uint32_t v___y_3857_; uint8_t v___y_3858_; uint64_t v___y_3859_; uint64_t v___y_3860_; uint8_t v___y_3861_; uint64_t v___y_3873_; uint8_t v___y_3874_; uint32_t v___y_3875_; uint8_t v___y_3876_; uint32_t v___y_3877_; uint64_t v___y_3878_; uint64_t v___y_3879_; uint8_t v___y_3880_; uint8_t v___y_3885_; uint32_t v___y_3886_; uint8_t v___y_3887_; uint32_t v___y_3888_; uint64_t v___y_3889_; uint64_t v___y_3890_; uint64_t v___y_3891_; uint64_t v___y_3892_; uint8_t v___y_3903_; uint32_t v___y_3904_; uint8_t v___y_3905_; uint32_t v___y_3906_; uint64_t v___y_3907_; uint32_t v___y_3908_; uint64_t v___y_3909_; uint64_t v___y_3910_; uint32_t v___y_3917_; uint8_t v___y_3918_; uint32_t v___y_3919_; uint32_t v___y_3920_; uint8_t v___y_3921_; uint64_t v___y_3922_; uint32_t v___y_3923_; uint64_t v___y_3924_; uint32_t v___y_3931_; uint8_t v___y_3932_; uint32_t v___y_3933_; uint8_t v___y_3934_; uint32_t v___y_3935_; uint32_t v___y_3936_; uint64_t v___y_3937_; uint32_t v___y_3947_; uint32_t v___y_3948_; uint32_t v___y_3949_; uint8_t v___y_3950_; uint32_t v___y_3951_; uint8_t v___y_3952_; uint32_t v___y_3962_; uint8_t v___y_3963_; uint32_t v___y_3964_; uint32_t v___y_3965_; uint32_t v___y_3966_; uint8_t v___y_3967_; uint8_t v___y_3974_; uint32_t v___x_3991_; uint32_t v___x_3992_; uint32_t v___x_3993_; uint32_t v___x_3994_; uint8_t v___x_3995_; 
v___x_3991_ = 4278190079;
v___x_3992_ = 1;
v___x_3993_ = lean_uint32_shift_left(v_x_3186_, v___x_3992_);
v___x_3994_ = lean_uint32_sub(v___x_3993_, v___x_3992_);
v___x_3995_ = lean_uint32_dec_le(v___x_3991_, v___x_3994_);
if (v___x_3995_ == 0)
{
uint32_t v___x_3996_; uint32_t v___x_3997_; uint8_t v___x_3998_; 
v___x_3996_ = lean_uint32_shift_left(v_y_3187_, v___x_3992_);
v___x_3997_ = lean_uint32_sub(v___x_3996_, v___x_3992_);
v___x_3998_ = lean_uint32_dec_le(v___x_3991_, v___x_3997_);
v___y_3974_ = v___x_3998_;
goto v___jp_3973_;
}
else
{
v___y_3974_ = v___x_3995_;
goto v___jp_3973_;
}
v___jp_3188_:
{
uint32_t v___x_3190_; uint32_t v___x_3191_; 
v___x_3190_ = 8388608;
v___x_3191_ = lean_uint32_lor(v___y_3189_, v___x_3190_);
return v___x_3191_;
}
v___jp_3192_:
{
uint32_t v___x_3194_; uint32_t v___x_3195_; 
v___x_3194_ = 8388608;
v___x_3195_ = lean_uint32_lor(v___y_3193_, v___x_3194_);
return v___x_3195_;
}
v___jp_3196_:
{
uint32_t v___x_3199_; uint32_t v___x_3200_; uint32_t v___x_3201_; 
v___x_3199_ = 8388607;
v___x_3200_ = lean_uint32_land(v___y_3197_, v___x_3199_);
v___x_3201_ = lean_uint32_lor(v___y_3198_, v___x_3200_);
return v___x_3201_;
}
v___jp_3202_:
{
uint8_t v___x_3206_; 
v___x_3206_ = lean_uint64_dec_eq(v___y_3205_, v___y_3203_);
if (v___x_3206_ == 0)
{
uint64_t v___x_3207_; uint8_t v___x_3208_; 
v___x_3207_ = 8388608ULL;
v___x_3208_ = lean_uint64_dec_eq(v___y_3205_, v___x_3207_);
if (v___x_3208_ == 0)
{
uint32_t v___x_3209_; uint8_t v___x_3210_; 
v___x_3209_ = lean_uint64_to_uint32(v___y_3205_);
v___x_3210_ = lean_unbox(v___y_3204_);
lean_dec(v___y_3204_);
if (v___x_3210_ == 0)
{
uint32_t v___x_3211_; 
v___x_3211_ = 0;
v___y_3197_ = v___x_3209_;
v___y_3198_ = v___x_3211_;
goto v___jp_3196_;
}
else
{
uint32_t v___x_3212_; 
v___x_3212_ = 2147483648;
v___y_3197_ = v___x_3209_;
v___y_3198_ = v___x_3212_;
goto v___jp_3196_;
}
}
else
{
uint8_t v___x_3213_; 
v___x_3213_ = lean_unbox(v___y_3204_);
lean_dec(v___y_3204_);
if (v___x_3213_ == 0)
{
uint32_t v___x_3214_; 
v___x_3214_ = 0;
v___y_3189_ = v___x_3214_;
goto v___jp_3188_;
}
else
{
uint32_t v___x_3215_; 
v___x_3215_ = 2147483648;
v___y_3189_ = v___x_3215_;
goto v___jp_3188_;
}
}
}
else
{
uint8_t v___x_3216_; 
v___x_3216_ = lean_unbox(v___y_3204_);
lean_dec(v___y_3204_);
if (v___x_3216_ == 0)
{
uint32_t v___x_3217_; 
v___x_3217_ = 0;
return v___x_3217_;
}
else
{
uint32_t v___x_3218_; 
v___x_3218_ = 2147483648;
return v___x_3218_;
}
}
}
v___jp_3219_:
{
uint32_t v___x_3225_; uint32_t v___x_3226_; uint32_t v___x_3227_; uint32_t v___x_3228_; uint32_t v___x_3229_; uint32_t v___x_3230_; 
v___x_3225_ = lean_uint32_land(v___y_3223_, v___y_3222_);
v___x_3226_ = lean_uint32_shift_left(v___x_3225_, v___y_3221_);
v___x_3227_ = lean_uint32_lor(v___y_3224_, v___x_3226_);
v___x_3228_ = 8388607;
v___x_3229_ = lean_uint32_land(v___y_3220_, v___x_3228_);
v___x_3230_ = lean_uint32_lor(v___x_3227_, v___x_3229_);
return v___x_3230_;
}
v___jp_3231_:
{
uint8_t v___x_3237_; 
v___x_3237_ = lean_unbox(v___y_3235_);
lean_dec(v___y_3235_);
if (v___x_3237_ == 0)
{
uint32_t v___x_3238_; 
v___x_3238_ = 0;
v___y_3220_ = v___y_3236_;
v___y_3221_ = v___y_3232_;
v___y_3222_ = v___y_3233_;
v___y_3223_ = v___y_3234_;
v___y_3224_ = v___x_3238_;
goto v___jp_3219_;
}
else
{
uint32_t v___x_3239_; 
v___x_3239_ = 2147483648;
v___y_3220_ = v___y_3236_;
v___y_3221_ = v___y_3232_;
v___y_3222_ = v___y_3233_;
v___y_3223_ = v___y_3234_;
v___y_3224_ = v___x_3239_;
goto v___jp_3219_;
}
}
v___jp_3240_:
{
uint64_t v___x_3247_; uint64_t v_encodedExponent_3248_; uint32_t v___x_3249_; uint64_t v___x_3250_; uint8_t v___x_3251_; 
v___x_3247_ = 171ULL;
v_encodedExponent_3248_ = lean_uint64_sub(v___y_3245_, v___x_3247_);
v___x_3249_ = lean_uint64_to_uint32(v_encodedExponent_3248_);
v___x_3250_ = 8388608ULL;
v___x_3251_ = lean_uint64_dec_lt(v___y_3246_, v___x_3250_);
if (v___x_3251_ == 0)
{
uint64_t v___x_3252_; uint32_t v___x_3253_; 
v___x_3252_ = lean_uint64_sub(v___y_3246_, v___x_3250_);
v___x_3253_ = lean_uint64_to_uint32(v___x_3252_);
v___y_3232_ = v___y_3242_;
v___y_3233_ = v___y_3243_;
v___y_3234_ = v___x_3249_;
v___y_3235_ = v___y_3244_;
v___y_3236_ = v___x_3253_;
goto v___jp_3231_;
}
else
{
uint32_t v___x_3254_; 
v___x_3254_ = lean_uint64_to_uint32(v___y_3241_);
v___y_3232_ = v___y_3242_;
v___y_3233_ = v___y_3243_;
v___y_3234_ = v___x_3249_;
v___y_3235_ = v___y_3244_;
v___y_3236_ = v___x_3254_;
goto v___jp_3231_;
}
}
v___jp_3255_:
{
uint64_t v___x_3263_; uint8_t v___x_3264_; 
v___x_3263_ = 425ULL;
v___x_3264_ = lean_uint64_dec_lt(v___x_3263_, v___y_3262_);
if (v___x_3264_ == 0)
{
if (v___y_3259_ == 0)
{
v___y_3241_ = v___y_3257_;
v___y_3242_ = v___y_3256_;
v___y_3243_ = v___y_3258_;
v___y_3244_ = v___y_3261_;
v___y_3245_ = v___y_3262_;
v___y_3246_ = v___y_3260_;
goto v___jp_3240_;
}
else
{
uint64_t v___x_3265_; 
v___x_3265_ = 8388608ULL;
v___y_3241_ = v___y_3257_;
v___y_3242_ = v___y_3256_;
v___y_3243_ = v___y_3258_;
v___y_3244_ = v___y_3261_;
v___y_3245_ = v___y_3262_;
v___y_3246_ = v___x_3265_;
goto v___jp_3240_;
}
}
else
{
uint8_t v___x_3266_; 
v___x_3266_ = lean_unbox(v___y_3261_);
lean_dec(v___y_3261_);
if (v___x_3266_ == 0)
{
uint32_t v___x_3267_; 
v___x_3267_ = 2139095040;
return v___x_3267_;
}
else
{
uint32_t v___x_3268_; 
v___x_3268_ = 4286578688;
return v___x_3268_;
}
}
}
v___jp_3269_:
{
uint64_t v___x_3276_; uint8_t v_carry_3277_; 
v___x_3276_ = 16777216ULL;
v_carry_3277_ = lean_uint64_dec_eq(v___y_3275_, v___x_3276_);
if (v_carry_3277_ == 0)
{
v___y_3256_ = v___y_3271_;
v___y_3257_ = v___y_3270_;
v___y_3258_ = v___y_3272_;
v___y_3259_ = v_carry_3277_;
v___y_3260_ = v___y_3275_;
v___y_3261_ = v___y_3274_;
v___y_3262_ = v___y_3273_;
goto v___jp_3255_;
}
else
{
uint64_t v___x_3278_; uint64_t v___x_3279_; 
v___x_3278_ = 1ULL;
v___x_3279_ = lean_uint64_add(v___y_3273_, v___x_3278_);
v___y_3256_ = v___y_3271_;
v___y_3257_ = v___y_3270_;
v___y_3258_ = v___y_3272_;
v___y_3259_ = v_carry_3277_;
v___y_3260_ = v___y_3275_;
v___y_3261_ = v___y_3274_;
v___y_3262_ = v___x_3279_;
goto v___jp_3255_;
}
}
v___jp_3280_:
{
uint64_t v_position_3289_; uint64_t v___x_3290_; uint8_t v___x_3291_; 
v_position_3289_ = lean_uint64_add(v___y_3288_, v___y_3286_);
v___x_3290_ = 172ULL;
v___x_3291_ = lean_uint64_dec_lt(v_position_3289_, v___x_3290_);
if (v___x_3291_ == 0)
{
uint64_t v___x_3292_; uint8_t v___x_3293_; 
v___x_3292_ = 23ULL;
v___x_3293_ = lean_uint64_dec_lt(v___y_3288_, v___x_3292_);
if (v___x_3293_ == 0)
{
uint64_t v___x_3294_; uint8_t v___x_3295_; 
v___x_3294_ = lean_uint64_sub(v___y_3288_, v___x_3292_);
v___x_3295_ = lean_uint64_dec_eq(v___x_3294_, v___y_3283_);
if (v___x_3295_ == 0)
{
uint64_t v___x_3296_; uint8_t v___x_3297_; 
v___x_3296_ = 64ULL;
v___x_3297_ = lean_uint64_dec_lt(v___x_3294_, v___x_3296_);
if (v___x_3297_ == 0)
{
uint8_t v___x_3298_; 
v___x_3298_ = lean_uint64_dec_eq(v___x_3294_, v___x_3296_);
if (v___x_3298_ == 0)
{
lean_dec(v___y_3281_);
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v___y_3283_;
goto v___jp_3269_;
}
else
{
uint64_t v___x_3299_; uint64_t v___x_3300_; uint8_t v___x_3301_; 
v___x_3299_ = 9223372036854775808ULL;
v___x_3300_ = lean_unbox_uint64(v___y_3281_);
lean_dec(v___y_3281_);
v___x_3301_ = lean_uint64_dec_lt(v___x_3299_, v___x_3300_);
if (v___x_3301_ == 0)
{
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v___y_3283_;
goto v___jp_3269_;
}
else
{
uint64_t v___x_3302_; 
v___x_3302_ = 1ULL;
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v___x_3302_;
goto v___jp_3269_;
}
}
}
else
{
uint64_t v___x_3303_; uint64_t v_quotient_3304_; uint64_t v___x_3305_; uint64_t v___x_3306_; uint64_t v___x_3307_; uint64_t v___x_3308_; uint64_t v_remainder_3309_; uint64_t v___x_3310_; uint64_t v_half_3311_; uint8_t v___x_3312_; 
v___x_3303_ = lean_unbox_uint64(v___y_3281_);
v_quotient_3304_ = lean_uint64_shift_right(v___x_3303_, v___x_3294_);
v___x_3305_ = 1ULL;
v___x_3306_ = lean_uint64_shift_left(v___x_3305_, v___x_3294_);
v___x_3307_ = lean_uint64_sub(v___x_3306_, v___x_3305_);
v___x_3308_ = lean_unbox_uint64(v___y_3281_);
lean_dec(v___y_3281_);
v_remainder_3309_ = lean_uint64_land(v___x_3308_, v___x_3307_);
v___x_3310_ = lean_uint64_sub(v___x_3294_, v___x_3305_);
v_half_3311_ = lean_uint64_shift_left(v___x_3305_, v___x_3310_);
v___x_3312_ = lean_uint64_dec_lt(v_remainder_3309_, v_half_3311_);
if (v___x_3312_ == 0)
{
uint8_t v___x_3313_; 
v___x_3313_ = lean_uint64_dec_lt(v_half_3311_, v_remainder_3309_);
if (v___x_3313_ == 0)
{
uint64_t v___x_3314_; uint8_t v___x_3315_; 
v___x_3314_ = lean_uint64_land(v_quotient_3304_, v___x_3305_);
v___x_3315_ = lean_uint64_dec_eq(v___x_3314_, v___y_3283_);
if (v___x_3315_ == 0)
{
uint64_t v___x_3316_; 
v___x_3316_ = lean_uint64_add(v_quotient_3304_, v___x_3305_);
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v___x_3316_;
goto v___jp_3269_;
}
else
{
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v_quotient_3304_;
goto v___jp_3269_;
}
}
else
{
uint64_t v___x_3317_; 
v___x_3317_ = lean_uint64_add(v_quotient_3304_, v___x_3305_);
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v___x_3317_;
goto v___jp_3269_;
}
}
else
{
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v_quotient_3304_;
goto v___jp_3269_;
}
}
}
else
{
uint64_t v___x_3318_; 
v___x_3318_ = lean_unbox_uint64(v___y_3281_);
lean_dec(v___y_3281_);
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v___x_3318_;
goto v___jp_3269_;
}
}
else
{
uint64_t v___x_3319_; uint64_t v___x_3320_; uint64_t v___x_3321_; 
v___x_3319_ = lean_uint64_sub(v___x_3292_, v___y_3288_);
v___x_3320_ = lean_unbox_uint64(v___y_3281_);
lean_dec(v___y_3281_);
v___x_3321_ = lean_uint64_shift_left(v___x_3320_, v___x_3319_);
v___y_3270_ = v___y_3283_;
v___y_3271_ = v___y_3282_;
v___y_3272_ = v___y_3285_;
v___y_3273_ = v_position_3289_;
v___y_3274_ = v___y_3287_;
v___y_3275_ = v___x_3321_;
goto v___jp_3269_;
}
}
else
{
uint8_t v___x_3322_; 
v___x_3322_ = lean_uint64_dec_lt(v___y_3286_, v___y_3284_);
if (v___x_3322_ == 0)
{
uint64_t v___x_3323_; uint64_t v___x_3324_; uint64_t v___x_3325_; 
v___x_3323_ = lean_uint64_sub(v___y_3286_, v___y_3284_);
v___x_3324_ = lean_unbox_uint64(v___y_3281_);
lean_dec(v___y_3281_);
v___x_3325_ = lean_uint64_shift_left(v___x_3324_, v___x_3323_);
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v___x_3325_;
goto v___jp_3202_;
}
else
{
uint64_t v___x_3326_; uint8_t v___x_3327_; 
v___x_3326_ = lean_uint64_sub(v___y_3284_, v___y_3286_);
v___x_3327_ = lean_uint64_dec_eq(v___x_3326_, v___y_3283_);
if (v___x_3327_ == 0)
{
uint64_t v___x_3328_; uint8_t v___x_3329_; 
v___x_3328_ = 64ULL;
v___x_3329_ = lean_uint64_dec_lt(v___x_3326_, v___x_3328_);
if (v___x_3329_ == 0)
{
uint8_t v___x_3330_; 
v___x_3330_ = lean_uint64_dec_eq(v___x_3326_, v___x_3328_);
if (v___x_3330_ == 0)
{
lean_dec(v___y_3281_);
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v___y_3283_;
goto v___jp_3202_;
}
else
{
uint64_t v___x_3331_; uint64_t v___x_3332_; uint8_t v___x_3333_; 
v___x_3331_ = 9223372036854775808ULL;
v___x_3332_ = lean_unbox_uint64(v___y_3281_);
lean_dec(v___y_3281_);
v___x_3333_ = lean_uint64_dec_lt(v___x_3331_, v___x_3332_);
if (v___x_3333_ == 0)
{
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v___y_3283_;
goto v___jp_3202_;
}
else
{
uint64_t v___x_3334_; 
v___x_3334_ = 1ULL;
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v___x_3334_;
goto v___jp_3202_;
}
}
}
else
{
uint64_t v___x_3335_; uint64_t v_quotient_3336_; uint64_t v___x_3337_; uint64_t v___x_3338_; uint64_t v___x_3339_; uint64_t v___x_3340_; uint64_t v_remainder_3341_; uint64_t v___x_3342_; uint64_t v_half_3343_; uint8_t v___x_3344_; 
v___x_3335_ = lean_unbox_uint64(v___y_3281_);
v_quotient_3336_ = lean_uint64_shift_right(v___x_3335_, v___x_3326_);
v___x_3337_ = 1ULL;
v___x_3338_ = lean_uint64_shift_left(v___x_3337_, v___x_3326_);
v___x_3339_ = lean_uint64_sub(v___x_3338_, v___x_3337_);
v___x_3340_ = lean_unbox_uint64(v___y_3281_);
lean_dec(v___y_3281_);
v_remainder_3341_ = lean_uint64_land(v___x_3340_, v___x_3339_);
v___x_3342_ = lean_uint64_sub(v___x_3326_, v___x_3337_);
v_half_3343_ = lean_uint64_shift_left(v___x_3337_, v___x_3342_);
v___x_3344_ = lean_uint64_dec_lt(v_remainder_3341_, v_half_3343_);
if (v___x_3344_ == 0)
{
uint8_t v___x_3345_; 
v___x_3345_ = lean_uint64_dec_lt(v_half_3343_, v_remainder_3341_);
if (v___x_3345_ == 0)
{
uint64_t v___x_3346_; uint8_t v___x_3347_; 
v___x_3346_ = lean_uint64_land(v_quotient_3336_, v___x_3337_);
v___x_3347_ = lean_uint64_dec_eq(v___x_3346_, v___y_3283_);
if (v___x_3347_ == 0)
{
uint64_t v___x_3348_; 
v___x_3348_ = lean_uint64_add(v_quotient_3336_, v___x_3337_);
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v___x_3348_;
goto v___jp_3202_;
}
else
{
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v_quotient_3336_;
goto v___jp_3202_;
}
}
else
{
uint64_t v___x_3349_; 
v___x_3349_ = lean_uint64_add(v_quotient_3336_, v___x_3337_);
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v___x_3349_;
goto v___jp_3202_;
}
}
else
{
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v_quotient_3336_;
goto v___jp_3202_;
}
}
}
else
{
uint64_t v___x_3350_; 
v___x_3350_ = lean_unbox_uint64(v___y_3281_);
lean_dec(v___y_3281_);
v___y_3203_ = v___y_3283_;
v___y_3204_ = v___y_3287_;
v___y_3205_ = v___x_3350_;
goto v___jp_3202_;
}
}
}
}
v___jp_3351_:
{
uint64_t v___x_3361_; uint64_t v___x_3362_; uint8_t v___x_3363_; 
v___x_3361_ = 1ULL;
v___x_3362_ = lean_uint64_shift_right(v___y_3358_, v___x_3361_);
v___x_3363_ = lean_uint64_dec_eq(v___x_3362_, v___y_3354_);
if (v___x_3363_ == 0)
{
uint64_t v___x_3364_; 
v___x_3364_ = lean_uint64_add(v___y_3360_, v___x_3361_);
v___y_3281_ = v___y_3353_;
v___y_3282_ = v___y_3352_;
v___y_3283_ = v___y_3354_;
v___y_3284_ = v___y_3355_;
v___y_3285_ = v___y_3356_;
v___y_3286_ = v___y_3357_;
v___y_3287_ = v___y_3359_;
v___y_3288_ = v___x_3364_;
goto v___jp_3280_;
}
else
{
v___y_3281_ = v___y_3353_;
v___y_3282_ = v___y_3352_;
v___y_3283_ = v___y_3354_;
v___y_3284_ = v___y_3355_;
v___y_3285_ = v___y_3356_;
v___y_3286_ = v___y_3357_;
v___y_3287_ = v___y_3359_;
v___y_3288_ = v___y_3360_;
goto v___jp_3280_;
}
}
v___jp_3365_:
{
uint64_t v___x_3377_; uint8_t v___x_3378_; 
v___x_3377_ = lean_uint64_shift_right(v___y_3373_, v___y_3372_);
v___x_3378_ = lean_uint64_dec_eq(v___x_3377_, v___y_3366_);
if (v___x_3378_ == 0)
{
uint64_t v___x_3379_; 
v___x_3379_ = lean_uint64_add(v___y_3371_, v___y_3372_);
v___y_3352_ = v___y_3368_;
v___y_3353_ = v___y_3367_;
v___y_3354_ = v___y_3366_;
v___y_3355_ = v___y_3369_;
v___y_3356_ = v___y_3370_;
v___y_3357_ = v___y_3374_;
v___y_3358_ = v___y_3376_;
v___y_3359_ = v___y_3375_;
v___y_3360_ = v___x_3379_;
goto v___jp_3351_;
}
else
{
v___y_3352_ = v___y_3368_;
v___y_3353_ = v___y_3367_;
v___y_3354_ = v___y_3366_;
v___y_3355_ = v___y_3369_;
v___y_3356_ = v___y_3370_;
v___y_3357_ = v___y_3374_;
v___y_3358_ = v___y_3376_;
v___y_3359_ = v___y_3375_;
v___y_3360_ = v___y_3371_;
goto v___jp_3351_;
}
}
v___jp_3380_:
{
uint64_t v___x_3390_; uint64_t v___x_3391_; uint8_t v___x_3392_; 
v___x_3390_ = 2ULL;
v___x_3391_ = lean_uint64_shift_right(v___y_3387_, v___x_3390_);
v___x_3392_ = lean_uint64_dec_eq(v___x_3391_, v___y_3383_);
if (v___x_3392_ == 0)
{
v___y_3366_ = v___y_3383_;
v___y_3367_ = v___y_3382_;
v___y_3368_ = v___y_3381_;
v___y_3369_ = v___y_3384_;
v___y_3370_ = v___y_3385_;
v___y_3371_ = v___y_3389_;
v___y_3372_ = v___x_3390_;
v___y_3373_ = v___y_3387_;
v___y_3374_ = v___y_3386_;
v___y_3375_ = v___y_3388_;
v___y_3376_ = v___x_3391_;
goto v___jp_3365_;
}
else
{
v___y_3366_ = v___y_3383_;
v___y_3367_ = v___y_3382_;
v___y_3368_ = v___y_3381_;
v___y_3369_ = v___y_3384_;
v___y_3370_ = v___y_3385_;
v___y_3371_ = v___y_3389_;
v___y_3372_ = v___x_3390_;
v___y_3373_ = v___y_3387_;
v___y_3374_ = v___y_3386_;
v___y_3375_ = v___y_3388_;
v___y_3376_ = v___y_3387_;
goto v___jp_3365_;
}
}
v___jp_3393_:
{
uint64_t v___x_3405_; uint8_t v___x_3406_; 
v___x_3405_ = lean_uint64_shift_right(v___y_3398_, v___y_3394_);
v___x_3406_ = lean_uint64_dec_eq(v___x_3405_, v___y_3395_);
if (v___x_3406_ == 0)
{
uint64_t v___x_3407_; 
v___x_3407_ = lean_uint64_add(v___y_3402_, v___y_3394_);
v___y_3381_ = v___y_3397_;
v___y_3382_ = v___y_3396_;
v___y_3383_ = v___y_3395_;
v___y_3384_ = v___y_3399_;
v___y_3385_ = v___y_3400_;
v___y_3386_ = v___y_3401_;
v___y_3387_ = v___y_3404_;
v___y_3388_ = v___y_3403_;
v___y_3389_ = v___x_3407_;
goto v___jp_3380_;
}
else
{
v___y_3381_ = v___y_3397_;
v___y_3382_ = v___y_3396_;
v___y_3383_ = v___y_3395_;
v___y_3384_ = v___y_3399_;
v___y_3385_ = v___y_3400_;
v___y_3386_ = v___y_3401_;
v___y_3387_ = v___y_3404_;
v___y_3388_ = v___y_3403_;
v___y_3389_ = v___y_3402_;
goto v___jp_3380_;
}
}
v___jp_3408_:
{
uint64_t v___x_3418_; uint64_t v___x_3419_; uint8_t v___x_3420_; 
v___x_3418_ = 4ULL;
v___x_3419_ = lean_uint64_shift_right(v___y_3413_, v___x_3418_);
v___x_3420_ = lean_uint64_dec_eq(v___x_3419_, v___y_3411_);
if (v___x_3420_ == 0)
{
v___y_3394_ = v___x_3418_;
v___y_3395_ = v___y_3411_;
v___y_3396_ = v___y_3410_;
v___y_3397_ = v___y_3409_;
v___y_3398_ = v___y_3413_;
v___y_3399_ = v___y_3412_;
v___y_3400_ = v___y_3414_;
v___y_3401_ = v___y_3415_;
v___y_3402_ = v___y_3417_;
v___y_3403_ = v___y_3416_;
v___y_3404_ = v___x_3419_;
goto v___jp_3393_;
}
else
{
v___y_3394_ = v___x_3418_;
v___y_3395_ = v___y_3411_;
v___y_3396_ = v___y_3410_;
v___y_3397_ = v___y_3409_;
v___y_3398_ = v___y_3413_;
v___y_3399_ = v___y_3412_;
v___y_3400_ = v___y_3414_;
v___y_3401_ = v___y_3415_;
v___y_3402_ = v___y_3417_;
v___y_3403_ = v___y_3416_;
v___y_3404_ = v___y_3413_;
goto v___jp_3393_;
}
}
v___jp_3421_:
{
uint64_t v___x_3433_; uint8_t v___x_3434_; 
v___x_3433_ = lean_uint64_shift_right(v___y_3429_, v___y_3422_);
v___x_3434_ = lean_uint64_dec_eq(v___x_3433_, v___y_3423_);
if (v___x_3434_ == 0)
{
uint64_t v___x_3435_; 
v___x_3435_ = lean_uint64_add(v___y_3428_, v___y_3422_);
v___y_3409_ = v___y_3425_;
v___y_3410_ = v___y_3424_;
v___y_3411_ = v___y_3423_;
v___y_3412_ = v___y_3426_;
v___y_3413_ = v___y_3432_;
v___y_3414_ = v___y_3427_;
v___y_3415_ = v___y_3430_;
v___y_3416_ = v___y_3431_;
v___y_3417_ = v___x_3435_;
goto v___jp_3408_;
}
else
{
v___y_3409_ = v___y_3425_;
v___y_3410_ = v___y_3424_;
v___y_3411_ = v___y_3423_;
v___y_3412_ = v___y_3426_;
v___y_3413_ = v___y_3432_;
v___y_3414_ = v___y_3427_;
v___y_3415_ = v___y_3430_;
v___y_3416_ = v___y_3431_;
v___y_3417_ = v___y_3428_;
goto v___jp_3408_;
}
}
v___jp_3436_:
{
uint64_t v___x_3446_; uint64_t v___x_3447_; uint8_t v___x_3448_; 
v___x_3446_ = 8ULL;
v___x_3447_ = lean_uint64_shift_right(v___y_3442_, v___x_3446_);
v___x_3448_ = lean_uint64_dec_eq(v___x_3447_, v___y_3439_);
if (v___x_3448_ == 0)
{
v___y_3422_ = v___x_3446_;
v___y_3423_ = v___y_3439_;
v___y_3424_ = v___y_3438_;
v___y_3425_ = v___y_3437_;
v___y_3426_ = v___y_3440_;
v___y_3427_ = v___y_3441_;
v___y_3428_ = v___y_3445_;
v___y_3429_ = v___y_3442_;
v___y_3430_ = v___y_3443_;
v___y_3431_ = v___y_3444_;
v___y_3432_ = v___x_3447_;
goto v___jp_3421_;
}
else
{
v___y_3422_ = v___x_3446_;
v___y_3423_ = v___y_3439_;
v___y_3424_ = v___y_3438_;
v___y_3425_ = v___y_3437_;
v___y_3426_ = v___y_3440_;
v___y_3427_ = v___y_3441_;
v___y_3428_ = v___y_3445_;
v___y_3429_ = v___y_3442_;
v___y_3430_ = v___y_3443_;
v___y_3431_ = v___y_3444_;
v___y_3432_ = v___y_3442_;
goto v___jp_3421_;
}
}
v___jp_3449_:
{
uint64_t v___x_3461_; uint8_t v___x_3462_; 
v___x_3461_ = lean_uint64_shift_right(v___y_3458_, v___y_3456_);
v___x_3462_ = lean_uint64_dec_eq(v___x_3461_, v___y_3450_);
if (v___x_3462_ == 0)
{
uint64_t v___x_3463_; 
v___x_3463_ = lean_uint64_add(v___y_3455_, v___y_3456_);
v___y_3437_ = v___y_3452_;
v___y_3438_ = v___y_3451_;
v___y_3439_ = v___y_3450_;
v___y_3440_ = v___y_3453_;
v___y_3441_ = v___y_3454_;
v___y_3442_ = v___y_3460_;
v___y_3443_ = v___y_3457_;
v___y_3444_ = v___y_3459_;
v___y_3445_ = v___x_3463_;
goto v___jp_3436_;
}
else
{
v___y_3437_ = v___y_3452_;
v___y_3438_ = v___y_3451_;
v___y_3439_ = v___y_3450_;
v___y_3440_ = v___y_3453_;
v___y_3441_ = v___y_3454_;
v___y_3442_ = v___y_3460_;
v___y_3443_ = v___y_3457_;
v___y_3444_ = v___y_3459_;
v___y_3445_ = v___y_3455_;
goto v___jp_3436_;
}
}
v___jp_3464_:
{
uint64_t v___x_3474_; uint64_t v___x_3475_; uint8_t v___x_3476_; 
v___x_3474_ = 16ULL;
v___x_3475_ = lean_uint64_shift_right(v___y_3471_, v___x_3474_);
v___x_3476_ = lean_uint64_dec_eq(v___x_3475_, v___y_3467_);
if (v___x_3476_ == 0)
{
v___y_3450_ = v___y_3467_;
v___y_3451_ = v___y_3466_;
v___y_3452_ = v___y_3465_;
v___y_3453_ = v___y_3468_;
v___y_3454_ = v___y_3469_;
v___y_3455_ = v___y_3473_;
v___y_3456_ = v___x_3474_;
v___y_3457_ = v___y_3470_;
v___y_3458_ = v___y_3471_;
v___y_3459_ = v___y_3472_;
v___y_3460_ = v___x_3475_;
goto v___jp_3449_;
}
else
{
v___y_3450_ = v___y_3467_;
v___y_3451_ = v___y_3466_;
v___y_3452_ = v___y_3465_;
v___y_3453_ = v___y_3468_;
v___y_3454_ = v___y_3469_;
v___y_3455_ = v___y_3473_;
v___y_3456_ = v___x_3474_;
v___y_3457_ = v___y_3470_;
v___y_3458_ = v___y_3471_;
v___y_3459_ = v___y_3472_;
v___y_3460_ = v___y_3471_;
goto v___jp_3449_;
}
}
v___jp_3477_:
{
uint64_t v___x_3487_; uint64_t v___x_3488_; uint8_t v___x_3489_; 
v___x_3487_ = lean_unbox_uint64(v___y_3479_);
v___x_3488_ = lean_uint64_shift_right(v___x_3487_, v___y_3484_);
v___x_3489_ = lean_uint64_dec_eq(v___x_3488_, v___y_3478_);
if (v___x_3489_ == 0)
{
v___y_3465_ = v___y_3480_;
v___y_3466_ = v___y_3479_;
v___y_3467_ = v___y_3478_;
v___y_3468_ = v___y_3481_;
v___y_3469_ = v___y_3482_;
v___y_3470_ = v___y_3483_;
v___y_3471_ = v___y_3486_;
v___y_3472_ = v___y_3485_;
v___y_3473_ = v___y_3484_;
goto v___jp_3464_;
}
else
{
v___y_3465_ = v___y_3480_;
v___y_3466_ = v___y_3479_;
v___y_3467_ = v___y_3478_;
v___y_3468_ = v___y_3481_;
v___y_3469_ = v___y_3482_;
v___y_3470_ = v___y_3483_;
v___y_3471_ = v___y_3486_;
v___y_3472_ = v___y_3485_;
v___y_3473_ = v___y_3478_;
goto v___jp_3464_;
}
}
v___jp_3490_:
{
uint64_t v___x_3496_; uint64_t v___x_3497_; uint8_t v___x_3498_; 
v___x_3496_ = 0ULL;
v___x_3497_ = lean_unbox_uint64(v_snd_3495_);
v___x_3498_ = lean_uint64_dec_eq(v___x_3497_, v___x_3496_);
if (v___x_3498_ == 0)
{
uint64_t v___x_3499_; uint64_t v___x_3500_; uint64_t v___x_3501_; uint64_t v___x_3502_; uint64_t v___x_3503_; uint8_t v___x_3504_; 
v___x_3499_ = 149ULL;
v___x_3500_ = lean_uint64_add(v___y_3493_, v___x_3499_);
v___x_3501_ = 32ULL;
v___x_3502_ = lean_unbox_uint64(v_snd_3495_);
v___x_3503_ = lean_uint64_shift_right(v___x_3502_, v___x_3501_);
v___x_3504_ = lean_uint64_dec_eq(v___x_3503_, v___x_3496_);
if (v___x_3504_ == 0)
{
v___y_3478_ = v___x_3496_;
v___y_3479_ = v_snd_3495_;
v___y_3480_ = v___y_3491_;
v___y_3481_ = v___x_3499_;
v___y_3482_ = v___y_3492_;
v___y_3483_ = v___x_3500_;
v___y_3484_ = v___x_3501_;
v___y_3485_ = v_fst_3494_;
v___y_3486_ = v___x_3503_;
goto v___jp_3477_;
}
else
{
uint64_t v___x_3505_; 
v___x_3505_ = lean_unbox_uint64(v_snd_3495_);
v___y_3478_ = v___x_3496_;
v___y_3479_ = v_snd_3495_;
v___y_3480_ = v___y_3491_;
v___y_3481_ = v___x_3499_;
v___y_3482_ = v___y_3492_;
v___y_3483_ = v___x_3500_;
v___y_3484_ = v___x_3501_;
v___y_3485_ = v_fst_3494_;
v___y_3486_ = v___x_3505_;
goto v___jp_3477_;
}
}
else
{
uint8_t v___x_3506_; 
lean_dec(v_snd_3495_);
v___x_3506_ = lean_unbox(v_fst_3494_);
lean_dec(v_fst_3494_);
if (v___x_3506_ == 0)
{
uint32_t v___x_3507_; 
v___x_3507_ = 0;
return v___x_3507_;
}
else
{
uint32_t v___x_3508_; 
v___x_3508_ = 2147483648;
return v___x_3508_;
}
}
}
v___jp_3509_:
{
uint32_t v___x_3512_; uint32_t v___x_3513_; uint32_t v___x_3514_; 
v___x_3512_ = 8388607;
v___x_3513_ = lean_uint32_land(v___y_3510_, v___x_3512_);
v___x_3514_ = lean_uint32_lor(v___y_3511_, v___x_3513_);
return v___x_3514_;
}
v___jp_3515_:
{
uint8_t v___x_3519_; 
v___x_3519_ = lean_uint64_dec_eq(v___y_3518_, v___y_3517_);
if (v___x_3519_ == 0)
{
uint64_t v___x_3520_; uint8_t v___x_3521_; 
v___x_3520_ = 8388608ULL;
v___x_3521_ = lean_uint64_dec_eq(v___y_3518_, v___x_3520_);
if (v___x_3521_ == 0)
{
uint32_t v___x_3522_; uint8_t v___x_3523_; 
v___x_3522_ = lean_uint64_to_uint32(v___y_3518_);
v___x_3523_ = lean_unbox(v___y_3516_);
lean_dec(v___y_3516_);
if (v___x_3523_ == 0)
{
uint32_t v___x_3524_; 
v___x_3524_ = 0;
v___y_3510_ = v___x_3522_;
v___y_3511_ = v___x_3524_;
goto v___jp_3509_;
}
else
{
uint32_t v___x_3525_; 
v___x_3525_ = 2147483648;
v___y_3510_ = v___x_3522_;
v___y_3511_ = v___x_3525_;
goto v___jp_3509_;
}
}
else
{
uint8_t v___x_3526_; 
v___x_3526_ = lean_unbox(v___y_3516_);
lean_dec(v___y_3516_);
if (v___x_3526_ == 0)
{
uint32_t v___x_3527_; 
v___x_3527_ = 0;
v___y_3193_ = v___x_3527_;
goto v___jp_3192_;
}
else
{
uint32_t v___x_3528_; 
v___x_3528_ = 2147483648;
v___y_3193_ = v___x_3528_;
goto v___jp_3192_;
}
}
}
else
{
uint8_t v___x_3529_; 
v___x_3529_ = lean_unbox(v___y_3516_);
lean_dec(v___y_3516_);
if (v___x_3529_ == 0)
{
uint32_t v___x_3530_; 
v___x_3530_ = 0;
return v___x_3530_;
}
else
{
uint32_t v___x_3531_; 
v___x_3531_ = 2147483648;
return v___x_3531_;
}
}
}
v___jp_3532_:
{
uint32_t v___x_3538_; uint32_t v___x_3539_; uint32_t v___x_3540_; uint32_t v___x_3541_; uint32_t v___x_3542_; uint32_t v___x_3543_; 
v___x_3538_ = lean_uint32_land(v___y_3535_, v___y_3536_);
v___x_3539_ = lean_uint32_shift_left(v___x_3538_, v___y_3534_);
v___x_3540_ = lean_uint32_lor(v___y_3537_, v___x_3539_);
v___x_3541_ = 8388607;
v___x_3542_ = lean_uint32_land(v___y_3533_, v___x_3541_);
v___x_3543_ = lean_uint32_lor(v___x_3540_, v___x_3542_);
return v___x_3543_;
}
v___jp_3544_:
{
uint8_t v___x_3550_; 
v___x_3550_ = lean_unbox(v___y_3548_);
lean_dec(v___y_3548_);
if (v___x_3550_ == 0)
{
uint32_t v___x_3551_; 
v___x_3551_ = 0;
v___y_3533_ = v___y_3549_;
v___y_3534_ = v___y_3546_;
v___y_3535_ = v___y_3545_;
v___y_3536_ = v___y_3547_;
v___y_3537_ = v___x_3551_;
goto v___jp_3532_;
}
else
{
uint32_t v___x_3552_; 
v___x_3552_ = 2147483648;
v___y_3533_ = v___y_3549_;
v___y_3534_ = v___y_3546_;
v___y_3535_ = v___y_3545_;
v___y_3536_ = v___y_3547_;
v___y_3537_ = v___x_3552_;
goto v___jp_3532_;
}
}
v___jp_3553_:
{
uint64_t v___x_3560_; uint64_t v_encodedExponent_3561_; uint32_t v___x_3562_; uint64_t v___x_3563_; uint8_t v___x_3564_; 
v___x_3560_ = 171ULL;
v_encodedExponent_3561_ = lean_uint64_sub(v___y_3558_, v___x_3560_);
v___x_3562_ = lean_uint64_to_uint32(v_encodedExponent_3561_);
v___x_3563_ = 8388608ULL;
v___x_3564_ = lean_uint64_dec_lt(v___y_3559_, v___x_3563_);
if (v___x_3564_ == 0)
{
uint64_t v___x_3565_; uint32_t v___x_3566_; 
v___x_3565_ = lean_uint64_sub(v___y_3559_, v___x_3563_);
v___x_3566_ = lean_uint64_to_uint32(v___x_3565_);
v___y_3545_ = v___x_3562_;
v___y_3546_ = v___y_3554_;
v___y_3547_ = v___y_3555_;
v___y_3548_ = v___y_3556_;
v___y_3549_ = v___x_3566_;
goto v___jp_3544_;
}
else
{
uint32_t v___x_3567_; 
v___x_3567_ = lean_uint64_to_uint32(v___y_3557_);
v___y_3545_ = v___x_3562_;
v___y_3546_ = v___y_3554_;
v___y_3547_ = v___y_3555_;
v___y_3548_ = v___y_3556_;
v___y_3549_ = v___x_3567_;
goto v___jp_3544_;
}
}
v___jp_3568_:
{
uint64_t v___x_3576_; uint8_t v___x_3577_; 
v___x_3576_ = 425ULL;
v___x_3577_ = lean_uint64_dec_lt(v___x_3576_, v___y_3575_);
if (v___x_3577_ == 0)
{
if (v___y_3573_ == 0)
{
v___y_3554_ = v___y_3569_;
v___y_3555_ = v___y_3570_;
v___y_3556_ = v___y_3572_;
v___y_3557_ = v___y_3574_;
v___y_3558_ = v___y_3575_;
v___y_3559_ = v___y_3571_;
goto v___jp_3553_;
}
else
{
uint64_t v___x_3578_; 
v___x_3578_ = 8388608ULL;
v___y_3554_ = v___y_3569_;
v___y_3555_ = v___y_3570_;
v___y_3556_ = v___y_3572_;
v___y_3557_ = v___y_3574_;
v___y_3558_ = v___y_3575_;
v___y_3559_ = v___x_3578_;
goto v___jp_3553_;
}
}
else
{
uint8_t v___x_3579_; 
v___x_3579_ = lean_unbox(v___y_3572_);
lean_dec(v___y_3572_);
if (v___x_3579_ == 0)
{
uint32_t v___x_3580_; 
v___x_3580_ = 2139095040;
return v___x_3580_;
}
else
{
uint32_t v___x_3581_; 
v___x_3581_ = 4286578688;
return v___x_3581_;
}
}
}
v___jp_3582_:
{
uint64_t v___x_3589_; uint8_t v_carry_3590_; 
v___x_3589_ = 16777216ULL;
v_carry_3590_ = lean_uint64_dec_eq(v___y_3588_, v___x_3589_);
if (v_carry_3590_ == 0)
{
v___y_3569_ = v___y_3584_;
v___y_3570_ = v___y_3585_;
v___y_3571_ = v___y_3588_;
v___y_3572_ = v___y_3586_;
v___y_3573_ = v_carry_3590_;
v___y_3574_ = v___y_3587_;
v___y_3575_ = v___y_3583_;
goto v___jp_3568_;
}
else
{
uint64_t v___x_3591_; uint64_t v___x_3592_; 
v___x_3591_ = 1ULL;
v___x_3592_ = lean_uint64_add(v___y_3583_, v___x_3591_);
v___y_3569_ = v___y_3584_;
v___y_3570_ = v___y_3585_;
v___y_3571_ = v___y_3588_;
v___y_3572_ = v___y_3586_;
v___y_3573_ = v_carry_3590_;
v___y_3574_ = v___y_3587_;
v___y_3575_ = v___x_3592_;
goto v___jp_3568_;
}
}
v___jp_3593_:
{
uint64_t v_position_3602_; uint64_t v___x_3603_; uint8_t v___x_3604_; 
v_position_3602_ = lean_uint64_add(v___y_3601_, v___y_3594_);
v___x_3603_ = 172ULL;
v___x_3604_ = lean_uint64_dec_lt(v_position_3602_, v___x_3603_);
if (v___x_3604_ == 0)
{
uint64_t v___x_3605_; uint8_t v___x_3606_; 
v___x_3605_ = 23ULL;
v___x_3606_ = lean_uint64_dec_lt(v___y_3601_, v___x_3605_);
if (v___x_3606_ == 0)
{
uint64_t v___x_3607_; uint8_t v___x_3608_; 
v___x_3607_ = lean_uint64_sub(v___y_3601_, v___x_3605_);
v___x_3608_ = lean_uint64_dec_eq(v___x_3607_, v___y_3600_);
if (v___x_3608_ == 0)
{
uint64_t v___x_3609_; uint8_t v___x_3610_; 
v___x_3609_ = 64ULL;
v___x_3610_ = lean_uint64_dec_lt(v___x_3607_, v___x_3609_);
if (v___x_3610_ == 0)
{
uint8_t v___x_3611_; 
v___x_3611_ = lean_uint64_dec_eq(v___x_3607_, v___x_3609_);
if (v___x_3611_ == 0)
{
lean_dec(v___y_3597_);
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___y_3600_;
goto v___jp_3582_;
}
else
{
uint64_t v___x_3612_; uint64_t v___x_3613_; uint8_t v___x_3614_; 
v___x_3612_ = 9223372036854775808ULL;
v___x_3613_ = lean_unbox_uint64(v___y_3597_);
lean_dec(v___y_3597_);
v___x_3614_ = lean_uint64_dec_lt(v___x_3612_, v___x_3613_);
if (v___x_3614_ == 0)
{
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___y_3600_;
goto v___jp_3582_;
}
else
{
uint64_t v___x_3615_; 
v___x_3615_ = 1ULL;
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___x_3615_;
goto v___jp_3582_;
}
}
}
else
{
uint64_t v___x_3616_; uint64_t v_quotient_3617_; uint64_t v___x_3618_; uint64_t v___x_3619_; uint64_t v___x_3620_; uint64_t v___x_3621_; uint64_t v_remainder_3622_; uint64_t v___x_3623_; uint64_t v_half_3624_; uint8_t v___x_3625_; 
v___x_3616_ = lean_unbox_uint64(v___y_3597_);
v_quotient_3617_ = lean_uint64_shift_right(v___x_3616_, v___x_3607_);
v___x_3618_ = 1ULL;
v___x_3619_ = lean_uint64_shift_left(v___x_3618_, v___x_3607_);
v___x_3620_ = lean_uint64_sub(v___x_3619_, v___x_3618_);
v___x_3621_ = lean_unbox_uint64(v___y_3597_);
lean_dec(v___y_3597_);
v_remainder_3622_ = lean_uint64_land(v___x_3621_, v___x_3620_);
v___x_3623_ = lean_uint64_sub(v___x_3607_, v___x_3618_);
v_half_3624_ = lean_uint64_shift_left(v___x_3618_, v___x_3623_);
v___x_3625_ = lean_uint64_dec_lt(v_remainder_3622_, v_half_3624_);
if (v___x_3625_ == 0)
{
uint8_t v___x_3626_; 
v___x_3626_ = lean_uint64_dec_lt(v_half_3624_, v_remainder_3622_);
if (v___x_3626_ == 0)
{
uint64_t v___x_3627_; uint8_t v___x_3628_; 
v___x_3627_ = lean_uint64_land(v_quotient_3617_, v___x_3618_);
v___x_3628_ = lean_uint64_dec_eq(v___x_3627_, v___y_3600_);
if (v___x_3628_ == 0)
{
uint64_t v___x_3629_; 
v___x_3629_ = lean_uint64_add(v_quotient_3617_, v___x_3618_);
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___x_3629_;
goto v___jp_3582_;
}
else
{
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v_quotient_3617_;
goto v___jp_3582_;
}
}
else
{
uint64_t v___x_3630_; 
v___x_3630_ = lean_uint64_add(v_quotient_3617_, v___x_3618_);
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___x_3630_;
goto v___jp_3582_;
}
}
else
{
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v_quotient_3617_;
goto v___jp_3582_;
}
}
}
else
{
uint64_t v___x_3631_; 
v___x_3631_ = lean_unbox_uint64(v___y_3597_);
lean_dec(v___y_3597_);
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___x_3631_;
goto v___jp_3582_;
}
}
else
{
uint64_t v___x_3632_; uint64_t v___x_3633_; uint64_t v___x_3634_; 
v___x_3632_ = lean_uint64_sub(v___x_3605_, v___y_3601_);
v___x_3633_ = lean_unbox_uint64(v___y_3597_);
lean_dec(v___y_3597_);
v___x_3634_ = lean_uint64_shift_left(v___x_3633_, v___x_3632_);
v___y_3583_ = v_position_3602_;
v___y_3584_ = v___y_3595_;
v___y_3585_ = v___y_3596_;
v___y_3586_ = v___y_3599_;
v___y_3587_ = v___y_3600_;
v___y_3588_ = v___x_3634_;
goto v___jp_3582_;
}
}
else
{
uint8_t v___x_3635_; 
v___x_3635_ = lean_uint64_dec_lt(v___y_3594_, v___y_3598_);
if (v___x_3635_ == 0)
{
uint64_t v___x_3636_; uint64_t v___x_3637_; uint64_t v___x_3638_; 
v___x_3636_ = lean_uint64_sub(v___y_3594_, v___y_3598_);
v___x_3637_ = lean_unbox_uint64(v___y_3597_);
lean_dec(v___y_3597_);
v___x_3638_ = lean_uint64_shift_left(v___x_3637_, v___x_3636_);
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v___x_3638_;
goto v___jp_3515_;
}
else
{
uint64_t v___x_3639_; uint8_t v___x_3640_; 
v___x_3639_ = lean_uint64_sub(v___y_3598_, v___y_3594_);
v___x_3640_ = lean_uint64_dec_eq(v___x_3639_, v___y_3600_);
if (v___x_3640_ == 0)
{
uint64_t v___x_3641_; uint8_t v___x_3642_; 
v___x_3641_ = 64ULL;
v___x_3642_ = lean_uint64_dec_lt(v___x_3639_, v___x_3641_);
if (v___x_3642_ == 0)
{
uint8_t v___x_3643_; 
v___x_3643_ = lean_uint64_dec_eq(v___x_3639_, v___x_3641_);
if (v___x_3643_ == 0)
{
lean_dec(v___y_3597_);
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v___y_3600_;
goto v___jp_3515_;
}
else
{
uint64_t v___x_3644_; uint64_t v___x_3645_; uint8_t v___x_3646_; 
v___x_3644_ = 9223372036854775808ULL;
v___x_3645_ = lean_unbox_uint64(v___y_3597_);
lean_dec(v___y_3597_);
v___x_3646_ = lean_uint64_dec_lt(v___x_3644_, v___x_3645_);
if (v___x_3646_ == 0)
{
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v___y_3600_;
goto v___jp_3515_;
}
else
{
uint64_t v___x_3647_; 
v___x_3647_ = 1ULL;
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v___x_3647_;
goto v___jp_3515_;
}
}
}
else
{
uint64_t v___x_3648_; uint64_t v_quotient_3649_; uint64_t v___x_3650_; uint64_t v___x_3651_; uint64_t v___x_3652_; uint64_t v___x_3653_; uint64_t v_remainder_3654_; uint64_t v___x_3655_; uint64_t v_half_3656_; uint8_t v___x_3657_; 
v___x_3648_ = lean_unbox_uint64(v___y_3597_);
v_quotient_3649_ = lean_uint64_shift_right(v___x_3648_, v___x_3639_);
v___x_3650_ = 1ULL;
v___x_3651_ = lean_uint64_shift_left(v___x_3650_, v___x_3639_);
v___x_3652_ = lean_uint64_sub(v___x_3651_, v___x_3650_);
v___x_3653_ = lean_unbox_uint64(v___y_3597_);
lean_dec(v___y_3597_);
v_remainder_3654_ = lean_uint64_land(v___x_3653_, v___x_3652_);
v___x_3655_ = lean_uint64_sub(v___x_3639_, v___x_3650_);
v_half_3656_ = lean_uint64_shift_left(v___x_3650_, v___x_3655_);
v___x_3657_ = lean_uint64_dec_lt(v_remainder_3654_, v_half_3656_);
if (v___x_3657_ == 0)
{
uint8_t v___x_3658_; 
v___x_3658_ = lean_uint64_dec_lt(v_half_3656_, v_remainder_3654_);
if (v___x_3658_ == 0)
{
uint64_t v___x_3659_; uint8_t v___x_3660_; 
v___x_3659_ = lean_uint64_land(v_quotient_3649_, v___x_3650_);
v___x_3660_ = lean_uint64_dec_eq(v___x_3659_, v___y_3600_);
if (v___x_3660_ == 0)
{
uint64_t v___x_3661_; 
v___x_3661_ = lean_uint64_add(v_quotient_3649_, v___x_3650_);
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v___x_3661_;
goto v___jp_3515_;
}
else
{
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v_quotient_3649_;
goto v___jp_3515_;
}
}
else
{
uint64_t v___x_3662_; 
v___x_3662_ = lean_uint64_add(v_quotient_3649_, v___x_3650_);
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v___x_3662_;
goto v___jp_3515_;
}
}
else
{
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v_quotient_3649_;
goto v___jp_3515_;
}
}
}
else
{
uint64_t v___x_3663_; 
v___x_3663_ = lean_unbox_uint64(v___y_3597_);
lean_dec(v___y_3597_);
v___y_3516_ = v___y_3599_;
v___y_3517_ = v___y_3600_;
v___y_3518_ = v___x_3663_;
goto v___jp_3515_;
}
}
}
}
v___jp_3664_:
{
uint64_t v___x_3674_; uint64_t v___x_3675_; uint8_t v___x_3676_; 
v___x_3674_ = 1ULL;
v___x_3675_ = lean_uint64_shift_right(v___y_3672_, v___x_3674_);
v___x_3676_ = lean_uint64_dec_eq(v___x_3675_, v___y_3671_);
if (v___x_3676_ == 0)
{
uint64_t v___x_3677_; 
v___x_3677_ = lean_uint64_add(v___y_3673_, v___x_3674_);
v___y_3594_ = v___y_3665_;
v___y_3595_ = v___y_3666_;
v___y_3596_ = v___y_3667_;
v___y_3597_ = v___y_3668_;
v___y_3598_ = v___y_3670_;
v___y_3599_ = v___y_3669_;
v___y_3600_ = v___y_3671_;
v___y_3601_ = v___x_3677_;
goto v___jp_3593_;
}
else
{
v___y_3594_ = v___y_3665_;
v___y_3595_ = v___y_3666_;
v___y_3596_ = v___y_3667_;
v___y_3597_ = v___y_3668_;
v___y_3598_ = v___y_3670_;
v___y_3599_ = v___y_3669_;
v___y_3600_ = v___y_3671_;
v___y_3601_ = v___y_3673_;
goto v___jp_3593_;
}
}
v___jp_3678_:
{
uint64_t v___x_3690_; uint8_t v___x_3691_; 
v___x_3690_ = lean_uint64_shift_right(v___y_3685_, v___y_3682_);
v___x_3691_ = lean_uint64_dec_eq(v___x_3690_, v___y_3688_);
if (v___x_3691_ == 0)
{
uint64_t v___x_3692_; 
v___x_3692_ = lean_uint64_add(v___y_3681_, v___y_3682_);
v___y_3665_ = v___y_3679_;
v___y_3666_ = v___y_3680_;
v___y_3667_ = v___y_3683_;
v___y_3668_ = v___y_3684_;
v___y_3669_ = v___y_3687_;
v___y_3670_ = v___y_3686_;
v___y_3671_ = v___y_3688_;
v___y_3672_ = v___y_3689_;
v___y_3673_ = v___x_3692_;
goto v___jp_3664_;
}
else
{
v___y_3665_ = v___y_3679_;
v___y_3666_ = v___y_3680_;
v___y_3667_ = v___y_3683_;
v___y_3668_ = v___y_3684_;
v___y_3669_ = v___y_3687_;
v___y_3670_ = v___y_3686_;
v___y_3671_ = v___y_3688_;
v___y_3672_ = v___y_3689_;
v___y_3673_ = v___y_3681_;
goto v___jp_3664_;
}
}
v___jp_3693_:
{
uint64_t v___x_3703_; uint64_t v___x_3704_; uint8_t v___x_3705_; 
v___x_3703_ = 2ULL;
v___x_3704_ = lean_uint64_shift_right(v___y_3698_, v___x_3703_);
v___x_3705_ = lean_uint64_dec_eq(v___x_3704_, v___y_3701_);
if (v___x_3705_ == 0)
{
v___y_3679_ = v___y_3694_;
v___y_3680_ = v___y_3695_;
v___y_3681_ = v___y_3702_;
v___y_3682_ = v___x_3703_;
v___y_3683_ = v___y_3696_;
v___y_3684_ = v___y_3697_;
v___y_3685_ = v___y_3698_;
v___y_3686_ = v___y_3700_;
v___y_3687_ = v___y_3699_;
v___y_3688_ = v___y_3701_;
v___y_3689_ = v___x_3704_;
goto v___jp_3678_;
}
else
{
v___y_3679_ = v___y_3694_;
v___y_3680_ = v___y_3695_;
v___y_3681_ = v___y_3702_;
v___y_3682_ = v___x_3703_;
v___y_3683_ = v___y_3696_;
v___y_3684_ = v___y_3697_;
v___y_3685_ = v___y_3698_;
v___y_3686_ = v___y_3700_;
v___y_3687_ = v___y_3699_;
v___y_3688_ = v___y_3701_;
v___y_3689_ = v___y_3698_;
goto v___jp_3678_;
}
}
v___jp_3706_:
{
uint64_t v___x_3718_; uint8_t v___x_3719_; 
v___x_3718_ = lean_uint64_shift_right(v___y_3707_, v___y_3710_);
v___x_3719_ = lean_uint64_dec_eq(v___x_3718_, v___y_3716_);
if (v___x_3719_ == 0)
{
uint64_t v___x_3720_; 
v___x_3720_ = lean_uint64_add(v___y_3712_, v___y_3710_);
v___y_3694_ = v___y_3708_;
v___y_3695_ = v___y_3709_;
v___y_3696_ = v___y_3711_;
v___y_3697_ = v___y_3713_;
v___y_3698_ = v___y_3717_;
v___y_3699_ = v___y_3715_;
v___y_3700_ = v___y_3714_;
v___y_3701_ = v___y_3716_;
v___y_3702_ = v___x_3720_;
goto v___jp_3693_;
}
else
{
v___y_3694_ = v___y_3708_;
v___y_3695_ = v___y_3709_;
v___y_3696_ = v___y_3711_;
v___y_3697_ = v___y_3713_;
v___y_3698_ = v___y_3717_;
v___y_3699_ = v___y_3715_;
v___y_3700_ = v___y_3714_;
v___y_3701_ = v___y_3716_;
v___y_3702_ = v___y_3712_;
goto v___jp_3693_;
}
}
v___jp_3721_:
{
uint64_t v___x_3731_; uint64_t v___x_3732_; uint8_t v___x_3733_; 
v___x_3731_ = 4ULL;
v___x_3732_ = lean_uint64_shift_right(v___y_3723_, v___x_3731_);
v___x_3733_ = lean_uint64_dec_eq(v___x_3732_, v___y_3729_);
if (v___x_3733_ == 0)
{
v___y_3707_ = v___y_3723_;
v___y_3708_ = v___y_3722_;
v___y_3709_ = v___y_3724_;
v___y_3710_ = v___x_3731_;
v___y_3711_ = v___y_3725_;
v___y_3712_ = v___y_3730_;
v___y_3713_ = v___y_3726_;
v___y_3714_ = v___y_3728_;
v___y_3715_ = v___y_3727_;
v___y_3716_ = v___y_3729_;
v___y_3717_ = v___x_3732_;
goto v___jp_3706_;
}
else
{
v___y_3707_ = v___y_3723_;
v___y_3708_ = v___y_3722_;
v___y_3709_ = v___y_3724_;
v___y_3710_ = v___x_3731_;
v___y_3711_ = v___y_3725_;
v___y_3712_ = v___y_3730_;
v___y_3713_ = v___y_3726_;
v___y_3714_ = v___y_3728_;
v___y_3715_ = v___y_3727_;
v___y_3716_ = v___y_3729_;
v___y_3717_ = v___y_3723_;
goto v___jp_3706_;
}
}
v___jp_3734_:
{
uint64_t v___x_3746_; uint8_t v___x_3747_; 
v___x_3746_ = lean_uint64_shift_right(v___y_3743_, v___y_3735_);
v___x_3747_ = lean_uint64_dec_eq(v___x_3746_, v___y_3744_);
if (v___x_3747_ == 0)
{
uint64_t v___x_3748_; 
v___x_3748_ = lean_uint64_add(v___y_3738_, v___y_3735_);
v___y_3722_ = v___y_3736_;
v___y_3723_ = v___y_3745_;
v___y_3724_ = v___y_3737_;
v___y_3725_ = v___y_3739_;
v___y_3726_ = v___y_3740_;
v___y_3727_ = v___y_3742_;
v___y_3728_ = v___y_3741_;
v___y_3729_ = v___y_3744_;
v___y_3730_ = v___x_3748_;
goto v___jp_3721_;
}
else
{
v___y_3722_ = v___y_3736_;
v___y_3723_ = v___y_3745_;
v___y_3724_ = v___y_3737_;
v___y_3725_ = v___y_3739_;
v___y_3726_ = v___y_3740_;
v___y_3727_ = v___y_3742_;
v___y_3728_ = v___y_3741_;
v___y_3729_ = v___y_3744_;
v___y_3730_ = v___y_3738_;
goto v___jp_3721_;
}
}
v___jp_3749_:
{
uint64_t v___x_3759_; uint64_t v___x_3760_; uint8_t v___x_3761_; 
v___x_3759_ = 8ULL;
v___x_3760_ = lean_uint64_shift_right(v___y_3757_, v___x_3759_);
v___x_3761_ = lean_uint64_dec_eq(v___x_3760_, v___y_3756_);
if (v___x_3761_ == 0)
{
v___y_3735_ = v___x_3759_;
v___y_3736_ = v___y_3750_;
v___y_3737_ = v___y_3751_;
v___y_3738_ = v___y_3758_;
v___y_3739_ = v___y_3752_;
v___y_3740_ = v___y_3753_;
v___y_3741_ = v___y_3755_;
v___y_3742_ = v___y_3754_;
v___y_3743_ = v___y_3757_;
v___y_3744_ = v___y_3756_;
v___y_3745_ = v___x_3760_;
goto v___jp_3734_;
}
else
{
v___y_3735_ = v___x_3759_;
v___y_3736_ = v___y_3750_;
v___y_3737_ = v___y_3751_;
v___y_3738_ = v___y_3758_;
v___y_3739_ = v___y_3752_;
v___y_3740_ = v___y_3753_;
v___y_3741_ = v___y_3755_;
v___y_3742_ = v___y_3754_;
v___y_3743_ = v___y_3757_;
v___y_3744_ = v___y_3756_;
v___y_3745_ = v___y_3757_;
goto v___jp_3734_;
}
}
v___jp_3762_:
{
uint64_t v___x_3774_; uint8_t v___x_3775_; 
v___x_3774_ = lean_uint64_shift_right(v___y_3767_, v___y_3768_);
v___x_3775_ = lean_uint64_dec_eq(v___x_3774_, v___y_3772_);
if (v___x_3775_ == 0)
{
uint64_t v___x_3776_; 
v___x_3776_ = lean_uint64_add(v___y_3766_, v___y_3768_);
v___y_3750_ = v___y_3763_;
v___y_3751_ = v___y_3764_;
v___y_3752_ = v___y_3765_;
v___y_3753_ = v___y_3769_;
v___y_3754_ = v___y_3771_;
v___y_3755_ = v___y_3770_;
v___y_3756_ = v___y_3772_;
v___y_3757_ = v___y_3773_;
v___y_3758_ = v___x_3776_;
goto v___jp_3749_;
}
else
{
v___y_3750_ = v___y_3763_;
v___y_3751_ = v___y_3764_;
v___y_3752_ = v___y_3765_;
v___y_3753_ = v___y_3769_;
v___y_3754_ = v___y_3771_;
v___y_3755_ = v___y_3770_;
v___y_3756_ = v___y_3772_;
v___y_3757_ = v___y_3773_;
v___y_3758_ = v___y_3766_;
goto v___jp_3749_;
}
}
v___jp_3777_:
{
uint64_t v___x_3787_; uint64_t v___x_3788_; uint8_t v___x_3789_; 
v___x_3787_ = 16ULL;
v___x_3788_ = lean_uint64_shift_right(v___y_3781_, v___x_3787_);
v___x_3789_ = lean_uint64_dec_eq(v___x_3788_, v___y_3785_);
if (v___x_3789_ == 0)
{
v___y_3763_ = v___y_3778_;
v___y_3764_ = v___y_3779_;
v___y_3765_ = v___y_3780_;
v___y_3766_ = v___y_3786_;
v___y_3767_ = v___y_3781_;
v___y_3768_ = v___x_3787_;
v___y_3769_ = v___y_3782_;
v___y_3770_ = v___y_3784_;
v___y_3771_ = v___y_3783_;
v___y_3772_ = v___y_3785_;
v___y_3773_ = v___x_3788_;
goto v___jp_3762_;
}
else
{
v___y_3763_ = v___y_3778_;
v___y_3764_ = v___y_3779_;
v___y_3765_ = v___y_3780_;
v___y_3766_ = v___y_3786_;
v___y_3767_ = v___y_3781_;
v___y_3768_ = v___x_3787_;
v___y_3769_ = v___y_3782_;
v___y_3770_ = v___y_3784_;
v___y_3771_ = v___y_3783_;
v___y_3772_ = v___y_3785_;
v___y_3773_ = v___y_3781_;
goto v___jp_3762_;
}
}
v___jp_3790_:
{
uint64_t v___x_3800_; uint64_t v___x_3801_; uint8_t v___x_3802_; 
v___x_3800_ = lean_unbox_uint64(v___y_3795_);
v___x_3801_ = lean_uint64_shift_right(v___x_3800_, v___y_3793_);
v___x_3802_ = lean_uint64_dec_eq(v___x_3801_, v___y_3798_);
if (v___x_3802_ == 0)
{
v___y_3778_ = v___y_3791_;
v___y_3779_ = v___y_3792_;
v___y_3780_ = v___y_3794_;
v___y_3781_ = v___y_3799_;
v___y_3782_ = v___y_3795_;
v___y_3783_ = v___y_3797_;
v___y_3784_ = v___y_3796_;
v___y_3785_ = v___y_3798_;
v___y_3786_ = v___y_3793_;
goto v___jp_3777_;
}
else
{
v___y_3778_ = v___y_3791_;
v___y_3779_ = v___y_3792_;
v___y_3780_ = v___y_3794_;
v___y_3781_ = v___y_3799_;
v___y_3782_ = v___y_3795_;
v___y_3783_ = v___y_3797_;
v___y_3784_ = v___y_3796_;
v___y_3785_ = v___y_3798_;
v___y_3786_ = v___y_3798_;
goto v___jp_3777_;
}
}
v___jp_3803_:
{
uint64_t v___x_3809_; uint64_t v___x_3810_; uint8_t v___x_3811_; 
v___x_3809_ = 0ULL;
v___x_3810_ = lean_unbox_uint64(v_snd_3808_);
v___x_3811_ = lean_uint64_dec_eq(v___x_3810_, v___x_3809_);
if (v___x_3811_ == 0)
{
uint64_t v___x_3812_; uint64_t v___x_3813_; uint64_t v___x_3814_; uint64_t v___x_3815_; uint64_t v___x_3816_; uint8_t v___x_3817_; 
v___x_3812_ = 149ULL;
v___x_3813_ = lean_uint64_add(v___y_3804_, v___x_3812_);
v___x_3814_ = 32ULL;
v___x_3815_ = lean_unbox_uint64(v_snd_3808_);
v___x_3816_ = lean_uint64_shift_right(v___x_3815_, v___x_3814_);
v___x_3817_ = lean_uint64_dec_eq(v___x_3816_, v___x_3809_);
if (v___x_3817_ == 0)
{
v___y_3791_ = v___x_3813_;
v___y_3792_ = v___y_3805_;
v___y_3793_ = v___x_3814_;
v___y_3794_ = v___y_3806_;
v___y_3795_ = v_snd_3808_;
v___y_3796_ = v___x_3812_;
v___y_3797_ = v_fst_3807_;
v___y_3798_ = v___x_3809_;
v___y_3799_ = v___x_3816_;
goto v___jp_3790_;
}
else
{
uint64_t v___x_3818_; 
v___x_3818_ = lean_unbox_uint64(v_snd_3808_);
v___y_3791_ = v___x_3813_;
v___y_3792_ = v___y_3805_;
v___y_3793_ = v___x_3814_;
v___y_3794_ = v___y_3806_;
v___y_3795_ = v_snd_3808_;
v___y_3796_ = v___x_3812_;
v___y_3797_ = v_fst_3807_;
v___y_3798_ = v___x_3809_;
v___y_3799_ = v___x_3818_;
goto v___jp_3790_;
}
}
else
{
uint8_t v___x_3819_; 
lean_dec(v_snd_3808_);
v___x_3819_ = lean_unbox(v_fst_3807_);
lean_dec(v_fst_3807_);
if (v___x_3819_ == 0)
{
uint32_t v___x_3820_; 
v___x_3820_ = 0;
return v___x_3820_;
}
else
{
uint32_t v___x_3821_; 
v___x_3821_ = 2147483648;
return v___x_3821_;
}
}
}
v___jp_3822_:
{
uint8_t v___x_3831_; 
v___x_3831_ = lean_uint64_dec_eq(v___y_3824_, v___y_3829_);
if (v___x_3831_ == 0)
{
uint8_t v___x_3832_; 
v___x_3832_ = lean_uint64_dec_lt(v___y_3824_, v___y_3829_);
if (v___x_3832_ == 0)
{
uint64_t v___x_3833_; lean_object* v___x_3834_; lean_object* v___x_3835_; 
v___x_3833_ = lean_uint64_sub(v___y_3824_, v___y_3829_);
v___x_3834_ = lean_box(v___y_3828_);
v___x_3835_ = lean_box_uint64(v___x_3833_);
v___y_3804_ = v___y_3823_;
v___y_3805_ = v___y_3826_;
v___y_3806_ = v___y_3827_;
v_fst_3807_ = v___x_3834_;
v_snd_3808_ = v___x_3835_;
goto v___jp_3803_;
}
else
{
uint64_t v___x_3836_; lean_object* v___x_3837_; lean_object* v___x_3838_; 
v___x_3836_ = lean_uint64_sub(v___y_3829_, v___y_3824_);
v___x_3837_ = lean_box(v___y_3825_);
v___x_3838_ = lean_box_uint64(v___x_3836_);
v___y_3804_ = v___y_3823_;
v___y_3805_ = v___y_3826_;
v___y_3806_ = v___y_3827_;
v_fst_3807_ = v___x_3837_;
v_snd_3808_ = v___x_3838_;
goto v___jp_3803_;
}
}
else
{
lean_object* v___x_3839_; lean_object* v___x_3840_; 
v___x_3839_ = lean_box(v___y_3830_);
v___x_3840_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_3804_ = v___y_3823_;
v___y_3805_ = v___y_3826_;
v___y_3806_ = v___y_3827_;
v_fst_3807_ = v___x_3839_;
v_snd_3808_ = v___x_3840_;
goto v___jp_3803_;
}
}
v___jp_3841_:
{
if (v___y_3849_ == 0)
{
v___y_3823_ = v___y_3843_;
v___y_3824_ = v___y_3842_;
v___y_3825_ = v___y_3844_;
v___y_3826_ = v___y_3845_;
v___y_3827_ = v___y_3847_;
v___y_3828_ = v___y_3846_;
v___y_3829_ = v___y_3848_;
v___y_3830_ = v___y_3849_;
goto v___jp_3822_;
}
else
{
uint64_t v___x_3850_; lean_object* v___x_3851_; lean_object* v___x_3852_; 
v___x_3850_ = lean_uint64_add(v___y_3842_, v___y_3848_);
v___x_3851_ = lean_box(v___y_3846_);
v___x_3852_ = lean_box_uint64(v___x_3850_);
v___y_3804_ = v___y_3843_;
v___y_3805_ = v___y_3845_;
v___y_3806_ = v___y_3847_;
v_fst_3807_ = v___x_3851_;
v_snd_3808_ = v___x_3852_;
goto v___jp_3803_;
}
}
v___jp_3853_:
{
uint8_t v___x_3862_; 
v___x_3862_ = lean_uint64_dec_eq(v___y_3860_, v___y_3854_);
if (v___x_3862_ == 0)
{
uint8_t v___x_3863_; 
v___x_3863_ = lean_uint64_dec_lt(v___y_3860_, v___y_3854_);
if (v___x_3863_ == 0)
{
uint64_t v___x_3864_; lean_object* v___x_3865_; lean_object* v___x_3866_; 
v___x_3864_ = lean_uint64_sub(v___y_3860_, v___y_3854_);
v___x_3865_ = lean_box(v___y_3858_);
v___x_3866_ = lean_box_uint64(v___x_3864_);
v___y_3491_ = v___y_3856_;
v___y_3492_ = v___y_3857_;
v___y_3493_ = v___y_3859_;
v_fst_3494_ = v___x_3865_;
v_snd_3495_ = v___x_3866_;
goto v___jp_3490_;
}
else
{
uint64_t v___x_3867_; lean_object* v___x_3868_; lean_object* v___x_3869_; 
v___x_3867_ = lean_uint64_sub(v___y_3854_, v___y_3860_);
v___x_3868_ = lean_box(v___y_3855_);
v___x_3869_ = lean_box_uint64(v___x_3867_);
v___y_3491_ = v___y_3856_;
v___y_3492_ = v___y_3857_;
v___y_3493_ = v___y_3859_;
v_fst_3494_ = v___x_3868_;
v_snd_3495_ = v___x_3869_;
goto v___jp_3490_;
}
}
else
{
lean_object* v___x_3870_; lean_object* v___x_3871_; 
v___x_3870_ = lean_box(v___y_3861_);
v___x_3871_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_3491_ = v___y_3856_;
v___y_3492_ = v___y_3857_;
v___y_3493_ = v___y_3859_;
v_fst_3494_ = v___x_3870_;
v_snd_3495_ = v___x_3871_;
goto v___jp_3490_;
}
}
v___jp_3872_:
{
if (v___y_3880_ == 0)
{
v___y_3854_ = v___y_3873_;
v___y_3855_ = v___y_3874_;
v___y_3856_ = v___y_3875_;
v___y_3857_ = v___y_3877_;
v___y_3858_ = v___y_3876_;
v___y_3859_ = v___y_3878_;
v___y_3860_ = v___y_3879_;
v___y_3861_ = v___y_3880_;
goto v___jp_3853_;
}
else
{
uint64_t v___x_3881_; lean_object* v___x_3882_; lean_object* v___x_3883_; 
v___x_3881_ = lean_uint64_add(v___y_3879_, v___y_3873_);
v___x_3882_ = lean_box(v___y_3876_);
v___x_3883_ = lean_box_uint64(v___x_3881_);
v___y_3491_ = v___y_3875_;
v___y_3492_ = v___y_3877_;
v___y_3493_ = v___y_3878_;
v_fst_3494_ = v___x_3882_;
v_snd_3495_ = v___x_3883_;
goto v___jp_3490_;
}
}
v___jp_3884_:
{
uint8_t v___x_3893_; 
v___x_3893_ = lean_uint64_dec_le(v___y_3889_, v___y_3892_);
if (v___x_3893_ == 0)
{
uint64_t v_shift_3894_; uint64_t v___x_3895_; uint8_t v___x_3896_; 
v_shift_3894_ = lean_uint64_sub(v___y_3889_, v___y_3892_);
v___x_3895_ = 39ULL;
v___x_3896_ = lean_uint64_dec_le(v_shift_3894_, v___x_3895_);
if (v___x_3896_ == 0)
{
return v_x_3186_;
}
else
{
uint64_t v___x_3897_; 
v___x_3897_ = lean_uint64_shift_left(v___y_3890_, v_shift_3894_);
if (v___y_3887_ == 0)
{
if (v___y_3885_ == 0)
{
v___y_3842_ = v___x_3897_;
v___y_3843_ = v___y_3892_;
v___y_3844_ = v___y_3885_;
v___y_3845_ = v___y_3886_;
v___y_3846_ = v___y_3887_;
v___y_3847_ = v___y_3888_;
v___y_3848_ = v___y_3891_;
v___y_3849_ = v___x_3896_;
goto v___jp_3841_;
}
else
{
v___y_3823_ = v___y_3892_;
v___y_3824_ = v___x_3897_;
v___y_3825_ = v___y_3885_;
v___y_3826_ = v___y_3886_;
v___y_3827_ = v___y_3888_;
v___y_3828_ = v___y_3887_;
v___y_3829_ = v___y_3891_;
v___y_3830_ = v___y_3887_;
goto v___jp_3822_;
}
}
else
{
v___y_3842_ = v___x_3897_;
v___y_3843_ = v___y_3892_;
v___y_3844_ = v___y_3885_;
v___y_3845_ = v___y_3886_;
v___y_3846_ = v___y_3887_;
v___y_3847_ = v___y_3888_;
v___y_3848_ = v___y_3891_;
v___y_3849_ = v___y_3885_;
goto v___jp_3841_;
}
}
}
else
{
uint64_t v_shift_3898_; uint64_t v___x_3899_; uint8_t v___x_3900_; 
v_shift_3898_ = lean_uint64_sub(v___y_3892_, v___y_3889_);
v___x_3899_ = 39ULL;
v___x_3900_ = lean_uint64_dec_le(v_shift_3898_, v___x_3899_);
if (v___x_3900_ == 0)
{
return v_y_3187_;
}
else
{
uint64_t v___x_3901_; 
v___x_3901_ = lean_uint64_shift_left(v___y_3891_, v_shift_3898_);
if (v___y_3887_ == 0)
{
if (v___y_3885_ == 0)
{
v___y_3873_ = v___x_3901_;
v___y_3874_ = v___y_3885_;
v___y_3875_ = v___y_3886_;
v___y_3876_ = v___y_3887_;
v___y_3877_ = v___y_3888_;
v___y_3878_ = v___y_3889_;
v___y_3879_ = v___y_3890_;
v___y_3880_ = v___x_3900_;
goto v___jp_3872_;
}
else
{
v___y_3854_ = v___x_3901_;
v___y_3855_ = v___y_3885_;
v___y_3856_ = v___y_3886_;
v___y_3857_ = v___y_3888_;
v___y_3858_ = v___y_3887_;
v___y_3859_ = v___y_3889_;
v___y_3860_ = v___y_3890_;
v___y_3861_ = v___y_3887_;
goto v___jp_3853_;
}
}
else
{
v___y_3873_ = v___x_3901_;
v___y_3874_ = v___y_3885_;
v___y_3875_ = v___y_3886_;
v___y_3876_ = v___y_3887_;
v___y_3877_ = v___y_3888_;
v___y_3878_ = v___y_3889_;
v___y_3879_ = v___y_3890_;
v___y_3880_ = v___y_3885_;
goto v___jp_3872_;
}
}
}
}
v___jp_3902_:
{
uint64_t v___x_3911_; uint64_t v___x_3912_; uint8_t v___x_3913_; 
v___x_3911_ = lean_uint32_to_uint64(v___y_3908_);
v___x_3912_ = 0ULL;
v___x_3913_ = lean_uint64_dec_eq(v___x_3911_, v___x_3912_);
if (v___x_3913_ == 0)
{
uint64_t v___x_3914_; uint64_t v___x_3915_; 
v___x_3914_ = 1ULL;
v___x_3915_ = lean_uint64_sub(v___x_3911_, v___x_3914_);
v___y_3885_ = v___y_3903_;
v___y_3886_ = v___y_3904_;
v___y_3887_ = v___y_3905_;
v___y_3888_ = v___y_3906_;
v___y_3889_ = v___y_3910_;
v___y_3890_ = v___y_3907_;
v___y_3891_ = v___y_3909_;
v___y_3892_ = v___x_3915_;
goto v___jp_3884_;
}
else
{
v___y_3885_ = v___y_3903_;
v___y_3886_ = v___y_3904_;
v___y_3887_ = v___y_3905_;
v___y_3888_ = v___y_3906_;
v___y_3889_ = v___y_3910_;
v___y_3890_ = v___y_3907_;
v___y_3891_ = v___y_3909_;
v___y_3892_ = v___x_3912_;
goto v___jp_3884_;
}
}
v___jp_3916_:
{
uint64_t v___x_3925_; uint64_t v___x_3926_; uint8_t v___x_3927_; 
v___x_3925_ = lean_uint32_to_uint64(v___y_3917_);
v___x_3926_ = 0ULL;
v___x_3927_ = lean_uint64_dec_eq(v___x_3925_, v___x_3926_);
if (v___x_3927_ == 0)
{
uint64_t v___x_3928_; uint64_t v___x_3929_; 
v___x_3928_ = 1ULL;
v___x_3929_ = lean_uint64_sub(v___x_3925_, v___x_3928_);
v___y_3903_ = v___y_3918_;
v___y_3904_ = v___y_3919_;
v___y_3905_ = v___y_3921_;
v___y_3906_ = v___y_3920_;
v___y_3907_ = v___y_3922_;
v___y_3908_ = v___y_3923_;
v___y_3909_ = v___y_3924_;
v___y_3910_ = v___x_3929_;
goto v___jp_3902_;
}
else
{
v___y_3903_ = v___y_3918_;
v___y_3904_ = v___y_3919_;
v___y_3905_ = v___y_3921_;
v___y_3906_ = v___y_3920_;
v___y_3907_ = v___y_3922_;
v___y_3908_ = v___y_3923_;
v___y_3909_ = v___y_3924_;
v___y_3910_ = v___x_3926_;
goto v___jp_3902_;
}
}
v___jp_3930_:
{
uint32_t v___x_3938_; uint32_t v___x_3939_; uint32_t v___x_3940_; uint8_t v___x_3941_; 
v___x_3938_ = 8388607;
v___x_3939_ = lean_uint32_land(v_y_3187_, v___x_3938_);
v___x_3940_ = 0;
v___x_3941_ = lean_uint32_dec_eq(v___y_3936_, v___x_3940_);
if (v___x_3941_ == 0)
{
uint64_t v___x_3942_; uint64_t v___x_3943_; uint64_t v___x_3944_; 
v___x_3942_ = lean_uint32_to_uint64(v___x_3939_);
v___x_3943_ = 8388608ULL;
v___x_3944_ = lean_uint64_lor(v___x_3942_, v___x_3943_);
v___y_3917_ = v___y_3931_;
v___y_3918_ = v___y_3932_;
v___y_3919_ = v___y_3933_;
v___y_3920_ = v___y_3935_;
v___y_3921_ = v___y_3934_;
v___y_3922_ = v___y_3937_;
v___y_3923_ = v___y_3936_;
v___y_3924_ = v___x_3944_;
goto v___jp_3916_;
}
else
{
uint64_t v___x_3945_; 
v___x_3945_ = lean_uint32_to_uint64(v___x_3939_);
v___y_3917_ = v___y_3931_;
v___y_3918_ = v___y_3932_;
v___y_3919_ = v___y_3933_;
v___y_3920_ = v___y_3935_;
v___y_3921_ = v___y_3934_;
v___y_3922_ = v___y_3937_;
v___y_3923_ = v___y_3936_;
v___y_3924_ = v___x_3945_;
goto v___jp_3916_;
}
}
v___jp_3946_:
{
uint32_t v___x_3953_; uint32_t v___x_3954_; uint32_t v___x_3955_; uint8_t v___x_3956_; 
v___x_3953_ = 8388607;
v___x_3954_ = lean_uint32_land(v_x_3186_, v___x_3953_);
v___x_3955_ = 0;
v___x_3956_ = lean_uint32_dec_eq(v___y_3947_, v___x_3955_);
if (v___x_3956_ == 0)
{
uint64_t v___x_3957_; uint64_t v___x_3958_; uint64_t v___x_3959_; 
v___x_3957_ = lean_uint32_to_uint64(v___x_3954_);
v___x_3958_ = 8388608ULL;
v___x_3959_ = lean_uint64_lor(v___x_3957_, v___x_3958_);
v___y_3931_ = v___y_3947_;
v___y_3932_ = v___y_3952_;
v___y_3933_ = v___y_3948_;
v___y_3934_ = v___y_3950_;
v___y_3935_ = v___y_3949_;
v___y_3936_ = v___y_3951_;
v___y_3937_ = v___x_3959_;
goto v___jp_3930_;
}
else
{
uint64_t v___x_3960_; 
v___x_3960_ = lean_uint32_to_uint64(v___x_3954_);
v___y_3931_ = v___y_3947_;
v___y_3932_ = v___y_3952_;
v___y_3933_ = v___y_3948_;
v___y_3934_ = v___y_3950_;
v___y_3935_ = v___y_3949_;
v___y_3936_ = v___y_3951_;
v___y_3937_ = v___x_3960_;
goto v___jp_3930_;
}
}
v___jp_3961_:
{
uint32_t v___x_3968_; uint32_t v___x_3969_; uint32_t v___x_3970_; uint8_t v___x_3971_; 
v___x_3968_ = 2147483648;
v___x_3969_ = lean_uint32_land(v_y_3187_, v___x_3968_);
v___x_3970_ = 0;
v___x_3971_ = lean_uint32_dec_eq(v___x_3969_, v___x_3970_);
if (v___x_3971_ == 0)
{
uint8_t v___x_3972_; 
v___x_3972_ = 1;
v___y_3947_ = v___y_3962_;
v___y_3948_ = v___y_3964_;
v___y_3949_ = v___y_3965_;
v___y_3950_ = v___y_3967_;
v___y_3951_ = v___y_3966_;
v___y_3952_ = v___x_3972_;
goto v___jp_3946_;
}
else
{
v___y_3947_ = v___y_3962_;
v___y_3948_ = v___y_3964_;
v___y_3949_ = v___y_3965_;
v___y_3950_ = v___y_3967_;
v___y_3951_ = v___y_3966_;
v___y_3952_ = v___y_3963_;
goto v___jp_3946_;
}
}
v___jp_3973_:
{
if (v___y_3974_ == 0)
{
uint32_t v___x_3975_; uint32_t v___x_3976_; uint32_t v___x_3977_; uint32_t v_xExponent_3978_; uint32_t v___x_3979_; uint32_t v_yExponent_3980_; uint32_t v___x_3981_; uint32_t v___x_3982_; uint32_t v___x_3983_; uint8_t v___x_3984_; 
v___x_3975_ = 23;
v___x_3976_ = lean_uint32_shift_right(v_x_3186_, v___x_3975_);
v___x_3977_ = 255;
v_xExponent_3978_ = lean_uint32_land(v___x_3976_, v___x_3977_);
v___x_3979_ = lean_uint32_shift_right(v_y_3187_, v___x_3975_);
v_yExponent_3980_ = lean_uint32_land(v___x_3979_, v___x_3977_);
v___x_3981_ = 2147483648;
v___x_3982_ = lean_uint32_land(v_x_3186_, v___x_3981_);
v___x_3983_ = 0;
v___x_3984_ = lean_uint32_dec_eq(v___x_3982_, v___x_3983_);
if (v___x_3984_ == 0)
{
uint8_t v___x_3985_; 
v___x_3985_ = 1;
v___y_3962_ = v_xExponent_3978_;
v___y_3963_ = v___y_3974_;
v___y_3964_ = v___x_3975_;
v___y_3965_ = v___x_3977_;
v___y_3966_ = v_yExponent_3980_;
v___y_3967_ = v___x_3985_;
goto v___jp_3961_;
}
else
{
v___y_3962_ = v_xExponent_3978_;
v___y_3963_ = v___y_3974_;
v___y_3964_ = v___x_3975_;
v___y_3965_ = v___x_3977_;
v___y_3966_ = v_yExponent_3980_;
v___y_3967_ = v___y_3974_;
goto v___jp_3961_;
}
}
else
{
lean_object* v___x_3986_; lean_object* v___x_3987_; lean_object* v___x_3988_; lean_object* v___x_3989_; uint32_t v___x_3990_; 
v___x_3986_ = ((lean_object*)(lp_competition_Submission_TunedAdd_add___closed__0));
v___x_3987_ = lean_uint32_to_nat(v_x_3186_);
v___x_3988_ = lean_uint32_to_nat(v_y_3187_);
v___x_3989_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(v___x_3986_, v___x_3987_, v___x_3988_);
v___x_3990_ = lean_uint32_of_nat(v___x_3989_);
lean_dec(v___x_3989_);
return v___x_3990_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object* v_x_3999_, lean_object* v_y_4000_){
_start:
{
uint32_t v_x_boxed_4001_; uint32_t v_y_boxed_4002_; uint32_t v_res_4003_; lean_object* v_r_4004_; 
v_x_boxed_4001_ = lean_unbox_uint32(v_x_3999_);
lean_dec(v_x_3999_);
v_y_boxed_4002_ = lean_unbox_uint32(v_y_4000_);
lean_dec(v_y_4000_);
v_res_4003_ = lp_competition_Submission_add(v_x_boxed_4001_, v_y_boxed_4002_);
v_r_4004_ = lean_box_uint32(v_res_4003_);
return v_r_4004_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t v_x_4005_, uint32_t v_y_4006_){
_start:
{
uint32_t v___y_4008_; uint32_t v___y_4012_; uint32_t v___y_4013_; uint32_t v___y_4014_; uint32_t v___y_4018_; uint8_t v___y_4019_; uint64_t v___y_4020_; uint64_t v___y_4021_; uint32_t v___y_4033_; uint32_t v___y_4034_; uint32_t v___y_4035_; uint32_t v___y_4036_; uint32_t v___y_4037_; uint32_t v___y_4038_; uint32_t v___y_4045_; uint32_t v___y_4046_; uint32_t v___y_4047_; uint32_t v___y_4048_; uint8_t v___y_4049_; uint32_t v___y_4050_; uint32_t v___y_4054_; uint32_t v___y_4055_; uint64_t v___y_4056_; uint32_t v___y_4057_; uint8_t v___y_4058_; uint64_t v___y_4059_; uint64_t v___y_4060_; uint8_t v___y_4070_; uint32_t v___y_4071_; uint32_t v___y_4072_; uint32_t v___y_4073_; uint8_t v___y_4074_; uint64_t v___y_4075_; uint64_t v___y_4076_; uint64_t v___y_4077_; uint64_t v___y_4084_; uint32_t v___y_4085_; uint32_t v___y_4086_; uint32_t v___y_4087_; uint8_t v___y_4088_; uint64_t v___y_4089_; uint64_t v___y_4090_; uint32_t v___y_4096_; uint32_t v___y_4097_; uint64_t v___y_4098_; uint32_t v___y_4099_; uint64_t v___y_4100_; uint8_t v___y_4101_; uint64_t v___y_4102_; uint64_t v___y_4103_; uint32_t v___y_4158_; uint64_t v___y_4159_; uint32_t v___y_4160_; uint32_t v___y_4161_; uint64_t v___y_4162_; uint8_t v___y_4163_; uint64_t v___y_4164_; uint64_t v___y_4165_; uint64_t v___y_4166_; uint32_t v___y_4172_; uint64_t v___y_4173_; uint32_t v___y_4174_; uint64_t v___y_4175_; uint32_t v___y_4176_; uint64_t v___y_4177_; uint64_t v___y_4178_; uint8_t v___y_4179_; uint64_t v___y_4180_; uint64_t v___y_4181_; uint64_t v___y_4182_; uint32_t v___y_4187_; uint64_t v___y_4188_; uint32_t v___y_4189_; uint64_t v___y_4190_; uint32_t v___y_4191_; uint8_t v___y_4192_; uint64_t v___y_4193_; uint64_t v___y_4194_; uint64_t v___y_4195_; uint64_t v___y_4200_; uint32_t v___y_4201_; uint32_t v___y_4202_; uint64_t v___y_4203_; uint32_t v___y_4204_; uint64_t v___y_4205_; uint64_t v___y_4206_; uint8_t v___y_4207_; uint64_t v___y_4208_; uint64_t v___y_4209_; uint64_t v___y_4210_; uint64_t v___y_4215_; uint32_t v___y_4216_; uint64_t v___y_4217_; uint32_t v___y_4218_; uint32_t v___y_4219_; uint8_t v___y_4220_; uint64_t v___y_4221_; uint64_t v___y_4222_; uint64_t v___y_4223_; uint64_t v___y_4228_; uint32_t v___y_4229_; uint32_t v___y_4230_; uint64_t v___y_4231_; uint32_t v___y_4232_; uint64_t v___y_4233_; uint64_t v___y_4234_; uint8_t v___y_4235_; uint64_t v___y_4236_; uint64_t v___y_4237_; uint64_t v___y_4238_; uint32_t v___y_4243_; uint64_t v___y_4244_; uint32_t v___y_4245_; uint32_t v___y_4246_; uint8_t v___y_4247_; uint64_t v___y_4248_; uint64_t v___y_4249_; uint64_t v___y_4250_; uint64_t v___y_4251_; uint64_t v___y_4256_; uint32_t v___y_4257_; uint32_t v___y_4258_; uint64_t v___y_4259_; uint32_t v___y_4260_; uint64_t v___y_4261_; uint64_t v___y_4262_; uint64_t v___y_4263_; uint8_t v___y_4264_; uint64_t v___y_4265_; uint64_t v___y_4266_; uint32_t v___y_4271_; uint64_t v___y_4272_; uint32_t v___y_4273_; uint32_t v___y_4274_; uint64_t v___y_4275_; uint8_t v___y_4276_; uint64_t v___y_4277_; uint64_t v___y_4278_; uint64_t v___y_4279_; uint32_t v___y_4284_; uint32_t v___y_4285_; uint64_t v___y_4286_; uint32_t v___y_4287_; uint64_t v___y_4288_; uint8_t v___y_4289_; uint64_t v___y_4290_; uint64_t v___y_4291_; uint64_t v___y_4292_; uint32_t v___y_4296_; uint32_t v___y_4297_; uint32_t v___y_4298_; uint64_t v___y_4299_; uint8_t v___y_4300_; uint64_t v___y_4301_; uint64_t v___y_4302_; uint64_t v___y_4303_; uint32_t v___y_4314_; uint32_t v___y_4315_; uint32_t v___y_4316_; uint32_t v___y_4317_; uint64_t v___y_4318_; uint8_t v___y_4319_; uint64_t v___y_4320_; uint64_t v___y_4321_; uint32_t v___y_4328_; uint32_t v___y_4329_; uint32_t v___y_4330_; uint32_t v___y_4331_; uint32_t v___y_4332_; uint8_t v___y_4333_; uint64_t v___y_4334_; uint64_t v___y_4335_; uint32_t v___y_4342_; uint32_t v___y_4343_; uint32_t v___y_4344_; uint32_t v___y_4345_; uint32_t v___y_4346_; uint8_t v___y_4347_; uint32_t v___y_4348_; uint64_t v___y_4349_; uint32_t v___y_4357_; uint32_t v___y_4358_; uint32_t v___y_4359_; uint32_t v___y_4360_; uint8_t v___y_4361_; uint32_t v___y_4372_; uint32_t v___y_4373_; uint32_t v___y_4374_; uint32_t v___y_4375_; uint8_t v___y_4378_; uint32_t v___y_4379_; uint32_t v___y_4380_; uint8_t v___y_4381_; uint32_t v___y_4382_; uint32_t v___y_4383_; uint8_t v___y_4384_; uint32_t v___y_4386_; uint8_t v___y_4387_; uint32_t v___y_4388_; uint32_t v___y_4389_; uint32_t v___y_4390_; uint8_t v___y_4391_; uint8_t v___y_4398_; uint32_t v___x_4415_; uint32_t v___x_4416_; uint32_t v___x_4417_; uint8_t v___x_4418_; 
v___x_4415_ = 4278190080;
v___x_4416_ = 1;
v___x_4417_ = lean_uint32_shift_left(v_x_4005_, v___x_4416_);
v___x_4418_ = lean_uint32_dec_le(v___x_4415_, v___x_4417_);
if (v___x_4418_ == 0)
{
uint32_t v___x_4419_; uint8_t v___x_4420_; 
v___x_4419_ = lean_uint32_shift_left(v_y_4006_, v___x_4416_);
v___x_4420_ = lean_uint32_dec_le(v___x_4415_, v___x_4419_);
v___y_4398_ = v___x_4420_;
goto v___jp_4397_;
}
else
{
v___y_4398_ = v___x_4418_;
goto v___jp_4397_;
}
v___jp_4007_:
{
uint32_t v___x_4009_; uint32_t v___x_4010_; 
v___x_4009_ = 8388608;
v___x_4010_ = lean_uint32_lor(v___y_4008_, v___x_4009_);
return v___x_4010_;
}
v___jp_4011_:
{
uint32_t v___x_4015_; uint32_t v___x_4016_; 
v___x_4015_ = lean_uint32_land(v___y_4013_, v___y_4012_);
v___x_4016_ = lean_uint32_lor(v___y_4014_, v___x_4015_);
return v___x_4016_;
}
v___jp_4017_:
{
uint8_t v___x_4022_; 
v___x_4022_ = lean_uint64_dec_eq(v___y_4021_, v___y_4020_);
if (v___x_4022_ == 0)
{
uint64_t v___x_4023_; uint8_t v___x_4024_; 
v___x_4023_ = 8388608ULL;
v___x_4024_ = lean_uint64_dec_eq(v___y_4021_, v___x_4023_);
if (v___x_4024_ == 0)
{
uint32_t v___x_4025_; 
v___x_4025_ = lean_uint64_to_uint32(v___y_4021_);
if (v___y_4019_ == 0)
{
uint32_t v___x_4026_; 
v___x_4026_ = 0;
v___y_4012_ = v___y_4018_;
v___y_4013_ = v___x_4025_;
v___y_4014_ = v___x_4026_;
goto v___jp_4011_;
}
else
{
uint32_t v___x_4027_; 
v___x_4027_ = 2147483648;
v___y_4012_ = v___y_4018_;
v___y_4013_ = v___x_4025_;
v___y_4014_ = v___x_4027_;
goto v___jp_4011_;
}
}
else
{
if (v___y_4019_ == 0)
{
uint32_t v___x_4028_; 
v___x_4028_ = 0;
v___y_4008_ = v___x_4028_;
goto v___jp_4007_;
}
else
{
uint32_t v___x_4029_; 
v___x_4029_ = 2147483648;
v___y_4008_ = v___x_4029_;
goto v___jp_4007_;
}
}
}
else
{
if (v___y_4019_ == 0)
{
uint32_t v___x_4030_; 
v___x_4030_ = 0;
return v___x_4030_;
}
else
{
uint32_t v___x_4031_; 
v___x_4031_ = 2147483648;
return v___x_4031_;
}
}
}
v___jp_4032_:
{
uint32_t v___x_4039_; uint32_t v___x_4040_; uint32_t v___x_4041_; uint32_t v___x_4042_; uint32_t v___x_4043_; 
v___x_4039_ = lean_uint32_land(v___y_4033_, v___y_4036_);
v___x_4040_ = lean_uint32_shift_left(v___x_4039_, v___y_4034_);
v___x_4041_ = lean_uint32_lor(v___y_4038_, v___x_4040_);
v___x_4042_ = lean_uint32_land(v___y_4037_, v___y_4035_);
v___x_4043_ = lean_uint32_lor(v___x_4041_, v___x_4042_);
return v___x_4043_;
}
v___jp_4044_:
{
if (v___y_4049_ == 0)
{
uint32_t v___x_4051_; 
v___x_4051_ = 0;
v___y_4033_ = v___y_4045_;
v___y_4034_ = v___y_4046_;
v___y_4035_ = v___y_4047_;
v___y_4036_ = v___y_4048_;
v___y_4037_ = v___y_4050_;
v___y_4038_ = v___x_4051_;
goto v___jp_4032_;
}
else
{
uint32_t v___x_4052_; 
v___x_4052_ = 2147483648;
v___y_4033_ = v___y_4045_;
v___y_4034_ = v___y_4046_;
v___y_4035_ = v___y_4047_;
v___y_4036_ = v___y_4048_;
v___y_4037_ = v___y_4050_;
v___y_4038_ = v___x_4052_;
goto v___jp_4032_;
}
}
v___jp_4053_:
{
uint64_t v___x_4061_; uint64_t v_encodedExponent_4062_; uint32_t v___x_4063_; uint64_t v___x_4064_; uint8_t v___x_4065_; 
v___x_4061_ = 171ULL;
v_encodedExponent_4062_ = lean_uint64_sub(v___y_4056_, v___x_4061_);
v___x_4063_ = lean_uint64_to_uint32(v_encodedExponent_4062_);
v___x_4064_ = 8388608ULL;
v___x_4065_ = lean_uint64_dec_lt(v___y_4060_, v___x_4064_);
if (v___x_4065_ == 0)
{
uint64_t v___x_4066_; uint32_t v___x_4067_; 
v___x_4066_ = lean_uint64_sub(v___y_4060_, v___x_4064_);
v___x_4067_ = lean_uint64_to_uint32(v___x_4066_);
v___y_4045_ = v___x_4063_;
v___y_4046_ = v___y_4054_;
v___y_4047_ = v___y_4055_;
v___y_4048_ = v___y_4057_;
v___y_4049_ = v___y_4058_;
v___y_4050_ = v___x_4067_;
goto v___jp_4044_;
}
else
{
uint32_t v___x_4068_; 
v___x_4068_ = lean_uint64_to_uint32(v___y_4059_);
v___y_4045_ = v___x_4063_;
v___y_4046_ = v___y_4054_;
v___y_4047_ = v___y_4055_;
v___y_4048_ = v___y_4057_;
v___y_4049_ = v___y_4058_;
v___y_4050_ = v___x_4068_;
goto v___jp_4044_;
}
}
v___jp_4069_:
{
uint64_t v___x_4078_; uint8_t v___x_4079_; 
v___x_4078_ = 425ULL;
v___x_4079_ = lean_uint64_dec_lt(v___x_4078_, v___y_4077_);
if (v___x_4079_ == 0)
{
if (v___y_4070_ == 0)
{
v___y_4054_ = v___y_4071_;
v___y_4055_ = v___y_4072_;
v___y_4056_ = v___y_4077_;
v___y_4057_ = v___y_4073_;
v___y_4058_ = v___y_4074_;
v___y_4059_ = v___y_4076_;
v___y_4060_ = v___y_4075_;
goto v___jp_4053_;
}
else
{
uint64_t v___x_4080_; 
v___x_4080_ = 8388608ULL;
v___y_4054_ = v___y_4071_;
v___y_4055_ = v___y_4072_;
v___y_4056_ = v___y_4077_;
v___y_4057_ = v___y_4073_;
v___y_4058_ = v___y_4074_;
v___y_4059_ = v___y_4076_;
v___y_4060_ = v___x_4080_;
goto v___jp_4053_;
}
}
else
{
if (v___y_4074_ == 0)
{
uint32_t v___x_4081_; 
v___x_4081_ = 2139095040;
return v___x_4081_;
}
else
{
uint32_t v___x_4082_; 
v___x_4082_ = 4286578688;
return v___x_4082_;
}
}
}
v___jp_4083_:
{
uint64_t v___x_4091_; uint8_t v_carry_4092_; 
v___x_4091_ = 16777216ULL;
v_carry_4092_ = lean_uint64_dec_eq(v___y_4090_, v___x_4091_);
if (v_carry_4092_ == 0)
{
v___y_4070_ = v_carry_4092_;
v___y_4071_ = v___y_4085_;
v___y_4072_ = v___y_4086_;
v___y_4073_ = v___y_4087_;
v___y_4074_ = v___y_4088_;
v___y_4075_ = v___y_4090_;
v___y_4076_ = v___y_4089_;
v___y_4077_ = v___y_4084_;
goto v___jp_4069_;
}
else
{
uint64_t v___x_4093_; uint64_t v___x_4094_; 
v___x_4093_ = 1ULL;
v___x_4094_ = lean_uint64_add(v___y_4084_, v___x_4093_);
v___y_4070_ = v_carry_4092_;
v___y_4071_ = v___y_4085_;
v___y_4072_ = v___y_4086_;
v___y_4073_ = v___y_4087_;
v___y_4074_ = v___y_4088_;
v___y_4075_ = v___y_4090_;
v___y_4076_ = v___y_4089_;
v___y_4077_ = v___x_4094_;
goto v___jp_4069_;
}
}
v___jp_4095_:
{
uint64_t v_position_4104_; uint64_t v___x_4105_; uint8_t v___x_4106_; 
v_position_4104_ = lean_uint64_add(v___y_4103_, v___y_4098_);
v___x_4105_ = 172ULL;
v___x_4106_ = lean_uint64_dec_lt(v_position_4104_, v___x_4105_);
if (v___x_4106_ == 0)
{
uint64_t v___x_4107_; uint8_t v___x_4108_; 
v___x_4107_ = 23ULL;
v___x_4108_ = lean_uint64_dec_lt(v___y_4103_, v___x_4107_);
if (v___x_4108_ == 0)
{
uint64_t v___x_4109_; uint8_t v___x_4110_; 
v___x_4109_ = lean_uint64_sub(v___y_4103_, v___x_4107_);
v___x_4110_ = lean_uint64_dec_eq(v___x_4109_, v___y_4102_);
if (v___x_4110_ == 0)
{
uint64_t v___x_4111_; uint8_t v___x_4112_; 
v___x_4111_ = 64ULL;
v___x_4112_ = lean_uint64_dec_lt(v___x_4109_, v___x_4111_);
if (v___x_4112_ == 0)
{
uint8_t v___x_4113_; 
v___x_4113_ = lean_uint64_dec_eq(v___x_4109_, v___x_4111_);
if (v___x_4113_ == 0)
{
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v___y_4102_;
goto v___jp_4083_;
}
else
{
uint64_t v___x_4114_; uint8_t v___x_4115_; 
v___x_4114_ = 9223372036854775808ULL;
v___x_4115_ = lean_uint64_dec_lt(v___x_4114_, v___y_4100_);
if (v___x_4115_ == 0)
{
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v___y_4102_;
goto v___jp_4083_;
}
else
{
uint64_t v___x_4116_; 
v___x_4116_ = 1ULL;
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v___x_4116_;
goto v___jp_4083_;
}
}
}
else
{
uint64_t v_quotient_4117_; uint64_t v___x_4118_; uint64_t v___x_4119_; uint64_t v___x_4120_; uint64_t v_remainder_4121_; uint64_t v___x_4122_; uint64_t v_half_4123_; uint8_t v___x_4124_; 
v_quotient_4117_ = lean_uint64_shift_right(v___y_4100_, v___x_4109_);
v___x_4118_ = 1ULL;
v___x_4119_ = lean_uint64_shift_left(v___x_4118_, v___x_4109_);
v___x_4120_ = lean_uint64_sub(v___x_4119_, v___x_4118_);
v_remainder_4121_ = lean_uint64_land(v___y_4100_, v___x_4120_);
v___x_4122_ = lean_uint64_sub(v___x_4109_, v___x_4118_);
v_half_4123_ = lean_uint64_shift_left(v___x_4118_, v___x_4122_);
v___x_4124_ = lean_uint64_dec_lt(v_remainder_4121_, v_half_4123_);
if (v___x_4124_ == 0)
{
uint8_t v___x_4125_; 
v___x_4125_ = lean_uint64_dec_lt(v_half_4123_, v_remainder_4121_);
if (v___x_4125_ == 0)
{
uint64_t v___x_4126_; uint8_t v___x_4127_; 
v___x_4126_ = lean_uint64_land(v_quotient_4117_, v___x_4118_);
v___x_4127_ = lean_uint64_dec_eq(v___x_4126_, v___y_4102_);
if (v___x_4127_ == 0)
{
uint64_t v___x_4128_; 
v___x_4128_ = lean_uint64_add(v_quotient_4117_, v___x_4118_);
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v___x_4128_;
goto v___jp_4083_;
}
else
{
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v_quotient_4117_;
goto v___jp_4083_;
}
}
else
{
uint64_t v___x_4129_; 
v___x_4129_ = lean_uint64_add(v_quotient_4117_, v___x_4118_);
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v___x_4129_;
goto v___jp_4083_;
}
}
else
{
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v_quotient_4117_;
goto v___jp_4083_;
}
}
}
else
{
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v___y_4100_;
goto v___jp_4083_;
}
}
else
{
uint64_t v___x_4130_; uint64_t v___x_4131_; 
v___x_4130_ = lean_uint64_sub(v___x_4107_, v___y_4103_);
v___x_4131_ = lean_uint64_shift_left(v___y_4100_, v___x_4130_);
v___y_4084_ = v_position_4104_;
v___y_4085_ = v___y_4096_;
v___y_4086_ = v___y_4097_;
v___y_4087_ = v___y_4099_;
v___y_4088_ = v___y_4101_;
v___y_4089_ = v___y_4102_;
v___y_4090_ = v___x_4131_;
goto v___jp_4083_;
}
}
else
{
uint64_t v___x_4132_; uint8_t v___x_4133_; 
v___x_4132_ = 149ULL;
v___x_4133_ = lean_uint64_dec_lt(v___y_4098_, v___x_4132_);
if (v___x_4133_ == 0)
{
uint64_t v___x_4134_; uint64_t v___x_4135_; 
v___x_4134_ = lean_uint64_sub(v___y_4098_, v___x_4132_);
v___x_4135_ = lean_uint64_shift_left(v___y_4100_, v___x_4134_);
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v___x_4135_;
goto v___jp_4017_;
}
else
{
uint64_t v___x_4136_; uint8_t v___x_4137_; 
v___x_4136_ = lean_uint64_sub(v___x_4132_, v___y_4098_);
v___x_4137_ = lean_uint64_dec_eq(v___x_4136_, v___y_4102_);
if (v___x_4137_ == 0)
{
uint64_t v___x_4138_; uint8_t v___x_4139_; 
v___x_4138_ = 64ULL;
v___x_4139_ = lean_uint64_dec_lt(v___x_4136_, v___x_4138_);
if (v___x_4139_ == 0)
{
uint8_t v___x_4140_; 
v___x_4140_ = lean_uint64_dec_eq(v___x_4136_, v___x_4138_);
if (v___x_4140_ == 0)
{
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v___y_4102_;
goto v___jp_4017_;
}
else
{
uint64_t v___x_4141_; uint8_t v___x_4142_; 
v___x_4141_ = 9223372036854775808ULL;
v___x_4142_ = lean_uint64_dec_lt(v___x_4141_, v___y_4100_);
if (v___x_4142_ == 0)
{
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v___y_4102_;
goto v___jp_4017_;
}
else
{
uint64_t v___x_4143_; 
v___x_4143_ = 1ULL;
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v___x_4143_;
goto v___jp_4017_;
}
}
}
else
{
uint64_t v_quotient_4144_; uint64_t v___x_4145_; uint64_t v___x_4146_; uint64_t v___x_4147_; uint64_t v_remainder_4148_; uint64_t v___x_4149_; uint64_t v_half_4150_; uint8_t v___x_4151_; 
v_quotient_4144_ = lean_uint64_shift_right(v___y_4100_, v___x_4136_);
v___x_4145_ = 1ULL;
v___x_4146_ = lean_uint64_shift_left(v___x_4145_, v___x_4136_);
v___x_4147_ = lean_uint64_sub(v___x_4146_, v___x_4145_);
v_remainder_4148_ = lean_uint64_land(v___y_4100_, v___x_4147_);
v___x_4149_ = lean_uint64_sub(v___x_4136_, v___x_4145_);
v_half_4150_ = lean_uint64_shift_left(v___x_4145_, v___x_4149_);
v___x_4151_ = lean_uint64_dec_lt(v_remainder_4148_, v_half_4150_);
if (v___x_4151_ == 0)
{
uint8_t v___x_4152_; 
v___x_4152_ = lean_uint64_dec_lt(v_half_4150_, v_remainder_4148_);
if (v___x_4152_ == 0)
{
uint64_t v___x_4153_; uint8_t v___x_4154_; 
v___x_4153_ = lean_uint64_land(v_quotient_4144_, v___x_4145_);
v___x_4154_ = lean_uint64_dec_eq(v___x_4153_, v___y_4102_);
if (v___x_4154_ == 0)
{
uint64_t v___x_4155_; 
v___x_4155_ = lean_uint64_add(v_quotient_4144_, v___x_4145_);
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v___x_4155_;
goto v___jp_4017_;
}
else
{
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v_quotient_4144_;
goto v___jp_4017_;
}
}
else
{
uint64_t v___x_4156_; 
v___x_4156_ = lean_uint64_add(v_quotient_4144_, v___x_4145_);
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v___x_4156_;
goto v___jp_4017_;
}
}
else
{
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v_quotient_4144_;
goto v___jp_4017_;
}
}
}
else
{
v___y_4018_ = v___y_4097_;
v___y_4019_ = v___y_4101_;
v___y_4020_ = v___y_4102_;
v___y_4021_ = v___y_4100_;
goto v___jp_4017_;
}
}
}
}
v___jp_4157_:
{
uint64_t v___x_4167_; uint64_t v___x_4168_; uint8_t v___x_4169_; 
v___x_4167_ = 1ULL;
v___x_4168_ = lean_uint64_shift_right(v___y_4162_, v___x_4167_);
v___x_4169_ = lean_uint64_dec_eq(v___x_4168_, v___y_4165_);
if (v___x_4169_ == 0)
{
uint64_t v___x_4170_; 
v___x_4170_ = lean_uint64_add(v___y_4166_, v___x_4167_);
v___y_4096_ = v___y_4158_;
v___y_4097_ = v___y_4160_;
v___y_4098_ = v___y_4159_;
v___y_4099_ = v___y_4161_;
v___y_4100_ = v___y_4164_;
v___y_4101_ = v___y_4163_;
v___y_4102_ = v___y_4165_;
v___y_4103_ = v___x_4170_;
goto v___jp_4095_;
}
else
{
v___y_4096_ = v___y_4158_;
v___y_4097_ = v___y_4160_;
v___y_4098_ = v___y_4159_;
v___y_4099_ = v___y_4161_;
v___y_4100_ = v___y_4164_;
v___y_4101_ = v___y_4163_;
v___y_4102_ = v___y_4165_;
v___y_4103_ = v___y_4166_;
goto v___jp_4095_;
}
}
v___jp_4171_:
{
uint64_t v___x_4183_; uint8_t v___x_4184_; 
v___x_4183_ = lean_uint64_shift_right(v___y_4173_, v___y_4181_);
v___x_4184_ = lean_uint64_dec_eq(v___x_4183_, v___y_4180_);
if (v___x_4184_ == 0)
{
uint64_t v___x_4185_; 
v___x_4185_ = lean_uint64_add(v___y_4177_, v___y_4181_);
v___y_4158_ = v___y_4172_;
v___y_4159_ = v___y_4175_;
v___y_4160_ = v___y_4174_;
v___y_4161_ = v___y_4176_;
v___y_4162_ = v___y_4182_;
v___y_4163_ = v___y_4179_;
v___y_4164_ = v___y_4178_;
v___y_4165_ = v___y_4180_;
v___y_4166_ = v___x_4185_;
goto v___jp_4157_;
}
else
{
v___y_4158_ = v___y_4172_;
v___y_4159_ = v___y_4175_;
v___y_4160_ = v___y_4174_;
v___y_4161_ = v___y_4176_;
v___y_4162_ = v___y_4182_;
v___y_4163_ = v___y_4179_;
v___y_4164_ = v___y_4178_;
v___y_4165_ = v___y_4180_;
v___y_4166_ = v___y_4177_;
goto v___jp_4157_;
}
}
v___jp_4186_:
{
uint64_t v___x_4196_; uint64_t v___x_4197_; uint8_t v___x_4198_; 
v___x_4196_ = 2ULL;
v___x_4197_ = lean_uint64_shift_right(v___y_4190_, v___x_4196_);
v___x_4198_ = lean_uint64_dec_eq(v___x_4197_, v___y_4194_);
if (v___x_4198_ == 0)
{
v___y_4172_ = v___y_4187_;
v___y_4173_ = v___y_4190_;
v___y_4174_ = v___y_4189_;
v___y_4175_ = v___y_4188_;
v___y_4176_ = v___y_4191_;
v___y_4177_ = v___y_4195_;
v___y_4178_ = v___y_4193_;
v___y_4179_ = v___y_4192_;
v___y_4180_ = v___y_4194_;
v___y_4181_ = v___x_4196_;
v___y_4182_ = v___x_4197_;
goto v___jp_4171_;
}
else
{
v___y_4172_ = v___y_4187_;
v___y_4173_ = v___y_4190_;
v___y_4174_ = v___y_4189_;
v___y_4175_ = v___y_4188_;
v___y_4176_ = v___y_4191_;
v___y_4177_ = v___y_4195_;
v___y_4178_ = v___y_4193_;
v___y_4179_ = v___y_4192_;
v___y_4180_ = v___y_4194_;
v___y_4181_ = v___x_4196_;
v___y_4182_ = v___y_4190_;
goto v___jp_4171_;
}
}
v___jp_4199_:
{
uint64_t v___x_4211_; uint8_t v___x_4212_; 
v___x_4211_ = lean_uint64_shift_right(v___y_4200_, v___y_4205_);
v___x_4212_ = lean_uint64_dec_eq(v___x_4211_, v___y_4209_);
if (v___x_4212_ == 0)
{
uint64_t v___x_4213_; 
v___x_4213_ = lean_uint64_add(v___y_4208_, v___y_4205_);
v___y_4187_ = v___y_4201_;
v___y_4188_ = v___y_4203_;
v___y_4189_ = v___y_4202_;
v___y_4190_ = v___y_4210_;
v___y_4191_ = v___y_4204_;
v___y_4192_ = v___y_4207_;
v___y_4193_ = v___y_4206_;
v___y_4194_ = v___y_4209_;
v___y_4195_ = v___x_4213_;
goto v___jp_4186_;
}
else
{
v___y_4187_ = v___y_4201_;
v___y_4188_ = v___y_4203_;
v___y_4189_ = v___y_4202_;
v___y_4190_ = v___y_4210_;
v___y_4191_ = v___y_4204_;
v___y_4192_ = v___y_4207_;
v___y_4193_ = v___y_4206_;
v___y_4194_ = v___y_4209_;
v___y_4195_ = v___y_4208_;
goto v___jp_4186_;
}
}
v___jp_4214_:
{
uint64_t v___x_4224_; uint64_t v___x_4225_; uint8_t v___x_4226_; 
v___x_4224_ = 4ULL;
v___x_4225_ = lean_uint64_shift_right(v___y_4215_, v___x_4224_);
v___x_4226_ = lean_uint64_dec_eq(v___x_4225_, v___y_4222_);
if (v___x_4226_ == 0)
{
v___y_4200_ = v___y_4215_;
v___y_4201_ = v___y_4216_;
v___y_4202_ = v___y_4218_;
v___y_4203_ = v___y_4217_;
v___y_4204_ = v___y_4219_;
v___y_4205_ = v___x_4224_;
v___y_4206_ = v___y_4221_;
v___y_4207_ = v___y_4220_;
v___y_4208_ = v___y_4223_;
v___y_4209_ = v___y_4222_;
v___y_4210_ = v___x_4225_;
goto v___jp_4199_;
}
else
{
v___y_4200_ = v___y_4215_;
v___y_4201_ = v___y_4216_;
v___y_4202_ = v___y_4218_;
v___y_4203_ = v___y_4217_;
v___y_4204_ = v___y_4219_;
v___y_4205_ = v___x_4224_;
v___y_4206_ = v___y_4221_;
v___y_4207_ = v___y_4220_;
v___y_4208_ = v___y_4223_;
v___y_4209_ = v___y_4222_;
v___y_4210_ = v___y_4215_;
goto v___jp_4199_;
}
}
v___jp_4227_:
{
uint64_t v___x_4239_; uint8_t v___x_4240_; 
v___x_4239_ = lean_uint64_shift_right(v___y_4237_, v___y_4233_);
v___x_4240_ = lean_uint64_dec_eq(v___x_4239_, v___y_4236_);
if (v___x_4240_ == 0)
{
uint64_t v___x_4241_; 
v___x_4241_ = lean_uint64_add(v___y_4228_, v___y_4233_);
v___y_4215_ = v___y_4238_;
v___y_4216_ = v___y_4229_;
v___y_4217_ = v___y_4231_;
v___y_4218_ = v___y_4230_;
v___y_4219_ = v___y_4232_;
v___y_4220_ = v___y_4235_;
v___y_4221_ = v___y_4234_;
v___y_4222_ = v___y_4236_;
v___y_4223_ = v___x_4241_;
goto v___jp_4214_;
}
else
{
v___y_4215_ = v___y_4238_;
v___y_4216_ = v___y_4229_;
v___y_4217_ = v___y_4231_;
v___y_4218_ = v___y_4230_;
v___y_4219_ = v___y_4232_;
v___y_4220_ = v___y_4235_;
v___y_4221_ = v___y_4234_;
v___y_4222_ = v___y_4236_;
v___y_4223_ = v___y_4228_;
goto v___jp_4214_;
}
}
v___jp_4242_:
{
uint64_t v___x_4252_; uint64_t v___x_4253_; uint8_t v___x_4254_; 
v___x_4252_ = 8ULL;
v___x_4253_ = lean_uint64_shift_right(v___y_4250_, v___x_4252_);
v___x_4254_ = lean_uint64_dec_eq(v___x_4253_, v___y_4249_);
if (v___x_4254_ == 0)
{
v___y_4228_ = v___y_4251_;
v___y_4229_ = v___y_4243_;
v___y_4230_ = v___y_4245_;
v___y_4231_ = v___y_4244_;
v___y_4232_ = v___y_4246_;
v___y_4233_ = v___x_4252_;
v___y_4234_ = v___y_4248_;
v___y_4235_ = v___y_4247_;
v___y_4236_ = v___y_4249_;
v___y_4237_ = v___y_4250_;
v___y_4238_ = v___x_4253_;
goto v___jp_4227_;
}
else
{
v___y_4228_ = v___y_4251_;
v___y_4229_ = v___y_4243_;
v___y_4230_ = v___y_4245_;
v___y_4231_ = v___y_4244_;
v___y_4232_ = v___y_4246_;
v___y_4233_ = v___x_4252_;
v___y_4234_ = v___y_4248_;
v___y_4235_ = v___y_4247_;
v___y_4236_ = v___y_4249_;
v___y_4237_ = v___y_4250_;
v___y_4238_ = v___y_4250_;
goto v___jp_4227_;
}
}
v___jp_4255_:
{
uint64_t v___x_4267_; uint8_t v___x_4268_; 
v___x_4267_ = lean_uint64_shift_right(v___y_4261_, v___y_4256_);
v___x_4268_ = lean_uint64_dec_eq(v___x_4267_, v___y_4265_);
if (v___x_4268_ == 0)
{
uint64_t v___x_4269_; 
v___x_4269_ = lean_uint64_add(v___y_4262_, v___y_4256_);
v___y_4243_ = v___y_4257_;
v___y_4244_ = v___y_4259_;
v___y_4245_ = v___y_4258_;
v___y_4246_ = v___y_4260_;
v___y_4247_ = v___y_4264_;
v___y_4248_ = v___y_4263_;
v___y_4249_ = v___y_4265_;
v___y_4250_ = v___y_4266_;
v___y_4251_ = v___x_4269_;
goto v___jp_4242_;
}
else
{
v___y_4243_ = v___y_4257_;
v___y_4244_ = v___y_4259_;
v___y_4245_ = v___y_4258_;
v___y_4246_ = v___y_4260_;
v___y_4247_ = v___y_4264_;
v___y_4248_ = v___y_4263_;
v___y_4249_ = v___y_4265_;
v___y_4250_ = v___y_4266_;
v___y_4251_ = v___y_4262_;
goto v___jp_4242_;
}
}
v___jp_4270_:
{
uint64_t v___x_4280_; uint64_t v___x_4281_; uint8_t v___x_4282_; 
v___x_4280_ = 16ULL;
v___x_4281_ = lean_uint64_shift_right(v___y_4275_, v___x_4280_);
v___x_4282_ = lean_uint64_dec_eq(v___x_4281_, v___y_4278_);
if (v___x_4282_ == 0)
{
v___y_4256_ = v___x_4280_;
v___y_4257_ = v___y_4271_;
v___y_4258_ = v___y_4273_;
v___y_4259_ = v___y_4272_;
v___y_4260_ = v___y_4274_;
v___y_4261_ = v___y_4275_;
v___y_4262_ = v___y_4279_;
v___y_4263_ = v___y_4277_;
v___y_4264_ = v___y_4276_;
v___y_4265_ = v___y_4278_;
v___y_4266_ = v___x_4281_;
goto v___jp_4255_;
}
else
{
v___y_4256_ = v___x_4280_;
v___y_4257_ = v___y_4271_;
v___y_4258_ = v___y_4273_;
v___y_4259_ = v___y_4272_;
v___y_4260_ = v___y_4274_;
v___y_4261_ = v___y_4275_;
v___y_4262_ = v___y_4279_;
v___y_4263_ = v___y_4277_;
v___y_4264_ = v___y_4276_;
v___y_4265_ = v___y_4278_;
v___y_4266_ = v___y_4275_;
goto v___jp_4255_;
}
}
v___jp_4283_:
{
uint64_t v___x_4293_; uint8_t v___x_4294_; 
v___x_4293_ = lean_uint64_shift_right(v___y_4288_, v___y_4291_);
v___x_4294_ = lean_uint64_dec_eq(v___x_4293_, v___y_4290_);
if (v___x_4294_ == 0)
{
v___y_4271_ = v___y_4284_;
v___y_4272_ = v___y_4286_;
v___y_4273_ = v___y_4285_;
v___y_4274_ = v___y_4287_;
v___y_4275_ = v___y_4292_;
v___y_4276_ = v___y_4289_;
v___y_4277_ = v___y_4288_;
v___y_4278_ = v___y_4290_;
v___y_4279_ = v___y_4291_;
goto v___jp_4270_;
}
else
{
v___y_4271_ = v___y_4284_;
v___y_4272_ = v___y_4286_;
v___y_4273_ = v___y_4285_;
v___y_4274_ = v___y_4287_;
v___y_4275_ = v___y_4292_;
v___y_4276_ = v___y_4289_;
v___y_4277_ = v___y_4288_;
v___y_4278_ = v___y_4290_;
v___y_4279_ = v___y_4290_;
goto v___jp_4270_;
}
}
v___jp_4295_:
{
uint64_t v___x_4304_; uint64_t v___x_4305_; uint8_t v___x_4306_; 
v___x_4304_ = lean_uint64_mul(v___y_4302_, v___y_4301_);
v___x_4305_ = 0ULL;
v___x_4306_ = lean_uint64_dec_eq(v___x_4304_, v___x_4305_);
if (v___x_4306_ == 0)
{
uint64_t v___x_4307_; uint64_t v___x_4308_; uint64_t v___x_4309_; uint8_t v___x_4310_; 
v___x_4307_ = lean_uint64_add(v___y_4299_, v___y_4303_);
v___x_4308_ = 32ULL;
v___x_4309_ = lean_uint64_shift_right(v___x_4304_, v___x_4308_);
v___x_4310_ = lean_uint64_dec_eq(v___x_4309_, v___x_4305_);
if (v___x_4310_ == 0)
{
v___y_4284_ = v___y_4296_;
v___y_4285_ = v___y_4297_;
v___y_4286_ = v___x_4307_;
v___y_4287_ = v___y_4298_;
v___y_4288_ = v___x_4304_;
v___y_4289_ = v___y_4300_;
v___y_4290_ = v___x_4305_;
v___y_4291_ = v___x_4308_;
v___y_4292_ = v___x_4309_;
goto v___jp_4283_;
}
else
{
v___y_4284_ = v___y_4296_;
v___y_4285_ = v___y_4297_;
v___y_4286_ = v___x_4307_;
v___y_4287_ = v___y_4298_;
v___y_4288_ = v___x_4304_;
v___y_4289_ = v___y_4300_;
v___y_4290_ = v___x_4305_;
v___y_4291_ = v___x_4308_;
v___y_4292_ = v___x_4304_;
goto v___jp_4283_;
}
}
else
{
if (v___y_4300_ == 0)
{
uint32_t v___x_4311_; 
v___x_4311_ = 0;
return v___x_4311_;
}
else
{
uint32_t v___x_4312_; 
v___x_4312_ = 2147483648;
return v___x_4312_;
}
}
}
v___jp_4313_:
{
uint64_t v___x_4322_; uint64_t v___x_4323_; uint8_t v___x_4324_; 
v___x_4322_ = lean_uint32_to_uint64(v___y_4317_);
v___x_4323_ = 0ULL;
v___x_4324_ = lean_uint64_dec_eq(v___x_4322_, v___x_4323_);
if (v___x_4324_ == 0)
{
uint64_t v___x_4325_; uint64_t v___x_4326_; 
v___x_4325_ = 1ULL;
v___x_4326_ = lean_uint64_sub(v___x_4322_, v___x_4325_);
v___y_4296_ = v___y_4314_;
v___y_4297_ = v___y_4315_;
v___y_4298_ = v___y_4316_;
v___y_4299_ = v___y_4321_;
v___y_4300_ = v___y_4319_;
v___y_4301_ = v___y_4318_;
v___y_4302_ = v___y_4320_;
v___y_4303_ = v___x_4326_;
goto v___jp_4295_;
}
else
{
v___y_4296_ = v___y_4314_;
v___y_4297_ = v___y_4315_;
v___y_4298_ = v___y_4316_;
v___y_4299_ = v___y_4321_;
v___y_4300_ = v___y_4319_;
v___y_4301_ = v___y_4318_;
v___y_4302_ = v___y_4320_;
v___y_4303_ = v___x_4323_;
goto v___jp_4295_;
}
}
v___jp_4327_:
{
uint64_t v___x_4336_; uint64_t v___x_4337_; uint8_t v___x_4338_; 
v___x_4336_ = lean_uint32_to_uint64(v___y_4332_);
v___x_4337_ = 0ULL;
v___x_4338_ = lean_uint64_dec_eq(v___x_4336_, v___x_4337_);
if (v___x_4338_ == 0)
{
uint64_t v___x_4339_; uint64_t v___x_4340_; 
v___x_4339_ = 1ULL;
v___x_4340_ = lean_uint64_sub(v___x_4336_, v___x_4339_);
v___y_4314_ = v___y_4328_;
v___y_4315_ = v___y_4329_;
v___y_4316_ = v___y_4330_;
v___y_4317_ = v___y_4331_;
v___y_4318_ = v___y_4335_;
v___y_4319_ = v___y_4333_;
v___y_4320_ = v___y_4334_;
v___y_4321_ = v___x_4340_;
goto v___jp_4313_;
}
else
{
v___y_4314_ = v___y_4328_;
v___y_4315_ = v___y_4329_;
v___y_4316_ = v___y_4330_;
v___y_4317_ = v___y_4331_;
v___y_4318_ = v___y_4335_;
v___y_4319_ = v___y_4333_;
v___y_4320_ = v___y_4334_;
v___y_4321_ = v___x_4337_;
goto v___jp_4313_;
}
}
v___jp_4341_:
{
uint32_t v___x_4350_; uint8_t v___x_4351_; 
v___x_4350_ = 0;
v___x_4351_ = lean_uint32_dec_eq(v___y_4346_, v___x_4350_);
if (v___x_4351_ == 0)
{
uint64_t v___x_4352_; uint64_t v___x_4353_; uint64_t v___x_4354_; 
v___x_4352_ = lean_uint32_to_uint64(v___y_4342_);
v___x_4353_ = 8388608ULL;
v___x_4354_ = lean_uint64_lor(v___x_4352_, v___x_4353_);
v___y_4328_ = v___y_4343_;
v___y_4329_ = v___y_4344_;
v___y_4330_ = v___y_4345_;
v___y_4331_ = v___y_4346_;
v___y_4332_ = v___y_4348_;
v___y_4333_ = v___y_4347_;
v___y_4334_ = v___y_4349_;
v___y_4335_ = v___x_4354_;
goto v___jp_4327_;
}
else
{
uint64_t v___x_4355_; 
v___x_4355_ = lean_uint32_to_uint64(v___y_4342_);
v___y_4328_ = v___y_4343_;
v___y_4329_ = v___y_4344_;
v___y_4330_ = v___y_4345_;
v___y_4331_ = v___y_4346_;
v___y_4332_ = v___y_4348_;
v___y_4333_ = v___y_4347_;
v___y_4334_ = v___y_4349_;
v___y_4335_ = v___x_4355_;
goto v___jp_4327_;
}
}
v___jp_4356_:
{
uint32_t v___x_4362_; uint32_t v_xFraction_4363_; uint32_t v_yFraction_4364_; uint32_t v___x_4365_; uint8_t v___x_4366_; 
v___x_4362_ = 8388607;
v_xFraction_4363_ = lean_uint32_land(v_x_4005_, v___x_4362_);
v_yFraction_4364_ = lean_uint32_land(v_y_4006_, v___x_4362_);
v___x_4365_ = 0;
v___x_4366_ = lean_uint32_dec_eq(v___y_4360_, v___x_4365_);
if (v___x_4366_ == 0)
{
uint64_t v___x_4367_; uint64_t v___x_4368_; uint64_t v___x_4369_; 
v___x_4367_ = lean_uint32_to_uint64(v_xFraction_4363_);
v___x_4368_ = 8388608ULL;
v___x_4369_ = lean_uint64_lor(v___x_4367_, v___x_4368_);
v___y_4342_ = v_yFraction_4364_;
v___y_4343_ = v___y_4357_;
v___y_4344_ = v___x_4362_;
v___y_4345_ = v___y_4358_;
v___y_4346_ = v___y_4359_;
v___y_4347_ = v___y_4361_;
v___y_4348_ = v___y_4360_;
v___y_4349_ = v___x_4369_;
goto v___jp_4341_;
}
else
{
uint64_t v___x_4370_; 
v___x_4370_ = lean_uint32_to_uint64(v_xFraction_4363_);
v___y_4342_ = v_yFraction_4364_;
v___y_4343_ = v___y_4357_;
v___y_4344_ = v___x_4362_;
v___y_4345_ = v___y_4358_;
v___y_4346_ = v___y_4359_;
v___y_4347_ = v___y_4361_;
v___y_4348_ = v___y_4360_;
v___y_4349_ = v___x_4370_;
goto v___jp_4341_;
}
}
v___jp_4371_:
{
uint8_t v___x_4376_; 
v___x_4376_ = 1;
v___y_4357_ = v___y_4372_;
v___y_4358_ = v___y_4373_;
v___y_4359_ = v___y_4374_;
v___y_4360_ = v___y_4375_;
v___y_4361_ = v___x_4376_;
goto v___jp_4356_;
}
v___jp_4377_:
{
if (v___y_4378_ == 0)
{
if (v___y_4384_ == 0)
{
v___y_4357_ = v___y_4379_;
v___y_4358_ = v___y_4380_;
v___y_4359_ = v___y_4382_;
v___y_4360_ = v___y_4383_;
v___y_4361_ = v___y_4381_;
goto v___jp_4356_;
}
else
{
v___y_4372_ = v___y_4379_;
v___y_4373_ = v___y_4380_;
v___y_4374_ = v___y_4382_;
v___y_4375_ = v___y_4383_;
goto v___jp_4371_;
}
}
else
{
if (v___y_4384_ == 0)
{
v___y_4372_ = v___y_4379_;
v___y_4373_ = v___y_4380_;
v___y_4374_ = v___y_4382_;
v___y_4375_ = v___y_4383_;
goto v___jp_4371_;
}
else
{
v___y_4357_ = v___y_4379_;
v___y_4358_ = v___y_4380_;
v___y_4359_ = v___y_4382_;
v___y_4360_ = v___y_4383_;
v___y_4361_ = v___y_4381_;
goto v___jp_4356_;
}
}
}
v___jp_4385_:
{
uint32_t v___x_4392_; uint32_t v___x_4393_; uint32_t v___x_4394_; uint8_t v___x_4395_; 
v___x_4392_ = 2147483648;
v___x_4393_ = lean_uint32_land(v_y_4006_, v___x_4392_);
v___x_4394_ = 0;
v___x_4395_ = lean_uint32_dec_eq(v___x_4393_, v___x_4394_);
if (v___x_4395_ == 0)
{
uint8_t v___x_4396_; 
v___x_4396_ = 1;
v___y_4378_ = v___y_4391_;
v___y_4379_ = v___y_4386_;
v___y_4380_ = v___y_4388_;
v___y_4381_ = v___y_4387_;
v___y_4382_ = v___y_4389_;
v___y_4383_ = v___y_4390_;
v___y_4384_ = v___x_4396_;
goto v___jp_4377_;
}
else
{
v___y_4378_ = v___y_4391_;
v___y_4379_ = v___y_4386_;
v___y_4380_ = v___y_4388_;
v___y_4381_ = v___y_4387_;
v___y_4382_ = v___y_4389_;
v___y_4383_ = v___y_4390_;
v___y_4384_ = v___y_4387_;
goto v___jp_4377_;
}
}
v___jp_4397_:
{
if (v___y_4398_ == 0)
{
uint32_t v___x_4399_; uint32_t v___x_4400_; uint32_t v___x_4401_; uint32_t v_xExponent_4402_; uint32_t v___x_4403_; uint32_t v_yExponent_4404_; uint32_t v___x_4405_; uint32_t v___x_4406_; uint32_t v___x_4407_; uint8_t v___x_4408_; 
v___x_4399_ = 23;
v___x_4400_ = lean_uint32_shift_right(v_x_4005_, v___x_4399_);
v___x_4401_ = 255;
v_xExponent_4402_ = lean_uint32_land(v___x_4400_, v___x_4401_);
v___x_4403_ = lean_uint32_shift_right(v_y_4006_, v___x_4399_);
v_yExponent_4404_ = lean_uint32_land(v___x_4403_, v___x_4401_);
v___x_4405_ = 2147483648;
v___x_4406_ = lean_uint32_land(v_x_4005_, v___x_4405_);
v___x_4407_ = 0;
v___x_4408_ = lean_uint32_dec_eq(v___x_4406_, v___x_4407_);
if (v___x_4408_ == 0)
{
uint8_t v___x_4409_; 
v___x_4409_ = 1;
v___y_4386_ = v___x_4399_;
v___y_4387_ = v___y_4398_;
v___y_4388_ = v___x_4401_;
v___y_4389_ = v_yExponent_4404_;
v___y_4390_ = v_xExponent_4402_;
v___y_4391_ = v___x_4409_;
goto v___jp_4385_;
}
else
{
v___y_4386_ = v___x_4399_;
v___y_4387_ = v___y_4398_;
v___y_4388_ = v___x_4401_;
v___y_4389_ = v_yExponent_4404_;
v___y_4390_ = v_xExponent_4402_;
v___y_4391_ = v___y_4398_;
goto v___jp_4385_;
}
}
else
{
lean_object* v___x_4410_; lean_object* v___x_4411_; lean_object* v___x_4412_; lean_object* v___x_4413_; uint32_t v___x_4414_; 
v___x_4410_ = ((lean_object*)(lp_competition_Submission_TunedAdd_add___closed__0));
v___x_4411_ = lean_uint32_to_nat(v_x_4005_);
v___x_4412_ = lean_uint32_to_nat(v_y_4006_);
v___x_4413_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_4410_, v___x_4411_, v___x_4412_);
v___x_4414_ = lean_uint32_of_nat(v___x_4413_);
lean_dec(v___x_4413_);
return v___x_4414_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object* v_x_4421_, lean_object* v_y_4422_){
_start:
{
uint32_t v_x_boxed_4423_; uint32_t v_y_boxed_4424_; uint32_t v_res_4425_; lean_object* v_r_4426_; 
v_x_boxed_4423_ = lean_unbox_uint32(v_x_4421_);
lean_dec(v_x_4421_);
v_y_boxed_4424_ = lean_unbox_uint32(v_y_4422_);
lean_dec(v_y_4422_);
v_res_4425_ = lp_competition_Submission_mul(v_x_boxed_4423_, v_y_boxed_4424_);
v_r_4426_ = lean_box_uint32(v_res_4425_);
return v_r_4426_;
}
}
static lean_object* _init_lp_competition_Submission_sum___redArg___lam__0___boxed__const__1(void){
_start:
{
uint32_t v___x_4427_; lean_object* v___x_4428_; 
v___x_4427_ = 2139095040;
v___x_4428_ = lean_box_uint32(v___x_4427_);
return v___x_4428_;
}
}
static lean_object* _init_lp_competition_Submission_sum___redArg___lam__0___boxed__const__2(void){
_start:
{
uint32_t v___x_4429_; lean_object* v___x_4430_; 
v___x_4429_ = 4286578688;
v___x_4430_ = lean_box_uint32(v___x_4429_);
return v___x_4430_;
}
}
static lean_object* _init_lp_competition_Submission_sum___redArg___lam__0___boxed__const__3(void){
_start:
{
uint32_t v___x_4431_; lean_object* v___x_4432_; 
v___x_4431_ = 0;
v___x_4432_ = lean_box_uint32(v___x_4431_);
return v___x_4432_;
}
}
static lean_object* _init_lp_competition_Submission_sum___redArg___lam__0___boxed__const__4(void){
_start:
{
uint32_t v___x_4433_; lean_object* v___x_4434_; 
v___x_4433_ = 2147483648;
v___x_4434_ = lean_box_uint32(v___x_4433_);
return v___x_4434_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___lam__0(uint8_t v___x_4435_, uint32_t v_x1_4436_, uint32_t v_x2_4437_){
_start:
{
uint32_t v___y_4439_; uint32_t v___y_4440_; uint32_t v___y_4441_; uint32_t v___y_4442_; uint32_t v___y_4443_; lean_object* v___y_4452_; uint32_t v___y_4453_; uint32_t v___y_4454_; uint32_t v___y_4455_; uint32_t v___y_4456_; uint32_t v___y_4461_; lean_object* v___y_4462_; uint64_t v___y_4463_; uint64_t v___y_4464_; uint32_t v___y_4465_; uint64_t v___y_4466_; lean_object* v___y_4476_; uint32_t v___y_4477_; uint64_t v___y_4478_; uint64_t v___y_4479_; uint8_t v___y_4480_; uint32_t v___y_4481_; uint64_t v___y_4482_; uint32_t v___y_4490_; lean_object* v___y_4491_; uint64_t v___y_4492_; uint64_t v___y_4493_; uint32_t v___y_4494_; uint64_t v___y_4495_; uint32_t v___y_4501_; uint32_t v___y_4502_; uint32_t v___y_4508_; uint32_t v___y_4509_; uint32_t v___y_4510_; uint32_t v___y_4511_; uint32_t v___y_4512_; uint32_t v___y_4521_; uint32_t v___y_4522_; lean_object* v___y_4523_; uint32_t v___y_4524_; uint32_t v___y_4525_; uint32_t v___y_4530_; uint64_t v___y_4531_; uint64_t v___y_4532_; uint32_t v___y_4533_; lean_object* v___y_4534_; uint64_t v___y_4535_; uint32_t v___y_4545_; uint64_t v___y_4546_; uint8_t v___y_4547_; uint64_t v___y_4548_; lean_object* v___y_4549_; uint32_t v___y_4550_; uint64_t v___y_4551_; uint32_t v___y_4559_; uint64_t v___y_4560_; uint64_t v___y_4561_; uint32_t v___y_4562_; lean_object* v___y_4563_; uint64_t v___y_4564_; uint32_t v___y_4570_; uint32_t v___y_4571_; uint32_t v___y_4577_; uint64_t v___y_4582_; lean_object* v___y_4583_; uint64_t v___y_4584_; uint32_t v___y_4599_; uint64_t v___y_4600_; lean_object* v___y_4601_; uint64_t v___y_4602_; uint64_t v___y_4603_; lean_object* v___y_4604_; uint32_t v___y_4605_; uint64_t v___y_4606_; uint32_t v___y_4670_; uint64_t v___y_4671_; lean_object* v___y_4672_; uint64_t v___y_4673_; uint64_t v___y_4674_; uint32_t v___y_4675_; lean_object* v___y_4676_; uint64_t v___y_4677_; uint64_t v___y_4678_; uint64_t v___y_4684_; uint32_t v___y_4685_; uint64_t v___y_4686_; uint64_t v___y_4687_; uint64_t v___y_4688_; lean_object* v___y_4689_; uint64_t v___y_4690_; uint64_t v___y_4691_; lean_object* v___y_4692_; uint32_t v___y_4693_; uint64_t v___y_4694_; uint32_t v___y_4699_; uint64_t v___y_4700_; lean_object* v___y_4701_; uint64_t v___y_4702_; uint64_t v___y_4703_; uint64_t v___y_4704_; uint32_t v___y_4705_; lean_object* v___y_4706_; uint64_t v___y_4707_; uint32_t v___y_4712_; uint64_t v___y_4713_; uint64_t v___y_4714_; uint64_t v___y_4715_; lean_object* v___y_4716_; uint64_t v___y_4717_; uint64_t v___y_4718_; uint64_t v___y_4719_; lean_object* v___y_4720_; uint32_t v___y_4721_; uint64_t v___y_4722_; uint32_t v___y_4727_; uint64_t v___y_4728_; uint64_t v___y_4729_; lean_object* v___y_4730_; uint64_t v___y_4731_; uint64_t v___y_4732_; uint32_t v___y_4733_; lean_object* v___y_4734_; uint64_t v___y_4735_; uint64_t v___y_4740_; uint32_t v___y_4741_; uint64_t v___y_4742_; lean_object* v___y_4743_; uint64_t v___y_4744_; uint64_t v___y_4745_; uint64_t v___y_4746_; uint64_t v___y_4747_; lean_object* v___y_4748_; uint32_t v___y_4749_; uint64_t v___y_4750_; uint32_t v___y_4755_; uint64_t v___y_4756_; lean_object* v___y_4757_; uint64_t v___y_4758_; uint64_t v___y_4759_; uint64_t v___y_4760_; uint32_t v___y_4761_; lean_object* v___y_4762_; uint64_t v___y_4763_; uint32_t v___y_4768_; uint64_t v___y_4769_; uint64_t v___y_4770_; lean_object* v___y_4771_; uint64_t v___y_4772_; uint64_t v___y_4773_; uint64_t v___y_4774_; uint64_t v___y_4775_; lean_object* v___y_4776_; uint32_t v___y_4777_; uint64_t v___y_4778_; uint32_t v___y_4783_; uint64_t v___y_4784_; uint64_t v___y_4785_; lean_object* v___y_4786_; uint64_t v___y_4787_; uint64_t v___y_4788_; uint32_t v___y_4789_; lean_object* v___y_4790_; uint64_t v___y_4791_; uint32_t v___y_4796_; uint64_t v___y_4797_; lean_object* v___y_4798_; uint64_t v___y_4799_; uint64_t v___y_4800_; uint64_t v___y_4801_; lean_object* v___y_4802_; uint32_t v___y_4803_; uint64_t v___y_4804_; uint32_t v___y_4809_; uint64_t v___y_4810_; uint32_t v___y_4811_; lean_object* v_fst_4812_; lean_object* v_snd_4813_; uint32_t v___y_4828_; uint64_t v___y_4829_; uint8_t v___y_4830_; uint8_t v___y_4831_; uint64_t v___y_4832_; uint64_t v___y_4833_; uint32_t v___y_4834_; uint8_t v___y_4835_; uint32_t v___y_4847_; uint64_t v___y_4848_; uint8_t v___y_4849_; uint64_t v___y_4850_; uint8_t v___y_4851_; uint64_t v___y_4852_; uint32_t v___y_4853_; uint8_t v___y_4854_; uint32_t v___y_4859_; lean_object* v___y_4864_; uint64_t v___y_4865_; uint64_t v___y_4866_; lean_object* v___y_4881_; uint32_t v___y_4882_; uint64_t v___y_4883_; uint64_t v___y_4884_; uint64_t v___y_4885_; lean_object* v___y_4886_; uint32_t v___y_4887_; uint64_t v___y_4888_; uint32_t v___y_4952_; lean_object* v___y_4953_; uint64_t v___y_4954_; uint64_t v___y_4955_; uint64_t v___y_4956_; uint64_t v___y_4957_; uint32_t v___y_4958_; lean_object* v___y_4959_; uint64_t v___y_4960_; lean_object* v___y_4966_; uint32_t v___y_4967_; uint64_t v___y_4968_; uint64_t v___y_4969_; uint64_t v___y_4970_; uint64_t v___y_4971_; uint64_t v___y_4972_; uint64_t v___y_4973_; lean_object* v___y_4974_; uint32_t v___y_4975_; uint64_t v___y_4976_; uint32_t v___y_4981_; lean_object* v___y_4982_; uint64_t v___y_4983_; uint64_t v___y_4984_; uint64_t v___y_4985_; uint64_t v___y_4986_; uint32_t v___y_4987_; lean_object* v___y_4988_; uint64_t v___y_4989_; lean_object* v___y_4994_; uint32_t v___y_4995_; uint64_t v___y_4996_; uint64_t v___y_4997_; uint64_t v___y_4998_; uint64_t v___y_4999_; uint64_t v___y_5000_; uint64_t v___y_5001_; lean_object* v___y_5002_; uint32_t v___y_5003_; uint64_t v___y_5004_; uint32_t v___y_5009_; lean_object* v___y_5010_; uint64_t v___y_5011_; uint64_t v___y_5012_; uint64_t v___y_5013_; uint64_t v___y_5014_; uint32_t v___y_5015_; lean_object* v___y_5016_; uint64_t v___y_5017_; lean_object* v___y_5022_; uint32_t v___y_5023_; uint64_t v___y_5024_; uint64_t v___y_5025_; uint64_t v___y_5026_; uint64_t v___y_5027_; uint64_t v___y_5028_; uint64_t v___y_5029_; lean_object* v___y_5030_; uint32_t v___y_5031_; uint64_t v___y_5032_; uint32_t v___y_5037_; lean_object* v___y_5038_; uint64_t v___y_5039_; uint64_t v___y_5040_; uint64_t v___y_5041_; uint64_t v___y_5042_; uint32_t v___y_5043_; lean_object* v___y_5044_; uint64_t v___y_5045_; lean_object* v___y_5050_; uint32_t v___y_5051_; uint64_t v___y_5052_; uint64_t v___y_5053_; uint64_t v___y_5054_; uint64_t v___y_5055_; uint64_t v___y_5056_; uint64_t v___y_5057_; lean_object* v___y_5058_; uint32_t v___y_5059_; uint64_t v___y_5060_; uint32_t v___y_5065_; lean_object* v___y_5066_; uint64_t v___y_5067_; uint64_t v___y_5068_; uint64_t v___y_5069_; uint64_t v___y_5070_; uint32_t v___y_5071_; lean_object* v___y_5072_; uint64_t v___y_5073_; lean_object* v___y_5078_; uint32_t v___y_5079_; uint64_t v___y_5080_; uint64_t v___y_5081_; uint64_t v___y_5082_; uint64_t v___y_5083_; lean_object* v___y_5084_; uint32_t v___y_5085_; uint64_t v___y_5086_; uint32_t v___y_5091_; uint64_t v___y_5092_; uint32_t v___y_5093_; lean_object* v_fst_5094_; lean_object* v_snd_5095_; uint32_t v___y_5110_; uint8_t v___y_5111_; uint64_t v___y_5112_; uint8_t v___y_5113_; uint64_t v___y_5114_; uint64_t v___y_5115_; uint32_t v___y_5116_; uint8_t v___y_5117_; uint32_t v___y_5129_; uint8_t v___y_5130_; uint8_t v___y_5131_; uint64_t v___y_5132_; uint64_t v___y_5133_; uint64_t v___y_5134_; uint32_t v___y_5135_; uint8_t v___y_5136_; uint32_t v___y_5141_; uint8_t v___y_5142_; uint8_t v___y_5143_; uint64_t v___y_5144_; uint64_t v___y_5145_; uint64_t v___y_5146_; uint32_t v___y_5147_; uint64_t v___y_5148_; uint32_t v___y_5161_; uint8_t v___y_5162_; uint64_t v___y_5163_; uint8_t v___y_5164_; uint32_t v___y_5165_; uint64_t v___y_5166_; uint32_t v___y_5167_; uint64_t v___y_5168_; uint32_t v___y_5175_; uint8_t v___y_5176_; uint32_t v___y_5177_; uint8_t v___y_5178_; uint64_t v___y_5179_; uint32_t v___y_5180_; uint32_t v___y_5181_; uint64_t v___y_5182_; uint32_t v___y_5189_; uint8_t v___y_5190_; uint8_t v___y_5191_; uint32_t v___y_5192_; uint32_t v___y_5193_; uint32_t v___y_5194_; uint64_t v___y_5195_; uint32_t v___y_5205_; uint32_t v___y_5206_; uint8_t v___y_5207_; uint32_t v___y_5208_; uint32_t v___y_5209_; uint8_t v___y_5210_; uint32_t v___y_5220_; uint8_t v___y_5221_; uint32_t v___y_5222_; uint32_t v___y_5223_; uint32_t v___y_5224_; uint8_t v___y_5225_; uint8_t v___y_5231_; uint32_t v___x_5248_; uint32_t v___x_5249_; uint32_t v___x_5250_; uint32_t v___x_5251_; uint8_t v___x_5252_; 
v___x_5248_ = 4278190079;
v___x_5249_ = 1;
v___x_5250_ = lean_uint32_shift_left(v_x1_4436_, v___x_5249_);
v___x_5251_ = lean_uint32_sub(v___x_5250_, v___x_5249_);
v___x_5252_ = lean_uint32_dec_le(v___x_5248_, v___x_5251_);
if (v___x_5252_ == 0)
{
uint32_t v___x_5253_; uint32_t v___x_5254_; uint8_t v___x_5255_; 
v___x_5253_ = lean_uint32_shift_left(v_x2_4437_, v___x_5249_);
v___x_5254_ = lean_uint32_sub(v___x_5253_, v___x_5249_);
v___x_5255_ = lean_uint32_dec_le(v___x_5248_, v___x_5254_);
v___y_5231_ = v___x_5255_;
goto v___jp_5230_;
}
else
{
v___y_5231_ = v___x_5252_;
goto v___jp_5230_;
}
v___jp_4438_:
{
uint32_t v___x_4444_; uint32_t v___x_4445_; uint32_t v___x_4446_; uint32_t v___x_4447_; uint32_t v___x_4448_; uint32_t v___x_4449_; lean_object* v___x_4450_; 
v___x_4444_ = lean_uint32_land(v___y_4441_, v___y_4442_);
v___x_4445_ = lean_uint32_shift_left(v___x_4444_, v___y_4439_);
v___x_4446_ = lean_uint32_lor(v___y_4443_, v___x_4445_);
v___x_4447_ = 8388607;
v___x_4448_ = lean_uint32_land(v___y_4440_, v___x_4447_);
v___x_4449_ = lean_uint32_lor(v___x_4446_, v___x_4448_);
v___x_4450_ = lean_box_uint32(v___x_4449_);
return v___x_4450_;
}
v___jp_4451_:
{
uint8_t v___x_4457_; 
v___x_4457_ = lean_unbox(v___y_4452_);
lean_dec(v___y_4452_);
if (v___x_4457_ == 0)
{
uint32_t v___x_4458_; 
v___x_4458_ = 0;
v___y_4439_ = v___y_4453_;
v___y_4440_ = v___y_4456_;
v___y_4441_ = v___y_4454_;
v___y_4442_ = v___y_4455_;
v___y_4443_ = v___x_4458_;
goto v___jp_4438_;
}
else
{
uint32_t v___x_4459_; 
v___x_4459_ = 2147483648;
v___y_4439_ = v___y_4453_;
v___y_4440_ = v___y_4456_;
v___y_4441_ = v___y_4454_;
v___y_4442_ = v___y_4455_;
v___y_4443_ = v___x_4459_;
goto v___jp_4438_;
}
}
v___jp_4460_:
{
uint64_t v___x_4467_; uint64_t v_encodedExponent_4468_; uint32_t v___x_4469_; uint64_t v___x_4470_; uint8_t v___x_4471_; 
v___x_4467_ = 171ULL;
v_encodedExponent_4468_ = lean_uint64_sub(v___y_4463_, v___x_4467_);
v___x_4469_ = lean_uint64_to_uint32(v_encodedExponent_4468_);
v___x_4470_ = 8388608ULL;
v___x_4471_ = lean_uint64_dec_lt(v___y_4466_, v___x_4470_);
if (v___x_4471_ == 0)
{
uint64_t v___x_4472_; uint32_t v___x_4473_; 
v___x_4472_ = lean_uint64_sub(v___y_4466_, v___x_4470_);
v___x_4473_ = lean_uint64_to_uint32(v___x_4472_);
v___y_4452_ = v___y_4462_;
v___y_4453_ = v___y_4461_;
v___y_4454_ = v___x_4469_;
v___y_4455_ = v___y_4465_;
v___y_4456_ = v___x_4473_;
goto v___jp_4451_;
}
else
{
uint32_t v___x_4474_; 
v___x_4474_ = lean_uint64_to_uint32(v___y_4464_);
v___y_4452_ = v___y_4462_;
v___y_4453_ = v___y_4461_;
v___y_4454_ = v___x_4469_;
v___y_4455_ = v___y_4465_;
v___y_4456_ = v___x_4474_;
goto v___jp_4451_;
}
}
v___jp_4475_:
{
uint64_t v___x_4483_; uint8_t v___x_4484_; 
v___x_4483_ = 425ULL;
v___x_4484_ = lean_uint64_dec_lt(v___x_4483_, v___y_4482_);
if (v___x_4484_ == 0)
{
if (v___y_4480_ == 0)
{
v___y_4461_ = v___y_4477_;
v___y_4462_ = v___y_4476_;
v___y_4463_ = v___y_4482_;
v___y_4464_ = v___y_4479_;
v___y_4465_ = v___y_4481_;
v___y_4466_ = v___y_4478_;
goto v___jp_4460_;
}
else
{
uint64_t v___x_4485_; 
v___x_4485_ = 8388608ULL;
v___y_4461_ = v___y_4477_;
v___y_4462_ = v___y_4476_;
v___y_4463_ = v___y_4482_;
v___y_4464_ = v___y_4479_;
v___y_4465_ = v___y_4481_;
v___y_4466_ = v___x_4485_;
goto v___jp_4460_;
}
}
else
{
uint8_t v___x_4486_; 
v___x_4486_ = lean_unbox(v___y_4476_);
lean_dec(v___y_4476_);
if (v___x_4486_ == 0)
{
lean_object* v___x_4487_; 
v___x_4487_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__1;
return v___x_4487_;
}
else
{
lean_object* v___x_4488_; 
v___x_4488_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__2;
return v___x_4488_;
}
}
}
v___jp_4489_:
{
uint64_t v___x_4496_; uint8_t v_carry_4497_; 
v___x_4496_ = 16777216ULL;
v_carry_4497_ = lean_uint64_dec_eq(v___y_4495_, v___x_4496_);
if (v_carry_4497_ == 0)
{
v___y_4476_ = v___y_4491_;
v___y_4477_ = v___y_4490_;
v___y_4478_ = v___y_4495_;
v___y_4479_ = v___y_4493_;
v___y_4480_ = v_carry_4497_;
v___y_4481_ = v___y_4494_;
v___y_4482_ = v___y_4492_;
goto v___jp_4475_;
}
else
{
uint64_t v___x_4498_; uint64_t v___x_4499_; 
v___x_4498_ = 1ULL;
v___x_4499_ = lean_uint64_add(v___y_4492_, v___x_4498_);
v___y_4476_ = v___y_4491_;
v___y_4477_ = v___y_4490_;
v___y_4478_ = v___y_4495_;
v___y_4479_ = v___y_4493_;
v___y_4480_ = v_carry_4497_;
v___y_4481_ = v___y_4494_;
v___y_4482_ = v___x_4499_;
goto v___jp_4475_;
}
}
v___jp_4500_:
{
uint32_t v___x_4503_; uint32_t v___x_4504_; uint32_t v___x_4505_; lean_object* v___x_4506_; 
v___x_4503_ = 8388607;
v___x_4504_ = lean_uint32_land(v___y_4501_, v___x_4503_);
v___x_4505_ = lean_uint32_lor(v___y_4502_, v___x_4504_);
v___x_4506_ = lean_box_uint32(v___x_4505_);
return v___x_4506_;
}
v___jp_4507_:
{
uint32_t v___x_4513_; uint32_t v___x_4514_; uint32_t v___x_4515_; uint32_t v___x_4516_; uint32_t v___x_4517_; uint32_t v___x_4518_; lean_object* v___x_4519_; 
v___x_4513_ = lean_uint32_land(v___y_4510_, v___y_4511_);
v___x_4514_ = lean_uint32_shift_left(v___x_4513_, v___y_4508_);
v___x_4515_ = lean_uint32_lor(v___y_4512_, v___x_4514_);
v___x_4516_ = 8388607;
v___x_4517_ = lean_uint32_land(v___y_4509_, v___x_4516_);
v___x_4518_ = lean_uint32_lor(v___x_4515_, v___x_4517_);
v___x_4519_ = lean_box_uint32(v___x_4518_);
return v___x_4519_;
}
v___jp_4520_:
{
uint8_t v___x_4526_; 
v___x_4526_ = lean_unbox(v___y_4523_);
lean_dec(v___y_4523_);
if (v___x_4526_ == 0)
{
uint32_t v___x_4527_; 
v___x_4527_ = 0;
v___y_4508_ = v___y_4521_;
v___y_4509_ = v___y_4525_;
v___y_4510_ = v___y_4522_;
v___y_4511_ = v___y_4524_;
v___y_4512_ = v___x_4527_;
goto v___jp_4507_;
}
else
{
uint32_t v___x_4528_; 
v___x_4528_ = 2147483648;
v___y_4508_ = v___y_4521_;
v___y_4509_ = v___y_4525_;
v___y_4510_ = v___y_4522_;
v___y_4511_ = v___y_4524_;
v___y_4512_ = v___x_4528_;
goto v___jp_4507_;
}
}
v___jp_4529_:
{
uint64_t v___x_4536_; uint64_t v_encodedExponent_4537_; uint32_t v___x_4538_; uint64_t v___x_4539_; uint8_t v___x_4540_; 
v___x_4536_ = 171ULL;
v_encodedExponent_4537_ = lean_uint64_sub(v___y_4532_, v___x_4536_);
v___x_4538_ = lean_uint64_to_uint32(v_encodedExponent_4537_);
v___x_4539_ = 8388608ULL;
v___x_4540_ = lean_uint64_dec_lt(v___y_4535_, v___x_4539_);
if (v___x_4540_ == 0)
{
uint64_t v___x_4541_; uint32_t v___x_4542_; 
v___x_4541_ = lean_uint64_sub(v___y_4535_, v___x_4539_);
v___x_4542_ = lean_uint64_to_uint32(v___x_4541_);
v___y_4521_ = v___y_4530_;
v___y_4522_ = v___x_4538_;
v___y_4523_ = v___y_4534_;
v___y_4524_ = v___y_4533_;
v___y_4525_ = v___x_4542_;
goto v___jp_4520_;
}
else
{
uint32_t v___x_4543_; 
v___x_4543_ = lean_uint64_to_uint32(v___y_4531_);
v___y_4521_ = v___y_4530_;
v___y_4522_ = v___x_4538_;
v___y_4523_ = v___y_4534_;
v___y_4524_ = v___y_4533_;
v___y_4525_ = v___x_4543_;
goto v___jp_4520_;
}
}
v___jp_4544_:
{
uint64_t v___x_4552_; uint8_t v___x_4553_; 
v___x_4552_ = 425ULL;
v___x_4553_ = lean_uint64_dec_lt(v___x_4552_, v___y_4551_);
if (v___x_4553_ == 0)
{
if (v___y_4547_ == 0)
{
v___y_4530_ = v___y_4545_;
v___y_4531_ = v___y_4548_;
v___y_4532_ = v___y_4551_;
v___y_4533_ = v___y_4550_;
v___y_4534_ = v___y_4549_;
v___y_4535_ = v___y_4546_;
goto v___jp_4529_;
}
else
{
uint64_t v___x_4554_; 
v___x_4554_ = 8388608ULL;
v___y_4530_ = v___y_4545_;
v___y_4531_ = v___y_4548_;
v___y_4532_ = v___y_4551_;
v___y_4533_ = v___y_4550_;
v___y_4534_ = v___y_4549_;
v___y_4535_ = v___x_4554_;
goto v___jp_4529_;
}
}
else
{
uint8_t v___x_4555_; 
v___x_4555_ = lean_unbox(v___y_4549_);
lean_dec(v___y_4549_);
if (v___x_4555_ == 0)
{
lean_object* v___x_4556_; 
v___x_4556_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__1;
return v___x_4556_;
}
else
{
lean_object* v___x_4557_; 
v___x_4557_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__2;
return v___x_4557_;
}
}
}
v___jp_4558_:
{
uint64_t v___x_4565_; uint8_t v_carry_4566_; 
v___x_4565_ = 16777216ULL;
v_carry_4566_ = lean_uint64_dec_eq(v___y_4564_, v___x_4565_);
if (v_carry_4566_ == 0)
{
v___y_4545_ = v___y_4559_;
v___y_4546_ = v___y_4564_;
v___y_4547_ = v_carry_4566_;
v___y_4548_ = v___y_4560_;
v___y_4549_ = v___y_4563_;
v___y_4550_ = v___y_4562_;
v___y_4551_ = v___y_4561_;
goto v___jp_4544_;
}
else
{
uint64_t v___x_4567_; uint64_t v___x_4568_; 
v___x_4567_ = 1ULL;
v___x_4568_ = lean_uint64_add(v___y_4561_, v___x_4567_);
v___y_4545_ = v___y_4559_;
v___y_4546_ = v___y_4564_;
v___y_4547_ = v_carry_4566_;
v___y_4548_ = v___y_4560_;
v___y_4549_ = v___y_4563_;
v___y_4550_ = v___y_4562_;
v___y_4551_ = v___x_4568_;
goto v___jp_4544_;
}
}
v___jp_4569_:
{
uint32_t v___x_4572_; uint32_t v___x_4573_; uint32_t v___x_4574_; lean_object* v___x_4575_; 
v___x_4572_ = 8388607;
v___x_4573_ = lean_uint32_land(v___y_4570_, v___x_4572_);
v___x_4574_ = lean_uint32_lor(v___y_4571_, v___x_4573_);
v___x_4575_ = lean_box_uint32(v___x_4574_);
return v___x_4575_;
}
v___jp_4576_:
{
uint32_t v___x_4578_; uint32_t v___x_4579_; lean_object* v___x_4580_; 
v___x_4578_ = 8388608;
v___x_4579_ = lean_uint32_lor(v___y_4577_, v___x_4578_);
v___x_4580_ = lean_box_uint32(v___x_4579_);
return v___x_4580_;
}
v___jp_4581_:
{
uint8_t v___x_4585_; 
v___x_4585_ = lean_uint64_dec_eq(v___y_4584_, v___y_4582_);
if (v___x_4585_ == 0)
{
uint64_t v___x_4586_; uint8_t v___x_4587_; 
v___x_4586_ = 8388608ULL;
v___x_4587_ = lean_uint64_dec_eq(v___y_4584_, v___x_4586_);
if (v___x_4587_ == 0)
{
uint32_t v___x_4588_; uint8_t v___x_4589_; 
v___x_4588_ = lean_uint64_to_uint32(v___y_4584_);
v___x_4589_ = lean_unbox(v___y_4583_);
lean_dec(v___y_4583_);
if (v___x_4589_ == 0)
{
uint32_t v___x_4590_; 
v___x_4590_ = 0;
v___y_4570_ = v___x_4588_;
v___y_4571_ = v___x_4590_;
goto v___jp_4569_;
}
else
{
uint32_t v___x_4591_; 
v___x_4591_ = 2147483648;
v___y_4570_ = v___x_4588_;
v___y_4571_ = v___x_4591_;
goto v___jp_4569_;
}
}
else
{
uint8_t v___x_4592_; 
v___x_4592_ = lean_unbox(v___y_4583_);
lean_dec(v___y_4583_);
if (v___x_4592_ == 0)
{
uint32_t v___x_4593_; 
v___x_4593_ = 0;
v___y_4577_ = v___x_4593_;
goto v___jp_4576_;
}
else
{
uint32_t v___x_4594_; 
v___x_4594_ = 2147483648;
v___y_4577_ = v___x_4594_;
goto v___jp_4576_;
}
}
}
else
{
uint8_t v___x_4595_; 
v___x_4595_ = lean_unbox(v___y_4583_);
lean_dec(v___y_4583_);
if (v___x_4595_ == 0)
{
lean_object* v___x_4596_; 
v___x_4596_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
return v___x_4596_;
}
else
{
lean_object* v___x_4597_; 
v___x_4597_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
return v___x_4597_;
}
}
}
v___jp_4598_:
{
uint64_t v_position_4607_; uint64_t v___x_4608_; uint8_t v___x_4609_; 
v_position_4607_ = lean_uint64_add(v___y_4606_, v___y_4600_);
v___x_4608_ = 172ULL;
v___x_4609_ = lean_uint64_dec_lt(v_position_4607_, v___x_4608_);
if (v___x_4609_ == 0)
{
uint64_t v___x_4610_; uint8_t v___x_4611_; 
v___x_4610_ = 23ULL;
v___x_4611_ = lean_uint64_dec_lt(v___y_4606_, v___x_4610_);
if (v___x_4611_ == 0)
{
uint64_t v___x_4612_; uint8_t v___x_4613_; 
v___x_4612_ = lean_uint64_sub(v___y_4606_, v___x_4610_);
v___x_4613_ = lean_uint64_dec_eq(v___x_4612_, v___y_4603_);
if (v___x_4613_ == 0)
{
uint64_t v___x_4614_; uint8_t v___x_4615_; 
v___x_4614_ = 64ULL;
v___x_4615_ = lean_uint64_dec_lt(v___x_4612_, v___x_4614_);
if (v___x_4615_ == 0)
{
uint8_t v___x_4616_; 
v___x_4616_ = lean_uint64_dec_eq(v___x_4612_, v___x_4614_);
if (v___x_4616_ == 0)
{
lean_dec(v___y_4601_);
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v___y_4603_;
goto v___jp_4558_;
}
else
{
uint64_t v___x_4617_; uint64_t v___x_4618_; uint8_t v___x_4619_; 
v___x_4617_ = 9223372036854775808ULL;
v___x_4618_ = lean_unbox_uint64(v___y_4601_);
lean_dec(v___y_4601_);
v___x_4619_ = lean_uint64_dec_lt(v___x_4617_, v___x_4618_);
if (v___x_4619_ == 0)
{
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v___y_4603_;
goto v___jp_4558_;
}
else
{
uint64_t v___x_4620_; 
v___x_4620_ = 1ULL;
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v___x_4620_;
goto v___jp_4558_;
}
}
}
else
{
uint64_t v___x_4621_; uint64_t v_quotient_4622_; uint64_t v___x_4623_; uint64_t v___x_4624_; uint64_t v___x_4625_; uint64_t v___x_4626_; uint64_t v_remainder_4627_; uint64_t v___x_4628_; uint64_t v_half_4629_; uint8_t v___x_4630_; 
v___x_4621_ = lean_unbox_uint64(v___y_4601_);
v_quotient_4622_ = lean_uint64_shift_right(v___x_4621_, v___x_4612_);
v___x_4623_ = 1ULL;
v___x_4624_ = lean_uint64_shift_left(v___x_4623_, v___x_4612_);
v___x_4625_ = lean_uint64_sub(v___x_4624_, v___x_4623_);
v___x_4626_ = lean_unbox_uint64(v___y_4601_);
lean_dec(v___y_4601_);
v_remainder_4627_ = lean_uint64_land(v___x_4626_, v___x_4625_);
v___x_4628_ = lean_uint64_sub(v___x_4612_, v___x_4623_);
v_half_4629_ = lean_uint64_shift_left(v___x_4623_, v___x_4628_);
v___x_4630_ = lean_uint64_dec_lt(v_remainder_4627_, v_half_4629_);
if (v___x_4630_ == 0)
{
uint8_t v___x_4631_; 
v___x_4631_ = lean_uint64_dec_lt(v_half_4629_, v_remainder_4627_);
if (v___x_4631_ == 0)
{
uint64_t v___x_4632_; uint8_t v___x_4633_; 
v___x_4632_ = lean_uint64_land(v_quotient_4622_, v___x_4623_);
v___x_4633_ = lean_uint64_dec_eq(v___x_4632_, v___y_4603_);
if (v___x_4633_ == 0)
{
uint64_t v___x_4634_; 
v___x_4634_ = lean_uint64_add(v_quotient_4622_, v___x_4623_);
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v___x_4634_;
goto v___jp_4558_;
}
else
{
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v_quotient_4622_;
goto v___jp_4558_;
}
}
else
{
uint64_t v___x_4635_; 
v___x_4635_ = lean_uint64_add(v_quotient_4622_, v___x_4623_);
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v___x_4635_;
goto v___jp_4558_;
}
}
else
{
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v_quotient_4622_;
goto v___jp_4558_;
}
}
}
else
{
uint64_t v___x_4636_; 
v___x_4636_ = lean_unbox_uint64(v___y_4601_);
lean_dec(v___y_4601_);
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v___x_4636_;
goto v___jp_4558_;
}
}
else
{
uint64_t v___x_4637_; uint64_t v___x_4638_; uint64_t v___x_4639_; 
v___x_4637_ = lean_uint64_sub(v___x_4610_, v___y_4606_);
v___x_4638_ = lean_unbox_uint64(v___y_4601_);
lean_dec(v___y_4601_);
v___x_4639_ = lean_uint64_shift_left(v___x_4638_, v___x_4637_);
v___y_4559_ = v___y_4599_;
v___y_4560_ = v___y_4603_;
v___y_4561_ = v_position_4607_;
v___y_4562_ = v___y_4605_;
v___y_4563_ = v___y_4604_;
v___y_4564_ = v___x_4639_;
goto v___jp_4558_;
}
}
else
{
uint8_t v___x_4640_; 
v___x_4640_ = lean_uint64_dec_lt(v___y_4600_, v___y_4602_);
if (v___x_4640_ == 0)
{
uint64_t v___x_4641_; uint64_t v___x_4642_; uint64_t v___x_4643_; 
v___x_4641_ = lean_uint64_sub(v___y_4600_, v___y_4602_);
v___x_4642_ = lean_unbox_uint64(v___y_4601_);
lean_dec(v___y_4601_);
v___x_4643_ = lean_uint64_shift_left(v___x_4642_, v___x_4641_);
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v___x_4643_;
goto v___jp_4581_;
}
else
{
uint64_t v___x_4644_; uint8_t v___x_4645_; 
v___x_4644_ = lean_uint64_sub(v___y_4602_, v___y_4600_);
v___x_4645_ = lean_uint64_dec_eq(v___x_4644_, v___y_4603_);
if (v___x_4645_ == 0)
{
uint64_t v___x_4646_; uint8_t v___x_4647_; 
v___x_4646_ = 64ULL;
v___x_4647_ = lean_uint64_dec_lt(v___x_4644_, v___x_4646_);
if (v___x_4647_ == 0)
{
uint8_t v___x_4648_; 
v___x_4648_ = lean_uint64_dec_eq(v___x_4644_, v___x_4646_);
if (v___x_4648_ == 0)
{
lean_dec(v___y_4601_);
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v___y_4603_;
goto v___jp_4581_;
}
else
{
uint64_t v___x_4649_; uint64_t v___x_4650_; uint8_t v___x_4651_; 
v___x_4649_ = 9223372036854775808ULL;
v___x_4650_ = lean_unbox_uint64(v___y_4601_);
lean_dec(v___y_4601_);
v___x_4651_ = lean_uint64_dec_lt(v___x_4649_, v___x_4650_);
if (v___x_4651_ == 0)
{
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v___y_4603_;
goto v___jp_4581_;
}
else
{
uint64_t v___x_4652_; 
v___x_4652_ = 1ULL;
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v___x_4652_;
goto v___jp_4581_;
}
}
}
else
{
uint64_t v___x_4653_; uint64_t v_quotient_4654_; uint64_t v___x_4655_; uint64_t v___x_4656_; uint64_t v___x_4657_; uint64_t v___x_4658_; uint64_t v_remainder_4659_; uint64_t v___x_4660_; uint64_t v_half_4661_; uint8_t v___x_4662_; 
v___x_4653_ = lean_unbox_uint64(v___y_4601_);
v_quotient_4654_ = lean_uint64_shift_right(v___x_4653_, v___x_4644_);
v___x_4655_ = 1ULL;
v___x_4656_ = lean_uint64_shift_left(v___x_4655_, v___x_4644_);
v___x_4657_ = lean_uint64_sub(v___x_4656_, v___x_4655_);
v___x_4658_ = lean_unbox_uint64(v___y_4601_);
lean_dec(v___y_4601_);
v_remainder_4659_ = lean_uint64_land(v___x_4658_, v___x_4657_);
v___x_4660_ = lean_uint64_sub(v___x_4644_, v___x_4655_);
v_half_4661_ = lean_uint64_shift_left(v___x_4655_, v___x_4660_);
v___x_4662_ = lean_uint64_dec_lt(v_remainder_4659_, v_half_4661_);
if (v___x_4662_ == 0)
{
uint8_t v___x_4663_; 
v___x_4663_ = lean_uint64_dec_lt(v_half_4661_, v_remainder_4659_);
if (v___x_4663_ == 0)
{
uint64_t v___x_4664_; uint8_t v___x_4665_; 
v___x_4664_ = lean_uint64_land(v_quotient_4654_, v___x_4655_);
v___x_4665_ = lean_uint64_dec_eq(v___x_4664_, v___y_4603_);
if (v___x_4665_ == 0)
{
uint64_t v___x_4666_; 
v___x_4666_ = lean_uint64_add(v_quotient_4654_, v___x_4655_);
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v___x_4666_;
goto v___jp_4581_;
}
else
{
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v_quotient_4654_;
goto v___jp_4581_;
}
}
else
{
uint64_t v___x_4667_; 
v___x_4667_ = lean_uint64_add(v_quotient_4654_, v___x_4655_);
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v___x_4667_;
goto v___jp_4581_;
}
}
else
{
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v_quotient_4654_;
goto v___jp_4581_;
}
}
}
else
{
uint64_t v___x_4668_; 
v___x_4668_ = lean_unbox_uint64(v___y_4601_);
lean_dec(v___y_4601_);
v___y_4582_ = v___y_4603_;
v___y_4583_ = v___y_4604_;
v___y_4584_ = v___x_4668_;
goto v___jp_4581_;
}
}
}
}
v___jp_4669_:
{
uint64_t v___x_4679_; uint64_t v___x_4680_; uint8_t v___x_4681_; 
v___x_4679_ = 1ULL;
v___x_4680_ = lean_uint64_shift_right(v___y_4677_, v___x_4679_);
v___x_4681_ = lean_uint64_dec_eq(v___x_4680_, v___y_4674_);
if (v___x_4681_ == 0)
{
uint64_t v___x_4682_; 
v___x_4682_ = lean_uint64_add(v___y_4678_, v___x_4679_);
v___y_4599_ = v___y_4670_;
v___y_4600_ = v___y_4671_;
v___y_4601_ = v___y_4672_;
v___y_4602_ = v___y_4673_;
v___y_4603_ = v___y_4674_;
v___y_4604_ = v___y_4676_;
v___y_4605_ = v___y_4675_;
v___y_4606_ = v___x_4682_;
goto v___jp_4598_;
}
else
{
v___y_4599_ = v___y_4670_;
v___y_4600_ = v___y_4671_;
v___y_4601_ = v___y_4672_;
v___y_4602_ = v___y_4673_;
v___y_4603_ = v___y_4674_;
v___y_4604_ = v___y_4676_;
v___y_4605_ = v___y_4675_;
v___y_4606_ = v___y_4678_;
goto v___jp_4598_;
}
}
v___jp_4683_:
{
uint64_t v___x_4695_; uint8_t v___x_4696_; 
v___x_4695_ = lean_uint64_shift_right(v___y_4688_, v___y_4684_);
v___x_4696_ = lean_uint64_dec_eq(v___x_4695_, v___y_4690_);
if (v___x_4696_ == 0)
{
uint64_t v___x_4697_; 
v___x_4697_ = lean_uint64_add(v___y_4687_, v___y_4684_);
v___y_4670_ = v___y_4685_;
v___y_4671_ = v___y_4686_;
v___y_4672_ = v___y_4689_;
v___y_4673_ = v___y_4691_;
v___y_4674_ = v___y_4690_;
v___y_4675_ = v___y_4693_;
v___y_4676_ = v___y_4692_;
v___y_4677_ = v___y_4694_;
v___y_4678_ = v___x_4697_;
goto v___jp_4669_;
}
else
{
v___y_4670_ = v___y_4685_;
v___y_4671_ = v___y_4686_;
v___y_4672_ = v___y_4689_;
v___y_4673_ = v___y_4691_;
v___y_4674_ = v___y_4690_;
v___y_4675_ = v___y_4693_;
v___y_4676_ = v___y_4692_;
v___y_4677_ = v___y_4694_;
v___y_4678_ = v___y_4687_;
goto v___jp_4669_;
}
}
v___jp_4698_:
{
uint64_t v___x_4708_; uint64_t v___x_4709_; uint8_t v___x_4710_; 
v___x_4708_ = 2ULL;
v___x_4709_ = lean_uint64_shift_right(v___y_4702_, v___x_4708_);
v___x_4710_ = lean_uint64_dec_eq(v___x_4709_, v___y_4704_);
if (v___x_4710_ == 0)
{
v___y_4684_ = v___x_4708_;
v___y_4685_ = v___y_4699_;
v___y_4686_ = v___y_4700_;
v___y_4687_ = v___y_4707_;
v___y_4688_ = v___y_4702_;
v___y_4689_ = v___y_4701_;
v___y_4690_ = v___y_4704_;
v___y_4691_ = v___y_4703_;
v___y_4692_ = v___y_4706_;
v___y_4693_ = v___y_4705_;
v___y_4694_ = v___x_4709_;
goto v___jp_4683_;
}
else
{
v___y_4684_ = v___x_4708_;
v___y_4685_ = v___y_4699_;
v___y_4686_ = v___y_4700_;
v___y_4687_ = v___y_4707_;
v___y_4688_ = v___y_4702_;
v___y_4689_ = v___y_4701_;
v___y_4690_ = v___y_4704_;
v___y_4691_ = v___y_4703_;
v___y_4692_ = v___y_4706_;
v___y_4693_ = v___y_4705_;
v___y_4694_ = v___y_4702_;
goto v___jp_4683_;
}
}
v___jp_4711_:
{
uint64_t v___x_4723_; uint8_t v___x_4724_; 
v___x_4723_ = lean_uint64_shift_right(v___y_4713_, v___y_4714_);
v___x_4724_ = lean_uint64_dec_eq(v___x_4723_, v___y_4718_);
if (v___x_4724_ == 0)
{
uint64_t v___x_4725_; 
v___x_4725_ = lean_uint64_add(v___y_4717_, v___y_4714_);
v___y_4699_ = v___y_4712_;
v___y_4700_ = v___y_4715_;
v___y_4701_ = v___y_4716_;
v___y_4702_ = v___y_4722_;
v___y_4703_ = v___y_4719_;
v___y_4704_ = v___y_4718_;
v___y_4705_ = v___y_4721_;
v___y_4706_ = v___y_4720_;
v___y_4707_ = v___x_4725_;
goto v___jp_4698_;
}
else
{
v___y_4699_ = v___y_4712_;
v___y_4700_ = v___y_4715_;
v___y_4701_ = v___y_4716_;
v___y_4702_ = v___y_4722_;
v___y_4703_ = v___y_4719_;
v___y_4704_ = v___y_4718_;
v___y_4705_ = v___y_4721_;
v___y_4706_ = v___y_4720_;
v___y_4707_ = v___y_4717_;
goto v___jp_4698_;
}
}
v___jp_4726_:
{
uint64_t v___x_4736_; uint64_t v___x_4737_; uint8_t v___x_4738_; 
v___x_4736_ = 4ULL;
v___x_4737_ = lean_uint64_shift_right(v___y_4728_, v___x_4736_);
v___x_4738_ = lean_uint64_dec_eq(v___x_4737_, v___y_4732_);
if (v___x_4738_ == 0)
{
v___y_4712_ = v___y_4727_;
v___y_4713_ = v___y_4728_;
v___y_4714_ = v___x_4736_;
v___y_4715_ = v___y_4729_;
v___y_4716_ = v___y_4730_;
v___y_4717_ = v___y_4735_;
v___y_4718_ = v___y_4732_;
v___y_4719_ = v___y_4731_;
v___y_4720_ = v___y_4734_;
v___y_4721_ = v___y_4733_;
v___y_4722_ = v___x_4737_;
goto v___jp_4711_;
}
else
{
v___y_4712_ = v___y_4727_;
v___y_4713_ = v___y_4728_;
v___y_4714_ = v___x_4736_;
v___y_4715_ = v___y_4729_;
v___y_4716_ = v___y_4730_;
v___y_4717_ = v___y_4735_;
v___y_4718_ = v___y_4732_;
v___y_4719_ = v___y_4731_;
v___y_4720_ = v___y_4734_;
v___y_4721_ = v___y_4733_;
v___y_4722_ = v___y_4728_;
goto v___jp_4711_;
}
}
v___jp_4739_:
{
uint64_t v___x_4751_; uint8_t v___x_4752_; 
v___x_4751_ = lean_uint64_shift_right(v___y_4747_, v___y_4740_);
v___x_4752_ = lean_uint64_dec_eq(v___x_4751_, v___y_4744_);
if (v___x_4752_ == 0)
{
uint64_t v___x_4753_; 
v___x_4753_ = lean_uint64_add(v___y_4746_, v___y_4740_);
v___y_4727_ = v___y_4741_;
v___y_4728_ = v___y_4750_;
v___y_4729_ = v___y_4742_;
v___y_4730_ = v___y_4743_;
v___y_4731_ = v___y_4745_;
v___y_4732_ = v___y_4744_;
v___y_4733_ = v___y_4749_;
v___y_4734_ = v___y_4748_;
v___y_4735_ = v___x_4753_;
goto v___jp_4726_;
}
else
{
v___y_4727_ = v___y_4741_;
v___y_4728_ = v___y_4750_;
v___y_4729_ = v___y_4742_;
v___y_4730_ = v___y_4743_;
v___y_4731_ = v___y_4745_;
v___y_4732_ = v___y_4744_;
v___y_4733_ = v___y_4749_;
v___y_4734_ = v___y_4748_;
v___y_4735_ = v___y_4746_;
goto v___jp_4726_;
}
}
v___jp_4754_:
{
uint64_t v___x_4764_; uint64_t v___x_4765_; uint8_t v___x_4766_; 
v___x_4764_ = 8ULL;
v___x_4765_ = lean_uint64_shift_right(v___y_4760_, v___x_4764_);
v___x_4766_ = lean_uint64_dec_eq(v___x_4765_, v___y_4759_);
if (v___x_4766_ == 0)
{
v___y_4740_ = v___x_4764_;
v___y_4741_ = v___y_4755_;
v___y_4742_ = v___y_4756_;
v___y_4743_ = v___y_4757_;
v___y_4744_ = v___y_4759_;
v___y_4745_ = v___y_4758_;
v___y_4746_ = v___y_4763_;
v___y_4747_ = v___y_4760_;
v___y_4748_ = v___y_4762_;
v___y_4749_ = v___y_4761_;
v___y_4750_ = v___x_4765_;
goto v___jp_4739_;
}
else
{
v___y_4740_ = v___x_4764_;
v___y_4741_ = v___y_4755_;
v___y_4742_ = v___y_4756_;
v___y_4743_ = v___y_4757_;
v___y_4744_ = v___y_4759_;
v___y_4745_ = v___y_4758_;
v___y_4746_ = v___y_4763_;
v___y_4747_ = v___y_4760_;
v___y_4748_ = v___y_4762_;
v___y_4749_ = v___y_4761_;
v___y_4750_ = v___y_4760_;
goto v___jp_4739_;
}
}
v___jp_4767_:
{
uint64_t v___x_4779_; uint8_t v___x_4780_; 
v___x_4779_ = lean_uint64_shift_right(v___y_4770_, v___y_4775_);
v___x_4780_ = lean_uint64_dec_eq(v___x_4779_, v___y_4772_);
if (v___x_4780_ == 0)
{
uint64_t v___x_4781_; 
v___x_4781_ = lean_uint64_add(v___y_4774_, v___y_4775_);
v___y_4755_ = v___y_4768_;
v___y_4756_ = v___y_4769_;
v___y_4757_ = v___y_4771_;
v___y_4758_ = v___y_4773_;
v___y_4759_ = v___y_4772_;
v___y_4760_ = v___y_4778_;
v___y_4761_ = v___y_4777_;
v___y_4762_ = v___y_4776_;
v___y_4763_ = v___x_4781_;
goto v___jp_4754_;
}
else
{
v___y_4755_ = v___y_4768_;
v___y_4756_ = v___y_4769_;
v___y_4757_ = v___y_4771_;
v___y_4758_ = v___y_4773_;
v___y_4759_ = v___y_4772_;
v___y_4760_ = v___y_4778_;
v___y_4761_ = v___y_4777_;
v___y_4762_ = v___y_4776_;
v___y_4763_ = v___y_4774_;
goto v___jp_4754_;
}
}
v___jp_4782_:
{
uint64_t v___x_4792_; uint64_t v___x_4793_; uint8_t v___x_4794_; 
v___x_4792_ = 16ULL;
v___x_4793_ = lean_uint64_shift_right(v___y_4785_, v___x_4792_);
v___x_4794_ = lean_uint64_dec_eq(v___x_4793_, v___y_4788_);
if (v___x_4794_ == 0)
{
v___y_4768_ = v___y_4783_;
v___y_4769_ = v___y_4784_;
v___y_4770_ = v___y_4785_;
v___y_4771_ = v___y_4786_;
v___y_4772_ = v___y_4788_;
v___y_4773_ = v___y_4787_;
v___y_4774_ = v___y_4791_;
v___y_4775_ = v___x_4792_;
v___y_4776_ = v___y_4790_;
v___y_4777_ = v___y_4789_;
v___y_4778_ = v___x_4793_;
goto v___jp_4767_;
}
else
{
v___y_4768_ = v___y_4783_;
v___y_4769_ = v___y_4784_;
v___y_4770_ = v___y_4785_;
v___y_4771_ = v___y_4786_;
v___y_4772_ = v___y_4788_;
v___y_4773_ = v___y_4787_;
v___y_4774_ = v___y_4791_;
v___y_4775_ = v___x_4792_;
v___y_4776_ = v___y_4790_;
v___y_4777_ = v___y_4789_;
v___y_4778_ = v___y_4785_;
goto v___jp_4767_;
}
}
v___jp_4795_:
{
uint64_t v___x_4805_; uint64_t v___x_4806_; uint8_t v___x_4807_; 
v___x_4805_ = lean_unbox_uint64(v___y_4798_);
v___x_4806_ = lean_uint64_shift_right(v___x_4805_, v___y_4801_);
v___x_4807_ = lean_uint64_dec_eq(v___x_4806_, v___y_4799_);
if (v___x_4807_ == 0)
{
v___y_4783_ = v___y_4796_;
v___y_4784_ = v___y_4797_;
v___y_4785_ = v___y_4804_;
v___y_4786_ = v___y_4798_;
v___y_4787_ = v___y_4800_;
v___y_4788_ = v___y_4799_;
v___y_4789_ = v___y_4803_;
v___y_4790_ = v___y_4802_;
v___y_4791_ = v___y_4801_;
goto v___jp_4782_;
}
else
{
v___y_4783_ = v___y_4796_;
v___y_4784_ = v___y_4797_;
v___y_4785_ = v___y_4804_;
v___y_4786_ = v___y_4798_;
v___y_4787_ = v___y_4800_;
v___y_4788_ = v___y_4799_;
v___y_4789_ = v___y_4803_;
v___y_4790_ = v___y_4802_;
v___y_4791_ = v___y_4799_;
goto v___jp_4782_;
}
}
v___jp_4808_:
{
uint64_t v___x_4814_; uint64_t v___x_4815_; uint8_t v___x_4816_; 
v___x_4814_ = 0ULL;
v___x_4815_ = lean_unbox_uint64(v_snd_4813_);
v___x_4816_ = lean_uint64_dec_eq(v___x_4815_, v___x_4814_);
if (v___x_4816_ == 0)
{
uint64_t v___x_4817_; uint64_t v___x_4818_; uint64_t v___x_4819_; uint64_t v___x_4820_; uint64_t v___x_4821_; uint8_t v___x_4822_; 
v___x_4817_ = 149ULL;
v___x_4818_ = lean_uint64_add(v___y_4810_, v___x_4817_);
v___x_4819_ = 32ULL;
v___x_4820_ = lean_unbox_uint64(v_snd_4813_);
v___x_4821_ = lean_uint64_shift_right(v___x_4820_, v___x_4819_);
v___x_4822_ = lean_uint64_dec_eq(v___x_4821_, v___x_4814_);
if (v___x_4822_ == 0)
{
v___y_4796_ = v___y_4809_;
v___y_4797_ = v___x_4818_;
v___y_4798_ = v_snd_4813_;
v___y_4799_ = v___x_4814_;
v___y_4800_ = v___x_4817_;
v___y_4801_ = v___x_4819_;
v___y_4802_ = v_fst_4812_;
v___y_4803_ = v___y_4811_;
v___y_4804_ = v___x_4821_;
goto v___jp_4795_;
}
else
{
uint64_t v___x_4823_; 
v___x_4823_ = lean_unbox_uint64(v_snd_4813_);
v___y_4796_ = v___y_4809_;
v___y_4797_ = v___x_4818_;
v___y_4798_ = v_snd_4813_;
v___y_4799_ = v___x_4814_;
v___y_4800_ = v___x_4817_;
v___y_4801_ = v___x_4819_;
v___y_4802_ = v_fst_4812_;
v___y_4803_ = v___y_4811_;
v___y_4804_ = v___x_4823_;
goto v___jp_4795_;
}
}
else
{
uint8_t v___x_4824_; 
lean_dec(v_snd_4813_);
v___x_4824_ = lean_unbox(v_fst_4812_);
lean_dec(v_fst_4812_);
if (v___x_4824_ == 0)
{
lean_object* v___x_4825_; 
v___x_4825_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
return v___x_4825_;
}
else
{
lean_object* v___x_4826_; 
v___x_4826_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
return v___x_4826_;
}
}
}
v___jp_4827_:
{
uint8_t v___x_4836_; 
v___x_4836_ = lean_uint64_dec_eq(v___y_4832_, v___y_4829_);
if (v___x_4836_ == 0)
{
uint8_t v___x_4837_; 
v___x_4837_ = lean_uint64_dec_lt(v___y_4832_, v___y_4829_);
if (v___x_4837_ == 0)
{
uint64_t v___x_4838_; lean_object* v___x_4839_; lean_object* v___x_4840_; 
v___x_4838_ = lean_uint64_sub(v___y_4832_, v___y_4829_);
v___x_4839_ = lean_box(v___y_4831_);
v___x_4840_ = lean_box_uint64(v___x_4838_);
v___y_4809_ = v___y_4828_;
v___y_4810_ = v___y_4833_;
v___y_4811_ = v___y_4834_;
v_fst_4812_ = v___x_4839_;
v_snd_4813_ = v___x_4840_;
goto v___jp_4808_;
}
else
{
uint64_t v___x_4841_; lean_object* v___x_4842_; lean_object* v___x_4843_; 
v___x_4841_ = lean_uint64_sub(v___y_4829_, v___y_4832_);
v___x_4842_ = lean_box(v___y_4830_);
v___x_4843_ = lean_box_uint64(v___x_4841_);
v___y_4809_ = v___y_4828_;
v___y_4810_ = v___y_4833_;
v___y_4811_ = v___y_4834_;
v_fst_4812_ = v___x_4842_;
v_snd_4813_ = v___x_4843_;
goto v___jp_4808_;
}
}
else
{
lean_object* v___x_4844_; lean_object* v___x_4845_; 
v___x_4844_ = lean_box(v___y_4835_);
v___x_4845_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_4809_ = v___y_4828_;
v___y_4810_ = v___y_4833_;
v___y_4811_ = v___y_4834_;
v_fst_4812_ = v___x_4844_;
v_snd_4813_ = v___x_4845_;
goto v___jp_4808_;
}
}
v___jp_4846_:
{
if (v___y_4854_ == 0)
{
v___y_4828_ = v___y_4847_;
v___y_4829_ = v___y_4848_;
v___y_4830_ = v___y_4849_;
v___y_4831_ = v___y_4851_;
v___y_4832_ = v___y_4850_;
v___y_4833_ = v___y_4852_;
v___y_4834_ = v___y_4853_;
v___y_4835_ = v___y_4854_;
goto v___jp_4827_;
}
else
{
uint64_t v___x_4855_; lean_object* v___x_4856_; lean_object* v___x_4857_; 
v___x_4855_ = lean_uint64_add(v___y_4850_, v___y_4848_);
v___x_4856_ = lean_box(v___y_4851_);
v___x_4857_ = lean_box_uint64(v___x_4855_);
v___y_4809_ = v___y_4847_;
v___y_4810_ = v___y_4852_;
v___y_4811_ = v___y_4853_;
v_fst_4812_ = v___x_4856_;
v_snd_4813_ = v___x_4857_;
goto v___jp_4808_;
}
}
v___jp_4858_:
{
uint32_t v___x_4860_; uint32_t v___x_4861_; lean_object* v___x_4862_; 
v___x_4860_ = 8388608;
v___x_4861_ = lean_uint32_lor(v___y_4859_, v___x_4860_);
v___x_4862_ = lean_box_uint32(v___x_4861_);
return v___x_4862_;
}
v___jp_4863_:
{
uint8_t v___x_4867_; 
v___x_4867_ = lean_uint64_dec_eq(v___y_4866_, v___y_4865_);
if (v___x_4867_ == 0)
{
uint64_t v___x_4868_; uint8_t v___x_4869_; 
v___x_4868_ = 8388608ULL;
v___x_4869_ = lean_uint64_dec_eq(v___y_4866_, v___x_4868_);
if (v___x_4869_ == 0)
{
uint32_t v___x_4870_; uint8_t v___x_4871_; 
v___x_4870_ = lean_uint64_to_uint32(v___y_4866_);
v___x_4871_ = lean_unbox(v___y_4864_);
lean_dec(v___y_4864_);
if (v___x_4871_ == 0)
{
uint32_t v___x_4872_; 
v___x_4872_ = 0;
v___y_4501_ = v___x_4870_;
v___y_4502_ = v___x_4872_;
goto v___jp_4500_;
}
else
{
uint32_t v___x_4873_; 
v___x_4873_ = 2147483648;
v___y_4501_ = v___x_4870_;
v___y_4502_ = v___x_4873_;
goto v___jp_4500_;
}
}
else
{
uint8_t v___x_4874_; 
v___x_4874_ = lean_unbox(v___y_4864_);
lean_dec(v___y_4864_);
if (v___x_4874_ == 0)
{
uint32_t v___x_4875_; 
v___x_4875_ = 0;
v___y_4859_ = v___x_4875_;
goto v___jp_4858_;
}
else
{
uint32_t v___x_4876_; 
v___x_4876_ = 2147483648;
v___y_4859_ = v___x_4876_;
goto v___jp_4858_;
}
}
}
else
{
uint8_t v___x_4877_; 
v___x_4877_ = lean_unbox(v___y_4864_);
lean_dec(v___y_4864_);
if (v___x_4877_ == 0)
{
lean_object* v___x_4878_; 
v___x_4878_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
return v___x_4878_;
}
else
{
lean_object* v___x_4879_; 
v___x_4879_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
return v___x_4879_;
}
}
}
v___jp_4880_:
{
uint64_t v_position_4889_; uint64_t v___x_4890_; uint8_t v___x_4891_; 
v_position_4889_ = lean_uint64_add(v___y_4888_, v___y_4883_);
v___x_4890_ = 172ULL;
v___x_4891_ = lean_uint64_dec_lt(v_position_4889_, v___x_4890_);
if (v___x_4891_ == 0)
{
uint64_t v___x_4892_; uint8_t v___x_4893_; 
v___x_4892_ = 23ULL;
v___x_4893_ = lean_uint64_dec_lt(v___y_4888_, v___x_4892_);
if (v___x_4893_ == 0)
{
uint64_t v___x_4894_; uint8_t v___x_4895_; 
v___x_4894_ = lean_uint64_sub(v___y_4888_, v___x_4892_);
v___x_4895_ = lean_uint64_dec_eq(v___x_4894_, v___y_4884_);
if (v___x_4895_ == 0)
{
uint64_t v___x_4896_; uint8_t v___x_4897_; 
v___x_4896_ = 64ULL;
v___x_4897_ = lean_uint64_dec_lt(v___x_4894_, v___x_4896_);
if (v___x_4897_ == 0)
{
uint8_t v___x_4898_; 
v___x_4898_ = lean_uint64_dec_eq(v___x_4894_, v___x_4896_);
if (v___x_4898_ == 0)
{
lean_dec(v___y_4886_);
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v___y_4884_;
goto v___jp_4489_;
}
else
{
uint64_t v___x_4899_; uint64_t v___x_4900_; uint8_t v___x_4901_; 
v___x_4899_ = 9223372036854775808ULL;
v___x_4900_ = lean_unbox_uint64(v___y_4886_);
lean_dec(v___y_4886_);
v___x_4901_ = lean_uint64_dec_lt(v___x_4899_, v___x_4900_);
if (v___x_4901_ == 0)
{
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v___y_4884_;
goto v___jp_4489_;
}
else
{
uint64_t v___x_4902_; 
v___x_4902_ = 1ULL;
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v___x_4902_;
goto v___jp_4489_;
}
}
}
else
{
uint64_t v___x_4903_; uint64_t v_quotient_4904_; uint64_t v___x_4905_; uint64_t v___x_4906_; uint64_t v___x_4907_; uint64_t v___x_4908_; uint64_t v_remainder_4909_; uint64_t v___x_4910_; uint64_t v_half_4911_; uint8_t v___x_4912_; 
v___x_4903_ = lean_unbox_uint64(v___y_4886_);
v_quotient_4904_ = lean_uint64_shift_right(v___x_4903_, v___x_4894_);
v___x_4905_ = 1ULL;
v___x_4906_ = lean_uint64_shift_left(v___x_4905_, v___x_4894_);
v___x_4907_ = lean_uint64_sub(v___x_4906_, v___x_4905_);
v___x_4908_ = lean_unbox_uint64(v___y_4886_);
lean_dec(v___y_4886_);
v_remainder_4909_ = lean_uint64_land(v___x_4908_, v___x_4907_);
v___x_4910_ = lean_uint64_sub(v___x_4894_, v___x_4905_);
v_half_4911_ = lean_uint64_shift_left(v___x_4905_, v___x_4910_);
v___x_4912_ = lean_uint64_dec_lt(v_remainder_4909_, v_half_4911_);
if (v___x_4912_ == 0)
{
uint8_t v___x_4913_; 
v___x_4913_ = lean_uint64_dec_lt(v_half_4911_, v_remainder_4909_);
if (v___x_4913_ == 0)
{
uint64_t v___x_4914_; uint8_t v___x_4915_; 
v___x_4914_ = lean_uint64_land(v_quotient_4904_, v___x_4905_);
v___x_4915_ = lean_uint64_dec_eq(v___x_4914_, v___y_4884_);
if (v___x_4915_ == 0)
{
uint64_t v___x_4916_; 
v___x_4916_ = lean_uint64_add(v_quotient_4904_, v___x_4905_);
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v___x_4916_;
goto v___jp_4489_;
}
else
{
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v_quotient_4904_;
goto v___jp_4489_;
}
}
else
{
uint64_t v___x_4917_; 
v___x_4917_ = lean_uint64_add(v_quotient_4904_, v___x_4905_);
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v___x_4917_;
goto v___jp_4489_;
}
}
else
{
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v_quotient_4904_;
goto v___jp_4489_;
}
}
}
else
{
uint64_t v___x_4918_; 
v___x_4918_ = lean_unbox_uint64(v___y_4886_);
lean_dec(v___y_4886_);
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v___x_4918_;
goto v___jp_4489_;
}
}
else
{
uint64_t v___x_4919_; uint64_t v___x_4920_; uint64_t v___x_4921_; 
v___x_4919_ = lean_uint64_sub(v___x_4892_, v___y_4888_);
v___x_4920_ = lean_unbox_uint64(v___y_4886_);
lean_dec(v___y_4886_);
v___x_4921_ = lean_uint64_shift_left(v___x_4920_, v___x_4919_);
v___y_4490_ = v___y_4882_;
v___y_4491_ = v___y_4881_;
v___y_4492_ = v_position_4889_;
v___y_4493_ = v___y_4884_;
v___y_4494_ = v___y_4887_;
v___y_4495_ = v___x_4921_;
goto v___jp_4489_;
}
}
else
{
uint8_t v___x_4922_; 
v___x_4922_ = lean_uint64_dec_lt(v___y_4883_, v___y_4885_);
if (v___x_4922_ == 0)
{
uint64_t v___x_4923_; uint64_t v___x_4924_; uint64_t v___x_4925_; 
v___x_4923_ = lean_uint64_sub(v___y_4883_, v___y_4885_);
v___x_4924_ = lean_unbox_uint64(v___y_4886_);
lean_dec(v___y_4886_);
v___x_4925_ = lean_uint64_shift_left(v___x_4924_, v___x_4923_);
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v___x_4925_;
goto v___jp_4863_;
}
else
{
uint64_t v___x_4926_; uint8_t v___x_4927_; 
v___x_4926_ = lean_uint64_sub(v___y_4885_, v___y_4883_);
v___x_4927_ = lean_uint64_dec_eq(v___x_4926_, v___y_4884_);
if (v___x_4927_ == 0)
{
uint64_t v___x_4928_; uint8_t v___x_4929_; 
v___x_4928_ = 64ULL;
v___x_4929_ = lean_uint64_dec_lt(v___x_4926_, v___x_4928_);
if (v___x_4929_ == 0)
{
uint8_t v___x_4930_; 
v___x_4930_ = lean_uint64_dec_eq(v___x_4926_, v___x_4928_);
if (v___x_4930_ == 0)
{
lean_dec(v___y_4886_);
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v___y_4884_;
goto v___jp_4863_;
}
else
{
uint64_t v___x_4931_; uint64_t v___x_4932_; uint8_t v___x_4933_; 
v___x_4931_ = 9223372036854775808ULL;
v___x_4932_ = lean_unbox_uint64(v___y_4886_);
lean_dec(v___y_4886_);
v___x_4933_ = lean_uint64_dec_lt(v___x_4931_, v___x_4932_);
if (v___x_4933_ == 0)
{
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v___y_4884_;
goto v___jp_4863_;
}
else
{
uint64_t v___x_4934_; 
v___x_4934_ = 1ULL;
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v___x_4934_;
goto v___jp_4863_;
}
}
}
else
{
uint64_t v___x_4935_; uint64_t v_quotient_4936_; uint64_t v___x_4937_; uint64_t v___x_4938_; uint64_t v___x_4939_; uint64_t v___x_4940_; uint64_t v_remainder_4941_; uint64_t v___x_4942_; uint64_t v_half_4943_; uint8_t v___x_4944_; 
v___x_4935_ = lean_unbox_uint64(v___y_4886_);
v_quotient_4936_ = lean_uint64_shift_right(v___x_4935_, v___x_4926_);
v___x_4937_ = 1ULL;
v___x_4938_ = lean_uint64_shift_left(v___x_4937_, v___x_4926_);
v___x_4939_ = lean_uint64_sub(v___x_4938_, v___x_4937_);
v___x_4940_ = lean_unbox_uint64(v___y_4886_);
lean_dec(v___y_4886_);
v_remainder_4941_ = lean_uint64_land(v___x_4940_, v___x_4939_);
v___x_4942_ = lean_uint64_sub(v___x_4926_, v___x_4937_);
v_half_4943_ = lean_uint64_shift_left(v___x_4937_, v___x_4942_);
v___x_4944_ = lean_uint64_dec_lt(v_remainder_4941_, v_half_4943_);
if (v___x_4944_ == 0)
{
uint8_t v___x_4945_; 
v___x_4945_ = lean_uint64_dec_lt(v_half_4943_, v_remainder_4941_);
if (v___x_4945_ == 0)
{
uint64_t v___x_4946_; uint8_t v___x_4947_; 
v___x_4946_ = lean_uint64_land(v_quotient_4936_, v___x_4937_);
v___x_4947_ = lean_uint64_dec_eq(v___x_4946_, v___y_4884_);
if (v___x_4947_ == 0)
{
uint64_t v___x_4948_; 
v___x_4948_ = lean_uint64_add(v_quotient_4936_, v___x_4937_);
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v___x_4948_;
goto v___jp_4863_;
}
else
{
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v_quotient_4936_;
goto v___jp_4863_;
}
}
else
{
uint64_t v___x_4949_; 
v___x_4949_ = lean_uint64_add(v_quotient_4936_, v___x_4937_);
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v___x_4949_;
goto v___jp_4863_;
}
}
else
{
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v_quotient_4936_;
goto v___jp_4863_;
}
}
}
else
{
uint64_t v___x_4950_; 
v___x_4950_ = lean_unbox_uint64(v___y_4886_);
lean_dec(v___y_4886_);
v___y_4864_ = v___y_4881_;
v___y_4865_ = v___y_4884_;
v___y_4866_ = v___x_4950_;
goto v___jp_4863_;
}
}
}
}
v___jp_4951_:
{
uint64_t v___x_4961_; uint64_t v___x_4962_; uint8_t v___x_4963_; 
v___x_4961_ = 1ULL;
v___x_4962_ = lean_uint64_shift_right(v___y_4957_, v___x_4961_);
v___x_4963_ = lean_uint64_dec_eq(v___x_4962_, v___y_4955_);
if (v___x_4963_ == 0)
{
uint64_t v___x_4964_; 
v___x_4964_ = lean_uint64_add(v___y_4960_, v___x_4961_);
v___y_4881_ = v___y_4953_;
v___y_4882_ = v___y_4952_;
v___y_4883_ = v___y_4954_;
v___y_4884_ = v___y_4955_;
v___y_4885_ = v___y_4956_;
v___y_4886_ = v___y_4959_;
v___y_4887_ = v___y_4958_;
v___y_4888_ = v___x_4964_;
goto v___jp_4880_;
}
else
{
v___y_4881_ = v___y_4953_;
v___y_4882_ = v___y_4952_;
v___y_4883_ = v___y_4954_;
v___y_4884_ = v___y_4955_;
v___y_4885_ = v___y_4956_;
v___y_4886_ = v___y_4959_;
v___y_4887_ = v___y_4958_;
v___y_4888_ = v___y_4960_;
goto v___jp_4880_;
}
}
v___jp_4965_:
{
uint64_t v___x_4977_; uint8_t v___x_4978_; 
v___x_4977_ = lean_uint64_shift_right(v___y_4973_, v___y_4969_);
v___x_4978_ = lean_uint64_dec_eq(v___x_4977_, v___y_4970_);
if (v___x_4978_ == 0)
{
uint64_t v___x_4979_; 
v___x_4979_ = lean_uint64_add(v___y_4972_, v___y_4969_);
v___y_4952_ = v___y_4967_;
v___y_4953_ = v___y_4966_;
v___y_4954_ = v___y_4968_;
v___y_4955_ = v___y_4970_;
v___y_4956_ = v___y_4971_;
v___y_4957_ = v___y_4976_;
v___y_4958_ = v___y_4975_;
v___y_4959_ = v___y_4974_;
v___y_4960_ = v___x_4979_;
goto v___jp_4951_;
}
else
{
v___y_4952_ = v___y_4967_;
v___y_4953_ = v___y_4966_;
v___y_4954_ = v___y_4968_;
v___y_4955_ = v___y_4970_;
v___y_4956_ = v___y_4971_;
v___y_4957_ = v___y_4976_;
v___y_4958_ = v___y_4975_;
v___y_4959_ = v___y_4974_;
v___y_4960_ = v___y_4972_;
goto v___jp_4951_;
}
}
v___jp_4980_:
{
uint64_t v___x_4990_; uint64_t v___x_4991_; uint8_t v___x_4992_; 
v___x_4990_ = 2ULL;
v___x_4991_ = lean_uint64_shift_right(v___y_4986_, v___x_4990_);
v___x_4992_ = lean_uint64_dec_eq(v___x_4991_, v___y_4984_);
if (v___x_4992_ == 0)
{
v___y_4966_ = v___y_4982_;
v___y_4967_ = v___y_4981_;
v___y_4968_ = v___y_4983_;
v___y_4969_ = v___x_4990_;
v___y_4970_ = v___y_4984_;
v___y_4971_ = v___y_4985_;
v___y_4972_ = v___y_4989_;
v___y_4973_ = v___y_4986_;
v___y_4974_ = v___y_4988_;
v___y_4975_ = v___y_4987_;
v___y_4976_ = v___x_4991_;
goto v___jp_4965_;
}
else
{
v___y_4966_ = v___y_4982_;
v___y_4967_ = v___y_4981_;
v___y_4968_ = v___y_4983_;
v___y_4969_ = v___x_4990_;
v___y_4970_ = v___y_4984_;
v___y_4971_ = v___y_4985_;
v___y_4972_ = v___y_4989_;
v___y_4973_ = v___y_4986_;
v___y_4974_ = v___y_4988_;
v___y_4975_ = v___y_4987_;
v___y_4976_ = v___y_4986_;
goto v___jp_4965_;
}
}
v___jp_4993_:
{
uint64_t v___x_5005_; uint8_t v___x_5006_; 
v___x_5005_ = lean_uint64_shift_right(v___y_4998_, v___y_4997_);
v___x_5006_ = lean_uint64_dec_eq(v___x_5005_, v___y_4999_);
if (v___x_5006_ == 0)
{
uint64_t v___x_5007_; 
v___x_5007_ = lean_uint64_add(v___y_5001_, v___y_4997_);
v___y_4981_ = v___y_4995_;
v___y_4982_ = v___y_4994_;
v___y_4983_ = v___y_4996_;
v___y_4984_ = v___y_4999_;
v___y_4985_ = v___y_5000_;
v___y_4986_ = v___y_5004_;
v___y_4987_ = v___y_5003_;
v___y_4988_ = v___y_5002_;
v___y_4989_ = v___x_5007_;
goto v___jp_4980_;
}
else
{
v___y_4981_ = v___y_4995_;
v___y_4982_ = v___y_4994_;
v___y_4983_ = v___y_4996_;
v___y_4984_ = v___y_4999_;
v___y_4985_ = v___y_5000_;
v___y_4986_ = v___y_5004_;
v___y_4987_ = v___y_5003_;
v___y_4988_ = v___y_5002_;
v___y_4989_ = v___y_5001_;
goto v___jp_4980_;
}
}
v___jp_5008_:
{
uint64_t v___x_5018_; uint64_t v___x_5019_; uint8_t v___x_5020_; 
v___x_5018_ = 4ULL;
v___x_5019_ = lean_uint64_shift_right(v___y_5012_, v___x_5018_);
v___x_5020_ = lean_uint64_dec_eq(v___x_5019_, v___y_5013_);
if (v___x_5020_ == 0)
{
v___y_4994_ = v___y_5010_;
v___y_4995_ = v___y_5009_;
v___y_4996_ = v___y_5011_;
v___y_4997_ = v___x_5018_;
v___y_4998_ = v___y_5012_;
v___y_4999_ = v___y_5013_;
v___y_5000_ = v___y_5014_;
v___y_5001_ = v___y_5017_;
v___y_5002_ = v___y_5016_;
v___y_5003_ = v___y_5015_;
v___y_5004_ = v___x_5019_;
goto v___jp_4993_;
}
else
{
v___y_4994_ = v___y_5010_;
v___y_4995_ = v___y_5009_;
v___y_4996_ = v___y_5011_;
v___y_4997_ = v___x_5018_;
v___y_4998_ = v___y_5012_;
v___y_4999_ = v___y_5013_;
v___y_5000_ = v___y_5014_;
v___y_5001_ = v___y_5017_;
v___y_5002_ = v___y_5016_;
v___y_5003_ = v___y_5015_;
v___y_5004_ = v___y_5012_;
goto v___jp_4993_;
}
}
v___jp_5021_:
{
uint64_t v___x_5033_; uint8_t v___x_5034_; 
v___x_5033_ = lean_uint64_shift_right(v___y_5025_, v___y_5024_);
v___x_5034_ = lean_uint64_dec_eq(v___x_5033_, v___y_5028_);
if (v___x_5034_ == 0)
{
uint64_t v___x_5035_; 
v___x_5035_ = lean_uint64_add(v___y_5027_, v___y_5024_);
v___y_5009_ = v___y_5023_;
v___y_5010_ = v___y_5022_;
v___y_5011_ = v___y_5026_;
v___y_5012_ = v___y_5032_;
v___y_5013_ = v___y_5028_;
v___y_5014_ = v___y_5029_;
v___y_5015_ = v___y_5031_;
v___y_5016_ = v___y_5030_;
v___y_5017_ = v___x_5035_;
goto v___jp_5008_;
}
else
{
v___y_5009_ = v___y_5023_;
v___y_5010_ = v___y_5022_;
v___y_5011_ = v___y_5026_;
v___y_5012_ = v___y_5032_;
v___y_5013_ = v___y_5028_;
v___y_5014_ = v___y_5029_;
v___y_5015_ = v___y_5031_;
v___y_5016_ = v___y_5030_;
v___y_5017_ = v___y_5027_;
goto v___jp_5008_;
}
}
v___jp_5036_:
{
uint64_t v___x_5046_; uint64_t v___x_5047_; uint8_t v___x_5048_; 
v___x_5046_ = 8ULL;
v___x_5047_ = lean_uint64_shift_right(v___y_5039_, v___x_5046_);
v___x_5048_ = lean_uint64_dec_eq(v___x_5047_, v___y_5041_);
if (v___x_5048_ == 0)
{
v___y_5022_ = v___y_5038_;
v___y_5023_ = v___y_5037_;
v___y_5024_ = v___x_5046_;
v___y_5025_ = v___y_5039_;
v___y_5026_ = v___y_5040_;
v___y_5027_ = v___y_5045_;
v___y_5028_ = v___y_5041_;
v___y_5029_ = v___y_5042_;
v___y_5030_ = v___y_5044_;
v___y_5031_ = v___y_5043_;
v___y_5032_ = v___x_5047_;
goto v___jp_5021_;
}
else
{
v___y_5022_ = v___y_5038_;
v___y_5023_ = v___y_5037_;
v___y_5024_ = v___x_5046_;
v___y_5025_ = v___y_5039_;
v___y_5026_ = v___y_5040_;
v___y_5027_ = v___y_5045_;
v___y_5028_ = v___y_5041_;
v___y_5029_ = v___y_5042_;
v___y_5030_ = v___y_5044_;
v___y_5031_ = v___y_5043_;
v___y_5032_ = v___y_5039_;
goto v___jp_5021_;
}
}
v___jp_5049_:
{
uint64_t v___x_5061_; uint8_t v___x_5062_; 
v___x_5061_ = lean_uint64_shift_right(v___y_5052_, v___y_5056_);
v___x_5062_ = lean_uint64_dec_eq(v___x_5061_, v___y_5055_);
if (v___x_5062_ == 0)
{
uint64_t v___x_5063_; 
v___x_5063_ = lean_uint64_add(v___y_5054_, v___y_5056_);
v___y_5037_ = v___y_5051_;
v___y_5038_ = v___y_5050_;
v___y_5039_ = v___y_5060_;
v___y_5040_ = v___y_5053_;
v___y_5041_ = v___y_5055_;
v___y_5042_ = v___y_5057_;
v___y_5043_ = v___y_5059_;
v___y_5044_ = v___y_5058_;
v___y_5045_ = v___x_5063_;
goto v___jp_5036_;
}
else
{
v___y_5037_ = v___y_5051_;
v___y_5038_ = v___y_5050_;
v___y_5039_ = v___y_5060_;
v___y_5040_ = v___y_5053_;
v___y_5041_ = v___y_5055_;
v___y_5042_ = v___y_5057_;
v___y_5043_ = v___y_5059_;
v___y_5044_ = v___y_5058_;
v___y_5045_ = v___y_5054_;
goto v___jp_5036_;
}
}
v___jp_5064_:
{
uint64_t v___x_5074_; uint64_t v___x_5075_; uint8_t v___x_5076_; 
v___x_5074_ = 16ULL;
v___x_5075_ = lean_uint64_shift_right(v___y_5067_, v___x_5074_);
v___x_5076_ = lean_uint64_dec_eq(v___x_5075_, v___y_5069_);
if (v___x_5076_ == 0)
{
v___y_5050_ = v___y_5066_;
v___y_5051_ = v___y_5065_;
v___y_5052_ = v___y_5067_;
v___y_5053_ = v___y_5068_;
v___y_5054_ = v___y_5073_;
v___y_5055_ = v___y_5069_;
v___y_5056_ = v___x_5074_;
v___y_5057_ = v___y_5070_;
v___y_5058_ = v___y_5072_;
v___y_5059_ = v___y_5071_;
v___y_5060_ = v___x_5075_;
goto v___jp_5049_;
}
else
{
v___y_5050_ = v___y_5066_;
v___y_5051_ = v___y_5065_;
v___y_5052_ = v___y_5067_;
v___y_5053_ = v___y_5068_;
v___y_5054_ = v___y_5073_;
v___y_5055_ = v___y_5069_;
v___y_5056_ = v___x_5074_;
v___y_5057_ = v___y_5070_;
v___y_5058_ = v___y_5072_;
v___y_5059_ = v___y_5071_;
v___y_5060_ = v___y_5067_;
goto v___jp_5049_;
}
}
v___jp_5077_:
{
uint64_t v___x_5087_; uint64_t v___x_5088_; uint8_t v___x_5089_; 
v___x_5087_ = lean_unbox_uint64(v___y_5084_);
v___x_5088_ = lean_uint64_shift_right(v___x_5087_, v___y_5080_);
v___x_5089_ = lean_uint64_dec_eq(v___x_5088_, v___y_5082_);
if (v___x_5089_ == 0)
{
v___y_5065_ = v___y_5079_;
v___y_5066_ = v___y_5078_;
v___y_5067_ = v___y_5086_;
v___y_5068_ = v___y_5081_;
v___y_5069_ = v___y_5082_;
v___y_5070_ = v___y_5083_;
v___y_5071_ = v___y_5085_;
v___y_5072_ = v___y_5084_;
v___y_5073_ = v___y_5080_;
goto v___jp_5064_;
}
else
{
v___y_5065_ = v___y_5079_;
v___y_5066_ = v___y_5078_;
v___y_5067_ = v___y_5086_;
v___y_5068_ = v___y_5081_;
v___y_5069_ = v___y_5082_;
v___y_5070_ = v___y_5083_;
v___y_5071_ = v___y_5085_;
v___y_5072_ = v___y_5084_;
v___y_5073_ = v___y_5082_;
goto v___jp_5064_;
}
}
v___jp_5090_:
{
uint64_t v___x_5096_; uint64_t v___x_5097_; uint8_t v___x_5098_; 
v___x_5096_ = 0ULL;
v___x_5097_ = lean_unbox_uint64(v_snd_5095_);
v___x_5098_ = lean_uint64_dec_eq(v___x_5097_, v___x_5096_);
if (v___x_5098_ == 0)
{
uint64_t v___x_5099_; uint64_t v___x_5100_; uint64_t v___x_5101_; uint64_t v___x_5102_; uint64_t v___x_5103_; uint8_t v___x_5104_; 
v___x_5099_ = 149ULL;
v___x_5100_ = lean_uint64_add(v___y_5092_, v___x_5099_);
v___x_5101_ = 32ULL;
v___x_5102_ = lean_unbox_uint64(v_snd_5095_);
v___x_5103_ = lean_uint64_shift_right(v___x_5102_, v___x_5101_);
v___x_5104_ = lean_uint64_dec_eq(v___x_5103_, v___x_5096_);
if (v___x_5104_ == 0)
{
v___y_5078_ = v_fst_5094_;
v___y_5079_ = v___y_5091_;
v___y_5080_ = v___x_5101_;
v___y_5081_ = v___x_5100_;
v___y_5082_ = v___x_5096_;
v___y_5083_ = v___x_5099_;
v___y_5084_ = v_snd_5095_;
v___y_5085_ = v___y_5093_;
v___y_5086_ = v___x_5103_;
goto v___jp_5077_;
}
else
{
uint64_t v___x_5105_; 
v___x_5105_ = lean_unbox_uint64(v_snd_5095_);
v___y_5078_ = v_fst_5094_;
v___y_5079_ = v___y_5091_;
v___y_5080_ = v___x_5101_;
v___y_5081_ = v___x_5100_;
v___y_5082_ = v___x_5096_;
v___y_5083_ = v___x_5099_;
v___y_5084_ = v_snd_5095_;
v___y_5085_ = v___y_5093_;
v___y_5086_ = v___x_5105_;
goto v___jp_5077_;
}
}
else
{
uint8_t v___x_5106_; 
lean_dec(v_snd_5095_);
v___x_5106_ = lean_unbox(v_fst_5094_);
lean_dec(v_fst_5094_);
if (v___x_5106_ == 0)
{
lean_object* v___x_5107_; 
v___x_5107_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
return v___x_5107_;
}
else
{
lean_object* v___x_5108_; 
v___x_5108_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
return v___x_5108_;
}
}
}
v___jp_5109_:
{
uint8_t v___x_5118_; 
v___x_5118_ = lean_uint64_dec_eq(v___y_5114_, v___y_5115_);
if (v___x_5118_ == 0)
{
uint8_t v___x_5119_; 
v___x_5119_ = lean_uint64_dec_lt(v___y_5114_, v___y_5115_);
if (v___x_5119_ == 0)
{
uint64_t v___x_5120_; lean_object* v___x_5121_; lean_object* v___x_5122_; 
v___x_5120_ = lean_uint64_sub(v___y_5114_, v___y_5115_);
v___x_5121_ = lean_box(v___y_5113_);
v___x_5122_ = lean_box_uint64(v___x_5120_);
v___y_5091_ = v___y_5110_;
v___y_5092_ = v___y_5112_;
v___y_5093_ = v___y_5116_;
v_fst_5094_ = v___x_5121_;
v_snd_5095_ = v___x_5122_;
goto v___jp_5090_;
}
else
{
uint64_t v___x_5123_; lean_object* v___x_5124_; lean_object* v___x_5125_; 
v___x_5123_ = lean_uint64_sub(v___y_5115_, v___y_5114_);
v___x_5124_ = lean_box(v___y_5111_);
v___x_5125_ = lean_box_uint64(v___x_5123_);
v___y_5091_ = v___y_5110_;
v___y_5092_ = v___y_5112_;
v___y_5093_ = v___y_5116_;
v_fst_5094_ = v___x_5124_;
v_snd_5095_ = v___x_5125_;
goto v___jp_5090_;
}
}
else
{
lean_object* v___x_5126_; lean_object* v___x_5127_; 
v___x_5126_ = lean_box(v___y_5117_);
v___x_5127_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_5091_ = v___y_5110_;
v___y_5092_ = v___y_5112_;
v___y_5093_ = v___y_5116_;
v_fst_5094_ = v___x_5126_;
v_snd_5095_ = v___x_5127_;
goto v___jp_5090_;
}
}
v___jp_5128_:
{
if (v___y_5136_ == 0)
{
v___y_5110_ = v___y_5129_;
v___y_5111_ = v___y_5130_;
v___y_5112_ = v___y_5132_;
v___y_5113_ = v___y_5131_;
v___y_5114_ = v___y_5133_;
v___y_5115_ = v___y_5134_;
v___y_5116_ = v___y_5135_;
v___y_5117_ = v___y_5136_;
goto v___jp_5109_;
}
else
{
uint64_t v___x_5137_; lean_object* v___x_5138_; lean_object* v___x_5139_; 
v___x_5137_ = lean_uint64_add(v___y_5133_, v___y_5134_);
v___x_5138_ = lean_box(v___y_5131_);
v___x_5139_ = lean_box_uint64(v___x_5137_);
v___y_5091_ = v___y_5129_;
v___y_5092_ = v___y_5132_;
v___y_5093_ = v___y_5135_;
v_fst_5094_ = v___x_5138_;
v_snd_5095_ = v___x_5139_;
goto v___jp_5090_;
}
}
v___jp_5140_:
{
uint8_t v___x_5149_; 
v___x_5149_ = lean_uint64_dec_le(v___y_5146_, v___y_5148_);
if (v___x_5149_ == 0)
{
uint64_t v_shift_5150_; uint64_t v___x_5151_; uint8_t v___x_5152_; 
v_shift_5150_ = lean_uint64_sub(v___y_5146_, v___y_5148_);
v___x_5151_ = 39ULL;
v___x_5152_ = lean_uint64_dec_le(v_shift_5150_, v___x_5151_);
if (v___x_5152_ == 0)
{
lean_object* v___x_5153_; 
v___x_5153_ = lean_box_uint32(v_x1_4436_);
return v___x_5153_;
}
else
{
uint64_t v___x_5154_; 
v___x_5154_ = lean_uint64_shift_left(v___y_5144_, v_shift_5150_);
if (v___y_5143_ == 0)
{
if (v___y_5142_ == 0)
{
v___y_5129_ = v___y_5141_;
v___y_5130_ = v___y_5142_;
v___y_5131_ = v___y_5143_;
v___y_5132_ = v___y_5148_;
v___y_5133_ = v___x_5154_;
v___y_5134_ = v___y_5145_;
v___y_5135_ = v___y_5147_;
v___y_5136_ = v___x_5152_;
goto v___jp_5128_;
}
else
{
v___y_5110_ = v___y_5141_;
v___y_5111_ = v___y_5142_;
v___y_5112_ = v___y_5148_;
v___y_5113_ = v___y_5143_;
v___y_5114_ = v___x_5154_;
v___y_5115_ = v___y_5145_;
v___y_5116_ = v___y_5147_;
v___y_5117_ = v___y_5143_;
goto v___jp_5109_;
}
}
else
{
v___y_5129_ = v___y_5141_;
v___y_5130_ = v___y_5142_;
v___y_5131_ = v___y_5143_;
v___y_5132_ = v___y_5148_;
v___y_5133_ = v___x_5154_;
v___y_5134_ = v___y_5145_;
v___y_5135_ = v___y_5147_;
v___y_5136_ = v___y_5142_;
goto v___jp_5128_;
}
}
}
else
{
uint64_t v_shift_5155_; uint64_t v___x_5156_; uint8_t v___x_5157_; 
v_shift_5155_ = lean_uint64_sub(v___y_5148_, v___y_5146_);
v___x_5156_ = 39ULL;
v___x_5157_ = lean_uint64_dec_le(v_shift_5155_, v___x_5156_);
if (v___x_5157_ == 0)
{
lean_object* v___x_5158_; 
v___x_5158_ = lean_box_uint32(v_x2_4437_);
return v___x_5158_;
}
else
{
uint64_t v___x_5159_; 
v___x_5159_ = lean_uint64_shift_left(v___y_5145_, v_shift_5155_);
if (v___y_5143_ == 0)
{
if (v___y_5142_ == 0)
{
v___y_4847_ = v___y_5141_;
v___y_4848_ = v___x_5159_;
v___y_4849_ = v___y_5142_;
v___y_4850_ = v___y_5144_;
v___y_4851_ = v___y_5143_;
v___y_4852_ = v___y_5146_;
v___y_4853_ = v___y_5147_;
v___y_4854_ = v___x_5157_;
goto v___jp_4846_;
}
else
{
v___y_4828_ = v___y_5141_;
v___y_4829_ = v___x_5159_;
v___y_4830_ = v___y_5142_;
v___y_4831_ = v___y_5143_;
v___y_4832_ = v___y_5144_;
v___y_4833_ = v___y_5146_;
v___y_4834_ = v___y_5147_;
v___y_4835_ = v___y_5143_;
goto v___jp_4827_;
}
}
else
{
v___y_4847_ = v___y_5141_;
v___y_4848_ = v___x_5159_;
v___y_4849_ = v___y_5142_;
v___y_4850_ = v___y_5144_;
v___y_4851_ = v___y_5143_;
v___y_4852_ = v___y_5146_;
v___y_4853_ = v___y_5147_;
v___y_4854_ = v___y_5142_;
goto v___jp_4846_;
}
}
}
}
v___jp_5160_:
{
uint64_t v___x_5169_; uint64_t v___x_5170_; uint8_t v___x_5171_; 
v___x_5169_ = lean_uint32_to_uint64(v___y_5165_);
v___x_5170_ = 0ULL;
v___x_5171_ = lean_uint64_dec_eq(v___x_5169_, v___x_5170_);
if (v___x_5171_ == 0)
{
uint64_t v___x_5172_; uint64_t v___x_5173_; 
v___x_5172_ = 1ULL;
v___x_5173_ = lean_uint64_sub(v___x_5169_, v___x_5172_);
v___y_5141_ = v___y_5161_;
v___y_5142_ = v___y_5162_;
v___y_5143_ = v___y_5164_;
v___y_5144_ = v___y_5163_;
v___y_5145_ = v___y_5166_;
v___y_5146_ = v___y_5168_;
v___y_5147_ = v___y_5167_;
v___y_5148_ = v___x_5173_;
goto v___jp_5140_;
}
else
{
v___y_5141_ = v___y_5161_;
v___y_5142_ = v___y_5162_;
v___y_5143_ = v___y_5164_;
v___y_5144_ = v___y_5163_;
v___y_5145_ = v___y_5166_;
v___y_5146_ = v___y_5168_;
v___y_5147_ = v___y_5167_;
v___y_5148_ = v___x_5170_;
goto v___jp_5140_;
}
}
v___jp_5174_:
{
uint64_t v___x_5183_; uint64_t v___x_5184_; uint8_t v___x_5185_; 
v___x_5183_ = lean_uint32_to_uint64(v___y_5177_);
v___x_5184_ = 0ULL;
v___x_5185_ = lean_uint64_dec_eq(v___x_5183_, v___x_5184_);
if (v___x_5185_ == 0)
{
uint64_t v___x_5186_; uint64_t v___x_5187_; 
v___x_5186_ = 1ULL;
v___x_5187_ = lean_uint64_sub(v___x_5183_, v___x_5186_);
v___y_5161_ = v___y_5175_;
v___y_5162_ = v___y_5176_;
v___y_5163_ = v___y_5179_;
v___y_5164_ = v___y_5178_;
v___y_5165_ = v___y_5180_;
v___y_5166_ = v___y_5182_;
v___y_5167_ = v___y_5181_;
v___y_5168_ = v___x_5187_;
goto v___jp_5160_;
}
else
{
v___y_5161_ = v___y_5175_;
v___y_5162_ = v___y_5176_;
v___y_5163_ = v___y_5179_;
v___y_5164_ = v___y_5178_;
v___y_5165_ = v___y_5180_;
v___y_5166_ = v___y_5182_;
v___y_5167_ = v___y_5181_;
v___y_5168_ = v___x_5184_;
goto v___jp_5160_;
}
}
v___jp_5188_:
{
uint32_t v___x_5196_; uint32_t v___x_5197_; uint32_t v___x_5198_; uint8_t v___x_5199_; 
v___x_5196_ = 8388607;
v___x_5197_ = lean_uint32_land(v_x2_4437_, v___x_5196_);
v___x_5198_ = 0;
v___x_5199_ = lean_uint32_dec_eq(v___y_5193_, v___x_5198_);
if (v___x_5199_ == 0)
{
uint64_t v___x_5200_; uint64_t v___x_5201_; uint64_t v___x_5202_; 
v___x_5200_ = lean_uint32_to_uint64(v___x_5197_);
v___x_5201_ = 8388608ULL;
v___x_5202_ = lean_uint64_lor(v___x_5200_, v___x_5201_);
v___y_5175_ = v___y_5189_;
v___y_5176_ = v___y_5190_;
v___y_5177_ = v___y_5192_;
v___y_5178_ = v___y_5191_;
v___y_5179_ = v___y_5195_;
v___y_5180_ = v___y_5193_;
v___y_5181_ = v___y_5194_;
v___y_5182_ = v___x_5202_;
goto v___jp_5174_;
}
else
{
uint64_t v___x_5203_; 
v___x_5203_ = lean_uint32_to_uint64(v___x_5197_);
v___y_5175_ = v___y_5189_;
v___y_5176_ = v___y_5190_;
v___y_5177_ = v___y_5192_;
v___y_5178_ = v___y_5191_;
v___y_5179_ = v___y_5195_;
v___y_5180_ = v___y_5193_;
v___y_5181_ = v___y_5194_;
v___y_5182_ = v___x_5203_;
goto v___jp_5174_;
}
}
v___jp_5204_:
{
uint32_t v___x_5211_; uint32_t v___x_5212_; uint32_t v___x_5213_; uint8_t v___x_5214_; 
v___x_5211_ = 8388607;
v___x_5212_ = lean_uint32_land(v_x1_4436_, v___x_5211_);
v___x_5213_ = 0;
v___x_5214_ = lean_uint32_dec_eq(v___y_5206_, v___x_5213_);
if (v___x_5214_ == 0)
{
uint64_t v___x_5215_; uint64_t v___x_5216_; uint64_t v___x_5217_; 
v___x_5215_ = lean_uint32_to_uint64(v___x_5212_);
v___x_5216_ = 8388608ULL;
v___x_5217_ = lean_uint64_lor(v___x_5215_, v___x_5216_);
v___y_5189_ = v___y_5205_;
v___y_5190_ = v___y_5210_;
v___y_5191_ = v___y_5207_;
v___y_5192_ = v___y_5206_;
v___y_5193_ = v___y_5208_;
v___y_5194_ = v___y_5209_;
v___y_5195_ = v___x_5217_;
goto v___jp_5188_;
}
else
{
uint64_t v___x_5218_; 
v___x_5218_ = lean_uint32_to_uint64(v___x_5212_);
v___y_5189_ = v___y_5205_;
v___y_5190_ = v___y_5210_;
v___y_5191_ = v___y_5207_;
v___y_5192_ = v___y_5206_;
v___y_5193_ = v___y_5208_;
v___y_5194_ = v___y_5209_;
v___y_5195_ = v___x_5218_;
goto v___jp_5188_;
}
}
v___jp_5219_:
{
uint32_t v___x_5226_; uint32_t v___x_5227_; uint32_t v___x_5228_; uint8_t v___x_5229_; 
v___x_5226_ = 2147483648;
v___x_5227_ = lean_uint32_land(v_x2_4437_, v___x_5226_);
v___x_5228_ = 0;
v___x_5229_ = lean_uint32_dec_eq(v___x_5227_, v___x_5228_);
if (v___x_5229_ == 0)
{
v___y_5205_ = v___y_5220_;
v___y_5206_ = v___y_5222_;
v___y_5207_ = v___y_5225_;
v___y_5208_ = v___y_5223_;
v___y_5209_ = v___y_5224_;
v___y_5210_ = v___x_4435_;
goto v___jp_5204_;
}
else
{
v___y_5205_ = v___y_5220_;
v___y_5206_ = v___y_5222_;
v___y_5207_ = v___y_5225_;
v___y_5208_ = v___y_5223_;
v___y_5209_ = v___y_5224_;
v___y_5210_ = v___y_5221_;
goto v___jp_5204_;
}
}
v___jp_5230_:
{
if (v___y_5231_ == 0)
{
uint32_t v___x_5232_; uint32_t v___x_5233_; uint32_t v___x_5234_; uint32_t v_xExponent_5235_; uint32_t v___x_5236_; uint32_t v_yExponent_5237_; uint32_t v___x_5238_; uint32_t v___x_5239_; uint32_t v___x_5240_; uint8_t v___x_5241_; 
v___x_5232_ = 23;
v___x_5233_ = lean_uint32_shift_right(v_x1_4436_, v___x_5232_);
v___x_5234_ = 255;
v_xExponent_5235_ = lean_uint32_land(v___x_5233_, v___x_5234_);
v___x_5236_ = lean_uint32_shift_right(v_x2_4437_, v___x_5232_);
v_yExponent_5237_ = lean_uint32_land(v___x_5236_, v___x_5234_);
v___x_5238_ = 2147483648;
v___x_5239_ = lean_uint32_land(v_x1_4436_, v___x_5238_);
v___x_5240_ = 0;
v___x_5241_ = lean_uint32_dec_eq(v___x_5239_, v___x_5240_);
if (v___x_5241_ == 0)
{
v___y_5220_ = v___x_5232_;
v___y_5221_ = v___y_5231_;
v___y_5222_ = v_xExponent_5235_;
v___y_5223_ = v_yExponent_5237_;
v___y_5224_ = v___x_5234_;
v___y_5225_ = v___x_4435_;
goto v___jp_5219_;
}
else
{
v___y_5220_ = v___x_5232_;
v___y_5221_ = v___y_5231_;
v___y_5222_ = v_xExponent_5235_;
v___y_5223_ = v_yExponent_5237_;
v___y_5224_ = v___x_5234_;
v___y_5225_ = v___y_5231_;
goto v___jp_5219_;
}
}
else
{
lean_object* v___x_5242_; lean_object* v___x_5243_; lean_object* v___x_5244_; lean_object* v___x_5245_; uint32_t v___x_5246_; lean_object* v___x_5247_; 
v___x_5242_ = ((lean_object*)(lp_competition_Submission_TunedAdd_add___closed__0));
v___x_5243_ = lean_uint32_to_nat(v_x1_4436_);
v___x_5244_ = lean_uint32_to_nat(v_x2_4437_);
v___x_5245_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(v___x_5242_, v___x_5243_, v___x_5244_);
v___x_5246_ = lean_uint32_of_nat(v___x_5245_);
lean_dec(v___x_5245_);
v___x_5247_ = lean_box_uint32(v___x_5246_);
return v___x_5247_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___lam__0___boxed(lean_object* v___x_5256_, lean_object* v_x1_5257_, lean_object* v_x2_5258_){
_start:
{
uint8_t v___x_3892__boxed_5259_; uint32_t v_x1_3893__boxed_5260_; uint32_t v_x2_3894__boxed_5261_; lean_object* v_res_5262_; 
v___x_3892__boxed_5259_ = lean_unbox(v___x_5256_);
v_x1_3893__boxed_5260_ = lean_unbox_uint32(v_x1_5257_);
lean_dec(v_x1_5257_);
v_x2_3894__boxed_5261_ = lean_unbox_uint32(v_x2_5258_);
lean_dec(v_x2_5258_);
v_res_5262_ = lp_competition_Submission_sum___redArg___lam__0(v___x_3892__boxed_5259_, v_x1_3893__boxed_5260_, v_x2_3894__boxed_5261_);
return v_res_5262_;
}
}
static lean_object* _init_lp_competition_Submission_sum___redArg___closed__0(void){
_start:
{
lean_object* v___x_5263_; lean_object* v___x_5264_; lean_object* v___x_5265_; 
v___x_5263_ = lean_unsigned_to_nat(0u);
v___x_5264_ = lean_unsigned_to_nat(32u);
v___x_5265_ = l_BitVec_ofNat(v___x_5264_, v___x_5263_);
return v___x_5265_;
}
}
static uint32_t _init_lp_competition_Submission_sum___redArg___closed__1(void){
_start:
{
lean_object* v___x_5266_; uint32_t v___x_5267_; 
v___x_5266_ = lean_obj_once(&lp_competition_Submission_sum___redArg___closed__0, &lp_competition_Submission_sum___redArg___closed__0_once, _init_lp_competition_Submission_sum___redArg___closed__0);
v___x_5267_ = lean_uint32_of_nat(v___x_5266_);
return v___x_5267_;
}
}
static lean_object* _init_lp_competition_Submission_sum___redArg___boxed__const__1(void){
_start:
{
uint32_t v___x_5287_; lean_object* v___x_5288_; 
v___x_5287_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_5288_ = lean_box_uint32(v___x_5287_);
return v___x_5288_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum___redArg(lean_object* v_x_5289_){
_start:
{
lean_object* v___x_5290_; uint32_t v___x_5291_; lean_object* v___x_5292_; lean_object* v___x_5293_; uint8_t v___x_5294_; 
v___x_5290_ = lean_unsigned_to_nat(0u);
v___x_5291_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_5292_ = lean_array_get_size(v_x_5289_);
v___x_5293_ = ((lean_object*)(lp_competition_Submission_sum___redArg___closed__11));
v___x_5294_ = lean_nat_dec_lt(v___x_5290_, v___x_5292_);
if (v___x_5294_ == 0)
{
lean_dec_ref(v_x_5289_);
return v___x_5291_;
}
else
{
lean_object* v___x_5295_; lean_object* v___f_5296_; uint8_t v___x_5297_; 
v___x_5295_ = lean_box(v___x_5294_);
v___f_5296_ = lean_alloc_closure((void*)(lp_competition_Submission_sum___redArg___lam__0___boxed), 3, 1);
lean_closure_set(v___f_5296_, 0, v___x_5295_);
v___x_5297_ = lean_nat_dec_le(v___x_5292_, v___x_5292_);
if (v___x_5297_ == 0)
{
if (v___x_5294_ == 0)
{
lean_dec_ref(v___f_5296_);
lean_dec_ref(v_x_5289_);
return v___x_5291_;
}
else
{
size_t v___x_5298_; size_t v___x_5299_; lean_object* v___x_5300_; lean_object* v___x_5301_; uint32_t v___x_5302_; 
v___x_5298_ = ((size_t)0ULL);
v___x_5299_ = lean_usize_of_nat(v___x_5292_);
v___x_5300_ = lp_competition_Submission_sum___redArg___boxed__const__1;
v___x_5301_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___redArg(v___x_5293_, v___f_5296_, v_x_5289_, v___x_5298_, v___x_5299_, v___x_5300_);
v___x_5302_ = lean_unbox_uint32(v___x_5301_);
lean_dec(v___x_5301_);
return v___x_5302_;
}
}
else
{
size_t v___x_5303_; size_t v___x_5304_; lean_object* v___x_5305_; lean_object* v___x_5306_; uint32_t v___x_5307_; 
v___x_5303_ = ((size_t)0ULL);
v___x_5304_ = lean_usize_of_nat(v___x_5292_);
v___x_5305_ = lp_competition_Submission_sum___redArg___boxed__const__1;
v___x_5306_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___redArg(v___x_5293_, v___f_5296_, v_x_5289_, v___x_5303_, v___x_5304_, v___x_5305_);
v___x_5307_ = lean_unbox_uint32(v___x_5306_);
lean_dec(v___x_5306_);
return v___x_5307_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___boxed(lean_object* v_x_5308_){
_start:
{
uint32_t v_res_5309_; lean_object* v_r_5310_; 
v_res_5309_ = lp_competition_Submission_sum___redArg(v_x_5308_);
v_r_5310_ = lean_box_uint32(v_res_5309_);
return v_r_5310_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object* v_n_5311_, lean_object* v_x_5312_){
_start:
{
lean_object* v___x_5313_; uint32_t v___x_5314_; lean_object* v___x_5315_; lean_object* v___x_5316_; uint8_t v___x_5317_; 
v___x_5313_ = lean_unsigned_to_nat(0u);
v___x_5314_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_5315_ = lean_array_get_size(v_x_5312_);
v___x_5316_ = ((lean_object*)(lp_competition_Submission_sum___redArg___closed__11));
v___x_5317_ = lean_nat_dec_lt(v___x_5313_, v___x_5315_);
if (v___x_5317_ == 0)
{
lean_dec_ref(v_x_5312_);
return v___x_5314_;
}
else
{
lean_object* v___x_5318_; lean_object* v___f_5319_; uint8_t v___x_5320_; 
v___x_5318_ = lean_box(v___x_5317_);
v___f_5319_ = lean_alloc_closure((void*)(lp_competition_Submission_sum___redArg___lam__0___boxed), 3, 1);
lean_closure_set(v___f_5319_, 0, v___x_5318_);
v___x_5320_ = lean_nat_dec_le(v___x_5315_, v___x_5315_);
if (v___x_5320_ == 0)
{
if (v___x_5317_ == 0)
{
lean_dec_ref(v___f_5319_);
lean_dec_ref(v_x_5312_);
return v___x_5314_;
}
else
{
size_t v___x_5321_; size_t v___x_5322_; lean_object* v___x_5323_; lean_object* v___x_5324_; uint32_t v___x_5325_; 
v___x_5321_ = ((size_t)0ULL);
v___x_5322_ = lean_usize_of_nat(v___x_5315_);
v___x_5323_ = lp_competition_Submission_sum___redArg___boxed__const__1;
v___x_5324_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___redArg(v___x_5316_, v___f_5319_, v_x_5312_, v___x_5321_, v___x_5322_, v___x_5323_);
v___x_5325_ = lean_unbox_uint32(v___x_5324_);
lean_dec(v___x_5324_);
return v___x_5325_;
}
}
else
{
size_t v___x_5326_; size_t v___x_5327_; lean_object* v___x_5328_; lean_object* v___x_5329_; uint32_t v___x_5330_; 
v___x_5326_ = ((size_t)0ULL);
v___x_5327_ = lean_usize_of_nat(v___x_5315_);
v___x_5328_ = lp_competition_Submission_sum___redArg___boxed__const__1;
v___x_5329_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___redArg(v___x_5316_, v___f_5319_, v_x_5312_, v___x_5326_, v___x_5327_, v___x_5328_);
v___x_5330_ = lean_unbox_uint32(v___x_5329_);
lean_dec(v___x_5329_);
return v___x_5330_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object* v_n_5331_, lean_object* v_x_5332_){
_start:
{
uint32_t v_res_5333_; lean_object* v_r_5334_; 
v_res_5333_ = lp_competition_Submission_sum(v_n_5331_, v_x_5332_);
lean_dec(v_n_5331_);
v_r_5334_ = lean_box_uint32(v_res_5333_);
return v_r_5334_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0(lean_object* v_fst_5335_, lean_object* v_m_5336_, lean_object* v_fst_5337_, lean_object* v_n_5338_, lean_object* v_p_5339_, lean_object* v_snd_5340_, lean_object* v_B_5341_, lean_object* v_A_5342_, uint32_t v_acc_5343_, lean_object* v_k_5344_){
_start:
{
uint32_t v___y_5346_; uint32_t v___y_5351_; uint32_t v___y_5356_; uint32_t v___y_5357_; lean_object* v___y_5363_; uint64_t v___y_5364_; uint64_t v___y_5365_; uint32_t v___y_5380_; uint32_t v___y_5381_; uint32_t v___y_5382_; uint32_t v___y_5383_; uint32_t v___y_5384_; uint32_t v___y_5393_; uint32_t v___y_5394_; lean_object* v___y_5395_; uint32_t v___y_5396_; uint32_t v___y_5397_; uint64_t v___y_5402_; uint32_t v___y_5403_; uint32_t v___y_5404_; lean_object* v___y_5405_; uint64_t v___y_5406_; uint64_t v___y_5407_; uint8_t v___y_5417_; uint32_t v___y_5418_; uint32_t v___y_5419_; lean_object* v___y_5420_; uint64_t v___y_5421_; uint64_t v___y_5422_; uint64_t v___y_5423_; uint32_t v___y_5431_; uint32_t v___y_5432_; lean_object* v___y_5433_; uint64_t v___y_5434_; uint64_t v___y_5435_; uint64_t v___y_5436_; uint64_t v___y_5442_; uint32_t v___y_5443_; uint32_t v___y_5444_; lean_object* v___y_5445_; lean_object* v___y_5446_; uint64_t v___y_5447_; uint64_t v___y_5448_; uint64_t v___y_5449_; uint64_t v___y_5513_; uint32_t v___y_5514_; uint64_t v___y_5515_; uint32_t v___y_5516_; lean_object* v___y_5517_; lean_object* v___y_5518_; uint64_t v___y_5519_; uint64_t v___y_5520_; uint64_t v___y_5521_; uint64_t v___y_5527_; uint32_t v___y_5528_; uint32_t v___y_5529_; lean_object* v___y_5530_; uint64_t v___y_5531_; lean_object* v___y_5532_; uint64_t v___y_5533_; uint64_t v___y_5534_; uint64_t v___y_5535_; uint64_t v___y_5536_; uint64_t v___y_5537_; uint64_t v___y_5542_; uint32_t v___y_5543_; uint32_t v___y_5544_; lean_object* v___y_5545_; lean_object* v___y_5546_; uint64_t v___y_5547_; uint64_t v___y_5548_; uint64_t v___y_5549_; uint64_t v___y_5550_; uint64_t v___y_5555_; uint64_t v___y_5556_; uint32_t v___y_5557_; uint64_t v___y_5558_; uint32_t v___y_5559_; lean_object* v___y_5560_; uint64_t v___y_5561_; lean_object* v___y_5562_; uint64_t v___y_5563_; uint64_t v___y_5564_; uint64_t v___y_5565_; uint64_t v___y_5570_; uint32_t v___y_5571_; uint32_t v___y_5572_; lean_object* v___y_5573_; lean_object* v___y_5574_; uint64_t v___y_5575_; uint64_t v___y_5576_; uint64_t v___y_5577_; uint64_t v___y_5578_; uint64_t v___y_5583_; uint64_t v___y_5584_; uint32_t v___y_5585_; uint32_t v___y_5586_; lean_object* v___y_5587_; uint64_t v___y_5588_; lean_object* v___y_5589_; uint64_t v___y_5590_; uint64_t v___y_5591_; uint64_t v___y_5592_; uint64_t v___y_5593_; uint64_t v___y_5598_; uint32_t v___y_5599_; uint32_t v___y_5600_; lean_object* v___y_5601_; lean_object* v___y_5602_; uint64_t v___y_5603_; uint64_t v___y_5604_; uint64_t v___y_5605_; uint64_t v___y_5606_; uint64_t v___y_5611_; uint64_t v___y_5612_; uint32_t v___y_5613_; uint32_t v___y_5614_; lean_object* v___y_5615_; uint64_t v___y_5616_; uint64_t v___y_5617_; lean_object* v___y_5618_; uint64_t v___y_5619_; uint64_t v___y_5620_; uint64_t v___y_5621_; uint64_t v___y_5626_; uint32_t v___y_5627_; uint32_t v___y_5628_; lean_object* v___y_5629_; lean_object* v___y_5630_; uint64_t v___y_5631_; uint64_t v___y_5632_; uint64_t v___y_5633_; uint64_t v___y_5634_; uint64_t v___y_5639_; uint64_t v___y_5640_; uint32_t v___y_5641_; uint32_t v___y_5642_; lean_object* v___y_5643_; uint64_t v___y_5644_; lean_object* v___y_5645_; uint64_t v___y_5646_; uint64_t v___y_5647_; uint64_t v___y_5652_; uint32_t v___y_5653_; uint32_t v___y_5654_; lean_object* v_fst_5655_; lean_object* v_snd_5656_; uint8_t v___y_5671_; uint64_t v___y_5672_; uint64_t v___y_5673_; uint8_t v___y_5674_; uint32_t v___y_5675_; uint32_t v___y_5676_; uint64_t v___y_5677_; uint8_t v___y_5678_; uint8_t v___y_5690_; uint64_t v___y_5691_; uint64_t v___y_5692_; uint32_t v___y_5693_; uint8_t v___y_5694_; uint32_t v___y_5695_; uint64_t v___y_5696_; uint8_t v___y_5697_; uint32_t v___y_5702_; uint32_t v___y_5703_; lean_object* v___y_5709_; uint64_t v___y_5710_; uint64_t v___y_5711_; uint32_t v___y_5726_; uint32_t v___y_5727_; uint32_t v___y_5728_; uint32_t v___y_5729_; uint32_t v___y_5730_; lean_object* v___y_5739_; uint32_t v___y_5740_; uint32_t v___y_5741_; uint32_t v___y_5742_; uint32_t v___y_5743_; lean_object* v___y_5748_; uint32_t v___y_5749_; uint32_t v___y_5750_; uint64_t v___y_5751_; uint64_t v___y_5752_; uint64_t v___y_5753_; lean_object* v___y_5763_; uint8_t v___y_5764_; uint32_t v___y_5765_; uint32_t v___y_5766_; uint64_t v___y_5767_; uint64_t v___y_5768_; uint64_t v___y_5769_; lean_object* v___y_5777_; uint32_t v___y_5778_; uint32_t v___y_5779_; uint64_t v___y_5780_; uint64_t v___y_5781_; uint64_t v___y_5782_; lean_object* v___y_5788_; uint64_t v___y_5789_; lean_object* v___y_5790_; uint32_t v___y_5791_; uint32_t v___y_5792_; uint64_t v___y_5793_; uint64_t v___y_5794_; uint64_t v___y_5795_; uint64_t v___y_5859_; lean_object* v___y_5860_; uint32_t v___y_5861_; lean_object* v___y_5862_; uint32_t v___y_5863_; uint64_t v___y_5864_; uint64_t v___y_5865_; uint64_t v___y_5866_; uint64_t v___y_5867_; lean_object* v___y_5873_; uint64_t v___y_5874_; lean_object* v___y_5875_; uint32_t v___y_5876_; uint64_t v___y_5877_; uint32_t v___y_5878_; uint64_t v___y_5879_; uint64_t v___y_5880_; uint64_t v___y_5881_; uint64_t v___y_5882_; uint64_t v___y_5883_; uint64_t v___y_5888_; lean_object* v___y_5889_; uint32_t v___y_5890_; lean_object* v___y_5891_; uint64_t v___y_5892_; uint32_t v___y_5893_; uint64_t v___y_5894_; uint64_t v___y_5895_; uint64_t v___y_5896_; lean_object* v___y_5901_; uint64_t v___y_5902_; uint64_t v___y_5903_; uint64_t v___y_5904_; lean_object* v___y_5905_; uint32_t v___y_5906_; uint64_t v___y_5907_; uint32_t v___y_5908_; uint64_t v___y_5909_; uint64_t v___y_5910_; uint64_t v___y_5911_; uint64_t v___y_5916_; lean_object* v___y_5917_; uint64_t v___y_5918_; uint32_t v___y_5919_; lean_object* v___y_5920_; uint32_t v___y_5921_; uint64_t v___y_5922_; uint64_t v___y_5923_; uint64_t v___y_5924_; lean_object* v___y_5929_; uint64_t v___y_5930_; lean_object* v___y_5931_; uint32_t v___y_5932_; uint32_t v___y_5933_; uint64_t v___y_5934_; uint64_t v___y_5935_; uint64_t v___y_5936_; uint64_t v___y_5937_; uint64_t v___y_5938_; uint64_t v___y_5939_; uint64_t v___y_5944_; lean_object* v___y_5945_; uint32_t v___y_5946_; lean_object* v___y_5947_; uint32_t v___y_5948_; uint64_t v___y_5949_; uint64_t v___y_5950_; uint64_t v___y_5951_; uint64_t v___y_5952_; lean_object* v___y_5957_; uint64_t v___y_5958_; lean_object* v___y_5959_; uint32_t v___y_5960_; uint64_t v___y_5961_; uint64_t v___y_5962_; uint32_t v___y_5963_; uint64_t v___y_5964_; uint64_t v___y_5965_; uint64_t v___y_5966_; uint64_t v___y_5967_; uint64_t v___y_5972_; lean_object* v___y_5973_; uint32_t v___y_5974_; lean_object* v___y_5975_; uint64_t v___y_5976_; uint32_t v___y_5977_; uint64_t v___y_5978_; uint64_t v___y_5979_; uint64_t v___y_5980_; lean_object* v___y_5985_; uint64_t v___y_5986_; lean_object* v___y_5987_; uint32_t v___y_5988_; uint32_t v___y_5989_; uint64_t v___y_5990_; uint64_t v___y_5991_; uint64_t v___y_5992_; uint64_t v___y_5993_; uint32_t v___y_5998_; uint32_t v___y_5999_; uint64_t v___y_6000_; lean_object* v_fst_6001_; lean_object* v_snd_6002_; uint8_t v___y_6017_; uint64_t v___y_6018_; uint8_t v___y_6019_; uint32_t v___y_6020_; uint32_t v___y_6021_; uint64_t v___y_6022_; uint64_t v___y_6023_; uint8_t v___y_6024_; uint64_t v___y_6036_; uint8_t v___y_6037_; uint32_t v___y_6038_; uint8_t v___y_6039_; uint32_t v___y_6040_; uint64_t v___y_6041_; uint64_t v___y_6042_; uint8_t v___y_6043_; uint64_t v___y_6048_; uint8_t v___y_6049_; uint64_t v___y_6050_; uint64_t v___y_6051_; uint8_t v___y_6052_; uint32_t v___y_6053_; uint32_t v___y_6054_; uint32_t v___y_6055_; uint64_t v___y_6056_; uint8_t v___y_6069_; uint64_t v___y_6070_; uint64_t v___y_6071_; uint8_t v___y_6072_; uint32_t v___y_6073_; uint32_t v___y_6074_; uint32_t v___y_6075_; uint32_t v___y_6076_; uint64_t v___y_6077_; uint8_t v___y_6084_; uint64_t v___y_6085_; uint32_t v___y_6086_; uint8_t v___y_6087_; uint32_t v___y_6088_; uint32_t v___y_6089_; uint32_t v___y_6090_; uint32_t v___y_6091_; uint64_t v___y_6092_; uint8_t v___y_6099_; uint8_t v___y_6100_; uint32_t v___y_6101_; uint32_t v___y_6102_; uint32_t v___y_6103_; uint32_t v___y_6104_; uint32_t v___y_6105_; uint64_t v___y_6106_; uint8_t v___y_6116_; uint32_t v___y_6117_; uint32_t v___y_6118_; uint32_t v___y_6119_; uint32_t v___y_6120_; uint32_t v___y_6121_; uint8_t v___y_6122_; uint32_t v___y_6132_; uint32_t v___y_6133_; uint32_t v___y_6134_; uint32_t v___y_6135_; uint8_t v___y_6136_; uint32_t v___y_6137_; uint8_t v___y_6138_; uint32_t v___y_6145_; uint8_t v___y_6146_; uint32_t v___y_6165_; uint32_t v___y_6175_; uint32_t v___y_6179_; uint32_t v___y_6180_; uint32_t v___y_6181_; uint32_t v___y_6185_; uint8_t v___y_6186_; uint64_t v___y_6187_; uint64_t v___y_6188_; uint32_t v___y_6200_; uint32_t v___y_6201_; uint32_t v___y_6202_; uint32_t v___y_6203_; uint32_t v___y_6204_; uint32_t v___y_6205_; uint32_t v___y_6212_; uint32_t v___y_6213_; uint32_t v___y_6214_; uint8_t v___y_6215_; uint32_t v___y_6216_; uint32_t v___y_6217_; uint32_t v___y_6221_; uint32_t v___y_6222_; uint8_t v___y_6223_; uint64_t v___y_6224_; uint32_t v___y_6225_; uint64_t v___y_6226_; uint64_t v___y_6227_; uint32_t v___y_6237_; uint32_t v___y_6238_; uint8_t v___y_6239_; uint8_t v___y_6240_; uint64_t v___y_6241_; uint64_t v___y_6242_; uint32_t v___y_6243_; uint64_t v___y_6244_; uint32_t v___y_6251_; uint32_t v___y_6252_; uint8_t v___y_6253_; uint64_t v___y_6254_; uint32_t v___y_6255_; uint64_t v___y_6256_; uint64_t v___y_6257_; uint32_t v___y_6263_; uint64_t v___y_6264_; uint64_t v___y_6265_; uint32_t v___y_6266_; uint8_t v___y_6267_; uint64_t v___y_6268_; uint32_t v___y_6269_; uint64_t v___y_6270_; uint32_t v___y_6325_; uint64_t v___y_6326_; uint32_t v___y_6327_; uint64_t v___y_6328_; uint8_t v___y_6329_; uint64_t v___y_6330_; uint64_t v___y_6331_; uint32_t v___y_6332_; uint64_t v___y_6333_; uint64_t v___y_6339_; uint32_t v___y_6340_; uint64_t v___y_6341_; uint64_t v___y_6342_; uint64_t v___y_6343_; uint32_t v___y_6344_; uint8_t v___y_6345_; uint64_t v___y_6346_; uint32_t v___y_6347_; uint64_t v___y_6348_; uint64_t v___y_6349_; uint32_t v___y_6354_; uint64_t v___y_6355_; uint32_t v___y_6356_; uint64_t v___y_6357_; uint8_t v___y_6358_; uint64_t v___y_6359_; uint32_t v___y_6360_; uint64_t v___y_6361_; uint64_t v___y_6362_; uint32_t v___y_6367_; uint64_t v___y_6368_; uint64_t v___y_6369_; uint64_t v___y_6370_; uint32_t v___y_6371_; uint8_t v___y_6372_; uint64_t v___y_6373_; uint64_t v___y_6374_; uint32_t v___y_6375_; uint64_t v___y_6376_; uint64_t v___y_6377_; uint32_t v___y_6382_; uint64_t v___y_6383_; uint32_t v___y_6384_; uint64_t v___y_6385_; uint8_t v___y_6386_; uint64_t v___y_6387_; uint32_t v___y_6388_; uint64_t v___y_6389_; uint64_t v___y_6390_; uint32_t v___y_6395_; uint64_t v___y_6396_; uint64_t v___y_6397_; uint64_t v___y_6398_; uint32_t v___y_6399_; uint8_t v___y_6400_; uint64_t v___y_6401_; uint64_t v___y_6402_; uint64_t v___y_6403_; uint32_t v___y_6404_; uint64_t v___y_6405_; uint32_t v___y_6410_; uint64_t v___y_6411_; uint64_t v___y_6412_; uint32_t v___y_6413_; uint64_t v___y_6414_; uint8_t v___y_6415_; uint64_t v___y_6416_; uint32_t v___y_6417_; uint64_t v___y_6418_; uint32_t v___y_6423_; uint64_t v___y_6424_; uint64_t v___y_6425_; uint32_t v___y_6426_; uint8_t v___y_6427_; uint64_t v___y_6428_; uint64_t v___y_6429_; uint64_t v___y_6430_; uint32_t v___y_6431_; uint64_t v___y_6432_; uint64_t v___y_6433_; uint32_t v___y_6438_; uint64_t v___y_6439_; uint32_t v___y_6440_; uint64_t v___y_6441_; uint8_t v___y_6442_; uint64_t v___y_6443_; uint32_t v___y_6444_; uint64_t v___y_6445_; uint64_t v___y_6446_; uint32_t v___y_6451_; uint64_t v___y_6452_; uint64_t v___y_6453_; uint64_t v___y_6454_; uint32_t v___y_6455_; uint8_t v___y_6456_; uint64_t v___y_6457_; uint32_t v___y_6458_; uint64_t v___y_6459_; uint32_t v___y_6463_; uint64_t v___y_6464_; uint32_t v___y_6465_; uint8_t v___y_6466_; uint64_t v___y_6467_; uint32_t v___y_6468_; uint64_t v___y_6469_; uint64_t v___y_6470_; uint32_t v___y_6481_; uint64_t v___y_6482_; uint32_t v___y_6483_; uint8_t v___y_6484_; uint64_t v___y_6485_; uint32_t v___y_6486_; uint32_t v___y_6487_; uint64_t v___y_6488_; uint32_t v___y_6495_; uint64_t v___y_6496_; uint32_t v___y_6497_; uint32_t v___y_6498_; uint8_t v___y_6499_; uint32_t v___y_6500_; uint32_t v___y_6501_; uint64_t v___y_6502_; uint32_t v___y_6509_; uint32_t v___y_6510_; uint32_t v___y_6511_; uint32_t v___y_6512_; uint8_t v___y_6513_; uint32_t v___y_6514_; uint32_t v___y_6515_; uint64_t v___y_6516_; uint32_t v___y_6524_; uint32_t v___y_6525_; uint32_t v___y_6526_; uint32_t v___y_6527_; uint32_t v___y_6528_; uint32_t v___y_6529_; uint8_t v___y_6530_; uint32_t v___y_6541_; uint32_t v___y_6542_; uint32_t v___y_6543_; uint32_t v___y_6544_; uint32_t v___y_6545_; uint32_t v___y_6546_; uint32_t v___y_6549_; uint8_t v___y_6550_; uint8_t v___y_6551_; uint32_t v___y_6552_; uint32_t v___y_6553_; uint32_t v___y_6554_; uint32_t v___y_6555_; uint32_t v___y_6556_; uint8_t v___y_6557_; uint32_t v___y_6559_; uint8_t v___y_6560_; uint32_t v___y_6561_; uint32_t v___y_6562_; uint32_t v___y_6563_; uint32_t v___y_6564_; uint32_t v___y_6565_; uint8_t v___y_6566_; lean_object* v___x_6572_; lean_object* v___x_6573_; lean_object* v___x_6574_; lean_object* v___x_6575_; lean_object* v___x_6576_; uint32_t v___y_6578_; uint32_t v___y_6579_; uint8_t v___y_6580_; uint32_t v___y_6597_; uint32_t v___y_6598_; uint32_t v___x_6605_; uint32_t v___y_6607_; lean_object* v___x_6616_; uint8_t v___x_6617_; 
v___x_6572_ = lean_nat_mul(v_fst_5335_, v_m_5336_);
v___x_6573_ = lean_nat_add(v___x_6572_, v_fst_5337_);
lean_dec(v___x_6572_);
v___x_6574_ = lean_nat_mul(v___x_6573_, v_n_5338_);
lean_dec(v___x_6573_);
v___x_6575_ = lean_nat_add(v___x_6574_, v_k_5344_);
lean_dec(v___x_6574_);
v___x_6576_ = ((lean_object*)(lp_competition_Submission_TunedAdd_add___closed__0));
v___x_6605_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_6616_ = lean_array_get_size(v_A_5342_);
v___x_6617_ = lean_nat_dec_lt(v___x_6575_, v___x_6616_);
if (v___x_6617_ == 0)
{
lean_dec(v___x_6575_);
v___y_6607_ = v___x_6605_;
goto v___jp_6606_;
}
else
{
lean_object* v___x_6618_; uint32_t v___x_6619_; 
v___x_6618_ = lean_array_fget_borrowed(v_A_5342_, v___x_6575_);
lean_dec(v___x_6575_);
v___x_6619_ = lean_unbox_uint32(v___x_6618_);
v___y_6607_ = v___x_6619_;
goto v___jp_6606_;
}
v___jp_5345_:
{
uint32_t v___x_5347_; uint32_t v___x_5348_; lean_object* v___x_5349_; 
v___x_5347_ = 8388608;
v___x_5348_ = lean_uint32_lor(v___y_5346_, v___x_5347_);
v___x_5349_ = lean_box_uint32(v___x_5348_);
return v___x_5349_;
}
v___jp_5350_:
{
uint32_t v___x_5352_; uint32_t v___x_5353_; lean_object* v___x_5354_; 
v___x_5352_ = 8388608;
v___x_5353_ = lean_uint32_lor(v___y_5351_, v___x_5352_);
v___x_5354_ = lean_box_uint32(v___x_5353_);
return v___x_5354_;
}
v___jp_5355_:
{
uint32_t v___x_5358_; uint32_t v___x_5359_; uint32_t v___x_5360_; lean_object* v___x_5361_; 
v___x_5358_ = 8388607;
v___x_5359_ = lean_uint32_land(v___y_5356_, v___x_5358_);
v___x_5360_ = lean_uint32_lor(v___y_5357_, v___x_5359_);
v___x_5361_ = lean_box_uint32(v___x_5360_);
return v___x_5361_;
}
v___jp_5362_:
{
uint8_t v___x_5366_; 
v___x_5366_ = lean_uint64_dec_eq(v___y_5365_, v___y_5364_);
if (v___x_5366_ == 0)
{
uint64_t v___x_5367_; uint8_t v___x_5368_; 
v___x_5367_ = 8388608ULL;
v___x_5368_ = lean_uint64_dec_eq(v___y_5365_, v___x_5367_);
if (v___x_5368_ == 0)
{
uint32_t v___x_5369_; uint8_t v___x_5370_; 
v___x_5369_ = lean_uint64_to_uint32(v___y_5365_);
v___x_5370_ = lean_unbox(v___y_5363_);
lean_dec(v___y_5363_);
if (v___x_5370_ == 0)
{
uint32_t v___x_5371_; 
v___x_5371_ = 0;
v___y_5356_ = v___x_5369_;
v___y_5357_ = v___x_5371_;
goto v___jp_5355_;
}
else
{
uint32_t v___x_5372_; 
v___x_5372_ = 2147483648;
v___y_5356_ = v___x_5369_;
v___y_5357_ = v___x_5372_;
goto v___jp_5355_;
}
}
else
{
uint8_t v___x_5373_; 
v___x_5373_ = lean_unbox(v___y_5363_);
lean_dec(v___y_5363_);
if (v___x_5373_ == 0)
{
uint32_t v___x_5374_; 
v___x_5374_ = 0;
v___y_5351_ = v___x_5374_;
goto v___jp_5350_;
}
else
{
uint32_t v___x_5375_; 
v___x_5375_ = 2147483648;
v___y_5351_ = v___x_5375_;
goto v___jp_5350_;
}
}
}
else
{
uint8_t v___x_5376_; 
v___x_5376_ = lean_unbox(v___y_5363_);
lean_dec(v___y_5363_);
if (v___x_5376_ == 0)
{
lean_object* v___x_5377_; 
v___x_5377_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
return v___x_5377_;
}
else
{
lean_object* v___x_5378_; 
v___x_5378_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
return v___x_5378_;
}
}
}
v___jp_5379_:
{
uint32_t v___x_5385_; uint32_t v___x_5386_; uint32_t v___x_5387_; uint32_t v___x_5388_; uint32_t v___x_5389_; uint32_t v___x_5390_; lean_object* v___x_5391_; 
v___x_5385_ = lean_uint32_land(v___y_5383_, v___y_5382_);
v___x_5386_ = lean_uint32_shift_left(v___x_5385_, v___y_5380_);
v___x_5387_ = lean_uint32_lor(v___y_5384_, v___x_5386_);
v___x_5388_ = 8388607;
v___x_5389_ = lean_uint32_land(v___y_5381_, v___x_5388_);
v___x_5390_ = lean_uint32_lor(v___x_5387_, v___x_5389_);
v___x_5391_ = lean_box_uint32(v___x_5390_);
return v___x_5391_;
}
v___jp_5392_:
{
uint8_t v___x_5398_; 
v___x_5398_ = lean_unbox(v___y_5395_);
lean_dec(v___y_5395_);
if (v___x_5398_ == 0)
{
uint32_t v___x_5399_; 
v___x_5399_ = 0;
v___y_5380_ = v___y_5393_;
v___y_5381_ = v___y_5397_;
v___y_5382_ = v___y_5394_;
v___y_5383_ = v___y_5396_;
v___y_5384_ = v___x_5399_;
goto v___jp_5379_;
}
else
{
uint32_t v___x_5400_; 
v___x_5400_ = 2147483648;
v___y_5380_ = v___y_5393_;
v___y_5381_ = v___y_5397_;
v___y_5382_ = v___y_5394_;
v___y_5383_ = v___y_5396_;
v___y_5384_ = v___x_5400_;
goto v___jp_5379_;
}
}
v___jp_5401_:
{
uint64_t v___x_5408_; uint64_t v_encodedExponent_5409_; uint32_t v___x_5410_; uint64_t v___x_5411_; uint8_t v___x_5412_; 
v___x_5408_ = 171ULL;
v_encodedExponent_5409_ = lean_uint64_sub(v___y_5402_, v___x_5408_);
v___x_5410_ = lean_uint64_to_uint32(v_encodedExponent_5409_);
v___x_5411_ = 8388608ULL;
v___x_5412_ = lean_uint64_dec_lt(v___y_5407_, v___x_5411_);
if (v___x_5412_ == 0)
{
uint64_t v___x_5413_; uint32_t v___x_5414_; 
v___x_5413_ = lean_uint64_sub(v___y_5407_, v___x_5411_);
v___x_5414_ = lean_uint64_to_uint32(v___x_5413_);
v___y_5393_ = v___y_5403_;
v___y_5394_ = v___y_5404_;
v___y_5395_ = v___y_5405_;
v___y_5396_ = v___x_5410_;
v___y_5397_ = v___x_5414_;
goto v___jp_5392_;
}
else
{
uint32_t v___x_5415_; 
v___x_5415_ = lean_uint64_to_uint32(v___y_5406_);
v___y_5393_ = v___y_5403_;
v___y_5394_ = v___y_5404_;
v___y_5395_ = v___y_5405_;
v___y_5396_ = v___x_5410_;
v___y_5397_ = v___x_5415_;
goto v___jp_5392_;
}
}
v___jp_5416_:
{
uint64_t v___x_5424_; uint8_t v___x_5425_; 
v___x_5424_ = 425ULL;
v___x_5425_ = lean_uint64_dec_lt(v___x_5424_, v___y_5423_);
if (v___x_5425_ == 0)
{
if (v___y_5417_ == 0)
{
v___y_5402_ = v___y_5423_;
v___y_5403_ = v___y_5418_;
v___y_5404_ = v___y_5419_;
v___y_5405_ = v___y_5420_;
v___y_5406_ = v___y_5421_;
v___y_5407_ = v___y_5422_;
goto v___jp_5401_;
}
else
{
uint64_t v___x_5426_; 
v___x_5426_ = 8388608ULL;
v___y_5402_ = v___y_5423_;
v___y_5403_ = v___y_5418_;
v___y_5404_ = v___y_5419_;
v___y_5405_ = v___y_5420_;
v___y_5406_ = v___y_5421_;
v___y_5407_ = v___x_5426_;
goto v___jp_5401_;
}
}
else
{
uint8_t v___x_5427_; 
v___x_5427_ = lean_unbox(v___y_5420_);
lean_dec(v___y_5420_);
if (v___x_5427_ == 0)
{
lean_object* v___x_5428_; 
v___x_5428_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__1;
return v___x_5428_;
}
else
{
lean_object* v___x_5429_; 
v___x_5429_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__2;
return v___x_5429_;
}
}
}
v___jp_5430_:
{
uint64_t v___x_5437_; uint8_t v_carry_5438_; 
v___x_5437_ = 16777216ULL;
v_carry_5438_ = lean_uint64_dec_eq(v___y_5436_, v___x_5437_);
if (v_carry_5438_ == 0)
{
v___y_5417_ = v_carry_5438_;
v___y_5418_ = v___y_5431_;
v___y_5419_ = v___y_5432_;
v___y_5420_ = v___y_5433_;
v___y_5421_ = v___y_5434_;
v___y_5422_ = v___y_5436_;
v___y_5423_ = v___y_5435_;
goto v___jp_5416_;
}
else
{
uint64_t v___x_5439_; uint64_t v___x_5440_; 
v___x_5439_ = 1ULL;
v___x_5440_ = lean_uint64_add(v___y_5435_, v___x_5439_);
v___y_5417_ = v_carry_5438_;
v___y_5418_ = v___y_5431_;
v___y_5419_ = v___y_5432_;
v___y_5420_ = v___y_5433_;
v___y_5421_ = v___y_5434_;
v___y_5422_ = v___y_5436_;
v___y_5423_ = v___x_5440_;
goto v___jp_5416_;
}
}
v___jp_5441_:
{
uint64_t v_position_5450_; uint64_t v___x_5451_; uint8_t v___x_5452_; 
v_position_5450_ = lean_uint64_add(v___y_5449_, v___y_5448_);
v___x_5451_ = 172ULL;
v___x_5452_ = lean_uint64_dec_lt(v_position_5450_, v___x_5451_);
if (v___x_5452_ == 0)
{
uint64_t v___x_5453_; uint8_t v___x_5454_; 
v___x_5453_ = 23ULL;
v___x_5454_ = lean_uint64_dec_lt(v___y_5449_, v___x_5453_);
if (v___x_5454_ == 0)
{
uint64_t v___x_5455_; uint8_t v___x_5456_; 
v___x_5455_ = lean_uint64_sub(v___y_5449_, v___x_5453_);
v___x_5456_ = lean_uint64_dec_eq(v___x_5455_, v___y_5447_);
if (v___x_5456_ == 0)
{
uint64_t v___x_5457_; uint8_t v___x_5458_; 
v___x_5457_ = 64ULL;
v___x_5458_ = lean_uint64_dec_lt(v___x_5455_, v___x_5457_);
if (v___x_5458_ == 0)
{
uint8_t v___x_5459_; 
v___x_5459_ = lean_uint64_dec_eq(v___x_5455_, v___x_5457_);
if (v___x_5459_ == 0)
{
lean_dec(v___y_5446_);
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v___y_5447_;
goto v___jp_5430_;
}
else
{
uint64_t v___x_5460_; uint64_t v___x_5461_; uint8_t v___x_5462_; 
v___x_5460_ = 9223372036854775808ULL;
v___x_5461_ = lean_unbox_uint64(v___y_5446_);
lean_dec(v___y_5446_);
v___x_5462_ = lean_uint64_dec_lt(v___x_5460_, v___x_5461_);
if (v___x_5462_ == 0)
{
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v___y_5447_;
goto v___jp_5430_;
}
else
{
uint64_t v___x_5463_; 
v___x_5463_ = 1ULL;
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v___x_5463_;
goto v___jp_5430_;
}
}
}
else
{
uint64_t v___x_5464_; uint64_t v_quotient_5465_; uint64_t v___x_5466_; uint64_t v___x_5467_; uint64_t v___x_5468_; uint64_t v___x_5469_; uint64_t v_remainder_5470_; uint64_t v___x_5471_; uint64_t v_half_5472_; uint8_t v___x_5473_; 
v___x_5464_ = lean_unbox_uint64(v___y_5446_);
v_quotient_5465_ = lean_uint64_shift_right(v___x_5464_, v___x_5455_);
v___x_5466_ = 1ULL;
v___x_5467_ = lean_uint64_shift_left(v___x_5466_, v___x_5455_);
v___x_5468_ = lean_uint64_sub(v___x_5467_, v___x_5466_);
v___x_5469_ = lean_unbox_uint64(v___y_5446_);
lean_dec(v___y_5446_);
v_remainder_5470_ = lean_uint64_land(v___x_5469_, v___x_5468_);
v___x_5471_ = lean_uint64_sub(v___x_5455_, v___x_5466_);
v_half_5472_ = lean_uint64_shift_left(v___x_5466_, v___x_5471_);
v___x_5473_ = lean_uint64_dec_lt(v_remainder_5470_, v_half_5472_);
if (v___x_5473_ == 0)
{
uint8_t v___x_5474_; 
v___x_5474_ = lean_uint64_dec_lt(v_half_5472_, v_remainder_5470_);
if (v___x_5474_ == 0)
{
uint64_t v___x_5475_; uint8_t v___x_5476_; 
v___x_5475_ = lean_uint64_land(v_quotient_5465_, v___x_5466_);
v___x_5476_ = lean_uint64_dec_eq(v___x_5475_, v___y_5447_);
if (v___x_5476_ == 0)
{
uint64_t v___x_5477_; 
v___x_5477_ = lean_uint64_add(v_quotient_5465_, v___x_5466_);
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v___x_5477_;
goto v___jp_5430_;
}
else
{
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v_quotient_5465_;
goto v___jp_5430_;
}
}
else
{
uint64_t v___x_5478_; 
v___x_5478_ = lean_uint64_add(v_quotient_5465_, v___x_5466_);
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v___x_5478_;
goto v___jp_5430_;
}
}
else
{
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v_quotient_5465_;
goto v___jp_5430_;
}
}
}
else
{
uint64_t v___x_5479_; 
v___x_5479_ = lean_unbox_uint64(v___y_5446_);
lean_dec(v___y_5446_);
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v___x_5479_;
goto v___jp_5430_;
}
}
else
{
uint64_t v___x_5480_; uint64_t v___x_5481_; uint64_t v___x_5482_; 
v___x_5480_ = lean_uint64_sub(v___x_5453_, v___y_5449_);
v___x_5481_ = lean_unbox_uint64(v___y_5446_);
lean_dec(v___y_5446_);
v___x_5482_ = lean_uint64_shift_left(v___x_5481_, v___x_5480_);
v___y_5431_ = v___y_5443_;
v___y_5432_ = v___y_5444_;
v___y_5433_ = v___y_5445_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v_position_5450_;
v___y_5436_ = v___x_5482_;
goto v___jp_5430_;
}
}
else
{
uint8_t v___x_5483_; 
v___x_5483_ = lean_uint64_dec_lt(v___y_5448_, v___y_5442_);
if (v___x_5483_ == 0)
{
uint64_t v___x_5484_; uint64_t v___x_5485_; uint64_t v___x_5486_; 
v___x_5484_ = lean_uint64_sub(v___y_5448_, v___y_5442_);
v___x_5485_ = lean_unbox_uint64(v___y_5446_);
lean_dec(v___y_5446_);
v___x_5486_ = lean_uint64_shift_left(v___x_5485_, v___x_5484_);
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v___x_5486_;
goto v___jp_5362_;
}
else
{
uint64_t v___x_5487_; uint8_t v___x_5488_; 
v___x_5487_ = lean_uint64_sub(v___y_5442_, v___y_5448_);
v___x_5488_ = lean_uint64_dec_eq(v___x_5487_, v___y_5447_);
if (v___x_5488_ == 0)
{
uint64_t v___x_5489_; uint8_t v___x_5490_; 
v___x_5489_ = 64ULL;
v___x_5490_ = lean_uint64_dec_lt(v___x_5487_, v___x_5489_);
if (v___x_5490_ == 0)
{
uint8_t v___x_5491_; 
v___x_5491_ = lean_uint64_dec_eq(v___x_5487_, v___x_5489_);
if (v___x_5491_ == 0)
{
lean_dec(v___y_5446_);
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v___y_5447_;
goto v___jp_5362_;
}
else
{
uint64_t v___x_5492_; uint64_t v___x_5493_; uint8_t v___x_5494_; 
v___x_5492_ = 9223372036854775808ULL;
v___x_5493_ = lean_unbox_uint64(v___y_5446_);
lean_dec(v___y_5446_);
v___x_5494_ = lean_uint64_dec_lt(v___x_5492_, v___x_5493_);
if (v___x_5494_ == 0)
{
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v___y_5447_;
goto v___jp_5362_;
}
else
{
uint64_t v___x_5495_; 
v___x_5495_ = 1ULL;
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v___x_5495_;
goto v___jp_5362_;
}
}
}
else
{
uint64_t v___x_5496_; uint64_t v_quotient_5497_; uint64_t v___x_5498_; uint64_t v___x_5499_; uint64_t v___x_5500_; uint64_t v___x_5501_; uint64_t v_remainder_5502_; uint64_t v___x_5503_; uint64_t v_half_5504_; uint8_t v___x_5505_; 
v___x_5496_ = lean_unbox_uint64(v___y_5446_);
v_quotient_5497_ = lean_uint64_shift_right(v___x_5496_, v___x_5487_);
v___x_5498_ = 1ULL;
v___x_5499_ = lean_uint64_shift_left(v___x_5498_, v___x_5487_);
v___x_5500_ = lean_uint64_sub(v___x_5499_, v___x_5498_);
v___x_5501_ = lean_unbox_uint64(v___y_5446_);
lean_dec(v___y_5446_);
v_remainder_5502_ = lean_uint64_land(v___x_5501_, v___x_5500_);
v___x_5503_ = lean_uint64_sub(v___x_5487_, v___x_5498_);
v_half_5504_ = lean_uint64_shift_left(v___x_5498_, v___x_5503_);
v___x_5505_ = lean_uint64_dec_lt(v_remainder_5502_, v_half_5504_);
if (v___x_5505_ == 0)
{
uint8_t v___x_5506_; 
v___x_5506_ = lean_uint64_dec_lt(v_half_5504_, v_remainder_5502_);
if (v___x_5506_ == 0)
{
uint64_t v___x_5507_; uint8_t v___x_5508_; 
v___x_5507_ = lean_uint64_land(v_quotient_5497_, v___x_5498_);
v___x_5508_ = lean_uint64_dec_eq(v___x_5507_, v___y_5447_);
if (v___x_5508_ == 0)
{
uint64_t v___x_5509_; 
v___x_5509_ = lean_uint64_add(v_quotient_5497_, v___x_5498_);
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v___x_5509_;
goto v___jp_5362_;
}
else
{
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v_quotient_5497_;
goto v___jp_5362_;
}
}
else
{
uint64_t v___x_5510_; 
v___x_5510_ = lean_uint64_add(v_quotient_5497_, v___x_5498_);
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v___x_5510_;
goto v___jp_5362_;
}
}
else
{
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v_quotient_5497_;
goto v___jp_5362_;
}
}
}
else
{
uint64_t v___x_5511_; 
v___x_5511_ = lean_unbox_uint64(v___y_5446_);
lean_dec(v___y_5446_);
v___y_5363_ = v___y_5445_;
v___y_5364_ = v___y_5447_;
v___y_5365_ = v___x_5511_;
goto v___jp_5362_;
}
}
}
}
v___jp_5512_:
{
uint64_t v___x_5522_; uint64_t v___x_5523_; uint8_t v___x_5524_; 
v___x_5522_ = 1ULL;
v___x_5523_ = lean_uint64_shift_right(v___y_5515_, v___x_5522_);
v___x_5524_ = lean_uint64_dec_eq(v___x_5523_, v___y_5519_);
if (v___x_5524_ == 0)
{
uint64_t v___x_5525_; 
v___x_5525_ = lean_uint64_add(v___y_5521_, v___x_5522_);
v___y_5442_ = v___y_5513_;
v___y_5443_ = v___y_5514_;
v___y_5444_ = v___y_5516_;
v___y_5445_ = v___y_5517_;
v___y_5446_ = v___y_5518_;
v___y_5447_ = v___y_5519_;
v___y_5448_ = v___y_5520_;
v___y_5449_ = v___x_5525_;
goto v___jp_5441_;
}
else
{
v___y_5442_ = v___y_5513_;
v___y_5443_ = v___y_5514_;
v___y_5444_ = v___y_5516_;
v___y_5445_ = v___y_5517_;
v___y_5446_ = v___y_5518_;
v___y_5447_ = v___y_5519_;
v___y_5448_ = v___y_5520_;
v___y_5449_ = v___y_5521_;
goto v___jp_5441_;
}
}
v___jp_5526_:
{
uint64_t v___x_5538_; uint8_t v___x_5539_; 
v___x_5538_ = lean_uint64_shift_right(v___y_5536_, v___y_5534_);
v___x_5539_ = lean_uint64_dec_eq(v___x_5538_, v___y_5531_);
if (v___x_5539_ == 0)
{
uint64_t v___x_5540_; 
v___x_5540_ = lean_uint64_add(v___y_5533_, v___y_5534_);
v___y_5513_ = v___y_5527_;
v___y_5514_ = v___y_5528_;
v___y_5515_ = v___y_5537_;
v___y_5516_ = v___y_5529_;
v___y_5517_ = v___y_5530_;
v___y_5518_ = v___y_5532_;
v___y_5519_ = v___y_5531_;
v___y_5520_ = v___y_5535_;
v___y_5521_ = v___x_5540_;
goto v___jp_5512_;
}
else
{
v___y_5513_ = v___y_5527_;
v___y_5514_ = v___y_5528_;
v___y_5515_ = v___y_5537_;
v___y_5516_ = v___y_5529_;
v___y_5517_ = v___y_5530_;
v___y_5518_ = v___y_5532_;
v___y_5519_ = v___y_5531_;
v___y_5520_ = v___y_5535_;
v___y_5521_ = v___y_5533_;
goto v___jp_5512_;
}
}
v___jp_5541_:
{
uint64_t v___x_5551_; uint64_t v___x_5552_; uint8_t v___x_5553_; 
v___x_5551_ = 2ULL;
v___x_5552_ = lean_uint64_shift_right(v___y_5549_, v___x_5551_);
v___x_5553_ = lean_uint64_dec_eq(v___x_5552_, v___y_5547_);
if (v___x_5553_ == 0)
{
v___y_5527_ = v___y_5542_;
v___y_5528_ = v___y_5543_;
v___y_5529_ = v___y_5544_;
v___y_5530_ = v___y_5545_;
v___y_5531_ = v___y_5547_;
v___y_5532_ = v___y_5546_;
v___y_5533_ = v___y_5550_;
v___y_5534_ = v___x_5551_;
v___y_5535_ = v___y_5548_;
v___y_5536_ = v___y_5549_;
v___y_5537_ = v___x_5552_;
goto v___jp_5526_;
}
else
{
v___y_5527_ = v___y_5542_;
v___y_5528_ = v___y_5543_;
v___y_5529_ = v___y_5544_;
v___y_5530_ = v___y_5545_;
v___y_5531_ = v___y_5547_;
v___y_5532_ = v___y_5546_;
v___y_5533_ = v___y_5550_;
v___y_5534_ = v___x_5551_;
v___y_5535_ = v___y_5548_;
v___y_5536_ = v___y_5549_;
v___y_5537_ = v___y_5549_;
goto v___jp_5526_;
}
}
v___jp_5554_:
{
uint64_t v___x_5566_; uint8_t v___x_5567_; 
v___x_5566_ = lean_uint64_shift_right(v___y_5563_, v___y_5558_);
v___x_5567_ = lean_uint64_dec_eq(v___x_5566_, v___y_5561_);
if (v___x_5567_ == 0)
{
uint64_t v___x_5568_; 
v___x_5568_ = lean_uint64_add(v___y_5555_, v___y_5558_);
v___y_5542_ = v___y_5556_;
v___y_5543_ = v___y_5557_;
v___y_5544_ = v___y_5559_;
v___y_5545_ = v___y_5560_;
v___y_5546_ = v___y_5562_;
v___y_5547_ = v___y_5561_;
v___y_5548_ = v___y_5564_;
v___y_5549_ = v___y_5565_;
v___y_5550_ = v___x_5568_;
goto v___jp_5541_;
}
else
{
v___y_5542_ = v___y_5556_;
v___y_5543_ = v___y_5557_;
v___y_5544_ = v___y_5559_;
v___y_5545_ = v___y_5560_;
v___y_5546_ = v___y_5562_;
v___y_5547_ = v___y_5561_;
v___y_5548_ = v___y_5564_;
v___y_5549_ = v___y_5565_;
v___y_5550_ = v___y_5555_;
goto v___jp_5541_;
}
}
v___jp_5569_:
{
uint64_t v___x_5579_; uint64_t v___x_5580_; uint8_t v___x_5581_; 
v___x_5579_ = 4ULL;
v___x_5580_ = lean_uint64_shift_right(v___y_5576_, v___x_5579_);
v___x_5581_ = lean_uint64_dec_eq(v___x_5580_, v___y_5575_);
if (v___x_5581_ == 0)
{
v___y_5555_ = v___y_5578_;
v___y_5556_ = v___y_5570_;
v___y_5557_ = v___y_5571_;
v___y_5558_ = v___x_5579_;
v___y_5559_ = v___y_5572_;
v___y_5560_ = v___y_5573_;
v___y_5561_ = v___y_5575_;
v___y_5562_ = v___y_5574_;
v___y_5563_ = v___y_5576_;
v___y_5564_ = v___y_5577_;
v___y_5565_ = v___x_5580_;
goto v___jp_5554_;
}
else
{
v___y_5555_ = v___y_5578_;
v___y_5556_ = v___y_5570_;
v___y_5557_ = v___y_5571_;
v___y_5558_ = v___x_5579_;
v___y_5559_ = v___y_5572_;
v___y_5560_ = v___y_5573_;
v___y_5561_ = v___y_5575_;
v___y_5562_ = v___y_5574_;
v___y_5563_ = v___y_5576_;
v___y_5564_ = v___y_5577_;
v___y_5565_ = v___y_5576_;
goto v___jp_5554_;
}
}
v___jp_5582_:
{
uint64_t v___x_5594_; uint8_t v___x_5595_; 
v___x_5594_ = lean_uint64_shift_right(v___y_5592_, v___y_5583_);
v___x_5595_ = lean_uint64_dec_eq(v___x_5594_, v___y_5588_);
if (v___x_5595_ == 0)
{
uint64_t v___x_5596_; 
v___x_5596_ = lean_uint64_add(v___y_5590_, v___y_5583_);
v___y_5570_ = v___y_5584_;
v___y_5571_ = v___y_5585_;
v___y_5572_ = v___y_5586_;
v___y_5573_ = v___y_5587_;
v___y_5574_ = v___y_5589_;
v___y_5575_ = v___y_5588_;
v___y_5576_ = v___y_5593_;
v___y_5577_ = v___y_5591_;
v___y_5578_ = v___x_5596_;
goto v___jp_5569_;
}
else
{
v___y_5570_ = v___y_5584_;
v___y_5571_ = v___y_5585_;
v___y_5572_ = v___y_5586_;
v___y_5573_ = v___y_5587_;
v___y_5574_ = v___y_5589_;
v___y_5575_ = v___y_5588_;
v___y_5576_ = v___y_5593_;
v___y_5577_ = v___y_5591_;
v___y_5578_ = v___y_5590_;
goto v___jp_5569_;
}
}
v___jp_5597_:
{
uint64_t v___x_5607_; uint64_t v___x_5608_; uint8_t v___x_5609_; 
v___x_5607_ = 8ULL;
v___x_5608_ = lean_uint64_shift_right(v___y_5605_, v___x_5607_);
v___x_5609_ = lean_uint64_dec_eq(v___x_5608_, v___y_5603_);
if (v___x_5609_ == 0)
{
v___y_5583_ = v___x_5607_;
v___y_5584_ = v___y_5598_;
v___y_5585_ = v___y_5599_;
v___y_5586_ = v___y_5600_;
v___y_5587_ = v___y_5601_;
v___y_5588_ = v___y_5603_;
v___y_5589_ = v___y_5602_;
v___y_5590_ = v___y_5606_;
v___y_5591_ = v___y_5604_;
v___y_5592_ = v___y_5605_;
v___y_5593_ = v___x_5608_;
goto v___jp_5582_;
}
else
{
v___y_5583_ = v___x_5607_;
v___y_5584_ = v___y_5598_;
v___y_5585_ = v___y_5599_;
v___y_5586_ = v___y_5600_;
v___y_5587_ = v___y_5601_;
v___y_5588_ = v___y_5603_;
v___y_5589_ = v___y_5602_;
v___y_5590_ = v___y_5606_;
v___y_5591_ = v___y_5604_;
v___y_5592_ = v___y_5605_;
v___y_5593_ = v___y_5605_;
goto v___jp_5582_;
}
}
v___jp_5610_:
{
uint64_t v___x_5622_; uint8_t v___x_5623_; 
v___x_5622_ = lean_uint64_shift_right(v___y_5619_, v___y_5611_);
v___x_5623_ = lean_uint64_dec_eq(v___x_5622_, v___y_5617_);
if (v___x_5623_ == 0)
{
uint64_t v___x_5624_; 
v___x_5624_ = lean_uint64_add(v___y_5616_, v___y_5611_);
v___y_5598_ = v___y_5612_;
v___y_5599_ = v___y_5613_;
v___y_5600_ = v___y_5614_;
v___y_5601_ = v___y_5615_;
v___y_5602_ = v___y_5618_;
v___y_5603_ = v___y_5617_;
v___y_5604_ = v___y_5620_;
v___y_5605_ = v___y_5621_;
v___y_5606_ = v___x_5624_;
goto v___jp_5597_;
}
else
{
v___y_5598_ = v___y_5612_;
v___y_5599_ = v___y_5613_;
v___y_5600_ = v___y_5614_;
v___y_5601_ = v___y_5615_;
v___y_5602_ = v___y_5618_;
v___y_5603_ = v___y_5617_;
v___y_5604_ = v___y_5620_;
v___y_5605_ = v___y_5621_;
v___y_5606_ = v___y_5616_;
goto v___jp_5597_;
}
}
v___jp_5625_:
{
uint64_t v___x_5635_; uint64_t v___x_5636_; uint8_t v___x_5637_; 
v___x_5635_ = 16ULL;
v___x_5636_ = lean_uint64_shift_right(v___y_5632_, v___x_5635_);
v___x_5637_ = lean_uint64_dec_eq(v___x_5636_, v___y_5631_);
if (v___x_5637_ == 0)
{
v___y_5611_ = v___x_5635_;
v___y_5612_ = v___y_5626_;
v___y_5613_ = v___y_5627_;
v___y_5614_ = v___y_5628_;
v___y_5615_ = v___y_5629_;
v___y_5616_ = v___y_5634_;
v___y_5617_ = v___y_5631_;
v___y_5618_ = v___y_5630_;
v___y_5619_ = v___y_5632_;
v___y_5620_ = v___y_5633_;
v___y_5621_ = v___x_5636_;
goto v___jp_5610_;
}
else
{
v___y_5611_ = v___x_5635_;
v___y_5612_ = v___y_5626_;
v___y_5613_ = v___y_5627_;
v___y_5614_ = v___y_5628_;
v___y_5615_ = v___y_5629_;
v___y_5616_ = v___y_5634_;
v___y_5617_ = v___y_5631_;
v___y_5618_ = v___y_5630_;
v___y_5619_ = v___y_5632_;
v___y_5620_ = v___y_5633_;
v___y_5621_ = v___y_5632_;
goto v___jp_5610_;
}
}
v___jp_5638_:
{
uint64_t v___x_5648_; uint64_t v___x_5649_; uint8_t v___x_5650_; 
v___x_5648_ = lean_unbox_uint64(v___y_5645_);
v___x_5649_ = lean_uint64_shift_right(v___x_5648_, v___y_5639_);
v___x_5650_ = lean_uint64_dec_eq(v___x_5649_, v___y_5644_);
if (v___x_5650_ == 0)
{
v___y_5626_ = v___y_5640_;
v___y_5627_ = v___y_5641_;
v___y_5628_ = v___y_5642_;
v___y_5629_ = v___y_5643_;
v___y_5630_ = v___y_5645_;
v___y_5631_ = v___y_5644_;
v___y_5632_ = v___y_5647_;
v___y_5633_ = v___y_5646_;
v___y_5634_ = v___y_5639_;
goto v___jp_5625_;
}
else
{
v___y_5626_ = v___y_5640_;
v___y_5627_ = v___y_5641_;
v___y_5628_ = v___y_5642_;
v___y_5629_ = v___y_5643_;
v___y_5630_ = v___y_5645_;
v___y_5631_ = v___y_5644_;
v___y_5632_ = v___y_5647_;
v___y_5633_ = v___y_5646_;
v___y_5634_ = v___y_5644_;
goto v___jp_5625_;
}
}
v___jp_5651_:
{
uint64_t v___x_5657_; uint64_t v___x_5658_; uint8_t v___x_5659_; 
v___x_5657_ = 0ULL;
v___x_5658_ = lean_unbox_uint64(v_snd_5656_);
v___x_5659_ = lean_uint64_dec_eq(v___x_5658_, v___x_5657_);
if (v___x_5659_ == 0)
{
uint64_t v___x_5660_; uint64_t v___x_5661_; uint64_t v___x_5662_; uint64_t v___x_5663_; uint64_t v___x_5664_; uint8_t v___x_5665_; 
v___x_5660_ = 149ULL;
v___x_5661_ = lean_uint64_add(v___y_5652_, v___x_5660_);
v___x_5662_ = 32ULL;
v___x_5663_ = lean_unbox_uint64(v_snd_5656_);
v___x_5664_ = lean_uint64_shift_right(v___x_5663_, v___x_5662_);
v___x_5665_ = lean_uint64_dec_eq(v___x_5664_, v___x_5657_);
if (v___x_5665_ == 0)
{
v___y_5639_ = v___x_5662_;
v___y_5640_ = v___x_5660_;
v___y_5641_ = v___y_5653_;
v___y_5642_ = v___y_5654_;
v___y_5643_ = v_fst_5655_;
v___y_5644_ = v___x_5657_;
v___y_5645_ = v_snd_5656_;
v___y_5646_ = v___x_5661_;
v___y_5647_ = v___x_5664_;
goto v___jp_5638_;
}
else
{
uint64_t v___x_5666_; 
v___x_5666_ = lean_unbox_uint64(v_snd_5656_);
v___y_5639_ = v___x_5662_;
v___y_5640_ = v___x_5660_;
v___y_5641_ = v___y_5653_;
v___y_5642_ = v___y_5654_;
v___y_5643_ = v_fst_5655_;
v___y_5644_ = v___x_5657_;
v___y_5645_ = v_snd_5656_;
v___y_5646_ = v___x_5661_;
v___y_5647_ = v___x_5666_;
goto v___jp_5638_;
}
}
else
{
uint8_t v___x_5667_; 
lean_dec(v_snd_5656_);
v___x_5667_ = lean_unbox(v_fst_5655_);
lean_dec(v_fst_5655_);
if (v___x_5667_ == 0)
{
lean_object* v___x_5668_; 
v___x_5668_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
return v___x_5668_;
}
else
{
lean_object* v___x_5669_; 
v___x_5669_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
return v___x_5669_;
}
}
}
v___jp_5670_:
{
uint8_t v___x_5679_; 
v___x_5679_ = lean_uint64_dec_eq(v___y_5673_, v___y_5677_);
if (v___x_5679_ == 0)
{
uint8_t v___x_5680_; 
v___x_5680_ = lean_uint64_dec_lt(v___y_5673_, v___y_5677_);
if (v___x_5680_ == 0)
{
uint64_t v___x_5681_; lean_object* v___x_5682_; lean_object* v___x_5683_; 
v___x_5681_ = lean_uint64_sub(v___y_5673_, v___y_5677_);
v___x_5682_ = lean_box(v___y_5671_);
v___x_5683_ = lean_box_uint64(v___x_5681_);
v___y_5652_ = v___y_5672_;
v___y_5653_ = v___y_5675_;
v___y_5654_ = v___y_5676_;
v_fst_5655_ = v___x_5682_;
v_snd_5656_ = v___x_5683_;
goto v___jp_5651_;
}
else
{
uint64_t v___x_5684_; lean_object* v___x_5685_; lean_object* v___x_5686_; 
v___x_5684_ = lean_uint64_sub(v___y_5677_, v___y_5673_);
v___x_5685_ = lean_box(v___y_5674_);
v___x_5686_ = lean_box_uint64(v___x_5684_);
v___y_5652_ = v___y_5672_;
v___y_5653_ = v___y_5675_;
v___y_5654_ = v___y_5676_;
v_fst_5655_ = v___x_5685_;
v_snd_5656_ = v___x_5686_;
goto v___jp_5651_;
}
}
else
{
lean_object* v___x_5687_; lean_object* v___x_5688_; 
v___x_5687_ = lean_box(v___y_5678_);
v___x_5688_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_5652_ = v___y_5672_;
v___y_5653_ = v___y_5675_;
v___y_5654_ = v___y_5676_;
v_fst_5655_ = v___x_5687_;
v_snd_5656_ = v___x_5688_;
goto v___jp_5651_;
}
}
v___jp_5689_:
{
if (v___y_5697_ == 0)
{
v___y_5671_ = v___y_5690_;
v___y_5672_ = v___y_5692_;
v___y_5673_ = v___y_5691_;
v___y_5674_ = v___y_5694_;
v___y_5675_ = v___y_5693_;
v___y_5676_ = v___y_5695_;
v___y_5677_ = v___y_5696_;
v___y_5678_ = v___y_5697_;
goto v___jp_5670_;
}
else
{
uint64_t v___x_5698_; lean_object* v___x_5699_; lean_object* v___x_5700_; 
v___x_5698_ = lean_uint64_add(v___y_5691_, v___y_5696_);
v___x_5699_ = lean_box(v___y_5690_);
v___x_5700_ = lean_box_uint64(v___x_5698_);
v___y_5652_ = v___y_5692_;
v___y_5653_ = v___y_5693_;
v___y_5654_ = v___y_5695_;
v_fst_5655_ = v___x_5699_;
v_snd_5656_ = v___x_5700_;
goto v___jp_5651_;
}
}
v___jp_5701_:
{
uint32_t v___x_5704_; uint32_t v___x_5705_; uint32_t v___x_5706_; lean_object* v___x_5707_; 
v___x_5704_ = 8388607;
v___x_5705_ = lean_uint32_land(v___y_5702_, v___x_5704_);
v___x_5706_ = lean_uint32_lor(v___y_5703_, v___x_5705_);
v___x_5707_ = lean_box_uint32(v___x_5706_);
return v___x_5707_;
}
v___jp_5708_:
{
uint8_t v___x_5712_; 
v___x_5712_ = lean_uint64_dec_eq(v___y_5711_, v___y_5710_);
if (v___x_5712_ == 0)
{
uint64_t v___x_5713_; uint8_t v___x_5714_; 
v___x_5713_ = 8388608ULL;
v___x_5714_ = lean_uint64_dec_eq(v___y_5711_, v___x_5713_);
if (v___x_5714_ == 0)
{
uint32_t v___x_5715_; uint8_t v___x_5716_; 
v___x_5715_ = lean_uint64_to_uint32(v___y_5711_);
v___x_5716_ = lean_unbox(v___y_5709_);
lean_dec(v___y_5709_);
if (v___x_5716_ == 0)
{
uint32_t v___x_5717_; 
v___x_5717_ = 0;
v___y_5702_ = v___x_5715_;
v___y_5703_ = v___x_5717_;
goto v___jp_5701_;
}
else
{
uint32_t v___x_5718_; 
v___x_5718_ = 2147483648;
v___y_5702_ = v___x_5715_;
v___y_5703_ = v___x_5718_;
goto v___jp_5701_;
}
}
else
{
uint8_t v___x_5719_; 
v___x_5719_ = lean_unbox(v___y_5709_);
lean_dec(v___y_5709_);
if (v___x_5719_ == 0)
{
uint32_t v___x_5720_; 
v___x_5720_ = 0;
v___y_5346_ = v___x_5720_;
goto v___jp_5345_;
}
else
{
uint32_t v___x_5721_; 
v___x_5721_ = 2147483648;
v___y_5346_ = v___x_5721_;
goto v___jp_5345_;
}
}
}
else
{
uint8_t v___x_5722_; 
v___x_5722_ = lean_unbox(v___y_5709_);
lean_dec(v___y_5709_);
if (v___x_5722_ == 0)
{
lean_object* v___x_5723_; 
v___x_5723_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
return v___x_5723_;
}
else
{
lean_object* v___x_5724_; 
v___x_5724_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
return v___x_5724_;
}
}
}
v___jp_5725_:
{
uint32_t v___x_5731_; uint32_t v___x_5732_; uint32_t v___x_5733_; uint32_t v___x_5734_; uint32_t v___x_5735_; uint32_t v___x_5736_; lean_object* v___x_5737_; 
v___x_5731_ = lean_uint32_land(v___y_5729_, v___y_5727_);
v___x_5732_ = lean_uint32_shift_left(v___x_5731_, v___y_5726_);
v___x_5733_ = lean_uint32_lor(v___y_5730_, v___x_5732_);
v___x_5734_ = 8388607;
v___x_5735_ = lean_uint32_land(v___y_5728_, v___x_5734_);
v___x_5736_ = lean_uint32_lor(v___x_5733_, v___x_5735_);
v___x_5737_ = lean_box_uint32(v___x_5736_);
return v___x_5737_;
}
v___jp_5738_:
{
uint8_t v___x_5744_; 
v___x_5744_ = lean_unbox(v___y_5739_);
lean_dec(v___y_5739_);
if (v___x_5744_ == 0)
{
uint32_t v___x_5745_; 
v___x_5745_ = 0;
v___y_5726_ = v___y_5740_;
v___y_5727_ = v___y_5741_;
v___y_5728_ = v___y_5743_;
v___y_5729_ = v___y_5742_;
v___y_5730_ = v___x_5745_;
goto v___jp_5725_;
}
else
{
uint32_t v___x_5746_; 
v___x_5746_ = 2147483648;
v___y_5726_ = v___y_5740_;
v___y_5727_ = v___y_5741_;
v___y_5728_ = v___y_5743_;
v___y_5729_ = v___y_5742_;
v___y_5730_ = v___x_5746_;
goto v___jp_5725_;
}
}
v___jp_5747_:
{
uint64_t v___x_5754_; uint64_t v_encodedExponent_5755_; uint32_t v___x_5756_; uint64_t v___x_5757_; uint8_t v___x_5758_; 
v___x_5754_ = 171ULL;
v_encodedExponent_5755_ = lean_uint64_sub(v___y_5752_, v___x_5754_);
v___x_5756_ = lean_uint64_to_uint32(v_encodedExponent_5755_);
v___x_5757_ = 8388608ULL;
v___x_5758_ = lean_uint64_dec_lt(v___y_5753_, v___x_5757_);
if (v___x_5758_ == 0)
{
uint64_t v___x_5759_; uint32_t v___x_5760_; 
v___x_5759_ = lean_uint64_sub(v___y_5753_, v___x_5757_);
v___x_5760_ = lean_uint64_to_uint32(v___x_5759_);
v___y_5739_ = v___y_5748_;
v___y_5740_ = v___y_5749_;
v___y_5741_ = v___y_5750_;
v___y_5742_ = v___x_5756_;
v___y_5743_ = v___x_5760_;
goto v___jp_5738_;
}
else
{
uint32_t v___x_5761_; 
v___x_5761_ = lean_uint64_to_uint32(v___y_5751_);
v___y_5739_ = v___y_5748_;
v___y_5740_ = v___y_5749_;
v___y_5741_ = v___y_5750_;
v___y_5742_ = v___x_5756_;
v___y_5743_ = v___x_5761_;
goto v___jp_5738_;
}
}
v___jp_5762_:
{
uint64_t v___x_5770_; uint8_t v___x_5771_; 
v___x_5770_ = 425ULL;
v___x_5771_ = lean_uint64_dec_lt(v___x_5770_, v___y_5769_);
if (v___x_5771_ == 0)
{
if (v___y_5764_ == 0)
{
v___y_5748_ = v___y_5763_;
v___y_5749_ = v___y_5765_;
v___y_5750_ = v___y_5766_;
v___y_5751_ = v___y_5767_;
v___y_5752_ = v___y_5769_;
v___y_5753_ = v___y_5768_;
goto v___jp_5747_;
}
else
{
uint64_t v___x_5772_; 
v___x_5772_ = 8388608ULL;
v___y_5748_ = v___y_5763_;
v___y_5749_ = v___y_5765_;
v___y_5750_ = v___y_5766_;
v___y_5751_ = v___y_5767_;
v___y_5752_ = v___y_5769_;
v___y_5753_ = v___x_5772_;
goto v___jp_5747_;
}
}
else
{
uint8_t v___x_5773_; 
v___x_5773_ = lean_unbox(v___y_5763_);
lean_dec(v___y_5763_);
if (v___x_5773_ == 0)
{
lean_object* v___x_5774_; 
v___x_5774_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__1;
return v___x_5774_;
}
else
{
lean_object* v___x_5775_; 
v___x_5775_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__2;
return v___x_5775_;
}
}
}
v___jp_5776_:
{
uint64_t v___x_5783_; uint8_t v_carry_5784_; 
v___x_5783_ = 16777216ULL;
v_carry_5784_ = lean_uint64_dec_eq(v___y_5782_, v___x_5783_);
if (v_carry_5784_ == 0)
{
v___y_5763_ = v___y_5777_;
v___y_5764_ = v_carry_5784_;
v___y_5765_ = v___y_5778_;
v___y_5766_ = v___y_5779_;
v___y_5767_ = v___y_5780_;
v___y_5768_ = v___y_5782_;
v___y_5769_ = v___y_5781_;
goto v___jp_5762_;
}
else
{
uint64_t v___x_5785_; uint64_t v___x_5786_; 
v___x_5785_ = 1ULL;
v___x_5786_ = lean_uint64_add(v___y_5781_, v___x_5785_);
v___y_5763_ = v___y_5777_;
v___y_5764_ = v_carry_5784_;
v___y_5765_ = v___y_5778_;
v___y_5766_ = v___y_5779_;
v___y_5767_ = v___y_5780_;
v___y_5768_ = v___y_5782_;
v___y_5769_ = v___x_5786_;
goto v___jp_5762_;
}
}
v___jp_5787_:
{
uint64_t v_position_5796_; uint64_t v___x_5797_; uint8_t v___x_5798_; 
v_position_5796_ = lean_uint64_add(v___y_5795_, v___y_5789_);
v___x_5797_ = 172ULL;
v___x_5798_ = lean_uint64_dec_lt(v_position_5796_, v___x_5797_);
if (v___x_5798_ == 0)
{
uint64_t v___x_5799_; uint8_t v___x_5800_; 
v___x_5799_ = 23ULL;
v___x_5800_ = lean_uint64_dec_lt(v___y_5795_, v___x_5799_);
if (v___x_5800_ == 0)
{
uint64_t v___x_5801_; uint8_t v___x_5802_; 
v___x_5801_ = lean_uint64_sub(v___y_5795_, v___x_5799_);
v___x_5802_ = lean_uint64_dec_eq(v___x_5801_, v___y_5793_);
if (v___x_5802_ == 0)
{
uint64_t v___x_5803_; uint8_t v___x_5804_; 
v___x_5803_ = 64ULL;
v___x_5804_ = lean_uint64_dec_lt(v___x_5801_, v___x_5803_);
if (v___x_5804_ == 0)
{
uint8_t v___x_5805_; 
v___x_5805_ = lean_uint64_dec_eq(v___x_5801_, v___x_5803_);
if (v___x_5805_ == 0)
{
lean_dec(v___y_5790_);
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v___y_5793_;
goto v___jp_5776_;
}
else
{
uint64_t v___x_5806_; uint64_t v___x_5807_; uint8_t v___x_5808_; 
v___x_5806_ = 9223372036854775808ULL;
v___x_5807_ = lean_unbox_uint64(v___y_5790_);
lean_dec(v___y_5790_);
v___x_5808_ = lean_uint64_dec_lt(v___x_5806_, v___x_5807_);
if (v___x_5808_ == 0)
{
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v___y_5793_;
goto v___jp_5776_;
}
else
{
uint64_t v___x_5809_; 
v___x_5809_ = 1ULL;
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v___x_5809_;
goto v___jp_5776_;
}
}
}
else
{
uint64_t v___x_5810_; uint64_t v_quotient_5811_; uint64_t v___x_5812_; uint64_t v___x_5813_; uint64_t v___x_5814_; uint64_t v___x_5815_; uint64_t v_remainder_5816_; uint64_t v___x_5817_; uint64_t v_half_5818_; uint8_t v___x_5819_; 
v___x_5810_ = lean_unbox_uint64(v___y_5790_);
v_quotient_5811_ = lean_uint64_shift_right(v___x_5810_, v___x_5801_);
v___x_5812_ = 1ULL;
v___x_5813_ = lean_uint64_shift_left(v___x_5812_, v___x_5801_);
v___x_5814_ = lean_uint64_sub(v___x_5813_, v___x_5812_);
v___x_5815_ = lean_unbox_uint64(v___y_5790_);
lean_dec(v___y_5790_);
v_remainder_5816_ = lean_uint64_land(v___x_5815_, v___x_5814_);
v___x_5817_ = lean_uint64_sub(v___x_5801_, v___x_5812_);
v_half_5818_ = lean_uint64_shift_left(v___x_5812_, v___x_5817_);
v___x_5819_ = lean_uint64_dec_lt(v_remainder_5816_, v_half_5818_);
if (v___x_5819_ == 0)
{
uint8_t v___x_5820_; 
v___x_5820_ = lean_uint64_dec_lt(v_half_5818_, v_remainder_5816_);
if (v___x_5820_ == 0)
{
uint64_t v___x_5821_; uint8_t v___x_5822_; 
v___x_5821_ = lean_uint64_land(v_quotient_5811_, v___x_5812_);
v___x_5822_ = lean_uint64_dec_eq(v___x_5821_, v___y_5793_);
if (v___x_5822_ == 0)
{
uint64_t v___x_5823_; 
v___x_5823_ = lean_uint64_add(v_quotient_5811_, v___x_5812_);
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v___x_5823_;
goto v___jp_5776_;
}
else
{
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v_quotient_5811_;
goto v___jp_5776_;
}
}
else
{
uint64_t v___x_5824_; 
v___x_5824_ = lean_uint64_add(v_quotient_5811_, v___x_5812_);
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v___x_5824_;
goto v___jp_5776_;
}
}
else
{
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v_quotient_5811_;
goto v___jp_5776_;
}
}
}
else
{
uint64_t v___x_5825_; 
v___x_5825_ = lean_unbox_uint64(v___y_5790_);
lean_dec(v___y_5790_);
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v___x_5825_;
goto v___jp_5776_;
}
}
else
{
uint64_t v___x_5826_; uint64_t v___x_5827_; uint64_t v___x_5828_; 
v___x_5826_ = lean_uint64_sub(v___x_5799_, v___y_5795_);
v___x_5827_ = lean_unbox_uint64(v___y_5790_);
lean_dec(v___y_5790_);
v___x_5828_ = lean_uint64_shift_left(v___x_5827_, v___x_5826_);
v___y_5777_ = v___y_5788_;
v___y_5778_ = v___y_5791_;
v___y_5779_ = v___y_5792_;
v___y_5780_ = v___y_5793_;
v___y_5781_ = v_position_5796_;
v___y_5782_ = v___x_5828_;
goto v___jp_5776_;
}
}
else
{
uint8_t v___x_5829_; 
v___x_5829_ = lean_uint64_dec_lt(v___y_5789_, v___y_5794_);
if (v___x_5829_ == 0)
{
uint64_t v___x_5830_; uint64_t v___x_5831_; uint64_t v___x_5832_; 
v___x_5830_ = lean_uint64_sub(v___y_5789_, v___y_5794_);
v___x_5831_ = lean_unbox_uint64(v___y_5790_);
lean_dec(v___y_5790_);
v___x_5832_ = lean_uint64_shift_left(v___x_5831_, v___x_5830_);
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v___x_5832_;
goto v___jp_5708_;
}
else
{
uint64_t v___x_5833_; uint8_t v___x_5834_; 
v___x_5833_ = lean_uint64_sub(v___y_5794_, v___y_5789_);
v___x_5834_ = lean_uint64_dec_eq(v___x_5833_, v___y_5793_);
if (v___x_5834_ == 0)
{
uint64_t v___x_5835_; uint8_t v___x_5836_; 
v___x_5835_ = 64ULL;
v___x_5836_ = lean_uint64_dec_lt(v___x_5833_, v___x_5835_);
if (v___x_5836_ == 0)
{
uint8_t v___x_5837_; 
v___x_5837_ = lean_uint64_dec_eq(v___x_5833_, v___x_5835_);
if (v___x_5837_ == 0)
{
lean_dec(v___y_5790_);
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v___y_5793_;
goto v___jp_5708_;
}
else
{
uint64_t v___x_5838_; uint64_t v___x_5839_; uint8_t v___x_5840_; 
v___x_5838_ = 9223372036854775808ULL;
v___x_5839_ = lean_unbox_uint64(v___y_5790_);
lean_dec(v___y_5790_);
v___x_5840_ = lean_uint64_dec_lt(v___x_5838_, v___x_5839_);
if (v___x_5840_ == 0)
{
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v___y_5793_;
goto v___jp_5708_;
}
else
{
uint64_t v___x_5841_; 
v___x_5841_ = 1ULL;
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v___x_5841_;
goto v___jp_5708_;
}
}
}
else
{
uint64_t v___x_5842_; uint64_t v_quotient_5843_; uint64_t v___x_5844_; uint64_t v___x_5845_; uint64_t v___x_5846_; uint64_t v___x_5847_; uint64_t v_remainder_5848_; uint64_t v___x_5849_; uint64_t v_half_5850_; uint8_t v___x_5851_; 
v___x_5842_ = lean_unbox_uint64(v___y_5790_);
v_quotient_5843_ = lean_uint64_shift_right(v___x_5842_, v___x_5833_);
v___x_5844_ = 1ULL;
v___x_5845_ = lean_uint64_shift_left(v___x_5844_, v___x_5833_);
v___x_5846_ = lean_uint64_sub(v___x_5845_, v___x_5844_);
v___x_5847_ = lean_unbox_uint64(v___y_5790_);
lean_dec(v___y_5790_);
v_remainder_5848_ = lean_uint64_land(v___x_5847_, v___x_5846_);
v___x_5849_ = lean_uint64_sub(v___x_5833_, v___x_5844_);
v_half_5850_ = lean_uint64_shift_left(v___x_5844_, v___x_5849_);
v___x_5851_ = lean_uint64_dec_lt(v_remainder_5848_, v_half_5850_);
if (v___x_5851_ == 0)
{
uint8_t v___x_5852_; 
v___x_5852_ = lean_uint64_dec_lt(v_half_5850_, v_remainder_5848_);
if (v___x_5852_ == 0)
{
uint64_t v___x_5853_; uint8_t v___x_5854_; 
v___x_5853_ = lean_uint64_land(v_quotient_5843_, v___x_5844_);
v___x_5854_ = lean_uint64_dec_eq(v___x_5853_, v___y_5793_);
if (v___x_5854_ == 0)
{
uint64_t v___x_5855_; 
v___x_5855_ = lean_uint64_add(v_quotient_5843_, v___x_5844_);
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v___x_5855_;
goto v___jp_5708_;
}
else
{
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v_quotient_5843_;
goto v___jp_5708_;
}
}
else
{
uint64_t v___x_5856_; 
v___x_5856_ = lean_uint64_add(v_quotient_5843_, v___x_5844_);
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v___x_5856_;
goto v___jp_5708_;
}
}
else
{
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v_quotient_5843_;
goto v___jp_5708_;
}
}
}
else
{
uint64_t v___x_5857_; 
v___x_5857_ = lean_unbox_uint64(v___y_5790_);
lean_dec(v___y_5790_);
v___y_5709_ = v___y_5788_;
v___y_5710_ = v___y_5793_;
v___y_5711_ = v___x_5857_;
goto v___jp_5708_;
}
}
}
}
v___jp_5858_:
{
uint64_t v___x_5868_; uint64_t v___x_5869_; uint8_t v___x_5870_; 
v___x_5868_ = 1ULL;
v___x_5869_ = lean_uint64_shift_right(v___y_5864_, v___x_5868_);
v___x_5870_ = lean_uint64_dec_eq(v___x_5869_, v___y_5865_);
if (v___x_5870_ == 0)
{
uint64_t v___x_5871_; 
v___x_5871_ = lean_uint64_add(v___y_5867_, v___x_5868_);
v___y_5788_ = v___y_5860_;
v___y_5789_ = v___y_5859_;
v___y_5790_ = v___y_5862_;
v___y_5791_ = v___y_5861_;
v___y_5792_ = v___y_5863_;
v___y_5793_ = v___y_5865_;
v___y_5794_ = v___y_5866_;
v___y_5795_ = v___x_5871_;
goto v___jp_5787_;
}
else
{
v___y_5788_ = v___y_5860_;
v___y_5789_ = v___y_5859_;
v___y_5790_ = v___y_5862_;
v___y_5791_ = v___y_5861_;
v___y_5792_ = v___y_5863_;
v___y_5793_ = v___y_5865_;
v___y_5794_ = v___y_5866_;
v___y_5795_ = v___y_5867_;
goto v___jp_5787_;
}
}
v___jp_5872_:
{
uint64_t v___x_5884_; uint8_t v___x_5885_; 
v___x_5884_ = lean_uint64_shift_right(v___y_5877_, v___y_5882_);
v___x_5885_ = lean_uint64_dec_eq(v___x_5884_, v___y_5879_);
if (v___x_5885_ == 0)
{
uint64_t v___x_5886_; 
v___x_5886_ = lean_uint64_add(v___y_5881_, v___y_5882_);
v___y_5859_ = v___y_5874_;
v___y_5860_ = v___y_5873_;
v___y_5861_ = v___y_5876_;
v___y_5862_ = v___y_5875_;
v___y_5863_ = v___y_5878_;
v___y_5864_ = v___y_5883_;
v___y_5865_ = v___y_5879_;
v___y_5866_ = v___y_5880_;
v___y_5867_ = v___x_5886_;
goto v___jp_5858_;
}
else
{
v___y_5859_ = v___y_5874_;
v___y_5860_ = v___y_5873_;
v___y_5861_ = v___y_5876_;
v___y_5862_ = v___y_5875_;
v___y_5863_ = v___y_5878_;
v___y_5864_ = v___y_5883_;
v___y_5865_ = v___y_5879_;
v___y_5866_ = v___y_5880_;
v___y_5867_ = v___y_5881_;
goto v___jp_5858_;
}
}
v___jp_5887_:
{
uint64_t v___x_5897_; uint64_t v___x_5898_; uint8_t v___x_5899_; 
v___x_5897_ = 2ULL;
v___x_5898_ = lean_uint64_shift_right(v___y_5892_, v___x_5897_);
v___x_5899_ = lean_uint64_dec_eq(v___x_5898_, v___y_5894_);
if (v___x_5899_ == 0)
{
v___y_5873_ = v___y_5889_;
v___y_5874_ = v___y_5888_;
v___y_5875_ = v___y_5891_;
v___y_5876_ = v___y_5890_;
v___y_5877_ = v___y_5892_;
v___y_5878_ = v___y_5893_;
v___y_5879_ = v___y_5894_;
v___y_5880_ = v___y_5895_;
v___y_5881_ = v___y_5896_;
v___y_5882_ = v___x_5897_;
v___y_5883_ = v___x_5898_;
goto v___jp_5872_;
}
else
{
v___y_5873_ = v___y_5889_;
v___y_5874_ = v___y_5888_;
v___y_5875_ = v___y_5891_;
v___y_5876_ = v___y_5890_;
v___y_5877_ = v___y_5892_;
v___y_5878_ = v___y_5893_;
v___y_5879_ = v___y_5894_;
v___y_5880_ = v___y_5895_;
v___y_5881_ = v___y_5896_;
v___y_5882_ = v___x_5897_;
v___y_5883_ = v___y_5892_;
goto v___jp_5872_;
}
}
v___jp_5900_:
{
uint64_t v___x_5912_; uint8_t v___x_5913_; 
v___x_5912_ = lean_uint64_shift_right(v___y_5904_, v___y_5907_);
v___x_5913_ = lean_uint64_dec_eq(v___x_5912_, v___y_5909_);
if (v___x_5913_ == 0)
{
uint64_t v___x_5914_; 
v___x_5914_ = lean_uint64_add(v___y_5903_, v___y_5907_);
v___y_5888_ = v___y_5902_;
v___y_5889_ = v___y_5901_;
v___y_5890_ = v___y_5906_;
v___y_5891_ = v___y_5905_;
v___y_5892_ = v___y_5911_;
v___y_5893_ = v___y_5908_;
v___y_5894_ = v___y_5909_;
v___y_5895_ = v___y_5910_;
v___y_5896_ = v___x_5914_;
goto v___jp_5887_;
}
else
{
v___y_5888_ = v___y_5902_;
v___y_5889_ = v___y_5901_;
v___y_5890_ = v___y_5906_;
v___y_5891_ = v___y_5905_;
v___y_5892_ = v___y_5911_;
v___y_5893_ = v___y_5908_;
v___y_5894_ = v___y_5909_;
v___y_5895_ = v___y_5910_;
v___y_5896_ = v___y_5903_;
goto v___jp_5887_;
}
}
v___jp_5915_:
{
uint64_t v___x_5925_; uint64_t v___x_5926_; uint8_t v___x_5927_; 
v___x_5925_ = 4ULL;
v___x_5926_ = lean_uint64_shift_right(v___y_5918_, v___x_5925_);
v___x_5927_ = lean_uint64_dec_eq(v___x_5926_, v___y_5922_);
if (v___x_5927_ == 0)
{
v___y_5901_ = v___y_5917_;
v___y_5902_ = v___y_5916_;
v___y_5903_ = v___y_5924_;
v___y_5904_ = v___y_5918_;
v___y_5905_ = v___y_5920_;
v___y_5906_ = v___y_5919_;
v___y_5907_ = v___x_5925_;
v___y_5908_ = v___y_5921_;
v___y_5909_ = v___y_5922_;
v___y_5910_ = v___y_5923_;
v___y_5911_ = v___x_5926_;
goto v___jp_5900_;
}
else
{
v___y_5901_ = v___y_5917_;
v___y_5902_ = v___y_5916_;
v___y_5903_ = v___y_5924_;
v___y_5904_ = v___y_5918_;
v___y_5905_ = v___y_5920_;
v___y_5906_ = v___y_5919_;
v___y_5907_ = v___x_5925_;
v___y_5908_ = v___y_5921_;
v___y_5909_ = v___y_5922_;
v___y_5910_ = v___y_5923_;
v___y_5911_ = v___y_5918_;
goto v___jp_5900_;
}
}
v___jp_5928_:
{
uint64_t v___x_5940_; uint8_t v___x_5941_; 
v___x_5940_ = lean_uint64_shift_right(v___y_5937_, v___y_5936_);
v___x_5941_ = lean_uint64_dec_eq(v___x_5940_, v___y_5934_);
if (v___x_5941_ == 0)
{
uint64_t v___x_5942_; 
v___x_5942_ = lean_uint64_add(v___y_5938_, v___y_5936_);
v___y_5916_ = v___y_5930_;
v___y_5917_ = v___y_5929_;
v___y_5918_ = v___y_5939_;
v___y_5919_ = v___y_5932_;
v___y_5920_ = v___y_5931_;
v___y_5921_ = v___y_5933_;
v___y_5922_ = v___y_5934_;
v___y_5923_ = v___y_5935_;
v___y_5924_ = v___x_5942_;
goto v___jp_5915_;
}
else
{
v___y_5916_ = v___y_5930_;
v___y_5917_ = v___y_5929_;
v___y_5918_ = v___y_5939_;
v___y_5919_ = v___y_5932_;
v___y_5920_ = v___y_5931_;
v___y_5921_ = v___y_5933_;
v___y_5922_ = v___y_5934_;
v___y_5923_ = v___y_5935_;
v___y_5924_ = v___y_5938_;
goto v___jp_5915_;
}
}
v___jp_5943_:
{
uint64_t v___x_5953_; uint64_t v___x_5954_; uint8_t v___x_5955_; 
v___x_5953_ = 8ULL;
v___x_5954_ = lean_uint64_shift_right(v___y_5951_, v___x_5953_);
v___x_5955_ = lean_uint64_dec_eq(v___x_5954_, v___y_5949_);
if (v___x_5955_ == 0)
{
v___y_5929_ = v___y_5945_;
v___y_5930_ = v___y_5944_;
v___y_5931_ = v___y_5947_;
v___y_5932_ = v___y_5946_;
v___y_5933_ = v___y_5948_;
v___y_5934_ = v___y_5949_;
v___y_5935_ = v___y_5950_;
v___y_5936_ = v___x_5953_;
v___y_5937_ = v___y_5951_;
v___y_5938_ = v___y_5952_;
v___y_5939_ = v___x_5954_;
goto v___jp_5928_;
}
else
{
v___y_5929_ = v___y_5945_;
v___y_5930_ = v___y_5944_;
v___y_5931_ = v___y_5947_;
v___y_5932_ = v___y_5946_;
v___y_5933_ = v___y_5948_;
v___y_5934_ = v___y_5949_;
v___y_5935_ = v___y_5950_;
v___y_5936_ = v___x_5953_;
v___y_5937_ = v___y_5951_;
v___y_5938_ = v___y_5952_;
v___y_5939_ = v___y_5951_;
goto v___jp_5928_;
}
}
v___jp_5956_:
{
uint64_t v___x_5968_; uint8_t v___x_5969_; 
v___x_5968_ = lean_uint64_shift_right(v___y_5961_, v___y_5966_);
v___x_5969_ = lean_uint64_dec_eq(v___x_5968_, v___y_5964_);
if (v___x_5969_ == 0)
{
uint64_t v___x_5970_; 
v___x_5970_ = lean_uint64_add(v___y_5962_, v___y_5966_);
v___y_5944_ = v___y_5958_;
v___y_5945_ = v___y_5957_;
v___y_5946_ = v___y_5960_;
v___y_5947_ = v___y_5959_;
v___y_5948_ = v___y_5963_;
v___y_5949_ = v___y_5964_;
v___y_5950_ = v___y_5965_;
v___y_5951_ = v___y_5967_;
v___y_5952_ = v___x_5970_;
goto v___jp_5943_;
}
else
{
v___y_5944_ = v___y_5958_;
v___y_5945_ = v___y_5957_;
v___y_5946_ = v___y_5960_;
v___y_5947_ = v___y_5959_;
v___y_5948_ = v___y_5963_;
v___y_5949_ = v___y_5964_;
v___y_5950_ = v___y_5965_;
v___y_5951_ = v___y_5967_;
v___y_5952_ = v___y_5962_;
goto v___jp_5943_;
}
}
v___jp_5971_:
{
uint64_t v___x_5981_; uint64_t v___x_5982_; uint8_t v___x_5983_; 
v___x_5981_ = 16ULL;
v___x_5982_ = lean_uint64_shift_right(v___y_5976_, v___x_5981_);
v___x_5983_ = lean_uint64_dec_eq(v___x_5982_, v___y_5978_);
if (v___x_5983_ == 0)
{
v___y_5957_ = v___y_5973_;
v___y_5958_ = v___y_5972_;
v___y_5959_ = v___y_5975_;
v___y_5960_ = v___y_5974_;
v___y_5961_ = v___y_5976_;
v___y_5962_ = v___y_5980_;
v___y_5963_ = v___y_5977_;
v___y_5964_ = v___y_5978_;
v___y_5965_ = v___y_5979_;
v___y_5966_ = v___x_5981_;
v___y_5967_ = v___x_5982_;
goto v___jp_5956_;
}
else
{
v___y_5957_ = v___y_5973_;
v___y_5958_ = v___y_5972_;
v___y_5959_ = v___y_5975_;
v___y_5960_ = v___y_5974_;
v___y_5961_ = v___y_5976_;
v___y_5962_ = v___y_5980_;
v___y_5963_ = v___y_5977_;
v___y_5964_ = v___y_5978_;
v___y_5965_ = v___y_5979_;
v___y_5966_ = v___x_5981_;
v___y_5967_ = v___y_5976_;
goto v___jp_5956_;
}
}
v___jp_5984_:
{
uint64_t v___x_5994_; uint64_t v___x_5995_; uint8_t v___x_5996_; 
v___x_5994_ = lean_unbox_uint64(v___y_5987_);
v___x_5995_ = lean_uint64_shift_right(v___x_5994_, v___y_5992_);
v___x_5996_ = lean_uint64_dec_eq(v___x_5995_, v___y_5990_);
if (v___x_5996_ == 0)
{
v___y_5972_ = v___y_5986_;
v___y_5973_ = v___y_5985_;
v___y_5974_ = v___y_5988_;
v___y_5975_ = v___y_5987_;
v___y_5976_ = v___y_5993_;
v___y_5977_ = v___y_5989_;
v___y_5978_ = v___y_5990_;
v___y_5979_ = v___y_5991_;
v___y_5980_ = v___y_5992_;
goto v___jp_5971_;
}
else
{
v___y_5972_ = v___y_5986_;
v___y_5973_ = v___y_5985_;
v___y_5974_ = v___y_5988_;
v___y_5975_ = v___y_5987_;
v___y_5976_ = v___y_5993_;
v___y_5977_ = v___y_5989_;
v___y_5978_ = v___y_5990_;
v___y_5979_ = v___y_5991_;
v___y_5980_ = v___y_5990_;
goto v___jp_5971_;
}
}
v___jp_5997_:
{
uint64_t v___x_6003_; uint64_t v___x_6004_; uint8_t v___x_6005_; 
v___x_6003_ = 0ULL;
v___x_6004_ = lean_unbox_uint64(v_snd_6002_);
v___x_6005_ = lean_uint64_dec_eq(v___x_6004_, v___x_6003_);
if (v___x_6005_ == 0)
{
uint64_t v___x_6006_; uint64_t v___x_6007_; uint64_t v___x_6008_; uint64_t v___x_6009_; uint64_t v___x_6010_; uint8_t v___x_6011_; 
v___x_6006_ = 149ULL;
v___x_6007_ = lean_uint64_add(v___y_6000_, v___x_6006_);
v___x_6008_ = 32ULL;
v___x_6009_ = lean_unbox_uint64(v_snd_6002_);
v___x_6010_ = lean_uint64_shift_right(v___x_6009_, v___x_6008_);
v___x_6011_ = lean_uint64_dec_eq(v___x_6010_, v___x_6003_);
if (v___x_6011_ == 0)
{
v___y_5985_ = v_fst_6001_;
v___y_5986_ = v___x_6007_;
v___y_5987_ = v_snd_6002_;
v___y_5988_ = v___y_5998_;
v___y_5989_ = v___y_5999_;
v___y_5990_ = v___x_6003_;
v___y_5991_ = v___x_6006_;
v___y_5992_ = v___x_6008_;
v___y_5993_ = v___x_6010_;
goto v___jp_5984_;
}
else
{
uint64_t v___x_6012_; 
v___x_6012_ = lean_unbox_uint64(v_snd_6002_);
v___y_5985_ = v_fst_6001_;
v___y_5986_ = v___x_6007_;
v___y_5987_ = v_snd_6002_;
v___y_5988_ = v___y_5998_;
v___y_5989_ = v___y_5999_;
v___y_5990_ = v___x_6003_;
v___y_5991_ = v___x_6006_;
v___y_5992_ = v___x_6008_;
v___y_5993_ = v___x_6012_;
goto v___jp_5984_;
}
}
else
{
uint8_t v___x_6013_; 
lean_dec(v_snd_6002_);
v___x_6013_ = lean_unbox(v_fst_6001_);
lean_dec(v_fst_6001_);
if (v___x_6013_ == 0)
{
lean_object* v___x_6014_; 
v___x_6014_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__3;
return v___x_6014_;
}
else
{
lean_object* v___x_6015_; 
v___x_6015_ = lp_competition_Submission_sum___redArg___lam__0___boxed__const__4;
return v___x_6015_;
}
}
}
v___jp_6016_:
{
uint8_t v___x_6025_; 
v___x_6025_ = lean_uint64_dec_eq(v___y_6022_, v___y_6018_);
if (v___x_6025_ == 0)
{
uint8_t v___x_6026_; 
v___x_6026_ = lean_uint64_dec_lt(v___y_6022_, v___y_6018_);
if (v___x_6026_ == 0)
{
uint64_t v___x_6027_; lean_object* v___x_6028_; lean_object* v___x_6029_; 
v___x_6027_ = lean_uint64_sub(v___y_6022_, v___y_6018_);
v___x_6028_ = lean_box(v___y_6017_);
v___x_6029_ = lean_box_uint64(v___x_6027_);
v___y_5998_ = v___y_6020_;
v___y_5999_ = v___y_6021_;
v___y_6000_ = v___y_6023_;
v_fst_6001_ = v___x_6028_;
v_snd_6002_ = v___x_6029_;
goto v___jp_5997_;
}
else
{
uint64_t v___x_6030_; lean_object* v___x_6031_; lean_object* v___x_6032_; 
v___x_6030_ = lean_uint64_sub(v___y_6018_, v___y_6022_);
v___x_6031_ = lean_box(v___y_6019_);
v___x_6032_ = lean_box_uint64(v___x_6030_);
v___y_5998_ = v___y_6020_;
v___y_5999_ = v___y_6021_;
v___y_6000_ = v___y_6023_;
v_fst_6001_ = v___x_6031_;
v_snd_6002_ = v___x_6032_;
goto v___jp_5997_;
}
}
else
{
lean_object* v___x_6033_; lean_object* v___x_6034_; 
v___x_6033_ = lean_box(v___y_6024_);
v___x_6034_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_5998_ = v___y_6020_;
v___y_5999_ = v___y_6021_;
v___y_6000_ = v___y_6023_;
v_fst_6001_ = v___x_6033_;
v_snd_6002_ = v___x_6034_;
goto v___jp_5997_;
}
}
v___jp_6035_:
{
if (v___y_6043_ == 0)
{
v___y_6017_ = v___y_6037_;
v___y_6018_ = v___y_6036_;
v___y_6019_ = v___y_6039_;
v___y_6020_ = v___y_6038_;
v___y_6021_ = v___y_6040_;
v___y_6022_ = v___y_6041_;
v___y_6023_ = v___y_6042_;
v___y_6024_ = v___y_6043_;
goto v___jp_6016_;
}
else
{
uint64_t v___x_6044_; lean_object* v___x_6045_; lean_object* v___x_6046_; 
v___x_6044_ = lean_uint64_add(v___y_6041_, v___y_6036_);
v___x_6045_ = lean_box(v___y_6037_);
v___x_6046_ = lean_box_uint64(v___x_6044_);
v___y_5998_ = v___y_6038_;
v___y_5999_ = v___y_6040_;
v___y_6000_ = v___y_6042_;
v_fst_6001_ = v___x_6045_;
v_snd_6002_ = v___x_6046_;
goto v___jp_5997_;
}
}
v___jp_6047_:
{
uint8_t v___x_6057_; 
v___x_6057_ = lean_uint64_dec_le(v___y_6051_, v___y_6056_);
if (v___x_6057_ == 0)
{
uint64_t v_shift_6058_; uint64_t v___x_6059_; uint8_t v___x_6060_; 
v_shift_6058_ = lean_uint64_sub(v___y_6051_, v___y_6056_);
v___x_6059_ = 39ULL;
v___x_6060_ = lean_uint64_dec_le(v_shift_6058_, v___x_6059_);
if (v___x_6060_ == 0)
{
lean_object* v___x_6061_; 
v___x_6061_ = lean_box_uint32(v_acc_5343_);
return v___x_6061_;
}
else
{
uint64_t v___x_6062_; 
v___x_6062_ = lean_uint64_shift_left(v___y_6050_, v_shift_6058_);
if (v___y_6049_ == 0)
{
if (v___y_6052_ == 0)
{
v___y_6036_ = v___y_6048_;
v___y_6037_ = v___y_6049_;
v___y_6038_ = v___y_6053_;
v___y_6039_ = v___y_6052_;
v___y_6040_ = v___y_6054_;
v___y_6041_ = v___x_6062_;
v___y_6042_ = v___y_6056_;
v___y_6043_ = v___x_6060_;
goto v___jp_6035_;
}
else
{
v___y_6017_ = v___y_6049_;
v___y_6018_ = v___y_6048_;
v___y_6019_ = v___y_6052_;
v___y_6020_ = v___y_6053_;
v___y_6021_ = v___y_6054_;
v___y_6022_ = v___x_6062_;
v___y_6023_ = v___y_6056_;
v___y_6024_ = v___y_6049_;
goto v___jp_6016_;
}
}
else
{
v___y_6036_ = v___y_6048_;
v___y_6037_ = v___y_6049_;
v___y_6038_ = v___y_6053_;
v___y_6039_ = v___y_6052_;
v___y_6040_ = v___y_6054_;
v___y_6041_ = v___x_6062_;
v___y_6042_ = v___y_6056_;
v___y_6043_ = v___y_6052_;
goto v___jp_6035_;
}
}
}
else
{
uint64_t v_shift_6063_; uint64_t v___x_6064_; uint8_t v___x_6065_; 
v_shift_6063_ = lean_uint64_sub(v___y_6056_, v___y_6051_);
v___x_6064_ = 39ULL;
v___x_6065_ = lean_uint64_dec_le(v_shift_6063_, v___x_6064_);
if (v___x_6065_ == 0)
{
lean_object* v___x_6066_; 
v___x_6066_ = lean_box_uint32(v___y_6055_);
return v___x_6066_;
}
else
{
uint64_t v___x_6067_; 
v___x_6067_ = lean_uint64_shift_left(v___y_6048_, v_shift_6063_);
if (v___y_6049_ == 0)
{
if (v___y_6052_ == 0)
{
v___y_5690_ = v___y_6049_;
v___y_5691_ = v___y_6050_;
v___y_5692_ = v___y_6051_;
v___y_5693_ = v___y_6053_;
v___y_5694_ = v___y_6052_;
v___y_5695_ = v___y_6054_;
v___y_5696_ = v___x_6067_;
v___y_5697_ = v___x_6065_;
goto v___jp_5689_;
}
else
{
v___y_5671_ = v___y_6049_;
v___y_5672_ = v___y_6051_;
v___y_5673_ = v___y_6050_;
v___y_5674_ = v___y_6052_;
v___y_5675_ = v___y_6053_;
v___y_5676_ = v___y_6054_;
v___y_5677_ = v___x_6067_;
v___y_5678_ = v___y_6049_;
goto v___jp_5670_;
}
}
else
{
v___y_5690_ = v___y_6049_;
v___y_5691_ = v___y_6050_;
v___y_5692_ = v___y_6051_;
v___y_5693_ = v___y_6053_;
v___y_5694_ = v___y_6052_;
v___y_5695_ = v___y_6054_;
v___y_5696_ = v___x_6067_;
v___y_5697_ = v___y_6052_;
goto v___jp_5689_;
}
}
}
}
v___jp_6068_:
{
uint64_t v___x_6078_; uint64_t v___x_6079_; uint8_t v___x_6080_; 
v___x_6078_ = lean_uint32_to_uint64(v___y_6075_);
v___x_6079_ = 0ULL;
v___x_6080_ = lean_uint64_dec_eq(v___x_6078_, v___x_6079_);
if (v___x_6080_ == 0)
{
uint64_t v___x_6081_; uint64_t v___x_6082_; 
v___x_6081_ = 1ULL;
v___x_6082_ = lean_uint64_sub(v___x_6078_, v___x_6081_);
v___y_6048_ = v___y_6070_;
v___y_6049_ = v___y_6069_;
v___y_6050_ = v___y_6071_;
v___y_6051_ = v___y_6077_;
v___y_6052_ = v___y_6072_;
v___y_6053_ = v___y_6073_;
v___y_6054_ = v___y_6074_;
v___y_6055_ = v___y_6076_;
v___y_6056_ = v___x_6082_;
goto v___jp_6047_;
}
else
{
v___y_6048_ = v___y_6070_;
v___y_6049_ = v___y_6069_;
v___y_6050_ = v___y_6071_;
v___y_6051_ = v___y_6077_;
v___y_6052_ = v___y_6072_;
v___y_6053_ = v___y_6073_;
v___y_6054_ = v___y_6074_;
v___y_6055_ = v___y_6076_;
v___y_6056_ = v___x_6079_;
goto v___jp_6047_;
}
}
v___jp_6083_:
{
uint64_t v___x_6093_; uint64_t v___x_6094_; uint8_t v___x_6095_; 
v___x_6093_ = lean_uint32_to_uint64(v___y_6091_);
v___x_6094_ = 0ULL;
v___x_6095_ = lean_uint64_dec_eq(v___x_6093_, v___x_6094_);
if (v___x_6095_ == 0)
{
uint64_t v___x_6096_; uint64_t v___x_6097_; 
v___x_6096_ = 1ULL;
v___x_6097_ = lean_uint64_sub(v___x_6093_, v___x_6096_);
v___y_6069_ = v___y_6084_;
v___y_6070_ = v___y_6092_;
v___y_6071_ = v___y_6085_;
v___y_6072_ = v___y_6087_;
v___y_6073_ = v___y_6086_;
v___y_6074_ = v___y_6088_;
v___y_6075_ = v___y_6089_;
v___y_6076_ = v___y_6090_;
v___y_6077_ = v___x_6097_;
goto v___jp_6068_;
}
else
{
v___y_6069_ = v___y_6084_;
v___y_6070_ = v___y_6092_;
v___y_6071_ = v___y_6085_;
v___y_6072_ = v___y_6087_;
v___y_6073_ = v___y_6086_;
v___y_6074_ = v___y_6088_;
v___y_6075_ = v___y_6089_;
v___y_6076_ = v___y_6090_;
v___y_6077_ = v___x_6094_;
goto v___jp_6068_;
}
}
v___jp_6098_:
{
uint32_t v___x_6107_; uint32_t v___x_6108_; uint32_t v___x_6109_; uint8_t v___x_6110_; 
v___x_6107_ = 8388607;
v___x_6108_ = lean_uint32_land(v___y_6104_, v___x_6107_);
v___x_6109_ = 0;
v___x_6110_ = lean_uint32_dec_eq(v___y_6103_, v___x_6109_);
if (v___x_6110_ == 0)
{
uint64_t v___x_6111_; uint64_t v___x_6112_; uint64_t v___x_6113_; 
v___x_6111_ = lean_uint32_to_uint64(v___x_6108_);
v___x_6112_ = 8388608ULL;
v___x_6113_ = lean_uint64_lor(v___x_6111_, v___x_6112_);
v___y_6084_ = v___y_6099_;
v___y_6085_ = v___y_6106_;
v___y_6086_ = v___y_6101_;
v___y_6087_ = v___y_6100_;
v___y_6088_ = v___y_6102_;
v___y_6089_ = v___y_6103_;
v___y_6090_ = v___y_6104_;
v___y_6091_ = v___y_6105_;
v___y_6092_ = v___x_6113_;
goto v___jp_6083_;
}
else
{
uint64_t v___x_6114_; 
v___x_6114_ = lean_uint32_to_uint64(v___x_6108_);
v___y_6084_ = v___y_6099_;
v___y_6085_ = v___y_6106_;
v___y_6086_ = v___y_6101_;
v___y_6087_ = v___y_6100_;
v___y_6088_ = v___y_6102_;
v___y_6089_ = v___y_6103_;
v___y_6090_ = v___y_6104_;
v___y_6091_ = v___y_6105_;
v___y_6092_ = v___x_6114_;
goto v___jp_6083_;
}
}
v___jp_6115_:
{
uint32_t v___x_6123_; uint32_t v___x_6124_; uint32_t v___x_6125_; uint8_t v___x_6126_; 
v___x_6123_ = 8388607;
v___x_6124_ = lean_uint32_land(v_acc_5343_, v___x_6123_);
v___x_6125_ = 0;
v___x_6126_ = lean_uint32_dec_eq(v___y_6121_, v___x_6125_);
if (v___x_6126_ == 0)
{
uint64_t v___x_6127_; uint64_t v___x_6128_; uint64_t v___x_6129_; 
v___x_6127_ = lean_uint32_to_uint64(v___x_6124_);
v___x_6128_ = 8388608ULL;
v___x_6129_ = lean_uint64_lor(v___x_6127_, v___x_6128_);
v___y_6099_ = v___y_6116_;
v___y_6100_ = v___y_6122_;
v___y_6101_ = v___y_6117_;
v___y_6102_ = v___y_6118_;
v___y_6103_ = v___y_6119_;
v___y_6104_ = v___y_6120_;
v___y_6105_ = v___y_6121_;
v___y_6106_ = v___x_6129_;
goto v___jp_6098_;
}
else
{
uint64_t v___x_6130_; 
v___x_6130_ = lean_uint32_to_uint64(v___x_6124_);
v___y_6099_ = v___y_6116_;
v___y_6100_ = v___y_6122_;
v___y_6101_ = v___y_6117_;
v___y_6102_ = v___y_6118_;
v___y_6103_ = v___y_6119_;
v___y_6104_ = v___y_6120_;
v___y_6105_ = v___y_6121_;
v___y_6106_ = v___x_6130_;
goto v___jp_6098_;
}
}
v___jp_6131_:
{
uint32_t v___x_6139_; uint32_t v___x_6140_; uint32_t v___x_6141_; uint8_t v___x_6142_; 
v___x_6139_ = 2147483648;
v___x_6140_ = lean_uint32_land(v___y_6135_, v___x_6139_);
v___x_6141_ = 0;
v___x_6142_ = lean_uint32_dec_eq(v___x_6140_, v___x_6141_);
if (v___x_6142_ == 0)
{
uint8_t v___x_6143_; 
v___x_6143_ = 1;
v___y_6116_ = v___y_6138_;
v___y_6117_ = v___y_6132_;
v___y_6118_ = v___y_6133_;
v___y_6119_ = v___y_6134_;
v___y_6120_ = v___y_6135_;
v___y_6121_ = v___y_6137_;
v___y_6122_ = v___x_6143_;
goto v___jp_6115_;
}
else
{
v___y_6116_ = v___y_6138_;
v___y_6117_ = v___y_6132_;
v___y_6118_ = v___y_6133_;
v___y_6119_ = v___y_6134_;
v___y_6120_ = v___y_6135_;
v___y_6121_ = v___y_6137_;
v___y_6122_ = v___y_6136_;
goto v___jp_6115_;
}
}
v___jp_6144_:
{
if (v___y_6146_ == 0)
{
uint32_t v___x_6147_; uint32_t v___x_6148_; uint32_t v___x_6149_; uint32_t v_xExponent_6150_; uint32_t v___x_6151_; uint32_t v_yExponent_6152_; uint32_t v___x_6153_; uint32_t v___x_6154_; uint32_t v___x_6155_; uint8_t v___x_6156_; 
v___x_6147_ = 23;
v___x_6148_ = lean_uint32_shift_right(v_acc_5343_, v___x_6147_);
v___x_6149_ = 255;
v_xExponent_6150_ = lean_uint32_land(v___x_6148_, v___x_6149_);
v___x_6151_ = lean_uint32_shift_right(v___y_6145_, v___x_6147_);
v_yExponent_6152_ = lean_uint32_land(v___x_6151_, v___x_6149_);
v___x_6153_ = 2147483648;
v___x_6154_ = lean_uint32_land(v_acc_5343_, v___x_6153_);
v___x_6155_ = 0;
v___x_6156_ = lean_uint32_dec_eq(v___x_6154_, v___x_6155_);
if (v___x_6156_ == 0)
{
uint8_t v___x_6157_; 
v___x_6157_ = 1;
v___y_6132_ = v___x_6147_;
v___y_6133_ = v___x_6149_;
v___y_6134_ = v_yExponent_6152_;
v___y_6135_ = v___y_6145_;
v___y_6136_ = v___y_6146_;
v___y_6137_ = v_xExponent_6150_;
v___y_6138_ = v___x_6157_;
goto v___jp_6131_;
}
else
{
v___y_6132_ = v___x_6147_;
v___y_6133_ = v___x_6149_;
v___y_6134_ = v_yExponent_6152_;
v___y_6135_ = v___y_6145_;
v___y_6136_ = v___y_6146_;
v___y_6137_ = v_xExponent_6150_;
v___y_6138_ = v___y_6146_;
goto v___jp_6131_;
}
}
else
{
lean_object* v___x_6158_; lean_object* v___x_6159_; lean_object* v___x_6160_; lean_object* v___x_6161_; uint32_t v___x_6162_; lean_object* v___x_6163_; 
v___x_6158_ = ((lean_object*)(lp_competition_Submission_TunedAdd_add___closed__0));
v___x_6159_ = lean_uint32_to_nat(v_acc_5343_);
v___x_6160_ = lean_uint32_to_nat(v___y_6145_);
v___x_6161_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word(v___x_6158_, v___x_6159_, v___x_6160_);
v___x_6162_ = lean_uint32_of_nat(v___x_6161_);
lean_dec(v___x_6161_);
v___x_6163_ = lean_box_uint32(v___x_6162_);
return v___x_6163_;
}
}
v___jp_6164_:
{
uint32_t v___x_6166_; uint32_t v___x_6167_; uint32_t v___x_6168_; uint32_t v___x_6169_; uint8_t v___x_6170_; 
v___x_6166_ = 4278190079;
v___x_6167_ = 1;
v___x_6168_ = lean_uint32_shift_left(v_acc_5343_, v___x_6167_);
v___x_6169_ = lean_uint32_sub(v___x_6168_, v___x_6167_);
v___x_6170_ = lean_uint32_dec_le(v___x_6166_, v___x_6169_);
if (v___x_6170_ == 0)
{
uint32_t v___x_6171_; uint32_t v___x_6172_; uint8_t v___x_6173_; 
v___x_6171_ = lean_uint32_shift_left(v___y_6165_, v___x_6167_);
v___x_6172_ = lean_uint32_sub(v___x_6171_, v___x_6167_);
v___x_6173_ = lean_uint32_dec_le(v___x_6166_, v___x_6172_);
v___y_6145_ = v___y_6165_;
v___y_6146_ = v___x_6173_;
goto v___jp_6144_;
}
else
{
v___y_6145_ = v___y_6165_;
v___y_6146_ = v___x_6170_;
goto v___jp_6144_;
}
}
v___jp_6174_:
{
uint32_t v___x_6176_; uint32_t v___x_6177_; 
v___x_6176_ = 8388608;
v___x_6177_ = lean_uint32_lor(v___y_6175_, v___x_6176_);
v___y_6165_ = v___x_6177_;
goto v___jp_6164_;
}
v___jp_6178_:
{
uint32_t v___x_6182_; uint32_t v___x_6183_; 
v___x_6182_ = lean_uint32_land(v___y_6179_, v___y_6180_);
v___x_6183_ = lean_uint32_lor(v___y_6181_, v___x_6182_);
v___y_6165_ = v___x_6183_;
goto v___jp_6164_;
}
v___jp_6184_:
{
uint8_t v___x_6189_; 
v___x_6189_ = lean_uint64_dec_eq(v___y_6188_, v___y_6187_);
if (v___x_6189_ == 0)
{
uint64_t v___x_6190_; uint8_t v___x_6191_; 
v___x_6190_ = 8388608ULL;
v___x_6191_ = lean_uint64_dec_eq(v___y_6188_, v___x_6190_);
if (v___x_6191_ == 0)
{
uint32_t v___x_6192_; 
v___x_6192_ = lean_uint64_to_uint32(v___y_6188_);
if (v___y_6186_ == 0)
{
uint32_t v___x_6193_; 
v___x_6193_ = 0;
v___y_6179_ = v___x_6192_;
v___y_6180_ = v___y_6185_;
v___y_6181_ = v___x_6193_;
goto v___jp_6178_;
}
else
{
uint32_t v___x_6194_; 
v___x_6194_ = 2147483648;
v___y_6179_ = v___x_6192_;
v___y_6180_ = v___y_6185_;
v___y_6181_ = v___x_6194_;
goto v___jp_6178_;
}
}
else
{
if (v___y_6186_ == 0)
{
uint32_t v___x_6195_; 
v___x_6195_ = 0;
v___y_6175_ = v___x_6195_;
goto v___jp_6174_;
}
else
{
uint32_t v___x_6196_; 
v___x_6196_ = 2147483648;
v___y_6175_ = v___x_6196_;
goto v___jp_6174_;
}
}
}
else
{
if (v___y_6186_ == 0)
{
uint32_t v___x_6197_; 
v___x_6197_ = 0;
v___y_6165_ = v___x_6197_;
goto v___jp_6164_;
}
else
{
uint32_t v___x_6198_; 
v___x_6198_ = 2147483648;
v___y_6165_ = v___x_6198_;
goto v___jp_6164_;
}
}
}
v___jp_6199_:
{
uint32_t v___x_6206_; uint32_t v___x_6207_; uint32_t v___x_6208_; uint32_t v___x_6209_; uint32_t v___x_6210_; 
v___x_6206_ = lean_uint32_land(v___y_6202_, v___y_6201_);
v___x_6207_ = lean_uint32_shift_left(v___x_6206_, v___y_6204_);
v___x_6208_ = lean_uint32_lor(v___y_6205_, v___x_6207_);
v___x_6209_ = lean_uint32_land(v___y_6200_, v___y_6203_);
v___x_6210_ = lean_uint32_lor(v___x_6208_, v___x_6209_);
v___y_6165_ = v___x_6210_;
goto v___jp_6164_;
}
v___jp_6211_:
{
if (v___y_6215_ == 0)
{
uint32_t v___x_6218_; 
v___x_6218_ = 0;
v___y_6200_ = v___y_6217_;
v___y_6201_ = v___y_6212_;
v___y_6202_ = v___y_6213_;
v___y_6203_ = v___y_6214_;
v___y_6204_ = v___y_6216_;
v___y_6205_ = v___x_6218_;
goto v___jp_6199_;
}
else
{
uint32_t v___x_6219_; 
v___x_6219_ = 2147483648;
v___y_6200_ = v___y_6217_;
v___y_6201_ = v___y_6212_;
v___y_6202_ = v___y_6213_;
v___y_6203_ = v___y_6214_;
v___y_6204_ = v___y_6216_;
v___y_6205_ = v___x_6219_;
goto v___jp_6199_;
}
}
v___jp_6220_:
{
uint64_t v___x_6228_; uint64_t v_encodedExponent_6229_; uint32_t v___x_6230_; uint64_t v___x_6231_; uint8_t v___x_6232_; 
v___x_6228_ = 171ULL;
v_encodedExponent_6229_ = lean_uint64_sub(v___y_6226_, v___x_6228_);
v___x_6230_ = lean_uint64_to_uint32(v_encodedExponent_6229_);
v___x_6231_ = 8388608ULL;
v___x_6232_ = lean_uint64_dec_lt(v___y_6227_, v___x_6231_);
if (v___x_6232_ == 0)
{
uint64_t v___x_6233_; uint32_t v___x_6234_; 
v___x_6233_ = lean_uint64_sub(v___y_6227_, v___x_6231_);
v___x_6234_ = lean_uint64_to_uint32(v___x_6233_);
v___y_6212_ = v___y_6221_;
v___y_6213_ = v___x_6230_;
v___y_6214_ = v___y_6222_;
v___y_6215_ = v___y_6223_;
v___y_6216_ = v___y_6225_;
v___y_6217_ = v___x_6234_;
goto v___jp_6211_;
}
else
{
uint32_t v___x_6235_; 
v___x_6235_ = lean_uint64_to_uint32(v___y_6224_);
v___y_6212_ = v___y_6221_;
v___y_6213_ = v___x_6230_;
v___y_6214_ = v___y_6222_;
v___y_6215_ = v___y_6223_;
v___y_6216_ = v___y_6225_;
v___y_6217_ = v___x_6235_;
goto v___jp_6211_;
}
}
v___jp_6236_:
{
uint64_t v___x_6245_; uint8_t v___x_6246_; 
v___x_6245_ = 425ULL;
v___x_6246_ = lean_uint64_dec_lt(v___x_6245_, v___y_6244_);
if (v___x_6246_ == 0)
{
if (v___y_6239_ == 0)
{
v___y_6221_ = v___y_6237_;
v___y_6222_ = v___y_6238_;
v___y_6223_ = v___y_6240_;
v___y_6224_ = v___y_6241_;
v___y_6225_ = v___y_6243_;
v___y_6226_ = v___y_6244_;
v___y_6227_ = v___y_6242_;
goto v___jp_6220_;
}
else
{
uint64_t v___x_6247_; 
v___x_6247_ = 8388608ULL;
v___y_6221_ = v___y_6237_;
v___y_6222_ = v___y_6238_;
v___y_6223_ = v___y_6240_;
v___y_6224_ = v___y_6241_;
v___y_6225_ = v___y_6243_;
v___y_6226_ = v___y_6244_;
v___y_6227_ = v___x_6247_;
goto v___jp_6220_;
}
}
else
{
if (v___y_6240_ == 0)
{
uint32_t v___x_6248_; 
v___x_6248_ = 2139095040;
v___y_6165_ = v___x_6248_;
goto v___jp_6164_;
}
else
{
uint32_t v___x_6249_; 
v___x_6249_ = 4286578688;
v___y_6165_ = v___x_6249_;
goto v___jp_6164_;
}
}
}
v___jp_6250_:
{
uint64_t v___x_6258_; uint8_t v_carry_6259_; 
v___x_6258_ = 16777216ULL;
v_carry_6259_ = lean_uint64_dec_eq(v___y_6257_, v___x_6258_);
if (v_carry_6259_ == 0)
{
v___y_6237_ = v___y_6251_;
v___y_6238_ = v___y_6252_;
v___y_6239_ = v_carry_6259_;
v___y_6240_ = v___y_6253_;
v___y_6241_ = v___y_6254_;
v___y_6242_ = v___y_6257_;
v___y_6243_ = v___y_6255_;
v___y_6244_ = v___y_6256_;
goto v___jp_6236_;
}
else
{
uint64_t v___x_6260_; uint64_t v___x_6261_; 
v___x_6260_ = 1ULL;
v___x_6261_ = lean_uint64_add(v___y_6256_, v___x_6260_);
v___y_6237_ = v___y_6251_;
v___y_6238_ = v___y_6252_;
v___y_6239_ = v_carry_6259_;
v___y_6240_ = v___y_6253_;
v___y_6241_ = v___y_6254_;
v___y_6242_ = v___y_6257_;
v___y_6243_ = v___y_6255_;
v___y_6244_ = v___x_6261_;
goto v___jp_6236_;
}
}
v___jp_6262_:
{
uint64_t v_position_6271_; uint64_t v___x_6272_; uint8_t v___x_6273_; 
v_position_6271_ = lean_uint64_add(v___y_6270_, v___y_6264_);
v___x_6272_ = 172ULL;
v___x_6273_ = lean_uint64_dec_lt(v_position_6271_, v___x_6272_);
if (v___x_6273_ == 0)
{
uint64_t v___x_6274_; uint8_t v___x_6275_; 
v___x_6274_ = 23ULL;
v___x_6275_ = lean_uint64_dec_lt(v___y_6270_, v___x_6274_);
if (v___x_6275_ == 0)
{
uint64_t v___x_6276_; uint8_t v___x_6277_; 
v___x_6276_ = lean_uint64_sub(v___y_6270_, v___x_6274_);
v___x_6277_ = lean_uint64_dec_eq(v___x_6276_, v___y_6268_);
if (v___x_6277_ == 0)
{
uint64_t v___x_6278_; uint8_t v___x_6279_; 
v___x_6278_ = 64ULL;
v___x_6279_ = lean_uint64_dec_lt(v___x_6276_, v___x_6278_);
if (v___x_6279_ == 0)
{
uint8_t v___x_6280_; 
v___x_6280_ = lean_uint64_dec_eq(v___x_6276_, v___x_6278_);
if (v___x_6280_ == 0)
{
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v___y_6268_;
goto v___jp_6250_;
}
else
{
uint64_t v___x_6281_; uint8_t v___x_6282_; 
v___x_6281_ = 9223372036854775808ULL;
v___x_6282_ = lean_uint64_dec_lt(v___x_6281_, v___y_6265_);
if (v___x_6282_ == 0)
{
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v___y_6268_;
goto v___jp_6250_;
}
else
{
uint64_t v___x_6283_; 
v___x_6283_ = 1ULL;
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v___x_6283_;
goto v___jp_6250_;
}
}
}
else
{
uint64_t v_quotient_6284_; uint64_t v___x_6285_; uint64_t v___x_6286_; uint64_t v___x_6287_; uint64_t v_remainder_6288_; uint64_t v___x_6289_; uint64_t v_half_6290_; uint8_t v___x_6291_; 
v_quotient_6284_ = lean_uint64_shift_right(v___y_6265_, v___x_6276_);
v___x_6285_ = 1ULL;
v___x_6286_ = lean_uint64_shift_left(v___x_6285_, v___x_6276_);
v___x_6287_ = lean_uint64_sub(v___x_6286_, v___x_6285_);
v_remainder_6288_ = lean_uint64_land(v___y_6265_, v___x_6287_);
v___x_6289_ = lean_uint64_sub(v___x_6276_, v___x_6285_);
v_half_6290_ = lean_uint64_shift_left(v___x_6285_, v___x_6289_);
v___x_6291_ = lean_uint64_dec_lt(v_remainder_6288_, v_half_6290_);
if (v___x_6291_ == 0)
{
uint8_t v___x_6292_; 
v___x_6292_ = lean_uint64_dec_lt(v_half_6290_, v_remainder_6288_);
if (v___x_6292_ == 0)
{
uint64_t v___x_6293_; uint8_t v___x_6294_; 
v___x_6293_ = lean_uint64_land(v_quotient_6284_, v___x_6285_);
v___x_6294_ = lean_uint64_dec_eq(v___x_6293_, v___y_6268_);
if (v___x_6294_ == 0)
{
uint64_t v___x_6295_; 
v___x_6295_ = lean_uint64_add(v_quotient_6284_, v___x_6285_);
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v___x_6295_;
goto v___jp_6250_;
}
else
{
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v_quotient_6284_;
goto v___jp_6250_;
}
}
else
{
uint64_t v___x_6296_; 
v___x_6296_ = lean_uint64_add(v_quotient_6284_, v___x_6285_);
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v___x_6296_;
goto v___jp_6250_;
}
}
else
{
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v_quotient_6284_;
goto v___jp_6250_;
}
}
}
else
{
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v___y_6265_;
goto v___jp_6250_;
}
}
else
{
uint64_t v___x_6297_; uint64_t v___x_6298_; 
v___x_6297_ = lean_uint64_sub(v___x_6274_, v___y_6270_);
v___x_6298_ = lean_uint64_shift_left(v___y_6265_, v___x_6297_);
v___y_6251_ = v___y_6263_;
v___y_6252_ = v___y_6266_;
v___y_6253_ = v___y_6267_;
v___y_6254_ = v___y_6268_;
v___y_6255_ = v___y_6269_;
v___y_6256_ = v_position_6271_;
v___y_6257_ = v___x_6298_;
goto v___jp_6250_;
}
}
else
{
uint64_t v___x_6299_; uint8_t v___x_6300_; 
v___x_6299_ = 149ULL;
v___x_6300_ = lean_uint64_dec_lt(v___y_6264_, v___x_6299_);
if (v___x_6300_ == 0)
{
uint64_t v___x_6301_; uint64_t v___x_6302_; 
v___x_6301_ = lean_uint64_sub(v___y_6264_, v___x_6299_);
v___x_6302_ = lean_uint64_shift_left(v___y_6265_, v___x_6301_);
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v___x_6302_;
goto v___jp_6184_;
}
else
{
uint64_t v___x_6303_; uint8_t v___x_6304_; 
v___x_6303_ = lean_uint64_sub(v___x_6299_, v___y_6264_);
v___x_6304_ = lean_uint64_dec_eq(v___x_6303_, v___y_6268_);
if (v___x_6304_ == 0)
{
uint64_t v___x_6305_; uint8_t v___x_6306_; 
v___x_6305_ = 64ULL;
v___x_6306_ = lean_uint64_dec_lt(v___x_6303_, v___x_6305_);
if (v___x_6306_ == 0)
{
uint8_t v___x_6307_; 
v___x_6307_ = lean_uint64_dec_eq(v___x_6303_, v___x_6305_);
if (v___x_6307_ == 0)
{
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v___y_6268_;
goto v___jp_6184_;
}
else
{
uint64_t v___x_6308_; uint8_t v___x_6309_; 
v___x_6308_ = 9223372036854775808ULL;
v___x_6309_ = lean_uint64_dec_lt(v___x_6308_, v___y_6265_);
if (v___x_6309_ == 0)
{
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v___y_6268_;
goto v___jp_6184_;
}
else
{
uint64_t v___x_6310_; 
v___x_6310_ = 1ULL;
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v___x_6310_;
goto v___jp_6184_;
}
}
}
else
{
uint64_t v_quotient_6311_; uint64_t v___x_6312_; uint64_t v___x_6313_; uint64_t v___x_6314_; uint64_t v_remainder_6315_; uint64_t v___x_6316_; uint64_t v_half_6317_; uint8_t v___x_6318_; 
v_quotient_6311_ = lean_uint64_shift_right(v___y_6265_, v___x_6303_);
v___x_6312_ = 1ULL;
v___x_6313_ = lean_uint64_shift_left(v___x_6312_, v___x_6303_);
v___x_6314_ = lean_uint64_sub(v___x_6313_, v___x_6312_);
v_remainder_6315_ = lean_uint64_land(v___y_6265_, v___x_6314_);
v___x_6316_ = lean_uint64_sub(v___x_6303_, v___x_6312_);
v_half_6317_ = lean_uint64_shift_left(v___x_6312_, v___x_6316_);
v___x_6318_ = lean_uint64_dec_lt(v_remainder_6315_, v_half_6317_);
if (v___x_6318_ == 0)
{
uint8_t v___x_6319_; 
v___x_6319_ = lean_uint64_dec_lt(v_half_6317_, v_remainder_6315_);
if (v___x_6319_ == 0)
{
uint64_t v___x_6320_; uint8_t v___x_6321_; 
v___x_6320_ = lean_uint64_land(v_quotient_6311_, v___x_6312_);
v___x_6321_ = lean_uint64_dec_eq(v___x_6320_, v___y_6268_);
if (v___x_6321_ == 0)
{
uint64_t v___x_6322_; 
v___x_6322_ = lean_uint64_add(v_quotient_6311_, v___x_6312_);
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v___x_6322_;
goto v___jp_6184_;
}
else
{
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v_quotient_6311_;
goto v___jp_6184_;
}
}
else
{
uint64_t v___x_6323_; 
v___x_6323_ = lean_uint64_add(v_quotient_6311_, v___x_6312_);
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v___x_6323_;
goto v___jp_6184_;
}
}
else
{
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v_quotient_6311_;
goto v___jp_6184_;
}
}
}
else
{
v___y_6185_ = v___y_6266_;
v___y_6186_ = v___y_6267_;
v___y_6187_ = v___y_6268_;
v___y_6188_ = v___y_6265_;
goto v___jp_6184_;
}
}
}
}
v___jp_6324_:
{
uint64_t v___x_6334_; uint64_t v___x_6335_; uint8_t v___x_6336_; 
v___x_6334_ = 1ULL;
v___x_6335_ = lean_uint64_shift_right(v___y_6330_, v___x_6334_);
v___x_6336_ = lean_uint64_dec_eq(v___x_6335_, v___y_6331_);
if (v___x_6336_ == 0)
{
uint64_t v___x_6337_; 
v___x_6337_ = lean_uint64_add(v___y_6333_, v___x_6334_);
v___y_6263_ = v___y_6325_;
v___y_6264_ = v___y_6326_;
v___y_6265_ = v___y_6328_;
v___y_6266_ = v___y_6327_;
v___y_6267_ = v___y_6329_;
v___y_6268_ = v___y_6331_;
v___y_6269_ = v___y_6332_;
v___y_6270_ = v___x_6337_;
goto v___jp_6262_;
}
else
{
v___y_6263_ = v___y_6325_;
v___y_6264_ = v___y_6326_;
v___y_6265_ = v___y_6328_;
v___y_6266_ = v___y_6327_;
v___y_6267_ = v___y_6329_;
v___y_6268_ = v___y_6331_;
v___y_6269_ = v___y_6332_;
v___y_6270_ = v___y_6333_;
goto v___jp_6262_;
}
}
v___jp_6338_:
{
uint64_t v___x_6350_; uint8_t v___x_6351_; 
v___x_6350_ = lean_uint64_shift_right(v___y_6348_, v___y_6339_);
v___x_6351_ = lean_uint64_dec_eq(v___x_6350_, v___y_6346_);
if (v___x_6351_ == 0)
{
uint64_t v___x_6352_; 
v___x_6352_ = lean_uint64_add(v___y_6342_, v___y_6339_);
v___y_6325_ = v___y_6340_;
v___y_6326_ = v___y_6341_;
v___y_6327_ = v___y_6344_;
v___y_6328_ = v___y_6343_;
v___y_6329_ = v___y_6345_;
v___y_6330_ = v___y_6349_;
v___y_6331_ = v___y_6346_;
v___y_6332_ = v___y_6347_;
v___y_6333_ = v___x_6352_;
goto v___jp_6324_;
}
else
{
v___y_6325_ = v___y_6340_;
v___y_6326_ = v___y_6341_;
v___y_6327_ = v___y_6344_;
v___y_6328_ = v___y_6343_;
v___y_6329_ = v___y_6345_;
v___y_6330_ = v___y_6349_;
v___y_6331_ = v___y_6346_;
v___y_6332_ = v___y_6347_;
v___y_6333_ = v___y_6342_;
goto v___jp_6324_;
}
}
v___jp_6353_:
{
uint64_t v___x_6363_; uint64_t v___x_6364_; uint8_t v___x_6365_; 
v___x_6363_ = 2ULL;
v___x_6364_ = lean_uint64_shift_right(v___y_6361_, v___x_6363_);
v___x_6365_ = lean_uint64_dec_eq(v___x_6364_, v___y_6359_);
if (v___x_6365_ == 0)
{
v___y_6339_ = v___x_6363_;
v___y_6340_ = v___y_6354_;
v___y_6341_ = v___y_6355_;
v___y_6342_ = v___y_6362_;
v___y_6343_ = v___y_6357_;
v___y_6344_ = v___y_6356_;
v___y_6345_ = v___y_6358_;
v___y_6346_ = v___y_6359_;
v___y_6347_ = v___y_6360_;
v___y_6348_ = v___y_6361_;
v___y_6349_ = v___x_6364_;
goto v___jp_6338_;
}
else
{
v___y_6339_ = v___x_6363_;
v___y_6340_ = v___y_6354_;
v___y_6341_ = v___y_6355_;
v___y_6342_ = v___y_6362_;
v___y_6343_ = v___y_6357_;
v___y_6344_ = v___y_6356_;
v___y_6345_ = v___y_6358_;
v___y_6346_ = v___y_6359_;
v___y_6347_ = v___y_6360_;
v___y_6348_ = v___y_6361_;
v___y_6349_ = v___y_6361_;
goto v___jp_6338_;
}
}
v___jp_6366_:
{
uint64_t v___x_6378_; uint8_t v___x_6379_; 
v___x_6378_ = lean_uint64_shift_right(v___y_6376_, v___y_6374_);
v___x_6379_ = lean_uint64_dec_eq(v___x_6378_, v___y_6373_);
if (v___x_6379_ == 0)
{
uint64_t v___x_6380_; 
v___x_6380_ = lean_uint64_add(v___y_6369_, v___y_6374_);
v___y_6354_ = v___y_6367_;
v___y_6355_ = v___y_6368_;
v___y_6356_ = v___y_6371_;
v___y_6357_ = v___y_6370_;
v___y_6358_ = v___y_6372_;
v___y_6359_ = v___y_6373_;
v___y_6360_ = v___y_6375_;
v___y_6361_ = v___y_6377_;
v___y_6362_ = v___x_6380_;
goto v___jp_6353_;
}
else
{
v___y_6354_ = v___y_6367_;
v___y_6355_ = v___y_6368_;
v___y_6356_ = v___y_6371_;
v___y_6357_ = v___y_6370_;
v___y_6358_ = v___y_6372_;
v___y_6359_ = v___y_6373_;
v___y_6360_ = v___y_6375_;
v___y_6361_ = v___y_6377_;
v___y_6362_ = v___y_6369_;
goto v___jp_6353_;
}
}
v___jp_6381_:
{
uint64_t v___x_6391_; uint64_t v___x_6392_; uint8_t v___x_6393_; 
v___x_6391_ = 4ULL;
v___x_6392_ = lean_uint64_shift_right(v___y_6389_, v___x_6391_);
v___x_6393_ = lean_uint64_dec_eq(v___x_6392_, v___y_6387_);
if (v___x_6393_ == 0)
{
v___y_6367_ = v___y_6382_;
v___y_6368_ = v___y_6383_;
v___y_6369_ = v___y_6390_;
v___y_6370_ = v___y_6385_;
v___y_6371_ = v___y_6384_;
v___y_6372_ = v___y_6386_;
v___y_6373_ = v___y_6387_;
v___y_6374_ = v___x_6391_;
v___y_6375_ = v___y_6388_;
v___y_6376_ = v___y_6389_;
v___y_6377_ = v___x_6392_;
goto v___jp_6366_;
}
else
{
v___y_6367_ = v___y_6382_;
v___y_6368_ = v___y_6383_;
v___y_6369_ = v___y_6390_;
v___y_6370_ = v___y_6385_;
v___y_6371_ = v___y_6384_;
v___y_6372_ = v___y_6386_;
v___y_6373_ = v___y_6387_;
v___y_6374_ = v___x_6391_;
v___y_6375_ = v___y_6388_;
v___y_6376_ = v___y_6389_;
v___y_6377_ = v___y_6389_;
goto v___jp_6366_;
}
}
v___jp_6394_:
{
uint64_t v___x_6406_; uint8_t v___x_6407_; 
v___x_6406_ = lean_uint64_shift_right(v___y_6397_, v___y_6401_);
v___x_6407_ = lean_uint64_dec_eq(v___x_6406_, v___y_6402_);
if (v___x_6407_ == 0)
{
uint64_t v___x_6408_; 
v___x_6408_ = lean_uint64_add(v___y_6403_, v___y_6401_);
v___y_6382_ = v___y_6395_;
v___y_6383_ = v___y_6396_;
v___y_6384_ = v___y_6399_;
v___y_6385_ = v___y_6398_;
v___y_6386_ = v___y_6400_;
v___y_6387_ = v___y_6402_;
v___y_6388_ = v___y_6404_;
v___y_6389_ = v___y_6405_;
v___y_6390_ = v___x_6408_;
goto v___jp_6381_;
}
else
{
v___y_6382_ = v___y_6395_;
v___y_6383_ = v___y_6396_;
v___y_6384_ = v___y_6399_;
v___y_6385_ = v___y_6398_;
v___y_6386_ = v___y_6400_;
v___y_6387_ = v___y_6402_;
v___y_6388_ = v___y_6404_;
v___y_6389_ = v___y_6405_;
v___y_6390_ = v___y_6403_;
goto v___jp_6381_;
}
}
v___jp_6409_:
{
uint64_t v___x_6419_; uint64_t v___x_6420_; uint8_t v___x_6421_; 
v___x_6419_ = 8ULL;
v___x_6420_ = lean_uint64_shift_right(v___y_6412_, v___x_6419_);
v___x_6421_ = lean_uint64_dec_eq(v___x_6420_, v___y_6416_);
if (v___x_6421_ == 0)
{
v___y_6395_ = v___y_6410_;
v___y_6396_ = v___y_6411_;
v___y_6397_ = v___y_6412_;
v___y_6398_ = v___y_6414_;
v___y_6399_ = v___y_6413_;
v___y_6400_ = v___y_6415_;
v___y_6401_ = v___x_6419_;
v___y_6402_ = v___y_6416_;
v___y_6403_ = v___y_6418_;
v___y_6404_ = v___y_6417_;
v___y_6405_ = v___x_6420_;
goto v___jp_6394_;
}
else
{
v___y_6395_ = v___y_6410_;
v___y_6396_ = v___y_6411_;
v___y_6397_ = v___y_6412_;
v___y_6398_ = v___y_6414_;
v___y_6399_ = v___y_6413_;
v___y_6400_ = v___y_6415_;
v___y_6401_ = v___x_6419_;
v___y_6402_ = v___y_6416_;
v___y_6403_ = v___y_6418_;
v___y_6404_ = v___y_6417_;
v___y_6405_ = v___y_6412_;
goto v___jp_6394_;
}
}
v___jp_6422_:
{
uint64_t v___x_6434_; uint8_t v___x_6435_; 
v___x_6434_ = lean_uint64_shift_right(v___y_6432_, v___y_6430_);
v___x_6435_ = lean_uint64_dec_eq(v___x_6434_, v___y_6429_);
if (v___x_6435_ == 0)
{
uint64_t v___x_6436_; 
v___x_6436_ = lean_uint64_add(v___y_6428_, v___y_6430_);
v___y_6410_ = v___y_6423_;
v___y_6411_ = v___y_6424_;
v___y_6412_ = v___y_6433_;
v___y_6413_ = v___y_6426_;
v___y_6414_ = v___y_6425_;
v___y_6415_ = v___y_6427_;
v___y_6416_ = v___y_6429_;
v___y_6417_ = v___y_6431_;
v___y_6418_ = v___x_6436_;
goto v___jp_6409_;
}
else
{
v___y_6410_ = v___y_6423_;
v___y_6411_ = v___y_6424_;
v___y_6412_ = v___y_6433_;
v___y_6413_ = v___y_6426_;
v___y_6414_ = v___y_6425_;
v___y_6415_ = v___y_6427_;
v___y_6416_ = v___y_6429_;
v___y_6417_ = v___y_6431_;
v___y_6418_ = v___y_6428_;
goto v___jp_6409_;
}
}
v___jp_6437_:
{
uint64_t v___x_6447_; uint64_t v___x_6448_; uint8_t v___x_6449_; 
v___x_6447_ = 16ULL;
v___x_6448_ = lean_uint64_shift_right(v___y_6445_, v___x_6447_);
v___x_6449_ = lean_uint64_dec_eq(v___x_6448_, v___y_6443_);
if (v___x_6449_ == 0)
{
v___y_6423_ = v___y_6438_;
v___y_6424_ = v___y_6439_;
v___y_6425_ = v___y_6441_;
v___y_6426_ = v___y_6440_;
v___y_6427_ = v___y_6442_;
v___y_6428_ = v___y_6446_;
v___y_6429_ = v___y_6443_;
v___y_6430_ = v___x_6447_;
v___y_6431_ = v___y_6444_;
v___y_6432_ = v___y_6445_;
v___y_6433_ = v___x_6448_;
goto v___jp_6422_;
}
else
{
v___y_6423_ = v___y_6438_;
v___y_6424_ = v___y_6439_;
v___y_6425_ = v___y_6441_;
v___y_6426_ = v___y_6440_;
v___y_6427_ = v___y_6442_;
v___y_6428_ = v___y_6446_;
v___y_6429_ = v___y_6443_;
v___y_6430_ = v___x_6447_;
v___y_6431_ = v___y_6444_;
v___y_6432_ = v___y_6445_;
v___y_6433_ = v___y_6445_;
goto v___jp_6422_;
}
}
v___jp_6450_:
{
uint64_t v___x_6460_; uint8_t v___x_6461_; 
v___x_6460_ = lean_uint64_shift_right(v___y_6454_, v___y_6453_);
v___x_6461_ = lean_uint64_dec_eq(v___x_6460_, v___y_6457_);
if (v___x_6461_ == 0)
{
v___y_6438_ = v___y_6451_;
v___y_6439_ = v___y_6452_;
v___y_6440_ = v___y_6455_;
v___y_6441_ = v___y_6454_;
v___y_6442_ = v___y_6456_;
v___y_6443_ = v___y_6457_;
v___y_6444_ = v___y_6458_;
v___y_6445_ = v___y_6459_;
v___y_6446_ = v___y_6453_;
goto v___jp_6437_;
}
else
{
v___y_6438_ = v___y_6451_;
v___y_6439_ = v___y_6452_;
v___y_6440_ = v___y_6455_;
v___y_6441_ = v___y_6454_;
v___y_6442_ = v___y_6456_;
v___y_6443_ = v___y_6457_;
v___y_6444_ = v___y_6458_;
v___y_6445_ = v___y_6459_;
v___y_6446_ = v___y_6457_;
goto v___jp_6437_;
}
}
v___jp_6462_:
{
uint64_t v___x_6471_; uint64_t v___x_6472_; uint8_t v___x_6473_; 
v___x_6471_ = lean_uint64_mul(v___y_6464_, v___y_6469_);
v___x_6472_ = 0ULL;
v___x_6473_ = lean_uint64_dec_eq(v___x_6471_, v___x_6472_);
if (v___x_6473_ == 0)
{
uint64_t v___x_6474_; uint64_t v___x_6475_; uint64_t v___x_6476_; uint8_t v___x_6477_; 
v___x_6474_ = lean_uint64_add(v___y_6467_, v___y_6470_);
v___x_6475_ = 32ULL;
v___x_6476_ = lean_uint64_shift_right(v___x_6471_, v___x_6475_);
v___x_6477_ = lean_uint64_dec_eq(v___x_6476_, v___x_6472_);
if (v___x_6477_ == 0)
{
v___y_6451_ = v___y_6463_;
v___y_6452_ = v___x_6474_;
v___y_6453_ = v___x_6475_;
v___y_6454_ = v___x_6471_;
v___y_6455_ = v___y_6465_;
v___y_6456_ = v___y_6466_;
v___y_6457_ = v___x_6472_;
v___y_6458_ = v___y_6468_;
v___y_6459_ = v___x_6476_;
goto v___jp_6450_;
}
else
{
v___y_6451_ = v___y_6463_;
v___y_6452_ = v___x_6474_;
v___y_6453_ = v___x_6475_;
v___y_6454_ = v___x_6471_;
v___y_6455_ = v___y_6465_;
v___y_6456_ = v___y_6466_;
v___y_6457_ = v___x_6472_;
v___y_6458_ = v___y_6468_;
v___y_6459_ = v___x_6471_;
goto v___jp_6450_;
}
}
else
{
if (v___y_6466_ == 0)
{
uint32_t v___x_6478_; 
v___x_6478_ = 0;
v___y_6165_ = v___x_6478_;
goto v___jp_6164_;
}
else
{
uint32_t v___x_6479_; 
v___x_6479_ = 2147483648;
v___y_6165_ = v___x_6479_;
goto v___jp_6164_;
}
}
}
v___jp_6480_:
{
uint64_t v___x_6489_; uint64_t v___x_6490_; uint8_t v___x_6491_; 
v___x_6489_ = lean_uint32_to_uint64(v___y_6487_);
v___x_6490_ = 0ULL;
v___x_6491_ = lean_uint64_dec_eq(v___x_6489_, v___x_6490_);
if (v___x_6491_ == 0)
{
uint64_t v___x_6492_; uint64_t v___x_6493_; 
v___x_6492_ = 1ULL;
v___x_6493_ = lean_uint64_sub(v___x_6489_, v___x_6492_);
v___y_6463_ = v___y_6481_;
v___y_6464_ = v___y_6482_;
v___y_6465_ = v___y_6483_;
v___y_6466_ = v___y_6484_;
v___y_6467_ = v___y_6488_;
v___y_6468_ = v___y_6486_;
v___y_6469_ = v___y_6485_;
v___y_6470_ = v___x_6493_;
goto v___jp_6462_;
}
else
{
v___y_6463_ = v___y_6481_;
v___y_6464_ = v___y_6482_;
v___y_6465_ = v___y_6483_;
v___y_6466_ = v___y_6484_;
v___y_6467_ = v___y_6488_;
v___y_6468_ = v___y_6486_;
v___y_6469_ = v___y_6485_;
v___y_6470_ = v___x_6490_;
goto v___jp_6462_;
}
}
v___jp_6494_:
{
uint64_t v___x_6503_; uint64_t v___x_6504_; uint8_t v___x_6505_; 
v___x_6503_ = lean_uint32_to_uint64(v___y_6497_);
v___x_6504_ = 0ULL;
v___x_6505_ = lean_uint64_dec_eq(v___x_6503_, v___x_6504_);
if (v___x_6505_ == 0)
{
uint64_t v___x_6506_; uint64_t v___x_6507_; 
v___x_6506_ = 1ULL;
v___x_6507_ = lean_uint64_sub(v___x_6503_, v___x_6506_);
v___y_6481_ = v___y_6495_;
v___y_6482_ = v___y_6496_;
v___y_6483_ = v___y_6498_;
v___y_6484_ = v___y_6499_;
v___y_6485_ = v___y_6502_;
v___y_6486_ = v___y_6500_;
v___y_6487_ = v___y_6501_;
v___y_6488_ = v___x_6507_;
goto v___jp_6480_;
}
else
{
v___y_6481_ = v___y_6495_;
v___y_6482_ = v___y_6496_;
v___y_6483_ = v___y_6498_;
v___y_6484_ = v___y_6499_;
v___y_6485_ = v___y_6502_;
v___y_6486_ = v___y_6500_;
v___y_6487_ = v___y_6501_;
v___y_6488_ = v___x_6504_;
goto v___jp_6480_;
}
}
v___jp_6508_:
{
uint32_t v___x_6517_; uint8_t v___x_6518_; 
v___x_6517_ = 0;
v___x_6518_ = lean_uint32_dec_eq(v___y_6515_, v___x_6517_);
if (v___x_6518_ == 0)
{
uint64_t v___x_6519_; uint64_t v___x_6520_; uint64_t v___x_6521_; 
v___x_6519_ = lean_uint32_to_uint64(v___y_6510_);
v___x_6520_ = 8388608ULL;
v___x_6521_ = lean_uint64_lor(v___x_6519_, v___x_6520_);
v___y_6495_ = v___y_6509_;
v___y_6496_ = v___y_6516_;
v___y_6497_ = v___y_6512_;
v___y_6498_ = v___y_6511_;
v___y_6499_ = v___y_6513_;
v___y_6500_ = v___y_6514_;
v___y_6501_ = v___y_6515_;
v___y_6502_ = v___x_6521_;
goto v___jp_6494_;
}
else
{
uint64_t v___x_6522_; 
v___x_6522_ = lean_uint32_to_uint64(v___y_6510_);
v___y_6495_ = v___y_6509_;
v___y_6496_ = v___y_6516_;
v___y_6497_ = v___y_6512_;
v___y_6498_ = v___y_6511_;
v___y_6499_ = v___y_6513_;
v___y_6500_ = v___y_6514_;
v___y_6501_ = v___y_6515_;
v___y_6502_ = v___x_6522_;
goto v___jp_6494_;
}
}
v___jp_6523_:
{
uint32_t v___x_6531_; uint32_t v_xFraction_6532_; uint32_t v_yFraction_6533_; uint32_t v___x_6534_; uint8_t v___x_6535_; 
v___x_6531_ = 8388607;
v_xFraction_6532_ = lean_uint32_land(v___y_6527_, v___x_6531_);
v_yFraction_6533_ = lean_uint32_land(v___y_6525_, v___x_6531_);
v___x_6534_ = 0;
v___x_6535_ = lean_uint32_dec_eq(v___y_6526_, v___x_6534_);
if (v___x_6535_ == 0)
{
uint64_t v___x_6536_; uint64_t v___x_6537_; uint64_t v___x_6538_; 
v___x_6536_ = lean_uint32_to_uint64(v_xFraction_6532_);
v___x_6537_ = 8388608ULL;
v___x_6538_ = lean_uint64_lor(v___x_6536_, v___x_6537_);
v___y_6509_ = v___y_6524_;
v___y_6510_ = v_yFraction_6533_;
v___y_6511_ = v___x_6531_;
v___y_6512_ = v___y_6526_;
v___y_6513_ = v___y_6530_;
v___y_6514_ = v___y_6528_;
v___y_6515_ = v___y_6529_;
v___y_6516_ = v___x_6538_;
goto v___jp_6508_;
}
else
{
uint64_t v___x_6539_; 
v___x_6539_ = lean_uint32_to_uint64(v_xFraction_6532_);
v___y_6509_ = v___y_6524_;
v___y_6510_ = v_yFraction_6533_;
v___y_6511_ = v___x_6531_;
v___y_6512_ = v___y_6526_;
v___y_6513_ = v___y_6530_;
v___y_6514_ = v___y_6528_;
v___y_6515_ = v___y_6529_;
v___y_6516_ = v___x_6539_;
goto v___jp_6508_;
}
}
v___jp_6540_:
{
uint8_t v___x_6547_; 
v___x_6547_ = 1;
v___y_6524_ = v___y_6541_;
v___y_6525_ = v___y_6542_;
v___y_6526_ = v___y_6543_;
v___y_6527_ = v___y_6544_;
v___y_6528_ = v___y_6545_;
v___y_6529_ = v___y_6546_;
v___y_6530_ = v___x_6547_;
goto v___jp_6523_;
}
v___jp_6548_:
{
if (v___y_6550_ == 0)
{
if (v___y_6557_ == 0)
{
v___y_6524_ = v___y_6549_;
v___y_6525_ = v___y_6552_;
v___y_6526_ = v___y_6553_;
v___y_6527_ = v___y_6554_;
v___y_6528_ = v___y_6555_;
v___y_6529_ = v___y_6556_;
v___y_6530_ = v___y_6551_;
goto v___jp_6523_;
}
else
{
v___y_6541_ = v___y_6549_;
v___y_6542_ = v___y_6552_;
v___y_6543_ = v___y_6553_;
v___y_6544_ = v___y_6554_;
v___y_6545_ = v___y_6555_;
v___y_6546_ = v___y_6556_;
goto v___jp_6540_;
}
}
else
{
if (v___y_6557_ == 0)
{
v___y_6541_ = v___y_6549_;
v___y_6542_ = v___y_6552_;
v___y_6543_ = v___y_6553_;
v___y_6544_ = v___y_6554_;
v___y_6545_ = v___y_6555_;
v___y_6546_ = v___y_6556_;
goto v___jp_6540_;
}
else
{
v___y_6524_ = v___y_6549_;
v___y_6525_ = v___y_6552_;
v___y_6526_ = v___y_6553_;
v___y_6527_ = v___y_6554_;
v___y_6528_ = v___y_6555_;
v___y_6529_ = v___y_6556_;
v___y_6530_ = v___y_6551_;
goto v___jp_6523_;
}
}
}
v___jp_6558_:
{
uint32_t v___x_6567_; uint32_t v___x_6568_; uint32_t v___x_6569_; uint8_t v___x_6570_; 
v___x_6567_ = 2147483648;
v___x_6568_ = lean_uint32_land(v___y_6561_, v___x_6567_);
v___x_6569_ = 0;
v___x_6570_ = lean_uint32_dec_eq(v___x_6568_, v___x_6569_);
if (v___x_6570_ == 0)
{
uint8_t v___x_6571_; 
v___x_6571_ = 1;
v___y_6549_ = v___y_6559_;
v___y_6550_ = v___y_6566_;
v___y_6551_ = v___y_6560_;
v___y_6552_ = v___y_6561_;
v___y_6553_ = v___y_6562_;
v___y_6554_ = v___y_6563_;
v___y_6555_ = v___y_6564_;
v___y_6556_ = v___y_6565_;
v___y_6557_ = v___x_6571_;
goto v___jp_6548_;
}
else
{
v___y_6549_ = v___y_6559_;
v___y_6550_ = v___y_6566_;
v___y_6551_ = v___y_6560_;
v___y_6552_ = v___y_6561_;
v___y_6553_ = v___y_6562_;
v___y_6554_ = v___y_6563_;
v___y_6555_ = v___y_6564_;
v___y_6556_ = v___y_6565_;
v___y_6557_ = v___y_6560_;
goto v___jp_6548_;
}
}
v___jp_6577_:
{
if (v___y_6580_ == 0)
{
uint32_t v___x_6581_; uint32_t v___x_6582_; uint32_t v___x_6583_; uint32_t v_xExponent_6584_; uint32_t v___x_6585_; uint32_t v_yExponent_6586_; uint32_t v___x_6587_; uint32_t v___x_6588_; uint32_t v___x_6589_; uint8_t v___x_6590_; 
v___x_6581_ = 23;
v___x_6582_ = lean_uint32_shift_right(v___y_6579_, v___x_6581_);
v___x_6583_ = 255;
v_xExponent_6584_ = lean_uint32_land(v___x_6582_, v___x_6583_);
v___x_6585_ = lean_uint32_shift_right(v___y_6578_, v___x_6581_);
v_yExponent_6586_ = lean_uint32_land(v___x_6585_, v___x_6583_);
v___x_6587_ = 2147483648;
v___x_6588_ = lean_uint32_land(v___y_6579_, v___x_6587_);
v___x_6589_ = 0;
v___x_6590_ = lean_uint32_dec_eq(v___x_6588_, v___x_6589_);
if (v___x_6590_ == 0)
{
uint8_t v___x_6591_; 
v___x_6591_ = 1;
v___y_6559_ = v___x_6583_;
v___y_6560_ = v___y_6580_;
v___y_6561_ = v___y_6578_;
v___y_6562_ = v_xExponent_6584_;
v___y_6563_ = v___y_6579_;
v___y_6564_ = v___x_6581_;
v___y_6565_ = v_yExponent_6586_;
v___y_6566_ = v___x_6591_;
goto v___jp_6558_;
}
else
{
v___y_6559_ = v___x_6583_;
v___y_6560_ = v___y_6580_;
v___y_6561_ = v___y_6578_;
v___y_6562_ = v_xExponent_6584_;
v___y_6563_ = v___y_6579_;
v___y_6564_ = v___x_6581_;
v___y_6565_ = v_yExponent_6586_;
v___y_6566_ = v___y_6580_;
goto v___jp_6558_;
}
}
else
{
lean_object* v___x_6592_; lean_object* v___x_6593_; lean_object* v___x_6594_; uint32_t v___x_6595_; 
v___x_6592_ = lean_uint32_to_nat(v___y_6579_);
v___x_6593_ = lean_uint32_to_nat(v___y_6578_);
v___x_6594_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_6576_, v___x_6592_, v___x_6593_);
v___x_6595_ = lean_uint32_of_nat(v___x_6594_);
lean_dec(v___x_6594_);
v___y_6165_ = v___x_6595_;
goto v___jp_6164_;
}
}
v___jp_6596_:
{
uint32_t v___x_6599_; uint32_t v___x_6600_; uint32_t v___x_6601_; uint8_t v___x_6602_; 
v___x_6599_ = 4278190080;
v___x_6600_ = 1;
v___x_6601_ = lean_uint32_shift_left(v___y_6597_, v___x_6600_);
v___x_6602_ = lean_uint32_dec_le(v___x_6599_, v___x_6601_);
if (v___x_6602_ == 0)
{
uint32_t v___x_6603_; uint8_t v___x_6604_; 
v___x_6603_ = lean_uint32_shift_left(v___y_6598_, v___x_6600_);
v___x_6604_ = lean_uint32_dec_le(v___x_6599_, v___x_6603_);
v___y_6578_ = v___y_6598_;
v___y_6579_ = v___y_6597_;
v___y_6580_ = v___x_6604_;
goto v___jp_6577_;
}
else
{
v___y_6578_ = v___y_6598_;
v___y_6579_ = v___y_6597_;
v___y_6580_ = v___x_6602_;
goto v___jp_6577_;
}
}
v___jp_6606_:
{
lean_object* v___x_6608_; lean_object* v___x_6609_; lean_object* v___x_6610_; lean_object* v___x_6611_; lean_object* v___x_6612_; uint8_t v___x_6613_; 
v___x_6608_ = lean_nat_mul(v_fst_5335_, v_n_5338_);
v___x_6609_ = lean_nat_add(v___x_6608_, v_k_5344_);
lean_dec(v___x_6608_);
v___x_6610_ = lean_nat_mul(v___x_6609_, v_p_5339_);
lean_dec(v___x_6609_);
v___x_6611_ = lean_nat_add(v___x_6610_, v_snd_5340_);
lean_dec(v___x_6610_);
v___x_6612_ = lean_array_get_size(v_B_5341_);
v___x_6613_ = lean_nat_dec_lt(v___x_6611_, v___x_6612_);
if (v___x_6613_ == 0)
{
lean_dec(v___x_6611_);
v___y_6597_ = v___y_6607_;
v___y_6598_ = v___x_6605_;
goto v___jp_6596_;
}
else
{
lean_object* v___x_6614_; uint32_t v___x_6615_; 
v___x_6614_ = lean_array_fget_borrowed(v_B_5341_, v___x_6611_);
lean_dec(v___x_6611_);
v___x_6615_ = lean_unbox_uint32(v___x_6614_);
v___y_6597_ = v___y_6607_;
v___y_6598_ = v___x_6615_;
goto v___jp_6596_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0___boxed(lean_object* v_fst_6620_, lean_object* v_m_6621_, lean_object* v_fst_6622_, lean_object* v_n_6623_, lean_object* v_p_6624_, lean_object* v_snd_6625_, lean_object* v_B_6626_, lean_object* v_A_6627_, lean_object* v_acc_6628_, lean_object* v_k_6629_){
_start:
{
uint32_t v_acc_boxed_6630_; lean_object* v_res_6631_; 
v_acc_boxed_6630_ = lean_unbox_uint32(v_acc_6628_);
lean_dec(v_acc_6628_);
v_res_6631_ = lp_competition_Submission_bmm___lam__0(v_fst_6620_, v_m_6621_, v_fst_6622_, v_n_6623_, v_p_6624_, v_snd_6625_, v_B_6626_, v_A_6627_, v_acc_boxed_6630_, v_k_6629_);
lean_dec(v_k_6629_);
lean_dec_ref(v_A_6627_);
lean_dec_ref(v_B_6626_);
lean_dec(v_snd_6625_);
lean_dec(v_p_6624_);
lean_dec(v_n_6623_);
lean_dec(v_fst_6622_);
lean_dec(v_m_6621_);
lean_dec(v_fst_6620_);
return v_res_6631_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_bmm___lam__1(lean_object* v_m_6632_, lean_object* v_p_6633_, lean_object* v_n_6634_, lean_object* v_B_6635_, lean_object* v_A_6636_, lean_object* v_q_6637_){
_start:
{
lean_object* v___x_6638_; lean_object* v_snd_6639_; lean_object* v_fst_6640_; lean_object* v_fst_6641_; lean_object* v_snd_6642_; lean_object* v___f_6643_; lean_object* v___x_6644_; lean_object* v___x_6645_; lean_object* v___x_6646_; uint32_t v___x_6647_; 
v___x_6638_ = lp_competition_Competition_bmmDecodeC(v_m_6632_, v_p_6633_, v_q_6637_);
v_snd_6639_ = lean_ctor_get(v___x_6638_, 1);
lean_inc(v_snd_6639_);
v_fst_6640_ = lean_ctor_get(v___x_6638_, 0);
lean_inc(v_fst_6640_);
lean_dec_ref(v___x_6638_);
v_fst_6641_ = lean_ctor_get(v_snd_6639_, 0);
lean_inc(v_fst_6641_);
v_snd_6642_ = lean_ctor_get(v_snd_6639_, 1);
lean_inc(v_snd_6642_);
lean_dec(v_snd_6639_);
lean_inc(v_n_6634_);
v___f_6643_ = lean_alloc_closure((void*)(lp_competition_Submission_bmm___lam__0___boxed), 10, 8);
lean_closure_set(v___f_6643_, 0, v_fst_6640_);
lean_closure_set(v___f_6643_, 1, v_m_6632_);
lean_closure_set(v___f_6643_, 2, v_fst_6641_);
lean_closure_set(v___f_6643_, 3, v_n_6634_);
lean_closure_set(v___f_6643_, 4, v_p_6633_);
lean_closure_set(v___f_6643_, 5, v_snd_6642_);
lean_closure_set(v___f_6643_, 6, v_B_6635_);
lean_closure_set(v___f_6643_, 7, v_A_6636_);
v___x_6644_ = lean_unsigned_to_nat(0u);
v___x_6645_ = lp_competition_Submission_sum___redArg___boxed__const__1;
v___x_6646_ = l_Fin_foldl_loop___redArg(v_n_6634_, v___f_6643_, v___x_6645_, v___x_6644_);
lean_dec(v_n_6634_);
v___x_6647_ = lean_unbox_uint32(v___x_6646_);
lean_dec(v___x_6646_);
return v___x_6647_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__1___boxed(lean_object* v_m_6648_, lean_object* v_p_6649_, lean_object* v_n_6650_, lean_object* v_B_6651_, lean_object* v_A_6652_, lean_object* v_q_6653_){
_start:
{
uint32_t v_res_6654_; lean_object* v_r_6655_; 
v_res_6654_ = lp_competition_Submission_bmm___lam__1(v_m_6648_, v_p_6649_, v_n_6650_, v_B_6651_, v_A_6652_, v_q_6653_);
lean_dec(v_q_6653_);
v_r_6655_ = lean_box_uint32(v_res_6654_);
return v_r_6655_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_6656_, lean_object* v_m_6657_, lean_object* v_n_6658_, lean_object* v_p_6659_, lean_object* v_A_6660_, lean_object* v_B_6661_){
_start:
{
lean_object* v___f_6662_; lean_object* v___x_6663_; lean_object* v___x_6664_; lean_object* v___x_6665_; 
lean_inc(v_p_6659_);
lean_inc(v_m_6657_);
v___f_6662_ = lean_alloc_closure((void*)(lp_competition_Submission_bmm___lam__1___boxed), 6, 5);
lean_closure_set(v___f_6662_, 0, v_m_6657_);
lean_closure_set(v___f_6662_, 1, v_p_6659_);
lean_closure_set(v___f_6662_, 2, v_n_6658_);
lean_closure_set(v___f_6662_, 3, v_B_6661_);
lean_closure_set(v___f_6662_, 4, v_A_6660_);
v___x_6663_ = lean_nat_mul(v_batch_6656_, v_m_6657_);
lean_dec(v_m_6657_);
v___x_6664_ = lean_nat_mul(v___x_6663_, v_p_6659_);
lean_dec(v_p_6659_);
lean_dec(v___x_6663_);
v___x_6665_ = l_Array_ofFn___redArg(v___x_6664_, v___f_6662_);
return v___x_6665_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___boxed(lean_object* v_batch_6666_, lean_object* v_m_6667_, lean_object* v_n_6668_, lean_object* v_p_6669_, lean_object* v_A_6670_, lean_object* v_B_6671_){
_start:
{
lean_object* v_res_6672_; 
v_res_6672_ = lp_competition_Submission_bmm(v_batch_6666_, v_m_6667_, v_n_6668_, v_p_6669_, v_A_6670_, v_B_6671_);
lean_dec(v_batch_6666_);
return v_res_6672_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_ContractTensor(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_Submission(uint8_t builtin) {
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
res = initialize_competition_ContractTensor(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
lp_competition_Submission_TunedAdd_Plan = _init_lp_competition_Submission_TunedAdd_Plan();
lp_competition_Submission_FastMul_Plan = _init_lp_competition_Submission_FastMul_Plan();
lp_competition_Submission_sum___redArg___lam__0___boxed__const__1 = _init_lp_competition_Submission_sum___redArg___lam__0___boxed__const__1();
lean_mark_persistent(lp_competition_Submission_sum___redArg___lam__0___boxed__const__1);
lp_competition_Submission_sum___redArg___lam__0___boxed__const__2 = _init_lp_competition_Submission_sum___redArg___lam__0___boxed__const__2();
lean_mark_persistent(lp_competition_Submission_sum___redArg___lam__0___boxed__const__2);
lp_competition_Submission_sum___redArg___lam__0___boxed__const__3 = _init_lp_competition_Submission_sum___redArg___lam__0___boxed__const__3();
lean_mark_persistent(lp_competition_Submission_sum___redArg___lam__0___boxed__const__3);
lp_competition_Submission_sum___redArg___lam__0___boxed__const__4 = _init_lp_competition_Submission_sum___redArg___lam__0___boxed__const__4();
lean_mark_persistent(lp_competition_Submission_sum___redArg___lam__0___boxed__const__4);
lp_competition_Submission_sum___redArg___boxed__const__1 = _init_lp_competition_Submission_sum___redArg___boxed__const__1();
lean_mark_persistent(lp_competition_Submission_sum___redArg___boxed__const__1);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
