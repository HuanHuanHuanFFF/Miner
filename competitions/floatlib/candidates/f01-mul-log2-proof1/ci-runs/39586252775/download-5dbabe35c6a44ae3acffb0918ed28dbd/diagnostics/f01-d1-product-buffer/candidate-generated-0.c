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
lean_object* lp_competition_Competition_bmmDecodeC(lean_object*, lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
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
uint64_t lean_uint32_to_uint64(uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
lean_object* lean_nat_add(lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_nat_mul(lean_object*, lean_object*);
lean_object* lean_array_get_size(lean_object*);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
size_t lean_usize_of_nat(lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
size_t lean_usize_add(size_t, size_t);
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
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_add(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_add___boxed(lean_object*, lean_object*);
static const lean_ctor_object lp_competition_Submission_TunedAdd_Fmt___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 8, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(8) << 1) | 1)),((lean_object*)(((size_t)(23) << 1) | 1)),((lean_object*)(((size_t)(127) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
static const lean_object* lp_competition_Submission_TunedAdd_Fmt___closed__0 = (const lean_object*)&lp_competition_Submission_TunedAdd_Fmt___closed__0_value;
LEAN_EXPORT const lean_object* lp_competition_Submission_TunedAdd_Fmt = (const lean_object*)&lp_competition_Submission_TunedAdd_Fmt___closed__0_value;
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
LEAN_EXPORT const lean_object* lp_competition_Submission_FastMul_Fmt = (const lean_object*)&lp_competition_Submission_TunedAdd_Fmt___closed__0_value;
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_Plan;
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(lean_object*, size_t, size_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_sum___redArg___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_sum___redArg___closed__0;
static lean_once_cell_t lp_competition_Submission_sum___redArg___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static uint32_t lp_competition_Submission_sum___redArg___closed__1;
LEAN_EXPORT uint32_t lp_competition_Submission_sum___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_referenceBmm___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_hoistedBmm_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_hoistedBmm_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_hoistedBmm___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_hoistedBmm___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_hoistedBmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_hoistedBmm___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_bmm___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_add(uint32_t v_x_1146_, uint32_t v_y_1147_){
_start:
{
uint32_t v___y_1149_; uint32_t v___y_1153_; uint32_t v___y_1157_; uint32_t v___y_1158_; lean_object* v___y_1163_; uint64_t v___y_1164_; uint64_t v___y_1165_; uint32_t v___y_1180_; uint32_t v___y_1181_; uint32_t v___y_1182_; uint32_t v___y_1183_; uint32_t v___y_1184_; uint32_t v___y_1192_; uint32_t v___y_1193_; uint32_t v___y_1194_; lean_object* v___y_1195_; uint32_t v___y_1196_; uint32_t v___y_1201_; uint32_t v___y_1202_; uint64_t v___y_1203_; lean_object* v___y_1204_; uint64_t v___y_1205_; uint64_t v___y_1206_; uint8_t v___y_1216_; uint32_t v___y_1217_; uint32_t v___y_1218_; uint64_t v___y_1219_; lean_object* v___y_1220_; uint64_t v___y_1221_; uint64_t v___y_1222_; uint32_t v___y_1230_; uint64_t v___y_1231_; uint32_t v___y_1232_; lean_object* v___y_1233_; uint64_t v___y_1234_; uint64_t v___y_1235_; uint64_t v___y_1241_; uint32_t v___y_1242_; uint32_t v___y_1243_; lean_object* v___y_1244_; uint64_t v___y_1245_; lean_object* v___y_1246_; uint64_t v___y_1247_; uint64_t v___y_1248_; uint64_t v___y_1312_; uint32_t v___y_1313_; uint64_t v___y_1314_; uint32_t v___y_1315_; lean_object* v___y_1316_; lean_object* v___y_1317_; uint64_t v___y_1318_; uint64_t v___y_1319_; uint64_t v___y_1320_; uint64_t v___y_1326_; uint32_t v___y_1327_; uint64_t v___y_1328_; uint64_t v___y_1329_; uint32_t v___y_1330_; uint64_t v___y_1331_; lean_object* v___y_1332_; uint64_t v___y_1333_; lean_object* v___y_1334_; uint64_t v___y_1335_; uint64_t v___y_1336_; uint64_t v___y_1341_; uint32_t v___y_1342_; uint64_t v___y_1343_; uint32_t v___y_1344_; lean_object* v___y_1345_; lean_object* v___y_1346_; uint64_t v___y_1347_; uint64_t v___y_1348_; uint64_t v___y_1349_; uint64_t v___y_1354_; uint64_t v___y_1355_; uint32_t v___y_1356_; uint64_t v___y_1357_; uint64_t v___y_1358_; uint32_t v___y_1359_; lean_object* v___y_1360_; uint64_t v___y_1361_; lean_object* v___y_1362_; uint64_t v___y_1363_; uint64_t v___y_1364_; uint64_t v___y_1369_; uint64_t v___y_1370_; uint32_t v___y_1371_; uint32_t v___y_1372_; lean_object* v___y_1373_; lean_object* v___y_1374_; uint64_t v___y_1375_; uint64_t v___y_1376_; uint64_t v___y_1377_; uint64_t v___y_1382_; uint32_t v___y_1383_; uint64_t v___y_1384_; uint64_t v___y_1385_; uint32_t v___y_1386_; lean_object* v___y_1387_; uint64_t v___y_1388_; lean_object* v___y_1389_; uint64_t v___y_1390_; uint64_t v___y_1391_; uint64_t v___y_1392_; uint64_t v___y_1397_; uint32_t v___y_1398_; uint32_t v___y_1399_; lean_object* v___y_1400_; lean_object* v___y_1401_; uint64_t v___y_1402_; uint64_t v___y_1403_; uint64_t v___y_1404_; uint64_t v___y_1405_; uint64_t v___y_1410_; uint32_t v___y_1411_; uint64_t v___y_1412_; uint64_t v___y_1413_; uint32_t v___y_1414_; lean_object* v___y_1415_; uint64_t v___y_1416_; lean_object* v___y_1417_; uint64_t v___y_1418_; uint64_t v___y_1419_; uint64_t v___y_1420_; uint64_t v___y_1425_; uint32_t v___y_1426_; uint64_t v___y_1427_; uint32_t v___y_1428_; lean_object* v___y_1429_; lean_object* v___y_1430_; uint64_t v___y_1431_; uint64_t v___y_1432_; uint64_t v___y_1433_; uint64_t v___y_1438_; uint32_t v___y_1439_; uint32_t v___y_1440_; lean_object* v___y_1441_; uint64_t v___y_1442_; lean_object* v___y_1443_; uint64_t v___y_1444_; uint64_t v___y_1445_; uint64_t v___y_1446_; uint64_t v___y_1451_; uint32_t v___y_1452_; uint32_t v___y_1453_; lean_object* v_fst_1454_; lean_object* v_snd_1455_; uint32_t v___y_1470_; uint32_t v___y_1471_; uint64_t v___y_1476_; lean_object* v___y_1477_; uint64_t v___y_1478_; uint32_t v___y_1493_; uint32_t v___y_1494_; uint32_t v___y_1495_; uint32_t v___y_1496_; uint32_t v___y_1497_; uint32_t v___y_1505_; lean_object* v___y_1506_; uint32_t v___y_1507_; uint32_t v___y_1508_; uint32_t v___y_1509_; uint32_t v___y_1514_; uint64_t v___y_1515_; lean_object* v___y_1516_; uint32_t v___y_1517_; uint64_t v___y_1518_; uint64_t v___y_1519_; uint64_t v___y_1529_; uint32_t v___y_1530_; uint64_t v___y_1531_; lean_object* v___y_1532_; uint32_t v___y_1533_; uint8_t v___y_1534_; uint64_t v___y_1535_; uint32_t v___y_1543_; uint64_t v___y_1544_; uint64_t v___y_1545_; lean_object* v___y_1546_; uint32_t v___y_1547_; uint64_t v___y_1548_; uint64_t v___y_1554_; lean_object* v___y_1555_; uint32_t v___y_1556_; uint64_t v___y_1557_; lean_object* v___y_1558_; uint32_t v___y_1559_; uint64_t v___y_1560_; uint64_t v___y_1561_; lean_object* v___y_1625_; uint64_t v___y_1626_; uint32_t v___y_1627_; uint64_t v___y_1628_; uint64_t v___y_1629_; lean_object* v___y_1630_; uint32_t v___y_1631_; uint64_t v___y_1632_; uint64_t v___y_1633_; uint64_t v___y_1639_; uint64_t v___y_1640_; lean_object* v___y_1641_; uint32_t v___y_1642_; uint64_t v___y_1643_; lean_object* v___y_1644_; uint64_t v___y_1645_; uint32_t v___y_1646_; uint64_t v___y_1647_; uint64_t v___y_1648_; uint64_t v___y_1649_; lean_object* v___y_1654_; uint64_t v___y_1655_; uint32_t v___y_1656_; uint64_t v___y_1657_; lean_object* v___y_1658_; uint32_t v___y_1659_; uint64_t v___y_1660_; uint64_t v___y_1661_; uint64_t v___y_1662_; uint64_t v___y_1667_; lean_object* v___y_1668_; uint32_t v___y_1669_; uint64_t v___y_1670_; lean_object* v___y_1671_; uint32_t v___y_1672_; uint64_t v___y_1673_; uint64_t v___y_1674_; uint64_t v___y_1675_; uint64_t v___y_1676_; uint64_t v___y_1677_; lean_object* v___y_1682_; uint64_t v___y_1683_; uint32_t v___y_1684_; uint64_t v___y_1685_; lean_object* v___y_1686_; uint32_t v___y_1687_; uint64_t v___y_1688_; uint64_t v___y_1689_; uint64_t v___y_1690_; uint64_t v___y_1695_; lean_object* v___y_1696_; uint64_t v___y_1697_; uint32_t v___y_1698_; uint64_t v___y_1699_; lean_object* v___y_1700_; uint32_t v___y_1701_; uint64_t v___y_1702_; uint64_t v___y_1703_; uint64_t v___y_1704_; uint64_t v___y_1705_; lean_object* v___y_1710_; uint64_t v___y_1711_; uint32_t v___y_1712_; uint64_t v___y_1713_; uint64_t v___y_1714_; lean_object* v___y_1715_; uint32_t v___y_1716_; uint64_t v___y_1717_; uint64_t v___y_1718_; uint64_t v___y_1723_; lean_object* v___y_1724_; uint32_t v___y_1725_; uint64_t v___y_1726_; lean_object* v___y_1727_; uint64_t v___y_1728_; uint64_t v___y_1729_; uint32_t v___y_1730_; uint64_t v___y_1731_; uint64_t v___y_1732_; uint64_t v___y_1733_; lean_object* v___y_1738_; uint64_t v___y_1739_; uint32_t v___y_1740_; uint64_t v___y_1741_; lean_object* v___y_1742_; uint32_t v___y_1743_; uint64_t v___y_1744_; uint64_t v___y_1745_; uint64_t v___y_1746_; uint64_t v___y_1751_; lean_object* v___y_1752_; uint32_t v___y_1753_; uint64_t v___y_1754_; uint64_t v___y_1755_; lean_object* v___y_1756_; uint32_t v___y_1757_; uint64_t v___y_1758_; uint64_t v___y_1759_; uint32_t v___y_1764_; uint64_t v___y_1765_; uint32_t v___y_1766_; lean_object* v_fst_1767_; lean_object* v_snd_1768_; uint32_t v___y_1783_; uint64_t v___y_1784_; uint64_t v___y_1785_; uint64_t v___y_1786_; uint32_t v___y_1787_; uint8_t v___y_1788_; uint8_t v___y_1789_; uint8_t v___y_1790_; uint64_t v___y_1802_; uint32_t v___y_1803_; uint64_t v___y_1804_; uint64_t v___y_1805_; uint32_t v___y_1806_; uint8_t v___y_1807_; uint8_t v___y_1808_; uint8_t v___y_1809_; uint64_t v___y_1814_; uint32_t v___y_1815_; uint64_t v___y_1816_; uint64_t v___y_1817_; uint32_t v___y_1818_; uint8_t v___y_1819_; uint8_t v___y_1820_; uint8_t v___y_1821_; uint64_t v___y_1833_; uint32_t v___y_1834_; uint64_t v___y_1835_; uint64_t v___y_1836_; uint32_t v___y_1837_; uint8_t v___y_1838_; uint8_t v___y_1839_; uint8_t v___y_1840_; uint64_t v___y_1845_; uint32_t v___y_1846_; uint64_t v___y_1847_; uint64_t v___y_1848_; uint32_t v___y_1849_; uint8_t v___y_1850_; uint8_t v___y_1851_; uint64_t v___y_1852_; uint32_t v___y_1863_; uint32_t v___y_1864_; uint64_t v___y_1865_; uint64_t v___y_1866_; uint32_t v___y_1867_; uint8_t v___y_1868_; uint8_t v___y_1869_; uint64_t v___y_1870_; uint32_t v___y_1877_; uint64_t v___y_1878_; uint32_t v___y_1879_; uint32_t v___y_1880_; uint8_t v___y_1881_; uint32_t v___y_1882_; uint8_t v___y_1883_; uint64_t v___y_1884_; uint32_t v___y_1891_; uint32_t v___y_1892_; uint32_t v___y_1893_; uint8_t v___y_1894_; uint8_t v___y_1895_; uint32_t v___y_1896_; uint64_t v___y_1897_; uint32_t v___y_1907_; uint32_t v___y_1908_; uint32_t v___y_1909_; uint8_t v___y_1910_; uint32_t v___y_1911_; uint8_t v___y_1912_; uint8_t v___y_1922_; uint32_t v___y_1923_; uint32_t v___y_1924_; uint32_t v___y_1925_; uint32_t v___y_1926_; uint8_t v___y_1927_; uint8_t v___y_1934_; uint32_t v___x_1950_; uint32_t v___x_1951_; uint32_t v___x_1952_; uint32_t v___x_1953_; uint8_t v___x_1954_; 
v___x_1950_ = 4278190079;
v___x_1951_ = 1;
v___x_1952_ = lean_uint32_shift_left(v_x_1146_, v___x_1951_);
v___x_1953_ = lean_uint32_sub(v___x_1952_, v___x_1951_);
v___x_1954_ = lean_uint32_dec_le(v___x_1950_, v___x_1953_);
if (v___x_1954_ == 0)
{
uint32_t v___x_1955_; uint32_t v___x_1956_; uint8_t v___x_1957_; 
v___x_1955_ = lean_uint32_shift_left(v_y_1147_, v___x_1951_);
v___x_1956_ = lean_uint32_sub(v___x_1955_, v___x_1951_);
v___x_1957_ = lean_uint32_dec_le(v___x_1950_, v___x_1956_);
v___y_1934_ = v___x_1957_;
goto v___jp_1933_;
}
else
{
v___y_1934_ = v___x_1954_;
goto v___jp_1933_;
}
v___jp_1148_:
{
uint32_t v___x_1150_; uint32_t v___x_1151_; 
v___x_1150_ = 8388608;
v___x_1151_ = lean_uint32_lor(v___y_1149_, v___x_1150_);
return v___x_1151_;
}
v___jp_1152_:
{
uint32_t v___x_1154_; uint32_t v___x_1155_; 
v___x_1154_ = 8388608;
v___x_1155_ = lean_uint32_lor(v___y_1153_, v___x_1154_);
return v___x_1155_;
}
v___jp_1156_:
{
uint32_t v___x_1159_; uint32_t v___x_1160_; uint32_t v___x_1161_; 
v___x_1159_ = 8388607;
v___x_1160_ = lean_uint32_land(v___y_1157_, v___x_1159_);
v___x_1161_ = lean_uint32_lor(v___y_1158_, v___x_1160_);
return v___x_1161_;
}
v___jp_1162_:
{
uint8_t v___x_1166_; 
v___x_1166_ = lean_uint64_dec_eq(v___y_1165_, v___y_1164_);
if (v___x_1166_ == 0)
{
uint64_t v___x_1167_; uint8_t v___x_1168_; 
v___x_1167_ = 8388608ULL;
v___x_1168_ = lean_uint64_dec_eq(v___y_1165_, v___x_1167_);
if (v___x_1168_ == 0)
{
uint32_t v___x_1169_; uint8_t v___x_1170_; 
v___x_1169_ = lean_uint64_to_uint32(v___y_1165_);
v___x_1170_ = lean_unbox(v___y_1163_);
lean_dec(v___y_1163_);
if (v___x_1170_ == 0)
{
uint32_t v___x_1171_; 
v___x_1171_ = 0;
v___y_1157_ = v___x_1169_;
v___y_1158_ = v___x_1171_;
goto v___jp_1156_;
}
else
{
uint32_t v___x_1172_; 
v___x_1172_ = 2147483648;
v___y_1157_ = v___x_1169_;
v___y_1158_ = v___x_1172_;
goto v___jp_1156_;
}
}
else
{
uint8_t v___x_1173_; 
v___x_1173_ = lean_unbox(v___y_1163_);
lean_dec(v___y_1163_);
if (v___x_1173_ == 0)
{
uint32_t v___x_1174_; 
v___x_1174_ = 0;
v___y_1153_ = v___x_1174_;
goto v___jp_1152_;
}
else
{
uint32_t v___x_1175_; 
v___x_1175_ = 2147483648;
v___y_1153_ = v___x_1175_;
goto v___jp_1152_;
}
}
}
else
{
uint8_t v___x_1176_; 
v___x_1176_ = lean_unbox(v___y_1163_);
lean_dec(v___y_1163_);
if (v___x_1176_ == 0)
{
uint32_t v___x_1177_; 
v___x_1177_ = 0;
return v___x_1177_;
}
else
{
uint32_t v___x_1178_; 
v___x_1178_ = 2147483648;
return v___x_1178_;
}
}
}
v___jp_1179_:
{
uint32_t v___x_1185_; uint32_t v___x_1186_; uint32_t v___x_1187_; uint32_t v___x_1188_; uint32_t v___x_1189_; uint32_t v___x_1190_; 
v___x_1185_ = lean_uint32_land(v___y_1181_, v___y_1182_);
v___x_1186_ = lean_uint32_shift_left(v___x_1185_, v___y_1180_);
v___x_1187_ = lean_uint32_lor(v___y_1184_, v___x_1186_);
v___x_1188_ = 8388607;
v___x_1189_ = lean_uint32_land(v___y_1183_, v___x_1188_);
v___x_1190_ = lean_uint32_lor(v___x_1187_, v___x_1189_);
return v___x_1190_;
}
v___jp_1191_:
{
uint8_t v___x_1197_; 
v___x_1197_ = lean_unbox(v___y_1195_);
lean_dec(v___y_1195_);
if (v___x_1197_ == 0)
{
uint32_t v___x_1198_; 
v___x_1198_ = 0;
v___y_1180_ = v___y_1192_;
v___y_1181_ = v___y_1193_;
v___y_1182_ = v___y_1194_;
v___y_1183_ = v___y_1196_;
v___y_1184_ = v___x_1198_;
goto v___jp_1179_;
}
else
{
uint32_t v___x_1199_; 
v___x_1199_ = 2147483648;
v___y_1180_ = v___y_1192_;
v___y_1181_ = v___y_1193_;
v___y_1182_ = v___y_1194_;
v___y_1183_ = v___y_1196_;
v___y_1184_ = v___x_1199_;
goto v___jp_1179_;
}
}
v___jp_1200_:
{
uint64_t v___x_1207_; uint64_t v_encodedExponent_1208_; uint32_t v___x_1209_; uint64_t v___x_1210_; uint8_t v___x_1211_; 
v___x_1207_ = 171ULL;
v_encodedExponent_1208_ = lean_uint64_sub(v___y_1203_, v___x_1207_);
v___x_1209_ = lean_uint64_to_uint32(v_encodedExponent_1208_);
v___x_1210_ = 8388608ULL;
v___x_1211_ = lean_uint64_dec_lt(v___y_1206_, v___x_1210_);
if (v___x_1211_ == 0)
{
uint64_t v___x_1212_; uint32_t v___x_1213_; 
v___x_1212_ = lean_uint64_sub(v___y_1206_, v___x_1210_);
v___x_1213_ = lean_uint64_to_uint32(v___x_1212_);
v___y_1192_ = v___y_1201_;
v___y_1193_ = v___x_1209_;
v___y_1194_ = v___y_1202_;
v___y_1195_ = v___y_1204_;
v___y_1196_ = v___x_1213_;
goto v___jp_1191_;
}
else
{
uint32_t v___x_1214_; 
v___x_1214_ = lean_uint64_to_uint32(v___y_1205_);
v___y_1192_ = v___y_1201_;
v___y_1193_ = v___x_1209_;
v___y_1194_ = v___y_1202_;
v___y_1195_ = v___y_1204_;
v___y_1196_ = v___x_1214_;
goto v___jp_1191_;
}
}
v___jp_1215_:
{
uint64_t v___x_1223_; uint8_t v___x_1224_; 
v___x_1223_ = 425ULL;
v___x_1224_ = lean_uint64_dec_lt(v___x_1223_, v___y_1222_);
if (v___x_1224_ == 0)
{
if (v___y_1216_ == 0)
{
v___y_1201_ = v___y_1217_;
v___y_1202_ = v___y_1218_;
v___y_1203_ = v___y_1222_;
v___y_1204_ = v___y_1220_;
v___y_1205_ = v___y_1221_;
v___y_1206_ = v___y_1219_;
goto v___jp_1200_;
}
else
{
uint64_t v___x_1225_; 
v___x_1225_ = 8388608ULL;
v___y_1201_ = v___y_1217_;
v___y_1202_ = v___y_1218_;
v___y_1203_ = v___y_1222_;
v___y_1204_ = v___y_1220_;
v___y_1205_ = v___y_1221_;
v___y_1206_ = v___x_1225_;
goto v___jp_1200_;
}
}
else
{
uint8_t v___x_1226_; 
v___x_1226_ = lean_unbox(v___y_1220_);
lean_dec(v___y_1220_);
if (v___x_1226_ == 0)
{
uint32_t v___x_1227_; 
v___x_1227_ = 2139095040;
return v___x_1227_;
}
else
{
uint32_t v___x_1228_; 
v___x_1228_ = 4286578688;
return v___x_1228_;
}
}
}
v___jp_1229_:
{
uint64_t v___x_1236_; uint8_t v_carry_1237_; 
v___x_1236_ = 16777216ULL;
v_carry_1237_ = lean_uint64_dec_eq(v___y_1235_, v___x_1236_);
if (v_carry_1237_ == 0)
{
v___y_1216_ = v_carry_1237_;
v___y_1217_ = v___y_1230_;
v___y_1218_ = v___y_1232_;
v___y_1219_ = v___y_1235_;
v___y_1220_ = v___y_1233_;
v___y_1221_ = v___y_1234_;
v___y_1222_ = v___y_1231_;
goto v___jp_1215_;
}
else
{
uint64_t v___x_1238_; uint64_t v___x_1239_; 
v___x_1238_ = 1ULL;
v___x_1239_ = lean_uint64_add(v___y_1231_, v___x_1238_);
v___y_1216_ = v_carry_1237_;
v___y_1217_ = v___y_1230_;
v___y_1218_ = v___y_1232_;
v___y_1219_ = v___y_1235_;
v___y_1220_ = v___y_1233_;
v___y_1221_ = v___y_1234_;
v___y_1222_ = v___x_1239_;
goto v___jp_1215_;
}
}
v___jp_1240_:
{
uint64_t v_position_1249_; uint64_t v___x_1250_; uint8_t v___x_1251_; 
v_position_1249_ = lean_uint64_add(v___y_1248_, v___y_1241_);
v___x_1250_ = 172ULL;
v___x_1251_ = lean_uint64_dec_lt(v_position_1249_, v___x_1250_);
if (v___x_1251_ == 0)
{
uint64_t v___x_1252_; uint8_t v___x_1253_; 
v___x_1252_ = 23ULL;
v___x_1253_ = lean_uint64_dec_lt(v___y_1248_, v___x_1252_);
if (v___x_1253_ == 0)
{
uint64_t v___x_1254_; uint8_t v___x_1255_; 
v___x_1254_ = lean_uint64_sub(v___y_1248_, v___x_1252_);
v___x_1255_ = lean_uint64_dec_eq(v___x_1254_, v___y_1247_);
if (v___x_1255_ == 0)
{
uint64_t v___x_1256_; uint8_t v___x_1257_; 
v___x_1256_ = 64ULL;
v___x_1257_ = lean_uint64_dec_lt(v___x_1254_, v___x_1256_);
if (v___x_1257_ == 0)
{
uint8_t v___x_1258_; 
v___x_1258_ = lean_uint64_dec_eq(v___x_1254_, v___x_1256_);
if (v___x_1258_ == 0)
{
lean_dec(v___y_1244_);
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___y_1247_;
goto v___jp_1229_;
}
else
{
uint64_t v___x_1259_; uint64_t v___x_1260_; uint8_t v___x_1261_; 
v___x_1259_ = 9223372036854775808ULL;
v___x_1260_ = lean_unbox_uint64(v___y_1244_);
lean_dec(v___y_1244_);
v___x_1261_ = lean_uint64_dec_lt(v___x_1259_, v___x_1260_);
if (v___x_1261_ == 0)
{
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___y_1247_;
goto v___jp_1229_;
}
else
{
uint64_t v___x_1262_; 
v___x_1262_ = 1ULL;
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___x_1262_;
goto v___jp_1229_;
}
}
}
else
{
uint64_t v___x_1263_; uint64_t v_quotient_1264_; uint64_t v___x_1265_; uint64_t v___x_1266_; uint64_t v___x_1267_; uint64_t v___x_1268_; uint64_t v_remainder_1269_; uint64_t v___x_1270_; uint64_t v_half_1271_; uint8_t v___x_1272_; 
v___x_1263_ = lean_unbox_uint64(v___y_1244_);
v_quotient_1264_ = lean_uint64_shift_right(v___x_1263_, v___x_1254_);
v___x_1265_ = 1ULL;
v___x_1266_ = lean_uint64_shift_left(v___x_1265_, v___x_1254_);
v___x_1267_ = lean_uint64_sub(v___x_1266_, v___x_1265_);
v___x_1268_ = lean_unbox_uint64(v___y_1244_);
lean_dec(v___y_1244_);
v_remainder_1269_ = lean_uint64_land(v___x_1268_, v___x_1267_);
v___x_1270_ = lean_uint64_sub(v___x_1254_, v___x_1265_);
v_half_1271_ = lean_uint64_shift_left(v___x_1265_, v___x_1270_);
v___x_1272_ = lean_uint64_dec_lt(v_remainder_1269_, v_half_1271_);
if (v___x_1272_ == 0)
{
uint8_t v___x_1273_; 
v___x_1273_ = lean_uint64_dec_lt(v_half_1271_, v_remainder_1269_);
if (v___x_1273_ == 0)
{
uint64_t v___x_1274_; uint8_t v___x_1275_; 
v___x_1274_ = lean_uint64_land(v_quotient_1264_, v___x_1265_);
v___x_1275_ = lean_uint64_dec_eq(v___x_1274_, v___y_1247_);
if (v___x_1275_ == 0)
{
uint64_t v___x_1276_; 
v___x_1276_ = lean_uint64_add(v_quotient_1264_, v___x_1265_);
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___x_1276_;
goto v___jp_1229_;
}
else
{
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v_quotient_1264_;
goto v___jp_1229_;
}
}
else
{
uint64_t v___x_1277_; 
v___x_1277_ = lean_uint64_add(v_quotient_1264_, v___x_1265_);
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___x_1277_;
goto v___jp_1229_;
}
}
else
{
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v_quotient_1264_;
goto v___jp_1229_;
}
}
}
else
{
uint64_t v___x_1278_; 
v___x_1278_ = lean_unbox_uint64(v___y_1244_);
lean_dec(v___y_1244_);
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___x_1278_;
goto v___jp_1229_;
}
}
else
{
uint64_t v___x_1279_; uint64_t v___x_1280_; uint64_t v___x_1281_; 
v___x_1279_ = lean_uint64_sub(v___x_1252_, v___y_1248_);
v___x_1280_ = lean_unbox_uint64(v___y_1244_);
lean_dec(v___y_1244_);
v___x_1281_ = lean_uint64_shift_left(v___x_1280_, v___x_1279_);
v___y_1230_ = v___y_1242_;
v___y_1231_ = v_position_1249_;
v___y_1232_ = v___y_1243_;
v___y_1233_ = v___y_1246_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___x_1281_;
goto v___jp_1229_;
}
}
else
{
uint8_t v___x_1282_; 
v___x_1282_ = lean_uint64_dec_lt(v___y_1241_, v___y_1245_);
if (v___x_1282_ == 0)
{
uint64_t v___x_1283_; uint64_t v___x_1284_; uint64_t v___x_1285_; 
v___x_1283_ = lean_uint64_sub(v___y_1241_, v___y_1245_);
v___x_1284_ = lean_unbox_uint64(v___y_1244_);
lean_dec(v___y_1244_);
v___x_1285_ = lean_uint64_shift_left(v___x_1284_, v___x_1283_);
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v___x_1285_;
goto v___jp_1162_;
}
else
{
uint64_t v___x_1286_; uint8_t v___x_1287_; 
v___x_1286_ = lean_uint64_sub(v___y_1245_, v___y_1241_);
v___x_1287_ = lean_uint64_dec_eq(v___x_1286_, v___y_1247_);
if (v___x_1287_ == 0)
{
uint64_t v___x_1288_; uint8_t v___x_1289_; 
v___x_1288_ = 64ULL;
v___x_1289_ = lean_uint64_dec_lt(v___x_1286_, v___x_1288_);
if (v___x_1289_ == 0)
{
uint8_t v___x_1290_; 
v___x_1290_ = lean_uint64_dec_eq(v___x_1286_, v___x_1288_);
if (v___x_1290_ == 0)
{
lean_dec(v___y_1244_);
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v___y_1247_;
goto v___jp_1162_;
}
else
{
uint64_t v___x_1291_; uint64_t v___x_1292_; uint8_t v___x_1293_; 
v___x_1291_ = 9223372036854775808ULL;
v___x_1292_ = lean_unbox_uint64(v___y_1244_);
lean_dec(v___y_1244_);
v___x_1293_ = lean_uint64_dec_lt(v___x_1291_, v___x_1292_);
if (v___x_1293_ == 0)
{
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v___y_1247_;
goto v___jp_1162_;
}
else
{
uint64_t v___x_1294_; 
v___x_1294_ = 1ULL;
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v___x_1294_;
goto v___jp_1162_;
}
}
}
else
{
uint64_t v___x_1295_; uint64_t v_quotient_1296_; uint64_t v___x_1297_; uint64_t v___x_1298_; uint64_t v___x_1299_; uint64_t v___x_1300_; uint64_t v_remainder_1301_; uint64_t v___x_1302_; uint64_t v_half_1303_; uint8_t v___x_1304_; 
v___x_1295_ = lean_unbox_uint64(v___y_1244_);
v_quotient_1296_ = lean_uint64_shift_right(v___x_1295_, v___x_1286_);
v___x_1297_ = 1ULL;
v___x_1298_ = lean_uint64_shift_left(v___x_1297_, v___x_1286_);
v___x_1299_ = lean_uint64_sub(v___x_1298_, v___x_1297_);
v___x_1300_ = lean_unbox_uint64(v___y_1244_);
lean_dec(v___y_1244_);
v_remainder_1301_ = lean_uint64_land(v___x_1300_, v___x_1299_);
v___x_1302_ = lean_uint64_sub(v___x_1286_, v___x_1297_);
v_half_1303_ = lean_uint64_shift_left(v___x_1297_, v___x_1302_);
v___x_1304_ = lean_uint64_dec_lt(v_remainder_1301_, v_half_1303_);
if (v___x_1304_ == 0)
{
uint8_t v___x_1305_; 
v___x_1305_ = lean_uint64_dec_lt(v_half_1303_, v_remainder_1301_);
if (v___x_1305_ == 0)
{
uint64_t v___x_1306_; uint8_t v___x_1307_; 
v___x_1306_ = lean_uint64_land(v_quotient_1296_, v___x_1297_);
v___x_1307_ = lean_uint64_dec_eq(v___x_1306_, v___y_1247_);
if (v___x_1307_ == 0)
{
uint64_t v___x_1308_; 
v___x_1308_ = lean_uint64_add(v_quotient_1296_, v___x_1297_);
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v___x_1308_;
goto v___jp_1162_;
}
else
{
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v_quotient_1296_;
goto v___jp_1162_;
}
}
else
{
uint64_t v___x_1309_; 
v___x_1309_ = lean_uint64_add(v_quotient_1296_, v___x_1297_);
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v___x_1309_;
goto v___jp_1162_;
}
}
else
{
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v_quotient_1296_;
goto v___jp_1162_;
}
}
}
else
{
uint64_t v___x_1310_; 
v___x_1310_ = lean_unbox_uint64(v___y_1244_);
lean_dec(v___y_1244_);
v___y_1163_ = v___y_1246_;
v___y_1164_ = v___y_1247_;
v___y_1165_ = v___x_1310_;
goto v___jp_1162_;
}
}
}
}
v___jp_1311_:
{
uint64_t v___x_1321_; uint64_t v___x_1322_; uint8_t v___x_1323_; 
v___x_1321_ = 1ULL;
v___x_1322_ = lean_uint64_shift_right(v___y_1314_, v___x_1321_);
v___x_1323_ = lean_uint64_dec_eq(v___x_1322_, v___y_1319_);
if (v___x_1323_ == 0)
{
uint64_t v___x_1324_; 
v___x_1324_ = lean_uint64_add(v___y_1320_, v___x_1321_);
v___y_1241_ = v___y_1312_;
v___y_1242_ = v___y_1313_;
v___y_1243_ = v___y_1315_;
v___y_1244_ = v___y_1316_;
v___y_1245_ = v___y_1318_;
v___y_1246_ = v___y_1317_;
v___y_1247_ = v___y_1319_;
v___y_1248_ = v___x_1324_;
goto v___jp_1240_;
}
else
{
v___y_1241_ = v___y_1312_;
v___y_1242_ = v___y_1313_;
v___y_1243_ = v___y_1315_;
v___y_1244_ = v___y_1316_;
v___y_1245_ = v___y_1318_;
v___y_1246_ = v___y_1317_;
v___y_1247_ = v___y_1319_;
v___y_1248_ = v___y_1320_;
goto v___jp_1240_;
}
}
v___jp_1325_:
{
uint64_t v___x_1337_; uint8_t v___x_1338_; 
v___x_1337_ = lean_uint64_shift_right(v___y_1328_, v___y_1331_);
v___x_1338_ = lean_uint64_dec_eq(v___x_1337_, v___y_1335_);
if (v___x_1338_ == 0)
{
uint64_t v___x_1339_; 
v___x_1339_ = lean_uint64_add(v___y_1329_, v___y_1331_);
v___y_1312_ = v___y_1326_;
v___y_1313_ = v___y_1327_;
v___y_1314_ = v___y_1336_;
v___y_1315_ = v___y_1330_;
v___y_1316_ = v___y_1332_;
v___y_1317_ = v___y_1334_;
v___y_1318_ = v___y_1333_;
v___y_1319_ = v___y_1335_;
v___y_1320_ = v___x_1339_;
goto v___jp_1311_;
}
else
{
v___y_1312_ = v___y_1326_;
v___y_1313_ = v___y_1327_;
v___y_1314_ = v___y_1336_;
v___y_1315_ = v___y_1330_;
v___y_1316_ = v___y_1332_;
v___y_1317_ = v___y_1334_;
v___y_1318_ = v___y_1333_;
v___y_1319_ = v___y_1335_;
v___y_1320_ = v___y_1329_;
goto v___jp_1311_;
}
}
v___jp_1340_:
{
uint64_t v___x_1350_; uint64_t v___x_1351_; uint8_t v___x_1352_; 
v___x_1350_ = 2ULL;
v___x_1351_ = lean_uint64_shift_right(v___y_1343_, v___x_1350_);
v___x_1352_ = lean_uint64_dec_eq(v___x_1351_, v___y_1348_);
if (v___x_1352_ == 0)
{
v___y_1326_ = v___y_1341_;
v___y_1327_ = v___y_1342_;
v___y_1328_ = v___y_1343_;
v___y_1329_ = v___y_1349_;
v___y_1330_ = v___y_1344_;
v___y_1331_ = v___x_1350_;
v___y_1332_ = v___y_1345_;
v___y_1333_ = v___y_1347_;
v___y_1334_ = v___y_1346_;
v___y_1335_ = v___y_1348_;
v___y_1336_ = v___x_1351_;
goto v___jp_1325_;
}
else
{
v___y_1326_ = v___y_1341_;
v___y_1327_ = v___y_1342_;
v___y_1328_ = v___y_1343_;
v___y_1329_ = v___y_1349_;
v___y_1330_ = v___y_1344_;
v___y_1331_ = v___x_1350_;
v___y_1332_ = v___y_1345_;
v___y_1333_ = v___y_1347_;
v___y_1334_ = v___y_1346_;
v___y_1335_ = v___y_1348_;
v___y_1336_ = v___y_1343_;
goto v___jp_1325_;
}
}
v___jp_1353_:
{
uint64_t v___x_1365_; uint8_t v___x_1366_; 
v___x_1365_ = lean_uint64_shift_right(v___y_1355_, v___y_1358_);
v___x_1366_ = lean_uint64_dec_eq(v___x_1365_, v___y_1363_);
if (v___x_1366_ == 0)
{
uint64_t v___x_1367_; 
v___x_1367_ = lean_uint64_add(v___y_1357_, v___y_1358_);
v___y_1341_ = v___y_1354_;
v___y_1342_ = v___y_1356_;
v___y_1343_ = v___y_1364_;
v___y_1344_ = v___y_1359_;
v___y_1345_ = v___y_1360_;
v___y_1346_ = v___y_1362_;
v___y_1347_ = v___y_1361_;
v___y_1348_ = v___y_1363_;
v___y_1349_ = v___x_1367_;
goto v___jp_1340_;
}
else
{
v___y_1341_ = v___y_1354_;
v___y_1342_ = v___y_1356_;
v___y_1343_ = v___y_1364_;
v___y_1344_ = v___y_1359_;
v___y_1345_ = v___y_1360_;
v___y_1346_ = v___y_1362_;
v___y_1347_ = v___y_1361_;
v___y_1348_ = v___y_1363_;
v___y_1349_ = v___y_1357_;
goto v___jp_1340_;
}
}
v___jp_1368_:
{
uint64_t v___x_1378_; uint64_t v___x_1379_; uint8_t v___x_1380_; 
v___x_1378_ = 4ULL;
v___x_1379_ = lean_uint64_shift_right(v___y_1370_, v___x_1378_);
v___x_1380_ = lean_uint64_dec_eq(v___x_1379_, v___y_1376_);
if (v___x_1380_ == 0)
{
v___y_1354_ = v___y_1369_;
v___y_1355_ = v___y_1370_;
v___y_1356_ = v___y_1371_;
v___y_1357_ = v___y_1377_;
v___y_1358_ = v___x_1378_;
v___y_1359_ = v___y_1372_;
v___y_1360_ = v___y_1373_;
v___y_1361_ = v___y_1375_;
v___y_1362_ = v___y_1374_;
v___y_1363_ = v___y_1376_;
v___y_1364_ = v___x_1379_;
goto v___jp_1353_;
}
else
{
v___y_1354_ = v___y_1369_;
v___y_1355_ = v___y_1370_;
v___y_1356_ = v___y_1371_;
v___y_1357_ = v___y_1377_;
v___y_1358_ = v___x_1378_;
v___y_1359_ = v___y_1372_;
v___y_1360_ = v___y_1373_;
v___y_1361_ = v___y_1375_;
v___y_1362_ = v___y_1374_;
v___y_1363_ = v___y_1376_;
v___y_1364_ = v___y_1370_;
goto v___jp_1353_;
}
}
v___jp_1381_:
{
uint64_t v___x_1393_; uint8_t v___x_1394_; 
v___x_1393_ = lean_uint64_shift_right(v___y_1391_, v___y_1384_);
v___x_1394_ = lean_uint64_dec_eq(v___x_1393_, v___y_1390_);
if (v___x_1394_ == 0)
{
uint64_t v___x_1395_; 
v___x_1395_ = lean_uint64_add(v___y_1385_, v___y_1384_);
v___y_1369_ = v___y_1382_;
v___y_1370_ = v___y_1392_;
v___y_1371_ = v___y_1383_;
v___y_1372_ = v___y_1386_;
v___y_1373_ = v___y_1387_;
v___y_1374_ = v___y_1389_;
v___y_1375_ = v___y_1388_;
v___y_1376_ = v___y_1390_;
v___y_1377_ = v___x_1395_;
goto v___jp_1368_;
}
else
{
v___y_1369_ = v___y_1382_;
v___y_1370_ = v___y_1392_;
v___y_1371_ = v___y_1383_;
v___y_1372_ = v___y_1386_;
v___y_1373_ = v___y_1387_;
v___y_1374_ = v___y_1389_;
v___y_1375_ = v___y_1388_;
v___y_1376_ = v___y_1390_;
v___y_1377_ = v___y_1385_;
goto v___jp_1368_;
}
}
v___jp_1396_:
{
uint64_t v___x_1406_; uint64_t v___x_1407_; uint8_t v___x_1408_; 
v___x_1406_ = 8ULL;
v___x_1407_ = lean_uint64_shift_right(v___y_1404_, v___x_1406_);
v___x_1408_ = lean_uint64_dec_eq(v___x_1407_, v___y_1403_);
if (v___x_1408_ == 0)
{
v___y_1382_ = v___y_1397_;
v___y_1383_ = v___y_1398_;
v___y_1384_ = v___x_1406_;
v___y_1385_ = v___y_1405_;
v___y_1386_ = v___y_1399_;
v___y_1387_ = v___y_1400_;
v___y_1388_ = v___y_1402_;
v___y_1389_ = v___y_1401_;
v___y_1390_ = v___y_1403_;
v___y_1391_ = v___y_1404_;
v___y_1392_ = v___x_1407_;
goto v___jp_1381_;
}
else
{
v___y_1382_ = v___y_1397_;
v___y_1383_ = v___y_1398_;
v___y_1384_ = v___x_1406_;
v___y_1385_ = v___y_1405_;
v___y_1386_ = v___y_1399_;
v___y_1387_ = v___y_1400_;
v___y_1388_ = v___y_1402_;
v___y_1389_ = v___y_1401_;
v___y_1390_ = v___y_1403_;
v___y_1391_ = v___y_1404_;
v___y_1392_ = v___y_1404_;
goto v___jp_1381_;
}
}
v___jp_1409_:
{
uint64_t v___x_1421_; uint8_t v___x_1422_; 
v___x_1421_ = lean_uint64_shift_right(v___y_1413_, v___y_1418_);
v___x_1422_ = lean_uint64_dec_eq(v___x_1421_, v___y_1419_);
if (v___x_1422_ == 0)
{
uint64_t v___x_1423_; 
v___x_1423_ = lean_uint64_add(v___y_1412_, v___y_1418_);
v___y_1397_ = v___y_1410_;
v___y_1398_ = v___y_1411_;
v___y_1399_ = v___y_1414_;
v___y_1400_ = v___y_1415_;
v___y_1401_ = v___y_1417_;
v___y_1402_ = v___y_1416_;
v___y_1403_ = v___y_1419_;
v___y_1404_ = v___y_1420_;
v___y_1405_ = v___x_1423_;
goto v___jp_1396_;
}
else
{
v___y_1397_ = v___y_1410_;
v___y_1398_ = v___y_1411_;
v___y_1399_ = v___y_1414_;
v___y_1400_ = v___y_1415_;
v___y_1401_ = v___y_1417_;
v___y_1402_ = v___y_1416_;
v___y_1403_ = v___y_1419_;
v___y_1404_ = v___y_1420_;
v___y_1405_ = v___y_1412_;
goto v___jp_1396_;
}
}
v___jp_1424_:
{
uint64_t v___x_1434_; uint64_t v___x_1435_; uint8_t v___x_1436_; 
v___x_1434_ = 16ULL;
v___x_1435_ = lean_uint64_shift_right(v___y_1427_, v___x_1434_);
v___x_1436_ = lean_uint64_dec_eq(v___x_1435_, v___y_1432_);
if (v___x_1436_ == 0)
{
v___y_1410_ = v___y_1425_;
v___y_1411_ = v___y_1426_;
v___y_1412_ = v___y_1433_;
v___y_1413_ = v___y_1427_;
v___y_1414_ = v___y_1428_;
v___y_1415_ = v___y_1429_;
v___y_1416_ = v___y_1431_;
v___y_1417_ = v___y_1430_;
v___y_1418_ = v___x_1434_;
v___y_1419_ = v___y_1432_;
v___y_1420_ = v___x_1435_;
goto v___jp_1409_;
}
else
{
v___y_1410_ = v___y_1425_;
v___y_1411_ = v___y_1426_;
v___y_1412_ = v___y_1433_;
v___y_1413_ = v___y_1427_;
v___y_1414_ = v___y_1428_;
v___y_1415_ = v___y_1429_;
v___y_1416_ = v___y_1431_;
v___y_1417_ = v___y_1430_;
v___y_1418_ = v___x_1434_;
v___y_1419_ = v___y_1432_;
v___y_1420_ = v___y_1427_;
goto v___jp_1409_;
}
}
v___jp_1437_:
{
uint64_t v___x_1447_; uint64_t v___x_1448_; uint8_t v___x_1449_; 
v___x_1447_ = lean_unbox_uint64(v___y_1441_);
v___x_1448_ = lean_uint64_shift_right(v___x_1447_, v___y_1445_);
v___x_1449_ = lean_uint64_dec_eq(v___x_1448_, v___y_1444_);
if (v___x_1449_ == 0)
{
v___y_1425_ = v___y_1438_;
v___y_1426_ = v___y_1439_;
v___y_1427_ = v___y_1446_;
v___y_1428_ = v___y_1440_;
v___y_1429_ = v___y_1441_;
v___y_1430_ = v___y_1443_;
v___y_1431_ = v___y_1442_;
v___y_1432_ = v___y_1444_;
v___y_1433_ = v___y_1445_;
goto v___jp_1424_;
}
else
{
v___y_1425_ = v___y_1438_;
v___y_1426_ = v___y_1439_;
v___y_1427_ = v___y_1446_;
v___y_1428_ = v___y_1440_;
v___y_1429_ = v___y_1441_;
v___y_1430_ = v___y_1443_;
v___y_1431_ = v___y_1442_;
v___y_1432_ = v___y_1444_;
v___y_1433_ = v___y_1444_;
goto v___jp_1424_;
}
}
v___jp_1450_:
{
uint64_t v___x_1456_; uint64_t v___x_1457_; uint8_t v___x_1458_; 
v___x_1456_ = 0ULL;
v___x_1457_ = lean_unbox_uint64(v_snd_1455_);
v___x_1458_ = lean_uint64_dec_eq(v___x_1457_, v___x_1456_);
if (v___x_1458_ == 0)
{
uint64_t v___x_1459_; uint64_t v___x_1460_; uint64_t v___x_1461_; uint64_t v___x_1462_; uint64_t v___x_1463_; uint8_t v___x_1464_; 
v___x_1459_ = 149ULL;
v___x_1460_ = lean_uint64_add(v___y_1451_, v___x_1459_);
v___x_1461_ = 32ULL;
v___x_1462_ = lean_unbox_uint64(v_snd_1455_);
v___x_1463_ = lean_uint64_shift_right(v___x_1462_, v___x_1461_);
v___x_1464_ = lean_uint64_dec_eq(v___x_1463_, v___x_1456_);
if (v___x_1464_ == 0)
{
v___y_1438_ = v___x_1460_;
v___y_1439_ = v___y_1452_;
v___y_1440_ = v___y_1453_;
v___y_1441_ = v_snd_1455_;
v___y_1442_ = v___x_1459_;
v___y_1443_ = v_fst_1454_;
v___y_1444_ = v___x_1456_;
v___y_1445_ = v___x_1461_;
v___y_1446_ = v___x_1463_;
goto v___jp_1437_;
}
else
{
uint64_t v___x_1465_; 
v___x_1465_ = lean_unbox_uint64(v_snd_1455_);
v___y_1438_ = v___x_1460_;
v___y_1439_ = v___y_1452_;
v___y_1440_ = v___y_1453_;
v___y_1441_ = v_snd_1455_;
v___y_1442_ = v___x_1459_;
v___y_1443_ = v_fst_1454_;
v___y_1444_ = v___x_1456_;
v___y_1445_ = v___x_1461_;
v___y_1446_ = v___x_1465_;
goto v___jp_1437_;
}
}
else
{
uint8_t v___x_1466_; 
lean_dec(v_snd_1455_);
v___x_1466_ = lean_unbox(v_fst_1454_);
lean_dec(v_fst_1454_);
if (v___x_1466_ == 0)
{
uint32_t v___x_1467_; 
v___x_1467_ = 0;
return v___x_1467_;
}
else
{
uint32_t v___x_1468_; 
v___x_1468_ = 2147483648;
return v___x_1468_;
}
}
}
v___jp_1469_:
{
uint32_t v___x_1472_; uint32_t v___x_1473_; uint32_t v___x_1474_; 
v___x_1472_ = 8388607;
v___x_1473_ = lean_uint32_land(v___y_1470_, v___x_1472_);
v___x_1474_ = lean_uint32_lor(v___y_1471_, v___x_1473_);
return v___x_1474_;
}
v___jp_1475_:
{
uint8_t v___x_1479_; 
v___x_1479_ = lean_uint64_dec_eq(v___y_1478_, v___y_1476_);
if (v___x_1479_ == 0)
{
uint64_t v___x_1480_; uint8_t v___x_1481_; 
v___x_1480_ = 8388608ULL;
v___x_1481_ = lean_uint64_dec_eq(v___y_1478_, v___x_1480_);
if (v___x_1481_ == 0)
{
uint32_t v___x_1482_; uint8_t v___x_1483_; 
v___x_1482_ = lean_uint64_to_uint32(v___y_1478_);
v___x_1483_ = lean_unbox(v___y_1477_);
lean_dec(v___y_1477_);
if (v___x_1483_ == 0)
{
uint32_t v___x_1484_; 
v___x_1484_ = 0;
v___y_1470_ = v___x_1482_;
v___y_1471_ = v___x_1484_;
goto v___jp_1469_;
}
else
{
uint32_t v___x_1485_; 
v___x_1485_ = 2147483648;
v___y_1470_ = v___x_1482_;
v___y_1471_ = v___x_1485_;
goto v___jp_1469_;
}
}
else
{
uint8_t v___x_1486_; 
v___x_1486_ = lean_unbox(v___y_1477_);
lean_dec(v___y_1477_);
if (v___x_1486_ == 0)
{
uint32_t v___x_1487_; 
v___x_1487_ = 0;
v___y_1149_ = v___x_1487_;
goto v___jp_1148_;
}
else
{
uint32_t v___x_1488_; 
v___x_1488_ = 2147483648;
v___y_1149_ = v___x_1488_;
goto v___jp_1148_;
}
}
}
else
{
uint8_t v___x_1489_; 
v___x_1489_ = lean_unbox(v___y_1477_);
lean_dec(v___y_1477_);
if (v___x_1489_ == 0)
{
uint32_t v___x_1490_; 
v___x_1490_ = 0;
return v___x_1490_;
}
else
{
uint32_t v___x_1491_; 
v___x_1491_ = 2147483648;
return v___x_1491_;
}
}
}
v___jp_1492_:
{
uint32_t v___x_1498_; uint32_t v___x_1499_; uint32_t v___x_1500_; uint32_t v___x_1501_; uint32_t v___x_1502_; uint32_t v___x_1503_; 
v___x_1498_ = lean_uint32_land(v___y_1496_, v___y_1495_);
v___x_1499_ = lean_uint32_shift_left(v___x_1498_, v___y_1493_);
v___x_1500_ = lean_uint32_lor(v___y_1497_, v___x_1499_);
v___x_1501_ = 8388607;
v___x_1502_ = lean_uint32_land(v___y_1494_, v___x_1501_);
v___x_1503_ = lean_uint32_lor(v___x_1500_, v___x_1502_);
return v___x_1503_;
}
v___jp_1504_:
{
uint8_t v___x_1510_; 
v___x_1510_ = lean_unbox(v___y_1506_);
lean_dec(v___y_1506_);
if (v___x_1510_ == 0)
{
uint32_t v___x_1511_; 
v___x_1511_ = 0;
v___y_1493_ = v___y_1505_;
v___y_1494_ = v___y_1509_;
v___y_1495_ = v___y_1507_;
v___y_1496_ = v___y_1508_;
v___y_1497_ = v___x_1511_;
goto v___jp_1492_;
}
else
{
uint32_t v___x_1512_; 
v___x_1512_ = 2147483648;
v___y_1493_ = v___y_1505_;
v___y_1494_ = v___y_1509_;
v___y_1495_ = v___y_1507_;
v___y_1496_ = v___y_1508_;
v___y_1497_ = v___x_1512_;
goto v___jp_1492_;
}
}
v___jp_1513_:
{
uint64_t v___x_1520_; uint64_t v_encodedExponent_1521_; uint32_t v___x_1522_; uint64_t v___x_1523_; uint8_t v___x_1524_; 
v___x_1520_ = 171ULL;
v_encodedExponent_1521_ = lean_uint64_sub(v___y_1518_, v___x_1520_);
v___x_1522_ = lean_uint64_to_uint32(v_encodedExponent_1521_);
v___x_1523_ = 8388608ULL;
v___x_1524_ = lean_uint64_dec_lt(v___y_1519_, v___x_1523_);
if (v___x_1524_ == 0)
{
uint64_t v___x_1525_; uint32_t v___x_1526_; 
v___x_1525_ = lean_uint64_sub(v___y_1519_, v___x_1523_);
v___x_1526_ = lean_uint64_to_uint32(v___x_1525_);
v___y_1505_ = v___y_1514_;
v___y_1506_ = v___y_1516_;
v___y_1507_ = v___y_1517_;
v___y_1508_ = v___x_1522_;
v___y_1509_ = v___x_1526_;
goto v___jp_1504_;
}
else
{
uint32_t v___x_1527_; 
v___x_1527_ = lean_uint64_to_uint32(v___y_1515_);
v___y_1505_ = v___y_1514_;
v___y_1506_ = v___y_1516_;
v___y_1507_ = v___y_1517_;
v___y_1508_ = v___x_1522_;
v___y_1509_ = v___x_1527_;
goto v___jp_1504_;
}
}
v___jp_1528_:
{
uint64_t v___x_1536_; uint8_t v___x_1537_; 
v___x_1536_ = 425ULL;
v___x_1537_ = lean_uint64_dec_lt(v___x_1536_, v___y_1535_);
if (v___x_1537_ == 0)
{
if (v___y_1534_ == 0)
{
v___y_1514_ = v___y_1530_;
v___y_1515_ = v___y_1531_;
v___y_1516_ = v___y_1532_;
v___y_1517_ = v___y_1533_;
v___y_1518_ = v___y_1535_;
v___y_1519_ = v___y_1529_;
goto v___jp_1513_;
}
else
{
uint64_t v___x_1538_; 
v___x_1538_ = 8388608ULL;
v___y_1514_ = v___y_1530_;
v___y_1515_ = v___y_1531_;
v___y_1516_ = v___y_1532_;
v___y_1517_ = v___y_1533_;
v___y_1518_ = v___y_1535_;
v___y_1519_ = v___x_1538_;
goto v___jp_1513_;
}
}
else
{
uint8_t v___x_1539_; 
v___x_1539_ = lean_unbox(v___y_1532_);
lean_dec(v___y_1532_);
if (v___x_1539_ == 0)
{
uint32_t v___x_1540_; 
v___x_1540_ = 2139095040;
return v___x_1540_;
}
else
{
uint32_t v___x_1541_; 
v___x_1541_ = 4286578688;
return v___x_1541_;
}
}
}
v___jp_1542_:
{
uint64_t v___x_1549_; uint8_t v_carry_1550_; 
v___x_1549_ = 16777216ULL;
v_carry_1550_ = lean_uint64_dec_eq(v___y_1548_, v___x_1549_);
if (v_carry_1550_ == 0)
{
v___y_1529_ = v___y_1548_;
v___y_1530_ = v___y_1543_;
v___y_1531_ = v___y_1544_;
v___y_1532_ = v___y_1546_;
v___y_1533_ = v___y_1547_;
v___y_1534_ = v_carry_1550_;
v___y_1535_ = v___y_1545_;
goto v___jp_1528_;
}
else
{
uint64_t v___x_1551_; uint64_t v___x_1552_; 
v___x_1551_ = 1ULL;
v___x_1552_ = lean_uint64_add(v___y_1545_, v___x_1551_);
v___y_1529_ = v___y_1548_;
v___y_1530_ = v___y_1543_;
v___y_1531_ = v___y_1544_;
v___y_1532_ = v___y_1546_;
v___y_1533_ = v___y_1547_;
v___y_1534_ = v_carry_1550_;
v___y_1535_ = v___x_1552_;
goto v___jp_1528_;
}
}
v___jp_1553_:
{
uint64_t v_position_1562_; uint64_t v___x_1563_; uint8_t v___x_1564_; 
v_position_1562_ = lean_uint64_add(v___y_1561_, v___y_1560_);
v___x_1563_ = 172ULL;
v___x_1564_ = lean_uint64_dec_lt(v_position_1562_, v___x_1563_);
if (v___x_1564_ == 0)
{
uint64_t v___x_1565_; uint8_t v___x_1566_; 
v___x_1565_ = 23ULL;
v___x_1566_ = lean_uint64_dec_lt(v___y_1561_, v___x_1565_);
if (v___x_1566_ == 0)
{
uint64_t v___x_1567_; uint8_t v___x_1568_; 
v___x_1567_ = lean_uint64_sub(v___y_1561_, v___x_1565_);
v___x_1568_ = lean_uint64_dec_eq(v___x_1567_, v___y_1557_);
if (v___x_1568_ == 0)
{
uint64_t v___x_1569_; uint8_t v___x_1570_; 
v___x_1569_ = 64ULL;
v___x_1570_ = lean_uint64_dec_lt(v___x_1567_, v___x_1569_);
if (v___x_1570_ == 0)
{
uint8_t v___x_1571_; 
v___x_1571_ = lean_uint64_dec_eq(v___x_1567_, v___x_1569_);
if (v___x_1571_ == 0)
{
lean_dec(v___y_1555_);
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___y_1557_;
goto v___jp_1542_;
}
else
{
uint64_t v___x_1572_; uint64_t v___x_1573_; uint8_t v___x_1574_; 
v___x_1572_ = 9223372036854775808ULL;
v___x_1573_ = lean_unbox_uint64(v___y_1555_);
lean_dec(v___y_1555_);
v___x_1574_ = lean_uint64_dec_lt(v___x_1572_, v___x_1573_);
if (v___x_1574_ == 0)
{
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___y_1557_;
goto v___jp_1542_;
}
else
{
uint64_t v___x_1575_; 
v___x_1575_ = 1ULL;
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___x_1575_;
goto v___jp_1542_;
}
}
}
else
{
uint64_t v___x_1576_; uint64_t v_quotient_1577_; uint64_t v___x_1578_; uint64_t v___x_1579_; uint64_t v___x_1580_; uint64_t v___x_1581_; uint64_t v_remainder_1582_; uint64_t v___x_1583_; uint64_t v_half_1584_; uint8_t v___x_1585_; 
v___x_1576_ = lean_unbox_uint64(v___y_1555_);
v_quotient_1577_ = lean_uint64_shift_right(v___x_1576_, v___x_1567_);
v___x_1578_ = 1ULL;
v___x_1579_ = lean_uint64_shift_left(v___x_1578_, v___x_1567_);
v___x_1580_ = lean_uint64_sub(v___x_1579_, v___x_1578_);
v___x_1581_ = lean_unbox_uint64(v___y_1555_);
lean_dec(v___y_1555_);
v_remainder_1582_ = lean_uint64_land(v___x_1581_, v___x_1580_);
v___x_1583_ = lean_uint64_sub(v___x_1567_, v___x_1578_);
v_half_1584_ = lean_uint64_shift_left(v___x_1578_, v___x_1583_);
v___x_1585_ = lean_uint64_dec_lt(v_remainder_1582_, v_half_1584_);
if (v___x_1585_ == 0)
{
uint8_t v___x_1586_; 
v___x_1586_ = lean_uint64_dec_lt(v_half_1584_, v_remainder_1582_);
if (v___x_1586_ == 0)
{
uint64_t v___x_1587_; uint8_t v___x_1588_; 
v___x_1587_ = lean_uint64_land(v_quotient_1577_, v___x_1578_);
v___x_1588_ = lean_uint64_dec_eq(v___x_1587_, v___y_1557_);
if (v___x_1588_ == 0)
{
uint64_t v___x_1589_; 
v___x_1589_ = lean_uint64_add(v_quotient_1577_, v___x_1578_);
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___x_1589_;
goto v___jp_1542_;
}
else
{
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v_quotient_1577_;
goto v___jp_1542_;
}
}
else
{
uint64_t v___x_1590_; 
v___x_1590_ = lean_uint64_add(v_quotient_1577_, v___x_1578_);
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___x_1590_;
goto v___jp_1542_;
}
}
else
{
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v_quotient_1577_;
goto v___jp_1542_;
}
}
}
else
{
uint64_t v___x_1591_; 
v___x_1591_ = lean_unbox_uint64(v___y_1555_);
lean_dec(v___y_1555_);
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___x_1591_;
goto v___jp_1542_;
}
}
else
{
uint64_t v___x_1592_; uint64_t v___x_1593_; uint64_t v___x_1594_; 
v___x_1592_ = lean_uint64_sub(v___x_1565_, v___y_1561_);
v___x_1593_ = lean_unbox_uint64(v___y_1555_);
lean_dec(v___y_1555_);
v___x_1594_ = lean_uint64_shift_left(v___x_1593_, v___x_1592_);
v___y_1543_ = v___y_1556_;
v___y_1544_ = v___y_1557_;
v___y_1545_ = v_position_1562_;
v___y_1546_ = v___y_1558_;
v___y_1547_ = v___y_1559_;
v___y_1548_ = v___x_1594_;
goto v___jp_1542_;
}
}
else
{
uint8_t v___x_1595_; 
v___x_1595_ = lean_uint64_dec_lt(v___y_1560_, v___y_1554_);
if (v___x_1595_ == 0)
{
uint64_t v___x_1596_; uint64_t v___x_1597_; uint64_t v___x_1598_; 
v___x_1596_ = lean_uint64_sub(v___y_1560_, v___y_1554_);
v___x_1597_ = lean_unbox_uint64(v___y_1555_);
lean_dec(v___y_1555_);
v___x_1598_ = lean_uint64_shift_left(v___x_1597_, v___x_1596_);
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v___x_1598_;
goto v___jp_1475_;
}
else
{
uint64_t v___x_1599_; uint8_t v___x_1600_; 
v___x_1599_ = lean_uint64_sub(v___y_1554_, v___y_1560_);
v___x_1600_ = lean_uint64_dec_eq(v___x_1599_, v___y_1557_);
if (v___x_1600_ == 0)
{
uint64_t v___x_1601_; uint8_t v___x_1602_; 
v___x_1601_ = 64ULL;
v___x_1602_ = lean_uint64_dec_lt(v___x_1599_, v___x_1601_);
if (v___x_1602_ == 0)
{
uint8_t v___x_1603_; 
v___x_1603_ = lean_uint64_dec_eq(v___x_1599_, v___x_1601_);
if (v___x_1603_ == 0)
{
lean_dec(v___y_1555_);
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v___y_1557_;
goto v___jp_1475_;
}
else
{
uint64_t v___x_1604_; uint64_t v___x_1605_; uint8_t v___x_1606_; 
v___x_1604_ = 9223372036854775808ULL;
v___x_1605_ = lean_unbox_uint64(v___y_1555_);
lean_dec(v___y_1555_);
v___x_1606_ = lean_uint64_dec_lt(v___x_1604_, v___x_1605_);
if (v___x_1606_ == 0)
{
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v___y_1557_;
goto v___jp_1475_;
}
else
{
uint64_t v___x_1607_; 
v___x_1607_ = 1ULL;
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v___x_1607_;
goto v___jp_1475_;
}
}
}
else
{
uint64_t v___x_1608_; uint64_t v_quotient_1609_; uint64_t v___x_1610_; uint64_t v___x_1611_; uint64_t v___x_1612_; uint64_t v___x_1613_; uint64_t v_remainder_1614_; uint64_t v___x_1615_; uint64_t v_half_1616_; uint8_t v___x_1617_; 
v___x_1608_ = lean_unbox_uint64(v___y_1555_);
v_quotient_1609_ = lean_uint64_shift_right(v___x_1608_, v___x_1599_);
v___x_1610_ = 1ULL;
v___x_1611_ = lean_uint64_shift_left(v___x_1610_, v___x_1599_);
v___x_1612_ = lean_uint64_sub(v___x_1611_, v___x_1610_);
v___x_1613_ = lean_unbox_uint64(v___y_1555_);
lean_dec(v___y_1555_);
v_remainder_1614_ = lean_uint64_land(v___x_1613_, v___x_1612_);
v___x_1615_ = lean_uint64_sub(v___x_1599_, v___x_1610_);
v_half_1616_ = lean_uint64_shift_left(v___x_1610_, v___x_1615_);
v___x_1617_ = lean_uint64_dec_lt(v_remainder_1614_, v_half_1616_);
if (v___x_1617_ == 0)
{
uint8_t v___x_1618_; 
v___x_1618_ = lean_uint64_dec_lt(v_half_1616_, v_remainder_1614_);
if (v___x_1618_ == 0)
{
uint64_t v___x_1619_; uint8_t v___x_1620_; 
v___x_1619_ = lean_uint64_land(v_quotient_1609_, v___x_1610_);
v___x_1620_ = lean_uint64_dec_eq(v___x_1619_, v___y_1557_);
if (v___x_1620_ == 0)
{
uint64_t v___x_1621_; 
v___x_1621_ = lean_uint64_add(v_quotient_1609_, v___x_1610_);
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v___x_1621_;
goto v___jp_1475_;
}
else
{
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v_quotient_1609_;
goto v___jp_1475_;
}
}
else
{
uint64_t v___x_1622_; 
v___x_1622_ = lean_uint64_add(v_quotient_1609_, v___x_1610_);
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v___x_1622_;
goto v___jp_1475_;
}
}
else
{
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v_quotient_1609_;
goto v___jp_1475_;
}
}
}
else
{
uint64_t v___x_1623_; 
v___x_1623_ = lean_unbox_uint64(v___y_1555_);
lean_dec(v___y_1555_);
v___y_1476_ = v___y_1557_;
v___y_1477_ = v___y_1558_;
v___y_1478_ = v___x_1623_;
goto v___jp_1475_;
}
}
}
}
v___jp_1624_:
{
uint64_t v___x_1634_; uint64_t v___x_1635_; uint8_t v___x_1636_; 
v___x_1634_ = 1ULL;
v___x_1635_ = lean_uint64_shift_right(v___y_1628_, v___x_1634_);
v___x_1636_ = lean_uint64_dec_eq(v___x_1635_, v___y_1629_);
if (v___x_1636_ == 0)
{
uint64_t v___x_1637_; 
v___x_1637_ = lean_uint64_add(v___y_1633_, v___x_1634_);
v___y_1554_ = v___y_1626_;
v___y_1555_ = v___y_1625_;
v___y_1556_ = v___y_1627_;
v___y_1557_ = v___y_1629_;
v___y_1558_ = v___y_1630_;
v___y_1559_ = v___y_1631_;
v___y_1560_ = v___y_1632_;
v___y_1561_ = v___x_1637_;
goto v___jp_1553_;
}
else
{
v___y_1554_ = v___y_1626_;
v___y_1555_ = v___y_1625_;
v___y_1556_ = v___y_1627_;
v___y_1557_ = v___y_1629_;
v___y_1558_ = v___y_1630_;
v___y_1559_ = v___y_1631_;
v___y_1560_ = v___y_1632_;
v___y_1561_ = v___y_1633_;
goto v___jp_1553_;
}
}
v___jp_1638_:
{
uint64_t v___x_1650_; uint8_t v___x_1651_; 
v___x_1650_ = lean_uint64_shift_right(v___y_1645_, v___y_1648_);
v___x_1651_ = lean_uint64_dec_eq(v___x_1650_, v___y_1643_);
if (v___x_1651_ == 0)
{
uint64_t v___x_1652_; 
v___x_1652_ = lean_uint64_add(v___y_1639_, v___y_1648_);
v___y_1625_ = v___y_1641_;
v___y_1626_ = v___y_1640_;
v___y_1627_ = v___y_1642_;
v___y_1628_ = v___y_1649_;
v___y_1629_ = v___y_1643_;
v___y_1630_ = v___y_1644_;
v___y_1631_ = v___y_1646_;
v___y_1632_ = v___y_1647_;
v___y_1633_ = v___x_1652_;
goto v___jp_1624_;
}
else
{
v___y_1625_ = v___y_1641_;
v___y_1626_ = v___y_1640_;
v___y_1627_ = v___y_1642_;
v___y_1628_ = v___y_1649_;
v___y_1629_ = v___y_1643_;
v___y_1630_ = v___y_1644_;
v___y_1631_ = v___y_1646_;
v___y_1632_ = v___y_1647_;
v___y_1633_ = v___y_1639_;
goto v___jp_1624_;
}
}
v___jp_1653_:
{
uint64_t v___x_1663_; uint64_t v___x_1664_; uint8_t v___x_1665_; 
v___x_1663_ = 2ULL;
v___x_1664_ = lean_uint64_shift_right(v___y_1660_, v___x_1663_);
v___x_1665_ = lean_uint64_dec_eq(v___x_1664_, v___y_1657_);
if (v___x_1665_ == 0)
{
v___y_1639_ = v___y_1662_;
v___y_1640_ = v___y_1655_;
v___y_1641_ = v___y_1654_;
v___y_1642_ = v___y_1656_;
v___y_1643_ = v___y_1657_;
v___y_1644_ = v___y_1658_;
v___y_1645_ = v___y_1660_;
v___y_1646_ = v___y_1659_;
v___y_1647_ = v___y_1661_;
v___y_1648_ = v___x_1663_;
v___y_1649_ = v___x_1664_;
goto v___jp_1638_;
}
else
{
v___y_1639_ = v___y_1662_;
v___y_1640_ = v___y_1655_;
v___y_1641_ = v___y_1654_;
v___y_1642_ = v___y_1656_;
v___y_1643_ = v___y_1657_;
v___y_1644_ = v___y_1658_;
v___y_1645_ = v___y_1660_;
v___y_1646_ = v___y_1659_;
v___y_1647_ = v___y_1661_;
v___y_1648_ = v___x_1663_;
v___y_1649_ = v___y_1660_;
goto v___jp_1638_;
}
}
v___jp_1666_:
{
uint64_t v___x_1678_; uint8_t v___x_1679_; 
v___x_1678_ = lean_uint64_shift_right(v___y_1676_, v___y_1674_);
v___x_1679_ = lean_uint64_dec_eq(v___x_1678_, v___y_1670_);
if (v___x_1679_ == 0)
{
uint64_t v___x_1680_; 
v___x_1680_ = lean_uint64_add(v___y_1673_, v___y_1674_);
v___y_1654_ = v___y_1668_;
v___y_1655_ = v___y_1667_;
v___y_1656_ = v___y_1669_;
v___y_1657_ = v___y_1670_;
v___y_1658_ = v___y_1671_;
v___y_1659_ = v___y_1672_;
v___y_1660_ = v___y_1677_;
v___y_1661_ = v___y_1675_;
v___y_1662_ = v___x_1680_;
goto v___jp_1653_;
}
else
{
v___y_1654_ = v___y_1668_;
v___y_1655_ = v___y_1667_;
v___y_1656_ = v___y_1669_;
v___y_1657_ = v___y_1670_;
v___y_1658_ = v___y_1671_;
v___y_1659_ = v___y_1672_;
v___y_1660_ = v___y_1677_;
v___y_1661_ = v___y_1675_;
v___y_1662_ = v___y_1673_;
goto v___jp_1653_;
}
}
v___jp_1681_:
{
uint64_t v___x_1691_; uint64_t v___x_1692_; uint8_t v___x_1693_; 
v___x_1691_ = 4ULL;
v___x_1692_ = lean_uint64_shift_right(v___y_1689_, v___x_1691_);
v___x_1693_ = lean_uint64_dec_eq(v___x_1692_, v___y_1685_);
if (v___x_1693_ == 0)
{
v___y_1667_ = v___y_1683_;
v___y_1668_ = v___y_1682_;
v___y_1669_ = v___y_1684_;
v___y_1670_ = v___y_1685_;
v___y_1671_ = v___y_1686_;
v___y_1672_ = v___y_1687_;
v___y_1673_ = v___y_1690_;
v___y_1674_ = v___x_1691_;
v___y_1675_ = v___y_1688_;
v___y_1676_ = v___y_1689_;
v___y_1677_ = v___x_1692_;
goto v___jp_1666_;
}
else
{
v___y_1667_ = v___y_1683_;
v___y_1668_ = v___y_1682_;
v___y_1669_ = v___y_1684_;
v___y_1670_ = v___y_1685_;
v___y_1671_ = v___y_1686_;
v___y_1672_ = v___y_1687_;
v___y_1673_ = v___y_1690_;
v___y_1674_ = v___x_1691_;
v___y_1675_ = v___y_1688_;
v___y_1676_ = v___y_1689_;
v___y_1677_ = v___y_1689_;
goto v___jp_1666_;
}
}
v___jp_1694_:
{
uint64_t v___x_1706_; uint8_t v___x_1707_; 
v___x_1706_ = lean_uint64_shift_right(v___y_1697_, v___y_1704_);
v___x_1707_ = lean_uint64_dec_eq(v___x_1706_, v___y_1699_);
if (v___x_1707_ == 0)
{
uint64_t v___x_1708_; 
v___x_1708_ = lean_uint64_add(v___y_1702_, v___y_1704_);
v___y_1682_ = v___y_1696_;
v___y_1683_ = v___y_1695_;
v___y_1684_ = v___y_1698_;
v___y_1685_ = v___y_1699_;
v___y_1686_ = v___y_1700_;
v___y_1687_ = v___y_1701_;
v___y_1688_ = v___y_1703_;
v___y_1689_ = v___y_1705_;
v___y_1690_ = v___x_1708_;
goto v___jp_1681_;
}
else
{
v___y_1682_ = v___y_1696_;
v___y_1683_ = v___y_1695_;
v___y_1684_ = v___y_1698_;
v___y_1685_ = v___y_1699_;
v___y_1686_ = v___y_1700_;
v___y_1687_ = v___y_1701_;
v___y_1688_ = v___y_1703_;
v___y_1689_ = v___y_1705_;
v___y_1690_ = v___y_1702_;
goto v___jp_1681_;
}
}
v___jp_1709_:
{
uint64_t v___x_1719_; uint64_t v___x_1720_; uint8_t v___x_1721_; 
v___x_1719_ = 8ULL;
v___x_1720_ = lean_uint64_shift_right(v___y_1713_, v___x_1719_);
v___x_1721_ = lean_uint64_dec_eq(v___x_1720_, v___y_1714_);
if (v___x_1721_ == 0)
{
v___y_1695_ = v___y_1711_;
v___y_1696_ = v___y_1710_;
v___y_1697_ = v___y_1713_;
v___y_1698_ = v___y_1712_;
v___y_1699_ = v___y_1714_;
v___y_1700_ = v___y_1715_;
v___y_1701_ = v___y_1716_;
v___y_1702_ = v___y_1718_;
v___y_1703_ = v___y_1717_;
v___y_1704_ = v___x_1719_;
v___y_1705_ = v___x_1720_;
goto v___jp_1694_;
}
else
{
v___y_1695_ = v___y_1711_;
v___y_1696_ = v___y_1710_;
v___y_1697_ = v___y_1713_;
v___y_1698_ = v___y_1712_;
v___y_1699_ = v___y_1714_;
v___y_1700_ = v___y_1715_;
v___y_1701_ = v___y_1716_;
v___y_1702_ = v___y_1718_;
v___y_1703_ = v___y_1717_;
v___y_1704_ = v___x_1719_;
v___y_1705_ = v___y_1713_;
goto v___jp_1694_;
}
}
v___jp_1722_:
{
uint64_t v___x_1734_; uint8_t v___x_1735_; 
v___x_1734_ = lean_uint64_shift_right(v___y_1732_, v___y_1729_);
v___x_1735_ = lean_uint64_dec_eq(v___x_1734_, v___y_1726_);
if (v___x_1735_ == 0)
{
uint64_t v___x_1736_; 
v___x_1736_ = lean_uint64_add(v___y_1728_, v___y_1729_);
v___y_1710_ = v___y_1724_;
v___y_1711_ = v___y_1723_;
v___y_1712_ = v___y_1725_;
v___y_1713_ = v___y_1733_;
v___y_1714_ = v___y_1726_;
v___y_1715_ = v___y_1727_;
v___y_1716_ = v___y_1730_;
v___y_1717_ = v___y_1731_;
v___y_1718_ = v___x_1736_;
goto v___jp_1709_;
}
else
{
v___y_1710_ = v___y_1724_;
v___y_1711_ = v___y_1723_;
v___y_1712_ = v___y_1725_;
v___y_1713_ = v___y_1733_;
v___y_1714_ = v___y_1726_;
v___y_1715_ = v___y_1727_;
v___y_1716_ = v___y_1730_;
v___y_1717_ = v___y_1731_;
v___y_1718_ = v___y_1728_;
goto v___jp_1709_;
}
}
v___jp_1737_:
{
uint64_t v___x_1747_; uint64_t v___x_1748_; uint8_t v___x_1749_; 
v___x_1747_ = 16ULL;
v___x_1748_ = lean_uint64_shift_right(v___y_1745_, v___x_1747_);
v___x_1749_ = lean_uint64_dec_eq(v___x_1748_, v___y_1741_);
if (v___x_1749_ == 0)
{
v___y_1723_ = v___y_1739_;
v___y_1724_ = v___y_1738_;
v___y_1725_ = v___y_1740_;
v___y_1726_ = v___y_1741_;
v___y_1727_ = v___y_1742_;
v___y_1728_ = v___y_1746_;
v___y_1729_ = v___x_1747_;
v___y_1730_ = v___y_1743_;
v___y_1731_ = v___y_1744_;
v___y_1732_ = v___y_1745_;
v___y_1733_ = v___x_1748_;
goto v___jp_1722_;
}
else
{
v___y_1723_ = v___y_1739_;
v___y_1724_ = v___y_1738_;
v___y_1725_ = v___y_1740_;
v___y_1726_ = v___y_1741_;
v___y_1727_ = v___y_1742_;
v___y_1728_ = v___y_1746_;
v___y_1729_ = v___x_1747_;
v___y_1730_ = v___y_1743_;
v___y_1731_ = v___y_1744_;
v___y_1732_ = v___y_1745_;
v___y_1733_ = v___y_1745_;
goto v___jp_1722_;
}
}
v___jp_1750_:
{
uint64_t v___x_1760_; uint64_t v___x_1761_; uint8_t v___x_1762_; 
v___x_1760_ = lean_unbox_uint64(v___y_1752_);
v___x_1761_ = lean_uint64_shift_right(v___x_1760_, v___y_1754_);
v___x_1762_ = lean_uint64_dec_eq(v___x_1761_, v___y_1755_);
if (v___x_1762_ == 0)
{
v___y_1738_ = v___y_1752_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___y_1755_;
v___y_1742_ = v___y_1756_;
v___y_1743_ = v___y_1757_;
v___y_1744_ = v___y_1758_;
v___y_1745_ = v___y_1759_;
v___y_1746_ = v___y_1754_;
goto v___jp_1737_;
}
else
{
v___y_1738_ = v___y_1752_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___y_1755_;
v___y_1742_ = v___y_1756_;
v___y_1743_ = v___y_1757_;
v___y_1744_ = v___y_1758_;
v___y_1745_ = v___y_1759_;
v___y_1746_ = v___y_1755_;
goto v___jp_1737_;
}
}
v___jp_1763_:
{
uint64_t v___x_1769_; uint64_t v___x_1770_; uint8_t v___x_1771_; 
v___x_1769_ = 0ULL;
v___x_1770_ = lean_unbox_uint64(v_snd_1768_);
v___x_1771_ = lean_uint64_dec_eq(v___x_1770_, v___x_1769_);
if (v___x_1771_ == 0)
{
uint64_t v___x_1772_; uint64_t v___x_1773_; uint64_t v___x_1774_; uint64_t v___x_1775_; uint64_t v___x_1776_; uint8_t v___x_1777_; 
v___x_1772_ = 149ULL;
v___x_1773_ = lean_uint64_add(v___y_1765_, v___x_1772_);
v___x_1774_ = 32ULL;
v___x_1775_ = lean_unbox_uint64(v_snd_1768_);
v___x_1776_ = lean_uint64_shift_right(v___x_1775_, v___x_1774_);
v___x_1777_ = lean_uint64_dec_eq(v___x_1776_, v___x_1769_);
if (v___x_1777_ == 0)
{
v___y_1751_ = v___x_1772_;
v___y_1752_ = v_snd_1768_;
v___y_1753_ = v___y_1764_;
v___y_1754_ = v___x_1774_;
v___y_1755_ = v___x_1769_;
v___y_1756_ = v_fst_1767_;
v___y_1757_ = v___y_1766_;
v___y_1758_ = v___x_1773_;
v___y_1759_ = v___x_1776_;
goto v___jp_1750_;
}
else
{
uint64_t v___x_1778_; 
v___x_1778_ = lean_unbox_uint64(v_snd_1768_);
v___y_1751_ = v___x_1772_;
v___y_1752_ = v_snd_1768_;
v___y_1753_ = v___y_1764_;
v___y_1754_ = v___x_1774_;
v___y_1755_ = v___x_1769_;
v___y_1756_ = v_fst_1767_;
v___y_1757_ = v___y_1766_;
v___y_1758_ = v___x_1773_;
v___y_1759_ = v___x_1778_;
goto v___jp_1750_;
}
}
else
{
uint8_t v___x_1779_; 
lean_dec(v_snd_1768_);
v___x_1779_ = lean_unbox(v_fst_1767_);
lean_dec(v_fst_1767_);
if (v___x_1779_ == 0)
{
uint32_t v___x_1780_; 
v___x_1780_ = 0;
return v___x_1780_;
}
else
{
uint32_t v___x_1781_; 
v___x_1781_ = 2147483648;
return v___x_1781_;
}
}
}
v___jp_1782_:
{
uint8_t v___x_1791_; 
v___x_1791_ = lean_uint64_dec_eq(v___y_1784_, v___y_1786_);
if (v___x_1791_ == 0)
{
uint8_t v___x_1792_; 
v___x_1792_ = lean_uint64_dec_lt(v___y_1784_, v___y_1786_);
if (v___x_1792_ == 0)
{
uint64_t v___x_1793_; lean_object* v___x_1794_; lean_object* v___x_1795_; 
v___x_1793_ = lean_uint64_sub(v___y_1784_, v___y_1786_);
v___x_1794_ = lean_box(v___y_1788_);
v___x_1795_ = lean_box_uint64(v___x_1793_);
v___y_1764_ = v___y_1783_;
v___y_1765_ = v___y_1785_;
v___y_1766_ = v___y_1787_;
v_fst_1767_ = v___x_1794_;
v_snd_1768_ = v___x_1795_;
goto v___jp_1763_;
}
else
{
uint64_t v___x_1796_; lean_object* v___x_1797_; lean_object* v___x_1798_; 
v___x_1796_ = lean_uint64_sub(v___y_1786_, v___y_1784_);
v___x_1797_ = lean_box(v___y_1789_);
v___x_1798_ = lean_box_uint64(v___x_1796_);
v___y_1764_ = v___y_1783_;
v___y_1765_ = v___y_1785_;
v___y_1766_ = v___y_1787_;
v_fst_1767_ = v___x_1797_;
v_snd_1768_ = v___x_1798_;
goto v___jp_1763_;
}
}
else
{
lean_object* v___x_1799_; lean_object* v___x_1800_; 
v___x_1799_ = lean_box(v___y_1790_);
v___x_1800_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1764_ = v___y_1783_;
v___y_1765_ = v___y_1785_;
v___y_1766_ = v___y_1787_;
v_fst_1767_ = v___x_1799_;
v_snd_1768_ = v___x_1800_;
goto v___jp_1763_;
}
}
v___jp_1801_:
{
if (v___y_1809_ == 0)
{
v___y_1783_ = v___y_1803_;
v___y_1784_ = v___y_1802_;
v___y_1785_ = v___y_1804_;
v___y_1786_ = v___y_1805_;
v___y_1787_ = v___y_1806_;
v___y_1788_ = v___y_1807_;
v___y_1789_ = v___y_1808_;
v___y_1790_ = v___y_1809_;
goto v___jp_1782_;
}
else
{
uint64_t v___x_1810_; lean_object* v___x_1811_; lean_object* v___x_1812_; 
v___x_1810_ = lean_uint64_add(v___y_1802_, v___y_1805_);
v___x_1811_ = lean_box(v___y_1807_);
v___x_1812_ = lean_box_uint64(v___x_1810_);
v___y_1764_ = v___y_1803_;
v___y_1765_ = v___y_1804_;
v___y_1766_ = v___y_1806_;
v_fst_1767_ = v___x_1811_;
v_snd_1768_ = v___x_1812_;
goto v___jp_1763_;
}
}
v___jp_1813_:
{
uint8_t v___x_1822_; 
v___x_1822_ = lean_uint64_dec_eq(v___y_1817_, v___y_1816_);
if (v___x_1822_ == 0)
{
uint8_t v___x_1823_; 
v___x_1823_ = lean_uint64_dec_lt(v___y_1817_, v___y_1816_);
if (v___x_1823_ == 0)
{
uint64_t v___x_1824_; lean_object* v___x_1825_; lean_object* v___x_1826_; 
v___x_1824_ = lean_uint64_sub(v___y_1817_, v___y_1816_);
v___x_1825_ = lean_box(v___y_1819_);
v___x_1826_ = lean_box_uint64(v___x_1824_);
v___y_1451_ = v___y_1814_;
v___y_1452_ = v___y_1815_;
v___y_1453_ = v___y_1818_;
v_fst_1454_ = v___x_1825_;
v_snd_1455_ = v___x_1826_;
goto v___jp_1450_;
}
else
{
uint64_t v___x_1827_; lean_object* v___x_1828_; lean_object* v___x_1829_; 
v___x_1827_ = lean_uint64_sub(v___y_1816_, v___y_1817_);
v___x_1828_ = lean_box(v___y_1820_);
v___x_1829_ = lean_box_uint64(v___x_1827_);
v___y_1451_ = v___y_1814_;
v___y_1452_ = v___y_1815_;
v___y_1453_ = v___y_1818_;
v_fst_1454_ = v___x_1828_;
v_snd_1455_ = v___x_1829_;
goto v___jp_1450_;
}
}
else
{
lean_object* v___x_1830_; lean_object* v___x_1831_; 
v___x_1830_ = lean_box(v___y_1821_);
v___x_1831_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1451_ = v___y_1814_;
v___y_1452_ = v___y_1815_;
v___y_1453_ = v___y_1818_;
v_fst_1454_ = v___x_1830_;
v_snd_1455_ = v___x_1831_;
goto v___jp_1450_;
}
}
v___jp_1832_:
{
if (v___y_1840_ == 0)
{
v___y_1814_ = v___y_1833_;
v___y_1815_ = v___y_1834_;
v___y_1816_ = v___y_1836_;
v___y_1817_ = v___y_1835_;
v___y_1818_ = v___y_1837_;
v___y_1819_ = v___y_1838_;
v___y_1820_ = v___y_1839_;
v___y_1821_ = v___y_1840_;
goto v___jp_1813_;
}
else
{
uint64_t v___x_1841_; lean_object* v___x_1842_; lean_object* v___x_1843_; 
v___x_1841_ = lean_uint64_add(v___y_1835_, v___y_1836_);
v___x_1842_ = lean_box(v___y_1838_);
v___x_1843_ = lean_box_uint64(v___x_1841_);
v___y_1451_ = v___y_1833_;
v___y_1452_ = v___y_1834_;
v___y_1453_ = v___y_1837_;
v_fst_1454_ = v___x_1842_;
v_snd_1455_ = v___x_1843_;
goto v___jp_1450_;
}
}
v___jp_1844_:
{
uint8_t v___x_1853_; 
v___x_1853_ = lean_uint64_dec_le(v___y_1845_, v___y_1852_);
if (v___x_1853_ == 0)
{
uint64_t v_shift_1854_; uint64_t v___x_1855_; uint8_t v___x_1856_; 
v_shift_1854_ = lean_uint64_sub(v___y_1845_, v___y_1852_);
v___x_1855_ = 39ULL;
v___x_1856_ = lean_uint64_dec_le(v_shift_1854_, v___x_1855_);
if (v___x_1856_ == 0)
{
return v_x_1146_;
}
else
{
uint64_t v___x_1857_; 
v___x_1857_ = lean_uint64_shift_left(v___y_1847_, v_shift_1854_);
if (v___y_1850_ == 0)
{
if (v___y_1851_ == 0)
{
v___y_1802_ = v___x_1857_;
v___y_1803_ = v___y_1846_;
v___y_1804_ = v___y_1852_;
v___y_1805_ = v___y_1848_;
v___y_1806_ = v___y_1849_;
v___y_1807_ = v___y_1850_;
v___y_1808_ = v___y_1851_;
v___y_1809_ = v___x_1856_;
goto v___jp_1801_;
}
else
{
v___y_1783_ = v___y_1846_;
v___y_1784_ = v___x_1857_;
v___y_1785_ = v___y_1852_;
v___y_1786_ = v___y_1848_;
v___y_1787_ = v___y_1849_;
v___y_1788_ = v___y_1850_;
v___y_1789_ = v___y_1851_;
v___y_1790_ = v___y_1850_;
goto v___jp_1782_;
}
}
else
{
v___y_1802_ = v___x_1857_;
v___y_1803_ = v___y_1846_;
v___y_1804_ = v___y_1852_;
v___y_1805_ = v___y_1848_;
v___y_1806_ = v___y_1849_;
v___y_1807_ = v___y_1850_;
v___y_1808_ = v___y_1851_;
v___y_1809_ = v___y_1851_;
goto v___jp_1801_;
}
}
}
else
{
uint64_t v_shift_1858_; uint64_t v___x_1859_; uint8_t v___x_1860_; 
v_shift_1858_ = lean_uint64_sub(v___y_1852_, v___y_1845_);
v___x_1859_ = 39ULL;
v___x_1860_ = lean_uint64_dec_le(v_shift_1858_, v___x_1859_);
if (v___x_1860_ == 0)
{
return v_y_1147_;
}
else
{
uint64_t v___x_1861_; 
v___x_1861_ = lean_uint64_shift_left(v___y_1848_, v_shift_1858_);
if (v___y_1850_ == 0)
{
if (v___y_1851_ == 0)
{
v___y_1833_ = v___y_1845_;
v___y_1834_ = v___y_1846_;
v___y_1835_ = v___y_1847_;
v___y_1836_ = v___x_1861_;
v___y_1837_ = v___y_1849_;
v___y_1838_ = v___y_1850_;
v___y_1839_ = v___y_1851_;
v___y_1840_ = v___x_1860_;
goto v___jp_1832_;
}
else
{
v___y_1814_ = v___y_1845_;
v___y_1815_ = v___y_1846_;
v___y_1816_ = v___x_1861_;
v___y_1817_ = v___y_1847_;
v___y_1818_ = v___y_1849_;
v___y_1819_ = v___y_1850_;
v___y_1820_ = v___y_1851_;
v___y_1821_ = v___y_1850_;
goto v___jp_1813_;
}
}
else
{
v___y_1833_ = v___y_1845_;
v___y_1834_ = v___y_1846_;
v___y_1835_ = v___y_1847_;
v___y_1836_ = v___x_1861_;
v___y_1837_ = v___y_1849_;
v___y_1838_ = v___y_1850_;
v___y_1839_ = v___y_1851_;
v___y_1840_ = v___y_1851_;
goto v___jp_1832_;
}
}
}
}
v___jp_1862_:
{
uint64_t v___x_1871_; uint64_t v___x_1872_; uint8_t v___x_1873_; 
v___x_1871_ = lean_uint32_to_uint64(v___y_1864_);
v___x_1872_ = 0ULL;
v___x_1873_ = lean_uint64_dec_eq(v___x_1871_, v___x_1872_);
if (v___x_1873_ == 0)
{
uint64_t v___x_1874_; uint64_t v___x_1875_; 
v___x_1874_ = 1ULL;
v___x_1875_ = lean_uint64_sub(v___x_1871_, v___x_1874_);
v___y_1845_ = v___y_1870_;
v___y_1846_ = v___y_1863_;
v___y_1847_ = v___y_1865_;
v___y_1848_ = v___y_1866_;
v___y_1849_ = v___y_1867_;
v___y_1850_ = v___y_1868_;
v___y_1851_ = v___y_1869_;
v___y_1852_ = v___x_1875_;
goto v___jp_1844_;
}
else
{
v___y_1845_ = v___y_1870_;
v___y_1846_ = v___y_1863_;
v___y_1847_ = v___y_1865_;
v___y_1848_ = v___y_1866_;
v___y_1849_ = v___y_1867_;
v___y_1850_ = v___y_1868_;
v___y_1851_ = v___y_1869_;
v___y_1852_ = v___x_1872_;
goto v___jp_1844_;
}
}
v___jp_1876_:
{
uint64_t v___x_1885_; uint64_t v___x_1886_; uint8_t v___x_1887_; 
v___x_1885_ = lean_uint32_to_uint64(v___y_1882_);
v___x_1886_ = 0ULL;
v___x_1887_ = lean_uint64_dec_eq(v___x_1885_, v___x_1886_);
if (v___x_1887_ == 0)
{
uint64_t v___x_1888_; uint64_t v___x_1889_; 
v___x_1888_ = 1ULL;
v___x_1889_ = lean_uint64_sub(v___x_1885_, v___x_1888_);
v___y_1863_ = v___y_1877_;
v___y_1864_ = v___y_1879_;
v___y_1865_ = v___y_1878_;
v___y_1866_ = v___y_1884_;
v___y_1867_ = v___y_1880_;
v___y_1868_ = v___y_1881_;
v___y_1869_ = v___y_1883_;
v___y_1870_ = v___x_1889_;
goto v___jp_1862_;
}
else
{
v___y_1863_ = v___y_1877_;
v___y_1864_ = v___y_1879_;
v___y_1865_ = v___y_1878_;
v___y_1866_ = v___y_1884_;
v___y_1867_ = v___y_1880_;
v___y_1868_ = v___y_1881_;
v___y_1869_ = v___y_1883_;
v___y_1870_ = v___x_1886_;
goto v___jp_1862_;
}
}
v___jp_1890_:
{
uint32_t v___x_1898_; uint32_t v___x_1899_; uint32_t v___x_1900_; uint8_t v___x_1901_; 
v___x_1898_ = 8388607;
v___x_1899_ = lean_uint32_land(v_y_1147_, v___x_1898_);
v___x_1900_ = 0;
v___x_1901_ = lean_uint32_dec_eq(v___y_1892_, v___x_1900_);
if (v___x_1901_ == 0)
{
uint64_t v___x_1902_; uint64_t v___x_1903_; uint64_t v___x_1904_; 
v___x_1902_ = lean_uint32_to_uint64(v___x_1899_);
v___x_1903_ = 8388608ULL;
v___x_1904_ = lean_uint64_lor(v___x_1902_, v___x_1903_);
v___y_1877_ = v___y_1891_;
v___y_1878_ = v___y_1897_;
v___y_1879_ = v___y_1892_;
v___y_1880_ = v___y_1893_;
v___y_1881_ = v___y_1894_;
v___y_1882_ = v___y_1896_;
v___y_1883_ = v___y_1895_;
v___y_1884_ = v___x_1904_;
goto v___jp_1876_;
}
else
{
uint64_t v___x_1905_; 
v___x_1905_ = lean_uint32_to_uint64(v___x_1899_);
v___y_1877_ = v___y_1891_;
v___y_1878_ = v___y_1897_;
v___y_1879_ = v___y_1892_;
v___y_1880_ = v___y_1893_;
v___y_1881_ = v___y_1894_;
v___y_1882_ = v___y_1896_;
v___y_1883_ = v___y_1895_;
v___y_1884_ = v___x_1905_;
goto v___jp_1876_;
}
}
v___jp_1906_:
{
uint32_t v___x_1913_; uint32_t v___x_1914_; uint32_t v___x_1915_; uint8_t v___x_1916_; 
v___x_1913_ = 8388607;
v___x_1914_ = lean_uint32_land(v_x_1146_, v___x_1913_);
v___x_1915_ = 0;
v___x_1916_ = lean_uint32_dec_eq(v___y_1911_, v___x_1915_);
if (v___x_1916_ == 0)
{
uint64_t v___x_1917_; uint64_t v___x_1918_; uint64_t v___x_1919_; 
v___x_1917_ = lean_uint32_to_uint64(v___x_1914_);
v___x_1918_ = 8388608ULL;
v___x_1919_ = lean_uint64_lor(v___x_1917_, v___x_1918_);
v___y_1891_ = v___y_1907_;
v___y_1892_ = v___y_1908_;
v___y_1893_ = v___y_1909_;
v___y_1894_ = v___y_1910_;
v___y_1895_ = v___y_1912_;
v___y_1896_ = v___y_1911_;
v___y_1897_ = v___x_1919_;
goto v___jp_1890_;
}
else
{
uint64_t v___x_1920_; 
v___x_1920_ = lean_uint32_to_uint64(v___x_1914_);
v___y_1891_ = v___y_1907_;
v___y_1892_ = v___y_1908_;
v___y_1893_ = v___y_1909_;
v___y_1894_ = v___y_1910_;
v___y_1895_ = v___y_1912_;
v___y_1896_ = v___y_1911_;
v___y_1897_ = v___x_1920_;
goto v___jp_1890_;
}
}
v___jp_1921_:
{
uint32_t v___x_1928_; uint32_t v___x_1929_; uint32_t v___x_1930_; uint8_t v___x_1931_; 
v___x_1928_ = 2147483648;
v___x_1929_ = lean_uint32_land(v_y_1147_, v___x_1928_);
v___x_1930_ = 0;
v___x_1931_ = lean_uint32_dec_eq(v___x_1929_, v___x_1930_);
if (v___x_1931_ == 0)
{
uint8_t v___x_1932_; 
v___x_1932_ = 1;
v___y_1907_ = v___y_1923_;
v___y_1908_ = v___y_1924_;
v___y_1909_ = v___y_1925_;
v___y_1910_ = v___y_1927_;
v___y_1911_ = v___y_1926_;
v___y_1912_ = v___x_1932_;
goto v___jp_1906_;
}
else
{
v___y_1907_ = v___y_1923_;
v___y_1908_ = v___y_1924_;
v___y_1909_ = v___y_1925_;
v___y_1910_ = v___y_1927_;
v___y_1911_ = v___y_1926_;
v___y_1912_ = v___y_1922_;
goto v___jp_1906_;
}
}
v___jp_1933_:
{
if (v___y_1934_ == 0)
{
uint32_t v___x_1935_; uint32_t v___x_1936_; uint32_t v___x_1937_; uint32_t v_xExponent_1938_; uint32_t v___x_1939_; uint32_t v_yExponent_1940_; uint32_t v___x_1941_; uint32_t v___x_1942_; uint32_t v___x_1943_; uint8_t v___x_1944_; 
v___x_1935_ = 23;
v___x_1936_ = lean_uint32_shift_right(v_x_1146_, v___x_1935_);
v___x_1937_ = 255;
v_xExponent_1938_ = lean_uint32_land(v___x_1936_, v___x_1937_);
v___x_1939_ = lean_uint32_shift_right(v_y_1147_, v___x_1935_);
v_yExponent_1940_ = lean_uint32_land(v___x_1939_, v___x_1937_);
v___x_1941_ = 2147483648;
v___x_1942_ = lean_uint32_land(v_x_1146_, v___x_1941_);
v___x_1943_ = 0;
v___x_1944_ = lean_uint32_dec_eq(v___x_1942_, v___x_1943_);
if (v___x_1944_ == 0)
{
uint8_t v___x_1945_; 
v___x_1945_ = 1;
v___y_1922_ = v___y_1934_;
v___y_1923_ = v___x_1935_;
v___y_1924_ = v_yExponent_1940_;
v___y_1925_ = v___x_1937_;
v___y_1926_ = v_xExponent_1938_;
v___y_1927_ = v___x_1945_;
goto v___jp_1921_;
}
else
{
v___y_1922_ = v___y_1934_;
v___y_1923_ = v___x_1935_;
v___y_1924_ = v_yExponent_1940_;
v___y_1925_ = v___x_1937_;
v___y_1926_ = v_xExponent_1938_;
v___y_1927_ = v___y_1934_;
goto v___jp_1921_;
}
}
else
{
lean_object* v___x_1946_; lean_object* v___x_1947_; lean_object* v___x_1948_; uint32_t v___x_1949_; 
v___x_1946_ = lean_uint32_to_nat(v_x_1146_);
v___x_1947_ = lean_uint32_to_nat(v_y_1147_);
v___x_1948_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1946_, v___x_1947_);
v___x_1949_ = lean_uint32_of_nat(v___x_1948_);
lean_dec(v___x_1948_);
return v___x_1949_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_add___boxed(lean_object* v_x_1958_, lean_object* v_y_1959_){
_start:
{
uint32_t v_x_boxed_1960_; uint32_t v_y_boxed_1961_; uint32_t v_res_1962_; lean_object* v_r_1963_; 
v_x_boxed_1960_ = lean_unbox_uint32(v_x_1958_);
lean_dec(v_x_1958_);
v_y_boxed_1961_ = lean_unbox_uint32(v_y_1959_);
lean_dec(v_y_1959_);
v_res_1962_ = lp_competition_Submission_TunedAdd_add(v_x_boxed_1960_, v_y_boxed_1961_);
v_r_1963_ = lean_box_uint32(v_res_1962_);
return v_r_1963_;
}
}
static uint8_t _init_lp_competition_Submission_TunedAdd_Plan(void){
_start:
{
uint8_t v___x_1970_; 
v___x_1970_ = 2;
return v___x_1970_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec(uint32_t v_z_1971_){
_start:
{
lean_object* v___x_1972_; 
v___x_1972_ = lean_uint32_to_nat(v_z_1971_);
return v___x_1972_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec___boxed(lean_object* v_z_1973_){
_start:
{
uint32_t v_z_boxed_1974_; lean_object* v_res_1975_; 
v_z_boxed_1974_ = lean_unbox_uint32(v_z_1973_);
lean_dec(v_z_1973_);
v_res_1975_ = lp_competition_Submission_TunedAdd_dec(v_z_boxed_1974_);
return v_res_1975_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sx(uint64_t v_k_1976_, uint64_t v_x_1977_){
_start:
{
uint64_t v___x_1978_; uint64_t v___x_1979_; uint8_t v___x_1980_; 
v___x_1978_ = lean_uint64_shift_right(v_x_1977_, v_k_1976_);
v___x_1979_ = 0ULL;
v___x_1980_ = lean_uint64_dec_eq(v___x_1978_, v___x_1979_);
if (v___x_1980_ == 0)
{
return v___x_1978_;
}
else
{
return v_x_1977_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sx___boxed(lean_object* v_k_1981_, lean_object* v_x_1982_){
_start:
{
uint64_t v_k_boxed_1983_; uint64_t v_x_boxed_1984_; uint64_t v_res_1985_; lean_object* v_r_1986_; 
v_k_boxed_1983_ = lean_unbox_uint64(v_k_1981_);
lean_dec_ref(v_k_1981_);
v_x_boxed_1984_ = lean_unbox_uint64(v_x_1982_);
lean_dec_ref(v_x_1982_);
v_res_1985_ = lp_competition_Submission_FastMul_sx(v_k_boxed_1983_, v_x_boxed_1984_);
v_r_1986_ = lean_box_uint64(v_res_1985_);
return v_r_1986_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sr(uint64_t v_k_1987_, uint64_t v_x_1988_, uint64_t v_r_1989_){
_start:
{
uint64_t v___x_1990_; uint64_t v___x_1991_; uint8_t v___x_1992_; 
v___x_1990_ = lean_uint64_shift_right(v_x_1988_, v_k_1987_);
v___x_1991_ = 0ULL;
v___x_1992_ = lean_uint64_dec_eq(v___x_1990_, v___x_1991_);
if (v___x_1992_ == 0)
{
uint64_t v___x_1993_; 
v___x_1993_ = lean_uint64_add(v_r_1989_, v_k_1987_);
return v___x_1993_;
}
else
{
return v_r_1989_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sr___boxed(lean_object* v_k_1994_, lean_object* v_x_1995_, lean_object* v_r_1996_){
_start:
{
uint64_t v_k_boxed_1997_; uint64_t v_x_boxed_1998_; uint64_t v_r_boxed_1999_; uint64_t v_res_2000_; lean_object* v_r_2001_; 
v_k_boxed_1997_ = lean_unbox_uint64(v_k_1994_);
lean_dec_ref(v_k_1994_);
v_x_boxed_1998_ = lean_unbox_uint64(v_x_1995_);
lean_dec_ref(v_x_1995_);
v_r_boxed_1999_ = lean_unbox_uint64(v_r_1996_);
lean_dec_ref(v_r_1996_);
v_res_2000_ = lp_competition_Submission_FastMul_sr(v_k_boxed_1997_, v_x_boxed_1998_, v_r_boxed_1999_);
v_r_2001_ = lean_box_uint64(v_res_2000_);
return v_r_2001_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_fastLog2(uint64_t v_x0_2002_){
_start:
{
uint64_t v___y_2004_; uint64_t v___y_2005_; uint64_t v___y_2012_; uint64_t v___y_2013_; uint64_t v___y_2014_; uint64_t v___y_2015_; uint64_t v___y_2021_; uint64_t v___y_2022_; uint64_t v___y_2028_; uint64_t v___y_2029_; uint64_t v___y_2030_; uint64_t v___y_2031_; uint64_t v___y_2037_; uint64_t v___y_2038_; uint64_t v___y_2044_; uint64_t v___y_2045_; uint64_t v___y_2046_; uint64_t v___y_2047_; uint64_t v___y_2053_; uint64_t v___y_2054_; uint64_t v___y_2060_; uint64_t v___y_2061_; uint64_t v___y_2062_; uint64_t v___y_2063_; uint64_t v___y_2069_; uint64_t v___y_2070_; uint64_t v___x_2075_; uint64_t v___y_2077_; uint64_t v___x_2081_; uint64_t v___x_2082_; uint8_t v___x_2083_; 
v___x_2075_ = 32ULL;
v___x_2081_ = lean_uint64_shift_right(v_x0_2002_, v___x_2075_);
v___x_2082_ = 0ULL;
v___x_2083_ = lean_uint64_dec_eq(v___x_2081_, v___x_2082_);
if (v___x_2083_ == 0)
{
v___y_2077_ = v___x_2081_;
goto v___jp_2076_;
}
else
{
v___y_2077_ = v_x0_2002_;
goto v___jp_2076_;
}
v___jp_2003_:
{
uint64_t v___x_2006_; uint64_t v___x_2007_; uint64_t v___x_2008_; uint8_t v___x_2009_; 
v___x_2006_ = 1ULL;
v___x_2007_ = lean_uint64_shift_right(v___y_2004_, v___x_2006_);
v___x_2008_ = 0ULL;
v___x_2009_ = lean_uint64_dec_eq(v___x_2007_, v___x_2008_);
if (v___x_2009_ == 0)
{
uint64_t v___x_2010_; 
v___x_2010_ = lean_uint64_add(v___y_2005_, v___x_2006_);
return v___x_2010_;
}
else
{
return v___y_2005_;
}
}
v___jp_2011_:
{
uint64_t v___x_2016_; uint64_t v___x_2017_; uint8_t v___x_2018_; 
v___x_2016_ = lean_uint64_shift_right(v___y_2012_, v___y_2013_);
v___x_2017_ = 0ULL;
v___x_2018_ = lean_uint64_dec_eq(v___x_2016_, v___x_2017_);
if (v___x_2018_ == 0)
{
uint64_t v___x_2019_; 
v___x_2019_ = lean_uint64_add(v___y_2014_, v___y_2013_);
v___y_2004_ = v___y_2015_;
v___y_2005_ = v___x_2019_;
goto v___jp_2003_;
}
else
{
v___y_2004_ = v___y_2015_;
v___y_2005_ = v___y_2014_;
goto v___jp_2003_;
}
}
v___jp_2020_:
{
uint64_t v___x_2023_; uint64_t v___x_2024_; uint64_t v___x_2025_; uint8_t v___x_2026_; 
v___x_2023_ = 2ULL;
v___x_2024_ = lean_uint64_shift_right(v___y_2021_, v___x_2023_);
v___x_2025_ = 0ULL;
v___x_2026_ = lean_uint64_dec_eq(v___x_2024_, v___x_2025_);
if (v___x_2026_ == 0)
{
v___y_2012_ = v___y_2021_;
v___y_2013_ = v___x_2023_;
v___y_2014_ = v___y_2022_;
v___y_2015_ = v___x_2024_;
goto v___jp_2011_;
}
else
{
v___y_2012_ = v___y_2021_;
v___y_2013_ = v___x_2023_;
v___y_2014_ = v___y_2022_;
v___y_2015_ = v___y_2021_;
goto v___jp_2011_;
}
}
v___jp_2027_:
{
uint64_t v___x_2032_; uint64_t v___x_2033_; uint8_t v___x_2034_; 
v___x_2032_ = lean_uint64_shift_right(v___y_2029_, v___y_2028_);
v___x_2033_ = 0ULL;
v___x_2034_ = lean_uint64_dec_eq(v___x_2032_, v___x_2033_);
if (v___x_2034_ == 0)
{
uint64_t v___x_2035_; 
v___x_2035_ = lean_uint64_add(v___y_2030_, v___y_2028_);
v___y_2021_ = v___y_2031_;
v___y_2022_ = v___x_2035_;
goto v___jp_2020_;
}
else
{
v___y_2021_ = v___y_2031_;
v___y_2022_ = v___y_2030_;
goto v___jp_2020_;
}
}
v___jp_2036_:
{
uint64_t v___x_2039_; uint64_t v___x_2040_; uint64_t v___x_2041_; uint8_t v___x_2042_; 
v___x_2039_ = 4ULL;
v___x_2040_ = lean_uint64_shift_right(v___y_2037_, v___x_2039_);
v___x_2041_ = 0ULL;
v___x_2042_ = lean_uint64_dec_eq(v___x_2040_, v___x_2041_);
if (v___x_2042_ == 0)
{
v___y_2028_ = v___x_2039_;
v___y_2029_ = v___y_2037_;
v___y_2030_ = v___y_2038_;
v___y_2031_ = v___x_2040_;
goto v___jp_2027_;
}
else
{
v___y_2028_ = v___x_2039_;
v___y_2029_ = v___y_2037_;
v___y_2030_ = v___y_2038_;
v___y_2031_ = v___y_2037_;
goto v___jp_2027_;
}
}
v___jp_2043_:
{
uint64_t v___x_2048_; uint64_t v___x_2049_; uint8_t v___x_2050_; 
v___x_2048_ = lean_uint64_shift_right(v___y_2044_, v___y_2046_);
v___x_2049_ = 0ULL;
v___x_2050_ = lean_uint64_dec_eq(v___x_2048_, v___x_2049_);
if (v___x_2050_ == 0)
{
uint64_t v___x_2051_; 
v___x_2051_ = lean_uint64_add(v___y_2045_, v___y_2046_);
v___y_2037_ = v___y_2047_;
v___y_2038_ = v___x_2051_;
goto v___jp_2036_;
}
else
{
v___y_2037_ = v___y_2047_;
v___y_2038_ = v___y_2045_;
goto v___jp_2036_;
}
}
v___jp_2052_:
{
uint64_t v___x_2055_; uint64_t v___x_2056_; uint64_t v___x_2057_; uint8_t v___x_2058_; 
v___x_2055_ = 8ULL;
v___x_2056_ = lean_uint64_shift_right(v___y_2053_, v___x_2055_);
v___x_2057_ = 0ULL;
v___x_2058_ = lean_uint64_dec_eq(v___x_2056_, v___x_2057_);
if (v___x_2058_ == 0)
{
v___y_2044_ = v___y_2053_;
v___y_2045_ = v___y_2054_;
v___y_2046_ = v___x_2055_;
v___y_2047_ = v___x_2056_;
goto v___jp_2043_;
}
else
{
v___y_2044_ = v___y_2053_;
v___y_2045_ = v___y_2054_;
v___y_2046_ = v___x_2055_;
v___y_2047_ = v___y_2053_;
goto v___jp_2043_;
}
}
v___jp_2059_:
{
uint64_t v___x_2064_; uint64_t v___x_2065_; uint8_t v___x_2066_; 
v___x_2064_ = lean_uint64_shift_right(v___y_2060_, v___y_2061_);
v___x_2065_ = 0ULL;
v___x_2066_ = lean_uint64_dec_eq(v___x_2064_, v___x_2065_);
if (v___x_2066_ == 0)
{
uint64_t v___x_2067_; 
v___x_2067_ = lean_uint64_add(v___y_2062_, v___y_2061_);
v___y_2053_ = v___y_2063_;
v___y_2054_ = v___x_2067_;
goto v___jp_2052_;
}
else
{
v___y_2053_ = v___y_2063_;
v___y_2054_ = v___y_2062_;
goto v___jp_2052_;
}
}
v___jp_2068_:
{
uint64_t v___x_2071_; uint64_t v___x_2072_; uint64_t v___x_2073_; uint8_t v___x_2074_; 
v___x_2071_ = 16ULL;
v___x_2072_ = lean_uint64_shift_right(v___y_2069_, v___x_2071_);
v___x_2073_ = 0ULL;
v___x_2074_ = lean_uint64_dec_eq(v___x_2072_, v___x_2073_);
if (v___x_2074_ == 0)
{
v___y_2060_ = v___y_2069_;
v___y_2061_ = v___x_2071_;
v___y_2062_ = v___y_2070_;
v___y_2063_ = v___x_2072_;
goto v___jp_2059_;
}
else
{
v___y_2060_ = v___y_2069_;
v___y_2061_ = v___x_2071_;
v___y_2062_ = v___y_2070_;
v___y_2063_ = v___y_2069_;
goto v___jp_2059_;
}
}
v___jp_2076_:
{
uint64_t v___x_2078_; uint64_t v___x_2079_; uint8_t v___x_2080_; 
v___x_2078_ = lean_uint64_shift_right(v_x0_2002_, v___x_2075_);
v___x_2079_ = 0ULL;
v___x_2080_ = lean_uint64_dec_eq(v___x_2078_, v___x_2079_);
if (v___x_2080_ == 0)
{
v___y_2069_ = v___y_2077_;
v___y_2070_ = v___x_2075_;
goto v___jp_2068_;
}
else
{
v___y_2069_ = v___y_2077_;
v___y_2070_ = v___x_2079_;
goto v___jp_2068_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fastLog2___boxed(lean_object* v_x0_2084_){
_start:
{
uint64_t v_x0_boxed_2085_; uint64_t v_res_2086_; lean_object* v_r_2087_; 
v_x0_boxed_2085_ = lean_unbox_uint64(v_x0_2084_);
lean_dec_ref(v_x0_2084_);
v_res_2086_ = lp_competition_Submission_FastMul_fastLog2(v_x0_boxed_2085_);
v_r_2087_ = lean_box_uint64(v_res_2086_);
return v_r_2087_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rse(uint64_t v_value_2088_, uint64_t v_shift_2089_){
_start:
{
uint64_t v_quotient_2090_; uint64_t v___x_2091_; uint64_t v___x_2092_; uint64_t v___x_2093_; uint64_t v_remainder_2094_; uint64_t v___x_2095_; uint64_t v_half_2096_; uint8_t v___x_2097_; 
v_quotient_2090_ = lean_uint64_shift_right(v_value_2088_, v_shift_2089_);
v___x_2091_ = 1ULL;
v___x_2092_ = lean_uint64_shift_left(v___x_2091_, v_shift_2089_);
v___x_2093_ = lean_uint64_sub(v___x_2092_, v___x_2091_);
v_remainder_2094_ = lean_uint64_land(v_value_2088_, v___x_2093_);
v___x_2095_ = lean_uint64_sub(v_shift_2089_, v___x_2091_);
v_half_2096_ = lean_uint64_shift_left(v___x_2091_, v___x_2095_);
v___x_2097_ = lean_uint64_dec_lt(v_remainder_2094_, v_half_2096_);
if (v___x_2097_ == 0)
{
uint8_t v___x_2098_; 
v___x_2098_ = lean_uint64_dec_lt(v_half_2096_, v_remainder_2094_);
if (v___x_2098_ == 0)
{
uint64_t v___x_2099_; uint64_t v___x_2100_; uint8_t v___x_2101_; 
v___x_2099_ = lean_uint64_land(v_quotient_2090_, v___x_2091_);
v___x_2100_ = 0ULL;
v___x_2101_ = lean_uint64_dec_eq(v___x_2099_, v___x_2100_);
if (v___x_2101_ == 0)
{
uint64_t v___x_2102_; 
v___x_2102_ = lean_uint64_add(v_quotient_2090_, v___x_2091_);
return v___x_2102_;
}
else
{
return v_quotient_2090_;
}
}
else
{
uint64_t v___x_2103_; 
v___x_2103_ = lean_uint64_add(v_quotient_2090_, v___x_2091_);
return v___x_2103_;
}
}
else
{
return v_quotient_2090_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rse___boxed(lean_object* v_value_2104_, lean_object* v_shift_2105_){
_start:
{
uint64_t v_value_boxed_2106_; uint64_t v_shift_boxed_2107_; uint64_t v_res_2108_; lean_object* v_r_2109_; 
v_value_boxed_2106_ = lean_unbox_uint64(v_value_2104_);
lean_dec_ref(v_value_2104_);
v_shift_boxed_2107_ = lean_unbox_uint64(v_shift_2105_);
lean_dec_ref(v_shift_2105_);
v_res_2108_ = lp_competition_Submission_FastMul_rse(v_value_boxed_2106_, v_shift_boxed_2107_);
v_r_2109_ = lean_box_uint64(v_res_2108_);
return v_r_2109_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rseAny(uint64_t v_value_2110_, uint64_t v_shift_2111_){
_start:
{
uint64_t v___x_2112_; uint8_t v___x_2113_; 
v___x_2112_ = 0ULL;
v___x_2113_ = lean_uint64_dec_eq(v_shift_2111_, v___x_2112_);
if (v___x_2113_ == 0)
{
uint64_t v___x_2114_; uint8_t v___x_2115_; 
v___x_2114_ = 64ULL;
v___x_2115_ = lean_uint64_dec_lt(v_shift_2111_, v___x_2114_);
if (v___x_2115_ == 0)
{
uint8_t v___x_2116_; 
v___x_2116_ = lean_uint64_dec_eq(v_shift_2111_, v___x_2114_);
if (v___x_2116_ == 0)
{
return v___x_2112_;
}
else
{
uint64_t v___x_2117_; uint8_t v___x_2118_; 
v___x_2117_ = 9223372036854775808ULL;
v___x_2118_ = lean_uint64_dec_lt(v___x_2117_, v_value_2110_);
if (v___x_2118_ == 0)
{
return v___x_2112_;
}
else
{
uint64_t v___x_2119_; 
v___x_2119_ = 1ULL;
return v___x_2119_;
}
}
}
else
{
uint64_t v_quotient_2120_; uint64_t v___x_2121_; uint64_t v___x_2122_; uint64_t v___x_2123_; uint64_t v_remainder_2124_; uint64_t v___x_2125_; uint64_t v_half_2126_; uint8_t v___x_2127_; 
v_quotient_2120_ = lean_uint64_shift_right(v_value_2110_, v_shift_2111_);
v___x_2121_ = 1ULL;
v___x_2122_ = lean_uint64_shift_left(v___x_2121_, v_shift_2111_);
v___x_2123_ = lean_uint64_sub(v___x_2122_, v___x_2121_);
v_remainder_2124_ = lean_uint64_land(v_value_2110_, v___x_2123_);
v___x_2125_ = lean_uint64_sub(v_shift_2111_, v___x_2121_);
v_half_2126_ = lean_uint64_shift_left(v___x_2121_, v___x_2125_);
v___x_2127_ = lean_uint64_dec_lt(v_remainder_2124_, v_half_2126_);
if (v___x_2127_ == 0)
{
uint8_t v___x_2128_; 
v___x_2128_ = lean_uint64_dec_lt(v_half_2126_, v_remainder_2124_);
if (v___x_2128_ == 0)
{
uint64_t v___x_2129_; uint8_t v___x_2130_; 
v___x_2129_ = lean_uint64_land(v_quotient_2120_, v___x_2121_);
v___x_2130_ = lean_uint64_dec_eq(v___x_2129_, v___x_2112_);
if (v___x_2130_ == 0)
{
uint64_t v___x_2131_; 
v___x_2131_ = lean_uint64_add(v_quotient_2120_, v___x_2121_);
return v___x_2131_;
}
else
{
return v_quotient_2120_;
}
}
else
{
uint64_t v___x_2132_; 
v___x_2132_ = lean_uint64_add(v_quotient_2120_, v___x_2121_);
return v___x_2132_;
}
}
else
{
return v_quotient_2120_;
}
}
}
else
{
return v_value_2110_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rseAny___boxed(lean_object* v_value_2133_, lean_object* v_shift_2134_){
_start:
{
uint64_t v_value_boxed_2135_; uint64_t v_shift_boxed_2136_; uint64_t v_res_2137_; lean_object* v_r_2138_; 
v_value_boxed_2135_ = lean_unbox_uint64(v_value_2133_);
lean_dec_ref(v_value_2133_);
v_shift_boxed_2136_ = lean_unbox_uint64(v_shift_2134_);
lean_dec_ref(v_shift_2134_);
v_res_2137_ = lp_competition_Submission_FastMul_rseAny(v_value_boxed_2135_, v_shift_boxed_2136_);
v_r_2138_ = lean_box_uint64(v_res_2137_);
return v_r_2138_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mkW(uint8_t v_sign_2139_, uint32_t v_e_2140_, uint32_t v_f_2141_){
_start:
{
uint32_t v___y_2143_; 
if (v_sign_2139_ == 0)
{
uint32_t v___x_2152_; 
v___x_2152_ = 0;
v___y_2143_ = v___x_2152_;
goto v___jp_2142_;
}
else
{
uint32_t v___x_2153_; 
v___x_2153_ = 2147483648;
v___y_2143_ = v___x_2153_;
goto v___jp_2142_;
}
v___jp_2142_:
{
uint32_t v___x_2144_; uint32_t v___x_2145_; uint32_t v___x_2146_; uint32_t v___x_2147_; uint32_t v___x_2148_; uint32_t v___x_2149_; uint32_t v___x_2150_; uint32_t v___x_2151_; 
v___x_2144_ = 255;
v___x_2145_ = lean_uint32_land(v_e_2140_, v___x_2144_);
v___x_2146_ = 23;
v___x_2147_ = lean_uint32_shift_left(v___x_2145_, v___x_2146_);
v___x_2148_ = lean_uint32_lor(v___y_2143_, v___x_2147_);
v___x_2149_ = 8388607;
v___x_2150_ = lean_uint32_land(v_f_2141_, v___x_2149_);
v___x_2151_ = lean_uint32_lor(v___x_2148_, v___x_2150_);
return v___x_2151_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mkW___boxed(lean_object* v_sign_2154_, lean_object* v_e_2155_, lean_object* v_f_2156_){
_start:
{
uint8_t v_sign_boxed_2157_; uint32_t v_e_boxed_2158_; uint32_t v_f_boxed_2159_; uint32_t v_res_2160_; lean_object* v_r_2161_; 
v_sign_boxed_2157_ = lean_unbox(v_sign_2154_);
v_e_boxed_2158_ = lean_unbox_uint32(v_e_2155_);
lean_dec(v_e_2155_);
v_f_boxed_2159_ = lean_unbox_uint32(v_f_2156_);
lean_dec(v_f_2156_);
v_res_2160_ = lp_competition_Submission_FastMul_mkW(v_sign_boxed_2157_, v_e_boxed_2158_, v_f_boxed_2159_);
v_r_2161_ = lean_box_uint32(v_res_2160_);
return v_r_2161_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_fracW(uint64_t v_n_2162_){
_start:
{
uint64_t v___x_2163_; uint8_t v___x_2164_; 
v___x_2163_ = 8388608ULL;
v___x_2164_ = lean_uint64_dec_lt(v_n_2162_, v___x_2163_);
if (v___x_2164_ == 0)
{
uint64_t v___x_2165_; uint32_t v___x_2166_; 
v___x_2165_ = lean_uint64_sub(v_n_2162_, v___x_2163_);
v___x_2166_ = lean_uint64_to_uint32(v___x_2165_);
return v___x_2166_;
}
else
{
uint32_t v___x_2167_; 
v___x_2167_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
return v___x_2167_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fracW___boxed(lean_object* v_n_2168_){
_start:
{
uint64_t v_n_boxed_2169_; uint32_t v_res_2170_; lean_object* v_r_2171_; 
v_n_boxed_2169_ = lean_unbox_uint64(v_n_2168_);
lean_dec_ref(v_n_2168_);
v_res_2170_ = lp_competition_Submission_FastMul_fracW(v_n_boxed_2169_);
v_r_2171_ = lean_box_uint32(v_res_2170_);
return v_r_2171_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_roundP(uint8_t v_sign_2172_, uint64_t v_product_2173_, uint64_t v_scale_2174_){
_start:
{
uint32_t v___y_2176_; uint32_t v___y_2180_; uint32_t v___y_2181_; uint32_t v___y_2186_; uint32_t v___y_2187_; uint32_t v___y_2188_; uint32_t v___y_2198_; uint32_t v___y_2199_; uint64_t v___x_2202_; uint64_t v___y_2204_; uint64_t v___y_2216_; uint64_t v___y_2217_; uint8_t v___y_2227_; uint64_t v___y_2228_; uint64_t v___y_2229_; uint64_t v___y_2236_; uint64_t v___y_2237_; uint64_t v___y_2243_; uint64_t v___y_2298_; uint64_t v___y_2299_; uint64_t v___y_2305_; uint64_t v___y_2306_; uint64_t v___y_2307_; uint64_t v___y_2308_; uint64_t v___y_2313_; uint64_t v___y_2314_; uint64_t v___y_2319_; uint64_t v___y_2320_; uint64_t v___y_2321_; uint64_t v___y_2322_; uint64_t v___y_2327_; uint64_t v___y_2328_; uint64_t v___y_2333_; uint64_t v___y_2334_; uint64_t v___y_2335_; uint64_t v___y_2336_; uint64_t v___y_2341_; uint64_t v___y_2342_; uint64_t v___y_2347_; uint64_t v___y_2348_; uint64_t v___y_2349_; uint64_t v___y_2350_; uint64_t v___y_2355_; uint64_t v___y_2356_; uint8_t v___x_2360_; 
v___x_2202_ = 0ULL;
v___x_2360_ = lean_uint64_dec_eq(v_product_2173_, v___x_2202_);
if (v___x_2360_ == 0)
{
uint64_t v___x_2361_; uint64_t v___y_2363_; uint64_t v___x_2366_; uint8_t v___x_2367_; 
v___x_2361_ = 32ULL;
v___x_2366_ = lean_uint64_shift_right(v_product_2173_, v___x_2361_);
v___x_2367_ = lean_uint64_dec_eq(v___x_2366_, v___x_2202_);
if (v___x_2367_ == 0)
{
v___y_2363_ = v___x_2366_;
goto v___jp_2362_;
}
else
{
v___y_2363_ = v_product_2173_;
goto v___jp_2362_;
}
v___jp_2362_:
{
uint64_t v___x_2364_; uint8_t v___x_2365_; 
v___x_2364_ = lean_uint64_shift_right(v_product_2173_, v___x_2361_);
v___x_2365_ = lean_uint64_dec_eq(v___x_2364_, v___x_2202_);
if (v___x_2365_ == 0)
{
v___y_2355_ = v___y_2363_;
v___y_2356_ = v___x_2361_;
goto v___jp_2354_;
}
else
{
v___y_2355_ = v___y_2363_;
v___y_2356_ = v___x_2202_;
goto v___jp_2354_;
}
}
}
else
{
if (v_sign_2172_ == 0)
{
uint32_t v___x_2368_; 
v___x_2368_ = 0;
return v___x_2368_;
}
else
{
uint32_t v___x_2369_; 
v___x_2369_ = 2147483648;
return v___x_2369_;
}
}
v___jp_2175_:
{
uint32_t v___x_2177_; uint32_t v___x_2178_; 
v___x_2177_ = 8388608;
v___x_2178_ = lean_uint32_lor(v___y_2176_, v___x_2177_);
return v___x_2178_;
}
v___jp_2179_:
{
uint32_t v___x_2182_; uint32_t v___x_2183_; uint32_t v___x_2184_; 
v___x_2182_ = 8388607;
v___x_2183_ = lean_uint32_land(v___y_2180_, v___x_2182_);
v___x_2184_ = lean_uint32_lor(v___y_2181_, v___x_2183_);
return v___x_2184_;
}
v___jp_2185_:
{
uint32_t v___x_2189_; uint32_t v___x_2190_; uint32_t v___x_2191_; uint32_t v___x_2192_; uint32_t v___x_2193_; uint32_t v___x_2194_; uint32_t v___x_2195_; uint32_t v___x_2196_; 
v___x_2189_ = 255;
v___x_2190_ = lean_uint32_land(v___y_2187_, v___x_2189_);
v___x_2191_ = 23;
v___x_2192_ = lean_uint32_shift_left(v___x_2190_, v___x_2191_);
v___x_2193_ = lean_uint32_lor(v___y_2188_, v___x_2192_);
v___x_2194_ = 8388607;
v___x_2195_ = lean_uint32_land(v___y_2186_, v___x_2194_);
v___x_2196_ = lean_uint32_lor(v___x_2193_, v___x_2195_);
return v___x_2196_;
}
v___jp_2197_:
{
if (v_sign_2172_ == 0)
{
uint32_t v___x_2200_; 
v___x_2200_ = 0;
v___y_2186_ = v___y_2199_;
v___y_2187_ = v___y_2198_;
v___y_2188_ = v___x_2200_;
goto v___jp_2185_;
}
else
{
uint32_t v___x_2201_; 
v___x_2201_ = 2147483648;
v___y_2186_ = v___y_2199_;
v___y_2187_ = v___y_2198_;
v___y_2188_ = v___x_2201_;
goto v___jp_2185_;
}
}
v___jp_2203_:
{
uint8_t v___x_2205_; 
v___x_2205_ = lean_uint64_dec_eq(v___y_2204_, v___x_2202_);
if (v___x_2205_ == 0)
{
uint64_t v___x_2206_; uint8_t v___x_2207_; 
v___x_2206_ = 8388608ULL;
v___x_2207_ = lean_uint64_dec_eq(v___y_2204_, v___x_2206_);
if (v___x_2207_ == 0)
{
uint32_t v___x_2208_; 
v___x_2208_ = lean_uint64_to_uint32(v___y_2204_);
if (v_sign_2172_ == 0)
{
uint32_t v___x_2209_; 
v___x_2209_ = 0;
v___y_2180_ = v___x_2208_;
v___y_2181_ = v___x_2209_;
goto v___jp_2179_;
}
else
{
uint32_t v___x_2210_; 
v___x_2210_ = 2147483648;
v___y_2180_ = v___x_2208_;
v___y_2181_ = v___x_2210_;
goto v___jp_2179_;
}
}
else
{
if (v_sign_2172_ == 0)
{
uint32_t v___x_2211_; 
v___x_2211_ = 0;
v___y_2176_ = v___x_2211_;
goto v___jp_2175_;
}
else
{
uint32_t v___x_2212_; 
v___x_2212_ = 2147483648;
v___y_2176_ = v___x_2212_;
goto v___jp_2175_;
}
}
}
else
{
if (v_sign_2172_ == 0)
{
uint32_t v___x_2213_; 
v___x_2213_ = 0;
return v___x_2213_;
}
else
{
uint32_t v___x_2214_; 
v___x_2214_ = 2147483648;
return v___x_2214_;
}
}
}
v___jp_2215_:
{
uint64_t v___x_2218_; uint64_t v_encodedExponent_2219_; uint32_t v___x_2220_; uint64_t v___x_2221_; uint8_t v___x_2222_; 
v___x_2218_ = 171ULL;
v_encodedExponent_2219_ = lean_uint64_sub(v___y_2216_, v___x_2218_);
v___x_2220_ = lean_uint64_to_uint32(v_encodedExponent_2219_);
v___x_2221_ = 8388608ULL;
v___x_2222_ = lean_uint64_dec_lt(v___y_2217_, v___x_2221_);
if (v___x_2222_ == 0)
{
uint64_t v___x_2223_; uint32_t v___x_2224_; 
v___x_2223_ = lean_uint64_sub(v___y_2217_, v___x_2221_);
v___x_2224_ = lean_uint64_to_uint32(v___x_2223_);
v___y_2198_ = v___x_2220_;
v___y_2199_ = v___x_2224_;
goto v___jp_2197_;
}
else
{
uint32_t v___x_2225_; 
v___x_2225_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_2198_ = v___x_2220_;
v___y_2199_ = v___x_2225_;
goto v___jp_2197_;
}
}
v___jp_2226_:
{
uint64_t v___x_2230_; uint8_t v___x_2231_; 
v___x_2230_ = 425ULL;
v___x_2231_ = lean_uint64_dec_lt(v___x_2230_, v___y_2229_);
if (v___x_2231_ == 0)
{
if (v___y_2227_ == 0)
{
v___y_2216_ = v___y_2229_;
v___y_2217_ = v___y_2228_;
goto v___jp_2215_;
}
else
{
uint64_t v___x_2232_; 
v___x_2232_ = 8388608ULL;
v___y_2216_ = v___y_2229_;
v___y_2217_ = v___x_2232_;
goto v___jp_2215_;
}
}
else
{
if (v_sign_2172_ == 0)
{
uint32_t v___x_2233_; 
v___x_2233_ = 2139095040;
return v___x_2233_;
}
else
{
uint32_t v___x_2234_; 
v___x_2234_ = 4286578688;
return v___x_2234_;
}
}
}
v___jp_2235_:
{
uint64_t v___x_2238_; uint8_t v_carry_2239_; 
v___x_2238_ = 16777216ULL;
v_carry_2239_ = lean_uint64_dec_eq(v___y_2237_, v___x_2238_);
if (v_carry_2239_ == 0)
{
v___y_2227_ = v_carry_2239_;
v___y_2228_ = v___y_2237_;
v___y_2229_ = v___y_2236_;
goto v___jp_2226_;
}
else
{
uint64_t v___x_2240_; uint64_t v___x_2241_; 
v___x_2240_ = 1ULL;
v___x_2241_ = lean_uint64_add(v___y_2236_, v___x_2240_);
v___y_2227_ = v_carry_2239_;
v___y_2228_ = v___y_2237_;
v___y_2229_ = v___x_2241_;
goto v___jp_2226_;
}
}
v___jp_2242_:
{
uint64_t v_position_2244_; uint64_t v___x_2245_; uint8_t v___x_2246_; 
v_position_2244_ = lean_uint64_add(v___y_2243_, v_scale_2174_);
v___x_2245_ = 172ULL;
v___x_2246_ = lean_uint64_dec_lt(v_position_2244_, v___x_2245_);
if (v___x_2246_ == 0)
{
uint64_t v___x_2247_; uint8_t v___x_2248_; 
v___x_2247_ = 23ULL;
v___x_2248_ = lean_uint64_dec_lt(v___y_2243_, v___x_2247_);
if (v___x_2248_ == 0)
{
uint64_t v___x_2249_; uint8_t v___x_2250_; 
v___x_2249_ = lean_uint64_sub(v___y_2243_, v___x_2247_);
v___x_2250_ = lean_uint64_dec_eq(v___x_2249_, v___x_2202_);
if (v___x_2250_ == 0)
{
uint64_t v___x_2251_; uint8_t v___x_2252_; 
v___x_2251_ = 64ULL;
v___x_2252_ = lean_uint64_dec_lt(v___x_2249_, v___x_2251_);
if (v___x_2252_ == 0)
{
uint8_t v___x_2253_; 
v___x_2253_ = lean_uint64_dec_eq(v___x_2249_, v___x_2251_);
if (v___x_2253_ == 0)
{
v___y_2236_ = v_position_2244_;
v___y_2237_ = v___x_2202_;
goto v___jp_2235_;
}
else
{
uint64_t v___x_2254_; uint8_t v___x_2255_; 
v___x_2254_ = 9223372036854775808ULL;
v___x_2255_ = lean_uint64_dec_lt(v___x_2254_, v_product_2173_);
if (v___x_2255_ == 0)
{
v___y_2236_ = v_position_2244_;
v___y_2237_ = v___x_2202_;
goto v___jp_2235_;
}
else
{
uint64_t v___x_2256_; 
v___x_2256_ = 1ULL;
v___y_2236_ = v_position_2244_;
v___y_2237_ = v___x_2256_;
goto v___jp_2235_;
}
}
}
else
{
uint64_t v_quotient_2257_; uint64_t v___x_2258_; uint64_t v___x_2259_; uint64_t v___x_2260_; uint64_t v_remainder_2261_; uint64_t v___x_2262_; uint64_t v_half_2263_; uint8_t v___x_2264_; 
v_quotient_2257_ = lean_uint64_shift_right(v_product_2173_, v___x_2249_);
v___x_2258_ = 1ULL;
v___x_2259_ = lean_uint64_shift_left(v___x_2258_, v___x_2249_);
v___x_2260_ = lean_uint64_sub(v___x_2259_, v___x_2258_);
v_remainder_2261_ = lean_uint64_land(v_product_2173_, v___x_2260_);
v___x_2262_ = lean_uint64_sub(v___x_2249_, v___x_2258_);
v_half_2263_ = lean_uint64_shift_left(v___x_2258_, v___x_2262_);
v___x_2264_ = lean_uint64_dec_lt(v_remainder_2261_, v_half_2263_);
if (v___x_2264_ == 0)
{
uint8_t v___x_2265_; 
v___x_2265_ = lean_uint64_dec_lt(v_half_2263_, v_remainder_2261_);
if (v___x_2265_ == 0)
{
uint64_t v___x_2266_; uint8_t v___x_2267_; 
v___x_2266_ = lean_uint64_land(v_quotient_2257_, v___x_2258_);
v___x_2267_ = lean_uint64_dec_eq(v___x_2266_, v___x_2202_);
if (v___x_2267_ == 0)
{
uint64_t v___x_2268_; 
v___x_2268_ = lean_uint64_add(v_quotient_2257_, v___x_2258_);
v___y_2236_ = v_position_2244_;
v___y_2237_ = v___x_2268_;
goto v___jp_2235_;
}
else
{
v___y_2236_ = v_position_2244_;
v___y_2237_ = v_quotient_2257_;
goto v___jp_2235_;
}
}
else
{
uint64_t v___x_2269_; 
v___x_2269_ = lean_uint64_add(v_quotient_2257_, v___x_2258_);
v___y_2236_ = v_position_2244_;
v___y_2237_ = v___x_2269_;
goto v___jp_2235_;
}
}
else
{
v___y_2236_ = v_position_2244_;
v___y_2237_ = v_quotient_2257_;
goto v___jp_2235_;
}
}
}
else
{
v___y_2236_ = v_position_2244_;
v___y_2237_ = v_product_2173_;
goto v___jp_2235_;
}
}
else
{
uint64_t v___x_2270_; uint64_t v___x_2271_; 
v___x_2270_ = lean_uint64_sub(v___x_2247_, v___y_2243_);
v___x_2271_ = lean_uint64_shift_left(v_product_2173_, v___x_2270_);
v___y_2236_ = v_position_2244_;
v___y_2237_ = v___x_2271_;
goto v___jp_2235_;
}
}
else
{
uint64_t v___x_2272_; uint8_t v___x_2273_; 
v___x_2272_ = 149ULL;
v___x_2273_ = lean_uint64_dec_lt(v_scale_2174_, v___x_2272_);
if (v___x_2273_ == 0)
{
uint64_t v___x_2274_; uint64_t v___x_2275_; 
v___x_2274_ = lean_uint64_sub(v_scale_2174_, v___x_2272_);
v___x_2275_ = lean_uint64_shift_left(v_product_2173_, v___x_2274_);
v___y_2204_ = v___x_2275_;
goto v___jp_2203_;
}
else
{
uint64_t v___x_2276_; uint8_t v___x_2277_; 
v___x_2276_ = lean_uint64_sub(v___x_2272_, v_scale_2174_);
v___x_2277_ = lean_uint64_dec_eq(v___x_2276_, v___x_2202_);
if (v___x_2277_ == 0)
{
uint64_t v___x_2278_; uint8_t v___x_2279_; 
v___x_2278_ = 64ULL;
v___x_2279_ = lean_uint64_dec_lt(v___x_2276_, v___x_2278_);
if (v___x_2279_ == 0)
{
uint8_t v___x_2280_; 
v___x_2280_ = lean_uint64_dec_eq(v___x_2276_, v___x_2278_);
if (v___x_2280_ == 0)
{
v___y_2204_ = v___x_2202_;
goto v___jp_2203_;
}
else
{
uint64_t v___x_2281_; uint8_t v___x_2282_; 
v___x_2281_ = 9223372036854775808ULL;
v___x_2282_ = lean_uint64_dec_lt(v___x_2281_, v_product_2173_);
if (v___x_2282_ == 0)
{
v___y_2204_ = v___x_2202_;
goto v___jp_2203_;
}
else
{
uint64_t v___x_2283_; 
v___x_2283_ = 1ULL;
v___y_2204_ = v___x_2283_;
goto v___jp_2203_;
}
}
}
else
{
uint64_t v_quotient_2284_; uint64_t v___x_2285_; uint64_t v___x_2286_; uint64_t v___x_2287_; uint64_t v_remainder_2288_; uint64_t v___x_2289_; uint64_t v_half_2290_; uint8_t v___x_2291_; 
v_quotient_2284_ = lean_uint64_shift_right(v_product_2173_, v___x_2276_);
v___x_2285_ = 1ULL;
v___x_2286_ = lean_uint64_shift_left(v___x_2285_, v___x_2276_);
v___x_2287_ = lean_uint64_sub(v___x_2286_, v___x_2285_);
v_remainder_2288_ = lean_uint64_land(v_product_2173_, v___x_2287_);
v___x_2289_ = lean_uint64_sub(v___x_2276_, v___x_2285_);
v_half_2290_ = lean_uint64_shift_left(v___x_2285_, v___x_2289_);
v___x_2291_ = lean_uint64_dec_lt(v_remainder_2288_, v_half_2290_);
if (v___x_2291_ == 0)
{
uint8_t v___x_2292_; 
v___x_2292_ = lean_uint64_dec_lt(v_half_2290_, v_remainder_2288_);
if (v___x_2292_ == 0)
{
uint64_t v___x_2293_; uint8_t v___x_2294_; 
v___x_2293_ = lean_uint64_land(v_quotient_2284_, v___x_2285_);
v___x_2294_ = lean_uint64_dec_eq(v___x_2293_, v___x_2202_);
if (v___x_2294_ == 0)
{
uint64_t v___x_2295_; 
v___x_2295_ = lean_uint64_add(v_quotient_2284_, v___x_2285_);
v___y_2204_ = v___x_2295_;
goto v___jp_2203_;
}
else
{
v___y_2204_ = v_quotient_2284_;
goto v___jp_2203_;
}
}
else
{
uint64_t v___x_2296_; 
v___x_2296_ = lean_uint64_add(v_quotient_2284_, v___x_2285_);
v___y_2204_ = v___x_2296_;
goto v___jp_2203_;
}
}
else
{
v___y_2204_ = v_quotient_2284_;
goto v___jp_2203_;
}
}
}
else
{
v___y_2204_ = v_product_2173_;
goto v___jp_2203_;
}
}
}
}
v___jp_2297_:
{
uint64_t v___x_2300_; uint64_t v___x_2301_; uint8_t v___x_2302_; 
v___x_2300_ = 1ULL;
v___x_2301_ = lean_uint64_shift_right(v___y_2298_, v___x_2300_);
v___x_2302_ = lean_uint64_dec_eq(v___x_2301_, v___x_2202_);
if (v___x_2302_ == 0)
{
uint64_t v___x_2303_; 
v___x_2303_ = lean_uint64_add(v___y_2299_, v___x_2300_);
v___y_2243_ = v___x_2303_;
goto v___jp_2242_;
}
else
{
v___y_2243_ = v___y_2299_;
goto v___jp_2242_;
}
}
v___jp_2304_:
{
uint64_t v___x_2309_; uint8_t v___x_2310_; 
v___x_2309_ = lean_uint64_shift_right(v___y_2306_, v___y_2307_);
v___x_2310_ = lean_uint64_dec_eq(v___x_2309_, v___x_2202_);
if (v___x_2310_ == 0)
{
uint64_t v___x_2311_; 
v___x_2311_ = lean_uint64_add(v___y_2305_, v___y_2307_);
v___y_2298_ = v___y_2308_;
v___y_2299_ = v___x_2311_;
goto v___jp_2297_;
}
else
{
v___y_2298_ = v___y_2308_;
v___y_2299_ = v___y_2305_;
goto v___jp_2297_;
}
}
v___jp_2312_:
{
uint64_t v___x_2315_; uint64_t v___x_2316_; uint8_t v___x_2317_; 
v___x_2315_ = 2ULL;
v___x_2316_ = lean_uint64_shift_right(v___y_2313_, v___x_2315_);
v___x_2317_ = lean_uint64_dec_eq(v___x_2316_, v___x_2202_);
if (v___x_2317_ == 0)
{
v___y_2305_ = v___y_2314_;
v___y_2306_ = v___y_2313_;
v___y_2307_ = v___x_2315_;
v___y_2308_ = v___x_2316_;
goto v___jp_2304_;
}
else
{
v___y_2305_ = v___y_2314_;
v___y_2306_ = v___y_2313_;
v___y_2307_ = v___x_2315_;
v___y_2308_ = v___y_2313_;
goto v___jp_2304_;
}
}
v___jp_2318_:
{
uint64_t v___x_2323_; uint8_t v___x_2324_; 
v___x_2323_ = lean_uint64_shift_right(v___y_2321_, v___y_2320_);
v___x_2324_ = lean_uint64_dec_eq(v___x_2323_, v___x_2202_);
if (v___x_2324_ == 0)
{
uint64_t v___x_2325_; 
v___x_2325_ = lean_uint64_add(v___y_2319_, v___y_2320_);
v___y_2313_ = v___y_2322_;
v___y_2314_ = v___x_2325_;
goto v___jp_2312_;
}
else
{
v___y_2313_ = v___y_2322_;
v___y_2314_ = v___y_2319_;
goto v___jp_2312_;
}
}
v___jp_2326_:
{
uint64_t v___x_2329_; uint64_t v___x_2330_; uint8_t v___x_2331_; 
v___x_2329_ = 4ULL;
v___x_2330_ = lean_uint64_shift_right(v___y_2327_, v___x_2329_);
v___x_2331_ = lean_uint64_dec_eq(v___x_2330_, v___x_2202_);
if (v___x_2331_ == 0)
{
v___y_2319_ = v___y_2328_;
v___y_2320_ = v___x_2329_;
v___y_2321_ = v___y_2327_;
v___y_2322_ = v___x_2330_;
goto v___jp_2318_;
}
else
{
v___y_2319_ = v___y_2328_;
v___y_2320_ = v___x_2329_;
v___y_2321_ = v___y_2327_;
v___y_2322_ = v___y_2327_;
goto v___jp_2318_;
}
}
v___jp_2332_:
{
uint64_t v___x_2337_; uint8_t v___x_2338_; 
v___x_2337_ = lean_uint64_shift_right(v___y_2335_, v___y_2333_);
v___x_2338_ = lean_uint64_dec_eq(v___x_2337_, v___x_2202_);
if (v___x_2338_ == 0)
{
uint64_t v___x_2339_; 
v___x_2339_ = lean_uint64_add(v___y_2334_, v___y_2333_);
v___y_2327_ = v___y_2336_;
v___y_2328_ = v___x_2339_;
goto v___jp_2326_;
}
else
{
v___y_2327_ = v___y_2336_;
v___y_2328_ = v___y_2334_;
goto v___jp_2326_;
}
}
v___jp_2340_:
{
uint64_t v___x_2343_; uint64_t v___x_2344_; uint8_t v___x_2345_; 
v___x_2343_ = 8ULL;
v___x_2344_ = lean_uint64_shift_right(v___y_2341_, v___x_2343_);
v___x_2345_ = lean_uint64_dec_eq(v___x_2344_, v___x_2202_);
if (v___x_2345_ == 0)
{
v___y_2333_ = v___x_2343_;
v___y_2334_ = v___y_2342_;
v___y_2335_ = v___y_2341_;
v___y_2336_ = v___x_2344_;
goto v___jp_2332_;
}
else
{
v___y_2333_ = v___x_2343_;
v___y_2334_ = v___y_2342_;
v___y_2335_ = v___y_2341_;
v___y_2336_ = v___y_2341_;
goto v___jp_2332_;
}
}
v___jp_2346_:
{
uint64_t v___x_2351_; uint8_t v___x_2352_; 
v___x_2351_ = lean_uint64_shift_right(v___y_2347_, v___y_2348_);
v___x_2352_ = lean_uint64_dec_eq(v___x_2351_, v___x_2202_);
if (v___x_2352_ == 0)
{
uint64_t v___x_2353_; 
v___x_2353_ = lean_uint64_add(v___y_2349_, v___y_2348_);
v___y_2341_ = v___y_2350_;
v___y_2342_ = v___x_2353_;
goto v___jp_2340_;
}
else
{
v___y_2341_ = v___y_2350_;
v___y_2342_ = v___y_2349_;
goto v___jp_2340_;
}
}
v___jp_2354_:
{
uint64_t v___x_2357_; uint64_t v___x_2358_; uint8_t v___x_2359_; 
v___x_2357_ = 16ULL;
v___x_2358_ = lean_uint64_shift_right(v___y_2355_, v___x_2357_);
v___x_2359_ = lean_uint64_dec_eq(v___x_2358_, v___x_2202_);
if (v___x_2359_ == 0)
{
v___y_2347_ = v___y_2355_;
v___y_2348_ = v___x_2357_;
v___y_2349_ = v___y_2356_;
v___y_2350_ = v___x_2358_;
goto v___jp_2346_;
}
else
{
v___y_2347_ = v___y_2355_;
v___y_2348_ = v___x_2357_;
v___y_2349_ = v___y_2356_;
v___y_2350_ = v___y_2355_;
goto v___jp_2346_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_roundP___boxed(lean_object* v_sign_2370_, lean_object* v_product_2371_, lean_object* v_scale_2372_){
_start:
{
uint8_t v_sign_boxed_2373_; uint64_t v_product_boxed_2374_; uint64_t v_scale_boxed_2375_; uint32_t v_res_2376_; lean_object* v_r_2377_; 
v_sign_boxed_2373_ = lean_unbox(v_sign_2370_);
v_product_boxed_2374_ = lean_unbox_uint64(v_product_2371_);
lean_dec_ref(v_product_2371_);
v_scale_boxed_2375_ = lean_unbox_uint64(v_scale_2372_);
lean_dec_ref(v_scale_2372_);
v_res_2376_ = lp_competition_Submission_FastMul_roundP(v_sign_boxed_2373_, v_product_boxed_2374_, v_scale_boxed_2375_);
v_r_2377_ = lean_box_uint32(v_res_2376_);
return v_r_2377_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_core(uint32_t v_xBits_2378_, uint32_t v_yBits_2379_){
_start:
{
uint32_t v___y_2381_; uint32_t v___y_2385_; uint32_t v___y_2386_; uint32_t v___y_2387_; uint64_t v___y_2391_; uint8_t v___y_2392_; uint32_t v___y_2393_; uint64_t v___y_2394_; uint32_t v___x_2405_; uint32_t v___x_2406_; uint32_t v___x_2407_; uint32_t v___y_2409_; uint32_t v___y_2410_; uint32_t v___y_2411_; uint32_t v___y_2412_; uint8_t v___y_2419_; uint32_t v___y_2420_; uint32_t v___y_2421_; uint32_t v___y_2422_; uint64_t v___y_2426_; uint64_t v___y_2427_; uint32_t v___y_2428_; uint8_t v___y_2429_; uint64_t v___y_2430_; uint64_t v___y_2440_; uint64_t v___y_2441_; uint8_t v___y_2442_; uint8_t v___y_2443_; uint32_t v___y_2444_; uint64_t v___y_2445_; uint64_t v___y_2452_; uint32_t v___y_2453_; uint8_t v___y_2454_; uint64_t v___y_2455_; uint64_t v___y_2456_; uint64_t v___y_2462_; uint64_t v___y_2463_; uint8_t v___y_2464_; uint32_t v___y_2465_; uint64_t v___y_2466_; uint64_t v___y_2467_; uint64_t v___y_2522_; uint64_t v___y_2523_; uint32_t v___y_2524_; uint8_t v___y_2525_; uint64_t v___y_2526_; uint64_t v___y_2527_; uint64_t v___y_2528_; uint64_t v___y_2534_; uint64_t v___y_2535_; uint64_t v___y_2536_; uint8_t v___y_2537_; uint32_t v___y_2538_; uint64_t v___y_2539_; uint64_t v___y_2540_; uint64_t v___y_2541_; uint64_t v___y_2542_; uint64_t v___y_2547_; uint64_t v___y_2548_; uint64_t v___y_2549_; uint32_t v___y_2550_; uint8_t v___y_2551_; uint64_t v___y_2552_; uint64_t v___y_2553_; uint64_t v___y_2558_; uint64_t v___y_2559_; uint64_t v___y_2560_; uint64_t v___y_2561_; uint8_t v___y_2562_; uint32_t v___y_2563_; uint64_t v___y_2564_; uint64_t v___y_2565_; uint64_t v___y_2566_; uint64_t v___y_2571_; uint64_t v___y_2572_; uint32_t v___y_2573_; uint8_t v___y_2574_; uint64_t v___y_2575_; uint64_t v___y_2576_; uint64_t v___y_2577_; uint64_t v___y_2582_; uint64_t v___y_2583_; uint64_t v___y_2584_; uint64_t v___y_2585_; uint64_t v___y_2586_; uint8_t v___y_2587_; uint32_t v___y_2588_; uint64_t v___y_2589_; uint64_t v___y_2590_; uint64_t v___y_2595_; uint64_t v___y_2596_; uint64_t v___y_2597_; uint32_t v___y_2598_; uint8_t v___y_2599_; uint64_t v___y_2600_; uint64_t v___y_2601_; uint64_t v___y_2606_; uint64_t v___y_2607_; uint64_t v___y_2608_; uint64_t v___y_2609_; uint8_t v___y_2610_; uint32_t v___y_2611_; uint64_t v___y_2612_; uint64_t v___y_2613_; uint64_t v___y_2614_; uint64_t v___y_2619_; uint64_t v___y_2620_; uint64_t v___y_2621_; uint32_t v___y_2622_; uint8_t v___y_2623_; uint64_t v___y_2624_; uint64_t v___y_2625_; uint64_t v___y_2630_; uint64_t v___y_2631_; uint64_t v___y_2632_; uint8_t v___y_2633_; uint32_t v___y_2634_; uint64_t v___y_2635_; uint64_t v___y_2636_; uint64_t v___y_2640_; uint32_t v___y_2641_; uint8_t v___y_2642_; uint64_t v___y_2643_; uint64_t v___y_2644_; uint64_t v___y_2645_; uint32_t v_xExponent_2655_; uint32_t v___x_2656_; uint32_t v_yExponent_2657_; uint64_t v___y_2659_; uint8_t v___y_2660_; uint32_t v___y_2661_; uint64_t v___y_2662_; uint64_t v___y_2663_; uint64_t v___y_2670_; uint32_t v___y_2671_; uint8_t v___y_2672_; uint64_t v___y_2673_; uint32_t v___y_2680_; uint8_t v___y_2681_; uint32_t v___y_2682_; uint64_t v___y_2683_; uint8_t v___y_2691_; uint8_t v___y_2706_; uint8_t v___y_2707_; uint8_t v___y_2709_; uint32_t v___x_2716_; uint32_t v___x_2717_; uint32_t v___x_2718_; uint8_t v___x_2719_; 
v___x_2405_ = 23;
v___x_2406_ = lean_uint32_shift_right(v_xBits_2378_, v___x_2405_);
v___x_2407_ = 255;
v_xExponent_2655_ = lean_uint32_land(v___x_2406_, v___x_2407_);
v___x_2656_ = lean_uint32_shift_right(v_yBits_2379_, v___x_2405_);
v_yExponent_2657_ = lean_uint32_land(v___x_2656_, v___x_2407_);
v___x_2716_ = 2147483648;
v___x_2717_ = lean_uint32_land(v_xBits_2378_, v___x_2716_);
v___x_2718_ = 0;
v___x_2719_ = lean_uint32_dec_eq(v___x_2717_, v___x_2718_);
if (v___x_2719_ == 0)
{
uint8_t v___x_2720_; 
v___x_2720_ = 1;
v___y_2709_ = v___x_2720_;
goto v___jp_2708_;
}
else
{
uint8_t v___x_2721_; 
v___x_2721_ = 0;
v___y_2709_ = v___x_2721_;
goto v___jp_2708_;
}
v___jp_2380_:
{
uint32_t v___x_2382_; uint32_t v___x_2383_; 
v___x_2382_ = 8388608;
v___x_2383_ = lean_uint32_lor(v___y_2381_, v___x_2382_);
return v___x_2383_;
}
v___jp_2384_:
{
uint32_t v___x_2388_; uint32_t v___x_2389_; 
v___x_2388_ = lean_uint32_land(v___y_2385_, v___y_2386_);
v___x_2389_ = lean_uint32_lor(v___y_2387_, v___x_2388_);
return v___x_2389_;
}
v___jp_2390_:
{
uint8_t v___x_2395_; 
v___x_2395_ = lean_uint64_dec_eq(v___y_2394_, v___y_2391_);
if (v___x_2395_ == 0)
{
uint64_t v___x_2396_; uint8_t v___x_2397_; 
v___x_2396_ = 8388608ULL;
v___x_2397_ = lean_uint64_dec_eq(v___y_2394_, v___x_2396_);
if (v___x_2397_ == 0)
{
uint32_t v___x_2398_; 
v___x_2398_ = lean_uint64_to_uint32(v___y_2394_);
if (v___y_2392_ == 0)
{
uint32_t v___x_2399_; 
v___x_2399_ = 0;
v___y_2385_ = v___x_2398_;
v___y_2386_ = v___y_2393_;
v___y_2387_ = v___x_2399_;
goto v___jp_2384_;
}
else
{
uint32_t v___x_2400_; 
v___x_2400_ = 2147483648;
v___y_2385_ = v___x_2398_;
v___y_2386_ = v___y_2393_;
v___y_2387_ = v___x_2400_;
goto v___jp_2384_;
}
}
else
{
if (v___y_2392_ == 0)
{
uint32_t v___x_2401_; 
v___x_2401_ = 0;
v___y_2381_ = v___x_2401_;
goto v___jp_2380_;
}
else
{
uint32_t v___x_2402_; 
v___x_2402_ = 2147483648;
v___y_2381_ = v___x_2402_;
goto v___jp_2380_;
}
}
}
else
{
if (v___y_2392_ == 0)
{
uint32_t v___x_2403_; 
v___x_2403_ = 0;
return v___x_2403_;
}
else
{
uint32_t v___x_2404_; 
v___x_2404_ = 2147483648;
return v___x_2404_;
}
}
}
v___jp_2408_:
{
uint32_t v___x_2413_; uint32_t v___x_2414_; uint32_t v___x_2415_; uint32_t v___x_2416_; uint32_t v___x_2417_; 
v___x_2413_ = lean_uint32_land(v___y_2410_, v___x_2407_);
v___x_2414_ = lean_uint32_shift_left(v___x_2413_, v___x_2405_);
v___x_2415_ = lean_uint32_lor(v___y_2412_, v___x_2414_);
v___x_2416_ = lean_uint32_land(v___y_2411_, v___y_2409_);
v___x_2417_ = lean_uint32_lor(v___x_2415_, v___x_2416_);
return v___x_2417_;
}
v___jp_2418_:
{
if (v___y_2419_ == 0)
{
uint32_t v___x_2423_; 
v___x_2423_ = 0;
v___y_2409_ = v___y_2421_;
v___y_2410_ = v___y_2420_;
v___y_2411_ = v___y_2422_;
v___y_2412_ = v___x_2423_;
goto v___jp_2408_;
}
else
{
uint32_t v___x_2424_; 
v___x_2424_ = 2147483648;
v___y_2409_ = v___y_2421_;
v___y_2410_ = v___y_2420_;
v___y_2411_ = v___y_2422_;
v___y_2412_ = v___x_2424_;
goto v___jp_2408_;
}
}
v___jp_2425_:
{
uint64_t v___x_2431_; uint64_t v_encodedExponent_2432_; uint32_t v___x_2433_; uint64_t v___x_2434_; uint8_t v___x_2435_; 
v___x_2431_ = 171ULL;
v_encodedExponent_2432_ = lean_uint64_sub(v___y_2427_, v___x_2431_);
v___x_2433_ = lean_uint64_to_uint32(v_encodedExponent_2432_);
v___x_2434_ = 8388608ULL;
v___x_2435_ = lean_uint64_dec_lt(v___y_2430_, v___x_2434_);
if (v___x_2435_ == 0)
{
uint64_t v___x_2436_; uint32_t v___x_2437_; 
v___x_2436_ = lean_uint64_sub(v___y_2430_, v___x_2434_);
v___x_2437_ = lean_uint64_to_uint32(v___x_2436_);
v___y_2419_ = v___y_2429_;
v___y_2420_ = v___x_2433_;
v___y_2421_ = v___y_2428_;
v___y_2422_ = v___x_2437_;
goto v___jp_2418_;
}
else
{
uint32_t v___x_2438_; 
v___x_2438_ = lean_uint64_to_uint32(v___y_2426_);
v___y_2419_ = v___y_2429_;
v___y_2420_ = v___x_2433_;
v___y_2421_ = v___y_2428_;
v___y_2422_ = v___x_2438_;
goto v___jp_2418_;
}
}
v___jp_2439_:
{
uint64_t v___x_2446_; uint8_t v___x_2447_; 
v___x_2446_ = 425ULL;
v___x_2447_ = lean_uint64_dec_lt(v___x_2446_, v___y_2445_);
if (v___x_2447_ == 0)
{
if (v___y_2442_ == 0)
{
v___y_2426_ = v___y_2441_;
v___y_2427_ = v___y_2445_;
v___y_2428_ = v___y_2444_;
v___y_2429_ = v___y_2443_;
v___y_2430_ = v___y_2440_;
goto v___jp_2425_;
}
else
{
uint64_t v___x_2448_; 
v___x_2448_ = 8388608ULL;
v___y_2426_ = v___y_2441_;
v___y_2427_ = v___y_2445_;
v___y_2428_ = v___y_2444_;
v___y_2429_ = v___y_2443_;
v___y_2430_ = v___x_2448_;
goto v___jp_2425_;
}
}
else
{
if (v___y_2443_ == 0)
{
uint32_t v___x_2449_; 
v___x_2449_ = 2139095040;
return v___x_2449_;
}
else
{
uint32_t v___x_2450_; 
v___x_2450_ = 4286578688;
return v___x_2450_;
}
}
}
v___jp_2451_:
{
uint64_t v___x_2457_; uint8_t v_carry_2458_; 
v___x_2457_ = 16777216ULL;
v_carry_2458_ = lean_uint64_dec_eq(v___y_2456_, v___x_2457_);
if (v_carry_2458_ == 0)
{
v___y_2440_ = v___y_2456_;
v___y_2441_ = v___y_2452_;
v___y_2442_ = v_carry_2458_;
v___y_2443_ = v___y_2454_;
v___y_2444_ = v___y_2453_;
v___y_2445_ = v___y_2455_;
goto v___jp_2439_;
}
else
{
uint64_t v___x_2459_; uint64_t v___x_2460_; 
v___x_2459_ = 1ULL;
v___x_2460_ = lean_uint64_add(v___y_2455_, v___x_2459_);
v___y_2440_ = v___y_2456_;
v___y_2441_ = v___y_2452_;
v___y_2442_ = v_carry_2458_;
v___y_2443_ = v___y_2454_;
v___y_2444_ = v___y_2453_;
v___y_2445_ = v___x_2460_;
goto v___jp_2439_;
}
}
v___jp_2461_:
{
uint64_t v_position_2468_; uint64_t v___x_2469_; uint8_t v___x_2470_; 
v_position_2468_ = lean_uint64_add(v___y_2467_, v___y_2466_);
v___x_2469_ = 172ULL;
v___x_2470_ = lean_uint64_dec_lt(v_position_2468_, v___x_2469_);
if (v___x_2470_ == 0)
{
uint64_t v___x_2471_; uint8_t v___x_2472_; 
v___x_2471_ = 23ULL;
v___x_2472_ = lean_uint64_dec_lt(v___y_2467_, v___x_2471_);
if (v___x_2472_ == 0)
{
uint64_t v___x_2473_; uint8_t v___x_2474_; 
v___x_2473_ = lean_uint64_sub(v___y_2467_, v___x_2471_);
v___x_2474_ = lean_uint64_dec_eq(v___x_2473_, v___y_2463_);
if (v___x_2474_ == 0)
{
uint64_t v___x_2475_; uint8_t v___x_2476_; 
v___x_2475_ = 64ULL;
v___x_2476_ = lean_uint64_dec_lt(v___x_2473_, v___x_2475_);
if (v___x_2476_ == 0)
{
uint8_t v___x_2477_; 
v___x_2477_ = lean_uint64_dec_eq(v___x_2473_, v___x_2475_);
if (v___x_2477_ == 0)
{
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v___y_2463_;
goto v___jp_2451_;
}
else
{
uint64_t v___x_2478_; uint8_t v___x_2479_; 
v___x_2478_ = 9223372036854775808ULL;
v___x_2479_ = lean_uint64_dec_lt(v___x_2478_, v___y_2462_);
if (v___x_2479_ == 0)
{
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v___y_2463_;
goto v___jp_2451_;
}
else
{
uint64_t v___x_2480_; 
v___x_2480_ = 1ULL;
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v___x_2480_;
goto v___jp_2451_;
}
}
}
else
{
uint64_t v_quotient_2481_; uint64_t v___x_2482_; uint64_t v___x_2483_; uint64_t v___x_2484_; uint64_t v_remainder_2485_; uint64_t v___x_2486_; uint64_t v_half_2487_; uint8_t v___x_2488_; 
v_quotient_2481_ = lean_uint64_shift_right(v___y_2462_, v___x_2473_);
v___x_2482_ = 1ULL;
v___x_2483_ = lean_uint64_shift_left(v___x_2482_, v___x_2473_);
v___x_2484_ = lean_uint64_sub(v___x_2483_, v___x_2482_);
v_remainder_2485_ = lean_uint64_land(v___y_2462_, v___x_2484_);
v___x_2486_ = lean_uint64_sub(v___x_2473_, v___x_2482_);
v_half_2487_ = lean_uint64_shift_left(v___x_2482_, v___x_2486_);
v___x_2488_ = lean_uint64_dec_lt(v_remainder_2485_, v_half_2487_);
if (v___x_2488_ == 0)
{
uint8_t v___x_2489_; 
v___x_2489_ = lean_uint64_dec_lt(v_half_2487_, v_remainder_2485_);
if (v___x_2489_ == 0)
{
uint64_t v___x_2490_; uint8_t v___x_2491_; 
v___x_2490_ = lean_uint64_land(v_quotient_2481_, v___x_2482_);
v___x_2491_ = lean_uint64_dec_eq(v___x_2490_, v___y_2463_);
if (v___x_2491_ == 0)
{
uint64_t v___x_2492_; 
v___x_2492_ = lean_uint64_add(v_quotient_2481_, v___x_2482_);
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v___x_2492_;
goto v___jp_2451_;
}
else
{
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v_quotient_2481_;
goto v___jp_2451_;
}
}
else
{
uint64_t v___x_2493_; 
v___x_2493_ = lean_uint64_add(v_quotient_2481_, v___x_2482_);
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v___x_2493_;
goto v___jp_2451_;
}
}
else
{
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v_quotient_2481_;
goto v___jp_2451_;
}
}
}
else
{
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v___y_2462_;
goto v___jp_2451_;
}
}
else
{
uint64_t v___x_2494_; uint64_t v___x_2495_; 
v___x_2494_ = lean_uint64_sub(v___x_2471_, v___y_2467_);
v___x_2495_ = lean_uint64_shift_left(v___y_2462_, v___x_2494_);
v___y_2452_ = v___y_2463_;
v___y_2453_ = v___y_2465_;
v___y_2454_ = v___y_2464_;
v___y_2455_ = v_position_2468_;
v___y_2456_ = v___x_2495_;
goto v___jp_2451_;
}
}
else
{
uint64_t v___x_2496_; uint8_t v___x_2497_; 
v___x_2496_ = 149ULL;
v___x_2497_ = lean_uint64_dec_lt(v___y_2466_, v___x_2496_);
if (v___x_2497_ == 0)
{
uint64_t v___x_2498_; uint64_t v___x_2499_; 
v___x_2498_ = lean_uint64_sub(v___y_2466_, v___x_2496_);
v___x_2499_ = lean_uint64_shift_left(v___y_2462_, v___x_2498_);
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___x_2499_;
goto v___jp_2390_;
}
else
{
uint64_t v___x_2500_; uint8_t v___x_2501_; 
v___x_2500_ = lean_uint64_sub(v___x_2496_, v___y_2466_);
v___x_2501_ = lean_uint64_dec_eq(v___x_2500_, v___y_2463_);
if (v___x_2501_ == 0)
{
uint64_t v___x_2502_; uint8_t v___x_2503_; 
v___x_2502_ = 64ULL;
v___x_2503_ = lean_uint64_dec_lt(v___x_2500_, v___x_2502_);
if (v___x_2503_ == 0)
{
uint8_t v___x_2504_; 
v___x_2504_ = lean_uint64_dec_eq(v___x_2500_, v___x_2502_);
if (v___x_2504_ == 0)
{
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2463_;
goto v___jp_2390_;
}
else
{
uint64_t v___x_2505_; uint8_t v___x_2506_; 
v___x_2505_ = 9223372036854775808ULL;
v___x_2506_ = lean_uint64_dec_lt(v___x_2505_, v___y_2462_);
if (v___x_2506_ == 0)
{
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2463_;
goto v___jp_2390_;
}
else
{
uint64_t v___x_2507_; 
v___x_2507_ = 1ULL;
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___x_2507_;
goto v___jp_2390_;
}
}
}
else
{
uint64_t v_quotient_2508_; uint64_t v___x_2509_; uint64_t v___x_2510_; uint64_t v___x_2511_; uint64_t v_remainder_2512_; uint64_t v___x_2513_; uint64_t v_half_2514_; uint8_t v___x_2515_; 
v_quotient_2508_ = lean_uint64_shift_right(v___y_2462_, v___x_2500_);
v___x_2509_ = 1ULL;
v___x_2510_ = lean_uint64_shift_left(v___x_2509_, v___x_2500_);
v___x_2511_ = lean_uint64_sub(v___x_2510_, v___x_2509_);
v_remainder_2512_ = lean_uint64_land(v___y_2462_, v___x_2511_);
v___x_2513_ = lean_uint64_sub(v___x_2500_, v___x_2509_);
v_half_2514_ = lean_uint64_shift_left(v___x_2509_, v___x_2513_);
v___x_2515_ = lean_uint64_dec_lt(v_remainder_2512_, v_half_2514_);
if (v___x_2515_ == 0)
{
uint8_t v___x_2516_; 
v___x_2516_ = lean_uint64_dec_lt(v_half_2514_, v_remainder_2512_);
if (v___x_2516_ == 0)
{
uint64_t v___x_2517_; uint8_t v___x_2518_; 
v___x_2517_ = lean_uint64_land(v_quotient_2508_, v___x_2509_);
v___x_2518_ = lean_uint64_dec_eq(v___x_2517_, v___y_2463_);
if (v___x_2518_ == 0)
{
uint64_t v___x_2519_; 
v___x_2519_ = lean_uint64_add(v_quotient_2508_, v___x_2509_);
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___x_2519_;
goto v___jp_2390_;
}
else
{
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v_quotient_2508_;
goto v___jp_2390_;
}
}
else
{
uint64_t v___x_2520_; 
v___x_2520_ = lean_uint64_add(v_quotient_2508_, v___x_2509_);
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___x_2520_;
goto v___jp_2390_;
}
}
else
{
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v_quotient_2508_;
goto v___jp_2390_;
}
}
}
else
{
v___y_2391_ = v___y_2463_;
v___y_2392_ = v___y_2464_;
v___y_2393_ = v___y_2465_;
v___y_2394_ = v___y_2462_;
goto v___jp_2390_;
}
}
}
}
v___jp_2521_:
{
uint64_t v___x_2529_; uint64_t v___x_2530_; uint8_t v___x_2531_; 
v___x_2529_ = 1ULL;
v___x_2530_ = lean_uint64_shift_right(v___y_2527_, v___x_2529_);
v___x_2531_ = lean_uint64_dec_eq(v___x_2530_, v___y_2523_);
if (v___x_2531_ == 0)
{
uint64_t v___x_2532_; 
v___x_2532_ = lean_uint64_add(v___y_2528_, v___x_2529_);
v___y_2462_ = v___y_2522_;
v___y_2463_ = v___y_2523_;
v___y_2464_ = v___y_2525_;
v___y_2465_ = v___y_2524_;
v___y_2466_ = v___y_2526_;
v___y_2467_ = v___x_2532_;
goto v___jp_2461_;
}
else
{
v___y_2462_ = v___y_2522_;
v___y_2463_ = v___y_2523_;
v___y_2464_ = v___y_2525_;
v___y_2465_ = v___y_2524_;
v___y_2466_ = v___y_2526_;
v___y_2467_ = v___y_2528_;
goto v___jp_2461_;
}
}
v___jp_2533_:
{
uint64_t v___x_2543_; uint8_t v___x_2544_; 
v___x_2543_ = lean_uint64_shift_right(v___y_2534_, v___y_2539_);
v___x_2544_ = lean_uint64_dec_eq(v___x_2543_, v___y_2535_);
if (v___x_2544_ == 0)
{
uint64_t v___x_2545_; 
v___x_2545_ = lean_uint64_add(v___y_2541_, v___y_2539_);
v___y_2522_ = v___y_2536_;
v___y_2523_ = v___y_2535_;
v___y_2524_ = v___y_2538_;
v___y_2525_ = v___y_2537_;
v___y_2526_ = v___y_2540_;
v___y_2527_ = v___y_2542_;
v___y_2528_ = v___x_2545_;
goto v___jp_2521_;
}
else
{
v___y_2522_ = v___y_2536_;
v___y_2523_ = v___y_2535_;
v___y_2524_ = v___y_2538_;
v___y_2525_ = v___y_2537_;
v___y_2526_ = v___y_2540_;
v___y_2527_ = v___y_2542_;
v___y_2528_ = v___y_2541_;
goto v___jp_2521_;
}
}
v___jp_2546_:
{
uint64_t v___x_2554_; uint64_t v___x_2555_; uint8_t v___x_2556_; 
v___x_2554_ = 2ULL;
v___x_2555_ = lean_uint64_shift_right(v___y_2547_, v___x_2554_);
v___x_2556_ = lean_uint64_dec_eq(v___x_2555_, v___y_2549_);
if (v___x_2556_ == 0)
{
v___y_2534_ = v___y_2547_;
v___y_2535_ = v___y_2549_;
v___y_2536_ = v___y_2548_;
v___y_2537_ = v___y_2551_;
v___y_2538_ = v___y_2550_;
v___y_2539_ = v___x_2554_;
v___y_2540_ = v___y_2552_;
v___y_2541_ = v___y_2553_;
v___y_2542_ = v___x_2555_;
goto v___jp_2533_;
}
else
{
v___y_2534_ = v___y_2547_;
v___y_2535_ = v___y_2549_;
v___y_2536_ = v___y_2548_;
v___y_2537_ = v___y_2551_;
v___y_2538_ = v___y_2550_;
v___y_2539_ = v___x_2554_;
v___y_2540_ = v___y_2552_;
v___y_2541_ = v___y_2553_;
v___y_2542_ = v___y_2547_;
goto v___jp_2533_;
}
}
v___jp_2557_:
{
uint64_t v___x_2567_; uint8_t v___x_2568_; 
v___x_2567_ = lean_uint64_shift_right(v___y_2564_, v___y_2561_);
v___x_2568_ = lean_uint64_dec_eq(v___x_2567_, v___y_2558_);
if (v___x_2568_ == 0)
{
uint64_t v___x_2569_; 
v___x_2569_ = lean_uint64_add(v___y_2560_, v___y_2561_);
v___y_2547_ = v___y_2566_;
v___y_2548_ = v___y_2559_;
v___y_2549_ = v___y_2558_;
v___y_2550_ = v___y_2563_;
v___y_2551_ = v___y_2562_;
v___y_2552_ = v___y_2565_;
v___y_2553_ = v___x_2569_;
goto v___jp_2546_;
}
else
{
v___y_2547_ = v___y_2566_;
v___y_2548_ = v___y_2559_;
v___y_2549_ = v___y_2558_;
v___y_2550_ = v___y_2563_;
v___y_2551_ = v___y_2562_;
v___y_2552_ = v___y_2565_;
v___y_2553_ = v___y_2560_;
goto v___jp_2546_;
}
}
v___jp_2570_:
{
uint64_t v___x_2578_; uint64_t v___x_2579_; uint8_t v___x_2580_; 
v___x_2578_ = 4ULL;
v___x_2579_ = lean_uint64_shift_right(v___y_2575_, v___x_2578_);
v___x_2580_ = lean_uint64_dec_eq(v___x_2579_, v___y_2572_);
if (v___x_2580_ == 0)
{
v___y_2558_ = v___y_2572_;
v___y_2559_ = v___y_2571_;
v___y_2560_ = v___y_2577_;
v___y_2561_ = v___x_2578_;
v___y_2562_ = v___y_2574_;
v___y_2563_ = v___y_2573_;
v___y_2564_ = v___y_2575_;
v___y_2565_ = v___y_2576_;
v___y_2566_ = v___x_2579_;
goto v___jp_2557_;
}
else
{
v___y_2558_ = v___y_2572_;
v___y_2559_ = v___y_2571_;
v___y_2560_ = v___y_2577_;
v___y_2561_ = v___x_2578_;
v___y_2562_ = v___y_2574_;
v___y_2563_ = v___y_2573_;
v___y_2564_ = v___y_2575_;
v___y_2565_ = v___y_2576_;
v___y_2566_ = v___y_2575_;
goto v___jp_2557_;
}
}
v___jp_2581_:
{
uint64_t v___x_2591_; uint8_t v___x_2592_; 
v___x_2591_ = lean_uint64_shift_right(v___y_2582_, v___y_2583_);
v___x_2592_ = lean_uint64_dec_eq(v___x_2591_, v___y_2584_);
if (v___x_2592_ == 0)
{
uint64_t v___x_2593_; 
v___x_2593_ = lean_uint64_add(v___y_2586_, v___y_2583_);
v___y_2571_ = v___y_2585_;
v___y_2572_ = v___y_2584_;
v___y_2573_ = v___y_2588_;
v___y_2574_ = v___y_2587_;
v___y_2575_ = v___y_2590_;
v___y_2576_ = v___y_2589_;
v___y_2577_ = v___x_2593_;
goto v___jp_2570_;
}
else
{
v___y_2571_ = v___y_2585_;
v___y_2572_ = v___y_2584_;
v___y_2573_ = v___y_2588_;
v___y_2574_ = v___y_2587_;
v___y_2575_ = v___y_2590_;
v___y_2576_ = v___y_2589_;
v___y_2577_ = v___y_2586_;
goto v___jp_2570_;
}
}
v___jp_2594_:
{
uint64_t v___x_2602_; uint64_t v___x_2603_; uint8_t v___x_2604_; 
v___x_2602_ = 8ULL;
v___x_2603_ = lean_uint64_shift_right(v___y_2595_, v___x_2602_);
v___x_2604_ = lean_uint64_dec_eq(v___x_2603_, v___y_2597_);
if (v___x_2604_ == 0)
{
v___y_2582_ = v___y_2595_;
v___y_2583_ = v___x_2602_;
v___y_2584_ = v___y_2597_;
v___y_2585_ = v___y_2596_;
v___y_2586_ = v___y_2601_;
v___y_2587_ = v___y_2599_;
v___y_2588_ = v___y_2598_;
v___y_2589_ = v___y_2600_;
v___y_2590_ = v___x_2603_;
goto v___jp_2581_;
}
else
{
v___y_2582_ = v___y_2595_;
v___y_2583_ = v___x_2602_;
v___y_2584_ = v___y_2597_;
v___y_2585_ = v___y_2596_;
v___y_2586_ = v___y_2601_;
v___y_2587_ = v___y_2599_;
v___y_2588_ = v___y_2598_;
v___y_2589_ = v___y_2600_;
v___y_2590_ = v___y_2595_;
goto v___jp_2581_;
}
}
v___jp_2605_:
{
uint64_t v___x_2615_; uint8_t v___x_2616_; 
v___x_2615_ = lean_uint64_shift_right(v___y_2606_, v___y_2609_);
v___x_2616_ = lean_uint64_dec_eq(v___x_2615_, v___y_2607_);
if (v___x_2616_ == 0)
{
uint64_t v___x_2617_; 
v___x_2617_ = lean_uint64_add(v___y_2612_, v___y_2609_);
v___y_2595_ = v___y_2614_;
v___y_2596_ = v___y_2608_;
v___y_2597_ = v___y_2607_;
v___y_2598_ = v___y_2611_;
v___y_2599_ = v___y_2610_;
v___y_2600_ = v___y_2613_;
v___y_2601_ = v___x_2617_;
goto v___jp_2594_;
}
else
{
v___y_2595_ = v___y_2614_;
v___y_2596_ = v___y_2608_;
v___y_2597_ = v___y_2607_;
v___y_2598_ = v___y_2611_;
v___y_2599_ = v___y_2610_;
v___y_2600_ = v___y_2613_;
v___y_2601_ = v___y_2612_;
goto v___jp_2594_;
}
}
v___jp_2618_:
{
uint64_t v___x_2626_; uint64_t v___x_2627_; uint8_t v___x_2628_; 
v___x_2626_ = 16ULL;
v___x_2627_ = lean_uint64_shift_right(v___y_2619_, v___x_2626_);
v___x_2628_ = lean_uint64_dec_eq(v___x_2627_, v___y_2621_);
if (v___x_2628_ == 0)
{
v___y_2606_ = v___y_2619_;
v___y_2607_ = v___y_2621_;
v___y_2608_ = v___y_2620_;
v___y_2609_ = v___x_2626_;
v___y_2610_ = v___y_2623_;
v___y_2611_ = v___y_2622_;
v___y_2612_ = v___y_2625_;
v___y_2613_ = v___y_2624_;
v___y_2614_ = v___x_2627_;
goto v___jp_2605_;
}
else
{
v___y_2606_ = v___y_2619_;
v___y_2607_ = v___y_2621_;
v___y_2608_ = v___y_2620_;
v___y_2609_ = v___x_2626_;
v___y_2610_ = v___y_2623_;
v___y_2611_ = v___y_2622_;
v___y_2612_ = v___y_2625_;
v___y_2613_ = v___y_2624_;
v___y_2614_ = v___y_2619_;
goto v___jp_2605_;
}
}
v___jp_2629_:
{
uint64_t v___x_2637_; uint8_t v___x_2638_; 
v___x_2637_ = lean_uint64_shift_right(v___y_2632_, v___y_2630_);
v___x_2638_ = lean_uint64_dec_eq(v___x_2637_, v___y_2631_);
if (v___x_2638_ == 0)
{
v___y_2619_ = v___y_2636_;
v___y_2620_ = v___y_2632_;
v___y_2621_ = v___y_2631_;
v___y_2622_ = v___y_2634_;
v___y_2623_ = v___y_2633_;
v___y_2624_ = v___y_2635_;
v___y_2625_ = v___y_2630_;
goto v___jp_2618_;
}
else
{
v___y_2619_ = v___y_2636_;
v___y_2620_ = v___y_2632_;
v___y_2621_ = v___y_2631_;
v___y_2622_ = v___y_2634_;
v___y_2623_ = v___y_2633_;
v___y_2624_ = v___y_2635_;
v___y_2625_ = v___y_2631_;
goto v___jp_2618_;
}
}
v___jp_2639_:
{
uint64_t v___x_2646_; uint64_t v___x_2647_; uint8_t v___x_2648_; 
v___x_2646_ = lean_uint64_mul(v___y_2640_, v___y_2644_);
v___x_2647_ = 0ULL;
v___x_2648_ = lean_uint64_dec_eq(v___x_2646_, v___x_2647_);
if (v___x_2648_ == 0)
{
uint64_t v___x_2649_; uint64_t v___x_2650_; uint64_t v___x_2651_; uint8_t v___x_2652_; 
v___x_2649_ = lean_uint64_add(v___y_2643_, v___y_2645_);
v___x_2650_ = 32ULL;
v___x_2651_ = lean_uint64_shift_right(v___x_2646_, v___x_2650_);
v___x_2652_ = lean_uint64_dec_eq(v___x_2651_, v___x_2647_);
if (v___x_2652_ == 0)
{
v___y_2630_ = v___x_2650_;
v___y_2631_ = v___x_2647_;
v___y_2632_ = v___x_2646_;
v___y_2633_ = v___y_2642_;
v___y_2634_ = v___y_2641_;
v___y_2635_ = v___x_2649_;
v___y_2636_ = v___x_2651_;
goto v___jp_2629_;
}
else
{
v___y_2630_ = v___x_2650_;
v___y_2631_ = v___x_2647_;
v___y_2632_ = v___x_2646_;
v___y_2633_ = v___y_2642_;
v___y_2634_ = v___y_2641_;
v___y_2635_ = v___x_2649_;
v___y_2636_ = v___x_2646_;
goto v___jp_2629_;
}
}
else
{
if (v___y_2642_ == 0)
{
uint32_t v___x_2653_; 
v___x_2653_ = 0;
return v___x_2653_;
}
else
{
uint32_t v___x_2654_; 
v___x_2654_ = 2147483648;
return v___x_2654_;
}
}
}
v___jp_2658_:
{
uint64_t v___x_2664_; uint64_t v___x_2665_; uint8_t v___x_2666_; 
v___x_2664_ = lean_uint32_to_uint64(v_yExponent_2657_);
v___x_2665_ = 0ULL;
v___x_2666_ = lean_uint64_dec_eq(v___x_2664_, v___x_2665_);
if (v___x_2666_ == 0)
{
uint64_t v___x_2667_; uint64_t v___x_2668_; 
v___x_2667_ = 1ULL;
v___x_2668_ = lean_uint64_sub(v___x_2664_, v___x_2667_);
v___y_2640_ = v___y_2659_;
v___y_2641_ = v___y_2661_;
v___y_2642_ = v___y_2660_;
v___y_2643_ = v___y_2663_;
v___y_2644_ = v___y_2662_;
v___y_2645_ = v___x_2668_;
goto v___jp_2639_;
}
else
{
v___y_2640_ = v___y_2659_;
v___y_2641_ = v___y_2661_;
v___y_2642_ = v___y_2660_;
v___y_2643_ = v___y_2663_;
v___y_2644_ = v___y_2662_;
v___y_2645_ = v___x_2665_;
goto v___jp_2639_;
}
}
v___jp_2669_:
{
uint64_t v___x_2674_; uint64_t v___x_2675_; uint8_t v___x_2676_; 
v___x_2674_ = lean_uint32_to_uint64(v_xExponent_2655_);
v___x_2675_ = 0ULL;
v___x_2676_ = lean_uint64_dec_eq(v___x_2674_, v___x_2675_);
if (v___x_2676_ == 0)
{
uint64_t v___x_2677_; uint64_t v___x_2678_; 
v___x_2677_ = 1ULL;
v___x_2678_ = lean_uint64_sub(v___x_2674_, v___x_2677_);
v___y_2659_ = v___y_2670_;
v___y_2660_ = v___y_2672_;
v___y_2661_ = v___y_2671_;
v___y_2662_ = v___y_2673_;
v___y_2663_ = v___x_2678_;
goto v___jp_2658_;
}
else
{
v___y_2659_ = v___y_2670_;
v___y_2660_ = v___y_2672_;
v___y_2661_ = v___y_2671_;
v___y_2662_ = v___y_2673_;
v___y_2663_ = v___x_2675_;
goto v___jp_2658_;
}
}
v___jp_2679_:
{
uint32_t v___x_2684_; uint8_t v___x_2685_; 
v___x_2684_ = 0;
v___x_2685_ = lean_uint32_dec_eq(v_yExponent_2657_, v___x_2684_);
if (v___x_2685_ == 0)
{
uint64_t v___x_2686_; uint64_t v___x_2687_; uint64_t v___x_2688_; 
v___x_2686_ = lean_uint32_to_uint64(v___y_2680_);
v___x_2687_ = 8388608ULL;
v___x_2688_ = lean_uint64_lor(v___x_2686_, v___x_2687_);
v___y_2670_ = v___y_2683_;
v___y_2671_ = v___y_2682_;
v___y_2672_ = v___y_2681_;
v___y_2673_ = v___x_2688_;
goto v___jp_2669_;
}
else
{
uint64_t v___x_2689_; 
v___x_2689_ = lean_uint32_to_uint64(v___y_2680_);
v___y_2670_ = v___y_2683_;
v___y_2671_ = v___y_2682_;
v___y_2672_ = v___y_2681_;
v___y_2673_ = v___x_2689_;
goto v___jp_2669_;
}
}
v___jp_2690_:
{
uint32_t v___x_2692_; uint32_t v_xFraction_2693_; uint32_t v_yFraction_2694_; uint32_t v___x_2695_; uint8_t v___x_2696_; 
v___x_2692_ = 8388607;
v_xFraction_2693_ = lean_uint32_land(v_xBits_2378_, v___x_2692_);
v_yFraction_2694_ = lean_uint32_land(v_yBits_2379_, v___x_2692_);
v___x_2695_ = 0;
v___x_2696_ = lean_uint32_dec_eq(v_xExponent_2655_, v___x_2695_);
if (v___x_2696_ == 0)
{
uint64_t v___x_2697_; uint64_t v___x_2698_; uint64_t v___x_2699_; 
v___x_2697_ = lean_uint32_to_uint64(v_xFraction_2693_);
v___x_2698_ = 8388608ULL;
v___x_2699_ = lean_uint64_lor(v___x_2697_, v___x_2698_);
v___y_2680_ = v_yFraction_2694_;
v___y_2681_ = v___y_2691_;
v___y_2682_ = v___x_2692_;
v___y_2683_ = v___x_2699_;
goto v___jp_2679_;
}
else
{
uint64_t v___x_2700_; 
v___x_2700_ = lean_uint32_to_uint64(v_xFraction_2693_);
v___y_2680_ = v_yFraction_2694_;
v___y_2681_ = v___y_2691_;
v___y_2682_ = v___x_2692_;
v___y_2683_ = v___x_2700_;
goto v___jp_2679_;
}
}
v___jp_2701_:
{
uint8_t v___x_2702_; 
v___x_2702_ = 1;
v___y_2691_ = v___x_2702_;
goto v___jp_2690_;
}
v___jp_2703_:
{
uint8_t v___x_2704_; 
v___x_2704_ = 0;
v___y_2691_ = v___x_2704_;
goto v___jp_2690_;
}
v___jp_2705_:
{
if (v___y_2706_ == 0)
{
if (v___y_2707_ == 0)
{
goto v___jp_2703_;
}
else
{
goto v___jp_2701_;
}
}
else
{
if (v___y_2707_ == 0)
{
goto v___jp_2701_;
}
else
{
goto v___jp_2703_;
}
}
}
v___jp_2708_:
{
uint32_t v___x_2710_; uint32_t v___x_2711_; uint32_t v___x_2712_; uint8_t v___x_2713_; 
v___x_2710_ = 2147483648;
v___x_2711_ = lean_uint32_land(v_yBits_2379_, v___x_2710_);
v___x_2712_ = 0;
v___x_2713_ = lean_uint32_dec_eq(v___x_2711_, v___x_2712_);
if (v___x_2713_ == 0)
{
uint8_t v___x_2714_; 
v___x_2714_ = 1;
v___y_2706_ = v___y_2709_;
v___y_2707_ = v___x_2714_;
goto v___jp_2705_;
}
else
{
uint8_t v___x_2715_; 
v___x_2715_ = 0;
v___y_2706_ = v___y_2709_;
v___y_2707_ = v___x_2715_;
goto v___jp_2705_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_core___boxed(lean_object* v_xBits_2722_, lean_object* v_yBits_2723_){
_start:
{
uint32_t v_xBits_boxed_2724_; uint32_t v_yBits_boxed_2725_; uint32_t v_res_2726_; lean_object* v_r_2727_; 
v_xBits_boxed_2724_ = lean_unbox_uint32(v_xBits_2722_);
lean_dec(v_xBits_2722_);
v_yBits_boxed_2725_ = lean_unbox_uint32(v_yBits_2723_);
lean_dec(v_yBits_2723_);
v_res_2726_ = lp_competition_Submission_FastMul_core(v_xBits_boxed_2724_, v_yBits_boxed_2725_);
v_r_2727_ = lean_box_uint32(v_res_2726_);
return v_r_2727_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_sm1(uint32_t v_a_2728_){
_start:
{
uint32_t v___x_2729_; uint32_t v___x_2730_; uint32_t v___x_2731_; uint8_t v___x_2732_; 
v___x_2729_ = 4278190080;
v___x_2730_ = 1;
v___x_2731_ = lean_uint32_shift_left(v_a_2728_, v___x_2730_);
v___x_2732_ = lean_uint32_dec_le(v___x_2729_, v___x_2731_);
return v___x_2732_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sm1___boxed(lean_object* v_a_2733_){
_start:
{
uint32_t v_a_boxed_2734_; uint8_t v_res_2735_; lean_object* v_r_2736_; 
v_a_boxed_2734_ = lean_unbox_uint32(v_a_2733_);
lean_dec(v_a_2733_);
v_res_2735_ = lp_competition_Submission_FastMul_sm1(v_a_boxed_2734_);
v_r_2736_ = lean_box(v_res_2735_);
return v_r_2736_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_special(uint32_t v_a_2737_, uint32_t v_b_2738_){
_start:
{
uint32_t v___x_2739_; uint32_t v___x_2740_; uint32_t v___x_2741_; uint8_t v___x_2742_; 
v___x_2739_ = 4278190080;
v___x_2740_ = 1;
v___x_2741_ = lean_uint32_shift_left(v_a_2737_, v___x_2740_);
v___x_2742_ = lean_uint32_dec_le(v___x_2739_, v___x_2741_);
if (v___x_2742_ == 0)
{
uint32_t v___x_2743_; uint8_t v___x_2744_; 
v___x_2743_ = lean_uint32_shift_left(v_b_2738_, v___x_2740_);
v___x_2744_ = lean_uint32_dec_le(v___x_2739_, v___x_2743_);
return v___x_2744_;
}
else
{
return v___x_2742_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_special___boxed(lean_object* v_a_2745_, lean_object* v_b_2746_){
_start:
{
uint32_t v_a_boxed_2747_; uint32_t v_b_boxed_2748_; uint8_t v_res_2749_; lean_object* v_r_2750_; 
v_a_boxed_2747_ = lean_unbox_uint32(v_a_2745_);
lean_dec(v_a_2745_);
v_b_boxed_2748_ = lean_unbox_uint32(v_b_2746_);
lean_dec(v_b_2746_);
v_res_2749_ = lp_competition_Submission_FastMul_special(v_a_boxed_2747_, v_b_boxed_2748_);
v_r_2750_ = lean_box(v_res_2749_);
return v_r_2750_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_ofBits(uint32_t v_w_2751_){
_start:
{
return v_w_2751_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_ofBits___boxed(lean_object* v_w_2752_){
_start:
{
uint32_t v_w_boxed_2753_; uint32_t v_res_2754_; lean_object* v_r_2755_; 
v_w_boxed_2753_ = lean_unbox_uint32(v_w_2752_);
lean_dec(v_w_2752_);
v_res_2754_ = lp_competition_Submission_FastMul_ofBits(v_w_boxed_2753_);
v_r_2755_ = lean_box_uint32(v_res_2754_);
return v_r_2755_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mul(uint32_t v_x_2756_, uint32_t v_y_2757_){
_start:
{
uint32_t v___y_2759_; uint32_t v___y_2763_; uint32_t v___y_2764_; uint32_t v___y_2765_; uint32_t v___y_2769_; uint8_t v___y_2770_; uint64_t v___y_2771_; uint64_t v___y_2772_; uint32_t v___y_2784_; uint32_t v___y_2785_; uint32_t v___y_2786_; uint32_t v___y_2787_; uint32_t v___y_2788_; uint32_t v___y_2789_; uint32_t v___y_2796_; uint32_t v___y_2797_; uint32_t v___y_2798_; uint32_t v___y_2799_; uint8_t v___y_2800_; uint32_t v___y_2801_; uint32_t v___y_2805_; uint32_t v___y_2806_; uint64_t v___y_2807_; uint32_t v___y_2808_; uint8_t v___y_2809_; uint64_t v___y_2810_; uint64_t v___y_2811_; uint32_t v___y_2821_; uint64_t v___y_2822_; uint32_t v___y_2823_; uint8_t v___y_2824_; uint32_t v___y_2825_; uint8_t v___y_2826_; uint64_t v___y_2827_; uint64_t v___y_2828_; uint32_t v___y_2835_; uint32_t v___y_2836_; uint32_t v___y_2837_; uint8_t v___y_2838_; uint64_t v___y_2839_; uint64_t v___y_2840_; uint64_t v___y_2841_; uint32_t v___y_2847_; uint32_t v___y_2848_; uint64_t v___y_2849_; uint64_t v___y_2850_; uint32_t v___y_2851_; uint8_t v___y_2852_; uint64_t v___y_2853_; uint64_t v___y_2854_; uint32_t v___y_2909_; uint32_t v___y_2910_; uint64_t v___y_2911_; uint64_t v___y_2912_; uint32_t v___y_2913_; uint8_t v___y_2914_; uint64_t v___y_2915_; uint64_t v___y_2916_; uint64_t v___y_2917_; uint64_t v___y_2923_; uint32_t v___y_2924_; uint32_t v___y_2925_; uint64_t v___y_2926_; uint64_t v___y_2927_; uint64_t v___y_2928_; uint32_t v___y_2929_; uint8_t v___y_2930_; uint64_t v___y_2931_; uint64_t v___y_2932_; uint64_t v___y_2933_; uint32_t v___y_2938_; uint32_t v___y_2939_; uint64_t v___y_2940_; uint64_t v___y_2941_; uint64_t v___y_2942_; uint32_t v___y_2943_; uint8_t v___y_2944_; uint64_t v___y_2945_; uint64_t v___y_2946_; uint32_t v___y_2951_; uint32_t v___y_2952_; uint64_t v___y_2953_; uint64_t v___y_2954_; uint64_t v___y_2955_; uint64_t v___y_2956_; uint64_t v___y_2957_; uint32_t v___y_2958_; uint8_t v___y_2959_; uint64_t v___y_2960_; uint64_t v___y_2961_; uint32_t v___y_2966_; uint32_t v___y_2967_; uint64_t v___y_2968_; uint64_t v___y_2969_; uint64_t v___y_2970_; uint32_t v___y_2971_; uint8_t v___y_2972_; uint64_t v___y_2973_; uint64_t v___y_2974_; uint32_t v___y_2979_; uint64_t v___y_2980_; uint32_t v___y_2981_; uint64_t v___y_2982_; uint64_t v___y_2983_; uint64_t v___y_2984_; uint64_t v___y_2985_; uint32_t v___y_2986_; uint8_t v___y_2987_; uint64_t v___y_2988_; uint64_t v___y_2989_; uint32_t v___y_2994_; uint32_t v___y_2995_; uint64_t v___y_2996_; uint64_t v___y_2997_; uint64_t v___y_2998_; uint32_t v___y_2999_; uint8_t v___y_3000_; uint64_t v___y_3001_; uint64_t v___y_3002_; uint64_t v___y_3007_; uint32_t v___y_3008_; uint32_t v___y_3009_; uint64_t v___y_3010_; uint64_t v___y_3011_; uint64_t v___y_3012_; uint64_t v___y_3013_; uint32_t v___y_3014_; uint8_t v___y_3015_; uint64_t v___y_3016_; uint64_t v___y_3017_; uint32_t v___y_3022_; uint32_t v___y_3023_; uint64_t v___y_3024_; uint64_t v___y_3025_; uint64_t v___y_3026_; uint32_t v___y_3027_; uint8_t v___y_3028_; uint64_t v___y_3029_; uint64_t v___y_3030_; uint32_t v___y_3035_; uint32_t v___y_3036_; uint64_t v___y_3037_; uint64_t v___y_3038_; uint32_t v___y_3039_; uint8_t v___y_3040_; uint64_t v___y_3041_; uint64_t v___y_3042_; uint64_t v___y_3043_; uint32_t v___y_3047_; uint32_t v___y_3048_; uint64_t v___y_3049_; uint32_t v___y_3050_; uint64_t v___y_3051_; uint8_t v___y_3052_; uint64_t v___y_3053_; uint64_t v___y_3054_; uint32_t v___y_3065_; uint64_t v___y_3066_; uint32_t v___y_3067_; uint32_t v___y_3068_; uint32_t v___y_3069_; uint8_t v___y_3070_; uint64_t v___y_3071_; uint64_t v___y_3072_; uint32_t v___y_3079_; uint32_t v___y_3080_; uint64_t v___y_3081_; uint32_t v___y_3082_; uint32_t v___y_3083_; uint32_t v___y_3084_; uint8_t v___y_3085_; uint64_t v___y_3086_; uint32_t v___y_3093_; uint32_t v___y_3094_; uint32_t v___y_3095_; uint32_t v___y_3096_; uint32_t v___y_3097_; uint8_t v___y_3098_; uint32_t v___y_3099_; uint64_t v___y_3100_; uint32_t v___y_3108_; uint32_t v___y_3109_; uint32_t v___y_3110_; uint32_t v___y_3111_; uint8_t v___y_3112_; uint32_t v___y_3123_; uint32_t v___y_3124_; uint32_t v___y_3125_; uint32_t v___y_3126_; uint32_t v___y_3129_; uint8_t v___y_3130_; uint32_t v___y_3131_; uint32_t v___y_3132_; uint8_t v___y_3133_; uint32_t v___y_3134_; uint8_t v___y_3135_; uint32_t v___y_3137_; uint8_t v___y_3138_; uint32_t v___y_3139_; uint32_t v___y_3140_; uint32_t v___y_3141_; uint8_t v___y_3142_; uint8_t v___y_3149_; uint32_t v___x_3165_; uint32_t v___x_3166_; uint32_t v___x_3167_; uint8_t v___x_3168_; 
v___x_3165_ = 4278190080;
v___x_3166_ = 1;
v___x_3167_ = lean_uint32_shift_left(v_x_2756_, v___x_3166_);
v___x_3168_ = lean_uint32_dec_le(v___x_3165_, v___x_3167_);
if (v___x_3168_ == 0)
{
uint32_t v___x_3169_; uint8_t v___x_3170_; 
v___x_3169_ = lean_uint32_shift_left(v_y_2757_, v___x_3166_);
v___x_3170_ = lean_uint32_dec_le(v___x_3165_, v___x_3169_);
v___y_3149_ = v___x_3170_;
goto v___jp_3148_;
}
else
{
v___y_3149_ = v___x_3168_;
goto v___jp_3148_;
}
v___jp_2758_:
{
uint32_t v___x_2760_; uint32_t v___x_2761_; 
v___x_2760_ = 8388608;
v___x_2761_ = lean_uint32_lor(v___y_2759_, v___x_2760_);
return v___x_2761_;
}
v___jp_2762_:
{
uint32_t v___x_2766_; uint32_t v___x_2767_; 
v___x_2766_ = lean_uint32_land(v___y_2764_, v___y_2763_);
v___x_2767_ = lean_uint32_lor(v___y_2765_, v___x_2766_);
return v___x_2767_;
}
v___jp_2768_:
{
uint8_t v___x_2773_; 
v___x_2773_ = lean_uint64_dec_eq(v___y_2772_, v___y_2771_);
if (v___x_2773_ == 0)
{
uint64_t v___x_2774_; uint8_t v___x_2775_; 
v___x_2774_ = 8388608ULL;
v___x_2775_ = lean_uint64_dec_eq(v___y_2772_, v___x_2774_);
if (v___x_2775_ == 0)
{
uint32_t v___x_2776_; 
v___x_2776_ = lean_uint64_to_uint32(v___y_2772_);
if (v___y_2770_ == 0)
{
uint32_t v___x_2777_; 
v___x_2777_ = 0;
v___y_2763_ = v___y_2769_;
v___y_2764_ = v___x_2776_;
v___y_2765_ = v___x_2777_;
goto v___jp_2762_;
}
else
{
uint32_t v___x_2778_; 
v___x_2778_ = 2147483648;
v___y_2763_ = v___y_2769_;
v___y_2764_ = v___x_2776_;
v___y_2765_ = v___x_2778_;
goto v___jp_2762_;
}
}
else
{
if (v___y_2770_ == 0)
{
uint32_t v___x_2779_; 
v___x_2779_ = 0;
v___y_2759_ = v___x_2779_;
goto v___jp_2758_;
}
else
{
uint32_t v___x_2780_; 
v___x_2780_ = 2147483648;
v___y_2759_ = v___x_2780_;
goto v___jp_2758_;
}
}
}
else
{
if (v___y_2770_ == 0)
{
uint32_t v___x_2781_; 
v___x_2781_ = 0;
return v___x_2781_;
}
else
{
uint32_t v___x_2782_; 
v___x_2782_ = 2147483648;
return v___x_2782_;
}
}
}
v___jp_2783_:
{
uint32_t v___x_2790_; uint32_t v___x_2791_; uint32_t v___x_2792_; uint32_t v___x_2793_; uint32_t v___x_2794_; 
v___x_2790_ = lean_uint32_land(v___y_2785_, v___y_2784_);
v___x_2791_ = lean_uint32_shift_left(v___x_2790_, v___y_2788_);
v___x_2792_ = lean_uint32_lor(v___y_2789_, v___x_2791_);
v___x_2793_ = lean_uint32_land(v___y_2787_, v___y_2786_);
v___x_2794_ = lean_uint32_lor(v___x_2792_, v___x_2793_);
return v___x_2794_;
}
v___jp_2795_:
{
if (v___y_2800_ == 0)
{
uint32_t v___x_2802_; 
v___x_2802_ = 0;
v___y_2784_ = v___y_2797_;
v___y_2785_ = v___y_2796_;
v___y_2786_ = v___y_2798_;
v___y_2787_ = v___y_2801_;
v___y_2788_ = v___y_2799_;
v___y_2789_ = v___x_2802_;
goto v___jp_2783_;
}
else
{
uint32_t v___x_2803_; 
v___x_2803_ = 2147483648;
v___y_2784_ = v___y_2797_;
v___y_2785_ = v___y_2796_;
v___y_2786_ = v___y_2798_;
v___y_2787_ = v___y_2801_;
v___y_2788_ = v___y_2799_;
v___y_2789_ = v___x_2803_;
goto v___jp_2783_;
}
}
v___jp_2804_:
{
uint64_t v___x_2812_; uint64_t v_encodedExponent_2813_; uint32_t v___x_2814_; uint64_t v___x_2815_; uint8_t v___x_2816_; 
v___x_2812_ = 171ULL;
v_encodedExponent_2813_ = lean_uint64_sub(v___y_2807_, v___x_2812_);
v___x_2814_ = lean_uint64_to_uint32(v_encodedExponent_2813_);
v___x_2815_ = 8388608ULL;
v___x_2816_ = lean_uint64_dec_lt(v___y_2811_, v___x_2815_);
if (v___x_2816_ == 0)
{
uint64_t v___x_2817_; uint32_t v___x_2818_; 
v___x_2817_ = lean_uint64_sub(v___y_2811_, v___x_2815_);
v___x_2818_ = lean_uint64_to_uint32(v___x_2817_);
v___y_2796_ = v___x_2814_;
v___y_2797_ = v___y_2805_;
v___y_2798_ = v___y_2806_;
v___y_2799_ = v___y_2808_;
v___y_2800_ = v___y_2809_;
v___y_2801_ = v___x_2818_;
goto v___jp_2795_;
}
else
{
uint32_t v___x_2819_; 
v___x_2819_ = lean_uint64_to_uint32(v___y_2810_);
v___y_2796_ = v___x_2814_;
v___y_2797_ = v___y_2805_;
v___y_2798_ = v___y_2806_;
v___y_2799_ = v___y_2808_;
v___y_2800_ = v___y_2809_;
v___y_2801_ = v___x_2819_;
goto v___jp_2795_;
}
}
v___jp_2820_:
{
uint64_t v___x_2829_; uint8_t v___x_2830_; 
v___x_2829_ = 425ULL;
v___x_2830_ = lean_uint64_dec_lt(v___x_2829_, v___y_2828_);
if (v___x_2830_ == 0)
{
if (v___y_2824_ == 0)
{
v___y_2805_ = v___y_2821_;
v___y_2806_ = v___y_2823_;
v___y_2807_ = v___y_2828_;
v___y_2808_ = v___y_2825_;
v___y_2809_ = v___y_2826_;
v___y_2810_ = v___y_2827_;
v___y_2811_ = v___y_2822_;
goto v___jp_2804_;
}
else
{
uint64_t v___x_2831_; 
v___x_2831_ = 8388608ULL;
v___y_2805_ = v___y_2821_;
v___y_2806_ = v___y_2823_;
v___y_2807_ = v___y_2828_;
v___y_2808_ = v___y_2825_;
v___y_2809_ = v___y_2826_;
v___y_2810_ = v___y_2827_;
v___y_2811_ = v___x_2831_;
goto v___jp_2804_;
}
}
else
{
if (v___y_2826_ == 0)
{
uint32_t v___x_2832_; 
v___x_2832_ = 2139095040;
return v___x_2832_;
}
else
{
uint32_t v___x_2833_; 
v___x_2833_ = 4286578688;
return v___x_2833_;
}
}
}
v___jp_2834_:
{
uint64_t v___x_2842_; uint8_t v_carry_2843_; 
v___x_2842_ = 16777216ULL;
v_carry_2843_ = lean_uint64_dec_eq(v___y_2841_, v___x_2842_);
if (v_carry_2843_ == 0)
{
v___y_2821_ = v___y_2835_;
v___y_2822_ = v___y_2841_;
v___y_2823_ = v___y_2836_;
v___y_2824_ = v_carry_2843_;
v___y_2825_ = v___y_2837_;
v___y_2826_ = v___y_2838_;
v___y_2827_ = v___y_2840_;
v___y_2828_ = v___y_2839_;
goto v___jp_2820_;
}
else
{
uint64_t v___x_2844_; uint64_t v___x_2845_; 
v___x_2844_ = 1ULL;
v___x_2845_ = lean_uint64_add(v___y_2839_, v___x_2844_);
v___y_2821_ = v___y_2835_;
v___y_2822_ = v___y_2841_;
v___y_2823_ = v___y_2836_;
v___y_2824_ = v_carry_2843_;
v___y_2825_ = v___y_2837_;
v___y_2826_ = v___y_2838_;
v___y_2827_ = v___y_2840_;
v___y_2828_ = v___x_2845_;
goto v___jp_2820_;
}
}
v___jp_2846_:
{
uint64_t v_position_2855_; uint64_t v___x_2856_; uint8_t v___x_2857_; 
v_position_2855_ = lean_uint64_add(v___y_2854_, v___y_2850_);
v___x_2856_ = 172ULL;
v___x_2857_ = lean_uint64_dec_lt(v_position_2855_, v___x_2856_);
if (v___x_2857_ == 0)
{
uint64_t v___x_2858_; uint8_t v___x_2859_; 
v___x_2858_ = 23ULL;
v___x_2859_ = lean_uint64_dec_lt(v___y_2854_, v___x_2858_);
if (v___x_2859_ == 0)
{
uint64_t v___x_2860_; uint8_t v___x_2861_; 
v___x_2860_ = lean_uint64_sub(v___y_2854_, v___x_2858_);
v___x_2861_ = lean_uint64_dec_eq(v___x_2860_, v___y_2853_);
if (v___x_2861_ == 0)
{
uint64_t v___x_2862_; uint8_t v___x_2863_; 
v___x_2862_ = 64ULL;
v___x_2863_ = lean_uint64_dec_lt(v___x_2860_, v___x_2862_);
if (v___x_2863_ == 0)
{
uint8_t v___x_2864_; 
v___x_2864_ = lean_uint64_dec_eq(v___x_2860_, v___x_2862_);
if (v___x_2864_ == 0)
{
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v___y_2853_;
goto v___jp_2834_;
}
else
{
uint64_t v___x_2865_; uint8_t v___x_2866_; 
v___x_2865_ = 9223372036854775808ULL;
v___x_2866_ = lean_uint64_dec_lt(v___x_2865_, v___y_2849_);
if (v___x_2866_ == 0)
{
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v___y_2853_;
goto v___jp_2834_;
}
else
{
uint64_t v___x_2867_; 
v___x_2867_ = 1ULL;
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v___x_2867_;
goto v___jp_2834_;
}
}
}
else
{
uint64_t v_quotient_2868_; uint64_t v___x_2869_; uint64_t v___x_2870_; uint64_t v___x_2871_; uint64_t v_remainder_2872_; uint64_t v___x_2873_; uint64_t v_half_2874_; uint8_t v___x_2875_; 
v_quotient_2868_ = lean_uint64_shift_right(v___y_2849_, v___x_2860_);
v___x_2869_ = 1ULL;
v___x_2870_ = lean_uint64_shift_left(v___x_2869_, v___x_2860_);
v___x_2871_ = lean_uint64_sub(v___x_2870_, v___x_2869_);
v_remainder_2872_ = lean_uint64_land(v___y_2849_, v___x_2871_);
v___x_2873_ = lean_uint64_sub(v___x_2860_, v___x_2869_);
v_half_2874_ = lean_uint64_shift_left(v___x_2869_, v___x_2873_);
v___x_2875_ = lean_uint64_dec_lt(v_remainder_2872_, v_half_2874_);
if (v___x_2875_ == 0)
{
uint8_t v___x_2876_; 
v___x_2876_ = lean_uint64_dec_lt(v_half_2874_, v_remainder_2872_);
if (v___x_2876_ == 0)
{
uint64_t v___x_2877_; uint8_t v___x_2878_; 
v___x_2877_ = lean_uint64_land(v_quotient_2868_, v___x_2869_);
v___x_2878_ = lean_uint64_dec_eq(v___x_2877_, v___y_2853_);
if (v___x_2878_ == 0)
{
uint64_t v___x_2879_; 
v___x_2879_ = lean_uint64_add(v_quotient_2868_, v___x_2869_);
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v___x_2879_;
goto v___jp_2834_;
}
else
{
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v_quotient_2868_;
goto v___jp_2834_;
}
}
else
{
uint64_t v___x_2880_; 
v___x_2880_ = lean_uint64_add(v_quotient_2868_, v___x_2869_);
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v___x_2880_;
goto v___jp_2834_;
}
}
else
{
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v_quotient_2868_;
goto v___jp_2834_;
}
}
}
else
{
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v___y_2849_;
goto v___jp_2834_;
}
}
else
{
uint64_t v___x_2881_; uint64_t v___x_2882_; 
v___x_2881_ = lean_uint64_sub(v___x_2858_, v___y_2854_);
v___x_2882_ = lean_uint64_shift_left(v___y_2849_, v___x_2881_);
v___y_2835_ = v___y_2847_;
v___y_2836_ = v___y_2848_;
v___y_2837_ = v___y_2851_;
v___y_2838_ = v___y_2852_;
v___y_2839_ = v_position_2855_;
v___y_2840_ = v___y_2853_;
v___y_2841_ = v___x_2882_;
goto v___jp_2834_;
}
}
else
{
uint64_t v___x_2883_; uint8_t v___x_2884_; 
v___x_2883_ = 149ULL;
v___x_2884_ = lean_uint64_dec_lt(v___y_2850_, v___x_2883_);
if (v___x_2884_ == 0)
{
uint64_t v___x_2885_; uint64_t v___x_2886_; 
v___x_2885_ = lean_uint64_sub(v___y_2850_, v___x_2883_);
v___x_2886_ = lean_uint64_shift_left(v___y_2849_, v___x_2885_);
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___x_2886_;
goto v___jp_2768_;
}
else
{
uint64_t v___x_2887_; uint8_t v___x_2888_; 
v___x_2887_ = lean_uint64_sub(v___x_2883_, v___y_2850_);
v___x_2888_ = lean_uint64_dec_eq(v___x_2887_, v___y_2853_);
if (v___x_2888_ == 0)
{
uint64_t v___x_2889_; uint8_t v___x_2890_; 
v___x_2889_ = 64ULL;
v___x_2890_ = lean_uint64_dec_lt(v___x_2887_, v___x_2889_);
if (v___x_2890_ == 0)
{
uint8_t v___x_2891_; 
v___x_2891_ = lean_uint64_dec_eq(v___x_2887_, v___x_2889_);
if (v___x_2891_ == 0)
{
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2853_;
goto v___jp_2768_;
}
else
{
uint64_t v___x_2892_; uint8_t v___x_2893_; 
v___x_2892_ = 9223372036854775808ULL;
v___x_2893_ = lean_uint64_dec_lt(v___x_2892_, v___y_2849_);
if (v___x_2893_ == 0)
{
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2853_;
goto v___jp_2768_;
}
else
{
uint64_t v___x_2894_; 
v___x_2894_ = 1ULL;
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___x_2894_;
goto v___jp_2768_;
}
}
}
else
{
uint64_t v_quotient_2895_; uint64_t v___x_2896_; uint64_t v___x_2897_; uint64_t v___x_2898_; uint64_t v_remainder_2899_; uint64_t v___x_2900_; uint64_t v_half_2901_; uint8_t v___x_2902_; 
v_quotient_2895_ = lean_uint64_shift_right(v___y_2849_, v___x_2887_);
v___x_2896_ = 1ULL;
v___x_2897_ = lean_uint64_shift_left(v___x_2896_, v___x_2887_);
v___x_2898_ = lean_uint64_sub(v___x_2897_, v___x_2896_);
v_remainder_2899_ = lean_uint64_land(v___y_2849_, v___x_2898_);
v___x_2900_ = lean_uint64_sub(v___x_2887_, v___x_2896_);
v_half_2901_ = lean_uint64_shift_left(v___x_2896_, v___x_2900_);
v___x_2902_ = lean_uint64_dec_lt(v_remainder_2899_, v_half_2901_);
if (v___x_2902_ == 0)
{
uint8_t v___x_2903_; 
v___x_2903_ = lean_uint64_dec_lt(v_half_2901_, v_remainder_2899_);
if (v___x_2903_ == 0)
{
uint64_t v___x_2904_; uint8_t v___x_2905_; 
v___x_2904_ = lean_uint64_land(v_quotient_2895_, v___x_2896_);
v___x_2905_ = lean_uint64_dec_eq(v___x_2904_, v___y_2853_);
if (v___x_2905_ == 0)
{
uint64_t v___x_2906_; 
v___x_2906_ = lean_uint64_add(v_quotient_2895_, v___x_2896_);
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___x_2906_;
goto v___jp_2768_;
}
else
{
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v_quotient_2895_;
goto v___jp_2768_;
}
}
else
{
uint64_t v___x_2907_; 
v___x_2907_ = lean_uint64_add(v_quotient_2895_, v___x_2896_);
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___x_2907_;
goto v___jp_2768_;
}
}
else
{
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v_quotient_2895_;
goto v___jp_2768_;
}
}
}
else
{
v___y_2769_ = v___y_2848_;
v___y_2770_ = v___y_2852_;
v___y_2771_ = v___y_2853_;
v___y_2772_ = v___y_2849_;
goto v___jp_2768_;
}
}
}
}
v___jp_2908_:
{
uint64_t v___x_2918_; uint64_t v___x_2919_; uint8_t v___x_2920_; 
v___x_2918_ = 1ULL;
v___x_2919_ = lean_uint64_shift_right(v___y_2915_, v___x_2918_);
v___x_2920_ = lean_uint64_dec_eq(v___x_2919_, v___y_2916_);
if (v___x_2920_ == 0)
{
uint64_t v___x_2921_; 
v___x_2921_ = lean_uint64_add(v___y_2917_, v___x_2918_);
v___y_2847_ = v___y_2909_;
v___y_2848_ = v___y_2910_;
v___y_2849_ = v___y_2911_;
v___y_2850_ = v___y_2912_;
v___y_2851_ = v___y_2913_;
v___y_2852_ = v___y_2914_;
v___y_2853_ = v___y_2916_;
v___y_2854_ = v___x_2921_;
goto v___jp_2846_;
}
else
{
v___y_2847_ = v___y_2909_;
v___y_2848_ = v___y_2910_;
v___y_2849_ = v___y_2911_;
v___y_2850_ = v___y_2912_;
v___y_2851_ = v___y_2913_;
v___y_2852_ = v___y_2914_;
v___y_2853_ = v___y_2916_;
v___y_2854_ = v___y_2917_;
goto v___jp_2846_;
}
}
v___jp_2922_:
{
uint64_t v___x_2934_; uint8_t v___x_2935_; 
v___x_2934_ = lean_uint64_shift_right(v___y_2927_, v___y_2923_);
v___x_2935_ = lean_uint64_dec_eq(v___x_2934_, v___y_2932_);
if (v___x_2935_ == 0)
{
uint64_t v___x_2936_; 
v___x_2936_ = lean_uint64_add(v___y_2931_, v___y_2923_);
v___y_2909_ = v___y_2924_;
v___y_2910_ = v___y_2925_;
v___y_2911_ = v___y_2926_;
v___y_2912_ = v___y_2928_;
v___y_2913_ = v___y_2929_;
v___y_2914_ = v___y_2930_;
v___y_2915_ = v___y_2933_;
v___y_2916_ = v___y_2932_;
v___y_2917_ = v___x_2936_;
goto v___jp_2908_;
}
else
{
v___y_2909_ = v___y_2924_;
v___y_2910_ = v___y_2925_;
v___y_2911_ = v___y_2926_;
v___y_2912_ = v___y_2928_;
v___y_2913_ = v___y_2929_;
v___y_2914_ = v___y_2930_;
v___y_2915_ = v___y_2933_;
v___y_2916_ = v___y_2932_;
v___y_2917_ = v___y_2931_;
goto v___jp_2908_;
}
}
v___jp_2937_:
{
uint64_t v___x_2947_; uint64_t v___x_2948_; uint8_t v___x_2949_; 
v___x_2947_ = 2ULL;
v___x_2948_ = lean_uint64_shift_right(v___y_2941_, v___x_2947_);
v___x_2949_ = lean_uint64_dec_eq(v___x_2948_, v___y_2945_);
if (v___x_2949_ == 0)
{
v___y_2923_ = v___x_2947_;
v___y_2924_ = v___y_2938_;
v___y_2925_ = v___y_2939_;
v___y_2926_ = v___y_2940_;
v___y_2927_ = v___y_2941_;
v___y_2928_ = v___y_2942_;
v___y_2929_ = v___y_2943_;
v___y_2930_ = v___y_2944_;
v___y_2931_ = v___y_2946_;
v___y_2932_ = v___y_2945_;
v___y_2933_ = v___x_2948_;
goto v___jp_2922_;
}
else
{
v___y_2923_ = v___x_2947_;
v___y_2924_ = v___y_2938_;
v___y_2925_ = v___y_2939_;
v___y_2926_ = v___y_2940_;
v___y_2927_ = v___y_2941_;
v___y_2928_ = v___y_2942_;
v___y_2929_ = v___y_2943_;
v___y_2930_ = v___y_2944_;
v___y_2931_ = v___y_2946_;
v___y_2932_ = v___y_2945_;
v___y_2933_ = v___y_2941_;
goto v___jp_2922_;
}
}
v___jp_2950_:
{
uint64_t v___x_2962_; uint8_t v___x_2963_; 
v___x_2962_ = lean_uint64_shift_right(v___y_2956_, v___y_2954_);
v___x_2963_ = lean_uint64_dec_eq(v___x_2962_, v___y_2960_);
if (v___x_2963_ == 0)
{
uint64_t v___x_2964_; 
v___x_2964_ = lean_uint64_add(v___y_2957_, v___y_2954_);
v___y_2938_ = v___y_2951_;
v___y_2939_ = v___y_2952_;
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___y_2961_;
v___y_2942_ = v___y_2955_;
v___y_2943_ = v___y_2958_;
v___y_2944_ = v___y_2959_;
v___y_2945_ = v___y_2960_;
v___y_2946_ = v___x_2964_;
goto v___jp_2937_;
}
else
{
v___y_2938_ = v___y_2951_;
v___y_2939_ = v___y_2952_;
v___y_2940_ = v___y_2953_;
v___y_2941_ = v___y_2961_;
v___y_2942_ = v___y_2955_;
v___y_2943_ = v___y_2958_;
v___y_2944_ = v___y_2959_;
v___y_2945_ = v___y_2960_;
v___y_2946_ = v___y_2957_;
goto v___jp_2937_;
}
}
v___jp_2965_:
{
uint64_t v___x_2975_; uint64_t v___x_2976_; uint8_t v___x_2977_; 
v___x_2975_ = 4ULL;
v___x_2976_ = lean_uint64_shift_right(v___y_2970_, v___x_2975_);
v___x_2977_ = lean_uint64_dec_eq(v___x_2976_, v___y_2973_);
if (v___x_2977_ == 0)
{
v___y_2951_ = v___y_2966_;
v___y_2952_ = v___y_2967_;
v___y_2953_ = v___y_2968_;
v___y_2954_ = v___x_2975_;
v___y_2955_ = v___y_2969_;
v___y_2956_ = v___y_2970_;
v___y_2957_ = v___y_2974_;
v___y_2958_ = v___y_2971_;
v___y_2959_ = v___y_2972_;
v___y_2960_ = v___y_2973_;
v___y_2961_ = v___x_2976_;
goto v___jp_2950_;
}
else
{
v___y_2951_ = v___y_2966_;
v___y_2952_ = v___y_2967_;
v___y_2953_ = v___y_2968_;
v___y_2954_ = v___x_2975_;
v___y_2955_ = v___y_2969_;
v___y_2956_ = v___y_2970_;
v___y_2957_ = v___y_2974_;
v___y_2958_ = v___y_2971_;
v___y_2959_ = v___y_2972_;
v___y_2960_ = v___y_2973_;
v___y_2961_ = v___y_2970_;
goto v___jp_2950_;
}
}
v___jp_2978_:
{
uint64_t v___x_2990_; uint8_t v___x_2991_; 
v___x_2990_ = lean_uint64_shift_right(v___y_2980_, v___y_2984_);
v___x_2991_ = lean_uint64_dec_eq(v___x_2990_, v___y_2988_);
if (v___x_2991_ == 0)
{
uint64_t v___x_2992_; 
v___x_2992_ = lean_uint64_add(v___y_2982_, v___y_2984_);
v___y_2966_ = v___y_2979_;
v___y_2967_ = v___y_2981_;
v___y_2968_ = v___y_2983_;
v___y_2969_ = v___y_2985_;
v___y_2970_ = v___y_2989_;
v___y_2971_ = v___y_2986_;
v___y_2972_ = v___y_2987_;
v___y_2973_ = v___y_2988_;
v___y_2974_ = v___x_2992_;
goto v___jp_2965_;
}
else
{
v___y_2966_ = v___y_2979_;
v___y_2967_ = v___y_2981_;
v___y_2968_ = v___y_2983_;
v___y_2969_ = v___y_2985_;
v___y_2970_ = v___y_2989_;
v___y_2971_ = v___y_2986_;
v___y_2972_ = v___y_2987_;
v___y_2973_ = v___y_2988_;
v___y_2974_ = v___y_2982_;
goto v___jp_2965_;
}
}
v___jp_2993_:
{
uint64_t v___x_3003_; uint64_t v___x_3004_; uint8_t v___x_3005_; 
v___x_3003_ = 8ULL;
v___x_3004_ = lean_uint64_shift_right(v___y_2996_, v___x_3003_);
v___x_3005_ = lean_uint64_dec_eq(v___x_3004_, v___y_3001_);
if (v___x_3005_ == 0)
{
v___y_2979_ = v___y_2994_;
v___y_2980_ = v___y_2996_;
v___y_2981_ = v___y_2995_;
v___y_2982_ = v___y_3002_;
v___y_2983_ = v___y_2997_;
v___y_2984_ = v___x_3003_;
v___y_2985_ = v___y_2998_;
v___y_2986_ = v___y_2999_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___x_3004_;
goto v___jp_2978_;
}
else
{
v___y_2979_ = v___y_2994_;
v___y_2980_ = v___y_2996_;
v___y_2981_ = v___y_2995_;
v___y_2982_ = v___y_3002_;
v___y_2983_ = v___y_2997_;
v___y_2984_ = v___x_3003_;
v___y_2985_ = v___y_2998_;
v___y_2986_ = v___y_2999_;
v___y_2987_ = v___y_3000_;
v___y_2988_ = v___y_3001_;
v___y_2989_ = v___y_2996_;
goto v___jp_2978_;
}
}
v___jp_3006_:
{
uint64_t v___x_3018_; uint8_t v___x_3019_; 
v___x_3018_ = lean_uint64_shift_right(v___y_3012_, v___y_3010_);
v___x_3019_ = lean_uint64_dec_eq(v___x_3018_, v___y_3016_);
if (v___x_3019_ == 0)
{
uint64_t v___x_3020_; 
v___x_3020_ = lean_uint64_add(v___y_3007_, v___y_3010_);
v___y_2994_ = v___y_3008_;
v___y_2995_ = v___y_3009_;
v___y_2996_ = v___y_3017_;
v___y_2997_ = v___y_3011_;
v___y_2998_ = v___y_3013_;
v___y_2999_ = v___y_3014_;
v___y_3000_ = v___y_3015_;
v___y_3001_ = v___y_3016_;
v___y_3002_ = v___x_3020_;
goto v___jp_2993_;
}
else
{
v___y_2994_ = v___y_3008_;
v___y_2995_ = v___y_3009_;
v___y_2996_ = v___y_3017_;
v___y_2997_ = v___y_3011_;
v___y_2998_ = v___y_3013_;
v___y_2999_ = v___y_3014_;
v___y_3000_ = v___y_3015_;
v___y_3001_ = v___y_3016_;
v___y_3002_ = v___y_3007_;
goto v___jp_2993_;
}
}
v___jp_3021_:
{
uint64_t v___x_3031_; uint64_t v___x_3032_; uint8_t v___x_3033_; 
v___x_3031_ = 16ULL;
v___x_3032_ = lean_uint64_shift_right(v___y_3026_, v___x_3031_);
v___x_3033_ = lean_uint64_dec_eq(v___x_3032_, v___y_3029_);
if (v___x_3033_ == 0)
{
v___y_3007_ = v___y_3030_;
v___y_3008_ = v___y_3022_;
v___y_3009_ = v___y_3023_;
v___y_3010_ = v___x_3031_;
v___y_3011_ = v___y_3024_;
v___y_3012_ = v___y_3026_;
v___y_3013_ = v___y_3025_;
v___y_3014_ = v___y_3027_;
v___y_3015_ = v___y_3028_;
v___y_3016_ = v___y_3029_;
v___y_3017_ = v___x_3032_;
goto v___jp_3006_;
}
else
{
v___y_3007_ = v___y_3030_;
v___y_3008_ = v___y_3022_;
v___y_3009_ = v___y_3023_;
v___y_3010_ = v___x_3031_;
v___y_3011_ = v___y_3024_;
v___y_3012_ = v___y_3026_;
v___y_3013_ = v___y_3025_;
v___y_3014_ = v___y_3027_;
v___y_3015_ = v___y_3028_;
v___y_3016_ = v___y_3029_;
v___y_3017_ = v___y_3026_;
goto v___jp_3006_;
}
}
v___jp_3034_:
{
uint64_t v___x_3044_; uint8_t v___x_3045_; 
v___x_3044_ = lean_uint64_shift_right(v___y_3037_, v___y_3041_);
v___x_3045_ = lean_uint64_dec_eq(v___x_3044_, v___y_3042_);
if (v___x_3045_ == 0)
{
v___y_3022_ = v___y_3035_;
v___y_3023_ = v___y_3036_;
v___y_3024_ = v___y_3037_;
v___y_3025_ = v___y_3038_;
v___y_3026_ = v___y_3043_;
v___y_3027_ = v___y_3039_;
v___y_3028_ = v___y_3040_;
v___y_3029_ = v___y_3042_;
v___y_3030_ = v___y_3041_;
goto v___jp_3021_;
}
else
{
v___y_3022_ = v___y_3035_;
v___y_3023_ = v___y_3036_;
v___y_3024_ = v___y_3037_;
v___y_3025_ = v___y_3038_;
v___y_3026_ = v___y_3043_;
v___y_3027_ = v___y_3039_;
v___y_3028_ = v___y_3040_;
v___y_3029_ = v___y_3042_;
v___y_3030_ = v___y_3042_;
goto v___jp_3021_;
}
}
v___jp_3046_:
{
uint64_t v___x_3055_; uint64_t v___x_3056_; uint8_t v___x_3057_; 
v___x_3055_ = lean_uint64_mul(v___y_3049_, v___y_3053_);
v___x_3056_ = 0ULL;
v___x_3057_ = lean_uint64_dec_eq(v___x_3055_, v___x_3056_);
if (v___x_3057_ == 0)
{
uint64_t v___x_3058_; uint64_t v___x_3059_; uint64_t v___x_3060_; uint8_t v___x_3061_; 
v___x_3058_ = lean_uint64_add(v___y_3051_, v___y_3054_);
v___x_3059_ = 32ULL;
v___x_3060_ = lean_uint64_shift_right(v___x_3055_, v___x_3059_);
v___x_3061_ = lean_uint64_dec_eq(v___x_3060_, v___x_3056_);
if (v___x_3061_ == 0)
{
v___y_3035_ = v___y_3047_;
v___y_3036_ = v___y_3048_;
v___y_3037_ = v___x_3055_;
v___y_3038_ = v___x_3058_;
v___y_3039_ = v___y_3050_;
v___y_3040_ = v___y_3052_;
v___y_3041_ = v___x_3059_;
v___y_3042_ = v___x_3056_;
v___y_3043_ = v___x_3060_;
goto v___jp_3034_;
}
else
{
v___y_3035_ = v___y_3047_;
v___y_3036_ = v___y_3048_;
v___y_3037_ = v___x_3055_;
v___y_3038_ = v___x_3058_;
v___y_3039_ = v___y_3050_;
v___y_3040_ = v___y_3052_;
v___y_3041_ = v___x_3059_;
v___y_3042_ = v___x_3056_;
v___y_3043_ = v___x_3055_;
goto v___jp_3034_;
}
}
else
{
if (v___y_3052_ == 0)
{
uint32_t v___x_3062_; 
v___x_3062_ = 0;
return v___x_3062_;
}
else
{
uint32_t v___x_3063_; 
v___x_3063_ = 2147483648;
return v___x_3063_;
}
}
}
v___jp_3064_:
{
uint64_t v___x_3073_; uint64_t v___x_3074_; uint8_t v___x_3075_; 
v___x_3073_ = lean_uint32_to_uint64(v___y_3068_);
v___x_3074_ = 0ULL;
v___x_3075_ = lean_uint64_dec_eq(v___x_3073_, v___x_3074_);
if (v___x_3075_ == 0)
{
uint64_t v___x_3076_; uint64_t v___x_3077_; 
v___x_3076_ = 1ULL;
v___x_3077_ = lean_uint64_sub(v___x_3073_, v___x_3076_);
v___y_3047_ = v___y_3065_;
v___y_3048_ = v___y_3067_;
v___y_3049_ = v___y_3066_;
v___y_3050_ = v___y_3069_;
v___y_3051_ = v___y_3072_;
v___y_3052_ = v___y_3070_;
v___y_3053_ = v___y_3071_;
v___y_3054_ = v___x_3077_;
goto v___jp_3046_;
}
else
{
v___y_3047_ = v___y_3065_;
v___y_3048_ = v___y_3067_;
v___y_3049_ = v___y_3066_;
v___y_3050_ = v___y_3069_;
v___y_3051_ = v___y_3072_;
v___y_3052_ = v___y_3070_;
v___y_3053_ = v___y_3071_;
v___y_3054_ = v___x_3074_;
goto v___jp_3046_;
}
}
v___jp_3078_:
{
uint64_t v___x_3087_; uint64_t v___x_3088_; uint8_t v___x_3089_; 
v___x_3087_ = lean_uint32_to_uint64(v___y_3082_);
v___x_3088_ = 0ULL;
v___x_3089_ = lean_uint64_dec_eq(v___x_3087_, v___x_3088_);
if (v___x_3089_ == 0)
{
uint64_t v___x_3090_; uint64_t v___x_3091_; 
v___x_3090_ = 1ULL;
v___x_3091_ = lean_uint64_sub(v___x_3087_, v___x_3090_);
v___y_3065_ = v___y_3079_;
v___y_3066_ = v___y_3081_;
v___y_3067_ = v___y_3080_;
v___y_3068_ = v___y_3083_;
v___y_3069_ = v___y_3084_;
v___y_3070_ = v___y_3085_;
v___y_3071_ = v___y_3086_;
v___y_3072_ = v___x_3091_;
goto v___jp_3064_;
}
else
{
v___y_3065_ = v___y_3079_;
v___y_3066_ = v___y_3081_;
v___y_3067_ = v___y_3080_;
v___y_3068_ = v___y_3083_;
v___y_3069_ = v___y_3084_;
v___y_3070_ = v___y_3085_;
v___y_3071_ = v___y_3086_;
v___y_3072_ = v___x_3088_;
goto v___jp_3064_;
}
}
v___jp_3092_:
{
uint32_t v___x_3101_; uint8_t v___x_3102_; 
v___x_3101_ = 0;
v___x_3102_ = lean_uint32_dec_eq(v___y_3096_, v___x_3101_);
if (v___x_3102_ == 0)
{
uint64_t v___x_3103_; uint64_t v___x_3104_; uint64_t v___x_3105_; 
v___x_3103_ = lean_uint32_to_uint64(v___y_3099_);
v___x_3104_ = 8388608ULL;
v___x_3105_ = lean_uint64_lor(v___x_3103_, v___x_3104_);
v___y_3079_ = v___y_3093_;
v___y_3080_ = v___y_3094_;
v___y_3081_ = v___y_3100_;
v___y_3082_ = v___y_3095_;
v___y_3083_ = v___y_3096_;
v___y_3084_ = v___y_3097_;
v___y_3085_ = v___y_3098_;
v___y_3086_ = v___x_3105_;
goto v___jp_3078_;
}
else
{
uint64_t v___x_3106_; 
v___x_3106_ = lean_uint32_to_uint64(v___y_3099_);
v___y_3079_ = v___y_3093_;
v___y_3080_ = v___y_3094_;
v___y_3081_ = v___y_3100_;
v___y_3082_ = v___y_3095_;
v___y_3083_ = v___y_3096_;
v___y_3084_ = v___y_3097_;
v___y_3085_ = v___y_3098_;
v___y_3086_ = v___x_3106_;
goto v___jp_3078_;
}
}
v___jp_3107_:
{
uint32_t v___x_3113_; uint32_t v_xFraction_3114_; uint32_t v_yFraction_3115_; uint32_t v___x_3116_; uint8_t v___x_3117_; 
v___x_3113_ = 8388607;
v_xFraction_3114_ = lean_uint32_land(v_x_2756_, v___x_3113_);
v_yFraction_3115_ = lean_uint32_land(v_y_2757_, v___x_3113_);
v___x_3116_ = 0;
v___x_3117_ = lean_uint32_dec_eq(v___y_3109_, v___x_3116_);
if (v___x_3117_ == 0)
{
uint64_t v___x_3118_; uint64_t v___x_3119_; uint64_t v___x_3120_; 
v___x_3118_ = lean_uint32_to_uint64(v_xFraction_3114_);
v___x_3119_ = 8388608ULL;
v___x_3120_ = lean_uint64_lor(v___x_3118_, v___x_3119_);
v___y_3093_ = v___y_3108_;
v___y_3094_ = v___x_3113_;
v___y_3095_ = v___y_3109_;
v___y_3096_ = v___y_3110_;
v___y_3097_ = v___y_3111_;
v___y_3098_ = v___y_3112_;
v___y_3099_ = v_yFraction_3115_;
v___y_3100_ = v___x_3120_;
goto v___jp_3092_;
}
else
{
uint64_t v___x_3121_; 
v___x_3121_ = lean_uint32_to_uint64(v_xFraction_3114_);
v___y_3093_ = v___y_3108_;
v___y_3094_ = v___x_3113_;
v___y_3095_ = v___y_3109_;
v___y_3096_ = v___y_3110_;
v___y_3097_ = v___y_3111_;
v___y_3098_ = v___y_3112_;
v___y_3099_ = v_yFraction_3115_;
v___y_3100_ = v___x_3121_;
goto v___jp_3092_;
}
}
v___jp_3122_:
{
uint8_t v___x_3127_; 
v___x_3127_ = 1;
v___y_3108_ = v___y_3123_;
v___y_3109_ = v___y_3124_;
v___y_3110_ = v___y_3125_;
v___y_3111_ = v___y_3126_;
v___y_3112_ = v___x_3127_;
goto v___jp_3107_;
}
v___jp_3128_:
{
if (v___y_3133_ == 0)
{
if (v___y_3135_ == 0)
{
v___y_3108_ = v___y_3129_;
v___y_3109_ = v___y_3131_;
v___y_3110_ = v___y_3132_;
v___y_3111_ = v___y_3134_;
v___y_3112_ = v___y_3130_;
goto v___jp_3107_;
}
else
{
v___y_3123_ = v___y_3129_;
v___y_3124_ = v___y_3131_;
v___y_3125_ = v___y_3132_;
v___y_3126_ = v___y_3134_;
goto v___jp_3122_;
}
}
else
{
if (v___y_3135_ == 0)
{
v___y_3123_ = v___y_3129_;
v___y_3124_ = v___y_3131_;
v___y_3125_ = v___y_3132_;
v___y_3126_ = v___y_3134_;
goto v___jp_3122_;
}
else
{
v___y_3108_ = v___y_3129_;
v___y_3109_ = v___y_3131_;
v___y_3110_ = v___y_3132_;
v___y_3111_ = v___y_3134_;
v___y_3112_ = v___y_3130_;
goto v___jp_3107_;
}
}
}
v___jp_3136_:
{
uint32_t v___x_3143_; uint32_t v___x_3144_; uint32_t v___x_3145_; uint8_t v___x_3146_; 
v___x_3143_ = 2147483648;
v___x_3144_ = lean_uint32_land(v_y_2757_, v___x_3143_);
v___x_3145_ = 0;
v___x_3146_ = lean_uint32_dec_eq(v___x_3144_, v___x_3145_);
if (v___x_3146_ == 0)
{
uint8_t v___x_3147_; 
v___x_3147_ = 1;
v___y_3129_ = v___y_3137_;
v___y_3130_ = v___y_3138_;
v___y_3131_ = v___y_3139_;
v___y_3132_ = v___y_3140_;
v___y_3133_ = v___y_3142_;
v___y_3134_ = v___y_3141_;
v___y_3135_ = v___x_3147_;
goto v___jp_3128_;
}
else
{
v___y_3129_ = v___y_3137_;
v___y_3130_ = v___y_3138_;
v___y_3131_ = v___y_3139_;
v___y_3132_ = v___y_3140_;
v___y_3133_ = v___y_3142_;
v___y_3134_ = v___y_3141_;
v___y_3135_ = v___y_3138_;
goto v___jp_3128_;
}
}
v___jp_3148_:
{
if (v___y_3149_ == 0)
{
uint32_t v___x_3150_; uint32_t v___x_3151_; uint32_t v___x_3152_; uint32_t v_xExponent_3153_; uint32_t v___x_3154_; uint32_t v_yExponent_3155_; uint32_t v___x_3156_; uint32_t v___x_3157_; uint32_t v___x_3158_; uint8_t v___x_3159_; 
v___x_3150_ = 23;
v___x_3151_ = lean_uint32_shift_right(v_x_2756_, v___x_3150_);
v___x_3152_ = 255;
v_xExponent_3153_ = lean_uint32_land(v___x_3151_, v___x_3152_);
v___x_3154_ = lean_uint32_shift_right(v_y_2757_, v___x_3150_);
v_yExponent_3155_ = lean_uint32_land(v___x_3154_, v___x_3152_);
v___x_3156_ = 2147483648;
v___x_3157_ = lean_uint32_land(v_x_2756_, v___x_3156_);
v___x_3158_ = 0;
v___x_3159_ = lean_uint32_dec_eq(v___x_3157_, v___x_3158_);
if (v___x_3159_ == 0)
{
uint8_t v___x_3160_; 
v___x_3160_ = 1;
v___y_3137_ = v___x_3152_;
v___y_3138_ = v___y_3149_;
v___y_3139_ = v_xExponent_3153_;
v___y_3140_ = v_yExponent_3155_;
v___y_3141_ = v___x_3150_;
v___y_3142_ = v___x_3160_;
goto v___jp_3136_;
}
else
{
v___y_3137_ = v___x_3152_;
v___y_3138_ = v___y_3149_;
v___y_3139_ = v_xExponent_3153_;
v___y_3140_ = v_yExponent_3155_;
v___y_3141_ = v___x_3150_;
v___y_3142_ = v___y_3149_;
goto v___jp_3136_;
}
}
else
{
lean_object* v___x_3161_; lean_object* v___x_3162_; lean_object* v___x_3163_; uint32_t v___x_3164_; 
v___x_3161_ = lean_uint32_to_nat(v_x_2756_);
v___x_3162_ = lean_uint32_to_nat(v_y_2757_);
v___x_3163_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3161_, v___x_3162_);
v___x_3164_ = lean_uint32_of_nat(v___x_3163_);
lean_dec(v___x_3163_);
return v___x_3164_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mul___boxed(lean_object* v_x_3171_, lean_object* v_y_3172_){
_start:
{
uint32_t v_x_boxed_3173_; uint32_t v_y_boxed_3174_; uint32_t v_res_3175_; lean_object* v_r_3176_; 
v_x_boxed_3173_ = lean_unbox_uint32(v_x_3171_);
lean_dec(v_x_3171_);
v_y_boxed_3174_ = lean_unbox_uint32(v_y_3172_);
lean_dec(v_y_3172_);
v_res_3175_ = lp_competition_Submission_FastMul_mul(v_x_boxed_3173_, v_y_boxed_3174_);
v_r_3176_ = lean_box_uint32(v_res_3175_);
return v_r_3176_;
}
}
static uint8_t _init_lp_competition_Submission_FastMul_Plan(void){
_start:
{
uint8_t v___x_3178_; 
v___x_3178_ = 2;
return v___x_3178_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec(uint32_t v_z_3179_){
_start:
{
lean_object* v___x_3180_; 
v___x_3180_ = lean_uint32_to_nat(v_z_3179_);
return v___x_3180_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec___boxed(lean_object* v_z_3181_){
_start:
{
uint32_t v_z_boxed_3182_; lean_object* v_res_3183_; 
v_z_boxed_3182_ = lean_unbox_uint32(v_z_3181_);
lean_dec(v_z_3181_);
v_res_3183_ = lp_competition_Submission_FastMul_dec(v_z_boxed_3182_);
return v_res_3183_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t v_x_3184_, uint32_t v_y_3185_){
_start:
{
uint32_t v___x_3186_; 
v___x_3186_ = lp_competition_Submission_TunedAdd_add(v_x_3184_, v_y_3185_);
return v___x_3186_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object* v_x_3187_, lean_object* v_y_3188_){
_start:
{
uint32_t v_x_boxed_3189_; uint32_t v_y_boxed_3190_; uint32_t v_res_3191_; lean_object* v_r_3192_; 
v_x_boxed_3189_ = lean_unbox_uint32(v_x_3187_);
lean_dec(v_x_3187_);
v_y_boxed_3190_ = lean_unbox_uint32(v_y_3188_);
lean_dec(v_y_3188_);
v_res_3191_ = lp_competition_Submission_add(v_x_boxed_3189_, v_y_boxed_3190_);
v_r_3192_ = lean_box_uint32(v_res_3191_);
return v_r_3192_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t v_x_3193_, uint32_t v_y_3194_){
_start:
{
uint32_t v___x_3195_; 
v___x_3195_ = lp_competition_Submission_FastMul_mul(v_x_3193_, v_y_3194_);
return v___x_3195_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object* v_x_3196_, lean_object* v_y_3197_){
_start:
{
uint32_t v_x_boxed_3198_; uint32_t v_y_boxed_3199_; uint32_t v_res_3200_; lean_object* v_r_3201_; 
v_x_boxed_3198_ = lean_unbox_uint32(v_x_3196_);
lean_dec(v_x_3196_);
v_y_boxed_3199_ = lean_unbox_uint32(v_y_3197_);
lean_dec(v_y_3197_);
v_res_3200_ = lp_competition_Submission_mul(v_x_boxed_3198_, v_y_boxed_3199_);
v_r_3201_ = lean_box_uint32(v_res_3200_);
return v_r_3201_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(lean_object* v_as_3202_, size_t v_i_3203_, size_t v_stop_3204_, uint32_t v_b_3205_){
_start:
{
uint8_t v___x_3206_; 
v___x_3206_ = lean_usize_dec_eq(v_i_3203_, v_stop_3204_);
if (v___x_3206_ == 0)
{
lean_object* v___x_3207_; uint32_t v___x_3208_; uint32_t v___x_3209_; size_t v___x_3210_; size_t v___x_3211_; 
v___x_3207_ = lean_array_uget_borrowed(v_as_3202_, v_i_3203_);
v___x_3208_ = lean_unbox_uint32(v___x_3207_);
v___x_3209_ = lp_competition_Submission_TunedAdd_add(v_b_3205_, v___x_3208_);
v___x_3210_ = ((size_t)1ULL);
v___x_3211_ = lean_usize_add(v_i_3203_, v___x_3210_);
v_i_3203_ = v___x_3211_;
v_b_3205_ = v___x_3209_;
goto _start;
}
else
{
return v_b_3205_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0___boxed(lean_object* v_as_3213_, lean_object* v_i_3214_, lean_object* v_stop_3215_, lean_object* v_b_3216_){
_start:
{
size_t v_i_boxed_3217_; size_t v_stop_boxed_3218_; uint32_t v_b_boxed_3219_; uint32_t v_res_3220_; lean_object* v_r_3221_; 
v_i_boxed_3217_ = lean_unbox_usize(v_i_3214_);
lean_dec(v_i_3214_);
v_stop_boxed_3218_ = lean_unbox_usize(v_stop_3215_);
lean_dec(v_stop_3215_);
v_b_boxed_3219_ = lean_unbox_uint32(v_b_3216_);
lean_dec(v_b_3216_);
v_res_3220_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(v_as_3213_, v_i_boxed_3217_, v_stop_boxed_3218_, v_b_boxed_3219_);
lean_dec_ref(v_as_3213_);
v_r_3221_ = lean_box_uint32(v_res_3220_);
return v_r_3221_;
}
}
static lean_object* _init_lp_competition_Submission_sum___redArg___closed__0(void){
_start:
{
lean_object* v___x_3222_; lean_object* v___x_3223_; lean_object* v___x_3224_; 
v___x_3222_ = lean_unsigned_to_nat(0u);
v___x_3223_ = lean_unsigned_to_nat(32u);
v___x_3224_ = l_BitVec_ofNat(v___x_3223_, v___x_3222_);
return v___x_3224_;
}
}
static uint32_t _init_lp_competition_Submission_sum___redArg___closed__1(void){
_start:
{
lean_object* v___x_3225_; uint32_t v___x_3226_; 
v___x_3225_ = lean_obj_once(&lp_competition_Submission_sum___redArg___closed__0, &lp_competition_Submission_sum___redArg___closed__0_once, _init_lp_competition_Submission_sum___redArg___closed__0);
v___x_3226_ = lean_uint32_of_nat(v___x_3225_);
return v___x_3226_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum___redArg(lean_object* v_x_3227_){
_start:
{
lean_object* v___x_3228_; uint32_t v___x_3229_; lean_object* v___x_3230_; uint8_t v___x_3231_; 
v___x_3228_ = lean_unsigned_to_nat(0u);
v___x_3229_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_3230_ = lean_array_get_size(v_x_3227_);
v___x_3231_ = lean_nat_dec_lt(v___x_3228_, v___x_3230_);
if (v___x_3231_ == 0)
{
return v___x_3229_;
}
else
{
uint8_t v___x_3232_; 
v___x_3232_ = lean_nat_dec_le(v___x_3230_, v___x_3230_);
if (v___x_3232_ == 0)
{
if (v___x_3231_ == 0)
{
return v___x_3229_;
}
else
{
size_t v___x_3233_; size_t v___x_3234_; uint32_t v___x_3235_; 
v___x_3233_ = ((size_t)0ULL);
v___x_3234_ = lean_usize_of_nat(v___x_3230_);
v___x_3235_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(v_x_3227_, v___x_3233_, v___x_3234_, v___x_3229_);
return v___x_3235_;
}
}
else
{
size_t v___x_3236_; size_t v___x_3237_; uint32_t v___x_3238_; 
v___x_3236_ = ((size_t)0ULL);
v___x_3237_ = lean_usize_of_nat(v___x_3230_);
v___x_3238_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(v_x_3227_, v___x_3236_, v___x_3237_, v___x_3229_);
return v___x_3238_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___boxed(lean_object* v_x_3239_){
_start:
{
uint32_t v_res_3240_; lean_object* v_r_3241_; 
v_res_3240_ = lp_competition_Submission_sum___redArg(v_x_3239_);
lean_dec_ref(v_x_3239_);
v_r_3241_ = lean_box_uint32(v_res_3240_);
return v_r_3241_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object* v_n_3242_, lean_object* v_x_3243_){
_start:
{
uint32_t v___x_3244_; 
v___x_3244_ = lp_competition_Submission_sum___redArg(v_x_3243_);
return v___x_3244_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object* v_n_3245_, lean_object* v_x_3246_){
_start:
{
uint32_t v_res_3247_; lean_object* v_r_3248_; 
v_res_3247_ = lp_competition_Submission_sum(v_n_3245_, v_x_3246_);
lean_dec_ref(v_x_3246_);
lean_dec(v_n_3245_);
v_r_3248_ = lean_box_uint32(v_res_3247_);
return v_r_3248_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(lean_object* v_A_3249_, lean_object* v_fst_3250_, lean_object* v_m_3251_, lean_object* v_fst_3252_, lean_object* v_n_3253_, lean_object* v_B_3254_, lean_object* v_p_3255_, lean_object* v_snd_3256_, lean_object* v_n_3257_, uint32_t v_x_3258_, lean_object* v_i_3259_){
_start:
{
uint32_t v___y_3261_; uint32_t v___y_3262_; uint8_t v___x_3268_; 
v___x_3268_ = lean_nat_dec_lt(v_i_3259_, v_n_3257_);
if (v___x_3268_ == 0)
{
lean_dec(v_i_3259_);
return v_x_3258_;
}
else
{
lean_object* v___x_3269_; lean_object* v___x_3270_; lean_object* v___x_3271_; lean_object* v___x_3272_; uint32_t v___x_3273_; uint32_t v___y_3275_; lean_object* v___x_3284_; uint8_t v___x_3285_; 
v___x_3269_ = lean_nat_mul(v_fst_3250_, v_m_3251_);
v___x_3270_ = lean_nat_add(v___x_3269_, v_fst_3252_);
lean_dec(v___x_3269_);
v___x_3271_ = lean_nat_mul(v___x_3270_, v_n_3253_);
lean_dec(v___x_3270_);
v___x_3272_ = lean_nat_add(v___x_3271_, v_i_3259_);
lean_dec(v___x_3271_);
v___x_3273_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_3284_ = lean_array_get_size(v_A_3249_);
v___x_3285_ = lean_nat_dec_lt(v___x_3272_, v___x_3284_);
if (v___x_3285_ == 0)
{
lean_dec(v___x_3272_);
v___y_3275_ = v___x_3273_;
goto v___jp_3274_;
}
else
{
lean_object* v___x_3286_; uint32_t v___x_3287_; 
v___x_3286_ = lean_array_fget_borrowed(v_A_3249_, v___x_3272_);
lean_dec(v___x_3272_);
v___x_3287_ = lean_unbox_uint32(v___x_3286_);
v___y_3275_ = v___x_3287_;
goto v___jp_3274_;
}
v___jp_3274_:
{
lean_object* v___x_3276_; lean_object* v___x_3277_; lean_object* v___x_3278_; lean_object* v___x_3279_; lean_object* v___x_3280_; uint8_t v___x_3281_; 
v___x_3276_ = lean_nat_mul(v_fst_3250_, v_n_3253_);
v___x_3277_ = lean_nat_add(v___x_3276_, v_i_3259_);
lean_dec(v___x_3276_);
v___x_3278_ = lean_nat_mul(v___x_3277_, v_p_3255_);
lean_dec(v___x_3277_);
v___x_3279_ = lean_nat_add(v___x_3278_, v_snd_3256_);
lean_dec(v___x_3278_);
v___x_3280_ = lean_array_get_size(v_B_3254_);
v___x_3281_ = lean_nat_dec_lt(v___x_3279_, v___x_3280_);
if (v___x_3281_ == 0)
{
lean_dec(v___x_3279_);
v___y_3261_ = v___y_3275_;
v___y_3262_ = v___x_3273_;
goto v___jp_3260_;
}
else
{
lean_object* v___x_3282_; uint32_t v___x_3283_; 
v___x_3282_ = lean_array_fget_borrowed(v_B_3254_, v___x_3279_);
lean_dec(v___x_3279_);
v___x_3283_ = lean_unbox_uint32(v___x_3282_);
v___y_3261_ = v___y_3275_;
v___y_3262_ = v___x_3283_;
goto v___jp_3260_;
}
}
}
v___jp_3260_:
{
uint32_t v___x_3263_; uint32_t v___x_3264_; lean_object* v___x_3265_; lean_object* v___x_3266_; 
v___x_3263_ = lp_competition_Submission_FastMul_mul(v___y_3261_, v___y_3262_);
v___x_3264_ = lp_competition_Submission_TunedAdd_add(v_x_3258_, v___x_3263_);
v___x_3265_ = lean_unsigned_to_nat(1u);
v___x_3266_ = lean_nat_add(v_i_3259_, v___x_3265_);
lean_dec(v_i_3259_);
v_x_3258_ = v___x_3264_;
v_i_3259_ = v___x_3266_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0___boxed(lean_object* v_A_3288_, lean_object* v_fst_3289_, lean_object* v_m_3290_, lean_object* v_fst_3291_, lean_object* v_n_3292_, lean_object* v_B_3293_, lean_object* v_p_3294_, lean_object* v_snd_3295_, lean_object* v_n_3296_, lean_object* v_x_3297_, lean_object* v_i_3298_){
_start:
{
uint32_t v_x_boxed_3299_; uint32_t v_res_3300_; lean_object* v_r_3301_; 
v_x_boxed_3299_ = lean_unbox_uint32(v_x_3297_);
lean_dec(v_x_3297_);
v_res_3300_ = lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(v_A_3288_, v_fst_3289_, v_m_3290_, v_fst_3291_, v_n_3292_, v_B_3293_, v_p_3294_, v_snd_3295_, v_n_3296_, v_x_boxed_3299_, v_i_3298_);
lean_dec(v_n_3296_);
lean_dec(v_snd_3295_);
lean_dec(v_p_3294_);
lean_dec_ref(v_B_3293_);
lean_dec(v_n_3292_);
lean_dec(v_fst_3291_);
lean_dec(v_m_3290_);
lean_dec(v_fst_3289_);
lean_dec_ref(v_A_3288_);
v_r_3301_ = lean_box_uint32(v_res_3300_);
return v_r_3301_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceBmm___lam__0(lean_object* v_m_3302_, lean_object* v_p_3303_, lean_object* v_A_3304_, lean_object* v_n_3305_, lean_object* v_B_3306_, lean_object* v_q_3307_){
_start:
{
lean_object* v___x_3308_; lean_object* v_snd_3309_; lean_object* v_fst_3310_; lean_object* v_fst_3311_; lean_object* v_snd_3312_; lean_object* v___x_3313_; uint32_t v___x_3314_; uint32_t v___x_3315_; 
v___x_3308_ = lp_competition_Competition_bmmDecodeC(v_m_3302_, v_p_3303_, v_q_3307_);
v_snd_3309_ = lean_ctor_get(v___x_3308_, 1);
lean_inc(v_snd_3309_);
v_fst_3310_ = lean_ctor_get(v___x_3308_, 0);
lean_inc(v_fst_3310_);
lean_dec_ref(v___x_3308_);
v_fst_3311_ = lean_ctor_get(v_snd_3309_, 0);
lean_inc(v_fst_3311_);
v_snd_3312_ = lean_ctor_get(v_snd_3309_, 1);
lean_inc(v_snd_3312_);
lean_dec(v_snd_3309_);
v___x_3313_ = lean_unsigned_to_nat(0u);
v___x_3314_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_3315_ = lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(v_A_3304_, v_fst_3310_, v_m_3302_, v_fst_3311_, v_n_3305_, v_B_3306_, v_p_3303_, v_snd_3312_, v_n_3305_, v___x_3314_, v___x_3313_);
lean_dec(v_snd_3312_);
lean_dec(v_fst_3311_);
lean_dec(v_fst_3310_);
return v___x_3315_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___lam__0___boxed(lean_object* v_m_3316_, lean_object* v_p_3317_, lean_object* v_A_3318_, lean_object* v_n_3319_, lean_object* v_B_3320_, lean_object* v_q_3321_){
_start:
{
uint32_t v_res_3322_; lean_object* v_r_3323_; 
v_res_3322_ = lp_competition_Submission_referenceBmm___lam__0(v_m_3316_, v_p_3317_, v_A_3318_, v_n_3319_, v_B_3320_, v_q_3321_);
lean_dec(v_q_3321_);
lean_dec_ref(v_B_3320_);
lean_dec(v_n_3319_);
lean_dec_ref(v_A_3318_);
lean_dec(v_p_3317_);
lean_dec(v_m_3316_);
v_r_3323_ = lean_box_uint32(v_res_3322_);
return v_r_3323_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm(lean_object* v_batch_3324_, lean_object* v_m_3325_, lean_object* v_n_3326_, lean_object* v_p_3327_, lean_object* v_A_3328_, lean_object* v_B_3329_){
_start:
{
lean_object* v___f_3330_; lean_object* v___x_3331_; lean_object* v___x_3332_; lean_object* v___x_3333_; 
lean_inc(v_p_3327_);
lean_inc(v_m_3325_);
v___f_3330_ = lean_alloc_closure((void*)(lp_competition_Submission_referenceBmm___lam__0___boxed), 6, 5);
lean_closure_set(v___f_3330_, 0, v_m_3325_);
lean_closure_set(v___f_3330_, 1, v_p_3327_);
lean_closure_set(v___f_3330_, 2, v_A_3328_);
lean_closure_set(v___f_3330_, 3, v_n_3326_);
lean_closure_set(v___f_3330_, 4, v_B_3329_);
v___x_3331_ = lean_nat_mul(v_batch_3324_, v_m_3325_);
lean_dec(v_m_3325_);
v___x_3332_ = lean_nat_mul(v___x_3331_, v_p_3327_);
lean_dec(v_p_3327_);
lean_dec(v___x_3331_);
v___x_3333_ = l_Array_ofFn___redArg(v___x_3332_, v___f_3330_);
return v___x_3333_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___boxed(lean_object* v_batch_3334_, lean_object* v_m_3335_, lean_object* v_n_3336_, lean_object* v_p_3337_, lean_object* v_A_3338_, lean_object* v_B_3339_){
_start:
{
lean_object* v_res_3340_; 
v_res_3340_ = lp_competition_Submission_referenceBmm(v_batch_3334_, v_m_3335_, v_n_3336_, v_p_3337_, v_A_3338_, v_B_3339_);
lean_dec(v_batch_3334_);
return v_res_3340_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_hoistedBmm_spec__0(lean_object* v_A_3341_, lean_object* v_baseA_3342_, lean_object* v_B_3343_, lean_object* v_p_3344_, lean_object* v_baseB_3345_, lean_object* v_n_3346_, uint32_t v_x_3347_, lean_object* v_i_3348_){
_start:
{
uint32_t v___y_3350_; uint32_t v___y_3351_; uint8_t v___x_3357_; 
v___x_3357_ = lean_nat_dec_lt(v_i_3348_, v_n_3346_);
if (v___x_3357_ == 0)
{
lean_dec(v_i_3348_);
return v_x_3347_;
}
else
{
lean_object* v___x_3358_; uint32_t v___x_3359_; uint32_t v___y_3361_; lean_object* v___x_3368_; uint8_t v___x_3369_; 
v___x_3358_ = lean_nat_add(v_baseA_3342_, v_i_3348_);
v___x_3359_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_3368_ = lean_array_get_size(v_A_3341_);
v___x_3369_ = lean_nat_dec_lt(v___x_3358_, v___x_3368_);
if (v___x_3369_ == 0)
{
lean_dec(v___x_3358_);
v___y_3361_ = v___x_3359_;
goto v___jp_3360_;
}
else
{
lean_object* v___x_3370_; uint32_t v___x_3371_; 
v___x_3370_ = lean_array_fget_borrowed(v_A_3341_, v___x_3358_);
lean_dec(v___x_3358_);
v___x_3371_ = lean_unbox_uint32(v___x_3370_);
v___y_3361_ = v___x_3371_;
goto v___jp_3360_;
}
v___jp_3360_:
{
lean_object* v___x_3362_; lean_object* v___x_3363_; lean_object* v___x_3364_; uint8_t v___x_3365_; 
v___x_3362_ = lean_nat_mul(v_i_3348_, v_p_3344_);
v___x_3363_ = lean_nat_add(v_baseB_3345_, v___x_3362_);
lean_dec(v___x_3362_);
v___x_3364_ = lean_array_get_size(v_B_3343_);
v___x_3365_ = lean_nat_dec_lt(v___x_3363_, v___x_3364_);
if (v___x_3365_ == 0)
{
lean_dec(v___x_3363_);
v___y_3350_ = v___y_3361_;
v___y_3351_ = v___x_3359_;
goto v___jp_3349_;
}
else
{
lean_object* v___x_3366_; uint32_t v___x_3367_; 
v___x_3366_ = lean_array_fget_borrowed(v_B_3343_, v___x_3363_);
lean_dec(v___x_3363_);
v___x_3367_ = lean_unbox_uint32(v___x_3366_);
v___y_3350_ = v___y_3361_;
v___y_3351_ = v___x_3367_;
goto v___jp_3349_;
}
}
}
v___jp_3349_:
{
uint32_t v___x_3352_; uint32_t v___x_3353_; lean_object* v___x_3354_; lean_object* v___x_3355_; 
v___x_3352_ = lp_competition_Submission_FastMul_mul(v___y_3350_, v___y_3351_);
v___x_3353_ = lp_competition_Submission_TunedAdd_add(v_x_3347_, v___x_3352_);
v___x_3354_ = lean_unsigned_to_nat(1u);
v___x_3355_ = lean_nat_add(v_i_3348_, v___x_3354_);
lean_dec(v_i_3348_);
v_x_3347_ = v___x_3353_;
v_i_3348_ = v___x_3355_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_hoistedBmm_spec__0___boxed(lean_object* v_A_3372_, lean_object* v_baseA_3373_, lean_object* v_B_3374_, lean_object* v_p_3375_, lean_object* v_baseB_3376_, lean_object* v_n_3377_, lean_object* v_x_3378_, lean_object* v_i_3379_){
_start:
{
uint32_t v_x_boxed_3380_; uint32_t v_res_3381_; lean_object* v_r_3382_; 
v_x_boxed_3380_ = lean_unbox_uint32(v_x_3378_);
lean_dec(v_x_3378_);
v_res_3381_ = lp_competition_Fin_foldl_loop___at___00Submission_hoistedBmm_spec__0(v_A_3372_, v_baseA_3373_, v_B_3374_, v_p_3375_, v_baseB_3376_, v_n_3377_, v_x_boxed_3380_, v_i_3379_);
lean_dec(v_n_3377_);
lean_dec(v_baseB_3376_);
lean_dec(v_p_3375_);
lean_dec_ref(v_B_3374_);
lean_dec(v_baseA_3373_);
lean_dec_ref(v_A_3372_);
v_r_3382_ = lean_box_uint32(v_res_3381_);
return v_r_3382_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_hoistedBmm___lam__0(lean_object* v_m_3383_, lean_object* v_p_3384_, lean_object* v_n_3385_, lean_object* v_A_3386_, lean_object* v_B_3387_, lean_object* v_q_3388_){
_start:
{
lean_object* v___x_3389_; lean_object* v_snd_3390_; lean_object* v_fst_3391_; lean_object* v_fst_3392_; lean_object* v_snd_3393_; lean_object* v___x_3394_; lean_object* v___x_3395_; lean_object* v_baseA_3396_; lean_object* v___x_3397_; lean_object* v___x_3398_; lean_object* v_baseB_3399_; lean_object* v___x_3400_; uint32_t v___x_3401_; uint32_t v___x_3402_; 
v___x_3389_ = lp_competition_Competition_bmmDecodeC(v_m_3383_, v_p_3384_, v_q_3388_);
v_snd_3390_ = lean_ctor_get(v___x_3389_, 1);
lean_inc(v_snd_3390_);
v_fst_3391_ = lean_ctor_get(v___x_3389_, 0);
lean_inc(v_fst_3391_);
lean_dec_ref(v___x_3389_);
v_fst_3392_ = lean_ctor_get(v_snd_3390_, 0);
lean_inc(v_fst_3392_);
v_snd_3393_ = lean_ctor_get(v_snd_3390_, 1);
lean_inc(v_snd_3393_);
lean_dec(v_snd_3390_);
v___x_3394_ = lean_nat_mul(v_fst_3391_, v_m_3383_);
v___x_3395_ = lean_nat_add(v___x_3394_, v_fst_3392_);
lean_dec(v_fst_3392_);
lean_dec(v___x_3394_);
v_baseA_3396_ = lean_nat_mul(v___x_3395_, v_n_3385_);
lean_dec(v___x_3395_);
v___x_3397_ = lean_nat_mul(v_fst_3391_, v_n_3385_);
lean_dec(v_fst_3391_);
v___x_3398_ = lean_nat_mul(v___x_3397_, v_p_3384_);
lean_dec(v___x_3397_);
v_baseB_3399_ = lean_nat_add(v___x_3398_, v_snd_3393_);
lean_dec(v_snd_3393_);
lean_dec(v___x_3398_);
v___x_3400_ = lean_unsigned_to_nat(0u);
v___x_3401_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_3402_ = lp_competition_Fin_foldl_loop___at___00Submission_hoistedBmm_spec__0(v_A_3386_, v_baseA_3396_, v_B_3387_, v_p_3384_, v_baseB_3399_, v_n_3385_, v___x_3401_, v___x_3400_);
lean_dec(v_baseB_3399_);
lean_dec(v_baseA_3396_);
return v___x_3402_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_hoistedBmm___lam__0___boxed(lean_object* v_m_3403_, lean_object* v_p_3404_, lean_object* v_n_3405_, lean_object* v_A_3406_, lean_object* v_B_3407_, lean_object* v_q_3408_){
_start:
{
uint32_t v_res_3409_; lean_object* v_r_3410_; 
v_res_3409_ = lp_competition_Submission_hoistedBmm___lam__0(v_m_3403_, v_p_3404_, v_n_3405_, v_A_3406_, v_B_3407_, v_q_3408_);
lean_dec(v_q_3408_);
lean_dec_ref(v_B_3407_);
lean_dec_ref(v_A_3406_);
lean_dec(v_n_3405_);
lean_dec(v_p_3404_);
lean_dec(v_m_3403_);
v_r_3410_ = lean_box_uint32(v_res_3409_);
return v_r_3410_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_hoistedBmm(lean_object* v_batch_3411_, lean_object* v_m_3412_, lean_object* v_n_3413_, lean_object* v_p_3414_, lean_object* v_A_3415_, lean_object* v_B_3416_){
_start:
{
lean_object* v___f_3417_; lean_object* v___x_3418_; lean_object* v___x_3419_; lean_object* v___x_3420_; 
lean_inc(v_p_3414_);
lean_inc(v_m_3412_);
v___f_3417_ = lean_alloc_closure((void*)(lp_competition_Submission_hoistedBmm___lam__0___boxed), 6, 5);
lean_closure_set(v___f_3417_, 0, v_m_3412_);
lean_closure_set(v___f_3417_, 1, v_p_3414_);
lean_closure_set(v___f_3417_, 2, v_n_3413_);
lean_closure_set(v___f_3417_, 3, v_A_3415_);
lean_closure_set(v___f_3417_, 4, v_B_3416_);
v___x_3418_ = lean_nat_mul(v_batch_3411_, v_m_3412_);
lean_dec(v_m_3412_);
v___x_3419_ = lean_nat_mul(v___x_3418_, v_p_3414_);
lean_dec(v_p_3414_);
lean_dec(v___x_3418_);
v___x_3420_ = l_Array_ofFn___redArg(v___x_3419_, v___f_3417_);
return v___x_3420_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_hoistedBmm___boxed(lean_object* v_batch_3421_, lean_object* v_m_3422_, lean_object* v_n_3423_, lean_object* v_p_3424_, lean_object* v_A_3425_, lean_object* v_B_3426_){
_start:
{
lean_object* v_res_3427_; 
v_res_3427_ = lp_competition_Submission_hoistedBmm(v_batch_3421_, v_m_3422_, v_n_3423_, v_p_3424_, v_A_3425_, v_B_3426_);
lean_dec(v_batch_3421_);
return v_res_3427_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_bmm___lam__0(lean_object* v_baseA_3428_, lean_object* v_p_3429_, lean_object* v_baseB_3430_, lean_object* v_B_3431_, lean_object* v_A_3432_, lean_object* v_k_3433_){
_start:
{
lean_object* v___x_3434_; uint32_t v___x_3435_; uint32_t v___y_3437_; lean_object* v___x_3446_; uint8_t v___x_3447_; 
v___x_3434_ = lean_nat_add(v_baseA_3428_, v_k_3433_);
v___x_3435_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_3446_ = lean_array_get_size(v_A_3432_);
v___x_3447_ = lean_nat_dec_lt(v___x_3434_, v___x_3446_);
if (v___x_3447_ == 0)
{
lean_dec(v___x_3434_);
v___y_3437_ = v___x_3435_;
goto v___jp_3436_;
}
else
{
lean_object* v___x_3448_; uint32_t v___x_3449_; 
v___x_3448_ = lean_array_fget_borrowed(v_A_3432_, v___x_3434_);
lean_dec(v___x_3434_);
v___x_3449_ = lean_unbox_uint32(v___x_3448_);
v___y_3437_ = v___x_3449_;
goto v___jp_3436_;
}
v___jp_3436_:
{
lean_object* v___x_3438_; lean_object* v___x_3439_; lean_object* v___x_3440_; uint8_t v___x_3441_; 
v___x_3438_ = lean_nat_mul(v_k_3433_, v_p_3429_);
v___x_3439_ = lean_nat_add(v_baseB_3430_, v___x_3438_);
lean_dec(v___x_3438_);
v___x_3440_ = lean_array_get_size(v_B_3431_);
v___x_3441_ = lean_nat_dec_lt(v___x_3439_, v___x_3440_);
if (v___x_3441_ == 0)
{
uint32_t v___x_3442_; 
lean_dec(v___x_3439_);
v___x_3442_ = lp_competition_Submission_FastMul_mul(v___y_3437_, v___x_3435_);
return v___x_3442_;
}
else
{
lean_object* v___x_3443_; uint32_t v___x_3444_; uint32_t v___x_3445_; 
v___x_3443_ = lean_array_fget_borrowed(v_B_3431_, v___x_3439_);
lean_dec(v___x_3439_);
v___x_3444_ = lean_unbox_uint32(v___x_3443_);
v___x_3445_ = lp_competition_Submission_FastMul_mul(v___y_3437_, v___x_3444_);
return v___x_3445_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0___boxed(lean_object* v_baseA_3450_, lean_object* v_p_3451_, lean_object* v_baseB_3452_, lean_object* v_B_3453_, lean_object* v_A_3454_, lean_object* v_k_3455_){
_start:
{
uint32_t v_res_3456_; lean_object* v_r_3457_; 
v_res_3456_ = lp_competition_Submission_bmm___lam__0(v_baseA_3450_, v_p_3451_, v_baseB_3452_, v_B_3453_, v_A_3454_, v_k_3455_);
lean_dec(v_k_3455_);
lean_dec_ref(v_A_3454_);
lean_dec_ref(v_B_3453_);
lean_dec(v_baseB_3452_);
lean_dec(v_p_3451_);
lean_dec(v_baseA_3450_);
v_r_3457_ = lean_box_uint32(v_res_3456_);
return v_r_3457_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_bmm___lam__1(lean_object* v_m_3458_, lean_object* v_p_3459_, lean_object* v_n_3460_, lean_object* v_B_3461_, lean_object* v_A_3462_, lean_object* v_q_3463_){
_start:
{
lean_object* v___x_3464_; lean_object* v_snd_3465_; lean_object* v_fst_3466_; lean_object* v_fst_3467_; lean_object* v_snd_3468_; lean_object* v___x_3469_; lean_object* v___x_3470_; lean_object* v_baseA_3471_; lean_object* v___x_3472_; lean_object* v___x_3473_; lean_object* v_baseB_3474_; lean_object* v___f_3475_; lean_object* v___x_3476_; lean_object* v___x_3477_; uint32_t v___x_3478_; lean_object* v___x_3479_; uint8_t v___x_3480_; 
v___x_3464_ = lp_competition_Competition_bmmDecodeC(v_m_3458_, v_p_3459_, v_q_3463_);
v_snd_3465_ = lean_ctor_get(v___x_3464_, 1);
lean_inc(v_snd_3465_);
v_fst_3466_ = lean_ctor_get(v___x_3464_, 0);
lean_inc(v_fst_3466_);
lean_dec_ref(v___x_3464_);
v_fst_3467_ = lean_ctor_get(v_snd_3465_, 0);
lean_inc(v_fst_3467_);
v_snd_3468_ = lean_ctor_get(v_snd_3465_, 1);
lean_inc(v_snd_3468_);
lean_dec(v_snd_3465_);
v___x_3469_ = lean_nat_mul(v_fst_3466_, v_m_3458_);
v___x_3470_ = lean_nat_add(v___x_3469_, v_fst_3467_);
lean_dec(v_fst_3467_);
lean_dec(v___x_3469_);
v_baseA_3471_ = lean_nat_mul(v___x_3470_, v_n_3460_);
lean_dec(v___x_3470_);
v___x_3472_ = lean_nat_mul(v_fst_3466_, v_n_3460_);
lean_dec(v_fst_3466_);
v___x_3473_ = lean_nat_mul(v___x_3472_, v_p_3459_);
lean_dec(v___x_3472_);
v_baseB_3474_ = lean_nat_add(v___x_3473_, v_snd_3468_);
lean_dec(v_snd_3468_);
lean_dec(v___x_3473_);
v___f_3475_ = lean_alloc_closure((void*)(lp_competition_Submission_bmm___lam__0___boxed), 6, 5);
lean_closure_set(v___f_3475_, 0, v_baseA_3471_);
lean_closure_set(v___f_3475_, 1, v_p_3459_);
lean_closure_set(v___f_3475_, 2, v_baseB_3474_);
lean_closure_set(v___f_3475_, 3, v_B_3461_);
lean_closure_set(v___f_3475_, 4, v_A_3462_);
v___x_3476_ = l_Array_ofFn___redArg(v_n_3460_, v___f_3475_);
v___x_3477_ = lean_unsigned_to_nat(0u);
v___x_3478_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_3479_ = lean_array_get_size(v___x_3476_);
v___x_3480_ = lean_nat_dec_lt(v___x_3477_, v___x_3479_);
if (v___x_3480_ == 0)
{
lean_dec_ref(v___x_3476_);
return v___x_3478_;
}
else
{
uint8_t v___x_3481_; 
v___x_3481_ = lean_nat_dec_le(v___x_3479_, v___x_3479_);
if (v___x_3481_ == 0)
{
if (v___x_3480_ == 0)
{
lean_dec_ref(v___x_3476_);
return v___x_3478_;
}
else
{
size_t v___x_3482_; size_t v___x_3483_; uint32_t v___x_3484_; 
v___x_3482_ = ((size_t)0ULL);
v___x_3483_ = lean_usize_of_nat(v___x_3479_);
v___x_3484_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(v___x_3476_, v___x_3482_, v___x_3483_, v___x_3478_);
lean_dec_ref(v___x_3476_);
return v___x_3484_;
}
}
else
{
size_t v___x_3485_; size_t v___x_3486_; uint32_t v___x_3487_; 
v___x_3485_ = ((size_t)0ULL);
v___x_3486_ = lean_usize_of_nat(v___x_3479_);
v___x_3487_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(v___x_3476_, v___x_3485_, v___x_3486_, v___x_3478_);
lean_dec_ref(v___x_3476_);
return v___x_3487_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__1___boxed(lean_object* v_m_3488_, lean_object* v_p_3489_, lean_object* v_n_3490_, lean_object* v_B_3491_, lean_object* v_A_3492_, lean_object* v_q_3493_){
_start:
{
uint32_t v_res_3494_; lean_object* v_r_3495_; 
v_res_3494_ = lp_competition_Submission_bmm___lam__1(v_m_3488_, v_p_3489_, v_n_3490_, v_B_3491_, v_A_3492_, v_q_3493_);
lean_dec(v_q_3493_);
lean_dec(v_m_3488_);
v_r_3495_ = lean_box_uint32(v_res_3494_);
return v_r_3495_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_3496_, lean_object* v_m_3497_, lean_object* v_n_3498_, lean_object* v_p_3499_, lean_object* v_A_3500_, lean_object* v_B_3501_){
_start:
{
lean_object* v___f_3502_; lean_object* v___x_3503_; lean_object* v___x_3504_; lean_object* v___x_3505_; 
lean_inc(v_p_3499_);
lean_inc(v_m_3497_);
v___f_3502_ = lean_alloc_closure((void*)(lp_competition_Submission_bmm___lam__1___boxed), 6, 5);
lean_closure_set(v___f_3502_, 0, v_m_3497_);
lean_closure_set(v___f_3502_, 1, v_p_3499_);
lean_closure_set(v___f_3502_, 2, v_n_3498_);
lean_closure_set(v___f_3502_, 3, v_B_3501_);
lean_closure_set(v___f_3502_, 4, v_A_3500_);
v___x_3503_ = lean_nat_mul(v_batch_3496_, v_m_3497_);
lean_dec(v_m_3497_);
v___x_3504_ = lean_nat_mul(v___x_3503_, v_p_3499_);
lean_dec(v_p_3499_);
lean_dec(v___x_3503_);
v___x_3505_ = l_Array_ofFn___redArg(v___x_3504_, v___f_3502_);
return v___x_3505_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___boxed(lean_object* v_batch_3506_, lean_object* v_m_3507_, lean_object* v_n_3508_, lean_object* v_p_3509_, lean_object* v_A_3510_, lean_object* v_B_3511_){
_start:
{
lean_object* v_res_3512_; 
v_res_3512_ = lp_competition_Submission_bmm(v_batch_3506_, v_m_3507_, v_n_3508_, v_p_3509_, v_A_3510_, v_B_3511_);
lean_dec(v_batch_3506_);
return v_res_3512_;
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
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
